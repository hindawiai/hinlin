<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * budget-av.c: driver क्रम the SAA7146 based Budget DVB cards
 *              with analog video in
 *
 * Compiled from various sources by Michael Hunold <michael@mihu.de>
 *
 * CI पूर्णांकerface support (c) 2004 Olivier Gournet <ogournet@anevia.com> &
 *                               Andrew de Quincey <adq_dvb@lidskialf.net>
 *
 * Copyright (C) 2002 Ralph Metzler <rjkm@metzlerbros.de>
 *
 * Copyright (C) 1999-2002 Ralph  Metzler
 *                       & Marcus Metzler क्रम convergence पूर्णांकegrated media GmbH
 *
 * the project's page is at https://linuxtv.org
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "budget.h"
#समावेश "stv0299.h"
#समावेश "stb0899_drv.h"
#समावेश "stb0899_reg.h"
#समावेश "stb0899_cfg.h"
#समावेश "tda8261.h"
#समावेश "tda8261_cfg.h"
#समावेश "tda1002x.h"
#समावेश "tda1004x.h"
#समावेश "tua6100.h"
#समावेश "dvb-pll.h"
#समावेश <media/drv-पूर्णांकf/saa7146_vv.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/spinlock.h>

#समावेश <media/dvb_ca_en50221.h>

#घोषणा DEBICICAM		0x02420000

#घोषणा SLOTSTATUS_NONE         1
#घोषणा SLOTSTATUS_PRESENT      2
#घोषणा SLOTSTATUS_RESET        4
#घोषणा SLOTSTATUS_READY        8
#घोषणा SLOTSTATUS_OCCUPIED     (SLOTSTATUS_PRESENT|SLOTSTATUS_RESET|SLOTSTATUS_READY)

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

काष्ठा budget_av अणु
	काष्ठा budget budget;
	काष्ठा video_device vd;
	पूर्णांक cur_input;
	पूर्णांक has_saa7113;
	काष्ठा tasklet_काष्ठा ciपूर्णांकf_irq_tasklet;
	पूर्णांक slot_status;
	काष्ठा dvb_ca_en50221 ca;
	u8 reinitialise_demod:1;
पूर्ण;

अटल पूर्णांक ciपूर्णांकf_slot_shutकरोwn(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot);


/* GPIO Connections:
 * 0 - Vcc/Reset (Reset is controlled by capacitor). Resets the frontend *AS WELL*!
 * 1 - CI memory select 0=>IO memory, 1=>Attribute Memory
 * 2 - CI Card Enable (Active Low)
 * 3 - CI Card Detect
 */

/****************************************************************************
 * INITIALIZATION
 ****************************************************************************/

अटल u8 i2c_पढ़ोreg(काष्ठा i2c_adapter *i2c, u8 id, u8 reg)
अणु
	u8 mm1[] = अणु 0x00 पूर्ण;
	u8 mm2[] = अणु 0x00 पूर्ण;
	काष्ठा i2c_msg msgs[2];

	msgs[0].flags = 0;
	msgs[1].flags = I2C_M_RD;
	msgs[0].addr = msgs[1].addr = id / 2;
	mm1[0] = reg;
	msgs[0].len = 1;
	msgs[1].len = 1;
	msgs[0].buf = mm1;
	msgs[1].buf = mm2;

	i2c_transfer(i2c, msgs, 2);

	वापस mm2[0];
पूर्ण

अटल पूर्णांक i2c_पढ़ोregs(काष्ठा i2c_adapter *i2c, u8 id, u8 reg, u8 * buf, u8 len)
अणु
	u8 mm1[] = अणु reg पूर्ण;
	काष्ठा i2c_msg msgs[2] = अणु
		अणु.addr = id / 2,.flags = 0,.buf = mm1,.len = 1पूर्ण,
		अणु.addr = id / 2,.flags = I2C_M_RD,.buf = buf,.len = lenपूर्ण
	पूर्ण;

	अगर (i2c_transfer(i2c, msgs, 2) != 2)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_ग_लिखोreg(काष्ठा i2c_adapter *i2c, u8 id, u8 reg, u8 val)
अणु
	u8 msg[2] = अणु reg, val पूर्ण;
	काष्ठा i2c_msg msgs;

	msgs.flags = 0;
	msgs.addr = id / 2;
	msgs.len = 2;
	msgs.buf = msg;
	वापस i2c_transfer(i2c, &msgs, 1);
पूर्ण

