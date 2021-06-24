<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>,
 *                   Takashi Iwai <tiwai@suse.de>
 *                   Creative Lअसल, Inc.
 *  Routines क्रम control of EMU10K1 chips / mixer routines
 *  Multichannel PCM support Copyright (c) Lee Revell <rlrevell@joe-job.com>
 *
 *  Copyright (c) by James Courtier-Dutton <James@superbug.co.uk>
 *  	Added EMU 1010 support.
 *
 *  BUGS:
 *    --
 *
 *  TODO:
 *    --
 */

#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <sound/core.h>
#समावेश <sound/emu10k1.h>
#समावेश <linux/delay.h>
#समावेश <sound/tlv.h>

#समावेश "p17v.h"

#घोषणा AC97_ID_STAC9758	0x83847658

अटल स्थिर DECLARE_TLV_DB_SCALE(snd_audigy_db_scale2, -10350, 50, 1); /* WM8775 gain scale */

अटल पूर्णांक snd_emu10k1_spdअगर_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
                                 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अचिन्हित दीर्घ flags;

	/* Limit: emu->spdअगर_bits */
	अगर (idx >= 3)
		वापस -EINVAL;
	spin_lock_irqsave(&emu->reg_lock, flags);
	ucontrol->value.iec958.status[0] = (emu->spdअगर_bits[idx] >> 0) & 0xff;
	ucontrol->value.iec958.status[1] = (emu->spdअगर_bits[idx] >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = (emu->spdअगर_bits[idx] >> 16) & 0xff;
	ucontrol->value.iec958.status[3] = (emu->spdअगर_bits[idx] >> 24) & 0xff;
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_spdअगर_get_mask(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = 0xff;
	ucontrol->value.iec958.status[1] = 0xff;
	ucontrol->value.iec958.status[2] = 0xff;
	ucontrol->value.iec958.status[3] = 0xff;
	वापस 0;
पूर्ण

/*
 * Items labels in क्रमागत mixer controls assigning source data to
 * each destination
 */
अटल स्थिर अक्षर * स्थिर emu1010_src_texts[] = अणु
	"Silence",
	"Dock Mic A",
	"Dock Mic B",
	"Dock ADC1 Left",
	"Dock ADC1 Right",
	"Dock ADC2 Left",
	"Dock ADC2 Right",
	"Dock ADC3 Left",
	"Dock ADC3 Right",
	"0202 ADC Left",
	"0202 ADC Right",
	"0202 SPDIF Left",
	"0202 SPDIF Right",
	"ADAT 0",
	"ADAT 1",
	"ADAT 2",
	"ADAT 3",
	"ADAT 4",
	"ADAT 5",
	"ADAT 6",
	"ADAT 7",
	"DSP 0",
	"DSP 1",
	"DSP 2",
	"DSP 3",
	"DSP 4",
	"DSP 5",
	"DSP 6",
	"DSP 7",
	"DSP 8",
	"DSP 9",
	"DSP 10",
	"DSP 11",
	"DSP 12",
	"DSP 13",
	"DSP 14",
	"DSP 15",
	"DSP 16",
	"DSP 17",
	"DSP 18",
	"DSP 19",
	"DSP 20",
	"DSP 21",
	"DSP 22",
	"DSP 23",
	"DSP 24",
	"DSP 25",
	"DSP 26",
	"DSP 27",
	"DSP 28",
	"DSP 29",
	"DSP 30",
	"DSP 31",
पूर्ण;

/* 1616(m) cardbus */

अटल स्थिर अक्षर * स्थिर emu1616_src_texts[] = अणु
	"Silence",
	"Dock Mic A",
	"Dock Mic B",
	"Dock ADC1 Left",
	"Dock ADC1 Right",
	"Dock ADC2 Left",
	"Dock ADC2 Right",
	"Dock SPDIF Left",
	"Dock SPDIF Right",
	"ADAT 0",
	"ADAT 1",
	"ADAT 2",
	"ADAT 3",
	"ADAT 4",
	"ADAT 5",
	"ADAT 6",
	"ADAT 7",
	"DSP 0",
	"DSP 1",
	"DSP 2",
	"DSP 3",
	"DSP 4",
	"DSP 5",
	"DSP 6",
	"DSP 7",
	"DSP 8",
	"DSP 9",
	"DSP 10",
	"DSP 11",
	"DSP 12",
	"DSP 13",
	"DSP 14",
	"DSP 15",
	"DSP 16",
	"DSP 17",
	"DSP 18",
	"DSP 19",
	"DSP 20",
	"DSP 21",
	"DSP 22",
	"DSP 23",
	"DSP 24",
	"DSP 25",
	"DSP 26",
	"DSP 27",
	"DSP 28",
	"DSP 29",
	"DSP 30",
	"DSP 31",
पूर्ण;


/*
 * List of data sources available क्रम each destination
 */
अटल स्थिर अचिन्हित पूर्णांक emu1010_src_regs[] = अणु
	EMU_SRC_SILENCE,/* 0 */
	EMU_SRC_DOCK_MIC_A1, /* 1 */
	EMU_SRC_DOCK_MIC_B1, /* 2 */
	EMU_SRC_DOCK_ADC1_LEFT1, /* 3 */
	EMU_SRC_DOCK_ADC1_RIGHT1, /* 4 */
	EMU_SRC_DOCK_ADC2_LEFT1, /* 5 */
	EMU_SRC_DOCK_ADC2_RIGHT1, /* 6 */
	EMU_SRC_DOCK_ADC3_LEFT1, /* 7 */
	EMU_SRC_DOCK_ADC3_RIGHT1, /* 8 */
	EMU_SRC_HAMOA_ADC_LEFT1, /* 9 */
	EMU_SRC_HAMOA_ADC_RIGHT1, /* 10 */
	EMU_SRC_HANA_SPDIF_LEFT1, /* 11 */
	EMU_SRC_HANA_SPDIF_RIGHT1, /* 12 */
	EMU_SRC_HANA_ADAT, /* 13 */
	EMU_SRC_HANA_ADAT+1, /* 14 */
	EMU_SRC_HANA_ADAT+2, /* 15 */
	EMU_SRC_HANA_ADAT+3, /* 16 */
	EMU_SRC_HANA_ADAT+4, /* 17 */
	EMU_SRC_HANA_ADAT+5, /* 18 */
	EMU_SRC_HANA_ADAT+6, /* 19 */
	EMU_SRC_HANA_ADAT+7, /* 20 */
	EMU_SRC_ALICE_EMU32A, /* 21 */
	EMU_SRC_ALICE_EMU32A+1, /* 22 */
	EMU_SRC_ALICE_EMU32A+2, /* 23 */
	EMU_SRC_ALICE_EMU32A+3, /* 24 */
	EMU_SRC_ALICE_EMU32A+4, /* 25 */
	EMU_SRC_ALICE_EMU32A+5, /* 26 */
	EMU_SRC_ALICE_EMU32A+6, /* 27 */
	EMU_SRC_ALICE_EMU32A+7, /* 28 */
	EMU_SRC_ALICE_EMU32A+8, /* 29 */
	EMU_SRC_ALICE_EMU32A+9, /* 30 */
	EMU_SRC_ALICE_EMU32A+0xa, /* 31 */
	EMU_SRC_ALICE_EMU32A+0xb, /* 32 */
	EMU_SRC_ALICE_EMU32A+0xc, /* 33 */
	EMU_SRC_ALICE_EMU32A+0xd, /* 34 */
	EMU_SRC_ALICE_EMU32A+0xe, /* 35 */
	EMU_SRC_ALICE_EMU32A+0xf, /* 36 */
	EMU_SRC_ALICE_EMU32B, /* 37 */
	EMU_SRC_ALICE_EMU32B+1, /* 38 */
	EMU_SRC_ALICE_EMU32B+2, /* 39 */
	EMU_SRC_ALICE_EMU32B+3, /* 40 */
	EMU_SRC_ALICE_EMU32B+4, /* 41 */
	EMU_SRC_ALICE_EMU32B+5, /* 42 */
	EMU_SRC_ALICE_EMU32B+6, /* 43 */
	EMU_SRC_ALICE_EMU32B+7, /* 44 */
	EMU_SRC_ALICE_EMU32B+8, /* 45 */
	EMU_SRC_ALICE_EMU32B+9, /* 46 */
	EMU_SRC_ALICE_EMU32B+0xa, /* 47 */
	EMU_SRC_ALICE_EMU32B+0xb, /* 48 */
	EMU_SRC_ALICE_EMU32B+0xc, /* 49 */
	EMU_SRC_ALICE_EMU32B+0xd, /* 50 */
	EMU_SRC_ALICE_EMU32B+0xe, /* 51 */
	EMU_SRC_ALICE_EMU32B+0xf, /* 52 */
पूर्ण;

/* 1616(m) cardbus */
अटल स्थिर अचिन्हित पूर्णांक emu1616_src_regs[] = अणु
	EMU_SRC_SILENCE,
	EMU_SRC_DOCK_MIC_A1,
	EMU_SRC_DOCK_MIC_B1,
	EMU_SRC_DOCK_ADC1_LEFT1,
	EMU_SRC_DOCK_ADC1_RIGHT1,
	EMU_SRC_DOCK_ADC2_LEFT1,
	EMU_SRC_DOCK_ADC2_RIGHT1,
	EMU_SRC_MDOCK_SPDIF_LEFT1,
	EMU_SRC_MDOCK_SPDIF_RIGHT1,
	EMU_SRC_MDOCK_ADAT,
	EMU_SRC_MDOCK_ADAT+1,
	EMU_SRC_MDOCK_ADAT+2,
	EMU_SRC_MDOCK_ADAT+3,
	EMU_SRC_MDOCK_ADAT+4,
	EMU_SRC_MDOCK_ADAT+5,
	EMU_SRC_MDOCK_ADAT+6,
	EMU_SRC_MDOCK_ADAT+7,
	EMU_SRC_ALICE_EMU32A,
	EMU_SRC_ALICE_EMU32A+1,
	EMU_SRC_ALICE_EMU32A+2,
	EMU_SRC_ALICE_EMU32A+3,
	EMU_SRC_ALICE_EMU32A+4,
	EMU_SRC_ALICE_EMU32A+5,
	EMU_SRC_ALICE_EMU32A+6,
	EMU_SRC_ALICE_EMU32A+7,
	EMU_SRC_ALICE_EMU32A+8,
	EMU_SRC_ALICE_EMU32A+9,
	EMU_SRC_ALICE_EMU32A+0xa,
	EMU_SRC_ALICE_EMU32A+0xb,
	EMU_SRC_ALICE_EMU32A+0xc,
	EMU_SRC_ALICE_EMU32A+0xd,
	EMU_SRC_ALICE_EMU32A+0xe,
	EMU_SRC_ALICE_EMU32A+0xf,
	EMU_SRC_ALICE_EMU32B,
	EMU_SRC_ALICE_EMU32B+1,
	EMU_SRC_ALICE_EMU32B+2,
	EMU_SRC_ALICE_EMU32B+3,
	EMU_SRC_ALICE_EMU32B+4,
	EMU_SRC_ALICE_EMU32B+5,
	EMU_SRC_ALICE_EMU32B+6,
	EMU_SRC_ALICE_EMU32B+7,
	EMU_SRC_ALICE_EMU32B+8,
	EMU_SRC_ALICE_EMU32B+9,
	EMU_SRC_ALICE_EMU32B+0xa,
	EMU_SRC_ALICE_EMU32B+0xb,
	EMU_SRC_ALICE_EMU32B+0xc,
	EMU_SRC_ALICE_EMU32B+0xd,
	EMU_SRC_ALICE_EMU32B+0xe,
	EMU_SRC_ALICE_EMU32B+0xf,
पूर्ण;

/*
 * Data destinations - physical EMU outमाला_दो.
 * Each destination has an क्रमागत mixer control to choose a data source
 */
अटल स्थिर अचिन्हित पूर्णांक emu1010_output_dst[] = अणु
	EMU_DST_DOCK_DAC1_LEFT1, /* 0 */
	EMU_DST_DOCK_DAC1_RIGHT1, /* 1 */
	EMU_DST_DOCK_DAC2_LEFT1, /* 2 */
	EMU_DST_DOCK_DAC2_RIGHT1, /* 3 */
	EMU_DST_DOCK_DAC3_LEFT1, /* 4 */
	EMU_DST_DOCK_DAC3_RIGHT1, /* 5 */
	EMU_DST_DOCK_DAC4_LEFT1, /* 6 */
	EMU_DST_DOCK_DAC4_RIGHT1, /* 7 */
	EMU_DST_DOCK_PHONES_LEFT1, /* 8 */
	EMU_DST_DOCK_PHONES_RIGHT1, /* 9 */
	EMU_DST_DOCK_SPDIF_LEFT1, /* 10 */
	EMU_DST_DOCK_SPDIF_RIGHT1, /* 11 */
	EMU_DST_HANA_SPDIF_LEFT1, /* 12 */
	EMU_DST_HANA_SPDIF_RIGHT1, /* 13 */
	EMU_DST_HAMOA_DAC_LEFT1, /* 14 */
	EMU_DST_HAMOA_DAC_RIGHT1, /* 15 */
	EMU_DST_HANA_ADAT, /* 16 */
	EMU_DST_HANA_ADAT+1, /* 17 */
	EMU_DST_HANA_ADAT+2, /* 18 */
	EMU_DST_HANA_ADAT+3, /* 19 */
	EMU_DST_HANA_ADAT+4, /* 20 */
	EMU_DST_HANA_ADAT+5, /* 21 */
	EMU_DST_HANA_ADAT+6, /* 22 */
	EMU_DST_HANA_ADAT+7, /* 23 */
पूर्ण;

/* 1616(m) cardbus */
अटल स्थिर अचिन्हित पूर्णांक emu1616_output_dst[] = अणु
	EMU_DST_DOCK_DAC1_LEFT1,
	EMU_DST_DOCK_DAC1_RIGHT1,
	EMU_DST_DOCK_DAC2_LEFT1,
	EMU_DST_DOCK_DAC2_RIGHT1,
	EMU_DST_DOCK_DAC3_LEFT1,
	EMU_DST_DOCK_DAC3_RIGHT1,
	EMU_DST_MDOCK_SPDIF_LEFT1,
	EMU_DST_MDOCK_SPDIF_RIGHT1,
	EMU_DST_MDOCK_ADAT,
	EMU_DST_MDOCK_ADAT+1,
	EMU_DST_MDOCK_ADAT+2,
	EMU_DST_MDOCK_ADAT+3,
	EMU_DST_MDOCK_ADAT+4,
	EMU_DST_MDOCK_ADAT+5,
	EMU_DST_MDOCK_ADAT+6,
	EMU_DST_MDOCK_ADAT+7,
	EMU_DST_MANA_DAC_LEFT,
	EMU_DST_MANA_DAC_RIGHT,
पूर्ण;

/*
 * Data destinations - HANA outमाला_दो going to Alice2 (audigy) क्रम
 *   capture (EMU32 + I2S links)
 * Each destination has an क्रमागत mixer control to choose a data source
 */
अटल स्थिर अचिन्हित पूर्णांक emu1010_input_dst[] = अणु
	EMU_DST_ALICE2_EMU32_0,
	EMU_DST_ALICE2_EMU32_1,
	EMU_DST_ALICE2_EMU32_2,
	EMU_DST_ALICE2_EMU32_3,
	EMU_DST_ALICE2_EMU32_4,
	EMU_DST_ALICE2_EMU32_5,
	EMU_DST_ALICE2_EMU32_6,
	EMU_DST_ALICE2_EMU32_7,
	EMU_DST_ALICE2_EMU32_8,
	EMU_DST_ALICE2_EMU32_9,
	EMU_DST_ALICE2_EMU32_A,
	EMU_DST_ALICE2_EMU32_B,
	EMU_DST_ALICE2_EMU32_C,
	EMU_DST_ALICE2_EMU32_D,
	EMU_DST_ALICE2_EMU32_E,
	EMU_DST_ALICE2_EMU32_F,
	EMU_DST_ALICE_I2S0_LEFT,
	EMU_DST_ALICE_I2S0_RIGHT,
	EMU_DST_ALICE_I2S1_LEFT,
	EMU_DST_ALICE_I2S1_RIGHT,
	EMU_DST_ALICE_I2S2_LEFT,
	EMU_DST_ALICE_I2S2_RIGHT,
पूर्ण;

अटल पूर्णांक snd_emu1010_input_output_source_info(काष्ठा snd_kcontrol *kcontrol,
						काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);

	अगर (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616)
		वापस snd_ctl_क्रमागत_info(uinfo, 1, 49, emu1616_src_texts);
	अन्यथा
		वापस snd_ctl_क्रमागत_info(uinfo, 1, 53, emu1010_src_texts);
पूर्ण

अटल पूर्णांक snd_emu1010_output_source_get(काष्ठा snd_kcontrol *kcontrol,
                                 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक channel;

	channel = (kcontrol->निजी_value) & 0xff;
	/* Limit: emu1010_output_dst, emu->emu1010.output_source */
	अगर (channel >= 24 ||
	    (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616 &&
	     channel >= 18))
		वापस -EINVAL;
	ucontrol->value.क्रमागतerated.item[0] = emu->emu1010.output_source[channel];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu1010_output_source_put(काष्ठा snd_kcontrol *kcontrol,
                                 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक channel;

	val = ucontrol->value.क्रमागतerated.item[0];
	अगर (val >= 53 ||
	    (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616 &&
	     val >= 49))
		वापस -EINVAL;
	channel = (kcontrol->निजी_value) & 0xff;
	/* Limit: emu1010_output_dst, emu->emu1010.output_source */
	अगर (channel >= 24 ||
	    (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616 &&
	     channel >= 18))
		वापस -EINVAL;
	अगर (emu->emu1010.output_source[channel] == val)
		वापस 0;
	emu->emu1010.output_source[channel] = val;
	अगर (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616)
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			emu1616_output_dst[channel], emu1616_src_regs[val]);
	अन्यथा
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			emu1010_output_dst[channel], emu1010_src_regs[val]);
	वापस 1;
पूर्ण

अटल पूर्णांक snd_emu1010_input_source_get(काष्ठा snd_kcontrol *kcontrol,
                                 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक channel;

	channel = (kcontrol->निजी_value) & 0xff;
	/* Limit: emu1010_input_dst, emu->emu1010.input_source */
	अगर (channel >= 22)
		वापस -EINVAL;
	ucontrol->value.क्रमागतerated.item[0] = emu->emu1010.input_source[channel];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu1010_input_source_put(काष्ठा snd_kcontrol *kcontrol,
                                 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक channel;

	val = ucontrol->value.क्रमागतerated.item[0];
	अगर (val >= 53 ||
	    (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616 &&
	     val >= 49))
		वापस -EINVAL;
	channel = (kcontrol->निजी_value) & 0xff;
	/* Limit: emu1010_input_dst, emu->emu1010.input_source */
	अगर (channel >= 22)
		वापस -EINVAL;
	अगर (emu->emu1010.input_source[channel] == val)
		वापस 0;
	emu->emu1010.input_source[channel] = val;
	अगर (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616)
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			emu1010_input_dst[channel], emu1616_src_regs[val]);
	अन्यथा
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			emu1010_input_dst[channel], emu1010_src_regs[val]);
	वापस 1;
पूर्ण

#घोषणा EMU1010_SOURCE_OUTPUT(xname,chid) \
अणु								\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,	\
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,		\
	.info =  snd_emu1010_input_output_source_info,		\
	.get =   snd_emu1010_output_source_get,			\
	.put =   snd_emu1010_output_source_put,			\
	.निजी_value = chid					\
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu1010_output_क्रमागत_ctls[] = अणु
	EMU1010_SOURCE_OUTPUT("Dock DAC1 Left Playback Enum", 0),
	EMU1010_SOURCE_OUTPUT("Dock DAC1 Right Playback Enum", 1),
	EMU1010_SOURCE_OUTPUT("Dock DAC2 Left Playback Enum", 2),
	EMU1010_SOURCE_OUTPUT("Dock DAC2 Right Playback Enum", 3),
	EMU1010_SOURCE_OUTPUT("Dock DAC3 Left Playback Enum", 4),
	EMU1010_SOURCE_OUTPUT("Dock DAC3 Right Playback Enum", 5),
	EMU1010_SOURCE_OUTPUT("Dock DAC4 Left Playback Enum", 6),
	EMU1010_SOURCE_OUTPUT("Dock DAC4 Right Playback Enum", 7),
	EMU1010_SOURCE_OUTPUT("Dock Phones Left Playback Enum", 8),
	EMU1010_SOURCE_OUTPUT("Dock Phones Right Playback Enum", 9),
	EMU1010_SOURCE_OUTPUT("Dock SPDIF Left Playback Enum", 0xa),
	EMU1010_SOURCE_OUTPUT("Dock SPDIF Right Playback Enum", 0xb),
	EMU1010_SOURCE_OUTPUT("1010 SPDIF Left Playback Enum", 0xc),
	EMU1010_SOURCE_OUTPUT("1010 SPDIF Right Playback Enum", 0xd),
	EMU1010_SOURCE_OUTPUT("0202 DAC Left Playback Enum", 0xe),
	EMU1010_SOURCE_OUTPUT("0202 DAC Right Playback Enum", 0xf),
	EMU1010_SOURCE_OUTPUT("1010 ADAT 0 Playback Enum", 0x10),
	EMU1010_SOURCE_OUTPUT("1010 ADAT 1 Playback Enum", 0x11),
	EMU1010_SOURCE_OUTPUT("1010 ADAT 2 Playback Enum", 0x12),
	EMU1010_SOURCE_OUTPUT("1010 ADAT 3 Playback Enum", 0x13),
	EMU1010_SOURCE_OUTPUT("1010 ADAT 4 Playback Enum", 0x14),
	EMU1010_SOURCE_OUTPUT("1010 ADAT 5 Playback Enum", 0x15),
	EMU1010_SOURCE_OUTPUT("1010 ADAT 6 Playback Enum", 0x16),
	EMU1010_SOURCE_OUTPUT("1010 ADAT 7 Playback Enum", 0x17),
पूर्ण;


/* 1616(m) cardbus */
अटल स्थिर काष्ठा snd_kcontrol_new snd_emu1616_output_क्रमागत_ctls[] = अणु
	EMU1010_SOURCE_OUTPUT("Dock DAC1 Left Playback Enum", 0),
	EMU1010_SOURCE_OUTPUT("Dock DAC1 Right Playback Enum", 1),
	EMU1010_SOURCE_OUTPUT("Dock DAC2 Left Playback Enum", 2),
	EMU1010_SOURCE_OUTPUT("Dock DAC2 Right Playback Enum", 3),
	EMU1010_SOURCE_OUTPUT("Dock DAC3 Left Playback Enum", 4),
	EMU1010_SOURCE_OUTPUT("Dock DAC3 Right Playback Enum", 5),
	EMU1010_SOURCE_OUTPUT("Dock SPDIF Left Playback Enum", 6),
	EMU1010_SOURCE_OUTPUT("Dock SPDIF Right Playback Enum", 7),
	EMU1010_SOURCE_OUTPUT("Dock ADAT 0 Playback Enum", 8),
	EMU1010_SOURCE_OUTPUT("Dock ADAT 1 Playback Enum", 9),
	EMU1010_SOURCE_OUTPUT("Dock ADAT 2 Playback Enum", 0xa),
	EMU1010_SOURCE_OUTPUT("Dock ADAT 3 Playback Enum", 0xb),
	EMU1010_SOURCE_OUTPUT("Dock ADAT 4 Playback Enum", 0xc),
	EMU1010_SOURCE_OUTPUT("Dock ADAT 5 Playback Enum", 0xd),
	EMU1010_SOURCE_OUTPUT("Dock ADAT 6 Playback Enum", 0xe),
	EMU1010_SOURCE_OUTPUT("Dock ADAT 7 Playback Enum", 0xf),
	EMU1010_SOURCE_OUTPUT("Mana DAC Left Playback Enum", 0x10),
	EMU1010_SOURCE_OUTPUT("Mana DAC Right Playback Enum", 0x11),
पूर्ण;


#घोषणा EMU1010_SOURCE_INPUT(xname,chid) \
अणु								\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,	\
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,		\
	.info =  snd_emu1010_input_output_source_info,		\
	.get =   snd_emu1010_input_source_get,			\
	.put =   snd_emu1010_input_source_put,			\
	.निजी_value = chid					\
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu1010_input_क्रमागत_ctls[] = अणु
	EMU1010_SOURCE_INPUT("DSP 0 Capture Enum", 0),
	EMU1010_SOURCE_INPUT("DSP 1 Capture Enum", 1),
	EMU1010_SOURCE_INPUT("DSP 2 Capture Enum", 2),
	EMU1010_SOURCE_INPUT("DSP 3 Capture Enum", 3),
	EMU1010_SOURCE_INPUT("DSP 4 Capture Enum", 4),
	EMU1010_SOURCE_INPUT("DSP 5 Capture Enum", 5),
	EMU1010_SOURCE_INPUT("DSP 6 Capture Enum", 6),
	EMU1010_SOURCE_INPUT("DSP 7 Capture Enum", 7),
	EMU1010_SOURCE_INPUT("DSP 8 Capture Enum", 8),
	EMU1010_SOURCE_INPUT("DSP 9 Capture Enum", 9),
	EMU1010_SOURCE_INPUT("DSP A Capture Enum", 0xa),
	EMU1010_SOURCE_INPUT("DSP B Capture Enum", 0xb),
	EMU1010_SOURCE_INPUT("DSP C Capture Enum", 0xc),
	EMU1010_SOURCE_INPUT("DSP D Capture Enum", 0xd),
	EMU1010_SOURCE_INPUT("DSP E Capture Enum", 0xe),
	EMU1010_SOURCE_INPUT("DSP F Capture Enum", 0xf),
	EMU1010_SOURCE_INPUT("DSP 10 Capture Enum", 0x10),
	EMU1010_SOURCE_INPUT("DSP 11 Capture Enum", 0x11),
	EMU1010_SOURCE_INPUT("DSP 12 Capture Enum", 0x12),
	EMU1010_SOURCE_INPUT("DSP 13 Capture Enum", 0x13),
	EMU1010_SOURCE_INPUT("DSP 14 Capture Enum", 0x14),
	EMU1010_SOURCE_INPUT("DSP 15 Capture Enum", 0x15),
पूर्ण;



#घोषणा snd_emu1010_adc_pads_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_emu1010_adc_pads_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक mask = kcontrol->निजी_value & 0xff;
	ucontrol->value.पूर्णांकeger.value[0] = (emu->emu1010.adc_pads & mask) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu1010_adc_pads_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक mask = kcontrol->निजी_value & 0xff;
	अचिन्हित पूर्णांक val, cache;
	val = ucontrol->value.पूर्णांकeger.value[0];
	cache = emu->emu1010.adc_pads;
	अगर (val == 1) 
		cache = cache | mask;
	अन्यथा
		cache = cache & ~mask;
	अगर (cache != emu->emu1010.adc_pads) अणु
		snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_ADC_PADS, cache );
	        emu->emu1010.adc_pads = cache;
	पूर्ण

	वापस 0;
पूर्ण



#घोषणा EMU1010_ADC_PADS(xname,chid) \
अणु								\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,	\
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,		\
	.info =  snd_emu1010_adc_pads_info,			\
	.get =   snd_emu1010_adc_pads_get,			\
	.put =   snd_emu1010_adc_pads_put,			\
	.निजी_value = chid					\
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu1010_adc_pads[] = अणु
	EMU1010_ADC_PADS("ADC1 14dB PAD Audio Dock Capture Switch", EMU_HANA_DOCK_ADC_PAD1),
	EMU1010_ADC_PADS("ADC2 14dB PAD Audio Dock Capture Switch", EMU_HANA_DOCK_ADC_PAD2),
	EMU1010_ADC_PADS("ADC3 14dB PAD Audio Dock Capture Switch", EMU_HANA_DOCK_ADC_PAD3),
	EMU1010_ADC_PADS("ADC1 14dB PAD 0202 Capture Switch", EMU_HANA_0202_ADC_PAD1),
पूर्ण;

#घोषणा snd_emu1010_dac_pads_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_emu1010_dac_pads_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक mask = kcontrol->निजी_value & 0xff;
	ucontrol->value.पूर्णांकeger.value[0] = (emu->emu1010.dac_pads & mask) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu1010_dac_pads_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक mask = kcontrol->निजी_value & 0xff;
	अचिन्हित पूर्णांक val, cache;
	val = ucontrol->value.पूर्णांकeger.value[0];
	cache = emu->emu1010.dac_pads;
	अगर (val == 1) 
		cache = cache | mask;
	अन्यथा
		cache = cache & ~mask;
	अगर (cache != emu->emu1010.dac_pads) अणु
		snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DAC_PADS, cache );
	        emu->emu1010.dac_pads = cache;
	पूर्ण

	वापस 0;
