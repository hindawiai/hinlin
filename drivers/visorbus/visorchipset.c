<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2010 - 2015 UNISYS CORPORATION
 * All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/visorbus.h>

#समावेश "visorbus_private.h"

/* अणु72120008-4AAB-11DC-8530-444553544200पूर्ण */
#घोषणा VISOR_SIOVM_GUID GUID_INIT(0x72120008, 0x4AAB, 0x11DC, 0x85, 0x30, \
				   0x44, 0x45, 0x53, 0x54, 0x42, 0x00)

अटल स्थिर guid_t visor_vhba_channel_guid = VISOR_VHBA_CHANNEL_GUID;
अटल स्थिर guid_t visor_siovm_guid = VISOR_SIOVM_GUID;
अटल स्थिर guid_t visor_controlvm_channel_guid = VISOR_CONTROLVM_CHANNEL_GUID;

#घोषणा POLLJIFFIES_CONTROLVM_FAST 1
#घोषणा POLLJIFFIES_CONTROLVM_SLOW 100

#घोषणा MAX_CONTROLVM_PAYLOAD_BYTES (1024 * 128)

#घोषणा UNISYS_VISOR_LEAF_ID 0x40000000

/* The s-Par leaf ID वापसs "UnisysSpar64" encoded across ebx, ecx, edx */
#घोषणा UNISYS_VISOR_ID_EBX 0x73696e55
#घोषणा UNISYS_VISOR_ID_ECX 0x70537379
#घोषणा UNISYS_VISOR_ID_EDX 0x34367261

/*
 * When the controlvm channel is idle क्रम at least MIN_IDLE_SECONDS, we चयन
 * to slow polling mode. As soon as we get a controlvm message, we चयन back
 * to fast polling mode.
 */
#घोषणा MIN_IDLE_SECONDS 10

काष्ठा parser_context अणु
	अचिन्हित दीर्घ allocbytes;
	अचिन्हित दीर्घ param_bytes;
	u8 *curr;
	अचिन्हित दीर्घ bytes_reमुख्यing;
	bool byte_stream;
	काष्ठा visor_controlvm_parameters_header data;
पूर्ण;

/* VMCALL_CONTROLVM_ADDR: Used by all guests, not just IO. */
#घोषणा VMCALL_CONTROLVM_ADDR 0x0501

क्रमागत vmcall_result अणु
	VMCALL_RESULT_SUCCESS = 0,
	VMCALL_RESULT_INVALID_PARAM = 1,
	VMCALL_RESULT_DATA_UNAVAILABLE = 2,
	VMCALL_RESULT_FAILURE_UNAVAILABLE = 3,
	VMCALL_RESULT_DEVICE_ERROR = 4,
	VMCALL_RESULT_DEVICE_NOT_READY = 5
पूर्ण;

/*
 * काष्ठा vmcall_io_controlvm_addr_params - Structure क्रम IO VMCALLS. Has
 *					    parameters to VMCALL_CONTROLVM_ADDR
 *					    पूर्णांकerface.
 * @address:	   The Guest-relative physical address of the ControlVm channel.
 *		   This VMCall fills this in with the appropriate address.
 *		   Contents provided by this VMCALL (OUT).
 * @channel_bytes: The size of the ControlVm channel in bytes This VMCall fills
 *		   this in with the appropriate address. Contents provided by
 *		   this VMCALL (OUT).
 * @unused:	   Unused Bytes in the 64-Bit Aligned Struct.
 */
काष्ठा vmcall_io_controlvm_addr_params अणु
	u64 address;
	u32 channel_bytes;
	u8 unused[4];
पूर्ण __packed;

काष्ठा visorchipset_device अणु
	काष्ठा acpi_device *acpi_device;
	अचिन्हित दीर्घ poll_jअगरfies;
	/* when we got our last controlvm message */
	अचिन्हित दीर्घ most_recent_message_jअगरfies;
	काष्ठा delayed_work periodic_controlvm_work;
	काष्ठा visorchannel *controlvm_channel;
	अचिन्हित दीर्घ controlvm_payload_bytes_buffered;
	/*
	 * The following variables are used to handle the scenario where we are
	 * unable to offload the payload from a controlvm message due to memory
	 * requirements. In this scenario, we simply stash the controlvm
	 * message, then attempt to process it again the next समय
	 * controlvm_periodic_work() runs.
	 */
	काष्ठा controlvm_message controlvm_pending_msg;
	bool controlvm_pending_msg_valid;
	काष्ठा vmcall_io_controlvm_addr_params controlvm_params;
पूर्ण;

अटल काष्ठा visorchipset_device *chipset_dev;

काष्ठा parahotplug_request अणु
	काष्ठा list_head list;
	पूर्णांक id;
	अचिन्हित दीर्घ expiration;
	काष्ठा controlvm_message msg;
पूर्ण;

/* prototypes क्रम attributes */
अटल sमाप_प्रकार toolaction_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	u8 tool_action = 0;
	पूर्णांक err;

	err = visorchannel_पढ़ो(chipset_dev->controlvm_channel,
				दुरत्व(काष्ठा visor_controlvm_channel,
					 tool_action),
				&tool_action, माप(u8));
	अगर (err)
		वापस err;
	वापस प्र_लिखो(buf, "%u\n", tool_action);
पूर्ण

अटल sमाप_प्रकार toolaction_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u8 tool_action;
	पूर्णांक err;

	अगर (kstrtou8(buf, 10, &tool_action))
		वापस -EINVAL;
	err = visorchannel_ग_लिखो(chipset_dev->controlvm_channel,
				 दुरत्व(काष्ठा visor_controlvm_channel,
					  tool_action),
				 &tool_action, माप(u8));
	अगर (err)
		वापस err;
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(toolaction);

अटल sमाप_प्रकार boottotool_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा efi_visor_indication efi_visor_indication;
	पूर्णांक err;

	err = visorchannel_पढ़ो(chipset_dev->controlvm_channel,
				दुरत्व(काष्ठा visor_controlvm_channel,
					 efi_visor_ind),
				&efi_visor_indication,
				माप(काष्ठा efi_visor_indication));
	अगर (err)
		वापस err;
	वापस प्र_लिखो(buf, "%u\n", efi_visor_indication.boot_to_tool);
पूर्ण

अटल sमाप_प्रकार boottotool_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक val, err;
	काष्ठा efi_visor_indication efi_visor_indication;

	अगर (kstrtoपूर्णांक(buf, 10, &val))
		वापस -EINVAL;
	efi_visor_indication.boot_to_tool = val;
	err = visorchannel_ग_लिखो(chipset_dev->controlvm_channel,
				 दुरत्व(काष्ठा visor_controlvm_channel,
					  efi_visor_ind),
				 &(efi_visor_indication),
				 माप(काष्ठा efi_visor_indication));
	अगर (err)
		वापस err;
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(boottotool);

अटल sमाप_प्रकार error_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	u32 error = 0;
	पूर्णांक err;

	err = visorchannel_पढ़ो(chipset_dev->controlvm_channel,
				दुरत्व(काष्ठा visor_controlvm_channel,
					 installation_error),
				&error, माप(u32));
	अगर (err)
		वापस err;
	वापस प्र_लिखो(buf, "%u\n", error);
पूर्ण

अटल sमाप_प्रकार error_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 error;
	पूर्णांक err;

	अगर (kstrtou32(buf, 10, &error))
		वापस -EINVAL;
	err = visorchannel_ग_लिखो(chipset_dev->controlvm_channel,
				 दुरत्व(काष्ठा visor_controlvm_channel,
					  installation_error),
				 &error, माप(u32));
	अगर (err)
		वापस err;
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(error);

अटल sमाप_प्रकार textid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	u32 text_id = 0;
	पूर्णांक err;

	err = visorchannel_पढ़ो(chipset_dev->controlvm_channel,
				दुरत्व(काष्ठा visor_controlvm_channel,
					 installation_text_id),
				&text_id, माप(u32));
	अगर (err)
		वापस err;
	वापस प्र_लिखो(buf, "%u\n", text_id);
पूर्ण

