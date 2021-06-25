<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ------------------------------------------------------------------------- */
/* i2c-iop3xx.c i2c driver algorithms क्रम Intel XScale IOP3xx & IXP46x       */
/* ------------------------------------------------------------------------- */
/* Copyright (C) 2003 Peter Milne, D-TACQ Solutions Ltd
 *                    <Peter करोt Milne at D hyphen TACQ करोt com>
 *
 * With acknowledgements to i2c-algo-ibm_ocp.c by
 * Ian DaSilva, MontaVista Software, Inc. idasilva@mvista.com
 *
 * And i2c-algo-pcf.c, which was created by Simon G. Vogl and Hans Berglund:
 *
 * Copyright (C) 1995-1997 Simon G. Vogl, 1998-2000 Hans Berglund
 *
 * And which acknowledged Kyथघsti Mथअlkki <kmalkki@cc.hut.fi>,
 * Froकरो Looijaard <froकरोl@dds.nl>, Martin Bailey<mbailey@littlefeet-inc.com>
 *
 * Major cleanup by Deepak Saxena <dsaxena@plनिकासy.net>, 01/2005:
 *
 * - Use driver model to pass per-chip info instead of hardcoding and #अगर_घोषितs
 * - Use ioremap/__raw_पढ़ोl/__raw_ग_लिखोl instead of direct dereference
 * - Make it work with IXP46x chips
 * - Cleanup function names, coding style, etc
 *
 * - writing to slave address causes latchup on iop331.
 *	fix: driver refuses to address self.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/consumer.h>

#समावेश "i2c-iop3xx.h"

/* global unit counter */
अटल पूर्णांक i2c_id;

अटल अंतरभूत अचिन्हित अक्षर
iic_cook_addr(काष्ठा i2c_msg *msg)
अणु
	अचिन्हित अक्षर addr;

	addr = i2c_8bit_addr_from_msg(msg);

	वापस addr;
पूर्ण

अटल व्योम
iop3xx_i2c_reset(काष्ठा i2c_algo_iop3xx_data *iop3xx_adap)
अणु
	/* Follows devman 9.3 */
	__raw_ग_लिखोl(IOP3XX_ICR_UNIT_RESET, iop3xx_adap->ioaddr + CR_OFFSET);
	__raw_ग_लिखोl(IOP3XX_ISR_CLEARBITS, iop3xx_adap->ioaddr + SR_OFFSET);
	__raw_ग_लिखोl(0, iop3xx_adap->ioaddr + CR_OFFSET);
पूर्ण

अटल व्योम
iop3xx_i2c_enable(काष्ठा i2c_algo_iop3xx_data *iop3xx_adap)
अणु
	u32 cr = IOP3XX_ICR_GCD | IOP3XX_ICR_SCLEN | IOP3XX_ICR_UE;

	/*
	 * Every समय unit enable is निश्चितed, GPOD needs to be cleared
	 * on IOP3XX to aव्योम data corruption on the bus. We use the
	 * gpiod_set_raw_value() to make sure the 0 hits the hardware
	 * GPOD रेजिस्टर. These descriptors are only passed aदीर्घ to
	 * the device अगर this is necessary.
	 */
	अगर (iop3xx_adap->gpio_scl)
		gpiod_set_raw_value(iop3xx_adap->gpio_scl, 0);
	अगर (iop3xx_adap->gpio_sda)
		gpiod_set_raw_value(iop3xx_adap->gpio_sda, 0);

	/* NB SR bits not same position as CR IE bits :-( */
	iop3xx_adap->SR_enabled =
		IOP3XX_ISR_ALD | IOP3XX_ISR_BERRD |
		IOP3XX_ISR_RXFULL | IOP3XX_ISR_TXEMPTY;

	cr |= IOP3XX_ICR_ALD_IE | IOP3XX_ICR_BERR_IE |
		IOP3XX_ICR_RXFULL_IE | IOP3XX_ICR_TXEMPTY_IE;

	__raw_ग_लिखोl(cr, iop3xx_adap->ioaddr + CR_OFFSET);
पूर्ण

