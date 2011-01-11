#include "FileUtils.h"
#include <fstream>

#include <stdio.h>
#include <sys/stat.h>

//#include <cstdio>
//#include <boost/filesystem/operations.hpp>

int FileUtils::GetFileSize(const char* filename)
{
	std::ifstream f;
	f.open(filename, std::ios_base::binary | std::ios_base::in);
	if (!f.good() || f.eof() || !f.is_open()) { return 0; }
	f.seekg(0, std::ios_base::beg);
	std::ifstream::pos_type begin_pos = f.tellg();
	f.seekg(0, std::ios_base::end);
	return static_cast<int>(f.tellg() - begin_pos);
}

bool FileUtils::FileExists(const char* filename)
{
	std::ifstream file;
	file.open(filename);
	if(file.is_open())
	{
		file.close();
		return true;
	}
	file.close();
	return false;
}

bool FileUtils::FileExists(const std::string & filename)
{
    return FileExists(filename.c_str());
}

// jakas inna implementacja, z CGameOptions.cpp
//bool FileExists( const std::string& filename )
//{
//    std::ifstream f( filename.c_str(), std::ios::in );
//    f.close();
//    return ( !f.fail() );
//}


#ifdef PLATFORM_LINUX
#include <wordexp.h>
static std::string gUserDir = "~/.WarlocksGauntlet/";
static bool gInitialized = false;
const std::string & FileUtils::GetUserDir()
{
    if (!gInitialized) {
        wordexp_t exp_result;
        wordexp("~/.WarlocksGauntlet/", &exp_result, 0);
        gUserDir = exp_result.we_wordv[0];
        wordfree(&exp_result);

        //inny sposob: char * home = getenv("HOME");

        fprintf(stderr, "Detected userDir as `%s'\n", gUserDir.c_str());

        gInitialized = true;
    }
    return gUserDir;
}
#endif    

#ifdef PLATFORM_MACOSX
extern "C" const char * CreateDirectoryIfNotExists(const char *dname);
const std::string & FileUtils::GetUserDir()
{
    return CreateDirectoryIfNotExists((std::string("~/Library/WarlocksGauntlet")+CGameOptions::mModDir).c_str());
}
#endif

#ifdef PLATFORM_WINDOWS
const std::string & FileUtils::GetUserDir()
{
    return "user/"
}
#endif


void FileUtils::InitializeUserDir()
{
    fprintf(stderr, "Initializing user dir...\n");
    mkdir(GetUserDir().c_str(), 0700);
    //i tutaj reszta inicjalizacji - kopiowanie 'first_game', 'config.xml' itepe itede
    // mozna tez pomyslec o tym, aby przy uruchamianu WarlocksGauntlet.exe --clean-user-dir 
    // skasowac ten katalog i na nowo go tworzyc
}

/*
* A function to list all contents of a given directory
* author: Danny Battison
* contact: gabehabe@hotmail.com
*/ 

/*#include <dirent.h>

void FileUtils::listdir (const char *path)
{
    DIR *pdir = NULL; // remember, it's good practice to initialise a pointer to NULL!
    pdir = opendir (path); // "." will refer to the current directory
    struct dirent *pent = NULL;
    if (pdir == NULL) // if pdir wasn't initialised correctly
    { // print an error message and exit the program
        printf ("\nERROR! pdir could not be initialised correctly");
        return; // exit the function
    }
    while (pent = readdir (pdir)){
        if (pent == NULL) // if pent has not been initialised correctly
        { // print an error message, and exit the program
            printf ("\nERROR! pent could not be initialised correctly");
            return; // exit the function
        }
        // otherwise, it was initialised correctly. let's print it on the console:
        printf ("%s\n", pent->d_name);
    }
    // finally, let's close the directory
    closedir (pdir);
}
*/
