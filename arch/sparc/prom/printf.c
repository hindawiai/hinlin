<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * म_लिखो.c:  Internal prom library म_लिखो facility.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 * Copyright (c) 2002 Pete Zaitcev (zaitcev@yahoo.com)
 *
 * We used to warn all over the code: DO NOT USE prom_म_लिखो(),
 * and yet people करो. Anton's banking code was outputting banks
 * with prom_म_लिखो क्रम most of the 2.4 lअगरeसमय. Since an effective
 * stick is not available, we deployed a carrot: an early prपूर्णांकk
 * through PROM by means of -p boot option. This ought to fix it.
 * USE prपूर्णांकk; अगर you need, deploy -p.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/compiler.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>

#घोषणा CONSOLE_WRITE_BUF_SIZE	1024

अटल अक्षर ppbuf[1024];
अटल अक्षर console_ग_लिखो_buf[CONSOLE_WRITE_BUF_SIZE];
अटल DEFINE_RAW_SPINLOCK(console_ग_लिखो_lock);

व्योम notrace prom_ग_लिखो(स्थिर अक्षर *buf, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक dest_len;
	अचिन्हित दीर्घ flags;
	अक्षर *dest;

	dest = console_ग_लिखो_buf;
	raw_spin_lock_irqsave(&console_ग_लिखो_lock, flags);

	dest_len = 0;
	जबतक (n-- != 0) अणु
		अक्षर ch = *buf++;
		अगर (ch == '\n') अणु
			*dest++ = '\r';
			dest_len++;
		पूर्ण
		*dest++ = ch;
		dest_len++;
		अगर (dest_len >= CONSOLE_WRITE_BUF_SIZE - 1) अणु
			prom_console_ग_लिखो_buf(console_ग_लिखो_buf, dest_len);
			dest = console_ग_लिखो_buf;
			dest_len = 0;
		पूर्ण
	पूर्ण
	अगर (dest_len)
		prom_console_ग_लिखो_buf(console_ग_लिखो_buf, dest_len);

	raw_spin_unlock_irqrestore(&console_ग_लिखो_lock, flags);
पूर्ण

व्योम notrace prom_म_लिखो(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक i;

	बहु_शुरू(args, fmt);
	i = vscnम_लिखो(ppbuf, माप(ppbuf), fmt, args);
	बहु_पूर्ण(args);

	prom_ग_लिखो(ppbuf, i);
पूर्ण
