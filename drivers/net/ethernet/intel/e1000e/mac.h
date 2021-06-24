<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000E_MAC_H_
#घोषणा _E1000E_MAC_H_

s32 e1000e_blink_led_generic(काष्ठा e1000_hw *hw);
s32 e1000e_check_क्रम_copper_link(काष्ठा e1000_hw *hw);
s32 e1000e_check_क्रम_fiber_link(काष्ठा e1000_hw *hw);
s32 e1000e_check_क्रम_serdes_link(काष्ठा e1000_hw *hw);
s32 e1000e_cleanup_led_generic(काष्ठा e1000_hw *hw);
s32 e1000e_config_fc_after_link_up(काष्ठा e1000_hw *hw);
s32 e1000e_disable_pcie_master(काष्ठा e1000_hw *hw);
s32 e1000e_क्रमce_mac_fc(काष्ठा e1000_hw *hw);
s32 e1000e_get_स्वतः_rd_करोne(काष्ठा e1000_hw *hw);
s32 e1000e_get_bus_info_pcie(काष्ठा e1000_hw *hw);
व्योम e1000_set_lan_id_single_port(काष्ठा e1000_hw *hw);
s32 e1000e_get_hw_semaphore(काष्ठा e1000_hw *hw);
s32 e1000e_get_speed_and_duplex_copper(काष्ठा e1000_hw *hw, u16 *speed,
				       u16 *duplex);
s32 e1000e_get_speed_and_duplex_fiber_serdes(काष्ठा e1000_hw *hw,
					     u16 *speed, u16 *duplex);
s32 e1000e_id_led_init_generic(काष्ठा e1000_hw *hw);
s32 e1000e_led_on_generic(काष्ठा e1000_hw *hw);
s32 e1000e_led_off_generic(काष्ठा e1000_hw *hw);
व्योम e1000e_update_mc_addr_list_generic(काष्ठा e1000_hw *hw,
					u8 *mc_addr_list, u32 mc_addr_count);
s32 e1000e_set_fc_watermarks(काष्ठा e1000_hw *hw);
s32 e1000e_setup_fiber_serdes_link(काष्ठा e1000_hw *hw);
s32 e1000e_setup_led_generic(काष्ठा e1000_hw *hw);
s32 e1000e_setup_link_generic(काष्ठा e1000_hw *hw);
s32 e1000e_validate_mdi_setting_generic(काष्ठा e1000_hw *hw);
s32 e1000e_validate_mdi_setting_crossover_generic(काष्ठा e1000_hw *hw);

व्योम e1000e_clear_hw_cntrs_base(काष्ठा e1000_hw *hw);
व्योम e1000_clear_vfta_generic(काष्ठा e1000_hw *hw);
व्योम e1000e_init_rx_addrs(काष्ठा e1000_hw *hw, u16 rar_count);
व्योम e1000e_put_hw_semaphore(काष्ठा e1000_hw *hw);
s32 e1000_check_alt_mac_addr_generic(काष्ठा e1000_hw *hw);
व्योम e1000e_reset_adaptive(काष्ठा e1000_hw *hw);
व्योम e1000e_set_pcie_no_snoop(काष्ठा e1000_hw *hw, u32 no_snoop);
व्योम e1000e_update_adaptive(काष्ठा e1000_hw *hw);
व्योम e1000_ग_लिखो_vfta_generic(काष्ठा e1000_hw *hw, u32 offset, u32 value);

व्योम e1000_set_lan_id_multi_port_pcie(काष्ठा e1000_hw *hw);
u32 e1000e_rar_get_count_generic(काष्ठा e1000_hw *hw);
पूर्णांक e1000e_rar_set_generic(काष्ठा e1000_hw *hw, u8 *addr, u32 index);
व्योम e1000e_config_collision_dist_generic(काष्ठा e1000_hw *hw);

#पूर्ण_अगर
