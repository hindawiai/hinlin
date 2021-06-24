<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Handles the M-Systems DiskOnChip G3 chip
 *
 * Copyright (C) 2011 Robert Jarzmik
 */

#अगर_अघोषित _MTD_DOCG3_H
#घोषणा _MTD_DOCG3_H

#समावेश <linux/mtd/mtd.h>

/*
 * Flash memory areas :
 *   - 0x0000 .. 0x07ff : IPL
 *   - 0x0800 .. 0x0fff : Data area
 *   - 0x1000 .. 0x17ff : Registers
 *   - 0x1800 .. 0x1fff : Unknown
 */
#घोषणा DOC_IOSPACE_IPL			0x0000
#घोषणा DOC_IOSPACE_DATA		0x0800
#घोषणा DOC_IOSPACE_SIZE		0x2000

/*
 * DOC G3 layout and adressing scheme
 *   A page address क्रम the block "b", plane "P" and page "p":
 *   address = [bbbb bPpp pppp]
 */

#घोषणा DOC_ADDR_PAGE_MASK		0x3f
#घोषणा DOC_ADDR_BLOCK_SHIFT		6
#घोषणा DOC_LAYOUT_NBPLANES		2
#घोषणा DOC_LAYOUT_PAGES_PER_BLOCK	64
#घोषणा DOC_LAYOUT_PAGE_SIZE		512
#घोषणा DOC_LAYOUT_OOB_SIZE		16
#घोषणा DOC_LAYOUT_WEAR_SIZE		8
#घोषणा DOC_LAYOUT_PAGE_OOB_SIZE				\
	(DOC_LAYOUT_PAGE_SIZE + DOC_LAYOUT_OOB_SIZE)
#घोषणा DOC_LAYOUT_WEAR_OFFSET		(DOC_LAYOUT_PAGE_OOB_SIZE * 2)
#घोषणा DOC_LAYOUT_BLOCK_SIZE					\
	(DOC_LAYOUT_PAGES_PER_BLOCK * DOC_LAYOUT_PAGE_SIZE)

/*
 * ECC related स्थिरants
 */
#घोषणा DOC_ECC_BCH_M			14
#घोषणा DOC_ECC_BCH_T			4
#घोषणा DOC_ECC_BCH_PRIMPOLY		0x4443
#घोषणा DOC_ECC_BCH_SIZE		7
#घोषणा DOC_ECC_BCH_COVERED_BYTES				\
	(DOC_LAYOUT_PAGE_SIZE + DOC_LAYOUT_OOB_PAGEINFO_SZ +	\
	 DOC_LAYOUT_OOB_HAMMING_SZ)
#घोषणा DOC_ECC_BCH_TOTAL_BYTES					\
	(DOC_ECC_BCH_COVERED_BYTES + DOC_LAYOUT_OOB_BCH_SZ)

/*
 * Blocks distribution
 */
#घोषणा DOC_LAYOUT_BLOCK_BBT		0
#घोषणा DOC_LAYOUT_BLOCK_OTP		0
#घोषणा DOC_LAYOUT_BLOCK_FIRST_DATA	6

#घोषणा DOC_LAYOUT_PAGE_BBT		4

/*
 * Extra page OOB (16 bytes wide) layout
 */
#घोषणा DOC_LAYOUT_OOB_PAGEINFO_OFS	0
#घोषणा DOC_LAYOUT_OOB_HAMMING_OFS	7
#घोषणा DOC_LAYOUT_OOB_BCH_OFS		8
#घोषणा DOC_LAYOUT_OOB_UNUSED_OFS	15
#घोषणा DOC_LAYOUT_OOB_PAGEINFO_SZ	7
#घोषणा DOC_LAYOUT_OOB_HAMMING_SZ	1
#घोषणा DOC_LAYOUT_OOB_BCH_SZ		7
#घोषणा DOC_LAYOUT_OOB_UNUSED_SZ	1


#घोषणा DOC_CHIPID_G3			0x200
#घोषणा DOC_ERASE_MARK			0xaa
#घोषणा DOC_MAX_NBFLOORS		4
/*
 * Flash रेजिस्टरs
 */
