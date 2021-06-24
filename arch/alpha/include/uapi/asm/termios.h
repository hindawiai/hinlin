<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ALPHA_TERMIOS_H
#घोषणा _UAPI_ALPHA_TERMIOS_H

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

#घोषणा NCC 8
काष्ठा termio अणु
	अचिन्हित लघु c_अगरlag;		/* input mode flags */
	अचिन्हित लघु c_oflag;		/* output mode flags */
	अचिन्हित लघु c_cflag;		/* control mode flags */
	अचिन्हित लघु c_lflag;		/* local mode flags */
	अचिन्हित अक्षर c_line;		/* line discipline */
	अचिन्हित अक्षर c_cc[NCC];	/* control अक्षरacters */
पूर्ण;

/*
 * c_cc अक्षरacters in the termio काष्ठाure.  Oh, how I love being
 * backwardly compatible.  Notice that अक्षरacter 4 and 5 are
 * पूर्णांकerpreted dअगरferently depending on whether ICANON is set in
 * c_lflag.  If it's set, they are used as _Vखातापूर्ण and _VEOL, otherwise
 * as _VMIN and V_TIME.  This is क्रम compatibility with OSF/1 (which
 * is compatible with sysV)...
 */
#घोषणा _VINTR	0
#घोषणा _VQUIT	1
#घोषणा _VERASE	2
#घोषणा _VKILL	3
#घोषणा _Vखातापूर्ण	4
#घोषणा _VMIN	4
#घोषणा _VEOL	5
#घोषणा _VTIME	5
#घोषणा _VEOL2	6
#घोषणा _VSWTC	7


#पूर्ण_अगर /* _UAPI_ALPHA_TERMIOS_H */
