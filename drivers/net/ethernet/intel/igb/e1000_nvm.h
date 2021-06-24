<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2007 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000_NVM_H_
#घोषणा _E1000_NVM_H_

s32  igb_acquire_nvm(काष्ठा e1000_hw *hw);
व्योम igb_release_nvm(काष्ठा e1000_hw *hw);
s32  igb_पढ़ो_mac_addr(काष्ठा e1000_hw *hw);
s32  igb_पढ़ो_part_num(काष्ठा e1000_hw *hw, u32 *part_num);
s32  igb_पढ़ो_part_string(काष्ठा e1000_hw *hw, u8 *part_num,
			  u32 part_num_size);
s32  igb_पढ़ो_nvm_eerd(काष्ठा e1000_hw *hw, u16 offset, u16 words, u16 *data);
s32  igb_पढ़ो_nvm_spi(काष्ठा e1000_hw *hw, u16 offset, u16 words, u16 *data);
s32  igb_ग_लिखो_nvm_spi(काष्ठा e1000_hw *hw, u16 offset, u16 words, u16 *data);
s32  igb_validate_nvm_checksum(काष्ठा e1000_hw *hw);
s32  igb_update_nvm_checksum(काष्ठा e1000_hw *hw);

काष्ठा e1000_fw_version अणु
	u32 etrack_id;
	u16 eep_major;
	u16 eep_minor;
	u16 eep_build;

	u8 invm_major;
	u8 invm_minor;
	u8 invm_img_type;

	bool or_valid;
	u16 or_major;
	u16 or_build;
	u16 or_patch;
पूर्ण;
व्योम igb_get_fw_version(काष्ठा e1000_hw *hw, काष्ठा e1000_fw_version *fw_vers);

#पूर्ण_अगर
