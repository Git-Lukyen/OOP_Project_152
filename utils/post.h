#ifndef OOP_PROJECT_152_POST_H
#define OOP_PROJECT_152_POST_H

namespace avizier {
    class Post {
    private:
        std::string post_text;
        std::unordered_set<post_category> post_categories;
        std::unordered_set<skill_category> post_tags;
        time_t date_posted;

    public:
        Post(std::string post_text, std::unordered_set<post_category> categories, std::unordered_set<skill_category> tags) {
            this->post_text = post_text;
            this->post_categories = categories;
            this->post_tags = tags;
            date_posted = time(nullptr);
        }

        std::string get_text() {
            return this->post_text;
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
            stream << "Text: " << post.get_text();
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

        void add_posts(const std::vector<Post>& new_posts) {
            for (auto &new_post: new_posts)
                add_post(new_post);
        }

        static bool check_contains(const std::unordered_set<post_category> &category_set1, const std::unordered_set<post_category> &category_set2) {
            for (auto &category: category_set2)
                if (category_set1.contains(category))
                    return true;

            return false;
        }

        static bool check_contains(const std::unordered_set<skill_category> &tags_set1, const std::unordered_set<skill_category> &tags_set2) {
            for (auto &category: tags_set2)
                if (tags_set1.contains(category))
                    return true;

            return false;
        }

        std::vector<Post> get_recommended(const std::unordered_set<post_category> &categories, const std::unordered_set<skill_category> &tags) {
            std::vector<Post> recommended_posts;

            for (Post &post: posts)
                if (check_contains(categories, post.get_categories()) || check_contains(tags, post.get_tags()))
                    recommended_posts.push_back(post);

            return recommended_posts;
        }

        std::vector<Post> get_recommended(User &user) {
            std::vector<Post> recommended_posts;

            for (Post &post: posts)
                if (check_contains(user.get_interests(), post.get_categories()) || check_contains(user.get_skills(), post.get_tags()))
                    recommended_posts.push_back(post);

            return recommended_posts;
        }

    };
}

#endif //OOP_PROJECT_152_POST_H
