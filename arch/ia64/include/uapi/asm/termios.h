<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Modअगरied 1999
 *	David Mosberger-Tang <davidm@hpl.hp.com>, Hewlett-Packard Co
 *
 * 99/01/28	Added N_IRDA and N_SMSBLOCK
 */
#अगर_अघोषित _UAPI_ASM_IA64_TERMIOS_H
#घोषणा _UAPI_ASM_IA64_TERMIOS_H


#समावेश <यंत्र/termbits.h>
#समावेश <यंत्र/ioctls.h>

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

/* modem lines */
#घोषणा TIOCM_LE	0x001
#घोषणा TIOCM_DTR	0x002
#घोषणा TIOCM_RTS	0x004
#घोषणा TIOCM_ST	0x008
#घोषणा TIOCM_SR	0x010
#घोषणा TIOCM_CTS	0x020
#घोषणा TIOCM_CAR	0x040
#घोषणा TIOCM_RNG	0x080
#घोषणा TIOCM_DSR	0x100
#घोषणा TIOCM_CD	TIOCM_CAR
#घोषणा TIOCM_RI	TIOCM_RNG
#घोषणा TIOCM_OUT1	0x2000
#घोषणा TIOCM_OUT2	0x4000
#घोषणा TIOCM_LOOP	0x8000

/* ioctl (fd, TIOCSERGETLSR, &result) where result may be as below */


#पूर्ण_अगर /* _UAPI_ASM_IA64_TERMIOS_H */
