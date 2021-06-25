<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * cmdline.c: Kernel command line creation using ARCS argc/argv.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 */
#समावेश <linux/bug.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/bootinfo.h>

#अघोषित DEBUG_CMDLINE

/*
 * A 32-bit ARC PROM pass arguments and environment as 32-bit poपूर्णांकer.
 * These macro take care of sign extension.
 */
#घोषणा prom_argv(index) ((अक्षर *) (दीर्घ)argv[(index)])

अटल अक्षर *ignored[] = अणु
	"ConsoleIn=",
	"ConsoleOut=",
	"SystemPartition=",
	"OSLoader=",
	"OSLoadPartition=",
	"OSLoadFilename=",
	"OSLoadOptions="
पूर्ण;

अटल अक्षर *used_arc[][2] = अणु
	अणु "OSLoadPartition=", "root=" पूर्ण,
	अणु "OSLoadOptions=", "" पूर्ण
पूर्ण;

अटल अक्षर __init *move_firmware_args(पूर्णांक argc, LONG *argv, अक्षर *cp)
अणु
	अक्षर *s;
	पूर्णांक actr, i;

	actr = 1; /* Always ignore argv[0] */

	जबतक (actr < argc) अणु
		क्रम(i = 0; i < ARRAY_SIZE(used_arc); i++) अणु
			पूर्णांक len = म_माप(used_arc[i][0]);

			अगर (!म_भेदन(prom_argv(actr), used_arc[i][0], len)) अणु
			/* Ok, we want it. First append the replacement... */
				म_जोड़ो(cp, used_arc[i][1]);
				cp += म_माप(used_arc[i][1]);
				/* ... and now the argument */
				s = म_अक्षर(prom_argv(actr), '=');
				अगर (s) अणु
					s++;
					म_नकल(cp, s);
					cp += म_माप(s);
				पूर्ण
				*cp++ = ' ';
				अवरोध;
			पूर्ण
		पूर्ण
		actr++;
	पूर्ण

	वापस cp;
पूर्ण

व्योम __init prom_init_cmdline(पूर्णांक argc, LONG *argv)
अणु
	अक्षर *cp;
	पूर्णांक actr, i;

	actr = 1; /* Always ignore argv[0] */

	cp = arcs_cmdline;
	/*
	 * Move ARC variables to the beginning to make sure they can be
	 * overridden by later arguments.
	 */
	cp = move_firmware_args(argc, argv, cp);

	जबतक (actr < argc) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ignored); i++) अणु
			पूर्णांक len = म_माप(ignored[i]);

			अगर (!म_भेदन(prom_argv(actr), ignored[i], len))
				जाओ pic_cont;
		पूर्ण
		/* Ok, we want it. */
		म_नकल(cp, prom_argv(actr));
		cp += म_माप(prom_argv(actr));
		*cp++ = ' ';

	pic_cont:
		actr++;
	पूर्ण

	अगर (cp != arcs_cmdline)		/* get rid of trailing space */
		--cp;
	*cp = '\0';

#अगर_घोषित DEBUG_CMDLINE
	prपूर्णांकk(KERN_DEBUG "prom cmdline: %s\n", arcs_cmdline);
#पूर्ण_अगर
पूर्ण
