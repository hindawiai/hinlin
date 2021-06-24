<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HD audio पूर्णांकerface patch क्रम Cirrus Logic CS420x chip
 *
 * Copyright (c) 2009 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <sound/tlv.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"
#समावेश "hda_auto_parser.h"
#समावेश "hda_jack.h"
#समावेश "hda_generic.h"

/*
 */

#घोषणा CS42L42_HP_CH     (2U)
#घोषणा CS42L42_HS_MIC_CH (1U)

काष्ठा cs_spec अणु
	काष्ठा hda_gen_spec gen;

	अचिन्हित पूर्णांक gpio_mask;
	अचिन्हित पूर्णांक gpio_dir;
	अचिन्हित पूर्णांक gpio_data;
	अचिन्हित पूर्णांक gpio_eapd_hp; /* EAPD GPIO bit क्रम headphones */
	अचिन्हित पूर्णांक gpio_eapd_speaker; /* EAPD GPIO bit क्रम speakers */

	/* CS421x */
	अचिन्हित पूर्णांक spdअगर_detect:1;
	अचिन्हित पूर्णांक spdअगर_present:1;
	अचिन्हित पूर्णांक sense_b:1;
	hda_nid_t venकरोr_nid;

	/* क्रम MBP SPDIF control */
	पूर्णांक (*spdअगर_sw_put)(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol);

	अचिन्हित पूर्णांक cs42l42_hp_jack_in:1;
	अचिन्हित पूर्णांक cs42l42_mic_jack_in:1;
	अचिन्हित पूर्णांक cs42l42_volume_init:1;
	अक्षर cs42l42_hp_volume[CS42L42_HP_CH];
	अक्षर cs42l42_hs_mic_volume[CS42L42_HS_MIC_CH];

	काष्ठा mutex cs8409_i2c_mux;

	/* verb exec op override */
	पूर्णांक (*exec_verb)(काष्ठा hdac_device *dev, अचिन्हित पूर्णांक cmd,
				 अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक *res);
पूर्ण;

/* available models with CS420x */
क्रमागत अणु
	CS420X_MBP53,
	CS420X_MBP55,
	CS420X_IMAC27,
	CS420X_GPIO_13,
	CS420X_GPIO_23,
	CS420X_MBP101,
	CS420X_MBP81,
	CS420X_MBA42,
	CS420X_AUTO,
	/* aliases */
	CS420X_IMAC27_122 = CS420X_GPIO_23,
	CS420X_APPLE = CS420X_GPIO_13,
पूर्ण;

/* CS421x boards */
क्रमागत अणु
	CS421X_CDB4210,
	CS421X_SENSE_B,
	CS421X_STUMPY,
पूर्ण;

/* Venकरोr-specअगरic processing widget */
#घोषणा CS420X_VENDOR_NID	0x11
#घोषणा CS_DIG_OUT1_PIN_NID	0x10
#घोषणा CS_DIG_OUT2_PIN_NID	0x15
#घोषणा CS_DMIC1_PIN_NID	0x0e
#घोषणा CS_DMIC2_PIN_NID	0x12

/* coef indices */
#घोषणा IDX_SPDIF_STAT		0x0000
#घोषणा IDX_SPDIF_CTL		0x0001
#घोषणा IDX_ADC_CFG		0x0002
/* SZC biपंचांगask, 4 modes below:
 * 0 = immediate,
 * 1 = digital immediate, analog zero-cross
 * 2 = digtail & analog soft-ramp
 * 3 = digital soft-ramp, analog zero-cross
 */
#घोषणा   CS_COEF_ADC_SZC_MASK		(3 << 0)
#घोषणा   CS_COEF_ADC_MIC_SZC_MODE	(3 << 0) /* SZC setup क्रम mic */
#घोषणा   CS_COEF_ADC_LI_SZC_MODE	(3 << 0) /* SZC setup क्रम line-in */
/* PGA mode: 0 = dअगरferential, 1 = signle-ended */
#घोषणा   CS_COEF_ADC_MIC_PGA_MODE	(1 << 5) /* PGA setup क्रम mic */
#घोषणा   CS_COEF_ADC_LI_PGA_MODE	(1 << 6) /* PGA setup क्रम line-in */
#घोषणा IDX_DAC_CFG		0x0003
/* SZC biपंचांगask, 4 modes below:
 * 0 = Immediate
 * 1 = zero-cross
 * 2 = soft-ramp
 * 3 = soft-ramp on zero-cross
 */
#घोषणा   CS_COEF_DAC_HP_SZC_MODE	(3 << 0) /* nid 0x02 */
#घोषणा   CS_COEF_DAC_LO_SZC_MODE	(3 << 2) /* nid 0x03 */
#घोषणा   CS_COEF_DAC_SPK_SZC_MODE	(3 << 4) /* nid 0x04 */

#घोषणा IDX_BEEP_CFG		0x0004
/* 0x0008 - test reg key */
/* 0x0009 - 0x0014 -> 12 test regs */
/* 0x0015 - visibility reg */

/* Cirrus Logic CS4208 */
#घोषणा CS4208_VENDOR_NID	0x24

/*
 * Cirrus Logic CS4210
 *
 * 1 DAC => HP(sense) / Speakers,
 * 1 ADC <= LineIn(sense) / MicIn / DMicIn,
 * 1 SPDIF OUT => SPDIF Trयंत्रitter(sense)
 */
#घोषणा CS4210_DAC_NID		0x02
#घोषणा CS4210_ADC_NID		0x03
#घोषणा CS4210_VENDOR_NID	0x0B
#घोषणा CS421X_DMIC_PIN_NID	0x09 /* Port E */
#घोषणा CS421X_SPDIF_PIN_NID	0x0A /* Port H */

#घोषणा CS421X_IDX_DEV_CFG	0x01
#घोषणा CS421X_IDX_ADC_CFG	0x02
#घोषणा CS421X_IDX_DAC_CFG	0x03
#घोषणा CS421X_IDX_SPK_CTL	0x04

/* Cirrus Logic CS4213 is like CS4210 but करोes not have SPDIF input/output */
#घोषणा CS4213_VENDOR_NID	0x09


अटल अंतरभूत पूर्णांक cs_venकरोr_coef_get(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा cs_spec *spec = codec->spec;

	snd_hda_codec_ग_लिखो(codec, spec->venकरोr_nid, 0,
			    AC_VERB_SET_COEF_INDEX, idx);
	वापस snd_hda_codec_पढ़ो(codec, spec->venकरोr_nid, 0,
				  AC_VERB_GET_PROC_COEF, 0);
पूर्ण

अटल अंतरभूत व्योम cs_venकरोr_coef_set(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक idx,
				      अचिन्हित पूर्णांक coef)
अणु
	काष्ठा cs_spec *spec = codec->spec;

	snd_hda_codec_ग_लिखो(codec, spec->venकरोr_nid, 0,
			    AC_VERB_SET_COEF_INDEX, idx);
	snd_hda_codec_ग_लिखो(codec, spec->venकरोr_nid, 0,
			    AC_VERB_SET_PROC_COEF, coef);
पूर्ण

/*
 * स्वतः-mute and स्वतः-mic चयनing
 * CS421x स्वतः-output redirecting
 * HP/SPK/SPDIF
 */

अटल व्योम cs_स्वतःmute(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec = codec->spec;

	/* mute HPs अगर spdअगर jack (SENSE_B) is present */
	spec->gen.master_mute = !!(spec->spdअगर_present && spec->sense_b);

	snd_hda_gen_update_outमाला_दो(codec);

	अगर (spec->gpio_eapd_hp || spec->gpio_eapd_speaker) अणु
		अगर (spec->gen.स्वतःmute_speaker)
			spec->gpio_data = spec->gen.hp_jack_present ?
				spec->gpio_eapd_hp : spec->gpio_eapd_speaker;
		अन्यथा
			spec->gpio_data =
				spec->gpio_eapd_hp | spec->gpio_eapd_speaker;
		snd_hda_codec_ग_लिखो(codec, 0x01, 0,
				    AC_VERB_SET_GPIO_DATA, spec->gpio_data);
	पूर्ण
पूर्ण

अटल bool is_active_pin(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक val;

	val = snd_hda_codec_get_pincfg(codec, nid);
	वापस (get_defcfg_connect(val) != AC_JACK_PORT_NONE);
पूर्ण

अटल व्योम init_input_coef(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec = codec->spec;
	अचिन्हित पूर्णांक coef;

	/* CS420x has multiple ADC, CS421x has single ADC */
	अगर (spec->venकरोr_nid == CS420X_VENDOR_NID) अणु
		coef = cs_venकरोr_coef_get(codec, IDX_BEEP_CFG);
		अगर (is_active_pin(codec, CS_DMIC2_PIN_NID))
			coef |= 1 << 4; /* DMIC2 2 chan on, GPIO1 off */
		अगर (is_active_pin(codec, CS_DMIC1_PIN_NID))
			coef |= 1 << 3; /* DMIC1 2 chan on, GPIO0 off
					 * No effect अगर SPDIF_OUT2 is
					 * selected in IDX_SPDIF_CTL.
					 */

		cs_venकरोr_coef_set(codec, IDX_BEEP_CFG, coef);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hda_verb cs_coef_init_verbs[] = अणु
	अणु0x11, AC_VERB_SET_PROC_STATE, 1पूर्ण,
	अणु0x11, AC_VERB_SET_COEF_INDEX, IDX_DAC_CFGपूर्ण,
	अणु0x11, AC_VERB_SET_PROC_COEF,
	 (0x002a /* DAC1/2/3 SZCMode Soft Ramp */
	  | 0x0040 /* Mute DACs on FIFO error */
	  | 0x1000 /* Enable DACs High Pass Filter */
	  | 0x0400 /* Disable Coefficient Auto increment */
	  )पूर्ण,
	/* ADC1/2 - Digital and Analog Soft Ramp */
	अणु0x11, AC_VERB_SET_COEF_INDEX, IDX_ADC_CFGपूर्ण,
	अणु0x11, AC_VERB_SET_PROC_COEF, 0x000aपूर्ण,
	/* Beep */
	अणु0x11, AC_VERB_SET_COEF_INDEX, IDX_BEEP_CFGपूर्ण,
	अणु0x11, AC_VERB_SET_PROC_COEF, 0x0007पूर्ण, /* Enable Beep thru DAC1/2/3 */

	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_verb cs4208_coef_init_verbs[] = अणु
	अणु0x01, AC_VERB_SET_POWER_STATE, 0x00पूर्ण, /* AFG: D0 */
	अणु0x24, AC_VERB_SET_PROC_STATE, 0x01पूर्ण,  /* VPW: processing on */
	अणु0x24, AC_VERB_SET_COEF_INDEX, 0x0033पूर्ण,
	अणु0x24, AC_VERB_SET_PROC_COEF, 0x0001पूर्ण, /* A1 ICS */
	अणु0x24, AC_VERB_SET_COEF_INDEX, 0x0034पूर्ण,
	अणु0x24, AC_VERB_SET_PROC_COEF, 0x1C01पूर्ण, /* A1 Enable, A Thresh = 300mV */
	अणुपूर्ण /* terminator */
पूर्ण;

/* Errata: CS4207 rev C0/C1/C2 Silicon
 *
 * http://www.cirrus.com/en/pubs/errata/ER880C3.pdf
 *
 * 6. At high temperature (TA > +85तओC), the digital supply current (IVD)
 * may be excessive (up to an additional 200 NञA), which is most easily
 * observed जबतक the part is being held in reset (RESET# active low).
 *
 * Root Cause: At initial घातerup of the device, the logic that drives
 * the घड़ी and ग_लिखो enable to the S/PDIF SRC RAMs is not properly
 * initialized.
 * Certain अक्रमom patterns will cause a steady leakage current in those
 * RAM cells. The issue will resolve once the SRCs are used (turned on).
 *
 * Workaround: The following verb sequence briefly turns on the S/PDIF SRC
 * blocks, which will alleviate the issue.
 */

अटल स्थिर काष्ठा hda_verb cs_errata_init_verbs[] = अणु
	अणु0x01, AC_VERB_SET_POWER_STATE, 0x00पूर्ण, /* AFG: D0 */
	अणु0x11, AC_VERB_SET_PROC_STATE, 0x01पूर्ण,  /* VPW: processing on */

	अणु0x11, AC_VERB_SET_COEF_INDEX, 0x0008पूर्ण,
	अणु0x11, AC_VERB_SET_PROC_COEF, 0x9999पूर्ण,
	अणु0x11, AC_VERB_SET_COEF_INDEX, 0x0017पूर्ण,
	अणु0x11, AC_VERB_SET_PROC_COEF, 0xa412पूर्ण,
	अणु0x11, AC_VERB_SET_COEF_INDEX, 0x0001पूर्ण,
	अणु0x11, AC_VERB_SET_PROC_COEF, 0x0009पूर्ण,

	अणु0x07, AC_VERB_SET_POWER_STATE, 0x00पूर्ण, /* S/PDIF Rx: D0 */
	अणु0x08, AC_VERB_SET_POWER_STATE, 0x00पूर्ण, /* S/PDIF Tx: D0 */

	अणु0x11, AC_VERB_SET_COEF_INDEX, 0x0017पूर्ण,
	अणु0x11, AC_VERB_SET_PROC_COEF, 0x2412पूर्ण,
	अणु0x11, AC_VERB_SET_COEF_INDEX, 0x0008पूर्ण,
	अणु0x11, AC_VERB_SET_PROC_COEF, 0x0000पूर्ण,
	अणु0x11, AC_VERB_SET_COEF_INDEX, 0x0001पूर्ण,
	अणु0x11, AC_VERB_SET_PROC_COEF, 0x0008पूर्ण,
	अणु0x11, AC_VERB_SET_PROC_STATE, 0x00पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;

/* SPDIF setup */
अटल व्योम init_digital_coef(काष्ठा hda_codec *codec)
अणु
	अचिन्हित पूर्णांक coef;

	coef = 0x0002; /* SRC_MUTE soft-mute on SPDIF (अगर no lock) */
	coef |= 0x0008; /* Replace with mute on error */
	अगर (is_active_pin(codec, CS_DIG_OUT2_PIN_NID))
		coef |= 0x4000; /* RX to TX1 or TX2 Loopthru / SPDIF2
				 * SPDIF_OUT2 is shared with GPIO1 and
				 * DMIC_SDA2.
				 */
	cs_venकरोr_coef_set(codec, IDX_SPDIF_CTL, coef);
पूर्ण

अटल पूर्णांक cs_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec = codec->spec;

	अगर (spec->venकरोr_nid == CS420X_VENDOR_NID) अणु
		/* init_verb sequence क्रम C0/C1/C2 errata*/
		snd_hda_sequence_ग_लिखो(codec, cs_errata_init_verbs);
		snd_hda_sequence_ग_लिखो(codec, cs_coef_init_verbs);
	पूर्ण अन्यथा अगर (spec->venकरोr_nid == CS4208_VENDOR_NID) अणु
		snd_hda_sequence_ग_लिखो(codec, cs4208_coef_init_verbs);
	पूर्ण

	snd_hda_gen_init(codec);

	अगर (spec->gpio_mask) अणु
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, AC_VERB_SET_GPIO_MASK,
				    spec->gpio_mask);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, AC_VERB_SET_GPIO_सूचीECTION,
				    spec->gpio_dir);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, AC_VERB_SET_GPIO_DATA,
				    spec->gpio_data);
	पूर्ण

	अगर (spec->venकरोr_nid == CS420X_VENDOR_NID) अणु
		init_input_coef(codec);
		init_digital_coef(codec);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs_build_controls(काष्ठा hda_codec *codec)
अणु
	पूर्णांक err;

	err = snd_hda_gen_build_controls(codec);
	अगर (err < 0)
		वापस err;
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_BUILD);
	वापस 0;