अटल पूर्णांक ciपूर्णांकf_पढ़ो_attribute_mem(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक address)
अणु
	काष्ठा budget_av *budget_av = (काष्ठा budget_av *) ca->data;
	पूर्णांक result;

	अगर (slot != 0)
		वापस -EINVAL;

	saa7146_setgpio(budget_av->budget.dev, 1, SAA7146_GPIO_OUTHI);
	udelay(1);

	result = ttpci_budget_debiपढ़ो(&budget_av->budget, DEBICICAM, address & 0xfff, 1, 0, 1);
	अगर (result == -ETIMEDOUT) अणु
		ciपूर्णांकf_slot_shutकरोwn(ca, slot);
		pr_info("cam ejected 1\n");
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक ciपूर्णांकf_ग_लिखो_attribute_mem(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक address, u8 value)
अणु
	काष्ठा budget_av *budget_av = (काष्ठा budget_av *) ca->data;
	पूर्णांक result;

	अगर (slot != 0)
		वापस -EINVAL;

	saa7146_setgpio(budget_av->budget.dev, 1, SAA7146_GPIO_OUTHI);
	udelay(1);

	result = ttpci_budget_debiग_लिखो(&budget_av->budget, DEBICICAM, address & 0xfff, 1, value, 0, 1);
	अगर (result == -ETIMEDOUT) अणु
		ciपूर्णांकf_slot_shutकरोwn(ca, slot);
		pr_info("cam ejected 2\n");
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक ciपूर्णांकf_पढ़ो_cam_control(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, u8 address)
अणु
	काष्ठा budget_av *budget_av = (काष्ठा budget_av *) ca->data;
	पूर्णांक result;

	अगर (slot != 0)
		वापस -EINVAL;

	saa7146_setgpio(budget_av->budget.dev, 1, SAA7146_GPIO_OUTLO);
	udelay(1);

	result = ttpci_budget_debiपढ़ो(&budget_av->budget, DEBICICAM, address & 3, 1, 0, 0);
	अगर (result == -ETIMEDOUT) अणु
		ciपूर्णांकf_slot_shutकरोwn(ca, slot);
		pr_info("cam ejected 3\n");
		वापस -ETIMEDOUT;
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक ciपूर्णांकf_ग_लिखो_cam_control(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, u8 address, u8 value)
अणु
	काष्ठा budget_av *budget_av = (काष्ठा budget_av *) ca->data;
	पूर्णांक result;

	अगर (slot != 0)
		वापस -EINVAL;

	saa7146_setgpio(budget_av->budget.dev, 1, SAA7146_GPIO_OUTLO);
	udelay(1);

	result = ttpci_budget_debiग_लिखो(&budget_av->budget, DEBICICAM, address & 3, 1, value, 0, 0);
	अगर (result == -ETIMEDOUT) अणु
		ciपूर्णांकf_slot_shutकरोwn(ca, slot);
		pr_info("cam ejected 5\n");
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक ciपूर्णांकf_slot_reset(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा budget_av *budget_av = (काष्ठा budget_av *) ca->data;
	काष्ठा saa7146_dev *saa = budget_av->budget.dev;

	अगर (slot != 0)
		वापस -EINVAL;

	dprपूर्णांकk(1, "ciintf_slot_reset\n");
	budget_av->slot_status = SLOTSTATUS_RESET;

	saa7146_setgpio(saa, 2, SAA7146_GPIO_OUTHI); /* disable card */

	saa7146_setgpio(saa, 0, SAA7146_GPIO_OUTHI); /* Vcc off */
	msleep(2);
	saa7146_setgpio(saa, 0, SAA7146_GPIO_OUTLO); /* Vcc on */
	msleep(20); /* 20 ms Vcc settling समय */

	saa7146_setgpio(saa, 2, SAA7146_GPIO_OUTLO); /* enable card */
	ttpci_budget_set_video_port(saa, BUDGET_VIDEO_PORTB);
	msleep(20);

	/* reinitialise the frontend अगर necessary */
	अगर (budget_av->reinitialise_demod)
		dvb_frontend_reinitialise(budget_av->budget.dvb_frontend);

	वापस 0;
पूर्ण

अटल पूर्णांक ciपूर्णांकf_slot_shutकरोwn(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा budget_av *budget_av = (काष्ठा budget_av *) ca->data;
	काष्ठा saa7146_dev *saa = budget_av->budget.dev;

	अगर (slot != 0)
		वापस -EINVAL;

	dprपूर्णांकk(1, "ciintf_slot_shutdown\n");

	ttpci_budget_set_video_port(saa, BUDGET_VIDEO_PORTB);
	budget_av->slot_status = SLOTSTATUS_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक ciपूर्णांकf_slot_ts_enable(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा budget_av *budget_av = (काष्ठा budget_av *) ca->data;
	काष्ठा saa7146_dev *saa = budget_av->budget.dev;

	अगर (slot != 0)
		वापस -EINVAL;

	dprपूर्णांकk(1, "ciintf_slot_ts_enable: %d\n", budget_av->slot_status);

	ttpci_budget_set_video_port(saa, BUDGET_VIDEO_PORTA);

	वापस 0;
पूर्ण

अटल पूर्णांक ciपूर्णांकf_poll_slot_status(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक खोलो)
अणु
	काष्ठा budget_av *budget_av = (काष्ठा budget_av *) ca->data;
	काष्ठा saa7146_dev *saa = budget_av->budget.dev;
	पूर्णांक result;

	अगर (slot != 0)
		वापस -EINVAL;

	/* test the card detect line - needs to be करोne carefully
	 * since it never goes high क्रम some CAMs on this पूर्णांकerface (e.g. topuptv) */
	अगर (budget_av->slot_status == SLOTSTATUS_NONE) अणु
		saa7146_setgpio(saa, 3, SAA7146_GPIO_INPUT);
		udelay(1);
		अगर (saa7146_पढ़ो(saa, PSR) & MASK_06) अणु
			अगर (budget_av->slot_status == SLOTSTATUS_NONE) अणु
				budget_av->slot_status = SLOTSTATUS_PRESENT;
				pr_info("cam inserted A\n");
			पूर्ण
		पूर्ण
		saa7146_setgpio(saa, 3, SAA7146_GPIO_OUTLO);
	पूर्ण

	/* We also try and पढ़ो from IO memory to work round the above detection bug. If
	 * there is no CAM, we will get a समयout. Only करोne अगर there is no cam
	 * present, since this test actually अवरोधs some cams :(
	 *
	 * अगर the CI पूर्णांकerface is not खोलो, we also करो the above test since we
	 * करोn't care if the cam has problems - we'll be resetting it on खोलो() anyway */
	अगर ((budget_av->slot_status == SLOTSTATUS_NONE) || (!खोलो)) अणु
		saa7146_setgpio(budget_av->budget.dev, 1, SAA7146_GPIO_OUTLO);
		result = ttpci_budget_debiपढ़ो(&budget_av->budget, DEBICICAM, 0, 1, 0, 1);
		अगर ((result >= 0) && (budget_av->slot_status == SLOTSTATUS_NONE)) अणु
			budget_av->slot_status = SLOTSTATUS_PRESENT;
			pr_info("cam inserted B\n");
		पूर्ण अन्यथा अगर (result < 0) अणु
			अगर (budget_av->slot_status != SLOTSTATUS_NONE) अणु
				ciपूर्णांकf_slot_shutकरोwn(ca, slot);
				pr_info("cam ejected 5\n");
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	/* पढ़ो from attribute memory in reset/पढ़ोy state to know when the CAM is पढ़ोy */
	अगर (budget_av->slot_status == SLOTSTATUS_RESET) अणु
		result = ciपूर्णांकf_पढ़ो_attribute_mem(ca, slot, 0);
		अगर (result == 0x1d) अणु
			budget_av->slot_status = SLOTSTATUS_READY;
		पूर्ण
	पूर्ण

	/* work out correct वापस code */
	अगर (budget_av->slot_status != SLOTSTATUS_NONE) अणु
		अगर (budget_av->slot_status & SLOTSTATUS_READY) अणु
			वापस DVB_CA_EN50221_POLL_CAM_PRESENT | DVB_CA_EN50221_POLL_CAM_READY;
		पूर्ण
		वापस DVB_CA_EN50221_POLL_CAM_PRESENT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ciपूर्णांकf_init(काष्ठा budget_av *budget_av)
अणु
	काष्ठा saa7146_dev *saa = budget_av->budget.dev;
	पूर्णांक result;

	स_रखो(&budget_av->ca, 0, माप(काष्ठा dvb_ca_en50221));

	saa7146_setgpio(saa, 0, SAA7146_GPIO_OUTLO);
	saa7146_setgpio(saa, 1, SAA7146_GPIO_OUTLO);
	saa7146_setgpio(saa, 2, SAA7146_GPIO_OUTLO);
	saa7146_setgpio(saa, 3, SAA7146_GPIO_OUTLO);

	/* Enable DEBI pins */
	saa7146_ग_लिखो(saa, MC1, MASK_27 | MASK_11);

	/* रेजिस्टर CI पूर्णांकerface */
	budget_av->ca.owner = THIS_MODULE;
	budget_av->ca.पढ़ो_attribute_mem = ciपूर्णांकf_पढ़ो_attribute_mem;
	budget_av->ca.ग_लिखो_attribute_mem = ciपूर्णांकf_ग_लिखो_attribute_mem;
	budget_av->ca.पढ़ो_cam_control = ciपूर्णांकf_पढ़ो_cam_control;
	budget_av->ca.ग_लिखो_cam_control = ciपूर्णांकf_ग_लिखो_cam_control;
	budget_av->ca.slot_reset = ciपूर्णांकf_slot_reset;
	budget_av->ca.slot_shutकरोwn = ciपूर्णांकf_slot_shutकरोwn;
	budget_av->ca.slot_ts_enable = ciपूर्णांकf_slot_ts_enable;
	budget_av->ca.poll_slot_status = ciपूर्णांकf_poll_slot_status;
	budget_av->ca.data = budget_av;
	budget_av->budget.ci_present = 1;
	budget_av->slot_status = SLOTSTATUS_NONE;

	अगर ((result = dvb_ca_en50221_init(&budget_av->budget.dvb_adapter,
					  &budget_av->ca, 0, 1)) != 0) अणु
		pr_err("ci initialisation failed\n");
		जाओ error;
	पूर्ण

	pr_info("ci interface initialised\n");
	वापस 0;

error:
	saa7146_ग_लिखो(saa, MC1, MASK_27);
	वापस result;
पूर्ण

अटल व्योम ciपूर्णांकf_deinit(काष्ठा budget_av *budget_av)
अणु
	काष्ठा saa7146_dev *saa = budget_av->budget.dev;

	saa7146_setgpio(saa, 0, SAA7146_GPIO_INPUT);
	saa7146_setgpio(saa, 1, SAA7146_GPIO_INPUT);
	saa7146_setgpio(saa, 2, SAA7146_GPIO_INPUT);
	saa7146_setgpio(saa, 3, SAA7146_GPIO_INPUT);

	/* release the CA device */
	dvb_ca_en50221_release(&budget_av->ca);

	/* disable DEBI pins */
	saa7146_ग_लिखो(saa, MC1, MASK_27);
पूर्ण


अटल स्थिर u8 saa7113_tab[] = अणु
	0x01, 0x08,
	0x02, 0xc0,
	0x03, 0x33,
	0x04, 0x00,
	0x05, 0x00,
	0x06, 0xeb,
	0x07, 0xe0,
	0x08, 0x28,
	0x09, 0x00,
	0x0a, 0x80,
	0x0b, 0x47,
	0x0c, 0x40,
	0x0d, 0x00,
	0x0e, 0x01,
	0x0f, 0x44,

	0x10, 0x08,
	0x11, 0x0c,
	0x12, 0x7b,
	0x13, 0x00,
	0x15, 0x00, 0x16, 0x00, 0x17, 0x00,

	0x57, 0xff,
	0x40, 0x82, 0x58, 0x00, 0x59, 0x54, 0x5a, 0x07,
	0x5b, 0x83, 0x5e, 0x00,
	0xff
पूर्ण;

अटल पूर्णांक saa7113_init(काष्ठा budget_av *budget_av)
अणु
	काष्ठा budget *budget = &budget_av->budget;
	काष्ठा saa7146_dev *saa = budget->dev;
	स्थिर u8 *data = saa7113_tab;

	saa7146_setgpio(saa, 0, SAA7146_GPIO_OUTHI);
	msleep(200);

	अगर (i2c_ग_लिखोreg(&budget->i2c_adap, 0x4a, 0x01, 0x08) != 1) अणु
		dprपूर्णांकk(1, "saa7113 not found on KNC card\n");
		वापस -ENODEV;
	पूर्ण

	dprपूर्णांकk(1, "saa7113 detected and initializing\n");

	जबतक (*data != 0xff) अणु
		i2c_ग_लिखोreg(&budget->i2c_adap, 0x4a, *data, *(data + 1));
		data += 2;
	पूर्ण

	dprपूर्णांकk(1, "saa7113  status=%02x\n", i2c_पढ़ोreg(&budget->i2c_adap, 0x4a, 0x1f));

	वापस 0;
पूर्ण

अटल पूर्णांक saa7113_setinput(काष्ठा budget_av *budget_av, पूर्णांक input)
अणु
	काष्ठा budget *budget = &budget_av->budget;

	अगर (1 != budget_av->has_saa7113)
		वापस -ENODEV;

	अगर (input == 1) अणु
		i2c_ग_लिखोreg(&budget->i2c_adap, 0x4a, 0x02, 0xc7);
		i2c_ग_लिखोreg(&budget->i2c_adap, 0x4a, 0x09, 0x80);
	पूर्ण अन्यथा अगर (input == 0) अणु
		i2c_ग_लिखोreg(&budget->i2c_adap, 0x4a, 0x02, 0xc0);
		i2c_ग_लिखोreg(&budget->i2c_adap, 0x4a, 0x09, 0x00);
	पूर्ण अन्यथा
		वापस -EINVAL;

	budget_av->cur_input = input;
	वापस 0;
पूर्ण


अटल पूर्णांक philips_su1278_ty_ci_set_symbol_rate(काष्ठा dvb_frontend *fe, u32 srate, u32 ratio)
अणु
	u8 aclk = 0;
	u8 bclk = 0;
	u8 m1;

	aclk = 0xb5;
	अगर (srate < 2000000)
		bclk = 0x86;
	अन्यथा अगर (srate < 5000000)
		bclk = 0x89;
	अन्यथा अगर (srate < 15000000)
		bclk = 0x8f;
	अन्यथा अगर (srate < 45000000)
		bclk = 0x95;

	m1 = 0x14;
	अगर (srate < 4000000)
		m1 = 0x10;

	stv0299_ग_लिखोreg(fe, 0x13, aclk);
	stv0299_ग_लिखोreg(fe, 0x14, bclk);
	stv0299_ग_लिखोreg(fe, 0x1f, (ratio >> 16) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x20, (ratio >> 8) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x21, (ratio) & 0xf0);
	stv0299_ग_लिखोreg(fe, 0x0f, 0x80 | m1);

	वापस 0;
पूर्ण

अटल पूर्णांक philips_su1278_ty_ci_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 भाग;
	u8 buf[4];
	काष्ठा budget *budget = (काष्ठा budget *) fe->dvb->priv;
	काष्ठा i2c_msg msg = अणु.addr = 0x61,.flags = 0,.buf = buf,.len = माप(buf) पूर्ण;

	अगर ((c->frequency < 950000) || (c->frequency > 2150000))
		वापस -EINVAL;

	भाग = (c->frequency + (125 - 1)) / 125;	/* round correctly */
	buf[0] = (भाग >> 8) & 0x7f;
	buf[1] = भाग & 0xff;
	buf[2] = 0x80 | ((भाग & 0x18000) >> 10) | 4;
	buf[3] = 0x20;

	अगर (c->symbol_rate < 4000000)
		buf[3] |= 1;

	अगर (c->frequency < 1250000)
		buf[3] |= 0;
	अन्यथा अगर (c->frequency < 1550000)
		buf[3] |= 0x40;
	अन्यथा अगर (c->frequency < 2050000)
		buf[3] |= 0x80;
	अन्यथा अगर (c->frequency < 2150000)
		buf[3] |= 0xC0;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&budget->i2c_adap, &msg, 1) != 1)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल u8 typhoon_cinergy1200s_inittab[] = अणु
	0x01, 0x15,
	0x02, 0x30,
	0x03, 0x00,
	0x04, 0x7d,		/* F22FR = 0x7d, F22 = f_VCO / 128 / 0x7d = 22 kHz */
	0x05, 0x35,		/* I2CT = 0, SCLT = 1, SDAT = 1 */
	0x06, 0x40,		/* DAC not used, set to high impendance mode */
	0x07, 0x00,		/* DAC LSB */
	0x08, 0x40,		/* DiSEqC off */
	0x09, 0x00,		/* FIFO */
	0x0c, 0x51,		/* OP1 ctl = Normal, OP1 val = 1 (LNB Power ON) */
	0x0d, 0x82,		/* DC offset compensation = ON, beta_agc1 = 2 */
	0x0e, 0x23,		/* alpha_पंचांगg = 2, beta_पंचांगg = 3 */
	0x10, 0x3f,		// AGC2  0x3d
	0x11, 0x84,
	0x12, 0xb9,
	0x15, 0xc9,		// lock detector threshold
	0x16, 0x00,
	0x17, 0x00,
	0x18, 0x00,
	0x19, 0x00,
	0x1a, 0x00,
	0x1f, 0x50,
	0x20, 0x00,
	0x21, 0x00,
	0x22, 0x00,
	0x23, 0x00,
	0x28, 0x00,		// out imp: normal  out type: parallel FEC mode:0
	0x29, 0x1e,		// 1/2 threshold
	0x2a, 0x14,		// 2/3 threshold
	0x2b, 0x0f,		// 3/4 threshold
	0x2c, 0x09,		// 5/6 threshold
	0x2d, 0x05,		// 7/8 threshold
	0x2e, 0x01,
	0x31, 0x1f,		// test all FECs
	0x32, 0x19,		// viterbi and synchro search
	0x33, 0xfc,		// rs control
	0x34, 0x93,		// error control
	0x0f, 0x92,
	0xff, 0xff
पूर्ण;

अटल स्थिर काष्ठा stv0299_config typhoon_config = अणु
	.demod_address = 0x68,
	.inittab = typhoon_cinergy1200s_inittab,
	.mclk = 88000000UL,
	.invert = 0,
	.skip_reinit = 0,
	.lock_output = STV0299_LOCKOUTPUT_1,
	.volt13_op0_op1 = STV0299_VOLT13_OP0,
	.min_delay_ms = 100,
	.set_symbol_rate = philips_su1278_ty_ci_set_symbol_rate,
पूर्ण;


अटल स्थिर काष्ठा stv0299_config cinergy_1200s_config = अणु
	.demod_address = 0x68,
	.inittab = typhoon_cinergy1200s_inittab,
	.mclk = 88000000UL,
	.invert = 0,
	.skip_reinit = 0,
	.lock_output = STV0299_LOCKOUTPUT_0,
	.volt13_op0_op1 = STV0299_VOLT13_OP0,
	.min_delay_ms = 100,
	.set_symbol_rate = philips_su1278_ty_ci_set_symbol_rate,
पूर्ण;

अटल स्थिर काष्ठा stv0299_config cinergy_1200s_1894_0010_config = अणु
	.demod_address = 0x68,
	.inittab = typhoon_cinergy1200s_inittab,
	.mclk = 88000000UL,
	.invert = 1,
	.skip_reinit = 0,
	.lock_output = STV0299_LOCKOUTPUT_1,
	.volt13_op0_op1 = STV0299_VOLT13_OP0,
	.min_delay_ms = 100,
	.set_symbol_rate = philips_su1278_ty_ci_set_symbol_rate,
पूर्ण;

अटल पूर्णांक philips_cu1216_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा budget *budget = (काष्ठा budget *) fe->dvb->priv;
	u8 buf[6];
	काष्ठा i2c_msg msg = अणु.addr = 0x60,.flags = 0,.buf = buf,.len = माप(buf) पूर्ण;
	पूर्णांक i;

#घोषणा CU1216_IF 36125000
#घोषणा TUNER_MUL 62500

	u32 भाग = (c->frequency + CU1216_IF + TUNER_MUL / 2) / TUNER_MUL;

	buf[0] = (भाग >> 8) & 0x7f;
	buf[1] = भाग & 0xff;
	buf[2] = 0xce;
	buf[3] = (c->frequency < 150000000 ? 0x01 :
		  c->frequency < 445000000 ? 0x02 : 0x04);
	buf[4] = 0xde;
	buf[5] = 0x20;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&budget->i2c_adap, &msg, 1) != 1)
		वापस -EIO;

	/* रुको क्रम the pll lock */
	msg.flags = I2C_M_RD;
	msg.len = 1;
	क्रम (i = 0; i < 20; i++) अणु
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		अगर (i2c_transfer(&budget->i2c_adap, &msg, 1) == 1 && (buf[0] & 0x40))
			अवरोध;
		msleep(10);
	पूर्ण

	/* चयन the अक्षरge pump to the lower current */
	msg.flags = 0;
	msg.len = 2;
	msg.buf = &buf[2];
	buf[2] &= ~0x40;
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&budget->i2c_adap, &msg, 1) != 1)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल काष्ठा tda1002x_config philips_cu1216_config = अणु
	.demod_address = 0x0c,
	.invert = 1,
