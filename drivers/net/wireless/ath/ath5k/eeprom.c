<शैली गुरु>
/*
 * Copyright (c) 2004-2008 Reyk Floeter <reyk@खोलोbsd.org>
 * Copyright (c) 2006-2009 Nick Kossअगरidis <mickflemm@gmail.com>
 * Copyright (c) 2008-2009 Felix Fietkau <nbd@खोलोwrt.org>
 *
 * Permission to use, copy, modअगरy, and distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/*************************************\
* EEPROM access functions and helpers *
\*************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>

#समावेश "ath5k.h"
#समावेश "reg.h"
#समावेश "debug.h"


/******************\
* Helper functions *
\******************/

/*
 * Translate binary channel representation in EEPROM to frequency
 */
अटल u16 ath5k_eeprom_bin2freq(काष्ठा ath5k_eeprom_info *ee, u16 bin,
							अचिन्हित पूर्णांक mode)
अणु
	u16 val;

	अगर (bin == AR5K_EEPROM_CHANNEL_DIS)
		वापस bin;

	अगर (mode == AR5K_EEPROM_MODE_11A) अणु
		अगर (ee->ee_version > AR5K_EEPROM_VERSION_3_2)
			val = (5 * bin) + 4800;
		अन्यथा
			val = bin > 62 ? (10 * 62) + (5 * (bin - 62)) + 5100 :
				(bin * 10) + 5100;
	पूर्ण अन्यथा अणु
		अगर (ee->ee_version > AR5K_EEPROM_VERSION_3_2)
			val = bin + 2300;
		अन्यथा
			val = bin + 2400;
	पूर्ण

	वापस val;
पूर्ण


/*********\
* Parsers *
\*********/

/*
 * Initialize eeprom & capabilities काष्ठाs
 */
अटल पूर्णांक
ath5k_eeprom_init_header(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u16 val;
	u32 cksum, offset, eep_max = AR5K_EEPROM_INFO_MAX;

	/*
	 * Read values from EEPROM and store them in the capability काष्ठाure
	 */
	AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MAGIC, ee_magic);
	AR5K_EEPROM_READ_HDR(AR5K_EEPROM_PROTECT, ee_protect);
	AR5K_EEPROM_READ_HDR(AR5K_EEPROM_REG_DOMAIN, ee_regकरोमुख्य);
	AR5K_EEPROM_READ_HDR(AR5K_EEPROM_VERSION, ee_version);
	AR5K_EEPROM_READ_HDR(AR5K_EEPROM_HDR, ee_header);

	/* Return अगर we have an old EEPROM */
	अगर (ah->ah_ee_version < AR5K_EEPROM_VERSION_3_0)
		वापस 0;

	/*
	 * Validate the checksum of the EEPROM date. There are some
	 * devices with invalid EEPROMs.
	 */
	AR5K_EEPROM_READ(AR5K_EEPROM_SIZE_UPPER, val);
	अगर (val) अणु
		eep_max = (val & AR5K_EEPROM_SIZE_UPPER_MASK) <<
			   AR5K_EEPROM_SIZE_ENDLOC_SHIFT;
		AR5K_EEPROM_READ(AR5K_EEPROM_SIZE_LOWER, val);
		eep_max = (eep_max | val) - AR5K_EEPROM_INFO_BASE;

		/*
		 * Fail safe check to prevent stupid loops due
		 * to busted EEPROMs. XXX: This value is likely too
		 * big still, रुकोing on a better value.
		 */
		अगर (eep_max > (3 * AR5K_EEPROM_INFO_MAX)) अणु
			ATH5K_ERR(ah, "Invalid max custom EEPROM size: "
				  "%d (0x%04x) max expected: %d (0x%04x)\n",
				  eep_max, eep_max,
				  3 * AR5K_EEPROM_INFO_MAX,
				  3 * AR5K_EEPROM_INFO_MAX);
			वापस -EIO;
		पूर्ण
	पूर्ण

	क्रम (cksum = 0, offset = 0; offset < eep_max; offset++) अणु
		AR5K_EEPROM_READ(AR5K_EEPROM_INFO(offset), val);
		cksum ^= val;
	पूर्ण
	अगर (cksum != AR5K_EEPROM_INFO_CKSUM) अणु
		ATH5K_ERR(ah, "Invalid EEPROM "
			  "checksum: 0x%04x eep_max: 0x%04x (%s)\n",
			  cksum, eep_max,
			  eep_max == AR5K_EEPROM_INFO_MAX ?
				"default size" : "custom size");
		वापस -EIO;
	पूर्ण

	AR5K_EEPROM_READ_HDR(AR5K_EEPROM_ANT_GAIN(ah->ah_ee_version),
	    ee_ant_gain);

	अगर (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_0) अणु
		AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MISC0, ee_misc0);
		AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MISC1, ee_misc1);

		/* XXX: Don't know which versions include these two */
		AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MISC2, ee_misc2);

		अगर (ee->ee_version >= AR5K_EEPROM_VERSION_4_3)
			AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MISC3, ee_misc3);

		अगर (ee->ee_version >= AR5K_EEPROM_VERSION_5_0) अणु
			AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MISC4, ee_misc4);
			AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MISC5, ee_misc5);
			AR5K_EEPROM_READ_HDR(AR5K_EEPROM_MISC6, ee_misc6);
		पूर्ण
	पूर्ण

	अगर (ah->ah_ee_version < AR5K_EEPROM_VERSION_3_3) अणु
		AR5K_EEPROM_READ(AR5K_EEPROM_OBDB0_2GHZ, val);
		ee->ee_ob[AR5K_EEPROM_MODE_11B][0] = val & 0x7;
		ee->ee_db[AR5K_EEPROM_MODE_11B][0] = (val >> 3) & 0x7;

		AR5K_EEPROM_READ(AR5K_EEPROM_OBDB1_2GHZ, val);
		ee->ee_ob[AR5K_EEPROM_MODE_11G][0] = val & 0x7;
		ee->ee_db[AR5K_EEPROM_MODE_11G][0] = (val >> 3) & 0x7;
	पूर्ण

	AR5K_EEPROM_READ(AR5K_EEPROM_IS_HB63, val);

	अगर ((ah->ah_mac_version == (AR5K_SREV_AR2425 >> 4)) && val)
		ee->ee_is_hb63 = true;
	अन्यथा
		ee->ee_is_hb63 = false;

	AR5K_EEPROM_READ(AR5K_EEPROM_RFKILL, val);
	ee->ee_rfसमाप्त_pin = (u8) AR5K_REG_MS(val, AR5K_EEPROM_RFKILL_GPIO_SEL);
	ee->ee_rfसमाप्त_pol = val & AR5K_EEPROM_RFKILL_POLARITY ? true : false;

	/* Check अगर PCIE_OFFSET poपूर्णांकs to PCIE_SERDES_SECTION
	 * and enable serdes programming अगर needed.
	 *
	 * XXX: Serdes values seem to be fixed so
	 * no need to पढ़ो them here, we ग_लिखो them
	 * during ath5k_hw_init */
	AR5K_EEPROM_READ(AR5K_EEPROM_PCIE_OFFSET, val);
	ee->ee_serdes = (val == AR5K_EEPROM_PCIE_SERDES_SECTION) ?
							true : false;

	वापस 0;
पूर्ण


/*
 * Read antenna infos from eeprom
 */