पूर्ण

#घोषणा cs_मुक्त		snd_hda_gen_मुक्त

अटल स्थिर काष्ठा hda_codec_ops cs_patch_ops = अणु
	.build_controls = cs_build_controls,
	.build_pcms = snd_hda_gen_build_pcms,
	.init = cs_init,
	.मुक्त = cs_मुक्त,
	.unsol_event = snd_hda_jack_unsol_event,
पूर्ण;

अटल पूर्णांक cs_parse_स्वतः_config(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec = codec->spec;
	पूर्णांक err;
	पूर्णांक i;

	err = snd_hda_parse_pin_defcfg(codec, &spec->gen.स्वतःcfg, शून्य, 0);
	अगर (err < 0)
		वापस err;

	err = snd_hda_gen_parse_स्वतः_config(codec, &spec->gen.स्वतःcfg);
	अगर (err < 0)
		वापस err;

	/* keep the ADCs घातered up when it's dynamically चयनable */
	अगर (spec->gen.dyn_adc_चयन) अणु
		अचिन्हित पूर्णांक करोne = 0;

		क्रम (i = 0; i < spec->gen.input_mux.num_items; i++) अणु
			पूर्णांक idx = spec->gen.dyn_adc_idx[i];

			अगर (करोne & (1 << idx))
				जारी;
			snd_hda_gen_fix_pin_घातer(codec,
						  spec->gen.adc_nids[idx]);
			करोne |= 1 << idx;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hda_model_fixup cs420x_models[] = अणु
	अणु .id = CS420X_MBP53, .name = "mbp53" पूर्ण,
	अणु .id = CS420X_MBP55, .name = "mbp55" पूर्ण,
	अणु .id = CS420X_IMAC27, .name = "imac27" पूर्ण,
	अणु .id = CS420X_IMAC27_122, .name = "imac27_122" पूर्ण,
	अणु .id = CS420X_APPLE, .name = "apple" पूर्ण,
	अणु .id = CS420X_MBP101, .name = "mbp101" पूर्ण,
	अणु .id = CS420X_MBP81, .name = "mbp81" पूर्ण,
	अणु .id = CS420X_MBA42, .name = "mba42" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk cs420x_fixup_tbl[] = अणु
	SND_PCI_QUIRK(0x10de, 0x0ac0, "MacBookPro 5,3", CS420X_MBP53),
	SND_PCI_QUIRK(0x10de, 0x0d94, "MacBookAir 3,1(2)", CS420X_MBP55),
	SND_PCI_QUIRK(0x10de, 0xcb79, "MacBookPro 5,5", CS420X_MBP55),
	SND_PCI_QUIRK(0x10de, 0xcb89, "MacBookPro 7,1", CS420X_MBP55),
	/* this conflicts with too many other models */
	/*SND_PCI_QUIRK(0x8086, 0x7270, "IMac 27 Inch", CS420X_IMAC27),*/

	/* codec SSID */
	SND_PCI_QUIRK(0x106b, 0x0600, "iMac 14,1", CS420X_IMAC27_122),
	SND_PCI_QUIRK(0x106b, 0x1c00, "MacBookPro 8,1", CS420X_MBP81),
	SND_PCI_QUIRK(0x106b, 0x2000, "iMac 12,2", CS420X_IMAC27_122),
	SND_PCI_QUIRK(0x106b, 0x2800, "MacBookPro 10,1", CS420X_MBP101),
	SND_PCI_QUIRK(0x106b, 0x5600, "MacBookAir 5,2", CS420X_MBP81),
	SND_PCI_QUIRK(0x106b, 0x5b00, "MacBookAir 4,2", CS420X_MBA42),
	SND_PCI_QUIRK_VENDOR(0x106b, "Apple", CS420X_APPLE),
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl mbp53_pincfgs[] = अणु
	अणु 0x09, 0x012b4050 पूर्ण,
	अणु 0x0a, 0x90100141 पूर्ण,
	अणु 0x0b, 0x90100140 पूर्ण,
	अणु 0x0c, 0x018b3020 पूर्ण,
	अणु 0x0d, 0x90a00110 पूर्ण,
	अणु 0x0e, 0x400000f0 पूर्ण,
	अणु 0x0f, 0x01cbe030 पूर्ण,
	अणु 0x10, 0x014be060 पूर्ण,
	अणु 0x12, 0x400000f0 पूर्ण,
	अणु 0x15, 0x400000f0 पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl mbp55_pincfgs[] = अणु
	अणु 0x09, 0x012b4030 पूर्ण,
	अणु 0x0a, 0x90100121 पूर्ण,
	अणु 0x0b, 0x90100120 पूर्ण,
	अणु 0x0c, 0x400000f0 पूर्ण,
	अणु 0x0d, 0x90a00110 पूर्ण,
	अणु 0x0e, 0x400000f0 पूर्ण,
	अणु 0x0f, 0x400000f0 पूर्ण,
	अणु 0x10, 0x014be040 पूर्ण,
	अणु 0x12, 0x400000f0 पूर्ण,
	अणु 0x15, 0x400000f0 पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl imac27_pincfgs[] = अणु
	अणु 0x09, 0x012b4050 पूर्ण,
	अणु 0x0a, 0x90100140 पूर्ण,
	अणु 0x0b, 0x90100142 पूर्ण,
	अणु 0x0c, 0x018b3020 पूर्ण,
	अणु 0x0d, 0x90a00110 पूर्ण,
	अणु 0x0e, 0x400000f0 पूर्ण,
	अणु 0x0f, 0x01cbe030 पूर्ण,
	अणु 0x10, 0x014be060 पूर्ण,
	अणु 0x12, 0x01ab9070 पूर्ण,
	अणु 0x15, 0x400000f0 पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl mbp101_pincfgs[] = अणु
	अणु 0x0d, 0x40ab90f0 पूर्ण,
	अणु 0x0e, 0x90a600f0 पूर्ण,
	अणु 0x12, 0x50a600f0 पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl mba42_pincfgs[] = अणु
	अणु 0x09, 0x012b4030 पूर्ण, /* HP */
	अणु 0x0a, 0x400000f0 पूर्ण,
	अणु 0x0b, 0x90100120 पूर्ण, /* speaker */
	अणु 0x0c, 0x400000f0 पूर्ण,
	अणु 0x0d, 0x90a00110 पूर्ण, /* mic */
	अणु 0x0e, 0x400000f0 पूर्ण,
	अणु 0x0f, 0x400000f0 पूर्ण,
	अणु 0x10, 0x400000f0 पूर्ण,
	अणु 0x12, 0x400000f0 पूर्ण,
	अणु 0x15, 0x400000f0 पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl mba6_pincfgs[] = अणु
	अणु 0x10, 0x032120f0 पूर्ण, /* HP */
	अणु 0x11, 0x500000f0 पूर्ण,
	अणु 0x12, 0x90100010 पूर्ण, /* Speaker */
	अणु 0x13, 0x500000f0 पूर्ण,
	अणु 0x14, 0x500000f0 पूर्ण,
	अणु 0x15, 0x770000f0 पूर्ण,
	अणु 0x16, 0x770000f0 पूर्ण,
	अणु 0x17, 0x430000f0 पूर्ण,
	अणु 0x18, 0x43ab9030 पूर्ण, /* Mic */
	अणु 0x19, 0x770000f0 पूर्ण,
	अणु 0x1a, 0x770000f0 पूर्ण,
	अणु 0x1b, 0x770000f0 पूर्ण,
	अणु 0x1c, 0x90a00090 पूर्ण,
	अणु 0x1d, 0x500000f0 पूर्ण,
	अणु 0x1e, 0x500000f0 पूर्ण,
	अणु 0x1f, 0x500000f0 पूर्ण,
	अणु 0x20, 0x500000f0 पूर्ण,
	अणु 0x21, 0x430000f0 पूर्ण,
	अणु 0x22, 0x430000f0 पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;

अटल व्योम cs420x_fixup_gpio_13(काष्ठा hda_codec *codec,
				 स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		काष्ठा cs_spec *spec = codec->spec;

		spec->gpio_eapd_hp = 2; /* GPIO1 = headphones */
		spec->gpio_eapd_speaker = 8; /* GPIO3 = speakers */
		spec->gpio_mask = spec->gpio_dir =
			spec->gpio_eapd_hp | spec->gpio_eapd_speaker;
	पूर्ण
पूर्ण

अटल व्योम cs420x_fixup_gpio_23(काष्ठा hda_codec *codec,
				 स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		काष्ठा cs_spec *spec = codec->spec;

		spec->gpio_eapd_hp = 4; /* GPIO2 = headphones */
		spec->gpio_eapd_speaker = 8; /* GPIO3 = speakers */
		spec->gpio_mask = spec->gpio_dir =
			spec->gpio_eapd_hp | spec->gpio_eapd_speaker;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hda_fixup cs420x_fixups[] = अणु
	[CS420X_MBP53] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = mbp53_pincfgs,
		.chained = true,
		.chain_id = CS420X_APPLE,
	पूर्ण,
	[CS420X_MBP55] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = mbp55_pincfgs,
		.chained = true,
		.chain_id = CS420X_GPIO_13,
	पूर्ण,
	[CS420X_IMAC27] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = imac27_pincfgs,
		.chained = true,
		.chain_id = CS420X_GPIO_13,
	पूर्ण,
	[CS420X_GPIO_13] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cs420x_fixup_gpio_13,
	पूर्ण,
	[CS420X_GPIO_23] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cs420x_fixup_gpio_23,
	पूर्ण,
	[CS420X_MBP101] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = mbp101_pincfgs,
		.chained = true,
		.chain_id = CS420X_GPIO_13,
	पूर्ण,
	[CS420X_MBP81] = अणु
		.type = HDA_FIXUP_VERBS,
		.v.verbs = (स्थिर काष्ठा hda_verb[]) अणु
			/* पूर्णांकernal mic ADC2: right only, single ended */
			अणु0x11, AC_VERB_SET_COEF_INDEX, IDX_ADC_CFGपूर्ण,
			अणु0x11, AC_VERB_SET_PROC_COEF, 0x102aपूर्ण,
			अणुपूर्ण
		पूर्ण,
		.chained = true,
		.chain_id = CS420X_GPIO_13,
	पूर्ण,
	[CS420X_MBA42] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = mba42_pincfgs,
		.chained = true,
		.chain_id = CS420X_GPIO_13,
	पूर्ण,
पूर्ण;

अटल काष्ठा cs_spec *cs_alloc_spec(काष्ठा hda_codec *codec, पूर्णांक venकरोr_nid)
अणु
	काष्ठा cs_spec *spec;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस शून्य;
	codec->spec = spec;
	spec->venकरोr_nid = venकरोr_nid;
	codec->घातer_save_node = 1;
	snd_hda_gen_spec_init(&spec->gen);

	वापस spec;
पूर्ण

अटल पूर्णांक patch_cs420x(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec;
	पूर्णांक err;

	spec = cs_alloc_spec(codec, CS420X_VENDOR_NID);
	अगर (!spec)
		वापस -ENOMEM;

	codec->patch_ops = cs_patch_ops;
	spec->gen.स्वतःmute_hook = cs_स्वतःmute;
	codec->single_adc_amp = 1;

	snd_hda_pick_fixup(codec, cs420x_models, cs420x_fixup_tbl,
			   cs420x_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	err = cs_parse_स्वतः_config(codec);
	अगर (err < 0)
		जाओ error;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;

 error:
	cs_मुक्त(codec);
	वापस err;
पूर्ण

/*
 * CS4208 support:
 * Its layout is no दीर्घer compatible with CS4206/CS4207
 */
क्रमागत अणु
	CS4208_MAC_AUTO,
	CS4208_MBA6,
	CS4208_MBP11,
	CS4208_MACMINI,
	CS4208_GPIO0,
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup cs4208_models[] = अणु
	अणु .id = CS4208_GPIO0, .name = "gpio0" पूर्ण,
	अणु .id = CS4208_MBA6, .name = "mba6" पूर्ण,
	अणु .id = CS4208_MBP11, .name = "mbp11" पूर्ण,
	अणु .id = CS4208_MACMINI, .name = "macmini" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk cs4208_fixup_tbl[] = अणु
	SND_PCI_QUIRK_VENDOR(0x106b, "Apple", CS4208_MAC_AUTO),
	अणुपूर्ण /* terminator */
पूर्ण;

/* codec SSID matching */
अटल स्थिर काष्ठा snd_pci_quirk cs4208_mac_fixup_tbl[] = अणु
	SND_PCI_QUIRK(0x106b, 0x5e00, "MacBookPro 11,2", CS4208_MBP11),
	SND_PCI_QUIRK(0x106b, 0x6c00, "MacMini 7,1", CS4208_MACMINI),
	SND_PCI_QUIRK(0x106b, 0x7100, "MacBookAir 6,1", CS4208_MBA6),
	SND_PCI_QUIRK(0x106b, 0x7200, "MacBookAir 6,2", CS4208_MBA6),
	SND_PCI_QUIRK(0x106b, 0x7b00, "MacBookPro 12,1", CS4208_MBP11),
	अणुपूर्ण /* terminator */
पूर्ण;

अटल व्योम cs4208_fixup_gpio0(काष्ठा hda_codec *codec,
			       स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		काष्ठा cs_spec *spec = codec->spec;

		spec->gpio_eapd_hp = 0;
		spec->gpio_eapd_speaker = 1;
		spec->gpio_mask = spec->gpio_dir =
			spec->gpio_eapd_hp | spec->gpio_eapd_speaker;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hda_fixup cs4208_fixups[];

/* remap the fixup from codec SSID and apply it */
अटल व्योम cs4208_fixup_mac(काष्ठा hda_codec *codec,
			     स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	codec->fixup_id = HDA_FIXUP_ID_NOT_SET;
	snd_hda_pick_fixup(codec, शून्य, cs4208_mac_fixup_tbl, cs4208_fixups);
	अगर (codec->fixup_id == HDA_FIXUP_ID_NOT_SET)
		codec->fixup_id = CS4208_GPIO0; /* शेष fixup */
	snd_hda_apply_fixup(codec, action);
पूर्ण

/* MacMini 7,1 has the inverted jack detection */
अटल व्योम cs4208_fixup_macmini(काष्ठा hda_codec *codec,
				 स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अटल स्थिर काष्ठा hda_pपूर्णांकbl pincfgs[] = अणु
		अणु 0x18, 0x00ab9150 पूर्ण, /* mic (audio-in) jack: disable detect */
		अणु 0x21, 0x004be140 पूर्ण, /* SPDIF: disable detect */
		अणु पूर्ण
	पूर्ण;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		/* HP pin (0x10) has an inverted detection */
		codec->inv_jack_detect = 1;
		/* disable the bogus Mic and SPDIF jack detections */
		snd_hda_apply_pincfgs(codec, pincfgs);
	पूर्ण
पूर्ण

अटल पूर्णांक cs4208_spdअगर_sw_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा cs_spec *spec = codec->spec;
	hda_nid_t pin = spec->gen.स्वतःcfg.dig_out_pins[0];
	पूर्णांक pinctl = ucontrol->value.पूर्णांकeger.value[0] ? PIN_OUT : 0;

	snd_hda_set_pin_ctl_cache(codec, pin, pinctl);
	वापस spec->spdअगर_sw_put(kcontrol, ucontrol);
पूर्ण

/* hook the SPDIF चयन */
अटल व्योम cs4208_fixup_spdअगर_चयन(काष्ठा hda_codec *codec,
				      स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action == HDA_FIXUP_ACT_BUILD) अणु
		काष्ठा cs_spec *spec = codec->spec;
		काष्ठा snd_kcontrol *kctl;

		अगर (!spec->gen.स्वतःcfg.dig_out_pins[0])
			वापस;
		kctl = snd_hda_find_mixer_ctl(codec, "IEC958 Playback Switch");
		अगर (!kctl)
			वापस;
		spec->spdअगर_sw_put = kctl->put;
		kctl->put = cs4208_spdअगर_sw_put;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hda_fixup cs4208_fixups[] = अणु
	[CS4208_MBA6] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = mba6_pincfgs,
		.chained = true,
		.chain_id = CS4208_GPIO0,
	पूर्ण,
	[CS4208_MBP11] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cs4208_fixup_spdअगर_चयन,
		.chained = true,
		.chain_id = CS4208_GPIO0,
	पूर्ण,
	[CS4208_MACMINI] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cs4208_fixup_macmini,
		.chained = true,
		.chain_id = CS4208_GPIO0,
	पूर्ण,
	[CS4208_GPIO0] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cs4208_fixup_gpio0,
	पूर्ण,
	[CS4208_MAC_AUTO] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cs4208_fixup_mac,
	पूर्ण,
पूर्ण;

/* correct the 0dB offset of input pins */
अटल व्योम cs4208_fix_amp_caps(काष्ठा hda_codec *codec, hda_nid_t adc)
अणु
	अचिन्हित पूर्णांक caps;

	caps = query_amp_caps(codec, adc, HDA_INPUT);
	caps &= ~(AC_AMPCAP_OFFSET);
	caps |= 0x02;
	snd_hda_override_amp_caps(codec, adc, HDA_INPUT, caps);
पूर्ण

अटल पूर्णांक patch_cs4208(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec;
	पूर्णांक err;

	spec = cs_alloc_spec(codec, CS4208_VENDOR_NID);
	अगर (!spec)
		वापस -ENOMEM;

	codec->patch_ops = cs_patch_ops;
	spec->gen.स्वतःmute_hook = cs_स्वतःmute;
	/* exclude NID 0x10 (HP) from output volumes due to dअगरferent steps */
	spec->gen.out_vol_mask = 1ULL << 0x10;

	snd_hda_pick_fixup(codec, cs4208_models, cs4208_fixup_tbl,
			   cs4208_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	snd_hda_override_wcaps(codec, 0x18,
			       get_wcaps(codec, 0x18) | AC_WCAP_STEREO);
	cs4208_fix_amp_caps(codec, 0x18);
	cs4208_fix_amp_caps(codec, 0x1b);
	cs4208_fix_amp_caps(codec, 0x1c);

	err = cs_parse_स्वतः_config(codec);
	अगर (err < 0)
		जाओ error;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;

 error:
	cs_मुक्त(codec);
	वापस err;
पूर्ण

/*
 * Cirrus Logic CS4210
 *
 * 1 DAC => HP(sense) / Speakers,
 * 1 ADC <= LineIn(sense) / MicIn / DMicIn,
 * 1 SPDIF OUT => SPDIF Trयंत्रitter(sense)
 */

/* CS4210 board names */
अटल स्थिर काष्ठा hda_model_fixup cs421x_models[] = अणु
	अणु .id = CS421X_CDB4210, .name = "cdb4210" पूर्ण,
	अणु .id = CS421X_STUMPY, .name = "stumpy" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk cs421x_fixup_tbl[] = अणु
	/* Test Intel board + CDB2410  */
	SND_PCI_QUIRK(0x8086, 0x5001, "DP45SG/CDB4210", CS421X_CDB4210),
	अणुपूर्ण /* terminator */
पूर्ण;

/* CS4210 board pinconfigs */
/* Default CS4210 (CDB4210)*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl cdb4210_pincfgs[] = अणु
	अणु 0x05, 0x0321401f पूर्ण,
	अणु 0x06, 0x90170010 पूर्ण,
	अणु 0x07, 0x03813031 पूर्ण,
	अणु 0x08, 0xb7a70037 पूर्ण,
	अणु 0x09, 0xb7a6003e पूर्ण,
	अणु 0x0a, 0x034510f0 पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;

/* Stumpy ChromeBox */
अटल स्थिर काष्ठा hda_pपूर्णांकbl stumpy_pincfgs[] = अणु
	अणु 0x05, 0x022120f0 पूर्ण,
	अणु 0x06, 0x901700f0 पूर्ण,
	अणु 0x07, 0x02a120f0 पूर्ण,
	अणु 0x08, 0x77a70037 पूर्ण,
	अणु 0x09, 0x77a6003e पूर्ण,
	अणु 0x0a, 0x434510f0 पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;

/* Setup GPIO/SENSE क्रम each board (अगर used) */
अटल व्योम cs421x_fixup_sense_b(काष्ठा hda_codec *codec,
				 स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा cs_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE)
		spec->sense_b = 1;
पूर्ण

अटल स्थिर काष्ठा hda_fixup cs421x_fixups[] = अणु
	[CS421X_CDB4210] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = cdb4210_pincfgs,
		.chained = true,
		.chain_id = CS421X_SENSE_B,
	पूर्ण,
	[CS421X_SENSE_B] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cs421x_fixup_sense_b,
	पूर्ण,
	[CS421X_STUMPY] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = stumpy_pincfgs,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_verb cs421x_coef_init_verbs[] = अणु
	अणु0x0B, AC_VERB_SET_PROC_STATE, 1पूर्ण,
	अणु0x0B, AC_VERB_SET_COEF_INDEX, CS421X_IDX_DEV_CFGपूर्ण,
	/*
	 *  Disable Coefficient Index Auto-Increment(DAI)=1,
	 *  PDREF=0
	 */
	अणु0x0B, AC_VERB_SET_PROC_COEF, 0x0001 पूर्ण,

	अणु0x0B, AC_VERB_SET_COEF_INDEX, CS421X_IDX_ADC_CFGपूर्ण,
	/* ADC SZCMode = Digital Soft Ramp */
	अणु0x0B, AC_VERB_SET_PROC_COEF, 0x0002 पूर्ण,

	अणु0x0B, AC_VERB_SET_COEF_INDEX, CS421X_IDX_DAC_CFGपूर्ण,
	अणु0x0B, AC_VERB_SET_PROC_COEF,
	 (0x0002 /* DAC SZCMode = Digital Soft Ramp */
	  | 0x0004 /* Mute DAC on FIFO error */
	  | 0x0008 /* Enable DAC High Pass Filter */
	  )पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;

/* Errata: CS4210 rev A1 Silicon
 *
 * http://www.cirrus.com/en/pubs/errata/
 *
 * Description:
 * 1. Perक्रमmance degredation is present in the ADC.
 * 2. Speaker output is not completely muted upon HP detect.
 * 3. Noise is present when clipping occurs on the amplअगरied
 *    speaker outमाला_दो.
 *
 * Workaround:
 * The following verb sequence written to the रेजिस्टरs during
 * initialization will correct the issues listed above.
 */

अटल स्थिर काष्ठा hda_verb cs421x_coef_init_verbs_A1_silicon_fixes[] = अणु
	अणु0x0B, AC_VERB_SET_PROC_STATE, 0x01पूर्ण,  /* VPW: processing on */

	अणु0x0B, AC_VERB_SET_COEF_INDEX, 0x0006पूर्ण,
	अणु0x0B, AC_VERB_SET_PROC_COEF, 0x9999पूर्ण, /* Test mode: on */

	अणु0x0B, AC_VERB_SET_COEF_INDEX, 0x000Aपूर्ण,
	अणु0x0B, AC_VERB_SET_PROC_COEF, 0x14CBपूर्ण, /* Chop द्विगुन */

	अणु0x0B, AC_VERB_SET_COEF_INDEX, 0x0011पूर्ण,
	अणु0x0B, AC_VERB_SET_PROC_COEF, 0xA2D0पूर्ण, /* Increase ADC current */

	अणु0x0B, AC_VERB_SET_COEF_INDEX, 0x001Aपूर्ण,
	अणु0x0B, AC_VERB_SET_PROC_COEF, 0x02A9पूर्ण, /* Mute speaker */

	अणु0x0B, AC_VERB_SET_COEF_INDEX, 0x001Bपूर्ण,
	अणु0x0B, AC_VERB_SET_PROC_COEF, 0X1006पूर्ण, /* Remove noise */

	अणुपूर्ण /* terminator */
पूर्ण;

/* Speaker Amp Gain is controlled by the venकरोr widget's coef 4 */
अटल स्थिर DECLARE_TLV_DB_SCALE(cs421x_speaker_boost_db_scale, 900, 300, 0);

अटल पूर्णांक cs421x_boost_vol_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 3;
	वापस 0;
पूर्ण

अटल पूर्णांक cs421x_boost_vol_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] =
		cs_venकरोr_coef_get(codec, CS421X_IDX_SPK_CTL) & 0x0003;
	वापस 0;
पूर्ण

अटल पूर्णांक cs421x_boost_vol_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);

	अचिन्हित पूर्णांक vol = ucontrol->value.पूर्णांकeger.value[0];
	अचिन्हित पूर्णांक coef =
		cs_venकरोr_coef_get(codec, CS421X_IDX_SPK_CTL);
	अचिन्हित पूर्णांक original_coef = coef;

	coef &= ~0x0003;
	coef |= (vol & 0x0003);
	अगर (original_coef != coef) अणु
		cs_venकरोr_coef_set(codec, CS421X_IDX_SPK_CTL, coef);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new cs421x_speaker_boost_ctl = अणु

	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.name = "Speaker Boost Playback Volume",
	.info = cs421x_boost_vol_info,
	.get = cs421x_boost_vol_get,
	.put = cs421x_boost_vol_put,
	.tlv = अणु .p = cs421x_speaker_boost_db_scale पूर्ण,
पूर्ण;

अटल व्योम cs4210_pinmux_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec = codec->spec;
	अचिन्हित पूर्णांक def_conf, coef;

	/* GPIO, DMIC_SCL, DMIC_SDA and SENSE_B are multiplexed */
	coef = cs_venकरोr_coef_get(codec, CS421X_IDX_DEV_CFG);

	अगर (spec->gpio_mask)
		coef |= 0x0008; /* B1,B2 are GPIOs */
	अन्यथा
		coef &= ~0x0008;

	अगर (spec->sense_b)
		coef |= 0x0010; /* B2 is SENSE_B, not inverted  */
	अन्यथा
		coef &= ~0x0010;

	cs_venकरोr_coef_set(codec, CS421X_IDX_DEV_CFG, coef);

	अगर ((spec->gpio_mask || spec->sense_b) &&
	    is_active_pin(codec, CS421X_DMIC_PIN_NID)) अणु

		/*
		 *  GPIO or SENSE_B क्रमced - disconnect the DMIC pin.
		 */
		def_conf = snd_hda_codec_get_pincfg(codec, CS421X_DMIC_PIN_NID);
		def_conf &= ~AC_DEFCFG_PORT_CONN;
		def_conf |= (AC_JACK_PORT_NONE << AC_DEFCFG_PORT_CONN_SHIFT);
		snd_hda_codec_set_pincfg(codec, CS421X_DMIC_PIN_NID, def_conf);
	पूर्ण
पूर्ण

अटल व्योम cs4210_spdअगर_स्वतःmute(काष्ठा hda_codec *codec,
				  काष्ठा hda_jack_callback *tbl)
अणु
	काष्ठा cs_spec *spec = codec->spec;
	bool spdअगर_present = false;
	hda_nid_t spdअगर_pin = spec->gen.स्वतःcfg.dig_out_pins[0];

	/* detect on spdअगर is specअगरic to CS4210 */
	अगर (!spec->spdअगर_detect ||
	    spec->venकरोr_nid != CS4210_VENDOR_NID)
		वापस;

	spdअगर_present = snd_hda_jack_detect(codec, spdअगर_pin);
	अगर (spdअगर_present == spec->spdअगर_present)
		वापस;

	spec->spdअगर_present = spdअगर_present;
	/* SPDIF TX on/off */
	snd_hda_set_pin_ctl(codec, spdअगर_pin, spdअगर_present ? PIN_OUT : 0);

	cs_स्वतःmute(codec);
पूर्ण

अटल व्योम parse_cs421x_digital(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->gen.स्वतःcfg;
	पूर्णांक i;

	क्रम (i = 0; i < cfg->dig_outs; i++) अणु
		hda_nid_t nid = cfg->dig_out_pins[i];

		अगर (get_wcaps(codec, nid) & AC_WCAP_UNSOL_CAP) अणु
			spec->spdअगर_detect = 1;
			snd_hda_jack_detect_enable_callback(codec, nid,
							    cs4210_spdअगर_स्वतःmute);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक cs421x_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec = codec->spec;

	अगर (spec->venकरोr_nid == CS4210_VENDOR_NID) अणु
		snd_hda_sequence_ग_लिखो(codec, cs421x_coef_init_verbs);
		snd_hda_sequence_ग_लिखो(codec, cs421x_coef_init_verbs_A1_silicon_fixes);
		cs4210_pinmux_init(codec);
	पूर्ण

	snd_hda_gen_init(codec);

	अगर (spec->gpio_mask) अणु
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, AC_VERB_SET_GPIO_MASK,
				    spec->gpio_mask);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, AC_VERB_SET_GPIO_सूचीECTION,
				    spec->gpio_dir);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, AC_VERB_SET_GPIO_DATA,
				    spec->gpio_data);
	पूर्ण

	init_input_coef(codec);

	cs4210_spdअगर_स्वतःmute(codec, शून्य);

	वापस 0;
पूर्ण

अटल व्योम fix_volume_caps(काष्ठा hda_codec *codec, hda_nid_t dac)
अणु
	अचिन्हित पूर्णांक caps;

	/* set the upper-limit क्रम mixer amp to 0dB */
	caps = query_amp_caps(codec, dac, HDA_OUTPUT);
	caps &= ~(0x7f << AC_AMPCAP_NUM_STEPS_SHIFT);
	caps |= ((caps >> AC_AMPCAP_OFFSET_SHIFT) & 0x7f)
		<< AC_AMPCAP_NUM_STEPS_SHIFT;
	snd_hda_override_amp_caps(codec, dac, HDA_OUTPUT, caps);
पूर्ण

अटल पूर्णांक cs421x_parse_स्वतः_config(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec = codec->spec;
	hda_nid_t dac = CS4210_DAC_NID;
	पूर्णांक err;

	fix_volume_caps(codec, dac);

	err = snd_hda_parse_pin_defcfg(codec, &spec->gen.स्वतःcfg, शून्य, 0);
	अगर (err < 0)
		वापस err;

	err = snd_hda_gen_parse_स्वतः_config(codec, &spec->gen.स्वतःcfg);
	अगर (err < 0)
		वापस err;

	parse_cs421x_digital(codec);

	अगर (spec->gen.स्वतःcfg.speaker_outs &&
	    spec->venकरोr_nid == CS4210_VENDOR_NID) अणु
		अगर (!snd_hda_gen_add_kctl(&spec->gen, शून्य,
					  &cs421x_speaker_boost_ctl))
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
/*
 *	Manage PDREF, when transitioning to D3hot
 *	(DAC,ADC) -> D3, PDREF=1, AFG->D3
 */
अटल पूर्णांक cs421x_suspend(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec = codec->spec;
	अचिन्हित पूर्णांक coef;

	snd_hda_shutup_pins(codec);

	snd_hda_codec_ग_लिखो(codec, CS4210_DAC_NID, 0,
			    AC_VERB_SET_POWER_STATE,  AC_PWRST_D3);
	snd_hda_codec_ग_लिखो(codec, CS4210_ADC_NID, 0,
			    AC_VERB_SET_POWER_STATE,  AC_PWRST_D3);

	अगर (spec->venकरोr_nid == CS4210_VENDOR_NID) अणु
		coef = cs_venकरोr_coef_get(codec, CS421X_IDX_DEV_CFG);
		coef |= 0x0004; /* PDREF */
		cs_venकरोr_coef_set(codec, CS421X_IDX_DEV_CFG, coef);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा hda_codec_ops cs421x_patch_ops = अणु
	.build_controls = snd_hda_gen_build_controls,
	.build_pcms = snd_hda_gen_build_pcms,
	.init = cs421x_init,
	.मुक्त = cs_मुक्त,
	.unsol_event = snd_hda_jack_unsol_event,
#अगर_घोषित CONFIG_PM
	.suspend = cs421x_suspend,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक patch_cs4210(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec;
	पूर्णांक err;

	spec = cs_alloc_spec(codec, CS4210_VENDOR_NID);
	अगर (!spec)
		वापस -ENOMEM;

	codec->patch_ops = cs421x_patch_ops;
	spec->gen.स्वतःmute_hook = cs_स्वतःmute;

	snd_hda_pick_fixup(codec, cs421x_models, cs421x_fixup_tbl,
			   cs421x_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	/*
	 *  Update the GPIO/DMIC/SENSE_B pinmux beक्रमe the configuration
	 *   is स्वतः-parsed. If GPIO or SENSE_B is क्रमced, DMIC input
	 *   is disabled.
	 */
	cs4210_pinmux_init(codec);

	err = cs421x_parse_स्वतः_config(codec);
	अगर (err < 0)
		जाओ error;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;

 error:
	cs_मुक्त(codec);
	वापस err;
पूर्ण

अटल पूर्णांक patch_cs4213(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec;
	पूर्णांक err;

	spec = cs_alloc_spec(codec, CS4213_VENDOR_NID);
	अगर (!spec)
		वापस -ENOMEM;

	codec->patch_ops = cs421x_patch_ops;

	err = cs421x_parse_स्वतः_config(codec);
	अगर (err < 0)
		जाओ error;

	वापस 0;

 error:
	cs_मुक्त(codec);
	वापस err;
पूर्ण

/* Cirrus Logic CS8409 HDA bridge with
 * companion codec CS42L42
 */
#घोषणा CS8409_VENDOR_NID 0x47

#घोषणा CS8409_CS42L42_HP_PIN_NID	0x24
#घोषणा CS8409_CS42L42_SPK_PIN_NID	0x2c
#घोषणा CS8409_CS42L42_AMIC_PIN_NID	0x34
#घोषणा CS8409_CS42L42_DMIC_PIN_NID	0x44
#घोषणा CS8409_CS42L42_DMIC_ADC_PIN_NID	0x22

#घोषणा CS42L42_HSDET_AUTO_DONE	0x02
#घोषणा CS42L42_HSTYPE_MASK		0x03

#घोषणा CS42L42_JACK_INSERTED	0x0C
#घोषणा CS42L42_JACK_REMOVED	0x00

#घोषणा GPIO3_INT (1 << 3)
#घोषणा GPIO4_INT (1 << 4)
#घोषणा GPIO5_INT (1 << 5)

#घोषणा CS42L42_I2C_ADDR	(0x48 << 1)

#घोषणा CIR_I2C_ADDR	0x0059
#घोषणा CIR_I2C_DATA	0x005A
#घोषणा CIR_I2C_CTRL	0x005B
#घोषणा CIR_I2C_STATUS	0x005C
#घोषणा CIR_I2C_QWRITE	0x005D
#घोषणा CIR_I2C_QREAD	0x005E

#घोषणा CS8409_CS42L42_HP_VOL_REAL_MIN   (-63)
#घोषणा CS8409_CS42L42_HP_VOL_REAL_MAX   (0)
#घोषणा CS8409_CS42L42_AMIC_VOL_REAL_MIN (-97)
#घोषणा CS8409_CS42L42_AMIC_VOL_REAL_MAX (12)
#घोषणा CS8409_CS42L42_REG_HS_VOLUME_CHA (0x2301)
#घोषणा CS8409_CS42L42_REG_HS_VOLUME_CHB (0x2303)
#घोषणा CS8409_CS42L42_REG_AMIC_VOLUME   (0x1D03)

काष्ठा cs8409_i2c_param अणु
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक reg;
पूर्ण;

काष्ठा cs8409_cir_param अणु
	अचिन्हित पूर्णांक nid;
	अचिन्हित पूर्णांक cir;
	अचिन्हित पूर्णांक coeff;
पूर्ण;

क्रमागत अणु
	CS8409_BULLSEYE,
	CS8409_WARLOCK,
	CS8409_CYBORG,
	CS8409_FIXUPS,
पूर्ण;

अटल व्योम cs8409_cs42l42_fixups(काष्ठा hda_codec *codec,
				    स्थिर काष्ठा hda_fixup *fix, पूर्णांक action);
अटल पूर्णांक cs8409_cs42l42_exec_verb(काष्ठा hdac_device *dev,
		अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक *res);

/* Dell Inspiron models with cs8409/cs42l42 */
अटल स्थिर काष्ठा hda_model_fixup cs8409_models[] = अणु
	अणु .id = CS8409_BULLSEYE, .name = "bullseye" पूर्ण,
	अणु .id = CS8409_WARLOCK, .name = "warlock" पूर्ण,
	अणु .id = CS8409_CYBORG, .name = "cyborg" पूर्ण,
	अणुपूर्ण
पूर्ण;

/* Dell Inspiron platक्रमms
 * with cs8409 bridge and cs42l42 codec
 */
अटल स्थिर काष्ठा snd_pci_quirk cs8409_fixup_tbl[] = अणु
	SND_PCI_QUIRK(0x1028, 0x0A11, "Bullseye", CS8409_BULLSEYE),
	SND_PCI_QUIRK(0x1028, 0x0A12, "Bullseye", CS8409_BULLSEYE),
	SND_PCI_QUIRK(0x1028, 0x0A23, "Bullseye", CS8409_BULLSEYE),
	SND_PCI_QUIRK(0x1028, 0x0A24, "Bullseye", CS8409_BULLSEYE),
	SND_PCI_QUIRK(0x1028, 0x0A25, "Bullseye", CS8409_BULLSEYE),
	SND_PCI_QUIRK(0x1028, 0x0A29, "Bullseye", CS8409_BULLSEYE),
	SND_PCI_QUIRK(0x1028, 0x0A2A, "Bullseye", CS8409_BULLSEYE),
	SND_PCI_QUIRK(0x1028, 0x0A2B, "Bullseye", CS8409_BULLSEYE),
	SND_PCI_QUIRK(0x1028, 0x0AB0, "Warlock", CS8409_WARLOCK),
	SND_PCI_QUIRK(0x1028, 0x0AB2, "Warlock", CS8409_WARLOCK),
	SND_PCI_QUIRK(0x1028, 0x0AB1, "Warlock", CS8409_WARLOCK),
	SND_PCI_QUIRK(0x1028, 0x0AB3, "Warlock", CS8409_WARLOCK),
	SND_PCI_QUIRK(0x1028, 0x0AB4, "Warlock", CS8409_WARLOCK),
	SND_PCI_QUIRK(0x1028, 0x0AB5, "Warlock", CS8409_WARLOCK),
	SND_PCI_QUIRK(0x1028, 0x0AD9, "Warlock", CS8409_WARLOCK),
	SND_PCI_QUIRK(0x1028, 0x0ADA, "Warlock", CS8409_WARLOCK),
	SND_PCI_QUIRK(0x1028, 0x0ADB, "Warlock", CS8409_WARLOCK),
	SND_PCI_QUIRK(0x1028, 0x0ADC, "Warlock", CS8409_WARLOCK),
	SND_PCI_QUIRK(0x1028, 0x0AF4, "Warlock", CS8409_WARLOCK),
	SND_PCI_QUIRK(0x1028, 0x0AF5, "Warlock", CS8409_WARLOCK),
	SND_PCI_QUIRK(0x1028, 0x0A77, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0A78, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0A79, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0A7A, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0A7D, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0A7E, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0A7F, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0A80, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0ADF, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0AE0, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0AE1, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0AE2, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0AE9, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0AEA, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0AEB, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0AEC, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0AED, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0AEE, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0AEF, "Cyborg", CS8409_CYBORG),
	SND_PCI_QUIRK(0x1028, 0x0AF0, "Cyborg", CS8409_CYBORG),
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_verb cs8409_cs42l42_init_verbs[] = अणु
	अणु 0x01, AC_VERB_SET_GPIO_WAKE_MASK, 0x0018 पूर्ण, /* WAKE from GPIO 3,4 */
	अणु 0x47, AC_VERB_SET_PROC_STATE, 0x0001 पूर्ण,     /* Enable VPW processing  */
	अणु 0x47, AC_VERB_SET_COEF_INDEX, 0x0002 पूर्ण,     /* Configure GPIO 6,7 */
	अणु 0x47, AC_VERB_SET_PROC_COEF,  0x0080 पूर्ण,     /* I2C mode */
	अणु 0x47, AC_VERB_SET_COEF_INDEX, 0x005b पूर्ण,     /* Set I2C bus speed */
	अणु 0x47, AC_VERB_SET_PROC_COEF,  0x0200 पूर्ण,     /* 100kHz I2C_STO = 2 */
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl cs8409_cs42l42_pincfgs[] = अणु
	अणु 0x24, 0x042120f0 पूर्ण, /* ASP-1-TX */
	अणु 0x34, 0x04a12050 पूर्ण, /* ASP-1-RX */
	अणु 0x2c, 0x901000f0 पूर्ण, /* ASP-2-TX */
	अणु 0x44, 0x90a00090 पूर्ण, /* DMIC-1 */
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_fixup cs8409_fixups[] = अणु
	[CS8409_BULLSEYE] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = cs8409_cs42l42_pincfgs,
		.chained = true,
		.chain_id = CS8409_FIXUPS,
	पूर्ण,
	[CS8409_WARLOCK] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = cs8409_cs42l42_pincfgs,
		.chained = true,
		.chain_id = CS8409_FIXUPS,
	पूर्ण,
	[CS8409_CYBORG] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = cs8409_cs42l42_pincfgs,
		.chained = true,
		.chain_id = CS8409_FIXUPS,
	पूर्ण,
	[CS8409_FIXUPS] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cs8409_cs42l42_fixups,
	पूर्ण,
पूर्ण;

/* Venकरोr specअगरic HW configuration क्रम CS42L42 */
अटल स्थिर काष्ठा cs8409_i2c_param cs42l42_init_reg_seq[] = अणु
	अणु 0x1010, 0xB0 पूर्ण,
	अणु 0x1D01, 0x00 पूर्ण,
	अणु 0x1D02, 0x06 पूर्ण,
	अणु 0x1D03, 0x00 पूर्ण,
	अणु 0x1107, 0x01 पूर्ण,
	अणु 0x1009, 0x02 पूर्ण,
	अणु 0x1007, 0x03 पूर्ण,
	अणु 0x1201, 0x00 पूर्ण,
	अणु 0x1208, 0x13 पूर्ण,
	अणु 0x1205, 0xFF पूर्ण,
	अणु 0x1206, 0x00 पूर्ण,
	अणु 0x1207, 0x20 पूर्ण,
	अणु 0x1202, 0x0D पूर्ण,
	अणु 0x2A02, 0x02 पूर्ण,
	अणु 0x2A03, 0x00 पूर्ण,
	अणु 0x2A04, 0x00 पूर्ण,
	अणु 0x2A05, 0x02 पूर्ण,
	अणु 0x2A06, 0x00 पूर्ण,
	अणु 0x2A07, 0x20 पूर्ण,
	अणु 0x2A08, 0x02 पूर्ण,
	अणु 0x2A09, 0x00 पूर्ण,
	अणु 0x2A0A, 0x80 पूर्ण,
	अणु 0x2A0B, 0x02 पूर्ण,
	अणु 0x2A0C, 0x00 पूर्ण,
	अणु 0x2A0D, 0xA0 पूर्ण,
	अणु 0x2A01, 0x0C पूर्ण,
	अणु 0x2902, 0x01 पूर्ण,
	अणु 0x2903, 0x02 पूर्ण,
	अणु 0x2904, 0x00 पूर्ण,
	अणु 0x2905, 0x00 पूर्ण,
	अणु 0x2901, 0x01 पूर्ण,
	अणु 0x1101, 0x0A पूर्ण,
	अणु 0x1102, 0x84 पूर्ण,
	अणु 0x2301, 0x00 पूर्ण,
	अणु 0x2303, 0x00 पूर्ण,
	अणु 0x2302, 0x3f पूर्ण,
	अणु 0x2001, 0x03 पूर्ण,
	अणु 0x1B75, 0xB6 पूर्ण,
	अणु 0x1B73, 0xC2 पूर्ण,
	अणु 0x1129, 0x01 पूर्ण,
	अणु 0x1121, 0xF3 पूर्ण,
	अणु 0x1103, 0x20 पूर्ण,
	अणु 0x1105, 0x00 पूर्ण,
	अणु 0x1112, 0xC0 पूर्ण,
	अणु 0x1113, 0x80 पूर्ण,
	अणु 0x1C03, 0xC0 पूर्ण,
	अणु 0x1105, 0x00 पूर्ण,
	अणु 0x1112, 0xC0 पूर्ण,
	अणु 0x1101, 0x02 पूर्ण,
	अणुपूर्ण /* Terminator */
पूर्ण;

/* Venकरोr specअगरic hw configuration क्रम CS8409 */
अटल स्थिर काष्ठा cs8409_cir_param cs8409_cs42l42_hw_cfg[] = अणु
	अणु 0x47, 0x00, 0xb008 पूर्ण, /* +PLL1/2_EN, +I2C_EN */
	अणु 0x47, 0x01, 0x0002 पूर्ण, /* ASP1/2_EN=0, ASP1_STP=1 */
	अणु 0x47, 0x02, 0x0a80 पूर्ण, /* ASP1/2_BUS_IDLE=10, +GPIO_I2C */
	अणु 0x47, 0x19, 0x0800 पूर्ण, /* ASP1.A: TX.LAP=0, TX.LSZ=24 bits, TX.LCS=0 */
	अणु 0x47, 0x1a, 0x0820 पूर्ण, /* ASP1.A: TX.RAP=0, TX.RSZ=24 bits, TX.RCS=32 */
	अणु 0x47, 0x29, 0x0800 पूर्ण, /* ASP2.A: TX.LAP=0, TX.LSZ=24 bits, TX.LCS=0 */
	अणु 0x47, 0x2a, 0x2800 पूर्ण, /* ASP2.A: TX.RAP=1, TX.RSZ=24 bits, TX.RCS=0 */
	अणु 0x47, 0x39, 0x0800 पूर्ण, /* ASP1.A: RX.LAP=0, RX.LSZ=24 bits, RX.LCS=0 */
	अणु 0x47, 0x3a, 0x0800 पूर्ण, /* ASP1.A: RX.RAP=0, RX.RSZ=24 bits, RX.RCS=0 */
	अणु 0x47, 0x03, 0x8000 पूर्ण, /* ASP1: LCHI = 00h */
	अणु 0x47, 0x04, 0x28ff पूर्ण, /* ASP1: MC/SC_SRCSEL=PLL1, LCPR=FFh */
	अणु 0x47, 0x05, 0x0062 पूर्ण, /* ASP1: MCEN=0, FSD=011, SCPOL_IN/OUT=0, SCDIV=1:4 */
	अणु 0x47, 0x06, 0x801f पूर्ण, /* ASP2: LCHI=1Fh */
	अणु 0x47, 0x07, 0x283f पूर्ण, /* ASP2: MC/SC_SRCSEL=PLL1, LCPR=3Fh */
	अणु 0x47, 0x08, 0x805c पूर्ण, /* ASP2: 5050=1, MCEN=0, FSD=010, SCPOL_IN/OUT=1, SCDIV=1:16 */
	अणु 0x47, 0x09, 0x0023 पूर्ण, /* DMIC1_MO=10b, DMIC1/2_SR=1 */
	अणु 0x47, 0x0a, 0x0000 पूर्ण, /* ASP1/2_BEEP=0 */
	अणु 0x47, 0x01, 0x0062 पूर्ण, /* ASP1/2_EN=1, ASP1_STP=1 */
	अणु 0x47, 0x00, 0x9008 पूर्ण, /* -PLL2_EN */
	अणु 0x47, 0x68, 0x0000 पूर्ण, /* TX2.A: pre-scale att.=0 dB */
	अणु 0x47, 0x82, 0xfc03 पूर्ण, /* ASP1/2_xxx_EN=1, ASP1/2_MCLK_EN=0, DMIC1_SCL_EN=1 */
	अणु 0x47, 0xc0, 0x9999 पूर्ण, /* test mode on */
	अणु 0x47, 0xc5, 0x0000 पूर्ण, /* GPIO hysteresis = 30 us */
	अणु 0x47, 0xc0, 0x0000 पूर्ण, /* test mode off */
	अणुपूर्ण /* Terminator */
पूर्ण;

अटल स्थिर काष्ठा cs8409_cir_param cs8409_cs42l42_bullseye_atn[] = अणु
	अणु 0x47, 0x65, 0x4000 पूर्ण, /* EQ_SEL=1, EQ1/2_EN=0 */
	अणु 0x47, 0x64, 0x4000 पूर्ण, /* +EQ_ACC */
	अणु 0x47, 0x65, 0x4010 पूर्ण, /* +EQ2_EN */
	अणु 0x47, 0x63, 0x0647 पूर्ण, /* EQ_DATA_HI=0x0647 */
	अणु 0x47, 0x64, 0xc0c7 पूर्ण, /* +EQ_WRT, +EQ_ACC, EQ_ADR=0, EQ_DATA_LO=0x67 */
	अणु 0x47, 0x63, 0x0647 पूर्ण, /* EQ_DATA_HI=0x0647 */
	अणु 0x47, 0x64, 0xc1c7 पूर्ण, /* +EQ_WRT, +EQ_ACC, EQ_ADR=1, EQ_DATA_LO=0x67 */
	अणु 0x47, 0x63, 0xf370 पूर्ण, /* EQ_DATA_HI=0xf370 */
	अणु 0x47, 0x64, 0xc271 पूर्ण, /* +EQ_WRT, +EQ_ACC, EQ_ADR=2, EQ_DATA_LO=0x71 */
	अणु 0x47, 0x63, 0x1ef8 पूर्ण, /* EQ_DATA_HI=0x1ef8 */
	अणु 0x47, 0x64, 0xc348 पूर्ण, /* +EQ_WRT, +EQ_ACC, EQ_ADR=3, EQ_DATA_LO=0x48 */
	अणु 0x47, 0x63, 0xc110 पूर्ण, /* EQ_DATA_HI=0xc110 */
	अणु 0x47, 0x64, 0xc45a पूर्ण, /* +EQ_WRT, +EQ_ACC, EQ_ADR=4, EQ_DATA_LO=0x5a */
	अणु 0x47, 0x63, 0x1f29 पूर्ण, /* EQ_DATA_HI=0x1f29 */
	अणु 0x47, 0x64, 0xc574 पूर्ण, /* +EQ_WRT, +EQ_ACC, EQ_ADR=5, EQ_DATA_LO=0x74 */
	अणु 0x47, 0x63, 0x1d7a पूर्ण, /* EQ_DATA_HI=0x1d7a */
	अणु 0x47, 0x64, 0xc653 पूर्ण, /* +EQ_WRT, +EQ_ACC, EQ_ADR=6, EQ_DATA_LO=0x53 */
	अणु 0x47, 0x63, 0xc38c पूर्ण, /* EQ_DATA_HI=0xc38c */
	अणु 0x47, 0x64, 0xc714 पूर्ण, /* +EQ_WRT, +EQ_ACC, EQ_ADR=7, EQ_DATA_LO=0x14 */
	अणु 0x47, 0x63, 0x1ca3 पूर्ण, /* EQ_DATA_HI=0x1ca3 */
	अणु 0x47, 0x64, 0xc8c7 पूर्ण, /* +EQ_WRT, +EQ_ACC, EQ_ADR=8, EQ_DATA_LO=0xc7 */
	अणु 0x47, 0x63, 0xc38c पूर्ण, /* EQ_DATA_HI=0xc38c */
	अणु 0x47, 0x64, 0xc914 पूर्ण, /* +EQ_WRT, +EQ_ACC, EQ_ADR=9, EQ_DATA_LO=0x14 */
	अणु 0x47, 0x64, 0x0000 पूर्ण, /* -EQ_ACC, -EQ_WRT */
	अणुपूर्ण /* Terminator */
पूर्ण;

/**
 * cs8409_enable_i2c_घड़ी - Enable I2C घड़ीs
 * @codec: the codec instance
 * @enable: Enable or disable I2C घड़ीs
 *
 * Enable or Disable I2C घड़ीs.
 */
अटल व्योम cs8409_enable_i2c_घड़ी(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक retval;
	अचिन्हित पूर्णांक newval;

	retval = cs_venकरोr_coef_get(codec, 0x0);
	newval = (enable) ? (retval | 0x8) : (retval & 0xfffffff7);
	cs_venकरोr_coef_set(codec, 0x0, newval);
पूर्ण

/**
 * cs8409_i2c_रुको_complete - Wait क्रम I2C transaction
 * @codec: the codec instance
 *
 * Wait क्रम I2C transaction to complete.
 * Return -1 अगर transaction रुको बार out.
 */
अटल पूर्णांक cs8409_i2c_रुको_complete(काष्ठा hda_codec *codec)
अणु
	पूर्णांक repeat = 5;
	अचिन्हित पूर्णांक retval;

	करो अणु
		retval = cs_venकरोr_coef_get(codec, CIR_I2C_STATUS);
		अगर ((retval & 0x18) != 0x18) अणु
			usleep_range(2000, 4000);
			--repeat;
		पूर्ण अन्यथा
			वापस 0;

	पूर्ण जबतक (repeat);

	वापस -1;
पूर्ण

/**
 * cs8409_i2c_पढ़ो - CS8409 I2C Read.
 * @codec: the codec instance
 * @i2c_address: I2C Address
 * @i2c_reg: Register to पढ़ो
 * @paged: Is a paged transaction
 *
 * CS8409 I2C Read.
 * Returns negative on error, otherwise वापसs पढ़ो value in bits 0-7.
 */
अटल पूर्णांक cs8409_i2c_पढ़ो(काष्ठा hda_codec *codec,
		अचिन्हित पूर्णांक i2c_address,
		अचिन्हित पूर्णांक i2c_reg,
		अचिन्हित पूर्णांक paged)
अणु
	अचिन्हित पूर्णांक i2c_reg_data;
	अचिन्हित पूर्णांक पढ़ो_data;

	cs8409_enable_i2c_घड़ी(codec, 1);
	cs_venकरोr_coef_set(codec, CIR_I2C_ADDR, i2c_address);

	अगर (paged) अणु
		cs_venकरोr_coef_set(codec, CIR_I2C_QWRITE, i2c_reg >> 8);
		अगर (cs8409_i2c_रुको_complete(codec) < 0) अणु
			codec_err(codec,
				"%s() Paged Transaction Failed 0x%02x : 0x%04x\n",
				__func__, i2c_address, i2c_reg);
			वापस -EIO;
		पूर्ण
	पूर्ण

	i2c_reg_data = (i2c_reg << 8) & 0x0ffff;
	cs_venकरोr_coef_set(codec, CIR_I2C_QREAD, i2c_reg_data);
	अगर (cs8409_i2c_रुको_complete(codec) < 0) अणु
		codec_err(codec, "%s() Transaction Failed 0x%02x : 0x%04x\n",
			__func__, i2c_address, i2c_reg);
		वापस -EIO;
	पूर्ण

	/* Register in bits 15-8 and the data in 7-0 */
	पढ़ो_data = cs_venकरोr_coef_get(codec, CIR_I2C_QREAD);

	cs8409_enable_i2c_घड़ी(codec, 0);

	वापस पढ़ो_data & 0x0ff;
पूर्ण

/**
 * cs8409_i2c_ग_लिखो - CS8409 I2C Write.
 * @codec: the codec instance
 * @i2c_address: I2C Address
 * @i2c_reg: Register to ग_लिखो to
 * @i2c_data: Data to ग_लिखो
 * @paged: Is a paged transaction
 *
 * CS8409 I2C Write.
 * Returns negative on error, otherwise वापसs 0.
 */
अटल पूर्णांक cs8409_i2c_ग_लिखो(काष्ठा hda_codec *codec,
		अचिन्हित पूर्णांक i2c_address, अचिन्हित पूर्णांक i2c_reg,
		अचिन्हित पूर्णांक i2c_data,
		अचिन्हित पूर्णांक paged)
अणु
	अचिन्हित पूर्णांक i2c_reg_data;

	cs8409_enable_i2c_घड़ी(codec, 1);
	cs_venकरोr_coef_set(codec, CIR_I2C_ADDR, i2c_address);

	अगर (paged) अणु
		cs_venकरोr_coef_set(codec, CIR_I2C_QWRITE, i2c_reg >> 8);
		अगर (cs8409_i2c_रुको_complete(codec) < 0) अणु
			codec_err(codec,
				"%s() Paged Transaction Failed 0x%02x : 0x%04x\n",
				__func__, i2c_address, i2c_reg);
			वापस -EIO;
		पूर्ण
	पूर्ण

	i2c_reg_data = ((i2c_reg << 8) & 0x0ff00) | (i2c_data & 0x0ff);
	cs_venकरोr_coef_set(codec, CIR_I2C_QWRITE, i2c_reg_data);

	अगर (cs8409_i2c_रुको_complete(codec) < 0) अणु
		codec_err(codec, "%s() Transaction Failed 0x%02x : 0x%04x\n",
			__func__, i2c_address, i2c_reg);
		वापस -EIO;
	पूर्ण

	cs8409_enable_i2c_घड़ी(codec, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक cs8409_cs42l42_volume_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	u16 nid = get_amp_nid(kcontrol);
	u8 chs = get_amp_channels(kcontrol);

	codec_dbg(codec, "%s() nid: %d\n", __func__, nid);
	चयन (nid) अणु
	हाल CS8409_CS42L42_HP_PIN_NID:
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
		uinfo->count = chs == 3 ? 2 : 1;
		uinfo->value.पूर्णांकeger.min = CS8409_CS42L42_HP_VOL_REAL_MIN;
		uinfo->value.पूर्णांकeger.max = CS8409_CS42L42_HP_VOL_REAL_MAX;
		अवरोध;
	हाल CS8409_CS42L42_AMIC_PIN_NID:
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
		uinfo->count = chs == 3 ? 2 : 1;
		uinfo->value.पूर्णांकeger.min = CS8409_CS42L42_AMIC_VOL_REAL_MIN;
		uinfo->value.पूर्णांकeger.max = CS8409_CS42L42_AMIC_VOL_REAL_MAX;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cs8409_cs42l42_update_volume(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec = codec->spec;
	पूर्णांक data;

	mutex_lock(&spec->cs8409_i2c_mux);
	data = cs8409_i2c_पढ़ो(codec, CS42L42_I2C_ADDR,
				CS8409_CS42L42_REG_HS_VOLUME_CHA, 1);
	अगर (data >= 0)
		spec->cs42l42_hp_volume[0] = -data;
	अन्यथा
		spec->cs42l42_hp_volume[0] = CS8409_CS42L42_HP_VOL_REAL_MIN;
	data = cs8409_i2c_पढ़ो(codec, CS42L42_I2C_ADDR,
				CS8409_CS42L42_REG_HS_VOLUME_CHB, 1);
	अगर (data >= 0)
		spec->cs42l42_hp_volume[1] = -data;
	अन्यथा
		spec->cs42l42_hp_volume[1] = CS8409_CS42L42_HP_VOL_REAL_MIN;
	data = cs8409_i2c_पढ़ो(codec, CS42L42_I2C_ADDR,
				CS8409_CS42L42_REG_AMIC_VOLUME, 1);
	अगर (data >= 0)
		spec->cs42l42_hs_mic_volume[0] = -data;
	अन्यथा
		spec->cs42l42_hs_mic_volume[0] = CS8409_CS42L42_AMIC_VOL_REAL_MIN;
	mutex_unlock(&spec->cs8409_i2c_mux);
	spec->cs42l42_volume_init = 1;
पूर्ण

अटल पूर्णांक cs8409_cs42l42_volume_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा cs_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	पूर्णांक chs = get_amp_channels(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;

	अगर (!spec->cs42l42_volume_init) अणु
		snd_hda_घातer_up(codec);
		cs8409_cs42l42_update_volume(codec);
		snd_hda_घातer_करोwn(codec);
	पूर्ण
	चयन (nid) अणु
	हाल CS8409_CS42L42_HP_PIN_NID:
		अगर (chs & BIT(0))
			*valp++ = spec->cs42l42_hp_volume[0];
		अगर (chs & BIT(1))
			*valp++ = spec->cs42l42_hp_volume[1];
		अवरोध;
	हाल CS8409_CS42L42_AMIC_PIN_NID:
		अगर (chs & BIT(0))
			*valp++ = spec->cs42l42_hs_mic_volume[0];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cs8409_cs42l42_volume_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा cs_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	पूर्णांक chs = get_amp_channels(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;
	पूर्णांक change = 0;
	अक्षर vol;

	snd_hda_घातer_up(codec);
	चयन (nid) अणु
	हाल CS8409_CS42L42_HP_PIN_NID:
		mutex_lock(&spec->cs8409_i2c_mux);
		अगर (chs & BIT(0)) अणु
			vol = -(*valp);
			change = cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR,
				CS8409_CS42L42_REG_HS_VOLUME_CHA, vol, 1);
			valp++;
		पूर्ण
		अगर (chs & BIT(1)) अणु
			vol = -(*valp);
			change |= cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR,
				CS8409_CS42L42_REG_HS_VOLUME_CHB, vol, 1);
		पूर्ण
		mutex_unlock(&spec->cs8409_i2c_mux);
		अवरोध;
	हाल CS8409_CS42L42_AMIC_PIN_NID:
		mutex_lock(&spec->cs8409_i2c_mux);
		अगर (chs & BIT(0)) अणु
			change = cs8409_i2c_ग_लिखो(
				codec, CS42L42_I2C_ADDR,
				CS8409_CS42L42_REG_AMIC_VOLUME, (अक्षर)*valp, 1);
			valp++;
		पूर्ण
		mutex_unlock(&spec->cs8409_i2c_mux);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	cs8409_cs42l42_update_volume(codec);
	snd_hda_घातer_करोwn(codec);
	वापस change;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(
	cs8409_cs42l42_hp_db_scale,
	CS8409_CS42L42_HP_VOL_REAL_MIN * 100, 100, 1);

अटल स्थिर DECLARE_TLV_DB_SCALE(
	cs8409_cs42l42_amic_db_scale,
	CS8409_CS42L42_AMIC_VOL_REAL_MIN * 100, 100, 1);

अटल स्थिर काष्ठा snd_kcontrol_new cs8409_cs42l42_hp_volume_mixer = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.index = 0,
	.name = "Headphone Playback Volume",
	.subdevice = (HDA_SUBDEV_AMP_FLAG | HDA_SUBDEV_NID_FLAG),
	.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE
			 | SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.info = cs8409_cs42l42_volume_info,
	.get = cs8409_cs42l42_volume_get,
	.put = cs8409_cs42l42_volume_put,
	.tlv = अणु .p = cs8409_cs42l42_hp_db_scale पूर्ण,
	.निजी_value = HDA_COMPOSE_AMP_VAL(
		CS8409_CS42L42_HP_PIN_NID, 3, 0, HDA_OUTPUT)
		| HDA_AMP_VAL_MIN_MUTE
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cs8409_cs42l42_amic_volume_mixer = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.index = 0,
	.name = "Mic Capture Volume",
	.subdevice = (HDA_SUBDEV_AMP_FLAG | HDA_SUBDEV_NID_FLAG),
	.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE
			 | SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.info = cs8409_cs42l42_volume_info,
	.get = cs8409_cs42l42_volume_get,
	.put = cs8409_cs42l42_volume_put,
	.tlv = अणु .p = cs8409_cs42l42_amic_db_scale पूर्ण,
	.निजी_value = HDA_COMPOSE_AMP_VAL(
		CS8409_CS42L42_AMIC_PIN_NID, 1, 0, HDA_INPUT)
		| HDA_AMP_VAL_MIN_MUTE
पूर्ण;

/* Assert/release RTS# line to CS42L42 */
अटल व्योम cs8409_cs42l42_reset(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec = codec->spec;

	/* Assert RTS# line */
	snd_hda_codec_ग_लिखो(codec,
			codec->core.afg, 0, AC_VERB_SET_GPIO_DATA, 0);
	/* रुको ~10ms */
	usleep_range(10000, 15000);
	/* Release RTS# line */
	snd_hda_codec_ग_लिखो(codec,
			codec->core.afg, 0, AC_VERB_SET_GPIO_DATA, GPIO5_INT);
	/* रुको ~10ms */
	usleep_range(10000, 15000);

	mutex_lock(&spec->cs8409_i2c_mux);

	/* Clear पूर्णांकerrupts, by पढ़ोing पूर्णांकerrupt status रेजिस्टरs */
	cs8409_i2c_पढ़ो(codec, CS42L42_I2C_ADDR, 0x1308, 1);
	cs8409_i2c_पढ़ो(codec, CS42L42_I2C_ADDR, 0x1309, 1);
	cs8409_i2c_पढ़ो(codec, CS42L42_I2C_ADDR, 0x130A, 1);
	cs8409_i2c_पढ़ो(codec, CS42L42_I2C_ADDR, 0x130F, 1);

	mutex_unlock(&spec->cs8409_i2c_mux);

पूर्ण

/* Configure CS42L42 slave codec क्रम jack स्वतःdetect */
अटल व्योम cs8409_cs42l42_enable_jack_detect(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec = codec->spec;

	mutex_lock(&spec->cs8409_i2c_mux);

	/* Set TIP_SENSE_EN क्रम analog front-end of tip sense. */
	cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR, 0x1b70, 0x0020, 1);
	/* Clear WAKE# */
	cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR, 0x1b71, 0x0001, 1);
	/* Wait ~2.5ms */
	usleep_range(2500, 3000);
	/* Set mode WAKE# output follows the combination logic directly */
	cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR, 0x1b71, 0x0020, 1);
	/* Clear पूर्णांकerrupts status */
	cs8409_i2c_पढ़ो(codec, CS42L42_I2C_ADDR, 0x130f, 1);
	cs8409_i2c_पढ़ो(codec, CS42L42_I2C_ADDR, 0x1b7b, 1);
	/* Enable पूर्णांकerrupt */
	cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR, 0x1320, 0x03, 1);
	cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR, 0x1b79, 0x00, 1);

	mutex_unlock(&spec->cs8409_i2c_mux);
पूर्ण

/* Enable and run CS42L42 slave codec jack स्वतः detect */
अटल व्योम cs8409_cs42l42_run_jack_detect(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec = codec->spec;

	mutex_lock(&spec->cs8409_i2c_mux);

	/* Clear पूर्णांकerrupts */
	cs8409_i2c_पढ़ो(codec, CS42L42_I2C_ADDR, 0x1308, 1);
	cs8409_i2c_पढ़ो(codec, CS42L42_I2C_ADDR, 0x1b77, 1);

	cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR, 0x1102, 0x87, 1);
	cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR, 0x1f06, 0x86, 1);
	cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR, 0x1b74, 0x07, 1);
	cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR, 0x131b, 0x01, 1);
	cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR, 0x1120, 0x80, 1);
	/* Wait ~110ms*/
	usleep_range(110000, 200000);
	cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR, 0x111f, 0x77, 1);
	cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR, 0x1120, 0xc0, 1);
	/* Wait ~10ms */
	usleep_range(10000, 25000);

	mutex_unlock(&spec->cs8409_i2c_mux);

पूर्ण

अटल व्योम cs8409_cs42l42_reg_setup(काष्ठा hda_codec *codec)
अणु
	स्थिर काष्ठा cs8409_i2c_param *seq = cs42l42_init_reg_seq;
	काष्ठा cs_spec *spec = codec->spec;

	mutex_lock(&spec->cs8409_i2c_mux);

	क्रम (; seq->addr; seq++)
		cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR, seq->addr, seq->reg, 1);

	mutex_unlock(&spec->cs8409_i2c_mux);

पूर्ण

/*
 * In the हाल of CS8409 we करो not have unsolicited events from NID's 0x24
 * and 0x34 where hs mic and hp are connected. Companion codec CS42L42 will
 * generate पूर्णांकerrupt via gpio 4 to notअगरy jack events. We have to overग_लिखो
 * generic snd_hda_jack_unsol_event(), पढ़ो CS42L42 jack detect status रेजिस्टरs
 * and then notअगरy status via generic snd_hda_jack_unsol_event() call.
 */
अटल व्योम cs8409_jack_unsol_event(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक res)
अणु
	काष्ठा cs_spec *spec = codec->spec;
	पूर्णांक status_changed = 0;
	पूर्णांक reg_cdc_status;
	पूर्णांक reg_hs_status;
	पूर्णांक reg_ts_status;
	पूर्णांक type;
	काष्ठा hda_jack_tbl *jk;

	/* jack_unsol_event() will be called every समय gpio line changing state.
	 * In this हाल gpio4 line goes up as a result of पढ़ोing पूर्णांकerrupt status
	 * रेजिस्टरs in previous cs8409_jack_unsol_event() call.
	 * We करोn't need to handle this event, ignoring...
	 */
	अगर ((res & (1 << 4)))
		वापस;

	mutex_lock(&spec->cs8409_i2c_mux);

	/* Read jack detect status रेजिस्टरs */
	reg_cdc_status = cs8409_i2c_पढ़ो(codec, CS42L42_I2C_ADDR, 0x1308, 1);
	reg_hs_status = cs8409_i2c_पढ़ो(codec, CS42L42_I2C_ADDR, 0x1124, 1);
	reg_ts_status = cs8409_i2c_पढ़ो(codec, CS42L42_I2C_ADDR, 0x130f, 1);

	/* Clear पूर्णांकerrupts, by पढ़ोing पूर्णांकerrupt status रेजिस्टरs */
	cs8409_i2c_पढ़ो(codec, CS42L42_I2C_ADDR, 0x1b7b, 1);

	mutex_unlock(&spec->cs8409_i2c_mux);

	/* If status values are < 0, पढ़ो error has occurred. */
	अगर (reg_cdc_status < 0 || reg_hs_status < 0 || reg_ts_status < 0)
		वापस;

	/* HSDET_AUTO_DONE */
	अगर (reg_cdc_status & CS42L42_HSDET_AUTO_DONE) अणु

		type = ((reg_hs_status & CS42L42_HSTYPE_MASK) + 1);
		/* CS42L42 reports optical jack as type 4
		 * We करोn't handle optical jack
		 */
		अगर (type != 4) अणु
			अगर (!spec->cs42l42_hp_jack_in) अणु
				status_changed = 1;
				spec->cs42l42_hp_jack_in = 1;
			पूर्ण
			/* type = 3 has no mic */
			अगर ((!spec->cs42l42_mic_jack_in) && (type != 3)) अणु
				status_changed = 1;
				spec->cs42l42_mic_jack_in = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (spec->cs42l42_hp_jack_in || spec->cs42l42_mic_jack_in) अणु
				status_changed = 1;
				spec->cs42l42_hp_jack_in = 0;
				spec->cs42l42_mic_jack_in = 0;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		/* TIP_SENSE INSERT/REMOVE */
		चयन (reg_ts_status) अणु
		हाल CS42L42_JACK_INSERTED:
			cs8409_cs42l42_run_jack_detect(codec);
			अवरोध;

		हाल CS42L42_JACK_REMOVED:
			अगर (spec->cs42l42_hp_jack_in || spec->cs42l42_mic_jack_in) अणु
				status_changed = 1;
				spec->cs42l42_hp_jack_in = 0;
				spec->cs42l42_mic_jack_in = 0;
			पूर्ण
			अवरोध;

		शेष:
			/* jack in transition */
			status_changed = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (status_changed) अणु

		snd_hda_set_pin_ctl(codec, CS8409_CS42L42_SPK_PIN_NID,
				spec->cs42l42_hp_jack_in ? 0 : PIN_OUT);

		/* Report jack*/
		jk = snd_hda_jack_tbl_get_mst(codec, CS8409_CS42L42_HP_PIN_NID, 0);
		अगर (jk) अणु
			snd_hda_jack_unsol_event(codec,
				(jk->tag << AC_UNSOL_RES_TAG_SHIFT) & AC_UNSOL_RES_TAG);
		पूर्ण
		/* Report jack*/
		jk = snd_hda_jack_tbl_get_mst(codec, CS8409_CS42L42_AMIC_PIN_NID, 0);
		अगर (jk) अणु
			snd_hda_jack_unsol_event(codec,
				(jk->tag << AC_UNSOL_RES_TAG_SHIFT) & AC_UNSOL_RES_TAG);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
/* Manage PDREF, when transition to D3hot */
अटल पूर्णांक cs8409_suspend(काष्ठा hda_codec *codec)
अणु
	काष्ठा cs_spec *spec = codec->spec;

	mutex_lock(&spec->cs8409_i2c_mux);
	/* Power करोwn CS42L42 ASP/EQ/MIX/HP */
	cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR, 0x1101, 0xfe, 1);
	mutex_unlock(&spec->cs8409_i2c_mux);
	/* Assert CS42L42 RTS# line */
	snd_hda_codec_ग_लिखो(codec,
			codec->core.afg, 0, AC_VERB_SET_GPIO_DATA, 0);

	snd_hda_shutup_pins(codec);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Enable/Disable Unsolicited Response क्रम gpio(s) 3,4 */
अटल व्योम cs8409_enable_ur(काष्ठा hda_codec *codec, पूर्णांक flag)
अणु
	/* GPIO4 INT# and GPIO3 WAKE# */
	snd_hda_codec_ग_लिखो(codec, codec->core.afg,
			0, AC_VERB_SET_GPIO_UNSOLICITED_RSP_MASK,
			flag ? (GPIO3_INT | GPIO4_INT) : 0);

	snd_hda_codec_ग_लिखो(codec, codec->core.afg,
			0, AC_VERB_SET_UNSOLICITED_ENABLE,
			flag ? AC_UNSOL_ENABLED : 0);

पूर्ण

/* Venकरोr specअगरic HW configuration
 * PLL, ASP, I2C, SPI, GPIOs, DMIC etc...
 */
अटल व्योम cs8409_cs42l42_hw_init(काष्ठा hda_codec *codec)
अणु
	स्थिर काष्ठा cs8409_cir_param *seq = cs8409_cs42l42_hw_cfg;
	स्थिर काष्ठा cs8409_cir_param *seq_bullseye = cs8409_cs42l42_bullseye_atn;
	काष्ठा cs_spec *spec = codec->spec;

	अगर (spec->gpio_mask) अणु
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, AC_VERB_SET_GPIO_MASK,
				    spec->gpio_mask);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, AC_VERB_SET_GPIO_सूचीECTION,
				    spec->gpio_dir);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, AC_VERB_SET_GPIO_DATA,
				    spec->gpio_data);
	पूर्ण

	क्रम (; seq->nid; seq++)
		cs_venकरोr_coef_set(codec, seq->cir, seq->coeff);

	अगर (codec->fixup_id == CS8409_BULLSEYE)
		क्रम (; seq_bullseye->nid; seq_bullseye++)
			cs_venकरोr_coef_set(codec, seq_bullseye->cir, seq_bullseye->coeff);

	/* Disable Unsolicited Response during boot */
	cs8409_enable_ur(codec, 0);

	/* Reset CS42L42 */
	cs8409_cs42l42_reset(codec);

	/* Initialise CS42L42 companion codec */
	cs8409_cs42l42_reg_setup(codec);

	अगर (codec->fixup_id == CS8409_WARLOCK ||
			codec->fixup_id == CS8409_CYBORG) अणु
		/* FULL_SCALE_VOL = 0 क्रम Warlock / Cyborg */
		mutex_lock(&spec->cs8409_i2c_mux);
		cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR, 0x2001, 0x01, 1);
		mutex_unlock(&spec->cs8409_i2c_mux);
		/* DMIC1_MO=00b, DMIC1/2_SR=1 */
		cs_venकरोr_coef_set(codec, 0x09, 0x0003);
	पूर्ण

	/* Restore Volumes after Resume */
	अगर (spec->cs42l42_volume_init) अणु
		mutex_lock(&spec->cs8409_i2c_mux);
		cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR,
					CS8409_CS42L42_REG_HS_VOLUME_CHA,
					-spec->cs42l42_hp_volume[0],
					1);
		cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR,
					CS8409_CS42L42_REG_HS_VOLUME_CHB,
					-spec->cs42l42_hp_volume[1],
					1);
		cs8409_i2c_ग_लिखो(codec, CS42L42_I2C_ADDR,
					CS8409_CS42L42_REG_AMIC_VOLUME,
					spec->cs42l42_hs_mic_volume[0],
					1);
		mutex_unlock(&spec->cs8409_i2c_mux);
	पूर्ण

	cs8409_cs42l42_update_volume(codec);

	cs8409_cs42l42_enable_jack_detect(codec);

	/* Enable Unsolicited Response */
	cs8409_enable_ur(codec, 1);
