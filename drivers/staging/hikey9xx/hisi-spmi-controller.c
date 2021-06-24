<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/spmi.h>

/*
 * SPMI रेजिस्टर addr
 */
#घोषणा SPMI_CHANNEL_OFFSET				0x0300
#घोषणा SPMI_SLAVE_OFFSET				0x20

#घोषणा SPMI_APB_SPMI_CMD_BASE_ADDR			0x0100

#घोषणा SPMI_APB_SPMI_WDATA0_BASE_ADDR			0x0104
#घोषणा SPMI_APB_SPMI_WDATA1_BASE_ADDR			0x0108
#घोषणा SPMI_APB_SPMI_WDATA2_BASE_ADDR			0x010c
#घोषणा SPMI_APB_SPMI_WDATA3_BASE_ADDR			0x0110

#घोषणा SPMI_APB_SPMI_STATUS_BASE_ADDR			0x0200

#घोषणा SPMI_APB_SPMI_RDATA0_BASE_ADDR			0x0204
#घोषणा SPMI_APB_SPMI_RDATA1_BASE_ADDR			0x0208
#घोषणा SPMI_APB_SPMI_RDATA2_BASE_ADDR			0x020c
#घोषणा SPMI_APB_SPMI_RDATA3_BASE_ADDR			0x0210

#घोषणा SPMI_PER_DATAREG_BYTE				4
/*
 * SPMI cmd रेजिस्टर
 */
#घोषणा SPMI_APB_SPMI_CMD_EN				BIT(31)
#घोषणा SPMI_APB_SPMI_CMD_TYPE_OFFSET			24
#घोषणा SPMI_APB_SPMI_CMD_LENGTH_OFFSET			20
#घोषणा SPMI_APB_SPMI_CMD_SLAVEID_OFFSET		16
#घोषणा SPMI_APB_SPMI_CMD_ADDR_OFFSET			0

/* Command Opcodes */

क्रमागत spmi_controller_cmd_op_code अणु
	SPMI_CMD_REG_ZERO_WRITE = 0,
	SPMI_CMD_REG_WRITE = 1,
	SPMI_CMD_REG_READ = 2,
	SPMI_CMD_EXT_REG_WRITE = 3,
	SPMI_CMD_EXT_REG_READ = 4,
	SPMI_CMD_EXT_REG_WRITE_L = 5,
	SPMI_CMD_EXT_REG_READ_L = 6,
	SPMI_CMD_REG_RESET = 7,
	SPMI_CMD_REG_SLEEP = 8,
	SPMI_CMD_REG_SHUTDOWN = 9,
	SPMI_CMD_REG_WAKEUP = 10,
पूर्ण;

/*
 * SPMI status रेजिस्टर
 */
#घोषणा SPMI_APB_TRANS_DONE			BIT(0)
#घोषणा SPMI_APB_TRANS_FAIL			BIT(2)

/* Command रेजिस्टर fields */
#घोषणा SPMI_CONTROLLER_CMD_MAX_BYTE_COUNT	16

/* Maximum number of support PMIC peripherals */
#घोषणा SPMI_CONTROLLER_TIMEOUT_US		1000
#घोषणा SPMI_CONTROLLER_MAX_TRANS_BYTES		16

काष्ठा spmi_controller_dev अणु
	काष्ठा spmi_controller	*controller;
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	spinlock_t		lock;
	u32			channel;
पूर्ण;

अटल पूर्णांक spmi_controller_रुको_क्रम_करोne(काष्ठा device *dev,
					 काष्ठा spmi_controller_dev *ctrl_dev,
					 व्योम __iomem *base, u8 sid, u16 addr)
