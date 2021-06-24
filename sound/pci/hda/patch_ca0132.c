<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HD audio पूर्णांकerface patch क्रम Creative CA0132 chip
 *
 * Copyright (c) 2011, Creative Technology Ltd.
 *
 * Based on patch_ca0110.c
 * Copyright (c) 2008 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <यंत्र/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"
#समावेश "hda_auto_parser.h"
#समावेश "hda_jack.h"

#समावेश "ca0132_regs.h"

/* Enable this to see controls क्रम tuning purpose. */
/*#घोषणा ENABLE_TUNING_CONTROLS*/

#अगर_घोषित ENABLE_TUNING_CONTROLS
#समावेश <sound/tlv.h>
#पूर्ण_अगर

#घोषणा FLOAT_ZERO	0x00000000
#घोषणा FLOAT_ONE	0x3f800000
#घोषणा FLOAT_TWO	0x40000000
#घोषणा FLOAT_THREE     0x40400000
#घोषणा FLOAT_FIVE	0x40a00000
#घोषणा FLOAT_SIX       0x40c00000
#घोषणा FLOAT_EIGHT     0x41000000
#घोषणा FLOAT_MINUS_5	0xc0a00000

#घोषणा UNSOL_TAG_DSP	0x16

#घोषणा DSP_DMA_WRITE_BUFLEN_INIT (1UL<<18)
#घोषणा DSP_DMA_WRITE_BUFLEN_OVLY (1UL<<15)

#घोषणा DMA_TRANSFER_FRAME_SIZE_NWORDS		8
#घोषणा DMA_TRANSFER_MAX_FRAME_SIZE_NWORDS	32
#घोषणा DMA_OVERLAY_FRAME_SIZE_NWORDS		2

#घोषणा MASTERCONTROL				0x80
#घोषणा MASTERCONTROL_ALLOC_DMA_CHAN		10
#घोषणा MASTERCONTROL_QUERY_SPEAKER_EQ_ADDRESS	60

#घोषणा WIDGET_CHIP_CTRL      0x15
#घोषणा WIDGET_DSP_CTRL       0x16

#घोषणा MEM_CONNID_MICIN1     3
#घोषणा MEM_CONNID_MICIN2     5
#घोषणा MEM_CONNID_MICOUT1    12
#घोषणा MEM_CONNID_MICOUT2    14
#घोषणा MEM_CONNID_WUH        10
#घोषणा MEM_CONNID_DSP        16
#घोषणा MEM_CONNID_DMIC       100

#घोषणा SCP_SET    0
#घोषणा SCP_GET    1

#घोषणा EFX_खाता   "ctefx.bin"
#घोषणा DESKTOP_EFX_खाता   "ctefx-desktop.bin"
#घोषणा R3DI_EFX_खाता  "ctefx-r3di.bin"

#अगर_घोषित CONFIG_SND_HDA_CODEC_CA0132_DSP
MODULE_FIRMWARE(EFX_खाता);
MODULE_FIRMWARE(DESKTOP_EFX_खाता);
MODULE_FIRMWARE(R3DI_EFX_खाता);
#पूर्ण_अगर

अटल स्थिर अक्षर *स्थिर dirstr[2] = अणु "Playback", "Capture" पूर्ण;

#घोषणा NUM_OF_OUTPUTS 2
अटल स्थिर अक्षर *स्थिर out_type_str[2] = अणु "Speakers", "Headphone" पूर्ण;
क्रमागत अणु
	SPEAKER_OUT,
	HEADPHONE_OUT,
पूर्ण;

क्रमागत अणु
	DIGITAL_MIC,
	LINE_MIC_IN
पूर्ण;

/* Strings क्रम Input Source Enum Control */
अटल स्थिर अक्षर *स्थिर in_src_str[3] = अणु "Microphone", "Line In", "Front Microphone" पूर्ण;
#घोषणा IN_SRC_NUM_OF_INPUTS 3
क्रमागत अणु
	REAR_MIC,
	REAR_LINE_IN,
	FRONT_MIC,
पूर्ण;

क्रमागत अणु
#घोषणा VNODE_START_NID    0x80
	VNID_SPK = VNODE_START_NID,			/* Speaker vnid */
	VNID_MIC,
	VNID_HP_SEL,
	VNID_AMIC1_SEL,
	VNID_HP_ASEL,
	VNID_AMIC1_ASEL,
	VNODE_END_NID,
#घोषणा VNODES_COUNT  (VNODE_END_NID - VNODE_START_NID)

#घोषणा EFFECT_START_NID    0x90
#घोषणा OUT_EFFECT_START_NID    EFFECT_START_NID
	SURROUND = OUT_EFFECT_START_NID,
	CRYSTALIZER,
	DIALOG_PLUS,
	SMART_VOLUME,
	X_BASS,
	EQUALIZER,
	OUT_EFFECT_END_NID,
#घोषणा OUT_EFFECTS_COUNT  (OUT_EFFECT_END_NID - OUT_EFFECT_START_NID)

#घोषणा IN_EFFECT_START_NID  OUT_EFFECT_END_NID
	ECHO_CANCELLATION = IN_EFFECT_START_NID,
	VOICE_FOCUS,
	MIC_SVM,
	NOISE_REDUCTION,
	IN_EFFECT_END_NID,
#घोषणा IN_EFFECTS_COUNT  (IN_EFFECT_END_NID - IN_EFFECT_START_NID)

	VOICEFX = IN_EFFECT_END_NID,
	PLAY_ENHANCEMENT,
	CRYSTAL_VOICE,
	EFFECT_END_NID,
	OUTPUT_SOURCE_ENUM,
	INPUT_SOURCE_ENUM,
	XBASS_XOVER,
	EQ_PRESET_ENUM,
	SMART_VOLUME_ENUM,
	MIC_BOOST_ENUM,
	AE5_HEADPHONE_GAIN_ENUM,
	AE5_SOUND_FILTER_ENUM,
	ZXR_HEADPHONE_GAIN,
	SPEAKER_CHANNEL_CFG_ENUM,
	SPEAKER_FULL_RANGE_FRONT,
	SPEAKER_FULL_RANGE_REAR,
	BASS_REसूचीECTION,
	BASS_REसूचीECTION_XOVER,
#घोषणा EFFECTS_COUNT  (EFFECT_END_NID - EFFECT_START_NID)
पूर्ण;

/* Effects values size*/
#घोषणा EFFECT_VALS_MAX_COUNT 12

/*
 * Default values क्रम the effect slider controls, they are in order of their
 * effect NID's. Surround, Crystalizer, Dialog Plus, Smart Volume, and then
 * X-bass.
 */
अटल स्थिर अचिन्हित पूर्णांक effect_slider_शेषs[] = अणु67, 65, 50, 74, 50पूर्ण;
/* Amount of effect level sliders क्रम ca0132_alt controls. */
#घोषणा EFFECT_LEVEL_SLIDERS 5

/* Latency पूर्णांकroduced by DSP blocks in milliseconds. */
#घोषणा DSP_CAPTURE_INIT_LATENCY        0
#घोषणा DSP_CRYSTAL_VOICE_LATENCY       124
#घोषणा DSP_PLAYBACK_INIT_LATENCY       13
#घोषणा DSP_PLAY_ENHANCEMENT_LATENCY    30
#घोषणा DSP_SPEAKER_OUT_LATENCY         7

काष्ठा ct_effect अणु
	अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	hda_nid_t nid;
	पूर्णांक mid; /*effect module ID*/
	पूर्णांक reqs[EFFECT_VALS_MAX_COUNT]; /*effect module request*/
	पूर्णांक direct; /* 0:output; 1:input*/
	पूर्णांक params; /* number of शेष non-on/off params */
	/*effect शेष values, 1st is on/off. */
	अचिन्हित पूर्णांक def_vals[EFFECT_VALS_MAX_COUNT];
पूर्ण;

#घोषणा EFX_सूची_OUT 0
#घोषणा EFX_सूची_IN  1

अटल स्थिर काष्ठा ct_effect ca0132_effects[EFFECTS_COUNT] = अणु
	अणु .name = "Surround",
	  .nid = SURROUND,
	  .mid = 0x96,
	  .reqs = अणु0, 1पूर्ण,
	  .direct = EFX_सूची_OUT,
	  .params = 1,
	  .def_vals = अणु0x3F800000, 0x3F2B851Fपूर्ण
	पूर्ण,
	अणु .name = "Crystalizer",
	  .nid = CRYSTALIZER,
	  .mid = 0x96,
	  .reqs = अणु7, 8पूर्ण,
	  .direct = EFX_सूची_OUT,
	  .params = 1,
	  .def_vals = अणु0x3F800000, 0x3F266666पूर्ण
	पूर्ण,
	अणु .name = "Dialog Plus",
	  .nid = DIALOG_PLUS,
	  .mid = 0x96,
	  .reqs = अणु2, 3पूर्ण,
	  .direct = EFX_सूची_OUT,
	  .params = 1,
	  .def_vals = अणु0x00000000, 0x3F000000पूर्ण
	पूर्ण,
	अणु .name = "Smart Volume",
	  .nid = SMART_VOLUME,
	  .mid = 0x96,
	  .reqs = अणु4, 5, 6पूर्ण,
	  .direct = EFX_सूची_OUT,
	  .params = 2,
	  .def_vals = अणु0x3F800000, 0x3F3D70A4, 0x00000000पूर्ण
	पूर्ण,
	अणु .name = "X-Bass",
	  .nid = X_BASS,
	  .mid = 0x96,
	  .reqs = अणु24, 23, 25पूर्ण,
	  .direct = EFX_सूची_OUT,
	  .params = 2,
	  .def_vals = अणु0x3F800000, 0x42A00000, 0x3F000000पूर्ण
	पूर्ण,
	अणु .name = "Equalizer",
	  .nid = EQUALIZER,
	  .mid = 0x96,
	  .reqs = अणु9, 10, 11, 12, 13, 14,
			15, 16, 17, 18, 19, 20पूर्ण,
	  .direct = EFX_सूची_OUT,
	  .params = 11,
	  .def_vals = अणु0x00000000, 0x00000000, 0x00000000, 0x00000000,
		       0x00000000, 0x00000000, 0x00000000, 0x00000000,
		       0x00000000, 0x00000000, 0x00000000, 0x00000000पूर्ण
	पूर्ण,
	अणु .name = "Echo Cancellation",
	  .nid = ECHO_CANCELLATION,
	  .mid = 0x95,
	  .reqs = अणु0, 1, 2, 3पूर्ण,
	  .direct = EFX_सूची_IN,
	  .params = 3,
	  .def_vals = अणु0x00000000, 0x3F3A9692, 0x00000000, 0x00000000पूर्ण
	पूर्ण,
	अणु .name = "Voice Focus",
	  .nid = VOICE_FOCUS,
	  .mid = 0x95,
	  .reqs = अणु6, 7, 8, 9पूर्ण,
	  .direct = EFX_सूची_IN,
	  .params = 3,
	  .def_vals = अणु0x3F800000, 0x3D7DF3B6, 0x41F00000, 0x41F00000पूर्ण
	पूर्ण,
	अणु .name = "Mic SVM",
	  .nid = MIC_SVM,
	  .mid = 0x95,
	  .reqs = अणु44, 45पूर्ण,
	  .direct = EFX_सूची_IN,
	  .params = 1,
	  .def_vals = अणु0x00000000, 0x3F3D70A4पूर्ण
	पूर्ण,
	अणु .name = "Noise Reduction",
	  .nid = NOISE_REDUCTION,
	  .mid = 0x95,
	  .reqs = अणु4, 5पूर्ण,
	  .direct = EFX_सूची_IN,
	  .params = 1,
	  .def_vals = अणु0x3F800000, 0x3F000000पूर्ण
	पूर्ण,
	अणु .name = "VoiceFX",
	  .nid = VOICEFX,
	  .mid = 0x95,
	  .reqs = अणु10, 11, 12, 13, 14, 15, 16, 17, 18पूर्ण,
	  .direct = EFX_सूची_IN,
	  .params = 8,
	  .def_vals = अणु0x00000000, 0x43C80000, 0x44AF0000, 0x44FA0000,
		       0x3F800000, 0x3F800000, 0x3F800000, 0x00000000,
		       0x00000000पूर्ण
	पूर्ण
पूर्ण;

/* Tuning controls */
#अगर_घोषित ENABLE_TUNING_CONTROLS

क्रमागत अणु
#घोषणा TUNING_CTL_START_NID  0xC0
	WEDGE_ANGLE = TUNING_CTL_START_NID,
	SVM_LEVEL,
	EQUALIZER_BAND_0,
	EQUALIZER_BAND_1,
	EQUALIZER_BAND_2,
	EQUALIZER_BAND_3,
	EQUALIZER_BAND_4,
	EQUALIZER_BAND_5,
	EQUALIZER_BAND_6,
	EQUALIZER_BAND_7,
	EQUALIZER_BAND_8,
	EQUALIZER_BAND_9,
	TUNING_CTL_END_NID
#घोषणा TUNING_CTLS_COUNT  (TUNING_CTL_END_NID - TUNING_CTL_START_NID)
पूर्ण;

काष्ठा ct_tuning_ctl अणु
	अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	hda_nid_t parent_nid;
	hda_nid_t nid;
	पूर्णांक mid; /*effect module ID*/
	पूर्णांक req; /*effect module request*/
	पूर्णांक direct; /* 0:output; 1:input*/
	अचिन्हित पूर्णांक def_val;/*effect शेष values*/
पूर्ण;

अटल स्थिर काष्ठा ct_tuning_ctl ca0132_tuning_ctls[] = अणु
	अणु .name = "Wedge Angle",
	  .parent_nid = VOICE_FOCUS,
	  .nid = WEDGE_ANGLE,
	  .mid = 0x95,
	  .req = 8,
	  .direct = EFX_सूची_IN,
	  .def_val = 0x41F00000
	पूर्ण,
	अणु .name = "SVM Level",
	  .parent_nid = MIC_SVM,
	  .nid = SVM_LEVEL,
	  .mid = 0x95,
	  .req = 45,
	  .direct = EFX_सूची_IN,
	  .def_val = 0x3F3D70A4
	पूर्ण,
	अणु .name = "EQ Band0",
	  .parent_nid = EQUALIZER,
	  .nid = EQUALIZER_BAND_0,
	  .mid = 0x96,
	  .req = 11,
	  .direct = EFX_सूची_OUT,
	  .def_val = 0x00000000
	पूर्ण,
	अणु .name = "EQ Band1",
	  .parent_nid = EQUALIZER,
	  .nid = EQUALIZER_BAND_1,
	  .mid = 0x96,
	  .req = 12,
	  .direct = EFX_सूची_OUT,
	  .def_val = 0x00000000
	पूर्ण,
	अणु .name = "EQ Band2",
	  .parent_nid = EQUALIZER,
	  .nid = EQUALIZER_BAND_2,
	  .mid = 0x96,
	  .req = 13,
	  .direct = EFX_सूची_OUT,
	  .def_val = 0x00000000
	पूर्ण,
	अणु .name = "EQ Band3",
	  .parent_nid = EQUALIZER,
	  .nid = EQUALIZER_BAND_3,
	  .mid = 0x96,
	  .req = 14,
	  .direct = EFX_सूची_OUT,
	  .def_val = 0x00000000
	पूर्ण,
	अणु .name = "EQ Band4",
	  .parent_nid = EQUALIZER,
	  .nid = EQUALIZER_BAND_4,
	  .mid = 0x96,
	  .req = 15,
	  .direct = EFX_सूची_OUT,
	  .def_val = 0x00000000
	पूर्ण,
	अणु .name = "EQ Band5",
	  .parent_nid = EQUALIZER,
	  .nid = EQUALIZER_BAND_5,
	  .mid = 0x96,
	  .req = 16,
	  .direct = EFX_सूची_OUT,
	  .def_val = 0x00000000
	पूर्ण,
	अणु .name = "EQ Band6",
	  .parent_nid = EQUALIZER,
	  .nid = EQUALIZER_BAND_6,
	  .mid = 0x96,
	  .req = 17,
	  .direct = EFX_सूची_OUT,
	  .def_val = 0x00000000
	पूर्ण,
	अणु .name = "EQ Band7",
	  .parent_nid = EQUALIZER,
	  .nid = EQUALIZER_BAND_7,
	  .mid = 0x96,
	  .req = 18,
	  .direct = EFX_सूची_OUT,
	  .def_val = 0x00000000
	पूर्ण,
	अणु .name = "EQ Band8",
	  .parent_nid = EQUALIZER,
	  .nid = EQUALIZER_BAND_8,
	  .mid = 0x96,
	  .req = 19,
	  .direct = EFX_सूची_OUT,
	  .def_val = 0x00000000
	पूर्ण,
	अणु .name = "EQ Band9",
	  .parent_nid = EQUALIZER,
	  .nid = EQUALIZER_BAND_9,
	  .mid = 0x96,
	  .req = 20,
	  .direct = EFX_सूची_OUT,
	  .def_val = 0x00000000
	पूर्ण
पूर्ण;
#पूर्ण_अगर

/* Voice FX Presets */
#घोषणा VOICEFX_MAX_PARAM_COUNT 9

काष्ठा ct_voicefx अणु
	अक्षर *name;
	hda_nid_t nid;
	पूर्णांक mid;
	पूर्णांक reqs[VOICEFX_MAX_PARAM_COUNT]; /*effect module request*/
पूर्ण;

काष्ठा ct_voicefx_preset अणु
	अक्षर *name; /*preset name*/
	अचिन्हित पूर्णांक vals[VOICEFX_MAX_PARAM_COUNT];
पूर्ण;

अटल स्थिर काष्ठा ct_voicefx ca0132_voicefx = अणु
	.name = "VoiceFX Capture Switch",
	.nid = VOICEFX,
	.mid = 0x95,
	.reqs = अणु10, 11, 12, 13, 14, 15, 16, 17, 18पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ct_voicefx_preset ca0132_voicefx_presets[] = अणु
	अणु .name = "Neutral",
	  .vals = अणु 0x00000000, 0x43C80000, 0x44AF0000,
		    0x44FA0000, 0x3F800000, 0x3F800000,
		    0x3F800000, 0x00000000, 0x00000000 पूर्ण
	पूर्ण,
	अणु .name = "Female2Male",
	  .vals = अणु 0x3F800000, 0x43C80000, 0x44AF0000,
		    0x44FA0000, 0x3F19999A, 0x3F866666,
		    0x3F800000, 0x00000000, 0x00000000 पूर्ण
	पूर्ण,
	अणु .name = "Male2Female",
	  .vals = अणु 0x3F800000, 0x43C80000, 0x44AF0000,
		    0x450AC000, 0x4017AE14, 0x3F6B851F,
		    0x3F800000, 0x00000000, 0x00000000 पूर्ण
	पूर्ण,
	अणु .name = "ScrappyKid",
	  .vals = अणु 0x3F800000, 0x43C80000, 0x44AF0000,
		    0x44FA0000, 0x40400000, 0x3F28F5C3,
		    0x3F800000, 0x00000000, 0x00000000 पूर्ण
	पूर्ण,
	अणु .name = "Elderly",
	  .vals = अणु 0x3F800000, 0x44324000, 0x44BB8000,
		    0x44E10000, 0x3FB33333, 0x3FB9999A,
		    0x3F800000, 0x3E3A2E43, 0x00000000 पूर्ण
	पूर्ण,
	अणु .name = "Orc",
	  .vals = अणु 0x3F800000, 0x43EA0000, 0x44A52000,
		    0x45098000, 0x3F266666, 0x3FC00000,
		    0x3F800000, 0x00000000, 0x00000000 पूर्ण
	पूर्ण,
	अणु .name = "Elf",
	  .vals = अणु 0x3F800000, 0x43C70000, 0x44AE6000,
		    0x45193000, 0x3F8E147B, 0x3F75C28F,
		    0x3F800000, 0x00000000, 0x00000000 पूर्ण
	पूर्ण,
	अणु .name = "Dwarf",
	  .vals = अणु 0x3F800000, 0x43930000, 0x44BEE000,
		    0x45007000, 0x3F451EB8, 0x3F7851EC,
		    0x3F800000, 0x00000000, 0x00000000 पूर्ण
	पूर्ण,
	अणु .name = "AlienBrute",
	  .vals = अणु 0x3F800000, 0x43BFC5AC, 0x44B28FDF,
		    0x451F6000, 0x3F266666, 0x3FA7D945,
		    0x3F800000, 0x3CF5C28F, 0x00000000 पूर्ण
	पूर्ण,
	अणु .name = "Robot",
	  .vals = अणु 0x3F800000, 0x43C80000, 0x44AF0000,
		    0x44FA0000, 0x3FB2718B, 0x3F800000,
		    0xBC07010E, 0x00000000, 0x00000000 पूर्ण
	पूर्ण,
	अणु .name = "Marine",
	  .vals = अणु 0x3F800000, 0x43C20000, 0x44906000,
		    0x44E70000, 0x3F4CCCCD, 0x3F8A3D71,
		    0x3F0A3D71, 0x00000000, 0x00000000 पूर्ण
	पूर्ण,
	अणु .name = "Emo",
	  .vals = अणु 0x3F800000, 0x43C80000, 0x44AF0000,
		    0x44FA0000, 0x3F800000, 0x3F800000,
		    0x3E4CCCCD, 0x00000000, 0x00000000 पूर्ण
	पूर्ण,
	अणु .name = "DeepVoice",
	  .vals = अणु 0x3F800000, 0x43A9C5AC, 0x44AA4FDF,
		    0x44FFC000, 0x3EDBB56F, 0x3F99C4CA,
		    0x3F800000, 0x00000000, 0x00000000 पूर्ण
	पूर्ण,
	अणु .name = "Munchkin",
	  .vals = अणु 0x3F800000, 0x43C80000, 0x44AF0000,
		    0x44FA0000, 0x3F800000, 0x3F1A043C,
		    0x3F800000, 0x00000000, 0x00000000 पूर्ण
	पूर्ण
पूर्ण;

/* ca0132 EQ presets, taken from Winकरोws Sound Blaster Z Driver */

#घोषणा EQ_PRESET_MAX_PARAM_COUNT 11

काष्ठा ct_eq अणु
	अक्षर *name;
	hda_nid_t nid;
	पूर्णांक mid;
	पूर्णांक reqs[EQ_PRESET_MAX_PARAM_COUNT]; /*effect module request*/
पूर्ण;

काष्ठा ct_eq_preset अणु
	अक्षर *name; /*preset name*/
	अचिन्हित पूर्णांक vals[EQ_PRESET_MAX_PARAM_COUNT];
पूर्ण;

अटल स्थिर काष्ठा ct_eq ca0132_alt_eq_क्रमागत = अणु
	.name = "FX: Equalizer Preset Switch",
	.nid = EQ_PRESET_ENUM,
	.mid = 0x96,
	.reqs = अणु10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20पूर्ण
पूर्ण;


अटल स्थिर काष्ठा ct_eq_preset ca0132_alt_eq_presets[] = अणु
	अणु .name = "Flat",
	 .vals = अणु 0x00000000, 0x00000000, 0x00000000,
		   0x00000000, 0x00000000, 0x00000000,
		   0x00000000, 0x00000000, 0x00000000,
		   0x00000000, 0x00000000	     पूर्ण
	पूर्ण,
	अणु .name = "Acoustic",
	 .vals = अणु 0x00000000, 0x00000000, 0x3F8CCCCD,
		   0x40000000, 0x00000000, 0x00000000,
		   0x00000000, 0x00000000, 0x40000000,
		   0x40000000, 0x40000000	     पूर्ण
	पूर्ण,
	अणु .name = "Classical",
	 .vals = अणु 0x00000000, 0x00000000, 0x40C00000,
		   0x40C00000, 0x40466666, 0x00000000,
		   0x00000000, 0x00000000, 0x00000000,
		   0x40466666, 0x40466666	     पूर्ण
	पूर्ण,
	अणु .name = "Country",
	 .vals = अणु 0x00000000, 0xBF99999A, 0x00000000,
		   0x3FA66666, 0x3FA66666, 0x3F8CCCCD,
		   0x00000000, 0x00000000, 0x40000000,
		   0x40466666, 0x40800000	     पूर्ण
	पूर्ण,
	अणु .name = "Dance",
	 .vals = अणु 0x00000000, 0xBF99999A, 0x40000000,
		   0x40466666, 0x40866666, 0xBF99999A,
		   0xBF99999A, 0x00000000, 0x00000000,
		   0x40800000, 0x40800000	     पूर्ण
	पूर्ण,
	अणु .name = "Jazz",
	 .vals = अणु 0x00000000, 0x00000000, 0x00000000,
		   0x3F8CCCCD, 0x40800000, 0x40800000,
		   0x40800000, 0x00000000, 0x3F8CCCCD,
		   0x40466666, 0x40466666	     पूर्ण
	पूर्ण,
	अणु .name = "New Age",
	 .vals = अणु 0x00000000, 0x00000000, 0x40000000,
		   0x40000000, 0x00000000, 0x00000000,
		   0x00000000, 0x3F8CCCCD, 0x40000000,
		   0x40000000, 0x40000000	     पूर्ण
	पूर्ण,
	अणु .name = "Pop",
	 .vals = अणु 0x00000000, 0xBFCCCCCD, 0x00000000,
		   0x40000000, 0x40000000, 0x00000000,
		   0xBF99999A, 0xBF99999A, 0x00000000,
		   0x40466666, 0x40C00000	     पूर्ण
	पूर्ण,
	अणु .name = "Rock",
	 .vals = अणु 0x00000000, 0xBF99999A, 0xBF99999A,
		   0x3F8CCCCD, 0x40000000, 0xBF99999A,
		   0xBF99999A, 0x00000000, 0x00000000,
		   0x40800000, 0x40800000	     पूर्ण
	पूर्ण,
	अणु .name = "Vocal",
	 .vals = अणु 0x00000000, 0xC0000000, 0xBF99999A,
		   0xBF99999A, 0x00000000, 0x40466666,
		   0x40800000, 0x40466666, 0x00000000,
		   0x00000000, 0x3F8CCCCD	     पूर्ण
	पूर्ण
पूर्ण;

/*
 * DSP reqs क्रम handling full-range speakers/bass redirection. If a speaker is
 * set as not being full range, and bass redirection is enabled, all
 * frequencies below the crossover frequency are redirected to the LFE
 * channel. If the surround configuration has no LFE channel, this can't be
 * enabled. X-Bass must be disabled when using these.
 */
क्रमागत speaker_range_reqs अणु
	SPEAKER_BASS_REसूचीECT            = 0x15,
	SPEAKER_BASS_REसूचीECT_XOVER_FREQ = 0x16,
	/* Between 0x16-0x1a are the X-Bass reqs. */
	SPEAKER_FULL_RANGE_FRONT_L_R     = 0x1a,
	SPEAKER_FULL_RANGE_CENTER_LFE    = 0x1b,
	SPEAKER_FULL_RANGE_REAR_L_R      = 0x1c,
	SPEAKER_FULL_RANGE_SURROUND_L_R  = 0x1d,
	SPEAKER_BASS_REसूचीECT_SUB_GAIN   = 0x1e,
पूर्ण;

/*
 * Definitions क्रम the DSP req's to handle speaker tuning. These all beदीर्घ to
 * module ID 0x96, the output effects module.
 */
क्रमागत speaker_tuning_reqs अणु
	/*
	 * Currently, this value is always set to 0.0f. However, on Winकरोws,
	 * when selecting certain headphone profiles on the new Sound Blaster
	 * connect software, the QUERY_SPEAKER_EQ_ADDRESS req on mid 0x80 is
	 * sent. This माला_लो the speaker EQ address area, which is then used to
	 * send over (presumably) an equalizer profile क्रम the specअगरic
	 * headphone setup. It is sent using the same method the DSP
	 * firmware is uploaded with, which I believe is why the 'ctspeq.bin'
	 * file exists in linux firmware tree but goes unused. It would also
	 * explain why the QUERY_SPEAKER_EQ_ADDRESS req is defined but unused.
	 * Once this profile is sent over, SPEAKER_TUNING_USE_SPEAKER_EQ is
	 * set to 1.0f.
	 */
	SPEAKER_TUNING_USE_SPEAKER_EQ           = 0x1f,
	SPEAKER_TUNING_ENABLE_CENTER_EQ         = 0x20,
	SPEAKER_TUNING_FRONT_LEFT_VOL_LEVEL     = 0x21,
	SPEAKER_TUNING_FRONT_RIGHT_VOL_LEVEL    = 0x22,
	SPEAKER_TUNING_CENTER_VOL_LEVEL         = 0x23,
	SPEAKER_TUNING_LFE_VOL_LEVEL            = 0x24,
	SPEAKER_TUNING_REAR_LEFT_VOL_LEVEL      = 0x25,
	SPEAKER_TUNING_REAR_RIGHT_VOL_LEVEL     = 0x26,
	SPEAKER_TUNING_SURROUND_LEFT_VOL_LEVEL  = 0x27,
	SPEAKER_TUNING_SURROUND_RIGHT_VOL_LEVEL = 0x28,
	/*
	 * Inversion is used when setting headphone भवization to line
	 * out. Not sure why this is, but it's the only place it's ever used.
	 */
	SPEAKER_TUNING_FRONT_LEFT_INVERT        = 0x29,
	SPEAKER_TUNING_FRONT_RIGHT_INVERT       = 0x2a,
	SPEAKER_TUNING_CENTER_INVERT            = 0x2b,
	SPEAKER_TUNING_LFE_INVERT               = 0x2c,
	SPEAKER_TUNING_REAR_LEFT_INVERT         = 0x2d,
	SPEAKER_TUNING_REAR_RIGHT_INVERT        = 0x2e,
	SPEAKER_TUNING_SURROUND_LEFT_INVERT     = 0x2f,
	SPEAKER_TUNING_SURROUND_RIGHT_INVERT    = 0x30,
	/* Delay is used when setting surround speaker distance in Winकरोws. */
	SPEAKER_TUNING_FRONT_LEFT_DELAY         = 0x31,
	SPEAKER_TUNING_FRONT_RIGHT_DELAY        = 0x32,
	SPEAKER_TUNING_CENTER_DELAY             = 0x33,
	SPEAKER_TUNING_LFE_DELAY                = 0x34,
	SPEAKER_TUNING_REAR_LEFT_DELAY          = 0x35,
	SPEAKER_TUNING_REAR_RIGHT_DELAY         = 0x36,
	SPEAKER_TUNING_SURROUND_LEFT_DELAY      = 0x37,
	SPEAKER_TUNING_SURROUND_RIGHT_DELAY     = 0x38,
	/* Of these two, only mute seems to ever be used. */
	SPEAKER_TUNING_MAIN_VOLUME              = 0x39,
	SPEAKER_TUNING_MUTE                     = 0x3a,
पूर्ण;

/* Surround output channel count configuration काष्ठाures. */
#घोषणा SPEAKER_CHANNEL_CFG_COUNT 5
क्रमागत अणु
	SPEAKER_CHANNELS_2_0,
	SPEAKER_CHANNELS_2_1,
	SPEAKER_CHANNELS_4_0,
	SPEAKER_CHANNELS_4_1,
	SPEAKER_CHANNELS_5_1,
पूर्ण;

काष्ठा ca0132_alt_speaker_channel_cfg अणु
	अक्षर *name;
	अचिन्हित पूर्णांक val;
पूर्ण;

अटल स्थिर काष्ठा ca0132_alt_speaker_channel_cfg speaker_channel_cfgs[] = अणु
	अणु .name = "2.0",
	  .val = FLOAT_ONE
	पूर्ण,
	अणु .name = "2.1",
	  .val = FLOAT_TWO
	पूर्ण,
	अणु .name = "4.0",
	  .val = FLOAT_FIVE
	पूर्ण,
	अणु .name = "4.1",
	  .val = FLOAT_SIX
	पूर्ण,
	अणु .name = "5.1",
	  .val = FLOAT_EIGHT
	पूर्ण
पूर्ण;

/*
 * DSP volume setting काष्ठाs. Req 1 is left volume, req 2 is right volume,
 * and I करोn't know what the third req is, but it's always zero. I assume it's
 * some sort of update or set command to tell the DSP there's new volume info.
 */
#घोषणा DSP_VOL_OUT 0
#घोषणा DSP_VOL_IN  1

काष्ठा ct_dsp_volume_ctl अणु
	hda_nid_t vnid;
	पूर्णांक mid; /* module ID*/
	अचिन्हित पूर्णांक reqs[3]; /* scp req ID */
पूर्ण;

अटल स्थिर काष्ठा ct_dsp_volume_ctl ca0132_alt_vol_ctls[] = अणु
	अणु .vnid = VNID_SPK,
	  .mid = 0x32,
	  .reqs = अणु3, 4, 2पूर्ण
	पूर्ण,
	अणु .vnid = VNID_MIC,
	  .mid = 0x37,
	  .reqs = अणु2, 3, 1पूर्ण
	पूर्ण
पूर्ण;

/* Values क्रम ca0113_mmio_command_set क्रम selecting output. */
#घोषणा AE_CA0113_OUT_SET_COMMANDS 6
काष्ठा ae_ca0113_output_set अणु
	अचिन्हित पूर्णांक group[AE_CA0113_OUT_SET_COMMANDS];
	अचिन्हित पूर्णांक target[AE_CA0113_OUT_SET_COMMANDS];
	अचिन्हित पूर्णांक vals[NUM_OF_OUTPUTS][AE_CA0113_OUT_SET_COMMANDS];
पूर्ण;

अटल स्थिर काष्ठा ae_ca0113_output_set ae5_ca0113_output_presets = अणु
	.group =  अणु 0x30, 0x30, 0x48, 0x48, 0x48, 0x30 पूर्ण,
	.target = अणु 0x2e, 0x30, 0x0d, 0x17, 0x19, 0x32 पूर्ण,
		    /* Speakers. */
	.vals =   अणु अणु 0x00, 0x00, 0x40, 0x00, 0x00, 0x3f पूर्ण,
		    /* Headphones. */
		    अणु 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00 पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ae_ca0113_output_set ae7_ca0113_output_presets = अणु
	.group  = अणु 0x30, 0x30, 0x48, 0x48, 0x48, 0x30 पूर्ण,
	.target = अणु 0x2e, 0x30, 0x0d, 0x17, 0x19, 0x32 पूर्ण,
		    /* Speakers. */
	.vals   = अणु अणु 0x00, 0x00, 0x40, 0x00, 0x00, 0x3f पूर्ण,
		    /* Headphones. */
		    अणु 0x3f, 0x3f, 0x00, 0x00, 0x02, 0x00 पूर्ण पूर्ण,
पूर्ण;

/* ae5 ca0113 command sequences to set headphone gain levels. */
#घोषणा AE5_HEADPHONE_GAIN_PRESET_MAX_COMMANDS 4
काष्ठा ae5_headphone_gain_set अणु
	अक्षर *name;
	अचिन्हित पूर्णांक vals[AE5_HEADPHONE_GAIN_PRESET_MAX_COMMANDS];
पूर्ण;

अटल स्थिर काष्ठा ae5_headphone_gain_set ae5_headphone_gain_presets[] = अणु
	अणु .name = "Low (16-31",
	  .vals = अणु 0xff, 0x2c, 0xf5, 0x32 पूर्ण
	पूर्ण,
	अणु .name = "Medium (32-149",
	  .vals = अणु 0x38, 0xa8, 0x3e, 0x4c पूर्ण
	पूर्ण,
	अणु .name = "High (150-600",
	  .vals = अणु 0xff, 0xff, 0xff, 0x7f पूर्ण
	पूर्ण
पूर्ण;

काष्ठा ae5_filter_set अणु
	अक्षर *name;
	अचिन्हित पूर्णांक val;
पूर्ण;

अटल स्थिर काष्ठा ae5_filter_set ae5_filter_presets[] = अणु
	अणु .name = "Slow Roll Off",
	  .val = 0xa0
	पूर्ण,
	अणु .name = "Minimum Phase",
	  .val = 0xc0
	पूर्ण,
	अणु .name = "Fast Roll Off",
	  .val = 0x80
	पूर्ण
पूर्ण;

/*
 * Data काष्ठाures क्रम storing audio router remapping data. These are used to
 * remap a currently active streams ports.
 */
काष्ठा chipio_stream_remap_data अणु
	अचिन्हित पूर्णांक stream_id;
	अचिन्हित पूर्णांक count;

	अचिन्हित पूर्णांक offset[16];
	अचिन्हित पूर्णांक value[16];
पूर्ण;

अटल स्थिर काष्ठा chipio_stream_remap_data stream_remap_data[] = अणु
	अणु .stream_id = 0x14,
	  .count     = 0x04,
	  .offset    = अणु 0x00, 0x04, 0x08, 0x0c पूर्ण,
	  .value     = अणु 0x0001f8c0, 0x0001f9c1, 0x0001fac6, 0x0001fbc7 पूर्ण,
	पूर्ण,
	अणु .stream_id = 0x0c,
	  .count     = 0x0c,
	  .offset    = अणु 0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, 0x18, 0x1c,
			 0x20, 0x24, 0x28, 0x2c पूर्ण,
	  .value     = अणु 0x0001e0c0, 0x0001e1c1, 0x0001e4c2, 0x0001e5c3,
			 0x0001e2c4, 0x0001e3c5, 0x0001e8c6, 0x0001e9c7,
			 0x0001ecc8, 0x0001edc9, 0x0001eaca, 0x0001ebcb पूर्ण,
	पूर्ण,
	अणु .stream_id = 0x0c,
	  .count     = 0x08,
	  .offset    = अणु 0x08, 0x0c, 0x10, 0x14, 0x20, 0x24, 0x28, 0x2c पूर्ण,
	  .value     = अणु 0x000140c2, 0x000141c3, 0x000150c4, 0x000151c5,
			 0x000142c8, 0x000143c9, 0x000152ca, 0x000153cb पूर्ण,
	पूर्ण
पूर्ण;

क्रमागत hda_cmd_venकरोr_io अणु
	/* क्रम DspIO node */
	VENDOR_DSPIO_SCP_WRITE_DATA_LOW      = 0x000,
	VENDOR_DSPIO_SCP_WRITE_DATA_HIGH     = 0x100,

	VENDOR_DSPIO_STATUS                  = 0xF01,
	VENDOR_DSPIO_SCP_POST_READ_DATA      = 0x702,
	VENDOR_DSPIO_SCP_READ_DATA           = 0xF02,
	VENDOR_DSPIO_DSP_INIT                = 0x703,
	VENDOR_DSPIO_SCP_POST_COUNT_QUERY    = 0x704,
	VENDOR_DSPIO_SCP_READ_COUNT          = 0xF04,

	/* क्रम ChipIO node */
	VENDOR_CHIPIO_ADDRESS_LOW            = 0x000,
	VENDOR_CHIPIO_ADDRESS_HIGH           = 0x100,
	VENDOR_CHIPIO_STREAM_FORMAT          = 0x200,
	VENDOR_CHIPIO_DATA_LOW               = 0x300,
	VENDOR_CHIPIO_DATA_HIGH              = 0x400,

	VENDOR_CHIPIO_8051_WRITE_सूचीECT      = 0x500,
	VENDOR_CHIPIO_8051_READ_सूचीECT       = 0xD00,

	VENDOR_CHIPIO_GET_PARAMETER          = 0xF00,
	VENDOR_CHIPIO_STATUS                 = 0xF01,
	VENDOR_CHIPIO_HIC_POST_READ          = 0x702,
	VENDOR_CHIPIO_HIC_READ_DATA          = 0xF03,

	VENDOR_CHIPIO_8051_DATA_WRITE        = 0x707,
	VENDOR_CHIPIO_8051_DATA_READ         = 0xF07,
	VENDOR_CHIPIO_8051_PMEM_READ         = 0xF08,
	VENDOR_CHIPIO_8051_IRAM_WRITE        = 0x709,
	VENDOR_CHIPIO_8051_IRAM_READ         = 0xF09,

	VENDOR_CHIPIO_CT_EXTENSIONS_ENABLE   = 0x70A,
	VENDOR_CHIPIO_CT_EXTENSIONS_GET      = 0xF0A,

	VENDOR_CHIPIO_PLL_PMU_WRITE          = 0x70C,
	VENDOR_CHIPIO_PLL_PMU_READ           = 0xF0C,
	VENDOR_CHIPIO_8051_ADDRESS_LOW       = 0x70D,
	VENDOR_CHIPIO_8051_ADDRESS_HIGH      = 0x70E,
	VENDOR_CHIPIO_FLAG_SET               = 0x70F,
	VENDOR_CHIPIO_FLAGS_GET              = 0xF0F,
	VENDOR_CHIPIO_PARAM_SET              = 0x710,
	VENDOR_CHIPIO_PARAM_GET              = 0xF10,

	VENDOR_CHIPIO_PORT_ALLOC_CONFIG_SET  = 0x711,
	VENDOR_CHIPIO_PORT_ALLOC_SET         = 0x712,
	VENDOR_CHIPIO_PORT_ALLOC_GET         = 0xF12,
	VENDOR_CHIPIO_PORT_FREE_SET          = 0x713,

	VENDOR_CHIPIO_PARAM_EX_ID_GET        = 0xF17,
	VENDOR_CHIPIO_PARAM_EX_ID_SET        = 0x717,
	VENDOR_CHIPIO_PARAM_EX_VALUE_GET     = 0xF18,
	VENDOR_CHIPIO_PARAM_EX_VALUE_SET     = 0x718,

	VENDOR_CHIPIO_DMIC_CTL_SET           = 0x788,
	VENDOR_CHIPIO_DMIC_CTL_GET           = 0xF88,
	VENDOR_CHIPIO_DMIC_PIN_SET           = 0x789,
	VENDOR_CHIPIO_DMIC_PIN_GET           = 0xF89,
	VENDOR_CHIPIO_DMIC_MCLK_SET          = 0x78A,
	VENDOR_CHIPIO_DMIC_MCLK_GET          = 0xF8A,

	VENDOR_CHIPIO_EAPD_SEL_SET           = 0x78D
पूर्ण;

/*
 *  Control flag IDs
 */
क्रमागत control_flag_id अणु
	/* Connection manager stream setup is bypassed/enabled */
	CONTROL_FLAG_C_MGR                  = 0,
	/* DSP DMA is bypassed/enabled */
	CONTROL_FLAG_DMA                    = 1,
	/* 8051 'idle' mode is disabled/enabled */
	CONTROL_FLAG_IDLE_ENABLE            = 2,
	/* Tracker क्रम the SPDIF-in path is bypassed/enabled */
	CONTROL_FLAG_TRACKER                = 3,
	/* DigitalOut to Spdअगर2Out connection is disabled/enabled */
	CONTROL_FLAG_SPDIF2OUT              = 4,
	/* Digital Microphone is disabled/enabled */
	CONTROL_FLAG_DMIC                   = 5,
	/* ADC_B rate is 48 kHz/96 kHz */
	CONTROL_FLAG_ADC_B_96KHZ            = 6,
	/* ADC_C rate is 48 kHz/96 kHz */
	CONTROL_FLAG_ADC_C_96KHZ            = 7,
	/* DAC rate is 48 kHz/96 kHz (affects all DACs) */
	CONTROL_FLAG_DAC_96KHZ              = 8,
	/* DSP rate is 48 kHz/96 kHz */
	CONTROL_FLAG_DSP_96KHZ              = 9,
	/* SRC घड़ी is 98 MHz/196 MHz (196 MHz क्रमces rate to 96 KHz) */
	CONTROL_FLAG_SRC_CLOCK_196MHZ       = 10,
	/* SRC rate is 48 kHz/96 kHz (48 kHz disabled when घड़ी is 196 MHz) */
	CONTROL_FLAG_SRC_RATE_96KHZ         = 11,
	/* Decode Loop (DSP->SRC->DSP) is disabled/enabled */
	CONTROL_FLAG_DECODE_LOOP            = 12,
	/* De-emphasis filter on DAC-1 disabled/enabled */
	CONTROL_FLAG_DAC1_DEEMPHASIS        = 13,
	/* De-emphasis filter on DAC-2 disabled/enabled */
	CONTROL_FLAG_DAC2_DEEMPHASIS        = 14,
	/* De-emphasis filter on DAC-3 disabled/enabled */
	CONTROL_FLAG_DAC3_DEEMPHASIS        = 15,
	/* High-pass filter on ADC_B disabled/enabled */
	CONTROL_FLAG_ADC_B_HIGH_PASS        = 16,
	/* High-pass filter on ADC_C disabled/enabled */
	CONTROL_FLAG_ADC_C_HIGH_PASS        = 17,
	/* Common mode on Port_A disabled/enabled */
	CONTROL_FLAG_PORT_A_COMMON_MODE     = 18,
	/* Common mode on Port_D disabled/enabled */
	CONTROL_FLAG_PORT_D_COMMON_MODE     = 19,
	/* Impedance क्रम ramp generator on Port_A 16 Ohm/10K Ohm */
	CONTROL_FLAG_PORT_A_10KOHM_LOAD     = 20,
	/* Impedance क्रम ramp generator on Port_D, 16 Ohm/10K Ohm */
	CONTROL_FLAG_PORT_D_10KOHM_LOAD     = 21,
	/* ASI rate is 48kHz/96kHz */
	CONTROL_FLAG_ASI_96KHZ              = 22,
	/* DAC घातer settings able to control attached ports no/yes */
	CONTROL_FLAG_DACS_CONTROL_PORTS     = 23,
	/* Clock Stop OK reporting is disabled/enabled */
	CONTROL_FLAG_CONTROL_STOP_OK_ENABLE = 24,
	/* Number of control flags */
	CONTROL_FLAGS_MAX = (CONTROL_FLAG_CONTROL_STOP_OK_ENABLE+1)
पूर्ण;

/*
 * Control parameter IDs
 */
क्रमागत control_param_id अणु
	/* 0: None, 1: Mic1In*/
	CONTROL_PARAM_VIP_SOURCE               = 1,
	/* 0: क्रमce HDA, 1: allow DSP अगर HDA Spdअगर1Out stream is idle */
	CONTROL_PARAM_SPDIF1_SOURCE            = 2,
	/* Port A output stage gain setting to use when 16 Ohm output
	 * impedance is selected*/
	CONTROL_PARAM_PORTA_160OHM_GAIN        = 8,
	/* Port D output stage gain setting to use when 16 Ohm output
	 * impedance is selected*/
	CONTROL_PARAM_PORTD_160OHM_GAIN        = 10,

	/*
	 * This control param name was found in the 8051 memory, and makes
	 * sense given the fact the AE-5 uses it and has the ASI flag set.
	 */
	CONTROL_PARAM_ASI                      = 23,

	/* Stream Control */

	/* Select stream with the given ID */
	CONTROL_PARAM_STREAM_ID                = 24,
	/* Source connection poपूर्णांक क्रम the selected stream */
	CONTROL_PARAM_STREAM_SOURCE_CONN_POINT = 25,
	/* Destination connection poपूर्णांक क्रम the selected stream */
	CONTROL_PARAM_STREAM_DEST_CONN_POINT   = 26,
	/* Number of audio channels in the selected stream */
	CONTROL_PARAM_STREAMS_CHANNELS         = 27,
	/*Enable control क्रम the selected stream */
	CONTROL_PARAM_STREAM_CONTROL           = 28,

	/* Connection Poपूर्णांक Control */

	/* Select connection poपूर्णांक with the given ID */
	CONTROL_PARAM_CONN_POINT_ID            = 29,
	/* Connection poपूर्णांक sample rate */
	CONTROL_PARAM_CONN_POINT_SAMPLE_RATE   = 30,

	/* Node Control */

	/* Select HDA node with the given ID */
	CONTROL_PARAM_NODE_ID                  = 31
पूर्ण;

/*
 *  Dsp Io Status codes
 */
क्रमागत hda_venकरोr_status_dspio अणु
	/* Success */
	VENDOR_STATUS_DSPIO_OK                       = 0x00,
	/* Busy, unable to accept new command, the host must retry */
	VENDOR_STATUS_DSPIO_BUSY                     = 0x01,
	/* SCP command queue is full */
	VENDOR_STATUS_DSPIO_SCP_COMMAND_QUEUE_FULL   = 0x02,
	/* SCP response queue is empty */
	VENDOR_STATUS_DSPIO_SCP_RESPONSE_QUEUE_EMPTY = 0x03
पूर्ण;

/*
 *  Chip Io Status codes
 */
क्रमागत hda_venकरोr_status_chipio अणु
	/* Success */
	VENDOR_STATUS_CHIPIO_OK   = 0x00,
	/* Busy, unable to accept new command, the host must retry */
	VENDOR_STATUS_CHIPIO_BUSY = 0x01
पूर्ण;

/*
 *  CA0132 sample rate
 */
क्रमागत ca0132_sample_rate अणु
	SR_6_000        = 0x00,
	SR_8_000        = 0x01,
	SR_9_600        = 0x02,
	SR_11_025       = 0x03,
	SR_16_000       = 0x04,
	SR_22_050       = 0x05,
	SR_24_000       = 0x06,
	SR_32_000       = 0x07,
	SR_44_100       = 0x08,
	SR_48_000       = 0x09,
	SR_88_200       = 0x0A,
	SR_96_000       = 0x0B,
	SR_144_000      = 0x0C,
	SR_176_400      = 0x0D,
	SR_192_000      = 0x0E,
	SR_384_000      = 0x0F,

	SR_COUNT        = 0x10,

	SR_RATE_UNKNOWN = 0x1F
पूर्ण;

क्रमागत dsp_करोwnload_state अणु
	DSP_DOWNLOAD_FAILED = -1,
	DSP_DOWNLOAD_INIT   = 0,
	DSP_DOWNLOADING     = 1,
	DSP_DOWNLOADED      = 2
पूर्ण;

/* retrieve parameters from hda क्रमmat */
#घोषणा get_hdafmt_chs(fmt)	(fmt & 0xf)
#घोषणा get_hdafmt_bits(fmt)	((fmt >> 4) & 0x7)
#घोषणा get_hdafmt_rate(fmt)	((fmt >> 8) & 0x7f)
#घोषणा get_hdafmt_type(fmt)	((fmt >> 15) & 0x1)

/*
 * CA0132 specअगरic
 */

काष्ठा ca0132_spec अणु
	स्थिर काष्ठा snd_kcontrol_new *mixers[5];
	अचिन्हित पूर्णांक num_mixers;
	स्थिर काष्ठा hda_verb *base_init_verbs;
	स्थिर काष्ठा hda_verb *base_निकास_verbs;
	स्थिर काष्ठा hda_verb *chip_init_verbs;
	स्थिर काष्ठा hda_verb *desktop_init_verbs;
	काष्ठा hda_verb *spec_init_verbs;
	काष्ठा स्वतः_pin_cfg स्वतःcfg;

	/* Nodes configurations */
	काष्ठा hda_multi_out multiout;
	hda_nid_t out_pins[AUTO_CFG_MAX_OUTS];
	hda_nid_t dacs[AUTO_CFG_MAX_OUTS];
	अचिन्हित पूर्णांक num_outमाला_दो;
	hda_nid_t input_pins[AUTO_PIN_LAST];
	hda_nid_t adcs[AUTO_PIN_LAST];
	hda_nid_t dig_out;
	hda_nid_t dig_in;
	अचिन्हित पूर्णांक num_inमाला_दो;
	hda_nid_t shared_mic_nid;
	hda_nid_t shared_out_nid;
	hda_nid_t unsol_tag_hp;
	hda_nid_t unsol_tag_front_hp; /* क्रम desktop ca0132 codecs */
	hda_nid_t unsol_tag_amic1;

	/* chip access */
	काष्ठा mutex chipio_mutex; /* chip access mutex */
	u32 curr_chip_addx;

	/* DSP करोwnload related */
	क्रमागत dsp_करोwnload_state dsp_state;
	अचिन्हित पूर्णांक dsp_stream_id;
	अचिन्हित पूर्णांक रुको_scp;
	अचिन्हित पूर्णांक रुको_scp_header;
	अचिन्हित पूर्णांक रुको_num_data;
	अचिन्हित पूर्णांक scp_resp_header;
	अचिन्हित पूर्णांक scp_resp_data[4];
	अचिन्हित पूर्णांक scp_resp_count;
	bool startup_check_entered;
	bool dsp_reload;

	/* mixer and effects related */
	अचिन्हित अक्षर dmic_ctl;
	पूर्णांक cur_out_type;
	पूर्णांक cur_mic_type;
	दीर्घ vnode_lvol[VNODES_COUNT];
	दीर्घ vnode_rvol[VNODES_COUNT];
	दीर्घ vnode_lचयन[VNODES_COUNT];
	दीर्घ vnode_rचयन[VNODES_COUNT];
	दीर्घ effects_चयन[EFFECTS_COUNT];
	दीर्घ voicefx_val;
	दीर्घ cur_mic_boost;
	/* ca0132_alt control related values */
	अचिन्हित अक्षर in_क्रमागत_val;
	अचिन्हित अक्षर out_क्रमागत_val;
	अचिन्हित अक्षर channel_cfg_val;
	अचिन्हित अक्षर speaker_range_val[2];
	अचिन्हित अक्षर mic_boost_क्रमागत_val;
	अचिन्हित अक्षर smart_volume_setting;
	अचिन्हित अक्षर bass_redirection_val;
	दीर्घ bass_redirect_xover_freq;
	दीर्घ fx_ctl_val[EFFECT_LEVEL_SLIDERS];
	दीर्घ xbass_xover_freq;
	दीर्घ eq_preset_val;
	अचिन्हित पूर्णांक tlv[4];
	काष्ठा hda_vmaster_mute_hook vmaster_mute;
	/* AE-5 Control values */
	अचिन्हित अक्षर ae5_headphone_gain_val;
	अचिन्हित अक्षर ae5_filter_val;
	/* ZxR Control Values */
	अचिन्हित अक्षर zxr_gain_set;

	काष्ठा hda_codec *codec;
	काष्ठा delayed_work unsol_hp_work;
	पूर्णांक quirk;

#अगर_घोषित ENABLE_TUNING_CONTROLS
	दीर्घ cur_ctl_vals[TUNING_CTLS_COUNT];
#पूर्ण_अगर
	/*
	 * The Recon3D, Sound Blaster Z, Sound Blaster ZxR, and Sound Blaster
	 * AE-5 all use PCI region 2 to toggle GPIO and other currently unknown
	 * things.
	 */
	bool use_pci_mmio;
	व्योम __iomem *mem_base;

	/*
	 * Whether or not to use the alt functions like alt_select_out,
	 * alt_select_in, etc. Only used on desktop codecs क्रम now, because of
	 * surround sound support.
	 */
	bool use_alt_functions;

	/*
	 * Whether or not to use alt controls:	volume effect sliders, EQ
	 * presets, smart volume presets, and new control names with FX prefix.
	 * Renames PlayEnhancement and CrystalVoice too.
	 */
	bool use_alt_controls;
पूर्ण;

/*
 * CA0132 quirks table
 */
क्रमागत अणु
	QUIRK_NONE,
	QUIRK_ALIENWARE,
	QUIRK_ALIENWARE_M17XR4,
	QUIRK_SBZ,
	QUIRK_ZXR,
	QUIRK_ZXR_DBPRO,
	QUIRK_R3DI,
	QUIRK_R3D,
	QUIRK_AE5,
	QUIRK_AE7,
पूर्ण;

#अगर_घोषित CONFIG_PCI
#घोषणा ca0132_quirk(spec)		((spec)->quirk)
#घोषणा ca0132_use_pci_mmio(spec)	((spec)->use_pci_mmio)
#घोषणा ca0132_use_alt_functions(spec)	((spec)->use_alt_functions)
#घोषणा ca0132_use_alt_controls(spec)	((spec)->use_alt_controls)
#अन्यथा
#घोषणा ca0132_quirk(spec)		(अणु (व्योम)(spec); QUIRK_NONE; पूर्ण)
#घोषणा ca0132_use_alt_functions(spec)	(अणु (व्योम)(spec); false; पूर्ण)
#घोषणा ca0132_use_pci_mmio(spec)	(अणु (व्योम)(spec); false; पूर्ण)
#घोषणा ca0132_use_alt_controls(spec)	(अणु (व्योम)(spec); false; पूर्ण)
#पूर्ण_अगर

अटल स्थिर काष्ठा hda_pपूर्णांकbl alienware_pincfgs[] = अणु
	अणु 0x0b, 0x90170110 पूर्ण, /* Builtin Speaker */
	अणु 0x0c, 0x411111f0 पूर्ण, /* N/A */
	अणु 0x0d, 0x411111f0 पूर्ण, /* N/A */
	अणु 0x0e, 0x411111f0 पूर्ण, /* N/A */
	अणु 0x0f, 0x0321101f पूर्ण, /* HP */
	अणु 0x10, 0x411111f0 पूर्ण, /* Headset?  disabled क्रम now */
	अणु 0x11, 0x03a11021 पूर्ण, /* Mic */
	अणु 0x12, 0xd5a30140 पूर्ण, /* Builtin Mic */
	अणु 0x13, 0x411111f0 पूर्ण, /* N/A */
	अणु 0x18, 0x411111f0 पूर्ण, /* N/A */
	अणुपूर्ण
पूर्ण;

/* Sound Blaster Z pin configs taken from Winकरोws Driver */
अटल स्थिर काष्ठा hda_pपूर्णांकbl sbz_pincfgs[] = अणु
	अणु 0x0b, 0x01017010 पूर्ण, /* Port G -- Lineout FRONT L/R */
	अणु 0x0c, 0x014510f0 पूर्ण, /* SPDIF Out 1 */
	अणु 0x0d, 0x014510f0 पूर्ण, /* Digital Out */
	अणु 0x0e, 0x01c510f0 पूर्ण, /* SPDIF In */
	अणु 0x0f, 0x0221701f पूर्ण, /* Port A -- BackPanel HP */
	अणु 0x10, 0x01017012 पूर्ण, /* Port D -- Center/LFE or FP Hp */
	अणु 0x11, 0x01017014 पूर्ण, /* Port B -- LineMicIn2 / Rear L/R */
	अणु 0x12, 0x01a170f0 पूर्ण, /* Port C -- LineIn1 */
	अणु 0x13, 0x908700f0 पूर्ण, /* What U Hear In*/
	अणु 0x18, 0x50d000f0 पूर्ण, /* N/A */
	अणुपूर्ण
पूर्ण;

/* Sound Blaster ZxR pin configs taken from Winकरोws Driver */
अटल स्थिर काष्ठा hda_pपूर्णांकbl zxr_pincfgs[] = अणु
	अणु 0x0b, 0x01047110 पूर्ण, /* Port G -- Lineout FRONT L/R */
	अणु 0x0c, 0x414510f0 पूर्ण, /* SPDIF Out 1 - Disabled*/
	अणु 0x0d, 0x014510f0 पूर्ण, /* Digital Out */
	अणु 0x0e, 0x41c520f0 पूर्ण, /* SPDIF In - Disabled*/
	अणु 0x0f, 0x0122711f पूर्ण, /* Port A -- BackPanel HP */
	अणु 0x10, 0x01017111 पूर्ण, /* Port D -- Center/LFE */
	अणु 0x11, 0x01017114 पूर्ण, /* Port B -- LineMicIn2 / Rear L/R */
	अणु 0x12, 0x01a271f0 पूर्ण, /* Port C -- LineIn1 */
	अणु 0x13, 0x908700f0 पूर्ण, /* What U Hear In*/
	अणु 0x18, 0x50d000f0 पूर्ण, /* N/A */
	अणुपूर्ण
पूर्ण;

/* Recon3D pin configs taken from Winकरोws Driver */
अटल स्थिर काष्ठा hda_pपूर्णांकbl r3d_pincfgs[] = अणु
	अणु 0x0b, 0x01014110 पूर्ण, /* Port G -- Lineout FRONT L/R */
	अणु 0x0c, 0x014510f0 पूर्ण, /* SPDIF Out 1 */
	अणु 0x0d, 0x014510f0 पूर्ण, /* Digital Out */
	अणु 0x0e, 0x01c520f0 पूर्ण, /* SPDIF In */
	अणु 0x0f, 0x0221401f पूर्ण, /* Port A -- BackPanel HP */
	अणु 0x10, 0x01016011 पूर्ण, /* Port D -- Center/LFE or FP Hp */
	अणु 0x11, 0x01011014 पूर्ण, /* Port B -- LineMicIn2 / Rear L/R */
	अणु 0x12, 0x02a090f0 पूर्ण, /* Port C -- LineIn1 */
	अणु 0x13, 0x908700f0 पूर्ण, /* What U Hear In*/
	अणु 0x18, 0x50d000f0 पूर्ण, /* N/A */
	अणुपूर्ण
पूर्ण;

/* Sound Blaster AE-5 pin configs taken from Winकरोws Driver */
अटल स्थिर काष्ठा hda_pपूर्णांकbl ae5_pincfgs[] = अणु
	अणु 0x0b, 0x01017010 पूर्ण, /* Port G -- Lineout FRONT L/R */
	अणु 0x0c, 0x014510f0 पूर्ण, /* SPDIF Out 1 */
	अणु 0x0d, 0x014510f0 पूर्ण, /* Digital Out */
	अणु 0x0e, 0x01c510f0 पूर्ण, /* SPDIF In */
	अणु 0x0f, 0x01017114 पूर्ण, /* Port A -- Rear L/R. */
	अणु 0x10, 0x01017012 पूर्ण, /* Port D -- Center/LFE or FP Hp */
	अणु 0x11, 0x012170ff पूर्ण, /* Port B -- LineMicIn2 / Rear Headphone */
	अणु 0x12, 0x01a170f0 पूर्ण, /* Port C -- LineIn1 */
	अणु 0x13, 0x908700f0 पूर्ण, /* What U Hear In*/
	अणु 0x18, 0x50d000f0 पूर्ण, /* N/A */
	अणुपूर्ण
पूर्ण;

/* Recon3D पूर्णांकegrated pin configs taken from Winकरोws Driver */
अटल स्थिर काष्ठा hda_pपूर्णांकbl r3di_pincfgs[] = अणु
	अणु 0x0b, 0x01014110 पूर्ण, /* Port G -- Lineout FRONT L/R */
	अणु 0x0c, 0x014510f0 पूर्ण, /* SPDIF Out 1 */
	अणु 0x0d, 0x014510f0 पूर्ण, /* Digital Out */
	अणु 0x0e, 0x41c520f0 पूर्ण, /* SPDIF In */
	अणु 0x0f, 0x0221401f पूर्ण, /* Port A -- BackPanel HP */
	अणु 0x10, 0x01016011 पूर्ण, /* Port D -- Center/LFE or FP Hp */
	अणु 0x11, 0x01011014 पूर्ण, /* Port B -- LineMicIn2 / Rear L/R */
	अणु 0x12, 0x02a090f0 पूर्ण, /* Port C -- LineIn1 */
	अणु 0x13, 0x908700f0 पूर्ण, /* What U Hear In*/
	अणु 0x18, 0x500000f0 पूर्ण, /* N/A */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl ae7_pincfgs[] = अणु
	अणु 0x0b, 0x01017010 पूर्ण,
	अणु 0x0c, 0x014510f0 पूर्ण,
	अणु 0x0d, 0x414510f0 पूर्ण,
	अणु 0x0e, 0x01c520f0 पूर्ण,
	अणु 0x0f, 0x01017114 पूर्ण,
	अणु 0x10, 0x01017011 पूर्ण,
	अणु 0x11, 0x018170ff पूर्ण,
	अणु 0x12, 0x01a170f0 पूर्ण,
	अणु 0x13, 0x908700f0 पूर्ण,
	अणु 0x18, 0x500000f0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk ca0132_quirks[] = अणु
	SND_PCI_QUIRK(0x1028, 0x057b, "Alienware M17x R4", QUIRK_ALIENWARE_M17XR4),
	SND_PCI_QUIRK(0x1028, 0x0685, "Alienware 15 2015", QUIRK_ALIENWARE),
	SND_PCI_QUIRK(0x1028, 0x0688, "Alienware 17 2015", QUIRK_ALIENWARE),
	SND_PCI_QUIRK(0x1028, 0x0708, "Alienware 15 R2 2016", QUIRK_ALIENWARE),
	SND_PCI_QUIRK(0x1102, 0x0010, "Sound Blaster Z", QUIRK_SBZ),
	SND_PCI_QUIRK(0x1102, 0x0023, "Sound Blaster Z", QUIRK_SBZ),
	SND_PCI_QUIRK(0x1102, 0x0027, "Sound Blaster Z", QUIRK_SBZ),
	SND_PCI_QUIRK(0x1102, 0x0033, "Sound Blaster ZxR", QUIRK_SBZ),
	SND_PCI_QUIRK(0x1458, 0xA016, "Recon3Di", QUIRK_R3DI),
	SND_PCI_QUIRK(0x1458, 0xA026, "Gigabyte G1.Sniper Z97", QUIRK_R3DI),
	SND_PCI_QUIRK(0x1458, 0xA036, "Gigabyte GA-Z170X-Gaming 7", QUIRK_R3DI),
	SND_PCI_QUIRK(0x3842, 0x1038, "EVGA X99 Classified", QUIRK_R3DI),
	SND_PCI_QUIRK(0x1102, 0x0013, "Recon3D", QUIRK_R3D),
	SND_PCI_QUIRK(0x1102, 0x0018, "Recon3D", QUIRK_R3D),
	SND_PCI_QUIRK(0x1102, 0x0051, "Sound Blaster AE-5", QUIRK_AE5),
	SND_PCI_QUIRK(0x1102, 0x0191, "Sound Blaster AE-5 Plus", QUIRK_AE5),
	SND_PCI_QUIRK(0x1102, 0x0081, "Sound Blaster AE-7", QUIRK_AE7),
	अणुपूर्ण
पूर्ण;

/* Output selection quirk info काष्ठाures. */
#घोषणा MAX_QUIRK_MMIO_GPIO_SET_VALS 3
#घोषणा MAX_QUIRK_SCP_SET_VALS 2
काष्ठा ca0132_alt_out_set_info अणु
	अचिन्हित पूर्णांक dac2port; /* ParamID 0x0d value. */

	bool has_hda_gpio;
	अक्षर hda_gpio_pin;
	अक्षर hda_gpio_set;

	अचिन्हित पूर्णांक mmio_gpio_count;
	अक्षर mmio_gpio_pin[MAX_QUIRK_MMIO_GPIO_SET_VALS];
	अक्षर mmio_gpio_set[MAX_QUIRK_MMIO_GPIO_SET_VALS];

	अचिन्हित पूर्णांक scp_cmds_count;
	अचिन्हित पूर्णांक scp_cmd_mid[MAX_QUIRK_SCP_SET_VALS];
	अचिन्हित पूर्णांक scp_cmd_req[MAX_QUIRK_SCP_SET_VALS];
	अचिन्हित पूर्णांक scp_cmd_val[MAX_QUIRK_SCP_SET_VALS];

	bool has_chipio_ग_लिखो;
	अचिन्हित पूर्णांक chipio_ग_लिखो_addr;
	अचिन्हित पूर्णांक chipio_ग_लिखो_data;
पूर्ण;

काष्ठा ca0132_alt_out_set_quirk_data अणु
	पूर्णांक quirk_id;

	bool has_headphone_gain;
	bool is_ae_series;

	काष्ठा ca0132_alt_out_set_info out_set_info[NUM_OF_OUTPUTS];
पूर्ण;

अटल स्थिर काष्ठा ca0132_alt_out_set_quirk_data quirk_out_set_data[] = अणु
	अणु .quirk_id = QUIRK_R3DI,
	  .has_headphone_gain = false,
	  .is_ae_series       = false,
	  .out_set_info = अणु
		/* Speakers. */
		अणु .dac2port         = 0x24,
		  .has_hda_gpio     = true,
		  .hda_gpio_pin     = 2,
		  .hda_gpio_set     = 1,
		  .mmio_gpio_count  = 0,
		  .scp_cmds_count   = 0,
		  .has_chipio_ग_लिखो = false,
		पूर्ण,
		/* Headphones. */
		अणु .dac2port         = 0x21,
		  .has_hda_gpio     = true,
		  .hda_gpio_pin     = 2,
		  .hda_gpio_set     = 0,
		  .mmio_gpio_count  = 0,
		  .scp_cmds_count   = 0,
		  .has_chipio_ग_लिखो = false,
		पूर्ण पूर्ण,
	पूर्ण,
	अणु .quirk_id = QUIRK_R3D,
	  .has_headphone_gain = false,
	  .is_ae_series       = false,
	  .out_set_info = अणु
		/* Speakers. */
		अणु .dac2port         = 0x24,
		  .has_hda_gpio     = false,
		  .mmio_gpio_count  = 1,
		  .mmio_gpio_pin    = अणु 1 पूर्ण,
		  .mmio_gpio_set    = अणु 1 पूर्ण,
		  .scp_cmds_count   = 0,
		  .has_chipio_ग_लिखो = false,
		पूर्ण,
		/* Headphones. */
		अणु .dac2port         = 0x21,
		  .has_hda_gpio     = false,
		  .mmio_gpio_count  = 1,
		  .mmio_gpio_pin    = अणु 1 पूर्ण,
		  .mmio_gpio_set    = अणु 0 पूर्ण,
		  .scp_cmds_count   = 0,
		  .has_chipio_ग_लिखो = false,
		पूर्ण पूर्ण,
	पूर्ण,
	अणु .quirk_id = QUIRK_SBZ,
	  .has_headphone_gain = false,
	  .is_ae_series       = false,
	  .out_set_info = अणु
		/* Speakers. */
		अणु .dac2port         = 0x18,
		  .has_hda_gpio     = false,
		  .mmio_gpio_count  = 3,
		  .mmio_gpio_pin    = अणु 7, 4, 1 पूर्ण,
		  .mmio_gpio_set    = अणु 0, 1, 1 पूर्ण,
		  .scp_cmds_count   = 0,
		  .has_chipio_ग_लिखो = false, पूर्ण,
		/* Headphones. */
		अणु .dac2port         = 0x12,
		  .has_hda_gpio     = false,
		  .mmio_gpio_count  = 3,
		  .mmio_gpio_pin    = अणु 7, 4, 1 पूर्ण,
		  .mmio_gpio_set    = अणु 1, 1, 0 पूर्ण,
		  .scp_cmds_count   = 0,
		  .has_chipio_ग_लिखो = false,
		पूर्ण पूर्ण,
	पूर्ण,
	अणु .quirk_id = QUIRK_ZXR,
	  .has_headphone_gain = true,
	  .is_ae_series       = false,
	  .out_set_info = अणु
		/* Speakers. */
		अणु .dac2port         = 0x24,
		  .has_hda_gpio     = false,
		  .mmio_gpio_count  = 3,
		  .mmio_gpio_pin    = अणु 2, 3, 5 पूर्ण,
		  .mmio_gpio_set    = अणु 1, 1, 0 पूर्ण,
		  .scp_cmds_count   = 0,
		  .has_chipio_ग_लिखो = false,
		पूर्ण,
		/* Headphones. */
		अणु .dac2port         = 0x21,
		  .has_hda_gpio     = false,
		  .mmio_gpio_count  = 3,
		  .mmio_gpio_pin    = अणु 2, 3, 5 पूर्ण,
		  .mmio_gpio_set    = अणु 0, 1, 1 पूर्ण,
		  .scp_cmds_count   = 0,
		  .has_chipio_ग_लिखो = false,
		पूर्ण पूर्ण,
	पूर्ण,
	अणु .quirk_id = QUIRK_AE5,
	  .has_headphone_gain = true,
	  .is_ae_series       = true,
	  .out_set_info = अणु
		/* Speakers. */
		अणु .dac2port          = 0xa4,
		  .has_hda_gpio      = false,
		  .mmio_gpio_count   = 0,
		  .scp_cmds_count    = 2,
		  .scp_cmd_mid       = अणु 0x96, 0x96 पूर्ण,
		  .scp_cmd_req       = अणु SPEAKER_TUNING_FRONT_LEFT_INVERT,
					 SPEAKER_TUNING_FRONT_RIGHT_INVERT पूर्ण,
		  .scp_cmd_val       = अणु FLOAT_ZERO, FLOAT_ZERO पूर्ण,
		  .has_chipio_ग_लिखो  = true,
		  .chipio_ग_लिखो_addr = 0x0018b03c,
		  .chipio_ग_लिखो_data = 0x00000012
		पूर्ण,
		/* Headphones. */
		अणु .dac2port          = 0xa1,
		  .has_hda_gpio      = false,
		  .mmio_gpio_count   = 0,
		  .scp_cmds_count    = 2,
		  .scp_cmd_mid       = अणु 0x96, 0x96 पूर्ण,
		  .scp_cmd_req       = अणु SPEAKER_TUNING_FRONT_LEFT_INVERT,
					 SPEAKER_TUNING_FRONT_RIGHT_INVERT पूर्ण,
		  .scp_cmd_val       = अणु FLOAT_ONE, FLOAT_ONE पूर्ण,
		  .has_chipio_ग_लिखो  = true,
		  .chipio_ग_लिखो_addr = 0x0018b03c,
		  .chipio_ग_लिखो_data = 0x00000012
		पूर्ण पूर्ण,
	पूर्ण,
	अणु .quirk_id = QUIRK_AE7,
	  .has_headphone_gain = true,
	  .is_ae_series       = true,
	  .out_set_info = अणु
		/* Speakers. */
		अणु .dac2port          = 0x58,
		  .has_hda_gpio      = false,
		  .mmio_gpio_count   = 1,
		  .mmio_gpio_pin     = अणु 0 पूर्ण,
		  .mmio_gpio_set     = अणु 1 पूर्ण,
		  .scp_cmds_count    = 2,
		  .scp_cmd_mid       = अणु 0x96, 0x96 पूर्ण,
		  .scp_cmd_req       = अणु SPEAKER_TUNING_FRONT_LEFT_INVERT,
					 SPEAKER_TUNING_FRONT_RIGHT_INVERT पूर्ण,
		  .scp_cmd_val       = अणु FLOAT_ZERO, FLOAT_ZERO पूर्ण,
		  .has_chipio_ग_लिखो  = true,
		  .chipio_ग_लिखो_addr = 0x0018b03c,
		  .chipio_ग_लिखो_data = 0x00000000
		पूर्ण,
		/* Headphones. */
		अणु .dac2port          = 0x58,
		  .has_hda_gpio      = false,
		  .mmio_gpio_count   = 1,
		  .mmio_gpio_pin     = अणु 0 पूर्ण,
		  .mmio_gpio_set     = अणु 1 पूर्ण,
		  .scp_cmds_count    = 2,
		  .scp_cmd_mid       = अणु 0x96, 0x96 पूर्ण,
		  .scp_cmd_req       = अणु SPEAKER_TUNING_FRONT_LEFT_INVERT,
					 SPEAKER_TUNING_FRONT_RIGHT_INVERT पूर्ण,
		  .scp_cmd_val       = अणु FLOAT_ONE, FLOAT_ONE पूर्ण,
		  .has_chipio_ग_लिखो  = true,
		  .chipio_ग_लिखो_addr = 0x0018b03c,
		  .chipio_ग_लिखो_data = 0x00000010
		पूर्ण पूर्ण,
	पूर्ण
पूर्ण;

/*
 * CA0132 codec access
 */
अटल अचिन्हित पूर्णांक codec_send_command(काष्ठा hda_codec *codec, hda_nid_t nid,
		अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक parm, अचिन्हित पूर्णांक *res)
अणु
	अचिन्हित पूर्णांक response;
	response = snd_hda_codec_पढ़ो(codec, nid, 0, verb, parm);
	*res = response;

	वापस ((response == -1) ? -1 : 0);
पूर्ण

अटल पूर्णांक codec_set_converter_क्रमmat(काष्ठा hda_codec *codec, hda_nid_t nid,
		अचिन्हित लघु converter_क्रमmat, अचिन्हित पूर्णांक *res)
अणु
	वापस codec_send_command(codec, nid, VENDOR_CHIPIO_STREAM_FORMAT,
				converter_क्रमmat & 0xffff, res);
पूर्ण

अटल पूर्णांक codec_set_converter_stream_channel(काष्ठा hda_codec *codec,
				hda_nid_t nid, अचिन्हित अक्षर stream,
				अचिन्हित अक्षर channel, अचिन्हित पूर्णांक *res)
अणु
	अचिन्हित अक्षर converter_stream_channel = 0;

	converter_stream_channel = (stream << 4) | (channel & 0x0f);
	वापस codec_send_command(codec, nid, AC_VERB_SET_CHANNEL_STREAMID,
				converter_stream_channel, res);
पूर्ण

/* Chip access helper function */
अटल पूर्णांक chipio_send(काष्ठा hda_codec *codec,
		       अचिन्हित पूर्णांक reg,
		       अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक res;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);

	/* send bits of data specअगरied by reg */
	करो अणु
		res = snd_hda_codec_पढ़ो(codec, WIDGET_CHIP_CTRL, 0,
					 reg, data);
		अगर (res == VENDOR_STATUS_CHIPIO_OK)
			वापस 0;
		msleep(20);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	वापस -EIO;
पूर्ण

/*
 * Write chip address through the venकरोr widget -- NOT रक्षित by the Mutex!
 */
अटल पूर्णांक chipio_ग_लिखो_address(काष्ठा hda_codec *codec,
				अचिन्हित पूर्णांक chip_addx)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक res;

	अगर (spec->curr_chip_addx == chip_addx)
			वापस 0;

	/* send low 16 bits of the address */
	res = chipio_send(codec, VENDOR_CHIPIO_ADDRESS_LOW,
			  chip_addx & 0xffff);

	अगर (res != -EIO) अणु
		/* send high 16 bits of the address */
		res = chipio_send(codec, VENDOR_CHIPIO_ADDRESS_HIGH,
				  chip_addx >> 16);
	पूर्ण

	spec->curr_chip_addx = (res < 0) ? ~0U : chip_addx;

	वापस res;
पूर्ण

/*
 * Write data through the venकरोr widget -- NOT रक्षित by the Mutex!
 */
अटल पूर्णांक chipio_ग_लिखो_data(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक data)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक res;

	/* send low 16 bits of the data */
	res = chipio_send(codec, VENDOR_CHIPIO_DATA_LOW, data & 0xffff);

	अगर (res != -EIO) अणु
		/* send high 16 bits of the data */
		res = chipio_send(codec, VENDOR_CHIPIO_DATA_HIGH,
				  data >> 16);
	पूर्ण

	/*If no error encountered, स्वतःmatically increment the address
	as per chip behaviour*/
	spec->curr_chip_addx = (res != -EIO) ?
					(spec->curr_chip_addx + 4) : ~0U;
	वापस res;
पूर्ण

/*
 * Write multiple data through the venकरोr widget -- NOT रक्षित by the Mutex!
 */
अटल पूर्णांक chipio_ग_लिखो_data_multiple(काष्ठा hda_codec *codec,
				      स्थिर u32 *data,
				      अचिन्हित पूर्णांक count)
अणु
	पूर्णांक status = 0;

	अगर (data == शून्य) अणु
		codec_dbg(codec, "chipio_write_data null ptr\n");
		वापस -EINVAL;
	पूर्ण

	जबतक ((count-- != 0) && (status == 0))
		status = chipio_ग_लिखो_data(codec, *data++);

	वापस status;
पूर्ण


/*
 * Read data through the venकरोr widget -- NOT रक्षित by the Mutex!
 */
अटल पूर्णांक chipio_पढ़ो_data(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक res;

	/* post पढ़ो */
	res = chipio_send(codec, VENDOR_CHIPIO_HIC_POST_READ, 0);

	अगर (res != -EIO) अणु
		/* पढ़ो status */
		res = chipio_send(codec, VENDOR_CHIPIO_STATUS, 0);
	पूर्ण

	अगर (res != -EIO) अणु
		/* पढ़ो data */
		*data = snd_hda_codec_पढ़ो(codec, WIDGET_CHIP_CTRL, 0,
					   VENDOR_CHIPIO_HIC_READ_DATA,
					   0);
	पूर्ण

	/*If no error encountered, स्वतःmatically increment the address
	as per chip behaviour*/
	spec->curr_chip_addx = (res != -EIO) ?
					(spec->curr_chip_addx + 4) : ~0U;
	वापस res;
पूर्ण

/*
 * Write given value to the given address through the chip I/O widget.
 * रक्षित by the Mutex
 */
अटल पूर्णांक chipio_ग_लिखो(काष्ठा hda_codec *codec,
		अचिन्हित पूर्णांक chip_addx, स्थिर अचिन्हित पूर्णांक data)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक err;

	mutex_lock(&spec->chipio_mutex);

	/* ग_लिखो the address, and अगर successful proceed to ग_लिखो data */
	err = chipio_ग_लिखो_address(codec, chip_addx);
	अगर (err < 0)
		जाओ निकास;

	err = chipio_ग_लिखो_data(codec, data);
	अगर (err < 0)
		जाओ निकास;

निकास:
	mutex_unlock(&spec->chipio_mutex);
	वापस err;
पूर्ण

/*
 * Write given value to the given address through the chip I/O widget.
 * not रक्षित by the Mutex
 */
अटल पूर्णांक chipio_ग_लिखो_no_mutex(काष्ठा hda_codec *codec,
		अचिन्हित पूर्णांक chip_addx, स्थिर अचिन्हित पूर्णांक data)
अणु
	पूर्णांक err;


	/* ग_लिखो the address, and अगर successful proceed to ग_लिखो data */
	err = chipio_ग_लिखो_address(codec, chip_addx);
	अगर (err < 0)
		जाओ निकास;

	err = chipio_ग_लिखो_data(codec, data);
	अगर (err < 0)
		जाओ निकास;

निकास:
	वापस err;
पूर्ण

/*
 * Write multiple values to the given address through the chip I/O widget.
 * रक्षित by the Mutex
 */
अटल पूर्णांक chipio_ग_लिखो_multiple(काष्ठा hda_codec *codec,
				 u32 chip_addx,
				 स्थिर u32 *data,
				 अचिन्हित पूर्णांक count)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक status;

	mutex_lock(&spec->chipio_mutex);
	status = chipio_ग_लिखो_address(codec, chip_addx);
	अगर (status < 0)
		जाओ error;

	status = chipio_ग_लिखो_data_multiple(codec, data, count);
error:
	mutex_unlock(&spec->chipio_mutex);

	वापस status;
पूर्ण

/*
 * Read the given address through the chip I/O widget
 * रक्षित by the Mutex
 */
अटल पूर्णांक chipio_पढ़ो(काष्ठा hda_codec *codec,
		अचिन्हित पूर्णांक chip_addx, अचिन्हित पूर्णांक *data)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक err;

	mutex_lock(&spec->chipio_mutex);

	/* ग_लिखो the address, and अगर successful proceed to ग_लिखो data */
	err = chipio_ग_लिखो_address(codec, chip_addx);
	अगर (err < 0)
		जाओ निकास;

	err = chipio_पढ़ो_data(codec, data);
	अगर (err < 0)
		जाओ निकास;

निकास:
	mutex_unlock(&spec->chipio_mutex);
	वापस err;
पूर्ण

/*
 * Set chip control flags through the chip I/O widget.
 */
अटल व्योम chipio_set_control_flag(काष्ठा hda_codec *codec,
				    क्रमागत control_flag_id flag_id,
				    bool flag_state)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक flag_bit;

	flag_bit = (flag_state ? 1 : 0);
	val = (flag_bit << 7) | (flag_id);
	snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_FLAG_SET, val);
पूर्ण

/*
 * Set chip parameters through the chip I/O widget.
 */
अटल व्योम chipio_set_control_param(काष्ठा hda_codec *codec,
		क्रमागत control_param_id param_id, पूर्णांक param_val)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक val;

	अगर ((param_id < 32) && (param_val < 8)) अणु
		val = (param_val << 5) | (param_id);
		snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
				    VENDOR_CHIPIO_PARAM_SET, val);
	पूर्ण अन्यथा अणु
		mutex_lock(&spec->chipio_mutex);
		अगर (chipio_send(codec, VENDOR_CHIPIO_STATUS, 0) == 0) अणु
			snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
					    VENDOR_CHIPIO_PARAM_EX_ID_SET,
					    param_id);
			snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
					    VENDOR_CHIPIO_PARAM_EX_VALUE_SET,
					    param_val);
		पूर्ण
		mutex_unlock(&spec->chipio_mutex);
	पूर्ण
पूर्ण

/*
 * Set chip parameters through the chip I/O widget. NO MUTEX.
 */
अटल व्योम chipio_set_control_param_no_mutex(काष्ठा hda_codec *codec,
		क्रमागत control_param_id param_id, पूर्णांक param_val)
अणु
	पूर्णांक val;

	अगर ((param_id < 32) && (param_val < 8)) अणु
		val = (param_val << 5) | (param_id);
		snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
				    VENDOR_CHIPIO_PARAM_SET, val);
	पूर्ण अन्यथा अणु
		अगर (chipio_send(codec, VENDOR_CHIPIO_STATUS, 0) == 0) अणु
			snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
					    VENDOR_CHIPIO_PARAM_EX_ID_SET,
					    param_id);
			snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
					    VENDOR_CHIPIO_PARAM_EX_VALUE_SET,
					    param_val);
		पूर्ण
	पूर्ण
पूर्ण
/*
 * Connect stream to a source poपूर्णांक, and then connect
 * that source poपूर्णांक to a destination poपूर्णांक.
 */
अटल व्योम chipio_set_stream_source_dest(काष्ठा hda_codec *codec,
				पूर्णांक streamid, पूर्णांक source_poपूर्णांक, पूर्णांक dest_poपूर्णांक)
अणु
	chipio_set_control_param_no_mutex(codec,
			CONTROL_PARAM_STREAM_ID, streamid);
	chipio_set_control_param_no_mutex(codec,
			CONTROL_PARAM_STREAM_SOURCE_CONN_POINT, source_poपूर्णांक);
	chipio_set_control_param_no_mutex(codec,
			CONTROL_PARAM_STREAM_DEST_CONN_POINT, dest_poपूर्णांक);
पूर्ण

/*
 * Set number of channels in the selected stream.
 */
अटल व्योम chipio_set_stream_channels(काष्ठा hda_codec *codec,
				पूर्णांक streamid, अचिन्हित पूर्णांक channels)
अणु
	chipio_set_control_param_no_mutex(codec,
			CONTROL_PARAM_STREAM_ID, streamid);
	chipio_set_control_param_no_mutex(codec,
			CONTROL_PARAM_STREAMS_CHANNELS, channels);
पूर्ण

/*
 * Enable/Disable audio stream.
 */
अटल व्योम chipio_set_stream_control(काष्ठा hda_codec *codec,
				पूर्णांक streamid, पूर्णांक enable)
अणु
	chipio_set_control_param_no_mutex(codec,
			CONTROL_PARAM_STREAM_ID, streamid);
	chipio_set_control_param_no_mutex(codec,
			CONTROL_PARAM_STREAM_CONTROL, enable);
पूर्ण

/*
 * Get ChipIO audio stream's status.
 */
अटल व्योम chipio_get_stream_control(काष्ठा hda_codec *codec,
				पूर्णांक streamid, अचिन्हित पूर्णांक *enable)
अणु
	chipio_set_control_param_no_mutex(codec,
			CONTROL_PARAM_STREAM_ID, streamid);
	*enable = snd_hda_codec_पढ़ो(codec, WIDGET_CHIP_CTRL, 0,
			   VENDOR_CHIPIO_PARAM_GET,
			   CONTROL_PARAM_STREAM_CONTROL);
पूर्ण

/*
 * Set sampling rate of the connection poपूर्णांक. NO MUTEX.
 */
अटल व्योम chipio_set_conn_rate_no_mutex(काष्ठा hda_codec *codec,
				पूर्णांक connid, क्रमागत ca0132_sample_rate rate)
अणु
	chipio_set_control_param_no_mutex(codec,
			CONTROL_PARAM_CONN_POINT_ID, connid);
	chipio_set_control_param_no_mutex(codec,
			CONTROL_PARAM_CONN_POINT_SAMPLE_RATE, rate);
पूर्ण

/*
 * Set sampling rate of the connection poपूर्णांक.
 */
अटल व्योम chipio_set_conn_rate(काष्ठा hda_codec *codec,
				पूर्णांक connid, क्रमागत ca0132_sample_rate rate)
अणु
	chipio_set_control_param(codec, CONTROL_PARAM_CONN_POINT_ID, connid);
	chipio_set_control_param(codec, CONTROL_PARAM_CONN_POINT_SAMPLE_RATE,
				 rate);
पूर्ण

/*
 * Writes to the 8051's पूर्णांकernal address space directly instead of indirectly,
 * giving access to the special function रेजिस्टरs located at addresses
 * 0x80-0xFF.
 */
अटल व्योम chipio_8051_ग_लिखो_direct(काष्ठा hda_codec *codec,
		अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक verb;

	verb = VENDOR_CHIPIO_8051_WRITE_सूचीECT | data;
	snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0, verb, addr);
पूर्ण

/*
 * Writes to the 8051's exram, which has 16-bits of address space.
 * Data at addresses 0x2000-0x7fff is mirrored to 0x8000-0xdfff.
 * Data at 0x8000-0xdfff can also be used as program memory क्रम the 8051 by
 * setting the pmem bank selection SFR.
 * 0xe000-0xffff is always mapped as program memory, with only 0xf000-0xffff
 * being writable.
 */
अटल व्योम chipio_8051_set_address(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक addr)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	/* Lower 8-bits. */
	पंचांगp = addr & 0xff;
	snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_8051_ADDRESS_LOW, पंचांगp);

	/* Upper 8-bits. */
	पंचांगp = (addr >> 8) & 0xff;
	snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_8051_ADDRESS_HIGH, पंचांगp);
पूर्ण

अटल व्योम chipio_8051_set_data(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक data)
अणु
	/* 8-bits of data. */
	snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_8051_DATA_WRITE, data & 0xff);
पूर्ण

अटल अचिन्हित पूर्णांक chipio_8051_get_data(काष्ठा hda_codec *codec)
अणु
	वापस snd_hda_codec_पढ़ो(codec, WIDGET_CHIP_CTRL, 0,
				   VENDOR_CHIPIO_8051_DATA_READ, 0);
पूर्ण

/* PLL_PMU ग_लिखोs share the lower address रेजिस्टर of the 8051 exram ग_लिखोs. */
अटल व्योम chipio_8051_set_data_pll(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक data)
अणु
	/* 8-bits of data. */
	snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_PLL_PMU_WRITE, data & 0xff);
पूर्ण

अटल व्योम chipio_8051_ग_लिखो_exram(काष्ठा hda_codec *codec,
		अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक data)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	mutex_lock(&spec->chipio_mutex);

	chipio_8051_set_address(codec, addr);
	chipio_8051_set_data(codec, data);

	mutex_unlock(&spec->chipio_mutex);
पूर्ण

अटल व्योम chipio_8051_ग_लिखो_exram_no_mutex(काष्ठा hda_codec *codec,
		अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक data)
अणु
	chipio_8051_set_address(codec, addr);
	chipio_8051_set_data(codec, data);
पूर्ण

/* Readback data from the 8051's exram. No mutex. */
अटल व्योम chipio_8051_पढ़ो_exram(काष्ठा hda_codec *codec,
		अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक *data)
अणु
	chipio_8051_set_address(codec, addr);
	*data = chipio_8051_get_data(codec);
पूर्ण

अटल व्योम chipio_8051_ग_लिखो_pll_pmu(काष्ठा hda_codec *codec,
		अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक data)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	mutex_lock(&spec->chipio_mutex);

	chipio_8051_set_address(codec, addr & 0xff);
	chipio_8051_set_data_pll(codec, data);

	mutex_unlock(&spec->chipio_mutex);
पूर्ण

अटल व्योम chipio_8051_ग_लिखो_pll_pmu_no_mutex(काष्ठा hda_codec *codec,
		अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक data)
अणु
	chipio_8051_set_address(codec, addr & 0xff);
	chipio_8051_set_data_pll(codec, data);
पूर्ण

/*
 * Enable घड़ीs.
 */
अटल व्योम chipio_enable_घड़ीs(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	mutex_lock(&spec->chipio_mutex);

	chipio_8051_ग_लिखो_pll_pmu_no_mutex(codec, 0x00, 0xff);
	chipio_8051_ग_लिखो_pll_pmu_no_mutex(codec, 0x05, 0x0b);
	chipio_8051_ग_लिखो_pll_pmu_no_mutex(codec, 0x06, 0xff);

	mutex_unlock(&spec->chipio_mutex);
पूर्ण

/*
 * CA0132 DSP IO stuffs
 */
अटल पूर्णांक dspio_send(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक reg,
		      अचिन्हित पूर्णांक data)
अणु
	पूर्णांक res;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);

	/* send bits of data specअगरied by reg to dsp */
	करो अणु
		res = snd_hda_codec_पढ़ो(codec, WIDGET_DSP_CTRL, 0, reg, data);
		अगर ((res >= 0) && (res != VENDOR_STATUS_DSPIO_BUSY))
			वापस res;
		msleep(20);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	वापस -EIO;
पूर्ण

/*
 * Wait क्रम DSP to be पढ़ोy क्रम commands
 */
अटल व्योम dspio_ग_लिखो_रुको(काष्ठा hda_codec *codec)
अणु
	पूर्णांक status;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);

	करो अणु
		status = snd_hda_codec_पढ़ो(codec, WIDGET_DSP_CTRL, 0,
						VENDOR_DSPIO_STATUS, 0);
		अगर ((status == VENDOR_STATUS_DSPIO_OK) ||
		    (status == VENDOR_STATUS_DSPIO_SCP_RESPONSE_QUEUE_EMPTY))
			अवरोध;
		msleep(1);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));
पूर्ण

/*
 * Write SCP data to DSP
 */
अटल पूर्णांक dspio_ग_लिखो(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक scp_data)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक status;

	dspio_ग_लिखो_रुको(codec);

	mutex_lock(&spec->chipio_mutex);
	status = dspio_send(codec, VENDOR_DSPIO_SCP_WRITE_DATA_LOW,
			    scp_data & 0xffff);
	अगर (status < 0)
		जाओ error;

	status = dspio_send(codec, VENDOR_DSPIO_SCP_WRITE_DATA_HIGH,
				    scp_data >> 16);
	अगर (status < 0)
		जाओ error;

	/* OK, now check अगर the ग_लिखो itself has executed*/
	status = snd_hda_codec_पढ़ो(codec, WIDGET_DSP_CTRL, 0,
				    VENDOR_DSPIO_STATUS, 0);
error:
	mutex_unlock(&spec->chipio_mutex);

	वापस (status == VENDOR_STATUS_DSPIO_SCP_COMMAND_QUEUE_FULL) ?
			-EIO : 0;
पूर्ण

/*
 * Write multiple SCP data to DSP
 */
अटल पूर्णांक dspio_ग_लिखो_multiple(काष्ठा hda_codec *codec,
				अचिन्हित पूर्णांक *buffer, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक status = 0;
	अचिन्हित पूर्णांक count;

	अगर (buffer == शून्य)
		वापस -EINVAL;

	count = 0;
	जबतक (count < size) अणु
		status = dspio_ग_लिखो(codec, *buffer++);
		अगर (status != 0)
			अवरोध;
		count++;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक dspio_पढ़ो(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक status;

	status = dspio_send(codec, VENDOR_DSPIO_SCP_POST_READ_DATA, 0);
	अगर (status == -EIO)
		वापस status;

	status = dspio_send(codec, VENDOR_DSPIO_STATUS, 0);
	अगर (status == -EIO ||
	    status == VENDOR_STATUS_DSPIO_SCP_RESPONSE_QUEUE_EMPTY)
		वापस -EIO;

	*data = snd_hda_codec_पढ़ो(codec, WIDGET_DSP_CTRL, 0,
				   VENDOR_DSPIO_SCP_READ_DATA, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक dspio_पढ़ो_multiple(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक *buffer,
			       अचिन्हित पूर्णांक *buf_size, अचिन्हित पूर्णांक size_count)
अणु
	पूर्णांक status = 0;
	अचिन्हित पूर्णांक size = *buf_size;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक skip_count;
	अचिन्हित पूर्णांक dummy;

	अगर (buffer == शून्य)
		वापस -1;

	count = 0;
	जबतक (count < size && count < size_count) अणु
		status = dspio_पढ़ो(codec, buffer++);
		अगर (status != 0)
			अवरोध;
		count++;
	पूर्ण

	skip_count = count;
	अगर (status == 0) अणु
		जबतक (skip_count < size) अणु
			status = dspio_पढ़ो(codec, &dummy);
			अगर (status != 0)
				अवरोध;
			skip_count++;
		पूर्ण
	पूर्ण
	*buf_size = count;

	वापस status;
पूर्ण

/*
 * Conकाष्ठा the SCP header using corresponding fields
 */
अटल अंतरभूत अचिन्हित पूर्णांक
make_scp_header(अचिन्हित पूर्णांक target_id, अचिन्हित पूर्णांक source_id,
		अचिन्हित पूर्णांक get_flag, अचिन्हित पूर्णांक req,
		अचिन्हित पूर्णांक device_flag, अचिन्हित पूर्णांक resp_flag,
		अचिन्हित पूर्णांक error_flag, अचिन्हित पूर्णांक data_size)
अणु
	अचिन्हित पूर्णांक header = 0;

	header = (data_size & 0x1f) << 27;
	header |= (error_flag & 0x01) << 26;
	header |= (resp_flag & 0x01) << 25;
	header |= (device_flag & 0x01) << 24;
	header |= (req & 0x7f) << 17;
	header |= (get_flag & 0x01) << 16;
	header |= (source_id & 0xff) << 8;
	header |= target_id & 0xff;

	वापस header;
पूर्ण

/*
 * Extract corresponding fields from SCP header
 */
अटल अंतरभूत व्योम
extract_scp_header(अचिन्हित पूर्णांक header,
		   अचिन्हित पूर्णांक *target_id, अचिन्हित पूर्णांक *source_id,
		   अचिन्हित पूर्णांक *get_flag, अचिन्हित पूर्णांक *req,
		   अचिन्हित पूर्णांक *device_flag, अचिन्हित पूर्णांक *resp_flag,
		   अचिन्हित पूर्णांक *error_flag, अचिन्हित पूर्णांक *data_size)
अणु
	अगर (data_size)
		*data_size = (header >> 27) & 0x1f;
	अगर (error_flag)
		*error_flag = (header >> 26) & 0x01;
	अगर (resp_flag)
		*resp_flag = (header >> 25) & 0x01;
	अगर (device_flag)
		*device_flag = (header >> 24) & 0x01;
	अगर (req)
		*req = (header >> 17) & 0x7f;
	अगर (get_flag)
		*get_flag = (header >> 16) & 0x01;
	अगर (source_id)
		*source_id = (header >> 8) & 0xff;
	अगर (target_id)
		*target_id = header & 0xff;
पूर्ण

#घोषणा SCP_MAX_DATA_WORDS  (16)

/* Structure to contain any SCP message */
काष्ठा scp_msg अणु
	अचिन्हित पूर्णांक hdr;
	अचिन्हित पूर्णांक data[SCP_MAX_DATA_WORDS];
पूर्ण;

अटल व्योम dspio_clear_response_queue(काष्ठा hda_codec *codec)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);
	अचिन्हित पूर्णांक dummy = 0;
	पूर्णांक status;

	/* clear all from the response queue */
	करो अणु
		status = dspio_पढ़ो(codec, &dummy);
	पूर्ण जबतक (status == 0 && समय_beक्रमe(jअगरfies, समयout));
पूर्ण

अटल पूर्णांक dspio_get_response_data(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक data = 0;
	अचिन्हित पूर्णांक count;

	अगर (dspio_पढ़ो(codec, &data) < 0)
		वापस -EIO;

	अगर ((data & 0x00ffffff) == spec->रुको_scp_header) अणु
		spec->scp_resp_header = data;
		spec->scp_resp_count = data >> 27;
		count = spec->रुको_num_data;
		dspio_पढ़ो_multiple(codec, spec->scp_resp_data,
				    &spec->scp_resp_count, count);
		वापस 0;
	पूर्ण

	वापस -EIO;
पूर्ण

/*
 * Send SCP message to DSP
 */
अटल पूर्णांक dspio_send_scp_message(काष्ठा hda_codec *codec,
				  अचिन्हित अक्षर *send_buf,
				  अचिन्हित पूर्णांक send_buf_size,
				  अचिन्हित अक्षर *वापस_buf,
				  अचिन्हित पूर्णांक वापस_buf_size,
				  अचिन्हित पूर्णांक *bytes_वापसed)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक status = -1;
	अचिन्हित पूर्णांक scp_send_size = 0;
	अचिन्हित पूर्णांक total_size;
	bool रुकोing_क्रम_resp = false;
	अचिन्हित पूर्णांक header;
	काष्ठा scp_msg *ret_msg;
	अचिन्हित पूर्णांक resp_src_id, resp_target_id;
	अचिन्हित पूर्णांक data_size, src_id, target_id, get_flag, device_flag;

	अगर (bytes_वापसed)
		*bytes_वापसed = 0;

	/* get scp header from buffer */
	header = *((अचिन्हित पूर्णांक *)send_buf);
	extract_scp_header(header, &target_id, &src_id, &get_flag, शून्य,
			   &device_flag, शून्य, शून्य, &data_size);
	scp_send_size = data_size + 1;
	total_size = (scp_send_size * 4);

	अगर (send_buf_size < total_size)
		वापस -EINVAL;

	अगर (get_flag || device_flag) अणु
		अगर (!वापस_buf || वापस_buf_size < 4 || !bytes_वापसed)
			वापस -EINVAL;

		spec->रुको_scp_header = *((अचिन्हित पूर्णांक *)send_buf);

		/* swap source id with target id */
		resp_target_id = src_id;
		resp_src_id = target_id;
		spec->रुको_scp_header &= 0xffff0000;
		spec->रुको_scp_header |= (resp_src_id << 8) | (resp_target_id);
		spec->रुको_num_data = वापस_buf_size/माप(अचिन्हित पूर्णांक) - 1;
		spec->रुको_scp = 1;
		रुकोing_क्रम_resp = true;
	पूर्ण

	status = dspio_ग_लिखो_multiple(codec, (अचिन्हित पूर्णांक *)send_buf,
				      scp_send_size);
	अगर (status < 0) अणु
		spec->रुको_scp = 0;
		वापस status;
	पूर्ण

	अगर (रुकोing_क्रम_resp) अणु
		अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);
		स_रखो(वापस_buf, 0, वापस_buf_size);
		करो अणु
			msleep(20);
		पूर्ण जबतक (spec->रुको_scp && समय_beक्रमe(jअगरfies, समयout));
		रुकोing_क्रम_resp = false;
		अगर (!spec->रुको_scp) अणु
			ret_msg = (काष्ठा scp_msg *)वापस_buf;
			स_नकल(&ret_msg->hdr, &spec->scp_resp_header, 4);
			स_नकल(&ret_msg->data, spec->scp_resp_data,
			       spec->रुको_num_data);
			*bytes_वापसed = (spec->scp_resp_count + 1) * 4;
			status = 0;
		पूर्ण अन्यथा अणु
			status = -EIO;
		पूर्ण
		spec->रुको_scp = 0;
	पूर्ण

	वापस status;
पूर्ण

/**
 * dspio_scp - Prepare and send the SCP message to DSP
 * @codec: the HDA codec
 * @mod_id: ID of the DSP module to send the command
 * @src_id: ID of the source
 * @req: ID of request to send to the DSP module
 * @dir: SET or GET
 * @data: poपूर्णांकer to the data to send with the request, request specअगरic
 * @len: length of the data, in bytes
 * @reply: poपूर्णांक to the buffer to hold data वापसed क्रम a reply
 * @reply_len: length of the reply buffer वापसed from GET
 *
 * Returns zero or a negative error code.
 */
अटल पूर्णांक dspio_scp(काष्ठा hda_codec *codec,
		पूर्णांक mod_id, पूर्णांक src_id, पूर्णांक req, पूर्णांक dir, स्थिर व्योम *data,
		अचिन्हित पूर्णांक len, व्योम *reply, अचिन्हित पूर्णांक *reply_len)
अणु
	पूर्णांक status = 0;
	काष्ठा scp_msg scp_send, scp_reply;
	अचिन्हित पूर्णांक ret_bytes, send_size, ret_size;
	अचिन्हित पूर्णांक send_get_flag, reply_resp_flag, reply_error_flag;
	अचिन्हित पूर्णांक reply_data_size;

	स_रखो(&scp_send, 0, माप(scp_send));
	स_रखो(&scp_reply, 0, माप(scp_reply));

	अगर ((len != 0 && data == शून्य) || (len > SCP_MAX_DATA_WORDS))
		वापस -EINVAL;

	अगर (dir == SCP_GET && reply == शून्य) अणु
		codec_dbg(codec, "dspio_scp get but has no buffer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (reply != शून्य && (reply_len == शून्य || (*reply_len == 0))) अणु
		codec_dbg(codec, "dspio_scp bad resp buf len parms\n");
		वापस -EINVAL;
	पूर्ण

	scp_send.hdr = make_scp_header(mod_id, src_id, (dir == SCP_GET), req,
				       0, 0, 0, len/माप(अचिन्हित पूर्णांक));
	अगर (data != शून्य && len > 0) अणु
		len = min((अचिन्हित पूर्णांक)(माप(scp_send.data)), len);
		स_नकल(scp_send.data, data, len);
	पूर्ण

	ret_bytes = 0;
	send_size = माप(अचिन्हित पूर्णांक) + len;
	status = dspio_send_scp_message(codec, (अचिन्हित अक्षर *)&scp_send,
					send_size, (अचिन्हित अक्षर *)&scp_reply,
					माप(scp_reply), &ret_bytes);

	अगर (status < 0) अणु
		codec_dbg(codec, "dspio_scp: send scp msg failed\n");
		वापस status;
	पूर्ण

	/* extract send and reply headers members */
	extract_scp_header(scp_send.hdr, शून्य, शून्य, &send_get_flag,
			   शून्य, शून्य, शून्य, शून्य, शून्य);
	extract_scp_header(scp_reply.hdr, शून्य, शून्य, शून्य, शून्य, शून्य,
			   &reply_resp_flag, &reply_error_flag,
			   &reply_data_size);

	अगर (!send_get_flag)
		वापस 0;

	अगर (reply_resp_flag && !reply_error_flag) अणु
		ret_size = (ret_bytes - माप(scp_reply.hdr))
					/ माप(अचिन्हित पूर्णांक);

		अगर (*reply_len < ret_size*माप(अचिन्हित पूर्णांक)) अणु
			codec_dbg(codec, "reply too long for buf\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (ret_size != reply_data_size) अणु
			codec_dbg(codec, "RetLen and HdrLen .NE.\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (!reply) अणु
			codec_dbg(codec, "NULL reply\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			*reply_len = ret_size*माप(अचिन्हित पूर्णांक);
			स_नकल(reply, scp_reply.data, *reply_len);
		पूर्ण
	पूर्ण अन्यथा अणु
		codec_dbg(codec, "reply ill-formed or errflag set\n");
		वापस -EIO;
	पूर्ण

	वापस status;
पूर्ण

/*
 * Set DSP parameters
 */
अटल पूर्णांक dspio_set_param(काष्ठा hda_codec *codec, पूर्णांक mod_id,
			पूर्णांक src_id, पूर्णांक req, स्थिर व्योम *data, अचिन्हित पूर्णांक len)
अणु
	वापस dspio_scp(codec, mod_id, src_id, req, SCP_SET, data, len, शून्य,
			शून्य);
पूर्ण

अटल पूर्णांक dspio_set_uपूर्णांक_param(काष्ठा hda_codec *codec, पूर्णांक mod_id,
			पूर्णांक req, स्थिर अचिन्हित पूर्णांक data)
अणु
	वापस dspio_set_param(codec, mod_id, 0x20, req, &data,
			माप(अचिन्हित पूर्णांक));
पूर्ण

/*
 * Allocate a DSP DMA channel via an SCP message
 */
अटल पूर्णांक dspio_alloc_dma_chan(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक *dma_chan)
अणु
	पूर्णांक status = 0;
	अचिन्हित पूर्णांक size = माप(dma_chan);

	codec_dbg(codec, "     dspio_alloc_dma_chan() -- begin\n");
	status = dspio_scp(codec, MASTERCONTROL, 0x20,
			MASTERCONTROL_ALLOC_DMA_CHAN, SCP_GET, शून्य, 0,
			dma_chan, &size);

	अगर (status < 0) अणु
		codec_dbg(codec, "dspio_alloc_dma_chan: SCP Failed\n");
		वापस status;
	पूर्ण

	अगर ((*dma_chan + 1) == 0) अणु
		codec_dbg(codec, "no free dma channels to allocate\n");
		वापस -EBUSY;
	पूर्ण

	codec_dbg(codec, "dspio_alloc_dma_chan: chan=%d\n", *dma_chan);
	codec_dbg(codec, "     dspio_alloc_dma_chan() -- complete\n");

	वापस status;
पूर्ण

/*
 * Free a DSP DMA via an SCP message
 */
अटल पूर्णांक dspio_मुक्त_dma_chan(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक dma_chan)
अणु
	पूर्णांक status = 0;
	अचिन्हित पूर्णांक dummy = 0;

	codec_dbg(codec, "     dspio_free_dma_chan() -- begin\n");
	codec_dbg(codec, "dspio_free_dma_chan: chan=%d\n", dma_chan);

	status = dspio_scp(codec, MASTERCONTROL, 0x20,
			MASTERCONTROL_ALLOC_DMA_CHAN, SCP_SET, &dma_chan,
			माप(dma_chan), शून्य, &dummy);

	अगर (status < 0) अणु
		codec_dbg(codec, "dspio_free_dma_chan: SCP Failed\n");
		वापस status;
	पूर्ण

	codec_dbg(codec, "     dspio_free_dma_chan() -- complete\n");

	वापस status;
पूर्ण

/*
 * (Re)start the DSP
 */
अटल पूर्णांक dsp_set_run_state(काष्ठा hda_codec *codec)
अणु
	अचिन्हित पूर्णांक dbg_ctrl_reg;
	अचिन्हित पूर्णांक halt_state;
	पूर्णांक err;

	err = chipio_पढ़ो(codec, DSP_DBGCNTL_INST_OFFSET, &dbg_ctrl_reg);
	अगर (err < 0)
		वापस err;

	halt_state = (dbg_ctrl_reg & DSP_DBGCNTL_STATE_MASK) >>
		      DSP_DBGCNTL_STATE_LOBIT;

	अगर (halt_state != 0) अणु
		dbg_ctrl_reg &= ~((halt_state << DSP_DBGCNTL_SS_LOBIT) &
				  DSP_DBGCNTL_SS_MASK);
		err = chipio_ग_लिखो(codec, DSP_DBGCNTL_INST_OFFSET,
				   dbg_ctrl_reg);
		अगर (err < 0)
			वापस err;

		dbg_ctrl_reg |= (halt_state << DSP_DBGCNTL_EXEC_LOBIT) &
				DSP_DBGCNTL_EXEC_MASK;
		err = chipio_ग_लिखो(codec, DSP_DBGCNTL_INST_OFFSET,
				   dbg_ctrl_reg);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Reset the DSP
 */
अटल पूर्णांक dsp_reset(काष्ठा hda_codec *codec)
अणु
	अचिन्हित पूर्णांक res;
	पूर्णांक retry = 20;

	codec_dbg(codec, "dsp_reset\n");
	करो अणु
		res = dspio_send(codec, VENDOR_DSPIO_DSP_INIT, 0);
		retry--;
	पूर्ण जबतक (res == -EIO && retry);

	अगर (!retry) अणु
		codec_dbg(codec, "dsp_reset timeout\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Convert chip address to DSP address
 */
अटल अचिन्हित पूर्णांक dsp_chip_to_dsp_addx(अचिन्हित पूर्णांक chip_addx,
					bool *code, bool *yram)
अणु
	*code = *yram = false;

	अगर (UC_RANGE(chip_addx, 1)) अणु
		*code = true;
		वापस UC_OFF(chip_addx);
	पूर्ण अन्यथा अगर (X_RANGE_ALL(chip_addx, 1)) अणु
		वापस X_OFF(chip_addx);
	पूर्ण अन्यथा अगर (Y_RANGE_ALL(chip_addx, 1)) अणु
		*yram = true;
		वापस Y_OFF(chip_addx);
	पूर्ण

	वापस INVALID_CHIP_ADDRESS;
पूर्ण

/*
 * Check अगर the DSP DMA is active
 */
अटल bool dsp_is_dma_active(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक dma_chan)
अणु
	अचिन्हित पूर्णांक dma_chnlstart_reg;

	chipio_पढ़ो(codec, DSPDMAC_CHNLSTART_INST_OFFSET, &dma_chnlstart_reg);

	वापस ((dma_chnlstart_reg & (1 <<
			(DSPDMAC_CHNLSTART_EN_LOBIT + dma_chan))) != 0);
पूर्ण

अटल पूर्णांक dsp_dma_setup_common(काष्ठा hda_codec *codec,
				अचिन्हित पूर्णांक chip_addx,
				अचिन्हित पूर्णांक dma_chan,
				अचिन्हित पूर्णांक port_map_mask,
				bool ovly)
अणु
	पूर्णांक status = 0;
	अचिन्हित पूर्णांक chnl_prop;
	अचिन्हित पूर्णांक dsp_addx;
	अचिन्हित पूर्णांक active;
	bool code, yram;

	codec_dbg(codec, "-- dsp_dma_setup_common() -- Begin ---------\n");

	अगर (dma_chan >= DSPDMAC_DMA_CFG_CHANNEL_COUNT) अणु
		codec_dbg(codec, "dma chan num invalid\n");
		वापस -EINVAL;
	पूर्ण

	अगर (dsp_is_dma_active(codec, dma_chan)) अणु
		codec_dbg(codec, "dma already active\n");
		वापस -EBUSY;
	पूर्ण

	dsp_addx = dsp_chip_to_dsp_addx(chip_addx, &code, &yram);

	अगर (dsp_addx == INVALID_CHIP_ADDRESS) अणु
		codec_dbg(codec, "invalid chip addr\n");
		वापस -ENXIO;
	पूर्ण

	chnl_prop = DSPDMAC_CHNLPROP_AC_MASK;
	active = 0;

	codec_dbg(codec, "   dsp_dma_setup_common()    start reg pgm\n");

	अगर (ovly) अणु
		status = chipio_पढ़ो(codec, DSPDMAC_CHNLPROP_INST_OFFSET,
				     &chnl_prop);

		अगर (status < 0) अणु
			codec_dbg(codec, "read CHNLPROP Reg fail\n");
			वापस status;
		पूर्ण
		codec_dbg(codec, "dsp_dma_setup_common() Read CHNLPROP\n");
	पूर्ण

	अगर (!code)
		chnl_prop &= ~(1 << (DSPDMAC_CHNLPROP_MSPCE_LOBIT + dma_chan));
	अन्यथा
		chnl_prop |=  (1 << (DSPDMAC_CHNLPROP_MSPCE_LOBIT + dma_chan));

	chnl_prop &= ~(1 << (DSPDMAC_CHNLPROP_DCON_LOBIT + dma_chan));

	status = chipio_ग_लिखो(codec, DSPDMAC_CHNLPROP_INST_OFFSET, chnl_prop);
	अगर (status < 0) अणु
		codec_dbg(codec, "write CHNLPROP Reg fail\n");
		वापस status;
	पूर्ण
	codec_dbg(codec, "   dsp_dma_setup_common()    Write CHNLPROP\n");

	अगर (ovly) अणु
		status = chipio_पढ़ो(codec, DSPDMAC_ACTIVE_INST_OFFSET,
				     &active);

		अगर (status < 0) अणु
			codec_dbg(codec, "read ACTIVE Reg fail\n");
			वापस status;
		पूर्ण
		codec_dbg(codec, "dsp_dma_setup_common() Read ACTIVE\n");
	पूर्ण

	active &= (~(1 << (DSPDMAC_ACTIVE_AAR_LOBIT + dma_chan))) &
		DSPDMAC_ACTIVE_AAR_MASK;

	status = chipio_ग_लिखो(codec, DSPDMAC_ACTIVE_INST_OFFSET, active);
	अगर (status < 0) अणु
		codec_dbg(codec, "write ACTIVE Reg fail\n");
		वापस status;
	पूर्ण

	codec_dbg(codec, "   dsp_dma_setup_common()    Write ACTIVE\n");

	status = chipio_ग_लिखो(codec, DSPDMAC_AUDCHSEL_INST_OFFSET(dma_chan),
			      port_map_mask);
	अगर (status < 0) अणु
		codec_dbg(codec, "write AUDCHSEL Reg fail\n");
		वापस status;
	पूर्ण
	codec_dbg(codec, "   dsp_dma_setup_common()    Write AUDCHSEL\n");

	status = chipio_ग_लिखो(codec, DSPDMAC_IRQCNT_INST_OFFSET(dma_chan),
			DSPDMAC_IRQCNT_BICNT_MASK | DSPDMAC_IRQCNT_CICNT_MASK);
	अगर (status < 0) अणु
		codec_dbg(codec, "write IRQCNT Reg fail\n");
		वापस status;
	पूर्ण
	codec_dbg(codec, "   dsp_dma_setup_common()    Write IRQCNT\n");

	codec_dbg(codec,
		   "ChipA=0x%x,DspA=0x%x,dmaCh=%u, "
		   "CHSEL=0x%x,CHPROP=0x%x,Active=0x%x\n",
		   chip_addx, dsp_addx, dma_chan,
		   port_map_mask, chnl_prop, active);

	codec_dbg(codec, "-- dsp_dma_setup_common() -- Complete ------\n");

	वापस 0;
पूर्ण

/*
 * Setup the DSP DMA per-transfer-specअगरic रेजिस्टरs
 */
अटल पूर्णांक dsp_dma_setup(काष्ठा hda_codec *codec,
			अचिन्हित पूर्णांक chip_addx,
			अचिन्हित पूर्णांक count,
			अचिन्हित पूर्णांक dma_chan)
अणु
	पूर्णांक status = 0;
	bool code, yram;
	अचिन्हित पूर्णांक dsp_addx;
	अचिन्हित पूर्णांक addr_field;
	अचिन्हित पूर्णांक incr_field;
	अचिन्हित पूर्णांक base_cnt;
	अचिन्हित पूर्णांक cur_cnt;
	अचिन्हित पूर्णांक dma_cfg = 0;
	अचिन्हित पूर्णांक adr_ofs = 0;
	अचिन्हित पूर्णांक xfr_cnt = 0;
	स्थिर अचिन्हित पूर्णांक max_dma_count = 1 << (DSPDMAC_XFRCNT_BCNT_HIBIT -
						DSPDMAC_XFRCNT_BCNT_LOBIT + 1);

	codec_dbg(codec, "-- dsp_dma_setup() -- Begin ---------\n");

	अगर (count > max_dma_count) अणु
		codec_dbg(codec, "count too big\n");
		वापस -EINVAL;
	पूर्ण

	dsp_addx = dsp_chip_to_dsp_addx(chip_addx, &code, &yram);
	अगर (dsp_addx == INVALID_CHIP_ADDRESS) अणु
		codec_dbg(codec, "invalid chip addr\n");
		वापस -ENXIO;
	पूर्ण

	codec_dbg(codec, "   dsp_dma_setup()    start reg pgm\n");

	addr_field = dsp_addx << DSPDMAC_DMACFG_DBADR_LOBIT;
	incr_field   = 0;

	अगर (!code) अणु
		addr_field <<= 1;
		अगर (yram)
			addr_field |= (1 << DSPDMAC_DMACFG_DBADR_LOBIT);

		incr_field  = (1 << DSPDMAC_DMACFG_AINCR_LOBIT);
	पूर्ण

	dma_cfg = addr_field + incr_field;
	status = chipio_ग_लिखो(codec, DSPDMAC_DMACFG_INST_OFFSET(dma_chan),
				dma_cfg);
	अगर (status < 0) अणु
		codec_dbg(codec, "write DMACFG Reg fail\n");
		वापस status;
	पूर्ण
	codec_dbg(codec, "   dsp_dma_setup()    Write DMACFG\n");

	adr_ofs = (count - 1) << (DSPDMAC_DSPADROFS_BOFS_LOBIT +
							(code ? 0 : 1));

	status = chipio_ग_लिखो(codec, DSPDMAC_DSPADROFS_INST_OFFSET(dma_chan),
				adr_ofs);
	अगर (status < 0) अणु
		codec_dbg(codec, "write DSPADROFS Reg fail\n");
		वापस status;
	पूर्ण
	codec_dbg(codec, "   dsp_dma_setup()    Write DSPADROFS\n");

	base_cnt = (count - 1) << DSPDMAC_XFRCNT_BCNT_LOBIT;

	cur_cnt  = (count - 1) << DSPDMAC_XFRCNT_CCNT_LOBIT;

	xfr_cnt = base_cnt | cur_cnt;

	status = chipio_ग_लिखो(codec,
				DSPDMAC_XFRCNT_INST_OFFSET(dma_chan), xfr_cnt);
	अगर (status < 0) अणु
		codec_dbg(codec, "write XFRCNT Reg fail\n");
		वापस status;
	पूर्ण
	codec_dbg(codec, "   dsp_dma_setup()    Write XFRCNT\n");

	codec_dbg(codec,
		   "ChipA=0x%x, cnt=0x%x, DMACFG=0x%x, "
		   "ADROFS=0x%x, XFRCNT=0x%x\n",
		   chip_addx, count, dma_cfg, adr_ofs, xfr_cnt);

	codec_dbg(codec, "-- dsp_dma_setup() -- Complete ---------\n");

	वापस 0;
पूर्ण

/*
 * Start the DSP DMA
 */
अटल पूर्णांक dsp_dma_start(काष्ठा hda_codec *codec,
			 अचिन्हित पूर्णांक dma_chan, bool ovly)
अणु
	अचिन्हित पूर्णांक reg = 0;
	पूर्णांक status = 0;

	codec_dbg(codec, "-- dsp_dma_start() -- Begin ---------\n");

	अगर (ovly) अणु
		status = chipio_पढ़ो(codec,
				     DSPDMAC_CHNLSTART_INST_OFFSET, &reg);

		अगर (status < 0) अणु
			codec_dbg(codec, "read CHNLSTART reg fail\n");
			वापस status;
		पूर्ण
		codec_dbg(codec, "-- dsp_dma_start()    Read CHNLSTART\n");

		reg &= ~(DSPDMAC_CHNLSTART_EN_MASK |
				DSPDMAC_CHNLSTART_DIS_MASK);
	पूर्ण

	status = chipio_ग_लिखो(codec, DSPDMAC_CHNLSTART_INST_OFFSET,
			reg | (1 << (dma_chan + DSPDMAC_CHNLSTART_EN_LOBIT)));
	अगर (status < 0) अणु
		codec_dbg(codec, "write CHNLSTART reg fail\n");
		वापस status;
	पूर्ण
	codec_dbg(codec, "-- dsp_dma_start() -- Complete ---------\n");

	वापस status;
पूर्ण

/*
 * Stop the DSP DMA
 */
अटल पूर्णांक dsp_dma_stop(काष्ठा hda_codec *codec,
			अचिन्हित पूर्णांक dma_chan, bool ovly)
अणु
	अचिन्हित पूर्णांक reg = 0;
	पूर्णांक status = 0;

	codec_dbg(codec, "-- dsp_dma_stop() -- Begin ---------\n");

	अगर (ovly) अणु
		status = chipio_पढ़ो(codec,
				     DSPDMAC_CHNLSTART_INST_OFFSET, &reg);

		अगर (status < 0) अणु
			codec_dbg(codec, "read CHNLSTART reg fail\n");
			वापस status;
		पूर्ण
		codec_dbg(codec, "-- dsp_dma_stop()    Read CHNLSTART\n");
		reg &= ~(DSPDMAC_CHNLSTART_EN_MASK |
				DSPDMAC_CHNLSTART_DIS_MASK);
	पूर्ण

	status = chipio_ग_लिखो(codec, DSPDMAC_CHNLSTART_INST_OFFSET,
			reg | (1 << (dma_chan + DSPDMAC_CHNLSTART_DIS_LOBIT)));
	अगर (status < 0) अणु
		codec_dbg(codec, "write CHNLSTART reg fail\n");
		वापस status;
	पूर्ण
	codec_dbg(codec, "-- dsp_dma_stop() -- Complete ---------\n");

	वापस status;
पूर्ण

/**
 * dsp_allocate_router_ports - Allocate router ports
 *
 * @codec: the HDA codec
 * @num_chans: number of channels in the stream
 * @ports_per_channel: number of ports per channel
 * @start_device: start device
 * @port_map: poपूर्णांकer to the port list to hold the allocated ports
 *
 * Returns zero or a negative error code.
 */
अटल पूर्णांक dsp_allocate_router_ports(काष्ठा hda_codec *codec,
				     अचिन्हित पूर्णांक num_chans,
				     अचिन्हित पूर्णांक ports_per_channel,
				     अचिन्हित पूर्णांक start_device,
				     अचिन्हित पूर्णांक *port_map)
अणु
	पूर्णांक status = 0;
	पूर्णांक res;
	u8 val;

	status = chipio_send(codec, VENDOR_CHIPIO_STATUS, 0);
	अगर (status < 0)
		वापस status;

	val = start_device << 6;
	val |= (ports_per_channel - 1) << 4;
	val |= num_chans - 1;

	snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_PORT_ALLOC_CONFIG_SET,
			    val);

	snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_PORT_ALLOC_SET,
			    MEM_CONNID_DSP);

	status = chipio_send(codec, VENDOR_CHIPIO_STATUS, 0);
	अगर (status < 0)
		वापस status;

	res = snd_hda_codec_पढ़ो(codec, WIDGET_CHIP_CTRL, 0,
				VENDOR_CHIPIO_PORT_ALLOC_GET, 0);

	*port_map = res;

	वापस (res < 0) ? res : 0;
पूर्ण

/*
 * Free router ports
 */
अटल पूर्णांक dsp_मुक्त_router_ports(काष्ठा hda_codec *codec)
अणु
	पूर्णांक status = 0;

	status = chipio_send(codec, VENDOR_CHIPIO_STATUS, 0);
	अगर (status < 0)
		वापस status;

	snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_PORT_FREE_SET,
			    MEM_CONNID_DSP);

	status = chipio_send(codec, VENDOR_CHIPIO_STATUS, 0);

	वापस status;
पूर्ण

/*
 * Allocate DSP ports क्रम the करोwnload stream
 */
अटल पूर्णांक dsp_allocate_ports(काष्ठा hda_codec *codec,
			अचिन्हित पूर्णांक num_chans,
			अचिन्हित पूर्णांक rate_multi, अचिन्हित पूर्णांक *port_map)
अणु
	पूर्णांक status;

	codec_dbg(codec, "     dsp_allocate_ports() -- begin\n");

	अगर ((rate_multi != 1) && (rate_multi != 2) && (rate_multi != 4)) अणु
		codec_dbg(codec, "bad rate multiple\n");
		वापस -EINVAL;
	पूर्ण

	status = dsp_allocate_router_ports(codec, num_chans,
					   rate_multi, 0, port_map);

	codec_dbg(codec, "     dsp_allocate_ports() -- complete\n");

	वापस status;
पूर्ण

अटल पूर्णांक dsp_allocate_ports_क्रमmat(काष्ठा hda_codec *codec,
			स्थिर अचिन्हित लघु fmt,
			अचिन्हित पूर्णांक *port_map)
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक num_chans;

	अचिन्हित पूर्णांक sample_rate_भाग = ((get_hdafmt_rate(fmt) >> 0) & 3) + 1;
	अचिन्हित पूर्णांक sample_rate_mul = ((get_hdafmt_rate(fmt) >> 3) & 3) + 1;
	अचिन्हित पूर्णांक rate_multi = sample_rate_mul / sample_rate_भाग;

	अगर ((rate_multi != 1) && (rate_multi != 2) && (rate_multi != 4)) अणु
		codec_dbg(codec, "bad rate multiple\n");
		वापस -EINVAL;
	पूर्ण

	num_chans = get_hdafmt_chs(fmt) + 1;

	status = dsp_allocate_ports(codec, num_chans, rate_multi, port_map);

	वापस status;
पूर्ण

/*
 * मुक्त DSP ports
 */
अटल पूर्णांक dsp_मुक्त_ports(काष्ठा hda_codec *codec)
अणु
	पूर्णांक status;

	codec_dbg(codec, "     dsp_free_ports() -- begin\n");

	status = dsp_मुक्त_router_ports(codec);
	अगर (status < 0) अणु
		codec_dbg(codec, "free router ports fail\n");
		वापस status;
	पूर्ण
	codec_dbg(codec, "     dsp_free_ports() -- complete\n");

	वापस status;
पूर्ण

/*
 *  HDA DMA engine stuffs क्रम DSP code करोwnload
 */
काष्ठा dma_engine अणु
	काष्ठा hda_codec *codec;
	अचिन्हित लघु m_converter_क्रमmat;
	काष्ठा snd_dma_buffer *dmab;
	अचिन्हित पूर्णांक buf_size;
पूर्ण;


क्रमागत dma_state अणु
	DMA_STATE_STOP  = 0,
	DMA_STATE_RUN   = 1
पूर्ण;

अटल पूर्णांक dma_convert_to_hda_क्रमmat(काष्ठा hda_codec *codec,
		अचिन्हित पूर्णांक sample_rate,
		अचिन्हित लघु channels,
		अचिन्हित लघु *hda_क्रमmat)
अणु
	अचिन्हित पूर्णांक क्रमmat_val;

	क्रमmat_val = snd_hdac_calc_stream_क्रमmat(sample_rate,
				channels, SNDRV_PCM_FORMAT_S32_LE, 32, 0);

	अगर (hda_क्रमmat)
		*hda_क्रमmat = (अचिन्हित लघु)क्रमmat_val;

	वापस 0;
पूर्ण

/*
 *  Reset DMA क्रम DSP करोwnload
 */
अटल पूर्णांक dma_reset(काष्ठा dma_engine *dma)
अणु
	काष्ठा hda_codec *codec = dma->codec;
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक status;

	अगर (dma->dmab->area)
		snd_hda_codec_load_dsp_cleanup(codec, dma->dmab);

	status = snd_hda_codec_load_dsp_prepare(codec,
			dma->m_converter_क्रमmat,
			dma->buf_size,
			dma->dmab);
	अगर (status < 0)
		वापस status;
	spec->dsp_stream_id = status;
	वापस 0;
पूर्ण

अटल पूर्णांक dma_set_state(काष्ठा dma_engine *dma, क्रमागत dma_state state)
अणु
	bool cmd;

	चयन (state) अणु
	हाल DMA_STATE_STOP:
		cmd = false;
		अवरोध;
	हाल DMA_STATE_RUN:
		cmd = true;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	snd_hda_codec_load_dsp_trigger(dma->codec, cmd);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक dma_get_buffer_size(काष्ठा dma_engine *dma)
अणु
	वापस dma->dmab->bytes;
पूर्ण

अटल अचिन्हित अक्षर *dma_get_buffer_addr(काष्ठा dma_engine *dma)
अणु
	वापस dma->dmab->area;
पूर्ण

अटल पूर्णांक dma_xfer(काष्ठा dma_engine *dma,
		स्थिर अचिन्हित पूर्णांक *data,
		अचिन्हित पूर्णांक count)
अणु
	स_नकल(dma->dmab->area, data, count);
	वापस 0;
पूर्ण

अटल व्योम dma_get_converter_क्रमmat(
		काष्ठा dma_engine *dma,
		अचिन्हित लघु *क्रमmat)
अणु
	अगर (क्रमmat)
		*क्रमmat = dma->m_converter_क्रमmat;
पूर्ण

अटल अचिन्हित पूर्णांक dma_get_stream_id(काष्ठा dma_engine *dma)
अणु
	काष्ठा ca0132_spec *spec = dma->codec->spec;

	वापस spec->dsp_stream_id;
पूर्ण

काष्ठा dsp_image_seg अणु
	u32 magic;
	u32 chip_addr;
	u32 count;
	u32 data[];
पूर्ण;

अटल स्थिर u32 g_magic_value = 0x4c46584d;
अटल स्थिर u32 g_chip_addr_magic_value = 0xFFFFFF01;

अटल bool is_valid(स्थिर काष्ठा dsp_image_seg *p)
अणु
	वापस p->magic == g_magic_value;
पूर्ण

अटल bool is_hci_prog_list_seg(स्थिर काष्ठा dsp_image_seg *p)
अणु
	वापस g_chip_addr_magic_value == p->chip_addr;
पूर्ण

अटल bool is_last(स्थिर काष्ठा dsp_image_seg *p)
अणु
	वापस p->count == 0;
पूर्ण

अटल माप_प्रकार dsp_माप(स्थिर काष्ठा dsp_image_seg *p)
अणु
	वापस काष्ठा_size(p, data, p->count);
पूर्ण

अटल स्थिर काष्ठा dsp_image_seg *get_next_seg_ptr(
				स्थिर काष्ठा dsp_image_seg *p)
अणु
	वापस (काष्ठा dsp_image_seg *)((अचिन्हित अक्षर *)(p) + dsp_माप(p));
पूर्ण

/*
 * CA0132 chip DSP transfer stuffs.  For DSP करोwnload.
 */
#घोषणा INVALID_DMA_CHANNEL (~0U)

/*
 * Program a list of address/data pairs via the ChipIO widget.
 * The segment data is in the क्रमmat of successive pairs of words.
 * These are repeated as indicated by the segment's count field.
 */
अटल पूर्णांक dspxfr_hci_ग_लिखो(काष्ठा hda_codec *codec,
			स्थिर काष्ठा dsp_image_seg *fls)
अणु
	पूर्णांक status;
	स्थिर u32 *data;
	अचिन्हित पूर्णांक count;

	अगर (fls == शून्य || fls->chip_addr != g_chip_addr_magic_value) अणु
		codec_dbg(codec, "hci_write invalid params\n");
		वापस -EINVAL;
	पूर्ण

	count = fls->count;
	data = (u32 *)(fls->data);
	जबतक (count >= 2) अणु
		status = chipio_ग_लिखो(codec, data[0], data[1]);
		अगर (status < 0) अणु
			codec_dbg(codec, "hci_write chipio failed\n");
			वापस status;
		पूर्ण
		count -= 2;
		data  += 2;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * dspxfr_one_seg - Write a block of data पूर्णांकo DSP code or data RAM using pre-allocated DMA engine.
 *
 * @codec: the HDA codec
 * @fls: poपूर्णांकer to a fast load image
 * @reloc: Relocation address क्रम loading single-segment overlays, or 0 क्रम
 *	   no relocation
 * @dma_engine: poपूर्णांकer to DMA engine to be used क्रम DSP करोwnload
 * @dma_chan: The number of DMA channels used क्रम DSP करोwnload
 * @port_map_mask: port mapping
 * @ovly: TRUE अगर overlay क्रमmat is required
 *
 * Returns zero or a negative error code.
 */
अटल पूर्णांक dspxfr_one_seg(काष्ठा hda_codec *codec,
			स्थिर काष्ठा dsp_image_seg *fls,
			अचिन्हित पूर्णांक reloc,
			काष्ठा dma_engine *dma_engine,
			अचिन्हित पूर्णांक dma_chan,
			अचिन्हित पूर्णांक port_map_mask,
			bool ovly)
अणु
	पूर्णांक status = 0;
	bool comm_dma_setup_करोne = false;
	स्थिर अचिन्हित पूर्णांक *data;
	अचिन्हित पूर्णांक chip_addx;
	अचिन्हित पूर्णांक words_to_ग_लिखो;
	अचिन्हित पूर्णांक buffer_size_words;
	अचिन्हित अक्षर *buffer_addx;
	अचिन्हित लघु hda_क्रमmat;
	अचिन्हित पूर्णांक sample_rate_भाग;
	अचिन्हित पूर्णांक sample_rate_mul;
	अचिन्हित पूर्णांक num_chans;
	अचिन्हित पूर्णांक hda_frame_size_words;
	अचिन्हित पूर्णांक reमुख्यder_words;
	स्थिर u32 *data_reमुख्यder;
	u32 chip_addx_reमुख्यder;
	अचिन्हित पूर्णांक run_size_words;
	स्थिर काष्ठा dsp_image_seg *hci_ग_लिखो = शून्य;
	अचिन्हित दीर्घ समयout;
	bool dma_active;

	अगर (fls == शून्य)
		वापस -EINVAL;
	अगर (is_hci_prog_list_seg(fls)) अणु
		hci_ग_लिखो = fls;
		fls = get_next_seg_ptr(fls);
	पूर्ण

	अगर (hci_ग_लिखो && (!fls || is_last(fls))) अणु
		codec_dbg(codec, "hci_write\n");
		वापस dspxfr_hci_ग_लिखो(codec, hci_ग_लिखो);
	पूर्ण

	अगर (fls == शून्य || dma_engine == शून्य || port_map_mask == 0) अणु
		codec_dbg(codec, "Invalid Params\n");
		वापस -EINVAL;
	पूर्ण

	data = fls->data;
	chip_addx = fls->chip_addr;
	words_to_ग_लिखो = fls->count;

	अगर (!words_to_ग_लिखो)
		वापस hci_ग_लिखो ? dspxfr_hci_ग_लिखो(codec, hci_ग_लिखो) : 0;
	अगर (reloc)
		chip_addx = (chip_addx & (0xFFFF0000 << 2)) + (reloc << 2);

	अगर (!UC_RANGE(chip_addx, words_to_ग_लिखो) &&
	    !X_RANGE_ALL(chip_addx, words_to_ग_लिखो) &&
	    !Y_RANGE_ALL(chip_addx, words_to_ग_लिखो)) अणु
		codec_dbg(codec, "Invalid chip_addx Params\n");
		वापस -EINVAL;
	पूर्ण

	buffer_size_words = (अचिन्हित पूर्णांक)dma_get_buffer_size(dma_engine) /
					माप(u32);

	buffer_addx = dma_get_buffer_addr(dma_engine);

	अगर (buffer_addx == शून्य) अणु
		codec_dbg(codec, "dma_engine buffer NULL\n");
		वापस -EINVAL;
	पूर्ण

	dma_get_converter_क्रमmat(dma_engine, &hda_क्रमmat);
	sample_rate_भाग = ((get_hdafmt_rate(hda_क्रमmat) >> 0) & 3) + 1;
	sample_rate_mul = ((get_hdafmt_rate(hda_क्रमmat) >> 3) & 3) + 1;
	num_chans = get_hdafmt_chs(hda_क्रमmat) + 1;

	hda_frame_size_words = ((sample_rate_भाग == 0) ? 0 :
			(num_chans * sample_rate_mul / sample_rate_भाग));

	अगर (hda_frame_size_words == 0) अणु
		codec_dbg(codec, "frmsz zero\n");
		वापस -EINVAL;
	पूर्ण

	buffer_size_words = min(buffer_size_words,
				(अचिन्हित पूर्णांक)(UC_RANGE(chip_addx, 1) ?
				65536 : 32768));
	buffer_size_words -= buffer_size_words % hda_frame_size_words;
	codec_dbg(codec,
		   "chpadr=0x%08x frmsz=%u nchan=%u "
		   "rate_mul=%u div=%u bufsz=%u\n",
		   chip_addx, hda_frame_size_words, num_chans,
		   sample_rate_mul, sample_rate_भाग, buffer_size_words);

	अगर (buffer_size_words < hda_frame_size_words) अणु
		codec_dbg(codec, "dspxfr_one_seg:failed\n");
		वापस -EINVAL;
	पूर्ण

	reमुख्यder_words = words_to_ग_लिखो % hda_frame_size_words;
	data_reमुख्यder = data;
	chip_addx_reमुख्यder = chip_addx;

	data += reमुख्यder_words;
	chip_addx += reमुख्यder_words*माप(u32);
	words_to_ग_लिखो -= reमुख्यder_words;

	जबतक (words_to_ग_लिखो != 0) अणु
		run_size_words = min(buffer_size_words, words_to_ग_लिखो);
		codec_dbg(codec, "dspxfr (seg loop)cnt=%u rs=%u remainder=%u\n",
			    words_to_ग_लिखो, run_size_words, reमुख्यder_words);
		dma_xfer(dma_engine, data, run_size_words*माप(u32));
		अगर (!comm_dma_setup_करोne) अणु
			status = dsp_dma_stop(codec, dma_chan, ovly);
			अगर (status < 0)
				वापस status;
			status = dsp_dma_setup_common(codec, chip_addx,
						dma_chan, port_map_mask, ovly);
			अगर (status < 0)
				वापस status;
			comm_dma_setup_करोne = true;
		पूर्ण

		status = dsp_dma_setup(codec, chip_addx,
						run_size_words, dma_chan);
		अगर (status < 0)
			वापस status;
		status = dsp_dma_start(codec, dma_chan, ovly);
		अगर (status < 0)
			वापस status;
		अगर (!dsp_is_dma_active(codec, dma_chan)) अणु
			codec_dbg(codec, "dspxfr:DMA did not start\n");
			वापस -EIO;
		पूर्ण
		status = dma_set_state(dma_engine, DMA_STATE_RUN);
		अगर (status < 0)
			वापस status;
		अगर (reमुख्यder_words != 0) अणु
			status = chipio_ग_लिखो_multiple(codec,
						chip_addx_reमुख्यder,
						data_reमुख्यder,
						reमुख्यder_words);
			अगर (status < 0)
				वापस status;
			reमुख्यder_words = 0;
		पूर्ण
		अगर (hci_ग_लिखो) अणु
			status = dspxfr_hci_ग_लिखो(codec, hci_ग_लिखो);
			अगर (status < 0)
				वापस status;
			hci_ग_लिखो = शून्य;
		पूर्ण

		समयout = jअगरfies + msecs_to_jअगरfies(2000);
		करो अणु
			dma_active = dsp_is_dma_active(codec, dma_chan);
			अगर (!dma_active)
				अवरोध;
			msleep(20);
		पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));
		अगर (dma_active)
			अवरोध;

		codec_dbg(codec, "+++++ DMA complete\n");
		dma_set_state(dma_engine, DMA_STATE_STOP);
		status = dma_reset(dma_engine);

		अगर (status < 0)
			वापस status;

		data += run_size_words;
		chip_addx += run_size_words*माप(u32);
		words_to_ग_लिखो -= run_size_words;
	पूर्ण

	अगर (reमुख्यder_words != 0) अणु
		status = chipio_ग_लिखो_multiple(codec, chip_addx_reमुख्यder,
					data_reमुख्यder, reमुख्यder_words);
	पूर्ण

	वापस status;
पूर्ण

/**
 * dspxfr_image - Write the entire DSP image of a DSP code/data overlay to DSP memories
 *
 * @codec: the HDA codec
 * @fls_data: poपूर्णांकer to a fast load image
 * @reloc: Relocation address क्रम loading single-segment overlays, or 0 क्रम
 *	   no relocation
 * @sample_rate: sampling rate of the stream used क्रम DSP करोwnload
 * @channels: channels of the stream used क्रम DSP करोwnload
 * @ovly: TRUE अगर overlay क्रमmat is required
 *
 * Returns zero or a negative error code.
 */
अटल पूर्णांक dspxfr_image(काष्ठा hda_codec *codec,
			स्थिर काष्ठा dsp_image_seg *fls_data,
			अचिन्हित पूर्णांक reloc,
			अचिन्हित पूर्णांक sample_rate,
			अचिन्हित लघु channels,
			bool ovly)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक status;
	अचिन्हित लघु hda_क्रमmat = 0;
	अचिन्हित पूर्णांक response;
	अचिन्हित अक्षर stream_id = 0;
	काष्ठा dma_engine *dma_engine;
	अचिन्हित पूर्णांक dma_chan;
	अचिन्हित पूर्णांक port_map_mask;

	अगर (fls_data == शून्य)
		वापस -EINVAL;

	dma_engine = kzalloc(माप(*dma_engine), GFP_KERNEL);
	अगर (!dma_engine)
		वापस -ENOMEM;

	dma_engine->dmab = kzalloc(माप(*dma_engine->dmab), GFP_KERNEL);
	अगर (!dma_engine->dmab) अणु
		kमुक्त(dma_engine);
		वापस -ENOMEM;
	पूर्ण

	dma_engine->codec = codec;
	dma_convert_to_hda_क्रमmat(codec, sample_rate, channels, &hda_क्रमmat);
	dma_engine->m_converter_क्रमmat = hda_क्रमmat;
	dma_engine->buf_size = (ovly ? DSP_DMA_WRITE_BUFLEN_OVLY :
			DSP_DMA_WRITE_BUFLEN_INIT) * 2;

	dma_chan = ovly ? INVALID_DMA_CHANNEL : 0;

	status = codec_set_converter_क्रमmat(codec, WIDGET_CHIP_CTRL,
					hda_क्रमmat, &response);

	अगर (status < 0) अणु
		codec_dbg(codec, "set converter format fail\n");
		जाओ निकास;
	पूर्ण

	status = snd_hda_codec_load_dsp_prepare(codec,
				dma_engine->m_converter_क्रमmat,
				dma_engine->buf_size,
				dma_engine->dmab);
	अगर (status < 0)
		जाओ निकास;
	spec->dsp_stream_id = status;

	अगर (ovly) अणु
		status = dspio_alloc_dma_chan(codec, &dma_chan);
		अगर (status < 0) अणु
			codec_dbg(codec, "alloc dmachan fail\n");
			dma_chan = INVALID_DMA_CHANNEL;
			जाओ निकास;
		पूर्ण
	पूर्ण

	port_map_mask = 0;
	status = dsp_allocate_ports_क्रमmat(codec, hda_क्रमmat,
					&port_map_mask);
	अगर (status < 0) अणु
		codec_dbg(codec, "alloc ports fail\n");
		जाओ निकास;
	पूर्ण

	stream_id = dma_get_stream_id(dma_engine);
	status = codec_set_converter_stream_channel(codec,
			WIDGET_CHIP_CTRL, stream_id, 0, &response);
	अगर (status < 0) अणु
		codec_dbg(codec, "set stream chan fail\n");
		जाओ निकास;
	पूर्ण

	जबतक ((fls_data != शून्य) && !is_last(fls_data)) अणु
		अगर (!is_valid(fls_data)) अणु
			codec_dbg(codec, "FLS check fail\n");
			status = -EINVAL;
			जाओ निकास;
		पूर्ण
		status = dspxfr_one_seg(codec, fls_data, reloc,
					dma_engine, dma_chan,
					port_map_mask, ovly);
		अगर (status < 0)
			अवरोध;

		अगर (is_hci_prog_list_seg(fls_data))
			fls_data = get_next_seg_ptr(fls_data);

		अगर ((fls_data != शून्य) && !is_last(fls_data))
			fls_data = get_next_seg_ptr(fls_data);
	पूर्ण

	अगर (port_map_mask != 0)
		status = dsp_मुक्त_ports(codec);

	अगर (status < 0)
		जाओ निकास;

	status = codec_set_converter_stream_channel(codec,
				WIDGET_CHIP_CTRL, 0, 0, &response);

निकास:
	अगर (ovly && (dma_chan != INVALID_DMA_CHANNEL))
		dspio_मुक्त_dma_chan(codec, dma_chan);

	अगर (dma_engine->dmab->area)
		snd_hda_codec_load_dsp_cleanup(codec, dma_engine->dmab);
	kमुक्त(dma_engine->dmab);
	kमुक्त(dma_engine);

	वापस status;
पूर्ण

/*
 * CA0132 DSP करोwnload stuffs.
 */
अटल व्योम dspload_post_setup(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	codec_dbg(codec, "---- dspload_post_setup ------\n");
	अगर (!ca0132_use_alt_functions(spec)) अणु
		/*set DSP speaker to 2.0 configuration*/
		chipio_ग_लिखो(codec, XRAM_XRAM_INST_OFFSET(0x18), 0x08080080);
		chipio_ग_लिखो(codec, XRAM_XRAM_INST_OFFSET(0x19), 0x3f800000);

		/*update ग_लिखो poपूर्णांकer*/
		chipio_ग_लिखो(codec, XRAM_XRAM_INST_OFFSET(0x29), 0x00000002);
	पूर्ण
पूर्ण

/**
 * dspload_image - Download DSP from a DSP Image Fast Load काष्ठाure.
 *
 * @codec: the HDA codec
 * @fls: poपूर्णांकer to a fast load image
 * @ovly: TRUE अगर overlay क्रमmat is required
 * @reloc: Relocation address क्रम loading single-segment overlays, or 0 क्रम
 *	   no relocation
 * @स्वतःstart: TRUE अगर DSP starts after loading; ignored अगर ovly is TRUE
 * @router_chans: number of audio router channels to be allocated (0 means use
 *		  पूर्णांकernal शेषs; max is 32)
 *
 * Download DSP from a DSP Image Fast Load काष्ठाure. This काष्ठाure is a
 * linear, non-स्थिरant sized element array of काष्ठाures, each of which
 * contain the count of the data to be loaded, the data itself, and the
 * corresponding starting chip address of the starting data location.
 * Returns zero or a negative error code.
 */
अटल पूर्णांक dspload_image(काष्ठा hda_codec *codec,
			स्थिर काष्ठा dsp_image_seg *fls,
			bool ovly,
			अचिन्हित पूर्णांक reloc,
			bool स्वतःstart,
			पूर्णांक router_chans)
अणु
	पूर्णांक status = 0;
	अचिन्हित पूर्णांक sample_rate;
	अचिन्हित लघु channels;

	codec_dbg(codec, "---- dspload_image begin ------\n");
	अगर (router_chans == 0) अणु
		अगर (!ovly)
			router_chans = DMA_TRANSFER_FRAME_SIZE_NWORDS;
		अन्यथा
			router_chans = DMA_OVERLAY_FRAME_SIZE_NWORDS;
	पूर्ण

	sample_rate = 48000;
	channels = (अचिन्हित लघु)router_chans;

	जबतक (channels > 16) अणु
		sample_rate *= 2;
		channels /= 2;
	पूर्ण

	करो अणु
		codec_dbg(codec, "Ready to program DMA\n");
		अगर (!ovly)
			status = dsp_reset(codec);

		अगर (status < 0)
			अवरोध;

		codec_dbg(codec, "dsp_reset() complete\n");
		status = dspxfr_image(codec, fls, reloc, sample_rate, channels,
				      ovly);

		अगर (status < 0)
			अवरोध;

		codec_dbg(codec, "dspxfr_image() complete\n");
		अगर (स्वतःstart && !ovly) अणु
			dspload_post_setup(codec);
			status = dsp_set_run_state(codec);
		पूर्ण

		codec_dbg(codec, "LOAD FINISHED\n");
	पूर्ण जबतक (0);

	वापस status;
पूर्ण

#अगर_घोषित CONFIG_SND_HDA_CODEC_CA0132_DSP
अटल bool dspload_is_loaded(काष्ठा hda_codec *codec)
अणु
	अचिन्हित पूर्णांक data = 0;
	पूर्णांक status = 0;

	status = chipio_पढ़ो(codec, 0x40004, &data);
	अगर ((status < 0) || (data != 1))
		वापस false;

	वापस true;
पूर्ण
#अन्यथा
#घोषणा dspload_is_loaded(codec)	false
#पूर्ण_अगर

अटल bool dspload_रुको_loaded(काष्ठा hda_codec *codec)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(2000);

	करो अणु
		अगर (dspload_is_loaded(codec)) अणु
			codec_info(codec, "ca0132 DSP downloaded and running\n");
			वापस true;
		पूर्ण
		msleep(20);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	codec_err(codec, "ca0132 failed to download DSP\n");
	वापस false;
पूर्ण

/*
 * ca0113 related functions. The ca0113 acts as the HDA bus क्रम the pci-e
 * based cards, and has a second mmio region, region2, that's used क्रम special
 * commands.
 */

/*
 * For cards with PCI-E region2 (Sound Blaster Z/ZxR, Recon3D, and AE-5)
 * the mmio address 0x320 is used to set GPIO pins. The क्रमmat क्रम the data
 * The first eight bits are just the number of the pin. So far, I've only seen
 * this number go to 7.
 * AE-5 note: The AE-5 seems to use pins 2 and 3 to somehow set the color value
 * of the on-card LED. It seems to use pin 2 क्रम data, then toggles 3 to on and
 * then off to send that bit.
 */
अटल व्योम ca0113_mmio_gpio_set(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक gpio_pin,
		bool enable)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित लघु gpio_data;

	gpio_data = gpio_pin & 0xF;
	gpio_data |= ((enable << 8) & 0x100);

	ग_लिखोw(gpio_data, spec->mem_base + 0x320);
पूर्ण

/*
 * Special pci region2 commands that are only used by the AE-5. They follow
 * a set क्रमmat, and require पढ़ोs at certain poपूर्णांकs to seemingly 'clear'
 * the response data. My first tests didn't करो these पढ़ोs, and would cause
 * the card to get locked up until the memory was पढ़ो. These commands
 * seem to work with three distinct values that I've taken to calling group,
 * target-id, and value.
 */
अटल व्योम ca0113_mmio_command_set(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक group,
		अचिन्हित पूर्णांक target, अचिन्हित पूर्णांक value)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक ग_लिखो_val;

	ग_लिखोl(0x0000007e, spec->mem_base + 0x210);
	पढ़ोl(spec->mem_base + 0x210);
	ग_लिखोl(0x0000005a, spec->mem_base + 0x210);
	पढ़ोl(spec->mem_base + 0x210);
	पढ़ोl(spec->mem_base + 0x210);

	ग_लिखोl(0x00800005, spec->mem_base + 0x20c);
	ग_लिखोl(group, spec->mem_base + 0x804);

	ग_लिखोl(0x00800005, spec->mem_base + 0x20c);
	ग_लिखो_val = (target & 0xff);
	ग_लिखो_val |= (value << 8);


	ग_लिखोl(ग_लिखो_val, spec->mem_base + 0x204);
	/*
	 * Need delay here or अन्यथा it goes too fast and works inconsistently.
	 */
	msleep(20);

	पढ़ोl(spec->mem_base + 0x860);
	पढ़ोl(spec->mem_base + 0x854);
	पढ़ोl(spec->mem_base + 0x840);

	ग_लिखोl(0x00800004, spec->mem_base + 0x20c);
	ग_लिखोl(0x00000000, spec->mem_base + 0x210);
	पढ़ोl(spec->mem_base + 0x210);
	पढ़ोl(spec->mem_base + 0x210);
पूर्ण

/*
 * This second type of command is used क्रम setting the sound filter type.
 */
अटल व्योम ca0113_mmio_command_set_type2(काष्ठा hda_codec *codec,
		अचिन्हित पूर्णांक group, अचिन्हित पूर्णांक target, अचिन्हित पूर्णांक value)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक ग_लिखो_val;

	ग_लिखोl(0x0000007e, spec->mem_base + 0x210);
	पढ़ोl(spec->mem_base + 0x210);
	ग_लिखोl(0x0000005a, spec->mem_base + 0x210);
	पढ़ोl(spec->mem_base + 0x210);
	पढ़ोl(spec->mem_base + 0x210);

	ग_लिखोl(0x00800003, spec->mem_base + 0x20c);
	ग_लिखोl(group, spec->mem_base + 0x804);

	ग_लिखोl(0x00800005, spec->mem_base + 0x20c);
	ग_लिखो_val = (target & 0xff);
	ग_लिखो_val |= (value << 8);


	ग_लिखोl(ग_लिखो_val, spec->mem_base + 0x204);
	msleep(20);
	पढ़ोl(spec->mem_base + 0x860);
	पढ़ोl(spec->mem_base + 0x854);
	पढ़ोl(spec->mem_base + 0x840);

	ग_लिखोl(0x00800004, spec->mem_base + 0x20c);
	ग_लिखोl(0x00000000, spec->mem_base + 0x210);
	पढ़ोl(spec->mem_base + 0x210);
	पढ़ोl(spec->mem_base + 0x210);
पूर्ण

/*
 * Setup GPIO क्रम the other variants of Core3D.
 */

/*
 * Sets up the GPIO pins so that they are discoverable. If this isn't करोne,
 * the card shows as having no GPIO pins.
 */
अटल व्योम ca0132_gpio_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_SBZ:
	हाल QUIRK_AE5:
	हाल QUIRK_AE7:
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, 0x793, 0x00);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, 0x794, 0x53);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, 0x790, 0x23);
		अवरोध;
	हाल QUIRK_R3DI:
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, 0x793, 0x00);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, 0x794, 0x5B);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

पूर्ण

/* Sets the GPIO क्रम audio output. */
अटल व्योम ca0132_gpio_setup(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_SBZ:
		snd_hda_codec_ग_लिखो(codec, 0x01, 0,
				AC_VERB_SET_GPIO_सूचीECTION, 0x07);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0,
				AC_VERB_SET_GPIO_MASK, 0x07);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0,
				AC_VERB_SET_GPIO_DATA, 0x04);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0,
				AC_VERB_SET_GPIO_DATA, 0x06);
		अवरोध;
	हाल QUIRK_R3DI:
		snd_hda_codec_ग_लिखो(codec, 0x01, 0,
				AC_VERB_SET_GPIO_सूचीECTION, 0x1E);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0,
				AC_VERB_SET_GPIO_MASK, 0x1F);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0,
				AC_VERB_SET_GPIO_DATA, 0x0C);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * GPIO control functions क्रम the Recon3D पूर्णांकegrated.
 */

क्रमागत r3di_gpio_bit अणु
	/* Bit 1 - Switch between front/rear mic. 0 = rear, 1 = front */
	R3DI_MIC_SELECT_BIT = 1,
	/* Bit 2 - Switch between headphone/line out. 0 = Headphone, 1 = Line */
	R3DI_OUT_SELECT_BIT = 2,
	/*
	 * I dunno what this actually करोes, but it stays on until the dsp
	 * is करोwnloaded.
	 */
	R3DI_GPIO_DSP_DOWNLOADING = 3,
	/*
	 * Same as above, no clue what it करोes, but it comes on after the dsp
	 * is करोwnloaded.
	 */
	R3DI_GPIO_DSP_DOWNLOADED = 4
पूर्ण;

क्रमागत r3di_mic_select अणु
	/* Set GPIO bit 1 to 0 क्रम rear mic */
	R3DI_REAR_MIC = 0,
	/* Set GPIO bit 1 to 1 क्रम front microphone*/
	R3DI_FRONT_MIC = 1
पूर्ण;

क्रमागत r3di_out_select अणु
	/* Set GPIO bit 2 to 0 क्रम headphone */
	R3DI_HEADPHONE_OUT = 0,
	/* Set GPIO bit 2 to 1 क्रम speaker */
	R3DI_LINE_OUT = 1
पूर्ण;
क्रमागत r3di_dsp_status अणु
	/* Set GPIO bit 3 to 1 until DSP is करोwnloaded */
	R3DI_DSP_DOWNLOADING = 0,
	/* Set GPIO bit 4 to 1 once DSP is करोwnloaded */
	R3DI_DSP_DOWNLOADED = 1
पूर्ण;


अटल व्योम r3di_gpio_mic_set(काष्ठा hda_codec *codec,
		क्रमागत r3di_mic_select cur_mic)
अणु
	अचिन्हित पूर्णांक cur_gpio;

	/* Get the current GPIO Data setup */
	cur_gpio = snd_hda_codec_पढ़ो(codec, 0x01, 0, AC_VERB_GET_GPIO_DATA, 0);

	चयन (cur_mic) अणु
	हाल R3DI_REAR_MIC:
		cur_gpio &= ~(1 << R3DI_MIC_SELECT_BIT);
		अवरोध;
	हाल R3DI_FRONT_MIC:
		cur_gpio |= (1 << R3DI_MIC_SELECT_BIT);
		अवरोध;
	पूर्ण
	snd_hda_codec_ग_लिखो(codec, codec->core.afg, 0,
			    AC_VERB_SET_GPIO_DATA, cur_gpio);
पूर्ण

अटल व्योम r3di_gpio_dsp_status_set(काष्ठा hda_codec *codec,
		क्रमागत r3di_dsp_status dsp_status)
अणु
	अचिन्हित पूर्णांक cur_gpio;

	/* Get the current GPIO Data setup */
	cur_gpio = snd_hda_codec_पढ़ो(codec, 0x01, 0, AC_VERB_GET_GPIO_DATA, 0);

	चयन (dsp_status) अणु
	हाल R3DI_DSP_DOWNLOADING:
		cur_gpio |= (1 << R3DI_GPIO_DSP_DOWNLOADING);
		snd_hda_codec_ग_लिखो(codec, codec->core.afg, 0,
				AC_VERB_SET_GPIO_DATA, cur_gpio);
		अवरोध;
	हाल R3DI_DSP_DOWNLOADED:
		/* Set DOWNLOADING bit to 0. */
		cur_gpio &= ~(1 << R3DI_GPIO_DSP_DOWNLOADING);

		snd_hda_codec_ग_लिखो(codec, codec->core.afg, 0,
				AC_VERB_SET_GPIO_DATA, cur_gpio);

		cur_gpio |= (1 << R3DI_GPIO_DSP_DOWNLOADED);
		अवरोध;
	पूर्ण

	snd_hda_codec_ग_लिखो(codec, codec->core.afg, 0,
			    AC_VERB_SET_GPIO_DATA, cur_gpio);
पूर्ण

/*
 * PCM callbacks
 */
अटल पूर्णांक ca0132_playback_pcm_prepare(काष्ठा hda_pcm_stream *hinfo,
			काष्ठा hda_codec *codec,
			अचिन्हित पूर्णांक stream_tag,
			अचिन्हित पूर्णांक क्रमmat,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	snd_hda_codec_setup_stream(codec, spec->dacs[0], stream_tag, 0, क्रमmat);

	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_playback_pcm_cleanup(काष्ठा hda_pcm_stream *hinfo,
			काष्ठा hda_codec *codec,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	अगर (spec->dsp_state == DSP_DOWNLOADING)
		वापस 0;

	/*If Playback effects are on, allow stream some समय to flush
	 *effects tail*/
	अगर (spec->effects_चयन[PLAY_ENHANCEMENT - EFFECT_START_NID])
		msleep(50);

	snd_hda_codec_cleanup_stream(codec, spec->dacs[0]);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ca0132_playback_pcm_delay(काष्ठा hda_pcm_stream *info,
			काष्ठा hda_codec *codec,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक latency = DSP_PLAYBACK_INIT_LATENCY;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (spec->dsp_state != DSP_DOWNLOADED)
		वापस 0;

	/* Add latency अगर playback enhancement and either effect is enabled. */
	अगर (spec->effects_चयन[PLAY_ENHANCEMENT - EFFECT_START_NID]) अणु
		अगर ((spec->effects_चयन[SURROUND - EFFECT_START_NID]) ||
		    (spec->effects_चयन[DIALOG_PLUS - EFFECT_START_NID]))
			latency += DSP_PLAY_ENHANCEMENT_LATENCY;
	पूर्ण

	/* Applying Speaker EQ adds latency as well. */
	अगर (spec->cur_out_type == SPEAKER_OUT)
		latency += DSP_SPEAKER_OUT_LATENCY;

	वापस (latency * runसमय->rate) / 1000;
पूर्ण

/*
 * Digital out
 */
अटल पूर्णांक ca0132_dig_playback_pcm_खोलो(काष्ठा hda_pcm_stream *hinfo,
					काष्ठा hda_codec *codec,
					काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	वापस snd_hda_multi_out_dig_खोलो(codec, &spec->multiout);
पूर्ण

अटल पूर्णांक ca0132_dig_playback_pcm_prepare(काष्ठा hda_pcm_stream *hinfo,
			काष्ठा hda_codec *codec,
			अचिन्हित पूर्णांक stream_tag,
			अचिन्हित पूर्णांक क्रमmat,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	वापस snd_hda_multi_out_dig_prepare(codec, &spec->multiout,
					     stream_tag, क्रमmat, substream);
पूर्ण

अटल पूर्णांक ca0132_dig_playback_pcm_cleanup(काष्ठा hda_pcm_stream *hinfo,
			काष्ठा hda_codec *codec,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	वापस snd_hda_multi_out_dig_cleanup(codec, &spec->multiout);
पूर्ण

अटल पूर्णांक ca0132_dig_playback_pcm_बंद(काष्ठा hda_pcm_stream *hinfo,
					 काष्ठा hda_codec *codec,
					 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	वापस snd_hda_multi_out_dig_बंद(codec, &spec->multiout);
पूर्ण

/*
 * Analog capture
 */
अटल पूर्णांक ca0132_capture_pcm_prepare(काष्ठा hda_pcm_stream *hinfo,
					काष्ठा hda_codec *codec,
					अचिन्हित पूर्णांक stream_tag,
					अचिन्हित पूर्णांक क्रमmat,
					काष्ठा snd_pcm_substream *substream)
अणु
	snd_hda_codec_setup_stream(codec, hinfo->nid,
				   stream_tag, 0, क्रमmat);

	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_capture_pcm_cleanup(काष्ठा hda_pcm_stream *hinfo,
			काष्ठा hda_codec *codec,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	अगर (spec->dsp_state == DSP_DOWNLOADING)
		वापस 0;

	snd_hda_codec_cleanup_stream(codec, hinfo->nid);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ca0132_capture_pcm_delay(काष्ठा hda_pcm_stream *info,
			काष्ठा hda_codec *codec,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक latency = DSP_CAPTURE_INIT_LATENCY;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (spec->dsp_state != DSP_DOWNLOADED)
		वापस 0;

	अगर (spec->effects_चयन[CRYSTAL_VOICE - EFFECT_START_NID])
		latency += DSP_CRYSTAL_VOICE_LATENCY;

	वापस (latency * runसमय->rate) / 1000;
पूर्ण

/*
 * Controls stuffs.
 */

/*
 * Mixer controls helpers.
 */
#घोषणा CA0132_CODEC_VOL_MONO(xname, nid, channel, dir) \
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	  .name = xname, \
	  .subdevice = HDA_SUBDEV_AMP_FLAG, \
	  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | \
			SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
			SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK, \
	  .info = ca0132_volume_info, \
	  .get = ca0132_volume_get, \
	  .put = ca0132_volume_put, \
	  .tlv = अणु .c = ca0132_volume_tlv पूर्ण, \
	  .निजी_value = HDA_COMPOSE_AMP_VAL(nid, channel, 0, dir) पूर्ण

/*
 * Creates a mixer control that uses शेषs of HDA_CODEC_VOL except क्रम the
 * volume put, which is used क्रम setting the DSP volume. This was करोne because
 * the ca0132 functions were taking too much समय and causing lag.
 */
#घोषणा CA0132_ALT_CODEC_VOL_MONO(xname, nid, channel, dir) \
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	  .name = xname, \
	  .subdevice = HDA_SUBDEV_AMP_FLAG, \
	  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | \
			SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
			SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK, \
	  .info = snd_hda_mixer_amp_volume_info, \
	  .get = snd_hda_mixer_amp_volume_get, \
	  .put = ca0132_alt_volume_put, \
	  .tlv = अणु .c = snd_hda_mixer_amp_tlv पूर्ण, \
	  .निजी_value = HDA_COMPOSE_AMP_VAL(nid, channel, 0, dir) पूर्ण

#घोषणा CA0132_CODEC_MUTE_MONO(xname, nid, channel, dir) \
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	  .name = xname, \
	  .subdevice = HDA_SUBDEV_AMP_FLAG, \
	  .info = snd_hda_mixer_amp_चयन_info, \
	  .get = ca0132_चयन_get, \
	  .put = ca0132_चयन_put, \
	  .निजी_value = HDA_COMPOSE_AMP_VAL(nid, channel, 0, dir) पूर्ण

/* stereo */
#घोषणा CA0132_CODEC_VOL(xname, nid, dir) \
	CA0132_CODEC_VOL_MONO(xname, nid, 3, dir)
#घोषणा CA0132_ALT_CODEC_VOL(xname, nid, dir) \
	CA0132_ALT_CODEC_VOL_MONO(xname, nid, 3, dir)
#घोषणा CA0132_CODEC_MUTE(xname, nid, dir) \
	CA0132_CODEC_MUTE_MONO(xname, nid, 3, dir)

/* lookup tables */
/*
 * Lookup table with decibel values क्रम the DSP. When volume is changed in
 * Winकरोws, the DSP is also sent the dB value in भग्नing poपूर्णांक. In Winकरोws,
 * these values have decimal poपूर्णांकs, probably because the Winकरोws driver
 * actually uses भग्नing poपूर्णांक. We can't here, so I made a lookup table of
 * values -90 to 9. -90 is the lowest decibel value क्रम both the ADC's and the
 * DAC's, and 9 is the maximum.
 */
अटल स्थिर अचिन्हित पूर्णांक भग्न_vol_db_lookup[] = अणु
0xC2B40000, 0xC2B20000, 0xC2B00000, 0xC2AE0000, 0xC2AC0000, 0xC2AA0000,
0xC2A80000, 0xC2A60000, 0xC2A40000, 0xC2A20000, 0xC2A00000, 0xC29E0000,
0xC29C0000, 0xC29A0000, 0xC2980000, 0xC2960000, 0xC2940000, 0xC2920000,
0xC2900000, 0xC28E0000, 0xC28C0000, 0xC28A0000, 0xC2880000, 0xC2860000,
0xC2840000, 0xC2820000, 0xC2800000, 0xC27C0000, 0xC2780000, 0xC2740000,
0xC2700000, 0xC26C0000, 0xC2680000, 0xC2640000, 0xC2600000, 0xC25C0000,
0xC2580000, 0xC2540000, 0xC2500000, 0xC24C0000, 0xC2480000, 0xC2440000,
0xC2400000, 0xC23C0000, 0xC2380000, 0xC2340000, 0xC2300000, 0xC22C0000,
0xC2280000, 0xC2240000, 0xC2200000, 0xC21C0000, 0xC2180000, 0xC2140000,
0xC2100000, 0xC20C0000, 0xC2080000, 0xC2040000, 0xC2000000, 0xC1F80000,
0xC1F00000, 0xC1E80000, 0xC1E00000, 0xC1D80000, 0xC1D00000, 0xC1C80000,
0xC1C00000, 0xC1B80000, 0xC1B00000, 0xC1A80000, 0xC1A00000, 0xC1980000,
0xC1900000, 0xC1880000, 0xC1800000, 0xC1700000, 0xC1600000, 0xC1500000,
0xC1400000, 0xC1300000, 0xC1200000, 0xC1100000, 0xC1000000, 0xC0E00000,
0xC0C00000, 0xC0A00000, 0xC0800000, 0xC0400000, 0xC0000000, 0xBF800000,
0x00000000, 0x3F800000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000,
0x40C00000, 0x40E00000, 0x41000000, 0x41100000
पूर्ण;

/*
 * This table counts from भग्न 0 to 1 in increments of .01, which is
 * useful क्रम a few dअगरferent sliders.
 */
अटल स्थिर अचिन्हित पूर्णांक भग्न_zero_to_one_lookup[] = अणु
0x00000000, 0x3C23D70A, 0x3CA3D70A, 0x3CF5C28F, 0x3D23D70A, 0x3D4CCCCD,
0x3D75C28F, 0x3D8F5C29, 0x3DA3D70A, 0x3DB851EC, 0x3DCCCCCD, 0x3DE147AE,
0x3DF5C28F, 0x3E051EB8, 0x3E0F5C29, 0x3E19999A, 0x3E23D70A, 0x3E2E147B,
0x3E3851EC, 0x3E428F5C, 0x3E4CCCCD, 0x3E570A3D, 0x3E6147AE, 0x3E6B851F,
0x3E75C28F, 0x3E800000, 0x3E851EB8, 0x3E8A3D71, 0x3E8F5C29, 0x3E947AE1,
0x3E99999A, 0x3E9EB852, 0x3EA3D70A, 0x3EA8F5C3, 0x3EAE147B, 0x3EB33333,
0x3EB851EC, 0x3EBD70A4, 0x3EC28F5C, 0x3EC7AE14, 0x3ECCCCCD, 0x3ED1EB85,
0x3ED70A3D, 0x3EDC28F6, 0x3EE147AE, 0x3EE66666, 0x3EEB851F, 0x3EF0A3D7,
0x3EF5C28F, 0x3EFAE148, 0x3F000000, 0x3F028F5C, 0x3F051EB8, 0x3F07AE14,
0x3F0A3D71, 0x3F0CCCCD, 0x3F0F5C29, 0x3F11EB85, 0x3F147AE1, 0x3F170A3D,
0x3F19999A, 0x3F1C28F6, 0x3F1EB852, 0x3F2147AE, 0x3F23D70A, 0x3F266666,
0x3F28F5C3, 0x3F2B851F, 0x3F2E147B, 0x3F30A3D7, 0x3F333333, 0x3F35C28F,
0x3F3851EC, 0x3F3AE148, 0x3F3D70A4, 0x3F400000, 0x3F428F5C, 0x3F451EB8,
0x3F47AE14, 0x3F4A3D71, 0x3F4CCCCD, 0x3F4F5C29, 0x3F51EB85, 0x3F547AE1,
0x3F570A3D, 0x3F59999A, 0x3F5C28F6, 0x3F5EB852, 0x3F6147AE, 0x3F63D70A,
0x3F666666, 0x3F68F5C3, 0x3F6B851F, 0x3F6E147B, 0x3F70A3D7, 0x3F733333,
0x3F75C28F, 0x3F7851EC, 0x3F7AE148, 0x3F7D70A4, 0x3F800000
पूर्ण;

/*
 * This table counts from भग्न 10 to 1000, which is the range of the x-bass
 * crossover slider in Winकरोws.
 */
अटल स्थिर अचिन्हित पूर्णांक भग्न_xbass_xover_lookup[] = अणु
0x41200000, 0x41A00000, 0x41F00000, 0x42200000, 0x42480000, 0x42700000,
0x428C0000, 0x42A00000, 0x42B40000, 0x42C80000, 0x42DC0000, 0x42F00000,
0x43020000, 0x430C0000, 0x43160000, 0x43200000, 0x432A0000, 0x43340000,
0x433E0000, 0x43480000, 0x43520000, 0x435C0000, 0x43660000, 0x43700000,
0x437A0000, 0x43820000, 0x43870000, 0x438C0000, 0x43910000, 0x43960000,
0x439B0000, 0x43A00000, 0x43A50000, 0x43AA0000, 0x43AF0000, 0x43B40000,
0x43B90000, 0x43BE0000, 0x43C30000, 0x43C80000, 0x43CD0000, 0x43D20000,
0x43D70000, 0x43DC0000, 0x43E10000, 0x43E60000, 0x43EB0000, 0x43F00000,
0x43F50000, 0x43FA0000, 0x43FF0000, 0x44020000, 0x44048000, 0x44070000,
0x44098000, 0x440C0000, 0x440E8000, 0x44110000, 0x44138000, 0x44160000,
0x44188000, 0x441B0000, 0x441D8000, 0x44200000, 0x44228000, 0x44250000,
0x44278000, 0x442A0000, 0x442C8000, 0x442F0000, 0x44318000, 0x44340000,
0x44368000, 0x44390000, 0x443B8000, 0x443E0000, 0x44408000, 0x44430000,
0x44458000, 0x44480000, 0x444A8000, 0x444D0000, 0x444F8000, 0x44520000,
0x44548000, 0x44570000, 0x44598000, 0x445C0000, 0x445E8000, 0x44610000,
0x44638000, 0x44660000, 0x44688000, 0x446B0000, 0x446D8000, 0x44700000,
0x44728000, 0x44750000, 0x44778000, 0x447A0000
पूर्ण;

/* The following are क्रम tuning of products */
#अगर_घोषित ENABLE_TUNING_CONTROLS

अटल स्थिर अचिन्हित पूर्णांक voice_focus_vals_lookup[] = अणु
0x41A00000, 0x41A80000, 0x41B00000, 0x41B80000, 0x41C00000, 0x41C80000,
0x41D00000, 0x41D80000, 0x41E00000, 0x41E80000, 0x41F00000, 0x41F80000,
0x42000000, 0x42040000, 0x42080000, 0x420C0000, 0x42100000, 0x42140000,
0x42180000, 0x421C0000, 0x42200000, 0x42240000, 0x42280000, 0x422C0000,
0x42300000, 0x42340000, 0x42380000, 0x423C0000, 0x42400000, 0x42440000,
0x42480000, 0x424C0000, 0x42500000, 0x42540000, 0x42580000, 0x425C0000,
0x42600000, 0x42640000, 0x42680000, 0x426C0000, 0x42700000, 0x42740000,
0x42780000, 0x427C0000, 0x42800000, 0x42820000, 0x42840000, 0x42860000,
0x42880000, 0x428A0000, 0x428C0000, 0x428E0000, 0x42900000, 0x42920000,
0x42940000, 0x42960000, 0x42980000, 0x429A0000, 0x429C0000, 0x429E0000,
0x42A00000, 0x42A20000, 0x42A40000, 0x42A60000, 0x42A80000, 0x42AA0000,
0x42AC0000, 0x42AE0000, 0x42B00000, 0x42B20000, 0x42B40000, 0x42B60000,
0x42B80000, 0x42BA0000, 0x42BC0000, 0x42BE0000, 0x42C00000, 0x42C20000,
0x42C40000, 0x42C60000, 0x42C80000, 0x42CA0000, 0x42CC0000, 0x42CE0000,
0x42D00000, 0x42D20000, 0x42D40000, 0x42D60000, 0x42D80000, 0x42DA0000,
0x42DC0000, 0x42DE0000, 0x42E00000, 0x42E20000, 0x42E40000, 0x42E60000,
0x42E80000, 0x42EA0000, 0x42EC0000, 0x42EE0000, 0x42F00000, 0x42F20000,
0x42F40000, 0x42F60000, 0x42F80000, 0x42FA0000, 0x42FC0000, 0x42FE0000,
0x43000000, 0x43010000, 0x43020000, 0x43030000, 0x43040000, 0x43050000,
0x43060000, 0x43070000, 0x43080000, 0x43090000, 0x430A0000, 0x430B0000,
0x430C0000, 0x430D0000, 0x430E0000, 0x430F0000, 0x43100000, 0x43110000,
0x43120000, 0x43130000, 0x43140000, 0x43150000, 0x43160000, 0x43170000,
0x43180000, 0x43190000, 0x431A0000, 0x431B0000, 0x431C0000, 0x431D0000,
0x431E0000, 0x431F0000, 0x43200000, 0x43210000, 0x43220000, 0x43230000,
0x43240000, 0x43250000, 0x43260000, 0x43270000, 0x43280000, 0x43290000,
0x432A0000, 0x432B0000, 0x432C0000, 0x432D0000, 0x432E0000, 0x432F0000,
0x43300000, 0x43310000, 0x43320000, 0x43330000, 0x43340000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक mic_svm_vals_lookup[] = अणु
0x00000000, 0x3C23D70A, 0x3CA3D70A, 0x3CF5C28F, 0x3D23D70A, 0x3D4CCCCD,
0x3D75C28F, 0x3D8F5C29, 0x3DA3D70A, 0x3DB851EC, 0x3DCCCCCD, 0x3DE147AE,
0x3DF5C28F, 0x3E051EB8, 0x3E0F5C29, 0x3E19999A, 0x3E23D70A, 0x3E2E147B,
0x3E3851EC, 0x3E428F5C, 0x3E4CCCCD, 0x3E570A3D, 0x3E6147AE, 0x3E6B851F,
0x3E75C28F, 0x3E800000, 0x3E851EB8, 0x3E8A3D71, 0x3E8F5C29, 0x3E947AE1,
0x3E99999A, 0x3E9EB852, 0x3EA3D70A, 0x3EA8F5C3, 0x3EAE147B, 0x3EB33333,
0x3EB851EC, 0x3EBD70A4, 0x3EC28F5C, 0x3EC7AE14, 0x3ECCCCCD, 0x3ED1EB85,
0x3ED70A3D, 0x3EDC28F6, 0x3EE147AE, 0x3EE66666, 0x3EEB851F, 0x3EF0A3D7,
0x3EF5C28F, 0x3EFAE148, 0x3F000000, 0x3F028F5C, 0x3F051EB8, 0x3F07AE14,
0x3F0A3D71, 0x3F0CCCCD, 0x3F0F5C29, 0x3F11EB85, 0x3F147AE1, 0x3F170A3D,
0x3F19999A, 0x3F1C28F6, 0x3F1EB852, 0x3F2147AE, 0x3F23D70A, 0x3F266666,
0x3F28F5C3, 0x3F2B851F, 0x3F2E147B, 0x3F30A3D7, 0x3F333333, 0x3F35C28F,
0x3F3851EC, 0x3F3AE148, 0x3F3D70A4, 0x3F400000, 0x3F428F5C, 0x3F451EB8,
0x3F47AE14, 0x3F4A3D71, 0x3F4CCCCD, 0x3F4F5C29, 0x3F51EB85, 0x3F547AE1,
0x3F570A3D, 0x3F59999A, 0x3F5C28F6, 0x3F5EB852, 0x3F6147AE, 0x3F63D70A,
0x3F666666, 0x3F68F5C3, 0x3F6B851F, 0x3F6E147B, 0x3F70A3D7, 0x3F733333,
0x3F75C28F, 0x3F7851EC, 0x3F7AE148, 0x3F7D70A4, 0x3F800000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक equalizer_vals_lookup[] = अणु
0xC1C00000, 0xC1B80000, 0xC1B00000, 0xC1A80000, 0xC1A00000, 0xC1980000,
0xC1900000, 0xC1880000, 0xC1800000, 0xC1700000, 0xC1600000, 0xC1500000,
0xC1400000, 0xC1300000, 0xC1200000, 0xC1100000, 0xC1000000, 0xC0E00000,
0xC0C00000, 0xC0A00000, 0xC0800000, 0xC0400000, 0xC0000000, 0xBF800000,
0x00000000, 0x3F800000, 0x40000000, 0x40400000, 0x40800000, 0x40A00000,
0x40C00000, 0x40E00000, 0x41000000, 0x41100000, 0x41200000, 0x41300000,
0x41400000, 0x41500000, 0x41600000, 0x41700000, 0x41800000, 0x41880000,
0x41900000, 0x41980000, 0x41A00000, 0x41A80000, 0x41B00000, 0x41B80000,
0x41C00000
पूर्ण;

अटल पूर्णांक tuning_ctl_set(काष्ठा hda_codec *codec, hda_nid_t nid,
			  स्थिर अचिन्हित पूर्णांक *lookup, पूर्णांक idx)
अणु
	पूर्णांक i = 0;

	क्रम (i = 0; i < TUNING_CTLS_COUNT; i++)
		अगर (nid == ca0132_tuning_ctls[i].nid)
			अवरोध;

	snd_hda_घातer_up(codec);
	dspio_set_param(codec, ca0132_tuning_ctls[i].mid, 0x20,
			ca0132_tuning_ctls[i].req,
			&(lookup[idx]), माप(अचिन्हित पूर्णांक));
	snd_hda_घातer_करोwn(codec);

	वापस 1;
पूर्ण

अटल पूर्णांक tuning_ctl_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;
	पूर्णांक idx = nid - TUNING_CTL_START_NID;

	*valp = spec->cur_ctl_vals[idx];
	वापस 0;
पूर्ण

अटल पूर्णांक voice_focus_ctl_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक chs = get_amp_channels(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = chs == 3 ? 2 : 1;
	uinfo->value.पूर्णांकeger.min = 20;
	uinfo->value.पूर्णांकeger.max = 180;
	uinfo->value.पूर्णांकeger.step = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक voice_focus_ctl_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;
	पूर्णांक idx;

	idx = nid - TUNING_CTL_START_NID;
	/* any change? */
	अगर (spec->cur_ctl_vals[idx] == *valp)
		वापस 0;

	spec->cur_ctl_vals[idx] = *valp;

	idx = *valp - 20;
	tuning_ctl_set(codec, nid, voice_focus_vals_lookup, idx);

	वापस 1;
पूर्ण

अटल पूर्णांक mic_svm_ctl_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक chs = get_amp_channels(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = chs == 3 ? 2 : 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 100;
	uinfo->value.पूर्णांकeger.step = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mic_svm_ctl_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;
	पूर्णांक idx;

	idx = nid - TUNING_CTL_START_NID;
	/* any change? */
	अगर (spec->cur_ctl_vals[idx] == *valp)
		वापस 0;

	spec->cur_ctl_vals[idx] = *valp;

	idx = *valp;
	tuning_ctl_set(codec, nid, mic_svm_vals_lookup, idx);

	वापस 0;
पूर्ण

अटल पूर्णांक equalizer_ctl_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक chs = get_amp_channels(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = chs == 3 ? 2 : 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 48;
	uinfo->value.पूर्णांकeger.step = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक equalizer_ctl_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;
	पूर्णांक idx;

	idx = nid - TUNING_CTL_START_NID;
	/* any change? */
	अगर (spec->cur_ctl_vals[idx] == *valp)
		वापस 0;

	spec->cur_ctl_vals[idx] = *valp;

	idx = *valp;
	tuning_ctl_set(codec, nid, equalizer_vals_lookup, idx);

	वापस 1;
पूर्ण

अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_SCALE(voice_focus_db_scale, 2000, 100, 0);
अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_SCALE(eq_db_scale, -2400, 100, 0);

अटल पूर्णांक add_tuning_control(काष्ठा hda_codec *codec,
				hda_nid_t pnid, hda_nid_t nid,
				स्थिर अक्षर *name, पूर्णांक dir)
अणु
	अक्षर namestr[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	पूर्णांक type = dir ? HDA_INPUT : HDA_OUTPUT;
	काष्ठा snd_kcontrol_new knew =
		HDA_CODEC_VOLUME_MONO(namestr, nid, 1, 0, type);

	knew.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			SNDRV_CTL_ELEM_ACCESS_TLV_READ;
	knew.tlv.c = 0;
	knew.tlv.p = 0;
	चयन (pnid) अणु
	हाल VOICE_FOCUS:
		knew.info = voice_focus_ctl_info;
		knew.get = tuning_ctl_get;
		knew.put = voice_focus_ctl_put;
		knew.tlv.p = voice_focus_db_scale;
		अवरोध;
	हाल MIC_SVM:
		knew.info = mic_svm_ctl_info;
		knew.get = tuning_ctl_get;
		knew.put = mic_svm_ctl_put;
		अवरोध;
	हाल EQUALIZER:
		knew.info = equalizer_ctl_info;
		knew.get = tuning_ctl_get;
		knew.put = equalizer_ctl_put;
		knew.tlv.p = eq_db_scale;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	knew.निजी_value =
		HDA_COMPOSE_AMP_VAL(nid, 1, 0, type);
	प्र_लिखो(namestr, "%s %s Volume", name, dirstr[dir]);
	वापस snd_hda_ctl_add(codec, nid, snd_ctl_new1(&knew, codec));
पूर्ण

अटल पूर्णांक add_tuning_ctls(काष्ठा hda_codec *codec)
अणु
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < TUNING_CTLS_COUNT; i++) अणु
		err = add_tuning_control(codec,
					ca0132_tuning_ctls[i].parent_nid,
					ca0132_tuning_ctls[i].nid,
					ca0132_tuning_ctls[i].name,
					ca0132_tuning_ctls[i].direct);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ca0132_init_tuning_शेषs(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक i;

	/* Wedge Angle शेषs to 30.  10 below is 30 - 20.  20 is min. */
	spec->cur_ctl_vals[WEDGE_ANGLE - TUNING_CTL_START_NID] = 10;
	/* SVM level शेषs to 0.74. */
	spec->cur_ctl_vals[SVM_LEVEL - TUNING_CTL_START_NID] = 74;

	/* EQ शेषs to 0dB. */
	क्रम (i = 2; i < TUNING_CTLS_COUNT; i++)
		spec->cur_ctl_vals[i] = 24;
पूर्ण
#पूर्ण_अगर /*ENABLE_TUNING_CONTROLS*/

/*
 * Select the active output.
 * If स्वतःdetect is enabled, output will be selected based on jack detection.
 * If jack inserted, headphone will be selected, अन्यथा built-in speakers
 * If स्वतःdetect is disabled, output will be selected based on selection.
 */
अटल पूर्णांक ca0132_select_out(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक pin_ctl;
	पूर्णांक jack_present;
	पूर्णांक स्वतः_jack;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक err;

	codec_dbg(codec, "ca0132_select_out\n");

	snd_hda_घातer_up_pm(codec);

	स्वतः_jack = spec->vnode_lचयन[VNID_HP_ASEL - VNODE_START_NID];

	अगर (स्वतः_jack)
		jack_present = snd_hda_jack_detect(codec, spec->unsol_tag_hp);
	अन्यथा
		jack_present =
			spec->vnode_lचयन[VNID_HP_SEL - VNODE_START_NID];

	अगर (jack_present)
		spec->cur_out_type = HEADPHONE_OUT;
	अन्यथा
		spec->cur_out_type = SPEAKER_OUT;

	अगर (spec->cur_out_type == SPEAKER_OUT) अणु
		codec_dbg(codec, "ca0132_select_out speaker\n");
		/*speaker out config*/
		पंचांगp = FLOAT_ONE;
		err = dspio_set_uपूर्णांक_param(codec, 0x80, 0x04, पंचांगp);
		अगर (err < 0)
			जाओ निकास;
		/*enable speaker EQ*/
		पंचांगp = FLOAT_ONE;
		err = dspio_set_uपूर्णांक_param(codec, 0x8f, 0x00, पंचांगp);
		अगर (err < 0)
			जाओ निकास;

		/* Setup EAPD */
		snd_hda_codec_ग_लिखो(codec, spec->out_pins[1], 0,
				    VENDOR_CHIPIO_EAPD_SEL_SET, 0x02);
		snd_hda_codec_ग_लिखो(codec, spec->out_pins[0], 0,
				    AC_VERB_SET_EAPD_BTLENABLE, 0x00);
		snd_hda_codec_ग_लिखो(codec, spec->out_pins[0], 0,
				    VENDOR_CHIPIO_EAPD_SEL_SET, 0x00);
		snd_hda_codec_ग_लिखो(codec, spec->out_pins[0], 0,
				    AC_VERB_SET_EAPD_BTLENABLE, 0x02);

		/* disable headphone node */
		pin_ctl = snd_hda_codec_पढ़ो(codec, spec->out_pins[1], 0,
					AC_VERB_GET_PIN_WIDGET_CONTROL, 0);
		snd_hda_set_pin_ctl(codec, spec->out_pins[1],
				    pin_ctl & ~PIN_HP);
		/* enable speaker node */
		pin_ctl = snd_hda_codec_पढ़ो(codec, spec->out_pins[0], 0,
				AC_VERB_GET_PIN_WIDGET_CONTROL, 0);
		snd_hda_set_pin_ctl(codec, spec->out_pins[0],
				    pin_ctl | PIN_OUT);
	पूर्ण अन्यथा अणु
		codec_dbg(codec, "ca0132_select_out hp\n");
		/*headphone out config*/
		पंचांगp = FLOAT_ZERO;
		err = dspio_set_uपूर्णांक_param(codec, 0x80, 0x04, पंचांगp);
		अगर (err < 0)
			जाओ निकास;
		/*disable speaker EQ*/
		पंचांगp = FLOAT_ZERO;
		err = dspio_set_uपूर्णांक_param(codec, 0x8f, 0x00, पंचांगp);
		अगर (err < 0)
			जाओ निकास;

		/* Setup EAPD */
		snd_hda_codec_ग_लिखो(codec, spec->out_pins[0], 0,
				    VENDOR_CHIPIO_EAPD_SEL_SET, 0x00);
		snd_hda_codec_ग_लिखो(codec, spec->out_pins[0], 0,
				    AC_VERB_SET_EAPD_BTLENABLE, 0x00);
		snd_hda_codec_ग_लिखो(codec, spec->out_pins[1], 0,
				    VENDOR_CHIPIO_EAPD_SEL_SET, 0x02);
		snd_hda_codec_ग_लिखो(codec, spec->out_pins[0], 0,
				    AC_VERB_SET_EAPD_BTLENABLE, 0x02);

		/* disable speaker*/
		pin_ctl = snd_hda_codec_पढ़ो(codec, spec->out_pins[0], 0,
					AC_VERB_GET_PIN_WIDGET_CONTROL, 0);
		snd_hda_set_pin_ctl(codec, spec->out_pins[0],
				    pin_ctl & ~PIN_HP);
		/* enable headphone*/
		pin_ctl = snd_hda_codec_पढ़ो(codec, spec->out_pins[1], 0,
					AC_VERB_GET_PIN_WIDGET_CONTROL, 0);
		snd_hda_set_pin_ctl(codec, spec->out_pins[1],
				    pin_ctl | PIN_HP);
	पूर्ण

निकास:
	snd_hda_घातer_करोwn_pm(codec);

	वापस err < 0 ? err : 0;
पूर्ण

अटल पूर्णांक ae5_headphone_gain_set(काष्ठा hda_codec *codec, दीर्घ val);
अटल पूर्णांक zxr_headphone_gain_set(काष्ठा hda_codec *codec, दीर्घ val);
अटल पूर्णांक ca0132_effects_set(काष्ठा hda_codec *codec, hda_nid_t nid, दीर्घ val);

अटल व्योम ae5_mmio_select_out(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	स्थिर काष्ठा ae_ca0113_output_set *out_cmds;
	अचिन्हित पूर्णांक i;

	अगर (ca0132_quirk(spec) == QUIRK_AE5)
		out_cmds = &ae5_ca0113_output_presets;
	अन्यथा
		out_cmds = &ae7_ca0113_output_presets;

	क्रम (i = 0; i < AE_CA0113_OUT_SET_COMMANDS; i++)
		ca0113_mmio_command_set(codec, out_cmds->group[i],
				out_cmds->target[i],
				out_cmds->vals[spec->cur_out_type][i]);
पूर्ण

अटल पूर्णांक ca0132_alt_set_full_range_speaker(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक quirk = ca0132_quirk(spec);
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक err;

	/* 2.0/4.0 setup has no LFE channel, so setting full-range करोes nothing. */
	अगर (spec->channel_cfg_val == SPEAKER_CHANNELS_4_0
			|| spec->channel_cfg_val == SPEAKER_CHANNELS_2_0)
		वापस 0;

	/* Set front L/R full range. Zero क्रम full-range, one क्रम redirection. */
	पंचांगp = spec->speaker_range_val[0] ? FLOAT_ZERO : FLOAT_ONE;
	err = dspio_set_uपूर्णांक_param(codec, 0x96,
			SPEAKER_FULL_RANGE_FRONT_L_R, पंचांगp);
	अगर (err < 0)
		वापस err;

	/* When setting full-range rear, both rear and center/lfe are set. */
	पंचांगp = spec->speaker_range_val[1] ? FLOAT_ZERO : FLOAT_ONE;
	err = dspio_set_uपूर्णांक_param(codec, 0x96,
			SPEAKER_FULL_RANGE_CENTER_LFE, पंचांगp);
	अगर (err < 0)
		वापस err;

	err = dspio_set_uपूर्णांक_param(codec, 0x96,
			SPEAKER_FULL_RANGE_REAR_L_R, पंचांगp);
	अगर (err < 0)
		वापस err;

	/*
	 * Only the AE series cards set this value when setting full-range,
	 * and it's always 1.0f.
	 */
	अगर (quirk == QUIRK_AE5 || quirk == QUIRK_AE7) अणु
		err = dspio_set_uपूर्णांक_param(codec, 0x96,
				SPEAKER_FULL_RANGE_SURROUND_L_R, FLOAT_ONE);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_surround_set_bass_redirection(काष्ठा hda_codec *codec,
		bool val)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक err;

	अगर (val && spec->channel_cfg_val != SPEAKER_CHANNELS_4_0 &&
			spec->channel_cfg_val != SPEAKER_CHANNELS_2_0)
		पंचांगp = FLOAT_ONE;
	अन्यथा
		पंचांगp = FLOAT_ZERO;

	err = dspio_set_uपूर्णांक_param(codec, 0x96, SPEAKER_BASS_REसूचीECT, पंचांगp);
	अगर (err < 0)
		वापस err;

	/* If it is enabled, make sure to set the crossover frequency. */
	अगर (पंचांगp) अणु
		पंचांगp = भग्न_xbass_xover_lookup[spec->xbass_xover_freq];
		err = dspio_set_uपूर्णांक_param(codec, 0x96,
				SPEAKER_BASS_REसूचीECT_XOVER_FREQ, पंचांगp);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * These are the commands needed to setup output on each of the dअगरferent card
 * types.
 */
अटल व्योम ca0132_alt_select_out_get_quirk_data(काष्ठा hda_codec *codec,
		स्थिर काष्ठा ca0132_alt_out_set_quirk_data **quirk_data)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक quirk = ca0132_quirk(spec);
	अचिन्हित पूर्णांक i;

	*quirk_data = शून्य;
	क्रम (i = 0; i < ARRAY_SIZE(quirk_out_set_data); i++) अणु
		अगर (quirk_out_set_data[i].quirk_id == quirk) अणु
			*quirk_data = &quirk_out_set_data[i];
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ca0132_alt_select_out_quirk_set(काष्ठा hda_codec *codec)
अणु
	स्थिर काष्ठा ca0132_alt_out_set_quirk_data *quirk_data;
	स्थिर काष्ठा ca0132_alt_out_set_info *out_info;
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक i, gpio_data;
	पूर्णांक err;

	ca0132_alt_select_out_get_quirk_data(codec, &quirk_data);
	अगर (!quirk_data)
		वापस 0;

	out_info = &quirk_data->out_set_info[spec->cur_out_type];
	अगर (quirk_data->is_ae_series)
		ae5_mmio_select_out(codec);

	अगर (out_info->has_hda_gpio) अणु
		gpio_data = snd_hda_codec_पढ़ो(codec, codec->core.afg, 0,
				AC_VERB_GET_GPIO_DATA, 0);

		अगर (out_info->hda_gpio_set)
			gpio_data |= (1 << out_info->hda_gpio_pin);
		अन्यथा
			gpio_data &= ~(1 << out_info->hda_gpio_pin);

		snd_hda_codec_ग_लिखो(codec, codec->core.afg, 0,
				    AC_VERB_SET_GPIO_DATA, gpio_data);
	पूर्ण

	अगर (out_info->mmio_gpio_count) अणु
		क्रम (i = 0; i < out_info->mmio_gpio_count; i++) अणु
			ca0113_mmio_gpio_set(codec, out_info->mmio_gpio_pin[i],
					out_info->mmio_gpio_set[i]);
		पूर्ण
	पूर्ण

	अगर (out_info->scp_cmds_count) अणु
		क्रम (i = 0; i < out_info->scp_cmds_count; i++) अणु
			err = dspio_set_uपूर्णांक_param(codec,
					out_info->scp_cmd_mid[i],
					out_info->scp_cmd_req[i],
					out_info->scp_cmd_val[i]);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	chipio_set_control_param(codec, 0x0d, out_info->dac2port);

	अगर (out_info->has_chipio_ग_लिखो) अणु
		chipio_ग_लिखो(codec, out_info->chipio_ग_लिखो_addr,
				out_info->chipio_ग_लिखो_data);
	पूर्ण

	अगर (quirk_data->has_headphone_gain) अणु
		अगर (spec->cur_out_type != HEADPHONE_OUT) अणु
			अगर (quirk_data->is_ae_series)
				ae5_headphone_gain_set(codec, 2);
			अन्यथा
				zxr_headphone_gain_set(codec, 0);
		पूर्ण अन्यथा अणु
			अगर (quirk_data->is_ae_series)
				ae5_headphone_gain_set(codec,
						spec->ae5_headphone_gain_val);
			अन्यथा
				zxr_headphone_gain_set(codec,
						spec->zxr_gain_set);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ca0132_set_out_node_pincfg(काष्ठा hda_codec *codec, hda_nid_t nid,
		bool out_enable, bool hp_enable)
अणु
	अचिन्हित पूर्णांक pin_ctl;

	pin_ctl = snd_hda_codec_पढ़ो(codec, nid, 0,
			AC_VERB_GET_PIN_WIDGET_CONTROL, 0);

	pin_ctl = hp_enable ? pin_ctl | PIN_HP_AMP : pin_ctl & ~PIN_HP_AMP;
	pin_ctl = out_enable ? pin_ctl | PIN_OUT : pin_ctl & ~PIN_OUT;
	snd_hda_set_pin_ctl(codec, nid, pin_ctl);
पूर्ण

/*
 * This function behaves similarly to the ca0132_select_out funciton above,
 * except with a few dअगरferences. It adds the ability to select the current
 * output with an क्रमागतerated control "output source" अगर the स्वतः detect
 * mute चयन is set to off. If the स्वतः detect mute चयन is enabled, it
 * will detect either headphone or lineout(SPEAKER_OUT) from jack detection.
 * It also adds the ability to स्वतः-detect the front headphone port.
 */
अटल पूर्णांक ca0132_alt_select_out(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक पंचांगp, outfx_set;
	पूर्णांक jack_present;
	पूर्णांक स्वतः_jack;
	पूर्णांक err;
	/* Default Headphone is rear headphone */
	hda_nid_t headphone_nid = spec->out_pins[1];

	codec_dbg(codec, "%s\n", __func__);

	snd_hda_घातer_up_pm(codec);

	स्वतः_jack = spec->vnode_lचयन[VNID_HP_ASEL - VNODE_START_NID];

	/*
	 * If headphone rear or front is plugged in, set to headphone.
	 * If neither is plugged in, set to rear line out. Only अगर
	 * hp/speaker स्वतः detect is enabled.
	 */
	अगर (स्वतः_jack) अणु
		jack_present = snd_hda_jack_detect(codec, spec->unsol_tag_hp) ||
			   snd_hda_jack_detect(codec, spec->unsol_tag_front_hp);

		अगर (jack_present)
			spec->cur_out_type = HEADPHONE_OUT;
		अन्यथा
			spec->cur_out_type = SPEAKER_OUT;
	पूर्ण अन्यथा
		spec->cur_out_type = spec->out_क्रमागत_val;

	outfx_set = spec->effects_चयन[PLAY_ENHANCEMENT - EFFECT_START_NID];

	/* Begin DSP output चयन, mute DSP volume. */
	err = dspio_set_uपूर्णांक_param(codec, 0x96, SPEAKER_TUNING_MUTE, FLOAT_ONE);
	अगर (err < 0)
		जाओ निकास;

	अगर (ca0132_alt_select_out_quirk_set(codec) < 0)
		जाओ निकास;

	चयन (spec->cur_out_type) अणु
	हाल SPEAKER_OUT:
		codec_dbg(codec, "%s speaker\n", __func__);

		/* Enable EAPD */
		snd_hda_codec_ग_लिखो(codec, spec->out_pins[0], 0,
			AC_VERB_SET_EAPD_BTLENABLE, 0x01);

		/* Disable headphone node. */
		ca0132_set_out_node_pincfg(codec, spec->out_pins[1], 0, 0);
		/* Set front L-R to output. */
		ca0132_set_out_node_pincfg(codec, spec->out_pins[0], 1, 0);
		/* Set Center/LFE to output. */
		ca0132_set_out_node_pincfg(codec, spec->out_pins[2], 1, 0);
		/* Set rear surround to output. */
		ca0132_set_out_node_pincfg(codec, spec->out_pins[3], 1, 0);

		/*
		 * Without PlayEnhancement being enabled, अगर we've got a 2.0
		 * setup, set it to भग्नing poपूर्णांक eight to disable any DSP
		 * processing effects.
		 */
		अगर (!outfx_set && spec->channel_cfg_val == SPEAKER_CHANNELS_2_0)
			पंचांगp = FLOAT_EIGHT;
		अन्यथा
			पंचांगp = speaker_channel_cfgs[spec->channel_cfg_val].val;

		err = dspio_set_uपूर्णांक_param(codec, 0x80, 0x04, पंचांगp);
		अगर (err < 0)
			जाओ निकास;

		अवरोध;
	हाल HEADPHONE_OUT:
		codec_dbg(codec, "%s hp\n", __func__);
		snd_hda_codec_ग_लिखो(codec, spec->out_pins[0], 0,
			AC_VERB_SET_EAPD_BTLENABLE, 0x00);

		/* Disable all speaker nodes. */
		ca0132_set_out_node_pincfg(codec, spec->out_pins[0], 0, 0);
		ca0132_set_out_node_pincfg(codec, spec->out_pins[2], 0, 0);
		ca0132_set_out_node_pincfg(codec, spec->out_pins[3], 0, 0);

		/* enable headphone, either front or rear */
		अगर (snd_hda_jack_detect(codec, spec->unsol_tag_front_hp))
			headphone_nid = spec->out_pins[2];
		अन्यथा अगर (snd_hda_jack_detect(codec, spec->unsol_tag_hp))
			headphone_nid = spec->out_pins[1];

		ca0132_set_out_node_pincfg(codec, headphone_nid, 1, 1);

		अगर (outfx_set)
			err = dspio_set_uपूर्णांक_param(codec, 0x80, 0x04, FLOAT_ONE);
		अन्यथा
			err = dspio_set_uपूर्णांक_param(codec, 0x80, 0x04, FLOAT_ZERO);

		अगर (err < 0)
			जाओ निकास;
		अवरोध;
	पूर्ण
	/*
	 * If output effects are enabled, set the X-Bass effect value again to
	 * make sure that it's properly enabled/disabled क्रम speaker
	 * configurations with an LFE channel.
	 */
	अगर (outfx_set)
		ca0132_effects_set(codec, X_BASS,
			spec->effects_चयन[X_BASS - EFFECT_START_NID]);

	/* Set speaker EQ bypass attenuation to 0. */
	err = dspio_set_uपूर्णांक_param(codec, 0x8f, 0x01, FLOAT_ZERO);
	अगर (err < 0)
		जाओ निकास;

	/*
	 * Although unused on all cards but the AE series, this is always set
	 * to zero when setting the output.
	 */
	err = dspio_set_uपूर्णांक_param(codec, 0x96,
			SPEAKER_TUNING_USE_SPEAKER_EQ, FLOAT_ZERO);
	अगर (err < 0)
		जाओ निकास;

	अगर (spec->cur_out_type == SPEAKER_OUT)
		err = ca0132_alt_surround_set_bass_redirection(codec,
				spec->bass_redirection_val);
	अन्यथा
		err = ca0132_alt_surround_set_bass_redirection(codec, 0);

	/* Unmute DSP now that we're करोne with output selection. */
	err = dspio_set_uपूर्णांक_param(codec, 0x96,
			SPEAKER_TUNING_MUTE, FLOAT_ZERO);
	अगर (err < 0)
		जाओ निकास;

	अगर (spec->cur_out_type == SPEAKER_OUT) अणु
		err = ca0132_alt_set_full_range_speaker(codec);
		अगर (err < 0)
			जाओ निकास;
	पूर्ण

निकास:
	snd_hda_घातer_करोwn_pm(codec);

	वापस err < 0 ? err : 0;
पूर्ण

अटल व्योम ca0132_unsol_hp_delayed(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ca0132_spec *spec = container_of(
		to_delayed_work(work), काष्ठा ca0132_spec, unsol_hp_work);
	काष्ठा hda_jack_tbl *jack;

	अगर (ca0132_use_alt_functions(spec))
		ca0132_alt_select_out(spec->codec);
	अन्यथा
		ca0132_select_out(spec->codec);

	jack = snd_hda_jack_tbl_get(spec->codec, spec->unsol_tag_hp);
	अगर (jack) अणु
		jack->block_report = 0;
		snd_hda_jack_report_sync(spec->codec);
	पूर्ण
पूर्ण

अटल व्योम ca0132_set_dmic(काष्ठा hda_codec *codec, पूर्णांक enable);
अटल पूर्णांक ca0132_mic_boost_set(काष्ठा hda_codec *codec, दीर्घ val);
अटल व्योम resume_mic1(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक oldval);
अटल पूर्णांक stop_mic1(काष्ठा hda_codec *codec);
अटल पूर्णांक ca0132_cvoice_चयन_set(काष्ठा hda_codec *codec);
अटल पूर्णांक ca0132_alt_mic_boost_set(काष्ठा hda_codec *codec, दीर्घ val);

/*
 * Select the active VIP source
 */
अटल पूर्णांक ca0132_set_vipsource(काष्ठा hda_codec *codec, पूर्णांक val)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक पंचांगp;

	अगर (spec->dsp_state != DSP_DOWNLOADED)
		वापस 0;

	/* अगर CrystalVoice अगर off, vipsource should be 0 */
	अगर (!spec->effects_चयन[CRYSTAL_VOICE - EFFECT_START_NID] ||
	    (val == 0)) अणु
		chipio_set_control_param(codec, CONTROL_PARAM_VIP_SOURCE, 0);
		chipio_set_conn_rate(codec, MEM_CONNID_MICIN1, SR_96_000);
		chipio_set_conn_rate(codec, MEM_CONNID_MICOUT1, SR_96_000);
		अगर (spec->cur_mic_type == DIGITAL_MIC)
			पंचांगp = FLOAT_TWO;
		अन्यथा
			पंचांगp = FLOAT_ONE;
		dspio_set_uपूर्णांक_param(codec, 0x80, 0x00, पंचांगp);
		पंचांगp = FLOAT_ZERO;
		dspio_set_uपूर्णांक_param(codec, 0x80, 0x05, पंचांगp);
	पूर्ण अन्यथा अणु
		chipio_set_conn_rate(codec, MEM_CONNID_MICIN1, SR_16_000);
		chipio_set_conn_rate(codec, MEM_CONNID_MICOUT1, SR_16_000);
		अगर (spec->cur_mic_type == DIGITAL_MIC)
			पंचांगp = FLOAT_TWO;
		अन्यथा
			पंचांगp = FLOAT_ONE;
		dspio_set_uपूर्णांक_param(codec, 0x80, 0x00, पंचांगp);
		पंचांगp = FLOAT_ONE;
		dspio_set_uपूर्णांक_param(codec, 0x80, 0x05, पंचांगp);
		msleep(20);
		chipio_set_control_param(codec, CONTROL_PARAM_VIP_SOURCE, val);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक ca0132_alt_set_vipsource(काष्ठा hda_codec *codec, पूर्णांक val)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक पंचांगp;

	अगर (spec->dsp_state != DSP_DOWNLOADED)
		वापस 0;

	codec_dbg(codec, "%s\n", __func__);

	chipio_set_stream_control(codec, 0x03, 0);
	chipio_set_stream_control(codec, 0x04, 0);

	/* अगर CrystalVoice is off, vipsource should be 0 */
	अगर (!spec->effects_चयन[CRYSTAL_VOICE - EFFECT_START_NID] ||
	    (val == 0) || spec->in_क्रमागत_val == REAR_LINE_IN) अणु
		codec_dbg(codec, "%s: off.", __func__);
		chipio_set_control_param(codec, CONTROL_PARAM_VIP_SOURCE, 0);

		पंचांगp = FLOAT_ZERO;
		dspio_set_uपूर्णांक_param(codec, 0x80, 0x05, पंचांगp);

		chipio_set_conn_rate(codec, MEM_CONNID_MICIN1, SR_96_000);
		chipio_set_conn_rate(codec, MEM_CONNID_MICOUT1, SR_96_000);
		अगर (ca0132_quirk(spec) == QUIRK_R3DI)
			chipio_set_conn_rate(codec, 0x0F, SR_96_000);


		अगर (spec->in_क्रमागत_val == REAR_LINE_IN)
			पंचांगp = FLOAT_ZERO;
		अन्यथा अणु
			अगर (ca0132_quirk(spec) == QUIRK_SBZ)
				पंचांगp = FLOAT_THREE;
			अन्यथा
				पंचांगp = FLOAT_ONE;
		पूर्ण

		dspio_set_uपूर्णांक_param(codec, 0x80, 0x00, पंचांगp);

	पूर्ण अन्यथा अणु
		codec_dbg(codec, "%s: on.", __func__);
		chipio_set_conn_rate(codec, MEM_CONNID_MICIN1, SR_16_000);
		chipio_set_conn_rate(codec, MEM_CONNID_MICOUT1, SR_16_000);
		अगर (ca0132_quirk(spec) == QUIRK_R3DI)
			chipio_set_conn_rate(codec, 0x0F, SR_16_000);

		अगर (spec->effects_चयन[VOICE_FOCUS - EFFECT_START_NID])
			पंचांगp = FLOAT_TWO;
		अन्यथा
			पंचांगp = FLOAT_ONE;
		dspio_set_uपूर्णांक_param(codec, 0x80, 0x00, पंचांगp);

		पंचांगp = FLOAT_ONE;
		dspio_set_uपूर्णांक_param(codec, 0x80, 0x05, पंचांगp);

		msleep(20);
		chipio_set_control_param(codec, CONTROL_PARAM_VIP_SOURCE, val);
	पूर्ण

	chipio_set_stream_control(codec, 0x03, 1);
	chipio_set_stream_control(codec, 0x04, 1);

	वापस 1;
पूर्ण

/*
 * Select the active microphone.
 * If स्वतःdetect is enabled, mic will be selected based on jack detection.
 * If jack inserted, ext.mic will be selected, अन्यथा built-in mic
 * If स्वतःdetect is disabled, mic will be selected based on selection.
 */
अटल पूर्णांक ca0132_select_mic(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक jack_present;
	पूर्णांक स्वतः_jack;

	codec_dbg(codec, "ca0132_select_mic\n");

	snd_hda_घातer_up_pm(codec);

	स्वतः_jack = spec->vnode_lचयन[VNID_AMIC1_ASEL - VNODE_START_NID];

	अगर (स्वतः_jack)
		jack_present = snd_hda_jack_detect(codec, spec->unsol_tag_amic1);
	अन्यथा
		jack_present =
			spec->vnode_lचयन[VNID_AMIC1_SEL - VNODE_START_NID];

	अगर (jack_present)
		spec->cur_mic_type = LINE_MIC_IN;
	अन्यथा
		spec->cur_mic_type = DIGITAL_MIC;

	अगर (spec->cur_mic_type == DIGITAL_MIC) अणु
		/* enable digital Mic */
		chipio_set_conn_rate(codec, MEM_CONNID_DMIC, SR_32_000);
		ca0132_set_dmic(codec, 1);
		ca0132_mic_boost_set(codec, 0);
		/* set voice focus */
		ca0132_effects_set(codec, VOICE_FOCUS,
				   spec->effects_चयन
				   [VOICE_FOCUS - EFFECT_START_NID]);
	पूर्ण अन्यथा अणु
		/* disable digital Mic */
		chipio_set_conn_rate(codec, MEM_CONNID_DMIC, SR_96_000);
		ca0132_set_dmic(codec, 0);
		ca0132_mic_boost_set(codec, spec->cur_mic_boost);
		/* disable voice focus */
		ca0132_effects_set(codec, VOICE_FOCUS, 0);
	पूर्ण

	snd_hda_घातer_करोwn_pm(codec);

	वापस 0;
पूर्ण

/*
 * Select the active input.
 * Mic detection isn't used, because it's kind of poपूर्णांकless on the SBZ.
 * The front mic has no jack-detection, so the only way to चयन to it
 * is to करो it manually in alsamixer.
 */
अटल पूर्णांक ca0132_alt_select_in(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक पंचांगp;

	codec_dbg(codec, "%s\n", __func__);

	snd_hda_घातer_up_pm(codec);

	chipio_set_stream_control(codec, 0x03, 0);
	chipio_set_stream_control(codec, 0x04, 0);

	spec->cur_mic_type = spec->in_क्रमागत_val;

	चयन (spec->cur_mic_type) अणु
	हाल REAR_MIC:
		चयन (ca0132_quirk(spec)) अणु
		हाल QUIRK_SBZ:
		हाल QUIRK_R3D:
			ca0113_mmio_gpio_set(codec, 0, false);
			पंचांगp = FLOAT_THREE;
			अवरोध;
		हाल QUIRK_ZXR:
			पंचांगp = FLOAT_THREE;
			अवरोध;
		हाल QUIRK_R3DI:
			r3di_gpio_mic_set(codec, R3DI_REAR_MIC);
			पंचांगp = FLOAT_ONE;
			अवरोध;
		हाल QUIRK_AE5:
			ca0113_mmio_command_set(codec, 0x30, 0x28, 0x00);
			पंचांगp = FLOAT_THREE;
			अवरोध;
		हाल QUIRK_AE7:
			ca0113_mmio_command_set(codec, 0x30, 0x28, 0x00);
			पंचांगp = FLOAT_THREE;
			chipio_set_conn_rate(codec, MEM_CONNID_MICIN2,
					SR_96_000);
			chipio_set_conn_rate(codec, MEM_CONNID_MICOUT2,
					SR_96_000);
			dspio_set_uपूर्णांक_param(codec, 0x80, 0x01, FLOAT_ZERO);
			अवरोध;
		शेष:
			पंचांगp = FLOAT_ONE;
			अवरोध;
		पूर्ण

		chipio_set_conn_rate(codec, MEM_CONNID_MICIN1, SR_96_000);
		chipio_set_conn_rate(codec, MEM_CONNID_MICOUT1, SR_96_000);
		अगर (ca0132_quirk(spec) == QUIRK_R3DI)
			chipio_set_conn_rate(codec, 0x0F, SR_96_000);

		dspio_set_uपूर्णांक_param(codec, 0x80, 0x00, पंचांगp);

		chipio_set_stream_control(codec, 0x03, 1);
		chipio_set_stream_control(codec, 0x04, 1);
		चयन (ca0132_quirk(spec)) अणु
		हाल QUIRK_SBZ:
			chipio_ग_लिखो(codec, 0x18B098, 0x0000000C);
			chipio_ग_लिखो(codec, 0x18B09C, 0x0000000C);
			अवरोध;
		हाल QUIRK_ZXR:
			chipio_ग_लिखो(codec, 0x18B098, 0x0000000C);
			chipio_ग_लिखो(codec, 0x18B09C, 0x000000CC);
			अवरोध;
		हाल QUIRK_AE5:
			chipio_ग_लिखो(codec, 0x18B098, 0x0000000C);
			chipio_ग_लिखो(codec, 0x18B09C, 0x0000004C);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		ca0132_alt_mic_boost_set(codec, spec->mic_boost_क्रमागत_val);
		अवरोध;
	हाल REAR_LINE_IN:
		ca0132_mic_boost_set(codec, 0);
		चयन (ca0132_quirk(spec)) अणु
		हाल QUIRK_SBZ:
		हाल QUIRK_R3D:
			ca0113_mmio_gpio_set(codec, 0, false);
			अवरोध;
		हाल QUIRK_R3DI:
			r3di_gpio_mic_set(codec, R3DI_REAR_MIC);
			अवरोध;
		हाल QUIRK_AE5:
			ca0113_mmio_command_set(codec, 0x30, 0x28, 0x00);
			अवरोध;
		हाल QUIRK_AE7:
			ca0113_mmio_command_set(codec, 0x30, 0x28, 0x3f);
			chipio_set_conn_rate(codec, MEM_CONNID_MICIN2,
					SR_96_000);
			chipio_set_conn_rate(codec, MEM_CONNID_MICOUT2,
					SR_96_000);
			dspio_set_uपूर्णांक_param(codec, 0x80, 0x01, FLOAT_ZERO);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		chipio_set_conn_rate(codec, MEM_CONNID_MICIN1, SR_96_000);
		chipio_set_conn_rate(codec, MEM_CONNID_MICOUT1, SR_96_000);
		अगर (ca0132_quirk(spec) == QUIRK_R3DI)
			chipio_set_conn_rate(codec, 0x0F, SR_96_000);

		अगर (ca0132_quirk(spec) == QUIRK_AE7)
			पंचांगp = FLOAT_THREE;
		अन्यथा
			पंचांगp = FLOAT_ZERO;
		dspio_set_uपूर्णांक_param(codec, 0x80, 0x00, पंचांगp);

		चयन (ca0132_quirk(spec)) अणु
		हाल QUIRK_SBZ:
		हाल QUIRK_AE5:
			chipio_ग_लिखो(codec, 0x18B098, 0x00000000);
			chipio_ग_लिखो(codec, 0x18B09C, 0x00000000);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		chipio_set_stream_control(codec, 0x03, 1);
		chipio_set_stream_control(codec, 0x04, 1);
		अवरोध;
	हाल FRONT_MIC:
		चयन (ca0132_quirk(spec)) अणु
		हाल QUIRK_SBZ:
		हाल QUIRK_R3D:
			ca0113_mmio_gpio_set(codec, 0, true);
			ca0113_mmio_gpio_set(codec, 5, false);
			पंचांगp = FLOAT_THREE;
			अवरोध;
		हाल QUIRK_R3DI:
			r3di_gpio_mic_set(codec, R3DI_FRONT_MIC);
			पंचांगp = FLOAT_ONE;
			अवरोध;
		हाल QUIRK_AE5:
			ca0113_mmio_command_set(codec, 0x30, 0x28, 0x3f);
			पंचांगp = FLOAT_THREE;
			अवरोध;
		शेष:
			पंचांगp = FLOAT_ONE;
			अवरोध;
		पूर्ण

		chipio_set_conn_rate(codec, MEM_CONNID_MICIN1, SR_96_000);
		chipio_set_conn_rate(codec, MEM_CONNID_MICOUT1, SR_96_000);
		अगर (ca0132_quirk(spec) == QUIRK_R3DI)
			chipio_set_conn_rate(codec, 0x0F, SR_96_000);

		dspio_set_uपूर्णांक_param(codec, 0x80, 0x00, पंचांगp);

		chipio_set_stream_control(codec, 0x03, 1);
		chipio_set_stream_control(codec, 0x04, 1);

		चयन (ca0132_quirk(spec)) अणु
		हाल QUIRK_SBZ:
			chipio_ग_लिखो(codec, 0x18B098, 0x0000000C);
			chipio_ग_लिखो(codec, 0x18B09C, 0x000000CC);
			अवरोध;
		हाल QUIRK_AE5:
			chipio_ग_लिखो(codec, 0x18B098, 0x0000000C);
			chipio_ग_लिखो(codec, 0x18B09C, 0x0000004C);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		ca0132_alt_mic_boost_set(codec, spec->mic_boost_क्रमागत_val);
		अवरोध;
	पूर्ण
	ca0132_cvoice_चयन_set(codec);

	snd_hda_घातer_करोwn_pm(codec);
	वापस 0;
पूर्ण

/*
 * Check अगर VNODE settings take effect immediately.
 */
अटल bool ca0132_is_vnode_effective(काष्ठा hda_codec *codec,
				     hda_nid_t vnid,
				     hda_nid_t *shared_nid)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid;

	चयन (vnid) अणु
	हाल VNID_SPK:
		nid = spec->shared_out_nid;
		अवरोध;
	हाल VNID_MIC:
		nid = spec->shared_mic_nid;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर (shared_nid)
		*shared_nid = nid;

	वापस true;
पूर्ण

/*
* The following functions are control change helpers.
* They वापस 0 अगर no changed.  Return 1 अगर changed.
*/
अटल पूर्णांक ca0132_voicefx_set(काष्ठा hda_codec *codec, पूर्णांक enable)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक पंचांगp;

	/* based on CrystalVoice state to enable VoiceFX. */
	अगर (enable) अणु
		पंचांगp = spec->effects_चयन[CRYSTAL_VOICE - EFFECT_START_NID] ?
			FLOAT_ONE : FLOAT_ZERO;
	पूर्ण अन्यथा अणु
		पंचांगp = FLOAT_ZERO;
	पूर्ण

	dspio_set_uपूर्णांक_param(codec, ca0132_voicefx.mid,
			     ca0132_voicefx.reqs[0], पंचांगp);

	वापस 1;
पूर्ण

/*
 * Set the effects parameters
 */
अटल पूर्णांक ca0132_effects_set(काष्ठा hda_codec *codec, hda_nid_t nid, दीर्घ val)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक on, पंचांगp, channel_cfg;
	पूर्णांक num_fx = OUT_EFFECTS_COUNT + IN_EFFECTS_COUNT;
	पूर्णांक err = 0;
	पूर्णांक idx = nid - EFFECT_START_NID;

	अगर ((idx < 0) || (idx >= num_fx))
		वापस 0; /* no changed */

	/* क्रम out effect, qualअगरy with PE */
	अगर ((nid >= OUT_EFFECT_START_NID) && (nid < OUT_EFFECT_END_NID)) अणु
		/* अगर PE अगर off, turn off out effects. */
		अगर (!spec->effects_चयन[PLAY_ENHANCEMENT - EFFECT_START_NID])
			val = 0;
		अगर (spec->cur_out_type == SPEAKER_OUT && nid == X_BASS) अणु
			channel_cfg = spec->channel_cfg_val;
			अगर (channel_cfg != SPEAKER_CHANNELS_2_0 &&
					channel_cfg != SPEAKER_CHANNELS_4_0)
				val = 0;
		पूर्ण
	पूर्ण

	/* क्रम in effect, qualअगरy with CrystalVoice */
	अगर ((nid >= IN_EFFECT_START_NID) && (nid < IN_EFFECT_END_NID)) अणु
		/* अगर CrystalVoice अगर off, turn off in effects. */
		अगर (!spec->effects_चयन[CRYSTAL_VOICE - EFFECT_START_NID])
			val = 0;

		/* Voice Focus applies to 2-ch Mic, Digital Mic */
		अगर ((nid == VOICE_FOCUS) && (spec->cur_mic_type != DIGITAL_MIC))
			val = 0;

		/* If Voice Focus on SBZ, set to two channel. */
		अगर ((nid == VOICE_FOCUS) && ca0132_use_pci_mmio(spec)
				&& (spec->cur_mic_type != REAR_LINE_IN)) अणु
			अगर (spec->effects_चयन[CRYSTAL_VOICE -
						 EFFECT_START_NID]) अणु

				अगर (spec->effects_चयन[VOICE_FOCUS -
							 EFFECT_START_NID]) अणु
					पंचांगp = FLOAT_TWO;
					val = 1;
				पूर्ण अन्यथा
					पंचांगp = FLOAT_ONE;

				dspio_set_uपूर्णांक_param(codec, 0x80, 0x00, पंचांगp);
			पूर्ण
		पूर्ण
		/*
		 * For SBZ noise reduction, there's an extra command
		 * to module ID 0x47. No clue why.
		 */
		अगर ((nid == NOISE_REDUCTION) && ca0132_use_pci_mmio(spec)
				&& (spec->cur_mic_type != REAR_LINE_IN)) अणु
			अगर (spec->effects_चयन[CRYSTAL_VOICE -
						 EFFECT_START_NID]) अणु
				अगर (spec->effects_चयन[NOISE_REDUCTION -
							 EFFECT_START_NID])
					पंचांगp = FLOAT_ONE;
				अन्यथा
					पंचांगp = FLOAT_ZERO;
			पूर्ण अन्यथा
				पंचांगp = FLOAT_ZERO;

			dspio_set_uपूर्णांक_param(codec, 0x47, 0x00, पंचांगp);
		पूर्ण

		/* If rear line in disable effects. */
		अगर (ca0132_use_alt_functions(spec) &&
				spec->in_क्रमागत_val == REAR_LINE_IN)
			val = 0;
	पूर्ण

	codec_dbg(codec, "ca0132_effect_set: nid=0x%x, val=%ld\n",
		    nid, val);

	on = (val == 0) ? FLOAT_ZERO : FLOAT_ONE;
	err = dspio_set_uपूर्णांक_param(codec, ca0132_effects[idx].mid,
				   ca0132_effects[idx].reqs[0], on);

	अगर (err < 0)
		वापस 0; /* no changed */

	वापस 1;
पूर्ण

/*
 * Turn on/off Playback Enhancements
 */
अटल पूर्णांक ca0132_pe_चयन_set(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid;
	पूर्णांक i, ret = 0;

	codec_dbg(codec, "ca0132_pe_switch_set: val=%ld\n",
		    spec->effects_चयन[PLAY_ENHANCEMENT - EFFECT_START_NID]);

	अगर (ca0132_use_alt_functions(spec))
		ca0132_alt_select_out(codec);

	i = OUT_EFFECT_START_NID - EFFECT_START_NID;
	nid = OUT_EFFECT_START_NID;
	/* PE affects all out effects */
	क्रम (; nid < OUT_EFFECT_END_NID; nid++, i++)
		ret |= ca0132_effects_set(codec, nid, spec->effects_चयन[i]);

	वापस ret;
पूर्ण

/* Check अगर Mic1 is streaming, अगर so, stop streaming */
अटल पूर्णांक stop_mic1(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक oldval = snd_hda_codec_पढ़ो(codec, spec->adcs[0], 0,
						 AC_VERB_GET_CONV, 0);
	अगर (oldval != 0)
		snd_hda_codec_ग_लिखो(codec, spec->adcs[0], 0,
				    AC_VERB_SET_CHANNEL_STREAMID,
				    0);
	वापस oldval;
पूर्ण

/* Resume Mic1 streaming अगर it was stopped. */
अटल व्योम resume_mic1(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक oldval)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	/* Restore the previous stream and channel */
	अगर (oldval != 0)
		snd_hda_codec_ग_लिखो(codec, spec->adcs[0], 0,
				    AC_VERB_SET_CHANNEL_STREAMID,
				    oldval);
पूर्ण

/*
 * Turn on/off CrystalVoice
 */
अटल पूर्णांक ca0132_cvoice_चयन_set(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid;
	पूर्णांक i, ret = 0;
	अचिन्हित पूर्णांक oldval;

	codec_dbg(codec, "ca0132_cvoice_switch_set: val=%ld\n",
		    spec->effects_चयन[CRYSTAL_VOICE - EFFECT_START_NID]);

	i = IN_EFFECT_START_NID - EFFECT_START_NID;
	nid = IN_EFFECT_START_NID;
	/* CrystalVoice affects all in effects */
	क्रम (; nid < IN_EFFECT_END_NID; nid++, i++)
		ret |= ca0132_effects_set(codec, nid, spec->effects_चयन[i]);

	/* including VoiceFX */
	ret |= ca0132_voicefx_set(codec, (spec->voicefx_val ? 1 : 0));

	/* set correct vipsource */
	oldval = stop_mic1(codec);
	अगर (ca0132_use_alt_functions(spec))
		ret |= ca0132_alt_set_vipsource(codec, 1);
	अन्यथा
		ret |= ca0132_set_vipsource(codec, 1);
	resume_mic1(codec, oldval);
	वापस ret;
पूर्ण

अटल पूर्णांक ca0132_mic_boost_set(काष्ठा hda_codec *codec, दीर्घ val)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक ret = 0;

	अगर (val) /* on */
		ret = snd_hda_codec_amp_update(codec, spec->input_pins[0], 0,
					HDA_INPUT, 0, HDA_AMP_VOLMASK, 3);
	अन्यथा /* off */
		ret = snd_hda_codec_amp_update(codec, spec->input_pins[0], 0,
					HDA_INPUT, 0, HDA_AMP_VOLMASK, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक ca0132_alt_mic_boost_set(काष्ठा hda_codec *codec, दीर्घ val)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक ret = 0;

	ret = snd_hda_codec_amp_update(codec, spec->input_pins[0], 0,
				HDA_INPUT, 0, HDA_AMP_VOLMASK, val);
	वापस ret;
पूर्ण

अटल पूर्णांक ae5_headphone_gain_set(काष्ठा hda_codec *codec, दीर्घ val)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		ca0113_mmio_command_set(codec, 0x48, 0x11 + i,
				ae5_headphone_gain_presets[val].vals[i]);
	वापस 0;
पूर्ण

/*
 * gpio pin 1 is a relay that चयनes on/off, apparently setting the headphone
 * amplअगरier to handle a 600 ohm load.
 */
अटल पूर्णांक zxr_headphone_gain_set(काष्ठा hda_codec *codec, दीर्घ val)
अणु
	ca0113_mmio_gpio_set(codec, 1, val);

	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_vnode_चयन_set(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = get_amp_nid(kcontrol);
	hda_nid_t shared_nid = 0;
	bool effective;
	पूर्णांक ret = 0;
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक स्वतः_jack;

	अगर (nid == VNID_HP_SEL) अणु
		स्वतः_jack =
			spec->vnode_lचयन[VNID_HP_ASEL - VNODE_START_NID];
		अगर (!स्वतः_jack) अणु
			अगर (ca0132_use_alt_functions(spec))
				ca0132_alt_select_out(codec);
			अन्यथा
				ca0132_select_out(codec);
		पूर्ण
		वापस 1;
	पूर्ण

	अगर (nid == VNID_AMIC1_SEL) अणु
		स्वतः_jack =
			spec->vnode_lचयन[VNID_AMIC1_ASEL - VNODE_START_NID];
		अगर (!स्वतः_jack)
			ca0132_select_mic(codec);
		वापस 1;
	पूर्ण

	अगर (nid == VNID_HP_ASEL) अणु
		अगर (ca0132_use_alt_functions(spec))
			ca0132_alt_select_out(codec);
		अन्यथा
			ca0132_select_out(codec);
		वापस 1;
	पूर्ण

	अगर (nid == VNID_AMIC1_ASEL) अणु
		ca0132_select_mic(codec);
		वापस 1;
	पूर्ण

	/* अगर effective conditions, then update hw immediately. */
	effective = ca0132_is_vnode_effective(codec, nid, &shared_nid);
	अगर (effective) अणु
		पूर्णांक dir = get_amp_direction(kcontrol);
		पूर्णांक ch = get_amp_channels(kcontrol);
		अचिन्हित दीर्घ pval;

		mutex_lock(&codec->control_mutex);
		pval = kcontrol->निजी_value;
		kcontrol->निजी_value = HDA_COMPOSE_AMP_VAL(shared_nid, ch,
								0, dir);
		ret = snd_hda_mixer_amp_चयन_put(kcontrol, ucontrol);
		kcontrol->निजी_value = pval;
		mutex_unlock(&codec->control_mutex);
	पूर्ण

	वापस ret;
पूर्ण
/* End of control change helpers. */

अटल व्योम ca0132_alt_bass_redirection_xover_set(काष्ठा hda_codec *codec,
		दीर्घ idx)
अणु
	snd_hda_घातer_up(codec);

	dspio_set_param(codec, 0x96, 0x20, SPEAKER_BASS_REसूचीECT_XOVER_FREQ,
			&(भग्न_xbass_xover_lookup[idx]), माप(अचिन्हित पूर्णांक));

	snd_hda_घातer_करोwn(codec);
पूर्ण

/*
 * Below I've added controls to mess with the effect levels, I've only enabled
 * them on the Sound Blaster Z, but they would probably also work on the
 * Chromebook. I figured they were probably tuned specअगरically क्रम it, and left
 * out क्रम a reason.
 */

/* Sets DSP effect level from the sliders above the controls */

अटल पूर्णांक ca0132_alt_slider_ctl_set(काष्ठा hda_codec *codec, hda_nid_t nid,
			  स्थिर अचिन्हित पूर्णांक *lookup, पूर्णांक idx)
अणु
	पूर्णांक i = 0;
	अचिन्हित पूर्णांक y;
	/*
	 * For X_BASS, req 2 is actually crossover freq instead of
	 * effect level
	 */
	अगर (nid == X_BASS)
		y = 2;
	अन्यथा
		y = 1;

	snd_hda_घातer_up(codec);
	अगर (nid == XBASS_XOVER) अणु
		क्रम (i = 0; i < OUT_EFFECTS_COUNT; i++)
			अगर (ca0132_effects[i].nid == X_BASS)
				अवरोध;

		dspio_set_param(codec, ca0132_effects[i].mid, 0x20,
				ca0132_effects[i].reqs[1],
				&(lookup[idx - 1]), माप(अचिन्हित पूर्णांक));
	पूर्ण अन्यथा अणु
		/* Find the actual effect काष्ठाure */
		क्रम (i = 0; i < OUT_EFFECTS_COUNT; i++)
			अगर (nid == ca0132_effects[i].nid)
				अवरोध;

		dspio_set_param(codec, ca0132_effects[i].mid, 0x20,
				ca0132_effects[i].reqs[y],
				&(lookup[idx]), माप(अचिन्हित पूर्णांक));
	पूर्ण

	snd_hda_घातer_करोwn(codec);

	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_xbass_xover_slider_ctl_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;
	hda_nid_t nid = get_amp_nid(kcontrol);

	अगर (nid == BASS_REसूचीECTION_XOVER)
		*valp = spec->bass_redirect_xover_freq;
	अन्यथा
		*valp = spec->xbass_xover_freq;

	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_slider_ctl_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;
	पूर्णांक idx = nid - OUT_EFFECT_START_NID;

	*valp = spec->fx_ctl_val[idx];
	वापस 0;
पूर्ण

/*
 * The X-bass crossover starts at 10hz, so the min is 1. The
 * frequency is set in multiples of 10.
 */
अटल पूर्णांक ca0132_alt_xbass_xover_slider_info(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 1;
	uinfo->value.पूर्णांकeger.max = 100;
	uinfo->value.पूर्णांकeger.step = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_effect_slider_info(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक chs = get_amp_channels(kcontrol);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = chs == 3 ? 2 : 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 100;
	uinfo->value.पूर्णांकeger.step = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_xbass_xover_slider_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;
	दीर्घ *cur_val;
	पूर्णांक idx;

	अगर (nid == BASS_REसूचीECTION_XOVER)
		cur_val = &spec->bass_redirect_xover_freq;
	अन्यथा
		cur_val = &spec->xbass_xover_freq;

	/* any change? */
	अगर (*cur_val == *valp)
		वापस 0;

	*cur_val = *valp;

	idx = *valp;
	अगर (nid == BASS_REसूचीECTION_XOVER)
		ca0132_alt_bass_redirection_xover_set(codec, *cur_val);
	अन्यथा
		ca0132_alt_slider_ctl_set(codec, nid, भग्न_xbass_xover_lookup, idx);

	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_effect_slider_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;
	पूर्णांक idx;

	idx = nid - EFFECT_START_NID;
	/* any change? */
	अगर (spec->fx_ctl_val[idx] == *valp)
		वापस 0;

	spec->fx_ctl_val[idx] = *valp;

	idx = *valp;
	ca0132_alt_slider_ctl_set(codec, nid, भग्न_zero_to_one_lookup, idx);

	वापस 0;
पूर्ण


/*
 * Mic Boost Enum क्रम alternative ca0132 codecs. I didn't like that the original
 * only has off or full 30 dB, and didn't like making a volume slider that has
 * traditional 0-100 in alsamixer that goes in big steps. I like क्रमागत better.
 */
#घोषणा MIC_BOOST_NUM_OF_STEPS 4
#घोषणा MIC_BOOST_ENUM_MAX_STRLEN 10

अटल पूर्णांक ca0132_alt_mic_boost_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अक्षर *sfx = "dB";
	अक्षर namestr[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = MIC_BOOST_NUM_OF_STEPS;
	अगर (uinfo->value.क्रमागतerated.item >= MIC_BOOST_NUM_OF_STEPS)
		uinfo->value.क्रमागतerated.item = MIC_BOOST_NUM_OF_STEPS - 1;
	प्र_लिखो(namestr, "%d %s", (uinfo->value.क्रमागतerated.item * 10), sfx);
	म_नकल(uinfo->value.क्रमागतerated.name, namestr);
	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_mic_boost_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;

	ucontrol->value.क्रमागतerated.item[0] = spec->mic_boost_क्रमागत_val;
	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_mic_boost_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक sel = ucontrol->value.क्रमागतerated.item[0];
	अचिन्हित पूर्णांक items = MIC_BOOST_NUM_OF_STEPS;

	अगर (sel >= items)
		वापस 0;

	codec_dbg(codec, "ca0132_alt_mic_boost: boost=%d\n",
		    sel);

	spec->mic_boost_क्रमागत_val = sel;

	अगर (spec->in_क्रमागत_val != REAR_LINE_IN)
		ca0132_alt_mic_boost_set(codec, spec->mic_boost_क्रमागत_val);

	वापस 1;
पूर्ण

/*
 * Sound BlasterX AE-5 Headphone Gain Controls.
 */
#घोषणा AE5_HEADPHONE_GAIN_MAX 3
अटल पूर्णांक ae5_headphone_gain_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अक्षर *sfx = " Ohms)";
	अक्षर namestr[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = AE5_HEADPHONE_GAIN_MAX;
	अगर (uinfo->value.क्रमागतerated.item >= AE5_HEADPHONE_GAIN_MAX)
		uinfo->value.क्रमागतerated.item = AE5_HEADPHONE_GAIN_MAX - 1;
	प्र_लिखो(namestr, "%s %s",
		ae5_headphone_gain_presets[uinfo->value.क्रमागतerated.item].name,
		sfx);
	म_नकल(uinfo->value.क्रमागतerated.name, namestr);
	वापस 0;
पूर्ण

अटल पूर्णांक ae5_headphone_gain_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;

	ucontrol->value.क्रमागतerated.item[0] = spec->ae5_headphone_gain_val;
	वापस 0;
पूर्ण

अटल पूर्णांक ae5_headphone_gain_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक sel = ucontrol->value.क्रमागतerated.item[0];
	अचिन्हित पूर्णांक items = AE5_HEADPHONE_GAIN_MAX;

	अगर (sel >= items)
		वापस 0;

	codec_dbg(codec, "ae5_headphone_gain: boost=%d\n",
		    sel);

	spec->ae5_headphone_gain_val = sel;

	अगर (spec->out_क्रमागत_val == HEADPHONE_OUT)
		ae5_headphone_gain_set(codec, spec->ae5_headphone_gain_val);

	वापस 1;
पूर्ण

/*
 * Sound BlasterX AE-5 sound filter क्रमागतerated control.
 */
#घोषणा AE5_SOUND_FILTER_MAX 3

अटल पूर्णांक ae5_sound_filter_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अक्षर namestr[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = AE5_SOUND_FILTER_MAX;
	अगर (uinfo->value.क्रमागतerated.item >= AE5_SOUND_FILTER_MAX)
		uinfo->value.क्रमागतerated.item = AE5_SOUND_FILTER_MAX - 1;
	प्र_लिखो(namestr, "%s",
			ae5_filter_presets[uinfo->value.क्रमागतerated.item].name);
	म_नकल(uinfo->value.क्रमागतerated.name, namestr);
	वापस 0;
पूर्ण

अटल पूर्णांक ae5_sound_filter_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;

	ucontrol->value.क्रमागतerated.item[0] = spec->ae5_filter_val;
	वापस 0;
पूर्ण

अटल पूर्णांक ae5_sound_filter_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक sel = ucontrol->value.क्रमागतerated.item[0];
	अचिन्हित पूर्णांक items = AE5_SOUND_FILTER_MAX;

	अगर (sel >= items)
		वापस 0;

	codec_dbg(codec, "ae5_sound_filter: %s\n",
			ae5_filter_presets[sel].name);

	spec->ae5_filter_val = sel;

	ca0113_mmio_command_set_type2(codec, 0x48, 0x07,
			ae5_filter_presets[sel].val);

	वापस 1;
पूर्ण

/*
 * Input Select Control क्रम alternative ca0132 codecs. This exists because
 * front microphone has no स्वतः-detect, and we need a way to set the rear
 * as line-in
 */
अटल पूर्णांक ca0132_alt_input_source_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = IN_SRC_NUM_OF_INPUTS;
	अगर (uinfo->value.क्रमागतerated.item >= IN_SRC_NUM_OF_INPUTS)
		uinfo->value.क्रमागतerated.item = IN_SRC_NUM_OF_INPUTS - 1;
	म_नकल(uinfo->value.क्रमागतerated.name,
			in_src_str[uinfo->value.क्रमागतerated.item]);
	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_input_source_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;

	ucontrol->value.क्रमागतerated.item[0] = spec->in_क्रमागत_val;
	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_input_source_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक sel = ucontrol->value.क्रमागतerated.item[0];
	अचिन्हित पूर्णांक items = IN_SRC_NUM_OF_INPUTS;

	/*
	 * The AE-7 has no front microphone, so limit items to 2: rear mic and
	 * line-in.
	 */
	अगर (ca0132_quirk(spec) == QUIRK_AE7)
		items = 2;

	अगर (sel >= items)
		वापस 0;

	codec_dbg(codec, "ca0132_alt_input_select: sel=%d, preset=%s\n",
		    sel, in_src_str[sel]);

	spec->in_क्रमागत_val = sel;

	ca0132_alt_select_in(codec);

	वापस 1;
पूर्ण

/* Sound Blaster Z Output Select Control */
अटल पूर्णांक ca0132_alt_output_select_get_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = NUM_OF_OUTPUTS;
	अगर (uinfo->value.क्रमागतerated.item >= NUM_OF_OUTPUTS)
		uinfo->value.क्रमागतerated.item = NUM_OF_OUTPUTS - 1;
	म_नकल(uinfo->value.क्रमागतerated.name,
			out_type_str[uinfo->value.क्रमागतerated.item]);
	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_output_select_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;

	ucontrol->value.क्रमागतerated.item[0] = spec->out_क्रमागत_val;
	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_output_select_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक sel = ucontrol->value.क्रमागतerated.item[0];
	अचिन्हित पूर्णांक items = NUM_OF_OUTPUTS;
	अचिन्हित पूर्णांक स्वतः_jack;

	अगर (sel >= items)
		वापस 0;

	codec_dbg(codec, "ca0132_alt_output_select: sel=%d, preset=%s\n",
		    sel, out_type_str[sel]);

	spec->out_क्रमागत_val = sel;

	स्वतः_jack = spec->vnode_lचयन[VNID_HP_ASEL - VNODE_START_NID];

	अगर (!स्वतः_jack)
		ca0132_alt_select_out(codec);

	वापस 1;
पूर्ण

/* Select surround output type: 2.1, 4.0, 4.1, or 5.1. */
अटल पूर्णांक ca0132_alt_speaker_channel_cfg_get_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अचिन्हित पूर्णांक items = SPEAKER_CHANNEL_CFG_COUNT;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = items;
	अगर (uinfo->value.क्रमागतerated.item >= items)
		uinfo->value.क्रमागतerated.item = items - 1;
	म_नकल(uinfo->value.क्रमागतerated.name,
			speaker_channel_cfgs[uinfo->value.क्रमागतerated.item].name);
	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_speaker_channel_cfg_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;

	ucontrol->value.क्रमागतerated.item[0] = spec->channel_cfg_val;
	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_speaker_channel_cfg_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक sel = ucontrol->value.क्रमागतerated.item[0];
	अचिन्हित पूर्णांक items = SPEAKER_CHANNEL_CFG_COUNT;

	अगर (sel >= items)
		वापस 0;

	codec_dbg(codec, "ca0132_alt_speaker_channels: sel=%d, channels=%s\n",
		    sel, speaker_channel_cfgs[sel].name);

	spec->channel_cfg_val = sel;

	अगर (spec->out_क्रमागत_val == SPEAKER_OUT)
		ca0132_alt_select_out(codec);

	वापस 1;
पूर्ण

/*
 * Smart Volume output setting control. Three dअगरferent settings, Normal,
 * which takes the value from the smart volume slider. The two others, loud
 * and night, disregard the slider value and have uneditable values.
 */
#घोषणा NUM_OF_SVM_SETTINGS 3
अटल स्थिर अक्षर *स्थिर out_svm_set_क्रमागत_str[3] = अणु"Normal", "Loud", "Night" पूर्ण;

अटल पूर्णांक ca0132_alt_svm_setting_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = NUM_OF_SVM_SETTINGS;
	अगर (uinfo->value.क्रमागतerated.item >= NUM_OF_SVM_SETTINGS)
		uinfo->value.क्रमागतerated.item = NUM_OF_SVM_SETTINGS - 1;
	म_नकल(uinfo->value.क्रमागतerated.name,
			out_svm_set_क्रमागत_str[uinfo->value.क्रमागतerated.item]);
	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_svm_setting_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;

	ucontrol->value.क्रमागतerated.item[0] = spec->smart_volume_setting;
	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_svm_setting_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक sel = ucontrol->value.क्रमागतerated.item[0];
	अचिन्हित पूर्णांक items = NUM_OF_SVM_SETTINGS;
	अचिन्हित पूर्णांक idx = SMART_VOLUME - EFFECT_START_NID;
	अचिन्हित पूर्णांक पंचांगp;

	अगर (sel >= items)
		वापस 0;

	codec_dbg(codec, "ca0132_alt_svm_setting: sel=%d, preset=%s\n",
		    sel, out_svm_set_क्रमागत_str[sel]);

	spec->smart_volume_setting = sel;

	चयन (sel) अणु
	हाल 0:
		पंचांगp = FLOAT_ZERO;
		अवरोध;
	हाल 1:
		पंचांगp = FLOAT_ONE;
		अवरोध;
	हाल 2:
		पंचांगp = FLOAT_TWO;
		अवरोध;
	शेष:
		पंचांगp = FLOAT_ZERO;
		अवरोध;
	पूर्ण
	/* Req 2 is the Smart Volume Setting req. */
	dspio_set_uपूर्णांक_param(codec, ca0132_effects[idx].mid,
			ca0132_effects[idx].reqs[2], पंचांगp);
	वापस 1;
पूर्ण

/* Sound Blaster Z EQ preset controls */
अटल पूर्णांक ca0132_alt_eq_preset_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अचिन्हित पूर्णांक items = ARRAY_SIZE(ca0132_alt_eq_presets);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = items;
	अगर (uinfo->value.क्रमागतerated.item >= items)
		uinfo->value.क्रमागतerated.item = items - 1;
	म_नकल(uinfo->value.क्रमागतerated.name,
		ca0132_alt_eq_presets[uinfo->value.क्रमागतerated.item].name);
	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_eq_preset_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;

	ucontrol->value.क्रमागतerated.item[0] = spec->eq_preset_val;
	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_alt_eq_preset_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक i, err = 0;
	पूर्णांक sel = ucontrol->value.क्रमागतerated.item[0];
	अचिन्हित पूर्णांक items = ARRAY_SIZE(ca0132_alt_eq_presets);

	अगर (sel >= items)
		वापस 0;

	codec_dbg(codec, "%s: sel=%d, preset=%s\n", __func__, sel,
			ca0132_alt_eq_presets[sel].name);
	/*
	 * Idx 0 is शेष.
	 * Default needs to qualअगरy with CrystalVoice state.
	 */
	क्रम (i = 0; i < EQ_PRESET_MAX_PARAM_COUNT; i++) अणु
		err = dspio_set_uपूर्णांक_param(codec, ca0132_alt_eq_क्रमागत.mid,
				ca0132_alt_eq_क्रमागत.reqs[i],
				ca0132_alt_eq_presets[sel].vals[i]);
		अगर (err < 0)
			अवरोध;
	पूर्ण

	अगर (err >= 0)
		spec->eq_preset_val = sel;

	वापस 1;
पूर्ण

अटल पूर्णांक ca0132_voicefx_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अचिन्हित पूर्णांक items = ARRAY_SIZE(ca0132_voicefx_presets);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = items;
	अगर (uinfo->value.क्रमागतerated.item >= items)
		uinfo->value.क्रमागतerated.item = items - 1;
	म_नकल(uinfo->value.क्रमागतerated.name,
	       ca0132_voicefx_presets[uinfo->value.क्रमागतerated.item].name);
	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_voicefx_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;

	ucontrol->value.क्रमागतerated.item[0] = spec->voicefx_val;
	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_voicefx_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक i, err = 0;
	पूर्णांक sel = ucontrol->value.क्रमागतerated.item[0];

	अगर (sel >= ARRAY_SIZE(ca0132_voicefx_presets))
		वापस 0;

	codec_dbg(codec, "ca0132_voicefx_put: sel=%d, preset=%s\n",
		    sel, ca0132_voicefx_presets[sel].name);

	/*
	 * Idx 0 is शेष.
	 * Default needs to qualअगरy with CrystalVoice state.
	 */
	क्रम (i = 0; i < VOICEFX_MAX_PARAM_COUNT; i++) अणु
		err = dspio_set_uपूर्णांक_param(codec, ca0132_voicefx.mid,
				ca0132_voicefx.reqs[i],
				ca0132_voicefx_presets[sel].vals[i]);
		अगर (err < 0)
			अवरोध;
	पूर्ण

	अगर (err >= 0) अणु
		spec->voicefx_val = sel;
		/* enable voice fx */
		ca0132_voicefx_set(codec, (sel ? 1 : 0));
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक ca0132_चयन_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	पूर्णांक ch = get_amp_channels(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;

	/* vnode */
	अगर ((nid >= VNODE_START_NID) && (nid < VNODE_END_NID)) अणु
		अगर (ch & 1) अणु
			*valp = spec->vnode_lचयन[nid - VNODE_START_NID];
			valp++;
		पूर्ण
		अगर (ch & 2) अणु
			*valp = spec->vnode_rचयन[nid - VNODE_START_NID];
			valp++;
		पूर्ण
		वापस 0;
	पूर्ण

	/* effects, include PE and CrystalVoice */
	अगर ((nid >= EFFECT_START_NID) && (nid < EFFECT_END_NID)) अणु
		*valp = spec->effects_चयन[nid - EFFECT_START_NID];
		वापस 0;
	पूर्ण

	/* mic boost */
	अगर (nid == spec->input_pins[0]) अणु
		*valp = spec->cur_mic_boost;
		वापस 0;
	पूर्ण

	अगर (nid == ZXR_HEADPHONE_GAIN) अणु
		*valp = spec->zxr_gain_set;
		वापस 0;
	पूर्ण

	अगर (nid == SPEAKER_FULL_RANGE_FRONT || nid == SPEAKER_FULL_RANGE_REAR) अणु
		*valp = spec->speaker_range_val[nid - SPEAKER_FULL_RANGE_FRONT];
		वापस 0;
	पूर्ण

	अगर (nid == BASS_REसूचीECTION) अणु
		*valp = spec->bass_redirection_val;
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_चयन_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	पूर्णांक ch = get_amp_channels(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;
	पूर्णांक changed = 1;

	codec_dbg(codec, "ca0132_switch_put: nid=0x%x, val=%ld\n",
		    nid, *valp);

	snd_hda_घातer_up(codec);
	/* vnode */
	अगर ((nid >= VNODE_START_NID) && (nid < VNODE_END_NID)) अणु
		अगर (ch & 1) अणु
			spec->vnode_lचयन[nid - VNODE_START_NID] = *valp;
			valp++;
		पूर्ण
		अगर (ch & 2) अणु
			spec->vnode_rचयन[nid - VNODE_START_NID] = *valp;
			valp++;
		पूर्ण
		changed = ca0132_vnode_चयन_set(kcontrol, ucontrol);
		जाओ निकास;
	पूर्ण

	/* PE */
	अगर (nid == PLAY_ENHANCEMENT) अणु
		spec->effects_चयन[nid - EFFECT_START_NID] = *valp;
		changed = ca0132_pe_चयन_set(codec);
		जाओ निकास;
	पूर्ण

	/* CrystalVoice */
	अगर (nid == CRYSTAL_VOICE) अणु
		spec->effects_चयन[nid - EFFECT_START_NID] = *valp;
		changed = ca0132_cvoice_चयन_set(codec);
		जाओ निकास;
	पूर्ण

	/* out and in effects */
	अगर (((nid >= OUT_EFFECT_START_NID) && (nid < OUT_EFFECT_END_NID)) ||
	    ((nid >= IN_EFFECT_START_NID) && (nid < IN_EFFECT_END_NID))) अणु
		spec->effects_चयन[nid - EFFECT_START_NID] = *valp;
		changed = ca0132_effects_set(codec, nid, *valp);
		जाओ निकास;
	पूर्ण

	/* mic boost */
	अगर (nid == spec->input_pins[0]) अणु
		spec->cur_mic_boost = *valp;
		अगर (ca0132_use_alt_functions(spec)) अणु
			अगर (spec->in_क्रमागत_val != REAR_LINE_IN)
				changed = ca0132_mic_boost_set(codec, *valp);
		पूर्ण अन्यथा अणु
			/* Mic boost करोes not apply to Digital Mic */
			अगर (spec->cur_mic_type != DIGITAL_MIC)
				changed = ca0132_mic_boost_set(codec, *valp);
		पूर्ण

		जाओ निकास;
	पूर्ण

	अगर (nid == ZXR_HEADPHONE_GAIN) अणु
		spec->zxr_gain_set = *valp;
		अगर (spec->cur_out_type == HEADPHONE_OUT)
			changed = zxr_headphone_gain_set(codec, *valp);
		अन्यथा
			changed = 0;

		जाओ निकास;
	पूर्ण

	अगर (nid == SPEAKER_FULL_RANGE_FRONT || nid == SPEAKER_FULL_RANGE_REAR) अणु
		spec->speaker_range_val[nid - SPEAKER_FULL_RANGE_FRONT] = *valp;
		अगर (spec->cur_out_type == SPEAKER_OUT)
			ca0132_alt_set_full_range_speaker(codec);

		changed = 0;
	पूर्ण

	अगर (nid == BASS_REसूचीECTION) अणु
		spec->bass_redirection_val = *valp;
		अगर (spec->cur_out_type == SPEAKER_OUT)
			ca0132_alt_surround_set_bass_redirection(codec, *valp);

		changed = 0;
	पूर्ण

निकास:
	snd_hda_घातer_करोwn(codec);
	वापस changed;
पूर्ण

/*
 * Volume related
 */
/*
 * Sets the पूर्णांकernal DSP decibel level to match the DAC क्रम output, and the
 * ADC क्रम input. Currently only the SBZ sets dsp capture volume level, and
 * all alternative codecs set DSP playback volume.
 */
अटल व्योम ca0132_alt_dsp_volume_put(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक dsp_dir;
	अचिन्हित पूर्णांक lookup_val;

	अगर (nid == VNID_SPK)
		dsp_dir = DSP_VOL_OUT;
	अन्यथा
		dsp_dir = DSP_VOL_IN;

	lookup_val = spec->vnode_lvol[nid - VNODE_START_NID];

	dspio_set_uपूर्णांक_param(codec,
		ca0132_alt_vol_ctls[dsp_dir].mid,
		ca0132_alt_vol_ctls[dsp_dir].reqs[0],
		भग्न_vol_db_lookup[lookup_val]);

	lookup_val = spec->vnode_rvol[nid - VNODE_START_NID];

	dspio_set_uपूर्णांक_param(codec,
		ca0132_alt_vol_ctls[dsp_dir].mid,
		ca0132_alt_vol_ctls[dsp_dir].reqs[1],
		भग्न_vol_db_lookup[lookup_val]);

	dspio_set_uपूर्णांक_param(codec,
		ca0132_alt_vol_ctls[dsp_dir].mid,
		ca0132_alt_vol_ctls[dsp_dir].reqs[2], FLOAT_ZERO);
पूर्ण

अटल पूर्णांक ca0132_volume_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	पूर्णांक ch = get_amp_channels(kcontrol);
	पूर्णांक dir = get_amp_direction(kcontrol);
	अचिन्हित दीर्घ pval;
	पूर्णांक err;

	चयन (nid) अणु
	हाल VNID_SPK:
		/* follow shared_out info */
		nid = spec->shared_out_nid;
		mutex_lock(&codec->control_mutex);
		pval = kcontrol->निजी_value;
		kcontrol->निजी_value = HDA_COMPOSE_AMP_VAL(nid, ch, 0, dir);
		err = snd_hda_mixer_amp_volume_info(kcontrol, uinfo);
		kcontrol->निजी_value = pval;
		mutex_unlock(&codec->control_mutex);
		अवरोध;
	हाल VNID_MIC:
		/* follow shared_mic info */
		nid = spec->shared_mic_nid;
		mutex_lock(&codec->control_mutex);
		pval = kcontrol->निजी_value;
		kcontrol->निजी_value = HDA_COMPOSE_AMP_VAL(nid, ch, 0, dir);
		err = snd_hda_mixer_amp_volume_info(kcontrol, uinfo);
		kcontrol->निजी_value = pval;
		mutex_unlock(&codec->control_mutex);
		अवरोध;
	शेष:
		err = snd_hda_mixer_amp_volume_info(kcontrol, uinfo);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक ca0132_volume_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	पूर्णांक ch = get_amp_channels(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;

	/* store the left and right volume */
	अगर (ch & 1) अणु
		*valp = spec->vnode_lvol[nid - VNODE_START_NID];
		valp++;
	पूर्ण
	अगर (ch & 2) अणु
		*valp = spec->vnode_rvol[nid - VNODE_START_NID];
		valp++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ca0132_volume_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	पूर्णांक ch = get_amp_channels(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;
	hda_nid_t shared_nid = 0;
	bool effective;
	पूर्णांक changed = 1;

	/* store the left and right volume */
	अगर (ch & 1) अणु
		spec->vnode_lvol[nid - VNODE_START_NID] = *valp;
		valp++;
	पूर्ण
	अगर (ch & 2) अणु
		spec->vnode_rvol[nid - VNODE_START_NID] = *valp;
		valp++;
	पूर्ण

	/* अगर effective conditions, then update hw immediately. */
	effective = ca0132_is_vnode_effective(codec, nid, &shared_nid);
	अगर (effective) अणु
		पूर्णांक dir = get_amp_direction(kcontrol);
		अचिन्हित दीर्घ pval;

		snd_hda_घातer_up(codec);
		mutex_lock(&codec->control_mutex);
		pval = kcontrol->निजी_value;
		kcontrol->निजी_value = HDA_COMPOSE_AMP_VAL(shared_nid, ch,
								0, dir);
		changed = snd_hda_mixer_amp_volume_put(kcontrol, ucontrol);
		kcontrol->निजी_value = pval;
		mutex_unlock(&codec->control_mutex);
		snd_hda_घातer_करोwn(codec);
	पूर्ण

	वापस changed;
पूर्ण

/*
 * This function is the same as the one above, because using an अगर statement
 * inside of the above volume control क्रम the DSP volume would cause too much
 * lag. This is a lot more smooth.
 */
अटल पूर्णांक ca0132_alt_volume_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	पूर्णांक ch = get_amp_channels(kcontrol);
	दीर्घ *valp = ucontrol->value.पूर्णांकeger.value;
	hda_nid_t vnid = 0;
	पूर्णांक changed;

	चयन (nid) अणु
	हाल 0x02:
		vnid = VNID_SPK;
		अवरोध;
	हाल 0x07:
		vnid = VNID_MIC;
		अवरोध;
	पूर्ण

	/* store the left and right volume */
	अगर (ch & 1) अणु
		spec->vnode_lvol[vnid - VNODE_START_NID] = *valp;
		valp++;
	पूर्ण
	अगर (ch & 2) अणु
		spec->vnode_rvol[vnid - VNODE_START_NID] = *valp;
		valp++;
	पूर्ण

	snd_hda_घातer_up(codec);
	ca0132_alt_dsp_volume_put(codec, vnid);
	mutex_lock(&codec->control_mutex);
	changed = snd_hda_mixer_amp_volume_put(kcontrol, ucontrol);
	mutex_unlock(&codec->control_mutex);
	snd_hda_घातer_करोwn(codec);

	वापस changed;
पूर्ण

अटल पूर्णांक ca0132_volume_tlv(काष्ठा snd_kcontrol *kcontrol, पूर्णांक op_flag,
			     अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक __user *tlv)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	पूर्णांक ch = get_amp_channels(kcontrol);
	पूर्णांक dir = get_amp_direction(kcontrol);
	अचिन्हित दीर्घ pval;
	पूर्णांक err;

	चयन (nid) अणु
	हाल VNID_SPK:
		/* follow shared_out tlv */
		nid = spec->shared_out_nid;
		mutex_lock(&codec->control_mutex);
		pval = kcontrol->निजी_value;
		kcontrol->निजी_value = HDA_COMPOSE_AMP_VAL(nid, ch, 0, dir);
		err = snd_hda_mixer_amp_tlv(kcontrol, op_flag, size, tlv);
		kcontrol->निजी_value = pval;
		mutex_unlock(&codec->control_mutex);
		अवरोध;
	हाल VNID_MIC:
		/* follow shared_mic tlv */
		nid = spec->shared_mic_nid;
		mutex_lock(&codec->control_mutex);
		pval = kcontrol->निजी_value;
		kcontrol->निजी_value = HDA_COMPOSE_AMP_VAL(nid, ch, 0, dir);
		err = snd_hda_mixer_amp_tlv(kcontrol, op_flag, size, tlv);
		kcontrol->निजी_value = pval;
		mutex_unlock(&codec->control_mutex);
		अवरोध;
	शेष:
		err = snd_hda_mixer_amp_tlv(kcontrol, op_flag, size, tlv);
	पूर्ण
	वापस err;
पूर्ण

/* Add volume slider control क्रम effect level */
अटल पूर्णांक ca0132_alt_add_effect_slider(काष्ठा hda_codec *codec, hda_nid_t nid,
					स्थिर अक्षर *pfx, पूर्णांक dir)
अणु
	अक्षर namestr[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	पूर्णांक type = dir ? HDA_INPUT : HDA_OUTPUT;
	काष्ठा snd_kcontrol_new knew =
		HDA_CODEC_VOLUME_MONO(namestr, nid, 1, 0, type);

	प्र_लिखो(namestr, "FX: %s %s Volume", pfx, dirstr[dir]);

	knew.tlv.c = शून्य;

	चयन (nid) अणु
	हाल XBASS_XOVER:
		knew.info = ca0132_alt_xbass_xover_slider_info;
		knew.get = ca0132_alt_xbass_xover_slider_ctl_get;
		knew.put = ca0132_alt_xbass_xover_slider_put;
		अवरोध;
	शेष:
		knew.info = ca0132_alt_effect_slider_info;
		knew.get = ca0132_alt_slider_ctl_get;
		knew.put = ca0132_alt_effect_slider_put;
		knew.निजी_value =
			HDA_COMPOSE_AMP_VAL(nid, 1, 0, type);
		अवरोध;
	पूर्ण

	वापस snd_hda_ctl_add(codec, nid, snd_ctl_new1(&knew, codec));
पूर्ण

/*
 * Added FX: prefix क्रम the alternative codecs, because otherwise the surround
 * effect would conflict with the Surround sound volume control. Also seems more
 * clear as to what the चयनes करो. Left alone क्रम others.
 */
अटल पूर्णांक add_fx_चयन(काष्ठा hda_codec *codec, hda_nid_t nid,
			 स्थिर अक्षर *pfx, पूर्णांक dir)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अक्षर namestr[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	पूर्णांक type = dir ? HDA_INPUT : HDA_OUTPUT;
	काष्ठा snd_kcontrol_new knew =
		CA0132_CODEC_MUTE_MONO(namestr, nid, 1, type);
	/* If using alt_controls, add FX: prefix. But, करोn't add FX:
	 * prefix to OutFX or InFX enable controls.
	 */
	अगर (ca0132_use_alt_controls(spec) && (nid <= IN_EFFECT_END_NID))
		प्र_लिखो(namestr, "FX: %s %s Switch", pfx, dirstr[dir]);
	अन्यथा
		प्र_लिखो(namestr, "%s %s Switch", pfx, dirstr[dir]);

	वापस snd_hda_ctl_add(codec, nid, snd_ctl_new1(&knew, codec));
पूर्ण

अटल पूर्णांक add_voicefx(काष्ठा hda_codec *codec)
अणु
	काष्ठा snd_kcontrol_new knew =
		HDA_CODEC_MUTE_MONO(ca0132_voicefx.name,
				    VOICEFX, 1, 0, HDA_INPUT);
	knew.info = ca0132_voicefx_info;
	knew.get = ca0132_voicefx_get;
	knew.put = ca0132_voicefx_put;
	वापस snd_hda_ctl_add(codec, VOICEFX, snd_ctl_new1(&knew, codec));
पूर्ण

/* Create the EQ Preset control */
अटल पूर्णांक add_ca0132_alt_eq_presets(काष्ठा hda_codec *codec)
अणु
	काष्ठा snd_kcontrol_new knew =
		HDA_CODEC_MUTE_MONO(ca0132_alt_eq_क्रमागत.name,
				    EQ_PRESET_ENUM, 1, 0, HDA_OUTPUT);
	knew.info = ca0132_alt_eq_preset_info;
	knew.get = ca0132_alt_eq_preset_get;
	knew.put = ca0132_alt_eq_preset_put;
	वापस snd_hda_ctl_add(codec, EQ_PRESET_ENUM,
				snd_ctl_new1(&knew, codec));
पूर्ण

/*
 * Add क्रमागतerated control क्रम the three dअगरferent settings of the smart volume
 * output effect. Normal just uses the slider value, and loud and night are
 * their own things that ignore that value.
 */
अटल पूर्णांक ca0132_alt_add_svm_क्रमागत(काष्ठा hda_codec *codec)
अणु
	काष्ठा snd_kcontrol_new knew =
		HDA_CODEC_MUTE_MONO("FX: Smart Volume Setting",
				    SMART_VOLUME_ENUM, 1, 0, HDA_OUTPUT);
	knew.info = ca0132_alt_svm_setting_info;
	knew.get = ca0132_alt_svm_setting_get;
	knew.put = ca0132_alt_svm_setting_put;
	वापस snd_hda_ctl_add(codec, SMART_VOLUME_ENUM,
				snd_ctl_new1(&knew, codec));

पूर्ण

/*
 * Create an Output Select क्रमागतerated control क्रम codecs with surround
 * out capabilities.
 */
अटल पूर्णांक ca0132_alt_add_output_क्रमागत(काष्ठा hda_codec *codec)
अणु
	काष्ठा snd_kcontrol_new knew =
		HDA_CODEC_MUTE_MONO("Output Select",
				    OUTPUT_SOURCE_ENUM, 1, 0, HDA_OUTPUT);
	knew.info = ca0132_alt_output_select_get_info;
	knew.get = ca0132_alt_output_select_get;
	knew.put = ca0132_alt_output_select_put;
	वापस snd_hda_ctl_add(codec, OUTPUT_SOURCE_ENUM,
				snd_ctl_new1(&knew, codec));
पूर्ण

/*
 * Add a control क्रम selecting channel count on speaker output. Setting this
 * allows the DSP to करो bass redirection and channel upmixing on surround
 * configurations.
 */
अटल पूर्णांक ca0132_alt_add_speaker_channel_cfg_क्रमागत(काष्ठा hda_codec *codec)
अणु
	काष्ठा snd_kcontrol_new knew =
		HDA_CODEC_MUTE_MONO("Surround Channel Config",
				    SPEAKER_CHANNEL_CFG_ENUM, 1, 0, HDA_OUTPUT);
	knew.info = ca0132_alt_speaker_channel_cfg_get_info;
	knew.get = ca0132_alt_speaker_channel_cfg_get;
	knew.put = ca0132_alt_speaker_channel_cfg_put;
	वापस snd_hda_ctl_add(codec, SPEAKER_CHANNEL_CFG_ENUM,
				snd_ctl_new1(&knew, codec));
पूर्ण

/*
 * Full range front stereo and rear surround चयनes. When these are set to
 * full range, the lower frequencies from these channels are no दीर्घer
 * redirected to the LFE channel.
 */
अटल पूर्णांक ca0132_alt_add_front_full_range_चयन(काष्ठा hda_codec *codec)
अणु
	काष्ठा snd_kcontrol_new knew =
		CA0132_CODEC_MUTE_MONO("Full-Range Front Speakers",
				    SPEAKER_FULL_RANGE_FRONT, 1, HDA_OUTPUT);

	वापस snd_hda_ctl_add(codec, SPEAKER_FULL_RANGE_FRONT,
				snd_ctl_new1(&knew, codec));
पूर्ण

अटल पूर्णांक ca0132_alt_add_rear_full_range_चयन(काष्ठा hda_codec *codec)
अणु
	काष्ठा snd_kcontrol_new knew =
		CA0132_CODEC_MUTE_MONO("Full-Range Rear Speakers",
				    SPEAKER_FULL_RANGE_REAR, 1, HDA_OUTPUT);

	वापस snd_hda_ctl_add(codec, SPEAKER_FULL_RANGE_REAR,
				snd_ctl_new1(&knew, codec));
पूर्ण

/*
 * Bass redirection redirects audio below the crossover frequency to the LFE
 * channel on speakers that are set as not being full-range. On configurations
 * without an LFE channel, it करोes nothing. Bass redirection seems to be the
 * replacement क्रम X-Bass on configurations with an LFE channel.
 */
अटल पूर्णांक ca0132_alt_add_bass_redirection_crossover(काष्ठा hda_codec *codec)
अणु
	स्थिर अक्षर *namestr = "Bass Redirection Crossover";
	काष्ठा snd_kcontrol_new knew =
		HDA_CODEC_VOLUME_MONO(namestr, BASS_REसूचीECTION_XOVER, 1, 0,
				HDA_OUTPUT);

	knew.tlv.c = शून्य;
	knew.info = ca0132_alt_xbass_xover_slider_info;
	knew.get = ca0132_alt_xbass_xover_slider_ctl_get;
	knew.put = ca0132_alt_xbass_xover_slider_put;

	वापस snd_hda_ctl_add(codec, BASS_REसूचीECTION_XOVER,
			snd_ctl_new1(&knew, codec));
पूर्ण

अटल पूर्णांक ca0132_alt_add_bass_redirection_चयन(काष्ठा hda_codec *codec)
अणु
	स्थिर अक्षर *namestr = "Bass Redirection";
	काष्ठा snd_kcontrol_new knew =
		CA0132_CODEC_MUTE_MONO(namestr, BASS_REसूचीECTION, 1,
				HDA_OUTPUT);

	वापस snd_hda_ctl_add(codec, BASS_REसूचीECTION,
			snd_ctl_new1(&knew, codec));
पूर्ण

/*
 * Create an Input Source क्रमागतerated control क्रम the alternate ca0132 codecs
 * because the front microphone has no स्वतः-detect, and Line-in has to be set
 * somehow.
 */
अटल पूर्णांक ca0132_alt_add_input_क्रमागत(काष्ठा hda_codec *codec)
अणु
	काष्ठा snd_kcontrol_new knew =
		HDA_CODEC_MUTE_MONO("Input Source",
				    INPUT_SOURCE_ENUM, 1, 0, HDA_INPUT);
	knew.info = ca0132_alt_input_source_info;
	knew.get = ca0132_alt_input_source_get;
	knew.put = ca0132_alt_input_source_put;
	वापस snd_hda_ctl_add(codec, INPUT_SOURCE_ENUM,
				snd_ctl_new1(&knew, codec));
पूर्ण

/*
 * Add mic boost क्रमागतerated control. Switches through 0dB to 30dB. This adds
 * more control than the original mic boost, which is either full 30dB or off.
 */
अटल पूर्णांक ca0132_alt_add_mic_boost_क्रमागत(काष्ठा hda_codec *codec)
अणु
	काष्ठा snd_kcontrol_new knew =
		HDA_CODEC_MUTE_MONO("Mic Boost Capture Switch",
				    MIC_BOOST_ENUM, 1, 0, HDA_INPUT);
	knew.info = ca0132_alt_mic_boost_info;
	knew.get = ca0132_alt_mic_boost_get;
	knew.put = ca0132_alt_mic_boost_put;
	वापस snd_hda_ctl_add(codec, MIC_BOOST_ENUM,
				snd_ctl_new1(&knew, codec));

पूर्ण

/*
 * Add headphone gain क्रमागतerated control क्रम the AE-5. This चयनes between
 * three modes, low, medium, and high. When non-headphone outमाला_दो are selected,
 * it is स्वतःmatically set to high. This is the same behavior as Winकरोws.
 */
अटल पूर्णांक ae5_add_headphone_gain_क्रमागत(काष्ठा hda_codec *codec)
अणु
	काष्ठा snd_kcontrol_new knew =
		HDA_CODEC_MUTE_MONO("AE-5: Headphone Gain",
				    AE5_HEADPHONE_GAIN_ENUM, 1, 0, HDA_OUTPUT);
	knew.info = ae5_headphone_gain_info;
	knew.get = ae5_headphone_gain_get;
	knew.put = ae5_headphone_gain_put;
	वापस snd_hda_ctl_add(codec, AE5_HEADPHONE_GAIN_ENUM,
				snd_ctl_new1(&knew, codec));
पूर्ण

/*
 * Add sound filter क्रमागतerated control क्रम the AE-5. This adds three dअगरferent
 * settings: Slow Roll Off, Minimum Phase, and Fast Roll Off. From what I've
 * पढ़ो पूर्णांकo it, it changes the DAC's पूर्णांकerpolation filter.
 */
अटल पूर्णांक ae5_add_sound_filter_क्रमागत(काष्ठा hda_codec *codec)
अणु
	काष्ठा snd_kcontrol_new knew =
		HDA_CODEC_MUTE_MONO("AE-5: Sound Filter",
				    AE5_SOUND_FILTER_ENUM, 1, 0, HDA_OUTPUT);
	knew.info = ae5_sound_filter_info;
	knew.get = ae5_sound_filter_get;
	knew.put = ae5_sound_filter_put;
	वापस snd_hda_ctl_add(codec, AE5_SOUND_FILTER_ENUM,
				snd_ctl_new1(&knew, codec));
पूर्ण

अटल पूर्णांक zxr_add_headphone_gain_चयन(काष्ठा hda_codec *codec)
अणु
	काष्ठा snd_kcontrol_new knew =
		CA0132_CODEC_MUTE_MONO("ZxR: 600 Ohm Gain",
				    ZXR_HEADPHONE_GAIN, 1, HDA_OUTPUT);

	वापस snd_hda_ctl_add(codec, ZXR_HEADPHONE_GAIN,
				snd_ctl_new1(&knew, codec));
पूर्ण

/*
 * Need to create follower controls क्रम the alternate codecs that have surround
 * capabilities.
 */
अटल स्थिर अक्षर * स्थिर ca0132_alt_follower_pfxs[] = अणु
	"Front", "Surround", "Center", "LFE", शून्य,
पूर्ण;

/*
 * Also need special channel map, because the शेष one is incorrect.
 * I think this has to करो with the pin क्रम rear surround being 0x11,
 * and the center/lfe being 0x10. Usually the pin order is the opposite.
 */
अटल स्थिर काष्ठा snd_pcm_chmap_elem ca0132_alt_chmaps[] = अणु
	अणु .channels = 2,
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR पूर्ण पूर्ण,
	अणु .channels = 4,
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR,
		   SNDRV_CHMAP_RL, SNDRV_CHMAP_RR पूर्ण पूर्ण,
	अणु .channels = 6,
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_RL, SNDRV_CHMAP_RR पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;

/* Add the correct chmap क्रम streams with 6 channels. */
अटल व्योम ca0132_alt_add_chmap_ctls(काष्ठा hda_codec *codec)
अणु
	पूर्णांक err = 0;
	काष्ठा hda_pcm *pcm;

	list_क्रम_each_entry(pcm, &codec->pcm_list_head, list) अणु
		काष्ठा hda_pcm_stream *hinfo =
			&pcm->stream[SNDRV_PCM_STREAM_PLAYBACK];
		काष्ठा snd_pcm_chmap *chmap;
		स्थिर काष्ठा snd_pcm_chmap_elem *elem;

		elem = ca0132_alt_chmaps;
		अगर (hinfo->channels_max == 6) अणु
			err = snd_pcm_add_chmap_ctls(pcm->pcm,
					SNDRV_PCM_STREAM_PLAYBACK,
					elem, hinfo->channels_max, 0, &chmap);
			अगर (err < 0)
				codec_dbg(codec, "snd_pcm_add_chmap_ctls failed!");
		पूर्ण
	पूर्ण
पूर्ण

/*
 * When changing Node IDs क्रम Mixer Controls below, make sure to update
 * Node IDs in ca0132_config() as well.
 */
अटल स्थिर काष्ठा snd_kcontrol_new ca0132_mixer[] = अणु
	CA0132_CODEC_VOL("Master Playback Volume", VNID_SPK, HDA_OUTPUT),
	CA0132_CODEC_MUTE("Master Playback Switch", VNID_SPK, HDA_OUTPUT),
	CA0132_CODEC_VOL("Capture Volume", VNID_MIC, HDA_INPUT),
	CA0132_CODEC_MUTE("Capture Switch", VNID_MIC, HDA_INPUT),
	HDA_CODEC_VOLUME("Analog-Mic2 Capture Volume", 0x08, 0, HDA_INPUT),
	HDA_CODEC_MUTE("Analog-Mic2 Capture Switch", 0x08, 0, HDA_INPUT),
	HDA_CODEC_VOLUME("What U Hear Capture Volume", 0x0a, 0, HDA_INPUT),
	HDA_CODEC_MUTE("What U Hear Capture Switch", 0x0a, 0, HDA_INPUT),
	CA0132_CODEC_MUTE_MONO("Mic1-Boost (30dB) Capture Switch",
			       0x12, 1, HDA_INPUT),
	CA0132_CODEC_MUTE_MONO("HP/Speaker Playback Switch",
			       VNID_HP_SEL, 1, HDA_OUTPUT),
	CA0132_CODEC_MUTE_MONO("AMic1/DMic Capture Switch",
			       VNID_AMIC1_SEL, 1, HDA_INPUT),
	CA0132_CODEC_MUTE_MONO("HP/Speaker Auto Detect Playback Switch",
			       VNID_HP_ASEL, 1, HDA_OUTPUT),
	CA0132_CODEC_MUTE_MONO("AMic1/DMic Auto Detect Capture Switch",
			       VNID_AMIC1_ASEL, 1, HDA_INPUT),
	अणु पूर्ण /* end */
पूर्ण;

/*
 * Desktop specअगरic control mixer. Removes स्वतः-detect क्रम mic, and adds
 * surround controls. Also sets both the Front Playback and Capture Volume
 * controls to alt so they set the DSP's decibel level.
 */
अटल स्थिर काष्ठा snd_kcontrol_new desktop_mixer[] = अणु
	CA0132_ALT_CODEC_VOL("Front Playback Volume", 0x02, HDA_OUTPUT),
	CA0132_CODEC_MUTE("Front Playback Switch", VNID_SPK, HDA_OUTPUT),
	HDA_CODEC_VOLUME("Surround Playback Volume", 0x04, 0, HDA_OUTPUT),
	HDA_CODEC_MUTE("Surround Playback Switch", 0x04, 0, HDA_OUTPUT),
	HDA_CODEC_VOLUME_MONO("Center Playback Volume", 0x03, 1, 0, HDA_OUTPUT),
	HDA_CODEC_MUTE_MONO("Center Playback Switch", 0x03, 1, 0, HDA_OUTPUT),
	HDA_CODEC_VOLUME_MONO("LFE Playback Volume", 0x03, 2, 0, HDA_OUTPUT),
	HDA_CODEC_MUTE_MONO("LFE Playback Switch", 0x03, 2, 0, HDA_OUTPUT),
	CA0132_ALT_CODEC_VOL("Capture Volume", 0x07, HDA_INPUT),
	CA0132_CODEC_MUTE("Capture Switch", VNID_MIC, HDA_INPUT),
	HDA_CODEC_VOLUME("What U Hear Capture Volume", 0x0a, 0, HDA_INPUT),
	HDA_CODEC_MUTE("What U Hear Capture Switch", 0x0a, 0, HDA_INPUT),
	CA0132_CODEC_MUTE_MONO("HP/Speaker Auto Detect Playback Switch",
				VNID_HP_ASEL, 1, HDA_OUTPUT),
	अणु पूर्ण /* end */
पूर्ण;

/*
 * Same as the Sound Blaster Z, except करोesn't use the alt volume क्रम capture
 * because it करोesn't set decibel levels क्रम the DSP क्रम capture.
 */
अटल स्थिर काष्ठा snd_kcontrol_new r3di_mixer[] = अणु
	CA0132_ALT_CODEC_VOL("Front Playback Volume", 0x02, HDA_OUTPUT),
	CA0132_CODEC_MUTE("Front Playback Switch", VNID_SPK, HDA_OUTPUT),
	HDA_CODEC_VOLUME("Surround Playback Volume", 0x04, 0, HDA_OUTPUT),
	HDA_CODEC_MUTE("Surround Playback Switch", 0x04, 0, HDA_OUTPUT),
	HDA_CODEC_VOLUME_MONO("Center Playback Volume", 0x03, 1, 0, HDA_OUTPUT),
	HDA_CODEC_MUTE_MONO("Center Playback Switch", 0x03, 1, 0, HDA_OUTPUT),
	HDA_CODEC_VOLUME_MONO("LFE Playback Volume", 0x03, 2, 0, HDA_OUTPUT),
	HDA_CODEC_MUTE_MONO("LFE Playback Switch", 0x03, 2, 0, HDA_OUTPUT),
	CA0132_CODEC_VOL("Capture Volume", VNID_MIC, HDA_INPUT),
	CA0132_CODEC_MUTE("Capture Switch", VNID_MIC, HDA_INPUT),
	HDA_CODEC_VOLUME("What U Hear Capture Volume", 0x0a, 0, HDA_INPUT),
	HDA_CODEC_MUTE("What U Hear Capture Switch", 0x0a, 0, HDA_INPUT),
	CA0132_CODEC_MUTE_MONO("HP/Speaker Auto Detect Playback Switch",
				VNID_HP_ASEL, 1, HDA_OUTPUT),
	अणु पूर्ण /* end */
पूर्ण;

अटल पूर्णांक ca0132_build_controls(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक i, num_fx, num_sliders;
	पूर्णांक err = 0;

	/* Add Mixer controls */
	क्रम (i = 0; i < spec->num_mixers; i++) अणु
		err = snd_hda_add_new_ctls(codec, spec->mixers[i]);
		अगर (err < 0)
			वापस err;
	पूर्ण
	/* Setup vmaster with surround followers क्रम desktop ca0132 devices */
	अगर (ca0132_use_alt_functions(spec)) अणु
		snd_hda_set_vmaster_tlv(codec, spec->dacs[0], HDA_OUTPUT,
					spec->tlv);
		snd_hda_add_vmaster(codec, "Master Playback Volume",
					spec->tlv, ca0132_alt_follower_pfxs,
					"Playback Volume", 0);
		err = __snd_hda_add_vmaster(codec, "Master Playback Switch",
					    शून्य, ca0132_alt_follower_pfxs,
					    "Playback Switch",
					    true, 0, &spec->vmaster_mute.sw_kctl);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* Add in and out effects controls.
	 * VoiceFX, PE and CrystalVoice are added separately.
	 */
	num_fx = OUT_EFFECTS_COUNT + IN_EFFECTS_COUNT;
	क्रम (i = 0; i < num_fx; i++) अणु
		/* Desktop cards अवरोध अगर Echo Cancellation is used. */
		अगर (ca0132_use_pci_mmio(spec)) अणु
			अगर (i == (ECHO_CANCELLATION - IN_EFFECT_START_NID +
						OUT_EFFECTS_COUNT))
				जारी;
		पूर्ण

		err = add_fx_चयन(codec, ca0132_effects[i].nid,
				    ca0132_effects[i].name,
				    ca0132_effects[i].direct);
		अगर (err < 0)
			वापस err;
	पूर्ण
	/*
	 * If codec has use_alt_controls set to true, add effect level sliders,
	 * EQ presets, and Smart Volume presets. Also, change names to add FX
	 * prefix, and change PlayEnhancement and CrystalVoice to match.
	 */
	अगर (ca0132_use_alt_controls(spec)) अणु
		err = ca0132_alt_add_svm_क्रमागत(codec);
		अगर (err < 0)
			वापस err;

		err = add_ca0132_alt_eq_presets(codec);
		अगर (err < 0)
			वापस err;

		err = add_fx_चयन(codec, PLAY_ENHANCEMENT,
					"Enable OutFX", 0);
		अगर (err < 0)
			वापस err;

		err = add_fx_चयन(codec, CRYSTAL_VOICE,
					"Enable InFX", 1);
		अगर (err < 0)
			वापस err;

		num_sliders = OUT_EFFECTS_COUNT - 1;
		क्रम (i = 0; i < num_sliders; i++) अणु
			err = ca0132_alt_add_effect_slider(codec,
					    ca0132_effects[i].nid,
					    ca0132_effects[i].name,
					    ca0132_effects[i].direct);
			अगर (err < 0)
				वापस err;
		पूर्ण

		err = ca0132_alt_add_effect_slider(codec, XBASS_XOVER,
					"X-Bass Crossover", EFX_सूची_OUT);

		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		err = add_fx_चयन(codec, PLAY_ENHANCEMENT,
					"PlayEnhancement", 0);
		अगर (err < 0)
			वापस err;

		err = add_fx_चयन(codec, CRYSTAL_VOICE,
					"CrystalVoice", 1);
		अगर (err < 0)
			वापस err;
	पूर्ण
	err = add_voicefx(codec);
	अगर (err < 0)
		वापस err;

	/*
	 * If the codec uses alt_functions, you need the क्रमागतerated controls
	 * to select the new outमाला_दो and inमाला_दो, plus add the new mic boost
	 * setting control.
	 */
	अगर (ca0132_use_alt_functions(spec)) अणु
		err = ca0132_alt_add_output_क्रमागत(codec);
		अगर (err < 0)
			वापस err;
		err = ca0132_alt_add_speaker_channel_cfg_क्रमागत(codec);
		अगर (err < 0)
			वापस err;
		err = ca0132_alt_add_front_full_range_चयन(codec);
		अगर (err < 0)
			वापस err;
		err = ca0132_alt_add_rear_full_range_चयन(codec);
		अगर (err < 0)
			वापस err;
		err = ca0132_alt_add_bass_redirection_crossover(codec);
		अगर (err < 0)
			वापस err;
		err = ca0132_alt_add_bass_redirection_चयन(codec);
		अगर (err < 0)
			वापस err;
		err = ca0132_alt_add_mic_boost_क्रमागत(codec);
		अगर (err < 0)
			वापस err;
		/*
		 * ZxR only has microphone input, there is no front panel
		 * header on the card, and aux-in is handled by the DBPro board.
		 */
		अगर (ca0132_quirk(spec) != QUIRK_ZXR) अणु
			err = ca0132_alt_add_input_क्रमागत(codec);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_AE5:
	हाल QUIRK_AE7:
		err = ae5_add_headphone_gain_क्रमागत(codec);
		अगर (err < 0)
			वापस err;
		err = ae5_add_sound_filter_क्रमागत(codec);
		अगर (err < 0)
			वापस err;
		अवरोध;
	हाल QUIRK_ZXR:
		err = zxr_add_headphone_gain_चयन(codec);
		अगर (err < 0)
			वापस err;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

#अगर_घोषित ENABLE_TUNING_CONTROLS
	add_tuning_ctls(codec);
#पूर्ण_अगर

	err = snd_hda_jack_add_kctls(codec, &spec->स्वतःcfg);
	अगर (err < 0)
		वापस err;

	अगर (spec->dig_out) अणु
		err = snd_hda_create_spdअगर_out_ctls(codec, spec->dig_out,
						    spec->dig_out);
		अगर (err < 0)
			वापस err;
		err = snd_hda_create_spdअगर_share_sw(codec, &spec->multiout);
		अगर (err < 0)
			वापस err;
		/* spec->multiout.share_spdअगर = 1; */
	पूर्ण

	अगर (spec->dig_in) अणु
		err = snd_hda_create_spdअगर_in_ctls(codec, spec->dig_in);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (ca0132_use_alt_functions(spec))
		ca0132_alt_add_chmap_ctls(codec);

	वापस 0;
पूर्ण

अटल पूर्णांक dbpro_build_controls(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक err = 0;

	अगर (spec->dig_out) अणु
		err = snd_hda_create_spdअगर_out_ctls(codec, spec->dig_out,
				spec->dig_out);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (spec->dig_in) अणु
		err = snd_hda_create_spdअगर_in_ctls(codec, spec->dig_in);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * PCM
 */
अटल स्थिर काष्ठा hda_pcm_stream ca0132_pcm_analog_playback = अणु
	.substreams = 1,
	.channels_min = 2,
	.channels_max = 6,
	.ops = अणु
		.prepare = ca0132_playback_pcm_prepare,
		.cleanup = ca0132_playback_pcm_cleanup,
		.get_delay = ca0132_playback_pcm_delay,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_pcm_stream ca0132_pcm_analog_capture = अणु
	.substreams = 1,
	.channels_min = 2,
	.channels_max = 2,
	.ops = अणु
		.prepare = ca0132_capture_pcm_prepare,
		.cleanup = ca0132_capture_pcm_cleanup,
		.get_delay = ca0132_capture_pcm_delay,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_pcm_stream ca0132_pcm_digital_playback = अणु
	.substreams = 1,
	.channels_min = 2,
	.channels_max = 2,
	.ops = अणु
		.खोलो = ca0132_dig_playback_pcm_खोलो,
		.बंद = ca0132_dig_playback_pcm_बंद,
		.prepare = ca0132_dig_playback_pcm_prepare,
		.cleanup = ca0132_dig_playback_pcm_cleanup
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_pcm_stream ca0132_pcm_digital_capture = अणु
	.substreams = 1,
	.channels_min = 2,
	.channels_max = 2,
पूर्ण;

अटल पूर्णांक ca0132_build_pcms(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	काष्ठा hda_pcm *info;

	info = snd_hda_codec_pcm_new(codec, "CA0132 Analog");
	अगर (!info)
		वापस -ENOMEM;
	अगर (ca0132_use_alt_functions(spec)) अणु
		info->own_chmap = true;
		info->stream[SNDRV_PCM_STREAM_PLAYBACK].chmap
			= ca0132_alt_chmaps;
	पूर्ण
	info->stream[SNDRV_PCM_STREAM_PLAYBACK] = ca0132_pcm_analog_playback;
	info->stream[SNDRV_PCM_STREAM_PLAYBACK].nid = spec->dacs[0];
	info->stream[SNDRV_PCM_STREAM_PLAYBACK].channels_max =
		spec->multiout.max_channels;
	info->stream[SNDRV_PCM_STREAM_CAPTURE] = ca0132_pcm_analog_capture;
	info->stream[SNDRV_PCM_STREAM_CAPTURE].substreams = 1;
	info->stream[SNDRV_PCM_STREAM_CAPTURE].nid = spec->adcs[0];

	/* With the DSP enabled, desktops करोn't use this ADC. */
	अगर (!ca0132_use_alt_functions(spec)) अणु
		info = snd_hda_codec_pcm_new(codec, "CA0132 Analog Mic-In2");
		अगर (!info)
			वापस -ENOMEM;
		info->stream[SNDRV_PCM_STREAM_CAPTURE] =
			ca0132_pcm_analog_capture;
		info->stream[SNDRV_PCM_STREAM_CAPTURE].substreams = 1;
		info->stream[SNDRV_PCM_STREAM_CAPTURE].nid = spec->adcs[1];
	पूर्ण

	info = snd_hda_codec_pcm_new(codec, "CA0132 What U Hear");
	अगर (!info)
		वापस -ENOMEM;
	info->stream[SNDRV_PCM_STREAM_CAPTURE] = ca0132_pcm_analog_capture;
	info->stream[SNDRV_PCM_STREAM_CAPTURE].substreams = 1;
	info->stream[SNDRV_PCM_STREAM_CAPTURE].nid = spec->adcs[2];

	अगर (!spec->dig_out && !spec->dig_in)
		वापस 0;

	info = snd_hda_codec_pcm_new(codec, "CA0132 Digital");
	अगर (!info)
		वापस -ENOMEM;
	info->pcm_type = HDA_PCM_TYPE_SPDIF;
	अगर (spec->dig_out) अणु
		info->stream[SNDRV_PCM_STREAM_PLAYBACK] =
			ca0132_pcm_digital_playback;
		info->stream[SNDRV_PCM_STREAM_PLAYBACK].nid = spec->dig_out;
	पूर्ण
	अगर (spec->dig_in) अणु
		info->stream[SNDRV_PCM_STREAM_CAPTURE] =
			ca0132_pcm_digital_capture;
		info->stream[SNDRV_PCM_STREAM_CAPTURE].nid = spec->dig_in;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dbpro_build_pcms(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	काष्ठा hda_pcm *info;

	info = snd_hda_codec_pcm_new(codec, "CA0132 Alt Analog");
	अगर (!info)
		वापस -ENOMEM;
	info->stream[SNDRV_PCM_STREAM_CAPTURE] = ca0132_pcm_analog_capture;
	info->stream[SNDRV_PCM_STREAM_CAPTURE].substreams = 1;
	info->stream[SNDRV_PCM_STREAM_CAPTURE].nid = spec->adcs[0];


	अगर (!spec->dig_out && !spec->dig_in)
		वापस 0;

	info = snd_hda_codec_pcm_new(codec, "CA0132 Digital");
	अगर (!info)
		वापस -ENOMEM;
	info->pcm_type = HDA_PCM_TYPE_SPDIF;
	अगर (spec->dig_out) अणु
		info->stream[SNDRV_PCM_STREAM_PLAYBACK] =
			ca0132_pcm_digital_playback;
		info->stream[SNDRV_PCM_STREAM_PLAYBACK].nid = spec->dig_out;
	पूर्ण
	अगर (spec->dig_in) अणु
		info->stream[SNDRV_PCM_STREAM_CAPTURE] =
			ca0132_pcm_digital_capture;
		info->stream[SNDRV_PCM_STREAM_CAPTURE].nid = spec->dig_in;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम init_output(काष्ठा hda_codec *codec, hda_nid_t pin, hda_nid_t dac)
अणु
	अगर (pin) अणु
		snd_hda_set_pin_ctl(codec, pin, PIN_HP);
		अगर (get_wcaps(codec, pin) & AC_WCAP_OUT_AMP)
			snd_hda_codec_ग_लिखो(codec, pin, 0,
					    AC_VERB_SET_AMP_GAIN_MUTE,
					    AMP_OUT_UNMUTE);
	पूर्ण
	अगर (dac && (get_wcaps(codec, dac) & AC_WCAP_OUT_AMP))
		snd_hda_codec_ग_लिखो(codec, dac, 0,
				    AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_ZERO);
पूर्ण

अटल व्योम init_input(काष्ठा hda_codec *codec, hda_nid_t pin, hda_nid_t adc)
अणु
	अगर (pin) अणु
		snd_hda_set_pin_ctl(codec, pin, PIN_VREF80);
		अगर (get_wcaps(codec, pin) & AC_WCAP_IN_AMP)
			snd_hda_codec_ग_लिखो(codec, pin, 0,
					    AC_VERB_SET_AMP_GAIN_MUTE,
					    AMP_IN_UNMUTE(0));
	पूर्ण
	अगर (adc && (get_wcaps(codec, adc) & AC_WCAP_IN_AMP)) अणु
		snd_hda_codec_ग_लिखो(codec, adc, 0, AC_VERB_SET_AMP_GAIN_MUTE,
				    AMP_IN_UNMUTE(0));

		/* init to 0 dB and unmute. */
		snd_hda_codec_amp_stereo(codec, adc, HDA_INPUT, 0,
					 HDA_AMP_VOLMASK, 0x5a);
		snd_hda_codec_amp_stereo(codec, adc, HDA_INPUT, 0,
					 HDA_AMP_MUTE, 0);
	पूर्ण
पूर्ण

अटल व्योम refresh_amp_caps(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dir)
अणु
	अचिन्हित पूर्णांक caps;

	caps = snd_hda_param_पढ़ो(codec, nid, dir == HDA_OUTPUT ?
				  AC_PAR_AMP_OUT_CAP : AC_PAR_AMP_IN_CAP);
	snd_hda_override_amp_caps(codec, nid, dir, caps);
पूर्ण

/*
 * Switch between Digital built-in mic and analog mic.
 */
अटल व्योम ca0132_set_dmic(काष्ठा hda_codec *codec, पूर्णांक enable)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक पंचांगp;
	u8 val;
	अचिन्हित पूर्णांक oldval;

	codec_dbg(codec, "ca0132_set_dmic: enable=%d\n", enable);

	oldval = stop_mic1(codec);
	ca0132_set_vipsource(codec, 0);
	अगर (enable) अणु
		/* set DMic input as 2-ch */
		पंचांगp = FLOAT_TWO;
		dspio_set_uपूर्णांक_param(codec, 0x80, 0x00, पंचांगp);

		val = spec->dmic_ctl;
		val |= 0x80;
		snd_hda_codec_ग_लिखो(codec, spec->input_pins[0], 0,
				    VENDOR_CHIPIO_DMIC_CTL_SET, val);

		अगर (!(spec->dmic_ctl & 0x20))
			chipio_set_control_flag(codec, CONTROL_FLAG_DMIC, 1);
	पूर्ण अन्यथा अणु
		/* set AMic input as mono */
		पंचांगp = FLOAT_ONE;
		dspio_set_uपूर्णांक_param(codec, 0x80, 0x00, पंचांगp);

		val = spec->dmic_ctl;
		/* clear bit7 and bit5 to disable dmic */
		val &= 0x5f;
		snd_hda_codec_ग_लिखो(codec, spec->input_pins[0], 0,
				    VENDOR_CHIPIO_DMIC_CTL_SET, val);

		अगर (!(spec->dmic_ctl & 0x20))
			chipio_set_control_flag(codec, CONTROL_FLAG_DMIC, 0);
	पूर्ण
	ca0132_set_vipsource(codec, 1);
	resume_mic1(codec, oldval);
पूर्ण

/*
 * Initialization क्रम Digital Mic.
 */
अटल व्योम ca0132_init_dmic(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	u8 val;

	/* Setup Digital Mic here, but करोn't enable.
	 * Enable based on jack detect.
	 */

	/* MCLK uses MPIO1, set to enable.
	 * Bit 2-0: MPIO select
	 * Bit   3: set to disable
	 * Bit 7-4: reserved
	 */
	val = 0x01;
	snd_hda_codec_ग_लिखो(codec, spec->input_pins[0], 0,
			    VENDOR_CHIPIO_DMIC_MCLK_SET, val);

	/* Data1 uses MPIO3. Data2 not use
	 * Bit 2-0: Data1 MPIO select
	 * Bit   3: set disable Data1
	 * Bit 6-4: Data2 MPIO select
	 * Bit   7: set disable Data2
	 */
	val = 0x83;
	snd_hda_codec_ग_लिखो(codec, spec->input_pins[0], 0,
			    VENDOR_CHIPIO_DMIC_PIN_SET, val);

	/* Use Ch-0 and Ch-1. Rate is 48K, mode 1. Disable DMic first.
	 * Bit 3-0: Channel mask
	 * Bit   4: set क्रम 48KHz, clear क्रम 32KHz
	 * Bit   5: mode
	 * Bit   6: set to select Data2, clear क्रम Data1
	 * Bit   7: set to enable DMic, clear क्रम AMic
	 */
	अगर (ca0132_quirk(spec) == QUIRK_ALIENWARE_M17XR4)
		val = 0x33;
	अन्यथा
		val = 0x23;
	/* keep a copy of dmic ctl val क्रम enable/disable dmic purpuse */
	spec->dmic_ctl = val;
	snd_hda_codec_ग_लिखो(codec, spec->input_pins[0], 0,
			    VENDOR_CHIPIO_DMIC_CTL_SET, val);
पूर्ण

/*
 * Initialization क्रम Analog Mic 2
 */
अटल व्योम ca0132_init_analog_mic2(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	mutex_lock(&spec->chipio_mutex);

	chipio_8051_ग_लिखो_exram_no_mutex(codec, 0x1920, 0x00);
	chipio_8051_ग_लिखो_exram_no_mutex(codec, 0x192d, 0x00);

	mutex_unlock(&spec->chipio_mutex);
पूर्ण

अटल व्योम ca0132_refresh_widget_caps(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक i;

	codec_dbg(codec, "ca0132_refresh_widget_caps.\n");
	snd_hda_codec_update_widमाला_लो(codec);

	क्रम (i = 0; i < spec->multiout.num_dacs; i++)
		refresh_amp_caps(codec, spec->dacs[i], HDA_OUTPUT);

	क्रम (i = 0; i < spec->num_outमाला_दो; i++)
		refresh_amp_caps(codec, spec->out_pins[i], HDA_OUTPUT);

	क्रम (i = 0; i < spec->num_inमाला_दो; i++) अणु
		refresh_amp_caps(codec, spec->adcs[i], HDA_INPUT);
		refresh_amp_caps(codec, spec->input_pins[i], HDA_INPUT);
	पूर्ण
पूर्ण


/* If there is an active channel क्रम some reason, find it and मुक्त it. */
अटल व्योम ca0132_alt_मुक्त_active_dma_channels(काष्ठा hda_codec *codec)
अणु
	अचिन्हित पूर्णांक i, पंचांगp;
	पूर्णांक status;

	/* Read active DSPDMAC channel रेजिस्टर. */
	status = chipio_पढ़ो(codec, DSPDMAC_CHNLSTART_MODULE_OFFSET, &पंचांगp);
	अगर (status >= 0) अणु
		/* AND against 0xfff to get the active channel bits. */
		पंचांगp = पंचांगp & 0xfff;

		/* If there are no active channels, nothing to मुक्त. */
		अगर (!पंचांगp)
			वापस;
	पूर्ण अन्यथा अणु
		codec_dbg(codec, "%s: Failed to read active DSP DMA channel register.\n",
				__func__);
		वापस;
	पूर्ण

	/*
	 * Check each DSP DMA channel क्रम activity, and अगर the channel is
	 * active, मुक्त it.
	 */
	क्रम (i = 0; i < DSPDMAC_DMA_CFG_CHANNEL_COUNT; i++) अणु
		अगर (dsp_is_dma_active(codec, i)) अणु
			status = dspio_मुक्त_dma_chan(codec, i);
			अगर (status < 0)
				codec_dbg(codec, "%s: Failed to free active DSP DMA channel %d.\n",
						__func__, i);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * In the हाल of CT_EXTENSIONS_ENABLE being set to 1, and the DSP being in
 * use, audio is no दीर्घer routed directly to the DAC/ADC from the HDA stream.
 * Instead, audio is now routed through the DSP's DMA controllers, which
 * the DSP is tasked with setting up itself. Through debugging, it seems the
 * cause of most of the no-audio on startup issues were due to improperly
 * configured DSP DMA channels.
 *
 * Normally, the DSP configures these the first समय an HDA audio stream is
 * started post DSP firmware करोwnload. That is why creating a 'dummy' stream
 * worked in fixing the audio in some हालs. This works most of the समय, but
 * someबार अगर a stream is started/stopped beक्रमe the DSP can setup the DMA
 * configuration रेजिस्टरs, it ends up in a broken state. Issues can also
 * arise अगर streams are started in an unusual order, i.e the audio output dma
 * channel being sandwiched between the mic1 and mic2 dma channels.
 *
 * The solution to this is to make sure that the DSP has no DMA channels
 * in use post DSP firmware करोwnload, and then to manually start each शेष
 * DSP stream that uses the DMA channels. These are 0x0c, the audio output
 * stream, 0x03, analog mic 1, and 0x04, analog mic 2.
 */
अटल व्योम ca0132_alt_start_dsp_audio_streams(काष्ठा hda_codec *codec)
अणु
	स्थिर अचिन्हित पूर्णांक dsp_dma_stream_ids[] = अणु 0x0c, 0x03, 0x04 पूर्ण;
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक i, पंचांगp;

	/*
	 * Check अगर any of the शेष streams are active, and अगर they are,
	 * stop them.
	 */
	mutex_lock(&spec->chipio_mutex);

	क्रम (i = 0; i < ARRAY_SIZE(dsp_dma_stream_ids); i++) अणु
		chipio_get_stream_control(codec, dsp_dma_stream_ids[i], &पंचांगp);

		अगर (पंचांगp) अणु
			chipio_set_stream_control(codec,
					dsp_dma_stream_ids[i], 0);
		पूर्ण
	पूर्ण

	mutex_unlock(&spec->chipio_mutex);

	/*
	 * If all DSP streams are inactive, there should be no active DSP DMA
	 * channels. Check and make sure this is the हाल, and अगर it isn't,
	 * मुक्त any active channels.
	 */
	ca0132_alt_मुक्त_active_dma_channels(codec);

	mutex_lock(&spec->chipio_mutex);

	/* Make sure stream 0x0c is six channels. */
	chipio_set_stream_channels(codec, 0x0c, 6);

	क्रम (i = 0; i < ARRAY_SIZE(dsp_dma_stream_ids); i++) अणु
		chipio_set_stream_control(codec,
				dsp_dma_stream_ids[i], 1);

		/* Give the DSP some समय to setup the DMA channel. */
		msleep(75);
	पूर्ण

	mutex_unlock(&spec->chipio_mutex);
पूर्ण

/*
 * The region of ChipIO memory from 0x190000-0x1903fc is a sort of 'audio
 * router', where each entry represents a 48khz audio channel, with a क्रमmat
 * of an 8-bit destination, an 8-bit source, and an unknown 2-bit number
 * value. The 2-bit number value is seemingly 0 अगर inactive, 1 अगर active,
 * and 3 अगर it's using Sample Rate Converter ports.
 * An example is:
 * 0x0001f8c0
 * In this हाल, f8 is the destination, and c0 is the source. The number value
 * is 1.
 * This region of memory is normally managed पूर्णांकernally by the 8051, where
 * the region of exram memory from 0x1477-0x1575 has each byte represent an
 * entry within the 0x190000 range, and when a range of entries is in use, the
 * ending value is overwritten with 0xff.
 * 0x1578 in exram is a table of 0x25 entries, corresponding to the ChipIO
 * streamID's, where each entry is a starting 0x190000 port offset.
 * 0x159d in exram is the same as 0x1578, except it contains the ending port
 * offset क्रम the corresponding streamID.
 *
 * On certain cards, such as the SBZ/ZxR/AE7, these are originally setup by
 * the 8051, then manually overwritten to remap the ports to work with the
 * new DACs.
 *
 * Currently known portID's:
 * 0x00-0x1f: HDA audio stream input/output ports.
 * 0x80-0xbf: Sample rate converter input/outमाला_दो. Only valid ports seem to
 *            have the lower-nibble set to 0x1, 0x2, and 0x9.
 * 0xc0-0xdf: DSP DMA input/output ports. Dynamically asचिन्हित.
 * 0xe0-0xff: DAC/ADC audio input/output ports.
 *
 * Currently known streamID's:
 * 0x03: Mic1 ADC to DSP.
 * 0x04: Mic2 ADC to DSP.
 * 0x05: HDA node 0x02 audio stream to DSP.
 * 0x0f: DSP Mic निकास to HDA node 0x07.
 * 0x0c: DSP processed audio to DACs.
 * 0x14: DAC0, front L/R.
 *
 * It is possible to route the HDA audio streams directly to the DAC and
 * bypass the DSP entirely, with the only करोwnside being that since the DSP
 * करोes volume control, the only volume control you'll get is through PCM on
 * the PC side, in the same way volume is handled क्रम optical out. This may be
 * useful क्रम debugging.
 */
अटल व्योम chipio_remap_stream(काष्ठा hda_codec *codec,
		स्थिर काष्ठा chipio_stream_remap_data *remap_data)
अणु
	अचिन्हित पूर्णांक i, stream_offset;

	/* Get the starting port क्रम the stream to be remapped. */
	chipio_8051_पढ़ो_exram(codec, 0x1578 + remap_data->stream_id,
			&stream_offset);

	/*
	 * Check अगर the stream's port value is 0xff, because the 8051 may not
	 * have gotten around to setting up the stream yet. Wait until it's
	 * setup to remap it's ports.
	 */
	अगर (stream_offset == 0xff) अणु
		क्रम (i = 0; i < 5; i++) अणु
			msleep(25);

			chipio_8051_पढ़ो_exram(codec, 0x1578 + remap_data->stream_id,
					&stream_offset);

			अगर (stream_offset != 0xff)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (stream_offset == 0xff) अणु
		codec_info(codec, "%s: Stream 0x%02x ports aren't allocated, remap failed!\n",
				__func__, remap_data->stream_id);
		वापस;
	पूर्ण

	/* Offset isn't in bytes, its in 32-bit words, so multiply it by 4. */
	stream_offset *= 0x04;
	stream_offset += 0x190000;

	क्रम (i = 0; i < remap_data->count; i++) अणु
		chipio_ग_लिखो_no_mutex(codec,
				stream_offset + remap_data->offset[i],
				remap_data->value[i]);
	पूर्ण

	/* Update stream map configuration. */
	chipio_ग_लिखो_no_mutex(codec, 0x19042c, 0x00000001);
पूर्ण

/*
 * Default speaker tuning values setup क्रम alternative codecs.
 */
अटल स्थिर अचिन्हित पूर्णांक sbz_शेष_delay_values[] = अणु
	/* Non-zero values are भग्नing poपूर्णांक 0.000198. */
	0x394f9e38, 0x394f9e38, 0x00000000, 0x00000000, 0x00000000, 0x00000000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक zxr_शेष_delay_values[] = अणु
	/* Non-zero values are भग्नing poपूर्णांक 0.000220. */
	0x00000000, 0x00000000, 0x3966afcd, 0x3966afcd, 0x3966afcd, 0x3966afcd
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ae5_शेष_delay_values[] = अणु
	/* Non-zero values are भग्नing poपूर्णांक 0.000100. */
	0x00000000, 0x00000000, 0x38d1b717, 0x38d1b717, 0x38d1b717, 0x38d1b717
पूर्ण;

/*
 * If we never change these, probably only need them on initialization.
 */
अटल व्योम ca0132_alt_init_speaker_tuning(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक i, पंचांगp, start_req, end_req;
	स्थिर अचिन्हित पूर्णांक *values;

	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_SBZ:
		values = sbz_शेष_delay_values;
		अवरोध;
	हाल QUIRK_ZXR:
		values = zxr_शेष_delay_values;
		अवरोध;
	हाल QUIRK_AE5:
	हाल QUIRK_AE7:
		values = ae5_शेष_delay_values;
		अवरोध;
	शेष:
		values = sbz_शेष_delay_values;
		अवरोध;
	पूर्ण

	पंचांगp = FLOAT_ZERO;
	dspio_set_uपूर्णांक_param(codec, 0x96, SPEAKER_TUNING_ENABLE_CENTER_EQ, पंचांगp);

	start_req = SPEAKER_TUNING_FRONT_LEFT_VOL_LEVEL;
	end_req = SPEAKER_TUNING_REAR_RIGHT_VOL_LEVEL;
	क्रम (i = start_req; i < end_req + 1; i++)
		dspio_set_uपूर्णांक_param(codec, 0x96, i, पंचांगp);

	start_req = SPEAKER_TUNING_FRONT_LEFT_INVERT;
	end_req = SPEAKER_TUNING_REAR_RIGHT_INVERT;
	क्रम (i = start_req; i < end_req + 1; i++)
		dspio_set_uपूर्णांक_param(codec, 0x96, i, पंचांगp);


	क्रम (i = 0; i < 6; i++)
		dspio_set_uपूर्णांक_param(codec, 0x96,
				SPEAKER_TUNING_FRONT_LEFT_DELAY + i, values[i]);
पूर्ण

/*
 * Initialize mic क्रम non-chromebook ca0132 implementations.
 */
अटल व्योम ca0132_alt_init_analog_mics(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक पंचांगp;

	/* Mic 1 Setup */
	chipio_set_conn_rate(codec, MEM_CONNID_MICIN1, SR_96_000);
	chipio_set_conn_rate(codec, MEM_CONNID_MICOUT1, SR_96_000);
	अगर (ca0132_quirk(spec) == QUIRK_R3DI) अणु
		chipio_set_conn_rate(codec, 0x0F, SR_96_000);
		पंचांगp = FLOAT_ONE;
	पूर्ण अन्यथा
		पंचांगp = FLOAT_THREE;
	dspio_set_uपूर्णांक_param(codec, 0x80, 0x00, पंचांगp);

	/* Mic 2 setup (not present on desktop cards) */
	chipio_set_conn_rate(codec, MEM_CONNID_MICIN2, SR_96_000);
	chipio_set_conn_rate(codec, MEM_CONNID_MICOUT2, SR_96_000);
	अगर (ca0132_quirk(spec) == QUIRK_R3DI)
		chipio_set_conn_rate(codec, 0x0F, SR_96_000);
	पंचांगp = FLOAT_ZERO;
	dspio_set_uपूर्णांक_param(codec, 0x80, 0x01, पंचांगp);
पूर्ण

/*
 * Sets the source of stream 0x14 to connpoपूर्णांकID 0x48, and the destination
 * connpoपूर्णांकID to 0x91. If this isn't करोne, the destination is 0x71, and
 * you get no sound. I'm guessing this has to करो with the Sound Blaster Z
 * having an updated DAC, which changes the destination to that DAC.
 */
अटल व्योम sbz_connect_streams(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	mutex_lock(&spec->chipio_mutex);

	codec_dbg(codec, "Connect Streams entered, mutex locked and loaded.\n");

	/* This value is 0x43 क्रम 96khz, and 0x83 क्रम 192khz. */
	chipio_ग_लिखो_no_mutex(codec, 0x18a020, 0x00000043);

	/* Setup stream 0x14 with it's source and destination poपूर्णांकs */
	chipio_set_stream_source_dest(codec, 0x14, 0x48, 0x91);
	chipio_set_conn_rate_no_mutex(codec, 0x48, SR_96_000);
	chipio_set_conn_rate_no_mutex(codec, 0x91, SR_96_000);
	chipio_set_stream_channels(codec, 0x14, 2);
	chipio_set_stream_control(codec, 0x14, 1);

	codec_dbg(codec, "Connect Streams exited, mutex released.\n");

	mutex_unlock(&spec->chipio_mutex);
पूर्ण

/*
 * Write data through ChipIO to setup proper stream destinations.
 * Not sure how it exactly works, but it seems to direct data
 * to dअगरferent destinations. Example is f8 to c0, e0 to c0.
 * All I know is, अगर you करोn't set these, you get no sound.
 */
अटल व्योम sbz_chipio_startup_data(काष्ठा hda_codec *codec)
अणु
	स्थिर काष्ठा chipio_stream_remap_data *dsp_out_remap_data;
	काष्ठा ca0132_spec *spec = codec->spec;

	mutex_lock(&spec->chipio_mutex);
	codec_dbg(codec, "Startup Data entered, mutex locked and loaded.\n");

	/* Remap DAC0's output ports. */
	chipio_remap_stream(codec, &stream_remap_data[0]);

	/* Remap DSP audio output stream ports. */
	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_SBZ:
		dsp_out_remap_data = &stream_remap_data[1];
		अवरोध;

	हाल QUIRK_ZXR:
		dsp_out_remap_data = &stream_remap_data[2];
		अवरोध;

	शेष:
		dsp_out_remap_data = शून्य;
		अवरोध;
	पूर्ण

	अगर (dsp_out_remap_data)
		chipio_remap_stream(codec, dsp_out_remap_data);

	codec_dbg(codec, "Startup Data exited, mutex released.\n");
	mutex_unlock(&spec->chipio_mutex);
पूर्ण

अटल व्योम ca0132_alt_dsp_initial_mic_setup(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक पंचांगp;

	chipio_set_stream_control(codec, 0x03, 0);
	chipio_set_stream_control(codec, 0x04, 0);

	chipio_set_conn_rate(codec, MEM_CONNID_MICIN1, SR_96_000);
	chipio_set_conn_rate(codec, MEM_CONNID_MICOUT1, SR_96_000);

	पंचांगp = FLOAT_THREE;
	dspio_set_uपूर्णांक_param(codec, 0x80, 0x00, पंचांगp);

	chipio_set_stream_control(codec, 0x03, 1);
	chipio_set_stream_control(codec, 0x04, 1);

	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_SBZ:
		chipio_ग_लिखो(codec, 0x18b098, 0x0000000c);
		chipio_ग_लिखो(codec, 0x18b09C, 0x0000000c);
		अवरोध;
	हाल QUIRK_AE5:
		chipio_ग_लिखो(codec, 0x18b098, 0x0000000c);
		chipio_ग_लिखो(codec, 0x18b09c, 0x0000004c);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ae5_post_dsp_रेजिस्टर_set(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	chipio_8051_ग_लिखो_direct(codec, 0x93, 0x10);
	chipio_8051_ग_लिखो_pll_pmu(codec, 0x44, 0xc2);

	ग_लिखोb(0xff, spec->mem_base + 0x304);
	ग_लिखोb(0xff, spec->mem_base + 0x304);
	ग_लिखोb(0xff, spec->mem_base + 0x304);
	ग_लिखोb(0xff, spec->mem_base + 0x304);
	ग_लिखोb(0x00, spec->mem_base + 0x100);
	ग_लिखोb(0xff, spec->mem_base + 0x304);
	ग_लिखोb(0x00, spec->mem_base + 0x100);
	ग_लिखोb(0xff, spec->mem_base + 0x304);
	ग_लिखोb(0x00, spec->mem_base + 0x100);
	ग_लिखोb(0xff, spec->mem_base + 0x304);
	ग_लिखोb(0x00, spec->mem_base + 0x100);
	ग_लिखोb(0xff, spec->mem_base + 0x304);

	ca0113_mmio_command_set(codec, 0x30, 0x2b, 0x3f);
	ca0113_mmio_command_set(codec, 0x30, 0x2d, 0x3f);
	ca0113_mmio_command_set(codec, 0x48, 0x07, 0x83);
पूर्ण

अटल व्योम ae5_post_dsp_param_setup(काष्ठा hda_codec *codec)
अणु
	/*
	 * Param3 in the 8051's memory is represented by the ascii string 'mch'
	 * which seems to be 'multichannel'. This is also mentioned in the
	 * AE-5's registry values in Winकरोws.
	 */
	chipio_set_control_param(codec, 3, 0);
	/*
	 * I believe ASI is 'audio serial interface' and that it's used to
	 * change colors on the बाह्यal LED strip connected to the AE-5.
	 */
	chipio_set_control_flag(codec, CONTROL_FLAG_ASI_96KHZ, 1);

	snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0, 0x724, 0x83);
	chipio_set_control_param(codec, CONTROL_PARAM_ASI, 0);

	chipio_8051_ग_लिखो_exram(codec, 0xfa92, 0x22);
पूर्ण

अटल व्योम ae5_post_dsp_pll_setup(काष्ठा hda_codec *codec)
अणु
	chipio_8051_ग_लिखो_pll_pmu(codec, 0x41, 0xc8);
	chipio_8051_ग_लिखो_pll_pmu(codec, 0x45, 0xcc);
	chipio_8051_ग_लिखो_pll_pmu(codec, 0x40, 0xcb);
	chipio_8051_ग_लिखो_pll_pmu(codec, 0x43, 0xc7);
	chipio_8051_ग_लिखो_pll_pmu(codec, 0x51, 0x8d);
पूर्ण

अटल व्योम ae5_post_dsp_stream_setup(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	mutex_lock(&spec->chipio_mutex);

	snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0, 0x725, 0x81);

	chipio_set_conn_rate_no_mutex(codec, 0x70, SR_96_000);

	chipio_set_stream_source_dest(codec, 0x5, 0x43, 0x0);

	chipio_set_stream_source_dest(codec, 0x18, 0x9, 0xd0);
	chipio_set_conn_rate_no_mutex(codec, 0xd0, SR_96_000);
	chipio_set_stream_channels(codec, 0x18, 6);
	chipio_set_stream_control(codec, 0x18, 1);

	chipio_set_control_param_no_mutex(codec, CONTROL_PARAM_ASI, 4);

	chipio_8051_ग_लिखो_pll_pmu_no_mutex(codec, 0x43, 0xc7);

	ca0113_mmio_command_set(codec, 0x48, 0x01, 0x80);

	mutex_unlock(&spec->chipio_mutex);
पूर्ण

अटल व्योम ae5_post_dsp_startup_data(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	mutex_lock(&spec->chipio_mutex);

	chipio_ग_लिखो_no_mutex(codec, 0x189000, 0x0001f101);
	chipio_ग_लिखो_no_mutex(codec, 0x189004, 0x0001f101);
	chipio_ग_लिखो_no_mutex(codec, 0x189024, 0x00014004);
	chipio_ग_लिखो_no_mutex(codec, 0x189028, 0x0002000f);

	ca0113_mmio_command_set(codec, 0x48, 0x0a, 0x05);
	chipio_set_control_param_no_mutex(codec, CONTROL_PARAM_ASI, 7);
	ca0113_mmio_command_set(codec, 0x48, 0x0b, 0x12);
	ca0113_mmio_command_set(codec, 0x48, 0x04, 0x00);
	ca0113_mmio_command_set(codec, 0x48, 0x06, 0x48);
	ca0113_mmio_command_set(codec, 0x48, 0x0a, 0x05);
	ca0113_mmio_command_set(codec, 0x48, 0x07, 0x83);
	ca0113_mmio_command_set(codec, 0x48, 0x0f, 0x00);
	ca0113_mmio_command_set(codec, 0x48, 0x10, 0x00);
	ca0113_mmio_gpio_set(codec, 0, true);
	ca0113_mmio_gpio_set(codec, 1, true);
	ca0113_mmio_command_set(codec, 0x48, 0x07, 0x80);

	chipio_ग_लिखो_no_mutex(codec, 0x18b03c, 0x00000012);

	ca0113_mmio_command_set(codec, 0x48, 0x0f, 0x00);
	ca0113_mmio_command_set(codec, 0x48, 0x10, 0x00);

	mutex_unlock(&spec->chipio_mutex);
पूर्ण

अटल व्योम ae7_post_dsp_setup_ports(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	mutex_lock(&spec->chipio_mutex);

	/* Seems to share the same port remapping as the SBZ. */
	chipio_remap_stream(codec, &stream_remap_data[1]);

	ca0113_mmio_command_set(codec, 0x30, 0x30, 0x00);
	ca0113_mmio_command_set(codec, 0x48, 0x0d, 0x40);
	ca0113_mmio_command_set(codec, 0x48, 0x17, 0x00);
	ca0113_mmio_command_set(codec, 0x48, 0x19, 0x00);
	ca0113_mmio_command_set(codec, 0x48, 0x11, 0xff);
	ca0113_mmio_command_set(codec, 0x48, 0x12, 0xff);
	ca0113_mmio_command_set(codec, 0x48, 0x13, 0xff);
	ca0113_mmio_command_set(codec, 0x48, 0x14, 0x7f);

	mutex_unlock(&spec->chipio_mutex);
पूर्ण

अटल व्योम ae7_post_dsp_asi_stream_setup(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	mutex_lock(&spec->chipio_mutex);

	snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0, 0x725, 0x81);
	ca0113_mmio_command_set(codec, 0x30, 0x2b, 0x00);

	chipio_set_conn_rate_no_mutex(codec, 0x70, SR_96_000);

	chipio_set_stream_source_dest(codec, 0x05, 0x43, 0x00);
	chipio_set_stream_source_dest(codec, 0x18, 0x09, 0xd0);

	chipio_set_conn_rate_no_mutex(codec, 0xd0, SR_96_000);
	chipio_set_stream_channels(codec, 0x18, 6);
	chipio_set_stream_control(codec, 0x18, 1);

	chipio_set_control_param_no_mutex(codec, CONTROL_PARAM_ASI, 4);

	mutex_unlock(&spec->chipio_mutex);
पूर्ण

अटल व्योम ae7_post_dsp_pll_setup(काष्ठा hda_codec *codec)
अणु
	अटल स्थिर अचिन्हित पूर्णांक addr[] = अणु
		0x41, 0x45, 0x40, 0x43, 0x51
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक data[] = अणु
		0xc8, 0xcc, 0xcb, 0xc7, 0x8d
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(addr); i++)
		chipio_8051_ग_लिखो_pll_pmu_no_mutex(codec, addr[i], data[i]);
पूर्ण

अटल व्योम ae7_post_dsp_asi_setup_ports(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अटल स्थिर अचिन्हित पूर्णांक target[] = अणु
		0x0b, 0x04, 0x06, 0x0a, 0x0c, 0x11, 0x12, 0x13, 0x14
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक data[] = अणु
		0x12, 0x00, 0x48, 0x05, 0x5f, 0xff, 0xff, 0xff, 0x7f
	पूर्ण;
	अचिन्हित पूर्णांक i;

	mutex_lock(&spec->chipio_mutex);

	chipio_8051_ग_लिखो_pll_pmu_no_mutex(codec, 0x43, 0xc7);

	chipio_ग_लिखो_no_mutex(codec, 0x189000, 0x0001f101);
	chipio_ग_लिखो_no_mutex(codec, 0x189004, 0x0001f101);
	chipio_ग_लिखो_no_mutex(codec, 0x189024, 0x00014004);
	chipio_ग_लिखो_no_mutex(codec, 0x189028, 0x0002000f);

	ae7_post_dsp_pll_setup(codec);
	chipio_set_control_param_no_mutex(codec, CONTROL_PARAM_ASI, 7);

	क्रम (i = 0; i < ARRAY_SIZE(target); i++)
		ca0113_mmio_command_set(codec, 0x48, target[i], data[i]);

	ca0113_mmio_command_set_type2(codec, 0x48, 0x07, 0x83);
	ca0113_mmio_command_set(codec, 0x48, 0x0f, 0x00);
	ca0113_mmio_command_set(codec, 0x48, 0x10, 0x00);

	chipio_set_stream_source_dest(codec, 0x21, 0x64, 0x56);
	chipio_set_stream_channels(codec, 0x21, 2);
	chipio_set_conn_rate_no_mutex(codec, 0x56, SR_8_000);

	chipio_set_control_param_no_mutex(codec, CONTROL_PARAM_NODE_ID, 0x09);
	/*
	 * In the 8051's memory, this param is referred to as 'n2sid', which I
	 * believe is 'node to streamID'. It seems to be a way to assign a
	 * stream to a given HDA node.
	 */
	chipio_set_control_param_no_mutex(codec, 0x20, 0x21);

	chipio_ग_लिखो_no_mutex(codec, 0x18b038, 0x00000088);

	/*
	 * Now, at this poपूर्णांक on Winकरोws, an actual stream is setup and
	 * seemingly sends data to the HDA node 0x09, which is the digital
	 * audio input node. This is left out here, because obviously I करोn't
	 * know what data is being sent. Interestingly, the AE-5 seems to go
	 * through the motions of getting here and never actually takes this
	 * step, but the AE-7 करोes.
	 */

	ca0113_mmio_gpio_set(codec, 0, 1);
	ca0113_mmio_gpio_set(codec, 1, 1);

	ca0113_mmio_command_set_type2(codec, 0x48, 0x07, 0x83);
	chipio_ग_लिखो_no_mutex(codec, 0x18b03c, 0x00000000);
	ca0113_mmio_command_set(codec, 0x48, 0x0f, 0x00);
	ca0113_mmio_command_set(codec, 0x48, 0x10, 0x00);

	chipio_set_stream_source_dest(codec, 0x05, 0x43, 0x00);
	chipio_set_stream_source_dest(codec, 0x18, 0x09, 0xd0);

	chipio_set_conn_rate_no_mutex(codec, 0xd0, SR_96_000);
	chipio_set_stream_channels(codec, 0x18, 6);

	/*
	 * Runs again, this has been repeated a few बार, but I'm just
	 * following what the Winकरोws driver करोes.
	 */
	ae7_post_dsp_pll_setup(codec);
	chipio_set_control_param_no_mutex(codec, CONTROL_PARAM_ASI, 7);

	mutex_unlock(&spec->chipio_mutex);
पूर्ण

/*
 * The Winकरोws driver has commands that seem to setup ASI, which I believe to
 * be some sort of audio serial पूर्णांकerface. My current speculation is that it's
 * related to communicating with the new DAC.
 */
अटल व्योम ae7_post_dsp_asi_setup(काष्ठा hda_codec *codec)
अणु
	chipio_8051_ग_लिखो_direct(codec, 0x93, 0x10);

	chipio_8051_ग_लिखो_pll_pmu(codec, 0x44, 0xc2);

	ca0113_mmio_command_set_type2(codec, 0x48, 0x07, 0x83);
	ca0113_mmio_command_set(codec, 0x30, 0x2e, 0x3f);

	chipio_set_control_param(codec, 3, 3);
	chipio_set_control_flag(codec, CONTROL_FLAG_ASI_96KHZ, 1);

	snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0, 0x724, 0x83);
	chipio_set_control_param(codec, CONTROL_PARAM_ASI, 0);
	snd_hda_codec_ग_लिखो(codec, 0x17, 0, 0x794, 0x00);

	chipio_8051_ग_लिखो_exram(codec, 0xfa92, 0x22);

	ae7_post_dsp_pll_setup(codec);
	ae7_post_dsp_asi_stream_setup(codec);

	chipio_8051_ग_लिखो_pll_pmu(codec, 0x43, 0xc7);

	ae7_post_dsp_asi_setup_ports(codec);
पूर्ण

/*
 * Setup शेष parameters क्रम DSP
 */
अटल व्योम ca0132_setup_शेषs(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक num_fx;
	पूर्णांक idx, i;

	अगर (spec->dsp_state != DSP_DOWNLOADED)
		वापस;

	/* out, in effects + voicefx */
	num_fx = OUT_EFFECTS_COUNT + IN_EFFECTS_COUNT + 1;
	क्रम (idx = 0; idx < num_fx; idx++) अणु
		क्रम (i = 0; i <= ca0132_effects[idx].params; i++) अणु
			dspio_set_uपूर्णांक_param(codec, ca0132_effects[idx].mid,
					     ca0132_effects[idx].reqs[i],
					     ca0132_effects[idx].def_vals[i]);
		पूर्ण
	पूर्ण

	/*हटाओ DSP headroom*/
	पंचांगp = FLOAT_ZERO;
	dspio_set_uपूर्णांक_param(codec, 0x96, 0x3C, पंचांगp);

	/*set speaker EQ bypass attenuation*/
	dspio_set_uपूर्णांक_param(codec, 0x8f, 0x01, पंचांगp);

	/* set AMic1 and AMic2 as mono mic */
	पंचांगp = FLOAT_ONE;
	dspio_set_uपूर्णांक_param(codec, 0x80, 0x00, पंचांगp);
	dspio_set_uपूर्णांक_param(codec, 0x80, 0x01, पंचांगp);

	/* set AMic1 as CrystalVoice input */
	पंचांगp = FLOAT_ONE;
	dspio_set_uपूर्णांक_param(codec, 0x80, 0x05, पंचांगp);

	/* set WUH source */
	पंचांगp = FLOAT_TWO;
	dspio_set_uपूर्णांक_param(codec, 0x31, 0x00, पंचांगp);
पूर्ण

/*
 * Setup शेष parameters क्रम Recon3D/Recon3Di DSP.
 */

अटल व्योम r3d_setup_शेषs(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक num_fx;
	पूर्णांक idx, i;

	अगर (spec->dsp_state != DSP_DOWNLOADED)
		वापस;

	ca0132_alt_init_analog_mics(codec);
	ca0132_alt_start_dsp_audio_streams(codec);

	/*हटाओ DSP headroom*/
	पंचांगp = FLOAT_ZERO;
	dspio_set_uपूर्णांक_param(codec, 0x96, 0x3C, पंचांगp);

	/* set WUH source */
	पंचांगp = FLOAT_TWO;
	dspio_set_uपूर्णांक_param(codec, 0x31, 0x00, पंचांगp);
	chipio_set_conn_rate(codec, MEM_CONNID_WUH, SR_48_000);

	/* Set speaker source? */
	dspio_set_uपूर्णांक_param(codec, 0x32, 0x00, पंचांगp);

	अगर (ca0132_quirk(spec) == QUIRK_R3DI)
		r3di_gpio_dsp_status_set(codec, R3DI_DSP_DOWNLOADED);

	/* Disable mute on Center/LFE. */
	अगर (ca0132_quirk(spec) == QUIRK_R3D) अणु
		ca0113_mmio_gpio_set(codec, 2, false);
		ca0113_mmio_gpio_set(codec, 4, true);
	पूर्ण

	/* Setup effect शेषs */
	num_fx = OUT_EFFECTS_COUNT + IN_EFFECTS_COUNT + 1;
	क्रम (idx = 0; idx < num_fx; idx++) अणु
		क्रम (i = 0; i <= ca0132_effects[idx].params; i++) अणु
			dspio_set_uपूर्णांक_param(codec,
					ca0132_effects[idx].mid,
					ca0132_effects[idx].reqs[i],
					ca0132_effects[idx].def_vals[i]);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Setup शेष parameters क्रम the Sound Blaster Z DSP. A lot more going on
 * than the Chromebook setup.
 */
अटल व्योम sbz_setup_शेषs(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक num_fx;
	पूर्णांक idx, i;

	अगर (spec->dsp_state != DSP_DOWNLOADED)
		वापस;

	ca0132_alt_init_analog_mics(codec);
	ca0132_alt_start_dsp_audio_streams(codec);
	sbz_connect_streams(codec);
	sbz_chipio_startup_data(codec);

	/*
	 * Sets पूर्णांकernal input loopback to off, used to have a चयन to
	 * enable input loopback, but turned out to be way too buggy.
	 */
	पंचांगp = FLOAT_ONE;
	dspio_set_uपूर्णांक_param(codec, 0x37, 0x08, पंचांगp);
	dspio_set_uपूर्णांक_param(codec, 0x37, 0x10, पंचांगp);

	/*हटाओ DSP headroom*/
	पंचांगp = FLOAT_ZERO;
	dspio_set_uपूर्णांक_param(codec, 0x96, 0x3C, पंचांगp);

	/* set WUH source */
	पंचांगp = FLOAT_TWO;
	dspio_set_uपूर्णांक_param(codec, 0x31, 0x00, पंचांगp);
	chipio_set_conn_rate(codec, MEM_CONNID_WUH, SR_48_000);

	/* Set speaker source? */
	dspio_set_uपूर्णांक_param(codec, 0x32, 0x00, पंचांगp);

	ca0132_alt_dsp_initial_mic_setup(codec);

	/* out, in effects + voicefx */
	num_fx = OUT_EFFECTS_COUNT + IN_EFFECTS_COUNT + 1;
	क्रम (idx = 0; idx < num_fx; idx++) अणु
		क्रम (i = 0; i <= ca0132_effects[idx].params; i++) अणु
			dspio_set_uपूर्णांक_param(codec,
					ca0132_effects[idx].mid,
					ca0132_effects[idx].reqs[i],
					ca0132_effects[idx].def_vals[i]);
		पूर्ण
	पूर्ण

	ca0132_alt_init_speaker_tuning(codec);
पूर्ण

/*
 * Setup शेष parameters क्रम the Sound BlasterX AE-5 DSP.
 */
अटल व्योम ae5_setup_शेषs(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक num_fx;
	पूर्णांक idx, i;

	अगर (spec->dsp_state != DSP_DOWNLOADED)
		वापस;

	ca0132_alt_init_analog_mics(codec);
	ca0132_alt_start_dsp_audio_streams(codec);

	/* New, unknown SCP req's */
	पंचांगp = FLOAT_ZERO;
	dspio_set_uपूर्णांक_param(codec, 0x96, 0x29, पंचांगp);
	dspio_set_uपूर्णांक_param(codec, 0x96, 0x2a, पंचांगp);
	dspio_set_uपूर्णांक_param(codec, 0x80, 0x0d, पंचांगp);
	dspio_set_uपूर्णांक_param(codec, 0x80, 0x0e, पंचांगp);

	ca0113_mmio_command_set(codec, 0x30, 0x2e, 0x3f);
	ca0113_mmio_gpio_set(codec, 0, false);
	ca0113_mmio_command_set(codec, 0x30, 0x28, 0x00);

	/* Internal loopback off */
	पंचांगp = FLOAT_ONE;
	dspio_set_uपूर्णांक_param(codec, 0x37, 0x08, पंचांगp);
	dspio_set_uपूर्णांक_param(codec, 0x37, 0x10, पंचांगp);

	/*हटाओ DSP headroom*/
	पंचांगp = FLOAT_ZERO;
	dspio_set_uपूर्णांक_param(codec, 0x96, 0x3C, पंचांगp);

	/* set WUH source */
	पंचांगp = FLOAT_TWO;
	dspio_set_uपूर्णांक_param(codec, 0x31, 0x00, पंचांगp);
	chipio_set_conn_rate(codec, MEM_CONNID_WUH, SR_48_000);

	/* Set speaker source? */
	dspio_set_uपूर्णांक_param(codec, 0x32, 0x00, पंचांगp);

	ca0132_alt_dsp_initial_mic_setup(codec);
	ae5_post_dsp_रेजिस्टर_set(codec);
	ae5_post_dsp_param_setup(codec);
	ae5_post_dsp_pll_setup(codec);
	ae5_post_dsp_stream_setup(codec);
	ae5_post_dsp_startup_data(codec);

	/* out, in effects + voicefx */
	num_fx = OUT_EFFECTS_COUNT + IN_EFFECTS_COUNT + 1;
	क्रम (idx = 0; idx < num_fx; idx++) अणु
		क्रम (i = 0; i <= ca0132_effects[idx].params; i++) अणु
			dspio_set_uपूर्णांक_param(codec,
					ca0132_effects[idx].mid,
					ca0132_effects[idx].reqs[i],
					ca0132_effects[idx].def_vals[i]);
		पूर्ण
	पूर्ण

	ca0132_alt_init_speaker_tuning(codec);
पूर्ण

/*
 * Setup शेष parameters क्रम the Sound Blaster AE-7 DSP.
 */
अटल व्योम ae7_setup_शेषs(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक num_fx;
	पूर्णांक idx, i;

	अगर (spec->dsp_state != DSP_DOWNLOADED)
		वापस;

	ca0132_alt_init_analog_mics(codec);
	ca0132_alt_start_dsp_audio_streams(codec);
	ae7_post_dsp_setup_ports(codec);

	पंचांगp = FLOAT_ZERO;
	dspio_set_uपूर्णांक_param(codec, 0x96,
			SPEAKER_TUNING_FRONT_LEFT_INVERT, पंचांगp);
	dspio_set_uपूर्णांक_param(codec, 0x96,
			SPEAKER_TUNING_FRONT_RIGHT_INVERT, पंचांगp);

	ca0113_mmio_command_set(codec, 0x30, 0x2e, 0x3f);

	/* New, unknown SCP req's */
	dspio_set_uपूर्णांक_param(codec, 0x80, 0x0d, पंचांगp);
	dspio_set_uपूर्णांक_param(codec, 0x80, 0x0e, पंचांगp);

	ca0113_mmio_gpio_set(codec, 0, false);

	/* Internal loopback off */
	पंचांगp = FLOAT_ONE;
	dspio_set_uपूर्णांक_param(codec, 0x37, 0x08, पंचांगp);
	dspio_set_uपूर्णांक_param(codec, 0x37, 0x10, पंचांगp);

	/*हटाओ DSP headroom*/
	पंचांगp = FLOAT_ZERO;
	dspio_set_uपूर्णांक_param(codec, 0x96, 0x3C, पंचांगp);

	/* set WUH source */
	पंचांगp = FLOAT_TWO;
	dspio_set_uपूर्णांक_param(codec, 0x31, 0x00, पंचांगp);
	chipio_set_conn_rate(codec, MEM_CONNID_WUH, SR_48_000);

	/* Set speaker source? */
	dspio_set_uपूर्णांक_param(codec, 0x32, 0x00, पंचांगp);
	ca0113_mmio_command_set(codec, 0x30, 0x28, 0x00);

	/*
	 * This is the second समय we've called this, but this is seemingly
	 * what Winकरोws करोes.
	 */
	ca0132_alt_init_analog_mics(codec);

	ae7_post_dsp_asi_setup(codec);

	/*
	 * Not sure why, but these are both set to 1. They're only set to 0
	 * upon shutकरोwn.
	 */
	ca0113_mmio_gpio_set(codec, 0, true);
	ca0113_mmio_gpio_set(codec, 1, true);

	/* Volume control related. */
	ca0113_mmio_command_set(codec, 0x48, 0x0f, 0x04);
	ca0113_mmio_command_set(codec, 0x48, 0x10, 0x04);
	ca0113_mmio_command_set_type2(codec, 0x48, 0x07, 0x80);

	/* out, in effects + voicefx */
	num_fx = OUT_EFFECTS_COUNT + IN_EFFECTS_COUNT + 1;
	क्रम (idx = 0; idx < num_fx; idx++) अणु
		क्रम (i = 0; i <= ca0132_effects[idx].params; i++) अणु
			dspio_set_uपूर्णांक_param(codec,
					ca0132_effects[idx].mid,
					ca0132_effects[idx].reqs[i],
					ca0132_effects[idx].def_vals[i]);
		पूर्ण
	पूर्ण

	ca0132_alt_init_speaker_tuning(codec);
पूर्ण

/*
 * Initialization of flags in chip
 */
अटल व्योम ca0132_init_flags(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	अगर (ca0132_use_alt_functions(spec)) अणु
		chipio_set_control_flag(codec, CONTROL_FLAG_DSP_96KHZ, 1);
		chipio_set_control_flag(codec, CONTROL_FLAG_DAC_96KHZ, 1);
		chipio_set_control_flag(codec, CONTROL_FLAG_ADC_B_96KHZ, 1);
		chipio_set_control_flag(codec, CONTROL_FLAG_ADC_C_96KHZ, 1);
		chipio_set_control_flag(codec, CONTROL_FLAG_SRC_RATE_96KHZ, 1);
		chipio_set_control_flag(codec, CONTROL_FLAG_IDLE_ENABLE, 0);
		chipio_set_control_flag(codec, CONTROL_FLAG_SPDIF2OUT, 0);
		chipio_set_control_flag(codec,
				CONTROL_FLAG_PORT_D_10KOHM_LOAD, 0);
		chipio_set_control_flag(codec,
				CONTROL_FLAG_PORT_A_10KOHM_LOAD, 1);
	पूर्ण अन्यथा अणु
		chipio_set_control_flag(codec, CONTROL_FLAG_IDLE_ENABLE, 0);
		chipio_set_control_flag(codec,
				CONTROL_FLAG_PORT_A_COMMON_MODE, 0);
		chipio_set_control_flag(codec,
				CONTROL_FLAG_PORT_D_COMMON_MODE, 0);
		chipio_set_control_flag(codec,
				CONTROL_FLAG_PORT_A_10KOHM_LOAD, 0);
		chipio_set_control_flag(codec,
				CONTROL_FLAG_PORT_D_10KOHM_LOAD, 0);
		chipio_set_control_flag(codec, CONTROL_FLAG_ADC_C_HIGH_PASS, 1);
	पूर्ण
पूर्ण

/*
 * Initialization of parameters in chip
 */
अटल व्योम ca0132_init_params(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	अगर (ca0132_use_alt_functions(spec)) अणु
		chipio_set_conn_rate(codec, MEM_CONNID_WUH, SR_48_000);
		chipio_set_conn_rate(codec, 0x0B, SR_48_000);
		chipio_set_control_param(codec, CONTROL_PARAM_SPDIF1_SOURCE, 0);
		chipio_set_control_param(codec, 0, 0);
		chipio_set_control_param(codec, CONTROL_PARAM_VIP_SOURCE, 0);
	पूर्ण

	chipio_set_control_param(codec, CONTROL_PARAM_PORTA_160OHM_GAIN, 6);
	chipio_set_control_param(codec, CONTROL_PARAM_PORTD_160OHM_GAIN, 6);
पूर्ण

अटल व्योम ca0132_set_dsp_msr(काष्ठा hda_codec *codec, bool is96k)
अणु
	chipio_set_control_flag(codec, CONTROL_FLAG_DSP_96KHZ, is96k);
	chipio_set_control_flag(codec, CONTROL_FLAG_DAC_96KHZ, is96k);
	chipio_set_control_flag(codec, CONTROL_FLAG_SRC_RATE_96KHZ, is96k);
	chipio_set_control_flag(codec, CONTROL_FLAG_SRC_CLOCK_196MHZ, is96k);
	chipio_set_control_flag(codec, CONTROL_FLAG_ADC_B_96KHZ, is96k);
	chipio_set_control_flag(codec, CONTROL_FLAG_ADC_C_96KHZ, is96k);

	chipio_set_conn_rate(codec, MEM_CONNID_MICIN1, SR_96_000);
	chipio_set_conn_rate(codec, MEM_CONNID_MICOUT1, SR_96_000);
	chipio_set_conn_rate(codec, MEM_CONNID_WUH, SR_48_000);
पूर्ण

अटल bool ca0132_करोwnload_dsp_images(काष्ठा hda_codec *codec)
अणु
	bool dsp_loaded = false;
	काष्ठा ca0132_spec *spec = codec->spec;
	स्थिर काष्ठा dsp_image_seg *dsp_os_image;
	स्थिर काष्ठा firmware *fw_entry = शून्य;
	/*
	 * Alternate firmwares क्रम dअगरferent variants. The Recon3Di apparently
	 * can use the शेष firmware, but I'll leave the option in हाल
	 * it needs it again.
	 */
	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_SBZ:
	हाल QUIRK_R3D:
	हाल QUIRK_AE5:
		अगर (request_firmware(&fw_entry, DESKTOP_EFX_खाता,
					codec->card->dev) != 0)
			codec_dbg(codec, "Desktop firmware not found.");
		अन्यथा
			codec_dbg(codec, "Desktop firmware selected.");
		अवरोध;
	हाल QUIRK_R3DI:
		अगर (request_firmware(&fw_entry, R3DI_EFX_खाता,
					codec->card->dev) != 0)
			codec_dbg(codec, "Recon3Di alt firmware not detected.");
		अन्यथा
			codec_dbg(codec, "Recon3Di firmware selected.");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	/*
	 * Use शेष ctefx.bin अगर no alt firmware is detected, or अगर none
	 * exists क्रम your particular codec.
	 */
	अगर (!fw_entry) अणु
		codec_dbg(codec, "Default firmware selected.");
		अगर (request_firmware(&fw_entry, EFX_खाता,
					codec->card->dev) != 0)
			वापस false;
	पूर्ण

	dsp_os_image = (काष्ठा dsp_image_seg *)(fw_entry->data);
	अगर (dspload_image(codec, dsp_os_image, 0, 0, true, 0)) अणु
		codec_err(codec, "ca0132 DSP load image failed\n");
		जाओ निकास_करोwnload;
	पूर्ण

	dsp_loaded = dspload_रुको_loaded(codec);

निकास_करोwnload:
	release_firmware(fw_entry);

	वापस dsp_loaded;
पूर्ण

अटल व्योम ca0132_करोwnload_dsp(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

#अगर_अघोषित CONFIG_SND_HDA_CODEC_CA0132_DSP
	वापस; /* NOP */
#पूर्ण_अगर

	अगर (spec->dsp_state == DSP_DOWNLOAD_FAILED)
		वापस; /* करोn't retry failures */

	chipio_enable_घड़ीs(codec);
	अगर (spec->dsp_state != DSP_DOWNLOADED) अणु
		spec->dsp_state = DSP_DOWNLOADING;

		अगर (!ca0132_करोwnload_dsp_images(codec))
			spec->dsp_state = DSP_DOWNLOAD_FAILED;
		अन्यथा
			spec->dsp_state = DSP_DOWNLOADED;
	पूर्ण

	/* For codecs using alt functions, this is alपढ़ोy करोne earlier */
	अगर (spec->dsp_state == DSP_DOWNLOADED && !ca0132_use_alt_functions(spec))
		ca0132_set_dsp_msr(codec, true);
पूर्ण

अटल व्योम ca0132_process_dsp_response(काष्ठा hda_codec *codec,
					काष्ठा hda_jack_callback *callback)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	codec_dbg(codec, "ca0132_process_dsp_response\n");
	snd_hda_घातer_up_pm(codec);
	अगर (spec->रुको_scp) अणु
		अगर (dspio_get_response_data(codec) >= 0)
			spec->रुको_scp = 0;
	पूर्ण

	dspio_clear_response_queue(codec);
	snd_hda_घातer_करोwn_pm(codec);
पूर्ण

अटल व्योम hp_callback(काष्ठा hda_codec *codec, काष्ठा hda_jack_callback *cb)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	काष्ठा hda_jack_tbl *tbl;

	/* Delay enabling the HP amp, to let the mic-detection
	 * state machine run.
	 */
	tbl = snd_hda_jack_tbl_get(codec, cb->nid);
	अगर (tbl)
		tbl->block_report = 1;
	schedule_delayed_work(&spec->unsol_hp_work, msecs_to_jअगरfies(500));
पूर्ण

अटल व्योम amic_callback(काष्ठा hda_codec *codec, काष्ठा hda_jack_callback *cb)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	अगर (ca0132_use_alt_functions(spec))
		ca0132_alt_select_in(codec);
	अन्यथा
		ca0132_select_mic(codec);
पूर्ण

अटल व्योम ca0132_setup_unsol(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	snd_hda_jack_detect_enable_callback(codec, spec->unsol_tag_hp, hp_callback);
	snd_hda_jack_detect_enable_callback(codec, spec->unsol_tag_amic1,
					    amic_callback);
	snd_hda_jack_detect_enable_callback(codec, UNSOL_TAG_DSP,
					    ca0132_process_dsp_response);
	/* Front headphone jack detection */
	अगर (ca0132_use_alt_functions(spec))
		snd_hda_jack_detect_enable_callback(codec,
			spec->unsol_tag_front_hp, hp_callback);
पूर्ण

/*
 * Verbs tables.
 */

/* Sends beक्रमe DSP करोwnload. */
अटल स्थिर काष्ठा hda_verb ca0132_base_init_verbs[] = अणु
	/*enable ct extension*/
	अणु0x15, VENDOR_CHIPIO_CT_EXTENSIONS_ENABLE, 0x1पूर्ण,
	अणुपूर्ण
पूर्ण;

/* Send at निकास. */
अटल स्थिर काष्ठा hda_verb ca0132_base_निकास_verbs[] = अणु
	/*set afg to D3*/
	अणु0x01, AC_VERB_SET_POWER_STATE, 0x03पूर्ण,
	/*disable ct extension*/
	अणु0x15, VENDOR_CHIPIO_CT_EXTENSIONS_ENABLE, 0पूर्ण,
	अणुपूर्ण
पूर्ण;

/* Other verbs tables. Sends after DSP करोwnload. */

अटल स्थिर काष्ठा hda_verb ca0132_init_verbs0[] = अणु
	/* chip init verbs */
	अणु0x15, 0x70D, 0xF0पूर्ण,
	अणु0x15, 0x70E, 0xFEपूर्ण,
	अणु0x15, 0x707, 0x75पूर्ण,
	अणु0x15, 0x707, 0xD3पूर्ण,
	अणु0x15, 0x707, 0x09पूर्ण,
	अणु0x15, 0x707, 0x53पूर्ण,
	अणु0x15, 0x707, 0xD4पूर्ण,
	अणु0x15, 0x707, 0xEFपूर्ण,
	अणु0x15, 0x707, 0x75पूर्ण,
	अणु0x15, 0x707, 0xD3पूर्ण,
	अणु0x15, 0x707, 0x09पूर्ण,
	अणु0x15, 0x707, 0x02पूर्ण,
	अणु0x15, 0x707, 0x37पूर्ण,
	अणु0x15, 0x707, 0x78पूर्ण,
	अणु0x15, 0x53C, 0xCEपूर्ण,
	अणु0x15, 0x575, 0xC9पूर्ण,
	अणु0x15, 0x53D, 0xCEपूर्ण,
	अणु0x15, 0x5B7, 0xC9पूर्ण,
	अणु0x15, 0x70D, 0xE8पूर्ण,
	अणु0x15, 0x70E, 0xFEपूर्ण,
	अणु0x15, 0x707, 0x02पूर्ण,
	अणु0x15, 0x707, 0x68पूर्ण,
	अणु0x15, 0x707, 0x62पूर्ण,
	अणु0x15, 0x53A, 0xCEपूर्ण,
	अणु0x15, 0x546, 0xC9पूर्ण,
	अणु0x15, 0x53B, 0xCEपूर्ण,
	अणु0x15, 0x5E8, 0xC9पूर्ण,
	अणुपूर्ण
पूर्ण;

/* Extra init verbs क्रम desktop cards. */
अटल स्थिर काष्ठा hda_verb ca0132_init_verbs1[] = अणु
	अणु0x15, 0x70D, 0x20पूर्ण,
	अणु0x15, 0x70E, 0x19पूर्ण,
	अणु0x15, 0x707, 0x00पूर्ण,
	अणु0x15, 0x539, 0xCEपूर्ण,
	अणु0x15, 0x546, 0xC9पूर्ण,
	अणु0x15, 0x70D, 0xB7पूर्ण,
	अणु0x15, 0x70E, 0x09पूर्ण,
	अणु0x15, 0x707, 0x10पूर्ण,
	अणु0x15, 0x70D, 0xAFपूर्ण,
	अणु0x15, 0x70E, 0x09पूर्ण,
	अणु0x15, 0x707, 0x01पूर्ण,
	अणु0x15, 0x707, 0x05पूर्ण,
	अणु0x15, 0x70D, 0x73पूर्ण,
	अणु0x15, 0x70E, 0x09पूर्ण,
	अणु0x15, 0x707, 0x14पूर्ण,
	अणु0x15, 0x6FF, 0xC4पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम ca0132_init_chip(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	पूर्णांक num_fx;
	पूर्णांक i;
	अचिन्हित पूर्णांक on;

	mutex_init(&spec->chipio_mutex);

	/*
	 * The Winकरोws driver always करोes this upon startup, which seems to
	 * clear out any previous configuration. This should help issues where
	 * a boot पूर्णांकo Winकरोws prior to a boot पूर्णांकo Linux अवरोधs things. Also,
	 * Winकरोws always sends the reset twice.
	 */
	अगर (ca0132_use_alt_functions(spec)) अणु
		chipio_set_control_flag(codec, CONTROL_FLAG_IDLE_ENABLE, 0);
		chipio_ग_लिखो_no_mutex(codec, 0x18b0a4, 0x000000c2);

		snd_hda_codec_ग_लिखो(codec, codec->core.afg, 0,
			    AC_VERB_SET_CODEC_RESET, 0);
		snd_hda_codec_ग_लिखो(codec, codec->core.afg, 0,
			    AC_VERB_SET_CODEC_RESET, 0);
	पूर्ण

	spec->cur_out_type = SPEAKER_OUT;
	अगर (!ca0132_use_alt_functions(spec))
		spec->cur_mic_type = DIGITAL_MIC;
	अन्यथा
		spec->cur_mic_type = REAR_MIC;

	spec->cur_mic_boost = 0;

	क्रम (i = 0; i < VNODES_COUNT; i++) अणु
		spec->vnode_lvol[i] = 0x5a;
		spec->vnode_rvol[i] = 0x5a;
		spec->vnode_lचयन[i] = 0;
		spec->vnode_rचयन[i] = 0;
	पूर्ण

	/*
	 * Default states क्रम effects are in ca0132_effects[].
	 */
	num_fx = OUT_EFFECTS_COUNT + IN_EFFECTS_COUNT;
	क्रम (i = 0; i < num_fx; i++) अणु
		on = (अचिन्हित पूर्णांक)ca0132_effects[i].reqs[0];
		spec->effects_चयन[i] = on ? 1 : 0;
	पूर्ण
	/*
	 * Sets शेषs क्रम the effect slider controls, only क्रम alternative
	 * ca0132 codecs. Also sets x-bass crossover frequency to 80hz.
	 */
	अगर (ca0132_use_alt_controls(spec)) अणु
		/* Set speakers to शेष to full range. */
		spec->speaker_range_val[0] = 1;
		spec->speaker_range_val[1] = 1;

		spec->xbass_xover_freq = 8;
		क्रम (i = 0; i < EFFECT_LEVEL_SLIDERS; i++)
			spec->fx_ctl_val[i] = effect_slider_शेषs[i];

		spec->bass_redirect_xover_freq = 8;
	पूर्ण

	spec->voicefx_val = 0;
	spec->effects_चयन[PLAY_ENHANCEMENT - EFFECT_START_NID] = 1;
	spec->effects_चयन[CRYSTAL_VOICE - EFFECT_START_NID] = 0;

	/*
	 * The ZxR करोesn't have a front panel header, and it's line-in is on
	 * the daughter board. So, there is no input क्रमागत control, and we need
	 * to make sure that spec->in_क्रमागत_val is set properly.
	 */
	अगर (ca0132_quirk(spec) == QUIRK_ZXR)
		spec->in_क्रमागत_val = REAR_MIC;

#अगर_घोषित ENABLE_TUNING_CONTROLS
	ca0132_init_tuning_शेषs(codec);
#पूर्ण_अगर
पूर्ण

/*
 * Recon3Di निकास specअगरic commands.
 */
/* prevents popping noise on shutकरोwn */
अटल व्योम r3di_gpio_shutकरोwn(काष्ठा hda_codec *codec)
अणु
	snd_hda_codec_ग_लिखो(codec, 0x01, 0, AC_VERB_SET_GPIO_DATA, 0x00);
पूर्ण

/*
 * Sound Blaster Z निकास specअगरic commands.
 */
अटल व्योम sbz_region2_निकास(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		ग_लिखोb(0x0, spec->mem_base + 0x100);
	क्रम (i = 0; i < 8; i++)
		ग_लिखोb(0xb3, spec->mem_base + 0x304);

	ca0113_mmio_gpio_set(codec, 0, false);
	ca0113_mmio_gpio_set(codec, 1, false);
	ca0113_mmio_gpio_set(codec, 4, true);
	ca0113_mmio_gpio_set(codec, 5, false);
	ca0113_mmio_gpio_set(codec, 7, false);
पूर्ण

अटल व्योम sbz_set_pin_ctl_शेष(काष्ठा hda_codec *codec)
अणु
	अटल स्थिर hda_nid_t pins[] = अणु0x0B, 0x0C, 0x0E, 0x12, 0x13पूर्ण;
	अचिन्हित पूर्णांक i;

	snd_hda_codec_ग_लिखो(codec, 0x11, 0,
			AC_VERB_SET_PIN_WIDGET_CONTROL, 0x40);

	क्रम (i = 0; i < ARRAY_SIZE(pins); i++)
		snd_hda_codec_ग_लिखो(codec, pins[i], 0,
				AC_VERB_SET_PIN_WIDGET_CONTROL, 0x00);
पूर्ण

अटल व्योम ca0132_clear_unsolicited(काष्ठा hda_codec *codec)
अणु
	अटल स्थिर hda_nid_t pins[] = अणु0x0B, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pins); i++) अणु
		snd_hda_codec_ग_लिखो(codec, pins[i], 0,
				AC_VERB_SET_UNSOLICITED_ENABLE, 0x00);
	पूर्ण
पूर्ण

/* On shutकरोwn, sends commands in sets of three */
अटल व्योम sbz_gpio_shutकरोwn_commands(काष्ठा hda_codec *codec, पूर्णांक dir,
							पूर्णांक mask, पूर्णांक data)
अणु
	अगर (dir >= 0)
		snd_hda_codec_ग_लिखो(codec, 0x01, 0,
				AC_VERB_SET_GPIO_सूचीECTION, dir);
	अगर (mask >= 0)
		snd_hda_codec_ग_लिखो(codec, 0x01, 0,
				AC_VERB_SET_GPIO_MASK, mask);

	अगर (data >= 0)
		snd_hda_codec_ग_लिखो(codec, 0x01, 0,
				AC_VERB_SET_GPIO_DATA, data);
पूर्ण

अटल व्योम zxr_dbpro_घातer_state_shutकरोwn(काष्ठा hda_codec *codec)
अणु
	अटल स्थिर hda_nid_t pins[] = अणु0x05, 0x0c, 0x09, 0x0e, 0x08, 0x11, 0x01पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pins); i++)
		snd_hda_codec_ग_लिखो(codec, pins[i], 0,
				AC_VERB_SET_POWER_STATE, 0x03);
पूर्ण

अटल व्योम sbz_निकास_chip(काष्ठा hda_codec *codec)
अणु
	chipio_set_stream_control(codec, 0x03, 0);
	chipio_set_stream_control(codec, 0x04, 0);

	/* Mess with GPIO */
	sbz_gpio_shutकरोwn_commands(codec, 0x07, 0x07, -1);
	sbz_gpio_shutकरोwn_commands(codec, 0x07, 0x07, 0x05);
	sbz_gpio_shutकरोwn_commands(codec, 0x07, 0x07, 0x01);

	chipio_set_stream_control(codec, 0x14, 0);
	chipio_set_stream_control(codec, 0x0C, 0);

	chipio_set_conn_rate(codec, 0x41, SR_192_000);
	chipio_set_conn_rate(codec, 0x91, SR_192_000);

	chipio_ग_लिखो(codec, 0x18a020, 0x00000083);

	sbz_gpio_shutकरोwn_commands(codec, 0x07, 0x07, 0x03);
	sbz_gpio_shutकरोwn_commands(codec, 0x07, 0x07, 0x07);
	sbz_gpio_shutकरोwn_commands(codec, 0x07, 0x07, 0x06);

	chipio_set_stream_control(codec, 0x0C, 0);

	chipio_set_control_param(codec, 0x0D, 0x24);

	ca0132_clear_unsolicited(codec);
	sbz_set_pin_ctl_शेष(codec);

	snd_hda_codec_ग_लिखो(codec, 0x0B, 0,
		AC_VERB_SET_EAPD_BTLENABLE, 0x00);

	sbz_region2_निकास(codec);
पूर्ण

अटल व्योम r3d_निकास_chip(काष्ठा hda_codec *codec)
अणु
	ca0132_clear_unsolicited(codec);
	snd_hda_codec_ग_लिखो(codec, 0x01, 0, 0x793, 0x00);
	snd_hda_codec_ग_लिखो(codec, 0x01, 0, 0x794, 0x5b);
पूर्ण

अटल व्योम ae5_निकास_chip(काष्ठा hda_codec *codec)
अणु
	chipio_set_stream_control(codec, 0x03, 0);
	chipio_set_stream_control(codec, 0x04, 0);

	ca0113_mmio_command_set(codec, 0x30, 0x32, 0x3f);
	ca0113_mmio_command_set(codec, 0x48, 0x07, 0x83);
	ca0113_mmio_command_set(codec, 0x48, 0x07, 0x83);
	ca0113_mmio_command_set(codec, 0x30, 0x30, 0x00);
	ca0113_mmio_command_set(codec, 0x30, 0x2b, 0x00);
	ca0113_mmio_command_set(codec, 0x30, 0x2d, 0x00);
	ca0113_mmio_gpio_set(codec, 0, false);
	ca0113_mmio_gpio_set(codec, 1, false);

	snd_hda_codec_ग_लिखो(codec, 0x01, 0, 0x793, 0x00);
	snd_hda_codec_ग_लिखो(codec, 0x01, 0, 0x794, 0x53);

	chipio_set_control_param(codec, CONTROL_PARAM_ASI, 0);

	chipio_set_stream_control(codec, 0x18, 0);
	chipio_set_stream_control(codec, 0x0c, 0);

	snd_hda_codec_ग_लिखो(codec, 0x01, 0, 0x724, 0x83);
पूर्ण

अटल व्योम ae7_निकास_chip(काष्ठा hda_codec *codec)
अणु
	chipio_set_stream_control(codec, 0x18, 0);
	chipio_set_stream_source_dest(codec, 0x21, 0xc8, 0xc8);
	chipio_set_stream_channels(codec, 0x21, 0);
	chipio_set_control_param(codec, CONTROL_PARAM_NODE_ID, 0x09);
	chipio_set_control_param(codec, 0x20, 0x01);

	chipio_set_control_param(codec, CONTROL_PARAM_ASI, 0);

	chipio_set_stream_control(codec, 0x18, 0);
	chipio_set_stream_control(codec, 0x0c, 0);

	ca0113_mmio_command_set(codec, 0x30, 0x2b, 0x00);
	snd_hda_codec_ग_लिखो(codec, 0x15, 0, 0x724, 0x83);
	ca0113_mmio_command_set_type2(codec, 0x48, 0x07, 0x83);
	ca0113_mmio_command_set(codec, 0x30, 0x30, 0x00);
	ca0113_mmio_command_set(codec, 0x30, 0x2e, 0x00);
	ca0113_mmio_gpio_set(codec, 0, false);
	ca0113_mmio_gpio_set(codec, 1, false);
	ca0113_mmio_command_set(codec, 0x30, 0x32, 0x3f);

	snd_hda_codec_ग_लिखो(codec, 0x01, 0, 0x793, 0x00);
	snd_hda_codec_ग_लिखो(codec, 0x01, 0, 0x794, 0x53);
पूर्ण

अटल व्योम zxr_निकास_chip(काष्ठा hda_codec *codec)
अणु
	chipio_set_stream_control(codec, 0x03, 0);
	chipio_set_stream_control(codec, 0x04, 0);
	chipio_set_stream_control(codec, 0x14, 0);
	chipio_set_stream_control(codec, 0x0C, 0);

	chipio_set_conn_rate(codec, 0x41, SR_192_000);
	chipio_set_conn_rate(codec, 0x91, SR_192_000);

	chipio_ग_लिखो(codec, 0x18a020, 0x00000083);

	snd_hda_codec_ग_लिखो(codec, 0x01, 0, 0x793, 0x00);
	snd_hda_codec_ग_लिखो(codec, 0x01, 0, 0x794, 0x53);

	ca0132_clear_unsolicited(codec);
	sbz_set_pin_ctl_शेष(codec);
	snd_hda_codec_ग_लिखो(codec, 0x0B, 0, AC_VERB_SET_EAPD_BTLENABLE, 0x00);

	ca0113_mmio_gpio_set(codec, 5, false);
	ca0113_mmio_gpio_set(codec, 2, false);
	ca0113_mmio_gpio_set(codec, 3, false);
	ca0113_mmio_gpio_set(codec, 0, false);
	ca0113_mmio_gpio_set(codec, 4, true);
	ca0113_mmio_gpio_set(codec, 0, true);
	ca0113_mmio_gpio_set(codec, 5, true);
	ca0113_mmio_gpio_set(codec, 2, false);
	ca0113_mmio_gpio_set(codec, 3, false);
पूर्ण

अटल व्योम ca0132_निकास_chip(काष्ठा hda_codec *codec)
अणु
	/* put any chip cleanup stuffs here. */

	अगर (dspload_is_loaded(codec))
		dsp_reset(codec);
पूर्ण

/*
 * This fixes a problem that was hard to reproduce. Very rarely, I would
 * boot up, and there would be no sound, but the DSP indicated it had loaded
 * properly. I did a few memory dumps to see अगर anything was dअगरferent, and
 * there were a few areas of memory uninitialized with a1a2a3a4. This function
 * checks अगर those areas are uninitialized, and अगर they are, it'll attempt to
 * reload the card 3 बार. Usually it fixes by the second.
 */
अटल व्योम sbz_dsp_startup_check(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक dsp_data_check[4];
	अचिन्हित पूर्णांक cur_address = 0x390;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक failure = 0;
	अचिन्हित पूर्णांक reload = 3;

	अगर (spec->startup_check_entered)
		वापस;

	spec->startup_check_entered = true;

	क्रम (i = 0; i < 4; i++) अणु
		chipio_पढ़ो(codec, cur_address, &dsp_data_check[i]);
		cur_address += 0x4;
	पूर्ण
	क्रम (i = 0; i < 4; i++) अणु
		अगर (dsp_data_check[i] == 0xa1a2a3a4)
			failure = 1;
	पूर्ण

	codec_dbg(codec, "Startup Check: %d ", failure);
	अगर (failure)
		codec_info(codec, "DSP not initialized properly. Attempting to fix.");
	/*
	 * While the failure condition is true, and we haven't reached our
	 * three reload limit, जारी trying to reload the driver and
	 * fix the issue.
	 */
	जबतक (failure && (reload != 0)) अणु
		codec_info(codec, "Reloading... Tries left: %d", reload);
		sbz_निकास_chip(codec);
		spec->dsp_state = DSP_DOWNLOAD_INIT;
		codec->patch_ops.init(codec);
		failure = 0;
		क्रम (i = 0; i < 4; i++) अणु
			chipio_पढ़ो(codec, cur_address, &dsp_data_check[i]);
			cur_address += 0x4;
		पूर्ण
		क्रम (i = 0; i < 4; i++) अणु
			अगर (dsp_data_check[i] == 0xa1a2a3a4)
				failure = 1;
		पूर्ण
		reload--;
	पूर्ण

	अगर (!failure && reload < 3)
		codec_info(codec, "DSP fixed.");

	अगर (!failure)
		वापस;

	codec_info(codec, "DSP failed to initialize properly. Either try a full shutdown or a suspend to clear the internal memory.");
पूर्ण

/*
 * This is क्रम the extra volume verbs 0x797 (left) and 0x798 (right). These add
 * extra precision क्रम decibel values. If you had the dB value in भग्नing poपूर्णांक
 * you would take the value after the decimal poपूर्णांक, multiply by 64, and भागide
 * by 2. So क्रम 8.59, it's (59 * 64) / 100. Useful अगर someone wanted to
 * implement fixed poपूर्णांक or भग्नing poपूर्णांक dB volumes. For now, I'll set them
 * to 0 just inहाल a value has lingered from a boot पूर्णांकo Winकरोws.
 */
अटल व्योम ca0132_alt_vol_setup(काष्ठा hda_codec *codec)
अणु
	snd_hda_codec_ग_लिखो(codec, 0x02, 0, 0x797, 0x00);
	snd_hda_codec_ग_लिखो(codec, 0x02, 0, 0x798, 0x00);
	snd_hda_codec_ग_लिखो(codec, 0x03, 0, 0x797, 0x00);
	snd_hda_codec_ग_लिखो(codec, 0x03, 0, 0x798, 0x00);
	snd_hda_codec_ग_लिखो(codec, 0x04, 0, 0x797, 0x00);
	snd_hda_codec_ग_लिखो(codec, 0x04, 0, 0x798, 0x00);
	snd_hda_codec_ग_लिखो(codec, 0x07, 0, 0x797, 0x00);
	snd_hda_codec_ग_लिखो(codec, 0x07, 0, 0x798, 0x00);
पूर्ण

/*
 * Extra commands that करोn't really fit anywhere अन्यथा.
 */
अटल व्योम sbz_pre_dsp_setup(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	ग_लिखोl(0x00820680, spec->mem_base + 0x01C);
	ग_लिखोl(0x00820680, spec->mem_base + 0x01C);

	chipio_ग_लिखो(codec, 0x18b0a4, 0x000000c2);

	snd_hda_codec_ग_लिखो(codec, 0x11, 0,
			AC_VERB_SET_PIN_WIDGET_CONTROL, 0x44);
पूर्ण

अटल व्योम r3d_pre_dsp_setup(काष्ठा hda_codec *codec)
अणु
	chipio_ग_लिखो(codec, 0x18b0a4, 0x000000c2);

	chipio_8051_ग_लिखो_exram(codec, 0x1c1e, 0x5b);

	snd_hda_codec_ग_लिखो(codec, 0x11, 0,
			AC_VERB_SET_PIN_WIDGET_CONTROL, 0x44);
पूर्ण

अटल व्योम r3di_pre_dsp_setup(काष्ठा hda_codec *codec)
अणु
	chipio_ग_लिखो(codec, 0x18b0a4, 0x000000c2);

	chipio_8051_ग_लिखो_exram(codec, 0x1c1e, 0x5b);
	chipio_8051_ग_लिखो_exram(codec, 0x1920, 0x00);
	chipio_8051_ग_लिखो_exram(codec, 0x1921, 0x40);

	snd_hda_codec_ग_लिखो(codec, 0x11, 0,
			AC_VERB_SET_PIN_WIDGET_CONTROL, 0x04);
पूर्ण

/*
 * The ZxR seems to use alternative DAC's क्रम the surround channels, which
 * require PLL PMU setup क्रम the घड़ी rate, I'm guessing. Without setting
 * this up, we get no audio out of the surround jacks.
 */
अटल व्योम zxr_pre_dsp_setup(काष्ठा hda_codec *codec)
अणु
	अटल स्थिर अचिन्हित पूर्णांक addr[] = अणु 0x43, 0x40, 0x41, 0x42, 0x45 पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक data[] = अणु 0x08, 0x0c, 0x0b, 0x07, 0x0d पूर्ण;
	अचिन्हित पूर्णांक i;

	chipio_ग_लिखो(codec, 0x189000, 0x0001f100);
	msleep(50);
	chipio_ग_लिखो(codec, 0x18900c, 0x0001f100);
	msleep(50);

	/*
	 * This ग_लिखोs a RET inकाष्ठाion at the entry poपूर्णांक of the function at
	 * 0xfa92 in exram. This function seems to have something to करो with
	 * ASI. Might be some way to prevent the card from reconfiguring the
	 * ASI stuff itself.
	 */
	chipio_8051_ग_लिखो_exram(codec, 0xfa92, 0x22);

	chipio_8051_ग_लिखो_pll_pmu(codec, 0x51, 0x98);

	snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0, 0x725, 0x82);
	chipio_set_control_param(codec, CONTROL_PARAM_ASI, 3);

	chipio_ग_लिखो(codec, 0x18902c, 0x00000000);
	msleep(50);
	chipio_ग_लिखो(codec, 0x18902c, 0x00000003);
	msleep(50);

	क्रम (i = 0; i < ARRAY_SIZE(addr); i++)
		chipio_8051_ग_लिखो_pll_pmu(codec, addr[i], data[i]);
पूर्ण

/*
 * These are sent beक्रमe the DSP is करोwnloaded. Not sure
 * what they करो, or अगर they're necessary. Could possibly
 * be हटाओd. Figure they're better to leave in.
 */
अटल स्थिर अचिन्हित पूर्णांक ca0113_mmio_init_address_sbz[] = अणु
	0x400, 0x408, 0x40c, 0x01c, 0xc0c, 0xc00, 0xc04, 0xc0c, 0xc0c, 0xc0c,
	0xc0c, 0xc08, 0xc08, 0xc08, 0xc08, 0xc08, 0xc04
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ca0113_mmio_init_data_sbz[] = अणु
	0x00000030, 0x00000000, 0x00000003, 0x00000003, 0x00000003,
	0x00000003, 0x000000c1, 0x000000f1, 0x00000001, 0x000000c7,
	0x000000c1, 0x00000080
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ca0113_mmio_init_data_zxr[] = अणु
	0x00000030, 0x00000000, 0x00000000, 0x00000003, 0x00000003,
	0x00000003, 0x00000001, 0x000000f1, 0x00000001, 0x000000c7,
	0x000000c1, 0x00000080
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ca0113_mmio_init_address_ae5[] = अणु
	0x400, 0x42c, 0x46c, 0x4ac, 0x4ec, 0x43c, 0x47c, 0x4bc, 0x4fc, 0x408,
	0x100, 0x410, 0x40c, 0x100, 0x100, 0x830, 0x86c, 0x800, 0x86c, 0x800,
	0x804, 0x20c, 0x01c, 0xc0c, 0xc00, 0xc04, 0xc0c, 0xc0c, 0xc0c, 0xc0c,
	0xc08, 0xc08, 0xc08, 0xc08, 0xc08, 0xc04, 0x01c
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ca0113_mmio_init_data_ae5[] = अणु
	0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001,
	0x00000600, 0x00000014, 0x00000001, 0x0000060f, 0x0000070f,
	0x00000aff, 0x00000000, 0x0000006b, 0x00000001, 0x0000006b,
	0x00000057, 0x00800000, 0x00880680, 0x00000080, 0x00000030,
	0x00000000, 0x00000000, 0x00000003, 0x00000003, 0x00000003,
	0x00000001, 0x000000f1, 0x00000001, 0x000000c7, 0x000000c1,
	0x00000080, 0x00880680
पूर्ण;

अटल व्योम ca0132_mmio_init_sbz(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक पंचांगp[2], i, count, cur_addr;
	स्थिर अचिन्हित पूर्णांक *addr, *data;

	addr = ca0113_mmio_init_address_sbz;
	क्रम (i = 0; i < 3; i++)
		ग_लिखोl(0x00000000, spec->mem_base + addr[i]);

	cur_addr = i;
	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_ZXR:
		पंचांगp[0] = 0x00880480;
		पंचांगp[1] = 0x00000080;
		अवरोध;
	हाल QUIRK_SBZ:
		पंचांगp[0] = 0x00820680;
		पंचांगp[1] = 0x00000083;
		अवरोध;
	हाल QUIRK_R3D:
		पंचांगp[0] = 0x00880680;
		पंचांगp[1] = 0x00000083;
		अवरोध;
	शेष:
		पंचांगp[0] = 0x00000000;
		पंचांगp[1] = 0x00000000;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < 2; i++)
		ग_लिखोl(पंचांगp[i], spec->mem_base + addr[cur_addr + i]);

	cur_addr += i;

	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_ZXR:
		count = ARRAY_SIZE(ca0113_mmio_init_data_zxr);
		data = ca0113_mmio_init_data_zxr;
		अवरोध;
	शेष:
		count = ARRAY_SIZE(ca0113_mmio_init_data_sbz);
		data = ca0113_mmio_init_data_sbz;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < count; i++)
		ग_लिखोl(data[i], spec->mem_base + addr[cur_addr + i]);
पूर्ण

अटल व्योम ca0132_mmio_init_ae5(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	स्थिर अचिन्हित पूर्णांक *addr, *data;
	अचिन्हित पूर्णांक i, count;

	addr = ca0113_mmio_init_address_ae5;
	data = ca0113_mmio_init_data_ae5;
	count = ARRAY_SIZE(ca0113_mmio_init_data_ae5);

	अगर (ca0132_quirk(spec) == QUIRK_AE7) अणु
		ग_लिखोl(0x00000680, spec->mem_base + 0x1c);
		ग_लिखोl(0x00880680, spec->mem_base + 0x1c);
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		/*
		 * AE-7 shares all ग_लिखोs with the AE-5, except that it ग_लिखोs
		 * a dअगरferent value to 0x20c.
		 */
		अगर (i == 21 && ca0132_quirk(spec) == QUIRK_AE7) अणु
			ग_लिखोl(0x00800001, spec->mem_base + addr[i]);
			जारी;
		पूर्ण

		ग_लिखोl(data[i], spec->mem_base + addr[i]);
	पूर्ण

	अगर (ca0132_quirk(spec) == QUIRK_AE5)
		ग_लिखोl(0x00880680, spec->mem_base + 0x1c);
पूर्ण

अटल व्योम ca0132_mmio_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_R3D:
	हाल QUIRK_SBZ:
	हाल QUIRK_ZXR:
		ca0132_mmio_init_sbz(codec);
		अवरोध;
	हाल QUIRK_AE5:
		ca0132_mmio_init_ae5(codec);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक ca0132_ae5_रेजिस्टर_set_addresses[] = अणु
	0x304, 0x304, 0x304, 0x304, 0x100, 0x304, 0x100, 0x304, 0x100, 0x304,
	0x100, 0x304, 0x86c, 0x800, 0x86c, 0x800, 0x804
पूर्ण;

अटल स्थिर अचिन्हित अक्षर ca0132_ae5_रेजिस्टर_set_data[] = अणु
	0x0f, 0x0e, 0x1f, 0x0c, 0x3f, 0x08, 0x7f, 0x00, 0xff, 0x00, 0x6b,
	0x01, 0x6b, 0x57
पूर्ण;

/*
 * This function ग_लिखोs to some SFR's, करोes some region2 ग_लिखोs, and then
 * eventually resets the codec with the 0x7ff verb. Not quite sure why it करोes
 * what it करोes.
 */
अटल व्योम ae5_रेजिस्टर_set(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	अचिन्हित पूर्णांक count = ARRAY_SIZE(ca0132_ae5_रेजिस्टर_set_addresses);
	स्थिर अचिन्हित पूर्णांक *addr = ca0132_ae5_रेजिस्टर_set_addresses;
	स्थिर अचिन्हित अक्षर *data = ca0132_ae5_रेजिस्टर_set_data;
	अचिन्हित पूर्णांक i, cur_addr;
	अचिन्हित अक्षर पंचांगp[3];

	अगर (ca0132_quirk(spec) == QUIRK_AE7)
		chipio_8051_ग_लिखो_pll_pmu(codec, 0x41, 0xc8);

	chipio_8051_ग_लिखो_direct(codec, 0x93, 0x10);
	chipio_8051_ग_लिखो_pll_pmu(codec, 0x44, 0xc2);

	अगर (ca0132_quirk(spec) == QUIRK_AE7) अणु
		पंचांगp[0] = 0x03;
		पंचांगp[1] = 0x03;
		पंचांगp[2] = 0x07;
	पूर्ण अन्यथा अणु
		पंचांगp[0] = 0x0f;
		पंचांगp[1] = 0x0f;
		पंचांगp[2] = 0x0f;
	पूर्ण

	क्रम (i = cur_addr = 0; i < 3; i++, cur_addr++)
		ग_लिखोb(पंचांगp[i], spec->mem_base + addr[cur_addr]);

	/*
	 * First ग_लिखोs are in single bytes, final are in 4 bytes. So, we use
	 * ग_लिखोb, then ग_लिखोl.
	 */
	क्रम (i = 0; cur_addr < 12; i++, cur_addr++)
		ग_लिखोb(data[i], spec->mem_base + addr[cur_addr]);

	क्रम (; cur_addr < count; i++, cur_addr++)
		ग_लिखोl(data[i], spec->mem_base + addr[cur_addr]);

	ग_लिखोl(0x00800001, spec->mem_base + 0x20c);

	अगर (ca0132_quirk(spec) == QUIRK_AE7) अणु
		ca0113_mmio_command_set_type2(codec, 0x48, 0x07, 0x83);
		ca0113_mmio_command_set(codec, 0x30, 0x2e, 0x3f);
	पूर्ण अन्यथा अणु
		ca0113_mmio_command_set(codec, 0x30, 0x2d, 0x3f);
	पूर्ण

	chipio_8051_ग_लिखो_direct(codec, 0x90, 0x00);
	chipio_8051_ग_लिखो_direct(codec, 0x90, 0x10);

	अगर (ca0132_quirk(spec) == QUIRK_AE5)
		ca0113_mmio_command_set(codec, 0x48, 0x07, 0x83);
पूर्ण

/*
 * Extra init functions क्रम alternative ca0132 codecs. Done
 * here so they करोn't clutter up the मुख्य ca0132_init function
 * anymore than they have to.
 */
अटल व्योम ca0132_alt_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	ca0132_alt_vol_setup(codec);

	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_SBZ:
		codec_dbg(codec, "SBZ alt_init");
		ca0132_gpio_init(codec);
		sbz_pre_dsp_setup(codec);
		snd_hda_sequence_ग_लिखो(codec, spec->chip_init_verbs);
		snd_hda_sequence_ग_लिखो(codec, spec->desktop_init_verbs);
		अवरोध;
	हाल QUIRK_R3DI:
		codec_dbg(codec, "R3DI alt_init");
		ca0132_gpio_init(codec);
		ca0132_gpio_setup(codec);
		r3di_gpio_dsp_status_set(codec, R3DI_DSP_DOWNLOADING);
		r3di_pre_dsp_setup(codec);
		snd_hda_sequence_ग_लिखो(codec, spec->chip_init_verbs);
		snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0, 0x6FF, 0xC4);
		अवरोध;
	हाल QUIRK_R3D:
		r3d_pre_dsp_setup(codec);
		snd_hda_sequence_ग_लिखो(codec, spec->chip_init_verbs);
		snd_hda_sequence_ग_लिखो(codec, spec->desktop_init_verbs);
		अवरोध;
	हाल QUIRK_AE5:
		ca0132_gpio_init(codec);
		chipio_8051_ग_लिखो_pll_pmu(codec, 0x49, 0x88);
		chipio_ग_लिखो(codec, 0x18b030, 0x00000020);
		snd_hda_sequence_ग_लिखो(codec, spec->chip_init_verbs);
		snd_hda_sequence_ग_लिखो(codec, spec->desktop_init_verbs);
		ca0113_mmio_command_set(codec, 0x30, 0x32, 0x3f);
		अवरोध;
	हाल QUIRK_AE7:
		ca0132_gpio_init(codec);
		chipio_8051_ग_लिखो_pll_pmu(codec, 0x49, 0x88);
		snd_hda_sequence_ग_लिखो(codec, spec->chip_init_verbs);
		snd_hda_sequence_ग_लिखो(codec, spec->desktop_init_verbs);
		chipio_ग_लिखो(codec, 0x18b008, 0x000000f8);
		chipio_ग_लिखो(codec, 0x18b008, 0x000000f0);
		chipio_ग_लिखो(codec, 0x18b030, 0x00000020);
		ca0113_mmio_command_set(codec, 0x30, 0x32, 0x3f);
		अवरोध;
	हाल QUIRK_ZXR:
		chipio_8051_ग_लिखो_pll_pmu(codec, 0x49, 0x88);
		snd_hda_sequence_ग_लिखो(codec, spec->chip_init_verbs);
		snd_hda_sequence_ग_लिखो(codec, spec->desktop_init_verbs);
		zxr_pre_dsp_setup(codec);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ca0132_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	पूर्णांक i;
	bool dsp_loaded;

	/*
	 * If the DSP is alपढ़ोy करोwnloaded, and init has been entered again,
	 * there's only two reasons क्रम it. One, the codec has awaken from a
	 * suspended state, and in that हाल dspload_is_loaded will वापस
	 * false, and the init will be ran again. The other reason it माला_लो
	 * re entered is on startup क्रम some reason it triggers a suspend and
	 * resume state. In this हाल, it will check अगर the DSP is करोwnloaded,
	 * and not run the init function again. For codecs using alt_functions,
	 * it will check अगर the DSP is loaded properly.
	 */
	अगर (spec->dsp_state == DSP_DOWNLOADED) अणु
		dsp_loaded = dspload_is_loaded(codec);
		अगर (!dsp_loaded) अणु
			spec->dsp_reload = true;
			spec->dsp_state = DSP_DOWNLOAD_INIT;
		पूर्ण अन्यथा अणु
			अगर (ca0132_quirk(spec) == QUIRK_SBZ)
				sbz_dsp_startup_check(codec);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (spec->dsp_state != DSP_DOWNLOAD_FAILED)
		spec->dsp_state = DSP_DOWNLOAD_INIT;
	spec->curr_chip_addx = INVALID_CHIP_ADDRESS;

	अगर (ca0132_use_pci_mmio(spec))
		ca0132_mmio_init(codec);

	snd_hda_घातer_up_pm(codec);

	अगर (ca0132_quirk(spec) == QUIRK_AE5 || ca0132_quirk(spec) == QUIRK_AE7)
		ae5_रेजिस्टर_set(codec);

	ca0132_init_params(codec);
	ca0132_init_flags(codec);

	snd_hda_sequence_ग_लिखो(codec, spec->base_init_verbs);

	अगर (ca0132_use_alt_functions(spec))
		ca0132_alt_init(codec);

	ca0132_करोwnload_dsp(codec);

	ca0132_refresh_widget_caps(codec);

	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_R3DI:
	हाल QUIRK_R3D:
		r3d_setup_शेषs(codec);
		अवरोध;
	हाल QUIRK_SBZ:
	हाल QUIRK_ZXR:
		sbz_setup_शेषs(codec);
		अवरोध;
	हाल QUIRK_AE5:
		ae5_setup_शेषs(codec);
		अवरोध;
	हाल QUIRK_AE7:
		ae7_setup_शेषs(codec);
		अवरोध;
	शेष:
		ca0132_setup_शेषs(codec);
		ca0132_init_analog_mic2(codec);
		ca0132_init_dmic(codec);
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < spec->num_outमाला_दो; i++)
		init_output(codec, spec->out_pins[i], spec->dacs[0]);

	init_output(codec, cfg->dig_out_pins[0], spec->dig_out);

	क्रम (i = 0; i < spec->num_inमाला_दो; i++)
		init_input(codec, spec->input_pins[i], spec->adcs[i]);

	init_input(codec, cfg->dig_in_pin, spec->dig_in);

	अगर (!ca0132_use_alt_functions(spec)) अणु
		snd_hda_sequence_ग_लिखो(codec, spec->chip_init_verbs);
		snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_PARAM_EX_ID_SET, 0x0D);
		snd_hda_codec_ग_लिखो(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_PARAM_EX_VALUE_SET, 0x20);
	पूर्ण

	अगर (ca0132_quirk(spec) == QUIRK_SBZ)
		ca0132_gpio_setup(codec);

	snd_hda_sequence_ग_लिखो(codec, spec->spec_init_verbs);
	अगर (ca0132_use_alt_functions(spec)) अणु
		ca0132_alt_select_out(codec);
		ca0132_alt_select_in(codec);
	पूर्ण अन्यथा अणु
		ca0132_select_out(codec);
		ca0132_select_mic(codec);
	पूर्ण

	snd_hda_jack_report_sync(codec);

	/*
	 * Re set the PlayEnhancement चयन on a resume event, because the
	 * controls will not be reloaded.
	 */
	अगर (spec->dsp_reload) अणु
		spec->dsp_reload = false;
		ca0132_pe_चयन_set(codec);
	पूर्ण

	snd_hda_घातer_करोwn_pm(codec);

	वापस 0;
पूर्ण

अटल पूर्णांक dbpro_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->स्वतःcfg;
	अचिन्हित पूर्णांक i;

	init_output(codec, cfg->dig_out_pins[0], spec->dig_out);
	init_input(codec, cfg->dig_in_pin, spec->dig_in);

	क्रम (i = 0; i < spec->num_inमाला_दो; i++)
		init_input(codec, spec->input_pins[i], spec->adcs[i]);

	वापस 0;
पूर्ण

अटल व्योम ca0132_मुक्त(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	cancel_delayed_work_sync(&spec->unsol_hp_work);
	snd_hda_घातer_up(codec);
	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_SBZ:
		sbz_निकास_chip(codec);
		अवरोध;
	हाल QUIRK_ZXR:
		zxr_निकास_chip(codec);
		अवरोध;
	हाल QUIRK_R3D:
		r3d_निकास_chip(codec);
		अवरोध;
	हाल QUIRK_AE5:
		ae5_निकास_chip(codec);
		अवरोध;
	हाल QUIRK_AE7:
		ae7_निकास_chip(codec);
		अवरोध;
	हाल QUIRK_R3DI:
		r3di_gpio_shutकरोwn(codec);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	snd_hda_sequence_ग_लिखो(codec, spec->base_निकास_verbs);
	ca0132_निकास_chip(codec);

	snd_hda_घातer_करोwn(codec);
#अगर_घोषित CONFIG_PCI
	अगर (spec->mem_base)
		pci_iounmap(codec->bus->pci, spec->mem_base);
#पूर्ण_अगर
	kमुक्त(spec->spec_init_verbs);
	kमुक्त(codec->spec);
पूर्ण

अटल व्योम dbpro_मुक्त(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	zxr_dbpro_घातer_state_shutकरोwn(codec);

	kमुक्त(spec->spec_init_verbs);
	kमुक्त(codec->spec);
पूर्ण

अटल व्योम ca0132_reboot_notअगरy(काष्ठा hda_codec *codec)
अणु
	codec->patch_ops.मुक्त(codec);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ca0132_suspend(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	cancel_delayed_work_sync(&spec->unsol_hp_work);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा hda_codec_ops ca0132_patch_ops = अणु
	.build_controls = ca0132_build_controls,
	.build_pcms = ca0132_build_pcms,
	.init = ca0132_init,
	.मुक्त = ca0132_मुक्त,
	.unsol_event = snd_hda_jack_unsol_event,
#अगर_घोषित CONFIG_PM
	.suspend = ca0132_suspend,
#पूर्ण_अगर
	.reboot_notअगरy = ca0132_reboot_notअगरy,
पूर्ण;

अटल स्थिर काष्ठा hda_codec_ops dbpro_patch_ops = अणु
	.build_controls = dbpro_build_controls,
	.build_pcms = dbpro_build_pcms,
	.init = dbpro_init,
	.मुक्त = dbpro_मुक्त,
पूर्ण;

अटल व्योम ca0132_config(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	spec->dacs[0] = 0x2;
	spec->dacs[1] = 0x3;
	spec->dacs[2] = 0x4;

	spec->multiout.dac_nids = spec->dacs;
	spec->multiout.num_dacs = 3;

	अगर (!ca0132_use_alt_functions(spec))
		spec->multiout.max_channels = 2;
	अन्यथा
		spec->multiout.max_channels = 6;

	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_ALIENWARE:
		codec_dbg(codec, "%s: QUIRK_ALIENWARE applied.\n", __func__);
		snd_hda_apply_pincfgs(codec, alienware_pincfgs);
		अवरोध;
	हाल QUIRK_SBZ:
		codec_dbg(codec, "%s: QUIRK_SBZ applied.\n", __func__);
		snd_hda_apply_pincfgs(codec, sbz_pincfgs);
		अवरोध;
	हाल QUIRK_ZXR:
		codec_dbg(codec, "%s: QUIRK_ZXR applied.\n", __func__);
		snd_hda_apply_pincfgs(codec, zxr_pincfgs);
		अवरोध;
	हाल QUIRK_R3D:
		codec_dbg(codec, "%s: QUIRK_R3D applied.\n", __func__);
		snd_hda_apply_pincfgs(codec, r3d_pincfgs);
		अवरोध;
	हाल QUIRK_R3DI:
		codec_dbg(codec, "%s: QUIRK_R3DI applied.\n", __func__);
		snd_hda_apply_pincfgs(codec, r3di_pincfgs);
		अवरोध;
	हाल QUIRK_AE5:
		codec_dbg(codec, "%s: QUIRK_AE5 applied.\n", __func__);
		snd_hda_apply_pincfgs(codec, ae5_pincfgs);
		अवरोध;
	हाल QUIRK_AE7:
		codec_dbg(codec, "%s: QUIRK_AE7 applied.\n", __func__);
		snd_hda_apply_pincfgs(codec, ae7_pincfgs);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_ALIENWARE:
		spec->num_outमाला_दो = 2;
		spec->out_pins[0] = 0x0b; /* speaker out */
		spec->out_pins[1] = 0x0f;
		spec->shared_out_nid = 0x2;
		spec->unsol_tag_hp = 0x0f;

		spec->adcs[0] = 0x7; /* digital mic / analog mic1 */
		spec->adcs[1] = 0x8; /* analog mic2 */
		spec->adcs[2] = 0xa; /* what u hear */

		spec->num_inमाला_दो = 3;
		spec->input_pins[0] = 0x12;
		spec->input_pins[1] = 0x11;
		spec->input_pins[2] = 0x13;
		spec->shared_mic_nid = 0x7;
		spec->unsol_tag_amic1 = 0x11;
		अवरोध;
	हाल QUIRK_SBZ:
	हाल QUIRK_R3D:
		spec->num_outमाला_दो = 2;
		spec->out_pins[0] = 0x0B; /* Line out */
		spec->out_pins[1] = 0x0F; /* Rear headphone out */
		spec->out_pins[2] = 0x10; /* Front Headphone / Center/LFE*/
		spec->out_pins[3] = 0x11; /* Rear surround */
		spec->shared_out_nid = 0x2;
		spec->unsol_tag_hp = spec->out_pins[1];
		spec->unsol_tag_front_hp = spec->out_pins[2];

		spec->adcs[0] = 0x7; /* Rear Mic / Line-in */
		spec->adcs[1] = 0x8; /* Front Mic, but only अगर no DSP */
		spec->adcs[2] = 0xa; /* what u hear */

		spec->num_inमाला_दो = 2;
		spec->input_pins[0] = 0x12; /* Rear Mic / Line-in */
		spec->input_pins[1] = 0x13; /* What U Hear */
		spec->shared_mic_nid = 0x7;
		spec->unsol_tag_amic1 = spec->input_pins[0];

		/* SPDIF I/O */
		spec->dig_out = 0x05;
		spec->multiout.dig_out_nid = spec->dig_out;
		spec->dig_in = 0x09;
		अवरोध;
	हाल QUIRK_ZXR:
		spec->num_outमाला_दो = 2;
		spec->out_pins[0] = 0x0B; /* Line out */
		spec->out_pins[1] = 0x0F; /* Rear headphone out */
		spec->out_pins[2] = 0x10; /* Center/LFE */
		spec->out_pins[3] = 0x11; /* Rear surround */
		spec->shared_out_nid = 0x2;
		spec->unsol_tag_hp = spec->out_pins[1];
		spec->unsol_tag_front_hp = spec->out_pins[2];

		spec->adcs[0] = 0x7; /* Rear Mic / Line-in */
		spec->adcs[1] = 0x8; /* Not connected, no front mic */
		spec->adcs[2] = 0xa; /* what u hear */

		spec->num_inमाला_दो = 2;
		spec->input_pins[0] = 0x12; /* Rear Mic / Line-in */
		spec->input_pins[1] = 0x13; /* What U Hear */
		spec->shared_mic_nid = 0x7;
		spec->unsol_tag_amic1 = spec->input_pins[0];
		अवरोध;
	हाल QUIRK_ZXR_DBPRO:
		spec->adcs[0] = 0x8; /* ZxR DBPro Aux In */

		spec->num_inमाला_दो = 1;
		spec->input_pins[0] = 0x11; /* RCA Line-in */

		spec->dig_out = 0x05;
		spec->multiout.dig_out_nid = spec->dig_out;

		spec->dig_in = 0x09;
		अवरोध;
	हाल QUIRK_AE5:
	हाल QUIRK_AE7:
		spec->num_outमाला_दो = 2;
		spec->out_pins[0] = 0x0B; /* Line out */
		spec->out_pins[1] = 0x11; /* Rear headphone out */
		spec->out_pins[2] = 0x10; /* Front Headphone / Center/LFE*/
		spec->out_pins[3] = 0x0F; /* Rear surround */
		spec->shared_out_nid = 0x2;
		spec->unsol_tag_hp = spec->out_pins[1];
		spec->unsol_tag_front_hp = spec->out_pins[2];

		spec->adcs[0] = 0x7; /* Rear Mic / Line-in */
		spec->adcs[1] = 0x8; /* Front Mic, but only अगर no DSP */
		spec->adcs[2] = 0xa; /* what u hear */

		spec->num_inमाला_दो = 2;
		spec->input_pins[0] = 0x12; /* Rear Mic / Line-in */
		spec->input_pins[1] = 0x13; /* What U Hear */
		spec->shared_mic_nid = 0x7;
		spec->unsol_tag_amic1 = spec->input_pins[0];

		/* SPDIF I/O */
		spec->dig_out = 0x05;
		spec->multiout.dig_out_nid = spec->dig_out;
		अवरोध;
	हाल QUIRK_R3DI:
		spec->num_outमाला_दो = 2;
		spec->out_pins[0] = 0x0B; /* Line out */
		spec->out_pins[1] = 0x0F; /* Rear headphone out */
		spec->out_pins[2] = 0x10; /* Front Headphone / Center/LFE*/
		spec->out_pins[3] = 0x11; /* Rear surround */
		spec->shared_out_nid = 0x2;
		spec->unsol_tag_hp = spec->out_pins[1];
		spec->unsol_tag_front_hp = spec->out_pins[2];

		spec->adcs[0] = 0x07; /* Rear Mic / Line-in */
		spec->adcs[1] = 0x08; /* Front Mic, but only अगर no DSP */
		spec->adcs[2] = 0x0a; /* what u hear */

		spec->num_inमाला_दो = 2;
		spec->input_pins[0] = 0x12; /* Rear Mic / Line-in */
		spec->input_pins[1] = 0x13; /* What U Hear */
		spec->shared_mic_nid = 0x7;
		spec->unsol_tag_amic1 = spec->input_pins[0];

		/* SPDIF I/O */
		spec->dig_out = 0x05;
		spec->multiout.dig_out_nid = spec->dig_out;
		अवरोध;
	शेष:
		spec->num_outमाला_दो = 2;
		spec->out_pins[0] = 0x0b; /* speaker out */
		spec->out_pins[1] = 0x10; /* headphone out */
		spec->shared_out_nid = 0x2;
		spec->unsol_tag_hp = spec->out_pins[1];

		spec->adcs[0] = 0x7; /* digital mic / analog mic1 */
		spec->adcs[1] = 0x8; /* analog mic2 */
		spec->adcs[2] = 0xa; /* what u hear */

		spec->num_inमाला_दो = 3;
		spec->input_pins[0] = 0x12;
		spec->input_pins[1] = 0x11;
		spec->input_pins[2] = 0x13;
		spec->shared_mic_nid = 0x7;
		spec->unsol_tag_amic1 = spec->input_pins[0];

		/* SPDIF I/O */
		spec->dig_out = 0x05;
		spec->multiout.dig_out_nid = spec->dig_out;
		spec->dig_in = 0x09;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ca0132_prepare_verbs(काष्ठा hda_codec *codec)
अणु
/* Verbs + terminator (an empty element) */
#घोषणा NUM_SPEC_VERBS 2
	काष्ठा ca0132_spec *spec = codec->spec;

	spec->chip_init_verbs = ca0132_init_verbs0;
	/*
	 * Since desktop cards use pci_mmio, this can be used to determine
	 * whether or not to use these verbs instead of a separate bool.
	 */
	अगर (ca0132_use_pci_mmio(spec))
		spec->desktop_init_verbs = ca0132_init_verbs1;
	spec->spec_init_verbs = kसुस्मृति(NUM_SPEC_VERBS,
					माप(काष्ठा hda_verb),
					GFP_KERNEL);
	अगर (!spec->spec_init_verbs)
		वापस -ENOMEM;

	/* config EAPD */
	spec->spec_init_verbs[0].nid = 0x0b;
	spec->spec_init_verbs[0].param = 0x78D;
	spec->spec_init_verbs[0].verb = 0x00;

	/* Previously commented configuration */
	/*
	spec->spec_init_verbs[2].nid = 0x0b;
	spec->spec_init_verbs[2].param = AC_VERB_SET_EAPD_BTLENABLE;
	spec->spec_init_verbs[2].verb = 0x02;

	spec->spec_init_verbs[3].nid = 0x10;
	spec->spec_init_verbs[3].param = 0x78D;
	spec->spec_init_verbs[3].verb = 0x02;

	spec->spec_init_verbs[4].nid = 0x10;
	spec->spec_init_verbs[4].param = AC_VERB_SET_EAPD_BTLENABLE;
	spec->spec_init_verbs[4].verb = 0x02;
	*/

	/* Terminator: spec->spec_init_verbs[NUM_SPEC_VERBS-1] */
	वापस 0;
पूर्ण

/*
 * The Sound Blaster ZxR shares the same PCI subप्रणाली ID as some regular
 * Sound Blaster Z cards. However, they have dअगरferent HDA codec subप्रणाली
 * ID's. So, we check for the ZxR's subप्रणाली ID, as well as the DBPro
 * daughter boards ID.
 */
अटल व्योम sbz_detect_quirk(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec = codec->spec;

	चयन (codec->core.subप्रणाली_id) अणु
	हाल 0x11020033:
		spec->quirk = QUIRK_ZXR;
		अवरोध;
	हाल 0x1102003f:
		spec->quirk = QUIRK_ZXR_DBPRO;
		अवरोध;
	शेष:
		spec->quirk = QUIRK_SBZ;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक patch_ca0132(काष्ठा hda_codec *codec)
अणु
	काष्ठा ca0132_spec *spec;
	पूर्णांक err;
	स्थिर काष्ठा snd_pci_quirk *quirk;

	codec_dbg(codec, "patch_ca0132\n");

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	codec->spec = spec;
	spec->codec = codec;

	/* Detect codec quirk */
	quirk = snd_pci_quirk_lookup(codec->bus->pci, ca0132_quirks);
	अगर (quirk)
		spec->quirk = quirk->value;
	अन्यथा
		spec->quirk = QUIRK_NONE;
	अगर (ca0132_quirk(spec) == QUIRK_SBZ)
		sbz_detect_quirk(codec);

	अगर (ca0132_quirk(spec) == QUIRK_ZXR_DBPRO)
		codec->patch_ops = dbpro_patch_ops;
	अन्यथा
		codec->patch_ops = ca0132_patch_ops;

	codec->pcm_क्रमmat_first = 1;
	codec->no_sticky_stream = 1;


	spec->dsp_state = DSP_DOWNLOAD_INIT;
	spec->num_mixers = 1;

	/* Set which mixers each quirk uses. */
	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_SBZ:
		spec->mixers[0] = desktop_mixer;
		snd_hda_codec_set_name(codec, "Sound Blaster Z");
		अवरोध;
	हाल QUIRK_ZXR:
		spec->mixers[0] = desktop_mixer;
		snd_hda_codec_set_name(codec, "Sound Blaster ZxR");
		अवरोध;
	हाल QUIRK_ZXR_DBPRO:
		अवरोध;
	हाल QUIRK_R3D:
		spec->mixers[0] = desktop_mixer;
		snd_hda_codec_set_name(codec, "Recon3D");
		अवरोध;
	हाल QUIRK_R3DI:
		spec->mixers[0] = r3di_mixer;
		snd_hda_codec_set_name(codec, "Recon3Di");
		अवरोध;
	हाल QUIRK_AE5:
		spec->mixers[0] = desktop_mixer;
		snd_hda_codec_set_name(codec, "Sound BlasterX AE-5");
		अवरोध;
	हाल QUIRK_AE7:
		spec->mixers[0] = desktop_mixer;
		snd_hda_codec_set_name(codec, "Sound Blaster AE-7");
		अवरोध;
	शेष:
		spec->mixers[0] = ca0132_mixer;
		अवरोध;
	पूर्ण

	/* Setup whether or not to use alt functions/controls/pci_mmio */
	चयन (ca0132_quirk(spec)) अणु
	हाल QUIRK_SBZ:
	हाल QUIRK_R3D:
	हाल QUIRK_AE5:
	हाल QUIRK_AE7:
	हाल QUIRK_ZXR:
		spec->use_alt_controls = true;
		spec->use_alt_functions = true;
		spec->use_pci_mmio = true;
		अवरोध;
	हाल QUIRK_R3DI:
		spec->use_alt_controls = true;
		spec->use_alt_functions = true;
		spec->use_pci_mmio = false;
		अवरोध;
	शेष:
		spec->use_alt_controls = false;
		spec->use_alt_functions = false;
		spec->use_pci_mmio = false;
		अवरोध;
	पूर्ण

#अगर_घोषित CONFIG_PCI
	अगर (spec->use_pci_mmio) अणु
		spec->mem_base = pci_iomap(codec->bus->pci, 2, 0xC20);
		अगर (spec->mem_base == शून्य) अणु
			codec_warn(codec, "pci_iomap failed! Setting quirk to QUIRK_NONE.");
			spec->quirk = QUIRK_NONE;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	spec->base_init_verbs = ca0132_base_init_verbs;
	spec->base_निकास_verbs = ca0132_base_निकास_verbs;

	INIT_DELAYED_WORK(&spec->unsol_hp_work, ca0132_unsol_hp_delayed);

	ca0132_init_chip(codec);

	ca0132_config(codec);

	err = ca0132_prepare_verbs(codec);
	अगर (err < 0)
		जाओ error;

	err = snd_hda_parse_pin_def_config(codec, &spec->स्वतःcfg, शून्य);
	अगर (err < 0)
		जाओ error;

	ca0132_setup_unsol(codec);

	वापस 0;

 error:
	ca0132_मुक्त(codec);
	वापस err;
पूर्ण

/*
 * patch entries
 */
अटल स्थिर काष्ठा hda_device_id snd_hda_id_ca0132[] = अणु
	HDA_CODEC_ENTRY(0x11020011, "CA0132", patch_ca0132),
	अणुपूर्ण /* terminator */
पूर्ण;
MODULE_DEVICE_TABLE(hdaudio, snd_hda_id_ca0132);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Creative Sound Core3D codec");

अटल काष्ठा hda_codec_driver ca0132_driver = अणु
	.id = snd_hda_id_ca0132,
पूर्ण;

module_hda_codec_driver(ca0132_driver);
