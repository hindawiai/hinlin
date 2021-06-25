<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ca91c042.h
 *
 * Support क्रम the Tundra Universe 1 and Universe II VME bridge chips
 *
 * Author: Tom Armistead
 * Updated by Ajit Prem
 * Copyright 2004 Motorola Inc.
 *
 * Further updated by Martyn Welch <martyn.welch@ge.com>
 * Copyright 2009 GE Intelligent Platक्रमms Embedded Systems, Inc.
 *
 * Derived from ca91c042.h by Michael Wyrick
 */

#अगर_अघोषित _CA91CX42_H
#घोषणा _CA91CX42_H

#अगर_अघोषित	PCI_VENDOR_ID_TUNDRA
#घोषणा	PCI_VENDOR_ID_TUNDRA 0x10e3
#पूर्ण_अगर

#अगर_अघोषित	PCI_DEVICE_ID_TUNDRA_CA91C142
#घोषणा	PCI_DEVICE_ID_TUNDRA_CA91C142 0x0000
#पूर्ण_अगर

/*
 *  Define the number of each that the CA91C142 supports.
 */
#घोषणा CA91C142_MAX_MASTER		8	/* Max Master Winकरोws */
#घोषणा CA91C142_MAX_SLAVE		8	/* Max Slave Winकरोws */
#घोषणा CA91C142_MAX_DMA		1	/* Max DMA Controllers */
#घोषणा CA91C142_MAX_MAILBOX		4	/* Max Mail Box रेजिस्टरs */

/* Structure used to hold driver specअगरic inक्रमmation */
काष्ठा ca91cx42_driver अणु
	व्योम __iomem *base;	/* Base Address of device रेजिस्टरs */
	रुको_queue_head_t dma_queue;
	रुको_queue_head_t iack_queue;
	रुको_queue_head_t mbox_queue;
	व्योम (*lm_callback[4])(व्योम *);	/* Called in पूर्णांकerrupt handler */
	व्योम *lm_data[4];
	व्योम *crcsr_kernel;
	dma_addr_t crcsr_bus;
	काष्ठा mutex vme_rmw;		/* Only one RMW cycle at a समय */
	काष्ठा mutex vme_पूर्णांक;		/*
					 * Only one VME पूर्णांकerrupt can be
					 * generated at a समय, provide locking
					 */
पूर्ण;

/* See Page 2-77 in the Universe User Manual */
काष्ठा ca91cx42_dma_descriptor अणु
	अचिन्हित पूर्णांक dctl;      /* DMA Control */
	अचिन्हित पूर्णांक dtbc;      /* Transfer Byte Count */
	अचिन्हित पूर्णांक dla;       /* PCI Address */
	अचिन्हित पूर्णांक res1;      /* Reserved */
	अचिन्हित पूर्णांक dva;       /* Vme Address */
	अचिन्हित पूर्णांक res2;      /* Reserved */
	अचिन्हित पूर्णांक dcpp;      /* Poपूर्णांकer to Numed Cmd Packet with rPN */
	अचिन्हित पूर्णांक res3;      /* Reserved */
पूर्ण;

काष्ठा ca91cx42_dma_entry अणु
	काष्ठा ca91cx42_dma_descriptor descriptor;
	काष्ठा list_head list;
पूर्ण;

/* Universe Register Offsets */
/* general PCI configuration रेजिस्टरs */
#घोषणा CA91CX42_PCI_ID		0x000
#घोषणा CA91CX42_PCI_CSR	0x004
#घोषणा CA91CX42_PCI_CLASS	0x008
#घोषणा CA91CX42_PCI_MISC0	0x00C
#घोषणा CA91CX42_PCI_BS		0x010
#घोषणा CA91CX42_PCI_MISC1	0x03C

#घोषणा LSI0_CTL		0x0100
#घोषणा LSI0_BS			0x0104
#घोषणा LSI0_BD			0x0108
#घोषणा LSI0_TO			0x010C

