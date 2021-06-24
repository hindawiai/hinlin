<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA SoC codec क्रम HDMI encoder drivers
 * Copyright (C) 2015 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Jyri Sarha <jsarha@ti.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/pcm_drm_eld.h>
#समावेश <sound/hdmi-codec.h>
#समावेश <sound/pcm_iec958.h>

#समावेश <drm/drm_crtc.h> /* This is only to get MAX_ELD_BYTES */

#घोषणा HDMI_CODEC_CHMAP_IDX_UNKNOWN  -1

काष्ठा hdmi_codec_channel_map_table अणु
	अचिन्हित अक्षर map;	/* ALSA API channel map position */
पूर्ण;

/*
 * CEA speaker placement क्रम HDMI 1.4:
 *
 *  FL  FLC   FC   FRC   FR   FRW
 *
 *                                  LFE
 *
 *  RL  RLC   RC   RRC   RR
 *
 *  Speaker placement has to be extended to support HDMI 2.0
 */
क्रमागत hdmi_codec_cea_spk_placement अणु
	FL  = BIT(0),	/* Front Left           */
	FC  = BIT(1),	/* Front Center         */
	FR  = BIT(2),	/* Front Right          */
	FLC = BIT(3),	/* Front Left Center    */
	FRC = BIT(4),	/* Front Right Center   */
	RL  = BIT(5),	/* Rear Left            */
	RC  = BIT(6),	/* Rear Center          */
	RR  = BIT(7),	/* Rear Right           */
	RLC = BIT(8),	/* Rear Left Center     */
	RRC = BIT(9),	/* Rear Right Center    */
	LFE = BIT(10),	/* Low Frequency Effect */
पूर्ण;

/*
 * cea Speaker allocation काष्ठाure
 */
काष्ठा hdmi_codec_cea_spk_alloc अणु
	स्थिर पूर्णांक ca_id;
	अचिन्हित पूर्णांक n_ch;
	अचिन्हित दीर्घ mask;
पूर्ण;

/* Channel maps  stereo HDMI */
अटल स्थिर काष्ठा snd_pcm_chmap_elem hdmi_codec_stereo_chmaps[] = अणु
	अणु .channels = 2,
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;

