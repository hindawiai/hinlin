<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 1996, 2000, 2001 by Ralf Baechle
 * Copyright (C) 2000, 2001 Silicon Graphics, Inc.
 */
#अगर_अघोषित _UAPI_ASM_TERMIOS_H
#घोषणा _UAPI_ASM_TERMIOS_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/termbits.h>
#समावेश <यंत्र/ioctls.h>

काष्ठा sgttyb अणु
	अक्षर	sg_ispeed;
	अक्षर	sg_ospeed;
	अक्षर	sg_erase;
	अक्षर	sg_समाप्त;
	पूर्णांक	sg_flags;	/* SGI special - पूर्णांक, not लघु */
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
	अक्षर	t_suspc;	/* stop process संकेत */
	अक्षर	t_dsuspc;	/* delayed stop process संकेत */
	अक्षर	t_rprntc;	/* reprपूर्णांक line */
	अक्षर	t_flushc;	/* flush output (toggles) */
	अक्षर	t_werasc;	/* word erase */
	अक्षर	t_lnextc;	/* literal next अक्षरacter */
पूर्ण;

/* TIOCGSIZE, TIOCSSIZE not defined yet.  Only needed क्रम SunOS source
   compatibility anyway ... */

काष्ठा winsize अणु
	अचिन्हित लघु ws_row;
	अचिन्हित लघु ws_col;
	अचिन्हित लघु ws_xpixel;
	अचिन्हित लघु ws_ypixel;
पूर्ण;

#घोषणा NCC	8
काष्ठा termio अणु
	अचिन्हित लघु c_अगरlag;		/* input mode flags */
	अचिन्हित लघु c_oflag;		/* output mode flags */
	अचिन्हित लघु c_cflag;		/* control mode flags */
	अचिन्हित लघु c_lflag;		/* local mode flags */
	अक्षर c_line;			/* line discipline */
	अचिन्हित अक्षर c_cc[NCCS];	/* control अक्षरacters */
पूर्ण;


/* modem lines */
#घोषणा TIOCM_LE	0x001		/* line enable */
#घोषणा TIOCM_DTR	0x002		/* data terminal पढ़ोy */
#घोषणा TIOCM_RTS	0x004		/* request to send */
#घोषणा TIOCM_ST	0x010		/* secondary transmit */
#घोषणा TIOCM_SR	0x020		/* secondary receive */
#घोषणा TIOCM_CTS	0x040		/* clear to send */
#घोषणा TIOCM_CAR	0x100		/* carrier detect */
#घोषणा TIOCM_CD	TIOCM_CAR
#घोषणा TIOCM_RNG	0x200		/* ring */
#घोषणा TIOCM_RI	TIOCM_RNG
#घोषणा TIOCM_DSR	0x400		/* data set पढ़ोy */
#घोषणा TIOCM_OUT1	0x2000
#घोषणा TIOCM_OUT2	0x4000
#घोषणा TIOCM_LOOP	0x8000


#पूर्ण_अगर /* _UAPI_ASM_TERMIOS_H */
