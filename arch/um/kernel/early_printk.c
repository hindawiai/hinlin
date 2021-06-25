<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Riअक्षरd Weinberger <richrd@nod.at>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <os.h>

अटल व्योम early_console_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित पूर्णांक n)
अणु
	um_early_prपूर्णांकk(s, n);
पूर्ण

अटल काष्ठा console early_console_dev = अणु
	.name = "earlycon",
	.ग_लिखो = early_console_ग_लिखो,
	.flags = CON_BOOT,
	.index = -1,
पूर्ण;

अटल पूर्णांक __init setup_early_prपूर्णांकk(अक्षर *buf)
अणु
	अगर (!early_console) अणु
		early_console = &early_console_dev;
		रेजिस्टर_console(&early_console_dev);
	पूर्ण
	वापस 0;
पूर्ण

early_param("earlyprintk", setup_early_prपूर्णांकk);