अटल पूर्णांक ath5k_eeprom_पढ़ो_ants(काष्ठा ath5k_hw *ah, u32 *offset,
		अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u32 o = *offset;
	u16 val;
	पूर्णांक i = 0;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_चयन_settling[mode]	= (val >> 8) & 0x7f;
	ee->ee_atn_tx_rx[mode]		= (val >> 2) & 0x3f;
	ee->ee_ant_control[mode][i]	= (val << 4) & 0x3f;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_ant_control[mode][i++]	|= (val >> 12) & 0xf;
	ee->ee_ant_control[mode][i++]	= (val >> 6) & 0x3f;
	ee->ee_ant_control[mode][i++]	= val & 0x3f;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_ant_control[mode][i++]	= (val >> 10) & 0x3f;
	ee->ee_ant_control[mode][i++]	= (val >> 4) & 0x3f;
	ee->ee_ant_control[mode][i]	= (val << 2) & 0x3f;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_ant_control[mode][i++]	|= (val >> 14) & 0x3;
	ee->ee_ant_control[mode][i++]	= (val >> 8) & 0x3f;
	ee->ee_ant_control[mode][i++]	= (val >> 2) & 0x3f;
	ee->ee_ant_control[mode][i]	= (val << 4) & 0x3f;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_ant_control[mode][i++]	|= (val >> 12) & 0xf;
	ee->ee_ant_control[mode][i++]	= (val >> 6) & 0x3f;
	ee->ee_ant_control[mode][i++]	= val & 0x3f;

	/* Get antenna चयन tables */
	ah->ah_ant_ctl[mode][AR5K_ANT_CTL] =
	    (ee->ee_ant_control[mode][0] << 4);
	ah->ah_ant_ctl[mode][AR5K_ANT_SWTABLE_A] =
	     ee->ee_ant_control[mode][1]	|
	    (ee->ee_ant_control[mode][2] << 6)	|
	    (ee->ee_ant_control[mode][3] << 12) |
	    (ee->ee_ant_control[mode][4] << 18) |
	    (ee->ee_ant_control[mode][5] << 24);
	ah->ah_ant_ctl[mode][AR5K_ANT_SWTABLE_B] =
	     ee->ee_ant_control[mode][6]	|
	    (ee->ee_ant_control[mode][7] << 6)	|
	    (ee->ee_ant_control[mode][8] << 12) |
	    (ee->ee_ant_control[mode][9] << 18) |
	    (ee->ee_ant_control[mode][10] << 24);

	/* वापस new offset */
	*offset = o;

	वापस 0;
पूर्ण

/*
 * Read supported modes and some mode-specअगरic calibration data
 * from eeprom
 */
अटल पूर्णांक ath5k_eeprom_पढ़ो_modes(काष्ठा ath5k_hw *ah, u32 *offset,
		अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u32 o = *offset;
	u16 val;

	ee->ee_n_piers[mode] = 0;
	AR5K_EEPROM_READ(o++, val);
	ee->ee_adc_desired_size[mode]	= (s8)((val >> 8) & 0xff);
	चयन (mode) अणु
	हाल AR5K_EEPROM_MODE_11A:
		ee->ee_ob[mode][3]	= (val >> 5) & 0x7;
		ee->ee_db[mode][3]	= (val >> 2) & 0x7;
		ee->ee_ob[mode][2]	= (val << 1) & 0x7;

		AR5K_EEPROM_READ(o++, val);
		ee->ee_ob[mode][2]	|= (val >> 15) & 0x1;
		ee->ee_db[mode][2]	= (val >> 12) & 0x7;
		ee->ee_ob[mode][1]	= (val >> 9) & 0x7;
		ee->ee_db[mode][1]	= (val >> 6) & 0x7;
		ee->ee_ob[mode][0]	= (val >> 3) & 0x7;
		ee->ee_db[mode][0]	= val & 0x7;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11G:
	हाल AR5K_EEPROM_MODE_11B:
		ee->ee_ob[mode][1]	= (val >> 4) & 0x7;
		ee->ee_db[mode][1]	= val & 0x7;
		अवरोध;
	पूर्ण

	AR5K_EEPROM_READ(o++, val);
	ee->ee_tx_end2xlna_enable[mode]	= (val >> 8) & 0xff;
	ee->ee_thr_62[mode]		= val & 0xff;

	अगर (ah->ah_ee_version <= AR5K_EEPROM_VERSION_3_2)
		ee->ee_thr_62[mode] = mode == AR5K_EEPROM_MODE_11A ? 15 : 28;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_tx_end2xpa_disable[mode]	= (val >> 8) & 0xff;
	ee->ee_tx_frm2xpa_enable[mode]	= val & 0xff;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_pga_desired_size[mode]	= (val >> 8) & 0xff;

	अगर ((val & 0xff) & 0x80)
		ee->ee_noise_न्यूनमान_thr[mode] = -((((val & 0xff) ^ 0xff)) + 1);
	अन्यथा
		ee->ee_noise_न्यूनमान_thr[mode] = val & 0xff;

	अगर (ah->ah_ee_version <= AR5K_EEPROM_VERSION_3_2)
		ee->ee_noise_न्यूनमान_thr[mode] =
		    mode == AR5K_EEPROM_MODE_11A ? -54 : -1;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_xlna_gain[mode]		= (val >> 5) & 0xff;
	ee->ee_x_gain[mode]		= (val >> 1) & 0xf;
	ee->ee_xpd[mode]		= val & 0x1;

	अगर (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_0 &&
	    mode != AR5K_EEPROM_MODE_11B)
		ee->ee_fixed_bias[mode] = (val >> 13) & 0x1;

	अगर (ah->ah_ee_version >= AR5K_EEPROM_VERSION_3_3) अणु
		AR5K_EEPROM_READ(o++, val);
		ee->ee_false_detect[mode] = (val >> 6) & 0x7f;

		अगर (mode == AR5K_EEPROM_MODE_11A)
			ee->ee_xr_घातer[mode] = val & 0x3f;
		अन्यथा अणु
			/* b_DB_11[bg] and b_OB_11[bg] */
			ee->ee_ob[mode][0] = val & 0x7;
			ee->ee_db[mode][0] = (val >> 3) & 0x7;
		पूर्ण
	पूर्ण

	अगर (ah->ah_ee_version < AR5K_EEPROM_VERSION_3_4) अणु
		ee->ee_i_gain[mode] = AR5K_EEPROM_I_GAIN;
		ee->ee_cck_ofdm_घातer_delta = AR5K_EEPROM_CCK_OFDM_DELTA;
	पूर्ण अन्यथा अणु
		ee->ee_i_gain[mode] = (val >> 13) & 0x7;

		AR5K_EEPROM_READ(o++, val);
		ee->ee_i_gain[mode] |= (val << 3) & 0x38;

		अगर (mode == AR5K_EEPROM_MODE_11G) अणु
			ee->ee_cck_ofdm_घातer_delta = (val >> 3) & 0xff;
			अगर (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_6)
				ee->ee_scaled_cck_delta = (val >> 11) & 0x1f;
		पूर्ण
	पूर्ण

	अगर (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_0 &&
			mode == AR5K_EEPROM_MODE_11A) अणु
		ee->ee_i_cal[mode] = (val >> 8) & 0x3f;
		ee->ee_q_cal[mode] = (val >> 3) & 0x1f;
	पूर्ण

	अगर (ah->ah_ee_version < AR5K_EEPROM_VERSION_4_0)
		जाओ करोne;

	/* Note: >= v5 have bg freq piers on another location
	 * so these freq piers are ignored क्रम >= v5 (should be 0xff
	 * anyway) */
	चयन (mode) अणु
	हाल AR5K_EEPROM_MODE_11A:
		अगर (ah->ah_ee_version < AR5K_EEPROM_VERSION_4_1)
			अवरोध;

		AR5K_EEPROM_READ(o++, val);
		ee->ee_margin_tx_rx[mode] = val & 0x3f;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11B:
		AR5K_EEPROM_READ(o++, val);

		ee->ee_pwr_cal_b[0].freq =
			ath5k_eeprom_bin2freq(ee, val & 0xff, mode);
		अगर (ee->ee_pwr_cal_b[0].freq != AR5K_EEPROM_CHANNEL_DIS)
			ee->ee_n_piers[mode]++;

		ee->ee_pwr_cal_b[1].freq =
			ath5k_eeprom_bin2freq(ee, (val >> 8) & 0xff, mode);
		अगर (ee->ee_pwr_cal_b[1].freq != AR5K_EEPROM_CHANNEL_DIS)
			ee->ee_n_piers[mode]++;

		AR5K_EEPROM_READ(o++, val);
		ee->ee_pwr_cal_b[2].freq =
			ath5k_eeprom_bin2freq(ee, val & 0xff, mode);
		अगर (ee->ee_pwr_cal_b[2].freq != AR5K_EEPROM_CHANNEL_DIS)
			ee->ee_n_piers[mode]++;

		अगर (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_1)
			ee->ee_margin_tx_rx[mode] = (val >> 8) & 0x3f;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11G:
		AR5K_EEPROM_READ(o++, val);

		ee->ee_pwr_cal_g[0].freq =
			ath5k_eeprom_bin2freq(ee, val & 0xff, mode);
		अगर (ee->ee_pwr_cal_g[0].freq != AR5K_EEPROM_CHANNEL_DIS)
			ee->ee_n_piers[mode]++;

		ee->ee_pwr_cal_g[1].freq =
			ath5k_eeprom_bin2freq(ee, (val >> 8) & 0xff, mode);
		अगर (ee->ee_pwr_cal_g[1].freq != AR5K_EEPROM_CHANNEL_DIS)
			ee->ee_n_piers[mode]++;

		AR5K_EEPROM_READ(o++, val);
		ee->ee_turbo_max_घातer[mode] = val & 0x7f;
		ee->ee_xr_घातer[mode] = (val >> 7) & 0x3f;

		AR5K_EEPROM_READ(o++, val);
		ee->ee_pwr_cal_g[2].freq =
			ath5k_eeprom_bin2freq(ee, val & 0xff, mode);
		अगर (ee->ee_pwr_cal_g[2].freq != AR5K_EEPROM_CHANNEL_DIS)
			ee->ee_n_piers[mode]++;

		अगर (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_1)
			ee->ee_margin_tx_rx[mode] = (val >> 8) & 0x3f;

		AR5K_EEPROM_READ(o++, val);
		ee->ee_i_cal[mode] = (val >> 5) & 0x3f;
		ee->ee_q_cal[mode] = val & 0x1f;

		अगर (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_2) अणु
			AR5K_EEPROM_READ(o++, val);
			ee->ee_cck_ofdm_gain_delta = val & 0xff;
		पूर्ण
		अवरोध;
	पूर्ण

	/*
	 * Read turbo mode inक्रमmation on newer EEPROM versions
	 */
	अगर (ee->ee_version < AR5K_EEPROM_VERSION_5_0)
		जाओ करोne;

	चयन (mode) अणु
	हाल AR5K_EEPROM_MODE_11A:
		ee->ee_चयन_settling_turbo[mode] = (val >> 6) & 0x7f;

		ee->ee_atn_tx_rx_turbo[mode] = (val >> 13) & 0x7;
		AR5K_EEPROM_READ(o++, val);
		ee->ee_atn_tx_rx_turbo[mode] |= (val & 0x7) << 3;
		ee->ee_margin_tx_rx_turbo[mode] = (val >> 3) & 0x3f;

		ee->ee_adc_desired_माप_प्रकारurbo[mode] = (val >> 9) & 0x7f;
		AR5K_EEPROM_READ(o++, val);
		ee->ee_adc_desired_माप_प्रकारurbo[mode] |= (val & 0x1) << 7;
		ee->ee_pga_desired_माप_प्रकारurbo[mode] = (val >> 1) & 0xff;

		अगर (AR5K_EEPROM_EEMAP(ee->ee_misc0) >= 2)
			ee->ee_pd_gain_overlap = (val >> 9) & 0xf;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11G:
		ee->ee_चयन_settling_turbo[mode] = (val >> 8) & 0x7f;

		ee->ee_atn_tx_rx_turbo[mode] = (val >> 15) & 0x7;
		AR5K_EEPROM_READ(o++, val);
		ee->ee_atn_tx_rx_turbo[mode] |= (val & 0x1f) << 1;
		ee->ee_margin_tx_rx_turbo[mode] = (val >> 5) & 0x3f;

		ee->ee_adc_desired_माप_प्रकारurbo[mode] = (val >> 11) & 0x7f;
		AR5K_EEPROM_READ(o++, val);
		ee->ee_adc_desired_माप_प्रकारurbo[mode] |= (val & 0x7) << 5;
		ee->ee_pga_desired_माप_प्रकारurbo[mode] = (val >> 3) & 0xff;
		अवरोध;
	पूर्ण

करोne:
	/* वापस new offset */
	*offset = o;

	वापस 0;
पूर्ण

/* Read mode-specअगरic data (except घातer calibration data) */
अटल पूर्णांक
ath5k_eeprom_init_modes(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u32 mode_offset[3];
	अचिन्हित पूर्णांक mode;
	u32 offset;
	पूर्णांक ret;

	/*
	 * Get values क्रम all modes
	 */
	mode_offset[AR5K_EEPROM_MODE_11A] = AR5K_EEPROM_MODES_11A(ah->ah_ee_version);
	mode_offset[AR5K_EEPROM_MODE_11B] = AR5K_EEPROM_MODES_11B(ah->ah_ee_version);
	mode_offset[AR5K_EEPROM_MODE_11G] = AR5K_EEPROM_MODES_11G(ah->ah_ee_version);

	ee->ee_turbo_max_घातer[AR5K_EEPROM_MODE_11A] =
		AR5K_EEPROM_HDR_T_5GHZ_DBM(ee->ee_header);

	क्रम (mode = AR5K_EEPROM_MODE_11A; mode <= AR5K_EEPROM_MODE_11G; mode++) अणु
		offset = mode_offset[mode];

		ret = ath5k_eeprom_पढ़ो_ants(ah, &offset, mode);
		अगर (ret)
			वापस ret;

		ret = ath5k_eeprom_पढ़ो_modes(ah, &offset, mode);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* override क्रम older eeprom versions क्रम better perक्रमmance */
	अगर (ah->ah_ee_version <= AR5K_EEPROM_VERSION_3_2) अणु
		ee->ee_thr_62[AR5K_EEPROM_MODE_11A] = 15;
		ee->ee_thr_62[AR5K_EEPROM_MODE_11B] = 28;
		ee->ee_thr_62[AR5K_EEPROM_MODE_11G] = 28;
	पूर्ण

	वापस 0;
पूर्ण

/* Read the frequency piers क्रम each mode (mostly used on newer eeproms with 0xff
 * frequency mask) */
अटल अंतरभूत पूर्णांक
ath5k_eeprom_पढ़ो_freq_list(काष्ठा ath5k_hw *ah, पूर्णांक *offset, पूर्णांक max,
			काष्ठा ath5k_chan_pcal_info *pc, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	पूर्णांक o = *offset;
	पूर्णांक i = 0;
	u8 freq1, freq2;
	u16 val;

	ee->ee_n_piers[mode] = 0;
	जबतक (i < max) अणु
		AR5K_EEPROM_READ(o++, val);

		freq1 = val & 0xff;
		अगर (!freq1)
			अवरोध;

		pc[i++].freq = ath5k_eeprom_bin2freq(ee,
				freq1, mode);
		ee->ee_n_piers[mode]++;

		freq2 = (val >> 8) & 0xff;
		अगर (!freq2)
			अवरोध;

		pc[i++].freq = ath5k_eeprom_bin2freq(ee,
				freq2, mode);
		ee->ee_n_piers[mode]++;
	पूर्ण

	/* वापस new offset */
	*offset = o;

	वापस 0;
पूर्ण

/* Read frequency piers क्रम 802.11a */
अटल पूर्णांक
ath5k_eeprom_init_11a_pcal_freq(काष्ठा ath5k_hw *ah, पूर्णांक offset)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	काष्ठा ath5k_chan_pcal_info *pcal = ee->ee_pwr_cal_a;
	पूर्णांक i;
	u16 val;
	u8 mask;

	अगर (ee->ee_version >= AR5K_EEPROM_VERSION_3_3) अणु
		ath5k_eeprom_पढ़ो_freq_list(ah, &offset,
			AR5K_EEPROM_N_5GHZ_CHAN, pcal,
			AR5K_EEPROM_MODE_11A);
	पूर्ण अन्यथा अणु
		mask = AR5K_EEPROM_FREQ_M(ah->ah_ee_version);

		AR5K_EEPROM_READ(offset++, val);
		pcal[0].freq  = (val >> 9) & mask;
		pcal[1].freq  = (val >> 2) & mask;
		pcal[2].freq  = (val << 5) & mask;

		AR5K_EEPROM_READ(offset++, val);
		pcal[2].freq |= (val >> 11) & 0x1f;
		pcal[3].freq  = (val >> 4) & mask;
		pcal[4].freq  = (val << 3) & mask;

		AR5K_EEPROM_READ(offset++, val);
		pcal[4].freq |= (val >> 13) & 0x7;
		pcal[5].freq  = (val >> 6) & mask;
		pcal[6].freq  = (val << 1) & mask;

		AR5K_EEPROM_READ(offset++, val);
		pcal[6].freq |= (val >> 15) & 0x1;
		pcal[7].freq  = (val >> 8) & mask;
		pcal[8].freq  = (val >> 1) & mask;
		pcal[9].freq  = (val << 6) & mask;

		AR5K_EEPROM_READ(offset++, val);
		pcal[9].freq |= (val >> 10) & 0x3f;

		/* Fixed number of piers */
		ee->ee_n_piers[AR5K_EEPROM_MODE_11A] = 10;

		क्रम (i = 0; i < AR5K_EEPROM_N_5GHZ_CHAN; i++) अणु
			pcal[i].freq = ath5k_eeprom_bin2freq(ee,
				pcal[i].freq, AR5K_EEPROM_MODE_11A);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Read frequency piers क्रम 802.11bg on eeprom versions >= 5 and eemap >= 2 */
अटल अंतरभूत पूर्णांक
ath5k_eeprom_init_11bg_2413(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक mode, पूर्णांक offset)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	काष्ठा ath5k_chan_pcal_info *pcal;

	चयन (mode) अणु
	हाल AR5K_EEPROM_MODE_11B:
		pcal = ee->ee_pwr_cal_b;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11G:
		pcal = ee->ee_pwr_cal_g;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ath5k_eeprom_पढ़ो_freq_list(ah, &offset,
		AR5K_EEPROM_N_2GHZ_CHAN_2413, pcal,
		mode);

	वापस 0;
पूर्ण


/*
 * Read घातer calibration क्रम RF5111 chips
 *
 * For RF5111 we have an XPD -eXternal Power Detector- curve
 * क्रम each calibrated channel. Each curve has 0,5dB Power steps
 * on x axis and PCDAC steps (offsets) on y axis and looks like an
 * exponential function. To recreate the curve we पढ़ो 11 poपूर्णांकs
 * here and पूर्णांकerpolate later.
 */

/* Used to match PCDAC steps with घातer values on RF5111 chips
 * (eeprom versions < 4). For RF5111 we have 11 pre-defined PCDAC
 * steps that match with the घातer values we पढ़ो from eeprom. On
 * older eeprom versions (< 3.2) these steps are equally spaced at
 * 10% of the pcdac curve -until the curve reaches its maximum-
 * (11 steps from 0 to 100%) but on newer eeprom versions (>= 3.2)
 * these 11 steps are spaced in a dअगरferent way. This function वापसs
 * the pcdac steps based on eeprom version and curve min/max so that we
 * can have pcdac/pwr poपूर्णांकs.
 */
अटल अंतरभूत व्योम
ath5k_get_pcdac_पूर्णांकercepts(काष्ठा ath5k_hw *ah, u8 min, u8 max, u8 *vp)
अणु
	अटल स्थिर u16 पूर्णांकercepts3[] = अणु
		0, 5, 10, 20, 30, 50, 70, 85, 90, 95, 100
	पूर्ण;
	अटल स्थिर u16 पूर्णांकercepts3_2[] = अणु
		0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
	पूर्ण;
	स्थिर u16 *ip;
	पूर्णांक i;

	अगर (ah->ah_ee_version >= AR5K_EEPROM_VERSION_3_2)
		ip = पूर्णांकercepts3_2;
	अन्यथा
		ip = पूर्णांकercepts3;

	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांकercepts3); i++)
		vp[i] = (ip[i] * max + (100 - ip[i]) * min) / 100;
पूर्ण

अटल पूर्णांक
ath5k_eeprom_मुक्त_pcal_info(काष्ठा ath5k_hw *ah, पूर्णांक mode)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	काष्ठा ath5k_chan_pcal_info *chinfo;
	u8 pier, pdg;

	चयन (mode) अणु
	हाल AR5K_EEPROM_MODE_11A:
		अगर (!AR5K_EEPROM_HDR_11A(ee->ee_header))
			वापस 0;
		chinfo = ee->ee_pwr_cal_a;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11B:
		अगर (!AR5K_EEPROM_HDR_11B(ee->ee_header))
			वापस 0;
		chinfo = ee->ee_pwr_cal_b;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11G:
		अगर (!AR5K_EEPROM_HDR_11G(ee->ee_header))
			वापस 0;
		chinfo = ee->ee_pwr_cal_g;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (pier = 0; pier < ee->ee_n_piers[mode]; pier++) अणु
		अगर (!chinfo[pier].pd_curves)
			जारी;

		क्रम (pdg = 0; pdg < AR5K_EEPROM_N_PD_CURVES; pdg++) अणु
			काष्ठा ath5k_pdgain_info *pd =
					&chinfo[pier].pd_curves[pdg];

			kमुक्त(pd->pd_step);
			kमुक्त(pd->pd_pwr);
		पूर्ण

		kमुक्त(chinfo[pier].pd_curves);
	पूर्ण

	वापस 0;
पूर्ण

/* Convert RF5111 specअगरic data to generic raw data
 * used by पूर्णांकerpolation code */
अटल पूर्णांक
ath5k_eeprom_convert_pcal_info_5111(काष्ठा ath5k_hw *ah, पूर्णांक mode,
				काष्ठा ath5k_chan_pcal_info *chinfo)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	काष्ठा ath5k_chan_pcal_info_rf5111 *pcinfo;
	काष्ठा ath5k_pdgain_info *pd;
	u8 pier, poपूर्णांक, idx;
	u8 *pdgain_idx = ee->ee_pdc_to_idx[mode];

	/* Fill raw data क्रम each calibration pier */
	क्रम (pier = 0; pier < ee->ee_n_piers[mode]; pier++) अणु

		pcinfo = &chinfo[pier].rf5111_info;

		/* Allocate pd_curves क्रम this cal pier */
		chinfo[pier].pd_curves =
			kसुस्मृति(AR5K_EEPROM_N_PD_CURVES,
				माप(काष्ठा ath5k_pdgain_info),
				GFP_KERNEL);

		अगर (!chinfo[pier].pd_curves)
			जाओ err_out;

		/* Only one curve क्रम RF5111
		 * find out which one and place
		 * in pd_curves.
		 * Note: ee_x_gain is reversed here */
		क्रम (idx = 0; idx < AR5K_EEPROM_N_PD_CURVES; idx++) अणु

			अगर (!((ee->ee_x_gain[mode] >> idx) & 0x1)) अणु
				pdgain_idx[0] = idx;
				अवरोध;
			पूर्ण
		पूर्ण

		ee->ee_pd_gains[mode] = 1;

		pd = &chinfo[pier].pd_curves[idx];

		pd->pd_poपूर्णांकs = AR5K_EEPROM_N_PWR_POINTS_5111;

		/* Allocate pd poपूर्णांकs क्रम this curve */
		pd->pd_step = kसुस्मृति(AR5K_EEPROM_N_PWR_POINTS_5111,
					माप(u8), GFP_KERNEL);
		अगर (!pd->pd_step)
			जाओ err_out;

		pd->pd_pwr = kसुस्मृति(AR5K_EEPROM_N_PWR_POINTS_5111,
					माप(s16), GFP_KERNEL);
		अगर (!pd->pd_pwr)
			जाओ err_out;

		/* Fill raw dataset
		 * (convert घातer to 0.25dB units
		 * क्रम RF5112 compatibility) */
		क्रम (poपूर्णांक = 0; poपूर्णांक < pd->pd_poपूर्णांकs; poपूर्णांक++) अणु

			/* Absolute values */
			pd->pd_pwr[poपूर्णांक] = 2 * pcinfo->pwr[poपूर्णांक];

			/* Alपढ़ोy sorted */
			pd->pd_step[poपूर्णांक] = pcinfo->pcdac[poपूर्णांक];
		पूर्ण

		/* Set min/max pwr */
		chinfo[pier].min_pwr = pd->pd_pwr[0];
		chinfo[pier].max_pwr = pd->pd_pwr[10];

	पूर्ण

	वापस 0;

err_out:
	ath5k_eeprom_मुक्त_pcal_info(ah, mode);
	वापस -ENOMEM;
पूर्ण

/* Parse EEPROM data */
अटल पूर्णांक
ath5k_eeprom_पढ़ो_pcal_info_5111(काष्ठा ath5k_hw *ah, पूर्णांक mode)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	काष्ठा ath5k_chan_pcal_info *pcal;
	पूर्णांक offset, ret;
	पूर्णांक i;
	u16 val;

	offset = AR5K_EEPROM_GROUPS_START(ee->ee_version);
	चयन (mode) अणु
	हाल AR5K_EEPROM_MODE_11A:
		अगर (!AR5K_EEPROM_HDR_11A(ee->ee_header))
			वापस 0;

		ret = ath5k_eeprom_init_11a_pcal_freq(ah,
			offset + AR5K_EEPROM_GROUP1_OFFSET);
		अगर (ret < 0)
			वापस ret;

		offset += AR5K_EEPROM_GROUP2_OFFSET;
		pcal = ee->ee_pwr_cal_a;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11B:
		अगर (!AR5K_EEPROM_HDR_11B(ee->ee_header) &&
		    !AR5K_EEPROM_HDR_11G(ee->ee_header))
			वापस 0;

		pcal = ee->ee_pwr_cal_b;
		offset += AR5K_EEPROM_GROUP3_OFFSET;

		/* fixed piers */
		pcal[0].freq = 2412;
		pcal[1].freq = 2447;
		pcal[2].freq = 2484;
		ee->ee_n_piers[mode] = 3;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11G:
		अगर (!AR5K_EEPROM_HDR_11G(ee->ee_header))
			वापस 0;

		pcal = ee->ee_pwr_cal_g;
		offset += AR5K_EEPROM_GROUP4_OFFSET;

		/* fixed piers */
		pcal[0].freq = 2312;
		pcal[1].freq = 2412;
		pcal[2].freq = 2484;
		ee->ee_n_piers[mode] = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ee->ee_n_piers[mode]; i++) अणु
		काष्ठा ath5k_chan_pcal_info_rf5111 *cdata =
			&pcal[i].rf5111_info;

		AR5K_EEPROM_READ(offset++, val);
		cdata->pcdac_max = ((val >> 10) & AR5K_EEPROM_PCDAC_M);
		cdata->pcdac_min = ((val >> 4) & AR5K_EEPROM_PCDAC_M);
		cdata->pwr[0] = ((val << 2) & AR5K_EEPROM_POWER_M);

		AR5K_EEPROM_READ(offset++, val);
		cdata->pwr[0] |= ((val >> 14) & 0x3);
		cdata->pwr[1] = ((val >> 8) & AR5K_EEPROM_POWER_M);
		cdata->pwr[2] = ((val >> 2) & AR5K_EEPROM_POWER_M);
		cdata->pwr[3] = ((val << 4) & AR5K_EEPROM_POWER_M);

		AR5K_EEPROM_READ(offset++, val);
		cdata->pwr[3] |= ((val >> 12) & 0xf);
		cdata->pwr[4] = ((val >> 6) & AR5K_EEPROM_POWER_M);
		cdata->pwr[5] = (val  & AR5K_EEPROM_POWER_M);

		AR5K_EEPROM_READ(offset++, val);
		cdata->pwr[6] = ((val >> 10) & AR5K_EEPROM_POWER_M);
		cdata->pwr[7] = ((val >> 4) & AR5K_EEPROM_POWER_M);
		cdata->pwr[8] = ((val << 2) & AR5K_EEPROM_POWER_M);

		AR5K_EEPROM_READ(offset++, val);
		cdata->pwr[8] |= ((val >> 14) & 0x3);
		cdata->pwr[9] = ((val >> 8) & AR5K_EEPROM_POWER_M);
		cdata->pwr[10] = ((val >> 2) & AR5K_EEPROM_POWER_M);

		ath5k_get_pcdac_पूर्णांकercepts(ah, cdata->pcdac_min,
			cdata->pcdac_max, cdata->pcdac);
	पूर्ण

	वापस ath5k_eeprom_convert_pcal_info_5111(ah, mode, pcal);
पूर्ण


/*
 * Read घातer calibration क्रम RF5112 chips
 *
 * For RF5112 we have 4 XPD -eXternal Power Detector- curves
 * क्रम each calibrated channel on 0, -6, -12 and -18dBm but we only
 * use the higher (3) and the lower (0) curves. Each curve has 0.5dB
 * घातer steps on x axis and PCDAC steps on y axis and looks like a
 * linear function. To recreate the curve and pass the घातer values
 * on hw, we पढ़ो 4 poपूर्णांकs क्रम xpd 0 (lower gain -> max घातer)
 * and 3 poपूर्णांकs क्रम xpd 3 (higher gain -> lower घातer) here and
 * पूर्णांकerpolate later.
 *
 * Note: Many venकरोrs just use xpd 0 so xpd 3 is zeroed.
 */

/* Convert RF5112 specअगरic data to generic raw data
 * used by पूर्णांकerpolation code */
अटल पूर्णांक
ath5k_eeprom_convert_pcal_info_5112(काष्ठा ath5k_hw *ah, पूर्णांक mode,
				काष्ठा ath5k_chan_pcal_info *chinfo)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	काष्ठा ath5k_chan_pcal_info_rf5112 *pcinfo;
	u8 *pdgain_idx = ee->ee_pdc_to_idx[mode];
	अचिन्हित पूर्णांक pier, pdg, poपूर्णांक;

	/* Fill raw data क्रम each calibration pier */
	क्रम (pier = 0; pier < ee->ee_n_piers[mode]; pier++) अणु

		pcinfo = &chinfo[pier].rf5112_info;

		/* Allocate pd_curves क्रम this cal pier */
		chinfo[pier].pd_curves =
				kसुस्मृति(AR5K_EEPROM_N_PD_CURVES,
					माप(काष्ठा ath5k_pdgain_info),
					GFP_KERNEL);

		अगर (!chinfo[pier].pd_curves)
			जाओ err_out;

		/* Fill pd_curves */
		क्रम (pdg = 0; pdg < ee->ee_pd_gains[mode]; pdg++) अणु

			u8 idx = pdgain_idx[pdg];
			काष्ठा ath5k_pdgain_info *pd =
					&chinfo[pier].pd_curves[idx];

			/* Lowest gain curve (max घातer) */
			अगर (pdg == 0) अणु
				/* One more poपूर्णांक क्रम better accuracy */
				pd->pd_poपूर्णांकs = AR5K_EEPROM_N_XPD0_POINTS;

				/* Allocate pd poपूर्णांकs क्रम this curve */
				pd->pd_step = kसुस्मृति(pd->pd_poपूर्णांकs,
						माप(u8), GFP_KERNEL);

				अगर (!pd->pd_step)
					जाओ err_out;

				pd->pd_pwr = kसुस्मृति(pd->pd_poपूर्णांकs,
						माप(s16), GFP_KERNEL);

				अगर (!pd->pd_pwr)
					जाओ err_out;

				/* Fill raw dataset
				 * (all घातer levels are in 0.25dB units) */
				pd->pd_step[0] = pcinfo->pcdac_x0[0];
				pd->pd_pwr[0] = pcinfo->pwr_x0[0];

				क्रम (poपूर्णांक = 1; poपूर्णांक < pd->pd_poपूर्णांकs;
				poपूर्णांक++) अणु
					/* Absolute values */
					pd->pd_pwr[poपूर्णांक] =
						pcinfo->pwr_x0[poपूर्णांक];

					/* Deltas */
					pd->pd_step[poपूर्णांक] =
						pd->pd_step[poपूर्णांक - 1] +
						pcinfo->pcdac_x0[poपूर्णांक];
				पूर्ण

				/* Set min घातer क्रम this frequency */
				chinfo[pier].min_pwr = pd->pd_pwr[0];

			/* Highest gain curve (min घातer) */
			पूर्ण अन्यथा अगर (pdg == 1) अणु

				pd->pd_poपूर्णांकs = AR5K_EEPROM_N_XPD3_POINTS;

				/* Allocate pd poपूर्णांकs क्रम this curve */
				pd->pd_step = kसुस्मृति(pd->pd_poपूर्णांकs,
						माप(u8), GFP_KERNEL);

				अगर (!pd->pd_step)
					जाओ err_out;

				pd->pd_pwr = kसुस्मृति(pd->pd_poपूर्णांकs,
						माप(s16), GFP_KERNEL);

				अगर (!pd->pd_pwr)
					जाओ err_out;

				/* Fill raw dataset
				 * (all घातer levels are in 0.25dB units) */
				क्रम (poपूर्णांक = 0; poपूर्णांक < pd->pd_poपूर्णांकs;
				poपूर्णांक++) अणु
					/* Absolute values */
					pd->pd_pwr[poपूर्णांक] =
						pcinfo->pwr_x3[poपूर्णांक];

					/* Fixed poपूर्णांकs */
					pd->pd_step[poपूर्णांक] =
						pcinfo->pcdac_x3[poपूर्णांक];
				पूर्ण

				/* Since we have a higher gain curve
				 * override min घातer */
				chinfo[pier].min_pwr = pd->pd_pwr[0];
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

err_out:
	ath5k_eeprom_मुक्त_pcal_info(ah, mode);
	वापस -ENOMEM;
पूर्ण

/* Parse EEPROM data */
अटल पूर्णांक
ath5k_eeprom_पढ़ो_pcal_info_5112(काष्ठा ath5k_hw *ah, पूर्णांक mode)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	काष्ठा ath5k_chan_pcal_info_rf5112 *chan_pcal_info;
	काष्ठा ath5k_chan_pcal_info *gen_chan_info;
	u8 *pdgain_idx = ee->ee_pdc_to_idx[mode];
	u32 offset;
	u8 i, c;
	u16 val;
	u8 pd_gains = 0;

	/* Count how many curves we have and
	 * identअगरy them (which one of the 4
	 * available curves we have on each count).
	 * Curves are stored from lower (x0) to
	 * higher (x3) gain */
	क्रम (i = 0; i < AR5K_EEPROM_N_PD_CURVES; i++) अणु
		/* ee_x_gain[mode] is x gain mask */
		अगर ((ee->ee_x_gain[mode] >> i) & 0x1)
			pdgain_idx[pd_gains++] = i;
	पूर्ण
	ee->ee_pd_gains[mode] = pd_gains;

	अगर (pd_gains == 0 || pd_gains > 2)
		वापस -EINVAL;

	चयन (mode) अणु
	हाल AR5K_EEPROM_MODE_11A:
		/*
		 * Read 5GHz EEPROM channels
		 */
		offset = AR5K_EEPROM_GROUPS_START(ee->ee_version);
		ath5k_eeprom_init_11a_pcal_freq(ah, offset);

		offset += AR5K_EEPROM_GROUP2_OFFSET;
		gen_chan_info = ee->ee_pwr_cal_a;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11B:
		offset = AR5K_EEPROM_GROUPS_START(ee->ee_version);
		अगर (AR5K_EEPROM_HDR_11A(ee->ee_header))
			offset += AR5K_EEPROM_GROUP3_OFFSET;

		/* NB: frequency piers parsed during mode init */
		gen_chan_info = ee->ee_pwr_cal_b;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11G:
		offset = AR5K_EEPROM_GROUPS_START(ee->ee_version);
		अगर (AR5K_EEPROM_HDR_11A(ee->ee_header))
			offset += AR5K_EEPROM_GROUP4_OFFSET;
		अन्यथा अगर (AR5K_EEPROM_HDR_11B(ee->ee_header))
			offset += AR5K_EEPROM_GROUP2_OFFSET;

		/* NB: frequency piers parsed during mode init */
		gen_chan_info = ee->ee_pwr_cal_g;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ee->ee_n_piers[mode]; i++) अणु
		chan_pcal_info = &gen_chan_info[i].rf5112_info;

		/* Power values in quarter dB
		 * क्रम the lower xpd gain curve
		 * (0 dBm -> higher output घातer) */
		क्रम (c = 0; c < AR5K_EEPROM_N_XPD0_POINTS; c++) अणु
			AR5K_EEPROM_READ(offset++, val);
			chan_pcal_info->pwr_x0[c] = (s8) (val & 0xff);
			chan_pcal_info->pwr_x0[++c] = (s8) ((val >> 8) & 0xff);
		पूर्ण

		/* PCDAC steps
		 * corresponding to the above घातer
		 * measurements */
		AR5K_EEPROM_READ(offset++, val);
		chan_pcal_info->pcdac_x0[1] = (val & 0x1f);
		chan_pcal_info->pcdac_x0[2] = ((val >> 5) & 0x1f);
		chan_pcal_info->pcdac_x0[3] = ((val >> 10) & 0x1f);

		/* Power values in quarter dB
		 * क्रम the higher xpd gain curve
		 * (18 dBm -> lower output घातer) */
		AR5K_EEPROM_READ(offset++, val);
		chan_pcal_info->pwr_x3[0] = (s8) (val & 0xff);
		chan_pcal_info->pwr_x3[1] = (s8) ((val >> 8) & 0xff);

		AR5K_EEPROM_READ(offset++, val);
		chan_pcal_info->pwr_x3[2] = (val & 0xff);

		/* PCDAC steps
		 * corresponding to the above घातer
		 * measurements (fixed) */
		chan_pcal_info->pcdac_x3[0] = 20;
		chan_pcal_info->pcdac_x3[1] = 35;
		chan_pcal_info->pcdac_x3[2] = 63;

		अगर (ee->ee_version >= AR5K_EEPROM_VERSION_4_3) अणु
			chan_pcal_info->pcdac_x0[0] = ((val >> 8) & 0x3f);

			/* Last xpd0 घातer level is also channel maximum */
			gen_chan_info[i].max_pwr = chan_pcal_info->pwr_x0[3];
		पूर्ण अन्यथा अणु
			chan_pcal_info->pcdac_x0[0] = 1;
			gen_chan_info[i].max_pwr = (s8) ((val >> 8) & 0xff);
		पूर्ण

	पूर्ण

	वापस ath5k_eeprom_convert_pcal_info_5112(ah, mode, gen_chan_info);
