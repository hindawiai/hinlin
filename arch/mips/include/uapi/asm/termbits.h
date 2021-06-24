<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 96, 99, 2001, 06 Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 * Copyright (C) 2001 MIPS Technologies, Inc.
 */
#अगर_अघोषित _ASM_TERMBITS_H
#घोषणा _ASM_TERMBITS_H

#समावेश <linux/posix_types.h>

प्रकार अचिन्हित अक्षर cc_t;
प्रकार अचिन्हित पूर्णांक speed_t;
प्रकार अचिन्हित पूर्णांक tcflag_t;

/*
 * The ABI says nothing about NCC but seems to use NCCS as
 * replacement क्रम it in काष्ठा termio
 */
#घोषणा NCCS	23
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
#घोषणा VINTR		 0		/* Interrupt अक्षरacter [ISIG].	*/
#घोषणा VQUIT		 1		/* Quit अक्षरacter [ISIG].  */
#घोषणा VERASE		 2		/* Erase अक्षरacter [ICANON].  */
#घोषणा VKILL		 3		/* Kill-line अक्षरacter [ICANON].  */
#घोषणा VMIN		 4		/* Minimum number of bytes पढ़ो at once [!ICANON].  */
#घोषणा VTIME		 5		/* Time-out value (tenths of a second) [!ICANON].  */
#घोषणा VEOL2		 6		/* Second EOL अक्षरacter [ICANON].  */
#घोषणा VSWTC		 7		/* ??? */
#घोषणा VSWTCH		VSWTC
#घोषणा VSTART		 8		/* Start (X-ON) अक्षरacter [IXON, IXOFF].  */
#घोषणा VSTOP		 9		/* Stop (X-OFF) अक्षरacter [IXON, IXOFF].  */
#घोषणा VSUSP		10		/* Suspend अक्षरacter [ISIG].  */
#अगर 0
/*
 * VDSUSP is not supported
 */
#घोषणा VDSUSP		11		/* Delayed suspend अक्षरacter [ISIG].  */
#पूर्ण_अगर
#घोषणा VREPRINT	12		/* Reprपूर्णांक-line अक्षरacter [ICANON].  */
#घोषणा VDISCARD	13		/* Discard अक्षरacter [IEXTEN].	*/
#घोषणा VWERASE		14		/* Word-erase अक्षरacter [ICANON].  */
#घोषणा VLNEXT		15		/* Literal-next अक्षरacter [IEXTEN].  */
#घोषणा Vखातापूर्ण		16		/* End-of-file अक्षरacter [ICANON].  */
#घोषणा VEOL		17		/* End-of-line अक्षरacter [ICANON].  */

/* c_अगरlag bits */
#घोषणा IGNBRK	0000001		/* Ignore अवरोध condition.  */
#घोषणा BRKINT	0000002		/* Signal पूर्णांकerrupt on अवरोध.  */
#घोषणा IGNPAR	0000004		/* Ignore अक्षरacters with parity errors.  */
#घोषणा PARMRK	0000010		/* Mark parity and framing errors.  */
#घोषणा INPCK	0000020		/* Enable input parity check.  */
#घोषणा ISTRIP	0000040		/* Strip 8th bit off अक्षरacters.  */
#घोषणा INLCR	0000100		/* Map NL to CR on input.  */
#घोषणा IGNCR	0000200		/* Ignore CR.  */
#घोषणा ICRNL	0000400		/* Map CR to NL on input.  */
#घोषणा IUCLC	0001000		/* Map upper हाल to lower हाल on input.  */
#घोषणा IXON	0002000		/* Enable start/stop output control.  */
#घोषणा IXANY	0004000		/* Any अक्षरacter will restart after stop.  */
#घोषणा IXOFF	0010000		/* Enable start/stop input control.  */
#घोषणा IMAXBEL 0020000		/* Ring bell when input queue is full.	*/
#घोषणा IUTF8	0040000		/* Input is UTF-8 */

/* c_oflag bits */
#घोषणा OPOST	0000001		/* Perक्रमm output processing.  */
#घोषणा OLCUC	0000002		/* Map lower हाल to upper हाल on output.  */
#घोषणा ONLCR	0000004		/* Map NL to CR-NL on output.  */
#घोषणा OCRNL	0000010
#घोषणा ONOCR	0000020
#घोषणा ONLRET	0000040
#घोषणा OFILL	0000100
#घोषणा OFDEL	0000200
#घोषणा NLDLY	0000400
#घोषणा	  NL0	0000000
#घोषणा	  NL1	0000400
#घोषणा CRDLY	0003000
#घोषणा	  CR0	0000000
#घोषणा	  CR1	0001000
#घोषणा	  CR2	0002000
#घोषणा	  CR3	0003000
#घोषणा TABDLY	0014000
#घोषणा	  TAB0	0000000
#घोषणा	  TAB1	0004000
#घोषणा	  TAB2	0010000
#घोषणा	  TAB3	0014000
#घोषणा	  XTABS 0014000
#घोषणा BSDLY	0020000
#घोषणा	  BS0	0000000
#घोषणा	  BS1	0020000
#घोषणा VTDLY	0040000
#घोषणा	  VT0	0000000
#घोषणा	  VT1	0040000
#घोषणा FFDLY	0100000
#घोषणा	  FF0	0000000
#घोषणा	  FF1	0100000
/*
#घोषणा PAGEOUT ???
#घोषणा WRAP	???
 */

