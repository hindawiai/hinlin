<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _COMPAT_SIGNAL_H
#घोषणा _COMPAT_SIGNAL_H

#समावेश <linux/compat.h>
#समावेश <यंत्र/संकेत.स>

#अगर_घोषित CONFIG_COMPAT
काष्ठा __new_sigaction32 अणु
	अचिन्हित पूर्णांक		sa_handler;
	अचिन्हित पूर्णांक    	sa_flags;
	अचिन्हित पूर्णांक		sa_restorer;     /* not used by Linux/SPARC yet */
	compat_sigset_t 	sa_mask;
पूर्ण;

काष्ठा __old_sigaction32 अणु
	अचिन्हित पूर्णांक		sa_handler;
	compat_old_sigset_t  	sa_mask;
	अचिन्हित पूर्णांक    	sa_flags;
	अचिन्हित पूर्णांक		sa_restorer;     /* not used by Linux/SPARC yet */
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* !(_COMPAT_SIGNAL_H) */
