<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram miXart soundcards
 *
 * mixer callbacks
 *
 * Copyright (c) 2003 by Digigram <alsa@digigram.com>
 */

#समावेश <linux/समय.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>

#समावेश <sound/core.h>
#समावेश "mixart.h"
#समावेश "mixart_core.h"
#समावेश "mixart_hwdep.h"
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश "mixart_mixer.h"

अटल स्थिर u32 mixart_analog_level[256] = अणु
	0xc2c00000,		/* [000] -96.0 dB */
	0xc2bf0000,		/* [001] -95.5 dB */
	0xc2be0000,		/* [002] -95.0 dB */
	0xc2bd0000,		/* [003] -94.5 dB */
	0xc2bc0000,		/* [004] -94.0 dB */
	0xc2bb0000,		/* [005] -93.5 dB */
	0xc2ba0000,		/* [006] -93.0 dB */
	0xc2b90000,		/* [007] -92.5 dB */
	0xc2b80000,		/* [008] -92.0 dB */
	0xc2b70000,		/* [009] -91.5 dB */
	0xc2b60000,		/* [010] -91.0 dB */
	0xc2b50000,		/* [011] -90.5 dB */
	0xc2b40000,		/* [012] -90.0 dB */
	0xc2b30000,		/* [013] -89.5 dB */
	0xc2b20000,		/* [014] -89.0 dB */
	0xc2b10000,		/* [015] -88.5 dB */
	0xc2b00000,		/* [016] -88.0 dB */
	0xc2af0000,		/* [017] -87.5 dB */
	0xc2ae0000,		/* [018] -87.0 dB */
	0xc2ad0000,		/* [019] -86.5 dB */
	0xc2ac0000,		/* [020] -86.0 dB */
	0xc2ab0000,		/* [021] -85.5 dB */
	0xc2aa0000,		/* [022] -85.0 dB */
	0xc2a90000,		/* [023] -84.5 dB */
	0xc2a80000,		/* [024] -84.0 dB */
	0xc2a70000,		/* [025] -83.5 dB */
	0xc2a60000,		/* [026] -83.0 dB */
	0xc2a50000,		/* [027] -82.5 dB */
	0xc2a40000,		/* [028] -82.0 dB */
	0xc2a30000,		/* [029] -81.5 dB */
	0xc2a20000,		/* [030] -81.0 dB */
	0xc2a10000,		/* [031] -80.5 dB */
	0xc2a00000,		/* [032] -80.0 dB */
	0xc29f0000,		/* [033] -79.5 dB */
	0xc29e0000,		/* [034] -79.0 dB */
	0xc29d0000,		/* [035] -78.5 dB */
	0xc29c0000,		/* [036] -78.0 dB */
	0xc29b0000,		/* [037] -77.5 dB */
	0xc29a0000,		/* [038] -77.0 dB */
	0xc2990000,		/* [039] -76.5 dB */
	0xc2980000,		/* [040] -76.0 dB */
	0xc2970000,		/* [041] -75.5 dB */
	0xc2960000,		/* [042] -75.0 dB */
	0xc2950000,		/* [043] -74.5 dB */
	0xc2940000,		/* [044] -74.0 dB */
	0xc2930000,		/* [045] -73.5 dB */
	0xc2920000,		/* [046] -73.0 dB */
	0xc2910000,		/* [047] -72.5 dB */
	0xc2900000,		/* [048] -72.0 dB */
	0xc28f0000,		/* [049] -71.5 dB */
	0xc28e0000,		/* [050] -71.0 dB */
	0xc28d0000,		/* [051] -70.5 dB */
	0xc28c0000,		/* [052] -70.0 dB */
	0xc28b0000,		/* [053] -69.5 dB */
	0xc28a0000,		/* [054] -69.0 dB */
	0xc2890000,		/* [055] -68.5 dB */
	0xc2880000,		/* [056] -68.0 dB */
	0xc2870000,		/* [057] -67.5 dB */
	0xc2860000,		/* [058] -67.0 dB */
	0xc2850000,		/* [059] -66.5 dB */
	0xc2840000,		/* [060] -66.0 dB */
	0xc2830000,		/* [061] -65.5 dB */
	0xc2820000,		/* [062] -65.0 dB */
	0xc2810000,		/* [063] -64.5 dB */
	0xc2800000,		/* [064] -64.0 dB */
	0xc27e0000,		/* [065] -63.5 dB */
	0xc27c0000,		/* [066] -63.0 dB */
	0xc27a0000,		/* [067] -62.5 dB */
	0xc2780000,		/* [068] -62.0 dB */
	0xc2760000,		/* [069] -61.5 dB */
	0xc2740000,		/* [070] -61.0 dB */
	0xc2720000,		/* [071] -60.5 dB */
	0xc2700000,		/* [072] -60.0 dB */
	0xc26e0000,		/* [073] -59.5 dB */
	0xc26c0000,		/* [074] -59.0 dB */
	0xc26a0000,		/* [075] -58.5 dB */
	0xc2680000,		/* [076] -58.0 dB */
	0xc2660000,		/* [077] -57.5 dB */
	0xc2640000,		/* [078] -57.0 dB */
	0xc2620000,		/* [079] -56.5 dB */
	0xc2600000,		/* [080] -56.0 dB */
	0xc25e0000,		/* [081] -55.5 dB */
	0xc25c0000,		/* [082] -55.0 dB */
	0xc25a0000,		/* [083] -54.5 dB */
	0xc2580000,		/* [084] -54.0 dB */
	0xc2560000,		/* [085] -53.5 dB */
	0xc2540000,		/* [086] -53.0 dB */
	0xc2520000,		/* [087] -52.5 dB */
	0xc2500000,		/* [088] -52.0 dB */
	0xc24e0000,		/* [089] -51.5 dB */
	0xc24c0000,		/* [090] -51.0 dB */
	0xc24a0000,		/* [091] -50.5 dB */
	0xc2480000,		/* [092] -50.0 dB */
	0xc2460000,		/* [093] -49.5 dB */
	0xc2440000,		/* [094] -49.0 dB */
	0xc2420000,		/* [095] -48.5 dB */
	0xc2400000,		/* [096] -48.0 dB */
	0xc23e0000,		/* [097] -47.5 dB */
	0xc23c0000,		/* [098] -47.0 dB */
	0xc23a0000,		/* [099] -46.5 dB */
	0xc2380000,		/* [100] -46.0 dB */
	0xc2360000,		/* [101] -45.5 dB */
	0xc2340000,		/* [102] -45.0 dB */
	0xc2320000,		/* [103] -44.5 dB */
	0xc2300000,		/* [104] -44.0 dB */
	0xc22e0000,		/* [105] -43.5 dB */
	0xc22c0000,		/* [106] -43.0 dB */
	0xc22a0000,		/* [107] -42.5 dB */
	0xc2280000,		/* [108] -42.0 dB */
	0xc2260000,		/* [109] -41.5 dB */
	0xc2240000,		/* [110] -41.0 dB */
	0xc2220000,		/* [111] -40.5 dB */
	0xc2200000,		/* [112] -40.0 dB */
	0xc21e0000,		/* [113] -39.5 dB */
	0xc21c0000,		/* [114] -39.0 dB */
	0xc21a0000,		/* [115] -38.5 dB */
	0xc2180000,		/* [116] -38.0 dB */
	0xc2160000,		/* [117] -37.5 dB */
	0xc2140000,		/* [118] -37.0 dB */
	0xc2120000,		/* [119] -36.5 dB */
	0xc2100000,		/* [120] -36.0 dB */
	0xc20e0000,		/* [121] -35.5 dB */
	0xc20c0000,		/* [122] -35.0 dB */
	0xc20a0000,		/* [123] -34.5 dB */
	0xc2080000,		/* [124] -34.0 dB */
	0xc2060000,		/* [125] -33.5 dB */
	0xc2040000,		/* [126] -33.0 dB */
	0xc2020000,		/* [127] -32.5 dB */
	0xc2000000,		/* [128] -32.0 dB */
	0xc1fc0000,		/* [129] -31.5 dB */
	0xc1f80000,		/* [130] -31.0 dB */
	0xc1f40000,		/* [131] -30.5 dB */
	0xc1f00000,		/* [132] -30.0 dB */
	0xc1ec0000,		/* [133] -29.5 dB */
	0xc1e80000,		/* [134] -29.0 dB */
	0xc1e40000,		/* [135] -28.5 dB */
	0xc1e00000,		/* [136] -28.0 dB */
	0xc1dc0000,		/* [137] -27.5 dB */
	0xc1d80000,		/* [138] -27.0 dB */
	0xc1d40000,		/* [139] -26.5 dB */
	0xc1d00000,		/* [140] -26.0 dB */
	0xc1cc0000,		/* [141] -25.5 dB */
	0xc1c80000,		/* [142] -25.0 dB */
	0xc1c40000,		/* [143] -24.5 dB */
	0xc1c00000,		/* [144] -24.0 dB */
	0xc1bc0000,		/* [145] -23.5 dB */
	0xc1b80000,		/* [146] -23.0 dB */
	0xc1b40000,		/* [147] -22.5 dB */
	0xc1b00000,		/* [148] -22.0 dB */
	0xc1ac0000,		/* [149] -21.5 dB */
	0xc1a80000,		/* [150] -21.0 dB */
	0xc1a40000,		/* [151] -20.5 dB */
	0xc1a00000,		/* [152] -20.0 dB */
	0xc19c0000,		/* [153] -19.5 dB */
	0xc1980000,		/* [154] -19.0 dB */
	0xc1940000,		/* [155] -18.5 dB */
	0xc1900000,		/* [156] -18.0 dB */
	0xc18c0000,		/* [157] -17.5 dB */
	0xc1880000,		/* [158] -17.0 dB */
	0xc1840000,		/* [159] -16.5 dB */
	0xc1800000,		/* [160] -16.0 dB */
	0xc1780000,		/* [161] -15.5 dB */
	0xc1700000,		/* [162] -15.0 dB */
	0xc1680000,		/* [163] -14.5 dB */
	0xc1600000,		/* [164] -14.0 dB */
	0xc1580000,		/* [165] -13.5 dB */
	0xc1500000,		/* [166] -13.0 dB */
	0xc1480000,		/* [167] -12.5 dB */
	0xc1400000,		/* [168] -12.0 dB */
	0xc1380000,		/* [169] -11.5 dB */
	0xc1300000,		/* [170] -11.0 dB */
	0xc1280000,		/* [171] -10.5 dB */
	0xc1200000,		/* [172] -10.0 dB */
	0xc1180000,		/* [173] -9.5 dB */
	0xc1100000,		/* [174] -9.0 dB */
	0xc1080000,		/* [175] -8.5 dB */
	0xc1000000,		/* [176] -8.0 dB */
	0xc0f00000,		/* [177] -7.5 dB */
	0xc0e00000,		/* [178] -7.0 dB */
	0xc0d00000,		/* [179] -6.5 dB */
	0xc0c00000,		/* [180] -6.0 dB */
	0xc0b00000,		/* [181] -5.5 dB */
	0xc0a00000,		/* [182] -5.0 dB */
	0xc0900000,		/* [183] -4.5 dB */
	0xc0800000,		/* [184] -4.0 dB */
	0xc0600000,		/* [185] -3.5 dB */
	0xc0400000,		/* [186] -3.0 dB */
	0xc0200000,		/* [187] -2.5 dB */
	0xc0000000,		/* [188] -2.0 dB */
	0xbfc00000,		/* [189] -1.5 dB */
	0xbf800000,		/* [190] -1.0 dB */
	0xbf000000,		/* [191] -0.5 dB */
	0x00000000,		/* [192] 0.0 dB */
	0x3f000000,		/* [193] 0.5 dB */
	0x3f800000,		/* [194] 1.0 dB */
	0x3fc00000,		/* [195] 1.5 dB */
	0x40000000,		/* [196] 2.0 dB */
	0x40200000,		/* [197] 2.5 dB */
	0x40400000,		/* [198] 3.0 dB */
	0x40600000,		/* [199] 3.5 dB */
	0x40800000,		/* [200] 4.0 dB */
	0x40900000,		/* [201] 4.5 dB */
	0x40a00000,		/* [202] 5.0 dB */
	0x40b00000,		/* [203] 5.5 dB */
	0x40c00000,		/* [204] 6.0 dB */
	0x40d00000,		/* [205] 6.5 dB */
	0x40e00000,		/* [206] 7.0 dB */
	0x40f00000,		/* [207] 7.5 dB */
	0x41000000,		/* [208] 8.0 dB */
	0x41080000,		/* [209] 8.5 dB */
	0x41100000,		/* [210] 9.0 dB */
	0x41180000,		/* [211] 9.5 dB */
	0x41200000,		/* [212] 10.0 dB */
	0x41280000,		/* [213] 10.5 dB */
	0x41300000,		/* [214] 11.0 dB */
	0x41380000,		/* [215] 11.5 dB */
	0x41400000,		/* [216] 12.0 dB */
	0x41480000,		/* [217] 12.5 dB */
	0x41500000,		/* [218] 13.0 dB */
	0x41580000,		/* [219] 13.5 dB */
	0x41600000,		/* [220] 14.0 dB */
	0x41680000,		/* [221] 14.5 dB */
	0x41700000,		/* [222] 15.0 dB */
	0x41780000,		/* [223] 15.5 dB */
	0x41800000,		/* [224] 16.0 dB */
	0x41840000,		/* [225] 16.5 dB */
	0x41880000,		/* [226] 17.0 dB */
	0x418c0000,		/* [227] 17.5 dB */
	0x41900000,		/* [228] 18.0 dB */
	0x41940000,		/* [229] 18.5 dB */
	0x41980000,		/* [230] 19.0 dB */
	0x419c0000,		/* [231] 19.5 dB */
	0x41a00000,		/* [232] 20.0 dB */
	0x41a40000,		/* [233] 20.5 dB */
	0x41a80000,		/* [234] 21.0 dB */
	0x41ac0000,		/* [235] 21.5 dB */
	0x41b00000,		/* [236] 22.0 dB */
	0x41b40000,		/* [237] 22.5 dB */
	0x41b80000,		/* [238] 23.0 dB */
	0x41bc0000,		/* [239] 23.5 dB */
	0x41c00000,		/* [240] 24.0 dB */
	0x41c40000,		/* [241] 24.5 dB */
	0x41c80000,		/* [242] 25.0 dB */
	0x41cc0000,		/* [243] 25.5 dB */
	0x41d00000,		/* [244] 26.0 dB */
	0x41d40000,		/* [245] 26.5 dB */
	0x41d80000,		/* [246] 27.0 dB */
	0x41dc0000,		/* [247] 27.5 dB */
	0x41e00000,		/* [248] 28.0 dB */
	0x41e40000,		/* [249] 28.5 dB */
	0x41e80000,		/* [250] 29.0 dB */
	0x41ec0000,		/* [251] 29.5 dB */
	0x41f00000,		/* [252] 30.0 dB */
	0x41f40000,		/* [253] 30.5 dB */
	0x41f80000,		/* [254] 31.0 dB */
	0x41fc0000,		/* [255] 31.5 dB */
