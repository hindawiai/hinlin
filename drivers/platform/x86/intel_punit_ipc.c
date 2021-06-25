<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the Intel P-Unit Mailbox IPC mechanism
 *
 * (C) Copyright 2015 Intel Corporation
 *
 * The heart of the P-Unit is the Foxton microcontroller and its firmware,
 * which provide mailbox पूर्णांकerface क्रम घातer management usage.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/पूर्णांकel_punit_ipc.h>

/* IPC Mailbox रेजिस्टरs */
#घोषणा OFFSET_DATA_LOW		0x0
#घोषणा OFFSET_DATA_HIGH	0x4
/* bit field of पूर्णांकerface रेजिस्टर */
#घोषणा	CMD_RUN			BIT(31)
#घोषणा	CMD_ERRCODE_MASK	GENMASK(7, 0)
#घोषणा	CMD_PARA1_SHIFT		8
#घोषणा	CMD_PARA2_SHIFT		16

#घोषणा CMD_TIMEOUT_SECONDS	1

क्रमागत अणु
	BASE_DATA = 0,
	BASE_IFACE,
	BASE_MAX,
पूर्ण;

प्रकार काष्ठा अणु
	काष्ठा device *dev;
	काष्ठा mutex lock;
	पूर्णांक irq;
	काष्ठा completion cmd_complete;
	/* base of पूर्णांकerface and data रेजिस्टरs */
	व्योम __iomem *base[RESERVED_IPC][BASE_MAX];
	IPC_TYPE type;
पूर्ण IPC_DEV;

अटल IPC_DEV *punit_ipcdev;

अटल अंतरभूत u32 ipc_पढ़ो_status(IPC_DEV *ipcdev, IPC_TYPE type)
अणु
	वापस पढ़ोl(ipcdev->base[type][BASE_IFACE]);
पूर्ण

अटल अंतरभूत व्योम ipc_ग_लिखो_cmd(IPC_DEV *ipcdev, IPC_TYPE type, u32 cmd)
अणु
	ग_लिखोl(cmd, ipcdev->base[type][BASE_IFACE]);
पूर्ण

अटल अंतरभूत u32 ipc_पढ़ो_data_low(IPC_DEV *ipcdev, IPC_TYPE type)
अणु
	वापस पढ़ोl(ipcdev->base[type][BASE_DATA] + OFFSET_DATA_LOW);
पूर्ण

अटल अंतरभूत u32 ipc_पढ़ो_data_high(IPC_DEV *ipcdev, IPC_TYPE type)
अणु
	वापस पढ़ोl(ipcdev->base[type][BASE_DATA] + OFFSET_DATA_HIGH);
पूर्ण

अटल अंतरभूत व्योम ipc_ग_लिखो_data_low(IPC_DEV *ipcdev, IPC_TYPE type, u32 data)
अणु
	ग_लिखोl(data, ipcdev->base[type][BASE_DATA] + OFFSET_DATA_LOW);
पूर्ण

अटल अंतरभूत व्योम ipc_ग_लिखो_data_high(IPC_DEV *ipcdev, IPC_TYPE type, u32 data)
अणु
	ग_लिखोl(data, ipcdev->base[type][BASE_DATA] + OFFSET_DATA_HIGH);
पूर्ण

अटल स्थिर अक्षर *ipc_err_string(पूर्णांक error)
अणु
	अगर (error == IPC_PUNIT_ERR_SUCCESS)
		वापस "no error";
	अन्यथा अगर (error == IPC_PUNIT_ERR_INVALID_CMD)
		वापस "invalid command";
	अन्यथा अगर (error == IPC_PUNIT_ERR_INVALID_PARAMETER)
		वापस "invalid parameter";
	अन्यथा अगर (error == IPC_PUNIT_ERR_CMD_TIMEOUT)
		वापस "command timeout";
	अन्यथा अगर (error == IPC_PUNIT_ERR_CMD_LOCKED)
		वापस "command locked";
	अन्यथा अगर (error == IPC_PUNIT_ERR_INVALID_VR_ID)
		वापस "invalid vr id";
	अन्यथा अगर (error == IPC_PUNIT_ERR_VR_ERR)
		वापस "vr error";
	अन्यथा
		वापस "unknown error";
पूर्ण

