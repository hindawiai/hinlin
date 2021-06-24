<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * drivers/aपंचांग/suni.h - S/UNI PHY driver
 */
 
/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */

#अगर_अघोषित DRIVER_ATM_SUNI_H
#घोषणा DRIVER_ATM_SUNI_H

#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांगioc.h>
#समावेश <linux/sonet.h>

/* SUNI रेजिस्टरs */

#घोषणा SUNI_MRI		0x00	/* Master Reset and Identity / Load
					   Meter */
#घोषणा SUNI_MC			0x01	/* Master Configuration */
#घोषणा SUNI_MIS		0x02	/* Master Interrupt Status */
			  /* no 0x03 */
#घोषणा SUNI_MCM		0x04	/* Master Clock Monitor */
#घोषणा SUNI_MCT		0x05	/* Master Control */
#घोषणा SUNI_CSCS		0x06	/* Clock Synthesis Control and Status */
#घोषणा SUNI_CRCS		0x07	/* Clock Recovery Control and Status */
			     /* 0x08-0x0F reserved */
#घोषणा SUNI_RSOP_CIE		0x10	/* RSOP Control/Interrupt Enable */
#घोषणा SUNI_RSOP_SIS		0x11	/* RSOP Status/Interrupt Status */
#घोषणा SUNI_RSOP_SBL		0x12	/* RSOP Section BIP-8 LSB */
#घोषणा SUNI_RSOP_SBM		0x13	/* RSOP Section BIP-8 MSB */
#घोषणा SUNI_TSOP_CTRL		0x14	/* TSOP Control */
#घोषणा SUNI_TSOP_DIAG		0x15	/* TSOP Diagnostic */
			     /* 0x16-0x17 reserved */
#घोषणा SUNI_RLOP_CS		0x18	/* RLOP Control/Status */
#घोषणा SUNI_RLOP_IES		0x19	/* RLOP Interrupt Enable/Status */
#घोषणा SUNI_RLOP_LBL		0x1A	/* RLOP Line BIP-8/24 LSB */
#घोषणा SUNI_RLOP_LB		0x1B	/* RLOP Line BIP-8/24 */
#घोषणा SUNI_RLOP_LBM		0x1C	/* RLOP Line BIP-8/24 MSB */
#घोषणा SUNI_RLOP_LFL		0x1D	/* RLOP Line FEBE LSB */
#घोषणा SUNI_RLOP_LF 		0x1E	/* RLOP Line FEBE */
#घोषणा SUNI_RLOP_LFM		0x1F	/* RLOP Line FEBE MSB */
#घोषणा SUNI_TLOP_CTRL		0x20	/* TLOP Control */
#घोषणा SUNI_TLOP_DIAG		0x21	/* TLOP Diagnostic */
			     /* 0x22-0x27 reserved */
#घोषणा SUNI_SSTB_CTRL		0x28
#घोषणा SUNI_RPOP_SC		0x30	/* RPOP Status/Control */
#घोषणा SUNI_RPOP_IS		0x31	/* RPOP Interrupt Status */
			     /* 0x32 reserved */
#घोषणा SUNI_RPOP_IE		0x33	/* RPOP Interrupt Enable */
			     /* 0x34-0x36 reserved */
#घोषणा SUNI_RPOP_PSL		0x37	/* RPOP Path Signal Label */
#घोषणा SUNI_RPOP_PBL		0x38	/* RPOP Path BIP-8 LSB */
#घोषणा SUNI_RPOP_PBM		0x39	/* RPOP Path BIP-8 MSB */
#घोषणा SUNI_RPOP_PFL		0x3A	/* RPOP Path FEBE LSB */
#घोषणा SUNI_RPOP_PFM		0x3B	/* RPOP Path FEBE MSB */
			     /* 0x3C reserved */
#घोषणा SUNI_RPOP_PBC		0x3D	/* RPOP Path BIP-8 Configuration */
#घोषणा SUNI_RPOP_RC		0x3D	/* RPOP Ring Control (PM5355) */
			     /* 0x3E-0x3F reserved */
#घोषणा SUNI_TPOP_CD		0x40	/* TPOP Control/Diagnostic */
#घोषणा SUNI_TPOP_PC		0x41	/* TPOP Poपूर्णांकer Control */
			     /* 0x42-0x44 reserved */
