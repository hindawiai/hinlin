<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2018-2019, Intel Corporation. */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/uuid.h>
#समावेश <linux/crc32.h>
#समावेश <linux/pldmfw.h>
#समावेश "ice.h"
#समावेश "ice_fw_update.h"

काष्ठा ice_fwu_priv अणु
	काष्ठा pldmfw context;

	काष्ठा ice_pf *pf;
	काष्ठा netlink_ext_ack *extack;

	/* Track which NVM banks to activate at the end of the update */
	u8 activate_flags;
पूर्ण;

/**
 * ice_send_package_data - Send record package data to firmware
 * @context: PLDM fw update काष्ठाure
 * @data: poपूर्णांकer to the package data
 * @length: length of the package data
 *
 * Send a copy of the package data associated with the PLDM record matching
 * this device to the firmware.
 *
 * Note that this function sends an AdminQ command that will fail unless the
 * NVM resource has been acquired.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
अटल पूर्णांक
ice_send_package_data(काष्ठा pldmfw *context, स्थिर u8 *data, u16 length)
अणु
	काष्ठा ice_fwu_priv *priv = container_of(context, काष्ठा ice_fwu_priv, context);
	काष्ठा netlink_ext_ack *extack = priv->extack;
	काष्ठा device *dev = context->dev;
	काष्ठा ice_pf *pf = priv->pf;
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	u8 *package_data;

	dev_dbg(dev, "Sending PLDM record package data to firmware\n");

	package_data = kmemdup(data, length, GFP_KERNEL);
	अगर (!package_data)
		वापस -ENOMEM;

	status = ice_nvm_set_pkg_data(hw, false, package_data, length, शून्य);

	kमुक्त(package_data);

	अगर (status) अणु
		dev_err(dev, "Failed to send record package data to firmware, err %s aq_err %s\n",
			ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		NL_SET_ERR_MSG_MOD(extack, "Failed to record package data to firmware");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_check_component_response - Report firmware response to a component
 * @pf: device निजी data काष्ठाure
 * @id: component id being checked
 * @response: indicates whether this component can be updated
 * @code: code indicating reason क्रम response
 * @extack: netlink extended ACK काष्ठाure
 *
 * Check whether firmware indicates अगर this component can be updated. Report
 * a suitable error message over the netlink extended ACK अगर the component
 * cannot be updated.
 *
 * Returns: zero अगर the component can be updated, or -ECANCELED of the
 * firmware indicates the component cannot be updated.
 */
