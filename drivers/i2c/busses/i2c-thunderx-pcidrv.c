<शैली गुरु>
/*
 * Cavium ThunderX i2c driver.
 *
 * Copyright (C) 2015,2016 Cavium Inc.
 * Authors: Fred Martin <fmartin@caviumnetworks.com>
 *	    Jan Glauber <jglauber@cavium.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-smbus.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pci.h>

#समावेश "i2c-octeon-core.h"

#घोषणा DRV_NAME "i2c-thunderx"

#घोषणा PCI_DEVICE_ID_THUNDER_TWSI	0xa012

#घोषणा SYS_FREQ_DEFAULT		700000000

#घोषणा TWSI_INT_ENA_W1C		0x1028
#घोषणा TWSI_INT_ENA_W1S		0x1030

/*
 * Enable the CORE पूर्णांकerrupt.
 * The पूर्णांकerrupt will be निश्चितed when there is non-STAT_IDLE state in the
 * SW_TWSI_EOP_TWSI_STAT रेजिस्टर.
 */
अटल व्योम thunder_i2c_पूर्णांक_enable(काष्ठा octeon_i2c *i2c)
अणु
	octeon_i2c_ग_लिखोq_flush(TWSI_INT_CORE_INT,
				i2c->twsi_base + TWSI_INT_ENA_W1S);
पूर्ण

/*
 * Disable the CORE पूर्णांकerrupt.
 */
अटल व्योम thunder_i2c_पूर्णांक_disable(काष्ठा octeon_i2c *i2c)
अणु
	octeon_i2c_ग_लिखोq_flush(TWSI_INT_CORE_INT,
				i2c->twsi_base + TWSI_INT_ENA_W1C);
पूर्ण

अटल व्योम thunder_i2c_hlc_पूर्णांक_enable(काष्ठा octeon_i2c *i2c)
अणु
	octeon_i2c_ग_लिखोq_flush(TWSI_INT_ST_INT | TWSI_INT_TS_INT,
				i2c->twsi_base + TWSI_INT_ENA_W1S);
पूर्ण

अटल व्योम thunder_i2c_hlc_पूर्णांक_disable(काष्ठा octeon_i2c *i2c)
अणु
	octeon_i2c_ग_लिखोq_flush(TWSI_INT_ST_INT | TWSI_INT_TS_INT,
				i2c->twsi_base + TWSI_INT_ENA_W1C);
पूर्ण

अटल u32 thunderx_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK) |
	       I2C_FUNC_SMBUS_READ_BLOCK_DATA | I2C_SMBUS_BLOCK_PROC_CALL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm thunderx_i2c_algo = अणु
	.master_xfer = octeon_i2c_xfer,
	.functionality = thunderx_i2c_functionality,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter thunderx_i2c_ops = अणु
	.owner	= THIS_MODULE,
	.name	= "ThunderX adapter",
	.algo	= &thunderx_i2c_algo,
पूर्ण;

अटल व्योम thunder_i2c_घड़ी_enable(काष्ठा device *dev, काष्ठा octeon_i2c *i2c)
अणु
	पूर्णांक ret;

	अगर (acpi_disabled) अणु
		/* DT */
		i2c->clk = clk_get(dev, शून्य);
		अगर (IS_ERR(i2c->clk)) अणु
			i2c->clk = शून्य;
			जाओ skip;
		पूर्ण

		ret = clk_prepare_enable(i2c->clk);
		अगर (ret)
			जाओ skip;
		i2c->sys_freq = clk_get_rate(i2c->clk);
	पूर्ण अन्यथा अणु
		/* ACPI */
		device_property_पढ़ो_u32(dev, "sclk", &i2c->sys_freq);
	पूर्ण

skip:
	अगर (!i2c->sys_freq)
		i2c->sys_freq = SYS_FREQ_DEFAULT;
पूर्ण

अटल व्योम thunder_i2c_घड़ी_disable(काष्ठा device *dev, काष्ठा clk *clk)
अणु
	अगर (!clk)
		वापस;
	clk_disable_unprepare(clk);
	clk_put(clk);
पूर्ण

अटल पूर्णांक thunder_i2c_smbus_setup_of(काष्ठा octeon_i2c *i2c,
				      काष्ठा device_node *node)
अणु
	काष्ठा i2c_client *ara;

	अगर (!node)
		वापस -EINVAL;

	i2c->alert_data.irq = irq_of_parse_and_map(node, 0);
	अगर (!i2c->alert_data.irq)
		वापस -EINVAL;

	ara = i2c_new_smbus_alert_device(&i2c->adap, &i2c->alert_data);
	अगर (IS_ERR(ara))
		वापस PTR_ERR(ara);

	i2c->ara = ara;

	वापस 0;
