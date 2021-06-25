<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vmk80xx.c
 * Velleman USB Board Low-Level Driver
 *
 * Copyright (C) 2009 Manuel Gebele <क्रमensixs@gmx.de>, Germany
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: vmk80xx
 * Description: Velleman USB Board Low-Level Driver
 * Devices: [Velleman] K8055 (K8055/VM110), K8061 (K8061/VM140),
 *   VM110 (K8055/VM110), VM140 (K8061/VM140)
 * Author: Manuel Gebele <क्रमensixs@gmx.de>
 * Updated: Sun, 10 May 2009 11:14:59 +0200
 * Status: works
 *
 * Supports:
 *  - analog input
 *  - analog output
 *  - digital input
 *  - digital output
 *  - counter
 *  - pwm
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/uaccess.h>

#समावेश "../comedi_usb.h"

क्रमागत अणु
	DEVICE_VMK8055,
	DEVICE_VMK8061
पूर्ण;

#घोषणा VMK8055_DI_REG		0x00
#घोषणा VMK8055_DO_REG		0x01
#घोषणा VMK8055_AO1_REG		0x02
#घोषणा VMK8055_AO2_REG		0x03
#घोषणा VMK8055_AI1_REG		0x02
#घोषणा VMK8055_AI2_REG		0x03
#घोषणा VMK8055_CNT1_REG	0x04
#घोषणा VMK8055_CNT2_REG	0x06

#घोषणा VMK8061_CH_REG		0x01
#घोषणा VMK8061_DI_REG		0x01
#घोषणा VMK8061_DO_REG		0x01
#घोषणा VMK8061_PWM_REG1	0x01
#घोषणा VMK8061_PWM_REG2	0x02
#घोषणा VMK8061_CNT_REG		0x02
#घोषणा VMK8061_AO_REG		0x02
#घोषणा VMK8061_AI_REG1		0x02
#घोषणा VMK8061_AI_REG2		0x03

#घोषणा VMK8055_CMD_RST		0x00
#घोषणा VMK8055_CMD_DEB1_TIME	0x01
#घोषणा VMK8055_CMD_DEB2_TIME	0x02
#घोषणा VMK8055_CMD_RST_CNT1	0x03
#घोषणा VMK8055_CMD_RST_CNT2	0x04
#घोषणा VMK8055_CMD_WRT_AD	0x05

#घोषणा VMK8061_CMD_RD_AI	0x00
#घोषणा VMK8061_CMR_RD_ALL_AI	0x01	/* !non-active! */
#घोषणा VMK8061_CMD_SET_AO	0x02
#घोषणा VMK8061_CMD_SET_ALL_AO	0x03	/* !non-active! */
#घोषणा VMK8061_CMD_OUT_PWM	0x04
#घोषणा VMK8061_CMD_RD_DI	0x05
#घोषणा VMK8061_CMD_DO		0x06	/* !non-active! */
#घोषणा VMK8061_CMD_CLR_DO	0x07
#घोषणा VMK8061_CMD_SET_DO	0x08
#घोषणा VMK8061_CMD_RD_CNT	0x09	/* TODO: completely poपूर्णांकless? */
#घोषणा VMK8061_CMD_RST_CNT	0x0a	/* TODO: completely poपूर्णांकless? */
#घोषणा VMK8061_CMD_RD_VERSION	0x0b	/* पूर्णांकernal usage */
#घोषणा VMK8061_CMD_RD_JMP_STAT	0x0c	/* TODO: not implemented yet */
#घोषणा VMK8061_CMD_RD_PWR_STAT	0x0d	/* पूर्णांकernal usage */
#घोषणा VMK8061_CMD_RD_DO	0x0e
#घोषणा VMK8061_CMD_RD_AO	0x0f
#घोषणा VMK8061_CMD_RD_PWM	0x10

#घोषणा IC3_VERSION		BIT(0)
#घोषणा IC6_VERSION		BIT(1)

क्रमागत vmk80xx_model अणु
	VMK8055_MODEL,
	VMK8061_MODEL
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange vmk8061_range = अणु
	2, अणु
		UNI_RANGE(5),
		UNI_RANGE(10)
	पूर्ण
पूर्ण;

