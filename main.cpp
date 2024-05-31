#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>

// 用户角色枚举
enum class Role {
    ADMIN,
    CHEF,
    CUSTOMER
};

// 用户类
class User {
public:
    std::string username;
    Role role;

    User(std::string name, Role r) : username(name), role(r) {}
};

// 原材料信息
class Ingredient {
public:
    Ingredient() {

    }

    int id;
    std::string name;
    double price;
    int quantity;

    Ingredient(int i, std::string n, double p, int q) : id(i), name(n), price(p), quantity(q) {}
};

// 菜肴信息
class Dish {
public:
    Dish() {

    }

    int dishID;
    std::string name;
    double price;
    std::vector<Ingredient> ingredients;

    Dish(int id, std::string n, double p) : dishID(id), name(n), price(p) {}

    void addIngredient(const Ingredient &ingredient) {
        ingredients.push_back(ingredient);
    }
};

// 客户信息
class Customer {
public:
    Customer() {

    }
    Customer(int i, const std::string& name) : id(i), name(name) {}


    int id;
    std::string name;
    std::vector<Dish> orders;

    Customer(std::string n) : name(n) {}

    void orderDish(const Dish &dish) {
        orders.push_back(Dish(dish));
    }

    void removeDish(const Dish &dish) {
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            if (it->dishID == dish.dishID) {
                orders.erase(it);
                break;
            }
        }
    }
};

// 餐厅管理系统类
class RestaurantManagementSystem {
private:
    std::unordered_map<std::string, std::string> userLoginInfo;
    std::vector<Ingredient> ingredients;
    std::vector<Dish> menu;
    std::vector<Customer> customers;
    int nextIngredientId = 1;
    int nextDishId = 1;
    int nextCustomerId = 1;

public:
    RestaurantManagementSystem() {
        // 初始化用户登录信息
        userLoginInfo["admin"] = "adminpass";
        userLoginInfo["chef"] = "chefpass";
        userLoginInfo["customer1"] = "customerpass";
        userLoginInfo["customer2"] = "customerpass"; // 添加更多用户

        // 初始化一些菜肴
        menu.emplace_back(1, "Spaghetti Carbonara", 12.99);
        menu.emplace_back(2, "Margherita Pizza", 9.99);
        menu.emplace_back(3, "Caesar Salad", 7.99);
        // 初始化一些原材料
        ingredients.emplace_back(nextIngredientId++, "Tomatoes", 0.50, 150);
        ingredients.emplace_back(nextIngredientId++, "Basil", 0.30, 100);
        ingredients.emplace_back(nextIngredientId++, "Garlic", 0.20, 80);
        ingredients.emplace_back(nextIngredientId++, "Olive Oil", 1.00, 50);
        ingredients.emplace_back(nextIngredientId++, "Mozzarella", 2.00, 30);

        // 初始化一些顾客
        customers.push_back(Customer(nextCustomerId++,"customer1"));
        customers.push_back(Customer(nextCustomerId++,"customer2"));
        // ...


    }

    bool login(const std::string &username, const std::string &password) {
        return userLoginInfo[username] == password;
    }

    void showIngredient() {
        for (const auto &item: ingredients) {
            std::cout << item.id << " " << item.name << "" << item.price << " " << item.quantity
                      << std::endl;
        }
    }

    // 添加原材料
    void addIngredient() {
        Ingredient ing;
        std::cout << "Enter ingredient name: ";
        std::cin >> ing.name;
        std::cout << "Enter price: ";
        std::cin >> ing.price;
        std::cout << "Enter quantity: ";
        std::cin >> ing.quantity;
        ing.id = nextIngredientId++;
        ingredients.push_back(ing);
        std::cout << "Ingredient added successfully.\n";
    }

    // 删除原材料
    void removeIngredient() {
        int id;
        std::cout << "Enter ingredient ID to remove: ";
        std::cin >> id;
        ingredients.erase(std::remove_if(ingredients.begin(), ingredients.end(),
                                         [id](const Ingredient &ing) { return ing.id == id; }), ingredients.end());
        std::cout << "Ingredient removed successfully.\n";
    }

    // 更新原材料
    void updateIngredient() {
        int id;
        std::cout << "Enter ingredient ID to update: ";
        std::cin >> id;
        auto it = std::find_if(ingredients.begin(), ingredients.end(),
                               [id](const Ingredient &ing) { return ing.id == id; });
        if (it != ingredients.end()) {
            std::cout << "Enter new name: ";
            std::cin >> it->name;
            std::cout << "Enter new price: ";
            std::cin >> it->price;
            std::cout << "Enter new quantity: ";
            std::cin >> it->quantity;
            std::cout << "Ingredient updated successfully.\n";
        } else {
            std::cout << "Ingredient not found.\n";
        }
    }