पूर्ण


/*
 * Read घातer calibration क्रम RF2413 chips
 *
 * For RF2413 we have a Power to PDDAC table (Power Detector)
 * instead of a PCDAC and 4 pd gain curves क्रम each calibrated channel.
 * Each curve has घातer on x axis in 0.5 db steps and PDDADC steps on y
 * axis and looks like an exponential function like the RF5111 curve.
 *
 * To recreate the curves we पढ़ो here the poपूर्णांकs and पूर्णांकerpolate
 * later. Note that in most हालs only 2 (higher and lower) curves are
 * used (like RF5112) but venकरोrs have the opportunity to include all
 * 4 curves on eeprom. The final curve (higher घातer) has an extra
 * poपूर्णांक क्रम better accuracy like RF5112.
 */

/* For RF2413 घातer calibration data करोesn't start on a fixed location and
 * अगर a mode is not supported, its section is missing -not zeroed-.
 * So we need to calculate the starting offset क्रम each section by using
 * these two functions */

/* Return the size of each section based on the mode and the number of pd
 * gains available (maximum 4). */
अटल अंतरभूत अचिन्हित पूर्णांक
ath5k_pdgains_size_2413(काष्ठा ath5k_eeprom_info *ee, अचिन्हित पूर्णांक mode)
अणु
	अटल स्थिर अचिन्हित पूर्णांक pdgains_size[] = अणु 4, 6, 9, 12 पूर्ण;
	अचिन्हित पूर्णांक sz;

	sz = pdgains_size[ee->ee_pd_gains[mode] - 1];
	sz *= ee->ee_n_piers[mode];

	वापस sz;
