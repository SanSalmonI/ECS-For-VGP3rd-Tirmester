#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Component {
private:
    string name;

public:
    Component(const string& name) : name(name) {}

    string getName() const {
        return name;
    }
};

class Entity {
private:
    vector<Component*> components;
    string name;
    int hp;

public:
    Entity(const string& name, int hp) : name(name), hp(hp) {}

    void addComponent(Component* c) {
        components.push_back(c);
    }

    void print() const {
        cout << "Entity: " << name << endl;
        cout << "HP: " << hp << endl;
        cout << "Components: ";
        for (const Component* c : components) {
            cout << c->getName() << " ";
        }
        cout << endl << endl;
    }

    int getHP() const {
        return hp;
    }

    void reduceHP(int amount) {
        hp -= amount;
    }

    string getName() const {
        return name;
    }

    const vector<Component*>& getComponents() const {
        return components;
    }
};

class System {
public:
    virtual void update(Entity* e1, Entity* e2) = 0;
};

class BattleSystem : public System {
public:
    void update(Entity* e1, Entity* e2) override {
        cout << "Battle between " << e1->getName() << " and " << e2->getName() << endl;

        // Simple battle logic based on HP, this needs to also compare types to give advantage
        while (e1->getHP() > 0 && e2->getHP() > 0) {
            int damageToE2 = calculateDamage(e1, e2);
            int damageToE1 = calculateDamage(e2, e1);

            e1->reduceHP(damageToE1);
            e2->reduceHP(damageToE2);

            cout << e1->getName() << " deals " << damageToE2 << " damage to " << e2->getName() << endl;
            cout << e2->getName() << " deals " << damageToE1 << " damage to " << e1->getName() << endl;
        }

        if (e1->getHP() <= 0 && e2->getHP() <= 0) {
            cout << "Both entities are destroyed in the battle!" << endl;
        }
        else if (e1->getHP() <= 0) {
            cout << e1->getName() << " is destroyed!" << endl;
            cout << e2->getName() << " wins the battle!" << endl;
        }
        else {
            cout << e2->getName() << " is destroyed!" << endl;
            cout << e1->getName() << " wins the battle!" << endl;
        }
    }

private:
    int calculateDamage(Entity* attacker, Entity* defender) {
        int baseDamage = rand() % 10 + 1; // Random damage between 1 and 10
        double multiplier = 1.0;

        for (const Component* aComp : attacker->getComponents()) {
            for (const Component* dComp : defender->getComponents()) {
                if ((aComp->getName() == "Fire" && dComp->getName() == "Grass") ||
                    (aComp->getName() == "Grass" && dComp->getName() == "Water") ||
                    (aComp->getName() == "Water" && dComp->getName() == "Fire")) {
                    multiplier = 1.5;
                }
                else if ((aComp->getName() == "Grass" && dComp->getName() == "Fire") ||
                    (aComp->getName() == "Water" && dComp->getName() == "Grass") ||
                    (aComp->getName() == "Fire" && dComp->getName() == "Water")) {
                    multiplier = 0.5;
                }
            }
        }

        return static_cast<int>(baseDamage * multiplier);
    }
};

class EntityManager {
private:
    vector<Entity*> entities;

public:
    ~EntityManager() {
        for (Entity* e : entities) {
            delete e;
        }
    }

    Entity* createEntity(const string& name, int hp) {
        Entity* entity = new Entity(name, hp);
        entities.push_back(entity);
        return entity;
    }

    const vector<Entity*>& getEntities() const {
        return entities;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator

    // Create some components
    Component fire("Fire");
    Component water("Water");
    Component grass("Grass");

    // Create an entity manager
    EntityManager entityManager;

    // Create some entities
    Entity* sword = entityManager.createEntity("Sword", 50);
    Entity* shield = entityManager.createEntity("Shield", 60);
    Entity* bow = entityManager.createEntity("Bow", 45);

    // Add components to entities
    sword->addComponent(&fire);
    shield->addComponent(&water);
    bow->addComponent(&grass);

    // Print entity information
    sword->print();
    shield->print();
    bow->print();

    // Create a battle system
    BattleSystem battleSystem;

    // Perform battles
    battleSystem.update(sword, shield);
    battleSystem.update(shield, bow);
    battleSystem.update(bow, sword);

    return 0;
}
