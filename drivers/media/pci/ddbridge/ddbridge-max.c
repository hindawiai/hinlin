<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ddbridge-max.c: Digital Devices bridge MAX card support
 *
 * Copyright (C) 2010-2017 Digital Devices GmbH
 *                         Ralph Metzler <rjkm@metzlerbros.de>
 *                         Marcus Metzler <mocm@metzlerbros.de>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 only, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/समयr.h>
#समावेश <linux/i2c.h>
#समावेश <linux/swab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "ddbridge.h"
#समावेश "ddbridge-regs.h"
#समावेश "ddbridge-io.h"
#समावेश "ddbridge-mci.h"

#समावेश "ddbridge-max.h"
#समावेश "mxl5xx.h"

/******************************************************************************/

/* MaxS4/8 related modparams */
अटल पूर्णांक भ_शेषe;
module_param(भ_शेषe, पूर्णांक, 0444);
MODULE_PARM_DESC(भ_शेषe, "frontend emulation mode");

अटल पूर्णांक भ_शेषe_sat = -1;
module_param(भ_शेषe_sat, पूर्णांक, 0444);
MODULE_PARM_DESC(भ_शेषe_sat, "set frontend emulation mode sat");

अटल पूर्णांक old_quattro;
module_param(old_quattro, पूर्णांक, 0444);
MODULE_PARM_DESC(old_quattro, "old quattro LNB input order ");

/******************************************************************************/

अटल पूर्णांक lnb_command(काष्ठा ddb *dev, u32 link, u32 lnb, u32 cmd)
अणु
	u32 c, v = 0, tag = DDB_LINK_TAG(link);

	v = LNB_TONE & (dev->link[link].lnb.tone << (15 - lnb));
	ddbग_लिखोl(dev, cmd | v, tag | LNB_CONTROL(lnb));
	क्रम (c = 0; c < 10; c++) अणु
		v = ddbपढ़ोl(dev, tag | LNB_CONTROL(lnb));
		अगर ((v & LNB_BUSY) == 0)
			अवरोध;
		msleep(20);
	पूर्ण
	अगर (c == 10)
		dev_info(dev->dev, "%s lnb = %08x  cmd = %08x\n",
			 __func__, lnb, cmd);
	वापस 0;
पूर्ण

