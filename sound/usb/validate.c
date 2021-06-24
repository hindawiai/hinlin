<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
//
// Validation of USB-audio class descriptors
//

#समावेश <linux/init.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/audपन.स>
#समावेश <linux/usb/audio-v2.h>
#समावेश <linux/usb/audio-v3.h>
#समावेश <linux/usb/midi.h>
#समावेश "usbaudio.h"
#समावेश "helper.h"

काष्ठा usb_desc_validator अणु
	अचिन्हित अक्षर protocol;
	अचिन्हित अक्षर type;
	bool (*func)(स्थिर व्योम *p, स्थिर काष्ठा usb_desc_validator *v);
	माप_प्रकार size;
पूर्ण;

#घोषणा UAC_VERSION_ALL		(अचिन्हित अक्षर)(-1)

/* UAC1 only */
अटल bool validate_uac1_header(स्थिर व्योम *p,
				 स्थिर काष्ठा usb_desc_validator *v)
अणु
	स्थिर काष्ठा uac1_ac_header_descriptor *d = p;

	वापस d->bLength >= माप(*d) &&
		d->bLength >= माप(*d) + d->bInCollection;
पूर्ण

/* क्रम mixer unit; covering all UACs */
अटल bool validate_mixer_unit(स्थिर व्योम *p,
				स्थिर काष्ठा usb_desc_validator *v)
अणु
	स्थिर काष्ठा uac_mixer_unit_descriptor *d = p;
	माप_प्रकार len;

	अगर (d->bLength < माप(*d) || !d->bNrInPins)
		वापस false;
	len = माप(*d) + d->bNrInPins;
	/* We can't determine the biपंचांगap size only from this unit descriptor,
	 * so just check with the reमुख्यing length.
	 * The actual biपंचांगap is checked at mixer unit parser.
	 */
	चयन (v->protocol) अणु
	हाल UAC_VERSION_1:
	शेष:
		len += 2 + 1; /* wChannelConfig, iChannelNames */
		/* bmControls[n*m] */
		len += 1; /* iMixer */
		अवरोध;
	हाल UAC_VERSION_2:
		len += 4 + 1; /* bmChannelConfig, iChannelNames */
		/* bmMixerControls[n*m] */
		len += 1 + 1; /* bmControls, iMixer */
		अवरोध;
	हाल UAC_VERSION_3:
		len += 2; /* wClusterDescrID */
		/* bmMixerControls[n*m] */
		अवरोध;
	पूर्ण
	वापस d->bLength >= len;
पूर्ण

/* both क्रम processing and extension units; covering all UACs */
अटल bool validate_processing_unit(स्थिर व्योम *p,
				     स्थिर काष्ठा usb_desc_validator *v)
