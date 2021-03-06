#include "teamMember.hpp"
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

TeamMember::TeamMember() {
  this->username = "";
}

TeamMember::TeamMember(string given_username) {
    this->username = given_username;
}

//test with the given user
bool TeamMember::isMemberOf(vector<TeamMember> teammates) {
    bool found = false;
    for(int i = 0; i < teammates.size(); i++) {
        if(this->username == teammates[i].getUsername()) {
            found = true;
        }
    }
    return found;
}

//cout operator
ostream& operator<<(ostream& out, const TeamMember& member) {
    out<<member.username;
    return out;
}

//assigning operator
TeamMember& TeamMember::operator=(const TeamMember& given_issue) {
    this->username = given_issue.username;

    return *this;
}