पूर्ण;

#घोषणा MIXART_ANALOG_CAPTURE_LEVEL_MIN   0      /* -96.0 dB + 8.0 dB = -88.0 dB */
#घोषणा MIXART_ANALOG_CAPTURE_LEVEL_MAX   255    /*  31.5 dB + 8.0 dB =  39.5 dB */
#घोषणा MIXART_ANALOG_CAPTURE_ZERO_LEVEL  176    /*  -8.0 dB + 8.0 dB =  0.0 dB */

#घोषणा MIXART_ANALOG_PLAYBACK_LEVEL_MIN  0      /* -96.0 dB + 1.5 dB = -94.5 dB (possible is करोwn to (-114.0+1.5)dB) */
#घोषणा MIXART_ANALOG_PLAYBACK_LEVEL_MAX  192    /*   0.0 dB + 1.5 dB =  1.5 dB */
#घोषणा MIXART_ANALOG_PLAYBACK_ZERO_LEVEL 189    /*  -1.5 dB + 1.5 dB =  0.0 dB */

अटल पूर्णांक mixart_update_analog_audio_level(काष्ठा snd_mixart* chip, पूर्णांक is_capture)
अणु
	पूर्णांक i, err;
	काष्ठा mixart_msg request;
	काष्ठा mixart_io_level io_level;
	काष्ठा mixart_वापस_uid resp;

	स_रखो(&io_level, 0, माप(io_level));
	io_level.channel = -1; /* left and right */

	क्रम(i=0; i<2; i++) अणु
		अगर(is_capture) अणु
			io_level.level[i].analog_level = mixart_analog_level[chip->analog_capture_volume[i]];
		पूर्ण अन्यथा अणु
			अगर(chip->analog_playback_active[i])
				io_level.level[i].analog_level = mixart_analog_level[chip->analog_playback_volume[i]];
			अन्यथा
				io_level.level[i].analog_level = mixart_analog_level[MIXART_ANALOG_PLAYBACK_LEVEL_MIN];
		पूर्ण
	पूर्ण

	अगर(is_capture)	request.uid = chip->uid_in_analog_physio;
	अन्यथा		request.uid = chip->uid_out_analog_physio;
	request.message_id = MSG_PHYSICALIO_SET_LEVEL;
	request.data = &io_level;
	request.size = माप(io_level);

	err = snd_mixart_send_msg(chip->mgr, &request, माप(resp), &resp);
	अगर((err<0) || (resp.error_code)) अणु
		dev_dbg(chip->card->dev,
			"error MSG_PHYSICALIO_SET_LEVEL card(%d) is_capture(%d) error_code(%x)\n",
			chip->chip_idx, is_capture, resp.error_code);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * analog level control
 */
