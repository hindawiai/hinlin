<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * nicstar.h
 *
 * Header file क्रम the nicstar device driver.
 *
 * Author: Rui Prior (rprior@inescn.pt)
 * PowerPC support by Jay Talbott (jay_talbott@mcg.mot.com) April 1999
 *
 * (C) INESC 1998
 */

#अगर_अघोषित _LINUX_NICSTAR_H_
#घोषणा _LINUX_NICSTAR_H_

/* Includes */

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/idr.h>
#समावेश <linux/uपन.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांग_nicstar.h>

/* Options */

#घोषणा NS_MAX_CARDS 4		/* Maximum number of NICStAR based cards
				   controlled by the device driver. Must
				   be <= 5 */

#अघोषित RCQ_SUPPORT		/* Do not define this क्रम now */

#घोषणा NS_TST_NUM_ENTRIES 2340	/* + 1 क्रम वापस */
#घोषणा NS_TST_RESERVED 340	/* N. entries reserved क्रम UBR/ABR/VBR */

#घोषणा NS_SMबफ_मानE 48		/* 48, 96, 240 or 2048 */
#घोषणा NS_LGबफ_मानE 16384	/* 2048, 4096, 8192 or 16384 */
#घोषणा NS_RSQSIZE 8192		/* 2048, 4096 or 8192 */
#घोषणा NS_VPIBITS 2		/* 0, 1, 2, or 8 */

#घोषणा NS_MAX_RCTSIZE 4096	/* Number of entries. 4096 or 16384.
				   Define 4096 only अगर (all) your card(s)
				   have 32K x 32bit SRAM, in which हाल
				   setting this to 16384 will just waste a
				   lot of memory.
				   Setting this to 4096 क्रम a card with
				   128K x 32bit SRAM will limit the maximum
				   VCI. */

				/*#घोषणा NS_PCI_LATENCY 64*//* Must be a multiple of 32 */

	/* Number of buffers initially allocated */
#घोषणा NUM_SB 32		/* Must be even */
#घोषणा NUM_LB 24		/* Must be even */
#घोषणा NUM_HB 8		/* Pre-allocated huge buffers */
#घोषणा NUM_IOVB 48		/* Iovec buffers */

	/* Lower level क्रम count of buffers */
#घोषणा MIN_SB 8		/* Must be even */
#घोषणा MIN_LB 8		/* Must be even */
#घोषणा MIN_HB 6
#घोषणा MIN_IOVB 8

	/* Upper level क्रम count of buffers */
#घोषणा MAX_SB 64		/* Must be even, <= 508 */
#घोषणा MAX_LB 48		/* Must be even, <= 508 */
#घोषणा MAX_HB 10
#घोषणा MAX_IOVB 80

	/* These are the असलolute maximum allowed क्रम the ioctl() */
#घोषणा TOP_SB 256		/* Must be even, <= 508 */
#घोषणा TOP_LB 128		/* Must be even, <= 508 */
#घोषणा TOP_HB 64
#घोषणा TOP_IOVB 256

#घोषणा MAX_TBD_PER_VC 1	/* Number of TBDs beक्रमe a TSR */
#घोषणा MAX_TBD_PER_SCQ 10	/* Only meaningful क्रम variable rate SCQs */

#अघोषित ENABLE_TSQFIE

#घोषणा SCQFULL_TIMEOUT (5 * HZ)

#घोषणा NS_POLL_PERIOD (HZ)

#घोषणा PCR_TOLERANCE (1.0001)

/* ESI stuff */

#घोषणा NICSTAR_EPROM_MAC_ADDR_OFFSET 0x6C
#घोषणा NICSTAR_EPROM_MAC_ADDR_OFFSET_ALT 0xF6

/* #घोषणाs */

#घोषणा NS_IOREMAP_SIZE 4096

/*
 * BUF_XX distinguish the Rx buffers depending on their (small/large) size.
 * BUG_SM and BUG_LG are both used by the driver and the device.
 * BUF_NONE is only used by the driver.
 */
#घोषणा BUF_SM		0x00000000	/* These two are used क्रम push_rxbufs() */
#घोषणा BUF_LG		0x00000001	/* CMD, Write_FreeBufQ, LBUF bit */
#घोषणा BUF_NONE 	0xffffffff	/* Software only: */

#घोषणा NS_Hबफ_मानE 65568	/* Size of max. AAL5 PDU */
#घोषणा NS_MAX_IOVECS (2 + (65568 - NS_SMबफ_मानE) / \
                       (NS_LGबफ_मानE - (NS_LGबफ_मानE % 48)))
#घोषणा NS_IOVबफ_मानE (NS_MAX_IOVECS * (माप(काष्ठा iovec)))

#घोषणा NS_SMबफ_मानE_USABLE (NS_SMबफ_मानE - NS_SMबफ_मानE % 48)
#घोषणा NS_LGबफ_मानE_USABLE (NS_LGबफ_मानE - NS_LGबफ_मानE % 48)