काष्ठा vmk80xx_board अणु
	स्थिर अक्षर *name;
	क्रमागत vmk80xx_model model;
	स्थिर काष्ठा comedi_lrange *range;
	पूर्णांक ai_nchans;
	अचिन्हित पूर्णांक ai_maxdata;
	पूर्णांक ao_nchans;
	पूर्णांक di_nchans;
	अचिन्हित पूर्णांक cnt_maxdata;
	पूर्णांक pwm_nchans;
	अचिन्हित पूर्णांक pwm_maxdata;
पूर्ण;

अटल स्थिर काष्ठा vmk80xx_board vmk80xx_boardinfo[] = अणु
	[DEVICE_VMK8055] = अणु
		.name		= "K8055 (VM110)",
		.model		= VMK8055_MODEL,
		.range		= &range_unipolar5,
		.ai_nchans	= 2,
		.ai_maxdata	= 0x00ff,
		.ao_nchans	= 2,
		.di_nchans	= 6,
		.cnt_maxdata	= 0xffff,
	पूर्ण,
	[DEVICE_VMK8061] = अणु
		.name		= "K8061 (VM140)",
		.model		= VMK8061_MODEL,
		.range		= &vmk8061_range,
		.ai_nchans	= 8,
		.ai_maxdata	= 0x03ff,
		.ao_nchans	= 8,
		.di_nchans	= 8,
		.cnt_maxdata	= 0,	/* unknown, device is not ग_लिखोable */
		.pwm_nchans	= 1,
		.pwm_maxdata	= 0x03ff,
	पूर्ण,
पूर्ण;

काष्ठा vmk80xx_निजी अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_rx;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_tx;
	काष्ठा semaphore limit_sem;
	अचिन्हित अक्षर *usb_rx_buf;
	अचिन्हित अक्षर *usb_tx_buf;
	क्रमागत vmk80xx_model model;
पूर्ण;

अटल व्योम vmk80xx_करो_bulk_msg(काष्ठा comedi_device *dev)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	__u8 tx_addr;
	__u8 rx_addr;
	अचिन्हित पूर्णांक tx_pipe;
	अचिन्हित पूर्णांक rx_pipe;
	माप_प्रकार size;

	tx_addr = devpriv->ep_tx->bEndpoपूर्णांकAddress;
	rx_addr = devpriv->ep_rx->bEndpoपूर्णांकAddress;
	tx_pipe = usb_sndbulkpipe(usb, tx_addr);
	rx_pipe = usb_rcvbulkpipe(usb, rx_addr);

	/*
	 * The max packet size attributes of the K8061
	 * input/output endpoपूर्णांकs are identical
	 */
	size = usb_endpoपूर्णांक_maxp(devpriv->ep_tx);

	usb_bulk_msg(usb, tx_pipe, devpriv->usb_tx_buf,
		     size, शून्य, devpriv->ep_tx->bInterval);
	usb_bulk_msg(usb, rx_pipe, devpriv->usb_rx_buf, size, शून्य, HZ * 10);
पूर्ण

अटल पूर्णांक vmk80xx_पढ़ो_packet(काष्ठा comedi_device *dev)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	अचिन्हित पूर्णांक pipe;

	अगर (devpriv->model == VMK8061_MODEL) अणु
		vmk80xx_करो_bulk_msg(dev);
		वापस 0;
	पूर्ण

	ep = devpriv->ep_rx;
	pipe = usb_rcvपूर्णांकpipe(usb, ep->bEndpoपूर्णांकAddress);
	वापस usb_पूर्णांकerrupt_msg(usb, pipe, devpriv->usb_rx_buf,
				 usb_endpoपूर्णांक_maxp(ep), शून्य,
				 HZ * 10);
पूर्ण

अटल पूर्णांक vmk80xx_ग_लिखो_packet(काष्ठा comedi_device *dev, पूर्णांक cmd)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	अचिन्हित पूर्णांक pipe;

	devpriv->usb_tx_buf[0] = cmd;

	अगर (devpriv->model == VMK8061_MODEL) अणु
		vmk80xx_करो_bulk_msg(dev);
		वापस 0;
	पूर्ण

	ep = devpriv->ep_tx;
	pipe = usb_sndपूर्णांकpipe(usb, ep->bEndpoपूर्णांकAddress);
	वापस usb_पूर्णांकerrupt_msg(usb, pipe, devpriv->usb_tx_buf,
				 usb_endpoपूर्णांक_maxp(ep), शून्य,
				 HZ * 10);
