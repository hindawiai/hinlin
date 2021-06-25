<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_TTY_FLAGS_H
#घोषणा _LINUX_TTY_FLAGS_H

/*
 * Definitions क्रम async_काष्ठा (and serial_काष्ठा) flags field also
 * shared by the tty_port flags काष्ठाures.
 *
 * Define ASYNCB_* क्रम convenient use with अणुtest,set,clearपूर्ण_bit.
 *
 * Bits [0..ASYNCB_LAST_USER] are userspace defined/visible/changeable
 * [x] in the bit comments indicates the flag is defunct and no दीर्घer used.
 */
#घोषणा ASYNCB_HUP_NOTIFY	 0 /* Notअगरy getty on hangups and बंदs
				    * on the callout port */
#घोषणा ASYNCB_FOURPORT		 1 /* Set OUT1, OUT2 per AST Fourport settings */
#घोषणा ASYNCB_SAK		 2 /* Secure Attention Key (Orange book) */
#घोषणा ASYNCB_SPLIT_TERMIOS	 3 /* [x] Separate termios क्रम dialin/callout */
#घोषणा ASYNCB_SPD_HI		 4 /* Use 57600 instead of 38400 bps */
#घोषणा ASYNCB_SPD_VHI		 5 /* Use 115200 instead of 38400 bps */
#घोषणा ASYNCB_SKIP_TEST	 6 /* Skip UART test during स्वतःconfiguration */
#घोषणा ASYNCB_AUTO_IRQ		 7 /* Do स्वतःmatic IRQ during
				    * स्वतःconfiguration */
#घोषणा ASYNCB_SESSION_LOCKOUT	 8 /* [x] Lock out cua खोलोs based on session */
#घोषणा ASYNCB_PGRP_LOCKOUT	 9 /* [x] Lock out cua खोलोs based on pgrp */
#घोषणा ASYNCB_CALLOUT_NOHUP	10 /* [x] Don't करो hangups क्रम cua device */
#घोषणा ASYNCB_HARDPPS_CD	11 /* Call hardpps when CD goes high  */
#घोषणा ASYNCB_SPD_SHI		12 /* Use 230400 instead of 38400 bps */
#घोषणा ASYNCB_LOW_LATENCY	13 /* Request low latency behaviour */
#घोषणा ASYNCB_BUGGY_UART	14 /* This is a buggy UART, skip some safety
				    * checks.  Note: can be dangerous! */
#घोषणा ASYNCB_AUTOPROBE	15 /* [x] Port was स्वतःprobed by PCI/PNP code */
#घोषणा ASYNCB_MAGIC_MULTIPLIER	16 /* Use special CLK or भागisor */
#घोषणा ASYNCB_LAST_USER	16

/*
 * Internal flags used only by kernel (पढ़ो-only)
 *
 * WARNING: These flags are no दीर्घer used and have been superceded by the
 *	    TTY_PORT_ flags in the अगरlags field (and not userspace-visible)
 */
#अगर_अघोषित __KERNEL__
#घोषणा ASYNCB_INITIALIZED	31 /* Serial port was initialized */
#घोषणा ASYNCB_SUSPENDED	30 /* Serial port is suspended */
#घोषणा ASYNCB_NORMAL_ACTIVE	29 /* Normal device is active */
#घोषणा ASYNCB_BOOT_AUTOCONF	28 /* Autoconfigure port on bootup */
#घोषणा ASYNCB_CLOSING		27 /* Serial port is closing */
#घोषणा ASYNCB_CTS_FLOW		26 /* Do CTS flow control */
#घोषणा ASYNCB_CHECK_CD		25 /* i.e., CLOCAL */
#घोषणा ASYNCB_SHARE_IRQ	24 /* क्रम multअगरunction cards, no दीर्घer used */
#घोषणा ASYNCB_CONS_FLOW	23 /* flow control क्रम console  */
#घोषणा ASYNCB_FIRST_KERNEL	22
#पूर्ण_अगर