अटल पूर्णांक
ice_check_component_response(काष्ठा ice_pf *pf, u16 id, u8 response, u8 code,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	स्थिर अक्षर *component;

	चयन (id) अणु
	हाल NVM_COMP_ID_OROM:
		component = "fw.undi";
		अवरोध;
	हाल NVM_COMP_ID_NVM:
		component = "fw.mgmt";
		अवरोध;
	हाल NVM_COMP_ID_NETLIST:
		component = "fw.netlist";
		अवरोध;
	शेष:
		WARN(1, "Unexpected unknown component identifier 0x%02x", id);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "%s: firmware response 0x%x, code 0x%x\n",
		component, response, code);

	चयन (response) अणु
	हाल ICE_AQ_NVM_PASS_COMP_CAN_BE_UPDATED:
		/* firmware indicated this update is good to proceed */
		वापस 0;
	हाल ICE_AQ_NVM_PASS_COMP_CAN_MAY_BE_UPDATEABLE:
		dev_warn(dev, "firmware recommends not updating %s, as it may result in a downgrade. continuing anyways\n", component);
		वापस 0;
	हाल ICE_AQ_NVM_PASS_COMP_CAN_NOT_BE_UPDATED:
		dev_info(dev, "firmware has rejected updating %s\n", component);
		अवरोध;
	पूर्ण

	चयन (code) अणु
	हाल ICE_AQ_NVM_PASS_COMP_STAMP_IDENTICAL_CODE:
		dev_err(dev, "Component comparison stamp for %s is identical to the running image\n",
			component);
		NL_SET_ERR_MSG_MOD(extack, "Component comparison stamp is identical to running image");
		अवरोध;
	हाल ICE_AQ_NVM_PASS_COMP_STAMP_LOWER:
		dev_err(dev, "Component comparison stamp for %s is lower than the running image\n",
			component);
		NL_SET_ERR_MSG_MOD(extack, "Component comparison stamp is lower than running image");
		अवरोध;
	हाल ICE_AQ_NVM_PASS_COMP_INVALID_STAMP_CODE:
		dev_err(dev, "Component comparison stamp for %s is invalid\n",
			component);
		NL_SET_ERR_MSG_MOD(extack, "Component comparison stamp is invalid");
		अवरोध;
	हाल ICE_AQ_NVM_PASS_COMP_CONFLICT_CODE:
		dev_err(dev, "%s conflicts with a previous component table\n",
			component);
		NL_SET_ERR_MSG_MOD(extack, "Component table conflict occurred");
		अवरोध;
	हाल ICE_AQ_NVM_PASS_COMP_PRE_REQ_NOT_MET_CODE:
		dev_err(dev, "Pre-requisites for component %s have not been met\n",
			component);
		NL_SET_ERR_MSG_MOD(extack, "Component pre-requisites not met");
		अवरोध;
	हाल ICE_AQ_NVM_PASS_COMP_NOT_SUPPORTED_CODE:
		dev_err(dev, "%s is not a supported component\n",
			component);
		NL_SET_ERR_MSG_MOD(extack, "Component not supported");
		अवरोध;
	हाल ICE_AQ_NVM_PASS_COMP_CANNOT_DOWNGRADE_CODE:
		dev_err(dev, "Security restrictions prevent %s from being downgraded\n",
			component);
		NL_SET_ERR_MSG_MOD(extack, "Component cannot be downgraded");
		अवरोध;
	हाल ICE_AQ_NVM_PASS_COMP_INCOMPLETE_IMAGE_CODE:
		dev_err(dev, "Received an incomplete component image for %s\n",
			component);
		NL_SET_ERR_MSG_MOD(extack, "Incomplete component image");
		अवरोध;
	हाल ICE_AQ_NVM_PASS_COMP_VER_STR_IDENTICAL_CODE:
		dev_err(dev, "Component version for %s is identical to the running image\n",
			component);
		NL_SET_ERR_MSG_MOD(extack, "Component version is identical to running image");
		अवरोध;
	हाल ICE_AQ_NVM_PASS_COMP_VER_STR_LOWER_CODE:
		dev_err(dev, "Component version for %s is lower than the running image\n",
			component);
		NL_SET_ERR_MSG_MOD(extack, "Component version is lower than the running image");
		अवरोध;
	शेष:
		dev_err(dev, "Unexpected response code 0x02%x for %s\n",
			code, component);
		NL_SET_ERR_MSG_MOD(extack, "Received unexpected response code from firmware");
		अवरोध;
	पूर्ण

	वापस -ECANCELED;
पूर्ण

