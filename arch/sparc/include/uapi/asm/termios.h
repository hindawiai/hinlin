<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_SPARC_TERMIOS_H
#घोषणा _UAPI_SPARC_TERMIOS_H

#समावेश <यंत्र/ioctls.h>
#समावेश <यंत्र/termbits.h>

#अगर defined(__KERNEL__) || defined(__DEFINE_BSD_TERMIOS)
काष्ठा sgttyb अणु
	अक्षर	sg_ispeed;
	अक्षर	sg_ospeed;
	अक्षर	sg_erase;
	अक्षर	sg_समाप्त;
	लघु	sg_flags;
पूर्ण;

काष्ठा tअक्षरs अणु
	अक्षर	t_पूर्णांकrc;
	अक्षर	t_quitc;
	अक्षर	t_startc;
	अक्षर	t_stopc;
	अक्षर	t_eofc;
	अक्षर	t_brkc;
पूर्ण;

काष्ठा ltअक्षरs अणु
	अक्षर	t_suspc;
	अक्षर	t_dsuspc;
	अक्षर	t_rprntc;
	अक्षर	t_flushc;
	अक्षर	t_werasc;
	अक्षर	t_lnextc;
पूर्ण;
#पूर्ण_अगर /* __KERNEL__ */

काष्ठा winsize अणु
	अचिन्हित लघु ws_row;
	अचिन्हित लघु ws_col;
	अचिन्हित लघु ws_xpixel;
	अचिन्हित लघु ws_ypixel;
पूर्ण;


#पूर्ण_अगर /* _UAPI_SPARC_TERMIOS_H */