पूर्ण

/* Return the starting offset क्रम a section based on the modes supported
 * and each section's size. */
अटल अचिन्हित पूर्णांक
ath5k_cal_data_offset_2413(काष्ठा ath5k_eeprom_info *ee, पूर्णांक mode)
अणु
	u32 offset = AR5K_EEPROM_CAL_DATA_START(ee->ee_misc4);

	चयन (mode) अणु
	हाल AR5K_EEPROM_MODE_11G:
		अगर (AR5K_EEPROM_HDR_11B(ee->ee_header))
			offset += ath5k_pdgains_size_2413(ee,
					AR5K_EEPROM_MODE_11B) +
					AR5K_EEPROM_N_2GHZ_CHAN_2413 / 2;
		fallthrough;
	हाल AR5K_EEPROM_MODE_11B:
		अगर (AR5K_EEPROM_HDR_11A(ee->ee_header))
			offset += ath5k_pdgains_size_2413(ee,
					AR5K_EEPROM_MODE_11A) +
					AR5K_EEPROM_N_5GHZ_CHAN / 2;
		fallthrough;
	हाल AR5K_EEPROM_MODE_11A:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस offset;
पूर्ण

/* Convert RF2413 specअगरic data to generic raw data
 * used by पूर्णांकerpolation code */