/**
 * ice_send_component_table - Send PLDM component table to firmware
 * @context: PLDM fw update काष्ठाure
 * @component: the component to process
 * @transfer_flag: relative transfer order of this component
 *
 * Read relevant data from the component and क्रमward it to the device
 * firmware. Check the response to determine अगर the firmware indicates that
 * the update can proceed.
 *
 * This function sends AdminQ commands related to the NVM, and assumes that
 * the NVM resource has been acquired.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
अटल पूर्णांक
ice_send_component_table(काष्ठा pldmfw *context, काष्ठा pldmfw_component *component,
			 u8 transfer_flag)
अणु
	काष्ठा ice_fwu_priv *priv = container_of(context, काष्ठा ice_fwu_priv, context);
	काष्ठा netlink_ext_ack *extack = priv->extack;
	काष्ठा ice_aqc_nvm_comp_tbl *comp_tbl;
	u8 comp_response, comp_response_code;
	काष्ठा device *dev = context->dev;
	काष्ठा ice_pf *pf = priv->pf;
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	माप_प्रकार length;

	चयन (component->identअगरier) अणु
	हाल NVM_COMP_ID_OROM:
	हाल NVM_COMP_ID_NVM:
	हाल NVM_COMP_ID_NETLIST:
		अवरोध;
	शेष:
		dev_err(dev, "Unable to update due to a firmware component with unknown ID %u\n",
			component->identअगरier);
		NL_SET_ERR_MSG_MOD(extack, "Unable to update due to unknown firmware component");
		वापस -EOPNOTSUPP;
	पूर्ण

	length = काष्ठा_size(comp_tbl, cvs, component->version_len);
	comp_tbl = kzalloc(length, GFP_KERNEL);
	अगर (!comp_tbl)
		वापस -ENOMEM;

	comp_tbl->comp_class = cpu_to_le16(component->classअगरication);
	comp_tbl->comp_id = cpu_to_le16(component->identअगरier);
	comp_tbl->comp_class_idx = FWU_COMP_CLASS_IDX_NOT_USE;
	comp_tbl->comp_cmp_stamp = cpu_to_le32(component->comparison_stamp);
	comp_tbl->cvs_type = component->version_type;
	comp_tbl->cvs_len = component->version_len;
	स_नकल(comp_tbl->cvs, component->version_string, component->version_len);

	dev_dbg(dev, "Sending component table to firmware:\n");

	status = ice_nvm_pass_component_tbl(hw, (u8 *)comp_tbl, length,
					    transfer_flag, &comp_response,
					    &comp_response_code, शून्य);

	kमुक्त(comp_tbl);

	अगर (status) अणु
		dev_err(dev, "Failed to transfer component table to firmware, err %s aq_err %s\n",
			ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		NL_SET_ERR_MSG_MOD(extack, "Failed to transfer component table to firmware");
		वापस -EIO;
	पूर्ण

	वापस ice_check_component_response(pf, component->identअगरier, comp_response,
					    comp_response_code, extack);
पूर्ण

/**
 * ice_ग_लिखो_one_nvm_block - Write an NVM block and aरुको completion response
 * @pf: the PF data काष्ठाure
 * @module: the module to ग_लिखो to
 * @offset: offset in bytes
 * @block_size: size of the block to ग_लिखो, up to 4k
 * @block: poपूर्णांकer to block of data to ग_लिखो
 * @last_cmd: whether this is the last command
 * @extack: netlink extended ACK काष्ठाure
 *
 * Write a block of data to a flash module, and aरुको क्रम the completion
 * response message from firmware.
 *
 * Note this function assumes the caller has acquired the NVM resource.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
अटल पूर्णांक
ice_ग_लिखो_one_nvm_block(काष्ठा ice_pf *pf, u16 module, u32 offset,
			u16 block_size, u8 *block, bool last_cmd,
			काष्ठा netlink_ext_ack *extack)
अणु
	u16 completion_module, completion_retval;
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_rq_event_info event;
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	u32 completion_offset;
	पूर्णांक err;

	स_रखो(&event, 0, माप(event));

	dev_dbg(dev, "Writing block of %u bytes for module 0x%02x at offset %u\n",
		block_size, module, offset);

	status = ice_aq_update_nvm(hw, module, offset, block_size, block,
				   last_cmd, 0, शून्य);
	अगर (status) अणु
		dev_err(dev, "Failed to flash module 0x%02x with block of size %u at offset %u, err %s aq_err %s\n",
			module, block_size, offset, ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		NL_SET_ERR_MSG_MOD(extack, "Failed to program flash module");
		वापस -EIO;
	पूर्ण

	/* In most हालs, firmware reports a ग_लिखो completion within a few
	 * milliseconds. However, it has been observed that a completion might
	 * take more than a second to complete in some हालs. The समयout here
	 * is conservative and is पूर्णांकended to prevent failure to update when
	 * firmware is slow to respond.
	 */
	err = ice_aq_रुको_क्रम_event(pf, ice_aqc_opc_nvm_ग_लिखो, 15 * HZ, &event);
	अगर (err) अणु
		dev_err(dev, "Timed out while trying to flash module 0x%02x with block of size %u at offset %u, err %d\n",
			module, block_size, offset, err);
		NL_SET_ERR_MSG_MOD(extack, "Timed out waiting for firmware");
		वापस -EIO;
	पूर्ण

	completion_module = le16_to_cpu(event.desc.params.nvm.module_typeid);
	completion_retval = le16_to_cpu(event.desc.retval);

	completion_offset = le16_to_cpu(event.desc.params.nvm.offset_low);
	completion_offset |= event.desc.params.nvm.offset_high << 16;

	अगर (completion_module != module) अणु
		dev_err(dev, "Unexpected module_typeid in write completion: got 0x%x, expected 0x%x\n",
			completion_module, module);
		NL_SET_ERR_MSG_MOD(extack, "Unexpected firmware response");
		वापस -EIO;
	पूर्ण

	अगर (completion_offset != offset) अणु
		dev_err(dev, "Unexpected offset in write completion: got %u, expected %u\n",
			completion_offset, offset);
		NL_SET_ERR_MSG_MOD(extack, "Unexpected firmware response");
		वापस -EIO;
	पूर्ण

	अगर (completion_retval) अणु
		dev_err(dev, "Firmware failed to flash module 0x%02x with block of size %u at offset %u, err %s\n",
			module, block_size, offset,
			ice_aq_str((क्रमागत ice_aq_err)completion_retval));
		NL_SET_ERR_MSG_MOD(extack, "Firmware failed to program flash module");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_ग_लिखो_nvm_module - Write data to an NVM module
 * @pf: the PF driver काष्ठाure
 * @module: the module id to program
 * @component: the name of the component being updated
 * @image: buffer of image data to ग_लिखो to the NVM
 * @length: length of the buffer
 * @extack: netlink extended ACK काष्ठाure
 *
 * Loop over the data क्रम a given NVM module and program it in 4 Kb
 * blocks. Notअगरy devlink core of progress after each block is programmed.
 * Loops over a block of data and programs the NVM in 4k block chunks.
 *
 * Note this function assumes the caller has acquired the NVM resource.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
