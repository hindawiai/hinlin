<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

#समावेश <linux/init.h>
#समावेश <linux/usb.h>

#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/pcm.h>

#समावेश "usbaudio.h"
#समावेश "helper.h"
#समावेश "card.h"
#समावेश "endpoint.h"
#समावेश "proc.h"

/* convert our full speed USB rate पूर्णांकo sampling rate in Hz */
अटल अंतरभूत अचिन्हित get_full_speed_hz(अचिन्हित पूर्णांक usb_rate)
अणु
	वापस (usb_rate * 125 + (1 << 12)) >> 13;
पूर्ण

/* convert our high speed USB rate पूर्णांकo sampling rate in Hz */
अटल अंतरभूत अचिन्हित get_high_speed_hz(अचिन्हित पूर्णांक usb_rate)
अणु
	वापस (usb_rate * 125 + (1 << 9)) >> 10;
पूर्ण

/*
 * common proc files to show the usb device info
 */
अटल व्योम proc_audio_usbbus_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_usb_audio *chip = entry->निजी_data;
	अगर (!atomic_पढ़ो(&chip->shutकरोwn))
		snd_iम_लिखो(buffer, "%03d/%03d\n", chip->dev->bus->busnum, chip->dev->devnum);
पूर्ण

अटल व्योम proc_audio_usbid_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_usb_audio *chip = entry->निजी_data;
	अगर (!atomic_पढ़ो(&chip->shutकरोwn))
		snd_iम_लिखो(buffer, "%04x:%04x\n", 
			    USB_ID_VENDOR(chip->usb_id),
			    USB_ID_PRODUCT(chip->usb_id));
पूर्ण

व्योम snd_usb_audio_create_proc(काष्ठा snd_usb_audio *chip)
अणु
	snd_card_ro_proc_new(chip->card, "usbbus", chip,
			     proc_audio_usbbus_पढ़ो);
	snd_card_ro_proc_new(chip->card, "usbid", chip,
			     proc_audio_usbid_पढ़ो);
पूर्ण

अटल स्थिर अक्षर * स्थिर channel_labels[] = अणु
	[SNDRV_CHMAP_NA]	= "N/A",
	[SNDRV_CHMAP_MONO]	= "MONO",
	[SNDRV_CHMAP_FL]	= "FL",
	[SNDRV_CHMAP_FR]	= "FR",
	[SNDRV_CHMAP_FC]	= "FC",
	[SNDRV_CHMAP_LFE]	= "LFE",
	[SNDRV_CHMAP_RL]	= "RL",
	[SNDRV_CHMAP_RR]	= "RR",
	[SNDRV_CHMAP_FLC]	= "FLC",
	[SNDRV_CHMAP_FRC]	= "FRC",
	[SNDRV_CHMAP_RC]	= "RC",
	[SNDRV_CHMAP_SL]	= "SL",
	[SNDRV_CHMAP_SR]	= "SR",
	[SNDRV_CHMAP_TC]	= "TC",
	[SNDRV_CHMAP_TFL]	= "TFL",
	[SNDRV_CHMAP_TFC]	= "TFC",
	[SNDRV_CHMAP_TFR]	= "TFR",
	[SNDRV_CHMAP_TRL]	= "TRL",
	[SNDRV_CHMAP_TRC]	= "TRC",
	[SNDRV_CHMAP_TRR]	= "TRR",
	[SNDRV_CHMAP_TFLC]	= "TFLC",
	[SNDRV_CHMAP_TFRC]	= "TFRC",
	[SNDRV_CHMAP_LLFE]	= "LLFE",
	[SNDRV_CHMAP_RLFE]	= "RLFE",
	[SNDRV_CHMAP_TSL]	= "TSL",
	[SNDRV_CHMAP_TSR]	= "TSR",
	[SNDRV_CHMAP_BC]	= "BC",
	[SNDRV_CHMAP_RLC]	= "RLC",
	[SNDRV_CHMAP_RRC]	= "RRC",
पूर्ण;

/*
 * proc पूर्णांकerface क्रम list the supported pcm क्रमmats
 */
