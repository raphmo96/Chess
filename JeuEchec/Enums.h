#pragma once

namespace Enums {
	enum PieceType {
		Pawn,
		Tower,
		Knight,
		Bishop,
		Queen,
		King
	};

	enum Spells {
		Null,
		Heal,
		Freeze,
		RegenMana,
		Skip,
		Rewind,
	};

	enum ButtonType {
		Empty,
		LoadGame,
		ResetGame,
		HealButton,
		FreezeButton,
		RegenManaButton,
		SkipButton,
		RewindButton,

	};
}