अटल व्योम
iop3xx_i2c_transaction_cleanup(काष्ठा i2c_algo_iop3xx_data *iop3xx_adap)
अणु
	अचिन्हित दीर्घ cr = __raw_पढ़ोl(iop3xx_adap->ioaddr + CR_OFFSET);

	cr &= ~(IOP3XX_ICR_MSTART | IOP3XX_ICR_TBYTE |
		IOP3XX_ICR_MSTOP | IOP3XX_ICR_SCLEN);

	__raw_ग_लिखोl(cr, iop3xx_adap->ioaddr + CR_OFFSET);
पूर्ण

/*
 * NB: the handler has to clear the source of the पूर्णांकerrupt!
 * Then it passes the SR flags of पूर्णांकerest to BH via adap data
 */
अटल irqवापस_t
iop3xx_i2c_irq_handler(पूर्णांक this_irq, व्योम *dev_id)
अणु
	काष्ठा i2c_algo_iop3xx_data *iop3xx_adap = dev_id;
	u32 sr = __raw_पढ़ोl(iop3xx_adap->ioaddr + SR_OFFSET);

	अगर ((sr &= iop3xx_adap->SR_enabled)) अणु
		__raw_ग_लिखोl(sr, iop3xx_adap->ioaddr + SR_OFFSET);
		iop3xx_adap->SR_received |= sr;
		wake_up_पूर्णांकerruptible(&iop3xx_adap->रुकोq);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/* check all error conditions, clear them , report most important */
अटल पूर्णांक
iop3xx_i2c_error(u32 sr)
अणु
	पूर्णांक rc = 0;

	अगर ((sr & IOP3XX_ISR_BERRD)) अणु
		अगर (!rc)
			rc = -I2C_ERR_BERR;
	पूर्ण
	अगर ((sr & IOP3XX_ISR_ALD)) अणु
		अगर (!rc)
			rc = -I2C_ERR_ALD;
	पूर्ण
	वापस rc;
पूर्ण

अटल अंतरभूत u32
iop3xx_i2c_get_srstat(काष्ठा i2c_algo_iop3xx_data *iop3xx_adap)
अणु
	अचिन्हित दीर्घ flags;
	u32 sr;

	spin_lock_irqsave(&iop3xx_adap->lock, flags);
	sr = iop3xx_adap->SR_received;
	iop3xx_adap->SR_received = 0;
	spin_unlock_irqrestore(&iop3xx_adap->lock, flags);

	वापस sr;
पूर्ण

/*
 * sleep until पूर्णांकerrupted, then recover and analyse the SR
 * saved by handler
 */
प्रकार पूर्णांक (*compare_func)(अचिन्हित test, अचिन्हित mask);
/* वापसs 1 on correct comparison */

अटल पूर्णांक
iop3xx_i2c_रुको_event(काष्ठा i2c_algo_iop3xx_data *iop3xx_adap,
			  अचिन्हित flags, अचिन्हित *status,
			  compare_func compare)
अणु
	अचिन्हित sr = 0;
	पूर्णांक पूर्णांकerrupted;
	पूर्णांक करोne;
	पूर्णांक rc = 0;

	करो अणु
		पूर्णांकerrupted = रुको_event_पूर्णांकerruptible_समयout (
			iop3xx_adap->रुकोq,
			(करोne = compare(sr = iop3xx_i2c_get_srstat(iop3xx_adap), flags)),
			1 * HZ
			);
		अगर ((rc = iop3xx_i2c_error(sr)) < 0) अणु
			*status = sr;
			वापस rc;
		पूर्ण अन्यथा अगर (!पूर्णांकerrupted) अणु
			*status = sr;
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण जबतक (!करोne);

	*status = sr;

	वापस 0;
पूर्ण

/*
 * Concrete compare_funcs
 */
अटल पूर्णांक
all_bits_clear(अचिन्हित test, अचिन्हित mask)
अणु
	वापस (test & mask) == 0;
पूर्ण

अटल पूर्णांक
any_bits_set(अचिन्हित test, अचिन्हित mask)
अणु
	वापस (test & mask) != 0;
पूर्ण

अटल पूर्णांक
iop3xx_i2c_रुको_tx_करोne(काष्ठा i2c_algo_iop3xx_data *iop3xx_adap, पूर्णांक *status)
अणु
	वापस iop3xx_i2c_रुको_event(
		iop3xx_adap,
		IOP3XX_ISR_TXEMPTY | IOP3XX_ISR_ALD | IOP3XX_ISR_BERRD,
		status, any_bits_set);