अटल पूर्णांक mixart_analog_vol_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	अगर(kcontrol->निजी_value == 0) अणु	/* playback */
		uinfo->value.पूर्णांकeger.min = MIXART_ANALOG_PLAYBACK_LEVEL_MIN;  /* -96 dB */
		uinfo->value.पूर्णांकeger.max = MIXART_ANALOG_PLAYBACK_LEVEL_MAX;  /* 0 dB */
	पूर्ण अन्यथा अणु				/* capture */
		uinfo->value.पूर्णांकeger.min = MIXART_ANALOG_CAPTURE_LEVEL_MIN;   /* -96 dB */
		uinfo->value.पूर्णांकeger.max = MIXART_ANALOG_CAPTURE_LEVEL_MAX;   /* 31.5 dB */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mixart_analog_vol_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_mixart *chip = snd_kcontrol_chip(kcontrol);
	mutex_lock(&chip->mgr->mixer_mutex);
	अगर(kcontrol->निजी_value == 0) अणु	/* playback */
		ucontrol->value.पूर्णांकeger.value[0] = chip->analog_playback_volume[0];
		ucontrol->value.पूर्णांकeger.value[1] = chip->analog_playback_volume[1];
	पूर्ण अन्यथा अणु				/* capture */
		ucontrol->value.पूर्णांकeger.value[0] = chip->analog_capture_volume[0];
		ucontrol->value.पूर्णांकeger.value[1] = chip->analog_capture_volume[1];
	पूर्ण
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक mixart_analog_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_mixart *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	पूर्णांक is_capture, i;

	mutex_lock(&chip->mgr->mixer_mutex);
	is_capture = (kcontrol->निजी_value != 0);
	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांक new_volume = ucontrol->value.पूर्णांकeger.value[i];
		पूर्णांक *stored_volume = is_capture ?
			&chip->analog_capture_volume[i] :
			&chip->analog_playback_volume[i];
		अगर (is_capture) अणु
			अगर (new_volume < MIXART_ANALOG_CAPTURE_LEVEL_MIN ||
			    new_volume > MIXART_ANALOG_CAPTURE_LEVEL_MAX)
				जारी;
		पूर्ण अन्यथा अणु
			अगर (new_volume < MIXART_ANALOG_PLAYBACK_LEVEL_MIN ||
			    new_volume > MIXART_ANALOG_PLAYBACK_LEVEL_MAX)
				जारी;
		पूर्ण
		अगर (*stored_volume != new_volume) अणु
			*stored_volume = new_volume;
			changed = 1;
		पूर्ण
	पूर्ण
	अगर (changed)
		mixart_update_analog_audio_level(chip, is_capture);
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस changed;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_analog, -9600, 50, 0);

अटल स्थिर काष्ठा snd_kcontrol_new mixart_control_analog_level = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
		   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	/* name will be filled later */
	.info =		mixart_analog_vol_info,
	.get =		mixart_analog_vol_get,
	.put =		mixart_analog_vol_put,
	.tlv = अणु .p = db_scale_analog पूर्ण,
पूर्ण;

/* shared */
#घोषणा mixart_sw_info		snd_ctl_boolean_stereo_info

