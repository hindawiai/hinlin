<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Frontend part of the Linux driver क्रम the Afatech 9005
 * USB1.1 DVB-T receiver.
 *
 * Copyright (C) 2007 Luca Olivetti (luca@ventoso.org)
 *
 * Thanks to Afatech who kindly provided inक्रमmation.
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "af9005.h"
#समावेश "af9005-script.h"
#समावेश "mt2060.h"
#समावेश "qt1010.h"
#समावेश <यंत्र/भाग64.h>

काष्ठा af9005_fe_state अणु
	काष्ठा dvb_usb_device *d;
	क्रमागत fe_status stat;

	/* retraining parameters */
	u32 original_fcw;
	u16 original_rf_top;
	u16 original_अगर_top;
	u16 original_अगर_min;
	u16 original_aci0_अगर_top;
	u16 original_aci1_अगर_top;
	u16 original_aci0_अगर_min;
	u8 original_अगर_unplug_th;
	u8 original_rf_unplug_th;
	u8 original_dtop_अगर_unplug_th;
	u8 original_dtop_rf_unplug_th;

	/* statistics */
	u32 pre_vit_error_count;
	u32 pre_vit_bit_count;
	u32 ber;
	u32 post_vit_error_count;
	u32 post_vit_bit_count;
	u32 unc;
	u16 पात_count;

	पूर्णांक खोलोed;
	पूर्णांक strong;
	अचिन्हित दीर्घ next_status_check;
	काष्ठा dvb_frontend frontend;
पूर्ण;

अटल पूर्णांक af9005_ग_लिखो_word_agc(काष्ठा dvb_usb_device *d, u16 reghi,
				 u16 reglo, u8 pos, u8 len, u16 value)
अणु
	पूर्णांक ret;

	अगर ((ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, reglo, (u8) (value & 0xff))))
		वापस ret;
	वापस af9005_ग_लिखो_रेजिस्टर_bits(d, reghi, pos, len,
					  (u8) ((value & 0x300) >> 8));
पूर्ण

अटल पूर्णांक af9005_पढ़ो_word_agc(काष्ठा dvb_usb_device *d, u16 reghi,
				u16 reglo, u8 pos, u8 len, u16 * value)
अणु
	पूर्णांक ret;
	u8 temp0, temp1;

	अगर ((ret = af9005_पढ़ो_ofdm_रेजिस्टर(d, reglo, &temp0)))
		वापस ret;
	अगर ((ret = af9005_पढ़ो_ofdm_रेजिस्टर(d, reghi, &temp1)))
		वापस ret;
	चयन (pos) अणु
	हाल 0:
		*value = ((u16) (temp1 & 0x03) << 8) + (u16) temp0;
		अवरोध;
	हाल 2:
		*value = ((u16) (temp1 & 0x0C) << 6) + (u16) temp0;
		अवरोध;
	हाल 4:
		*value = ((u16) (temp1 & 0x30) << 4) + (u16) temp0;
		अवरोध;
	हाल 6:
		*value = ((u16) (temp1 & 0xC0) << 2) + (u16) temp0;
		अवरोध;
	शेष:
		err("invalid pos in read word agc");
		वापस -EINVAL;
	पूर्ण
	वापस 0;

पूर्ण

अटल पूर्णांक af9005_is_fecmon_available(काष्ठा dvb_frontend *fe, पूर्णांक *available)
अणु
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 temp;

	*available = false;

	ret = af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_p_fec_vtb_rsd_mon_en,
					fec_vtb_rsd_mon_en_pos,
					fec_vtb_rsd_mon_en_len, &temp);
	अगर (ret)
		वापस ret;
	अगर (temp & 1) अणु
		ret =
		    af9005_पढ़ो_रेजिस्टर_bits(state->d,
					      xd_p_reg_ofsm_पढ़ो_rbc_en,
					      reg_ofsm_पढ़ो_rbc_en_pos,
					      reg_ofsm_पढ़ो_rbc_en_len, &temp);
		अगर (ret)
			वापस ret;
		अगर ((temp & 1) == 0)
			*available = true;

	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_get_post_vit_err_cw_count(काष्ठा dvb_frontend *fe,
					    u32 * post_err_count,
					    u32 * post_cw_count,
					    u16 * पात_count)
अणु
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u32 err_count;
	u32 cw_count;
	u8 temp, temp0, temp1, temp2;
	u16 loc_पात_count;

	*post_err_count = 0;
	*post_cw_count = 0;

	/* check अगर error bit count is पढ़ोy */
	ret =
	    af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_r_fec_rsd_ber_rdy,
				      fec_rsd_ber_rdy_pos, fec_rsd_ber_rdy_len,
				      &temp);
	अगर (ret)
		वापस ret;
	अगर (!temp) अणु
		deb_info("rsd counter not ready\n");
		वापस 100;
	पूर्ण
	/* get पात count */
	ret =
	    af9005_पढ़ो_ofdm_रेजिस्टर(state->d,
				      xd_r_fec_rsd_पात_packet_cnt_7_0,
				      &temp0);
	अगर (ret)
		वापस ret;
	ret =
	    af9005_पढ़ो_ofdm_रेजिस्टर(state->d,
				      xd_r_fec_rsd_पात_packet_cnt_15_8,
				      &temp1);
	अगर (ret)
		वापस ret;
	loc_पात_count = ((u16) temp1 << 8) + temp0;

	/* get error count */
	ret =
	    af9005_पढ़ो_ofdm_रेजिस्टर(state->d, xd_r_fec_rsd_bit_err_cnt_7_0,
				      &temp0);
	अगर (ret)
		वापस ret;
	ret =
	    af9005_पढ़ो_ofdm_रेजिस्टर(state->d, xd_r_fec_rsd_bit_err_cnt_15_8,
				      &temp1);
	अगर (ret)
		वापस ret;
	ret =
	    af9005_पढ़ो_ofdm_रेजिस्टर(state->d, xd_r_fec_rsd_bit_err_cnt_23_16,
				      &temp2);
	अगर (ret)
		वापस ret;
	err_count = ((u32) temp2 << 16) + ((u32) temp1 << 8) + temp0;
	*post_err_count = err_count - (u32) loc_पात_count *8 * 8;

	/* get RSD packet number */
	ret =
	    af9005_पढ़ो_ofdm_रेजिस्टर(state->d, xd_p_fec_rsd_packet_unit_7_0,
				      &temp0);
	अगर (ret)
		वापस ret;
	ret =
	    af9005_पढ़ो_ofdm_रेजिस्टर(state->d, xd_p_fec_rsd_packet_unit_15_8,
				      &temp1);
	अगर (ret)
		वापस ret;
	cw_count = ((u32) temp1 << 8) + temp0;
	अगर (cw_count == 0) अणु
		err("wrong RSD packet count");
		वापस -EIO;
	पूर्ण
	deb_info("POST abort count %d err count %d rsd packets %d\n",
		 loc_पात_count, err_count, cw_count);
	*post_cw_count = cw_count - (u32) loc_पात_count;
	*पात_count = loc_पात_count;
	वापस 0;

