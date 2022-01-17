#include "Character.h"
#include "Exception.h"
//------------------------------------------------//

Exception* blad_c[9];
//------------------------------------------------//
//------------METODY CHARACTER--------------------//
//------------------------------------------------//
/////////////////////PUBLIC/////////////////////////
void Character::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->sprite, state);
}

//Zwracanie Bounds poza klas¹
sf::FloatRect Character::getBounds()
{
	return sprite.getGlobalBounds();
}

//Zwracanie Position poza klas¹
sf::Vector2f Character::getPosition()
{
	return sprite.getPosition();
}

sf::Vector2f Character::getVelocity()
{
	return this->velocity;
}
//------------------------------------------------//
//------------METODY PAC_MAN----------------------//
//------------------------------------------------//
/////////////////////PRIVATE////////////////////////

//ZMIANA TEKSTURY PACMANA
void Pac_man::setTexture() {
	if (timer.getElapsedTime() >= sf::milliseconds(500)) {
		sprite.setTexture(texture);
		if (timer.getElapsedTime() >= sf::milliseconds(1000)) {
			timer.restart();
		}
	}
	else if (timer.getElapsedTime() < sf::milliseconds(500)) {
		sprite.setTexture(texture2);
	}
}

//USTAWIENIE PREDKOSCI - OBSLUGA KLAWIATURY
void Pac_man::setMove(char forbidden)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && forbidden != 'W') {
		this->velocity.x = 0;
		this->velocity.y = -this->Pac_manVelocity;
		this->rotation = 270;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && forbidden != 'S') {
		this->velocity.x = 0;
		this->velocity.y = this->Pac_manVelocity;
		this->rotation = 90;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && forbidden != 'A') {
		this->velocity.x = -this->Pac_manVelocity;
		this->velocity.y = 0;
		this->rotation = 180;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && forbidden != 'D') {
		this->velocity.x = this->Pac_manVelocity;
		this->velocity.y = 0;
		this->rotation = 0;
	}
	this->isCollision = false;
}

//COFNIECIE PACMANA PRZY ZDERZENIU
void Pac_man::moveBack(){
	sprite.move(-this->velocity);
}

//USTAWIENIE ROTACJI TEKSTURY
void Pac_man::rotate() {
	sprite.setRotation(this->rotation);
}

//metoda move() zmienia wartoœci wektora prêdkoœci - zmiana kierunku ruchu
void Pac_man::move() {
	if (this->isCollision == false)
	{
		this->lastVelocity = this->velocity;
		this->lastRotation = this->rotation;
		this->setMove('O');								//O jak OK
		sprite.move(this->velocity);
	}
	else if (this->isCollision == true)
	{
		//std::cout << velocity.x << " | " << velocity.y << std::endl;
		if (this->velocity.x == this->Pac_manVelocity) {
			if (this->lastVelocity != this->velocity)
			{
				this->velocity = this->lastVelocity;
				this->rotation = this->lastRotation;
			}
			else
			{
				this->velocity.x = 0;
				this->velocity.y = 0;
				this->setMove('D');

			}
		}
		else if (this->velocity.y == this->Pac_manVelocity) {
			if (this->lastVelocity != this->velocity)
			{
				this->velocity = this->lastVelocity;
				this->rotation = this->lastRotation;
			}
			else
			{
				this->velocity.x = 0;
				this->velocity.y = 0;
				this->setMove('S');
			}
		}
		else if (this->velocity.x == -this->Pac_manVelocity) {
			if (this->lastVelocity != this->velocity)
			{
				this->velocity = this->lastVelocity;
				this->rotation = this->lastRotation;
			}
			else
			{
				this->velocity.x = 0;
				this->velocity.y = 0;
				this->setMove('A');
			}
		}
		else if (this->velocity.y == -this->Pac_manVelocity) {
			if (this->lastVelocity != this->velocity)
			{
				this->velocity = this->lastVelocity;
				this->rotation = this->lastRotation;
			}
			else
			{
				this->velocity.x = 0;
				this->velocity.y = 0;
				this->setMove('W');
			}
		}
		this->isCollision = false;
		sprite.move(this->velocity);

	}
}

//
void Pac_man::setPosition()
{
	this->position = sprite.getPosition();
}

