<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * ppp-ioctl.h - PPP ioctl definitions.
 *
 * Copyright 1999-2002 Paul Mackerras.
 *
 *  This program is मुक्त software; you can redistribute it and/or
 *  modअगरy it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.
 */
#अगर_अघोषित _PPP_IOCTL_H
#घोषणा _PPP_IOCTL_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/ppp_defs.h>

/*
 * Bit definitions क्रम flags argument to PPPIOCGFLAGS/PPPIOCSFLAGS.
 */
#घोषणा SC_COMP_PROT	0x00000001	/* protocol compression (output) */
#घोषणा SC_COMP_AC	0x00000002	/* header compression (output) */
#घोषणा	SC_COMP_TCP	0x00000004	/* TCP (VJ) compression (output) */
#घोषणा SC_NO_TCP_CCID	0x00000008	/* disable VJ connection-id comp. */
#घोषणा SC_REJ_COMP_AC	0x00000010	/* reject adrs/ctrl comp. on input */
#घोषणा SC_REJ_COMP_TCP	0x00000020	/* reject TCP (VJ) comp. on input */
#घोषणा SC_CCP_OPEN	0x00000040	/* Look at CCP packets */
#घोषणा SC_CCP_UP	0x00000080	/* May send/recv compressed packets */
#घोषणा SC_ENABLE_IP	0x00000100	/* IP packets may be exchanged */
#घोषणा SC_LOOP_TRAFFIC	0x00000200	/* send traffic to pppd */
#घोषणा SC_MULTILINK	0x00000400	/* करो multilink encapsulation */
#घोषणा SC_MP_SHORTSEQ	0x00000800	/* use लघु MP sequence numbers */
#घोषणा SC_COMP_RUN	0x00001000	/* compressor has been inited */
#घोषणा SC_DECOMP_RUN	0x00002000	/* decompressor has been inited */
#घोषणा SC_MP_XSHORTSEQ	0x00004000	/* transmit लघु MP seq numbers */
#घोषणा SC_DEBUG	0x00010000	/* enable debug messages */
#घोषणा SC_LOG_INPKT	0x00020000	/* log contents of good pkts recvd */
#घोषणा SC_LOG_OUTPKT	0x00040000	/* log contents of pkts sent */
#घोषणा SC_LOG_RAWIN	0x00080000	/* log all अक्षरs received */
#घोषणा SC_LOG_FLUSH	0x00100000	/* log all अक्षरs flushed */
#घोषणा	SC_SYNC		0x00200000	/* synchronous serial mode */
#घोषणा	SC_MUST_COMP    0x00400000	/* no uncompressed packets may be sent or received */
#घोषणा	SC_MASK		0x0f600fff	/* bits that user can change */

/* state bits */
#घोषणा SC_XMIT_BUSY	0x10000000	/* (used by isdn_ppp?) */
#घोषणा SC_RCV_ODDP	0x08000000	/* have rcvd अक्षर with odd parity */
#घोषणा SC_RCV_EVNP	0x04000000	/* have rcvd अक्षर with even parity */
#घोषणा SC_RCV_B7_1	0x02000000	/* have rcvd अक्षर with bit 7 = 1 */
#घोषणा SC_RCV_B7_0	0x01000000	/* have rcvd अक्षर with bit 7 = 0 */
#घोषणा SC_DC_FERROR	0x00800000	/* fatal decomp error detected */
#घोषणा SC_DC_ERROR	0x00400000	/* non-fatal decomp error detected */

/* Used with PPPIOCGNPMODE/PPPIOCSNPMODE */
काष्ठा npioctl अणु
	पूर्णांक		protocol;	/* PPP protocol, e.g. PPP_IP */
	क्रमागत NPmode	mode;
पूर्ण;

/* Structure describing a CCP configuration option, क्रम PPPIOCSCOMPRESS */
काष्ठा ppp_option_data अणु
	__u8	__user *ptr;
	__u32	length;
	पूर्णांक	transmit;
पूर्ण;

/* For PPPIOCGL2TPSTATS */
काष्ठा pppol2tp_ioc_stats अणु
	__u16		tunnel_id;	/* redundant */
	__u16		session_id;	/* अगर zero, get tunnel stats */
	__u32		using_ipsec:1;
	__aligned_u64	tx_packets;
	__aligned_u64	tx_bytes;
	__aligned_u64	tx_errors;
	__aligned_u64	rx_packets;
	__aligned_u64	rx_bytes;
	__aligned_u64	rx_seq_discards;
	__aligned_u64	rx_oos_packets;
	__aligned_u64	rx_errors;
