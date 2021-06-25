<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010-2013 Bluecherry, LLC <https://www.bluecherrydvr.com>
 *
 * Original author:
 * Ben Collins <bcollins@ubuntu.com>
 *
 * Additional work by:
 * John Brooks <john.brooks@bluecherry.net>
 */

/* XXX: The SOLO6x10 i2c करोes not have separate पूर्णांकerrupts क्रम each i2c
 * channel. The bus can only handle one i2c event at a समय. The below handles
 * this all wrong. We should be using the status रेजिस्टरs to see अगर the bus
 * is in use, and have a global lock to check the status रेजिस्टर. Also,
 * the bulk of the work should be handled out-of-पूर्णांकerrupt. The ugly loops
 * that occur during पूर्णांकerrupt scare me. The ISR should merely संकेत
 * thपढ़ो context, ACK the पूर्णांकerrupt, and move on. -- BenC */

#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "solo6x10.h"

u8 solo_i2c_पढ़ोbyte(काष्ठा solo_dev *solo_dev, पूर्णांक id, u8 addr, u8 off)
अणु
	काष्ठा i2c_msg msgs[2];
	u8 data;

	msgs[0].flags = 0;
	msgs[0].addr = addr;
	msgs[0].len = 1;
	msgs[0].buf = &off;

	msgs[1].flags = I2C_M_RD;
	msgs[1].addr = addr;
	msgs[1].len = 1;
	msgs[1].buf = &data;

	i2c_transfer(&solo_dev->i2c_adap[id], msgs, 2);

	वापस data;
पूर्ण

व्योम solo_i2c_ग_लिखोbyte(काष्ठा solo_dev *solo_dev, पूर्णांक id, u8 addr,
			u8 off, u8 data)
अणु
	काष्ठा i2c_msg msgs;
	u8 buf[2];

	buf[0] = off;
	buf[1] = data;
	msgs.flags = 0;
	msgs.addr = addr;
	msgs.len = 2;
	msgs.buf = buf;

	i2c_transfer(&solo_dev->i2c_adap[id], &msgs, 1);
पूर्ण

अटल व्योम solo_i2c_flush(काष्ठा solo_dev *solo_dev, पूर्णांक wr)
अणु
	u32 ctrl;

	ctrl = SOLO_IIC_CH_SET(solo_dev->i2c_id);

	अगर (solo_dev->i2c_state == IIC_STATE_START)
		ctrl |= SOLO_IIC_START;

	अगर (wr) अणु
		ctrl |= SOLO_IIC_WRITE;
	पूर्ण अन्यथा अणु
		ctrl |= SOLO_IIC_READ;
		अगर (!(solo_dev->i2c_msg->flags & I2C_M_NO_RD_ACK))
			ctrl |= SOLO_IIC_ACK_EN;
	पूर्ण

	अगर (solo_dev->i2c_msg_ptr == solo_dev->i2c_msg->len)
		ctrl |= SOLO_IIC_STOP;

	solo_reg_ग_लिखो(solo_dev, SOLO_IIC_CTRL, ctrl);
पूर्ण

अटल व्योम solo_i2c_start(काष्ठा solo_dev *solo_dev)
अणु
	u32 addr = solo_dev->i2c_msg->addr << 1;

	अगर (solo_dev->i2c_msg->flags & I2C_M_RD)
		addr |= 1;

	solo_dev->i2c_state = IIC_STATE_START;
	solo_reg_ग_लिखो(solo_dev, SOLO_IIC_TXD, addr);
	solo_i2c_flush(solo_dev, 1);
पूर्ण

अटल व्योम solo_i2c_stop(काष्ठा solo_dev *solo_dev)
अणु
	solo_irq_off(solo_dev, SOLO_IRQ_IIC);
	solo_reg_ग_लिखो(solo_dev, SOLO_IIC_CTRL, 0);
	solo_dev->i2c_state = IIC_STATE_STOP;
	wake_up(&solo_dev->i2c_रुको);
पूर्ण

