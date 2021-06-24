<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  sst_mfld_platक्रमm.h - Intel MID Platक्रमm driver header file
 *
 *  Copyright (C) 2010 Intel Corp
 *  Author: Vinod Koul <vinod.koul@पूर्णांकel.com>
 *  Author: Harsha Priya <priya.harsha@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#अगर_अघोषित __SST_PLATFORMDRV_H__
#घोषणा __SST_PLATFORMDRV_H__

#समावेश "sst-mfld-dsp.h"
#समावेश "sst-atom-controls.h"

बाह्य काष्ठा sst_device *sst;
बाह्य स्थिर काष्ठा snd_compress_ops sst_platक्रमm_compress_ops;

#घोषणा DRV_NAME "sst"

#घोषणा SST_MONO		1
#घोषणा SST_STEREO		2
#घोषणा SST_MAX_CAP		5

#घोषणा SST_MAX_BUFFER		(800*1024)
#घोषणा SST_MIN_BUFFER		(800*1024)
#घोषणा SST_MIN_PERIOD_BYTES	32
#घोषणा SST_MAX_PERIOD_BYTES	SST_MAX_BUFFER
#घोषणा SST_MIN_PERIODS		2
#घोषणा SST_MAX_PERIODS		(1024*2)
#घोषणा SST_FIFO_SIZE		0

काष्ठा pcm_stream_info अणु
	पूर्णांक str_id;
	व्योम *arg;
	व्योम (*period_elapsed) (व्योम *arg);
	अचिन्हित दीर्घ दीर्घ buffer_ptr;
	अचिन्हित दीर्घ दीर्घ pcm_delay;
	पूर्णांक sfreq;
पूर्ण;

क्रमागत sst_drv_status अणु
	SST_PLATFORM_INIT = 1,
	SST_PLATFORM_STARTED,
	SST_PLATFORM_RUNNING,
	SST_PLATFORM_PAUSED,
	SST_PLATFORM_DROPPED,
पूर्ण;

क्रमागत sst_stream_ops अणु
	STREAM_OPS_PLAYBACK = 0,
	STREAM_OPS_CAPTURE,
पूर्ण;

क्रमागत sst_audio_device_type अणु
	SND_SST_DEVICE_HEADSET = 1,
	SND_SST_DEVICE_IHF,
	SND_SST_DEVICE_VIBRA,
	SND_SST_DEVICE_HAPTIC,
	SND_SST_DEVICE_CAPTURE,
	SND_SST_DEVICE_COMPRESS,
पूर्ण;

/* PCM Parameters */
काष्ठा sst_pcm_params अणु
	u16 codec;	/* codec type */
	u8 num_chan;	/* 1=Mono, 2=Stereo */
	u8 pcm_wd_sz;	/* 16/24 - bit*/
	u32 reserved;	/* Bitrate in bits per second */
	u32 sfreq;	/* Sampling rate in Hz */
	u32 ring_buffer_size;
	u32 period_count;	/* period elapsed in samples*/
	u32 ring_buffer_addr;
पूर्ण;

काष्ठा sst_stream_params अणु
	u32 result;
	u32 stream_id;
	u8 codec;
	u8 ops;
	u8 stream_type;
	u8 device_type;
	काष्ठा sst_pcm_params sparams;
पूर्ण;

काष्ठा sst_compress_cb अणु
	व्योम *param;
	व्योम (*compr_cb)(व्योम *param);
	व्योम *drain_cb_param;
	व्योम (*drain_notअगरy)(व्योम *param);
पूर्ण;

काष्ठा compress_sst_ops अणु
	स्थिर अक्षर *name;
	पूर्णांक (*खोलो)(काष्ठा device *dev,
		काष्ठा snd_sst_params *str_params, काष्ठा sst_compress_cb *cb);
	पूर्णांक (*stream_start)(काष्ठा device *dev, अचिन्हित पूर्णांक str_id);
	पूर्णांक (*stream_drop)(काष्ठा device *dev, अचिन्हित पूर्णांक str_id);
	पूर्णांक (*stream_drain)(काष्ठा device *dev, अचिन्हित पूर्णांक str_id);
	पूर्णांक (*stream_partial_drain)(काष्ठा device *dev,	अचिन्हित पूर्णांक str_id);
	पूर्णांक (*stream_छोड़ो)(काष्ठा device *dev, अचिन्हित पूर्णांक str_id);
	पूर्णांक (*stream_छोड़ो_release)(काष्ठा device *dev,	अचिन्हित पूर्णांक str_id);

	पूर्णांक (*tstamp)(काष्ठा device *dev, अचिन्हित पूर्णांक str_id,
			काष्ठा snd_compr_tstamp *tstamp);
	पूर्णांक (*ack)(काष्ठा device *dev, अचिन्हित पूर्णांक str_id,
			अचिन्हित दीर्घ bytes);
	पूर्णांक (*बंद)(काष्ठा device *dev, अचिन्हित पूर्णांक str_id);
	पूर्णांक (*get_caps)(काष्ठा snd_compr_caps *caps);
	पूर्णांक (*get_codec_caps)(काष्ठा snd_compr_codec_caps *codec);
	पूर्णांक (*set_metadata)(काष्ठा device *dev,	अचिन्हित पूर्णांक str_id,
			काष्ठा snd_compr_metadata *mdata);
	पूर्णांक (*घातer)(काष्ठा device *dev, bool state);