पूर्ण



#घोषणा EMU1010_DAC_PADS(xname,chid) \
अणु								\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,	\
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,		\
	.info =  snd_emu1010_dac_pads_info,			\
	.get =   snd_emu1010_dac_pads_get,			\
	.put =   snd_emu1010_dac_pads_put,			\
	.निजी_value = chid					\
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu1010_dac_pads[] = अणु
	EMU1010_DAC_PADS("DAC1 Audio Dock 14dB PAD Playback Switch", EMU_HANA_DOCK_DAC_PAD1),
	EMU1010_DAC_PADS("DAC2 Audio Dock 14dB PAD Playback Switch", EMU_HANA_DOCK_DAC_PAD2),
	EMU1010_DAC_PADS("DAC3 Audio Dock 14dB PAD Playback Switch", EMU_HANA_DOCK_DAC_PAD3),
	EMU1010_DAC_PADS("DAC4 Audio Dock 14dB PAD Playback Switch", EMU_HANA_DOCK_DAC_PAD4),
	EMU1010_DAC_PADS("DAC1 0202 14dB PAD Playback Switch", EMU_HANA_0202_DAC_PAD1),
पूर्ण;


अटल पूर्णांक snd_emu1010_पूर्णांकernal_घड़ी_info(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु
		"44100", "48000", "SPDIF", "ADAT"
	पूर्ण;
		
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 4, texts);
पूर्ण