अटल sमाप_प्रकार textid_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 text_id;
	पूर्णांक err;

	अगर (kstrtou32(buf, 10, &text_id))
		वापस -EINVAL;
	err = visorchannel_ग_लिखो(chipset_dev->controlvm_channel,
				 दुरत्व(काष्ठा visor_controlvm_channel,
					  installation_text_id),
				 &text_id, माप(u32));
	अगर (err)
		वापस err;
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(textid);

अटल sमाप_प्रकार reमुख्यing_steps_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u16 reमुख्यing_steps = 0;
	पूर्णांक err;

	err = visorchannel_पढ़ो(chipset_dev->controlvm_channel,
				दुरत्व(काष्ठा visor_controlvm_channel,
					 installation_reमुख्यing_steps),
				&reमुख्यing_steps, माप(u16));
	अगर (err)
		वापस err;
	वापस प्र_लिखो(buf, "%hu\n", reमुख्यing_steps);
पूर्ण

अटल sमाप_प्रकार reमुख्यing_steps_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u16 reमुख्यing_steps;
	पूर्णांक err;

	अगर (kstrtou16(buf, 10, &reमुख्यing_steps))
		वापस -EINVAL;
	err = visorchannel_ग_लिखो(chipset_dev->controlvm_channel,
				 दुरत्व(काष्ठा visor_controlvm_channel,
					  installation_reमुख्यing_steps),
				 &reमुख्यing_steps, माप(u16));
	अगर (err)
		वापस err;
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(reमुख्यing_steps);

अटल व्योम controlvm_init_response(काष्ठा controlvm_message *msg,
				    काष्ठा controlvm_message_header *msg_hdr,
				    पूर्णांक response)
अणु
	स_रखो(msg, 0, माप(काष्ठा controlvm_message));
	स_नकल(&msg->hdr, msg_hdr, माप(काष्ठा controlvm_message_header));
	msg->hdr.payload_bytes = 0;
	msg->hdr.payload_vm_offset = 0;
	msg->hdr.payload_max_bytes = 0;
	अगर (response < 0) अणु
		msg->hdr.flags.failed = 1;
		msg->hdr.completion_status = (u32)(-response);
	पूर्ण
पूर्ण

अटल पूर्णांक controlvm_respond_chipset_init(
				काष्ठा controlvm_message_header *msg_hdr,
				पूर्णांक response,
				क्रमागत visor_chipset_feature features)
अणु
	काष्ठा controlvm_message ouपंचांगsg;

	controlvm_init_response(&ouपंचांगsg, msg_hdr, response);
	ouपंचांगsg.cmd.init_chipset.features = features;
	वापस visorchannel_संकेतinsert(chipset_dev->controlvm_channel,
					 CONTROLVM_QUEUE_REQUEST, &ouपंचांगsg);
पूर्ण

अटल पूर्णांक chipset_init(काष्ठा controlvm_message *inmsg)
अणु
	अटल पूर्णांक chipset_inited;
	क्रमागत visor_chipset_feature features = 0;
	पूर्णांक rc = CONTROLVM_RESP_SUCCESS;
	पूर्णांक res = 0;

	अगर (chipset_inited) अणु
		rc = -CONTROLVM_RESP_ALREADY_DONE;
		res = -EIO;
		जाओ out_respond;
	पूर्ण
	chipset_inited = 1;
	/*
	 * Set features to indicate we support parahotplug (अगर Command also
	 * supports it). Set the "reply" bit so Command knows this is a
	 * features-aware driver.
	 */
	features = inmsg->cmd.init_chipset.features &
		   VISOR_CHIPSET_FEATURE_PARA_HOTPLUG;
	features |= VISOR_CHIPSET_FEATURE_REPLY;

out_respond:
	अगर (inmsg->hdr.flags.response_expected)
		res = controlvm_respond_chipset_init(&inmsg->hdr, rc, features);

	वापस res;
पूर्ण

अटल पूर्णांक controlvm_respond(काष्ठा controlvm_message_header *msg_hdr,
			     पूर्णांक response, काष्ठा visor_segment_state *state)
अणु
	काष्ठा controlvm_message ouपंचांगsg;

	controlvm_init_response(&ouपंचांगsg, msg_hdr, response);
	अगर (ouपंचांगsg.hdr.flags.test_message == 1)
		वापस -EINVAL;
	अगर (state) अणु
		ouपंचांगsg.cmd.device_change_state.state = *state;
		ouपंचांगsg.cmd.device_change_state.flags.phys_device = 1;
	पूर्ण
	वापस visorchannel_संकेतinsert(chipset_dev->controlvm_channel,
					 CONTROLVM_QUEUE_REQUEST, &ouपंचांगsg);
पूर्ण

क्रमागत crash_obj_type अणु
	CRASH_DEV,
	CRASH_BUS,
पूर्ण;

अटल पूर्णांक save_crash_message(काष्ठा controlvm_message *msg,
			      क्रमागत crash_obj_type cr_type)
अणु
	u32 local_crash_msg_offset;
	u16 local_crash_msg_count;
	पूर्णांक err;

	err = visorchannel_पढ़ो(chipset_dev->controlvm_channel,
				दुरत्व(काष्ठा visor_controlvm_channel,
					 saved_crash_message_count),
				&local_crash_msg_count, माप(u16));
	अगर (err) अणु
		dev_err(&chipset_dev->acpi_device->dev,
			"failed to read message count\n");
		वापस err;
	पूर्ण
	अगर (local_crash_msg_count != CONTROLVM_CRASHMSG_MAX) अणु
		dev_err(&chipset_dev->acpi_device->dev,
			"invalid number of messages\n");
		वापस -EIO;
	पूर्ण
	err = visorchannel_पढ़ो(chipset_dev->controlvm_channel,
				दुरत्व(काष्ठा visor_controlvm_channel,
					 saved_crash_message_offset),
				&local_crash_msg_offset, माप(u32));
	अगर (err) अणु
		dev_err(&chipset_dev->acpi_device->dev,
			"failed to read offset\n");
		वापस err;
	पूर्ण
	चयन (cr_type) अणु
	हाल CRASH_DEV:
		local_crash_msg_offset += माप(काष्ठा controlvm_message);
		err = visorchannel_ग_लिखो(chipset_dev->controlvm_channel,
					 local_crash_msg_offset, msg,
					 माप(काष्ठा controlvm_message));
		अगर (err) अणु
			dev_err(&chipset_dev->acpi_device->dev,
				"failed to write dev msg\n");
			वापस err;
		पूर्ण
		अवरोध;
	हाल CRASH_BUS:
		err = visorchannel_ग_लिखो(chipset_dev->controlvm_channel,
					 local_crash_msg_offset, msg,
					 माप(काष्ठा controlvm_message));
		अगर (err) अणु
			dev_err(&chipset_dev->acpi_device->dev,
				"failed to write bus msg\n");
			वापस err;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(&chipset_dev->acpi_device->dev,
			"Invalid crash_obj_type\n");
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक controlvm_responder(क्रमागत controlvm_id cmd_id,
			       काष्ठा controlvm_message_header *pending_msg_hdr,
			       पूर्णांक response)
अणु
	अगर (pending_msg_hdr->id != (u32)cmd_id)
		वापस -EINVAL;

	वापस controlvm_respond(pending_msg_hdr, response, शून्य);
पूर्ण

अटल पूर्णांक device_changestate_responder(क्रमागत controlvm_id cmd_id,
					काष्ठा visor_device *p, पूर्णांक response,
					काष्ठा visor_segment_state state)
अणु
	काष्ठा controlvm_message ouपंचांगsg;

	अगर (p->pending_msg_hdr->id != cmd_id)
		वापस -EINVAL;

	controlvm_init_response(&ouपंचांगsg, p->pending_msg_hdr, response);
	ouपंचांगsg.cmd.device_change_state.bus_no = p->chipset_bus_no;
	ouपंचांगsg.cmd.device_change_state.dev_no = p->chipset_dev_no;
	ouपंचांगsg.cmd.device_change_state.state = state;
	वापस visorchannel_संकेतinsert(chipset_dev->controlvm_channel,
					 CONTROLVM_QUEUE_REQUEST, &ouपंचांगsg);
पूर्ण

