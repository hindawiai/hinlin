<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus audio driver
 * Copyright 2015 Google Inc.
 * Copyright 2015 Linaro Ltd.
 */

#अगर_अघोषित __LINUX_GBAUDIO_CODEC_H
#घोषणा __LINUX_GBAUDIO_CODEC_H

#समावेश <linux/greybus.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>

#घोषणा NAME_SIZE	32
#घोषणा MAX_DAIS	2	/* APB1, APB2 */

क्रमागत अणु
	APB1_PCM = 0,
	APB2_PCM,
	NUM_CODEC_DAIS,
पूर्ण;

/*
 * device_type should be same as defined in audपन.स
 * (Android media layer)
 */
क्रमागत अणु
	GBAUDIO_DEVICE_NONE                     = 0x0,
	/* reserved bits */
	GBAUDIO_DEVICE_BIT_IN                   = 0x80000000,
	GBAUDIO_DEVICE_BIT_DEFAULT              = 0x40000000,
	/* output devices */
	GBAUDIO_DEVICE_OUT_SPEAKER              = 0x2,
	GBAUDIO_DEVICE_OUT_WIRED_HEADSET        = 0x4,
	GBAUDIO_DEVICE_OUT_WIRED_HEADPHONE      = 0x8,
	/* input devices */
	GBAUDIO_DEVICE_IN_BUILTIN_MIC           = GBAUDIO_DEVICE_BIT_IN | 0x4,
	GBAUDIO_DEVICE_IN_WIRED_HEADSET         = GBAUDIO_DEVICE_BIT_IN | 0x10,
पूर्ण;

#घोषणा GBCODEC_JACK_MASK		0x0000FFFF
#घोषणा GBCODEC_JACK_BUTTON_MASK	0xFFFF0000

क्रमागत gbaudio_codec_state अणु
	GBAUDIO_CODEC_SHUTDOWN = 0,
	GBAUDIO_CODEC_STARTUP,
	GBAUDIO_CODEC_HWPARAMS,
	GBAUDIO_CODEC_PREPARE,
	GBAUDIO_CODEC_START,
	GBAUDIO_CODEC_STOP,
पूर्ण;

काष्ठा gbaudio_stream_params अणु
	पूर्णांक state;
	u8 sig_bits, channels;
	u32 क्रमmat, rate;
पूर्ण;

काष्ठा gbaudio_codec_dai अणु
	पूर्णांक id;
	/* runसमय params क्रम playback/capture streams */
	काष्ठा gbaudio_stream_params params[2];
	काष्ठा list_head list;
पूर्ण;

काष्ठा gbaudio_codec_info अणु
	काष्ठा device *dev;
	काष्ठा snd_soc_component *component;
	काष्ठा list_head module_list;
	/* to मुख्यtain runसमय stream params क्रम each DAI */
	काष्ठा list_head dai_list;
	काष्ठा mutex lock;
पूर्ण;

काष्ठा gbaudio_widget अणु
	__u8 id;
	स्थिर अक्षर *name;
	काष्ठा list_head list;
पूर्ण;

काष्ठा gbaudio_control अणु
	__u8 id;
	अक्षर *name;
	अक्षर *wname;
	स्थिर अक्षर * स्थिर *texts;
	पूर्णांक items;
	काष्ठा list_head list;
पूर्ण;

काष्ठा gbaudio_data_connection अणु
	पूर्णांक id;
	__le16 data_cport;
	काष्ठा gb_connection *connection;
	काष्ठा list_head list;
	/* मुख्यtain runसमय state क्रम playback/capture stream */
	पूर्णांक state[2];
पूर्ण;

/* stream direction */
#घोषणा GB_PLAYBACK	BIT(0)
#घोषणा GB_CAPTURE	BIT(1)

क्रमागत gbaudio_module_state अणु
	GBAUDIO_MODULE_OFF = 0,
	GBAUDIO_MODULE_ON,
पूर्ण;

काष्ठा gbaudio_jack अणु
	काष्ठा snd_soc_jack jack;
	काष्ठा list_head list;
पूर्ण;

काष्ठा gbaudio_module_info अणु
	/* module info */
	काष्ठा device *dev;
	पूर्णांक dev_id;	/* check अगर it should be bundle_id/hd_cport_id */
	पूर्णांक vid;
	पूर्णांक pid;
	पूर्णांक type;
	पूर्णांक set_uevent;
	अक्षर vstr[NAME_SIZE];
	अक्षर pstr[NAME_SIZE];
	काष्ठा list_head list;
	/* need to share this info to above user space */
	पूर्णांक manager_id;
	अक्षर name[NAME_SIZE];
	अचिन्हित पूर्णांक ip_devices;
	अचिन्हित पूर्णांक op_devices;

	/* jack related */
	अक्षर jack_name[NAME_SIZE];
	अक्षर button_name[NAME_SIZE];
	पूर्णांक jack_type;
	पूर्णांक jack_mask;
	पूर्णांक button_mask;
	पूर्णांक button_status;
	काष्ठा gbaudio_jack headset;
	काष्ठा gbaudio_jack button;

	/* connection info */
	काष्ठा gb_connection *mgmt_connection;
	माप_प्रकार num_data_connections;
	काष्ठा list_head data_list;

	/* topology related */
	पूर्णांक num_dais;
	पूर्णांक num_controls;
	पूर्णांक num_dapm_widमाला_लो;
	पूर्णांक num_dapm_routes;
	अचिन्हित दीर्घ dai_offset;
	अचिन्हित दीर्घ widget_offset;
	अचिन्हित दीर्घ control_offset;
	अचिन्हित दीर्घ route_offset;
	काष्ठा snd_kcontrol_new *controls;
	काष्ठा snd_soc_dapm_widget *dapm_widमाला_लो;
	काष्ठा snd_soc_dapm_route *dapm_routes;
	काष्ठा snd_soc_dai_driver *dais;

	काष्ठा list_head widget_list;
	काष्ठा list_head ctl_list;
	काष्ठा list_head widget_ctl_list;
	काष्ठा list_head jack_list;

	काष्ठा gb_audio_topology *topology;
