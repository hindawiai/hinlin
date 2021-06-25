<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * क्रम more details.
 *
 */
#समावेश <linux/netlink.h>
#समावेश <net/devlink.h>
#समावेश <linux/firmware.h>

#समावेश "hinic_port.h"
#समावेश "hinic_devlink.h"
#समावेश "hinic_hw_dev.h"

अटल bool check_image_valid(काष्ठा hinic_devlink_priv *priv, स्थिर u8 *buf,
			      u32 image_size, काष्ठा host_image_st *host_image)
अणु
	काष्ठा fw_image_st *fw_image = शून्य;
	u32 len = 0;
	u32 i;

	fw_image = (काष्ठा fw_image_st *)buf;

	अगर (fw_image->fw_magic != HINIC_MAGIC_NUM) अणु
		dev_err(&priv->hwdev->hwअगर->pdev->dev, "Wrong fw_magic read from file, fw_magic: 0x%x\n",
			fw_image->fw_magic);
		वापस false;
	पूर्ण

	अगर (fw_image->fw_info.fw_section_cnt > MAX_FW_TYPE_NUM) अणु
		dev_err(&priv->hwdev->hwअगर->pdev->dev, "Wrong fw_type_num read from file, fw_type_num: 0x%x\n",
			fw_image->fw_info.fw_section_cnt);
		वापस false;
	पूर्ण

	क्रम (i = 0; i < fw_image->fw_info.fw_section_cnt; i++) अणु
		len += fw_image->fw_section_info[i].fw_section_len;
		स_नकल(&host_image->image_section_info[i],
		       &fw_image->fw_section_info[i],
		       माप(काष्ठा fw_section_info_st));
	पूर्ण

	अगर (len != fw_image->fw_len ||
	    (fw_image->fw_len + UPDATEFW_IMAGE_HEAD_SIZE) != image_size) अणु
		dev_err(&priv->hwdev->hwअगर->pdev->dev, "Wrong data size read from file\n");
		वापस false;
	पूर्ण

	host_image->image_info.up_total_len = fw_image->fw_len;
	host_image->image_info.fw_version = fw_image->fw_version;
	host_image->section_type_num = fw_image->fw_info.fw_section_cnt;
	host_image->device_id = fw_image->device_id;

	वापस true;
पूर्ण

अटल bool check_image_पूर्णांकegrity(काष्ठा hinic_devlink_priv *priv,
				  काष्ठा host_image_st *host_image,
				  u32 update_type)
अणु
	u32 collect_section_type = 0;
	u32 i, type;

	क्रम (i = 0; i < host_image->section_type_num; i++) अणु
		type = host_image->image_section_info[i].fw_section_type;
		अगर (collect_section_type & (1U << type)) अणु
			dev_err(&priv->hwdev->hwअगर->pdev->dev, "Duplicate section type: %u\n",
				type);
			वापस false;
		पूर्ण
		collect_section_type |= (1U << type);
	पूर्ण

	अगर (update_type == FW_UPDATE_COLD &&
	    (((collect_section_type & _IMAGE_COLD_SUB_MODULES_MUST_IN) ==
	       _IMAGE_COLD_SUB_MODULES_MUST_IN) ||
	      collect_section_type == _IMAGE_CFG_SUB_MODULES_MUST_IN))
		वापस true;

	अगर (update_type == FW_UPDATE_HOT &&
	    (collect_section_type & _IMAGE_HOT_SUB_MODULES_MUST_IN) ==
	    _IMAGE_HOT_SUB_MODULES_MUST_IN)
		वापस true;

	अगर (update_type == FW_UPDATE_COLD)
		dev_err(&priv->hwdev->hwअगर->pdev->dev, "Check file integrity failed, valid: 0x%x or 0x%lx, current: 0x%x\n",
			_IMAGE_COLD_SUB_MODULES_MUST_IN,
			_IMAGE_CFG_SUB_MODULES_MUST_IN, collect_section_type);
	अन्यथा
		dev_err(&priv->hwdev->hwअगर->pdev->dev, "Check file integrity failed, valid:0x%x, current: 0x%x\n",
			_IMAGE_HOT_SUB_MODULES_MUST_IN, collect_section_type);

	वापस false;
पूर्ण

अटल पूर्णांक check_image_device_type(काष्ठा hinic_devlink_priv *priv,
				   u32 image_device_type)
