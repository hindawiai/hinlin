<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2004 James Courtier-Dutton <James@superbug.demon.co.uk>
 *  Driver CA0106 chips. e.g. Sound Blaster Audigy LS and Live 24bit
 *  Version: 0.0.18
 *
 *  FEATURES currently supported:
 *    See ca0106_मुख्य.c क्रम features.
 * 
 *  Changelog:
 *    Support पूर्णांकerrupts per period.
 *    Removed noise from Center/LFE channel when in Analog mode.
 *    Rename and हटाओ mixer controls.
 *  0.0.6
 *    Use separate card based DMA buffer क्रम periods table list.
 *  0.0.7
 *    Change हटाओ and नाम ctrls पूर्णांकo lists.
 *  0.0.8
 *    Try to fix capture sources.
 *  0.0.9
 *    Fix AC3 output.
 *    Enable S32_LE क्रमmat support.
 *  0.0.10
 *    Enable playback 48000 and 96000 rates. (Rates other that these करो not work, even with "plug:front".)
 *  0.0.11
 *    Add Model name recognition.
 *  0.0.12
 *    Correct पूर्णांकerrupt timing. पूर्णांकerrupt at end of period, instead of in the middle of a playback period.
 *    Remove redundent "voice" handling.
 *  0.0.13
 *    Single trigger call क्रम multi channels.
 *  0.0.14
 *    Set limits based on what the sound card hardware can करो.
 *    playback periods_min=2, periods_max=8
 *    capture hw स्थिरraपूर्णांकs require period_size = n * 64 bytes.
 *    playback hw स्थिरraपूर्णांकs require period_size = n * 64 bytes.
 *  0.0.15
 *    Separated ca0106.c पूर्णांकo separate functional .c files.
 *  0.0.16
 *    Modअगरied Copyright message.
 *  0.0.17
 *    Implement Mic and Line in Capture.
 *  0.0.18
 *    Add support क्रम mute control on SB Live 24bit (cards w/ SPI DAC)
 *
 *  This code was initially based on code from ALSA's emu10k1x.c which is:
 *  Copyright (c) by Francisco Moraes <fmoraes@nc.rr.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/info.h>
#समावेश <sound/tlv.h>
#समावेश <linux/पन.स>

#समावेश "ca0106.h"

अटल व्योम ca0106_spdअगर_enable(काष्ठा snd_ca0106 *emu)
अणु
	अचिन्हित पूर्णांक val;

	अगर (emu->spdअगर_enable) अणु
		/* Digital */
		snd_ca0106_ptr_ग_लिखो(emu, SPDIF_SELECT1, 0, 0xf);
		snd_ca0106_ptr_ग_लिखो(emu, SPDIF_SELECT2, 0, 0x0b000000);
		val = snd_ca0106_ptr_पढ़ो(emu, CAPTURE_CONTROL, 0) & ~0x1000;
		snd_ca0106_ptr_ग_लिखो(emu, CAPTURE_CONTROL, 0, val);
		val = inl(emu->port + GPIO) & ~0x101;
		outl(val, emu->port + GPIO);

	पूर्ण अन्यथा अणु
		/* Analog */
		snd_ca0106_ptr_ग_लिखो(emu, SPDIF_SELECT1, 0, 0xf);
		snd_ca0106_ptr_ग_लिखो(emu, SPDIF_SELECT2, 0, 0x000f0000);
		val = snd_ca0106_ptr_पढ़ो(emu, CAPTURE_CONTROL, 0) | 0x1000;
		snd_ca0106_ptr_ग_लिखो(emu, CAPTURE_CONTROL, 0, val);
		val = inl(emu->port + GPIO) | 0x101;
		outl(val, emu->port + GPIO);
	पूर्ण
पूर्ण

अटल व्योम ca0106_set_capture_source(काष्ठा snd_ca0106 *emu)
अणु
	अचिन्हित पूर्णांक val = emu->capture_source;
	अचिन्हित पूर्णांक source, mask;
	source = (val << 28) | (val << 24) | (val << 20) | (val << 16);
	mask = snd_ca0106_ptr_पढ़ो(emu, CAPTURE_SOURCE, 0) & 0xffff;
	snd_ca0106_ptr_ग_लिखो(emu, CAPTURE_SOURCE, 0, source | mask);
