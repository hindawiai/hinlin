<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RapidIO रेजिस्टर definitions
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 */

#अगर_अघोषित LINUX_RIO_REGS_H
#घोषणा LINUX_RIO_REGS_H

/*
 * In RapidIO, each device has a 16MB configuration space that is
 * accessed via मुख्यtenance transactions.  Portions of configuration
 * space are standardized and/or reserved.
 */
#घोषणा RIO_MAINT_SPACE_SZ	0x1000000 /* 16MB of RapidIO मुख्यenance space */

#घोषणा RIO_DEV_ID_CAR		0x00	/* [I] Device Identity CAR */
#घोषणा RIO_DEV_INFO_CAR	0x04	/* [I] Device Inक्रमmation CAR */
#घोषणा RIO_ASM_ID_CAR		0x08	/* [I] Assembly Identity CAR */
#घोषणा  RIO_ASM_ID_MASK		0xffff0000	/* [I] Asm ID Mask */
#घोषणा  RIO_ASM_VEN_ID_MASK		0x0000ffff	/* [I] Asm Vend Mask */

#घोषणा RIO_ASM_INFO_CAR	0x0c	/* [I] Assembly Inक्रमmation CAR */
#घोषणा  RIO_ASM_REV_MASK		0xffff0000	/* [I] Asm Rev Mask */
#घोषणा  RIO_EXT_FTR_PTR_MASK		0x0000ffff	/* [I] EF_PTR Mask */

#घोषणा RIO_PEF_CAR		0x10	/* [I] Processing Element Features CAR */
#घोषणा  RIO_PEF_BRIDGE			0x80000000	/* [I] Bridge */
#घोषणा  RIO_PEF_MEMORY			0x40000000	/* [I] MMIO */
#घोषणा  RIO_PEF_PROCESSOR		0x20000000	/* [I] Processor */
#घोषणा  RIO_PEF_SWITCH			0x10000000	/* [I] Switch */
#घोषणा  RIO_PEF_MULTIPORT		0x08000000	/* [VI, 2.1] Multiport */
#घोषणा  RIO_PEF_INB_MBOX		0x00f00000	/* [II, <= 1.2] Mailboxes */
#घोषणा  RIO_PEF_INB_MBOX0		0x00800000	/* [II, <= 1.2] Mailbox 0 */
#घोषणा  RIO_PEF_INB_MBOX1		0x00400000	/* [II, <= 1.2] Mailbox 1 */
#घोषणा  RIO_PEF_INB_MBOX2		0x00200000	/* [II, <= 1.2] Mailbox 2 */
#घोषणा  RIO_PEF_INB_MBOX3		0x00100000	/* [II, <= 1.2] Mailbox 3 */
#घोषणा  RIO_PEF_INB_DOORBELL		0x00080000	/* [II, <= 1.2] Doorbells */
#घोषणा  RIO_PEF_DEV32			0x00001000	/* [III] PE supports Common TRansport Dev32 */
#घोषणा  RIO_PEF_EXT_RT			0x00000200	/* [III, 1.3] Extended route table support */
#घोषणा  RIO_PEF_STD_RT			0x00000100	/* [III, 1.3] Standard route table support */
#घोषणा  RIO_PEF_CTLS			0x00000010	/* [III] Common Transport Large System (< rev.3) */
#घोषणा  RIO_PEF_DEV16			0x00000010	/* [III] PE Supports Common Transport Dev16 (rev.3) */
#घोषणा  RIO_PEF_EXT_FEATURES		0x00000008	/* [I] EFT_PTR valid */
#घोषणा  RIO_PEF_ADDR_66		0x00000004	/* [I] 66 bits */
#घोषणा  RIO_PEF_ADDR_50		0x00000002	/* [I] 50 bits */
#घोषणा  RIO_PEF_ADDR_34		0x00000001	/* [I] 34 bits */

