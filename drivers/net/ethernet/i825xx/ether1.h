<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/acorn/net/ether1.h
 *
 *  Copyright (C) 1996 Russell King
 *
 *  Network driver क्रम Acorn Ether1 cards.
 */

#अगर_अघोषित _LINUX_ether1_H
#घोषणा _LINUX_ether1_H

#अगर_घोषित __ETHER1_C
/* use 0 क्रम production, 1 क्रम verअगरication, >2 क्रम debug */
#अगर_अघोषित NET_DEBUG
#घोषणा NET_DEBUG 0
#पूर्ण_अगर

#घोषणा priv(dev)	((काष्ठा ether1_priv *)netdev_priv(dev))

/* Page रेजिस्टर */
#घोषणा REG_PAGE	(priv(dev)->base + 0x0000)

/* Control रेजिस्टर */
#घोषणा REG_CONTROL	(priv(dev)->base + 0x0004)
#घोषणा CTRL_RST	0x01
#घोषणा CTRL_LOOPBACK	0x02
#घोषणा CTRL_CA		0x04
#घोषणा CTRL_ACK	0x08

#घोषणा ETHER1_RAM	(priv(dev)->base + 0x2000)

/* HW address */
#घोषणा IDPROM_ADDRESS	(priv(dev)->base + 0x0024)

काष्ठा ether1_priv अणु
	व्योम __iomem *base;
	अचिन्हित पूर्णांक tx_link;
	अचिन्हित पूर्णांक tx_head;
	अस्थिर अचिन्हित पूर्णांक tx_tail;
	अस्थिर अचिन्हित पूर्णांक rx_head;
	अस्थिर अचिन्हित पूर्णांक rx_tail;
	अचिन्हित अक्षर bus_type;
	अचिन्हित अक्षर resetting;
	अचिन्हित अक्षर initialising : 1;
	अचिन्हित अक्षर restart      : 1;
पूर्ण;

#घोषणा I82586_शून्य (-1)

प्रकार काष्ठा अणु /* tdr */
	अचिन्हित लघु tdr_status;
	अचिन्हित लघु tdr_command;
	अचिन्हित लघु tdr_link;
	अचिन्हित लघु tdr_result;
#घोषणा TDR_TIME	(0x7ff)
#घोषणा TDR_SHORT	(1 << 12)
#घोषणा TDR_OPEN	(1 << 13)
#घोषणा TDR_XCVRPROB	(1 << 14)
#घोषणा TDR_LNKOK	(1 << 15)
पूर्ण tdr_t;

प्रकार काष्ठा अणु /* transmit */
	अचिन्हित लघु tx_status;
	अचिन्हित लघु tx_command;
	अचिन्हित लघु tx_link;
	अचिन्हित लघु tx_tbकरोffset;
पूर्ण tx_t;

प्रकार काष्ठा अणु /* tbd */
	अचिन्हित लघु tbd_opts;
#घोषणा TBD_CNT		(0x3fff)
#घोषणा TBD_EOL		(1 << 15)
	अचिन्हित लघु tbd_link;
	अचिन्हित लघु tbd_bufl;
	अचिन्हित लघु tbd_bufh;
पूर्ण tbd_t;

प्रकार काष्ठा अणु /* rfd */
	अचिन्हित लघु rfd_status;
#घोषणा RFD_NOखातापूर्ण	(1 << 6)
#घोषणा RFD_FRAMESHORT	(1 << 7)
#घोषणा RFD_DMAOVRN	(1 << 8)
#घोषणा RFD_NORESOURCES	(1 << 9)
#घोषणा RFD_ALIGNERROR	(1 << 10)
#घोषणा RFD_CRCERROR	(1 << 11)
#घोषणा RFD_OK		(1 << 13)
#घोषणा RFD_FDCONSUMED	(1 << 14)
#घोषणा RFD_COMPLETE	(1 << 15)
	अचिन्हित लघु rfd_command;
#घोषणा RFD_CMDSUSPEND	(1 << 14)
#घोषणा RFD_CMDEL	(1 << 15)
	अचिन्हित लघु rfd_link;
	अचिन्हित लघु rfd_rbकरोffset;
	अचिन्हित अक्षर  rfd_dest[6];
	अचिन्हित अक्षर  rfd_src[6];
	अचिन्हित लघु rfd_len;
पूर्ण rfd_t;

प्रकार काष्ठा अणु /* rbd */
	अचिन्हित लघु rbd_status;
#घोषणा RBD_ACNT	(0x3fff)
#घोषणा RBD_ACNTVALID	(1 << 14)
#घोषणा RBD_खातापूर्ण		(1 << 15)
	अचिन्हित लघु rbd_link;
	अचिन्हित लघु rbd_bufl;
	अचिन्हित लघु rbd_bufh;
	अचिन्हित लघु rbd_len;