पूर्ण

अटल व्योम ca0106_set_i2c_capture_source(काष्ठा snd_ca0106 *emu,
					  अचिन्हित पूर्णांक val, पूर्णांक क्रमce)
अणु
	अचिन्हित पूर्णांक ngain, ogain;
	u32 source;

	snd_ca0106_i2c_ग_लिखो(emu, ADC_MUX, 0); /* Mute input */
	ngain = emu->i2c_capture_volume[val][0]; /* Left */
	ogain = emu->i2c_capture_volume[emu->i2c_capture_source][0]; /* Left */
	अगर (क्रमce || ngain != ogain)
		snd_ca0106_i2c_ग_लिखो(emu, ADC_ATTEN_ADCL, ngain & 0xff);
	ngain = emu->i2c_capture_volume[val][1]; /* Right */
	ogain = emu->i2c_capture_volume[emu->i2c_capture_source][1]; /* Right */
	अगर (क्रमce || ngain != ogain)
		snd_ca0106_i2c_ग_लिखो(emu, ADC_ATTEN_ADCR, ngain & 0xff);
	source = 1 << val;
	snd_ca0106_i2c_ग_लिखो(emu, ADC_MUX, source); /* Set source */
	emu->i2c_capture_source = val;
पूर्ण

अटल व्योम ca0106_set_capture_mic_line_in(काष्ठा snd_ca0106 *emu)
अणु
	u32 पंचांगp;

	अगर (emu->capture_mic_line_in) अणु
		/* snd_ca0106_i2c_ग_लिखो(emu, ADC_MUX, 0); */ /* Mute input */
		पंचांगp = inl(emu->port+GPIO) & ~0x400;
		पंचांगp = पंचांगp | 0x400;
		outl(पंचांगp, emu->port+GPIO);
		/* snd_ca0106_i2c_ग_लिखो(emu, ADC_MUX, ADC_MUX_MIC); */
	पूर्ण अन्यथा अणु
		/* snd_ca0106_i2c_ग_लिखो(emu, ADC_MUX, 0); */ /* Mute input */
		पंचांगp = inl(emu->port+GPIO) & ~0x400;
		outl(पंचांगp, emu->port+GPIO);
		/* snd_ca0106_i2c_ग_लिखो(emu, ADC_MUX, ADC_MUX_LINEIN); */
	पूर्ण
पूर्ण

अटल व्योम ca0106_set_spdअगर_bits(काष्ठा snd_ca0106 *emu, पूर्णांक idx)
अणु
	snd_ca0106_ptr_ग_लिखो(emu, SPCS0 + idx, 0, emu->spdअगर_str_bits[idx]);
पूर्ण

/*
 */
