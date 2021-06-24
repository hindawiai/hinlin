<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * console.c: Routines that deal with sending and receiving IO
 *            to/from the current console device using the PROM.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 1998 Pete Zaitcev <zaitcev@yahoo.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <linux/माला.स>

बाह्य व्योम restore_current(व्योम);

/* Non blocking put अक्षरacter to console device, वापसs -1 अगर
 * unsuccessful.
 */
अटल पूर्णांक prom_nbअक्षर_दो(स्थिर अक्षर *buf)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i = -1;

	spin_lock_irqsave(&prom_lock, flags);
	चयन(prom_vers) अणु
	हाल PROM_V0:
		अगर ((*(romvec->pv_nbअक्षर_दो))(*buf))
			i = 1;
		अवरोध;
	हाल PROM_V2:
	हाल PROM_V3:
		अगर ((*(romvec->pv_v2devops).v2_dev_ग_लिखो)(*romvec->pv_v2bootargs.fd_मानक_निकास,
							  buf, 0x1) == 1)
			i = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);
	वापस i; /* Ugh, we could spin क्रमever on unsupported proms ;( */
पूर्ण

व्योम prom_console_ग_लिखो_buf(स्थिर अक्षर *buf, पूर्णांक len)
अणु
	जबतक (len) अणु
		पूर्णांक n = prom_nbअक्षर_दो(buf);
		अगर (n < 0)
			जारी;
		len--;
		buf++;
	पूर्ण
पूर्ण