अटल व्योम proc_dump_substream_क्रमmats(काष्ठा snd_usb_substream *subs, काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा audioक्रमmat *fp;
	अटल स्थिर अक्षर * स्थिर sync_types[4] = अणु
		"NONE", "ASYNC", "ADAPTIVE", "SYNC"
	पूर्ण;

	list_क्रम_each_entry(fp, &subs->fmt_list, list) अणु
		snd_pcm_क्रमmat_t fmt;

		snd_iम_लिखो(buffer, "  Interface %d\n", fp->अगरace);
		snd_iम_लिखो(buffer, "    Altset %d\n", fp->altsetting);
		snd_iम_लिखो(buffer, "    Format:");
		pcm_क्रम_each_क्रमmat(fmt)
			अगर (fp->क्रमmats & pcm_क्रमmat_to_bits(fmt))
				snd_iम_लिखो(buffer, " %s",
					    snd_pcm_क्रमmat_name(fmt));
		snd_iम_लिखो(buffer, "\n");
		snd_iम_लिखो(buffer, "    Channels: %d\n", fp->channels);
		snd_iम_लिखो(buffer, "    Endpoint: 0x%02x (%d %s) (%s)\n",
			    fp->endpoपूर्णांक,
			    fp->endpoपूर्णांक & USB_ENDPOINT_NUMBER_MASK,
			    fp->endpoपूर्णांक & USB_सूची_IN ? "IN" : "OUT",
			    sync_types[(fp->ep_attr & USB_ENDPOINT_SYNCTYPE) >> 2]);
		अगर (fp->rates & SNDRV_PCM_RATE_CONTINUOUS) अणु
			snd_iम_लिखो(buffer, "    Rates: %d - %d (continuous)\n",
				    fp->rate_min, fp->rate_max);
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक i;
			snd_iम_लिखो(buffer, "    Rates: ");
			क्रम (i = 0; i < fp->nr_rates; i++) अणु
				अगर (i > 0)
					snd_iम_लिखो(buffer, ", ");
				snd_iम_लिखो(buffer, "%d", fp->rate_table[i]);
			पूर्ण
			snd_iम_लिखो(buffer, "\n");
		पूर्ण
		अगर (subs->speed != USB_SPEED_FULL)
			snd_iम_लिखो(buffer, "    Data packet interval: %d us\n",
				    125 * (1 << fp->dataपूर्णांकerval));
		snd_iम_लिखो(buffer, "    Bits: %d\n", fp->fmt_bits);

		अगर (fp->dsd_raw)
			snd_iम_लिखो(buffer, "    DSD raw: DOP=%d, bitrev=%d\n",
				    fp->dsd_करोp, fp->dsd_bitrev);

		अगर (fp->chmap) अणु
			स्थिर काष्ठा snd_pcm_chmap_elem *map = fp->chmap;
			पूर्णांक c;

			snd_iम_लिखो(buffer, "    Channel map:");
			क्रम (c = 0; c < map->channels; c++) अणु
				अगर (map->map[c] >= ARRAY_SIZE(channel_labels) ||
				    !channel_labels[map->map[c]])
					snd_iम_लिखो(buffer, " --");
				अन्यथा
					snd_iम_लिखो(buffer, " %s",
						    channel_labels[map->map[c]]);
			पूर्ण
			snd_iम_लिखो(buffer, "\n");
		पूर्ण

		अगर (fp->sync_ep) अणु
			snd_iम_लिखो(buffer, "    Sync Endpoint: 0x%02x (%d %s)\n",
				    fp->sync_ep,
				    fp->sync_ep & USB_ENDPOINT_NUMBER_MASK,
				    fp->sync_ep & USB_सूची_IN ? "IN" : "OUT");
			snd_iम_लिखो(buffer, "    Sync EP Interface: %d\n",
				    fp->sync_अगरace);
			snd_iम_लिखो(buffer, "    Sync EP Altset: %d\n",
				    fp->sync_altsetting);
			snd_iम_लिखो(buffer, "    Implicit Feedback Mode: %s\n",
				    fp->implicit_fb ? "Yes" : "No");
		पूर्ण

		// snd_iम_लिखो(buffer, "    Max Packet Size = %d\n", fp->maxpacksize);
		// snd_iम_लिखो(buffer, "    EP Attribute = %#x\n", fp->attributes);
	पूर्ण
पूर्ण

अटल व्योम proc_dump_ep_status(काष्ठा snd_usb_substream *subs,
				काष्ठा snd_usb_endpoपूर्णांक *data_ep,
				काष्ठा snd_usb_endpoपूर्णांक *sync_ep,
				काष्ठा snd_info_buffer *buffer)
अणु
	अगर (!data_ep)
		वापस;
	snd_iम_लिखो(buffer, "    Packet Size = %d\n", data_ep->curpacksize);
	snd_iम_लिखो(buffer, "    Momentary freq = %u Hz (%#x.%04x)\n",
		    subs->speed == USB_SPEED_FULL
		    ? get_full_speed_hz(data_ep->freqm)
		    : get_high_speed_hz(data_ep->freqm),
		    data_ep->freqm >> 16, data_ep->freqm & 0xffff);
	अगर (sync_ep && data_ep->freqshअगरt != पूर्णांक_न्यून) अणु
		पूर्णांक res = 16 - data_ep->freqshअगरt;
		snd_iम_लिखो(buffer, "    Feedback Format = %d.%d\n",
			    (sync_ep->syncmaxsize > 3 ? 32 : 24) - res, res);
	पूर्ण
पूर्ण

अटल व्योम proc_dump_substream_status(काष्ठा snd_usb_audio *chip,
				       काष्ठा snd_usb_substream *subs,
				       काष्ठा snd_info_buffer *buffer)
अणु
	mutex_lock(&chip->mutex);
	अगर (subs->running) अणु
		snd_iम_लिखो(buffer, "  Status: Running\n");
		अगर (subs->cur_audiofmt) अणु
			snd_iम_लिखो(buffer, "    Interface = %d\n", subs->cur_audiofmt->अगरace);
			snd_iम_लिखो(buffer, "    Altset = %d\n", subs->cur_audiofmt->altsetting);
		पूर्ण
		proc_dump_ep_status(subs, subs->data_endpoपूर्णांक, subs->sync_endpoपूर्णांक, buffer);
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "  Status: Stop\n");
	पूर्ण
	mutex_unlock(&chip->mutex);
