<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * The Virtual DTV test driver serves as a reference DVB driver and helps
 * validate the existing APIs in the media subप्रणाली. It can also aid
 * developers working on userspace applications.
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 * Based on the example driver written by Emard <emard@softhome.net>
 */

#अगर_अघोषित VIDTV_DEMOD_H
#घोषणा VIDTV_DEMOD_H

#समावेश <linux/dvb/frontend.h>

#समावेश <media/dvb_frontend.h>

/**
 * काष्ठा vidtv_demod_cnr_to_qual_s - Map CNR values to a given combination of
 * modulation and fec_inner
 * @modulation: see क्रमागत fe_modulation
 * @fec: see क्रमागत fe_fec_rate
 * @cnr_ok: S/N threshold to consider the संकेत as OK. Below that, there's
 *          a chance of losing sync.
 * @cnr_good: S/N threshold to consider the संकेत strong.
 *
 * This काष्ठा matches values क्रम 'good' and 'ok' CNRs given the combination
 * of modulation and fec_inner in use. We might simulate some noise अगर the
 * संकेत quality is not too good.
 *
 * The values were taken from libdvbv5.
 */
काष्ठा vidtv_demod_cnr_to_qual_s अणु
	u32 modulation;
	u32 fec;
	u32 cnr_ok;
	u32 cnr_good;
पूर्ण;

/**
 * काष्ठा vidtv_demod_config - Configuration used to init the demod
 * @drop_tslock_prob_on_low_snr: probability of losing the lock due to low snr
 * @recover_tslock_prob_on_good_snr: probability of recovering when the संकेत
 * improves
 *
 * The configuration used to init the demodulator module, usually filled
 * by a bridge driver. For vidtv, this is filled by vidtv_bridge beक्रमe the
 * demodulator module is probed.
 */
काष्ठा vidtv_demod_config अणु
	u8 drop_tslock_prob_on_low_snr;
	u8 recover_tslock_prob_on_good_snr;
पूर्ण;

/**
 * काष्ठा vidtv_demod_state - The demodulator state
 * @frontend: The frontend काष्ठाure allocated by the demod.
 * @config: The config used to init the demod.
 * @status: the demod status.
 * @tuner_cnr: current S/N ratio क्रम the संकेत carrier
 */
काष्ठा vidtv_demod_state अणु
	काष्ठा dvb_frontend frontend;
	काष्ठा vidtv_demod_config config;
	क्रमागत fe_status status;
	u16 tuner_cnr;
पूर्ण;
#पूर्ण_अगर // VIDTV_DEMOD_H