पूर्ण rbd_t;

प्रकार काष्ठा अणु /* nop */
	अचिन्हित लघु nop_status;
	अचिन्हित लघु nop_command;
	अचिन्हित लघु nop_link;
पूर्ण nop_t;

प्रकार काष्ठा अणु /* set multicast */
	अचिन्हित लघु mc_status;
	अचिन्हित लघु mc_command;
	अचिन्हित लघु mc_link;
	अचिन्हित लघु mc_cnt;
	अचिन्हित अक्षर  mc_addrs[1][6];
पूर्ण mc_t;

प्रकार काष्ठा अणु /* set address */
	अचिन्हित लघु sa_status;
	अचिन्हित लघु sa_command;
	अचिन्हित लघु sa_link;
	अचिन्हित अक्षर  sa_addr[6];
पूर्ण sa_t;

प्रकार काष्ठा अणु /* config command */
	अचिन्हित लघु cfg_status;
	अचिन्हित लघु cfg_command;
	अचिन्हित लघु cfg_link;
	अचिन्हित अक्षर  cfg_bytecnt;	/* size foll data: 4 - 12		 */
	अचिन्हित अक्षर  cfg_fअगरolim;	/* FIFO threshold			 */
	अचिन्हित अक्षर  cfg_byte8;
#घोषणा CFG8_SRDY	(1 << 6)
#घोषणा CFG8_SAVEBADF	(1 << 7)
	अचिन्हित अक्षर  cfg_byte9;
#घोषणा CFG9_ADDRLEN(x)	(x)
#घोषणा CFG9_ADDRLENBUF	(1 << 3)
#घोषणा CFG9_PREAMB2	(0 << 4)
#घोषणा CFG9_PREAMB4	(1 << 4)
#घोषणा CFG9_PREAMB8	(2 << 4)
#घोषणा CFG9_PREAMB16	(3 << 4)
#घोषणा CFG9_ILOOPBACK	(1 << 6)
#घोषणा CFG9_ELOOPBACK	(1 << 7)
	अचिन्हित अक्षर  cfg_byte10;
#घोषणा CFG10_LINPRI(x)	(x)
#घोषणा CFG10_ACR(x)	(x << 4)
#घोषणा CFG10_BOFMET	(1 << 7)
	अचिन्हित अक्षर  cfg_अगरs;
	अचिन्हित अक्षर  cfg_slotl;
	अचिन्हित अक्षर  cfg_byte13;
#घोषणा CFG13_SLOTH(x)	(x)
#घोषणा CFG13_RETRY(x)	(x << 4)
	अचिन्हित अक्षर  cfg_byte14;
#घोषणा CFG14_PROMISC	(1 << 0)
#घोषणा CFG14_DISBRD	(1 << 1)
#घोषणा CFG14_MANCH	(1 << 2)
#घोषणा CFG14_TNCRS	(1 << 3)
#घोषणा CFG14_NOCRC	(1 << 4)
#घोषणा CFG14_CRC16	(1 << 5)
#घोषणा CFG14_BTSTF	(1 << 6)
#घोषणा CFG14_FLGPAD	(1 << 7)
	अचिन्हित अक्षर  cfg_byte15;
#घोषणा CFG15_CSTF(x)	(x)
#घोषणा CFG15_ICSS	(1 << 3)
#घोषणा CFG15_CDTF(x)	(x << 4)
#घोषणा CFG15_ICDS	(1 << 7)
	अचिन्हित लघु cfg_minfrmlen;
पूर्ण cfg_t;

प्रकार काष्ठा अणु /* scb */
	अचिन्हित लघु scb_status;	/* status of 82586			*/
#घोषणा SCB_STRXMASK		(7 << 4)	/* Receive unit status		*/
#घोषणा SCB_STRXIDLE		(0 << 4)	/* Idle				*/
#घोषणा SCB_STRXSUSP		(1 << 4)	/* Suspended			*/
#घोषणा SCB_STRXNRES		(2 << 4)	/* No resources			*/
#घोषणा SCB_STRXRDY		(4 << 4)	/* Ready			*/
#घोषणा SCB_STCUMASK		(7 << 8)	/* Command unit status		*/
#घोषणा SCB_STCUIDLE		(0 << 8)	/* Idle				*/
#घोषणा SCB_STCUSUSP		(1 << 8)	/* Suspended			*/
#घोषणा SCB_STCUACTV		(2 << 8)	/* Active			*/
#घोषणा SCB_STRNR		(1 << 12)	/* Receive unit not पढ़ोy	*/
#घोषणा SCB_STCNA		(1 << 13)	/* Command unit not पढ़ोy	*/
#घोषणा SCB_STFR		(1 << 14)	/* Frame received		*/
#घोषणा SCB_STCX		(1 << 15)	/* Command completed		*/
	अचिन्हित लघु scb_command;	/* Next command				*/
