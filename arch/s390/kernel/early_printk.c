<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2017
 */

#समावेश <linux/console.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/sclp.h>

अटल व्योम sclp_early_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित पूर्णांक len)
अणु
	__sclp_early_prपूर्णांकk(s, len);
पूर्ण

अटल काष्ठा console sclp_early_console = अणु
	.name  = "earlysclp",
	.ग_लिखो = sclp_early_ग_लिखो,
	.flags = CON_PRINTBUFFER | CON_BOOT,
	.index = -1,
पूर्ण;

अटल पूर्णांक __init setup_early_prपूर्णांकk(अक्षर *buf)
अणु
	अगर (early_console)
		वापस 0;
	/* Accept only "earlyprintk" and "earlyprintk=sclp" */
	अगर (buf && !str_has_prefix(buf, "sclp"))
		वापस 0;
	अगर (!sclp.has_linemode && !sclp.has_vt220)
		वापस 0;
	early_console = &sclp_early_console;
	रेजिस्टर_console(early_console);
	वापस 0;
पूर्ण
early_param("earlyprintk", setup_early_prपूर्णांकk);
