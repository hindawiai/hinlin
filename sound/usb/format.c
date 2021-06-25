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

#समावेश "usbaudio.h"
#समावेश "card.h"
#समावेश "quirks.h"
#समावेश "helper.h"
#समावेश "clock.h"
#समावेश "format.h"

/*
 * parse the audio क्रमmat type I descriptor
 * and वापसs the corresponding pcm क्रमmat
 *
 * @dev: usb device
 * @fp: audioक्रमmat record
 * @क्रमmat: the क्रमmat tag (wFormatTag)
 * @fmt: the क्रमmat type descriptor (v1/v2) or AudioStreaming descriptor (v3)
 */
अटल u64 parse_audio_क्रमmat_i_type(काष्ठा snd_usb_audio *chip,
				     काष्ठा audioक्रमmat *fp,
				     u64 क्रमmat, व्योम *_fmt)
अणु
	पूर्णांक sample_width, sample_bytes;
	u64 pcm_क्रमmats = 0;

	चयन (fp->protocol) अणु
	हाल UAC_VERSION_1:
	शेष: अणु
		काष्ठा uac_क्रमmat_type_i_discrete_descriptor *fmt = _fmt;
		अगर (क्रमmat >= 64)
			वापस 0; /* invalid क्रमmat */
		sample_width = fmt->bBitResolution;
		sample_bytes = fmt->bSubframeSize;
		क्रमmat = 1ULL << क्रमmat;
		अवरोध;
	पूर्ण

	हाल UAC_VERSION_2: अणु
		काष्ठा uac_क्रमmat_type_i_ext_descriptor *fmt = _fmt;
		sample_width = fmt->bBitResolution;
		sample_bytes = fmt->bSubslotSize;

		अगर (क्रमmat & UAC2_FORMAT_TYPE_I_RAW_DATA) अणु
			pcm_क्रमmats |= SNDRV_PCM_FMTBIT_SPECIAL;
			/* flag potentially raw DSD capable altsettings */
			fp->dsd_raw = true;
		पूर्ण

		क्रमmat <<= 1;
		अवरोध;
	पूर्ण
	हाल UAC_VERSION_3: अणु
		काष्ठा uac3_as_header_descriptor *as = _fmt;

		sample_width = as->bBitResolution;
		sample_bytes = as->bSubslotSize;

		अगर (क्रमmat & UAC3_FORMAT_TYPE_I_RAW_DATA)
			pcm_क्रमmats |= SNDRV_PCM_FMTBIT_SPECIAL;

		क्रमmat <<= 1;
		अवरोध;
	पूर्ण
	पूर्ण

	fp->fmt_bits = sample_width;

	अगर ((pcm_क्रमmats == 0) &&
	    (क्रमmat == 0 || क्रमmat == (1 << UAC_FORMAT_TYPE_I_UNDEFINED))) अणु
		/* some devices करोn't define this correctly... */
		usb_audio_info(chip, "%u:%d : format type 0 is detected, processed as PCM\n",
			fp->अगरace, fp->altsetting);
		क्रमmat = 1 << UAC_FORMAT_TYPE_I_PCM;
	पूर्ण
	अगर (क्रमmat & (1 << UAC_FORMAT_TYPE_I_PCM)) अणु
		अगर (((chip->usb_id == USB_ID(0x0582, 0x0016)) ||
		     /* Edirol SD-90 */
		     (chip->usb_id == USB_ID(0x0582, 0x000c))) &&
		     /* Roland SC-D70 */
		    sample_width == 24 && sample_bytes == 2)
			sample_bytes = 3;
		अन्यथा अगर (sample_width > sample_bytes * 8) अणु
			usb_audio_info(chip, "%u:%d : sample bitwidth %d in over sample bytes %d\n",
				 fp->अगरace, fp->altsetting,
				 sample_width, sample_bytes);
		पूर्ण
		/* check the क्रमmat byte size */
		चयन (sample_bytes) अणु
		हाल 1:
			pcm_क्रमmats |= SNDRV_PCM_FMTBIT_S8;
			अवरोध;
		हाल 2:
			अगर (snd_usb_is_big_endian_क्रमmat(chip, fp))
				pcm_क्रमmats |= SNDRV_PCM_FMTBIT_S16_BE; /* grrr, big endian!! */
			अन्यथा
				pcm_क्रमmats |= SNDRV_PCM_FMTBIT_S16_LE;
			अवरोध;
		हाल 3:
			अगर (snd_usb_is_big_endian_क्रमmat(chip, fp))
				pcm_क्रमmats |= SNDRV_PCM_FMTBIT_S24_3BE; /* grrr, big endian!! */
			अन्यथा
				pcm_क्रमmats |= SNDRV_PCM_FMTBIT_S24_3LE;
			अवरोध;
		हाल 4:
			pcm_क्रमmats |= SNDRV_PCM_FMTBIT_S32_LE;
			अवरोध;
		शेष:
			usb_audio_info(chip,
				 "%u:%d : unsupported sample bitwidth %d in %d bytes\n",
				 fp->अगरace, fp->altsetting,
				 sample_width, sample_bytes);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (क्रमmat & (1 << UAC_FORMAT_TYPE_I_PCM8)) अणु
		/* Dallas DS4201 workaround: it advertises U8 क्रमmat, but really
		   supports S8. */
		अगर (chip->usb_id == USB_ID(0x04fa, 0x4201))
			pcm_क्रमmats |= SNDRV_PCM_FMTBIT_S8;
		अन्यथा
			pcm_क्रमmats |= SNDRV_PCM_FMTBIT_U8;
	पूर्ण
	अगर (क्रमmat & (1 << UAC_FORMAT_TYPE_I_IEEE_FLOAT)) अणु
		pcm_क्रमmats |= SNDRV_PCM_FMTBIT_FLOAT_LE;
	पूर्ण
	अगर (क्रमmat & (1 << UAC_FORMAT_TYPE_I_ALAW)) अणु
		pcm_क्रमmats |= SNDRV_PCM_FMTBIT_A_LAW;
	पूर्ण
	अगर (क्रमmat & (1 << UAC_FORMAT_TYPE_I_MULAW)) अणु
		pcm_क्रमmats |= SNDRV_PCM_FMTBIT_MU_LAW;
	पूर्ण
	अगर (क्रमmat & ~0x3f) अणु
		usb_audio_info(chip,
			 "%u:%d : unsupported format bits %#llx\n",
			 fp->अगरace, fp->altsetting, क्रमmat);
	पूर्ण

	pcm_क्रमmats |= snd_usb_पूर्णांकerface_dsd_क्रमmat_quirks(chip, fp, sample_bytes);

	वापस pcm_क्रमmats;
