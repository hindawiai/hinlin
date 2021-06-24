<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c)  2018 Intel Corporation */

#अगर_अघोषित _IGC_NVM_H_
#घोषणा _IGC_NVM_H_

s32 igc_acquire_nvm(काष्ठा igc_hw *hw);
व्योम igc_release_nvm(काष्ठा igc_hw *hw);
s32 igc_पढ़ो_mac_addr(काष्ठा igc_hw *hw);
s32 igc_पढ़ो_nvm_eerd(काष्ठा igc_hw *hw, u16 offset, u16 words, u16 *data);
s32 igc_validate_nvm_checksum(काष्ठा igc_hw *hw);
s32 igc_update_nvm_checksum(काष्ठा igc_hw *hw);

#पूर्ण_अगर