पूर्ण

अटल पूर्णांक cs8409_cs42l42_init(काष्ठा hda_codec *codec)
अणु
	पूर्णांक ret = snd_hda_gen_init(codec);

	अगर (!ret)
		snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_INIT);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hda_codec_ops cs8409_cs42l42_patch_ops = अणु
	.build_controls = cs_build_controls,
	.build_pcms = snd_hda_gen_build_pcms,
	.init = cs8409_cs42l42_init,
	.मुक्त = cs_मुक्त,
	.unsol_event = cs8409_jack_unsol_event,
#अगर_घोषित CONFIG_PM
	.suspend = cs8409_suspend,
#पूर्ण_अगर
पूर्ण;

अटल व्योम cs8409_cs42l42_fixups(काष्ठा hda_codec *codec,
				    स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा cs_spec *spec = codec->spec;
	पूर्णांक caps;

	चयन (action) अणु
	हाल HDA_FIXUP_ACT_PRE_PROBE:
		snd_hda_add_verbs(codec, cs8409_cs42l42_init_verbs);
		/* verb exec op override */
		spec->exec_verb = codec->core.exec_verb;
		codec->core.exec_verb = cs8409_cs42l42_exec_verb;

		mutex_init(&spec->cs8409_i2c_mux);

		codec->patch_ops = cs8409_cs42l42_patch_ops;

		spec->gen.suppress_स्वतः_mute = 1;
		spec->gen.no_primary_hp = 1;
		spec->gen.suppress_vmaster = 1;

		/* GPIO 5 out, 3,4 in */
		spec->gpio_dir = GPIO5_INT;
		spec->gpio_data = 0;
		spec->gpio_mask = 0x03f;

		spec->cs42l42_hp_jack_in = 0;
		spec->cs42l42_mic_jack_in = 0;

		/* Basic initial sequence क्रम specअगरic hw configuration */
		snd_hda_sequence_ग_लिखो(codec, cs8409_cs42l42_init_verbs);

		/* CS8409 is simple HDA bridge and पूर्णांकended to be used with a remote
		 * companion codec. Most of input/output PIN(s) have only basic
		 * capabilities. NID(s) 0x24 and 0x34 have only OUTC and INC
		 * capabilities and no presence detect capable (PDC) and call to
		 * snd_hda_gen_build_controls() will mark them as non detectable
		 * phantom jacks. However, in this configuration companion codec
		 * CS42L42 is connected to these pins and it has jack detect
		 * capabilities. We have to override pin capabilities,
		 * otherwise they will not be created as input devices.
		 */
		caps = snd_hdac_पढ़ो_parm(&codec->core, CS8409_CS42L42_HP_PIN_NID,
				AC_PAR_PIN_CAP);
		अगर (caps >= 0)
			snd_hdac_override_parm(&codec->core,
				CS8409_CS42L42_HP_PIN_NID, AC_PAR_PIN_CAP,
				(caps | (AC_PINCAP_IMP_SENSE | AC_PINCAP_PRES_DETECT)));

		caps = snd_hdac_पढ़ो_parm(&codec->core, CS8409_CS42L42_AMIC_PIN_NID,
				AC_PAR_PIN_CAP);
		अगर (caps >= 0)
			snd_hdac_override_parm(&codec->core,
				CS8409_CS42L42_AMIC_PIN_NID, AC_PAR_PIN_CAP,
				(caps | (AC_PINCAP_IMP_SENSE | AC_PINCAP_PRES_DETECT)));

		snd_hda_override_wcaps(codec, CS8409_CS42L42_HP_PIN_NID,
			(get_wcaps(codec, CS8409_CS42L42_HP_PIN_NID) | AC_WCAP_UNSOL_CAP));

		snd_hda_override_wcaps(codec, CS8409_CS42L42_AMIC_PIN_NID,
			(get_wcaps(codec, CS8409_CS42L42_AMIC_PIN_NID) | AC_WCAP_UNSOL_CAP));
		अवरोध;
	हाल HDA_FIXUP_ACT_PROBE:

		/* Set initial DMIC volume to -26 dB */
		snd_hda_codec_amp_init_stereo(codec, CS8409_CS42L42_DMIC_ADC_PIN_NID,
				HDA_INPUT, 0, 0xff, 0x19);
		snd_hda_gen_add_kctl(&spec->gen,
			शून्य, &cs8409_cs42l42_hp_volume_mixer);
		snd_hda_gen_add_kctl(&spec->gen,
			शून्य, &cs8409_cs42l42_amic_volume_mixer);
		cs8409_cs42l42_hw_init(codec);
		snd_hda_codec_set_name(codec, "CS8409/CS42L42");
		अवरोध;
	हाल HDA_FIXUP_ACT_INIT:
		cs8409_cs42l42_hw_init(codec);
		fallthrough;
	हाल HDA_FIXUP_ACT_BUILD:
		/* Run jack स्वतः detect first समय on boot
		 * after controls have been added, to check अगर jack has
		 * been alपढ़ोy plugged in.
		 * Run immediately after init.
		 */
		cs8409_cs42l42_run_jack_detect(codec);
		usleep_range(100000, 150000);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक cs8409_cs42l42_exec_verb(काष्ठा hdac_device *dev,
		अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक *res)
अणु
	काष्ठा hda_codec *codec = container_of(dev, काष्ठा hda_codec, core);
	काष्ठा cs_spec *spec = codec->spec;

	अचिन्हित पूर्णांक nid = ((cmd >> 20) & 0x07f);
	अचिन्हित पूर्णांक verb = ((cmd >> 8) & 0x0fff);

	/* CS8409 pins have no AC_PINSENSE_PRESENCE
	 * capabilities. We have to पूर्णांकercept 2 calls क्रम pins 0x24 and 0x34
	 * and वापस correct pin sense values क्रम पढ़ो_pin_sense() call from
	 * hda_jack based on CS42L42 jack detect status.
	 */
	चयन (nid) अणु
	हाल CS8409_CS42L42_HP_PIN_NID:
		अगर (verb == AC_VERB_GET_PIN_SENSE) अणु
			*res = (spec->cs42l42_hp_jack_in) ? AC_PINSENSE_PRESENCE : 0;
			वापस 0;
		पूर्ण
		अवरोध;

	हाल CS8409_CS42L42_AMIC_PIN_NID:
		अगर (verb == AC_VERB_GET_PIN_SENSE) अणु
			*res = (spec->cs42l42_mic_jack_in) ? AC_PINSENSE_PRESENCE : 0;
			वापस 0;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस spec->exec_verb(dev, cmd, flags, res);
पूर्ण

अटल पूर्णांक patch_cs8409(काष्ठा hda_codec *codec)
अणु
	पूर्णांक err;

	अगर (!cs_alloc_spec(codec, CS8409_VENDOR_NID))
		वापस -ENOMEM;

	snd_hda_pick_fixup(codec,
			cs8409_models, cs8409_fixup_tbl, cs8409_fixups);

	codec_dbg(codec, "Picked ID=%d, VID=%08x, DEV=%08x\n",
			codec->fixup_id,
			codec->bus->pci->subप्रणाली_venकरोr,
			codec->bus->pci->subप्रणाली_device);

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	err = cs_parse_स्वतः_config(codec);
	अगर (err < 0) अणु
		cs_मुक्त(codec);
		वापस err;
	पूर्ण

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);
	वापस 0;
पूर्ण

/*
 * patch entries
 */
अटल स्थिर काष्ठा hda_device_id snd_hda_id_cirrus[] = अणु
	HDA_CODEC_ENTRY(0x10134206, "CS4206", patch_cs420x),
	HDA_CODEC_ENTRY(0x10134207, "CS4207", patch_cs420x),
	HDA_CODEC_ENTRY(0x10134208, "CS4208", patch_cs4208),
	HDA_CODEC_ENTRY(0x10134210, "CS4210", patch_cs4210),
	HDA_CODEC_ENTRY(0x10134213, "CS4213", patch_cs4213),
	HDA_CODEC_ENTRY(0x10138409, "CS8409", patch_cs8409),
	अणुपूर्ण /* terminator */
पूर्ण;
MODULE_DEVICE_TABLE(hdaudio, snd_hda_id_cirrus);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Cirrus Logic HD-audio codec");

अटल काष्ठा hda_codec_driver cirrus_driver = अणु
	.id = snd_hda_id_cirrus,
पूर्ण;

module_hda_codec_driver(cirrus_driver);
