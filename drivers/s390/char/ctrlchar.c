<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Unअगरied handling of special अक्षरs.
 *
 *    Copyright IBM Corp. 2001
 *    Author(s): Fritz Elfert <felfert@millenux.com> <elfert@de.ibm.com>
 *
 */

#समावेश <linux/मानकघोष.स>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <linux/sysrq.h>
#समावेश <linux/प्रकार.स>

#समावेश "ctrlchar.h"

#अगर_घोषित CONFIG_MAGIC_SYSRQ
अटल काष्ठा sysrq_work ctrlअक्षर_sysrq;

अटल व्योम
ctrlअक्षर_handle_sysrq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sysrq_work *sysrq = container_of(work, काष्ठा sysrq_work, work);

	handle_sysrq(sysrq->key);
पूर्ण

व्योम schedule_sysrq_work(काष्ठा sysrq_work *sw)
अणु
	INIT_WORK(&sw->work, ctrlअक्षर_handle_sysrq);
	schedule_work(&sw->work);
पूर्ण
#पूर्ण_अगर


/**
 * Check क्रम special अक्षरs at start of input.
 *
 * @param buf Console input buffer.
 * @param len Length of valid data in buffer.
 * @param tty The tty काष्ठा क्रम this console.
 * @वापस CTRLCHAR_NONE, अगर nothing matched,
 *         CTRLCHAR_SYSRQ, अगर sysrq was encountered
 *         otherwise अक्षर to be inserted logically or'ed
 *         with CTRLCHAR_CTRL
 */
अचिन्हित पूर्णांक
ctrlअक्षर_handle(स्थिर अचिन्हित अक्षर *buf, पूर्णांक len, काष्ठा tty_काष्ठा *tty)
अणु
	अगर ((len < 2) || (len > 3))
		वापस CTRLCHAR_NONE;

	/* hat is 0xb1 in codepage 037 (US etc.) and thus */
	/* converted to 0x5e in ascii ('^') */
	अगर ((buf[0] != '^') && (buf[0] != '\252'))
		वापस CTRLCHAR_NONE;

#अगर_घोषित CONFIG_MAGIC_SYSRQ
	/* racy */
	अगर (len == 3 && buf[1] == '-') अणु
		ctrlअक्षर_sysrq.key = buf[2];
		schedule_sysrq_work(&ctrlअक्षर_sysrq);
		वापस CTRLCHAR_SYSRQ;
	पूर्ण
#पूर्ण_अगर

	अगर (len != 2)
		वापस CTRLCHAR_NONE;

	चयन (छोटे(buf[1])) अणु
	हाल 'c':
		वापस INTR_CHAR(tty) | CTRLCHAR_CTRL;
	हाल 'd':
		वापस खातापूर्ण_CHAR(tty)  | CTRLCHAR_CTRL;
	हाल 'z':
		वापस SUSP_CHAR(tty) | CTRLCHAR_CTRL;
	पूर्ण
	वापस CTRLCHAR_NONE;
पूर्ण