अटल पूर्णांक visorbus_create(काष्ठा controlvm_message *inmsg)
अणु
	काष्ठा controlvm_message_packet *cmd = &inmsg->cmd;
	काष्ठा controlvm_message_header *pmsg_hdr;
	u32 bus_no = cmd->create_bus.bus_no;
	काष्ठा visor_device *bus_info;
	काष्ठा visorchannel *visorchannel;
	पूर्णांक err;

	bus_info = visorbus_get_device_by_id(bus_no, BUS_ROOT_DEVICE, शून्य);
	अगर (bus_info && bus_info->state.created == 1) अणु
		dev_err(&chipset_dev->acpi_device->dev,
			"failed %s: already exists\n", __func__);
		err = -EEXIST;
		जाओ err_respond;
	पूर्ण
	bus_info = kzalloc(माप(*bus_info), GFP_KERNEL);
	अगर (!bus_info) अणु
		err = -ENOMEM;
		जाओ err_respond;
	पूर्ण
	INIT_LIST_HEAD(&bus_info->list_all);
	bus_info->chipset_bus_no = bus_no;
	bus_info->chipset_dev_no = BUS_ROOT_DEVICE;
	अगर (guid_equal(&cmd->create_bus.bus_inst_guid, &visor_siovm_guid)) अणु
		err = save_crash_message(inmsg, CRASH_BUS);
		अगर (err)
			जाओ err_मुक्त_bus_info;
	पूर्ण
	अगर (inmsg->hdr.flags.response_expected == 1) अणु
		pmsg_hdr = kzalloc(माप(*pmsg_hdr), GFP_KERNEL);
		अगर (!pmsg_hdr) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_bus_info;
		पूर्ण
		स_नकल(pmsg_hdr, &inmsg->hdr,
		       माप(काष्ठा controlvm_message_header));
		bus_info->pending_msg_hdr = pmsg_hdr;
	पूर्ण
	visorchannel = visorchannel_create(cmd->create_bus.channel_addr,
					   GFP_KERNEL,
					   &cmd->create_bus.bus_data_type_guid,
					   false);
	अगर (!visorchannel) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_pending_msg;
	पूर्ण
	bus_info->visorchannel = visorchannel;
	/* Response will be handled by visorbus_create_instance on success */
	err = visorbus_create_instance(bus_info);
	अगर (err)
		जाओ err_destroy_channel;
	वापस 0;

err_destroy_channel:
	visorchannel_destroy(visorchannel);

err_मुक्त_pending_msg:
	kमुक्त(bus_info->pending_msg_hdr);

err_मुक्त_bus_info:
	kमुक्त(bus_info);

err_respond:
	अगर (inmsg->hdr.flags.response_expected == 1)
		controlvm_responder(inmsg->hdr.id, &inmsg->hdr, err);
	वापस err;
पूर्ण

अटल पूर्णांक visorbus_destroy(काष्ठा controlvm_message *inmsg)
अणु
	काष्ठा controlvm_message_header *pmsg_hdr;
	u32 bus_no = inmsg->cmd.destroy_bus.bus_no;
	काष्ठा visor_device *bus_info;
	पूर्णांक err;

	bus_info = visorbus_get_device_by_id(bus_no, BUS_ROOT_DEVICE, शून्य);
	अगर (!bus_info) अणु
		err = -ENODEV;
		जाओ err_respond;
	पूर्ण
	अगर (bus_info->state.created == 0) अणु
		err = -ENOENT;
		जाओ err_respond;
	पूर्ण
	अगर (bus_info->pending_msg_hdr) अणु
		/* only non-शून्य अगर dev is still रुकोing on a response */
		err = -EEXIST;
		जाओ err_respond;
	पूर्ण
	अगर (inmsg->hdr.flags.response_expected == 1) अणु
		pmsg_hdr = kzalloc(माप(*pmsg_hdr), GFP_KERNEL);
		अगर (!pmsg_hdr) अणु
			err = -ENOMEM;
			जाओ err_respond;
		पूर्ण
		स_नकल(pmsg_hdr, &inmsg->hdr,
		       माप(काष्ठा controlvm_message_header));
		bus_info->pending_msg_hdr = pmsg_hdr;
	पूर्ण
	/* Response will be handled by visorbus_हटाओ_instance */
	visorbus_हटाओ_instance(bus_info);
	वापस 0;

err_respond:
	अगर (inmsg->hdr.flags.response_expected == 1)
		controlvm_responder(inmsg->hdr.id, &inmsg->hdr, err);
	वापस err;
पूर्ण

अटल स्थिर guid_t *parser_id_get(काष्ठा parser_context *ctx)
अणु
	वापस &ctx->data.id;
पूर्ण

अटल व्योम *parser_string_get(u8 *pscan, पूर्णांक nscan)
अणु
	पूर्णांक value_length;
	व्योम *value;

	अगर (nscan == 0)
		वापस शून्य;

	value_length = strnlen(pscan, nscan);
	value = kzalloc(value_length + 1, GFP_KERNEL);
	अगर (!value)
		वापस शून्य;
	अगर (value_length > 0)
		स_नकल(value, pscan, value_length);
	वापस value;
पूर्ण

अटल व्योम *parser_name_get(काष्ठा parser_context *ctx)
अणु
	काष्ठा visor_controlvm_parameters_header *phdr;

	phdr = &ctx->data;
	अगर ((अचिन्हित दीर्घ)phdr->name_offset +
	    (अचिन्हित दीर्घ)phdr->name_length > ctx->param_bytes)
		वापस शून्य;
	ctx->curr = (अक्षर *)&phdr + phdr->name_offset;
	ctx->bytes_reमुख्यing = phdr->name_length;
	वापस parser_string_get(ctx->curr, phdr->name_length);
पूर्ण

अटल पूर्णांक visorbus_configure(काष्ठा controlvm_message *inmsg,
			      काष्ठा parser_context *parser_ctx)
अणु
	काष्ठा controlvm_message_packet *cmd = &inmsg->cmd;
	u32 bus_no;
	काष्ठा visor_device *bus_info;
	पूर्णांक err = 0;

	bus_no = cmd->configure_bus.bus_no;
	bus_info = visorbus_get_device_by_id(bus_no, BUS_ROOT_DEVICE, शून्य);
	अगर (!bus_info) अणु
		err = -EINVAL;
		जाओ err_respond;
	पूर्ण
	अगर (bus_info->state.created == 0) अणु
		err = -EINVAL;
		जाओ err_respond;
	पूर्ण
	अगर (bus_info->pending_msg_hdr) अणु
		err = -EIO;
		जाओ err_respond;
	पूर्ण
	err = visorchannel_set_clientpartition(bus_info->visorchannel,
					       cmd->configure_bus.guest_handle);
	अगर (err)
		जाओ err_respond;
	अगर (parser_ctx) अणु
		स्थिर guid_t *partition_guid = parser_id_get(parser_ctx);

		guid_copy(&bus_info->partition_guid, partition_guid);
		bus_info->name = parser_name_get(parser_ctx);
	पूर्ण
	अगर (inmsg->hdr.flags.response_expected == 1)
		controlvm_responder(inmsg->hdr.id, &inmsg->hdr, err);
	वापस 0;

err_respond:
	dev_err(&chipset_dev->acpi_device->dev,
		"%s exited with err: %d\n", __func__, err);
	अगर (inmsg->hdr.flags.response_expected == 1)
		controlvm_responder(inmsg->hdr.id, &inmsg->hdr, err);
	वापस err;
पूर्ण