/* Channel maps क्रम multi-channel playbacks, up to 8 n_ch */
अटल स्थिर काष्ठा snd_pcm_chmap_elem hdmi_codec_8ch_chmaps[] = अणु
	अणु .channels = 2, /* CA_ID 0x00 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR पूर्ण पूर्ण,
	अणु .channels = 4, /* CA_ID 0x01 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_NA पूर्ण पूर्ण,
	अणु .channels = 4, /* CA_ID 0x02 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FC पूर्ण पूर्ण,
	अणु .channels = 4, /* CA_ID 0x03 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_FC पूर्ण पूर्ण,
	अणु .channels = 6, /* CA_ID 0x04 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_NA, SNDRV_CHMAP_RC, SNDRV_CHMAP_NA पूर्ण पूर्ण,
	अणु .channels = 6, /* CA_ID 0x05 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_NA, SNDRV_CHMAP_RC, SNDRV_CHMAP_NA पूर्ण पूर्ण,
	अणु .channels = 6, /* CA_ID 0x06 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_RC, SNDRV_CHMAP_NA पूर्ण पूर्ण,
	अणु .channels = 6, /* CA_ID 0x07 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_RC, SNDRV_CHMAP_NA पूर्ण पूर्ण,
	अणु .channels = 6, /* CA_ID 0x08 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_NA, SNDRV_CHMAP_RL, SNDRV_CHMAP_RR पूर्ण पूर्ण,
	अणु .channels = 6, /* CA_ID 0x09 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_NA, SNDRV_CHMAP_RL, SNDRV_CHMAP_RR पूर्ण पूर्ण,
	अणु .channels = 6, /* CA_ID 0x0A */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_RL, SNDRV_CHMAP_RR पूर्ण पूर्ण,
	अणु .channels = 6, /* CA_ID 0x0B */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_RL, SNDRV_CHMAP_RR पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x0C */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_NA, SNDRV_CHMAP_RL, SNDRV_CHMAP_RR,
		   SNDRV_CHMAP_RC, SNDRV_CHMAP_NA पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x0D */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_NA, SNDRV_CHMAP_RL, SNDRV_CHMAP_RR,
		   SNDRV_CHMAP_RC, SNDRV_CHMAP_NA पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x0E */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_RL, SNDRV_CHMAP_RR,
		   SNDRV_CHMAP_RC, SNDRV_CHMAP_NA पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x0F */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_RL, SNDRV_CHMAP_RR,
		   SNDRV_CHMAP_RC, SNDRV_CHMAP_NA पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x10 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_NA, SNDRV_CHMAP_RL, SNDRV_CHMAP_RR,
		   SNDRV_CHMAP_RLC, SNDRV_CHMAP_RRC पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x11 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_NA, SNDRV_CHMAP_RL, SNDRV_CHMAP_RR,
		   SNDRV_CHMAP_RLC, SNDRV_CHMAP_RRC पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x12 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_RL, SNDRV_CHMAP_RR,
		   SNDRV_CHMAP_RLC, SNDRV_CHMAP_RRC पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x13 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_RL, SNDRV_CHMAP_RR,
		   SNDRV_CHMAP_RLC, SNDRV_CHMAP_RRC पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x14 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_NA, SNDRV_CHMAP_NA, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FLC, SNDRV_CHMAP_FRC पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x15 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_NA, SNDRV_CHMAP_NA, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FLC, SNDRV_CHMAP_FRC पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x16 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_NA, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FLC, SNDRV_CHMAP_FRC पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x17 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_NA, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FLC, SNDRV_CHMAP_FRC पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x18 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_NA, SNDRV_CHMAP_NA, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FLC, SNDRV_CHMAP_FRC पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x19 */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_NA, SNDRV_CHMAP_NA, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FLC, SNDRV_CHMAP_FRC पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x1A */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_NA, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FLC, SNDRV_CHMAP_FRC पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x1B */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_NA, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FLC, SNDRV_CHMAP_FRC पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x1C */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_NA, SNDRV_CHMAP_NA, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FLC, SNDRV_CHMAP_FRC पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x1D */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_NA, SNDRV_CHMAP_NA, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FLC, SNDRV_CHMAP_FRC पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x1E */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_NA, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FLC, SNDRV_CHMAP_FRC पूर्ण पूर्ण,
	अणु .channels = 8, /* CA_ID 0x1F */
	  .map = अणु SNDRV_CHMAP_FL, SNDRV_CHMAP_FR, SNDRV_CHMAP_LFE,
		   SNDRV_CHMAP_FC, SNDRV_CHMAP_NA, SNDRV_CHMAP_NA,
		   SNDRV_CHMAP_FLC, SNDRV_CHMAP_FRC पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * hdmi_codec_channel_alloc: speaker configuration available क्रम CEA
 *
 * This is an ordered list that must match with hdmi_codec_8ch_chmaps काष्ठा
 * The preceding ones have better chances to be selected by
 * hdmi_codec_get_ch_alloc_table_idx().
 */
