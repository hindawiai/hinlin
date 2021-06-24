<शैली गुरु>
/*
 * Copyright (c) 2013 Federico Simoncelli
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * Fushicai USBTV007 Audio-Video Grabber Driver
 *
 * Product web site:
 * http://www.fushicai.com/products_detail/&productId=d05449ee-b690-42f9-a661-aa7353894bed.hपंचांगl
 *
 * No physical hardware was harmed running Winकरोws during the
 * reverse-engineering activity
 */

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/pcm_params.h>

#समावेश "usbtv.h"

अटल स्थिर काष्ठा snd_pcm_hardware snd_usbtv_digital_hw = अणु
	.info = SNDRV_PCM_INFO_BATCH |
		SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP_VALID,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.rates = SNDRV_PCM_RATE_48000,
	.rate_min = 48000,
	.rate_max = 48000,
	.channels_min = 2,
	.channels_max = 2,
	.period_bytes_min = 11059,
	.period_bytes_max = 13516,
	.periods_min = 2,
	.periods_max = 98,
	.buffer_bytes_max = 62720 * 8, /* value in usbaudio.c */
पूर्ण;

अटल पूर्णांक snd_usbtv_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा usbtv *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	chip->snd_substream = substream;
	runसमय->hw = snd_usbtv_digital_hw;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_usbtv_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा usbtv *chip = snd_pcm_substream_chip(substream);

	अगर (atomic_पढ़ो(&chip->snd_stream)) अणु
		atomic_set(&chip->snd_stream, 0);
		schedule_work(&chip->snd_trigger);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_usbtv_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा usbtv *chip = snd_pcm_substream_chip(substream);

	chip->snd_buffer_pos = 0;
	chip->snd_period_pos = 0;

	वापस 0;
पूर्ण

अटल व्योम usbtv_audio_urb_received(काष्ठा urb *urb)
अणु
	काष्ठा usbtv *chip = urb->context;
	काष्ठा snd_pcm_substream *substream = chip->snd_substream;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	माप_प्रकार i, frame_bytes, chunk_length, buffer_pos, period_pos;
	पूर्णांक period_elapsed;
	अचिन्हित दीर्घ flags;
	व्योम *urb_current;

	चयन (urb->status) अणु
	हाल 0:
	हाल -ETIMEDOUT:
		अवरोध;
	हाल -ENOENT:
	हाल -EPROTO:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		वापस;
	शेष:
		dev_warn(chip->dev, "unknown audio urb status %i\n",
			urb->status);
	पूर्ण

	अगर (!atomic_पढ़ो(&chip->snd_stream))
		वापस;

	frame_bytes = runसमय->frame_bits >> 3;
	chunk_length = USBTV_CHUNK / frame_bytes;

	buffer_pos = chip->snd_buffer_pos;
	period_pos = chip->snd_period_pos;
	period_elapsed = 0;

	क्रम (i = 0; i < urb->actual_length; i += USBTV_CHUNK_SIZE) अणु
		urb_current = urb->transfer_buffer + i + USBTV_AUDIO_HDRSIZE;

		अगर (buffer_pos + chunk_length >= runसमय->buffer_size) अणु
			माप_प्रकार cnt = (runसमय->buffer_size - buffer_pos) *
				frame_bytes;
			स_नकल(runसमय->dma_area + buffer_pos * frame_bytes,
				urb_current, cnt);
			स_नकल(runसमय->dma_area, urb_current + cnt,
				chunk_length * frame_bytes - cnt);
		पूर्ण अन्यथा अणु
			स_नकल(runसमय->dma_area + buffer_pos * frame_bytes,
				urb_current, chunk_length * frame_bytes);
		पूर्ण

		buffer_pos += chunk_length;
		period_pos += chunk_length;

		अगर (buffer_pos >= runसमय->buffer_size)
			buffer_pos -= runसमय->buffer_size;

		अगर (period_pos >= runसमय->period_size) अणु
			period_pos -= runसमय->period_size;
			period_elapsed = 1;
		पूर्ण
	पूर्ण

	snd_pcm_stream_lock_irqsave(substream, flags);

	chip->snd_buffer_pos = buffer_pos;
	chip->snd_period_pos = period_pos;

	snd_pcm_stream_unlock_irqrestore(substream, flags);

	अगर (period_elapsed)
		snd_pcm_period_elapsed(substream);

	usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक usbtv_audio_start(काष्ठा usbtv *chip)
