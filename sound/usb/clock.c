<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Clock करोमुख्य and sample rate management functions
 */

#समावेश <linux/bitops.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/audपन.स>
#समावेश <linux/usb/audio-v2.h>
#समावेश <linux/usb/audio-v3.h>

#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/pcm.h>

#समावेश "usbaudio.h"
#समावेश "card.h"
#समावेश "helper.h"
#समावेश "clock.h"
#समावेश "quirks.h"

अटल व्योम *find_uac_घड़ी_desc(काष्ठा usb_host_पूर्णांकerface *अगरace, पूर्णांक id,
				 bool (*validator)(व्योम *, पूर्णांक), u8 type)
अणु
	व्योम *cs = शून्य;

	जबतक ((cs = snd_usb_find_csपूर्णांक_desc(अगरace->extra, अगरace->extralen,
					     cs, type))) अणु
		अगर (validator(cs, id))
			वापस cs;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool validate_घड़ी_source_v2(व्योम *p, पूर्णांक id)
अणु
	काष्ठा uac_घड़ी_source_descriptor *cs = p;
	वापस cs->bClockID == id;
पूर्ण

अटल bool validate_घड़ी_source_v3(व्योम *p, पूर्णांक id)
अणु
	काष्ठा uac3_घड़ी_source_descriptor *cs = p;
	वापस cs->bClockID == id;
पूर्ण

अटल bool validate_घड़ी_selector_v2(व्योम *p, पूर्णांक id)
अणु
	काष्ठा uac_घड़ी_selector_descriptor *cs = p;
	वापस cs->bClockID == id;
पूर्ण

अटल bool validate_घड़ी_selector_v3(व्योम *p, पूर्णांक id)
अणु
	काष्ठा uac3_घड़ी_selector_descriptor *cs = p;
	वापस cs->bClockID == id;
पूर्ण

अटल bool validate_घड़ी_multiplier_v2(व्योम *p, पूर्णांक id)
अणु
	काष्ठा uac_घड़ी_multiplier_descriptor *cs = p;
	वापस cs->bClockID == id;
पूर्ण

अटल bool validate_घड़ी_multiplier_v3(व्योम *p, पूर्णांक id)
अणु
	काष्ठा uac3_घड़ी_multiplier_descriptor *cs = p;
	वापस cs->bClockID == id;
पूर्ण

#घोषणा DEFINE_FIND_HELPER(name, obj, validator, type)		\
अटल obj *name(काष्ठा usb_host_पूर्णांकerface *अगरace, पूर्णांक id)	\
अणु								\
	वापस find_uac_घड़ी_desc(अगरace, id, validator, type);	\
पूर्ण

DEFINE_FIND_HELPER(snd_usb_find_घड़ी_source,
		   काष्ठा uac_घड़ी_source_descriptor,
		   validate_घड़ी_source_v2, UAC2_CLOCK_SOURCE);
DEFINE_FIND_HELPER(snd_usb_find_घड़ी_source_v3,
		   काष्ठा uac3_घड़ी_source_descriptor,
		   validate_घड़ी_source_v3, UAC3_CLOCK_SOURCE);

DEFINE_FIND_HELPER(snd_usb_find_घड़ी_selector,
		   काष्ठा uac_घड़ी_selector_descriptor,
		   validate_घड़ी_selector_v2, UAC2_CLOCK_SELECTOR);
DEFINE_FIND_HELPER(snd_usb_find_घड़ी_selector_v3,
		   काष्ठा uac3_घड़ी_selector_descriptor,
		   validate_घड़ी_selector_v3, UAC3_CLOCK_SELECTOR);

DEFINE_FIND_HELPER(snd_usb_find_घड़ी_multiplier,
		   काष्ठा uac_घड़ी_multiplier_descriptor,
		   validate_घड़ी_multiplier_v2, UAC2_CLOCK_MULTIPLIER);
