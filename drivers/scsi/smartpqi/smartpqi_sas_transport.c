<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    driver क्रम Microsemi PQI-based storage controllers
 *    Copyright (c) 2019-2020 Microchip Technology Inc. and its subsidiaries
 *    Copyright (c) 2016-2018 Microsemi Corporation
 *    Copyright (c) 2016 PMC-Sierra, Inc.
 *
 *    Questions/Comments/Bugfixes to storagedev@microchip.com
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/bsg-lib.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_transport_sas.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "smartpqi.h"

अटल काष्ठा pqi_sas_phy *pqi_alloc_sas_phy(काष्ठा pqi_sas_port *pqi_sas_port)
अणु
	काष्ठा pqi_sas_phy *pqi_sas_phy;
	काष्ठा sas_phy *phy;

	pqi_sas_phy = kzalloc(माप(*pqi_sas_phy), GFP_KERNEL);
	अगर (!pqi_sas_phy)
		वापस शून्य;

	phy = sas_phy_alloc(pqi_sas_port->parent_node->parent_dev,
		pqi_sas_port->next_phy_index);
	अगर (!phy) अणु
		kमुक्त(pqi_sas_phy);
		वापस शून्य;
	पूर्ण

	pqi_sas_port->next_phy_index++;
	pqi_sas_phy->phy = phy;
	pqi_sas_phy->parent_port = pqi_sas_port;

	वापस pqi_sas_phy;
पूर्ण

अटल व्योम pqi_मुक्त_sas_phy(काष्ठा pqi_sas_phy *pqi_sas_phy)
अणु
	काष्ठा sas_phy *phy = pqi_sas_phy->phy;

	sas_port_delete_phy(pqi_sas_phy->parent_port->port, phy);
	अगर (pqi_sas_phy->added_to_port)
		list_del(&pqi_sas_phy->phy_list_entry);
	sas_phy_delete(phy);
	kमुक्त(pqi_sas_phy);
पूर्ण

अटल पूर्णांक pqi_sas_port_add_phy(काष्ठा pqi_sas_phy *pqi_sas_phy)
अणु
	पूर्णांक rc;
	काष्ठा pqi_sas_port *pqi_sas_port;
	काष्ठा sas_phy *phy;
	काष्ठा sas_identअगरy *identअगरy;

	pqi_sas_port = pqi_sas_phy->parent_port;
	phy = pqi_sas_phy->phy;

	identअगरy = &phy->identअगरy;
	स_रखो(identअगरy, 0, माप(*identअगरy));
	identअगरy->sas_address = pqi_sas_port->sas_address;
	identअगरy->device_type = SAS_END_DEVICE;
	identअगरy->initiator_port_protocols = SAS_PROTOCOL_ALL;
	identअगरy->target_port_protocols = SAS_PROTOCOL_ALL;
	phy->minimum_linkrate_hw = SAS_LINK_RATE_UNKNOWN;
	phy->maximum_linkrate_hw = SAS_LINK_RATE_UNKNOWN;
	phy->minimum_linkrate = SAS_LINK_RATE_UNKNOWN;
	phy->maximum_linkrate = SAS_LINK_RATE_UNKNOWN;
	phy->negotiated_linkrate = SAS_LINK_RATE_UNKNOWN;

	rc = sas_phy_add(pqi_sas_phy->phy);
	अगर (rc)
		वापस rc;

	sas_port_add_phy(pqi_sas_port->port, pqi_sas_phy->phy);
	list_add_tail(&pqi_sas_phy->phy_list_entry,
		&pqi_sas_port->phy_list_head);
	pqi_sas_phy->added_to_port = true;

	वापस 0;
पूर्ण

अटल पूर्णांक pqi_sas_port_add_rphy(काष्ठा pqi_sas_port *pqi_sas_port,
	काष्ठा sas_rphy *rphy)
