<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_SPARC_TERMBITS_H
#घोषणा _UAPI_SPARC_TERMBITS_H

#समावेश <linux/posix_types.h>

प्रकार अचिन्हित अक्षर   cc_t;
प्रकार अचिन्हित पूर्णांक    speed_t;

#अगर defined(__sparc__) && defined(__arch64__)
प्रकार अचिन्हित पूर्णांक    tcflag_t;
#अन्यथा
प्रकार अचिन्हित दीर्घ   tcflag_t;
#पूर्ण_अगर

#घोषणा NCC 8
काष्ठा termio अणु
	अचिन्हित लघु c_अगरlag;		/* input mode flags */
	अचिन्हित लघु c_oflag;		/* output mode flags */
	अचिन्हित लघु c_cflag;		/* control mode flags */
	अचिन्हित लघु c_lflag;		/* local mode flags */
	अचिन्हित अक्षर c_line;		/* line discipline */
	अचिन्हित अक्षर c_cc[NCC];	/* control अक्षरacters */
पूर्ण;

#घोषणा NCCS 17
काष्ठा termios अणु
	tcflag_t c_अगरlag;		/* input mode flags */
	tcflag_t c_oflag;		/* output mode flags */
	tcflag_t c_cflag;		/* control mode flags */
	tcflag_t c_lflag;		/* local mode flags */
	cc_t c_line;			/* line discipline */
#अगर_अघोषित __KERNEL__
	cc_t c_cc[NCCS];		/* control अक्षरacters */
#अन्यथा
	cc_t c_cc[NCCS+2];	/* kernel needs 2 more to hold vmin/vसमय */
#घोषणा SIZखातापूर्ण_USER_TERMIOS माप (काष्ठा termios) - (2*माप (cc_t))
#पूर्ण_अगर
पूर्ण;

काष्ठा termios2 अणु
	tcflag_t c_अगरlag;		/* input mode flags */
	tcflag_t c_oflag;		/* output mode flags */
	tcflag_t c_cflag;		/* control mode flags */
	tcflag_t c_lflag;		/* local mode flags */
	cc_t c_line;			/* line discipline */
	cc_t c_cc[NCCS+2];		/* control अक्षरacters */
	speed_t c_ispeed;		/* input speed */
	speed_t c_ospeed;		/* output speed */
पूर्ण;

काष्ठा ktermios अणु
	tcflag_t c_अगरlag;		/* input mode flags */
	tcflag_t c_oflag;		/* output mode flags */
	tcflag_t c_cflag;		/* control mode flags */
	tcflag_t c_lflag;		/* local mode flags */
	cc_t c_line;			/* line discipline */
	cc_t c_cc[NCCS+2];		/* control अक्षरacters */
	speed_t c_ispeed;		/* input speed */
	speed_t c_ospeed;		/* output speed */
पूर्ण;

/* c_cc अक्षरacters */
#घोषणा VINTR    0
#घोषणा VQUIT    1
#घोषणा VERASE   2
#घोषणा VKILL    3
#घोषणा Vखातापूर्ण     4
#घोषणा VEOL     5
#घोषणा VEOL2    6
#घोषणा VSWTC    7
#घोषणा VSTART   8
#घोषणा VSTOP    9



#घोषणा VSUSP    10
#घोषणा VDSUSP   11  /* SunOS POSIX nicety I करो believe... */
#घोषणा VREPRINT 12
#घोषणा VDISCARD 13
#घोषणा VWERASE  14
#घोषणा VLNEXT   15

/* Kernel keeps vmin/vसमय separated, user apps assume vmin/vसमय is
 * shared with eof/eol
 */
#अगर_अघोषित __KERNEL__
#घोषणा VMIN     Vखातापूर्ण
#घोषणा VTIME    VEOL
#पूर्ण_अगर

/* c_अगरlag bits */
#घोषणा IGNBRK	0x00000001
#घोषणा BRKINT	0x00000002
#घोषणा IGNPAR	0x00000004
#घोषणा PARMRK	0x00000008
#घोषणा INPCK	0x00000010
#घोषणा ISTRIP	0x00000020
#घोषणा INLCR	0x00000040
#घोषणा IGNCR	0x00000080
#घोषणा ICRNL	0x00000100
#घोषणा IUCLC	0x00000200
#घोषणा IXON	0x00000400
#घोषणा IXANY	0x00000800
#घोषणा IXOFF	0x00001000
#घोषणा IMAXBEL	0x00002000
#घोषणा IUTF8   0x00004000

