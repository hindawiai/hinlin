<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */


#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/audपन.स>
#समावेश <linux/usb/audio-v2.h>
#समावेश <linux/usb/audio-v3.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>

#समावेश "usbaudio.h"
#समावेश "card.h"
#समावेश "proc.h"
#समावेश "quirks.h"
#समावेश "endpoint.h"
#समावेश "pcm.h"
#समावेश "helper.h"
#समावेश "format.h"
#समावेश "clock.h"
#समावेश "stream.h"
#समावेश "power.h"
#समावेश "media.h"

अटल व्योम audioक्रमmat_मुक्त(काष्ठा audioक्रमmat *fp)
अणु
	list_del(&fp->list); /* unlink क्रम aव्योमing द्विगुन-मुक्त */
	kमुक्त(fp->rate_table);
	kमुक्त(fp->chmap);
	kमुक्त(fp);
पूर्ण

/*
 * मुक्त a substream
 */
अटल व्योम मुक्त_substream(काष्ठा snd_usb_substream *subs)
अणु
	काष्ठा audioक्रमmat *fp, *n;

	अगर (!subs->num_क्रमmats)
		वापस; /* not initialized */
	list_क्रम_each_entry_safe(fp, n, &subs->fmt_list, list)
		audioक्रमmat_मुक्त(fp);
	kमुक्त(subs->str_pd);
	snd_media_stream_delete(subs);
पूर्ण


/*
 * मुक्त a usb stream instance
 */
अटल व्योम snd_usb_audio_stream_मुक्त(काष्ठा snd_usb_stream *stream)
अणु
	मुक्त_substream(&stream->substream[0]);
	मुक्त_substream(&stream->substream[1]);
	list_del(&stream->list);
	kमुक्त(stream);
पूर्ण

