<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (c) 2013-2014, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */
#अगर_अघोषित _MEI_HW_TXE_REGS_H_
#घोषणा _MEI_HW_TXE_REGS_H_

#समावेश "hw.h"

#घोषणा SEC_ALIVENESS_TIMER_TIMEOUT        (5 * MSEC_PER_SEC)
#घोषणा SEC_ALIVENESS_WAIT_TIMEOUT         (1 * MSEC_PER_SEC)
#घोषणा SEC_RESET_WAIT_TIMEOUT             (1 * MSEC_PER_SEC)
#घोषणा SEC_READY_WAIT_TIMEOUT             (5 * MSEC_PER_SEC)
#घोषणा START_MESSAGE_RESPONSE_WAIT_TIMEOUT (5 * MSEC_PER_SEC)
#घोषणा RESET_CANCEL_WAIT_TIMEOUT          (1 * MSEC_PER_SEC)

क्रमागत अणु
	SEC_BAR,
	BRIDGE_BAR,

	NUM_OF_MEM_BARS
पूर्ण;

/* SeC FW Status Register
 *
 * FW uses this रेजिस्टर in order to report its status to host.
 * This रेजिस्टर resides in PCI-E config space.
 */
#घोषणा PCI_CFG_TXE_FW_STS0   0x40
#  define PCI_CFG_TXE_FW_STS0_WRK_ST_MSK    0x0000000F
#  define PCI_CFG_TXE_FW_STS0_OP_ST_MSK     0x000001C0
#  define PCI_CFG_TXE_FW_STS0_FW_INIT_CMPLT 0x00000200
#  define PCI_CFG_TXE_FW_STS0_ERR_CODE_MSK  0x0000F000
#  define PCI_CFG_TXE_FW_STS0_OP_MODE_MSK   0x000F0000
#  define PCI_CFG_TXE_FW_STS0_RST_CNT_MSK   0x00F00000
#घोषणा PCI_CFG_TXE_FW_STS1   0x48

#घोषणा IPC_BASE_ADDR	0x80400 /* SeC IPC Base Address */

/* IPC Input Doorbell Register */
#घोषणा SEC_IPC_INPUT_DOORBELL_REG       (0x0000 + IPC_BASE_ADDR)

/* IPC Input Status Register
 * This रेजिस्टर indicates whether or not processing of
 * the most recent command has been completed by the SEC
 * New commands and payloads should not be written by the Host
 * until this indicates that the previous command has been processed.
 */
#घोषणा SEC_IPC_INPUT_STATUS_REG         (0x0008 + IPC_BASE_ADDR)
#  define SEC_IPC_INPUT_STATUS_RDY    BIT(0)

/* IPC Host Interrupt Status Register */
#घोषणा SEC_IPC_HOST_INT_STATUS_REG      (0x0010 + IPC_BASE_ADDR)
#घोषणा   SEC_IPC_HOST_INT_STATUS_OUT_DB             BIT(0)
#घोषणा   SEC_IPC_HOST_INT_STATUS_IN_RDY             BIT(1)
#घोषणा   SEC_IPC_HOST_INT_STATUS_HDCP_M0_RCVD       BIT(5)
#घोषणा   SEC_IPC_HOST_INT_STATUS_ILL_MEM_ACCESS     BIT(17)
#घोषणा   SEC_IPC_HOST_INT_STATUS_AES_HKEY_ERR       BIT(18)
#घोषणा   SEC_IPC_HOST_INT_STATUS_DES_HKEY_ERR       BIT(19)
#घोषणा   SEC_IPC_HOST_INT_STATUS_TMRMTB_OVERFLOW    BIT(21)

/* Convenient mask क्रम pending पूर्णांकerrupts */
#घोषणा   SEC_IPC_HOST_INT_STATUS_PENDING \
		(SEC_IPC_HOST_INT_STATUS_OUT_DB| \
		SEC_IPC_HOST_INT_STATUS_IN_RDY)

/* IPC Host Interrupt Mask Register */
#घोषणा SEC_IPC_HOST_INT_MASK_REG        (0x0014 + IPC_BASE_ADDR)

#  define SEC_IPC_HOST_INT_MASK_OUT_DB	BIT(0) /* Output Doorbell Int Mask */
#  define SEC_IPC_HOST_INT_MASK_IN_RDY	BIT(1) /* Input Ready Int Mask */