#घोषणा RIO_SWP_INFO_CAR	0x14	/* [I] Switch Port Inक्रमmation CAR */
#घोषणा  RIO_SWP_INFO_PORT_TOTAL_MASK	0x0000ff00	/* [I] Total number of ports */
#घोषणा  RIO_SWP_INFO_PORT_NUM_MASK	0x000000ff	/* [I] Maपूर्णांकenance transaction port number */
#घोषणा  RIO_GET_TOTAL_PORTS(x)		((x & RIO_SWP_INFO_PORT_TOTAL_MASK) >> 8)
#घोषणा  RIO_GET_PORT_NUM(x)		(x & RIO_SWP_INFO_PORT_NUM_MASK)

#घोषणा RIO_SRC_OPS_CAR		0x18	/* [I] Source Operations CAR */
#घोषणा  RIO_SRC_OPS_READ		0x00008000	/* [I] Read op */
#घोषणा  RIO_SRC_OPS_WRITE		0x00004000	/* [I] Write op */
#घोषणा  RIO_SRC_OPS_STREAM_WRITE	0x00002000	/* [I] Str-ग_लिखो op */
#घोषणा  RIO_SRC_OPS_WRITE_RESPONSE	0x00001000	/* [I] Write/resp op */
#घोषणा  RIO_SRC_OPS_DATA_MSG		0x00000800	/* [II] Data msg op */
#घोषणा  RIO_SRC_OPS_DOORBELL		0x00000400	/* [II] Doorbell op */
#घोषणा  RIO_SRC_OPS_ATOMIC_TST_SWP	0x00000100	/* [I] Atomic TAS op */
#घोषणा  RIO_SRC_OPS_ATOMIC_INC		0x00000080	/* [I] Atomic inc op */
#घोषणा  RIO_SRC_OPS_ATOMIC_DEC		0x00000040	/* [I] Atomic dec op */
#घोषणा  RIO_SRC_OPS_ATOMIC_SET		0x00000020	/* [I] Atomic set op */
#घोषणा  RIO_SRC_OPS_ATOMIC_CLR		0x00000010	/* [I] Atomic clr op */
#घोषणा  RIO_SRC_OPS_PORT_WRITE		0x00000004	/* [I] Port-ग_लिखो op */

#घोषणा RIO_DST_OPS_CAR		0x1c	/* Destination Operations CAR */
#घोषणा  RIO_DST_OPS_READ		0x00008000	/* [I] Read op */
#घोषणा  RIO_DST_OPS_WRITE		0x00004000	/* [I] Write op */
#घोषणा  RIO_DST_OPS_STREAM_WRITE	0x00002000	/* [I] Str-ग_लिखो op */
#घोषणा  RIO_DST_OPS_WRITE_RESPONSE	0x00001000	/* [I] Write/resp op */
#घोषणा  RIO_DST_OPS_DATA_MSG		0x00000800	/* [II] Data msg op */
#घोषणा  RIO_DST_OPS_DOORBELL		0x00000400	/* [II] Doorbell op */
#घोषणा  RIO_DST_OPS_ATOMIC_TST_SWP	0x00000100	/* [I] Atomic TAS op */
#घोषणा  RIO_DST_OPS_ATOMIC_INC		0x00000080	/* [I] Atomic inc op */
#घोषणा  RIO_DST_OPS_ATOMIC_DEC		0x00000040	/* [I] Atomic dec op */
#घोषणा  RIO_DST_OPS_ATOMIC_SET		0x00000020	/* [I] Atomic set op */
#घोषणा  RIO_DST_OPS_ATOMIC_CLR		0x00000010	/* [I] Atomic clr op */
#घोषणा  RIO_DST_OPS_PORT_WRITE		0x00000004	/* [I] Port-ग_लिखो op */

#घोषणा  RIO_OPS_READ			0x00008000	/* [I] Read op */
#घोषणा  RIO_OPS_WRITE			0x00004000	/* [I] Write op */
#घोषणा  RIO_OPS_STREAM_WRITE		0x00002000	/* [I] Str-ग_लिखो op */
#घोषणा  RIO_OPS_WRITE_RESPONSE		0x00001000	/* [I] Write/resp op */
#घोषणा  RIO_OPS_DATA_MSG		0x00000800	/* [II] Data msg op */
#घोषणा  RIO_OPS_DOORBELL		0x00000400	/* [II] Doorbell op */
#घोषणा  RIO_OPS_ATOMIC_TST_SWP		0x00000100	/* [I] Atomic TAS op */
#घोषणा  RIO_OPS_ATOMIC_INC		0x00000080	/* [I] Atomic inc op */
#घोषणा  RIO_OPS_ATOMIC_DEC		0x00000040	/* [I] Atomic dec op */
#घोषणा  RIO_OPS_ATOMIC_SET		0x00000020	/* [I] Atomic set op */
#घोषणा  RIO_OPS_ATOMIC_CLR		0x00000010	/* [I] Atomic clr op */
#घोषणा  RIO_OPS_PORT_WRITE		0x00000004	/* [I] Port-ग_लिखो op */

					/* 0x20-0x30 *//* Reserved */