#घोषणा LSI1_CTL		0x0114
#घोषणा LSI1_BS			0x0118
#घोषणा LSI1_BD			0x011C
#घोषणा LSI1_TO			0x0120

#घोषणा LSI2_CTL		0x0128
#घोषणा LSI2_BS			0x012C
#घोषणा LSI2_BD			0x0130
#घोषणा LSI2_TO			0x0134

#घोषणा LSI3_CTL		0x013C
#घोषणा LSI3_BS			0x0140
#घोषणा LSI3_BD			0x0144
#घोषणा LSI3_TO			0x0148

#घोषणा LSI4_CTL		0x01A0
#घोषणा LSI4_BS			0x01A4
#घोषणा LSI4_BD			0x01A8
#घोषणा LSI4_TO			0x01AC

#घोषणा LSI5_CTL		0x01B4
#घोषणा LSI5_BS			0x01B8
#घोषणा LSI5_BD			0x01BC
#घोषणा LSI5_TO			0x01C0

#घोषणा LSI6_CTL		0x01C8
#घोषणा LSI6_BS			0x01CC
#घोषणा LSI6_BD			0x01D0
#घोषणा LSI6_TO			0x01D4

#घोषणा LSI7_CTL		0x01DC
#घोषणा LSI7_BS			0x01E0
#घोषणा LSI7_BD			0x01E4
#घोषणा LSI7_TO			0x01E8

अटल स्थिर पूर्णांक CA91CX42_LSI_CTL[] = अणु LSI0_CTL, LSI1_CTL, LSI2_CTL, LSI3_CTL,
				LSI4_CTL, LSI5_CTL, LSI6_CTL, LSI7_CTL पूर्ण;

अटल स्थिर पूर्णांक CA91CX42_LSI_BS[] = अणु LSI0_BS, LSI1_BS, LSI2_BS, LSI3_BS,
				LSI4_BS, LSI5_BS, LSI6_BS, LSI7_BS पूर्ण;

अटल स्थिर पूर्णांक CA91CX42_LSI_BD[] = अणु LSI0_BD, LSI1_BD, LSI2_BD, LSI3_BD,
				LSI4_BD, LSI5_BD, LSI6_BD, LSI7_BD पूर्ण;

अटल स्थिर पूर्णांक CA91CX42_LSI_TO[] = अणु LSI0_TO, LSI1_TO, LSI2_TO, LSI3_TO,
				LSI4_TO, LSI5_TO, LSI6_TO, LSI7_TO पूर्ण;

#घोषणा SCYC_CTL		0x0170
#घोषणा SCYC_ADDR		0x0174
#घोषणा SCYC_EN			0x0178
#घोषणा SCYC_CMP		0x017C
#घोषणा SCYC_SWP		0x0180
#घोषणा LMISC			0x0184
#घोषणा SLSI		        0x0188
#घोषणा L_CMDERR		0x018C
#घोषणा LAERR		        0x0190

#घोषणा DCTL		        0x0200
#घोषणा DTBC		        0x0204
#घोषणा DLA			0x0208
#घोषणा DVA			0x0210
#घोषणा DCPP		        0x0218
#घोषणा DGCS		        0x0220
#घोषणा D_LLUE			0x0224

#घोषणा LINT_EN			0x0300
#घोषणा LINT_STAT		0x0304
#घोषणा LINT_MAP0		0x0308
#घोषणा LINT_MAP1		0x030C
#घोषणा VINT_EN			0x0310
#घोषणा VINT_STAT		0x0314
#घोषणा VINT_MAP0		0x0318
#घोषणा VINT_MAP1		0x031C
#घोषणा STATID			0x0320

#घोषणा V1_STATID		0x0324
#घोषणा V2_STATID		0x0328
#घोषणा V3_STATID		0x032C
#घोषणा V4_STATID		0x0330
#घोषणा V5_STATID		0x0334
#घोषणा V6_STATID		0x0338
#घोषणा V7_STATID		0x033C

