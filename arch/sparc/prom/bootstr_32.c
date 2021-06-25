<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bootstr.c:  Boot string/argument acquisition from the PROM.
 *
 * Copyright(C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#समावेश <linux/माला.स>
#समावेश <यंत्र/oplib.h>
#समावेश <linux/init.h>

#घोषणा BARG_LEN  256
अटल अक्षर barg_buf[BARG_LEN] = अणु 0 पूर्ण;
अटल अक्षर fetched __initdata = 0;

अक्षर * __init
prom_getbootargs(व्योम)
अणु
	पूर्णांक iter;
	अक्षर *cp, *arg;

	/* This check saves us from a panic when bootfd patches args. */
	अगर (fetched) अणु
		वापस barg_buf;
	पूर्ण

	चयन (prom_vers) अणु
	हाल PROM_V0:
		cp = barg_buf;
		/* Start from 1 and go over fd(0,0,0)kernel */
		क्रम (iter = 1; iter < 8; iter++) अणु
			arg = (*(romvec->pv_v0bootargs))->argv[iter];
			अगर (arg == शून्य)
				अवरोध;
			जबतक (*arg != 0) अणु
				/* Leave place क्रम space and null. */
				अगर (cp >= barg_buf + BARG_LEN - 2)
					/* We might issue a warning here. */
					अवरोध;
				*cp++ = *arg++;
			पूर्ण
			*cp++ = ' ';
			अगर (cp >= barg_buf + BARG_LEN - 1)
				/* We might issue a warning here. */
				अवरोध;
		पूर्ण
		*cp = 0;
		अवरोध;
	हाल PROM_V2:
	हाल PROM_V3:
		/*
		 * V3 PROM cannot supply as with more than 128 bytes
		 * of an argument. But a smart bootstrap loader can.
		 */
		strlcpy(barg_buf, *romvec->pv_v2bootargs.bootargs, माप(barg_buf));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	fetched = 1;
	वापस barg_buf;
पूर्ण
