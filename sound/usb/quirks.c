<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/audपन.स>
#समावेश <linux/usb/midi.h>
#समावेश <linux/bits.h>

#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/pcm.h>

#समावेश "usbaudio.h"
#समावेश "card.h"
#समावेश "mixer.h"
#समावेश "mixer_quirks.h"
#समावेश "midi.h"
#समावेश "quirks.h"
#समावेश "helper.h"
#समावेश "endpoint.h"
#समावेश "pcm.h"
#समावेश "clock.h"
#समावेश "stream.h"

/*
 * handle the quirks क्रम the contained पूर्णांकerfaces
 */
अटल पूर्णांक create_composite_quirk(काष्ठा snd_usb_audio *chip,
				  काष्ठा usb_पूर्णांकerface *अगरace,
				  काष्ठा usb_driver *driver,
				  स्थिर काष्ठा snd_usb_audio_quirk *quirk_comp)
अणु
	पूर्णांक probed_अगरnum = get_अगरace_desc(अगरace->altsetting)->bInterfaceNumber;
	स्थिर काष्ठा snd_usb_audio_quirk *quirk;
	पूर्णांक err;

	क्रम (quirk = quirk_comp->data; quirk->अगरnum >= 0; ++quirk) अणु
		अगरace = usb_अगरnum_to_अगर(chip->dev, quirk->अगरnum);
		अगर (!अगरace)
			जारी;
		अगर (quirk->अगरnum != probed_अगरnum &&
		    usb_पूर्णांकerface_claimed(अगरace))
			जारी;
		err = snd_usb_create_quirk(chip, अगरace, driver, quirk);
		अगर (err < 0)
			वापस err;
	पूर्ण

	क्रम (quirk = quirk_comp->data; quirk->अगरnum >= 0; ++quirk) अणु
		अगरace = usb_अगरnum_to_अगर(chip->dev, quirk->अगरnum);
		अगर (!अगरace)
			जारी;
		अगर (quirk->अगरnum != probed_अगरnum &&
		    !usb_पूर्णांकerface_claimed(अगरace)) अणु
			err = usb_driver_claim_पूर्णांकerface(driver, अगरace,
							 USB_AUDIO_IFACE_UNUSED);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ignore_पूर्णांकerface_quirk(काष्ठा snd_usb_audio *chip,
				  काष्ठा usb_पूर्णांकerface *अगरace,
				  काष्ठा usb_driver *driver,
				  स्थिर काष्ठा snd_usb_audio_quirk *quirk)
अणु
	वापस 0;
पूर्ण


/*
 * Allow alignment on audio sub-slot (channel samples) rather than
 * on audio slots (audio frames)
 */
अटल पूर्णांक create_align_transfer_quirk(काष्ठा snd_usb_audio *chip,
				       काष्ठा usb_पूर्णांकerface *अगरace,
				       काष्ठा usb_driver *driver,
				       स्थिर काष्ठा snd_usb_audio_quirk *quirk)
अणु
	chip->txfr_quirk = 1;
	वापस 1;	/* Continue with creating streams and mixer */
पूर्ण

अटल पूर्णांक create_any_midi_quirk(काष्ठा snd_usb_audio *chip,
				 काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				 काष्ठा usb_driver *driver,
				 स्थिर काष्ठा snd_usb_audio_quirk *quirk)
अणु
	वापस snd_usbmidi_create(chip->card, पूर्णांकf, &chip->midi_list, quirk);
पूर्ण

/*
 * create a stream क्रम an पूर्णांकerface with proper descriptors
 */
अटल पूर्णांक create_standard_audio_quirk(काष्ठा snd_usb_audio *chip,
				       काष्ठा usb_पूर्णांकerface *अगरace,
				       काष्ठा usb_driver *driver,
				       स्थिर काष्ठा snd_usb_audio_quirk *quirk)
अणु
	काष्ठा usb_host_पूर्णांकerface *alts;
	काष्ठा usb_पूर्णांकerface_descriptor *altsd;
	पूर्णांक err;

	अगर (chip->usb_id == USB_ID(0x1686, 0x00dd)) /* Zoom R16/24 */
		chip->tx_length_quirk = 1;

	alts = &अगरace->altsetting[0];
	altsd = get_अगरace_desc(alts);
	err = snd_usb_parse_audio_पूर्णांकerface(chip, altsd->bInterfaceNumber);
	अगर (err < 0) अणु
		usb_audio_err(chip, "cannot setup if %d: error %d\n",
			   altsd->bInterfaceNumber, err);
		वापस err;
	पूर्ण
	/* reset the current पूर्णांकerface */
	usb_set_पूर्णांकerface(chip->dev, altsd->bInterfaceNumber, 0);
	वापस 0;
पूर्ण

/* create the audio stream and the corresponding endpoपूर्णांकs from the fixed
 * audioक्रमmat object; this is used क्रम quirks with the fixed EPs
 */
अटल पूर्णांक add_audio_stream_from_fixed_fmt(काष्ठा snd_usb_audio *chip,
					   काष्ठा audioक्रमmat *fp)
अणु
	पूर्णांक stream, err;

	stream = (fp->endpoपूर्णांक & USB_सूची_IN) ?
		SNDRV_PCM_STREAM_CAPTURE : SNDRV_PCM_STREAM_PLAYBACK;

	snd_usb_audioक्रमmat_set_sync_ep(chip, fp);

	err = snd_usb_add_audio_stream(chip, stream, fp);
	अगर (err < 0)
		वापस err;

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

	वापस 0;
पूर्ण

/*
 * create a stream क्रम an endpoपूर्णांक/altsetting without proper descriptors
 */
अटल पूर्णांक create_fixed_stream_quirk(काष्ठा snd_usb_audio *chip,
				     काष्ठा usb_पूर्णांकerface *अगरace,
				     काष्ठा usb_driver *driver,
				     स्थिर काष्ठा snd_usb_audio_quirk *quirk)
अणु
	काष्ठा audioक्रमmat *fp;
	काष्ठा usb_host_पूर्णांकerface *alts;
	काष्ठा usb_पूर्णांकerface_descriptor *altsd;
	अचिन्हित *rate_table = शून्य;
	पूर्णांक err;

	fp = kmemdup(quirk->data, माप(*fp), GFP_KERNEL);
	अगर (!fp)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&fp->list);
	अगर (fp->nr_rates > MAX_NR_RATES) अणु
		kमुक्त(fp);
		वापस -EINVAL;
	पूर्ण
	अगर (fp->nr_rates > 0) अणु
		rate_table = kmemdup(fp->rate_table,
				     माप(पूर्णांक) * fp->nr_rates, GFP_KERNEL);
		अगर (!rate_table) अणु
			kमुक्त(fp);
			वापस -ENOMEM;
		पूर्ण
		fp->rate_table = rate_table;
	पूर्ण

	अगर (fp->अगरace != get_अगरace_desc(&अगरace->altsetting[0])->bInterfaceNumber ||
	    fp->altset_idx >= अगरace->num_altsetting) अणु
		err = -EINVAL;
		जाओ error;
	पूर्ण
	alts = &अगरace->altsetting[fp->altset_idx];
	altsd = get_अगरace_desc(alts);
	अगर (altsd->bNumEndpoपूर्णांकs <= fp->ep_idx) अणु
		err = -EINVAL;
		जाओ error;
	पूर्ण

	fp->protocol = altsd->bInterfaceProtocol;

	अगर (fp->dataपूर्णांकerval == 0)
		fp->dataपूर्णांकerval = snd_usb_parse_dataपूर्णांकerval(chip, alts);
	अगर (fp->maxpacksize == 0)
		fp->maxpacksize = le16_to_cpu(get_endpoपूर्णांक(alts, fp->ep_idx)->wMaxPacketSize);
	अगर (!fp->fmt_type)
		fp->fmt_type = UAC_FORMAT_TYPE_I;

	err = add_audio_stream_from_fixed_fmt(chip, fp);
	अगर (err < 0)
		जाओ error;

	usb_set_पूर्णांकerface(chip->dev, fp->अगरace, 0);
	snd_usb_init_pitch(chip, fp);
	snd_usb_init_sample_rate(chip, fp, fp->rate_max);
	वापस 0;

 error:
	list_del(&fp->list); /* unlink क्रम aव्योमing द्विगुन-मुक्त */
	kमुक्त(fp);
	kमुक्त(rate_table);
	वापस err;
पूर्ण

अटल पूर्णांक create_स्वतः_pcm_quirk(काष्ठा snd_usb_audio *chip,
				 काष्ठा usb_पूर्णांकerface *अगरace,
				 काष्ठा usb_driver *driver)
