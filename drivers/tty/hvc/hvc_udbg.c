<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * udbg पूर्णांकerface to hvc_console.c
 *
 * (C) Copyright David Gibson, IBM Corporation 2008.
 */

#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/udbg.h>

#समावेश "hvc_console.h"

अटल काष्ठा hvc_काष्ठा *hvc_udbg_dev;

अटल पूर्णांक hvc_udbg_put(uपूर्णांक32_t vtermno, स्थिर अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count && udbg_अ_दो; i++)
		udbg_अ_दो(buf[i]);

	वापस i;
पूर्ण

अटल पूर्णांक hvc_udbg_get(uपूर्णांक32_t vtermno, अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक i, c;

	अगर (!udbg_अ_लो_poll)
		वापस 0;

	क्रम (i = 0; i < count; i++) अणु
		अगर ((c = udbg_अ_लो_poll()) == -1)
			अवरोध;
		buf[i] = c;
	पूर्ण

	वापस i;
पूर्ण

अटल स्थिर काष्ठा hv_ops hvc_udbg_ops = अणु
	.get_अक्षरs = hvc_udbg_get,
	.put_अक्षरs = hvc_udbg_put,
पूर्ण;

अटल पूर्णांक __init hvc_udbg_init(व्योम)
अणु
	काष्ठा hvc_काष्ठा *hp;

	अगर (!udbg_अ_दो)
		वापस -ENODEV;

	BUG_ON(hvc_udbg_dev);

	hp = hvc_alloc(0, 0, &hvc_udbg_ops, 16);
	अगर (IS_ERR(hp))
		वापस PTR_ERR(hp);

	hvc_udbg_dev = hp;

	वापस 0;
पूर्ण
device_initcall(hvc_udbg_init);

अटल पूर्णांक __init hvc_udbg_console_init(व्योम)
अणु
	अगर (!udbg_अ_दो)
		वापस -ENODEV;

	hvc_instantiate(0, 0, &hvc_udbg_ops);
	add_preferred_console("hvc", 0, शून्य);

	वापस 0;
पूर्ण
console_initcall(hvc_udbg_console_init);
