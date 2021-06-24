<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ISH रेजिस्टरs definitions
 *
 * Copyright (c) 2012-2016, Intel Corporation.
 */

#अगर_अघोषित _ISHTP_ISH_REGS_H_
#घोषणा _ISHTP_ISH_REGS_H_


/*** IPC PCI Offsets and sizes ***/
/* ISH IPC Base Address */
#घोषणा IPC_REG_BASE		0x0000
/* Peripheral Interrupt Status Register */
#घोषणा IPC_REG_PISR_CHV_AB      (IPC_REG_BASE + 0x00)
/* Peripheral Interrupt Mask Register */
#घोषणा IPC_REG_PIMR_CHV_AB      (IPC_REG_BASE + 0x04)
/*BXT, CHV_K0*/
/*Peripheral Interrupt Status Register */
#घोषणा IPC_REG_PISR_BXT	 (IPC_REG_BASE + 0x0C)
/*Peripheral Interrupt Mask Register */
#घोषणा IPC_REG_PIMR_BXT	 (IPC_REG_BASE + 0x08)
/***********************************/
/* ISH Host Firmware status Register */
#घोषणा IPC_REG_ISH_HOST_FWSTS	(IPC_REG_BASE + 0x34)
/* Host Communication Register */
#घोषणा IPC_REG_HOST_COMM	(IPC_REG_BASE + 0x38)
/* Reset रेजिस्टर */
#घोषणा IPC_REG_ISH_RST		(IPC_REG_BASE + 0x44)

/* Inbound करोorbell रेजिस्टर Host to ISH */
#घोषणा IPC_REG_HOST2ISH_DRBL	(IPC_REG_BASE + 0x48)
/* Outbound करोorbell रेजिस्टर ISH to Host */
#घोषणा IPC_REG_ISH2HOST_DRBL	(IPC_REG_BASE + 0x54)
/* ISH to HOST message रेजिस्टरs */
#घोषणा IPC_REG_ISH2HOST_MSG	(IPC_REG_BASE + 0x60)
/* HOST to ISH message रेजिस्टरs */
#घोषणा IPC_REG_HOST2ISH_MSG	(IPC_REG_BASE + 0xE0)
/* REMAP2 to enable DMA (D3 RCR) */
#घोषणा	IPC_REG_ISH_RMP2	(IPC_REG_BASE + 0x368)

#घोषणा	IPC_REG_MAX		(IPC_REG_BASE + 0x400)

/*** रेजिस्टर bits - HISR ***/
/* bit corresponds HOST2ISH पूर्णांकerrupt in PISR and PIMR रेजिस्टरs */
#घोषणा IPC_INT_HOST2ISH_BIT            (1<<0)
/***********************************/
/*CHV_A0, CHV_B0*/
/* bit corresponds ISH2HOST पूर्णांकerrupt in PISR and PIMR रेजिस्टरs */
#घोषणा IPC_INT_ISH2HOST_BIT_CHV_AB	(1<<3)
/*BXT, CHV_K0*/
/* bit corresponds ISH2HOST पूर्णांकerrupt in PISR and PIMR रेजिस्टरs */
#घोषणा IPC_INT_ISH2HOST_BIT_BXT	(1<<0)
/***********************************/

/* bit corresponds ISH2HOST busy clear पूर्णांकerrupt in PIMR रेजिस्टर */
#घोषणा IPC_INT_ISH2HOST_CLR_MASK_BIT	(1<<11)

/* offset of ISH2HOST busy clear पूर्णांकerrupt in IPC_BUSY_CLR रेजिस्टर */
#घोषणा IPC_INT_ISH2HOST_CLR_OFFS	(0)

/* bit corresponds ISH2HOST busy clear पूर्णांकerrupt in IPC_BUSY_CLR रेजिस्टर */
#घोषणा IPC_INT_ISH2HOST_CLR_BIT	(1<<IPC_INT_ISH2HOST_CLR_OFFS)

/* bit corresponds busy bit in करोorbell रेजिस्टरs */
#घोषणा IPC_DRBL_BUSY_OFFS		(31)
#घोषणा IPC_DRBL_BUSY_BIT		(1<<IPC_DRBL_BUSY_OFFS)

#घोषणा	IPC_HOST_OWNS_MSG_OFFS		(30)

