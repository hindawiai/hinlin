<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Asihpi soundcard
 *  Copyright (c) by AudioScience Inc <support@audioscience.com>
 *
 *  The following is not a condition of use, merely a request:
 *  If you modअगरy this program, particularly अगर you fix errors, AudioScience Inc
 *  would appreciate it अगर you grant us the right to use those modअगरications
 *  क्रम any purpose including commercial applications.
 */

#समावेश "hpi_internal.h"
#समावेश "hpi_version.h"
#समावेश "hpimsginit.h"
#समावेश "hpioctl.h"
#समावेश "hpicmn.h"

#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/info.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/hwdep.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("AudioScience inc. <support@audioscience.com>");
MODULE_DESCRIPTION("AudioScience ALSA ASI5xxx ASI6xxx ASI87xx ASI89xx "
			HPI_VER_STRING);

#अगर defined CONFIG_SND_DEBUG_VERBOSE
/**
 * snd_prपूर्णांकddd - very verbose debug prपूर्णांकk
 * @क्रमmat: क्रमmat string
 *
 * Works like snd_prपूर्णांकk() क्रम debugging purposes.
 * Ignored when CONFIG_SND_DEBUG_VERBOSE is not set.
 * Must set snd module debug parameter to 3 to enable at runसमय.
 */
#घोषणा snd_prपूर्णांकddd(क्रमmat, args...) \
	__snd_prपूर्णांकk(3, __खाता__, __LINE__, क्रमmat, ##args)
#अन्यथा
#घोषणा snd_prपूर्णांकddd(क्रमmat, args...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;
अटल bool enable_hpi_hwdep = 1;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "ALSA index value for AudioScience soundcard.");

module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ALSA ID string for AudioScience soundcard.");

module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "ALSA enable AudioScience soundcard.");

module_param(enable_hpi_hwdep, bool, 0644);
MODULE_PARM_DESC(enable_hpi_hwdep,
		"ALSA enable HPI hwdep for AudioScience soundcard ");

/* identअगरy driver */
#अगर_घोषित KERNEL_ALSA_BUILD
अटल अक्षर *build_info = "Built using headers from kernel source";
module_param(build_info, अक्षरp, 0444);
MODULE_PARM_DESC(build_info, "Built using headers from kernel source");
#अन्यथा
अटल अक्षर *build_info = "Built within ALSA source";
module_param(build_info, अक्षरp, 0444);
MODULE_PARM_DESC(build_info, "Built within ALSA source");
#पूर्ण_अगर

/* set to 1 to dump every control from adapter to log */
अटल स्थिर पूर्णांक mixer_dump;

#घोषणा DEFAULT_SAMPLERATE 44100
अटल पूर्णांक adapter_fs = DEFAULT_SAMPLERATE;

/* शेषs */
#घोषणा PERIODS_MIN 2
#घोषणा PERIOD_BYTES_MIN  2048
#घोषणा BUFFER_BYTES_MAX (512 * 1024)

#घोषणा MAX_CLOCKSOURCES (HPI_SAMPLECLOCK_SOURCE_LAST + 1 + 7)

काष्ठा clk_source अणु
	पूर्णांक source;
	पूर्णांक index;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा clk_cache अणु
	पूर्णांक count;
	पूर्णांक has_local;
	काष्ठा clk_source s[MAX_CLOCKSOURCES];
पूर्ण;

/* Per card data */
काष्ठा snd_card_asihpi अणु
	काष्ठा snd_card *card;
	काष्ठा pci_dev *pci;
	काष्ठा hpi_adapter *hpi;

	/* In low latency mode there is only one stream, a poपूर्णांकer to its
	 * निजी data is stored here on trigger and cleared on stop.
	 * The पूर्णांकerrupt handler uses it as a parameter when calling
	 * snd_card_asihpi_समयr_function().
	 */
	काष्ठा snd_card_asihpi_pcm *llmode_streampriv;
	व्योम (*pcm_start)(काष्ठा snd_pcm_substream *substream);
	व्योम (*pcm_stop)(काष्ठा snd_pcm_substream *substream);

	u32 h_mixer;
	काष्ठा clk_cache cc;

	u16 can_dma;
	u16 support_grouping;
	u16 support_mrx;
	u16 update_पूर्णांकerval_frames;
	u16 in_max_chans;
	u16 out_max_chans;
	u16 in_min_chans;
	u16 out_min_chans;
पूर्ण;

/* Per stream data */
काष्ठा snd_card_asihpi_pcm अणु
	काष्ठा समयr_list समयr;
	अचिन्हित पूर्णांक respawn_समयr;
	अचिन्हित पूर्णांक hpi_buffer_attached;
	अचिन्हित पूर्णांक buffer_bytes;
	अचिन्हित पूर्णांक period_bytes;
	अचिन्हित पूर्णांक bytes_per_sec;
	अचिन्हित पूर्णांक pcm_buf_host_rw_ofs; /* Host R/W pos */
	अचिन्हित पूर्णांक pcm_buf_dma_ofs;	/* DMA R/W offset in buffer */
	अचिन्हित पूर्णांक pcm_buf_elapsed_dma_ofs;	/* DMA R/W offset in buffer */
	अचिन्हित पूर्णांक drained_count;
	काष्ठा snd_pcm_substream *substream;
	u32 h_stream;
	काष्ठा hpi_क्रमmat क्रमmat;
पूर्ण;

/* universal stream verbs work with out or in stream handles */

/* Functions to allow driver to give a buffer to HPI क्रम busmastering */

अटल u16 hpi_stream_host_buffer_attach(
	u32 h_stream,   /* handle to outstream. */
	u32 size_in_bytes, /* size in bytes of bus mastering buffer */
	u32 pci_address
)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	अचिन्हित पूर्णांक obj = hpi_handle_object(h_stream);

	अगर (!h_stream)
		वापस HPI_ERROR_INVALID_OBJ;
	hpi_init_message_response(&hm, &hr, obj,
			obj == HPI_OBJ_OSTREAM ?
				HPI_OSTREAM_HOSTBUFFER_ALLOC :
				HPI_ISTREAM_HOSTBUFFER_ALLOC);

	hpi_handle_to_indexes(h_stream, &hm.adapter_index,
				&hm.obj_index);

	hm.u.d.u.buffer.buffer_size = size_in_bytes;
	hm.u.d.u.buffer.pci_address = pci_address;
	hm.u.d.u.buffer.command = HPI_BUFFER_CMD_INTERNAL_GRANTADAPTER;
	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

