<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT

/*
 * Xen para-भव sound device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#समावेश <xen/xenbus.h>

#समावेश <xen/पूर्णांकerface/io/sndअगर.h>

#समावेश "xen_snd_front.h"
#समावेश "xen_snd_front_cfg.h"

/* Maximum number of supported streams. */
#घोषणा VSND_MAX_STREAM		8

काष्ठा cfg_hw_sample_rate अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक value;
पूर्ण;

अटल स्थिर काष्ठा cfg_hw_sample_rate CFG_HW_SUPPORTED_RATES[] = अणु
	अणु .name = "5512",   .mask = SNDRV_PCM_RATE_5512,   .value = 5512 पूर्ण,
	अणु .name = "8000",   .mask = SNDRV_PCM_RATE_8000,   .value = 8000 पूर्ण,
	अणु .name = "11025",  .mask = SNDRV_PCM_RATE_11025,  .value = 11025 पूर्ण,
	अणु .name = "16000",  .mask = SNDRV_PCM_RATE_16000,  .value = 16000 पूर्ण,
	अणु .name = "22050",  .mask = SNDRV_PCM_RATE_22050,  .value = 22050 पूर्ण,
	अणु .name = "32000",  .mask = SNDRV_PCM_RATE_32000,  .value = 32000 पूर्ण,
	अणु .name = "44100",  .mask = SNDRV_PCM_RATE_44100,  .value = 44100 पूर्ण,
	अणु .name = "48000",  .mask = SNDRV_PCM_RATE_48000,  .value = 48000 पूर्ण,
	अणु .name = "64000",  .mask = SNDRV_PCM_RATE_64000,  .value = 64000 पूर्ण,
	अणु .name = "96000",  .mask = SNDRV_PCM_RATE_96000,  .value = 96000 पूर्ण,
	अणु .name = "176400", .mask = SNDRV_PCM_RATE_176400, .value = 176400 पूर्ण,
	अणु .name = "192000", .mask = SNDRV_PCM_RATE_192000, .value = 192000 पूर्ण,
पूर्ण;

काष्ठा cfg_hw_sample_क्रमmat अणु
	स्थिर अक्षर *name;
	u64 mask;
पूर्ण;

अटल स्थिर काष्ठा cfg_hw_sample_क्रमmat CFG_HW_SUPPORTED_FORMATS[] = अणु
	अणु
		.name = XENSND_PCM_FORMAT_U8_STR,
		.mask = SNDRV_PCM_FMTBIT_U8
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_S8_STR,
		.mask = SNDRV_PCM_FMTBIT_S8
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_U16_LE_STR,
		.mask = SNDRV_PCM_FMTBIT_U16_LE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_U16_BE_STR,
		.mask = SNDRV_PCM_FMTBIT_U16_BE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_S16_LE_STR,
		.mask = SNDRV_PCM_FMTBIT_S16_LE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_S16_BE_STR,
		.mask = SNDRV_PCM_FMTBIT_S16_BE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_U24_LE_STR,
		.mask = SNDRV_PCM_FMTBIT_U24_LE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_U24_BE_STR,
		.mask = SNDRV_PCM_FMTBIT_U24_BE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_S24_LE_STR,
		.mask = SNDRV_PCM_FMTBIT_S24_LE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_S24_BE_STR,
		.mask = SNDRV_PCM_FMTBIT_S24_BE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_U32_LE_STR,
		.mask = SNDRV_PCM_FMTBIT_U32_LE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_U32_BE_STR,
		.mask = SNDRV_PCM_FMTBIT_U32_BE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_S32_LE_STR,
		.mask = SNDRV_PCM_FMTBIT_S32_LE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_S32_BE_STR,
		.mask = SNDRV_PCM_FMTBIT_S32_BE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_A_LAW_STR,
		.mask = SNDRV_PCM_FMTBIT_A_LAW
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_MU_LAW_STR,
		.mask = SNDRV_PCM_FMTBIT_MU_LAW
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_F32_LE_STR,
		.mask = SNDRV_PCM_FMTBIT_FLOAT_LE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_F32_BE_STR,
		.mask = SNDRV_PCM_FMTBIT_FLOAT_BE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_F64_LE_STR,
		.mask = SNDRV_PCM_FMTBIT_FLOAT64_LE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_F64_BE_STR,
		.mask = SNDRV_PCM_FMTBIT_FLOAT64_BE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_IEC958_SUBFRAME_LE_STR,
		.mask = SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_IEC958_SUBFRAME_BE_STR,
		.mask = SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_BE
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_IMA_ADPCM_STR,
		.mask = SNDRV_PCM_FMTBIT_IMA_ADPCM
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_MPEG_STR,
		.mask = SNDRV_PCM_FMTBIT_MPEG
	पूर्ण,
	अणु
		.name = XENSND_PCM_FORMAT_GSM_STR,
		.mask = SNDRV_PCM_FMTBIT_GSM
	पूर्ण,