पूर्ण

अटल पूर्णांक af9005_get_post_vit_ber(काष्ठा dvb_frontend *fe,
				   u32 * post_err_count, u32 * post_cw_count,
				   u16 * पात_count)
अणु
	u32 loc_cw_count = 0, loc_err_count;
	u16 loc_पात_count = 0;
	पूर्णांक ret;

	ret =
	    af9005_get_post_vit_err_cw_count(fe, &loc_err_count, &loc_cw_count,
					     &loc_पात_count);
	अगर (ret)
		वापस ret;
	*post_err_count = loc_err_count;
	*post_cw_count = loc_cw_count * 204 * 8;
	*पात_count = loc_पात_count;

	वापस 0;
पूर्ण

अटल पूर्णांक af9005_get_pre_vit_err_bit_count(काष्ठा dvb_frontend *fe,
					    u32 * pre_err_count,
					    u32 * pre_bit_count)
अणु
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;
	u8 temp, temp0, temp1, temp2;
	u32 super_frame_count, x, bits;
	पूर्णांक ret;

	ret =
	    af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_r_fec_vtb_ber_rdy,
				      fec_vtb_ber_rdy_pos, fec_vtb_ber_rdy_len,
				      &temp);
	अगर (ret)
		वापस ret;
	अगर (!temp) अणु
		deb_info("viterbi counter not ready\n");
		वापस 101;	/* ERR_APO_VTB_COUNTER_NOT_READY; */
	पूर्ण
	ret =
	    af9005_पढ़ो_ofdm_रेजिस्टर(state->d, xd_r_fec_vtb_err_bit_cnt_7_0,
				      &temp0);
	अगर (ret)
		वापस ret;
	ret =
	    af9005_पढ़ो_ofdm_रेजिस्टर(state->d, xd_r_fec_vtb_err_bit_cnt_15_8,
				      &temp1);
	अगर (ret)
		वापस ret;
	ret =
	    af9005_पढ़ो_ofdm_रेजिस्टर(state->d, xd_r_fec_vtb_err_bit_cnt_23_16,
				      &temp2);
	अगर (ret)
		वापस ret;
	*pre_err_count = ((u32) temp2 << 16) + ((u32) temp1 << 8) + temp0;

	ret =
	    af9005_पढ़ो_ofdm_रेजिस्टर(state->d, xd_p_fec_super_frm_unit_7_0,
				      &temp0);
	अगर (ret)
		वापस ret;
	ret =
	    af9005_पढ़ो_ofdm_रेजिस्टर(state->d, xd_p_fec_super_frm_unit_15_8,
				      &temp1);
	अगर (ret)
		वापस ret;
	super_frame_count = ((u32) temp1 << 8) + temp0;
	अगर (super_frame_count == 0) अणु
		deb_info("super frame count 0\n");
		वापस 102;
	पूर्ण

	/* पढ़ो fft mode */
	ret =
	    af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_g_reg_tpsd_txmod,
				      reg_tpsd_txmod_pos, reg_tpsd_txmod_len,
				      &temp);
	अगर (ret)
		वापस ret;
	अगर (temp == 0) अणु
		/* 2K */
		x = 1512;
	पूर्ण अन्यथा अगर (temp == 1) अणु
		/* 8k */
		x = 6048;
	पूर्ण अन्यथा अणु
		err("Invalid fft mode");
		वापस -EINVAL;
	पूर्ण

	/* पढ़ो modulation mode */
	ret =
	    af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_g_reg_tpsd_स्थिर,
				      reg_tpsd_स्थिर_pos, reg_tpsd_स्थिर_len,
				      &temp);
	अगर (ret)
		वापस ret;
	चयन (temp) अणु
	हाल 0:		/* QPSK */
		bits = 2;
		अवरोध;
	हाल 1:		/* QAM_16 */
		bits = 4;
		अवरोध;
	हाल 2:		/* QAM_64 */
		bits = 6;
		अवरोध;
	शेष:
		err("invalid modulation mode");
		वापस -EINVAL;
	पूर्ण
	*pre_bit_count = super_frame_count * 68 * 4 * x * bits;
	deb_info("PRE err count %d frame count %d bit count %d\n",
		 *pre_err_count, super_frame_count, *pre_bit_count);
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_reset_pre_viterbi(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	/* set super frame count to 1 */
	ret =
	    af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, xd_p_fec_super_frm_unit_7_0,
				       1 & 0xff);
	अगर (ret)
		वापस ret;
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, xd_p_fec_super_frm_unit_15_8,
					 1 >> 8);
	अगर (ret)
		वापस ret;
	/* reset pre viterbi error count */
	ret =
	    af9005_ग_लिखो_रेजिस्टर_bits(state->d, xd_p_fec_vtb_ber_rst,
				       fec_vtb_ber_rst_pos, fec_vtb_ber_rst_len,
				       1);

	वापस ret;
पूर्ण

