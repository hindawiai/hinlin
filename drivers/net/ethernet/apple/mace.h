<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * mace.h - definitions क्रम the रेजिस्टरs in the Am79C940 MACE
 * (Medium Access Control क्रम Ethernet) controller.
 *
 * Copyright (C) 1996 Paul Mackerras.
 */

#घोषणा REG(x)	अस्थिर अचिन्हित अक्षर x; अक्षर x ## _pad[15]

काष्ठा mace अणु
	REG(rcvfअगरo);		/* receive FIFO */
	REG(xmtfअगरo);		/* transmit FIFO */
	REG(xmtfc);		/* transmit frame control */
	REG(xmtfs);		/* transmit frame status */
	REG(xmtrc);		/* transmit retry count */
	REG(rcvfc);		/* receive frame control */
	REG(rcvfs);		/* receive frame status (4 bytes) */
	REG(fअगरofc);		/* FIFO frame count */
	REG(ir);		/* पूर्णांकerrupt रेजिस्टर */
	REG(imr);		/* पूर्णांकerrupt mask रेजिस्टर */
	REG(pr);		/* poll रेजिस्टर */
	REG(biucc);		/* bus पूर्णांकerface unit config control */
	REG(fअगरocc);		/* FIFO configuration control */
	REG(maccc);		/* medium access control config control */
	REG(plscc);		/* phys layer संकेतling config control */
	REG(phycc);		/* physical configuration control */
	REG(chipid_lo);		/* chip ID, lsb */
	REG(chipid_hi);		/* chip ID, msb */
	REG(iac);		/* पूर्णांकernal address config */
	REG(reg19);
	REG(ladrf);		/* logical address filter (8 bytes) */
	REG(padr);		/* physical address (6 bytes) */
	REG(reg22);
	REG(reg23);
	REG(mpc);		/* missed packet count (clears when पढ़ो) */
	REG(reg25);
	REG(rntpc);		/* runt packet count (clears when पढ़ो) */
	REG(rcvcc);		/* recv collision count (clears when पढ़ो) */
	REG(reg28);
	REG(utr);		/* user test reg */
	REG(reg30);
	REG(reg31);
पूर्ण;

/* Bits in XMTFC */
#घोषणा DRTRY		0x80	/* करोn't retry transmission after collision */
#घोषणा DXMTFCS		0x08	/* करोn't append FCS to transmitted frame */
#घोषणा AUTO_PAD_XMIT	0x01	/* स्वतः-pad लघु packets on transmission */

/* Bits in XMTFS: only valid when XMTSV is set in PR and XMTFS */
#घोषणा XMTSV		0x80	/* transmit status (i.e. XMTFS) valid */
#घोषणा UFLO		0x40	/* underflow - xmit fअगरo ran dry */
#घोषणा LCOL		0x20	/* late collision (transmission पातed) */
#घोषणा MORE		0x10	/* 2 or more retries needed to xmit frame */
#घोषणा ONE		0x08	/* 1 retry needed to xmit frame */
#घोषणा DEFER		0x04	/* MACE had to defer xmission (enet busy) */
#घोषणा LCAR		0x02	/* loss of carrier (transmission पातed) */
#घोषणा RTRY		0x01	/* too many retries (transmission पातed) */

/* Bits in XMTRC: only valid when XMTSV is set in PR (and XMTFS) */
#घोषणा EXDEF		0x80	/* had to defer क्रम excessive समय */
#घोषणा RETRY_MASK	0x0f	/* number of retries (0 - 15) */

/* Bits in RCVFC */
#घोषणा LLRCV		0x08	/* low latency receive: early DMA request */
#घोषणा M_RBAR		0x04	/* sets function of EAM/R pin */
#घोषणा AUTO_STRIP_RCV	0x01	/* स्वतः-strip लघु LLC frames on recv */

/*
 * Bits in RCVFS.  After a frame is received, four bytes of status
 * are स्वतःmatically पढ़ो from this रेजिस्टर and appended to the frame
 * data in memory.  These are:
 * Byte 0 and 1: message byte count and frame status
 * Byte 2: runt packet count
 * Byte 3: receive collision count
 */
#घोषणा RS_OFLO		0x8000	/* receive FIFO overflowed */
#घोषणा RS_CLSN		0x4000	/* received frame suffered (late) collision */
#घोषणा RS_FRAMERR	0x2000	/* framing error flag */
#घोषणा RS_FCSERR	0x1000	/* frame had FCS error */
#घोषणा RS_COUNT	0x0fff	/* mask क्रम byte count field */

/* Bits (fields) in FIFOFC */
#घोषणा RCVFC_SH	4	/* receive frame count in FIFO */
#घोषणा RCVFC_MASK	0x0f
#घोषणा XMTFC_SH	0	/* transmit frame count in FIFO */
#घोषणा XMTFC_MASK	0x0f

/*
 * Bits in IR and IMR.  The IR clears itself when पढ़ो.
 * Setting a bit in the IMR will disable the corresponding पूर्णांकerrupt.
 */
