<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Universal Interface क्रम Intel High Definition Audio Codec
 *
 * HD audio पूर्णांकerface patch क्रम Silicon Lअसल 3054/5 modem codec
 *
 * Copyright (c) 2005 Sasha Khapyorsky <sashak@alsa-project.org>
 *                    Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"

/* si3054 verbs */
#घोषणा SI3054_VERB_READ_NODE  0x900
#घोषणा SI3054_VERB_WRITE_NODE 0x100

/* si3054 nodes (रेजिस्टरs) */
#घोषणा SI3054_EXTENDED_MID    2
#घोषणा SI3054_LINE_RATE       3
#घोषणा SI3054_LINE_LEVEL      4
#घोषणा SI3054_GPIO_CFG        5
#घोषणा SI3054_GPIO_POLARITY   6
#घोषणा SI3054_GPIO_STICKY     7
#घोषणा SI3054_GPIO_WAKEUP     8
#घोषणा SI3054_GPIO_STATUS     9
#घोषणा SI3054_GPIO_CONTROL   10
#घोषणा SI3054_MISC_AFE       11
#घोषणा SI3054_CHIPID         12
#घोषणा SI3054_LINE_CFG1      13
#घोषणा SI3054_LINE_STATUS    14
#घोषणा SI3054_DC_TERMINATION 15
#घोषणा SI3054_LINE_CONFIG    16
#घोषणा SI3054_CALLPROG_ATT   17
#घोषणा SI3054_SQ_CONTROL     18
#घोषणा SI3054_MISC_CONTROL   19
#घोषणा SI3054_RING_CTRL1     20
#घोषणा SI3054_RING_CTRL2     21

/* extended MID */
#घोषणा SI3054_MEI_READY 0xf

/* line level */
#घोषणा SI3054_ATAG_MASK 0x00f0
#घोषणा SI3054_DTAG_MASK 0xf000

/* GPIO bits */
#घोषणा SI3054_GPIO_OH    0x0001
#घोषणा SI3054_GPIO_CID   0x0002

/* chipid and revisions */
#घोषणा SI3054_CHIPID_CODEC_REV_MASK 0x000f
#घोषणा SI3054_CHIPID_DAA_REV_MASK   0x00f0
#घोषणा SI3054_CHIPID_INTERNATIONAL  0x0100
#घोषणा SI3054_CHIPID_DAA_ID         0x0f00
#घोषणा SI3054_CHIPID_CODEC_ID      (1<<12)

/* si3054 codec रेजिस्टरs (nodes) access macros */
#घोषणा GET_REG(codec,reg) (snd_hda_codec_पढ़ो(codec,reg,0,SI3054_VERB_READ_NODE,0))
#घोषणा SET_REG(codec,reg,val) (snd_hda_codec_ग_लिखो(codec,reg,0,SI3054_VERB_WRITE_NODE,val))
#घोषणा SET_REG_CACHE(codec,reg,val) \
	snd_hda_codec_ग_लिखो_cache(codec,reg,0,SI3054_VERB_WRITE_NODE,val)


काष्ठा si3054_spec अणु
	अचिन्हित पूर्णांकernational;
पूर्ण;


/*
 * Modem mixer
 */

#घोषणा PRIVATE_VALUE(reg,mask) ((reg<<16)|(mask&0xffff))
#घोषणा PRIVATE_REG(val) ((val>>16)&0xffff)
#घोषणा PRIVATE_MASK(val) (val&0xffff)

#घोषणा si3054_चयन_info	snd_ctl_boolean_mono_info

अटल पूर्णांक si3054_चयन_get(काष्ठा snd_kcontrol *kcontrol,
		               काष्ठा snd_ctl_elem_value *uvalue)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	u16 reg  = PRIVATE_REG(kcontrol->निजी_value);
	u16 mask = PRIVATE_MASK(kcontrol->निजी_value);
	uvalue->value.पूर्णांकeger.value[0] = (GET_REG(codec, reg)) & mask ? 1 : 0 ;
	वापस 0;
पूर्ण

