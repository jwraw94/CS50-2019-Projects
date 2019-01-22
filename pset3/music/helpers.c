// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <string.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
// Input as string, return the number of eighths
int duration(string fraction)
{
    int a = fraction[0] - '0';
    int b = fraction[2] - '0';
    return (8 * a) / b;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int accidental = 0;
    int octave = 0;

    // Find out if accidental & octave.
    if (note[1] == 35)
    {
        accidental = 1 ;
        octave = note[2] - 52;
    }
    else if (note[1] == 98)
    {
        accidental = -1 ;
        octave = note[2] - 52;
    }
    else
    {
        octave = note[1] - 52;
    }
    int possible[12] = {65, 65, 66, 67, 67, 68, 68, 69, 70, 70, 71, 71};
    int semitones = 0;
    int y = 0;
    int x = 1;
    int q = 0;
    int r = 1;
    //Work out how many halftones by iterating over NOTES array
    for (int j = 0; (x != y) && (j < 11) ; j++)
    {
        x = note[0];
        y = possible[j];
        semitones = j;
    }
    if (note[0] >= 67 && octave <= 0)
    {
        int npossible[12] = {72, 71, 71, 70, 69, 69, 68, 68, 67, 66, 66, 65};
        for (int p = 0; (q != r) && (p < 11) ; p++)
        {
            q = note[0];
            r = npossible[p];
            semitones = -p;
        }
    }
    if (note[0] >= 67 && octave > 0)
    {
        semitones = semitones - 12;
    }
    int frequency = 0;
    double n = 0;
    double nf = 0;
    if (note[0] >= 67 && octave <= 0)
    {
        n = semitones + (12 * (octave)) + accidental - 1;
    }
    else
    {
        n = semitones + (12 * octave) + accidental;
    }

    nf = (n / 12);
    frequency = round(440 * pow(2, nf));
    return frequency;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0] == '\0')
    {
        return true;
    }
    else
    {
        return false;
    }
}