/////////////////////PUBLIC/////////////////////////
//konstruktor
Pac_man::Pac_man() {
	if(!texture.loadFromFile("assets/png/close_pac.png")) { blad_c[6] = new Exception(3, "Nie udalo sie wczytac tekstury z pliku: assets/png/close_pac.png"); throw* blad_c[6]; }
	texture.setSmooth(true);
	if (!texture2.loadFromFile("assets/png/open_pac.png")) { blad_c[7] = new Exception(3, "Nie udalo sie wczytac tekstury z pliku: assets/png/open_pac.png"); throw* blad_c[7]; }
	texture2.setSmooth(true);
	if(!brak.loadFromFile("assets/png/black.png")) { blad_c[8] = new Exception(3, "Nie udalo sie wczytac tekstury z pliku: assets/png/brak.png"); throw* blad_c[8]; }
	sprite.setTexture(texture);
	sprite.scale(sf::Vector2f(0.047f, 0.047f));
	sf::Vector2f multiplier{ (1.f / (2 * sprite.getScale().x)), (1.f / (2 * sprite.getScale().y)) };
	sprite.setOrigin(multiplier.x * sprite.getGlobalBounds().width, multiplier.y * sprite.getGlobalBounds().height);			//DLACZEGO POTRZEBNY MULTIPLIER?
	sprite.setPosition(this->position.x, this->position.y);
}

//metoda ³¹cz¹ca funkcje klasy
void Pac_man::update() {
	if (this->isDead == false)
	{
		this->setTexture();
		if (this->isCollision == true)
		{
			this->moveBack();
		}
		this->rotate();
		this->move();
		this->setPosition();
	}
	else
	{
		this->die();
	}
}

//zmiana private bool
void Pac_man::changeCollision(bool arg_isCollision)
{
	this->isCollision = arg_isCollision;
}

//po kolizji pac-man - ghost
void Pac_man::die()
{
	if (this->death_timer.getElapsedTime() <= sf::milliseconds(2000))
	{
		this->isDead = true;
		this->moveBack();
		this->velocity = { 0.f, 0.f };
		if (timer.getElapsedTime() >= sf::milliseconds(500)) {
			sprite.setTexture(texture);
			sprite.setTexture(brak);
			if (timer.getElapsedTime() >= sf::milliseconds(1000)) {
				timer.restart();
			}
		}
		else if (timer.getElapsedTime() < sf::milliseconds(500)) {
			sprite.setTexture(texture);			//throw Wyjatek(1, "cos tam")
		}
	}
	else
	{
		this->isDead = false;
		sprite.setPosition( 350.f, 500.f );
		sprite.setTexture(texture);
		return;
	}
}