अटल स्थिर पूर्णांक CA91CX42_V_STATID[8] = अणु 0, V1_STATID, V2_STATID, V3_STATID,
					V4_STATID, V5_STATID, V6_STATID,
					V7_STATID पूर्ण;

#घोषणा LINT_MAP2		0x0340
#घोषणा VINT_MAP2		0x0344

#घोषणा MBOX0			0x0348
#घोषणा MBOX1			0x034C
#घोषणा MBOX2			0x0350
#घोषणा MBOX3			0x0354
#घोषणा SEMA0			0x0358
#घोषणा SEMA1			0x035C

#घोषणा MAST_CTL		0x0400
#घोषणा MISC_CTL		0x0404
#घोषणा MISC_STAT		0x0408
#घोषणा USER_AM			0x040C

#घोषणा VSI0_CTL		0x0F00
#घोषणा VSI0_BS			0x0F04
#घोषणा VSI0_BD			0x0F08
#घोषणा VSI0_TO			0x0F0C

#घोषणा VSI1_CTL		0x0F14
#घोषणा VSI1_BS			0x0F18
#घोषणा VSI1_BD			0x0F1C
#घोषणा VSI1_TO			0x0F20

#घोषणा VSI2_CTL		0x0F28
#घोषणा VSI2_BS			0x0F2C
#घोषणा VSI2_BD			0x0F30
#घोषणा VSI2_TO			0x0F34

#घोषणा VSI3_CTL		0x0F3C
#घोषणा VSI3_BS			0x0F40
#घोषणा VSI3_BD			0x0F44
#घोषणा VSI3_TO			0x0F48

#घोषणा LM_CTL			0x0F64
#घोषणा LM_BS			0x0F68

#घोषणा VRAI_CTL		0x0F70

#घोषणा VRAI_BS			0x0F74
#घोषणा VCSR_CTL		0x0F80
#घोषणा VCSR_TO			0x0F84
#घोषणा V_AMERR			0x0F88
#घोषणा VAERR			0x0F8C

#घोषणा VSI4_CTL		0x0F90
#घोषणा VSI4_BS			0x0F94
#घोषणा VSI4_BD			0x0F98
#घोषणा VSI4_TO			0x0F9C

#घोषणा VSI5_CTL		0x0FA4
#घोषणा VSI5_BS			0x0FA8
#घोषणा VSI5_BD			0x0FAC
#घोषणा VSI5_TO			0x0FB0

#घोषणा VSI6_CTL		0x0FB8
#घोषणा VSI6_BS			0x0FBC
#घोषणा VSI6_BD			0x0FC0
#घोषणा VSI6_TO			0x0FC4

#घोषणा VSI7_CTL		0x0FCC
#घोषणा VSI7_BS			0x0FD0
#घोषणा VSI7_BD			0x0FD4
#घोषणा VSI7_TO			0x0FD8

अटल स्थिर पूर्णांक CA91CX42_VSI_CTL[] = अणु VSI0_CTL, VSI1_CTL, VSI2_CTL, VSI3_CTL,
				VSI4_CTL, VSI5_CTL, VSI6_CTL, VSI7_CTL पूर्ण;

अटल स्थिर पूर्णांक CA91CX42_VSI_BS[] = अणु VSI0_BS, VSI1_BS, VSI2_BS, VSI3_BS,
				VSI4_BS, VSI5_BS, VSI6_BS, VSI7_BS पूर्ण;

अटल स्थिर पूर्णांक CA91CX42_VSI_BD[] = अणु VSI0_BD, VSI1_BD, VSI2_BD, VSI3_BD,
				VSI4_BD, VSI5_BD, VSI6_BD, VSI7_BD पूर्ण;

