<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ISHTP client driver क्रम HID (ISH)
 *
 * Copyright (c) 2014-2016, Intel Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/hid.h>
#समावेश <linux/पूर्णांकel-ish-client-अगर.h>
#समावेश <linux/sched.h>
#समावेश "ishtp-hid.h"

/* Rx ring buffer pool size */
#घोषणा HID_CL_RX_RING_SIZE	32
#घोषणा HID_CL_TX_RING_SIZE	16

#घोषणा cl_data_to_dev(client_data) ishtp_device(client_data->cl_device)

/**
 * report_bad_packets() - Report bad packets
 * @hid_ishtp_cl:	Client instance to get stats
 * @recv_buf:		Raw received host पूर्णांकerface message
 * @cur_pos:		Current position index in payload
 * @payload_len:	Length of payload expected
 *
 * Dumps error in हाल bad packet is received
 */
अटल व्योम report_bad_packet(काष्ठा ishtp_cl *hid_ishtp_cl, व्योम *recv_buf,
			      माप_प्रकार cur_pos,  माप_प्रकार payload_len)
अणु
	काष्ठा hostअगर_msg *recv_msg = recv_buf;
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(hid_ishtp_cl);

	dev_err(cl_data_to_dev(client_data), "[hid-ish]: BAD packet %02X\n"
		"total_bad=%u cur_pos=%u\n"
		"[%02X %02X %02X %02X]\n"
		"payload_len=%u\n"
		"multi_packet_cnt=%u\n"
		"is_response=%02X\n",
		recv_msg->hdr.command, client_data->bad_recv_cnt,
		(अचिन्हित पूर्णांक)cur_pos,
		((अचिन्हित अक्षर *)recv_msg)[0], ((अचिन्हित अक्षर *)recv_msg)[1],
		((अचिन्हित अक्षर *)recv_msg)[2], ((अचिन्हित अक्षर *)recv_msg)[3],
		(अचिन्हित पूर्णांक)payload_len, client_data->multi_packet_cnt,
		recv_msg->hdr.command & ~CMD_MASK);
पूर्ण

/**
 * process_recv() - Received and parse incoming packet
 * @hid_ishtp_cl:	Client instance to get stats
 * @recv_buf:		Raw received host पूर्णांकerface message
 * @data_len:		length of the message
 *
 * Parse the incoming packet. If it is a response packet then it will update
 * per instance flags and wake up the caller रुकोing to क्रम the response.
 */
अटल व्योम process_recv(काष्ठा ishtp_cl *hid_ishtp_cl, व्योम *recv_buf,
			 माप_प्रकार data_len)
