<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * include/यंत्र-xtensa/termbits.h
 *
 * Copied from SH.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_TERMBITS_H
#घोषणा _XTENSA_TERMBITS_H


#समावेश <linux/posix_types.h>

प्रकार अचिन्हित अक्षर	cc_t;
प्रकार अचिन्हित पूर्णांक	speed_t;
प्रकार अचिन्हित पूर्णांक	tcflag_t;

#घोषणा NCCS 19
काष्ठा termios अणु
	tcflag_t c_अगरlag;		/* input mode flags */
	tcflag_t c_oflag;		/* output mode flags */
	tcflag_t c_cflag;		/* control mode flags */
	tcflag_t c_lflag;		/* local mode flags */
	cc_t c_line;			/* line discipline */
	cc_t c_cc[NCCS];		/* control अक्षरacters */
पूर्ण;

काष्ठा termios2 अणु
	tcflag_t c_अगरlag;		/* input mode flags */
	tcflag_t c_oflag;		/* output mode flags */
	tcflag_t c_cflag;		/* control mode flags */
	tcflag_t c_lflag;		/* local mode flags */
	cc_t c_line;			/* line discipline */
	cc_t c_cc[NCCS];		/* control अक्षरacters */
	speed_t c_ispeed;		/* input speed */
	speed_t c_ospeed;		/* output speed */
पूर्ण;

काष्ठा ktermios अणु
	tcflag_t c_अगरlag;		/* input mode flags */
	tcflag_t c_oflag;		/* output mode flags */
	tcflag_t c_cflag;		/* control mode flags */
	tcflag_t c_lflag;		/* local mode flags */
	cc_t c_line;			/* line discipline */
	cc_t c_cc[NCCS];		/* control अक्षरacters */
	speed_t c_ispeed;		/* input speed */
	speed_t c_ospeed;		/* output speed */
पूर्ण;

/* c_cc अक्षरacters */

#घोषणा VINTR 0
#घोषणा VQUIT 1
#घोषणा VERASE 2
#घोषणा VKILL 3
#घोषणा Vखातापूर्ण 4
#घोषणा VTIME 5
#घोषणा VMIN 6
#घोषणा VSWTC 7
#घोषणा VSTART 8
#घोषणा VSTOP 9
#घोषणा VSUSP 10
#घोषणा VEOL 11
#घोषणा VREPRINT 12
#घोषणा VDISCARD 13
#घोषणा VWERASE 14
#घोषणा VLNEXT 15
#घोषणा VEOL2 16

/* c_अगरlag bits */

#घोषणा IGNBRK	0000001
#घोषणा BRKINT	0000002
#घोषणा IGNPAR	0000004
#घोषणा PARMRK	0000010
#घोषणा INPCK	0000020
#घोषणा ISTRIP	0000040
#घोषणा INLCR	0000100
#घोषणा IGNCR	0000200
#घोषणा ICRNL	0000400
#घोषणा IUCLC	0001000
#घोषणा IXON	0002000
#घोषणा IXANY	0004000
#घोषणा IXOFF	0010000
#घोषणा IMAXBEL	0020000
#घोषणा IUTF8	0040000

/* c_oflag bits */

#घोषणा OPOST	0000001
#घोषणा OLCUC	0000002
#घोषणा ONLCR	0000004
#घोषणा OCRNL	0000010
#घोषणा ONOCR	0000020
#घोषणा ONLRET	0000040
#घोषणा OFILL	0000100
#घोषणा OFDEL	0000200
#घोषणा NLDLY	0000400
#घोषणा   NL0	0000000
#घोषणा   NL1	0000400
#घोषणा CRDLY	0003000
#घोषणा   CR0	0000000
#घोषणा   CR1	0001000
#घोषणा   CR2	0002000
#घोषणा   CR3	0003000
#घोषणा TABDLY	0014000
#घोषणा   TAB0	0000000
#घोषणा   TAB1	0004000
#घोषणा   TAB2	0010000
#घोषणा   TAB3	0014000
#घोषणा   XTABS	0014000
#घोषणा BSDLY	0020000
#घोषणा   BS0	0000000
#घोषणा   BS1	0020000
#घोषणा VTDLY	0040000
#घोषणा   VT0	0000000
#घोषणा   VT1	0040000
#घोषणा FFDLY	0100000
#घोषणा   FF0	0000000
#घोषणा   FF1	0100000