#घोषणा JABBER		0x80	/* jabber error - 10baseT xmission too दीर्घ */
#घोषणा BABBLE		0x40	/* babble - xmitter xmitting क्रम too दीर्घ */
#घोषणा CERR		0x20	/* collision err - no SQE test (heartbeat) */
#घोषणा RCVCCO		0x10	/* RCVCC overflow */
#घोषणा RNTPCO		0x08	/* RNTPC overflow */
#घोषणा MPCO		0x04	/* MPC overflow */
#घोषणा RCVINT		0x02	/* receive पूर्णांकerrupt */
#घोषणा XMTINT		0x01	/* transmitter पूर्णांकerrupt */

/* Bits in PR */
#घोषणा XMTSV		0x80	/* XMTFS valid (same as in XMTFS) */
#घोषणा TDTREQ		0x40	/* set when xmit fअगरo is requesting data */
#घोषणा RDTREQ		0x20	/* set when recv fअगरo requests data xfer */

/* Bits in BIUCC */
#घोषणा BSWP		0x40	/* byte swap, i.e. big-endian bus */
#घोषणा XMTSP_4		0x00	/* start xmitting when 4 bytes in FIFO */
#घोषणा XMTSP_16	0x10	/* start xmitting when 16 bytes in FIFO */
#घोषणा XMTSP_64	0x20	/* start xmitting when 64 bytes in FIFO */
#घोषणा XMTSP_112	0x30	/* start xmitting when 112 bytes in FIFO */
#घोषणा SWRST		0x01	/* software reset */

/* Bits in FIFOCC */
#घोषणा XMTFW_8		0x00	/* xmit fअगरo watermark = 8 words मुक्त */
#घोषणा XMTFW_16	0x40	/*  16 words मुक्त */
#घोषणा XMTFW_32	0x80	/*  32 words मुक्त */
#घोषणा RCVFW_16	0x00	/* recv fअगरo watermark = 16 bytes avail */
#घोषणा RCVFW_32	0x10	/*  32 bytes avail */
#घोषणा RCVFW_64	0x20	/*  64 bytes avail */
#घोषणा XMTFWU		0x08	/* xmit fअगरo watermark update enable */
#घोषणा RCVFWU		0x04	/* recv fअगरo watermark update enable */
#घोषणा XMTBRST		0x02	/* enable transmit burst mode */
#घोषणा RCVBRST		0x01	/* enable receive burst mode */

/* Bits in MACCC */
#घोषणा PROM		0x80	/* promiscuous mode */
#घोषणा DXMT2PD		0x40	/* disable xmit two-part deferral algorithm */
#घोषणा EMBA		0x20	/* enable modअगरied backoff algorithm */
#घोषणा DRCVPA		0x08	/* disable receiving physical address */
#घोषणा DRCVBC		0x04	/* disable receiving broadcasts */
#घोषणा ENXMT		0x02	/* enable transmitter */
#घोषणा ENRCV		0x01	/* enable receiver */

/* Bits in PLSCC */
#घोषणा XMTSEL		0x08	/* select DO+/DO- state when idle */
#घोषणा PORTSEL_AUI	0x00	/* select AUI port */
#घोषणा PORTSEL_10T	0x02	/* select 10Base-T port */
#घोषणा PORTSEL_DAI	0x04	/* select DAI port */
#घोषणा PORTSEL_GPSI	0x06	/* select GPSI port */
#घोषणा ENPLSIO		0x01	/* enable optional PLS I/O pins */

/* Bits in PHYCC */
#घोषणा LNKFL		0x80	/* reports 10Base-T link failure */
#घोषणा DLNKTST		0x40	/* disable 10Base-T link test */
#घोषणा REVPOL		0x20	/* 10Base-T receiver polarity reversed */
#घोषणा DAPC		0x10	/* disable स्वतः receiver polarity correction */
#घोषणा LRT		0x08	/* low receive threshold क्रम दीर्घ links */
#घोषणा ASEL		0x04	/* स्वतः-select AUI or 10Base-T port */
#घोषणा RWAKE		0x02	/* remote wake function */
#घोषणा AWAKE		0x01	/* स्वतः wake function */

/* Bits in IAC */
#घोषणा ADDRCHG		0x80	/* request address change */
#घोषणा PHYADDR		0x04	/* access physical address */
#घोषणा LOGADDR		0x02	/* access multicast filter */

/* Bits in UTR */
#घोषणा RTRE		0x80	/* reserved test रेजिस्टर enable. DON'T SET. */
#घोषणा RTRD		0x40	/* reserved test रेजिस्टर disable.  Sticky */
#घोषणा RPAC		0x20	/* accept runt packets */
#घोषणा FCOLL		0x10	/* क्रमce collision */
#घोषणा RCVFCSE		0x08	/* receive FCS enable */
#घोषणा LOOP_NONE	0x00	/* no loopback */
#घोषणा LOOP_EXT	0x02	/* बाह्यal loopback */
#घोषणा LOOP_INT	0x04	/* पूर्णांकernal loopback, excludes MENDEC */
#घोषणा LOOP_MENDEC	0x06	/* पूर्णांकernal loopback, includes MENDEC */