अणु
	काष्ठा usb_host_पूर्णांकerface *alts;
	काष्ठा usb_पूर्णांकerface_descriptor *altsd;
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;
	काष्ठा uac1_as_header_descriptor *ashd;
	काष्ठा uac_क्रमmat_type_i_discrete_descriptor *fmtd;

	/*
	 * Most Roland/Yamaha audio streaming पूर्णांकerfaces have more or less
	 * standard descriptors, but older devices might lack descriptors, and
	 * future ones might change, so ensure that we fail silently अगर the
	 * पूर्णांकerface करोesn't look exactly right.
	 */

	/* must have a non-zero altsetting क्रम streaming */
	अगर (अगरace->num_altsetting < 2)
		वापस -ENODEV;
	alts = &अगरace->altsetting[1];
	altsd = get_अगरace_desc(alts);

	/* must have an isochronous endpoपूर्णांक क्रम streaming */
	अगर (altsd->bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;
	epd = get_endpoपूर्णांक(alts, 0);
	अगर (!usb_endpoपूर्णांक_xfer_isoc(epd))
		वापस -ENODEV;

	/* must have क्रमmat descriptors */
	ashd = snd_usb_find_csपूर्णांक_desc(alts->extra, alts->extralen, शून्य,
				       UAC_AS_GENERAL);
	fmtd = snd_usb_find_csपूर्णांक_desc(alts->extra, alts->extralen, शून्य,
				       UAC_FORMAT_TYPE);
	अगर (!ashd || ashd->bLength < 7 ||
	    !fmtd || fmtd->bLength < 8)
		वापस -ENODEV;

	वापस create_standard_audio_quirk(chip, अगरace, driver, शून्य);
पूर्ण

अटल पूर्णांक create_yamaha_midi_quirk(काष्ठा snd_usb_audio *chip,
				    काष्ठा usb_पूर्णांकerface *अगरace,
				    काष्ठा usb_driver *driver,
				    काष्ठा usb_host_पूर्णांकerface *alts)
अणु
	अटल स्थिर काष्ठा snd_usb_audio_quirk yamaha_midi_quirk = अणु
		.type = QUIRK_MIDI_YAMAHA
	पूर्ण;
	काष्ठा usb_midi_in_jack_descriptor *injd;
	काष्ठा usb_midi_out_jack_descriptor *outjd;

	/* must have some valid jack descriptors */
	injd = snd_usb_find_csपूर्णांक_desc(alts->extra, alts->extralen,
				       शून्य, USB_MS_MIDI_IN_JACK);
	outjd = snd_usb_find_csपूर्णांक_desc(alts->extra, alts->extralen,
					शून्य, USB_MS_MIDI_OUT_JACK);
	अगर (!injd && !outjd)
		वापस -ENODEV;
	अगर ((injd && !snd_usb_validate_midi_desc(injd)) ||
	    (outjd && !snd_usb_validate_midi_desc(outjd)))
		वापस -ENODEV;
	अगर (injd && (injd->bLength < 5 ||
		     (injd->bJackType != USB_MS_EMBEDDED &&
		      injd->bJackType != USB_MS_EXTERNAL)))
		वापस -ENODEV;
	अगर (outjd && (outjd->bLength < 6 ||
		      (outjd->bJackType != USB_MS_EMBEDDED &&
		       outjd->bJackType != USB_MS_EXTERNAL)))
		वापस -ENODEV;
	वापस create_any_midi_quirk(chip, अगरace, driver, &yamaha_midi_quirk);
पूर्ण

अटल पूर्णांक create_roland_midi_quirk(काष्ठा snd_usb_audio *chip,
				    काष्ठा usb_पूर्णांकerface *अगरace,
				    काष्ठा usb_driver *driver,
				    काष्ठा usb_host_पूर्णांकerface *alts)
अणु
	अटल स्थिर काष्ठा snd_usb_audio_quirk roland_midi_quirk = अणु
		.type = QUIRK_MIDI_ROLAND
	पूर्ण;
	u8 *roland_desc = शून्य;

	/* might have a venकरोr-specअगरic descriptor <06 24 F1 02 ...> */
	क्रम (;;) अणु
		roland_desc = snd_usb_find_csपूर्णांक_desc(alts->extra,
						      alts->extralen,
						      roland_desc, 0xf1);
		अगर (!roland_desc)
			वापस -ENODEV;
		अगर (roland_desc[0] < 6 || roland_desc[3] != 2)
			जारी;
		वापस create_any_midi_quirk(chip, अगरace, driver,
					     &roland_midi_quirk);
	पूर्ण
पूर्ण

अटल पूर्णांक create_std_midi_quirk(काष्ठा snd_usb_audio *chip,
				 काष्ठा usb_पूर्णांकerface *अगरace,
				 काष्ठा usb_driver *driver,
				 काष्ठा usb_host_पूर्णांकerface *alts)
अणु
	काष्ठा usb_ms_header_descriptor *mshd;
	काष्ठा usb_ms_endpoपूर्णांक_descriptor *msepd;

	/* must have the MIDIStreaming पूर्णांकerface header descriptor*/
	mshd = (काष्ठा usb_ms_header_descriptor *)alts->extra;
	अगर (alts->extralen < 7 ||
	    mshd->bLength < 7 ||
	    mshd->bDescriptorType != USB_DT_CS_INTERFACE ||
	    mshd->bDescriptorSubtype != USB_MS_HEADER)
		वापस -ENODEV;
	/* must have the MIDIStreaming endpoपूर्णांक descriptor*/
	msepd = (काष्ठा usb_ms_endpoपूर्णांक_descriptor *)alts->endpoपूर्णांक[0].extra;
	अगर (alts->endpoपूर्णांक[0].extralen < 4 ||
	    msepd->bLength < 4 ||
	    msepd->bDescriptorType != USB_DT_CS_ENDPOINT ||
	    msepd->bDescriptorSubtype != UAC_MS_GENERAL ||
	    msepd->bNumEmbMIDIJack < 1 ||
	    msepd->bNumEmbMIDIJack > 16)
		वापस -ENODEV;

	वापस create_any_midi_quirk(chip, अगरace, driver, शून्य);
पूर्ण

अटल पूर्णांक create_स्वतः_midi_quirk(काष्ठा snd_usb_audio *chip,
				  काष्ठा usb_पूर्णांकerface *अगरace,
				  काष्ठा usb_driver *driver)
अणु
	काष्ठा usb_host_पूर्णांकerface *alts;
	काष्ठा usb_पूर्णांकerface_descriptor *altsd;
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;
	पूर्णांक err;

	alts = &अगरace->altsetting[0];
	altsd = get_अगरace_desc(alts);

	/* must have at least one bulk/पूर्णांकerrupt endpoपूर्णांक क्रम streaming */
	अगर (altsd->bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;
	epd = get_endpoपूर्णांक(alts, 0);
	अगर (!usb_endpoपूर्णांक_xfer_bulk(epd) &&
	    !usb_endpoपूर्णांक_xfer_पूर्णांक(epd))
		वापस -ENODEV;

	चयन (USB_ID_VENDOR(chip->usb_id)) अणु
	हाल 0x0499: /* Yamaha */
		err = create_yamaha_midi_quirk(chip, अगरace, driver, alts);
		अगर (err != -ENODEV)
			वापस err;
		अवरोध;
	हाल 0x0582: /* Roland */
		err = create_roland_midi_quirk(chip, अगरace, driver, alts);
		अगर (err != -ENODEV)
			वापस err;
		अवरोध;
	पूर्ण

	वापस create_std_midi_quirk(chip, अगरace, driver, alts);
पूर्ण

अटल पूर्णांक create_स्वतःdetect_quirk(काष्ठा snd_usb_audio *chip,
				   काष्ठा usb_पूर्णांकerface *अगरace,
				   काष्ठा usb_driver *driver)
अणु
	पूर्णांक err;

	err = create_स्वतः_pcm_quirk(chip, अगरace, driver);
	अगर (err == -ENODEV)
		err = create_स्वतः_midi_quirk(chip, अगरace, driver);
	वापस err;
पूर्ण

अटल पूर्णांक create_स्वतःdetect_quirks(काष्ठा snd_usb_audio *chip,
				    काष्ठा usb_पूर्णांकerface *अगरace,
				    काष्ठा usb_driver *driver,
				    स्थिर काष्ठा snd_usb_audio_quirk *quirk)
अणु
	पूर्णांक probed_अगरnum = get_अगरace_desc(अगरace->altsetting)->bInterfaceNumber;
	पूर्णांक अगरcount, अगरnum, err;

	err = create_स्वतःdetect_quirk(chip, अगरace, driver);
	अगर (err < 0)
		वापस err;

	/*
	 * ALSA PCM playback/capture devices cannot be रेजिस्टरed in two steps,
	 * so we have to claim the other corresponding पूर्णांकerface here.
	 */
	अगरcount = chip->dev->actconfig->desc.bNumInterfaces;
	क्रम (अगरnum = 0; अगरnum < अगरcount; अगरnum++) अणु
		अगर (अगरnum == probed_अगरnum || quirk->अगरnum >= 0)
			जारी;
		अगरace = usb_अगरnum_to_अगर(chip->dev, अगरnum);
		अगर (!अगरace ||
		    usb_पूर्णांकerface_claimed(अगरace) ||
		    get_अगरace_desc(अगरace->altsetting)->bInterfaceClass !=
							USB_CLASS_VENDOR_SPEC)
			जारी;

		err = create_स्वतःdetect_quirk(chip, अगरace, driver);
		अगर (err >= 0) अणु
			err = usb_driver_claim_पूर्णांकerface(driver, अगरace,
							 USB_AUDIO_IFACE_UNUSED);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Create a stream क्रम an Edirol UA-700/UA-25/UA-4FX पूर्णांकerface.  
 * The only way to detect the sample rate is by looking at wMaxPacketSize.
 */
अटल पूर्णांक create_uaxx_quirk(काष्ठा snd_usb_audio *chip,
			     काष्ठा usb_पूर्णांकerface *अगरace,
			     काष्ठा usb_driver *driver,
			     स्थिर काष्ठा snd_usb_audio_quirk *quirk)
अणु
	अटल स्थिर काष्ठा audioक्रमmat ua_क्रमmat = अणु
		.क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE,
		.channels = 2,
		.fmt_type = UAC_FORMAT_TYPE_I,
		.altsetting = 1,
		.altset_idx = 1,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
	पूर्ण;
	काष्ठा usb_host_पूर्णांकerface *alts;
	काष्ठा usb_पूर्णांकerface_descriptor *altsd;
	काष्ठा audioक्रमmat *fp;
	पूर्णांक err;

	/* both PCM and MIDI पूर्णांकerfaces have 2 or more altsettings */
	अगर (अगरace->num_altsetting < 2)
		वापस -ENXIO;
	alts = &अगरace->altsetting[1];
	altsd = get_अगरace_desc(alts);

	अगर (altsd->bNumEndpoपूर्णांकs == 2) अणु
		अटल स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info ua700_ep = अणु
			.out_cables = 0x0003,
			.in_cables  = 0x0003
		पूर्ण;
		अटल स्थिर काष्ठा snd_usb_audio_quirk ua700_quirk = अणु
			.type = QUIRK_MIDI_FIXED_ENDPOINT,
			.data = &ua700_ep
		पूर्ण;
		अटल स्थिर काष्ठा snd_usb_midi_endpoपूर्णांक_info uaxx_ep = अणु
			.out_cables = 0x0001,
			.in_cables  = 0x0001
		पूर्ण;
		अटल स्थिर काष्ठा snd_usb_audio_quirk uaxx_quirk = अणु
			.type = QUIRK_MIDI_FIXED_ENDPOINT,
			.data = &uaxx_ep
		पूर्ण;
		स्थिर काष्ठा snd_usb_audio_quirk *quirk =
			chip->usb_id == USB_ID(0x0582, 0x002b)
			? &ua700_quirk : &uaxx_quirk;
		वापस __snd_usbmidi_create(chip->card, अगरace,
					  &chip->midi_list, quirk,
					  chip->usb_id);
	पूर्ण

	अगर (altsd->bNumEndpoपूर्णांकs != 1)
		वापस -ENXIO;

	fp = kmemdup(&ua_क्रमmat, माप(*fp), GFP_KERNEL);
	अगर (!fp)
		वापस -ENOMEM;

	fp->अगरace = altsd->bInterfaceNumber;
	fp->endpoपूर्णांक = get_endpoपूर्णांक(alts, 0)->bEndpoपूर्णांकAddress;
	fp->ep_attr = get_endpoपूर्णांक(alts, 0)->bmAttributes;
	fp->dataपूर्णांकerval = 0;
	fp->maxpacksize = le16_to_cpu(get_endpoपूर्णांक(alts, 0)->wMaxPacketSize);
	INIT_LIST_HEAD(&fp->list);

	चयन (fp->maxpacksize) अणु
	हाल 0x120:
		fp->rate_max = fp->rate_min = 44100;
		अवरोध;
	हाल 0x138:
	हाल 0x140:
		fp->rate_max = fp->rate_min = 48000;
		अवरोध;
	हाल 0x258:
	हाल 0x260:
		fp->rate_max = fp->rate_min = 96000;
		अवरोध;
	शेष:
		usb_audio_err(chip, "unknown sample rate\n");
		kमुक्त(fp);
		वापस -ENXIO;
	पूर्ण

	err = add_audio_stream_from_fixed_fmt(chip, fp);
	अगर (err < 0) अणु
		list_del(&fp->list); /* unlink क्रम aव्योमing द्विगुन-मुक्त */
		kमुक्त(fp);
		वापस err;
	पूर्ण
	usb_set_पूर्णांकerface(chip->dev, fp->अगरace, 0);
	वापस 0;
पूर्ण

/*
 * Create a standard mixer क्रम the specअगरied पूर्णांकerface.
 */
अटल पूर्णांक create_standard_mixer_quirk(काष्ठा snd_usb_audio *chip,
				       काष्ठा usb_पूर्णांकerface *अगरace,
				       काष्ठा usb_driver *driver,
				       स्थिर काष्ठा snd_usb_audio_quirk *quirk)
अणु
	अगर (quirk->अगरnum < 0)
		वापस 0;

	वापस snd_usb_create_mixer(chip, quirk->अगरnum, 0);
पूर्ण

अटल पूर्णांक setup_disable_स्वतःsuspend(काष्ठा snd_usb_audio *chip,
				       काष्ठा usb_पूर्णांकerface *अगरace,
				       काष्ठा usb_driver *driver,
				       स्थिर काष्ठा snd_usb_audio_quirk *quirk)
अणु
	usb_disable_स्वतःsuspend(पूर्णांकerface_to_usbdev(अगरace));
	वापस 1;	/* Continue with creating streams and mixer */
पूर्ण

/*
 * audio-पूर्णांकerface quirks
 *
 * वापसs zero अगर no standard audio/MIDI parsing is needed.
 * वापसs a positive value अगर standard audio/midi पूर्णांकerfaces are parsed
 * after this.
 * वापसs a negative value at error.
 */
पूर्णांक snd_usb_create_quirk(काष्ठा snd_usb_audio *chip,
			 काष्ठा usb_पूर्णांकerface *अगरace,
			 काष्ठा usb_driver *driver,
			 स्थिर काष्ठा snd_usb_audio_quirk *quirk)
अणु
	प्रकार पूर्णांक (*quirk_func_t)(काष्ठा snd_usb_audio *,
				    काष्ठा usb_पूर्णांकerface *,
				    काष्ठा usb_driver *,
				    स्थिर काष्ठा snd_usb_audio_quirk *);
	अटल स्थिर quirk_func_t quirk_funcs[] = अणु
		[QUIRK_IGNORE_INTERFACE] = ignore_पूर्णांकerface_quirk,
		[QUIRK_COMPOSITE] = create_composite_quirk,
		[QUIRK_AUTODETECT] = create_स्वतःdetect_quirks,
		[QUIRK_MIDI_STANDARD_INTERFACE] = create_any_midi_quirk,
		[QUIRK_MIDI_FIXED_ENDPOINT] = create_any_midi_quirk,
		[QUIRK_MIDI_YAMAHA] = create_any_midi_quirk,
		[QUIRK_MIDI_ROLAND] = create_any_midi_quirk,
		[QUIRK_MIDI_MIDIMAN] = create_any_midi_quirk,
		[QUIRK_MIDI_NOVATION] = create_any_midi_quirk,
		[QUIRK_MIDI_RAW_BYTES] = create_any_midi_quirk,
		[QUIRK_MIDI_EMAGIC] = create_any_midi_quirk,
		[QUIRK_MIDI_CME] = create_any_midi_quirk,
		[QUIRK_MIDI_AKAI] = create_any_midi_quirk,
		[QUIRK_MIDI_FTDI] = create_any_midi_quirk,
		[QUIRK_MIDI_CH345] = create_any_midi_quirk,
		[QUIRK_AUDIO_STANDARD_INTERFACE] = create_standard_audio_quirk,
		[QUIRK_AUDIO_FIXED_ENDPOINT] = create_fixed_stream_quirk,
		[QUIRK_AUDIO_EसूचीOL_UAXX] = create_uaxx_quirk,
		[QUIRK_AUDIO_ALIGN_TRANSFER] = create_align_transfer_quirk,
		[QUIRK_AUDIO_STANDARD_MIXER] = create_standard_mixer_quirk,
		[QUIRK_SETUP_DISABLE_AUTOSUSPEND] = setup_disable_स्वतःsuspend,
	पूर्ण;

	अगर (quirk->type < QUIRK_TYPE_COUNT) अणु
		वापस quirk_funcs[quirk->type](chip, अगरace, driver, quirk);
	पूर्ण अन्यथा अणु
		usb_audio_err(chip, "invalid quirk type %d\n", quirk->type);
		वापस -ENXIO;
	पूर्ण
पूर्ण

/*
 * boot quirks
 */

#घोषणा EXTIGY_FIRMWARE_SIZE_OLD 794
#घोषणा EXTIGY_FIRMWARE_SIZE_NEW 483

अटल पूर्णांक snd_usb_extigy_boot_quirk(काष्ठा usb_device *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_host_config *config = dev->actconfig;
	पूर्णांक err;

	अगर (le16_to_cpu(get_cfg_desc(config)->wTotalLength) == EXTIGY_FIRMWARE_SIZE_OLD ||
	    le16_to_cpu(get_cfg_desc(config)->wTotalLength) == EXTIGY_FIRMWARE_SIZE_NEW) अणु
		dev_dbg(&dev->dev, "sending Extigy boot sequence...\n");
		/* Send message to क्रमce it to reconnect with full पूर्णांकerface. */
		err = snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev,0),
				      0x10, 0x43, 0x0001, 0x000a, शून्य, 0);
		अगर (err < 0)
			dev_dbg(&dev->dev, "error sending boot message: %d\n", err);
		err = usb_get_descriptor(dev, USB_DT_DEVICE, 0,
				&dev->descriptor, माप(dev->descriptor));
		config = dev->actconfig;
		अगर (err < 0)
			dev_dbg(&dev->dev, "error usb_get_descriptor: %d\n", err);
		err = usb_reset_configuration(dev);
		अगर (err < 0)
			dev_dbg(&dev->dev, "error usb_reset_configuration: %d\n", err);
		dev_dbg(&dev->dev, "extigy_boot: new boot length = %d\n",
			    le16_to_cpu(get_cfg_desc(config)->wTotalLength));
		वापस -ENODEV; /* quit this anyway */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_usb_audigy2nx_boot_quirk(काष्ठा usb_device *dev)
अणु
	u8 buf = 1;

	snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0), 0x2a,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_OTHER,
			0, 0, &buf, 1);
	अगर (buf == 0) अणु
		snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0), 0x29,
				USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
				1, 2000, शून्य, 0);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_usb_fasttrackpro_boot_quirk(काष्ठा usb_device *dev)