//------------------------------------------------//
//------------METODY GHOST------------------------//
//------------------------------------------------//
/////////////////////PRIVATE////////////////////////
//Poruszanie siê duszka - œledzenie go (zmierza do pozycji pac-mana)
void Ghost::setMove(sf::Vector2f togo)
{
	//Wyjscie ghosta z boxu
	if (this->position.y <= 325.f && this->position.y > 275.f)
	{
		if(this->position.x >= 300.f && this->position.x < 350.f)
		this->velocity.x = this->ghostVelocity;
		else if(this->position.x > 350.f && this->position.x <= 400.f)
		this->velocity.x = -this->ghostVelocity;
		if (this->position.x == 350.f)
		{
			this->velocity.x = 0;
			this->velocity.y = -this->ghostVelocity;
		}	
	}
	//--------------------wlasny pomysl-------------------//
	else
	{
		//Gdy pac_man - ghost s¹ w jednej linii w plaszczyznie y
		if (this->position.y - togo.y == 0)
		{
			//idz do niego po osi x
			if (this->bangNo < 10)
			{
				//?????
				if (this->position.x < togo.x)
				{
					this->velocity.x = this->ghostVelocity;
					this->velocity.y = 0;
				}
				else if (this->position.x > togo.x)
				{
					this->velocity.x = -this->ghostVelocity;
					this->velocity.y = 0;
				}
			}
			//obejdz go po osi y
			if (this->bangNo >= 10)
			{
				//?????
				if (this->position.y == togo.y)									
				{
					this->velocity.y = -this->ghostVelocity;
				}
				else if (this->position.y == togo.y)
				{
					this->velocity.y = this->ghostVelocity;
				}
			}
			
		}
		//w plaszczyznie x
		else if (this->position.x - togo.x == 0)
		{
			//idz do niego po osi y
			if (this->bangNo < 10)
			{
				if (this->position.y > togo.y)
				{
					this->velocity.x = 0;
					this->velocity.y = -this->ghostVelocity;
				}
				else if (this->position.y < togo.y)
				{
					this->velocity.x = 0;
					this->velocity.y = this->ghostVelocity;
				}
			}
			//obejdz go po osi x
			if (this->bangNo >= 10)
			{
				if (this->position.x > togo.x)
				{
					this->velocity.x = -this->ghostVelocity;
				}
				else if (this->position.x < togo.x)
				{
					this->velocity.x = this->ghostVelocity;
				}
			}
			
		}
		//Gdy nie sa na jednej linii
		else
		{
			//Jesli odleglosc miedzy wsp x jest mniejsza niz miedzy wsp y
			if (abs(this->position.x - togo.x) < abs(this->position.y - togo.y) || abs(togo.x - this->position.x) < abs(togo.y - this->position.y))
			{
				if (this->position.x < togo.x)
				{
					//idz do niego po osi x
					if (this->bangNo < 10)
					{
						this->velocity.x = this->ghostVelocity;
						this->velocity.y = 0;
					}
					//obejdz go po osi y
					if (this->bangNo >= 10)
					{
						if (this->position.y > togo.y)
						{
							this->velocity.y = -this->ghostVelocity;
						}
						else
						{
							this->velocity.y = this->ghostVelocity;
						}
					}
					
				}
				else if (this->position.x > togo.x)
				{
					//idz do niego po osi x
					if (this->bangNo < 10)
					{
						this->velocity.x = -this->ghostVelocity;
						this->velocity.y = 0;
					}
					//obejdz go po osi y
					if (this->bangNo >= 10)
					{
						if (this->position.y > togo.y)
						{
							this->velocity.y = -this->ghostVelocity;
						}
						else
						{
							this->velocity.y = this->ghostVelocity;
						}
					}
				}
			}
			//Jesli odleglosc miedzy y jest mniejsza niz miedzy x
			else if (abs(this->position.x - togo.x) > abs(this->position.y - togo.y) || abs(togo.x - this->position.x) > abs(togo.y - this->position.y))
			{
				if (this->position.y > togo.y)
				{
					//idz do niego po osi y
					if (this->bangNo < 10)
					{
						this->velocity.x = 0;
						this->velocity.y = -this->ghostVelocity;
					}
					//obejdz go po osi x
					if (this->bangNo >= 10)
					{
						if (this->position.x > togo.x)
						{
							this->velocity.x = -this->ghostVelocity;
						}
						else
						{
							this->velocity.x = this->ghostVelocity;
						}
					}
				}
				else if (this->position.y < togo.y)
				{
					if (this->bangNo < 10)
							{
								this->velocity.x = 0;
								this->velocity.y = this->ghostVelocity;
							}
					if (this->bangNo >= 10)
							{
								if (this->position.x > togo.x)
								{
										this->velocity.x = -this->ghostVelocity;
								}
								else
								{
										this->velocity.x = this->ghostVelocity;
								}
							}
				}
			}
		}
		
	}
	//-------------------pomysl zaczerpniety z yt---------//uzywa calc_dist i setsetmove
	/*else
	{
	if (this->calc_dist(togo, 'W') <= this->calc_dist(togo, 'S'))
	{
		if (this->calc_dist(togo, 'D') <= this->calc_dist(togo, 'A'))
		{
			if (this->calc_dist(togo, 'D') <= this->calc_dist(togo, 'W'))
			{
				if (this->bangNo <= 30) { this->setsetMove('D'); }
				else { this->setsetMove('A'); }
			}
			else
			{
				if (this->bangNo <= 30) { this->setsetMove('W'); }
				else { this->setsetMove('S'); }
			}
		}
		else
		{
			if (this->calc_dist(togo, 'A') <= this->calc_dist(togo, 'W'))
			{
				if (this->bangNo <= 30) { this->setsetMove('A'); }
				else { this->setsetMove('D'); }
			}
			else
			{
				if (this->bangNo <= 30) { this->setsetMove('W'); }
				else { this->setsetMove('S'); }
			}
		}
	}
	else
	{
		if (this->calc_dist(togo, 'D') <= this->calc_dist(togo, 'A'))
		{
			if (this->calc_dist(togo, 'D') <= this->calc_dist(togo, 'S'))
			{
				if(this->bangNo <=30) { this->setsetMove('D'); }
				else { this->setsetMove('A'); }
			}
			else
			{
				if (this->bangNo <= 30) { this->setsetMove('S'); }
				else { this->setsetMove('W'); }
			}
		}
		else
		{
			if (this->calc_dist(togo, 'A') < this->calc_dist(togo, 'S'))
			{
				if (this->bangNo <= 30) { this->setsetMove('A'); }
				else { this->setsetMove('D'); }
			}
			else
			{
				if (this->bangNo <= 30) { this->setsetMove('S'); }
				else { this->setsetMove('W'); }
			}
		}
	}
	}*/
}