DEFINE_FIND_HELPER(snd_usb_find_घड़ी_multiplier_v3,
		   काष्ठा uac3_घड़ी_multiplier_descriptor,
		   validate_घड़ी_multiplier_v3, UAC3_CLOCK_MULTIPLIER);

अटल पूर्णांक uac_घड़ी_selector_get_val(काष्ठा snd_usb_audio *chip, पूर्णांक selector_id)
अणु
	अचिन्हित अक्षर buf;
	पूर्णांक ret;

	ret = snd_usb_ctl_msg(chip->dev, usb_rcvctrlpipe(chip->dev, 0),
			      UAC2_CS_CUR,
			      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_IN,
			      UAC2_CX_CLOCK_SELECTOR << 8,
			      snd_usb_ctrl_पूर्णांकf(chip) | (selector_id << 8),
			      &buf, माप(buf));

	अगर (ret < 0)
		वापस ret;

	वापस buf;
पूर्ण

अटल पूर्णांक uac_घड़ी_selector_set_val(काष्ठा snd_usb_audio *chip, पूर्णांक selector_id,
					अचिन्हित अक्षर pin)
अणु
	पूर्णांक ret;

	ret = snd_usb_ctl_msg(chip->dev, usb_sndctrlpipe(chip->dev, 0),
			      UAC2_CS_CUR,
			      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_OUT,
			      UAC2_CX_CLOCK_SELECTOR << 8,
			      snd_usb_ctrl_पूर्णांकf(chip) | (selector_id << 8),
			      &pin, माप(pin));
	अगर (ret < 0)
		वापस ret;

	अगर (ret != माप(pin)) अणु
		usb_audio_err(chip,
			"setting selector (id %d) unexpected length %d\n",
			selector_id, ret);
		वापस -EINVAL;
	पूर्ण

	ret = uac_घड़ी_selector_get_val(chip, selector_id);
	अगर (ret < 0)
		वापस ret;

	अगर (ret != pin) अणु
		usb_audio_err(chip,
			"setting selector (id %d) to %x failed (current: %d)\n",
			selector_id, pin, ret);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool uac_घड़ी_source_is_valid_quirk(काष्ठा snd_usb_audio *chip,
					    स्थिर काष्ठा audioक्रमmat *fmt,
					    पूर्णांक source_id)
अणु
	bool ret = false;
	पूर्णांक count;
	अचिन्हित अक्षर data;
	काष्ठा usb_device *dev = chip->dev;

	अगर (fmt->protocol == UAC_VERSION_2) अणु
		काष्ठा uac_घड़ी_source_descriptor *cs_desc =
			snd_usb_find_घड़ी_source(chip->ctrl_पूर्णांकf, source_id);

		अगर (!cs_desc)
			वापस false;

		/*
		 * Assume the घड़ी is valid अगर घड़ी source supports only one
		 * single sample rate, the terminal is connected directly to it
		 * (there is no घड़ी selector) and घड़ी type is पूर्णांकernal.
		 * This is to deal with some Denon DJ controllers that always
		 * reports that घड़ी is invalid.
		 */
		अगर (fmt->nr_rates == 1 &&
		    (fmt->घड़ी & 0xff) == cs_desc->bClockID &&
		    (cs_desc->bmAttributes & 0x3) !=
				UAC_CLOCK_SOURCE_TYPE_EXT)
			वापस true;
	पूर्ण

	/*
	 * MOTU MicroBook IIc
	 * Sample rate changes takes more than 2 seconds क्रम this device. Clock
	 * validity request वापसs false during that period.
	 */
	अगर (chip->usb_id == USB_ID(0x07fd, 0x0004)) अणु
		count = 0;

		जबतक ((!ret) && (count < 50)) अणु
			पूर्णांक err;

			msleep(100);

			err = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0), UAC2_CS_CUR,
					      USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_IN,
					      UAC2_CS_CONTROL_CLOCK_VALID << 8,
					      snd_usb_ctrl_पूर्णांकf(chip) | (source_id << 8),
					      &data, माप(data));
			अगर (err < 0) अणु
				dev_warn(&dev->dev,
					 "%s(): cannot get clock validity for id %d\n",
					   __func__, source_id);
				वापस false;
			पूर्ण

			ret = !!data;
			count++;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल bool uac_घड़ी_source_is_valid(काष्ठा snd_usb_audio *chip,
				      स्थिर काष्ठा audioक्रमmat *fmt,
				      पूर्णांक source_id)