अटल पूर्णांक af9005_reset_post_viterbi(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	/* set packet unit */
	ret =
	    af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, xd_p_fec_rsd_packet_unit_7_0,
				       10000 & 0xff);
	अगर (ret)
		वापस ret;
	ret =
	    af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, xd_p_fec_rsd_packet_unit_15_8,
				       10000 >> 8);
	अगर (ret)
		वापस ret;
	/* reset post viterbi error count */
	ret =
	    af9005_ग_लिखो_रेजिस्टर_bits(state->d, xd_p_fec_rsd_ber_rst,
				       fec_rsd_ber_rst_pos, fec_rsd_ber_rst_len,
				       1);

	वापस ret;
पूर्ण

अटल पूर्णांक af9005_get_statistic(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret, fecavailable;
	u64 numerator, denominator;

	deb_info("GET STATISTIC\n");
	ret = af9005_is_fecmon_available(fe, &fecavailable);
	अगर (ret)
		वापस ret;
	अगर (!fecavailable) अणु
		deb_info("fecmon not available\n");
		वापस 0;
	पूर्ण

	ret = af9005_get_pre_vit_err_bit_count(fe, &state->pre_vit_error_count,
					       &state->pre_vit_bit_count);
	अगर (ret == 0) अणु
		af9005_reset_pre_viterbi(fe);
		अगर (state->pre_vit_bit_count > 0) अणु
			/* according to v 0.0.4 of the dvb api ber should be a multiple
			   of 10E-9 so we have to multiply the error count by
			   10E9=1000000000 */
			numerator =
			    (u64) state->pre_vit_error_count * (u64) 1000000000;
			denominator = (u64) state->pre_vit_bit_count;
			state->ber = करो_भाग(numerator, denominator);
		पूर्ण अन्यथा अणु
			state->ber = 0xffffffff;
		पूर्ण
	पूर्ण

	ret = af9005_get_post_vit_ber(fe, &state->post_vit_error_count,
				      &state->post_vit_bit_count,
				      &state->पात_count);
	अगर (ret == 0) अणु
		ret = af9005_reset_post_viterbi(fe);
		state->unc += state->पात_count;
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_fe_refresh_state(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;
	अगर (समय_after(jअगरfies, state->next_status_check)) अणु
		deb_info("REFRESH STATE\n");

		/* statistics */
		अगर (af9005_get_statistic(fe))
			err("get_statistic_failed");
		state->next_status_check = jअगरfies + 250 * HZ / 1000;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_fe_पढ़ो_status(काष्ठा dvb_frontend *fe,
				 क्रमागत fe_status *stat)
अणु
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;
	u8 temp;
	पूर्णांक ret;

	अगर (fe->ops.tuner_ops.release == शून्य)
		वापस -ENODEV;

	*stat = 0;
	ret = af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_p_agc_lock,
					agc_lock_pos, agc_lock_len, &temp);
	अगर (ret)
		वापस ret;
	अगर (temp)
		*stat |= FE_HAS_SIGNAL;

	ret = af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_p_fd_tpsd_lock,
					fd_tpsd_lock_pos, fd_tpsd_lock_len,
					&temp);
	अगर (ret)
		वापस ret;
	अगर (temp)
		*stat |= FE_HAS_CARRIER;

	ret = af9005_पढ़ो_रेजिस्टर_bits(state->d,
					xd_r_mp2अगर_sync_byte_locked,
					mp2अगर_sync_byte_locked_pos,
					mp2अगर_sync_byte_locked_pos, &temp);
	अगर (ret)
		वापस ret;
	अगर (temp)
		*stat |= FE_HAS_SYNC | FE_HAS_VITERBI | FE_HAS_LOCK;
	अगर (state->खोलोed)
		af9005_led_control(state->d, *stat & FE_HAS_LOCK);

	ret =
	    af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_p_reg_strong_sginal_detected,
				      reg_strong_sginal_detected_pos,
				      reg_strong_sginal_detected_len, &temp);
	अगर (ret)
		वापस ret;
	अगर (temp != state->strong) अणु
		deb_info("adjust for strong signal %d\n", temp);
		state->strong = temp;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_fe_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 * ber)
अणु
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;
	अगर (fe->ops.tuner_ops.release  == शून्य)
		वापस -ENODEV;
	af9005_fe_refresh_state(fe);
	*ber = state->ber;
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_fe_पढ़ो_unc_blocks(काष्ठा dvb_frontend *fe, u32 * unc)
अणु
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;
	अगर (fe->ops.tuner_ops.release == शून्य)
		वापस -ENODEV;
	af9005_fe_refresh_state(fe);
	*unc = state->unc;
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_fe_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
					  u16 * strength)