#घोषणा NS_AAL0_HEADER (ATM_AAL0_SDU - ATM_CELL_PAYLOAD)	/* 4 bytes */

#घोषणा NS_SMSKBSIZE (NS_SMबफ_मानE + NS_AAL0_HEADER)
#घोषणा NS_LGSKBSIZE (NS_SMबफ_मानE + NS_LGबफ_मानE)

/* NICStAR काष्ठाures located in host memory */

/*
 * RSQ - Receive Status Queue
 *
 * Written by the NICStAR, पढ़ो by the device driver.
 */

प्रकार काष्ठा ns_rsqe अणु
	u32 word_1;
	u32 buffer_handle;
	u32 final_aal5_crc32;
	u32 word_4;
पूर्ण ns_rsqe;

#घोषणा ns_rsqe_vpi(ns_rsqep) \
        ((le32_to_cpu((ns_rsqep)->word_1) & 0x00FF0000) >> 16)
#घोषणा ns_rsqe_vci(ns_rsqep) \
        (le32_to_cpu((ns_rsqep)->word_1) & 0x0000FFFF)

#घोषणा NS_RSQE_VALID      0x80000000
#घोषणा NS_RSQE_NZGFC      0x00004000
#घोषणा NS_RSQE_EOPDU      0x00002000
#घोषणा NS_RSQE_बफ_मानE    0x00001000
#घोषणा NS_RSQE_CONGESTION 0x00000800
#घोषणा NS_RSQE_CLP        0x00000400
#घोषणा NS_RSQE_CRCERR     0x00000200

#घोषणा NS_RSQE_बफ_मानE_SM 0x00000000
#घोषणा NS_RSQE_बफ_मानE_LG 0x00001000

#घोषणा ns_rsqe_valid(ns_rsqep) \
        (le32_to_cpu((ns_rsqep)->word_4) & NS_RSQE_VALID)
#घोषणा ns_rsqe_nzgfc(ns_rsqep) \
        (le32_to_cpu((ns_rsqep)->word_4) & NS_RSQE_NZGFC)
#घोषणा ns_rsqe_eopdu(ns_rsqep) \
        (le32_to_cpu((ns_rsqep)->word_4) & NS_RSQE_EOPDU)
#घोषणा ns_rsqe_bufsize(ns_rsqep) \
        (le32_to_cpu((ns_rsqep)->word_4) & NS_RSQE_बफ_मानE)
#घोषणा ns_rsqe_congestion(ns_rsqep) \
        (le32_to_cpu((ns_rsqep)->word_4) & NS_RSQE_CONGESTION)
#घोषणा ns_rsqe_clp(ns_rsqep) \
        (le32_to_cpu((ns_rsqep)->word_4) & NS_RSQE_CLP)
#घोषणा ns_rsqe_crcerr(ns_rsqep) \
        (le32_to_cpu((ns_rsqep)->word_4) & NS_RSQE_CRCERR)

#घोषणा ns_rsqe_cellcount(ns_rsqep) \
        (le32_to_cpu((ns_rsqep)->word_4) & 0x000001FF)
#घोषणा ns_rsqe_init(ns_rsqep) \
        ((ns_rsqep)->word_4 = cpu_to_le32(0x00000000))

#घोषणा NS_RSQ_NUM_ENTRIES (NS_RSQSIZE / 16)
#घोषणा NS_RSQ_ALIGNMENT NS_RSQSIZE

/*
 * RCQ - Raw Cell Queue
 *
 * Written by the NICStAR, पढ़ो by the device driver.
 */

प्रकार काष्ठा cell_payload अणु
	u32 word[12];
पूर्ण cell_payload;

प्रकार काष्ठा ns_rcqe अणु
	u32 word_1;
	u32 word_2;
	u32 word_3;
	u32 word_4;
	cell_payload payload;
पूर्ण ns_rcqe;

#घोषणा NS_RCQE_SIZE 64		/* bytes */

#घोषणा ns_rcqe_islast(ns_rcqep) \
        (le32_to_cpu((ns_rcqep)->word_2) != 0x00000000)
#घोषणा ns_rcqe_cellheader(ns_rcqep) \
        (le32_to_cpu((ns_rcqep)->word_1))
#घोषणा ns_rcqe_nextbufhandle(ns_rcqep) \
        (le32_to_cpu((ns_rcqep)->word_2))

/*
 * SCQ - Segmentation Channel Queue
 *
 * Written by the device driver, पढ़ो by the NICStAR.
 */

प्रकार काष्ठा ns_scqe अणु
	u32 word_1;
	u32 word_2;
	u32 word_3;
	u32 word_4;
पूर्ण ns_scqe;

   /* NOTE: SCQ entries can be either a TBD (Transmit Buffer Descriptors)
      or TSR (Transmit Status Requests) */

