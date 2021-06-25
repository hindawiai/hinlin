<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ICSWX api
 *
 * Copyright (C) 2015 IBM Corp.
 *
 * This provides the Initiate Coprocessor Store Word Indexed (ICSWX)
 * inकाष्ठाion.  This inकाष्ठाion is used to communicate with PowerPC
 * coprocessors.  This also provides definitions of the काष्ठाures used
 * to communicate with the coprocessor.
 *
 * The RFC02130: Coprocessor Architecture करोcument is the reference क्रम
 * everything in this file unless otherwise noted.
 */
#अगर_अघोषित _ARCH_POWERPC_INCLUDE_ASM_ICSWX_H_
#घोषणा _ARCH_POWERPC_INCLUDE_ASM_ICSWX_H_

#समावेश <यंत्र/ppc-opcode.h> /* क्रम PPC_ICSWX */

/* Chapter 6.5.8 Coprocessor-Completion Block (CCB) */

#घोषणा CCB_VALUE		(0x3fffffffffffffff)
#घोषणा CCB_ADDRESS		(0xfffffffffffffff8)
#घोषणा CCB_CM			(0x0000000000000007)
#घोषणा CCB_CM0			(0x0000000000000004)
#घोषणा CCB_CM12		(0x0000000000000003)

#घोषणा CCB_CM0_ALL_COMPLETIONS	(0x0)
#घोषणा CCB_CM0_LAST_IN_CHAIN	(0x4)
#घोषणा CCB_CM12_STORE		(0x0)
#घोषणा CCB_CM12_INTERRUPT	(0x1)

#घोषणा CCB_SIZE		(0x10)
#घोषणा CCB_ALIGN		CCB_SIZE

काष्ठा coprocessor_completion_block अणु
	__be64 value;
	__be64 address;
पूर्ण __packed __aligned(CCB_ALIGN);


/* Chapter 6.5.7 Coprocessor-Status Block (CSB) */

#घोषणा CSB_V			(0x80)
#घोषणा CSB_F			(0x04)
#घोषणा CSB_CH			(0x03)
#घोषणा CSB_CE_INCOMPLETE	(0x80)
#घोषणा CSB_CE_TERMINATION	(0x40)
#घोषणा CSB_CE_TPBC		(0x20)

#घोषणा CSB_CC_SUCCESS		(0)
#घोषणा CSB_CC_INVALID_ALIGN	(1)
#घोषणा CSB_CC_OPERAND_OVERLAP	(2)
#घोषणा CSB_CC_DATA_LENGTH	(3)
#घोषणा CSB_CC_TRANSLATION	(5)
#घोषणा CSB_CC_PROTECTION	(6)
#घोषणा CSB_CC_RD_EXTERNAL	(7)
#घोषणा CSB_CC_INVALID_OPERAND	(8)
#घोषणा CSB_CC_PRIVILEGE	(9)
#घोषणा CSB_CC_INTERNAL		(10)
#घोषणा CSB_CC_WR_EXTERNAL	(12)
#घोषणा CSB_CC_NOSPC		(13)
#घोषणा CSB_CC_EXCESSIVE_DDE	(14)
#घोषणा CSB_CC_WR_TRANSLATION	(15)
#घोषणा CSB_CC_WR_PROTECTION	(16)
#घोषणा CSB_CC_UNKNOWN_CODE	(17)
#घोषणा CSB_CC_ABORT		(18)
#घोषणा CSB_CC_EXCEED_BYTE_COUNT	(19)	/* P9 or later */
#घोषणा CSB_CC_TRANSPORT	(20)
#घोषणा CSB_CC_INVALID_CRB	(21)	/* P9 or later */
#घोषणा CSB_CC_INVALID_DDE	(30)	/* P9 or later */
#घोषणा CSB_CC_SEGMENTED_DDL	(31)
#घोषणा CSB_CC_PROGRESS_POINT	(32)
#घोषणा CSB_CC_DDE_OVERFLOW	(33)
#घोषणा CSB_CC_SESSION		(34)
#घोषणा CSB_CC_PROVISION	(36)
#घोषणा CSB_CC_CHAIN		(37)
#घोषणा CSB_CC_SEQUENCE		(38)
#घोषणा CSB_CC_HW		(39)
/* P9 DD2 NX Workbook 3.2 (Table 4-36): Address translation fault */
#घोषणा	CSB_CC_FAULT_ADDRESS	(250)