/* Masks */
#घोषणा ASYNC_HUP_NOTIFY	(1U << ASYNCB_HUP_NOTIFY)
#घोषणा ASYNC_SUSPENDED		(1U << ASYNCB_SUSPENDED)
#घोषणा ASYNC_FOURPORT		(1U << ASYNCB_FOURPORT)
#घोषणा ASYNC_SAK		(1U << ASYNCB_SAK)
#घोषणा ASYNC_SPLIT_TERMIOS	(1U << ASYNCB_SPLIT_TERMIOS)
#घोषणा ASYNC_SPD_HI		(1U << ASYNCB_SPD_HI)
#घोषणा ASYNC_SPD_VHI		(1U << ASYNCB_SPD_VHI)
#घोषणा ASYNC_SKIP_TEST		(1U << ASYNCB_SKIP_TEST)
#घोषणा ASYNC_AUTO_IRQ		(1U << ASYNCB_AUTO_IRQ)
#घोषणा ASYNC_SESSION_LOCKOUT	(1U << ASYNCB_SESSION_LOCKOUT)
#घोषणा ASYNC_PGRP_LOCKOUT	(1U << ASYNCB_PGRP_LOCKOUT)
#घोषणा ASYNC_CALLOUT_NOHUP	(1U << ASYNCB_CALLOUT_NOHUP)
#घोषणा ASYNC_HARDPPS_CD	(1U << ASYNCB_HARDPPS_CD)
#घोषणा ASYNC_SPD_SHI		(1U << ASYNCB_SPD_SHI)
#घोषणा ASYNC_LOW_LATENCY	(1U << ASYNCB_LOW_LATENCY)
#घोषणा ASYNC_BUGGY_UART	(1U << ASYNCB_BUGGY_UART)
#घोषणा ASYNC_AUTOPROBE		(1U << ASYNCB_AUTOPROBE)
#घोषणा ASYNC_MAGIC_MULTIPLIER	(1U << ASYNCB_MAGIC_MULTIPLIER)

#घोषणा ASYNC_FLAGS		((1U << (ASYNCB_LAST_USER + 1)) - 1)
#घोषणा ASYNC_DEPRECATED	(ASYNC_SPLIT_TERMIOS | ASYNC_SESSION_LOCKOUT | \
		ASYNC_PGRP_LOCKOUT | ASYNC_CALLOUT_NOHUP | ASYNC_AUTOPROBE)
#घोषणा ASYNC_USR_MASK		(ASYNC_SPD_MASK|ASYNC_CALLOUT_NOHUP| \
		ASYNC_LOW_LATENCY)
#घोषणा ASYNC_SPD_CUST		(ASYNC_SPD_HI|ASYNC_SPD_VHI)
#घोषणा ASYNC_SPD_WARP		(ASYNC_SPD_HI|ASYNC_SPD_SHI)
#घोषणा ASYNC_SPD_MASK		(ASYNC_SPD_HI|ASYNC_SPD_VHI|ASYNC_SPD_SHI)

#अगर_अघोषित __KERNEL__
/* These flags are no दीर्घer used (and were always masked from userspace) */
#घोषणा ASYNC_INITIALIZED	(1U << ASYNCB_INITIALIZED)
#घोषणा ASYNC_NORMAL_ACTIVE	(1U << ASYNCB_NORMAL_ACTIVE)
#घोषणा ASYNC_BOOT_AUTOCONF	(1U << ASYNCB_BOOT_AUTOCONF)
#घोषणा ASYNC_CLOSING		(1U << ASYNCB_CLOSING)
#घोषणा ASYNC_CTS_FLOW		(1U << ASYNCB_CTS_FLOW)
#घोषणा ASYNC_CHECK_CD		(1U << ASYNCB_CHECK_CD)
#घोषणा ASYNC_SHARE_IRQ		(1U << ASYNCB_SHARE_IRQ)
#घोषणा ASYNC_CONS_FLOW		(1U << ASYNCB_CONS_FLOW)
#घोषणा ASYNC_INTERNAL_FLAGS	(~((1U << ASYNCB_FIRST_KERNEL) - 1))
#पूर्ण_अगर

#पूर्ण_अगर