#घोषणा NS_SCQE_TYPE_TBD 0x00000000
#घोषणा NS_SCQE_TYPE_TSR 0x80000000

#घोषणा NS_TBD_EOPDU 0x40000000
#घोषणा NS_TBD_AAL0  0x00000000
#घोषणा NS_TBD_AAL34 0x04000000
#घोषणा NS_TBD_AAL5  0x08000000

#घोषणा NS_TBD_VPI_MASK 0x0FF00000
#घोषणा NS_TBD_VCI_MASK 0x000FFFF0
#घोषणा NS_TBD_VC_MASK (NS_TBD_VPI_MASK | NS_TBD_VCI_MASK)

#घोषणा NS_TBD_VPI_SHIFT 20
#घोषणा NS_TBD_VCI_SHIFT 4

#घोषणा ns_tbd_mkword_1(flags, m, n, buflen) \
      (cpu_to_le32((flags) | (m) << 23 | (n) << 16 | (buflen)))
#घोषणा ns_tbd_mkword_1_novbr(flags, buflen) \
      (cpu_to_le32((flags) | (buflen) | 0x00810000))
#घोषणा ns_tbd_mkword_3(control, pdulen) \
      (cpu_to_le32((control) << 16 | (pdulen)))
#घोषणा ns_tbd_mkword_4(gfc, vpi, vci, pt, clp) \
      (cpu_to_le32((gfc) << 28 | (vpi) << 20 | (vci) << 4 | (pt) << 1 | (clp)))

#घोषणा NS_TSR_INTENABLE 0x20000000

#घोषणा NS_TSR_SCDISVBR 0xFFFF	/* Use as scdi क्रम VBR SCD */

#घोषणा ns_tsr_mkword_1(flags) \
        (cpu_to_le32(NS_SCQE_TYPE_TSR | (flags)))
#घोषणा ns_tsr_mkword_2(scdi, scqi) \
        (cpu_to_le32((scdi) << 16 | 0x00008000 | (scqi)))

#घोषणा ns_scqe_is_tsr(ns_scqep) \
        (le32_to_cpu((ns_scqep)->word_1) & NS_SCQE_TYPE_TSR)

#घोषणा VBR_SCQ_NUM_ENTRIES 512
#घोषणा VBR_SCQSIZE 8192
#घोषणा CBR_SCQ_NUM_ENTRIES 64
#घोषणा CBR_SCQSIZE 1024

#घोषणा NS_SCQE_SIZE 16

/*
 * TSQ - Transmit Status Queue
 *
 * Written by the NICStAR, पढ़ो by the device driver.
 */

प्रकार काष्ठा ns_tsi अणु
	u32 word_1;
	u32 word_2;
पूर्ण ns_tsi;

   /* NOTE: The first word can be a status word copied from the TSR which
      originated the TSI, or a समयr overflow indicator. In this last
      हाल, the value of the first word is all zeroes. */

#घोषणा NS_TSI_EMPTY          0x80000000
#घोषणा NS_TSI_TIMESTAMP_MASK 0x00FFFFFF

#घोषणा ns_tsi_isempty(ns_tsip) \
        (le32_to_cpu((ns_tsip)->word_2) & NS_TSI_EMPTY)
#घोषणा ns_tsi_समय_लोstamp(ns_tsip) \
        (le32_to_cpu((ns_tsip)->word_2) & NS_TSI_TIMESTAMP_MASK)

#घोषणा ns_tsi_init(ns_tsip) \
        ((ns_tsip)->word_2 = cpu_to_le32(NS_TSI_EMPTY))

#घोषणा NS_TSQSIZE 8192
#घोषणा NS_TSQ_NUM_ENTRIES 1024
#घोषणा NS_TSQ_ALIGNMENT 8192

#घोषणा NS_TSI_SCDISVBR NS_TSR_SCDISVBR

#घोषणा ns_tsi_पंचांगrof(ns_tsip) \
        (le32_to_cpu((ns_tsip)->word_1) == 0x00000000)
#घोषणा ns_tsi_माला_लोcdindex(ns_tsip) \
        ((le32_to_cpu((ns_tsip)->word_1) & 0xFFFF0000) >> 16)
#घोषणा ns_tsi_माला_लोcqpos(ns_tsip) \
        (le32_to_cpu((ns_tsip)->word_1) & 0x00007FFF)

/* NICStAR काष्ठाures located in local SRAM */

/*
 * RCT - Receive Connection Table
 *
 * Written by both the NICStAR and the device driver.
 */

प्रकार काष्ठा ns_rcte अणु
	u32 word_1;
	u32 buffer_handle;
	u32 dma_address;
	u32 aal5_crc32;
पूर्ण ns_rcte;