पूर्ण

अटल पूर्णांक vmk80xx_reset_device(काष्ठा comedi_device *dev)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	माप_प्रकार size;
	पूर्णांक retval;

	size = usb_endpoपूर्णांक_maxp(devpriv->ep_tx);
	स_रखो(devpriv->usb_tx_buf, 0, size);
	retval = vmk80xx_ग_लिखो_packet(dev, VMK8055_CMD_RST);
	अगर (retval)
		वापस retval;
	/* set outमाला_दो to known state as we cannot पढ़ो them */
	वापस vmk80xx_ग_लिखो_packet(dev, VMK8055_CMD_WRT_AD);
पूर्ण

अटल पूर्णांक vmk80xx_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	पूर्णांक chan;
	पूर्णांक reg[2];
	पूर्णांक n;

	करोwn(&devpriv->limit_sem);
	chan = CR_CHAN(insn->chanspec);

	चयन (devpriv->model) अणु
	हाल VMK8055_MODEL:
		अगर (!chan)
			reg[0] = VMK8055_AI1_REG;
		अन्यथा
			reg[0] = VMK8055_AI2_REG;
		अवरोध;
	हाल VMK8061_MODEL:
	शेष:
		reg[0] = VMK8061_AI_REG1;
		reg[1] = VMK8061_AI_REG2;
		devpriv->usb_tx_buf[0] = VMK8061_CMD_RD_AI;
		devpriv->usb_tx_buf[VMK8061_CH_REG] = chan;
		अवरोध;
	पूर्ण

	क्रम (n = 0; n < insn->n; n++) अणु
		अगर (vmk80xx_पढ़ो_packet(dev))
			अवरोध;

		अगर (devpriv->model == VMK8055_MODEL) अणु
			data[n] = devpriv->usb_rx_buf[reg[0]];
			जारी;
		पूर्ण

		/* VMK8061_MODEL */
		data[n] = devpriv->usb_rx_buf[reg[0]] + 256 *
		    devpriv->usb_rx_buf[reg[1]];
	पूर्ण

	up(&devpriv->limit_sem);

	वापस n;
पूर्ण

अटल पूर्णांक vmk80xx_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	पूर्णांक chan;
	पूर्णांक cmd;
	पूर्णांक reg;
	पूर्णांक n;

	करोwn(&devpriv->limit_sem);
	chan = CR_CHAN(insn->chanspec);

	चयन (devpriv->model) अणु
	हाल VMK8055_MODEL:
		cmd = VMK8055_CMD_WRT_AD;
		अगर (!chan)
			reg = VMK8055_AO1_REG;
		अन्यथा
			reg = VMK8055_AO2_REG;
		अवरोध;
	शेष:		/* NOTE: aव्योम compiler warnings */
		cmd = VMK8061_CMD_SET_AO;
		reg = VMK8061_AO_REG;
		devpriv->usb_tx_buf[VMK8061_CH_REG] = chan;
		अवरोध;
	पूर्ण

	क्रम (n = 0; n < insn->n; n++) अणु
		devpriv->usb_tx_buf[reg] = data[n];

		अगर (vmk80xx_ग_लिखो_packet(dev, cmd))
			अवरोध;
	पूर्ण

	up(&devpriv->limit_sem);

	वापस n;
पूर्ण

अटल पूर्णांक vmk80xx_ao_insn_पढ़ो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	पूर्णांक chan;
	पूर्णांक reg;
	पूर्णांक n;

	करोwn(&devpriv->limit_sem);
	chan = CR_CHAN(insn->chanspec);

	reg = VMK8061_AO_REG - 1;

	devpriv->usb_tx_buf[0] = VMK8061_CMD_RD_AO;

	क्रम (n = 0; n < insn->n; n++) अणु
		अगर (vmk80xx_पढ़ो_packet(dev))
			अवरोध;

		data[n] = devpriv->usb_rx_buf[reg + chan];
	पूर्ण

	up(&devpriv->limit_sem);

	वापस n;
पूर्ण

