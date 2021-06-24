<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007-2008 rPath, Inc. - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * arch/x86/boot/cpu.c
 *
 * Check क्रम obligatory CPU features and पात अगर the features are not
 * present.
 */

#समावेश "boot.h"
#अगर_घोषित CONFIG_X86_FEATURE_NAMES
#समावेश "cpustr.h"
#पूर्ण_अगर

अटल अक्षर *cpu_name(पूर्णांक level)
अणु
	अटल अक्षर buf[6];

	अगर (level == 64) अणु
		वापस "x86-64";
	पूर्ण अन्यथा अणु
		अगर (level == 15)
			level = 6;
		प्र_लिखो(buf, "i%d86", level);
		वापस buf;
	पूर्ण
पूर्ण

अटल व्योम show_cap_strs(u32 *err_flags)
अणु
	पूर्णांक i, j;
#अगर_घोषित CONFIG_X86_FEATURE_NAMES
	स्थिर अचिन्हित अक्षर *msg_strs = (स्थिर अचिन्हित अक्षर *)x86_cap_strs;
	क्रम (i = 0; i < NCAPINTS; i++) अणु
		u32 e = err_flags[i];
		क्रम (j = 0; j < 32; j++) अणु
			अगर (msg_strs[0] < i ||
			    (msg_strs[0] == i && msg_strs[1] < j)) अणु
				/* Skip to the next string */
				msg_strs += 2;
				जबतक (*msg_strs++)
					;
			पूर्ण
			अगर (e & 1) अणु
				अगर (msg_strs[0] == i &&
				    msg_strs[1] == j &&
				    msg_strs[2])
					म_लिखो("%s ", msg_strs+2);
				अन्यथा
					म_लिखो("%d:%d ", i, j);
			पूर्ण
			e >>= 1;
		पूर्ण
	पूर्ण
#अन्यथा
	क्रम (i = 0; i < NCAPINTS; i++) अणु
		u32 e = err_flags[i];
		क्रम (j = 0; j < 32; j++) अणु
			अगर (e & 1)
				म_लिखो("%d:%d ", i, j);
			e >>= 1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

पूर्णांक validate_cpu(व्योम)
अणु
	u32 *err_flags;
	पूर्णांक cpu_level, req_level;

	check_cpu(&cpu_level, &req_level, &err_flags);

	अगर (cpu_level < req_level) अणु
		म_लिखो("This kernel requires an %s CPU, ",
		       cpu_name(req_level));
		म_लिखो("but only detected an %s CPU.\n",
		       cpu_name(cpu_level));
		वापस -1;
	पूर्ण

	अगर (err_flags) अणु
		माला_दो("This kernel requires the following features "
		     "not present on the CPU:\n");
		show_cap_strs(err_flags);
		अक्षर_दो('\n');
		वापस -1;
	पूर्ण अन्यथा अगर (check_knl_erratum()) अणु
		वापस -1;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण
