<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_SH_IOCTLS_H
#घोषणा __ASM_SH_IOCTLS_H

#समावेश <यंत्र/ioctl.h>

#घोषणा FIOCLEX		_IO('f', 1)
#घोषणा FIONCLEX	_IO('f', 2)
#घोषणा FIOASYNC	_IOW('f', 125, पूर्णांक)
#घोषणा FIONBIO		_IOW('f', 126, पूर्णांक)
#घोषणा FIONREAD	_IOR('f', 127, पूर्णांक)
#घोषणा TIOCINQ		FIONREAD
#घोषणा FIOQSIZE	_IOR('f', 128, loff_t)

#घोषणा TCGETS		0x5401
#घोषणा TCSETS		0x5402
#घोषणा TCSETSW		0x5403
#घोषणा TCSETSF		0x5404

#घोषणा TCGETA		0x80127417	/* _IOR('t', 23, काष्ठा termio) */
#घोषणा TCSETA		0x40127418	/* _IOW('t', 24, काष्ठा termio) */
#घोषणा TCSETAW		0x40127419	/* _IOW('t', 25, काष्ठा termio) */
#घोषणा TCSETAF		0x4012741C	/* _IOW('t', 28, काष्ठा termio) */

#घोषणा TCSBRK		_IO('t', 29)
#घोषणा TCXONC		_IO('t', 30)
#घोषणा TCFLSH		_IO('t', 31)

#घोषणा TIOCSWINSZ	0x40087467	/* _IOW('t', 103, काष्ठा winsize) */
#घोषणा TIOCGWINSZ	0x80087468	/* _IOR('t', 104, काष्ठा winsize) */
#घोषणा	TIOCSTART	_IO('t', 110)		/* start output, like ^Q */
#घोषणा	TIOCSTOP	_IO('t', 111)		/* stop output, like ^S */
#घोषणा TIOCOUTQ        _IOR('t', 115, पूर्णांक)     /* output queue size */

#घोषणा TIOCSPGRP	_IOW('t', 118, पूर्णांक)
#घोषणा TIOCGPGRP	_IOR('t', 119, पूर्णांक)

#घोषणा TIOCEXCL	_IO('T', 12) /* 0x540C */
#घोषणा TIOCNXCL	_IO('T', 13) /* 0x540D */
#घोषणा TIOCSCTTY	_IO('T', 14) /* 0x540E */

#घोषणा TIOCSTI		_IOW('T', 18, अक्षर) /* 0x5412 */
#घोषणा TIOCMGET	_IOR('T', 21, अचिन्हित पूर्णांक) /* 0x5415 */
#घोषणा TIOCMBIS	_IOW('T', 22, अचिन्हित पूर्णांक) /* 0x5416 */
#घोषणा TIOCMBIC	_IOW('T', 23, अचिन्हित पूर्णांक) /* 0x5417 */
#घोषणा TIOCMSET	_IOW('T', 24, अचिन्हित पूर्णांक) /* 0x5418 */
# define TIOCM_LE	0x001
# define TIOCM_DTR	0x002
# define TIOCM_RTS	0x004
# define TIOCM_ST	0x008
# define TIOCM_SR	0x010
# define TIOCM_CTS	0x020
# define TIOCM_CAR	0x040
# define TIOCM_RNG	0x080
# define TIOCM_DSR	0x100
# define TIOCM_CD	TIOCM_CAR
# define TIOCM_RI	TIOCM_RNG

#घोषणा TIOCGSOFTCAR	_IOR('T', 25, अचिन्हित पूर्णांक) /* 0x5419 */
#घोषणा TIOCSSOFTCAR	_IOW('T', 26, अचिन्हित पूर्णांक) /* 0x541A */
#घोषणा TIOCLINUX	_IOW('T', 28, अक्षर) /* 0x541C */
#घोषणा TIOCCONS	_IO('T', 29) /* 0x541D */
#घोषणा TIOCGSERIAL	0x803C541E	/* _IOR('T', 30, काष्ठा serial_काष्ठा) 0x541E */
#घोषणा TIOCSSERIAL	0x403C541F	/* _IOW('T', 31, काष्ठा serial_काष्ठा) 0x541F */
#घोषणा TIOCPKT		_IOW('T', 32, पूर्णांक) /* 0x5420 */
# define TIOCPKT_DATA		 0
# define TIOCPKT_FLUSHREAD	 1
# define TIOCPKT_FLUSHWRITE	 2
# define TIOCPKT_STOP		 4
# define TIOCPKT_START		 8
# define TIOCPKT_NOSTOP		16
# define TIOCPKT_DOSTOP		32
# define TIOCPKT_IOCTL		64


#घोषणा TIOCNOTTY	_IO('T', 34) /* 0x5422 */
#घोषणा TIOCSETD	_IOW('T', 35, पूर्णांक) /* 0x5423 */
#घोषणा TIOCGETD	_IOR('T', 36, पूर्णांक) /* 0x5424 */
#घोषणा TCSBRKP		_IOW('T', 37, पूर्णांक) /* 0x5425 */	/* Needed क्रम POSIX tcsendअवरोध() */
#घोषणा TIOCSBRK	_IO('T', 39) /* 0x5427 */ /* BSD compatibility */
#घोषणा TIOCCBRK	_IO('T', 40) /* 0x5428 */ /* BSD compatibility */
#घोषणा TIOCGSID	_IOR('T', 41, pid_t) /* 0x5429 */ /* Return the session ID of FD */
#घोषणा TCGETS2		_IOR('T', 42, काष्ठा termios2)
#घोषणा TCSETS2		_IOW('T', 43, काष्ठा termios2)
#घोषणा TCSETSW2	_IOW('T', 44, काष्ठा termios2)
#घोषणा TCSETSF2	_IOW('T', 45, काष्ठा termios2)
#घोषणा TIOCGRS485	_IOR('T', 46, काष्ठा serial_rs485)
#घोषणा TIOCSRS485	_IOWR('T', 47, काष्ठा serial_rs485)
#घोषणा TIOCGPTN	_IOR('T',0x30, अचिन्हित पूर्णांक) /* Get Pty Number (of pty-mux device) */
#घोषणा TIOCSPTLCK	_IOW('T',0x31, पूर्णांक)  /* Lock/unlock Pty */
#घोषणा TIOCGDEV	_IOR('T',0x32, अचिन्हित पूर्णांक) /* Get primary device node of /dev/console */
#घोषणा TIOCSIG		_IOW('T',0x36, पूर्णांक)  /* Generate संकेत on Pty slave */
#घोषणा TIOCVHANGUP	_IO('T', 0x37)
#घोषणा TIOCGPKT	_IOR('T', 0x38, पूर्णांक) /* Get packet mode state */
#घोषणा TIOCGPTLCK	_IOR('T', 0x39, पूर्णांक) /* Get Pty lock state */
#घोषणा TIOCGEXCL	_IOR('T', 0x40, पूर्णांक) /* Get exclusive mode state */
#घोषणा TIOCGPTPEER	_IO('T', 0x41) /* Safely खोलो the slave */
#घोषणा TIOCGISO7816	_IOR('T', 0x42, काष्ठा serial_iso7816)
#घोषणा TIOCSISO7816	_IOWR('T', 0x43, काष्ठा serial_iso7816)

#घोषणा TIOCSERCONFIG	_IO('T', 83) /* 0x5453 */
#घोषणा TIOCSERGWILD	_IOR('T', 84,  पूर्णांक) /* 0x5454 */
#घोषणा TIOCSERSWILD	_IOW('T', 85,  पूर्णांक) /* 0x5455 */
#घोषणा TIOCGLCKTRMIOS	0x5456
#घोषणा TIOCSLCKTRMIOS	0x5457
#घोषणा TIOCSERGSTRUCT	0x80d85458	/* _IOR('T', 88, काष्ठा async_काष्ठा) 0x5458 */ /* For debugging only */
#घोषणा TIOCSERGETLSR   _IOR('T', 89, अचिन्हित पूर्णांक) /* 0x5459 */ /* Get line status रेजिस्टर */
  /* ioctl (fd, TIOCSERGETLSR, &result) where result may be as below */
# define TIOCSER_TEMT    0x01	/* Transmitter physically empty */
#घोषणा TIOCSERGETMULTI 0x80A8545A	/* _IOR('T', 90, काष्ठा serial_multiport_काष्ठा) 0x545A */ /* Get multiport config */
#घोषणा TIOCSERSETMULTI 0x40A8545B	/* _IOW('T', 91, काष्ठा serial_multiport_काष्ठा) 0x545B */ /* Set multiport config */

#घोषणा TIOCMIWAIT	_IO('T', 92) /* 0x545C */	/* रुको क्रम a change on serial input line(s) */
#घोषणा TIOCGICOUNT	0x545D	/* पढ़ो serial port अंतरभूत पूर्णांकerrupt counts */

#पूर्ण_अगर /* __ASM_SH_IOCTLS_H */