अणु
	काष्ठा hostअगर_msg *recv_msg;
	अचिन्हित अक्षर *payload;
	काष्ठा device_info *dev_info;
	पूर्णांक i, j;
	माप_प्रकार	payload_len, total_len, cur_pos, raw_len;
	पूर्णांक report_type;
	काष्ठा report_list *reports_list;
	अक्षर *reports;
	माप_प्रकार report_len;
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(hid_ishtp_cl);
	पूर्णांक curr_hid_dev = client_data->cur_hid_dev;
	काष्ठा ishtp_hid_data *hid_data = शून्य;
	काष्ठा hid_device *hid = शून्य;

	payload = recv_buf + माप(काष्ठा hostअगर_msg_hdr);
	total_len = data_len;
	cur_pos = 0;

	करो अणु
		अगर (cur_pos + माप(काष्ठा hostअगर_msg) > total_len) अणु
			dev_err(cl_data_to_dev(client_data),
				"[hid-ish]: error, received %u which is less than data header %u\n",
				(अचिन्हित पूर्णांक)data_len,
				(अचिन्हित पूर्णांक)माप(काष्ठा hostअगर_msg_hdr));
			++client_data->bad_recv_cnt;
			ish_hw_reset(ishtp_get_ishtp_device(hid_ishtp_cl));
			अवरोध;
		पूर्ण

		recv_msg = (काष्ठा hostअगर_msg *)(recv_buf + cur_pos);
		payload_len = recv_msg->hdr.size;

		/* Sanity checks */
		अगर (cur_pos + payload_len + माप(काष्ठा hostअगर_msg) >
				total_len) अणु
			++client_data->bad_recv_cnt;
			report_bad_packet(hid_ishtp_cl, recv_msg, cur_pos,
					  payload_len);
			ish_hw_reset(ishtp_get_ishtp_device(hid_ishtp_cl));
			अवरोध;
		पूर्ण

		hid_ishtp_trace(client_data,  "%s %d\n",
				__func__, recv_msg->hdr.command & CMD_MASK);

		चयन (recv_msg->hdr.command & CMD_MASK) अणु
		हाल HOSTIF_DM_ENUM_DEVICES:
			अगर ((!(recv_msg->hdr.command & ~CMD_MASK) ||
					client_data->init_करोne)) अणु
				++client_data->bad_recv_cnt;
				report_bad_packet(hid_ishtp_cl, recv_msg,
						  cur_pos,
						  payload_len);
				ish_hw_reset(ishtp_get_ishtp_device(hid_ishtp_cl));
				अवरोध;
			पूर्ण
			client_data->hid_dev_count = (अचिन्हित पूर्णांक)*payload;
			अगर (!client_data->hid_devices)
				client_data->hid_devices = devm_kसुस्मृति(
						cl_data_to_dev(client_data),
						client_data->hid_dev_count,
						माप(काष्ठा device_info),
						GFP_KERNEL);
			अगर (!client_data->hid_devices) अणु
				dev_err(cl_data_to_dev(client_data),
				"Mem alloc failed for hid device info\n");
				wake_up_पूर्णांकerruptible(&client_data->init_रुको);
				अवरोध;
			पूर्ण
			क्रम (i = 0; i < client_data->hid_dev_count; ++i) अणु
				अगर (1 + माप(काष्ठा device_info) * i >=
						payload_len) अणु
					dev_err(cl_data_to_dev(client_data),
						"[hid-ish]: [ENUM_DEVICES]: content size %zu is bigger than payload_len %zu\n",
						1 + माप(काष्ठा device_info)
						* i, payload_len);
				पूर्ण

				अगर (1 + माप(काष्ठा device_info) * i >=
						data_len)
					अवरोध;

				dev_info = (काष्ठा device_info *)(payload + 1 +
					माप(काष्ठा device_info) * i);
				अगर (client_data->hid_devices)
					स_नकल(client_data->hid_devices + i,
					       dev_info,
					       माप(काष्ठा device_info));
			पूर्ण

			client_data->क्रमागत_devices_करोne = true;
			wake_up_पूर्णांकerruptible(&client_data->init_रुको);

			अवरोध;

		हाल HOSTIF_GET_HID_DESCRIPTOR:
			अगर ((!(recv_msg->hdr.command & ~CMD_MASK) ||
					client_data->init_करोne)) अणु
				++client_data->bad_recv_cnt;
				report_bad_packet(hid_ishtp_cl, recv_msg,
						  cur_pos,
						  payload_len);
				ish_hw_reset(ishtp_get_ishtp_device(hid_ishtp_cl));
				अवरोध;
			पूर्ण
			अगर (!client_data->hid_descr[curr_hid_dev])
				client_data->hid_descr[curr_hid_dev] =
				devm_kदो_स्मृति(cl_data_to_dev(client_data),
					     payload_len, GFP_KERNEL);
			अगर (client_data->hid_descr[curr_hid_dev]) अणु
				स_नकल(client_data->hid_descr[curr_hid_dev],
				       payload, payload_len);
				client_data->hid_descr_size[curr_hid_dev] =
					payload_len;
				client_data->hid_descr_करोne = true;
			पूर्ण
			wake_up_पूर्णांकerruptible(&client_data->init_रुको);

			अवरोध;

		हाल HOSTIF_GET_REPORT_DESCRIPTOR:
			अगर ((!(recv_msg->hdr.command & ~CMD_MASK) ||
					client_data->init_करोne)) अणु
				++client_data->bad_recv_cnt;
				report_bad_packet(hid_ishtp_cl, recv_msg,
						  cur_pos,
						  payload_len);
				ish_hw_reset(ishtp_get_ishtp_device(hid_ishtp_cl));
				अवरोध;
			पूर्ण
			अगर (!client_data->report_descr[curr_hid_dev])
				client_data->report_descr[curr_hid_dev] =
				devm_kदो_स्मृति(cl_data_to_dev(client_data),
					     payload_len, GFP_KERNEL);
			अगर (client_data->report_descr[curr_hid_dev])  अणु
				स_नकल(client_data->report_descr[curr_hid_dev],
				       payload,
				       payload_len);
				client_data->report_descr_size[curr_hid_dev] =
					payload_len;
				client_data->report_descr_करोne = true;
			पूर्ण
			wake_up_पूर्णांकerruptible(&client_data->init_रुको);

			अवरोध;

		हाल HOSTIF_GET_FEATURE_REPORT:
			report_type = HID_FEATURE_REPORT;
			जाओ	करो_get_report;

		हाल HOSTIF_GET_INPUT_REPORT:
			report_type = HID_INPUT_REPORT;
