#ifndef teamMember_hpp
#define teamMember_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class TeamMember {
public:
    TeamMember();
    TeamMember(string given_username);
    void setUsername(string given_username) {username = given_username;}
    string getUsername() {return username;}
    bool isMemberOf(vector<TeamMember> teammates);
    friend ostream& operator<<(ostream& out, const TeamMember& member);
    TeamMember& operator=(const TeamMember& given_issue);
    
    
private:
    // team member username
    string username;
    
};

#endif
