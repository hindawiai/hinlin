<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _FM10K_COMMON_H_
#घोषणा _FM10K_COMMON_H_

#समावेश "fm10k_type.h"

#घोषणा FM10K_REMOVED(hw_addr) unlikely(!(hw_addr))

/* PCI configuration पढ़ो */
u16 fm10k_पढ़ो_pci_cfg_word(काष्ठा fm10k_hw *hw, u32 reg);

/* पढ़ो operations, indexed using DWORDS */
u32 fm10k_पढ़ो_reg(काष्ठा fm10k_hw *hw, पूर्णांक reg);

/* ग_लिखो operations, indexed using DWORDS */
#घोषणा fm10k_ग_लिखो_reg(hw, reg, val) \
करो अणु \
	u32 __iomem *hw_addr = READ_ONCE((hw)->hw_addr); \
	अगर (!FM10K_REMOVED(hw_addr)) \
		ग_लिखोl((val), &hw_addr[(reg)]); \
पूर्ण जबतक (0)

/* Switch रेजिस्टर ग_लिखो operations, index using DWORDS */
#घोषणा fm10k_ग_लिखो_sw_reg(hw, reg, val) \
करो अणु \
	u32 __iomem *sw_addr = READ_ONCE((hw)->sw_addr); \
	अगर (!FM10K_REMOVED(sw_addr)) \
		ग_लिखोl((val), &sw_addr[(reg)]); \
पूर्ण जबतक (0)

/* पढ़ो ctrl रेजिस्टर which has no clear on पढ़ो fields as PCIe flush */
#घोषणा fm10k_ग_लिखो_flush(hw) fm10k_पढ़ो_reg((hw), FM10K_CTRL)
s32 fm10k_get_bus_info_generic(काष्ठा fm10k_hw *hw);
s32 fm10k_get_invariants_generic(काष्ठा fm10k_hw *hw);
s32 fm10k_disable_queues_generic(काष्ठा fm10k_hw *hw, u16 q_cnt);
s32 fm10k_start_hw_generic(काष्ठा fm10k_hw *hw);
s32 fm10k_stop_hw_generic(काष्ठा fm10k_hw *hw);
u32 fm10k_पढ़ो_hw_stats_32b(काष्ठा fm10k_hw *hw, u32 addr,
			    काष्ठा fm10k_hw_stat *stat);
#घोषणा fm10k_update_hw_base_32b(stat, delta) ((stat)->base_l += (delta))
व्योम fm10k_update_hw_stats_q(काष्ठा fm10k_hw *hw, काष्ठा fm10k_hw_stats_q *q,
			     u32 idx, u32 count);
#घोषणा fm10k_unbind_hw_stats_32b(s) ((s)->base_h = 0)
व्योम fm10k_unbind_hw_stats_q(काष्ठा fm10k_hw_stats_q *q, u32 idx, u32 count);
s32 fm10k_get_host_state_generic(काष्ठा fm10k_hw *hw, bool *host_पढ़ोy);
#पूर्ण_अगर /* _FM10K_COMMON_H_ */
