<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Synopsys DesignWare I2C adapter driver (slave only).
 *
 * Based on the Synopsys DesignWare I2C adapter driver (master).
 *
 * Copyright (C) 2016 Synopsys Inc.
 */
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश "i2c-designware-core.h"

अटल व्योम i2c_dw_configure_fअगरo_slave(काष्ठा dw_i2c_dev *dev)
अणु
	/* Configure Tx/Rx FIFO threshold levels. */
	regmap_ग_लिखो(dev->map, DW_IC_TX_TL, 0);
	regmap_ग_लिखो(dev->map, DW_IC_RX_TL, 0);

	/* Configure the I2C slave. */
	regmap_ग_लिखो(dev->map, DW_IC_CON, dev->slave_cfg);
	regmap_ग_लिखो(dev->map, DW_IC_INTR_MASK, DW_IC_INTR_SLAVE_MASK);
पूर्ण

/**
 * i2c_dw_init_slave() - Initialize the designware i2c slave hardware
 * @dev: device निजी data
 *
 * This function configures and enables the I2C in slave mode.
 * This function is called during I2C init function, and in हाल of समयout at
 * run समय.
 */
अटल पूर्णांक i2c_dw_init_slave(काष्ठा dw_i2c_dev *dev)
अणु
	पूर्णांक ret;

	ret = i2c_dw_acquire_lock(dev);
	अगर (ret)
		वापस ret;

	/* Disable the adapter. */
	__i2c_dw_disable(dev);

	/* Write SDA hold समय अगर supported */
	अगर (dev->sda_hold_समय)
		regmap_ग_लिखो(dev->map, DW_IC_SDA_HOLD, dev->sda_hold_समय);

	i2c_dw_configure_fअगरo_slave(dev);
	i2c_dw_release_lock(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_dw_reg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा dw_i2c_dev *dev = i2c_get_adapdata(slave->adapter);

	अगर (dev->slave)
		वापस -EBUSY;
	अगर (slave->flags & I2C_CLIENT_TEN)
		वापस -EAFNOSUPPORT;
	pm_runसमय_get_sync(dev->dev);

	/*
	 * Set slave address in the IC_SAR रेजिस्टर,
	 * the address to which the DW_apb_i2c responds.
	 */
	__i2c_dw_disable_noरुको(dev);
	regmap_ग_लिखो(dev->map, DW_IC_SAR, slave->addr);
	dev->slave = slave;

	__i2c_dw_enable(dev);

	dev->cmd_err = 0;
	dev->msg_ग_लिखो_idx = 0;
	dev->msg_पढ़ो_idx = 0;
	dev->msg_err = 0;
	dev->status = STATUS_IDLE;
	dev->पात_source = 0;
	dev->rx_outstanding = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_dw_unreg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा dw_i2c_dev *dev = i2c_get_adapdata(slave->adapter);

	dev->disable_पूर्णांक(dev);
	dev->disable(dev);
	synchronize_irq(dev->irq);
	dev->slave = शून्य;
	pm_runसमय_put(dev->dev);

	वापस 0;
पूर्ण

अटल u32 i2c_dw_पढ़ो_clear_पूर्णांकrbits_slave(काष्ठा dw_i2c_dev *dev)
अणु
	u32 stat, dummy;

	/*
	 * The IC_INTR_STAT रेजिस्टर just indicates "enabled" पूर्णांकerrupts.
	 * The unmasked raw version of पूर्णांकerrupt status bits is available
	 * in the IC_RAW_INTR_STAT रेजिस्टर.
	 *
	 * That is,
	 *   stat = पढ़ोl(IC_INTR_STAT);
	 * equals to,
	 *   stat = पढ़ोl(IC_RAW_INTR_STAT) & पढ़ोl(IC_INTR_MASK);
	 *
	 * The raw version might be useful क्रम debugging purposes.
	 */
	regmap_पढ़ो(dev->map, DW_IC_INTR_STAT, &stat);

	/*
	 * Do not use the IC_CLR_INTR रेजिस्टर to clear पूर्णांकerrupts, or
	 * you'll miss some पूर्णांकerrupts, triggered during the period from
	 * पढ़ोl(IC_INTR_STAT) to पढ़ोl(IC_CLR_INTR).
	 *
	 * Instead, use the separately-prepared IC_CLR_* रेजिस्टरs.
	 */
	अगर (stat & DW_IC_INTR_TX_ABRT)
		regmap_पढ़ो(dev->map, DW_IC_CLR_TX_ABRT, &dummy);
	अगर (stat & DW_IC_INTR_RX_UNDER)
		regmap_पढ़ो(dev->map, DW_IC_CLR_RX_UNDER, &dummy);
	अगर (stat & DW_IC_INTR_RX_OVER)
		regmap_पढ़ो(dev->map, DW_IC_CLR_RX_OVER, &dummy);
	अगर (stat & DW_IC_INTR_TX_OVER)
		regmap_पढ़ो(dev->map, DW_IC_CLR_TX_OVER, &dummy);
	अगर (stat & DW_IC_INTR_RX_DONE)
		regmap_पढ़ो(dev->map, DW_IC_CLR_RX_DONE, &dummy);
	अगर (stat & DW_IC_INTR_ACTIVITY)
		regmap_पढ़ो(dev->map, DW_IC_CLR_ACTIVITY, &dummy);
	अगर (stat & DW_IC_INTR_STOP_DET)
		regmap_पढ़ो(dev->map, DW_IC_CLR_STOP_DET, &dummy);
	अगर (stat & DW_IC_INTR_START_DET)
		regmap_पढ़ो(dev->map, DW_IC_CLR_START_DET, &dummy);
	अगर (stat & DW_IC_INTR_GEN_CALL)
		regmap_पढ़ो(dev->map, DW_IC_CLR_GEN_CALL, &dummy);

	वापस stat;
पूर्ण

/*
 * Interrupt service routine. This माला_लो called whenever an I2C slave पूर्णांकerrupt
 * occurs.
 */

अटल पूर्णांक i2c_dw_irq_handler_slave(काष्ठा dw_i2c_dev *dev)
अणु
	u32 raw_stat, stat, enabled, पंचांगp;
	u8 val = 0, slave_activity;

	regmap_पढ़ो(dev->map, DW_IC_ENABLE, &enabled);
	regmap_पढ़ो(dev->map, DW_IC_RAW_INTR_STAT, &raw_stat);
	regmap_पढ़ो(dev->map, DW_IC_STATUS, &पंचांगp);
	slave_activity = ((पंचांगp & DW_IC_STATUS_SLAVE_ACTIVITY) >> 6);

	अगर (!enabled || !(raw_stat & ~DW_IC_INTR_ACTIVITY) || !dev->slave)
		वापस 0;

	stat = i2c_dw_पढ़ो_clear_पूर्णांकrbits_slave(dev);
	dev_dbg(dev->dev,
		"%#x STATUS SLAVE_ACTIVITY=%#x : RAW_INTR_STAT=%#x : INTR_STAT=%#x\n",
		enabled, slave_activity, raw_stat, stat);

	अगर (stat & DW_IC_INTR_RX_FULL) अणु
		अगर (dev->status != STATUS_WRITE_IN_PROGRESS) अणु
			dev->status = STATUS_WRITE_IN_PROGRESS;
			i2c_slave_event(dev->slave, I2C_SLAVE_WRITE_REQUESTED,
					&val);
		पूर्ण

		regmap_पढ़ो(dev->map, DW_IC_DATA_CMD, &पंचांगp);
		val = पंचांगp;
		अगर (!i2c_slave_event(dev->slave, I2C_SLAVE_WRITE_RECEIVED,
				     &val))
			dev_vdbg(dev->dev, "Byte %X acked!", val);
	पूर्ण

	अगर (stat & DW_IC_INTR_RD_REQ) अणु
		अगर (slave_activity) अणु
			regmap_पढ़ो(dev->map, DW_IC_CLR_RD_REQ, &पंचांगp);

			dev->status = STATUS_READ_IN_PROGRESS;
			अगर (!i2c_slave_event(dev->slave,
					     I2C_SLAVE_READ_REQUESTED,
					     &val))
				regmap_ग_लिखो(dev->map, DW_IC_DATA_CMD, val);
		पूर्ण
	पूर्ण

	अगर (stat & DW_IC_INTR_RX_DONE) अणु
		अगर (!i2c_slave_event(dev->slave, I2C_SLAVE_READ_PROCESSED,
				     &val))
			regmap_पढ़ो(dev->map, DW_IC_CLR_RX_DONE, &पंचांगp);
	पूर्ण

	अगर (stat & DW_IC_INTR_STOP_DET) अणु
		dev->status = STATUS_IDLE;
		i2c_slave_event(dev->slave, I2C_SLAVE_STOP, &val);
	पूर्ण

	वापस 1;
पूर्ण

अटल irqवापस_t i2c_dw_isr_slave(पूर्णांक this_irq, व्योम *dev_id)
अणु
	काष्ठा dw_i2c_dev *dev = dev_id;
	पूर्णांक ret;

	ret = i2c_dw_irq_handler_slave(dev);
	अगर (ret > 0)
		complete(&dev->cmd_complete);

	वापस IRQ_RETVAL(ret);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm i2c_dw_algo = अणु
	.functionality = i2c_dw_func,
	.reg_slave = i2c_dw_reg_slave,
	.unreg_slave = i2c_dw_unreg_slave,
पूर्ण;

व्योम i2c_dw_configure_slave(काष्ठा dw_i2c_dev *dev)
अणु
	dev->functionality = I2C_FUNC_SLAVE | DW_IC_DEFAULT_FUNCTIONALITY;

	dev->slave_cfg = DW_IC_CON_RX_FIFO_FULL_HLD_CTRL |
			 DW_IC_CON_RESTART_EN | DW_IC_CON_STOP_DET_IFADDRESSED;

	dev->mode = DW_IC_SLAVE;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_dw_configure_slave);