#घोषणा NS_RCTE_BSFB            0x00200000	/* Rev. D only */
#घोषणा NS_RCTE_NZGFC           0x00100000
#घोषणा NS_RCTE_CONNECTOPEN     0x00080000
#घोषणा NS_RCTE_AALMASK         0x00070000
#घोषणा NS_RCTE_AAL0            0x00000000
#घोषणा NS_RCTE_AAL34           0x00010000
#घोषणा NS_RCTE_AAL5            0x00020000
#घोषणा NS_RCTE_RCQ             0x00030000
#घोषणा NS_RCTE_RAWCELLINTEN    0x00008000
#घोषणा NS_RCTE_RXCONSTCELLADDR 0x00004000
#घोषणा NS_RCTE_BUFFVALID       0x00002000
#घोषणा NS_RCTE_FBDSIZE         0x00001000
#घोषणा NS_RCTE_EFCI            0x00000800
#घोषणा NS_RCTE_CLP             0x00000400
#घोषणा NS_RCTE_CRCERROR        0x00000200
#घोषणा NS_RCTE_CELLCOUNT_MASK  0x000001FF

#घोषणा NS_RCTE_FBDSIZE_SM 0x00000000
#घोषणा NS_RCTE_FBDSIZE_LG 0x00001000

#घोषणा NS_RCT_ENTRY_SIZE 4	/* Number of dwords */

   /* NOTE: We could make macros to contruct the first word of the RCTE,
      but that करोesn't seem to make much sense... */

/*
 * FBD - Free Buffer Descriptor
 *
 * Written by the device driver using via the command रेजिस्टर.
 */

प्रकार काष्ठा ns_fbd अणु
	u32 buffer_handle;
	u32 dma_address;
पूर्ण ns_fbd;

/*
 * TST - Transmit Schedule Table
 *
 * Written by the device driver.
 */

प्रकार u32 ns_tste;

#घोषणा NS_TST_OPCODE_MASK 0x60000000

#घोषणा NS_TST_OPCODE_शून्य     0x00000000	/* Insert null cell */
#घोषणा NS_TST_OPCODE_FIXED    0x20000000	/* Cell from a fixed rate channel */
#घोषणा NS_TST_OPCODE_VARIABLE 0x40000000
#घोषणा NS_TST_OPCODE_END      0x60000000	/* Jump */

#घोषणा ns_tste_make(opcode, sramad) (opcode | sramad)

   /* NOTE:

      - When the opcode is FIXED, sramad specअगरies the SRAM address of the
      SCD क्रम that fixed rate channel.
      - When the opcode is END, sramad specअगरies the SRAM address of the
      location of the next TST entry to पढ़ो.
    */

/*
 * SCD - Segmentation Channel Descriptor
 *
 * Written by both the device driver and the NICStAR
 */

प्रकार काष्ठा ns_scd अणु
	u32 word_1;
	u32 word_2;
	u32 partial_aal5_crc;
	u32 reserved;
	ns_scqe cache_a;
	ns_scqe cache_b;
पूर्ण ns_scd;

#घोषणा NS_SCD_BASE_MASK_VAR 0xFFFFE000	/* Variable rate */
#घोषणा NS_SCD_BASE_MASK_FIX 0xFFFFFC00	/* Fixed rate */
#घोषणा NS_SCD_TAIL_MASK_VAR 0x00001FF0
#घोषणा NS_SCD_TAIL_MASK_FIX 0x000003F0
#घोषणा NS_SCD_HEAD_MASK_VAR 0x00001FF0
#घोषणा NS_SCD_HEAD_MASK_FIX 0x000003F0
#घोषणा NS_SCD_XMITFOREVER   0x02000000

   /* NOTE: There are other fields in word 2 of the SCD, but as they should
      not be needed in the device driver they are not defined here. */

/* NICStAR local SRAM memory map */

#घोषणा NS_RCT           0x00000
#घोषणा NS_RCT_32_END    0x03FFF
#घोषणा NS_RCT_128_END   0x0FFFF
#घोषणा NS_UNUSED_32     0x04000
#घोषणा NS_UNUSED_128    0x10000
#घोषणा NS_UNUSED_END    0x1BFFF
#घोषणा NS_TST_FRSCD     0x1C000
#घोषणा NS_TST_FRSCD_END 0x1E7DB
#घोषणा NS_VRSCD2        0x1E7DC
#घोषणा NS_VRSCD2_END    0x1E7E7
#घोषणा NS_VRSCD1        0x1E7E8
#घोषणा NS_VRSCD1_END    0x1E7F3
#घोषणा NS_VRSCD0        0x1E7F4
#घोषणा NS_VRSCD0_END    0x1E7FF
#घोषणा NS_RXFIFO        0x1E800
#घोषणा NS_RXFIFO_END    0x1F7FF
#घोषणा NS_SMFBQ         0x1F800
#घोषणा NS_SMFBQ_END     0x1FBFF
#घोषणा NS_LGFBQ         0x1FC00
#घोषणा NS_LGFBQ_END     0x1FFFF

/* NISCtAR operation रेजिस्टरs */

/* See Section 3.4 of `IDT77211 NICStAR User Manual' from www.idt.com */

