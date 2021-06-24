<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ddbridge-sx8.c: Digital Devices MAX SX8 driver
 *
 * Copyright (C) 2018 Digital Devices GmbH
 *                    Marcus Metzler <mocm@metzlerbros.de>
 *                    Ralph Metzler <rjkm@metzlerbros.de>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 only, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#समावेश "ddbridge.h"
#समावेश "ddbridge-io.h"
#समावेश "ddbridge-mci.h"

अटल स्थिर u32 MCLK = (1550000000 / 12);
अटल स्थिर u32 MAX_LDPC_BITRATE = (720000000);
अटल स्थिर u32 MAX_DEMOD_LDPC_BITRATE = (1550000000 / 6);

#घोषणा SX8_TUNER_NUM 4
#घोषणा SX8_DEMOD_NUM 8
#घोषणा SX8_DEMOD_NONE 0xff

काष्ठा sx8_base अणु
	काष्ठा mci_base      mci_base;

	u8                   tuner_use_count[SX8_TUNER_NUM];
	u32                  gain_mode[SX8_TUNER_NUM];

	u32                  used_ldpc_bitrate[SX8_DEMOD_NUM];
	u8                   demod_in_use[SX8_DEMOD_NUM];
	u32                  iq_mode;
	u32                  burst_size;
	u32                  direct_mode;
पूर्ण;

काष्ठा sx8 अणु
	काष्ठा mci           mci;

	पूर्णांक                  first_समय_lock;
	पूर्णांक                  started;
	काष्ठा mci_result    संकेत_info;

	u32                  bb_mode;
	u32                  local_frequency;
पूर्ण;

अटल व्योम release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा sx8 *state = fe->demodulator_priv;
	काष्ठा mci_base *mci_base = state->mci.base;

	mci_base->count--;
	अगर (mci_base->count == 0) अणु
		list_del(&mci_base->mci_list);
		kमुक्त(mci_base);
	पूर्ण
	kमुक्त(state);
पूर्ण