/*
 * A0: bit means that host owns MSGnn रेजिस्टरs and is पढ़ोing them.
 * ISH FW may not ग_लिखो to them
 */
#घोषणा	IPC_HOST_OWNS_MSG_BIT		(1<<IPC_HOST_OWNS_MSG_OFFS)

/*
 * Host status bits (HOSTCOMM)
 */
/* bit corresponds host पढ़ोy bit in Host Status Register (HOST_COMM) */
#घोषणा IPC_HOSTCOMM_READY_OFFS		(7)
#घोषणा IPC_HOSTCOMM_READY_BIT		(1<<IPC_HOSTCOMM_READY_OFFS)

/***********************************/
/*CHV_A0, CHV_B0*/
#घोषणा	IPC_HOSTCOMM_INT_EN_OFFS_CHV_AB	(31)
#घोषणा	IPC_HOSTCOMM_INT_EN_BIT_CHV_AB		\
	(1<<IPC_HOSTCOMM_INT_EN_OFFS_CHV_AB)
/*BXT, CHV_K0*/
#घोषणा IPC_PIMR_INT_EN_OFFS_BXT	(0)
#घोषणा IPC_PIMR_INT_EN_BIT_BXT		(1<<IPC_PIMR_INT_EN_OFFS_BXT)

#घोषणा IPC_HOST2ISH_BUSYCLEAR_MASK_OFFS_BXT	(8)
#घोषणा IPC_HOST2ISH_BUSYCLEAR_MASK_BIT		\
	(1<<IPC_HOST2ISH_BUSYCLEAR_MASK_OFFS_BXT)
/***********************************/
/*
 * both Host and ISH have ILUP at bit 0
 * bit corresponds host पढ़ोy bit in both status रेजिस्टरs
 */
#घोषणा IPC_ILUP_OFFS			(0)
#घोषणा IPC_ILUP_BIT			(1<<IPC_ILUP_OFFS)

/*
 * ISH FW status bits in ISH FW Status Register
 */
#घोषणा IPC_ISH_FWSTS_SHIFT		12
#घोषणा IPC_ISH_FWSTS_MASK		GENMASK(15, 12)
#घोषणा IPC_GET_ISH_FWSTS(status)	\
	(((status) & IPC_ISH_FWSTS_MASK) >> IPC_ISH_FWSTS_SHIFT)

/*
 * FW status bits (relevant)
 */
#घोषणा	IPC_FWSTS_ILUP		0x1
#घोषणा	IPC_FWSTS_ISHTP_UP	(1<<1)
#घोषणा	IPC_FWSTS_DMA0		(1<<16)
#घोषणा	IPC_FWSTS_DMA1		(1<<17)
#घोषणा	IPC_FWSTS_DMA2		(1<<18)
#घोषणा	IPC_FWSTS_DMA3		(1<<19)

#घोषणा	IPC_ISH_IN_DMA		\
	(IPC_FWSTS_DMA0 | IPC_FWSTS_DMA1 | IPC_FWSTS_DMA2 | IPC_FWSTS_DMA3)

/* bit corresponds host पढ़ोy bit in ISH FW Status Register */
#घोषणा IPC_ISH_ISHTP_READY_OFFS		(1)
#घोषणा IPC_ISH_ISHTP_READY_BIT		(1<<IPC_ISH_ISHTP_READY_OFFS)

#घोषणा	IPC_RMP2_DMA_ENABLED	0x1	/* Value to enable DMA, per D3 RCR */

#घोषणा IPC_MSG_MAX_SIZE	0x80


#घोषणा IPC_HEADER_LENGTH_MASK		0x03FF
#घोषणा IPC_HEADER_PROTOCOL_MASK	0x0F
#घोषणा IPC_HEADER_MNG_CMD_MASK		0x0F

#घोषणा IPC_HEADER_LENGTH_OFFSET	0
#घोषणा IPC_HEADER_PROTOCOL_OFFSET	10
#घोषणा IPC_HEADER_MNG_CMD_OFFSET	16

#घोषणा IPC_HEADER_GET_LENGTH(drbl_reg)		\
	(((drbl_reg) >> IPC_HEADER_LENGTH_OFFSET)&IPC_HEADER_LENGTH_MASK)
#घोषणा IPC_HEADER_GET_PROTOCOL(drbl_reg)	\
	(((drbl_reg) >> IPC_HEADER_PROTOCOL_OFFSET)&IPC_HEADER_PROTOCOL_MASK)