अटल स्थिर पूर्णांक CA91CX42_VSI_TO[] = अणु VSI0_TO, VSI1_TO, VSI2_TO, VSI3_TO,
				VSI4_TO, VSI5_TO, VSI6_TO, VSI7_TO पूर्ण;

#घोषणा VCSR_CLR		0x0FF4
#घोषणा VCSR_SET		0x0FF8
#घोषणा VCSR_BS			0x0FFC

/*
 * PCI Class Register
 * offset 008
 */
#घोषणा CA91CX42_BM_PCI_CLASS_BASE          0xFF000000
#घोषणा CA91CX42_OF_PCI_CLASS_BASE          24
#घोषणा CA91CX42_BM_PCI_CLASS_SUB           0x00FF0000
#घोषणा CA91CX42_OF_PCI_CLASS_SUB           16
#घोषणा CA91CX42_BM_PCI_CLASS_PROG          0x0000FF00
#घोषणा CA91CX42_OF_PCI_CLASS_PROG          8
#घोषणा CA91CX42_BM_PCI_CLASS_RID           0x000000FF
#घोषणा CA91CX42_OF_PCI_CLASS_RID           0

#घोषणा CA91CX42_OF_PCI_CLASS_RID_UNIVERSE_I 0
#घोषणा CA91CX42_OF_PCI_CLASS_RID_UNIVERSE_II 1

/*
 * PCI Misc Register
 * offset 00C
 */
#घोषणा CA91CX42_BM_PCI_MISC0_BISTC         0x80000000
#घोषणा CA91CX42_BM_PCI_MISC0_SBIST         0x60000000
#घोषणा CA91CX42_BM_PCI_MISC0_CCODE         0x0F000000
#घोषणा CA91CX42_BM_PCI_MISC0_MFUNCT        0x00800000
#घोषणा CA91CX42_BM_PCI_MISC0_LAYOUT        0x007F0000
#घोषणा CA91CX42_BM_PCI_MISC0_LTIMER        0x0000FF00
#घोषणा CA91CX42_OF_PCI_MISC0_LTIMER        8


/*
 * LSI Control Register
 * offset  100
 */
#घोषणा CA91CX42_LSI_CTL_EN		(1<<31)
#घोषणा CA91CX42_LSI_CTL_PWEN		(1<<30)

#घोषणा CA91CX42_LSI_CTL_VDW_M		(3<<22)
#घोषणा CA91CX42_LSI_CTL_VDW_D8		0
#घोषणा CA91CX42_LSI_CTL_VDW_D16	(1<<22)
#घोषणा CA91CX42_LSI_CTL_VDW_D32	(1<<23)
#घोषणा CA91CX42_LSI_CTL_VDW_D64	(3<<22)

#घोषणा CA91CX42_LSI_CTL_VAS_M		(7<<16)
#घोषणा CA91CX42_LSI_CTL_VAS_A16	0
#घोषणा CA91CX42_LSI_CTL_VAS_A24	(1<<16)
#घोषणा CA91CX42_LSI_CTL_VAS_A32	(1<<17)
#घोषणा CA91CX42_LSI_CTL_VAS_CRCSR	(5<<16)
#घोषणा CA91CX42_LSI_CTL_VAS_USER1	(3<<17)
#घोषणा CA91CX42_LSI_CTL_VAS_USER2	(7<<16)

#घोषणा CA91CX42_LSI_CTL_PGM_M		(1<<14)
#घोषणा CA91CX42_LSI_CTL_PGM_DATA	0
#घोषणा CA91CX42_LSI_CTL_PGM_PGM	(1<<14)

#घोषणा CA91CX42_LSI_CTL_SUPER_M	(1<<12)
#घोषणा CA91CX42_LSI_CTL_SUPER_NPRIV	0
#घोषणा CA91CX42_LSI_CTL_SUPER_SUPR	(1<<12)

