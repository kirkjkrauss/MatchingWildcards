int testtame(void)
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
		// Case with last character mismatch.
        bAllPassed &= test("abc", "abd", false);

        // Cases with repeating character sequences.
        bAllPassed &= test("abcccd", "abcccd", true);
        bAllPassed &= test("mississipissippi", "mississipissippi", true);
        bAllPassed &= test("xxxxzzzzzzzzyf", "xxxxzzzzzzzzyfffff", false);
        bAllPassed &= test("xxxxzzzzzzzzyf", "xxxxzzzzzzzzyf", true);
        bAllPassed &= test("xxxxzzzzzzzzyf", "xxxxzzy.fffff", false);
        bAllPassed &= test("xxxxzzzzzzzzyf", "xxxxzzzzzzzzyf", true);
        bAllPassed &= test("xyxyxyzyxyz", "xyxyxyzyxyz", true);
        bAllPassed &= test("mississippi", "mississippi", true);
        bAllPassed &= test("xyxyxyxyz", "xyxyxyxyz", true);
        bAllPassed &= test("m ississippi", "m ississippi", true);
        bAllPassed &= test("ababac", "ababac?", false);
        bAllPassed &= test("dababac", "ababac", false);
        bAllPassed &= test("aaazz", "aaazz", true);
        bAllPassed &= test("a12b12", "1212", false);
        bAllPassed &= test("a12b12", "a12b", false);
        bAllPassed &= test("a12b12", "a12b12", true);

        // A mix of cases
        bAllPassed &= test("n", "n", true);
        bAllPassed &= test("aabab", "aabab", true);
        bAllPassed &= test("ar", "ar", true);
        bAllPassed &= test("aar", "aaar", false);
        bAllPassed &= test("XYXYXYZYXYz", "XYXYXYZYXYz", true);
        bAllPassed &= test("missisSIPpi", "missisSIPpi", true);
        bAllPassed &= test("mississipPI", "mississipPI", true);
        bAllPassed &= test("xyxyxyxyz", "xyxyxyxyz", true);
        bAllPassed &= test("miSsissippi", "miSsissippi", true);
        bAllPassed &= test("miSsissippi", "miSsisSippi", false);
        bAllPassed &= test("abAbac", "abAbac", true);
        bAllPassed &= test("abAbac", "abAbac", true);
        bAllPassed &= test("aAazz", "aAazz", true);
        bAllPassed &= test("A12b12", "A12b123", false);
        bAllPassed &= test("a12B12", "a12B12", true);
        bAllPassed &= test("oWn", "oWn", true);
        bAllPassed &= test("bLah", "bLah", true);
        bAllPassed &= test("bLah", "bLaH", false);

        // Single '?' cases.
        bAllPassed &= test("a", "a", true);
        bAllPassed &= test("ab", "a?", true);
        bAllPassed &= test("abc", "ab?", true);

        // Mixed '?' cases.
        bAllPassed &= test("a", "??", false);
        bAllPassed &= test("ab", "??", true);
        bAllPassed &= test("abc", "???", true);
        bAllPassed &= test("abcd", "????", true);
        bAllPassed &= test("abc", "????", false);
        bAllPassed &= test("abcd", "?b??", true);
        bAllPassed &= test("abcd", "?a??", false);
        bAllPassed &= test("abcd", "??c?", true);
        bAllPassed &= test("abcd", "??d?", false);
        bAllPassed &= test("abcde", "?b?d*?", true);

        // Longer string scenarios.
        bAllPassed &= test("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", 
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", true);
        bAllPassed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab", 
            "abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab", true);
        bAllPassed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab", 
            "abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajaxalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab", false);
        bAllPassed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab", 
            "abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaggggagaaaaaaaab", false);
        bAllPassed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab", 
            "abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab", true);
        bAllPassed &= test("aaabbaabbaab", "aaabbaabbaab", true);
        bAllPassed &= test("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", true);
        bAllPassed &= test("aaaaaaaaaaaaaaaaa", 
            "aaaaaaaaaaaaaaaaa", true);
        bAllPassed &= test("aaaaaaaaaaaaaaaa", 
            "aaaaaaaaaaaaaaaaa", false);
        bAllPassed &= test("abcabcdabcdeabcdefabcdefgabcdefghabcdefghia\
bcdefghijabcdefghijkabcdefghijklabcdefghijklmabcdefghijklmn", 
            "abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc", 
			false);
        bAllPassed &= test("abcabcdabcdeabcdefabcdefgabcdefghabcdefghia\
bcdefghijabcdefghijkabcdefghijklabcdefghijklmabcdefghijklmn", 
            "abcabcdabcdeabcdefabcdefgabcdefghabcdefghia\
bcdefghijabcdefghijkabcdefghijklabcdefghijklmabcdefghijklmn", 
			true);
        bAllPassed &= test("abcabcdabcdabcabcd", "abcabc?abcabcabc", 
            false);
        bAllPassed &= test(
            "abcabcdabcdabcabcdabcdabcabcdabcabcabcd", 
            "abcabc?abc?abcabc?abc?abc?bc?abc?bc?bcd", true);
        bAllPassed &= test("?abc?", "?abc?", true);
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
