<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000E_NVM_H_
#घोषणा _E1000E_NVM_H_

s32 e1000e_acquire_nvm(काष्ठा e1000_hw *hw);

s32 e1000e_poll_eerd_eewr_करोne(काष्ठा e1000_hw *hw, पूर्णांक ee_reg);
s32 e1000_पढ़ो_mac_addr_generic(काष्ठा e1000_hw *hw);
s32 e1000_पढ़ो_pba_string_generic(काष्ठा e1000_hw *hw, u8 *pba_num,
				  u32 pba_num_size);
s32 e1000e_पढ़ो_nvm_eerd(काष्ठा e1000_hw *hw, u16 offset, u16 words, u16 *data);
s32 e1000e_valid_led_शेष(काष्ठा e1000_hw *hw, u16 *data);
s32 e1000e_validate_nvm_checksum_generic(काष्ठा e1000_hw *hw);
s32 e1000e_ग_लिखो_nvm_spi(काष्ठा e1000_hw *hw, u16 offset, u16 words, u16 *data);
s32 e1000e_update_nvm_checksum_generic(काष्ठा e1000_hw *hw);
व्योम e1000e_release_nvm(काष्ठा e1000_hw *hw);

#घोषणा E1000_STM_OPCODE	0xDB00

#पूर्ण_अगर
