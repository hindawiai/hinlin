<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Liberally adapted from alpha/termios.h.  In particular, the c_cc[]
 * fields have been reordered so that termio & termios share the
 * common subset in the same order (क्रम brain dead programs that करोn't
 * know or care about the dअगरferences).
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _UAPI_ASM_POWERPC_TERMIOS_H
#घोषणा _UAPI_ASM_POWERPC_TERMIOS_H


#समावेश <यंत्र/ioctls.h>
#समावेश <यंत्र/termbits.h>

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

काष्ठा winsize अणु
	अचिन्हित लघु ws_row;
	अचिन्हित लघु ws_col;
	अचिन्हित लघु ws_xpixel;
	अचिन्हित लघु ws_ypixel;
पूर्ण;

#घोषणा NCC 10
काष्ठा termio अणु
	अचिन्हित लघु c_अगरlag;		/* input mode flags */
	अचिन्हित लघु c_oflag;		/* output mode flags */
	अचिन्हित लघु c_cflag;		/* control mode flags */
	अचिन्हित लघु c_lflag;		/* local mode flags */
	अचिन्हित अक्षर c_line;		/* line discipline */
	अचिन्हित अक्षर c_cc[NCC];	/* control अक्षरacters */
पूर्ण;

/* c_cc अक्षरacters */
#घोषणा _VINTR	0
#घोषणा _VQUIT	1
#घोषणा _VERASE	2
#घोषणा _VKILL	3
#घोषणा _Vखातापूर्ण	4
#घोषणा _VMIN	5
#घोषणा _VEOL	6
#घोषणा _VTIME	7
#घोषणा _VEOL2	8
#घोषणा _VSWTC	9



#पूर्ण_अगर /* _UAPI_ASM_POWERPC_TERMIOS_H */
