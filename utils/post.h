#include <utility>
#include "exceptions.h"

#ifndef OOP_PROJECT_152_POST_H
#define OOP_PROJECT_152_POST_H

namespace avizier {
    class Post {
    private:
        std::string post_text;
        std::unordered_set<post_category> post_categories;
        std::unordered_set<skill_category> post_tags;
        time_t date_posted;

    protected:
        time_t date_modified;

        void set_string(std::string &new_text) {
            this->post_text = new_text;
            this->date_modified = time(nullptr);
        }

        time_t get_date_modified() {
            return this->date_modified;
        }

    public:
        Post(std::string post_text, std::unordered_set<post_category> categories,
             std::unordered_set<skill_category> tags) {
            this->post_text = post_text;
            this->post_categories = categories;
            this->post_tags = tags;

            date_posted = time(nullptr);
            date_modified = date_posted;
        }

        std::string get_text() {
            if (post_text.length() > 500)
                throw PostTextTooLongException();

            return this->post_text;
        }

        void display_post_text(std::ostream &stream) {
            if (post_text.length() > 500)
                throw PostTextTooLongException();

            stream << this->get_text();
        }

        std::string get_date_string() {
            return ctime(&date_posted);
        }

        std::unordered_set<post_category> get_categories() {
            return post_categories;
        }

        std::unordered_set<skill_category> get_tags() {
            return post_tags;
        }

        Post &operator=(const Post &user) = default;

        friend std::ostream &operator<<(std::ostream &stream, Post &post) {
            stream << "\n";
            stream << "Date Posted: " << post.get_date_string();

            try {
                stream << "Text: " << post.get_text();
            } catch (PostTextTooLongException &exception) {
                stream << "Text too long...";
            }

            stream << "\n";
            stream << "Categories: ";
            for (auto category: post.get_categories())
                stream << get_category_text(category) << ", ";
            stream << "\n";
            stream << "Tags: ";
            for (auto tag: post.get_tags())
                stream << get_category_text(tag) << ", ";
            stream << "\n";

            return stream;
        };

        virtual int get_annual_salary() {
            return 0;
        };

        virtual void update_requirements(std::string new_requirements) {

        };

        virtual void print_extra_info(std::ostream &stream) {

        };
    };

    class JobPosting : public Post {
    private:
        int salary;
        time_t start_date;
        std::string requirements;

    public:
        JobPosting(std::string post_text, std::unordered_set<post_category> categories,
                   std::unordered_set<skill_category> tags, std::string requirements, int salary, time_t start_date)
                : Post(post_text, categories,
                       tags) {

            this->requirements = requirements;
            this->salary = salary;
            this->start_date = start_date;
        }

        int get_annual_salary() override {
            return this->salary * 12;
        }

        void update_requirements(std::string new_requirements) override {
            this->requirements = new_requirements;
        }

        void print_extra_info(std::ostream &stream) override {

            // A case of dynamic dispatch
            stream << "Annual Salary: " << this->get_annual_salary() << "\n";
            stream << "\n";
            stream << "Job Requirements: " << requirements;
            stream << "\n";
        }
    };

    class PostManager {
    private:
        std::vector<Post> posts;

    public:
        PostManager() = default;

        std::vector<Post> get_posts() {
            return posts;
        }

        void add_post(const Post &new_post) {
            posts.push_back(new_post);
        }

        void remove_post(int index) {
            if (index < 0 || index >= posts.size())
                return;

            posts.erase(std::next(posts.begin(), index));
        }

        void add_posts(const std::vector<Post> &new_posts) {
            for (auto &new_post: new_posts)
                add_post(new_post);
        }

        static bool check_contains(const std::unordered_set<post_category> &category_set1,
                                   const std::unordered_set<post_category> &category_set2) {
            for (auto &category: category_set2)
                if (category_set1.contains(category))
                    return true;

            return false;
        }

        static bool check_contains(const std::unordered_set<skill_category> &tags_set1,
                                   const std::unordered_set<skill_category> &tags_set2) {
            for (auto &category: tags_set2)
                if (tags_set1.contains(category))
                    return true;

            return false;
        }

        std::vector<Post> get_recommended(const std::unordered_set<post_category> &categories,
                                          const std::unordered_set<skill_category> &tags) {
            std::vector<Post> recommended_posts;

            for (Post &post: posts)
                if (check_contains(categories, post.get_categories()) || check_contains(tags, post.get_tags()))
                    recommended_posts.push_back(post);

            return recommended_posts;
        }

        std::vector<Post> get_recommended(User &user) {
            std::vector<Post> recommended_posts;

            for (Post &post: posts)
                if (check_contains(user.get_interests(), post.get_categories()) ||
                    check_contains(user.get_skills(), post.get_tags()))
                    recommended_posts.push_back(post);

            return recommended_posts;
        }

    };
}

#endif //OOP_PROJECT_152_POST_H
