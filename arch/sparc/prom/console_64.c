<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* console.c: Routines that deal with sending and receiving IO
 *            to/from the current console device using the PROM.
 *
 * Copyright (C) 1995 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1996,1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <linux/माला.स>

अटल पूर्णांक __prom_console_ग_लिखो_buf(स्थिर अक्षर *buf, पूर्णांक len)
अणु
	अचिन्हित दीर्घ args[7];
	पूर्णांक ret;

	args[0] = (अचिन्हित दीर्घ) "write";
	args[1] = 3;
	args[2] = 1;
	args[3] = (अचिन्हित पूर्णांक) prom_मानक_निकास;
	args[4] = (अचिन्हित दीर्घ) buf;
	args[5] = (अचिन्हित पूर्णांक) len;
	args[6] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);

	ret = (पूर्णांक) args[6];
	अगर (ret < 0)
		वापस -1;
	वापस ret;
पूर्ण

व्योम prom_console_ग_लिखो_buf(स्थिर अक्षर *buf, पूर्णांक len)
अणु
	जबतक (len) अणु
		पूर्णांक n = __prom_console_ग_लिखो_buf(buf, len);
		अगर (n < 0)
			जारी;
		len -= n;
		buf += len;
	पूर्ण
पूर्ण
