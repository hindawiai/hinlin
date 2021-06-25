<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 1999 - 2010 Intel Corporation.
 * Copyright (C) 2010 OKI SEMICONDUCTOR Co., LTD.
 *
 * This code was derived from the Intel e1000e Linux driver.
 */
#अगर_अघोषित _PCH_GBE_PHY_H_
#घोषणा _PCH_GBE_PHY_H_

#घोषणा PCH_GBE_PHY_REGS_LEN		32
#घोषणा	PCH_GBE_PHY_RESET_DELAY_US	10

s32 pch_gbe_phy_get_id(काष्ठा pch_gbe_hw *hw);
s32 pch_gbe_phy_पढ़ो_reg_miic(काष्ठा pch_gbe_hw *hw, u32 offset, u16 *data);
s32 pch_gbe_phy_ग_लिखो_reg_miic(काष्ठा pch_gbe_hw *hw, u32 offset, u16 data);
व्योम pch_gbe_phy_hw_reset(काष्ठा pch_gbe_hw *hw);
व्योम pch_gbe_phy_घातer_up(काष्ठा pch_gbe_hw *hw);
व्योम pch_gbe_phy_घातer_करोwn(काष्ठा pch_gbe_hw *hw);
व्योम pch_gbe_phy_set_rgmii(काष्ठा pch_gbe_hw *hw);
व्योम pch_gbe_phy_init_setting(काष्ठा pch_gbe_hw *hw);
पूर्णांक pch_gbe_phy_disable_hibernate(काष्ठा pch_gbe_hw *hw);

#पूर्ण_अगर /* _PCH_GBE_PHY_H_ */