पूर्ण;

काष्ठा sst_ops अणु
	पूर्णांक (*खोलो)(काष्ठा device *dev, काष्ठा snd_sst_params *str_param);
	पूर्णांक (*stream_init)(काष्ठा device *dev, काष्ठा pcm_stream_info *str_info);
	पूर्णांक (*stream_start)(काष्ठा device *dev, पूर्णांक str_id);
	पूर्णांक (*stream_drop)(काष्ठा device *dev, पूर्णांक str_id);
	पूर्णांक (*stream_छोड़ो)(काष्ठा device *dev, पूर्णांक str_id);
	पूर्णांक (*stream_छोड़ो_release)(काष्ठा device *dev, पूर्णांक str_id);
	पूर्णांक (*stream_पढ़ो_tstamp)(काष्ठा device *dev, काष्ठा pcm_stream_info *str_info);
	पूर्णांक (*send_byte_stream)(काष्ठा device *dev, काष्ठा snd_sst_bytes_v2 *bytes);
	पूर्णांक (*बंद)(काष्ठा device *dev, अचिन्हित पूर्णांक str_id);
	पूर्णांक (*घातer)(काष्ठा device *dev, bool state);
पूर्ण;

काष्ठा sst_runसमय_stream अणु
	पूर्णांक     stream_status;
	अचिन्हित पूर्णांक id;
	माप_प्रकार bytes_written;
	काष्ठा pcm_stream_info stream_info;
	काष्ठा sst_ops *ops;
	काष्ठा compress_sst_ops *compr_ops;
	spinlock_t	status_lock;
पूर्ण;

काष्ठा sst_device अणु
	अक्षर *name;
	काष्ठा device *dev;
	काष्ठा sst_ops *ops;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा compress_sst_ops *compr_ops;
पूर्ण;

काष्ठा sst_data;

पूर्णांक sst_dsp_init_v2_dpcm(काष्ठा snd_soc_component *component);
पूर्णांक sst_send_pipe_gains(काष्ठा snd_soc_dai *dai, पूर्णांक stream, पूर्णांक mute);
पूर्णांक send_ssp_cmd(काष्ठा snd_soc_dai *dai, स्थिर अक्षर *id, bool enable);
पूर्णांक sst_handle_vb_समयr(काष्ठा snd_soc_dai *dai, bool enable);

व्योम sst_set_stream_status(काष्ठा sst_runसमय_stream *stream, पूर्णांक state);
पूर्णांक sst_fill_stream_params(व्योम *substream, स्थिर काष्ठा sst_data *ctx,
			   काष्ठा snd_sst_params *str_params, bool is_compress);

काष्ठा sst_algo_पूर्णांक_control_v2 अणु
	काष्ठा soc_mixer_control mc;
	u16 module_id; /* module identअगरieer */
	u16 pipe_id; /* location info: pipe_id + instance_id */
	u16 instance_id;
	अचिन्हित पूर्णांक value; /* Value received is stored here */
पूर्ण;
काष्ठा sst_data अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा sst_platक्रमm_data *pdata;
	काष्ठा snd_sst_bytes_v2 *byte_stream;
	काष्ठा mutex lock;
	काष्ठा snd_soc_card *soc_card;
	काष्ठा sst_cmd_sba_hw_set_ssp ssp_cmd;
पूर्ण;
पूर्णांक sst_रेजिस्टर_dsp(काष्ठा sst_device *dev);
पूर्णांक sst_unरेजिस्टर_dsp(काष्ठा sst_device *dev);
#पूर्ण_अगर
