<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  FM Driver क्रम Connectivity chip of Texas Instruments.
 *  This sub-module of FM driver implements FM TX functionality.
 *
 *  Copyright (C) 2011 Texas Instruments
 */

#समावेश <linux/delay.h>
#समावेश "fmdrv.h"
#समावेश "fmdrv_common.h"
#समावेश "fmdrv_tx.h"

पूर्णांक fm_tx_set_stereo_mono(काष्ठा fmdev *fmdev, u16 mode)
अणु
	u16 payload;
	पूर्णांक ret;

	अगर (fmdev->tx_data.aud_mode == mode)
		वापस 0;

	fmdbg("stereo mode: %d\n", mode);

	/* Set Stereo/Mono mode */
	payload = (1 - mode);
	ret = fmc_send_cmd(fmdev, MONO_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	fmdev->tx_data.aud_mode = mode;

	वापस ret;
पूर्ण

अटल पूर्णांक set_rds_text(काष्ठा fmdev *fmdev, u8 *rds_text)
अणु
	u16 payload;
	पूर्णांक ret;

	ret = fmc_send_cmd(fmdev, RDS_DATA_SET, REG_WR, rds_text,
			म_माप(rds_text), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Scroll mode */
	payload = (u16)0x1;
	ret = fmc_send_cmd(fmdev, DISPLAY_MODE, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक set_rds_data_mode(काष्ठा fmdev *fmdev, u8 mode)
अणु
	u16 payload;
	पूर्णांक ret;

	/* Setting unique PI TODO: how unique? */
	payload = (u16)0xcafe;
	ret = fmc_send_cmd(fmdev, PI_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Set decoder id */
	payload = (u16)0xa;
	ret = fmc_send_cmd(fmdev, DI_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* TODO: RDS_MODE_GET? */
	वापस 0;
पूर्ण

अटल पूर्णांक set_rds_len(काष्ठा fmdev *fmdev, u8 type, u16 len)
अणु
	u16 payload;
	पूर्णांक ret;

	len |= type << 8;
	payload = len;
	ret = fmc_send_cmd(fmdev, RDS_CONFIG_DATA_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* TODO: LENGTH_GET? */
	वापस 0;
पूर्ण

पूर्णांक fm_tx_set_rds_mode(काष्ठा fmdev *fmdev, u8 rds_en_dis)
अणु
	u16 payload;
	पूर्णांक ret;
	u8 rds_text[] = "Zoom2\n";

	fmdbg("rds_en_dis:%d(E:%d, D:%d)\n", rds_en_dis,
		   FM_RDS_ENABLE, FM_RDS_DISABLE);

	अगर (rds_en_dis == FM_RDS_ENABLE) अणु
		/* Set RDS length */
		set_rds_len(fmdev, 0, म_माप(rds_text));

		/* Set RDS text */
		set_rds_text(fmdev, rds_text);

		/* Set RDS mode */
		set_rds_data_mode(fmdev, 0x0);
	पूर्ण

	/* Send command to enable RDS */
	अगर (rds_en_dis == FM_RDS_ENABLE)
		payload = 0x01;
	अन्यथा
		payload = 0x00;

	ret = fmc_send_cmd(fmdev, RDS_DATA_ENB, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	अगर (rds_en_dis == FM_RDS_ENABLE) अणु
		/* Set RDS length */
		set_rds_len(fmdev, 0, म_माप(rds_text));

		/* Set RDS text */
		set_rds_text(fmdev, rds_text);
	पूर्ण
	fmdev->tx_data.rds.flag = rds_en_dis;

	वापस 0;
पूर्ण

पूर्णांक fm_tx_set_radio_text(काष्ठा fmdev *fmdev, u8 *rds_text, u8 rds_type)
अणु
	u16 payload;
	पूर्णांक ret;

	अगर (fmdev->curr_fmmode != FM_MODE_TX)
		वापस -EPERM;

	fm_tx_set_rds_mode(fmdev, 0);

	/* Set RDS length */
	set_rds_len(fmdev, rds_type, म_माप(rds_text));

	/* Set RDS text */
	set_rds_text(fmdev, rds_text);

	/* Set RDS mode */
	set_rds_data_mode(fmdev, 0x0);

	payload = 1;
	ret = fmc_send_cmd(fmdev, RDS_DATA_ENB, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक fm_tx_set_af(काष्ठा fmdev *fmdev, u32 af)
अणु
	u16 payload;
	पूर्णांक ret;

	अगर (fmdev->curr_fmmode != FM_MODE_TX)
		वापस -EPERM;

	fmdbg("AF: %d\n", af);

	af = (af - 87500) / 100;
	payload = (u16)af;
	ret = fmc_send_cmd(fmdev, TA_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक fm_tx_set_region(काष्ठा fmdev *fmdev, u8 region)
अणु
	u16 payload;
	पूर्णांक ret;

	अगर (region != FM_BAND_EUROPE_US && region != FM_BAND_JAPAN) अणु
		fmerr("Invalid band\n");
		वापस -EINVAL;
	पूर्ण

	/* Send command to set the band */
	payload = (u16)region;
	ret = fmc_send_cmd(fmdev, TX_BAND_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक fm_tx_set_mute_mode(काष्ठा fmdev *fmdev, u8 mute_mode_toset)
अणु
	u16 payload;
	पूर्णांक ret;

	fmdbg("tx: mute mode %d\n", mute_mode_toset);

	payload = mute_mode_toset;
	ret = fmc_send_cmd(fmdev, MUTE, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/* Set TX Audio I/O */
अटल पूर्णांक set_audio_io(काष्ठा fmdev *fmdev)
अणु
	काष्ठा fmtx_data *tx = &fmdev->tx_data;
	u16 payload;
	पूर्णांक ret;

	/* Set Audio I/O Enable */
	payload = tx->audio_io;
	ret = fmc_send_cmd(fmdev, AUDIO_IO_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* TODO: is audio set? */
	वापस 0;
पूर्ण

/* Start TX Transmission */
अटल पूर्णांक enable_xmit(काष्ठा fmdev *fmdev, u8 new_xmit_state)
अणु
	काष्ठा fmtx_data *tx = &fmdev->tx_data;
	अचिन्हित दीर्घ समयleft;
	u16 payload;
	पूर्णांक ret;

	/* Enable POWER_ENB पूर्णांकerrupts */
	payload = FM_POW_ENB_EVENT;
	ret = fmc_send_cmd(fmdev, INT_MASK_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Set Power Enable */
	payload = new_xmit_state;
	ret = fmc_send_cmd(fmdev, POWER_ENB_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* Wait क्रम Power Enabled */
	init_completion(&fmdev->मुख्यtask_comp);
	समयleft = रुको_क्रम_completion_समयout(&fmdev->मुख्यtask_comp,
			FM_DRV_TX_TIMEOUT);
	अगर (!समयleft) अणु
		fmerr("Timeout(%d sec),didn't get tune ended interrupt\n",
			   jअगरfies_to_msecs(FM_DRV_TX_TIMEOUT) / 1000);
		वापस -ETIMEDOUT;
	पूर्ण

	set_bit(FM_CORE_TX_XMITING, &fmdev->flag);
	tx->xmit_state = new_xmit_state;

	वापस 0;
पूर्ण

/* Set TX घातer level */
पूर्णांक fm_tx_set_pwr_lvl(काष्ठा fmdev *fmdev, u8 new_pwr_lvl)
अणु
	u16 payload;
	काष्ठा fmtx_data *tx = &fmdev->tx_data;
	पूर्णांक ret;

	अगर (fmdev->curr_fmmode != FM_MODE_TX)
		वापस -EPERM;
	fmdbg("tx: pwr_level_to_set %ld\n", (दीर्घ पूर्णांक)new_pwr_lvl);

	/* If the core isn't पढ़ोy update global variable */
	अगर (!test_bit(FM_CORE_READY, &fmdev->flag)) अणु
		tx->pwr_lvl = new_pwr_lvl;
		वापस 0;
	पूर्ण

	/* Set घातer level: Application will specअगरy घातer level value in
	 * units of dB/uV, whereas range and step are specअगरic to FM chip.
	 * For TI's WL chips, convert application specअगरied घातer level value
	 * to chip specअगरic value by subtracting 122 from it. Refer to TI FM
	 * data sheet क्रम details.
	 * */

	payload = (FM_PWR_LVL_HIGH - new_pwr_lvl);
	ret = fmc_send_cmd(fmdev, POWER_LEV_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* TODO: is the घातer level set? */
	tx->pwr_lvl = new_pwr_lvl;

	वापस 0;
पूर्ण

/*
 * Sets FM TX pre-emphasis filter value (OFF, 50us, or 75us)
 * Convert V4L2 specअगरied filter values to chip specअगरic filter values.
 */
पूर्णांक fm_tx_set_preemph_filter(काष्ठा fmdev *fmdev, u32 preemphasis)
अणु
	काष्ठा fmtx_data *tx = &fmdev->tx_data;
	u16 payload;
	पूर्णांक ret;

	अगर (fmdev->curr_fmmode != FM_MODE_TX)
		वापस -EPERM;

	चयन (preemphasis) अणु
	हाल V4L2_PREEMPHASIS_DISABLED:
		payload = FM_TX_PREEMPH_OFF;
		अवरोध;
	हाल V4L2_PREEMPHASIS_50_uS:
		payload = FM_TX_PREEMPH_50US;
		अवरोध;
	हाल V4L2_PREEMPHASIS_75_uS:
		payload = FM_TX_PREEMPH_75US;
		अवरोध;
	पूर्ण

	ret = fmc_send_cmd(fmdev, PREMPH_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	tx->preemph = payload;

	वापस ret;
पूर्ण

/* Get the TX tuning capacitor value.*/
पूर्णांक fm_tx_get_tune_cap_val(काष्ठा fmdev *fmdev)
अणु
	u16 curr_val;
	u32 resp_len;
	पूर्णांक ret;

	अगर (fmdev->curr_fmmode != FM_MODE_TX)
		वापस -EPERM;

	ret = fmc_send_cmd(fmdev, READ_FMANT_TUNE_VALUE, REG_RD,
			शून्य, माप(curr_val), &curr_val, &resp_len);
	अगर (ret < 0)
		वापस ret;

	curr_val = be16_to_cpu((__क्रमce __be16)curr_val);

	वापस curr_val;
पूर्ण

/* Set TX Frequency */
पूर्णांक fm_tx_set_freq(काष्ठा fmdev *fmdev, u32 freq_to_set)
अणु
	काष्ठा fmtx_data *tx = &fmdev->tx_data;
	u16 payload, chanl_index;
	पूर्णांक ret;

	अगर (test_bit(FM_CORE_TX_XMITING, &fmdev->flag)) अणु
		enable_xmit(fmdev, 0);
		clear_bit(FM_CORE_TX_XMITING, &fmdev->flag);
	पूर्ण

	/* Enable FR, BL पूर्णांकerrupts */
	payload = (FM_FR_EVENT | FM_BL_EVENT);
	ret = fmc_send_cmd(fmdev, INT_MASK_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	tx->tx_frq = (अचिन्हित दीर्घ)freq_to_set;
	fmdbg("tx: freq_to_set %ld\n", (दीर्घ पूर्णांक)tx->tx_frq);

	chanl_index = freq_to_set / 10;

	/* Set current tuner channel */
	payload = chanl_index;
	ret = fmc_send_cmd(fmdev, CHANL_SET, REG_WR, &payload,
			माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	fm_tx_set_pwr_lvl(fmdev, tx->pwr_lvl);
	fm_tx_set_preemph_filter(fmdev, tx->preemph);

	tx->audio_io = 0x01;	/* I2S */
	set_audio_io(fmdev);

	enable_xmit(fmdev, 0x01);	/* Enable transmission */

	tx->aud_mode = FM_STEREO_MODE;
	tx->rds.flag = FM_RDS_DISABLE;

	वापस 0;
पूर्ण