अटल u16 hpi_stream_host_buffer_detach(u32  h_stream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	अचिन्हित पूर्णांक obj = hpi_handle_object(h_stream);

	अगर (!h_stream)
		वापस HPI_ERROR_INVALID_OBJ;

	hpi_init_message_response(&hm, &hr,  obj,
			obj == HPI_OBJ_OSTREAM ?
				HPI_OSTREAM_HOSTBUFFER_FREE :
				HPI_ISTREAM_HOSTBUFFER_FREE);

	hpi_handle_to_indexes(h_stream, &hm.adapter_index,
				&hm.obj_index);
	hm.u.d.u.buffer.command = HPI_BUFFER_CMD_INTERNAL_REVOKEADAPTER;
	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

अटल अंतरभूत u16 hpi_stream_start(u32 h_stream)
अणु
	अगर (hpi_handle_object(h_stream) ==  HPI_OBJ_OSTREAM)
		वापस hpi_outstream_start(h_stream);
	अन्यथा
		वापस hpi_instream_start(h_stream);
पूर्ण

अटल अंतरभूत u16 hpi_stream_stop(u32 h_stream)
अणु
	अगर (hpi_handle_object(h_stream) ==  HPI_OBJ_OSTREAM)
		वापस hpi_outstream_stop(h_stream);
	अन्यथा
		वापस hpi_instream_stop(h_stream);
पूर्ण

अटल अंतरभूत u16 hpi_stream_get_info_ex(
    u32 h_stream,
    u16        *pw_state,
    u32        *pbuffer_size,
    u32        *pdata_in_buffer,
    u32        *psample_count,
    u32        *pauxiliary_data
)
अणु
	u16 e;
	अगर (hpi_handle_object(h_stream)  ==  HPI_OBJ_OSTREAM)
		e = hpi_outstream_get_info_ex(h_stream, pw_state,
					pbuffer_size, pdata_in_buffer,
					psample_count, pauxiliary_data);
	अन्यथा
		e = hpi_instream_get_info_ex(h_stream, pw_state,
					pbuffer_size, pdata_in_buffer,
					psample_count, pauxiliary_data);
	वापस e;
पूर्ण

अटल अंतरभूत u16 hpi_stream_group_add(
					u32 h_master,
					u32 h_stream)
अणु
	अगर (hpi_handle_object(h_master) ==  HPI_OBJ_OSTREAM)
		वापस hpi_outstream_group_add(h_master, h_stream);
	अन्यथा
		वापस hpi_instream_group_add(h_master, h_stream);
पूर्ण

अटल अंतरभूत u16 hpi_stream_group_reset(u32 h_stream)
अणु
	अगर (hpi_handle_object(h_stream) ==  HPI_OBJ_OSTREAM)
		वापस hpi_outstream_group_reset(h_stream);
	अन्यथा
		वापस hpi_instream_group_reset(h_stream);
पूर्ण

अटल u16 handle_error(u16 err, पूर्णांक line, अक्षर *filename)
अणु
	अगर (err)
		prपूर्णांकk(KERN_WARNING
			"in file %s, line %d: HPI error %d\n",
			filename, line, err);
	वापस err;
पूर्ण

#घोषणा hpi_handle_error(x)  handle_error(x, __LINE__, __खाता__)

/***************************** GENERAL PCM ****************/

अटल व्योम prपूर्णांक_hwparams(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *p)
अणु
	अक्षर name[16];
	snd_pcm_debug_name(substream, name, माप(name));
	snd_prपूर्णांकdd("%s HWPARAMS\n", name);
	snd_prपूर्णांकdd(" samplerate=%dHz channels=%d format=%d subformat=%d\n",
		params_rate(p), params_channels(p),
		params_क्रमmat(p), params_subक्रमmat(p));
	snd_prपूर्णांकdd(" buffer=%dB period=%dB period_size=%dB periods=%d\n",
		params_buffer_bytes(p), params_period_bytes(p),
		params_period_size(p), params_periods(p));
	snd_prपूर्णांकdd(" buffer_size=%d access=%d data_rate=%dB/s\n",
		params_buffer_size(p), params_access(p),
		params_rate(p) * params_channels(p) *
		snd_pcm_क्रमmat_width(params_क्रमmat(p)) / 8);
पूर्ण

#घोषणा INVALID_FORMAT	(__क्रमce snd_pcm_क्रमmat_t)(-1)

अटल स्थिर snd_pcm_क्रमmat_t hpi_to_alsa_क्रमmats[] = अणु
	INVALID_FORMAT,		/* INVALID */
	SNDRV_PCM_FORMAT_U8,	/* HPI_FORMAT_PCM8_UNSIGNED        1 */
	SNDRV_PCM_FORMAT_S16,	/* HPI_FORMAT_PCM16_SIGNED         2 */
	INVALID_FORMAT,		/* HPI_FORMAT_MPEG_L1              3 */
	SNDRV_PCM_FORMAT_MPEG,	/* HPI_FORMAT_MPEG_L2              4 */
	SNDRV_PCM_FORMAT_MPEG,	/* HPI_FORMAT_MPEG_L3              5 */
	INVALID_FORMAT,		/* HPI_FORMAT_DOLBY_AC2            6 */
	INVALID_FORMAT,		/* HPI_FORMAT_DOLBY_AC3            7 */
	SNDRV_PCM_FORMAT_S16_BE,/* HPI_FORMAT_PCM16_BIGENDIAN      8 */
	INVALID_FORMAT,		/* HPI_FORMAT_AA_TAGIT1_HITS       9 */
	INVALID_FORMAT,		/* HPI_FORMAT_AA_TAGIT1_INSERTS   10 */
	SNDRV_PCM_FORMAT_S32,	/* HPI_FORMAT_PCM32_SIGNED        11 */
	INVALID_FORMAT,		/* HPI_FORMAT_RAW_BITSTREAM       12 */
	INVALID_FORMAT,		/* HPI_FORMAT_AA_TAGIT1_HITS_EX1  13 */
	SNDRV_PCM_FORMAT_FLOAT,	/* HPI_FORMAT_PCM32_FLOAT         14 */
#अगर 1
	/* ALSA can't handle 3 byte sample size together with घातer-of-2
	 *  स्थिरraपूर्णांक on buffer_bytes, so disable this क्रमmat
	 */
	INVALID_FORMAT
#अन्यथा
	/* SNDRV_PCM_FORMAT_S24_3LE */ /* HPI_FORMAT_PCM24_SIGNED 15 */
#पूर्ण_अगर
पूर्ण;


अटल पूर्णांक snd_card_asihpi_क्रमmat_alsa2hpi(snd_pcm_क्रमmat_t alsa_क्रमmat,
					   u16 *hpi_क्रमmat)
अणु
	u16 क्रमmat;

	क्रम (क्रमmat = HPI_FORMAT_PCM8_UNSIGNED;
	     क्रमmat <= HPI_FORMAT_PCM24_SIGNED; क्रमmat++) अणु
		अगर (hpi_to_alsa_क्रमmats[क्रमmat] == alsa_क्रमmat) अणु
			*hpi_क्रमmat = क्रमmat;
			वापस 0;
		पूर्ण
	पूर्ण

	snd_prपूर्णांकd(KERN_WARNING "failed match for alsa format %d\n",
		   alsa_क्रमmat);
	*hpi_क्रमmat = 0;
	वापस -EINVAL;
पूर्ण

अटल व्योम snd_card_asihpi_pcm_samplerates(काष्ठा snd_card_asihpi *asihpi,
					 काष्ठा snd_pcm_hardware *pcmhw)
अणु
	u16 err;
	u32 h_control;
	u32 sample_rate;
	पूर्णांक idx;
	अचिन्हित पूर्णांक rate_min = 200000;
	अचिन्हित पूर्णांक rate_max = 0;
	अचिन्हित पूर्णांक rates = 0;

	अगर (asihpi->support_mrx) अणु
		rates |= SNDRV_PCM_RATE_CONTINUOUS;
		rates |= SNDRV_PCM_RATE_8000_96000;
		rate_min = 8000;
		rate_max = 100000;
	पूर्ण अन्यथा अणु
		/* on cards without SRC,
		   valid rates are determined by sampleघड़ी */
		err = hpi_mixer_get_control(asihpi->h_mixer,
					  HPI_SOURCENODE_CLOCK_SOURCE, 0, 0, 0,
					  HPI_CONTROL_SAMPLECLOCK, &h_control);
		अगर (err) अणु
			dev_err(&asihpi->pci->dev,
				"No local sampleclock, err %d\n", err);
		पूर्ण

		क्रम (idx = -1; idx < 100; idx++) अणु
			अगर (idx == -1) अणु
				अगर (hpi_sample_घड़ी_get_sample_rate(h_control,
								&sample_rate))
					जारी;
			पूर्ण अन्यथा अगर (hpi_sample_घड़ी_query_local_rate(h_control,
							idx, &sample_rate)) अणु
				अवरोध;
			पूर्ण

			rate_min = min(rate_min, sample_rate);
			rate_max = max(rate_max, sample_rate);

			चयन (sample_rate) अणु
			हाल 5512:
				rates |= SNDRV_PCM_RATE_5512;
				अवरोध;
			हाल 8000:
				rates |= SNDRV_PCM_RATE_8000;
				अवरोध;
			हाल 11025:
				rates |= SNDRV_PCM_RATE_11025;
				अवरोध;
			हाल 16000:
				rates |= SNDRV_PCM_RATE_16000;
				अवरोध;
			हाल 22050:
				rates |= SNDRV_PCM_RATE_22050;
				अवरोध;
			हाल 32000:
				rates |= SNDRV_PCM_RATE_32000;
				अवरोध;
			हाल 44100:
				rates |= SNDRV_PCM_RATE_44100;
				अवरोध;
			हाल 48000:
				rates |= SNDRV_PCM_RATE_48000;
				अवरोध;
			हाल 64000:
				rates |= SNDRV_PCM_RATE_64000;
				अवरोध;
			हाल 88200:
				rates |= SNDRV_PCM_RATE_88200;
				अवरोध;
			हाल 96000:
				rates |= SNDRV_PCM_RATE_96000;
				अवरोध;
			हाल 176400:
				rates |= SNDRV_PCM_RATE_176400;
				अवरोध;
			हाल 192000:
				rates |= SNDRV_PCM_RATE_192000;
				अवरोध;
			शेष: /* some other rate */
				rates |= SNDRV_PCM_RATE_KNOT;
			पूर्ण
		पूर्ण
	पूर्ण

	pcmhw->rates = rates;
	pcmhw->rate_min = rate_min;
	pcmhw->rate_max = rate_max;
पूर्ण

अटल पूर्णांक snd_card_asihpi_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
					 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_card_asihpi_pcm *dpcm = runसमय->निजी_data;
	काष्ठा snd_card_asihpi *card = snd_pcm_substream_chip(substream);
	पूर्णांक err;
	u16 क्रमmat;
	पूर्णांक width;
	अचिन्हित पूर्णांक bytes_per_sec;

	prपूर्णांक_hwparams(substream, params);
	err = snd_card_asihpi_क्रमmat_alsa2hpi(params_क्रमmat(params), &क्रमmat);
	अगर (err)
		वापस err;

	hpi_handle_error(hpi_क्रमmat_create(&dpcm->क्रमmat,
			params_channels(params),
			क्रमmat, params_rate(params), 0, 0));

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		अगर (hpi_instream_reset(dpcm->h_stream) != 0)
			वापस -EINVAL;

		अगर (hpi_instream_set_क्रमmat(
			dpcm->h_stream, &dpcm->क्रमmat) != 0)
			वापस -EINVAL;
	पूर्ण

	dpcm->hpi_buffer_attached = 0;
	अगर (card->can_dma) अणु
		err = hpi_stream_host_buffer_attach(dpcm->h_stream,
			params_buffer_bytes(params),  runसमय->dma_addr);
		अगर (err == 0) अणु
			snd_prपूर्णांकdd(
				"stream_host_buffer_attach success %u %lu\n",
				params_buffer_bytes(params),
				(अचिन्हित दीर्घ)runसमय->dma_addr);
		पूर्ण अन्यथा अणु
			snd_prपूर्णांकd("stream_host_buffer_attach error %d\n",
					err);
			वापस -ENOMEM;
		पूर्ण

		err = hpi_stream_get_info_ex(dpcm->h_stream, शून्य,
				&dpcm->hpi_buffer_attached, शून्य, शून्य, शून्य);
	पूर्ण
	bytes_per_sec = params_rate(params) * params_channels(params);
	width = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	bytes_per_sec *= width;
	bytes_per_sec /= 8;
	अगर (width < 0 || bytes_per_sec == 0)
		वापस -EINVAL;

	dpcm->bytes_per_sec = bytes_per_sec;
	dpcm->buffer_bytes = params_buffer_bytes(params);
	dpcm->period_bytes = params_period_bytes(params);

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_card_asihpi_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_card_asihpi_pcm *dpcm = runसमय->निजी_data;
	अगर (dpcm->hpi_buffer_attached)
		hpi_stream_host_buffer_detach(dpcm->h_stream);

	वापस 0;
पूर्ण

अटल व्योम snd_card_asihpi_runसमय_मुक्त(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	काष्ठा snd_card_asihpi_pcm *dpcm = runसमय->निजी_data;
	kमुक्त(dpcm);
पूर्ण

अटल व्योम snd_card_asihpi_pcm_समयr_start(काष्ठा snd_pcm_substream *
					    substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_card_asihpi_pcm *dpcm = runसमय->निजी_data;
	पूर्णांक expiry;

	expiry = HZ / 200;

	expiry = max(expiry, 1); /* करोn't let it be zero! */
	mod_समयr(&dpcm->समयr, jअगरfies + expiry);
	dpcm->respawn_समयr = 1;
पूर्ण

अटल व्योम snd_card_asihpi_pcm_समयr_stop(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_card_asihpi_pcm *dpcm = runसमय->निजी_data;

	dpcm->respawn_समयr = 0;
	del_समयr(&dpcm->समयr);
पूर्ण

अटल व्योम snd_card_asihpi_pcm_पूर्णांक_start(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_card_asihpi_pcm *dpcm;
	काष्ठा snd_card_asihpi *card;

	dpcm = (काष्ठा snd_card_asihpi_pcm *)substream->runसमय->निजी_data;
	card = snd_pcm_substream_chip(substream);

	WARN_ON(in_पूर्णांकerrupt());
	card->llmode_streampriv = dpcm;

	hpi_handle_error(hpi_adapter_set_property(card->hpi->adapter->index,
		HPI_ADAPTER_PROPERTY_IRQ_RATE,
		card->update_पूर्णांकerval_frames, 0));
पूर्ण

अटल व्योम snd_card_asihpi_pcm_पूर्णांक_stop(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_card_asihpi *card;

	card = snd_pcm_substream_chip(substream);

	hpi_handle_error(hpi_adapter_set_property(card->hpi->adapter->index,
		HPI_ADAPTER_PROPERTY_IRQ_RATE, 0, 0));

	card->llmode_streampriv = शून्य;
पूर्ण

अटल पूर्णांक snd_card_asihpi_trigger(काष्ठा snd_pcm_substream *substream,
					   पूर्णांक cmd)
अणु
	काष्ठा snd_card_asihpi_pcm *dpcm = substream->runसमय->निजी_data;
	काष्ठा snd_card_asihpi *card = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_substream *s;
	u16 e;
	अक्षर name[16];

	snd_pcm_debug_name(substream, name, माप(name));

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		snd_prपूर्णांकdd("%s trigger start\n", name);
		snd_pcm_group_क्रम_each_entry(s, substream) अणु
			काष्ठा snd_pcm_runसमय *runसमय = s->runसमय;
			काष्ठा snd_card_asihpi_pcm *ds = runसमय->निजी_data;

			अगर (snd_pcm_substream_chip(s) != card)
				जारी;

			/* करोn't link Cap and Play */
			अगर (substream->stream != s->stream)
				जारी;

			ds->drained_count = 0;
			अगर (s->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
				/* How करो I know how much valid data is present
				* in buffer? Must be at least one period!
				* Guessing 2 periods, but अगर
				* buffer is bigger it may contain even more
				* data??
				*/
				अचिन्हित पूर्णांक preload = ds->period_bytes * 1;
				snd_prपूर्णांकddd("%d preload %d\n", s->number, preload);
				hpi_handle_error(hpi_outstream_ग_लिखो_buf(
						ds->h_stream,
						&runसमय->dma_area[0],
						preload,
						&ds->क्रमmat));
				ds->pcm_buf_host_rw_ofs = preload;
			पूर्ण

			अगर (card->support_grouping) अणु
				snd_prपूर्णांकdd("%d group\n", s->number);
				e = hpi_stream_group_add(
					dpcm->h_stream,
					ds->h_stream);
				अगर (!e) अणु
					snd_pcm_trigger_करोne(s, substream);
				पूर्ण अन्यथा अणु
					hpi_handle_error(e);
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा
				अवरोध;
		पूर्ण
		/* start the master stream */
		card->pcm_start(substream);
		अगर ((substream->stream == SNDRV_PCM_STREAM_CAPTURE) ||
			!card->can_dma)
			hpi_handle_error(hpi_stream_start(dpcm->h_stream));
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
		snd_prपूर्णांकdd("%s trigger stop\n", name);
		card->pcm_stop(substream);
		snd_pcm_group_क्रम_each_entry(s, substream) अणु
			अगर (snd_pcm_substream_chip(s) != card)
				जारी;
			/* करोn't link Cap and Play */
			अगर (substream->stream != s->stream)
				जारी;

			/*? workaround linked streams करोn't
			transition to SETUP 20070706*/
			s->runसमय->status->state = SNDRV_PCM_STATE_SETUP;

			अगर (card->support_grouping) अणु
				snd_prपूर्णांकdd("%d group\n", s->number);
				snd_pcm_trigger_करोne(s, substream);
			पूर्ण अन्यथा
				अवरोध;
		पूर्ण

		/* _prepare and _hwparams reset the stream */
		hpi_handle_error(hpi_stream_stop(dpcm->h_stream));
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			hpi_handle_error(
				hpi_outstream_reset(dpcm->h_stream));

		अगर (card->support_grouping)
			hpi_handle_error(hpi_stream_group_reset(dpcm->h_stream));
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		snd_prपूर्णांकdd("%s trigger pause release\n", name);
		card->pcm_start(substream);
		hpi_handle_error(hpi_stream_start(dpcm->h_stream));
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		snd_prपूर्णांकdd("%s trigger pause push\n", name);
		card->pcm_stop(substream);
		hpi_handle_error(hpi_stream_stop(dpcm->h_stream));
		अवरोध;
	शेष:
		snd_prपूर्णांकd(KERN_ERR "\tINVALID\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*algorithm outline
 Without linking degenerates to getting single stream pos etc
 Without mmap 2nd loop degenerates to snd_pcm_period_elapsed
*/
/*
pcm_buf_dma_ofs=get_buf_pos(s);
क्रम_each_linked_stream(s) अणु
	pcm_buf_dma_ofs=get_buf_pos(s);
	min_buf_pos = modulo_min(min_buf_pos, pcm_buf_dma_ofs, buffer_bytes)
	new_data = min(new_data, calc_new_data(pcm_buf_dma_ofs,irq_pos)
पूर्ण
समयr.expires = jअगरfies + predict_next_period_पढ़ोy(min_buf_pos);
क्रम_each_linked_stream(s) अणु
	s->pcm_buf_dma_ofs = min_buf_pos;
	अगर (new_data > period_bytes) अणु
		अगर (mmap) अणु
			irq_pos = (irq_pos + period_bytes) % buffer_bytes;
			अगर (playback) अणु
				ग_लिखो(period_bytes);
			पूर्ण अन्यथा अणु
				पढ़ो(period_bytes);
			पूर्ण
		पूर्ण
		snd_pcm_period_elapsed(s);
	पूर्ण
पूर्ण
*/

/** Minimum of 2 modulo values.  Works correctly when the dअगरference between
* the values is less than half the modulus
*/
अटल अंतरभूत अचिन्हित पूर्णांक modulo_min(अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b,
					अचिन्हित दीर्घ पूर्णांक modulus)
अणु
	अचिन्हित पूर्णांक result;
	अगर (((a-b) % modulus) < (modulus/2))
		result = b;
	अन्यथा
		result = a;

	वापस result;
पूर्ण

/** Timer function, equivalent to पूर्णांकerrupt service routine क्रम cards
*/
अटल व्योम snd_card_asihpi_समयr_function(काष्ठा समयr_list *t)
अणु
	काष्ठा snd_card_asihpi_pcm *dpcm = from_समयr(dpcm, t, समयr);
	काष्ठा snd_pcm_substream *substream = dpcm->substream;
	काष्ठा snd_card_asihpi *card = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा snd_pcm_substream *s;
	अचिन्हित पूर्णांक newdata = 0;
	अचिन्हित पूर्णांक pcm_buf_dma_ofs, min_buf_pos = 0;
	अचिन्हित पूर्णांक remdata, xfercount, next_jअगरfies;
	पूर्णांक first = 1;
	पूर्णांक loops = 0;
	u16 state;
	u32 buffer_size, bytes_avail, samples_played, on_card_bytes;
	अक्षर name[16];


	snd_pcm_debug_name(substream, name, माप(name));

	/* find minimum newdata and buffer pos in group */
	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		काष्ठा snd_card_asihpi_pcm *ds = s->runसमय->निजी_data;
		runसमय = s->runसमय;

		अगर (snd_pcm_substream_chip(s) != card)
			जारी;

		/* करोn't link Cap and Play */
		अगर (substream->stream != s->stream)
			जारी;

		hpi_handle_error(hpi_stream_get_info_ex(
					ds->h_stream, &state,
					&buffer_size, &bytes_avail,
					&samples_played, &on_card_bytes));

		/* number of bytes in on-card buffer */
		runसमय->delay = on_card_bytes;

		अगर (!card->can_dma)
			on_card_bytes = bytes_avail;

		अगर (s->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			pcm_buf_dma_ofs = ds->pcm_buf_host_rw_ofs - bytes_avail;
			अगर (state == HPI_STATE_STOPPED) अणु
				अगर (bytes_avail == 0) अणु
					hpi_handle_error(hpi_stream_start(ds->h_stream));
					snd_prपूर्णांकdd("P%d start\n", s->number);
					ds->drained_count = 0;
				पूर्ण
			पूर्ण अन्यथा अगर (state == HPI_STATE_DRAINED) अणु
				snd_prपूर्णांकd(KERN_WARNING "P%d drained\n",
						s->number);
				ds->drained_count++;
				अगर (ds->drained_count > 20) अणु
					snd_pcm_stop_xrun(s);
					जारी;
				पूर्ण
			पूर्ण अन्यथा अणु
				ds->drained_count = 0;
			पूर्ण
		पूर्ण अन्यथा
			pcm_buf_dma_ofs = bytes_avail + ds->pcm_buf_host_rw_ofs;

		अगर (first) अणु
			/* can't अटलally init min when wrap is involved */
			min_buf_pos = pcm_buf_dma_ofs;
			newdata = (pcm_buf_dma_ofs - ds->pcm_buf_elapsed_dma_ofs) % ds->buffer_bytes;
			first = 0;
		पूर्ण अन्यथा अणु
			min_buf_pos =
				modulo_min(min_buf_pos, pcm_buf_dma_ofs, अच_पूर्णांक_उच्च+1L);
			newdata = min(
				(pcm_buf_dma_ofs - ds->pcm_buf_elapsed_dma_ofs) % ds->buffer_bytes,
				newdata);
		पूर्ण

		snd_prपूर्णांकddd(
			"timer1, %s, %d, S=%d, elap=%d, rw=%d, dsp=%d, left=%d, aux=%d, space=%d, hw_ptr=%ld, appl_ptr=%ld\n",
			name, s->number, state,
			ds->pcm_buf_elapsed_dma_ofs,
			ds->pcm_buf_host_rw_ofs,
			pcm_buf_dma_ofs,
			(पूर्णांक)bytes_avail,

			(पूर्णांक)on_card_bytes,
			buffer_size-bytes_avail,
			(अचिन्हित दीर्घ)frames_to_bytes(runसमय,
						runसमय->status->hw_ptr),
			(अचिन्हित दीर्घ)frames_to_bytes(runसमय,
						runसमय->control->appl_ptr)
		);
		loops++;
	पूर्ण
	pcm_buf_dma_ofs = min_buf_pos;

	remdata = newdata % dpcm->period_bytes;
	xfercount = newdata - remdata; /* a multiple of period_bytes */
	/* come back when on_card_bytes has decreased enough to allow
	   ग_लिखो to happen, or when data has been consumed to make another
	   period
	*/
	अगर (xfercount && (on_card_bytes  > dpcm->period_bytes))
		next_jअगरfies = ((on_card_bytes - dpcm->period_bytes) * HZ / dpcm->bytes_per_sec);
	अन्यथा
		next_jअगरfies = ((dpcm->period_bytes - remdata) * HZ / dpcm->bytes_per_sec);

	next_jअगरfies = max(next_jअगरfies, 1U);
	dpcm->समयr.expires = jअगरfies + next_jअगरfies;
	snd_prपूर्णांकddd("timer2, jif=%d, buf_pos=%d, newdata=%d, xfer=%d\n",
			next_jअगरfies, pcm_buf_dma_ofs, newdata, xfercount);

	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		काष्ठा snd_card_asihpi_pcm *ds = s->runसमय->निजी_data;

		/* करोn't link Cap and Play */
		अगर (substream->stream != s->stream)
			जारी;

		/* Store dma offset क्रम use by poपूर्णांकer callback */
		ds->pcm_buf_dma_ofs = pcm_buf_dma_ofs;

		अगर (xfercount &&
			/* Limit use of on card fअगरo क्रम playback */
			((on_card_bytes <= ds->period_bytes) ||
			(s->stream == SNDRV_PCM_STREAM_CAPTURE)))

		अणु

			अचिन्हित पूर्णांक buf_ofs = ds->pcm_buf_host_rw_ofs % ds->buffer_bytes;
			अचिन्हित पूर्णांक xfer1, xfer2;
			अक्षर *pd = &s->runसमय->dma_area[buf_ofs];

			अगर (card->can_dma) अणु /* buffer wrap is handled at lower level */
				xfer1 = xfercount;
				xfer2 = 0;
			पूर्ण अन्यथा अणु
				xfer1 = min(xfercount, ds->buffer_bytes - buf_ofs);
				xfer2 = xfercount - xfer1;
			पूर्ण

			अगर (s->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
				snd_prपूर्णांकddd("write1, P=%d, xfer=%d, buf_ofs=%d\n",
					s->number, xfer1, buf_ofs);
				hpi_handle_error(
					hpi_outstream_ग_लिखो_buf(
						ds->h_stream, pd, xfer1,
						&ds->क्रमmat));

				अगर (xfer2) अणु
					pd = s->runसमय->dma_area;

					snd_prपूर्णांकddd("write2, P=%d, xfer=%d, buf_ofs=%d\n",
							s->number,
							xfercount - xfer1, buf_ofs);
					hpi_handle_error(
						hpi_outstream_ग_लिखो_buf(
							ds->h_stream, pd,
							xfercount - xfer1,
							&ds->क्रमmat));
				पूर्ण
			पूर्ण अन्यथा अणु
				snd_prपूर्णांकddd("read1, C=%d, xfer=%d\n",
					s->number, xfer1);
				hpi_handle_error(
					hpi_instream_पढ़ो_buf(
						ds->h_stream,
						pd, xfer1));
				अगर (xfer2) अणु
					pd = s->runसमय->dma_area;
					snd_prपूर्णांकddd("read2, C=%d, xfer=%d\n",
						s->number, xfer2);
					hpi_handle_error(
						hpi_instream_पढ़ो_buf(
							ds->h_stream,
							pd, xfer2));
				पूर्ण
			पूर्ण
			/* ? host_rw_ofs always ahead of elapsed_dma_ofs by preload size? */
			ds->pcm_buf_host_rw_ofs += xfercount;
			ds->pcm_buf_elapsed_dma_ofs += xfercount;
			snd_pcm_period_elapsed(s);
		पूर्ण
	पूर्ण

	अगर (!card->hpi->पूर्णांकerrupt_mode && dpcm->respawn_समयr)
		add_समयr(&dpcm->समयr);
पूर्ण

अटल व्योम snd_card_asihpi_isr(काष्ठा hpi_adapter *a)
अणु
	काष्ठा snd_card_asihpi *asihpi;

	WARN_ON(!a || !a->snd_card || !a->snd_card->निजी_data);
	asihpi = (काष्ठा snd_card_asihpi *)a->snd_card->निजी_data;
	अगर (asihpi->llmode_streampriv)
		snd_card_asihpi_समयr_function(
			&asihpi->llmode_streampriv->समयr);
पूर्ण

/***************************** PLAYBACK OPS ****************/
अटल पूर्णांक snd_card_asihpi_playback_prepare(काष्ठा snd_pcm_substream *
					    substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_card_asihpi_pcm *dpcm = runसमय->निजी_data;

	snd_prपूर्णांकdd("P%d prepare\n", substream->number);

	hpi_handle_error(hpi_outstream_reset(dpcm->h_stream));
	dpcm->pcm_buf_host_rw_ofs = 0;
	dpcm->pcm_buf_dma_ofs = 0;
	dpcm->pcm_buf_elapsed_dma_ofs = 0;
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t
snd_card_asihpi_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_card_asihpi_pcm *dpcm = runसमय->निजी_data;
	snd_pcm_uframes_t ptr;
	अक्षर name[16];
	snd_pcm_debug_name(substream, name, माप(name));

	ptr = bytes_to_frames(runसमय, dpcm->pcm_buf_dma_ofs  % dpcm->buffer_bytes);
	snd_prपूर्णांकddd("%s, pointer=%ld\n", name, (अचिन्हित दीर्घ)ptr);
	वापस ptr;
पूर्ण

अटल u64 snd_card_asihpi_playback_क्रमmats(काष्ठा snd_card_asihpi *asihpi,
						u32 h_stream)
अणु
	काष्ठा hpi_क्रमmat hpi_क्रमmat;
	u16 क्रमmat;
	u16 err;
	u32 h_control;
	u32 sample_rate = 48000;
	u64 क्रमmats = 0;

	/* on cards without SRC, must query at valid rate,
	* maybe set by बाह्यal sync
	*/
	err = hpi_mixer_get_control(asihpi->h_mixer,
				  HPI_SOURCENODE_CLOCK_SOURCE, 0, 0, 0,
				  HPI_CONTROL_SAMPLECLOCK, &h_control);

	अगर (!err)
		err = hpi_sample_घड़ी_get_sample_rate(h_control,
				&sample_rate);

	क्रम (क्रमmat = HPI_FORMAT_PCM8_UNSIGNED;
	     क्रमmat <= HPI_FORMAT_PCM24_SIGNED; क्रमmat++) अणु
		err = hpi_क्रमmat_create(&hpi_क्रमmat, asihpi->out_max_chans,
					क्रमmat, sample_rate, 128000, 0);
		अगर (!err)
			err = hpi_outstream_query_क्रमmat(h_stream, &hpi_क्रमmat);
		अगर (!err && (hpi_to_alsa_क्रमmats[क्रमmat] != INVALID_FORMAT))
			क्रमmats |= pcm_क्रमmat_to_bits(hpi_to_alsa_क्रमmats[क्रमmat]);
	पूर्ण
	वापस क्रमmats;
पूर्ण

अटल पूर्णांक snd_card_asihpi_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_card_asihpi_pcm *dpcm;
	काष्ठा snd_card_asihpi *card = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_hardware snd_card_asihpi_playback;
	पूर्णांक err;

	dpcm = kzalloc(माप(*dpcm), GFP_KERNEL);
	अगर (dpcm == शून्य)
		वापस -ENOMEM;

	err = hpi_outstream_खोलो(card->hpi->adapter->index,
			      substream->number, &dpcm->h_stream);
	hpi_handle_error(err);
	अगर (err)
		kमुक्त(dpcm);
	अगर (err == HPI_ERROR_OBJ_ALREADY_OPEN)
		वापस -EBUSY;
	अगर (err)
		वापस -EIO;

	/*? also check ASI5000 samplerate source
	    If बाह्यal, only support बाह्यal rate.
	    If पूर्णांकernal and other stream playing, can't चयन
	*/

	समयr_setup(&dpcm->समयr, snd_card_asihpi_समयr_function, 0);
	dpcm->substream = substream;
	runसमय->निजी_data = dpcm;
	runसमय->निजी_मुक्त = snd_card_asihpi_runसमय_मुक्त;

	स_रखो(&snd_card_asihpi_playback, 0, माप(snd_card_asihpi_playback));
	अगर (!card->hpi->पूर्णांकerrupt_mode) अणु
		snd_card_asihpi_playback.buffer_bytes_max = BUFFER_BYTES_MAX;
		snd_card_asihpi_playback.period_bytes_min = PERIOD_BYTES_MIN;
		snd_card_asihpi_playback.period_bytes_max = BUFFER_BYTES_MAX / PERIODS_MIN;
		snd_card_asihpi_playback.periods_min = PERIODS_MIN;
		snd_card_asihpi_playback.periods_max = BUFFER_BYTES_MAX / PERIOD_BYTES_MIN;
	पूर्ण अन्यथा अणु
		माप_प्रकार pbmin = card->update_पूर्णांकerval_frames *
			card->out_max_chans;
		snd_card_asihpi_playback.buffer_bytes_max = BUFFER_BYTES_MAX;
		snd_card_asihpi_playback.period_bytes_min = pbmin;
		snd_card_asihpi_playback.period_bytes_max = BUFFER_BYTES_MAX / PERIODS_MIN;
		snd_card_asihpi_playback.periods_min = PERIODS_MIN;
		snd_card_asihpi_playback.periods_max = BUFFER_BYTES_MAX / pbmin;
	पूर्ण

	/* snd_card_asihpi_playback.fअगरo_size = 0; */
	snd_card_asihpi_playback.channels_max = card->out_max_chans;
	snd_card_asihpi_playback.channels_min = card->out_min_chans;
	snd_card_asihpi_playback.क्रमmats =
			snd_card_asihpi_playback_क्रमmats(card, dpcm->h_stream);

	snd_card_asihpi_pcm_samplerates(card,  &snd_card_asihpi_playback);

	snd_card_asihpi_playback.info = SNDRV_PCM_INFO_INTERLEAVED |
					SNDRV_PCM_INFO_DOUBLE |
					SNDRV_PCM_INFO_BATCH |
					SNDRV_PCM_INFO_BLOCK_TRANSFER |
					SNDRV_PCM_INFO_PAUSE |
					SNDRV_PCM_INFO_MMAP |
					SNDRV_PCM_INFO_MMAP_VALID;

	अगर (card->support_grouping) अणु
		snd_card_asihpi_playback.info |= SNDRV_PCM_INFO_SYNC_START;
		snd_pcm_set_sync(substream);
	पूर्ण

	/* काष्ठा is copied, so can create initializer dynamically */
	runसमय->hw = snd_card_asihpi_playback;

	अगर (card->can_dma)
		err = snd_pcm_hw_स्थिरraपूर्णांक_घात2(runसमय, 0,
					SNDRV_PCM_HW_PARAM_BUFFER_BYTES);
	अगर (err < 0)
		वापस err;

	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
		card->update_पूर्णांकerval_frames);

	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
		card->update_पूर्णांकerval_frames, अच_पूर्णांक_उच्च);

	snd_prपूर्णांकdd("playback open\n");

	वापस 0;
पूर्ण

अटल पूर्णांक snd_card_asihpi_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_card_asihpi_pcm *dpcm = runसमय->निजी_data;

	hpi_handle_error(hpi_outstream_बंद(dpcm->h_stream));
	snd_prपूर्णांकdd("playback close\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_card_asihpi_playback_mmap_ops = अणु
	.खोलो = snd_card_asihpi_playback_खोलो,
	.बंद = snd_card_asihpi_playback_बंद,
	.hw_params = snd_card_asihpi_pcm_hw_params,
	.hw_मुक्त = snd_card_asihpi_hw_मुक्त,
	.prepare = snd_card_asihpi_playback_prepare,
	.trigger = snd_card_asihpi_trigger,
	.poपूर्णांकer = snd_card_asihpi_playback_poपूर्णांकer,
पूर्ण;

/***************************** CAPTURE OPS ****************/
अटल snd_pcm_uframes_t
snd_card_asihpi_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_card_asihpi_pcm *dpcm = runसमय->निजी_data;
	अक्षर name[16];
	snd_pcm_debug_name(substream, name, माप(name));

	snd_prपूर्णांकddd("%s, pointer=%d\n", name, dpcm->pcm_buf_dma_ofs);
	/* NOTE Unlike playback can't use actual samples_played
		क्रम the capture position, because those samples aren't yet in
		the local buffer available क्रम पढ़ोing.
	*/
	वापस bytes_to_frames(runसमय, dpcm->pcm_buf_dma_ofs % dpcm->buffer_bytes);
पूर्ण

अटल पूर्णांक snd_card_asihpi_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_card_asihpi_pcm *dpcm = runसमय->निजी_data;

	hpi_handle_error(hpi_instream_reset(dpcm->h_stream));
	dpcm->pcm_buf_host_rw_ofs = 0;
	dpcm->pcm_buf_dma_ofs = 0;
	dpcm->pcm_buf_elapsed_dma_ofs = 0;

	snd_prपूर्णांकdd("Capture Prepare %d\n", substream->number);
	वापस 0;
पूर्ण

अटल u64 snd_card_asihpi_capture_क्रमmats(काष्ठा snd_card_asihpi *asihpi,
					u32 h_stream)
अणु
	काष्ठा hpi_क्रमmat hpi_क्रमmat;
	u16 क्रमmat;
	u16 err;
	u32 h_control;
	u32 sample_rate = 48000;
	u64 क्रमmats = 0;

	/* on cards without SRC, must query at valid rate,
		maybe set by बाह्यal sync */
	err = hpi_mixer_get_control(asihpi->h_mixer,
				  HPI_SOURCENODE_CLOCK_SOURCE, 0, 0, 0,
				  HPI_CONTROL_SAMPLECLOCK, &h_control);

	अगर (!err)
		err = hpi_sample_घड़ी_get_sample_rate(h_control,
			&sample_rate);

	क्रम (क्रमmat = HPI_FORMAT_PCM8_UNSIGNED;
		क्रमmat <= HPI_FORMAT_PCM24_SIGNED; क्रमmat++) अणु

		err = hpi_क्रमmat_create(&hpi_क्रमmat, asihpi->in_max_chans,
					क्रमmat, sample_rate, 128000, 0);
		अगर (!err)
			err = hpi_instream_query_क्रमmat(h_stream, &hpi_क्रमmat);
		अगर (!err && (hpi_to_alsa_क्रमmats[क्रमmat] != INVALID_FORMAT))
			क्रमmats |= pcm_क्रमmat_to_bits(hpi_to_alsa_क्रमmats[क्रमmat]);
	पूर्ण
	वापस क्रमmats;
पूर्ण

अटल पूर्णांक snd_card_asihpi_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_card_asihpi *card = snd_pcm_substream_chip(substream);
	काष्ठा snd_card_asihpi_pcm *dpcm;
	काष्ठा snd_pcm_hardware snd_card_asihpi_capture;
	पूर्णांक err;

	dpcm = kzalloc(माप(*dpcm), GFP_KERNEL);
	अगर (dpcm == शून्य)
		वापस -ENOMEM;

	snd_prपूर्णांकdd("capture open adapter %d stream %d\n",
			card->hpi->adapter->index, substream->number);

	err = hpi_handle_error(
	    hpi_instream_खोलो(card->hpi->adapter->index,
			     substream->number, &dpcm->h_stream));
	अगर (err)
		kमुक्त(dpcm);
	अगर (err == HPI_ERROR_OBJ_ALREADY_OPEN)
		वापस -EBUSY;
	अगर (err)
		वापस -EIO;

	समयr_setup(&dpcm->समयr, snd_card_asihpi_समयr_function, 0);
	dpcm->substream = substream;
	runसमय->निजी_data = dpcm;
	runसमय->निजी_मुक्त = snd_card_asihpi_runसमय_मुक्त;

	स_रखो(&snd_card_asihpi_capture, 0, माप(snd_card_asihpi_capture));
	अगर (!card->hpi->पूर्णांकerrupt_mode) अणु
		snd_card_asihpi_capture.buffer_bytes_max = BUFFER_BYTES_MAX;
		snd_card_asihpi_capture.period_bytes_min = PERIOD_BYTES_MIN;
		snd_card_asihpi_capture.period_bytes_max = BUFFER_BYTES_MAX / PERIODS_MIN;
		snd_card_asihpi_capture.periods_min = PERIODS_MIN;
		snd_card_asihpi_capture.periods_max = BUFFER_BYTES_MAX / PERIOD_BYTES_MIN;
	पूर्ण अन्यथा अणु
		माप_प्रकार pbmin = card->update_पूर्णांकerval_frames *
			card->out_max_chans;
		snd_card_asihpi_capture.buffer_bytes_max = BUFFER_BYTES_MAX;
		snd_card_asihpi_capture.period_bytes_min = pbmin;
		snd_card_asihpi_capture.period_bytes_max = BUFFER_BYTES_MAX / PERIODS_MIN;
		snd_card_asihpi_capture.periods_min = PERIODS_MIN;
		snd_card_asihpi_capture.periods_max = BUFFER_BYTES_MAX / pbmin;
	पूर्ण
	/* snd_card_asihpi_capture.fअगरo_size = 0; */
	snd_card_asihpi_capture.channels_max = card->in_max_chans;
	snd_card_asihpi_capture.channels_min = card->in_min_chans;
	snd_card_asihpi_capture.क्रमmats =
		snd_card_asihpi_capture_क्रमmats(card, dpcm->h_stream);
	snd_card_asihpi_pcm_samplerates(card,  &snd_card_asihpi_capture);
	snd_card_asihpi_capture.info = SNDRV_PCM_INFO_INTERLEAVED |
					SNDRV_PCM_INFO_MMAP |
					SNDRV_PCM_INFO_MMAP_VALID;

	अगर (card->support_grouping)
		snd_card_asihpi_capture.info |= SNDRV_PCM_INFO_SYNC_START;

	runसमय->hw = snd_card_asihpi_capture;

	अगर (card->can_dma)
		err = snd_pcm_hw_स्थिरraपूर्णांक_घात2(runसमय, 0,
					SNDRV_PCM_HW_PARAM_BUFFER_BYTES);
	अगर (err < 0)
		वापस err;

	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
		card->update_पूर्णांकerval_frames);
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
		card->update_पूर्णांकerval_frames, अच_पूर्णांक_उच्च);

	snd_pcm_set_sync(substream);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_card_asihpi_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_card_asihpi_pcm *dpcm = substream->runसमय->निजी_data;

	hpi_handle_error(hpi_instream_बंद(dpcm->h_stream));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_card_asihpi_capture_mmap_ops = अणु
	.खोलो = snd_card_asihpi_capture_खोलो,
	.बंद = snd_card_asihpi_capture_बंद,
	.hw_params = snd_card_asihpi_pcm_hw_params,
	.hw_मुक्त = snd_card_asihpi_hw_मुक्त,
	.prepare = snd_card_asihpi_capture_prepare,
	.trigger = snd_card_asihpi_trigger,
	.poपूर्णांकer = snd_card_asihpi_capture_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_card_asihpi_pcm_new(काष्ठा snd_card_asihpi *asihpi, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;
	u16 num_instreams, num_outstreams, x16;
	u32 x32;

	err = hpi_adapter_get_info(asihpi->hpi->adapter->index,
			&num_outstreams, &num_instreams,
			&x16, &x32, &x16);

	err = snd_pcm_new(asihpi->card, "Asihpi PCM", device,
			num_outstreams,	num_instreams, &pcm);
	अगर (err < 0)
		वापस err;

	/* poपूर्णांकer to ops काष्ठा is stored, करोnt change ops afterwards! */
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_card_asihpi_playback_mmap_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
			&snd_card_asihpi_capture_mmap_ops);

	pcm->निजी_data = asihpi;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "Asihpi PCM");

	/*? करो we want to emulate MMAP क्रम non-BBM cards?
	Jack करोesn't work with ALSAs MMAP emulation - WHY NOT? */
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &asihpi->pci->dev,
				       64*1024, BUFFER_BYTES_MAX);

	वापस 0;
पूर्ण

/***************************** MIXER CONTROLS ****************/
काष्ठा hpi_control अणु
	u32 h_control;
	u16 control_type;
	u16 src_node_type;
	u16 src_node_index;
	u16 dst_node_type;
	u16 dst_node_index;
	u16 band;
	अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN]; /* copied to snd_ctl_elem_id.name[44]; */
पूर्ण;

अटल स्थिर अक्षर * स्थिर asihpi_tuner_band_names[] = अणु
	"invalid",
	"AM",
	"FM mono",
	"TV NTSC-M",
	"FM stereo",
	"AUX",
	"TV PAL BG",
	"TV PAL I",
	"TV PAL DK",
	"TV SECAM",
	"TV DAB",
पूर्ण;
/* Number of strings must match the क्रमागतerations क्रम HPI_TUNER_BAND in hpi.h */
compile_समय_निश्चित(
	(ARRAY_SIZE(asihpi_tuner_band_names) ==
		(HPI_TUNER_BAND_LAST+1)),
	निश्चित_tuner_band_names_size);

अटल स्थिर अक्षर * स्थिर asihpi_src_names[] = अणु
	"no source",
	"PCM",
	"Line",
	"Digital",
	"Tuner",
	"RF",
	"Clock",
	"Bitstream",
	"Mic",
	"Net",
	"Analog",
	"Adapter",
	"RTP",
	"Internal",
	"AVB",
	"BLU-Link"
पूर्ण;
/* Number of strings must match the क्रमागतerations क्रम HPI_SOURCENODES in hpi.h */
compile_समय_निश्चित(
	(ARRAY_SIZE(asihpi_src_names) ==
		(HPI_SOURCENODE_LAST_INDEX-HPI_SOURCENODE_NONE+1)),
	निश्चित_src_names_size);

अटल स्थिर अक्षर * स्थिर asihpi_dst_names[] = अणु
	"no destination",
	"PCM",
	"Line",
	"Digital",
	"RF",
	"Speaker",
	"Net",
	"Analog",
	"RTP",
	"AVB",
	"Internal",
	"BLU-Link"
पूर्ण;
/* Number of strings must match the क्रमागतerations क्रम HPI_DESTNODES in hpi.h */
compile_समय_निश्चित(
	(ARRAY_SIZE(asihpi_dst_names) ==
		(HPI_DESTNODE_LAST_INDEX-HPI_DESTNODE_NONE+1)),
	निश्चित_dst_names_size);

अटल अंतरभूत पूर्णांक ctl_add(काष्ठा snd_card *card, काष्ठा snd_kcontrol_new *ctl,
				काष्ठा snd_card_asihpi *asihpi)
अणु
	पूर्णांक err;

	err = snd_ctl_add(card, snd_ctl_new1(ctl, asihpi));
	अगर (err < 0)
		वापस err;
	अन्यथा अगर (mixer_dump)
		dev_info(&asihpi->pci->dev, "added %s(%d)\n", ctl->name, ctl->index);

	वापस 0;
पूर्ण

/* Convert HPI control name and location पूर्णांकo ALSA control name */
अटल व्योम asihpi_ctl_init(काष्ठा snd_kcontrol_new *snd_control,
				काष्ठा hpi_control *hpi_ctl,
				अक्षर *name)
अणु
	अक्षर *dir;
	स_रखो(snd_control, 0, माप(*snd_control));
	snd_control->name = hpi_ctl->name;
	snd_control->निजी_value = hpi_ctl->h_control;
	snd_control->अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	snd_control->index = 0;

	अगर (hpi_ctl->src_node_type + HPI_SOURCENODE_NONE == HPI_SOURCENODE_CLOCK_SOURCE)
		dir = ""; /* घड़ी is neither capture nor playback */
	अन्यथा अगर (hpi_ctl->dst_node_type + HPI_DESTNODE_NONE == HPI_DESTNODE_ISTREAM)
		dir = "Capture ";  /* On or towards a PCM capture destination*/
	अन्यथा अगर ((hpi_ctl->src_node_type + HPI_SOURCENODE_NONE != HPI_SOURCENODE_OSTREAM) &&
		(!hpi_ctl->dst_node_type))
		dir = "Capture "; /* On a source node that is not PCM playback */
	अन्यथा अगर (hpi_ctl->src_node_type &&
		(hpi_ctl->src_node_type + HPI_SOURCENODE_NONE != HPI_SOURCENODE_OSTREAM) &&
		(hpi_ctl->dst_node_type))
		dir = "Monitor Playback "; /* Between an input and an output */
	अन्यथा
		dir = "Playback "; /* PCM Playback source, or  output node */

	अगर (hpi_ctl->src_node_type && hpi_ctl->dst_node_type)
		प्र_लिखो(hpi_ctl->name, "%s %d %s %d %s%s",
			asihpi_src_names[hpi_ctl->src_node_type],
			hpi_ctl->src_node_index,
			asihpi_dst_names[hpi_ctl->dst_node_type],
			hpi_ctl->dst_node_index,
			dir, name);
	अन्यथा अगर (hpi_ctl->dst_node_type) अणु
		प्र_लिखो(hpi_ctl->name, "%s %d %s%s",
		asihpi_dst_names[hpi_ctl->dst_node_type],
		hpi_ctl->dst_node_index,
		dir, name);
	पूर्ण अन्यथा अणु
		प्र_लिखो(hpi_ctl->name, "%s %d %s%s",
		asihpi_src_names[hpi_ctl->src_node_type],
		hpi_ctl->src_node_index,
		dir, name);
	पूर्ण
	/* prपूर्णांकk(KERN_INFO "Adding %s %d to %d ",  hpi_ctl->name,
		hpi_ctl->wSrcNodeType, hpi_ctl->wDstNodeType); */
पूर्ण

/*------------------------------------------------------------
   Volume controls
 ------------------------------------------------------------*/
#घोषणा VOL_STEP_mB 1
अटल पूर्णांक snd_asihpi_volume_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	u32 h_control = kcontrol->निजी_value;
	u32 count;
	u16 err;
	/* native gains are in millibels */
	लघु min_gain_mB;
	लघु max_gain_mB;
	लघु step_gain_mB;

	err = hpi_volume_query_range(h_control,
			&min_gain_mB, &max_gain_mB, &step_gain_mB);
	अगर (err) अणु
		max_gain_mB = 0;
		min_gain_mB = -10000;
		step_gain_mB = VOL_STEP_mB;
	पूर्ण

	err = hpi_meter_query_channels(h_control, &count);
	अगर (err)
		count = HPI_MAX_CHANNELS;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = count;
	uinfo->value.पूर्णांकeger.min = min_gain_mB / VOL_STEP_mB;
	uinfo->value.पूर्णांकeger.max = max_gain_mB / VOL_STEP_mB;
	uinfo->value.पूर्णांकeger.step = step_gain_mB / VOL_STEP_mB;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_volume_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 h_control = kcontrol->निजी_value;
	लघु an_gain_mB[HPI_MAX_CHANNELS];

	hpi_handle_error(hpi_volume_get_gain(h_control, an_gain_mB));
	ucontrol->value.पूर्णांकeger.value[0] = an_gain_mB[0] / VOL_STEP_mB;
	ucontrol->value.पूर्णांकeger.value[1] = an_gain_mB[1] / VOL_STEP_mB;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_volume_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 h_control = kcontrol->निजी_value;
	लघु an_gain_mB[HPI_MAX_CHANNELS];

	an_gain_mB[0] =
	    (ucontrol->value.पूर्णांकeger.value[0]) * VOL_STEP_mB;
	an_gain_mB[1] =
	    (ucontrol->value.पूर्णांकeger.value[1]) * VOL_STEP_mB;
	/*  change = asihpi->mixer_volume[addr][0] != left ||
	   asihpi->mixer_volume[addr][1] != right;
	 */
	hpi_handle_error(hpi_volume_set_gain(h_control, an_gain_mB));
	वापस 1;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_100, -10000, VOL_STEP_mB, 0);

#घोषणा snd_asihpi_volume_mute_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_asihpi_volume_mute_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 h_control = kcontrol->निजी_value;
	u32 mute;

	hpi_handle_error(hpi_volume_get_mute(h_control, &mute));
	ucontrol->value.पूर्णांकeger.value[0] = mute ? 0 : 1;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_volume_mute_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 h_control = kcontrol->निजी_value;
	/* HPI currently only supports all or none muting of multichannel volume
	ALSA Switch element has opposite sense to HPI mute: on==unmuted, off=muted
	*/
	पूर्णांक mute =  ucontrol->value.पूर्णांकeger.value[0] ? 0 : HPI_BITMASK_ALL_CHANNELS;
	hpi_handle_error(hpi_volume_set_mute(h_control, mute));
	वापस 1;
पूर्ण

अटल पूर्णांक snd_asihpi_volume_add(काष्ठा snd_card_asihpi *asihpi,
				 काष्ठा hpi_control *hpi_ctl)
अणु
	काष्ठा snd_card *card = asihpi->card;
	काष्ठा snd_kcontrol_new snd_control;
	पूर्णांक err;
	u32 mute;

	asihpi_ctl_init(&snd_control, hpi_ctl, "Volume");
	snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ;
	snd_control.info = snd_asihpi_volume_info;
	snd_control.get = snd_asihpi_volume_get;
	snd_control.put = snd_asihpi_volume_put;
	snd_control.tlv.p = db_scale_100;

	err = ctl_add(card, &snd_control, asihpi);
	अगर (err)
		वापस err;

	अगर (hpi_volume_get_mute(hpi_ctl->h_control, &mute) == 0) अणु
		asihpi_ctl_init(&snd_control, hpi_ctl, "Switch");
		snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
		snd_control.info = snd_asihpi_volume_mute_info;
		snd_control.get = snd_asihpi_volume_mute_get;
		snd_control.put = snd_asihpi_volume_mute_put;
		err = ctl_add(card, &snd_control, asihpi);
	पूर्ण
	वापस err;
पूर्ण

/*------------------------------------------------------------
   Level controls
 ------------------------------------------------------------*/
अटल पूर्णांक snd_asihpi_level_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	u32 h_control = kcontrol->निजी_value;
	u16 err;
	लघु min_gain_mB;
	लघु max_gain_mB;
	लघु step_gain_mB;

	err =
	    hpi_level_query_range(h_control, &min_gain_mB,
			       &max_gain_mB, &step_gain_mB);
	अगर (err) अणु
		max_gain_mB = 2400;
		min_gain_mB = -1000;
		step_gain_mB = 100;
	पूर्ण

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = min_gain_mB / HPI_UNITS_PER_dB;
	uinfo->value.पूर्णांकeger.max = max_gain_mB / HPI_UNITS_PER_dB;
	uinfo->value.पूर्णांकeger.step = step_gain_mB / HPI_UNITS_PER_dB;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_level_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 h_control = kcontrol->निजी_value;
	लघु an_gain_mB[HPI_MAX_CHANNELS];

	hpi_handle_error(hpi_level_get_gain(h_control, an_gain_mB));
	ucontrol->value.पूर्णांकeger.value[0] =
	    an_gain_mB[0] / HPI_UNITS_PER_dB;
	ucontrol->value.पूर्णांकeger.value[1] =
	    an_gain_mB[1] / HPI_UNITS_PER_dB;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_level_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक change;
	u32 h_control = kcontrol->निजी_value;
	लघु an_gain_mB[HPI_MAX_CHANNELS];

	an_gain_mB[0] =
	    (ucontrol->value.पूर्णांकeger.value[0]) * HPI_UNITS_PER_dB;
	an_gain_mB[1] =
	    (ucontrol->value.पूर्णांकeger.value[1]) * HPI_UNITS_PER_dB;
	/*  change = asihpi->mixer_level[addr][0] != left ||
	   asihpi->mixer_level[addr][1] != right;
	 */
	change = 1;
	hpi_handle_error(hpi_level_set_gain(h_control, an_gain_mB));
	वापस change;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_level, -1000, 100, 0);

अटल पूर्णांक snd_asihpi_level_add(काष्ठा snd_card_asihpi *asihpi,
				काष्ठा hpi_control *hpi_ctl)
अणु
	काष्ठा snd_card *card = asihpi->card;
	काष्ठा snd_kcontrol_new snd_control;

	/* can't use 'volume' cos some nodes have volume as well */
	asihpi_ctl_init(&snd_control, hpi_ctl, "Level");
	snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ;
	snd_control.info = snd_asihpi_level_info;
	snd_control.get = snd_asihpi_level_get;
	snd_control.put = snd_asihpi_level_put;
	snd_control.tlv.p = db_scale_level;

	वापस ctl_add(card, &snd_control, asihpi);
पूर्ण

/*------------------------------------------------------------
   AESEBU controls
 ------------------------------------------------------------*/

/* AESEBU क्रमmat */
अटल स्थिर अक्षर * स्थिर asihpi_aesebu_क्रमmat_names[] = अणु
	"N/A", "S/PDIF", "AES/EBU" पूर्ण;

अटल पूर्णांक snd_asihpi_aesebu_क्रमmat_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, asihpi_aesebu_क्रमmat_names);
पूर्ण

अटल पूर्णांक snd_asihpi_aesebu_क्रमmat_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol,
			u16 (*func)(u32, u16 *))
अणु
	u32 h_control = kcontrol->निजी_value;
	u16 source, err;

	err = func(h_control, &source);

	/* शेष to N/A */
	ucontrol->value.क्रमागतerated.item[0] = 0;
	/* वापस success but set the control to N/A */
	अगर (err)
		वापस 0;
	अगर (source == HPI_AESEBU_FORMAT_SPDIF)
		ucontrol->value.क्रमागतerated.item[0] = 1;
	अगर (source == HPI_AESEBU_FORMAT_AESEBU)
		ucontrol->value.क्रमागतerated.item[0] = 2;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_aesebu_क्रमmat_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol,
			 u16 (*func)(u32, u16))
