<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Serial Attached SCSI (SAS) Expander discovery and configuration
 *
 * Copyright (C) 2007 James E.J. Bottomley
 *		<James.Bottomley@HansenPartnership.com>
 */
#समावेश <linux/scatterlist.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

#समावेश "sas_internal.h"

#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_sas.h>
#समावेश "../scsi_sas_internal.h"

अटल व्योम sas_host_smp_discover(काष्ठा sas_ha_काष्ठा *sas_ha, u8 *resp_data,
				  u8 phy_id)
अणु
	काष्ठा sas_phy *phy;
	काष्ठा sas_rphy *rphy;

	अगर (phy_id >= sas_ha->num_phys) अणु
		resp_data[2] = SMP_RESP_NO_PHY;
		वापस;
	पूर्ण
	resp_data[2] = SMP_RESP_FUNC_ACC;

	phy = sas_ha->sas_phy[phy_id]->phy;
	resp_data[9] = phy_id;
	resp_data[13] = phy->negotiated_linkrate;
	स_नकल(resp_data + 16, sas_ha->sas_addr, SAS_ADDR_SIZE);
	स_नकल(resp_data + 24, sas_ha->sas_phy[phy_id]->attached_sas_addr,
	       SAS_ADDR_SIZE);
	resp_data[40] = (phy->minimum_linkrate << 4) |
		phy->minimum_linkrate_hw;
	resp_data[41] = (phy->maximum_linkrate << 4) |
		phy->maximum_linkrate_hw;

	अगर (!sas_ha->sas_phy[phy_id]->port ||
	    !sas_ha->sas_phy[phy_id]->port->port_dev)
		वापस;

	rphy = sas_ha->sas_phy[phy_id]->port->port_dev->rphy;
	resp_data[12] = rphy->identअगरy.device_type << 4;
	resp_data[14] = rphy->identअगरy.initiator_port_protocols;
	resp_data[15] = rphy->identअगरy.target_port_protocols;
पूर्ण

/**
 * to_sas_gpio_gp_bit - given the gpio frame data find the byte/bit position of 'od'
 * @od: od bit to find
 * @data: incoming bitstream (from frame)
 * @index: requested data रेजिस्टर index (from frame)
 * @count: total number of रेजिस्टरs in the bitstream (from frame)
 * @bit: bit position of 'od' in the वापसed byte
 *
 * वापसs शून्य अगर 'od' is not in 'data'
 *
 * From SFF-8485 v0.7:
 * "In GPIO_TX[1], bit 0 of byte 3 contains the first bit (i.e., OD0.0)
 *  and bit 7 of byte 0 contains the 32nd bit (i.e., OD10.1).
 *
 *  In GPIO_TX[2], bit 0 of byte 3 contains the 33rd bit (i.e., OD10.2)
 *  and bit 7 of byte 0 contains the 64th bit (i.e., OD21.0)."
 *
 * The general-purpose (raw-bitstream) RX रेजिस्टरs have the same layout
 * although 'od' is renamed 'id' for 'input data'.
 *
 * SFF-8489 defines the behavior of the LEDs in response to the 'od' values.
 */
अटल u8 *to_sas_gpio_gp_bit(अचिन्हित पूर्णांक od, u8 *data, u8 index, u8 count, u8 *bit)
अणु
	अचिन्हित पूर्णांक reg;
	u8 byte;

	/* gp रेजिस्टरs start at index 1 */
	अगर (index == 0)
		वापस शून्य;

	index--; /* make index 0-based */
	अगर (od < index * 32)
		वापस शून्य;

	od -= index * 32;
	reg = od >> 5;

	अगर (reg >= count)
		वापस शून्य;

	od &= (1 << 5) - 1;
	byte = 3 - (od >> 3);
	*bit = od & ((1 << 3) - 1);

	वापस &data[reg * 4 + byte];
पूर्ण

पूर्णांक try_test_sas_gpio_gp_bit(अचिन्हित पूर्णांक od, u8 *data, u8 index, u8 count)
अणु
	u8 *byte;
	u8 bit;

	byte = to_sas_gpio_gp_bit(od, data, index, count, &bit);
	अगर (!byte)
		वापस -1;

	वापस (*byte >> bit) & 1;
पूर्ण
EXPORT_SYMBOL(try_test_sas_gpio_gp_bit);

अटल पूर्णांक sas_host_smp_ग_लिखो_gpio(काष्ठा sas_ha_काष्ठा *sas_ha, u8 *resp_data,
				   u8 reg_type, u8 reg_index, u8 reg_count,
				   u8 *req_data)
