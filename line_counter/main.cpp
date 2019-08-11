#include <iostream>
#include <fstream>
#include <dirent.h>
#include <string>

using namespace std;

int main()
{
    cout<<"Counting the number of lines in files located in the current folder\nwith the extension .h .c .cpp or .rc"<<endl;

    DIR *dirp;
    struct dirent *dp;

    //open dir
    if((dirp = opendir(".")) == NULL)
    {
        cout<<"ERROR: Could not open current directory\n";
        return 1;
    }

    //read dir
    int numof_files=0;
    int numof_lines=0;
    int numof_files_ex=0;
    int numof_lines_ex=0;
    do
    {
        if( (dp=readdir(dirp)) != NULL )
        {
            //cout<<dp->d_name<<endl;
            string file_name(dp->d_name);

            //find dot
            for(int i=0;i<(int)file_name.size();i++)
            {
                if(file_name[i]=='.')
                {
                    bool read_this_file=false;
                    //test .h and .c extension
                    if(i==(int)file_name.size()-2)
                    {
                        if(file_name[i+1]=='h' || file_name[i+1]=='c') read_this_file=true;
                    }
                    //test .cpp
                    else if(i==(int)file_name.size()-4)
                    {
                        if(file_name[i+1]=='c' &&
                           file_name[i+2]=='p' &&
                           file_name[i+3]=='p') read_this_file=true;
                    }
                    //test .rc
                    else if(i==(int)file_name.size()-3)
                    {
                        if(file_name[i+1]=='r' &&
                           file_name[i+2]=='c') read_this_file=true;
                    }

                    //read number of \n
                    if(read_this_file)
                    {
                        numof_files++;
                        if(file_name!="files_in_text.cpp")
                         numof_files_ex++;

                        ifstream file(dp->d_name);
                        if(file==0)
                        {
                            cout<<"ERROR: Could not read the file: "<<dp->d_name<<endl;
                            return 1;
                        }

                        string line;
                        while(getline(file,line))
                        {
                            numof_lines++;
                            if(file_name!="files_in_text.cpp")
                             numof_lines_ex++;
                        }

                        file.close();
                    }
                }
            }
        }
    }
    while(dp != NULL);

    //done
    closedir(dirp);

    //report lines of code
    cout<<"\n "<<numof_lines<<" lines of code in "<<numof_files<<" files\n";

    //test if special file found
    if(numof_lines!=numof_lines_ex)
    {
        cout<<"If excluding the file \"files_in_text.cpp\"";
        cout<<"\n "<<numof_lines_ex<<" lines of code in "<<numof_files_ex<<" files\n";
    }

    cout<<"\nPress ENTER to quit\n";
    string trap;
    getline(cin,trap);

    return 0;
}
