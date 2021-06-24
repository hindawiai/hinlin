<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2016-2017  Realtek Corporation.*/

#समावेश "halbt_precomp.h"

व्योम ex_hal8822b_wअगरi_only_hw_config(काष्ठा wअगरi_only_cfg *wअगरionlycfg)
अणु
	/*BB control*/
	halwअगरionly_phy_set_bb_reg(wअगरionlycfg, 0x4c, 0x01800000, 0x2);
	/*SW control*/
	halwअगरionly_phy_set_bb_reg(wअगरionlycfg, 0xcb4, 0xff, 0x77);
	/*antenna mux चयन */
	halwअगरionly_phy_set_bb_reg(wअगरionlycfg, 0x974, 0x300, 0x3);

	halwअगरionly_phy_set_bb_reg(wअगरionlycfg, 0x1990, 0x300, 0x0);

	halwअगरionly_phy_set_bb_reg(wअगरionlycfg, 0xcbc, 0x80000, 0x0);
	/*चयन to WL side controller and gnt_wl gnt_bt debug संकेत */
	halwअगरionly_phy_set_bb_reg(wअगरionlycfg, 0x70, 0xff000000, 0x0e);
	/*gnt_wl=1 , gnt_bt=0*/
	halwअगरionly_phy_set_bb_reg(wअगरionlycfg, 0x1704, 0xffffffff, 0x7700);
	halwअगरionly_phy_set_bb_reg(wअगरionlycfg, 0x1700, 0xffffffff, 0xc00f0038);
पूर्ण

व्योम ex_hal8822b_wअगरi_only_scannotअगरy(काष्ठा wअगरi_only_cfg *wअगरionlycfg,
				      u8 is_5g)
अणु
	hal8822b_wअगरi_only_चयन_antenna(wअगरionlycfg, is_5g);
पूर्ण

व्योम ex_hal8822b_wअगरi_only_चयनbandnotअगरy(काष्ठा wअगरi_only_cfg *wअगरionlycfg,
					    u8 is_5g)
अणु
	hal8822b_wअगरi_only_चयन_antenna(wअगरionlycfg, is_5g);
पूर्ण

व्योम hal8822b_wअगरi_only_चयन_antenna(काष्ठा wअगरi_only_cfg *wअगरionlycfg,
				       u8 is_5g)
अणु
	अगर (is_5g)
		halwअगरionly_phy_set_bb_reg(wअगरionlycfg, 0xcbc, 0x300, 0x1);
	अन्यथा
		halwअगरionly_phy_set_bb_reg(wअगरionlycfg, 0xcbc, 0x300, 0x2);
पूर्ण
