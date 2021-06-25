<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ddbridge-mci.c: Digital Devices microcode पूर्णांकerface
 *
 * Copyright (C) 2017-2018 Digital Devices GmbH
 *                         Ralph Metzler <rjkm@metzlerbros.de>
 *                         Marcus Metzler <mocm@metzlerbros.de>
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

अटल LIST_HEAD(mci_list);

अटल पूर्णांक mci_reset(काष्ठा mci *state)
अणु
	काष्ठा ddb_link *link = state->base->link;
	u32 status = 0;
	u32 समयout = 40;

	ddblग_लिखोl(link, MCI_CONTROL_RESET, MCI_CONTROL);
	ddblग_लिखोl(link, 0, MCI_CONTROL + 4); /* 1= no पूर्णांकernal init */
	msleep(300);
	ddblग_लिखोl(link, 0, MCI_CONTROL);

	जबतक (1) अणु
		status = ddblपढ़ोl(link, MCI_CONTROL);
		अगर ((status & MCI_CONTROL_READY) == MCI_CONTROL_READY)
			अवरोध;
		अगर (--समयout == 0)
			अवरोध;
		msleep(50);
	पूर्ण
	अगर ((status & MCI_CONTROL_READY) == 0)
		वापस -1;
	अगर (link->ids.device == 0x0009)
		ddblग_लिखोl(link, SX8_TSCONFIG_MODE_NORMAL, SX8_TSCONFIG);
	वापस 0;
पूर्ण

पूर्णांक ddb_mci_config(काष्ठा mci *state, u32 config)
अणु
	काष्ठा ddb_link *link = state->base->link;

	अगर (link->ids.device != 0x0009)
		वापस -EINVAL;
	ddblग_लिखोl(link, config, SX8_TSCONFIG);
	वापस 0;
पूर्ण

अटल पूर्णांक _mci_cmd_unlocked(काष्ठा mci *state,
			     u32 *cmd, u32 cmd_len,
			     u32 *res, u32 res_len)
अणु
	काष्ठा ddb_link *link = state->base->link;
	u32 i, val;
	अचिन्हित दीर्घ stat;

	val = ddblपढ़ोl(link, MCI_CONTROL);
	अगर (val & (MCI_CONTROL_RESET | MCI_CONTROL_START_COMMAND))
		वापस -EIO;
	अगर (cmd && cmd_len)
		क्रम (i = 0; i < cmd_len; i++)
			ddblग_लिखोl(link, cmd[i], MCI_COMMAND + i * 4);
	val |= (MCI_CONTROL_START_COMMAND | MCI_CONTROL_ENABLE_DONE_INTERRUPT);
	ddblग_लिखोl(link, val, MCI_CONTROL);

	stat = रुको_क्रम_completion_समयout(&state->base->completion, HZ);
	अगर (stat == 0) अणु
		dev_warn(state->base->dev, "MCI-%d: MCI timeout\n", state->nr);
		वापस -EIO;
	पूर्ण
	अगर (res && res_len)
		क्रम (i = 0; i < res_len; i++)
			res[i] = ddblपढ़ोl(link, MCI_RESULT + i * 4);
	वापस 0;
पूर्ण

पूर्णांक ddb_mci_cmd(काष्ठा mci *state,
		काष्ठा mci_command *command,
		काष्ठा mci_result *result)
अणु
	पूर्णांक stat;

	mutex_lock(&state->base->mci_lock);
	stat = _mci_cmd_unlocked(state,
				 (u32 *)command, माप(*command) / माप(u32),
				 (u32 *)result,	माप(*result) / माप(u32));
	mutex_unlock(&state->base->mci_lock);
	वापस stat;
पूर्ण

अटल व्योम mci_handler(व्योम *priv)
अणु
	काष्ठा mci_base *base = (काष्ठा mci_base *)priv;

	complete(&base->completion);
पूर्ण

अटल काष्ठा mci_base *match_base(व्योम *key)
अणु
	काष्ठा mci_base *p;

	list_क्रम_each_entry(p, &mci_list, mci_list)
		अगर (p->key == key)
			वापस p;
	वापस शून्य;
पूर्ण

अटल पूर्णांक probe(काष्ठा mci *state)
अणु
	mci_reset(state);
	वापस 0;
पूर्ण

काष्ठा dvb_frontend
*ddb_mci_attach(काष्ठा ddb_input *input, काष्ठा mci_cfg *cfg, पूर्णांक nr,
		पूर्णांक (**fn_set_input)(काष्ठा dvb_frontend *fe, पूर्णांक input))
अणु
	काष्ठा ddb_port *port = input->port;
	काष्ठा ddb *dev = port->dev;
	काष्ठा ddb_link *link = &dev->link[port->lnr];
	काष्ठा mci_base *base;
	काष्ठा mci *state;
	व्योम *key = cfg->type ? (व्योम *)port : (व्योम *)link;

	state = kzalloc(cfg->state_size, GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	base = match_base(key);
	अगर (base) अणु
		base->count++;
		state->base = base;
	पूर्ण अन्यथा अणु
		base = kzalloc(cfg->base_size, GFP_KERNEL);
		अगर (!base)
			जाओ fail;
		base->key = key;
		base->count = 1;
		base->link = link;
		base->dev = dev->dev;
		mutex_init(&base->mci_lock);
		mutex_init(&base->tuner_lock);
		ddb_irq_set(dev, link->nr, 0, mci_handler, base);
		init_completion(&base->completion);
		state->base = base;
		अगर (probe(state) < 0) अणु
			kमुक्त(base);
			जाओ fail;
		पूर्ण
		list_add(&base->mci_list, &mci_list);
		अगर (cfg->base_init)
			cfg->base_init(base);
	पूर्ण
	स_नकल(&state->fe.ops, cfg->fe_ops, माप(काष्ठा dvb_frontend_ops));
	state->fe.demodulator_priv = state;
	state->nr = nr;
	*fn_set_input = cfg->set_input;
	state->tuner = nr;
	state->demod = nr;
	अगर (cfg->init)
		cfg->init(state);
	वापस &state->fe;
fail:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
