<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Intel Corporation. */

#समावेश "ice_common.h"

/**
 * ice_aq_पढ़ो_nvm
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @module_typeid: module poपूर्णांकer location in words from the NVM beginning
 * @offset: byte offset from the module beginning
 * @length: length of the section to be पढ़ो (in bytes from the offset)
 * @data: command buffer (size [bytes] = length)
 * @last_command: tells अगर this is the last command in a series
 * @पढ़ो_shaकरोw_ram: tell अगर this is a shaकरोw RAM पढ़ो
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Read the NVM using the admin queue commands (0x0701)
 */
अटल क्रमागत ice_status
ice_aq_पढ़ो_nvm(काष्ठा ice_hw *hw, u16 module_typeid, u32 offset, u16 length,
		व्योम *data, bool last_command, bool पढ़ो_shaकरोw_ram,
		काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aq_desc desc;
	काष्ठा ice_aqc_nvm *cmd;

	cmd = &desc.params.nvm;

	अगर (offset > ICE_AQC_NVM_MAX_OFFSET)
		वापस ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_nvm_पढ़ो);

	अगर (!पढ़ो_shaकरोw_ram && module_typeid == ICE_AQC_NVM_START_POINT)
		cmd->cmd_flags |= ICE_AQC_NVM_FLASH_ONLY;

	/* If this is the last command in a series, set the proper flag. */
	अगर (last_command)
		cmd->cmd_flags |= ICE_AQC_NVM_LAST_CMD;
	cmd->module_typeid = cpu_to_le16(module_typeid);
	cmd->offset_low = cpu_to_le16(offset & 0xFFFF);
	cmd->offset_high = (offset >> 16) & 0xFF;
	cmd->length = cpu_to_le16(length);

	वापस ice_aq_send_cmd(hw, &desc, data, length, cd);
पूर्ण

/**
 * ice_पढ़ो_flat_nvm - Read portion of NVM by flat offset
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @offset: offset from beginning of NVM
 * @length: (in) number of bytes to पढ़ो; (out) number of bytes actually पढ़ो
 * @data: buffer to वापस data in (sized to fit the specअगरied length)
 * @पढ़ो_shaकरोw_ram: अगर true, पढ़ो from shaकरोw RAM instead of NVM
 *
 * Reads a portion of the NVM, as a flat memory space. This function correctly
 * अवरोधs पढ़ो requests across Shaकरोw RAM sectors and ensures that no single
 * पढ़ो request exceeds the maximum 4KB पढ़ो क्रम a single AdminQ command.
 *
 * Returns a status code on failure. Note that the data poपूर्णांकer may be
 * partially updated अगर some पढ़ोs succeed beक्रमe a failure.
 */
क्रमागत ice_status
ice_पढ़ो_flat_nvm(काष्ठा ice_hw *hw, u32 offset, u32 *length, u8 *data,
		  bool पढ़ो_shaकरोw_ram)
अणु
	क्रमागत ice_status status;
	u32 inlen = *length;
	u32 bytes_पढ़ो = 0;
	bool last_cmd;

	*length = 0;

	/* Verअगरy the length of the पढ़ो अगर this is क्रम the Shaकरोw RAM */
	अगर (पढ़ो_shaकरोw_ram && ((offset + inlen) > (hw->flash.sr_words * 2u))) अणु
		ice_debug(hw, ICE_DBG_NVM, "NVM error: requested offset is beyond Shadow RAM limit\n");
		वापस ICE_ERR_PARAM;
	पूर्ण

	करो अणु
		u32 पढ़ो_size, sector_offset;

		/* ice_aq_पढ़ो_nvm cannot पढ़ो more than 4KB at a समय.
		 * Additionally, a पढ़ो from the Shaकरोw RAM may not cross over
		 * a sector boundary. Conveniently, the sector size is also
		 * 4KB.
		 */
		sector_offset = offset % ICE_AQ_MAX_BUF_LEN;
		पढ़ो_size = min_t(u32, ICE_AQ_MAX_BUF_LEN - sector_offset,
				  inlen - bytes_पढ़ो);

		last_cmd = !(bytes_पढ़ो + पढ़ो_size < inlen);

		status = ice_aq_पढ़ो_nvm(hw, ICE_AQC_NVM_START_POINT,
					 offset, पढ़ो_size,
					 data + bytes_पढ़ो, last_cmd,
					 पढ़ो_shaकरोw_ram, शून्य);
		अगर (status)
			अवरोध;

		bytes_पढ़ो += पढ़ो_size;
		offset += पढ़ो_size;
	पूर्ण जबतक (!last_cmd);

	*length = bytes_पढ़ो;
	वापस status;
पूर्ण

/**
 * ice_aq_update_nvm
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @module_typeid: module poपूर्णांकer location in words from the NVM beginning
 * @offset: byte offset from the module beginning
 * @length: length of the section to be written (in bytes from the offset)
 * @data: command buffer (size [bytes] = length)
 * @last_command: tells अगर this is the last command in a series
 * @command_flags: command parameters
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Update the NVM using the admin queue commands (0x0703)
 */
क्रमागत ice_status
ice_aq_update_nvm(काष्ठा ice_hw *hw, u16 module_typeid, u32 offset,
		  u16 length, व्योम *data, bool last_command, u8 command_flags,
		  काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aq_desc desc;
	काष्ठा ice_aqc_nvm *cmd;

	cmd = &desc.params.nvm;

	/* In offset the highest byte must be zeroed. */
	अगर (offset & 0xFF000000)
		वापस ICE_ERR_PARAM;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_nvm_ग_लिखो);

	cmd->cmd_flags |= command_flags;

	/* If this is the last command in a series, set the proper flag. */
	अगर (last_command)
		cmd->cmd_flags |= ICE_AQC_NVM_LAST_CMD;
	cmd->module_typeid = cpu_to_le16(module_typeid);
	cmd->offset_low = cpu_to_le16(offset & 0xFFFF);
	cmd->offset_high = (offset >> 16) & 0xFF;
	cmd->length = cpu_to_le16(length);

	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	वापस ice_aq_send_cmd(hw, &desc, data, length, cd);