अणु
	u32 h_control = kcontrol->निजी_value;

	/* शेष to S/PDIF */
	u16 source = HPI_AESEBU_FORMAT_SPDIF;

	अगर (ucontrol->value.क्रमागतerated.item[0] == 1)
		source = HPI_AESEBU_FORMAT_SPDIF;
	अगर (ucontrol->value.क्रमागतerated.item[0] == 2)
		source = HPI_AESEBU_FORMAT_AESEBU;

	अगर (func(h_control, source) != 0)
		वापस -EINVAL;

	वापस 1;
पूर्ण

अटल पूर्णांक snd_asihpi_aesebu_rx_क्रमmat_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol) अणु
	वापस snd_asihpi_aesebu_क्रमmat_get(kcontrol, ucontrol,
					hpi_aesebu_receiver_get_क्रमmat);
पूर्ण

अटल पूर्णांक snd_asihpi_aesebu_rx_क्रमmat_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol) अणु
	वापस snd_asihpi_aesebu_क्रमmat_put(kcontrol, ucontrol,
					hpi_aesebu_receiver_set_क्रमmat);
पूर्ण

अटल पूर्णांक snd_asihpi_aesebu_rxstatus_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;

	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 0X1F;
	uinfo->value.पूर्णांकeger.step = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_aesebu_rxstatus_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol) अणु

	u32 h_control = kcontrol->निजी_value;
	u16 status;

	hpi_handle_error(hpi_aesebu_receiver_get_error_status(
					 h_control, &status));
	ucontrol->value.पूर्णांकeger.value[0] = status;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_aesebu_rx_add(काष्ठा snd_card_asihpi *asihpi,
				    काष्ठा hpi_control *hpi_ctl)
