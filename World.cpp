#include "World.h"

World::World() {
	int screenX, screenY;
	int spriteX, spriteY;
	getScreenSize(screenX, screenY);
	player = new Player(screenX / 2, screenY);

	TurretSprite = createSprite("./data/Turret.png");
	getSpriteSize(TurretSprite, spriteX, spriteY);
	setSpriteSize(TurretSprite, (int)((double)spriteX * Scalings::GetDefaultScale()), (int)((double)spriteY * Scalings::GetDefaultScale()));
	getSpriteSize(TurretSprite, spriteX, spriteY);
	turret = new Turret(TurretSprite, (screenX - spriteX) / 2, 0);
	
	PlatformSprite = createSprite("./data/Platform.png");
	getSpriteSize(PlatformSprite, spriteX, spriteY);
	setSpriteSize(PlatformSprite, (int)((double)spriteX * Scalings::GetDefaultScale()), (int)((double)spriteY * Scalings::GetDefaultScale()));

	EnemySprite = createSprite("./data/Enemy.png");
	setSpriteSize(EnemySprite, (int)(55.0 * Scalings::GetDefaultScale()), (int)(35.0 * Scalings::GetDefaultScale()));

	ProjectileSprite = createSprite("./data/Projectile.png");
	getSpriteSize(ProjectileSprite, spriteX, spriteY);
	setSpriteSize(ProjectileSprite, (int)((double)spriteX * Scalings::GetDefaultScale()), (int)((double)spriteY * Scalings::GetDefaultScale()));

	TurretProjectileSprite = createSprite("./data/TurretProjectile.png");
	getSpriteSize(TurretProjectileSprite, spriteX, spriteY);
	setSpriteSize(TurretProjectileSprite, (int)((double)spriteX * Scalings::GetDefaultScale()), (int)((double)spriteY * Scalings::GetDefaultScale()));

	CoinSprite = createSprite("./data/Coin.png");
	getSpriteSize(CoinSprite, spriteX, spriteY);
	setSpriteSize(CoinSprite, (int)((double)spriteX * Scalings::GetDefaultScale()), (int)((double)spriteY * Scalings::GetDefaultScale()));

	for (int i = 0; i < 10; i++) {
		Numbers[i] = createSprite(("./data/" + std::to_string(i) + ".png").c_str());
		getSpriteSize(Numbers[i], spriteX, spriteY);
		setSpriteSize(Numbers[i], (int)((double)spriteX * Scalings::GetScoreDefaultScale()), (int)((double)spriteY * Scalings::GetScoreDefaultScale()));
	}
	
	BackgroundSprite = createSprite("./data/Background.png");
	setSpriteSize(BackgroundSprite, screenX, screenY);

	TopSprite = createSprite("./data/TopScreen.png");
	setSpriteSize(TopSprite, screenX, screenY / 10);

	highestPlatform = screenY;
}

void World::ShowScores() {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	int startX = screenX / 10;
	int startY = screenY / 60;
	std::string ScoreStr = std::to_string(Score);
	std::string PlatScoreStr = std::to_string(PlatformScore);
	std::string CoinBalStr = std::to_string(CoinBalance);
	int lenSS = 0;
	int lenPSS = 0;
	int lenCBS = 0;
	for (int i = 0; i < ScoreStr.size(); i++) {
		int sizeX, sizeY;
		getSpriteSize(Numbers[ScoreStr[i] - '0'], sizeX, sizeY);
		lenSS += sizeX;
	}
	for (int i = 0; i < PlatScoreStr.size(); i++) {
		int sizeX, sizeY;
		getSpriteSize(Numbers[PlatScoreStr[i] - '0'], sizeX, sizeY);
		lenPSS += sizeX;
	}
	for (int i = 0; i < CoinBalStr.size(); i++) {
		int sizeX, sizeY;
		getSpriteSize(Numbers[CoinBalStr[i] - '0'], sizeX, sizeY);
		lenCBS += sizeX;
	}
	int GapSize = (8 * screenX / 10) - lenSS - lenPSS - lenCBS;
	GapSize /= 2;
	for (int i = 0; i < ScoreStr.size(); i++) {
		int sizeX, sizeY;
		getSpriteSize(Numbers[ScoreStr[i] - '0'], sizeX, sizeY);
		drawSprite(Numbers[ScoreStr[i] - '0'], startX, startY);
		startX += sizeX;
	}
	startX += GapSize;
	for (int i = 0; i < PlatScoreStr.size(); i++) {
		int sizeX, sizeY;
		getSpriteSize(Numbers[PlatScoreStr[i] - '0'], sizeX, sizeY);
		drawSprite(Numbers[PlatScoreStr[i] - '0'], startX, startY);
		startX += sizeX;
	}
	startX += GapSize;
	for (int i = 0; i < CoinBalStr.size(); i++) {
		int sizeX, sizeY;
		getSpriteSize(Numbers[CoinBalStr[i] - '0'], sizeX, sizeY);
		drawSprite(Numbers[CoinBalStr[i] - '0'], startX, startY);
		startX += sizeX;
	}
}