अणु
	काष्ठा hinic_comm_board_info board_info = अणु0पूर्ण;

	अगर (hinic_get_board_info(priv->hwdev, &board_info)) अणु
		dev_err(&priv->hwdev->hwअगर->pdev->dev, "Get board info failed\n");
		वापस false;
	पूर्ण

	अगर (image_device_type == board_info.info.board_type)
		वापस true;

	dev_err(&priv->hwdev->hwअगर->pdev->dev, "The device type of upgrade file doesn't match the device type of current firmware, please check the upgrade file\n");
	dev_err(&priv->hwdev->hwअगर->pdev->dev, "The image device type: 0x%x, firmware device type: 0x%x\n",
		image_device_type, board_info.info.board_type);

	वापस false;
पूर्ण

अटल पूर्णांक hinic_flash_fw(काष्ठा hinic_devlink_priv *priv, स्थिर u8 *data,
			  काष्ठा host_image_st *host_image)
अणु
	u32 section_reमुख्य_send_len, send_fragment_len, send_pos, up_total_len;
	काष्ठा hinic_cmd_update_fw *fw_update_msg = शून्य;
	u32 section_type, section_crc, section_version;
	u32 i, len, section_len, section_offset;
	u16 out_size = माप(*fw_update_msg);
	पूर्णांक total_len_flag = 0;
	पूर्णांक err;

	fw_update_msg = kzalloc(माप(*fw_update_msg), GFP_KERNEL);
	अगर (!fw_update_msg)
		वापस -ENOMEM;

	up_total_len = host_image->image_info.up_total_len;

	क्रम (i = 0; i < host_image->section_type_num; i++) अणु
		len = host_image->image_section_info[i].fw_section_len;
		अगर (host_image->image_section_info[i].fw_section_type ==
		    UP_FW_UPDATE_BOOT) अणु
			up_total_len = up_total_len - len;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < host_image->section_type_num; i++) अणु
		section_len =
			host_image->image_section_info[i].fw_section_len;
		section_offset =
			host_image->image_section_info[i].fw_section_offset;
		section_reमुख्य_send_len = section_len;
		section_type =
			host_image->image_section_info[i].fw_section_type;
		section_crc = host_image->image_section_info[i].fw_section_crc;
		section_version =
			host_image->image_section_info[i].fw_section_version;

		अगर (section_type == UP_FW_UPDATE_BOOT)
			जारी;

		send_fragment_len = 0;
		send_pos = 0;

		जबतक (section_reमुख्य_send_len > 0) अणु
			अगर (!total_len_flag) अणु
				fw_update_msg->total_len = up_total_len;
				total_len_flag = 1;
			पूर्ण अन्यथा अणु
				fw_update_msg->total_len = 0;
			पूर्ण

			स_रखो(fw_update_msg->data, 0, MAX_FW_FRAGMENT_LEN);

			fw_update_msg->ctl_info.SF =
				(section_reमुख्य_send_len == section_len) ?
				true : false;
			fw_update_msg->section_info.FW_section_CRC = section_crc;
			fw_update_msg->fw_section_version = section_version;
			fw_update_msg->ctl_info.flag = UP_TYPE_A;

			अगर (section_type <= UP_FW_UPDATE_UP_DATA_B) अणु
				fw_update_msg->section_info.FW_section_type =
					(section_type % 2) ?
					UP_FW_UPDATE_UP_DATA :
					UP_FW_UPDATE_UP_TEXT;

				fw_update_msg->ctl_info.flag = UP_TYPE_B;
				अगर (section_type <= UP_FW_UPDATE_UP_DATA_A)
					fw_update_msg->ctl_info.flag = UP_TYPE_A;
			पूर्ण अन्यथा अणु
				fw_update_msg->section_info.FW_section_type =
					section_type - 0x2;
			पूर्ण

			fw_update_msg->setion_total_len = section_len;
			fw_update_msg->section_offset = send_pos;

			अगर (section_reमुख्य_send_len <= MAX_FW_FRAGMENT_LEN) अणु
				fw_update_msg->ctl_info.SL = true;
				fw_update_msg->ctl_info.fragment_len =
					section_reमुख्य_send_len;
				send_fragment_len += section_reमुख्य_send_len;
			पूर्ण अन्यथा अणु
				fw_update_msg->ctl_info.SL = false;
				fw_update_msg->ctl_info.fragment_len =
					MAX_FW_FRAGMENT_LEN;
				send_fragment_len += MAX_FW_FRAGMENT_LEN;
			पूर्ण

			स_नकल(fw_update_msg->data,
			       data + UPDATEFW_IMAGE_HEAD_SIZE +
			       section_offset + send_pos,
			       fw_update_msg->ctl_info.fragment_len);

			err = hinic_port_msg_cmd(priv->hwdev,
						 HINIC_PORT_CMD_UPDATE_FW,
						 fw_update_msg,
						 माप(*fw_update_msg),
						 fw_update_msg, &out_size);
			अगर (err || !out_size || fw_update_msg->status) अणु
				dev_err(&priv->hwdev->hwअगर->pdev->dev, "Failed to update firmware, err: %d, status: 0x%x, out size: 0x%x\n",
					err, fw_update_msg->status, out_size);
				err = fw_update_msg->status ?
					fw_update_msg->status : -EIO;
				kमुक्त(fw_update_msg);
				वापस err;
			पूर्ण

			send_pos = send_fragment_len;
			section_reमुख्य_send_len = section_len -
						  send_fragment_len;
		पूर्ण
	पूर्ण

	kमुक्त(fw_update_msg);

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_firmware_update(काष्ठा hinic_devlink_priv *priv,
				 स्थिर काष्ठा firmware *fw,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा host_image_st host_image;
	पूर्णांक err;

	स_रखो(&host_image, 0, माप(काष्ठा host_image_st));

	अगर (!check_image_valid(priv, fw->data, fw->size, &host_image) ||
	    !check_image_पूर्णांकegrity(priv, &host_image, FW_UPDATE_COLD) ||
	    !check_image_device_type(priv, host_image.device_id)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Check image failed");
		वापस -EINVAL;
	पूर्ण

	dev_info(&priv->hwdev->hwअगर->pdev->dev, "Flash firmware begin\n");

	err = hinic_flash_fw(priv, fw->data, &host_image);
	अगर (err) अणु
		अगर (err == HINIC_FW_DISMATCH_ERROR) अणु
			dev_err(&priv->hwdev->hwअगर->pdev->dev, "Firmware image doesn't match this card, please use newer image, err: %d\n",
				err);
			NL_SET_ERR_MSG_MOD(extack,
					   "Firmware image doesn't match this card, please use newer image");
		पूर्ण अन्यथा अणु
			dev_err(&priv->hwdev->hwअगर->pdev->dev, "Send firmware image data failed, err: %d\n",
				err);
			NL_SET_ERR_MSG_MOD(extack, "Send firmware image data failed");
		पूर्ण

		वापस err;
	पूर्ण

	dev_info(&priv->hwdev->hwअगर->pdev->dev, "Flash firmware end\n");

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_devlink_flash_update(काष्ठा devlink *devlink,
				      काष्ठा devlink_flash_update_params *params,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा hinic_devlink_priv *priv = devlink_priv(devlink);

	वापस hinic_firmware_update(priv, params->fw, extack);
पूर्ण

अटल स्थिर काष्ठा devlink_ops hinic_devlink_ops = अणु
	.flash_update = hinic_devlink_flash_update,
पूर्ण;

काष्ठा devlink *hinic_devlink_alloc(व्योम)
अणु
	वापस devlink_alloc(&hinic_devlink_ops, माप(काष्ठा hinic_dev));
पूर्ण

व्योम hinic_devlink_मुक्त(काष्ठा devlink *devlink)
अणु
	devlink_मुक्त(devlink);
पूर्ण

पूर्णांक hinic_devlink_रेजिस्टर(काष्ठा hinic_devlink_priv *priv, काष्ठा device *dev)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(priv);

	वापस devlink_रेजिस्टर(devlink, dev);
पूर्ण

व्योम hinic_devlink_unरेजिस्टर(काष्ठा hinic_devlink_priv *priv)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(priv);

	devlink_unरेजिस्टर(devlink);
पूर्ण

अटल पूर्णांक chip_fault_show(काष्ठा devlink_fmsg *fmsg,
			   काष्ठा hinic_fault_event *event)
अणु
	स्थिर अक्षर * स्थिर level_str[FAULT_LEVEL_MAX + 1] = अणु
		"fatal", "reset", "flr", "general", "suggestion", "Unknown"पूर्ण;
	u8 fault_level;
	पूर्णांक err;

	fault_level = (event->event.chip.err_level < FAULT_LEVEL_MAX) ?
		event->event.chip.err_level : FAULT_LEVEL_MAX;
	अगर (fault_level == FAULT_LEVEL_SERIOUS_FLR) अणु
		err = devlink_fmsg_u32_pair_put(fmsg, "Function level err func_id",
						(u32)event->event.chip.func_id);
		अगर (err)
			वापस err;
	पूर्ण

	err = devlink_fmsg_u8_pair_put(fmsg, "module_id", event->event.chip.node_id);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "err_type", (u32)event->event.chip.err_type);
	अगर (err)
		वापस err;

	err = devlink_fmsg_string_pair_put(fmsg, "err_level", level_str[fault_level]);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "err_csr_addr",
					event->event.chip.err_csr_addr);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "err_csr_value",
					event->event.chip.err_csr_value);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक fault_report_show(काष्ठा devlink_fmsg *fmsg,
			     काष्ठा hinic_fault_event *event)