अटल पूर्णांक
ath5k_eeprom_convert_pcal_info_2413(काष्ठा ath5k_hw *ah, पूर्णांक mode,
				काष्ठा ath5k_chan_pcal_info *chinfo)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	काष्ठा ath5k_chan_pcal_info_rf2413 *pcinfo;
	u8 *pdgain_idx = ee->ee_pdc_to_idx[mode];
	अचिन्हित पूर्णांक pier, pdg, poपूर्णांक;

	/* Fill raw data क्रम each calibration pier */
	क्रम (pier = 0; pier < ee->ee_n_piers[mode]; pier++) अणु

		pcinfo = &chinfo[pier].rf2413_info;

		/* Allocate pd_curves क्रम this cal pier */
		chinfo[pier].pd_curves =
				kसुस्मृति(AR5K_EEPROM_N_PD_CURVES,
					माप(काष्ठा ath5k_pdgain_info),
					GFP_KERNEL);

		अगर (!chinfo[pier].pd_curves)
			जाओ err_out;

		/* Fill pd_curves */
		क्रम (pdg = 0; pdg < ee->ee_pd_gains[mode]; pdg++) अणु

			u8 idx = pdgain_idx[pdg];
			काष्ठा ath5k_pdgain_info *pd =
					&chinfo[pier].pd_curves[idx];

			/* One more poपूर्णांक क्रम the highest घातer
			 * curve (lowest gain) */
			अगर (pdg == ee->ee_pd_gains[mode] - 1)
				pd->pd_poपूर्णांकs = AR5K_EEPROM_N_PD_POINTS;
			अन्यथा
				pd->pd_poपूर्णांकs = AR5K_EEPROM_N_PD_POINTS - 1;

			/* Allocate pd poपूर्णांकs क्रम this curve */
			pd->pd_step = kसुस्मृति(pd->pd_poपूर्णांकs,
					माप(u8), GFP_KERNEL);

			अगर (!pd->pd_step)
				जाओ err_out;

			pd->pd_pwr = kसुस्मृति(pd->pd_poपूर्णांकs,
					माप(s16), GFP_KERNEL);

			अगर (!pd->pd_pwr)
				जाओ err_out;

			/* Fill raw dataset
			 * convert all pwr levels to
			 * quarter dB क्रम RF5112 compatibility */
			pd->pd_step[0] = pcinfo->pddac_i[pdg];
			pd->pd_pwr[0] = 4 * pcinfo->pwr_i[pdg];

			क्रम (poपूर्णांक = 1; poपूर्णांक < pd->pd_poपूर्णांकs; poपूर्णांक++) अणु

				pd->pd_pwr[poपूर्णांक] = pd->pd_pwr[poपूर्णांक - 1] +
					2 * pcinfo->pwr[pdg][poपूर्णांक - 1];

				pd->pd_step[poपूर्णांक] = pd->pd_step[poपूर्णांक - 1] +
						pcinfo->pddac[pdg][poपूर्णांक - 1];

			पूर्ण

			/* Highest gain curve -> min घातer */
			अगर (pdg == 0)
				chinfo[pier].min_pwr = pd->pd_pwr[0];

			/* Lowest gain curve -> max घातer */
			अगर (pdg == ee->ee_pd_gains[mode] - 1)
				chinfo[pier].max_pwr =
					pd->pd_pwr[pd->pd_poपूर्णांकs - 1];
		पूर्ण
	पूर्ण

	वापस 0;