अणु
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 अगर_gain, rf_gain;

	अगर (fe->ops.tuner_ops.release == शून्य)
		वापस -ENODEV;
	ret =
	    af9005_पढ़ो_ofdm_रेजिस्टर(state->d, xd_r_reg_aagc_rf_gain,
				      &rf_gain);
	अगर (ret)
		वापस ret;
	ret =
	    af9005_पढ़ो_ofdm_रेजिस्टर(state->d, xd_r_reg_aagc_अगर_gain,
				      &अगर_gain);
	अगर (ret)
		वापस ret;
	/* this value has no real meaning, but i करोn't have the tables that relate
	   the rf and अगर gain with the dbm, so I just scale the value */
	*strength = (512 - rf_gain - अगर_gain) << 7;
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_fe_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 * snr)
अणु
	/* the snr can be derived from the ber and the modulation
	   but I करोn't think this kind of complex calculations beदीर्घ
	   in the driver. I may be wrong.... */
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक af9005_fe_program_cfoe(काष्ठा dvb_usb_device *d, u32 bw)
अणु
	u8 temp0, temp1, temp2, temp3, buf[4];
	पूर्णांक ret;
	u32 NS_coeff1_2048Nu;
	u32 NS_coeff1_8191Nu;
	u32 NS_coeff1_8192Nu;
	u32 NS_coeff1_8193Nu;
	u32 NS_coeff2_2k;
	u32 NS_coeff2_8k;

	चयन (bw) अणु
	हाल 6000000:
		NS_coeff1_2048Nu = 0x2ADB6DC;
		NS_coeff1_8191Nu = 0xAB7313;
		NS_coeff1_8192Nu = 0xAB6DB7;
		NS_coeff1_8193Nu = 0xAB685C;
		NS_coeff2_2k = 0x156DB6E;
		NS_coeff2_8k = 0x55B6DC;
		अवरोध;

	हाल 7000000:
		NS_coeff1_2048Nu = 0x3200001;
		NS_coeff1_8191Nu = 0xC80640;
		NS_coeff1_8192Nu = 0xC80000;
		NS_coeff1_8193Nu = 0xC7F9C0;
		NS_coeff2_2k = 0x1900000;
		NS_coeff2_8k = 0x640000;
		अवरोध;

	हाल 8000000:
		NS_coeff1_2048Nu = 0x3924926;
		NS_coeff1_8191Nu = 0xE4996E;
		NS_coeff1_8192Nu = 0xE49249;
		NS_coeff1_8193Nu = 0xE48B25;
		NS_coeff2_2k = 0x1C92493;
		NS_coeff2_8k = 0x724925;
		अवरोध;
	शेष:
		err("Invalid bandwidth %d.", bw);
		वापस -EINVAL;
	पूर्ण

	/*
	 *  ग_लिखो NS_coeff1_2048Nu
	 */

	temp0 = (u8) (NS_coeff1_2048Nu & 0x000000FF);
	temp1 = (u8) ((NS_coeff1_2048Nu & 0x0000FF00) >> 8);
	temp2 = (u8) ((NS_coeff1_2048Nu & 0x00FF0000) >> 16);
	temp3 = (u8) ((NS_coeff1_2048Nu & 0x03000000) >> 24);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	/*  cfoe_NS_2k_coeff1_25_24 */
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE00, buf[0]);
	अगर (ret)
		वापस ret;

	/*  cfoe_NS_2k_coeff1_23_16 */
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE01, buf[1]);
	अगर (ret)
		वापस ret;

	/*  cfoe_NS_2k_coeff1_15_8 */
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE02, buf[2]);
	अगर (ret)
		वापस ret;

	/*  cfoe_NS_2k_coeff1_7_0 */
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE03, buf[3]);
	अगर (ret)
		वापस ret;

	/*
	 *  ग_लिखो NS_coeff2_2k
	 */

	temp0 = (u8) ((NS_coeff2_2k & 0x0000003F));
	temp1 = (u8) ((NS_coeff2_2k & 0x00003FC0) >> 6);
	temp2 = (u8) ((NS_coeff2_2k & 0x003FC000) >> 14);
	temp3 = (u8) ((NS_coeff2_2k & 0x01C00000) >> 22);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE04, buf[0]);
	अगर (ret)
		वापस ret;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE05, buf[1]);
	अगर (ret)
		वापस ret;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE06, buf[2]);
	अगर (ret)
		वापस ret;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE07, buf[3]);
	अगर (ret)
		वापस ret;

	/*
	 *  ग_लिखो NS_coeff1_8191Nu
	 */

	temp0 = (u8) ((NS_coeff1_8191Nu & 0x000000FF));
	temp1 = (u8) ((NS_coeff1_8191Nu & 0x0000FF00) >> 8);
	temp2 = (u8) ((NS_coeff1_8191Nu & 0x00FFC000) >> 16);
	temp3 = (u8) ((NS_coeff1_8191Nu & 0x03000000) >> 24);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE08, buf[0]);
	अगर (ret)
		वापस ret;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE09, buf[1]);
	अगर (ret)
		वापस ret;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE0A, buf[2]);
	अगर (ret)
		वापस ret;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE0B, buf[3]);
	अगर (ret)
		वापस ret;

	/*
	 *  ग_लिखो NS_coeff1_8192Nu
	 */

	temp0 = (u8) (NS_coeff1_8192Nu & 0x000000FF);
	temp1 = (u8) ((NS_coeff1_8192Nu & 0x0000FF00) >> 8);
	temp2 = (u8) ((NS_coeff1_8192Nu & 0x00FFC000) >> 16);
	temp3 = (u8) ((NS_coeff1_8192Nu & 0x03000000) >> 24);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE0C, buf[0]);
	अगर (ret)
		वापस ret;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE0D, buf[1]);
	अगर (ret)
		वापस ret;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE0E, buf[2]);
	अगर (ret)
		वापस ret;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE0F, buf[3]);
	अगर (ret)
		वापस ret;

	/*
	 *  ग_लिखो NS_coeff1_8193Nu
	 */

	temp0 = (u8) ((NS_coeff1_8193Nu & 0x000000FF));
	temp1 = (u8) ((NS_coeff1_8193Nu & 0x0000FF00) >> 8);
	temp2 = (u8) ((NS_coeff1_8193Nu & 0x00FFC000) >> 16);
	temp3 = (u8) ((NS_coeff1_8193Nu & 0x03000000) >> 24);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE10, buf[0]);
	अगर (ret)
		वापस ret;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE11, buf[1]);
	अगर (ret)
		वापस ret;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE12, buf[2]);
	अगर (ret)
		वापस ret;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE13, buf[3]);
	अगर (ret)
		वापस ret;

	/*
	 *  ग_लिखो NS_coeff2_8k
	 */

	temp0 = (u8) ((NS_coeff2_8k & 0x0000003F));
	temp1 = (u8) ((NS_coeff2_8k & 0x00003FC0) >> 6);
	temp2 = (u8) ((NS_coeff2_8k & 0x003FC000) >> 14);
	temp3 = (u8) ((NS_coeff2_8k & 0x01C00000) >> 22);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE14, buf[0]);
	अगर (ret)
		वापस ret;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE15, buf[1]);
	अगर (ret)
		वापस ret;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE16, buf[2]);
	अगर (ret)
		वापस ret;

	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(d, 0xAE17, buf[3]);
	वापस ret;

पूर्ण

अटल पूर्णांक af9005_fe_select_bw(काष्ठा dvb_usb_device *d, u32 bw)
अणु
	u8 temp;
	चयन (bw) अणु
	हाल 6000000:
		temp = 0;
		अवरोध;
	हाल 7000000:
		temp = 1;
		अवरोध;
	हाल 8000000:
		temp = 2;
		अवरोध;
	शेष:
		err("Invalid bandwidth %d.", bw);
		वापस -EINVAL;
	पूर्ण
	वापस af9005_ग_लिखो_रेजिस्टर_bits(d, xd_g_reg_bw, reg_bw_pos,
					  reg_bw_len, temp);