#घोषणा SUNI_TPOP_APL		0x45	/* TPOP Arbitrary Poपूर्णांकer LSB */
#घोषणा SUNI_TPOP_APM		0x46	/* TPOP Arbitrary Poपूर्णांकer MSB */
			     /* 0x47 reserved */
#घोषणा SUNI_TPOP_PSL		0x48	/* TPOP Path Signal Label */
#घोषणा SUNI_TPOP_PS		0x49	/* TPOP Path Status */
			     /* 0x4A-0x4F reserved */
#घोषणा SUNI_RACP_CS		0x50	/* RACP Control/Status */
#घोषणा SUNI_RACP_IES		0x51	/* RACP Interrupt Enable/Status */
#घोषणा SUNI_RACP_MHP		0x52	/* RACP Match Header Pattern */
#घोषणा SUNI_RACP_MHM		0x53	/* RACP Match Header Mask */
#घोषणा SUNI_RACP_CHEC		0x54	/* RACP Correctable HCS Error Count */
#घोषणा SUNI_RACP_UHEC		0x55	/* RACP Uncorrectable HCS Err Count */
#घोषणा SUNI_RACP_RCCL		0x56	/* RACP Receive Cell Counter LSB */
#घोषणा SUNI_RACP_RCC		0x57	/* RACP Receive Cell Counter */
#घोषणा SUNI_RACP_RCCM		0x58	/* RACP Receive Cell Counter MSB */
#घोषणा SUNI_RACP_CFG		0x59	/* RACP Configuration */
			     /* 0x5A-0x5F reserved */
#घोषणा SUNI_TACP_CS		0x60	/* TACP Control/Status */
#घोषणा SUNI_TACP_IUCHP		0x61	/* TACP Idle/Unasचिन्हित Cell Hdr Pat */
#घोषणा SUNI_TACP_IUCPOP	0x62	/* TACP Idle/Unasचिन्हित Cell Payload
					   Octet Pattern */
#घोषणा SUNI_TACP_FIFO		0x63	/* TACP FIFO Configuration */
#घोषणा SUNI_TACP_TCCL		0x64	/* TACP Transmit Cell Counter LSB */
#घोषणा SUNI_TACP_TCC		0x65	/* TACP Transmit Cell Counter */
#घोषणा SUNI_TACP_TCCM		0x66	/* TACP Transmit Cell Counter MSB */
#घोषणा SUNI_TACP_CFG		0x67	/* TACP Configuration */
#घोषणा SUNI_SPTB_CTRL		0x68	/* SPTB Control */
			     /* 0x69-0x7F reserved */
#घोषणा	SUNI_MT			0x80	/* Master Test */
			     /* 0x81-0xFF reserved */

/* SUNI रेजिस्टर values */


/* MRI is reg 0 */
#घोषणा SUNI_MRI_ID		0x0f	/* R, SUNI revision number */
#घोषणा SUNI_MRI_ID_SHIFT 	0
#घोषणा SUNI_MRI_TYPE		0x70	/* R, SUNI type (lite is 011) */
#घोषणा SUNI_MRI_TYPE_SHIFT 	4
#घोषणा SUNI_MRI_TYPE_PM5346	0x3	/* S/UNI 155 LITE */
#घोषणा SUNI_MRI_TYPE_PM5347	0x4	/* S/UNI 155 PLUS */
#घोषणा SUNI_MRI_TYPE_PM5350	0x7	/* S/UNI 155 ULTRA */
#घोषणा SUNI_MRI_TYPE_PM5355	0x1	/* S/UNI 622 */
#घोषणा SUNI_MRI_RESET		0x80	/* RW, reset & घातer करोwn chip
					   0: normal operation
					   1: reset & low घातer */

/* MCM is reg 0x4 */
#घोषणा SUNI_MCM_LLE		0x20	/* line loopback (PM5355) */
#घोषणा SUNI_MCM_DLE		0x10	/* diagnostic loopback (PM5355) */

/* MCT is reg 5 */
#घोषणा SUNI_MCT_LOOPT		0x01	/* RW, timing source, 0: from
					   TRCLK+/- */