अटल पूर्णांक visorbus_device_create(काष्ठा controlvm_message *inmsg)
अणु
	काष्ठा controlvm_message_packet *cmd = &inmsg->cmd;
	काष्ठा controlvm_message_header *pmsg_hdr;
	u32 bus_no = cmd->create_device.bus_no;
	u32 dev_no = cmd->create_device.dev_no;
	काष्ठा visor_device *dev_info;
	काष्ठा visor_device *bus_info;
	काष्ठा visorchannel *visorchannel;
	पूर्णांक err;

	bus_info = visorbus_get_device_by_id(bus_no, BUS_ROOT_DEVICE, शून्य);
	अगर (!bus_info) अणु
		dev_err(&chipset_dev->acpi_device->dev,
			"failed to get bus by id: %d\n", bus_no);
		err = -ENODEV;
		जाओ err_respond;
	पूर्ण
	अगर (bus_info->state.created == 0) अणु
		dev_err(&chipset_dev->acpi_device->dev,
			"bus not created, id: %d\n", bus_no);
		err = -EINVAL;
		जाओ err_respond;
	पूर्ण
	dev_info = visorbus_get_device_by_id(bus_no, dev_no, शून्य);
	अगर (dev_info && dev_info->state.created == 1) अणु
		dev_err(&chipset_dev->acpi_device->dev,
			"failed to get bus by id: %d/%d\n", bus_no, dev_no);
		err = -EEXIST;
		जाओ err_respond;
	पूर्ण

	dev_info = kzalloc(माप(*dev_info), GFP_KERNEL);
	अगर (!dev_info) अणु
		err = -ENOMEM;
		जाओ err_respond;
	पूर्ण
	dev_info->chipset_bus_no = bus_no;
	dev_info->chipset_dev_no = dev_no;
	guid_copy(&dev_info->inst, &cmd->create_device.dev_inst_guid);
	dev_info->device.parent = &bus_info->device;
	visorchannel = visorchannel_create(cmd->create_device.channel_addr,
					   GFP_KERNEL,
					   &cmd->create_device.data_type_guid,
					   true);
	अगर (!visorchannel) अणु
		dev_err(&chipset_dev->acpi_device->dev,
			"failed to create visorchannel: %d/%d\n",
			bus_no, dev_no);
		err = -ENOMEM;
		जाओ err_मुक्त_dev_info;
	पूर्ण
	dev_info->visorchannel = visorchannel;
	guid_copy(&dev_info->channel_type_guid,
		  &cmd->create_device.data_type_guid);
	अगर (guid_equal(&cmd->create_device.data_type_guid,
		       &visor_vhba_channel_guid)) अणु
		err = save_crash_message(inmsg, CRASH_DEV);
		अगर (err)
			जाओ err_destroy_visorchannel;
	पूर्ण
	अगर (inmsg->hdr.flags.response_expected == 1) अणु
		pmsg_hdr = kzalloc(माप(*pmsg_hdr), GFP_KERNEL);
		अगर (!pmsg_hdr) अणु
			err = -ENOMEM;
			जाओ err_destroy_visorchannel;
		पूर्ण
		स_नकल(pmsg_hdr, &inmsg->hdr,
		       माप(काष्ठा controlvm_message_header));
		dev_info->pending_msg_hdr = pmsg_hdr;
	पूर्ण
	/* create_visor_device will send response */
	err = create_visor_device(dev_info);
	अगर (err)
		जाओ err_destroy_visorchannel;

	वापस 0;

err_destroy_visorchannel:
	visorchannel_destroy(visorchannel);

err_मुक्त_dev_info:
	kमुक्त(dev_info);

err_respond:
	अगर (inmsg->hdr.flags.response_expected == 1)
		controlvm_responder(inmsg->hdr.id, &inmsg->hdr, err);
	वापस err;
पूर्ण

अटल पूर्णांक visorbus_device_changestate(काष्ठा controlvm_message *inmsg)
अणु
	काष्ठा controlvm_message_packet *cmd = &inmsg->cmd;
	काष्ठा controlvm_message_header *pmsg_hdr;
	u32 bus_no = cmd->device_change_state.bus_no;
	u32 dev_no = cmd->device_change_state.dev_no;
	काष्ठा visor_segment_state state = cmd->device_change_state.state;
	काष्ठा visor_device *dev_info;
	पूर्णांक err = 0;

	dev_info = visorbus_get_device_by_id(bus_no, dev_no, शून्य);
	अगर (!dev_info) अणु
		err = -ENODEV;
		जाओ err_respond;
	पूर्ण
	अगर (dev_info->state.created == 0) अणु
		err = -EINVAL;
		जाओ err_respond;
	पूर्ण
	अगर (dev_info->pending_msg_hdr) अणु
		/* only non-शून्य अगर dev is still रुकोing on a response */
		err = -EIO;
		जाओ err_respond;
	पूर्ण

	अगर (inmsg->hdr.flags.response_expected == 1) अणु
		pmsg_hdr = kzalloc(माप(*pmsg_hdr), GFP_KERNEL);
		अगर (!pmsg_hdr) अणु
			err = -ENOMEM;
			जाओ err_respond;
		पूर्ण
		स_नकल(pmsg_hdr, &inmsg->hdr,
		       माप(काष्ठा controlvm_message_header));
		dev_info->pending_msg_hdr = pmsg_hdr;
	पूर्ण
	अगर (state.alive == segment_state_running.alive &&
	    state.operating == segment_state_running.operating)
		/* Response will be sent from visorchipset_device_resume */
		err = visorchipset_device_resume(dev_info);
	/* ServerNotReady / ServerLost / SegmentStateStandby */
	अन्यथा अगर (state.alive == segment_state_standby.alive &&
		 state.operating == segment_state_standby.operating)
		/*
		 * technically this is standby हाल where server is lost.
		 * Response will be sent from visorchipset_device_छोड़ो.
		 */
		err = visorchipset_device_छोड़ो(dev_info);
	अगर (err)
		जाओ err_respond;
	वापस 0;

err_respond:
	dev_err(&chipset_dev->acpi_device->dev, "failed: %d\n", err);
	अगर (inmsg->hdr.flags.response_expected == 1)
		controlvm_responder(inmsg->hdr.id, &inmsg->hdr, err);
	वापस err;
पूर्ण

अटल पूर्णांक visorbus_device_destroy(काष्ठा controlvm_message *inmsg)
अणु
	काष्ठा controlvm_message_packet *cmd = &inmsg->cmd;
	काष्ठा controlvm_message_header *pmsg_hdr;
	u32 bus_no = cmd->destroy_device.bus_no;
	u32 dev_no = cmd->destroy_device.dev_no;
	काष्ठा visor_device *dev_info;
	पूर्णांक err;

	dev_info = visorbus_get_device_by_id(bus_no, dev_no, शून्य);
	अगर (!dev_info) अणु
		err = -ENODEV;
		जाओ err_respond;
	पूर्ण
	अगर (dev_info->state.created == 0) अणु
		err = -EINVAL;
		जाओ err_respond;
	पूर्ण
	अगर (dev_info->pending_msg_hdr) अणु
		/* only non-शून्य अगर dev is still रुकोing on a response */
		err = -EIO;
		जाओ err_respond;
	पूर्ण
	अगर (inmsg->hdr.flags.response_expected == 1) अणु
		pmsg_hdr = kzalloc(माप(*pmsg_hdr), GFP_KERNEL);
		अगर (!pmsg_hdr) अणु
			err = -ENOMEM;
			जाओ err_respond;
		पूर्ण

		स_नकल(pmsg_hdr, &inmsg->hdr,
		       माप(काष्ठा controlvm_message_header));
		dev_info->pending_msg_hdr = pmsg_hdr;
	पूर्ण
	kमुक्त(dev_info->name);
	हटाओ_visor_device(dev_info);
	वापस 0;

err_respond:
	अगर (inmsg->hdr.flags.response_expected == 1)
		controlvm_responder(inmsg->hdr.id, &inmsg->hdr, err);
	वापस err;
पूर्ण

/*
 * The general parahotplug flow works as follows. The visorchipset receives
 * a DEVICE_CHANGESTATE message from Command specअगरying a physical device
 * to enable or disable. The CONTROLVM message handler calls
 * parahotplug_process_message, which then adds the message to a global list
 * and kicks off a udev event which causes a user level script to enable or
 * disable the specअगरied device. The udev script then ग_लिखोs to
 * /sys/devices/platक्रमm/visorchipset/parahotplug, which causes the
 * parahotplug store functions to get called, at which poपूर्णांक the
 * appropriate CONTROLVM message is retrieved from the list and responded to.
 */

#घोषणा PARAHOTPLUG_TIMEOUT_MS 2000

