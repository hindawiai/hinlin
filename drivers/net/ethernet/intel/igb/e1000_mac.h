<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2007 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000_MAC_H_
#घोषणा _E1000_MAC_H_

#समावेश "e1000_hw.h"

#समावेश "e1000_phy.h"
#समावेश "e1000_nvm.h"
#समावेश "e1000_defines.h"
#समावेश "e1000_i210.h"

/* Functions that should not be called directly from drivers but can be used
 * by other files in this 'shared code'
 */
s32  igb_blink_led(काष्ठा e1000_hw *hw);
s32  igb_check_क्रम_copper_link(काष्ठा e1000_hw *hw);
s32  igb_cleanup_led(काष्ठा e1000_hw *hw);
s32  igb_config_fc_after_link_up(काष्ठा e1000_hw *hw);
s32  igb_disable_pcie_master(काष्ठा e1000_hw *hw);
s32  igb_क्रमce_mac_fc(काष्ठा e1000_hw *hw);
s32  igb_get_स्वतः_rd_करोne(काष्ठा e1000_hw *hw);
s32  igb_get_bus_info_pcie(काष्ठा e1000_hw *hw);
s32  igb_get_hw_semaphore(काष्ठा e1000_hw *hw);
s32  igb_get_speed_and_duplex_copper(काष्ठा e1000_hw *hw, u16 *speed,
				     u16 *duplex);
s32  igb_id_led_init(काष्ठा e1000_hw *hw);
s32  igb_led_off(काष्ठा e1000_hw *hw);
व्योम igb_update_mc_addr_list(काष्ठा e1000_hw *hw,
			     u8 *mc_addr_list, u32 mc_addr_count);
s32  igb_setup_link(काष्ठा e1000_hw *hw);
s32  igb_validate_mdi_setting(काष्ठा e1000_hw *hw);
s32  igb_ग_लिखो_8bit_ctrl_reg(काष्ठा e1000_hw *hw, u32 reg,
			     u32 offset, u8 data);

व्योम igb_clear_hw_cntrs_base(काष्ठा e1000_hw *hw);
व्योम igb_clear_vfta(काष्ठा e1000_hw *hw);
व्योम igb_ग_लिखो_vfta(काष्ठा e1000_hw *hw, u32 offset, u32 value);
s32  igb_vfta_set(काष्ठा e1000_hw *hw, u32 vid, u32 vind,
		  bool vlan_on, bool vlvf_bypass);
व्योम igb_config_collision_dist(काष्ठा e1000_hw *hw);
व्योम igb_init_rx_addrs(काष्ठा e1000_hw *hw, u16 rar_count);
व्योम igb_mta_set(काष्ठा e1000_hw *hw, u32 hash_value);
व्योम igb_put_hw_semaphore(काष्ठा e1000_hw *hw);
व्योम igb_rar_set(काष्ठा e1000_hw *hw, u8 *addr, u32 index);
s32  igb_check_alt_mac_addr(काष्ठा e1000_hw *hw);

bool igb_enable_mng_pass_thru(काष्ठा e1000_hw *hw);

क्रमागत e1000_mng_mode अणु
	e1000_mng_mode_none = 0,
	e1000_mng_mode_asf,
	e1000_mng_mode_pt,
	e1000_mng_mode_ipmi,
	e1000_mng_mode_host_अगर_only
पूर्ण;

#घोषणा E1000_FACTPS_MNGCG	0x20000000

#घोषणा E1000_FWSM_MODE_MASK	0xE
#घोषणा E1000_FWSM_MODE_SHIFT	1

#घोषणा E1000_MNG_DHCP_COOKIE_STATUS_VLAN	0x2

व्योम e1000_init_function_poपूर्णांकers_82575(काष्ठा e1000_hw *hw);

#पूर्ण_अगर