अणु
	काष्ठा snd_card *card = asihpi->card;
	काष्ठा snd_kcontrol_new snd_control;

	asihpi_ctl_init(&snd_control, hpi_ctl, "Format");
	snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	snd_control.info = snd_asihpi_aesebu_क्रमmat_info;
	snd_control.get = snd_asihpi_aesebu_rx_क्रमmat_get;
	snd_control.put = snd_asihpi_aesebu_rx_क्रमmat_put;


	अगर (ctl_add(card, &snd_control, asihpi) < 0)
		वापस -EINVAL;

	asihpi_ctl_init(&snd_control, hpi_ctl, "Status");
	snd_control.access =
	    SNDRV_CTL_ELEM_ACCESS_VOLATILE | SNDRV_CTL_ELEM_ACCESS_READ;
	snd_control.info = snd_asihpi_aesebu_rxstatus_info;
	snd_control.get = snd_asihpi_aesebu_rxstatus_get;

	वापस ctl_add(card, &snd_control, asihpi);
पूर्ण

अटल पूर्णांक snd_asihpi_aesebu_tx_क्रमmat_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol) अणु
	वापस snd_asihpi_aesebu_क्रमmat_get(kcontrol, ucontrol,
					hpi_aesebu_transmitter_get_क्रमmat);
