#ifndef teamMember_hpp
#define teamMember_hpp

#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

class TeamMember {
public:
    TeamMember(string given_username);
    void setUsername(string given_username) {username = given_username;}
    string getUsername() {return username;}

private:
    // team member username
    string username;
    
};

#endif