अटल स्थिर DECLARE_TLV_DB_SCALE(snd_ca0106_db_scale1, -5175, 25, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(snd_ca0106_db_scale2, -10350, 50, 1);

#घोषणा snd_ca0106_shared_spdअगर_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ca0106_shared_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = emu->spdअगर_enable;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_shared_spdअगर_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change = 0;

	val = !!ucontrol->value.पूर्णांकeger.value[0];
	change = (emu->spdअगर_enable != val);
	अगर (change) अणु
		emu->spdअगर_enable = val;
		ca0106_spdअगर_enable(emu);
	पूर्ण
        वापस change;
पूर्ण

अटल पूर्णांक snd_ca0106_capture_source_info(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[6] = अणु
		"IEC958 out", "i2s mixer out", "IEC958 in", "i2s in", "AC97 in", "SRC out"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 6, texts);
पूर्ण

अटल पूर्णांक snd_ca0106_capture_source_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = emu->capture_source;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_capture_source_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change = 0;

	val = ucontrol->value.क्रमागतerated.item[0] ;
	अगर (val >= 6)
		वापस -EINVAL;
	change = (emu->capture_source != val);
	अगर (change) अणु
		emu->capture_source = val;
		ca0106_set_capture_source(emu);
	पूर्ण
        वापस change;
पूर्ण

अटल पूर्णांक snd_ca0106_i2c_capture_source_info(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु
		"Phone", "Mic", "Line in", "Aux"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 4, texts);
पूर्ण

अटल पूर्णांक snd_ca0106_i2c_capture_source_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = emu->i2c_capture_source;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_i2c_capture_source_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक source_id;
	पूर्णांक change = 0;
	/* If the capture source has changed,
	 * update the capture volume from the cached value
	 * क्रम the particular source.
	 */
	source_id = ucontrol->value.क्रमागतerated.item[0] ;
	अगर (source_id >= 4)
		वापस -EINVAL;
	change = (emu->i2c_capture_source != source_id);
	अगर (change) अणु
		ca0106_set_i2c_capture_source(emu, source_id, 0);
	पूर्ण
        वापस change;
पूर्ण

अटल पूर्णांक snd_ca0106_capture_line_in_side_out_info(काष्ठा snd_kcontrol *kcontrol,
					       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु "Side out", "Line in" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक snd_ca0106_capture_mic_line_in_info(काष्ठा snd_kcontrol *kcontrol,
					       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु "Line in", "Mic in" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक snd_ca0106_capture_mic_line_in_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = emu->capture_mic_line_in;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_capture_mic_line_in_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change = 0;

	val = ucontrol->value.क्रमागतerated.item[0] ;
	अगर (val > 1)
		वापस -EINVAL;
	change = (emu->capture_mic_line_in != val);
	अगर (change) अणु
		emu->capture_mic_line_in = val;
		ca0106_set_capture_mic_line_in(emu);
	पूर्ण
        वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ca0106_capture_mic_line_in =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"Shared Mic/Line in Capture Switch",
	.info =		snd_ca0106_capture_mic_line_in_info,
	.get =		snd_ca0106_capture_mic_line_in_get,
	.put =		snd_ca0106_capture_mic_line_in_put
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ca0106_capture_line_in_side_out =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"Shared Line in/Side out Capture Switch",
	.info =		snd_ca0106_capture_line_in_side_out_info,
	.get =		snd_ca0106_capture_mic_line_in_get,
	.put =		snd_ca0106_capture_mic_line_in_put
पूर्ण;


अटल पूर्णांक snd_ca0106_spdअगर_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल व्योम decode_spdअगर_bits(अचिन्हित अक्षर *status, अचिन्हित पूर्णांक bits)
अणु
	status[0] = (bits >> 0) & 0xff;
	status[1] = (bits >> 8) & 0xff;
	status[2] = (bits >> 16) & 0xff;
	status[3] = (bits >> 24) & 0xff;
पूर्ण

अटल पूर्णांक snd_ca0106_spdअगर_get_शेष(काष्ठा snd_kcontrol *kcontrol,
                                 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);

	decode_spdअगर_bits(ucontrol->value.iec958.status,
			  emu->spdअगर_bits[idx]);
        वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_spdअगर_get_stream(काष्ठा snd_kcontrol *kcontrol,
                                 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);

	decode_spdअगर_bits(ucontrol->value.iec958.status,
			  emu->spdअगर_str_bits[idx]);
        वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_spdअगर_get_mask(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = 0xff;
	ucontrol->value.iec958.status[1] = 0xff;
	ucontrol->value.iec958.status[2] = 0xff;
	ucontrol->value.iec958.status[3] = 0xff;
        वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक encode_spdअगर_bits(अचिन्हित अक्षर *status)
अणु
	वापस ((अचिन्हित पूर्णांक)status[0] << 0) |
		((अचिन्हित पूर्णांक)status[1] << 8) |
		((अचिन्हित पूर्णांक)status[2] << 16) |
		((अचिन्हित पूर्णांक)status[3] << 24);
पूर्ण

अटल पूर्णांक snd_ca0106_spdअगर_put_शेष(काष्ठा snd_kcontrol *kcontrol,
                                 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अचिन्हित पूर्णांक val;

	val = encode_spdअगर_bits(ucontrol->value.iec958.status);
	अगर (val != emu->spdअगर_bits[idx]) अणु
		emu->spdअगर_bits[idx] = val;
		/* FIXME: this isn't safe, but needed to keep the compatibility
		 * with older alsa-lib config
		 */
		emu->spdअगर_str_bits[idx] = val;
		ca0106_set_spdअगर_bits(emu, idx);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_spdअगर_put_stream(काष्ठा snd_kcontrol *kcontrol,
                                 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अचिन्हित पूर्णांक val;

	val = encode_spdअगर_bits(ucontrol->value.iec958.status);
	अगर (val != emu->spdअगर_str_bits[idx]) अणु
		emu->spdअगर_str_bits[idx] = val;
		ca0106_set_spdअगर_bits(emu, idx);
		वापस 1;
	पूर्ण
        वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_volume_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
        uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
        uinfo->count = 2;
        uinfo->value.पूर्णांकeger.min = 0;
        uinfo->value.पूर्णांकeger.max = 255;
        वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_volume_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
        काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
        अचिन्हित पूर्णांक value;
	पूर्णांक channel_id, reg;

	channel_id = (kcontrol->निजी_value >> 8) & 0xff;
	reg = kcontrol->निजी_value & 0xff;

        value = snd_ca0106_ptr_पढ़ो(emu, reg, channel_id);
        ucontrol->value.पूर्णांकeger.value[0] = 0xff - ((value >> 24) & 0xff); /* Left */
        ucontrol->value.पूर्णांकeger.value[1] = 0xff - ((value >> 16) & 0xff); /* Right */
        वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_volume_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
        काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
        अचिन्हित पूर्णांक oval, nval;
	पूर्णांक channel_id, reg;

	channel_id = (kcontrol->निजी_value >> 8) & 0xff;
	reg = kcontrol->निजी_value & 0xff;

	oval = snd_ca0106_ptr_पढ़ो(emu, reg, channel_id);
	nval = ((0xff - ucontrol->value.पूर्णांकeger.value[0]) << 24) |
		((0xff - ucontrol->value.पूर्णांकeger.value[1]) << 16);
        nval |= ((0xff - ucontrol->value.पूर्णांकeger.value[0]) << 8) |
		((0xff - ucontrol->value.पूर्णांकeger.value[1]) );
	अगर (oval == nval)
		वापस 0;
	snd_ca0106_ptr_ग_लिखो(emu, reg, channel_id, nval);
	वापस 1;
पूर्ण

अटल पूर्णांक snd_ca0106_i2c_volume_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
        uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
        uinfo->count = 2;
        uinfo->value.पूर्णांकeger.min = 0;
        uinfo->value.पूर्णांकeger.max = 255;
        वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_i2c_volume_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
        काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
	पूर्णांक source_id;

	source_id = kcontrol->निजी_value;

        ucontrol->value.पूर्णांकeger.value[0] = emu->i2c_capture_volume[source_id][0];
        ucontrol->value.पूर्णांकeger.value[1] = emu->i2c_capture_volume[source_id][1];
        वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_i2c_volume_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
        काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
        अचिन्हित पूर्णांक ogain;
        अचिन्हित पूर्णांक ngain;
	पूर्णांक source_id;
	पूर्णांक change = 0;

	source_id = kcontrol->निजी_value;
	ogain = emu->i2c_capture_volume[source_id][0]; /* Left */
	ngain = ucontrol->value.पूर्णांकeger.value[0];
	अगर (ngain > 0xff)
		वापस -EINVAL;
	अगर (ogain != ngain) अणु
		अगर (emu->i2c_capture_source == source_id)
			snd_ca0106_i2c_ग_लिखो(emu, ADC_ATTEN_ADCL, ((ngain) & 0xff) );
		emu->i2c_capture_volume[source_id][0] = ucontrol->value.पूर्णांकeger.value[0];
		change = 1;
	पूर्ण
	ogain = emu->i2c_capture_volume[source_id][1]; /* Right */
	ngain = ucontrol->value.पूर्णांकeger.value[1];
	अगर (ngain > 0xff)
		वापस -EINVAL;
	अगर (ogain != ngain) अणु
		अगर (emu->i2c_capture_source == source_id)
			snd_ca0106_i2c_ग_लिखो(emu, ADC_ATTEN_ADCR, ((ngain) & 0xff));
		emu->i2c_capture_volume[source_id][1] = ucontrol->value.पूर्णांकeger.value[1];
		change = 1;
	पूर्ण

	वापस change;
पूर्ण

#घोषणा spi_mute_info	snd_ctl_boolean_mono_info

अटल पूर्णांक spi_mute_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक reg = kcontrol->निजी_value >> SPI_REG_SHIFT;
	अचिन्हित पूर्णांक bit = kcontrol->निजी_value & SPI_REG_MASK;

	ucontrol->value.पूर्णांकeger.value[0] = !(emu->spi_dac_reg[reg] & bit);
	वापस 0;
पूर्ण

अटल पूर्णांक spi_mute_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक reg = kcontrol->निजी_value >> SPI_REG_SHIFT;
	अचिन्हित पूर्णांक bit = kcontrol->निजी_value & SPI_REG_MASK;
	पूर्णांक ret;

	ret = emu->spi_dac_reg[reg] & bit;
	अगर (ucontrol->value.पूर्णांकeger.value[0]) अणु
		अगर (!ret)	/* bit alपढ़ोy cleared, करो nothing */
			वापस 0;
		emu->spi_dac_reg[reg] &= ~bit;
	पूर्ण अन्यथा अणु
		अगर (ret)	/* bit alपढ़ोy set, करो nothing */
			वापस 0;
		emu->spi_dac_reg[reg] |= bit;
	पूर्ण

	ret = snd_ca0106_spi_ग_लिखो(emu, emu->spi_dac_reg[reg]);
	वापस ret ? -EINVAL : 1;
पूर्ण

#घोषणा CA_VOLUME(xname,chid,reg) \
अणु								\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,	\
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |		\
	          SNDRV_CTL_ELEM_ACCESS_TLV_READ,		\
	.info =	 snd_ca0106_volume_info,			\
	.get =   snd_ca0106_volume_get,				\
	.put =   snd_ca0106_volume_put,				\
	.tlv = अणु .p = snd_ca0106_db_scale1 पूर्ण,			\
	.निजी_value = ((chid) << 8) | (reg)			\
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ca0106_volume_ctls[] = अणु
	CA_VOLUME("Analog Front Playback Volume",
		  CONTROL_FRONT_CHANNEL, PLAYBACK_VOLUME2),
        CA_VOLUME("Analog Rear Playback Volume",
		  CONTROL_REAR_CHANNEL, PLAYBACK_VOLUME2),
	CA_VOLUME("Analog Center/LFE Playback Volume",
		  CONTROL_CENTER_LFE_CHANNEL, PLAYBACK_VOLUME2),
        CA_VOLUME("Analog Side Playback Volume",
		  CONTROL_UNKNOWN_CHANNEL, PLAYBACK_VOLUME2),

        CA_VOLUME("IEC958 Front Playback Volume",
		  CONTROL_FRONT_CHANNEL, PLAYBACK_VOLUME1),
	CA_VOLUME("IEC958 Rear Playback Volume",
		  CONTROL_REAR_CHANNEL, PLAYBACK_VOLUME1),
	CA_VOLUME("IEC958 Center/LFE Playback Volume",
		  CONTROL_CENTER_LFE_CHANNEL, PLAYBACK_VOLUME1),
	CA_VOLUME("IEC958 Unknown Playback Volume",
		  CONTROL_UNKNOWN_CHANNEL, PLAYBACK_VOLUME1),

        CA_VOLUME("CAPTURE feedback Playback Volume",
		  1, CAPTURE_CONTROL),

	अणु
		.access =	SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace =        SNDRV_CTL_ELEM_IFACE_PCM,
		.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,MASK),
		.count =	4,
		.info =         snd_ca0106_spdअगर_info,
		.get =          snd_ca0106_spdअगर_get_mask
	पूर्ण,
	अणु
		.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
		.name =		"IEC958 Playback Switch",
		.info =		snd_ca0106_shared_spdअगर_info,
		.get =		snd_ca0106_shared_spdअगर_get,
		.put =		snd_ca0106_shared_spdअगर_put
	पूर्ण,
	अणु
		.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
		.name =		"Digital Source Capture Enum",
		.info =		snd_ca0106_capture_source_info,
		.get =		snd_ca0106_capture_source_get,
		.put =		snd_ca0106_capture_source_put
	पूर्ण,
	अणु
		.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
		.name =		"Analog Source Capture Enum",
		.info =		snd_ca0106_i2c_capture_source_info,
		.get =		snd_ca0106_i2c_capture_source_get,
		.put =		snd_ca0106_i2c_capture_source_put
	पूर्ण,
	अणु
		.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
		.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
		.count =	4,
		.info =         snd_ca0106_spdअगर_info,
		.get =          snd_ca0106_spdअगर_get_शेष,
		.put =          snd_ca0106_spdअगर_put_शेष
	पूर्ण,
	अणु
		.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
		.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,PCM_STREAM),
		.count =	4,
		.info =         snd_ca0106_spdअगर_info,
		.get =          snd_ca0106_spdअगर_get_stream,
		.put =          snd_ca0106_spdअगर_put_stream
	पूर्ण,
पूर्ण;

#घोषणा I2C_VOLUME(xname,chid) \
अणु								\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,	\
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |		\
	          SNDRV_CTL_ELEM_ACCESS_TLV_READ,		\
	.info =  snd_ca0106_i2c_volume_info,			\
	.get =   snd_ca0106_i2c_volume_get,			\
	.put =   snd_ca0106_i2c_volume_put,			\
	.tlv = अणु .p = snd_ca0106_db_scale2 पूर्ण,			\
	.निजी_value = chid					\
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ca0106_volume_i2c_adc_ctls[] = अणु
        I2C_VOLUME("Phone Capture Volume", 0),
        I2C_VOLUME("Mic Capture Volume", 1),
        I2C_VOLUME("Line in Capture Volume", 2),
        I2C_VOLUME("Aux Capture Volume", 3),
पूर्ण;

अटल स्थिर पूर्णांक spi_dmute_reg[] = अणु
	SPI_DMUTE0_REG,
	SPI_DMUTE1_REG,
	SPI_DMUTE2_REG,
	0,
	SPI_DMUTE4_REG,
पूर्ण;
अटल स्थिर पूर्णांक spi_dmute_bit[] = अणु
	SPI_DMUTE0_BIT,
	SPI_DMUTE1_BIT,
	SPI_DMUTE2_BIT,
	0,
	SPI_DMUTE4_BIT,
पूर्ण;

अटल काष्ठा snd_kcontrol_new
snd_ca0106_volume_spi_dac_ctl(स्थिर काष्ठा snd_ca0106_details *details,
			      पूर्णांक channel_id)
अणु
	काष्ठा snd_kcontrol_new spi_चयन = अणु0पूर्ण;
	पूर्णांक reg, bit;
	पूर्णांक dac_id;

	spi_चयन.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	spi_चयन.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	spi_चयन.info = spi_mute_info;
	spi_चयन.get = spi_mute_get;
	spi_चयन.put = spi_mute_put;

	चयन (channel_id) अणु
	हाल PCM_FRONT_CHANNEL:
		spi_चयन.name = "Analog Front Playback Switch";
		dac_id = (details->spi_dac & 0xf000) >> (4 * 3);
		अवरोध;
	हाल PCM_REAR_CHANNEL:
		spi_चयन.name = "Analog Rear Playback Switch";
		dac_id = (details->spi_dac & 0x0f00) >> (4 * 2);
		अवरोध;
	हाल PCM_CENTER_LFE_CHANNEL:
		spi_चयन.name = "Analog Center/LFE Playback Switch";
		dac_id = (details->spi_dac & 0x00f0) >> (4 * 1);
		अवरोध;
	हाल PCM_UNKNOWN_CHANNEL:
		spi_चयन.name = "Analog Side Playback Switch";
		dac_id = (details->spi_dac & 0x000f) >> (4 * 0);
		अवरोध;
	शेष:
		/* Unused channel */
		spi_चयन.name = शून्य;
		dac_id = 0;
	पूर्ण
	reg = spi_dmute_reg[dac_id];
	bit = spi_dmute_bit[dac_id];

	spi_चयन.निजी_value = (reg << SPI_REG_SHIFT) | bit;

	वापस spi_चयन;
पूर्ण

अटल पूर्णांक हटाओ_ctl(काष्ठा snd_card *card, स्थिर अक्षर *name)
अणु
	काष्ठा snd_ctl_elem_id id;
	स_रखो(&id, 0, माप(id));
	म_नकल(id.name, name);
	id.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	वापस snd_ctl_हटाओ_id(card, &id);
पूर्ण

अटल काष्ठा snd_kcontrol *ctl_find(काष्ठा snd_card *card, स्थिर अक्षर *name)
अणु
	काष्ठा snd_ctl_elem_id sid;
	स_रखो(&sid, 0, माप(sid));
	/* FIXME: म_नकल is bad. */
	म_नकल(sid.name, name);
	sid.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	वापस snd_ctl_find_id(card, &sid);
पूर्ण

अटल पूर्णांक नाम_ctl(काष्ठा snd_card *card, स्थिर अक्षर *src, स्थिर अक्षर *dst)
अणु
	काष्ठा snd_kcontrol *kctl = ctl_find(card, src);
	अगर (kctl) अणु
		म_नकल(kctl->id.name, dst);
		वापस 0;
	पूर्ण
	वापस -ENOENT;
पूर्ण

#घोषणा ADD_CTLS(emu, ctls)						\
	करो अणु								\
		पूर्णांक i, _err;						\
		क्रम (i = 0; i < ARRAY_SIZE(ctls); i++) अणु		\
			_err = snd_ctl_add(card, snd_ctl_new1(&ctls[i], emu)); \
			अगर (_err < 0)					\
				वापस _err;				\
		पूर्ण							\
	पूर्ण जबतक (0)

अटल
DECLARE_TLV_DB_SCALE(snd_ca0106_master_db_scale, -6375, 25, 1);

अटल स्थिर अक्षर * स्थिर follower_vols[] = अणु
	"Analog Front Playback Volume",
        "Analog Rear Playback Volume",
	"Analog Center/LFE Playback Volume",
        "Analog Side Playback Volume",
        "IEC958 Front Playback Volume",
	"IEC958 Rear Playback Volume",
	"IEC958 Center/LFE Playback Volume",
	"IEC958 Unknown Playback Volume",
        "CAPTURE feedback Playback Volume",
	शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर follower_sws[] = अणु
	"Analog Front Playback Switch",
	"Analog Rear Playback Switch",
	"Analog Center/LFE Playback Switch",
	"Analog Side Playback Switch",
	"IEC958 Playback Switch",
	शून्य
पूर्ण;

अटल व्योम add_followers(काष्ठा snd_card *card,
			  काष्ठा snd_kcontrol *master, स्थिर अक्षर * स्थिर *list)
अणु
	क्रम (; *list; list++) अणु
		काष्ठा snd_kcontrol *follower = ctl_find(card, *list);
		अगर (follower)
			snd_ctl_add_follower(master, follower);
	पूर्ण
पूर्ण

पूर्णांक snd_ca0106_mixer(काष्ठा snd_ca0106 *emu)
अणु
	पूर्णांक err;
        काष्ठा snd_card *card = emu->card;
	स्थिर अक्षर * स्थिर *c;
	काष्ठा snd_kcontrol *vmaster;
	अटल स्थिर अक्षर * स्थिर ca0106_हटाओ_ctls[] = अणु
		"Master Mono Playback Switch",
		"Master Mono Playback Volume",
		"3D Control - Switch",
		"3D Control Sigmatel - Depth",
		"PCM Playback Switch",
		"PCM Playback Volume",
		"CD Playback Switch",
		"CD Playback Volume",
		"Phone Playback Switch",
		"Phone Playback Volume",
		"Video Playback Switch",
		"Video Playback Volume",
		"Beep Playback Switch",
		"Beep Playback Volume",
		"Mono Output Select",
		"Capture Source",
		"Capture Switch",
		"Capture Volume",
		"External Amplifier",
		"Sigmatel 4-Speaker Stereo Playback Switch",
		"Surround Phase Inversion Playback Switch",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर ca0106_नाम_ctls[] = अणु
		"Master Playback Switch", "Capture Switch",
		"Master Playback Volume", "Capture Volume",
		"Line Playback Switch", "AC97 Line Capture Switch",
		"Line Playback Volume", "AC97 Line Capture Volume",
		"Aux Playback Switch", "AC97 Aux Capture Switch",
		"Aux Playback Volume", "AC97 Aux Capture Volume",
		"Mic Playback Switch", "AC97 Mic Capture Switch",
		"Mic Playback Volume", "AC97 Mic Capture Volume",
		"Mic Select", "AC97 Mic Select",
		"Mic Boost (+20dB)", "AC97 Mic Boost (+20dB)",
		शून्य
	पूर्ण;
#अगर 1
	क्रम (c = ca0106_हटाओ_ctls; *c; c++)
		हटाओ_ctl(card, *c);
	क्रम (c = ca0106_नाम_ctls; *c; c += 2)
		नाम_ctl(card, c[0], c[1]);
#पूर्ण_अगर

	ADD_CTLS(emu, snd_ca0106_volume_ctls);
	अगर (emu->details->i2c_adc == 1) अणु
		ADD_CTLS(emu, snd_ca0106_volume_i2c_adc_ctls);
		अगर (emu->details->gpio_type == 1)
			err = snd_ctl_add(card, snd_ctl_new1(&snd_ca0106_capture_mic_line_in, emu));
		अन्यथा  /* gpio_type == 2 */
			err = snd_ctl_add(card, snd_ctl_new1(&snd_ca0106_capture_line_in_side_out, emu));
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (emu->details->spi_dac) अणु
		पूर्णांक i;
		क्रम (i = 0;; i++) अणु
			काष्ठा snd_kcontrol_new ctl;
			ctl = snd_ca0106_volume_spi_dac_ctl(emu->details, i);
			अगर (!ctl.name)
				अवरोध;
			err = snd_ctl_add(card, snd_ctl_new1(&ctl, emu));
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	/* Create भव master controls */
	vmaster = snd_ctl_make_भव_master("Master Playback Volume",
					      snd_ca0106_master_db_scale);
	अगर (!vmaster)
		वापस -ENOMEM;
	err = snd_ctl_add(card, vmaster);
	अगर (err < 0)
		वापस err;
	add_followers(card, vmaster, follower_vols);

	अगर (emu->details->spi_dac) अणु
		vmaster = snd_ctl_make_भव_master("Master Playback Switch",
						      शून्य);
		अगर (!vmaster)
			वापस -ENOMEM;
		err = snd_ctl_add(card, vmaster);
		अगर (err < 0)
			वापस err;
		add_followers(card, vmaster, follower_sws);
	पूर्ण

	म_नकल(card->mixername, "CA0106");
        वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
काष्ठा ca0106_vol_tbl अणु
	अचिन्हित पूर्णांक channel_id;
	अचिन्हित पूर्णांक reg;
पूर्ण;

अटल स्थिर काष्ठा ca0106_vol_tbl saved_volumes[NUM_SAVED_VOLUMES] = अणु
	अणु CONTROL_FRONT_CHANNEL, PLAYBACK_VOLUME2 पूर्ण,
	अणु CONTROL_REAR_CHANNEL, PLAYBACK_VOLUME2 पूर्ण,
	अणु CONTROL_CENTER_LFE_CHANNEL, PLAYBACK_VOLUME2 पूर्ण,
	अणु CONTROL_UNKNOWN_CHANNEL, PLAYBACK_VOLUME2 पूर्ण,
	अणु CONTROL_FRONT_CHANNEL, PLAYBACK_VOLUME1 पूर्ण,
	अणु CONTROL_REAR_CHANNEL, PLAYBACK_VOLUME1 पूर्ण,
	अणु CONTROL_CENTER_LFE_CHANNEL, PLAYBACK_VOLUME1 पूर्ण,
	अणु CONTROL_UNKNOWN_CHANNEL, PLAYBACK_VOLUME1 पूर्ण,
	अणु 1, CAPTURE_CONTROL पूर्ण,
पूर्ण;

व्योम snd_ca0106_mixer_suspend(काष्ठा snd_ca0106 *chip)
अणु
	पूर्णांक i;

	/* save volumes */
	क्रम (i = 0; i < NUM_SAVED_VOLUMES; i++)
		chip->saved_vol[i] =
			snd_ca0106_ptr_पढ़ो(chip, saved_volumes[i].reg,
					    saved_volumes[i].channel_id);
पूर्ण

व्योम snd_ca0106_mixer_resume(काष्ठा snd_ca0106  *chip)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_SAVED_VOLUMES; i++)
		snd_ca0106_ptr_ग_लिखो(chip, saved_volumes[i].reg,
				     saved_volumes[i].channel_id,
				     chip->saved_vol[i]);

	ca0106_spdअगर_enable(chip);
	ca0106_set_capture_source(chip);
	ca0106_set_i2c_capture_source(chip, chip->i2c_capture_source, 1);
	क्रम (i = 0; i < 4; i++)
		ca0106_set_spdअगर_bits(chip, i);
	अगर (chip->details->i2c_adc)
		ca0106_set_capture_mic_line_in(chip);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */
