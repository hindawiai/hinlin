<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_SPARC_IOCTLS_H
#घोषणा _UAPI_ASM_SPARC_IOCTLS_H

#समावेश <यंत्र/ioctl.h>

/* Big T */
#घोषणा TCGETA		_IOR('T', 1, काष्ठा termio)
#घोषणा TCSETA		_IOW('T', 2, काष्ठा termio)
#घोषणा TCSETAW		_IOW('T', 3, काष्ठा termio)
#घोषणा TCSETAF		_IOW('T', 4, काष्ठा termio)
#घोषणा TCSBRK		_IO('T', 5)
#घोषणा TCXONC		_IO('T', 6)
#घोषणा TCFLSH		_IO('T', 7)
#घोषणा TCGETS		_IOR('T', 8, काष्ठा termios)
#घोषणा TCSETS		_IOW('T', 9, काष्ठा termios)
#घोषणा TCSETSW		_IOW('T', 10, काष्ठा termios)
#घोषणा TCSETSF		_IOW('T', 11, काष्ठा termios)
#घोषणा TCGETS2		_IOR('T', 12, काष्ठा termios2)
#घोषणा TCSETS2		_IOW('T', 13, काष्ठा termios2)
#घोषणा TCSETSW2	_IOW('T', 14, काष्ठा termios2)
#घोषणा TCSETSF2	_IOW('T', 15, काष्ठा termios2)
#घोषणा TIOCGDEV	_IOR('T',0x32, अचिन्हित पूर्णांक) /* Get primary device node of /dev/console */
#घोषणा TIOCVHANGUP	_IO('T', 0x37)
#घोषणा TIOCGPKT	_IOR('T', 0x38, पूर्णांक) /* Get packet mode state */
#घोषणा TIOCGPTLCK	_IOR('T', 0x39, पूर्णांक) /* Get Pty lock state */
#घोषणा TIOCGEXCL	_IOR('T', 0x40, पूर्णांक) /* Get exclusive mode state */
#घोषणा TIOCGRS485	_IOR('T', 0x41, काष्ठा serial_rs485)
#घोषणा TIOCSRS485	_IOWR('T', 0x42, काष्ठा serial_rs485)
#घोषणा TIOCGISO7816	_IOR('T', 0x43, काष्ठा serial_iso7816)
#घोषणा TIOCSISO7816	_IOWR('T', 0x44, काष्ठा serial_iso7816)

/* Note that all the ioctls that are not available in Linux have a
 * द्विगुन underscore on the front to: a) aव्योम some programs to
 * think we support some ioctls under Linux (स्वतःconfiguration stuff)
 */