अटल व्योम snd_usb_audio_pcm_मुक्त(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_usb_stream *stream = pcm->निजी_data;
	अगर (stream) अणु
		stream->pcm = शून्य;
		snd_usb_audio_stream_मुक्त(stream);
	पूर्ण
पूर्ण

/*
 * initialize the substream instance.
 */

अटल व्योम snd_usb_init_substream(काष्ठा snd_usb_stream *as,
				   पूर्णांक stream,
				   काष्ठा audioक्रमmat *fp,
				   काष्ठा snd_usb_घातer_करोमुख्य *pd)
अणु
	काष्ठा snd_usb_substream *subs = &as->substream[stream];

	INIT_LIST_HEAD(&subs->fmt_list);
	spin_lock_init(&subs->lock);

	subs->stream = as;
	subs->direction = stream;
	subs->dev = as->chip->dev;
	subs->txfr_quirk = as->chip->txfr_quirk;
	subs->tx_length_quirk = as->chip->tx_length_quirk;
	subs->speed = snd_usb_get_speed(subs->dev);
	subs->pkt_offset_adj = 0;
	subs->stream_offset_adj = 0;

	snd_usb_set_pcm_ops(as->pcm, stream);

	list_add_tail(&fp->list, &subs->fmt_list);
	subs->क्रमmats |= fp->क्रमmats;
	subs->num_क्रमmats++;
	subs->fmt_type = fp->fmt_type;
	subs->ep_num = fp->endpoपूर्णांक;
	अगर (fp->channels > subs->channels_max)
		subs->channels_max = fp->channels;

	अगर (pd) अणु
		subs->str_pd = pd;
		/* Initialize Power Doमुख्य to idle status D1 */
		snd_usb_घातer_करोमुख्य_set(subs->stream->chip, pd,
					 UAC3_PD_STATE_D1);
	पूर्ण

	snd_usb_pपुनः_स्मृतिate_buffer(subs);
पूर्ण

/* kctl callbacks क्रम usb-audio channel maps */
अटल पूर्णांक usb_chmap_ctl_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_pcm_chmap *info = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_usb_substream *subs = info->निजी_data;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = subs->channels_max;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = SNDRV_CHMAP_LAST;
	वापस 0;
पूर्ण

/* check whether a duplicated entry exists in the audiofmt list */
अटल bool have_dup_chmap(काष्ठा snd_usb_substream *subs,
			   काष्ठा audioक्रमmat *fp)
अणु
	काष्ठा audioक्रमmat *prev = fp;

	list_क्रम_each_entry_जारी_reverse(prev, &subs->fmt_list, list) अणु
		अगर (prev->chmap &&
		    !स_भेद(prev->chmap, fp->chmap, माप(*fp->chmap)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक usb_chmap_ctl_tlv(काष्ठा snd_kcontrol *kcontrol, पूर्णांक op_flag,
			     अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक __user *tlv)
अणु
	काष्ठा snd_pcm_chmap *info = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_usb_substream *subs = info->निजी_data;
	काष्ठा audioक्रमmat *fp;
	अचिन्हित पूर्णांक __user *dst;
	पूर्णांक count = 0;

	अगर (size < 8)
		वापस -ENOMEM;
	अगर (put_user(SNDRV_CTL_TLVT_CONTAINER, tlv))
		वापस -EFAULT;
	size -= 8;
	dst = tlv + 2;
	list_क्रम_each_entry(fp, &subs->fmt_list, list) अणु
		पूर्णांक i, ch_bytes;

		अगर (!fp->chmap)
			जारी;
		अगर (have_dup_chmap(subs, fp))
			जारी;
		/* copy the entry */
		ch_bytes = fp->chmap->channels * 4;
		अगर (size < 8 + ch_bytes)
			वापस -ENOMEM;
		अगर (put_user(SNDRV_CTL_TLVT_CHMAP_FIXED, dst) ||
		    put_user(ch_bytes, dst + 1))
			वापस -EFAULT;
		dst += 2;
		क्रम (i = 0; i < fp->chmap->channels; i++, dst++) अणु
			अगर (put_user(fp->chmap->map[i], dst))
				वापस -EFAULT;
		पूर्ण

		count += 8 + ch_bytes;
		size -= 8 + ch_bytes;
	पूर्ण
	अगर (put_user(count, tlv + 1))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक usb_chmap_ctl_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcm_chmap *info = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_usb_substream *subs = info->निजी_data;
	काष्ठा snd_pcm_chmap_elem *chmap = शून्य;
	पूर्णांक i = 0;

	अगर (subs->cur_audiofmt)
		chmap = subs->cur_audiofmt->chmap;
	अगर (chmap) अणु
		क्रम (i = 0; i < chmap->channels; i++)
			ucontrol->value.पूर्णांकeger.value[i] = chmap->map[i];
	पूर्ण
	क्रम (; i < subs->channels_max; i++)
		ucontrol->value.पूर्णांकeger.value[i] = 0;
	वापस 0;
पूर्ण

/* create a chmap kctl asचिन्हित to the given USB substream */
अटल पूर्णांक add_chmap(काष्ठा snd_pcm *pcm, पूर्णांक stream,
		     काष्ठा snd_usb_substream *subs)
अणु
	काष्ठा audioक्रमmat *fp;
	काष्ठा snd_pcm_chmap *chmap;
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक err;

	list_क्रम_each_entry(fp, &subs->fmt_list, list)
		अगर (fp->chmap)
			जाओ ok;
	/* no chmap is found */
	वापस 0;

 ok:
	err = snd_pcm_add_chmap_ctls(pcm, stream, शून्य, 0, 0, &chmap);
	अगर (err < 0)
		वापस err;

	/* override handlers */
	chmap->निजी_data = subs;
	kctl = chmap->kctl;
	kctl->info = usb_chmap_ctl_info;
	kctl->get = usb_chmap_ctl_get;
	kctl->tlv.c = usb_chmap_ctl_tlv;

	वापस 0;
पूर्ण

/* convert from USB ChannelConfig bits to ALSA chmap element */
अटल काष्ठा snd_pcm_chmap_elem *convert_chmap(पूर्णांक channels, अचिन्हित पूर्णांक bits,
						पूर्णांक protocol)
अणु
	अटल स्थिर अचिन्हित पूर्णांक uac1_maps[] = अणु
		SNDRV_CHMAP_FL,		/* left front */
		SNDRV_CHMAP_FR,		/* right front */
		SNDRV_CHMAP_FC,		/* center front */
		SNDRV_CHMAP_LFE,	/* LFE */
		SNDRV_CHMAP_SL,		/* left surround */
		SNDRV_CHMAP_SR,		/* right surround */
		SNDRV_CHMAP_FLC,	/* left of center */
		SNDRV_CHMAP_FRC,	/* right of center */
		SNDRV_CHMAP_RC,		/* surround */
		SNDRV_CHMAP_SL,		/* side left */
		SNDRV_CHMAP_SR,		/* side right */
		SNDRV_CHMAP_TC,		/* top */
		0 /* terminator */
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक uac2_maps[] = अणु
		SNDRV_CHMAP_FL,		/* front left */
		SNDRV_CHMAP_FR,		/* front right */
		SNDRV_CHMAP_FC,		/* front center */
		SNDRV_CHMAP_LFE,	/* LFE */
		SNDRV_CHMAP_RL,		/* back left */
		SNDRV_CHMAP_RR,		/* back right */
		SNDRV_CHMAP_FLC,	/* front left of center */
		SNDRV_CHMAP_FRC,	/* front right of center */
		SNDRV_CHMAP_RC,		/* back center */
		SNDRV_CHMAP_SL,		/* side left */
		SNDRV_CHMAP_SR,		/* side right */
		SNDRV_CHMAP_TC,		/* top center */
		SNDRV_CHMAP_TFL,	/* top front left */
		SNDRV_CHMAP_TFC,	/* top front center */
		SNDRV_CHMAP_TFR,	/* top front right */
		SNDRV_CHMAP_TRL,	/* top back left */
		SNDRV_CHMAP_TRC,	/* top back center */
		SNDRV_CHMAP_TRR,	/* top back right */
		SNDRV_CHMAP_TFLC,	/* top front left of center */
		SNDRV_CHMAP_TFRC,	/* top front right of center */
		SNDRV_CHMAP_LLFE,	/* left LFE */
		SNDRV_CHMAP_RLFE,	/* right LFE */
		SNDRV_CHMAP_TSL,	/* top side left */
		SNDRV_CHMAP_TSR,	/* top side right */
		SNDRV_CHMAP_BC,		/* bottom center */
		SNDRV_CHMAP_RLC,	/* back left of center */
		SNDRV_CHMAP_RRC,	/* back right of center */
		0 /* terminator */
	पूर्ण;
	काष्ठा snd_pcm_chmap_elem *chmap;
	स्थिर अचिन्हित पूर्णांक *maps;
	पूर्णांक c;

	अगर (channels > ARRAY_SIZE(chmap->map))
		वापस शून्य;

	chmap = kzalloc(माप(*chmap), GFP_KERNEL);
	अगर (!chmap)
		वापस शून्य;

	maps = protocol == UAC_VERSION_2 ? uac2_maps : uac1_maps;
	chmap->channels = channels;
	c = 0;

	अगर (bits) अणु
		क्रम (; bits && *maps; maps++, bits >>= 1)
			अगर (bits & 1)
				chmap->map[c++] = *maps;
	पूर्ण अन्यथा अणु
		/* If we're missing wChannelConfig, then guess something
		    to make sure the channel map is not skipped entirely */
		अगर (channels == 1)
			chmap->map[c++] = SNDRV_CHMAP_MONO;
		अन्यथा
			क्रम (; c < channels && *maps; maps++)
				chmap->map[c++] = *maps;
	पूर्ण

	क्रम (; c < channels; c++)
		chmap->map[c] = SNDRV_CHMAP_UNKNOWN;

	वापस chmap;
पूर्ण

/* UAC3 device stores channels inक्रमmation in Cluster Descriptors */
अटल काष्ठा
snd_pcm_chmap_elem *convert_chmap_v3(काष्ठा uac3_cluster_header_descriptor
								*cluster)
अणु
	अचिन्हित पूर्णांक channels = cluster->bNrChannels;
	काष्ठा snd_pcm_chmap_elem *chmap;
	व्योम *p = cluster;
	पूर्णांक len, c;

	अगर (channels > ARRAY_SIZE(chmap->map))
		वापस शून्य;

	chmap = kzalloc(माप(*chmap), GFP_KERNEL);
	अगर (!chmap)
		वापस शून्य;

	len = le16_to_cpu(cluster->wLength);
	c = 0;
	p += माप(काष्ठा uac3_cluster_header_descriptor);

	जबतक (((p - (व्योम *)cluster) < len) && (c < channels)) अणु
		काष्ठा uac3_cluster_segment_descriptor *cs_desc = p;
		u16 cs_len;
		u8 cs_type;

		cs_len = le16_to_cpu(cs_desc->wLength);
		cs_type = cs_desc->bSegmentType;

		अगर (cs_type == UAC3_CHANNEL_INFORMATION) अणु
			काष्ठा uac3_cluster_inक्रमmation_segment_descriptor *is = p;
			अचिन्हित अक्षर map;

			/*
			 * TODO: this conversion is not complete, update it
			 * after adding UAC3 values to asound.h
			 */
			चयन (is->bChRelationship) अणु
			हाल UAC3_CH_MONO:
				map = SNDRV_CHMAP_MONO;
				अवरोध;
			हाल UAC3_CH_LEFT:
			हाल UAC3_CH_FRONT_LEFT:
			हाल UAC3_CH_HEADPHONE_LEFT:
				map = SNDRV_CHMAP_FL;
				अवरोध;
			हाल UAC3_CH_RIGHT:
			हाल UAC3_CH_FRONT_RIGHT:
			हाल UAC3_CH_HEADPHONE_RIGHT:
				map = SNDRV_CHMAP_FR;
				अवरोध;
			हाल UAC3_CH_FRONT_CENTER:
				map = SNDRV_CHMAP_FC;
				अवरोध;
			हाल UAC3_CH_FRONT_LEFT_OF_CENTER:
				map = SNDRV_CHMAP_FLC;
				अवरोध;
			हाल UAC3_CH_FRONT_RIGHT_OF_CENTER:
				map = SNDRV_CHMAP_FRC;
				अवरोध;
			हाल UAC3_CH_SIDE_LEFT:
				map = SNDRV_CHMAP_SL;
				अवरोध;
			हाल UAC3_CH_SIDE_RIGHT:
				map = SNDRV_CHMAP_SR;
				अवरोध;
			हाल UAC3_CH_BACK_LEFT:
				map = SNDRV_CHMAP_RL;
				अवरोध;
			हाल UAC3_CH_BACK_RIGHT:
				map = SNDRV_CHMAP_RR;
				अवरोध;
			हाल UAC3_CH_BACK_CENTER:
				map = SNDRV_CHMAP_RC;
				अवरोध;
			हाल UAC3_CH_BACK_LEFT_OF_CENTER:
				map = SNDRV_CHMAP_RLC;
				अवरोध;
			हाल UAC3_CH_BACK_RIGHT_OF_CENTER:
				map = SNDRV_CHMAP_RRC;
				अवरोध;
			हाल UAC3_CH_TOP_CENTER:
				map = SNDRV_CHMAP_TC;
				अवरोध;
			हाल UAC3_CH_TOP_FRONT_LEFT:
				map = SNDRV_CHMAP_TFL;
				अवरोध;
			हाल UAC3_CH_TOP_FRONT_RIGHT:
				map = SNDRV_CHMAP_TFR;
				अवरोध;
			हाल UAC3_CH_TOP_FRONT_CENTER:
				map = SNDRV_CHMAP_TFC;
				अवरोध;
			हाल UAC3_CH_TOP_FRONT_LOC:
				map = SNDRV_CHMAP_TFLC;
				अवरोध;
			हाल UAC3_CH_TOP_FRONT_ROC:
				map = SNDRV_CHMAP_TFRC;
				अवरोध;
			हाल UAC3_CH_TOP_SIDE_LEFT:
				map = SNDRV_CHMAP_TSL;
				अवरोध;
			हाल UAC3_CH_TOP_SIDE_RIGHT:
				map = SNDRV_CHMAP_TSR;
				अवरोध;
			हाल UAC3_CH_TOP_BACK_LEFT:
				map = SNDRV_CHMAP_TRL;
				अवरोध;
			हाल UAC3_CH_TOP_BACK_RIGHT:
				map = SNDRV_CHMAP_TRR;
				अवरोध;
			हाल UAC3_CH_TOP_BACK_CENTER:
				map = SNDRV_CHMAP_TRC;
				अवरोध;
			हाल UAC3_CH_BOTTOM_CENTER:
				map = SNDRV_CHMAP_BC;
				अवरोध;
			हाल UAC3_CH_LOW_FREQUENCY_EFFECTS:
				map = SNDRV_CHMAP_LFE;
				अवरोध;
			हाल UAC3_CH_LFE_LEFT:
				map = SNDRV_CHMAP_LLFE;
				अवरोध;
			हाल UAC3_CH_LFE_RIGHT:
				map = SNDRV_CHMAP_RLFE;
				अवरोध;
			हाल UAC3_CH_RELATIONSHIP_UNDEFINED:
			शेष:
				map = SNDRV_CHMAP_UNKNOWN;
				अवरोध;
			पूर्ण
			chmap->map[c++] = map;
		पूर्ण
		p += cs_len;
	पूर्ण

	अगर (channels < c)
		pr_err("%s: channel number mismatch\n", __func__);

	chmap->channels = channels;

	क्रम (; c < channels; c++)
		chmap->map[c] = SNDRV_CHMAP_UNKNOWN;

	वापस chmap;
पूर्ण

/*
 * add this endpoपूर्णांक to the chip instance.
 * अगर a stream with the same endpoपूर्णांक alपढ़ोy exists, append to it.
 * अगर not, create a new pcm stream. note, fp is added to the substream
 * fmt_list and will be मुक्तd on the chip instance release. करो not मुक्त
 * fp or करो हटाओ it from the substream fmt_list to aव्योम द्विगुन-मुक्त.
 */
अटल पूर्णांक __snd_usb_add_audio_stream(काष्ठा snd_usb_audio *chip,
				      पूर्णांक stream,
				      काष्ठा audioक्रमmat *fp,
				      काष्ठा snd_usb_घातer_करोमुख्य *pd)

अणु
	काष्ठा snd_usb_stream *as;
	काष्ठा snd_usb_substream *subs;
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	list_क्रम_each_entry(as, &chip->pcm_list, list) अणु
		अगर (as->fmt_type != fp->fmt_type)
			जारी;
		subs = &as->substream[stream];
		अगर (subs->ep_num == fp->endpoपूर्णांक) अणु
			list_add_tail(&fp->list, &subs->fmt_list);
			subs->num_क्रमmats++;
			subs->क्रमmats |= fp->क्रमmats;
			वापस 0;
		पूर्ण
	पूर्ण
	/* look क्रम an empty stream */
	list_क्रम_each_entry(as, &chip->pcm_list, list) अणु
		अगर (as->fmt_type != fp->fmt_type)
			जारी;
		subs = &as->substream[stream];
		अगर (subs->ep_num)
			जारी;
		अगर (snd_device_get_state(chip->card, as->pcm) !=
		    SNDRV_DEV_BUILD)
			chip->need_delayed_रेजिस्टर = true;
		err = snd_pcm_new_stream(as->pcm, stream, 1);
		अगर (err < 0)
			वापस err;
		snd_usb_init_substream(as, stream, fp, pd);
		वापस add_chmap(as->pcm, stream, subs);
	पूर्ण

	/* create a new pcm */
	as = kzalloc(माप(*as), GFP_KERNEL);
	अगर (!as)
		वापस -ENOMEM;
	as->pcm_index = chip->pcm_devs;
	as->chip = chip;
	as->fmt_type = fp->fmt_type;
	err = snd_pcm_new(chip->card, "USB Audio", chip->pcm_devs,
			  stream == SNDRV_PCM_STREAM_PLAYBACK ? 1 : 0,
			  stream == SNDRV_PCM_STREAM_PLAYBACK ? 0 : 1,
			  &pcm);
	अगर (err < 0) अणु
		kमुक्त(as);
		वापस err;
	पूर्ण
	as->pcm = pcm;
	pcm->निजी_data = as;
	pcm->निजी_मुक्त = snd_usb_audio_pcm_मुक्त;
	pcm->info_flags = 0;
	अगर (chip->pcm_devs > 0)
		प्र_लिखो(pcm->name, "USB Audio #%d", chip->pcm_devs);
	अन्यथा
		म_नकल(pcm->name, "USB Audio");

	snd_usb_init_substream(as, stream, fp, pd);

	/*
	 * Keep using head insertion क्रम M-Audio Audiophile USB (पंचांग) which has a
	 * fix to swap capture stream order in conf/cards/USB-audio.conf
	 */
	अगर (chip->usb_id == USB_ID(0x0763, 0x2003))
		list_add(&as->list, &chip->pcm_list);
	अन्यथा
		list_add_tail(&as->list, &chip->pcm_list);

	chip->pcm_devs++;

	snd_usb_proc_pcm_क्रमmat_add(as);

	वापस add_chmap(pcm, stream, &as->substream[stream]);
पूर्ण

पूर्णांक snd_usb_add_audio_stream(काष्ठा snd_usb_audio *chip,
			     पूर्णांक stream,
			     काष्ठा audioक्रमmat *fp)
अणु
	वापस __snd_usb_add_audio_stream(chip, stream, fp, शून्य);
पूर्ण

अटल पूर्णांक snd_usb_add_audio_stream_v3(काष्ठा snd_usb_audio *chip,
				       पूर्णांक stream,
				       काष्ठा audioक्रमmat *fp,
				       काष्ठा snd_usb_घातer_करोमुख्य *pd)
अणु
	वापस __snd_usb_add_audio_stream(chip, stream, fp, pd);
पूर्ण

अटल पूर्णांक parse_uac_endpoपूर्णांक_attributes(काष्ठा snd_usb_audio *chip,
					 काष्ठा usb_host_पूर्णांकerface *alts,
					 पूर्णांक protocol, पूर्णांक अगरace_no)
अणु
	/* parsed with a v1 header here. that's ok as we only look at the
	 * header first which is the same क्रम both versions */
	काष्ठा uac_iso_endpoपूर्णांक_descriptor *csep;
	काष्ठा usb_पूर्णांकerface_descriptor *altsd = get_अगरace_desc(alts);
	पूर्णांक attributes = 0;

	csep = snd_usb_find_desc(alts->endpoपूर्णांक[0].extra, alts->endpoपूर्णांक[0].extralen, शून्य, USB_DT_CS_ENDPOINT);

	/* Creamware Noah has this descriptor after the 2nd endpoपूर्णांक */
	अगर (!csep && altsd->bNumEndpoपूर्णांकs >= 2)
		csep = snd_usb_find_desc(alts->endpoपूर्णांक[1].extra, alts->endpoपूर्णांक[1].extralen, शून्य, USB_DT_CS_ENDPOINT);

	/*
	 * If we can't locate the USB_DT_CS_ENDPOINT descriptor in the extra
	 * bytes after the first endpoपूर्णांक, go search the entire पूर्णांकerface.
	 * Some devices have it directly *beक्रमe* the standard endpoपूर्णांक.
	 */
	अगर (!csep)
		csep = snd_usb_find_desc(alts->extra, alts->extralen, शून्य, USB_DT_CS_ENDPOINT);

	अगर (!csep || csep->bLength < 7 ||
	    csep->bDescriptorSubtype != UAC_EP_GENERAL)
		जाओ error;

	अगर (protocol == UAC_VERSION_1) अणु
		attributes = csep->bmAttributes;
	पूर्ण अन्यथा अगर (protocol == UAC_VERSION_2) अणु
		काष्ठा uac2_iso_endpoपूर्णांक_descriptor *csep2 =
			(काष्ठा uac2_iso_endpoपूर्णांक_descriptor *) csep;

		अगर (csep2->bLength < माप(*csep2))
			जाओ error;
		attributes = csep->bmAttributes & UAC_EP_CS_ATTR_FILL_MAX;

		/* emulate the endpoपूर्णांक attributes of a v1 device */
		अगर (csep2->bmControls & UAC2_CONTROL_PITCH)
			attributes |= UAC_EP_CS_ATTR_PITCH_CONTROL;
	पूर्ण अन्यथा अणु /* UAC_VERSION_3 */
		काष्ठा uac3_iso_endpoपूर्णांक_descriptor *csep3 =
			(काष्ठा uac3_iso_endpoपूर्णांक_descriptor *) csep;

		अगर (csep3->bLength < माप(*csep3))
			जाओ error;
		/* emulate the endpoपूर्णांक attributes of a v1 device */
		अगर (le32_to_cpu(csep3->bmControls) & UAC2_CONTROL_PITCH)
			attributes |= UAC_EP_CS_ATTR_PITCH_CONTROL;
	पूर्ण

	वापस attributes;

 error:
	usb_audio_warn(chip,
		       "%u:%d : no or invalid class specific endpoint descriptor\n",
		       अगरace_no, altsd->bAlternateSetting);
	वापस 0;
पूर्ण

/* find an input terminal descriptor (either UAC1 or UAC2) with the given
 * terminal id
 */
अटल व्योम *
snd_usb_find_input_terminal_descriptor(काष्ठा usb_host_पूर्णांकerface *ctrl_अगरace,
				       पूर्णांक terminal_id, पूर्णांक protocol)
अणु
	काष्ठा uac2_input_terminal_descriptor *term = शून्य;

	जबतक ((term = snd_usb_find_csपूर्णांक_desc(ctrl_अगरace->extra,
					       ctrl_अगरace->extralen,
					       term, UAC_INPUT_TERMINAL))) अणु
		अगर (!snd_usb_validate_audio_desc(term, protocol))
			जारी;
		अगर (term->bTerminalID == terminal_id)
			वापस term;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *
snd_usb_find_output_terminal_descriptor(काष्ठा usb_host_पूर्णांकerface *ctrl_अगरace,
					पूर्णांक terminal_id, पूर्णांक protocol)
अणु
	/* OK to use with both UAC2 and UAC3 */
	काष्ठा uac2_output_terminal_descriptor *term = शून्य;

	जबतक ((term = snd_usb_find_csपूर्णांक_desc(ctrl_अगरace->extra,
					       ctrl_अगरace->extralen,
					       term, UAC_OUTPUT_TERMINAL))) अणु
		अगर (!snd_usb_validate_audio_desc(term, protocol))
			जारी;
		अगर (term->bTerminalID == terminal_id)
			वापस term;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा audioक्रमmat *
audio_क्रमmat_alloc_init(काष्ठा snd_usb_audio *chip,
		       काष्ठा usb_host_पूर्णांकerface *alts,
		       पूर्णांक protocol, पूर्णांक अगरace_no, पूर्णांक altset_idx,
		       पूर्णांक altno, पूर्णांक num_channels, पूर्णांक घड़ी)
अणु
	काष्ठा audioक्रमmat *fp;

	fp = kzalloc(माप(*fp), GFP_KERNEL);
	अगर (!fp)
		वापस शून्य;

	fp->अगरace = अगरace_no;
	fp->altsetting = altno;
	fp->altset_idx = altset_idx;
	fp->endpoपूर्णांक = get_endpoपूर्णांक(alts, 0)->bEndpoपूर्णांकAddress;
	fp->ep_attr = get_endpoपूर्णांक(alts, 0)->bmAttributes;
	fp->dataपूर्णांकerval = snd_usb_parse_dataपूर्णांकerval(chip, alts);
	fp->protocol = protocol;
	fp->maxpacksize = le16_to_cpu(get_endpoपूर्णांक(alts, 0)->wMaxPacketSize);
	fp->channels = num_channels;
	अगर (snd_usb_get_speed(chip->dev) == USB_SPEED_HIGH)
		fp->maxpacksize = (((fp->maxpacksize >> 11) & 3) + 1)
				* (fp->maxpacksize & 0x7ff);
	fp->घड़ी = घड़ी;
	INIT_LIST_HEAD(&fp->list);

	वापस fp;
पूर्ण

अटल काष्ठा audioक्रमmat *
snd_usb_get_audioक्रमmat_uac12(काष्ठा snd_usb_audio *chip,
			      काष्ठा usb_host_पूर्णांकerface *alts,
			      पूर्णांक protocol, पूर्णांक अगरace_no, पूर्णांक altset_idx,
			      पूर्णांक altno, पूर्णांक stream, पूर्णांक bm_quirk)
अणु
	काष्ठा usb_device *dev = chip->dev;
	काष्ठा uac_क्रमmat_type_i_continuous_descriptor *fmt;
	अचिन्हित पूर्णांक num_channels = 0, chconfig = 0;
	काष्ठा audioक्रमmat *fp;
	पूर्णांक घड़ी = 0;
	u64 क्रमmat;

	/* get audio क्रमmats */
	अगर (protocol == UAC_VERSION_1) अणु
		काष्ठा uac1_as_header_descriptor *as =
			snd_usb_find_csपूर्णांक_desc(alts->extra, alts->extralen,
						शून्य, UAC_AS_GENERAL);
		काष्ठा uac_input_terminal_descriptor *iterm;

		अगर (!as) अणु
			dev_err(&dev->dev,
				"%u:%d : UAC_AS_GENERAL descriptor not found\n",
				अगरace_no, altno);
			वापस शून्य;
		पूर्ण

		अगर (as->bLength < माप(*as)) अणु
			dev_err(&dev->dev,
				"%u:%d : invalid UAC_AS_GENERAL desc\n",
				अगरace_no, altno);
			वापस शून्य;
		पूर्ण

		क्रमmat = le16_to_cpu(as->wFormatTag); /* remember the क्रमmat value */

		iterm = snd_usb_find_input_terminal_descriptor(chip->ctrl_पूर्णांकf,
							       as->bTerminalLink,
							       protocol);
		अगर (iterm) अणु
			num_channels = iterm->bNrChannels;
			chconfig = le16_to_cpu(iterm->wChannelConfig);
		पूर्ण
	पूर्ण अन्यथा अणु /* UAC_VERSION_2 */
		काष्ठा uac2_input_terminal_descriptor *input_term;
		काष्ठा uac2_output_terminal_descriptor *output_term;
		काष्ठा uac2_as_header_descriptor *as =
			snd_usb_find_csपूर्णांक_desc(alts->extra, alts->extralen,
						शून्य, UAC_AS_GENERAL);

		अगर (!as) अणु
			dev_err(&dev->dev,
				"%u:%d : UAC_AS_GENERAL descriptor not found\n",
				अगरace_no, altno);
			वापस शून्य;
		पूर्ण

		अगर (as->bLength < माप(*as)) अणु
			dev_err(&dev->dev,
				"%u:%d : invalid UAC_AS_GENERAL desc\n",
				अगरace_no, altno);
			वापस शून्य;
		पूर्ण

		num_channels = as->bNrChannels;
		क्रमmat = le32_to_cpu(as->bmFormats);
		chconfig = le32_to_cpu(as->bmChannelConfig);

		/*
		 * lookup the terminal associated to this पूर्णांकerface
		 * to extract the घड़ी
		 */
		input_term = snd_usb_find_input_terminal_descriptor(chip->ctrl_पूर्णांकf,
								    as->bTerminalLink,
								    protocol);
		अगर (input_term) अणु
			घड़ी = input_term->bCSourceID;
			अगर (!chconfig && (num_channels == input_term->bNrChannels))
				chconfig = le32_to_cpu(input_term->bmChannelConfig);
			जाओ found_घड़ी;
		पूर्ण

		output_term = snd_usb_find_output_terminal_descriptor(chip->ctrl_पूर्णांकf,
								      as->bTerminalLink,
								      protocol);
		अगर (output_term) अणु
			घड़ी = output_term->bCSourceID;
			जाओ found_घड़ी;
		पूर्ण

		dev_err(&dev->dev,
			"%u:%d : bogus bTerminalLink %d\n",
			अगरace_no, altno, as->bTerminalLink);
		वापस शून्य;
	पूर्ण

found_घड़ी:
	/* get क्रमmat type */
	fmt = snd_usb_find_csपूर्णांक_desc(alts->extra, alts->extralen,
				      शून्य, UAC_FORMAT_TYPE);
	अगर (!fmt) अणु
		dev_err(&dev->dev,
			"%u:%d : no UAC_FORMAT_TYPE desc\n",
			अगरace_no, altno);
		वापस शून्य;
	पूर्ण
	अगर (((protocol == UAC_VERSION_1) && (fmt->bLength < 8))
			|| ((protocol == UAC_VERSION_2) &&
					(fmt->bLength < 6))) अणु
		dev_err(&dev->dev,
			"%u:%d : invalid UAC_FORMAT_TYPE desc\n",
			अगरace_no, altno);
		वापस शून्य;
	पूर्ण

	/*
	 * Blue Microphones workaround: The last altsetting is
	 * identical with the previous one, except क्रम a larger
	 * packet size, but is actually a mislabeled two-channel
	 * setting; ignore it.
	 *
	 * Part 2: analyze quirk flag and क्रमmat
	 */
	अगर (bm_quirk && fmt->bNrChannels == 1 && fmt->bSubframeSize == 2)
		वापस शून्य;

	fp = audio_क्रमmat_alloc_init(chip, alts, protocol, अगरace_no,
				     altset_idx, altno, num_channels, घड़ी);
	अगर (!fp)
		वापस ERR_PTR(-ENOMEM);

	fp->attributes = parse_uac_endpoपूर्णांक_attributes(chip, alts, protocol,
						       अगरace_no);

	/* some quirks क्रम attributes here */
	snd_usb_audioक्रमmat_attributes_quirk(chip, fp, stream);

	/* ok, let's parse further... */
	अगर (snd_usb_parse_audio_क्रमmat(chip, fp, क्रमmat,
					fmt, stream) < 0) अणु
		audioक्रमmat_मुक्त(fp);
		वापस शून्य;
	पूर्ण

	/* Create chmap */
	अगर (fp->channels != num_channels)
		chconfig = 0;

	fp->chmap = convert_chmap(fp->channels, chconfig, protocol);

	वापस fp;
पूर्ण

अटल काष्ठा audioक्रमmat *
snd_usb_get_audioक्रमmat_uac3(काष्ठा snd_usb_audio *chip,
			     काष्ठा usb_host_पूर्णांकerface *alts,
			     काष्ठा snd_usb_घातer_करोमुख्य **pd_out,
			     पूर्णांक अगरace_no, पूर्णांक altset_idx,
			     पूर्णांक altno, पूर्णांक stream)
अणु
	काष्ठा usb_device *dev = chip->dev;
	काष्ठा uac3_input_terminal_descriptor *input_term;
	काष्ठा uac3_output_terminal_descriptor *output_term;
	काष्ठा uac3_cluster_header_descriptor *cluster;
	काष्ठा uac3_as_header_descriptor *as = शून्य;
	काष्ठा uac3_hc_descriptor_header hc_header;
	काष्ठा snd_pcm_chmap_elem *chmap;
	काष्ठा snd_usb_घातer_करोमुख्य *pd;
	अचिन्हित अक्षर badd_profile;
	u64 badd_क्रमmats = 0;
	अचिन्हित पूर्णांक num_channels;
	काष्ठा audioक्रमmat *fp;
	u16 cluster_id, wLength;
	पूर्णांक घड़ी = 0;
	पूर्णांक err;

	badd_profile = chip->badd_profile;

	अगर (badd_profile >= UAC3_FUNCTION_SUBCLASS_GENERIC_IO) अणु
		अचिन्हित पूर्णांक maxpacksize =
			le16_to_cpu(get_endpoपूर्णांक(alts, 0)->wMaxPacketSize);

		चयन (maxpacksize) अणु
		शेष:
			dev_err(&dev->dev,
				"%u:%d : incorrect wMaxPacketSize for BADD profile\n",
				अगरace_no, altno);
			वापस शून्य;
		हाल UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_16:
		हाल UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_16:
			badd_क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
			num_channels = 1;
			अवरोध;
		हाल UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_24:
		हाल UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_24:
			badd_क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE;
			num_channels = 1;
			अवरोध;
		हाल UAC3_BADD_EP_MAXPSIZE_SYNC_STEREO_16:
		हाल UAC3_BADD_EP_MAXPSIZE_ASYNC_STEREO_16:
			badd_क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
			num_channels = 2;
			अवरोध;
		हाल UAC3_BADD_EP_MAXPSIZE_SYNC_STEREO_24:
		हाल UAC3_BADD_EP_MAXPSIZE_ASYNC_STEREO_24:
			badd_क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE;
			num_channels = 2;
			अवरोध;
		पूर्ण

		chmap = kzalloc(माप(*chmap), GFP_KERNEL);
		अगर (!chmap)
			वापस ERR_PTR(-ENOMEM);

		अगर (num_channels == 1) अणु
			chmap->map[0] = SNDRV_CHMAP_MONO;
		पूर्ण अन्यथा अणु
			chmap->map[0] = SNDRV_CHMAP_FL;
			chmap->map[1] = SNDRV_CHMAP_FR;
		पूर्ण

		chmap->channels = num_channels;
		घड़ी = UAC3_BADD_CS_ID9;
		जाओ found_घड़ी;
	पूर्ण

	as = snd_usb_find_csपूर्णांक_desc(alts->extra, alts->extralen,
				     शून्य, UAC_AS_GENERAL);
	अगर (!as) अणु
		dev_err(&dev->dev,
			"%u:%d : UAC_AS_GENERAL descriptor not found\n",
			अगरace_no, altno);
		वापस शून्य;
	पूर्ण

	अगर (as->bLength < माप(*as)) अणु
		dev_err(&dev->dev,
			"%u:%d : invalid UAC_AS_GENERAL desc\n",
			अगरace_no, altno);
		वापस शून्य;
	पूर्ण

	cluster_id = le16_to_cpu(as->wClusterDescrID);
	अगर (!cluster_id) अणु
		dev_err(&dev->dev,
			"%u:%d : no cluster descriptor\n",
			अगरace_no, altno);
		वापस शून्य;
	पूर्ण

	/*
	 * Get number of channels and channel map through
	 * High Capability Cluster Descriptor
	 *
	 * First step: get High Capability header and
	 * पढ़ो size of Cluster Descriptor
	 */
	err = snd_usb_ctl_msg(chip->dev,
			usb_rcvctrlpipe(chip->dev, 0),
			UAC3_CS_REQ_HIGH_CAPABILITY_DESCRIPTOR,
			USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_IN,
			cluster_id,
			snd_usb_ctrl_पूर्णांकf(chip),
			&hc_header, माप(hc_header));
	अगर (err < 0)
		वापस ERR_PTR(err);
	अन्यथा अगर (err != माप(hc_header)) अणु
		dev_err(&dev->dev,
			"%u:%d : can't get High Capability descriptor\n",
			अगरace_no, altno);
		वापस ERR_PTR(-EIO);
	पूर्ण

	/*
	 * Second step: allocate needed amount of memory
	 * and request Cluster Descriptor
	 */
	wLength = le16_to_cpu(hc_header.wLength);
	cluster = kzalloc(wLength, GFP_KERNEL);
	अगर (!cluster)
		वापस ERR_PTR(-ENOMEM);
	err = snd_usb_ctl_msg(chip->dev,
			usb_rcvctrlpipe(chip->dev, 0),
			UAC3_CS_REQ_HIGH_CAPABILITY_DESCRIPTOR,
			USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_IN,
			cluster_id,
			snd_usb_ctrl_पूर्णांकf(chip),
			cluster, wLength);
	अगर (err < 0) अणु
		kमुक्त(cluster);
		वापस ERR_PTR(err);
	पूर्ण अन्यथा अगर (err != wLength) अणु
		dev_err(&dev->dev,
			"%u:%d : can't get Cluster Descriptor\n",
			अगरace_no, altno);
		kमुक्त(cluster);
		वापस ERR_PTR(-EIO);
	पूर्ण

	num_channels = cluster->bNrChannels;
	chmap = convert_chmap_v3(cluster);
	kमुक्त(cluster);

	/*
	 * lookup the terminal associated to this पूर्णांकerface
	 * to extract the घड़ी
	 */
	input_term = snd_usb_find_input_terminal_descriptor(chip->ctrl_पूर्णांकf,
							    as->bTerminalLink,
							    UAC_VERSION_3);
	अगर (input_term) अणु
		घड़ी = input_term->bCSourceID;
		जाओ found_घड़ी;
	पूर्ण

	output_term = snd_usb_find_output_terminal_descriptor(chip->ctrl_पूर्णांकf,
							      as->bTerminalLink,
							      UAC_VERSION_3);
	अगर (output_term) अणु
		घड़ी = output_term->bCSourceID;
		जाओ found_घड़ी;
	पूर्ण

	dev_err(&dev->dev, "%u:%d : bogus bTerminalLink %d\n",
			अगरace_no, altno, as->bTerminalLink);
	kमुक्त(chmap);
	वापस शून्य;

found_घड़ी:
	fp = audio_क्रमmat_alloc_init(chip, alts, UAC_VERSION_3, अगरace_no,
				     altset_idx, altno, num_channels, घड़ी);
	अगर (!fp) अणु
		kमुक्त(chmap);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	fp->chmap = chmap;

	अगर (badd_profile >= UAC3_FUNCTION_SUBCLASS_GENERIC_IO) अणु
		fp->attributes = 0; /* No attributes */

		fp->fmt_type = UAC_FORMAT_TYPE_I;
		fp->क्रमmats = badd_क्रमmats;

		fp->nr_rates = 0;	/* SNDRV_PCM_RATE_CONTINUOUS */
		fp->rate_min = UAC3_BADD_SAMPLING_RATE;
		fp->rate_max = UAC3_BADD_SAMPLING_RATE;
		fp->rates = SNDRV_PCM_RATE_CONTINUOUS;

		pd = kzalloc(माप(*pd), GFP_KERNEL);
		अगर (!pd) अणु
			audioक्रमmat_मुक्त(fp);
			वापस शून्य;
		पूर्ण
		pd->pd_id = (stream == SNDRV_PCM_STREAM_PLAYBACK) ?
					UAC3_BADD_PD_ID10 : UAC3_BADD_PD_ID11;
		pd->pd_d1d0_rec = UAC3_BADD_PD_RECOVER_D1D0;
		pd->pd_d2d0_rec = UAC3_BADD_PD_RECOVER_D2D0;

	पूर्ण अन्यथा अणु
		fp->attributes = parse_uac_endpoपूर्णांक_attributes(chip, alts,
							       UAC_VERSION_3,
							       अगरace_no);

		pd = snd_usb_find_घातer_करोमुख्य(chip->ctrl_पूर्णांकf,
					       as->bTerminalLink);

		/* ok, let's parse further... */
		अगर (snd_usb_parse_audio_क्रमmat_v3(chip, fp, as, stream) < 0) अणु
			kमुक्त(pd);
			audioक्रमmat_मुक्त(fp);
			वापस शून्य;
		पूर्ण
	पूर्ण

	अगर (pd)
		*pd_out = pd;

	वापस fp;
पूर्ण

अटल पूर्णांक __snd_usb_parse_audio_पूर्णांकerface(काष्ठा snd_usb_audio *chip,
					   पूर्णांक अगरace_no,
					   bool *has_non_pcm, bool non_pcm)
अणु
	काष्ठा usb_device *dev;
	काष्ठा usb_पूर्णांकerface *अगरace;
	काष्ठा usb_host_पूर्णांकerface *alts;
	काष्ठा usb_पूर्णांकerface_descriptor *altsd;
	पूर्णांक i, altno, err, stream;
	काष्ठा audioक्रमmat *fp = शून्य;
	काष्ठा snd_usb_घातer_करोमुख्य *pd = शून्य;
	पूर्णांक num, protocol;

	dev = chip->dev;

	/* parse the पूर्णांकerface's altsettings */
	अगरace = usb_अगरnum_to_अगर(dev, अगरace_no);

	num = अगरace->num_altsetting;

	/*
	 * Dallas DS4201 workaround: It presents 5 altsettings, but the last
	 * one misses syncpipe, and करोes not produce any sound.
	 */
	अगर (chip->usb_id == USB_ID(0x04fa, 0x4201))
		num = 4;

	क्रम (i = 0; i < num; i++) अणु
		alts = &अगरace->altsetting[i];
		altsd = get_अगरace_desc(alts);
		protocol = altsd->bInterfaceProtocol;
		/* skip invalid one */
		अगर (((altsd->bInterfaceClass != USB_CLASS_AUDIO ||
		      (altsd->bInterfaceSubClass != USB_SUBCLASS_AUDIOSTREAMING &&
		       altsd->bInterfaceSubClass != USB_SUBCLASS_VENDOR_SPEC)) &&
		     altsd->bInterfaceClass != USB_CLASS_VENDOR_SPEC) ||
		    altsd->bNumEndpoपूर्णांकs < 1 ||
		    le16_to_cpu(get_endpoपूर्णांक(alts, 0)->wMaxPacketSize) == 0)
			जारी;
		/* must be isochronous */
		अगर ((get_endpoपूर्णांक(alts, 0)->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) !=
		    USB_ENDPOINT_XFER_ISOC)
			जारी;
		/* check direction */
		stream = (get_endpoपूर्णांक(alts, 0)->bEndpoपूर्णांकAddress & USB_सूची_IN) ?
			SNDRV_PCM_STREAM_CAPTURE : SNDRV_PCM_STREAM_PLAYBACK;
		altno = altsd->bAlternateSetting;

		अगर (snd_usb_apply_पूर्णांकerface_quirk(chip, अगरace_no, altno))
			जारी;

		/*
		 * Roland audio streaming पूर्णांकerfaces are marked with protocols
		 * 0/1/2, but are UAC 1 compatible.
		 */
		अगर (USB_ID_VENDOR(chip->usb_id) == 0x0582 &&
		    altsd->bInterfaceClass == USB_CLASS_VENDOR_SPEC &&
		    protocol <= 2)
			protocol = UAC_VERSION_1;

		चयन (protocol) अणु
		शेष:
			dev_dbg(&dev->dev, "%u:%d: unknown interface protocol %#02x, assuming v1\n",
				अगरace_no, altno, protocol);
			protocol = UAC_VERSION_1;
			fallthrough;
		हाल UAC_VERSION_1:
		हाल UAC_VERSION_2: अणु
			पूर्णांक bm_quirk = 0;

			/*
			 * Blue Microphones workaround: The last altsetting is
			 * identical with the previous one, except क्रम a larger
			 * packet size, but is actually a mislabeled two-channel
			 * setting; ignore it.
			 *
			 * Part 1: prepare quirk flag
			 */
			अगर (altno == 2 && num == 3 &&
			    fp && fp->altsetting == 1 && fp->channels == 1 &&
			    fp->क्रमmats == SNDRV_PCM_FMTBIT_S16_LE &&
			    protocol == UAC_VERSION_1 &&
			    le16_to_cpu(get_endpoपूर्णांक(alts, 0)->wMaxPacketSize) ==
							fp->maxpacksize * 2)
				bm_quirk = 1;

			fp = snd_usb_get_audioक्रमmat_uac12(chip, alts, protocol,
							   अगरace_no, i, altno,
							   stream, bm_quirk);
			अवरोध;
		पूर्ण
		हाल UAC_VERSION_3:
			fp = snd_usb_get_audioक्रमmat_uac3(chip, alts, &pd,
						अगरace_no, i, altno, stream);
			अवरोध;
		पूर्ण

		अगर (!fp)
			जारी;
		अन्यथा अगर (IS_ERR(fp))
			वापस PTR_ERR(fp);

		अगर (fp->fmt_type != UAC_FORMAT_TYPE_I)
			*has_non_pcm = true;
		अगर ((fp->fmt_type == UAC_FORMAT_TYPE_I) == non_pcm) अणु
			audioक्रमmat_मुक्त(fp);
			kमुक्त(pd);
			fp = शून्य;
			pd = शून्य;
			जारी;
		पूर्ण

		snd_usb_audioक्रमmat_set_sync_ep(chip, fp);

		dev_dbg(&dev->dev, "%u:%d: add audio endpoint %#x\n", अगरace_no, altno, fp->endpoपूर्णांक);
		अगर (protocol == UAC_VERSION_3)
			err = snd_usb_add_audio_stream_v3(chip, stream, fp, pd);
		अन्यथा
			err = snd_usb_add_audio_stream(chip, stream, fp);

		अगर (err < 0) अणु
			audioक्रमmat_मुक्त(fp);
			kमुक्त(pd);
			वापस err;
		पूर्ण

		/* add endpoपूर्णांकs */
		err = snd_usb_add_endpoपूर्णांक(chip, fp->endpoपूर्णांक,
					   SND_USB_ENDPOINT_TYPE_DATA);
		अगर (err < 0)
			वापस err;

		अगर (fp->sync_ep) अणु
			err = snd_usb_add_endpoपूर्णांक(chip, fp->sync_ep,
						   fp->implicit_fb ?
						   SND_USB_ENDPOINT_TYPE_DATA :
						   SND_USB_ENDPOINT_TYPE_SYNC);
			अगर (err < 0)
				वापस err;
		पूर्ण

		/* try to set the पूर्णांकerface... */
		usb_set_पूर्णांकerface(chip->dev, अगरace_no, 0);
		snd_usb_init_pitch(chip, fp);
		snd_usb_init_sample_rate(chip, fp, fp->rate_max);
		usb_set_पूर्णांकerface(chip->dev, अगरace_no, altno);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक snd_usb_parse_audio_पूर्णांकerface(काष्ठा snd_usb_audio *chip, पूर्णांक अगरace_no)
अणु
	पूर्णांक err;
	bool has_non_pcm = false;

	/* parse PCM क्रमmats */
	err = __snd_usb_parse_audio_पूर्णांकerface(chip, अगरace_no, &has_non_pcm, false);
	अगर (err < 0)
		वापस err;

	अगर (has_non_pcm) अणु
		/* parse non-PCM क्रमmats */
		err = __snd_usb_parse_audio_पूर्णांकerface(chip, अगरace_no, &has_non_pcm, true);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