#घोषणा IPC_HEADER_GET_MNG_CMD(drbl_reg)	\
	(((drbl_reg) >> IPC_HEADER_MNG_CMD_OFFSET)&IPC_HEADER_MNG_CMD_MASK)

#घोषणा IPC_IS_BUSY(drbl_reg)			\
	(((drbl_reg)&IPC_DRBL_BUSY_BIT) == ((uपूर्णांक32_t)IPC_DRBL_BUSY_BIT))

/***********************************/
/*CHV_A0, CHV_B0*/
#घोषणा IPC_INT_FROM_ISH_TO_HOST_CHV_AB(drbl_reg) \
	(((drbl_reg)&IPC_INT_ISH2HOST_BIT_CHV_AB) == \
	((u32)IPC_INT_ISH2HOST_BIT_CHV_AB))
/*BXT, CHV_K0*/
#घोषणा IPC_INT_FROM_ISH_TO_HOST_BXT(drbl_reg) \
	(((drbl_reg)&IPC_INT_ISH2HOST_BIT_BXT) == \
	((u32)IPC_INT_ISH2HOST_BIT_BXT))
/***********************************/

#घोषणा IPC_BUILD_HEADER(length, protocol, busy)		\
	(((busy)<<IPC_DRBL_BUSY_OFFS) |				\
	((protocol) << IPC_HEADER_PROTOCOL_OFFSET) |		\
	((length)<<IPC_HEADER_LENGTH_OFFSET))

#घोषणा IPC_BUILD_MNG_MSG(cmd, length)				\
	(((1)<<IPC_DRBL_BUSY_OFFS)|				\
	((IPC_PROTOCOL_MNG)<<IPC_HEADER_PROTOCOL_OFFSET)|	\
	((cmd)<<IPC_HEADER_MNG_CMD_OFFSET)|			\
	 ((length)<<IPC_HEADER_LENGTH_OFFSET))


#घोषणा IPC_SET_HOST_READY(host_status)		\
				((host_status) |= (IPC_HOSTCOMM_READY_BIT))

#घोषणा IPC_SET_HOST_ILUP(host_status)		\
				((host_status) |= (IPC_ILUP_BIT))

#घोषणा IPC_CLEAR_HOST_READY(host_status)	\
				((host_status) ^= (IPC_HOSTCOMM_READY_BIT))

#घोषणा IPC_CLEAR_HOST_ILUP(host_status)	\
				((host_status) ^= (IPC_ILUP_BIT))

/* toकरो - temp until PIMR HW पढ़ोy */
#घोषणा IPC_HOST_BUSY_READING_OFFS	6

/* bit corresponds host पढ़ोy bit in Host Status Register (HOST_COMM) */
#घोषणा IPC_HOST_BUSY_READING_BIT	(1<<IPC_HOST_BUSY_READING_OFFS)

#घोषणा IPC_SET_HOST_BUSY_READING(host_status)	\
				((host_status) |= (IPC_HOST_BUSY_READING_BIT))

#घोषणा IPC_CLEAR_HOST_BUSY_READING(host_status)\
				((host_status) ^= (IPC_HOST_BUSY_READING_BIT))


#घोषणा IPC_IS_ISH_ISHTP_READY(ish_status)	\
		(((ish_status) & IPC_ISH_ISHTP_READY_BIT) ==	\
			((uपूर्णांक32_t)IPC_ISH_ISHTP_READY_BIT))

#घोषणा IPC_IS_ISH_ILUP(ish_status)		\
		(((ish_status) & IPC_ILUP_BIT) == ((uपूर्णांक32_t)IPC_ILUP_BIT))


#घोषणा IPC_PROTOCOL_ISHTP		1
#घोषणा IPC_PROTOCOL_MNG		3

#घोषणा MNG_RX_CMPL_ENABLE		0
#घोषणा MNG_RX_CMPL_DISABLE		1
#घोषणा MNG_RX_CMPL_INDICATION		2
#घोषणा MNG_RESET_NOTIFY		3
#घोषणा MNG_RESET_NOTIFY_ACK		4
#घोषणा MNG_SYNC_FW_CLOCK		5
#घोषणा MNG_ILLEGAL_CMD			0xFF

#पूर्ण_अगर /* _ISHTP_ISH_REGS_H_ */