अणु
	काष्ठा sas_identअगरy *identअगरy;

	identअगरy = &rphy->identअगरy;
	identअगरy->sas_address = pqi_sas_port->sas_address;

	identअगरy->initiator_port_protocols = SAS_PROTOCOL_ALL;
	identअगरy->target_port_protocols = SAS_PROTOCOL_STP;

	अगर (pqi_sas_port->device) अणु
		identअगरy->phy_identअगरier = pqi_sas_port->device->phy_id;
		चयन (pqi_sas_port->device->device_type) अणु
		हाल SA_DEVICE_TYPE_SAS:
		हाल SA_DEVICE_TYPE_SES:
		हाल SA_DEVICE_TYPE_NVME:
			identअगरy->target_port_protocols = SAS_PROTOCOL_SSP;
			अवरोध;
		हाल SA_DEVICE_TYPE_EXPANDER_SMP:
			identअगरy->target_port_protocols = SAS_PROTOCOL_SMP;
			अवरोध;
		हाल SA_DEVICE_TYPE_SATA:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस sas_rphy_add(rphy);
पूर्ण

अटल काष्ठा sas_rphy *pqi_sas_rphy_alloc(काष्ठा pqi_sas_port *pqi_sas_port)
अणु
	अगर (pqi_sas_port->device && pqi_sas_port->device->is_expander_smp_device)
		वापस sas_expander_alloc(pqi_sas_port->port,
				SAS_FANOUT_EXPANDER_DEVICE);

	वापस sas_end_device_alloc(pqi_sas_port->port);
पूर्ण

अटल काष्ठा pqi_sas_port *pqi_alloc_sas_port(
	काष्ठा pqi_sas_node *pqi_sas_node, u64 sas_address,
	काष्ठा pqi_scsi_dev *device)
अणु
	पूर्णांक rc;
	काष्ठा pqi_sas_port *pqi_sas_port;
	काष्ठा sas_port *port;

	pqi_sas_port = kzalloc(माप(*pqi_sas_port), GFP_KERNEL);
	अगर (!pqi_sas_port)
		वापस शून्य;

	INIT_LIST_HEAD(&pqi_sas_port->phy_list_head);
	pqi_sas_port->parent_node = pqi_sas_node;

	port = sas_port_alloc_num(pqi_sas_node->parent_dev);
	अगर (!port)
		जाओ मुक्त_pqi_port;

	rc = sas_port_add(port);
	अगर (rc)
		जाओ मुक्त_sas_port;

	pqi_sas_port->port = port;
	pqi_sas_port->sas_address = sas_address;
	pqi_sas_port->device = device;
	list_add_tail(&pqi_sas_port->port_list_entry,
		&pqi_sas_node->port_list_head);

	वापस pqi_sas_port;

मुक्त_sas_port:
	sas_port_मुक्त(port);
मुक्त_pqi_port:
	kमुक्त(pqi_sas_port);

	वापस शून्य;
पूर्ण

अटल व्योम pqi_मुक्त_sas_port(काष्ठा pqi_sas_port *pqi_sas_port)
अणु
	काष्ठा pqi_sas_phy *pqi_sas_phy;
	काष्ठा pqi_sas_phy *next;

	list_क्रम_each_entry_safe(pqi_sas_phy, next,
		&pqi_sas_port->phy_list_head, phy_list_entry)
			pqi_मुक्त_sas_phy(pqi_sas_phy);

	sas_port_delete(pqi_sas_port->port);
	list_del(&pqi_sas_port->port_list_entry);
	kमुक्त(pqi_sas_port);
पूर्ण

अटल काष्ठा pqi_sas_node *pqi_alloc_sas_node(काष्ठा device *parent_dev)
अणु
	काष्ठा pqi_sas_node *pqi_sas_node;

	pqi_sas_node = kzalloc(माप(*pqi_sas_node), GFP_KERNEL);
	अगर (pqi_sas_node) अणु
		pqi_sas_node->parent_dev = parent_dev;
		INIT_LIST_HEAD(&pqi_sas_node->port_list_head);
	पूर्ण

	वापस pqi_sas_node;
पूर्ण