करो_get_report:
			/* Get index of device that matches this id */
			क्रम (i = 0; i < client_data->num_hid_devices; ++i) अणु
				अगर (recv_msg->hdr.device_id ==
					  client_data->hid_devices[i].dev_id) अणु
					hid = client_data->hid_sensor_hubs[i];
					अगर (!hid)
						अवरोध;

					hid_data = hid->driver_data;
					अगर (hid_data->raw_get_req) अणु
						raw_len =
						  (hid_data->raw_buf_size <
								payload_len) ?
						  hid_data->raw_buf_size :
						  payload_len;

						स_नकल(hid_data->raw_buf,
						       payload, raw_len);
					पूर्ण अन्यथा अणु
						hid_input_report
							(hid, report_type,
							 payload, payload_len,
							 0);
					पूर्ण

					ishtp_hid_wakeup(hid);
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;

		हाल HOSTIF_SET_FEATURE_REPORT:
			/* Get index of device that matches this id */
			क्रम (i = 0; i < client_data->num_hid_devices; ++i) अणु
				अगर (recv_msg->hdr.device_id ==
					client_data->hid_devices[i].dev_id)
					अगर (client_data->hid_sensor_hubs[i]) अणु
						ishtp_hid_wakeup(
						client_data->hid_sensor_hubs[
							i]);
						अवरोध;
					पूर्ण
			पूर्ण
			अवरोध;

		हाल HOSTIF_PUBLISH_INPUT_REPORT:
			report_type = HID_INPUT_REPORT;
			क्रम (i = 0; i < client_data->num_hid_devices; ++i)
				अगर (recv_msg->hdr.device_id ==
					client_data->hid_devices[i].dev_id)
					अगर (client_data->hid_sensor_hubs[i])
						hid_input_report(
						client_data->hid_sensor_hubs[
									i],
						report_type, payload,
						payload_len, 0);
			अवरोध;

		हाल HOSTIF_PUBLISH_INPUT_REPORT_LIST:
			report_type = HID_INPUT_REPORT;
			reports_list = (काष्ठा report_list *)payload;
			reports = (अक्षर *)reports_list->reports;

			क्रम (j = 0; j < reports_list->num_of_reports; j++) अणु
				recv_msg = (काष्ठा hostअगर_msg *)(reports +
					माप(uपूर्णांक16_t));
				report_len = *(uपूर्णांक16_t *)reports;
				payload = reports + माप(uपूर्णांक16_t) +
					माप(काष्ठा hostअगर_msg_hdr);
				payload_len = report_len -
					माप(काष्ठा hostअगर_msg_hdr);

				क्रम (i = 0; i < client_data->num_hid_devices;
				     ++i)
					अगर (recv_msg->hdr.device_id ==
					client_data->hid_devices[i].dev_id &&
					client_data->hid_sensor_hubs[i]) अणु
						hid_input_report(
						client_data->hid_sensor_hubs[
									i],
						report_type,
						payload, payload_len,
						0);
					पूर्ण

				reports += माप(uपूर्णांक16_t) + report_len;
			पूर्ण
			अवरोध;
		शेष:
			++client_data->bad_recv_cnt;
			report_bad_packet(hid_ishtp_cl, recv_msg, cur_pos,
					  payload_len);
			ish_hw_reset(ishtp_get_ishtp_device(hid_ishtp_cl));
			अवरोध;

		पूर्ण

		अगर (!cur_pos && cur_pos + payload_len +
				माप(काष्ठा hostअगर_msg) < total_len)
			++client_data->multi_packet_cnt;

		cur_pos += payload_len + माप(काष्ठा hostअगर_msg);
		payload += payload_len + माप(काष्ठा hostअगर_msg);

	पूर्ण जबतक (cur_pos < total_len);
पूर्ण

/**
 * ish_cl_event_cb() - bus driver callback क्रम incoming message/packet
 * @device:	Poपूर्णांकer to the the ishtp client device क्रम which this message
 *		is targeted
 *
 * Remove the packet from the list and process the message by calling
 * process_recv
 */
अटल व्योम ish_cl_event_cb(काष्ठा ishtp_cl_device *device)
अणु
	काष्ठा ishtp_cl	*hid_ishtp_cl = ishtp_get_drvdata(device);
	काष्ठा ishtp_cl_rb *rb_in_proc;
	माप_प्रकार r_length;

	अगर (!hid_ishtp_cl)
		वापस;

	जबतक ((rb_in_proc = ishtp_cl_rx_get_rb(hid_ishtp_cl)) != शून्य) अणु
		अगर (!rb_in_proc->buffer.data)
			वापस;

		r_length = rb_in_proc->buf_idx;

		/* decide what to करो with received data */
		process_recv(hid_ishtp_cl, rb_in_proc->buffer.data, r_length);

		ishtp_cl_io_rb_recycle(rb_in_proc);
	पूर्ण
पूर्ण

/**
 * hid_ishtp_set_feature() - send request to ISH FW to set a feature request
 * @hid:	hid device instance क्रम this request
 * @buf:	feature buffer
 * @len:	Length of feature buffer
 * @report_id:	Report id क्रम the feature set request
 *
 * This is called from hid core .request() callback. This function करोesn't रुको
 * क्रम response.
 */
