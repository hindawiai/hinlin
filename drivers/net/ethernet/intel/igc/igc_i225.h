<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c)  2018 Intel Corporation */

#अगर_अघोषित _IGC_I225_H_
#घोषणा _IGC_I225_H_

s32 igc_acquire_swfw_sync_i225(काष्ठा igc_hw *hw, u16 mask);
व्योम igc_release_swfw_sync_i225(काष्ठा igc_hw *hw, u16 mask);

s32 igc_init_nvm_params_i225(काष्ठा igc_hw *hw);
bool igc_get_flash_presence_i225(काष्ठा igc_hw *hw);
s32 igc_set_eee_i225(काष्ठा igc_hw *hw, bool adv2p5G, bool adv1G,
		     bool adv100M);
s32 igc_set_ltr_i225(काष्ठा igc_hw *hw, bool link);

#पूर्ण_अगर
