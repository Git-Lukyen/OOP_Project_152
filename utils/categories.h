#ifndef AVIZIER_CATEGORIES

#define AVIZIER_CATEGORIES

#include <string>
#include <map>

namespace avizier {
    enum post_category {
        internship, job, contest, workshop, summer_camp, meet_and_greet
    };

    enum skill_category {
        python, java, scala, c, cpp, oop, functional, unix, docker, data_bases, critical_thinking, problem_solving
    };

    static std::map<post_category, std::string> post_category_string_name{{internship, "Internship"},
                                                                          {job, "Job Opportunity"},
                                                                          {contest, "Programming Contest"},
                                                                          {workshop, "Workshop"},
                                                                          {summer_camp, "Summer Camp"},
                                                                          {meet_and_greet, "Meet & Greet"}};

    static std::map<skill_category, std::string> skill_category_string_name{{python,            "Python"},
                                                                            {java,              "Java"},
                                                                            {scala,             "Scala"},
                                                                            {c,                 "C Language"},
                                                                            {cpp,               "C++"},
                                                                            {oop,               "Object Oriented Programming"},
                                                                            {functional,        "Functional Programming"},
                                                                            {unix,              "UNIX"},
                                                                            {docker,            "Docker"},
                                                                            {data_bases,        "Data Bases"},
                                                                            {critical_thinking, "Critical Thinking"},
                                                                            {problem_solving,   "Problem Solving"}};

    std::string get_category_text(post_category &category) {
        return post_category_string_name[category];
    }

    std::string get_category_text(skill_category &category) {
        return skill_category_string_name[category];
    }
}

#endif //AVIZIER_CATEGORIES