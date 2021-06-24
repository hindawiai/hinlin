<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus Audio Device Class Protocol helpers
 *
 * Copyright 2015-2016 Google Inc.
 */

#समावेश <linux/greybus.h>
#समावेश "audio_apbridgea.h"
#समावेश "audio_codec.h"

पूर्णांक gb_audio_apbridgea_set_config(काष्ठा gb_connection *connection,
				  __u16 i2s_port, __u32 क्रमmat, __u32 rate,
				  __u32 mclk_freq)
अणु
	काष्ठा audio_apbridgea_set_config_request req;

	req.hdr.type = AUDIO_APBRIDGEA_TYPE_SET_CONFIG;
	req.hdr.i2s_port = cpu_to_le16(i2s_port);
	req.क्रमmat = cpu_to_le32(क्रमmat);
	req.rate = cpu_to_le32(rate);
	req.mclk_freq = cpu_to_le32(mclk_freq);

	वापस gb_hd_output(connection->hd, &req, माप(req),
			    GB_APB_REQUEST_AUDIO_CONTROL, true);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_apbridgea_set_config);

पूर्णांक gb_audio_apbridgea_रेजिस्टर_cport(काष्ठा gb_connection *connection,
				      __u16 i2s_port, __u16 cportid,
				      __u8 direction)
अणु
	काष्ठा audio_apbridgea_रेजिस्टर_cport_request req;
	पूर्णांक ret;

	req.hdr.type = AUDIO_APBRIDGEA_TYPE_REGISTER_CPORT;
	req.hdr.i2s_port = cpu_to_le16(i2s_port);
	req.cport = cpu_to_le16(cportid);
	req.direction = direction;

	ret = gb_pm_runसमय_get_sync(connection->bundle);
	अगर (ret)
		वापस ret;

	वापस gb_hd_output(connection->hd, &req, माप(req),
			    GB_APB_REQUEST_AUDIO_CONTROL, true);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_apbridgea_रेजिस्टर_cport);

पूर्णांक gb_audio_apbridgea_unरेजिस्टर_cport(काष्ठा gb_connection *connection,
					__u16 i2s_port, __u16 cportid,
					__u8 direction)
अणु
	काष्ठा audio_apbridgea_unरेजिस्टर_cport_request req;
	पूर्णांक ret;

	req.hdr.type = AUDIO_APBRIDGEA_TYPE_UNREGISTER_CPORT;
	req.hdr.i2s_port = cpu_to_le16(i2s_port);
	req.cport = cpu_to_le16(cportid);
	req.direction = direction;

	ret = gb_hd_output(connection->hd, &req, माप(req),
			   GB_APB_REQUEST_AUDIO_CONTROL, true);

	gb_pm_runसमय_put_स्वतःsuspend(connection->bundle);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_apbridgea_unरेजिस्टर_cport);

पूर्णांक gb_audio_apbridgea_set_tx_data_size(काष्ठा gb_connection *connection,
					__u16 i2s_port, __u16 size)
अणु
	काष्ठा audio_apbridgea_set_tx_data_size_request req;

	req.hdr.type = AUDIO_APBRIDGEA_TYPE_SET_TX_DATA_SIZE;
	req.hdr.i2s_port = cpu_to_le16(i2s_port);
	req.size = cpu_to_le16(size);

	वापस gb_hd_output(connection->hd, &req, माप(req),
			    GB_APB_REQUEST_AUDIO_CONTROL, true);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_apbridgea_set_tx_data_size);

पूर्णांक gb_audio_apbridgea_prepare_tx(काष्ठा gb_connection *connection,
				  __u16 i2s_port)
अणु
	काष्ठा audio_apbridgea_prepare_tx_request req;

	req.hdr.type = AUDIO_APBRIDGEA_TYPE_PREPARE_TX;
	req.hdr.i2s_port = cpu_to_le16(i2s_port);

	वापस gb_hd_output(connection->hd, &req, माप(req),
			    GB_APB_REQUEST_AUDIO_CONTROL, true);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_apbridgea_prepare_tx);

पूर्णांक gb_audio_apbridgea_start_tx(काष्ठा gb_connection *connection,
				__u16 i2s_port, __u64 बारtamp)
अणु
	काष्ठा audio_apbridgea_start_tx_request req;

	req.hdr.type = AUDIO_APBRIDGEA_TYPE_START_TX;
	req.hdr.i2s_port = cpu_to_le16(i2s_port);
	req.बारtamp = cpu_to_le64(बारtamp);

	वापस gb_hd_output(connection->hd, &req, माप(req),
			    GB_APB_REQUEST_AUDIO_CONTROL, true);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_apbridgea_start_tx);

