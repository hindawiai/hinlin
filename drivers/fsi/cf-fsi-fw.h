<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
#अगर_अघोषित __CF_FSI_FW_H
#घोषणा __CF_FSI_FW_H

/*
 * uCode file layout
 *
 * 0000...03ff : m68k exception vectors
 * 0400...04ff : Header info & boot config block
 * 0500....... : Code & stack
 */

/*
 * Header info & boot config area
 *
 * The Header info is built पूर्णांकo the ucode and provide version and
 * platक्रमm inक्रमmation.
 *
 * the Boot config needs to be adjusted by the ARM prior to starting
 * the ucode अगर the Command/Status area isn't at 0x320000 in CF space
 * (ie. beginning of SRAM).
 */

#घोषणा HDR_OFFSET	        0x400

/* Info: Signature & version */
#घोषणा HDR_SYS_SIG		0x00	/* 2 bytes प्रणाली signature */
#घोषणा  SYS_SIG_SHARED		0x5348
#घोषणा  SYS_SIG_SPLIT		0x5350
#घोषणा HDR_FW_VERS		0x02	/* 2 bytes Major.Minor */
#घोषणा HDR_API_VERS		0x04	/* 2 bytes Major.Minor */
#घोषणा  API_VERSION_MAJ	2	/* Current version */
#घोषणा  API_VERSION_MIN	1
#घोषणा HDR_FW_OPTIONS		0x08	/* 4 bytes option flags */
#घोषणा  FW_OPTION_TRACE_EN	0x00000001	/* FW tracing enabled */
#घोषणा	 FW_OPTION_CONT_CLOCK	0x00000002	/* Continuous घड़ीing supported */
#घोषणा HDR_FW_SIZE		0x10	/* 4 bytes size क्रम combo image */

/* Boot Config: Address of Command/Status area */
#घोषणा HDR_CMD_STAT_AREA	0x80	/* 4 bytes CF address */
#घोषणा HDR_FW_CONTROL		0x84	/* 4 bytes control flags */
#घोषणा	 FW_CONTROL_CONT_CLOCK	0x00000002	/* Continuous घड़ीing enabled */
#घोषणा	 FW_CONTROL_DUMMY_RD	0x00000004	/* Extra dummy पढ़ो (AST2400) */
#घोषणा	 FW_CONTROL_USE_STOP	0x00000008	/* Use STOP inकाष्ठाions */
#घोषणा HDR_CLOCK_GPIO_VADDR	0x90	/* 2 bytes offset from GPIO base */
#घोषणा HDR_CLOCK_GPIO_DADDR	0x92	/* 2 bytes offset from GPIO base */
#घोषणा HDR_DATA_GPIO_VADDR	0x94	/* 2 bytes offset from GPIO base */
#घोषणा HDR_DATA_GPIO_DADDR	0x96	/* 2 bytes offset from GPIO base */
#घोषणा HDR_TRANS_GPIO_VADDR	0x98	/* 2 bytes offset from GPIO base */
#घोषणा HDR_TRANS_GPIO_DADDR	0x9a	/* 2 bytes offset from GPIO base */
#घोषणा HDR_CLOCK_GPIO_BIT	0x9c	/* 1 byte bit number */
#घोषणा HDR_DATA_GPIO_BIT	0x9d	/* 1 byte bit number */
#घोषणा HDR_TRANS_GPIO_BIT	0x9e	/* 1 byte bit number */

/*
 *  Command/Status area layout: Main part
 */

/* Command/Status रेजिस्टर:
 *
 * +---------------------------+
 * | STAT | RLEN | CLEN | CMD  |
 * |   8  |   8  |   8  |   8  |
 * +---------------------------+
 *    |       |      |      |
 *    status  |      |      |
 * Response len      |      |
 * (in bits)         |      |
 *                   |      |
 *         Command len      |
 *         (in bits)        |
 *                          |
 *               Command code
 *
 * Due to the big endian layout, that means that a byte पढ़ो will
 * वापस the status byte
 */
#घोषणा	CMD_STAT_REG	        0x00
#घोषणा  CMD_REG_CMD_MASK	0x000000ff
#घोषणा  CMD_REG_CMD_SHIFT	0
#घोषणा	  CMD_NONE		0x00
#घोषणा	  CMD_COMMAND		0x01
#घोषणा	  CMD_BREAK		0x02
#घोषणा	  CMD_IDLE_CLOCKS	0x03 /* clen = #घड़ीs */
#घोषणा   CMD_INVALID		0xff
#घोषणा  CMD_REG_CLEN_MASK	0x0000ff00
#घोषणा  CMD_REG_CLEN_SHIFT	8
#घोषणा  CMD_REG_RLEN_MASK	0x00ff0000
#घोषणा  CMD_REG_RLEN_SHIFT	16
#घोषणा  CMD_REG_STAT_MASK	0xff000000
#घोषणा  CMD_REG_STAT_SHIFT	24
#घोषणा	  STAT_WORKING		0x00
#घोषणा	  STAT_COMPLETE		0x01
#घोषणा	  STAT_ERR_INVAL_CMD	0x80
#घोषणा	  STAT_ERR_INVAL_IRQ	0x81
#घोषणा	  STAT_ERR_MTOE		0x82

/* Response tag & CRC */
#घोषणा	STAT_RTAG		0x04

/* Response CRC */
#घोषणा	STAT_RCRC		0x05

/* Echo and Send delay */
#घोषणा	ECHO_DLY_REG		0x08
#घोषणा	SEND_DLY_REG		0x09

/* Command data area
 *
 * Last byte of message must be left aligned
 */
#घोषणा	CMD_DATA		0x10 /* 64 bit of data */

/* Response data area, right aligned, unused top bits are 1 */
#घोषणा	RSP_DATA		0x20 /* 32 bit of data */

/* Misc */
#घोषणा	INT_CNT			0x30 /* 32-bit पूर्णांकerrupt count */
#घोषणा	BAD_INT_VEC		0x34 /* 32-bit bad पूर्णांकerrupt vector # */
#घोषणा	CF_STARTED		0x38 /* byte, set to -1 when copro started */
#घोषणा	CLK_CNT			0x3c /* 32-bit, घड़ी count (debug only) */

/*
 *  SRAM layout: GPIO arbitration part
 */
#घोषणा ARB_REG			0x40
#घोषणा  ARB_ARM_REQ		0x01
#घोषणा  ARB_ARM_ACK		0x02

/* Misc2 */
#घोषणा CF_RESET_D0		0x50
#घोषणा CF_RESET_D1		0x54
#घोषणा BAD_INT_S0		0x58
#घोषणा BAD_INT_S1		0x5c
#घोषणा STOP_CNT		0x60

/* Internal */

/*
 * SRAM layout: Trace buffer (debug builds only)
 */
#घोषणा	TRACEBUF		0x100
#घोषणा	  TR_CLKOBIT0		0xc0
#घोषणा	  TR_CLKOBIT1		0xc1
#घोषणा	  TR_CLKOSTART		0x82
#घोषणा	  TR_OLEN		0x83 /* + len */
#घोषणा	  TR_CLKZ		0x84 /* + count */
#घोषणा	  TR_CLKWSTART		0x85
#घोषणा	  TR_CLKTAG		0x86 /* + tag */
#घोषणा	  TR_CLKDATA		0x87 /* + len */
#घोषणा	  TR_CLKCRC		0x88 /* + raw crc */
#घोषणा	  TR_CLKIBIT0		0x90
#घोषणा	  TR_CLKIBIT1		0x91
#घोषणा	  TR_END		0xff

#पूर्ण_अगर /* __CF_FSI_FW_H */