    // 显示菜肴
    void showDish() {
        for (const auto &item: menu) {
            std::cout << item.dishID << " " << item.name << "" << item.price << std::endl;
        }
    }
    void showDish(User user) {
        auto cs = std::find_if(customers.begin(), customers.end(), [&user](const Customer& customer) {
            return customer.name == user.username;
        });
        for (const auto &item: cs->orders) {
            std::cout << item.dishID << " " << item.name << "" << item.price << std::endl;
        }
    }

    // 添加菜肴
    void addDish() {
        Dish dish;
        std::cout << "Enter dish name: ";
        std::cin >> dish.name;
        std::cout << "Enter price: ";
        std::cin >> dish.price;
        dish.dishID = nextDishId++;
        menu.push_back(dish);
        std::cout << "Dish added successfully.\n";
    }

    // 删除菜肴
    void removeDish() {
        int id;
        std::cout << "Enter dish ID to remove: ";
        std::cin >> id;
        menu.erase(std::remove_if(menu.begin(), menu.end(),
                                  [id](const Dish &dish) { return dish.dishID == id; }), menu.end());
        std::cout << "Dish removed successfully.\n";
    }

    // 更新菜肴
    void updateDish() {
        int id;
        std::cout << "Enter dish ID to update: ";
        std::cin >> id;
        auto it = std::find_if(menu.begin(), menu.end(),
                               [id](const Dish &dish) { return dish.dishID == id; });
        if (it != menu.end()) {
            std::cout << "Enter new name: ";
            std::cin >> it->name;
            std::cout << "Enter new price: ";
            std::cin >> it->price;
            std::cout << "Dish updated successfully.\n";
        } else {
            std::cout << "Dish not found.\n";
        }
    }

    // 显示客户
    void showCustomer() {
        for (const auto &item: customers) {
            std::cout << item.id << " " << item.name << std::endl;
        }
    }

    // 添加客户
    void addCustomer() {
        Customer customer;
        std::cout << "Enter customer name: ";
        std::cin >> customer.name;
        customer.id = nextCustomerId++;
        customers.push_back(customer);
        std::cout << "Customer added successfully.\n";
    }

    // 删除客户
    void removeCustomer() {
        int id;
        std::cout << "Enter customer ID to remove: ";
        std::cin >> id;
        customers.erase(std::remove_if(customers.begin(), customers.end(),
                                       [id](const Customer &cust) { return cust.id == id; }), customers.end());
        std::cout << "Customer removed successfully.\n";
    }

    // 更新客户
    void updateCustomer() {
        int id;
        std::cout << "Enter customer ID to update: ";
        std::cin >> id;
        auto it = std::find_if(customers.begin(), customers.end(),
                               [id](const Customer &cust) { return cust.id == id; });
        if (it != customers.end()) {
            std::cout << "Enter new name: ";
            std::cin >> it->name;
            std::cout << "Customer updated successfully.\n";
        } else {
            std::cout << "Customer not found.\n";
        }
    }

    // 查看订单
    void showOrder() {
        for (const auto &item: customers) {
            // 显示每个客户的订单
            std::cout << "Customer: " << item.name << "\n";
            double total = 0;
            for (const auto &order: item.orders) {
                std::cout << order.name << " " << order.price << "\n";
                total += order.price;
            }
            std::cout << "total price: " << total << "\n";
        }

    }

    void orderDish(User user) {
        showDish();
        std::cout << "Enter dish ID: ";
        int id;
        std::cin >> id;
        // 查找菜单中的菜肴
        auto dishIt = std::find_if(menu.begin(), menu.end(), [id](const Dish& dish) {
            return dish.dishID == id;
        });

        if (dishIt != menu.end()) {
            // 查找顾客
            auto cs = std::find_if(customers.begin(), customers.end(), [&user](const Customer& customer) {
                return customer.name == user.username;
            });

            if (cs != customers.end()) {
                // 将菜肴添加到顾客的订单中
                (*cs).orders.push_back(Dish(*dishIt));
                std::cout << "Dish ordered successfully.\n";
            } else {
                std::cout << "Customer not found.\n";
            }
        } else {
            std::cout << "Dish not found.\n";
        }
    }

    void cancelOrder(User user) {
        showDish(user);
        std::cout << "Enter dish ID: ";
        int id;
        std::cin >> id;
        // 查找菜单中的菜肴
        auto dishIt = std::find_if(menu.begin(), menu.end(), [id](const Dish& dish) {
            return dish.dishID == id;
        });

        if (dishIt != menu.end()) {
            // 获取用户名
            std::string username = user.username;

            // 查找顾客
            auto customerIt = std::find_if(customers.begin(), customers.end(), [username](const Customer& customer) {
                return customer.name == username;
            });

            if (customerIt != customers.end()) {
                // 查找顾客订单中的菜肴并移除
                auto orderIt = std::find_if(customerIt->orders.begin(), customerIt->orders.end(), [id](const Dish& order) {
                    return order.dishID == id;
                });

                if (orderIt != customerIt->orders.end()) {
                    customerIt->orders.erase(orderIt);
                    std::cout << "Order cancelled successfully.\n";
                } else {
                    std::cout << "Dish not found in your order.\n";
                }
            } else {
                std::cout << "Customer not found.\n";
            }
        } else {
            std::cout << "Dish not found.\n";
        }
    }

