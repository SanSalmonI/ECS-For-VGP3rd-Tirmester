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
    bool selection;

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

    void generateSelection() {
        selection = rand() % 2;
    }

    bool getSelection() {
        return selection;
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
    void update(Entity* e1, Entity* e2) {
        cout << "Battle between " << e1->getName() << " and " << e2->getName() << endl;

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
        int baseDamage = rand() % 10 + 1;
        double multiplier = 1.0;

        for (const Component* aComp : attacker->getComponents()) {
            for (const Component* dComp : defender->getComponents()) {
                if ((aComp->getName() == "Rock" && (dComp->getName() == "Electric" || dComp->getName() == "Plastic" || dComp->getName() == "Conceptual")) ||
                    (aComp->getName() == "Metal" && (dComp->getName() == "Rock" || dComp->getName() == "Organic" || dComp->getName() == "Light")) ||
                    (aComp->getName() == "Fire" && (dComp->getName() == "Metal" || dComp->getName() == "Electric" || dComp->getName() == "Plastic")) ||
                    (aComp->getName() == "Electric" && (dComp->getName() == "Fire" || dComp->getName() == "Organic" || dComp->getName() == "Light")) ||
                    (aComp->getName() == "Organic" && (dComp->getName() == "Rock" || dComp->getName() == "Fire" || dComp->getName() == "Conceptual")) ||
                    (aComp->getName() == "Plastic" && (dComp->getName() == "Metal" || dComp->getName() == "Organic" || dComp->getName() == "Light")) ||
                    (aComp->getName() == "Conceptual" && (dComp->getName() == "Fire" || dComp->getName() == "Electric" || dComp->getName() == "Plastic")) ||
                    (aComp->getName() == "Light" && (dComp->getName() == "Rock" || dComp->getName() == "Metal" || dComp->getName() == "Conceptual"))) {
                    multiplier = 1.5;
                }
                else if ((aComp->getName() == "Rock" && (dComp->getName() == "Metal" || dComp->getName() == "Organic" || dComp->getName() == "Light")) ||
                    (aComp->getName() == "Metal" && (dComp->getName() == "Fire" || dComp->getName() == "Electric" || dComp->getName() == "Plastic")) ||
                    (aComp->getName() == "Fire" && (dComp->getName() == "Rock" || dComp->getName() == "Organic" || dComp->getName() == "Conceptual")) ||
                    (aComp->getName() == "Electric" && (dComp->getName() == "Rock" || dComp->getName() == "Metal" || dComp->getName() == "Conceptual")) ||
                    (aComp->getName() == "Organic" && (dComp->getName() == "Metal" || dComp->getName() == "Electric" || dComp->getName() == "Plastic")) ||
                    (aComp->getName() == "Plastic" && (dComp->getName() == "Rock" || dComp->getName() == "Fire" || dComp->getName() == "Conceptual")) ||
                    (aComp->getName() == "Conceptual" && (dComp->getName() == "Rock" || dComp->getName() == "Organic" || dComp->getName() == "Light")) ||
                    (aComp->getName() == "Light" && (dComp->getName() == "Electric" || dComp->getName() == "Organic" || dComp->getName() == "Plastic"))) {
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

    Entity* assignEntity(Entity E1, Entity E2) {
        for (int i = 0; i < 10; i++)
        {
            if (E1.getSelection() == 0)
            {
                return &E1;
            }
            else
            {
                return &E2;
            }
        }

    }

    const vector<Entity*>& getEntities() const {
        return entities;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Component rock("Rock");
    Component metal("Metal");
    Component fire("Fire");
    Component electric("Electric");
    Component organic("Organic");
    Component plastic("Plastic");
    Component conceptual("Conceptual");
    Component light("Light");

    EntityManager entityManager;

    Entity* entity1 = entityManager.createEntity("Entity1", 50);
    Entity* entity2 = entityManager.createEntity("Entity2", 60);
    Entity* entity3 = entityManager.createEntity("Entity3", 45);

    entity1->addComponent(&rock);
    entity2->addComponent(&metal);
    entity3->addComponent(&fire);

    entity1->print();
    entity2->print();
    entity3->print();

    System battleSystem;

    battleSystem.update(entity1, entity2);
    battleSystem.update(entity2, entity3);
    battleSystem.update(entity3, entity1);

    return 0;
}
