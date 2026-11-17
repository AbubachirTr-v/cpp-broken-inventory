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
    std::cout << "Failures: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