अटल पूर्णांक vmk80xx_di_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	अचिन्हित अक्षर *rx_buf;
	पूर्णांक reg;
	पूर्णांक retval;

	करोwn(&devpriv->limit_sem);

	rx_buf = devpriv->usb_rx_buf;

	अगर (devpriv->model == VMK8061_MODEL) अणु
		reg = VMK8061_DI_REG;
		devpriv->usb_tx_buf[0] = VMK8061_CMD_RD_DI;
	पूर्ण अन्यथा अणु
		reg = VMK8055_DI_REG;
	पूर्ण

	retval = vmk80xx_पढ़ो_packet(dev);

	अगर (!retval) अणु
		अगर (devpriv->model == VMK8055_MODEL)
			data[1] = (((rx_buf[reg] >> 4) & 0x03) |
				  ((rx_buf[reg] << 2) & 0x04) |
				  ((rx_buf[reg] >> 3) & 0x18));
		अन्यथा
			data[1] = rx_buf[reg];

		retval = 2;
	पूर्ण

	up(&devpriv->limit_sem);

	वापस retval;
पूर्ण

अटल पूर्णांक vmk80xx_करो_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	अचिन्हित अक्षर *rx_buf = devpriv->usb_rx_buf;
	अचिन्हित अक्षर *tx_buf = devpriv->usb_tx_buf;
	पूर्णांक reg, cmd;
	पूर्णांक ret = 0;

	अगर (devpriv->model == VMK8061_MODEL) अणु
		reg = VMK8061_DO_REG;
		cmd = VMK8061_CMD_DO;
	पूर्ण अन्यथा अणु /* VMK8055_MODEL */
		reg = VMK8055_DO_REG;
		cmd = VMK8055_CMD_WRT_AD;
	पूर्ण

	करोwn(&devpriv->limit_sem);

	अगर (comedi_dio_update_state(s, data)) अणु
		tx_buf[reg] = s->state;
		ret = vmk80xx_ग_लिखो_packet(dev, cmd);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (devpriv->model == VMK8061_MODEL) अणु
		tx_buf[0] = VMK8061_CMD_RD_DO;
		ret = vmk80xx_पढ़ो_packet(dev);
		अगर (ret)
			जाओ out;
		data[1] = rx_buf[reg];
	पूर्ण अन्यथा अणु
		data[1] = s->state;
	पूर्ण

out:
	up(&devpriv->limit_sem);

	वापस ret ? ret : insn->n;
पूर्ण

अटल पूर्णांक vmk80xx_cnt_insn_पढ़ो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	पूर्णांक chan;
	पूर्णांक reg[2];
	पूर्णांक n;

	करोwn(&devpriv->limit_sem);
	chan = CR_CHAN(insn->chanspec);

	चयन (devpriv->model) अणु
	हाल VMK8055_MODEL:
		अगर (!chan)
			reg[0] = VMK8055_CNT1_REG;
		अन्यथा
			reg[0] = VMK8055_CNT2_REG;
		अवरोध;
	हाल VMK8061_MODEL:
	शेष:
		reg[0] = VMK8061_CNT_REG;
		reg[1] = VMK8061_CNT_REG;
		devpriv->usb_tx_buf[0] = VMK8061_CMD_RD_CNT;
		अवरोध;
	पूर्ण

	क्रम (n = 0; n < insn->n; n++) अणु
		अगर (vmk80xx_पढ़ो_packet(dev))
			अवरोध;

		अगर (devpriv->model == VMK8055_MODEL)
			data[n] = devpriv->usb_rx_buf[reg[0]];
		अन्यथा /* VMK8061_MODEL */
			data[n] = devpriv->usb_rx_buf[reg[0] * (chan + 1) + 1]
			    + 256 * devpriv->usb_rx_buf[reg[1] * 2 + 2];
	पूर्ण

	up(&devpriv->limit_sem);

	वापस n;
पूर्ण

अटल पूर्णांक vmk80xx_cnt_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक cmd;
	पूर्णांक reg;
	पूर्णांक ret;

	करोwn(&devpriv->limit_sem);
	चयन (data[0]) अणु
	हाल INSN_CONFIG_RESET:
		अगर (devpriv->model == VMK8055_MODEL) अणु
			अगर (!chan) अणु
				cmd = VMK8055_CMD_RST_CNT1;
				reg = VMK8055_CNT1_REG;
			पूर्ण अन्यथा अणु
				cmd = VMK8055_CMD_RST_CNT2;
				reg = VMK8055_CNT2_REG;
			पूर्ण
			devpriv->usb_tx_buf[reg] = 0x00;
		पूर्ण अन्यथा अणु
			cmd = VMK8061_CMD_RST_CNT;
		पूर्ण
		ret = vmk80xx_ग_लिखो_packet(dev, cmd);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	up(&devpriv->limit_sem);

	वापस ret ? ret : insn->n;