अटल व्योम pqi_मुक्त_sas_node(काष्ठा pqi_sas_node *pqi_sas_node)
अणु
	काष्ठा pqi_sas_port *pqi_sas_port;
	काष्ठा pqi_sas_port *next;

	अगर (!pqi_sas_node)
		वापस;

	list_क्रम_each_entry_safe(pqi_sas_port, next,
		&pqi_sas_node->port_list_head, port_list_entry)
			pqi_मुक्त_sas_port(pqi_sas_port);

	kमुक्त(pqi_sas_node);
पूर्ण

काष्ठा pqi_scsi_dev *pqi_find_device_by_sas_rphy(
	काष्ठा pqi_ctrl_info *ctrl_info, काष्ठा sas_rphy *rphy)
अणु
	काष्ठा pqi_scsi_dev *device;

	list_क्रम_each_entry(device, &ctrl_info->scsi_device_list,
		scsi_device_list_entry) अणु
		अगर (!device->sas_port)
			जारी;
		अगर (device->sas_port->rphy == rphy)
			वापस device;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक pqi_add_sas_host(काष्ठा Scsi_Host *shost, काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	काष्ठा device *parent_dev;
	काष्ठा pqi_sas_node *pqi_sas_node;
	काष्ठा pqi_sas_port *pqi_sas_port;
	काष्ठा pqi_sas_phy *pqi_sas_phy;

	parent_dev = &shost->shost_dev;

	pqi_sas_node = pqi_alloc_sas_node(parent_dev);
	अगर (!pqi_sas_node)
		वापस -ENOMEM;

	pqi_sas_port = pqi_alloc_sas_port(pqi_sas_node,
		ctrl_info->sas_address, शून्य);
	अगर (!pqi_sas_port) अणु
		rc = -ENODEV;
		जाओ मुक्त_sas_node;
	पूर्ण

	pqi_sas_phy = pqi_alloc_sas_phy(pqi_sas_port);
	अगर (!pqi_sas_phy) अणु
		rc = -ENODEV;
		जाओ मुक्त_sas_port;
	पूर्ण

	rc = pqi_sas_port_add_phy(pqi_sas_phy);
	अगर (rc)
		जाओ मुक्त_sas_phy;

	ctrl_info->sas_host = pqi_sas_node;

	वापस 0;

मुक्त_sas_phy:
	pqi_मुक्त_sas_phy(pqi_sas_phy);
मुक्त_sas_port:
	pqi_मुक्त_sas_port(pqi_sas_port);
मुक्त_sas_node:
	pqi_मुक्त_sas_node(pqi_sas_node);

	वापस rc;
पूर्ण

व्योम pqi_delete_sas_host(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	pqi_मुक्त_sas_node(ctrl_info->sas_host);
पूर्ण

पूर्णांक pqi_add_sas_device(काष्ठा pqi_sas_node *pqi_sas_node,
	काष्ठा pqi_scsi_dev *device)
अणु
	पूर्णांक rc;
	काष्ठा pqi_sas_port *pqi_sas_port;
	काष्ठा sas_rphy *rphy;

	pqi_sas_port = pqi_alloc_sas_port(pqi_sas_node,
		device->sas_address, device);
	अगर (!pqi_sas_port)
		वापस -ENOMEM;

	rphy = pqi_sas_rphy_alloc(pqi_sas_port);
	अगर (!rphy) अणु
		rc = -ENODEV;
		जाओ मुक्त_sas_port;
	पूर्ण

	pqi_sas_port->rphy = rphy;
	device->sas_port = pqi_sas_port;

	rc = pqi_sas_port_add_rphy(pqi_sas_port, rphy);
	अगर (rc)
		जाओ मुक्त_sas_port;

	वापस 0;

मुक्त_sas_port:
	pqi_मुक्त_sas_port(pqi_sas_port);
	device->sas_port = शून्य;

	वापस rc;
पूर्ण

व्योम pqi_हटाओ_sas_device(काष्ठा pqi_scsi_dev *device)
अणु
	अगर (device->sas_port) अणु
		pqi_मुक्त_sas_port(device->sas_port);
		device->sas_port = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक pqi_sas_get_linkerrors(काष्ठा sas_phy *phy)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pqi_sas_get_enclosure_identअगरier(काष्ठा sas_rphy *rphy,
	u64 *identअगरier)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;
	काष्ठा Scsi_Host *shost;
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा pqi_scsi_dev *found_device;
	काष्ठा pqi_scsi_dev *device;

	अगर (!rphy)
		वापस -ENODEV;

	shost = rphy_to_shost(rphy);
	ctrl_info = shost_to_hba(shost);
	spin_lock_irqsave(&ctrl_info->scsi_device_list_lock, flags);
	found_device = pqi_find_device_by_sas_rphy(ctrl_info, rphy);

	अगर (!found_device) अणु
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (found_device->devtype == TYPE_ENCLOSURE) अणु
		*identअगरier = get_unaligned_be64(&found_device->wwid);
		rc = 0;
		जाओ out;
	पूर्ण

	अगर (found_device->box_index == 0xff ||
		found_device->phys_box_on_bus == 0 ||
		found_device->bay == 0xff) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	list_क्रम_each_entry(device, &ctrl_info->scsi_device_list,
		scsi_device_list_entry) अणु
		अगर (device->devtype == TYPE_ENCLOSURE &&
			device->box_index == found_device->box_index &&
			device->phys_box_on_bus ==
				found_device->phys_box_on_bus &&
			स_भेद(device->phys_connector,
				found_device->phys_connector, 2) == 0) अणु
			*identअगरier =
				get_unaligned_be64(&device->wwid);
			rc = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (found_device->phy_connected_dev_type != SA_DEVICE_TYPE_CONTROLLER) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	list_क्रम_each_entry(device, &ctrl_info->scsi_device_list,
		scsi_device_list_entry) अणु
		अगर (device->devtype == TYPE_ENCLOSURE &&
			CISS_GET_DRIVE_NUMBER(device->scsi3addr) ==
				PQI_VSEP_CISS_BTL) अणु
			*identअगरier = get_unaligned_be64(&device->wwid);
			rc = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	rc = -EINVAL;
out:
	spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);

	वापस rc;
पूर्ण

अटल पूर्णांक pqi_sas_get_bay_identअगरier(काष्ठा sas_rphy *rphy)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा pqi_scsi_dev *device;
	काष्ठा Scsi_Host *shost;

	अगर (!rphy)
		वापस -ENODEV;

	shost = rphy_to_shost(rphy);
	ctrl_info = shost_to_hba(shost);
	spin_lock_irqsave(&ctrl_info->scsi_device_list_lock, flags);
	device = pqi_find_device_by_sas_rphy(ctrl_info, rphy);

	अगर (!device) अणु
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (device->bay == 0xff)
		rc = -EINVAL;
	अन्यथा
		rc = device->bay;

out:
	spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);

	वापस rc;