पूर्ण

अटल पूर्णांक snd_asihpi_aesebu_tx_क्रमmat_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol) अणु
	वापस snd_asihpi_aesebu_क्रमmat_put(kcontrol, ucontrol,
					hpi_aesebu_transmitter_set_क्रमmat);
पूर्ण


अटल पूर्णांक snd_asihpi_aesebu_tx_add(काष्ठा snd_card_asihpi *asihpi,
				    काष्ठा hpi_control *hpi_ctl)
अणु
	काष्ठा snd_card *card = asihpi->card;
	काष्ठा snd_kcontrol_new snd_control;

	asihpi_ctl_init(&snd_control, hpi_ctl, "Format");
	snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	snd_control.info = snd_asihpi_aesebu_क्रमmat_info;
	snd_control.get = snd_asihpi_aesebu_tx_क्रमmat_get;
	snd_control.put = snd_asihpi_aesebu_tx_क्रमmat_put;

	वापस ctl_add(card, &snd_control, asihpi);
पूर्ण

/*------------------------------------------------------------
   Tuner controls
 ------------------------------------------------------------*/

/* Gain */

अटल पूर्णांक snd_asihpi_tuner_gain_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	u32 h_control = kcontrol->निजी_value;
	u16 err;
	लघु idx;
	u16 gain_range[3];

	क्रम (idx = 0; idx < 3; idx++) अणु
		err = hpi_tuner_query_gain(h_control,
					  idx, &gain_range[idx]);
		अगर (err != 0)
			वापस err;
	पूर्ण

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = ((पूर्णांक)gain_range[0]) / HPI_UNITS_PER_dB;
	uinfo->value.पूर्णांकeger.max = ((पूर्णांक)gain_range[1]) / HPI_UNITS_PER_dB;
	uinfo->value.पूर्णांकeger.step = ((पूर्णांक) gain_range[2]) / HPI_UNITS_PER_dB;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_tuner_gain_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	/*
	काष्ठा snd_card_asihpi *asihpi = snd_kcontrol_chip(kcontrol);
	*/
	u32 h_control = kcontrol->निजी_value;
	लघु gain;

	hpi_handle_error(hpi_tuner_get_gain(h_control, &gain));
	ucontrol->value.पूर्णांकeger.value[0] = gain / HPI_UNITS_PER_dB;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_tuner_gain_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	/*
	काष्ठा snd_card_asihpi *asihpi = snd_kcontrol_chip(kcontrol);
	*/
	u32 h_control = kcontrol->निजी_value;
	लघु gain;

	gain = (ucontrol->value.पूर्णांकeger.value[0]) * HPI_UNITS_PER_dB;
	hpi_handle_error(hpi_tuner_set_gain(h_control, gain));

	वापस 1;
