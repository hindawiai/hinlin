<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c)  2018 Intel Corporation */

#अगर_अघोषित _IGC_PHY_H_
#घोषणा _IGC_PHY_H_

#समावेश "igc_mac.h"

s32 igc_check_reset_block(काष्ठा igc_hw *hw);
s32 igc_phy_hw_reset(काष्ठा igc_hw *hw);
s32 igc_get_phy_id(काष्ठा igc_hw *hw);
s32 igc_phy_has_link(काष्ठा igc_hw *hw, u32 iterations,
		     u32 usec_पूर्णांकerval, bool *success);
s32 igc_check_करोwnshअगरt(काष्ठा igc_hw *hw);
s32 igc_setup_copper_link(काष्ठा igc_hw *hw);
व्योम igc_घातer_up_phy_copper(काष्ठा igc_hw *hw);
व्योम igc_घातer_करोwn_phy_copper(काष्ठा igc_hw *hw);
s32 igc_ग_लिखो_phy_reg_gpy(काष्ठा igc_hw *hw, u32 offset, u16 data);
s32 igc_पढ़ो_phy_reg_gpy(काष्ठा igc_hw *hw, u32 offset, u16 *data);
u16 igc_पढ़ो_phy_fw_version(काष्ठा igc_hw *hw);

#पूर्ण_अगर