//Cofniecie duszka przy zderzeniu
void Ghost::moveBack() {
	sprite.move(-this->velocity);
}

//obsluga bool isCollision
void Ghost::move(sf::Vector2f togo)
{
	if (this->isCollision == false)
	{
		this->lastVelocity = this->velocity;
		this->setMove(togo);								
		sprite.move(this->velocity);
	}
	else if (this->isCollision == true)
	{
		if (this->velocity.x == this->ghostVelocity) {
			if (this->lastVelocity != this->velocity)
			{
				this->velocity = this->lastVelocity;
			}
			else
			{
				this->velocity.x = 0;
				this->velocity.y = 0;
				this->setMove(togo);
			}

		}
		else if (this->velocity.y == this->ghostVelocity) {
			if (this->lastVelocity != this->velocity)
			{
				this->velocity = this->lastVelocity;
			}
			else
			{
				this->velocity.x = 0;
				this->velocity.y = 0;
				this->setMove(togo);
			}
		}
		else if (this->velocity.x == -this->ghostVelocity) {
			if (this->lastVelocity != this->velocity)
			{
				this->velocity = this->lastVelocity;
			}
			else
			{
				this->velocity.x = 0;
				this->velocity.y = 0;
				this->setMove(togo);
			}
		}
		else if (this->velocity.y == -this->ghostVelocity) {
			if (this->lastVelocity != this->velocity)
			{
				this->velocity = this->lastVelocity;
			}
			else
			{
				this->velocity.x = 0;
				this->velocity.y = 0;
				this->setMove(togo);
			}
		}
		this->isCollision = false;
		sprite.move(this->velocity);

	}
}

//
void Ghost::setPosition()
{
	this->position = sprite.getPosition();
}

//Aktualizacja zmiennej bangNo
void Ghost::bangSet()
{
	if (this->bangNo == 1)
		this->lastPosition = this->position;
	if (abs(this->position.x - this->lastPosition.x) > 75.f || abs(this->position.y - this->lastPosition.y) > 75.f)
		this->bangNo = 0;
	if (this->bangNo >= 200)
		this->isStuck = true;
}

//obliczanie odleglosci w linii prostej
float Ghost::calc_dist(sf::Vector2f pac_pos, char dir)
{
	float dist_x = this->position.x - pac_pos.x;
	float dist_y = this->position.y - pac_pos.y;
	switch (dir)
	{
	case 'W':
		return sqrt(dist_x * dist_x + (dist_y - this->getBounds().height)*( dist_y - this->getBounds().height)); break;
	case 'S':
		return sqrt(dist_x * dist_x + (dist_y + this->getBounds().height) * (dist_y + this->getBounds().height)); break;
	case 'A':
		return sqrt((dist_x - this->getBounds().width) * (dist_x - this->getBounds().width) + dist_y*dist_y); break;
	case 'D':
		return sqrt((dist_x + this->getBounds().width) * (dist_x + this->getBounds().width) + dist_y * dist_y); break;
	}
}

