<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित __IXGBE_VF_H__
#घोषणा __IXGBE_VF_H__

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/netdevice.h>

#समावेश "defines.h"
#समावेश "regs.h"
#समावेश "mbx.h"

काष्ठा ixgbe_hw;

काष्ठा ixgbe_mac_operations अणु
	s32 (*init_hw)(काष्ठा ixgbe_hw *);
	s32 (*reset_hw)(काष्ठा ixgbe_hw *);
	s32 (*start_hw)(काष्ठा ixgbe_hw *);
	s32 (*clear_hw_cntrs)(काष्ठा ixgbe_hw *);
	क्रमागत ixgbe_media_type (*get_media_type)(काष्ठा ixgbe_hw *);
	s32 (*get_mac_addr)(काष्ठा ixgbe_hw *, u8 *);
	s32 (*stop_adapter)(काष्ठा ixgbe_hw *);
	s32 (*get_bus_info)(काष्ठा ixgbe_hw *);
	s32 (*negotiate_api_version)(काष्ठा ixgbe_hw *hw, पूर्णांक api);

	/* Link */
	s32 (*setup_link)(काष्ठा ixgbe_hw *, ixgbe_link_speed, bool, bool);
	s32 (*check_link)(काष्ठा ixgbe_hw *, ixgbe_link_speed *, bool *, bool);
	s32 (*get_link_capabilities)(काष्ठा ixgbe_hw *, ixgbe_link_speed *,
				     bool *);

	/* RAR, Multicast, VLAN */
	s32 (*set_rar)(काष्ठा ixgbe_hw *, u32, u8 *, u32);
	s32 (*set_uc_addr)(काष्ठा ixgbe_hw *, u32, u8 *);
	s32 (*init_rx_addrs)(काष्ठा ixgbe_hw *);
	s32 (*update_mc_addr_list)(काष्ठा ixgbe_hw *, काष्ठा net_device *);
	s32 (*update_xcast_mode)(काष्ठा ixgbe_hw *, पूर्णांक);
	s32 (*enable_mc)(काष्ठा ixgbe_hw *);
	s32 (*disable_mc)(काष्ठा ixgbe_hw *);
	s32 (*clear_vfta)(काष्ठा ixgbe_hw *);
	s32 (*set_vfta)(काष्ठा ixgbe_hw *, u32, u32, bool);
	s32 (*set_rlpml)(काष्ठा ixgbe_hw *, u16);
पूर्ण;

क्रमागत ixgbe_mac_type अणु
	ixgbe_mac_unknown = 0,
	ixgbe_mac_82599_vf,
	ixgbe_mac_X540_vf,
	ixgbe_mac_X550_vf,
	ixgbe_mac_X550EM_x_vf,
	ixgbe_mac_x550em_a_vf,
	ixgbe_num_macs
पूर्ण;

काष्ठा ixgbe_mac_info अणु
	काष्ठा ixgbe_mac_operations ops;
	u8 addr[6];
	u8 perm_addr[6];

	क्रमागत ixgbe_mac_type type;

	s32  mc_filter_type;

	bool get_link_status;
	u32  max_tx_queues;
	u32  max_rx_queues;
	u32  max_msix_vectors;
पूर्ण;

काष्ठा ixgbe_mbx_operations अणु
	s32 (*init_params)(काष्ठा ixgbe_hw *hw);
	s32 (*पढ़ो)(काष्ठा ixgbe_hw *, u32 *, u16);
	s32 (*ग_लिखो)(काष्ठा ixgbe_hw *, u32 *, u16);
	s32 (*पढ़ो_posted)(काष्ठा ixgbe_hw *, u32 *, u16);
	s32 (*ग_लिखो_posted)(काष्ठा ixgbe_hw *, u32 *, u16);
	s32 (*check_क्रम_msg)(काष्ठा ixgbe_hw *);
	s32 (*check_क्रम_ack)(काष्ठा ixgbe_hw *);
	s32 (*check_क्रम_rst)(काष्ठा ixgbe_hw *);
पूर्ण;

काष्ठा ixgbe_mbx_stats अणु
	u32 msgs_tx;
	u32 msgs_rx;

	u32 acks;
	u32 reqs;
	u32 rsts;