/* IPC Input Payload RAM */
#घोषणा SEC_IPC_INPUT_PAYLOAD_REG        (0x0100 + IPC_BASE_ADDR)
/* IPC Shared Payload RAM */
#घोषणा IPC_SHARED_PAYLOAD_REG           (0x0200 + IPC_BASE_ADDR)

/* SeC Address Translation Table Entry 2 - Ctrl
 *
 * This रेजिस्टर resides also in SeC's PCI-E Memory space.
 */
#घोषणा SATT2_CTRL_REG                   0x1040
#  define SATT2_CTRL_VALID_MSK            BIT(0)
#  define SATT2_CTRL_BR_BASE_ADDR_REG_SHIFT 8
#  define SATT2_CTRL_BRIDGE_HOST_EN_MSK   BIT(12)

/* SATT Table Entry 2 SAP Base Address Register */
#घोषणा SATT2_SAP_BA_REG                 0x1044
/* SATT Table Entry 2 SAP Size Register. */
#घोषणा SATT2_SAP_SIZE_REG               0x1048
 /* SATT Table Entry 2 SAP Bridge Address - LSB Register */
#घोषणा SATT2_BRG_BA_LSB_REG             0x104C

/* Host High-level Interrupt Status Register */
#घोषणा HHISR_REG                        0x2020
/* Host High-level Interrupt Enable Register
 *
 * Resides in PCI memory space. This is the top hierarchy क्रम
 * पूर्णांकerrupts from SeC to host, aggregating both पूर्णांकerrupts that
 * arrive through HICR रेजिस्टरs as well as पूर्णांकerrupts
 * that arrive via IPC.
 */
#घोषणा HHIER_REG                        0x2024
#घोषणा   IPC_HHIER_SEC	BIT(0)
#घोषणा   IPC_HHIER_BRIDGE	BIT(1)
#घोषणा   IPC_HHIER_MSK	(IPC_HHIER_SEC | IPC_HHIER_BRIDGE)

/* Host High-level Interrupt Mask Register.
 *
 * Resides in PCI memory space.
 * This is the top hierarchy क्रम masking पूर्णांकerrupts from SeC to host.
 */
#घोषणा HHIMR_REG                        0x2028
#घोषणा   IPC_HHIMR_SEC       BIT(0)
#घोषणा   IPC_HHIMR_BRIDGE    BIT(1)

/* Host High-level IRQ Status Register */
#घोषणा HHIRQSR_REG                      0x202C

/* Host Interrupt Cause Register 0 - SeC IPC Readiness
 *
 * This रेजिस्टर is both an ICR to Host from PCI Memory Space
 * and it is also exposed in the SeC memory space.
 * This रेजिस्टर is used by SeC's IPC driver in order
 * to synchronize with host about IPC पूर्णांकerface state.
 */
#घोषणा HICR_SEC_IPC_READINESS_REG       0x2040
#घोषणा   HICR_SEC_IPC_READINESS_HOST_RDY  BIT(0)
#घोषणा   HICR_SEC_IPC_READINESS_SEC_RDY   BIT(1)
#घोषणा   HICR_SEC_IPC_READINESS_SYS_RDY     \
	  (HICR_SEC_IPC_READINESS_HOST_RDY | \
	   HICR_SEC_IPC_READINESS_SEC_RDY)
#घोषणा   HICR_SEC_IPC_READINESS_RDY_CLR   BIT(2)

/* Host Interrupt Cause Register 1 - Aliveness Response */
/* This रेजिस्टर is both an ICR to Host from PCI Memory Space
 * and it is also exposed in the SeC memory space.
 * The रेजिस्टर may be used by SeC to ACK a host request क्रम aliveness.
 */
#घोषणा HICR_HOST_ALIVENESS_RESP_REG     0x2044
#घोषणा   HICR_HOST_ALIVENESS_RESP_ACK    BIT(0)

/* Host Interrupt Cause Register 2 - SeC IPC Output Doorbell */
#घोषणा HICR_SEC_IPC_OUTPUT_DOORBELL_REG 0x2048