#घोषणा DOC_CHIPID			0x1000
#घोषणा DOC_TEST			0x1004
#घोषणा DOC_BUSLOCK			0x1006
#घोषणा DOC_ENDIANCONTROL		0x1008
#घोषणा DOC_DEVICESELECT		0x100a
#घोषणा DOC_ASICMODE			0x100c
#घोषणा DOC_CONFIGURATION		0x100e
#घोषणा DOC_INTERRUPTCONTROL		0x1010
#घोषणा DOC_READADDRESS			0x101a
#घोषणा DOC_DATAEND			0x101e
#घोषणा DOC_INTERRUPTSTATUS		0x1020

#घोषणा DOC_FLASHSEQUENCE		0x1032
#घोषणा DOC_FLASHCOMMAND		0x1034
#घोषणा DOC_FLASHADDRESS		0x1036
#घोषणा DOC_FLASHCONTROL		0x1038
#घोषणा DOC_NOP				0x103e

#घोषणा DOC_ECCCONF0			0x1040
#घोषणा DOC_ECCCONF1			0x1042
#घोषणा DOC_ECCPRESET			0x1044
#घोषणा DOC_HAMMINGPARITY		0x1046
#घोषणा DOC_BCH_HW_ECC(idx)		(0x1048 + idx)

#घोषणा DOC_PROTECTION			0x1056
#घोषणा DOC_DPS0_KEY			0x105c
#घोषणा DOC_DPS1_KEY			0x105e
#घोषणा DOC_DPS0_ADDRLOW		0x1060
#घोषणा DOC_DPS0_ADDRHIGH		0x1062
#घोषणा DOC_DPS1_ADDRLOW		0x1064
#घोषणा DOC_DPS1_ADDRHIGH		0x1066
#घोषणा DOC_DPS0_STATUS			0x106c
#घोषणा DOC_DPS1_STATUS			0x106e

#घोषणा DOC_ASICMODECONFIRM		0x1072
#घोषणा DOC_CHIPID_INV			0x1074
#घोषणा DOC_POWERMODE			0x107c

/*
 * Flash sequences
 * A sequence is preset beक्रमe one or more commands are input to the chip.
 */
#घोषणा DOC_SEQ_RESET			0x00
#घोषणा DOC_SEQ_PAGE_SIZE_532		0x03
#घोषणा DOC_SEQ_SET_FASTMODE		0x05
#घोषणा DOC_SEQ_SET_RELIABLEMODE	0x09
#घोषणा DOC_SEQ_READ			0x12
#घोषणा DOC_SEQ_SET_PLANE1		0x0e
#घोषणा DOC_SEQ_SET_PLANE2		0x10
#घोषणा DOC_SEQ_PAGE_SETUP		0x1d
#घोषणा DOC_SEQ_ERASE			0x27
#घोषणा DOC_SEQ_PLANES_STATUS		0x31

/*
 * Flash commands
 */
#घोषणा DOC_CMD_READ_PLANE1		0x00
#घोषणा DOC_CMD_SET_ADDR_READ		0x05
#घोषणा DOC_CMD_READ_ALL_PLANES		0x30
#घोषणा DOC_CMD_READ_PLANE2		0x50
#घोषणा DOC_CMD_READ_FLASH		0xe0
#घोषणा DOC_CMD_PAGE_SIZE_532		0x3c

#घोषणा DOC_CMD_PROG_BLOCK_ADDR		0x60
#घोषणा DOC_CMD_PROG_CYCLE1		0x80
#घोषणा DOC_CMD_PROG_CYCLE2		0x10
#घोषणा DOC_CMD_PROG_CYCLE3		0x11
#घोषणा DOC_CMD_ERASECYCLE2		0xd0
#घोषणा DOC_CMD_READ_STATUS		0x70
#घोषणा DOC_CMD_PLANES_STATUS		0x71

#घोषणा DOC_CMD_RELIABLE_MODE		0x22
#घोषणा DOC_CMD_FAST_MODE		0xa2

#घोषणा DOC_CMD_RESET			0xff

/*
 * Flash रेजिस्टर : DOC_FLASHCONTROL
 */