अणु
	स्थिर काष्ठा uac_processing_unit_descriptor *d = p;
	स्थिर अचिन्हित अक्षर *hdr = p;
	माप_प्रकार len, m;

	अगर (d->bLength < माप(*d))
		वापस false;
	len = माप(*d) + d->bNrInPins;
	अगर (d->bLength < len)
		वापस false;
	चयन (v->protocol) अणु
	हाल UAC_VERSION_1:
	शेष:
		/* bNrChannels, wChannelConfig, iChannelNames */
		len += 1 + 2 + 1;
		अगर (d->bLength < len + 1) /* bControlSize */
			वापस false;
		m = hdr[len];
		len += 1 + m + 1; /* bControlSize, bmControls, iProcessing */
		अवरोध;
	हाल UAC_VERSION_2:
		/* bNrChannels, bmChannelConfig, iChannelNames */
		len += 1 + 4 + 1;
		अगर (v->type == UAC2_PROCESSING_UNIT_V2)
			len += 2; /* bmControls -- 2 bytes क्रम PU */
		अन्यथा
			len += 1; /* bmControls -- 1 byte क्रम EU */
		len += 1; /* iProcessing */
		अवरोध;
	हाल UAC_VERSION_3:
		/* wProcessingDescrStr, bmControls */
		len += 2 + 4;
		अवरोध;
	पूर्ण
	अगर (d->bLength < len)
		वापस false;

	चयन (v->protocol) अणु
	हाल UAC_VERSION_1:
	शेष:
		अगर (v->type == UAC1_EXTENSION_UNIT)
			वापस true; /* OK */
		चयन (le16_to_cpu(d->wProcessType)) अणु
		हाल UAC_PROCESS_UP_DOWNMIX:
		हाल UAC_PROCESS_DOLBY_PROLOGIC:
			अगर (d->bLength < len + 1) /* bNrModes */
				वापस false;
			m = hdr[len];
			len += 1 + m * 2; /* bNrModes, waModes(n) */
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल UAC_VERSION_2:
		अगर (v->type == UAC2_EXTENSION_UNIT_V2)
			वापस true; /* OK */
		चयन (le16_to_cpu(d->wProcessType)) अणु
		हाल UAC2_PROCESS_UP_DOWNMIX:
		हाल UAC2_PROCESS_DOLBY_PROLOCIC: /* SiC! */
			अगर (d->bLength < len + 1) /* bNrModes */
				वापस false;
			m = hdr[len];
			len += 1 + m * 4; /* bNrModes, daModes(n) */
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल UAC_VERSION_3:
		अगर (v->type == UAC3_EXTENSION_UNIT) अणु
			len += 2; /* wClusterDescrID */
			अवरोध;
		पूर्ण
		चयन (le16_to_cpu(d->wProcessType)) अणु
		हाल UAC3_PROCESS_UP_DOWNMIX:
			अगर (d->bLength < len + 1) /* bNrModes */
				वापस false;
			m = hdr[len];
			len += 1 + m * 2; /* bNrModes, waClusterDescrID(n) */
			अवरोध;
		हाल UAC3_PROCESS_MULTI_FUNCTION:
			len += 2 + 4; /* wClusterDescrID, bmAlgorighms */
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (d->bLength < len)
		वापस false;

	वापस true;
पूर्ण

/* both क्रम selector and घड़ी selector units; covering all UACs */
अटल bool validate_selector_unit(स्थिर व्योम *p,
				   स्थिर काष्ठा usb_desc_validator *v)
अणु
	स्थिर काष्ठा uac_selector_unit_descriptor *d = p;
	माप_प्रकार len;

	अगर (d->bLength < माप(*d))
		वापस false;
	len = माप(*d) + d->bNrInPins;
	चयन (v->protocol) अणु
	हाल UAC_VERSION_1:
	शेष:
		len += 1; /* iSelector */
		अवरोध;
	हाल UAC_VERSION_2:
		len += 1 + 1; /* bmControls, iSelector */
		अवरोध;
	हाल UAC_VERSION_3:
		len += 4 + 2; /* bmControls, wSelectorDescrStr */
		अवरोध;
	पूर्ण
	वापस d->bLength >= len;
पूर्ण

अटल bool validate_uac1_feature_unit(स्थिर व्योम *p,
				       स्थिर काष्ठा usb_desc_validator *v)
अणु
	स्थिर काष्ठा uac_feature_unit_descriptor *d = p;

	अगर (d->bLength < माप(*d) || !d->bControlSize)
		वापस false;
	/* at least bmaControls(0) क्रम master channel + iFeature */
	वापस d->bLength >= माप(*d) + d->bControlSize + 1;
पूर्ण

अटल bool validate_uac2_feature_unit(स्थिर व्योम *p,
				       स्थिर काष्ठा usb_desc_validator *v)
अणु
	स्थिर काष्ठा uac2_feature_unit_descriptor *d = p;

	अगर (d->bLength < माप(*d))
		वापस false;
	/* at least bmaControls(0) क्रम master channel + iFeature */
	वापस d->bLength >= माप(*d) + 4 + 1;
पूर्ण

अटल bool validate_uac3_feature_unit(स्थिर व्योम *p,
				       स्थिर काष्ठा usb_desc_validator *v)