अणु
	स्थिर अक्षर * स्थिर type_str[FAULT_TYPE_MAX + 1] = अणु
		"chip", "ucode", "mem rd timeout", "mem wr timeout",
		"reg rd timeout", "reg wr timeout", "phy fault", "Unknown"पूर्ण;
	u8 fault_type;
	पूर्णांक err;

	fault_type = (event->type < FAULT_TYPE_MAX) ? event->type : FAULT_TYPE_MAX;

	err = devlink_fmsg_string_pair_put(fmsg, "Fault type", type_str[fault_type]);
	अगर (err)
		वापस err;

	err = devlink_fmsg_binary_pair_put(fmsg, "Fault raw data",
					   event->event.val, माप(event->event.val));
	अगर (err)
		वापस err;

	चयन (event->type) अणु
	हाल FAULT_TYPE_CHIP:
		err = chip_fault_show(fmsg, event);
		अगर (err)
			वापस err;
		अवरोध;
	हाल FAULT_TYPE_UCODE:
		err = devlink_fmsg_u8_pair_put(fmsg, "Cause_id", event->event.ucode.cause_id);
		अगर (err)
			वापस err;
		err = devlink_fmsg_u8_pair_put(fmsg, "core_id", event->event.ucode.core_id);
		अगर (err)
			वापस err;
		err = devlink_fmsg_u8_pair_put(fmsg, "c_id", event->event.ucode.c_id);
		अगर (err)
			वापस err;
		err = devlink_fmsg_u8_pair_put(fmsg, "epc", event->event.ucode.epc);
		अगर (err)
			वापस err;
		अवरोध;
	हाल FAULT_TYPE_MEM_RD_TIMEOUT:
	हाल FAULT_TYPE_MEM_WR_TIMEOUT:
		err = devlink_fmsg_u32_pair_put(fmsg, "Err_csr_ctrl",
						event->event.mem_समयout.err_csr_ctrl);
		अगर (err)
			वापस err;
		err = devlink_fmsg_u32_pair_put(fmsg, "err_csr_data",
						event->event.mem_समयout.err_csr_data);
		अगर (err)
			वापस err;
		err = devlink_fmsg_u32_pair_put(fmsg, "ctrl_tab",
						event->event.mem_समयout.ctrl_tab);
		अगर (err)
			वापस err;
		err = devlink_fmsg_u32_pair_put(fmsg, "mem_index",
						event->event.mem_समयout.mem_index);
		अगर (err)
			वापस err;
		अवरोध;
	हाल FAULT_TYPE_REG_RD_TIMEOUT:
	हाल FAULT_TYPE_REG_WR_TIMEOUT:
		err = devlink_fmsg_u32_pair_put(fmsg, "Err_csr", event->event.reg_समयout.err_csr);
		अगर (err)
			वापस err;
		अवरोध;
	हाल FAULT_TYPE_PHY_FAULT:
		err = devlink_fmsg_u8_pair_put(fmsg, "Op_type", event->event.phy_fault.op_type);
		अगर (err)
			वापस err;
		err = devlink_fmsg_u8_pair_put(fmsg, "port_id", event->event.phy_fault.port_id);
		अगर (err)
			वापस err;
		err = devlink_fmsg_u8_pair_put(fmsg, "dev_ad", event->event.phy_fault.dev_ad);
		अगर (err)
			वापस err;

		err = devlink_fmsg_u32_pair_put(fmsg, "csr_addr", event->event.phy_fault.csr_addr);
		अगर (err)
			वापस err;
		err = devlink_fmsg_u32_pair_put(fmsg, "op_data", event->event.phy_fault.op_data);
		अगर (err)
			वापस err;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_hw_reporter_dump(काष्ठा devlink_health_reporter *reporter,
				  काष्ठा devlink_fmsg *fmsg, व्योम *priv_ctx,
				  काष्ठा netlink_ext_ack *extack)