अणु
	पूर्णांक err;

	अगर (dev->actconfig->desc.bConfigurationValue == 1) अणु
		dev_info(&dev->dev,
			   "Fast Track Pro switching to config #2\n");
		/* This function has to be available by the usb core module.
		 * अगर it is not avialable the boot quirk has to be left out
		 * and the configuration has to be set by udev or hotplug
		 * rules
		 */
		err = usb_driver_set_configuration(dev, 2);
		अगर (err < 0)
			dev_dbg(&dev->dev,
				"error usb_driver_set_configuration: %d\n",
				err);
		/* Always वापस an error, so that we stop creating a device
		   that will just be destroyed and recreated with a new
		   configuration */
		वापस -ENODEV;
	पूर्ण अन्यथा
		dev_info(&dev->dev, "Fast Track Pro config OK\n");

	वापस 0;
पूर्ण

/*
 * C-Media CM106/CM106+ have four 16-bit पूर्णांकernal रेजिस्टरs that are nicely
 * करोcumented in the device's data sheet.
 */
अटल पूर्णांक snd_usb_cm106_ग_लिखो_पूर्णांक_reg(काष्ठा usb_device *dev, पूर्णांक reg, u16 value)
अणु
	u8 buf[4];
	buf[0] = 0x20;
	buf[1] = value & 0xff;
	buf[2] = (value >> 8) & 0xff;
	buf[3] = reg;
	वापस snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0), USB_REQ_SET_CONFIGURATION,
			       USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_ENDPOINT,
			       0, 0, &buf, 4);
पूर्ण

अटल पूर्णांक snd_usb_cm106_boot_quirk(काष्ठा usb_device *dev)
अणु
	/*
	 * Enable line-out driver mode, set headphone source to front
	 * channels, enable stereo mic.
	 */
	वापस snd_usb_cm106_ग_लिखो_पूर्णांक_reg(dev, 2, 0x8004);
पूर्ण

/*
 * CM6206 रेजिस्टरs from the CM6206 datasheet rev 2.1
 */
#घोषणा CM6206_REG0_DMA_MASTER BIT(15)
#घोषणा CM6206_REG0_SPDIFO_RATE_48K (2 << 12)
#घोषणा CM6206_REG0_SPDIFO_RATE_96K (7 << 12)
/* Bit 4 thru 11 is the S/PDIF category code */
#घोषणा CM6206_REG0_SPDIFO_CAT_CODE_GENERAL (0 << 4)
#घोषणा CM6206_REG0_SPDIFO_EMPHASIS_CD BIT(3)
#घोषणा CM6206_REG0_SPDIFO_COPYRIGHT_NA BIT(2)
#घोषणा CM6206_REG0_SPDIFO_NON_AUDIO BIT(1)
#घोषणा CM6206_REG0_SPDIFO_PRO_FORMAT BIT(0)

#घोषणा CM6206_REG1_TEST_SEL_CLK BIT(14)
#घोषणा CM6206_REG1_PLLBIN_EN BIT(13)
#घोषणा CM6206_REG1_SOFT_MUTE_EN BIT(12)
#घोषणा CM6206_REG1_GPIO4_OUT BIT(11)
#घोषणा CM6206_REG1_GPIO4_OE BIT(10)
#घोषणा CM6206_REG1_GPIO3_OUT BIT(9)
#घोषणा CM6206_REG1_GPIO3_OE BIT(8)
#घोषणा CM6206_REG1_GPIO2_OUT BIT(7)
#घोषणा CM6206_REG1_GPIO2_OE BIT(6)
#घोषणा CM6206_REG1_GPIO1_OUT BIT(5)
#घोषणा CM6206_REG1_GPIO1_OE BIT(4)
#घोषणा CM6206_REG1_SPDIFO_INVALID BIT(3)
#घोषणा CM6206_REG1_SPDIF_LOOP_EN BIT(2)
#घोषणा CM6206_REG1_SPDIFO_DIS BIT(1)
#घोषणा CM6206_REG1_SPDIFI_MIX BIT(0)