पूर्ण

अटल व्योम proc_pcm_क्रमmat_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_usb_stream *stream = entry->निजी_data;
	काष्ठा snd_usb_audio *chip = stream->chip;

	snd_iम_लिखो(buffer, "%s : %s\n", chip->card->दीर्घname, stream->pcm->name);

	अगर (stream->substream[SNDRV_PCM_STREAM_PLAYBACK].num_क्रमmats) अणु
		snd_iम_लिखो(buffer, "\nPlayback:\n");
		proc_dump_substream_status(chip, &stream->substream[SNDRV_PCM_STREAM_PLAYBACK], buffer);
		proc_dump_substream_क्रमmats(&stream->substream[SNDRV_PCM_STREAM_PLAYBACK], buffer);
	पूर्ण
	अगर (stream->substream[SNDRV_PCM_STREAM_CAPTURE].num_क्रमmats) अणु
		snd_iम_लिखो(buffer, "\nCapture:\n");
		proc_dump_substream_status(chip, &stream->substream[SNDRV_PCM_STREAM_CAPTURE], buffer);
		proc_dump_substream_क्रमmats(&stream->substream[SNDRV_PCM_STREAM_CAPTURE], buffer);
	पूर्ण
पूर्ण

व्योम snd_usb_proc_pcm_क्रमmat_add(काष्ठा snd_usb_stream *stream)
अणु
	अक्षर name[32];
	काष्ठा snd_card *card = stream->chip->card;

	प्र_लिखो(name, "stream%d", stream->pcm_index);
	snd_card_ro_proc_new(card, name, stream, proc_pcm_क्रमmat_पढ़ो);
पूर्ण

