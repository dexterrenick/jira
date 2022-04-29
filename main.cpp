// Dexter, Grace, Khai
// main.cpp
// Run Jira Simulation
// Version 0.0.1
#define _GLIBCXX_USE_NANOSLEEP

#include "project.hpp"
#include "teamMember.hpp"
#include "issue.hpp"
#include "sprint.hpp"
#include "jira.hpp"
#include <future>
#include <thread>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <functional>

using namespace std;


int main() {
    TeamMember alex = TeamMember("Alex123");
    TeamMember ben = TeamMember("Ben134");
    TeamMember charles = TeamMember("Charles422");
    TeamMember emily = TeamMember("Emily082");
    TeamMember fenix = TeamMember("Fenix294");
    TeamMember harry = TeamMember("Harry1083");
    
    vector<TeamMember> docsLeads = vector<TeamMember>();
    docsLeads.push_back(ben);
    docsLeads.push_back(charles);

    vector<TeamMember> docsDevelop = vector<TeamMember>();
    docsDevelop.push_back(emily);
    docsDevelop.push_back(fenix);
    docsDevelop.push_back(harry);

    Project p1 = Project("Docs", 12, alex, docsLeads, docsDevelop);

    cout<<"Test"<<endl;
    
    
    // Jira j = Jira();

    // std::launch::async(Jira::runTimer);

    return -1;
}