पूर्ण

/**
 * ice_aq_erase_nvm
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @module_typeid: module poपूर्णांकer location in words from the NVM beginning
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Erase the NVM sector using the admin queue commands (0x0702)
 */
क्रमागत ice_status
ice_aq_erase_nvm(काष्ठा ice_hw *hw, u16 module_typeid, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aq_desc desc;
	काष्ठा ice_aqc_nvm *cmd;

	cmd = &desc.params.nvm;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_nvm_erase);

	cmd->module_typeid = cpu_to_le16(module_typeid);
	cmd->length = cpu_to_le16(ICE_AQC_NVM_ERASE_LEN);
	cmd->offset_low = 0;
	cmd->offset_high = 0;

	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, cd);
पूर्ण

/**
 * ice_पढ़ो_sr_word_aq - Reads Shaकरोw RAM via AQ
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: offset of the Shaकरोw RAM word to पढ़ो (0x000000 - 0x001FFF)
 * @data: word पढ़ो from the Shaकरोw RAM
 *
 * Reads one 16 bit word from the Shaकरोw RAM using ice_पढ़ो_flat_nvm.
 */
अटल क्रमागत ice_status
ice_पढ़ो_sr_word_aq(काष्ठा ice_hw *hw, u16 offset, u16 *data)
अणु
	u32 bytes = माप(u16);
	क्रमागत ice_status status;
	__le16 data_local;

	/* Note that ice_पढ़ो_flat_nvm takes पूर्णांकo account the 4Kb AdminQ and
	 * Shaकरोw RAM sector restrictions necessary when पढ़ोing from the NVM.
	 */
	status = ice_पढ़ो_flat_nvm(hw, offset * माप(u16), &bytes,
				   (__क्रमce u8 *)&data_local, true);
	अगर (status)
		वापस status;

	*data = le16_to_cpu(data_local);
	वापस 0;
पूर्ण

/**
 * ice_acquire_nvm - Generic request क्रम acquiring the NVM ownership
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @access: NVM access type (पढ़ो or ग_लिखो)
 *
 * This function will request NVM ownership.
 */
क्रमागत ice_status
ice_acquire_nvm(काष्ठा ice_hw *hw, क्रमागत ice_aq_res_access_type access)
अणु
	अगर (hw->flash.blank_nvm_mode)
		वापस 0;

	वापस ice_acquire_res(hw, ICE_NVM_RES_ID, access, ICE_NVM_TIMEOUT);
पूर्ण

/**
 * ice_release_nvm - Generic request क्रम releasing the NVM ownership
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * This function will release NVM ownership.
 */
व्योम ice_release_nvm(काष्ठा ice_hw *hw)
अणु
	अगर (hw->flash.blank_nvm_mode)
		वापस;

	ice_release_res(hw, ICE_NVM_RES_ID);
पूर्ण

/**
 * ice_get_flash_bank_offset - Get offset पूर्णांकo requested flash bank
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @bank: whether to पढ़ो from the active or inactive flash bank
 * @module: the module to पढ़ो from
 *
 * Based on the module, lookup the module offset from the beginning of the
 * flash.
 *
 * Returns the flash offset. Note that a value of zero is invalid and must be
 * treated as an error.
 */
अटल u32 ice_get_flash_bank_offset(काष्ठा ice_hw *hw, क्रमागत ice_bank_select bank, u16 module)
अणु
	काष्ठा ice_bank_info *banks = &hw->flash.banks;
	क्रमागत ice_flash_bank active_bank;
	bool second_bank_active;
	u32 offset, size;

	चयन (module) अणु
	हाल ICE_SR_1ST_NVM_BANK_PTR:
		offset = banks->nvm_ptr;
		size = banks->nvm_size;
		active_bank = banks->nvm_bank;
		अवरोध;
	हाल ICE_SR_1ST_OROM_BANK_PTR:
		offset = banks->orom_ptr;
		size = banks->orom_size;
		active_bank = banks->orom_bank;
		अवरोध;
	हाल ICE_SR_NETLIST_BANK_PTR:
		offset = banks->netlist_ptr;
		size = banks->netlist_size;
		active_bank = banks->netlist_bank;
		अवरोध;
	शेष:
		ice_debug(hw, ICE_DBG_NVM, "Unexpected value for flash module: 0x%04x\n", module);
		वापस 0;
	पूर्ण

	चयन (active_bank) अणु
	हाल ICE_1ST_FLASH_BANK:
		second_bank_active = false;
		अवरोध;
	हाल ICE_2ND_FLASH_BANK:
		second_bank_active = true;
		अवरोध;
	शेष:
		ice_debug(hw, ICE_DBG_NVM, "Unexpected value for active flash bank: %u\n",
			  active_bank);
		वापस 0;
	पूर्ण

	/* The second flash bank is stored immediately following the first
	 * bank. Based on whether the 1st or 2nd bank is active, and whether
	 * we want the active or inactive bank, calculate the desired offset.
	 */
	चयन (bank) अणु
	हाल ICE_ACTIVE_FLASH_BANK:
		वापस offset + (second_bank_active ? size : 0);
	हाल ICE_INACTIVE_FLASH_BANK:
		वापस offset + (second_bank_active ? 0 : size);
	पूर्ण

	ice_debug(hw, ICE_DBG_NVM, "Unexpected value for flash bank selection: %u\n", bank);
	वापस 0;
पूर्ण

/**
 * ice_पढ़ो_flash_module - Read a word from one of the मुख्य NVM modules
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @bank: which bank of the module to पढ़ो
 * @module: the module to पढ़ो
 * @offset: the offset पूर्णांकo the module in bytes
 * @data: storage क्रम the word पढ़ो from the flash
 * @length: bytes of data to पढ़ो
 *
 * Read data from the specअगरied flash module. The bank parameter indicates
 * whether or not to पढ़ो from the active bank or the inactive bank of that
 * module.
 *
 * The word will be पढ़ो using flat NVM access, and relies on the
 * hw->flash.banks data being setup by ice_determine_active_flash_banks()
 * during initialization.
 */