/*
 * parahotplug_next_id() - generate unique पूर्णांक to match an outstanding
 *                         CONTROLVM message with a udev script /sys
 *                         response
 *
 * Return: a unique पूर्णांकeger value
 */
अटल पूर्णांक parahotplug_next_id(व्योम)
अणु
	अटल atomic_t id = ATOMIC_INIT(0);

	वापस atomic_inc_वापस(&id);
पूर्ण

/*
 * parahotplug_next_expiration() - वापसs the समय (in jअगरfies) when a
 *                                 CONTROLVM message on the list should expire
 *                                 -- PARAHOTPLUG_TIMEOUT_MS in the future
 *
 * Return: expected expiration समय (in jअगरfies)
 */
अटल अचिन्हित दीर्घ parahotplug_next_expiration(व्योम)
अणु
	वापस jअगरfies + msecs_to_jअगरfies(PARAHOTPLUG_TIMEOUT_MS);
पूर्ण

/*
 * parahotplug_request_create() - create a parahotplug_request, which is
 *                                basically a wrapper क्रम a CONTROLVM_MESSAGE
 *                                that we can stick on a list
 * @msg: the message to insert in the request
 *
 * Return: the request containing the provided message
 */
अटल काष्ठा parahotplug_request *parahotplug_request_create(
						काष्ठा controlvm_message *msg)