पूर्ण

अटल पूर्णांक pqi_sas_phy_reset(काष्ठा sas_phy *phy, पूर्णांक hard_reset)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pqi_sas_phy_enable(काष्ठा sas_phy *phy, पूर्णांक enable)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pqi_sas_phy_setup(काष्ठा sas_phy *phy)
अणु
	वापस 0;
पूर्ण

अटल व्योम pqi_sas_phy_release(काष्ठा sas_phy *phy)
अणु
पूर्ण

अटल पूर्णांक pqi_sas_phy_speed(काष्ठा sas_phy *phy,
	काष्ठा sas_phy_linkrates *rates)
अणु
	वापस -EINVAL;
पूर्ण

#घोषणा CSMI_IOCTL_TIMEOUT	60
#घोषणा SMP_CRC_FIELD_LENGTH	4

अटल काष्ठा bmic_csmi_smp_passthru_buffer *
pqi_build_csmi_smp_passthru_buffer(काष्ठा sas_rphy *rphy,
	काष्ठा bsg_job *job)
अणु
	काष्ठा bmic_csmi_smp_passthru_buffer *smp_buf;
	काष्ठा bmic_csmi_ioctl_header *ioctl_header;
	काष्ठा bmic_csmi_smp_passthru *parameters;
	u32 req_size;
	u32 resp_size;

	smp_buf = kzalloc(माप(*smp_buf), GFP_KERNEL);
	अगर (!smp_buf)
		वापस शून्य;

	req_size = job->request_payload.payload_len;
	resp_size = job->reply_payload.payload_len;

	ioctl_header = &smp_buf->ioctl_header;
	put_unaligned_le32(माप(smp_buf->ioctl_header),
		&ioctl_header->header_length);
	put_unaligned_le32(CSMI_IOCTL_TIMEOUT, &ioctl_header->समयout);
	put_unaligned_le32(CSMI_CC_SAS_SMP_PASSTHRU,
		&ioctl_header->control_code);
	put_unaligned_le32(माप(smp_buf->parameters), &ioctl_header->length);

	parameters = &smp_buf->parameters;
	parameters->phy_identअगरier = rphy->identअगरy.phy_identअगरier;
	parameters->port_identअगरier = 0;
	parameters->connection_rate = 0;
	put_unaligned_be64(rphy->identअगरy.sas_address,
		&parameters->destination_sas_address);

	अगर (req_size > SMP_CRC_FIELD_LENGTH)
		req_size -= SMP_CRC_FIELD_LENGTH;

	put_unaligned_le32(req_size, &parameters->request_length);
	put_unaligned_le32(resp_size, &parameters->response_length);

	sg_copy_to_buffer(job->request_payload.sg_list,
		job->reply_payload.sg_cnt, &parameters->request,
		req_size);

	वापस smp_buf;