#घोषणा	RIO_SWITCH_RT_LIMIT	0x34	/* [III, 1.3] Switch Route Table Destination ID Limit CAR */
#घोषणा	 RIO_RT_MAX_DESTID		0x0000ffff

#घोषणा RIO_MBOX_CSR		0x40	/* [II, <= 1.2] Mailbox CSR */
#घोषणा  RIO_MBOX0_AVAIL		0x80000000	/* [II] Mbox 0 avail */
#घोषणा  RIO_MBOX0_FULL			0x40000000	/* [II] Mbox 0 full */
#घोषणा  RIO_MBOX0_EMPTY		0x20000000	/* [II] Mbox 0 empty */
#घोषणा  RIO_MBOX0_BUSY			0x10000000	/* [II] Mbox 0 busy */
#घोषणा  RIO_MBOX0_FAIL			0x08000000	/* [II] Mbox 0 fail */
#घोषणा  RIO_MBOX0_ERROR		0x04000000	/* [II] Mbox 0 error */
#घोषणा  RIO_MBOX1_AVAIL		0x00800000	/* [II] Mbox 1 avail */
#घोषणा  RIO_MBOX1_FULL			0x00200000	/* [II] Mbox 1 full */
#घोषणा  RIO_MBOX1_EMPTY		0x00200000	/* [II] Mbox 1 empty */
#घोषणा  RIO_MBOX1_BUSY			0x00100000	/* [II] Mbox 1 busy */
#घोषणा  RIO_MBOX1_FAIL			0x00080000	/* [II] Mbox 1 fail */
#घोषणा  RIO_MBOX1_ERROR		0x00040000	/* [II] Mbox 1 error */
#घोषणा  RIO_MBOX2_AVAIL		0x00008000	/* [II] Mbox 2 avail */
#घोषणा  RIO_MBOX2_FULL			0x00004000	/* [II] Mbox 2 full */
#घोषणा  RIO_MBOX2_EMPTY		0x00002000	/* [II] Mbox 2 empty */
#घोषणा  RIO_MBOX2_BUSY			0x00001000	/* [II] Mbox 2 busy */
#घोषणा  RIO_MBOX2_FAIL			0x00000800	/* [II] Mbox 2 fail */
#घोषणा  RIO_MBOX2_ERROR		0x00000400	/* [II] Mbox 2 error */
#घोषणा  RIO_MBOX3_AVAIL		0x00000080	/* [II] Mbox 3 avail */
#घोषणा  RIO_MBOX3_FULL			0x00000040	/* [II] Mbox 3 full */
#घोषणा  RIO_MBOX3_EMPTY		0x00000020	/* [II] Mbox 3 empty */
#घोषणा  RIO_MBOX3_BUSY			0x00000010	/* [II] Mbox 3 busy */
#घोषणा  RIO_MBOX3_FAIL			0x00000008	/* [II] Mbox 3 fail */
#घोषणा  RIO_MBOX3_ERROR		0x00000004	/* [II] Mbox 3 error */

