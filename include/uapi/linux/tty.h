<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_TTY_H
#घोषणा _UAPI_LINUX_TTY_H

/*
 * 'tty.h' defines some काष्ठाures used by tty_io.c and some defines.
 */

#घोषणा NR_LDISCS		30

/* line disciplines */
#घोषणा N_TTY		0
#घोषणा N_SLIP		1
#घोषणा N_MOUSE		2
#घोषणा N_PPP		3
#घोषणा N_STRIP		4
#घोषणा N_AX25		5
#घोषणा N_X25		6	/* X.25 async */
#घोषणा N_6PACK		7
#घोषणा N_MASC		8	/* Reserved क्रम Mobitex module <kaz@cafe.net> */
#घोषणा N_R3964		9	/* Reserved क्रम Simatic R3964 module */
#घोषणा N_PROFIBUS_FDL	10	/* Reserved क्रम Profibus */
#घोषणा N_IRDA		11	/* Linux IrDa - http://irda.sourceक्रमge.net/ */
#घोषणा N_SMSBLOCK	12	/* SMS block mode - क्रम talking to GSM data */
				/* cards about SMS messages */
#घोषणा N_HDLC		13	/* synchronous HDLC */
#घोषणा N_SYNC_PPP	14	/* synchronous PPP */
#घोषणा N_HCI		15	/* Bluetooth HCI UART */
#घोषणा N_GIGASET_M101	16	/* Siemens Gigaset M101 serial DECT adapter */
#घोषणा N_SLCAN		17	/* Serial / USB serial CAN Adaptors */
#घोषणा N_PPS		18	/* Pulse per Second */
#घोषणा N_V253		19	/* Codec control over voice modem */
#घोषणा N_CAIF		20      /* CAIF protocol क्रम talking to modems */
#घोषणा N_GSM0710	21	/* GSM 0710 Mux */
#घोषणा N_TI_WL		22	/* क्रम TI's WL BT, FM, GPS combo chips */
#घोषणा N_TRACESINK	23	/* Trace data routing क्रम MIPI P1149.7 */
#घोषणा N_TRACEROUTER	24	/* Trace data routing क्रम MIPI P1149.7 */
#घोषणा N_NCI		25	/* NFC NCI UART */
#घोषणा N_SPEAKUP	26	/* Speakup communication with synths */
#घोषणा N_शून्य		27	/* Null ldisc used क्रम error handling */

#पूर्ण_अगर /* _UAPI_LINUX_TTY_H */
