#pragma once

#include "EffectParam.h"

/*

PatternRow is the most basic component of a song. Both Patterns and Macros
are just a list of these.

A PatternRow consists of two EffectParams. The first one has a special meaning
in the editor, that is the note column. It still works internally exactly like
the "normal" effect column, except for the first column being able to trigger
new notes.

*/

struct PatternRow
{
	/* 
	 * Column order when a row has a note and an effect
	 */
	enum Column
	{
		NoteType,
		NoteParam1,
		NoteParam2,
		EffectType,
		EffectParam1,
		EffectParam2,
		NumColumns,
		
		Note = NoteType,
		Octave = NoteParam2
	};
	
	EffectParam note, effect;
	
	enum ColumnFlag 
	{
		FlagNote = 1 << Note,
		FlagOctave = 1 << Octave,
		FlagEffectType = 1 << EffectType,
		FlagEffectParam1 = 1 << EffectParam1,
		FlagEffectParam2 = 1 << EffectParam2,
		FlagEffect = FlagEffectType,
		FlagAllColumns = -1
	};
	
	PatternRow();
	
	static const char *getNoteName(int note);
	
	bool shouldSkipParam1() const;
	int getNote() const;
	int getOctave() const;
	void clear(int flags = FlagAllColumns);
	int getNoteWithOctave() const;
	void setOctave(int octave);
	void setNoteAndOctave(int noteAndOctave);
		
	static const int NoNote = 0xff;
};
