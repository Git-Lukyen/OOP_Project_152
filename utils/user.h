#ifndef AVIZIER_USER

#define AVIZIER_USER

#include <string>
#include <ctime>
#include <vector>
#include <set>
#include <optional>
#include <unordered_set>
#include "categories.h"

namespace avizier {
    class User {
    private:
        std::string username;
        short unsigned int initial_age;
        std::unordered_set<post_category> interests;
        std::unordered_set<skill_category> skills;
        time_t register_date;

    protected:
        int followers;

        int get_followers() {
            return this->followers;
        }

    public:
        void set_name(std::string &new_name) {
            username = new_name;
        }

        std::string get_username() const {
            return username;
        }

        std::unordered_set<post_category> get_interests() {
            return interests;
        }

        void add_interests(std::unordered_set<post_category> &new_interests) {
            interests.insert(new_interests.begin(), new_interests.end());
        }

        void remove_interests(std::unordered_set<post_category> &lost_interests) {
            interests.erase(lost_interests.begin(), lost_interests.end());
        }

        std::unordered_set<skill_category> get_skills() {
            return skills;
        }

        void add_skills(std::unordered_set<skill_category> &new_skills) {
            skills.insert(new_skills.begin(), new_skills.end());
        }

        void remove_skills(std::unordered_set<skill_category> &lost_skills) {
            skills.erase(lost_skills.begin(), lost_skills.end());
        }

        unsigned int get_age() {
            unsigned int register_year = 1900 + std::localtime(&register_date)->tm_year;

            time_t current_time = time(nullptr);
            unsigned int current_year = 1900 + std::localtime(&current_time)->tm_year;

            return current_year - register_year + initial_age;
        }

        explicit User(short unsigned int &age) {
            initial_age = age;
            register_date = time(nullptr);
        }

        User &operator=(const User &user) = default;

        friend std::ostream &operator<<(std::ostream &stream, User &user) {
            stream << "\n";
            stream << "Name: " << user.get_username();
            stream << "\n";
            stream << "Age: " << user.get_age();
            stream << "\n";
            stream << "Interests: ";
            for (auto interest: user.get_interests())
                stream << get_category_text(interest) << ", ";
            stream << "\n";
            stream << "Skills: ";
            for (auto skill: user.get_skills())
                stream << get_category_text(skill) << ", ";
            stream << "\n";

            return stream;
        };

        bool operator==(const User &user) const {
            return this->username == user.username;
        };
    };

    class Editor : public User {
    private:
        int nr_posts_created = 0;
        bool is_verified = false;

    public:
        Editor(short unsigned int &age) : User(age) {}
    };

    class UserManager {
    private:
        std::vector<User> users;

    public:
        UserManager() = default;

        std::vector<User> get_users() {
            return users;
        }

        std::optional<User> get_user(int index) {
            if (index < 0 || index >= users.size())
                return std::nullopt;

            return users[index];
        }

        std::optional<User> get_user(std::string &username) {
            for (const User &user: users) {
                if (user.get_username() == username)
                    return user;
            }

            return std::nullopt;
        }

        int get_user_index(const User &user) {
            int index = 0;

            for (const auto &user_it: users) {
                if (user_it == user)
                    return index;
                index++;
            }

            return -1;
        }

        int get_user_index(const std::string &username) {
            int index = 0;

            for (const auto &user_it: users) {
                if (user_it.get_username() == username)
                    return index;
                index++;
            }

            return -1;
        }

        void add_user(const User &new_user) {
            if (get_user_index(new_user) >= 0)
                return;

            users.push_back(new_user);
        }

        void add_users(const std::vector<User> &new_users) {
            for (const User &user: new_users)
                add_user(user);
        }

        void remove_users(std::vector<User> &lost_users) {
            users.erase(lost_users.begin(), lost_users.end());
        }

        void remove_user(int index) {
            if (index < 0 || index >= users.size())
                return;

            users.erase(std::next(users.begin(), index));
        }

        void remove_user(const std::string &username) {
            int index = get_user_index(username);

            remove_user(index);
        }


        static User
        create_user(std::string username, int age, std::unordered_set<post_category> initial_interests,
                    std::unordered_set<skill_category> initial_skills) {

            User user = User(reinterpret_cast<unsigned short &>(age));
            user.set_name(username);
            user.add_interests(initial_interests);
            user.add_skills(initial_skills);

            return user;
        }
    };
}

#endif //AVIZIER_USER
