<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * usage.c
 *
 * Various reporting routines.
 * Originally copied from GIT source.
 *
 * Copyright (C) Linus Torvalds, 2005
 */
#समावेश "util.h"
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <linux/compiler.h>

अटल __noवापस व्योम usage_builtin(स्थिर अक्षर *err)
अणु
	ख_लिखो(मानक_त्रुटि, "\n Usage: %s\n", err);
	निकास(129);
पूर्ण

/* If we are in a dlखोलो()ed .so ग_लिखो to a global variable would segfault
 * (ugh), so keep things अटल. */
अटल व्योम (*usage_routine)(स्थिर अक्षर *err) __noवापस = usage_builtin;

व्योम usage(स्थिर अक्षर *err)
अणु
	usage_routine(err);
पूर्ण
