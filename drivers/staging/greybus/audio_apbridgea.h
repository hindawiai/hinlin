<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
/*
 * Copyright (c) 2015-2016 Google Inc.
 */
/*
 * This is a special protocol क्रम configuring communication over the
 * I2S bus between the DSP on the MSM8994 and APBridgeA.  Thereक्रमe,
 * we can predefine several low-level attributes of the communication
 * because we know that they are supported.  In particular, the following
 * assumptions are made:
 *	- there are two channels (i.e., stereo)
 *	- the low-level protocol is I2S as defined by Philips/NXP
 *	- the DSP on the MSM8994 is the घड़ी master क्रम MCLK, BCLK, and WCLK
 *	- WCLK changes on the falling edge of BCLK
 *	- WCLK low क्रम left channel; high क्रम right channel
 *	- TX data is sent on the falling edge of BCLK
 *	- RX data is received/latched on the rising edge of BCLK
 */

#अगर_अघोषित __AUDIO_APBRIDGEA_H
#घोषणा __AUDIO_APBRIDGEA_H

#घोषणा AUDIO_APBRIDGEA_TYPE_SET_CONFIG			0x01
#घोषणा AUDIO_APBRIDGEA_TYPE_REGISTER_CPORT		0x02
#घोषणा AUDIO_APBRIDGEA_TYPE_UNREGISTER_CPORT		0x03
#घोषणा AUDIO_APBRIDGEA_TYPE_SET_TX_DATA_SIZE		0x04
							/* 0x05 unused */
#घोषणा AUDIO_APBRIDGEA_TYPE_PREPARE_TX			0x06
#घोषणा AUDIO_APBRIDGEA_TYPE_START_TX			0x07
#घोषणा AUDIO_APBRIDGEA_TYPE_STOP_TX			0x08
#घोषणा AUDIO_APBRIDGEA_TYPE_SHUTDOWN_TX		0x09
#घोषणा AUDIO_APBRIDGEA_TYPE_SET_RX_DATA_SIZE		0x0a
							/* 0x0b unused */
#घोषणा AUDIO_APBRIDGEA_TYPE_PREPARE_RX			0x0c
#घोषणा AUDIO_APBRIDGEA_TYPE_START_RX			0x0d
#घोषणा AUDIO_APBRIDGEA_TYPE_STOP_RX			0x0e
#घोषणा AUDIO_APBRIDGEA_TYPE_SHUTDOWN_RX		0x0f

#घोषणा AUDIO_APBRIDGEA_PCM_FMT_8			BIT(0)
#घोषणा AUDIO_APBRIDGEA_PCM_FMT_16			BIT(1)
#घोषणा AUDIO_APBRIDGEA_PCM_FMT_24			BIT(2)
#घोषणा AUDIO_APBRIDGEA_PCM_FMT_32			BIT(3)
#घोषणा AUDIO_APBRIDGEA_PCM_FMT_64			BIT(4)

#घोषणा AUDIO_APBRIDGEA_PCM_RATE_5512			BIT(0)
#घोषणा AUDIO_APBRIDGEA_PCM_RATE_8000			BIT(1)
#घोषणा AUDIO_APBRIDGEA_PCM_RATE_11025			BIT(2)
#घोषणा AUDIO_APBRIDGEA_PCM_RATE_16000			BIT(3)
#घोषणा AUDIO_APBRIDGEA_PCM_RATE_22050			BIT(4)
#घोषणा AUDIO_APBRIDGEA_PCM_RATE_32000			BIT(5)
#घोषणा AUDIO_APBRIDGEA_PCM_RATE_44100			BIT(6)
#घोषणा AUDIO_APBRIDGEA_PCM_RATE_48000			BIT(7)
#घोषणा AUDIO_APBRIDGEA_PCM_RATE_64000			BIT(8)
#घोषणा AUDIO_APBRIDGEA_PCM_RATE_88200			BIT(9)
#घोषणा AUDIO_APBRIDGEA_PCM_RATE_96000			BIT(10)
#घोषणा AUDIO_APBRIDGEA_PCM_RATE_176400			BIT(11)
#घोषणा AUDIO_APBRIDGEA_PCM_RATE_192000			BIT(12)

#घोषणा AUDIO_APBRIDGEA_सूचीECTION_TX			BIT(0)
#घोषणा AUDIO_APBRIDGEA_सूचीECTION_RX			BIT(1)

/* The I2S port is passed in the 'index' parameter of the USB request */
/* The CPort is passed in the 'value' parameter of the USB request */

काष्ठा audio_apbridgea_hdr अणु
	__u8	type;
	__le16	i2s_port;
	__u8	data[];
पूर्ण __packed;

काष्ठा audio_apbridgea_set_config_request अणु
	काष्ठा audio_apbridgea_hdr	hdr;
	__le32				क्रमmat;	/* AUDIO_APBRIDGEA_PCM_FMT_* */
	__le32				rate;	/* AUDIO_APBRIDGEA_PCM_RATE_* */
	__le32				mclk_freq; /* XXX Remove? */
पूर्ण __packed;

काष्ठा audio_apbridgea_रेजिस्टर_cport_request अणु
	काष्ठा audio_apbridgea_hdr	hdr;
	__le16				cport;
	__u8				direction;
पूर्ण __packed;

काष्ठा audio_apbridgea_unरेजिस्टर_cport_request अणु
	काष्ठा audio_apbridgea_hdr	hdr;
	__le16				cport;
	__u8				direction;
पूर्ण __packed;

काष्ठा audio_apbridgea_set_tx_data_size_request अणु
	काष्ठा audio_apbridgea_hdr	hdr;
	__le16				size;
पूर्ण __packed;

काष्ठा audio_apbridgea_prepare_tx_request अणु
	काष्ठा audio_apbridgea_hdr	hdr;
पूर्ण __packed;

काष्ठा audio_apbridgea_start_tx_request अणु
	काष्ठा audio_apbridgea_hdr	hdr;
	__le64				बारtamp;
पूर्ण __packed;

काष्ठा audio_apbridgea_stop_tx_request अणु
	काष्ठा audio_apbridgea_hdr	hdr;
पूर्ण __packed;

काष्ठा audio_apbridgea_shutकरोwn_tx_request अणु
	काष्ठा audio_apbridgea_hdr	hdr;
पूर्ण __packed;

काष्ठा audio_apbridgea_set_rx_data_size_request अणु
	काष्ठा audio_apbridgea_hdr	hdr;
	__le16				size;
पूर्ण __packed;

काष्ठा audio_apbridgea_prepare_rx_request अणु
	काष्ठा audio_apbridgea_hdr	hdr;
पूर्ण __packed;

काष्ठा audio_apbridgea_start_rx_request अणु
	काष्ठा audio_apbridgea_hdr	hdr;
पूर्ण __packed;

काष्ठा audio_apbridgea_stop_rx_request अणु
	काष्ठा audio_apbridgea_hdr	hdr;
पूर्ण __packed;

काष्ठा audio_apbridgea_shutकरोwn_rx_request अणु
	काष्ठा audio_apbridgea_hdr	hdr;
पूर्ण __packed;

#पूर्ण_अगर /*__AUDIO_APBRIDGEA_H */