अणु
	स्थिर काष्ठा uac3_feature_unit_descriptor *d = p;

	अगर (d->bLength < माप(*d))
		वापस false;
	/* at least bmaControls(0) क्रम master channel + wFeatureDescrStr */
	वापस d->bLength >= माप(*d) + 4 + 2;
पूर्ण

अटल bool validate_midi_out_jack(स्थिर व्योम *p,
				   स्थिर काष्ठा usb_desc_validator *v)
अणु
	स्थिर काष्ठा usb_midi_out_jack_descriptor *d = p;

	वापस d->bLength >= माप(*d) &&
		d->bLength >= माप(*d) + d->bNrInputPins * 2;
पूर्ण

#घोषणा FIXED(p, t, s) अणु .protocol = (p), .type = (t), .size = माप(s) पूर्ण
#घोषणा FUNC(p, t, f) अणु .protocol = (p), .type = (t), .func = (f) पूर्ण

अटल स्थिर काष्ठा usb_desc_validator audio_validators[] = अणु
	/* UAC1 */
	FUNC(UAC_VERSION_1, UAC_HEADER, validate_uac1_header),
	FIXED(UAC_VERSION_1, UAC_INPUT_TERMINAL,
	      काष्ठा uac_input_terminal_descriptor),
	FIXED(UAC_VERSION_1, UAC_OUTPUT_TERMINAL,
	      काष्ठा uac1_output_terminal_descriptor),
	FUNC(UAC_VERSION_1, UAC_MIXER_UNIT, validate_mixer_unit),
	FUNC(UAC_VERSION_1, UAC_SELECTOR_UNIT, validate_selector_unit),
	FUNC(UAC_VERSION_1, UAC_FEATURE_UNIT, validate_uac1_feature_unit),
	FUNC(UAC_VERSION_1, UAC1_PROCESSING_UNIT, validate_processing_unit),
	FUNC(UAC_VERSION_1, UAC1_EXTENSION_UNIT, validate_processing_unit),

	/* UAC2 */
	FIXED(UAC_VERSION_2, UAC_HEADER, काष्ठा uac2_ac_header_descriptor),
	FIXED(UAC_VERSION_2, UAC_INPUT_TERMINAL,
	      काष्ठा uac2_input_terminal_descriptor),
	FIXED(UAC_VERSION_2, UAC_OUTPUT_TERMINAL,
	      काष्ठा uac2_output_terminal_descriptor),
	FUNC(UAC_VERSION_2, UAC_MIXER_UNIT, validate_mixer_unit),
	FUNC(UAC_VERSION_2, UAC_SELECTOR_UNIT, validate_selector_unit),
	FUNC(UAC_VERSION_2, UAC_FEATURE_UNIT, validate_uac2_feature_unit),
	/* UAC_VERSION_2, UAC2_EFFECT_UNIT: not implemented yet */
	FUNC(UAC_VERSION_2, UAC2_PROCESSING_UNIT_V2, validate_processing_unit),
	FUNC(UAC_VERSION_2, UAC2_EXTENSION_UNIT_V2, validate_processing_unit),
	FIXED(UAC_VERSION_2, UAC2_CLOCK_SOURCE,
	      काष्ठा uac_घड़ी_source_descriptor),
	FUNC(UAC_VERSION_2, UAC2_CLOCK_SELECTOR, validate_selector_unit),
	FIXED(UAC_VERSION_2, UAC2_CLOCK_MULTIPLIER,
	      काष्ठा uac_घड़ी_multiplier_descriptor),
	/* UAC_VERSION_2, UAC2_SAMPLE_RATE_CONVERTER: not implemented yet */

	/* UAC3 */
	FIXED(UAC_VERSION_2, UAC_HEADER, काष्ठा uac3_ac_header_descriptor),
	FIXED(UAC_VERSION_3, UAC_INPUT_TERMINAL,
	      काष्ठा uac3_input_terminal_descriptor),
	FIXED(UAC_VERSION_3, UAC_OUTPUT_TERMINAL,
	      काष्ठा uac3_output_terminal_descriptor),
	/* UAC_VERSION_3, UAC3_EXTENDED_TERMINAL: not implemented yet */
	FUNC(UAC_VERSION_3, UAC3_MIXER_UNIT, validate_mixer_unit),
	FUNC(UAC_VERSION_3, UAC3_SELECTOR_UNIT, validate_selector_unit),
	FUNC(UAC_VERSION_3, UAC_FEATURE_UNIT, validate_uac3_feature_unit),
	/*  UAC_VERSION_3, UAC3_EFFECT_UNIT: not implemented yet */
	FUNC(UAC_VERSION_3, UAC3_PROCESSING_UNIT, validate_processing_unit),
	FUNC(UAC_VERSION_3, UAC3_EXTENSION_UNIT, validate_processing_unit),
	FIXED(UAC_VERSION_3, UAC3_CLOCK_SOURCE,
	      काष्ठा uac3_घड़ी_source_descriptor),
	FUNC(UAC_VERSION_3, UAC3_CLOCK_SELECTOR, validate_selector_unit),
	FIXED(UAC_VERSION_3, UAC3_CLOCK_MULTIPLIER,
	      काष्ठा uac3_घड़ी_multiplier_descriptor),
	/* UAC_VERSION_3, UAC3_SAMPLE_RATE_CONVERTER: not implemented yet */
	/* UAC_VERSION_3, UAC3_CONNECTORS: not implemented yet */
	अणु पूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा usb_desc_validator midi_validators[] = अणु
	FIXED(UAC_VERSION_ALL, USB_MS_HEADER,
	      काष्ठा usb_ms_header_descriptor),
	FIXED(UAC_VERSION_ALL, USB_MS_MIDI_IN_JACK,
	      काष्ठा usb_midi_in_jack_descriptor),
	FUNC(UAC_VERSION_ALL, USB_MS_MIDI_OUT_JACK,
	     validate_midi_out_jack),
	अणु पूर्ण /* terminator */