अणु
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(sas_ha->core.shost->transportt);
	पूर्णांक written;

	अगर (i->dft->lldd_ग_लिखो_gpio == शून्य) अणु
		resp_data[2] = SMP_RESP_FUNC_UNK;
		वापस 0;
	पूर्ण

	written = i->dft->lldd_ग_लिखो_gpio(sas_ha, reg_type, reg_index,
					  reg_count, req_data);

	अगर (written < 0) अणु
		resp_data[2] = SMP_RESP_FUNC_FAILED;
		written = 0;
	पूर्ण अन्यथा
		resp_data[2] = SMP_RESP_FUNC_ACC;

	वापस written;
पूर्ण

अटल व्योम sas_report_phy_sata(काष्ठा sas_ha_काष्ठा *sas_ha, u8 *resp_data,
				u8 phy_id)
अणु
	काष्ठा sas_rphy *rphy;
	काष्ठा dev_to_host_fis *fis;
	पूर्णांक i;

	अगर (phy_id >= sas_ha->num_phys) अणु
		resp_data[2] = SMP_RESP_NO_PHY;
		वापस;
	पूर्ण

	resp_data[2] = SMP_RESP_PHY_NO_SATA;

	अगर (!sas_ha->sas_phy[phy_id]->port)
		वापस;

	rphy = sas_ha->sas_phy[phy_id]->port->port_dev->rphy;
	fis = (काष्ठा dev_to_host_fis *)
		sas_ha->sas_phy[phy_id]->port->port_dev->frame_rcvd;
	अगर (rphy->identअगरy.target_port_protocols != SAS_PROTOCOL_SATA)
		वापस;

	resp_data[2] = SMP_RESP_FUNC_ACC;
	resp_data[9] = phy_id;
	स_नकल(resp_data + 16, sas_ha->sas_phy[phy_id]->attached_sas_addr,
	       SAS_ADDR_SIZE);

	/* check to see अगर we have a valid d2h fis */
	अगर (fis->fis_type != 0x34)
		वापस;

	/* the d2h fis is required by the standard to be in LE क्रमmat */
	क्रम (i = 0; i < 20; i += 4) अणु
		u8 *dst = resp_data + 24 + i, *src =
			&sas_ha->sas_phy[phy_id]->port->port_dev->frame_rcvd[i];
		dst[0] = src[3];
		dst[1] = src[2];
		dst[2] = src[1];
		dst[3] = src[0];
	पूर्ण
पूर्ण

अटल व्योम sas_phy_control(काष्ठा sas_ha_काष्ठा *sas_ha, u8 phy_id,
			    u8 phy_op, क्रमागत sas_linkrate min,
			    क्रमागत sas_linkrate max, u8 *resp_data)
अणु
	काष्ठा sas_पूर्णांकernal *i =
		to_sas_पूर्णांकernal(sas_ha->core.shost->transportt);
	काष्ठा sas_phy_linkrates rates;
	काष्ठा asd_sas_phy *asd_phy;

	अगर (phy_id >= sas_ha->num_phys) अणु
		resp_data[2] = SMP_RESP_NO_PHY;
		वापस;
	पूर्ण

	asd_phy = sas_ha->sas_phy[phy_id];
	चयन (phy_op) अणु
	हाल PHY_FUNC_NOP:
	हाल PHY_FUNC_LINK_RESET:
	हाल PHY_FUNC_HARD_RESET:
	हाल PHY_FUNC_DISABLE:
	हाल PHY_FUNC_CLEAR_ERROR_LOG:
	हाल PHY_FUNC_CLEAR_AFFIL:
	हाल PHY_FUNC_TX_SATA_PS_SIGNAL:
		अवरोध;

	शेष:
		resp_data[2] = SMP_RESP_PHY_UNK_OP;
		वापस;
	पूर्ण

	rates.minimum_linkrate = min;
	rates.maximum_linkrate = max;

	/* filter reset requests through libata eh */
	अगर (phy_op == PHY_FUNC_LINK_RESET && sas_try_ata_reset(asd_phy) == 0) अणु
		resp_data[2] = SMP_RESP_FUNC_ACC;
		वापस;
	पूर्ण

	अगर (i->dft->lldd_control_phy(asd_phy, phy_op, &rates))
		resp_data[2] = SMP_RESP_FUNC_FAILED;
	अन्यथा
		resp_data[2] = SMP_RESP_FUNC_ACC;
पूर्ण