अणु
	अचिन्हित पूर्णांक pipe;
	अटल स्थिर u16 setup[][2] = अणु
		/* These seem to enable the device. */
		अणु USBTV_BASE + 0x0008, 0x0001 पूर्ण,
		अणु USBTV_BASE + 0x01d0, 0x00ff पूर्ण,
		अणु USBTV_BASE + 0x01d9, 0x0002 पूर्ण,

		अणु USBTV_BASE + 0x01da, 0x0013 पूर्ण,
		अणु USBTV_BASE + 0x01db, 0x0012 पूर्ण,
		अणु USBTV_BASE + 0x01e9, 0x0002 पूर्ण,
		अणु USBTV_BASE + 0x01ec, 0x006c पूर्ण,
		अणु USBTV_BASE + 0x0294, 0x0020 पूर्ण,
		अणु USBTV_BASE + 0x0255, 0x00cf पूर्ण,
		अणु USBTV_BASE + 0x0256, 0x0020 पूर्ण,
		अणु USBTV_BASE + 0x01eb, 0x0030 पूर्ण,
		अणु USBTV_BASE + 0x027d, 0x00a6 पूर्ण,
		अणु USBTV_BASE + 0x0280, 0x0011 पूर्ण,
		अणु USBTV_BASE + 0x0281, 0x0040 पूर्ण,
		अणु USBTV_BASE + 0x0282, 0x0011 पूर्ण,
		अणु USBTV_BASE + 0x0283, 0x0040 पूर्ण,
		अणु 0xf891, 0x0010 पूर्ण,

		/* this sets the input from composite */
		अणु USBTV_BASE + 0x0284, 0x00aa पूर्ण,
	पूर्ण;

	chip->snd_bulk_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (chip->snd_bulk_urb == शून्य)
		जाओ err_alloc_urb;

	pipe = usb_rcvbulkpipe(chip->udev, USBTV_AUDIO_ENDP);

	chip->snd_bulk_urb->transfer_buffer = kzalloc(
		USBTV_AUDIO_URBSIZE, GFP_KERNEL);
	अगर (chip->snd_bulk_urb->transfer_buffer == शून्य)
		जाओ err_transfer_buffer;

	usb_fill_bulk_urb(chip->snd_bulk_urb, chip->udev, pipe,
		chip->snd_bulk_urb->transfer_buffer, USBTV_AUDIO_URBSIZE,
		usbtv_audio_urb_received, chip);

	/* starting the stream */
	usbtv_set_regs(chip, setup, ARRAY_SIZE(setup));

	usb_clear_halt(chip->udev, pipe);
	usb_submit_urb(chip->snd_bulk_urb, GFP_ATOMIC);

	वापस 0;

err_transfer_buffer:
	usb_मुक्त_urb(chip->snd_bulk_urb);
	chip->snd_bulk_urb = शून्य;

err_alloc_urb:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक usbtv_audio_stop(काष्ठा usbtv *chip)
अणु
	अटल स्थिर u16 setup[][2] = अणु
	/* The original winकरोws driver someबार sends also:
	 *   अणु USBTV_BASE + 0x00a2, 0x0013 पूर्ण
	 * but it seems useless and its real effects are untested at
	 * the moment.
	 */
		अणु USBTV_BASE + 0x027d, 0x0000 पूर्ण,
		अणु USBTV_BASE + 0x0280, 0x0010 पूर्ण,
		अणु USBTV_BASE + 0x0282, 0x0010 पूर्ण,
	पूर्ण;

	अगर (chip->snd_bulk_urb) अणु
		usb_समाप्त_urb(chip->snd_bulk_urb);
		kमुक्त(chip->snd_bulk_urb->transfer_buffer);
		usb_मुक्त_urb(chip->snd_bulk_urb);
		chip->snd_bulk_urb = शून्य;
	पूर्ण

	usbtv_set_regs(chip, setup, ARRAY_SIZE(setup));

	वापस 0;
