<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* -*- linux-c -*-
 *
 *	$Id: sysrq.h,v 1.3 1997/07/17 11:54:33 mj Exp $
 *
 *	Linux Magic System Request Key Hacks
 *
 *	(c) 1997 Martin Mares <mj@atrey.karlin.mff.cuni.cz>
 *
 *	(c) 2000 Crutcher Dunnavant <crutcher+kernel@datastacks.com>
 *	overhauled to use key registration
 *	based upon discusions in irc://irc.खोलोprojects.net/#kernelnewbies
 */

#अगर_अघोषित _LINUX_SYSRQ_H
#घोषणा _LINUX_SYSRQ_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>

/* Possible values of biपंचांगask क्रम enabling sysrq functions */
/* 0x0001 is reserved क्रम enable everything */
#घोषणा SYSRQ_ENABLE_LOG	0x0002
#घोषणा SYSRQ_ENABLE_KEYBOARD	0x0004
#घोषणा SYSRQ_ENABLE_DUMP	0x0008
#घोषणा SYSRQ_ENABLE_SYNC	0x0010
#घोषणा SYSRQ_ENABLE_REMOUNT	0x0020
#घोषणा SYSRQ_ENABLE_SIGNAL	0x0040
#घोषणा SYSRQ_ENABLE_BOOT	0x0080
#घोषणा SYSRQ_ENABLE_RTNICE	0x0100

काष्ठा sysrq_key_op अणु
	व्योम (* स्थिर handler)(पूर्णांक);
	स्थिर अक्षर * स्थिर help_msg;
	स्थिर अक्षर * स्थिर action_msg;
	स्थिर पूर्णांक enable_mask;
पूर्ण;

#अगर_घोषित CONFIG_MAGIC_SYSRQ

/* Generic SysRq पूर्णांकerface -- you may call it from any device driver, supplying
 * ASCII code of the key, poपूर्णांकer to रेजिस्टरs and kbd/tty काष्ठाs (अगर they
 * are available -- अन्यथा शून्य's).
 */

व्योम handle_sysrq(पूर्णांक key);
व्योम __handle_sysrq(पूर्णांक key, bool check_mask);
पूर्णांक रेजिस्टर_sysrq_key(पूर्णांक key, स्थिर काष्ठा sysrq_key_op *op);
पूर्णांक unरेजिस्टर_sysrq_key(पूर्णांक key, स्थिर काष्ठा sysrq_key_op *op);
बाह्य स्थिर काष्ठा sysrq_key_op *__sysrq_reboot_op;

पूर्णांक sysrq_toggle_support(पूर्णांक enable_mask);
पूर्णांक sysrq_mask(व्योम);

#अन्यथा

अटल अंतरभूत व्योम handle_sysrq(पूर्णांक key)
अणु
पूर्ण

अटल अंतरभूत व्योम __handle_sysrq(पूर्णांक key, bool check_mask)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक रेजिस्टर_sysrq_key(पूर्णांक key, स्थिर काष्ठा sysrq_key_op *op)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक unरेजिस्टर_sysrq_key(पूर्णांक key, स्थिर काष्ठा sysrq_key_op *op)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक sysrq_mask(व्योम)
अणु
	/* Magic SysRq disabled mask */
	वापस 0;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SYSRQ_H */