पूर्णांक i2c_dw_probe_slave(काष्ठा dw_i2c_dev *dev)
अणु
	काष्ठा i2c_adapter *adap = &dev->adapter;
	पूर्णांक ret;

	init_completion(&dev->cmd_complete);

	dev->init = i2c_dw_init_slave;
	dev->disable = i2c_dw_disable;
	dev->disable_पूर्णांक = i2c_dw_disable_पूर्णांक;

	ret = i2c_dw_init_regmap(dev);
	अगर (ret)
		वापस ret;

	ret = i2c_dw_set_sda_hold(dev);
	अगर (ret)
		वापस ret;

	ret = i2c_dw_set_fअगरo_size(dev);
	अगर (ret)
		वापस ret;

	ret = dev->init(dev);
	अगर (ret)
		वापस ret;

	snम_लिखो(adap->name, माप(adap->name),
		 "Synopsys DesignWare I2C Slave adapter");
	adap->retries = 3;
	adap->algo = &i2c_dw_algo;
	adap->dev.parent = dev->dev;
	i2c_set_adapdata(adap, dev);

	ret = devm_request_irq(dev->dev, dev->irq, i2c_dw_isr_slave,
			       IRQF_SHARED, dev_name(dev->dev), dev);
	अगर (ret) अणु
		dev_err(dev->dev, "failure requesting irq %i: %d\n",
			dev->irq, ret);
		वापस ret;
	पूर्ण

	ret = i2c_add_numbered_adapter(adap);
	अगर (ret)
		dev_err(dev->dev, "failure adding adapter: %d\n", ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_dw_probe_slave);

MODULE_AUTHOR("Luis Oliveira <lolivei@synopsys.com>");
MODULE_DESCRIPTION("Synopsys DesignWare I2C bus slave adapter");
MODULE_LICENSE("GPL v2");
