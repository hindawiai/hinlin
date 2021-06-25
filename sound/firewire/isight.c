<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Apple iSight audio driver
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/माला.स>
#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/tlv.h>
#समावेश "lib.h"
#समावेश "iso-resources.h"
#समावेश "packets-buffer.h"

#घोषणा OUI_APPLE		0x000a27
#घोषणा MODEL_APPLE_ISIGHT	0x000008
#घोषणा SW_ISIGHT_AUDIO		0x000010

#घोषणा REG_AUDIO_ENABLE	0x000
#घोषणा  AUDIO_ENABLE		0x80000000
#घोषणा REG_DEF_AUDIO_GAIN	0x204
#घोषणा REG_GAIN_RAW_START	0x210
#घोषणा REG_GAIN_RAW_END	0x214
#घोषणा REG_GAIN_DB_START	0x218
#घोषणा REG_GAIN_DB_END		0x21c
#घोषणा REG_SAMPLE_RATE_INQUIRY	0x280
#घोषणा REG_ISO_TX_CONFIG	0x300
#घोषणा  SPEED_SHIFT		16
#घोषणा REG_SAMPLE_RATE		0x400
#घोषणा  RATE_48000		0x80000000
#घोषणा REG_GAIN		0x500
#घोषणा REG_MUTE		0x504

#घोषणा MAX_FRAMES_PER_PACKET	475

#घोषणा QUEUE_LENGTH		20

काष्ठा isight अणु
	काष्ठा snd_card *card;
	काष्ठा fw_unit *unit;
	काष्ठा fw_device *device;
	u64 audio_base;
	काष्ठा snd_pcm_substream *pcm;
	काष्ठा mutex mutex;
	काष्ठा iso_packets_buffer buffer;
	काष्ठा fw_iso_resources resources;
	काष्ठा fw_iso_context *context;
	bool pcm_active;
	bool pcm_running;
	bool first_packet;
	पूर्णांक packet_index;
	u32 total_samples;
	अचिन्हित पूर्णांक buffer_poपूर्णांकer;
	अचिन्हित पूर्णांक period_counter;
	s32 gain_min, gain_max;
	अचिन्हित पूर्णांक gain_tlv[4];
पूर्ण;

काष्ठा audio_payload अणु
	__be32 sample_count;
	__be32 signature;
	__be32 sample_total;
	__be32 reserved;
	__be16 samples[2 * MAX_FRAMES_PER_PACKET];
पूर्ण;

MODULE_DESCRIPTION("iSight audio driver");
MODULE_AUTHOR("Clemens Ladisch <clemens@ladisch.de>");
MODULE_LICENSE("GPL v2");

अटल काष्ठा fw_iso_packet audio_packet = अणु
	.payload_length = माप(काष्ठा audio_payload),
	.पूर्णांकerrupt = 1,
	.header_length = 4,
पूर्ण;

अटल व्योम isight_update_poपूर्णांकers(काष्ठा isight *isight, अचिन्हित पूर्णांक count)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = isight->pcm->runसमय;
	अचिन्हित पूर्णांक ptr;

	smp_wmb(); /* update buffer data beक्रमe buffer poपूर्णांकer */

	ptr = isight->buffer_poपूर्णांकer;
	ptr += count;
	अगर (ptr >= runसमय->buffer_size)
		ptr -= runसमय->buffer_size;
	WRITE_ONCE(isight->buffer_poपूर्णांकer, ptr);

	isight->period_counter += count;
	अगर (isight->period_counter >= runसमय->period_size) अणु
		isight->period_counter -= runसमय->period_size;
		snd_pcm_period_elapsed(isight->pcm);
	पूर्ण
पूर्ण