#घोषणा CM6206_REG2_DRIVER_ON BIT(15)
#घोषणा CM6206_REG2_HEADP_SEL_SIDE_CHANNELS (0 << 13)
#घोषणा CM6206_REG2_HEADP_SEL_SURROUND_CHANNELS (1 << 13)
#घोषणा CM6206_REG2_HEADP_SEL_CENTER_SUBW (2 << 13)
#घोषणा CM6206_REG2_HEADP_SEL_FRONT_CHANNELS (3 << 13)
#घोषणा CM6206_REG2_MUTE_HEADPHONE_RIGHT BIT(12)
#घोषणा CM6206_REG2_MUTE_HEADPHONE_LEFT BIT(11)
#घोषणा CM6206_REG2_MUTE_REAR_SURROUND_RIGHT BIT(10)
#घोषणा CM6206_REG2_MUTE_REAR_SURROUND_LEFT BIT(9)
#घोषणा CM6206_REG2_MUTE_SIDE_SURROUND_RIGHT BIT(8)
#घोषणा CM6206_REG2_MUTE_SIDE_SURROUND_LEFT BIT(7)
#घोषणा CM6206_REG2_MUTE_SUBWOOFER BIT(6)
#घोषणा CM6206_REG2_MUTE_CENTER BIT(5)
#घोषणा CM6206_REG2_MUTE_RIGHT_FRONT BIT(3)
#घोषणा CM6206_REG2_MUTE_LEFT_FRONT BIT(3)
#घोषणा CM6206_REG2_EN_BTL BIT(2)
#घोषणा CM6206_REG2_MCUCLKSEL_1_5_MHZ (0)
#घोषणा CM6206_REG2_MCUCLKSEL_3_MHZ (1)
#घोषणा CM6206_REG2_MCUCLKSEL_6_MHZ (2)
#घोषणा CM6206_REG2_MCUCLKSEL_12_MHZ (3)

/* Bit 11..13 sets the sensitivity to FLY tuner volume control VP/VD संकेत */
#घोषणा CM6206_REG3_FLYSPEED_DEFAULT (2 << 11)
#घोषणा CM6206_REG3_VRAP25EN BIT(10)
#घोषणा CM6206_REG3_MSEL1 BIT(9)
#घोषणा CM6206_REG3_SPDIFI_RATE_44_1K BIT(0 << 7)
#घोषणा CM6206_REG3_SPDIFI_RATE_48K BIT(2 << 7)
#घोषणा CM6206_REG3_SPDIFI_RATE_32K BIT(3 << 7)
#घोषणा CM6206_REG3_PINSEL BIT(6)
#घोषणा CM6206_REG3_FOE BIT(5)
#घोषणा CM6206_REG3_ROE BIT(4)
#घोषणा CM6206_REG3_CBOE BIT(3)
#घोषणा CM6206_REG3_LOSE BIT(2)
#घोषणा CM6206_REG3_HPOE BIT(1)
#घोषणा CM6206_REG3_SPDIFI_CANREC BIT(0)

#घोषणा CM6206_REG5_DA_RSTN BIT(13)
#घोषणा CM6206_REG5_AD_RSTN BIT(12)
#घोषणा CM6206_REG5_SPDIFO_AD2SPDO BIT(12)
#घोषणा CM6206_REG5_SPDIFO_SEL_FRONT (0 << 9)
#घोषणा CM6206_REG5_SPDIFO_SEL_SIDE_SUR (1 << 9)
#घोषणा CM6206_REG5_SPDIFO_SEL_CEN_LFE (2 << 9)
#घोषणा CM6206_REG5_SPDIFO_SEL_REAR_SUR (3 << 9)
#घोषणा CM6206_REG5_CODECM BIT(8)
#घोषणा CM6206_REG5_EN_HPF BIT(7)
#घोषणा CM6206_REG5_T_SEL_DSDA4 BIT(6)
#घोषणा CM6206_REG5_T_SEL_DSDA3 BIT(5)
#घोषणा CM6206_REG5_T_SEL_DSDA2 BIT(4)
#घोषणा CM6206_REG5_T_SEL_DSDA1 BIT(3)
#घोषणा CM6206_REG5_T_SEL_DSDAD_NORMAL 0
#घोषणा CM6206_REG5_T_SEL_DSDAD_FRONT 4
#घोषणा CM6206_REG5_T_SEL_DSDAD_S_SURROUND 5
#घोषणा CM6206_REG5_T_SEL_DSDAD_CEN_LFE 6
#घोषणा CM6206_REG5_T_SEL_DSDAD_R_SURROUND 7

अटल पूर्णांक snd_usb_cm6206_boot_quirk(काष्ठा usb_device *dev)
अणु
	पूर्णांक err  = 0, reg;
	पूर्णांक val[] = अणु
		/*
		 * Values here are chosen based on snअगरfing USB traffic
		 * under Winकरोws.
		 *
		 * REG0: DAC is master, sample rate 48kHz, no copyright
		 */
		CM6206_REG0_SPDIFO_RATE_48K |
		CM6206_REG0_SPDIFO_COPYRIGHT_NA,
		/*
		 * REG1: PLL binary search enable, soft mute enable.
		 */
		CM6206_REG1_PLLBIN_EN |
		CM6206_REG1_SOFT_MUTE_EN,
		/*
		 * REG2: enable output drivers,
		 * select front channels to the headphone output,
		 * then mute the headphone channels, run the MCU
		 * at 1.5 MHz.
		 */
		CM6206_REG2_DRIVER_ON |
		CM6206_REG2_HEADP_SEL_FRONT_CHANNELS |
		CM6206_REG2_MUTE_HEADPHONE_RIGHT |
		CM6206_REG2_MUTE_HEADPHONE_LEFT,
		/*
		 * REG3: शेष flyspeed, set 2.5V mic bias
		 * enable all line out ports and enable SPDIF
		 */
		CM6206_REG3_FLYSPEED_DEFAULT |
		CM6206_REG3_VRAP25EN |
		CM6206_REG3_FOE |
		CM6206_REG3_ROE |
		CM6206_REG3_CBOE |
		CM6206_REG3_LOSE |
		CM6206_REG3_HPOE |
		CM6206_REG3_SPDIFI_CANREC,
		/* REG4 is just a bunch of GPIO lines */
		0x0000,
		/* REG5: de-निश्चित AD/DA reset संकेतs */
		CM6206_REG5_DA_RSTN |
		CM6206_REG5_AD_RSTN पूर्ण;

	क्रम (reg = 0; reg < ARRAY_SIZE(val); reg++) अणु
		err = snd_usb_cm106_ग_लिखो_पूर्णांक_reg(dev, reg, val[reg]);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण

/* quirk क्रम Plantronics GameCom 780 with CM6302 chip */
अटल पूर्णांक snd_usb_gamecon780_boot_quirk(काष्ठा usb_device *dev)
अणु
	/* set the initial volume and करोn't change; other values are either
	 * too loud or silent due to firmware bug (bko#65251)
	 */
	u8 buf[2] = अणु 0x74, 0xe3 पूर्ण;
	वापस snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0), UAC_SET_CUR,
			USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_OUT,
			UAC_FU_VOLUME << 8, 9 << 8, buf, 2);
पूर्ण

/*
 * Novation Twitch DJ controller
 * Focusrite Novation Saffire 6 USB audio card
 */
अटल पूर्णांक snd_usb_novation_boot_quirk(काष्ठा usb_device *dev)
अणु
	/* preemptively set up the device because otherwise the
	 * raw MIDI endpoपूर्णांकs are not active */
	usb_set_पूर्णांकerface(dev, 0, 1);
	वापस 0;
पूर्ण

/*
 * This call will put the synth in "USB send" mode, i.e it will send MIDI
 * messages through USB (this is disabled at startup). The synth will
 * acknowledge by sending a sysex on endpoपूर्णांक 0x85 and by displaying a USB
 * sign on its LCD. Values here are chosen based on snअगरfing USB traffic
 * under Winकरोws.
 */
अटल पूर्णांक snd_usb_accessmusic_boot_quirk(काष्ठा usb_device *dev)
अणु
	पूर्णांक err, actual_length;
	/* "midi send" enable */
	अटल स्थिर u8 seq[] = अणु 0x4e, 0x73, 0x52, 0x01 पूर्ण;
	व्योम *buf;

	अगर (usb_pipe_type_check(dev, usb_sndपूर्णांकpipe(dev, 0x05)))
		वापस -EINVAL;
	buf = kmemdup(seq, ARRAY_SIZE(seq), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	err = usb_पूर्णांकerrupt_msg(dev, usb_sndपूर्णांकpipe(dev, 0x05), buf,
			ARRAY_SIZE(seq), &actual_length, 1000);
	kमुक्त(buf);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

/*
 * Some sound cards from Native Instruments are in fact compliant to the USB
 * audio standard of version 2 and other approved USB standards, even though
 * they come up as venकरोr-specअगरic device when first connected.
 *
 * However, they can be told to come up with a new set of descriptors
 * upon their next क्रमागतeration, and the पूर्णांकerfaces announced by the new
 * descriptors will then be handled by the kernel's class drivers. As the
 * product ID will also change, no further checks are required.
 */

अटल पूर्णांक snd_usb_nativeinstruments_boot_quirk(काष्ठा usb_device *dev)
अणु
	पूर्णांक ret;

	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
				  0xaf, USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				  1, 0, शून्य, 0, 1000);

	अगर (ret < 0)
		वापस ret;

	usb_reset_device(dev);

	/* वापस -EAGAIN, so the creation of an audio पूर्णांकerface क्रम this
	 * temporary device is पातed. The device will reconnect with a
	 * new product ID */
	वापस -EAGAIN;
पूर्ण

अटल व्योम mbox2_setup_48_24_magic(काष्ठा usb_device *dev)
अणु
	u8 srate[3];
	u8 temp[12];

	/* Choose 48000Hz permanently */
	srate[0] = 0x80;
	srate[1] = 0xbb;
	srate[2] = 0x00;

	/* Send the magic! */
	snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0),
		0x01, 0x22, 0x0100, 0x0085, &temp, 0x0003);
	snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0),
		0x81, 0xa2, 0x0100, 0x0085, &srate, 0x0003);
	snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0),
		0x81, 0xa2, 0x0100, 0x0086, &srate, 0x0003);
	snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0),
		0x81, 0xa2, 0x0100, 0x0003, &srate, 0x0003);
	वापस;
पूर्ण

/* Digidesign Mbox 2 needs to load firmware onboard
 * and driver must रुको a few seconds क्रम initialisation.
 */

#घोषणा MBOX2_FIRMWARE_SIZE    646
#घोषणा MBOX2_BOOT_LOADING     0x01 /* Hard coded पूर्णांकo the device */
#घोषणा MBOX2_BOOT_READY       0x02 /* Hard coded पूर्णांकo the device */

