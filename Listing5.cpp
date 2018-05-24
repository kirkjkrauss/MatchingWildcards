int testempty(void)
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
		// A simple case
        bAllPassed &= test("", "abd", false);

        // Cases with repeating character sequences
        bAllPassed &= test("", "abcccd", false);
        bAllPassed &= test("", "mississipissippi", false);
        bAllPassed &= test("", "xxxxzzzzzzzzyfffff", false);
        bAllPassed &= test("", "xxxxzzzzzzzzyf", false);
        bAllPassed &= test("", "xxxxzzy.fffff", false);
        bAllPassed &= test("", "xxxxzzzzzzzzyf", false);
        bAllPassed &= test("", "xyxyxyzyxyz", false);
        bAllPassed &= test("", "mississippi", false);
        bAllPassed &= test("", "xyxyxyxyz", false);
        bAllPassed &= test("", "m ississippi", false);
        bAllPassed &= test("", "ababac*", false);
        bAllPassed &= test("", "ababac", false);
        bAllPassed &= test("", "aaazz", false);
        bAllPassed &= test("", "1212", false);
        bAllPassed &= test("", "a12b", false);
        bAllPassed &= test("", "a12b12", false);

        // A mix of cases
        bAllPassed &= test("", "n", false);
        bAllPassed &= test("", "aabab", false);
        bAllPassed &= test("", "ar", false);
        bAllPassed &= test("", "aaar", false);
        bAllPassed &= test("", "XYXYXYZYXYz", false);
        bAllPassed &= test("", "missisSIPpi", false);
        bAllPassed &= test("", "mississipPI", false);
        bAllPassed &= test("", "xyxyxyxyz", false);
        bAllPassed &= test("", "miSsissippi", false);
        bAllPassed &= test("", "miSsisSippi", false);
        bAllPassed &= test("", "abAbac", false);
        bAllPassed &= test("", "abAbac", false);
        bAllPassed &= test("", "aAazz", false);
        bAllPassed &= test("", "A12b123", false);
        bAllPassed &= test("", "a12B12", false);
        bAllPassed &= test("", "oWn", false);
        bAllPassed &= test("", "bLah", false);
        bAllPassed &= test("", "bLaH", false);

		// Both strings empty
        bAllPassed &= test("", "", true);

		// Another simple case
        bAllPassed &= test("abc", "", false);

        // Cases with repeating character sequences.
        bAllPassed &= test("abcccd", "", false);
        bAllPassed &= test("mississipissippi", "", false);
        bAllPassed &= test("xxxxzzzzzzzzyf", "", false);
        bAllPassed &= test("xxxxzzzzzzzzyf", "", false);
        bAllPassed &= test("xxxxzzzzzzzzyf", "", false);
        bAllPassed &= test("xxxxzzzzzzzzyf", "", false);
        bAllPassed &= test("xyxyxyzyxyz", "", false);
        bAllPassed &= test("mississippi", "", false);
        bAllPassed &= test("xyxyxyxyz", "", false);
        bAllPassed &= test("m ississippi", "", false);
        bAllPassed &= test("ababac", "", false);
        bAllPassed &= test("dababac", "", false);
        bAllPassed &= test("aaazz", "", false);
        bAllPassed &= test("a12b12", "", false);
        bAllPassed &= test("a12b12", "", false);
        bAllPassed &= test("a12b12", "", false);

        // A mix of cases
        bAllPassed &= test("n", "", false);
        bAllPassed &= test("aabab", "", false);
        bAllPassed &= test("ar", "", false);
        bAllPassed &= test("aar", "", false);
        bAllPassed &= test("XYXYXYZYXYz", "", false);
        bAllPassed &= test("missisSIPpi", "", false);
        bAllPassed &= test("mississipPI", "", false);
        bAllPassed &= test("xyxyxyxyz", "", false);
        bAllPassed &= test("miSsissippi", "", false);
        bAllPassed &= test("miSsissippi", "", false);
        bAllPassed &= test("abAbac", "", false);
        bAllPassed &= test("abAbac", "", false);
        bAllPassed &= test("aAazz", "", false);
        bAllPassed &= test("A12b12", "", false);
        bAllPassed &= test("a12B12", "", false);
        bAllPassed &= test("oWn", "", false);
        bAllPassed &= test("bLah", "", false);
        bAllPassed &= test("bLah", "", false);
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