व्योम sas_smp_host_handler(काष्ठा bsg_job *job, काष्ठा Scsi_Host *shost)
अणु
	काष्ठा sas_ha_काष्ठा *sas_ha = SHOST_TO_SAS_HA(shost);
	u8 *req_data, *resp_data;
	अचिन्हित पूर्णांक reslen = 0;
	पूर्णांक error = -EINVAL;

	/* eight is the minimum size क्रम request and response frames */
	अगर (job->request_payload.payload_len < 8 ||
	    job->reply_payload.payload_len < 8)
		जाओ out;

	error = -ENOMEM;
	req_data = kzalloc(job->request_payload.payload_len, GFP_KERNEL);
	अगर (!req_data)
		जाओ out;
	sg_copy_to_buffer(job->request_payload.sg_list,
			  job->request_payload.sg_cnt, req_data,
			  job->request_payload.payload_len);

	/* make sure frame can always be built ... we copy
	 * back only the requested length */
	resp_data = kzalloc(max(job->reply_payload.payload_len, 128U),
			GFP_KERNEL);
	अगर (!resp_data)
		जाओ out_मुक्त_req;

	error = -EINVAL;
	अगर (req_data[0] != SMP_REQUEST)
		जाओ out_मुक्त_resp;

	/* set up शेष करोn't know response */
	resp_data[0] = SMP_RESPONSE;
	resp_data[1] = req_data[1];
	resp_data[2] = SMP_RESP_FUNC_UNK;

	चयन (req_data[1]) अणु
	हाल SMP_REPORT_GENERAL:
		resp_data[2] = SMP_RESP_FUNC_ACC;
		resp_data[9] = sas_ha->num_phys;
		reslen = 32;
		अवरोध;

	हाल SMP_REPORT_MANUF_INFO:
		resp_data[2] = SMP_RESP_FUNC_ACC;
		स_नकल(resp_data + 12, shost->hostt->name,
		       SAS_EXPANDER_VENDOR_ID_LEN);
		स_नकल(resp_data + 20, "libsas virt phy",
		       SAS_EXPANDER_PRODUCT_ID_LEN);
		reslen = 64;
		अवरोध;

	हाल SMP_READ_GPIO_REG:
		/* FIXME: need GPIO support in the transport class */
		अवरोध;

	हाल SMP_DISCOVER:
		अगर (job->request_payload.payload_len < 16)
			जाओ out_मुक्त_resp;
		sas_host_smp_discover(sas_ha, resp_data, req_data[9]);
		reslen = 56;
		अवरोध;

	हाल SMP_REPORT_PHY_ERR_LOG:
		/* FIXME: could implement this with additional
		 * libsas callbacks providing the HW supports it */
		अवरोध;

	हाल SMP_REPORT_PHY_SATA:
		अगर (job->request_payload.payload_len < 16)
			जाओ out_मुक्त_resp;
		sas_report_phy_sata(sas_ha, resp_data, req_data[9]);
		reslen = 60;
		अवरोध;

	हाल SMP_REPORT_ROUTE_INFO:
		/* Can't implement; hosts have no routes */
		अवरोध;

	हाल SMP_WRITE_GPIO_REG: अणु
		/* SFF-8485 v0.7 */
		स्थिर पूर्णांक base_frame_size = 11;
		पूर्णांक to_ग_लिखो = req_data[4];

		अगर (job->request_payload.payload_len <
				base_frame_size + to_ग_लिखो * 4) अणु
			resp_data[2] = SMP_RESP_INV_FRM_LEN;
			अवरोध;
		पूर्ण

		to_ग_लिखो = sas_host_smp_ग_लिखो_gpio(sas_ha, resp_data, req_data[2],
						   req_data[3], to_ग_लिखो, &req_data[8]);
		reslen = 8;
		अवरोध;
	पूर्ण

	हाल SMP_CONF_ROUTE_INFO:
		/* Can't implement; hosts have no routes */
		अवरोध;

	हाल SMP_PHY_CONTROL:
		अगर (job->request_payload.payload_len < 44)
			जाओ out_मुक्त_resp;
		sas_phy_control(sas_ha, req_data[9], req_data[10],
				req_data[32] >> 4, req_data[33] >> 4,
				resp_data);
		reslen = 8;
		अवरोध;

	हाल SMP_PHY_TEST_FUNCTION:
		/* FIXME: should this be implemented? */
		अवरोध;

	शेष:
		/* probably a 2.0 function */
		अवरोध;
	पूर्ण

	sg_copy_from_buffer(job->reply_payload.sg_list,
			    job->reply_payload.sg_cnt, resp_data,
			    job->reply_payload.payload_len);

	error = 0;
out_मुक्त_resp:
	kमुक्त(resp_data);
out_मुक्त_req:
	kमुक्त(req_data);
out:
	bsg_job_करोne(job, error, reslen);
पूर्ण