पूर्ण

अटल पूर्णांक set_fixed_rate(काष्ठा audioक्रमmat *fp, पूर्णांक rate, पूर्णांक rate_bits)
अणु
	kमुक्त(fp->rate_table);
	fp->rate_table = kदो_स्मृति(माप(पूर्णांक), GFP_KERNEL);
	अगर (!fp->rate_table)
		वापस -ENOMEM;
	fp->nr_rates = 1;
	fp->rate_min = rate;
	fp->rate_max = rate;
	fp->rates = rate_bits;
	fp->rate_table[0] = rate;
	वापस 0;
पूर्ण

/* set up rate_min, rate_max and rates from the rate table */
अटल व्योम set_rate_table_min_max(काष्ठा audioक्रमmat *fp)
अणु
	अचिन्हित पूर्णांक rate;
	पूर्णांक i;

	fp->rate_min = पूर्णांक_उच्च;
	fp->rate_max = 0;
	fp->rates = 0;
	क्रम (i = 0; i < fp->nr_rates; i++) अणु
		rate = fp->rate_table[i];
		fp->rate_min = min(fp->rate_min, rate);
		fp->rate_max = max(fp->rate_max, rate);
		fp->rates |= snd_pcm_rate_to_rate_bit(rate);
	पूर्ण
पूर्ण

/*
 * parse the क्रमmat descriptor and stores the possible sample rates
 * on the audioक्रमmat table (audio class v1).
 *
 * @dev: usb device
 * @fp: audioक्रमmat record
 * @fmt: the क्रमmat descriptor
 * @offset: the start offset of descriptor poपूर्णांकing the rate type
 *          (7 क्रम type I and II, 8 क्रम type II)
 */
