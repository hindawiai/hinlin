<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus Audio Device Class Protocol helpers
 *
 * Copyright 2015-2016 Google Inc.
 */

#समावेश <linux/greybus.h>
#समावेश "audio_codec.h"

/* TODO: Split पूर्णांकo separate calls */
पूर्णांक gb_audio_gb_get_topology(काष्ठा gb_connection *connection,
			     काष्ठा gb_audio_topology **topology)
अणु
	काष्ठा gb_audio_get_topology_size_response size_resp;
	काष्ठा gb_audio_topology *topo;
	u16 size;
	पूर्णांक ret;

	ret = gb_operation_sync(connection, GB_AUDIO_TYPE_GET_TOPOLOGY_SIZE,
				शून्य, 0, &size_resp, माप(size_resp));
	अगर (ret)
		वापस ret;

	size = le16_to_cpu(size_resp.size);
	अगर (size < माप(*topo))
		वापस -ENODATA;

	topo = kzalloc(size, GFP_KERNEL);
	अगर (!topo)
		वापस -ENOMEM;

	ret = gb_operation_sync(connection, GB_AUDIO_TYPE_GET_TOPOLOGY, शून्य, 0,
				topo, size);
	अगर (ret) अणु
		kमुक्त(topo);
		वापस ret;
	पूर्ण

	*topology = topo;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_gb_get_topology);

पूर्णांक gb_audio_gb_get_control(काष्ठा gb_connection *connection,
			    u8 control_id, u8 index,
			    काष्ठा gb_audio_ctl_elem_value *value)
अणु
	काष्ठा gb_audio_get_control_request req;
	काष्ठा gb_audio_get_control_response resp;
	पूर्णांक ret;

	req.control_id = control_id;
	req.index = index;

	ret = gb_operation_sync(connection, GB_AUDIO_TYPE_GET_CONTROL,
				&req, माप(req), &resp, माप(resp));
	अगर (ret)
		वापस ret;

	स_नकल(value, &resp.value, माप(*value));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_gb_get_control);

पूर्णांक gb_audio_gb_set_control(काष्ठा gb_connection *connection,
			    u8 control_id, u8 index,
			    काष्ठा gb_audio_ctl_elem_value *value)
अणु
	काष्ठा gb_audio_set_control_request req;

	req.control_id = control_id;
	req.index = index;
	स_नकल(&req.value, value, माप(req.value));

	वापस gb_operation_sync(connection, GB_AUDIO_TYPE_SET_CONTROL,
				 &req, माप(req), शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_gb_set_control);

पूर्णांक gb_audio_gb_enable_widget(काष्ठा gb_connection *connection,
			      u8 widget_id)
अणु
	काष्ठा gb_audio_enable_widget_request req;

	req.widget_id = widget_id;

	वापस gb_operation_sync(connection, GB_AUDIO_TYPE_ENABLE_WIDGET,
				 &req, माप(req), शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_gb_enable_widget);

पूर्णांक gb_audio_gb_disable_widget(काष्ठा gb_connection *connection,
			       u8 widget_id)
अणु
	काष्ठा gb_audio_disable_widget_request req;

	req.widget_id = widget_id;

	वापस gb_operation_sync(connection, GB_AUDIO_TYPE_DISABLE_WIDGET,
				 &req, माप(req), शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_gb_disable_widget);

पूर्णांक gb_audio_gb_get_pcm(काष्ठा gb_connection *connection, u16 data_cport,
			u32 *क्रमmat, u32 *rate, u8 *channels,
			u8 *sig_bits)
अणु
	काष्ठा gb_audio_get_pcm_request req;
	काष्ठा gb_audio_get_pcm_response resp;
	पूर्णांक ret;

	req.data_cport = cpu_to_le16(data_cport);

	ret = gb_operation_sync(connection, GB_AUDIO_TYPE_GET_PCM,
				&req, माप(req), &resp, माप(resp));
	अगर (ret)
		वापस ret;

	*क्रमmat = le32_to_cpu(resp.क्रमmat);
	*rate = le32_to_cpu(resp.rate);
	*channels = resp.channels;
	*sig_bits = resp.sig_bits;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_gb_get_pcm);

पूर्णांक gb_audio_gb_set_pcm(काष्ठा gb_connection *connection, u16 data_cport,
			u32 क्रमmat, u32 rate, u8 channels,
			u8 sig_bits)
अणु
	काष्ठा gb_audio_set_pcm_request req;

	req.data_cport = cpu_to_le16(data_cport);
	req.क्रमmat = cpu_to_le32(क्रमmat);
	req.rate = cpu_to_le32(rate);
	req.channels = channels;
	req.sig_bits = sig_bits;

	वापस gb_operation_sync(connection, GB_AUDIO_TYPE_SET_PCM,
				 &req, माप(req), शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_gb_set_pcm);

पूर्णांक gb_audio_gb_set_tx_data_size(काष्ठा gb_connection *connection,
				 u16 data_cport, u16 size)
अणु
	काष्ठा gb_audio_set_tx_data_size_request req;

	req.data_cport = cpu_to_le16(data_cport);
	req.size = cpu_to_le16(size);

	वापस gb_operation_sync(connection, GB_AUDIO_TYPE_SET_TX_DATA_SIZE,
				 &req, माप(req), शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_gb_set_tx_data_size);

पूर्णांक gb_audio_gb_activate_tx(काष्ठा gb_connection *connection,
			    u16 data_cport)
अणु
	काष्ठा gb_audio_activate_tx_request req;

	req.data_cport = cpu_to_le16(data_cport);

	वापस gb_operation_sync(connection, GB_AUDIO_TYPE_ACTIVATE_TX,
				 &req, माप(req), शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_gb_activate_tx);

पूर्णांक gb_audio_gb_deactivate_tx(काष्ठा gb_connection *connection,
			      u16 data_cport)
अणु
	काष्ठा gb_audio_deactivate_tx_request req;

	req.data_cport = cpu_to_le16(data_cport);

	वापस gb_operation_sync(connection, GB_AUDIO_TYPE_DEACTIVATE_TX,
				 &req, माप(req), शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_gb_deactivate_tx);

पूर्णांक gb_audio_gb_set_rx_data_size(काष्ठा gb_connection *connection,
				 u16 data_cport, u16 size)
अणु
	काष्ठा gb_audio_set_rx_data_size_request req;

	req.data_cport = cpu_to_le16(data_cport);
	req.size = cpu_to_le16(size);

	वापस gb_operation_sync(connection, GB_AUDIO_TYPE_SET_RX_DATA_SIZE,
				 &req, माप(req), शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_gb_set_rx_data_size);

पूर्णांक gb_audio_gb_activate_rx(काष्ठा gb_connection *connection,
			    u16 data_cport)
अणु
	काष्ठा gb_audio_activate_rx_request req;

	req.data_cport = cpu_to_le16(data_cport);

	वापस gb_operation_sync(connection, GB_AUDIO_TYPE_ACTIVATE_RX,
				 &req, माप(req), शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_gb_activate_rx);

पूर्णांक gb_audio_gb_deactivate_rx(काष्ठा gb_connection *connection,
			      u16 data_cport)
अणु
	काष्ठा gb_audio_deactivate_rx_request req;

	req.data_cport = cpu_to_le16(data_cport);

	वापस gb_operation_sync(connection, GB_AUDIO_TYPE_DEACTIVATE_RX,
				 &req, माप(req), शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_gb_deactivate_rx);

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("greybus:audio-gb");
MODULE_DESCRIPTION("Greybus Audio Device Class Protocol library");
MODULE_AUTHOR("Mark Greer <mgreer@animalcreek.com>");
