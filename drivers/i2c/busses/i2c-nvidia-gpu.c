<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Nvidia GPU I2C controller Driver
 *
 * Copyright (C) 2018 NVIDIA Corporation. All rights reserved.
 * Author: Ajay Gupta <ajayg@nvidia.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <यंत्र/unaligned.h>

/* I2C definitions */
#घोषणा I2C_MST_CNTL				0x00
#घोषणा I2C_MST_CNTL_GEN_START			BIT(0)
#घोषणा I2C_MST_CNTL_GEN_STOP			BIT(1)
#घोषणा I2C_MST_CNTL_CMD_READ			(1 << 2)
#घोषणा I2C_MST_CNTL_CMD_WRITE			(2 << 2)
#घोषणा I2C_MST_CNTL_BURST_SIZE_SHIFT		6
#घोषणा I2C_MST_CNTL_GEN_NACK			BIT(28)
#घोषणा I2C_MST_CNTL_STATUS			GENMASK(30, 29)
#घोषणा I2C_MST_CNTL_STATUS_OKAY		(0 << 29)
#घोषणा I2C_MST_CNTL_STATUS_NO_ACK		(1 << 29)
#घोषणा I2C_MST_CNTL_STATUS_TIMEOUT		(2 << 29)
#घोषणा I2C_MST_CNTL_STATUS_BUS_BUSY		(3 << 29)
#घोषणा I2C_MST_CNTL_CYCLE_TRIGGER		BIT(31)

#घोषणा I2C_MST_ADDR				0x04

#घोषणा I2C_MST_I2C0_TIMING				0x08
#घोषणा I2C_MST_I2C0_TIMING_SCL_PERIOD_100KHZ		0x10e
#घोषणा I2C_MST_I2C0_TIMING_TIMEOUT_CLK_CNT		16
#घोषणा I2C_MST_I2C0_TIMING_TIMEOUT_CLK_CNT_MAX		255
#घोषणा I2C_MST_I2C0_TIMING_TIMEOUT_CHECK		BIT(24)

#घोषणा I2C_MST_DATA					0x0c

#घोषणा I2C_MST_HYBRID_PADCTL				0x20
#घोषणा I2C_MST_HYBRID_PADCTL_MODE_I2C			BIT(0)
#घोषणा I2C_MST_HYBRID_PADCTL_I2C_SCL_INPUT_RCV		BIT(14)
#घोषणा I2C_MST_HYBRID_PADCTL_I2C_SDA_INPUT_RCV		BIT(15)

काष्ठा gpu_i2c_dev अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा i2c_adapter adapter;
	काष्ठा i2c_board_info *gpu_ccgx_ucsi;
	काष्ठा i2c_client *ccgx_client;
पूर्ण;

अटल व्योम gpu_enable_i2c_bus(काष्ठा gpu_i2c_dev *i2cd)
अणु
	u32 val;

	/* enable I2C */
	val = पढ़ोl(i2cd->regs + I2C_MST_HYBRID_PADCTL);
	val |= I2C_MST_HYBRID_PADCTL_MODE_I2C |
		I2C_MST_HYBRID_PADCTL_I2C_SCL_INPUT_RCV |
		I2C_MST_HYBRID_PADCTL_I2C_SDA_INPUT_RCV;
	ग_लिखोl(val, i2cd->regs + I2C_MST_HYBRID_PADCTL);

	/* enable 100KHZ mode */
	val = I2C_MST_I2C0_TIMING_SCL_PERIOD_100KHZ;
	val |= (I2C_MST_I2C0_TIMING_TIMEOUT_CLK_CNT_MAX
	    << I2C_MST_I2C0_TIMING_TIMEOUT_CLK_CNT);
	val |= I2C_MST_I2C0_TIMING_TIMEOUT_CHECK;
	ग_लिखोl(val, i2cd->regs + I2C_MST_I2C0_TIMING);
पूर्ण