#घोषणा DOC_CTRL_VIOLATION		0x20
#घोषणा DOC_CTRL_CE			0x10
#घोषणा DOC_CTRL_UNKNOWN_BITS		0x08
#घोषणा DOC_CTRL_PROTECTION_ERROR	0x04
#घोषणा DOC_CTRL_SEQUENCE_ERROR		0x02
#घोषणा DOC_CTRL_FLASHREADY		0x01

/*
 * Flash रेजिस्टर : DOC_ASICMODE
 */
#घोषणा DOC_ASICMODE_RESET		0x00
#घोषणा DOC_ASICMODE_NORMAL		0x01
#घोषणा DOC_ASICMODE_POWERDOWN		0x02
#घोषणा DOC_ASICMODE_MDWREN		0x04
#घोषणा DOC_ASICMODE_BDETCT_RESET	0x08
#घोषणा DOC_ASICMODE_RSTIN_RESET	0x10
#घोषणा DOC_ASICMODE_RAM_WE		0x20

/*
 * Flash रेजिस्टर : DOC_ECCCONF0
 */
#घोषणा DOC_ECCCONF0_WRITE_MODE		0x0000
#घोषणा DOC_ECCCONF0_READ_MODE		0x8000
#घोषणा DOC_ECCCONF0_AUTO_ECC_ENABLE	0x4000
#घोषणा DOC_ECCCONF0_HAMMING_ENABLE	0x1000
#घोषणा DOC_ECCCONF0_BCH_ENABLE		0x0800
#घोषणा DOC_ECCCONF0_DATA_BYTES_MASK	0x07ff

/*
 * Flash रेजिस्टर : DOC_ECCCONF1
 */
#घोषणा DOC_ECCCONF1_BCH_SYNDROM_ERR	0x80
#घोषणा DOC_ECCCONF1_UNKOWN1		0x40
#घोषणा DOC_ECCCONF1_PAGE_IS_WRITTEN	0x20
#घोषणा DOC_ECCCONF1_UNKOWN3		0x10
#घोषणा DOC_ECCCONF1_HAMMING_BITS_MASK	0x0f

/*
 * Flash रेजिस्टर : DOC_PROTECTION
 */
#घोषणा DOC_PROTECT_FOUNDRY_OTP_LOCK	0x01
#घोषणा DOC_PROTECT_CUSTOMER_OTP_LOCK	0x02
#घोषणा DOC_PROTECT_LOCK_INPUT		0x04
#घोषणा DOC_PROTECT_STICKY_LOCK		0x08
#घोषणा DOC_PROTECT_PROTECTION_ENABLED	0x10
#घोषणा DOC_PROTECT_IPL_DOWNLOAD_LOCK	0x20
#घोषणा DOC_PROTECT_PROTECTION_ERROR	0x80

/*
 * Flash रेजिस्टर : DOC_DPS0_STATUS and DOC_DPS1_STATUS
 */
#घोषणा DOC_DPS_OTP_PROTECTED		0x01
#घोषणा DOC_DPS_READ_PROTECTED		0x02
#घोषणा DOC_DPS_WRITE_PROTECTED		0x04
#घोषणा DOC_DPS_HW_LOCK_ENABLED		0x08
#घोषणा DOC_DPS_KEY_OK			0x80

/*
 * Flash रेजिस्टर : DOC_CONFIGURATION
 */
#घोषणा DOC_CONF_IF_CFG			0x80
#घोषणा DOC_CONF_MAX_ID_MASK		0x30
#घोषणा DOC_CONF_VCCQ_3V		0x01

/*
 * Flash रेजिस्टर : DOC_READADDRESS
 */
#घोषणा DOC_READADDR_INC		0x8000
#घोषणा DOC_READADDR_ONE_BYTE		0x4000
#घोषणा DOC_READADDR_ADDR_MASK		0x1fff

/*
 * Flash रेजिस्टर : DOC_POWERMODE
 */
#घोषणा DOC_POWERDOWN_READY		0x80

/*
 * Status of erase and ग_लिखो operation
 */
#घोषणा DOC_PLANES_STATUS_FAIL		0x01
#घोषणा DOC_PLANES_STATUS_PLANE0_KO	0x02
#घोषणा DOC_PLANES_STATUS_PLANE1_KO	0x04