पूर्ण;

अटल काष्ठा tda1002x_config philips_cu1216_config_altaddress = अणु
	.demod_address = 0x0d,
	.invert = 0,
पूर्ण;

अटल काष्ठा tda10023_config philips_cu1216_tda10023_config = अणु
	.demod_address = 0x0c,
	.invert = 1,
पूर्ण;

अटल पूर्णांक philips_tu1216_tuner_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा budget *budget = (काष्ठा budget *) fe->dvb->priv;
	अटल u8 tu1216_init[] = अणु 0x0b, 0xf5, 0x85, 0xab पूर्ण;
	काष्ठा i2c_msg tuner_msg = अणु.addr = 0x60,.flags = 0,.buf = tu1216_init,.len = माप(tu1216_init) पूर्ण;

	// setup PLL configuration
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&budget->i2c_adap, &tuner_msg, 1) != 1)
		वापस -EIO;
	msleep(1);

	वापस 0;
पूर्ण

अटल पूर्णांक philips_tu1216_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा budget *budget = (काष्ठा budget *) fe->dvb->priv;
	u8 tuner_buf[4];
	काष्ठा i2c_msg tuner_msg = अणु.addr = 0x60,.flags = 0,.buf = tuner_buf,.len =
			माप(tuner_buf) पूर्ण;
	पूर्णांक tuner_frequency = 0;
	u8 band, cp, filter;

	// determine अक्षरge pump
	tuner_frequency = c->frequency + 36166000;
	अगर (tuner_frequency < 87000000)
		वापस -EINVAL;
	अन्यथा अगर (tuner_frequency < 130000000)
		cp = 3;
	अन्यथा अगर (tuner_frequency < 160000000)
		cp = 5;
	अन्यथा अगर (tuner_frequency < 200000000)
		cp = 6;
	अन्यथा अगर (tuner_frequency < 290000000)
		cp = 3;
	अन्यथा अगर (tuner_frequency < 420000000)
		cp = 5;
	अन्यथा अगर (tuner_frequency < 480000000)
		cp = 6;
	अन्यथा अगर (tuner_frequency < 620000000)
		cp = 3;
	अन्यथा अगर (tuner_frequency < 830000000)
		cp = 5;
	अन्यथा अगर (tuner_frequency < 895000000)
		cp = 7;
	अन्यथा
		वापस -EINVAL;

	// determine band
	अगर (c->frequency < 49000000)
		वापस -EINVAL;
	अन्यथा अगर (c->frequency < 161000000)
		band = 1;
	अन्यथा अगर (c->frequency < 444000000)
		band = 2;
	अन्यथा अगर (c->frequency < 861000000)
		band = 4;
	अन्यथा
		वापस -EINVAL;

	// setup PLL filter
	चयन (c->bandwidth_hz) अणु
	हाल 6000000:
		filter = 0;
		अवरोध;

	हाल 7000000:
		filter = 0;
		अवरोध;

	हाल 8000000:
		filter = 1;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	// calculate भागisor
	// ((36166000+((1000000/6)/2)) + Finput)/(1000000/6)
	tuner_frequency = (((c->frequency / 1000) * 6) + 217496) / 1000;

	// setup tuner buffer
	tuner_buf[0] = (tuner_frequency >> 8) & 0x7f;
	tuner_buf[1] = tuner_frequency & 0xff;
	tuner_buf[2] = 0xca;
	tuner_buf[3] = (cp << 5) | (filter << 3) | band;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&budget->i2c_adap, &tuner_msg, 1) != 1)
		वापस -EIO;

	msleep(1);
	वापस 0;