अटल व्योम isight_samples(काष्ठा isight *isight,
			   स्थिर __be16 *samples, अचिन्हित पूर्णांक count)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित पूर्णांक count1;

	अगर (!READ_ONCE(isight->pcm_running))
		वापस;

	runसमय = isight->pcm->runसमय;
	अगर (isight->buffer_poपूर्णांकer + count <= runसमय->buffer_size) अणु
		स_नकल(runसमय->dma_area + isight->buffer_poपूर्णांकer * 4,
		       samples, count * 4);
	पूर्ण अन्यथा अणु
		count1 = runसमय->buffer_size - isight->buffer_poपूर्णांकer;
		स_नकल(runसमय->dma_area + isight->buffer_poपूर्णांकer * 4,
		       samples, count1 * 4);
		samples += count1 * 2;
		स_नकल(runसमय->dma_area, samples, (count - count1) * 4);
	पूर्ण

	isight_update_poपूर्णांकers(isight, count);
पूर्ण

अटल व्योम isight_pcm_पात(काष्ठा isight *isight)
अणु
	अगर (READ_ONCE(isight->pcm_active))
		snd_pcm_stop_xrun(isight->pcm);
पूर्ण

अटल व्योम isight_dropped_samples(काष्ठा isight *isight, अचिन्हित पूर्णांक total)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;
	u32 dropped;
	अचिन्हित पूर्णांक count1;

	अगर (!READ_ONCE(isight->pcm_running))
		वापस;

	runसमय = isight->pcm->runसमय;
	dropped = total - isight->total_samples;
	अगर (dropped < runसमय->buffer_size) अणु
		अगर (isight->buffer_poपूर्णांकer + dropped <= runसमय->buffer_size) अणु
			स_रखो(runसमय->dma_area + isight->buffer_poपूर्णांकer * 4,
			       0, dropped * 4);
		पूर्ण अन्यथा अणु
			count1 = runसमय->buffer_size - isight->buffer_poपूर्णांकer;
			स_रखो(runसमय->dma_area + isight->buffer_poपूर्णांकer * 4,
			       0, count1 * 4);
			स_रखो(runसमय->dma_area, 0, (dropped - count1) * 4);
		पूर्ण
		isight_update_poपूर्णांकers(isight, dropped);
	पूर्ण अन्यथा अणु
		isight_pcm_पात(isight);
	पूर्ण
पूर्ण

अटल व्योम isight_packet(काष्ठा fw_iso_context *context, u32 cycle,
			  माप_प्रकार header_length, व्योम *header, व्योम *data)
अणु
	काष्ठा isight *isight = data;
	स्थिर काष्ठा audio_payload *payload;
	अचिन्हित पूर्णांक index, length, count, total;
	पूर्णांक err;

	अगर (isight->packet_index < 0)
		वापस;
	index = isight->packet_index;
	payload = isight->buffer.packets[index].buffer;
	length = be32_to_cpup(header) >> 16;

	अगर (likely(length >= 16 &&
		   payload->signature == cpu_to_be32(0x73676874/*"sght"*/))) अणु
		count = be32_to_cpu(payload->sample_count);
		अगर (likely(count <= (length - 16) / 4)) अणु
			total = be32_to_cpu(payload->sample_total);
			अगर (unlikely(total != isight->total_samples)) अणु
				अगर (!isight->first_packet)
					isight_dropped_samples(isight, total);
				isight->first_packet = false;
				isight->total_samples = total;
			पूर्ण

			isight_samples(isight, payload->samples, count);
			isight->total_samples += count;
		पूर्ण
	पूर्ण

	err = fw_iso_context_queue(isight->context, &audio_packet,
				   &isight->buffer.iso_buffer,
				   isight->buffer.packets[index].offset);
	अगर (err < 0) अणु
		dev_err(&isight->unit->device, "queueing error: %d\n", err);
		isight_pcm_पात(isight);
		isight->packet_index = -1;
		वापस;
	पूर्ण
	fw_iso_context_queue_flush(isight->context);

	अगर (++index >= QUEUE_LENGTH)
		index = 0;
	isight->packet_index = index;
पूर्ण

अटल पूर्णांक isight_connect(काष्ठा isight *isight)
अणु
	पूर्णांक ch, err;
	__be32 value;

