#include<stdio.h>
#include<string.h>

// Store details of Item
struct Item {

		int itemCode;
		char itemName[20];
		char description[200];
		float price;
		int quantity;

		// Constructor to initialize details of item

};

struct Item initialize (int code, char name[20], char des[200], float pr, int qn) {
	struct Item item;
	item.itemCode = code;
	strcpy(item.itemName, name);
	strcpy(item.description, des);
	item.price = pr;
	item.quantity = qn;

	return item;
};

int getItemCode(struct Item item) {
	return item.itemCode;
}

void getItemName(struct Item item, char name[20]) {
	strcpy(item.itemName, name);
}

void getDescription(struct Item item, char description[200]) {
	strcpy(item.description, description);
}

float getPrice(struct Item item) {
	return item.price;
}

int getQuantity(struct Item item) {
	return item.quantity;
}

		//Setters
void setItemCode(int code, struct Item item) {
	item.itemCode = code;
}

void setItemName(char name[20],  struct Item item) {
	strcpy(item.itemName, name);
}

void setDescription(char des[20], struct Item item) {
	strcpy(item.description, des);
}

void setPrice(float pr, struct Item item) {
	item.price = pr;
}

void setQuantity(int qn, struct Item item) {
	item.quantity = qn;
}

struct Inventory {

	// List of items
	struct Item itemList[200];
	int length;
};


	// Generate Receipt for product
	void generateReceipt(int quantity, int i, struct Inventory *inventory) {
		printf("%s" , "                                             RECEIPT\n");
		printf("%s" , "===========================================================================================================================\n");
		printf("%s" , "CODE         ITEM NAME           DESCRIPTION                                 PRICE           QUANTITY           TOTAL PRICE\n");
		printf("%d" , getItemCode(inventory->itemList[i]));
		printf("           ");
		printf("%s" , inventory->itemList[i].itemName);
		printf("           ");
		printf("%s" , inventory->itemList[i].description);
		printf("           ");
		printf("%.2f", getPrice(inventory->itemList[i]));
		printf("           ");
		printf("%d" ,getQuantity(inventory->itemList[i]));
		printf("           ");
		printf("%.2f" ,getPrice(inventory->itemList[i]) * getQuantity(inventory->itemList[i]));
		printf("%s" , "\n");
		printf("%s" , "===========================================================================================================================\n");
		printf("%s" , "\n");
		printf("%s" , "\n");
		printf("%s" , "\n");
		return;
	}

	// Update inventory with remaining quantity.
	void updateInventory(int quantity, int i, struct Inventory *inventory) {

		// If quantity after selling become 0, remove item from inventory.
		if (quantity == getQuantity(inventory->itemList[i])) {
			for (int in = i + 1; in < inventory->length; i++) {
				inventory->itemList[in - 1] = inventory->itemList[in];
				inventory->length--;
			}
		}

		// Else update quantity with remaining quantity.
		else {
			inventory->itemList[i].quantity = getQuantity(inventory->itemList[i]) - quantity;
			setQuantity(getQuantity(inventory->itemList[i]) - quantity, inventory->itemList[i]);
		}

		return;

	}

// Add new item in inventory
	void addNewItem(struct Item item, struct Inventory *inventory) {

		// Check if Item code already exists in Inventory,
		// If exists, then increase the quantity of the item,
		// Otherwise add new item in Inventory.

		int flag = 0;
		for (int i = 0; i < inventory->length; i++) {
			// Item Exists in inventory
			if (getItemCode(item) == getItemCode(item)) {
				flag = 1;
				setQuantity(getQuantity(inventory->itemList[i]) + getQuantity(item), inventory->itemList[i]);
			}
		}

		// Item doesn't exist in inventory
		if(flag == 0) {
			inventory->itemList[inventory->length] = item;
			inventory->length++;
		}

		printf("%s" , "Added item to inventory Successfully !!\n");
		return;
}

    // Customer purchase
	int buyFromInventory(int itemCode, int quantity, struct Inventory *inventory) {

		//Check if Item exists in inventory or not
		int index = -1;

		for (int i = 0; i < inventory->length; i++) {
			if (itemCode == getItemCode(inventory->itemList[i])) {
				index = i;
				break;
			}
		}

		// If item exists or not
		if (index == -1) {
			printf("%s" , "Item doesn't exists in inventory !!\n");
			printf("%s" , "Purchase not successful !! \n");
			return 0;
		}

		// If item exists, do we have sufficient quantity.
		else if (quantity > getQuantity(inventory->itemList[index])) {
			printf("%s" , "We don't have sufficient quantity of requested item.\n");
			printf("%s" , "Purchase not successful !!\n");
			return 0;
		}

		// Item exists and we have sufficient quantity.
		else {
			printf("%s" , "Your purchase is Successful :-)\n");
			// Generate Receipt.
			generateReceipt(quantity, index, inventory);

			// Update quantity of product.
			updateInventory(quantity, index, inventory);
		}

		return 1;
	}