अणु
	अगर (priv_ctx)
		वापस fault_report_show(fmsg, priv_ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक mgmt_watchकरोg_report_show(काष्ठा devlink_fmsg *fmsg,
				     काष्ठा hinic_mgmt_watchकरोg_info *watchकरोg_info)
अणु
	पूर्णांक err;

	err = devlink_fmsg_u32_pair_put(fmsg, "Mgmt deadloop time_h", watchकरोg_info->curr_समय_h);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "time_l", watchकरोg_info->curr_समय_l);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "task_id", watchकरोg_info->task_id);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "sp", watchकरोg_info->sp);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "stack_current_used", watchकरोg_info->curr_used);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "peak_used", watchकरोg_info->peak_used);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "\n Overflow_flag", watchकरोg_info->is_overflow);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "stack_top", watchकरोg_info->stack_top);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "stack_bottom", watchकरोg_info->stack_bottom);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "mgmt_pc", watchकरोg_info->pc);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "lr", watchकरोg_info->lr);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u32_pair_put(fmsg, "cpsr", watchकरोg_info->cpsr);
	अगर (err)
		वापस err;

	err = devlink_fmsg_binary_pair_put(fmsg, "Mgmt register info",
					   watchकरोg_info->reg, माप(watchकरोg_info->reg));
	अगर (err)
		वापस err;

	err = devlink_fmsg_binary_pair_put(fmsg, "Mgmt dump stack(start from sp)",
					   watchकरोg_info->data, माप(watchकरोg_info->data));
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_fw_reporter_dump(काष्ठा devlink_health_reporter *reporter,
				  काष्ठा devlink_fmsg *fmsg, व्योम *priv_ctx,
				  काष्ठा netlink_ext_ack *extack)