अणु
	काष्ठा parahotplug_request *req;

	req = kदो_स्मृति(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस शून्य;
	req->id = parahotplug_next_id();
	req->expiration = parahotplug_next_expiration();
	req->msg = *msg;
	वापस req;
पूर्ण

/*
 * parahotplug_request_destroy() - मुक्त a parahotplug_request
 * @req: the request to deallocate
 */
अटल व्योम parahotplug_request_destroy(काष्ठा parahotplug_request *req)
अणु
	kमुक्त(req);
पूर्ण

अटल LIST_HEAD(parahotplug_request_list);
/* lock क्रम above */
अटल DEFINE_SPINLOCK(parahotplug_request_list_lock);

/*
 * parahotplug_request_complete() - mark request as complete
 * @id:     the id of the request
 * @active: indicates whether the request is asचिन्हित to active partition
 *
 * Called from the /sys handler, which means the user script has
 * finished the enable/disable. Find the matching identअगरier, and
 * respond to the CONTROLVM message with success.
 *
 * Return: 0 on success or -EINVAL on failure
 */
अटल पूर्णांक parahotplug_request_complete(पूर्णांक id, u16 active)
अणु
	काष्ठा list_head *pos;
	काष्ठा list_head *पंचांगp;
	काष्ठा parahotplug_request *req;

	spin_lock(&parahotplug_request_list_lock);
	/* Look क्रम a request matching "id". */
	list_क्रम_each_safe(pos, पंचांगp, &parahotplug_request_list) अणु
		req = list_entry(pos, काष्ठा parahotplug_request, list);
		अगर (req->id == id) अणु
			/*
			 * Found a match. Remove it from the list and
			 * respond.
			 */
			list_del(pos);
			spin_unlock(&parahotplug_request_list_lock);
			req->msg.cmd.device_change_state.state.active = active;
			अगर (req->msg.hdr.flags.response_expected)
				controlvm_respond(
				       &req->msg.hdr, CONTROLVM_RESP_SUCCESS,
				       &req->msg.cmd.device_change_state.state);
			parahotplug_request_destroy(req);
			वापस 0;
		पूर्ण
	पूर्ण
	spin_unlock(&parahotplug_request_list_lock);
	वापस -EINVAL;
पूर्ण

/*
 * devicedisabled_store() - disables the hotplug device
 * @dev:   sysfs पूर्णांकerface variable not utilized in this function
 * @attr:  sysfs पूर्णांकerface variable not utilized in this function
 * @buf:   buffer containing the device id
 * @count: the size of the buffer
 *
 * The parahotplug/devicedisabled पूर्णांकerface माला_लो called by our support script
 * when an SR-IOV device has been shut करोwn. The ID is passed to the script
 * and then passed back when the device has been हटाओd.
 *
 * Return: the size of the buffer क्रम success or negative क्रम error
 */
अटल sमाप_प्रकार devicedisabled_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक id;
	पूर्णांक err;

	अगर (kstrtouपूर्णांक(buf, 10, &id))
		वापस -EINVAL;
	err = parahotplug_request_complete(id, 0);
	अगर (err < 0)
		वापस err;
	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(devicedisabled);

/*
 * deviceenabled_store() - enables the hotplug device
 * @dev:   sysfs पूर्णांकerface variable not utilized in this function
 * @attr:  sysfs पूर्णांकerface variable not utilized in this function
 * @buf:   buffer containing the device id
 * @count: the size of the buffer
 *
 * The parahotplug/deviceenabled पूर्णांकerface माला_लो called by our support script
 * when an SR-IOV device has been recovered. The ID is passed to the script
 * and then passed back when the device has been brought back up.
 *
 * Return: the size of the buffer क्रम success or negative क्रम error
 */
अटल sमाप_प्रकार deviceenabled_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक id;

	अगर (kstrtouपूर्णांक(buf, 10, &id))
		वापस -EINVAL;
	parahotplug_request_complete(id, 1);
	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(deviceenabled);

अटल काष्ठा attribute *visorchipset_install_attrs[] = अणु
	&dev_attr_toolaction.attr,
	&dev_attr_boottotool.attr,
	&dev_attr_error.attr,
	&dev_attr_textid.attr,
	&dev_attr_reमुख्यing_steps.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group visorchipset_install_group = अणु
	.name = "install",
	.attrs = visorchipset_install_attrs
पूर्ण;

अटल काष्ठा attribute *visorchipset_parahotplug_attrs[] = अणु
	&dev_attr_devicedisabled.attr,
	&dev_attr_deviceenabled.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group visorchipset_parahotplug_group = अणु
	.name = "parahotplug",
	.attrs = visorchipset_parahotplug_attrs
पूर्ण;

अटल स्थिर काष्ठा attribute_group *visorchipset_dev_groups[] = अणु
	&visorchipset_install_group,
	&visorchipset_parahotplug_group,
	शून्य
पूर्ण;

/*
 * parahotplug_request_kickoff() - initiate parahotplug request
 * @req: the request to initiate
 *
 * Cause uevent to run the user level script to करो the disable/enable specअगरied
 * in the parahotplug_request.
 */
अटल पूर्णांक parahotplug_request_kickoff(काष्ठा parahotplug_request *req)
अणु
	काष्ठा controlvm_message_packet *cmd = &req->msg.cmd;
	अक्षर env_cmd[40], env_id[40], env_state[40], env_bus[40], env_dev[40],
	     env_func[40];
	अक्षर *envp[] = अणु env_cmd, env_id, env_state, env_bus, env_dev,
			 env_func, शून्य
	पूर्ण;

	प्र_लिखो(env_cmd, "VISOR_PARAHOTPLUG=1");
	प्र_लिखो(env_id, "VISOR_PARAHOTPLUG_ID=%d", req->id);
	प्र_लिखो(env_state, "VISOR_PARAHOTPLUG_STATE=%d",
		cmd->device_change_state.state.active);
	प्र_लिखो(env_bus, "VISOR_PARAHOTPLUG_BUS=%d",
		cmd->device_change_state.bus_no);
	प्र_लिखो(env_dev, "VISOR_PARAHOTPLUG_DEVICE=%d",
		cmd->device_change_state.dev_no >> 3);
	प्र_लिखो(env_func, "VISOR_PARAHOTPLUG_FUNCTION=%d",
		cmd->device_change_state.dev_no & 0x7);
	वापस kobject_uevent_env(&chipset_dev->acpi_device->dev.kobj,
				  KOBJ_CHANGE, envp);
पूर्ण

/*
 * parahotplug_process_message() - enables or disables a PCI device by kicking
 *                                 off a udev script
 * @inmsg: the message indicating whether to enable or disable
 */
अटल पूर्णांक parahotplug_process_message(काष्ठा controlvm_message *inmsg)
अणु
	काष्ठा parahotplug_request *req;
	पूर्णांक err;

	req = parahotplug_request_create(inmsg);
	अगर (!req)
		वापस -ENOMEM;
	/*
	 * For enable messages, just respond with success right away, we करोn't
	 * need to रुको to see अगर the enable was successful.
	 */
	अगर (inmsg->cmd.device_change_state.state.active) अणु
		err = parahotplug_request_kickoff(req);
		अगर (err)
			जाओ err_respond;
		controlvm_respond(&inmsg->hdr, CONTROLVM_RESP_SUCCESS,
				  &inmsg->cmd.device_change_state.state);
		parahotplug_request_destroy(req);
		वापस 0;
	पूर्ण
	/*
	 * For disable messages, add the request to the request list beक्रमe
	 * kicking off the udev script. It won't get responded to until the
	 * script has indicated it's करोne.
	 */
	spin_lock(&parahotplug_request_list_lock);
	list_add_tail(&req->list, &parahotplug_request_list);
	spin_unlock(&parahotplug_request_list_lock);
	err = parahotplug_request_kickoff(req);
	अगर (err)
		जाओ err_respond;
	वापस 0;

err_respond:
	controlvm_respond(&inmsg->hdr, err,
			  &inmsg->cmd.device_change_state.state);
	वापस err;
पूर्ण

/*
 * chipset_पढ़ोy_uevent() - sends chipset_पढ़ोy action
 *
 * Send ACTION=online क्रम DEVPATH=/sys/devices/platक्रमm/visorchipset.
 *
 * Return: 0 on success, negative on failure
 */
अटल पूर्णांक chipset_पढ़ोy_uevent(काष्ठा controlvm_message_header *msg_hdr)
अणु
	पूर्णांक res;

	res = kobject_uevent(&chipset_dev->acpi_device->dev.kobj, KOBJ_ONLINE);
	अगर (msg_hdr->flags.response_expected)
		controlvm_respond(msg_hdr, res, शून्य);
	वापस res;
पूर्ण

/*
 * chipset_selftest_uevent() - sends chipset_selftest action
 *
 * Send ACTION=online क्रम DEVPATH=/sys/devices/platक्रमm/visorchipset.
 *
 * Return: 0 on success, negative on failure
 */
अटल पूर्णांक chipset_selftest_uevent(काष्ठा controlvm_message_header *msg_hdr)
अणु
	अक्षर env_selftest[20];
	अक्षर *envp[] = अणु env_selftest, शून्य पूर्ण;
	पूर्णांक res;

	प्र_लिखो(env_selftest, "SPARSP_SELFTEST=%d", 1);
	res = kobject_uevent_env(&chipset_dev->acpi_device->dev.kobj,
				 KOBJ_CHANGE, envp);
	अगर (msg_hdr->flags.response_expected)
		controlvm_respond(msg_hdr, res, शून्य);
	वापस res;
पूर्ण

/*
 * chipset_notपढ़ोy_uevent() - sends chipset_notपढ़ोy action
 *
 * Send ACTION=offline क्रम DEVPATH=/sys/devices/platक्रमm/visorchipset.
 *
 * Return: 0 on success, negative on failure
 */
अटल पूर्णांक chipset_notपढ़ोy_uevent(काष्ठा controlvm_message_header *msg_hdr)
अणु
	पूर्णांक res = kobject_uevent(&chipset_dev->acpi_device->dev.kobj,
				 KOBJ_OFFLINE);

	अगर (msg_hdr->flags.response_expected)
		controlvm_respond(msg_hdr, res, शून्य);
	वापस res;
पूर्ण

अटल पूर्णांक unisys_vmcall(अचिन्हित दीर्घ tuple, अचिन्हित दीर्घ param)
अणु
	पूर्णांक result = 0;
	अचिन्हित पूर्णांक cpuid_eax, cpuid_ebx, cpuid_ecx, cpuid_edx;
	अचिन्हित दीर्घ reg_ebx;
	अचिन्हित दीर्घ reg_ecx;

	reg_ebx = param & 0xFFFFFFFF;
	reg_ecx = param >> 32;
	cpuid(0x00000001, &cpuid_eax, &cpuid_ebx, &cpuid_ecx, &cpuid_edx);
	अगर (!(cpuid_ecx & 0x80000000))
		वापस -EPERM;
	__यंत्र__ __अस्थिर__(".byte 0x00f, 0x001, 0x0c1" : "=a"(result) :
			     "a"(tuple), "b"(reg_ebx), "c"(reg_ecx));
	अगर (result)
		जाओ error;
	वापस 0;

/* Need to convert from VMCALL error codes to Linux */
error:
	चयन (result) अणु
	हाल VMCALL_RESULT_INVALID_PARAM:
		वापस -EINVAL;
	हाल VMCALL_RESULT_DATA_UNAVAILABLE:
		वापस -ENODEV;
	शेष:
		वापस -EFAULT;
	पूर्ण
पूर्ण

अटल पूर्णांक controlvm_channel_create(काष्ठा visorchipset_device *dev)
अणु
	काष्ठा visorchannel *chan;
	u64 addr;
	पूर्णांक err;

	err = unisys_vmcall(VMCALL_CONTROLVM_ADDR,
			    virt_to_phys(&dev->controlvm_params));
	अगर (err)
		वापस err;
	addr = dev->controlvm_params.address;
	chan = visorchannel_create(addr, GFP_KERNEL,
				   &visor_controlvm_channel_guid, true);
	अगर (!chan)
		वापस -ENOMEM;
	dev->controlvm_channel = chan;
	वापस 0;
पूर्ण

अटल व्योम setup_crash_devices_work_queue(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा controlvm_message local_crash_bus_msg;
	काष्ठा controlvm_message local_crash_dev_msg;
	काष्ठा controlvm_message msg = अणु
		.hdr.id = CONTROLVM_CHIPSET_INIT,
		.cmd.init_chipset = अणु
			.bus_count = 23,
			.चयन_count = 0,
		पूर्ण,
	पूर्ण;
	u32 local_crash_msg_offset;
	u16 local_crash_msg_count;

	/* send init chipset msg */
	chipset_init(&msg);
	/* get saved message count */
	अगर (visorchannel_पढ़ो(chipset_dev->controlvm_channel,
			      दुरत्व(काष्ठा visor_controlvm_channel,
				       saved_crash_message_count),
			      &local_crash_msg_count, माप(u16)) < 0) अणु
		dev_err(&chipset_dev->acpi_device->dev,
			"failed to read channel\n");
		वापस;
	पूर्ण
	अगर (local_crash_msg_count != CONTROLVM_CRASHMSG_MAX) अणु
		dev_err(&chipset_dev->acpi_device->dev, "invalid count\n");
		वापस;
	पूर्ण
	/* get saved crash message offset */
	अगर (visorchannel_पढ़ो(chipset_dev->controlvm_channel,
			      दुरत्व(काष्ठा visor_controlvm_channel,
				       saved_crash_message_offset),
			      &local_crash_msg_offset, माप(u32)) < 0) अणु
		dev_err(&chipset_dev->acpi_device->dev,
			"failed to read channel\n");
		वापस;
	पूर्ण
	/* पढ़ो create device message क्रम storage bus offset */
	अगर (visorchannel_पढ़ो(chipset_dev->controlvm_channel,
			      local_crash_msg_offset,
			      &local_crash_bus_msg,
			      माप(काष्ठा controlvm_message)) < 0) अणु
		dev_err(&chipset_dev->acpi_device->dev,
			"failed to read channel\n");
		वापस;
	पूर्ण
	/* पढ़ो create device message क्रम storage device */
	अगर (visorchannel_पढ़ो(chipset_dev->controlvm_channel,
			      local_crash_msg_offset +
			      माप(काष्ठा controlvm_message),
			      &local_crash_dev_msg,
			      माप(काष्ठा controlvm_message)) < 0) अणु
		dev_err(&chipset_dev->acpi_device->dev,
			"failed to read channel\n");
		वापस;
	पूर्ण
	/* reuse IOVM create bus message */
	अगर (!local_crash_bus_msg.cmd.create_bus.channel_addr) अणु
		dev_err(&chipset_dev->acpi_device->dev,
			"no valid create_bus message\n");
		वापस;
	पूर्ण
	visorbus_create(&local_crash_bus_msg);
	/* reuse create device message क्रम storage device */
	अगर (!local_crash_dev_msg.cmd.create_device.channel_addr) अणु
		dev_err(&chipset_dev->acpi_device->dev,
			"no valid create_device message\n");
		वापस;
	पूर्ण
	visorbus_device_create(&local_crash_dev_msg);
पूर्ण

व्योम visorbus_response(काष्ठा visor_device *bus_info, पूर्णांक response,
		       पूर्णांक controlvm_id)
अणु
	अगर (!bus_info->pending_msg_hdr)
		वापस;

	controlvm_responder(controlvm_id, bus_info->pending_msg_hdr, response);
	kमुक्त(bus_info->pending_msg_hdr);
	bus_info->pending_msg_hdr = शून्य;
पूर्ण

व्योम visorbus_device_changestate_response(काष्ठा visor_device *dev_info,
					  पूर्णांक response,
					  काष्ठा visor_segment_state state)
अणु
	अगर (!dev_info->pending_msg_hdr)
		वापस;

	device_changestate_responder(CONTROLVM_DEVICE_CHANGESTATE, dev_info,
				     response, state);
	kमुक्त(dev_info->pending_msg_hdr);
	dev_info->pending_msg_hdr = शून्य;
पूर्ण

अटल व्योम parser_करोne(काष्ठा parser_context *ctx)
अणु
	chipset_dev->controlvm_payload_bytes_buffered -= ctx->param_bytes;
	kमुक्त(ctx);
पूर्ण

अटल काष्ठा parser_context *parser_init_stream(u64 addr, u32 bytes,
						 bool *retry)
अणु
	अचिन्हित दीर्घ allocbytes;
	काष्ठा parser_context *ctx;
	व्योम *mapping;

	*retry = false;
	/* alloc an extra byte to ensure payload is \0 terminated */
	allocbytes = (अचिन्हित दीर्घ)bytes + 1 + (माप(काष्ठा parser_context) -
		     माप(काष्ठा visor_controlvm_parameters_header));
	अगर ((chipset_dev->controlvm_payload_bytes_buffered + bytes) >
	     MAX_CONTROLVM_PAYLOAD_BYTES) अणु
		*retry = true;
		वापस शून्य;
	पूर्ण
	ctx = kzalloc(allocbytes, GFP_KERNEL);
	अगर (!ctx) अणु
		*retry = true;
		वापस शून्य;
	पूर्ण
	ctx->allocbytes = allocbytes;
	ctx->param_bytes = bytes;
	mapping = memremap(addr, bytes, MEMREMAP_WB);
	अगर (!mapping)
		जाओ err_finish_ctx;
	स_नकल(&ctx->data, mapping, bytes);
	memunmap(mapping);
	ctx->byte_stream = true;
	chipset_dev->controlvm_payload_bytes_buffered += ctx->param_bytes;
	वापस ctx;

err_finish_ctx:
	kमुक्त(ctx);
	वापस शून्य;
पूर्ण

/*
 * handle_command() - process a controlvm message
 * @inmsg:        the message to process
 * @channel_addr: address of the controlvm channel
 *
 * Return:
 *	0	- Successfully processed the message
 *	-EAGAIN - ControlVM message was not processed and should be retried
 *		  पढ़ोing the next controlvm message; a scenario where this can
 *		  occur is when we need to throttle the allocation of memory in
 *		  which to copy out controlvm payload data.
 *	< 0	- error: ControlVM message was processed but an error occurred.
 */
अटल पूर्णांक handle_command(काष्ठा controlvm_message inmsg, u64 channel_addr)
अणु
	काष्ठा controlvm_message_packet *cmd = &inmsg.cmd;
	u64 parm_addr;
	u32 parm_bytes;
	काष्ठा parser_context *parser_ctx = शून्य;
	काष्ठा controlvm_message ackmsg;
	पूर्णांक err = 0;

	/* create parsing context अगर necessary */
	parm_addr = channel_addr + inmsg.hdr.payload_vm_offset;
	parm_bytes = inmsg.hdr.payload_bytes;
	/*
	 * Parameter and channel addresses within test messages actually lie
	 * within our OS-controlled memory. We need to know that, because it
	 * makes a dअगरference in how we compute the भव address.
	 */
	अगर (parm_bytes) अणु
		bool retry;

		parser_ctx = parser_init_stream(parm_addr, parm_bytes, &retry);
		अगर (!parser_ctx && retry)
			वापस -EAGAIN;
	पूर्ण
	controlvm_init_response(&ackmsg, &inmsg.hdr, CONTROLVM_RESP_SUCCESS);
	err = visorchannel_संकेतinsert(chipset_dev->controlvm_channel,
					CONTROLVM_QUEUE_ACK, &ackmsg);
	अगर (err)
		वापस err;
	चयन (inmsg.hdr.id) अणु
	हाल CONTROLVM_CHIPSET_INIT:
		err = chipset_init(&inmsg);
		अवरोध;
	हाल CONTROLVM_BUS_CREATE:
		err = visorbus_create(&inmsg);
		अवरोध;
	हाल CONTROLVM_BUS_DESTROY:
		err = visorbus_destroy(&inmsg);
		अवरोध;
	हाल CONTROLVM_BUS_CONFIGURE:
		err = visorbus_configure(&inmsg, parser_ctx);
		अवरोध;
	हाल CONTROLVM_DEVICE_CREATE:
		err = visorbus_device_create(&inmsg);
		अवरोध;
	हाल CONTROLVM_DEVICE_CHANGESTATE:
		अगर (cmd->device_change_state.flags.phys_device) अणु
			err = parahotplug_process_message(&inmsg);
		पूर्ण अन्यथा अणु
			/*
			 * save the hdr and cmd काष्ठाures क्रम later use when
			 * sending back the response to Command
			 */
			err = visorbus_device_changestate(&inmsg);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CONTROLVM_DEVICE_DESTROY:
		err = visorbus_device_destroy(&inmsg);
		अवरोध;
	हाल CONTROLVM_DEVICE_CONFIGURE:
		/* no op just send a respond that we passed */
		अगर (inmsg.hdr.flags.response_expected)
			controlvm_respond(&inmsg.hdr, CONTROLVM_RESP_SUCCESS,
					  शून्य);
		अवरोध;
	हाल CONTROLVM_CHIPSET_READY:
		err = chipset_पढ़ोy_uevent(&inmsg.hdr);
		अवरोध;
	हाल CONTROLVM_CHIPSET_SELFTEST:
		err = chipset_selftest_uevent(&inmsg.hdr);
		अवरोध;
	हाल CONTROLVM_CHIPSET_STOP:
		err = chipset_notपढ़ोy_uevent(&inmsg.hdr);
		अवरोध;
	शेष:
		err = -ENOMSG;
		अगर (inmsg.hdr.flags.response_expected)
			controlvm_respond(&inmsg.hdr,
					  -CONTROLVM_RESP_ID_UNKNOWN, शून्य);
		अवरोध;
	पूर्ण
	अगर (parser_ctx) अणु
		parser_करोne(parser_ctx);
		parser_ctx = शून्य;
	पूर्ण
	वापस err;
पूर्ण

/*
 * पढ़ो_controlvm_event() - retreives the next message from the
 *                          CONTROLVM_QUEUE_EVENT queue in the controlvm
 *                          channel
 * @msg: poपूर्णांकer to the retrieved message
 *
 * Return: 0 अगर valid message was retrieved or -error
 */
अटल पूर्णांक पढ़ो_controlvm_event(काष्ठा controlvm_message *msg)
अणु
	पूर्णांक err = visorchannel_संकेतहटाओ(chipset_dev->controlvm_channel,
					    CONTROLVM_QUEUE_EVENT, msg);

	अगर (err)
		वापस err;
	/* got a message */
	अगर (msg->hdr.flags.test_message == 1)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * parahotplug_process_list() - हटाओ any request from the list that's been on
 *                              there too दीर्घ and respond with an error
 */
अटल व्योम parahotplug_process_list(व्योम)
अणु
	काष्ठा list_head *pos;
	काष्ठा list_head *पंचांगp;

	spin_lock(&parahotplug_request_list_lock);
	list_क्रम_each_safe(pos, पंचांगp, &parahotplug_request_list) अणु
		काष्ठा parahotplug_request *req =
		    list_entry(pos, काष्ठा parahotplug_request, list);

		अगर (!समय_after_eq(jअगरfies, req->expiration))
			जारी;
		list_del(pos);
		अगर (req->msg.hdr.flags.response_expected)
			controlvm_respond(
				&req->msg.hdr,
				CONTROLVM_RESP_DEVICE_UDEV_TIMEOUT,
				&req->msg.cmd.device_change_state.state);
		parahotplug_request_destroy(req);
	पूर्ण
	spin_unlock(&parahotplug_request_list_lock);
पूर्ण

अटल व्योम controlvm_periodic_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा controlvm_message inmsg;
	पूर्णांक count = 0;
	पूर्णांक err;

	/* Drain the RESPONSE queue make it empty */
	करो अणु
		err = visorchannel_संकेतहटाओ(chipset_dev->controlvm_channel,
						CONTROLVM_QUEUE_RESPONSE,
						&inmsg);
	पूर्ण जबतक ((!err) && (++count < CONTROLVM_MESSAGE_MAX));
	अगर (err != -EAGAIN)
		जाओ schedule_out;
	अगर (chipset_dev->controlvm_pending_msg_valid) अणु
		/*
		 * we throttled processing of a prior msg, so try to process
		 * it again rather than पढ़ोing a new one
		 */
		inmsg = chipset_dev->controlvm_pending_msg;
		chipset_dev->controlvm_pending_msg_valid = false;
		err = 0;
	पूर्ण अन्यथा अणु
		err = पढ़ो_controlvm_event(&inmsg);
	पूर्ण
	जबतक (!err) अणु
		chipset_dev->most_recent_message_jअगरfies = jअगरfies;
		err = handle_command(inmsg,
				     visorchannel_get_physaddr
				     (chipset_dev->controlvm_channel));
		अगर (err == -EAGAIN) अणु
			chipset_dev->controlvm_pending_msg = inmsg;
			chipset_dev->controlvm_pending_msg_valid = true;
			अवरोध;
		पूर्ण

		err = पढ़ो_controlvm_event(&inmsg);
	पूर्ण
	/* parahotplug_worker */
	parahotplug_process_list();

/*
 * The controlvm messages are sent in a bulk. If we start receiving messages, we
 * want the polling to be fast. If we करो not receive any message क्रम
 * MIN_IDLE_SECONDS, we can slow करोwn the polling.
 */
schedule_out:
	अगर (समय_after(jअगरfies, chipset_dev->most_recent_message_jअगरfies +
				(HZ * MIN_IDLE_SECONDS))) अणु
		/*
		 * it's been दीर्घer than MIN_IDLE_SECONDS since we processed
		 * our last controlvm message; slow करोwn the polling
		 */
		अगर (chipset_dev->poll_jअगरfies != POLLJIFFIES_CONTROLVM_SLOW)
			chipset_dev->poll_jअगरfies = POLLJIFFIES_CONTROLVM_SLOW;
	पूर्ण अन्यथा अणु
		अगर (chipset_dev->poll_jअगरfies != POLLJIFFIES_CONTROLVM_FAST)
			chipset_dev->poll_jअगरfies = POLLJIFFIES_CONTROLVM_FAST;
	पूर्ण
	schedule_delayed_work(&chipset_dev->periodic_controlvm_work,
			      chipset_dev->poll_jअगरfies);
पूर्ण

अटल पूर्णांक visorchipset_init(काष्ठा acpi_device *acpi_device)
अणु
	पूर्णांक err = -ENODEV;
	काष्ठा visorchannel *controlvm_channel;

	chipset_dev = kzalloc(माप(*chipset_dev), GFP_KERNEL);
	अगर (!chipset_dev)
		जाओ error;
	err = controlvm_channel_create(chipset_dev);
	अगर (err)
		जाओ error_मुक्त_chipset_dev;
	acpi_device->driver_data = chipset_dev;
	chipset_dev->acpi_device = acpi_device;
	chipset_dev->poll_jअगरfies = POLLJIFFIES_CONTROLVM_FAST;
	err = sysfs_create_groups(&chipset_dev->acpi_device->dev.kobj,
				  visorchipset_dev_groups);
	अगर (err < 0)
		जाओ error_destroy_channel;
	controlvm_channel = chipset_dev->controlvm_channel;
	अगर (!visor_check_channel(visorchannel_get_header(controlvm_channel),
				 &chipset_dev->acpi_device->dev,
				 &visor_controlvm_channel_guid,
				 "controlvm",
				 माप(काष्ठा visor_controlvm_channel),
				 VISOR_CONTROLVM_CHANNEL_VERSIONID,
				 VISOR_CHANNEL_SIGNATURE))
		जाओ error_delete_groups;
	/* अगर booting in a crash kernel */
	अगर (is_kdump_kernel())
		INIT_DELAYED_WORK(&chipset_dev->periodic_controlvm_work,
				  setup_crash_devices_work_queue);
	अन्यथा
		INIT_DELAYED_WORK(&chipset_dev->periodic_controlvm_work,
				  controlvm_periodic_work);
	chipset_dev->most_recent_message_jअगरfies = jअगरfies;
	chipset_dev->poll_jअगरfies = POLLJIFFIES_CONTROLVM_FAST;
	schedule_delayed_work(&chipset_dev->periodic_controlvm_work,
			      chipset_dev->poll_jअगरfies);
	err = visorbus_init();
	अगर (err < 0)
		जाओ error_cancel_work;
	वापस 0;

error_cancel_work:
	cancel_delayed_work_sync(&chipset_dev->periodic_controlvm_work);

error_delete_groups:
	sysfs_हटाओ_groups(&chipset_dev->acpi_device->dev.kobj,
			    visorchipset_dev_groups);

error_destroy_channel:
	visorchannel_destroy(chipset_dev->controlvm_channel);

error_मुक्त_chipset_dev:
	kमुक्त(chipset_dev);

error:
	dev_err(&acpi_device->dev, "failed with error %d\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक visorchipset_निकास(काष्ठा acpi_device *acpi_device)
अणु
	visorbus_निकास();
	cancel_delayed_work_sync(&chipset_dev->periodic_controlvm_work);
	sysfs_हटाओ_groups(&chipset_dev->acpi_device->dev.kobj,
			    visorchipset_dev_groups);
	visorchannel_destroy(chipset_dev->controlvm_channel);
	kमुक्त(chipset_dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id unisys_device_ids[] = अणु
	अणु"PNP0A07", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल काष्ठा acpi_driver unisys_acpi_driver = अणु
	.name = "unisys_acpi",
	.class = "unisys_acpi_class",
	.owner = THIS_MODULE,
	.ids = unisys_device_ids,
	.ops = अणु
		.add = visorchipset_init,
		.हटाओ = visorchipset_निकास,
	पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, unisys_device_ids);

अटल __init पूर्णांक visorutil_spar_detect(व्योम)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;

	अगर (boot_cpu_has(X86_FEATURE_HYPERVISOR)) अणु
		/* check the ID */
		cpuid(UNISYS_VISOR_LEAF_ID, &eax, &ebx, &ecx, &edx);
		वापस  (ebx == UNISYS_VISOR_ID_EBX) &&
			(ecx == UNISYS_VISOR_ID_ECX) &&
			(edx == UNISYS_VISOR_ID_EDX);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init init_unisys(व्योम)
अणु
	पूर्णांक result;

	अगर (!visorutil_spar_detect())
		वापस -ENODEV;
	result = acpi_bus_रेजिस्टर_driver(&unisys_acpi_driver);
	अगर (result)
		वापस -ENODEV;
	pr_info("Unisys Visorchipset Driver Loaded.\n");
	वापस 0;
पूर्ण;

अटल व्योम __निकास निकास_unisys(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&unisys_acpi_driver);
पूर्ण

module_init(init_unisys);
module_निकास(निकास_unisys);

MODULE_AUTHOR("Unisys");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("s-Par visorbus driver for virtual device buses");