पूर्ण;

पूर्णांक gbaudio_tplg_parse_data(काष्ठा gbaudio_module_info *module,
			    काष्ठा gb_audio_topology *tplg_data);
व्योम gbaudio_tplg_release(काष्ठा gbaudio_module_info *module);

पूर्णांक gbaudio_module_update(काष्ठा gbaudio_codec_info *codec,
			  काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा gbaudio_module_info *module,
			  पूर्णांक enable);
पूर्णांक gbaudio_रेजिस्टर_module(काष्ठा gbaudio_module_info *module);
व्योम gbaudio_unरेजिस्टर_module(काष्ठा gbaudio_module_info *module);

/* protocol related */
पूर्णांक gb_audio_gb_get_topology(काष्ठा gb_connection *connection,
			     काष्ठा gb_audio_topology **topology);
पूर्णांक gb_audio_gb_get_control(काष्ठा gb_connection *connection,
			    u8 control_id, u8 index,
			    काष्ठा gb_audio_ctl_elem_value *value);
पूर्णांक gb_audio_gb_set_control(काष्ठा gb_connection *connection,
			    u8 control_id, u8 index,
			    काष्ठा gb_audio_ctl_elem_value *value);
पूर्णांक gb_audio_gb_enable_widget(काष्ठा gb_connection *connection,
			      u8 widget_id);
पूर्णांक gb_audio_gb_disable_widget(काष्ठा gb_connection *connection,
			       u8 widget_id);
पूर्णांक gb_audio_gb_get_pcm(काष्ठा gb_connection *connection,
			u16 data_cport, u32 *क्रमmat,
			u32 *rate, u8 *channels,
			u8 *sig_bits);
पूर्णांक gb_audio_gb_set_pcm(काष्ठा gb_connection *connection,
			u16 data_cport, u32 क्रमmat,
			u32 rate, u8 channels,
			u8 sig_bits);
पूर्णांक gb_audio_gb_set_tx_data_size(काष्ठा gb_connection *connection,
				 u16 data_cport, u16 size);
पूर्णांक gb_audio_gb_activate_tx(काष्ठा gb_connection *connection,
			    u16 data_cport);
पूर्णांक gb_audio_gb_deactivate_tx(काष्ठा gb_connection *connection,
			      u16 data_cport);
पूर्णांक gb_audio_gb_set_rx_data_size(काष्ठा gb_connection *connection,
				 u16 data_cport, u16 size);
पूर्णांक gb_audio_gb_activate_rx(काष्ठा gb_connection *connection,
			    u16 data_cport);
पूर्णांक gb_audio_gb_deactivate_rx(काष्ठा gb_connection *connection,
			      u16 data_cport);
पूर्णांक gb_audio_apbridgea_set_config(काष्ठा gb_connection *connection,
				  __u16 i2s_port, __u32 क्रमmat,
				  __u32 rate, __u32 mclk_freq);
पूर्णांक gb_audio_apbridgea_रेजिस्टर_cport(काष्ठा gb_connection *connection,
				      __u16 i2s_port, __u16 cportid,
				      __u8 direction);
पूर्णांक gb_audio_apbridgea_unरेजिस्टर_cport(काष्ठा gb_connection *connection,
					__u16 i2s_port, __u16 cportid,
					__u8 direction);
पूर्णांक gb_audio_apbridgea_set_tx_data_size(काष्ठा gb_connection *connection,
					__u16 i2s_port, __u16 size);
पूर्णांक gb_audio_apbridgea_prepare_tx(काष्ठा gb_connection *connection,
				  __u16 i2s_port);
पूर्णांक gb_audio_apbridgea_start_tx(काष्ठा gb_connection *connection,
				__u16 i2s_port, __u64 बारtamp);
पूर्णांक gb_audio_apbridgea_stop_tx(काष्ठा gb_connection *connection,
			       __u16 i2s_port);
पूर्णांक gb_audio_apbridgea_shutकरोwn_tx(काष्ठा gb_connection *connection,
				   __u16 i2s_port);
पूर्णांक gb_audio_apbridgea_set_rx_data_size(काष्ठा gb_connection *connection,
					__u16 i2s_port, __u16 size);
पूर्णांक gb_audio_apbridgea_prepare_rx(काष्ठा gb_connection *connection,
				  __u16 i2s_port);
पूर्णांक gb_audio_apbridgea_start_rx(काष्ठा gb_connection *connection,
				__u16 i2s_port);
पूर्णांक gb_audio_apbridgea_stop_rx(काष्ठा gb_connection *connection,
			       __u16 i2s_port);
पूर्णांक gb_audio_apbridgea_shutकरोwn_rx(काष्ठा gb_connection *connection,
				   __u16 i2s_port);

#पूर्ण_अगर /* __LINUX_GBAUDIO_CODEC_H */