पूर्ण

व्योम usbtv_audio_suspend(काष्ठा usbtv *usbtv)
अणु
	अगर (atomic_पढ़ो(&usbtv->snd_stream) && usbtv->snd_bulk_urb)
		usb_समाप्त_urb(usbtv->snd_bulk_urb);
पूर्ण

व्योम usbtv_audio_resume(काष्ठा usbtv *usbtv)
अणु
	अगर (atomic_पढ़ो(&usbtv->snd_stream) && usbtv->snd_bulk_urb)
		usb_submit_urb(usbtv->snd_bulk_urb, GFP_ATOMIC);
पूर्ण

अटल व्योम snd_usbtv_trigger(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usbtv *chip = container_of(work, काष्ठा usbtv, snd_trigger);

	अगर (!chip->snd)
		वापस;

	अगर (atomic_पढ़ो(&chip->snd_stream))
		usbtv_audio_start(chip);
	अन्यथा
		usbtv_audio_stop(chip);
पूर्ण

अटल पूर्णांक snd_usbtv_card_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा usbtv *chip = snd_pcm_substream_chip(substream);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		atomic_set(&chip->snd_stream, 1);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		atomic_set(&chip->snd_stream, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	schedule_work(&chip->snd_trigger);

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_usbtv_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा usbtv *chip = snd_pcm_substream_chip(substream);

	वापस chip->snd_buffer_pos;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_usbtv_pcm_ops = अणु
	.खोलो = snd_usbtv_pcm_खोलो,
	.बंद = snd_usbtv_pcm_बंद,
	.prepare = snd_usbtv_prepare,
	.trigger = snd_usbtv_card_trigger,
	.poपूर्णांकer = snd_usbtv_poपूर्णांकer,
पूर्ण;

पूर्णांक usbtv_audio_init(काष्ठा usbtv *usbtv)
अणु
	पूर्णांक rv;
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;

	INIT_WORK(&usbtv->snd_trigger, snd_usbtv_trigger);
	atomic_set(&usbtv->snd_stream, 0);

	rv = snd_card_new(&usbtv->udev->dev, SNDRV_DEFAULT_IDX1, "usbtv",
		THIS_MODULE, 0, &card);
	अगर (rv < 0)
		वापस rv;

	strscpy(card->driver, usbtv->dev->driver->name, माप(card->driver));
	strscpy(card->लघुname, "usbtv", माप(card->लघुname));
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		"USBTV Audio at bus %d device %d", usbtv->udev->bus->busnum,
		usbtv->udev->devnum);

	snd_card_set_dev(card, usbtv->dev);

	usbtv->snd = card;

	rv = snd_pcm_new(card, "USBTV Audio", 0, 0, 1, &pcm);
	अगर (rv < 0)
		जाओ err;

	strscpy(pcm->name, "USBTV Audio Input", माप(pcm->name));
	pcm->info_flags = 0;
	pcm->निजी_data = usbtv;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_usbtv_pcm_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_CONTINUOUS,
		शून्य, USBTV_AUDIO_BUFFER, USBTV_AUDIO_BUFFER);

	rv = snd_card_रेजिस्टर(card);
	अगर (rv)
		जाओ err;

	वापस 0;

err:
	usbtv->snd = शून्य;
	snd_card_मुक्त(card);

	वापस rv;
पूर्ण

व्योम usbtv_audio_मुक्त(काष्ठा usbtv *usbtv)
अणु
	cancel_work_sync(&usbtv->snd_trigger);

	अगर (usbtv->snd && usbtv->udev) अणु
		snd_card_मुक्त_when_बंदd(usbtv->snd);
		usbtv->snd = शून्य;
	पूर्ण
पूर्ण