अटल पूर्णांक mixart_audio_sw_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_mixart *chip = snd_kcontrol_chip(kcontrol);

	mutex_lock(&chip->mgr->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->analog_playback_active[0];
	ucontrol->value.पूर्णांकeger.value[1] = chip->analog_playback_active[1];
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक mixart_audio_sw_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_mixart *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक i, changed = 0;
	mutex_lock(&chip->mgr->mixer_mutex);
	क्रम (i = 0; i < 2; i++) अणु
		अगर (chip->analog_playback_active[i] !=
		    ucontrol->value.पूर्णांकeger.value[i]) अणु
			chip->analog_playback_active[i] =
				!!ucontrol->value.पूर्णांकeger.value[i];
			changed = 1;
		पूर्ण
	पूर्ण
	अगर (changed) /* update playback levels */
		mixart_update_analog_audio_level(chip, 0);
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mixart_control_output_चयन = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Master Playback Switch",
	.info =         mixart_sw_info,		/* shared */
	.get =          mixart_audio_sw_get,
	.put =          mixart_audio_sw_put
पूर्ण;

अटल स्थिर u32 mixart_digital_level[256] = अणु
	0x00000000,		/* [000] = 0.00e+000 = mute अगर <= -109.5dB */
	0x366e1c7a,		/* [001] = 3.55e-006 = घात(10.0, 0.05 * -109.0dB) */
	0x367c3860,		/* [002] = 3.76e-006 = घात(10.0, 0.05 * -108.5dB) */
	0x36859525,		/* [003] = 3.98e-006 = घात(10.0, 0.05 * -108.0dB) */
	0x368d7f74,		/* [004] = 4.22e-006 = घात(10.0, 0.05 * -107.5dB) */
	0x3695e1d4,		/* [005] = 4.47e-006 = घात(10.0, 0.05 * -107.0dB) */
	0x369ec362,		/* [006] = 4.73e-006 = घात(10.0, 0.05 * -106.5dB) */
	0x36a82ba8,		/* [007] = 5.01e-006 = घात(10.0, 0.05 * -106.0dB) */
	0x36b222a0,		/* [008] = 5.31e-006 = घात(10.0, 0.05 * -105.5dB) */
	0x36bcb0c1,		/* [009] = 5.62e-006 = घात(10.0, 0.05 * -105.0dB) */
	0x36c7defd,		/* [010] = 5.96e-006 = घात(10.0, 0.05 * -104.5dB) */
	0x36d3b6d3,		/* [011] = 6.31e-006 = घात(10.0, 0.05 * -104.0dB) */
	0x36e0424e,		/* [012] = 6.68e-006 = घात(10.0, 0.05 * -103.5dB) */
	0x36ed8c14,		/* [013] = 7.08e-006 = घात(10.0, 0.05 * -103.0dB) */
	0x36fb9f6c,		/* [014] = 7.50e-006 = घात(10.0, 0.05 * -102.5dB) */
	0x37054423,		/* [015] = 7.94e-006 = घात(10.0, 0.05 * -102.0dB) */
	0x370d29a5,		/* [016] = 8.41e-006 = घात(10.0, 0.05 * -101.5dB) */
	0x371586f0,		/* [017] = 8.91e-006 = घात(10.0, 0.05 * -101.0dB) */
	0x371e631b,		/* [018] = 9.44e-006 = घात(10.0, 0.05 * -100.5dB) */
	0x3727c5ac,		/* [019] = 1.00e-005 = घात(10.0, 0.05 * -100.0dB) */
	0x3731b69a,		/* [020] = 1.06e-005 = घात(10.0, 0.05 * -99.5dB) */
	0x373c3e53,		/* [021] = 1.12e-005 = घात(10.0, 0.05 * -99.0dB) */
	0x374765c8,		/* [022] = 1.19e-005 = घात(10.0, 0.05 * -98.5dB) */
	0x3753366f,		/* [023] = 1.26e-005 = घात(10.0, 0.05 * -98.0dB) */
	0x375fba4f,		/* [024] = 1.33e-005 = घात(10.0, 0.05 * -97.5dB) */
	0x376cfc07,		/* [025] = 1.41e-005 = घात(10.0, 0.05 * -97.0dB) */
	0x377b06d5,		/* [026] = 1.50e-005 = घात(10.0, 0.05 * -96.5dB) */
	0x3784f352,		/* [027] = 1.58e-005 = घात(10.0, 0.05 * -96.0dB) */
	0x378cd40b,		/* [028] = 1.68e-005 = घात(10.0, 0.05 * -95.5dB) */
	0x37952c42,		/* [029] = 1.78e-005 = घात(10.0, 0.05 * -95.0dB) */
	0x379e030e,		/* [030] = 1.88e-005 = घात(10.0, 0.05 * -94.5dB) */
	0x37a75fef,		/* [031] = 2.00e-005 = घात(10.0, 0.05 * -94.0dB) */
	0x37b14ad5,		/* [032] = 2.11e-005 = घात(10.0, 0.05 * -93.5dB) */
	0x37bbcc2c,		/* [033] = 2.24e-005 = घात(10.0, 0.05 * -93.0dB) */
	0x37c6ecdd,		/* [034] = 2.37e-005 = घात(10.0, 0.05 * -92.5dB) */
	0x37d2b65a,		/* [035] = 2.51e-005 = घात(10.0, 0.05 * -92.0dB) */
	0x37df32a3,		/* [036] = 2.66e-005 = घात(10.0, 0.05 * -91.5dB) */
	0x37ec6c50,		/* [037] = 2.82e-005 = घात(10.0, 0.05 * -91.0dB) */
	0x37fa6e9b,		/* [038] = 2.99e-005 = घात(10.0, 0.05 * -90.5dB) */
	0x3804a2b3,		/* [039] = 3.16e-005 = घात(10.0, 0.05 * -90.0dB) */
	0x380c7ea4,		/* [040] = 3.35e-005 = घात(10.0, 0.05 * -89.5dB) */
	0x3814d1cc,		/* [041] = 3.55e-005 = घात(10.0, 0.05 * -89.0dB) */
	0x381da33c,		/* [042] = 3.76e-005 = घात(10.0, 0.05 * -88.5dB) */
	0x3826fa6f,		/* [043] = 3.98e-005 = घात(10.0, 0.05 * -88.0dB) */
	0x3830df51,		/* [044] = 4.22e-005 = घात(10.0, 0.05 * -87.5dB) */
	0x383b5a49,		/* [045] = 4.47e-005 = घात(10.0, 0.05 * -87.0dB) */
	0x3846743b,		/* [046] = 4.73e-005 = घात(10.0, 0.05 * -86.5dB) */
	0x38523692,		/* [047] = 5.01e-005 = घात(10.0, 0.05 * -86.0dB) */
	0x385eab48,		/* [048] = 5.31e-005 = घात(10.0, 0.05 * -85.5dB) */
	0x386bdcf1,		/* [049] = 5.62e-005 = घात(10.0, 0.05 * -85.0dB) */
	0x3879d6bc,		/* [050] = 5.96e-005 = घात(10.0, 0.05 * -84.5dB) */
	0x38845244,		/* [051] = 6.31e-005 = घात(10.0, 0.05 * -84.0dB) */
	0x388c2971,		/* [052] = 6.68e-005 = घात(10.0, 0.05 * -83.5dB) */
	0x3894778d,		/* [053] = 7.08e-005 = घात(10.0, 0.05 * -83.0dB) */
	0x389d43a4,		/* [054] = 7.50e-005 = घात(10.0, 0.05 * -82.5dB) */
	0x38a6952c,		/* [055] = 7.94e-005 = घात(10.0, 0.05 * -82.0dB) */
	0x38b0740f,		/* [056] = 8.41e-005 = घात(10.0, 0.05 * -81.5dB) */
	0x38bae8ac,		/* [057] = 8.91e-005 = घात(10.0, 0.05 * -81.0dB) */
	0x38c5fbe2,		/* [058] = 9.44e-005 = घात(10.0, 0.05 * -80.5dB) */
	0x38d1b717,		/* [059] = 1.00e-004 = घात(10.0, 0.05 * -80.0dB) */
	0x38de2440,		/* [060] = 1.06e-004 = घात(10.0, 0.05 * -79.5dB) */
	0x38eb4de8,		/* [061] = 1.12e-004 = घात(10.0, 0.05 * -79.0dB) */
	0x38f93f3a,		/* [062] = 1.19e-004 = घात(10.0, 0.05 * -78.5dB) */
	0x39040206,		/* [063] = 1.26e-004 = घात(10.0, 0.05 * -78.0dB) */
	0x390bd472,		/* [064] = 1.33e-004 = घात(10.0, 0.05 * -77.5dB) */
	0x39141d84,		/* [065] = 1.41e-004 = घात(10.0, 0.05 * -77.0dB) */
	0x391ce445,		/* [066] = 1.50e-004 = घात(10.0, 0.05 * -76.5dB) */
	0x39263027,		/* [067] = 1.58e-004 = घात(10.0, 0.05 * -76.0dB) */
	0x3930090d,		/* [068] = 1.68e-004 = घात(10.0, 0.05 * -75.5dB) */
	0x393a7753,		/* [069] = 1.78e-004 = घात(10.0, 0.05 * -75.0dB) */
	0x394583d2,		/* [070] = 1.88e-004 = घात(10.0, 0.05 * -74.5dB) */
	0x395137ea,		/* [071] = 2.00e-004 = घात(10.0, 0.05 * -74.0dB) */
	0x395d9d8a,		/* [072] = 2.11e-004 = घात(10.0, 0.05 * -73.5dB) */
	0x396abf37,		/* [073] = 2.24e-004 = घात(10.0, 0.05 * -73.0dB) */
	0x3978a814,		/* [074] = 2.37e-004 = घात(10.0, 0.05 * -72.5dB) */
	0x3983b1f8,		/* [075] = 2.51e-004 = घात(10.0, 0.05 * -72.0dB) */
	0x398b7fa6,		/* [076] = 2.66e-004 = घात(10.0, 0.05 * -71.5dB) */
	0x3993c3b2,		/* [077] = 2.82e-004 = घात(10.0, 0.05 * -71.0dB) */
	0x399c8521,		/* [078] = 2.99e-004 = घात(10.0, 0.05 * -70.5dB) */
	0x39a5cb5f,		/* [079] = 3.16e-004 = घात(10.0, 0.05 * -70.0dB) */
	0x39af9e4d,		/* [080] = 3.35e-004 = घात(10.0, 0.05 * -69.5dB) */
	0x39ba063f,		/* [081] = 3.55e-004 = घात(10.0, 0.05 * -69.0dB) */
	0x39c50c0b,		/* [082] = 3.76e-004 = घात(10.0, 0.05 * -68.5dB) */
	0x39d0b90a,		/* [083] = 3.98e-004 = घात(10.0, 0.05 * -68.0dB) */
	0x39dd1726,		/* [084] = 4.22e-004 = घात(10.0, 0.05 * -67.5dB) */
	0x39ea30db,		/* [085] = 4.47e-004 = घात(10.0, 0.05 * -67.0dB) */
	0x39f81149,		/* [086] = 4.73e-004 = घात(10.0, 0.05 * -66.5dB) */
	0x3a03621b,		/* [087] = 5.01e-004 = घात(10.0, 0.05 * -66.0dB) */
	0x3a0b2b0d,		/* [088] = 5.31e-004 = घात(10.0, 0.05 * -65.5dB) */
	0x3a136a16,		/* [089] = 5.62e-004 = घात(10.0, 0.05 * -65.0dB) */
	0x3a1c2636,		/* [090] = 5.96e-004 = घात(10.0, 0.05 * -64.5dB) */
	0x3a2566d5,		/* [091] = 6.31e-004 = घात(10.0, 0.05 * -64.0dB) */
	0x3a2f33cd,		/* [092] = 6.68e-004 = घात(10.0, 0.05 * -63.5dB) */
	0x3a399570,		/* [093] = 7.08e-004 = घात(10.0, 0.05 * -63.0dB) */
	0x3a44948c,		/* [094] = 7.50e-004 = घात(10.0, 0.05 * -62.5dB) */
	0x3a503a77,		/* [095] = 7.94e-004 = घात(10.0, 0.05 * -62.0dB) */
	0x3a5c9112,		/* [096] = 8.41e-004 = घात(10.0, 0.05 * -61.5dB) */
	0x3a69a2d7,		/* [097] = 8.91e-004 = घात(10.0, 0.05 * -61.0dB) */
	0x3a777ada,		/* [098] = 9.44e-004 = घात(10.0, 0.05 * -60.5dB) */
	0x3a83126f,		/* [099] = 1.00e-003 = घात(10.0, 0.05 * -60.0dB) */
	0x3a8ad6a8,		/* [100] = 1.06e-003 = घात(10.0, 0.05 * -59.5dB) */
	0x3a9310b1,		/* [101] = 1.12e-003 = घात(10.0, 0.05 * -59.0dB) */
	0x3a9bc784,		/* [102] = 1.19e-003 = घात(10.0, 0.05 * -58.5dB) */
	0x3aa50287,		/* [103] = 1.26e-003 = घात(10.0, 0.05 * -58.0dB) */
	0x3aaec98e,		/* [104] = 1.33e-003 = घात(10.0, 0.05 * -57.5dB) */
	0x3ab924e5,		/* [105] = 1.41e-003 = घात(10.0, 0.05 * -57.0dB) */
	0x3ac41d56,		/* [106] = 1.50e-003 = घात(10.0, 0.05 * -56.5dB) */
	0x3acfbc31,		/* [107] = 1.58e-003 = घात(10.0, 0.05 * -56.0dB) */
	0x3adc0b51,		/* [108] = 1.68e-003 = घात(10.0, 0.05 * -55.5dB) */
	0x3ae91528,		/* [109] = 1.78e-003 = घात(10.0, 0.05 * -55.0dB) */
	0x3af6e4c6,		/* [110] = 1.88e-003 = घात(10.0, 0.05 * -54.5dB) */
	0x3b02c2f2,		/* [111] = 2.00e-003 = घात(10.0, 0.05 * -54.0dB) */
	0x3b0a8276,		/* [112] = 2.11e-003 = घात(10.0, 0.05 * -53.5dB) */
	0x3b12b782,		/* [113] = 2.24e-003 = घात(10.0, 0.05 * -53.0dB) */
	0x3b1b690d,		/* [114] = 2.37e-003 = घात(10.0, 0.05 * -52.5dB) */
	0x3b249e76,		/* [115] = 2.51e-003 = घात(10.0, 0.05 * -52.0dB) */
	0x3b2e5f8f,		/* [116] = 2.66e-003 = घात(10.0, 0.05 * -51.5dB) */
	0x3b38b49f,		/* [117] = 2.82e-003 = घात(10.0, 0.05 * -51.0dB) */
	0x3b43a669,		/* [118] = 2.99e-003 = घात(10.0, 0.05 * -50.5dB) */
	0x3b4f3e37,		/* [119] = 3.16e-003 = घात(10.0, 0.05 * -50.0dB) */
	0x3b5b85e0,		/* [120] = 3.35e-003 = घात(10.0, 0.05 * -49.5dB) */
	0x3b6887cf,		/* [121] = 3.55e-003 = घात(10.0, 0.05 * -49.0dB) */
	0x3b764f0e,		/* [122] = 3.76e-003 = घात(10.0, 0.05 * -48.5dB) */
	0x3b8273a6,		/* [123] = 3.98e-003 = घात(10.0, 0.05 * -48.0dB) */
	0x3b8a2e77,		/* [124] = 4.22e-003 = घात(10.0, 0.05 * -47.5dB) */
	0x3b925e89,		/* [125] = 4.47e-003 = घात(10.0, 0.05 * -47.0dB) */
	0x3b9b0ace,		/* [126] = 4.73e-003 = घात(10.0, 0.05 * -46.5dB) */
	0x3ba43aa2,		/* [127] = 5.01e-003 = घात(10.0, 0.05 * -46.0dB) */
	0x3badf5d1,		/* [128] = 5.31e-003 = घात(10.0, 0.05 * -45.5dB) */
	0x3bb8449c,		/* [129] = 5.62e-003 = घात(10.0, 0.05 * -45.0dB) */
	0x3bc32fc3,		/* [130] = 5.96e-003 = घात(10.0, 0.05 * -44.5dB) */
	0x3bcec08a,		/* [131] = 6.31e-003 = घात(10.0, 0.05 * -44.0dB) */
	0x3bdb00c0,		/* [132] = 6.68e-003 = घात(10.0, 0.05 * -43.5dB) */
	0x3be7facc,		/* [133] = 7.08e-003 = घात(10.0, 0.05 * -43.0dB) */
	0x3bf5b9b0,		/* [134] = 7.50e-003 = घात(10.0, 0.05 * -42.5dB) */
	0x3c02248a,		/* [135] = 7.94e-003 = घात(10.0, 0.05 * -42.0dB) */
	0x3c09daac,		/* [136] = 8.41e-003 = घात(10.0, 0.05 * -41.5dB) */
	0x3c1205c6,		/* [137] = 8.91e-003 = घात(10.0, 0.05 * -41.0dB) */
	0x3c1aacc8,		/* [138] = 9.44e-003 = घात(10.0, 0.05 * -40.5dB) */
	0x3c23d70a,		/* [139] = 1.00e-002 = घात(10.0, 0.05 * -40.0dB) */
	0x3c2d8c52,		/* [140] = 1.06e-002 = घात(10.0, 0.05 * -39.5dB) */
	0x3c37d4dd,		/* [141] = 1.12e-002 = घात(10.0, 0.05 * -39.0dB) */
	0x3c42b965,		/* [142] = 1.19e-002 = घात(10.0, 0.05 * -38.5dB) */
	0x3c4e4329,		/* [143] = 1.26e-002 = घात(10.0, 0.05 * -38.0dB) */
	0x3c5a7bf1,		/* [144] = 1.33e-002 = घात(10.0, 0.05 * -37.5dB) */
	0x3c676e1e,		/* [145] = 1.41e-002 = घात(10.0, 0.05 * -37.0dB) */
	0x3c7524ac,		/* [146] = 1.50e-002 = घात(10.0, 0.05 * -36.5dB) */
	0x3c81d59f,		/* [147] = 1.58e-002 = घात(10.0, 0.05 * -36.0dB) */
	0x3c898712,		/* [148] = 1.68e-002 = घात(10.0, 0.05 * -35.5dB) */
	0x3c91ad39,		/* [149] = 1.78e-002 = घात(10.0, 0.05 * -35.0dB) */
	0x3c9a4efc,		/* [150] = 1.88e-002 = घात(10.0, 0.05 * -34.5dB) */
	0x3ca373af,		/* [151] = 2.00e-002 = घात(10.0, 0.05 * -34.0dB) */
	0x3cad2314,		/* [152] = 2.11e-002 = घात(10.0, 0.05 * -33.5dB) */
	0x3cb76563,		/* [153] = 2.24e-002 = घात(10.0, 0.05 * -33.0dB) */
	0x3cc24350,		/* [154] = 2.37e-002 = घात(10.0, 0.05 * -32.5dB) */
	0x3ccdc614,		/* [155] = 2.51e-002 = घात(10.0, 0.05 * -32.0dB) */
	0x3cd9f773,		/* [156] = 2.66e-002 = घात(10.0, 0.05 * -31.5dB) */
	0x3ce6e1c6,		/* [157] = 2.82e-002 = घात(10.0, 0.05 * -31.0dB) */
	0x3cf49003,		/* [158] = 2.99e-002 = घात(10.0, 0.05 * -30.5dB) */
	0x3d0186e2,		/* [159] = 3.16e-002 = घात(10.0, 0.05 * -30.0dB) */
	0x3d0933ac,		/* [160] = 3.35e-002 = घात(10.0, 0.05 * -29.5dB) */
	0x3d1154e1,		/* [161] = 3.55e-002 = घात(10.0, 0.05 * -29.0dB) */
	0x3d19f169,		/* [162] = 3.76e-002 = घात(10.0, 0.05 * -28.5dB) */
	0x3d231090,		/* [163] = 3.98e-002 = घात(10.0, 0.05 * -28.0dB) */
	0x3d2cba15,		/* [164] = 4.22e-002 = घात(10.0, 0.05 * -27.5dB) */
	0x3d36f62b,		/* [165] = 4.47e-002 = घात(10.0, 0.05 * -27.0dB) */
	0x3d41cd81,		/* [166] = 4.73e-002 = घात(10.0, 0.05 * -26.5dB) */
	0x3d4d494a,		/* [167] = 5.01e-002 = घात(10.0, 0.05 * -26.0dB) */
	0x3d597345,		/* [168] = 5.31e-002 = घात(10.0, 0.05 * -25.5dB) */
	0x3d6655c3,		/* [169] = 5.62e-002 = घात(10.0, 0.05 * -25.0dB) */
	0x3d73fbb4,		/* [170] = 5.96e-002 = घात(10.0, 0.05 * -24.5dB) */
	0x3d813856,		/* [171] = 6.31e-002 = घात(10.0, 0.05 * -24.0dB) */
	0x3d88e078,		/* [172] = 6.68e-002 = घात(10.0, 0.05 * -23.5dB) */
	0x3d90fcbf,		/* [173] = 7.08e-002 = घात(10.0, 0.05 * -23.0dB) */
	0x3d99940e,		/* [174] = 7.50e-002 = घात(10.0, 0.05 * -22.5dB) */
	0x3da2adad,		/* [175] = 7.94e-002 = घात(10.0, 0.05 * -22.0dB) */
	0x3dac5156,		/* [176] = 8.41e-002 = घात(10.0, 0.05 * -21.5dB) */
	0x3db68738,		/* [177] = 8.91e-002 = घात(10.0, 0.05 * -21.0dB) */
	0x3dc157fb,		/* [178] = 9.44e-002 = घात(10.0, 0.05 * -20.5dB) */
	0x3dcccccd,		/* [179] = 1.00e-001 = घात(10.0, 0.05 * -20.0dB) */
	0x3dd8ef67,		/* [180] = 1.06e-001 = घात(10.0, 0.05 * -19.5dB) */
	0x3de5ca15,		/* [181] = 1.12e-001 = घात(10.0, 0.05 * -19.0dB) */
	0x3df367bf,		/* [182] = 1.19e-001 = घात(10.0, 0.05 * -18.5dB) */
	0x3e00e9f9,		/* [183] = 1.26e-001 = घात(10.0, 0.05 * -18.0dB) */
	0x3e088d77,		/* [184] = 1.33e-001 = घात(10.0, 0.05 * -17.5dB) */
	0x3e10a4d3,		/* [185] = 1.41e-001 = घात(10.0, 0.05 * -17.0dB) */
	0x3e1936ec,		/* [186] = 1.50e-001 = घात(10.0, 0.05 * -16.5dB) */
	0x3e224b06,		/* [187] = 1.58e-001 = घात(10.0, 0.05 * -16.0dB) */
	0x3e2be8d7,		/* [188] = 1.68e-001 = घात(10.0, 0.05 * -15.5dB) */
	0x3e361887,		/* [189] = 1.78e-001 = घात(10.0, 0.05 * -15.0dB) */
	0x3e40e2bb,		/* [190] = 1.88e-001 = घात(10.0, 0.05 * -14.5dB) */
	0x3e4c509b,		/* [191] = 2.00e-001 = घात(10.0, 0.05 * -14.0dB) */
	0x3e586bd9,		/* [192] = 2.11e-001 = घात(10.0, 0.05 * -13.5dB) */
	0x3e653ebb,		/* [193] = 2.24e-001 = घात(10.0, 0.05 * -13.0dB) */
	0x3e72d424,		/* [194] = 2.37e-001 = घात(10.0, 0.05 * -12.5dB) */
	0x3e809bcc,		/* [195] = 2.51e-001 = घात(10.0, 0.05 * -12.0dB) */
	0x3e883aa8,		/* [196] = 2.66e-001 = घात(10.0, 0.05 * -11.5dB) */
	0x3e904d1c,		/* [197] = 2.82e-001 = घात(10.0, 0.05 * -11.0dB) */
	0x3e98da02,		/* [198] = 2.99e-001 = घात(10.0, 0.05 * -10.5dB) */
	0x3ea1e89b,		/* [199] = 3.16e-001 = घात(10.0, 0.05 * -10.0dB) */
	0x3eab8097,		/* [200] = 3.35e-001 = घात(10.0, 0.05 * -9.5dB) */
	0x3eb5aa1a,		/* [201] = 3.55e-001 = घात(10.0, 0.05 * -9.0dB) */
	0x3ec06dc3,		/* [202] = 3.76e-001 = घात(10.0, 0.05 * -8.5dB) */
	0x3ecbd4b4,		/* [203] = 3.98e-001 = घात(10.0, 0.05 * -8.0dB) */
	0x3ed7e89b,		/* [204] = 4.22e-001 = घात(10.0, 0.05 * -7.5dB) */
	0x3ee4b3b6,		/* [205] = 4.47e-001 = घात(10.0, 0.05 * -7.0dB) */
	0x3ef240e2,		/* [206] = 4.73e-001 = घात(10.0, 0.05 * -6.5dB) */
	0x3f004dce,		/* [207] = 5.01e-001 = घात(10.0, 0.05 * -6.0dB) */
	0x3f07e80b,		/* [208] = 5.31e-001 = घात(10.0, 0.05 * -5.5dB) */
	0x3f0ff59a,		/* [209] = 5.62e-001 = घात(10.0, 0.05 * -5.0dB) */
	0x3f187d50,		/* [210] = 5.96e-001 = घात(10.0, 0.05 * -4.5dB) */
	0x3f21866c,		/* [211] = 6.31e-001 = घात(10.0, 0.05 * -4.0dB) */
	0x3f2b1896,		/* [212] = 6.68e-001 = घात(10.0, 0.05 * -3.5dB) */
	0x3f353bef,		/* [213] = 7.08e-001 = घात(10.0, 0.05 * -3.0dB) */
	0x3f3ff911,		/* [214] = 7.50e-001 = घात(10.0, 0.05 * -2.5dB) */
	0x3f4b5918,		/* [215] = 7.94e-001 = घात(10.0, 0.05 * -2.0dB) */
	0x3f5765ac,		/* [216] = 8.41e-001 = घात(10.0, 0.05 * -1.5dB) */
	0x3f642905,		/* [217] = 8.91e-001 = घात(10.0, 0.05 * -1.0dB) */
	0x3f71adf9,		/* [218] = 9.44e-001 = घात(10.0, 0.05 * -0.5dB) */
	0x3f800000,		/* [219] = 1.00e+000 = घात(10.0, 0.05 * 0.0dB) */
	0x3f8795a0,		/* [220] = 1.06e+000 = घात(10.0, 0.05 * 0.5dB) */
	0x3f8f9e4d,		/* [221] = 1.12e+000 = घात(10.0, 0.05 * 1.0dB) */
	0x3f9820d7,		/* [222] = 1.19e+000 = घात(10.0, 0.05 * 1.5dB) */
	0x3fa12478,		/* [223] = 1.26e+000 = घात(10.0, 0.05 * 2.0dB) */
	0x3faab0d5,		/* [224] = 1.33e+000 = घात(10.0, 0.05 * 2.5dB) */
	0x3fb4ce08,		/* [225] = 1.41e+000 = घात(10.0, 0.05 * 3.0dB) */
	0x3fbf84a6,		/* [226] = 1.50e+000 = घात(10.0, 0.05 * 3.5dB) */
	0x3fcaddc8,		/* [227] = 1.58e+000 = घात(10.0, 0.05 * 4.0dB) */
	0x3fd6e30d,		/* [228] = 1.68e+000 = घात(10.0, 0.05 * 4.5dB) */
	0x3fe39ea9,		/* [229] = 1.78e+000 = घात(10.0, 0.05 * 5.0dB) */
	0x3ff11b6a,		/* [230] = 1.88e+000 = घात(10.0, 0.05 * 5.5dB) */
	0x3fff64c1,		/* [231] = 2.00e+000 = घात(10.0, 0.05 * 6.0dB) */
	0x40074368,		/* [232] = 2.11e+000 = घात(10.0, 0.05 * 6.5dB) */
	0x400f4735,		/* [233] = 2.24e+000 = घात(10.0, 0.05 * 7.0dB) */
	0x4017c496,		/* [234] = 2.37e+000 = घात(10.0, 0.05 * 7.5dB) */
	0x4020c2bf,		/* [235] = 2.51e+000 = घात(10.0, 0.05 * 8.0dB) */
	0x402a4952,		/* [236] = 2.66e+000 = घात(10.0, 0.05 * 8.5dB) */
	0x40346063,		/* [237] = 2.82e+000 = घात(10.0, 0.05 * 9.0dB) */
	0x403f1082,		/* [238] = 2.99e+000 = घात(10.0, 0.05 * 9.5dB) */
	0x404a62c2,		/* [239] = 3.16e+000 = घात(10.0, 0.05 * 10.0dB) */
	0x405660bd,		/* [240] = 3.35e+000 = घात(10.0, 0.05 * 10.5dB) */
	0x406314a0,		/* [241] = 3.55e+000 = घात(10.0, 0.05 * 11.0dB) */
	0x40708933,		/* [242] = 3.76e+000 = घात(10.0, 0.05 * 11.5dB) */
	0x407ec9e1,		/* [243] = 3.98e+000 = घात(10.0, 0.05 * 12.0dB) */
	0x4086f161,		/* [244] = 4.22e+000 = घात(10.0, 0.05 * 12.5dB) */
	0x408ef052,		/* [245] = 4.47e+000 = घात(10.0, 0.05 * 13.0dB) */
	0x4097688d,		/* [246] = 4.73e+000 = घात(10.0, 0.05 * 13.5dB) */
	0x40a06142,		/* [247] = 5.01e+000 = घात(10.0, 0.05 * 14.0dB) */
	0x40a9e20e,		/* [248] = 5.31e+000 = घात(10.0, 0.05 * 14.5dB) */
	0x40b3f300,		/* [249] = 5.62e+000 = घात(10.0, 0.05 * 15.0dB) */
	0x40be9ca5,		/* [250] = 5.96e+000 = घात(10.0, 0.05 * 15.5dB) */
	0x40c9e807,		/* [251] = 6.31e+000 = घात(10.0, 0.05 * 16.0dB) */
	0x40d5debc,		/* [252] = 6.68e+000 = घात(10.0, 0.05 * 16.5dB) */
	0x40e28aeb,		/* [253] = 7.08e+000 = घात(10.0, 0.05 * 17.0dB) */
	0x40eff755,		/* [254] = 7.50e+000 = घात(10.0, 0.05 * 17.5dB) */
	0x40fe2f5e,		/* [255] = 7.94e+000 = घात(10.0, 0.05 * 18.0dB) */
पूर्ण;

#घोषणा MIXART_DIGITAL_LEVEL_MIN   0      /* -109.5 dB */
#घोषणा MIXART_DIGITAL_LEVEL_MAX   255    /*  18.0 dB */
#घोषणा MIXART_DIGITAL_ZERO_LEVEL  219    /*  0.0 dB */


पूर्णांक mixart_update_playback_stream_level(काष्ठा snd_mixart* chip, पूर्णांक is_aes, पूर्णांक idx)
अणु
	पूर्णांक err, i;
	पूर्णांक volume[2];
	काष्ठा mixart_msg request;
	काष्ठा mixart_set_out_stream_level_req set_level;
	u32 status = 0;
	काष्ठा mixart_pipe *pipe;

	स_रखो(&set_level, 0, माप(set_level));
	set_level.nb_of_stream = 1;
	set_level.stream_level.desc.stream_idx = idx;

	अगर(is_aes) अणु
		pipe = &chip->pipe_out_dig;	/* AES playback */
		idx += MIXART_PLAYBACK_STREAMS;
	पूर्ण अन्यथा अणु
		pipe = &chip->pipe_out_ana;	/* analog playback */
	पूर्ण

	/* only when pipe exists ! */
	अगर(pipe->status == PIPE_UNDEFINED)
		वापस 0;

	set_level.stream_level.desc.uid_pipe = pipe->group_uid;

	क्रम(i=0; i<2; i++) अणु
		अगर(chip->digital_playback_active[idx][i])
			volume[i] = chip->digital_playback_volume[idx][i];
		अन्यथा
			volume[i] = MIXART_DIGITAL_LEVEL_MIN;
	पूर्ण

	set_level.stream_level.out_level.valid_mask1 = MIXART_OUT_STREAM_SET_LEVEL_LEFT_AUDIO1 | MIXART_OUT_STREAM_SET_LEVEL_RIGHT_AUDIO2;
	set_level.stream_level.out_level.left_to_out1_level = mixart_digital_level[volume[0]];
	set_level.stream_level.out_level.right_to_out2_level = mixart_digital_level[volume[1]];

	request.message_id = MSG_STREAM_SET_OUT_STREAM_LEVEL;
	request.uid = (काष्ठा mixart_uid)अणु0,0पूर्ण;
	request.data = &set_level;
	request.size = माप(set_level);

	err = snd_mixart_send_msg(chip->mgr, &request, माप(status), &status);
	अगर((err<0) || status) अणु
		dev_dbg(chip->card->dev,
			"error MSG_STREAM_SET_OUT_STREAM_LEVEL card(%d) status(%x)\n",
			chip->chip_idx, status);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक mixart_update_capture_stream_level(काष्ठा snd_mixart* chip, पूर्णांक is_aes)
अणु
	पूर्णांक err, i, idx;
	काष्ठा mixart_pipe *pipe;
	काष्ठा mixart_msg request;
	काष्ठा mixart_set_in_audio_level_req set_level;
	u32 status = 0;

	अगर(is_aes) अणु
		idx = 1;
		pipe = &chip->pipe_in_dig;
	पूर्ण अन्यथा अणु
		idx = 0;
		pipe = &chip->pipe_in_ana;
	पूर्ण

	/* only when pipe exists ! */
	अगर(pipe->status == PIPE_UNDEFINED)
		वापस 0;

	स_रखो(&set_level, 0, माप(set_level));
	set_level.audio_count = 2;
	set_level.level[0].connector = pipe->uid_left_connector;
	set_level.level[1].connector = pipe->uid_right_connector;

	क्रम(i=0; i<2; i++) अणु
		set_level.level[i].valid_mask1 = MIXART_AUDIO_LEVEL_DIGITAL_MASK;
		set_level.level[i].digital_level = mixart_digital_level[chip->digital_capture_volume[idx][i]];
	पूर्ण

	request.message_id = MSG_STREAM_SET_IN_AUDIO_LEVEL;
	request.uid = (काष्ठा mixart_uid)अणु0,0पूर्ण;
	request.data = &set_level;
	request.size = माप(set_level);

	err = snd_mixart_send_msg(chip->mgr, &request, माप(status), &status);
	अगर((err<0) || status) अणु
		dev_dbg(chip->card->dev,
			"error MSG_STREAM_SET_IN_AUDIO_LEVEL card(%d) status(%x)\n",
			chip->chip_idx, status);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


/* shared */
अटल पूर्णांक mixart_digital_vol_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = MIXART_DIGITAL_LEVEL_MIN;   /* -109.5 dB */
	uinfo->value.पूर्णांकeger.max = MIXART_DIGITAL_LEVEL_MAX;   /*   18.0 dB */
	वापस 0;
पूर्ण

#घोषणा MIXART_VOL_REC_MASK	1
#घोषणा MIXART_VOL_AES_MASK	2

अटल पूर्णांक mixart_pcm_vol_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_mixart *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id); /* index */
	पूर्णांक *stored_volume;
	पूर्णांक is_capture = kcontrol->निजी_value & MIXART_VOL_REC_MASK;
	पूर्णांक is_aes = kcontrol->निजी_value & MIXART_VOL_AES_MASK;
	mutex_lock(&chip->mgr->mixer_mutex);
	अगर(is_capture) अणु
		अगर(is_aes)	stored_volume = chip->digital_capture_volume[1];	/* AES capture */
		अन्यथा		stored_volume = chip->digital_capture_volume[0];	/* analog capture */
	पूर्ण अन्यथा अणु
		snd_BUG_ON(idx >= MIXART_PLAYBACK_STREAMS);
		अगर(is_aes)	stored_volume = chip->digital_playback_volume[MIXART_PLAYBACK_STREAMS + idx]; /* AES playback */
		अन्यथा		stored_volume = chip->digital_playback_volume[idx];	/* analog playback */
	पूर्ण
	ucontrol->value.पूर्णांकeger.value[0] = stored_volume[0];
	ucontrol->value.पूर्णांकeger.value[1] = stored_volume[1];
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक mixart_pcm_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_mixart *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id); /* index */
	पूर्णांक changed = 0;
	पूर्णांक is_capture = kcontrol->निजी_value & MIXART_VOL_REC_MASK;
	पूर्णांक is_aes = kcontrol->निजी_value & MIXART_VOL_AES_MASK;
	पूर्णांक* stored_volume;
	पूर्णांक i;
	mutex_lock(&chip->mgr->mixer_mutex);
	अगर (is_capture) अणु
		अगर (is_aes)	/* AES capture */
			stored_volume = chip->digital_capture_volume[1];
		अन्यथा		/* analog capture */
			stored_volume = chip->digital_capture_volume[0];
	पूर्ण अन्यथा अणु
		snd_BUG_ON(idx >= MIXART_PLAYBACK_STREAMS);
		अगर (is_aes)	/* AES playback */
			stored_volume = chip->digital_playback_volume[MIXART_PLAYBACK_STREAMS + idx];
		अन्यथा		/* analog playback */
			stored_volume = chip->digital_playback_volume[idx];
	पूर्ण
	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांक vol = ucontrol->value.पूर्णांकeger.value[i];
		अगर (vol < MIXART_DIGITAL_LEVEL_MIN ||
		    vol > MIXART_DIGITAL_LEVEL_MAX)
			जारी;
		अगर (stored_volume[i] != vol) अणु
			stored_volume[i] = vol;
			changed = 1;
		पूर्ण
	पूर्ण
	अगर (changed) अणु
		अगर (is_capture)
			mixart_update_capture_stream_level(chip, is_aes);
		अन्यथा
			mixart_update_playback_stream_level(chip, is_aes, idx);
	पूर्ण
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस changed;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_digital, -10950, 50, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_mixart_pcm_vol =
अणु
	.अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
		   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	/* name will be filled later */
	/* count will be filled later */
	.info =         mixart_digital_vol_info,		/* shared */
	.get =          mixart_pcm_vol_get,
	.put =          mixart_pcm_vol_put,
	.tlv = अणु .p = db_scale_digital पूर्ण,