//?
void Ghost::setsetMove(char dir)
{
switch (dir)
{
case 'W': goto W; break;
case 'A': goto A; break;
case 'S': goto S; break;
case 'D': goto D; break;
}
W:
	if (this->bangNo <= 30)
	{
		this->velocity.x = 0;
		this->velocity.y = -this->ghostVelocity;
		return;
	}
	else { this->bangNo = 0; this->moveBack(); goto A; }
A:
	if (this->bangNo <= 30)
	{
		this->velocity.x = -this->ghostVelocity;
		this->velocity.y = 0;
		return;
	}
	else { this->bangNo = 0; this->moveBack(); goto S; }
S:
	if (this->bangNo <= 30)
	{
		this->velocity.x = 0;
		this->velocity.y = this->ghostVelocity;
		return;
	}
	else { this->bangNo = 0; this->moveBack(); goto D; }
D:
	if (this->bangNo <= 30)
	{
		this->velocity.x = this->ghostVelocity;
		this->velocity.y = 0;
		return;
	}
	else { this->bangNo = 0; this->moveBack(); goto W; }


	/*char kolejnosc[] = "WASD";
	int nr;
	int i;
	char temp[4];
	for (i = 0; i < 4; i++)
	{
		if (kolejnosc[i] = dir) { nr = i; }
		if (nr - i > 0) { temp[i] = kolejnosc[nr - i]; }
		else { temp[i] = kolejnosc[i - nr]; }
	}
	if (this->bangNo <= 30)
	{
		switch (temp[1])
		{
		case 'W':
			this->velocity.x = 0;
			this->velocity.y = -this->ghostVelocity;
			break;
		case 'S':
			this->velocity.x = 0;
			this->velocity.y = this->ghostVelocity;
			break;
		case 'A':
			this->velocity.x = -this->ghostVelocity;
			this->velocity.y = 0;
			break;
		case 'D':
			this->velocity.x = this->ghostVelocity;
			this->velocity.y = 0;
			break;
		}
		this->bangNo = 0;
	}else
	{
		if (this->bangNo <= 30)
		{
			switch (temp[2])
			{
			case 'W':
				this->velocity.x = 0;
				this->velocity.y = -this->ghostVelocity;
				break;
			case 'S':
				this->velocity.x = 0;
				this->velocity.y = this->ghostVelocity;
				break;
			case 'A':
				this->velocity.x = -this->ghostVelocity;
				this->velocity.y = 0;
				break;
			case 'D':
				this->velocity.x = this->ghostVelocity;
				this->velocity.y = 0;
				break;
			}
			this->bangNo = 0;
		}
		else
		{
			if (this->bangNo <= 30)
			{
				switch (temp[3])
				{
				case 'W':
					this->velocity.x = 0;
					this->velocity.y = -this->ghostVelocity;
					break;
				case 'S':
					this->velocity.x = 0;
					this->velocity.y = this->ghostVelocity;
					break;
				case 'A':
					this->velocity.x = -this->ghostVelocity;
					this->velocity.y = 0;
					break;
				case 'D':
					this->velocity.x = this->ghostVelocity;
					this->velocity.y = 0;
					break;
				}
				this->bangNo = 0;
			}
			else
			{
				if (this->bangNo <= 30)
				{
					switch (temp[3])
					{
					case 'W':
						this->velocity.x = 0;
						this->velocity.y = -this->ghostVelocity;
						break;
					case 'S':
						this->velocity.x = 0;
						this->velocity.y = this->ghostVelocity;
						break;
					case 'A':
						this->velocity.x = -this->ghostVelocity;
						this->velocity.y = 0;
						break;
					case 'D':
						this->velocity.x = this->ghostVelocity;
						this->velocity.y = 0;
						break;
					}
					this->bangNo = 0;
				}
			}
		}
	}*/
}

void Ghost::fizzySet()
{
	if (this->isFizzy == true)
	{
		if (timer_ghost.getElapsedTime() >= sf::seconds(5))
		{
			this->isFizzy = false;
			this->isInvurnelable = false;
			sprite.setTexture(texture);
		}
	}
}

//konstruktor
Ghost::Ghost(int a)
{
	this->isFizzy = false;
	if (a == 0 && !texture.loadFromFile("assets/png/red.png")) { blad_c[0] = new Exception(3, "Nie udalo sie wczytac tekstury z pliku: assets/png/red.png"); throw* blad_c[0]; }
	if (a == 1 && !texture.loadFromFile("assets/png/orange.png")) { blad_c[1] = new Exception(3, "Nie udalo sie wczytac tekstury z pliku: assets/png/orange.png"); throw* blad_c[1]; }
	if (a == 2 && !texture.loadFromFile("assets/png/pink.png")) { blad_c[2] = new Exception(3, "Nie udalo sie wczytac tekstury z pliku: assets/png/pink.png"); throw* blad_c[2]; }
	if (a == 3 && !texture.loadFromFile("assets/png/blue.png")) { blad_c[3] = new Exception(3, "Nie udalo sie wczytac tekstury z pliku: assets/png/blue.png"); throw* blad_c[3]; }
	texture.setSmooth(true);
	if(!brak.loadFromFile("assets/png/black.png")) { blad_c[4] = new Exception(3, "Nie udalo sie wczytac tekstury z pliku: assets/png/black.png"); throw* blad_c[4]; }
	if(!fizzy.loadFromFile("assets/png/fizzy.png")) { blad_c[5] = new Exception(3, "Nie udalo sie wczytac tekstury z pliku: assets/png/fizzy.png"); throw* blad_c[5]; }
	sprite.setTexture(texture);
	sprite.scale(sf::Vector2f(0.03917f, 0.03917f));
	sf::Vector2f multiplier{ (1.f / (2 * sprite.getScale().x)), (1.f / (2 * sprite.getScale().y)) };
	sprite.setOrigin(multiplier.x * sprite.getGlobalBounds().width, multiplier.y * sprite.getGlobalBounds().height);
	sprite.setPosition(this->position.x + a*25.f, this->position.y);
	this->startPosition = { this->position.x + a * 25.f, this->position.y };
	this->nr = a;
}