#घोषणा CA91CX42_LSI_CTL_VCT_M		(1<<8)
#घोषणा CA91CX42_LSI_CTL_VCT_BLT	(1<<8)
#घोषणा CA91CX42_LSI_CTL_VCT_MBLT	(1<<8)
#घोषणा CA91CX42_LSI_CTL_LAS		(1<<0)

/*
 * SCYC_CTL Register
 * offset 178
 */
#घोषणा CA91CX42_SCYC_CTL_LAS_PCIMEM	0
#घोषणा CA91CX42_SCYC_CTL_LAS_PCIIO	(1<<2)

#घोषणा CA91CX42_SCYC_CTL_CYC_M		(3<<0)
#घोषणा CA91CX42_SCYC_CTL_CYC_RMW	(1<<0)
#घोषणा CA91CX42_SCYC_CTL_CYC_ADOH	(1<<1)

/*
 * LMISC Register
 * offset  184
 */
#घोषणा CA91CX42_BM_LMISC_CRT               0xF0000000
#घोषणा CA91CX42_OF_LMISC_CRT               28
#घोषणा CA91CX42_BM_LMISC_CWT               0x0F000000
#घोषणा CA91CX42_OF_LMISC_CWT               24

/*
 * SLSI Register
 * offset  188
 */
#घोषणा CA91CX42_BM_SLSI_EN                 0x80000000
#घोषणा CA91CX42_BM_SLSI_PWEN               0x40000000
#घोषणा CA91CX42_BM_SLSI_VDW                0x00F00000
#घोषणा CA91CX42_OF_SLSI_VDW                20
#घोषणा CA91CX42_BM_SLSI_PGM                0x0000F000
#घोषणा CA91CX42_OF_SLSI_PGM                12
#घोषणा CA91CX42_BM_SLSI_SUPER              0x00000F00
#घोषणा CA91CX42_OF_SLSI_SUPER              8
#घोषणा CA91CX42_BM_SLSI_BS                 0x000000F6
#घोषणा CA91CX42_OF_SLSI_BS                 2
#घोषणा CA91CX42_BM_SLSI_LAS                0x00000003
#घोषणा CA91CX42_OF_SLSI_LAS                0
#घोषणा CA91CX42_BM_SLSI_RESERVED           0x3F0F0000

/*
 * DCTL Register
 * offset 200
 */
#घोषणा CA91CX42_DCTL_L2V		(1<<31)
#घोषणा CA91CX42_DCTL_VDW_M		(3<<22)
#घोषणा CA91CX42_DCTL_VDW_D8		0
#घोषणा CA91CX42_DCTL_VDW_D16		(1<<22)
#घोषणा CA91CX42_DCTL_VDW_D32		(1<<23)
#घोषणा CA91CX42_DCTL_VDW_D64		(3<<22)

#घोषणा CA91CX42_DCTL_VAS_M		(7<<16)
#घोषणा CA91CX42_DCTL_VAS_A16		0
#घोषणा CA91CX42_DCTL_VAS_A24		(1<<16)
#घोषणा CA91CX42_DCTL_VAS_A32		(1<<17)
#घोषणा CA91CX42_DCTL_VAS_USER1		(3<<17)
#घोषणा CA91CX42_DCTL_VAS_USER2		(7<<16)

#घोषणा CA91CX42_DCTL_PGM_M		(1<<14)
#घोषणा CA91CX42_DCTL_PGM_DATA		0
#घोषणा CA91CX42_DCTL_PGM_PGM		(1<<14)

#घोषणा CA91CX42_DCTL_SUPER_M		(1<<12)
#घोषणा CA91CX42_DCTL_SUPER_NPRIV	0
#घोषणा CA91CX42_DCTL_SUPER_SUPR	(1<<12)

#घोषणा CA91CX42_DCTL_VCT_M		(1<<8)
#घोषणा CA91CX42_DCTL_VCT_BLT		(1<<8)
#घोषणा CA91CX42_DCTL_LD64EN		(1<<7)

