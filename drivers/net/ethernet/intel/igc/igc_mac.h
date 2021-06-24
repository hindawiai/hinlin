<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c)  2018 Intel Corporation */

#अगर_अघोषित _IGC_MAC_H_
#घोषणा _IGC_MAC_H_

#समावेश "igc_hw.h"
#समावेश "igc_phy.h"
#समावेश "igc_defines.h"

/* क्रमward declaration */
s32 igc_disable_pcie_master(काष्ठा igc_hw *hw);
s32 igc_check_क्रम_copper_link(काष्ठा igc_hw *hw);
s32 igc_config_fc_after_link_up(काष्ठा igc_hw *hw);
s32 igc_क्रमce_mac_fc(काष्ठा igc_hw *hw);
व्योम igc_init_rx_addrs(काष्ठा igc_hw *hw, u16 rar_count);
s32 igc_setup_link(काष्ठा igc_hw *hw);
व्योम igc_clear_hw_cntrs_base(काष्ठा igc_hw *hw);
s32 igc_get_स्वतः_rd_करोne(काष्ठा igc_hw *hw);
व्योम igc_put_hw_semaphore(काष्ठा igc_hw *hw);
व्योम igc_rar_set(काष्ठा igc_hw *hw, u8 *addr, u32 index);
व्योम igc_config_collision_dist(काष्ठा igc_hw *hw);

s32 igc_get_speed_and_duplex_copper(काष्ठा igc_hw *hw, u16 *speed,
				    u16 *duplex);

bool igc_enable_mng_pass_thru(काष्ठा igc_hw *hw);
व्योम igc_update_mc_addr_list(काष्ठा igc_hw *hw,
			     u8 *mc_addr_list, u32 mc_addr_count);

क्रमागत igc_mng_mode अणु
	igc_mng_mode_none = 0,
	igc_mng_mode_asf,
	igc_mng_mode_pt,
	igc_mng_mode_ipmi,
	igc_mng_mode_host_अगर_only
पूर्ण;

#पूर्ण_अगर