अटल पूर्णांक पूर्णांकel_punit_ipc_check_status(IPC_DEV *ipcdev, IPC_TYPE type)
अणु
	पूर्णांक loops = CMD_TIMEOUT_SECONDS * USEC_PER_SEC;
	पूर्णांक errcode;
	पूर्णांक status;

	अगर (ipcdev->irq) अणु
		अगर (!रुको_क्रम_completion_समयout(&ipcdev->cmd_complete,
						 CMD_TIMEOUT_SECONDS * HZ)) अणु
			dev_err(ipcdev->dev, "IPC timed out\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक ((ipc_पढ़ो_status(ipcdev, type) & CMD_RUN) && --loops)
			udelay(1);
		अगर (!loops) अणु
			dev_err(ipcdev->dev, "IPC timed out\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	status = ipc_पढ़ो_status(ipcdev, type);
	errcode = status & CMD_ERRCODE_MASK;
	अगर (errcode) अणु
		dev_err(ipcdev->dev, "IPC failed: %s, IPC_STS=0x%x\n",
			ipc_err_string(errcode), status);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_punit_ipc_simple_command() - Simple IPC command
 * @cmd:	IPC command code.
 * @para1:	First 8bit parameter, set 0 अगर not used.
 * @para2:	Second 8bit parameter, set 0 अगर not used.
 *
 * Send a IPC command to P-Unit when there is no data transaction
 *
 * Return:	IPC error code or 0 on success.
 */
पूर्णांक पूर्णांकel_punit_ipc_simple_command(पूर्णांक cmd, पूर्णांक para1, पूर्णांक para2)
अणु
	IPC_DEV *ipcdev = punit_ipcdev;
	IPC_TYPE type;
	u32 val;
	पूर्णांक ret;

	mutex_lock(&ipcdev->lock);

	reinit_completion(&ipcdev->cmd_complete);
	type = (cmd & IPC_PUNIT_CMD_TYPE_MASK) >> IPC_TYPE_OFFSET;

	val = cmd & ~IPC_PUNIT_CMD_TYPE_MASK;
	val |= CMD_RUN | para2 << CMD_PARA2_SHIFT | para1 << CMD_PARA1_SHIFT;
	ipc_ग_लिखो_cmd(ipcdev, type, val);
	ret = पूर्णांकel_punit_ipc_check_status(ipcdev, type);

	mutex_unlock(&ipcdev->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_punit_ipc_simple_command);

/**
 * पूर्णांकel_punit_ipc_command() - IPC command with data and poपूर्णांकers
 * @cmd:	IPC command code.
 * @para1:	First 8bit parameter, set 0 अगर not used.
 * @para2:	Second 8bit parameter, set 0 अगर not used.
 * @in:		Input data, 32bit क्रम BIOS cmd, two 32bit क्रम GTD and ISPD.
 * @out:	Output data.
 *
 * Send a IPC command to P-Unit with data transaction
 *
 * Return:	IPC error code or 0 on success.
 */
पूर्णांक पूर्णांकel_punit_ipc_command(u32 cmd, u32 para1, u32 para2, u32 *in, u32 *out)
अणु
	IPC_DEV *ipcdev = punit_ipcdev;
	IPC_TYPE type;
	u32 val;
	पूर्णांक ret;

	mutex_lock(&ipcdev->lock);

	reinit_completion(&ipcdev->cmd_complete);
	type = (cmd & IPC_PUNIT_CMD_TYPE_MASK) >> IPC_TYPE_OFFSET;

	अगर (in) अणु
		ipc_ग_लिखो_data_low(ipcdev, type, *in);
		अगर (type == GTDRIVER_IPC || type == ISPDRIVER_IPC)
			ipc_ग_लिखो_data_high(ipcdev, type, *++in);
	पूर्ण

	val = cmd & ~IPC_PUNIT_CMD_TYPE_MASK;
	val |= CMD_RUN | para2 << CMD_PARA2_SHIFT | para1 << CMD_PARA1_SHIFT;
	ipc_ग_लिखो_cmd(ipcdev, type, val);

	ret = पूर्णांकel_punit_ipc_check_status(ipcdev, type);
	अगर (ret)
		जाओ out;

	अगर (out) अणु
		*out = ipc_पढ़ो_data_low(ipcdev, type);
		अगर (type == GTDRIVER_IPC || type == ISPDRIVER_IPC)
			*++out = ipc_पढ़ो_data_high(ipcdev, type);
	पूर्ण

out:
	mutex_unlock(&ipcdev->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_punit_ipc_command);

अटल irqवापस_t पूर्णांकel_punit_ioc(पूर्णांक irq, व्योम *dev_id)
अणु
	IPC_DEV *ipcdev = dev_id;

	complete(&ipcdev->cmd_complete);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक पूर्णांकel_punit_get_bars(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *addr;

	/*
	 * The following resources are required
	 * - BIOS_IPC BASE_DATA
	 * - BIOS_IPC BASE_IFACE
	 */
	addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(addr))
		वापस PTR_ERR(addr);
	punit_ipcdev->base[BIOS_IPC][BASE_DATA] = addr;

	addr = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(addr))
		वापस PTR_ERR(addr);
	punit_ipcdev->base[BIOS_IPC][BASE_IFACE] = addr;

	/*
	 * The following resources are optional
	 * - ISPDRIVER_IPC BASE_DATA
	 * - ISPDRIVER_IPC BASE_IFACE
	 * - GTDRIVER_IPC BASE_DATA
	 * - GTDRIVER_IPC BASE_IFACE
	 */
	addr = devm_platक्रमm_ioremap_resource(pdev, 2);
	अगर (!IS_ERR(addr))
		punit_ipcdev->base[ISPDRIVER_IPC][BASE_DATA] = addr;

	addr = devm_platक्रमm_ioremap_resource(pdev, 3);
	अगर (!IS_ERR(addr))
		punit_ipcdev->base[ISPDRIVER_IPC][BASE_IFACE] = addr;

	addr = devm_platक्रमm_ioremap_resource(pdev, 4);
	अगर (!IS_ERR(addr))
		punit_ipcdev->base[GTDRIVER_IPC][BASE_DATA] = addr;

	addr = devm_platक्रमm_ioremap_resource(pdev, 5);
	अगर (!IS_ERR(addr))
		punit_ipcdev->base[GTDRIVER_IPC][BASE_IFACE] = addr;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_punit_ipc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक irq, ret;

	punit_ipcdev = devm_kzalloc(&pdev->dev,
				    माप(*punit_ipcdev), GFP_KERNEL);
	अगर (!punit_ipcdev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, punit_ipcdev);

	irq = platक्रमm_get_irq_optional(pdev, 0);
	अगर (irq < 0) अणु
		dev_warn(&pdev->dev, "Invalid IRQ, using polling mode\n");
	पूर्ण अन्यथा अणु
		ret = devm_request_irq(&pdev->dev, irq, पूर्णांकel_punit_ioc,
				       IRQF_NO_SUSPEND, "intel_punit_ipc",
				       &punit_ipcdev);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Failed to request irq: %d\n", irq);
			वापस ret;
		पूर्ण
		punit_ipcdev->irq = irq;
	पूर्ण

	ret = पूर्णांकel_punit_get_bars(pdev);
	अगर (ret)
		वापस ret;

	punit_ipcdev->dev = &pdev->dev;
	mutex_init(&punit_ipcdev->lock);
	init_completion(&punit_ipcdev->cmd_complete);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_punit_ipc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id punit_ipc_acpi_ids[] = अणु
	अणु "INT34D4", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, punit_ipc_acpi_ids);

अटल काष्ठा platक्रमm_driver पूर्णांकel_punit_ipc_driver = अणु
	.probe = पूर्णांकel_punit_ipc_probe,
	.हटाओ = पूर्णांकel_punit_ipc_हटाओ,
	.driver = अणु
		.name = "intel_punit_ipc",
		.acpi_match_table = ACPI_PTR(punit_ipc_acpi_ids),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init पूर्णांकel_punit_ipc_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&पूर्णांकel_punit_ipc_driver);
पूर्ण

अटल व्योम __निकास पूर्णांकel_punit_ipc_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&पूर्णांकel_punit_ipc_driver);
पूर्ण

MODULE_AUTHOR("Zha Qipeng <qipeng.zha@intel.com>");
MODULE_DESCRIPTION("Intel P-Unit IPC driver");
MODULE_LICENSE("GPL v2");

/* Some modules are dependent on this, so init earlier */
fs_initcall(पूर्णांकel_punit_ipc_init);
module_निकास(पूर्णांकel_punit_ipc_निकास);