पूर्ण

/* Band  */

अटल पूर्णांक asihpi_tuner_band_query(काष्ठा snd_kcontrol *kcontrol,
					u16 *band_list, u32 len) अणु
	u32 h_control = kcontrol->निजी_value;
	u16 err = 0;
	u32 i;

	क्रम (i = 0; i < len; i++) अणु
		err = hpi_tuner_query_band(
				h_control, i, &band_list[i]);
		अगर (err != 0)
			अवरोध;
	पूर्ण

	अगर (err && (err != HPI_ERROR_INVALID_OBJ_INDEX))
		वापस -EIO;

	वापस i;
पूर्ण

अटल पूर्णांक snd_asihpi_tuner_band_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	u16 tuner_bands[HPI_TUNER_BAND_LAST];
	पूर्णांक num_bands = 0;

	num_bands = asihpi_tuner_band_query(kcontrol, tuner_bands,
				HPI_TUNER_BAND_LAST);

	अगर (num_bands < 0)
		वापस num_bands;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, num_bands, asihpi_tuner_band_names);
पूर्ण

अटल पूर्णांक snd_asihpi_tuner_band_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 h_control = kcontrol->निजी_value;
	/*
	काष्ठा snd_card_asihpi *asihpi = snd_kcontrol_chip(kcontrol);
	*/
	u16 band, idx;
	u16 tuner_bands[HPI_TUNER_BAND_LAST];
	__always_unused u32 num_bands;

	num_bands = asihpi_tuner_band_query(kcontrol, tuner_bands,
				HPI_TUNER_BAND_LAST);

	hpi_handle_error(hpi_tuner_get_band(h_control, &band));

	ucontrol->value.क्रमागतerated.item[0] = -1;
	क्रम (idx = 0; idx < HPI_TUNER_BAND_LAST; idx++)
		अगर (tuner_bands[idx] == band) अणु
			ucontrol->value.क्रमागतerated.item[0] = idx;
			अवरोध;
		पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_tuner_band_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	/*
	काष्ठा snd_card_asihpi *asihpi = snd_kcontrol_chip(kcontrol);
	*/
	u32 h_control = kcontrol->निजी_value;
	अचिन्हित पूर्णांक idx;
	u16 band;
	u16 tuner_bands[HPI_TUNER_BAND_LAST];
	__always_unused u32 num_bands;

	num_bands = asihpi_tuner_band_query(kcontrol, tuner_bands,
			HPI_TUNER_BAND_LAST);

	idx = ucontrol->value.क्रमागतerated.item[0];
	अगर (idx >= ARRAY_SIZE(tuner_bands))
		idx = ARRAY_SIZE(tuner_bands) - 1;
	band = tuner_bands[idx];
	hpi_handle_error(hpi_tuner_set_band(h_control, band));

	वापस 1;
पूर्ण

/* Freq */

अटल पूर्णांक snd_asihpi_tuner_freq_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	u32 h_control = kcontrol->निजी_value;
	u16 err;
	u16 tuner_bands[HPI_TUNER_BAND_LAST];
	u16 num_bands = 0, band_iter, idx;
	u32 freq_range[3], temp_freq_range[3];

	num_bands = asihpi_tuner_band_query(kcontrol, tuner_bands,
			HPI_TUNER_BAND_LAST);

	freq_range[0] = पूर्णांक_उच्च;
	freq_range[1] = 0;
	freq_range[2] = पूर्णांक_उच्च;

	क्रम (band_iter = 0; band_iter < num_bands; band_iter++) अणु
		क्रम (idx = 0; idx < 3; idx++) अणु
			err = hpi_tuner_query_frequency(h_control,
				idx, tuner_bands[band_iter],
				&temp_freq_range[idx]);
			अगर (err != 0)
				वापस err;
		पूर्ण

		/* skip band with bogus stepping */
		अगर (temp_freq_range[2] <= 0)
			जारी;

		अगर (temp_freq_range[0] < freq_range[0])
			freq_range[0] = temp_freq_range[0];
		अगर (temp_freq_range[1] > freq_range[1])
			freq_range[1] = temp_freq_range[1];
		अगर (temp_freq_range[2] < freq_range[2])
			freq_range[2] = temp_freq_range[2];
	पूर्ण

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = ((पूर्णांक)freq_range[0]);
	uinfo->value.पूर्णांकeger.max = ((पूर्णांक)freq_range[1]);
	uinfo->value.पूर्णांकeger.step = ((पूर्णांक)freq_range[2]);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_tuner_freq_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 h_control = kcontrol->निजी_value;
	u32 freq;

	hpi_handle_error(hpi_tuner_get_frequency(h_control, &freq));
	ucontrol->value.पूर्णांकeger.value[0] = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_tuner_freq_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 h_control = kcontrol->निजी_value;
	u32 freq;

	freq = ucontrol->value.पूर्णांकeger.value[0];
	hpi_handle_error(hpi_tuner_set_frequency(h_control, freq));

	वापस 1;
पूर्ण

/* Tuner control group initializer  */
अटल पूर्णांक snd_asihpi_tuner_add(काष्ठा snd_card_asihpi *asihpi,
				काष्ठा hpi_control *hpi_ctl)
अणु
	काष्ठा snd_card *card = asihpi->card;
	काष्ठा snd_kcontrol_new snd_control;

	snd_control.निजी_value = hpi_ctl->h_control;
	snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;

	अगर (!hpi_tuner_get_gain(hpi_ctl->h_control, शून्य)) अणु
		asihpi_ctl_init(&snd_control, hpi_ctl, "Gain");
		snd_control.info = snd_asihpi_tuner_gain_info;
		snd_control.get = snd_asihpi_tuner_gain_get;
		snd_control.put = snd_asihpi_tuner_gain_put;

		अगर (ctl_add(card, &snd_control, asihpi) < 0)
			वापस -EINVAL;
	पूर्ण

	asihpi_ctl_init(&snd_control, hpi_ctl, "Band");
	snd_control.info = snd_asihpi_tuner_band_info;
	snd_control.get = snd_asihpi_tuner_band_get;
	snd_control.put = snd_asihpi_tuner_band_put;

	अगर (ctl_add(card, &snd_control, asihpi) < 0)
		वापस -EINVAL;

	asihpi_ctl_init(&snd_control, hpi_ctl, "Freq");
	snd_control.info = snd_asihpi_tuner_freq_info;
	snd_control.get = snd_asihpi_tuner_freq_get;
	snd_control.put = snd_asihpi_tuner_freq_put;

	वापस ctl_add(card, &snd_control, asihpi);
पूर्ण

/*------------------------------------------------------------
   Meter controls
 ------------------------------------------------------------*/
अटल पूर्णांक snd_asihpi_meter_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	u32 h_control = kcontrol->निजी_value;
	u32 count;
	u16 err;
	err = hpi_meter_query_channels(h_control, &count);
	अगर (err)
		count = HPI_MAX_CHANNELS;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = count;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 0x7FFFFFFF;
	वापस 0;
पूर्ण

/* linear values क्रम 10dB steps */
अटल स्थिर पूर्णांक log2lin[] = अणु
	0x7FFFFFFF, /* 0dB */
	679093956,
	214748365,
	 67909396,
	 21474837,
	  6790940,
	  2147484, /* -60dB */
	   679094,
	   214748, /* -80 */
	    67909,
	    21475, /* -100 */
	     6791,
	     2147,
	      679,
	      214,
	       68,
	       21,
		7,
		2
पूर्ण;

अटल पूर्णांक snd_asihpi_meter_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 h_control = kcontrol->निजी_value;
	लघु an_gain_mB[HPI_MAX_CHANNELS], i;
	u16 err;

	err = hpi_meter_get_peak(h_control, an_gain_mB);

	क्रम (i = 0; i < HPI_MAX_CHANNELS; i++) अणु
		अगर (err) अणु
			ucontrol->value.पूर्णांकeger.value[i] = 0;
		पूर्ण अन्यथा अगर (an_gain_mB[i] >= 0) अणु
			ucontrol->value.पूर्णांकeger.value[i] =
				an_gain_mB[i] << 16;
		पूर्ण अन्यथा अणु
			/* -ve is log value in millibels < -60dB,
			* convert to (roughly!) linear,
			*/
			ucontrol->value.पूर्णांकeger.value[i] =
					log2lin[an_gain_mB[i] / -1000];
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_meter_add(काष्ठा snd_card_asihpi *asihpi,
				काष्ठा hpi_control *hpi_ctl, पूर्णांक subidx)
अणु
	काष्ठा snd_card *card = asihpi->card;
	काष्ठा snd_kcontrol_new snd_control;

	asihpi_ctl_init(&snd_control, hpi_ctl, "Meter");
	snd_control.access =
	    SNDRV_CTL_ELEM_ACCESS_VOLATILE | SNDRV_CTL_ELEM_ACCESS_READ;
	snd_control.info = snd_asihpi_meter_info;
	snd_control.get = snd_asihpi_meter_get;

	snd_control.index = subidx;

	वापस ctl_add(card, &snd_control, asihpi);
पूर्ण

/*------------------------------------------------------------
   Multiplexer controls
 ------------------------------------------------------------*/
अटल पूर्णांक snd_card_asihpi_mux_count_sources(काष्ठा snd_kcontrol *snd_control)
अणु
	u32 h_control = snd_control->निजी_value;
	काष्ठा hpi_control hpi_ctl;
	पूर्णांक s, err;
	क्रम (s = 0; s < 32; s++) अणु
		err = hpi_multiplexer_query_source(h_control, s,
						  &hpi_ctl.
						  src_node_type,
						  &hpi_ctl.
						  src_node_index);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस s;
पूर्ण

अटल पूर्णांक snd_asihpi_mux_info(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	u16 src_node_type, src_node_index;
	u32 h_control = kcontrol->निजी_value;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items =
	    snd_card_asihpi_mux_count_sources(kcontrol);

	अगर (uinfo->value.क्रमागतerated.item >= uinfo->value.क्रमागतerated.items)
		uinfo->value.क्रमागतerated.item =
		    uinfo->value.क्रमागतerated.items - 1;

	hpi_multiplexer_query_source(h_control,
				     uinfo->value.क्रमागतerated.item,
				     &src_node_type, &src_node_index);

	प्र_लिखो(uinfo->value.क्रमागतerated.name, "%s %d",
		asihpi_src_names[src_node_type - HPI_SOURCENODE_NONE],
		src_node_index);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_mux_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 h_control = kcontrol->निजी_value;
	u16 source_type, source_index;
	u16 src_node_type, src_node_index;
	पूर्णांक s;

	hpi_handle_error(hpi_multiplexer_get_source(h_control,
				&source_type, &source_index));
	/* Should cache this search result! */
	क्रम (s = 0; s < 256; s++) अणु
		अगर (hpi_multiplexer_query_source(h_control, s,
					    &src_node_type, &src_node_index))
			अवरोध;

		अगर ((source_type == src_node_type)
		    && (source_index == src_node_index)) अणु
			ucontrol->value.क्रमागतerated.item[0] = s;
			वापस 0;
		पूर्ण
	पूर्ण
	snd_prपूर्णांकd(KERN_WARNING
		"Control %x failed to match mux source %hu %hu\n",
		h_control, source_type, source_index);
	ucontrol->value.क्रमागतerated.item[0] = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_mux_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक change;
	u32 h_control = kcontrol->निजी_value;
	u16 source_type, source_index;
	u16 e;

	change = 1;

	e = hpi_multiplexer_query_source(h_control,
				    ucontrol->value.क्रमागतerated.item[0],
				    &source_type, &source_index);
	अगर (!e)
		hpi_handle_error(
			hpi_multiplexer_set_source(h_control,
						source_type, source_index));
	वापस change;
पूर्ण


अटल पूर्णांक  snd_asihpi_mux_add(काष्ठा snd_card_asihpi *asihpi,
			       काष्ठा hpi_control *hpi_ctl)
अणु
	काष्ठा snd_card *card = asihpi->card;
	काष्ठा snd_kcontrol_new snd_control;

	asihpi_ctl_init(&snd_control, hpi_ctl, "Route");
	snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	snd_control.info = snd_asihpi_mux_info;
	snd_control.get = snd_asihpi_mux_get;
	snd_control.put = snd_asihpi_mux_put;

	वापस ctl_add(card, &snd_control, asihpi);

पूर्ण

/*------------------------------------------------------------
   Channel mode controls
 ------------------------------------------------------------*/
अटल पूर्णांक snd_asihpi_cmode_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर mode_names[HPI_CHANNEL_MODE_LAST + 1] = अणु
		"invalid",
		"Normal", "Swap",
		"From Left", "From Right",
		"To Left", "To Right"
	पूर्ण;

	u32 h_control = kcontrol->निजी_value;
	u16 mode;
	पूर्णांक i;
	स्थिर अक्षर *mapped_names[6];
	पूर्णांक valid_modes = 0;

	/* HPI channel mode values can be from 1 to 6
	Some adapters only support a contiguous subset
	*/
	क्रम (i = 0; i < HPI_CHANNEL_MODE_LAST; i++)
		अगर (!hpi_channel_mode_query_mode(
			h_control, i, &mode)) अणु
			mapped_names[valid_modes] = mode_names[mode];
			valid_modes++;
			पूर्ण

	अगर (!valid_modes)
		वापस -EINVAL;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, valid_modes, mapped_names);