अटल पूर्णांक parse_audio_क्रमmat_rates_v1(काष्ठा snd_usb_audio *chip, काष्ठा audioक्रमmat *fp,
				       अचिन्हित अक्षर *fmt, पूर्णांक offset)
अणु
	पूर्णांक nr_rates = fmt[offset];

	अगर (fmt[0] < offset + 1 + 3 * (nr_rates ? nr_rates : 2)) अणु
		usb_audio_err(chip,
			"%u:%d : invalid UAC_FORMAT_TYPE desc\n",
			fp->अगरace, fp->altsetting);
		वापस -EINVAL;
	पूर्ण

	अगर (nr_rates) अणु
		/*
		 * build the rate table and biपंचांगap flags
		 */
		पूर्णांक r, idx;

		fp->rate_table = kदो_स्मृति_array(nr_rates, माप(पूर्णांक),
					       GFP_KERNEL);
		अगर (fp->rate_table == शून्य)
			वापस -ENOMEM;

		fp->nr_rates = 0;
		क्रम (r = 0, idx = offset + 1; r < nr_rates; r++, idx += 3) अणु
			अचिन्हित पूर्णांक rate = combine_triple(&fmt[idx]);
			अगर (!rate)
				जारी;
			/* C-Media CM6501 mislabels its 96 kHz altsetting */
			/* Terratec Aureon 7.1 USB C-Media 6206, too */
			अगर (rate == 48000 && nr_rates == 1 &&
			    (chip->usb_id == USB_ID(0x0d8c, 0x0201) ||
			     chip->usb_id == USB_ID(0x0d8c, 0x0102) ||
			     chip->usb_id == USB_ID(0x0ccd, 0x00b1)) &&
			    fp->altsetting == 5 && fp->maxpacksize == 392)
				rate = 96000;
			/* Creative VF0420/VF0470 Live Cams report 16 kHz instead of 8kHz */
			अगर (rate == 16000 &&
			    (chip->usb_id == USB_ID(0x041e, 0x4064) ||
			     chip->usb_id == USB_ID(0x041e, 0x4068)))
				rate = 8000;

			fp->rate_table[fp->nr_rates++] = rate;
		पूर्ण
		अगर (!fp->nr_rates) अणु
			usb_audio_info(chip,
				       "%u:%d: All rates were zero\n",
				       fp->अगरace, fp->altsetting);
			वापस -EINVAL;
		पूर्ण
		set_rate_table_min_max(fp);
	पूर्ण अन्यथा अणु
		/* continuous rates */
		fp->rates = SNDRV_PCM_RATE_CONTINUOUS;
		fp->rate_min = combine_triple(&fmt[offset + 1]);
		fp->rate_max = combine_triple(&fmt[offset + 4]);
	पूर्ण

	/* Jabra Evolve 65 headset */
	अगर (chip->usb_id == USB_ID(0x0b0e, 0x030b)) अणु
		/* only 48kHz क्रम playback जबतक keeping 16kHz क्रम capture */
		अगर (fp->nr_rates != 1)
			वापस set_fixed_rate(fp, 48000, SNDRV_PCM_RATE_48000);
	पूर्ण

	वापस 0;
पूर्ण


/*
 * Presonus Studio 1810c supports a limited set of sampling
 * rates per altsetting but reports the full set each समय.
 * If we करोn't filter out the unsupported rates and attempt
 * to configure the card, it will hang refusing to करो any
 * further audio I/O until a hard reset is perक्रमmed.
 *
 * The list of supported rates per altsetting (set of available
 * I/O channels) is described in the owner's manual, section 2.2.
 */
अटल bool s1810c_valid_sample_rate(काष्ठा audioक्रमmat *fp,
				     अचिन्हित पूर्णांक rate)
अणु
	चयन (fp->altsetting) अणु
	हाल 1:
		/* All ADAT ports available */
		वापस rate <= 48000;
	हाल 2:
		/* Half of ADAT ports available */
		वापस (rate == 88200 || rate == 96000);
	हाल 3:
		/* Analog I/O only (no S/PDIF nor ADAT) */
		वापस rate >= 176400;
	शेष:
		वापस false;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Many Focusrite devices supports a limited set of sampling rates per
 * altsetting. Maximum rate is exposed in the last 4 bytes of Format Type
 * descriptor which has a non-standard bLength = 10.
 */