व्योम hid_ishtp_set_feature(काष्ठा hid_device *hid, अक्षर *buf, अचिन्हित पूर्णांक len,
			   पूर्णांक report_id)
अणु
	काष्ठा ishtp_hid_data *hid_data =  hid->driver_data;
	काष्ठा ishtp_cl_data *client_data = hid_data->client_data;
	काष्ठा hostअगर_msg *msg = (काष्ठा hostअगर_msg *)buf;
	पूर्णांक	rv;
	पूर्णांक	i;

	hid_ishtp_trace(client_data,  "%s hid %p\n", __func__, hid);

	rv = ishtp_hid_link_पढ़ोy_रुको(client_data);
	अगर (rv) अणु
		hid_ishtp_trace(client_data,  "%s hid %p link not ready\n",
				__func__, hid);
		वापस;
	पूर्ण

	स_रखो(msg, 0, माप(काष्ठा hostअगर_msg));
	msg->hdr.command = HOSTIF_SET_FEATURE_REPORT;
	क्रम (i = 0; i < client_data->num_hid_devices; ++i) अणु
		अगर (hid == client_data->hid_sensor_hubs[i]) अणु
			msg->hdr.device_id =
				client_data->hid_devices[i].dev_id;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == client_data->num_hid_devices)
		वापस;

	rv = ishtp_cl_send(client_data->hid_ishtp_cl, buf, len);
	अगर (rv)
		hid_ishtp_trace(client_data,  "%s hid %p send failed\n",
				__func__, hid);
पूर्ण

/**
 * hid_ishtp_get_report() - request to get feature/input report
 * @hid:	hid device instance क्रम this request
 * @report_id:	Report id क्रम the get request
 * @report_type:	Report type क्रम the this request
 *
 * This is called from hid core .request() callback. This function will send
 * request to FW and वापस without रुकोing क्रम response.
 */
व्योम hid_ishtp_get_report(काष्ठा hid_device *hid, पूर्णांक report_id,
			  पूर्णांक report_type)
अणु
	काष्ठा ishtp_hid_data *hid_data =  hid->driver_data;
	काष्ठा ishtp_cl_data *client_data = hid_data->client_data;
	काष्ठा hostअगर_msg_to_sensor msg = अणुपूर्ण;
	पूर्णांक	rv;
	पूर्णांक	i;

	hid_ishtp_trace(client_data,  "%s hid %p\n", __func__, hid);
	rv = ishtp_hid_link_पढ़ोy_रुको(client_data);
	अगर (rv) अणु
		hid_ishtp_trace(client_data,  "%s hid %p link not ready\n",
				__func__, hid);
		वापस;
	पूर्ण

	msg.hdr.command = (report_type == HID_FEATURE_REPORT) ?
		HOSTIF_GET_FEATURE_REPORT : HOSTIF_GET_INPUT_REPORT;
	क्रम (i = 0; i < client_data->num_hid_devices; ++i) अणु
		अगर (hid == client_data->hid_sensor_hubs[i]) अणु
			msg.hdr.device_id =
				client_data->hid_devices[i].dev_id;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == client_data->num_hid_devices)
		वापस;

	msg.report_id = report_id;
	rv = ishtp_cl_send(client_data->hid_ishtp_cl, (uपूर्णांक8_t *)&msg,
			    माप(msg));
	अगर (rv)
		hid_ishtp_trace(client_data,  "%s hid %p send failed\n",
				__func__, hid);
पूर्ण

/**
 * ishtp_hid_link_पढ़ोy_रुको() - Wait क्रम link पढ़ोy
 * @client_data:	client data instance
 *
 * If the transport link started suspend process, then रुको, till either
 * resumed or समयout
 *
 * Return: 0 on success, non zero on error
 */
पूर्णांक ishtp_hid_link_पढ़ोy_रुको(काष्ठा ishtp_cl_data *client_data)
अणु
	पूर्णांक rc;

	अगर (client_data->suspended) अणु
		hid_ishtp_trace(client_data,  "wait for link ready\n");
		rc = रुको_event_पूर्णांकerruptible_समयout(
					client_data->ishtp_resume_रुको,
					!client_data->suspended,
					5 * HZ);

		अगर (rc == 0) अणु
			hid_ishtp_trace(client_data,  "link not ready\n");
			वापस -EIO;
		पूर्ण
		hid_ishtp_trace(client_data,  "link ready\n");
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ishtp_क्रमागत_क्रमागत_devices() - Enumerate hid devices
 * @hid_ishtp_cl:	client instance
 *
 * Helper function to send request to firmware to क्रमागतerate HID devices
 *
 * Return: 0 on success, non zero on error
 */