पूर्ण;

अटल व्योम cfg_hw_rates(अक्षर *list, अचिन्हित पूर्णांक len,
			 स्थिर अक्षर *path, काष्ठा snd_pcm_hardware *pcm_hw)
अणु
	अक्षर *cur_rate;
	अचिन्हित पूर्णांक cur_mask;
	अचिन्हित पूर्णांक cur_value;
	अचिन्हित पूर्णांक rates;
	अचिन्हित पूर्णांक rate_min;
	अचिन्हित पूर्णांक rate_max;
	पूर्णांक i;

	rates = 0;
	rate_min = -1;
	rate_max = 0;
	जबतक ((cur_rate = strsep(&list, XENSND_LIST_SEPARATOR))) अणु
		क्रम (i = 0; i < ARRAY_SIZE(CFG_HW_SUPPORTED_RATES); i++)
			अगर (!strnहालcmp(cur_rate,
					 CFG_HW_SUPPORTED_RATES[i].name,
					 XENSND_SAMPLE_RATE_MAX_LEN)) अणु
				cur_mask = CFG_HW_SUPPORTED_RATES[i].mask;
				cur_value = CFG_HW_SUPPORTED_RATES[i].value;
				rates |= cur_mask;
				अगर (rate_min > cur_value)
					rate_min = cur_value;
				अगर (rate_max < cur_value)
					rate_max = cur_value;
			पूर्ण
	पूर्ण

	अगर (rates) अणु
		pcm_hw->rates = rates;
		pcm_hw->rate_min = rate_min;
		pcm_hw->rate_max = rate_max;
	पूर्ण
पूर्ण

अटल व्योम cfg_क्रमmats(अक्षर *list, अचिन्हित पूर्णांक len,
			स्थिर अक्षर *path, काष्ठा snd_pcm_hardware *pcm_hw)
अणु
	u64 क्रमmats;
	अक्षर *cur_क्रमmat;
	पूर्णांक i;

	क्रमmats = 0;
	जबतक ((cur_क्रमmat = strsep(&list, XENSND_LIST_SEPARATOR))) अणु
		क्रम (i = 0; i < ARRAY_SIZE(CFG_HW_SUPPORTED_FORMATS); i++)
			अगर (!strnहालcmp(cur_क्रमmat,
					 CFG_HW_SUPPORTED_FORMATS[i].name,
					 XENSND_SAMPLE_FORMAT_MAX_LEN))
				क्रमmats |= CFG_HW_SUPPORTED_FORMATS[i].mask;
	पूर्ण

	अगर (क्रमmats)
		pcm_hw->क्रमmats = क्रमmats;
पूर्ण

#घोषणा MAX_BUFFER_SIZE		(64 * 1024)
#घोषणा MIN_PERIOD_SIZE		64
#घोषणा MAX_PERIOD_SIZE		MAX_BUFFER_SIZE
#घोषणा USE_FORMATS		(SNDRV_PCM_FMTBIT_U8 | \
				 SNDRV_PCM_FMTBIT_S16_LE)
#घोषणा USE_RATE		(SNDRV_PCM_RATE_CONTINUOUS | \
				 SNDRV_PCM_RATE_8000_48000)