पूर्ण

अटल पूर्णांक
iop3xx_i2c_रुको_rx_करोne(काष्ठा i2c_algo_iop3xx_data *iop3xx_adap, पूर्णांक *status)
अणु
	वापस iop3xx_i2c_रुको_event(
		iop3xx_adap,
		IOP3XX_ISR_RXFULL | IOP3XX_ISR_ALD | IOP3XX_ISR_BERRD,
		status,	any_bits_set);
पूर्ण

अटल पूर्णांक
iop3xx_i2c_रुको_idle(काष्ठा i2c_algo_iop3xx_data *iop3xx_adap, पूर्णांक *status)
अणु
	वापस iop3xx_i2c_रुको_event(
		iop3xx_adap, IOP3XX_ISR_UNITBUSY, status, all_bits_clear);
पूर्ण

अटल पूर्णांक
iop3xx_i2c_send_target_addr(काष्ठा i2c_algo_iop3xx_data *iop3xx_adap,
				काष्ठा i2c_msg *msg)
अणु
	अचिन्हित दीर्घ cr = __raw_पढ़ोl(iop3xx_adap->ioaddr + CR_OFFSET);
	पूर्णांक status;
	पूर्णांक rc;

	/* aव्योम writing to my slave address (hangs on 80331),
	 * क्रमbidden in Intel developer manual
	 */
	अगर (msg->addr == MYSAR) अणु
		वापस -EBUSY;
	पूर्ण

	__raw_ग_लिखोl(iic_cook_addr(msg), iop3xx_adap->ioaddr + DBR_OFFSET);

	cr &= ~(IOP3XX_ICR_MSTOP | IOP3XX_ICR_NACK);
	cr |= IOP3XX_ICR_MSTART | IOP3XX_ICR_TBYTE;

	__raw_ग_लिखोl(cr, iop3xx_adap->ioaddr + CR_OFFSET);
	rc = iop3xx_i2c_रुको_tx_करोne(iop3xx_adap, &status);

	वापस rc;
पूर्ण

अटल पूर्णांक
iop3xx_i2c_ग_लिखो_byte(काष्ठा i2c_algo_iop3xx_data *iop3xx_adap, अक्षर byte,
				पूर्णांक stop)
अणु
	अचिन्हित दीर्घ cr = __raw_पढ़ोl(iop3xx_adap->ioaddr + CR_OFFSET);
	पूर्णांक status;
	पूर्णांक rc = 0;

	__raw_ग_लिखोl(byte, iop3xx_adap->ioaddr + DBR_OFFSET);
	cr &= ~IOP3XX_ICR_MSTART;
	अगर (stop) अणु
		cr |= IOP3XX_ICR_MSTOP;
	पूर्ण अन्यथा अणु
		cr &= ~IOP3XX_ICR_MSTOP;
	पूर्ण
	cr |= IOP3XX_ICR_TBYTE;
	__raw_ग_लिखोl(cr, iop3xx_adap->ioaddr + CR_OFFSET);
	rc = iop3xx_i2c_रुको_tx_करोne(iop3xx_adap, &status);

	वापस rc;
पूर्ण

अटल पूर्णांक
iop3xx_i2c_पढ़ो_byte(काष्ठा i2c_algo_iop3xx_data *iop3xx_adap, अक्षर *byte,
				पूर्णांक stop)
अणु
	अचिन्हित दीर्घ cr = __raw_पढ़ोl(iop3xx_adap->ioaddr + CR_OFFSET);
	पूर्णांक status;
	पूर्णांक rc = 0;

	cr &= ~IOP3XX_ICR_MSTART;

	अगर (stop) अणु
		cr |= IOP3XX_ICR_MSTOP | IOP3XX_ICR_NACK;
	पूर्ण अन्यथा अणु
		cr &= ~(IOP3XX_ICR_MSTOP | IOP3XX_ICR_NACK);
	पूर्ण
	cr |= IOP3XX_ICR_TBYTE;
	__raw_ग_लिखोl(cr, iop3xx_adap->ioaddr + CR_OFFSET);

	rc = iop3xx_i2c_रुको_rx_करोne(iop3xx_adap, &status);

	*byte = __raw_पढ़ोl(iop3xx_adap->ioaddr + DBR_OFFSET);

	वापस rc;
