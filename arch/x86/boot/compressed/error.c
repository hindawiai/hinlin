<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Callers outside of misc.c need access to the error reporting routines,
 * but the *_माला_दोtr() functions need to stay in misc.c because of how
 * स_नकल() and स_हटाओ() are defined क्रम the compressed boot environment.
 */
#समावेश "misc.h"
#समावेश "error.h"

व्योम warn(अक्षर *m)
अणु
	error_माला_दोtr("\n\n");
	error_माला_दोtr(m);
	error_माला_दोtr("\n\n");
पूर्ण

व्योम error(अक्षर *m)
अणु
	warn(m);
	error_माला_दोtr(" -- System halted");

	जबतक (1)
		यंत्र("hlt");
पूर्ण
