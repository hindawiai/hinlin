<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2008 rPath, Inc. - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * This is a host program to preprocess the CPU strings पूर्णांकo a
 * compact क्रमmat suitable क्रम the setup code.
 */

#समावेश <मानकपन.स>

#समावेश "../include/asm/required-features.h"
#समावेश "../include/asm/disabled-features.h"
#समावेश "../include/asm/cpufeatures.h"
#समावेश "../include/asm/vmxfeatures.h"
#समावेश "../kernel/cpu/capflags.c"

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक i, j;
	स्थिर अक्षर *str;

	म_लिखो("static const char x86_cap_strs[] =\n");

	क्रम (i = 0; i < NCAPINTS; i++) अणु
		क्रम (j = 0; j < 32; j++) अणु
			str = x86_cap_flags[i*32+j];

			अगर (i == NCAPINTS-1 && j == 31) अणु
				/* The last entry must be unconditional; this
				   also consumes the compiler-added null
				   अक्षरacter */
				अगर (!str)
					str = "";
				म_लिखो("\t\"\\x%02x\\x%02x\"\"%s\"\n",
				       i, j, str);
			पूर्ण अन्यथा अगर (str) अणु
				म_लिखो("#if REQUIRED_MASK%d & (1 << %d)\n"
				       "\t\"\\x%02x\\x%02x\"\"%s\\0\"\n"
				       "#endif\n",
				       i, j, i, j, str);
			पूर्ण
		पूर्ण
	पूर्ण
	म_लिखो("\t;\n");
	वापस 0;
पूर्ण
