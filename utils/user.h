#include <string>
#include <ctime>
#include <vector>
#include <set>
#include "categories.h"

namespace avizier {
    class User {
    private:
        std::string username;
        short unsigned int initial_age;
        std::set<post_category> interests;
        std::set<skill_category> skills;
        time_t register_date;

        explicit User(short unsigned int &age) {
            initial_age = age;
            register_date = time(nullptr);
        }

    public:
        void set_name(std::string &new_name) {
            username = new_name;
        }

        std::set<post_category> get_interests() {
            return interests;
        }

        void add_interests(std::set<post_category> &new_interests) {
            interests.insert(new_interests.begin(), new_interests.end());
        }

        void remove_interests(std::set<post_category> &lost_interests) {
            interests.erase(lost_interests.begin(), lost_interests.end());
        }

        std::set<skill_category> get_skills() {
            return skills;
        }

        void add_skills(std::set<skill_category> &new_skills) {
            skills.insert(new_skills.begin(), new_skills.end());
        }

        void remove_skills(std::set<skill_category> &lost_skills) {
            skills.erase(lost_skills.begin(), lost_skills.end());
        }

        unsigned int get_age() {
            unsigned int register_year = 1900 + std::localtime(&register_date)->tm_year;

            time_t current_time = time(nullptr);
            unsigned int current_year = 1900 + std::localtime(&current_time)->tm_year;

            return current_year - register_year + initial_age;
        }


        static User
        create_user(std::string &username, short unsigned int &age, std::set<post_category> &initial_interests,
                    std::set<skill_category> &initial_skills) {

            User user = User(age);
            user.set_name(username);
            user.add_interests(initial_interests);
            user.add_skills(initial_skills);

            return user;
        }
    };
}