पूर्णांक gb_audio_apbridgea_stop_tx(काष्ठा gb_connection *connection, __u16 i2s_port)
अणु
	काष्ठा audio_apbridgea_stop_tx_request req;

	req.hdr.type = AUDIO_APBRIDGEA_TYPE_STOP_TX;
	req.hdr.i2s_port = cpu_to_le16(i2s_port);

	वापस gb_hd_output(connection->hd, &req, माप(req),
			    GB_APB_REQUEST_AUDIO_CONTROL, true);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_apbridgea_stop_tx);

पूर्णांक gb_audio_apbridgea_shutकरोwn_tx(काष्ठा gb_connection *connection,
				   __u16 i2s_port)
अणु
	काष्ठा audio_apbridgea_shutकरोwn_tx_request req;

	req.hdr.type = AUDIO_APBRIDGEA_TYPE_SHUTDOWN_TX;
	req.hdr.i2s_port = cpu_to_le16(i2s_port);

	वापस gb_hd_output(connection->hd, &req, माप(req),
			    GB_APB_REQUEST_AUDIO_CONTROL, true);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_apbridgea_shutकरोwn_tx);

पूर्णांक gb_audio_apbridgea_set_rx_data_size(काष्ठा gb_connection *connection,
					__u16 i2s_port, __u16 size)
अणु
	काष्ठा audio_apbridgea_set_rx_data_size_request req;

	req.hdr.type = AUDIO_APBRIDGEA_TYPE_SET_RX_DATA_SIZE;
	req.hdr.i2s_port = cpu_to_le16(i2s_port);
	req.size = cpu_to_le16(size);

	वापस gb_hd_output(connection->hd, &req, माप(req),
			    GB_APB_REQUEST_AUDIO_CONTROL, true);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_apbridgea_set_rx_data_size);

पूर्णांक gb_audio_apbridgea_prepare_rx(काष्ठा gb_connection *connection,
				  __u16 i2s_port)
अणु
	काष्ठा audio_apbridgea_prepare_rx_request req;

	req.hdr.type = AUDIO_APBRIDGEA_TYPE_PREPARE_RX;
	req.hdr.i2s_port = cpu_to_le16(i2s_port);

	वापस gb_hd_output(connection->hd, &req, माप(req),
			    GB_APB_REQUEST_AUDIO_CONTROL, true);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_apbridgea_prepare_rx);

पूर्णांक gb_audio_apbridgea_start_rx(काष्ठा gb_connection *connection,
				__u16 i2s_port)
अणु
	काष्ठा audio_apbridgea_start_rx_request req;

	req.hdr.type = AUDIO_APBRIDGEA_TYPE_START_RX;
	req.hdr.i2s_port = cpu_to_le16(i2s_port);

	वापस gb_hd_output(connection->hd, &req, माप(req),
			    GB_APB_REQUEST_AUDIO_CONTROL, true);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_apbridgea_start_rx);

पूर्णांक gb_audio_apbridgea_stop_rx(काष्ठा gb_connection *connection, __u16 i2s_port)
अणु
	काष्ठा audio_apbridgea_stop_rx_request req;

	req.hdr.type = AUDIO_APBRIDGEA_TYPE_STOP_RX;
	req.hdr.i2s_port = cpu_to_le16(i2s_port);

	वापस gb_hd_output(connection->hd, &req, माप(req),
			    GB_APB_REQUEST_AUDIO_CONTROL, true);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_apbridgea_stop_rx);

पूर्णांक gb_audio_apbridgea_shutकरोwn_rx(काष्ठा gb_connection *connection,
				   __u16 i2s_port)
अणु
	काष्ठा audio_apbridgea_shutकरोwn_rx_request req;

	req.hdr.type = AUDIO_APBRIDGEA_TYPE_SHUTDOWN_RX;
	req.hdr.i2s_port = cpu_to_le16(i2s_port);

	वापस gb_hd_output(connection->hd, &req, माप(req),
			    GB_APB_REQUEST_AUDIO_CONTROL, true);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_apbridgea_shutकरोwn_rx);

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("greybus:audio-apbridgea");
MODULE_DESCRIPTION("Greybus Special APBridgeA Audio Protocol library");
MODULE_AUTHOR("Mark Greer <mgreer@animalcreek.com>");
