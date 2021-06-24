<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ddbridge-i2c.c: Digital Devices bridge i2c driver
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
#समावेश "ddbridge-i2c.h"
#समावेश "ddbridge-regs.h"
#समावेश "ddbridge-io.h"

/******************************************************************************/

अटल पूर्णांक ddb_i2c_cmd(काष्ठा ddb_i2c *i2c, u32 adr, u32 cmd)
अणु
	काष्ठा ddb *dev = i2c->dev;
	अचिन्हित दीर्घ stat;
	u32 val;

	ddbग_लिखोl(dev, (adr << 9) | cmd, i2c->regs + I2C_COMMAND);
	stat = रुको_क्रम_completion_समयout(&i2c->completion, HZ);
	val = ddbपढ़ोl(dev, i2c->regs + I2C_COMMAND);
	अगर (stat == 0) अणु
		dev_err(dev->dev, "I2C timeout, card %d, port %d, link %u\n",
			dev->nr, i2c->nr, i2c->link);
		अणु
			u32 istat = ddbपढ़ोl(dev, INTERRUPT_STATUS);

			dev_err(dev->dev, "DDBridge IRS %08x\n", istat);
			अगर (i2c->link) अणु
				u32 listat = ddbपढ़ोl(dev,
					DDB_LINK_TAG(i2c->link) |
					INTERRUPT_STATUS);

				dev_err(dev->dev, "DDBridge link %u IRS %08x\n",
					i2c->link, listat);
			पूर्ण
			अगर (istat & 1) अणु
				ddbग_लिखोl(dev, istat & 1, INTERRUPT_ACK);
			पूर्ण अन्यथा अणु
				u32 mon = ddbपढ़ोl(dev,
					i2c->regs + I2C_MONITOR);

				dev_err(dev->dev, "I2C cmd=%08x mon=%08x\n",
					val, mon);
			पूर्ण
		पूर्ण
		वापस -EIO;
	पूर्ण
	val &= 0x70000;
	अगर (val == 0x20000)
		dev_err(dev->dev, "I2C bus error\n");
	अगर (val)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक ddb_i2c_master_xfer(काष्ठा i2c_adapter *adapter,
			       काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा ddb_i2c *i2c = (काष्ठा ddb_i2c *)i2c_get_adapdata(adapter);
	काष्ठा ddb *dev = i2c->dev;
	u8 addr = 0;

	addr = msg[0].addr;
	अगर (msg[0].len > i2c->bsize)
		वापस -EIO;
	चयन (num) अणु
	हाल 1:
		अगर (msg[0].flags & I2C_M_RD) अणु
			ddbग_लिखोl(dev, msg[0].len << 16,
				  i2c->regs + I2C_TASKLENGTH);
			अगर (ddb_i2c_cmd(i2c, addr, 3))
				अवरोध;
			ddbcpyfrom(dev, msg[0].buf,
				   i2c->rbuf, msg[0].len);
			वापस num;
		पूर्ण
		ddbcpyto(dev, i2c->wbuf, msg[0].buf, msg[0].len);
		ddbग_लिखोl(dev, msg[0].len, i2c->regs + I2C_TASKLENGTH);
		अगर (ddb_i2c_cmd(i2c, addr, 2))
			अवरोध;
		वापस num;
	हाल 2:
		अगर ((msg[0].flags & I2C_M_RD) == I2C_M_RD)
			अवरोध;
		अगर ((msg[1].flags & I2C_M_RD) != I2C_M_RD)
			अवरोध;
		अगर (msg[1].len > i2c->bsize)
			अवरोध;
		ddbcpyto(dev, i2c->wbuf, msg[0].buf, msg[0].len);
		ddbग_लिखोl(dev, msg[0].len | (msg[1].len << 16),
			  i2c->regs + I2C_TASKLENGTH);
		अगर (ddb_i2c_cmd(i2c, addr, 1))
			अवरोध;
		ddbcpyfrom(dev, msg[1].buf,
			   i2c->rbuf,
			   msg[1].len);
		वापस num;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EIO;
पूर्ण

अटल u32 ddb_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm ddb_i2c_algo = अणु
	.master_xfer   = ddb_i2c_master_xfer,
	.functionality = ddb_i2c_functionality,
पूर्ण;

व्योम ddb_i2c_release(काष्ठा ddb *dev)
अणु
	पूर्णांक i;
	काष्ठा ddb_i2c *i2c;

	क्रम (i = 0; i < dev->i2c_num; i++) अणु
		i2c = &dev->i2c[i];
		i2c_del_adapter(&i2c->adap);
	पूर्ण
पूर्ण

अटल व्योम i2c_handler(व्योम *priv)
अणु
	काष्ठा ddb_i2c *i2c = (काष्ठा ddb_i2c *)priv;

	complete(&i2c->completion);
पूर्ण

अटल पूर्णांक ddb_i2c_add(काष्ठा ddb *dev, काष्ठा ddb_i2c *i2c,
		       स्थिर काष्ठा ddb_regmap *regmap, पूर्णांक link,
		       पूर्णांक i, पूर्णांक num)
अणु
	काष्ठा i2c_adapter *adap;

	i2c->nr = i;
	i2c->dev = dev;
	i2c->link = link;
	i2c->bsize = regmap->i2c_buf->size;
	i2c->wbuf = DDB_LINK_TAG(link) |
		(regmap->i2c_buf->base + i2c->bsize * i);
	i2c->rbuf = i2c->wbuf; /* + i2c->bsize / 2 */
	i2c->regs = DDB_LINK_TAG(link) |
		(regmap->i2c->base + regmap->i2c->size * i);
	ddbग_लिखोl(dev, I2C_SPEED_100, i2c->regs + I2C_TIMING);
	ddbग_लिखोl(dev, ((i2c->rbuf & 0xffff) << 16) | (i2c->wbuf & 0xffff),
		  i2c->regs + I2C_TASKADDRESS);
	init_completion(&i2c->completion);

	adap = &i2c->adap;
	i2c_set_adapdata(adap, i2c);
#अगर_घोषित I2C_ADAP_CLASS_TV_DIGITAL
	adap->class = I2C_ADAP_CLASS_TV_DIGITAL | I2C_CLASS_TV_ANALOG;
#अन्यथा
#अगर_घोषित I2C_CLASS_TV_ANALOG
	adap->class = I2C_CLASS_TV_ANALOG;
#पूर्ण_अगर
#पूर्ण_अगर
	snम_लिखो(adap->name, I2C_NAME_SIZE, "ddbridge_%02x.%x.%x",
		 dev->nr, i2c->link, i);
	adap->algo = &ddb_i2c_algo;
	adap->algo_data = (व्योम *)i2c;
	adap->dev.parent = dev->dev;
	वापस i2c_add_adapter(adap);
पूर्ण

पूर्णांक ddb_i2c_init(काष्ठा ddb *dev)
अणु
	पूर्णांक stat = 0;
	u32 i, j, num = 0, l, base;
	काष्ठा ddb_i2c *i2c;
	काष्ठा i2c_adapter *adap;
	स्थिर काष्ठा ddb_regmap *regmap;

	क्रम (l = 0; l < DDB_MAX_LINK; l++) अणु
		अगर (!dev->link[l].info)
			जारी;
		regmap = dev->link[l].info->regmap;
		अगर (!regmap || !regmap->i2c)
			जारी;
		base = regmap->irq_base_i2c;
		क्रम (i = 0; i < regmap->i2c->num; i++) अणु
			अगर (!(dev->link[l].info->i2c_mask & (1 << i)))
				जारी;
			i2c = &dev->i2c[num];
			ddb_irq_set(dev, l, i + base, i2c_handler, i2c);
			stat = ddb_i2c_add(dev, i2c, regmap, l, i, num);
			अगर (stat)
				अवरोध;
			num++;
		पूर्ण
	पूर्ण
	अगर (stat) अणु
		क्रम (j = 0; j < num; j++) अणु
			i2c = &dev->i2c[j];
			adap = &i2c->adap;
			i2c_del_adapter(adap);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev->i2c_num = num;
	पूर्ण

	वापस stat;
पूर्ण