अटल पूर्णांक gpu_i2c_check_status(काष्ठा gpu_i2c_dev *i2cd)
अणु
	u32 val;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout(i2cd->regs + I2C_MST_CNTL, val,
				 !(val & I2C_MST_CNTL_CYCLE_TRIGGER) ||
				 (val & I2C_MST_CNTL_STATUS) != I2C_MST_CNTL_STATUS_BUS_BUSY,
				 500, 1000 * USEC_PER_MSEC);

	अगर (ret) अणु
		dev_err(i2cd->dev, "i2c timeout error %x\n", val);
		वापस -ETIMEDOUT;
	पूर्ण

	val = पढ़ोl(i2cd->regs + I2C_MST_CNTL);
	चयन (val & I2C_MST_CNTL_STATUS) अणु
	हाल I2C_MST_CNTL_STATUS_OKAY:
		वापस 0;
	हाल I2C_MST_CNTL_STATUS_NO_ACK:
		वापस -ENXIO;
	हाल I2C_MST_CNTL_STATUS_TIMEOUT:
		वापस -ETIMEDOUT;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक gpu_i2c_पढ़ो(काष्ठा gpu_i2c_dev *i2cd, u8 *data, u16 len)
अणु
	पूर्णांक status;
	u32 val;

	val = I2C_MST_CNTL_GEN_START | I2C_MST_CNTL_CMD_READ |
		(len << I2C_MST_CNTL_BURST_SIZE_SHIFT) |
		I2C_MST_CNTL_CYCLE_TRIGGER | I2C_MST_CNTL_GEN_NACK;
	ग_लिखोl(val, i2cd->regs + I2C_MST_CNTL);

	status = gpu_i2c_check_status(i2cd);
	अगर (status < 0)
		वापस status;

	val = पढ़ोl(i2cd->regs + I2C_MST_DATA);
	चयन (len) अणु
	हाल 1:
		data[0] = val;
		अवरोध;
	हाल 2:
		put_unaligned_be16(val, data);
		अवरोध;
	हाल 3:
		put_unaligned_be24(val, data);
		अवरोध;
	हाल 4:
		put_unaligned_be32(val, data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक gpu_i2c_start(काष्ठा gpu_i2c_dev *i2cd)
अणु
	ग_लिखोl(I2C_MST_CNTL_GEN_START, i2cd->regs + I2C_MST_CNTL);
	वापस gpu_i2c_check_status(i2cd);
पूर्ण

अटल पूर्णांक gpu_i2c_stop(काष्ठा gpu_i2c_dev *i2cd)
अणु
	ग_लिखोl(I2C_MST_CNTL_GEN_STOP, i2cd->regs + I2C_MST_CNTL);
	वापस gpu_i2c_check_status(i2cd);
पूर्ण

अटल पूर्णांक gpu_i2c_ग_लिखो(काष्ठा gpu_i2c_dev *i2cd, u8 data)
अणु
	u32 val;

	ग_लिखोl(data, i2cd->regs + I2C_MST_DATA);

	val = I2C_MST_CNTL_CMD_WRITE | (1 << I2C_MST_CNTL_BURST_SIZE_SHIFT);
	ग_लिखोl(val, i2cd->regs + I2C_MST_CNTL);

	वापस gpu_i2c_check_status(i2cd);
पूर्ण

अटल पूर्णांक gpu_i2c_master_xfer(काष्ठा i2c_adapter *adap,
			       काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा gpu_i2c_dev *i2cd = i2c_get_adapdata(adap);
	पूर्णांक status, status2;
	bool send_stop = true;
	पूर्णांक i, j;

	/*
	 * The controller supports maximum 4 byte पढ़ो due to known
	 * limitation of sending STOP after every पढ़ो.
	 */
	pm_runसमय_get_sync(i2cd->dev);
	क्रम (i = 0; i < num; i++) अणु
		अगर (msgs[i].flags & I2C_M_RD) अणु
			/* program client address beक्रमe starting पढ़ो */
			ग_लिखोl(msgs[i].addr, i2cd->regs + I2C_MST_ADDR);
			/* gpu_i2c_पढ़ो has implicit start */
			status = gpu_i2c_पढ़ो(i2cd, msgs[i].buf, msgs[i].len);
			अगर (status < 0)
				जाओ निकास;
		पूर्ण अन्यथा अणु
			u8 addr = i2c_8bit_addr_from_msg(msgs + i);

			status = gpu_i2c_start(i2cd);
			अगर (status < 0) अणु
				अगर (i == 0)
					send_stop = false;
				जाओ निकास;
			पूर्ण

			status = gpu_i2c_ग_लिखो(i2cd, addr);
			अगर (status < 0)
				जाओ निकास;

			क्रम (j = 0; j < msgs[i].len; j++) अणु
				status = gpu_i2c_ग_लिखो(i2cd, msgs[i].buf[j]);
				अगर (status < 0)
					जाओ निकास;
			पूर्ण
		पूर्ण
	पूर्ण
	send_stop = false;
	status = gpu_i2c_stop(i2cd);
	अगर (status < 0)
		जाओ निकास;

	status = i;
निकास:
	अगर (send_stop) अणु
		status2 = gpu_i2c_stop(i2cd);
		अगर (status2 < 0)
			dev_err(i2cd->dev, "i2c stop failed %d\n", status2);
	पूर्ण
	pm_runसमय_mark_last_busy(i2cd->dev);
	pm_runसमय_put_स्वतःsuspend(i2cd->dev);
	वापस status;
पूर्ण

अटल स्थिर काष्ठा i2c_adapter_quirks gpu_i2c_quirks = अणु
	.max_पढ़ो_len = 4,
	.max_comb_2nd_msg_len = 4,
	.flags = I2C_AQ_COMB_WRITE_THEN_READ,
पूर्ण;

अटल u32 gpu_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm gpu_i2c_algorithm = अणु
	.master_xfer	= gpu_i2c_master_xfer,
	.functionality	= gpu_i2c_functionality,
पूर्ण;

/*
 * This driver is क्रम Nvidia GPU cards with USB Type-C पूर्णांकerface.
 * We want to identअगरy the cards using venकरोr ID and class code only
 * to aव्योम dependency of adding product id क्रम any new card which
 * requires this driver.
 * Currently there is no class code defined क्रम UCSI device over PCI
 * so using UNKNOWN class क्रम now and it will be updated when UCSI
 * over PCI माला_लो a class code.
 * There is no other NVIDIA cards with UNKNOWN class code. Even अगर the
 * driver माला_लो loaded क्रम an undesired card then eventually i2c_पढ़ो()
 * (initiated from UCSI i2c_client) will समयout or UCSI commands will
 * समयout.
 */
#घोषणा PCI_CLASS_SERIAL_UNKNOWN	0x0c80
अटल स्थिर काष्ठा pci_device_id gpu_i2c_ids[] = अणु
	अणु PCI_VENDOR_ID_NVIDIA, PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID,
		PCI_CLASS_SERIAL_UNKNOWN << 8, 0xffffff00पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, gpu_i2c_ids);

अटल स्थिर काष्ठा property_entry ccgx_props[] = अणु
	/* Use FW built क्रम NVIDIA (nv) only */
	PROPERTY_ENTRY_U16("ccgx,firmware-build", ('n' << 8) | 'v'),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node ccgx_node = अणु
	.properties = ccgx_props,
पूर्ण;

अटल पूर्णांक gpu_populate_client(काष्ठा gpu_i2c_dev *i2cd, पूर्णांक irq)
अणु
	i2cd->gpu_ccgx_ucsi = devm_kzalloc(i2cd->dev,
					   माप(*i2cd->gpu_ccgx_ucsi),
					   GFP_KERNEL);
	अगर (!i2cd->gpu_ccgx_ucsi)
		वापस -ENOMEM;

	strlcpy(i2cd->gpu_ccgx_ucsi->type, "ccgx-ucsi",
		माप(i2cd->gpu_ccgx_ucsi->type));
	i2cd->gpu_ccgx_ucsi->addr = 0x8;
	i2cd->gpu_ccgx_ucsi->irq = irq;
	i2cd->gpu_ccgx_ucsi->swnode = &ccgx_node;
	i2cd->ccgx_client = i2c_new_client_device(&i2cd->adapter, i2cd->gpu_ccgx_ucsi);
	वापस PTR_ERR_OR_ZERO(i2cd->ccgx_client);
पूर्ण

अटल पूर्णांक gpu_i2c_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा gpu_i2c_dev *i2cd;
	पूर्णांक status;

	i2cd = devm_kzalloc(&pdev->dev, माप(*i2cd), GFP_KERNEL);
	अगर (!i2cd)
		वापस -ENOMEM;

	i2cd->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, i2cd);

	status = pcim_enable_device(pdev);
	अगर (status < 0) अणु
		dev_err(&pdev->dev, "pcim_enable_device failed %d\n", status);
		वापस status;
	पूर्ण

	pci_set_master(pdev);

	i2cd->regs = pcim_iomap(pdev, 0, 0);
	अगर (!i2cd->regs) अणु
		dev_err(&pdev->dev, "pcim_iomap failed\n");
		वापस -ENOMEM;
	पूर्ण

	status = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSI);
	अगर (status < 0) अणु
		dev_err(&pdev->dev, "pci_alloc_irq_vectors err %d\n", status);
		वापस status;
	पूर्ण

	gpu_enable_i2c_bus(i2cd);

	i2c_set_adapdata(&i2cd->adapter, i2cd);
	i2cd->adapter.owner = THIS_MODULE;
	strlcpy(i2cd->adapter.name, "NVIDIA GPU I2C adapter",
		माप(i2cd->adapter.name));
	i2cd->adapter.algo = &gpu_i2c_algorithm;
	i2cd->adapter.quirks = &gpu_i2c_quirks;
	i2cd->adapter.dev.parent = &pdev->dev;
	status = i2c_add_adapter(&i2cd->adapter);
	अगर (status < 0)
		जाओ मुक्त_irq_vectors;

	status = gpu_populate_client(i2cd, pdev->irq);
	अगर (status < 0) अणु
		dev_err(&pdev->dev, "gpu_populate_client failed %d\n", status);
		जाओ del_adapter;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 3000);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);
	pm_runसमय_allow(&pdev->dev);

	वापस 0;