पूर्ण

अटल पूर्णांक thunder_i2c_smbus_setup(काष्ठा octeon_i2c *i2c,
				   काष्ठा device_node *node)
अणु
	/* TODO: ACPI support */
	अगर (!acpi_disabled)
		वापस -EOPNOTSUPP;

	वापस thunder_i2c_smbus_setup_of(i2c, node);
पूर्ण

अटल व्योम thunder_i2c_smbus_हटाओ(काष्ठा octeon_i2c *i2c)
अणु
	i2c_unरेजिस्टर_device(i2c->ara);
पूर्ण

अटल पूर्णांक thunder_i2c_probe_pci(काष्ठा pci_dev *pdev,
				 स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा octeon_i2c *i2c;
	पूर्णांक ret;

	i2c = devm_kzalloc(dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	i2c->roff.sw_twsi = 0x1000;
	i2c->roff.twsi_पूर्णांक = 0x1010;
	i2c->roff.sw_twsi_ext = 0x1018;

	i2c->dev = dev;
	pci_set_drvdata(pdev, i2c);
	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	ret = pci_request_regions(pdev, DRV_NAME);
	अगर (ret)
		वापस ret;

	i2c->twsi_base = pcim_iomap(pdev, 0, pci_resource_len(pdev, 0));
	अगर (!i2c->twsi_base)
		वापस -EINVAL;

	thunder_i2c_घड़ी_enable(dev, i2c);
	ret = device_property_पढ़ो_u32(dev, "clock-frequency", &i2c->twsi_freq);
	अगर (ret)
		i2c->twsi_freq = I2C_MAX_STANDARD_MODE_FREQ;

	init_रुकोqueue_head(&i2c->queue);

	i2c->पूर्णांक_enable = thunder_i2c_पूर्णांक_enable;
	i2c->पूर्णांक_disable = thunder_i2c_पूर्णांक_disable;
	i2c->hlc_पूर्णांक_enable = thunder_i2c_hlc_पूर्णांक_enable;
	i2c->hlc_पूर्णांक_disable = thunder_i2c_hlc_पूर्णांक_disable;

	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSIX);
	अगर (ret < 0)
		जाओ error;

	ret = devm_request_irq(dev, pci_irq_vector(pdev, 0), octeon_i2c_isr, 0,
			       DRV_NAME, i2c);
	अगर (ret)
		जाओ error;

	ret = octeon_i2c_init_lowlevel(i2c);
	अगर (ret)
		जाओ error;

	octeon_i2c_set_घड़ी(i2c);

	i2c->adap = thunderx_i2c_ops;
	i2c->adap.retries = 5;
	i2c->adap.class = I2C_CLASS_HWMON;
	i2c->adap.bus_recovery_info = &octeon_i2c_recovery_info;
	i2c->adap.dev.parent = dev;
	i2c->adap.dev.of_node = pdev->dev.of_node;
	snम_लिखो(i2c->adap.name, माप(i2c->adap.name),
		 "Cavium ThunderX i2c adapter at %s", dev_name(dev));
	i2c_set_adapdata(&i2c->adap, i2c);

	ret = i2c_add_adapter(&i2c->adap);
	अगर (ret)
		जाओ error;

	dev_info(i2c->dev, "Probed. Set system clock to %u\n", i2c->sys_freq);

	ret = thunder_i2c_smbus_setup(i2c, pdev->dev.of_node);
	अगर (ret)
		dev_info(dev, "SMBUS alert not active on this bus\n");

	वापस 0;

error:
	thunder_i2c_घड़ी_disable(dev, i2c->clk);
	वापस ret;
पूर्ण

अटल व्योम thunder_i2c_हटाओ_pci(काष्ठा pci_dev *pdev)
अणु
	काष्ठा octeon_i2c *i2c = pci_get_drvdata(pdev);

	thunder_i2c_smbus_हटाओ(i2c);
	thunder_i2c_घड़ी_disable(&pdev->dev, i2c->clk);
	i2c_del_adapter(&i2c->adap);
पूर्ण

अटल स्थिर काष्ठा pci_device_id thunder_i2c_pci_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVICE_ID_THUNDER_TWSI) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, thunder_i2c_pci_id_table);

अटल काष्ठा pci_driver thunder_i2c_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= thunder_i2c_pci_id_table,
	.probe		= thunder_i2c_probe_pci,
	.हटाओ		= thunder_i2c_हटाओ_pci,
पूर्ण;

module_pci_driver(thunder_i2c_pci_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fred Martin <fmartin@caviumnetworks.com>");
MODULE_DESCRIPTION("I2C-Bus adapter for Cavium ThunderX SOC");