पूर्ण

अटल पूर्णांक philips_tu1216_request_firmware(काष्ठा dvb_frontend *fe,
					   स्थिर काष्ठा firmware **fw, अक्षर *name)
अणु
	काष्ठा budget *budget = (काष्ठा budget *) fe->dvb->priv;

	वापस request_firmware(fw, name, &budget->dev->pci->dev);
पूर्ण

अटल काष्ठा tda1004x_config philips_tu1216_config = अणु

	.demod_address = 0x8,
	.invert = 1,
	.invert_oclk = 1,
	.xtal_freq = TDA10046_XTAL_4M,
	.agc_config = TDA10046_AGC_DEFAULT,
	.अगर_freq = TDA10046_FREQ_3617,
	.request_firmware = philips_tu1216_request_firmware,
पूर्ण;

अटल u8 philips_sd1878_inittab[] = अणु
	0x01, 0x15,
	0x02, 0x30,
	0x03, 0x00,
	0x04, 0x7d,
	0x05, 0x35,
	0x06, 0x40,
	0x07, 0x00,
	0x08, 0x43,
	0x09, 0x02,
	0x0C, 0x51,
	0x0D, 0x82,
	0x0E, 0x23,
	0x10, 0x3f,
	0x11, 0x84,
	0x12, 0xb9,
	0x15, 0xc9,
	0x16, 0x19,
	0x17, 0x8c,
	0x18, 0x59,
	0x19, 0xf8,
	0x1a, 0xfe,
	0x1c, 0x7f,
	0x1d, 0x00,
	0x1e, 0x00,
	0x1f, 0x50,
	0x20, 0x00,
	0x21, 0x00,
	0x22, 0x00,
	0x23, 0x00,
	0x28, 0x00,
	0x29, 0x28,
	0x2a, 0x14,
	0x2b, 0x0f,
	0x2c, 0x09,
	0x2d, 0x09,
	0x31, 0x1f,
	0x32, 0x19,
	0x33, 0xfc,
	0x34, 0x93,
	0xff, 0xff
पूर्ण;

अटल पूर्णांक philips_sd1878_ci_set_symbol_rate(काष्ठा dvb_frontend *fe,
		u32 srate, u32 ratio)
