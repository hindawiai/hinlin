<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित _ASM_POWERPC_TERMBITS_H
#घोषणा _ASM_POWERPC_TERMBITS_H

/*
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

प्रकार अचिन्हित अक्षर	cc_t;
प्रकार अचिन्हित पूर्णांक	speed_t;
प्रकार अचिन्हित पूर्णांक	tcflag_t;

/*
 * termios type and macro definitions.  Be careful about adding stuff
 * to this file since it's used in GNU libc and there are strict rules
 * concerning namespace pollution.
 */

#घोषणा NCCS 19
काष्ठा termios अणु
	tcflag_t c_अगरlag;		/* input mode flags */
	tcflag_t c_oflag;		/* output mode flags */
	tcflag_t c_cflag;		/* control mode flags */
	tcflag_t c_lflag;		/* local mode flags */
	cc_t c_cc[NCCS];		/* control अक्षरacters */
	cc_t c_line;			/* line discipline (== c_cc[19]) */
	speed_t c_ispeed;		/* input speed */
	speed_t c_ospeed;		/* output speed */
पूर्ण;

/* For PowerPC the termios and ktermios are the same */

काष्ठा ktermios अणु
	tcflag_t c_अगरlag;		/* input mode flags */
	tcflag_t c_oflag;		/* output mode flags */
	tcflag_t c_cflag;		/* control mode flags */
	tcflag_t c_lflag;		/* local mode flags */
	cc_t c_cc[NCCS];		/* control अक्षरacters */
	cc_t c_line;			/* line discipline (== c_cc[19]) */
	speed_t c_ispeed;		/* input speed */
	speed_t c_ospeed;		/* output speed */
पूर्ण;

/* c_cc अक्षरacters */
#घोषणा VINTR 	         0
#घोषणा VQUIT 	         1
#घोषणा VERASE 	         2
#घोषणा VKILL	         3
#घोषणा Vखातापूर्ण	         4
#घोषणा VMIN	         5
#घोषणा VEOL	         6
#घोषणा VTIME	         7
#घोषणा VEOL2	         8
#घोषणा VSWTC	         9
#घोषणा VWERASE 	10
#घोषणा VREPRINT	11
#घोषणा VSUSP 		12
#घोषणा VSTART		13
#घोषणा VSTOP		14
#घोषणा VLNEXT		15
#घोषणा VDISCARD	16

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
#घोषणा IXON	0001000
#घोषणा IXOFF	0002000
#घोषणा IXANY	0004000
#घोषणा IUCLC	0010000
#घोषणा IMAXBEL	0020000
#घोषणा	IUTF8	0040000

/* c_oflag bits */
#घोषणा OPOST	0000001
#घोषणा ONLCR	0000002
#घोषणा OLCUC	0000004

#घोषणा OCRNL	0000010
#घोषणा ONOCR	0000020
#घोषणा ONLRET	0000040

#घोषणा OFILL	00000100
#घोषणा OFDEL	00000200
#घोषणा NLDLY	00001400
#घोषणा   NL0	00000000
#घोषणा   NL1	00000400
#घोषणा   NL2	00001000
#घोषणा   NL3	00001400
#घोषणा TABDLY	00006000
#घोषणा   TAB0	00000000
#घोषणा   TAB1	00002000
#घोषणा   TAB2	00004000
#घोषणा   TAB3	00006000
#घोषणा   XTABS	00006000	/* required by POSIX to == TAB3 */
#घोषणा CRDLY	00030000
#घोषणा   CR0	00000000
#घोषणा   CR1	00010000
#घोषणा   CR2	00020000
#घोषणा   CR3	00030000
#घोषणा FFDLY	00040000
#घोषणा   FF0	00000000
#घोषणा   FF1	00040000
#घोषणा BSDLY	00100000
#घोषणा   BS0	00000000
#घोषणा   BS1	00100000
#घोषणा VTDLY	00200000
#घोषणा   VT0	00000000
#घोषणा   VT1	00200000

/* c_cflag bit meaning */
#घोषणा CBAUD	0000377
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
#घोषणा  EXTA   B19200
#घोषणा  EXTB   B38400
#घोषणा  CBAUDEX 0000000
#घोषणा  B57600   00020
#घोषणा  B115200  00021
#घोषणा  B230400  00022
#घोषणा  B460800  00023
#घोषणा  B500000  00024
#घोषणा  B576000  00025
#घोषणा  B921600  00026
#घोषणा B1000000  00027
#घोषणा B1152000  00030
#घोषणा B1500000  00031
#घोषणा B2000000  00032
#घोषणा B2500000  00033
#घोषणा B3000000  00034
#घोषणा B3500000  00035
#घोषणा B4000000  00036
#घोषणा   BOTHER  00037

#घोषणा CIBAUD	077600000
#घोषणा IBSHIFT	16		/* Shअगरt from CBAUD to CIBAUD */

#घोषणा CSIZE	00001400
#घोषणा   CS5	00000000
#घोषणा   CS6	00000400
#घोषणा   CS7	00001000
#घोषणा   CS8	00001400

#घोषणा CSTOPB	00002000
#घोषणा CREAD	00004000
#घोषणा PARENB	00010000
#घोषणा PARODD	00020000
#घोषणा HUPCL	00040000

#घोषणा CLOCAL	00100000
#घोषणा CMSPAR	  010000000000		/* mark or space (stick) parity */
#घोषणा CRTSCTS	  020000000000		/* flow control */

/* c_lflag bits */
#घोषणा ISIG	0x00000080
#घोषणा ICANON	0x00000100
#घोषणा XCASE	0x00004000
#घोषणा ECHO	0x00000008
#घोषणा ECHOE	0x00000002
#घोषणा ECHOK	0x00000004
#घोषणा ECHONL	0x00000010
#घोषणा NOFLSH	0x80000000
#घोषणा TOSTOP	0x00400000
#घोषणा ECHOCTL	0x00000040
#घोषणा ECHOPRT	0x00000020
#घोषणा ECHOKE	0x00000001
#घोषणा FLUSHO	0x00800000
#घोषणा PENDIN	0x20000000
#घोषणा IEXTEN	0x00000400
#घोषणा EXTPROC	0x10000000

/* Values क्रम the ACTION argument to `tcflow'.  */
#घोषणा	TCOOFF		0
#घोषणा	TCOON		1
#घोषणा	TCIOFF		2
#घोषणा	TCION		3

/* Values क्रम the QUEUE_SELECTOR argument to `tcflush'.  */
#घोषणा	TCIFLUSH	0
#घोषणा	TCOFLUSH	1
#घोषणा	TCIOFLUSH	2

/* Values क्रम the OPTIONAL_ACTIONS argument to `tcsetattr'.  */
#घोषणा	TCSANOW		0
#घोषणा	TCSADRAIN	1
#घोषणा	TCSAFLUSH	2

#पूर्ण_अगर	/* _ASM_POWERPC_TERMBITS_H */
