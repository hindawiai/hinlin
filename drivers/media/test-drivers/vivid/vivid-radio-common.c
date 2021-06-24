<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-radio-common.c - common radio rx/tx support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>

#समावेश "vivid-core.h"
#समावेश "vivid-ctrls.h"
#समावेश "vivid-radio-common.h"
#समावेश "vivid-rds-gen.h"

/*
 * These functions are shared between the vivid receiver and transmitter
 * since both use the same frequency bands.
 */

स्थिर काष्ठा v4l2_frequency_band vivid_radio_bands[TOT_BANDS] = अणु
	/* Band FM */
	अणु
		.type = V4L2_TUNER_RADIO,
		.index = 0,
		.capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			      V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   = FM_FREQ_RANGE_LOW,
		.rangehigh  = FM_FREQ_RANGE_HIGH,
		.modulation = V4L2_BAND_MODULATION_FM,
	पूर्ण,
	/* Band AM */
	अणु
		.type = V4L2_TUNER_RADIO,
		.index = 1,
		.capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   = AM_FREQ_RANGE_LOW,
		.rangehigh  = AM_FREQ_RANGE_HIGH,
		.modulation = V4L2_BAND_MODULATION_AM,
	पूर्ण,
	/* Band SW */
	अणु
		.type = V4L2_TUNER_RADIO,
		.index = 2,
		.capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   = SW_FREQ_RANGE_LOW,
		.rangehigh  = SW_FREQ_RANGE_HIGH,
		.modulation = V4L2_BAND_MODULATION_AM,
	पूर्ण,
पूर्ण;

/*
 * Initialize the RDS generator. If we can loop, then the RDS generator
 * is set up with the values from the RDS TX controls, otherwise it
 * will fill in standard values using one of two alternates.
 */
व्योम vivid_radio_rds_init(काष्ठा vivid_dev *dev)
अणु
	काष्ठा vivid_rds_gen *rds = &dev->rds_gen;
	bool alt = dev->radio_rx_rds_use_alternates;

	/* Do nothing, blocks will be filled by the transmitter */
	अगर (dev->radio_rds_loop && !dev->radio_tx_rds_controls)
		वापस;

	अगर (dev->radio_rds_loop) अणु
		v4l2_ctrl_lock(dev->radio_tx_rds_pi);
		rds->picode = dev->radio_tx_rds_pi->cur.val;
		rds->pty = dev->radio_tx_rds_pty->cur.val;
		rds->mono_stereo = dev->radio_tx_rds_mono_stereo->cur.val;
		rds->art_head = dev->radio_tx_rds_art_head->cur.val;
		rds->compressed = dev->radio_tx_rds_compressed->cur.val;
		rds->dyn_pty = dev->radio_tx_rds_dyn_pty->cur.val;
		rds->ta = dev->radio_tx_rds_ta->cur.val;
		rds->tp = dev->radio_tx_rds_tp->cur.val;
		rds->ms = dev->radio_tx_rds_ms->cur.val;
		strscpy(rds->psname,
			dev->radio_tx_rds_psname->p_cur.p_अक्षर,
			माप(rds->psname));
		strscpy(rds->radiotext,
			dev->radio_tx_rds_radiotext->p_cur.p_अक्षर + alt * 64,
			माप(rds->radiotext));
		v4l2_ctrl_unlock(dev->radio_tx_rds_pi);
	पूर्ण अन्यथा अणु
		vivid_rds_gen_fill(rds, dev->radio_rx_freq, alt);
	पूर्ण
	अगर (dev->radio_rx_rds_controls) अणु
		v4l2_ctrl_s_ctrl(dev->radio_rx_rds_pty, rds->pty);
		v4l2_ctrl_s_ctrl(dev->radio_rx_rds_ta, rds->ta);
		v4l2_ctrl_s_ctrl(dev->radio_rx_rds_tp, rds->tp);
		v4l2_ctrl_s_ctrl(dev->radio_rx_rds_ms, rds->ms);
		v4l2_ctrl_s_ctrl_string(dev->radio_rx_rds_psname, rds->psname);
		v4l2_ctrl_s_ctrl_string(dev->radio_rx_rds_radiotext, rds->radiotext);
		अगर (!dev->radio_rds_loop)
			dev->radio_rx_rds_use_alternates = !dev->radio_rx_rds_use_alternates;
	पूर्ण
	vivid_rds_generate(rds);
पूर्ण

/*
 * Calculate the emulated संकेत quality taking पूर्णांकo account the frequency
 * the transmitter is using.
 */
अटल व्योम vivid_radio_calc_sig_qual(काष्ठा vivid_dev *dev)
अणु
	पूर्णांक mod = 16000;
	पूर्णांक delta = 800;
	पूर्णांक sig_qual, sig_qual_tx = mod;

	/*
	 * For SW and FM there is a channel every 1000 kHz, क्रम AM there is one
	 * every 100 kHz.
	 */
	अगर (dev->radio_rx_freq <= AM_FREQ_RANGE_HIGH) अणु
		mod /= 10;
		delta /= 10;
	पूर्ण
	sig_qual = (dev->radio_rx_freq + delta) % mod - delta;
	अगर (dev->has_radio_tx)
		sig_qual_tx = dev->radio_rx_freq - dev->radio_tx_freq;
	अगर (असल(sig_qual_tx) <= असल(sig_qual)) अणु
		sig_qual = sig_qual_tx;
		/*
		 * Zero the पूर्णांकernal rds buffer अगर we are going to loop
		 * rds blocks.
		 */
		अगर (!dev->radio_rds_loop && !dev->radio_tx_rds_controls)
			स_रखो(dev->rds_gen.data, 0,
			       माप(dev->rds_gen.data));
		dev->radio_rds_loop = dev->radio_rx_freq >= FM_FREQ_RANGE_LOW;
	पूर्ण अन्यथा अणु
		dev->radio_rds_loop = false;
	पूर्ण
	अगर (dev->radio_rx_freq <= AM_FREQ_RANGE_HIGH)
		sig_qual *= 10;
	dev->radio_rx_sig_qual = sig_qual;
पूर्ण

पूर्णांक vivid_radio_g_frequency(काष्ठा file *file, स्थिर अचिन्हित *pfreq, काष्ठा v4l2_frequency *vf)
अणु
	अगर (vf->tuner != 0)
		वापस -EINVAL;
	vf->frequency = *pfreq;
	वापस 0;
पूर्ण

पूर्णांक vivid_radio_s_frequency(काष्ठा file *file, अचिन्हित *pfreq, स्थिर काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	अचिन्हित freq;
	अचिन्हित band;

	अगर (vf->tuner != 0)
		वापस -EINVAL;

	अगर (vf->frequency >= (FM_FREQ_RANGE_LOW + SW_FREQ_RANGE_HIGH) / 2)
		band = BAND_FM;
	अन्यथा अगर (vf->frequency <= (AM_FREQ_RANGE_HIGH + SW_FREQ_RANGE_LOW) / 2)
		band = BAND_AM;
	अन्यथा
		band = BAND_SW;

	freq = clamp_t(u32, vf->frequency, vivid_radio_bands[band].rangelow,
					   vivid_radio_bands[band].rangehigh);
	*pfreq = freq;

	/*
	 * For both receiver and transmitter recalculate the संकेत quality
	 * (since that depends on both frequencies) and re-init the rds
	 * generator.
	 */
	vivid_radio_calc_sig_qual(dev);
	vivid_radio_rds_init(dev);
	वापस 0;
पूर्ण