#घोषणा RIO_WRITE_PORT_CSR	0x44	/* [I, <= 1.2] Write Port CSR */
#घोषणा RIO_DOORBELL_CSR	0x44	/* [II, <= 1.2] Doorbell CSR */
#घोषणा  RIO_DOORBELL_AVAIL		0x80000000	/* [II] Doorbell avail */
#घोषणा  RIO_DOORBELL_FULL		0x40000000	/* [II] Doorbell full */
#घोषणा  RIO_DOORBELL_EMPTY		0x20000000	/* [II] Doorbell empty */
#घोषणा  RIO_DOORBELL_BUSY		0x10000000	/* [II] Doorbell busy */
#घोषणा  RIO_DOORBELL_FAILED		0x08000000	/* [II] Doorbell failed */
#घोषणा  RIO_DOORBELL_ERROR		0x04000000	/* [II] Doorbell error */
#घोषणा  RIO_WRITE_PORT_AVAILABLE	0x00000080	/* [I] Write Port Available */
#घोषणा  RIO_WRITE_PORT_FULL		0x00000040	/* [I] Write Port Full */
#घोषणा  RIO_WRITE_PORT_EMPTY		0x00000020	/* [I] Write Port Empty */
#घोषणा  RIO_WRITE_PORT_BUSY		0x00000010	/* [I] Write Port Busy */
#घोषणा  RIO_WRITE_PORT_FAILED		0x00000008	/* [I] Write Port Failed */
#घोषणा  RIO_WRITE_PORT_ERROR		0x00000004	/* [I] Write Port Error */

					/* 0x48 *//* Reserved */

#घोषणा RIO_PELL_CTRL_CSR	0x4c	/* [I] PE Logical Layer Control CSR */
#घोषणा   RIO_PELL_ADDR_66		0x00000004	/* [I] 66-bit addr */
#घोषणा   RIO_PELL_ADDR_50		0x00000002	/* [I] 50-bit addr */
#घोषणा   RIO_PELL_ADDR_34		0x00000001	/* [I] 34-bit addr */

					/* 0x50-0x54 *//* Reserved */

#घोषणा RIO_LCSH_BA		0x58	/* [I] LCS High Base Address */
#घोषणा RIO_LCSL_BA		0x5c	/* [I] LCS Base Address */

#घोषणा RIO_DID_CSR		0x60	/* [III] Base Device ID CSR */

					/* 0x64 *//* Reserved */

#घोषणा RIO_HOST_DID_LOCK_CSR	0x68	/* [III] Host Base Device ID Lock CSR */
#घोषणा RIO_COMPONENT_TAG_CSR	0x6c	/* [III] Component Tag CSR */

#घोषणा RIO_STD_RTE_CONF_DESTID_SEL_CSR	0x70
#घोषणा  RIO_STD_RTE_CONF_EXTCFGEN		0x80000000
#घोषणा RIO_STD_RTE_CONF_PORT_SEL_CSR	0x74
#घोषणा RIO_STD_RTE_DEFAULT_PORT	0x78

					/* 0x7c-0xf8 *//* Reserved */
					/* 0x100-0xfff8 *//* [I] Extended Features Space */
					/* 0x10000-0xfffff8 *//* [I] Implementation-defined Space */

/*
 * Extended Features Space is a configuration space area where
 * functionality is mapped पूर्णांकo extended feature blocks via a
 * singly linked list of extended feature poपूर्णांकers (EFT_PTR).
 *
 * Each extended feature block can be identअगरied/located in
 * Extended Features Space by walking the extended feature
 * list starting with the Extended Feature Poपूर्णांकer located
 * in the Assembly Inक्रमmation CAR.
 *
 * Extended Feature Blocks (EFBs) are identअगरied with an asचिन्हित
 * EFB ID. Extended feature block offsets in the definitions are
 * relative to the offset of the EFB within the  Extended Features
 * Space.
 */

/* Helper macros to parse the Extended Feature Block header */
#घोषणा RIO_EFB_PTR_MASK	0xffff0000
#घोषणा RIO_EFB_ID_MASK		0x0000ffff
#घोषणा RIO_GET_BLOCK_PTR(x)	((x & RIO_EFB_PTR_MASK) >> 16)
#घोषणा RIO_GET_BLOCK_ID(x)	(x & RIO_EFB_ID_MASK)