पूर्ण

अटल अचिन्हित पूर्णांक pqi_build_sas_smp_handler_reply(
	काष्ठा bmic_csmi_smp_passthru_buffer *smp_buf, काष्ठा bsg_job *job,
	काष्ठा pqi_raid_error_info *error_info)
अणु
	sg_copy_from_buffer(job->reply_payload.sg_list,
		job->reply_payload.sg_cnt, &smp_buf->parameters.response,
		le32_to_cpu(smp_buf->parameters.response_length));

	job->reply_len = le16_to_cpu(error_info->sense_data_length);
	स_नकल(job->reply, error_info->data,
		le16_to_cpu(error_info->sense_data_length));

	वापस job->reply_payload.payload_len -
		get_unaligned_le32(&error_info->data_in_transferred);
पूर्ण

व्योम pqi_sas_smp_handler(काष्ठा bsg_job *job, काष्ठा Scsi_Host *shost,
	काष्ठा sas_rphy *rphy)
अणु
	पूर्णांक rc;
	काष्ठा pqi_ctrl_info *ctrl_info;
	काष्ठा bmic_csmi_smp_passthru_buffer *smp_buf;
	काष्ठा pqi_raid_error_info error_info;
	अचिन्हित पूर्णांक reslen = 0;

	ctrl_info = shost_to_hba(shost);

	अगर (job->reply_payload.payload_len == 0) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (!rphy) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (rphy->identअगरy.device_type != SAS_FANOUT_EXPANDER_DEVICE) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (job->request_payload.sg_cnt > 1 || job->reply_payload.sg_cnt > 1) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	smp_buf = pqi_build_csmi_smp_passthru_buffer(rphy, job);
	अगर (!smp_buf) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	rc = pqi_csmi_smp_passthru(ctrl_info, smp_buf, माप(*smp_buf),
		&error_info);
	अगर (rc)
		जाओ out;

	reslen = pqi_build_sas_smp_handler_reply(smp_buf, job, &error_info);

out:
	bsg_job_करोne(job, rc, reslen);
पूर्ण
काष्ठा sas_function_ढाँचा pqi_sas_transport_functions = अणु
	.get_linkerrors = pqi_sas_get_linkerrors,
	.get_enclosure_identअगरier = pqi_sas_get_enclosure_identअगरier,
	.get_bay_identअगरier = pqi_sas_get_bay_identअगरier,
	.phy_reset = pqi_sas_phy_reset,
	.phy_enable = pqi_sas_phy_enable,
	.phy_setup = pqi_sas_phy_setup,
	.phy_release = pqi_sas_phy_release,
	.set_phy_speed = pqi_sas_phy_speed,
	.smp_handler = pqi_sas_smp_handler,
पूर्ण;
