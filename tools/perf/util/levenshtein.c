<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "levenshtein.h"
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

/*
 * This function implements the Damerau-Levenshtein algorithm to
 * calculate a distance between strings.
 *
 * Basically, it says how many letters need to be swapped, substituted,
 * deleted from, or added to string1, at least, to get string2.
 *
 * The idea is to build a distance matrix क्रम the substrings of both
 * strings.  To aव्योम a large space complनिकासy, only the last three rows
 * are kept in memory (अगर swaps had the same or higher cost as one deletion
 * plus one insertion, only two rows would be needed).
 *
 * At any stage, "i + 1" denotes the length of the current substring of
 * string1 that the distance is calculated क्रम.
 *
 * row2 holds the current row, row1 the previous row (i.e. क्रम the substring
 * of string1 of length "i"), and row0 the row beक्रमe that.
 *
 * In other words, at the start of the big loop, row2[j + 1] contains the
 * Damerau-Levenshtein distance between the substring of string1 of length
 * "i" and the substring of string2 of length "j + 1".
 *
 * All the big loop करोes is determine the partial minimum-cost paths.
 *
 * It करोes so by calculating the costs of the path ending in अक्षरacters
 * i (in string1) and j (in string2), respectively, given that the last
 * operation is a substitution, a swap, a deletion, or an insertion.
 *
 * This implementation allows the costs to be weighted:
 *
 * - w (as in "sWap")
 * - s (as in "Substitution")
 * - a (क्रम insertion, AKA "Add")
 * - d (as in "Deletion")
 *
 * Note that this algorithm calculates a distance _अगरf_ d == a.
 */
पूर्णांक levenshtein(स्थिर अक्षर *string1, स्थिर अक्षर *string2,
		पूर्णांक w, पूर्णांक s, पूर्णांक a, पूर्णांक d)
अणु
	पूर्णांक len1 = म_माप(string1), len2 = म_माप(string2);
	पूर्णांक *row0 = दो_स्मृति(माप(पूर्णांक) * (len2 + 1));
	पूर्णांक *row1 = दो_स्मृति(माप(पूर्णांक) * (len2 + 1));
	पूर्णांक *row2 = दो_स्मृति(माप(पूर्णांक) * (len2 + 1));
	पूर्णांक i, j;

	क्रम (j = 0; j <= len2; j++)
		row1[j] = j * a;
	क्रम (i = 0; i < len1; i++) अणु
		पूर्णांक *dummy;

		row2[0] = (i + 1) * d;
		क्रम (j = 0; j < len2; j++) अणु
			/* substitution */
			row2[j + 1] = row1[j] + s * (string1[i] != string2[j]);
			/* swap */
			अगर (i > 0 && j > 0 && string1[i - 1] == string2[j] &&
					string1[i] == string2[j - 1] &&
					row2[j + 1] > row0[j - 1] + w)
				row2[j + 1] = row0[j - 1] + w;
			/* deletion */
			अगर (row2[j + 1] > row1[j + 1] + d)
				row2[j + 1] = row1[j + 1] + d;
			/* insertion */
			अगर (row2[j + 1] > row2[j] + a)
				row2[j + 1] = row2[j] + a;
		पूर्ण

		dummy = row0;
		row0 = row1;
		row1 = row2;
		row2 = dummy;
	पूर्ण

	i = row1[len2];
	मुक्त(row0);
	मुक्त(row1);
	मुक्त(row2);

	वापस i;
पूर्ण