/* Host Interrupt Status Register.
 *
 * Resides in PCI memory space.
 * This is the मुख्य रेजिस्टर involved in generating पूर्णांकerrupts
 * from SeC to host via HICRs.
 * The पूर्णांकerrupt generation rules are as follows:
 * An पूर्णांकerrupt will be generated whenever क्रम any i,
 * there is a transition from a state where at least one of
 * the following conditions did not hold, to a state where
 * ALL the following conditions hold:
 * A) HISR.INT[i]_STS == 1.
 * B) HIER.INT[i]_EN == 1.
 */
#घोषणा HISR_REG                         0x2060
#घोषणा   HISR_INT_0_STS      BIT(0)
#घोषणा   HISR_INT_1_STS      BIT(1)
#घोषणा   HISR_INT_2_STS      BIT(2)
#घोषणा   HISR_INT_3_STS      BIT(3)
#घोषणा   HISR_INT_4_STS      BIT(4)
#घोषणा   HISR_INT_5_STS      BIT(5)
#घोषणा   HISR_INT_6_STS      BIT(6)
#घोषणा   HISR_INT_7_STS      BIT(7)
#घोषणा   HISR_INT_STS_MSK \
	(HISR_INT_0_STS | HISR_INT_1_STS | HISR_INT_2_STS)

/* Host Interrupt Enable Register. Resides in PCI memory space. */
#घोषणा HIER_REG                         0x2064
#घोषणा   HIER_INT_0_EN      BIT(0)
#घोषणा   HIER_INT_1_EN      BIT(1)
#घोषणा   HIER_INT_2_EN      BIT(2)
#घोषणा   HIER_INT_3_EN      BIT(3)
#घोषणा   HIER_INT_4_EN      BIT(4)
#घोषणा   HIER_INT_5_EN      BIT(5)
#घोषणा   HIER_INT_6_EN      BIT(6)
#घोषणा   HIER_INT_7_EN      BIT(7)

#घोषणा   HIER_INT_EN_MSK \
	 (HIER_INT_0_EN | HIER_INT_1_EN | HIER_INT_2_EN)


/* SEC Memory Space IPC output payload.
 *
 * This रेजिस्टर is part of the output payload which SEC provides to host.
 */
#घोषणा BRIDGE_IPC_OUTPUT_PAYLOAD_REG    0x20C0

/* SeC Interrupt Cause Register - Host Aliveness Request
 * This रेजिस्टर is both an ICR to SeC and it is also exposed
 * in the host-visible PCI memory space.
 * The रेजिस्टर is used by host to request SeC aliveness.
 */
#घोषणा SICR_HOST_ALIVENESS_REQ_REG      0x214C
#घोषणा   SICR_HOST_ALIVENESS_REQ_REQUESTED    BIT(0)


/* SeC Interrupt Cause Register - Host IPC Readiness
 *
 * This रेजिस्टर is both an ICR to SeC and it is also exposed
 * in the host-visible PCI memory space.
 * This रेजिस्टर is used by the host's SeC driver uses in order
 * to synchronize with SeC about IPC पूर्णांकerface state.
 */
#घोषणा SICR_HOST_IPC_READINESS_REQ_REG  0x2150


#घोषणा SICR_HOST_IPC_READINESS_HOST_RDY  BIT(0)
#घोषणा SICR_HOST_IPC_READINESS_SEC_RDY   BIT(1)
#घोषणा SICR_HOST_IPC_READINESS_SYS_RDY     \
	(SICR_HOST_IPC_READINESS_HOST_RDY | \
	 SICR_HOST_IPC_READINESS_SEC_RDY)
#घोषणा SICR_HOST_IPC_READINESS_RDY_CLR   BIT(2)

/* SeC Interrupt Cause Register - SeC IPC Output Status
 *
 * This रेजिस्टर indicates whether or not processing of the most recent
 * command has been completed by the Host.
 * New commands and payloads should not be written by SeC until this
 * रेजिस्टर indicates that the previous command has been processed.
 */
#घोषणा SICR_SEC_IPC_OUTPUT_STATUS_REG   0x2154
#  define SEC_IPC_OUTPUT_STATUS_RDY BIT(0)



/*  MEI IPC Message payload size 64 bytes */
#घोषणा PAYLOAD_SIZE        64

/* MAX size क्रम SATT range 32MB */
#घोषणा SATT_RANGE_MAX     (32 << 20)


#पूर्ण_अगर /* _MEI_HW_TXE_REGS_H_ */

