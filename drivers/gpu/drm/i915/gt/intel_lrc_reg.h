<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014-2018 Intel Corporation
 */

#अगर_अघोषित _INTEL_LRC_REG_H_
#घोषणा _INTEL_LRC_REG_H_

#समावेश <linux/types.h>

#घोषणा CTX_DESC_FORCE_RESTORE BIT_ULL(2)

/* GEN8 to GEN12 Reg State Context */
#घोषणा CTX_CONTEXT_CONTROL		(0x02 + 1)
#घोषणा CTX_RING_HEAD			(0x04 + 1)
#घोषणा CTX_RING_TAIL			(0x06 + 1)
#घोषणा CTX_RING_START			(0x08 + 1)
#घोषणा CTX_RING_CTL			(0x0a + 1)
#घोषणा CTX_BB_STATE			(0x10 + 1)
#घोषणा CTX_TIMESTAMP			(0x22 + 1)
#घोषणा CTX_PDP3_UDW			(0x24 + 1)
#घोषणा CTX_PDP3_LDW			(0x26 + 1)
#घोषणा CTX_PDP2_UDW			(0x28 + 1)
#घोषणा CTX_PDP2_LDW			(0x2a + 1)
#घोषणा CTX_PDP1_UDW			(0x2c + 1)
#घोषणा CTX_PDP1_LDW			(0x2e + 1)
#घोषणा CTX_PDP0_UDW			(0x30 + 1)
#घोषणा CTX_PDP0_LDW			(0x32 + 1)
#घोषणा CTX_R_PWR_CLK_STATE		(0x42 + 1)

#घोषणा GEN9_CTX_RING_MI_MODE		0x54

#घोषणा ASSIGN_CTX_PDP(ppgtt, reg_state, n) करो अणु \
	u32 *reg_state__ = (reg_state); \
	स्थिर u64 addr__ = i915_page_dir_dma_addr((ppgtt), (n)); \
	(reg_state__)[CTX_PDP ## n ## _UDW] = upper_32_bits(addr__); \
	(reg_state__)[CTX_PDP ## n ## _LDW] = lower_32_bits(addr__); \
पूर्ण जबतक (0)

#घोषणा ASSIGN_CTX_PML4(ppgtt, reg_state) करो अणु \
	u32 *reg_state__ = (reg_state); \
	स्थिर u64 addr__ = px_dma((ppgtt)->pd); \
	(reg_state__)[CTX_PDP0_UDW] = upper_32_bits(addr__); \
	(reg_state__)[CTX_PDP0_LDW] = lower_32_bits(addr__); \
पूर्ण जबतक (0)

#घोषणा GEN8_CTX_RCS_INसूचीECT_CTX_OFFSET_DEFAULT	0x17
#घोषणा GEN9_CTX_RCS_INसूचीECT_CTX_OFFSET_DEFAULT	0x26
#घोषणा GEN10_CTX_RCS_INसूचीECT_CTX_OFFSET_DEFAULT	0x19
#घोषणा GEN11_CTX_RCS_INसूचीECT_CTX_OFFSET_DEFAULT	0x1A
#घोषणा GEN12_CTX_RCS_INसूचीECT_CTX_OFFSET_DEFAULT	0xD

#घोषणा GEN8_EXECLISTS_STATUS_BUF 0x370
#घोषणा GEN11_EXECLISTS_STATUS_BUF2 0x3c0

/* Execlists regs */
#घोषणा RING_ELSP(base)				_MMIO((base) + 0x230)
#घोषणा RING_EXECLIST_STATUS_LO(base)		_MMIO((base) + 0x234)
#घोषणा RING_EXECLIST_STATUS_HI(base)		_MMIO((base) + 0x234 + 4)
#घोषणा RING_CONTEXT_CONTROL(base)		_MMIO((base) + 0x244)
#घोषणा	  CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT	REG_BIT(0)
#घोषणा   CTX_CTRL_RS_CTX_ENABLE		REG_BIT(1)
#घोषणा	  CTX_CTRL_ENGINE_CTX_SAVE_INHIBIT	REG_BIT(2)
#घोषणा	  CTX_CTRL_INHIBIT_SYN_CTX_SWITCH	REG_BIT(3)
#घोषणा	  GEN12_CTX_CTRL_OAR_CONTEXT_ENABLE	REG_BIT(8)
#घोषणा RING_CONTEXT_STATUS_PTR(base)		_MMIO((base) + 0x3a0)
#घोषणा RING_EXECLIST_SQ_CONTENTS(base)		_MMIO((base) + 0x510)
#घोषणा RING_EXECLIST_CONTROL(base)		_MMIO((base) + 0x550)
#घोषणा	  EL_CTRL_LOAD				REG_BIT(0)

/*
 * The करोcs specअगरy that the ग_लिखो poपूर्णांकer wraps around after 5h, "After status
 * is written out to the last available status QW at offset 5h, this poपूर्णांकer
 * wraps to 0."
 *
 * Thereक्रमe, one must infer than even though there are 3 bits available, 6 and
 * 7 appear to be * reserved.
 */
#घोषणा GEN8_CSB_ENTRIES 6
#घोषणा GEN8_CSB_PTR_MASK 0x7
#घोषणा GEN8_CSB_READ_PTR_MASK	(GEN8_CSB_PTR_MASK << 8)
#घोषणा GEN8_CSB_WRITE_PTR_MASK	(GEN8_CSB_PTR_MASK << 0)

#घोषणा GEN11_CSB_ENTRIES 12
#घोषणा GEN11_CSB_PTR_MASK 0xf
#घोषणा GEN11_CSB_READ_PTR_MASK		(GEN11_CSB_PTR_MASK << 8)
#घोषणा GEN11_CSB_WRITE_PTR_MASK	(GEN11_CSB_PTR_MASK << 0)

#घोषणा MAX_CONTEXT_HW_ID	(1 << 21) /* exclusive */
#घोषणा MAX_GUC_CONTEXT_HW_ID	(1 << 20) /* exclusive */
#घोषणा GEN11_MAX_CONTEXT_HW_ID	(1 << 11) /* exclusive */
/* in Gen12 ID 0x7FF is reserved to indicate idle */
#घोषणा GEN12_MAX_CONTEXT_HW_ID	(GEN11_MAX_CONTEXT_HW_ID - 1)

#पूर्ण_अगर /* _INTEL_LRC_REG_H_ */
