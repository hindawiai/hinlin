<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ngene-i2c.c: nGene PCIe bridge driver i2c functions
 *
 * Copyright (C) 2005-2007 Micronas
 *
 * Copyright (C) 2008-2009 Ralph Metzler <rjkm@metzlerbros.de>
 *                         Modअगरications क्रम new nGene firmware,
 *                         support क्रम EEPROM-copying,
 *                         support क्रम new dual DVB-S2 card prototype
 */

/* FIXME - some of these can probably be हटाओd */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/भाग64.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/समयr.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/firmware.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "ngene.h"

/* Firmware command क्रम i2c operations */
अटल पूर्णांक ngene_command_i2c_पढ़ो(काष्ठा ngene *dev, u8 adr,
			   u8 *out, u8 outlen, u8 *in, u8 inlen, पूर्णांक flag)
अणु
	काष्ठा ngene_command com;

	com.cmd.hdr.Opcode = CMD_I2C_READ;
	com.cmd.hdr.Length = outlen + 3;
	com.cmd.I2CRead.Device = adr << 1;
	स_नकल(com.cmd.I2CRead.Data, out, outlen);
	com.cmd.I2CRead.Data[outlen] = inlen;
	com.cmd.I2CRead.Data[outlen + 1] = 0;
	com.in_len = outlen + 3;
	com.out_len = inlen + 1;

	अगर (ngene_command(dev, &com) < 0)
		वापस -EIO;

	अगर ((com.cmd.raw8[0] >> 1) != adr)
		वापस -EIO;

	अगर (flag)
		स_नकल(in, com.cmd.raw8, inlen + 1);
	अन्यथा
		स_नकल(in, com.cmd.raw8 + 1, inlen);
	वापस 0;
पूर्ण

अटल पूर्णांक ngene_command_i2c_ग_लिखो(काष्ठा ngene *dev, u8 adr,
				   u8 *out, u8 outlen)
अणु
	काष्ठा ngene_command com;


	com.cmd.hdr.Opcode = CMD_I2C_WRITE;
	com.cmd.hdr.Length = outlen + 1;
	com.cmd.I2CRead.Device = adr << 1;
	स_नकल(com.cmd.I2CRead.Data, out, outlen);
	com.in_len = outlen + 1;
	com.out_len = 1;

	अगर (ngene_command(dev, &com) < 0)
		वापस -EIO;

	अगर (com.cmd.raw8[0] == 1)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम ngene_i2c_set_bus(काष्ठा ngene *dev, पूर्णांक bus)
अणु
	अगर (!(dev->card_info->i2c_access & 2))
		वापस;
	अगर (dev->i2c_current_bus == bus)
		वापस;

	चयन (bus) अणु
	हाल 0:
		ngene_command_gpio_set(dev, 3, 0);
		ngene_command_gpio_set(dev, 2, 1);
		अवरोध;

	हाल 1:
		ngene_command_gpio_set(dev, 2, 0);
		ngene_command_gpio_set(dev, 3, 1);
		अवरोध;
	पूर्ण
	dev->i2c_current_bus = bus;
पूर्ण

अटल पूर्णांक ngene_i2c_master_xfer(काष्ठा i2c_adapter *adapter,
				 काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा ngene_channel *chan =
		(काष्ठा ngene_channel *)i2c_get_adapdata(adapter);
	काष्ठा ngene *dev = chan->dev;

	mutex_lock(&dev->i2c_चयन_mutex);
	ngene_i2c_set_bus(dev, chan->number);

	अगर (num == 2 && msg[1].flags & I2C_M_RD && !(msg[0].flags & I2C_M_RD))
		अगर (!ngene_command_i2c_पढ़ो(dev, msg[0].addr,
					    msg[0].buf, msg[0].len,
					    msg[1].buf, msg[1].len, 0))
			जाओ करोne;

	अगर (num == 1 && !(msg[0].flags & I2C_M_RD))
		अगर (!ngene_command_i2c_ग_लिखो(dev, msg[0].addr,
					     msg[0].buf, msg[0].len))
			जाओ करोne;
	अगर (num == 1 && (msg[0].flags & I2C_M_RD))
		अगर (!ngene_command_i2c_पढ़ो(dev, msg[0].addr, शून्य, 0,
					    msg[0].buf, msg[0].len, 0))
			जाओ करोne;

	mutex_unlock(&dev->i2c_चयन_mutex);
	वापस -EIO;

करोne:
	mutex_unlock(&dev->i2c_चयन_mutex);
	वापस num;
पूर्ण


अटल u32 ngene_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm ngene_i2c_algo = अणु
	.master_xfer = ngene_i2c_master_xfer,
	.functionality = ngene_i2c_functionality,
पूर्ण;

पूर्णांक ngene_i2c_init(काष्ठा ngene *dev, पूर्णांक dev_nr)
अणु
	काष्ठा i2c_adapter *adap = &(dev->channel[dev_nr].i2c_adapter);

	i2c_set_adapdata(adap, &(dev->channel[dev_nr]));

	strscpy(adap->name, "nGene", माप(adap->name));

	adap->algo = &ngene_i2c_algo;
	adap->algo_data = (व्योम *)&(dev->channel[dev_nr]);
	adap->dev.parent = &dev->pci_dev->dev;

	वापस i2c_add_adapter(adap);
पूर्ण