/* c_oflag bits */
#घोषणा OPOST	0x00000001
#घोषणा OLCUC	0x00000002
#घोषणा ONLCR	0x00000004
#घोषणा OCRNL	0x00000008
#घोषणा ONOCR	0x00000010
#घोषणा ONLRET	0x00000020
#घोषणा OFILL	0x00000040
#घोषणा OFDEL	0x00000080
#घोषणा NLDLY	0x00000100
#घोषणा   NL0	0x00000000
#घोषणा   NL1	0x00000100
#घोषणा CRDLY	0x00000600
#घोषणा   CR0	0x00000000
#घोषणा   CR1	0x00000200
#घोषणा   CR2	0x00000400
#घोषणा   CR3	0x00000600
#घोषणा TABDLY	0x00001800
#घोषणा   TAB0	0x00000000
#घोषणा   TAB1	0x00000800
#घोषणा   TAB2	0x00001000
#घोषणा   TAB3	0x00001800
#घोषणा   XTABS	0x00001800
#घोषणा BSDLY	0x00002000
#घोषणा   BS0	0x00000000
#घोषणा   BS1	0x00002000
#घोषणा VTDLY	0x00004000
#घोषणा   VT0	0x00000000
#घोषणा   VT1	0x00004000
#घोषणा FFDLY	0x00008000
#घोषणा   FF0	0x00000000
#घोषणा   FF1	0x00008000
#घोषणा PAGEOUT 0x00010000  /* SUNOS specअगरic */
#घोषणा WRAP    0x00020000  /* SUNOS specअगरic */

/* c_cflag bit meaning */
#घोषणा CBAUD	  0x0000100f
#घोषणा  B0	  0x00000000   /* hang up */
#घोषणा  B50	  0x00000001
#घोषणा  B75	  0x00000002
#घोषणा  B110	  0x00000003
#घोषणा  B134	  0x00000004
#घोषणा  B150	  0x00000005
#घोषणा  B200	  0x00000006
#घोषणा  B300	  0x00000007
#घोषणा  B600	  0x00000008
#घोषणा  B1200	  0x00000009
#घोषणा  B1800	  0x0000000a
#घोषणा  B2400	  0x0000000b
#घोषणा  B4800	  0x0000000c
#घोषणा  B9600	  0x0000000d
#घोषणा  B19200	  0x0000000e
#घोषणा  B38400	  0x0000000f
#घोषणा EXTA      B19200
#घोषणा EXTB      B38400
#घोषणा  CSIZE    0x00000030
#घोषणा   CS5	  0x00000000
#घोषणा   CS6	  0x00000010
#घोषणा   CS7	  0x00000020
#घोषणा   CS8	  0x00000030
#घोषणा CSTOPB	  0x00000040
#घोषणा CREAD	  0x00000080
#घोषणा PARENB	  0x00000100
#घोषणा PARODD	  0x00000200
#घोषणा HUPCL	  0x00000400
#घोषणा CLOCAL	  0x00000800
#घोषणा CBAUDEX   0x00001000
/* We'll never see these speeds with the Zilogs, but क्रम completeness... */
#घोषणा  BOTHER   0x00001000
#घोषणा  B57600   0x00001001
#घोषणा  B115200  0x00001002
#घोषणा  B230400  0x00001003
#घोषणा  B460800  0x00001004
/* This is what we can करो with the Zilogs. */
#घोषणा  B76800   0x00001005
/* This is what we can करो with the SAB82532. */
#घोषणा  B153600  0x00001006
#घोषणा  B307200  0x00001007
#घोषणा  B614400  0x00001008
#घोषणा  B921600  0x00001009
/* And these are the rest... */
#घोषणा  B500000  0x0000100a
#घोषणा  B576000  0x0000100b
#घोषणा B1000000  0x0000100c
#घोषणा B1152000  0x0000100d
#घोषणा B1500000  0x0000100e
#घोषणा B2000000  0x0000100f
/* These have totally bogus values and nobody uses them
   so far. Later on we'd have to use say 0x10000x and
   adjust CBAUD स्थिरant and drivers accordingly.
#घोषणा B2500000  0x00001010
#घोषणा B3000000  0x00001011
#घोषणा B3500000  0x00001012
#घोषणा B4000000  0x00001013  */
#घोषणा CIBAUD	  0x100f0000  /* input baud rate (not used) */
#घोषणा CMSPAR	  0x40000000  /* mark or space (stick) parity */
#घोषणा CRTSCTS	  0x80000000  /* flow control */

#घोषणा IBSHIFT	  16		/* Shअगरt from CBAUD to CIBAUD */

/* c_lflag bits */
#घोषणा ISIG	0x00000001
#घोषणा ICANON	0x00000002
#घोषणा XCASE	0x00000004
#घोषणा ECHO	0x00000008
#घोषणा ECHOE	0x00000010
#घोषणा ECHOK	0x00000020
#घोषणा ECHONL	0x00000040
#घोषणा NOFLSH	0x00000080
#घोषणा TOSTOP	0x00000100
#घोषणा ECHOCTL	0x00000200
#घोषणा ECHOPRT	0x00000400
#घोषणा ECHOKE	0x00000800
#घोषणा DEFECHO 0x00001000  /* SUNOS thing, what is it? */
#घोषणा FLUSHO	0x00002000
#घोषणा PENDIN	0x00004000
#घोषणा IEXTEN	0x00008000
#घोषणा EXTPROC	0x00010000

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
#घोषणा TIOCSER_TEMT    0x01	/* Transmitter physically empty */


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

#पूर्ण_अगर /* _UAPI_SPARC_TERMBITS_H */