क्रमागत ns_regs अणु
	DR0 = 0x00,		/* Data Register 0 R/W */
	DR1 = 0x04,		/* Data Register 1 W */
	DR2 = 0x08,		/* Data Register 2 W */
	DR3 = 0x0C,		/* Data Register 3 W */
	CMD = 0x10,		/* Command W */
	CFG = 0x14,		/* Configuration R/W */
	STAT = 0x18,		/* Status R/W */
	RSQB = 0x1C,		/* Receive Status Queue Base W */
	RSQT = 0x20,		/* Receive Status Queue Tail R */
	RSQH = 0x24,		/* Receive Status Queue Head W */
	CDC = 0x28,		/* Cell Drop Counter R/clear */
	VPEC = 0x2C,		/* VPI/VCI Lookup Error Count R/clear */
	ICC = 0x30,		/* Invalid Cell Count R/clear */
	RAWCT = 0x34,		/* Raw Cell Tail R */
	TMR = 0x38,		/* Timer R */
	TSTB = 0x3C,		/* Transmit Schedule Table Base R/W */
	TSQB = 0x40,		/* Transmit Status Queue Base W */
	TSQT = 0x44,		/* Transmit Status Queue Tail R */
	TSQH = 0x48,		/* Transmit Status Queue Head W */
	GP = 0x4C,		/* General Purpose R/W */
	VPM = 0x50		/* VPI/VCI Mask W */
पूर्ण;

/* NICStAR commands issued to the CMD रेजिस्टर */

/* Top 4 bits are command opcode, lower 28 are parameters. */

#घोषणा NS_CMD_NO_OPERATION         0x00000000
	/* params always 0 */

#घोषणा NS_CMD_OPENCLOSE_CONNECTION 0x20000000
	/* b19अणु1=खोलो,0=बंदपूर्ण b18-2अणुSRAM addrपूर्ण */

#घोषणा NS_CMD_WRITE_SRAM           0x40000000
	/* b18-2अणुSRAM addrपूर्ण b1-0अणुburst sizeपूर्ण */

#घोषणा NS_CMD_READ_SRAM            0x50000000
	/* b18-2अणुSRAM addrपूर्ण */

#घोषणा NS_CMD_WRITE_FREEBUFQ       0x60000000
	/* b0अणुlarge buf indicatorपूर्ण */

#घोषणा NS_CMD_READ_UTILITY         0x80000000
	/* b8अणु1=select UTL_CS1पूर्ण b9अणु1=select UTL_CS0पूर्ण b7-0अणुbus addrपूर्ण */

#घोषणा NS_CMD_WRITE_UTILITY        0x90000000
	/* b8अणु1=select UTL_CS1पूर्ण b9अणु1=select UTL_CS0पूर्ण b7-0अणुbus addrपूर्ण */

#घोषणा NS_CMD_OPEN_CONNECTION (NS_CMD_OPENCLOSE_CONNECTION | 0x00080000)
#घोषणा NS_CMD_CLOSE_CONNECTION NS_CMD_OPENCLOSE_CONNECTION

/* NICStAR configuration bits */

#घोषणा NS_CFG_SWRST          0x80000000	/* Software Reset */
#घोषणा NS_CFG_RXPATH         0x20000000	/* Receive Path Enable */
#घोषणा NS_CFG_SMबफ_मानE_MASK 0x18000000	/* Small Receive Buffer Size */
#घोषणा NS_CFG_LGबफ_मानE_MASK 0x06000000	/* Large Receive Buffer Size */
#घोषणा NS_CFG_EFBIE          0x01000000	/* Empty Free Buffer Queue
						   Interrupt Enable */
#घोषणा NS_CFG_RSQSIZE_MASK   0x00C00000	/* Receive Status Queue Size */
#घोषणा NS_CFG_ICACCEPT       0x00200000	/* Invalid Cell Accept */
#घोषणा NS_CFG_IGNOREGFC      0x00100000	/* Ignore General Flow Control */
#घोषणा NS_CFG_VPIBITS_MASK   0x000C0000	/* VPI/VCI Bits Size Select */
#घोषणा NS_CFG_RCTSIZE_MASK   0x00030000	/* Receive Connection Table Size */
#घोषणा NS_CFG_VCERRACCEPT    0x00008000	/* VPI/VCI Error Cell Accept */
#घोषणा NS_CFG_RXINT_MASK     0x00007000	/* End of Receive PDU Interrupt
						   Handling */
#घोषणा NS_CFG_RAWIE          0x00000800	/* Raw Cell Qu' Interrupt Enable */
#घोषणा NS_CFG_RSQAFIE        0x00000400	/* Receive Queue Almost Full
						   Interrupt Enable */
#घोषणा NS_CFG_RXRM           0x00000200	/* Receive RM Cells */
#घोषणा NS_CFG_TMRROIE        0x00000080	/* Timer Roll Over Interrupt
						   Enable */
