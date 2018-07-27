#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Enums.h"
#include <tuple>
class Coordinates;

class Piece
{
public:
	Piece(bool, SDL_Surface*, Coordinates);
	~Piece();

	//Draw image on given surface in given rect;
	void virtual Draw(SDL_Surface*, SDL_Rect*);

	//Return wether the piece if black or white
	bool virtual IsWhite() { return m_IsWhite; }

	//Increment number of movement;
	void RaiseNbMove() { m_NbMove++; }

	//Apply damage to piece and return whether is was killed or not
	bool virtual ReceiveDamage(int);

	//Assert if the piece can move to the given coordinates, given its initial coordinates;
	bool virtual CanMove(Coordinates, Coordinates);

	//Return total number of movement the piece did;
	int GetNbMove() { return m_NbMove; }

	//Return remaining hp
	int GetHP() { return m_Hp; }

	//Return damage of piece;
	int GetDamage() { return m_Damage; }

	//Return remaining mana of piece;
	int GetMana() { return m_Mana; }

	//Return Armor of piece;
	int GetArmor() { return m_Armor; }

	//Give this piece more HP;
	void RegenHP(int);

	//Give this piece more Mana;
	void RegenMana(int);

	//Prevent a piece from moving;
	void ToggleFreeze();

	//Bring back begining stats
	void ResetStat();

	//Return skill description of piece
	std::string GetSkillDescription() { return m_SkillDescription; }

	//Return skill name of piece
	std::string GetSkillName() { return m_SkillName; }

	//Return the initial position of the piece;
	Coordinates GetInitialPos() { return m_InitialPos; }

	//Return the piece type;
	Enums::PieceType GetType() { return m_Type; }

protected:
	bool m_IsWhite;

	bool m_IsSelected;

	bool m_CanStackMovement;

	bool m_FirstPlay;

	int m_NbMove;

	int m_MaxMovement;

	int m_Mana;

	int m_Hp;

	int m_Armor;

	int m_Damage;

	bool m_IsFrozen;

	Enums::PieceType m_Type;

	std::string m_SkillName;

	std::string m_SkillDescription;

	Coordinates m_InitialPos;

	std::vector<Coordinates> m_PossibleMove;

	SDL_Surface* m_Image;

	std::tuple<int, int, int, int> m_Stats;

	//Initialize stats in order HP Armor Damage Mana
	void InitStats(std::tuple<int, int, int, int>);
};