अटल पूर्णांक get_info(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक stat;
	काष्ठा sx8 *state = fe->demodulator_priv;
	काष्ठा mci_command cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.command = MCI_CMD_GETSIGNALINFO;
	cmd.demod = state->mci.demod;
	stat = ddb_mci_cmd(&state->mci, &cmd, &state->संकेत_info);
	वापस stat;
पूर्ण

अटल पूर्णांक get_snr(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा sx8 *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	p->cnr.len = 1;
	p->cnr.stat[0].scale = FE_SCALE_DECIBEL;
	p->cnr.stat[0].svalue =
		(s64)state->संकेत_info.dvbs2_संकेत_info.संकेत_to_noise
		     * 10;
	वापस 0;
पूर्ण

अटल पूर्णांक get_strength(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा sx8 *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	s32 str;

	str = 100000 -
	      (state->संकेत_info.dvbs2_संकेत_info.channel_घातer
	       * 10 + 108750);
	p->strength.len = 1;
	p->strength.stat[0].scale = FE_SCALE_DECIBEL;
	p->strength.stat[0].svalue = str;
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	पूर्णांक stat;
	काष्ठा sx8 *state = fe->demodulator_priv;
	काष्ठा mci_command cmd;
	काष्ठा mci_result res;

	cmd.command = MCI_CMD_GETSTATUS;
	cmd.demod = state->mci.demod;
	stat = ddb_mci_cmd(&state->mci, &cmd, &res);
	अगर (stat)
		वापस stat;
	*status = 0x00;
	get_info(fe);
	get_strength(fe);
	अगर (res.status == SX8_DEMOD_WAIT_MATYPE)
		*status = 0x0f;
	अगर (res.status == SX8_DEMOD_LOCKED) अणु
		*status = 0x1f;
		get_snr(fe);
	पूर्ण
	वापस stat;
पूर्ण

अटल पूर्णांक mci_set_tuner(काष्ठा dvb_frontend *fe, u32 tuner, u32 on)
अणु
	काष्ठा sx8 *state = fe->demodulator_priv;
	काष्ठा mci_base *mci_base = state->mci.base;
	काष्ठा sx8_base *sx8_base = (काष्ठा sx8_base *)mci_base;
	काष्ठा mci_command cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.tuner = state->mci.tuner;
	cmd.command = on ? SX8_CMD_INPUT_ENABLE : SX8_CMD_INPUT_DISABLE;
	cmd.sx8_input_enable.flags = sx8_base->gain_mode[state->mci.tuner];
	वापस ddb_mci_cmd(&state->mci, &cmd, शून्य);
पूर्ण

अटल पूर्णांक stop(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा sx8 *state = fe->demodulator_priv;
	काष्ठा mci_base *mci_base = state->mci.base;
	काष्ठा sx8_base *sx8_base = (काष्ठा sx8_base *)mci_base;
	काष्ठा mci_command cmd;
	u32 input = state->mci.tuner;

	स_रखो(&cmd, 0, माप(cmd));
	अगर (state->mci.demod != SX8_DEMOD_NONE) अणु
		cmd.command = MCI_CMD_STOP;
		cmd.demod = state->mci.demod;
		ddb_mci_cmd(&state->mci, &cmd, शून्य);
		अगर (sx8_base->iq_mode) अणु
			cmd.command = SX8_CMD_DISABLE_IQOUTPUT;
			cmd.demod = state->mci.demod;
			cmd.output = 0;
			ddb_mci_cmd(&state->mci, &cmd, शून्य);
			ddb_mci_config(&state->mci, SX8_TSCONFIG_MODE_NORMAL);
		पूर्ण
	पूर्ण
	mutex_lock(&mci_base->tuner_lock);
	sx8_base->tuner_use_count[input]--;
	अगर (!sx8_base->tuner_use_count[input])
		mci_set_tuner(fe, input, 0);
	अगर (state->mci.demod < SX8_DEMOD_NUM) अणु
		sx8_base->demod_in_use[state->mci.demod] = 0;
		state->mci.demod = SX8_DEMOD_NONE;
	पूर्ण
	sx8_base->used_ldpc_bitrate[state->mci.nr] = 0;
	sx8_base->iq_mode = 0;
	mutex_unlock(&mci_base->tuner_lock);
	state->started = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक start(काष्ठा dvb_frontend *fe, u32 flags, u32 modmask, u32 ts_config)
अणु
	काष्ठा sx8 *state = fe->demodulator_priv;
	काष्ठा mci_base *mci_base = state->mci.base;
	काष्ठा sx8_base *sx8_base = (काष्ठा sx8_base *)mci_base;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 used_ldpc_bitrate = 0, मुक्त_ldpc_bitrate;
	u32 used_demods = 0;
	काष्ठा mci_command cmd;
	u32 input = state->mci.tuner;
	u32 bits_per_symbol = 0;
	पूर्णांक i = -1, stat = 0;

	अगर (p->symbol_rate >= (MCLK / 2))
		flags &= ~1;
	अगर ((flags & 3) == 0)
		वापस -EINVAL;

	अगर (flags & 2) अणु
		u32 पंचांगp = modmask;

		bits_per_symbol = 1;
		जबतक (पंचांगp & 1) अणु
			पंचांगp >>= 1;
			bits_per_symbol++;
		पूर्ण
	पूर्ण

	mutex_lock(&mci_base->tuner_lock);
	अगर (sx8_base->iq_mode) अणु
		stat = -EBUSY;
		जाओ unlock;
	पूर्ण

	अगर (sx8_base->direct_mode) अणु
		अगर (p->symbol_rate >= MCLK / 2) अणु
			अगर (state->mci.nr < 4)
				i = state->mci.nr;
		पूर्ण अन्यथा अणु
			i = state->mci.nr;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < SX8_DEMOD_NUM; i++) अणु
			used_ldpc_bitrate += sx8_base->used_ldpc_bitrate[i];
			अगर (sx8_base->demod_in_use[i])
				used_demods++;
		पूर्ण
		अगर (used_ldpc_bitrate >= MAX_LDPC_BITRATE ||
		    ((ts_config & SX8_TSCONFIG_MODE_MASK) >
		     SX8_TSCONFIG_MODE_NORMAL && used_demods > 0)) अणु
			stat = -EBUSY;
			जाओ unlock;
		पूर्ण
		मुक्त_ldpc_bitrate = MAX_LDPC_BITRATE - used_ldpc_bitrate;
		अगर (मुक्त_ldpc_bitrate > MAX_DEMOD_LDPC_BITRATE)
			मुक्त_ldpc_bitrate = MAX_DEMOD_LDPC_BITRATE;

		जबतक (p->symbol_rate * bits_per_symbol > मुक्त_ldpc_bitrate)
			bits_per_symbol--;
		अगर (bits_per_symbol < 2) अणु
			stat = -EBUSY;
			जाओ unlock;
		पूर्ण

		modmask &= ((1 << (bits_per_symbol - 1)) - 1);
		अगर (((flags & 0x02) != 0) && modmask == 0) अणु
			stat = -EBUSY;
			जाओ unlock;
		पूर्ण

		i = (p->symbol_rate > (MCLK / 2)) ? 3 : 7;
		जबतक (i >= 0 && sx8_base->demod_in_use[i])
			i--;
	पूर्ण

	अगर (i < 0) अणु
		stat = -EBUSY;
		जाओ unlock;
	पूर्ण
	sx8_base->demod_in_use[i] = 1;
	sx8_base->used_ldpc_bitrate[state->mci.nr] = p->symbol_rate
						     * bits_per_symbol;
	state->mci.demod = i;

	अगर (!sx8_base->tuner_use_count[input])
		mci_set_tuner(fe, input, 1);
	sx8_base->tuner_use_count[input]++;
	sx8_base->iq_mode = (ts_config > 1);
unlock:
	mutex_unlock(&mci_base->tuner_lock);
	अगर (stat)
		वापस stat;
	स_रखो(&cmd, 0, माप(cmd));

	अगर (sx8_base->iq_mode) अणु
		cmd.command = SX8_CMD_ENABLE_IQOUTPUT;
		cmd.demod = state->mci.demod;
		cmd.output = 0;
		ddb_mci_cmd(&state->mci, &cmd, शून्य);
		ddb_mci_config(&state->mci, ts_config);
	पूर्ण
	अगर (p->stream_id != NO_STREAM_ID_FILTER && p->stream_id != 0x80000000)
		flags |= 0x80;
	dev_dbg(mci_base->dev, "MCI-%d: tuner=%d demod=%d\n",
		state->mci.nr, state->mci.tuner, state->mci.demod);
	cmd.command = MCI_CMD_SEARCH_DVBS;
	cmd.dvbs2_search.flags = flags;
	cmd.dvbs2_search.s2_modulation_mask = modmask;
	cmd.dvbs2_search.retry = 2;
	cmd.dvbs2_search.frequency = p->frequency * 1000;
	cmd.dvbs2_search.symbol_rate = p->symbol_rate;
	cmd.dvbs2_search.scrambling_sequence_index =
		p->scrambling_sequence_index | 0x80000000;
	cmd.dvbs2_search.input_stream_id =
		(p->stream_id != NO_STREAM_ID_FILTER) ? p->stream_id : 0;
	cmd.tuner = state->mci.tuner;
	cmd.demod = state->mci.demod;
	cmd.output = state->mci.nr;
	अगर (p->stream_id == 0x80000000)
		cmd.output |= 0x80;
	stat = ddb_mci_cmd(&state->mci, &cmd, शून्य);
	अगर (stat)
		stop(fe);
	वापस stat;
पूर्ण

अटल पूर्णांक start_iq(काष्ठा dvb_frontend *fe, u32 flags, u32 roll_off,
		    u32 ts_config)
अणु
	काष्ठा sx8 *state = fe->demodulator_priv;
	काष्ठा mci_base *mci_base = state->mci.base;
	काष्ठा sx8_base *sx8_base = (काष्ठा sx8_base *)mci_base;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 used_demods = 0;
	काष्ठा mci_command cmd;
	u32 input = state->mci.tuner;
	पूर्णांक i, stat = 0;

	mutex_lock(&mci_base->tuner_lock);
	अगर (sx8_base->iq_mode) अणु
		stat = -EBUSY;
		जाओ unlock;
	पूर्ण
	क्रम (i = 0; i < SX8_DEMOD_NUM; i++)
		अगर (sx8_base->demod_in_use[i])
			used_demods++;
	अगर (used_demods > 0) अणु
		stat = -EBUSY;
		जाओ unlock;
	पूर्ण
	state->mci.demod = 0;
	अगर (!sx8_base->tuner_use_count[input])
		mci_set_tuner(fe, input, 1);
	sx8_base->tuner_use_count[input]++;
	sx8_base->iq_mode = (ts_config > 1);
unlock:
	mutex_unlock(&mci_base->tuner_lock);
	अगर (stat)
		वापस stat;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.command = SX8_CMD_START_IQ;
	cmd.sx8_start_iq.flags = flags;
	cmd.sx8_start_iq.roll_off = roll_off;
	cmd.sx8_start_iq.frequency = p->frequency * 1000;
	cmd.sx8_start_iq.symbol_rate = p->symbol_rate;
	cmd.tuner = state->mci.tuner;
	cmd.demod = state->mci.demod;
	stat = ddb_mci_cmd(&state->mci, &cmd, शून्य);
	अगर (stat)
		stop(fe);
	ddb_mci_config(&state->mci, ts_config);
	वापस stat;
पूर्ण

अटल पूर्णांक set_parameters(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक stat = 0;
	काष्ठा sx8 *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 ts_config = SX8_TSCONFIG_MODE_NORMAL, iq_mode = 0, isi;

	अगर (state->started)
		stop(fe);

	isi = p->stream_id;
	अगर (isi != NO_STREAM_ID_FILTER)
		iq_mode = (isi & 0x30000000) >> 28;

	अगर (iq_mode)
		ts_config = (SX8_TSCONFIG_TSHEADER | SX8_TSCONFIG_MODE_IQ);
	अगर (iq_mode < 3) अणु
		u32 mask;

		चयन (p->modulation) अणु
		/* uncomment whenever these modulations hit the DVB API
		 *	हाल APSK_256:
		 *		mask = 0x7f;
		 *		अवरोध;
		 *	हाल APSK_128:
		 *		mask = 0x3f;
		 *		अवरोध;
		 *	हाल APSK_64:
		 *		mask = 0x1f;
		 *		अवरोध;
		 */
		हाल APSK_32:
			mask = 0x0f;
			अवरोध;
		हाल APSK_16:
			mask = 0x07;
			अवरोध;
		शेष:
			mask = 0x03;
			अवरोध;
		पूर्ण
		stat = start(fe, 3, mask, ts_config);
	पूर्ण अन्यथा अणु
		stat = start_iq(fe, 0, 4, ts_config);
	पूर्ण
	अगर (!stat) अणु
		state->started = 1;
		state->first_समय_lock = 1;
		state->संकेत_info.status = SX8_DEMOD_WAIT_SIGNAL;
	पूर्ण

	वापस stat;
पूर्ण

अटल पूर्णांक tune(काष्ठा dvb_frontend *fe, bool re_tune,
		अचिन्हित पूर्णांक mode_flags,
		अचिन्हित पूर्णांक *delay, क्रमागत fe_status *status)
अणु
	पूर्णांक r;

	अगर (re_tune) अणु
		r = set_parameters(fe);
		अगर (r)
			वापस r;
	पूर्ण
	r = पढ़ो_status(fe, status);
	अगर (r)
		वापस r;

	अगर (*status & FE_HAS_LOCK)
		वापस 0;
	*delay = HZ / 10;
	वापस 0;
पूर्ण

अटल क्रमागत dvbfe_algo get_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस DVBFE_ALGO_HW;
पूर्ण

अटल पूर्णांक set_input(काष्ठा dvb_frontend *fe, पूर्णांक input)
अणु
	काष्ठा sx8 *state = fe->demodulator_priv;
	काष्ठा mci_base *mci_base = state->mci.base;

	अगर (input >= SX8_TUNER_NUM)
		वापस -EINVAL;

	state->mci.tuner = input;
	dev_dbg(mci_base->dev, "MCI-%d: input=%d\n", state->mci.nr, input);
	वापस 0;
पूर्ण

अटल काष्ठा dvb_frontend_ops sx8_ops = अणु
	.delsys = अणु SYS_DVBS, SYS_DVBS2 पूर्ण,
	.info = अणु
		.name			= "Digital Devices MaxSX8 MCI DVB-S/S2/S2X",
		.frequency_min_hz	=  950 * MHz,
		.frequency_max_hz	= 2150 * MHz,
		.symbol_rate_min	= 100000,
		.symbol_rate_max	= 100000000,
		.caps			= FE_CAN_INVERSION_AUTO |
					  FE_CAN_FEC_AUTO       |
					  FE_CAN_QPSK           |
					  FE_CAN_2G_MODULATION  |
					  FE_CAN_MULTISTREAM,
	पूर्ण,
	.get_frontend_algo		= get_algo,
	.tune				= tune,
	.release			= release,
	.पढ़ो_status			= पढ़ो_status,
पूर्ण;

अटल पूर्णांक init(काष्ठा mci *mci)
अणु
	काष्ठा sx8 *state = (काष्ठा sx8 *)mci;

	state->mci.demod = SX8_DEMOD_NONE;
	वापस 0;
पूर्ण

स्थिर काष्ठा mci_cfg ddb_max_sx8_cfg = अणु
	.type = 0,
	.fe_ops = &sx8_ops,
	.base_size = माप(काष्ठा sx8_base),
	.state_size = माप(काष्ठा sx8),
	.init = init,
	.set_input = set_input,
पूर्ण;
