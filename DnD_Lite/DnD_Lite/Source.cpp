#include <iostream>
#include <vector>
#include <string>

int random(int from, int to) {
	return rand() % (to - from + 1) + from;
}



class PlayerCharacter
{
private:
	std::string name;
	int health;
	int maxDamage;

public:
	PlayerCharacter(std::string name, int health, int maxDamage)
	{
		this->name = name;
		this->health = health;
		this->maxDamage = maxDamage;
	}

	void Status() {																//print status of character
		std::cout << name << " has " << health << " health " << std::endl;
		std::cout << std::endl;
	}

	void Attack(PlayerCharacter& target) {
		int damage = random(1, maxDamage);
		target.setHealth((target.getHealth()) - damage);
		std::cout << target.getName()<< " suffered " << damage << " damage" << std::endl;

		if (target.getHealth() <= 0) std::cout << target.getName() << " died" << std::endl;
		else target.Status();
	}

	void setHealth(int number) {
		health = number;
	}
	int getHealth() {
		return health;
	}

	std::string getName() {
		return name;
	}

	
};

std::vector<PlayerCharacter*> CreateEncounter(int numberOfEnemies, std::string enemyType) {

	std::vector<PlayerCharacter*> enemies;
	for (int i = 0; i < numberOfEnemies; i++) {
		enemies.push_back(new PlayerCharacter(enemyType + " " + std::to_string(random(1, 100)), 10, 4));
	}

	return enemies;
}

void PlayerTurn(PlayerCharacter fighter, std::vector<PlayerCharacter*>& enemies, std::string& target) {
	// ask for target
	std::cout << "Target name:" << std::endl;
	std::getline(std::cin, target);


	// resolve attack
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i]->getName() == target) fighter.Attack(*enemies[i]);
		if (enemies[i]->getHealth() <= 0) enemies.erase(enemies.begin() + i); //remove dead enemies from the list
	}

	std::cout << std::endl;
}

void EnemyTurn(PlayerCharacter fighter, std::vector<PlayerCharacter*>& enemies) {
	for (PlayerCharacter* enemy : enemies) {
		if (enemy->getHealth() > 0) enemy->Attack(fighter);
	}

}

int main() {

	//Init
	srand(time(0));

	std::vector<PlayerCharacter*> enemies = CreateEncounter(4, "Goblin");
	PlayerCharacter fighter("Fredrick", 30, 10);
	std::string target = "start";


	//main game loop
	while (!target.empty()) {


		// write out enemy names and hp
		for (PlayerCharacter* enemy : enemies) {
			std::cout << enemy->getName() << "<hp: " << enemy->getHealth() << ">" << std::endl;
		}

		PlayerTurn(fighter, enemies, target);
		EnemyTurn(fighter, enemies);

		if (fighter.getHealth() <= 0) return 0; // if player dead -> game over

	}

	return 0;
}