void World::DrawWorld() {
	//std::cout << Enemies.size() << std::endl;
	drawSprite(BackgroundSprite, 0, 0);
	for (int i = 0; i < Coins.size(); i++) {
		if (!Coins[i]->IsCollected()) {
			Coins[i]->ShowCoin();
		}
	}
	for (int i = 0; i < PlatformsMoving.size(); i++) {
		PlatformsMoving[i]->MovePlatform();
	}
	for (int i = 0; i < PlatformsStatic.size(); i++) {
		PlatformsStatic[i]->ShowPlatform();
	}
	for (int i = 0; i < Enemies.size(); i++) {
		if (Enemies[i]->IsAlive()) {
			Enemies[i]->ShowEnemy();
		}
	}
	for (int i = 0; i < PlayerProjectiles.size(); i++) {
		if (!PlayerProjectiles[i]->ShouldBeDespawned()) {
			PlayerProjectiles[i]->MoveProjectile();
		}
	}
	for (int i = 0; i < TurretProjectiles.size(); i++) {
		if (!TurretProjectiles[i]->ShouldBeDespawned()) {
			TurretProjectiles[i]->MoveProjectile();
		}
	}
	player->MoveOrStand();
	turret->ShowTurret();
	drawSprite(TopSprite, 0, 0);
	ShowScores();
}

bool World::CheckAllCollisionsTo(Rectangle* rect) {
	for (int i = 0; i < PlatformsMoving.size(); i++) {
		Rectangle* Rect = PlatformsMoving[i]->GetMovingRectangle();
		if (rect->ColideRectangles(Rect) || Rect->ColideRectangles(rect)) {
			return true;
		}
	}
	for (int i = 0; i < PlatformsStatic.size(); i++) {
		Rectangle* Rect = PlatformsStatic[i]->GetFullRectangle();
		if (rect->ColideRectangles(Rect) || Rect->ColideRectangles(rect)) {
			return true;
		}
	}
	for (int i = 0; i < Enemies.size(); i++) {
		Rectangle* Rect = Enemies[i]->GetEnemyRectangle();
		if (rect->ColideRectangles(Rect) || Rect->ColideRectangles(rect)) {
			return true;
		}
	}
	for (int i = 0; i < Coins.size(); i++) {
		Rectangle* Rect = Coins[i]->GetCoinRectangle();
		if (rect->ColideRectangles(Rect) || Rect->ColideRectangles(rect)) {
			return true;
		}
	}
	return false;
}

void World::MoveAll() {
	int ToMove = CameraDistance > 1 ? 1 : CameraDistance;
	CameraDistance -= ToMove;
	player->MoveCamera(ToMove);
	for (int i = 0; i < PlatformsMoving.size(); i++) {
		PlatformsMoving[i]->MoveCamera(ToMove);
	}
	for (int i = 0; i < PlatformsStatic.size(); i++) {
		PlatformsStatic[i]->MoveCamera(ToMove);
	}
	for (int i = 0; i < PlayerProjectiles.size(); i++) {
		PlayerProjectiles[i]->MoveCamera(ToMove);
	}
	for (int i = 0; i < TurretProjectiles.size(); i++) {
		TurretProjectiles[i]->MoveCamera(ToMove);
	}
	for (int i = 0; i < Enemies.size(); i++) {
		Enemies[i]->MoveCamera(ToMove);
	}
	for (int i = 0; i < Coins.size(); i++) {
		Coins[i]->MoveCamera(ToMove);
	}
	highestPlatform += ToMove;
	Score += ToMove;
}