पूर्ण

अटल पूर्णांक af9005_fe_घातer(काष्ठा dvb_frontend *fe, पूर्णांक on)
अणु
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;
	u8 temp = on;
	पूर्णांक ret;
	deb_info("power %s tuner\n", on ? "on" : "off");
	ret = af9005_send_command(state->d, 0x03, &temp, 1, शून्य, 0);
	वापस ret;
पूर्ण

अटल काष्ठा mt2060_config af9005_mt2060_config = अणु
	0xC0
पूर्ण;

अटल काष्ठा qt1010_config af9005_qt1010_config = अणु
	0xC4
पूर्ण;

अटल पूर्णांक af9005_fe_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	पूर्णांक ret, i, scriptlen;
	u8 temp, temp0 = 0, temp1 = 0, temp2 = 0;
	u8 buf[2];
	u16 अगर1;

	deb_info("in af9005_fe_init\n");

	/* reset */
	deb_info("reset\n");
	अगर ((ret =
	     af9005_ग_लिखो_रेजिस्टर_bits(state->d, xd_I2C_reg_ofdm_rst_en,
					4, 1, 0x01)))
		वापस ret;
	अगर ((ret = af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, APO_REG_RESET, 0)))
		वापस ret;
	/* clear ofdm reset */
	deb_info("clear ofdm reset\n");
	क्रम (i = 0; i < 150; i++) अणु
		अगर ((ret =
		     af9005_पढ़ो_ofdm_रेजिस्टर(state->d,
					       xd_I2C_reg_ofdm_rst, &temp)))
			वापस ret;
		अगर (temp & (regmask[reg_ofdm_rst_len - 1] << reg_ofdm_rst_pos))
			अवरोध;
		msleep(10);
	पूर्ण
	अगर (i == 150)
		वापस -ETIMEDOUT;

	/*FIXME in the dump
	   ग_लिखो B200 A9
	   ग_लिखो xd_g_reg_ofsm_clk 7
	   पढ़ो eepr c6 (2)
	   पढ़ो eepr c7 (2)
	   misc ctrl 3 -> 1
	   पढ़ो eepr ca (6)
	   ग_लिखो xd_g_reg_ofsm_clk 0
	   ग_लिखो B200 a1
	 */
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, 0xb200, 0xa9);
	अगर (ret)
		वापस ret;
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, xd_g_reg_ofsm_clk, 0x07);
	अगर (ret)
		वापस ret;
	temp = 0x01;
	ret = af9005_send_command(state->d, 0x03, &temp, 1, शून्य, 0);
	अगर (ret)
		वापस ret;
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, xd_g_reg_ofsm_clk, 0x00);
	अगर (ret)
		वापस ret;
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, 0xb200, 0xa1);
	अगर (ret)
		वापस ret;

	temp = regmask[reg_ofdm_rst_len - 1] << reg_ofdm_rst_pos;
	अगर ((ret =
	     af9005_ग_लिखो_रेजिस्टर_bits(state->d, xd_I2C_reg_ofdm_rst,
					reg_ofdm_rst_pos, reg_ofdm_rst_len, 1)))
		वापस ret;
	ret = af9005_ग_लिखो_रेजिस्टर_bits(state->d, xd_I2C_reg_ofdm_rst,
					 reg_ofdm_rst_pos, reg_ofdm_rst_len, 0);

	अगर (ret)
		वापस ret;
	/* करोn't know what रेजिस्टर aefc is, but this is what the winकरोws driver करोes */
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, 0xaefc, 0);
	अगर (ret)
		वापस ret;

	/* set stand alone chip */
	deb_info("set stand alone chip\n");
	अगर ((ret =
	     af9005_ग_लिखो_रेजिस्टर_bits(state->d, xd_p_reg_dca_stand_alone,
					reg_dca_stand_alone_pos,
					reg_dca_stand_alone_len, 1)))
		वापस ret;

	/* set dca upper & lower chip */
	deb_info("set dca upper & lower chip\n");
	अगर ((ret =
	     af9005_ग_लिखो_रेजिस्टर_bits(state->d, xd_p_reg_dca_upper_chip,
					reg_dca_upper_chip_pos,
					reg_dca_upper_chip_len, 0)))
		वापस ret;
	अगर ((ret =
	     af9005_ग_लिखो_रेजिस्टर_bits(state->d, xd_p_reg_dca_lower_chip,
					reg_dca_lower_chip_pos,
					reg_dca_lower_chip_len, 0)))
		वापस ret;

	/* set 2wire master घड़ी to 0x14 (क्रम 60KHz) */
	deb_info("set 2wire master clock to 0x14 (for 60KHz)\n");
	अगर ((ret =
	     af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, xd_I2C_i2c_m_period, 0x14)))
		वापस ret;

	/* clear dca enable chip */
	deb_info("clear dca enable chip\n");
	अगर ((ret =
	     af9005_ग_लिखो_रेजिस्टर_bits(state->d, xd_p_reg_dca_en,
					reg_dca_en_pos, reg_dca_en_len, 0)))
		वापस ret;
	/* FIXME these are रेजिस्टर bits, but I करोn't know which ones */
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, 0xa16c, 1);
	अगर (ret)
		वापस ret;
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, 0xa3c1, 0);
	अगर (ret)
		वापस ret;

	/* init other parameters: program cfoe and select bandwidth */
	deb_info("program cfoe\n");
	ret = af9005_fe_program_cfoe(state->d, 6000000);
	अगर (ret)
		वापस ret;
	/* set पढ़ो-update bit क्रम modulation */
	deb_info("set read-update bit for modulation\n");
	अगर ((ret =
	     af9005_ग_लिखो_रेजिस्टर_bits(state->d, xd_p_reg_feq_पढ़ो_update,
					reg_feq_पढ़ो_update_pos,
					reg_feq_पढ़ो_update_len, 1)))
		वापस ret;

	/* sample code has a set MPEG TS code here
	   but snअगरfing reveals that it करोesn't करो it */

	/* set पढ़ो-update bit to 1 क्रम DCA modulation */
	deb_info("set read-update bit 1 for DCA modulation\n");
	अगर ((ret =
	     af9005_ग_लिखो_रेजिस्टर_bits(state->d, xd_p_reg_dca_पढ़ो_update,
					reg_dca_पढ़ो_update_pos,
					reg_dca_पढ़ो_update_len, 1)))
		वापस ret;

	/* enable fec monitor */
	deb_info("enable fec monitor\n");
	अगर ((ret =
	     af9005_ग_लिखो_रेजिस्टर_bits(state->d, xd_p_fec_vtb_rsd_mon_en,
					fec_vtb_rsd_mon_en_pos,
					fec_vtb_rsd_mon_en_len, 1)))
		वापस ret;

	/* FIXME should be रेजिस्टर bits, I करोn't know which ones */
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, 0xa601, 0);

	/* set api_retrain_never_मुक्तze */
	deb_info("set api_retrain_never_freeze\n");
	अगर ((ret = af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, 0xaefb, 0x01)))
		वापस ret;

	/* load init script */
	deb_info("load init script\n");
	scriptlen = माप(script) / माप(RegDesc);
	क्रम (i = 0; i < scriptlen; i++) अणु
		अगर ((ret =
		     af9005_ग_लिखो_रेजिस्टर_bits(state->d, script[i].reg,
						script[i].pos,
						script[i].len, script[i].val)))
			वापस ret;
		/* save 3 bytes of original fcw */
		अगर (script[i].reg == 0xae18)
			temp2 = script[i].val;
		अगर (script[i].reg == 0xae19)
			temp1 = script[i].val;
		अगर (script[i].reg == 0xae1a)
			temp0 = script[i].val;

		/* save original unplug threshold */
		अगर (script[i].reg == xd_p_reg_unplug_th)
			state->original_अगर_unplug_th = script[i].val;
		अगर (script[i].reg == xd_p_reg_unplug_rf_gain_th)
			state->original_rf_unplug_th = script[i].val;
		अगर (script[i].reg == xd_p_reg_unplug_dtop_अगर_gain_th)
			state->original_dtop_अगर_unplug_th = script[i].val;
		अगर (script[i].reg == xd_p_reg_unplug_dtop_rf_gain_th)
			state->original_dtop_rf_unplug_th = script[i].val;

	पूर्ण
	state->original_fcw =
	    ((u32) temp2 << 16) + ((u32) temp1 << 8) + (u32) temp0;


	/* save original TOPs */
	deb_info("save original TOPs\n");

	/*  RF TOP */
	ret =
	    af9005_पढ़ो_word_agc(state->d,
				 xd_p_reg_aagc_rf_top_numerator_9_8,
				 xd_p_reg_aagc_rf_top_numerator_7_0, 0, 2,
				 &state->original_rf_top);
	अगर (ret)
		वापस ret;

	/*  IF TOP */
	ret =
	    af9005_पढ़ो_word_agc(state->d,
				 xd_p_reg_aagc_अगर_top_numerator_9_8,
				 xd_p_reg_aagc_अगर_top_numerator_7_0, 0, 2,
				 &state->original_अगर_top);
	अगर (ret)
		वापस ret;

	/*  ACI 0 IF TOP */
	ret =
	    af9005_पढ़ो_word_agc(state->d, 0xA60E, 0xA60A, 4, 2,
				 &state->original_aci0_अगर_top);
	अगर (ret)
		वापस ret;

	/*  ACI 1 IF TOP */
	ret =
	    af9005_पढ़ो_word_agc(state->d, 0xA60E, 0xA60B, 6, 2,
				 &state->original_aci1_अगर_top);
	अगर (ret)
		वापस ret;

	/* attach tuner and init */
	अगर (fe->ops.tuner_ops.release == शून्य) अणु
		/* पढ़ो tuner and board id from eeprom */
		ret = af9005_पढ़ो_eeprom(adap->dev, 0xc6, buf, 2);
		अगर (ret) अणु
			err("Impossible to read EEPROM\n");
			वापस ret;
		पूर्ण
		deb_info("Tuner id %d, board id %d\n", buf[0], buf[1]);
		चयन (buf[0]) अणु
		हाल 2:	/* MT2060 */
			/* पढ़ो अगर1 from eeprom */
			ret = af9005_पढ़ो_eeprom(adap->dev, 0xc8, buf, 2);
			अगर (ret) अणु
				err("Impossible to read EEPROM\n");
				वापस ret;
			पूर्ण
			अगर1 = (u16) (buf[0] << 8) + buf[1];
			अगर (dvb_attach(mt2060_attach, fe, &adap->dev->i2c_adap,
					 &af9005_mt2060_config, अगर1) == शून्य) अणु
				deb_info("MT2060 attach failed\n");
				वापस -ENODEV;
			पूर्ण
			अवरोध;
		हाल 3:	/* QT1010 */
		हाल 9:	/* QT1010B */
			अगर (dvb_attach(qt1010_attach, fe, &adap->dev->i2c_adap,
					&af9005_qt1010_config) ==शून्य) अणु
				deb_info("QT1010 attach failed\n");
				वापस -ENODEV;
			पूर्ण
			अवरोध;
		शेष:
			err("Unsupported tuner type %d", buf[0]);
			वापस -ENODEV;
		पूर्ण
		ret = fe->ops.tuner_ops.init(fe);
		अगर (ret)
			वापस ret;
	पूर्ण

	deb_info("profit!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_fe_sleep(काष्ठा dvb_frontend *fe)
अणु
	वापस af9005_fe_घातer(fe, 0);
पूर्ण

अटल पूर्णांक af9005_ts_bus_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक acquire)
अणु
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;

	अगर (acquire) अणु
		state->खोलोed++;
	पूर्ण अन्यथा अणु

		state->खोलोed--;
		अगर (!state->खोलोed)
			af9005_led_control(state->d, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक af9005_fe_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *fep = &fe->dtv_property_cache;
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 temp, temp0, temp1, temp2;

	deb_info("af9005_fe_set_frontend freq %d bw %d\n", fep->frequency,
		 fep->bandwidth_hz);
	अगर (fe->ops.tuner_ops.release == शून्य) अणु
		err("Tuner not attached");
		वापस -ENODEV;
	पूर्ण

	deb_info("turn off led\n");
	/* not in the log */
	ret = af9005_led_control(state->d, 0);
	अगर (ret)
		वापस ret;
	/* not sure about the bits */
	ret = af9005_ग_लिखो_रेजिस्टर_bits(state->d, XD_MP2IF_MISC, 2, 1, 0);
	अगर (ret)
		वापस ret;

	/* set FCW to शेष value */
	deb_info("set FCW to default value\n");
	temp0 = (u8) (state->original_fcw & 0x000000ff);
	temp1 = (u8) ((state->original_fcw & 0x0000ff00) >> 8);
	temp2 = (u8) ((state->original_fcw & 0x00ff0000) >> 16);
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, 0xae1a, temp0);
	अगर (ret)
		वापस ret;
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, 0xae19, temp1);
	अगर (ret)
		वापस ret;
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, 0xae18, temp2);
	अगर (ret)
		वापस ret;

	/* restore original TOPs */
	deb_info("restore original TOPs\n");
	ret =
	    af9005_ग_लिखो_word_agc(state->d,
				  xd_p_reg_aagc_rf_top_numerator_9_8,
				  xd_p_reg_aagc_rf_top_numerator_7_0, 0, 2,
				  state->original_rf_top);
	अगर (ret)
		वापस ret;
	ret =
	    af9005_ग_लिखो_word_agc(state->d,
				  xd_p_reg_aagc_अगर_top_numerator_9_8,
				  xd_p_reg_aagc_अगर_top_numerator_7_0, 0, 2,
				  state->original_अगर_top);
	अगर (ret)
		वापस ret;
	ret =
	    af9005_ग_लिखो_word_agc(state->d, 0xA60E, 0xA60A, 4, 2,
				  state->original_aci0_अगर_top);
	अगर (ret)
		वापस ret;
	ret =
	    af9005_ग_लिखो_word_agc(state->d, 0xA60E, 0xA60B, 6, 2,
				  state->original_aci1_अगर_top);
	अगर (ret)
		वापस ret;

	/* select bandwidth */
	deb_info("select bandwidth");
	ret = af9005_fe_select_bw(state->d, fep->bandwidth_hz);
	अगर (ret)
		वापस ret;
	ret = af9005_fe_program_cfoe(state->d, fep->bandwidth_hz);
	अगर (ret)
		वापस ret;

	/* clear easy mode flag */
	deb_info("clear easy mode flag\n");
	ret = af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, 0xaefd, 0);
	अगर (ret)
		वापस ret;

	/* set unplug threshold to original value */
	deb_info("set unplug threshold to original value\n");
	ret =
	    af9005_ग_लिखो_ofdm_रेजिस्टर(state->d, xd_p_reg_unplug_th,
				       state->original_अगर_unplug_th);
	अगर (ret)
		वापस ret;
	/* set tuner */
	deb_info("set tuner\n");
	ret = fe->ops.tuner_ops.set_params(fe);
	अगर (ret)
		वापस ret;

	/* trigger ofsm */
	deb_info("trigger ofsm\n");
	temp = 0;
	ret = af9005_ग_लिखो_tuner_रेजिस्टरs(state->d, 0xffff, &temp, 1);
	अगर (ret)
		वापस ret;

	/* clear retrain and मुक्तze flag */
	deb_info("clear retrain and freeze flag\n");
	ret =
	    af9005_ग_लिखो_रेजिस्टर_bits(state->d,
				       xd_p_reg_api_retrain_request,
				       reg_api_retrain_request_pos, 2, 0);
	अगर (ret)
		वापस ret;

	/* reset pre viterbi and post viterbi रेजिस्टरs and statistics */
	af9005_reset_pre_viterbi(fe);
	af9005_reset_post_viterbi(fe);
	state->pre_vit_error_count = 0;
	state->pre_vit_bit_count = 0;
	state->ber = 0;
	state->post_vit_error_count = 0;
	/* state->unc = 0; commented out since it should be ever increasing */
	state->पात_count = 0;

	state->next_status_check = jअगरfies;
	state->strong = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक af9005_fe_get_frontend(काष्ठा dvb_frontend *fe,
				  काष्ठा dtv_frontend_properties *fep)
