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
    int ownerID;

public:
    Entity(const string& name, int hp, int ownerID) : name(name), hp(hp), ownerID(ownerID) {}

    void addComponent(Component* c) {
        components.push_back(c);
    }

    void print() const {
        cout << "Entity: " << name << endl;
        cout << "HP: " << hp << endl;
        cout << "Owner ID: " << ownerID << endl;
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

    int getOwnerID() const {
        return ownerID;
    }

    void setOwnerID(int newOwnerID) {
        ownerID = newOwnerID;
    }

    const vector<Component*>& getComponents() const {
        return components;
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

    Entity* createEntity(const string& name, int hp, int ownerID) {
        Entity* e = new Entity(name, hp, ownerID);
        entities.push_back(e);
        return e;
    }

    const vector<Entity*>& getEntities() const {
        return entities;
    }

    Entity* findEntityByName(const string& name) {
        for (Entity* entity : entities) {
            if (entity->getName() == name) {
                return entity;
            }
        }
        return nullptr;
    }
};

class Actor {
private:
    string name;
    vector<Entity*> inventory;
    int ownerID;

public:
    Actor(const string& name, int ownerID) : name(name), ownerID(ownerID) {}

    string getName() const {
        return name;
    }

    void addItemToInventory(Entity* item) {
        item->setOwnerID(ownerID);
        inventory.push_back(item);
    }

    void printInventory() const {
        cout << name << "'s inventory:" << endl;
        for (Entity* item : inventory) {
            cout << item->getName() << endl;
        }
    }

    int getOwnerID() const {
        return ownerID;
    }
};

class System {
public:
    //trash vv
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

    //function to add defeated enemy's items to player's inventory after battle
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

    Entity* entity1 = entityManager.createEntity("Marble Statue", 5, 0);
    Entity* entityRock1 = entityManager.createEntity("Diamond", 10, 0);
    Entity* entityRock2 = entityManager.createEntity("Dumbell", 8, 0);

    Entity* entity2 = entityManager.createEntity("Soda Can", 6, 0);
    Entity* entityMetal1 = entityManager.createEntity("Car", 9, 0);
    Entity* entityMetal2 = entityManager.createEntity("Pocket Knife", 7, 0);

    Entity* entity3 = entityManager.createEntity("Bic Lighter", 4, 0);
    Entity* entityFire1 = entityManager.createEntity("Grill", 8, 0);
    Entity* entityFire2 = entityManager.createEntity("Smooore", 6, 0);

    Entity* entity4 = entityManager.createEntity("Puppy", 7, 0);
    Entity* entityOrganic1 = entityManager.createEntity("Tadpole", 10, 0);
    Entity* entityOrganic2 = entityManager.createEntity("Pond scum", 6, 0);

    Entity* entity5 = entityManager.createEntity("CPU", 8, 0);
    Entity* entityElectric1 = entityManager.createEntity("Taser", 10, 0);
    Entity* entityElectric2 = entityManager.createEntity("Microwave", 7, 0);

    Entity* entity6 = entityManager.createEntity("Lawn Chair", 9, 0);
    Entity* entityPlastic1 = entityManager.createEntity("Coathanger", 10, 0);
    Entity* entityPlastic2 = entityManager.createEntity("Plastic Bag", 7, 0);

    Entity* entity7 = entityManager.createEntity("Stock Trade", 5, 0);
    Entity* entityConcept1 = entityManager.createEntity("Internet", 6, 0);
    Entity* entityConcept2 = entityManager.createEntity("Patent", 8, 0);

    Entity* entity8 = entityManager.createEntity("Lightbulb", 6, 0);
    Entity* entityLight1 = entityManager.createEntity("Laser", 10, 0);
    Entity* entityLight2 = entityManager.createEntity("Flashlight", 7, 0);

    entity1->addComponent(&rock);
    entityRock1->addComponent(&rock);
    entityRock2->addComponent(&rock);

    entity2->addComponent(&metal);
    entityMetal1->addComponent(&metal);
    entityMetal2->addComponent(&metal);

    entity3->addComponent(&fire);
    entityFire1->addComponent(&fire);
    entityFire2->addComponent(&fire);

    entity4->addComponent(&organic);
    entityOrganic1->addComponent(&organic);
    entityOrganic2->addComponent(&organic);

    entity5->addComponent(&electric);
    entityElectric1->addComponent(&electric);
    entityElectric2->addComponent(&electric);

    entity6->addComponent(&plastic);
    entityPlastic1->addComponent(&plastic);
    entityPlastic2->addComponent(&plastic);

    entity7->addComponent(&conceptual);
    entityConcept1->addComponent(&conceptual);
    entityConcept2->addComponent(&conceptual);

    entity8->addComponent(&light);
    entityLight1->addComponent(&light);
    entityLight2->addComponent(&light);

    System battleSystem;

    //create and assign items to enemies
    Actor enemy1("Kaleb", 1);
    Actor enemy2("Salmn", 2);
    Actor enemy3("Habibi", 3);//change this, or not idk
    


    //for loop to assign items to enemies


    cout << "Please input your name: ";
    string playerName;
    cin >> playerName;

    Actor player(playerName, 0);

    for (Entity* e : entityManager.getEntities()) {
        player.addItemToInventory(e);
    }
    
    player.printInventory();


    cout << "Welcome to the ECS Battle Simulator!" << endl;
    cout << "Choose 5 items to store, you'll fight with these items against 3 opponents:" << endl;

    //function where player creates 5 new items to store

    cout << "You will fight against 3 opponents, beat them and get their items for your next battle!" << endl << "Good Luck!" << endl;

    // Placeholder for battle logic
    // Implement battle sequences here

    cout << "Congratulations! You have won the game!" << endl;

    return 0;
}