#घोषणा SUNI_MCT_DLE		0x02	/* RW, diagnostic loopback */
#घोषणा SUNI_MCT_LLE		0x04	/* RW, line loopback */
#घोषणा SUNI_MCT_FIXPTR		0x20	/* RW, disable transmit payload poपूर्णांकer
					   adjusपंचांगents
					   0: payload ptr controlled by TPOP
					      ptr control reg
					   1: payload poपूर्णांकer fixed at 522 */
#घोषणा SUNI_MCT_LCDV		0x40	/* R, loss of cell delineation */
#घोषणा SUNI_MCT_LCDE		0x80	/* RW, loss of cell delineation
					   पूर्णांकerrupt (1: on) */
/* RSOP_CIE is reg 0x10 */
#घोषणा SUNI_RSOP_CIE_OOFE	0x01	/* RW, enable पूर्णांकerrupt on frame alarm
					   state change */
#घोषणा SUNI_RSOP_CIE_LOFE	0x02	/* RW, enable पूर्णांकerrupt on loss of
					   frame state change */
#घोषणा SUNI_RSOP_CIE_LOSE	0x04	/* RW, enable पूर्णांकerrupt on loss of
					   संकेत state change */
#घोषणा SUNI_RSOP_CIE_BIPEE	0x08	/* RW, enable पूर्णांकerrupt on section
					   BIP-8 error (B1) */
#घोषणा SUNI_RSOP_CIE_FOOF	0x20	/* W, क्रमce RSOP out of frame at next
					   boundary */
#घोषणा SUNI_RSOP_CIE_DDS	0x40	/* RW, disable scrambling */

/* RSOP_SIS is reg 0x11 */
#घोषणा SUNI_RSOP_SIS_OOFV	0x01	/* R, out of frame */
#घोषणा SUNI_RSOP_SIS_LOFV	0x02	/* R, loss of frame */
#घोषणा SUNI_RSOP_SIS_LOSV	0x04	/* R, loss of संकेत */
#घोषणा SUNI_RSOP_SIS_OOFI	0x08	/* R, out of frame पूर्णांकerrupt */
#घोषणा SUNI_RSOP_SIS_LOFI	0x10	/* R, loss of frame पूर्णांकerrupt */
#घोषणा SUNI_RSOP_SIS_LOSI	0x20	/* R, loss of संकेत पूर्णांकerrupt */
#घोषणा SUNI_RSOP_SIS_BIPEI	0x40	/* R, section BIP-8 पूर्णांकerrupt */

/* TSOP_CTRL is reg 0x14 */
#घोषणा SUNI_TSOP_CTRL_LAIS	0x01	/* insert alarm indication संकेत */
#घोषणा SUNI_TSOP_CTRL_DS	0x40	/* disable scrambling */

/* TSOP_DIAG is reg 0x15 */
#घोषणा SUNI_TSOP_DIAG_DFP	0x01	/* insert single bit error cont. */
#घोषणा SUNI_TSOP_DIAG_DBIP8	0x02	/* insert section BIP err (cont) */
#घोषणा SUNI_TSOP_DIAG_DLOS	0x04	/* set line to zero (loss of संकेत) */

/* TLOP_DIAG is reg 0x21 */
#घोषणा SUNI_TLOP_DIAG_DBIP	0x01	/* insert line BIP err (continuously) */

/* SSTB_CTRL is reg 0x28 */
#घोषणा SUNI_SSTB_CTRL_LEN16	0x01	/* path trace message length bit */

/* RPOP_RC is reg 0x3D (PM5355) */
#घोषणा SUNI_RPOP_RC_ENSS	0x40	/* enable size bit */

/* TPOP_DIAG is reg 0x40 */
#घोषणा SUNI_TPOP_DIAG_PAIS	0x01	/* insert STS path alarm ind (cont) */
#घोषणा SUNI_TPOP_DIAG_DB3	0x02	/* insert path BIP err (continuously) */

/* TPOP_APM is reg 0x46 */
#घोषणा SUNI_TPOP_APM_APTR	0x03	/* RW, arbitrary poपूर्णांकer, upper 2
					   bits */
#घोषणा SUNI_TPOP_APM_APTR_SHIFT 0
#घोषणा SUNI_TPOP_APM_S		0x0c	/* RW, "unused" bits of payload
					   poपूर्णांकer */