अटल क्रमागत ice_status
ice_पढ़ो_flash_module(काष्ठा ice_hw *hw, क्रमागत ice_bank_select bank, u16 module,
		      u32 offset, u8 *data, u32 length)
अणु
	क्रमागत ice_status status;
	u32 start;

	start = ice_get_flash_bank_offset(hw, bank, module);
	अगर (!start) अणु
		ice_debug(hw, ICE_DBG_NVM, "Unable to calculate flash bank offset for module 0x%04x\n",
			  module);
		वापस ICE_ERR_PARAM;
	पूर्ण

	status = ice_acquire_nvm(hw, ICE_RES_READ);
	अगर (status)
		वापस status;

	status = ice_पढ़ो_flat_nvm(hw, start + offset, &length, data, false);

	ice_release_nvm(hw);

	वापस status;
पूर्ण

/**
 * ice_पढ़ो_nvm_module - Read from the active मुख्य NVM module
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @bank: whether to पढ़ो from active or inactive NVM module
 * @offset: offset पूर्णांकo the NVM module to पढ़ो, in words
 * @data: storage क्रम वापसed word value
 *
 * Read the specअगरied word from the active NVM module. This includes the CSS
 * header at the start of the NVM module.
 */
अटल क्रमागत ice_status
ice_पढ़ो_nvm_module(काष्ठा ice_hw *hw, क्रमागत ice_bank_select bank, u32 offset, u16 *data)
अणु
	क्रमागत ice_status status;
	__le16 data_local;

	status = ice_पढ़ो_flash_module(hw, bank, ICE_SR_1ST_NVM_BANK_PTR, offset * माप(u16),
				       (__क्रमce u8 *)&data_local, माप(u16));
	अगर (!status)
		*data = le16_to_cpu(data_local);

	वापस status;
पूर्ण

/**
 * ice_पढ़ो_nvm_sr_copy - Read a word from the Shaकरोw RAM copy in the NVM bank
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @bank: whether to पढ़ो from the active or inactive NVM module
 * @offset: offset पूर्णांकo the Shaकरोw RAM copy to पढ़ो, in words
 * @data: storage क्रम वापसed word value
 *
 * Read the specअगरied word from the copy of the Shaकरोw RAM found in the
 * specअगरied NVM module.
 */
अटल क्रमागत ice_status
ice_पढ़ो_nvm_sr_copy(काष्ठा ice_hw *hw, क्रमागत ice_bank_select bank, u32 offset, u16 *data)
अणु
	वापस ice_पढ़ो_nvm_module(hw, bank, ICE_NVM_SR_COPY_WORD_OFFSET + offset, data);
पूर्ण

/**
 * ice_पढ़ो_netlist_module - Read data from the netlist module area
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @bank: whether to पढ़ो from the active or inactive module
 * @offset: offset पूर्णांकo the netlist to पढ़ो from
 * @data: storage क्रम वापसed word value
 *
 * Read a word from the specअगरied netlist bank.
 */
अटल क्रमागत ice_status
ice_पढ़ो_netlist_module(काष्ठा ice_hw *hw, क्रमागत ice_bank_select bank, u32 offset, u16 *data)
अणु
	क्रमागत ice_status status;
	__le16 data_local;

	status = ice_पढ़ो_flash_module(hw, bank, ICE_SR_NETLIST_BANK_PTR, offset * माप(u16),
				       (__क्रमce u8 *)&data_local, माप(u16));
	अगर (!status)
		*data = le16_to_cpu(data_local);

	वापस status;
पूर्ण

/**
 * ice_पढ़ो_sr_word - Reads Shaकरोw RAM word and acquire NVM अगर necessary
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: offset of the Shaकरोw RAM word to पढ़ो (0x000000 - 0x001FFF)
 * @data: word पढ़ो from the Shaकरोw RAM
 *
 * Reads one 16 bit word from the Shaकरोw RAM using the ice_पढ़ो_sr_word_aq.
 */
क्रमागत ice_status ice_पढ़ो_sr_word(काष्ठा ice_hw *hw, u16 offset, u16 *data)
अणु
	क्रमागत ice_status status;

	status = ice_acquire_nvm(hw, ICE_RES_READ);
	अगर (!status) अणु
		status = ice_पढ़ो_sr_word_aq(hw, offset, data);
		ice_release_nvm(hw);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_get_pfa_module_tlv - Reads sub module TLV from NVM PFA
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @module_tlv: poपूर्णांकer to module TLV to वापस
 * @module_tlv_len: poपूर्णांकer to module TLV length to वापस
 * @module_type: module type requested
 *
 * Finds the requested sub module TLV type from the Preserved Field
 * Area (PFA) and वापसs the TLV poपूर्णांकer and length. The caller can
 * use these to पढ़ो the variable length TLV value.
 */
क्रमागत ice_status
ice_get_pfa_module_tlv(काष्ठा ice_hw *hw, u16 *module_tlv, u16 *module_tlv_len,
		       u16 module_type)