/* Extended Feature Block IDs */
#घोषणा RIO_EFB_SER_EP_M1_ID	0x0001	/* [VI] LP-Serial EP Devices, Map I */
#घोषणा RIO_EFB_SER_EP_SW_M1_ID	0x0002	/* [VI] LP-Serial EP w SW Recovery Devices, Map I */
#घोषणा RIO_EFB_SER_EPF_M1_ID	0x0003	/* [VI] LP-Serial EP Free Devices, Map I */
#घोषणा RIO_EFB_SER_EP_ID	0x0004	/* [VI] LP-Serial EP Devices, RIO 1.2 */
#घोषणा RIO_EFB_SER_EP_REC_ID	0x0005	/* [VI] LP-Serial EP w SW Recovery Devices, RIO 1.2 */
#घोषणा RIO_EFB_SER_EP_FREE_ID	0x0006	/* [VI] LP-Serial EP Free Devices, RIO 1.2 */
#घोषणा RIO_EFB_ERR_MGMNT	0x0007  /* [VIII] Error Management Extensions */
#घोषणा RIO_EFB_SER_EPF_SW_M1_ID	0x0009  /* [VI] LP-Serial EP Free w SW Recovery Devices, Map I */
#घोषणा RIO_EFB_SW_ROUTING_TBL	0x000E  /* [III] Switch Routing Table Block */
#घोषणा RIO_EFB_SER_EP_M2_ID	0x0011	/* [VI] LP-Serial EP Devices, Map II */
#घोषणा RIO_EFB_SER_EP_SW_M2_ID	0x0012	/* [VI] LP-Serial EP w SW Recovery Devices, Map II */
#घोषणा RIO_EFB_SER_EPF_M2_ID	0x0013	/* [VI] LP-Serial EP Free Devices, Map II */
#घोषणा RIO_EFB_ERR_MGMNT_HS	0x0017  /* [VIII] Error Management Extensions, Hot-Swap only */
#घोषणा RIO_EFB_SER_EPF_SW_M2_ID	0x0019  /* [VI] LP-Serial EP Free w SW Recovery Devices, Map II */

/*
 * Physical LP-Serial Registers Definitions
 * Parameters in रेजिस्टर macros:
 *    n - port number, m - Register Map Type (1 or 2)
 */
#घोषणा RIO_PORT_MNT_HEADER		0x0000
#घोषणा RIO_PORT_REQ_CTL_CSR		0x0020
#घोषणा RIO_PORT_RSP_CTL_CSR		0x0024
#घोषणा RIO_PORT_LINKTO_CTL_CSR		0x0020
#घोषणा RIO_PORT_RSPTO_CTL_CSR		0x0024
#घोषणा RIO_PORT_GEN_CTL_CSR		0x003c
#घोषणा  RIO_PORT_GEN_HOST		0x80000000
#घोषणा  RIO_PORT_GEN_MASTER		0x40000000
#घोषणा  RIO_PORT_GEN_DISCOVERED	0x20000000
#घोषणा RIO_PORT_N_MNT_REQ_CSR(n, m)	(0x40 + (n) * (0x20 * (m)))
#घोषणा  RIO_MNT_REQ_CMD_RD		0x03	/* Reset-device command */
#घोषणा  RIO_MNT_REQ_CMD_IS		0x04	/* Input-status command */
#घोषणा RIO_PORT_N_MNT_RSP_CSR(n, m)	(0x44 + (n) * (0x20 * (m)))
#घोषणा  RIO_PORT_N_MNT_RSP_RVAL	0x80000000 /* Response Valid */
#घोषणा  RIO_PORT_N_MNT_RSP_ASTAT	0x000007e0 /* ackID Status */
#घोषणा  RIO_PORT_N_MNT_RSP_LSTAT	0x0000001f /* Link Status */
#घोषणा RIO_PORT_N_ACK_STS_CSR(n)	(0x48 + (n) * 0x20) /* Only in RM-I */
#घोषणा  RIO_PORT_N_ACK_CLEAR		0x80000000
#घोषणा  RIO_PORT_N_ACK_INBOUND		0x3f000000
#घोषणा  RIO_PORT_N_ACK_OUTSTAND	0x00003f00
#घोषणा  RIO_PORT_N_ACK_OUTBOUND	0x0000003f
#घोषणा RIO_PORT_N_CTL2_CSR(n, m)	(0x54 + (n) * (0x20 * (m)))
#घोषणा  RIO_PORT_N_CTL2_SEL_BAUD	0xf0000000
#घोषणा RIO_PORT_N_ERR_STS_CSR(n, m)	(0x58 + (n) * (0x20 * (m)))
#घोषणा  RIO_PORT_N_ERR_STS_OUT_ES	0x00010000 /* Output Error-stopped */
#घोषणा  RIO_PORT_N_ERR_STS_INP_ES	0x00000100 /* Input Error-stopped */
#घोषणा  RIO_PORT_N_ERR_STS_PW_PEND	0x00000010 /* Port-Write Pending */
#घोषणा  RIO_PORT_N_ERR_STS_PORT_UA	0x00000008 /* Port Unavailable */
#घोषणा  RIO_PORT_N_ERR_STS_PORT_ERR	0x00000004
#घोषणा  RIO_PORT_N_ERR_STS_PORT_OK	0x00000002
#घोषणा  RIO_PORT_N_ERR_STS_PORT_UNINIT	0x00000001
#घोषणा RIO_PORT_N_CTL_CSR(n, m)	(0x5c + (n) * (0x20 * (m)))
#घोषणा  RIO_PORT_N_CTL_PWIDTH		0xc0000000
#घोषणा  RIO_PORT_N_CTL_PWIDTH_1	0x00000000
#घोषणा  RIO_PORT_N_CTL_PWIDTH_4	0x40000000
#घोषणा  RIO_PORT_N_CTL_IPW		0x38000000 /* Initialized Port Width */
#घोषणा  RIO_PORT_N_CTL_P_TYP_SER	0x00000001
#घोषणा  RIO_PORT_N_CTL_LOCKOUT		0x00000002
#घोषणा  RIO_PORT_N_CTL_EN_RX		0x00200000
#घोषणा  RIO_PORT_N_CTL_EN_TX		0x00400000
#घोषणा RIO_PORT_N_OB_ACK_CSR(n)	(0x60 + (n) * 0x40) /* Only in RM-II */
#घोषणा  RIO_PORT_N_OB_ACK_CLEAR	0x80000000
#घोषणा  RIO_PORT_N_OB_ACK_OUTSTD	0x00fff000
#घोषणा  RIO_PORT_N_OB_ACK_OUTBND	0x00000fff
#घोषणा RIO_PORT_N_IB_ACK_CSR(n)	(0x64 + (n) * 0x40) /* Only in RM-II */
#घोषणा  RIO_PORT_N_IB_ACK_INBND	0x00000fff