अटल पूर्णांक snd_usb_mbox2_boot_quirk(काष्ठा usb_device *dev)
अणु
	काष्ठा usb_host_config *config = dev->actconfig;
	पूर्णांक err;
	u8 bootresponse[0x12];
	पूर्णांक fwsize;
	पूर्णांक count;

	fwsize = le16_to_cpu(get_cfg_desc(config)->wTotalLength);

	अगर (fwsize != MBOX2_FIRMWARE_SIZE) अणु
		dev_err(&dev->dev, "Invalid firmware size=%d.\n", fwsize);
		वापस -ENODEV;
	पूर्ण

	dev_dbg(&dev->dev, "Sending Digidesign Mbox 2 boot sequence...\n");

	count = 0;
	bootresponse[0] = MBOX2_BOOT_LOADING;
	जबतक ((bootresponse[0] == MBOX2_BOOT_LOADING) && (count < 10)) अणु
		msleep(500); /* 0.5 second delay */
		snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0),
			/* Control magic - load onboard firmware */
			0x85, 0xc0, 0x0001, 0x0000, &bootresponse, 0x0012);
		अगर (bootresponse[0] == MBOX2_BOOT_READY)
			अवरोध;
		dev_dbg(&dev->dev, "device not ready, resending boot sequence...\n");
		count++;
	पूर्ण

	अगर (bootresponse[0] != MBOX2_BOOT_READY) अणु
		dev_err(&dev->dev, "Unknown bootresponse=%d, or timed out, ignoring device.\n", bootresponse[0]);
		वापस -ENODEV;
	पूर्ण

	dev_dbg(&dev->dev, "device initialised!\n");

	err = usb_get_descriptor(dev, USB_DT_DEVICE, 0,
		&dev->descriptor, माप(dev->descriptor));
	config = dev->actconfig;
	अगर (err < 0)
		dev_dbg(&dev->dev, "error usb_get_descriptor: %d\n", err);

	err = usb_reset_configuration(dev);
	अगर (err < 0)
		dev_dbg(&dev->dev, "error usb_reset_configuration: %d\n", err);
	dev_dbg(&dev->dev, "mbox2_boot: new boot length = %d\n",
		le16_to_cpu(get_cfg_desc(config)->wTotalLength));

	mbox2_setup_48_24_magic(dev);

	dev_info(&dev->dev, "Digidesign Mbox 2: 24bit 48kHz");

	वापस 0; /* Successful boot */
पूर्ण

अटल पूर्णांक snd_usb_axefx3_boot_quirk(काष्ठा usb_device *dev)
अणु
	पूर्णांक err;

	dev_dbg(&dev->dev, "Waiting for Axe-Fx III to boot up...\n");

	/* If the Axe-Fx III has not fully booted, it will समयout when trying
	 * to enable the audio streaming पूर्णांकerface. A more generous समयout is
	 * used here to detect when the Axe-Fx III has finished booting as the
	 * set पूर्णांकerface message will be acked once it has
	 */
	err = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
				USB_REQ_SET_INTERFACE, USB_RECIP_INTERFACE,
				1, 1, शून्य, 0, 120000);
	अगर (err < 0) अणु
		dev_err(&dev->dev,
			"failed waiting for Axe-Fx III to boot: %d\n", err);
		वापस err;
	पूर्ण

	dev_dbg(&dev->dev, "Axe-Fx III is now ready\n");

	err = usb_set_पूर्णांकerface(dev, 1, 0);
	अगर (err < 0)
		dev_dbg(&dev->dev,
			"error stopping Axe-Fx III interface: %d\n", err);

	वापस 0;
पूर्ण


#घोषणा MICROBOOK_BUF_SIZE 128

अटल पूर्णांक snd_usb_motu_microbookii_communicate(काष्ठा usb_device *dev, u8 *buf,
						पूर्णांक buf_size, पूर्णांक *length)
अणु
	पूर्णांक err, actual_length;

	अगर (usb_pipe_type_check(dev, usb_sndपूर्णांकpipe(dev, 0x01)))
		वापस -EINVAL;
	err = usb_पूर्णांकerrupt_msg(dev, usb_sndपूर्णांकpipe(dev, 0x01), buf, *length,
				&actual_length, 1000);
	अगर (err < 0)
		वापस err;

	prपूर्णांक_hex_dump(KERN_DEBUG, "MicroBookII snd: ", DUMP_PREFIX_NONE, 16, 1,
		       buf, actual_length, false);

	स_रखो(buf, 0, buf_size);

	अगर (usb_pipe_type_check(dev, usb_rcvपूर्णांकpipe(dev, 0x82)))
		वापस -EINVAL;
	err = usb_पूर्णांकerrupt_msg(dev, usb_rcvपूर्णांकpipe(dev, 0x82), buf, buf_size,
				&actual_length, 1000);
	अगर (err < 0)
		वापस err;

	prपूर्णांक_hex_dump(KERN_DEBUG, "MicroBookII rcv: ", DUMP_PREFIX_NONE, 16, 1,
		       buf, actual_length, false);

	*length = actual_length;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_usb_motu_microbookii_boot_quirk(काष्ठा usb_device *dev)
अणु
	पूर्णांक err, actual_length, poll_attempts = 0;
	अटल स्थिर u8 set_samplerate_seq[] = अणु 0x00, 0x00, 0x00, 0x00,
						 0x00, 0x00, 0x0b, 0x14,
						 0x00, 0x00, 0x00, 0x01 पूर्ण;
	अटल स्थिर u8 poll_पढ़ोy_seq[] = अणु 0x00, 0x04, 0x00, 0x00,
					     0x00, 0x00, 0x0b, 0x18 पूर्ण;
	u8 *buf = kzalloc(MICROBOOK_BUF_SIZE, GFP_KERNEL);

	अगर (!buf)
		वापस -ENOMEM;

	dev_info(&dev->dev, "Waiting for MOTU Microbook II to boot up...\n");

	/* First we tell the device which sample rate to use. */
	स_नकल(buf, set_samplerate_seq, माप(set_samplerate_seq));
	actual_length = माप(set_samplerate_seq);
	err = snd_usb_motu_microbookii_communicate(dev, buf, MICROBOOK_BUF_SIZE,
						   &actual_length);

	अगर (err < 0) अणु
		dev_err(&dev->dev,
			"failed setting the sample rate for Motu MicroBook II: %d\n",
			err);
		जाओ मुक्त_buf;
	पूर्ण

	/* Then we poll every 100 ms until the device inक्रमms of its पढ़ोiness. */
	जबतक (true) अणु
		अगर (++poll_attempts > 100) अणु
			dev_err(&dev->dev,
				"failed booting Motu MicroBook II: timeout\n");
			err = -ENODEV;
			जाओ मुक्त_buf;
		पूर्ण

		स_रखो(buf, 0, MICROBOOK_BUF_SIZE);
		स_नकल(buf, poll_पढ़ोy_seq, माप(poll_पढ़ोy_seq));

		actual_length = माप(poll_पढ़ोy_seq);
		err = snd_usb_motu_microbookii_communicate(
			dev, buf, MICROBOOK_BUF_SIZE, &actual_length);
		अगर (err < 0) अणु
			dev_err(&dev->dev,
				"failed booting Motu MicroBook II: communication error %d\n",
				err);
			जाओ मुक्त_buf;
		पूर्ण

		/* the device संकेतs its पढ़ोiness through a message of the
		 * क्रमm
		 *           XX 06 00 00 00 00 0b 18  00 00 00 01
		 * If the device is not yet पढ़ोy to accept audio data, the
		 * last byte of that sequence is 00.
		 */
		अगर (actual_length == 12 && buf[actual_length - 1] == 1)
			अवरोध;

		msleep(100);
	पूर्ण

	dev_info(&dev->dev, "MOTU MicroBook II ready\n");

मुक्त_buf:
	kमुक्त(buf);
	वापस err;
पूर्ण

अटल पूर्णांक snd_usb_motu_m_series_boot_quirk(काष्ठा usb_device *dev)
अणु
	msleep(2000);

	वापस 0;
पूर्ण

/*
 * Setup quirks
 */
#घोषणा MAUDIO_SET		0x01 /* parse device_setup */
#घोषणा MAUDIO_SET_COMPATIBLE	0x80 /* use only "win-compatible" पूर्णांकerfaces */
#घोषणा MAUDIO_SET_DTS		0x02 /* enable DTS Digital Output */
#घोषणा MAUDIO_SET_96K		0x04 /* 48-96kHz rate अगर set, 8-48kHz otherwise */
#घोषणा MAUDIO_SET_24B		0x08 /* 24bits sample अगर set, 16bits otherwise */
#घोषणा MAUDIO_SET_DI		0x10 /* enable Digital Input */
#घोषणा MAUDIO_SET_MASK		0x1f /* bit mask क्रम setup value */
#घोषणा MAUDIO_SET_24B_48K_DI	 0x19 /* 24bits+48kHz+Digital Input */
#घोषणा MAUDIO_SET_24B_48K_NOTDI 0x09 /* 24bits+48kHz+No Digital Input */
#घोषणा MAUDIO_SET_16B_48K_DI	 0x11 /* 16bits+48kHz+Digital Input */
#घोषणा MAUDIO_SET_16B_48K_NOTDI 0x01 /* 16bits+48kHz+No Digital Input */

अटल पूर्णांक quattro_skip_setting_quirk(काष्ठा snd_usb_audio *chip,
				      पूर्णांक अगरace, पूर्णांक altno)
अणु
	/* Reset ALL अगरaces to 0 altsetting.
	 * Call it क्रम every possible altsetting of every पूर्णांकerface.
	 */
	usb_set_पूर्णांकerface(chip->dev, अगरace, 0);
	अगर (chip->setup & MAUDIO_SET) अणु
		अगर (chip->setup & MAUDIO_SET_COMPATIBLE) अणु
			अगर (अगरace != 1 && अगरace != 2)
				वापस 1; /* skip all पूर्णांकerfaces but 1 and 2 */
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक mask;
			अगर (अगरace == 1 || अगरace == 2)
				वापस 1; /* skip पूर्णांकerfaces 1 and 2 */
			अगर ((chip->setup & MAUDIO_SET_96K) && altno != 1)
				वापस 1; /* skip this altsetting */
			mask = chip->setup & MAUDIO_SET_MASK;
			अगर (mask == MAUDIO_SET_24B_48K_DI && altno != 2)
				वापस 1; /* skip this altsetting */
			अगर (mask == MAUDIO_SET_24B_48K_NOTDI && altno != 3)
				वापस 1; /* skip this altsetting */
			अगर (mask == MAUDIO_SET_16B_48K_NOTDI && altno != 4)
				वापस 1; /* skip this altsetting */
		पूर्ण
	पूर्ण
	usb_audio_dbg(chip,
		    "using altsetting %d for interface %d config %d\n",
		    altno, अगरace, chip->setup);
	वापस 0; /* keep this altsetting */
पूर्ण

अटल पूर्णांक audiophile_skip_setting_quirk(काष्ठा snd_usb_audio *chip,
					 पूर्णांक अगरace,
					 पूर्णांक altno)