अणु
	क्रमागत ice_status status;
	u16 pfa_len, pfa_ptr;
	u16 next_tlv;

	status = ice_पढ़ो_sr_word(hw, ICE_SR_PFA_PTR, &pfa_ptr);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_INIT, "Preserved Field Array pointer.\n");
		वापस status;
	पूर्ण
	status = ice_पढ़ो_sr_word(hw, pfa_ptr, &pfa_len);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_INIT, "Failed to read PFA length.\n");
		वापस status;
	पूर्ण
	/* Starting with first TLV after PFA length, iterate through the list
	 * of TLVs to find the requested one.
	 */
	next_tlv = pfa_ptr + 1;
	जबतक (next_tlv < pfa_ptr + pfa_len) अणु
		u16 tlv_sub_module_type;
		u16 tlv_len;

		/* Read TLV type */
		status = ice_पढ़ो_sr_word(hw, next_tlv, &tlv_sub_module_type);
		अगर (status) अणु
			ice_debug(hw, ICE_DBG_INIT, "Failed to read TLV type.\n");
			अवरोध;
		पूर्ण
		/* Read TLV length */
		status = ice_पढ़ो_sr_word(hw, next_tlv + 1, &tlv_len);
		अगर (status) अणु
			ice_debug(hw, ICE_DBG_INIT, "Failed to read TLV length.\n");
			अवरोध;
		पूर्ण
		अगर (tlv_sub_module_type == module_type) अणु
			अगर (tlv_len) अणु
				*module_tlv = next_tlv;
				*module_tlv_len = tlv_len;
				वापस 0;
			पूर्ण
			वापस ICE_ERR_INVAL_SIZE;
		पूर्ण
		/* Check next TLV, i.e. current TLV poपूर्णांकer + length + 2 words
		 * (क्रम current TLV's type and length)
		 */
		next_tlv = next_tlv + tlv_len + 2;
	पूर्ण
	/* Module करोes not exist */
	वापस ICE_ERR_DOES_NOT_EXIST;
पूर्ण

/**
 * ice_पढ़ो_pba_string - Reads part number string from NVM
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @pba_num: stores the part number string from the NVM
 * @pba_num_size: part number string buffer length
 *
 * Reads the part number string from the NVM.
 */
क्रमागत ice_status
ice_पढ़ो_pba_string(काष्ठा ice_hw *hw, u8 *pba_num, u32 pba_num_size)
अणु
	u16 pba_tlv, pba_tlv_len;
	क्रमागत ice_status status;
	u16 pba_word, pba_size;
	u16 i;

	status = ice_get_pfa_module_tlv(hw, &pba_tlv, &pba_tlv_len,
					ICE_SR_PBA_BLOCK_PTR);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_INIT, "Failed to read PBA Block TLV.\n");
		वापस status;
	पूर्ण

	/* pba_size is the next word */
	status = ice_पढ़ो_sr_word(hw, (pba_tlv + 2), &pba_size);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_INIT, "Failed to read PBA Section size.\n");
		वापस status;
	पूर्ण

	अगर (pba_tlv_len < pba_size) अणु
		ice_debug(hw, ICE_DBG_INIT, "Invalid PBA Block TLV size.\n");
		वापस ICE_ERR_INVAL_SIZE;
	पूर्ण

	/* Subtract one to get PBA word count (PBA Size word is included in
	 * total size)
	 */
	pba_size--;
	अगर (pba_num_size < (((u32)pba_size * 2) + 1)) अणु
		ice_debug(hw, ICE_DBG_INIT, "Buffer too small for PBA data.\n");
		वापस ICE_ERR_PARAM;
	पूर्ण

	क्रम (i = 0; i < pba_size; i++) अणु
		status = ice_पढ़ो_sr_word(hw, (pba_tlv + 2 + 1) + i, &pba_word);
		अगर (status) अणु
			ice_debug(hw, ICE_DBG_INIT, "Failed to read PBA Block word %d.\n", i);
			वापस status;
		पूर्ण

		pba_num[(i * 2)] = (pba_word >> 8) & 0xFF;
		pba_num[(i * 2) + 1] = pba_word & 0xFF;
	पूर्ण
	pba_num[(pba_size * 2)] = '\0';

	वापस status;
पूर्ण

/**
 * ice_get_nvm_ver_info - Read NVM version inक्रमmation
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @bank: whether to पढ़ो from the active or inactive flash bank
 * @nvm: poपूर्णांकer to NVM info काष्ठाure
 *
 * Read the NVM EETRACK ID and map version of the मुख्य NVM image bank, filling
 * in the NVM info काष्ठाure.
 */
अटल क्रमागत ice_status
ice_get_nvm_ver_info(काष्ठा ice_hw *hw, क्रमागत ice_bank_select bank, काष्ठा ice_nvm_info *nvm)
अणु
	u16 eetrack_lo, eetrack_hi, ver;
	क्रमागत ice_status status;

	status = ice_पढ़ो_nvm_sr_copy(hw, bank, ICE_SR_NVM_DEV_STARTER_VER, &ver);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_NVM, "Failed to read DEV starter version.\n");
		वापस status;
	पूर्ण

	nvm->major = (ver & ICE_NVM_VER_HI_MASK) >> ICE_NVM_VER_HI_SHIFT;
	nvm->minor = (ver & ICE_NVM_VER_LO_MASK) >> ICE_NVM_VER_LO_SHIFT;

	status = ice_पढ़ो_nvm_sr_copy(hw, bank, ICE_SR_NVM_EETRACK_LO, &eetrack_lo);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_NVM, "Failed to read EETRACK lo.\n");
		वापस status;
	पूर्ण
	status = ice_पढ़ो_nvm_sr_copy(hw, bank, ICE_SR_NVM_EETRACK_HI, &eetrack_hi);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_NVM, "Failed to read EETRACK hi.\n");
		वापस status;
	पूर्ण

	nvm->eetrack = (eetrack_hi << 16) | eetrack_lo;

	वापस 0;
पूर्ण

/**
 * ice_get_inactive_nvm_ver - Read Option ROM version from the inactive bank
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @nvm: storage क्रम Option ROM version inक्रमmation
 *
 * Reads the NVM EETRACK ID, Map version, and security revision of the
 * inactive NVM bank. Used to access version data क्रम a pending update that
 * has not yet been activated.
 */
क्रमागत ice_status ice_get_inactive_nvm_ver(काष्ठा ice_hw *hw, काष्ठा ice_nvm_info *nvm)
अणु
	वापस ice_get_nvm_ver_info(hw, ICE_INACTIVE_FLASH_BANK, nvm);
