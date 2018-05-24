#include <stdio.h>

#define COMPARE_PERFORMANCE  1
#define COMPARE_WILD         1
#define COMPARE_TAME         1
#define COMPARE_EMPTY        1


bool test(char *pTame, char *pWild, bool bExpectedResult)
{
	bool bPassed = true;

	if (bExpectedResult != FastWildCompare(pWild, pTame))
	{
		bPassed = false;
	}

#if defined(COMPARE_PERFORMANCE)
	if (bExpectedResult != WildTextCompare(pTame, pWild))
	{
		bPassed = false;
	}
#endif

	return bPassed;
}


int testwild(void)
{
    int  nReps;
    bool bAllPassed = true;

#if defined(COMPARE_PERFORMANCE)
    // Can choose as many repetitions as you're expecting in the real world.
    nReps = 1000000;
#else
    nReps = 1;
#endif

    while (nReps--)
    {
		// Case with mismatch after '*'
        bAllPassed &= test("abc", "ab*d", false);

        // Cases with repeating character sequences.
        bAllPassed &= test("abcccd", "*ccd", true);
        bAllPassed &= test("mississipissippi", "*issip*ss*", true);
        bAllPassed &= test("xxxx*zzzzzzzzy*f", "xxxx*zzy*fffff", false);
        bAllPassed &= test("xxxx*zzzzzzzzy*f", "xxx*zzy*f", true);
        bAllPassed &= test("xxxxzzzzzzzzyf", "xxxx*zzy*fffff", false);
        bAllPassed &= test("xxxxzzzzzzzzyf", "xxxx*zzy*f", true);
        bAllPassed &= test("xyxyxyzyxyz", "xy*z*xyz", true);
        bAllPassed &= test("mississippi", "*sip*", true);
        bAllPassed &= test("xyxyxyxyz", "xy*xyz", true);
        bAllPassed &= test("mississippi", "mi*sip*", true);
        bAllPassed &= test("ababac", "*abac*", true);
        bAllPassed &= test("ababac", "*abac*", true);
        bAllPassed &= test("aaazz", "a*zz*", true);
        bAllPassed &= test("a12b12", "*12*23", false);
        bAllPassed &= test("a12b12", "a12b", false);
        bAllPassed &= test("a12b12", "*12*12*", true);

#if !defined(COMPARE_PERFORMANCE)
		// From DDJ reader Andy Belf
        bAllPassed &= test("caaab", "*a?b", true);
#endif

        // Additional cases where the '*' char appears in the tame string.
        bAllPassed &= test("*", "*", true);
        bAllPassed &= test("a*abab", "a*b", true);
        bAllPassed &= test("a*r", "a*", true);
        bAllPassed &= test("a*ar", "a*aar", false);

        // More double wildcard scenarios.
        bAllPassed &= test("XYXYXYZYXYz", "XY*Z*XYz", true);
        bAllPassed &= test("missisSIPpi", "*SIP*", true);
        bAllPassed &= test("mississipPI", "*issip*PI", true);
        bAllPassed &= test("xyxyxyxyz", "xy*xyz", true);
        bAllPassed &= test("miSsissippi", "mi*sip*", true);
        bAllPassed &= test("miSsissippi", "mi*Sip*", false);
        bAllPassed &= test("abAbac", "*Abac*", true);
        bAllPassed &= test("abAbac", "*Abac*", true);
        bAllPassed &= test("aAazz", "a*zz*", true);
        bAllPassed &= test("A12b12", "*12*23", false);
        bAllPassed &= test("a12B12", "*12*12*", true);
        bAllPassed &= test("oWn", "*oWn*", true);

        // Completely tame (no wildcards) cases.
        bAllPassed &= test("bLah", "bLah", true);
        bAllPassed &= test("bLah", "bLaH", false);

        // Simple mixed wildcard tests suggested by Marlin Deckert.
        bAllPassed &= test("a", "*?", true);
        bAllPassed &= test("ab", "*?", true);
        bAllPassed &= test("abc", "*?", true);

        // More mixed wildcard tests including coverage for false positives.
        bAllPassed &= test("a", "??", false);
        bAllPassed &= test("ab", "?*?", true);
        bAllPassed &= test("ab", "*?*?*", true);
        bAllPassed &= test("abc", "?**?*?", true);
        bAllPassed &= test("abc", "?**?*&?", false);
        bAllPassed &= test("abcd", "?b*??", true);
        bAllPassed &= test("abcd", "?a*??", false);
        bAllPassed &= test("abcd", "?**?c?", true);
        bAllPassed &= test("abcd", "?**?d?", false);
        bAllPassed &= test("abcde", "?*b*?*d*?", true);

        // Single-character-match cases.
        bAllPassed &= test("bLah", "bL?h", true);
        bAllPassed &= test("bLaaa", "bLa?", false);
        bAllPassed &= test("bLah", "bLa?", true);
        bAllPassed &= test("bLaH", "?Lah", false);
        bAllPassed &= test("bLaH", "?LaH", true);

        // Many-wildcard scenarios.
        bAllPassed &= test("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", 
            "a*a*a*a*a*a*aa*aaa*a*a*b", true);
        bAllPassed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab", 
            "*a*b*ba*ca*a*aa*aaa*fa*ga*b*", true);
        bAllPassed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab", 
            "*a*b*ba*ca*a*x*aaa*fa*ga*b*", false);
        bAllPassed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab", 
            "*a*b*ba*ca*aaaa*fa*ga*gggg*b*", false);
        bAllPassed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab", 
            "*a*b*ba*ca*aaaa*fa*ga*ggg*b*", true);
        bAllPassed &= test("aaabbaabbaab", "*aabbaa*a*", true);
        bAllPassed &= test("a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*", 
            "a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*", true);
        bAllPassed &= test("aaaaaaaaaaaaaaaaa", 
            "*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*", true);
        bAllPassed &= test("aaaaaaaaaaaaaaaa", 
            "*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*", false);
        bAllPassed &= test("abc*abcd*abcde*abcdef*abcdefg*abcdefgh*abcdefghi*a\
bcdefghij*abcdefghijk*abcdefghijkl*abcdefghijklm*abcdefghijklmn", 
            "abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*a\
            bc*", false);
        bAllPassed &= test("abc*abcd*abcde*abcdef*abcdefg*abcdefgh*abcdefghi*a\
bcdefghij*abcdefghijk*abcdefghijkl*abcdefghijklm*abcdefghijklmn", 
            "abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*", true);
        bAllPassed &= test("abc*abcd*abcd*abc*abcd", "abc*abc*abc*abc*abc", 
            false);
        bAllPassed &= test(
            "abc*abcd*abcd*abc*abcd*abcd*abc*abcd*abc*abc*abcd", 
            "abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abcd", true);
        bAllPassed &= test("abc", "********a********b********c********", 
            true);
        bAllPassed &= test("********a********b********c********", "abc", 
            false);
        bAllPassed &= test("abc", "********a********b********b********", 
            false);
        bAllPassed &= test("*abc*", "***a*b*c***", true);

        // A case-insensitive algorithm test.
        // bAllPassed &= test("mississippi", "*issip*PI", true);

        // Tests suggested by other DDJ readers
        bAllPassed &= test("", "?", false);
        bAllPassed &= test("", "*?", false);
        bAllPassed &= test("", "", true);
        bAllPassed &= test("a", "", false);
    }

    if (bAllPassed)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }

    return 0;
}


int main(void)
{
#if defined(COMPARE_TAME)
	testtame();
#endif

#if defined(COMPARE_EMPTY)
	testempty();
#endif

#if defined(COMPARE_WILD)
	testwild();
#endif

	return 0;
}