/* Little t */
#घोषणा TIOCGETD	_IOR('t', 0, पूर्णांक)
#घोषणा TIOCSETD	_IOW('t', 1, पूर्णांक)
#घोषणा __TIOCHPCL        _IO('t', 2) /* SunOS Specअगरic */
#घोषणा __TIOCMODG        _IOR('t', 3, पूर्णांक) /* SunOS Specअगरic */
#घोषणा __TIOCMODS        _IOW('t', 4, पूर्णांक) /* SunOS Specअगरic */
#घोषणा __TIOCGETP        _IOR('t', 8, काष्ठा sgttyb) /* SunOS Specअगरic */
#घोषणा __TIOCSETP        _IOW('t', 9, काष्ठा sgttyb) /* SunOS Specअगरic */
#घोषणा __TIOCSETN        _IOW('t', 10, काष्ठा sgttyb) /* SunOS Specअगरic */
#घोषणा TIOCEXCL	_IO('t', 13)
#घोषणा TIOCNXCL	_IO('t', 14)
#घोषणा __TIOCFLUSH       _IOW('t', 16, पूर्णांक) /* SunOS Specअगरic */
#घोषणा __TIOCSETC        _IOW('t', 17, काष्ठा tअक्षरs) /* SunOS Specअगरic */
#घोषणा __TIOCGETC        _IOR('t', 18, काष्ठा tअक्षरs) /* SunOS Specअगरic */
#घोषणा __TIOCTCNTL       _IOW('t', 32, पूर्णांक) /* SunOS Specअगरic */
#घोषणा __TIOCSIGNAL      _IOW('t', 33, पूर्णांक) /* SunOS Specअगरic */
#घोषणा __TIOCSETX        _IOW('t', 34, पूर्णांक) /* SunOS Specअगरic */
#घोषणा __TIOCGETX        _IOR('t', 35, पूर्णांक) /* SunOS Specअगरic */
#घोषणा TIOCCONS	_IO('t', 36)
#घोषणा TIOCGSOFTCAR	_IOR('t', 100, पूर्णांक)
#घोषणा TIOCSSOFTCAR	_IOW('t', 101, पूर्णांक)
#घोषणा __TIOCUCNTL       _IOW('t', 102, पूर्णांक) /* SunOS Specअगरic */
#घोषणा TIOCSWINSZ	_IOW('t', 103, काष्ठा winsize)
#घोषणा TIOCGWINSZ	_IOR('t', 104, काष्ठा winsize)
#घोषणा __TIOCREMOTE      _IOW('t', 105, पूर्णांक) /* SunOS Specअगरic */
#घोषणा TIOCMGET	_IOR('t', 106, पूर्णांक)
#घोषणा TIOCMBIC	_IOW('t', 107, पूर्णांक)
#घोषणा TIOCMBIS	_IOW('t', 108, पूर्णांक)
#घोषणा TIOCMSET	_IOW('t', 109, पूर्णांक)
#घोषणा TIOCSTART       _IO('t', 110)
#घोषणा TIOCSTOP        _IO('t', 111)
#घोषणा TIOCPKT		_IOW('t', 112, पूर्णांक)
#घोषणा TIOCNOTTY	_IO('t', 113)
#घोषणा TIOCSTI		_IOW('t', 114, अक्षर)
#घोषणा TIOCOUTQ	_IOR('t', 115, पूर्णांक)
#घोषणा __TIOCGLTC        _IOR('t', 116, काष्ठा ltअक्षरs) /* SunOS Specअगरic */
#घोषणा __TIOCSLTC        _IOW('t', 117, काष्ठा ltअक्षरs) /* SunOS Specअगरic */
/* 118 is the non-posix setpgrp tty ioctl */
/* 119 is the non-posix getpgrp tty ioctl */
#घोषणा __TIOCCDTR        _IO('t', 120) /* SunOS Specअगरic */
#घोषणा __TIOCSDTR        _IO('t', 121) /* SunOS Specअगरic */
#घोषणा TIOCCBRK        _IO('t', 122)
#घोषणा TIOCSBRK        _IO('t', 123)
#घोषणा __TIOCLGET        _IOW('t', 124, पूर्णांक) /* SunOS Specअगरic */
#घोषणा __TIOCLSET        _IOW('t', 125, पूर्णांक) /* SunOS Specअगरic */
#घोषणा __TIOCLBIC        _IOW('t', 126, पूर्णांक) /* SunOS Specअगरic */
#घोषणा __TIOCLBIS        _IOW('t', 127, पूर्णांक) /* SunOS Specअगरic */
#घोषणा __TIOCISPACE      _IOR('t', 128, पूर्णांक) /* SunOS Specअगरic */
#घोषणा __TIOCISIZE       _IOR('t', 129, पूर्णांक) /* SunOS Specअगरic */
#घोषणा TIOCSPGRP	_IOW('t', 130, पूर्णांक)
#घोषणा TIOCGPGRP	_IOR('t', 131, पूर्णांक)
#घोषणा TIOCSCTTY	_IO('t', 132)
#घोषणा TIOCGSID	_IOR('t', 133, पूर्णांक)
/* Get minor device of a pty master's FD -- Solaris equiv is ISPTM */
#घोषणा TIOCGPTN	_IOR('t', 134, अचिन्हित पूर्णांक) /* Get Pty Number */
#घोषणा TIOCSPTLCK	_IOW('t', 135, पूर्णांक) /* Lock/unlock PTY */
#घोषणा TIOCSIG		_IOW('t', 136, पूर्णांक) /* Generate संकेत on Pty slave */
#घोषणा TIOCGPTPEER	_IO('t', 137) /* Safely खोलो the slave */

/* Little f */
#घोषणा FIOCLEX		_IO('f', 1)
#घोषणा FIONCLEX	_IO('f', 2)
#घोषणा FIOASYNC	_IOW('f', 125, पूर्णांक)
#घोषणा FIONBIO		_IOW('f', 126, पूर्णांक)
#घोषणा FIONREAD	_IOR('f', 127, पूर्णांक)
#घोषणा TIOCINQ		FIONREAD
#घोषणा FIOQSIZE	_IOR('f', 128, loff_t)

/* SCARY Rutgers local SunOS kernel hackery, perhaps I will support it
 * someday.  This is completely bogus, I know...
 */
#घोषणा __TCGETSTAT       _IO('T', 200) /* Rutgers specअगरic */
#घोषणा __TCSETSTAT       _IO('T', 201) /* Rutgers specअगरic */

/* Linux specअगरic, no SunOS equivalent. */
#घोषणा TIOCLINUX	0x541C
#घोषणा TIOCGSERIAL	0x541E
#घोषणा TIOCSSERIAL	0x541F
#घोषणा TCSBRKP		0x5425
#घोषणा TIOCSERCONFIG	0x5453
#घोषणा TIOCSERGWILD	0x5454
#घोषणा TIOCSERSWILD	0x5455
#घोषणा TIOCGLCKTRMIOS	0x5456
#घोषणा TIOCSLCKTRMIOS	0x5457
#घोषणा TIOCSERGSTRUCT	0x5458 /* For debugging only */
#घोषणा TIOCSERGETLSR   0x5459 /* Get line status रेजिस्टर */
#घोषणा TIOCSERGETMULTI 0x545A /* Get multiport config  */
#घोषणा TIOCSERSETMULTI 0x545B /* Set multiport config */
#घोषणा TIOCMIWAIT	0x545C /* Wait क्रम change on serial input line(s) */
#घोषणा TIOCGICOUNT	0x545D /* Read serial port अंतरभूत पूर्णांकerrupt counts */

/* Kernel definitions */

/* Used क्रम packet mode */
#घोषणा TIOCPKT_DATA		 0
#घोषणा TIOCPKT_FLUSHREAD	 1
#घोषणा TIOCPKT_FLUSHWRITE	 2
#घोषणा TIOCPKT_STOP		 4
#घोषणा TIOCPKT_START		 8
#घोषणा TIOCPKT_NOSTOP		16
#घोषणा TIOCPKT_DOSTOP		32
#घोषणा TIOCPKT_IOCTL		64

#पूर्ण_अगर /* _UAPI_ASM_SPARC_IOCTLS_H */