err_out:
	ath5k_eeprom_मुक्त_pcal_info(ah, mode);
	वापस -ENOMEM;
पूर्ण

/* Parse EEPROM data */
अटल पूर्णांक
ath5k_eeprom_पढ़ो_pcal_info_2413(काष्ठा ath5k_hw *ah, पूर्णांक mode)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	काष्ठा ath5k_chan_pcal_info_rf2413 *pcinfo;
	काष्ठा ath5k_chan_pcal_info *chinfo;
	u8 *pdgain_idx = ee->ee_pdc_to_idx[mode];
	u32 offset;
	पूर्णांक idx, i;
	u16 val;
	u8 pd_gains = 0;

	/* Count how many curves we have and
	 * identअगरy them (which one of the 4
	 * available curves we have on each count).
	 * Curves are stored from higher to
	 * lower gain so we go backwards */
	क्रम (idx = AR5K_EEPROM_N_PD_CURVES - 1; idx >= 0; idx--) अणु
		/* ee_x_gain[mode] is x gain mask */
		अगर ((ee->ee_x_gain[mode] >> idx) & 0x1)
			pdgain_idx[pd_gains++] = idx;

	पूर्ण
	ee->ee_pd_gains[mode] = pd_gains;

	अगर (pd_gains == 0)
		वापस -EINVAL;

	offset = ath5k_cal_data_offset_2413(ee, mode);
	चयन (mode) अणु
	हाल AR5K_EEPROM_MODE_11A:
		अगर (!AR5K_EEPROM_HDR_11A(ee->ee_header))
			वापस 0;

		ath5k_eeprom_init_11a_pcal_freq(ah, offset);
		offset += AR5K_EEPROM_N_5GHZ_CHAN / 2;
		chinfo = ee->ee_pwr_cal_a;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11B:
		अगर (!AR5K_EEPROM_HDR_11B(ee->ee_header))
			वापस 0;

		ath5k_eeprom_init_11bg_2413(ah, mode, offset);
		offset += AR5K_EEPROM_N_2GHZ_CHAN_2413 / 2;
		chinfo = ee->ee_pwr_cal_b;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11G:
		अगर (!AR5K_EEPROM_HDR_11G(ee->ee_header))
			वापस 0;

		ath5k_eeprom_init_11bg_2413(ah, mode, offset);
		offset += AR5K_EEPROM_N_2GHZ_CHAN_2413 / 2;
		chinfo = ee->ee_pwr_cal_g;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ee->ee_n_piers[mode]; i++) अणु
		pcinfo = &chinfo[i].rf2413_info;

		/*
		 * Read pwr_i, pddac_i and the first
		 * 2 pd poपूर्णांकs (pwr, pddac)
		 */
		AR5K_EEPROM_READ(offset++, val);
		pcinfo->pwr_i[0] = val & 0x1f;
		pcinfo->pddac_i[0] = (val >> 5) & 0x7f;
		pcinfo->pwr[0][0] = (val >> 12) & 0xf;

		AR5K_EEPROM_READ(offset++, val);
		pcinfo->pddac[0][0] = val & 0x3f;
		pcinfo->pwr[0][1] = (val >> 6) & 0xf;
		pcinfo->pddac[0][1] = (val >> 10) & 0x3f;

		AR5K_EEPROM_READ(offset++, val);
		pcinfo->pwr[0][2] = val & 0xf;
		pcinfo->pddac[0][2] = (val >> 4) & 0x3f;

		pcinfo->pwr[0][3] = 0;
		pcinfo->pddac[0][3] = 0;

		अगर (pd_gains > 1) अणु
			/*
			 * Pd gain 0 is not the last pd gain
			 * so it only has 2 pd poपूर्णांकs.
			 * Continue with pd gain 1.
			 */
			pcinfo->pwr_i[1] = (val >> 10) & 0x1f;

			pcinfo->pddac_i[1] = (val >> 15) & 0x1;
			AR5K_EEPROM_READ(offset++, val);
			pcinfo->pddac_i[1] |= (val & 0x3F) << 1;

			pcinfo->pwr[1][0] = (val >> 6) & 0xf;
			pcinfo->pddac[1][0] = (val >> 10) & 0x3f;

			AR5K_EEPROM_READ(offset++, val);
			pcinfo->pwr[1][1] = val & 0xf;
			pcinfo->pddac[1][1] = (val >> 4) & 0x3f;
			pcinfo->pwr[1][2] = (val >> 10) & 0xf;

			pcinfo->pddac[1][2] = (val >> 14) & 0x3;
			AR5K_EEPROM_READ(offset++, val);
			pcinfo->pddac[1][2] |= (val & 0xF) << 2;

			pcinfo->pwr[1][3] = 0;
			pcinfo->pddac[1][3] = 0;
		पूर्ण अन्यथा अगर (pd_gains == 1) अणु
			/*
			 * Pd gain 0 is the last one so
			 * पढ़ो the extra poपूर्णांक.
			 */
			pcinfo->pwr[0][3] = (val >> 10) & 0xf;

			pcinfo->pddac[0][3] = (val >> 14) & 0x3;
			AR5K_EEPROM_READ(offset++, val);
			pcinfo->pddac[0][3] |= (val & 0xF) << 2;
		पूर्ण

		/*
		 * Proceed with the other pd_gains
		 * as above.
		 */
		अगर (pd_gains > 2) अणु
			pcinfo->pwr_i[2] = (val >> 4) & 0x1f;
			pcinfo->pddac_i[2] = (val >> 9) & 0x7f;

			AR5K_EEPROM_READ(offset++, val);
			pcinfo->pwr[2][0] = (val >> 0) & 0xf;
			pcinfo->pddac[2][0] = (val >> 4) & 0x3f;
			pcinfo->pwr[2][1] = (val >> 10) & 0xf;

			pcinfo->pddac[2][1] = (val >> 14) & 0x3;
			AR5K_EEPROM_READ(offset++, val);
			pcinfo->pddac[2][1] |= (val & 0xF) << 2;

			pcinfo->pwr[2][2] = (val >> 4) & 0xf;
			pcinfo->pddac[2][2] = (val >> 8) & 0x3f;

			pcinfo->pwr[2][3] = 0;
			pcinfo->pddac[2][3] = 0;
		पूर्ण अन्यथा अगर (pd_gains == 2) अणु
			pcinfo->pwr[1][3] = (val >> 4) & 0xf;
			pcinfo->pddac[1][3] = (val >> 8) & 0x3f;
		पूर्ण

		अगर (pd_gains > 3) अणु
			pcinfo->pwr_i[3] = (val >> 14) & 0x3;
			AR5K_EEPROM_READ(offset++, val);
			pcinfo->pwr_i[3] |= ((val >> 0) & 0x7) << 2;

			pcinfo->pddac_i[3] = (val >> 3) & 0x7f;
			pcinfo->pwr[3][0] = (val >> 10) & 0xf;
			pcinfo->pddac[3][0] = (val >> 14) & 0x3;

			AR5K_EEPROM_READ(offset++, val);
			pcinfo->pddac[3][0] |= (val & 0xF) << 2;
			pcinfo->pwr[3][1] = (val >> 4) & 0xf;
			pcinfo->pddac[3][1] = (val >> 8) & 0x3f;

			pcinfo->pwr[3][2] = (val >> 14) & 0x3;
			AR5K_EEPROM_READ(offset++, val);
			pcinfo->pwr[3][2] |= ((val >> 0) & 0x3) << 2;

			pcinfo->pddac[3][2] = (val >> 2) & 0x3f;
			pcinfo->pwr[3][3] = (val >> 8) & 0xf;

			pcinfo->pddac[3][3] = (val >> 12) & 0xF;
			AR5K_EEPROM_READ(offset++, val);
			pcinfo->pddac[3][3] |= ((val >> 0) & 0x3) << 4;
		पूर्ण अन्यथा अगर (pd_gains == 3) अणु
			pcinfo->pwr[2][3] = (val >> 14) & 0x3;
			AR5K_EEPROM_READ(offset++, val);
			pcinfo->pwr[2][3] |= ((val >> 0) & 0x3) << 2;

			pcinfo->pddac[2][3] = (val >> 2) & 0x3f;
		पूर्ण
	पूर्ण

	वापस ath5k_eeprom_convert_pcal_info_2413(ah, mode, chinfo);