/*
 * Device-based helper macros क्रम serial port रेजिस्टर access.
 *   d - poपूर्णांकer to rapidio device object, n - port number
 */

#घोषणा RIO_DEV_PORT_N_MNT_REQ_CSR(d, n)	\
		(d->phys_efptr + RIO_PORT_N_MNT_REQ_CSR(n, d->phys_rmap))

#घोषणा RIO_DEV_PORT_N_MNT_RSP_CSR(d, n)	\
		(d->phys_efptr + RIO_PORT_N_MNT_RSP_CSR(n, d->phys_rmap))

#घोषणा RIO_DEV_PORT_N_ACK_STS_CSR(d, n)	\
		(d->phys_efptr + RIO_PORT_N_ACK_STS_CSR(n))

#घोषणा RIO_DEV_PORT_N_CTL2_CSR(d, n)		\
		(d->phys_efptr + RIO_PORT_N_CTL2_CSR(n, d->phys_rmap))

#घोषणा RIO_DEV_PORT_N_ERR_STS_CSR(d, n)	\
		(d->phys_efptr + RIO_PORT_N_ERR_STS_CSR(n, d->phys_rmap))

#घोषणा RIO_DEV_PORT_N_CTL_CSR(d, n)		\
		(d->phys_efptr + RIO_PORT_N_CTL_CSR(n, d->phys_rmap))

#घोषणा RIO_DEV_PORT_N_OB_ACK_CSR(d, n)		\
		(d->phys_efptr + RIO_PORT_N_OB_ACK_CSR(n))

#घोषणा RIO_DEV_PORT_N_IB_ACK_CSR(d, n)		\
		(d->phys_efptr + RIO_PORT_N_IB_ACK_CSR(n))

/*
 * Error Management Extensions (RapidIO 1.3+, Part 8)
 *
 * Extended Features Block ID=0x0007
 */

/* General EM Registers (Common क्रम all Ports) */