/*
 * DCPP Register
 * offset 218
 */
#घोषणा CA91CX42_DCPP_M			0xf
#घोषणा CA91CX42_DCPP_शून्य		(1<<0)

/*
 * DMA General Control/Status Register (DGCS)
 * offset 220
 */
#घोषणा CA91CX42_DGCS_GO		(1<<31)
#घोषणा CA91CX42_DGCS_STOP_REQ		(1<<30)
#घोषणा CA91CX42_DGCS_HALT_REQ		(1<<29)
#घोषणा CA91CX42_DGCS_CHAIN		(1<<27)

#घोषणा CA91CX42_DGCS_VON_M		(7<<20)

#घोषणा CA91CX42_DGCS_VOFF_M		(0xf<<16)

#घोषणा CA91CX42_DGCS_ACT		(1<<15)
#घोषणा CA91CX42_DGCS_STOP		(1<<14)
#घोषणा CA91CX42_DGCS_HALT		(1<<13)
#घोषणा CA91CX42_DGCS_DONE		(1<<11)
#घोषणा CA91CX42_DGCS_LERR		(1<<10)
#घोषणा CA91CX42_DGCS_VERR		(1<<9)
#घोषणा CA91CX42_DGCS_PERR		(1<<8)
#घोषणा CA91CX42_DGCS_INT_STOP		(1<<6)
#घोषणा CA91CX42_DGCS_INT_HALT		(1<<5)
#घोषणा CA91CX42_DGCS_INT_DONE		(1<<3)
#घोषणा CA91CX42_DGCS_INT_LERR		(1<<2)
#घोषणा CA91CX42_DGCS_INT_VERR		(1<<1)
#घोषणा CA91CX42_DGCS_INT_PERR		(1<<0)

/*
 * PCI Interrupt Enable Register
 * offset  300
 */
#घोषणा CA91CX42_LINT_LM3		0x00800000
#घोषणा CA91CX42_LINT_LM2		0x00400000
#घोषणा CA91CX42_LINT_LM1		0x00200000
#घोषणा CA91CX42_LINT_LM0		0x00100000
#घोषणा CA91CX42_LINT_MBOX3		0x00080000
#घोषणा CA91CX42_LINT_MBOX2		0x00040000
#घोषणा CA91CX42_LINT_MBOX1		0x00020000
#घोषणा CA91CX42_LINT_MBOX0		0x00010000
#घोषणा CA91CX42_LINT_ACFAIL		0x00008000
#घोषणा CA91CX42_LINT_SYSFAIL		0x00004000
#घोषणा CA91CX42_LINT_SW_INT		0x00002000
#घोषणा CA91CX42_LINT_SW_IACK		0x00001000

#घोषणा CA91CX42_LINT_VERR		0x00000400
#घोषणा CA91CX42_LINT_LERR		0x00000200
#घोषणा CA91CX42_LINT_DMA		0x00000100
#घोषणा CA91CX42_LINT_VIRQ7		0x00000080
#घोषणा CA91CX42_LINT_VIRQ6		0x00000040
#घोषणा CA91CX42_LINT_VIRQ5		0x00000020
#घोषणा CA91CX42_LINT_VIRQ4		0x00000010
#घोषणा CA91CX42_LINT_VIRQ3		0x00000008
#घोषणा CA91CX42_LINT_VIRQ2		0x00000004
#घोषणा CA91CX42_LINT_VIRQ1		0x00000002
#घोषणा CA91CX42_LINT_VOWN		0x00000001

अटल स्थिर पूर्णांक CA91CX42_LINT_VIRQ[] = अणु 0, CA91CX42_LINT_VIRQ1,
				CA91CX42_LINT_VIRQ2, CA91CX42_LINT_VIRQ3,
				CA91CX42_LINT_VIRQ4, CA91CX42_LINT_VIRQ5,
				CA91CX42_LINT_VIRQ6, CA91CX42_LINT_VIRQ7 पूर्ण;

