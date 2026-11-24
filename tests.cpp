#include "inventory.hpp"
#include <iostream>
#include <limits>
int failures = 0;
void check(bool condition, const char* label) {
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}
int main() {
    Weapon sword("Sword", 1, 10);
    Armor shield("Shield", 1, 5);
    Potion potion("Health", 2, 20);
    Inventory inv;
    check(inv.size() == 0, "empty size");
    check(inv.add(&sword), "add weapon");
    check(inv.size() == 1, "one object");
    Item* base = &sword;
    check(base->use() == "Attack: Sword", "virtual dispatch weapon");
        check(!inv.add(nullptr), "add nullptr");
    check(!inv.add(&sword), "add duplicate address");
    check(inv.size() == 1, "size after duplicate rejected");

    Weapon sword2("Sword", 1, 5);
    check(inv.add(&sword2), "add different object with same name");
    check(inv.size() == 2, "size after same name");

    check(inv.find("Sword") == &sword, "find returns first matching");
    check(inv.find("Nonexistent") == nullptr, "find missing returns nullptr");

    check(inv.at(0) == &sword, "at index 0");
    check(inv.at(1) == &sword2, "at index 1");
    check(inv.at(99) == nullptr, "at out of range returns nullptr");

    check(inv.remove(0), "remove first");
    check(inv.size() == 1, "size after remove first");
    check(inv.at(0) == &sword2, "order preserved after remove first");

    check(!inv.remove(99), "remove invalid index");

    inv.clear();
    check(inv.size() == 0, "clear empties inventory");
    inv.clear();
    check(inv.size() == 0, "clear twice safe");
    std::cout << "Failures: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