#घोषणा RIO_EM_EFB_HEADER	0x000	/* Error Management Extensions Block Header */
#घोषणा RIO_EM_EMHS_CAR		0x004	/* EM Functionality CAR */
#घोषणा RIO_EM_LTL_ERR_DETECT	0x008	/* Logical/Transport Layer Error Detect CSR */
#घोषणा RIO_EM_LTL_ERR_EN	0x00c	/* Logical/Transport Layer Error Enable CSR */
#घोषणा  REM_LTL_ERR_ILLTRAN		0x08000000 /* Illegal Transaction decode */
#घोषणा  REM_LTL_ERR_UNSOLR		0x00800000 /* Unsolicited Response */
#घोषणा  REM_LTL_ERR_UNSUPTR		0x00400000 /* Unsupported Transaction */
#घोषणा  REM_LTL_ERR_IMPSPEC		0x000000ff /* Implementation Specअगरic */
#घोषणा RIO_EM_LTL_HIADDR_CAP	0x010	/* Logical/Transport Layer High Address Capture CSR */
#घोषणा RIO_EM_LTL_ADDR_CAP	0x014	/* Logical/Transport Layer Address Capture CSR */
#घोषणा RIO_EM_LTL_DEVID_CAP	0x018	/* Logical/Transport Layer Device ID Capture CSR */
#घोषणा RIO_EM_LTL_CTRL_CAP	0x01c	/* Logical/Transport Layer Control Capture CSR */
#घोषणा RIO_EM_LTL_DID32_CAP	0x020	/* Logical/Transport Layer Dev32 DestID Capture CSR */
#घोषणा RIO_EM_LTL_SID32_CAP	0x024	/* Logical/Transport Layer Dev32  source ID Capture CSR */
#घोषणा RIO_EM_PW_TGT_DEVID	0x028	/* Port-ग_लिखो Target deviceID CSR */
#घोषणा  RIO_EM_PW_TGT_DEVID_D16M	0xff000000	/* Port-ग_लिखो Target DID16 MSB */
#घोषणा  RIO_EM_PW_TGT_DEVID_D8		0x00ff0000	/* Port-ग_लिखो Target DID16 LSB or DID8 */
#घोषणा  RIO_EM_PW_TGT_DEVID_DEV16	0x00008000	/* Port-ग_लिखो Target DID16 LSB or DID8 */
#घोषणा  RIO_EM_PW_TGT_DEVID_DEV32	0x00004000	/* Port-ग_लिखो Target DID16 LSB or DID8 */
#घोषणा RIO_EM_PKT_TTL		0x02c	/* Packet Time-to-live CSR */
#घोषणा RIO_EM_PKT_TTL_VAL		0xffff0000	/* Packet Time-to-live value */
#घोषणा RIO_EM_PW_TGT32_DEVID	0x030	/* Port-ग_लिखो Dev32 Target deviceID CSR */
#घोषणा RIO_EM_PW_TX_CTRL	0x034	/* Port-ग_लिखो Transmission Control CSR */
#घोषणा RIO_EM_PW_TX_CTRL_PW_DIS	0x00000001	/* Port-ग_लिखो Transmission Disable bit */

/* Per-Port EM Registers */

#घोषणा RIO_EM_PN_ERR_DETECT(x)	(0x040 + x*0x40) /* Port N Error Detect CSR */
#घोषणा  REM_PED_IMPL_SPEC		0x80000000
#घोषणा  REM_PED_LINK_OK2U		0x40000000 /* Link OK to Uninit transition */
#घोषणा  REM_PED_LINK_UPDA		0x20000000 /* Link Uninit Packet Discard Active */
#घोषणा  REM_PED_LINK_U2OK		0x10000000 /* Link Uninit to OK transition */
#घोषणा  REM_PED_LINK_TO		0x00000001

#घोषणा RIO_EM_PN_ERRRATE_EN(x) (0x044 + x*0x40) /* Port N Error Rate Enable CSR */
#घोषणा RIO_EM_PN_ERRRATE_EN_OK2U	0x40000000 /* Enable notअगरication क्रम OK2U */
#घोषणा RIO_EM_PN_ERRRATE_EN_UPDA	0x20000000 /* Enable notअगरication क्रम UPDA */
#घोषणा RIO_EM_PN_ERRRATE_EN_U2OK	0x10000000 /* Enable notअगरication क्रम U2OK */