अटल bool focusrite_valid_sample_rate(काष्ठा snd_usb_audio *chip,
					काष्ठा audioक्रमmat *fp,
					अचिन्हित पूर्णांक rate)
अणु
	काष्ठा usb_पूर्णांकerface *अगरace;
	काष्ठा usb_host_पूर्णांकerface *alts;
	अचिन्हित अक्षर *fmt;
	अचिन्हित पूर्णांक max_rate;

	अगरace = usb_अगरnum_to_अगर(chip->dev, fp->अगरace);
	अगर (!अगरace)
		वापस true;

	alts = &अगरace->altsetting[fp->altset_idx];
	fmt = snd_usb_find_csपूर्णांक_desc(alts->extra, alts->extralen,
				      शून्य, UAC_FORMAT_TYPE);
	अगर (!fmt)
		वापस true;

	अगर (fmt[0] == 10) अणु /* bLength */
		max_rate = combine_quad(&fmt[6]);

		/* Validate max rate */
		अगर (max_rate != 48000 &&
		    max_rate != 96000 &&
		    max_rate != 192000 &&
		    max_rate != 384000) अणु

			usb_audio_info(chip,
				"%u:%d : unexpected max rate: %u\n",
				fp->अगरace, fp->altsetting, max_rate);

			वापस true;
		पूर्ण

		वापस rate <= max_rate;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Helper function to walk the array of sample rate triplets reported by
 * the device. The problem is that we need to parse whole array first to
 * get to know how many sample rates we have to expect.
 * Then fp->rate_table can be allocated and filled.
 */
अटल पूर्णांक parse_uac2_sample_rate_range(काष्ठा snd_usb_audio *chip,
					काष्ठा audioक्रमmat *fp, पूर्णांक nr_triplets,
					स्थिर अचिन्हित अक्षर *data)
अणु
	पूर्णांक i, nr_rates = 0;

	क्रम (i = 0; i < nr_triplets; i++) अणु
		पूर्णांक min = combine_quad(&data[2 + 12 * i]);
		पूर्णांक max = combine_quad(&data[6 + 12 * i]);
		पूर्णांक res = combine_quad(&data[10 + 12 * i]);
		अचिन्हित पूर्णांक rate;

		अगर ((max < 0) || (min < 0) || (res < 0) || (max < min))
			जारी;

		/*
		 * क्रम ranges with res == 1, we announce a continuous sample
		 * rate range, and this function should वापस 0 क्रम no further
		 * parsing.
		 */
		अगर (res == 1) अणु
			fp->rate_min = min;
			fp->rate_max = max;
			fp->rates = SNDRV_PCM_RATE_CONTINUOUS;
			वापस 0;
		पूर्ण

		क्रम (rate = min; rate <= max; rate += res) अणु

			/* Filter out invalid rates on Presonus Studio 1810c */
			अगर (chip->usb_id == USB_ID(0x0194f, 0x010c) &&
			    !s1810c_valid_sample_rate(fp, rate))
				जाओ skip_rate;

			/* Filter out invalid rates on Focusrite devices */
			अगर (USB_ID_VENDOR(chip->usb_id) == 0x1235 &&
			    !focusrite_valid_sample_rate(chip, fp, rate))
				जाओ skip_rate;

			अगर (fp->rate_table)
				fp->rate_table[nr_rates] = rate;
			nr_rates++;
			अगर (nr_rates >= MAX_NR_RATES) अणु
				usb_audio_err(chip, "invalid uac2 rates\n");
				अवरोध;
			पूर्ण

skip_rate:
			/* aव्योम endless loop */
			अगर (res == 0)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस nr_rates;
पूर्ण

/* Line6 Helix series and the Rode Rodecaster Pro करोn't support the
 * UAC2_CS_RANGE usb function call. Return a अटल table of known
 * घड़ी rates.
 */