पूर्ण

अटल पूर्णांक vmk80xx_cnt_insn_ग_लिखो(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ debसमय;
	अचिन्हित दीर्घ val;
	पूर्णांक chan;
	पूर्णांक cmd;
	पूर्णांक n;

	करोwn(&devpriv->limit_sem);
	chan = CR_CHAN(insn->chanspec);

	अगर (!chan)
		cmd = VMK8055_CMD_DEB1_TIME;
	अन्यथा
		cmd = VMK8055_CMD_DEB2_TIME;

	क्रम (n = 0; n < insn->n; n++) अणु
		debसमय = data[n];
		अगर (debसमय == 0)
			debसमय = 1;

		/* TODO: Prevent overflows */
		अगर (debसमय > 7450)
			debसमय = 7450;

		val = पूर्णांक_वर्ग_मूल(debसमय * 1000 / 115);
		अगर (((val + 1) * val) < debसमय * 1000 / 115)
			val += 1;

		devpriv->usb_tx_buf[6 + chan] = val;

		अगर (vmk80xx_ग_लिखो_packet(dev, cmd))
			अवरोध;
	पूर्ण

	up(&devpriv->limit_sem);

	वापस n;
पूर्ण

अटल पूर्णांक vmk80xx_pwm_insn_पढ़ो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	अचिन्हित अक्षर *tx_buf;
	अचिन्हित अक्षर *rx_buf;
	पूर्णांक reg[2];
	पूर्णांक n;

	करोwn(&devpriv->limit_sem);

	tx_buf = devpriv->usb_tx_buf;
	rx_buf = devpriv->usb_rx_buf;

	reg[0] = VMK8061_PWM_REG1;
	reg[1] = VMK8061_PWM_REG2;

	tx_buf[0] = VMK8061_CMD_RD_PWM;

	क्रम (n = 0; n < insn->n; n++) अणु
		अगर (vmk80xx_पढ़ो_packet(dev))
			अवरोध;

		data[n] = rx_buf[reg[0]] + 4 * rx_buf[reg[1]];
	पूर्ण

	up(&devpriv->limit_sem);

	वापस n;
पूर्ण

अटल पूर्णांक vmk80xx_pwm_insn_ग_लिखो(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	अचिन्हित अक्षर *tx_buf;
	पूर्णांक reg[2];
	पूर्णांक cmd;
	पूर्णांक n;

	करोwn(&devpriv->limit_sem);

	tx_buf = devpriv->usb_tx_buf;

	reg[0] = VMK8061_PWM_REG1;
	reg[1] = VMK8061_PWM_REG2;

	cmd = VMK8061_CMD_OUT_PWM;

	/*
	 * The followin piece of code was translated from the अंतरभूत
	 * assembler code in the DLL source code.
	 *
	 * यंत्र
	 *   mov eax, k  ; k is the value (data[n])
	 *   and al, 03h ; al are the lower 8 bits of eax
	 *   mov lo, al  ; lo is the low part (tx_buf[reg[0]])
	 *   mov eax, k
	 *   shr eax, 2  ; right shअगरt eax रेजिस्टर by 2
	 *   mov hi, al  ; hi is the high part (tx_buf[reg[1]])
	 * end;
	 */
	क्रम (n = 0; n < insn->n; n++) अणु
		tx_buf[reg[0]] = (अचिन्हित अक्षर)(data[n] & 0x03);
		tx_buf[reg[1]] = (अचिन्हित अक्षर)(data[n] >> 2) & 0xff;

		अगर (vmk80xx_ग_लिखो_packet(dev, cmd))
			अवरोध;
	पूर्ण

	up(&devpriv->limit_sem);

	वापस n;
पूर्ण

अटल पूर्णांक vmk80xx_find_usb_endpoपूर्णांकs(काष्ठा comedi_device *dev)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc = पूर्णांकf->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc;
	पूर्णांक i;

	अगर (अगरace_desc->desc.bNumEndpoपूर्णांकs != 2)
		वापस -ENODEV;

	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; i++) अणु
		ep_desc = &अगरace_desc->endpoपूर्णांक[i].desc;

		अगर (usb_endpoपूर्णांक_is_पूर्णांक_in(ep_desc) ||
		    usb_endpoपूर्णांक_is_bulk_in(ep_desc)) अणु
			अगर (!devpriv->ep_rx)
				devpriv->ep_rx = ep_desc;
			जारी;
		पूर्ण

		अगर (usb_endpoपूर्णांक_is_पूर्णांक_out(ep_desc) ||
		    usb_endpoपूर्णांक_is_bulk_out(ep_desc)) अणु
			अगर (!devpriv->ep_tx)
				devpriv->ep_tx = ep_desc;
			जारी;
		पूर्ण
	पूर्ण

	अगर (!devpriv->ep_rx || !devpriv->ep_tx)
		वापस -ENODEV;

	अगर (!usb_endpoपूर्णांक_maxp(devpriv->ep_rx) || !usb_endpoपूर्णांक_maxp(devpriv->ep_tx))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक vmk80xx_alloc_usb_buffers(काष्ठा comedi_device *dev)
अणु
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	माप_प्रकार size;

	size = usb_endpoपूर्णांक_maxp(devpriv->ep_rx);
	devpriv->usb_rx_buf = kzalloc(size, GFP_KERNEL);
	अगर (!devpriv->usb_rx_buf)
		वापस -ENOMEM;

	size = usb_endpoपूर्णांक_maxp(devpriv->ep_tx);
	devpriv->usb_tx_buf = kzalloc(size, GFP_KERNEL);
	अगर (!devpriv->usb_tx_buf)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक vmk80xx_init_subdevices(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा vmk80xx_board *board = dev->board_ptr;
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s;
	पूर्णांक n_subd;
	पूर्णांक ret;

	करोwn(&devpriv->limit_sem);

	अगर (devpriv->model == VMK8055_MODEL)
		n_subd = 5;
	अन्यथा
		n_subd = 6;
	ret = comedi_alloc_subdevices(dev, n_subd);
	अगर (ret) अणु
		up(&devpriv->limit_sem);
		वापस ret;
	पूर्ण

	/* Analog input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND;
	s->n_chan	= board->ai_nchans;
	s->maxdata	= board->ai_maxdata;
	s->range_table	= board->range;
	s->insn_पढ़ो	= vmk80xx_ai_insn_पढ़ो;

	/* Analog output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE | SDF_GROUND;
	s->n_chan	= board->ao_nchans;
	s->maxdata	= 0x00ff;
	s->range_table	= board->range;
	s->insn_ग_लिखो	= vmk80xx_ao_insn_ग_लिखो;
	अगर (devpriv->model == VMK8061_MODEL) अणु
		s->subdev_flags	|= SDF_READABLE;
		s->insn_पढ़ो	= vmk80xx_ao_insn_पढ़ो;
	पूर्ण

	/* Digital input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= board->di_nchans;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= vmk80xx_di_insn_bits;

	/* Digital output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= vmk80xx_करो_insn_bits;

	/* Counter subdevice */
	s = &dev->subdevices[4];
	s->type		= COMEDI_SUBD_COUNTER;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 2;
	s->maxdata	= board->cnt_maxdata;
	s->insn_पढ़ो	= vmk80xx_cnt_insn_पढ़ो;
	s->insn_config	= vmk80xx_cnt_insn_config;
	अगर (devpriv->model == VMK8055_MODEL) अणु
		s->subdev_flags	|= SDF_WRITABLE;
		s->insn_ग_लिखो	= vmk80xx_cnt_insn_ग_लिखो;
	पूर्ण

	/* PWM subdevice */
	अगर (devpriv->model == VMK8061_MODEL) अणु
		s = &dev->subdevices[5];
		s->type		= COMEDI_SUBD_PWM;
		s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
		s->n_chan	= board->pwm_nchans;
		s->maxdata	= board->pwm_maxdata;
		s->insn_पढ़ो	= vmk80xx_pwm_insn_पढ़ो;
		s->insn_ग_लिखो	= vmk80xx_pwm_insn_ग_लिखो;
	पूर्ण

	up(&devpriv->limit_sem);

	वापस 0;
पूर्ण

अटल पूर्णांक vmk80xx_स्वतः_attach(काष्ठा comedi_device *dev,
			       अचिन्हित दीर्घ context)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);
	स्थिर काष्ठा vmk80xx_board *board = शून्य;
	काष्ठा vmk80xx_निजी *devpriv;
	पूर्णांक ret;

	अगर (context < ARRAY_SIZE(vmk80xx_boardinfo))
		board = &vmk80xx_boardinfo[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	devpriv->model = board->model;

	sema_init(&devpriv->limit_sem, 8);

	ret = vmk80xx_find_usb_endpoपूर्णांकs(dev);
	अगर (ret)
		वापस ret;

	ret = vmk80xx_alloc_usb_buffers(dev);
	अगर (ret)
		वापस ret;

	usb_set_पूर्णांकfdata(पूर्णांकf, devpriv);

	अगर (devpriv->model == VMK8055_MODEL)
		vmk80xx_reset_device(dev);

	वापस vmk80xx_init_subdevices(dev);
पूर्ण

अटल व्योम vmk80xx_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);
	काष्ठा vmk80xx_निजी *devpriv = dev->निजी;

	अगर (!devpriv)
		वापस;

	करोwn(&devpriv->limit_sem);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	kमुक्त(devpriv->usb_rx_buf);
	kमुक्त(devpriv->usb_tx_buf);

	up(&devpriv->limit_sem);
पूर्ण

अटल काष्ठा comedi_driver vmk80xx_driver = अणु
	.module		= THIS_MODULE,
	.driver_name	= "vmk80xx",
	.स्वतः_attach	= vmk80xx_स्वतः_attach,
	.detach		= vmk80xx_detach,
पूर्ण;

अटल पूर्णांक vmk80xx_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			     स्थिर काष्ठा usb_device_id *id)
अणु
	वापस comedi_usb_स्वतः_config(पूर्णांकf, &vmk80xx_driver, id->driver_info);
