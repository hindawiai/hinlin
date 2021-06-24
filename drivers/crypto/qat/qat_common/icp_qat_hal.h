<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित __ICP_QAT_HAL_H
#घोषणा __ICP_QAT_HAL_H
#समावेश "icp_qat_fw_loader_handle.h"

क्रमागत hal_global_csr अणु
	MISC_CONTROL = 0xA04,
	ICP_RESET = 0xA0c,
	ICP_GLOBAL_CLK_ENABLE = 0xA50
पूर्ण;

क्रमागत अणु
	MISC_CONTROL_C4XXX = 0xAA0,
	ICP_RESET_CPP0 = 0x938,
	ICP_RESET_CPP1 = 0x93c,
	ICP_GLOBAL_CLK_ENABLE_CPP0 = 0x964,
	ICP_GLOBAL_CLK_ENABLE_CPP1 = 0x968
पूर्ण;

क्रमागत hal_ae_csr अणु
	USTORE_ADDRESS = 0x000,
	USTORE_DATA_LOWER = 0x004,
	USTORE_DATA_UPPER = 0x008,
	ALU_OUT = 0x010,
	CTX_ARB_CNTL = 0x014,
	CTX_ENABLES = 0x018,
	CC_ENABLE = 0x01c,
	CSR_CTX_POINTER = 0x020,
	CTX_STS_INसूचीECT = 0x040,
	ACTIVE_CTX_STATUS = 0x044,
	CTX_SIG_EVENTS_INसूचीECT = 0x048,
	CTX_SIG_EVENTS_ACTIVE = 0x04c,
	CTX_WAKEUP_EVENTS_INसूचीECT = 0x050,
	LM_ADDR_0_INसूचीECT = 0x060,
	LM_ADDR_1_INसूचीECT = 0x068,
	LM_ADDR_2_INसूचीECT = 0x0cc,
	LM_ADDR_3_INसूचीECT = 0x0d4,
	INसूचीECT_LM_ADDR_0_BYTE_INDEX = 0x0e0,
	INसूचीECT_LM_ADDR_1_BYTE_INDEX = 0x0e8,
	INसूचीECT_LM_ADDR_2_BYTE_INDEX = 0x10c,
	INसूचीECT_LM_ADDR_3_BYTE_INDEX = 0x114,
	INसूचीECT_T_INDEX = 0x0f8,
	INसूचीECT_T_INDEX_BYTE_INDEX = 0x0fc,
	FUTURE_COUNT_SIGNAL_INसूचीECT = 0x078,
	TIMESTAMP_LOW = 0x0c0,
	TIMESTAMP_HIGH = 0x0c4,
	PROखाता_COUNT = 0x144,
	SIGNATURE_ENABLE = 0x150,
	AE_MISC_CONTROL = 0x160,
	LOCAL_CSR_STATUS = 0x180,
पूर्ण;

क्रमागत fcu_csr अणु
	FCU_CONTROL           = 0x8c0,
	FCU_STATUS            = 0x8c4,
	FCU_STATUS1           = 0x8c8,
	FCU_DRAM_ADDR_LO      = 0x8cc,
	FCU_DRAM_ADDR_HI      = 0x8d0,
	FCU_RAMBASE_ADDR_HI   = 0x8d4,
	FCU_RAMBASE_ADDR_LO   = 0x8d8
पूर्ण;

क्रमागत fcu_csr_4xxx अणु
	FCU_CONTROL_4XXX           = 0x1000,
	FCU_STATUS_4XXX            = 0x1004,
	FCU_ME_BROADCAST_MASK_TYPE = 0x1008,
	FCU_AE_LOADED_4XXX         = 0x1010,
	FCU_DRAM_ADDR_LO_4XXX      = 0x1014,
	FCU_DRAM_ADDR_HI_4XXX      = 0x1018,
पूर्ण;

क्रमागत fcu_cmd अणु
	FCU_CTRL_CMD_NOOP  = 0,
	FCU_CTRL_CMD_AUTH  = 1,
	FCU_CTRL_CMD_LOAD  = 2,
	FCU_CTRL_CMD_START = 3
पूर्ण;

क्रमागत fcu_sts अणु
	FCU_STS_NO_STS    = 0,
	FCU_STS_VERI_DONE = 1,
	FCU_STS_LOAD_DONE = 2,
	FCU_STS_VERI_FAIL = 3,
	FCU_STS_LOAD_FAIL = 4,
	FCU_STS_BUSY      = 5