#घोषणा NS_CFG_TXEN           0x00000020	/* Transmit Operation Enable */
#घोषणा NS_CFG_TXIE           0x00000010	/* Transmit Status Interrupt
						   Enable */
#घोषणा NS_CFG_TXURIE         0x00000008	/* Transmit Under-run Interrupt
						   Enable */
#घोषणा NS_CFG_UMODE          0x00000004	/* Utopia Mode (cell/byte) Select */
#घोषणा NS_CFG_TSQFIE         0x00000002	/* Transmit Status Queue Full
						   Interrupt Enable */
#घोषणा NS_CFG_PHYIE          0x00000001	/* PHY Interrupt Enable */

#घोषणा NS_CFG_SMबफ_मानE_48    0x00000000
#घोषणा NS_CFG_SMबफ_मानE_96    0x08000000
#घोषणा NS_CFG_SMबफ_मानE_240   0x10000000
#घोषणा NS_CFG_SMबफ_मानE_2048  0x18000000

#घोषणा NS_CFG_LGबफ_मानE_2048  0x00000000
#घोषणा NS_CFG_LGबफ_मानE_4096  0x02000000
#घोषणा NS_CFG_LGबफ_मानE_8192  0x04000000
#घोषणा NS_CFG_LGबफ_मानE_16384 0x06000000

#घोषणा NS_CFG_RSQSIZE_2048 0x00000000
#घोषणा NS_CFG_RSQSIZE_4096 0x00400000
#घोषणा NS_CFG_RSQSIZE_8192 0x00800000

#घोषणा NS_CFG_VPIBITS_0 0x00000000
#घोषणा NS_CFG_VPIBITS_1 0x00040000
#घोषणा NS_CFG_VPIBITS_2 0x00080000
#घोषणा NS_CFG_VPIBITS_8 0x000C0000

#घोषणा NS_CFG_RCTSIZE_4096_ENTRIES  0x00000000
#घोषणा NS_CFG_RCTSIZE_8192_ENTRIES  0x00010000
#घोषणा NS_CFG_RCTSIZE_16384_ENTRIES 0x00020000

#घोषणा NS_CFG_RXINT_NOINT   0x00000000
#घोषणा NS_CFG_RXINT_NODELAY 0x00001000
#घोषणा NS_CFG_RXINT_314US   0x00002000
#घोषणा NS_CFG_RXINT_624US   0x00003000
#घोषणा NS_CFG_RXINT_899US   0x00004000

/* NICStAR STATus bits */

#घोषणा NS_STAT_SFBQC_MASK 0xFF000000	/* hi 8 bits Small Buffer Queue Count */
#घोषणा NS_STAT_LFBQC_MASK 0x00FF0000	/* hi 8 bits Large Buffer Queue Count */
#घोषणा NS_STAT_TSIF       0x00008000	/* Transmit Status Queue Indicator */
#घोषणा NS_STAT_TXICP      0x00004000	/* Transmit Incomplete PDU */
#घोषणा NS_STAT_TSQF       0x00001000	/* Transmit Status Queue Full */
#घोषणा NS_STAT_TMROF      0x00000800	/* Timer Overflow */
#घोषणा NS_STAT_PHYI       0x00000400	/* PHY Device Interrupt */
#घोषणा NS_STAT_CMDBZ      0x00000200	/* Command Busy */
#घोषणा NS_STAT_SFBQF      0x00000100	/* Small Buffer Queue Full */
#घोषणा NS_STAT_LFBQF      0x00000080	/* Large Buffer Queue Full */
#घोषणा NS_STAT_RSQF       0x00000040	/* Receive Status Queue Full */
#घोषणा NS_STAT_EOPDU      0x00000020	/* End of PDU */
#घोषणा NS_STAT_RAWCF      0x00000010	/* Raw Cell Flag */
#घोषणा NS_STAT_SFBQE      0x00000008	/* Small Buffer Queue Empty */
#घोषणा NS_STAT_LFBQE      0x00000004	/* Large Buffer Queue Empty */
#घोषणा NS_STAT_RSQAF      0x00000002	/* Receive Status Queue Almost Full */

#घोषणा ns_stat_sfbqc_get(stat) (((stat) & NS_STAT_SFBQC_MASK) >> 23)
#घोषणा ns_stat_lfbqc_get(stat) (((stat) & NS_STAT_LFBQC_MASK) >> 15)

/* #घोषणाs which depend on other #घोषणाs */

#घोषणा NS_TST0 NS_TST_FRSCD
#घोषणा NS_TST1 (NS_TST_FRSCD + NS_TST_NUM_ENTRIES + 1)

#घोषणा NS_FRSCD (NS_TST1 + NS_TST_NUM_ENTRIES + 1)
#घोषणा NS_FRSCD_SIZE 12	/* 12 dwords */
#घोषणा NS_FRSCD_NUM ((NS_TST_FRSCD_END + 1 - NS_FRSCD) / NS_FRSCD_SIZE)