अटल पूर्णांक line6_parse_audio_क्रमmat_rates_quirk(काष्ठा snd_usb_audio *chip,
						काष्ठा audioक्रमmat *fp)
अणु
	चयन (chip->usb_id) अणु
	हाल USB_ID(0x0e41, 0x4241): /* Line6 Helix */
	हाल USB_ID(0x0e41, 0x4242): /* Line6 Helix Rack */
	हाल USB_ID(0x0e41, 0x4244): /* Line6 Helix LT */
	हाल USB_ID(0x0e41, 0x4246): /* Line6 HX-Stomp */
	हाल USB_ID(0x0e41, 0x4247): /* Line6 Pod Go */
	हाल USB_ID(0x0e41, 0x4248): /* Line6 Helix >= fw 2.82 */
	हाल USB_ID(0x0e41, 0x4249): /* Line6 Helix Rack >= fw 2.82 */
	हाल USB_ID(0x0e41, 0x424a): /* Line6 Helix LT >= fw 2.82 */
	हाल USB_ID(0x19f7, 0x0011): /* Rode Rodecaster Pro */
		वापस set_fixed_rate(fp, 48000, SNDRV_PCM_RATE_48000);
	पूर्ण

	वापस -ENODEV;
पूर्ण

/* check whether the given altsetting is supported क्रम the alपढ़ोy set rate */
अटल bool check_valid_altsetting_v2v3(काष्ठा snd_usb_audio *chip, पूर्णांक अगरace,
					पूर्णांक altsetting)
अणु
	काष्ठा usb_device *dev = chip->dev;
	__le64 raw_data = 0;
	u64 data;
	पूर्णांक err;

	/* we assume 64bit is enough क्रम any altsettings */
	अगर (snd_BUG_ON(altsetting >= 64 - 8))
		वापस false;

	err = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0), UAC2_CS_CUR,
			      USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_IN,
			      UAC2_AS_VAL_ALT_SETTINGS << 8,
			      अगरace, &raw_data, माप(raw_data));
	अगर (err < 0)
		वापस false;

	data = le64_to_cpu(raw_data);
	/* first byte contains the biपंचांगap size */
	अगर ((data & 0xff) * 8 < altsetting)
		वापस false;
	अगर (data & (1ULL << (altsetting + 8)))
		वापस true;

	वापस false;
पूर्ण

/*
 * Validate each sample rate with the altsetting
 * Rebuild the rate table अगर only partial values are valid
 */
अटल पूर्णांक validate_sample_rate_table_v2v3(काष्ठा snd_usb_audio *chip,
					   काष्ठा audioक्रमmat *fp,
					   पूर्णांक घड़ी)