पूर्ण;


अटल पूर्णांक mixart_pcm_sw_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_mixart *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id); /* index */
	snd_BUG_ON(idx >= MIXART_PLAYBACK_STREAMS);
	mutex_lock(&chip->mgr->mixer_mutex);
	अगर(kcontrol->निजी_value & MIXART_VOL_AES_MASK)	/* AES playback */
		idx += MIXART_PLAYBACK_STREAMS;
	ucontrol->value.पूर्णांकeger.value[0] = chip->digital_playback_active[idx][0];
	ucontrol->value.पूर्णांकeger.value[1] = chip->digital_playback_active[idx][1];
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक mixart_pcm_sw_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_mixart *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	पूर्णांक is_aes = kcontrol->निजी_value & MIXART_VOL_AES_MASK;
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id); /* index */
	पूर्णांक i, j;
	snd_BUG_ON(idx >= MIXART_PLAYBACK_STREAMS);
	mutex_lock(&chip->mgr->mixer_mutex);
	j = idx;
	अगर (is_aes)
		j += MIXART_PLAYBACK_STREAMS;
	क्रम (i = 0; i < 2; i++) अणु
		अगर (chip->digital_playback_active[j][i] !=
		    ucontrol->value.पूर्णांकeger.value[i]) अणु
			chip->digital_playback_active[j][i] =
				!!ucontrol->value.पूर्णांकeger.value[i];
			changed = 1;
		पूर्ण
	पूर्ण
	अगर (changed)
		mixart_update_playback_stream_level(chip, is_aes, idx);
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mixart_control_pcm_चयन = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	/* name will be filled later */
	.count =        MIXART_PLAYBACK_STREAMS,
	.info =         mixart_sw_info,		/* shared */
	.get =          mixart_pcm_sw_get,
	.put =          mixart_pcm_sw_put
