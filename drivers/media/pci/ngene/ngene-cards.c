<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ngene-cards.c: nGene PCIe bridge driver - card specअगरic info
 *
 * Copyright (C) 2005-2007 Micronas
 *
 * Copyright (C) 2008-2009 Ralph Metzler <rjkm@metzlerbros.de>
 *                         Modअगरications क्रम new nGene firmware,
 *                         support क्रम EEPROM-copying,
 *                         support क्रम new dual DVB-S2 card prototype
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>

#समावेश "ngene.h"

/* demods/tuners */
#समावेश "stv6110x.h"
#समावेश "stv090x.h"
#समावेश "lnbh24.h"
#समावेश "lgdt330x.h"
#समावेश "mt2131.h"
#समावेश "tda18271c2dd.h"
#समावेश "drxk.h"
#समावेश "drxd.h"
#समावेश "dvb-pll.h"
#समावेश "stv0367.h"
#समावेश "stv0367_priv.h"
#समावेश "tda18212.h"
#समावेश "cxd2841er.h"
#समावेश "stv0910.h"
#समावेश "stv6111.h"
#समावेश "lnbh25.h"

/****************************************************************************/
/* I2C transfer functions used क्रम demod/tuner probing***********************/
/****************************************************************************/

अटल पूर्णांक i2c_io(काष्ठा i2c_adapter *adapter, u8 adr,
		  u8 *wbuf, u32 wlen, u8 *rbuf, u32 rlen)
अणु
	काष्ठा i2c_msg msgs[2] = अणुअणु.addr = adr,  .flags = 0,
				   .buf  = wbuf, .len   = wlen पूर्ण,
				  अणु.addr = adr,  .flags = I2C_M_RD,
				   .buf  = rbuf,  .len   = rlen पूर्ण पूर्ण;
	वापस (i2c_transfer(adapter, msgs, 2) == 2) ? 0 : -1;
पूर्ण

अटल पूर्णांक i2c_ग_लिखो(काष्ठा i2c_adapter *adap, u8 adr, u8 *data, पूर्णांक len)
अणु
	काष्ठा i2c_msg msg = अणु.addr = adr, .flags = 0,
			      .buf = data, .len = lenपूर्ण;

	वापस (i2c_transfer(adap, &msg, 1) == 1) ? 0 : -1;
पूर्ण

अटल पूर्णांक i2c_ग_लिखो_reg(काष्ठा i2c_adapter *adap, u8 adr,
			 u8 reg, u8 val)
अणु
	u8 msg[2] = अणुreg, valपूर्ण;

	वापस i2c_ग_लिखो(adap, adr, msg, 2);
पूर्ण

अटल पूर्णांक i2c_पढ़ो(काष्ठा i2c_adapter *adapter, u8 adr, u8 *val)
अणु
	काष्ठा i2c_msg msgs[1] = अणुअणु.addr = adr,  .flags = I2C_M_RD,
				   .buf  = val,  .len   = 1 पूर्ण पूर्ण;
	वापस (i2c_transfer(adapter, msgs, 1) == 1) ? 0 : -1;
पूर्ण

अटल पूर्णांक i2c_पढ़ो_reg16(काष्ठा i2c_adapter *adapter, u8 adr,
			  u16 reg, u8 *val)
अणु
	u8 msg[2] = अणुreg >> 8, reg & 0xffपूर्ण;
	काष्ठा i2c_msg msgs[2] = अणुअणु.addr = adr, .flags = 0,
				   .buf  = msg, .len   = 2पूर्ण,
				  अणु.addr = adr, .flags = I2C_M_RD,
				   .buf  = val, .len   = 1पूर्ण पूर्ण;
	वापस (i2c_transfer(adapter, msgs, 2) == 2) ? 0 : -1;
पूर्ण

अटल पूर्णांक i2c_पढ़ो_regs(काष्ठा i2c_adapter *adapter,
			 u8 adr, u8 reg, u8 *val, u8 len)
अणु
	काष्ठा i2c_msg msgs[2] = अणुअणु.addr = adr,  .flags = 0,
				   .buf  = &reg, .len   = 1पूर्ण,
				  अणु.addr = adr,  .flags = I2C_M_RD,
				   .buf  = val,  .len   = lenपूर्ण पूर्ण;

	वापस (i2c_transfer(adapter, msgs, 2) == 2) ? 0 : -1;
पूर्ण

अटल पूर्णांक i2c_पढ़ो_reg(काष्ठा i2c_adapter *adapter, u8 adr, u8 reg, u8 *val)
अणु
	वापस i2c_पढ़ो_regs(adapter, adr, reg, val, 1);
पूर्ण

/****************************************************************************/
/* Demod/tuner attachment ***************************************************/
/****************************************************************************/

अटल काष्ठा i2c_adapter *i2c_adapter_from_chan(काष्ठा ngene_channel *chan)
अणु
	/* tuner 1+2: i2c adapter #0, tuner 3+4: i2c adapter #1 */
	अगर (chan->number < 2)
		वापस &chan->dev->channel[0].i2c_adapter;

	वापस &chan->dev->channel[1].i2c_adapter;
पूर्ण

अटल पूर्णांक tuner_attach_stv6110(काष्ठा ngene_channel *chan)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	काष्ठा i2c_adapter *i2c = i2c_adapter_from_chan(chan);
	काष्ठा stv090x_config *feconf = (काष्ठा stv090x_config *)
		chan->dev->card_info->fe_config[chan->number];
	काष्ठा stv6110x_config *tunerconf = (काष्ठा stv6110x_config *)
		chan->dev->card_info->tuner_config[chan->number];
	स्थिर काष्ठा stv6110x_devctl *ctl;

	ctl = dvb_attach(stv6110x_attach, chan->fe, tunerconf, i2c);
	अगर (ctl == शून्य) अणु
		dev_err(pdev, "No STV6110X found!\n");
		वापस -ENODEV;
	पूर्ण

	feconf->tuner_init          = ctl->tuner_init;
	feconf->tuner_sleep         = ctl->tuner_sleep;
	feconf->tuner_set_mode      = ctl->tuner_set_mode;
	feconf->tuner_set_frequency = ctl->tuner_set_frequency;
	feconf->tuner_get_frequency = ctl->tuner_get_frequency;
	feconf->tuner_set_bandwidth = ctl->tuner_set_bandwidth;
	feconf->tuner_get_bandwidth = ctl->tuner_get_bandwidth;
	feconf->tuner_set_bbgain    = ctl->tuner_set_bbgain;
	feconf->tuner_get_bbgain    = ctl->tuner_get_bbgain;
	feconf->tuner_set_refclk    = ctl->tuner_set_refclk;
	feconf->tuner_get_status    = ctl->tuner_get_status;

	वापस 0;