अणु
	पूर्णांक err;
	अचिन्हित अक्षर data;
	काष्ठा usb_device *dev = chip->dev;
	u32 bmControls;

	अगर (fmt->protocol == UAC_VERSION_3) अणु
		काष्ठा uac3_घड़ी_source_descriptor *cs_desc =
			snd_usb_find_घड़ी_source_v3(chip->ctrl_पूर्णांकf, source_id);

		अगर (!cs_desc)
			वापस false;
		bmControls = le32_to_cpu(cs_desc->bmControls);
	पूर्ण अन्यथा अणु /* UAC_VERSION_1/2 */
		काष्ठा uac_घड़ी_source_descriptor *cs_desc =
			snd_usb_find_घड़ी_source(chip->ctrl_पूर्णांकf, source_id);

		अगर (!cs_desc)
			वापस false;
		bmControls = cs_desc->bmControls;
	पूर्ण

	/* If a घड़ी source can't tell us whether it's valid, we assume it is */
	अगर (!uac_v2v3_control_is_पढ़ोable(bmControls,
				      UAC2_CS_CONTROL_CLOCK_VALID))
		वापस true;

	err = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0), UAC2_CS_CUR,
			      USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_IN,
			      UAC2_CS_CONTROL_CLOCK_VALID << 8,
			      snd_usb_ctrl_पूर्णांकf(chip) | (source_id << 8),
			      &data, माप(data));

	अगर (err < 0) अणु
		dev_warn(&dev->dev,
			 "%s(): cannot get clock validity for id %d\n",
			   __func__, source_id);
		वापस false;
	पूर्ण

	अगर (data)
		वापस true;
	अन्यथा
		वापस uac_घड़ी_source_is_valid_quirk(chip, fmt, source_id);
पूर्ण

अटल पूर्णांक __uac_घड़ी_find_source(काष्ठा snd_usb_audio *chip,
				   स्थिर काष्ठा audioक्रमmat *fmt, पूर्णांक entity_id,
				   अचिन्हित दीर्घ *visited, bool validate)