#घोषणा CA91CX42_LINT_MBOX		0x000F0000

अटल स्थिर पूर्णांक CA91CX42_LINT_LM[] = अणु CA91CX42_LINT_LM0, CA91CX42_LINT_LM1,
					CA91CX42_LINT_LM2, CA91CX42_LINT_LM3 पूर्ण;

/*
 * MAST_CTL Register
 * offset  400
 */
#घोषणा CA91CX42_BM_MAST_CTL_MAXRTRY        0xF0000000
#घोषणा CA91CX42_OF_MAST_CTL_MAXRTRY        28
#घोषणा CA91CX42_BM_MAST_CTL_PWON           0x0F000000
#घोषणा CA91CX42_OF_MAST_CTL_PWON           24
#घोषणा CA91CX42_BM_MAST_CTL_VRL            0x00C00000
#घोषणा CA91CX42_OF_MAST_CTL_VRL            22
#घोषणा CA91CX42_BM_MAST_CTL_VRM            0x00200000
#घोषणा CA91CX42_BM_MAST_CTL_VREL           0x00100000
#घोषणा CA91CX42_BM_MAST_CTL_VOWN           0x00080000
#घोषणा CA91CX42_BM_MAST_CTL_VOWN_ACK       0x00040000
#घोषणा CA91CX42_BM_MAST_CTL_PABS           0x00001000
#घोषणा CA91CX42_BM_MAST_CTL_BUS_NO         0x0000000F
#घोषणा CA91CX42_OF_MAST_CTL_BUS_NO         0

/*
 * MISC_CTL Register
 * offset  404
 */
#घोषणा CA91CX42_MISC_CTL_VBTO           0xF0000000
#घोषणा CA91CX42_MISC_CTL_VARB           0x04000000
#घोषणा CA91CX42_MISC_CTL_VARBTO         0x03000000
#घोषणा CA91CX42_MISC_CTL_SW_LRST        0x00800000
#घोषणा CA91CX42_MISC_CTL_SW_SRST        0x00400000
#घोषणा CA91CX42_MISC_CTL_BI             0x00100000
#घोषणा CA91CX42_MISC_CTL_ENGBI          0x00080000
#घोषणा CA91CX42_MISC_CTL_RESCIND        0x00040000
#घोषणा CA91CX42_MISC_CTL_SYSCON         0x00020000
#घोषणा CA91CX42_MISC_CTL_V64AUTO        0x00010000
#घोषणा CA91CX42_MISC_CTL_RESERVED       0x0820FFFF

#घोषणा CA91CX42_OF_MISC_CTL_VARBTO         24
#घोषणा CA91CX42_OF_MISC_CTL_VBTO           28

/*
 * MISC_STAT Register
 * offset  408
 */
#घोषणा CA91CX42_BM_MISC_STAT_ENDIAN        0x80000000
#घोषणा CA91CX42_BM_MISC_STAT_LCLSIZE       0x40000000
#घोषणा CA91CX42_BM_MISC_STAT_DY4AUTO       0x08000000
#घोषणा CA91CX42_BM_MISC_STAT_MYBBSY        0x00200000
#घोषणा CA91CX42_BM_MISC_STAT_DY4DONE       0x00080000
#घोषणा CA91CX42_BM_MISC_STAT_TXFE          0x00040000
#घोषणा CA91CX42_BM_MISC_STAT_RXFE          0x00020000
#घोषणा CA91CX42_BM_MISC_STAT_DY4AUTOID     0x0000FF00
#घोषणा CA91CX42_OF_MISC_STAT_DY4AUTOID     8

/*
 * VSI Control Register
 * offset  F00
 */
#घोषणा CA91CX42_VSI_CTL_EN		(1<<31)
#घोषणा CA91CX42_VSI_CTL_PWEN		(1<<30)
#घोषणा CA91CX42_VSI_CTL_PREN		(1<<29)