पूर्ण;

/*
 * Ioctl definitions.
 */

#घोषणा	PPPIOCGFLAGS	_IOR('t', 90, पूर्णांक)	/* get configuration flags */
#घोषणा	PPPIOCSFLAGS	_IOW('t', 89, पूर्णांक)	/* set configuration flags */
#घोषणा	PPPIOCGASYNCMAP	_IOR('t', 88, पूर्णांक)	/* get async map */
#घोषणा	PPPIOCSASYNCMAP	_IOW('t', 87, पूर्णांक)	/* set async map */
#घोषणा	PPPIOCGUNIT	_IOR('t', 86, पूर्णांक)	/* get ppp unit number */
#घोषणा	PPPIOCGRASYNCMAP _IOR('t', 85, पूर्णांक)	/* get receive async map */
#घोषणा	PPPIOCSRASYNCMAP _IOW('t', 84, पूर्णांक)	/* set receive async map */
#घोषणा	PPPIOCGMRU	_IOR('t', 83, पूर्णांक)	/* get max receive unit */
#घोषणा	PPPIOCSMRU	_IOW('t', 82, पूर्णांक)	/* set max receive unit */
#घोषणा	PPPIOCSMAXCID	_IOW('t', 81, पूर्णांक)	/* set VJ max slot ID */
#घोषणा PPPIOCGXASYNCMAP _IOR('t', 80, ext_accm) /* get extended ACCM */
#घोषणा PPPIOCSXASYNCMAP _IOW('t', 79, ext_accm) /* set extended ACCM */
#घोषणा PPPIOCXFERUNIT	_IO('t', 78)		/* transfer PPP unit */
#घोषणा PPPIOCSCOMPRESS	_IOW('t', 77, काष्ठा ppp_option_data)
#घोषणा PPPIOCGNPMODE	_IOWR('t', 76, काष्ठा npioctl) /* get NP mode */
#घोषणा PPPIOCSNPMODE	_IOW('t', 75, काष्ठा npioctl)  /* set NP mode */
#घोषणा PPPIOCSPASS	_IOW('t', 71, काष्ठा sock_fprog) /* set pass filter */
#घोषणा PPPIOCSACTIVE	_IOW('t', 70, काष्ठा sock_fprog) /* set active filt */
#घोषणा PPPIOCGDEBUG	_IOR('t', 65, पूर्णांक)	/* Read debug level */
#घोषणा PPPIOCSDEBUG	_IOW('t', 64, पूर्णांक)	/* Set debug level */
#घोषणा PPPIOCGIDLE	_IOR('t', 63, काष्ठा ppp_idle) /* get idle समय */
#घोषणा PPPIOCGIDLE32	_IOR('t', 63, काष्ठा ppp_idle32) /* 32-bit बार */
#घोषणा PPPIOCGIDLE64	_IOR('t', 63, काष्ठा ppp_idle64) /* 64-bit बार */
#घोषणा PPPIOCNEWUNIT	_IOWR('t', 62, पूर्णांक)	/* create new ppp unit */
#घोषणा PPPIOCATTACH	_IOW('t', 61, पूर्णांक)	/* attach to ppp unit */
#घोषणा PPPIOCDETACH	_IOW('t', 60, पूर्णांक)	/* obsolete, करो not use */
#घोषणा PPPIOCSMRRU	_IOW('t', 59, पूर्णांक)	/* set multilink MRU */
#घोषणा PPPIOCCONNECT	_IOW('t', 58, पूर्णांक)	/* connect channel to unit */
#घोषणा PPPIOCDISCONN	_IO('t', 57)		/* disconnect channel */
#घोषणा PPPIOCATTCHAN	_IOW('t', 56, पूर्णांक)	/* attach to ppp channel */
#घोषणा PPPIOCGCHAN	_IOR('t', 55, पूर्णांक)	/* get ppp channel number */
#घोषणा PPPIOCGL2TPSTATS _IOR('t', 54, काष्ठा pppol2tp_ioc_stats)
#घोषणा PPPIOCBRIDGECHAN _IOW('t', 53, पूर्णांक)	/* bridge one channel to another */
#घोषणा PPPIOCUNBRIDGECHAN _IO('t', 52)	/* unbridge channel */

#घोषणा SIOCGPPPSTATS   (SIOCDEVPRIVATE + 0)
#घोषणा SIOCGPPPVER     (SIOCDEVPRIVATE + 1)	/* NEVER change this!! */
#घोषणा SIOCGPPPCSTATS  (SIOCDEVPRIVATE + 2)

#पूर्ण_अगर /* _PPP_IOCTL_H */