अणु
	u8 aclk = 0;
	u8 bclk = 0;
	u8 m1;

	aclk = 0xb5;
	अगर (srate < 2000000)
		bclk = 0x86;
	अन्यथा अगर (srate < 5000000)
		bclk = 0x89;
	अन्यथा अगर (srate < 15000000)
		bclk = 0x8f;
	अन्यथा अगर (srate < 45000000)
		bclk = 0x95;

	m1 = 0x14;
	अगर (srate < 4000000)
		m1 = 0x10;

	stv0299_ग_लिखोreg(fe, 0x0e, 0x23);
	stv0299_ग_लिखोreg(fe, 0x0f, 0x94);
	stv0299_ग_लिखोreg(fe, 0x10, 0x39);
	stv0299_ग_लिखोreg(fe, 0x13, aclk);
	stv0299_ग_लिखोreg(fe, 0x14, bclk);
	stv0299_ग_लिखोreg(fe, 0x15, 0xc9);
	stv0299_ग_लिखोreg(fe, 0x1f, (ratio >> 16) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x20, (ratio >> 8) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x21, (ratio) & 0xf0);
	stv0299_ग_लिखोreg(fe, 0x0f, 0x80 | m1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा stv0299_config philips_sd1878_config = अणु
	.demod_address = 0x68,
     .inittab = philips_sd1878_inittab,
	.mclk = 88000000UL,
	.invert = 0,
	.skip_reinit = 0,
	.lock_output = STV0299_LOCKOUTPUT_1,
	.volt13_op0_op1 = STV0299_VOLT13_OP0,
	.min_delay_ms = 100,
	.set_symbol_rate = philips_sd1878_ci_set_symbol_rate,
पूर्ण;

/* KNC1 DVB-S (STB0899) Inittab	*/
अटल स्थिर काष्ठा stb0899_s1_reg knc1_stb0899_s1_init_1[] = अणु

	अणु STB0899_DEV_ID		, 0x81 पूर्ण,
	अणु STB0899_DISCNTRL1		, 0x32 पूर्ण,
	अणु STB0899_DISCNTRL2		, 0x80 पूर्ण,
	अणु STB0899_DISRX_ST0		, 0x04 पूर्ण,
	अणु STB0899_DISRX_ST1		, 0x00 पूर्ण,
	अणु STB0899_DISPARITY		, 0x00 पूर्ण,
	अणु STB0899_DISSTATUS		, 0x20 पूर्ण,
	अणु STB0899_DISF22		, 0x8c पूर्ण,
	अणु STB0899_DISF22RX		, 0x9a पूर्ण,
	अणु STB0899_SYSREG		, 0x0b पूर्ण,
	अणु STB0899_ACRPRESC		, 0x11 पूर्ण,
	अणु STB0899_ACRDIV1		, 0x0a पूर्ण,
	अणु STB0899_ACRDIV2		, 0x05 पूर्ण,
	अणु STB0899_DACR1			, 0x00 पूर्ण,
	अणु STB0899_DACR2			, 0x00 पूर्ण,
	अणु STB0899_OUTCFG		, 0x00 पूर्ण,
	अणु STB0899_MODECFG		, 0x00 पूर्ण,
	अणु STB0899_IRQSTATUS_3		, 0x30 पूर्ण,
	अणु STB0899_IRQSTATUS_2		, 0x00 पूर्ण,
	अणु STB0899_IRQSTATUS_1		, 0x00 पूर्ण,
	अणु STB0899_IRQSTATUS_0		, 0x00 पूर्ण,
	अणु STB0899_IRQMSK_3		, 0xf3 पूर्ण,
	अणु STB0899_IRQMSK_2		, 0xfc पूर्ण,
	अणु STB0899_IRQMSK_1		, 0xff पूर्ण,
	अणु STB0899_IRQMSK_0		, 0xff पूर्ण,
	अणु STB0899_IRQCFG		, 0x00 पूर्ण,
	अणु STB0899_I2CCFG		, 0x88 पूर्ण,
	अणु STB0899_I2CRPT		, 0x58 पूर्ण, /* Repeater=8, Stop=disabled */
	अणु STB0899_IOPVALUE5		, 0x00 पूर्ण,
	अणु STB0899_IOPVALUE4		, 0x20 पूर्ण,
	अणु STB0899_IOPVALUE3		, 0xc9 पूर्ण,
	अणु STB0899_IOPVALUE2		, 0x90 पूर्ण,
	अणु STB0899_IOPVALUE1		, 0x40 पूर्ण,
	अणु STB0899_IOPVALUE0		, 0x00 पूर्ण,
	अणु STB0899_GPIO00CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO01CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO02CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO03CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO04CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO05CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO06CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO07CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO08CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO09CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO10CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO11CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO12CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO13CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO14CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO15CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO16CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO17CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO18CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO19CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO20CFG		, 0x82 पूर्ण,
	अणु STB0899_SDATCFG		, 0xb8 पूर्ण,
	अणु STB0899_SCLTCFG		, 0xba पूर्ण,
	अणु STB0899_AGCRFCFG		, 0x08 पूर्ण, /* 0x1c */
	अणु STB0899_GPIO22		, 0x82 पूर्ण, /* AGCBB2CFG */
	अणु STB0899_GPIO21		, 0x91 पूर्ण, /* AGCBB1CFG */
	अणु STB0899_सूचीCLKCFG		, 0x82 पूर्ण,
	अणु STB0899_CLKOUT27CFG		, 0x7e पूर्ण,
	अणु STB0899_STDBYCFG		, 0x82 पूर्ण,
	अणु STB0899_CS0CFG		, 0x82 पूर्ण,
	अणु STB0899_CS1CFG		, 0x82 पूर्ण,
	अणु STB0899_DISEQCOCFG		, 0x20 पूर्ण,
	अणु STB0899_GPIO32CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO33CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO34CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO35CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO36CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO37CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO38CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO39CFG		, 0x82 पूर्ण,
	अणु STB0899_NCOARSE		, 0x15 पूर्ण, /* 0x15 = 27 Mhz Clock, F/3 = 198MHz, F/6 = 99MHz */
	अणु STB0899_SYNTCTRL		, 0x02 पूर्ण, /* 0x00 = CLK from CLKI, 0x02 = CLK from XTALI */
	अणु STB0899_FILTCTRL		, 0x00 पूर्ण,
	अणु STB0899_SYSCTRL		, 0x00 पूर्ण,
	अणु STB0899_STOPCLK1		, 0x20 पूर्ण,
	अणु STB0899_STOPCLK2		, 0x00 पूर्ण,
	अणु STB0899_INTBUFSTATUS		, 0x00 पूर्ण,
	अणु STB0899_INTBUFCTRL		, 0x0a पूर्ण,
	अणु 0xffff			, 0xff पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा stb0899_s1_reg knc1_stb0899_s1_init_3[] = अणु
	अणु STB0899_DEMOD			, 0x00 पूर्ण,
	अणु STB0899_RCOMPC		, 0xc9 पूर्ण,
	अणु STB0899_AGC1CN		, 0x41 पूर्ण,
	अणु STB0899_AGC1REF		, 0x08 पूर्ण,
	अणु STB0899_RTC			, 0x7a पूर्ण,
	अणु STB0899_TMGCFG		, 0x4e पूर्ण,
	अणु STB0899_AGC2REF		, 0x33 पूर्ण,
	अणु STB0899_TLSR			, 0x84 पूर्ण,
	अणु STB0899_CFD			, 0xee पूर्ण,
	अणु STB0899_ACLC			, 0x87 पूर्ण,
	अणु STB0899_BCLC			, 0x94 पूर्ण,
	अणु STB0899_EQON			, 0x41 पूर्ण,
	अणु STB0899_LDT			, 0xdd पूर्ण,
	अणु STB0899_LDT2			, 0xc9 पूर्ण,
	अणु STB0899_EQUALREF		, 0xb4 पूर्ण,
	अणु STB0899_TMGRAMP		, 0x10 पूर्ण,
	अणु STB0899_TMGTHD		, 0x30 पूर्ण,
	अणु STB0899_IDCCOMP		, 0xfb पूर्ण,
	अणु STB0899_QDCCOMP		, 0x03 पूर्ण,
	अणु STB0899_POWERI		, 0x3b पूर्ण,
	अणु STB0899_POWERQ		, 0x3d पूर्ण,
	अणु STB0899_RCOMP			, 0x81 पूर्ण,
	अणु STB0899_AGCIQIN		, 0x80 पूर्ण,
	अणु STB0899_AGC2I1		, 0x04 पूर्ण,
	अणु STB0899_AGC2I2		, 0xf5 पूर्ण,
	अणु STB0899_TLIR			, 0x25 पूर्ण,
	अणु STB0899_RTF			, 0x80 पूर्ण,
	अणु STB0899_DSTATUS		, 0x00 पूर्ण,
	अणु STB0899_LDI			, 0xca पूर्ण,
	अणु STB0899_CFRM			, 0xf1 पूर्ण,
	अणु STB0899_CFRL			, 0xf3 पूर्ण,
	अणु STB0899_NIRM			, 0x2a पूर्ण,
	अणु STB0899_NIRL			, 0x05 पूर्ण,
	अणु STB0899_ISYMB			, 0x17 पूर्ण,
	अणु STB0899_QSYMB			, 0xfa पूर्ण,
	अणु STB0899_SFRH			, 0x2f पूर्ण,
	अणु STB0899_SFRM			, 0x68 पूर्ण,
	अणु STB0899_SFRL			, 0x40 पूर्ण,
	अणु STB0899_SFRUPH		, 0x2f पूर्ण,
	अणु STB0899_SFRUPM		, 0x68 पूर्ण,
	अणु STB0899_SFRUPL		, 0x40 पूर्ण,
	अणु STB0899_EQUAI1		, 0xfd पूर्ण,
	अणु STB0899_EQUAQ1		, 0x04 पूर्ण,
	अणु STB0899_EQUAI2		, 0x0f पूर्ण,
	अणु STB0899_EQUAQ2		, 0xff पूर्ण,
	अणु STB0899_EQUAI3		, 0xdf पूर्ण,
	अणु STB0899_EQUAQ3		, 0xfa पूर्ण,
	अणु STB0899_EQUAI4		, 0x37 पूर्ण,
	अणु STB0899_EQUAQ4		, 0x0d पूर्ण,
	अणु STB0899_EQUAI5		, 0xbd पूर्ण,
	अणु STB0899_EQUAQ5		, 0xf7 पूर्ण,
	अणु STB0899_DSTATUS2		, 0x00 पूर्ण,
	अणु STB0899_VSTATUS		, 0x00 पूर्ण,
	अणु STB0899_VERROR		, 0xff पूर्ण,
	अणु STB0899_IQSWAP		, 0x2a पूर्ण,
	अणु STB0899_ECNT1M		, 0x00 पूर्ण,
	अणु STB0899_ECNT1L		, 0x00 पूर्ण,
	अणु STB0899_ECNT2M		, 0x00 पूर्ण,
	अणु STB0899_ECNT2L		, 0x00 पूर्ण,
	अणु STB0899_ECNT3M		, 0x00 पूर्ण,
	अणु STB0899_ECNT3L		, 0x00 पूर्ण,
	अणु STB0899_FECAUTO1		, 0x06 पूर्ण,
	अणु STB0899_FECM			, 0x01 पूर्ण,
	अणु STB0899_VTH12			, 0xf0 पूर्ण,
	अणु STB0899_VTH23			, 0xa0 पूर्ण,
	अणु STB0899_VTH34			, 0x78 पूर्ण,
	अणु STB0899_VTH56			, 0x4e पूर्ण,
	अणु STB0899_VTH67			, 0x48 पूर्ण,
	अणु STB0899_VTH78			, 0x38 पूर्ण,
	अणु STB0899_PRVIT			, 0xff पूर्ण,
	अणु STB0899_VITSYNC		, 0x19 पूर्ण,
	अणु STB0899_RSULC			, 0xb1 पूर्ण, /* DVB = 0xb1, DSS = 0xa1 */
	अणु STB0899_TSULC			, 0x42 पूर्ण,
	अणु STB0899_RSLLC			, 0x40 पूर्ण,
	अणु STB0899_TSLPL			, 0x12 पूर्ण,
	अणु STB0899_TSCFGH		, 0x0c पूर्ण,
	अणु STB0899_TSCFGM		, 0x00 पूर्ण,
	अणु STB0899_TSCFGL		, 0x0c पूर्ण,
	अणु STB0899_TSOUT			, 0x4d पूर्ण, /* 0x0d क्रम CAM */
	अणु STB0899_RSSYNCDEL		, 0x00 पूर्ण,
	अणु STB0899_TSINHDELH		, 0x02 पूर्ण,
	अणु STB0899_TSINHDELM		, 0x00 पूर्ण,
	अणु STB0899_TSINHDELL		, 0x00 पूर्ण,
	अणु STB0899_TSLLSTKM		, 0x00 पूर्ण,
	अणु STB0899_TSLLSTKL		, 0x00 पूर्ण,
	अणु STB0899_TSULSTKM		, 0x00 पूर्ण,
	अणु STB0899_TSULSTKL		, 0xab पूर्ण,
	अणु STB0899_PCKLENUL		, 0x00 पूर्ण,
	अणु STB0899_PCKLENLL		, 0xcc पूर्ण,
	अणु STB0899_RSPCKLEN		, 0xcc पूर्ण,
	अणु STB0899_TSSTATUS		, 0x80 पूर्ण,
	अणु STB0899_ERRCTRL1		, 0xb6 पूर्ण,
	अणु STB0899_ERRCTRL2		, 0x96 पूर्ण,
	अणु STB0899_ERRCTRL3		, 0x89 पूर्ण,
	अणु STB0899_DMONMSK1		, 0x27 पूर्ण,
	अणु STB0899_DMONMSK0		, 0x03 पूर्ण,
	अणु STB0899_DEMAPVIT		, 0x5c पूर्ण,
	अणु STB0899_PLPARM		, 0x1f पूर्ण,
	अणु STB0899_PDELCTRL		, 0x48 पूर्ण,
	अणु STB0899_PDELCTRL2		, 0x00 पूर्ण,
	अणु STB0899_BBHCTRL1		, 0x00 पूर्ण,
	अणु STB0899_BBHCTRL2		, 0x00 पूर्ण,
	अणु STB0899_HYSTTHRESH		, 0x77 पूर्ण,
	अणु STB0899_MATCSTM		, 0x00 पूर्ण,
	अणु STB0899_MATCSTL		, 0x00 पूर्ण,
	अणु STB0899_UPLCSTM		, 0x00 पूर्ण,
	अणु STB0899_UPLCSTL		, 0x00 पूर्ण,
	अणु STB0899_DFLCSTM		, 0x00 पूर्ण,
	अणु STB0899_DFLCSTL		, 0x00 पूर्ण,
	अणु STB0899_SYNCCST		, 0x00 पूर्ण,
	अणु STB0899_SYNCDCSTM		, 0x00 पूर्ण,
	अणु STB0899_SYNCDCSTL		, 0x00 पूर्ण,
	अणु STB0899_ISI_ENTRY		, 0x00 पूर्ण,
	अणु STB0899_ISI_BIT_EN		, 0x00 पूर्ण,
	अणु STB0899_MATSTRM		, 0x00 पूर्ण,
	अणु STB0899_MATSTRL		, 0x00 पूर्ण,
	अणु STB0899_UPLSTRM		, 0x00 पूर्ण,
	अणु STB0899_UPLSTRL		, 0x00 पूर्ण,
	अणु STB0899_DFLSTRM		, 0x00 पूर्ण,
	अणु STB0899_DFLSTRL		, 0x00 पूर्ण,
	अणु STB0899_SYNCSTR		, 0x00 पूर्ण,
	अणु STB0899_SYNCDSTRM		, 0x00 पूर्ण,
	अणु STB0899_SYNCDSTRL		, 0x00 पूर्ण,
	अणु STB0899_CFGPDELSTATUS1	, 0x10 पूर्ण,
	अणु STB0899_CFGPDELSTATUS2	, 0x00 पूर्ण,
	अणु STB0899_BBFERRORM		, 0x00 पूर्ण,
	अणु STB0899_BBFERRORL		, 0x00 पूर्ण,
	अणु STB0899_UPKTERRORM		, 0x00 पूर्ण,
	अणु STB0899_UPKTERRORL		, 0x00 पूर्ण,
	अणु 0xffff			, 0xff पूर्ण,
पूर्ण;

/* STB0899 demodulator config क्रम the KNC1 and clones */
अटल काष्ठा stb0899_config knc1_dvbs2_config = अणु
	.init_dev		= knc1_stb0899_s1_init_1,
	.init_s2_demod		= stb0899_s2_init_2,
	.init_s1_demod		= knc1_stb0899_s1_init_3,
	.init_s2_fec		= stb0899_s2_init_4,
	.init_tst		= stb0899_s1_init_5,

	.postproc		= शून्य,

	.demod_address		= 0x68,
//	.ts_output_mode		= STB0899_OUT_PARALLEL,	/* types = SERIAL/PARALLEL	*/
	.block_sync_mode	= STB0899_SYNC_FORCED,	/* DSS, SYNC_FORCED/UNSYNCED	*/
//	.ts_pfbit_toggle	= STB0899_MPEG_NORMAL,	/* DirecTV, MPEG toggling seq	*/

	.xtal_freq		= 27000000,
	.inversion		= IQ_SWAP_OFF,

	.lo_clk			= 76500000,
	.hi_clk			= 90000000,

	.esno_ave		= STB0899_DVBS2_ESNO_AVE,
	.esno_quant		= STB0899_DVBS2_ESNO_QUANT,
	.avframes_coarse	= STB0899_DVBS2_AVFRAMES_COARSE,
	.avframes_fine		= STB0899_DVBS2_AVFRAMES_FINE,
	.miss_threshold		= STB0899_DVBS2_MISS_THRESHOLD,
	.uwp_threshold_acq	= STB0899_DVBS2_UWP_THRESHOLD_ACQ,
	.uwp_threshold_track	= STB0899_DVBS2_UWP_THRESHOLD_TRACK,
	.uwp_threshold_sof	= STB0899_DVBS2_UWP_THRESHOLD_SOF,
	.sof_search_समयout	= STB0899_DVBS2_SOF_SEARCH_TIMEOUT,

	.btr_nco_bits		= STB0899_DVBS2_BTR_NCO_BITS,
	.btr_gain_shअगरt_offset	= STB0899_DVBS2_BTR_GAIN_SHIFT_OFFSET,
	.crl_nco_bits		= STB0899_DVBS2_CRL_NCO_BITS,
	.ldpc_max_iter		= STB0899_DVBS2_LDPC_MAX_ITER,

	.tuner_get_frequency	= tda8261_get_frequency,
	.tuner_set_frequency	= tda8261_set_frequency,
	.tuner_set_bandwidth	= शून्य,
	.tuner_get_bandwidth	= tda8261_get_bandwidth,
	.tuner_set_rfsiggain	= शून्य
पूर्ण;

/*
 * SD1878/SHA tuner config
 * 1F, Single I/P, Horizontal mount, High Sensitivity
 */
अटल स्थिर काष्ठा tda8261_config sd1878c_config = अणु
//	.name		= "SD1878/SHA",
	.addr		= 0x60,
	.step_size	= TDA8261_STEP_1000 /* kHz */
पूर्ण;

अटल u8 पढ़ो_pwm(काष्ठा budget_av *budget_av)
अणु
	u8 b = 0xff;
	u8 pwm;
	काष्ठा i2c_msg msg[] = अणु अणु.addr = 0x50,.flags = 0,.buf = &b,.len = 1पूर्ण,
	अणु.addr = 0x50,.flags = I2C_M_RD,.buf = &pwm,.len = 1पूर्ण
	पूर्ण;

	अगर ((i2c_transfer(&budget_av->budget.i2c_adap, msg, 2) != 2)
	    || (pwm == 0xff))
		pwm = 0x48;

	वापस pwm;
पूर्ण

#घोषणा SUBID_DVBS_KNC1			0x0010
#घोषणा SUBID_DVBS_KNC1_PLUS		0x0011
#घोषणा SUBID_DVBS_TYPHOON		0x4f56
#घोषणा SUBID_DVBS_CINERGY1200		0x1154
#घोषणा SUBID_DVBS_CYNERGY1200N		0x1155
#घोषणा SUBID_DVBS_TV_STAR		0x0014
#घोषणा SUBID_DVBS_TV_STAR_PLUS_X4	0x0015
#घोषणा SUBID_DVBS_TV_STAR_CI		0x0016
#घोषणा SUBID_DVBS2_KNC1		0x0018
#घोषणा SUBID_DVBS2_KNC1_OEM		0x0019
#घोषणा SUBID_DVBS_EASYWATCH_1		0x001a
#घोषणा SUBID_DVBS_EASYWATCH_2		0x001b
#घोषणा SUBID_DVBS2_EASYWATCH		0x001d
#घोषणा SUBID_DVBS_EASYWATCH		0x001e

#घोषणा SUBID_DVBC_EASYWATCH		0x002a
#घोषणा SUBID_DVBC_EASYWATCH_MK3	0x002c
#घोषणा SUBID_DVBC_KNC1			0x0020
#घोषणा SUBID_DVBC_KNC1_PLUS		0x0021
#घोषणा SUBID_DVBC_KNC1_MK3		0x0022
#घोषणा SUBID_DVBC_KNC1_TDA10024	0x0028
#घोषणा SUBID_DVBC_KNC1_PLUS_MK3	0x0023
#घोषणा SUBID_DVBC_CINERGY1200		0x1156
#घोषणा SUBID_DVBC_CINERGY1200_MK3	0x1176

#घोषणा SUBID_DVBT_EASYWATCH		0x003a
#घोषणा SUBID_DVBT_KNC1_PLUS		0x0031
#घोषणा SUBID_DVBT_KNC1			0x0030
#घोषणा SUBID_DVBT_CINERGY1200		0x1157

अटल व्योम frontend_init(काष्ठा budget_av *budget_av)
अणु
	काष्ठा saa7146_dev * saa = budget_av->budget.dev;
	काष्ठा dvb_frontend * fe = शून्य;

	/* Enable / PowerON Frontend */
	saa7146_setgpio(saa, 0, SAA7146_GPIO_OUTLO);

	/* Wait क्रम PowerON */
	msleep(100);

	/* additional setup necessary क्रम the PLUS cards */
	चयन (saa->pci->subप्रणाली_device) अणु
		हाल SUBID_DVBS_KNC1_PLUS:
		हाल SUBID_DVBC_KNC1_PLUS:
		हाल SUBID_DVBT_KNC1_PLUS:
		हाल SUBID_DVBC_EASYWATCH:
		हाल SUBID_DVBC_KNC1_PLUS_MK3:
		हाल SUBID_DVBS2_KNC1:
		हाल SUBID_DVBS2_KNC1_OEM:
		हाल SUBID_DVBS2_EASYWATCH:
			saa7146_setgpio(saa, 3, SAA7146_GPIO_OUTHI);
			अवरोध;
	पूर्ण

	चयन (saa->pci->subप्रणाली_device) अणु

	हाल SUBID_DVBS_KNC1:
		/*
		 * maybe that setting is needed क्रम other dvb-s cards as well,
		 * but so far it has been only confirmed क्रम this type
		 */
		budget_av->reinitialise_demod = 1;
		fallthrough;
	हाल SUBID_DVBS_KNC1_PLUS:
	हाल SUBID_DVBS_EASYWATCH_1:
		अगर (saa->pci->subप्रणाली_venकरोr == 0x1894) अणु
			fe = dvb_attach(stv0299_attach, &cinergy_1200s_1894_0010_config,
					     &budget_av->budget.i2c_adap);
			अगर (fe) अणु
				dvb_attach(tua6100_attach, fe, 0x60, &budget_av->budget.i2c_adap);
			पूर्ण
		पूर्ण अन्यथा अणु
			fe = dvb_attach(stv0299_attach, &typhoon_config,
					     &budget_av->budget.i2c_adap);
			अगर (fe) अणु
				fe->ops.tuner_ops.set_params = philips_su1278_ty_ci_tuner_set_params;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल SUBID_DVBS_TV_STAR:
	हाल SUBID_DVBS_TV_STAR_PLUS_X4:
	हाल SUBID_DVBS_TV_STAR_CI:
	हाल SUBID_DVBS_CYNERGY1200N:
	हाल SUBID_DVBS_EASYWATCH:
	हाल SUBID_DVBS_EASYWATCH_2:
		fe = dvb_attach(stv0299_attach, &philips_sd1878_config,
				&budget_av->budget.i2c_adap);
		अगर (fe) अणु
			dvb_attach(dvb_pll_attach, fe, 0x60,
				   &budget_av->budget.i2c_adap,
				   DVB_PLL_PHILIPS_SD1878_TDA8261);
		पूर्ण
		अवरोध;

	हाल SUBID_DVBS_TYPHOON:
		fe = dvb_attach(stv0299_attach, &typhoon_config,
				    &budget_av->budget.i2c_adap);
		अगर (fe) अणु
			fe->ops.tuner_ops.set_params = philips_su1278_ty_ci_tuner_set_params;
		पूर्ण
		अवरोध;
	हाल SUBID_DVBS2_KNC1:
	हाल SUBID_DVBS2_KNC1_OEM:
	हाल SUBID_DVBS2_EASYWATCH:
		budget_av->reinitialise_demod = 1;
		अगर ((fe = dvb_attach(stb0899_attach, &knc1_dvbs2_config, &budget_av->budget.i2c_adap)))
			dvb_attach(tda8261_attach, fe, &sd1878c_config, &budget_av->budget.i2c_adap);

		अवरोध;
	हाल SUBID_DVBS_CINERGY1200:
		fe = dvb_attach(stv0299_attach, &cinergy_1200s_config,
				    &budget_av->budget.i2c_adap);
		अगर (fe) अणु
			fe->ops.tuner_ops.set_params = philips_su1278_ty_ci_tuner_set_params;
		पूर्ण
		अवरोध;

	हाल SUBID_DVBC_KNC1:
	हाल SUBID_DVBC_KNC1_PLUS:
	हाल SUBID_DVBC_CINERGY1200:
	हाल SUBID_DVBC_EASYWATCH:
		budget_av->reinitialise_demod = 1;
		budget_av->budget.dev->i2c_bitrate = SAA7146_I2C_BUS_BIT_RATE_240;
		fe = dvb_attach(tda10021_attach, &philips_cu1216_config,
				     &budget_av->budget.i2c_adap,
				     पढ़ो_pwm(budget_av));
		अगर (fe == शून्य)
			fe = dvb_attach(tda10021_attach, &philips_cu1216_config_altaddress,
					     &budget_av->budget.i2c_adap,
					     पढ़ो_pwm(budget_av));
		अगर (fe) अणु
			fe->ops.tuner_ops.set_params = philips_cu1216_tuner_set_params;
		पूर्ण
		अवरोध;

	हाल SUBID_DVBC_EASYWATCH_MK3:
	हाल SUBID_DVBC_CINERGY1200_MK3:
	हाल SUBID_DVBC_KNC1_MK3:
	हाल SUBID_DVBC_KNC1_TDA10024:
	हाल SUBID_DVBC_KNC1_PLUS_MK3:
		budget_av->reinitialise_demod = 1;
		budget_av->budget.dev->i2c_bitrate = SAA7146_I2C_BUS_BIT_RATE_240;
		fe = dvb_attach(tda10023_attach,
			&philips_cu1216_tda10023_config,
			&budget_av->budget.i2c_adap,
			पढ़ो_pwm(budget_av));
		अगर (fe) अणु
			fe->ops.tuner_ops.set_params = philips_cu1216_tuner_set_params;
		पूर्ण
		अवरोध;

	हाल SUBID_DVBT_EASYWATCH:
	हाल SUBID_DVBT_KNC1:
	हाल SUBID_DVBT_KNC1_PLUS:
	हाल SUBID_DVBT_CINERGY1200:
		budget_av->reinitialise_demod = 1;
		fe = dvb_attach(tda10046_attach, &philips_tu1216_config,
				     &budget_av->budget.i2c_adap);
		अगर (fe) अणु
			fe->ops.tuner_ops.init = philips_tu1216_tuner_init;
			fe->ops.tuner_ops.set_params = philips_tu1216_tuner_set_params;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (fe == शून्य) अणु
		pr_err("A frontend driver was not found for device [%04x:%04x] subsystem [%04x:%04x]\n",
		       saa->pci->venकरोr,
		       saa->pci->device,
		       saa->pci->subप्रणाली_venकरोr,
		       saa->pci->subप्रणाली_device);
		वापस;
	पूर्ण

	budget_av->budget.dvb_frontend = fe;

	अगर (dvb_रेजिस्टर_frontend(&budget_av->budget.dvb_adapter,
				  budget_av->budget.dvb_frontend)) अणु
		pr_err("Frontend registration failed!\n");
		dvb_frontend_detach(budget_av->budget.dvb_frontend);
		budget_av->budget.dvb_frontend = शून्य;
	पूर्ण
पूर्ण


अटल व्योम budget_av_irq(काष्ठा saa7146_dev *dev, u32 * isr)
अणु
	काष्ठा budget_av *budget_av = (काष्ठा budget_av *) dev->ext_priv;

	dprपूर्णांकk(8, "dev: %p, budget_av: %p\n", dev, budget_av);

	अगर (*isr & MASK_10)
		ttpci_budget_irq10_handler(dev, isr);
पूर्ण

अटल पूर्णांक budget_av_detach(काष्ठा saa7146_dev *dev)
अणु
	काष्ठा budget_av *budget_av = (काष्ठा budget_av *) dev->ext_priv;
	पूर्णांक err;

	dprपूर्णांकk(2, "dev: %p\n", dev);

	अगर (1 == budget_av->has_saa7113) अणु
		saa7146_setgpio(dev, 0, SAA7146_GPIO_OUTLO);

		msleep(200);

		saa7146_unरेजिस्टर_device(&budget_av->vd, dev);

		saa7146_vv_release(dev);
	पूर्ण

	अगर (budget_av->budget.ci_present)
		ciपूर्णांकf_deinit(budget_av);

	अगर (budget_av->budget.dvb_frontend != शून्य) अणु
		dvb_unरेजिस्टर_frontend(budget_av->budget.dvb_frontend);
		dvb_frontend_detach(budget_av->budget.dvb_frontend);
	पूर्ण
	err = ttpci_budget_deinit(&budget_av->budget);

	kमुक्त(budget_av);

	वापस err;
पूर्ण

#घोषणा KNC1_INPUTS 2
अटल काष्ठा v4l2_input knc1_inमाला_दो[KNC1_INPUTS] = अणु
	अणु 0, "Composite", V4L2_INPUT_TYPE_TUNER, 1, 0,
		V4L2_STD_PAL_BG | V4L2_STD_NTSC_M, 0, V4L2_IN_CAP_STD पूर्ण,
	अणु 1, "S-Video", V4L2_INPUT_TYPE_CAMERA, 2, 0,
		V4L2_STD_PAL_BG | V4L2_STD_NTSC_M, 0, V4L2_IN_CAP_STD पूर्ण,
पूर्ण;

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_input *i)
अणु
	dprपूर्णांकk(1, "VIDIOC_ENUMINPUT %d\n", i->index);
	अगर (i->index >= KNC1_INPUTS)
		वापस -EINVAL;
	स_नकल(i, &knc1_inमाला_दो[i->index], माप(काष्ठा v4l2_input));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा budget_av *budget_av = (काष्ठा budget_av *)dev->ext_priv;

	*i = budget_av->cur_input;

	dprपूर्णांकk(1, "VIDIOC_G_INPUT %d\n", *i);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक input)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा budget_av *budget_av = (काष्ठा budget_av *)dev->ext_priv;

	dprपूर्णांकk(1, "VIDIOC_S_INPUT %d\n", input);
	वापस saa7113_setinput(budget_av, input);