अणु
	काष्ठा uac_घड़ी_source_descriptor *source;
	काष्ठा uac_घड़ी_selector_descriptor *selector;
	काष्ठा uac_घड़ी_multiplier_descriptor *multiplier;

	entity_id &= 0xff;

	अगर (test_and_set_bit(entity_id, visited)) अणु
		usb_audio_warn(chip,
			 "%s(): recursive clock topology detected, id %d.\n",
			 __func__, entity_id);
		वापस -EINVAL;
	पूर्ण

	/* first, see अगर the ID we're looking क्रम is a घड़ी source alपढ़ोy */
	source = snd_usb_find_घड़ी_source(chip->ctrl_पूर्णांकf, entity_id);
	अगर (source) अणु
		entity_id = source->bClockID;
		अगर (validate && !uac_घड़ी_source_is_valid(chip, fmt,
								entity_id)) अणु
			usb_audio_err(chip,
				"clock source %d is not valid, cannot use\n",
				entity_id);
			वापस -ENXIO;
		पूर्ण
		वापस entity_id;
	पूर्ण

	selector = snd_usb_find_घड़ी_selector(chip->ctrl_पूर्णांकf, entity_id);
	अगर (selector) अणु
		पूर्णांक ret, i, cur, err;

		अगर (selector->bNrInPins == 1) अणु
			ret = 1;
			जाओ find_source;
		पूर्ण

		/* the entity ID we are looking क्रम is a selector.
		 * find out what it currently selects */
		ret = uac_घड़ी_selector_get_val(chip, selector->bClockID);
		अगर (ret < 0)
			वापस ret;

		/* Selector values are one-based */

		अगर (ret > selector->bNrInPins || ret < 1) अणु
			usb_audio_err(chip,
				"%s(): selector reported illegal value, id %d, ret %d\n",
				__func__, selector->bClockID, ret);

			वापस -EINVAL;
		पूर्ण

	find_source:
		cur = ret;
		ret = __uac_घड़ी_find_source(chip, fmt,
					      selector->baCSourceID[ret - 1],
					      visited, validate);
		अगर (ret > 0) अणु
			err = uac_घड़ी_selector_set_val(chip, entity_id, cur);
			अगर (err < 0)
				वापस err;
		पूर्ण

		अगर (!validate || ret > 0 || !chip->स्वतःघड़ी)
			वापस ret;

		/* The current घड़ी source is invalid, try others. */
		क्रम (i = 1; i <= selector->bNrInPins; i++) अणु
			अगर (i == cur)
				जारी;

			ret = __uac_घड़ी_find_source(chip, fmt,
						      selector->baCSourceID[i - 1],
						      visited, true);
			अगर (ret < 0)
				जारी;

			err = uac_घड़ी_selector_set_val(chip, entity_id, i);
			अगर (err < 0)
				जारी;

			usb_audio_info(chip,
				 "found and selected valid clock source %d\n",
				 ret);
			वापस ret;
		पूर्ण

		वापस -ENXIO;
	पूर्ण

	/* FIXME: multipliers only act as pass-thru element क्रम now */
	multiplier = snd_usb_find_घड़ी_multiplier(chip->ctrl_पूर्णांकf, entity_id);
	अगर (multiplier)
		वापस __uac_घड़ी_find_source(chip, fmt,
					       multiplier->bCSourceID,
					       visited, validate);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __uac3_घड़ी_find_source(काष्ठा snd_usb_audio *chip,
				    स्थिर काष्ठा audioक्रमmat *fmt, पूर्णांक entity_id,
				    अचिन्हित दीर्घ *visited, bool validate)
