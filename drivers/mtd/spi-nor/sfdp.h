<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __LINUX_MTD_SFDP_H
#घोषणा __LINUX_MTD_SFDP_H

/* SFDP revisions */
#घोषणा SFDP_JESD216_MAJOR	1
#घोषणा SFDP_JESD216_MINOR	0
#घोषणा SFDP_JESD216A_MINOR	5
#घोषणा SFDP_JESD216B_MINOR	6

/* Basic Flash Parameter Table */

/*
 * JESD216 rev D defines a Basic Flash Parameter Table of 20 DWORDs.
 * They are indexed from 1 but C arrays are indexed from 0.
 */
#घोषणा BFPT_DWORD(i)		((i) - 1)
#घोषणा BFPT_DWORD_MAX		20

काष्ठा sfdp_bfpt अणु
	u32	dwords[BFPT_DWORD_MAX];
पूर्ण;

/* The first version of JESD216 defined only 9 DWORDs. */
#घोषणा BFPT_DWORD_MAX_JESD216			9
#घोषणा BFPT_DWORD_MAX_JESD216B			16

/* 1st DWORD. */
#घोषणा BFPT_DWORD1_FAST_READ_1_1_2		BIT(16)
#घोषणा BFPT_DWORD1_ADDRESS_BYTES_MASK		GENMASK(18, 17)
#घोषणा BFPT_DWORD1_ADDRESS_BYTES_3_ONLY	(0x0UL << 17)
#घोषणा BFPT_DWORD1_ADDRESS_BYTES_3_OR_4	(0x1UL << 17)
#घोषणा BFPT_DWORD1_ADDRESS_BYTES_4_ONLY	(0x2UL << 17)
#घोषणा BFPT_DWORD1_DTR				BIT(19)
#घोषणा BFPT_DWORD1_FAST_READ_1_2_2		BIT(20)
#घोषणा BFPT_DWORD1_FAST_READ_1_4_4		BIT(21)
#घोषणा BFPT_DWORD1_FAST_READ_1_1_4		BIT(22)

/* 5th DWORD. */
#घोषणा BFPT_DWORD5_FAST_READ_2_2_2		BIT(0)
#घोषणा BFPT_DWORD5_FAST_READ_4_4_4		BIT(4)

/* 11th DWORD. */
#घोषणा BFPT_DWORD11_PAGE_SIZE_SHIFT		4
#घोषणा BFPT_DWORD11_PAGE_SIZE_MASK		GENMASK(7, 4)

/* 15th DWORD. */

/*
 * (from JESD216 rev B)
 * Quad Enable Requirements (QER):
 * - 000b: Device करोes not have a QE bit. Device detects 1-1-4 and 1-4-4
 *         पढ़ोs based on inकाष्ठाion. DQ3/HOLD# functions are hold during
 *         inकाष्ठाion phase.
 * - 001b: QE is bit 1 of status रेजिस्टर 2. It is set via Write Status with
 *         two data bytes where bit 1 of the second byte is one.
 *         [...]
 *         Writing only one byte to the status रेजिस्टर has the side-effect of
 *         clearing status रेजिस्टर 2, including the QE bit. The 100b code is
 *         used अगर writing one byte to the status रेजिस्टर करोes not modअगरy
 *         status रेजिस्टर 2.
 * - 010b: QE is bit 6 of status रेजिस्टर 1. It is set via Write Status with
 *         one data byte where bit 6 is one.
 *         [...]
 * - 011b: QE is bit 7 of status रेजिस्टर 2. It is set via Write status
 *         रेजिस्टर 2 inकाष्ठाion 3Eh with one data byte where bit 7 is one.
 *         [...]
 *         The status रेजिस्टर 2 is पढ़ो using inकाष्ठाion 3Fh.
 * - 100b: QE is bit 1 of status रेजिस्टर 2. It is set via Write Status with
 *         two data bytes where bit 1 of the second byte is one.
 *         [...]
 *         In contrast to the 001b code, writing one byte to the status
 *         रेजिस्टर करोes not modअगरy status रेजिस्टर 2.
 * - 101b: QE is bit 1 of status रेजिस्टर 2. Status रेजिस्टर 1 is पढ़ो using
 *         Read Status inकाष्ठाion 05h. Status रेजिस्टर2 is पढ़ो using
 *         inकाष्ठाion 35h. QE is set via Write Status inकाष्ठाion 01h with
 *         two data bytes where bit 1 of the second byte is one.
 *         [...]
 */
#घोषणा BFPT_DWORD15_QER_MASK			GENMASK(22, 20)
#घोषणा BFPT_DWORD15_QER_NONE			(0x0UL << 20) /* Micron */
#घोषणा BFPT_DWORD15_QER_SR2_BIT1_BUGGY		(0x1UL << 20)
#घोषणा BFPT_DWORD15_QER_SR1_BIT6		(0x2UL << 20) /* Macronix */
#घोषणा BFPT_DWORD15_QER_SR2_BIT7		(0x3UL << 20)
#घोषणा BFPT_DWORD15_QER_SR2_BIT1_NO_RD		(0x4UL << 20)
#घोषणा BFPT_DWORD15_QER_SR2_BIT1		(0x5UL << 20) /* Spansion */

#घोषणा BFPT_DWORD16_SWRST_EN_RST		BIT(12)

#घोषणा BFPT_DWORD18_CMD_EXT_MASK		GENMASK(30, 29)
#घोषणा BFPT_DWORD18_CMD_EXT_REP		(0x0UL << 29) /* Repeat */
#घोषणा BFPT_DWORD18_CMD_EXT_INV		(0x1UL << 29) /* Invert */
#घोषणा BFPT_DWORD18_CMD_EXT_RES		(0x2UL << 29) /* Reserved */
#घोषणा BFPT_DWORD18_CMD_EXT_16B		(0x3UL << 29) /* 16-bit opcode */

काष्ठा sfdp_parameter_header अणु
	u8		id_lsb;
	u8		minor;
	u8		major;
	u8		length; /* in द्विगुन words */
	u8		parameter_table_poपूर्णांकer[3]; /* byte address */
	u8		id_msb;
पूर्ण;

पूर्णांक spi_nor_parse_sfdp(काष्ठा spi_nor *nor);

#पूर्ण_अगर /* __LINUX_MTD_SFDP_H */