अटल स्थिर काष्ठा hdmi_codec_cea_spk_alloc hdmi_codec_channel_alloc[] = अणु
	अणु .ca_id = 0x00, .n_ch = 2,
	  .mask = FL | FRपूर्ण,
	/* 2.1 */
	अणु .ca_id = 0x01, .n_ch = 4,
	  .mask = FL | FR | LFEपूर्ण,
	/* Dolby Surround */
	अणु .ca_id = 0x02, .n_ch = 4,
	  .mask = FL | FR | FC पूर्ण,
	/* surround51 */
	अणु .ca_id = 0x0b, .n_ch = 6,
	  .mask = FL | FR | LFE | FC | RL | RRपूर्ण,
	/* surround40 */
	अणु .ca_id = 0x08, .n_ch = 6,
	  .mask = FL | FR | RL | RR पूर्ण,
	/* surround41 */
	अणु .ca_id = 0x09, .n_ch = 6,
	  .mask = FL | FR | LFE | RL | RR पूर्ण,
	/* surround50 */
	अणु .ca_id = 0x0a, .n_ch = 6,
	  .mask = FL | FR | FC | RL | RR पूर्ण,
	/* 6.1 */
	अणु .ca_id = 0x0f, .n_ch = 8,
	  .mask = FL | FR | LFE | FC | RL | RR | RC पूर्ण,
	/* surround71 */
	अणु .ca_id = 0x13, .n_ch = 8,
	  .mask = FL | FR | LFE | FC | RL | RR | RLC | RRC पूर्ण,
	/* others */
	अणु .ca_id = 0x03, .n_ch = 8,
	  .mask = FL | FR | LFE | FC पूर्ण,
	अणु .ca_id = 0x04, .n_ch = 8,
	  .mask = FL | FR | RCपूर्ण,
	अणु .ca_id = 0x05, .n_ch = 8,
	  .mask = FL | FR | LFE | RC पूर्ण,
	अणु .ca_id = 0x06, .n_ch = 8,
	  .mask = FL | FR | FC | RC पूर्ण,
	अणु .ca_id = 0x07, .n_ch = 8,
	  .mask = FL | FR | LFE | FC | RC पूर्ण,
	अणु .ca_id = 0x0c, .n_ch = 8,
	  .mask = FL | FR | RC | RL | RR पूर्ण,
	अणु .ca_id = 0x0d, .n_ch = 8,
	  .mask = FL | FR | LFE | RL | RR | RC पूर्ण,
	अणु .ca_id = 0x0e, .n_ch = 8,
	  .mask = FL | FR | FC | RL | RR | RC पूर्ण,
	अणु .ca_id = 0x10, .n_ch = 8,
	  .mask = FL | FR | RL | RR | RLC | RRC पूर्ण,
	अणु .ca_id = 0x11, .n_ch = 8,
	  .mask = FL | FR | LFE | RL | RR | RLC | RRC पूर्ण,
	अणु .ca_id = 0x12, .n_ch = 8,
	  .mask = FL | FR | FC | RL | RR | RLC | RRC पूर्ण,
	अणु .ca_id = 0x14, .n_ch = 8,
	  .mask = FL | FR | FLC | FRC पूर्ण,
	अणु .ca_id = 0x15, .n_ch = 8,
	  .mask = FL | FR | LFE | FLC | FRC पूर्ण,
	अणु .ca_id = 0x16, .n_ch = 8,
	  .mask = FL | FR | FC | FLC | FRC पूर्ण,
	अणु .ca_id = 0x17, .n_ch = 8,
	  .mask = FL | FR | LFE | FC | FLC | FRC पूर्ण,
	अणु .ca_id = 0x18, .n_ch = 8,
	  .mask = FL | FR | RC | FLC | FRC पूर्ण,
	अणु .ca_id = 0x19, .n_ch = 8,
	  .mask = FL | FR | LFE | RC | FLC | FRC पूर्ण,
	अणु .ca_id = 0x1a, .n_ch = 8,
	  .mask = FL | FR | RC | FC | FLC | FRC पूर्ण,
	अणु .ca_id = 0x1b, .n_ch = 8,
	  .mask = FL | FR | LFE | RC | FC | FLC | FRC पूर्ण,
	अणु .ca_id = 0x1c, .n_ch = 8,
	  .mask = FL | FR | RL | RR | FLC | FRC पूर्ण,
	अणु .ca_id = 0x1d, .n_ch = 8,
	  .mask = FL | FR | LFE | RL | RR | FLC | FRC पूर्ण,
	अणु .ca_id = 0x1e, .n_ch = 8,
	  .mask = FL | FR | FC | RL | RR | FLC | FRC पूर्ण,
	अणु .ca_id = 0x1f, .n_ch = 8,
	  .mask = FL | FR | LFE | FC | RL | RR | FLC | FRC पूर्ण,
पूर्ण;

काष्ठा hdmi_codec_priv अणु
	काष्ठा hdmi_codec_pdata hcd;
	uपूर्णांक8_t eld[MAX_ELD_BYTES];
	काष्ठा snd_pcm_chmap *chmap_info;
	अचिन्हित पूर्णांक chmap_idx;
	काष्ठा mutex lock;
	bool busy;
	काष्ठा snd_soc_jack *jack;
	अचिन्हित पूर्णांक jack_status;
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget hdmi_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("TX"),
	SND_SOC_DAPM_OUTPUT("RX"),
