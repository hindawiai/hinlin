<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  i2c slave support क्रम Aपंचांगel's AT91 Two-Wire Interface (TWI)
 *
 *  Copyright (C) 2017 Juergen Fitschen <me@jue.yt>
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "i2c-at91.h"

अटल irqवापस_t aपंचांगel_twi_पूर्णांकerrupt_slave(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा at91_twi_dev *dev = dev_id;
	स्थिर अचिन्हित status = at91_twi_पढ़ो(dev, AT91_TWI_SR);
	स्थिर अचिन्हित irqstatus = status & at91_twi_पढ़ो(dev, AT91_TWI_IMR);
	u8 value;

	अगर (!irqstatus)
		वापस IRQ_NONE;

	/* slave address has been detected on I2C bus */
	अगर (irqstatus & AT91_TWI_SVACC) अणु
		अगर (status & AT91_TWI_SVREAD) अणु
			i2c_slave_event(dev->slave,
					I2C_SLAVE_READ_REQUESTED, &value);
			ग_लिखोb_relaxed(value, dev->base + AT91_TWI_THR);
			at91_twi_ग_लिखो(dev, AT91_TWI_IER,
				       AT91_TWI_TXRDY | AT91_TWI_EOSACC);
		पूर्ण अन्यथा अणु
			i2c_slave_event(dev->slave,
					I2C_SLAVE_WRITE_REQUESTED, &value);
			at91_twi_ग_लिखो(dev, AT91_TWI_IER,
				       AT91_TWI_RXRDY | AT91_TWI_EOSACC);
		पूर्ण
		at91_twi_ग_लिखो(dev, AT91_TWI_IDR, AT91_TWI_SVACC);
	पूर्ण

	/* byte transmitted to remote master */
	अगर (irqstatus & AT91_TWI_TXRDY) अणु
		i2c_slave_event(dev->slave, I2C_SLAVE_READ_PROCESSED, &value);
		ग_लिखोb_relaxed(value, dev->base + AT91_TWI_THR);
	पूर्ण

	/* byte received from remote master */
	अगर (irqstatus & AT91_TWI_RXRDY) अणु
		value = पढ़ोb_relaxed(dev->base + AT91_TWI_RHR);
		i2c_slave_event(dev->slave, I2C_SLAVE_WRITE_RECEIVED, &value);
	पूर्ण

	/* master sent stop */
	अगर (irqstatus & AT91_TWI_EOSACC) अणु
		at91_twi_ग_लिखो(dev, AT91_TWI_IDR,
			       AT91_TWI_TXRDY | AT91_TWI_RXRDY | AT91_TWI_EOSACC);
		at91_twi_ग_लिखो(dev, AT91_TWI_IER, AT91_TWI_SVACC);
		i2c_slave_event(dev->slave, I2C_SLAVE_STOP, &value);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक at91_reg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा at91_twi_dev *dev = i2c_get_adapdata(slave->adapter);

	अगर (dev->slave)
		वापस -EBUSY;

	अगर (slave->flags & I2C_CLIENT_TEN)
		वापस -EAFNOSUPPORT;

	/* Make sure twi_clk करोesn't get turned off! */
	pm_runसमय_get_sync(dev->dev);

	dev->slave = slave;
	dev->smr = AT91_TWI_SMR_SADR(slave->addr);

	at91_init_twi_bus(dev);
	at91_twi_ग_लिखो(dev, AT91_TWI_IER, AT91_TWI_SVACC);

	dev_info(dev->dev, "entered slave mode (ADR=%d)\n", slave->addr);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_unreg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा at91_twi_dev *dev = i2c_get_adapdata(slave->adapter);

	WARN_ON(!dev->slave);

	dev_info(dev->dev, "leaving slave mode\n");

	dev->slave = शून्य;
	dev->smr = 0;

	at91_init_twi_bus(dev);

	pm_runसमय_put(dev->dev);

	वापस 0;
पूर्ण

अटल u32 at91_twi_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SLAVE | I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL
		| I2C_FUNC_SMBUS_READ_BLOCK_DATA;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm at91_twi_algorithm_slave = अणु
	.reg_slave	= at91_reg_slave,
	.unreg_slave	= at91_unreg_slave,
	.functionality	= at91_twi_func,
पूर्ण;

पूर्णांक at91_twi_probe_slave(काष्ठा platक्रमm_device *pdev,
			 u32 phy_addr, काष्ठा at91_twi_dev *dev)
अणु
	पूर्णांक rc;

	rc = devm_request_irq(&pdev->dev, dev->irq, aपंचांगel_twi_पूर्णांकerrupt_slave,
			      0, dev_name(dev->dev), dev);
	अगर (rc) अणु
		dev_err(dev->dev, "Cannot get irq %d: %d\n", dev->irq, rc);
		वापस rc;
	पूर्ण

	dev->adapter.algo = &at91_twi_algorithm_slave;

	वापस 0;
पूर्ण

व्योम at91_init_twi_bus_slave(काष्ठा at91_twi_dev *dev)
अणु
	at91_twi_ग_लिखो(dev, AT91_TWI_CR, AT91_TWI_MSDIS);
	अगर (dev->slave_detected && dev->smr) अणु
		at91_twi_ग_लिखो(dev, AT91_TWI_SMR, dev->smr);
		at91_twi_ग_लिखो(dev, AT91_TWI_CR, AT91_TWI_SVEN);
	पूर्ण
पूर्ण