अणु
	u32 समयout = SPMI_CONTROLLER_TIMEOUT_US;
	u32 status, offset;

	offset  = SPMI_APB_SPMI_STATUS_BASE_ADDR;
	offset += SPMI_CHANNEL_OFFSET * ctrl_dev->channel + SPMI_SLAVE_OFFSET * sid;

	करो अणु
		status = पढ़ोl(base + offset);

		अगर (status & SPMI_APB_TRANS_DONE) अणु
			अगर (status & SPMI_APB_TRANS_FAIL) अणु
				dev_err(dev, "%s: transaction failed (0x%x)\n",
					__func__, status);
				वापस -EIO;
			पूर्ण
			dev_dbg(dev, "%s: status 0x%x\n", __func__, status);
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण जबतक (समयout--);

	dev_err(dev, "%s: timeout, status 0x%x\n", __func__, status);
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक spmi_पढ़ो_cmd(काष्ठा spmi_controller *ctrl,
			 u8 opc, u8 slave_id, u16 slave_addr, u8 *__buf, माप_प्रकार bc)
अणु
	काष्ठा spmi_controller_dev *spmi_controller = dev_get_drvdata(&ctrl->dev);
	u32 chnl_ofst = SPMI_CHANNEL_OFFSET * spmi_controller->channel;
	अचिन्हित दीर्घ flags;
	u8 *buf = __buf;
	u32 cmd, data;
	पूर्णांक rc;
	u8 op_code, i;

	अगर (bc > SPMI_CONTROLLER_MAX_TRANS_BYTES) अणु
		dev_err(&ctrl->dev,
			"spmi_controller supports 1..%d bytes per trans, but:%zu requested\n",
			SPMI_CONTROLLER_MAX_TRANS_BYTES, bc);
		वापस  -EINVAL;
	पूर्ण

	चयन (opc) अणु
	हाल SPMI_CMD_READ:
		op_code = SPMI_CMD_REG_READ;
		अवरोध;
	हाल SPMI_CMD_EXT_READ:
		op_code = SPMI_CMD_EXT_REG_READ;
		अवरोध;
	हाल SPMI_CMD_EXT_READL:
		op_code = SPMI_CMD_EXT_REG_READ_L;
		अवरोध;
	शेष:
		dev_err(&ctrl->dev, "invalid read cmd 0x%x\n", opc);
		वापस -EINVAL;
	पूर्ण

	cmd = SPMI_APB_SPMI_CMD_EN |
	     (op_code << SPMI_APB_SPMI_CMD_TYPE_OFFSET) |
	     ((bc - 1) << SPMI_APB_SPMI_CMD_LENGTH_OFFSET) |
	     ((slave_id & 0xf) << SPMI_APB_SPMI_CMD_SLAVEID_OFFSET) |  /* slvid */
	     ((slave_addr & 0xffff)  << SPMI_APB_SPMI_CMD_ADDR_OFFSET); /* slave_addr */

	spin_lock_irqsave(&spmi_controller->lock, flags);

	ग_लिखोl(cmd, spmi_controller->base + chnl_ofst + SPMI_APB_SPMI_CMD_BASE_ADDR);

	rc = spmi_controller_रुको_क्रम_करोne(&ctrl->dev, spmi_controller,
					   spmi_controller->base, slave_id, slave_addr);
	अगर (rc)
		जाओ करोne;

	क्रम (i = 0; bc > i * SPMI_PER_DATAREG_BYTE; i++) अणु
		data = पढ़ोl(spmi_controller->base + chnl_ofst +
			     SPMI_SLAVE_OFFSET * slave_id +
			     SPMI_APB_SPMI_RDATA0_BASE_ADDR +
			     i * SPMI_PER_DATAREG_BYTE);
		data = be32_to_cpu((__be32 __क्रमce)data);
		अगर ((bc - i * SPMI_PER_DATAREG_BYTE) >> 2) अणु
			स_नकल(buf, &data, माप(data));
			buf += माप(data);
		पूर्ण अन्यथा अणु
			स_नकल(buf, &data, bc % SPMI_PER_DATAREG_BYTE);
			buf += (bc % SPMI_PER_DATAREG_BYTE);
		पूर्ण
	पूर्ण

