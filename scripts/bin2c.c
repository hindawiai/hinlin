<शैली गुरु>
/*
 * Unloved program to convert a binary on मानक_निवेश to a C include on मानक_निकास
 *
 * Jan 1999 Matt Mackall <mpm@selenic.com>
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 */

#समावेश <मानकपन.स>

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक ch, total = 0;

	अगर (argc > 1)
		म_लिखो("const char %s[] %s=\n",
			argv[1], argc > 2 ? argv[2] : "");

	करो अणु
		म_लिखो("\t\"");
		जबतक ((ch = अक्षर_लो()) != खातापूर्ण) अणु
			total++;
			म_लिखो("\\x%02x", ch);
			अगर (total % 16 == 0)
				अवरोध;
		पूर्ण
		म_लिखो("\"\n");
	पूर्ण जबतक (ch != खातापूर्ण);

	अगर (argc > 1)
		म_लिखो("\t;\n\n#include <linux/types.h>\n\nconst size_t %s_size = %d;\n",
		       argv[1], total);

	वापस 0;
पूर्ण