पूर्ण

अटल पूर्णांक snd_asihpi_cmode_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 h_control = kcontrol->निजी_value;
	u16 mode;

	अगर (hpi_channel_mode_get(h_control, &mode))
		mode = 1;

	ucontrol->value.क्रमागतerated.item[0] = mode - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_cmode_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक change;
	u32 h_control = kcontrol->निजी_value;

	change = 1;

	hpi_handle_error(hpi_channel_mode_set(h_control,
			   ucontrol->value.क्रमागतerated.item[0] + 1));
	वापस change;
पूर्ण


अटल पूर्णांक snd_asihpi_cmode_add(काष्ठा snd_card_asihpi *asihpi,
				काष्ठा hpi_control *hpi_ctl)
अणु
	काष्ठा snd_card *card = asihpi->card;
	काष्ठा snd_kcontrol_new snd_control;

	asihpi_ctl_init(&snd_control, hpi_ctl, "Mode");
	snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	snd_control.info = snd_asihpi_cmode_info;
	snd_control.get = snd_asihpi_cmode_get;
	snd_control.put = snd_asihpi_cmode_put;

	वापस ctl_add(card, &snd_control, asihpi);
पूर्ण

/*------------------------------------------------------------
   Sampleघड़ी source  controls
 ------------------------------------------------------------*/
अटल स्थिर अक्षर * स्थिर sampleघड़ी_sources[] = अणु
	"N/A", "Local PLL", "Digital Sync", "Word External", "Word Header",
	"SMPTE", "Digital1", "Auto", "Network", "Invalid",
	"Prev Module", "BLU-Link",
	"Digital2", "Digital3", "Digital4", "Digital5",
	"Digital6", "Digital7", "Digital8"पूर्ण;

	/* Number of strings must match expected क्रमागतerated values */
	compile_समय_निश्चित(
		(ARRAY_SIZE(sampleघड़ी_sources) == MAX_CLOCKSOURCES),
		निश्चित_sampleघड़ी_sources_size);

अटल पूर्णांक snd_asihpi_clksrc_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_card_asihpi *asihpi =
			(काष्ठा snd_card_asihpi *)(kcontrol->निजी_data);
	काष्ठा clk_cache *clkcache = &asihpi->cc;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = clkcache->count;

	अगर (uinfo->value.क्रमागतerated.item >= uinfo->value.क्रमागतerated.items)
		uinfo->value.क्रमागतerated.item =
				uinfo->value.क्रमागतerated.items - 1;

	म_नकल(uinfo->value.क्रमागतerated.name,
	       clkcache->s[uinfo->value.क्रमागतerated.item].name);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_clksrc_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_card_asihpi *asihpi =
			(काष्ठा snd_card_asihpi *)(kcontrol->निजी_data);
	काष्ठा clk_cache *clkcache = &asihpi->cc;
	u32 h_control = kcontrol->निजी_value;
	u16 source, srcindex = 0;
	पूर्णांक i;

	ucontrol->value.क्रमागतerated.item[0] = 0;
	अगर (hpi_sample_घड़ी_get_source(h_control, &source))
		source = 0;

	अगर (source == HPI_SAMPLECLOCK_SOURCE_AESEBU_INPUT)
		अगर (hpi_sample_घड़ी_get_source_index(h_control, &srcindex))
			srcindex = 0;

	क्रम (i = 0; i < clkcache->count; i++)
		अगर ((clkcache->s[i].source == source) &&
			(clkcache->s[i].index == srcindex))
			अवरोध;

	ucontrol->value.क्रमागतerated.item[0] = i;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_clksrc_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_card_asihpi *asihpi =
			(काष्ठा snd_card_asihpi *)(kcontrol->निजी_data);
	काष्ठा clk_cache *clkcache = &asihpi->cc;
	अचिन्हित पूर्णांक item;
	पूर्णांक change;
	u32 h_control = kcontrol->निजी_value;

	change = 1;
	item = ucontrol->value.क्रमागतerated.item[0];
	अगर (item >= clkcache->count)
		item = clkcache->count-1;

	hpi_handle_error(hpi_sample_घड़ी_set_source(
				h_control, clkcache->s[item].source));

	अगर (clkcache->s[item].source == HPI_SAMPLECLOCK_SOURCE_AESEBU_INPUT)
		hpi_handle_error(hpi_sample_घड़ी_set_source_index(
				h_control, clkcache->s[item].index));
	वापस change;
पूर्ण

/*------------------------------------------------------------
   Clkrate controls
 ------------------------------------------------------------*/
/* Need to change this to क्रमागतerated control with list of rates */
अटल पूर्णांक snd_asihpi_clklocal_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 8000;
	uinfo->value.पूर्णांकeger.max = 192000;
	uinfo->value.पूर्णांकeger.step = 100;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_clklocal_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 h_control = kcontrol->निजी_value;
	u32 rate;
	u16 e;

	e = hpi_sample_घड़ी_get_local_rate(h_control, &rate);
	अगर (!e)
		ucontrol->value.पूर्णांकeger.value[0] = rate;
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[0] = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_clklocal_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक change;
	u32 h_control = kcontrol->निजी_value;

	/*  change = asihpi->mixer_clkrate[addr][0] != left ||
	   asihpi->mixer_clkrate[addr][1] != right;
	 */
	change = 1;
	hpi_handle_error(hpi_sample_घड़ी_set_local_rate(h_control,
				      ucontrol->value.पूर्णांकeger.value[0]));
	वापस change;
पूर्ण

अटल पूर्णांक snd_asihpi_clkrate_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 8000;
	uinfo->value.पूर्णांकeger.max = 192000;
	uinfo->value.पूर्णांकeger.step = 100;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_clkrate_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 h_control = kcontrol->निजी_value;
	u32 rate;
	u16 e;

	e = hpi_sample_घड़ी_get_sample_rate(h_control, &rate);
	अगर (!e)
		ucontrol->value.पूर्णांकeger.value[0] = rate;
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[0] = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_asihpi_sampleघड़ी_add(काष्ठा snd_card_asihpi *asihpi,
				      काष्ठा hpi_control *hpi_ctl)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_kcontrol_new snd_control;

	काष्ठा clk_cache *clkcache;
	u32 hSC =  hpi_ctl->h_control;
	पूर्णांक has_aes_in = 0;
	पूर्णांक i, j;
	u16 source;

	अगर (snd_BUG_ON(!asihpi))
		वापस -EINVAL;
	card = asihpi->card;
	clkcache = &asihpi->cc;
	snd_control.निजी_value = hpi_ctl->h_control;

	clkcache->has_local = 0;

	क्रम (i = 0; i <= HPI_SAMPLECLOCK_SOURCE_LAST; i++) अणु
		अगर  (hpi_sample_घड़ी_query_source(hSC,
				i, &source))
			अवरोध;
		clkcache->s[i].source = source;
		clkcache->s[i].index = 0;
		clkcache->s[i].name = sampleघड़ी_sources[source];
		अगर (source == HPI_SAMPLECLOCK_SOURCE_AESEBU_INPUT)
			has_aes_in = 1;
		अगर (source == HPI_SAMPLECLOCK_SOURCE_LOCAL)
			clkcache->has_local = 1;
	पूर्ण
	अगर (has_aes_in)
		/* alपढ़ोy will have picked up index 0 above */
		क्रम (j = 1; j < 8; j++) अणु
			अगर (hpi_sample_घड़ी_query_source_index(hSC,
				j, HPI_SAMPLECLOCK_SOURCE_AESEBU_INPUT,
				&source))
				अवरोध;
			clkcache->s[i].source =
				HPI_SAMPLECLOCK_SOURCE_AESEBU_INPUT;
			clkcache->s[i].index = j;
			clkcache->s[i].name = sampleघड़ी_sources[
					j+HPI_SAMPLECLOCK_SOURCE_LAST];
			i++;
		पूर्ण
	clkcache->count = i;

	asihpi_ctl_init(&snd_control, hpi_ctl, "Source");
	snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE ;
	snd_control.info = snd_asihpi_clksrc_info;
	snd_control.get = snd_asihpi_clksrc_get;
	snd_control.put = snd_asihpi_clksrc_put;
	अगर (ctl_add(card, &snd_control, asihpi) < 0)
		वापस -EINVAL;


	अगर (clkcache->has_local) अणु
		asihpi_ctl_init(&snd_control, hpi_ctl, "Localrate");
		snd_control.access = SNDRV_CTL_ELEM_ACCESS_READWRITE ;
		snd_control.info = snd_asihpi_clklocal_info;
		snd_control.get = snd_asihpi_clklocal_get;
		snd_control.put = snd_asihpi_clklocal_put;


		अगर (ctl_add(card, &snd_control, asihpi) < 0)
			वापस -EINVAL;
	पूर्ण

	asihpi_ctl_init(&snd_control, hpi_ctl, "Rate");
	snd_control.access =
	    SNDRV_CTL_ELEM_ACCESS_VOLATILE | SNDRV_CTL_ELEM_ACCESS_READ;
	snd_control.info = snd_asihpi_clkrate_info;
	snd_control.get = snd_asihpi_clkrate_get;

	वापस ctl_add(card, &snd_control, asihpi);
पूर्ण
/*------------------------------------------------------------
   Mixer
 ------------------------------------------------------------*/

अटल पूर्णांक snd_card_asihpi_mixer_new(काष्ठा snd_card_asihpi *asihpi)
अणु
	काष्ठा snd_card *card;
	अचिन्हित पूर्णांक idx = 0;
	अचिन्हित पूर्णांक subindex = 0;
	पूर्णांक err;
	काष्ठा hpi_control hpi_ctl, prev_ctl;

	अगर (snd_BUG_ON(!asihpi))
		वापस -EINVAL;
	card = asihpi->card;
	म_नकल(card->mixername, "Asihpi Mixer");

	err =
	    hpi_mixer_खोलो(asihpi->hpi->adapter->index,
			  &asihpi->h_mixer);
	hpi_handle_error(err);
	अगर (err)
		वापस -err;

	स_रखो(&prev_ctl, 0, माप(prev_ctl));
	prev_ctl.control_type = -1;

	क्रम (idx = 0; idx < 2000; idx++) अणु
		err = hpi_mixer_get_control_by_index(
				asihpi->h_mixer,
				idx,
				&hpi_ctl.src_node_type,
				&hpi_ctl.src_node_index,
				&hpi_ctl.dst_node_type,
				&hpi_ctl.dst_node_index,
				&hpi_ctl.control_type,
				&hpi_ctl.h_control);
		अगर (err) अणु
			अगर (err == HPI_ERROR_CONTROL_DISABLED) अणु
				अगर (mixer_dump)
					dev_info(&asihpi->pci->dev,
						   "Disabled HPI Control(%d)\n",
						   idx);
				जारी;
			पूर्ण अन्यथा
				अवरोध;

		पूर्ण

		hpi_ctl.src_node_type -= HPI_SOURCENODE_NONE;
		hpi_ctl.dst_node_type -= HPI_DESTNODE_NONE;

		/* ASI50xx in SSX mode has multiple meters on the same node.
		   Use subindex to create distinct ALSA controls
		   क्रम any duplicated controls.
		*/
		अगर ((hpi_ctl.control_type == prev_ctl.control_type) &&
		    (hpi_ctl.src_node_type == prev_ctl.src_node_type) &&
		    (hpi_ctl.src_node_index == prev_ctl.src_node_index) &&
		    (hpi_ctl.dst_node_type == prev_ctl.dst_node_type) &&
		    (hpi_ctl.dst_node_index == prev_ctl.dst_node_index))
			subindex++;
		अन्यथा
			subindex = 0;

		prev_ctl = hpi_ctl;

		चयन (hpi_ctl.control_type) अणु
		हाल HPI_CONTROL_VOLUME:
			err = snd_asihpi_volume_add(asihpi, &hpi_ctl);
			अवरोध;
		हाल HPI_CONTROL_LEVEL:
			err = snd_asihpi_level_add(asihpi, &hpi_ctl);
			अवरोध;
		हाल HPI_CONTROL_MULTIPLEXER:
			err = snd_asihpi_mux_add(asihpi, &hpi_ctl);
			अवरोध;
		हाल HPI_CONTROL_CHANNEL_MODE:
			err = snd_asihpi_cmode_add(asihpi, &hpi_ctl);
			अवरोध;
		हाल HPI_CONTROL_METER:
			err = snd_asihpi_meter_add(asihpi, &hpi_ctl, subindex);
			अवरोध;
		हाल HPI_CONTROL_SAMPLECLOCK:
			err = snd_asihpi_sampleघड़ी_add(
						asihpi, &hpi_ctl);
			अवरोध;
		हाल HPI_CONTROL_CONNECTION:	/* ignore these */
			जारी;
		हाल HPI_CONTROL_TUNER:
			err = snd_asihpi_tuner_add(asihpi, &hpi_ctl);
			अवरोध;
		हाल HPI_CONTROL_AESEBU_TRANSMITTER:
			err = snd_asihpi_aesebu_tx_add(asihpi, &hpi_ctl);
			अवरोध;
		हाल HPI_CONTROL_AESEBU_RECEIVER:
			err = snd_asihpi_aesebu_rx_add(asihpi, &hpi_ctl);
			अवरोध;
		हाल HPI_CONTROL_VOX:
		हाल HPI_CONTROL_BITSTREAM:
		हाल HPI_CONTROL_MICROPHONE:
		हाल HPI_CONTROL_PARAMETRIC_EQ:
		हाल HPI_CONTROL_COMPANDER:
		शेष:
			अगर (mixer_dump)
				dev_info(&asihpi->pci->dev,
					"Untranslated HPI Control (%d) %d %d %d %d %d\n",
					idx,
					hpi_ctl.control_type,
					hpi_ctl.src_node_type,
					hpi_ctl.src_node_index,
					hpi_ctl.dst_node_type,
					hpi_ctl.dst_node_index);
			जारी;
		पूर्ण
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (HPI_ERROR_INVALID_OBJ_INDEX != err)
		hpi_handle_error(err);

	dev_info(&asihpi->pci->dev, "%d mixer controls found\n", idx);

	वापस 0;
