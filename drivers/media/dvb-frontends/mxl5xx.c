<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the MaxLinear MxL5xx family of tuners/demods
 *
 * Copyright (C) 2014-2015 Ralph Metzler <rjkm@metzlerbros.de>
 *                         Marcus Metzler <mocm@metzlerbros.de>
 *                         developed क्रम Digital Devices GmbH
 *
 * based on code:
 * Copyright (c) 2011-2013 MaxLinear, Inc. All rights reserved
 * which was released under GPL V2
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <media/dvb_frontend.h>
#समावेश "mxl5xx.h"
#समावेश "mxl5xx_regs.h"
#समावेश "mxl5xx_defs.h"

#घोषणा BYTE0(v) ((v >>  0) & 0xff)
#घोषणा BYTE1(v) ((v >>  8) & 0xff)
#घोषणा BYTE2(v) ((v >> 16) & 0xff)
#घोषणा BYTE3(v) ((v >> 24) & 0xff)

अटल LIST_HEAD(mxllist);

काष्ठा mxl_base अणु
	काष्ठा list_head     mxllist;
	काष्ठा list_head     mxls;

	u8                   adr;
	काष्ठा i2c_adapter  *i2c;

	u32                  count;
	u32                  type;
	u32                  sku_type;
	u32                  chipversion;
	u32                  घड़ी;
	u32                  fwversion;

	u8                  *ts_map;
	u8                   can_clkout;
	u8                   chan_bond;
	u8                   demod_num;
	u8                   tuner_num;

	अचिन्हित दीर्घ        next_tune;

	काष्ठा mutex         i2c_lock;
	काष्ठा mutex         status_lock;
	काष्ठा mutex         tune_lock;

	u8                   buf[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

	u32                  cmd_size;
	u8                   cmd_data[MAX_CMD_DATA];
पूर्ण;

काष्ठा mxl अणु
	काष्ठा list_head     mxl;

	काष्ठा mxl_base     *base;
	काष्ठा dvb_frontend  fe;
	काष्ठा device       *i2cdev;
	u32                  demod;
	u32                  tuner;
	u32                  tuner_in_use;
	u8                   xbar[3];

	अचिन्हित दीर्घ        tune_समय;
पूर्ण;

अटल व्योम convert_endian(u8 flag, u32 size, u8 *d)
अणु
	u32 i;

	अगर (!flag)
		वापस;
	क्रम (i = 0; i < (size & ~3); i += 4) अणु
		d[i + 0] ^= d[i + 3];
		d[i + 3] ^= d[i + 0];
		d[i + 0] ^= d[i + 3];

		d[i + 1] ^= d[i + 2];
		d[i + 2] ^= d[i + 1];
		d[i + 1] ^= d[i + 2];
	पूर्ण

	चयन (size & 3) अणु
	हाल 0:
	हाल 1:
		/* करो nothing */
		अवरोध;
	हाल 2:
		d[i + 0] ^= d[i + 1];
		d[i + 1] ^= d[i + 0];
		d[i + 0] ^= d[i + 1];
		अवरोध;

	हाल 3:
		d[i + 0] ^= d[i + 2];
		d[i + 2] ^= d[i + 0];
		d[i + 0] ^= d[i + 2];
		अवरोध;
	पूर्ण

पूर्ण

अटल पूर्णांक i2c_ग_लिखो(काष्ठा i2c_adapter *adap, u8 adr,
			    u8 *data, u32 len)
अणु
	काष्ठा i2c_msg msg = अणु.addr = adr, .flags = 0,
			      .buf = data, .len = lenपूर्ण;

	वापस (i2c_transfer(adap, &msg, 1) == 1) ? 0 : -1;
पूर्ण

अटल पूर्णांक i2c_पढ़ो(काष्ठा i2c_adapter *adap, u8 adr,
			   u8 *data, u32 len)
अणु
	काष्ठा i2c_msg msg = अणु.addr = adr, .flags = I2C_M_RD,
			      .buf = data, .len = lenपूर्ण;

	वापस (i2c_transfer(adap, &msg, 1) == 1) ? 0 : -1;
पूर्ण

अटल पूर्णांक i2cपढ़ो(काष्ठा mxl *state, u8 *data, पूर्णांक len)
अणु
	वापस i2c_पढ़ो(state->base->i2c, state->base->adr, data, len);
पूर्ण

अटल पूर्णांक i2cग_लिखो(काष्ठा mxl *state, u8 *data, पूर्णांक len)
अणु
	वापस i2c_ग_लिखो(state->base->i2c, state->base->adr, data, len);
पूर्ण

अटल पूर्णांक पढ़ो_रेजिस्टर_unlocked(काष्ठा mxl *state, u32 reg, u32 *val)
अणु
	पूर्णांक stat;
	u8 data[MXL_HYDRA_REG_SIZE_IN_BYTES + MXL_HYDRA_I2C_HDR_SIZE] = अणु
		MXL_HYDRA_PLID_REG_READ, 0x04,
		GET_BYTE(reg, 0), GET_BYTE(reg, 1),
		GET_BYTE(reg, 2), GET_BYTE(reg, 3),
	पूर्ण;

	stat = i2cग_लिखो(state, data,
			MXL_HYDRA_REG_SIZE_IN_BYTES + MXL_HYDRA_I2C_HDR_SIZE);
	अगर (stat)
		dev_err(state->i2cdev, "i2c read error 1\n");
	अगर (!stat)
		stat = i2cपढ़ो(state, (u8 *) val,
			       MXL_HYDRA_REG_SIZE_IN_BYTES);
	le32_to_cpus(val);
	अगर (stat)
		dev_err(state->i2cdev, "i2c read error 2\n");
	वापस stat;
पूर्ण

#घोषणा DMA_I2C_INTERRUPT_ADDR 0x8000011C
#घोषणा DMA_INTR_PROT_WR_CMP 0x08

अटल पूर्णांक send_command(काष्ठा mxl *state, u32 size, u8 *buf)
अणु
	पूर्णांक stat;
	u32 val, count = 10;

	mutex_lock(&state->base->i2c_lock);
	अगर (state->base->fwversion > 0x02010109)  अणु
		पढ़ो_रेजिस्टर_unlocked(state, DMA_I2C_INTERRUPT_ADDR, &val);
		अगर (DMA_INTR_PROT_WR_CMP & val)
			dev_info(state->i2cdev, "%s busy\n", __func__);
		जबतक ((DMA_INTR_PROT_WR_CMP & val) && --count) अणु
			mutex_unlock(&state->base->i2c_lock);
			usleep_range(1000, 2000);
			mutex_lock(&state->base->i2c_lock);
			पढ़ो_रेजिस्टर_unlocked(state, DMA_I2C_INTERRUPT_ADDR,
					       &val);
		पूर्ण
		अगर (!count) अणु
			dev_info(state->i2cdev, "%s busy\n", __func__);
			mutex_unlock(&state->base->i2c_lock);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	stat = i2cग_लिखो(state, buf, size);
	mutex_unlock(&state->base->i2c_lock);
	वापस stat;
पूर्ण

अटल पूर्णांक ग_लिखो_रेजिस्टर(काष्ठा mxl *state, u32 reg, u32 val)
अणु
	पूर्णांक stat;
	u8 data[MXL_HYDRA_REG_WRITE_LEN] = अणु
		MXL_HYDRA_PLID_REG_WRITE, 0x08,
		BYTE0(reg), BYTE1(reg), BYTE2(reg), BYTE3(reg),
		BYTE0(val), BYTE1(val), BYTE2(val), BYTE3(val),
	पूर्ण;
	mutex_lock(&state->base->i2c_lock);
	stat = i2cग_लिखो(state, data, माप(data));
	mutex_unlock(&state->base->i2c_lock);
	अगर (stat)
		dev_err(state->i2cdev, "i2c write error\n");
	वापस stat;
पूर्ण

अटल पूर्णांक ग_लिखो_firmware_block(काष्ठा mxl *state,
				u32 reg, u32 size, u8 *reg_data_ptr)
अणु
	पूर्णांक stat;
	u8 *buf = state->base->buf;

	mutex_lock(&state->base->i2c_lock);
	buf[0] = MXL_HYDRA_PLID_REG_WRITE;
	buf[1] = size + 4;
	buf[2] = GET_BYTE(reg, 0);
	buf[3] = GET_BYTE(reg, 1);
	buf[4] = GET_BYTE(reg, 2);
	buf[5] = GET_BYTE(reg, 3);
	स_नकल(&buf[6], reg_data_ptr, size);
	stat = i2cग_लिखो(state, buf,
			MXL_HYDRA_I2C_HDR_SIZE +
			MXL_HYDRA_REG_SIZE_IN_BYTES + size);
	mutex_unlock(&state->base->i2c_lock);
	अगर (stat)
		dev_err(state->i2cdev, "fw block write failed\n");
	वापस stat;
पूर्ण

अटल पूर्णांक पढ़ो_रेजिस्टर(काष्ठा mxl *state, u32 reg, u32 *val)
अणु
	पूर्णांक stat;
	u8 data[MXL_HYDRA_REG_SIZE_IN_BYTES + MXL_HYDRA_I2C_HDR_SIZE] = अणु
		MXL_HYDRA_PLID_REG_READ, 0x04,
		GET_BYTE(reg, 0), GET_BYTE(reg, 1),
		GET_BYTE(reg, 2), GET_BYTE(reg, 3),
	पूर्ण;

	mutex_lock(&state->base->i2c_lock);
	stat = i2cग_लिखो(state, data,
			MXL_HYDRA_REG_SIZE_IN_BYTES + MXL_HYDRA_I2C_HDR_SIZE);
	अगर (stat)
		dev_err(state->i2cdev, "i2c read error 1\n");
	अगर (!stat)
		stat = i2cपढ़ो(state, (u8 *) val,
			       MXL_HYDRA_REG_SIZE_IN_BYTES);
	mutex_unlock(&state->base->i2c_lock);
	le32_to_cpus(val);
	अगर (stat)
		dev_err(state->i2cdev, "i2c read error 2\n");
	वापस stat;
पूर्ण

अटल पूर्णांक पढ़ो_रेजिस्टर_block(काष्ठा mxl *state, u32 reg, u32 size, u8 *data)
अणु
	पूर्णांक stat;
	u8 *buf = state->base->buf;

	mutex_lock(&state->base->i2c_lock);

	buf[0] = MXL_HYDRA_PLID_REG_READ;
	buf[1] = size + 4;
	buf[2] = GET_BYTE(reg, 0);
	buf[3] = GET_BYTE(reg, 1);
	buf[4] = GET_BYTE(reg, 2);
	buf[5] = GET_BYTE(reg, 3);
	stat = i2cग_लिखो(state, buf,
			MXL_HYDRA_I2C_HDR_SIZE + MXL_HYDRA_REG_SIZE_IN_BYTES);
	अगर (!stat) अणु
		stat = i2cपढ़ो(state, data, size);
		convert_endian(MXL_ENABLE_BIG_ENDIAN, size, data);
	पूर्ण
	mutex_unlock(&state->base->i2c_lock);
	वापस stat;
पूर्ण

अटल पूर्णांक पढ़ो_by_mnemonic(काष्ठा mxl *state,
			    u32 reg, u8 lsbloc, u8 numofbits, u32 *val)
अणु
	u32 data = 0, mask = 0;
	पूर्णांक stat;

	stat = पढ़ो_रेजिस्टर(state, reg, &data);
	अगर (stat)
		वापस stat;
	mask = MXL_GET_REG_MASK_32(lsbloc, numofbits);
	data &= mask;
	data >>= lsbloc;
	*val = data;
	वापस 0;
पूर्ण


अटल पूर्णांक update_by_mnemonic(काष्ठा mxl *state,
			      u32 reg, u8 lsbloc, u8 numofbits, u32 val)
अणु
	u32 data, mask;
	पूर्णांक stat;

	stat = पढ़ो_रेजिस्टर(state, reg, &data);
	अगर (stat)
		वापस stat;
	mask = MXL_GET_REG_MASK_32(lsbloc, numofbits);
	data = (data & ~mask) | ((val << lsbloc) & mask);
	stat = ग_लिखो_रेजिस्टर(state, reg, data);
	वापस stat;
पूर्ण

अटल पूर्णांक firmware_is_alive(काष्ठा mxl *state)
अणु
	u32 hb0, hb1;

	अगर (पढ़ो_रेजिस्टर(state, HYDRA_HEAR_BEAT, &hb0))
		वापस 0;
	msleep(20);
	अगर (पढ़ो_रेजिस्टर(state, HYDRA_HEAR_BEAT, &hb1))
		वापस 0;
	अगर (hb1 == hb0)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	/* init fe stats */
	p->strength.len = 1;
	p->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->cnr.len = 1;
	p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->pre_bit_error.len = 1;
	p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->pre_bit_count.len = 1;
	p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_error.len = 1;
	p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_count.len = 1;
	p->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	वापस 0;
पूर्ण

अटल व्योम release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl *state = fe->demodulator_priv;

	list_del(&state->mxl);
	/* Release one frontend, two more shall take its place! */
	state->base->count--;
	अगर (state->base->count == 0) अणु
		list_del(&state->base->mxllist);
		kमुक्त(state->base);
	पूर्ण
	kमुक्त(state);
पूर्ण

अटल क्रमागत dvbfe_algo get_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस DVBFE_ALGO_HW;
पूर्ण

अटल u32 gold2root(u32 gold)
अणु
	u32 x, g, पंचांगp = gold;

	अगर (पंचांगp >= 0x3ffff)
		पंचांगp = 0;
	क्रम (g = 0, x = 1; g < पंचांगp; g++)
		x = (((x ^ (x >> 7)) & 1) << 17) | (x >> 1);
	वापस x;
पूर्ण

अटल पूर्णांक cfg_scrambler(काष्ठा mxl *state, u32 gold)
अणु
	u32 root;
	u8 buf[26] = अणु
		MXL_HYDRA_PLID_CMD_WRITE, 24,
		0, MXL_HYDRA_DEMOD_SCRAMBLE_CODE_CMD, 0, 0,
		state->demod, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0, 0,
	पूर्ण;

	root = gold2root(gold);

	buf[25] = (root >> 24) & 0xff;
	buf[24] = (root >> 16) & 0xff;
	buf[23] = (root >> 8) & 0xff;
	buf[22] = root & 0xff;

	वापस send_command(state, माप(buf), buf);
पूर्ण

अटल पूर्णांक cfg_demod_पात_tune(काष्ठा mxl *state)
अणु
	काष्ठा MXL_HYDRA_DEMOD_ABORT_TUNE_T पात_tune_cmd;
	u8 cmd_size = माप(पात_tune_cmd);
	u8 cmd_buff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

	पात_tune_cmd.demod_id = state->demod;
	BUILD_HYDRA_CMD(MXL_HYDRA_ABORT_TUNE_CMD, MXL_CMD_WRITE,
			cmd_size, &पात_tune_cmd, cmd_buff);
	वापस send_command(state, cmd_size + MXL_HYDRA_CMD_HEADER_SIZE,
			    &cmd_buff[0]);
पूर्ण

अटल पूर्णांक send_master_cmd(काष्ठा dvb_frontend *fe,
			   काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	/*काष्ठा mxl *state = fe->demodulator_priv;*/

	वापस 0; /*CfgDemodAbortTune(state);*/
पूर्ण

अटल पूर्णांक set_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा MXL_HYDRA_DEMOD_PARAM_T demod_chan_cfg;
	u8 cmd_size = माप(demod_chan_cfg);
	u8 cmd_buff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];
	u32 srange = 10;
	पूर्णांक stat;

	अगर (p->frequency < 950000 || p->frequency > 2150000)
		वापस -EINVAL;
	अगर (p->symbol_rate < 1000000 || p->symbol_rate > 45000000)
		वापस -EINVAL;

	/* CfgDemodAbortTune(state); */

	चयन (p->delivery_प्रणाली) अणु
	हाल SYS_DSS:
		demod_chan_cfg.standard = MXL_HYDRA_DSS;
		demod_chan_cfg.roll_off = MXL_HYDRA_ROLLOFF_AUTO;
		अवरोध;
	हाल SYS_DVBS:
		srange = p->symbol_rate / 1000000;
		अगर (srange > 10)
			srange = 10;
		demod_chan_cfg.standard = MXL_HYDRA_DVBS;
		demod_chan_cfg.roll_off = MXL_HYDRA_ROLLOFF_0_35;
		demod_chan_cfg.modulation_scheme = MXL_HYDRA_MOD_QPSK;
		demod_chan_cfg.pilots = MXL_HYDRA_PILOTS_OFF;
		अवरोध;
	हाल SYS_DVBS2:
		demod_chan_cfg.standard = MXL_HYDRA_DVBS2;
		demod_chan_cfg.roll_off = MXL_HYDRA_ROLLOFF_AUTO;
		demod_chan_cfg.modulation_scheme = MXL_HYDRA_MOD_AUTO;
		demod_chan_cfg.pilots = MXL_HYDRA_PILOTS_AUTO;
		cfg_scrambler(state, p->scrambling_sequence_index);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	demod_chan_cfg.tuner_index = state->tuner;
	demod_chan_cfg.demod_index = state->demod;
	demod_chan_cfg.frequency_in_hz = p->frequency * 1000;
	demod_chan_cfg.symbol_rate_in_hz = p->symbol_rate;
	demod_chan_cfg.max_carrier_offset_in_mhz = srange;
	demod_chan_cfg.spectrum_inversion = MXL_HYDRA_SPECTRUM_AUTO;
	demod_chan_cfg.fec_code_rate = MXL_HYDRA_FEC_AUTO;

	mutex_lock(&state->base->tune_lock);
	अगर (समय_after(jअगरfies + msecs_to_jअगरfies(200),
		       state->base->next_tune))
		जबतक (समय_beक्रमe(jअगरfies, state->base->next_tune))
			usleep_range(10000, 11000);
	state->base->next_tune = jअगरfies + msecs_to_jअगरfies(100);
	state->tuner_in_use = state->tuner;
	BUILD_HYDRA_CMD(MXL_HYDRA_DEMOD_SET_PARAM_CMD, MXL_CMD_WRITE,
			cmd_size, &demod_chan_cfg, cmd_buff);
	stat = send_command(state, cmd_size + MXL_HYDRA_CMD_HEADER_SIZE,
			    &cmd_buff[0]);
	mutex_unlock(&state->base->tune_lock);
	वापस stat;
पूर्ण

अटल पूर्णांक enable_tuner(काष्ठा mxl *state, u32 tuner, u32 enable);

अटल पूर्णांक sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl *state = fe->demodulator_priv;
	काष्ठा mxl *p;

	cfg_demod_पात_tune(state);
	अगर (state->tuner_in_use != 0xffffffff) अणु
		mutex_lock(&state->base->tune_lock);
		state->tuner_in_use = 0xffffffff;
		list_क्रम_each_entry(p, &state->base->mxls, mxl) अणु
			अगर (p->tuner_in_use == state->tuner)
				अवरोध;
		पूर्ण
		अगर (&p->mxl == &state->base->mxls)
			enable_tuner(state, state->tuner, 0);
		mutex_unlock(&state->base->tune_lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_snr(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl *state = fe->demodulator_priv;
	पूर्णांक stat;
	u32 reg_data = 0;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	mutex_lock(&state->base->status_lock);
	HYDRA_DEMOD_STATUS_LOCK(state, state->demod);
	stat = पढ़ो_रेजिस्टर(state, (HYDRA_DMD_SNR_ADDR_OFFSET +
				     HYDRA_DMD_STATUS_OFFSET(state->demod)),
			     &reg_data);
	HYDRA_DEMOD_STATUS_UNLOCK(state, state->demod);
	mutex_unlock(&state->base->status_lock);

	p->cnr.stat[0].scale = FE_SCALE_DECIBEL;
	p->cnr.stat[0].svalue = (s16)reg_data * 10;

	वापस stat;
पूर्ण

अटल पूर्णांक पढ़ो_ber(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 reg[8];

	mutex_lock(&state->base->status_lock);
	HYDRA_DEMOD_STATUS_LOCK(state, state->demod);
	पढ़ो_रेजिस्टर_block(state,
		(HYDRA_DMD_DVBS_1ST_CORR_RS_ERRORS_ADDR_OFFSET +
		 HYDRA_DMD_STATUS_OFFSET(state->demod)),
		(4 * माप(u32)),
		(u8 *) &reg[0]);
	HYDRA_DEMOD_STATUS_UNLOCK(state, state->demod);

	चयन (p->delivery_प्रणाली) अणु
	हाल SYS_DSS:
	हाल SYS_DVBS:
		p->pre_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		p->pre_bit_error.stat[0].uvalue = reg[2];
		p->pre_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		p->pre_bit_count.stat[0].uvalue = reg[3];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	पढ़ो_रेजिस्टर_block(state,
		(HYDRA_DMD_DVBS2_CRC_ERRORS_ADDR_OFFSET +
		 HYDRA_DMD_STATUS_OFFSET(state->demod)),
		(7 * माप(u32)),
		(u8 *) &reg[0]);

	चयन (p->delivery_प्रणाली) अणु
	हाल SYS_DSS:
	हाल SYS_DVBS:
		p->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		p->post_bit_error.stat[0].uvalue = reg[5];
		p->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		p->post_bit_count.stat[0].uvalue = reg[6];
		अवरोध;
	हाल SYS_DVBS2:
		p->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		p->post_bit_error.stat[0].uvalue = reg[1];
		p->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		p->post_bit_count.stat[0].uvalue = reg[2];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&state->base->status_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	पूर्णांक stat;
	u32 reg_data = 0;

	mutex_lock(&state->base->status_lock);
	HYDRA_DEMOD_STATUS_LOCK(state, state->demod);
	stat = पढ़ो_रेजिस्टर(state, (HYDRA_DMD_STATUS_INPUT_POWER_ADDR +
				     HYDRA_DMD_STATUS_OFFSET(state->demod)),
			     &reg_data);
	HYDRA_DEMOD_STATUS_UNLOCK(state, state->demod);
	mutex_unlock(&state->base->status_lock);

	p->strength.stat[0].scale = FE_SCALE_DECIBEL;
	p->strength.stat[0].svalue = (s16) reg_data * 10; /* fix scale */

	वापस stat;
पूर्ण

अटल पूर्णांक पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा mxl *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 reg_data = 0;

	mutex_lock(&state->base->status_lock);
	HYDRA_DEMOD_STATUS_LOCK(state, state->demod);
	पढ़ो_रेजिस्टर(state, (HYDRA_DMD_LOCK_STATUS_ADDR_OFFSET +
			     HYDRA_DMD_STATUS_OFFSET(state->demod)),
			     &reg_data);
	HYDRA_DEMOD_STATUS_UNLOCK(state, state->demod);
	mutex_unlock(&state->base->status_lock);

	*status = (reg_data == 1) ? 0x1f : 0;

	/* संकेत statistics */

	/* संकेत strength is always available */
	पढ़ो_संकेत_strength(fe);

	अगर (*status & FE_HAS_CARRIER)
		पढ़ो_snr(fe);
	अन्यथा
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	अगर (*status & FE_HAS_SYNC)
		पढ़ो_ber(fe);
	अन्यथा अणु
		p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tune(काष्ठा dvb_frontend *fe, bool re_tune,
		अचिन्हित पूर्णांक mode_flags,
		अचिन्हित पूर्णांक *delay, क्रमागत fe_status *status)
अणु
	काष्ठा mxl *state = fe->demodulator_priv;
	पूर्णांक r = 0;

	*delay = HZ / 2;
	अगर (re_tune) अणु
		r = set_parameters(fe);
		अगर (r)
			वापस r;
		state->tune_समय = jअगरfies;
	पूर्ण

	वापस पढ़ो_status(fe, status);
पूर्ण

अटल क्रमागत fe_code_rate conv_fec(क्रमागत MXL_HYDRA_FEC_E fec)
अणु
	क्रमागत fe_code_rate fec2fec[11] = अणु
		FEC_NONE, FEC_1_2, FEC_3_5, FEC_2_3,
		FEC_3_4, FEC_4_5, FEC_5_6, FEC_6_7,
		FEC_7_8, FEC_8_9, FEC_9_10
	पूर्ण;

	अगर (fec > MXL_HYDRA_FEC_9_10)
		वापस FEC_NONE;
	वापस fec2fec[fec];
पूर्ण

अटल पूर्णांक get_frontend(काष्ठा dvb_frontend *fe,
			काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा mxl *state = fe->demodulator_priv;
	u32 reg_data[MXL_DEMOD_CHAN_PARAMS_BUFF_SIZE];
	u32 freq;

	mutex_lock(&state->base->status_lock);
	HYDRA_DEMOD_STATUS_LOCK(state, state->demod);
	पढ़ो_रेजिस्टर_block(state,
		(HYDRA_DMD_STANDARD_ADDR_OFFSET +
		HYDRA_DMD_STATUS_OFFSET(state->demod)),
		(MXL_DEMOD_CHAN_PARAMS_BUFF_SIZE * 4), /* 25 * 4 bytes */
		(u8 *) &reg_data[0]);
	/* पढ़ो demod channel parameters */
	पढ़ो_रेजिस्टर_block(state,
		(HYDRA_DMD_STATUS_CENTER_FREQ_IN_KHZ_ADDR +
		HYDRA_DMD_STATUS_OFFSET(state->demod)),
		(4), /* 4 bytes */
		(u8 *) &freq);
	HYDRA_DEMOD_STATUS_UNLOCK(state, state->demod);
	mutex_unlock(&state->base->status_lock);

	dev_dbg(state->i2cdev, "freq=%u delsys=%u srate=%u\n",
		freq * 1000, reg_data[DMD_STANDARD_ADDR],
		reg_data[DMD_SYMBOL_RATE_ADDR]);
	p->symbol_rate = reg_data[DMD_SYMBOL_RATE_ADDR];
	p->frequency = freq;
	/*
	 * p->delivery_प्रणाली =
	 *	(MXL_HYDRA_BCAST_STD_E) regData[DMD_STANDARD_ADDR];
	 * p->inversion =
	 *	(MXL_HYDRA_SPECTRUM_E) regData[DMD_SPECTRUM_INVERSION_ADDR];
	 * freqSearchRangeKHz =
	 *	(regData[DMD_FREQ_SEARCH_RANGE_IN_KHZ_ADDR]);
	 */

	p->fec_inner = conv_fec(reg_data[DMD_FEC_CODE_RATE_ADDR]);
	चयन (p->delivery_प्रणाली) अणु
	हाल SYS_DSS:
		अवरोध;
	हाल SYS_DVBS2:
		चयन ((क्रमागत MXL_HYDRA_PILOTS_E)
			reg_data[DMD_DVBS2_PILOT_ON_OFF_ADDR]) अणु
		हाल MXL_HYDRA_PILOTS_OFF:
			p->pilot = PILOT_OFF;
			अवरोध;
		हाल MXL_HYDRA_PILOTS_ON:
			p->pilot = PILOT_ON;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		fallthrough;
	हाल SYS_DVBS:
		चयन ((क्रमागत MXL_HYDRA_MODULATION_E)
			reg_data[DMD_MODULATION_SCHEME_ADDR]) अणु
		हाल MXL_HYDRA_MOD_QPSK:
			p->modulation = QPSK;
			अवरोध;
		हाल MXL_HYDRA_MOD_8PSK:
			p->modulation = PSK_8;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		चयन ((क्रमागत MXL_HYDRA_ROLLOFF_E)
			reg_data[DMD_SPECTRUM_ROLL_OFF_ADDR]) अणु
		हाल MXL_HYDRA_ROLLOFF_0_20:
			p->rolloff = ROLLOFF_20;
			अवरोध;
		हाल MXL_HYDRA_ROLLOFF_0_35:
			p->rolloff = ROLLOFF_35;
			अवरोध;
		हाल MXL_HYDRA_ROLLOFF_0_25:
			p->rolloff = ROLLOFF_25;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक set_input(काष्ठा dvb_frontend *fe, पूर्णांक input)
अणु
	काष्ठा mxl *state = fe->demodulator_priv;

	state->tuner = input;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops mxl_ops = अणु
	.delsys = अणु SYS_DVBS, SYS_DVBS2, SYS_DSS पूर्ण,
	.info = अणु
		.name			= "MaxLinear MxL5xx DVB-S/S2 tuner-demodulator",
		.frequency_min_hz	=  300 * MHz,
		.frequency_max_hz	= 2350 * MHz,
		.symbol_rate_min	= 1000000,
		.symbol_rate_max	= 45000000,
		.caps			= FE_CAN_INVERSION_AUTO |
					  FE_CAN_FEC_AUTO       |
					  FE_CAN_QPSK           |
					  FE_CAN_2G_MODULATION
	पूर्ण,
	.init				= init,
	.release                        = release,
	.get_frontend_algo              = get_algo,
	.tune                           = tune,
	.पढ़ो_status			= पढ़ो_status,
	.sleep				= sleep,
	.get_frontend                   = get_frontend,
	.diseqc_send_master_cmd		= send_master_cmd,
पूर्ण;

अटल काष्ठा mxl_base *match_base(काष्ठा i2c_adapter  *i2c, u8 adr)
अणु
	काष्ठा mxl_base *p;

	list_क्रम_each_entry(p, &mxllist, mxllist)
		अगर (p->i2c == i2c && p->adr == adr)
			वापस p;
	वापस शून्य;
पूर्ण

अटल व्योम cfg_dev_xtal(काष्ठा mxl *state, u32 freq, u32 cap, u32 enable)
अणु
	अगर (state->base->can_clkout || !enable)
		update_by_mnemonic(state, 0x90200054, 23, 1, enable);

	अगर (freq == 24000000)
		ग_लिखो_रेजिस्टर(state, HYDRA_CRYSTAL_SETTING, 0);
	अन्यथा
		ग_लिखो_रेजिस्टर(state, HYDRA_CRYSTAL_SETTING, 1);

	ग_लिखो_रेजिस्टर(state, HYDRA_CRYSTAL_CAP, cap);
पूर्ण

अटल u32 get_big_endian(u8 num_of_bits, स्थिर u8 buf[])
अणु
	u32 ret_value = 0;

	चयन (num_of_bits) अणु
	हाल 24:
		ret_value = (((u32) buf[0]) << 16) |
			(((u32) buf[1]) << 8) | buf[2];
		अवरोध;
	हाल 32:
		ret_value = (((u32) buf[0]) << 24) |
			(((u32) buf[1]) << 16) |
			(((u32) buf[2]) << 8) | buf[3];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret_value;
पूर्ण

अटल पूर्णांक ग_लिखो_fw_segment(काष्ठा mxl *state,
			    u32 mem_addr, u32 total_size, u8 *data_ptr)
अणु
	पूर्णांक status;
	u32 data_count = 0;
	u32 size = 0;
	u32 orig_size = 0;
	u8 *w_buf_ptr = शून्य;
	u32 block_size = ((MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH -
			 (MXL_HYDRA_I2C_HDR_SIZE +
			  MXL_HYDRA_REG_SIZE_IN_BYTES)) / 4) * 4;
	u8 w_msg_buffer[MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH -
		      (MXL_HYDRA_I2C_HDR_SIZE + MXL_HYDRA_REG_SIZE_IN_BYTES)];

	करो अणु
		size = orig_size = (((u32)(data_count + block_size)) > total_size) ?
			(total_size - data_count) : block_size;

		अगर (orig_size & 3)
			size = (orig_size + 4) & ~3;
		w_buf_ptr = &w_msg_buffer[0];
		स_रखो((व्योम *) w_buf_ptr, 0, size);
		स_नकल((व्योम *) w_buf_ptr, (व्योम *) data_ptr, orig_size);
		convert_endian(1, size, w_buf_ptr);
		status  = ग_लिखो_firmware_block(state, mem_addr, size, w_buf_ptr);
		अगर (status)
			वापस status;
		data_count += size;
		mem_addr   += size;
		data_ptr   += size;
	पूर्ण जबतक (data_count < total_size);

	वापस status;
पूर्ण

अटल पूर्णांक करो_firmware_करोwnload(काष्ठा mxl *state, u8 *mbin_buffer_ptr,
				u32 mbin_buffer_size)

अणु
	पूर्णांक status;
	u32 index = 0;
	u32 seg_length = 0;
	u32 seg_address = 0;
	काष्ठा MBIN_खाता_T *mbin_ptr  = (काष्ठा MBIN_खाता_T *)mbin_buffer_ptr;
	काष्ठा MBIN_SEGMENT_T *segment_ptr;
	क्रमागत MXL_BOOL_E xcpu_fw_flag = MXL_FALSE;

	अगर (mbin_ptr->header.id != MBIN_खाता_HEADER_ID) अणु
		dev_err(state->i2cdev, "%s: Invalid file header ID (%c)\n",
		       __func__, mbin_ptr->header.id);
		वापस -EINVAL;
	पूर्ण
	status = ग_लिखो_रेजिस्टर(state, FW_DL_SIGN_ADDR, 0);
	अगर (status)
		वापस status;
	segment_ptr = (काष्ठा MBIN_SEGMENT_T *) (&mbin_ptr->data[0]);
	क्रम (index = 0; index < mbin_ptr->header.num_segments; index++) अणु
		अगर (segment_ptr->header.id != MBIN_SEGMENT_HEADER_ID) अणु
			dev_err(state->i2cdev, "%s: Invalid segment header ID (%c)\n",
			       __func__, segment_ptr->header.id);
			वापस -EINVAL;
		पूर्ण
		seg_length  = get_big_endian(24,
					    &(segment_ptr->header.len24[0]));
		seg_address = get_big_endian(32,
					    &(segment_ptr->header.address[0]));

		अगर (state->base->type == MXL_HYDRA_DEVICE_568) अणु
			अगर ((((seg_address & 0x90760000) == 0x90760000) ||
			     ((seg_address & 0x90740000) == 0x90740000)) &&
			    (xcpu_fw_flag == MXL_FALSE)) अणु
				update_by_mnemonic(state, 0x8003003C, 0, 1, 1);
				msleep(200);
				ग_लिखो_रेजिस्टर(state, 0x90720000, 0);
				usleep_range(10000, 11000);
				xcpu_fw_flag = MXL_TRUE;
			पूर्ण
			status = ग_लिखो_fw_segment(state, seg_address,
						  seg_length,
						  (u8 *) segment_ptr->data);
		पूर्ण अन्यथा अणु
			अगर (((seg_address & 0x90760000) != 0x90760000) &&
			    ((seg_address & 0x90740000) != 0x90740000))
				status = ग_लिखो_fw_segment(state, seg_address,
					seg_length, (u8 *) segment_ptr->data);
		पूर्ण
		अगर (status)
			वापस status;
		segment_ptr = (काष्ठा MBIN_SEGMENT_T *)
			&(segment_ptr->data[((seg_length + 3) / 4) * 4]);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक check_fw(काष्ठा mxl *state, u8 *mbin, u32 mbin_len)
अणु
	काष्ठा MBIN_खाता_HEADER_T *fh = (काष्ठा MBIN_खाता_HEADER_T *) mbin;
	u32 flen = (fh->image_size24[0] << 16) |
		(fh->image_size24[1] <<  8) | fh->image_size24[2];
	u8 *fw, cs = 0;
	u32 i;

	अगर (fh->id != 'M' || fh->fmt_version != '1' || flen > 0x3FFF0) अणु
		dev_info(state->i2cdev, "Invalid FW Header\n");
		वापस -1;
	पूर्ण
	fw = mbin + माप(काष्ठा MBIN_खाता_HEADER_T);
	क्रम (i = 0; i < flen; i += 1)
		cs += fw[i];
	अगर (cs != fh->image_checksum) अणु
		dev_info(state->i2cdev, "Invalid FW Checksum\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक firmware_करोwnload(काष्ठा mxl *state, u8 *mbin, u32 mbin_len)
अणु
	पूर्णांक status;
	u32 reg_data = 0;
	काष्ठा MXL_HYDRA_SKU_COMMAND_T dev_sku_cfg;
	u8 cmd_size = माप(काष्ठा MXL_HYDRA_SKU_COMMAND_T);
	u8 cmd_buff[माप(काष्ठा MXL_HYDRA_SKU_COMMAND_T) + 6];

	अगर (check_fw(state, mbin, mbin_len))
		वापस -1;

	/* put CPU पूर्णांकo reset */
	status = update_by_mnemonic(state, 0x8003003C, 0, 1, 0);
	अगर (status)
		वापस status;
	usleep_range(1000, 2000);

	/* Reset TX FIFO's, BBAND, XBAR */
	status = ग_लिखो_रेजिस्टर(state, HYDRA_RESET_TRANSPORT_FIFO_REG,
				HYDRA_RESET_TRANSPORT_FIFO_DATA);
	अगर (status)
		वापस status;
	status = ग_लिखो_रेजिस्टर(state, HYDRA_RESET_BBAND_REG,
				HYDRA_RESET_BBAND_DATA);
	अगर (status)
		वापस status;
	status = ग_लिखो_रेजिस्टर(state, HYDRA_RESET_XBAR_REG,
				HYDRA_RESET_XBAR_DATA);
	अगर (status)
		वापस status;

	/* Disable घड़ी to Baseband, Wideband, SerDes,
	 * Alias ext & Transport modules
	 */
	status = ग_लिखो_रेजिस्टर(state, HYDRA_MODULES_CLK_2_REG,
				HYDRA_DISABLE_CLK_2);
	अगर (status)
		वापस status;
	/* Clear Software & Host पूर्णांकerrupt status - (Clear on पढ़ो) */
	status = पढ़ो_रेजिस्टर(state, HYDRA_PRCM_ROOT_CLK_REG, &reg_data);
	अगर (status)
		वापस status;
	status = करो_firmware_करोwnload(state, mbin, mbin_len);
	अगर (status)
		वापस status;

	अगर (state->base->type == MXL_HYDRA_DEVICE_568) अणु
		usleep_range(10000, 11000);

		/* bring XCPU out of reset */
		status = ग_लिखो_रेजिस्टर(state, 0x90720000, 1);
		अगर (status)
			वापस status;
		msleep(500);

		/* Enable XCPU UART message processing in MCPU */
		status = ग_लिखो_रेजिस्टर(state, 0x9076B510, 1);
		अगर (status)
			वापस status;
	पूर्ण अन्यथा अणु
		/* Bring CPU out of reset */
		status = update_by_mnemonic(state, 0x8003003C, 0, 1, 1);
		अगर (status)
			वापस status;
		/* Wait until FW boots */
		msleep(150);
	पूर्ण

	/* Initialize XPT XBAR */
	status = ग_लिखो_रेजिस्टर(state, XPT_DMD0_BASEADDR, 0x76543210);
	अगर (status)
		वापस status;

	अगर (!firmware_is_alive(state))
		वापस -1;

	dev_info(state->i2cdev, "Hydra FW alive. Hail!\n");

	/* someबार रेजिस्टर values are wrong लघुly
	 * after first heart beats
	 */
	msleep(50);

	dev_sku_cfg.sku_type = state->base->sku_type;
	BUILD_HYDRA_CMD(MXL_HYDRA_DEV_CFG_SKU_CMD, MXL_CMD_WRITE,
			cmd_size, &dev_sku_cfg, cmd_buff);
	status = send_command(state, cmd_size + MXL_HYDRA_CMD_HEADER_SIZE,
			      &cmd_buff[0]);

	वापस status;
पूर्ण

अटल पूर्णांक cfg_ts_pad_mux(काष्ठा mxl *state, क्रमागत MXL_BOOL_E enable_serial_ts)
अणु
	पूर्णांक status = 0;
	u32 pad_mux_value = 0;

	अगर (enable_serial_ts == MXL_TRUE) अणु
		pad_mux_value = 0;
		अगर ((state->base->type == MXL_HYDRA_DEVICE_541) ||
		    (state->base->type == MXL_HYDRA_DEVICE_541S))
			pad_mux_value = 2;
	पूर्ण अन्यथा अणु
		अगर ((state->base->type == MXL_HYDRA_DEVICE_581) ||
		    (state->base->type == MXL_HYDRA_DEVICE_581S))
			pad_mux_value = 2;
		अन्यथा
			pad_mux_value = 3;
	पूर्ण

	चयन (state->base->type) अणु
	हाल MXL_HYDRA_DEVICE_561:
	हाल MXL_HYDRA_DEVICE_581:
	हाल MXL_HYDRA_DEVICE_541:
	हाल MXL_HYDRA_DEVICE_541S:
	हाल MXL_HYDRA_DEVICE_561S:
	हाल MXL_HYDRA_DEVICE_581S:
		status |= update_by_mnemonic(state, 0x90000170, 24, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000170, 28, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 0, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 4, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 8, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 12, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 16, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 20, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 24, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 28, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000178, 0, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000178, 4, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000178, 8, 3,
					     pad_mux_value);
		अवरोध;

	हाल MXL_HYDRA_DEVICE_544:
	हाल MXL_HYDRA_DEVICE_542:
		status |= update_by_mnemonic(state, 0x9000016C, 4, 3, 1);
		status |= update_by_mnemonic(state, 0x9000016C, 8, 3, 0);
		status |= update_by_mnemonic(state, 0x9000016C, 12, 3, 0);
		status |= update_by_mnemonic(state, 0x9000016C, 16, 3, 0);
		status |= update_by_mnemonic(state, 0x90000170, 0, 3, 0);
		status |= update_by_mnemonic(state, 0x90000178, 12, 3, 1);
		status |= update_by_mnemonic(state, 0x90000178, 16, 3, 1);
		status |= update_by_mnemonic(state, 0x90000178, 20, 3, 1);
		status |= update_by_mnemonic(state, 0x90000178, 24, 3, 1);
		status |= update_by_mnemonic(state, 0x9000017C, 0, 3, 1);
		status |= update_by_mnemonic(state, 0x9000017C, 4, 3, 1);
		अगर (enable_serial_ts == MXL_ENABLE) अणु
			status |= update_by_mnemonic(state,
				0x90000170, 4, 3, 0);
			status |= update_by_mnemonic(state,
				0x90000170, 8, 3, 0);
			status |= update_by_mnemonic(state,
				0x90000170, 12, 3, 0);
			status |= update_by_mnemonic(state,
				0x90000170, 16, 3, 0);
			status |= update_by_mnemonic(state,
				0x90000170, 20, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000170, 24, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000170, 28, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 0, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 4, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 8, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 12, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 16, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 20, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 24, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 28, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000178, 0, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000178, 4, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000178, 8, 3, 2);
		पूर्ण अन्यथा अणु
			status |= update_by_mnemonic(state,
				0x90000170, 4, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 8, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 12, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 16, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 20, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 24, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 28, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 0, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 4, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 8, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 12, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 16, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 20, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000174, 24, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000174, 28, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000178, 0, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000178, 4, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000178, 8, 3, 1);
		पूर्ण
		अवरोध;

	हाल MXL_HYDRA_DEVICE_568:
		अगर (enable_serial_ts == MXL_FALSE) अणु
			status |= update_by_mnemonic(state,
				0x9000016C, 8, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000016C, 12, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000016C, 16, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000016C, 20, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000016C, 24, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000016C, 28, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 0, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 4, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 8, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 12, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 16, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 20, 3, 5);

			status |= update_by_mnemonic(state,
				0x90000170, 24, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 0, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 4, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 8, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 12, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 16, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 20, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 24, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 28, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000178, 0, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000178, 4, 3, pad_mux_value);

			status |= update_by_mnemonic(state,
				0x90000178, 8, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000178, 12, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000178, 16, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000178, 20, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000178, 24, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000178, 28, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000017C, 0, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000017C, 4, 3, 5);
		पूर्ण अन्यथा अणु
			status |= update_by_mnemonic(state,
				0x90000170, 4, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000170, 8, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000170, 12, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000170, 16, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000170, 20, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000170, 24, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000170, 28, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 0, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 4, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 8, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 12, 3, pad_mux_value);
		पूर्ण
		अवरोध;


	हाल MXL_HYDRA_DEVICE_584:
	शेष:
		status |= update_by_mnemonic(state,
			0x90000170, 4, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000170, 8, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000170, 12, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000170, 16, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000170, 20, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000170, 24, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000170, 28, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000174, 0, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000174, 4, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000174, 8, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000174, 12, 3, pad_mux_value);
		अवरोध;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक set_drive_strength(काष्ठा mxl *state,
		क्रमागत MXL_HYDRA_TS_DRIVE_STRENGTH_E ts_drive_strength)
अणु
	पूर्णांक stat = 0;
	u32 val;

	पढ़ो_रेजिस्टर(state, 0x90000194, &val);
	dev_info(state->i2cdev, "DIGIO = %08x\n", val);
	dev_info(state->i2cdev, "set drive_strength = %u\n", ts_drive_strength);


	stat |= update_by_mnemonic(state, 0x90000194, 0, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x90000194, 20, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x90000194, 24, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x90000198, 12, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x90000198, 16, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x90000198, 20, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x90000198, 24, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x9000019C, 0, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x9000019C, 4, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x9000019C, 8, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x9000019C, 24, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x9000019C, 28, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x900001A0, 0, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x900001A0, 4, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x900001A0, 20, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x900001A0, 24, 3, ts_drive_strength);
	stat |= update_by_mnemonic(state, 0x900001A0, 28, 3, ts_drive_strength);

	वापस stat;
पूर्ण

अटल पूर्णांक enable_tuner(काष्ठा mxl *state, u32 tuner, u32 enable)
अणु
	पूर्णांक stat = 0;
	काष्ठा MXL_HYDRA_TUNER_CMD ctrl_tuner_cmd;
	u8 cmd_size = माप(ctrl_tuner_cmd);
	u8 cmd_buff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];
	u32 val, count = 10;

	ctrl_tuner_cmd.tuner_id = tuner;
	ctrl_tuner_cmd.enable = enable;
	BUILD_HYDRA_CMD(MXL_HYDRA_TUNER_ACTIVATE_CMD, MXL_CMD_WRITE,
			cmd_size, &ctrl_tuner_cmd, cmd_buff);
	stat = send_command(state, cmd_size + MXL_HYDRA_CMD_HEADER_SIZE,
			    &cmd_buff[0]);
	अगर (stat)
		वापस stat;
	पढ़ो_रेजिस्टर(state, HYDRA_TUNER_ENABLE_COMPLETE, &val);
	जबतक (--count && ((val >> tuner) & 1) != enable) अणु
		msleep(20);
		पढ़ो_रेजिस्टर(state, HYDRA_TUNER_ENABLE_COMPLETE, &val);
	पूर्ण
	अगर (!count)
		वापस -1;
	पढ़ो_रेजिस्टर(state, HYDRA_TUNER_ENABLE_COMPLETE, &val);
	dev_dbg(state->i2cdev, "tuner %u ready = %u\n",
		tuner, (val >> tuner) & 1);

	वापस 0;
पूर्ण


अटल पूर्णांक config_ts(काष्ठा mxl *state, क्रमागत MXL_HYDRA_DEMOD_ID_E demod_id,
		     काष्ठा MXL_HYDRA_MPEGOUT_PARAM_T *mpeg_out_param_ptr)
अणु
	पूर्णांक status = 0;
	u32 nco_count_min = 0;
	u32 clk_type = 0;

	काष्ठा MXL_REG_FIELD_T xpt_sync_polarity[MXL_HYDRA_DEMOD_MAX] = अणु
		अणु0x90700010, 8, 1पूर्ण, अणु0x90700010, 9, 1पूर्ण,
		अणु0x90700010, 10, 1पूर्ण, अणु0x90700010, 11, 1पूर्ण,
		अणु0x90700010, 12, 1पूर्ण, अणु0x90700010, 13, 1पूर्ण,
		अणु0x90700010, 14, 1पूर्ण, अणु0x90700010, 15, 1पूर्ण पूर्ण;
	काष्ठा MXL_REG_FIELD_T xpt_घड़ी_polarity[MXL_HYDRA_DEMOD_MAX] = अणु
		अणु0x90700010, 16, 1पूर्ण, अणु0x90700010, 17, 1पूर्ण,
		अणु0x90700010, 18, 1पूर्ण, अणु0x90700010, 19, 1पूर्ण,
		अणु0x90700010, 20, 1पूर्ण, अणु0x90700010, 21, 1पूर्ण,
		अणु0x90700010, 22, 1पूर्ण, अणु0x90700010, 23, 1पूर्ण पूर्ण;
	काष्ठा MXL_REG_FIELD_T xpt_valid_polarity[MXL_HYDRA_DEMOD_MAX] = अणु
		अणु0x90700014, 0, 1पूर्ण, अणु0x90700014, 1, 1पूर्ण,
		अणु0x90700014, 2, 1पूर्ण, अणु0x90700014, 3, 1पूर्ण,
		अणु0x90700014, 4, 1पूर्ण, अणु0x90700014, 5, 1पूर्ण,
		अणु0x90700014, 6, 1पूर्ण, अणु0x90700014, 7, 1पूर्ण पूर्ण;
	काष्ठा MXL_REG_FIELD_T xpt_ts_घड़ी_phase[MXL_HYDRA_DEMOD_MAX] = अणु
		अणु0x90700018, 0, 3पूर्ण, अणु0x90700018, 4, 3पूर्ण,
		अणु0x90700018, 8, 3पूर्ण, अणु0x90700018, 12, 3पूर्ण,
		अणु0x90700018, 16, 3पूर्ण, अणु0x90700018, 20, 3पूर्ण,
		अणु0x90700018, 24, 3पूर्ण, अणु0x90700018, 28, 3पूर्ण पूर्ण;
	काष्ठा MXL_REG_FIELD_T xpt_lsb_first[MXL_HYDRA_DEMOD_MAX] = अणु
		अणु0x9070000C, 16, 1पूर्ण, अणु0x9070000C, 17, 1पूर्ण,
		अणु0x9070000C, 18, 1पूर्ण, अणु0x9070000C, 19, 1पूर्ण,
		अणु0x9070000C, 20, 1पूर्ण, अणु0x9070000C, 21, 1पूर्ण,
		अणु0x9070000C, 22, 1पूर्ण, अणु0x9070000C, 23, 1पूर्ण पूर्ण;
	काष्ठा MXL_REG_FIELD_T xpt_sync_byte[MXL_HYDRA_DEMOD_MAX] = अणु
		अणु0x90700010, 0, 1पूर्ण, अणु0x90700010, 1, 1पूर्ण,
		अणु0x90700010, 2, 1पूर्ण, अणु0x90700010, 3, 1पूर्ण,
		अणु0x90700010, 4, 1पूर्ण, अणु0x90700010, 5, 1पूर्ण,
		अणु0x90700010, 6, 1पूर्ण, अणु0x90700010, 7, 1पूर्ण पूर्ण;
	काष्ठा MXL_REG_FIELD_T xpt_enable_output[MXL_HYDRA_DEMOD_MAX] = अणु
		अणु0x9070000C, 0, 1पूर्ण, अणु0x9070000C, 1, 1पूर्ण,
		अणु0x9070000C, 2, 1पूर्ण, अणु0x9070000C, 3, 1पूर्ण,
		अणु0x9070000C, 4, 1पूर्ण, अणु0x9070000C, 5, 1पूर्ण,
		अणु0x9070000C, 6, 1पूर्ण, अणु0x9070000C, 7, 1पूर्ण पूर्ण;
	काष्ठा MXL_REG_FIELD_T xpt_err_replace_sync[MXL_HYDRA_DEMOD_MAX] = अणु
		अणु0x9070000C, 24, 1पूर्ण, अणु0x9070000C, 25, 1पूर्ण,
		अणु0x9070000C, 26, 1पूर्ण, अणु0x9070000C, 27, 1पूर्ण,
		अणु0x9070000C, 28, 1पूर्ण, अणु0x9070000C, 29, 1पूर्ण,
		अणु0x9070000C, 30, 1पूर्ण, अणु0x9070000C, 31, 1पूर्ण पूर्ण;
	काष्ठा MXL_REG_FIELD_T xpt_err_replace_valid[MXL_HYDRA_DEMOD_MAX] = अणु
		अणु0x90700014, 8, 1पूर्ण, अणु0x90700014, 9, 1पूर्ण,
		अणु0x90700014, 10, 1पूर्ण, अणु0x90700014, 11, 1पूर्ण,
		अणु0x90700014, 12, 1पूर्ण, अणु0x90700014, 13, 1पूर्ण,
		अणु0x90700014, 14, 1पूर्ण, अणु0x90700014, 15, 1पूर्ण पूर्ण;
	काष्ठा MXL_REG_FIELD_T xpt_continuous_घड़ी[MXL_HYDRA_DEMOD_MAX] = अणु
		अणु0x907001D4, 0, 1पूर्ण, अणु0x907001D4, 1, 1पूर्ण,
		अणु0x907001D4, 2, 1पूर्ण, अणु0x907001D4, 3, 1पूर्ण,
		अणु0x907001D4, 4, 1पूर्ण, अणु0x907001D4, 5, 1पूर्ण,
		अणु0x907001D4, 6, 1पूर्ण, अणु0x907001D4, 7, 1पूर्ण पूर्ण;
	काष्ठा MXL_REG_FIELD_T xpt_nco_घड़ी_rate[MXL_HYDRA_DEMOD_MAX] = अणु
		अणु0x90700044, 16, 80पूर्ण, अणु0x90700044, 16, 81पूर्ण,
		अणु0x90700044, 16, 82पूर्ण, अणु0x90700044, 16, 83पूर्ण,
		अणु0x90700044, 16, 84पूर्ण, अणु0x90700044, 16, 85पूर्ण,
		अणु0x90700044, 16, 86पूर्ण, अणु0x90700044, 16, 87पूर्ण पूर्ण;

	demod_id = state->base->ts_map[demod_id];

	अगर (mpeg_out_param_ptr->enable == MXL_ENABLE) अणु
		अगर (mpeg_out_param_ptr->mpeg_mode ==
		    MXL_HYDRA_MPEG_MODE_PARALLEL) अणु
		पूर्ण अन्यथा अणु
			cfg_ts_pad_mux(state, MXL_TRUE);
			update_by_mnemonic(state,
				0x90700010, 27, 1, MXL_FALSE);
		पूर्ण
	पूर्ण

	nco_count_min =
		(u32)(MXL_HYDRA_NCO_CLK / mpeg_out_param_ptr->max_mpeg_clk_rate);

	अगर (state->base->chipversion >= 2) अणु
		status |= update_by_mnemonic(state,
			xpt_nco_घड़ी_rate[demod_id].reg_addr, /* Reg Addr */
			xpt_nco_घड़ी_rate[demod_id].lsb_pos, /* LSB pos */
			xpt_nco_घड़ी_rate[demod_id].num_of_bits, /* Num of bits */
			nco_count_min); /* Data */
	पूर्ण अन्यथा
		update_by_mnemonic(state, 0x90700044, 16, 8, nco_count_min);

	अगर (mpeg_out_param_ptr->mpeg_clk_type == MXL_HYDRA_MPEG_CLK_CONTINUOUS)
		clk_type = 1;

	अगर (mpeg_out_param_ptr->mpeg_mode < MXL_HYDRA_MPEG_MODE_PARALLEL) अणु
		status |= update_by_mnemonic(state,
			xpt_continuous_घड़ी[demod_id].reg_addr,
			xpt_continuous_घड़ी[demod_id].lsb_pos,
			xpt_continuous_घड़ी[demod_id].num_of_bits,
			clk_type);
	पूर्ण अन्यथा
		update_by_mnemonic(state, 0x907001D4, 8, 1, clk_type);

	status |= update_by_mnemonic(state,
		xpt_sync_polarity[demod_id].reg_addr,
		xpt_sync_polarity[demod_id].lsb_pos,
		xpt_sync_polarity[demod_id].num_of_bits,
		mpeg_out_param_ptr->mpeg_sync_pol);

	status |= update_by_mnemonic(state,
		xpt_valid_polarity[demod_id].reg_addr,
		xpt_valid_polarity[demod_id].lsb_pos,
		xpt_valid_polarity[demod_id].num_of_bits,
		mpeg_out_param_ptr->mpeg_valid_pol);

	status |= update_by_mnemonic(state,
		xpt_घड़ी_polarity[demod_id].reg_addr,
		xpt_घड़ी_polarity[demod_id].lsb_pos,
		xpt_घड़ी_polarity[demod_id].num_of_bits,
		mpeg_out_param_ptr->mpeg_clk_pol);

	status |= update_by_mnemonic(state,
		xpt_sync_byte[demod_id].reg_addr,
		xpt_sync_byte[demod_id].lsb_pos,
		xpt_sync_byte[demod_id].num_of_bits,
		mpeg_out_param_ptr->mpeg_sync_pulse_width);

	status |= update_by_mnemonic(state,
		xpt_ts_घड़ी_phase[demod_id].reg_addr,
		xpt_ts_घड़ी_phase[demod_id].lsb_pos,
		xpt_ts_घड़ी_phase[demod_id].num_of_bits,
		mpeg_out_param_ptr->mpeg_clk_phase);

	status |= update_by_mnemonic(state,
		xpt_lsb_first[demod_id].reg_addr,
		xpt_lsb_first[demod_id].lsb_pos,
		xpt_lsb_first[demod_id].num_of_bits,
		mpeg_out_param_ptr->lsb_or_msb_first);

	चयन (mpeg_out_param_ptr->mpeg_error_indication) अणु
	हाल MXL_HYDRA_MPEG_ERR_REPLACE_SYNC:
		status |= update_by_mnemonic(state,
			xpt_err_replace_sync[demod_id].reg_addr,
			xpt_err_replace_sync[demod_id].lsb_pos,
			xpt_err_replace_sync[demod_id].num_of_bits,
			MXL_TRUE);
		status |= update_by_mnemonic(state,
			xpt_err_replace_valid[demod_id].reg_addr,
			xpt_err_replace_valid[demod_id].lsb_pos,
			xpt_err_replace_valid[demod_id].num_of_bits,
			MXL_FALSE);
		अवरोध;

	हाल MXL_HYDRA_MPEG_ERR_REPLACE_VALID:
		status |= update_by_mnemonic(state,
			xpt_err_replace_sync[demod_id].reg_addr,
			xpt_err_replace_sync[demod_id].lsb_pos,
			xpt_err_replace_sync[demod_id].num_of_bits,
			MXL_FALSE);

		status |= update_by_mnemonic(state,
			xpt_err_replace_valid[demod_id].reg_addr,
			xpt_err_replace_valid[demod_id].lsb_pos,
			xpt_err_replace_valid[demod_id].num_of_bits,
			MXL_TRUE);
		अवरोध;

	हाल MXL_HYDRA_MPEG_ERR_INDICATION_DISABLED:
	शेष:
		status |= update_by_mnemonic(state,
			xpt_err_replace_sync[demod_id].reg_addr,
			xpt_err_replace_sync[demod_id].lsb_pos,
			xpt_err_replace_sync[demod_id].num_of_bits,
			MXL_FALSE);

		status |= update_by_mnemonic(state,
			xpt_err_replace_valid[demod_id].reg_addr,
			xpt_err_replace_valid[demod_id].lsb_pos,
			xpt_err_replace_valid[demod_id].num_of_bits,
			MXL_FALSE);

		अवरोध;

	पूर्ण

	अगर (mpeg_out_param_ptr->mpeg_mode != MXL_HYDRA_MPEG_MODE_PARALLEL) अणु
		status |= update_by_mnemonic(state,
			xpt_enable_output[demod_id].reg_addr,
			xpt_enable_output[demod_id].lsb_pos,
			xpt_enable_output[demod_id].num_of_bits,
			mpeg_out_param_ptr->enable);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक config_mux(काष्ठा mxl *state)
अणु
	update_by_mnemonic(state, 0x9070000C, 0, 1, 0);
	update_by_mnemonic(state, 0x9070000C, 1, 1, 0);
	update_by_mnemonic(state, 0x9070000C, 2, 1, 0);
	update_by_mnemonic(state, 0x9070000C, 3, 1, 0);
	update_by_mnemonic(state, 0x9070000C, 4, 1, 0);
	update_by_mnemonic(state, 0x9070000C, 5, 1, 0);
	update_by_mnemonic(state, 0x9070000C, 6, 1, 0);
	update_by_mnemonic(state, 0x9070000C, 7, 1, 0);
	update_by_mnemonic(state, 0x90700008, 0, 2, 1);
	update_by_mnemonic(state, 0x90700008, 2, 2, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक load_fw(काष्ठा mxl *state, काष्ठा mxl5xx_cfg *cfg)
अणु
	पूर्णांक stat = 0;
	u8 *buf;

	अगर (cfg->fw)
		वापस firmware_करोwnload(state, cfg->fw, cfg->fw_len);

	अगर (!cfg->fw_पढ़ो)
		वापस -1;

	buf = vदो_स्मृति(0x40000);
	अगर (!buf)
		वापस -ENOMEM;

	cfg->fw_पढ़ो(cfg->fw_priv, buf, 0x40000);
	stat = firmware_करोwnload(state, buf, 0x40000);
	vमुक्त(buf);

	वापस stat;
पूर्ण

अटल पूर्णांक validate_sku(काष्ठा mxl *state)
अणु
	u32 pad_mux_bond = 0, prcm_chip_id = 0, prcm_so_cid = 0;
	पूर्णांक status;
	u32 type = state->base->type;

	status = पढ़ो_by_mnemonic(state, 0x90000190, 0, 3, &pad_mux_bond);
	status |= पढ़ो_by_mnemonic(state, 0x80030000, 0, 12, &prcm_chip_id);
	status |= पढ़ो_by_mnemonic(state, 0x80030004, 24, 8, &prcm_so_cid);
	अगर (status)
		वापस -1;

	dev_info(state->i2cdev, "padMuxBond=%08x, prcmChipId=%08x, prcmSoCId=%08x\n",
		pad_mux_bond, prcm_chip_id, prcm_so_cid);

	अगर (prcm_chip_id != 0x560) अणु
		चयन (pad_mux_bond) अणु
		हाल MXL_HYDRA_SKU_ID_581:
			अगर (type == MXL_HYDRA_DEVICE_581)
				वापस 0;
			अगर (type == MXL_HYDRA_DEVICE_581S) अणु
				state->base->type = MXL_HYDRA_DEVICE_581;
				वापस 0;
			पूर्ण
			अवरोध;
		हाल MXL_HYDRA_SKU_ID_584:
			अगर (type == MXL_HYDRA_DEVICE_584)
				वापस 0;
			अवरोध;
		हाल MXL_HYDRA_SKU_ID_544:
			अगर (type == MXL_HYDRA_DEVICE_544)
				वापस 0;
			अगर (type == MXL_HYDRA_DEVICE_542)
				वापस 0;
			अवरोध;
		हाल MXL_HYDRA_SKU_ID_582:
			अगर (type == MXL_HYDRA_DEVICE_582)
				वापस 0;
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु

	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक get_fwinfo(काष्ठा mxl *state)
अणु
	पूर्णांक status;
	u32 val = 0;

	status = पढ़ो_by_mnemonic(state, 0x90000190, 0, 3, &val);
	अगर (status)
		वापस status;
	dev_info(state->i2cdev, "chipID=%08x\n", val);

	status = पढ़ो_by_mnemonic(state, 0x80030004, 8, 8, &val);
	अगर (status)
		वापस status;
	dev_info(state->i2cdev, "chipVer=%08x\n", val);

	status = पढ़ो_रेजिस्टर(state, HYDRA_FIRMWARE_VERSION, &val);
	अगर (status)
		वापस status;
	dev_info(state->i2cdev, "FWVer=%08x\n", val);

	state->base->fwversion = val;
	वापस status;
पूर्ण


अटल u8 ts_map1_to_1[MXL_HYDRA_DEMOD_MAX] = अणु
	MXL_HYDRA_DEMOD_ID_0,
	MXL_HYDRA_DEMOD_ID_1,
	MXL_HYDRA_DEMOD_ID_2,
	MXL_HYDRA_DEMOD_ID_3,
	MXL_HYDRA_DEMOD_ID_4,
	MXL_HYDRA_DEMOD_ID_5,
	MXL_HYDRA_DEMOD_ID_6,
	MXL_HYDRA_DEMOD_ID_7,
पूर्ण;

अटल u8 ts_map54x[MXL_HYDRA_DEMOD_MAX] = अणु
	MXL_HYDRA_DEMOD_ID_2,
	MXL_HYDRA_DEMOD_ID_3,
	MXL_HYDRA_DEMOD_ID_4,
	MXL_HYDRA_DEMOD_ID_5,
	MXL_HYDRA_DEMOD_MAX,
	MXL_HYDRA_DEMOD_MAX,
	MXL_HYDRA_DEMOD_MAX,
	MXL_HYDRA_DEMOD_MAX,
पूर्ण;

अटल पूर्णांक probe(काष्ठा mxl *state, काष्ठा mxl5xx_cfg *cfg)
अणु
	u32 chipver;
	पूर्णांक fw, status, j;
	काष्ठा MXL_HYDRA_MPEGOUT_PARAM_T mpeg_पूर्णांकerface_cfg;

	state->base->ts_map = ts_map1_to_1;

	चयन (state->base->type) अणु
	हाल MXL_HYDRA_DEVICE_581:
	हाल MXL_HYDRA_DEVICE_581S:
		state->base->can_clkout = 1;
		state->base->demod_num = 8;
		state->base->tuner_num = 1;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_581;
		अवरोध;
	हाल MXL_HYDRA_DEVICE_582:
		state->base->can_clkout = 1;
		state->base->demod_num = 8;
		state->base->tuner_num = 3;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_582;
		अवरोध;
	हाल MXL_HYDRA_DEVICE_585:
		state->base->can_clkout = 0;
		state->base->demod_num = 8;
		state->base->tuner_num = 4;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_585;
		अवरोध;
	हाल MXL_HYDRA_DEVICE_544:
		state->base->can_clkout = 0;
		state->base->demod_num = 4;
		state->base->tuner_num = 4;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_544;
		state->base->ts_map = ts_map54x;
		अवरोध;
	हाल MXL_HYDRA_DEVICE_541:
	हाल MXL_HYDRA_DEVICE_541S:
		state->base->can_clkout = 0;
		state->base->demod_num = 4;
		state->base->tuner_num = 1;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_541;
		state->base->ts_map = ts_map54x;
		अवरोध;
	हाल MXL_HYDRA_DEVICE_561:
	हाल MXL_HYDRA_DEVICE_561S:
		state->base->can_clkout = 0;
		state->base->demod_num = 6;
		state->base->tuner_num = 1;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_561;
		अवरोध;
	हाल MXL_HYDRA_DEVICE_568:
		state->base->can_clkout = 0;
		state->base->demod_num = 8;
		state->base->tuner_num = 1;
		state->base->chan_bond = 1;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_568;
		अवरोध;
	हाल MXL_HYDRA_DEVICE_542:
		state->base->can_clkout = 1;
		state->base->demod_num = 4;
		state->base->tuner_num = 3;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_542;
		state->base->ts_map = ts_map54x;
		अवरोध;
	हाल MXL_HYDRA_DEVICE_TEST:
	हाल MXL_HYDRA_DEVICE_584:
	शेष:
		state->base->can_clkout = 0;
		state->base->demod_num = 8;
		state->base->tuner_num = 4;
		state->base->sku_type = MXL_HYDRA_SKU_TYPE_584;
		अवरोध;
	पूर्ण

	status = validate_sku(state);
	अगर (status)
		वापस status;

	update_by_mnemonic(state, 0x80030014, 9, 1, 1);
	update_by_mnemonic(state, 0x8003003C, 12, 1, 1);
	status = पढ़ो_by_mnemonic(state, 0x80030000, 12, 4, &chipver);
	अगर (status)
		state->base->chipversion = 0;
	अन्यथा
		state->base->chipversion = (chipver == 2) ? 2 : 1;
	dev_info(state->i2cdev, "Hydra chip version %u\n",
		state->base->chipversion);

	cfg_dev_xtal(state, cfg->clk, cfg->cap, 0);

	fw = firmware_is_alive(state);
	अगर (!fw) अणु
		status = load_fw(state, cfg);
		अगर (status)
			वापस status;
	पूर्ण
	get_fwinfo(state);

	config_mux(state);
	mpeg_पूर्णांकerface_cfg.enable = MXL_ENABLE;
	mpeg_पूर्णांकerface_cfg.lsb_or_msb_first = MXL_HYDRA_MPEG_SERIAL_MSB_1ST;
	/*  supports only (0-104&139)MHz */
	अगर (cfg->ts_clk)
		mpeg_पूर्णांकerface_cfg.max_mpeg_clk_rate = cfg->ts_clk;
	अन्यथा
		mpeg_पूर्णांकerface_cfg.max_mpeg_clk_rate = 69; /* 139; */
	mpeg_पूर्णांकerface_cfg.mpeg_clk_phase = MXL_HYDRA_MPEG_CLK_PHASE_SHIFT_0_DEG;
	mpeg_पूर्णांकerface_cfg.mpeg_clk_pol = MXL_HYDRA_MPEG_CLK_IN_PHASE;
	/* MXL_HYDRA_MPEG_CLK_GAPPED; */
	mpeg_पूर्णांकerface_cfg.mpeg_clk_type = MXL_HYDRA_MPEG_CLK_CONTINUOUS;
	mpeg_पूर्णांकerface_cfg.mpeg_error_indication =
		MXL_HYDRA_MPEG_ERR_INDICATION_DISABLED;
	mpeg_पूर्णांकerface_cfg.mpeg_mode = MXL_HYDRA_MPEG_MODE_SERIAL_3_WIRE;
	mpeg_पूर्णांकerface_cfg.mpeg_sync_pol  = MXL_HYDRA_MPEG_ACTIVE_HIGH;
	mpeg_पूर्णांकerface_cfg.mpeg_sync_pulse_width  = MXL_HYDRA_MPEG_SYNC_WIDTH_BIT;
	mpeg_पूर्णांकerface_cfg.mpeg_valid_pol  = MXL_HYDRA_MPEG_ACTIVE_HIGH;

	क्रम (j = 0; j < state->base->demod_num; j++) अणु
		status = config_ts(state, (क्रमागत MXL_HYDRA_DEMOD_ID_E) j,
				   &mpeg_पूर्णांकerface_cfg);
		अगर (status)
			वापस status;
	पूर्ण
	set_drive_strength(state, 1);
	वापस 0;
पूर्ण

काष्ठा dvb_frontend *mxl5xx_attach(काष्ठा i2c_adapter *i2c,
	काष्ठा mxl5xx_cfg *cfg, u32 demod, u32 tuner,
	पूर्णांक (**fn_set_input)(काष्ठा dvb_frontend *, पूर्णांक))
अणु
	काष्ठा mxl *state;
	काष्ठा mxl_base *base;

	state = kzalloc(माप(काष्ठा mxl), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	state->demod = demod;
	state->tuner = tuner;
	state->tuner_in_use = 0xffffffff;
	state->i2cdev = &i2c->dev;

	base = match_base(i2c, cfg->adr);
	अगर (base) अणु
		base->count++;
		अगर (base->count > base->demod_num)
			जाओ fail;
		state->base = base;
	पूर्ण अन्यथा अणु
		base = kzalloc(माप(काष्ठा mxl_base), GFP_KERNEL);
		अगर (!base)
			जाओ fail;
		base->i2c = i2c;
		base->adr = cfg->adr;
		base->type = cfg->type;
		base->count = 1;
		mutex_init(&base->i2c_lock);
		mutex_init(&base->status_lock);
		mutex_init(&base->tune_lock);
		INIT_LIST_HEAD(&base->mxls);

		state->base = base;
		अगर (probe(state, cfg) < 0) अणु
			kमुक्त(base);
			जाओ fail;
		पूर्ण
		list_add(&base->mxllist, &mxllist);
	पूर्ण
	state->fe.ops               = mxl_ops;
	state->xbar[0]              = 4;
	state->xbar[1]              = demod;
	state->xbar[2]              = 8;
	state->fe.demodulator_priv  = state;
	*fn_set_input               = set_input;

	list_add(&state->mxl, &base->mxls);
	वापस &state->fe;

fail:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(mxl5xx_attach);

MODULE_DESCRIPTION("MaxLinear MxL5xx DVB-S/S2 tuner-demodulator driver");
MODULE_AUTHOR("Ralph and Marcus Metzler, Metzler Brothers Systementwicklung GbR");
MODULE_LICENSE("GPL v2");