अटल पूर्णांक snd_emu1010_पूर्णांकernal_घड़ी_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = emu->emu1010.पूर्णांकernal_घड़ी;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu1010_पूर्णांकernal_घड़ी_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change = 0;

	val = ucontrol->value.क्रमागतerated.item[0] ;
	/* Limit: uinfo->value.क्रमागतerated.items = 4; */
	अगर (val >= 4)
		वापस -EINVAL;
	change = (emu->emu1010.पूर्णांकernal_घड़ी != val);
	अगर (change) अणु
		emu->emu1010.पूर्णांकernal_घड़ी = val;
		चयन (val) अणु
		हाल 0:
			/* 44100 */
			/* Mute all */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_UNMUTE, EMU_MUTE );
			/* Default fallback घड़ी 48kHz */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DEFCLOCK, EMU_HANA_DEFCLOCK_44_1K );
			/* Word Clock source, Internal 44.1kHz x1 */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_WCLOCK,
			EMU_HANA_WCLOCK_INT_44_1K | EMU_HANA_WCLOCK_1X );
			/* Set LEDs on Audio Dock */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DOCK_LEDS_2,
				EMU_HANA_DOCK_LEDS_2_44K | EMU_HANA_DOCK_LEDS_2_LOCK );
			/* Allow DLL to settle */
			msleep(10);
			/* Unmute all */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_UNMUTE, EMU_UNMUTE );
			अवरोध;
		हाल 1:
			/* 48000 */
			/* Mute all */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_UNMUTE, EMU_MUTE );
			/* Default fallback घड़ी 48kHz */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DEFCLOCK, EMU_HANA_DEFCLOCK_48K );
			/* Word Clock source, Internal 48kHz x1 */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_WCLOCK,
				EMU_HANA_WCLOCK_INT_48K | EMU_HANA_WCLOCK_1X );
			/* Set LEDs on Audio Dock */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DOCK_LEDS_2,
				EMU_HANA_DOCK_LEDS_2_48K | EMU_HANA_DOCK_LEDS_2_LOCK );
			/* Allow DLL to settle */
			msleep(10);
			/* Unmute all */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_UNMUTE, EMU_UNMUTE );
			अवरोध;
			
		हाल 2: /* Take घड़ी from S/PDIF IN */
			/* Mute all */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_UNMUTE, EMU_MUTE );
			/* Default fallback घड़ी 48kHz */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DEFCLOCK, EMU_HANA_DEFCLOCK_48K );
			/* Word Clock source, sync to S/PDIF input */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_WCLOCK,
				EMU_HANA_WCLOCK_HANA_SPDIF_IN | EMU_HANA_WCLOCK_1X );
			/* Set LEDs on Audio Dock */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DOCK_LEDS_2,
				EMU_HANA_DOCK_LEDS_2_EXT | EMU_HANA_DOCK_LEDS_2_LOCK );
			/* FIXME: We should set EMU_HANA_DOCK_LEDS_2_LOCK only when घड़ी संकेत is present and valid */	
			/* Allow DLL to settle */
			msleep(10);
			/* Unmute all */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_UNMUTE, EMU_UNMUTE );
			अवरोध;
		
		हाल 3: 			
			/* Take घड़ी from ADAT IN */
			/* Mute all */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_UNMUTE, EMU_MUTE );
			/* Default fallback घड़ी 48kHz */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DEFCLOCK, EMU_HANA_DEFCLOCK_48K );
			/* Word Clock source, sync to ADAT input */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_WCLOCK,
				EMU_HANA_WCLOCK_HANA_ADAT_IN | EMU_HANA_WCLOCK_1X );
			/* Set LEDs on Audio Dock */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DOCK_LEDS_2, EMU_HANA_DOCK_LEDS_2_EXT | EMU_HANA_DOCK_LEDS_2_LOCK );
			/* FIXME: We should set EMU_HANA_DOCK_LEDS_2_LOCK only when घड़ी संकेत is present and valid */	
			/* Allow DLL to settle */
			msleep(10);
			/*   Unmute all */
			snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_UNMUTE, EMU_UNMUTE );
			 
			
			अवरोध;		
		पूर्ण
	पूर्ण
        वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu1010_पूर्णांकernal_घड़ी =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Clock Internal Rate",
	.count =	1,
	.info =         snd_emu1010_पूर्णांकernal_घड़ी_info,
	.get =          snd_emu1010_पूर्णांकernal_घड़ी_get,
	.put =          snd_emu1010_पूर्णांकernal_घड़ी_put
