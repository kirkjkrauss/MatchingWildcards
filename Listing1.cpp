// Compares two text strings.  Accepts '?' as a single-character wildcard.  
// For each '*' wildcard, seeks out a matching sequence of any characters 
// beyond it.  Otherwise compares the strings a character at a time. 
//
bool FastWildCompare(char *pWild, char *pTame)
{
	char *pWildSequence;  // Points to prospective wild string match after '*'
	char *pTameSequence;  // Points to prospective tame string match

	// Find a first wildcard, if one exists, and the beginning of any  
	// prospectively matching sequence after it.
	do
	{
		// Check for the end from the start.  Get out fast, if possible.
		if (!*pTame)
		{
			if (*pWild)
			{
				while (*(pWild++) == '*')
				{
					if (!(*pWild))
					{
						return true;   // "ab" matches "ab*".
					}
				}

			    return false;          // "abcd" doesn't match "abc".
			}
			else
			{
				return true;           // "abc" matches "abc".
			}
		}
		else if (*pWild == '*')
		{
			// Got wild: set up for the second loop and skip on down there.
			while (*(++pWild) == '*')
			{
				continue;
			}

			if (!*pWild)
			{
				return true;           // "abc*" matches "abcd".
			}

			// Search for the next prospective match.
			if (*pWild != '?')
			{
				while (*pWild != *pTame)
				{
					if (!*(++pTame))
					{
						return false;  // "a*bc" doesn't match "ab".
					}
				}
			}

			// Keep fallback positions for retry in case of incomplete match.
			pWildSequence = pWild;
			pTameSequence = pTame;
			break;
		}
		else if (*pWild != *pTame && *pWild != '?')
		{
			return false;              // "abc" doesn't match "abd".
		}

		++pWild;                       // Everything's a match, so far.
		++pTame;
	} while (true);

	// Find any further wildcards and any further matching sequences.
	do
	{
		if (*pWild == '*')
		{
			// Got wild again.
			while (*(++pWild) == '*')
			{
				continue;
			}

			if (!*pWild)
			{
				return true;           // "ab*c*" matches "abcd".
			}

			if (!*pTame)
			{
				return false;          // "*bcd*" doesn't match "abc".
			}

			// Search for the next prospective match.
			if (*pWild != '?')
			{
				while (*pWild != *pTame)
				{
					if (!*(++pTame))
					{
						return false;  // "a*b*c" doesn't match "ab".
					}
				}
			}

			// Keep the new fallback positions.
			pWildSequence = pWild;
			pTameSequence = pTame;
		}
		else if (*pWild != *pTame && *pWild != '?')
		{
			// The equivalent portion of the upper loop is really simple.
			if (!*pTame)
			{
				return false;          // "*bcd" doesn't match "abc".
			}

			// A fine time for questions.
			while (*pWildSequence == '?')
			{
				++pWildSequence;
				++pTameSequence;
			}

			pWild = pWildSequence;

			// Fall back, but never so far again.
			while (*pWild != *(++pTameSequence))
			{
				if (!*pTameSequence)
				{
					return false;      // "*a*b" doesn't match "ac".
				}
			}

			pTame = pTameSequence;
		}

		// Another check for the end, at the end.
		if (!*pTame)
		{
			if (!*pWild)
			{
				return true;           // "*bc" matches "abc".
			}
			else
			{
				return false;          // "*bc" doesn't match "abcd".
			}
		}

		++pWild;                       // Everything's still a match.
		++pTame;
	} while (true);
}
