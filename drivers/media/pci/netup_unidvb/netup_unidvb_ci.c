<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * netup_unidvb_ci.c
 *
 * DVB CAM support क्रम NetUP Universal Dual DVB-CI
 *
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Sergey Kozlov <serjk@netup.ru>
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kmod.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश "netup_unidvb.h"

/* CI slot 0 base address */
#घोषणा CAM0_CONFIG		0x0
#घोषणा CAM0_IO			0x8000
#घोषणा CAM0_MEM		0x10000
#घोषणा CAM0_SZ			32
/* CI slot 1 base address */
#घोषणा CAM1_CONFIG		0x20000
#घोषणा CAM1_IO			0x28000
#घोषणा CAM1_MEM		0x30000
#घोषणा CAM1_SZ			32
/* ctrlstat रेजिस्टरs */
#घोषणा CAM_CTRLSTAT_READ_SET	0x4980
#घोषणा CAM_CTRLSTAT_CLR	0x4982
/* रेजिस्टर bits */
#घोषणा BIT_CAM_STCHG		(1<<0)
#घोषणा BIT_CAM_PRESENT		(1<<1)
#घोषणा BIT_CAM_RESET		(1<<2)
#घोषणा BIT_CAM_BYPASS		(1<<3)
#घोषणा BIT_CAM_READY		(1<<4)
#घोषणा BIT_CAM_ERROR		(1<<5)
#घोषणा BIT_CAM_OVERCURR	(1<<6)
/* BIT_CAM_BYPASS bit shअगरt क्रम SLOT 1 */
#घोषणा CAM1_SHIFT 8

irqवापस_t netup_ci_पूर्णांकerrupt(काष्ठा netup_unidvb_dev *ndev)
अणु
	ग_लिखोw(0x101, ndev->bmmio0 + CAM_CTRLSTAT_CLR);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक netup_unidvb_ci_slot_ts_ctl(काष्ठा dvb_ca_en50221 *en50221,
				       पूर्णांक slot)
अणु
	काष्ठा netup_ci_state *state = en50221->data;
	काष्ठा netup_unidvb_dev *dev = state->dev;
	u16 shअगरt = (state->nr == 1) ? CAM1_SHIFT : 0;

	dev_dbg(&dev->pci_dev->dev, "%s(): CAM_CTRLSTAT=0x%x\n",
		__func__, पढ़ोw(dev->bmmio0 + CAM_CTRLSTAT_READ_SET));
	अगर (slot != 0)
		वापस -EINVAL;
	/* pass data to CAM module */
	ग_लिखोw(BIT_CAM_BYPASS << shअगरt, dev->bmmio0 + CAM_CTRLSTAT_CLR);
	dev_dbg(&dev->pci_dev->dev, "%s(): CAM_CTRLSTAT=0x%x done\n",
		__func__, पढ़ोw(dev->bmmio0 + CAM_CTRLSTAT_READ_SET));
	वापस 0;
पूर्ण

अटल पूर्णांक netup_unidvb_ci_slot_shutकरोwn(काष्ठा dvb_ca_en50221 *en50221,
					 पूर्णांक slot)
अणु
	काष्ठा netup_ci_state *state = en50221->data;
	काष्ठा netup_unidvb_dev *dev = state->dev;

	dev_dbg(&dev->pci_dev->dev, "%s()\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक netup_unidvb_ci_slot_reset(काष्ठा dvb_ca_en50221 *en50221,
				      पूर्णांक slot)
अणु
	काष्ठा netup_ci_state *state = en50221->data;
	काष्ठा netup_unidvb_dev *dev = state->dev;
	अचिन्हित दीर्घ समयout = 0;
	u16 shअगरt = (state->nr == 1) ? CAM1_SHIFT : 0;
	u16 ci_stat = 0;
	पूर्णांक reset_counter = 3;

	dev_dbg(&dev->pci_dev->dev, "%s(): CAM_CTRLSTAT_READ_SET=0x%x\n",
		__func__, पढ़ोw(dev->bmmio0 + CAM_CTRLSTAT_READ_SET));
reset:
	समयout = jअगरfies + msecs_to_jअगरfies(5000);
	/* start reset */
	ग_लिखोw(BIT_CAM_RESET << shअगरt, dev->bmmio0 + CAM_CTRLSTAT_READ_SET);
	dev_dbg(&dev->pci_dev->dev, "%s(): waiting for reset\n", __func__);
	/* रुको until reset करोne */
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		ci_stat = पढ़ोw(dev->bmmio0 + CAM_CTRLSTAT_READ_SET);
		अगर (ci_stat & (BIT_CAM_READY << shअगरt))
			अवरोध;
		udelay(1000);
	पूर्ण
	अगर (!(ci_stat & (BIT_CAM_READY << shअगरt)) && reset_counter > 0) अणु
		dev_dbg(&dev->pci_dev->dev,
			"%s(): CAMP reset timeout! Will try again..\n",
			 __func__);
		reset_counter--;
		जाओ reset;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक netup_unidvb_poll_ci_slot_status(काष्ठा dvb_ca_en50221 *en50221,
					    पूर्णांक slot, पूर्णांक खोलो)
अणु
	काष्ठा netup_ci_state *state = en50221->data;
	काष्ठा netup_unidvb_dev *dev = state->dev;
	u16 shअगरt = (state->nr == 1) ? CAM1_SHIFT : 0;
	u16 ci_stat = 0;

	dev_dbg(&dev->pci_dev->dev, "%s(): CAM_CTRLSTAT_READ_SET=0x%x\n",
		__func__, पढ़ोw(dev->bmmio0 + CAM_CTRLSTAT_READ_SET));
	ci_stat = पढ़ोw(dev->bmmio0 + CAM_CTRLSTAT_READ_SET);
	अगर (ci_stat & (BIT_CAM_READY << shअगरt)) अणु
		state->status = DVB_CA_EN50221_POLL_CAM_PRESENT |
			DVB_CA_EN50221_POLL_CAM_READY;
	पूर्ण अन्यथा अगर (ci_stat & (BIT_CAM_PRESENT << shअगरt)) अणु
		state->status = DVB_CA_EN50221_POLL_CAM_PRESENT;
	पूर्ण अन्यथा अणु
		state->status = 0;
	पूर्ण
	वापस state->status;