पूर्ण


/*
 * Read per rate target घातer (this is the maximum tx घातer
 * supported by the card). This info is used when setting
 * tx घातer, no matter the channel.
 *
 * This also works क्रम v5 EEPROMs.
 */
अटल पूर्णांक
ath5k_eeprom_पढ़ो_target_rate_pwr_info(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	काष्ठा ath5k_rate_pcal_info *rate_pcal_info;
	u8 *rate_target_pwr_num;
	u32 offset;
	u16 val;
	पूर्णांक i;

	offset = AR5K_EEPROM_TARGET_PWRSTART(ee->ee_misc1);
	rate_target_pwr_num = &ee->ee_rate_target_pwr_num[mode];
	चयन (mode) अणु
	हाल AR5K_EEPROM_MODE_11A:
		offset += AR5K_EEPROM_TARGET_PWR_OFF_11A(ee->ee_version);
		rate_pcal_info = ee->ee_rate_tpwr_a;
		ee->ee_rate_target_pwr_num[mode] = AR5K_EEPROM_N_5GHZ_RATE_CHAN;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11B:
		offset += AR5K_EEPROM_TARGET_PWR_OFF_11B(ee->ee_version);
		rate_pcal_info = ee->ee_rate_tpwr_b;
		ee->ee_rate_target_pwr_num[mode] = 2; /* 3rd is g mode's 1st */
		अवरोध;
	हाल AR5K_EEPROM_MODE_11G:
		offset += AR5K_EEPROM_TARGET_PWR_OFF_11G(ee->ee_version);
		rate_pcal_info = ee->ee_rate_tpwr_g;
		ee->ee_rate_target_pwr_num[mode] = AR5K_EEPROM_N_2GHZ_CHAN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Dअगरferent freq mask क्रम older eeproms (<= v3.2) */
	अगर (ee->ee_version <= AR5K_EEPROM_VERSION_3_2) अणु
		क्रम (i = 0; i < (*rate_target_pwr_num); i++) अणु
			AR5K_EEPROM_READ(offset++, val);
			rate_pcal_info[i].freq =
			    ath5k_eeprom_bin2freq(ee, (val >> 9) & 0x7f, mode);

			rate_pcal_info[i].target_घातer_6to24 = ((val >> 3) & 0x3f);
			rate_pcal_info[i].target_घातer_36 = (val << 3) & 0x3f;

			AR5K_EEPROM_READ(offset++, val);

			अगर (rate_pcal_info[i].freq == AR5K_EEPROM_CHANNEL_DIS ||
			    val == 0) अणु
				(*rate_target_pwr_num) = i;
				अवरोध;
			पूर्ण

			rate_pcal_info[i].target_घातer_36 |= ((val >> 13) & 0x7);
			rate_pcal_info[i].target_घातer_48 = ((val >> 7) & 0x3f);
			rate_pcal_info[i].target_घातer_54 = ((val >> 1) & 0x3f);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < (*rate_target_pwr_num); i++) अणु
			AR5K_EEPROM_READ(offset++, val);
			rate_pcal_info[i].freq =
			    ath5k_eeprom_bin2freq(ee, (val >> 8) & 0xff, mode);

			rate_pcal_info[i].target_घातer_6to24 = ((val >> 2) & 0x3f);
			rate_pcal_info[i].target_घातer_36 = (val << 4) & 0x3f;

			AR5K_EEPROM_READ(offset++, val);

			अगर (rate_pcal_info[i].freq == AR5K_EEPROM_CHANNEL_DIS ||
			    val == 0) अणु
				(*rate_target_pwr_num) = i;
				अवरोध;
			पूर्ण

			rate_pcal_info[i].target_घातer_36 |= (val >> 12) & 0xf;
			rate_pcal_info[i].target_घातer_48 = ((val >> 6) & 0x3f);
			rate_pcal_info[i].target_घातer_54 = (val & 0x3f);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


/*
 * Read per channel calibration info from EEPROM
 *
 * This info is used to calibrate the baseband घातer table. Imagine
 * that क्रम each channel there is a घातer curve that's hw specअगरic
 * (depends on amplअगरier etc) and we try to "correct" this curve using
 * offsets we pass on to phy chip (baseband -> beक्रमe amplअगरier) so that
 * it can use accurate घातer values when setting tx घातer (takes amplअगरier's
 * perक्रमmance on each channel पूर्णांकo account).
 *
 * EEPROM provides us with the offsets क्रम some pre-calibrated channels
 * and we have to पूर्णांकerpolate to create the full table क्रम these channels and
 * also the table क्रम any channel.
 */
