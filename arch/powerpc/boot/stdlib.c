<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * stdlib functions
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश "stdlib.h"

/* Not currently supported: leading whitespace, sign, 0x prefix, zero base */
अचिन्हित दीर्घ दीर्घ पूर्णांक म_से_अदीर्घl(स्थिर अक्षर *ptr, अक्षर **end, पूर्णांक base)
अणु
	अचिन्हित दीर्घ दीर्घ ret = 0;

	अगर (base > 36)
		जाओ out;

	जबतक (*ptr) अणु
		पूर्णांक digit;

		अगर (*ptr >= '0' && *ptr <= '9' && *ptr < '0' + base)
			digit = *ptr - '0';
		अन्यथा अगर (*ptr >= 'A' && *ptr < 'A' + base - 10)
			digit = *ptr - 'A' + 10;
		अन्यथा अगर (*ptr >= 'a' && *ptr < 'a' + base - 10)
			digit = *ptr - 'a' + 10;
		अन्यथा
			अवरोध;

		ret *= base;
		ret += digit;
		ptr++;
	पूर्ण

out:
	अगर (end)
		*end = (अक्षर *)ptr;

	वापस ret;
पूर्ण
