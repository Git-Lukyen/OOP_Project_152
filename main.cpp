#include <iostream>
#include <unordered_set>
#include <fstream>
#include "avizier.h"

using namespace avizier;


int main() {
    std::ofstream output_file("output.txt");
    std::ostream &output_stream = std::cout;

    UserManager userManager = UserManager();
    PostManager postManager = PostManager();

    User user1 = UserManager::create_user(std::string("ariciu31"),
                                          23,
                                          std::unordered_set<post_category>{internship, job},
                                          std::unordered_set<skill_category>{java, scala});

    User user2 = UserManager::create_user(std::string("costel_gladiatorul"),
                                          19,
                                          std::unordered_set<post_category>{contest, workshop, summer_camp, internship},
                                          std::unordered_set<skill_category>{c, cpp, python, problem_solving});

    Post post1 = Post(std::string("Microsoft a inceput un nou program de internship pentru C/C++ software dev.\n"
                                  "Pentru mai multe detalii accesati link-ul de mai jos."),
                      std::unordered_set<post_category>{internship, job},
                      std::unordered_set<skill_category>{c, cpp, problem_solving});

    Post post2 = Post(std::string("Esti student si vrei sa inveti si pe timp de vara? Inscrie-te la summer camp-ul de invatat python."),
                      std::unordered_set<post_category>{summer_camp, workshop},
                      std::unordered_set<skill_category>{python, docker});

    userManager.add_users(std::vector<User>{user1, user2});
    postManager.add_posts(std::vector<Post>{post1, post2});

    output_stream << "\n==== USERS ====\n";
    for (User &user: userManager.get_users())
        output_stream << user;

    output_stream << "\n==== POSTS ====\n";
    for (Post &post: postManager.get_posts())
        output_stream << post;

    output_stream << "\n==== RECOMMENDED FOR " << user1.get_username() << " ====\n";
    auto recommended_posts_user1 = postManager.get_recommended(user1);
    for (Post &post: recommended_posts_user1)
        output_stream << post;

    output_stream << "\n==== FIRST USER IS " << userManager.get_user(0)->get_username() << " ====\n";
    output_stream << (User &) userManager.get_user(0).value();
    return 0;
}