void World::CheckCollisions() {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	for (int i = 0; i < PlatformsMoving.size(); i++) {
		if (PlatformsMoving[i]->HasPlayerJumpedOn(player)) {
			player->Bounce();
			if (!HasPlayerBounced) {
				player->ChangeImmunity();
				HasPlayerBounced = true;
			}
			double platformX, platformY;
			PlatformsMoving[i]->GetCoordinates(platformX, platformY);
			CameraDistance = 9 * screenY / 10 - (int)platformY;
			PlatformScore = PlatformsMoving[i]->GetID();
		}
	}
	for (int i = 0; i < PlatformsStatic.size(); i++) {
		if (PlatformsStatic[i]->HasPlayerJumpedOn(player)) {
			player->Bounce();
			if (!HasPlayerBounced) {
				player->ChangeImmunity();
				HasPlayerBounced = true;
			}
			double platformX, platformY;
			PlatformsStatic[i]->GetCoordinates(platformX, platformY);
			CameraDistance = 9 * screenY / 10 - (int)platformY;
			PlatformScore = PlatformsStatic[i]->GetID();
		}
	}
	for (int i = 0; i < Enemies.size(); i++) {
		if (Enemies[i]->IsAlive()) {
			Enemies[i]->CheckCollision(player);
			for (int j = 0; j < PlayerProjectiles.size(); j++) {
				if (Enemies[i]->CheckCollision(PlayerProjectiles[j])) {
					PlayerProjectiles[j]->Despawn();
				}
			}
		}
	}
	for (int i = 0; i < TurretProjectiles.size(); i++) {
		player->CheckCollision(TurretProjectiles[i]);
	}
	for (int i = 0; i < Coins.size(); i++) {
		if (!Coins[i]->IsCollected()) {
			if (Coins[i]->CheckIfPlayerCollects(player)) {
				CoinBalance++;
			}
		}
	}
	if (CameraDistance < 0) {
		CameraDistance = 0;
	}
}

void World::ClearQueues() {
	for (int i = 0; i < PlatformsStatic.size(); i++) {
		Platform* p = PlatformsStatic.front();
		if (p->IsOutOfBounds()) {
			PlatformsStatic.pop_front();
			delete p;
		}
		else {
			PlatformsStatic.pop_front();
			PlatformsStatic.push_back(p);
		}
	}
	for (int i = 0; i < PlatformsMoving.size(); i++) {
		Platform* p = PlatformsMoving.front();
		if (p->IsOutOfBounds()) {
			PlatformsMoving.pop_front();
			delete p;
		}
		else {
			PlatformsMoving.pop_front();
			PlatformsMoving.push_back(p);
		}
	}
	for (int i = 0; i < PlayerProjectiles.size(); i++) {
		Projectile* p = PlayerProjectiles.front();
		if (p->IsOutOfBounds() || p->ShouldBeDespawned()) {
			PlayerProjectiles.pop_front();
			delete p;
		}
		else {
			PlayerProjectiles.pop_front();
			PlayerProjectiles.push_back(p);
		}
	}
	for (int i = 0; i < TurretProjectiles.size(); i++) {
		Projectile* p = TurretProjectiles.front();
		if (p->IsOutOfBounds() || p->ShouldBeDespawned()) {
			TurretProjectiles.pop_front();
			delete p;
		}
		else {
			TurretProjectiles.pop_front();
			TurretProjectiles.push_back(p);
		}
	}
	for (int i = 0; i < Coins.size(); i++) {
		Coin* c = Coins.front();
		if (c->IsOutOfBounds() || c->IsCollected()) {
			Coins.pop_front();
			delete c;
		}
		else {
			Coins.pop_front();
			Coins.push_back(c);
		}
	}
	for (int i = 0; i < Enemies.size(); i++) {
		Enemy* e = Enemies.front();
		if (e->IsOutOfBounds()) {
			Enemies.pop_front();
			delete e;
		}
		else {
			Enemies.pop_front();
			Enemies.push_back(e);
		}
	}
}