पूर्ण

अटल स्थिर काष्ठा usb_device_id vmk80xx_usb_id_table[] = अणु
	अणु USB_DEVICE(0x10cf, 0x5500), .driver_info = DEVICE_VMK8055 पूर्ण,
	अणु USB_DEVICE(0x10cf, 0x5501), .driver_info = DEVICE_VMK8055 पूर्ण,
	अणु USB_DEVICE(0x10cf, 0x5502), .driver_info = DEVICE_VMK8055 पूर्ण,
	अणु USB_DEVICE(0x10cf, 0x5503), .driver_info = DEVICE_VMK8055 पूर्ण,
	अणु USB_DEVICE(0x10cf, 0x8061), .driver_info = DEVICE_VMK8061 पूर्ण,
	अणु USB_DEVICE(0x10cf, 0x8062), .driver_info = DEVICE_VMK8061 पूर्ण,
	अणु USB_DEVICE(0x10cf, 0x8063), .driver_info = DEVICE_VMK8061 पूर्ण,
	अणु USB_DEVICE(0x10cf, 0x8064), .driver_info = DEVICE_VMK8061 पूर्ण,
	अणु USB_DEVICE(0x10cf, 0x8065), .driver_info = DEVICE_VMK8061 पूर्ण,
	अणु USB_DEVICE(0x10cf, 0x8066), .driver_info = DEVICE_VMK8061 पूर्ण,
	अणु USB_DEVICE(0x10cf, 0x8067), .driver_info = DEVICE_VMK8061 पूर्ण,
	अणु USB_DEVICE(0x10cf, 0x8068), .driver_info = DEVICE_VMK8061 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, vmk80xx_usb_id_table);

अटल काष्ठा usb_driver vmk80xx_usb_driver = अणु
	.name		= "vmk80xx",
	.id_table	= vmk80xx_usb_id_table,
	.probe		= vmk80xx_usb_probe,
	.disconnect	= comedi_usb_स्वतः_unconfig,
पूर्ण;
module_comedi_usb_driver(vmk80xx_driver, vmk80xx_usb_driver);

MODULE_AUTHOR("Manuel Gebele <forensixs@gmx.de>");
MODULE_DESCRIPTION("Velleman USB Board Low-Level Driver");
MODULE_LICENSE("GPL");