अणु
	काष्ठा usb_device *dev = chip->dev;
	अचिन्हित पूर्णांक *table;
	अचिन्हित पूर्णांक nr_rates;
	पूर्णांक i, err;

	/* perक्रमming the rate verअगरication may lead to unexpected USB bus
	 * behavior afterwards by some unknown reason.  Do this only क्रम the
	 * known devices.
	 */
	चयन (USB_ID_VENDOR(chip->usb_id)) अणु
	हाल 0x07fd: /* MOTU */
		अवरोध;
	शेष:
		वापस 0; /* करोn't perक्रमm the validation as शेष */
	पूर्ण

	table = kसुस्मृति(fp->nr_rates, माप(*table), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	/* clear the पूर्णांकerface altsetting at first */
	usb_set_पूर्णांकerface(dev, fp->अगरace, 0);

	nr_rates = 0;
	क्रम (i = 0; i < fp->nr_rates; i++) अणु
		err = snd_usb_set_sample_rate_v2v3(chip, fp, घड़ी,
						   fp->rate_table[i]);
		अगर (err < 0)
			जारी;

		अगर (check_valid_altsetting_v2v3(chip, fp->अगरace, fp->altsetting))
			table[nr_rates++] = fp->rate_table[i];
	पूर्ण

	अगर (!nr_rates) अणु
		usb_audio_dbg(chip,
			      "No valid sample rate available for %d:%d, assuming a firmware bug\n",
			      fp->अगरace, fp->altsetting);
		nr_rates = fp->nr_rates; /* जारी as is */
	पूर्ण

	अगर (fp->nr_rates == nr_rates) अणु
		kमुक्त(table);
		वापस 0;
	पूर्ण

	kमुक्त(fp->rate_table);
	fp->rate_table = table;
	fp->nr_rates = nr_rates;
	वापस 0;
पूर्ण

/*
 * parse the क्रमmat descriptor and stores the possible sample rates
 * on the audioक्रमmat table (audio class v2 and v3).
 */
अटल पूर्णांक parse_audio_क्रमmat_rates_v2v3(काष्ठा snd_usb_audio *chip,
				       काष्ठा audioक्रमmat *fp)
अणु
	काष्ठा usb_device *dev = chip->dev;
	अचिन्हित अक्षर पंचांगp[2], *data;
	पूर्णांक nr_triplets, data_size, ret = 0, ret_l6;
	पूर्णांक घड़ी = snd_usb_घड़ी_find_source(chip, fp, false);

	अगर (घड़ी < 0) अणु
		dev_err(&dev->dev,
			"%s(): unable to find clock source (clock %d)\n",
				__func__, घड़ी);
		जाओ err;
	पूर्ण

	/* get the number of sample rates first by only fetching 2 bytes */
	ret = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0), UAC2_CS_RANGE,
			      USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_IN,
			      UAC2_CS_CONTROL_SAM_FREQ << 8,
			      snd_usb_ctrl_पूर्णांकf(chip) | (घड़ी << 8),
			      पंचांगp, माप(पंचांगp));

	अगर (ret < 0) अणु
		/* line6 helix devices करोn't support UAC2_CS_CONTROL_SAM_FREQ call */
		ret_l6 = line6_parse_audio_क्रमmat_rates_quirk(chip, fp);
		अगर (ret_l6 == -ENODEV) अणु
			/* no line6 device found जारी showing the error */
			dev_err(&dev->dev,
				"%s(): unable to retrieve number of sample rates (clock %d)\n",
				__func__, घड़ी);
			जाओ err;
		पूर्ण
		अगर (ret_l6 == 0) अणु
			dev_info(&dev->dev,
				"%s(): unable to retrieve number of sample rates: set it to a predefined value (clock %d).\n",
				__func__, घड़ी);
			वापस 0;
		पूर्ण
		ret = ret_l6;
		जाओ err;
	पूर्ण

	nr_triplets = (पंचांगp[1] << 8) | पंचांगp[0];
	data_size = 2 + 12 * nr_triplets;
	data = kzalloc(data_size, GFP_KERNEL);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	/* now get the full inक्रमmation */
	ret = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0), UAC2_CS_RANGE,
			      USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_IN,
			      UAC2_CS_CONTROL_SAM_FREQ << 8,
			      snd_usb_ctrl_पूर्णांकf(chip) | (घड़ी << 8),
			      data, data_size);

	अगर (ret < 0) अणु
		dev_err(&dev->dev,
			"%s(): unable to retrieve sample rate range (clock %d)\n",
				__func__, घड़ी);
		ret = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	/* Call the triplet parser, and make sure fp->rate_table is शून्य.
	 * We just use the वापस value to know how many sample rates we
	 * will have to deal with. */
	kमुक्त(fp->rate_table);
	fp->rate_table = शून्य;
	fp->nr_rates = parse_uac2_sample_rate_range(chip, fp, nr_triplets, data);

	अगर (fp->nr_rates == 0) अणु
		/* SNDRV_PCM_RATE_CONTINUOUS */
		ret = 0;
		जाओ err_मुक्त;
	पूर्ण

	fp->rate_table = kदो_स्मृति_array(fp->nr_rates, माप(पूर्णांक), GFP_KERNEL);
	अगर (!fp->rate_table) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	/* Call the triplet parser again, but this समय, fp->rate_table is
	 * allocated, so the rates will be stored */
	parse_uac2_sample_rate_range(chip, fp, nr_triplets, data);

	ret = validate_sample_rate_table_v2v3(chip, fp, घड़ी);
	अगर (ret < 0)
		जाओ err_मुक्त;

	set_rate_table_min_max(fp);

err_मुक्त:
	kमुक्त(data);
err:
	वापस ret;
पूर्ण