पूर्ण

/**
 * ice_get_orom_civd_data - Get the combo version inक्रमmation from Option ROM
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @bank: whether to पढ़ो from the active or inactive flash module
 * @civd: storage क्रम the Option ROM CIVD data.
 *
 * Searches through the Option ROM flash contents to locate the CIVD data क्रम
 * the image.
 */
अटल क्रमागत ice_status
ice_get_orom_civd_data(काष्ठा ice_hw *hw, क्रमागत ice_bank_select bank,
		       काष्ठा ice_orom_civd_info *civd)
अणु
	काष्ठा ice_orom_civd_info पंचांगp;
	क्रमागत ice_status status;
	u32 offset;

	/* The CIVD section is located in the Option ROM aligned to 512 bytes.
	 * The first 4 bytes must contain the ASCII अक्षरacters "$CIV".
	 * A simple modulo 256 sum of all of the bytes of the काष्ठाure must
	 * equal 0.
	 */
	क्रम (offset = 0; (offset + 512) <= hw->flash.banks.orom_size; offset += 512) अणु
		u8 sum = 0, i;

		status = ice_पढ़ो_flash_module(hw, bank, ICE_SR_1ST_OROM_BANK_PTR,
					       offset, (u8 *)&पंचांगp, माप(पंचांगp));
		अगर (status) अणु
			ice_debug(hw, ICE_DBG_NVM, "Unable to read Option ROM CIVD data\n");
			वापस status;
		पूर्ण

		/* Skip क्रमward until we find a matching signature */
		अगर (स_भेद("$CIV", पंचांगp.signature, माप(पंचांगp.signature)) != 0)
			जारी;

		/* Verअगरy that the simple checksum is zero */
		क्रम (i = 0; i < माप(पंचांगp); i++)
			/* cppcheck-suppress objectIndex */
			sum += ((u8 *)&पंचांगp)[i];

		अगर (sum) अणु
			ice_debug(hw, ICE_DBG_NVM, "Found CIVD data with invalid checksum of %u\n",
				  sum);
			वापस ICE_ERR_NVM;
		पूर्ण

		*civd = पंचांगp;
		वापस 0;
	पूर्ण

	वापस ICE_ERR_NVM;
पूर्ण

/**
 * ice_get_orom_ver_info - Read Option ROM version inक्रमmation
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @bank: whether to पढ़ो from the active or inactive flash module
 * @orom: poपूर्णांकer to Option ROM info काष्ठाure
 *
 * Read Option ROM version and security revision from the Option ROM flash
 * section.
 */
अटल क्रमागत ice_status
ice_get_orom_ver_info(काष्ठा ice_hw *hw, क्रमागत ice_bank_select bank, काष्ठा ice_orom_info *orom)
अणु
	काष्ठा ice_orom_civd_info civd;
	क्रमागत ice_status status;
	u32 combo_ver;

	status = ice_get_orom_civd_data(hw, bank, &civd);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_NVM, "Failed to locate valid Option ROM CIVD data\n");
		वापस status;
	पूर्ण

	combo_ver = le32_to_cpu(civd.combo_ver);

	orom->major = (u8)((combo_ver & ICE_OROM_VER_MASK) >> ICE_OROM_VER_SHIFT);
	orom->patch = (u8)(combo_ver & ICE_OROM_VER_PATCH_MASK);
	orom->build = (u16)((combo_ver & ICE_OROM_VER_BUILD_MASK) >> ICE_OROM_VER_BUILD_SHIFT);

	वापस 0;
पूर्ण

/**
 * ice_get_inactive_orom_ver - Read Option ROM version from the inactive bank
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @orom: storage क्रम Option ROM version inक्रमmation
 *
 * Reads the Option ROM version and security revision data क्रम the inactive
 * section of flash. Used to access version data क्रम a pending update that has
 * not yet been activated.
 */
क्रमागत ice_status ice_get_inactive_orom_ver(काष्ठा ice_hw *hw, काष्ठा ice_orom_info *orom)
अणु
	वापस ice_get_orom_ver_info(hw, ICE_INACTIVE_FLASH_BANK, orom);
पूर्ण

/**
 * ice_get_netlist_info
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @bank: whether to पढ़ो from the active or inactive flash bank
 * @netlist: poपूर्णांकer to netlist version info काष्ठाure
 *
 * Get the netlist version inक्रमmation from the requested bank. Reads the Link
 * Topology section to find the Netlist ID block and extract the relevant
 * inक्रमmation पूर्णांकo the netlist version काष्ठाure.
 */
अटल क्रमागत ice_status
ice_get_netlist_info(काष्ठा ice_hw *hw, क्रमागत ice_bank_select bank,
		     काष्ठा ice_netlist_info *netlist)