/* c_cflag bit meaning */
#घोषणा CBAUD	0010017
#घोषणा	 B0	0000000		/* hang up */
#घोषणा	 B50	0000001
#घोषणा	 B75	0000002
#घोषणा	 B110	0000003
#घोषणा	 B134	0000004
#घोषणा	 B150	0000005
#घोषणा	 B200	0000006
#घोषणा	 B300	0000007
#घोषणा	 B600	0000010
#घोषणा	 B1200	0000011
#घोषणा	 B1800	0000012
#घोषणा	 B2400	0000013
#घोषणा	 B4800	0000014
#घोषणा	 B9600	0000015
#घोषणा	 B19200 0000016
#घोषणा	 B38400 0000017
#घोषणा EXTA B19200
#घोषणा EXTB B38400
#घोषणा CSIZE	0000060		/* Number of bits per byte (mask).  */
#घोषणा	  CS5	0000000		/* 5 bits per byte.  */
#घोषणा	  CS6	0000020		/* 6 bits per byte.  */
#घोषणा	  CS7	0000040		/* 7 bits per byte.  */
#घोषणा	  CS8	0000060		/* 8 bits per byte.  */
#घोषणा CSTOPB	0000100		/* Two stop bits instead of one.  */
#घोषणा CREAD	0000200		/* Enable receiver.  */
#घोषणा PARENB	0000400		/* Parity enable.  */
#घोषणा PARODD	0001000		/* Odd parity instead of even.	*/
#घोषणा HUPCL	0002000		/* Hang up on last बंद.  */
#घोषणा CLOCAL	0004000		/* Ignore modem status lines.  */
#घोषणा CBAUDEX 0010000
#घोषणा	   BOTHER 0010000
#घोषणा	   B57600 0010001
#घोषणा	  B115200 0010002
#घोषणा	  B230400 0010003
#घोषणा	  B460800 0010004
#घोषणा	  B500000 0010005
#घोषणा	  B576000 0010006
#घोषणा	  B921600 0010007
#घोषणा	 B1000000 0010010
#घोषणा	 B1152000 0010011
#घोषणा	 B1500000 0010012
#घोषणा	 B2000000 0010013
#घोषणा	 B2500000 0010014
#घोषणा	 B3000000 0010015
#घोषणा	 B3500000 0010016
#घोषणा	 B4000000 0010017
#घोषणा CIBAUD	  002003600000	/* input baud rate */
#घोषणा CMSPAR	  010000000000	/* mark or space (stick) parity */
#घोषणा CRTSCTS	  020000000000	/* flow control */

#घोषणा IBSHIFT 16		/* Shअगरt from CBAUD to CIBAUD */

/* c_lflag bits */
#घोषणा ISIG	0000001		/* Enable संकेतs.  */
#घोषणा ICANON	0000002		/* Do erase and समाप्त processing.  */
#घोषणा XCASE	0000004
#घोषणा ECHO	0000010		/* Enable echo.	 */
#घोषणा ECHOE	0000020		/* Visual erase क्रम ERASE.  */
#घोषणा ECHOK	0000040		/* Echo NL after KILL.	*/
#घोषणा ECHONL	0000100		/* Echo NL even अगर ECHO is off.	 */
#घोषणा NOFLSH	0000200		/* Disable flush after पूर्णांकerrupt.  */
#घोषणा IEXTEN	0000400		/* Enable DISCARD and LNEXT.  */
#घोषणा ECHOCTL 0001000		/* Echo control अक्षरacters as ^X.  */
#घोषणा ECHOPRT 0002000		/* Hardcopy visual erase.  */
#घोषणा ECHOKE	0004000		/* Visual erase क्रम KILL.  */
#घोषणा FLUSHO	0020000
#घोषणा PENDIN	0040000		/* Retype pending input (state).  */
#घोषणा TOSTOP	0100000		/* Send SIGTTOU क्रम background output.	*/
#घोषणा ITOSTOP TOSTOP
#घोषणा EXTPROC 0200000		/* External processing on pty */

/* ioctl (fd, TIOCSERGETLSR, &result) where result may be as below */
#घोषणा TIOCSER_TEMT	0x01	/* Transmitter physically empty */

/* tcflow() and TCXONC use these */
#घोषणा TCOOFF		0	/* Suspend output.  */
#घोषणा TCOON		1	/* Restart suspended output.  */
#घोषणा TCIOFF		2	/* Send a STOP अक्षरacter.  */
#घोषणा TCION		3	/* Send a START अक्षरacter.  */

/* tcflush() and TCFLSH use these */
#घोषणा TCIFLUSH	0	/* Discard data received but not yet पढ़ो.  */
#घोषणा TCOFLUSH	1	/* Discard data written but not yet sent.  */
#घोषणा TCIOFLUSH	2	/* Discard all pending data.  */

/* tcsetattr uses these */
#घोषणा TCSANOW		TCSETS	/* Change immediately.	*/
#घोषणा TCSADRAIN	TCSETSW /* Change when pending output is written.  */
#घोषणा TCSAFLUSH	TCSETSF /* Flush pending input beक्रमe changing.	 */

#पूर्ण_अगर /* _ASM_TERMBITS_H */