retry_after_bus_reset:
	ch = fw_iso_resources_allocate(&isight->resources,
				       माप(काष्ठा audio_payload),
				       isight->device->max_speed);
	अगर (ch < 0) अणु
		err = ch;
		जाओ error;
	पूर्ण

	value = cpu_to_be32(ch | (isight->device->max_speed << SPEED_SHIFT));
	err = snd_fw_transaction(isight->unit, TCODE_WRITE_QUADLET_REQUEST,
				 isight->audio_base + REG_ISO_TX_CONFIG,
				 &value, 4, FW_FIXED_GENERATION |
				 isight->resources.generation);
	अगर (err == -EAGAIN) अणु
		fw_iso_resources_मुक्त(&isight->resources);
		जाओ retry_after_bus_reset;
	पूर्ण अन्यथा अगर (err < 0) अणु
		जाओ err_resources;
	पूर्ण

	वापस 0;

err_resources:
	fw_iso_resources_मुक्त(&isight->resources);
error:
	वापस err;
पूर्ण

अटल पूर्णांक isight_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	अटल स्थिर काष्ठा snd_pcm_hardware hardware = अणु
		.info = SNDRV_PCM_INFO_MMAP |
			SNDRV_PCM_INFO_MMAP_VALID |
			SNDRV_PCM_INFO_BATCH |
			SNDRV_PCM_INFO_INTERLEAVED |
			SNDRV_PCM_INFO_BLOCK_TRANSFER,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_BE,
		.rates = SNDRV_PCM_RATE_48000,
		.rate_min = 48000,
		.rate_max = 48000,
		.channels_min = 2,
		.channels_max = 2,
		.buffer_bytes_max = 4 * 1024 * 1024,
		.period_bytes_min = MAX_FRAMES_PER_PACKET * 4,
		.period_bytes_max = 1024 * 1024,
		.periods_min = 2,
		.periods_max = अच_पूर्णांक_उच्च,
	पूर्ण;
	काष्ठा isight *isight = substream->निजी_data;

	substream->runसमय->hw = hardware;

	वापस iso_packets_buffer_init(&isight->buffer, isight->unit,
				       QUEUE_LENGTH,
				       माप(काष्ठा audio_payload),
				       DMA_FROM_DEVICE);
पूर्ण

अटल पूर्णांक isight_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा isight *isight = substream->निजी_data;

	iso_packets_buffer_destroy(&isight->buffer, isight->unit);

	वापस 0;
पूर्ण

अटल पूर्णांक isight_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा isight *isight = substream->निजी_data;

	WRITE_ONCE(isight->pcm_active, true);

	वापस 0;
पूर्ण

अटल पूर्णांक reg_पढ़ो(काष्ठा isight *isight, पूर्णांक offset, __be32 *value)
अणु
	वापस snd_fw_transaction(isight->unit, TCODE_READ_QUADLET_REQUEST,
				  isight->audio_base + offset, value, 4, 0);
पूर्ण

अटल पूर्णांक reg_ग_लिखो(काष्ठा isight *isight, पूर्णांक offset, __be32 value)
अणु
	वापस snd_fw_transaction(isight->unit, TCODE_WRITE_QUADLET_REQUEST,
				  isight->audio_base + offset, &value, 4, 0);
पूर्ण

अटल व्योम isight_stop_streaming(काष्ठा isight *isight)
अणु
	__be32 value;

	अगर (!isight->context)
		वापस;

	fw_iso_context_stop(isight->context);
	fw_iso_context_destroy(isight->context);
	isight->context = शून्य;
	fw_iso_resources_मुक्त(&isight->resources);
	value = 0;
	snd_fw_transaction(isight->unit, TCODE_WRITE_QUADLET_REQUEST,
			   isight->audio_base + REG_AUDIO_ENABLE,
			   &value, 4, FW_QUIET);
पूर्ण

