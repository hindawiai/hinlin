<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * IBM RTAS driver पूर्णांकerface to hvc_console.c
 *
 * (C) Copyright IBM Corporation 2001-2005
 * (C) Copyright Red Hat, Inc. 2005
 *
 * Author(s): Maximino Augilar <IBM STI Design Center>
 *	    : Ryan S. Arnold <rsa@us.ibm.com>
 *	    : Utz Bacher <utz.bacher@de.ibm.com>
 *	    : David Woodhouse <dwmw2@infradead.org>
 *
 *    inspired by drivers/अक्षर/hvc_console.c
 *    written by Anton Blanअक्षरd and Paul Mackerras
 */

#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/rtas.h>
#समावेश "hvc_console.h"

#घोषणा hvc_rtas_cookie 0x67781e15
काष्ठा hvc_काष्ठा *hvc_rtas_dev;

अटल पूर्णांक rtascons_put_अक्षर_token = RTAS_UNKNOWN_SERVICE;
अटल पूर्णांक rtascons_get_अक्षर_token = RTAS_UNKNOWN_SERVICE;

अटल अंतरभूत पूर्णांक hvc_rtas_ग_लिखो_console(uपूर्णांक32_t vtermno, स्थिर अक्षर *buf,
		पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		अगर (rtas_call(rtascons_put_अक्षर_token, 1, 1, शून्य, buf[i]))
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक hvc_rtas_पढ़ो_console(uपूर्णांक32_t vtermno, अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक i, c;

	क्रम (i = 0; i < count; i++) अणु
		अगर (rtas_call(rtascons_get_अक्षर_token, 0, 2, &c))
			अवरोध;

		buf[i] = c;
	पूर्ण

	वापस i;
पूर्ण

अटल स्थिर काष्ठा hv_ops hvc_rtas_get_put_ops = अणु
	.get_अक्षरs = hvc_rtas_पढ़ो_console,
	.put_अक्षरs = hvc_rtas_ग_लिखो_console,
पूर्ण;

अटल पूर्णांक __init hvc_rtas_init(व्योम)
अणु
	काष्ठा hvc_काष्ठा *hp;

	अगर (rtascons_put_अक्षर_token == RTAS_UNKNOWN_SERVICE)
		rtascons_put_अक्षर_token = rtas_token("put-term-char");
	अगर (rtascons_put_अक्षर_token == RTAS_UNKNOWN_SERVICE)
		वापस -EIO;

	अगर (rtascons_get_अक्षर_token == RTAS_UNKNOWN_SERVICE)
		rtascons_get_अक्षर_token = rtas_token("get-term-char");
	अगर (rtascons_get_अक्षर_token == RTAS_UNKNOWN_SERVICE)
		वापस -EIO;

	BUG_ON(hvc_rtas_dev);

	/* Allocate an hvc_काष्ठा क्रम the console device we instantiated
	 * earlier.  Save off hp so that we can वापस it on निकास */
	hp = hvc_alloc(hvc_rtas_cookie, 0, &hvc_rtas_get_put_ops, 16);
	अगर (IS_ERR(hp))
		वापस PTR_ERR(hp);

	hvc_rtas_dev = hp;

	वापस 0;
पूर्ण
device_initcall(hvc_rtas_init);

/* This will happen prior to module init.  There is no tty at this समय? */
अटल पूर्णांक __init hvc_rtas_console_init(व्योम)
अणु
	rtascons_put_अक्षर_token = rtas_token("put-term-char");
	अगर (rtascons_put_अक्षर_token == RTAS_UNKNOWN_SERVICE)
		वापस -EIO;

	rtascons_get_अक्षर_token = rtas_token("get-term-char");
	अगर (rtascons_get_अक्षर_token == RTAS_UNKNOWN_SERVICE)
		वापस -EIO;

	hvc_instantiate(hvc_rtas_cookie, 0, &hvc_rtas_get_put_ops);
	add_preferred_console("hvc", 0, शून्य);

	वापस 0;
पूर्ण
console_initcall(hvc_rtas_console_init);