अणु
	u16 module_id, length, node_count, i;
	क्रमागत ice_status status;
	u16 *id_blk;

	status = ice_पढ़ो_netlist_module(hw, bank, ICE_NETLIST_TYPE_OFFSET, &module_id);
	अगर (status)
		वापस status;

	अगर (module_id != ICE_NETLIST_LINK_TOPO_MOD_ID) अणु
		ice_debug(hw, ICE_DBG_NVM, "Expected netlist module_id ID of 0x%04x, but got 0x%04x\n",
			  ICE_NETLIST_LINK_TOPO_MOD_ID, module_id);
		वापस ICE_ERR_NVM;
	पूर्ण

	status = ice_पढ़ो_netlist_module(hw, bank, ICE_LINK_TOPO_MODULE_LEN, &length);
	अगर (status)
		वापस status;

	/* sanity check that we have at least enough words to store the netlist ID block */
	अगर (length < ICE_NETLIST_ID_BLK_SIZE) अणु
		ice_debug(hw, ICE_DBG_NVM, "Netlist Link Topology module too small. Expected at least %u words, but got %u words.\n",
			  ICE_NETLIST_ID_BLK_SIZE, length);
		वापस ICE_ERR_NVM;
	पूर्ण

	status = ice_पढ़ो_netlist_module(hw, bank, ICE_LINK_TOPO_NODE_COUNT, &node_count);
	अगर (status)
		वापस status;
	node_count &= ICE_LINK_TOPO_NODE_COUNT_M;

	id_blk = kसुस्मृति(ICE_NETLIST_ID_BLK_SIZE, माप(*id_blk), GFP_KERNEL);
	अगर (!id_blk)
		वापस ICE_ERR_NO_MEMORY;

	/* Read out the entire Netlist ID Block at once. */
	status = ice_पढ़ो_flash_module(hw, bank, ICE_SR_NETLIST_BANK_PTR,
				       ICE_NETLIST_ID_BLK_OFFSET(node_count) * माप(u16),
				       (u8 *)id_blk, ICE_NETLIST_ID_BLK_SIZE * माप(u16));
	अगर (status)
		जाओ निकास_error;

	क्रम (i = 0; i < ICE_NETLIST_ID_BLK_SIZE; i++)
		id_blk[i] = le16_to_cpu(((__क्रमce __le16 *)id_blk)[i]);

	netlist->major = id_blk[ICE_NETLIST_ID_BLK_MAJOR_VER_HIGH] << 16 |
			 id_blk[ICE_NETLIST_ID_BLK_MAJOR_VER_LOW];
	netlist->minor = id_blk[ICE_NETLIST_ID_BLK_MINOR_VER_HIGH] << 16 |
			 id_blk[ICE_NETLIST_ID_BLK_MINOR_VER_LOW];
	netlist->type = id_blk[ICE_NETLIST_ID_BLK_TYPE_HIGH] << 16 |
			id_blk[ICE_NETLIST_ID_BLK_TYPE_LOW];
	netlist->rev = id_blk[ICE_NETLIST_ID_BLK_REV_HIGH] << 16 |
		       id_blk[ICE_NETLIST_ID_BLK_REV_LOW];
	netlist->cust_ver = id_blk[ICE_NETLIST_ID_BLK_CUST_VER];
	/* Read the left most 4 bytes of SHA */
	netlist->hash = id_blk[ICE_NETLIST_ID_BLK_SHA_HASH_WORD(15)] << 16 |
			id_blk[ICE_NETLIST_ID_BLK_SHA_HASH_WORD(14)];

निकास_error:
	kमुक्त(id_blk);

	वापस status;
पूर्ण

/**
 * ice_get_inactive_netlist_ver
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @netlist: poपूर्णांकer to netlist version info काष्ठाure
 *
 * Read the netlist version data from the inactive netlist bank. Used to
 * extract version data of a pending flash update in order to display the
 * version data.
 */
क्रमागत ice_status ice_get_inactive_netlist_ver(काष्ठा ice_hw *hw, काष्ठा ice_netlist_info *netlist)
अणु
	वापस ice_get_netlist_info(hw, ICE_INACTIVE_FLASH_BANK, netlist);
पूर्ण

/**
 * ice_discover_flash_size - Discover the available flash size.
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * The device flash could be up to 16MB in size. However, it is possible that
 * the actual size is smaller. Use bisection to determine the accessible size
 * of flash memory.
 */
अटल क्रमागत ice_status ice_discover_flash_size(काष्ठा ice_hw *hw)
अणु
	u32 min_size = 0, max_size = ICE_AQC_NVM_MAX_OFFSET + 1;
	क्रमागत ice_status status;

	status = ice_acquire_nvm(hw, ICE_RES_READ);
	अगर (status)
		वापस status;

	जबतक ((max_size - min_size) > 1) अणु
		u32 offset = (max_size + min_size) / 2;
		u32 len = 1;
		u8 data;

		status = ice_पढ़ो_flat_nvm(hw, offset, &len, &data, false);
		अगर (status == ICE_ERR_AQ_ERROR &&
		    hw->adminq.sq_last_status == ICE_AQ_RC_EINVAL) अणु
			ice_debug(hw, ICE_DBG_NVM, "%s: New upper bound of %u bytes\n",
				  __func__, offset);
			status = 0;
			max_size = offset;
		पूर्ण अन्यथा अगर (!status) अणु
			ice_debug(hw, ICE_DBG_NVM, "%s: New lower bound of %u bytes\n",
				  __func__, offset);
			min_size = offset;
		पूर्ण अन्यथा अणु
			/* an unexpected error occurred */
			जाओ err_पढ़ो_flat_nvm;
		पूर्ण
	पूर्ण

	ice_debug(hw, ICE_DBG_NVM, "Predicted flash size is %u bytes\n", max_size);

	hw->flash.flash_size = max_size;

err_पढ़ो_flat_nvm:
	ice_release_nvm(hw);

	वापस status;
पूर्ण

/**
 * ice_पढ़ो_sr_poपूर्णांकer - Read the value of a Shaकरोw RAM poपूर्णांकer word
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: the word offset of the Shaकरोw RAM word to पढ़ो
 * @poपूर्णांकer: poपूर्णांकer value पढ़ो from Shaकरोw RAM
 *
 * Read the given Shaकरोw RAM word, and convert it to a poपूर्णांकer value specअगरied
 * in bytes. This function assumes the specअगरied offset is a valid poपूर्णांकer
 * word.
 *
 * Each poपूर्णांकer word specअगरies whether it is stored in word size or 4KB
 * sector size by using the highest bit. The reported poपूर्णांकer value will be in
 * bytes, पूर्णांकended क्रम flat NVM पढ़ोs.
 */
अटल क्रमागत ice_status
ice_पढ़ो_sr_poपूर्णांकer(काष्ठा ice_hw *hw, u16 offset, u32 *poपूर्णांकer)
अणु
	क्रमागत ice_status status;
	u16 value;

	status = ice_पढ़ो_sr_word(hw, offset, &value);
	अगर (status)
		वापस status;

	/* Determine अगर the poपूर्णांकer is in 4KB or word units */
	अगर (value & ICE_SR_NVM_PTR_4KB_UNITS)
		*poपूर्णांकer = (value & ~ICE_SR_NVM_PTR_4KB_UNITS) * 4 * 1024;
	अन्यथा
		*poपूर्णांकer = value * 2;

	वापस 0;
