<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * isar.h   ISAR (Siemens PSB 7110) specअगरic defines
 *
 * Author Karsten Keil (keil@isdn4linux.de)
 *
 * Copyright 2009  by Karsten Keil <keil@isdn4linux.de>
 */

#समावेश "iohelper.h"

काष्ठा isar_hw;

काष्ठा isar_ch अणु
	काष्ठा bchannel		bch;
	काष्ठा isar_hw		*is;
	काष्ठा समयr_list	fसमयr;
	u8			nr;
	u8			dpath;
	u8			mml;
	u8			state;
	u8			cmd;
	u8			mod;
	u8			newcmd;
	u8			newmod;
	u8			try_mod;
	u8			conmsg[16];
पूर्ण;

काष्ठा isar_hw अणु
	काष्ठा	isar_ch	ch[2];
	व्योम		*hw;
	spinlock_t	*hwlock;	/* lock HW access */
	अक्षर		*name;
	काष्ठा module	*owner;
	पढ़ो_reg_func	*पढ़ो_reg;
	ग_लिखो_reg_func	*ग_लिखो_reg;
	fअगरo_func	*पढ़ो_fअगरo;
	fअगरo_func	*ग_लिखो_fअगरo;
	पूर्णांक		(*ctrl)(व्योम *, u32, u_दीर्घ);
	व्योम		(*release)(काष्ठा isar_hw *);
	पूर्णांक		(*init)(काष्ठा isar_hw *);
	पूर्णांक		(*खोलो)(काष्ठा isar_hw *, काष्ठा channel_req *);
	पूर्णांक		(*firmware)(काष्ठा isar_hw *, स्थिर u8 *, पूर्णांक);
	अचिन्हित दीर्घ	Flags;
	पूर्णांक		version;
	u8		bstat;
	u8		iis;
	u8		cmsb;
	u8		clsb;
	u8		buf[256];
	u8		log[256];
पूर्ण;

#घोषणा ISAR_IRQMSK	0x04
#घोषणा ISAR_IRQSTA	0x04
#घोषणा ISAR_IRQBIT	0x75
#घोषणा ISAR_CTRL_H	0x61
#घोषणा ISAR_CTRL_L	0x60
#घोषणा ISAR_IIS	0x58
#घोषणा ISAR_IIA	0x58
#घोषणा ISAR_HIS	0x50
#घोषणा ISAR_HIA	0x50
#घोषणा ISAR_MBOX	0x4c
#घोषणा ISAR_WADR	0x4a
#घोषणा ISAR_RADR	0x48

#घोषणा ISAR_HIS_VNR		0x14
#घोषणा ISAR_HIS_DKEY		0x02
#घोषणा ISAR_HIS_FIRM		0x1e
#घोषणा ISAR_HIS_STDSP		0x08
#घोषणा ISAR_HIS_DIAG		0x05
#घोषणा ISAR_HIS_P0CFG		0x3c
#घोषणा ISAR_HIS_P12CFG		0x24
#घोषणा ISAR_HIS_SARTCFG	0x25
#घोषणा ISAR_HIS_PUMPCFG	0x26
#घोषणा ISAR_HIS_PUMPCTRL	0x2a
#घोषणा ISAR_HIS_IOM2CFG	0x27
#घोषणा ISAR_HIS_IOM2REQ	0x07
#घोषणा ISAR_HIS_IOM2CTRL	0x2b
#घोषणा ISAR_HIS_BSTREQ		0x0c
#घोषणा ISAR_HIS_PSTREQ		0x0e
#घोषणा ISAR_HIS_SDATA		0x20
#घोषणा ISAR_HIS_DPS1		0x40
#घोषणा ISAR_HIS_DPS2		0x80
#घोषणा SET_DPS(x)		((x << 6) & 0xc0)