#घोषणा CA91CX42_VSI_CTL_PGM_M		(3<<22)
#घोषणा CA91CX42_VSI_CTL_PGM_DATA	(1<<22)
#घोषणा CA91CX42_VSI_CTL_PGM_PGM	(1<<23)

#घोषणा CA91CX42_VSI_CTL_SUPER_M	(3<<20)
#घोषणा CA91CX42_VSI_CTL_SUPER_NPRIV	(1<<20)
#घोषणा CA91CX42_VSI_CTL_SUPER_SUPR	(1<<21)

#घोषणा CA91CX42_VSI_CTL_VAS_M		(7<<16)
#घोषणा CA91CX42_VSI_CTL_VAS_A16	0
#घोषणा CA91CX42_VSI_CTL_VAS_A24	(1<<16)
#घोषणा CA91CX42_VSI_CTL_VAS_A32	(1<<17)
#घोषणा CA91CX42_VSI_CTL_VAS_USER1	(3<<17)
#घोषणा CA91CX42_VSI_CTL_VAS_USER2	(7<<16)

#घोषणा CA91CX42_VSI_CTL_LD64EN		(1<<7)
#घोषणा CA91CX42_VSI_CTL_LLRMW		(1<<6)

#घोषणा CA91CX42_VSI_CTL_LAS_M		(3<<0)
#घोषणा CA91CX42_VSI_CTL_LAS_PCI_MS	0
#घोषणा CA91CX42_VSI_CTL_LAS_PCI_IO	(1<<0)
#घोषणा CA91CX42_VSI_CTL_LAS_PCI_CONF	(1<<1)

/* LM_CTL Register
 * offset  F64
 */
#घोषणा CA91CX42_LM_CTL_EN		(1<<31)
#घोषणा CA91CX42_LM_CTL_PGM		(1<<23)
#घोषणा CA91CX42_LM_CTL_DATA		(1<<22)
#घोषणा CA91CX42_LM_CTL_SUPR		(1<<21)
#घोषणा CA91CX42_LM_CTL_NPRIV		(1<<20)
#घोषणा CA91CX42_LM_CTL_AS_M		(7<<16)
#घोषणा CA91CX42_LM_CTL_AS_A16		0
#घोषणा CA91CX42_LM_CTL_AS_A24		(1<<16)
#घोषणा CA91CX42_LM_CTL_AS_A32		(1<<17)

/*
 * VRAI_CTL Register
 * offset  F70
 */
#घोषणा CA91CX42_BM_VRAI_CTL_EN             0x80000000
#घोषणा CA91CX42_BM_VRAI_CTL_PGM            0x00C00000
#घोषणा CA91CX42_OF_VRAI_CTL_PGM            22
#घोषणा CA91CX42_BM_VRAI_CTL_SUPER          0x00300000
#घोषणा CA91CX42_OF_VRAI_CTL_SUPER          20
#घोषणा CA91CX42_BM_VRAI_CTL_VAS            0x00030000
#घोषणा CA91CX42_OF_VRAI_CTL_VAS            16

/* VCSR_CTL Register
 * offset F80
 */
#घोषणा CA91CX42_VCSR_CTL_EN		(1<<31)

#घोषणा CA91CX42_VCSR_CTL_LAS_M		(3<<0)
#घोषणा CA91CX42_VCSR_CTL_LAS_PCI_MS	0
#घोषणा CA91CX42_VCSR_CTL_LAS_PCI_IO	(1<<0)
#घोषणा CA91CX42_VCSR_CTL_LAS_PCI_CONF	(1<<1)

/* VCSR_BS Register
 * offset FFC
 */
#घोषणा CA91CX42_VCSR_BS_SLOT_M		(0x1F<<27)

#पूर्ण_अगर /* _CA91CX42_H */