/*
 * DPS key management
 *
 * Each न्यूनमान of करोcg3 has 2 protection areas: DPS0 and DPS1. These areas span
 * across block boundaries, and define whether these blocks can be पढ़ो or
 * written.
 * The definition is dynamically stored in page 0 of blocks (2,3) क्रम DPS0, and
 * page 0 of blocks (4,5) क्रम DPS1.
 */
#घोषणा DOC_LAYOUT_DPS_KEY_LENGTH	8

/**
 * काष्ठा करोcg3_cascade - Cascade of 1 to 4 करोcg3 chips
 * @न्यूनमानs: न्यूनमानs (ie. one physical करोcg3 chip is one न्यूनमान)
 * @base: IO space to access all chips in the cascade
 * @bch: the BCH correcting control काष्ठाure
 * @lock: lock to protect करोcg3 IO space from concurrent accesses
 */
काष्ठा करोcg3_cascade अणु
	काष्ठा mtd_info *न्यूनमानs[DOC_MAX_NBFLOORS];
	व्योम __iomem *base;
	काष्ठा bch_control *bch;
	काष्ठा mutex lock;
पूर्ण;

/**
 * काष्ठा करोcg3 - DiskOnChip driver निजी data
 * @dev: the device currently under control
 * @cascade: the cascade this device beदीर्घs to
 * @device_id: number of the cascaded DoCG3 device (0, 1, 2 or 3)
 * @अगर_cfg: अगर true, पढ़ोs are on 16bits, अन्यथा पढ़ोs are on 8bits

 * @reliable: अगर 0, करोcg3 in normal mode, अगर 1 करोcg3 in fast mode, अगर 2 in
 *            reliable mode
 *            Fast mode implies more errors than normal mode.
 *            Reliable mode implies that page 2*n and 2*n+1 are clones.
 * @bbt: bad block table cache
 * @oob_ग_लिखो_ofs: offset of the MTD where this OOB should beदीर्घ (ie. in next
 *                 page_ग_लिखो)
 * @oob_स्वतःecc: अगर 1, use only bytes 0-7, 15, and fill the others with HW ECC
 *               अगर 0, use all the 16 bytes.
 * @oob_ग_लिखो_buf: prepared OOB क्रम next page_ग_लिखो
 */
काष्ठा करोcg3 अणु
	काष्ठा device *dev;
	काष्ठा करोcg3_cascade *cascade;
	अचिन्हित पूर्णांक device_id:4;
	अचिन्हित पूर्णांक अगर_cfg:1;
	अचिन्हित पूर्णांक reliable:2;
	पूर्णांक max_block;
	u8 *bbt;
	loff_t oob_ग_लिखो_ofs;
	पूर्णांक oob_स्वतःecc;
	u8 oob_ग_लिखो_buf[DOC_LAYOUT_OOB_SIZE];
पूर्ण;

#घोषणा करोc_err(fmt, arg...) dev_err(करोcg3->dev, (fmt), ## arg)
#घोषणा करोc_info(fmt, arg...) dev_info(करोcg3->dev, (fmt), ## arg)
#घोषणा करोc_dbg(fmt, arg...) dev_dbg(करोcg3->dev, (fmt), ## arg)
#घोषणा करोc_vdbg(fmt, arg...) dev_vdbg(करोcg3->dev, (fmt), ## arg)
#पूर्ण_अगर

/*
 * Trace events part
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM करोcg3

#अगर !defined(_MTD_DOCG3_TRACE) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _MTD_DOCG3_TRACE

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(करोcg3_io,
	    TP_PROTO(पूर्णांक op, पूर्णांक width, u16 reg, पूर्णांक val),
	    TP_ARGS(op, width, reg, val),
	    TP_STRUCT__entry(
		    __field(पूर्णांक, op)
		    __field(अचिन्हित अक्षर, width)
		    __field(u16, reg)
		    __field(पूर्णांक, val)),
	    TP_fast_assign(
		    __entry->op = op;
		    __entry->width = width;
		    __entry->reg = reg;
		    __entry->val = val;),
	    TP_prपूर्णांकk("docg3: %s%02d reg=%04x, val=%04x",
		      __entry->op ? "write" : "read", __entry->width,
		      __entry->reg, __entry->val)
	);
#पूर्ण_अगर

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता करोcg3
#समावेश <trace/define_trace.h>