करोne:
	spin_unlock_irqrestore(&spmi_controller->lock, flags);
	अगर (rc)
		dev_err(&ctrl->dev,
			"spmi read wait timeout op:0x%x slave_id:%d slave_addr:0x%x bc:%zu\n",
			opc, slave_id, slave_addr, bc + 1);
	अन्यथा
		dev_dbg(&ctrl->dev, "%s: id:%d slave_addr:0x%x, read value: %*ph\n",
			__func__, slave_id, slave_addr, (पूर्णांक)bc, __buf);

	वापस rc;
पूर्ण

अटल पूर्णांक spmi_ग_लिखो_cmd(काष्ठा spmi_controller *ctrl,
			  u8 opc, u8 slave_id, u16 slave_addr, स्थिर u8 *__buf, माप_प्रकार bc)
अणु
	काष्ठा spmi_controller_dev *spmi_controller = dev_get_drvdata(&ctrl->dev);
	u32 chnl_ofst = SPMI_CHANNEL_OFFSET * spmi_controller->channel;
	स्थिर u8 *buf = __buf;
	अचिन्हित दीर्घ flags;
	u32 cmd, data;
	पूर्णांक rc;
	u8 op_code, i;

	अगर (bc > SPMI_CONTROLLER_MAX_TRANS_BYTES) अणु
		dev_err(&ctrl->dev,
			"spmi_controller supports 1..%d bytes per trans, but:%zu requested\n",
			SPMI_CONTROLLER_MAX_TRANS_BYTES, bc);
		वापस  -EINVAL;
	पूर्ण

	चयन (opc) अणु
	हाल SPMI_CMD_WRITE:
		op_code = SPMI_CMD_REG_WRITE;
		अवरोध;
	हाल SPMI_CMD_EXT_WRITE:
		op_code = SPMI_CMD_EXT_REG_WRITE;
		अवरोध;
	हाल SPMI_CMD_EXT_WRITEL:
		op_code = SPMI_CMD_EXT_REG_WRITE_L;
		अवरोध;
	शेष:
		dev_err(&ctrl->dev, "invalid write cmd 0x%x\n", opc);
		वापस -EINVAL;
	पूर्ण

	cmd = SPMI_APB_SPMI_CMD_EN |
	      (op_code << SPMI_APB_SPMI_CMD_TYPE_OFFSET) |
	      ((bc - 1) << SPMI_APB_SPMI_CMD_LENGTH_OFFSET) |
	      ((slave_id & 0xf) << SPMI_APB_SPMI_CMD_SLAVEID_OFFSET) |
	      ((slave_addr & 0xffff)  << SPMI_APB_SPMI_CMD_ADDR_OFFSET);

	/* Write data to FIFOs */
	spin_lock_irqsave(&spmi_controller->lock, flags);

	क्रम (i = 0; bc > i * SPMI_PER_DATAREG_BYTE; i++) अणु
		data = 0;
		अगर ((bc - i * SPMI_PER_DATAREG_BYTE) >> 2) अणु
			स_नकल(&data, buf, माप(data));
			buf += माप(data);
		पूर्ण अन्यथा अणु
			स_नकल(&data, buf, bc % SPMI_PER_DATAREG_BYTE);
			buf += (bc % SPMI_PER_DATAREG_BYTE);
		पूर्ण

		ग_लिखोl((u32 __क्रमce)cpu_to_be32(data),
		       spmi_controller->base + chnl_ofst +
		       SPMI_APB_SPMI_WDATA0_BASE_ADDR +
		       SPMI_PER_DATAREG_BYTE * i);
	पूर्ण

	/* Start the transaction */
	ग_लिखोl(cmd, spmi_controller->base + chnl_ofst + SPMI_APB_SPMI_CMD_BASE_ADDR);

	rc = spmi_controller_रुको_क्रम_करोne(&ctrl->dev, spmi_controller,
					   spmi_controller->base, slave_id,
					   slave_addr);
	spin_unlock_irqrestore(&spmi_controller->lock, flags);

	अगर (rc)
		dev_err(&ctrl->dev, "spmi write wait timeout op:0x%x slave_id:%d slave_addr:0x%x bc:%zu\n",
			opc, slave_id, slave_addr, bc);
	अन्यथा
		dev_dbg(&ctrl->dev, "%s: id:%d slave_addr:0x%x, wrote value: %*ph\n",
			__func__, slave_id, slave_addr, (पूर्णांक)bc, __buf);

	वापस rc;