अटल पूर्णांक ishtp_क्रमागत_क्रमागत_devices(काष्ठा ishtp_cl *hid_ishtp_cl)
अणु
	काष्ठा hostअगर_msg msg;
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(hid_ishtp_cl);
	पूर्णांक retry_count;
	पूर्णांक rv;

	/* Send HOSTIF_DM_ENUM_DEVICES */
	स_रखो(&msg, 0, माप(काष्ठा hostअगर_msg));
	msg.hdr.command = HOSTIF_DM_ENUM_DEVICES;
	rv = ishtp_cl_send(hid_ishtp_cl, (अचिन्हित अक्षर *)&msg,
			   माप(काष्ठा hostअगर_msg));
	अगर (rv)
		वापस rv;

	retry_count = 0;
	जबतक (!client_data->क्रमागत_devices_करोne &&
	       retry_count < 10) अणु
		रुको_event_पूर्णांकerruptible_समयout(client_data->init_रुको,
					 client_data->क्रमागत_devices_करोne,
					 3 * HZ);
		++retry_count;
		अगर (!client_data->क्रमागत_devices_करोne)
			/* Send HOSTIF_DM_ENUM_DEVICES */
			rv = ishtp_cl_send(hid_ishtp_cl,
					   (अचिन्हित अक्षर *) &msg,
					   माप(काष्ठा hostअगर_msg));
	पूर्ण
	अगर (!client_data->क्रमागत_devices_करोne) अणु
		dev_err(cl_data_to_dev(client_data),
			"[hid-ish]: timed out waiting for enum_devices\n");
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (!client_data->hid_devices) अणु
		dev_err(cl_data_to_dev(client_data),
			"[hid-ish]: failed to allocate HID dev structures\n");
		वापस -ENOMEM;
	पूर्ण

	client_data->num_hid_devices = client_data->hid_dev_count;
	dev_info(ishtp_device(client_data->cl_device),
		"[hid-ish]: enum_devices_done OK, num_hid_devices=%d\n",
		client_data->num_hid_devices);

	वापस	0;
पूर्ण

/**
 * ishtp_get_hid_descriptor() - Get hid descriptor
 * @hid_ishtp_cl:	client instance
 * @index:		Index पूर्णांकo the hid_descr array
 *
 * Helper function to send request to firmware get HID descriptor of a device
 *
 * Return: 0 on success, non zero on error
 */