पूर्ण;

अटल पूर्णांक mixart_update_monitoring(काष्ठा snd_mixart* chip, पूर्णांक channel)
अणु
	पूर्णांक err;
	काष्ठा mixart_msg request;
	काष्ठा mixart_set_out_audio_level audio_level;
	u32 resp = 0;

	अगर(chip->pipe_out_ana.status == PIPE_UNDEFINED)
		वापस -EINVAL; /* no pipe defined */

	अगर(!channel)	request.uid = chip->pipe_out_ana.uid_left_connector;
	अन्यथा		request.uid = chip->pipe_out_ana.uid_right_connector;
	request.message_id = MSG_CONNECTOR_SET_OUT_AUDIO_LEVEL;
	request.data = &audio_level;
	request.size = माप(audio_level);

	स_रखो(&audio_level, 0, माप(audio_level));
	audio_level.valid_mask1 = MIXART_AUDIO_LEVEL_MONITOR_MASK | MIXART_AUDIO_LEVEL_MUTE_M1_MASK;
	audio_level.monitor_level = mixart_digital_level[chip->monitoring_volume[channel!=0]];
	audio_level.monitor_mute1 = !chip->monitoring_active[channel!=0];

	err = snd_mixart_send_msg(chip->mgr, &request, माप(resp), &resp);
	अगर((err<0) || resp) अणु
		dev_dbg(chip->card->dev,
			"error MSG_CONNECTOR_SET_OUT_AUDIO_LEVEL card(%d) resp(%x)\n",
			chip->chip_idx, resp);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * monitoring level control
 */

