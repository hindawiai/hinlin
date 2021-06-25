<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014-2019 Intel Corporation
 */

#अगर_अघोषित _INTEL_GUC_REG_H_
#घोषणा _INTEL_GUC_REG_H_

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

#समावेश "i915_reg.h"

/* Definitions of GuC H/W रेजिस्टरs, bits, etc */

#घोषणा GUC_STATUS			_MMIO(0xc000)
#घोषणा   GS_RESET_SHIFT		0
#घोषणा   GS_MIA_IN_RESET		  (0x01 << GS_RESET_SHIFT)
#घोषणा   GS_BOOTROM_SHIFT		1
#घोषणा   GS_BOOTROM_MASK		  (0x7F << GS_BOOTROM_SHIFT)
#घोषणा   GS_BOOTROM_RSA_FAILED		  (0x50 << GS_BOOTROM_SHIFT)
#घोषणा   GS_BOOTROM_JUMP_PASSED	  (0x76 << GS_BOOTROM_SHIFT)
#घोषणा   GS_UKERNEL_SHIFT		8
#घोषणा   GS_UKERNEL_MASK		  (0xFF << GS_UKERNEL_SHIFT)
#घोषणा   GS_UKERNEL_LAPIC_DONE		  (0x30 << GS_UKERNEL_SHIFT)
#घोषणा   GS_UKERNEL_DPC_ERROR		  (0x60 << GS_UKERNEL_SHIFT)
#घोषणा   GS_UKERNEL_EXCEPTION		  (0x70 << GS_UKERNEL_SHIFT)
#घोषणा   GS_UKERNEL_READY		  (0xF0 << GS_UKERNEL_SHIFT)
#घोषणा   GS_MIA_SHIFT			16
#घोषणा   GS_MIA_MASK			  (0x07 << GS_MIA_SHIFT)
#घोषणा   GS_MIA_CORE_STATE		  (0x01 << GS_MIA_SHIFT)
#घोषणा   GS_MIA_HALT_REQUESTED		  (0x02 << GS_MIA_SHIFT)
#घोषणा   GS_MIA_ISR_ENTRY		  (0x04 << GS_MIA_SHIFT)
#घोषणा   GS_AUTH_STATUS_SHIFT		30
#घोषणा   GS_AUTH_STATUS_MASK		  (0x03 << GS_AUTH_STATUS_SHIFT)
#घोषणा   GS_AUTH_STATUS_BAD		  (0x01 << GS_AUTH_STATUS_SHIFT)
#घोषणा   GS_AUTH_STATUS_GOOD		  (0x02 << GS_AUTH_STATUS_SHIFT)

#घोषणा SOFT_SCRATCH(n)			_MMIO(0xc180 + (n) * 4)
#घोषणा SOFT_SCRATCH_COUNT		16

#घोषणा GEN11_SOFT_SCRATCH(n)		_MMIO(0x190240 + (n) * 4)
#घोषणा GEN11_SOFT_SCRATCH_COUNT	4

#घोषणा UOS_RSA_SCRATCH(i)		_MMIO(0xc200 + (i) * 4)
#घोषणा UOS_RSA_SCRATCH_COUNT		64

#घोषणा DMA_ADDR_0_LOW			_MMIO(0xc300)
#घोषणा DMA_ADDR_0_HIGH			_MMIO(0xc304)
#घोषणा DMA_ADDR_1_LOW			_MMIO(0xc308)
#घोषणा DMA_ADDR_1_HIGH			_MMIO(0xc30c)
#घोषणा   DMA_ADDRESS_SPACE_WOPCM	  (7 << 16)
#घोषणा   DMA_ADDRESS_SPACE_GTT		  (8 << 16)
#घोषणा DMA_COPY_SIZE			_MMIO(0xc310)
#घोषणा DMA_CTRL			_MMIO(0xc314)
#घोषणा   HUC_UKERNEL			  (1<<9)
#घोषणा   UOS_MOVE			  (1<<4)
#घोषणा   START_DMA			  (1<<0)
#घोषणा DMA_GUC_WOPCM_OFFSET		_MMIO(0xc340)
#घोषणा   GUC_WOPCM_OFFSET_VALID	  (1<<0)
#घोषणा   HUC_LOADING_AGENT_VCR		  (0<<1)
#घोषणा   HUC_LOADING_AGENT_GUC		  (1<<1)
#घोषणा   GUC_WOPCM_OFFSET_SHIFT	14
#घोषणा   GUC_WOPCM_OFFSET_MASK		  (0x3ffff << GUC_WOPCM_OFFSET_SHIFT)
#घोषणा GUC_MAX_IDLE_COUNT		_MMIO(0xC3E4)

#घोषणा HUC_STATUS2             _MMIO(0xD3B0)
#घोषणा   HUC_FW_VERIFIED       (1<<7)

#घोषणा GEN11_HUC_KERNEL_LOAD_INFO	_MMIO(0xC1DC)
#घोषणा   HUC_LOAD_SUCCESSFUL		  (1 << 0)