#घोषणा ISAR_IIS_MSCMSD		0x3f
#घोषणा ISAR_IIS_VNR		0x15
#घोषणा ISAR_IIS_DKEY		0x03
#घोषणा ISAR_IIS_FIRM		0x1f
#घोषणा ISAR_IIS_STDSP		0x09
#घोषणा ISAR_IIS_DIAG		0x25
#घोषणा ISAR_IIS_GSTEV		0x00
#घोषणा ISAR_IIS_BSTEV		0x28
#घोषणा ISAR_IIS_BSTRSP		0x2c
#घोषणा ISAR_IIS_PSTRSP		0x2e
#घोषणा ISAR_IIS_PSTEV		0x2a
#घोषणा ISAR_IIS_IOM2RSP	0x27
#घोषणा ISAR_IIS_RDATA		0x20
#घोषणा ISAR_IIS_INVMSG		0x3f

#घोषणा ISAR_CTRL_SWVER	0x10
#घोषणा ISAR_CTRL_STST	0x40

#घोषणा ISAR_MSG_HWVER	0x20

#घोषणा ISAR_DP1_USE	1
#घोषणा ISAR_DP2_USE	2
#घोषणा ISAR_RATE_REQ	3

#घोषणा PMOD_DISABLE	0
#घोषणा PMOD_FAX	1
#घोषणा PMOD_DATAMODEM	2
#घोषणा PMOD_HALFDUPLEX	3
#घोषणा PMOD_V110	4
#घोषणा PMOD_DTMF	5
#घोषणा PMOD_DTMF_TRANS	6
#घोषणा PMOD_BYPASS	7

#घोषणा PCTRL_ORIG	0x80
#घोषणा PV32P2_V23R	0x40
#घोषणा PV32P2_V22A	0x20
#घोषणा PV32P2_V22B	0x10
#घोषणा PV32P2_V22C	0x08
#घोषणा PV32P2_V21	0x02
#घोषणा PV32P2_BEL	0x01

/* LSB MSB in ISAR करोc wrong !!! Arghhh */
#घोषणा PV32P3_AMOD	0x80
#घोषणा PV32P3_V32B	0x02
#घोषणा PV32P3_V23B	0x01
#घोषणा PV32P4_48	0x11
#घोषणा PV32P5_48	0x05
#घोषणा PV32P4_UT48	0x11
#घोषणा PV32P5_UT48	0x0d
#घोषणा PV32P4_96	0x11
#घोषणा PV32P5_96	0x03
#घोषणा PV32P4_UT96	0x11
#घोषणा PV32P5_UT96	0x0f
#घोषणा PV32P4_B96	0x91
#घोषणा PV32P5_B96	0x0b
#घोषणा PV32P4_UTB96	0xd1
#घोषणा PV32P5_UTB96	0x0f
#घोषणा PV32P4_120	0xb1
#घोषणा PV32P5_120	0x09
#घोषणा PV32P4_UT120	0xf1
#घोषणा PV32P5_UT120	0x0f
#घोषणा PV32P4_144	0x99
#घोषणा PV32P5_144	0x09
#घोषणा PV32P4_UT144	0xf9
#घोषणा PV32P5_UT144	0x0f
#घोषणा PV32P6_CTN	0x01
#घोषणा PV32P6_ATN	0x02

#घोषणा PFAXP2_CTN	0x01
#घोषणा PFAXP2_ATN	0x04

#घोषणा PSEV_10MS_TIMER	0x02
#घोषणा PSEV_CON_ON	0x18
#घोषणा PSEV_CON_OFF	0x19
#घोषणा PSEV_V24_OFF	0x20
#घोषणा PSEV_CTS_ON	0x21
#घोषणा PSEV_CTS_OFF	0x22
#घोषणा PSEV_DCD_ON	0x23
#घोषणा PSEV_DCD_OFF	0x24
#घोषणा PSEV_DSR_ON	0x25
#घोषणा PSEV_DSR_OFF	0x26
#घोषणा PSEV_REM_RET	0xcc
#घोषणा PSEV_REM_REN	0xcd
#घोषणा PSEV_GSTN_CLR	0xd4