पूर्ण

/*------------------------------------------------------------
   /proc पूर्णांकerface
 ------------------------------------------------------------*/

अटल व्योम
snd_asihpi_proc_पढ़ो(काष्ठा snd_info_entry *entry,
			काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_card_asihpi *asihpi = entry->निजी_data;
	u32 h_control;
	u32 rate = 0;
	u16 source = 0;

	u16 num_outstreams;
	u16 num_instreams;
	u16 version;
	u32 serial_number;
	u16 type;

	पूर्णांक err;

	snd_iम_लिखो(buffer, "ASIHPI driver proc file\n");

	hpi_handle_error(hpi_adapter_get_info(asihpi->hpi->adapter->index,
			&num_outstreams, &num_instreams,
			&version, &serial_number, &type));

	snd_iम_लिखो(buffer,
			"Adapter type ASI%4X\nHardware Index %d\n"
			"%d outstreams\n%d instreams\n",
			type, asihpi->hpi->adapter->index,
			num_outstreams, num_instreams);

	snd_iम_लिखो(buffer,
		"Serial#%d\nHardware version %c%d\nDSP code version %03d\n",
		serial_number, ((version >> 3) & 0xf) + 'A', version & 0x7,
		((version >> 13) * 100) + ((version >> 7) & 0x3f));

	err = hpi_mixer_get_control(asihpi->h_mixer,
				  HPI_SOURCENODE_CLOCK_SOURCE, 0, 0, 0,
				  HPI_CONTROL_SAMPLECLOCK, &h_control);

	अगर (!err) अणु
		err = hpi_sample_घड़ी_get_sample_rate(h_control, &rate);
		err += hpi_sample_घड़ी_get_source(h_control, &source);

		अगर (!err)
			snd_iम_लिखो(buffer, "Sample Clock %dHz, source %s\n",
			rate, sampleघड़ी_sources[source]);
	पूर्ण
पूर्ण

अटल व्योम snd_asihpi_proc_init(काष्ठा snd_card_asihpi *asihpi)
अणु
	snd_card_ro_proc_new(asihpi->card, "info", asihpi,
			     snd_asihpi_proc_पढ़ो);
पूर्ण

/*------------------------------------------------------------
   HWDEP
 ------------------------------------------------------------*/

अटल पूर्णांक snd_asihpi_hpi_खोलो(काष्ठा snd_hwdep *hw, काष्ठा file *file)
अणु
	अगर (enable_hpi_hwdep)
		वापस 0;
	अन्यथा
		वापस -ENODEV;

पूर्ण

अटल पूर्णांक snd_asihpi_hpi_release(काष्ठा snd_hwdep *hw, काष्ठा file *file)
अणु
	अगर (enable_hpi_hwdep)
		वापस asihpi_hpi_release(file);
	अन्यथा
		वापस -ENODEV;
पूर्ण

अटल पूर्णांक snd_asihpi_hpi_ioctl(काष्ठा snd_hwdep *hw, काष्ठा file *file,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अगर (enable_hpi_hwdep)
		वापस asihpi_hpi_ioctl(file, cmd, arg);
	अन्यथा
		वापस -ENODEV;
पूर्ण


/* results in /dev/snd/hwC#D0 file क्रम each card with index #
   also /proc/asound/hwdep will contain '#-00: asihpi (HPI) for each card'
*/
अटल पूर्णांक snd_asihpi_hpi_new(काष्ठा snd_card_asihpi *asihpi, पूर्णांक device)
अणु
	काष्ठा snd_hwdep *hw;
	पूर्णांक err;

	err = snd_hwdep_new(asihpi->card, "HPI", device, &hw);
	अगर (err < 0)
		वापस err;
	म_नकल(hw->name, "asihpi (HPI)");
	hw->अगरace = SNDRV_HWDEP_IFACE_LAST;
	hw->ops.खोलो = snd_asihpi_hpi_खोलो;
	hw->ops.ioctl = snd_asihpi_hpi_ioctl;
	hw->ops.release = snd_asihpi_hpi_release;
	hw->निजी_data = asihpi;
	वापस 0;
पूर्ण

/*------------------------------------------------------------
   CARD
 ------------------------------------------------------------*/
अटल पूर्णांक snd_asihpi_probe(काष्ठा pci_dev *pci_dev,
			    स्थिर काष्ठा pci_device_id *pci_id)
अणु
	पूर्णांक err;
	काष्ठा hpi_adapter *hpi;
	काष्ठा snd_card *card;
	काष्ठा snd_card_asihpi *asihpi;

	u32 h_control;
	u32 h_stream;
	u32 adapter_index;

	अटल पूर्णांक dev;
	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;

	/* Should this be enable[hpi->index] ? */
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	/* Initialise low-level HPI driver */
	err = asihpi_adapter_probe(pci_dev, pci_id);
	अगर (err < 0)
		वापस err;

	hpi = pci_get_drvdata(pci_dev);
	adapter_index = hpi->adapter->index;
	/* first try to give the card the same index as its hardware index */
	err = snd_card_new(&pci_dev->dev, adapter_index, id[adapter_index],
			   THIS_MODULE, माप(काष्ठा snd_card_asihpi), &card);
	अगर (err < 0) अणु
		/* अगर that fails, try the शेष index==next available */
		err = snd_card_new(&pci_dev->dev, index[dev], id[dev],
				   THIS_MODULE, माप(काष्ठा snd_card_asihpi),
				   &card);
		अगर (err < 0)
			वापस err;
		dev_warn(&pci_dev->dev, "Adapter index %d->ALSA index %d\n",
			adapter_index, card->number);
	पूर्ण

	asihpi = card->निजी_data;
	asihpi->card = card;
	asihpi->pci = pci_dev;
	asihpi->hpi = hpi;
	hpi->snd_card = card;

	err = hpi_adapter_get_property(adapter_index,
		HPI_ADAPTER_PROPERTY_CAPS1,
		शून्य, &asihpi->support_grouping);
	अगर (err)
		asihpi->support_grouping = 0;

	err = hpi_adapter_get_property(adapter_index,
		HPI_ADAPTER_PROPERTY_CAPS2,
		&asihpi->support_mrx, शून्य);
	अगर (err)
		asihpi->support_mrx = 0;

	err = hpi_adapter_get_property(adapter_index,
		HPI_ADAPTER_PROPERTY_INTERVAL,
		शून्य, &asihpi->update_पूर्णांकerval_frames);
	अगर (err)
		asihpi->update_पूर्णांकerval_frames = 512;

	अगर (hpi->पूर्णांकerrupt_mode) अणु
		asihpi->pcm_start = snd_card_asihpi_pcm_पूर्णांक_start;
		asihpi->pcm_stop = snd_card_asihpi_pcm_पूर्णांक_stop;
		hpi->पूर्णांकerrupt_callback = snd_card_asihpi_isr;
	पूर्ण अन्यथा अणु
		asihpi->pcm_start = snd_card_asihpi_pcm_समयr_start;
		asihpi->pcm_stop = snd_card_asihpi_pcm_समयr_stop;
	पूर्ण

	hpi_handle_error(hpi_instream_खोलो(adapter_index,
			     0, &h_stream));

	err = hpi_instream_host_buffer_मुक्त(h_stream);
	asihpi->can_dma = (!err);

	hpi_handle_error(hpi_instream_बंद(h_stream));

	अगर (!asihpi->can_dma)
		asihpi->update_पूर्णांकerval_frames *= 2;

	err = hpi_adapter_get_property(adapter_index,
		HPI_ADAPTER_PROPERTY_CURCHANNELS,
		&asihpi->in_max_chans, &asihpi->out_max_chans);
	अगर (err) अणु
		asihpi->in_max_chans = 2;
		asihpi->out_max_chans = 2;
	पूर्ण

	अगर (asihpi->out_max_chans > 2) अणु /* assume LL mode */
		asihpi->out_min_chans = asihpi->out_max_chans;
		asihpi->in_min_chans = asihpi->in_max_chans;
		asihpi->support_grouping = 0;
	पूर्ण अन्यथा अणु
		asihpi->out_min_chans = 1;
		asihpi->in_min_chans = 1;
	पूर्ण

	dev_info(&pci_dev->dev, "Has dma:%d, grouping:%d, mrx:%d, uif:%d\n",
			asihpi->can_dma,
			asihpi->support_grouping,
			asihpi->support_mrx,
			asihpi->update_पूर्णांकerval_frames
	      );

	err = snd_card_asihpi_pcm_new(asihpi, 0);
	अगर (err < 0) अणु
		dev_err(&pci_dev->dev, "pcm_new failed\n");
		जाओ __nodev;
	पूर्ण
	err = snd_card_asihpi_mixer_new(asihpi);
	अगर (err < 0) अणु
		dev_err(&pci_dev->dev, "mixer_new failed\n");
		जाओ __nodev;
	पूर्ण

	err = hpi_mixer_get_control(asihpi->h_mixer,
				  HPI_SOURCENODE_CLOCK_SOURCE, 0, 0, 0,
				  HPI_CONTROL_SAMPLECLOCK, &h_control);

	अगर (!err)
		err = hpi_sample_घड़ी_set_local_rate(
			h_control, adapter_fs);

	snd_asihpi_proc_init(asihpi);

	/* always create, can be enabled or disabled dynamically
	    by enable_hwdep  module param*/
	snd_asihpi_hpi_new(asihpi, 0);

	म_नकल(card->driver, "ASIHPI");

	प्र_लिखो(card->लघुname, "AudioScience ASI%4X",
			asihpi->hpi->adapter->type);
	प्र_लिखो(card->दीर्घname, "%s %i",
			card->लघुname, adapter_index);
	err = snd_card_रेजिस्टर(card);

	अगर (!err) अणु
		dev++;
		वापस 0;
	पूर्ण
__nodev:
	snd_card_मुक्त(card);
	dev_err(&pci_dev->dev, "snd_asihpi_probe error %d\n", err);
	वापस err;

पूर्ण

अटल व्योम snd_asihpi_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा hpi_adapter *hpi = pci_get_drvdata(pci_dev);

	/* Stop पूर्णांकerrupts */
	अगर (hpi->पूर्णांकerrupt_mode) अणु
		hpi->पूर्णांकerrupt_callback = शून्य;
		hpi_handle_error(hpi_adapter_set_property(hpi->adapter->index,
			HPI_ADAPTER_PROPERTY_IRQ_RATE, 0, 0));
	पूर्ण

	snd_card_मुक्त(hpi->snd_card);
	hpi->snd_card = शून्य;
	asihpi_adapter_हटाओ(pci_dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id asihpi_pci_tbl[] = अणु
	अणुHPI_PCI_VENDOR_ID_TI, HPI_PCI_DEV_ID_DSP6205,
		HPI_PCI_VENDOR_ID_AUDIOSCIENCE, PCI_ANY_ID, 0, 0,
		(kernel_uदीर्घ_t)HPI_6205पूर्ण,
	अणुHPI_PCI_VENDOR_ID_TI, HPI_PCI_DEV_ID_PCI2040,
		HPI_PCI_VENDOR_ID_AUDIOSCIENCE, PCI_ANY_ID, 0, 0,
		(kernel_uदीर्घ_t)HPI_6000पूर्ण,
	अणु0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, asihpi_pci_tbl);

अटल काष्ठा pci_driver driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = asihpi_pci_tbl,
	.probe = snd_asihpi_probe,
	.हटाओ = snd_asihpi_हटाओ,
पूर्ण;

अटल पूर्णांक __init snd_asihpi_init(व्योम)
अणु
	asihpi_init();
	वापस pci_रेजिस्टर_driver(&driver);
पूर्ण

अटल व्योम __निकास snd_asihpi_निकास(व्योम)
अणु

	pci_unरेजिस्टर_driver(&driver);
	asihpi_निकास();
पूर्ण

module_init(snd_asihpi_init)
module_निकास(snd_asihpi_निकास)