#घोषणा GUC_WOPCM_SIZE			_MMIO(0xc050)
#घोषणा   GUC_WOPCM_SIZE_LOCKED		  (1<<0)
#घोषणा   GUC_WOPCM_SIZE_SHIFT		12
#घोषणा   GUC_WOPCM_SIZE_MASK		  (0xfffff << GUC_WOPCM_SIZE_SHIFT)

#घोषणा GEN8_GT_PM_CONFIG		_MMIO(0x138140)
#घोषणा GEN9LP_GT_PM_CONFIG		_MMIO(0x138140)
#घोषणा GEN9_GT_PM_CONFIG		_MMIO(0x13816c)
#घोषणा   GT_DOORBELL_ENABLE		  (1<<0)

#घोषणा GEN8_GTCR			_MMIO(0x4274)
#घोषणा   GEN8_GTCR_INVALIDATE		  (1<<0)

#घोषणा GEN12_GUC_TLB_INV_CR		_MMIO(0xcee8)
#घोषणा   GEN12_GUC_TLB_INV_CR_INVALIDATE	(1 << 0)

#घोषणा GUC_ARAT_C6DIS			_MMIO(0xA178)

#घोषणा GUC_SHIM_CONTROL		_MMIO(0xc064)
#घोषणा   GUC_DISABLE_SRAM_INIT_TO_ZEROES	(1<<0)
#घोषणा   GUC_ENABLE_READ_CACHE_LOGIC		(1<<1)
#घोषणा   GUC_ENABLE_MIA_CACHING		(1<<2)
#घोषणा   GUC_GEN10_MSGCH_ENABLE		(1<<4)
#घोषणा   GUC_ENABLE_READ_CACHE_FOR_SRAM_DATA	(1<<9)
#घोषणा   GUC_ENABLE_READ_CACHE_FOR_WOPCM_DATA	(1<<10)
#घोषणा   GUC_ENABLE_MIA_CLOCK_GATING		(1<<15)
#घोषणा   GUC_GEN10_SHIM_WC_ENABLE		(1<<21)

#घोषणा GUC_SEND_INTERRUPT		_MMIO(0xc4c8)
#घोषणा   GUC_SEND_TRIGGER		  (1<<0)
#घोषणा GEN11_GUC_HOST_INTERRUPT	_MMIO(0x1901f0)

#घोषणा GUC_NUM_DOORBELLS		256

/* क्रमmat of the HW-monitored करोorbell cacheline */
काष्ठा guc_करोorbell_info अणु
	u32 db_status;
#घोषणा GUC_DOORBELL_DISABLED		0
#घोषणा GUC_DOORBELL_ENABLED		1

	u32 cookie;
	u32 reserved[14];
पूर्ण __packed;

#घोषणा GEN8_DRBREGL(x)			_MMIO(0x1000 + (x) * 8)
#घोषणा   GEN8_DRB_VALID		  (1<<0)
#घोषणा GEN8_DRBREGU(x)			_MMIO(0x1000 + (x) * 8 + 4)

#घोषणा GEN12_DIST_DBS_POPULATED		_MMIO(0xd08)
#घोषणा   GEN12_DOORBELLS_PER_SQIDI_SHIFT	16
#घोषणा   GEN12_DOORBELLS_PER_SQIDI		(0xff)
#घोषणा   GEN12_SQIDIS_DOORBELL_EXIST		(0xffff)

#घोषणा DE_GUCRMR			_MMIO(0x44054)

#घोषणा GUC_BCS_RCS_IER			_MMIO(0xC550)
#घोषणा GUC_VCS2_VCS1_IER		_MMIO(0xC554)
#घोषणा GUC_WD_VECS_IER			_MMIO(0xC558)
#घोषणा GUC_PM_P24C_IER			_MMIO(0xC55C)

/* GuC Interrupt Vector */
#घोषणा GUC_INTR_GUC2HOST		BIT(15)
#घोषणा GUC_INTR_EXEC_ERROR		BIT(14)
#घोषणा GUC_INTR_DISPLAY_EVENT		BIT(13)
#घोषणा GUC_INTR_SEM_SIG		BIT(12)
#घोषणा GUC_INTR_IOMMU2GUC		BIT(11)
#घोषणा GUC_INTR_DOORBELL_RANG		BIT(10)
#घोषणा GUC_INTR_DMA_DONE		BIT(9)
#घोषणा GUC_INTR_FATAL_ERROR		BIT(8)
#घोषणा GUC_INTR_NOTIF_ERROR		BIT(7)
#घोषणा GUC_INTR_SW_INT_6		BIT(6)
#घोषणा GUC_INTR_SW_INT_5		BIT(5)
#घोषणा GUC_INTR_SW_INT_4		BIT(4)
#घोषणा GUC_INTR_SW_INT_3		BIT(3)
#घोषणा GUC_INTR_SW_INT_2		BIT(2)
#घोषणा GUC_INTR_SW_INT_1		BIT(1)
#घोषणा GUC_INTR_SW_INT_0		BIT(0)

#पूर्ण_अगर