अटल पूर्णांक si3054_चयन_put(काष्ठा snd_kcontrol *kcontrol,
		               काष्ठा snd_ctl_elem_value *uvalue)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	u16 reg  = PRIVATE_REG(kcontrol->निजी_value);
	u16 mask = PRIVATE_MASK(kcontrol->निजी_value);
	अगर (uvalue->value.पूर्णांकeger.value[0])
		SET_REG_CACHE(codec, reg, (GET_REG(codec, reg)) | mask);
	अन्यथा
		SET_REG_CACHE(codec, reg, (GET_REG(codec, reg)) & ~mask);
	वापस 0;
पूर्ण

#घोषणा SI3054_KCONTROL(kname,reg,mask) अणु \
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = kname, \
	.subdevice = HDA_SUBDEV_NID_FLAG | reg, \
	.info = si3054_चयन_info, \
	.get  = si3054_चयन_get, \
	.put  = si3054_चयन_put, \
	.निजी_value = PRIVATE_VALUE(reg,mask), \
पूर्ण
		

अटल स्थिर काष्ठा snd_kcontrol_new si3054_modem_mixer[] = अणु
	SI3054_KCONTROL("Off-hook Switch", SI3054_GPIO_CONTROL, SI3054_GPIO_OH),
	SI3054_KCONTROL("Caller ID Switch", SI3054_GPIO_CONTROL, SI3054_GPIO_CID),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक si3054_build_controls(काष्ठा hda_codec *codec)
अणु
	वापस snd_hda_add_new_ctls(codec, si3054_modem_mixer);
पूर्ण


/*
 * PCM callbacks
 */

अटल पूर्णांक si3054_pcm_prepare(काष्ठा hda_pcm_stream *hinfo,
			      काष्ठा hda_codec *codec,
			      अचिन्हित पूर्णांक stream_tag,
			      अचिन्हित पूर्णांक क्रमmat,
			      काष्ठा snd_pcm_substream *substream)
अणु
	u16 val;

	SET_REG(codec, SI3054_LINE_RATE, substream->runसमय->rate);
	val = GET_REG(codec, SI3054_LINE_LEVEL);
	val &= 0xff << (8 * (substream->stream != SNDRV_PCM_STREAM_PLAYBACK));
	val |= ((stream_tag & 0xf) << 4) << (8 * (substream->stream == SNDRV_PCM_STREAM_PLAYBACK));
	SET_REG(codec, SI3054_LINE_LEVEL, val);

	snd_hda_codec_setup_stream(codec, hinfo->nid,
				   stream_tag, 0, क्रमmat);
	वापस 0;
पूर्ण

अटल पूर्णांक si3054_pcm_खोलो(काष्ठा hda_pcm_stream *hinfo,
			   काष्ठा hda_codec *codec,
			    काष्ठा snd_pcm_substream *substream)
अणु
	अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु 8000, 9600, 16000 पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_rates = अणु
		.count = ARRAY_SIZE(rates),
		.list = rates,
		.mask = 0,
	पूर्ण;
	substream->runसमय->hw.period_bytes_min = 80;
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE, &hw_स्थिरraपूर्णांकs_rates);
पूर्ण


अटल स्थिर काष्ठा hda_pcm_stream si3054_pcm = अणु
	.substreams = 1,
	.channels_min = 1,
	.channels_max = 1,
	.nid = 0x1,
	.rates = SNDRV_PCM_RATE_8000|SNDRV_PCM_RATE_16000|SNDRV_PCM_RATE_KNOT,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.maxbps = 16,
	.ops = अणु
		.खोलो = si3054_pcm_खोलो,
		.prepare = si3054_pcm_prepare,
	पूर्ण,
पूर्ण;


