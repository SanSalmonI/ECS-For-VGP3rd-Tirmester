Final Project: ECS Battle Simulator

Engine: Entity-Component-System (ECS)
- Our project utilizes and implements out first try at using an Entity-Component-System (ECS) architecture, which is a design pattern commonly used in game development. The ECS pattern separates data 
  (components) from the behavior (systems) and organizes entities that can dynamically have various components attached to them. This approach provides flexibility, scalability, and improved 
  performance.
- This project was a group assignment that involved 3 of us; Salmon, Kaleb and Ibrahim, and took about 3 weeks to learn and implement.

How ECS Works:
  Entities: The core objects that can have multiple components attached to them.
  Components: Data containers that hold specific attributes or states of entities.
  Systems: Logic handlers that process entities with specific components.

Entity Class
- The Entity class represents a game object. We use this primarily for our 'Items'/ 'Cards' that a player may create or use in battle!
- Each entity has:
              A unique name.
              Health points (HP) to determine its durability in battles.
              An owner ID to identify which actor owns the entity.
              A list of components to define its characteristics.
              
- The Entity class provides methods to add components, print entity details, and manage HP.

Components
- We designed several components to represent various attributes of entities, these acted as our 'Elements':
  Rock
  Metal
  Fire
  Electric
  Organic
  Plastic
  Conceptual
  Light
- Each component has a name and can be attached to entities to define their characteristics.

Systems
- We developed systems to handle the game logic and interactions between entities:

  Battle System: Manages the battle logic between two entities, calculating damage and determining the winner.
  Transfer System: Handles the transfer of items from a defeated actor to the winner.
  Assignment System: Randomly assigns items to enemy actors at the beginning of the game.

- How our Components Work Together:
    Components are attached to entities to define their characteristics. The systems then use these components to process game logic. For example, during a battle, the components of both attacking 
    and defending entities are considered to calculate damage based on their interactions.

Sequencing
- The game follows this sequence:

  Initialize components and entities.
  Assign items to enemy actors.
  Player is able to create up to 5 items, that are then assigned random elements.
  Engage in an automated battle against enemies, item vs item.
  Transfer items from defeated enemies to the player. -> *Broken but still possible.*
  Beat up to 3 opponents, each scaling with difficulty (Through the amount of cards they start with).
  Player wins if they beat all opponents. 
  Declare the winner if the player survives till the end!

Top Three Challenges

i)    Github: this is a very versitile tool, but sometimes its complexity hidered the developmet more than it aided us, sometimes the push wouldnt include the changes, and navigating the patches in 
      the github desktop was convoluted at best.
ii)   The vectors and classes: including so many list types makes it hard to keep consistency, our most common error was unallocated memmory and keeping the lists to a managebe size. 
iii)  General bug fixing and error solving: Just the general inability to sometimes wrap our head around a few logic errors and whatnot.

The Game: ECS Battle Simulator

![RockPaperSpockTrailer_1](https://github.com/SanSalmonI/ECS-For-VGP3rd-Tirmester/assets/171985375/5eb0fe6c-5e58-4dee-88fb-ad9d57d6edfe)

How It Plays
The game is a turn-based battle simulator where the player selects items to store and battles against three enemy actors. Each battle involves selecting an entity to attack with and calculating the outcome based on the entities' components.

![RockPaperSpockTrailer_2](https://github.com/SanSalmonI/ECS-For-VGP3rd-Tirmester/assets/171985375/72e8ce6c-cd40-45bb-951d-08fbd3bc9f9e)

Benefits from ECS

The ECS architecture allows for:

Modularity: Easily adding or modifying components and systems without affecting the overall game structure, we took full advantage of this by making a came about creating classes, by making the player inventory is full of items that have their own components.
Scalability:The values for the game are scalable, the programer can choose to add more by only changing numbers like the limit on how many items the player starts with or the number of entities, the limit is human input as we didnt add a way for the computer to generate the names for items on its own. 

Reusability: the game relies heavily on fuctions within the classes, this is so the main doesnt have much logic exept the gameflow and the Actors can only do whay they are designed to do. 

Scaling the Game
The game can be scaled by:
- Adding More Components: Introducing new components to diversify entity attributes, these have a type, name, and HP.
- Expanding Systems: the game can easily be modified to add crafting, trading, or exploring.
- Increasing Entity Variety: Designing more entities with unique combinations of components to add complexity to the type hirarchy.