#घोषणा SCB_CMDRXSTART		(1 << 4)	/* Start (at rfa_offset)	*/
#घोषणा SCB_CMDRXRESUME		(2 << 4)	/* Resume reception		*/
#घोषणा SCB_CMDRXSUSPEND	(3 << 4)	/* Suspend reception		*/
#घोषणा SCB_CMDRXABORT		(4 << 4)	/* Abort reception		*/
#घोषणा SCB_CMDCUCSTART		(1 << 8)	/* Start (at cbl_offset)	*/
#घोषणा SCB_CMDCUCRESUME	(2 << 8)	/* Resume execution		*/
#घोषणा SCB_CMDCUCSUSPEND	(3 << 8)	/* Suspend execution		*/
#घोषणा SCB_CMDCUCABORT		(4 << 8)	/* Abort execution		*/
#घोषणा SCB_CMDACKRNR		(1 << 12)	/* Ack RU not पढ़ोy		*/
#घोषणा SCB_CMDACKCNA		(1 << 13)	/* Ack CU not पढ़ोy		*/
#घोषणा SCB_CMDACKFR		(1 << 14)	/* Ack Frame received		*/
#घोषणा SCB_CMDACKCX		(1 << 15)	/* Ack Command complete		*/
	अचिन्हित लघु scb_cbl_offset;	/* Offset of first command unit		*/
	अचिन्हित लघु scb_rfa_offset;	/* Offset of first receive frame area	*/
	अचिन्हित लघु scb_crc_errors;	/* Properly aligned frame with CRC error*/
	अचिन्हित लघु scb_aln_errors;	/* Misaligned frames			*/
	अचिन्हित लघु scb_rsc_errors;	/* Frames lost due to no space		*/
	अचिन्हित लघु scb_ovn_errors;	/* Frames lost due to slow bus		*/
पूर्ण scb_t;

प्रकार काष्ठा अणु /* iscp */
	अचिन्हित लघु iscp_busy;	/* set by CPU beक्रमe CA			*/
	अचिन्हित लघु iscp_offset;	/* offset of SCB			*/
	अचिन्हित लघु iscp_basel;	/* base of SCB				*/
	अचिन्हित लघु iscp_baseh;
पूर्ण iscp_t;

    /* this address must be 0xfff6 */
प्रकार काष्ठा अणु /* scp */
	अचिन्हित लघु scp_sysbus;	/* bus size */
#घोषणा SCP_SY_16BBUS	0x00
#घोषणा SCP_SY_8BBUS	0x01
	अचिन्हित लघु scp_junk[2];	/* junk */
	अचिन्हित लघु scp_iscpl;	/* lower 16 bits of iscp */
	अचिन्हित लघु scp_iscph;	/* upper 16 bits of iscp */
पूर्ण scp_t;

/* commands */
#घोषणा CMD_NOP			0
#घोषणा CMD_SETADDRESS		1
#घोषणा CMD_CONFIG		2
#घोषणा CMD_SETMULTICAST	3
#घोषणा CMD_TX			4
#घोषणा CMD_TDR			5
#घोषणा CMD_DUMP		6
#घोषणा CMD_DIAGNOSE		7

#घोषणा CMD_MASK		7

#घोषणा CMD_INTR		(1 << 13)
#घोषणा CMD_SUSP		(1 << 14)
#घोषणा CMD_EOL			(1 << 15)

#घोषणा STAT_COLLISIONS		(15)
#घोषणा STAT_COLLEXCESSIVE	(1 << 5)
#घोषणा STAT_COLLAFTERTX	(1 << 6)
#घोषणा STAT_TXDEFERRED		(1 << 7)
#घोषणा STAT_TXSLOWDMA		(1 << 8)
#घोषणा STAT_TXLOSTCTS		(1 << 9)
#घोषणा STAT_NOCARRIER		(1 << 10)
#घोषणा STAT_FAIL		(1 << 11)
#घोषणा STAT_ABORTED		(1 << 12)
#घोषणा STAT_OK			(1 << 13)
#घोषणा STAT_BUSY		(1 << 14)
#घोषणा STAT_COMPLETE		(1 << 15)
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * Ether1 card definitions:
 *
 * FAST accesses:
 *	+0	Page रेजिस्टर
 * 			16 pages
 *	+4	Control
 *			'1' = reset
 *			'2' = loopback
 *			'4' = CA
 *			'8' = पूर्णांक ack
 *
 * RAM at address + 0x2000
 * Pod. Prod id = 3
 * Words after ID block [base + 8 words]
 *	+0 pcb issue (0x0c and 0xf3 invalid)
 *	+1 - +6 eth hw address
 */