#अगर (NS_SMबफ_मानE == 48)
#घोषणा NS_CFG_SMबफ_मानE NS_CFG_SMबफ_मानE_48
#या_अगर (NS_SMबफ_मानE == 96)
#घोषणा NS_CFG_SMबफ_मानE NS_CFG_SMबफ_मानE_96
#या_अगर (NS_SMबफ_मानE == 240)
#घोषणा NS_CFG_SMबफ_मानE NS_CFG_SMबफ_मानE_240
#या_अगर (NS_SMबफ_मानE == 2048)
#घोषणा NS_CFG_SMबफ_मानE NS_CFG_SMबफ_मानE_2048
#अन्यथा
#त्रुटि NS_SMबफ_मानE is incorrect in nicstar.h
#पूर्ण_अगर /* NS_SMबफ_मानE */

#अगर (NS_LGबफ_मानE == 2048)
#घोषणा NS_CFG_LGबफ_मानE NS_CFG_LGबफ_मानE_2048
#या_अगर (NS_LGबफ_मानE == 4096)
#घोषणा NS_CFG_LGबफ_मानE NS_CFG_LGबफ_मानE_4096
#या_अगर (NS_LGबफ_मानE == 8192)
#घोषणा NS_CFG_LGबफ_मानE NS_CFG_LGबफ_मानE_8192
#या_अगर (NS_LGबफ_मानE == 16384)
#घोषणा NS_CFG_LGबफ_मानE NS_CFG_LGबफ_मानE_16384
#अन्यथा
#त्रुटि NS_LGबफ_मानE is incorrect in nicstar.h
#पूर्ण_अगर /* NS_LGबफ_मानE */

#अगर (NS_RSQSIZE == 2048)
#घोषणा NS_CFG_RSQSIZE NS_CFG_RSQSIZE_2048
#या_अगर (NS_RSQSIZE == 4096)
#घोषणा NS_CFG_RSQSIZE NS_CFG_RSQSIZE_4096
#या_अगर (NS_RSQSIZE == 8192)
#घोषणा NS_CFG_RSQSIZE NS_CFG_RSQSIZE_8192
#अन्यथा
#त्रुटि NS_RSQSIZE is incorrect in nicstar.h
#पूर्ण_अगर /* NS_RSQSIZE */

#अगर (NS_VPIBITS == 0)
#घोषणा NS_CFG_VPIBITS NS_CFG_VPIBITS_0
#या_अगर (NS_VPIBITS == 1)
#घोषणा NS_CFG_VPIBITS NS_CFG_VPIBITS_1
#या_अगर (NS_VPIBITS == 2)
#घोषणा NS_CFG_VPIBITS NS_CFG_VPIBITS_2
#या_अगर (NS_VPIBITS == 8)
#घोषणा NS_CFG_VPIBITS NS_CFG_VPIBITS_8
#अन्यथा
#त्रुटि NS_VPIBITS is incorrect in nicstar.h
#पूर्ण_अगर /* NS_VPIBITS */

#अगर_घोषित RCQ_SUPPORT
#घोषणा NS_CFG_RAWIE_OPT NS_CFG_RAWIE
#अन्यथा
#घोषणा NS_CFG_RAWIE_OPT 0x00000000
#पूर्ण_अगर /* RCQ_SUPPORT */

#अगर_घोषित ENABLE_TSQFIE
#घोषणा NS_CFG_TSQFIE_OPT NS_CFG_TSQFIE
#अन्यथा
#घोषणा NS_CFG_TSQFIE_OPT 0x00000000
#पूर्ण_अगर /* ENABLE_TSQFIE */

/* PCI stuff */

#अगर_अघोषित PCI_VENDOR_ID_IDT
#घोषणा PCI_VENDOR_ID_IDT 0x111D
#पूर्ण_अगर /* PCI_VENDOR_ID_IDT */

#अगर_अघोषित PCI_DEVICE_ID_IDT_IDT77201
#घोषणा PCI_DEVICE_ID_IDT_IDT77201 0x0001
#पूर्ण_अगर /* PCI_DEVICE_ID_IDT_IDT77201 */

/* Device driver काष्ठाures */

काष्ठा ns_skb_prv अणु
	u32 buf_type;		/* BUF_SM/BUF_LG/BUF_NONE */
	u32 dma;
	पूर्णांक iovcnt;
पूर्ण;

#घोषणा NS_PRV_BUFTYPE(skb)   \
        (((काष्ठा ns_skb_prv *)(ATM_SKB(skb)+1))->buf_type)
#घोषणा NS_PRV_DMA(skb) \
        (((काष्ठा ns_skb_prv *)(ATM_SKB(skb)+1))->dma)
#घोषणा NS_PRV_IOVCNT(skb) \
        (((काष्ठा ns_skb_prv *)(ATM_SKB(skb)+1))->iovcnt)

