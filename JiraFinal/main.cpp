// Dexter, Grace, Khai
// main.cpp
// Run Jira Simulation
// Version 0.0.1

#include "project.hpp"
#include "teamMember.hpp"
#include "issue.hpp"
#include "sprint.hpp"
#include "jira.hpp"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


int main() {
  TeamMember* alex = new TeamMember("Alex123");
  TeamMember* ben = new TeamMember("Ben134");
  TeamMember* charles = new TeamMember("Charles422");
  TeamMember* emily = new TeamMember("Emily082");
  TeamMember* fenix = new TeamMember("Fenix294");
  TeamMember* harry = new TeamMember("Harry1083");

  vector<TeamMember*> allUsers;
  allUsers.push_back(alex);
  allUsers.push_back(ben);
  allUsers.push_back(charles);
  allUsers.push_back(emily);
  allUsers.push_back(fenix);
  allUsers.push_back(harry);
  
  vector<TeamMember*> docsLeads;
  docsLeads.push_back(ben);
  docsLeads.push_back(charles);

  vector<TeamMember*> docsDevelop;
  docsDevelop.push_back(emily);
  docsDevelop.push_back(fenix);
  docsDevelop.push_back(harry);
  
  Issue* docsIss1 = new Issue("Red", "in progress", "task", 3, 5, "Just a task", "must be done by emily", emily);
  Issue* docsIss2 = new Issue("Yellow", "in progress", "build", 2, 4, "build the issue", "very nice", fenix);
  Issue* docsIss3 = new Issue("Green", "in progress", "debug", 1, 3, "debug proj", "on track",harry);
  Issue* docsIss4 = new Issue("Red", "open", "user story", 2, 4, "how to make it simple", "very nice",charles);
  Issue* docsIss5 = new Issue("Yellow", "in progress", "build", 6, 8, "build the issue", "very nice",ben);
  Issue* docsIss6 = new Issue("Green", "done", "build", 0, 10, "open the project", "very nice", alex);
  
  vector<Issue*> docsloITodo;
  docsloITodo.push_back(docsIss4);
  
  vector<Issue*> docsloISp1;
  docsloISp1.push_back(docsIss1);
  docsloISp1.push_back(docsIss2);
  docsloISp1.push_back(docsIss3);
  Sprint* docsSprint1 = new Sprint(10, 8, docsloISp1);
  
  vector<Issue*> docsloISp2;
  docsloISp2.push_back(docsIss5);
  Sprint* docsSprint2 = new Sprint(15, 0, docsloISp2);
  
  vector<Sprint*> docsloSprint;
  docsloSprint.push_back(docsSprint1);
  docsloSprint.push_back(docsSprint2);
  
  vector<Issue*> docsloIDone;
  docsloIDone.push_back(docsIss6);

  Project* p1 = new Project("Docs", 10, docsloITodo, docsloSprint, docsloIDone, *alex, docsLeads, docsDevelop);
  
  vector<Project*> allProjects;
  allProjects.push_back(p1);
  
  Jira* j = new Jira(0, "", allProjects, allUsers);
  
  j->displaySignInUp();
  
  
  delete alex;
  delete ben;
  delete charles;
  delete emily;
  delete fenix;
  delete harry;

  delete docsIss1;
  delete docsIss2;
  delete docsIss3;
  delete docsIss4;
  delete docsIss5;
  delete docsIss6;

  docsloITodo.clear();
  docsloISp1.clear();
  docsloISp2.clear();
  docsloSprint.clear();
  docsloIDone.clear();

  delete p1;
  delete j;
  
  return 0;
}
