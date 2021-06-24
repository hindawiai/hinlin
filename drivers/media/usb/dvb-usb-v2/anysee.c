<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DVB USB Linux driver क्रम Anysee E30 DVB-C & DVB-T USB2.0 receiver
 *
 * Copyright (C) 2007 Antti Palosaari <crope@iki.fi>
 *
 * TODO:
 * - add smart card पढ़ोer support क्रम Conditional Access (CA)
 *
 * Card पढ़ोer in Anysee is nothing more than ISO 7816 card पढ़ोer.
 * There is no hardware CAM in any Anysee device sold.
 * In my understanding it should be implemented by making own module
 * क्रम ISO 7816 card पढ़ोer, like dvb_ca_en50221 is implemented. This
 * module रेजिस्टरs serial पूर्णांकerface that can be used to communicate
 * with any ISO 7816 smart card.
 *
 * Any help according to implement serial smart card पढ़ोer support
 * is highly welcome!
 */

#समावेश "anysee.h"
#समावेश "dvb-pll.h"
#समावेश "tda1002x.h"
#समावेश "mt352.h"
#समावेश "mt352_priv.h"
#समावेश "zl10353.h"
#समावेश "tda18212.h"
#समावेश "cx24116.h"
#समावेश "stv0900.h"
#समावेश "stv6110.h"
#समावेश "isl6423.h"
#समावेश "cxd2820r.h"

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल पूर्णांक anysee_ctrl_msg(काष्ठा dvb_usb_device *d,
		u8 *sbuf, u8 slen, u8 *rbuf, u8 rlen)
अणु
	काष्ठा anysee_state *state = d_to_priv(d);
	पूर्णांक act_len, ret, i;

	mutex_lock(&d->usb_mutex);

	स_नकल(&state->buf[0], sbuf, slen);
	state->buf[60] = state->seq++;

	dev_dbg(&d->udev->dev, "%s: >>> %*ph\n", __func__, slen, state->buf);

	/* We need receive one message more after dvb_usb_generic_rw due
	   to weird transaction flow, which is 1 x send + 2 x receive. */
	ret = dvb_usbv2_generic_rw_locked(d, state->buf, माप(state->buf),
			state->buf, माप(state->buf));
	अगर (ret)
		जाओ error_unlock;

	/* TODO FIXME: dvb_usb_generic_rw() fails rarely with error code -32
	 * (EPIPE, Broken pipe). Function supports currently msleep() as a
	 * parameter but I would not like to use it, since according to
	 * Documentation/समयrs/समयrs-howto.rst it should not be used such
	 * लघु, under < 20ms, sleeps. Repeating failed message would be
	 * better choice as not to add unwanted delays...
	 * Fixing that correctly is one of those or both;
	 * 1) use repeat अगर possible
	 * 2) add suitable delay
	 */

	/* get answer, retry few बार अगर error वापसed */
	क्रम (i = 0; i < 3; i++) अणु
		/* receive 2nd answer */
		ret = usb_bulk_msg(d->udev, usb_rcvbulkpipe(d->udev,
				d->props->generic_bulk_ctrl_endpoपूर्णांक),
				state->buf, माप(state->buf), &act_len, 2000);
		अगर (ret) अणु
			dev_dbg(&d->udev->dev,
					"%s: recv bulk message failed=%d\n",
					__func__, ret);
		पूर्ण अन्यथा अणु
			dev_dbg(&d->udev->dev, "%s: <<< %*ph\n", __func__,
					rlen, state->buf);

			अगर (state->buf[63] != 0x4f)
				dev_dbg(&d->udev->dev,
						"%s: cmd failed\n", __func__);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		/* all retries failed, it is fatal */
		dev_err(&d->udev->dev, "%s: recv bulk message failed=%d\n",
				KBUILD_MODNAME, ret);
		जाओ error_unlock;
	पूर्ण

	/* पढ़ो request, copy वापसed data to वापस buf */
	अगर (rbuf && rlen)
		स_नकल(rbuf, state->buf, rlen);