अटल पूर्णांक
ath5k_eeprom_पढ़ो_pcal_info(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	पूर्णांक (*पढ़ो_pcal)(काष्ठा ath5k_hw *hw, पूर्णांक mode);
	पूर्णांक mode;
	पूर्णांक err;

	अगर ((ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_0) &&
			(AR5K_EEPROM_EEMAP(ee->ee_misc0) == 1))
		पढ़ो_pcal = ath5k_eeprom_पढ़ो_pcal_info_5112;
	अन्यथा अगर ((ah->ah_ee_version >= AR5K_EEPROM_VERSION_5_0) &&
			(AR5K_EEPROM_EEMAP(ee->ee_misc0) == 2))
		पढ़ो_pcal = ath5k_eeprom_पढ़ो_pcal_info_2413;
	अन्यथा
		पढ़ो_pcal = ath5k_eeprom_पढ़ो_pcal_info_5111;


	क्रम (mode = AR5K_EEPROM_MODE_11A; mode <= AR5K_EEPROM_MODE_11G;
	mode++) अणु
		err = पढ़ो_pcal(ah, mode);
		अगर (err)
			वापस err;

		err = ath5k_eeprom_पढ़ो_target_rate_pwr_info(ah, mode);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Read conक्रमmance test limits used क्रम regulatory control */
अटल पूर्णांक
ath5k_eeprom_पढ़ो_ctl_info(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	काष्ठा ath5k_edge_घातer *rep;
	अचिन्हित पूर्णांक fmask, pmask;
	अचिन्हित पूर्णांक ctl_mode;
	पूर्णांक i, j;
	u32 offset;
	u16 val;

	pmask = AR5K_EEPROM_POWER_M;
	fmask = AR5K_EEPROM_FREQ_M(ee->ee_version);
	offset = AR5K_EEPROM_CTL(ee->ee_version);
	ee->ee_ctls = AR5K_EEPROM_N_CTLS(ee->ee_version);
	क्रम (i = 0; i < ee->ee_ctls; i += 2) अणु
		AR5K_EEPROM_READ(offset++, val);
		ee->ee_ctl[i] = (val >> 8) & 0xff;
		ee->ee_ctl[i + 1] = val & 0xff;
	पूर्ण

	offset = AR5K_EEPROM_GROUP8_OFFSET;
	अगर (ee->ee_version >= AR5K_EEPROM_VERSION_4_0)
		offset += AR5K_EEPROM_TARGET_PWRSTART(ee->ee_misc1) -
			AR5K_EEPROM_GROUP5_OFFSET;
	अन्यथा
		offset += AR5K_EEPROM_GROUPS_START(ee->ee_version);

	rep = ee->ee_ctl_pwr;
	क्रम (i = 0; i < ee->ee_ctls; i++) अणु
		चयन (ee->ee_ctl[i] & AR5K_CTL_MODE_M) अणु
		हाल AR5K_CTL_11A:
		हाल AR5K_CTL_TURBO:
			ctl_mode = AR5K_EEPROM_MODE_11A;
			अवरोध;
		शेष:
			ctl_mode = AR5K_EEPROM_MODE_11G;
			अवरोध;
		पूर्ण
		अगर (ee->ee_ctl[i] == 0) अणु
			अगर (ee->ee_version >= AR5K_EEPROM_VERSION_3_3)
				offset += 8;
			अन्यथा
				offset += 7;
			rep += AR5K_EEPROM_N_EDGES;
			जारी;
		पूर्ण
		अगर (ee->ee_version >= AR5K_EEPROM_VERSION_3_3) अणु
			क्रम (j = 0; j < AR5K_EEPROM_N_EDGES; j += 2) अणु
				AR5K_EEPROM_READ(offset++, val);
				rep[j].freq = (val >> 8) & fmask;
				rep[j + 1].freq = val & fmask;
			पूर्ण
			क्रम (j = 0; j < AR5K_EEPROM_N_EDGES; j += 2) अणु
				AR5K_EEPROM_READ(offset++, val);
				rep[j].edge = (val >> 8) & pmask;
				rep[j].flag = (val >> 14) & 1;
				rep[j + 1].edge = val & pmask;
				rep[j + 1].flag = (val >> 6) & 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			AR5K_EEPROM_READ(offset++, val);
			rep[0].freq = (val >> 9) & fmask;
			rep[1].freq = (val >> 2) & fmask;
			rep[2].freq = (val << 5) & fmask;

			AR5K_EEPROM_READ(offset++, val);
			rep[2].freq |= (val >> 11) & 0x1f;
			rep[3].freq = (val >> 4) & fmask;
			rep[4].freq = (val << 3) & fmask;

			AR5K_EEPROM_READ(offset++, val);
			rep[4].freq |= (val >> 13) & 0x7;
			rep[5].freq = (val >> 6) & fmask;
			rep[6].freq = (val << 1) & fmask;

			AR5K_EEPROM_READ(offset++, val);
			rep[6].freq |= (val >> 15) & 0x1;
			rep[7].freq = (val >> 8) & fmask;

			rep[0].edge = (val >> 2) & pmask;
			rep[1].edge = (val << 4) & pmask;

			AR5K_EEPROM_READ(offset++, val);
			rep[1].edge |= (val >> 12) & 0xf;
			rep[2].edge = (val >> 6) & pmask;
			rep[3].edge = val & pmask;

			AR5K_EEPROM_READ(offset++, val);
			rep[4].edge = (val >> 10) & pmask;
			rep[5].edge = (val >> 4) & pmask;
			rep[6].edge = (val << 2) & pmask;

			AR5K_EEPROM_READ(offset++, val);
			rep[6].edge |= (val >> 14) & 0x3;
			rep[7].edge = (val >> 8) & pmask;
		पूर्ण
		क्रम (j = 0; j < AR5K_EEPROM_N_EDGES; j++) अणु
			rep[j].freq = ath5k_eeprom_bin2freq(ee,
				rep[j].freq, ctl_mode);
		पूर्ण
		rep += AR5K_EEPROM_N_EDGES;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ath5k_eeprom_पढ़ो_spur_chans(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u32 offset;
	u16 val;
	पूर्णांक  i;

	offset = AR5K_EEPROM_CTL(ee->ee_version) +
				AR5K_EEPROM_N_CTLS(ee->ee_version);

	अगर (ee->ee_version < AR5K_EEPROM_VERSION_5_3) अणु
		/* No spur info क्रम 5GHz */
		ee->ee_spur_chans[0][0] = AR5K_EEPROM_NO_SPUR;
		/* 2 channels क्रम 2GHz (2464/2420) */
		ee->ee_spur_chans[0][1] = AR5K_EEPROM_5413_SPUR_CHAN_1;
		ee->ee_spur_chans[1][1] = AR5K_EEPROM_5413_SPUR_CHAN_2;
		ee->ee_spur_chans[2][1] = AR5K_EEPROM_NO_SPUR;
	पूर्ण अन्यथा अगर (ee->ee_version >= AR5K_EEPROM_VERSION_5_3) अणु
		क्रम (i = 0; i < AR5K_EEPROM_N_SPUR_CHANS; i++) अणु
			AR5K_EEPROM_READ(offset, val);
			ee->ee_spur_chans[i][0] = val;
			AR5K_EEPROM_READ(offset + AR5K_EEPROM_N_SPUR_CHANS,
									val);
			ee->ee_spur_chans[i][1] = val;
			offset++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


/***********************\
* Init/Detach functions *
\***********************/

/*
 * Initialize eeprom data काष्ठाure
 */
पूर्णांक
ath5k_eeprom_init(काष्ठा ath5k_hw *ah)
अणु
	पूर्णांक err;

	err = ath5k_eeprom_init_header(ah);
	अगर (err < 0)
		वापस err;

	err = ath5k_eeprom_init_modes(ah);
	अगर (err < 0)
		वापस err;

	err = ath5k_eeprom_पढ़ो_pcal_info(ah);
	अगर (err < 0)
		वापस err;

	err = ath5k_eeprom_पढ़ो_ctl_info(ah);
	अगर (err < 0)
		वापस err;

	err = ath5k_eeprom_पढ़ो_spur_chans(ah);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

व्योम
ath5k_eeprom_detach(काष्ठा ath5k_hw *ah)
अणु
	u8 mode;

	क्रम (mode = AR5K_EEPROM_MODE_11A; mode <= AR5K_EEPROM_MODE_11G; mode++)
		ath5k_eeprom_मुक्त_pcal_info(ah, mode);
पूर्ण

पूर्णांक
ath5k_eeprom_mode_from_channel(काष्ठा ath5k_hw *ah,
		काष्ठा ieee80211_channel *channel)
अणु
	चयन (channel->hw_value) अणु
	हाल AR5K_MODE_11A:
		वापस AR5K_EEPROM_MODE_11A;
	हाल AR5K_MODE_11G:
		वापस AR5K_EEPROM_MODE_11G;
	हाल AR5K_MODE_11B:
		वापस AR5K_EEPROM_MODE_11B;
	शेष:
		ATH5K_WARN(ah, "channel is not A/B/G!");
		वापस AR5K_EEPROM_MODE_11A;
	पूर्ण
पूर्ण