अटल पूर्णांक mixart_monitor_vol_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_mixart *chip = snd_kcontrol_chip(kcontrol);
	mutex_lock(&chip->mgr->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->monitoring_volume[0];
	ucontrol->value.पूर्णांकeger.value[1] = chip->monitoring_volume[1];
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक mixart_monitor_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_mixart *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	पूर्णांक i;
	mutex_lock(&chip->mgr->mixer_mutex);
	क्रम (i = 0; i < 2; i++) अणु
		अगर (chip->monitoring_volume[i] !=
		    ucontrol->value.पूर्णांकeger.value[i]) अणु
			chip->monitoring_volume[i] =
				!!ucontrol->value.पूर्णांकeger.value[i];
			mixart_update_monitoring(chip, i);
			changed = 1;
		पूर्ण
	पूर्ण
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mixart_control_monitor_vol = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
		   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.name =         "Monitoring Volume",
	.info =		mixart_digital_vol_info,		/* shared */
	.get =		mixart_monitor_vol_get,
	.put =		mixart_monitor_vol_put,
	.tlv = अणु .p = db_scale_digital पूर्ण,
पूर्ण;

/*
 * monitoring चयन control
 */

अटल पूर्णांक mixart_monitor_sw_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_mixart *chip = snd_kcontrol_chip(kcontrol);
	mutex_lock(&chip->mgr->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->monitoring_active[0];
	ucontrol->value.पूर्णांकeger.value[1] = chip->monitoring_active[1];
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक mixart_monitor_sw_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_mixart *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	पूर्णांक i;
	mutex_lock(&chip->mgr->mixer_mutex);
	क्रम (i = 0; i < 2; i++) अणु
		अगर (chip->monitoring_active[i] !=
		    ucontrol->value.पूर्णांकeger.value[i]) अणु
			chip->monitoring_active[i] =
				!!ucontrol->value.पूर्णांकeger.value[i];
			changed |= (1<<i); /* mask 0x01 ans 0x02 */
		पूर्ण
	पूर्ण
	अगर (changed) अणु
		/* allocate or release resources क्रम monitoring */
		पूर्णांक allocate = chip->monitoring_active[0] ||
			chip->monitoring_active[1];
		अगर (allocate) अणु
			/* allocate the playback pipe क्रम monitoring */
			snd_mixart_add_ref_pipe(chip, MIXART_PCM_ANALOG, 0, 1);
			/* allocate the capture pipe क्रम monitoring */
			snd_mixart_add_ref_pipe(chip, MIXART_PCM_ANALOG, 1, 1);
		पूर्ण
		अगर (changed & 0x01)
			mixart_update_monitoring(chip, 0);
		अगर (changed & 0x02)
			mixart_update_monitoring(chip, 1);
		अगर (!allocate) अणु
			/* release the capture pipe क्रम monitoring */
			snd_mixart_समाप्त_ref_pipe(chip->mgr,
						 &chip->pipe_in_ana, 1);
			/* release the playback pipe क्रम monitoring */
			snd_mixart_समाप्त_ref_pipe(chip->mgr,
						 &chip->pipe_out_ana, 1);
		पूर्ण
	पूर्ण

	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस (changed != 0);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mixart_control_monitor_sw = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Monitoring Switch",
	.info =         mixart_sw_info,		/* shared */
	.get =          mixart_monitor_sw_get,
	.put =          mixart_monitor_sw_put
पूर्ण;


अटल व्योम mixart_reset_audio_levels(काष्ठा snd_mixart *chip)
अणु
	/* analog volumes can be set even अगर there is no pipe */
	mixart_update_analog_audio_level(chip, 0);
	/* analog levels क्रम capture only on the first two chips */
	अगर(chip->chip_idx < 2) अणु
		mixart_update_analog_audio_level(chip, 1);
	पूर्ण
	वापस;
पूर्ण


पूर्णांक snd_mixart_create_mixer(काष्ठा mixart_mgr *mgr)
अणु
	काष्ठा snd_mixart *chip;
	पूर्णांक err, i;

	mutex_init(&mgr->mixer_mutex); /* can be in another place */

	क्रम(i=0; i<mgr->num_cards; i++) अणु
		काष्ठा snd_kcontrol_new temp;
		chip = mgr->chip[i];

		/* analog output level control */
		temp = mixart_control_analog_level;
		temp.name = "Master Playback Volume";
		temp.निजी_value = 0; /* playback */
		अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&temp, chip))) < 0)
			वापस err;
		/* output mute controls */
		अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&mixart_control_output_चयन, chip))) < 0)
			वापस err;

		/* analog input level control only on first two chips !*/
		अगर(i<2) अणु
			temp = mixart_control_analog_level;
			temp.name = "Master Capture Volume";
			temp.निजी_value = 1; /* capture */
			अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&temp, chip))) < 0)
				वापस err;
		पूर्ण

		temp = snd_mixart_pcm_vol;
		temp.name = "PCM Playback Volume";
		temp.count = MIXART_PLAYBACK_STREAMS;
		temp.निजी_value = 0; /* playback analog */
		अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&temp, chip))) < 0)
			वापस err;

		temp.name = "PCM Capture Volume";
		temp.count = 1;
		temp.निजी_value = MIXART_VOL_REC_MASK; /* capture analog */
		अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&temp, chip))) < 0)
			वापस err;

		अगर(mgr->board_type == MIXART_DAUGHTER_TYPE_AES) अणु
			temp.name = "AES Playback Volume";
			temp.count = MIXART_PLAYBACK_STREAMS;
			temp.निजी_value = MIXART_VOL_AES_MASK; /* playback AES/EBU */
			अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&temp, chip))) < 0)
				वापस err;

			temp.name = "AES Capture Volume";
			temp.count = 0;
			temp.निजी_value = MIXART_VOL_REC_MASK | MIXART_VOL_AES_MASK; /* capture AES/EBU */
			अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&temp, chip))) < 0)
				वापस err;
		पूर्ण
		temp = mixart_control_pcm_चयन;
		temp.name = "PCM Playback Switch";
		temp.निजी_value = 0; /* playback analog */
		अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&temp, chip))) < 0)
			वापस err;

		अगर(mgr->board_type == MIXART_DAUGHTER_TYPE_AES) अणु
			temp.name = "AES Playback Switch";
			temp.निजी_value = MIXART_VOL_AES_MASK; /* playback AES/EBU */
			अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&temp, chip))) < 0)
				वापस err;
		पूर्ण

		/* monitoring */
		अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&mixart_control_monitor_vol, chip))) < 0)
			वापस err;
		अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&mixart_control_monitor_sw, chip))) < 0)
			वापस err;

		/* init all mixer data and program the master volumes/चयनes */
		mixart_reset_audio_levels(chip);
	पूर्ण
	वापस 0;
पूर्ण