del_adapter:
	i2c_del_adapter(&i2cd->adapter);
मुक्त_irq_vectors:
	pci_मुक्त_irq_vectors(pdev);
	वापस status;
पूर्ण

अटल व्योम gpu_i2c_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा gpu_i2c_dev *i2cd = dev_get_drvdata(&pdev->dev);

	pm_runसमय_get_noresume(i2cd->dev);
	i2c_del_adapter(&i2cd->adapter);
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

#घोषणा gpu_i2c_suspend शून्य

अटल __maybe_unused पूर्णांक gpu_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा gpu_i2c_dev *i2cd = dev_get_drvdata(dev);

	gpu_enable_i2c_bus(i2cd);
	/*
	 * Runसमय resume ccgx client so that it can see क्रम any
	 * connector change event. Old ccg firmware has known
	 * issue of not triggering पूर्णांकerrupt when a device is
	 * connected to runसमय resume the controller.
	 */
	pm_request_resume(&i2cd->ccgx_client->dev);
	वापस 0;
पूर्ण

अटल UNIVERSAL_DEV_PM_OPS(gpu_i2c_driver_pm, gpu_i2c_suspend, gpu_i2c_resume,
			    शून्य);

अटल काष्ठा pci_driver gpu_i2c_driver = अणु
	.name		= "nvidia-gpu",
	.id_table	= gpu_i2c_ids,
	.probe		= gpu_i2c_probe,
	.हटाओ		= gpu_i2c_हटाओ,
	.driver		= अणु
		.pm	= &gpu_i2c_driver_pm,
	पूर्ण,
पूर्ण;

module_pci_driver(gpu_i2c_driver);

MODULE_AUTHOR("Ajay Gupta <ajayg@nvidia.com>");
MODULE_DESCRIPTION("Nvidia GPU I2C controller Driver");
MODULE_LICENSE("GPL v2");