अणु
	/* Reset ALL अगरaces to 0 altsetting.
	 * Call it क्रम every possible altsetting of every पूर्णांकerface.
	 */
	usb_set_पूर्णांकerface(chip->dev, अगरace, 0);

	अगर (chip->setup & MAUDIO_SET) अणु
		अचिन्हित पूर्णांक mask;
		अगर ((chip->setup & MAUDIO_SET_DTS) && altno != 6)
			वापस 1; /* skip this altsetting */
		अगर ((chip->setup & MAUDIO_SET_96K) && altno != 1)
			वापस 1; /* skip this altsetting */
		mask = chip->setup & MAUDIO_SET_MASK;
		अगर (mask == MAUDIO_SET_24B_48K_DI && altno != 2)
			वापस 1; /* skip this altsetting */
		अगर (mask == MAUDIO_SET_24B_48K_NOTDI && altno != 3)
			वापस 1; /* skip this altsetting */
		अगर (mask == MAUDIO_SET_16B_48K_DI && altno != 4)
			वापस 1; /* skip this altsetting */
		अगर (mask == MAUDIO_SET_16B_48K_NOTDI && altno != 5)
			वापस 1; /* skip this altsetting */
	पूर्ण

	वापस 0; /* keep this altsetting */
पूर्ण

अटल पूर्णांक fasttrackpro_skip_setting_quirk(काष्ठा snd_usb_audio *chip,
					   पूर्णांक अगरace, पूर्णांक altno)
अणु
	/* Reset ALL अगरaces to 0 altsetting.
	 * Call it क्रम every possible altsetting of every पूर्णांकerface.
	 */
	usb_set_पूर्णांकerface(chip->dev, अगरace, 0);

	/* possible configuration where both inमाला_दो and only one output is
	 *used is not supported by the current setup
	 */
	अगर (chip->setup & (MAUDIO_SET | MAUDIO_SET_24B)) अणु
		अगर (chip->setup & MAUDIO_SET_96K) अणु
			अगर (altno != 3 && altno != 6)
				वापस 1;
		पूर्ण अन्यथा अगर (chip->setup & MAUDIO_SET_DI) अणु
			अगर (अगरace == 4)
				वापस 1; /* no analog input */
			अगर (altno != 2 && altno != 5)
				वापस 1; /* enable only altsets 2 and 5 */
		पूर्ण अन्यथा अणु
			अगर (अगरace == 5)
				वापस 1; /* disable digialt input */
			अगर (altno != 2 && altno != 5)
				वापस 1; /* enalbe only altsets 2 and 5 */
		पूर्ण
	पूर्ण अन्यथा अणु
		/* keep only 16-Bit mode */
		अगर (altno != 1)
			वापस 1;
	पूर्ण

	usb_audio_dbg(chip,
		    "using altsetting %d for interface %d config %d\n",
		    altno, अगरace, chip->setup);
	वापस 0; /* keep this altsetting */
पूर्ण

अटल पूर्णांक s1810c_skip_setting_quirk(काष्ठा snd_usb_audio *chip,
					   पूर्णांक अगरace, पूर्णांक altno)
अणु
	/*
	 * Altno settings:
	 *
	 * Playback (Interface 1):
	 * 1: 6 Analog + 2 S/PDIF
	 * 2: 6 Analog + 2 S/PDIF
	 * 3: 6 Analog
	 *
	 * Capture (Interface 2):
	 * 1: 8 Analog + 2 S/PDIF + 8 ADAT
	 * 2: 8 Analog + 2 S/PDIF + 4 ADAT
	 * 3: 8 Analog
	 */

	/*
	 * I'll leave 2 as the शेष one and
	 * use device_setup to चयन to the
	 * other two.
	 */
	अगर ((chip->setup == 0 || chip->setup > 2) && altno != 2)
		वापस 1;
	अन्यथा अगर (chip->setup == 1 && altno != 1)
		वापस 1;
	अन्यथा अगर (chip->setup == 2 && altno != 3)
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक snd_usb_apply_पूर्णांकerface_quirk(काष्ठा snd_usb_audio *chip,
				  पूर्णांक अगरace,
				  पूर्णांक altno)
अणु
	/* audiophile usb: skip altsets incompatible with device_setup */
	अगर (chip->usb_id == USB_ID(0x0763, 0x2003))
		वापस audiophile_skip_setting_quirk(chip, अगरace, altno);
	/* quattro usb: skip altsets incompatible with device_setup */
	अगर (chip->usb_id == USB_ID(0x0763, 0x2001))
		वापस quattro_skip_setting_quirk(chip, अगरace, altno);
	/* fasttrackpro usb: skip altsets incompatible with device_setup */
	अगर (chip->usb_id == USB_ID(0x0763, 0x2012))
		वापस fasttrackpro_skip_setting_quirk(chip, अगरace, altno);
	/* presonus studio 1810c: skip altsets incompatible with device_setup */
	अगर (chip->usb_id == USB_ID(0x0194f, 0x010c))
		वापस s1810c_skip_setting_quirk(chip, अगरace, altno);


	वापस 0;
पूर्ण

पूर्णांक snd_usb_apply_boot_quirk(काष्ठा usb_device *dev,
			     काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			     स्थिर काष्ठा snd_usb_audio_quirk *quirk,
			     अचिन्हित पूर्णांक id)
अणु
	चयन (id) अणु
	हाल USB_ID(0x041e, 0x3000):
		/* SB Extigy needs special boot-up sequence */
		/* अगर more models come, this will go to the quirk list. */
		वापस snd_usb_extigy_boot_quirk(dev, पूर्णांकf);

	हाल USB_ID(0x041e, 0x3020):
		/* SB Audigy 2 NX needs its own boot-up magic, too */
		वापस snd_usb_audigy2nx_boot_quirk(dev);

	हाल USB_ID(0x10f5, 0x0200):
		/* C-Media CM106 / Turtle Beach Audio Advantage Roadie */
		वापस snd_usb_cm106_boot_quirk(dev);

	हाल USB_ID(0x0d8c, 0x0102):
		/* C-Media CM6206 / CM106-Like Sound Device */
	हाल USB_ID(0x0ccd, 0x00b1): /* Terratec Aureon 7.1 USB */
		वापस snd_usb_cm6206_boot_quirk(dev);

	हाल USB_ID(0x0dba, 0x3000):
		/* Digidesign Mbox 2 */
		वापस snd_usb_mbox2_boot_quirk(dev);

	हाल USB_ID(0x1235, 0x0010): /* Focusrite Novation Saffire 6 USB */
	हाल USB_ID(0x1235, 0x0018): /* Focusrite Novation Twitch */
		वापस snd_usb_novation_boot_quirk(dev);

	हाल USB_ID(0x133e, 0x0815):
		/* Access Music VirusTI Desktop */
		वापस snd_usb_accessmusic_boot_quirk(dev);

	हाल USB_ID(0x17cc, 0x1000): /* Komplete Audio 6 */
	हाल USB_ID(0x17cc, 0x1010): /* Traktor Audio 6 */
	हाल USB_ID(0x17cc, 0x1020): /* Traktor Audio 10 */
		वापस snd_usb_nativeinstruments_boot_quirk(dev);
	हाल USB_ID(0x0763, 0x2012):  /* M-Audio Fast Track Pro USB */
		वापस snd_usb_fasttrackpro_boot_quirk(dev);
	हाल USB_ID(0x047f, 0xc010): /* Plantronics Gamecom 780 */
		वापस snd_usb_gamecon780_boot_quirk(dev);
	हाल USB_ID(0x2466, 0x8010): /* Fractal Audio Axe-Fx 3 */
		वापस snd_usb_axefx3_boot_quirk(dev);
	हाल USB_ID(0x07fd, 0x0004): /* MOTU MicroBook II */
		/*
		 * For some reason पूर्णांकerface 3 with venकरोr-spec class is
		 * detected on MicroBook IIc.
		 */
		अगर (get_अगरace_desc(पूर्णांकf->altsetting)->bInterfaceClass ==
		    USB_CLASS_VENDOR_SPEC &&
		    get_अगरace_desc(पूर्णांकf->altsetting)->bInterfaceNumber < 3)
			वापस snd_usb_motu_microbookii_boot_quirk(dev);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_usb_apply_boot_quirk_once(काष्ठा usb_device *dev,
				  काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				  स्थिर काष्ठा snd_usb_audio_quirk *quirk,
				  अचिन्हित पूर्णांक id)
अणु
	चयन (id) अणु
	हाल USB_ID(0x07fd, 0x0008): /* MOTU M Series */
		वापस snd_usb_motu_m_series_boot_quirk(dev);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * check अगर the device uses big-endian samples
 */
पूर्णांक snd_usb_is_big_endian_क्रमmat(काष्ठा snd_usb_audio *chip,
				 स्थिर काष्ठा audioक्रमmat *fp)
अणु
	/* it depends on altsetting whether the device is big-endian or not */
	चयन (chip->usb_id) अणु
	हाल USB_ID(0x0763, 0x2001): /* M-Audio Quattro: captured data only */
		अगर (fp->altsetting == 2 || fp->altsetting == 3 ||
			fp->altsetting == 5 || fp->altsetting == 6)
			वापस 1;
		अवरोध;
	हाल USB_ID(0x0763, 0x2003): /* M-Audio Audiophile USB */
		अगर (chip->setup == 0x00 ||
			fp->altsetting == 1 || fp->altsetting == 2 ||
			fp->altsetting == 3)
			वापस 1;
		अवरोध;
	हाल USB_ID(0x0763, 0x2012): /* M-Audio Fast Track Pro */
		अगर (fp->altsetting == 2 || fp->altsetting == 3 ||
			fp->altsetting == 5 || fp->altsetting == 6)
			वापस 1;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * For E-Mu 0404USB/0202USB/TrackerPre/0204 sample rate should be set क्रम device,
 * not क्रम पूर्णांकerface.
 */

क्रमागत अणु
	EMU_QUIRK_SR_44100HZ = 0,
	EMU_QUIRK_SR_48000HZ,
	EMU_QUIRK_SR_88200HZ,
	EMU_QUIRK_SR_96000HZ,
	EMU_QUIRK_SR_176400HZ,
	EMU_QUIRK_SR_192000HZ
पूर्ण;

अटल व्योम set_क्रमmat_emu_quirk(काष्ठा snd_usb_substream *subs,
				 स्थिर काष्ठा audioक्रमmat *fmt)