अटल पूर्णांक max_send_master_cmd(काष्ठा dvb_frontend *fe,
			       काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	काष्ठा ddb_input *input = fe->sec_priv;
	काष्ठा ddb_port *port = input->port;
	काष्ठा ddb *dev = port->dev;
	काष्ठा ddb_dvb *dvb = &port->dvb[input->nr & 1];
	u32 tag = DDB_LINK_TAG(port->lnr);
	पूर्णांक i;
	u32 भ_शेषe = dev->link[port->lnr].lnb.भ_शेषe;

	अगर (भ_शेषe == 2 || भ_शेषe == 1)
		वापस 0;
	अगर (dvb->diseqc_send_master_cmd)
		dvb->diseqc_send_master_cmd(fe, cmd);

	mutex_lock(&dev->link[port->lnr].lnb.lock);
	ddbग_लिखोl(dev, 0, tag | LNB_BUF_LEVEL(dvb->input));
	क्रम (i = 0; i < cmd->msg_len; i++)
		ddbग_लिखोl(dev, cmd->msg[i], tag | LNB_BUF_WRITE(dvb->input));
	lnb_command(dev, port->lnr, dvb->input, LNB_CMD_DISEQC);
	mutex_unlock(&dev->link[port->lnr].lnb.lock);
	वापस 0;
पूर्ण

अटल पूर्णांक lnb_send_diseqc(काष्ठा ddb *dev, u32 link, u32 input,
			   काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	u32 tag = DDB_LINK_TAG(link);
	पूर्णांक i;

	ddbग_लिखोl(dev, 0, tag | LNB_BUF_LEVEL(input));
	क्रम (i = 0; i < cmd->msg_len; i++)
		ddbग_लिखोl(dev, cmd->msg[i], tag | LNB_BUF_WRITE(input));
	lnb_command(dev, link, input, LNB_CMD_DISEQC);
	वापस 0;
पूर्ण

अटल पूर्णांक lnb_set_sat(काष्ठा ddb *dev, u32 link, u32 input, u32 sat, u32 band,
		       u32 hor)
अणु
	काष्ठा dvb_diseqc_master_cmd cmd = अणु
		.msg = अणु0xe0, 0x10, 0x38, 0xf0, 0x00, 0x00पूर्ण,
		.msg_len = 4
	पूर्ण;
	cmd.msg[3] = 0xf0 | (((sat << 2) & 0x0c) | (band ? 1 : 0) |
		(hor ? 2 : 0));
	वापस lnb_send_diseqc(dev, link, input, &cmd);
पूर्ण

अटल पूर्णांक lnb_set_tone(काष्ठा ddb *dev, u32 link, u32 input,
			क्रमागत fe_sec_tone_mode tone)
अणु
	पूर्णांक s = 0;
	u32 mask = (1ULL << input);

	चयन (tone) अणु
	हाल SEC_TONE_OFF:
		अगर (!(dev->link[link].lnb.tone & mask))
			वापस 0;
		dev->link[link].lnb.tone &= ~(1ULL << input);
		अवरोध;
	हाल SEC_TONE_ON:
		अगर (dev->link[link].lnb.tone & mask)
			वापस 0;
		dev->link[link].lnb.tone |= (1ULL << input);
		अवरोध;
	शेष:
		s = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (!s)
		s = lnb_command(dev, link, input, LNB_CMD_NOP);
	वापस s;
पूर्ण

अटल पूर्णांक lnb_set_voltage(काष्ठा ddb *dev, u32 link, u32 input,
			   क्रमागत fe_sec_voltage voltage)
अणु
	पूर्णांक s = 0;

	अगर (dev->link[link].lnb.oldvoltage[input] == voltage)
		वापस 0;
	चयन (voltage) अणु
	हाल SEC_VOLTAGE_OFF:
		अगर (dev->link[link].lnb.voltage[input])
			वापस 0;
		lnb_command(dev, link, input, LNB_CMD_OFF);
		अवरोध;
	हाल SEC_VOLTAGE_13:
		lnb_command(dev, link, input, LNB_CMD_LOW);
		अवरोध;
	हाल SEC_VOLTAGE_18:
		lnb_command(dev, link, input, LNB_CMD_HIGH);
		अवरोध;
	शेष:
		s = -EINVAL;
		अवरोध;
	पूर्ण
	dev->link[link].lnb.oldvoltage[input] = voltage;
	वापस s;
पूर्ण

अटल पूर्णांक max_set_input_unlocked(काष्ठा dvb_frontend *fe, पूर्णांक in)
अणु
	काष्ठा ddb_input *input = fe->sec_priv;
	काष्ठा ddb_port *port = input->port;
	काष्ठा ddb *dev = port->dev;
	काष्ठा ddb_dvb *dvb = &port->dvb[input->nr & 1];
	पूर्णांक res = 0;

	अगर (in > 3)
		वापस -EINVAL;
	अगर (dvb->input != in) अणु
		u32 bit = (1ULL << input->nr);
		u32 obit =
			dev->link[port->lnr].lnb.voltage[dvb->input & 3] & bit;

		dev->link[port->lnr].lnb.voltage[dvb->input & 3] &= ~bit;
		dvb->input = in;
		dev->link[port->lnr].lnb.voltage[dvb->input & 3] |= obit;
	पूर्ण
	res = dvb->set_input(fe, in);
	वापस res;
पूर्ण

अटल पूर्णांक max_set_tone(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा ddb_input *input = fe->sec_priv;
	काष्ठा ddb_port *port = input->port;
	काष्ठा ddb *dev = port->dev;
	काष्ठा ddb_dvb *dvb = &port->dvb[input->nr & 1];
	पूर्णांक tuner = 0;
	पूर्णांक res = 0;
	u32 भ_शेषe = dev->link[port->lnr].lnb.भ_शेषe;

	mutex_lock(&dev->link[port->lnr].lnb.lock);
	dvb->tone = tone;
	चयन (भ_शेषe) अणु
	शेष:
	हाल 0:
	हाल 3:
		res = lnb_set_tone(dev, port->lnr, dvb->input, tone);
		अवरोध;
	हाल 1:
	हाल 2:
		अगर (old_quattro) अणु
			अगर (dvb->tone == SEC_TONE_ON)
				tuner |= 2;
			अगर (dvb->voltage == SEC_VOLTAGE_18)
				tuner |= 1;
		पूर्ण अन्यथा अणु
			अगर (dvb->tone == SEC_TONE_ON)
				tuner |= 1;
			अगर (dvb->voltage == SEC_VOLTAGE_18)
				tuner |= 2;
		पूर्ण
		res = max_set_input_unlocked(fe, tuner);
		अवरोध;
	पूर्ण
	mutex_unlock(&dev->link[port->lnr].lnb.lock);
	वापस res;
पूर्ण

अटल पूर्णांक max_set_voltage(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा ddb_input *input = fe->sec_priv;
	काष्ठा ddb_port *port = input->port;
	काष्ठा ddb *dev = port->dev;
	काष्ठा ddb_dvb *dvb = &port->dvb[input->nr & 1];
	पूर्णांक tuner = 0;
	u32 nv, ov = dev->link[port->lnr].lnb.voltages;
	पूर्णांक res = 0;
	u32 भ_शेषe = dev->link[port->lnr].lnb.भ_शेषe;

	mutex_lock(&dev->link[port->lnr].lnb.lock);
	dvb->voltage = voltage;

	चयन (भ_शेषe) अणु
	हाल 3:
	शेष:
	हाल 0:
		अगर (भ_शेषe == 3)
			max_set_input_unlocked(fe, 0);
		अगर (voltage == SEC_VOLTAGE_OFF)
			dev->link[port->lnr].lnb.voltage[dvb->input] &=
				~(1ULL << input->nr);
		अन्यथा
			dev->link[port->lnr].lnb.voltage[dvb->input] |=
				(1ULL << input->nr);

		res = lnb_set_voltage(dev, port->lnr, dvb->input, voltage);
		अवरोध;
	हाल 1:
	हाल 2:
		अगर (voltage == SEC_VOLTAGE_OFF)
			dev->link[port->lnr].lnb.voltages &=
				~(1ULL << input->nr);
		अन्यथा
			dev->link[port->lnr].lnb.voltages |=
				(1ULL << input->nr);

		nv = dev->link[port->lnr].lnb.voltages;

		अगर (old_quattro) अणु
			अगर (dvb->tone == SEC_TONE_ON)
				tuner |= 2;
			अगर (dvb->voltage == SEC_VOLTAGE_18)
				tuner |= 1;
		पूर्ण अन्यथा अणु
			अगर (dvb->tone == SEC_TONE_ON)
				tuner |= 1;
			अगर (dvb->voltage == SEC_VOLTAGE_18)
				tuner |= 2;
		पूर्ण
		res = max_set_input_unlocked(fe, tuner);

		अगर (nv != ov) अणु
			अगर (nv) अणु
				lnb_set_voltage(
					dev, port->lnr,
					0, SEC_VOLTAGE_13);
				अगर (भ_शेषe == 1) अणु
					lnb_set_voltage(
						dev, port->lnr,
						0, SEC_VOLTAGE_13);
					अगर (old_quattro) अणु
						lnb_set_voltage(
							dev, port->lnr,
							1, SEC_VOLTAGE_18);
						lnb_set_voltage(
							dev, port->lnr,
							2, SEC_VOLTAGE_13);
					पूर्ण अन्यथा अणु
						lnb_set_voltage(
							dev, port->lnr,
							1, SEC_VOLTAGE_13);
						lnb_set_voltage(
							dev, port->lnr,
							2, SEC_VOLTAGE_18);
					पूर्ण
					lnb_set_voltage(
						dev, port->lnr,
						3, SEC_VOLTAGE_18);
				पूर्ण
			पूर्ण अन्यथा अणु
				lnb_set_voltage(
					dev, port->lnr,
					0, SEC_VOLTAGE_OFF);
				अगर (भ_शेषe == 1) अणु
					lnb_set_voltage(
						dev, port->lnr,
						1, SEC_VOLTAGE_OFF);
					lnb_set_voltage(
						dev, port->lnr,
						2, SEC_VOLTAGE_OFF);
					lnb_set_voltage(
						dev, port->lnr,
						3, SEC_VOLTAGE_OFF);
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	mutex_unlock(&dev->link[port->lnr].lnb.lock);
	वापस res;
पूर्ण

अटल पूर्णांक max_enable_high_lnb_voltage(काष्ठा dvb_frontend *fe, दीर्घ arg)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक max_send_burst(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_mini_cmd burst)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mxl_fw_पढ़ो(व्योम *priv, u8 *buf, u32 len)
अणु
	काष्ठा ddb_link *link = priv;
	काष्ठा ddb *dev = link->dev;

	dev_info(dev->dev, "Read mxl_fw from link %u\n", link->nr);

	वापस ddbridge_flashपढ़ो(dev, link->nr, buf, 0xc0000, len);
पूर्ण

पूर्णांक ddb_lnb_init_भ_शेषe(काष्ठा ddb *dev, काष्ठा ddb_link *link, u32 fm)
अणु
	u32 l = link->nr;

	अगर (link->lnb.भ_शेषe == fm)
		वापस 0;
	dev_info(dev->dev, "Set fmode link %u = %u\n", l, fm);
	mutex_lock(&link->lnb.lock);
	अगर (fm == 2 || fm == 1) अणु
		अगर (भ_शेषe_sat >= 0) अणु
			lnb_set_sat(dev, l, 0, भ_शेषe_sat, 0, 0);
			अगर (old_quattro) अणु
				lnb_set_sat(dev, l, 1, भ_शेषe_sat, 0, 1);
				lnb_set_sat(dev, l, 2, भ_शेषe_sat, 1, 0);
			पूर्ण अन्यथा अणु
				lnb_set_sat(dev, l, 1, भ_शेषe_sat, 1, 0);
				lnb_set_sat(dev, l, 2, भ_शेषe_sat, 0, 1);
			पूर्ण
			lnb_set_sat(dev, l, 3, भ_शेषe_sat, 1, 1);
		पूर्ण
		lnb_set_tone(dev, l, 0, SEC_TONE_OFF);
		अगर (old_quattro) अणु
			lnb_set_tone(dev, l, 1, SEC_TONE_OFF);
			lnb_set_tone(dev, l, 2, SEC_TONE_ON);
		पूर्ण अन्यथा अणु
			lnb_set_tone(dev, l, 1, SEC_TONE_ON);
			lnb_set_tone(dev, l, 2, SEC_TONE_OFF);
		पूर्ण
		lnb_set_tone(dev, l, 3, SEC_TONE_ON);
	पूर्ण
	link->lnb.भ_शेषe = fm;
	mutex_unlock(&link->lnb.lock);
	वापस 0;
पूर्ण

अटल काष्ठा mxl5xx_cfg mxl5xx = अणु
	.adr      = 0x60,
	.type     = 0x01,
	.clk      = 27000000,
	.ts_clk   = 139,
	.cap      = 12,
	.fw_पढ़ो  = mxl_fw_पढ़ो,
पूर्ण;

पूर्णांक ddb_fe_attach_mxl5xx(काष्ठा ddb_input *input)
अणु
	काष्ठा ddb *dev = input->port->dev;
	काष्ठा i2c_adapter *i2c = &input->port->i2c->adap;
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	काष्ठा ddb_port *port = input->port;
	काष्ठा ddb_link *link = &dev->link[port->lnr];
	काष्ठा mxl5xx_cfg cfg;
	पूर्णांक demod, tuner;

	cfg = mxl5xx;
	cfg.fw_priv = link;
	dvb->set_input = शून्य;

	demod = input->nr;
	tuner = demod & 3;
	अगर (भ_शेषe == 3)
		tuner = 0;

	dvb->fe = dvb_attach(mxl5xx_attach, i2c, &cfg,
			     demod, tuner, &dvb->set_input);

	अगर (!dvb->fe) अणु
		dev_err(dev->dev, "No MXL5XX found!\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!dvb->set_input) अणु
		dev_err(dev->dev, "No mxl5xx_set_input function pointer!\n");
		वापस -ENODEV;
	पूर्ण

	अगर (input->nr < 4) अणु
		lnb_command(dev, port->lnr, input->nr, LNB_CMD_INIT);
		lnb_set_voltage(dev, port->lnr, input->nr, SEC_VOLTAGE_OFF);
	पूर्ण
	ddb_lnb_init_भ_शेषe(dev, link, भ_शेषe);

	dvb->fe->ops.set_voltage = max_set_voltage;
	dvb->fe->ops.enable_high_lnb_voltage = max_enable_high_lnb_voltage;
	dvb->fe->ops.set_tone = max_set_tone;
	dvb->diseqc_send_master_cmd = dvb->fe->ops.diseqc_send_master_cmd;
	dvb->fe->ops.diseqc_send_master_cmd = max_send_master_cmd;
	dvb->fe->ops.diseqc_send_burst = max_send_burst;
	dvb->fe->sec_priv = input;
	dvb->input = tuner;
	वापस 0;
पूर्ण

/******************************************************************************/
/* MAX MCI related functions */

पूर्णांक ddb_fe_attach_mci(काष्ठा ddb_input *input, u32 type)
अणु
	काष्ठा ddb *dev = input->port->dev;
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	काष्ठा ddb_port *port = input->port;
	काष्ठा ddb_link *link = &dev->link[port->lnr];
	पूर्णांक demod, tuner;
	काष्ठा mci_cfg cfg;

	demod = input->nr;
	tuner = demod & 3;
	चयन (type) अणु
	हाल DDB_TUNER_MCI_SX8:
		cfg = ddb_max_sx8_cfg;
		अगर (भ_शेषe == 3)
			tuner = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	dvb->fe = ddb_mci_attach(input, &cfg, demod, &dvb->set_input);
	अगर (!dvb->fe) अणु
		dev_err(dev->dev, "No MCI card found!\n");
		वापस -ENODEV;
	पूर्ण
	अगर (!dvb->set_input) अणु
		dev_err(dev->dev, "No MCI set_input function pointer!\n");
		वापस -ENODEV;
	पूर्ण
	अगर (input->nr < 4) अणु
		lnb_command(dev, port->lnr, input->nr, LNB_CMD_INIT);
		lnb_set_voltage(dev, port->lnr, input->nr, SEC_VOLTAGE_OFF);
	पूर्ण
	ddb_lnb_init_भ_शेषe(dev, link, भ_शेषe);

	dvb->fe->ops.set_voltage = max_set_voltage;
	dvb->fe->ops.enable_high_lnb_voltage = max_enable_high_lnb_voltage;
	dvb->fe->ops.set_tone = max_set_tone;
	dvb->diseqc_send_master_cmd = dvb->fe->ops.diseqc_send_master_cmd;
	dvb->fe->ops.diseqc_send_master_cmd = max_send_master_cmd;
	dvb->fe->ops.diseqc_send_burst = max_send_burst;
	dvb->fe->sec_priv = input;
	dvb->input = tuner;
	वापस 0;
पूर्ण