int World::SpawnPlatformAndEnemy() {
	int screenX, screenY;
	int maxX, minY;
	int platformX, platformY;

	getScreenSize(maxX, minY);
	getScreenSize(screenX, screenY);
	getSpriteSize(PlatformSprite, platformX, platformY);

	minY -= minY / 10;
	for (int i = 0; i < PlatformsMoving.size(); i++) {
		double platformX, platformY;
		PlatformsMoving[i]->GetCoordinates(platformX, platformY);
		if (platformY < minY) {
			minY = (int) platformY;
		}
	}
	for (int i = 0; i < PlatformsStatic.size(); i++) {
		double platformX, platformY;
		PlatformsStatic[i]->GetCoordinates(platformX, platformY);
		if (platformY < minY) {
			minY = (int) platformY;
		}
	}
	std::random_device rd;
	std::mt19937 mt(rd());
	auto randomX = std::uniform_int_distribution<int>(0, maxX - platformX);
	auto randomY = std::uniform_int_distribution<int>(minY - (screenY / 5), minY);
	auto randomType = std::uniform_int_distribution<int>(0, 100);
	auto randomSpawn = std::uniform_int_distribution<int>(0, 100);
	if (randomType(mt) > 90) {

		bool collide = true;
		while (collide) {
			int randX = randomX(mt);
			int randY = randomY(mt);
			Platform* p = new Platform(PlatformSprite, randX, randY, PlatformsSpawned + 1);
			collide = CheckAllCollisionsTo(p->GetMovingRectangle());
			if (!collide) {
				double platformX, platformY;
				p->GetCoordinates(platformX, platformY);
				PlatformsMoving.push_back(p);
				if (randomSpawn(mt) > 90) {
					int enemyX, enemyY;
					getSpriteSize(EnemySprite, enemyX, enemyY);
					Enemy* e = new Enemy(EnemySprite, p);
					Enemies.push_back(new Enemy(EnemySprite, p, true));
					return (int)(platformY - enemyY);
				}
				return (int)platformY;
			}
			else {
				delete p;
			}
		}
	}
	else {
		int randX = randomX(mt);
		int randY = randomY(mt);
		bool collide = true;
		while (collide) {
			int randX = randomX(mt);
			int randY = randomY(mt);
			Platform* p = new Platform(PlatformSprite, randX, randY, PlatformsSpawned + 1);
			collide = CheckAllCollisionsTo(p->GetFullRectangle());
			if (!collide) {
				double platformX, platformY;
				p->GetCoordinates(platformX, platformY);
				PlatformsStatic.push_back(p);
				if (randomSpawn(mt) > 90) {
					int enemyX, enemyY;
					getSpriteSize(EnemySprite, enemyX, enemyY);
					Enemy* e = new Enemy(EnemySprite, p);
					Enemies.push_back(new Enemy(EnemySprite, p));
					return (int)(platformY - enemyY);
				}
				return (int)platformY;
			}
			else {
				delete p;
			}
		}
	}
	abort();
}

void World::SpawnCoin() {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	std::random_device rd;
	std::mt19937 mt(rd());
	auto randomX = std::uniform_int_distribution<int>(0, screenX - 32);
	auto randomY = std::uniform_int_distribution<int>(0, highestPlatform);
	auto randomType = std::uniform_int_distribution<int>(0, 100);
	if (randomType(mt) > 90) {
		Coins.push_back(new Coin(CoinSprite, randomX(mt), randomY(mt)));
	}
}

void World::SpawnAll() {
	int screenX, screenY;
	getScreenSize(screenX, screenY);
	while (highestPlatform > 0) {
		SpawnCoin();
		highestPlatform = SpawnPlatformAndEnemy();
		PlatformsSpawned++;
	}
}

Player* World::GetPlayer() {
	return player;
}

bool World::ToRestart() {
	return !player->IsAlive() || player->IsOutOfBounds();
}

void World::SpawnProjectile(int mouseX, int mouseY, bool type) {
	if (type) {
		Projectile* p = turret->SpawnProjectile(TurretProjectileSprite, player);
		TurretProjectiles.push_back(p);
	}
	else {
		Projectile* p = player->SpawnProjectile(ProjectileSprite, mouseX, mouseY);
		PlayerProjectiles.push_back(p);
	}
}

bool World::CanPlayerBeImmune() {
	return CoinBalance >= 20 && player->CanBeImmune();
}

void World::StartPlayerImmunity() {
	player->ChangeImmunity();
	CoinBalance -= 20;
}

void World::StopPlayerImmunity() {
	player->ChangeImmunity();
}

World::~World() {
	delete player;
	delete turret;

	for (int i = 0; i < PlatformsStatic.size(); i++) {
		Platform* p = PlatformsStatic.front();
		PlatformsStatic.pop_front();
		delete p;
	}

	for (int i = 0; i < PlatformsMoving.size(); i++) {
		Platform* p = PlatformsMoving.front();
		PlatformsMoving.pop_front();
		delete p;
	}

	for (int i = 0; i < PlayerProjectiles.size(); i++) {
		Projectile* p = PlayerProjectiles.front();
		PlayerProjectiles.pop_front();
		delete p;
	}

	for (int i = 0; i < TurretProjectiles.size(); i++) {
		Projectile* p = TurretProjectiles.front();
		TurretProjectiles.pop_front();
		delete p;
	}

	for (int i = 0; i < Enemies.size(); i++) {
		Enemy* e = Enemies.front();
		Enemies.pop_front();
		delete e;
	}

	for (int i = 0; i < Coins.size(); i++) {
		Coin* c = Coins.front();
		Coins.pop_front();
		delete c;
	}

	destroySprite(PlatformSprite);
	destroySprite(ProjectileSprite);
	destroySprite(TurretProjectileSprite);
	destroySprite(BackgroundSprite);
	destroySprite(CoinSprite);
	destroySprite(TopSprite);
	destroySprite(EnemySprite);
	destroySprite(TurretSprite);
	for (int i = 0; i < 10; i++) {
		destroySprite(Numbers[i]);
	}
}