अणु
	काष्ठा uac3_घड़ी_source_descriptor *source;
	काष्ठा uac3_घड़ी_selector_descriptor *selector;
	काष्ठा uac3_घड़ी_multiplier_descriptor *multiplier;

	entity_id &= 0xff;

	अगर (test_and_set_bit(entity_id, visited)) अणु
		usb_audio_warn(chip,
			 "%s(): recursive clock topology detected, id %d.\n",
			 __func__, entity_id);
		वापस -EINVAL;
	पूर्ण

	/* first, see अगर the ID we're looking क्रम is a घड़ी source alपढ़ोy */
	source = snd_usb_find_घड़ी_source_v3(chip->ctrl_पूर्णांकf, entity_id);
	अगर (source) अणु
		entity_id = source->bClockID;
		अगर (validate && !uac_घड़ी_source_is_valid(chip, fmt,
								entity_id)) अणु
			usb_audio_err(chip,
				"clock source %d is not valid, cannot use\n",
				entity_id);
			वापस -ENXIO;
		पूर्ण
		वापस entity_id;
	पूर्ण

	selector = snd_usb_find_घड़ी_selector_v3(chip->ctrl_पूर्णांकf, entity_id);
	अगर (selector) अणु
		पूर्णांक ret, i, cur, err;

		/* the entity ID we are looking क्रम is a selector.
		 * find out what it currently selects */
		ret = uac_घड़ी_selector_get_val(chip, selector->bClockID);
		अगर (ret < 0)
			वापस ret;

		/* Selector values are one-based */

		अगर (ret > selector->bNrInPins || ret < 1) अणु
			usb_audio_err(chip,
				"%s(): selector reported illegal value, id %d, ret %d\n",
				__func__, selector->bClockID, ret);

			वापस -EINVAL;
		पूर्ण

		cur = ret;
		ret = __uac3_घड़ी_find_source(chip, fmt,
					       selector->baCSourceID[ret - 1],
					       visited, validate);
		अगर (ret > 0) अणु
			err = uac_घड़ी_selector_set_val(chip, entity_id, cur);
			अगर (err < 0)
				वापस err;
		पूर्ण

		अगर (!validate || ret > 0 || !chip->स्वतःघड़ी)
			वापस ret;

		/* The current घड़ी source is invalid, try others. */
		क्रम (i = 1; i <= selector->bNrInPins; i++) अणु
			पूर्णांक err;

			अगर (i == cur)
				जारी;

			ret = __uac3_घड़ी_find_source(chip, fmt,
						       selector->baCSourceID[i - 1],
						       visited, true);
			अगर (ret < 0)
				जारी;

			err = uac_घड़ी_selector_set_val(chip, entity_id, i);
			अगर (err < 0)
				जारी;

			usb_audio_info(chip,
				 "found and selected valid clock source %d\n",
				 ret);
			वापस ret;
		पूर्ण

		वापस -ENXIO;
	पूर्ण

	/* FIXME: multipliers only act as pass-thru element क्रम now */
	multiplier = snd_usb_find_घड़ी_multiplier_v3(chip->ctrl_पूर्णांकf,
						      entity_id);
	अगर (multiplier)
		वापस __uac3_घड़ी_find_source(chip, fmt,
						multiplier->bCSourceID,
						visited, validate);

	वापस -EINVAL;
पूर्ण

/*
 * For all kinds of sample rate settings and other device queries,
 * the घड़ी source (end-leaf) must be used. However, घड़ी selectors,
 * घड़ी multipliers and sample rate converters may be specअगरied as
 * घड़ी source input to terminal. This functions walks the घड़ी path
 * to its end and tries to find the source.
 *
 * The 'visited' bitfield is used पूर्णांकernally to detect recursive loops.
 *
 * Returns the घड़ी source UnitID (>=0) on success, or an error.
 */
पूर्णांक snd_usb_घड़ी_find_source(काष्ठा snd_usb_audio *chip,
			      स्थिर काष्ठा audioक्रमmat *fmt, bool validate)
अणु
	DECLARE_BITMAP(visited, 256);
	स_रखो(visited, 0, माप(visited));

	चयन (fmt->protocol) अणु
	हाल UAC_VERSION_2:
		वापस __uac_घड़ी_find_source(chip, fmt, fmt->घड़ी, visited,
					       validate);
	हाल UAC_VERSION_3:
		वापस __uac3_घड़ी_find_source(chip, fmt, fmt->घड़ी, visited,
					       validate);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक set_sample_rate_v1(काष्ठा snd_usb_audio *chip,
			      स्थिर काष्ठा audioक्रमmat *fmt, पूर्णांक rate)