अणु
	काष्ठा af9005_fe_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	u8 temp;

	/* mode */
	ret =
	    af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_g_reg_tpsd_स्थिर,
				      reg_tpsd_स्थिर_pos, reg_tpsd_स्थिर_len,
				      &temp);
	अगर (ret)
		वापस ret;
	deb_info("===== fe_get_frontend_legacy = =============\n");
	deb_info("CONSTELLATION ");
	चयन (temp) अणु
	हाल 0:
		fep->modulation = QPSK;
		deb_info("QPSK\n");
		अवरोध;
	हाल 1:
		fep->modulation = QAM_16;
		deb_info("QAM_16\n");
		अवरोध;
	हाल 2:
		fep->modulation = QAM_64;
		deb_info("QAM_64\n");
		अवरोध;
	पूर्ण

	/* tps hierarchy and alpha value */
	ret =
	    af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_g_reg_tpsd_hier,
				      reg_tpsd_hier_pos, reg_tpsd_hier_len,
				      &temp);
	अगर (ret)
		वापस ret;
	deb_info("HIERARCHY ");
	चयन (temp) अणु
	हाल 0:
		fep->hierarchy = HIERARCHY_NONE;
		deb_info("NONE\n");
		अवरोध;
	हाल 1:
		fep->hierarchy = HIERARCHY_1;
		deb_info("1\n");
		अवरोध;
	हाल 2:
		fep->hierarchy = HIERARCHY_2;
		deb_info("2\n");
		अवरोध;
	हाल 3:
		fep->hierarchy = HIERARCHY_4;
		deb_info("4\n");
		अवरोध;
	पूर्ण

	/*  high/low priority     */
	ret =
	    af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_g_reg_dec_pri,
				      reg_dec_pri_pos, reg_dec_pri_len, &temp);
	अगर (ret)
		वापस ret;
	/* अगर temp is set = high priority */
	deb_info("PRIORITY %s\n", temp ? "high" : "low");

	/* high coderate */
	ret =
	    af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_g_reg_tpsd_hpcr,
				      reg_tpsd_hpcr_pos, reg_tpsd_hpcr_len,
				      &temp);
	अगर (ret)
		वापस ret;
	deb_info("CODERATE HP ");
	चयन (temp) अणु
	हाल 0:
		fep->code_rate_HP = FEC_1_2;
		deb_info("FEC_1_2\n");
		अवरोध;
	हाल 1:
		fep->code_rate_HP = FEC_2_3;
		deb_info("FEC_2_3\n");
		अवरोध;
	हाल 2:
		fep->code_rate_HP = FEC_3_4;
		deb_info("FEC_3_4\n");
		अवरोध;
	हाल 3:
		fep->code_rate_HP = FEC_5_6;
		deb_info("FEC_5_6\n");
		अवरोध;
	हाल 4:
		fep->code_rate_HP = FEC_7_8;
		deb_info("FEC_7_8\n");
		अवरोध;
	पूर्ण

	/* low coderate */
	ret =
	    af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_g_reg_tpsd_lpcr,
				      reg_tpsd_lpcr_pos, reg_tpsd_lpcr_len,
				      &temp);
	अगर (ret)
		वापस ret;
	deb_info("CODERATE LP ");
	चयन (temp) अणु
	हाल 0:
		fep->code_rate_LP = FEC_1_2;
		deb_info("FEC_1_2\n");
		अवरोध;
	हाल 1:
		fep->code_rate_LP = FEC_2_3;
		deb_info("FEC_2_3\n");
		अवरोध;
	हाल 2:
		fep->code_rate_LP = FEC_3_4;
		deb_info("FEC_3_4\n");
		अवरोध;
	हाल 3:
		fep->code_rate_LP = FEC_5_6;
		deb_info("FEC_5_6\n");
		अवरोध;
	हाल 4:
		fep->code_rate_LP = FEC_7_8;
		deb_info("FEC_7_8\n");
		अवरोध;
	पूर्ण

	/* guard पूर्णांकerval */
	ret =
	    af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_g_reg_tpsd_gi,
				      reg_tpsd_gi_pos, reg_tpsd_gi_len, &temp);
	अगर (ret)
		वापस ret;
	deb_info("GUARD INTERVAL ");
	चयन (temp) अणु
	हाल 0:
		fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
		deb_info("1_32\n");
		अवरोध;
	हाल 1:
		fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
		deb_info("1_16\n");
		अवरोध;
	हाल 2:
		fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
		deb_info("1_8\n");
		अवरोध;
	हाल 3:
		fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
		deb_info("1_4\n");
		अवरोध;
	पूर्ण

	/* fft */
	ret =
	    af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_g_reg_tpsd_txmod,
				      reg_tpsd_txmod_pos, reg_tpsd_txmod_len,
				      &temp);
	अगर (ret)
		वापस ret;
	deb_info("TRANSMISSION MODE ");
	चयन (temp) अणु
	हाल 0:
		fep->transmission_mode = TRANSMISSION_MODE_2K;
		deb_info("2K\n");
		अवरोध;
	हाल 1:
		fep->transmission_mode = TRANSMISSION_MODE_8K;
		deb_info("8K\n");
		अवरोध;
	पूर्ण

	/* bandwidth      */
	ret =
	    af9005_पढ़ो_रेजिस्टर_bits(state->d, xd_g_reg_bw, reg_bw_pos,
				      reg_bw_len, &temp);
	deb_info("BANDWIDTH ");
	चयन (temp) अणु
	हाल 0:
		fep->bandwidth_hz = 6000000;
		deb_info("6\n");
		अवरोध;
	हाल 1:
		fep->bandwidth_hz = 7000000;
		deb_info("7\n");
		अवरोध;
	हाल 2:
		fep->bandwidth_hz = 8000000;
		deb_info("8\n");
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम af9005_fe_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा af9005_fe_state *state =
	    (काष्ठा af9005_fe_state *)fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops af9005_fe_ops;

