# Sequencer
Making a basic beat sequencer with hopes of learning more about digital audio
workstations and audio in general.

## Systems Requirements
GC / Linux 

## TODO
1.	Introduce resolution variable which would allow user to place samples in 
	between the counted beats of a bar.
		a.	Need to create a new "sound", "and". If the user sets a high
			resolution but doesn't want to place a sound on every single mark, 
			they can place an "and", meaning you would hear nothing inbetween
			the counted beats.
3.	Add error handling when samples inputed have diff num of channels
2.	Add ability to superimpose instruments. Maybe this looks like another sudo
	enum that tells which samples throughout the beat should be cut before the
	next beat and which should superimpose with the next sample. 

