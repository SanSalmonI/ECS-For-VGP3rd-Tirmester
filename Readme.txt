Readme File, add whatever quirks the code has.


start:
    //Player chooses variable items to store
    int playerChoice;
    cout << "How many items would you like to store? (Choose up to 5): ";
    cin >> playerChoice;

    if (playerChoice > 5 || playerChoice < 1)
    {
		cout << "Invalid choice, please choose again." << endl;
		goto start;
	}
    system("CLS");

    cout << "Choose " << playerChoice << " items to store, you'll fight with these items against 3 opponents:" << endl;

    cout << "1. Marble Statue" << endl;
    cout << "2. Soda Can" << endl;
    cout << "3. Bic Lighter" << endl;
    cout << "4. Puppy" << endl;
    cout << "5. CPU" << endl;
    cout << "6. Lawn Chair" << endl;
    cout << "7. Stock Trade" << endl;
    cout << "8. Lightbulb" << endl;

    for (int i = 0; i < playerChoice; i++)
    {
        int itemChoice;
		cout << "Choose item " << i + 1 << ": ";
		cin >> itemChoice;

        switch (itemChoice)
        {
		case 1:
			player.addItemToInventory(entity1);
            entity1->addComponent(components[(rand() % 8) + 1]);
			break;
		case 2:
			player.addItemToInventory(entity2);
			entity2->addComponent(components[(rand() % 8) + 1]);
			break;
		case 3:
			player.addItemToInventory(entity3);
            entity3->addComponent(components[(rand() % 8) + 1]);
			break;
		case 4:
			player.addItemToInventory(entity4);
			entity4->addComponent(components[(rand() % 8) + 1]);
			break;
		case 5:
			player.addItemToInventory(entity5);
            entity5->addComponent(components[(rand() % 8) + 1]);
			break;
		case 6:
			player.addItemToInventory(entity6);
            entity6->addComponent(components[(rand() % 8) + 1]);
			break;
		case 7:
			player.addItemToInventory(entity7);
            entity7->addComponent(components[(rand() % 8) + 1]);
			break;
		case 8:
			player.addItemToInventory(entity8);
			entity8->addComponent(components[(rand() % 8) + 1]);
			break;
		default:
			cout << "Invalid choice, please choose again." << endl;
			i--;
			break;
		}

    }
    system("CLS");