पूर्ण

अटल पूर्णांक tuner_attach_stv6111(काष्ठा ngene_channel *chan)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	काष्ठा i2c_adapter *i2c = i2c_adapter_from_chan(chan);
	काष्ठा dvb_frontend *fe;
	u8 adr = 4 + ((chan->number & 1) ? 0x63 : 0x60);

	fe = dvb_attach(stv6111_attach, chan->fe, i2c, adr);
	अगर (!fe) अणु
		fe = dvb_attach(stv6111_attach, chan->fe, i2c, adr & ~4);
		अगर (!fe) अणु
			dev_err(pdev, "stv6111_attach() failed!\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक drxk_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा ngene_channel *chan = fe->sec_priv;
	पूर्णांक status;

	अगर (enable) अणु
		करोwn(&chan->dev->pll_mutex);
		status = chan->gate_ctrl(fe, 1);
	पूर्ण अन्यथा अणु
		status = chan->gate_ctrl(fe, 0);
		up(&chan->dev->pll_mutex);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक tuner_attach_tda18271(काष्ठा ngene_channel *chan)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	काष्ठा i2c_adapter *i2c = i2c_adapter_from_chan(chan);
	काष्ठा dvb_frontend *fe;

	अगर (chan->fe->ops.i2c_gate_ctrl)
		chan->fe->ops.i2c_gate_ctrl(chan->fe, 1);
	fe = dvb_attach(tda18271c2dd_attach, chan->fe, i2c, 0x60);
	अगर (chan->fe->ops.i2c_gate_ctrl)
		chan->fe->ops.i2c_gate_ctrl(chan->fe, 0);
	अगर (!fe) अणु
		dev_err(pdev, "No TDA18271 found!\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tuner_tda18212_ping(काष्ठा ngene_channel *chan,
			       काष्ठा i2c_adapter *i2c,
			       अचिन्हित लघु adr)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	u8 tda_id[2];
	u8 subaddr = 0x00;

	dev_dbg(pdev, "stv0367-tda18212 tuner ping\n");
	अगर (chan->fe->ops.i2c_gate_ctrl)
		chan->fe->ops.i2c_gate_ctrl(chan->fe, 1);

	अगर (i2c_पढ़ो_regs(i2c, adr, subaddr, tda_id, माप(tda_id)) < 0)
		dev_dbg(pdev, "tda18212 ping 1 fail\n");
	अगर (i2c_पढ़ो_regs(i2c, adr, subaddr, tda_id, माप(tda_id)) < 0)
		dev_warn(pdev, "tda18212 ping failed, expect problems\n");

	अगर (chan->fe->ops.i2c_gate_ctrl)
		chan->fe->ops.i2c_gate_ctrl(chan->fe, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक tuner_attach_tda18212(काष्ठा ngene_channel *chan, u32 dmdtype)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	काष्ठा i2c_adapter *i2c = i2c_adapter_from_chan(chan);
	काष्ठा i2c_client *client;
	काष्ठा tda18212_config config = अणु
		.fe = chan->fe,
		.अगर_dvbt_6 = 3550,
		.अगर_dvbt_7 = 3700,
		.अगर_dvbt_8 = 4150,
		.अगर_dvbt2_6 = 3250,
		.अगर_dvbt2_7 = 4000,
		.अगर_dvbt2_8 = 4000,
		.अगर_dvbc = 5000,
	पूर्ण;
	u8 addr = (chan->number & 1) ? 0x63 : 0x60;

	/*
	 * due to a hardware quirk with the I2C gate on the stv0367+tda18212
	 * combo, the tda18212 must be probed by पढ़ोing it's id _twice_ when
	 * cold started, or it very likely will fail.
	 */
	अगर (dmdtype == DEMOD_TYPE_STV0367)
		tuner_tda18212_ping(chan, i2c, addr);

	/* perक्रमm tuner probe/init/attach */
	client = dvb_module_probe("tda18212", शून्य, i2c, addr, &config);
	अगर (!client)
		जाओ err;

	chan->i2c_client[0] = client;
	chan->i2c_client_fe = 1;

	वापस 0;
err:
	dev_err(pdev, "TDA18212 tuner not found. Device is not fully operational.\n");
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक tuner_attach_probe(काष्ठा ngene_channel *chan)
अणु
	चयन (chan->demod_type) अणु
	हाल DEMOD_TYPE_STV090X:
		वापस tuner_attach_stv6110(chan);
	हाल DEMOD_TYPE_DRXK:
		वापस tuner_attach_tda18271(chan);
	हाल DEMOD_TYPE_STV0367:
	हाल DEMOD_TYPE_SONY_CT2:
	हाल DEMOD_TYPE_SONY_ISDBT:
	हाल DEMOD_TYPE_SONY_C2T2:
	हाल DEMOD_TYPE_SONY_C2T2I:
		वापस tuner_attach_tda18212(chan, chan->demod_type);
	हाल DEMOD_TYPE_STV0910:
		वापस tuner_attach_stv6111(chan);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक demod_attach_stv0900(काष्ठा ngene_channel *chan)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	काष्ठा i2c_adapter *i2c = i2c_adapter_from_chan(chan);
	काष्ठा stv090x_config *feconf = (काष्ठा stv090x_config *)
		chan->dev->card_info->fe_config[chan->number];

	chan->fe = dvb_attach(stv090x_attach, feconf, i2c,
			(chan->number & 1) == 0 ? STV090x_DEMODULATOR_0
						: STV090x_DEMODULATOR_1);
	अगर (chan->fe == शून्य) अणु
		dev_err(pdev, "No STV0900 found!\n");
		वापस -ENODEV;
	पूर्ण

	/* store channel info */
	अगर (feconf->tuner_i2c_lock)
		chan->fe->analog_demod_priv = chan;

	अगर (!dvb_attach(lnbh24_attach, chan->fe, i2c, 0,
			0, chan->dev->card_info->lnb[chan->number])) अणु
		dev_err(pdev, "No LNBH24 found!\n");
		dvb_frontend_detach(chan->fe);
		chan->fe = शून्य;
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा stv0910_cfg stv0910_p = अणु
	.adr      = 0x68,
	.parallel = 1,
	.rptlvl   = 4,
	.clk      = 30000000,
	.tsspeed  = 0x28,
पूर्ण;

अटल काष्ठा lnbh25_config lnbh25_cfg = अणु
	.i2c_address = 0x0c << 1,
	.data2_config = LNBH25_TEN
पूर्ण;

अटल पूर्णांक demod_attach_stv0910(काष्ठा ngene_channel *chan,
				काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	काष्ठा stv0910_cfg cfg = stv0910_p;
	काष्ठा lnbh25_config lnbcfg = lnbh25_cfg;

	chan->fe = dvb_attach(stv0910_attach, i2c, &cfg, (chan->number & 1));
	अगर (!chan->fe) अणु
		cfg.adr = 0x6c;
		chan->fe = dvb_attach(stv0910_attach, i2c,
				      &cfg, (chan->number & 1));
	पूर्ण
	अगर (!chan->fe) अणु
		dev_err(pdev, "stv0910_attach() failed!\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * attach lnbh25 - leftshअगरt by one as the lnbh25 driver expects 8bit
	 * i2c addresses
	 */
	lnbcfg.i2c_address = (((chan->number & 1) ? 0x0d : 0x0c) << 1);
	अगर (!dvb_attach(lnbh25_attach, chan->fe, &lnbcfg, i2c)) अणु
		lnbcfg.i2c_address = (((chan->number & 1) ? 0x09 : 0x08) << 1);
		अगर (!dvb_attach(lnbh25_attach, chan->fe, &lnbcfg, i2c)) अणु
			dev_err(pdev, "lnbh25_attach() failed!\n");
			dvb_frontend_detach(chan->fe);
			chan->fe = शून्य;
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा stv0367_config ddb_stv0367_config[] = अणु
	अणु
		.demod_address = 0x1f,
		.xtal = 27000000,
		.अगर_khz = 0,
		.अगर_iq_mode = FE_TER_NORMAL_IF_TUNER,
		.ts_mode = STV0367_SERIAL_PUNCT_CLOCK,
		.clk_pol = STV0367_CLOCKPOLARITY_DEFAULT,
	पूर्ण, अणु
		.demod_address = 0x1e,
		.xtal = 27000000,
		.अगर_khz = 0,
		.अगर_iq_mode = FE_TER_NORMAL_IF_TUNER,
		.ts_mode = STV0367_SERIAL_PUNCT_CLOCK,
		.clk_pol = STV0367_CLOCKPOLARITY_DEFAULT,
	पूर्ण,
पूर्ण;

अटल पूर्णांक demod_attach_stv0367(काष्ठा ngene_channel *chan,
				काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;

	chan->fe = dvb_attach(stv0367ddb_attach,
			      &ddb_stv0367_config[(chan->number & 1)], i2c);

	अगर (!chan->fe) अणु
		dev_err(pdev, "stv0367ddb_attach() failed!\n");
		वापस -ENODEV;
	पूर्ण

	chan->fe->sec_priv = chan;
	chan->gate_ctrl = chan->fe->ops.i2c_gate_ctrl;
	chan->fe->ops.i2c_gate_ctrl = drxk_gate_ctrl;
	वापस 0;
पूर्ण

अटल पूर्णांक demod_attach_cxd28xx(काष्ठा ngene_channel *chan,
				काष्ठा i2c_adapter *i2c, पूर्णांक osc24)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	काष्ठा cxd2841er_config cfg;

	/* the cxd2841er driver expects 8bit/shअगरted I2C addresses */
	cfg.i2c_addr = ((chan->number & 1) ? 0x6d : 0x6c) << 1;

	cfg.xtal = osc24 ? SONY_XTAL_24000 : SONY_XTAL_20500;
	cfg.flags = CXD2841ER_AUTO_IFHZ | CXD2841ER_EARLY_TUNE |
		CXD2841ER_NO_WAIT_LOCK | CXD2841ER_NO_AGCNEG |
		CXD2841ER_TSBITS | CXD2841ER_TS_SERIAL;

	/* attach frontend */
	chan->fe = dvb_attach(cxd2841er_attach_t_c, &cfg, i2c);

	अगर (!chan->fe) अणु
		dev_err(pdev, "CXD28XX attach failed!\n");
		वापस -ENODEV;
	पूर्ण

	chan->fe->sec_priv = chan;
	chan->gate_ctrl = chan->fe->ops.i2c_gate_ctrl;
	chan->fe->ops.i2c_gate_ctrl = drxk_gate_ctrl;
	वापस 0;
पूर्ण

अटल व्योम cineS2_tuner_i2c_lock(काष्ठा dvb_frontend *fe, पूर्णांक lock)
अणु
	काष्ठा ngene_channel *chan = fe->analog_demod_priv;

	अगर (lock)
		करोwn(&chan->dev->pll_mutex);
	अन्यथा
		up(&chan->dev->pll_mutex);
पूर्ण

अटल पूर्णांक port_has_stv0900(काष्ठा i2c_adapter *i2c, पूर्णांक port)
अणु
	u8 val;
	अगर (i2c_पढ़ो_reg16(i2c, 0x68+port/2, 0xf100, &val) < 0)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक port_has_drxk(काष्ठा i2c_adapter *i2c, पूर्णांक port)
अणु
	u8 val;

	अगर (i2c_पढ़ो(i2c, 0x29+port, &val) < 0)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक port_has_stv0367(काष्ठा i2c_adapter *i2c)
अणु
	u8 val;

	अगर (i2c_पढ़ो_reg16(i2c, 0x1e, 0xf000, &val) < 0)
		वापस 0;
	अगर (val != 0x60)
		वापस 0;
	अगर (i2c_पढ़ो_reg16(i2c, 0x1f, 0xf000, &val) < 0)
		वापस 0;
	अगर (val != 0x60)
		वापस 0;
	वापस 1;
पूर्ण

पूर्णांक ngene_port_has_cxd2099(काष्ठा i2c_adapter *i2c, u8 *type)
अणु
	u8 val;
	u8 probe[4] = अणु 0xe0, 0x00, 0x00, 0x00 पूर्ण, data[4];
	काष्ठा i2c_msg msgs[2] = अणुअणु .addr = 0x40,  .flags = 0,
				    .buf  = probe, .len   = 4 पूर्ण,
				  अणु .addr = 0x40,  .flags = I2C_M_RD,
				    .buf  = data,  .len   = 4 पूर्ण पूर्ण;
	val = i2c_transfer(i2c, msgs, 2);
	अगर (val != 2)
		वापस 0;

	अगर (data[0] == 0x02 && data[1] == 0x2b && data[3] == 0x43)
		*type = 2;
	अन्यथा
		*type = 1;
	वापस 1;
पूर्ण

अटल पूर्णांक demod_attach_drxk(काष्ठा ngene_channel *chan,
			     काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	काष्ठा drxk_config config;

	स_रखो(&config, 0, माप(config));
	config.microcode_name = "drxk_a3.mc";
	config.qam_demod_parameter_count = 4;
	config.adr = 0x29 + (chan->number ^ 2);

	chan->fe = dvb_attach(drxk_attach, &config, i2c);
	अगर (!chan->fe) अणु
		dev_err(pdev, "No DRXK found!\n");
		वापस -ENODEV;
	पूर्ण
	chan->fe->sec_priv = chan;
	chan->gate_ctrl = chan->fe->ops.i2c_gate_ctrl;
	chan->fe->ops.i2c_gate_ctrl = drxk_gate_ctrl;
	वापस 0;
पूर्ण

/****************************************************************************/
/* XO2 related lists and functions ******************************************/
/****************************************************************************/

अटल अक्षर *xo2names[] = अणु
	"DUAL DVB-S2",
	"DUAL DVB-C/T/T2",
	"DUAL DVB-ISDBT",
	"DUAL DVB-C/C2/T/T2",
	"DUAL ATSC",
	"DUAL DVB-C/C2/T/T2/I",
पूर्ण;

अटल पूर्णांक init_xo2(काष्ठा ngene_channel *chan, काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	u8 addr = 0x10;
	u8 val, data[2];
	पूर्णांक res;

	res = i2c_पढ़ो_regs(i2c, addr, 0x04, data, 2);
	अगर (res < 0)
		वापस res;

	अगर (data[0] != 0x01)  अणु
		dev_info(pdev, "Invalid XO2 on channel %d\n", chan->number);
		वापस -1;
	पूर्ण

	i2c_पढ़ो_reg(i2c, addr, 0x08, &val);
	अगर (val != 0) अणु
		i2c_ग_लिखो_reg(i2c, addr, 0x08, 0x00);
		msleep(100);
	पूर्ण
	/* Enable tuner घातer, disable pll, reset demods */
	i2c_ग_लिखो_reg(i2c, addr, 0x08, 0x04);
	usleep_range(2000, 3000);
	/* Release demod resets */
	i2c_ग_लिखो_reg(i2c, addr, 0x08, 0x07);

	/*
	 * speed: 0=55,1=75,2=90,3=104 MBit/s
	 * Note: The ngene hardware must be run at 75 MBit/s compared
	 * to more modern ddbridge hardware which runs at 90 MBit/s,
	 * अन्यथा there will be issues with the data transport and non-
	 * working secondary/slave demods/tuners.
	 */
	i2c_ग_लिखो_reg(i2c, addr, 0x09, 1);

	i2c_ग_लिखो_reg(i2c, addr, 0x0a, 0x01);
	i2c_ग_लिखो_reg(i2c, addr, 0x0b, 0x01);

	usleep_range(2000, 3000);
	/* Start XO2 PLL */
	i2c_ग_लिखो_reg(i2c, addr, 0x08, 0x87);

	वापस 0;
पूर्ण

अटल पूर्णांक port_has_xo2(काष्ठा i2c_adapter *i2c, u8 *type, u8 *id)
अणु
	u8 probe[1] = अणु 0x00 पूर्ण, data[4];
	u8 addr = 0x10;

	*type = NGENE_XO2_TYPE_NONE;

	अगर (i2c_io(i2c, addr, probe, 1, data, 4))
		वापस 0;
	अगर (data[0] == 'D' && data[1] == 'F') अणु
		*id = data[2];
		*type = NGENE_XO2_TYPE_DUOFLEX;
		वापस 1;
	पूर्ण
	अगर (data[0] == 'C' && data[1] == 'I') अणु
		*id = data[2];
		*type = NGENE_XO2_TYPE_CI;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/****************************************************************************/
/* Probing and port/channel handling ****************************************/
/****************************************************************************/

अटल पूर्णांक cineS2_probe(काष्ठा ngene_channel *chan)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	काष्ठा i2c_adapter *i2c = i2c_adapter_from_chan(chan);
	काष्ठा stv090x_config *fe_conf;
	u8 buf[3];
	u8 xo2_type, xo2_id, xo2_demodtype;
	u8 sony_osc24 = 0;
	काष्ठा i2c_msg i2c_msg = अणु .flags = 0, .buf = buf पूर्ण;
	पूर्णांक rc;

	अगर (port_has_xo2(i2c, &xo2_type, &xo2_id)) अणु
		xo2_id >>= 2;
		dev_dbg(pdev, "XO2 on channel %d (type %d, id %d)\n",
			chan->number, xo2_type, xo2_id);

		चयन (xo2_type) अणु
		हाल NGENE_XO2_TYPE_DUOFLEX:
			अगर (chan->number & 1)
				dev_dbg(pdev,
					"skipping XO2 init on odd channel %d",
					chan->number);
			अन्यथा
				init_xo2(chan, i2c);

			xo2_demodtype = DEMOD_TYPE_XO2 + xo2_id;

			चयन (xo2_demodtype) अणु
			हाल DEMOD_TYPE_SONY_CT2:
			हाल DEMOD_TYPE_SONY_ISDBT:
			हाल DEMOD_TYPE_SONY_C2T2:
			हाल DEMOD_TYPE_SONY_C2T2I:
				dev_info(pdev, "%s (XO2) on channel %d\n",
					 xo2names[xo2_id], chan->number);
				chan->demod_type = xo2_demodtype;
				अगर (xo2_demodtype == DEMOD_TYPE_SONY_C2T2I)
					sony_osc24 = 1;

				demod_attach_cxd28xx(chan, i2c, sony_osc24);
				अवरोध;
			हाल DEMOD_TYPE_STV0910:
				dev_info(pdev, "%s (XO2) on channel %d\n",
					 xo2names[xo2_id], chan->number);
				chan->demod_type = xo2_demodtype;
				demod_attach_stv0910(chan, i2c);
				अवरोध;
			शेष:
				dev_warn(pdev,
					 "Unsupported XO2 module on channel %d\n",
					 chan->number);
				वापस -ENODEV;
			पूर्ण
			अवरोध;
		हाल NGENE_XO2_TYPE_CI:
			dev_info(pdev, "DuoFlex CI modules not supported\n");
			वापस -ENODEV;
		शेष:
			dev_info(pdev, "Unsupported XO2 module type\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अगर (port_has_stv0900(i2c, chan->number)) अणु
		chan->demod_type = DEMOD_TYPE_STV090X;
		fe_conf = chan->dev->card_info->fe_config[chan->number];
		/* demod found, attach it */
		rc = demod_attach_stv0900(chan);
		अगर (rc < 0 || chan->number < 2)
			वापस rc;

		/* demod #2: reprogram outमाला_दो DPN1 & DPN2 */
		i2c_msg.addr = fe_conf->address;
		i2c_msg.len = 3;
		buf[0] = 0xf1;
		चयन (chan->number) अणु
		हाल 2:
			buf[1] = 0x5c;
			buf[2] = 0xc2;
			अवरोध;
		हाल 3:
			buf[1] = 0x61;
			buf[2] = 0xcc;
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
		rc = i2c_transfer(i2c, &i2c_msg, 1);
		अगर (rc != 1) अणु
			dev_err(pdev, "Could not setup DPNx\n");
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अगर (port_has_drxk(i2c, chan->number^2)) अणु
		chan->demod_type = DEMOD_TYPE_DRXK;
		demod_attach_drxk(chan, i2c);
	पूर्ण अन्यथा अगर (port_has_stv0367(i2c)) अणु
		chan->demod_type = DEMOD_TYPE_STV0367;
		dev_info(pdev, "STV0367 on channel %d\n", chan->number);
		demod_attach_stv0367(chan, i2c);
	पूर्ण अन्यथा अणु
		dev_info(pdev, "No demod found on chan %d\n", chan->number);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण


अटल काष्ठा lgdt330x_config aver_m780 = अणु
	.demod_chip    = LGDT3303,
	.serial_mpeg   = 0x00, /* PARALLEL */
	.घड़ी_polarity_flip = 1,
पूर्ण;

अटल काष्ठा mt2131_config m780_tunerconfig = अणु
	0xc0 >> 1
पूर्ण;

/* A single func to attach the demo and tuner, rather than
 * use two sep funcs like the current design mandates.
 */
अटल पूर्णांक demod_attach_lg330x(काष्ठा ngene_channel *chan)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;

	chan->fe = dvb_attach(lgdt330x_attach, &aver_m780,
			      0xb2 >> 1, &chan->i2c_adapter);
	अगर (chan->fe == शून्य) अणु
		dev_err(pdev, "No LGDT330x found!\n");
		वापस -ENODEV;
	पूर्ण

	dvb_attach(mt2131_attach, chan->fe, &chan->i2c_adapter,
		   &m780_tunerconfig, 0);

	वापस (chan->fe) ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक demod_attach_drxd(काष्ठा ngene_channel *chan)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	काष्ठा drxd_config *feconf;

	feconf = chan->dev->card_info->fe_config[chan->number];

	chan->fe = dvb_attach(drxd_attach, feconf, chan,
			&chan->i2c_adapter, &chan->dev->pci_dev->dev);
	अगर (!chan->fe) अणु
		dev_err(pdev, "No DRXD found!\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tuner_attach_dtt7520x(काष्ठा ngene_channel *chan)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	काष्ठा drxd_config *feconf;

	feconf = chan->dev->card_info->fe_config[chan->number];

	अगर (!dvb_attach(dvb_pll_attach, chan->fe, feconf->pll_address,
			&chan->i2c_adapter,
			feconf->pll_type)) अणु
		dev_err(pdev, "No pll(%d) found!\n", feconf->pll_type);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

/****************************************************************************/
/* EEPROM TAGS **************************************************************/
/****************************************************************************/

#घोषणा MICNG_EE_START      0x0100
#घोषणा MICNG_EE_END        0x0FF0

#घोषणा MICNG_EETAG_END0    0x0000
#घोषणा MICNG_EETAG_END1    0xFFFF

/* 0x0001 - 0x000F reserved क्रम housekeeping */
/* 0xFFFF - 0xFFFE reserved क्रम housekeeping */

/* Micronas asचिन्हित tags
   EEProm tags क्रम hardware support */

#घोषणा MICNG_EETAG_DRXD1_OSCDEVIATION  0x1000  /* 2 Bytes data */
#घोषणा MICNG_EETAG_DRXD2_OSCDEVIATION  0x1001  /* 2 Bytes data */

#घोषणा MICNG_EETAG_MT2060_1_1STIF      0x1100  /* 2 Bytes data */
#घोषणा MICNG_EETAG_MT2060_2_1STIF      0x1101  /* 2 Bytes data */

/* Tag range क्रम OEMs */

#घोषणा MICNG_EETAG_OEM_FIRST  0xC000
#घोषणा MICNG_EETAG_OEM_LAST   0xFFEF

अटल पूर्णांक i2c_ग_लिखो_eeprom(काष्ठा i2c_adapter *adapter,
			    u8 adr, u16 reg, u8 data)
अणु
	काष्ठा device *pdev = adapter->dev.parent;
	u8 m[3] = अणु(reg >> 8), (reg & 0xff), dataपूर्ण;
	काष्ठा i2c_msg msg = अणु.addr = adr, .flags = 0, .buf = m,
			      .len = माप(m)पूर्ण;

	अगर (i2c_transfer(adapter, &msg, 1) != 1) अणु
		dev_err(pdev, "Error writing EEPROM!\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_पढ़ो_eeprom(काष्ठा i2c_adapter *adapter,
			   u8 adr, u16 reg, u8 *data, पूर्णांक len)
अणु
	काष्ठा device *pdev = adapter->dev.parent;
	u8 msg[2] = अणु(reg >> 8), (reg & 0xff)पूर्ण;
	काष्ठा i2c_msg msgs[2] = अणुअणु.addr = adr, .flags = 0,
				   .buf = msg, .len = 2 पूर्ण,
				  अणु.addr = adr, .flags = I2C_M_RD,
				   .buf = data, .len = lenपूर्ण पूर्ण;

	अगर (i2c_transfer(adapter, msgs, 2) != 2) अणु
		dev_err(pdev, "Error reading EEPROM\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ReadEEProm(काष्ठा i2c_adapter *adapter,
		      u16 Tag, u32 MaxLen, u8 *data, u32 *pLength)
अणु
	काष्ठा device *pdev = adapter->dev.parent;
	पूर्णांक status = 0;
	u16 Addr = MICNG_EE_START, Length, tag = 0;
	u8  EETag[3];

	जबतक (Addr + माप(u16) + 1 < MICNG_EE_END) अणु
		अगर (i2c_पढ़ो_eeprom(adapter, 0x50, Addr, EETag, माप(EETag)))
			वापस -1;
		tag = (EETag[0] << 8) | EETag[1];
		अगर (tag == MICNG_EETAG_END0 || tag == MICNG_EETAG_END1)
			वापस -1;
		अगर (tag == Tag)
			अवरोध;
		Addr += माप(u16) + 1 + EETag[2];
	पूर्ण
	अगर (Addr + माप(u16) + 1 + EETag[2] > MICNG_EE_END) अणु
		dev_err(pdev, "Reached EOEE @ Tag = %04x Length = %3d\n",
			tag, EETag[2]);
		वापस -1;
	पूर्ण
	Length = EETag[2];
	अगर (Length > MaxLen)
		Length = (u16) MaxLen;
	अगर (Length > 0) अणु
		Addr += माप(u16) + 1;
		status = i2c_पढ़ो_eeprom(adapter, 0x50, Addr, data, Length);
		अगर (!status) अणु
			*pLength = EETag[2];
#अगर 0
			अगर (Length < EETag[2])
				status = STATUS_BUFFER_OVERFLOW;
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक WriteEEProm(काष्ठा i2c_adapter *adapter,
		       u16 Tag, u32 Length, u8 *data)
अणु
	काष्ठा device *pdev = adapter->dev.parent;
	पूर्णांक status = 0;
	u16 Addr = MICNG_EE_START;
	u8 EETag[3];
	u16 tag = 0;
	पूर्णांक retry, i;

	जबतक (Addr + माप(u16) + 1 < MICNG_EE_END) अणु
		अगर (i2c_पढ़ो_eeprom(adapter, 0x50, Addr, EETag, माप(EETag)))
			वापस -1;
		tag = (EETag[0] << 8) | EETag[1];
		अगर (tag == MICNG_EETAG_END0 || tag == MICNG_EETAG_END1)
			वापस -1;
		अगर (tag == Tag)
			अवरोध;
		Addr += माप(u16) + 1 + EETag[2];
	पूर्ण
	अगर (Addr + माप(u16) + 1 + EETag[2] > MICNG_EE_END) अणु
		dev_err(pdev, "Reached EOEE @ Tag = %04x Length = %3d\n",
			tag, EETag[2]);
		वापस -1;
	पूर्ण

	अगर (Length > EETag[2])
		वापस -EINVAL;
	/* Note: We ग_लिखो the data one byte at a समय to aव्योम
	   issues with page sizes. (which are dअगरferent क्रम
	   each manufacture and eeprom size)
	 */
	Addr += माप(u16) + 1;
	क्रम (i = 0; i < Length; i++, Addr++) अणु
		status = i2c_ग_लिखो_eeprom(adapter, 0x50, Addr, data[i]);

		अगर (status)
			अवरोध;

		/* Poll क्रम finishing ग_लिखो cycle */
		retry = 10;
		जबतक (retry) अणु
			u8 Tmp;

			msleep(50);
			status = i2c_पढ़ो_eeprom(adapter, 0x50, Addr, &Tmp, 1);
			अगर (status)
				अवरोध;
			अगर (Tmp != data[i])
				dev_err(pdev, "eeprom write error\n");
			retry -= 1;
		पूर्ण
		अगर (status) अणु
			dev_err(pdev, "Timeout polling eeprom\n");
			अवरोध;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक eeprom_पढ़ो_uलघु(काष्ठा i2c_adapter *adapter, u16 tag, u16 *data)
अणु
	पूर्णांक stat;
	u8 buf[2];
	u32 len = 0;

	stat = ReadEEProm(adapter, tag, 2, buf, &len);
	अगर (stat)
		वापस stat;
	अगर (len != 2)
		वापस -EINVAL;

	*data = (buf[0] << 8) | buf[1];
	वापस 0;
पूर्ण

अटल पूर्णांक eeprom_ग_लिखो_uलघु(काष्ठा i2c_adapter *adapter, u16 tag, u16 data)
अणु
	u8 buf[2];

	buf[0] = data >> 8;
	buf[1] = data & 0xff;
	वापस WriteEEProm(adapter, tag, 2, buf);
पूर्ण

अटल s16 osc_deviation(व्योम *priv, s16 deviation, पूर्णांक flag)
अणु
	काष्ठा ngene_channel *chan = priv;
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	काष्ठा i2c_adapter *adap = &chan->i2c_adapter;
	u16 data = 0;

	अगर (flag) अणु
		data = (u16) deviation;
		dev_info(pdev, "write deviation %d\n",
			 deviation);
		eeprom_ग_लिखो_uलघु(adap, 0x1000 + chan->number, data);
	पूर्ण अन्यथा अणु
		अगर (eeprom_पढ़ो_uलघु(adap, 0x1000 + chan->number, &data))
			data = 0;
		dev_info(pdev, "read deviation %d\n",
			 (s16)data);
	पूर्ण

	वापस (s16) data;
पूर्ण

/****************************************************************************/
/* Switch control (I2C gates, etc.) *****************************************/
/****************************************************************************/


अटल काष्ठा stv090x_config fe_cineS2 = अणु
	.device         = STV0900,
	.demod_mode     = STV090x_DUAL,
	.clk_mode       = STV090x_CLK_EXT,

	.xtal           = 27000000,
	.address        = 0x68,

	.ts1_mode       = STV090x_TSMODE_SERIAL_PUNCTURED,
	.ts2_mode       = STV090x_TSMODE_SERIAL_PUNCTURED,

	.repeater_level = STV090x_RPTLEVEL_16,

	.adc1_range	= STV090x_ADC_1Vpp,
	.adc2_range	= STV090x_ADC_1Vpp,

	.diseqc_envelope_mode = true,

	.tuner_i2c_lock = cineS2_tuner_i2c_lock,
पूर्ण;

अटल काष्ठा stv090x_config fe_cineS2_2 = अणु
	.device         = STV0900,
	.demod_mode     = STV090x_DUAL,
	.clk_mode       = STV090x_CLK_EXT,

	.xtal           = 27000000,
	.address        = 0x69,

	.ts1_mode       = STV090x_TSMODE_SERIAL_PUNCTURED,
	.ts2_mode       = STV090x_TSMODE_SERIAL_PUNCTURED,

	.repeater_level = STV090x_RPTLEVEL_16,

	.adc1_range	= STV090x_ADC_1Vpp,
	.adc2_range	= STV090x_ADC_1Vpp,

	.diseqc_envelope_mode = true,

	.tuner_i2c_lock = cineS2_tuner_i2c_lock,
पूर्ण;

अटल काष्ठा stv6110x_config tuner_cineS2_0 = अणु
	.addr	= 0x60,
	.refclk	= 27000000,
	.clk_भाग = 1,
पूर्ण;

अटल काष्ठा stv6110x_config tuner_cineS2_1 = अणु
	.addr	= 0x63,
	.refclk	= 27000000,
	.clk_भाग = 1,
पूर्ण;

अटल स्थिर काष्ठा ngene_info ngene_info_cineS2 = अणु
	.type		= NGENE_SIDEWINDER,
	.name		= "Linux4Media cineS2 DVB-S2 Twin Tuner",
	.io_type	= अणुNGENE_IO_TSIN, NGENE_IO_TSINपूर्ण,
	.demod_attach	= अणुdemod_attach_stv0900, demod_attach_stv0900पूर्ण,
	.tuner_attach	= अणुtuner_attach_stv6110, tuner_attach_stv6110पूर्ण,
	.fe_config	= अणु&fe_cineS2, &fe_cineS2पूर्ण,
	.tuner_config	= अणु&tuner_cineS2_0, &tuner_cineS2_1पूर्ण,
	.lnb		= अणु0x0b, 0x08पूर्ण,
	.tsf		= अणु3, 3पूर्ण,
	.fw_version	= 18,
	.msi_supported	= true,
पूर्ण;

अटल स्थिर काष्ठा ngene_info ngene_info_satixS2 = अणु
	.type		= NGENE_SIDEWINDER,
	.name		= "Mystique SaTiX-S2 Dual",
	.io_type	= अणुNGENE_IO_TSIN, NGENE_IO_TSINपूर्ण,
	.demod_attach	= अणुdemod_attach_stv0900, demod_attach_stv0900पूर्ण,
	.tuner_attach	= अणुtuner_attach_stv6110, tuner_attach_stv6110पूर्ण,
	.fe_config	= अणु&fe_cineS2, &fe_cineS2पूर्ण,
	.tuner_config	= अणु&tuner_cineS2_0, &tuner_cineS2_1पूर्ण,
	.lnb		= अणु0x0b, 0x08पूर्ण,
	.tsf		= अणु3, 3पूर्ण,
	.fw_version	= 18,
	.msi_supported	= true,
पूर्ण;

अटल स्थिर काष्ठा ngene_info ngene_info_satixS2v2 = अणु
	.type		= NGENE_SIDEWINDER,
	.name		= "Mystique SaTiX-S2 Dual (v2)",
	.io_type	= अणुNGENE_IO_TSIN, NGENE_IO_TSIN, NGENE_IO_TSIN, NGENE_IO_TSIN,
			   NGENE_IO_TSOUTपूर्ण,
	.demod_attach	= अणुdemod_attach_stv0900, demod_attach_stv0900, cineS2_probe, cineS2_probeपूर्ण,
	.tuner_attach	= अणुtuner_attach_stv6110, tuner_attach_stv6110, tuner_attach_probe, tuner_attach_probeपूर्ण,
	.fe_config	= अणु&fe_cineS2, &fe_cineS2, &fe_cineS2_2, &fe_cineS2_2पूर्ण,
	.tuner_config	= अणु&tuner_cineS2_0, &tuner_cineS2_1, &tuner_cineS2_0, &tuner_cineS2_1पूर्ण,
	.lnb		= अणु0x0a, 0x08, 0x0b, 0x09पूर्ण,
	.tsf		= अणु3, 3पूर्ण,
	.fw_version	= 18,
	.msi_supported	= true,
पूर्ण;

अटल स्थिर काष्ठा ngene_info ngene_info_cineS2v5 = अणु
	.type		= NGENE_SIDEWINDER,
	.name		= "Linux4Media cineS2 DVB-S2 Twin Tuner (v5)",
	.io_type	= अणुNGENE_IO_TSIN, NGENE_IO_TSIN, NGENE_IO_TSIN, NGENE_IO_TSIN,
			   NGENE_IO_TSOUTपूर्ण,
	.demod_attach	= अणुdemod_attach_stv0900, demod_attach_stv0900, cineS2_probe, cineS2_probeपूर्ण,
	.tuner_attach	= अणुtuner_attach_stv6110, tuner_attach_stv6110, tuner_attach_probe, tuner_attach_probeपूर्ण,
	.fe_config	= अणु&fe_cineS2, &fe_cineS2, &fe_cineS2_2, &fe_cineS2_2पूर्ण,
	.tuner_config	= अणु&tuner_cineS2_0, &tuner_cineS2_1, &tuner_cineS2_0, &tuner_cineS2_1पूर्ण,
	.lnb		= अणु0x0a, 0x08, 0x0b, 0x09पूर्ण,
	.tsf		= अणु3, 3पूर्ण,
	.fw_version	= 18,
	.msi_supported	= true,
पूर्ण;


अटल स्थिर काष्ठा ngene_info ngene_info_duoFlex = अणु
	.type           = NGENE_SIDEWINDER,
	.name           = "Digital Devices DuoFlex PCIe or miniPCIe",
	.io_type        = अणुNGENE_IO_TSIN, NGENE_IO_TSIN, NGENE_IO_TSIN, NGENE_IO_TSIN,
			   NGENE_IO_TSOUTपूर्ण,
	.demod_attach   = अणुcineS2_probe, cineS2_probe, cineS2_probe, cineS2_probeपूर्ण,
	.tuner_attach   = अणुtuner_attach_probe, tuner_attach_probe, tuner_attach_probe, tuner_attach_probeपूर्ण,
	.fe_config      = अणु&fe_cineS2, &fe_cineS2, &fe_cineS2_2, &fe_cineS2_2पूर्ण,
	.tuner_config   = अणु&tuner_cineS2_0, &tuner_cineS2_1, &tuner_cineS2_0, &tuner_cineS2_1पूर्ण,
	.lnb            = अणु0x0a, 0x08, 0x0b, 0x09पूर्ण,
	.tsf            = अणु3, 3पूर्ण,
	.fw_version     = 18,
	.msi_supported	= true,
पूर्ण;

अटल स्थिर काष्ठा ngene_info ngene_info_m780 = अणु
	.type           = NGENE_APP,
	.name           = "Aver M780 ATSC/QAM-B",

	/* Channel 0 is analog, which is currently unsupported */
	.io_type        = अणु NGENE_IO_NONE, NGENE_IO_TSIN पूर्ण,
	.demod_attach   = अणु शून्य, demod_attach_lg330x पूर्ण,

	/* Ensure these are शून्य अन्यथा the frame will call them (as funcs) */
	.tuner_attach   = अणु शून्य, शून्य, शून्य, शून्य पूर्ण,
	.fe_config      = अणु शून्य, &aver_m780 पूर्ण,
	.avf            = अणु 0 पूर्ण,

	/* A custom electrical पूर्णांकerface config क्रम the demod to bridge */
	.tsf		= अणु 4, 4 पूर्ण,
	.fw_version	= 15,
पूर्ण;

अटल काष्ठा drxd_config fe_terratec_dvbt_0 = अणु
	.index          = 0,
	.demod_address  = 0x70,
	.demod_revision = 0xa2,
	.demoda_address = 0x00,
	.pll_address    = 0x60,
	.pll_type       = DVB_PLL_THOMSON_DTT7520X,
	.घड़ी          = 20000,
	.osc_deviation  = osc_deviation,
पूर्ण;

अटल काष्ठा drxd_config fe_terratec_dvbt_1 = अणु
	.index          = 1,
	.demod_address  = 0x71,
	.demod_revision = 0xa2,
	.demoda_address = 0x00,
	.pll_address    = 0x60,
	.pll_type       = DVB_PLL_THOMSON_DTT7520X,
	.घड़ी          = 20000,
	.osc_deviation  = osc_deviation,
पूर्ण;

अटल स्थिर काष्ठा ngene_info ngene_info_terratec = अणु
	.type           = NGENE_TERRATEC,
	.name           = "Terratec Integra/Cinergy2400i Dual DVB-T",
	.io_type        = अणुNGENE_IO_TSIN, NGENE_IO_TSINपूर्ण,
	.demod_attach   = अणुdemod_attach_drxd, demod_attach_drxdपूर्ण,
	.tuner_attach	= अणुtuner_attach_dtt7520x, tuner_attach_dtt7520xपूर्ण,
	.fe_config      = अणु&fe_terratec_dvbt_0, &fe_terratec_dvbt_1पूर्ण,
	.i2c_access     = 1,
पूर्ण;

/****************************************************************************/



/****************************************************************************/
/* PCI Subप्रणाली ID *********************************************************/
/****************************************************************************/

#घोषणा NGENE_ID(_subvend, _subdev, _driverdata) अणु \
	.venकरोr = NGENE_VID, .device = NGENE_PID, \
	.subvenकरोr = _subvend, .subdevice = _subdev, \
	.driver_data = (अचिन्हित दीर्घ) &_driverdata पूर्ण

/****************************************************************************/

अटल स्थिर काष्ठा pci_device_id ngene_id_tbl[] = अणु
	NGENE_ID(0x18c3, 0xab04, ngene_info_cineS2),
	NGENE_ID(0x18c3, 0xab05, ngene_info_cineS2v5),
	NGENE_ID(0x18c3, 0xabc3, ngene_info_cineS2),
	NGENE_ID(0x18c3, 0xabc4, ngene_info_cineS2),
	NGENE_ID(0x18c3, 0xdb01, ngene_info_satixS2),
	NGENE_ID(0x18c3, 0xdb02, ngene_info_satixS2v2),
	NGENE_ID(0x18c3, 0xdd00, ngene_info_cineS2v5),
	NGENE_ID(0x18c3, 0xdd10, ngene_info_duoFlex),
	NGENE_ID(0x18c3, 0xdd20, ngene_info_duoFlex),
	NGENE_ID(0x1461, 0x062e, ngene_info_m780),
	NGENE_ID(0x153b, 0x1167, ngene_info_terratec),
	अणु0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ngene_id_tbl);

/****************************************************************************/
/* Init/Exit ****************************************************************/
/****************************************************************************/

अटल pci_ers_result_t ngene_error_detected(काष्ठा pci_dev *dev,
					     pci_channel_state_t state)
अणु
	dev_err(&dev->dev, "PCI error\n");
	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;
	अगर (state == pci_channel_io_frozen)
		वापस PCI_ERS_RESULT_NEED_RESET;
	वापस PCI_ERS_RESULT_CAN_RECOVER;
पूर्ण

अटल pci_ers_result_t ngene_slot_reset(काष्ठा pci_dev *dev)
अणु
	dev_info(&dev->dev, "slot reset\n");
	वापस 0;
पूर्ण

अटल व्योम ngene_resume(काष्ठा pci_dev *dev)
अणु
	dev_info(&dev->dev, "resume\n");
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers ngene_errors = अणु
	.error_detected = ngene_error_detected,
	.slot_reset = ngene_slot_reset,
	.resume = ngene_resume,
पूर्ण;

अटल काष्ठा pci_driver ngene_pci_driver = अणु
	.name        = "ngene",
	.id_table    = ngene_id_tbl,
	.probe       = ngene_probe,
	.हटाओ      = ngene_हटाओ,
	.err_handler = &ngene_errors,
	.shutकरोwn    = ngene_shutकरोwn,
पूर्ण;

अटल __init पूर्णांक module_init_ngene(व्योम)
अणु
	/* pr_*() since we करोn't have a device to use with dev_*() yet */
	pr_info("nGene PCIE bridge driver, Copyright (C) 2005-2007 Micronas\n");

	वापस pci_रेजिस्टर_driver(&ngene_pci_driver);
पूर्ण

अटल __निकास व्योम module_निकास_ngene(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ngene_pci_driver);
पूर्ण

module_init(module_init_ngene);
module_निकास(module_निकास_ngene);

MODULE_DESCRIPTION("nGene");
MODULE_AUTHOR("Micronas, Ralph Metzler, Manfred Voelkel");
MODULE_LICENSE("GPL");