अटल पूर्णांक ishtp_get_hid_descriptor(काष्ठा ishtp_cl *hid_ishtp_cl, पूर्णांक index)
अणु
	काष्ठा hostअगर_msg msg;
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(hid_ishtp_cl);
	पूर्णांक rv;

	/* Get HID descriptor */
	client_data->hid_descr_करोne = false;
	स_रखो(&msg, 0, माप(काष्ठा hostअगर_msg));
	msg.hdr.command = HOSTIF_GET_HID_DESCRIPTOR;
	msg.hdr.device_id = client_data->hid_devices[index].dev_id;
	rv = ishtp_cl_send(hid_ishtp_cl, (अचिन्हित अक्षर *) &msg,
			   माप(काष्ठा hostअगर_msg));
	अगर (rv)
		वापस rv;

	अगर (!client_data->hid_descr_करोne) अणु
		रुको_event_पूर्णांकerruptible_समयout(client_data->init_रुको,
						 client_data->hid_descr_करोne,
						 3 * HZ);
		अगर (!client_data->hid_descr_करोne) अणु
			dev_err(cl_data_to_dev(client_data),
				"[hid-ish]: timed out for hid_descr_done\n");
			वापस -EIO;
		पूर्ण

		अगर (!client_data->hid_descr[index]) अणु
			dev_err(cl_data_to_dev(client_data),
				"[hid-ish]: allocation HID desc fail\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ishtp_get_report_descriptor() - Get report descriptor
 * @hid_ishtp_cl:	client instance
 * @index:		Index पूर्णांकo the hid_descr array
 *
 * Helper function to send request to firmware get HID report descriptor of
 * a device
 *
 * Return: 0 on success, non zero on error
 */
अटल पूर्णांक ishtp_get_report_descriptor(काष्ठा ishtp_cl *hid_ishtp_cl,
				       पूर्णांक index)
अणु
	काष्ठा hostअगर_msg msg;
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(hid_ishtp_cl);
	पूर्णांक rv;

	/* Get report descriptor */
	client_data->report_descr_करोne = false;
	स_रखो(&msg, 0, माप(काष्ठा hostअगर_msg));
	msg.hdr.command = HOSTIF_GET_REPORT_DESCRIPTOR;
	msg.hdr.device_id = client_data->hid_devices[index].dev_id;
	rv = ishtp_cl_send(hid_ishtp_cl, (अचिन्हित अक्षर *) &msg,
			   माप(काष्ठा hostअगर_msg));
	अगर (rv)
		वापस rv;

	अगर (!client_data->report_descr_करोne)
		रुको_event_पूर्णांकerruptible_समयout(client_data->init_रुको,
					 client_data->report_descr_करोne,
					 3 * HZ);
	अगर (!client_data->report_descr_करोne) अणु
		dev_err(cl_data_to_dev(client_data),
				"[hid-ish]: timed out for report descr\n");
		वापस -EIO;
	पूर्ण
	अगर (!client_data->report_descr[index]) अणु
		dev_err(cl_data_to_dev(client_data),
			"[hid-ish]: failed to alloc report descr\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hid_ishtp_cl_init() - Init function क्रम ISHTP client
 * @hid_ishtp_cl:	ISHTP client instance
 * @reset:		true अगर called क्रम init after reset
 *
 * This function complete the initializtion of the client. The summary of
 * processing:
 * - Send request to क्रमागतerate the hid clients
 *	Get the HID descriptor क्रम each क्रमागतearated device
 *	Get report description of each device
 *	Register each device wik hid core by calling ishtp_hid_probe
 *
 * Return: 0 on success, non zero on error
 */
अटल पूर्णांक hid_ishtp_cl_init(काष्ठा ishtp_cl *hid_ishtp_cl, पूर्णांक reset)
अणु
	काष्ठा ishtp_device *dev;
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(hid_ishtp_cl);
	काष्ठा ishtp_fw_client *fw_client;
	पूर्णांक i;
	पूर्णांक rv;

	dev_dbg(cl_data_to_dev(client_data), "%s\n", __func__);
	hid_ishtp_trace(client_data,  "%s reset flag: %d\n", __func__, reset);

	rv = ishtp_cl_link(hid_ishtp_cl);
	अगर (rv) अणु
		dev_err(cl_data_to_dev(client_data),
			"ishtp_cl_link failed\n");
		वापस	-ENOMEM;
	पूर्ण

	client_data->init_करोne = 0;

	dev = ishtp_get_ishtp_device(hid_ishtp_cl);

	/* Connect to FW client */
	ishtp_set_tx_ring_size(hid_ishtp_cl, HID_CL_TX_RING_SIZE);
	ishtp_set_rx_ring_size(hid_ishtp_cl, HID_CL_RX_RING_SIZE);

	fw_client = ishtp_fw_cl_get_client(dev, &hid_ishtp_guid);
	अगर (!fw_client) अणु
		dev_err(cl_data_to_dev(client_data),
			"ish client uuid not found\n");
		वापस -ENOENT;
	पूर्ण
	ishtp_cl_set_fw_client_id(hid_ishtp_cl,
				  ishtp_get_fw_client_id(fw_client));
	ishtp_set_connection_state(hid_ishtp_cl, ISHTP_CL_CONNECTING);

	rv = ishtp_cl_connect(hid_ishtp_cl);
	अगर (rv) अणु
		dev_err(cl_data_to_dev(client_data),
			"client connect fail\n");
		जाओ err_cl_unlink;
	पूर्ण

	hid_ishtp_trace(client_data,  "%s client connected\n", __func__);

	/* Register पढ़ो callback */
	ishtp_रेजिस्टर_event_cb(client_data->cl_device, ish_cl_event_cb);

	rv = ishtp_क्रमागत_क्रमागत_devices(hid_ishtp_cl);
	अगर (rv)
		जाओ err_cl_disconnect;

	hid_ishtp_trace(client_data,  "%s enumerated device count %d\n",
			__func__, client_data->num_hid_devices);

	क्रम (i = 0; i < client_data->num_hid_devices; ++i) अणु
		client_data->cur_hid_dev = i;

		rv = ishtp_get_hid_descriptor(hid_ishtp_cl, i);
		अगर (rv)
			जाओ err_cl_disconnect;

		rv = ishtp_get_report_descriptor(hid_ishtp_cl, i);
		अगर (rv)
			जाओ err_cl_disconnect;

		अगर (!reset) अणु
			rv = ishtp_hid_probe(i, client_data);
			अगर (rv) अणु
				dev_err(cl_data_to_dev(client_data),
				"[hid-ish]: HID probe for #%u failed: %d\n",
				i, rv);
				जाओ err_cl_disconnect;
			पूर्ण
		पूर्ण
	पूर्ण /* क्रम() on all hid devices */

	client_data->init_करोne = 1;
	client_data->suspended = false;
	wake_up_पूर्णांकerruptible(&client_data->ishtp_resume_रुको);
	hid_ishtp_trace(client_data,  "%s successful init\n", __func__);
	वापस 0;

err_cl_disconnect:
	ishtp_set_connection_state(hid_ishtp_cl, ISHTP_CL_DISCONNECTING);
	ishtp_cl_disconnect(hid_ishtp_cl);
err_cl_unlink:
	ishtp_cl_unlink(hid_ishtp_cl);
	वापस rv;
पूर्ण

/**
 * hid_ishtp_cl_deinit() - Deinit function क्रम ISHTP client
 * @hid_ishtp_cl:	ISHTP client instance
 *
 * Unlink and मुक्त hid client
 */
अटल व्योम hid_ishtp_cl_deinit(काष्ठा ishtp_cl *hid_ishtp_cl)
अणु
	ishtp_cl_unlink(hid_ishtp_cl);
	ishtp_cl_flush_queues(hid_ishtp_cl);

	/* disband and मुक्त all Tx and Rx client-level rings */
	ishtp_cl_मुक्त(hid_ishtp_cl);
पूर्ण

अटल व्योम hid_ishtp_cl_reset_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ishtp_cl_data *client_data;
	काष्ठा ishtp_cl *hid_ishtp_cl;
	काष्ठा ishtp_cl_device *cl_device;
	पूर्णांक retry;
	पूर्णांक rv;

	client_data = container_of(work, काष्ठा ishtp_cl_data, work);

	hid_ishtp_cl = client_data->hid_ishtp_cl;
	cl_device = client_data->cl_device;

	hid_ishtp_trace(client_data, "%s hid_ishtp_cl %p\n", __func__,
			hid_ishtp_cl);
	dev_dbg(ishtp_device(client_data->cl_device), "%s\n", __func__);

	hid_ishtp_cl_deinit(hid_ishtp_cl);

	hid_ishtp_cl = ishtp_cl_allocate(cl_device);
	अगर (!hid_ishtp_cl)
		वापस;

	ishtp_set_drvdata(cl_device, hid_ishtp_cl);
	ishtp_set_client_data(hid_ishtp_cl, client_data);
	client_data->hid_ishtp_cl = hid_ishtp_cl;

	client_data->num_hid_devices = 0;

	क्रम (retry = 0; retry < 3; ++retry) अणु
		rv = hid_ishtp_cl_init(hid_ishtp_cl, 1);
		अगर (!rv)
			अवरोध;
		dev_err(cl_data_to_dev(client_data), "Retry reset init\n");
	पूर्ण
	अगर (rv) अणु
		dev_err(cl_data_to_dev(client_data), "Reset Failed\n");
		hid_ishtp_trace(client_data, "%s Failed hid_ishtp_cl %p\n",
				__func__, hid_ishtp_cl);
	पूर्ण
पूर्ण

व्योम (*hid_prपूर्णांक_trace)(व्योम *unused, स्थिर अक्षर *क्रमmat, ...);

/**
 * hid_ishtp_cl_probe() - ISHTP client driver probe
 * @cl_device:		ISHTP client device instance
 *
 * This function माला_लो called on device create on ISHTP bus
 *
 * Return: 0 on success, non zero on error
 */
अटल पूर्णांक hid_ishtp_cl_probe(काष्ठा ishtp_cl_device *cl_device)
अणु
	काष्ठा ishtp_cl *hid_ishtp_cl;
	काष्ठा ishtp_cl_data *client_data;
	पूर्णांक rv;

	अगर (!cl_device)
		वापस	-ENODEV;

	client_data = devm_kzalloc(ishtp_device(cl_device),
				   माप(*client_data),
				   GFP_KERNEL);
	अगर (!client_data)
		वापस -ENOMEM;

	hid_ishtp_cl = ishtp_cl_allocate(cl_device);
	अगर (!hid_ishtp_cl)
		वापस -ENOMEM;

	ishtp_set_drvdata(cl_device, hid_ishtp_cl);
	ishtp_set_client_data(hid_ishtp_cl, client_data);
	client_data->hid_ishtp_cl = hid_ishtp_cl;
	client_data->cl_device = cl_device;

	init_रुकोqueue_head(&client_data->init_रुको);
	init_रुकोqueue_head(&client_data->ishtp_resume_रुको);

	INIT_WORK(&client_data->work, hid_ishtp_cl_reset_handler);

	hid_prपूर्णांक_trace = ishtp_trace_callback(cl_device);

	rv = hid_ishtp_cl_init(hid_ishtp_cl, 0);
	अगर (rv) अणु
		ishtp_cl_मुक्त(hid_ishtp_cl);
		वापस rv;
	पूर्ण
	ishtp_get_device(cl_device);

	वापस 0;
पूर्ण

/**
 * hid_ishtp_cl_हटाओ() - ISHTP client driver हटाओ
 * @cl_device:		ISHTP client device instance
 *
 * This function माला_लो called on device हटाओ on ISHTP bus
 *
 * Return: 0
 */
अटल पूर्णांक hid_ishtp_cl_हटाओ(काष्ठा ishtp_cl_device *cl_device)
अणु
	काष्ठा ishtp_cl *hid_ishtp_cl = ishtp_get_drvdata(cl_device);
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(hid_ishtp_cl);

	hid_ishtp_trace(client_data, "%s hid_ishtp_cl %p\n", __func__,
			hid_ishtp_cl);

	dev_dbg(ishtp_device(cl_device), "%s\n", __func__);
	ishtp_set_connection_state(hid_ishtp_cl, ISHTP_CL_DISCONNECTING);
	ishtp_cl_disconnect(hid_ishtp_cl);
	ishtp_put_device(cl_device);
	ishtp_hid_हटाओ(client_data);
	hid_ishtp_cl_deinit(hid_ishtp_cl);

	hid_ishtp_cl = शून्य;

	client_data->num_hid_devices = 0;

	वापस 0;
पूर्ण

/**
 * hid_ishtp_cl_reset() - ISHTP client driver reset
 * @cl_device:		ISHTP client device instance
 *
 * This function माला_लो called on device reset on ISHTP bus
 *
 * Return: 0
 */
अटल पूर्णांक hid_ishtp_cl_reset(काष्ठा ishtp_cl_device *cl_device)
अणु
	काष्ठा ishtp_cl *hid_ishtp_cl = ishtp_get_drvdata(cl_device);
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(hid_ishtp_cl);

	hid_ishtp_trace(client_data, "%s hid_ishtp_cl %p\n", __func__,
			hid_ishtp_cl);

	schedule_work(&client_data->work);

	वापस 0;
पूर्ण

/**
 * hid_ishtp_cl_suspend() - ISHTP client driver suspend
 * @device:	device instance
 *
 * This function माला_लो called on प्रणाली suspend
 *
 * Return: 0
 */
अटल पूर्णांक hid_ishtp_cl_suspend(काष्ठा device *device)
अणु
	काष्ठा ishtp_cl_device *cl_device = ishtp_dev_to_cl_device(device);
	काष्ठा ishtp_cl *hid_ishtp_cl = ishtp_get_drvdata(cl_device);
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(hid_ishtp_cl);

	hid_ishtp_trace(client_data, "%s hid_ishtp_cl %p\n", __func__,
			hid_ishtp_cl);
	client_data->suspended = true;

	वापस 0;
पूर्ण

/**
 * hid_ishtp_cl_resume() - ISHTP client driver resume
 * @device:	device instance
 *
 * This function माला_लो called on प्रणाली resume
 *
 * Return: 0
 */
अटल पूर्णांक hid_ishtp_cl_resume(काष्ठा device *device)
अणु
	काष्ठा ishtp_cl_device *cl_device = ishtp_dev_to_cl_device(device);
	काष्ठा ishtp_cl *hid_ishtp_cl = ishtp_get_drvdata(cl_device);
	काष्ठा ishtp_cl_data *client_data = ishtp_get_client_data(hid_ishtp_cl);

	hid_ishtp_trace(client_data, "%s hid_ishtp_cl %p\n", __func__,
			hid_ishtp_cl);
	client_data->suspended = false;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops hid_ishtp_pm_ops = अणु
	.suspend = hid_ishtp_cl_suspend,
	.resume = hid_ishtp_cl_resume,
पूर्ण;

अटल काष्ठा ishtp_cl_driver	hid_ishtp_cl_driver = अणु
	.name = "ish-hid",
	.guid = &hid_ishtp_guid,
	.probe = hid_ishtp_cl_probe,
	.हटाओ = hid_ishtp_cl_हटाओ,
	.reset = hid_ishtp_cl_reset,
	.driver.pm = &hid_ishtp_pm_ops,
पूर्ण;

अटल पूर्णांक __init ish_hid_init(व्योम)
अणु
	पूर्णांक	rv;

	/* Register ISHTP client device driver with ISHTP Bus */
	rv = ishtp_cl_driver_रेजिस्टर(&hid_ishtp_cl_driver, THIS_MODULE);

	वापस rv;

पूर्ण

अटल व्योम __निकास ish_hid_निकास(व्योम)
अणु
	ishtp_cl_driver_unरेजिस्टर(&hid_ishtp_cl_driver);
पूर्ण

late_initcall(ish_hid_init);
module_निकास(ish_hid_निकास);

MODULE_DESCRIPTION("ISH ISHTP HID client driver");
/* Primary author */
MODULE_AUTHOR("Daniel Drubin <daniel.drubin@intel.com>");
/*
 * Several modअगरication क्रम multi instance support
 * suspend/resume and clean up
 */
MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");

MODULE_LICENSE("GPL");
MODULE_ALIAS("ishtp:*");
