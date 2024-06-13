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

    const vector<Entity*>& getEntities() const {
        return entities;
    }
};

class Inventory {
private:
    vector<Entity*> items;

public:
    void addItem(Entity* item) {
        items.push_back(item);
    }

    void printInventory() const {
        cout << "Inventory: " << endl;
        for (const Entity* item : items) {
            item->print();
        }
    }

    const vector<Entity*>& getItems() const {
        return items;
    }
};

class Player {
private:
    string name;
    Inventory inventory;

public:
    Player(const string& name) : name(name) {}

    void addItemToInventory(Entity* item) {
        inventory.addItem(item);
    }

    void print() const {
        cout << "Player: " << name << endl;
        inventory.printInventory();
    }

    Inventory& getInventory() { 
        return inventory;
    }

    string getName() const {
        return name;
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

    Entity* entity1 = entityManager.createEntity("Marble Statue", 5);
	Entity* entityRock1 = entityManager.createEntity("Diamond", 10);
	Entity* entityRock2 = entityManager.createEntity("Dumbell", 8);

    Entity* entity2 = entityManager.createEntity("Soda Can", 6);
	Entity* entityMetal1 = entityManager.createEntity("Car", 9);
	Entity* entityMetal2 = entityManager.createEntity("Pocket Knife", 7);

    Entity* entity3 = entityManager.createEntity("Bic Lighter", 4);
	Entity* entityFire1 = entityManager.createEntity("Grill", 8);
	Entity* entityFire2 = entityManager.createEntity("Smooore", 6);

	Entity* entity4 = entityManager.createEntity("Puppy", 7);
	Entity* entityOrganic1 = entityManager.createEntity("Tadpole", 10);
	Entity* entityOrganic2 = entityManager.createEntity("Pond scum", 6);

	Entity* entity5 = entityManager.createEntity("CPU", 8);
	Entity* entityElectric1 = entityManager.createEntity("Taser", 10);
	Entity* entityElectric2 = entityManager.createEntity("Microwave", 7);


	Entity* entity6 = entityManager.createEntity("Lawn Chair", 9);
	Entity* entityPlastic1 = entityManager.createEntity("Coathanger", 10);
	Entity* entityPlastic2 = entityManager.createEntity("Plastic Bag", 7);

	Entity* entity7 = entityManager.createEntity("Stock Trade", 5); 
	Entity* entityConcept1 = entityManager.createEntity("Internet", 6);
	Entity* entityConcept2 = entityManager.createEntity("Patent", 8);

	Entity* entity8 = entityManager.createEntity("Lightbulb", 6);
	Entity* entityLight1 = entityManager.createEntity("Laser", 10);
	Entity* entityLight2 = entityManager.createEntity("Flashlight", 7);

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

	cout << "Please input yor name: " << endl;
	string playerName;
	cin >> playerName;
	Player player(playerName);

	cout << "Welcome to the ECS Battle Simulator!" << endl;
	cout << "Choose 5 items to store, youll fight with these items against 3 oponents:" << endl;

	//player inputs name of item, it gets asigned a class and health and stored in the player inventory.

	cout << "youll fight against 3 oponents, beat them and get their items for your next battle!" << endl << "Good Luck!"<<endl;

	//first battle
	//second battle
	//third battle

	cout << "Congratulations! You have won the game!" << endl;

    return 0;
}