#घोषणा RIO_EM_PN_ATTRIB_CAP(x)	(0x048 + x*0x40) /* Port N Attributes Capture CSR */
#घोषणा RIO_EM_PN_PKT_CAP_0(x)	(0x04c + x*0x40) /* Port N Packet/Control Symbol Capture 0 CSR */
#घोषणा RIO_EM_PN_PKT_CAP_1(x)	(0x050 + x*0x40) /* Port N Packet Capture 1 CSR */
#घोषणा RIO_EM_PN_PKT_CAP_2(x)	(0x054 + x*0x40) /* Port N Packet Capture 2 CSR */
#घोषणा RIO_EM_PN_PKT_CAP_3(x)	(0x058 + x*0x40) /* Port N Packet Capture 3 CSR */
#घोषणा RIO_EM_PN_ERRRATE(x)	(0x068 + x*0x40) /* Port N Error Rate CSR */
#घोषणा RIO_EM_PN_ERRRATE_TR(x) (0x06c + x*0x40) /* Port N Error Rate Threshold CSR */
#घोषणा RIO_EM_PN_LINK_UDT(x)	(0x070 + x*0x40) /* Port N Link Uninit Discard Timer CSR */
#घोषणा RIO_EM_PN_LINK_UDT_TO		0xffffff00 /* Link Uninit Timeout value */

/*
 * Switch Routing Table Register Block ID=0x000E (RapidIO 3.0+, part 3)
 * Register offsets are defined from beginning of the block.
 */

/* Broadcast Routing Table Control CSR */
#घोषणा RIO_BC_RT_CTL_CSR	0x020
#घोषणा  RIO_RT_CTL_THREE_LVL		0x80000000
#घोषणा  RIO_RT_CTL_DEV32_RT_CTRL	0x40000000
#घोषणा  RIO_RT_CTL_MC_MASK_SZ		0x03000000 /* 3.0+ Part 11: Multicast */

/* Broadcast Level 0 Info CSR */
#घोषणा RIO_BC_RT_LVL0_INFO_CSR	0x030
#घोषणा  RIO_RT_L0I_NUM_GR		0xff000000
#घोषणा  RIO_RT_L0I_GR_PTR		0x00fffc00

/* Broadcast Level 1 Info CSR */
#घोषणा RIO_BC_RT_LVL1_INFO_CSR	0x034
#घोषणा  RIO_RT_L1I_NUM_GR		0xff000000
#घोषणा  RIO_RT_L1I_GR_PTR		0x00fffc00

/* Broadcast Level 2 Info CSR */
#घोषणा RIO_BC_RT_LVL2_INFO_CSR	0x038
#घोषणा  RIO_RT_L2I_NUM_GR		0xff000000
#घोषणा  RIO_RT_L2I_GR_PTR		0x00fffc00

/* Per-Port Routing Table रेजिस्टरs.
 * Register fields defined in the broadcast section above are
 * applicable to the corresponding रेजिस्टरs below.
 */
#घोषणा RIO_SPx_RT_CTL_CSR(x)	(0x040 + (0x20 * x))
#घोषणा RIO_SPx_RT_LVL0_INFO_CSR(x)	(0x50 + (0x20 * x))
#घोषणा RIO_SPx_RT_LVL1_INFO_CSR(x)	(0x54 + (0x20 * x))
#घोषणा RIO_SPx_RT_LVL2_INFO_CSR(x)	(0x58 + (0x20 * x))

/* Register Formats क्रम Routing Table Group entry.
 * Register offsets are calculated using GR_PTR field in the corresponding
 * table Level_N and group/entry numbers (see RapidIO 3.0+ Part 3).
 */
#घोषणा RIO_RT_Ln_ENTRY_IMPL_DEF	0xf0000000
#घोषणा RIO_RT_Ln_ENTRY_RTE_VAL		0x000003ff
#घोषणा RIO_RT_ENTRY_DROP_PKT		0x300

#पूर्ण_अगर				/* LINUX_RIO_REGS_H */