पूर्ण

अटल पूर्णांक
iop3xx_i2c_ग_लिखोbytes(काष्ठा i2c_adapter *i2c_adap, स्थिर अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा i2c_algo_iop3xx_data *iop3xx_adap = i2c_adap->algo_data;
	पूर्णांक ii;
	पूर्णांक rc = 0;

	क्रम (ii = 0; rc == 0 && ii != count; ++ii)
		rc = iop3xx_i2c_ग_लिखो_byte(iop3xx_adap, buf[ii], ii == count-1);
	वापस rc;
पूर्ण

अटल पूर्णांक
iop3xx_i2c_पढ़ोbytes(काष्ठा i2c_adapter *i2c_adap, अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा i2c_algo_iop3xx_data *iop3xx_adap = i2c_adap->algo_data;
	पूर्णांक ii;
	पूर्णांक rc = 0;

	क्रम (ii = 0; rc == 0 && ii != count; ++ii)
		rc = iop3xx_i2c_पढ़ो_byte(iop3xx_adap, &buf[ii], ii == count-1);

	वापस rc;
पूर्ण

/*
 * Description:  This function implements combined transactions.  Combined
 * transactions consist of combinations of पढ़ोing and writing blocks of data.
 * FROM THE SAME ADDRESS
 * Each transfer (i.e. a पढ़ो or a ग_लिखो) is separated by a repeated start
 * condition.
 */
अटल पूर्णांक
iop3xx_i2c_handle_msg(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg *pmsg)
अणु
	काष्ठा i2c_algo_iop3xx_data *iop3xx_adap = i2c_adap->algo_data;
	पूर्णांक rc;

	rc = iop3xx_i2c_send_target_addr(iop3xx_adap, pmsg);
	अगर (rc < 0) अणु
		वापस rc;
	पूर्ण

	अगर ((pmsg->flags&I2C_M_RD)) अणु
		वापस iop3xx_i2c_पढ़ोbytes(i2c_adap, pmsg->buf, pmsg->len);
	पूर्ण अन्यथा अणु
		वापस iop3xx_i2c_ग_लिखोbytes(i2c_adap, pmsg->buf, pmsg->len);
	पूर्ण
पूर्ण

/*
 * master_xfer() - मुख्य पढ़ो/ग_लिखो entry
 */
अटल पूर्णांक
iop3xx_i2c_master_xfer(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg *msgs,
				पूर्णांक num)
अणु
	काष्ठा i2c_algo_iop3xx_data *iop3xx_adap = i2c_adap->algo_data;
	पूर्णांक im = 0;
	पूर्णांक ret = 0;
	पूर्णांक status;

	iop3xx_i2c_रुको_idle(iop3xx_adap, &status);
	iop3xx_i2c_reset(iop3xx_adap);
	iop3xx_i2c_enable(iop3xx_adap);

	क्रम (im = 0; ret == 0 && im != num; im++) अणु
		ret = iop3xx_i2c_handle_msg(i2c_adap, &msgs[im]);
	पूर्ण

	iop3xx_i2c_transaction_cleanup(iop3xx_adap);

	अगर (ret)
		वापस ret;

	वापस im;
पूर्ण

अटल u32
iop3xx_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm iop3xx_i2c_algo = अणु
	.master_xfer	= iop3xx_i2c_master_xfer,
	.functionality	= iop3xx_i2c_func,
पूर्ण;

अटल पूर्णांक
iop3xx_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_adapter *padapter = platक्रमm_get_drvdata(pdev);
	काष्ठा i2c_algo_iop3xx_data *adapter_data =
		(काष्ठा i2c_algo_iop3xx_data *)padapter->algo_data;
	काष्ठा resource *res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अचिन्हित दीर्घ cr = __raw_पढ़ोl(adapter_data->ioaddr + CR_OFFSET);

	/*
	 * Disable the actual HW unit
	 */
	cr &= ~(IOP3XX_ICR_ALD_IE | IOP3XX_ICR_BERR_IE |
		IOP3XX_ICR_RXFULL_IE | IOP3XX_ICR_TXEMPTY_IE);
	__raw_ग_लिखोl(cr, adapter_data->ioaddr + CR_OFFSET);

	iounmap(adapter_data->ioaddr);
	release_mem_region(res->start, IOP3XX_I2C_IO_SIZE);
	kमुक्त(adapter_data);
	kमुक्त(padapter);

	वापस 0;
पूर्ण

अटल पूर्णांक
iop3xx_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	पूर्णांक ret, irq;
	काष्ठा i2c_adapter *new_adapter;
	काष्ठा i2c_algo_iop3xx_data *adapter_data;

	new_adapter = kzalloc(माप(काष्ठा i2c_adapter), GFP_KERNEL);
	अगर (!new_adapter) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	adapter_data = kzalloc(माप(काष्ठा i2c_algo_iop3xx_data), GFP_KERNEL);
	अगर (!adapter_data) अणु
		ret = -ENOMEM;
		जाओ मुक्त_adapter;
	पूर्ण

	adapter_data->gpio_scl = devm_gpiod_get_optional(&pdev->dev,
							 "scl",
							 GPIOD_ASIS);
	अगर (IS_ERR(adapter_data->gpio_scl)) अणु
		ret = PTR_ERR(adapter_data->gpio_scl);
		जाओ मुक्त_both;
	पूर्ण
	adapter_data->gpio_sda = devm_gpiod_get_optional(&pdev->dev,
							 "sda",
							 GPIOD_ASIS);
	अगर (IS_ERR(adapter_data->gpio_sda)) अणु
		ret = PTR_ERR(adapter_data->gpio_sda);
		जाओ मुक्त_both;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		ret = -ENODEV;
		जाओ मुक्त_both;
	पूर्ण

	अगर (!request_mem_region(res->start, IOP3XX_I2C_IO_SIZE, pdev->name)) अणु
		ret = -EBUSY;
		जाओ मुक्त_both;
	पूर्ण

	/* set the adapter क्रमागतeration # */
	adapter_data->id = i2c_id++;

	adapter_data->ioaddr = ioremap(res->start, IOP3XX_I2C_IO_SIZE);
	अगर (!adapter_data->ioaddr) अणु
		ret = -ENOMEM;
		जाओ release_region;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = -ENXIO;
		जाओ unmap;
	पूर्ण
	ret = request_irq(irq, iop3xx_i2c_irq_handler, 0,
				pdev->name, adapter_data);

	अगर (ret) अणु
		ret = -EIO;
		जाओ unmap;
	पूर्ण

	स_नकल(new_adapter->name, pdev->name, म_माप(pdev->name));
	new_adapter->owner = THIS_MODULE;
	new_adapter->class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	new_adapter->dev.parent = &pdev->dev;
	new_adapter->dev.of_node = pdev->dev.of_node;
	new_adapter->nr = pdev->id;

	/*
	 * Default values...should these come in from board code?
	 */
	new_adapter->समयout = HZ;
	new_adapter->algo = &iop3xx_i2c_algo;

	init_रुकोqueue_head(&adapter_data->रुकोq);
	spin_lock_init(&adapter_data->lock);

	iop3xx_i2c_reset(adapter_data);
	iop3xx_i2c_enable(adapter_data);

	platक्रमm_set_drvdata(pdev, new_adapter);
	new_adapter->algo_data = adapter_data;

	i2c_add_numbered_adapter(new_adapter);

	वापस 0;

unmap:
	iounmap(adapter_data->ioaddr);

release_region:
	release_mem_region(res->start, IOP3XX_I2C_IO_SIZE);

मुक्त_both:
	kमुक्त(adapter_data);

मुक्त_adapter:
	kमुक्त(new_adapter);

out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id i2c_iop3xx_match[] = अणु
	अणु .compatible = "intel,iop3xx-i2c", पूर्ण,
	अणु .compatible = "intel,ixp4xx-i2c", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_iop3xx_match);

अटल काष्ठा platक्रमm_driver iop3xx_i2c_driver = अणु
	.probe		= iop3xx_i2c_probe,
	.हटाओ		= iop3xx_i2c_हटाओ,
	.driver		= अणु
		.name	= "IOP3xx-I2C",
		.of_match_table = i2c_iop3xx_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(iop3xx_i2c_driver);

MODULE_AUTHOR("D-TACQ Solutions Ltd <www.d-tacq.com>");
MODULE_DESCRIPTION("IOP3xx iic algorithm and driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:IOP3xx-I2C");