प्रकार काष्ठा tsq_info अणु
	व्योम *org;
        dma_addr_t dma;
	ns_tsi *base;
	ns_tsi *next;
	ns_tsi *last;
पूर्ण tsq_info;

प्रकार काष्ठा scq_info अणु
	व्योम *org;
	dma_addr_t dma;
	ns_scqe *base;
	ns_scqe *last;
	ns_scqe *next;
	अस्थिर ns_scqe *tail;	/* Not related to the nicstar रेजिस्टर */
	अचिन्हित num_entries;
	काष्ठा sk_buff **skb;	/* Poपूर्णांकer to an array of poपूर्णांकers
				   to the sk_buffs used क्रम tx */
	u32 scd;		/* SRAM address of the corresponding
				   SCD */
	पूर्णांक tbd_count;		/* Only meaningful on variable rate */
	रुको_queue_head_t scqfull_रुकोq;
	अस्थिर अक्षर full;	/* SCQ full indicator */
	spinlock_t lock;	/* SCQ spinlock */
पूर्ण scq_info;

प्रकार काष्ठा rsq_info अणु
	व्योम *org;
        dma_addr_t dma;
	ns_rsqe *base;
	ns_rsqe *next;
	ns_rsqe *last;
पूर्ण rsq_info;

प्रकार काष्ठा skb_pool अणु
	अस्थिर पूर्णांक count;	/* number of buffers in the queue */
	काष्ठा sk_buff_head queue;
पूर्ण skb_pool;

/* NOTE: क्रम small and large buffer pools, the count is not used, as the
         actual value used क्रम buffer management is the one पढ़ो from the
	 card. */

प्रकार काष्ठा vc_map अणु
	अस्थिर अचिन्हित पूर्णांक tx:1;	/* TX vc? */
	अस्थिर अचिन्हित पूर्णांक rx:1;	/* RX vc? */
	काष्ठा aपंचांग_vcc *tx_vcc, *rx_vcc;
	काष्ठा sk_buff *rx_iov;	/* RX iovector skb */
	scq_info *scq;		/* To keep track of the SCQ */
	u32 cbr_scd;		/* SRAM address of the corresponding
				   SCD. 0x00000000 क्रम UBR/VBR/ABR */
	पूर्णांक tbd_count;
पूर्ण vc_map;

प्रकार काष्ठा ns_dev अणु
	पूर्णांक index;		/* Card ID to the device driver */
	पूर्णांक sram_size;		/* In k x 32bit words. 32 or 128 */
	व्योम __iomem *membase;	/* Card's memory base address */
	अचिन्हित दीर्घ max_pcr;
	पूर्णांक rct_size;		/* Number of entries */
	पूर्णांक vpibits;
	पूर्णांक vcibits;
	काष्ठा pci_dev *pcidev;
	काष्ठा idr idr;
	काष्ठा aपंचांग_dev *aपंचांगdev;
	tsq_info tsq;
	rsq_info rsq;
	scq_info *scq0, *scq1, *scq2;	/* VBR SCQs */
	skb_pool sbpool;	/* Small buffers */
	skb_pool lbpool;	/* Large buffers */
	skb_pool hbpool;	/* Pre-allocated huge buffers */
	skb_pool iovpool;	/* iovector buffers */
	अस्थिर पूर्णांक efbie;	/* Empty मुक्त buf. queue पूर्णांक. enabled */
	अस्थिर u32 tst_addr;	/* SRAM address of the TST in use */
	अस्थिर पूर्णांक tst_मुक्त_entries;
	vc_map vcmap[NS_MAX_RCTSIZE];
	vc_map *tste2vc[NS_TST_NUM_ENTRIES];
	vc_map *scd2vc[NS_FRSCD_NUM];
	buf_nr sbnr;
	buf_nr lbnr;
	buf_nr hbnr;
	buf_nr iovnr;
	पूर्णांक sbfqc;
	पूर्णांक lbfqc;
	काष्ठा sk_buff *sm_handle;
	u32 sm_addr;
	काष्ठा sk_buff *lg_handle;
	u32 lg_addr;
	काष्ठा sk_buff *rcbuf;	/* Current raw cell buffer */
        काष्ठा ns_rcqe *rawcell;
	u32 rawch;		/* Raw cell queue head */
	अचिन्हित पूर्णांकcnt;	/* Interrupt counter */
	spinlock_t पूर्णांक_lock;	/* Interrupt lock */
	spinlock_t res_lock;	/* Card resource lock */
पूर्ण ns_dev;

   /* NOTE: Each tste2vc entry relates a given TST entry to the corresponding
      CBR vc. If the entry is not allocated, it must be शून्य.

      There are two TSTs so the driver can modअगरy them on the fly
      without stopping the transmission.

      scd2vc allows us to find out unused fixed rate SCDs, because
      they must have a शून्य poपूर्णांकer here. */

#पूर्ण_अगर /* _LINUX_NICSTAR_H_ */