अटल पूर्णांक isight_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा isight *isight = substream->निजी_data;

	WRITE_ONCE(isight->pcm_active, false);

	mutex_lock(&isight->mutex);
	isight_stop_streaming(isight);
	mutex_unlock(&isight->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक isight_start_streaming(काष्ठा isight *isight)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (isight->context) अणु
		अगर (isight->packet_index < 0)
			isight_stop_streaming(isight);
		अन्यथा
			वापस 0;
	पूर्ण

	err = reg_ग_लिखो(isight, REG_SAMPLE_RATE, cpu_to_be32(RATE_48000));
	अगर (err < 0)
		जाओ error;

	err = isight_connect(isight);
	अगर (err < 0)
		जाओ error;

	err = reg_ग_लिखो(isight, REG_AUDIO_ENABLE, cpu_to_be32(AUDIO_ENABLE));
	अगर (err < 0)
		जाओ err_resources;

	isight->context = fw_iso_context_create(isight->device->card,
						FW_ISO_CONTEXT_RECEIVE,
						isight->resources.channel,
						isight->device->max_speed,
						4, isight_packet, isight);
	अगर (IS_ERR(isight->context)) अणु
		err = PTR_ERR(isight->context);
		isight->context = शून्य;
		जाओ err_resources;
	पूर्ण

	क्रम (i = 0; i < QUEUE_LENGTH; ++i) अणु
		err = fw_iso_context_queue(isight->context, &audio_packet,
					   &isight->buffer.iso_buffer,
					   isight->buffer.packets[i].offset);
		अगर (err < 0)
			जाओ err_context;
	पूर्ण

	isight->first_packet = true;
	isight->packet_index = 0;

	err = fw_iso_context_start(isight->context, -1, 0,
				   FW_ISO_CONTEXT_MATCH_ALL_TAGS/*?*/);
	अगर (err < 0)
		जाओ err_context;

	वापस 0;

err_context:
	fw_iso_context_destroy(isight->context);
	isight->context = शून्य;
err_resources:
	fw_iso_resources_मुक्त(&isight->resources);
	reg_ग_लिखो(isight, REG_AUDIO_ENABLE, 0);
error:
	वापस err;
पूर्ण

अटल पूर्णांक isight_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा isight *isight = substream->निजी_data;
	पूर्णांक err;

	isight->buffer_poपूर्णांकer = 0;
	isight->period_counter = 0;

	mutex_lock(&isight->mutex);
	err = isight_start_streaming(isight);
	mutex_unlock(&isight->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक isight_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा isight *isight = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		WRITE_ONCE(isight->pcm_running, true);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		WRITE_ONCE(isight->pcm_running, false);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t isight_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा isight *isight = substream->निजी_data;

	वापस READ_ONCE(isight->buffer_poपूर्णांकer);
पूर्ण

अटल पूर्णांक isight_create_pcm(काष्ठा isight *isight)
अणु
	अटल स्थिर काष्ठा snd_pcm_ops ops = अणु
		.खोलो      = isight_खोलो,
		.बंद     = isight_बंद,
		.hw_params = isight_hw_params,
		.hw_मुक्त   = isight_hw_मुक्त,
		.prepare   = isight_prepare,
		.trigger   = isight_trigger,
		.poपूर्णांकer   = isight_poपूर्णांकer,
	पूर्ण;
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(isight->card, "iSight", 0, 0, 1, &pcm);
	अगर (err < 0)
		वापस err;
	pcm->निजी_data = isight;
	म_नकल(pcm->name, "iSight");
	isight->pcm = pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream;
	isight->pcm->ops = &ops;
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक isight_gain_info(काष्ठा snd_kcontrol *ctl,
			    काष्ठा snd_ctl_elem_info *info)
अणु
	काष्ठा isight *isight = ctl->निजी_data;

	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = 1;
	info->value.पूर्णांकeger.min = isight->gain_min;
	info->value.पूर्णांकeger.max = isight->gain_max;

	वापस 0;
पूर्ण

अटल पूर्णांक isight_gain_get(काष्ठा snd_kcontrol *ctl,
			   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा isight *isight = ctl->निजी_data;
	__be32 gain;
	पूर्णांक err;

	err = reg_पढ़ो(isight, REG_GAIN, &gain);
	अगर (err < 0)
		वापस err;

	value->value.पूर्णांकeger.value[0] = (s32)be32_to_cpu(gain);

	वापस 0;
पूर्ण

अटल पूर्णांक isight_gain_put(काष्ठा snd_kcontrol *ctl,
			   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा isight *isight = ctl->निजी_data;

	अगर (value->value.पूर्णांकeger.value[0] < isight->gain_min ||
	    value->value.पूर्णांकeger.value[0] > isight->gain_max)
		वापस -EINVAL;

	वापस reg_ग_लिखो(isight, REG_GAIN,
			 cpu_to_be32(value->value.पूर्णांकeger.value[0]));
पूर्ण

अटल पूर्णांक isight_mute_get(काष्ठा snd_kcontrol *ctl,
			   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा isight *isight = ctl->निजी_data;
	__be32 mute;
	पूर्णांक err;

	err = reg_पढ़ो(isight, REG_MUTE, &mute);
	अगर (err < 0)
		वापस err;

	value->value.पूर्णांकeger.value[0] = !mute;

	वापस 0;
पूर्ण

अटल पूर्णांक isight_mute_put(काष्ठा snd_kcontrol *ctl,
			   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा isight *isight = ctl->निजी_data;

	वापस reg_ग_लिखो(isight, REG_MUTE,
			 (__क्रमce __be32)!value->value.पूर्णांकeger.value[0]);
पूर्ण

अटल पूर्णांक isight_create_mixer(काष्ठा isight *isight)
अणु
	अटल स्थिर काष्ठा snd_kcontrol_new gain_control = अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Mic Capture Volume",
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			  SNDRV_CTL_ELEM_ACCESS_TLV_READ,
		.info = isight_gain_info,
		.get = isight_gain_get,
		.put = isight_gain_put,
	पूर्ण;
	अटल स्थिर काष्ठा snd_kcontrol_new mute_control = अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Mic Capture Switch",
		.info = snd_ctl_boolean_mono_info,
		.get = isight_mute_get,
		.put = isight_mute_put,
	पूर्ण;
	__be32 value;
	काष्ठा snd_kcontrol *ctl;
	पूर्णांक err;

	err = reg_पढ़ो(isight, REG_GAIN_RAW_START, &value);
	अगर (err < 0)
		वापस err;
	isight->gain_min = be32_to_cpu(value);

	err = reg_पढ़ो(isight, REG_GAIN_RAW_END, &value);
	अगर (err < 0)
		वापस err;
	isight->gain_max = be32_to_cpu(value);

	isight->gain_tlv[SNDRV_CTL_TLVO_TYPE] = SNDRV_CTL_TLVT_DB_MINMAX;
	isight->gain_tlv[SNDRV_CTL_TLVO_LEN] = 2 * माप(अचिन्हित पूर्णांक);

	err = reg_पढ़ो(isight, REG_GAIN_DB_START, &value);
	अगर (err < 0)
		वापस err;
	isight->gain_tlv[SNDRV_CTL_TLVO_DB_MINMAX_MIN] =
						(s32)be32_to_cpu(value) * 100;

	err = reg_पढ़ो(isight, REG_GAIN_DB_END, &value);
	अगर (err < 0)
		वापस err;
	isight->gain_tlv[SNDRV_CTL_TLVO_DB_MINMAX_MAX] =
						(s32)be32_to_cpu(value) * 100;

	ctl = snd_ctl_new1(&gain_control, isight);
	अगर (ctl)
		ctl->tlv.p = isight->gain_tlv;
	err = snd_ctl_add(isight->card, ctl);
	अगर (err < 0)
		वापस err;

	err = snd_ctl_add(isight->card, snd_ctl_new1(&mute_control, isight));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम isight_card_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा isight *isight = card->निजी_data;

	fw_iso_resources_destroy(&isight->resources);
पूर्ण

अटल u64 get_unit_base(काष्ठा fw_unit *unit)
अणु
	काष्ठा fw_csr_iterator i;
	पूर्णांक key, value;

	fw_csr_iterator_init(&i, unit->directory);
	जबतक (fw_csr_iterator_next(&i, &key, &value))
		अगर (key == CSR_OFFSET)
			वापस CSR_REGISTER_BASE + value * 4;
	वापस 0;
पूर्ण

अटल पूर्णांक isight_probe(काष्ठा fw_unit *unit,
			स्थिर काष्ठा ieee1394_device_id *id)
अणु
	काष्ठा fw_device *fw_dev = fw_parent_device(unit);
	काष्ठा snd_card *card;
	काष्ठा isight *isight;
	पूर्णांक err;

	err = snd_card_new(&unit->device, -1, शून्य, THIS_MODULE,
			   माप(*isight), &card);
	अगर (err < 0)
		वापस err;

	isight = card->निजी_data;
	isight->card = card;
	mutex_init(&isight->mutex);
	isight->unit = fw_unit_get(unit);
	isight->device = fw_dev;
	isight->audio_base = get_unit_base(unit);
	अगर (!isight->audio_base) अणु
		dev_err(&unit->device, "audio unit base not found\n");
		err = -ENXIO;
		जाओ error;
	पूर्ण
	fw_iso_resources_init(&isight->resources, unit);

	card->निजी_मुक्त = isight_card_मुक्त;

	म_नकल(card->driver, "iSight");
	म_नकल(card->लघुname, "Apple iSight");
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "Apple iSight (GUID %08x%08x) at %s, S%d",
		 fw_dev->config_rom[3], fw_dev->config_rom[4],
		 dev_name(&unit->device), 100 << fw_dev->max_speed);
	म_नकल(card->mixername, "iSight");

	err = isight_create_pcm(isight);
	अगर (err < 0)
		जाओ error;

	err = isight_create_mixer(isight);
	अगर (err < 0)
		जाओ error;

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ error;

	dev_set_drvdata(&unit->device, isight);

	वापस 0;
error:
	snd_card_मुक्त(card);

	mutex_destroy(&isight->mutex);
	fw_unit_put(isight->unit);

	वापस err;
पूर्ण

अटल व्योम isight_bus_reset(काष्ठा fw_unit *unit)
अणु
	काष्ठा isight *isight = dev_get_drvdata(&unit->device);

	अगर (fw_iso_resources_update(&isight->resources) < 0) अणु
		isight_pcm_पात(isight);

		mutex_lock(&isight->mutex);
		isight_stop_streaming(isight);
		mutex_unlock(&isight->mutex);
	पूर्ण
पूर्ण

अटल व्योम isight_हटाओ(काष्ठा fw_unit *unit)
अणु
	काष्ठा isight *isight = dev_get_drvdata(&unit->device);

	isight_pcm_पात(isight);

	snd_card_disconnect(isight->card);

	mutex_lock(&isight->mutex);
	isight_stop_streaming(isight);
	mutex_unlock(&isight->mutex);

	// Block till all of ALSA अक्षरacter devices are released.
	snd_card_मुक्त(isight->card);

	mutex_destroy(&isight->mutex);
	fw_unit_put(isight->unit);
पूर्ण

अटल स्थिर काष्ठा ieee1394_device_id isight_id_table[] = अणु
	अणु
		.match_flags  = IEEE1394_MATCH_SPECIFIER_ID |
				IEEE1394_MATCH_VERSION,
		.specअगरier_id = OUI_APPLE,
		.version      = SW_ISIGHT_AUDIO,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(ieee1394, isight_id_table);

अटल काष्ठा fw_driver isight_driver = अणु
	.driver   = अणु
		.owner	= THIS_MODULE,
		.name	= KBUILD_MODNAME,
		.bus	= &fw_bus_type,
	पूर्ण,
	.probe    = isight_probe,
	.update   = isight_bus_reset,
	.हटाओ   = isight_हटाओ,
	.id_table = isight_id_table,
पूर्ण;

अटल पूर्णांक __init alsa_isight_init(व्योम)
अणु
	वापस driver_रेजिस्टर(&isight_driver.driver);
पूर्ण

अटल व्योम __निकास alsa_isight_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&isight_driver.driver);
पूर्ण

module_init(alsa_isight_init);
module_निकास(alsa_isight_निकास);
