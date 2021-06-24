<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019, Intel Corporation. */

#अगर_अघोषित _ICE_NVM_H_
#घोषणा _ICE_NVM_H_

काष्ठा ice_orom_civd_info अणु
	u8 signature[4];	/* Must match ASCII '$CIV' अक्षरacters */
	u8 checksum;		/* Simple modulo 256 sum of all काष्ठाure bytes must equal 0 */
	__le32 combo_ver;	/* Combo Image Version number */
	u8 combo_name_len;	/* Length of the unicode combo image version string, max of 32 */
	__le16 combo_name[32];	/* Unicode string representing the Combo Image version */
पूर्ण __packed;

क्रमागत ice_status
ice_acquire_nvm(काष्ठा ice_hw *hw, क्रमागत ice_aq_res_access_type access);
व्योम ice_release_nvm(काष्ठा ice_hw *hw);
क्रमागत ice_status
ice_पढ़ो_flat_nvm(काष्ठा ice_hw *hw, u32 offset, u32 *length, u8 *data,
		  bool पढ़ो_shaकरोw_ram);
क्रमागत ice_status
ice_get_pfa_module_tlv(काष्ठा ice_hw *hw, u16 *module_tlv, u16 *module_tlv_len,
		       u16 module_type);
क्रमागत ice_status
ice_get_inactive_orom_ver(काष्ठा ice_hw *hw, काष्ठा ice_orom_info *orom);
क्रमागत ice_status
ice_get_inactive_nvm_ver(काष्ठा ice_hw *hw, काष्ठा ice_nvm_info *nvm);
क्रमागत ice_status
ice_get_inactive_netlist_ver(काष्ठा ice_hw *hw, काष्ठा ice_netlist_info *netlist);
क्रमागत ice_status
ice_पढ़ो_pba_string(काष्ठा ice_hw *hw, u8 *pba_num, u32 pba_num_size);
क्रमागत ice_status ice_init_nvm(काष्ठा ice_hw *hw);
क्रमागत ice_status ice_पढ़ो_sr_word(काष्ठा ice_hw *hw, u16 offset, u16 *data);
क्रमागत ice_status
ice_aq_update_nvm(काष्ठा ice_hw *hw, u16 module_typeid, u32 offset,
		  u16 length, व्योम *data, bool last_command, u8 command_flags,
		  काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_aq_erase_nvm(काष्ठा ice_hw *hw, u16 module_typeid, काष्ठा ice_sq_cd *cd);
क्रमागत ice_status ice_nvm_validate_checksum(काष्ठा ice_hw *hw);
क्रमागत ice_status ice_nvm_ग_लिखो_activate(काष्ठा ice_hw *hw, u8 cmd_flags);
क्रमागत ice_status ice_aq_nvm_update_empr(काष्ठा ice_hw *hw);
क्रमागत ice_status
ice_nvm_set_pkg_data(काष्ठा ice_hw *hw, bool del_pkg_data_flag, u8 *data,
		     u16 length, काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_nvm_pass_component_tbl(काष्ठा ice_hw *hw, u8 *data, u16 length,
			   u8 transfer_flag, u8 *comp_response,
			   u8 *comp_response_code, काष्ठा ice_sq_cd *cd);
#पूर्ण_अगर /* _ICE_NVM_H_ */