पूर्ण;

अटल पूर्णांक snd_emu1010_optical_out_info(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु
		"SPDIF", "ADAT"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक snd_emu1010_optical_out_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = emu->emu1010.optical_out;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu1010_optical_out_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	u32 पंचांगp;
	पूर्णांक change = 0;

	val = ucontrol->value.क्रमागतerated.item[0];
	/* Limit: uinfo->value.क्रमागतerated.items = 2; */
	अगर (val >= 2)
		वापस -EINVAL;
	change = (emu->emu1010.optical_out != val);
	अगर (change) अणु
		emu->emu1010.optical_out = val;
		पंचांगp = (emu->emu1010.optical_in ? EMU_HANA_OPTICAL_IN_ADAT : 0) |
			(emu->emu1010.optical_out ? EMU_HANA_OPTICAL_OUT_ADAT : 0);
		snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_OPTICAL_TYPE, पंचांगp);
	पूर्ण
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu1010_optical_out = अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Optical Output Mode",
	.count =	1,
	.info =         snd_emu1010_optical_out_info,
	.get =          snd_emu1010_optical_out_get,
	.put =          snd_emu1010_optical_out_put
पूर्ण;

अटल पूर्णांक snd_emu1010_optical_in_info(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु
		"SPDIF", "ADAT"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक snd_emu1010_optical_in_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = emu->emu1010.optical_in;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu1010_optical_in_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	u32 पंचांगp;
	पूर्णांक change = 0;

	val = ucontrol->value.क्रमागतerated.item[0];
	/* Limit: uinfo->value.क्रमागतerated.items = 2; */
	अगर (val >= 2)
		वापस -EINVAL;
	change = (emu->emu1010.optical_in != val);
	अगर (change) अणु
		emu->emu1010.optical_in = val;
		पंचांगp = (emu->emu1010.optical_in ? EMU_HANA_OPTICAL_IN_ADAT : 0) |
			(emu->emu1010.optical_out ? EMU_HANA_OPTICAL_OUT_ADAT : 0);
		snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_OPTICAL_TYPE, पंचांगp);
	पूर्ण
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu1010_optical_in = अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Optical Input Mode",
	.count =	1,
	.info =         snd_emu1010_optical_in_info,
	.get =          snd_emu1010_optical_in_get,
	.put =          snd_emu1010_optical_in_put
पूर्ण;