//metoda ³¹cz¹ca funkcje klasy
void Ghost::update(Character *w_pac, int a)
{
	switch(a)
	{
	case 1:
	{
		if (timer.getElapsedTime() <= sf::milliseconds(1000))
		{
			this->velocity = { 0.f, 0.f };
			std::cout << "JESTEM w SWITCH case 1" << "MOJE a = " << a << std::endl;
			return;
		}break;
	}
	case 2:
	{
		if (timer.getElapsedTime() <= sf::milliseconds(2000) && timer.getElapsedTime() > sf::milliseconds(1000))
		{
			this->velocity = { 0.f, 0.f };
			std::cout << "JESTEM w SWITCH case 2" << "MOJE a = " << a << std::endl;
			return;
		}break;
	}
	case 3:
	{
		if (timer.getElapsedTime() <= sf::milliseconds(3000) && timer.getElapsedTime() > sf::milliseconds(2000))
		{
			this->velocity = { 0.f, 0.f };
			std::cout << "JESTEM w SWITCH case 3" << "MOJE a = " << a << std::endl;
			return;
		}break;
	}
	}
	if (this->isDead == false)
	{
		if (this->isCollision == true)
		{
			this->moveBack();
			this->bangNo++;
			this->bangSet();
		}
		sf::Vector2f offset = { 250.f * w_pac->getVelocity() };
		if (this->isFizzy) { sprite.setTexture(fizzy); this->move({50.f,50.f}); }
		else { 
			switch (this->nr)
			{
			case 0:
				this->move(w_pac->getPosition()); break;
			case 1:
				this->move(w_pac->getPosition() + offset); break;
			case 2:
				offset = { 400.f * w_pac->getVelocity() };
				this->move(w_pac->getPosition() - offset); break;
			case 3:
				offset = { 150.f, -150.f };
				this->move(w_pac->getPosition() - offset); break;
			default:
				this->move(w_pac->getPosition());
			}
		}
		this->setPosition();
		this->fizzySet();
		//std::cout << "LICZBA UDERZEN: " << bangNo << std::endl;
	}
	else
	{
		if (this->isFizzy == false) { this->die(); }
		else { this->move({350.f, 275.f}); }
	}
}

//zmiana bool isCollision
void Ghost::changeCollision(bool arg_isCollision)
{
	this->isCollision = arg_isCollision;
}

//po kolizji pac-man - ghost
void Ghost::die()
{
	if (this->death_timer.getElapsedTime() <= sf::milliseconds(2000))
	{
		if (!this->isFizzy)
		{
			this->isDead = true;
			this->moveBack();
			this->velocity = { 0.f, 0.f };
			if (timer_ghost.getElapsedTime() >= sf::milliseconds(500)) {
				sprite.setTexture(texture);
				if (timer_ghost.getElapsedTime() >= sf::milliseconds(1000)) {
					timer_ghost.restart();
				}
			}
			else if (timer_ghost.getElapsedTime() < sf::milliseconds(500)) {
				sprite.setTexture(brak);
			}
		}
		else { this->move(this->startPosition); }
	}
	else
	{
		std::cout << "Dziala else!" << std::endl;
		sprite.setTexture(texture);
		sprite.setPosition(this->startPosition);
		this->isDead = false;
		return;
	}
}

void Ghost::changeDeath(bool arg_isDead)
{
	this->isDead = arg_isDead;
}