पूर्ण;

क्रमागत अणु
	DAI_ID_I2S = 0,
	DAI_ID_SPDIF,
पूर्ण;

अटल पूर्णांक hdmi_eld_ctl_info(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = माप_field(काष्ठा hdmi_codec_priv, eld);

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_eld_ctl_get(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा hdmi_codec_priv *hcp = snd_soc_component_get_drvdata(component);

	स_नकल(ucontrol->value.bytes.data, hcp->eld, माप(hcp->eld));

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ hdmi_codec_spk_mask_from_alloc(पूर्णांक spk_alloc)
अणु
	पूर्णांक i;
	अटल स्थिर अचिन्हित दीर्घ hdmi_codec_eld_spk_alloc_bits[] = अणु
		[0] = FL | FR, [1] = LFE, [2] = FC, [3] = RL | RR,
		[4] = RC, [5] = FLC | FRC, [6] = RLC | RRC,
	पूर्ण;
	अचिन्हित दीर्घ spk_mask = 0;

	क्रम (i = 0; i < ARRAY_SIZE(hdmi_codec_eld_spk_alloc_bits); i++) अणु
		अगर (spk_alloc & (1 << i))
			spk_mask |= hdmi_codec_eld_spk_alloc_bits[i];
	पूर्ण

	वापस spk_mask;
पूर्ण

अटल व्योम hdmi_codec_eld_chmap(काष्ठा hdmi_codec_priv *hcp)
अणु
	u8 spk_alloc;
	अचिन्हित दीर्घ spk_mask;

	spk_alloc = drm_eld_get_spk_alloc(hcp->eld);
	spk_mask = hdmi_codec_spk_mask_from_alloc(spk_alloc);

	/* Detect अगर only stereo supported, अन्यथा वापस 8 channels mappings */
	अगर ((spk_mask & ~(FL | FR)) && hcp->chmap_info->max_channels > 2)
		hcp->chmap_info->chmap = hdmi_codec_8ch_chmaps;
	अन्यथा
		hcp->chmap_info->chmap = hdmi_codec_stereo_chmaps;
पूर्ण

अटल पूर्णांक hdmi_codec_get_ch_alloc_table_idx(काष्ठा hdmi_codec_priv *hcp,
					     अचिन्हित अक्षर channels)
अणु
	पूर्णांक i;
	u8 spk_alloc;
	अचिन्हित दीर्घ spk_mask;
	स्थिर काष्ठा hdmi_codec_cea_spk_alloc *cap = hdmi_codec_channel_alloc;

	spk_alloc = drm_eld_get_spk_alloc(hcp->eld);
	spk_mask = hdmi_codec_spk_mask_from_alloc(spk_alloc);

	क्रम (i = 0; i < ARRAY_SIZE(hdmi_codec_channel_alloc); i++, cap++) अणु
		/* If spk_alloc == 0, HDMI is unplugged वापस stereo config*/
		अगर (!spk_alloc && cap->ca_id == 0)
			वापस i;
		अगर (cap->n_ch != channels)
			जारी;
		अगर (!(cap->mask == (spk_mask & cap->mask)))
			जारी;
		वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण
अटल पूर्णांक hdmi_codec_chmap_ctl_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित स्थिर अक्षर *map;
	अचिन्हित पूर्णांक i;
	काष्ठा snd_pcm_chmap *info = snd_kcontrol_chip(kcontrol);
	काष्ठा hdmi_codec_priv *hcp = info->निजी_data;

	map = info->chmap[hcp->chmap_idx].map;

	क्रम (i = 0; i < info->max_channels; i++) अणु
		अगर (hcp->chmap_idx == HDMI_CODEC_CHMAP_IDX_UNKNOWN)
			ucontrol->value.पूर्णांकeger.value[i] = 0;
		अन्यथा
			ucontrol->value.पूर्णांकeger.value[i] = map[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_codec_startup(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdmi_codec_priv *hcp = snd_soc_dai_get_drvdata(dai);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	पूर्णांक ret = 0;

	mutex_lock(&hcp->lock);
	अगर (hcp->busy) अणु
		dev_err(dai->dev, "Only one simultaneous stream supported!\n");
		mutex_unlock(&hcp->lock);
		वापस -EINVAL;
	पूर्ण

	अगर (hcp->hcd.ops->audio_startup) अणु
		ret = hcp->hcd.ops->audio_startup(dai->dev->parent, hcp->hcd.data);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (tx && hcp->hcd.ops->get_eld) अणु
		ret = hcp->hcd.ops->get_eld(dai->dev->parent, hcp->hcd.data,
					    hcp->eld, माप(hcp->eld));
		अगर (ret)
			जाओ err;

		ret = snd_pcm_hw_स्थिरraपूर्णांक_eld(substream->runसमय, hcp->eld);
		अगर (ret)
			जाओ err;

		/* Select chmap supported */
		hdmi_codec_eld_chmap(hcp);
	पूर्ण

	hcp->busy = true;

err:
	mutex_unlock(&hcp->lock);
	वापस ret;
पूर्ण

अटल व्योम hdmi_codec_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdmi_codec_priv *hcp = snd_soc_dai_get_drvdata(dai);

	hcp->chmap_idx = HDMI_CODEC_CHMAP_IDX_UNKNOWN;
	hcp->hcd.ops->audio_shutकरोwn(dai->dev->parent, hcp->hcd.data);

	mutex_lock(&hcp->lock);
	hcp->busy = false;
	mutex_unlock(&hcp->lock);
पूर्ण

अटल पूर्णांक hdmi_codec_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdmi_codec_priv *hcp = snd_soc_dai_get_drvdata(dai);
	काष्ठा hdmi_codec_daअगरmt *cf = dai->playback_dma_data;
	काष्ठा hdmi_codec_params hp = अणु
		.iec = अणु
			.status = अणु 0 पूर्ण,
			.subcode = अणु 0 पूर्ण,
			.pad = 0,
			.dig_subframe = अणु 0 पूर्ण,
		पूर्ण
	पूर्ण;
	पूर्णांक ret, idx;

	dev_dbg(dai->dev, "%s() width %d rate %d channels %d\n", __func__,
		params_width(params), params_rate(params),
		params_channels(params));

	ret = snd_pcm_create_iec958_consumer_hw_params(params, hp.iec.status,
						       माप(hp.iec.status));
	अगर (ret < 0) अणु
		dev_err(dai->dev, "Creating IEC958 channel status failed %d\n",
			ret);
		वापस ret;
	पूर्ण

	hdmi_audio_infoframe_init(&hp.cea);
	hp.cea.channels = params_channels(params);
	hp.cea.coding_type = HDMI_AUDIO_CODING_TYPE_STREAM;
	hp.cea.sample_size = HDMI_AUDIO_SAMPLE_SIZE_STREAM;
	hp.cea.sample_frequency = HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM;

	/* Select a channel allocation that matches with ELD and pcm channels */
	idx = hdmi_codec_get_ch_alloc_table_idx(hcp, hp.cea.channels);
	अगर (idx < 0) अणु
		dev_err(dai->dev, "Not able to map channels to speakers (%d)\n",
			idx);
		hcp->chmap_idx = HDMI_CODEC_CHMAP_IDX_UNKNOWN;
		वापस idx;
	पूर्ण
	hp.cea.channel_allocation = hdmi_codec_channel_alloc[idx].ca_id;
	hcp->chmap_idx = hdmi_codec_channel_alloc[idx].ca_id;

	hp.sample_width = params_width(params);
	hp.sample_rate = params_rate(params);
	hp.channels = params_channels(params);

	cf->bit_fmt = params_क्रमmat(params);
	वापस hcp->hcd.ops->hw_params(dai->dev->parent, hcp->hcd.data,
				       cf, &hp);
पूर्ण

अटल पूर्णांक hdmi_codec_i2s_set_fmt(काष्ठा snd_soc_dai *dai,
				  अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा hdmi_codec_daअगरmt *cf = dai->playback_dma_data;

	/* Reset daअगरmt */
	स_रखो(cf, 0, माप(*cf));

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		cf->bit_clk_master = 1;
		cf->frame_clk_master = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		cf->frame_clk_master = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		cf->bit_clk_master = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		cf->frame_clk_inv = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		cf->bit_clk_inv = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		cf->frame_clk_inv = 1;
		cf->bit_clk_inv = 1;
		अवरोध;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		cf->fmt = HDMI_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		cf->fmt = HDMI_DSP_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		cf->fmt = HDMI_DSP_B;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		cf->fmt = HDMI_RIGHT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		cf->fmt = HDMI_LEFT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_AC97:
		cf->fmt = HDMI_AC97;
		अवरोध;
	शेष:
		dev_err(dai->dev, "Invalid DAI interface format\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_codec_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा hdmi_codec_priv *hcp = snd_soc_dai_get_drvdata(dai);

	/*
	 * ignore अगर direction was CAPTURE
	 * and it had .no_capture_mute flag
	 * see
	 *	snd_soc_dai_digital_mute()
	 */
	अगर (hcp->hcd.ops->mute_stream &&
	    (direction == SNDRV_PCM_STREAM_PLAYBACK ||
	     !hcp->hcd.ops->no_capture_mute))
		वापस hcp->hcd.ops->mute_stream(dai->dev->parent,
						 hcp->hcd.data,
						 mute, direction);

	वापस -ENOTSUPP;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops hdmi_codec_i2s_dai_ops = अणु
	.startup	= hdmi_codec_startup,
	.shutकरोwn	= hdmi_codec_shutकरोwn,
	.hw_params	= hdmi_codec_hw_params,
	.set_fmt	= hdmi_codec_i2s_set_fmt,
	.mute_stream	= hdmi_codec_mute,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops hdmi_codec_spdअगर_dai_ops = अणु
	.startup	= hdmi_codec_startup,
	.shutकरोwn	= hdmi_codec_shutकरोwn,
	.hw_params	= hdmi_codec_hw_params,
	.mute_stream	= hdmi_codec_mute,
पूर्ण;

#घोषणा HDMI_RATES	(SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |\
			 SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 |\
			 SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 |\
			 SNDRV_PCM_RATE_192000)

#घोषणा SPDIF_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |\
			 SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S20_3BE |\
			 SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_3BE |\
			 SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_BE)

/*
 * This list is only क्रम क्रमmats allowed on the I2S bus. So there is
 * some क्रमmats listed that are not supported by HDMI पूर्णांकerface. For
 * instance allowing the 32-bit क्रमmats enables 24-precision with CPU
 * DAIs that करो not support 24-bit क्रमmats. If the extra क्रमmats cause
 * problems, we should add the video side driver an option to disable
 * them.
 */
#घोषणा I2S_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |\
			 SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S20_3BE |\
			 SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_3BE |\
			 SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_BE |\
			 SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S32_BE |\
			 SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE)

अटल पूर्णांक hdmi_codec_pcm_new(काष्ठा snd_soc_pcm_runसमय *rtd,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_dai_driver *drv = dai->driver;
	काष्ठा hdmi_codec_priv *hcp = snd_soc_dai_get_drvdata(dai);
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_kcontrol_new hdmi_eld_ctl = अणु
		.access	= SNDRV_CTL_ELEM_ACCESS_READ |
			  SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.अगरace	= SNDRV_CTL_ELEM_IFACE_PCM,
		.name	= "ELD",
		.info	= hdmi_eld_ctl_info,
		.get	= hdmi_eld_ctl_get,
		.device	= rtd->pcm->device,
	पूर्ण;
	पूर्णांक ret;

	ret =  snd_pcm_add_chmap_ctls(rtd->pcm, SNDRV_PCM_STREAM_PLAYBACK,
				      शून्य, drv->playback.channels_max, 0,
				      &hcp->chmap_info);
	अगर (ret < 0)
		वापस ret;

	/* override handlers */
	hcp->chmap_info->निजी_data = hcp;
	hcp->chmap_info->kctl->get = hdmi_codec_chmap_ctl_get;

	/* शेष chmap supported is stereo */
	hcp->chmap_info->chmap = hdmi_codec_stereo_chmaps;
	hcp->chmap_idx = HDMI_CODEC_CHMAP_IDX_UNKNOWN;

	/* add ELD ctl with the device number corresponding to the PCM stream */
	kctl = snd_ctl_new1(&hdmi_eld_ctl, dai->component);
	अगर (!kctl)
		वापस -ENOMEM;

	वापस snd_ctl_add(rtd->card->snd_card, kctl);
पूर्ण

अटल पूर्णांक hdmi_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_dapm_context *dapm;
	काष्ठा hdmi_codec_daअगरmt *daअगरmt;
	काष्ठा snd_soc_dapm_route route[] = अणु
		अणु
			.sink = "TX",
			.source = dai->driver->playback.stream_name,
		पूर्ण,
		अणु
			.sink = dai->driver->capture.stream_name,
			.source = "RX",
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	dapm = snd_soc_component_get_dapm(dai->component);
	ret = snd_soc_dapm_add_routes(dapm, route, 2);
	अगर (ret)
		वापस ret;

	daअगरmt = kzalloc(माप(*daअगरmt), GFP_KERNEL);
	अगर (!daअगरmt)
		वापस -ENOMEM;

	dai->playback_dma_data = daअगरmt;
	वापस 0;
पूर्ण

अटल व्योम hdmi_codec_jack_report(काष्ठा hdmi_codec_priv *hcp,
				   अचिन्हित पूर्णांक jack_status)
अणु
	अगर (hcp->jack && jack_status != hcp->jack_status) अणु
		snd_soc_jack_report(hcp->jack, jack_status, SND_JACK_LINEOUT);
		hcp->jack_status = jack_status;
	पूर्ण
पूर्ण

अटल व्योम plugged_cb(काष्ठा device *dev, bool plugged)
अणु
	काष्ठा hdmi_codec_priv *hcp = dev_get_drvdata(dev);

	अगर (plugged) अणु
		अगर (hcp->hcd.ops->get_eld) अणु
			hcp->hcd.ops->get_eld(dev->parent, hcp->hcd.data,
					    hcp->eld, माप(hcp->eld));
		पूर्ण
		hdmi_codec_jack_report(hcp, SND_JACK_LINEOUT);
	पूर्ण अन्यथा अणु
		hdmi_codec_jack_report(hcp, 0);
		स_रखो(hcp->eld, 0, माप(hcp->eld));
	पूर्ण
पूर्ण

अटल पूर्णांक hdmi_codec_set_jack(काष्ठा snd_soc_component *component,
			       काष्ठा snd_soc_jack *jack,
			       व्योम *data)
अणु
	काष्ठा hdmi_codec_priv *hcp = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = -ENOTSUPP;

	अगर (hcp->hcd.ops->hook_plugged_cb) अणु
		hcp->jack = jack;
		ret = hcp->hcd.ops->hook_plugged_cb(component->dev->parent,
						    hcp->hcd.data,
						    plugged_cb,
						    component->dev);
		अगर (ret)
			hcp->jack = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक hdmi_dai_spdअगर_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdmi_codec_daअगरmt *cf;
	पूर्णांक ret;

	ret = hdmi_dai_probe(dai);
	अगर (ret)
		वापस ret;

	cf = dai->playback_dma_data;
	cf->fmt = HDMI_SPDIF;

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_codec_dai_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	kमुक्त(dai->playback_dma_data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_driver hdmi_i2s_dai = अणु
	.name = "i2s-hifi",
	.id = DAI_ID_I2S,
	.probe = hdmi_dai_probe,
	.हटाओ = hdmi_codec_dai_हटाओ,
	.playback = अणु
		.stream_name = "I2S Playback",
		.channels_min = 2,
		.channels_max = 8,
		.rates = HDMI_RATES,
		.क्रमmats = I2S_FORMATS,
		.sig_bits = 24,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 8,
		.rates = HDMI_RATES,
		.क्रमmats = I2S_FORMATS,
		.sig_bits = 24,
	पूर्ण,
	.ops = &hdmi_codec_i2s_dai_ops,
	.pcm_new = hdmi_codec_pcm_new,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_driver hdmi_spdअगर_dai = अणु
	.name = "spdif-hifi",
	.id = DAI_ID_SPDIF,
	.probe = hdmi_dai_spdअगर_probe,
	.हटाओ = hdmi_codec_dai_हटाओ,
	.playback = अणु
		.stream_name = "SPDIF Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = HDMI_RATES,
		.क्रमmats = SPDIF_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = HDMI_RATES,
		.क्रमmats = SPDIF_FORMATS,
	पूर्ण,
	.ops = &hdmi_codec_spdअगर_dai_ops,
	.pcm_new = hdmi_codec_pcm_new,
पूर्ण;

अटल पूर्णांक hdmi_of_xlate_dai_id(काष्ठा snd_soc_component *component,
				 काष्ठा device_node *endpoपूर्णांक)
अणु
	काष्ठा hdmi_codec_priv *hcp = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = -ENOTSUPP; /* see snd_soc_get_dai_id() */

	अगर (hcp->hcd.ops->get_dai_id)
		ret = hcp->hcd.ops->get_dai_id(component, endpoपूर्णांक);

	वापस ret;
पूर्ण

अटल व्योम hdmi_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा hdmi_codec_priv *hcp = snd_soc_component_get_drvdata(component);

	अगर (hcp->hcd.ops->hook_plugged_cb)
		hcp->hcd.ops->hook_plugged_cb(component->dev->parent,
					      hcp->hcd.data, शून्य, शून्य);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver hdmi_driver = अणु
	.हटाओ			= hdmi_हटाओ,
	.dapm_widमाला_लो		= hdmi_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(hdmi_widमाला_लो),
	.of_xlate_dai_id	= hdmi_of_xlate_dai_id,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
	.set_jack		= hdmi_codec_set_jack,
पूर्ण;

अटल पूर्णांक hdmi_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hdmi_codec_pdata *hcd = pdev->dev.platक्रमm_data;
	काष्ठा snd_soc_dai_driver *daidrv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hdmi_codec_priv *hcp;
	पूर्णांक dai_count, i = 0;
	पूर्णांक ret;

	अगर (!hcd) अणु
		dev_err(dev, "%s: No platform data\n", __func__);
		वापस -EINVAL;
	पूर्ण

	dai_count = hcd->i2s + hcd->spdअगर;
	अगर (dai_count < 1 || !hcd->ops || !hcd->ops->hw_params ||
	    !hcd->ops->audio_shutकरोwn) अणु
		dev_err(dev, "%s: Invalid parameters\n", __func__);
		वापस -EINVAL;
	पूर्ण

	hcp = devm_kzalloc(dev, माप(*hcp), GFP_KERNEL);
	अगर (!hcp)
		वापस -ENOMEM;

	hcp->hcd = *hcd;
	mutex_init(&hcp->lock);

	daidrv = devm_kसुस्मृति(dev, dai_count, माप(*daidrv), GFP_KERNEL);
	अगर (!daidrv)
		वापस -ENOMEM;

	अगर (hcd->i2s) अणु
		daidrv[i] = hdmi_i2s_dai;
		daidrv[i].playback.channels_max = hcd->max_i2s_channels;
		i++;
	पूर्ण

	अगर (hcd->spdअगर)
		daidrv[i] = hdmi_spdअगर_dai;

	dev_set_drvdata(dev, hcp);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &hdmi_driver, daidrv,
					      dai_count);
	अगर (ret) अणु
		dev_err(dev, "%s: snd_soc_register_component() failed (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hdmi_codec_driver = अणु
	.driver = अणु
		.name = HDMI_CODEC_DRV_NAME,
	पूर्ण,
	.probe = hdmi_codec_probe,
पूर्ण;

module_platक्रमm_driver(hdmi_codec_driver);

MODULE_AUTHOR("Jyri Sarha <jsarha@ti.com>");
MODULE_DESCRIPTION("HDMI Audio Codec Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" HDMI_CODEC_DRV_NAME);