/*
 * parse the क्रमmat type I and III descriptors
 */
अटल पूर्णांक parse_audio_क्रमmat_i(काष्ठा snd_usb_audio *chip,
				काष्ठा audioक्रमmat *fp, u64 क्रमmat,
				व्योम *_fmt)
अणु
	snd_pcm_क्रमmat_t pcm_क्रमmat;
	अचिन्हित पूर्णांक fmt_type;
	पूर्णांक ret;

	चयन (fp->protocol) अणु
	शेष:
	हाल UAC_VERSION_1:
	हाल UAC_VERSION_2: अणु
		काष्ठा uac_क्रमmat_type_i_continuous_descriptor *fmt = _fmt;

		fmt_type = fmt->bFormatType;
		अवरोध;
	पूर्ण
	हाल UAC_VERSION_3: अणु
		/* fp->fmt_type is alपढ़ोy set in this हाल */
		fmt_type = fp->fmt_type;
		अवरोध;
	पूर्ण
	पूर्ण

	अगर (fmt_type == UAC_FORMAT_TYPE_III) अणु
		/* FIXME: the क्रमmat type is really IECxxx
		 *        but we give normal PCM क्रमmat to get the existing
		 *        apps working...
		 */
		चयन (chip->usb_id) अणु

		हाल USB_ID(0x0763, 0x2003): /* M-Audio Audiophile USB */
			अगर (chip->setup == 0x00 && 
			    fp->altsetting == 6)
				pcm_क्रमmat = SNDRV_PCM_FORMAT_S16_BE;
			अन्यथा
				pcm_क्रमmat = SNDRV_PCM_FORMAT_S16_LE;
			अवरोध;
		शेष:
			pcm_क्रमmat = SNDRV_PCM_FORMAT_S16_LE;
		पूर्ण
		fp->क्रमmats = pcm_क्रमmat_to_bits(pcm_क्रमmat);
	पूर्ण अन्यथा अणु
		fp->क्रमmats = parse_audio_क्रमmat_i_type(chip, fp, क्रमmat, _fmt);
		अगर (!fp->क्रमmats)
			वापस -EINVAL;
	पूर्ण

	/* gather possible sample rates */
	/* audio class v1 reports possible sample rates as part of the
	 * proprietary class specअगरic descriptor.
	 * audio class v2 uses class specअगरic EP0 range requests क्रम that.
	 */
	चयन (fp->protocol) अणु
	शेष:
	हाल UAC_VERSION_1: अणु
		काष्ठा uac_क्रमmat_type_i_continuous_descriptor *fmt = _fmt;

		fp->channels = fmt->bNrChannels;
		ret = parse_audio_क्रमmat_rates_v1(chip, fp, (अचिन्हित अक्षर *) fmt, 7);
		अवरोध;
	पूर्ण
	हाल UAC_VERSION_2:
	हाल UAC_VERSION_3: अणु
		/* fp->channels is alपढ़ोy set in this हाल */
		ret = parse_audio_क्रमmat_rates_v2v3(chip, fp);
		अवरोध;
	पूर्ण
	पूर्ण

	अगर (fp->channels < 1) अणु
		usb_audio_err(chip,
			"%u:%d : invalid channels %d\n",
			fp->अगरace, fp->altsetting, fp->channels);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * parse the क्रमmat type II descriptor
 */
अटल पूर्णांक parse_audio_क्रमmat_ii(काष्ठा snd_usb_audio *chip,
				 काष्ठा audioक्रमmat *fp,
				 u64 क्रमmat, व्योम *_fmt)