#घोषणा USE_RATE_MIN		5512
#घोषणा USE_RATE_MAX		48000
#घोषणा USE_CHANNELS_MIN	1
#घोषणा USE_CHANNELS_MAX	2
#घोषणा USE_PERIODS_MIN		2
#घोषणा USE_PERIODS_MAX		(MAX_BUFFER_SIZE / MIN_PERIOD_SIZE)

अटल स्थिर काष्ठा snd_pcm_hardware SND_DRV_PCM_HW_DEFAULT = अणु
	.info = (SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_RESUME |
		 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats = USE_FORMATS,
	.rates = USE_RATE,
	.rate_min = USE_RATE_MIN,
	.rate_max = USE_RATE_MAX,
	.channels_min = USE_CHANNELS_MIN,
	.channels_max = USE_CHANNELS_MAX,
	.buffer_bytes_max = MAX_BUFFER_SIZE,
	.period_bytes_min = MIN_PERIOD_SIZE,
	.period_bytes_max = MAX_PERIOD_SIZE,
	.periods_min = USE_PERIODS_MIN,
	.periods_max = USE_PERIODS_MAX,
	.fअगरo_size = 0,
पूर्ण;

अटल व्योम cfg_पढ़ो_pcm_hw(स्थिर अक्षर *path,
			    काष्ठा snd_pcm_hardware *parent_pcm_hw,
			    काष्ठा snd_pcm_hardware *pcm_hw)
अणु
	अक्षर *list;
	पूर्णांक val;
	माप_प्रकार buf_sz;
	अचिन्हित पूर्णांक len;

	/* Inherit parent's PCM HW and पढ़ो overrides from XenStore. */
	अगर (parent_pcm_hw)
		*pcm_hw = *parent_pcm_hw;
	अन्यथा
		*pcm_hw = SND_DRV_PCM_HW_DEFAULT;

	val = xenbus_पढ़ो_अचिन्हित(path, XENSND_FIELD_CHANNELS_MIN, 0);
	अगर (val)
		pcm_hw->channels_min = val;

	val = xenbus_पढ़ो_अचिन्हित(path, XENSND_FIELD_CHANNELS_MAX, 0);
	अगर (val)
		pcm_hw->channels_max = val;

	list = xenbus_पढ़ो(XBT_NIL, path, XENSND_FIELD_SAMPLE_RATES, &len);
	अगर (!IS_ERR(list)) अणु
		cfg_hw_rates(list, len, path, pcm_hw);
		kमुक्त(list);
	पूर्ण

	list = xenbus_पढ़ो(XBT_NIL, path, XENSND_FIELD_SAMPLE_FORMATS, &len);
	अगर (!IS_ERR(list)) अणु
		cfg_क्रमmats(list, len, path, pcm_hw);
		kमुक्त(list);
	पूर्ण

	buf_sz = xenbus_पढ़ो_अचिन्हित(path, XENSND_FIELD_BUFFER_SIZE, 0);
	अगर (buf_sz)
		pcm_hw->buffer_bytes_max = buf_sz;

	/* Update configuration to match new values. */
	अगर (pcm_hw->channels_min > pcm_hw->channels_max)
		pcm_hw->channels_min = pcm_hw->channels_max;

	अगर (pcm_hw->rate_min > pcm_hw->rate_max)
		pcm_hw->rate_min = pcm_hw->rate_max;

	pcm_hw->period_bytes_max = pcm_hw->buffer_bytes_max;

	pcm_hw->periods_max = pcm_hw->period_bytes_max /
		pcm_hw->period_bytes_min;
पूर्ण

अटल पूर्णांक cfg_get_stream_type(स्थिर अक्षर *path, पूर्णांक index,
			       पूर्णांक *num_pb, पूर्णांक *num_cap)
अणु
	अक्षर *str = शून्य;
	अक्षर *stream_path;
	पूर्णांक ret;

	*num_pb = 0;
	*num_cap = 0;
	stream_path = kaप्र_लिखो(GFP_KERNEL, "%s/%d", path, index);
	अगर (!stream_path) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	str = xenbus_पढ़ो(XBT_NIL, stream_path, XENSND_FIELD_TYPE, शून्य);
	अगर (IS_ERR(str)) अणु
		ret = PTR_ERR(str);
		str = शून्य;
		जाओ fail;
	पूर्ण

	अगर (!strnहालcmp(str, XENSND_STREAM_TYPE_PLAYBACK,
			 माप(XENSND_STREAM_TYPE_PLAYBACK))) अणु
		(*num_pb)++;
	पूर्ण अन्यथा अगर (!strnहालcmp(str, XENSND_STREAM_TYPE_CAPTURE,
			      माप(XENSND_STREAM_TYPE_CAPTURE))) अणु
		(*num_cap)++;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ fail;
	पूर्ण
	ret = 0;

fail:
	kमुक्त(stream_path);
	kमुक्त(str);
	वापस ret;
पूर्ण

अटल पूर्णांक cfg_stream(काष्ठा xen_snd_front_info *front_info,
		      काष्ठा xen_front_cfg_pcm_instance *pcm_instance,
		      स्थिर अक्षर *path, पूर्णांक index, पूर्णांक *cur_pb, पूर्णांक *cur_cap,
		      पूर्णांक *stream_cnt)
अणु
	अक्षर *str = शून्य;
	अक्षर *stream_path;
	काष्ठा xen_front_cfg_stream *stream;
	पूर्णांक ret;

	stream_path = devm_kaप्र_लिखो(&front_info->xb_dev->dev,
				     GFP_KERNEL, "%s/%d", path, index);
	अगर (!stream_path) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	str = xenbus_पढ़ो(XBT_NIL, stream_path, XENSND_FIELD_TYPE, शून्य);
	अगर (IS_ERR(str)) अणु
		ret = PTR_ERR(str);
		str = शून्य;
		जाओ fail;
	पूर्ण

	अगर (!strnहालcmp(str, XENSND_STREAM_TYPE_PLAYBACK,
			 माप(XENSND_STREAM_TYPE_PLAYBACK))) अणु
		stream = &pcm_instance->streams_pb[(*cur_pb)++];
	पूर्ण अन्यथा अगर (!strnहालcmp(str, XENSND_STREAM_TYPE_CAPTURE,
			      माप(XENSND_STREAM_TYPE_CAPTURE))) अणु
		stream = &pcm_instance->streams_cap[(*cur_cap)++];
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	/* Get next stream index. */
	stream->index = (*stream_cnt)++;
	stream->xenstore_path = stream_path;
	/*
	 * Check XenStore अगर PCM HW configuration exists क्रम this stream
	 * and update अगर so, e.g. we inherit all values from device's PCM HW,
	 * but can still override some of the values क्रम the stream.
	 */
	cfg_पढ़ो_pcm_hw(stream->xenstore_path,
			&pcm_instance->pcm_hw, &stream->pcm_hw);
	ret = 0;

fail:
	kमुक्त(str);
	वापस ret;
पूर्ण

अटल पूर्णांक cfg_device(काष्ठा xen_snd_front_info *front_info,
		      काष्ठा xen_front_cfg_pcm_instance *pcm_instance,
		      काष्ठा snd_pcm_hardware *parent_pcm_hw,
		      स्थिर अक्षर *path, पूर्णांक node_index, पूर्णांक *stream_cnt)
अणु
	अक्षर *str;
	अक्षर *device_path;
	पूर्णांक ret, i, num_streams;
	पूर्णांक num_pb, num_cap;
	पूर्णांक cur_pb, cur_cap;
	अक्षर node[3];

	device_path = kaप्र_लिखो(GFP_KERNEL, "%s/%d", path, node_index);
	अगर (!device_path)
		वापस -ENOMEM;

	str = xenbus_पढ़ो(XBT_NIL, device_path, XENSND_FIELD_DEVICE_NAME, शून्य);
	अगर (!IS_ERR(str)) अणु
		strscpy(pcm_instance->name, str, माप(pcm_instance->name));
		kमुक्त(str);
	पूर्ण

	pcm_instance->device_id = node_index;

	/*
	 * Check XenStore अगर PCM HW configuration exists क्रम this device
	 * and update अगर so, e.g. we inherit all values from card's PCM HW,
	 * but can still override some of the values क्रम the device.
	 */
	cfg_पढ़ो_pcm_hw(device_path, parent_pcm_hw, &pcm_instance->pcm_hw);

	/* Find out how many streams were configured in Xen store. */
	num_streams = 0;
	करो अणु
		snम_लिखो(node, माप(node), "%d", num_streams);
		अगर (!xenbus_exists(XBT_NIL, device_path, node))
			अवरोध;

		num_streams++;
	पूर्ण जबतक (num_streams < VSND_MAX_STREAM);

	pcm_instance->num_streams_pb = 0;
	pcm_instance->num_streams_cap = 0;
	/* Get number of playback and capture streams. */
	क्रम (i = 0; i < num_streams; i++) अणु
		ret = cfg_get_stream_type(device_path, i, &num_pb, &num_cap);
		अगर (ret < 0)
			जाओ fail;

		pcm_instance->num_streams_pb += num_pb;
		pcm_instance->num_streams_cap += num_cap;
	पूर्ण

	अगर (pcm_instance->num_streams_pb) अणु
		pcm_instance->streams_pb =
				devm_kसुस्मृति(&front_info->xb_dev->dev,
					     pcm_instance->num_streams_pb,
					     माप(काष्ठा xen_front_cfg_stream),
					     GFP_KERNEL);
		अगर (!pcm_instance->streams_pb) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (pcm_instance->num_streams_cap) अणु
		pcm_instance->streams_cap =
				devm_kसुस्मृति(&front_info->xb_dev->dev,
					     pcm_instance->num_streams_cap,
					     माप(काष्ठा xen_front_cfg_stream),
					     GFP_KERNEL);
		अगर (!pcm_instance->streams_cap) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण
	पूर्ण

	cur_pb = 0;
	cur_cap = 0;
	क्रम (i = 0; i < num_streams; i++) अणु
		ret = cfg_stream(front_info, pcm_instance, device_path, i,
				 &cur_pb, &cur_cap, stream_cnt);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण
	ret = 0;

fail:
	kमुक्त(device_path);
	वापस ret;
पूर्ण

पूर्णांक xen_snd_front_cfg_card(काष्ठा xen_snd_front_info *front_info,
			   पूर्णांक *stream_cnt)
अणु
	काष्ठा xenbus_device *xb_dev = front_info->xb_dev;
	काष्ठा xen_front_cfg_card *cfg = &front_info->cfg;
	पूर्णांक ret, num_devices, i;
	अक्षर node[3];

	*stream_cnt = 0;
	num_devices = 0;
	करो अणु
		snम_लिखो(node, माप(node), "%d", num_devices);
		अगर (!xenbus_exists(XBT_NIL, xb_dev->nodename, node))
			अवरोध;

		num_devices++;
	पूर्ण जबतक (num_devices < SNDRV_PCM_DEVICES);

	अगर (!num_devices) अणु
		dev_warn(&xb_dev->dev,
			 "No devices configured for sound card at %s\n",
			 xb_dev->nodename);
		वापस -ENODEV;
	पूर्ण

	/* Start from शेष PCM HW configuration क्रम the card. */
	cfg_पढ़ो_pcm_hw(xb_dev->nodename, शून्य, &cfg->pcm_hw);

	cfg->pcm_instances =
			devm_kसुस्मृति(&front_info->xb_dev->dev, num_devices,
				     माप(काष्ठा xen_front_cfg_pcm_instance),
				     GFP_KERNEL);
	अगर (!cfg->pcm_instances)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_devices; i++) अणु
		ret = cfg_device(front_info, &cfg->pcm_instances[i],
				 &cfg->pcm_hw, xb_dev->nodename, i, stream_cnt);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	cfg->num_pcm_instances = num_devices;
	वापस 0;
पूर्ण