पूर्ण

/**
 * ice_पढ़ो_sr_area_size - Read an area size from a Shaकरोw RAM word
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: the word offset of the Shaकरोw RAM to पढ़ो
 * @size: size value पढ़ो from the Shaकरोw RAM
 *
 * Read the given Shaकरोw RAM word, and convert it to an area size value
 * specअगरied in bytes. This function assumes the specअगरied offset is a valid
 * area size word.
 *
 * Each area size word is specअगरied in 4KB sector units. This function reports
 * the size in bytes, पूर्णांकended क्रम flat NVM पढ़ोs.
 */
अटल क्रमागत ice_status
ice_पढ़ो_sr_area_size(काष्ठा ice_hw *hw, u16 offset, u32 *size)
अणु
	क्रमागत ice_status status;
	u16 value;

	status = ice_पढ़ो_sr_word(hw, offset, &value);
	अगर (status)
		वापस status;

	/* Area sizes are always specअगरied in 4KB units */
	*size = value * 4 * 1024;

	वापस 0;
पूर्ण

/**
 * ice_determine_active_flash_banks - Discover active bank क्रम each module
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * Read the Shaकरोw RAM control word and determine which banks are active क्रम
 * the NVM, OROM, and Netlist modules. Also पढ़ो and calculate the associated
 * poपूर्णांकer and size. These values are then cached पूर्णांकo the ice_flash_info
 * काष्ठाure क्रम later use in order to calculate the correct offset to पढ़ो
 * from the active module.
 */
अटल क्रमागत ice_status
ice_determine_active_flash_banks(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_bank_info *banks = &hw->flash.banks;
	क्रमागत ice_status status;
	u16 ctrl_word;

	status = ice_पढ़ो_sr_word(hw, ICE_SR_NVM_CTRL_WORD, &ctrl_word);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_NVM, "Failed to read the Shadow RAM control word\n");
		वापस status;
	पूर्ण

	/* Check that the control word indicates validity */
	अगर ((ctrl_word & ICE_SR_CTRL_WORD_1_M) >> ICE_SR_CTRL_WORD_1_S != ICE_SR_CTRL_WORD_VALID) अणु
		ice_debug(hw, ICE_DBG_NVM, "Shadow RAM control word is invalid\n");
		वापस ICE_ERR_CFG;
	पूर्ण

	अगर (!(ctrl_word & ICE_SR_CTRL_WORD_NVM_BANK))
		banks->nvm_bank = ICE_1ST_FLASH_BANK;
	अन्यथा
		banks->nvm_bank = ICE_2ND_FLASH_BANK;

	अगर (!(ctrl_word & ICE_SR_CTRL_WORD_OROM_BANK))
		banks->orom_bank = ICE_1ST_FLASH_BANK;
	अन्यथा
		banks->orom_bank = ICE_2ND_FLASH_BANK;

	अगर (!(ctrl_word & ICE_SR_CTRL_WORD_NETLIST_BANK))
		banks->netlist_bank = ICE_1ST_FLASH_BANK;
	अन्यथा
		banks->netlist_bank = ICE_2ND_FLASH_BANK;

	status = ice_पढ़ो_sr_poपूर्णांकer(hw, ICE_SR_1ST_NVM_BANK_PTR, &banks->nvm_ptr);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_NVM, "Failed to read NVM bank pointer\n");
		वापस status;
	पूर्ण

	status = ice_पढ़ो_sr_area_size(hw, ICE_SR_NVM_BANK_SIZE, &banks->nvm_size);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_NVM, "Failed to read NVM bank area size\n");
		वापस status;
	पूर्ण

	status = ice_पढ़ो_sr_poपूर्णांकer(hw, ICE_SR_1ST_OROM_BANK_PTR, &banks->orom_ptr);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_NVM, "Failed to read OROM bank pointer\n");
		वापस status;
	पूर्ण

	status = ice_पढ़ो_sr_area_size(hw, ICE_SR_OROM_BANK_SIZE, &banks->orom_size);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_NVM, "Failed to read OROM bank area size\n");
		वापस status;
	पूर्ण

	status = ice_पढ़ो_sr_poपूर्णांकer(hw, ICE_SR_NETLIST_BANK_PTR, &banks->netlist_ptr);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_NVM, "Failed to read Netlist bank pointer\n");
		वापस status;
	पूर्ण

	status = ice_पढ़ो_sr_area_size(hw, ICE_SR_NETLIST_BANK_SIZE, &banks->netlist_size);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_NVM, "Failed to read Netlist bank area size\n");
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_init_nvm - initializes NVM setting
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * This function पढ़ोs and populates NVM settings such as Shaकरोw RAM size,
 * max_समयout, and blank_nvm_mode
 */
