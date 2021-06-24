<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008 David Gibson, IBM Corporation
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 * Copyright (C) 2017 SiFive
 */

#समावेश <linux/console.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/sbi.h>

#समावेश "hvc_console.h"

अटल पूर्णांक hvc_sbi_tty_put(uपूर्णांक32_t vtermno, स्थिर अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		sbi_console_अक्षर_दो(buf[i]);

	वापस i;
पूर्ण

अटल पूर्णांक hvc_sbi_tty_get(uपूर्णांक32_t vtermno, अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक i, c;

	क्रम (i = 0; i < count; i++) अणु
		c = sbi_console_अक्षर_लो();
		अगर (c < 0)
			अवरोध;
		buf[i] = c;
	पूर्ण

	वापस i;
पूर्ण

अटल स्थिर काष्ठा hv_ops hvc_sbi_ops = अणु
	.get_अक्षरs = hvc_sbi_tty_get,
	.put_अक्षरs = hvc_sbi_tty_put,
पूर्ण;

अटल पूर्णांक __init hvc_sbi_init(व्योम)
अणु
	वापस PTR_ERR_OR_ZERO(hvc_alloc(0, 0, &hvc_sbi_ops, 16));
पूर्ण
device_initcall(hvc_sbi_init);

अटल पूर्णांक __init hvc_sbi_console_init(व्योम)
अणु
	hvc_instantiate(0, 0, &hvc_sbi_ops);

	वापस 0;
पूर्ण
console_initcall(hvc_sbi_console_init);
