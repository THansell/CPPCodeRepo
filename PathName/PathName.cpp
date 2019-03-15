#include <cstring>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <linux/limits.h>
#include "PathName.h"

PathName::PathName() {
}

PathName::PathName(const std::string name) {
    this->setRawName( name );
}

PathName::PathName(const std::string dir, std::string base) {
    this->setDirBase( dir, base );
}

PathName::PathName(const std::string dir,
                   const std::string file,
                   const std::string ext) {
    this->setDirFileExt( dir, file, ext );
}

void PathName::clearMyNames() {
    this->myDirName.clear();
    this->myBaseName.clear();
    this->myFileName.clear();
    this->myExtension.clear();
}

typedef union {
    const char * tainted;
    const char * untainted;
} TaintRemover;

std::string untaint( const char * taint ) {
	TaintRemover tr;
    tr.tainted = taint;
    std::string antwort = tr.untainted ;
    return antwort;
}
    
void PathName::setRawName(const char* name) {
    this->clear();
    this->append(untaint(name));
}

void PathName::setRawName(std::string name) {
    this->clear();
    this->append( untaint(name.c_str()));
}

void PathName::setDirBase(std::string dir, std::string base) {
    if ( dir.empty() ) {
        this->setRawName( base );
    } else {
        this->setRawName( dir + "/" + base );
    }
}

void PathName::setDirFileExt(std::string dir,
                             std::string file,
                             std::string ext) {
    this->setDirBase( dir, file + ext );
}

void PathName::append(const std::string extension) {
    this->rawName.append(extension);
    this->clearMyNames();
}

void PathName::clear() {
    this->rawName.clear();
    this->clearMyNames();
}

std::string PathName::getRawName() {
    return( this->rawName );
}

std::string PathName::dirname() {
    if ( this->myDirName.empty() ) {
        if ( this->containsSlash() ) {
            this->myDirName = 
                this->rawName.substr(0,
                   this->rawName.find_last_of("/"));
        } else {
            this->myDirName = ".";
        }
    }
    return( this->myDirName );
}

std::string PathName::basename() {
    if ( this->myBaseName.empty() ) {
        this->myBaseName =
            this->rawName.substr(
                this->rawName.find_last_of("/") + 1 );
    }
    return( this->myBaseName );
}

std::string PathName::file() {
    if ( this->myFileName.empty() ) {
        this->myFileName = this->basename().substr(0, 
                this->basename().find_last_of("."));
    }
    return( this->myFileName );
}

std::string PathName::ext() {
    if ( this->myExtension.empty() ) {
        this->myExtension =
            this->basename().substr(
                this->basename().find_last_of("."));
    }
    return( this->myExtension );
}

bool PathName::exists() {
    char * canpath;
    if ( (canpath = canonicalize_file_name( this->rawName.c_str() )) ) {
        free( canpath );
        return( true ) ;
    } else {
        return( false );
    }
}

std::string PathName::canonicalize() {
    char * canpath;
    std::string canstring;
    if ( this->empty() ) {
        canstring = "";
    } else {
        if ( (canpath = canonicalize_file_name( this->rawName.c_str() )) ) {
            canstring = std::string( canpath );
            free( canpath );
        } else if ( ( canpath = canonicalize_file_name(
                    this->dirname().c_str()))) {
            canstring = std::string( canpath );
            free( canpath );
            canstring.append( "/" + this->basename() );
        } else {
            canstring = this->getRawName();
        }
    }
    return( canstring );
}

bool PathName::containsDots() {
    return( this->rawName.find("../") != this->rawName.npos );
}

bool PathName::containsSlash() {
    return( this->rawName.find("/") != this->rawName.npos );
}

bool PathName::isAbsolute() {
    return( this->rawName.front() == '/' && !this->containsDots() );
}

bool PathName::isRelative() {
    return( !this->isAbsolute() || this->containsDots() );
}

bool PathName::empty() {
    return( this->rawName.empty() ) ;
}

off_t PathName::fileSize() {
    if ( this->exists() ) {
        struct stat st;
        if (stat((const char *)this->canonicalize().c_str()
                , &st) != 0) {
            return(0);
        }
        return(st.st_size);
    }
    return(0);
}