अणु
	अगर (priv_ctx)
		वापस mgmt_watchकरोg_report_show(fmsg, priv_ctx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devlink_health_reporter_ops hinic_hw_fault_reporter_ops = अणु
	.name = "hw",
	.dump = hinic_hw_reporter_dump,
पूर्ण;

अटल स्थिर काष्ठा devlink_health_reporter_ops hinic_fw_fault_reporter_ops = अणु
	.name = "fw",
	.dump = hinic_fw_reporter_dump,
पूर्ण;

पूर्णांक hinic_health_reporters_create(काष्ठा hinic_devlink_priv *priv)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(priv);

	priv->hw_fault_reporter =
		devlink_health_reporter_create(devlink, &hinic_hw_fault_reporter_ops,
					       0, priv);
	अगर (IS_ERR(priv->hw_fault_reporter)) अणु
		dev_warn(&priv->hwdev->hwअगर->pdev->dev, "Failed to create hw fault reporter, err: %ld\n",
			 PTR_ERR(priv->hw_fault_reporter));
		वापस PTR_ERR(priv->hw_fault_reporter);
	पूर्ण

	priv->fw_fault_reporter =
		devlink_health_reporter_create(devlink, &hinic_fw_fault_reporter_ops,
					       0, priv);
	अगर (IS_ERR(priv->fw_fault_reporter)) अणु
		dev_warn(&priv->hwdev->hwअगर->pdev->dev, "Failed to create fw fault reporter, err: %ld\n",
			 PTR_ERR(priv->fw_fault_reporter));
		devlink_health_reporter_destroy(priv->hw_fault_reporter);
		priv->hw_fault_reporter = शून्य;
		वापस PTR_ERR(priv->fw_fault_reporter);
	पूर्ण

	वापस 0;
पूर्ण

व्योम hinic_health_reporters_destroy(काष्ठा hinic_devlink_priv *priv)
अणु
	अगर (!IS_ERR_OR_शून्य(priv->fw_fault_reporter)) अणु
		devlink_health_reporter_destroy(priv->fw_fault_reporter);
		priv->fw_fault_reporter = शून्य;
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(priv->hw_fault_reporter)) अणु
		devlink_health_reporter_destroy(priv->hw_fault_reporter);
		priv->hw_fault_reporter = शून्य;
	पूर्ण
पूर्ण