अणु
	अचिन्हित अक्षर emu_samplerate_id = 0;

	/* When capture is active
	 * sample rate shouldn't be changed
	 * by playback substream
	 */
	अगर (subs->direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (subs->stream->substream[SNDRV_PCM_STREAM_CAPTURE].cur_audiofmt)
			वापस;
	पूर्ण

	चयन (fmt->rate_min) अणु
	हाल 48000:
		emu_samplerate_id = EMU_QUIRK_SR_48000HZ;
		अवरोध;
	हाल 88200:
		emu_samplerate_id = EMU_QUIRK_SR_88200HZ;
		अवरोध;
	हाल 96000:
		emu_samplerate_id = EMU_QUIRK_SR_96000HZ;
		अवरोध;
	हाल 176400:
		emu_samplerate_id = EMU_QUIRK_SR_176400HZ;
		अवरोध;
	हाल 192000:
		emu_samplerate_id = EMU_QUIRK_SR_192000HZ;
		अवरोध;
	शेष:
		emu_samplerate_id = EMU_QUIRK_SR_44100HZ;
		अवरोध;
	पूर्ण
	snd_emuusb_set_samplerate(subs->stream->chip, emu_samplerate_id);
	subs->pkt_offset_adj = (emu_samplerate_id >= EMU_QUIRK_SR_176400HZ) ? 4 : 0;
पूर्ण

अटल पूर्णांक pioneer_djm_set_क्रमmat_quirk(काष्ठा snd_usb_substream *subs,
					u16 windex)
अणु
	अचिन्हित पूर्णांक cur_rate = subs->data_endpoपूर्णांक->cur_rate;
	u8 sr[3];
	// Convert to little endian
	sr[0] = cur_rate & 0xff;
	sr[1] = (cur_rate >> 8) & 0xff;
	sr[2] = (cur_rate >> 16) & 0xff;
	usb_set_पूर्णांकerface(subs->dev, 0, 1);
	// we should derive windex from fmt-sync_ep but it's not set
	snd_usb_ctl_msg(subs->stream->chip->dev,
		usb_sndctrlpipe(subs->stream->chip->dev, 0),
		0x01, 0x22, 0x0100, windex, &sr, 0x0003);
	वापस 0;
पूर्ण

व्योम snd_usb_set_क्रमmat_quirk(काष्ठा snd_usb_substream *subs,
			      स्थिर काष्ठा audioक्रमmat *fmt)
अणु
	चयन (subs->stream->chip->usb_id) अणु
	हाल USB_ID(0x041e, 0x3f02): /* E-Mu 0202 USB */
	हाल USB_ID(0x041e, 0x3f04): /* E-Mu 0404 USB */
	हाल USB_ID(0x041e, 0x3f0a): /* E-Mu Tracker Pre */
	हाल USB_ID(0x041e, 0x3f19): /* E-Mu 0204 USB */
		set_क्रमmat_emu_quirk(subs, fmt);
		अवरोध;
	हाल USB_ID(0x534d, 0x2109): /* MacroSilicon MS2109 */
		subs->stream_offset_adj = 2;
		अवरोध;
	हाल USB_ID(0x2b73, 0x0013): /* Pioneer DJM-450 */
		pioneer_djm_set_क्रमmat_quirk(subs, 0x0082);
		अवरोध;
	हाल USB_ID(0x08e4, 0x017f): /* Pioneer DJM-750 */
	हाल USB_ID(0x08e4, 0x0163): /* Pioneer DJM-850 */
		pioneer_djm_set_क्रमmat_quirk(subs, 0x0086);
		अवरोध;
	पूर्ण
पूर्ण

bool snd_usb_get_sample_rate_quirk(काष्ठा snd_usb_audio *chip)
अणु
	/* devices which करो not support पढ़ोing the sample rate. */
	चयन (chip->usb_id) अणु
	हाल USB_ID(0x041e, 0x4080): /* Creative Live Cam VF0610 */
	हाल USB_ID(0x04d8, 0xfeea): /* Benchmark DAC1 Pre */
	हाल USB_ID(0x0556, 0x0014): /* Phoenix Audio TMX320VC */
	हाल USB_ID(0x05a3, 0x9420): /* ELP HD USB Camera */
	हाल USB_ID(0x05a7, 0x1020): /* Bose Companion 5 */
	हाल USB_ID(0x074d, 0x3553): /* Outlaw RR2150 (Micronas UAC3553B) */
	हाल USB_ID(0x1395, 0x740a): /* Sennheiser DECT */
	हाल USB_ID(0x1901, 0x0191): /* GE B850V3 CP2114 audio पूर्णांकerface */
	हाल USB_ID(0x21b4, 0x0081): /* AudioQuest DragonFly */
	हाल USB_ID(0x2912, 0x30c8): /* Audioengine D1 */
	हाल USB_ID(0x413c, 0xa506): /* Dell AE515 sound bar */
	हाल USB_ID(0x046d, 0x084c): /* Logitech ConferenceCam Connect */
		वापस true;
	पूर्ण

	/* devices of these venकरोrs करोn't support पढ़ोing rate, either */
	चयन (USB_ID_VENDOR(chip->usb_id)) अणु
	हाल 0x045e: /* MS Lअगरecam */
	हाल 0x047f: /* Plantronics */
	हाल 0x1de7: /* Phoenix Audio */
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* ITF-USB DSD based DACs need a venकरोr cmd to चयन
 * between PCM and native DSD mode
 */
अटल bool is_itf_usb_dsd_dac(अचिन्हित पूर्णांक id)
अणु
	चयन (id) अणु
	हाल USB_ID(0x154e, 0x1002): /* Denon DCD-1500RE */
	हाल USB_ID(0x154e, 0x1003): /* Denon DA-300USB */
	हाल USB_ID(0x154e, 0x3005): /* Marantz HD-DAC1 */
	हाल USB_ID(0x154e, 0x3006): /* Marantz SA-14S1 */
	हाल USB_ID(0x1852, 0x5065): /* Luxman DA-06 */
	हाल USB_ID(0x0644, 0x8043): /* TEAC UD-501/UD-501V2/UD-503/NT-503 */
	हाल USB_ID(0x0644, 0x8044): /* Esoteric D-05X */
	हाल USB_ID(0x0644, 0x804a): /* TEAC UD-301 */
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक snd_usb_select_mode_quirk(काष्ठा snd_usb_audio *chip,
			      स्थिर काष्ठा audioक्रमmat *fmt)
अणु
	काष्ठा usb_device *dev = chip->dev;
	पूर्णांक err;

	अगर (is_itf_usb_dsd_dac(chip->usb_id)) अणु
		/* First चयन to alt set 0, otherwise the mode चयन cmd
		 * will not be accepted by the DAC
		 */
		err = usb_set_पूर्णांकerface(dev, fmt->अगरace, 0);
		अगर (err < 0)
			वापस err;

		msleep(20); /* Delay needed after setting the पूर्णांकerface */

		/* Venकरोr mode चयन cmd is required. */
		अगर (fmt->क्रमmats & SNDRV_PCM_FMTBIT_DSD_U32_BE) अणु
			/* DSD mode (DSD_U32) requested */
			err = snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0), 0,
					      USB_सूची_OUT|USB_TYPE_VENDOR|USB_RECIP_INTERFACE,
					      1, 1, शून्य, 0);
			अगर (err < 0)
				वापस err;

		पूर्ण अन्यथा अणु
			/* PCM or DOP mode (S32) requested */
			/* PCM mode (S16) requested */
			err = snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0), 0,
					      USB_सूची_OUT|USB_TYPE_VENDOR|USB_RECIP_INTERFACE,
					      0, 1, शून्य, 0);
			अगर (err < 0)
				वापस err;

		पूर्ण
		msleep(20);
	पूर्ण
	वापस 0;
पूर्ण

व्योम snd_usb_endpoपूर्णांक_start_quirk(काष्ठा snd_usb_endpoपूर्णांक *ep)
अणु
	/*
	 * "Playback Design" products send bogus feedback data at the start
	 * of the stream. Ignore them.
	 */
	अगर (USB_ID_VENDOR(ep->chip->usb_id) == 0x23ba &&
	    ep->type == SND_USB_ENDPOINT_TYPE_SYNC)
		ep->skip_packets = 4;

	/*
	 * M-Audio Fast Track C400/C600 - when packets are not skipped, real
	 * world latency varies by approx. +/- 50 frames (at 96kHz) each समय
	 * the stream is (re)started. When skipping packets 16 at endpoपूर्णांक
	 * start up, the real world latency is stable within +/- 1 frame (also
	 * across घातer cycles).
	 */
	अगर ((ep->chip->usb_id == USB_ID(0x0763, 0x2030) ||
	     ep->chip->usb_id == USB_ID(0x0763, 0x2031)) &&
	    ep->type == SND_USB_ENDPOINT_TYPE_DATA)
		ep->skip_packets = 16;

	/* Work around devices that report unreasonable feedback data */
	अगर ((ep->chip->usb_id == USB_ID(0x0644, 0x8038) ||  /* TEAC UD-H01 */
	     ep->chip->usb_id == USB_ID(0x1852, 0x5034)) && /* T+A Dac8 */
	    ep->syncmaxsize == 4)
		ep->tenor_fb_quirk = 1;
पूर्ण

व्योम snd_usb_set_पूर्णांकerface_quirk(काष्ठा snd_usb_audio *chip)
अणु
	अगर (!chip)
		वापस;
	/*
	 * "Playback Design" products need a 50ms delay after setting the
	 * USB पूर्णांकerface.
	 */
	चयन (USB_ID_VENDOR(chip->usb_id)) अणु
	हाल 0x23ba: /* Playback Design */
	हाल 0x0644: /* TEAC Corp. */
		msleep(50);
		अवरोध;
	पूर्ण
पूर्ण

/* quirk applied after snd_usb_ctl_msg(); not applied during boot quirks */
व्योम snd_usb_ctl_msg_quirk(काष्ठा usb_device *dev, अचिन्हित पूर्णांक pipe,
			   __u8 request, __u8 requesttype, __u16 value,
			   __u16 index, व्योम *data, __u16 size)
अणु
	काष्ठा snd_usb_audio *chip = dev_get_drvdata(&dev->dev);

	अगर (!chip)
		वापस;
	/*
	 * "Playback Design" products need a 20ms delay after each
	 * class compliant request
	 */
	अगर (USB_ID_VENDOR(chip->usb_id) == 0x23ba &&
	    (requesttype & USB_TYPE_MASK) == USB_TYPE_CLASS)
		msleep(20);

	/*
	 * "TEAC Corp." products need a 20ms delay after each
	 * class compliant request
	 */
	अगर (USB_ID_VENDOR(chip->usb_id) == 0x0644 &&
	    (requesttype & USB_TYPE_MASK) == USB_TYPE_CLASS)
		msleep(20);

	/* ITF-USB DSD based DACs functionality need a delay
	 * after each class compliant request
	 */
	अगर (is_itf_usb_dsd_dac(chip->usb_id)
	    && (requesttype & USB_TYPE_MASK) == USB_TYPE_CLASS)
		msleep(20);

	/*
	 * Plantronics headsets (C320, C320-M, etc) need a delay to aव्योम
	 * अक्रमom microhpone failures.
	 */
	अगर (USB_ID_VENDOR(chip->usb_id) == 0x047f &&
	    (requesttype & USB_TYPE_MASK) == USB_TYPE_CLASS)
		msleep(20);

	/* Zoom R16/24, many Logitech(at least H650e/H570e/BCC950),
	 * Jabra 550a, Kingston HyperX needs a tiny delay here,
	 * otherwise requests like get/set frequency वापस
	 * as failed despite actually succeeding.
	 */
	अगर ((chip->usb_id == USB_ID(0x1686, 0x00dd) ||
	     USB_ID_VENDOR(chip->usb_id) == 0x046d  || /* Logitech */
	     chip->usb_id == USB_ID(0x0b0e, 0x0349) ||
	     chip->usb_id == USB_ID(0x0951, 0x16ad)) &&
	    (requesttype & USB_TYPE_MASK) == USB_TYPE_CLASS)
		usleep_range(1000, 2000);

	/*
	 * Samsung USBC Headset (AKG) need a tiny delay after each
	 * class compliant request. (Model number: AAM625R or AAM627R)
	 */
	अगर (chip->usb_id == USB_ID(0x04e8, 0xa051) &&
	    (requesttype & USB_TYPE_MASK) == USB_TYPE_CLASS)
		usleep_range(5000, 6000);