पूर्ण

अटल पूर्णांक netup_unidvb_ci_पढ़ो_attribute_mem(काष्ठा dvb_ca_en50221 *en50221,
					      पूर्णांक slot, पूर्णांक addr)
अणु
	काष्ठा netup_ci_state *state = en50221->data;
	काष्ठा netup_unidvb_dev *dev = state->dev;
	u8 val = *((u8 __क्रमce *)state->membase8_config + addr);

	dev_dbg(&dev->pci_dev->dev,
		"%s(): addr=0x%x val=0x%x\n", __func__, addr, val);
	वापस val;
पूर्ण

अटल पूर्णांक netup_unidvb_ci_ग_लिखो_attribute_mem(काष्ठा dvb_ca_en50221 *en50221,
					       पूर्णांक slot, पूर्णांक addr, u8 data)
अणु
	काष्ठा netup_ci_state *state = en50221->data;
	काष्ठा netup_unidvb_dev *dev = state->dev;

	dev_dbg(&dev->pci_dev->dev,
		"%s(): addr=0x%x data=0x%x\n", __func__, addr, data);
	*((u8 __क्रमce *)state->membase8_config + addr) = data;
	वापस 0;
पूर्ण

अटल पूर्णांक netup_unidvb_ci_पढ़ो_cam_ctl(काष्ठा dvb_ca_en50221 *en50221,
					पूर्णांक slot, u8 addr)
अणु
	काष्ठा netup_ci_state *state = en50221->data;
	काष्ठा netup_unidvb_dev *dev = state->dev;
	u8 val = *((u8 __क्रमce *)state->membase8_io + addr);

	dev_dbg(&dev->pci_dev->dev,
		"%s(): addr=0x%x val=0x%x\n", __func__, addr, val);
	वापस val;
पूर्ण

अटल पूर्णांक netup_unidvb_ci_ग_लिखो_cam_ctl(काष्ठा dvb_ca_en50221 *en50221,
					 पूर्णांक slot, u8 addr, u8 data)
अणु
	काष्ठा netup_ci_state *state = en50221->data;
	काष्ठा netup_unidvb_dev *dev = state->dev;

	dev_dbg(&dev->pci_dev->dev,
		"%s(): addr=0x%x data=0x%x\n", __func__, addr, data);
	*((u8 __क्रमce *)state->membase8_io + addr) = data;
	वापस 0;
पूर्ण

पूर्णांक netup_unidvb_ci_रेजिस्टर(काष्ठा netup_unidvb_dev *dev,
			     पूर्णांक num, काष्ठा pci_dev *pci_dev)
अणु
	पूर्णांक result;
	काष्ठा netup_ci_state *state;

	अगर (num < 0 || num > 1) अणु
		dev_err(&pci_dev->dev, "%s(): invalid CI adapter %d\n",
			__func__, num);
		वापस -EINVAL;
	पूर्ण
	state = &dev->ci[num];
	state->nr = num;
	state->membase8_config = dev->bmmio1 +
		((num == 0) ? CAM0_CONFIG : CAM1_CONFIG);
	state->membase8_io = dev->bmmio1 +
		((num == 0) ? CAM0_IO : CAM1_IO);
	state->dev = dev;
	state->ca.owner = THIS_MODULE;
	state->ca.पढ़ो_attribute_mem = netup_unidvb_ci_पढ़ो_attribute_mem;
	state->ca.ग_लिखो_attribute_mem = netup_unidvb_ci_ग_लिखो_attribute_mem;
	state->ca.पढ़ो_cam_control = netup_unidvb_ci_पढ़ो_cam_ctl;
	state->ca.ग_लिखो_cam_control = netup_unidvb_ci_ग_लिखो_cam_ctl;
	state->ca.slot_reset = netup_unidvb_ci_slot_reset;
	state->ca.slot_shutकरोwn = netup_unidvb_ci_slot_shutकरोwn;
	state->ca.slot_ts_enable = netup_unidvb_ci_slot_ts_ctl;
	state->ca.poll_slot_status = netup_unidvb_poll_ci_slot_status;
	state->ca.data = state;
	result = dvb_ca_en50221_init(&dev->frontends[num].adapter,
		&state->ca, 0, 1);
	अगर (result < 0) अणु
		dev_err(&pci_dev->dev,
			"%s(): dvb_ca_en50221_init result %d\n",
			__func__, result);
		वापस result;
	पूर्ण
	ग_लिखोw(NETUP_UNIDVB_IRQ_CI, dev->bmmio0 + REG_IMASK_SET);
	dev_info(&pci_dev->dev,
		"%s(): CI adapter %d init done\n", __func__, num);
	वापस 0;
पूर्ण

व्योम netup_unidvb_ci_unरेजिस्टर(काष्ठा netup_unidvb_dev *dev, पूर्णांक num)
अणु
	काष्ठा netup_ci_state *state;

	dev_dbg(&dev->pci_dev->dev, "%s()\n", __func__);
	अगर (num < 0 || num > 1) अणु
		dev_err(&dev->pci_dev->dev, "%s(): invalid CI adapter %d\n",
				__func__, num);
		वापस;
	पूर्ण
	state = &dev->ci[num];
	dvb_ca_en50221_release(&state->ca);
पूर्ण