    // 管理员功能
    void adminTask() {
        int option;
        do {
            std::cout << "\nAdmin Menu:\n";
            std::cout << "1. Show Ingredient\n";
            std::cout << "2. Add Ingredient\n";
            std::cout << "3. Remove Ingredient\n";
            std::cout << "4. Update Ingredient\n";
            std::cout << "5. show Dish\n";
            std::cout << "6. Add Dish\n";
            std::cout << "7. Remove Dish\n";
            std::cout << "8. Update Dish\n";
            std::cout << "9. Show Customer\n";
            std::cout << "10. Add Customer\n";
            std::cout << "11. Remove Customer\n";
            std::cout << "12. Update Customer\n";
            std::cout << "13. Show Order\n";
            std::cout << "14. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> option;

            switch (option) {
                case 1:
                    showIngredient();
                    break;
                case 2:
                    addIngredient();
                    break;
                case 3:
                    removeIngredient();
                    break;
                case 4:
                    updateIngredient();
                    break;
                case 5:
                    showDish();
                    break;
                case 6:
                    addDish();
                    break;
                case 7:
                    removeDish();
                    break;
                case 8:
                    updateDish();
                    break;
                case 9:
                    showCustomer();
                    break;
                case 10:
                    addCustomer();
                    break;
                case 11:
                    removeCustomer();
                    break;
                case 12:
                    updateCustomer();
                    break;
                case 13:
                    showOrder();
                    break;
                case 14:
                    std::cout << "Exiting Admin Menu.\n";
                    break;
                default:
                    std::cout << "Invalid option, please try again.\n";
            }
        } while (option != 14);
    }

    // 厨师功能
    void chefTask(User user) {
        if (user.role == Role::CHEF) {
            int option;
            do {
                std::cout << "\nChef Menu:\n";
                std::cout << "1. Show Ingredient\n";
                std::cout << "2. Add Ingredient\n";
                std::cout << "3. Remove Ingredient\n";
                std::cout << "4. Update Ingredient\n";
                std::cout << "5. show Dish\n";
                std::cout << "6. Add Dish\n";
                std::cout << "7. Remove Dish\n";
                std::cout << "8. Update Dish\n";
                std::cout << "9. Exit\n";
                std::cout << "Enter your choice: ";
                std::cin >> option;
                switch (option) {
                    case 1:
                        showIngredient();
                        break;
                    case 2:
                        addIngredient();
                        break;
                    case 3:
                        removeIngredient();
                        break;
                    case 4:
                        updateIngredient();
                        break;
                    case 5:
                        showDish();
                    case 6:
                        addDish();
                        break;
                    case 7:
                        removeDish();
                        break;
                    case 8:
                        updateDish();
                        break;
                    case 9:
                        std::cout << "Exiting Chef Menu.\n";
                        break;
                    default:
                        std::cout << "Invalid option, please try again.\n";
                        break;

                }

            } while (option != 9);
            // 浏览原材料
            // 编辑菜单
            // ...
        }
    }


    // 客户功能
    void customerTask(User user) {
        if (user.role == Role::CUSTOMER) {
            int option;
            do {
                std::cout << "\nCustomer Menu:\n";
                std::cout << "1. Show Menu\n";
                std::cout << "2. Order Dish\n";
                std::cout << "3. Cancel Order\n";
                std::cout << "4. Exit\n";
                std::cout << "Enter your choice: ";
                std::cin >> option;
                switch (option) {
                    case 1:
                        showDish();
                        break;
                    case 2:
                        orderDish(user);
                        break;
                    case 3:
                        cancelOrder(user);
                        break;
                    case 4:
                        std::cout << "Exiting Customer Menu.\n";
                        break;
                    default:
                        std::cout << "Invalid option, please try again.\n";
                        break;

                }
            } while (option != 4);
            // 浏览菜单
            // 点菜
            // 退菜
            // ...
        }
    }
};

int main() {
    RestaurantManagementSystem rms;
    std::string username, password;

    // 用户登录
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (rms.login(username, password)) {
        // 登录成功，根据用户角色执行任务
        Role role;
        if (username == "admin") role = Role::ADMIN;
        else if (username == "chef") role = Role::CHEF;
        else if (username == "customer1") role = Role::CUSTOMER;

        User user(username, role);
        if (role == Role::ADMIN) rms.adminTask();
        else if (role == Role::CHEF) rms.chefTask(user);
        else if (role == Role::CUSTOMER) rms.customerTask(user);
    } else {
        std::cout << "Login failed." << std::endl;
    }

    return 0;
}