अटल पूर्णांक
ice_ग_लिखो_nvm_module(काष्ठा ice_pf *pf, u16 module, स्थिर अक्षर *component,
		     स्थिर u8 *image, u32 length,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा devlink *devlink;
	u32 offset = 0;
	bool last_cmd;
	u8 *block;
	पूर्णांक err;

	dev_dbg(dev, "Beginning write of flash component '%s', module 0x%02x\n", component, module);

	devlink = priv_to_devlink(pf);

	devlink_flash_update_status_notअगरy(devlink, "Flashing",
					   component, 0, length);

	block = kzalloc(ICE_AQ_MAX_BUF_LEN, GFP_KERNEL);
	अगर (!block)
		वापस -ENOMEM;

	करो अणु
		u32 block_size;

		block_size = min_t(u32, ICE_AQ_MAX_BUF_LEN, length - offset);
		last_cmd = !(offset + block_size < length);

		/* ice_aq_update_nvm may copy the firmware response पूर्णांकo the
		 * buffer, so we must make a copy since the source data is
		 * स्थिरant.
		 */
		स_नकल(block, image + offset, block_size);

		err = ice_ग_लिखो_one_nvm_block(pf, module, offset, block_size,
					      block, last_cmd, extack);
		अगर (err)
			अवरोध;

		offset += block_size;

		devlink_flash_update_status_notअगरy(devlink, "Flashing",
						   component, offset, length);
	पूर्ण जबतक (!last_cmd);

	dev_dbg(dev, "Completed write of flash component '%s', module 0x%02x\n", component, module);

	अगर (err)
		devlink_flash_update_status_notअगरy(devlink, "Flashing failed",
						   component, length, length);
	अन्यथा
		devlink_flash_update_status_notअगरy(devlink, "Flashing done",
						   component, length, length);

	kमुक्त(block);
	वापस err;
पूर्ण

/* Length in seconds to रुको beक्रमe timing out when erasing a flash module.
 * Yes, erasing really can take minutes to complete.
 */
#घोषणा ICE_FW_ERASE_TIMEOUT 300

/**
 * ice_erase_nvm_module - Erase an NVM module and aरुको firmware completion
 * @pf: the PF data काष्ठाure
 * @module: the module to erase
 * @component: name of the component being updated
 * @extack: netlink extended ACK काष्ठाure
 *
 * Erase the inactive NVM bank associated with this module, and aरुको क्रम
 * a completion response message from firmware.
 *
 * Note this function assumes the caller has acquired the NVM resource.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
अटल पूर्णांक
ice_erase_nvm_module(काष्ठा ice_pf *pf, u16 module, स्थिर अक्षर *component,
		     काष्ठा netlink_ext_ack *extack)
अणु
	u16 completion_module, completion_retval;
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_rq_event_info event;
	काष्ठा ice_hw *hw = &pf->hw;
	काष्ठा devlink *devlink;
	क्रमागत ice_status status;
	पूर्णांक err;

	dev_dbg(dev, "Beginning erase of flash component '%s', module 0x%02x\n", component, module);

	स_रखो(&event, 0, माप(event));

	devlink = priv_to_devlink(pf);

	devlink_flash_update_समयout_notअगरy(devlink, "Erasing", component, ICE_FW_ERASE_TIMEOUT);

	status = ice_aq_erase_nvm(hw, module, शून्य);
	अगर (status) अणु
		dev_err(dev, "Failed to erase %s (module 0x%02x), err %s aq_err %s\n",
			component, module, ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		NL_SET_ERR_MSG_MOD(extack, "Failed to erase flash module");
		err = -EIO;
		जाओ out_notअगरy_devlink;
	पूर्ण

	err = ice_aq_रुको_क्रम_event(pf, ice_aqc_opc_nvm_erase, ICE_FW_ERASE_TIMEOUT * HZ, &event);
	अगर (err) अणु
		dev_err(dev, "Timed out waiting for firmware to respond with erase completion for %s (module 0x%02x), err %d\n",
			component, module, err);
		NL_SET_ERR_MSG_MOD(extack, "Timed out waiting for firmware");
		जाओ out_notअगरy_devlink;
	पूर्ण

	completion_module = le16_to_cpu(event.desc.params.nvm.module_typeid);
	completion_retval = le16_to_cpu(event.desc.retval);

	अगर (completion_module != module) अणु
		dev_err(dev, "Unexpected module_typeid in erase completion for %s: got 0x%x, expected 0x%x\n",
			component, completion_module, module);
		NL_SET_ERR_MSG_MOD(extack, "Unexpected firmware response");
		err = -EIO;
		जाओ out_notअगरy_devlink;
	पूर्ण

	अगर (completion_retval) अणु
		dev_err(dev, "Firmware failed to erase %s (module 0x02%x), aq_err %s\n",
			component, module,
			ice_aq_str((क्रमागत ice_aq_err)completion_retval));
		NL_SET_ERR_MSG_MOD(extack, "Firmware failed to erase flash");
		err = -EIO;
		जाओ out_notअगरy_devlink;
	पूर्ण

	dev_dbg(dev, "Completed erase of flash component '%s', module 0x%02x\n", component, module);

out_notअगरy_devlink:
	अगर (err)
		devlink_flash_update_status_notअगरy(devlink, "Erasing failed",
						   component, 0, 0);
	अन्यथा
		devlink_flash_update_status_notअगरy(devlink, "Erasing done",
						   component, 0, 0);

	वापस err;
पूर्ण

/**
 * ice_चयन_flash_banks - Tell firmware to चयन NVM banks
 * @pf: Poपूर्णांकer to the PF data काष्ठाure
 * @activate_flags: flags used क्रम the activation command
 * @extack: netlink extended ACK काष्ठाure
 *
 * Notअगरy firmware to activate the newly written flash banks, and रुको क्रम the
 * firmware response.
 *
 * Returns: zero on success or an error code on failure.
 */
अटल पूर्णांक ice_चयन_flash_banks(काष्ठा ice_pf *pf, u8 activate_flags,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_rq_event_info event;
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	u16 completion_retval;
	पूर्णांक err;

	स_रखो(&event, 0, माप(event));

	status = ice_nvm_ग_लिखो_activate(hw, activate_flags);
	अगर (status) अणु
		dev_err(dev, "Failed to switch active flash banks, err %s aq_err %s\n",
			ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		NL_SET_ERR_MSG_MOD(extack, "Failed to switch active flash banks");
		वापस -EIO;
	पूर्ण

	err = ice_aq_रुको_क्रम_event(pf, ice_aqc_opc_nvm_ग_लिखो_activate, 30 * HZ,
				    &event);
	अगर (err) अणु
		dev_err(dev, "Timed out waiting for firmware to switch active flash banks, err %d\n",
			err);
		NL_SET_ERR_MSG_MOD(extack, "Timed out waiting for firmware");
		वापस err;
	पूर्ण

	completion_retval = le16_to_cpu(event.desc.retval);
	अगर (completion_retval) अणु
		dev_err(dev, "Firmware failed to switch active flash banks aq_err %s\n",
			ice_aq_str((क्रमागत ice_aq_err)completion_retval));
		NL_SET_ERR_MSG_MOD(extack, "Firmware failed to switch active flash banks");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_flash_component - Flash a component of the NVM
 * @context: PLDM fw update काष्ठाure
 * @component: the component table to program
 *
 * Program the flash contents क्रम a given component. First, determine the
 * module id. Then, erase the secondary bank क्रम this module. Finally, ग_लिखो
 * the contents of the component to the NVM.
 *
 * Note this function assumes the caller has acquired the NVM resource.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
अटल पूर्णांक
ice_flash_component(काष्ठा pldmfw *context, काष्ठा pldmfw_component *component)
अणु
	काष्ठा ice_fwu_priv *priv = container_of(context, काष्ठा ice_fwu_priv, context);
	काष्ठा netlink_ext_ack *extack = priv->extack;
	काष्ठा ice_pf *pf = priv->pf;
	स्थिर अक्षर *name;
	u16 module;
	u8 flag;
	पूर्णांक err;

	चयन (component->identअगरier) अणु
	हाल NVM_COMP_ID_OROM:
		module = ICE_SR_1ST_OROM_BANK_PTR;
		flag = ICE_AQC_NVM_ACTIV_SEL_OROM;
		name = "fw.undi";
		अवरोध;
	हाल NVM_COMP_ID_NVM:
		module = ICE_SR_1ST_NVM_BANK_PTR;
		flag = ICE_AQC_NVM_ACTIV_SEL_NVM;
		name = "fw.mgmt";
		अवरोध;
	हाल NVM_COMP_ID_NETLIST:
		module = ICE_SR_NETLIST_BANK_PTR;
		flag = ICE_AQC_NVM_ACTIV_SEL_NETLIST;
		name = "fw.netlist";
		अवरोध;
	शेष:
		/* This should not trigger, since we check the id beक्रमe
		 * sending the component table to firmware.
		 */
		WARN(1, "Unexpected unknown component identifier 0x%02x",
		     component->identअगरier);
		वापस -EINVAL;
	पूर्ण

	/* Mark this component क्रम activating at the end */
	priv->activate_flags |= flag;

	err = ice_erase_nvm_module(pf, module, name, extack);
	अगर (err)
		वापस err;

	वापस ice_ग_लिखो_nvm_module(pf, module, name, component->component_data,
				    component->component_size, extack);
पूर्ण

/**
 * ice_finalize_update - Perक्रमm last steps to complete device update
 * @context: PLDM fw update काष्ठाure
 *
 * Called as the last step of the update process. Complete the update by
 * telling the firmware to चयन active banks, and perक्रमm a reset of
 * configured.
 *
 * Returns: 0 on success, or an error code on failure.
 */
अटल पूर्णांक ice_finalize_update(काष्ठा pldmfw *context)
अणु
	काष्ठा ice_fwu_priv *priv = container_of(context, काष्ठा ice_fwu_priv, context);
	काष्ठा netlink_ext_ack *extack = priv->extack;
	काष्ठा ice_pf *pf = priv->pf;

	/* Finally, notअगरy firmware to activate the written NVM banks */
	वापस ice_चयन_flash_banks(pf, priv->activate_flags, extack);
पूर्ण

अटल स्थिर काष्ठा pldmfw_ops ice_fwu_ops = अणु
	.match_record = &pldmfw_op_pci_match_record,
	.send_package_data = &ice_send_package_data,
	.send_component_table = &ice_send_component_table,
	.flash_component = &ice_flash_component,
	.finalize_update = &ice_finalize_update,
पूर्ण;

/**
 * ice_flash_pldm_image - Write a PLDM-क्रमmatted firmware image to the device
 * @pf: निजी device driver काष्ठाure
 * @fw: firmware object poपूर्णांकing to the relevant firmware file
 * @preservation: preservation level to request from firmware
 * @extack: netlink extended ACK काष्ठाure
 *
 * Parse the data क्रम a given firmware file, verअगरying that it is a valid PLDM
 * क्रमmatted image that matches this device.
 *
 * Extract the device record Package Data and Component Tables and send them
 * to the firmware. Extract and ग_लिखो the flash data क्रम each of the three
 * मुख्य flash components, "fw.mgmt", "fw.undi", and "fw.netlist". Notअगरy
 * firmware once the data is written to the inactive banks.
 *
 * Returns: zero on success or a negative error code on failure.
 */
पूर्णांक ice_flash_pldm_image(काष्ठा ice_pf *pf, स्थिर काष्ठा firmware *fw,
			 u8 preservation, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;
	काष्ठा ice_fwu_priv priv;
	क्रमागत ice_status status;
	पूर्णांक err;

	चयन (preservation) अणु
	हाल ICE_AQC_NVM_PRESERVE_ALL:
	हाल ICE_AQC_NVM_PRESERVE_SELECTED:
	हाल ICE_AQC_NVM_NO_PRESERVATION:
	हाल ICE_AQC_NVM_FACTORY_DEFAULT:
		अवरोध;
	शेष:
		WARN(1, "Unexpected preservation level request %u", preservation);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&priv, 0, माप(priv));

	priv.context.ops = &ice_fwu_ops;
	priv.context.dev = dev;
	priv.extack = extack;
	priv.pf = pf;
	priv.activate_flags = preservation;

	status = ice_acquire_nvm(hw, ICE_RES_WRITE);
	अगर (status) अणु
		dev_err(dev, "Failed to acquire device flash lock, err %s aq_err %s\n",
			ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		NL_SET_ERR_MSG_MOD(extack, "Failed to acquire device flash lock");
		वापस -EIO;
	पूर्ण

	err = pldmfw_flash_image(&priv.context, fw);

	ice_release_nvm(hw);

	वापस err;
पूर्ण

/**
 * ice_check_क्रम_pending_update - Check क्रम a pending flash update
 * @pf: the PF driver काष्ठाure
 * @component: अगर not शून्य, the name of the component being updated
 * @extack: Netlink extended ACK काष्ठाure
 *
 * Check whether the device alपढ़ोy has a pending flash update. If such an
 * update is found, cancel it so that the requested update may proceed.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
पूर्णांक ice_check_क्रम_pending_update(काष्ठा ice_pf *pf, स्थिर अक्षर *component,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(pf);
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw_dev_caps *dev_caps;
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	u8 pending = 0;
	पूर्णांक err;

	dev_caps = kzalloc(माप(*dev_caps), GFP_KERNEL);
	अगर (!dev_caps)
		वापस -ENOMEM;

	/* Read the most recent device capabilities from firmware. Do not use
	 * the cached values in hw->dev_caps, because the pending update flag
	 * may have changed, e.g. अगर an update was previously completed and
	 * the प्रणाली has not yet rebooted.
	 */
	status = ice_discover_dev_caps(hw, dev_caps);
	अगर (status) अणु
		NL_SET_ERR_MSG_MOD(extack, "Unable to read device capabilities");
		kमुक्त(dev_caps);
		वापस -EIO;
	पूर्ण

	अगर (dev_caps->common_cap.nvm_update_pending_nvm) अणु
		dev_info(dev, "The fw.mgmt flash component has a pending update\n");
		pending |= ICE_AQC_NVM_ACTIV_SEL_NVM;
	पूर्ण

	अगर (dev_caps->common_cap.nvm_update_pending_orom) अणु
		dev_info(dev, "The fw.undi flash component has a pending update\n");
		pending |= ICE_AQC_NVM_ACTIV_SEL_OROM;
	पूर्ण

	अगर (dev_caps->common_cap.nvm_update_pending_netlist) अणु
		dev_info(dev, "The fw.netlist flash component has a pending update\n");
		pending |= ICE_AQC_NVM_ACTIV_SEL_NETLIST;
	पूर्ण

	kमुक्त(dev_caps);

	/* If the flash_update request is क्रम a specअगरic component, ignore all
	 * of the other components.
	 */
	अगर (component) अणु
		अगर (म_भेद(component, "fw.mgmt") == 0)
			pending &= ICE_AQC_NVM_ACTIV_SEL_NVM;
		अन्यथा अगर (म_भेद(component, "fw.undi") == 0)
			pending &= ICE_AQC_NVM_ACTIV_SEL_OROM;
		अन्यथा अगर (म_भेद(component, "fw.netlist") == 0)
			pending &= ICE_AQC_NVM_ACTIV_SEL_NETLIST;
		अन्यथा
			WARN(1, "Unexpected flash component %s", component);
	पूर्ण

	/* There is no previous pending update, so this request may जारी */
	अगर (!pending)
		वापस 0;

	/* In order to allow overwriting a previous pending update, notअगरy
	 * firmware to cancel that update by issuing the appropriate command.
	 */
	devlink_flash_update_status_notअगरy(devlink,
					   "Canceling previous pending update",
					   component, 0, 0);

	status = ice_acquire_nvm(hw, ICE_RES_WRITE);
	अगर (status) अणु
		dev_err(dev, "Failed to acquire device flash lock, err %s aq_err %s\n",
			ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		NL_SET_ERR_MSG_MOD(extack, "Failed to acquire device flash lock");
		वापस -EIO;
	पूर्ण

	pending |= ICE_AQC_NVM_REVERT_LAST_ACTIV;
	err = ice_चयन_flash_banks(pf, pending, extack);

	ice_release_nvm(hw);

	वापस err;
पूर्ण