पूर्ण

अटल पूर्णांक spmi_controller_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spmi_controller_dev *spmi_controller;
	काष्ठा spmi_controller *ctrl;
	काष्ठा resource *iores;
	पूर्णांक ret;

	ctrl = spmi_controller_alloc(&pdev->dev, माप(*spmi_controller));
	अगर (!ctrl) अणु
		dev_err(&pdev->dev, "can not allocate spmi_controller data\n");
		वापस -ENOMEM;
	पूर्ण
	spmi_controller = spmi_controller_get_drvdata(ctrl);
	spmi_controller->controller = ctrl;

	iores = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!iores) अणु
		dev_err(&pdev->dev, "can not get resource!\n");
		ret = -EINVAL;
		जाओ err_put_controller;
	पूर्ण

	spmi_controller->base = devm_ioremap(&pdev->dev, iores->start,
					     resource_size(iores));
	अगर (!spmi_controller->base) अणु
		dev_err(&pdev->dev, "can not remap base addr!\n");
		ret = -EADDRNOTAVAIL;
		जाओ err_put_controller;
	पूर्ण

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "spmi-channel",
				   &spmi_controller->channel);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can not get channel\n");
		ret = -ENODEV;
		जाओ err_put_controller;
	पूर्ण

	platक्रमm_set_drvdata(pdev, spmi_controller);
	dev_set_drvdata(&ctrl->dev, spmi_controller);

	spin_lock_init(&spmi_controller->lock);

	ctrl->nr = spmi_controller->channel;
	ctrl->dev.parent = pdev->dev.parent;
	ctrl->dev.of_node = of_node_get(pdev->dev.of_node);

	/* Callbacks */
	ctrl->पढ़ो_cmd = spmi_पढ़ो_cmd;
	ctrl->ग_लिखो_cmd = spmi_ग_लिखो_cmd;

	ret = spmi_controller_add(ctrl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "spmi_controller_add failed with error %d!\n", ret);
		जाओ err_put_controller;
	पूर्ण

	वापस 0;

err_put_controller:
	spmi_controller_put(ctrl);
	वापस ret;
पूर्ण

अटल पूर्णांक spmi_del_controller(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spmi_controller *ctrl = platक्रमm_get_drvdata(pdev);

	spmi_controller_हटाओ(ctrl);
	spmi_controller_put(ctrl);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id spmi_controller_match_table[] = अणु
	अणु
		.compatible = "hisilicon,kirin970-spmi-controller",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, spmi_controller_match_table);

अटल काष्ठा platक्रमm_driver spmi_controller_driver = अणु
	.probe		= spmi_controller_probe,
	.हटाओ		= spmi_del_controller,
	.driver		= अणु
		.name	= "hisi_spmi_controller",
		.of_match_table = spmi_controller_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init spmi_controller_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&spmi_controller_driver);
पूर्ण
postcore_initcall(spmi_controller_init);

अटल व्योम __निकास spmi_controller_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&spmi_controller_driver);
पूर्ण
module_निकास(spmi_controller_निकास);

MODULE_LICENSE("GPL v2");
MODULE_VERSION("1.0");
MODULE_ALIAS("platform:spmi_controller");