अटल पूर्णांक si3054_build_pcms(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_pcm *info;

	info = snd_hda_codec_pcm_new(codec, "Si3054 Modem");
	अगर (!info)
		वापस -ENOMEM;
	info->stream[SNDRV_PCM_STREAM_PLAYBACK] = si3054_pcm;
	info->stream[SNDRV_PCM_STREAM_CAPTURE]  = si3054_pcm;
	info->stream[SNDRV_PCM_STREAM_PLAYBACK].nid = codec->core.mfg;
	info->stream[SNDRV_PCM_STREAM_CAPTURE].nid = codec->core.mfg;
	info->pcm_type = HDA_PCM_TYPE_MODEM;
	वापस 0;
पूर्ण


/*
 * Init part
 */

अटल पूर्णांक si3054_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा si3054_spec *spec = codec->spec;
	अचिन्हित रुको_count;
	u16 val;

	अगर (snd_hdac_regmap_add_venकरोr_verb(&codec->core,
					    SI3054_VERB_WRITE_NODE))
		वापस -ENOMEM;

	snd_hda_codec_ग_लिखो(codec, AC_NODE_ROOT, 0, AC_VERB_SET_CODEC_RESET, 0);
	snd_hda_codec_ग_लिखो(codec, codec->core.mfg, 0, AC_VERB_SET_STREAM_FORMAT, 0);
	SET_REG(codec, SI3054_LINE_RATE, 9600);
	SET_REG(codec, SI3054_LINE_LEVEL, SI3054_DTAG_MASK|SI3054_ATAG_MASK);
	SET_REG(codec, SI3054_EXTENDED_MID, 0);

	रुको_count = 10;
	करो अणु
		msleep(2);
		val = GET_REG(codec, SI3054_EXTENDED_MID);
	पूर्ण जबतक ((val & SI3054_MEI_READY) != SI3054_MEI_READY && रुको_count--);

	अगर((val&SI3054_MEI_READY) != SI3054_MEI_READY) अणु
		codec_err(codec, "si3054: cannot initialize. EXT MID = %04x\n", val);
		/* let's pray that this is no fatal error */
		/* वापस -EACCES; */
	पूर्ण

	SET_REG(codec, SI3054_GPIO_POLARITY, 0xffff);
	SET_REG(codec, SI3054_GPIO_CFG, 0x0);
	SET_REG(codec, SI3054_MISC_AFE, 0);
	SET_REG(codec, SI3054_LINE_CFG1,0x200);

	अगर((GET_REG(codec,SI3054_LINE_STATUS) & (1<<6)) == 0) अणु
		codec_dbg(codec,
			  "Link Frame Detect(FDT) is not ready (line status: %04x)\n",
				GET_REG(codec,SI3054_LINE_STATUS));
	पूर्ण

	spec->पूर्णांकernational = GET_REG(codec, SI3054_CHIPID) & SI3054_CHIPID_INTERNATIONAL;

	वापस 0;
पूर्ण

अटल व्योम si3054_मुक्त(काष्ठा hda_codec *codec)
अणु
	kमुक्त(codec->spec);
पूर्ण


/*
 */

अटल स्थिर काष्ठा hda_codec_ops si3054_patch_ops = अणु
	.build_controls = si3054_build_controls,
	.build_pcms = si3054_build_pcms,
	.init = si3054_init,
	.मुक्त = si3054_मुक्त,
पूर्ण;

अटल पूर्णांक patch_si3054(काष्ठा hda_codec *codec)
अणु
	काष्ठा si3054_spec *spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (spec == शून्य)
		वापस -ENOMEM;
	codec->spec = spec;
	codec->patch_ops = si3054_patch_ops;
	वापस 0;
पूर्ण

/*
 * patch entries
 */
अटल स्थिर काष्ठा hda_device_id snd_hda_id_si3054[] = अणु
	HDA_CODEC_ENTRY(0x163c3055, "Si3054", patch_si3054),
	HDA_CODEC_ENTRY(0x163c3155, "Si3054", patch_si3054),
	HDA_CODEC_ENTRY(0x11c13026, "Si3054", patch_si3054),
	HDA_CODEC_ENTRY(0x11c13055, "Si3054", patch_si3054),
	HDA_CODEC_ENTRY(0x11c13155, "Si3054", patch_si3054),
	HDA_CODEC_ENTRY(0x10573055, "Si3054", patch_si3054),
	HDA_CODEC_ENTRY(0x10573057, "Si3054", patch_si3054),
	HDA_CODEC_ENTRY(0x10573155, "Si3054", patch_si3054),
	/* VIA HDA on Clevo m540 */
	HDA_CODEC_ENTRY(0x11063288, "Si3054", patch_si3054),
	/* Asus A8J Modem (SM56) */
	HDA_CODEC_ENTRY(0x15433155, "Si3054", patch_si3054),
	/* LG LW20 modem */
	HDA_CODEC_ENTRY(0x18540018, "Si3054", patch_si3054),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hdaudio, snd_hda_id_si3054);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Si3054 HD-audio modem codec");

अटल काष्ठा hda_codec_driver si3054_driver = अणु
	.id = snd_hda_id_si3054,
पूर्ण;

module_hda_codec_driver(si3054_driver);