अटल पूर्णांक solo_i2c_handle_पढ़ो(काष्ठा solo_dev *solo_dev)
अणु
prepare_पढ़ो:
	अगर (solo_dev->i2c_msg_ptr != solo_dev->i2c_msg->len) अणु
		solo_i2c_flush(solo_dev, 0);
		वापस 0;
	पूर्ण

	solo_dev->i2c_msg_ptr = 0;
	solo_dev->i2c_msg++;
	solo_dev->i2c_msg_num--;

	अगर (solo_dev->i2c_msg_num == 0) अणु
		solo_i2c_stop(solo_dev);
		वापस 0;
	पूर्ण

	अगर (!(solo_dev->i2c_msg->flags & I2C_M_NOSTART)) अणु
		solo_i2c_start(solo_dev);
	पूर्ण अन्यथा अणु
		अगर (solo_dev->i2c_msg->flags & I2C_M_RD)
			जाओ prepare_पढ़ो;
		अन्यथा
			solo_i2c_stop(solo_dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक solo_i2c_handle_ग_लिखो(काष्ठा solo_dev *solo_dev)
अणु
retry_ग_लिखो:
	अगर (solo_dev->i2c_msg_ptr != solo_dev->i2c_msg->len) अणु
		solo_reg_ग_लिखो(solo_dev, SOLO_IIC_TXD,
			       solo_dev->i2c_msg->buf[solo_dev->i2c_msg_ptr]);
		solo_dev->i2c_msg_ptr++;
		solo_i2c_flush(solo_dev, 1);
		वापस 0;
	पूर्ण

	solo_dev->i2c_msg_ptr = 0;
	solo_dev->i2c_msg++;
	solo_dev->i2c_msg_num--;

	अगर (solo_dev->i2c_msg_num == 0) अणु
		solo_i2c_stop(solo_dev);
		वापस 0;
	पूर्ण

	अगर (!(solo_dev->i2c_msg->flags & I2C_M_NOSTART)) अणु
		solo_i2c_start(solo_dev);
	पूर्ण अन्यथा अणु
		अगर (solo_dev->i2c_msg->flags & I2C_M_RD)
			solo_i2c_stop(solo_dev);
		अन्यथा
			जाओ retry_ग_लिखो;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक solo_i2c_isr(काष्ठा solo_dev *solo_dev)
अणु
	u32 status = solo_reg_पढ़ो(solo_dev, SOLO_IIC_CTRL);
	पूर्णांक ret = -EINVAL;


	अगर (CHK_FLAGS(status, SOLO_IIC_STATE_TRNS | SOLO_IIC_STATE_संक_त्रुटि)
	    || solo_dev->i2c_id < 0) अणु
		solo_i2c_stop(solo_dev);
		वापस -ENXIO;
	पूर्ण

	चयन (solo_dev->i2c_state) अणु
	हाल IIC_STATE_START:
		अगर (solo_dev->i2c_msg->flags & I2C_M_RD) अणु
			solo_dev->i2c_state = IIC_STATE_READ;
			ret = solo_i2c_handle_पढ़ो(solo_dev);
			अवरोध;
		पूर्ण

		solo_dev->i2c_state = IIC_STATE_WRITE;
		fallthrough;
	हाल IIC_STATE_WRITE:
		ret = solo_i2c_handle_ग_लिखो(solo_dev);
		अवरोध;

	हाल IIC_STATE_READ:
		solo_dev->i2c_msg->buf[solo_dev->i2c_msg_ptr] =
			solo_reg_पढ़ो(solo_dev, SOLO_IIC_RXD);
		solo_dev->i2c_msg_ptr++;

		ret = solo_i2c_handle_पढ़ो(solo_dev);
		अवरोध;

	शेष:
		solo_i2c_stop(solo_dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक solo_i2c_master_xfer(काष्ठा i2c_adapter *adap,
				काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा solo_dev *solo_dev = adap->algo_data;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;
	पूर्णांक i;
	DEFINE_WAIT(रुको);

	क्रम (i = 0; i < SOLO_I2C_ADAPTERS; i++) अणु
		अगर (&solo_dev->i2c_adap[i] == adap)
			अवरोध;
	पूर्ण

	अगर (i == SOLO_I2C_ADAPTERS)
		वापस num; /* XXX Right वापस value क्रम failure? */

	mutex_lock(&solo_dev->i2c_mutex);
	solo_dev->i2c_id = i;
	solo_dev->i2c_msg = msgs;
	solo_dev->i2c_msg_num = num;
	solo_dev->i2c_msg_ptr = 0;

	solo_reg_ग_लिखो(solo_dev, SOLO_IIC_CTRL, 0);
	solo_irq_on(solo_dev, SOLO_IRQ_IIC);
	solo_i2c_start(solo_dev);

	समयout = HZ / 2;

	क्रम (;;) अणु
		prepare_to_रुको(&solo_dev->i2c_रुको, &रुको,
				TASK_INTERRUPTIBLE);

		अगर (solo_dev->i2c_state == IIC_STATE_STOP)
			अवरोध;

		समयout = schedule_समयout(समयout);
		अगर (!समयout)
			अवरोध;

		अगर (संकेत_pending(current))
			अवरोध;
	पूर्ण

	finish_रुको(&solo_dev->i2c_रुको, &रुको);
	ret = num - solo_dev->i2c_msg_num;
	solo_dev->i2c_state = IIC_STATE_IDLE;
	solo_dev->i2c_id = -1;

	mutex_unlock(&solo_dev->i2c_mutex);

	वापस ret;
पूर्ण

अटल u32 solo_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm solo_i2c_algo = अणु
	.master_xfer	= solo_i2c_master_xfer,
	.functionality	= solo_i2c_functionality,
पूर्ण;

पूर्णांक solo_i2c_init(काष्ठा solo_dev *solo_dev)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	solo_reg_ग_लिखो(solo_dev, SOLO_IIC_CFG,
		       SOLO_IIC_PRESCALE(8) | SOLO_IIC_ENABLE);

	solo_dev->i2c_id = -1;
	solo_dev->i2c_state = IIC_STATE_IDLE;
	init_रुकोqueue_head(&solo_dev->i2c_रुको);
	mutex_init(&solo_dev->i2c_mutex);

	क्रम (i = 0; i < SOLO_I2C_ADAPTERS; i++) अणु
		काष्ठा i2c_adapter *adap = &solo_dev->i2c_adap[i];

		snम_लिखो(adap->name, I2C_NAME_SIZE, "%s I2C %d",
			 SOLO6X10_NAME, i);
		adap->algo = &solo_i2c_algo;
		adap->algo_data = solo_dev;
		adap->retries = 1;
		adap->dev.parent = &solo_dev->pdev->dev;

		ret = i2c_add_adapter(adap);
		अगर (ret) अणु
			adap->algo_data = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		क्रम (i = 0; i < SOLO_I2C_ADAPTERS; i++) अणु
			अगर (!solo_dev->i2c_adap[i].algo_data)
				अवरोध;
			i2c_del_adapter(&solo_dev->i2c_adap[i]);
			solo_dev->i2c_adap[i].algo_data = शून्य;
		पूर्ण
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम solo_i2c_निकास(काष्ठा solo_dev *solo_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SOLO_I2C_ADAPTERS; i++) अणु
		अगर (!solo_dev->i2c_adap[i].algo_data)
			जारी;
		i2c_del_adapter(&solo_dev->i2c_adap[i]);
		solo_dev->i2c_adap[i].algo_data = शून्य;
	पूर्ण
पूर्ण
