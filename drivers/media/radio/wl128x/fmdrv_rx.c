<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  FM Driver क्रम Connectivity chip of Texas Instruments.
 *  This sub-module of FM driver implements FM RX functionality.
 *
 *  Copyright (C) 2011 Texas Instruments
 *  Author: Raja Mani <raja_mani@ti.com>
 *  Author: Manjunatha Halli <manjunatha_halli@ti.com>
 */

#समावेश "fmdrv.h"
#समावेश "fmdrv_common.h"
#समावेश "fmdrv_rx.h"

व्योम fm_rx_reset_rds_cache(काष्ठा fmdev *fmdev)
अणु
	fmdev->rx.rds.flag = FM_RDS_DISABLE;
	fmdev->rx.rds.last_blk_idx = 0;
	fmdev->rx.rds.wr_idx = 0;
	fmdev->rx.rds.rd_idx = 0;

	अगर (fmdev->rx.af_mode == FM_RX_RDS_AF_SWITCH_MODE_ON)
		fmdev->irq_info.mask |= FM_LEV_EVENT;
पूर्ण

व्योम fm_rx_reset_station_info(काष्ठा fmdev *fmdev)
अणु
	fmdev->rx.stat_info.picode = FM_NO_PI_CODE;
	fmdev->rx.stat_info.afcache_size = 0;
	fmdev->rx.stat_info.af_list_max = 0;
पूर्ण