अणु
	काष्ठा usb_device *dev = chip->dev;
	अचिन्हित अक्षर data[3];
	पूर्णांक err, crate;

	/* अगर endpoपूर्णांक करोesn't have sampling rate control, bail out */
	अगर (!(fmt->attributes & UAC_EP_CS_ATTR_SAMPLE_RATE))
		वापस 0;

	data[0] = rate;
	data[1] = rate >> 8;
	data[2] = rate >> 16;
	err = snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0), UAC_SET_CUR,
			      USB_TYPE_CLASS | USB_RECIP_ENDPOINT | USB_सूची_OUT,
			      UAC_EP_CS_ATTR_SAMPLE_RATE << 8,
			      fmt->endpoपूर्णांक, data, माप(data));
	अगर (err < 0) अणु
		dev_err(&dev->dev, "%d:%d: cannot set freq %d to ep %#x\n",
			fmt->अगरace, fmt->altsetting, rate, fmt->endpoपूर्णांक);
		वापस err;
	पूर्ण

	/* Don't check the sample rate for devices which we know don't
	 * support पढ़ोing */
	अगर (snd_usb_get_sample_rate_quirk(chip))
		वापस 0;
	/* the firmware is likely buggy, करोn't repeat to fail too many बार */
	अगर (chip->sample_rate_पढ़ो_error > 2)
		वापस 0;

	err = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0), UAC_GET_CUR,
			      USB_TYPE_CLASS | USB_RECIP_ENDPOINT | USB_सूची_IN,
			      UAC_EP_CS_ATTR_SAMPLE_RATE << 8,
			      fmt->endpoपूर्णांक, data, माप(data));
	अगर (err < 0) अणु
		dev_err(&dev->dev, "%d:%d: cannot get freq at ep %#x\n",
			fmt->अगरace, fmt->altsetting, fmt->endpoपूर्णांक);
		chip->sample_rate_पढ़ो_error++;
		वापस 0; /* some devices करोn't support पढ़ोing */
	पूर्ण

	crate = data[0] | (data[1] << 8) | (data[2] << 16);
	अगर (!crate) अणु
		dev_info(&dev->dev, "failed to read current rate; disabling the check\n");
		chip->sample_rate_पढ़ो_error = 3; /* three strikes, see above */
		वापस 0;
	पूर्ण

	अगर (crate != rate) अणु
		dev_warn(&dev->dev, "current rate %d is different from the runtime rate %d\n", crate, rate);
		// runसमय->rate = crate;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_sample_rate_v2v3(काष्ठा snd_usb_audio *chip, पूर्णांक अगरace,
			      पूर्णांक altsetting, पूर्णांक घड़ी)
अणु
	काष्ठा usb_device *dev = chip->dev;
	__le32 data;
	पूर्णांक err;

	err = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0), UAC2_CS_CUR,
			      USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_IN,
			      UAC2_CS_CONTROL_SAM_FREQ << 8,
			      snd_usb_ctrl_पूर्णांकf(chip) | (घड़ी << 8),
			      &data, माप(data));
	अगर (err < 0) अणु
		dev_warn(&dev->dev, "%d:%d: cannot get freq (v2/v3): err %d\n",
			 अगरace, altsetting, err);
		वापस 0;
	पूर्ण

	वापस le32_to_cpu(data);
पूर्ण

/*
 * Try to set the given sample rate:
 *
 * Return 0 अगर the घड़ी source is पढ़ो-only, the actual rate on success,
 * or a negative error code.
 *
 * This function माला_लो called from क्रमmat.c to validate each sample rate, too.
 * Hence no message is shown upon error
 */
पूर्णांक snd_usb_set_sample_rate_v2v3(काष्ठा snd_usb_audio *chip,
				 स्थिर काष्ठा audioक्रमmat *fmt,
				 पूर्णांक घड़ी, पूर्णांक rate)
अणु
	bool ग_लिखोable;
	u32 bmControls;
	__le32 data;
	पूर्णांक err;

	अगर (fmt->protocol == UAC_VERSION_3) अणु
		काष्ठा uac3_घड़ी_source_descriptor *cs_desc;

		cs_desc = snd_usb_find_घड़ी_source_v3(chip->ctrl_पूर्णांकf, घड़ी);
		bmControls = le32_to_cpu(cs_desc->bmControls);
	पूर्ण अन्यथा अणु
		काष्ठा uac_घड़ी_source_descriptor *cs_desc;

		cs_desc = snd_usb_find_घड़ी_source(chip->ctrl_पूर्णांकf, घड़ी);
		bmControls = cs_desc->bmControls;
	पूर्ण

	ग_लिखोable = uac_v2v3_control_is_ग_लिखोable(bmControls,
						  UAC2_CS_CONTROL_SAM_FREQ);
	अगर (!ग_लिखोable)
		वापस 0;

	data = cpu_to_le32(rate);
	err = snd_usb_ctl_msg(chip->dev, usb_sndctrlpipe(chip->dev, 0), UAC2_CS_CUR,
			      USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_OUT,
			      UAC2_CS_CONTROL_SAM_FREQ << 8,
			      snd_usb_ctrl_पूर्णांकf(chip) | (घड़ी << 8),
			      &data, माप(data));
	अगर (err < 0)
		वापस err;

	वापस get_sample_rate_v2v3(chip, fmt->अगरace, fmt->altsetting, घड़ी);