पूर्ण;


/* Validate the given unit descriptor, वापस true अगर it's OK */
अटल bool validate_desc(अचिन्हित अक्षर *hdr, पूर्णांक protocol,
			  स्थिर काष्ठा usb_desc_validator *v)
अणु
	अगर (hdr[1] != USB_DT_CS_INTERFACE)
		वापस true; /* करोn't care */

	क्रम (; v->type; v++) अणु
		अगर (v->type == hdr[2] &&
		    (v->protocol == UAC_VERSION_ALL ||
		     v->protocol == protocol)) अणु
			अगर (v->func)
				वापस v->func(hdr, v);
			/* check क्रम the fixed size */
			वापस hdr[0] >= v->size;
		पूर्ण
	पूर्ण

	वापस true; /* not matching, skip validation */
पूर्ण

bool snd_usb_validate_audio_desc(व्योम *p, पूर्णांक protocol)
अणु
	अचिन्हित अक्षर *c = p;
	bool valid;

	valid = validate_desc(p, protocol, audio_validators);
	अगर (!valid && snd_usb_skip_validation) अणु
		prपूर्णांक_hex_dump(KERN_ERR, "USB-audio: buggy audio desc: ",
			       DUMP_PREFIX_NONE, 16, 1, c, c[0], true);
		valid = true;
	पूर्ण
	वापस valid;
पूर्ण

bool snd_usb_validate_midi_desc(व्योम *p)
अणु
	अचिन्हित अक्षर *c = p;
	bool valid;

	valid = validate_desc(p, UAC_VERSION_1, midi_validators);
	अगर (!valid && snd_usb_skip_validation) अणु
		prपूर्णांक_hex_dump(KERN_ERR, "USB-audio: buggy midi desc: ",
			       DUMP_PREFIX_NONE, 16, 1, c, c[0], true);
		valid = true;
	पूर्ण
	वापस valid;
पूर्ण