अटल पूर्णांक snd_audigy_i2c_capture_source_info(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
#अगर 0
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु
		"Unknown1", "Unknown2", "Mic", "Line"
	पूर्ण;
#पूर्ण_अगर
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु
		"Mic", "Line"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक snd_audigy_i2c_capture_source_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = emu->i2c_capture_source;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_audigy_i2c_capture_source_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक source_id;
	अचिन्हित पूर्णांक ngain, ogain;
	u32 gpio;
	पूर्णांक change = 0;
	अचिन्हित दीर्घ flags;
	u32 source;
	/* If the capture source has changed,
	 * update the capture volume from the cached value
	 * क्रम the particular source.
	 */
	source_id = ucontrol->value.क्रमागतerated.item[0];
	/* Limit: uinfo->value.क्रमागतerated.items = 2; */
	/*        emu->i2c_capture_volume */
	अगर (source_id >= 2)
		वापस -EINVAL;
	change = (emu->i2c_capture_source != source_id);
	अगर (change) अणु
		snd_emu10k1_i2c_ग_लिखो(emu, ADC_MUX, 0); /* Mute input */
		spin_lock_irqsave(&emu->emu_lock, flags);
		gpio = inl(emu->port + A_IOCFG);
		अगर (source_id==0)
			outl(gpio | 0x4, emu->port + A_IOCFG);
		अन्यथा
			outl(gpio & ~0x4, emu->port + A_IOCFG);
		spin_unlock_irqrestore(&emu->emu_lock, flags);

		ngain = emu->i2c_capture_volume[source_id][0]; /* Left */
		ogain = emu->i2c_capture_volume[emu->i2c_capture_source][0]; /* Left */
		अगर (ngain != ogain)
			snd_emu10k1_i2c_ग_लिखो(emu, ADC_ATTEN_ADCL, ((ngain) & 0xff));
		ngain = emu->i2c_capture_volume[source_id][1]; /* Right */
		ogain = emu->i2c_capture_volume[emu->i2c_capture_source][1]; /* Right */
		अगर (ngain != ogain)
			snd_emu10k1_i2c_ग_लिखो(emu, ADC_ATTEN_ADCR, ((ngain) & 0xff));

		source = 1 << (source_id + 2);
		snd_emu10k1_i2c_ग_लिखो(emu, ADC_MUX, source); /* Set source */
		emu->i2c_capture_source = source_id;
	पूर्ण
        वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_audigy_i2c_capture_source =
अणु
		.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
		.name =		"Capture Source",
		.info =		snd_audigy_i2c_capture_source_info,
		.get =		snd_audigy_i2c_capture_source_get,
		.put =		snd_audigy_i2c_capture_source_put
पूर्ण;

अटल पूर्णांक snd_audigy_i2c_volume_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 255;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_audigy_i2c_volume_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक source_id;

	source_id = kcontrol->निजी_value;
	/* Limit: emu->i2c_capture_volume */
        /*        capture_source: uinfo->value.क्रमागतerated.items = 2 */
	अगर (source_id >= 2)
		वापस -EINVAL;

	ucontrol->value.पूर्णांकeger.value[0] = emu->i2c_capture_volume[source_id][0];
	ucontrol->value.पूर्णांकeger.value[1] = emu->i2c_capture_volume[source_id][1];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_audigy_i2c_volume_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक ogain;
	अचिन्हित पूर्णांक ngain;
	अचिन्हित पूर्णांक source_id;
	पूर्णांक change = 0;

	source_id = kcontrol->निजी_value;
	/* Limit: emu->i2c_capture_volume */
        /*        capture_source: uinfo->value.क्रमागतerated.items = 2 */
	अगर (source_id >= 2)
		वापस -EINVAL;
	ogain = emu->i2c_capture_volume[source_id][0]; /* Left */
	ngain = ucontrol->value.पूर्णांकeger.value[0];
	अगर (ngain > 0xff)
		वापस 0;
	अगर (ogain != ngain) अणु
		अगर (emu->i2c_capture_source == source_id)
			snd_emu10k1_i2c_ग_लिखो(emu, ADC_ATTEN_ADCL, ((ngain) & 0xff) );
		emu->i2c_capture_volume[source_id][0] = ngain;
		change = 1;
	पूर्ण
	ogain = emu->i2c_capture_volume[source_id][1]; /* Right */
	ngain = ucontrol->value.पूर्णांकeger.value[1];
	अगर (ngain > 0xff)
		वापस 0;
	अगर (ogain != ngain) अणु
		अगर (emu->i2c_capture_source == source_id)
			snd_emu10k1_i2c_ग_लिखो(emu, ADC_ATTEN_ADCR, ((ngain) & 0xff));
		emu->i2c_capture_volume[source_id][1] = ngain;
		change = 1;
	पूर्ण

	वापस change;
पूर्ण

#घोषणा I2C_VOLUME(xname,chid) \
अणु								\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,	\
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |		\
	          SNDRV_CTL_ELEM_ACCESS_TLV_READ,		\
	.info =  snd_audigy_i2c_volume_info,			\
	.get =   snd_audigy_i2c_volume_get,			\
	.put =   snd_audigy_i2c_volume_put,			\
	.tlv = अणु .p = snd_audigy_db_scale2 पूर्ण,			\
	.निजी_value = chid					\
पूर्ण


अटल स्थिर काष्ठा snd_kcontrol_new snd_audigy_i2c_volume_ctls[] = अणु
	I2C_VOLUME("Mic Capture Volume", 0),
	I2C_VOLUME("Line Capture Volume", 0)
पूर्ण;

#अगर 0
अटल पूर्णांक snd_audigy_spdअगर_output_rate_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु"44100", "48000", "96000"पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक snd_audigy_spdअगर_output_rate_get(काष्ठा snd_kcontrol *kcontrol,
                                 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित दीर्घ flags;
	

	spin_lock_irqsave(&emu->reg_lock, flags);
	पंचांगp = snd_emu10k1_ptr_पढ़ो(emu, A_SPDIF_SAMPLERATE, 0);
	चयन (पंचांगp & A_SPDIF_RATE_MASK) अणु
	हाल A_SPDIF_44100:
		ucontrol->value.क्रमागतerated.item[0] = 0;
		अवरोध;
	हाल A_SPDIF_48000:
		ucontrol->value.क्रमागतerated.item[0] = 1;
		अवरोध;
	हाल A_SPDIF_96000:
		ucontrol->value.क्रमागतerated.item[0] = 2;
		अवरोध;
	शेष:
		ucontrol->value.क्रमागतerated.item[0] = 1;
	पूर्ण
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_audigy_spdअगर_output_rate_put(काष्ठा snd_kcontrol *kcontrol,
                                 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	अचिन्हित पूर्णांक reg, val, पंचांगp;
	अचिन्हित दीर्घ flags;

	चयन(ucontrol->value.क्रमागतerated.item[0]) अणु
	हाल 0:
		val = A_SPDIF_44100;
		अवरोध;
	हाल 1:
		val = A_SPDIF_48000;
		अवरोध;
	हाल 2:
		val = A_SPDIF_96000;
		अवरोध;
	शेष:
		val = A_SPDIF_48000;
		अवरोध;
	पूर्ण

	
	spin_lock_irqsave(&emu->reg_lock, flags);
	reg = snd_emu10k1_ptr_पढ़ो(emu, A_SPDIF_SAMPLERATE, 0);
	पंचांगp = reg & ~A_SPDIF_RATE_MASK;
	पंचांगp |= val;
	अगर ((change = (पंचांगp != reg)))
		snd_emu10k1_ptr_ग_लिखो(emu, A_SPDIF_SAMPLERATE, 0, पंचांगp);
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_audigy_spdअगर_output_rate =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Audigy SPDIF Output Sample Rate",
	.count =	1,
	.info =         snd_audigy_spdअगर_output_rate_info,
	.get =          snd_audigy_spdअगर_output_rate_get,
	.put =          snd_audigy_spdअगर_output_rate_put
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक snd_emu10k1_spdअगर_put(काष्ठा snd_kcontrol *kcontrol,
                                 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	पूर्णांक change;
	अचिन्हित पूर्णांक val;
	अचिन्हित दीर्घ flags;

	/* Limit: emu->spdअगर_bits */
	अगर (idx >= 3)
		वापस -EINVAL;
	val = (ucontrol->value.iec958.status[0] << 0) |
	      (ucontrol->value.iec958.status[1] << 8) |
	      (ucontrol->value.iec958.status[2] << 16) |
	      (ucontrol->value.iec958.status[3] << 24);
	spin_lock_irqsave(&emu->reg_lock, flags);
	change = val != emu->spdअगर_bits[idx];
	अगर (change) अणु
		snd_emu10k1_ptr_ग_लिखो(emu, SPCS0 + idx, 0, val);
		emu->spdअगर_bits[idx] = val;
	पूर्ण
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu10k1_spdअगर_mask_control =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,MASK),
	.count =	3,
	.info =         snd_emu10k1_spdअगर_info,
	.get =          snd_emu10k1_spdअगर_get_mask
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu10k1_spdअगर_control =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
	.count =	3,
	.info =         snd_emu10k1_spdअगर_info,
	.get =          snd_emu10k1_spdअगर_get,
	.put =          snd_emu10k1_spdअगर_put
पूर्ण;


अटल व्योम update_emu10k1_fxrt(काष्ठा snd_emu10k1 *emu, पूर्णांक voice, अचिन्हित अक्षर *route)
अणु
	अगर (emu->audigy) अणु
		snd_emu10k1_ptr_ग_लिखो(emu, A_FXRT1, voice,
				      snd_emu10k1_compose_audigy_fxrt1(route));
		snd_emu10k1_ptr_ग_लिखो(emu, A_FXRT2, voice,
				      snd_emu10k1_compose_audigy_fxrt2(route));
	पूर्ण अन्यथा अणु
		snd_emu10k1_ptr_ग_लिखो(emu, FXRT, voice,
				      snd_emu10k1_compose_send_routing(route));
	पूर्ण
पूर्ण

अटल व्योम update_emu10k1_send_volume(काष्ठा snd_emu10k1 *emu, पूर्णांक voice, अचिन्हित अक्षर *volume)
अणु
	snd_emu10k1_ptr_ग_लिखो(emu, PTRX_FXSENDAMOUNT_A, voice, volume[0]);
	snd_emu10k1_ptr_ग_लिखो(emu, PTRX_FXSENDAMOUNT_B, voice, volume[1]);
	snd_emu10k1_ptr_ग_लिखो(emu, PSST_FXSENDAMOUNT_C, voice, volume[2]);
	snd_emu10k1_ptr_ग_लिखो(emu, DSL_FXSENDAMOUNT_D, voice, volume[3]);
	अगर (emu->audigy) अणु
		अचिन्हित पूर्णांक val = ((अचिन्हित पूर्णांक)volume[4] << 24) |
			((अचिन्हित पूर्णांक)volume[5] << 16) |
			((अचिन्हित पूर्णांक)volume[6] << 8) |
			(अचिन्हित पूर्णांक)volume[7];
		snd_emu10k1_ptr_ग_लिखो(emu, A_SENDAMOUNTS, voice, val);
	पूर्ण
पूर्ण

/* PCM stream controls */

अटल पूर्णांक snd_emu10k1_send_routing_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = emu->audigy ? 3*8 : 3*4;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = emu->audigy ? 0x3f : 0x0f;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_send_routing_get(काष्ठा snd_kcontrol *kcontrol,
                                        काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_emu10k1_pcm_mixer *mix =
		&emu->pcm_mixer[snd_ctl_get_ioffidx(kcontrol, &ucontrol->id)];
	पूर्णांक voice, idx;
	पूर्णांक num_efx = emu->audigy ? 8 : 4;
	पूर्णांक mask = emu->audigy ? 0x3f : 0x0f;

	spin_lock_irqsave(&emu->reg_lock, flags);
	क्रम (voice = 0; voice < 3; voice++)
		क्रम (idx = 0; idx < num_efx; idx++)
			ucontrol->value.पूर्णांकeger.value[(voice * num_efx) + idx] = 
				mix->send_routing[voice][idx] & mask;
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_send_routing_put(काष्ठा snd_kcontrol *kcontrol,
                                        काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_emu10k1_pcm_mixer *mix =
		&emu->pcm_mixer[snd_ctl_get_ioffidx(kcontrol, &ucontrol->id)];
	पूर्णांक change = 0, voice, idx, val;
	पूर्णांक num_efx = emu->audigy ? 8 : 4;
	पूर्णांक mask = emu->audigy ? 0x3f : 0x0f;

	spin_lock_irqsave(&emu->reg_lock, flags);
	क्रम (voice = 0; voice < 3; voice++)
		क्रम (idx = 0; idx < num_efx; idx++) अणु
			val = ucontrol->value.पूर्णांकeger.value[(voice * num_efx) + idx] & mask;
			अगर (mix->send_routing[voice][idx] != val) अणु
				mix->send_routing[voice][idx] = val;
				change = 1;
			पूर्ण
		पूर्ण	
	अगर (change && mix->epcm) अणु
		अगर (mix->epcm->voices[0] && mix->epcm->voices[1]) अणु
			update_emu10k1_fxrt(emu, mix->epcm->voices[0]->number,
					    &mix->send_routing[1][0]);
			update_emu10k1_fxrt(emu, mix->epcm->voices[1]->number,
					    &mix->send_routing[2][0]);
		पूर्ण अन्यथा अगर (mix->epcm->voices[0]) अणु
			update_emu10k1_fxrt(emu, mix->epcm->voices[0]->number,
					    &mix->send_routing[0][0]);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu10k1_send_routing_control =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         "EMU10K1 PCM Send Routing",
	.count =	32,
	.info =         snd_emu10k1_send_routing_info,
	.get =          snd_emu10k1_send_routing_get,
	.put =          snd_emu10k1_send_routing_put
पूर्ण;

अटल पूर्णांक snd_emu10k1_send_volume_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = emu->audigy ? 3*8 : 3*4;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 255;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_send_volume_get(काष्ठा snd_kcontrol *kcontrol,
                                       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_emu10k1_pcm_mixer *mix =
		&emu->pcm_mixer[snd_ctl_get_ioffidx(kcontrol, &ucontrol->id)];
	पूर्णांक idx;
	पूर्णांक num_efx = emu->audigy ? 8 : 4;

	spin_lock_irqsave(&emu->reg_lock, flags);
	क्रम (idx = 0; idx < 3*num_efx; idx++)
		ucontrol->value.पूर्णांकeger.value[idx] = mix->send_volume[idx/num_efx][idx%num_efx];
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_send_volume_put(काष्ठा snd_kcontrol *kcontrol,
                                       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_emu10k1_pcm_mixer *mix =
		&emu->pcm_mixer[snd_ctl_get_ioffidx(kcontrol, &ucontrol->id)];
	पूर्णांक change = 0, idx, val;
	पूर्णांक num_efx = emu->audigy ? 8 : 4;

	spin_lock_irqsave(&emu->reg_lock, flags);
	क्रम (idx = 0; idx < 3*num_efx; idx++) अणु
		val = ucontrol->value.पूर्णांकeger.value[idx] & 255;
		अगर (mix->send_volume[idx/num_efx][idx%num_efx] != val) अणु
			mix->send_volume[idx/num_efx][idx%num_efx] = val;
			change = 1;
		पूर्ण
	पूर्ण
	अगर (change && mix->epcm) अणु
		अगर (mix->epcm->voices[0] && mix->epcm->voices[1]) अणु
			update_emu10k1_send_volume(emu, mix->epcm->voices[0]->number,
						   &mix->send_volume[1][0]);
			update_emu10k1_send_volume(emu, mix->epcm->voices[1]->number,
						   &mix->send_volume[2][0]);
		पूर्ण अन्यथा अगर (mix->epcm->voices[0]) अणु
			update_emu10k1_send_volume(emu, mix->epcm->voices[0]->number,
						   &mix->send_volume[0][0]);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu10k1_send_volume_control =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         "EMU10K1 PCM Send Volume",
	.count =	32,
	.info =         snd_emu10k1_send_volume_info,
	.get =          snd_emu10k1_send_volume_get,
	.put =          snd_emu10k1_send_volume_put
पूर्ण;

अटल पूर्णांक snd_emu10k1_attn_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 3;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 0xffff;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_attn_get(काष्ठा snd_kcontrol *kcontrol,
                                काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_emu10k1_pcm_mixer *mix =
		&emu->pcm_mixer[snd_ctl_get_ioffidx(kcontrol, &ucontrol->id)];
	अचिन्हित दीर्घ flags;
	पूर्णांक idx;

	spin_lock_irqsave(&emu->reg_lock, flags);
	क्रम (idx = 0; idx < 3; idx++)
		ucontrol->value.पूर्णांकeger.value[idx] = mix->attn[idx];
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_attn_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_emu10k1_pcm_mixer *mix =
		&emu->pcm_mixer[snd_ctl_get_ioffidx(kcontrol, &ucontrol->id)];
	पूर्णांक change = 0, idx, val;

	spin_lock_irqsave(&emu->reg_lock, flags);
	क्रम (idx = 0; idx < 3; idx++) अणु
		val = ucontrol->value.पूर्णांकeger.value[idx] & 0xffff;
		अगर (mix->attn[idx] != val) अणु
			mix->attn[idx] = val;
			change = 1;
		पूर्ण
	पूर्ण
	अगर (change && mix->epcm) अणु
		अगर (mix->epcm->voices[0] && mix->epcm->voices[1]) अणु
			snd_emu10k1_ptr_ग_लिखो(emu, VTFT_VOLUMETARGET, mix->epcm->voices[0]->number, mix->attn[1]);
			snd_emu10k1_ptr_ग_लिखो(emu, VTFT_VOLUMETARGET, mix->epcm->voices[1]->number, mix->attn[2]);
		पूर्ण अन्यथा अगर (mix->epcm->voices[0]) अणु
			snd_emu10k1_ptr_ग_लिखो(emu, VTFT_VOLUMETARGET, mix->epcm->voices[0]->number, mix->attn[0]);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu10k1_attn_control =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         "EMU10K1 PCM Volume",
	.count =	32,
	.info =         snd_emu10k1_attn_info,
	.get =          snd_emu10k1_attn_get,
	.put =          snd_emu10k1_attn_put
पूर्ण;

/* Mutichannel PCM stream controls */

अटल पूर्णांक snd_emu10k1_efx_send_routing_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = emu->audigy ? 8 : 4;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = emu->audigy ? 0x3f : 0x0f;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_efx_send_routing_get(काष्ठा snd_kcontrol *kcontrol,
                                        काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_emu10k1_pcm_mixer *mix =
		&emu->efx_pcm_mixer[snd_ctl_get_ioffidx(kcontrol, &ucontrol->id)];
	पूर्णांक idx;
	पूर्णांक num_efx = emu->audigy ? 8 : 4;
	पूर्णांक mask = emu->audigy ? 0x3f : 0x0f;

	spin_lock_irqsave(&emu->reg_lock, flags);
	क्रम (idx = 0; idx < num_efx; idx++)
		ucontrol->value.पूर्णांकeger.value[idx] = 
			mix->send_routing[0][idx] & mask;
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_efx_send_routing_put(काष्ठा snd_kcontrol *kcontrol,
                                        काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	पूर्णांक ch = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	काष्ठा snd_emu10k1_pcm_mixer *mix = &emu->efx_pcm_mixer[ch];
	पूर्णांक change = 0, idx, val;
	पूर्णांक num_efx = emu->audigy ? 8 : 4;
	पूर्णांक mask = emu->audigy ? 0x3f : 0x0f;

	spin_lock_irqsave(&emu->reg_lock, flags);
	क्रम (idx = 0; idx < num_efx; idx++) अणु
		val = ucontrol->value.पूर्णांकeger.value[idx] & mask;
		अगर (mix->send_routing[0][idx] != val) अणु
			mix->send_routing[0][idx] = val;
			change = 1;
		पूर्ण
	पूर्ण	

	अगर (change && mix->epcm) अणु
		अगर (mix->epcm->voices[ch]) अणु
			update_emu10k1_fxrt(emu, mix->epcm->voices[ch]->number,
					&mix->send_routing[0][0]);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu10k1_efx_send_routing_control =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         "Multichannel PCM Send Routing",
	.count =	16,
	.info =         snd_emu10k1_efx_send_routing_info,
	.get =          snd_emu10k1_efx_send_routing_get,
	.put =          snd_emu10k1_efx_send_routing_put
पूर्ण;

अटल पूर्णांक snd_emu10k1_efx_send_volume_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = emu->audigy ? 8 : 4;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 255;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_efx_send_volume_get(काष्ठा snd_kcontrol *kcontrol,
                                       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_emu10k1_pcm_mixer *mix =
		&emu->efx_pcm_mixer[snd_ctl_get_ioffidx(kcontrol, &ucontrol->id)];
	पूर्णांक idx;
	पूर्णांक num_efx = emu->audigy ? 8 : 4;

	spin_lock_irqsave(&emu->reg_lock, flags);
	क्रम (idx = 0; idx < num_efx; idx++)
		ucontrol->value.पूर्णांकeger.value[idx] = mix->send_volume[0][idx];
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_efx_send_volume_put(काष्ठा snd_kcontrol *kcontrol,
                                       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	पूर्णांक ch = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	काष्ठा snd_emu10k1_pcm_mixer *mix = &emu->efx_pcm_mixer[ch];
	पूर्णांक change = 0, idx, val;
	पूर्णांक num_efx = emu->audigy ? 8 : 4;

	spin_lock_irqsave(&emu->reg_lock, flags);
	क्रम (idx = 0; idx < num_efx; idx++) अणु
		val = ucontrol->value.पूर्णांकeger.value[idx] & 255;
		अगर (mix->send_volume[0][idx] != val) अणु
			mix->send_volume[0][idx] = val;
			change = 1;
		पूर्ण
	पूर्ण
	अगर (change && mix->epcm) अणु
		अगर (mix->epcm->voices[ch]) अणु
			update_emu10k1_send_volume(emu, mix->epcm->voices[ch]->number,
						   &mix->send_volume[0][0]);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस change;
पूर्ण


अटल स्थिर काष्ठा snd_kcontrol_new snd_emu10k1_efx_send_volume_control =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         "Multichannel PCM Send Volume",
	.count =	16,
	.info =         snd_emu10k1_efx_send_volume_info,
	.get =          snd_emu10k1_efx_send_volume_get,
	.put =          snd_emu10k1_efx_send_volume_put
पूर्ण;

अटल पूर्णांक snd_emu10k1_efx_attn_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 0xffff;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_efx_attn_get(काष्ठा snd_kcontrol *kcontrol,
                                काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_emu10k1_pcm_mixer *mix =
		&emu->efx_pcm_mixer[snd_ctl_get_ioffidx(kcontrol, &ucontrol->id)];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&emu->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = mix->attn[0];
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_efx_attn_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	पूर्णांक ch = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	काष्ठा snd_emu10k1_pcm_mixer *mix = &emu->efx_pcm_mixer[ch];
	पूर्णांक change = 0, val;

	spin_lock_irqsave(&emu->reg_lock, flags);
	val = ucontrol->value.पूर्णांकeger.value[0] & 0xffff;
	अगर (mix->attn[0] != val) अणु
		mix->attn[0] = val;
		change = 1;
	पूर्ण
	अगर (change && mix->epcm) अणु
		अगर (mix->epcm->voices[ch]) अणु
			snd_emu10k1_ptr_ग_लिखो(emu, VTFT_VOLUMETARGET, mix->epcm->voices[ch]->number, mix->attn[0]);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu10k1_efx_attn_control =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         "Multichannel PCM Volume",
	.count =	16,
	.info =         snd_emu10k1_efx_attn_info,
	.get =          snd_emu10k1_efx_attn_get,
	.put =          snd_emu10k1_efx_attn_put
पूर्ण;

#घोषणा snd_emu10k1_shared_spdअगर_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_emu10k1_shared_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);

	अगर (emu->audigy)
		ucontrol->value.पूर्णांकeger.value[0] = inl(emu->port + A_IOCFG) & A_IOCFG_GPOUT0 ? 1 : 0;
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[0] = inl(emu->port + HCFG) & HCFG_GPOUT0 ? 1 : 0;
	अगर (emu->card_capabilities->invert_shared_spdअगर)
		ucontrol->value.पूर्णांकeger.value[0] =
			!ucontrol->value.पूर्णांकeger.value[0];
		
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_shared_spdअगर_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक reg, val, sw;
	पूर्णांक change = 0;

	sw = ucontrol->value.पूर्णांकeger.value[0];
	अगर (emu->card_capabilities->invert_shared_spdअगर)
		sw = !sw;
	spin_lock_irqsave(&emu->reg_lock, flags);
	अगर ( emu->card_capabilities->i2c_adc) अणु
		/* Do nothing क्रम Audigy 2 ZS Notebook */
	पूर्ण अन्यथा अगर (emu->audigy) अणु
		reg = inl(emu->port + A_IOCFG);
		val = sw ? A_IOCFG_GPOUT0 : 0;
		change = (reg & A_IOCFG_GPOUT0) != val;
		अगर (change) अणु
			reg &= ~A_IOCFG_GPOUT0;
			reg |= val;
			outl(reg | val, emu->port + A_IOCFG);
		पूर्ण
	पूर्ण
	reg = inl(emu->port + HCFG);
	val = sw ? HCFG_GPOUT0 : 0;
	change |= (reg & HCFG_GPOUT0) != val;
	अगर (change) अणु
		reg &= ~HCFG_GPOUT0;
		reg |= val;
		outl(reg | val, emu->port + HCFG);
	पूर्ण
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_emu10k1_shared_spdअगर =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"SB Live Analog/Digital Output Jack",
	.info =		snd_emu10k1_shared_spdअगर_info,
	.get =		snd_emu10k1_shared_spdअगर_get,
	.put =		snd_emu10k1_shared_spdअगर_put
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_audigy_shared_spdअगर =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"Audigy Analog/Digital Output Jack",
	.info =		snd_emu10k1_shared_spdअगर_info,
	.get =		snd_emu10k1_shared_spdअगर_get,
	.put =		snd_emu10k1_shared_spdअगर_put
पूर्ण;

/* workaround क्रम too low volume on Audigy due to 16bit/24bit conversion */

#घोषणा snd_audigy_capture_boost_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_audigy_capture_boost_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;

	/* FIXME: better to use a cached version */
	val = snd_ac97_पढ़ो(emu->ac97, AC97_REC_GAIN);
	ucontrol->value.पूर्णांकeger.value[0] = !!val;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_audigy_capture_boost_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;

	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val = 0x0f0f;
	अन्यथा
		val = 0;
	वापस snd_ac97_update(emu->ac97, AC97_REC_GAIN, val);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_audigy_capture_boost =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"Mic Extra Boost",
	.info =		snd_audigy_capture_boost_info,
	.get =		snd_audigy_capture_boost_get,
	.put =		snd_audigy_capture_boost_put
पूर्ण;


/*
 */
अटल व्योम snd_emu10k1_mixer_मुक्त_ac97(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा snd_emu10k1 *emu = ac97->निजी_data;
	emu->ac97 = शून्य;
पूर्ण

/*
 */
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

पूर्णांक snd_emu10k1_mixer(काष्ठा snd_emu10k1 *emu,
		      पूर्णांक pcm_device, पूर्णांक multi_device)
अणु
	पूर्णांक err, pcm;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_card *card = emu->card;
	स्थिर अक्षर * स्थिर *c;
	अटल स्थिर अक्षर * स्थिर emu10k1_हटाओ_ctls[] = अणु
		/* no AC97 mono, surround, center/lfe */
		"Master Mono Playback Switch",
		"Master Mono Playback Volume",
		"PCM Out Path & Mute",
		"Mono Output Select",
		"Surround Playback Switch",
		"Surround Playback Volume",
		"Center Playback Switch",
		"Center Playback Volume",
		"LFE Playback Switch",
		"LFE Playback Volume",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर emu10k1_नाम_ctls[] = अणु
		"Surround Digital Playback Volume", "Surround Playback Volume",
		"Center Digital Playback Volume", "Center Playback Volume",
		"LFE Digital Playback Volume", "LFE Playback Volume",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर audigy_हटाओ_ctls[] = अणु
		/* Master/PCM controls on ac97 of Audigy has no effect */
		/* On the Audigy2 the AC97 playback is piped पूर्णांकo
		 * the Philips ADC क्रम 24bit capture */
		"PCM Playback Switch",
		"PCM Playback Volume",
		"Master Playback Switch",
		"Master Playback Volume",
		"PCM Out Path & Mute",
		"Mono Output Select",
		/* हटाओ unused AC97 capture controls */
		"Capture Source",
		"Capture Switch",
		"Capture Volume",
		"Mic Select",
		"Headphone Playback Switch",
		"Headphone Playback Volume",
		"3D Control - Center",
		"3D Control - Depth",
		"3D Control - Switch",
		"Video Playback Switch",
		"Video Playback Volume",
		"Mic Playback Switch",
		"Mic Playback Volume",
		"External Amplifier",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर audigy_नाम_ctls[] = अणु
		/* use conventional names */
		"Wave Playback Volume", "PCM Playback Volume",
		/* "Wave Capture Volume", "PCM Capture Volume", */
		"Wave Master Playback Volume", "Master Playback Volume",
		"AMic Playback Volume", "Mic Playback Volume",
		"Master Mono Playback Switch", "Phone Output Playback Switch",
		"Master Mono Playback Volume", "Phone Output Playback Volume",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर audigy_नाम_ctls_i2c_adc[] = अणु
		//"Analog Mix Capture Volume","OLD Analog Mix Capture Volume",
		"Line Capture Volume", "Analog Mix Capture Volume",
		"Wave Playback Volume", "OLD PCM Playback Volume",
		"Wave Master Playback Volume", "Master Playback Volume",
		"AMic Playback Volume", "Old Mic Playback Volume",
		"CD Capture Volume", "IEC958 Optical Capture Volume",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर audigy_हटाओ_ctls_i2c_adc[] = अणु
		/* On the Audigy2 ZS Notebook
		 * Capture via WM8775  */
		"Mic Capture Volume",
		"Analog Mix Capture Volume",
		"Aux Capture Volume",
		"IEC958 Optical Capture Volume",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर audigy_हटाओ_ctls_1361t_adc[] = अणु
		/* On the Audigy2 the AC97 playback is piped पूर्णांकo
		 * the Philips ADC क्रम 24bit capture */
		"PCM Playback Switch",
		"PCM Playback Volume",
		"Capture Source",
		"Capture Switch",
		"Capture Volume",
		"Mic Capture Volume",
		"Headphone Playback Switch",
		"Headphone Playback Volume",
		"3D Control - Center",
		"3D Control - Depth",
		"3D Control - Switch",
		"Line2 Playback Volume",
		"Line2 Capture Volume",
		शून्य
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर audigy_नाम_ctls_1361t_adc[] = अणु
		"Master Playback Switch", "Master Capture Switch",
		"Master Playback Volume", "Master Capture Volume",
		"Wave Master Playback Volume", "Master Playback Volume",
		"Beep Playback Switch", "Beep Capture Switch",
		"Beep Playback Volume", "Beep Capture Volume",
		"Phone Playback Switch", "Phone Capture Switch",
		"Phone Playback Volume", "Phone Capture Volume",
		"Mic Playback Switch", "Mic Capture Switch",
		"Mic Playback Volume", "Mic Capture Volume",
		"Line Playback Switch", "Line Capture Switch",
		"Line Playback Volume", "Line Capture Volume",
		"CD Playback Switch", "CD Capture Switch",
		"CD Playback Volume", "CD Capture Volume",
		"Aux Playback Switch", "Aux Capture Switch",
		"Aux Playback Volume", "Aux Capture Volume",
		"Video Playback Switch", "Video Capture Switch",
		"Video Playback Volume", "Video Capture Volume",
		"Master Mono Playback Switch", "Phone Output Playback Switch",
		"Master Mono Playback Volume", "Phone Output Playback Volume",
		शून्य
	पूर्ण;

	अगर (emu->card_capabilities->ac97_chip) अणु
		काष्ठा snd_ac97_bus *pbus;
		काष्ठा snd_ac97_ढाँचा ac97;
		अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
			.ग_लिखो = snd_emu10k1_ac97_ग_लिखो,
			.पढ़ो = snd_emu10k1_ac97_पढ़ो,
		पूर्ण;

		अगर ((err = snd_ac97_bus(emu->card, 0, &ops, शून्य, &pbus)) < 0)
			वापस err;
		pbus->no_vra = 1; /* we करोn't need VRA */
		
		स_रखो(&ac97, 0, माप(ac97));
		ac97.निजी_data = emu;
		ac97.निजी_मुक्त = snd_emu10k1_mixer_मुक्त_ac97;
		ac97.scaps = AC97_SCAP_NO_SPDIF;
		अगर ((err = snd_ac97_mixer(pbus, &ac97, &emu->ac97)) < 0) अणु
			अगर (emu->card_capabilities->ac97_chip == 1)
				वापस err;
			dev_info(emu->card->dev,
				 "AC97 is optional on this board\n");
			dev_info(emu->card->dev,
				 "Proceeding without ac97 mixers...\n");
			snd_device_मुक्त(emu->card, pbus);
			जाओ no_ac97; /* FIXME: get rid of ugly जाओs.. */
		पूर्ण
		अगर (emu->audigy) अणु
			/* set master volume to 0 dB */
			snd_ac97_ग_लिखो_cache(emu->ac97, AC97_MASTER, 0x0000);
			/* set capture source to mic */
			snd_ac97_ग_लिखो_cache(emu->ac97, AC97_REC_SEL, 0x0000);
			/* set mono output (TAD) to mic */
			snd_ac97_update_bits(emu->ac97, AC97_GENERAL_PURPOSE,
				0x0200, 0x0200);
			अगर (emu->card_capabilities->adc_1361t)
				c = audigy_हटाओ_ctls_1361t_adc;
			अन्यथा 
				c = audigy_हटाओ_ctls;
		पूर्ण अन्यथा अणु
			/*
			 * Credits क्रम cards based on STAC9758:
			 *   James Courtier-Dutton <James@superbug.demon.co.uk>
			 *   Voluspa <voluspa@comhem.se>
			 */
			अगर (emu->ac97->id == AC97_ID_STAC9758) अणु
				emu->rear_ac97 = 1;
				snd_emu10k1_ptr_ग_लिखो(emu, AC97SLOT, 0, AC97SLOT_CNTR|AC97SLOT_LFE|AC97SLOT_REAR_LEFT|AC97SLOT_REAR_RIGHT);
				snd_ac97_ग_लिखो_cache(emu->ac97, AC97_HEADPHONE, 0x0202);
				हटाओ_ctl(card,"Front Playback Volume");
				हटाओ_ctl(card,"Front Playback Switch");
			पूर्ण
			/* हटाओ unused AC97 controls */
			snd_ac97_ग_लिखो_cache(emu->ac97, AC97_SURROUND_MASTER, 0x0202);
			snd_ac97_ग_लिखो_cache(emu->ac97, AC97_CENTER_LFE_MASTER, 0x0202);
			c = emu10k1_हटाओ_ctls;
		पूर्ण
		क्रम (; *c; c++)
			हटाओ_ctl(card, *c);
	पूर्ण अन्यथा अगर (emu->card_capabilities->i2c_adc) अणु
		c = audigy_हटाओ_ctls_i2c_adc;
		क्रम (; *c; c++)
			हटाओ_ctl(card, *c);
	पूर्ण अन्यथा अणु
	no_ac97:
		अगर (emu->card_capabilities->ecard)
			म_नकल(emu->card->mixername, "EMU APS");
		अन्यथा अगर (emu->audigy)
			म_नकल(emu->card->mixername, "SB Audigy");
		अन्यथा
			म_नकल(emu->card->mixername, "Emu10k1");
	पूर्ण

	अगर (emu->audigy)
		अगर (emu->card_capabilities->adc_1361t)
			c = audigy_नाम_ctls_1361t_adc;
		अन्यथा अगर (emu->card_capabilities->i2c_adc)
			c = audigy_नाम_ctls_i2c_adc;
		अन्यथा
			c = audigy_नाम_ctls;
	अन्यथा
		c = emu10k1_नाम_ctls;
	क्रम (; *c; c += 2)
		नाम_ctl(card, c[0], c[1]);

	अगर (emu->card_capabilities->subप्रणाली == 0x80401102) अणु /* SB Live! Platinum CT4760P */
		हटाओ_ctl(card, "Center Playback Volume");
		हटाओ_ctl(card, "LFE Playback Volume");
		हटाओ_ctl(card, "Wave Center Playback Volume");
		हटाओ_ctl(card, "Wave LFE Playback Volume");
	पूर्ण
	अगर (emu->card_capabilities->subप्रणाली == 0x20071102) अणु  /* Audigy 4 Pro */
		नाम_ctl(card, "Line2 Capture Volume", "Line1/Mic Capture Volume");
		नाम_ctl(card, "Analog Mix Capture Volume", "Line2 Capture Volume");
		नाम_ctl(card, "Aux2 Capture Volume", "Line3 Capture Volume");
		नाम_ctl(card, "Mic Capture Volume", "Unknown1 Capture Volume");
	पूर्ण
	अगर ((kctl = emu->ctl_send_routing = snd_ctl_new1(&snd_emu10k1_send_routing_control, emu)) == शून्य)
		वापस -ENOMEM;
	kctl->id.device = pcm_device;
	अगर ((err = snd_ctl_add(card, kctl)))
		वापस err;
	अगर ((kctl = emu->ctl_send_volume = snd_ctl_new1(&snd_emu10k1_send_volume_control, emu)) == शून्य)
		वापस -ENOMEM;
	kctl->id.device = pcm_device;
	अगर ((err = snd_ctl_add(card, kctl)))
		वापस err;
	अगर ((kctl = emu->ctl_attn = snd_ctl_new1(&snd_emu10k1_attn_control, emu)) == शून्य)
		वापस -ENOMEM;
	kctl->id.device = pcm_device;
	अगर ((err = snd_ctl_add(card, kctl)))
		वापस err;

	अगर ((kctl = emu->ctl_efx_send_routing = snd_ctl_new1(&snd_emu10k1_efx_send_routing_control, emu)) == शून्य)
		वापस -ENOMEM;
	kctl->id.device = multi_device;
	अगर ((err = snd_ctl_add(card, kctl)))
		वापस err;
	
	अगर ((kctl = emu->ctl_efx_send_volume = snd_ctl_new1(&snd_emu10k1_efx_send_volume_control, emu)) == शून्य)
		वापस -ENOMEM;
	kctl->id.device = multi_device;
	अगर ((err = snd_ctl_add(card, kctl)))
		वापस err;
	
	अगर ((kctl = emu->ctl_efx_attn = snd_ctl_new1(&snd_emu10k1_efx_attn_control, emu)) == शून्य)
		वापस -ENOMEM;
	kctl->id.device = multi_device;
	अगर ((err = snd_ctl_add(card, kctl)))
		वापस err;

	/* initialize the routing and volume table क्रम each pcm playback stream */
	क्रम (pcm = 0; pcm < 32; pcm++) अणु
		काष्ठा snd_emu10k1_pcm_mixer *mix;
		पूर्णांक v;
		
		mix = &emu->pcm_mixer[pcm];
		mix->epcm = शून्य;

		क्रम (v = 0; v < 4; v++)
			mix->send_routing[0][v] = 
				mix->send_routing[1][v] = 
				mix->send_routing[2][v] = v;
		
		स_रखो(&mix->send_volume, 0, माप(mix->send_volume));
		mix->send_volume[0][0] = mix->send_volume[0][1] =
		mix->send_volume[1][0] = mix->send_volume[2][1] = 255;
		
		mix->attn[0] = mix->attn[1] = mix->attn[2] = 0xffff;
	पूर्ण
	
	/* initialize the routing and volume table क्रम the multichannel playback stream */
	क्रम (pcm = 0; pcm < NUM_EFX_PLAYBACK; pcm++) अणु
		काष्ठा snd_emu10k1_pcm_mixer *mix;
		पूर्णांक v;
		
		mix = &emu->efx_pcm_mixer[pcm];
		mix->epcm = शून्य;

		mix->send_routing[0][0] = pcm;
		mix->send_routing[0][1] = (pcm == 0) ? 1 : 0;
		क्रम (v = 0; v < 2; v++)
			mix->send_routing[0][2+v] = 13+v;
		अगर (emu->audigy)
			क्रम (v = 0; v < 4; v++)
				mix->send_routing[0][4+v] = 60+v;
		
		स_रखो(&mix->send_volume, 0, माप(mix->send_volume));
		mix->send_volume[0][0]  = 255;
		
		mix->attn[0] = 0xffff;
	पूर्ण
	
	अगर (! emu->card_capabilities->ecard) अणु /* FIXME: APS has these controls? */
		/* sb live! and audigy */
		अगर ((kctl = snd_ctl_new1(&snd_emu10k1_spdअगर_mask_control, emu)) == शून्य)
			वापस -ENOMEM;
		अगर (!emu->audigy)
			kctl->id.device = emu->pcm_efx->device;
		अगर ((err = snd_ctl_add(card, kctl)))
			वापस err;
		अगर ((kctl = snd_ctl_new1(&snd_emu10k1_spdअगर_control, emu)) == शून्य)
			वापस -ENOMEM;
		अगर (!emu->audigy)
			kctl->id.device = emu->pcm_efx->device;
		अगर ((err = snd_ctl_add(card, kctl)))
			वापस err;
	पूर्ण

	अगर (emu->card_capabilities->emu_model) अणु
		;  /* Disable the snd_audigy_spdअगर_shared_spdअगर */
	पूर्ण अन्यथा अगर (emu->audigy) अणु
		अगर ((kctl = snd_ctl_new1(&snd_audigy_shared_spdअगर, emu)) == शून्य)
			वापस -ENOMEM;
		अगर ((err = snd_ctl_add(card, kctl)))
			वापस err;
#अगर 0
		अगर ((kctl = snd_ctl_new1(&snd_audigy_spdअगर_output_rate, emu)) == शून्य)
			वापस -ENOMEM;
		अगर ((err = snd_ctl_add(card, kctl)))
			वापस err;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (! emu->card_capabilities->ecard) अणु
		/* sb live! */
		अगर ((kctl = snd_ctl_new1(&snd_emu10k1_shared_spdअगर, emu)) == शून्य)
			वापस -ENOMEM;
		अगर ((err = snd_ctl_add(card, kctl)))
			वापस err;
	पूर्ण
	अगर (emu->card_capabilities->ca0151_chip) अणु /* P16V */
		अगर ((err = snd_p16v_mixer(emu)))
			वापस err;
	पूर्ण

	अगर (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616) अणु
		/* 1616(m) cardbus */
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(snd_emu1616_output_क्रमागत_ctls); i++) अणु
			err = snd_ctl_add(card,
				snd_ctl_new1(&snd_emu1616_output_क्रमागत_ctls[i],
					     emu));
			अगर (err < 0)
				वापस err;
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(snd_emu1010_input_क्रमागत_ctls); i++) अणु
			err = snd_ctl_add(card,
				snd_ctl_new1(&snd_emu1010_input_क्रमागत_ctls[i],
					     emu));
			अगर (err < 0)
				वापस err;
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(snd_emu1010_adc_pads) - 2; i++) अणु
			err = snd_ctl_add(card,
				snd_ctl_new1(&snd_emu1010_adc_pads[i], emu));
			अगर (err < 0)
				वापस err;
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(snd_emu1010_dac_pads) - 2; i++) अणु
			err = snd_ctl_add(card,
				snd_ctl_new1(&snd_emu1010_dac_pads[i], emu));
			अगर (err < 0)
				वापस err;
		पूर्ण
		err = snd_ctl_add(card,
			snd_ctl_new1(&snd_emu1010_पूर्णांकernal_घड़ी, emu));
		अगर (err < 0)
			वापस err;
		err = snd_ctl_add(card,
			snd_ctl_new1(&snd_emu1010_optical_out, emu));
		अगर (err < 0)
			वापस err;
		err = snd_ctl_add(card,
			snd_ctl_new1(&snd_emu1010_optical_in, emu));
		अगर (err < 0)
			वापस err;

	पूर्ण अन्यथा अगर (emu->card_capabilities->emu_model) अणु
		/* all other e-mu cards क्रम now */
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(snd_emu1010_output_क्रमागत_ctls); i++) अणु
			err = snd_ctl_add(card,
				snd_ctl_new1(&snd_emu1010_output_क्रमागत_ctls[i],
					     emu));
			अगर (err < 0)
				वापस err;
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(snd_emu1010_input_क्रमागत_ctls); i++) अणु
			err = snd_ctl_add(card,
				snd_ctl_new1(&snd_emu1010_input_क्रमागत_ctls[i],
					     emu));
			अगर (err < 0)
				वापस err;
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(snd_emu1010_adc_pads); i++) अणु
			err = snd_ctl_add(card,
				snd_ctl_new1(&snd_emu1010_adc_pads[i], emu));
			अगर (err < 0)
				वापस err;
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(snd_emu1010_dac_pads); i++) अणु
			err = snd_ctl_add(card,
				snd_ctl_new1(&snd_emu1010_dac_pads[i], emu));
			अगर (err < 0)
				वापस err;
		पूर्ण
		err = snd_ctl_add(card,
			snd_ctl_new1(&snd_emu1010_पूर्णांकernal_घड़ी, emu));
		अगर (err < 0)
			वापस err;
		err = snd_ctl_add(card,
			snd_ctl_new1(&snd_emu1010_optical_out, emu));
		अगर (err < 0)
			वापस err;
		err = snd_ctl_add(card,
			snd_ctl_new1(&snd_emu1010_optical_in, emu));
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर ( emu->card_capabilities->i2c_adc) अणु
		पूर्णांक i;

		err = snd_ctl_add(card, snd_ctl_new1(&snd_audigy_i2c_capture_source, emu));
		अगर (err < 0)
			वापस err;

		क्रम (i = 0; i < ARRAY_SIZE(snd_audigy_i2c_volume_ctls); i++) अणु
			err = snd_ctl_add(card, snd_ctl_new1(&snd_audigy_i2c_volume_ctls[i], emu));
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
		
	अगर (emu->card_capabilities->ac97_chip && emu->audigy) अणु
		err = snd_ctl_add(card, snd_ctl_new1(&snd_audigy_capture_boost,
						     emu));
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