पूर्ण

/*
 * snd_usb_पूर्णांकerface_dsd_क्रमmat_quirks() is called from क्रमmat.c to
 * augment the PCM क्रमmat bit-field क्रम DSD types. The UAC standards
 * करोn't have a designated bit field to denote DSD-capable पूर्णांकerfaces,
 * hence all hardware that is known to support this क्रमmat has to be
 * listed here.
 */
u64 snd_usb_पूर्णांकerface_dsd_क्रमmat_quirks(काष्ठा snd_usb_audio *chip,
					काष्ठा audioक्रमmat *fp,
					अचिन्हित पूर्णांक sample_bytes)
अणु
	काष्ठा usb_पूर्णांकerface *अगरace;

	/* Playback Designs */
	अगर (USB_ID_VENDOR(chip->usb_id) == 0x23ba &&
	    USB_ID_PRODUCT(chip->usb_id) < 0x0110) अणु
		चयन (fp->altsetting) अणु
		हाल 1:
			fp->dsd_करोp = true;
			वापस SNDRV_PCM_FMTBIT_DSD_U16_LE;
		हाल 2:
			fp->dsd_bitrev = true;
			वापस SNDRV_PCM_FMTBIT_DSD_U8;
		हाल 3:
			fp->dsd_bitrev = true;
			वापस SNDRV_PCM_FMTBIT_DSD_U16_LE;
		पूर्ण
	पूर्ण

	/* XMOS based USB DACs */
	चयन (chip->usb_id) अणु
	हाल USB_ID(0x1511, 0x0037): /* AURALiC VEGA */
	हाल USB_ID(0x2522, 0x0012): /* LH Lअसल VI DAC Infinity */
	हाल USB_ID(0x2772, 0x0230): /* Pro-Ject Pre Box S2 Digital */
		अगर (fp->altsetting == 2)
			वापस SNDRV_PCM_FMTBIT_DSD_U32_BE;
		अवरोध;

	हाल USB_ID(0x0d8c, 0x0316): /* Hegel HD12 DSD */
	हाल USB_ID(0x10cb, 0x0103): /* The Bit Opus #3; with fp->dsd_raw */
	हाल USB_ID(0x16d0, 0x06b2): /* NuPrime DAC-10 */
	हाल USB_ID(0x16d0, 0x09dd): /* Encore mDSD */
	हाल USB_ID(0x16d0, 0x0733): /* Furutech ADL Stratos */
	हाल USB_ID(0x16d0, 0x09db): /* NuPrime Audio DAC-9 */
	हाल USB_ID(0x1db5, 0x0003): /* Bryston BDA3 */
	हाल USB_ID(0x22e1, 0xca01): /* HDTA Serenade DSD */
	हाल USB_ID(0x249c, 0x9326): /* M2Tech Young MkIII */
	हाल USB_ID(0x2616, 0x0106): /* PS Audio NuWave DAC */
	हाल USB_ID(0x2622, 0x0041): /* Audiolab M-DAC+ */
	हाल USB_ID(0x27f7, 0x3002): /* W4S DAC-2v2SE */
	हाल USB_ID(0x29a2, 0x0086): /* Mutec MC3+ USB */
	हाल USB_ID(0x6b42, 0x0042): /* MSB Technology */
		अगर (fp->altsetting == 3)
			वापस SNDRV_PCM_FMTBIT_DSD_U32_BE;
		अवरोध;

	/* Amanero Combo384 USB based DACs with native DSD support */
	हाल USB_ID(0x16d0, 0x071a):  /* Amanero - Combo384 */
	हाल USB_ID(0x2ab6, 0x0004):  /* T+A DAC8DSD-V2.0, MP1000E-V2.0, MP2000R-V2.0, MP2500R-V2.0, MP3100HV-V2.0 */
	हाल USB_ID(0x2ab6, 0x0005):  /* T+A USB HD Audio 1 */
	हाल USB_ID(0x2ab6, 0x0006):  /* T+A USB HD Audio 2 */
		अगर (fp->altsetting == 2) अणु
			चयन (le16_to_cpu(chip->dev->descriptor.bcdDevice)) अणु
			हाल 0x199:
				वापस SNDRV_PCM_FMTBIT_DSD_U32_LE;
			हाल 0x19b:
			हाल 0x203:
				वापस SNDRV_PCM_FMTBIT_DSD_U32_BE;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल USB_ID(0x16d0, 0x0a23):
		अगर (fp->altsetting == 2)
			वापस SNDRV_PCM_FMTBIT_DSD_U32_BE;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/* ITF-USB DSD based DACs */
	अगर (is_itf_usb_dsd_dac(chip->usb_id)) अणु
		अगरace = usb_अगरnum_to_अगर(chip->dev, fp->अगरace);

		/* Altsetting 2 support native DSD अगर the num of altsets is
		 * three (0-2),
		 * Altsetting 3 support native DSD अगर the num of altsets is
		 * four (0-3).
		 */
		अगर (fp->altsetting == अगरace->num_altsetting - 1)
			वापस SNDRV_PCM_FMTBIT_DSD_U32_BE;
	पूर्ण

	/* Mostly generic method to detect many DSD-capable implementations -
	 * from XMOS/Thesycon
	 */
	चयन (USB_ID_VENDOR(chip->usb_id)) अणु
	हाल 0x152a:  /* Thesycon devices */
	हाल 0x20b1:  /* XMOS based devices */
	हाल 0x22d9:  /* Oppo */
	हाल 0x23ba:  /* Playback Designs */
	हाल 0x25ce:  /* Mytek devices */
	हाल 0x278b:  /* Rotel? */
	हाल 0x292b:  /* Gustard/Ess based devices */
	हाल 0x2972:  /* FiiO devices */
	हाल 0x2ab6:  /* T+A devices */
	हाल 0x3353:  /* Khadas devices */
	हाल 0x3842:  /* EVGA */
	हाल 0xc502:  /* HiBy devices */
		अगर (fp->dsd_raw)
			वापस SNDRV_PCM_FMTBIT_DSD_U32_BE;
		अवरोध;
	शेष:
		अवरोध;

	पूर्ण

	वापस 0;
पूर्ण

व्योम snd_usb_audioक्रमmat_attributes_quirk(काष्ठा snd_usb_audio *chip,
					  काष्ठा audioक्रमmat *fp,
					  पूर्णांक stream)
अणु
	चयन (chip->usb_id) अणु
	हाल USB_ID(0x0a92, 0x0053): /* AudioTrak Optoplay */
		/* Optoplay sets the sample rate attribute although
		 * it seems not supporting it in fact.
		 */
		fp->attributes &= ~UAC_EP_CS_ATTR_SAMPLE_RATE;
		अवरोध;
	हाल USB_ID(0x041e, 0x3020): /* Creative SB Audigy 2 NX */
	हाल USB_ID(0x0763, 0x2003): /* M-Audio Audiophile USB */
		/* करोesn't set the sample rate attribute, but supports it */
		fp->attributes |= UAC_EP_CS_ATTR_SAMPLE_RATE;
		अवरोध;
	हाल USB_ID(0x0763, 0x2001):  /* M-Audio Quattro USB */
	हाल USB_ID(0x0763, 0x2012):  /* M-Audio Fast Track Pro USB */
	हाल USB_ID(0x047f, 0x0ca1): /* plantronics headset */
	हाल USB_ID(0x077d, 0x07af): /* Grअगरfin iMic (note that there is
					an older model 77d:223) */
	/*
	 * plantronics headset and Grअगरfin iMic have set adaptive-in
	 * although it's really not...
	 */
		fp->ep_attr &= ~USB_ENDPOINT_SYNCTYPE;
		अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
			fp->ep_attr |= USB_ENDPOINT_SYNC_ADAPTIVE;
		अन्यथा
			fp->ep_attr |= USB_ENDPOINT_SYNC_SYNC;
		अवरोध;
	हाल USB_ID(0x07fd, 0x0004):  /* MOTU MicroBook IIc */
		/*
		 * MaxPacketsOnly attribute is erroneously set in endpoपूर्णांक
		 * descriptors. As a result this card produces noise with
		 * all sample rates other than 96 kHz.
		 */
		fp->attributes &= ~UAC_EP_CS_ATTR_FILL_MAX;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * registration quirk:
 * the registration is skipped अगर a device matches with the given ID,
 * unless the पूर्णांकerface reaches to the defined one.  This is क्रम delaying
 * the registration until the last known पूर्णांकerface, so that the card and
 * devices appear at the same समय.
 */

काष्ठा registration_quirk अणु
	अचिन्हित पूर्णांक usb_id;	/* composed via USB_ID() */
	अचिन्हित पूर्णांक पूर्णांकerface;	/* the पूर्णांकerface to trigger रेजिस्टर */
पूर्ण;

#घोषणा REG_QUIRK_ENTRY(venकरोr, product, अगरace) \
	अणु .usb_id = USB_ID(venकरोr, product), .पूर्णांकerface = (अगरace) पूर्ण

अटल स्थिर काष्ठा registration_quirk registration_quirks[] = अणु
	REG_QUIRK_ENTRY(0x0951, 0x16d8, 2),	/* Kingston HyperX AMP */
	REG_QUIRK_ENTRY(0x0951, 0x16ed, 2),	/* Kingston HyperX Cloud Alpha S */
	REG_QUIRK_ENTRY(0x0951, 0x16ea, 2),	/* Kingston HyperX Cloud Flight S */
	अणु 0 पूर्ण					/* terminator */
पूर्ण;

/* वापस true अगर skipping registration */
bool snd_usb_registration_quirk(काष्ठा snd_usb_audio *chip, पूर्णांक अगरace)
अणु
	स्थिर काष्ठा registration_quirk *q;

	क्रम (q = registration_quirks; q->usb_id; q++)
		अगर (chip->usb_id == q->usb_id)
			वापस अगरace != q->पूर्णांकerface;

	/* Register as normal */
	वापस false;
पूर्ण