/* c_cflag bit meaning */

#घोषणा CBAUD	0010017
#घोषणा  B0	0000000		/* hang up */
#घोषणा  B50	0000001
#घोषणा  B75	0000002
#घोषणा  B110	0000003
#घोषणा  B134	0000004
#घोषणा  B150	0000005
#घोषणा  B200	0000006
#घोषणा  B300	0000007
#घोषणा  B600	0000010
#घोषणा  B1200	0000011
#घोषणा  B1800	0000012
#घोषणा  B2400	0000013
#घोषणा  B4800	0000014
#घोषणा  B9600	0000015
#घोषणा  B19200	0000016
#घोषणा  B38400	0000017
#घोषणा EXTA B19200
#घोषणा EXTB B38400
#घोषणा CSIZE	0000060
#घोषणा   CS5	0000000
#घोषणा   CS6	0000020
#घोषणा   CS7	0000040
#घोषणा   CS8	0000060
#घोषणा CSTOPB	0000100
#घोषणा CREAD	0000200
#घोषणा PARENB	0000400
#घोषणा PARODD	0001000
#घोषणा HUPCL	0002000
#घोषणा CLOCAL	0004000
#घोषणा CBAUDEX 0010000
#घोषणा	   BOTHER 0010000
#घोषणा    B57600 0010001
#घोषणा   B115200 0010002
#घोषणा   B230400 0010003
#घोषणा   B460800 0010004
#घोषणा   B500000 0010005
#घोषणा   B576000 0010006
#घोषणा   B921600 0010007
#घोषणा  B1000000 0010010
#घोषणा  B1152000 0010011
#घोषणा  B1500000 0010012
#घोषणा  B2000000 0010013
#घोषणा  B2500000 0010014
#घोषणा  B3000000 0010015
#घोषणा  B3500000 0010016
#घोषणा  B4000000 0010017
#घोषणा CIBAUD	  002003600000		/* input baud rate */
#घोषणा CMSPAR	  010000000000		/* mark or space (stick) parity */
#घोषणा CRTSCTS	  020000000000		/* flow control */

#घोषणा IBSHIFT	16		/* Shअगरt from CBAUD to CIBAUD */

/* c_lflag bits */

#घोषणा ISIG	0000001
#घोषणा ICANON	0000002
#घोषणा XCASE	0000004
#घोषणा ECHO	0000010
#घोषणा ECHOE	0000020
#घोषणा ECHOK	0000040
#घोषणा ECHONL	0000100
#घोषणा NOFLSH	0000200
#घोषणा TOSTOP	0000400
#घोषणा ECHOCTL	0001000
#घोषणा ECHOPRT	0002000
#घोषणा ECHOKE	0004000
#घोषणा FLUSHO	0010000
#घोषणा PENDIN	0040000
#घोषणा IEXTEN	0100000
#घोषणा EXTPROC	0200000

/* tcflow() and TCXONC use these */

#घोषणा	TCOOFF		0
#घोषणा	TCOON		1
#घोषणा	TCIOFF		2
#घोषणा	TCION		3

/* tcflush() and TCFLSH use these */

#घोषणा	TCIFLUSH	0
#घोषणा	TCOFLUSH	1
#घोषणा	TCIOFLUSH	2

/* tcsetattr uses these */

#घोषणा	TCSANOW		0
#घोषणा	TCSADRAIN	1
#घोषणा	TCSAFLUSH	2

#पूर्ण_अगर	/* _XTENSA_TERMBITS_H */
