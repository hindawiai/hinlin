<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_COMPAT_SIGNAL_H
#घोषणा __ASM_COMPAT_SIGNAL_H

#समावेश <linux/bug.h>
#समावेश <linux/compat.h>
#समावेश <linux/compiler.h>

#समावेश <यंत्र/संकेत.स>
#समावेश <यंत्र/siginfo.h>

#समावेश <linux/uaccess.h>

अटल अंतरभूत पूर्णांक __copy_conv_sigset_to_user(compat_sigset_t __user *d,
	स्थिर sigset_t *s)
अणु
	BUILD_BUG_ON(माप(*d) != माप(*s));
	BUILD_BUG_ON(_NSIG_WORDS != 2);

	वापस put_compat_sigset(d, s, माप(*d));
पूर्ण

अटल अंतरभूत पूर्णांक __copy_conv_sigset_from_user(sigset_t *d,
	स्थिर compat_sigset_t __user *s)
अणु
	वापस get_compat_sigset(d, s);
पूर्ण

#पूर्ण_अगर /* __ASM_COMPAT_SIGNAL_H */