क्रमागत ice_status ice_init_nvm(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_flash_info *flash = &hw->flash;
	क्रमागत ice_status status;
	u32 fla, gens_stat;
	u8 sr_size;

	/* The SR size is stored regardless of the NVM programming mode
	 * as the blank mode may be used in the factory line.
	 */
	gens_stat = rd32(hw, GLNVM_GENS);
	sr_size = (gens_stat & GLNVM_GENS_SR_SIZE_M) >> GLNVM_GENS_SR_SIZE_S;

	/* Switching to words (sr_size contains घातer of 2) */
	flash->sr_words = BIT(sr_size) * ICE_SR_WORDS_IN_1KB;

	/* Check अगर we are in the normal or blank NVM programming mode */
	fla = rd32(hw, GLNVM_FLA);
	अगर (fla & GLNVM_FLA_LOCKED_M) अणु /* Normal programming mode */
		flash->blank_nvm_mode = false;
	पूर्ण अन्यथा अणु
		/* Blank programming mode */
		flash->blank_nvm_mode = true;
		ice_debug(hw, ICE_DBG_NVM, "NVM init error: unsupported blank mode.\n");
		वापस ICE_ERR_NVM_BLANK_MODE;
	पूर्ण

	status = ice_discover_flash_size(hw);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_NVM, "NVM init error: failed to discover flash size.\n");
		वापस status;
	पूर्ण

	status = ice_determine_active_flash_banks(hw);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_NVM, "Failed to determine active flash banks.\n");
		वापस status;
	पूर्ण

	status = ice_get_nvm_ver_info(hw, ICE_ACTIVE_FLASH_BANK, &flash->nvm);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_INIT, "Failed to read NVM info.\n");
		वापस status;
	पूर्ण

	status = ice_get_orom_ver_info(hw, ICE_ACTIVE_FLASH_BANK, &flash->orom);
	अगर (status)
		ice_debug(hw, ICE_DBG_INIT, "Failed to read Option ROM info.\n");

	/* पढ़ो the netlist version inक्रमmation */
	status = ice_get_netlist_info(hw, ICE_ACTIVE_FLASH_BANK, &flash->netlist);
	अगर (status)
		ice_debug(hw, ICE_DBG_INIT, "Failed to read netlist info.\n");

	वापस 0;
पूर्ण

/**
 * ice_nvm_validate_checksum
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * Verअगरy NVM PFA checksum validity (0x0706)
 */
क्रमागत ice_status ice_nvm_validate_checksum(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_aqc_nvm_checksum *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	status = ice_acquire_nvm(hw, ICE_RES_READ);
	अगर (status)
		वापस status;

	cmd = &desc.params.nvm_checksum;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_nvm_checksum);
	cmd->flags = ICE_AQC_NVM_CHECKSUM_VERIFY;

	status = ice_aq_send_cmd(hw, &desc, शून्य, 0, शून्य);
	ice_release_nvm(hw);

	अगर (!status)
		अगर (le16_to_cpu(cmd->checksum) != ICE_AQC_NVM_CHECKSUM_CORRECT)
			status = ICE_ERR_NVM_CHECKSUM;

	वापस status;
पूर्ण

/**
 * ice_nvm_ग_लिखो_activate
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @cmd_flags: NVM activate admin command bits (banks to be validated)
 *
 * Update the control word with the required banks' validity bits
 * and dumps the Shaकरोw RAM to flash (0x0707)
 */
क्रमागत ice_status ice_nvm_ग_लिखो_activate(काष्ठा ice_hw *hw, u8 cmd_flags)
अणु
	काष्ठा ice_aqc_nvm *cmd;
	काष्ठा ice_aq_desc desc;

	cmd = &desc.params.nvm;
	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_nvm_ग_लिखो_activate);

	cmd->cmd_flags = cmd_flags;

	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, शून्य);
पूर्ण

/**
 * ice_aq_nvm_update_empr
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * Update empr (0x0709). This command allows SW to
 * request an EMPR to activate new FW.
 */
क्रमागत ice_status ice_aq_nvm_update_empr(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_nvm_update_empr);

	वापस ice_aq_send_cmd(hw, &desc, शून्य, 0, शून्य);
पूर्ण

/* ice_nvm_set_pkg_data
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @del_pkg_data_flag: If is set then the current pkg_data store by FW
 *		       is deleted.
 *		       If bit is set to 1, then buffer should be size 0.
 * @data: poपूर्णांकer to buffer
 * @length: length of the buffer
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Set package data (0x070A). This command is equivalent to the reception
 * of a PLDM FW Update GetPackageData cmd. This command should be sent
 * as part of the NVM update as the first cmd in the flow.
 */

क्रमागत ice_status
ice_nvm_set_pkg_data(काष्ठा ice_hw *hw, bool del_pkg_data_flag, u8 *data,
		     u16 length, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_nvm_pkg_data *cmd;
	काष्ठा ice_aq_desc desc;

	अगर (length != 0 && !data)
		वापस ICE_ERR_PARAM;

	cmd = &desc.params.pkg_data;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_nvm_pkg_data);
	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	अगर (del_pkg_data_flag)
		cmd->cmd_flags |= ICE_AQC_NVM_PKG_DELETE;

	वापस ice_aq_send_cmd(hw, &desc, data, length, cd);
पूर्ण

/* ice_nvm_pass_component_tbl
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @data: poपूर्णांकer to buffer
 * @length: length of the buffer
 * @transfer_flag: parameter क्रम determining stage of the update
 * @comp_response: a poपूर्णांकer to the response from the 0x070B AQC.
 * @comp_response_code: a poपूर्णांकer to the response code from the 0x070B AQC.
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Pass component table (0x070B). This command is equivalent to the reception
 * of a PLDM FW Update PassComponentTable cmd. This command should be sent once
 * per component. It can be only sent after Set Package Data cmd and beक्रमe
 * actual update. FW will assume these commands are going to be sent until
 * the TransferFlag is set to End or StartAndEnd.
 */

क्रमागत ice_status
ice_nvm_pass_component_tbl(काष्ठा ice_hw *hw, u8 *data, u16 length,
			   u8 transfer_flag, u8 *comp_response,
			   u8 *comp_response_code, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_nvm_pass_comp_tbl *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	अगर (!data || !comp_response || !comp_response_code)
		वापस ICE_ERR_PARAM;

	cmd = &desc.params.pass_comp_tbl;

	ice_fill_dflt_direct_cmd_desc(&desc,
				      ice_aqc_opc_nvm_pass_component_tbl);
	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	cmd->transfer_flag = transfer_flag;
	status = ice_aq_send_cmd(hw, &desc, data, length, cd);

	अगर (!status) अणु
		*comp_response = cmd->component_response;
		*comp_response_code = cmd->component_response_code;
	पूर्ण
	वापस status;
पूर्ण