पूर्णांक fm_rx_set_freq(काष्ठा fmdev *fmdev, u32 freq)
अणु
	अचिन्हित दीर्घ समयleft;
	u16 payload, curr_frq, पूर्णांकr_flag;
	u32 curr_frq_in_khz;
	u32 resp_len;
	पूर्णांक ret;

	अगर (freq < fmdev->rx.region.bot_freq || freq > fmdev->rx.region.top_freq) अणु
		fmerr("Invalid frequency %d\n", freq);
		वापस -EINVAL;
	पूर्ण

	/* Set audio enable */
	payload = FM_RX_AUDIO_ENABLE_I2S_AND_ANALOG;

	ret = fmc_send_cmd(fmdev, AUDIO_ENABLE_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Set hilo to स्वतःmatic selection */
	payload = FM_RX_IFFREQ_HILO_AUTOMATIC;
	ret = fmc_send_cmd(fmdev, HILO_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Calculate frequency index and set*/
	payload = (freq - fmdev->rx.region.bot_freq) / FM_FREQ_MUL;

	ret = fmc_send_cmd(fmdev, FREQ_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Read flags - just to clear any pending पूर्णांकerrupts अगर we had */
	ret = fmc_send_cmd(fmdev, FLAG_GET, REG_RD, शून्य, 2, शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Enable FR, BL पूर्णांकerrupts */
	पूर्णांकr_flag = fmdev->irq_info.mask;
	fmdev->irq_info.mask = (FM_FR_EVENT | FM_BL_EVENT);
	payload = fmdev->irq_info.mask;
	ret = fmc_send_cmd(fmdev, INT_MASK_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Start tune */
	payload = FM_TUNER_PRESET_MODE;
	ret = fmc_send_cmd(fmdev, TUNER_MODE_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		जाओ निकास;

	/* Wait क्रम tune ended पूर्णांकerrupt */
	init_completion(&fmdev->मुख्यtask_comp);
	समयleft = रुको_क्रम_completion_समयout(&fmdev->मुख्यtask_comp,
			FM_DRV_TX_TIMEOUT);
	अगर (!समयleft) अणु
		fmerr("Timeout(%d sec),didn't get tune ended int\n",
			   jअगरfies_to_msecs(FM_DRV_TX_TIMEOUT) / 1000);
		ret = -ETIMEDOUT;
		जाओ निकास;
	पूर्ण

	/* Read freq back to confirm */
	ret = fmc_send_cmd(fmdev, FREQ_SET, REG_RD, शून्य, 2, &curr_frq, &resp_len);
	अगर (ret < 0)
		जाओ निकास;

	curr_frq = be16_to_cpu((__क्रमce __be16)curr_frq);
	curr_frq_in_khz = (fmdev->rx.region.bot_freq + ((u32)curr_frq * FM_FREQ_MUL));

	अगर (curr_frq_in_khz != freq) अणु
		pr_info("Frequency is set to (%d) but requested freq is (%d)\n",
			curr_frq_in_khz, freq);
	पूर्ण

	/* Update local cache  */
	fmdev->rx.freq = curr_frq_in_khz;
निकास:
	/* Re-enable शेष FM पूर्णांकerrupts */
	fmdev->irq_info.mask = पूर्णांकr_flag;
	payload = fmdev->irq_info.mask;
	ret = fmc_send_cmd(fmdev, INT_MASK_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Reset RDS cache and current station poपूर्णांकers */
	fm_rx_reset_rds_cache(fmdev);
	fm_rx_reset_station_info(fmdev);

	वापस ret;
पूर्ण

अटल पूर्णांक fm_rx_set_channel_spacing(काष्ठा fmdev *fmdev, u32 spacing)
अणु
	u16 payload;
	पूर्णांक ret;

	अगर (spacing > 0 && spacing <= 50000)
		spacing = FM_CHANNEL_SPACING_50KHZ;
	अन्यथा अगर (spacing > 50000 && spacing <= 100000)
		spacing = FM_CHANNEL_SPACING_100KHZ;
	अन्यथा
		spacing = FM_CHANNEL_SPACING_200KHZ;

	/* set channel spacing */
	payload = spacing;
	ret = fmc_send_cmd(fmdev, CHANL_BW_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	fmdev->rx.region.chanl_space = spacing * FM_FREQ_MUL;

	वापस ret;
पूर्ण

पूर्णांक fm_rx_seek(काष्ठा fmdev *fmdev, u32 seek_upward,
		u32 wrap_around, u32 spacing)
अणु
	u32 resp_len;
	u16 curr_frq, next_frq, last_frq;
	u16 payload, पूर्णांक_reason, पूर्णांकr_flag;
	u16 offset, space_idx;
	अचिन्हित दीर्घ समयleft;
	पूर्णांक ret;

	/* Set channel spacing */
	ret = fm_rx_set_channel_spacing(fmdev, spacing);
	अगर (ret < 0) अणु
		fmerr("Failed to set channel spacing\n");
		वापस ret;
	पूर्ण

	/* Read the current frequency from chip */
	ret = fmc_send_cmd(fmdev, FREQ_SET, REG_RD, शून्य,
			माप(curr_frq), &curr_frq, &resp_len);
	अगर (ret < 0)
		वापस ret;

	curr_frq = be16_to_cpu((__क्रमce __be16)curr_frq);
	last_frq = (fmdev->rx.region.top_freq - fmdev->rx.region.bot_freq) / FM_FREQ_MUL;

	/* Check the offset in order to be aligned to the channel spacing*/
	space_idx = fmdev->rx.region.chanl_space / FM_FREQ_MUL;
	offset = curr_frq % space_idx;

	next_frq = seek_upward ? curr_frq + space_idx /* Seek Up */ :
				curr_frq - space_idx /* Seek Down */ ;

	/*
	 * Add or subtract offset in order to stay aligned to the channel
	 * spacing.
	 */
	अगर ((लघु)next_frq < 0)
		next_frq = last_frq - offset;
	अन्यथा अगर (next_frq > last_frq)
		next_frq = 0 + offset;

again:
	/* Set calculated next frequency to perक्रमm seek */
	payload = next_frq;
	ret = fmc_send_cmd(fmdev, FREQ_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Set search direction (0:Seek Down, 1:Seek Up) */
	payload = (seek_upward ? FM_SEARCH_सूचीECTION_UP : FM_SEARCH_सूचीECTION_DOWN);
	ret = fmc_send_cmd(fmdev, SEARCH_सूची_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Read flags - just to clear any pending पूर्णांकerrupts अगर we had */
	ret = fmc_send_cmd(fmdev, FLAG_GET, REG_RD, शून्य, 2, शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Enable FR, BL पूर्णांकerrupts */
	पूर्णांकr_flag = fmdev->irq_info.mask;
	fmdev->irq_info.mask = (FM_FR_EVENT | FM_BL_EVENT);
	payload = fmdev->irq_info.mask;
	ret = fmc_send_cmd(fmdev, INT_MASK_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Start seek */
	payload = FM_TUNER_AUTONOMOUS_SEARCH_MODE;
	ret = fmc_send_cmd(fmdev, TUNER_MODE_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Wait क्रम tune ended/band limit reached पूर्णांकerrupt */
	init_completion(&fmdev->मुख्यtask_comp);
	समयleft = रुको_क्रम_completion_समयout(&fmdev->मुख्यtask_comp,
			FM_DRV_RX_SEEK_TIMEOUT);
	अगर (!समयleft) अणु
		fmerr("Timeout(%d sec),didn't get tune ended int\n",
			   jअगरfies_to_msecs(FM_DRV_RX_SEEK_TIMEOUT) / 1000);
		वापस -ENODATA;
	पूर्ण

	पूर्णांक_reason = fmdev->irq_info.flag & (FM_TUNE_COMPLETE | FM_BAND_LIMIT);

	/* Re-enable शेष FM पूर्णांकerrupts */
	fmdev->irq_info.mask = पूर्णांकr_flag;
	payload = fmdev->irq_info.mask;
	ret = fmc_send_cmd(fmdev, INT_MASK_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	अगर (पूर्णांक_reason & FM_BL_EVENT) अणु
		अगर (wrap_around == 0) अणु
			fmdev->rx.freq = seek_upward ?
				fmdev->rx.region.top_freq :
				fmdev->rx.region.bot_freq;
		पूर्ण अन्यथा अणु
			fmdev->rx.freq = seek_upward ?
				fmdev->rx.region.bot_freq :
				fmdev->rx.region.top_freq;
			/* Calculate frequency index to ग_लिखो */
			next_frq = (fmdev->rx.freq -
					fmdev->rx.region.bot_freq) / FM_FREQ_MUL;
			जाओ again;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Read freq to know where operation tune operation stopped */
		ret = fmc_send_cmd(fmdev, FREQ_SET, REG_RD, शून्य, 2,
				&curr_frq, &resp_len);
		अगर (ret < 0)
			वापस ret;

		curr_frq = be16_to_cpu((__क्रमce __be16)curr_frq);
		fmdev->rx.freq = (fmdev->rx.region.bot_freq +
				((u32)curr_frq * FM_FREQ_MUL));

	पूर्ण
	/* Reset RDS cache and current station poपूर्णांकers */
	fm_rx_reset_rds_cache(fmdev);
	fm_rx_reset_station_info(fmdev);

	वापस ret;
पूर्ण

पूर्णांक fm_rx_set_volume(काष्ठा fmdev *fmdev, u16 vol_to_set)
अणु
	u16 payload;
	पूर्णांक ret;

	अगर (fmdev->curr_fmmode != FM_MODE_RX)
		वापस -EPERM;

	अगर (vol_to_set > FM_RX_VOLUME_MAX) अणु
		fmerr("Volume is not within(%d-%d) range\n",
			   FM_RX_VOLUME_MIN, FM_RX_VOLUME_MAX);
		वापस -EINVAL;
	पूर्ण
	vol_to_set *= FM_RX_VOLUME_GAIN_STEP;

	payload = vol_to_set;
	ret = fmc_send_cmd(fmdev, VOLUME_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	fmdev->rx.volume = vol_to_set;
	वापस ret;
पूर्ण

/* Get volume */
पूर्णांक fm_rx_get_volume(काष्ठा fmdev *fmdev, u16 *curr_vol)
अणु
	अगर (fmdev->curr_fmmode != FM_MODE_RX)
		वापस -EPERM;

	अगर (curr_vol == शून्य) अणु
		fmerr("Invalid memory\n");
		वापस -ENOMEM;
	पूर्ण

	*curr_vol = fmdev->rx.volume / FM_RX_VOLUME_GAIN_STEP;

	वापस 0;
पूर्ण

/* To get current band's bottom and top frequency */
पूर्णांक fm_rx_get_band_freq_range(काष्ठा fmdev *fmdev, u32 *bot_freq, u32 *top_freq)
अणु
	अगर (bot_freq != शून्य)
		*bot_freq = fmdev->rx.region.bot_freq;

	अगर (top_freq != शून्य)
		*top_freq = fmdev->rx.region.top_freq;

	वापस 0;
पूर्ण

/* Returns current band index (0-Europe/US; 1-Japan) */
व्योम fm_rx_get_region(काष्ठा fmdev *fmdev, u8 *region)
अणु
	*region = fmdev->rx.region.fm_band;
पूर्ण

/* Sets band (0-Europe/US; 1-Japan) */
पूर्णांक fm_rx_set_region(काष्ठा fmdev *fmdev, u8 region_to_set)
अणु
	u16 payload;
	u32 new_frq = 0;
	पूर्णांक ret;

	अगर (region_to_set != FM_BAND_EUROPE_US &&
	    region_to_set != FM_BAND_JAPAN) अणु
		fmerr("Invalid band\n");
		वापस -EINVAL;
	पूर्ण

	अगर (fmdev->rx.region.fm_band == region_to_set) अणु
		fmerr("Requested band is already configured\n");
		वापस 0;
	पूर्ण

	/* Send cmd to set the band  */
	payload = (u16)region_to_set;
	ret = fmc_send_cmd(fmdev, BAND_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	fmc_update_region_info(fmdev, region_to_set);

	/* Check whether current RX frequency is within band boundary */
	अगर (fmdev->rx.freq < fmdev->rx.region.bot_freq)
		new_frq = fmdev->rx.region.bot_freq;
	अन्यथा अगर (fmdev->rx.freq > fmdev->rx.region.top_freq)
		new_frq = fmdev->rx.region.top_freq;

	अगर (new_frq) अणु
		fmdbg("Current freq is not within band limit boundary,switching to %d KHz\n",
		      new_frq);
		 /* Current RX frequency is not in range. So, update it */
		ret = fm_rx_set_freq(fmdev, new_frq);
	पूर्ण

	वापस ret;
पूर्ण

/* Reads current mute mode (Mute Off/On/Attenuate)*/
पूर्णांक fm_rx_get_mute_mode(काष्ठा fmdev *fmdev, u8 *curr_mute_mode)
अणु
	अगर (fmdev->curr_fmmode != FM_MODE_RX)
		वापस -EPERM;

	अगर (curr_mute_mode == शून्य) अणु
		fmerr("Invalid memory\n");
		वापस -ENOMEM;
	पूर्ण

	*curr_mute_mode = fmdev->rx.mute_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक fm_config_rx_mute_reg(काष्ठा fmdev *fmdev)
अणु
	u16 payload, muteval;
	पूर्णांक ret;

	muteval = 0;
	चयन (fmdev->rx.mute_mode) अणु
	हाल FM_MUTE_ON:
		muteval = FM_RX_AC_MUTE_MODE;
		अवरोध;

	हाल FM_MUTE_OFF:
		muteval = FM_RX_UNMUTE_MODE;
		अवरोध;

	हाल FM_MUTE_ATTENUATE:
		muteval = FM_RX_SOFT_MUTE_FORCE_MODE;
		अवरोध;
	पूर्ण
	अगर (fmdev->rx.rf_depend_mute == FM_RX_RF_DEPENDENT_MUTE_ON)
		muteval |= FM_RX_RF_DEP_MODE;
	अन्यथा
		muteval &= ~FM_RX_RF_DEP_MODE;

	payload = muteval;
	ret = fmc_send_cmd(fmdev, MUTE_STATUS_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/* Configures mute mode (Mute Off/On/Attenuate) */
पूर्णांक fm_rx_set_mute_mode(काष्ठा fmdev *fmdev, u8 mute_mode_toset)
अणु
	u8 org_state;
	पूर्णांक ret;

	अगर (fmdev->rx.mute_mode == mute_mode_toset)
		वापस 0;

	org_state = fmdev->rx.mute_mode;
	fmdev->rx.mute_mode = mute_mode_toset;

	ret = fm_config_rx_mute_reg(fmdev);
	अगर (ret < 0) अणु
		fmdev->rx.mute_mode = org_state;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Gets RF dependent soft mute mode enable/disable status */
पूर्णांक fm_rx_get_rfdepend_sofपंचांगute(काष्ठा fmdev *fmdev, u8 *curr_mute_mode)
अणु
	अगर (fmdev->curr_fmmode != FM_MODE_RX)
		वापस -EPERM;

	अगर (curr_mute_mode == शून्य) अणु
		fmerr("Invalid memory\n");
		वापस -ENOMEM;
	पूर्ण

	*curr_mute_mode = fmdev->rx.rf_depend_mute;

	वापस 0;
पूर्ण

/* Sets RF dependent soft mute mode */
पूर्णांक fm_rx_set_rfdepend_sofपंचांगute(काष्ठा fmdev *fmdev, u8 rfdepend_mute)
अणु
	u8 org_state;
	पूर्णांक ret;

	अगर (fmdev->curr_fmmode != FM_MODE_RX)
		वापस -EPERM;

	अगर (rfdepend_mute != FM_RX_RF_DEPENDENT_MUTE_ON &&
	    rfdepend_mute != FM_RX_RF_DEPENDENT_MUTE_OFF) अणु
		fmerr("Invalid RF dependent soft mute\n");
		वापस -EINVAL;
	पूर्ण
	अगर (fmdev->rx.rf_depend_mute == rfdepend_mute)
		वापस 0;

	org_state = fmdev->rx.rf_depend_mute;
	fmdev->rx.rf_depend_mute = rfdepend_mute;

	ret = fm_config_rx_mute_reg(fmdev);
	अगर (ret < 0) अणु
		fmdev->rx.rf_depend_mute = org_state;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Returns the संकेत strength level of current channel */
पूर्णांक fm_rx_get_rssi_level(काष्ठा fmdev *fmdev, u16 *rssilvl)
अणु
	__be16 curr_rssi_lel;
	u32 resp_len;
	पूर्णांक ret;

	अगर (rssilvl == शून्य) अणु
		fmerr("Invalid memory\n");
		वापस -ENOMEM;
	पूर्ण
	/* Read current RSSI level */
	ret = fmc_send_cmd(fmdev, RSSI_LVL_GET, REG_RD, शून्य, 2,
			&curr_rssi_lel, &resp_len);
	अगर (ret < 0)
		वापस ret;

	*rssilvl = be16_to_cpu(curr_rssi_lel);

	वापस 0;
पूर्ण

/*
 * Sets the संकेत strength level that once reached
 * will stop the स्वतः search process
 */
पूर्णांक fm_rx_set_rssi_threshold(काष्ठा fmdev *fmdev, लघु rssi_lvl_toset)
अणु
	u16 payload;
	पूर्णांक ret;

	अगर (rssi_lvl_toset < FM_RX_RSSI_THRESHOLD_MIN ||
			rssi_lvl_toset > FM_RX_RSSI_THRESHOLD_MAX) अणु
		fmerr("Invalid RSSI threshold level\n");
		वापस -EINVAL;
	पूर्ण
	payload = (u16)rssi_lvl_toset;
	ret = fmc_send_cmd(fmdev, SEARCH_LVL_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	fmdev->rx.rssi_threshold = rssi_lvl_toset;

	वापस 0;
पूर्ण

/* Returns current RX RSSI threshold value */
पूर्णांक fm_rx_get_rssi_threshold(काष्ठा fmdev *fmdev, लघु *curr_rssi_lvl)
अणु
	अगर (fmdev->curr_fmmode != FM_MODE_RX)
		वापस -EPERM;

	अगर (curr_rssi_lvl == शून्य) अणु
		fmerr("Invalid memory\n");
		वापस -ENOMEM;
	पूर्ण

	*curr_rssi_lvl = fmdev->rx.rssi_threshold;

	वापस 0;
पूर्ण

/* Sets RX stereo/mono modes */
पूर्णांक fm_rx_set_stereo_mono(काष्ठा fmdev *fmdev, u16 mode)
अणु
	u16 payload;
	पूर्णांक ret;

	अगर (mode != FM_STEREO_MODE && mode != FM_MONO_MODE) अणु
		fmerr("Invalid mode\n");
		वापस -EINVAL;
	पूर्ण

	/* Set stereo/mono mode */
	payload = (u16)mode;
	ret = fmc_send_cmd(fmdev, MOST_MODE_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Set stereo blending mode */
	payload = FM_STEREO_SOFT_BLEND;
	ret = fmc_send_cmd(fmdev, MOST_BLEND_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/* Gets current RX stereo/mono mode */
पूर्णांक fm_rx_get_stereo_mono(काष्ठा fmdev *fmdev, u16 *mode)
अणु
	__be16 curr_mode;
	u32 resp_len;
	पूर्णांक ret;

	अगर (mode == शून्य) अणु
		fmerr("Invalid memory\n");
		वापस -ENOMEM;
	पूर्ण

	ret = fmc_send_cmd(fmdev, MOST_MODE_SET, REG_RD, शून्य, 2,
			&curr_mode, &resp_len);
	अगर (ret < 0)
		वापस ret;

	*mode = be16_to_cpu(curr_mode);

	वापस 0;
पूर्ण

/* Choose RX de-emphasis filter mode (50us/75us) */
पूर्णांक fm_rx_set_deemphasis_mode(काष्ठा fmdev *fmdev, u16 mode)
अणु
	u16 payload;
	पूर्णांक ret;

	अगर (fmdev->curr_fmmode != FM_MODE_RX)
		वापस -EPERM;

	अगर (mode != FM_RX_EMPHASIS_FILTER_50_USEC &&
			mode != FM_RX_EMPHASIS_FILTER_75_USEC) अणु
		fmerr("Invalid rx de-emphasis mode (%d)\n", mode);
		वापस -EINVAL;
	पूर्ण

	payload = mode;
	ret = fmc_send_cmd(fmdev, DEMPH_MODE_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	fmdev->rx.deemphasis_mode = mode;

	वापस 0;
पूर्ण

/* Gets current RX de-emphasis filter mode */
पूर्णांक fm_rx_get_deemph_mode(काष्ठा fmdev *fmdev, u16 *curr_deemphasis_mode)
अणु
	अगर (fmdev->curr_fmmode != FM_MODE_RX)
		वापस -EPERM;

	अगर (curr_deemphasis_mode == शून्य) अणु
		fmerr("Invalid memory\n");
		वापस -ENOMEM;
	पूर्ण

	*curr_deemphasis_mode = fmdev->rx.deemphasis_mode;

	वापस 0;
पूर्ण

/* Enable/Disable RX RDS */
पूर्णांक fm_rx_set_rds_mode(काष्ठा fmdev *fmdev, u8 rds_en_dis)
अणु
	u16 payload;
	पूर्णांक ret;

	अगर (rds_en_dis != FM_RDS_ENABLE && rds_en_dis != FM_RDS_DISABLE) अणु
		fmerr("Invalid rds option\n");
		वापस -EINVAL;
	पूर्ण

	अगर (rds_en_dis == FM_RDS_ENABLE
	    && fmdev->rx.rds.flag == FM_RDS_DISABLE) अणु
		/* Turn on RX RDS and RDS circuit */
		payload = FM_RX_PWR_SET_FM_AND_RDS_BLK_ON;
		ret = fmc_send_cmd(fmdev, POWER_SET, REG_WR, &payload,
				माप(payload), शून्य, शून्य);
		अगर (ret < 0)
			वापस ret;

		/* Clear and reset RDS FIFO */
		payload = FM_RX_RDS_FLUSH_FIFO;
		ret = fmc_send_cmd(fmdev, RDS_CNTRL_SET, REG_WR, &payload,
		माप(payload), शून्य, शून्य);
		अगर (ret < 0)
			वापस ret;

		/* Read flags - just to clear any pending पूर्णांकerrupts. */
		ret = fmc_send_cmd(fmdev, FLAG_GET, REG_RD, शून्य, 2,
				शून्य, शून्य);
		अगर (ret < 0)
			वापस ret;

		/* Set RDS FIFO threshold value */
		payload = FM_RX_RDS_FIFO_THRESHOLD;
		ret = fmc_send_cmd(fmdev, RDS_MEM_SET, REG_WR, &payload,
		माप(payload), शून्य, शून्य);
		अगर (ret < 0)
			वापस ret;

		/* Enable RDS पूर्णांकerrupt */
		fmdev->irq_info.mask |= FM_RDS_EVENT;
		payload = fmdev->irq_info.mask;
		ret = fmc_send_cmd(fmdev, INT_MASK_SET, REG_WR, &payload,
				माप(payload), शून्य, शून्य);
		अगर (ret < 0) अणु
			fmdev->irq_info.mask &= ~FM_RDS_EVENT;
			वापस ret;
		पूर्ण

		/* Update our local flag */
		fmdev->rx.rds.flag = FM_RDS_ENABLE;
	पूर्ण अन्यथा अगर (rds_en_dis == FM_RDS_DISABLE
		   && fmdev->rx.rds.flag == FM_RDS_ENABLE) अणु
		/* Turn off RX RDS */
		payload = FM_RX_PWR_SET_FM_ON_RDS_OFF;
		ret = fmc_send_cmd(fmdev, POWER_SET, REG_WR, &payload,
				माप(payload), शून्य, शून्य);
		अगर (ret < 0)
			वापस ret;

		/* Reset RDS poपूर्णांकers */
		fmdev->rx.rds.last_blk_idx = 0;
		fmdev->rx.rds.wr_idx = 0;
		fmdev->rx.rds.rd_idx = 0;
		fm_rx_reset_station_info(fmdev);

		/* Update RDS local cache */
		fmdev->irq_info.mask &= ~(FM_RDS_EVENT);
		fmdev->rx.rds.flag = FM_RDS_DISABLE;
	पूर्ण

	वापस 0;
पूर्ण

/* Returns current RX RDS enable/disable status */
पूर्णांक fm_rx_get_rds_mode(काष्ठा fmdev *fmdev, u8 *curr_rds_en_dis)
अणु
	अगर (fmdev->curr_fmmode != FM_MODE_RX)
		वापस -EPERM;

	अगर (curr_rds_en_dis == शून्य) अणु
		fmerr("Invalid memory\n");
		वापस -ENOMEM;
	पूर्ण

	*curr_rds_en_dis = fmdev->rx.rds.flag;

	वापस 0;
पूर्ण

/* Sets RDS operation mode (RDS/RDBS) */
पूर्णांक fm_rx_set_rds_प्रणाली(काष्ठा fmdev *fmdev, u8 rds_mode)
अणु
	u16 payload;
	पूर्णांक ret;

	अगर (fmdev->curr_fmmode != FM_MODE_RX)
		वापस -EPERM;

	अगर (rds_mode != FM_RDS_SYSTEM_RDS && rds_mode != FM_RDS_SYSTEM_RBDS) अणु
		fmerr("Invalid rds mode\n");
		वापस -EINVAL;
	पूर्ण
	/* Set RDS operation mode */
	payload = (u16)rds_mode;
	ret = fmc_send_cmd(fmdev, RDS_SYSTEM_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	fmdev->rx.rds_mode = rds_mode;

	वापस 0;
पूर्ण

/* Configures Alternate Frequency चयन mode */
पूर्णांक fm_rx_set_af_चयन(काष्ठा fmdev *fmdev, u8 af_mode)
अणु
	u16 payload;
	पूर्णांक ret;

	अगर (fmdev->curr_fmmode != FM_MODE_RX)
		वापस -EPERM;

	अगर (af_mode != FM_RX_RDS_AF_SWITCH_MODE_ON &&
	    af_mode != FM_RX_RDS_AF_SWITCH_MODE_OFF) अणु
		fmerr("Invalid af mode\n");
		वापस -EINVAL;
	पूर्ण
	/* Enable/disable low RSSI पूर्णांकerrupt based on af_mode */
	अगर (af_mode == FM_RX_RDS_AF_SWITCH_MODE_ON)
		fmdev->irq_info.mask |= FM_LEV_EVENT;
	अन्यथा
		fmdev->irq_info.mask &= ~FM_LEV_EVENT;

	payload = fmdev->irq_info.mask;
	ret = fmc_send_cmd(fmdev, INT_MASK_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	fmdev->rx.af_mode = af_mode;

	वापस 0;
पूर्ण

/* Returns Alternate Frequency चयन status */
पूर्णांक fm_rx_get_af_चयन(काष्ठा fmdev *fmdev, u8 *af_mode)
अणु
	अगर (fmdev->curr_fmmode != FM_MODE_RX)
		वापस -EPERM;

	अगर (af_mode == शून्य) अणु
		fmerr("Invalid memory\n");
		वापस -ENOMEM;
	पूर्ण

	*af_mode = fmdev->rx.af_mode;

	वापस 0;
पूर्ण