पूर्ण

अटल काष्ठा saa7146_ext_vv vv_data;

अटल पूर्णांक budget_av_attach(काष्ठा saa7146_dev *dev, काष्ठा saa7146_pci_extension_data *info)
अणु
	काष्ठा budget_av *budget_av;
	u8 *mac;
	पूर्णांक err;

	dprपूर्णांकk(2, "dev: %p\n", dev);

	अगर (!(budget_av = kzalloc(माप(काष्ठा budget_av), GFP_KERNEL)))
		वापस -ENOMEM;

	budget_av->has_saa7113 = 0;
	budget_av->budget.ci_present = 0;

	dev->ext_priv = budget_av;

	err = ttpci_budget_init(&budget_av->budget, dev, info, THIS_MODULE,
				adapter_nr);
	अगर (err) अणु
		kमुक्त(budget_av);
		वापस err;
	पूर्ण

	/* knc1 initialization */
	saa7146_ग_लिखो(dev, DD1_STREAM_B, 0x04000000);
	saa7146_ग_लिखो(dev, DD1_INIT, 0x07000600);
	saa7146_ग_लिखो(dev, MC2, MASK_09 | MASK_25 | MASK_10 | MASK_26);

	अगर (saa7113_init(budget_av) == 0) अणु
		budget_av->has_saa7113 = 1;
		err = saa7146_vv_init(dev, &vv_data);
		अगर (err != 0) अणु
			/* fixme: proper cleanup here */
			ERR("cannot init vv subsystem\n");
			वापस err;
		पूर्ण
		vv_data.vid_ops.vidioc_क्रमागत_input = vidioc_क्रमागत_input;
		vv_data.vid_ops.vidioc_g_input = vidioc_g_input;
		vv_data.vid_ops.vidioc_s_input = vidioc_s_input;

		अगर ((err = saa7146_रेजिस्टर_device(&budget_av->vd, dev, "knc1", VFL_TYPE_VIDEO))) अणु
			/* fixme: proper cleanup here */
			ERR("cannot register capture v4l2 device\n");
			saa7146_vv_release(dev);
			वापस err;
		पूर्ण

		/* beware: this modअगरies dev->vv ... */
		saa7146_set_hps_source_and_sync(dev, SAA7146_HPS_SOURCE_PORT_A,
						SAA7146_HPS_SYNC_PORT_A);

		saa7113_setinput(budget_av, 0);
	पूर्ण

	/* fixme: find some sane values here... */
	saa7146_ग_लिखो(dev, PCI_BT_V1, 0x1c00101f);

	mac = budget_av->budget.dvb_adapter.proposed_mac;
	अगर (i2c_पढ़ोregs(&budget_av->budget.i2c_adap, 0xa0, 0x30, mac, 6)) अणु
		pr_err("KNC1-%d: Could not read MAC from KNC1 card\n",
		       budget_av->budget.dvb_adapter.num);
		eth_zero_addr(mac);
	पूर्ण अन्यथा अणु
		pr_info("KNC1-%d: MAC addr = %pM\n",
			budget_av->budget.dvb_adapter.num, mac);
	पूर्ण

	budget_av->budget.dvb_adapter.priv = budget_av;
	frontend_init(budget_av);
	ciपूर्णांकf_init(budget_av);

	ttpci_budget_init_hooks(&budget_av->budget);

	वापस 0;