पूर्ण;

#घोषणा ALL_AE_MASK                 0xFFFFFFFF
#घोषणा UA_ECS                      (0x1 << 31)
#घोषणा ACS_ABO_BITPOS              31
#घोषणा ACS_ACNO                    0x7
#घोषणा CE_ENABLE_BITPOS            0x8
#घोषणा CE_LMADDR_0_GLOBAL_BITPOS   16
#घोषणा CE_LMADDR_1_GLOBAL_BITPOS   17
#घोषणा CE_LMADDR_2_GLOBAL_BITPOS   22
#घोषणा CE_LMADDR_3_GLOBAL_BITPOS   23
#घोषणा CE_T_INDEX_GLOBAL_BITPOS    21
#घोषणा CE_NN_MODE_BITPOS           20
#घोषणा CE_REG_PAR_ERR_BITPOS       25
#घोषणा CE_BREAKPOINT_BITPOS        27
#घोषणा CE_CNTL_STORE_PARITY_ERROR_BITPOS 29
#घोषणा CE_INUSE_CONTEXTS_BITPOS    31
#घोषणा CE_NN_MODE                  (0x1 << CE_NN_MODE_BITPOS)
#घोषणा CE_INUSE_CONTEXTS           (0x1 << CE_INUSE_CONTEXTS_BITPOS)
#घोषणा XCWE_VOLUNTARY              (0x1)
#घोषणा LCS_STATUS          (0x1)
#घोषणा MMC_SHARE_CS_BITPOS         2
#घोषणा WAKEUP_EVENT 0x10000
#घोषणा FCU_CTRL_BROADCAST_POS   0x4
#घोषणा FCU_CTRL_AE_POS     0x8
#घोषणा FCU_AUTH_STS_MASK   0x7
#घोषणा FCU_STS_DONE_POS    0x9
#घोषणा FCU_STS_AUTHFWLD_POS 0X8
#घोषणा FCU_LOADED_AE_POS   0x16
#घोषणा FW_AUTH_WAIT_PERIOD 10
#घोषणा FW_AUTH_MAX_RETRY   300
#घोषणा ICP_QAT_AE_OFFSET 0x20000
#घोषणा ICP_QAT_CAP_OFFSET (ICP_QAT_AE_OFFSET + 0x10000)
#घोषणा LOCAL_TO_XFER_REG_OFFSET 0x800
#घोषणा ICP_QAT_EP_OFFSET 0x3a000
#घोषणा ICP_QAT_EP_OFFSET_4XXX   0x200000 /* HI MMIO CSRs */
#घोषणा ICP_QAT_AE_OFFSET_4XXX   0x600000
#घोषणा ICP_QAT_CAP_OFFSET_4XXX  0x640000
#घोषणा SET_CAP_CSR(handle, csr, val) \
	ADF_CSR_WR((handle)->hal_cap_g_ctl_csr_addr_v, csr, val)
#घोषणा GET_CAP_CSR(handle, csr) \
	ADF_CSR_RD((handle)->hal_cap_g_ctl_csr_addr_v, csr)
#घोषणा AE_CSR(handle, ae) \
	((अक्षर __iomem *)(handle)->hal_cap_ae_local_csr_addr_v + ((ae) << 12))
#घोषणा AE_CSR_ADDR(handle, ae, csr) (AE_CSR(handle, ae) + (0x3ff & (csr)))
#घोषणा SET_AE_CSR(handle, ae, csr, val) \
	ADF_CSR_WR(AE_CSR_ADDR(handle, ae, csr), 0, val)
#घोषणा GET_AE_CSR(handle, ae, csr) ADF_CSR_RD(AE_CSR_ADDR(handle, ae, csr), 0)
#घोषणा AE_XFER(handle, ae) \
	((अक्षर __iomem *)(handle)->hal_cap_ae_xfer_csr_addr_v + ((ae) << 12))
#घोषणा AE_XFER_ADDR(handle, ae, reg) (AE_XFER(handle, ae) + \
	(((reg) & 0xff) << 2))
#घोषणा SET_AE_XFER(handle, ae, reg, val) \
	ADF_CSR_WR(AE_XFER_ADDR(handle, ae, reg), 0, val)
#घोषणा SRAM_WRITE(handle, addr, val) \
	ADF_CSR_WR((handle)->hal_sram_addr_v, addr, val)
#पूर्ण_अगर