पूर्ण;

काष्ठा ixgbe_mbx_info अणु
	काष्ठा ixgbe_mbx_operations ops;
	काष्ठा ixgbe_mbx_stats stats;
	u32 समयout;
	u32 udelay;
	u32 v2p_mailbox;
	u16 size;
पूर्ण;

काष्ठा ixgbe_hw अणु
	व्योम *back;

	u8 __iomem *hw_addr;

	काष्ठा ixgbe_mac_info mac;
	काष्ठा ixgbe_mbx_info mbx;

	u16 device_id;
	u16 subप्रणाली_venकरोr_id;
	u16 subप्रणाली_device_id;
	u16 venकरोr_id;

	u8  revision_id;
	bool adapter_stopped;

	पूर्णांक api_version;
पूर्ण;

काष्ठा ixgbevf_hw_stats अणु
	u64 base_vfgprc;
	u64 base_vfgptc;
	u64 base_vfgorc;
	u64 base_vfgotc;
	u64 base_vfmprc;

	u64 last_vfgprc;
	u64 last_vfgptc;
	u64 last_vfgorc;
	u64 last_vfgotc;
	u64 last_vfmprc;

	u64 vfgprc;
	u64 vfgptc;
	u64 vfgorc;
	u64 vfgotc;
	u64 vfmprc;

	u64 saved_reset_vfgprc;
	u64 saved_reset_vfgptc;
	u64 saved_reset_vfgorc;
	u64 saved_reset_vfgotc;
	u64 saved_reset_vfmprc;
पूर्ण;

काष्ठा ixgbevf_info अणु
	क्रमागत ixgbe_mac_type mac;
	स्थिर काष्ठा ixgbe_mac_operations *mac_ops;
पूर्ण;

#घोषणा IXGBE_FAILED_READ_REG 0xffffffffU

#घोषणा IXGBE_REMOVED(a) unlikely(!(a))

अटल अंतरभूत व्योम ixgbe_ग_लिखो_reg(काष्ठा ixgbe_hw *hw, u32 reg, u32 value)
अणु
	u8 __iomem *reg_addr = READ_ONCE(hw->hw_addr);

	अगर (IXGBE_REMOVED(reg_addr))
		वापस;
	ग_लिखोl(value, reg_addr + reg);
पूर्ण

#घोषणा IXGBE_WRITE_REG(h, r, v) ixgbe_ग_लिखो_reg(h, r, v)

u32 ixgbevf_पढ़ो_reg(काष्ठा ixgbe_hw *hw, u32 reg);
#घोषणा IXGBE_READ_REG(h, r) ixgbevf_पढ़ो_reg(h, r)

अटल अंतरभूत व्योम ixgbe_ग_लिखो_reg_array(काष्ठा ixgbe_hw *hw, u32 reg,
					 u32 offset, u32 value)
अणु
	ixgbe_ग_लिखो_reg(hw, reg + (offset << 2), value);
पूर्ण

#घोषणा IXGBE_WRITE_REG_ARRAY(h, r, o, v) ixgbe_ग_लिखो_reg_array(h, r, o, v)

अटल अंतरभूत u32 ixgbe_पढ़ो_reg_array(काष्ठा ixgbe_hw *hw, u32 reg,
				       u32 offset)
अणु
	वापस ixgbevf_पढ़ो_reg(hw, reg + (offset << 2));
पूर्ण

#घोषणा IXGBE_READ_REG_ARRAY(h, r, o) ixgbe_पढ़ो_reg_array(h, r, o)

पूर्णांक ixgbevf_get_queues(काष्ठा ixgbe_hw *hw, अचिन्हित पूर्णांक *num_tcs,
		       अचिन्हित पूर्णांक *शेष_tc);
पूर्णांक ixgbevf_get_reta_locked(काष्ठा ixgbe_hw *hw, u32 *reta, पूर्णांक num_rx_queues);
पूर्णांक ixgbevf_get_rss_key_locked(काष्ठा ixgbe_hw *hw, u8 *rss_key);
#पूर्ण_अगर /* __IXGBE_VF_H__ */