पूर्ण

अटल काष्ठा saa7146_standard standard[] = अणु
	अणु.name = "PAL",.id = V4L2_STD_PAL,
	 .v_offset = 0x17,.v_field = 288,
	 .h_offset = 0x14,.h_pixels = 680,
	 .v_max_out = 576,.h_max_out = 768 पूर्ण,

	अणु.name = "NTSC",.id = V4L2_STD_NTSC,
	 .v_offset = 0x16,.v_field = 240,
	 .h_offset = 0x06,.h_pixels = 708,
	 .v_max_out = 480,.h_max_out = 640, पूर्ण,
पूर्ण;

अटल काष्ठा saa7146_ext_vv vv_data = अणु
	.inमाला_दो = 2,
	.capabilities = 0,	// perhaps later: V4L2_CAP_VBI_CAPTURE, but that need tweaking with the saa7113
	.flags = 0,
	.stds = &standard[0],
	.num_stds = ARRAY_SIZE(standard),
पूर्ण;

अटल काष्ठा saa7146_extension budget_extension;

MAKE_BUDGET_INFO(knc1s, "KNC1 DVB-S", BUDGET_KNC1S);
MAKE_BUDGET_INFO(knc1s2,"KNC1 DVB-S2", BUDGET_KNC1S2);
MAKE_BUDGET_INFO(sates2,"Satelco EasyWatch DVB-S2", BUDGET_KNC1S2);
MAKE_BUDGET_INFO(knc1c, "KNC1 DVB-C", BUDGET_KNC1C);
MAKE_BUDGET_INFO(knc1t, "KNC1 DVB-T", BUDGET_KNC1T);
MAKE_BUDGET_INFO(kncxs, "KNC TV STAR DVB-S", BUDGET_TVSTAR);
MAKE_BUDGET_INFO(satewpls, "Satelco EasyWatch DVB-S light", BUDGET_TVSTAR);
MAKE_BUDGET_INFO(satewpls1, "Satelco EasyWatch DVB-S light", BUDGET_KNC1S);
MAKE_BUDGET_INFO(satewps, "Satelco EasyWatch DVB-S", BUDGET_KNC1S);
MAKE_BUDGET_INFO(satewplc, "Satelco EasyWatch DVB-C", BUDGET_KNC1CP);
MAKE_BUDGET_INFO(satewcmk3, "Satelco EasyWatch DVB-C MK3", BUDGET_KNC1C_MK3);
MAKE_BUDGET_INFO(satewt, "Satelco EasyWatch DVB-T", BUDGET_KNC1T);
MAKE_BUDGET_INFO(knc1sp, "KNC1 DVB-S Plus", BUDGET_KNC1SP);
MAKE_BUDGET_INFO(knc1spx4, "KNC1 DVB-S Plus X4", BUDGET_KNC1SP);
MAKE_BUDGET_INFO(knc1cp, "KNC1 DVB-C Plus", BUDGET_KNC1CP);
MAKE_BUDGET_INFO(knc1cmk3, "KNC1 DVB-C MK3", BUDGET_KNC1C_MK3);
MAKE_BUDGET_INFO(knc1ctda10024, "KNC1 DVB-C TDA10024", BUDGET_KNC1C_TDA10024);
MAKE_BUDGET_INFO(knc1cpmk3, "KNC1 DVB-C Plus MK3", BUDGET_KNC1CP_MK3);
MAKE_BUDGET_INFO(knc1tp, "KNC1 DVB-T Plus", BUDGET_KNC1TP);
MAKE_BUDGET_INFO(cin1200s, "TerraTec Cinergy 1200 DVB-S", BUDGET_CIN1200S);
MAKE_BUDGET_INFO(cin1200sn, "TerraTec Cinergy 1200 DVB-S", BUDGET_CIN1200S);
MAKE_BUDGET_INFO(cin1200c, "Terratec Cinergy 1200 DVB-C", BUDGET_CIN1200C);
MAKE_BUDGET_INFO(cin1200cmk3, "Terratec Cinergy 1200 DVB-C MK3", BUDGET_CIN1200C_MK3);
MAKE_BUDGET_INFO(cin1200t, "Terratec Cinergy 1200 DVB-T", BUDGET_CIN1200T);