//Display Inventory Items
	void displayInventory(struct Inventory inventory) {
		printf("%s" , "                                             INVENTORY\n");
		printf("%s" , "								             LIST OF ITEMS\n");
		printf("%s" , "=====================================================================================================\n");
		printf("%s" , "CODE         ITEM NAME           DESCRIPTION                                 PRICE           QUANTITY\n");
		for (int i = 0; i < inventory.length; i++) {
			printf("%d" , getItemCode(inventory.itemList[i]));
			printf("           ");
			printf("%s" , inventory.itemList[i].itemName);
			printf("           ");
			printf("%s" , inventory.itemList[i].description);
			printf("           ");
			printf("%.2f", getPrice(inventory.itemList[i]));
			printf("           ");
			printf("%d" ,getQuantity(inventory.itemList[i]));
			printf("\n");
		}

		printf("%s" , "=====================================================================================================\n");
		printf("%s" , "\n");
		printf("%s" , "\n");
		printf("%s" , "\n");
		return;
	}


void displayOptions() {
	printf("%s" , "                                             * INVENTORY + POS * SYSTEM * version: 1.1 *\n");
	printf("%s" , "===========================================================================================================================\n");
	printf("%s" , "                                             * MAIN * MENU *\n");
	printf("%s" , "===========================================================================================================================\n");
	printf("%s" , "             							1. New Sale\n");
	printf("%s" , "             							2. Add Item\n");
	printf("%s" , "             							3. Check Inventory\n");
	printf("%s" , "             							4. Exit\n");
	printf("%s" , "===========================================================================================================================\n");

	printf("%s" , "\n");
	printf("%s" , "\n");
	printf("%s" , "\n");

	return;
}

int checkValidityOfPrice(float price) {
	if (price < 0)
		return 0;

	return 1;
}

int checkValidityOfQuantity(int quantity) {
	if (quantity < 0)
		return 0;
	return 1;
}

int main() {
	struct Inventory inventory;

	inventory.length = 0;

	while(1) {
		displayOptions();

		char ch[2];
		printf("%s" , "Enter your choice\n");
		scanf("%s", ch);

		int itemCode;
		char itemName[20];
		char description[200];
		float price;
		int quantity;
		int choice;
		int flag = 0;
		char temp;

		switch (ch[0]) {

			case '1' :
				printf("%s" , "Enter 1 if you want to view inventory\n");
				printf("%s" , "Enter 2 if you want to make a purchase\n");
				scanf("%d", &choice);

				if (choice == 1) {
					displayInventory(inventory);
				}

				else {
					printf("%s" , "Enter item Code\n");
					scanf("%d", &itemCode);
					printf("%s" , "Enter quantity\n");
					scanf("%d", &quantity);
					buyFromInventory(itemCode, quantity, &inventory);
				}

				break;

			case '2' :
				printf("%s" , "Enter Item Code (Integer)\n");
				scanf("%d", &itemCode);
				printf("%s" ,  "Enter Item Name\n");
				scanf("%c",&temp);
				scanf("%[^\n]",itemName);
				printf("%s" , "Enter Description\n");
				scanf("%c",&temp);
				scanf("%[^\n]",description);
				printf("%s" , "Enter price\n");
				scanf("%f", &price);
				printf("%s" , "Enter quantity\n");
				scanf("%d", &quantity);

				if (checkValidityOfPrice(price) == 0 || checkValidityOfQuantity(quantity) == 0) {
					printf("%s" , "Details are not valid\n");
					printf("%s" , "Taking you to main details\n");
					printf("%s" , "\n");
					printf("%s" , "\n");
					break;
				} else {
					struct Item item = initialize(itemCode, itemName, description, price, quantity);
					addNewItem(item, &inventory);
					break;
				}

				break;

			case '3' :
				displayInventory(inventory);
				break;
			case '4' :
				flag = 1;
				printf("%s" , "Thank you for using the IPOS v1.1!\n");
				break;
			default :
				printf("%s" , "Error! Invalid selection.\n");
				break;
		}

		if(flag == 1)
			break;

	}
	return 0;
}