#घोषणा SUNI_TPOP_APM_S_SHIFT	2
#घोषणा SUNI_TPOP_APM_NDF	0xf0	 /* RW, NDF bits */
#घोषणा SUNI_TPOP_APM_NDF_SHIFT	4

#घोषणा SUNI_TPOP_S_SONET	0	/* set S bits to 00 */
#घोषणा SUNI_TPOP_S_SDH		2	/* set S bits to 10 */

/* RACP_IES is reg 0x51 */
#घोषणा SUNI_RACP_IES_FOVRI	0x02	/* R, FIFO overrun */
#घोषणा SUNI_RACP_IES_UHCSI	0x04	/* R, uncorrectable HCS error */
#घोषणा SUNI_RACP_IES_CHCSI	0x08	/* R, correctable HCS error */
#घोषणा SUNI_RACP_IES_OOCDI	0x10	/* R, change of cell delineation
					   state */
#घोषणा SUNI_RACP_IES_FIFOE	0x20	/* RW, enable FIFO overrun पूर्णांकerrupt */
#घोषणा SUNI_RACP_IES_HCSE	0x40	/* RW, enable HCS error पूर्णांकerrupt */
#घोषणा SUNI_RACP_IES_OOCDE	0x80	/* RW, enable cell delineation state
					   change पूर्णांकerrupt */

/* TACP_CS is reg 0x60 */
#घोषणा SUNI_TACP_CS_FIFORST	0x01	/* RW, reset transmit FIFO (sticky) */
#घोषणा SUNI_TACP_CS_DSCR	0x02	/* RW, disable payload scrambling */
#घोषणा SUNI_TACP_CS_HCAADD	0x04	/* RW, add coset polynomial to HCS */
#घोषणा SUNI_TACP_CS_DHCS	0x10	/* RW, insert HCS errors */
#घोषणा SUNI_TACP_CS_FOVRI	0x20	/* R, FIFO overrun */
#घोषणा SUNI_TACP_CS_TSOCI	0x40	/* R, TSOC input high */
#घोषणा SUNI_TACP_CS_FIFOE	0x80	/* RW, enable FIFO overrun पूर्णांकerrupt */

/* TACP_IUCHP is reg 0x61 */
#घोषणा SUNI_TACP_IUCHP_CLP	0x01	/* RW, 8th bit of 4th octet of i/u
					   pattern */
#घोषणा SUNI_TACP_IUCHP_PTI	0x0e	/* RW, 5th-7th bits of 4th octet of i/u
					   pattern */
#घोषणा SUNI_TACP_IUCHP_PTI_SHIFT 1
#घोषणा SUNI_TACP_IUCHP_GFC	0xf0	/* RW, 1st-4th bits of 1st octet of i/u
					   pattern */
#घोषणा SUNI_TACP_IUCHP_GFC_SHIFT 4

/* SPTB_CTRL is reg 0x68 */
#घोषणा SUNI_SPTB_CTRL_LEN16	0x01	/* path trace message length */

/* MT is reg 0x80 */
#घोषणा SUNI_MT_HIZIO		0x01	/* RW, all but data bus & MP पूर्णांकerface
					   tri-state */
#घोषणा SUNI_MT_HIZDATA		0x02	/* W, also tri-state data bus */
#घोषणा SUNI_MT_IOTST		0x04	/* RW, enable test mode */
#घोषणा SUNI_MT_DBCTRL		0x08	/* W, control data bus by CSB pin */
#घोषणा SUNI_MT_PMCTST		0x10	/* W, PMC test mode */
#घोषणा SUNI_MT_DS27_53		0x80	/* RW, select between 8- or 16- bit */


#घोषणा SUNI_IDLE_PATTERN       0x6a    /* idle pattern */


#अगर_घोषित __KERNEL__
काष्ठा suni_priv अणु
	काष्ठा k_sonet_stats sonet_stats;	/* link diagnostics */
	पूर्णांक loop_mode;				/* loopback mode */
	पूर्णांक type;				/* phy type */
	काष्ठा aपंचांग_dev *dev;			/* device back-poपूर्णांकer */
	काष्ठा suni_priv *next;			/* next SUNI */
पूर्ण;

पूर्णांक suni_init(काष्ठा aपंचांग_dev *dev);
#पूर्ण_अगर

#पूर्ण_अगर