#घोषणा CSB_SIZE		(0x10)
#घोषणा CSB_ALIGN		CSB_SIZE

काष्ठा coprocessor_status_block अणु
	u8 flags;
	u8 cs;
	u8 cc;
	u8 ce;
	__be32 count;
	__be64 address;
पूर्ण __packed __aligned(CSB_ALIGN);


/* Chapter 6.5.10 Data-Descriptor List (DDL)
 * each list contains one or more Data-Descriptor Entries (DDE)
 */

#घोषणा DDE_P			(0x8000)

#घोषणा DDE_SIZE		(0x10)
#घोषणा DDE_ALIGN		DDE_SIZE

काष्ठा data_descriptor_entry अणु
	__be16 flags;
	u8 count;
	u8 index;
	__be32 length;
	__be64 address;
पूर्ण __packed __aligned(DDE_ALIGN);

/* 4.3.2 NX-stamped Fault CRB */

#घोषणा NX_STAMP_ALIGN          (0x10)

काष्ठा nx_fault_stamp अणु
	__be64 fault_storage_addr;
	__be16 reserved;
	__u8   flags;
	__u8   fault_status;
	__be32 pswid;
पूर्ण __packed __aligned(NX_STAMP_ALIGN);

/* Chapter 6.5.2 Coprocessor-Request Block (CRB) */

#घोषणा CRB_SIZE		(0x80)
#घोषणा CRB_ALIGN		(0x100) /* Errata: requires 256 alignment */

/* Coprocessor Status Block field
 *   ADDRESS	address of CSB
 *   C		CCB is valid
 *   AT		0 = addrs are भव, 1 = addrs are phys
 *   M		enable perf monitor
 */
#घोषणा CRB_CSB_ADDRESS		(0xfffffffffffffff0)
#घोषणा CRB_CSB_C		(0x0000000000000008)
#घोषणा CRB_CSB_AT		(0x0000000000000002)
#घोषणा CRB_CSB_M		(0x0000000000000001)

काष्ठा coprocessor_request_block अणु
	__be32 ccw;
	__be32 flags;
	__be64 csb_addr;

	काष्ठा data_descriptor_entry source;
	काष्ठा data_descriptor_entry target;

	काष्ठा coprocessor_completion_block ccb;

	जोड़ अणु
		काष्ठा nx_fault_stamp nx;
		u8 reserved[16];
	पूर्ण stamp;

	u8 reserved[32];

	काष्ठा coprocessor_status_block csb;
पूर्ण __aligned(128);

/* RFC02167 Initiate Coprocessor Inकाष्ठाions करोcument
 * Chapter 8.2.1.1.1 RS
 * Chapter 8.2.3 Coprocessor Directive
 * Chapter 8.2.4 Execution
 *
 * The CCW must be converted to BE beक्रमe passing to icswx()
 */

#घोषणा CCW_PS			(0xff000000)
#घोषणा CCW_CT			(0x00ff0000)
#घोषणा CCW_CD			(0x0000ffff)
#घोषणा CCW_CL			(0x0000c000)


/* RFC02167 Initiate Coprocessor Inकाष्ठाions करोcument
 * Chapter 8.2.1 Initiate Coprocessor Store Word Indexed (ICSWX)
 * Chapter 8.2.4.1 Condition Register 0
 */

#घोषणा ICSWX_INITIATED		(0x8)
#घोषणा ICSWX_BUSY		(0x4)
#घोषणा ICSWX_REJECTED		(0x2)
#घोषणा ICSWX_XERS0		(0x1)	/* undefined or set from XERSO. */

अटल अंतरभूत पूर्णांक icswx(__be32 ccw, काष्ठा coprocessor_request_block *crb)
अणु
	__be64 ccw_reg = ccw;
	u32 cr;

	/* NB: the same काष्ठाures are used by VAS-NX */
	BUILD_BUG_ON(माप(*crb) != 128);

	__यंत्र__ __अस्थिर__(
	PPC_ICSWX(%1,0,%2) "\n"
	"mfcr %0\n"
	: "=r" (cr)
	: "r" (ccw_reg), "r" (crb)
	: "cr0", "memory");

	वापस (पूर्णांक)((cr >> 28) & 0xf);
पूर्ण


#पूर्ण_अगर /* _ARCH_POWERPC_INCLUDE_ASM_ICSWX_H_ */
