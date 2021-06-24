<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __CRB_H
#घोषणा __CRB_H
#समावेश <linux/types.h>
#समावेश "nx.h"

/* CCW 842 CI/FC masks
 * NX P8 workbook, section 4.3.1, figure 4-6
 * "CI/FC Boundary by NX CT type"
 */
#घोषणा CCW_CI_842              (0x00003ff8)
#घोषणा CCW_FC_842              (0x00000007)

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
पूर्ण __aligned(CCB_ALIGN);


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
#घोषणा CSB_CC_TRANSPORT	(20)
#घोषणा CSB_CC_SEGMENTED_DDL	(31)
#घोषणा CSB_CC_PROGRESS_POINT	(32)
#घोषणा CSB_CC_DDE_OVERFLOW	(33)
#घोषणा CSB_CC_SESSION		(34)
#घोषणा CSB_CC_PROVISION	(36)
#घोषणा CSB_CC_CHAIN		(37)
#घोषणा CSB_CC_SEQUENCE		(38)
#घोषणा CSB_CC_HW		(39)

#घोषणा CSB_SIZE		(0x10)
#घोषणा CSB_ALIGN		CSB_SIZE

काष्ठा coprocessor_status_block अणु
	__u8 flags;
	__u8 cs;
	__u8 cc;
	__u8 ce;
	__be32 count;
	__be64 address;
पूर्ण __aligned(CSB_ALIGN);


/* Chapter 6.5.10 Data-Descriptor List (DDL)
 * each list contains one or more Data-Descriptor Entries (DDE)
 */

#घोषणा DDE_P			(0x8000)

#घोषणा DDE_SIZE		(0x10)
#घोषणा DDE_ALIGN		DDE_SIZE

काष्ठा data_descriptor_entry अणु
	__be16 flags;
	__u8 count;
	__u8 index;
	__be32 length;
	__be64 address;
पूर्ण __aligned(DDE_ALIGN);


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

	__u8 reserved[48];

	काष्ठा coprocessor_status_block csb;
पूर्ण __aligned(CRB_ALIGN);

#घोषणा crb_csb_addr(c)         __be64_to_cpu(c->csb_addr)
#घोषणा crb_nx_fault_addr(c)    __be64_to_cpu(c->stamp.nx.fault_storage_addr)
#घोषणा crb_nx_flags(c)         c->stamp.nx.flags
#घोषणा crb_nx_fault_status(c)  c->stamp.nx.fault_status
#घोषणा crb_nx_pswid(c)		c->stamp.nx.pswid


/* RFC02167 Initiate Coprocessor Inकाष्ठाions करोcument
 * Chapter 8.2.1.1.1 RS
 * Chapter 8.2.3 Coprocessor Directive
 * Chapter 8.2.4 Execution
 *
 * The CCW must be converted to BE beक्रमe passing to icswx()
 */

#घोषणा CCW_PS                  (0xff000000)
#घोषणा CCW_CT                  (0x00ff0000)
#घोषणा CCW_CD                  (0x0000ffff)
#घोषणा CCW_CL                  (0x0000c000)

#पूर्ण_अगर