काष्ठा dvb_frontend *af9005_fe_attach(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा af9005_fe_state *state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा af9005_fe_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	deb_info("attaching frontend af9005\n");

	state->d = d;
	state->खोलोed = 0;

	स_नकल(&state->frontend.ops, &af9005_fe_ops,
	       माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	वापस &state->frontend;
      error:
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops af9005_fe_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		 .name = "AF9005 USB DVB-T",
		 .frequency_min_hz =    44250 * kHz,
		 .frequency_max_hz =   867250 * kHz,
		 .frequency_stepsize_hz = 250 * kHz,
		 .caps = FE_CAN_INVERSION_AUTO |
		 FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		 FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		 FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 |
		 FE_CAN_QAM_AUTO | FE_CAN_TRANSMISSION_MODE_AUTO |
		 FE_CAN_GUARD_INTERVAL_AUTO | FE_CAN_RECOVER |
		 FE_CAN_HIERARCHY_AUTO,
		 पूर्ण,

	.release = af9005_fe_release,

	.init = af9005_fe_init,
	.sleep = af9005_fe_sleep,
	.ts_bus_ctrl = af9005_ts_bus_ctrl,

	.set_frontend = af9005_fe_set_frontend,
	.get_frontend = af9005_fe_get_frontend,

	.पढ़ो_status = af9005_fe_पढ़ो_status,
	.पढ़ो_ber = af9005_fe_पढ़ो_ber,
	.पढ़ो_संकेत_strength = af9005_fe_पढ़ो_संकेत_strength,
	.पढ़ो_snr = af9005_fe_पढ़ो_snr,
	.पढ़ो_ucblocks = af9005_fe_पढ़ो_unc_blocks,
पूर्ण;