error_unlock:
	mutex_unlock(&d->usb_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक anysee_पढ़ो_reg(काष्ठा dvb_usb_device *d, u16 reg, u8 *val)
अणु
	u8 buf[] = अणुCMD_REG_READ, reg >> 8, reg & 0xff, 0x01पूर्ण;
	पूर्णांक ret;
	ret = anysee_ctrl_msg(d, buf, माप(buf), val, 1);
	dev_dbg(&d->udev->dev, "%s: reg=%04x val=%02x\n", __func__, reg, *val);
	वापस ret;
पूर्ण

अटल पूर्णांक anysee_ग_लिखो_reg(काष्ठा dvb_usb_device *d, u16 reg, u8 val)
अणु
	u8 buf[] = अणुCMD_REG_WRITE, reg >> 8, reg & 0xff, 0x01, valपूर्ण;
	dev_dbg(&d->udev->dev, "%s: reg=%04x val=%02x\n", __func__, reg, val);
	वापस anysee_ctrl_msg(d, buf, माप(buf), शून्य, 0);
पूर्ण

/* ग_लिखो single रेजिस्टर with mask */
अटल पूर्णांक anysee_wr_reg_mask(काष्ठा dvb_usb_device *d, u16 reg, u8 val,
	u8 mask)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	/* no need क्रम पढ़ो अगर whole reg is written */
	अगर (mask != 0xff) अणु
		ret = anysee_पढ़ो_reg(d, reg, &पंचांगp);
		अगर (ret)
			वापस ret;

		val &= mask;
		पंचांगp &= ~mask;
		val |= पंचांगp;
	पूर्ण

	वापस anysee_ग_लिखो_reg(d, reg, val);
पूर्ण

/* पढ़ो single रेजिस्टर with mask */
अटल पूर्णांक anysee_rd_reg_mask(काष्ठा dvb_usb_device *d, u16 reg, u8 *val,
	u8 mask)
अणु
	पूर्णांक ret, i;
	u8 पंचांगp;

	ret = anysee_पढ़ो_reg(d, reg, &पंचांगp);
	अगर (ret)
		वापस ret;

	पंचांगp &= mask;

	/* find position of the first bit */
	क्रम (i = 0; i < 8; i++) अणु
		अगर ((mask >> i) & 0x01)
			अवरोध;
	पूर्ण
	*val = पंचांगp >> i;

	वापस 0;
पूर्ण

अटल पूर्णांक anysee_get_hw_info(काष्ठा dvb_usb_device *d, u8 *id)
अणु
	u8 buf[] = अणुCMD_GET_HW_INFOपूर्ण;
	वापस anysee_ctrl_msg(d, buf, माप(buf), id, 3);
पूर्ण

अटल पूर्णांक anysee_streaming_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	u8 buf[] = अणुCMD_STREAMING_CTRL, (u8)onoff, 0x00पूर्ण;
	dev_dbg(&fe_to_d(fe)->udev->dev, "%s: onoff=%d\n", __func__, onoff);
	वापस anysee_ctrl_msg(fe_to_d(fe), buf, माप(buf), शून्य, 0);
पूर्ण

अटल पूर्णांक anysee_led_ctrl(काष्ठा dvb_usb_device *d, u8 mode, u8 पूर्णांकerval)
अणु
	u8 buf[] = अणुCMD_LED_AND_IR_CTRL, 0x01, mode, पूर्णांकervalपूर्ण;
	dev_dbg(&d->udev->dev, "%s: state=%d interval=%d\n", __func__,
			mode, पूर्णांकerval);
	वापस anysee_ctrl_msg(d, buf, माप(buf), शून्य, 0);
पूर्ण

अटल पूर्णांक anysee_ir_ctrl(काष्ठा dvb_usb_device *d, u8 onoff)
अणु
	u8 buf[] = अणुCMD_LED_AND_IR_CTRL, 0x02, onoffपूर्ण;
	dev_dbg(&d->udev->dev, "%s: onoff=%d\n", __func__, onoff);
	वापस anysee_ctrl_msg(d, buf, माप(buf), शून्य, 0);
पूर्ण

/* I2C */
अटल पूर्णांक anysee_master_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msg,
	पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	पूर्णांक ret = 0, inc, i = 0;
	u8 buf[52]; /* 4 + 48 (I2C WR USB command header + I2C WR max) */

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	जबतक (i < num) अणु
		अगर (num > i + 1 && (msg[i+1].flags & I2C_M_RD)) अणु
			अगर (msg[i].len > 2 || msg[i+1].len > 60) अणु
				ret = -EOPNOTSUPP;
				अवरोध;
			पूर्ण
			buf[0] = CMD_I2C_READ;
			buf[1] = (msg[i].addr << 1) | 0x01;
			buf[2] = msg[i].buf[0];
			buf[3] = msg[i].buf[1];
			buf[4] = msg[i].len-1;
			buf[5] = msg[i+1].len;
			ret = anysee_ctrl_msg(d, buf, 6, msg[i+1].buf,
				msg[i+1].len);
			inc = 2;
		पूर्ण अन्यथा अणु
			अगर (msg[i].len > 48) अणु
				ret = -EOPNOTSUPP;
				अवरोध;
			पूर्ण
			buf[0] = CMD_I2C_WRITE;
			buf[1] = (msg[i].addr << 1);
			buf[2] = msg[i].len;
			buf[3] = 0x01;
			स_नकल(&buf[4], msg[i].buf, msg[i].len);
			ret = anysee_ctrl_msg(d, buf, 4 + msg[i].len, शून्य, 0);
			inc = 1;
		पूर्ण
		अगर (ret)
			अवरोध;

		i += inc;
	पूर्ण

	mutex_unlock(&d->i2c_mutex);

	वापस ret ? ret : i;
पूर्ण

अटल u32 anysee_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm anysee_i2c_algo = अणु
	.master_xfer   = anysee_master_xfer,
	.functionality = anysee_i2c_func,
पूर्ण;

अटल पूर्णांक anysee_mt352_demod_init(काष्ठा dvb_frontend *fe)
अणु
	अटल u8 घड़ी_config[]   = अणु CLOCK_CTL,  0x38, 0x28 पूर्ण;
	अटल u8 reset[]          = अणु RESET,      0x80 पूर्ण;
	अटल u8 adc_ctl_1_cfg[]  = अणु ADC_CTL_1,  0x40 पूर्ण;
	अटल u8 agc_cfg[]        = अणु AGC_TARGET, 0x28, 0x20 पूर्ण;
	अटल u8 gpp_ctl_cfg[]    = अणु GPP_CTL,    0x33 पूर्ण;
	अटल u8 capt_range_cfg[] = अणु CAPT_RANGE, 0x32 पूर्ण;

	mt352_ग_लिखो(fe, घड़ी_config,   माप(घड़ी_config));
	udelay(200);
	mt352_ग_लिखो(fe, reset,          माप(reset));
	mt352_ग_लिखो(fe, adc_ctl_1_cfg,  माप(adc_ctl_1_cfg));

	mt352_ग_लिखो(fe, agc_cfg,        माप(agc_cfg));
	mt352_ग_लिखो(fe, gpp_ctl_cfg,    माप(gpp_ctl_cfg));
	mt352_ग_लिखो(fe, capt_range_cfg, माप(capt_range_cfg));

	वापस 0;
पूर्ण

/* Callbacks क्रम DVB USB */
अटल काष्ठा tda10023_config anysee_tda10023_config = अणु
	.demod_address = (0x1a >> 1),
	.invert = 0,
	.xtal   = 16000000,
	.pll_m  = 11,
	.pll_p  = 3,
	.pll_n  = 1,
	.output_mode = TDA10023_OUTPUT_MODE_PARALLEL_C,
	.deltaf = 0xfeeb,
पूर्ण;

अटल काष्ठा mt352_config anysee_mt352_config = अणु
	.demod_address = (0x1e >> 1),
	.demod_init    = anysee_mt352_demod_init,
पूर्ण;

अटल काष्ठा zl10353_config anysee_zl10353_config = अणु
	.demod_address = (0x1e >> 1),
	.parallel_ts = 1,
पूर्ण;

अटल काष्ठा zl10353_config anysee_zl10353_tda18212_config2 = अणु
	.demod_address = (0x1e >> 1),
	.parallel_ts = 1,
	.disable_i2c_gate_ctrl = 1,
	.no_tuner = 1,
	.अगर2 = 41500,
पूर्ण;

अटल काष्ठा zl10353_config anysee_zl10353_tda18212_config = अणु
	.demod_address = (0x18 >> 1),
	.parallel_ts = 1,
	.disable_i2c_gate_ctrl = 1,
	.no_tuner = 1,
	.अगर2 = 41500,
पूर्ण;

अटल काष्ठा tda10023_config anysee_tda10023_tda18212_config = अणु
	.demod_address = (0x1a >> 1),
	.xtal   = 16000000,
	.pll_m  = 12,
	.pll_p  = 3,
	.pll_n  = 1,
	.output_mode = TDA10023_OUTPUT_MODE_PARALLEL_B,
	.deltaf = 0xba02,
पूर्ण;

अटल स्थिर काष्ठा tda18212_config anysee_tda18212_config = अणु
	.अगर_dvbt_6 = 4150,
	.अगर_dvbt_7 = 4150,
	.अगर_dvbt_8 = 4150,
	.अगर_dvbc = 5000,
पूर्ण;

अटल स्थिर काष्ठा tda18212_config anysee_tda18212_config2 = अणु
	.अगर_dvbt_6 = 3550,
	.अगर_dvbt_7 = 3700,
	.अगर_dvbt_8 = 4150,
	.अगर_dvbt2_6 = 3250,
	.अगर_dvbt2_7 = 4000,
	.अगर_dvbt2_8 = 4000,
	.अगर_dvbc = 5000,
पूर्ण;

अटल काष्ठा cx24116_config anysee_cx24116_config = अणु
	.demod_address = (0xaa >> 1),
	.mpg_clk_pos_pol = 0x00,
	.i2c_wr_max = 48,
पूर्ण;

अटल काष्ठा stv0900_config anysee_stv0900_config = अणु
	.demod_address = (0xd0 >> 1),
	.demod_mode = 0,
	.xtal = 8000000,
	.clkmode = 3,
	.diseqc_mode = 2,
	.tun1_maddress = 0,
	.tun1_adc = 1, /* 1 Vpp */
	.path1_mode = 3,
पूर्ण;

अटल काष्ठा stv6110_config anysee_stv6110_config = अणु
	.i2c_address = (0xc0 >> 1),
	.mclk = 16000000,
	.clk_भाग = 1,
पूर्ण;

अटल काष्ठा isl6423_config anysee_isl6423_config = अणु
	.current_max = SEC_CURRENT_800m,
	.curlim  = SEC_CURRENT_LIM_OFF,
	.mod_बाह्य = 1,
	.addr = (0x10 >> 1),
पूर्ण;

अटल काष्ठा cxd2820r_config anysee_cxd2820r_config = अणु
	.i2c_address = 0x6d, /* (0xda >> 1) */
	.ts_mode = 0x38,
पूर्ण;

/*
 * New USB device strings: Mfr=1, Product=2, SerialNumber=0
 * Manufacturer: AMT.CO.KR
 *
 * E30 VID=04b4 PID=861f HW=2 FW=2.1 Product=????????
 * PCB: ?
 * parts: DNOS404ZH102A(MT352, DTT7579(?))
 *
 * E30 VID=04b4 PID=861f HW=2 FW=2.1 "anysee-T(LP)"
 * PCB: PCB 507T (rev1.61)
 * parts: DNOS404ZH103A(ZL10353, DTT7579(?))
 * OEA=0a OEB=00 OEC=00 OED=ff OEE=00
 * IOA=45 IOB=ff IOC=00 IOD=ff IOE=00
 *
 * E30 Plus VID=04b4 PID=861f HW=6 FW=1.0 "anysee"
 * PCB: 507CD (rev1.1)
 * parts: DNOS404ZH103A(ZL10353, DTT7579(?)), CST56I01
 * OEA=80 OEB=00 OEC=00 OED=ff OEE=fe
 * IOA=4f IOB=ff IOC=00 IOD=06 IOE=01
 * IOD[0] ZL10353 1=enabled
 * IOA[7] TS 0=enabled
 * tuner is not behind ZL10353 I2C-gate (no care अगर gate disabled or not)
 *
 * E30 C Plus VID=04b4 PID=861f HW=10 FW=1.0 "anysee-DC(LP)"
 * PCB: 507DC (rev0.2)
 * parts: TDA10023, DTOS403IH102B TM, CST56I01
 * OEA=80 OEB=00 OEC=00 OED=ff OEE=fe
 * IOA=4f IOB=ff IOC=00 IOD=26 IOE=01
 * IOD[0] TDA10023 1=enabled
 *
 * E30 S2 Plus VID=04b4 PID=861f HW=11 FW=0.1 "anysee-S2(LP)"
 * PCB: 507SI (rev2.1)
 * parts: BS2N10WCC01(CX24116, CX24118), ISL6423, TDA8024
 * OEA=80 OEB=00 OEC=ff OED=ff OEE=fe
 * IOA=4d IOB=ff IOC=00 IOD=26 IOE=01
 * IOD[0] CX24116 1=enabled
 *
 * E30 C Plus VID=1c73 PID=861f HW=15 FW=1.2 "anysee-FA(LP)"
 * PCB: 507FA (rev0.4)
 * parts: TDA10023, DTOS403IH102B TM, TDA8024
 * OEA=80 OEB=00 OEC=ff OED=ff OEE=ff
 * IOA=4d IOB=ff IOC=00 IOD=00 IOE=c0
 * IOD[5] TDA10023 1=enabled
 * IOE[0] tuner 1=enabled
 *
 * E30 Combo Plus VID=1c73 PID=861f HW=15 FW=1.2 "anysee-FA(LP)"
 * PCB: 507FA (rev1.1)
 * parts: ZL10353, TDA10023, DTOS403IH102B TM, TDA8024
 * OEA=80 OEB=00 OEC=ff OED=ff OEE=ff
 * IOA=4d IOB=ff IOC=00 IOD=00 IOE=c0
 * DVB-C:
 * IOD[5] TDA10023 1=enabled
 * IOE[0] tuner 1=enabled
 * DVB-T:
 * IOD[0] ZL10353 1=enabled
 * IOE[0] tuner 0=enabled
 * tuner is behind ZL10353 I2C-gate
 * tuner is behind TDA10023 I2C-gate
 *
 * E7 TC VID=1c73 PID=861f HW=18 FW=0.7 AMTCI=0.5 "anysee-E7TC(LP)"
 * PCB: 508TC (rev0.6)
 * parts: ZL10353, TDA10023, DNOD44CDH086A(TDA18212)
 * OEA=80 OEB=00 OEC=03 OED=f7 OEE=ff
 * IOA=4d IOB=00 IOC=cc IOD=48 IOE=e4
 * IOA[7] TS 1=enabled
 * IOE[4] TDA18212 1=enabled
 * DVB-C:
 * IOD[6] ZL10353 0=disabled
 * IOD[5] TDA10023 1=enabled
 * IOE[0] IF 1=enabled
 * DVB-T:
 * IOD[5] TDA10023 0=disabled
 * IOD[6] ZL10353 1=enabled
 * IOE[0] IF 0=enabled
 *
 * E7 S2 VID=1c73 PID=861f HW=19 FW=0.4 AMTCI=0.5 "anysee-E7S2(LP)"
 * PCB: 508S2 (rev0.7)
 * parts: DNBU10512IST(STV0903, STV6110), ISL6423
 * OEA=80 OEB=00 OEC=03 OED=f7 OEE=ff
 * IOA=4d IOB=00 IOC=c4 IOD=08 IOE=e4
 * IOA[7] TS 1=enabled
 * IOE[5] STV0903 1=enabled
 *
 * E7 T2C VID=1c73 PID=861f HW=20 FW=0.1 AMTCI=0.5 "anysee-E7T2C(LP)"
 * PCB: 508T2C (rev0.3)
 * parts: DNOQ44QCH106A(CXD2820R, TDA18212), TDA8024
 * OEA=80 OEB=00 OEC=03 OED=f7 OEE=ff
 * IOA=4d IOB=00 IOC=cc IOD=48 IOE=e4
 * IOA[7] TS 1=enabled
 * IOE[5] CXD2820R 1=enabled
 *
 * E7 PTC VID=1c73 PID=861f HW=21 FW=0.1 AMTCI=?? "anysee-E7PTC(LP)"
 * PCB: 508PTC (rev0.5)
 * parts: ZL10353, TDA10023, DNOD44CDH086A(TDA18212)
 * OEA=80 OEB=00 OEC=03 OED=f7 OEE=ff
 * IOA=4d IOB=00 IOC=cc IOD=48 IOE=e4
 * IOA[7] TS 1=enabled
 * IOE[4] TDA18212 1=enabled
 * DVB-C:
 * IOD[6] ZL10353 0=disabled
 * IOD[5] TDA10023 1=enabled
 * IOE[0] IF 1=enabled
 * DVB-T:
 * IOD[5] TDA10023 0=disabled
 * IOD[6] ZL10353 1=enabled
 * IOE[0] IF 0=enabled
 *
 * E7 PS2 VID=1c73 PID=861f HW=22 FW=0.1 AMTCI=?? "anysee-E7PS2(LP)"
 * PCB: 508PS2 (rev0.4)
 * parts: DNBU10512IST(STV0903, STV6110), ISL6423
 * OEA=80 OEB=00 OEC=03 OED=f7 OEE=ff
 * IOA=4d IOB=00 IOC=c4 IOD=08 IOE=e4
 * IOA[7] TS 1=enabled
 * IOE[5] STV0903 1=enabled
 */

अटल पूर्णांक anysee_पढ़ो_config(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा anysee_state *state = d_to_priv(d);
	पूर्णांक ret;
	u8 hw_info[3];

	/*
	 * Check which hardware we have.
	 * We must करो this call two बार to get reliable values (hw/fw bug).
	 */
	ret = anysee_get_hw_info(d, hw_info);
	अगर (ret)
		जाओ error;

	ret = anysee_get_hw_info(d, hw_info);
	अगर (ret)
		जाओ error;

	/*
	 * Meaning of these info bytes are guessed.
	 */
	dev_info(&d->udev->dev, "%s: firmware version %d.%d hardware id %d\n",
			KBUILD_MODNAME, hw_info[1], hw_info[2], hw_info[0]);

	state->hw = hw_info[0];
error:
	वापस ret;
पूर्ण

/* बाह्यal I2C gate used क्रम DNOD44CDH086A(TDA18212) tuner module */
अटल पूर्णांक anysee_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	/* enable / disable tuner access on IOE[4] */
	वापस anysee_wr_reg_mask(fe_to_d(fe), REG_IOE, (enable << 4), 0x10);
पूर्ण

अटल पूर्णांक anysee_frontend_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा anysee_state *state = fe_to_priv(fe);
	काष्ठा dvb_usb_device *d = fe_to_d(fe);
	पूर्णांक ret;
	dev_dbg(&d->udev->dev, "%s: fe=%d onoff=%d\n", __func__, fe->id, onoff);

	/* no frontend sleep control */
	अगर (onoff == 0)
		वापस 0;

	चयन (state->hw) अणु
	हाल ANYSEE_HW_507FA: /* 15 */
		/* E30 Combo Plus */
		/* E30 C Plus */

		अगर (fe->id == 0)  अणु
			/* disable DVB-T demod on IOD[0] */
			ret = anysee_wr_reg_mask(d, REG_IOD, (0 << 0), 0x01);
			अगर (ret)
				जाओ error;

			/* enable DVB-C demod on IOD[5] */
			ret = anysee_wr_reg_mask(d, REG_IOD, (1 << 5), 0x20);
			अगर (ret)
				जाओ error;

			/* enable DVB-C tuner on IOE[0] */
			ret = anysee_wr_reg_mask(d, REG_IOE, (1 << 0), 0x01);
			अगर (ret)
				जाओ error;
		पूर्ण अन्यथा अणु
			/* disable DVB-C demod on IOD[5] */
			ret = anysee_wr_reg_mask(d, REG_IOD, (0 << 5), 0x20);
			अगर (ret)
				जाओ error;

			/* enable DVB-T demod on IOD[0] */
			ret = anysee_wr_reg_mask(d, REG_IOD, (1 << 0), 0x01);
			अगर (ret)
				जाओ error;

			/* enable DVB-T tuner on IOE[0] */
			ret = anysee_wr_reg_mask(d, REG_IOE, (0 << 0), 0x01);
			अगर (ret)
				जाओ error;
		पूर्ण

		अवरोध;
	हाल ANYSEE_HW_508TC: /* 18 */
	हाल ANYSEE_HW_508PTC: /* 21 */
		/* E7 TC */
		/* E7 PTC */

		अगर (fe->id == 0)  अणु
			/* disable DVB-T demod on IOD[6] */
			ret = anysee_wr_reg_mask(d, REG_IOD, (0 << 6), 0x40);
			अगर (ret)
				जाओ error;

			/* enable DVB-C demod on IOD[5] */
			ret = anysee_wr_reg_mask(d, REG_IOD, (1 << 5), 0x20);
			अगर (ret)
				जाओ error;

			/* enable IF route on IOE[0] */
			ret = anysee_wr_reg_mask(d, REG_IOE, (1 << 0), 0x01);
			अगर (ret)
				जाओ error;
		पूर्ण अन्यथा अणु
			/* disable DVB-C demod on IOD[5] */
			ret = anysee_wr_reg_mask(d, REG_IOD, (0 << 5), 0x20);
			अगर (ret)
				जाओ error;

			/* enable DVB-T demod on IOD[6] */
			ret = anysee_wr_reg_mask(d, REG_IOD, (1 << 6), 0x40);
			अगर (ret)
				जाओ error;

			/* enable IF route on IOE[0] */
			ret = anysee_wr_reg_mask(d, REG_IOE, (0 << 0), 0x01);
			अगर (ret)
				जाओ error;
		पूर्ण

		अवरोध;
	शेष:
		ret = 0;
	पूर्ण

error:
	वापस ret;
पूर्ण

अटल पूर्णांक anysee_add_i2c_dev(काष्ठा dvb_usb_device *d, स्थिर अक्षर *type,
		u8 addr, व्योम *platक्रमm_data)
अणु
	पूर्णांक ret, num;
	काष्ठा anysee_state *state = d_to_priv(d);
	काष्ठा i2c_client *client;
	काष्ठा i2c_adapter *adapter = &d->i2c_adap;
	काष्ठा i2c_board_info board_info = अणु
		.addr = addr,
		.platक्रमm_data = platक्रमm_data,
	पूर्ण;

	strscpy(board_info.type, type, I2C_NAME_SIZE);

	/* find first मुक्त client */
	क्रम (num = 0; num < ANYSEE_I2C_CLIENT_MAX; num++) अणु
		अगर (state->i2c_client[num] == शून्य)
			अवरोध;
	पूर्ण

	dev_dbg(&d->udev->dev, "%s: num=%d\n", __func__, num);

	अगर (num == ANYSEE_I2C_CLIENT_MAX) अणु
		dev_err(&d->udev->dev, "%s: I2C client out of index\n",
				KBUILD_MODNAME);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	request_module("%s", board_info.type);

	/* रेजिस्टर I2C device */
	client = i2c_new_client_device(adapter, &board_info);
	अगर (!i2c_client_has_driver(client)) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	/* increase I2C driver usage count */
	अगर (!try_module_get(client->dev.driver->owner)) अणु
		i2c_unरेजिस्टर_device(client);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	state->i2c_client[num] = client;
	वापस 0;
err:
	dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल व्योम anysee_del_i2c_dev(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक num;
	काष्ठा anysee_state *state = d_to_priv(d);
	काष्ठा i2c_client *client;

	/* find last used client */
	num = ANYSEE_I2C_CLIENT_MAX;
	जबतक (num--) अणु
		अगर (state->i2c_client[num] != शून्य)
			अवरोध;
	पूर्ण

	dev_dbg(&d->udev->dev, "%s: num=%d\n", __func__, num);

	अगर (num == -1) अणु
		dev_err(&d->udev->dev, "%s: I2C client out of index\n",
				KBUILD_MODNAME);
		जाओ err;
	पूर्ण

	client = state->i2c_client[num];

	/* decrease I2C driver usage count */
	module_put(client->dev.driver->owner);

	/* unरेजिस्टर I2C device */
	i2c_unरेजिस्टर_device(client);

	state->i2c_client[num] = शून्य;
err:
	dev_dbg(&d->udev->dev, "%s: failed\n", __func__);
पूर्ण

अटल पूर्णांक anysee_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा anysee_state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	पूर्णांक ret = 0;
	u8 पंचांगp;
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = 0x60,
			.flags = 0,
			.len = 1,
			.buf = "\x00",
		पूर्ण, अणु
			.addr = 0x60,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = &पंचांगp,
		पूर्ण
	पूर्ण;

	चयन (state->hw) अणु
	हाल ANYSEE_HW_507T: /* 2 */
		/* E30 */

		/* attach demod */
		adap->fe[0] = dvb_attach(mt352_attach, &anysee_mt352_config,
				&d->i2c_adap);
		अगर (adap->fe[0])
			अवरोध;

		/* attach demod */
		adap->fe[0] = dvb_attach(zl10353_attach, &anysee_zl10353_config,
				&d->i2c_adap);

		अवरोध;
	हाल ANYSEE_HW_507CD: /* 6 */
		/* E30 Plus */

		/* enable DVB-T demod on IOD[0] */
		ret = anysee_wr_reg_mask(d, REG_IOD, (1 << 0), 0x01);
		अगर (ret)
			जाओ error;

		/* enable transport stream on IOA[7] */
		ret = anysee_wr_reg_mask(d, REG_IOA, (0 << 7), 0x80);
		अगर (ret)
			जाओ error;

		/* attach demod */
		adap->fe[0] = dvb_attach(zl10353_attach, &anysee_zl10353_config,
				&d->i2c_adap);

		अवरोध;
	हाल ANYSEE_HW_507DC: /* 10 */
		/* E30 C Plus */

		/* enable DVB-C demod on IOD[0] */
		ret = anysee_wr_reg_mask(d, REG_IOD, (1 << 0), 0x01);
		अगर (ret)
			जाओ error;

		/* attach demod */
		adap->fe[0] = dvb_attach(tda10023_attach,
				&anysee_tda10023_config, &d->i2c_adap, 0x48);

		अवरोध;
	हाल ANYSEE_HW_507SI: /* 11 */
		/* E30 S2 Plus */

		/* enable DVB-S/S2 demod on IOD[0] */
		ret = anysee_wr_reg_mask(d, REG_IOD, (1 << 0), 0x01);
		अगर (ret)
			जाओ error;

		/* attach demod */
		adap->fe[0] = dvb_attach(cx24116_attach, &anysee_cx24116_config,
				&d->i2c_adap);

		अवरोध;
	हाल ANYSEE_HW_507FA: /* 15 */
		/* E30 Combo Plus */
		/* E30 C Plus */

		/* enable tuner on IOE[4] */
		ret = anysee_wr_reg_mask(d, REG_IOE, (1 << 4), 0x10);
		अगर (ret)
			जाओ error;

		/* probe TDA18212 */
		पंचांगp = 0;
		ret = i2c_transfer(&d->i2c_adap, msg, 2);
		अगर (ret == 2 && पंचांगp == 0xc7) अणु
			dev_dbg(&d->udev->dev, "%s: TDA18212 found\n",
					__func__);
			state->has_tda18212 = true;
		पूर्ण
		अन्यथा
			पंचांगp = 0;

		/* disable tuner on IOE[4] */
		ret = anysee_wr_reg_mask(d, REG_IOE, (0 << 4), 0x10);
		अगर (ret)
			जाओ error;

		/* disable DVB-T demod on IOD[0] */
		ret = anysee_wr_reg_mask(d, REG_IOD, (0 << 0), 0x01);
		अगर (ret)
			जाओ error;

		/* enable DVB-C demod on IOD[5] */
		ret = anysee_wr_reg_mask(d, REG_IOD, (1 << 5), 0x20);
		अगर (ret)
			जाओ error;

		/* attach demod */
		अगर (पंचांगp == 0xc7) अणु
			/* TDA18212 config */
			adap->fe[0] = dvb_attach(tda10023_attach,
					&anysee_tda10023_tda18212_config,
					&d->i2c_adap, 0x48);

			/* I2C gate क्रम DNOD44CDH086A(TDA18212) tuner module */
			अगर (adap->fe[0])
				adap->fe[0]->ops.i2c_gate_ctrl =
						anysee_i2c_gate_ctrl;
		पूर्ण अन्यथा अणु
			/* PLL config */
			adap->fe[0] = dvb_attach(tda10023_attach,
					&anysee_tda10023_config,
					&d->i2c_adap, 0x48);
		पूर्ण

		/* अवरोध out अगर first frontend attaching fails */
		अगर (!adap->fe[0])
			अवरोध;

		/* disable DVB-C demod on IOD[5] */
		ret = anysee_wr_reg_mask(d, REG_IOD, (0 << 5), 0x20);
		अगर (ret)
			जाओ error;

		/* enable DVB-T demod on IOD[0] */
		ret = anysee_wr_reg_mask(d, REG_IOD, (1 << 0), 0x01);
		अगर (ret)
			जाओ error;

		/* attach demod */
		अगर (पंचांगp == 0xc7) अणु
			/* TDA18212 config */
			adap->fe[1] = dvb_attach(zl10353_attach,
					&anysee_zl10353_tda18212_config2,
					&d->i2c_adap);

			/* I2C gate क्रम DNOD44CDH086A(TDA18212) tuner module */
			अगर (adap->fe[1])
				adap->fe[1]->ops.i2c_gate_ctrl =
						anysee_i2c_gate_ctrl;
		पूर्ण अन्यथा अणु
			/* PLL config */
			adap->fe[1] = dvb_attach(zl10353_attach,
					&anysee_zl10353_config,
					&d->i2c_adap);
		पूर्ण

		अवरोध;
	हाल ANYSEE_HW_508TC: /* 18 */
	हाल ANYSEE_HW_508PTC: /* 21 */
		/* E7 TC */
		/* E7 PTC */

		/* disable DVB-T demod on IOD[6] */
		ret = anysee_wr_reg_mask(d, REG_IOD, (0 << 6), 0x40);
		अगर (ret)
			जाओ error;

		/* enable DVB-C demod on IOD[5] */
		ret = anysee_wr_reg_mask(d, REG_IOD, (1 << 5), 0x20);
		अगर (ret)
			जाओ error;

		/* attach demod */
		adap->fe[0] = dvb_attach(tda10023_attach,
				&anysee_tda10023_tda18212_config,
				&d->i2c_adap, 0x48);

		/* I2C gate क्रम DNOD44CDH086A(TDA18212) tuner module */
		अगर (adap->fe[0])
			adap->fe[0]->ops.i2c_gate_ctrl = anysee_i2c_gate_ctrl;

		/* अवरोध out अगर first frontend attaching fails */
		अगर (!adap->fe[0])
			अवरोध;

		/* disable DVB-C demod on IOD[5] */
		ret = anysee_wr_reg_mask(d, REG_IOD, (0 << 5), 0x20);
		अगर (ret)
			जाओ error;

		/* enable DVB-T demod on IOD[6] */
		ret = anysee_wr_reg_mask(d, REG_IOD, (1 << 6), 0x40);
		अगर (ret)
			जाओ error;

		/* attach demod */
		adap->fe[1] = dvb_attach(zl10353_attach,
				&anysee_zl10353_tda18212_config,
				&d->i2c_adap);

		/* I2C gate क्रम DNOD44CDH086A(TDA18212) tuner module */
		अगर (adap->fe[1])
			adap->fe[1]->ops.i2c_gate_ctrl = anysee_i2c_gate_ctrl;

		state->has_ci = true;

		अवरोध;
	हाल ANYSEE_HW_508S2: /* 19 */
	हाल ANYSEE_HW_508PS2: /* 22 */
		/* E7 S2 */
		/* E7 PS2 */

		/* enable DVB-S/S2 demod on IOE[5] */
		ret = anysee_wr_reg_mask(d, REG_IOE, (1 << 5), 0x20);
		अगर (ret)
			जाओ error;

		/* attach demod */
		adap->fe[0] = dvb_attach(stv0900_attach,
				&anysee_stv0900_config, &d->i2c_adap, 0);

		state->has_ci = true;

		अवरोध;
	हाल ANYSEE_HW_508T2C: /* 20 */
		/* E7 T2C */

		/* enable DVB-T/T2/C demod on IOE[5] */
		ret = anysee_wr_reg_mask(d, REG_IOE, (1 << 5), 0x20);
		अगर (ret)
			जाओ error;

		/* attach demod */
		adap->fe[0] = dvb_attach(cxd2820r_attach,
				&anysee_cxd2820r_config, &d->i2c_adap, शून्य);

		state->has_ci = true;

		अवरोध;
	पूर्ण

	अगर (!adap->fe[0]) अणु
		/* we have no frontend :-( */
		ret = -ENODEV;
		dev_err(&d->udev->dev,
				"%s: Unsupported Anysee version. Please report to <linux-media@vger.kernel.org>.\n",
				KBUILD_MODNAME);
	पूर्ण
error:
	वापस ret;
पूर्ण

अटल पूर्णांक anysee_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा anysee_state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा dvb_frontend *fe;
	पूर्णांक ret;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	चयन (state->hw) अणु
	हाल ANYSEE_HW_507T: /* 2 */
		/* E30 */

		/* attach tuner */
		fe = dvb_attach(dvb_pll_attach, adap->fe[0], (0xc2 >> 1), शून्य,
				DVB_PLL_THOMSON_DTT7579);

		अवरोध;
	हाल ANYSEE_HW_507CD: /* 6 */
		/* E30 Plus */

		/* attach tuner */
		fe = dvb_attach(dvb_pll_attach, adap->fe[0], (0xc2 >> 1),
				&d->i2c_adap, DVB_PLL_THOMSON_DTT7579);

		अवरोध;
	हाल ANYSEE_HW_507DC: /* 10 */
		/* E30 C Plus */

		/* attach tuner */
		fe = dvb_attach(dvb_pll_attach, adap->fe[0], (0xc0 >> 1),
				&d->i2c_adap, DVB_PLL_SAMSUNG_DTOS403IH102A);

		अवरोध;
	हाल ANYSEE_HW_507SI: /* 11 */
		/* E30 S2 Plus */

		/* attach LNB controller */
		fe = dvb_attach(isl6423_attach, adap->fe[0], &d->i2c_adap,
				&anysee_isl6423_config);

		अवरोध;
	हाल ANYSEE_HW_507FA: /* 15 */
		/* E30 Combo Plus */
		/* E30 C Plus */

		/* Try first attach TDA18212 silicon tuner on IOE[4], अगर that
		 * fails attach old simple PLL. */

		/* attach tuner */
		अगर (state->has_tda18212) अणु
			काष्ठा tda18212_config tda18212_config =
					anysee_tda18212_config;

			tda18212_config.fe = adap->fe[0];
			ret = anysee_add_i2c_dev(d, "tda18212", 0x60,
					&tda18212_config);
			अगर (ret)
				जाओ err;

			/* copy tuner ops क्रम 2nd FE as tuner is shared */
			अगर (adap->fe[1]) अणु
				adap->fe[1]->tuner_priv =
						adap->fe[0]->tuner_priv;
				स_नकल(&adap->fe[1]->ops.tuner_ops,
						&adap->fe[0]->ops.tuner_ops,
						माप(काष्ठा dvb_tuner_ops));
			पूर्ण

			वापस 0;
		पूर्ण अन्यथा अणु
			/* attach tuner */
			fe = dvb_attach(dvb_pll_attach, adap->fe[0],
					(0xc0 >> 1), &d->i2c_adap,
					DVB_PLL_SAMSUNG_DTOS403IH102A);

			अगर (fe && adap->fe[1]) अणु
				/* attach tuner क्रम 2nd FE */
				fe = dvb_attach(dvb_pll_attach, adap->fe[1],
						(0xc0 >> 1), &d->i2c_adap,
						DVB_PLL_SAMSUNG_DTOS403IH102A);
			पूर्ण
		पूर्ण

		अवरोध;
	हाल ANYSEE_HW_508TC: /* 18 */
	हाल ANYSEE_HW_508PTC: /* 21 */
	अणु
		/* E7 TC */
		/* E7 PTC */
		काष्ठा tda18212_config tda18212_config = anysee_tda18212_config;

		tda18212_config.fe = adap->fe[0];
		ret = anysee_add_i2c_dev(d, "tda18212", 0x60, &tda18212_config);
		अगर (ret)
			जाओ err;

		/* copy tuner ops क्रम 2nd FE as tuner is shared */
		अगर (adap->fe[1]) अणु
			adap->fe[1]->tuner_priv = adap->fe[0]->tuner_priv;
			स_नकल(&adap->fe[1]->ops.tuner_ops,
					&adap->fe[0]->ops.tuner_ops,
					माप(काष्ठा dvb_tuner_ops));
		पूर्ण

		वापस 0;
	पूर्ण
	हाल ANYSEE_HW_508S2: /* 19 */
	हाल ANYSEE_HW_508PS2: /* 22 */
		/* E7 S2 */
		/* E7 PS2 */

		/* attach tuner */
		fe = dvb_attach(stv6110_attach, adap->fe[0],
				&anysee_stv6110_config, &d->i2c_adap);

		अगर (fe) अणु
			/* attach LNB controller */
			fe = dvb_attach(isl6423_attach, adap->fe[0],
					&d->i2c_adap, &anysee_isl6423_config);
		पूर्ण

		अवरोध;

	हाल ANYSEE_HW_508T2C: /* 20 */
	अणु
		/* E7 T2C */
		काष्ठा tda18212_config tda18212_config =
				anysee_tda18212_config2;

		tda18212_config.fe = adap->fe[0];
		ret = anysee_add_i2c_dev(d, "tda18212", 0x60, &tda18212_config);
		अगर (ret)
			जाओ err;

		वापस 0;
	पूर्ण
	शेष:
		fe = शून्य;
	पूर्ण

	अगर (fe)
		ret = 0;
	अन्यथा
		ret = -ENODEV;
err:
	वापस ret;
पूर्ण

#अगर IS_ENABLED(CONFIG_RC_CORE)
अटल पूर्णांक anysee_rc_query(काष्ठा dvb_usb_device *d)
अणु
	u8 buf[] = अणुCMD_GET_IR_CODEपूर्ण;
	u8 ircode[2];
	पूर्णांक ret;

	/* Remote controller is basic NEC using address byte 0x08.
	   Anysee device RC query वापसs only two bytes, status and code,
	   address byte is dropped. Also it करोes not वापस any value क्रम
	   NEC RCs having address byte other than 0x08. Due to that, we
	   cannot use that device as standard NEC receiver.
	   It could be possible make hack which पढ़ोs whole code directly
	   from device memory... */

	ret = anysee_ctrl_msg(d, buf, माप(buf), ircode, माप(ircode));
	अगर (ret)
		वापस ret;

	अगर (ircode[0]) अणु
		dev_dbg(&d->udev->dev, "%s: key pressed %02x\n", __func__,
				ircode[1]);
		rc_keyकरोwn(d->rc_dev, RC_PROTO_NEC,
			   RC_SCANCODE_NEC(0x08, ircode[1]), 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक anysee_get_rc_config(काष्ठा dvb_usb_device *d, काष्ठा dvb_usb_rc *rc)
अणु
	rc->allowed_protos = RC_PROTO_BIT_NEC;
	rc->query          = anysee_rc_query;
	rc->पूर्णांकerval       = 250;  /* winकरोws driver uses 500ms */

	वापस 0;
पूर्ण
#अन्यथा
	#घोषणा anysee_get_rc_config शून्य
#पूर्ण_अगर

अटल पूर्णांक anysee_ci_पढ़ो_attribute_mem(काष्ठा dvb_ca_en50221 *ci, पूर्णांक slot,
	पूर्णांक addr)
अणु
	काष्ठा dvb_usb_device *d = ci->data;
	पूर्णांक ret;
	u8 buf[] = अणुCMD_CI, 0x02, 0x40 | addr >> 8, addr & 0xff, 0x00, 1पूर्ण;
	u8 val;

	ret = anysee_ctrl_msg(d, buf, माप(buf), &val, 1);
	अगर (ret)
		वापस ret;

	वापस val;
पूर्ण

अटल पूर्णांक anysee_ci_ग_लिखो_attribute_mem(काष्ठा dvb_ca_en50221 *ci, पूर्णांक slot,
	पूर्णांक addr, u8 val)
अणु
	काष्ठा dvb_usb_device *d = ci->data;
	u8 buf[] = अणुCMD_CI, 0x03, 0x40 | addr >> 8, addr & 0xff, 0x00, 1, valपूर्ण;

	वापस anysee_ctrl_msg(d, buf, माप(buf), शून्य, 0);
पूर्ण

अटल पूर्णांक anysee_ci_पढ़ो_cam_control(काष्ठा dvb_ca_en50221 *ci, पूर्णांक slot,
	u8 addr)
अणु
	काष्ठा dvb_usb_device *d = ci->data;
	पूर्णांक ret;
	u8 buf[] = अणुCMD_CI, 0x04, 0x40, addr, 0x00, 1पूर्ण;
	u8 val;

	ret = anysee_ctrl_msg(d, buf, माप(buf), &val, 1);
	अगर (ret)
		वापस ret;

	वापस val;
पूर्ण

अटल पूर्णांक anysee_ci_ग_लिखो_cam_control(काष्ठा dvb_ca_en50221 *ci, पूर्णांक slot,
	u8 addr, u8 val)
अणु
	काष्ठा dvb_usb_device *d = ci->data;
	u8 buf[] = अणुCMD_CI, 0x05, 0x40, addr, 0x00, 1, valपूर्ण;

	वापस anysee_ctrl_msg(d, buf, माप(buf), शून्य, 0);
पूर्ण

अटल पूर्णांक anysee_ci_slot_reset(काष्ठा dvb_ca_en50221 *ci, पूर्णांक slot)
अणु
	काष्ठा dvb_usb_device *d = ci->data;
	पूर्णांक ret;
	काष्ठा anysee_state *state = d_to_priv(d);

	state->ci_cam_पढ़ोy = jअगरfies + msecs_to_jअगरfies(1000);

	ret = anysee_wr_reg_mask(d, REG_IOA, (0 << 7), 0x80);
	अगर (ret)
		वापस ret;

	msleep(300);

	ret = anysee_wr_reg_mask(d, REG_IOA, (1 << 7), 0x80);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक anysee_ci_slot_shutकरोwn(काष्ठा dvb_ca_en50221 *ci, पूर्णांक slot)
अणु
	काष्ठा dvb_usb_device *d = ci->data;
	पूर्णांक ret;

	ret = anysee_wr_reg_mask(d, REG_IOA, (0 << 7), 0x80);
	अगर (ret)
		वापस ret;

	msleep(30);

	ret = anysee_wr_reg_mask(d, REG_IOA, (1 << 7), 0x80);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक anysee_ci_slot_ts_enable(काष्ठा dvb_ca_en50221 *ci, पूर्णांक slot)
अणु
	काष्ठा dvb_usb_device *d = ci->data;

	वापस anysee_wr_reg_mask(d, REG_IOD, (0 << 1), 0x02);
पूर्ण

अटल पूर्णांक anysee_ci_poll_slot_status(काष्ठा dvb_ca_en50221 *ci, पूर्णांक slot,
	पूर्णांक खोलो)
अणु
	काष्ठा dvb_usb_device *d = ci->data;
	काष्ठा anysee_state *state = d_to_priv(d);
	पूर्णांक ret;
	u8 पंचांगp = 0;

	ret = anysee_rd_reg_mask(d, REG_IOC, &पंचांगp, 0x40);
	अगर (ret)
		वापस ret;

	अगर (पंचांगp == 0) अणु
		ret = DVB_CA_EN50221_POLL_CAM_PRESENT;
		अगर (समय_after(jअगरfies, state->ci_cam_पढ़ोy))
			ret |= DVB_CA_EN50221_POLL_CAM_READY;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक anysee_ci_init(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा anysee_state *state = d_to_priv(d);
	पूर्णांक ret;

	state->ci.owner               = THIS_MODULE;
	state->ci.पढ़ो_attribute_mem  = anysee_ci_पढ़ो_attribute_mem;
	state->ci.ग_लिखो_attribute_mem = anysee_ci_ग_लिखो_attribute_mem;
	state->ci.पढ़ो_cam_control    = anysee_ci_पढ़ो_cam_control;
	state->ci.ग_लिखो_cam_control   = anysee_ci_ग_लिखो_cam_control;
	state->ci.slot_reset          = anysee_ci_slot_reset;
	state->ci.slot_shutकरोwn       = anysee_ci_slot_shutकरोwn;
	state->ci.slot_ts_enable      = anysee_ci_slot_ts_enable;
	state->ci.poll_slot_status    = anysee_ci_poll_slot_status;
	state->ci.data                = d;

	ret = anysee_wr_reg_mask(d, REG_IOA, (1 << 7), 0x80);
	अगर (ret)
		वापस ret;

	ret = anysee_wr_reg_mask(d, REG_IOD, (0 << 2)|(0 << 1)|(0 << 0), 0x07);
	अगर (ret)
		वापस ret;

	ret = anysee_wr_reg_mask(d, REG_IOD, (1 << 2)|(1 << 1)|(1 << 0), 0x07);
	अगर (ret)
		वापस ret;

	ret = dvb_ca_en50221_init(&d->adapter[0].dvb_adap, &state->ci, 0, 1);
	अगर (ret)
		वापस ret;

	state->ci_attached = true;

	वापस 0;
पूर्ण

अटल व्योम anysee_ci_release(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा anysee_state *state = d_to_priv(d);

	/* detach CI */
	अगर (state->ci_attached)
		dvb_ca_en50221_release(&state->ci);

	वापस;
पूर्ण

अटल पूर्णांक anysee_init(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा anysee_state *state = d_to_priv(d);
	पूर्णांक ret;

	/* There is one पूर्णांकerface with two alternate settings.
	   Alternate setting 0 is क्रम bulk transfer.
	   Alternate setting 1 is क्रम isochronous transfer.
	   We use bulk transfer (alternate setting 0). */
	ret = usb_set_पूर्णांकerface(d->udev, 0, 0);
	अगर (ret)
		वापस ret;

	/* LED light */
	ret = anysee_led_ctrl(d, 0x01, 0x03);
	अगर (ret)
		वापस ret;

	/* enable IR */
	ret = anysee_ir_ctrl(d, 1);
	अगर (ret)
		वापस ret;

	/* attach CI */
	अगर (state->has_ci) अणु
		ret = anysee_ci_init(d);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम anysee_निकास(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा anysee_state *state = d_to_priv(d);

	अगर (state->i2c_client[0])
		anysee_del_i2c_dev(d);

	वापस anysee_ci_release(d);
पूर्ण

/* DVB USB Driver stuff */
अटल काष्ठा dvb_usb_device_properties anysee_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा anysee_state),

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x81,

	.i2c_algo         = &anysee_i2c_algo,
	.पढ़ो_config      = anysee_पढ़ो_config,
	.frontend_attach  = anysee_frontend_attach,
	.tuner_attach     = anysee_tuner_attach,
	.init             = anysee_init,
	.get_rc_config    = anysee_get_rc_config,
	.frontend_ctrl    = anysee_frontend_ctrl,
	.streaming_ctrl   = anysee_streaming_ctrl,
	.निकास             = anysee_निकास,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_BULK(0x82, 8, 16 * 512),
		पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_device_id anysee_id_table[] = अणु
	अणु DVB_USB_DEVICE(USB_VID_CYPRESS, USB_PID_ANYSEE,
		&anysee_props, "Anysee", RC_MAP_ANYSEE) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_AMT, USB_PID_ANYSEE,
		&anysee_props, "Anysee", RC_MAP_ANYSEE) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, anysee_id_table);

अटल काष्ठा usb_driver anysee_usb_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = anysee_id_table,
	.probe = dvb_usbv2_probe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.resume = dvb_usbv2_resume,
	.reset_resume = dvb_usbv2_reset_resume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
पूर्ण;

module_usb_driver(anysee_usb_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Driver Anysee E30 DVB-C & DVB-T USB2.0");
MODULE_LICENSE("GPL");
