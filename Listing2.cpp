// Slower but portable version of FastWildCompare().  Performs no direct 
// pointer manipulation.  Can work with wide-character text strings.  Use 
// only with null-terminated strings.
//
// Compares two text strings.  Accepts '?' as a single-character wildcard.  
// For each '*' wildcard, seeks out a matching sequence of any characters 
// beyond it.  Otherwise compares the strings a character at a time.
//
bool FastWildComparePortable(char *strWild, char *strTame)
{
	int  iWild = 0;     // Index for both tame and wild strings in upper loop
	int  iTame;         // Index for tame string, set going into lower loop
	int  iWildSequence; // Index for prospective match after '*' (wild string)
	int  iTameSequence; // Index for prospective match (tame string)

	// Find a first wildcard, if one exists, and the beginning of any  
	// prospectively matching sequence after it.
	do
	{
		// Check for the end from the start.  Get out fast, if possible.
		if (!strTame[iWild])
		{
			if (strWild[iWild])
			{
			    return false;          // "abcd" doesn't match "abc".
			}
			else
			{
				return true;           // "abc" matches "abc".
			}
		}
		else if (strWild[iWild] == '*')
		{
			// Got wild: set up for the second loop and skip on down there.
			iTame = iWild;

			while (strWild[++iWild] == '*')
			{
				continue;
			}

			if (!strWild[iWild])
			{
				return true;           // "abc*" matches "abcd".
			}

			// Search for the next prospective match.
			if (strWild[iWild] != '?')
			{
				while (strWild[iWild] != strTame[iTame])
				{
					if (!strTame[++iTame])
					{
						return false;  // "a*bc" doesn't match "ab".
					}
				}
			}

			// Keep fallback positions for retry in case of incomplete match.
			iWildSequence = iWild;
			iTameSequence = iTame;
			break;
		}
		else if (strWild[iWild] != strTame[iWild] && strWild[iWild] != '?')
		{
			return false;              // "abc" doesn't match "abd".
		}

		++iWild;                       // Everything's a match, so far.
	} while (true);

	// Find any further wildcards and any further matching sequences.
	do
	{
		if (strWild[iWild] == '*')
		{
			// Got wild again.
			while (strWild[++iWild] == '*')
			{
				continue;
			}

			if (!strWild[iWild])
			{
				return true;           // "ab*c*" matches "abcd".
			}

			if (!strTame[iTame])
			{
				return false;          // "*bcd*" doesn't match "abc".
			}

			// Search for the next prospective match.
			if (strWild[iWild] != '?')
			{
				while (strWild[iWild] != strTame[iTame])
				{
					if (!strTame[++iTame])
					{
						return false;  // "a*b*c" doesn't match "ab".
					}
				}
			}

			// Keep the new fallback positions.
			iWildSequence = iWild;
			iTameSequence = iTame;
		}
		else if (strWild[iWild] != strTame[iTame] && strWild[iWild] != '?')
		{
			// The equivalent portion of the upper loop is really simple.
			if (!strTame[iTame])
			{
				return false;          // "*bcd" doesn't match "abc".
			}

			// A fine time for questions.
			while (strWild[iWildSequence] == '?')
			{
				++iWildSequence;
				++iTameSequence;
			}

			iWild = iWildSequence;

			// Fall back, but never so far again.
			while (strWild[iWild] != strTame[++iTameSequence])
			{
				if (!strTame[iTameSequence])
				{
					return false;      // "*a*b" doesn't match "ac".
				}
			}

			iTame = iTameSequence;
		}

		// Another check for the end, at the end.
		if (!strTame[iTame])
		{
			if (!strWild[iWild])
			{
				return true;           // "*bc" matches "abc".
			}
			else
			{
				return false;          // "*bc" doesn't match "abcd".
			}
		}

		++iWild;                       // Everything's still a match.
		++iTame;
	} while (true);
}