अटल स्थिर काष्ठा pci_device_id pci_tbl[] = अणु
	MAKE_EXTENSION_PCI(knc1s, 0x1131, 0x4f56),
	MAKE_EXTENSION_PCI(knc1s, 0x1131, 0x0010),
	MAKE_EXTENSION_PCI(knc1s, 0x1894, 0x0010),
	MAKE_EXTENSION_PCI(knc1sp, 0x1131, 0x0011),
	MAKE_EXTENSION_PCI(knc1sp, 0x1894, 0x0011),
	MAKE_EXTENSION_PCI(kncxs, 0x1894, 0x0014),
	MAKE_EXTENSION_PCI(knc1spx4, 0x1894, 0x0015),
	MAKE_EXTENSION_PCI(kncxs, 0x1894, 0x0016),
	MAKE_EXTENSION_PCI(knc1s2, 0x1894, 0x0018),
	MAKE_EXTENSION_PCI(knc1s2, 0x1894, 0x0019),
	MAKE_EXTENSION_PCI(sates2, 0x1894, 0x001d),
	MAKE_EXTENSION_PCI(satewpls, 0x1894, 0x001e),
	MAKE_EXTENSION_PCI(satewpls1, 0x1894, 0x001a),
	MAKE_EXTENSION_PCI(satewps, 0x1894, 0x001b),
	MAKE_EXTENSION_PCI(satewplc, 0x1894, 0x002a),
	MAKE_EXTENSION_PCI(satewcmk3, 0x1894, 0x002c),
	MAKE_EXTENSION_PCI(satewt, 0x1894, 0x003a),
	MAKE_EXTENSION_PCI(knc1c, 0x1894, 0x0020),
	MAKE_EXTENSION_PCI(knc1cp, 0x1894, 0x0021),
	MAKE_EXTENSION_PCI(knc1cmk3, 0x1894, 0x0022),
	MAKE_EXTENSION_PCI(knc1ctda10024, 0x1894, 0x0028),
	MAKE_EXTENSION_PCI(knc1cpmk3, 0x1894, 0x0023),
	MAKE_EXTENSION_PCI(knc1t, 0x1894, 0x0030),
	MAKE_EXTENSION_PCI(knc1tp, 0x1894, 0x0031),
	MAKE_EXTENSION_PCI(cin1200s, 0x153b, 0x1154),
	MAKE_EXTENSION_PCI(cin1200sn, 0x153b, 0x1155),
	MAKE_EXTENSION_PCI(cin1200c, 0x153b, 0x1156),
	MAKE_EXTENSION_PCI(cin1200cmk3, 0x153b, 0x1176),
	MAKE_EXTENSION_PCI(cin1200t, 0x153b, 0x1157),
	अणु
	 .venकरोr = 0,
	पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pci_tbl);

अटल काष्ठा saa7146_extension budget_extension = अणु
	.name = "budget_av",
	.flags = SAA7146_USE_I2C_IRQ,

	.pci_tbl = pci_tbl,

	.module = THIS_MODULE,
	.attach = budget_av_attach,
	.detach = budget_av_detach,

	.irq_mask = MASK_10,
	.irq_func = budget_av_irq,
पूर्ण;

अटल पूर्णांक __init budget_av_init(व्योम)
अणु
	वापस saa7146_रेजिस्टर_extension(&budget_extension);
पूर्ण

अटल व्योम __निकास budget_av_निकास(व्योम)
अणु
	saa7146_unरेजिस्टर_extension(&budget_extension);
पूर्ण

module_init(budget_av_init);
module_निकास(budget_av_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ralph Metzler, Marcus Metzler, Michael Hunold, others");
MODULE_DESCRIPTION("driver for the SAA7146 based so-called budget PCI DVB w/ analog input and CI-module (e.g. the KNC cards)");