अणु
	पूर्णांक brate, framesize, ret;

	चयन (क्रमmat) अणु
	हाल UAC_FORMAT_TYPE_II_AC3:
		/* FIXME: there is no AC3 क्रमmat defined yet */
		// fp->क्रमmats = SNDRV_PCM_FMTBIT_AC3;
		fp->क्रमmats = SNDRV_PCM_FMTBIT_U8; /* temporary hack to receive byte streams */
		अवरोध;
	हाल UAC_FORMAT_TYPE_II_MPEG:
		fp->क्रमmats = SNDRV_PCM_FMTBIT_MPEG;
		अवरोध;
	शेष:
		usb_audio_info(chip,
			 "%u:%d : unknown format tag %#llx is detected.  processed as MPEG.\n",
			 fp->अगरace, fp->altsetting, क्रमmat);
		fp->क्रमmats = SNDRV_PCM_FMTBIT_MPEG;
		अवरोध;
	पूर्ण

	fp->channels = 1;

	चयन (fp->protocol) अणु
	शेष:
	हाल UAC_VERSION_1: अणु
		काष्ठा uac_क्रमmat_type_ii_discrete_descriptor *fmt = _fmt;
		brate = le16_to_cpu(fmt->wMaxBitRate);
		framesize = le16_to_cpu(fmt->wSamplesPerFrame);
		usb_audio_info(chip, "found format II with max.bitrate = %d, frame size=%d\n", brate, framesize);
		fp->frame_size = framesize;
		ret = parse_audio_क्रमmat_rates_v1(chip, fp, _fmt, 8); /* fmt[8..] sample rates */
		अवरोध;
	पूर्ण
	हाल UAC_VERSION_2: अणु
		काष्ठा uac_क्रमmat_type_ii_ext_descriptor *fmt = _fmt;
		brate = le16_to_cpu(fmt->wMaxBitRate);
		framesize = le16_to_cpu(fmt->wSamplesPerFrame);
		usb_audio_info(chip, "found format II with max.bitrate = %d, frame size=%d\n", brate, framesize);
		fp->frame_size = framesize;
		ret = parse_audio_क्रमmat_rates_v2v3(chip, fp);
		अवरोध;
	पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक snd_usb_parse_audio_क्रमmat(काष्ठा snd_usb_audio *chip,
			       काष्ठा audioक्रमmat *fp, u64 क्रमmat,
			       काष्ठा uac_क्रमmat_type_i_continuous_descriptor *fmt,
			       पूर्णांक stream)
अणु
	पूर्णांक err;

	चयन (fmt->bFormatType) अणु
	हाल UAC_FORMAT_TYPE_I:
	हाल UAC_FORMAT_TYPE_III:
		err = parse_audio_क्रमmat_i(chip, fp, क्रमmat, fmt);
		अवरोध;
	हाल UAC_FORMAT_TYPE_II:
		err = parse_audio_क्रमmat_ii(chip, fp, क्रमmat, fmt);
		अवरोध;
	शेष:
		usb_audio_info(chip,
			 "%u:%d : format type %d is not supported yet\n",
			 fp->अगरace, fp->altsetting,
			 fmt->bFormatType);
		वापस -ENOTSUPP;
	पूर्ण
	fp->fmt_type = fmt->bFormatType;
	अगर (err < 0)
		वापस err;
#अगर 1
	/* FIXME: temporary hack क्रम extigy/audigy 2 nx/zs */
	/* extigy apparently supports sample rates other than 48k
	 * but not in ordinary way.  so we enable only 48k aपंचांग.
	 */
	अगर (chip->usb_id == USB_ID(0x041e, 0x3000) ||
	    chip->usb_id == USB_ID(0x041e, 0x3020) ||
	    chip->usb_id == USB_ID(0x041e, 0x3061)) अणु
		अगर (fmt->bFormatType == UAC_FORMAT_TYPE_I &&
		    fp->rates != SNDRV_PCM_RATE_48000 &&
		    fp->rates != SNDRV_PCM_RATE_96000)
			वापस -ENOTSUPP;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक snd_usb_parse_audio_क्रमmat_v3(काष्ठा snd_usb_audio *chip,
			       काष्ठा audioक्रमmat *fp,
			       काष्ठा uac3_as_header_descriptor *as,
			       पूर्णांक stream)
अणु
	u64 क्रमmat = le64_to_cpu(as->bmFormats);
	पूर्णांक err;

	/*
	 * Type I क्रमmat bits are D0..D6
	 * This test works because type IV is not supported
	 */
	अगर (क्रमmat & 0x7f)
		fp->fmt_type = UAC_FORMAT_TYPE_I;
	अन्यथा
		fp->fmt_type = UAC_FORMAT_TYPE_III;

	err = parse_audio_क्रमmat_i(chip, fp, क्रमmat, as);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