#घोषणा PSEV_RSP_READY	0xbc
#घोषणा PSEV_LINE_TX_H	0xb3
#घोषणा PSEV_LINE_TX_B	0xb2
#घोषणा PSEV_LINE_RX_H	0xb1
#घोषणा PSEV_LINE_RX_B	0xb0
#घोषणा PSEV_RSP_CONN	0xb5
#घोषणा PSEV_RSP_DISC	0xb7
#घोषणा PSEV_RSP_FCERR	0xb9
#घोषणा PSEV_RSP_SILDET	0xbe
#घोषणा PSEV_RSP_SILOFF	0xab
#घोषणा PSEV_FLAGS_DET	0xba

#घोषणा PCTRL_CMD_TDTMF	0x5a

#घोषणा PCTRL_CMD_FTH	0xa7
#घोषणा PCTRL_CMD_FRH	0xa5
#घोषणा PCTRL_CMD_FTM	0xa8
#घोषणा PCTRL_CMD_FRM	0xa6
#घोषणा PCTRL_CMD_SILON	0xac
#घोषणा PCTRL_CMD_CONT	0xa2
#घोषणा PCTRL_CMD_ESC	0xa4
#घोषणा PCTRL_CMD_SILOFF 0xab
#घोषणा PCTRL_CMD_HALT	0xa9

#घोषणा PCTRL_LOC_RET	0xcf
#घोषणा PCTRL_LOC_REN	0xce

#घोषणा SMODE_DISABLE	0
#घोषणा SMODE_V14	2
#घोषणा SMODE_HDLC	3
#घोषणा SMODE_BINARY	4
#घोषणा SMODE_FSK_V14	5

#घोषणा SCTRL_HDMC_BOTH	0x00
#घोषणा SCTRL_HDMC_DTX	0x80
#घोषणा SCTRL_HDMC_DRX	0x40
#घोषणा S_P1_OVSP	0x40
#घोषणा S_P1_SNP	0x20
#घोषणा S_P1_EOP	0x10
#घोषणा S_P1_EDP	0x08
#घोषणा S_P1_NSB	0x04
#घोषणा S_P1_CHS_8	0x03
#घोषणा S_P1_CHS_7	0x02
#घोषणा S_P1_CHS_6	0x01
#घोषणा S_P1_CHS_5	0x00

#घोषणा S_P2_BFT_DEF	0x10

#घोषणा IOM_CTRL_ENA	0x80
#घोषणा IOM_CTRL_NOPCM	0x00
#घोषणा IOM_CTRL_ALAW	0x02
#घोषणा IOM_CTRL_ULAW	0x04
#घोषणा IOM_CTRL_RCV	0x01

#घोषणा IOM_P1_TXD	0x10

#घोषणा HDLC_FED	0x40
#घोषणा HDLC_FSD	0x20
#घोषणा HDLC_FST	0x20
#घोषणा HDLC_ERROR	0x1c
#घोषणा HDLC_ERR_FAD	0x10
#घोषणा HDLC_ERR_RER	0x08
#घोषणा HDLC_ERR_CER	0x04
#घोषणा SART_NMD	0x01

#घोषणा BSTAT_RDM0	0x1
#घोषणा BSTAT_RDM1	0x2
#घोषणा BSTAT_RDM2	0x4
#घोषणा BSTAT_RDM3	0x8
#घोषणा BSTEV_TBO	0x1f
#घोषणा BSTEV_RBO	0x2f

/* FAX State Machine */
#घोषणा STFAX_शून्य	0
#घोषणा STFAX_READY	1
#घोषणा STFAX_LINE	2
#घोषणा STFAX_CONT	3
#घोषणा STFAX_ACTIV	4
#घोषणा STFAX_ESCAPE	5
#घोषणा STFAX_SILDET	6

बाह्य u32 mISDNisar_init(काष्ठा isar_hw *, व्योम *);
बाह्य व्योम mISDNisar_irq(काष्ठा isar_hw *);