पूर्ण

अटल पूर्णांक set_sample_rate_v2v3(काष्ठा snd_usb_audio *chip,
				स्थिर काष्ठा audioक्रमmat *fmt, पूर्णांक rate)
अणु
	पूर्णांक cur_rate, prev_rate;
	पूर्णांक घड़ी;

	/* First, try to find a valid घड़ी. This may trigger
	 * स्वतःmatic घड़ी selection अगर the current घड़ी is not
	 * valid.
	 */
	घड़ी = snd_usb_घड़ी_find_source(chip, fmt, true);
	अगर (घड़ी < 0) अणु
		/* We did not find a valid घड़ी, but that might be
		 * because the current sample rate करोes not match an
		 * बाह्यal घड़ी source. Try again without validation
		 * and we will करो another validation after setting the
		 * rate.
		 */
		घड़ी = snd_usb_घड़ी_find_source(chip, fmt, false);
		अगर (घड़ी < 0)
			वापस घड़ी;
	पूर्ण

	prev_rate = get_sample_rate_v2v3(chip, fmt->अगरace, fmt->altsetting, घड़ी);
	अगर (prev_rate == rate)
		जाओ validation;

	cur_rate = snd_usb_set_sample_rate_v2v3(chip, fmt, घड़ी, rate);
	अगर (cur_rate < 0) अणु
		usb_audio_err(chip,
			      "%d:%d: cannot set freq %d (v2/v3): err %d\n",
			      fmt->अगरace, fmt->altsetting, rate, cur_rate);
		वापस cur_rate;
	पूर्ण

	अगर (!cur_rate)
		cur_rate = prev_rate;

	अगर (cur_rate != rate) अणु
		usb_audio_dbg(chip,
			      "%d:%d: freq mismatch: req %d, clock runs @%d\n",
			      fmt->अगरace, fmt->altsetting, rate, cur_rate);
		/* जारी processing */
	पूर्ण

validation:
	/* validate घड़ी after rate change */
	अगर (!uac_घड़ी_source_is_valid(chip, fmt, घड़ी))
		वापस -ENXIO;
	वापस 0;
पूर्ण

पूर्णांक snd_usb_init_sample_rate(काष्ठा snd_usb_audio *chip,
			     स्थिर काष्ठा audioक्रमmat *fmt, पूर्णांक rate)
अणु
	usb_audio_dbg(chip, "%d:%d Set sample rate %d, clock %d\n",
		      fmt->अगरace, fmt->altsetting, rate, fmt->घड़ी);

	चयन (fmt->protocol) अणु
	हाल UAC_VERSION_1:
	शेष:
		वापस set_sample_rate_v1(chip, fmt, rate);

	हाल UAC_VERSION_3:
		अगर (chip->badd_profile >= UAC3_FUNCTION_SUBCLASS_GENERIC_IO) अणु
			अगर (rate != UAC3_BADD_SAMPLING_RATE)
				वापस -ENXIO;
			अन्यथा
				वापस 0;
		पूर्ण
		fallthrough;
	हाल UAC_VERSION_2:
		वापस set_sample_rate_v2v3(chip, fmt, rate);
	पूर्ण
पूर्ण

