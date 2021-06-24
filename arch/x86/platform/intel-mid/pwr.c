<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel MID Power Management Unit (PWRMU) device driver
 *
 * Copyright (C) 2016, Intel Corporation
 *
 * Author: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 *
 * Intel MID Power Management Unit device driver handles the South Complex PCI
 * devices such as GPDMA, SPI, I2C, PWM, and so on. By शेष PCI core
 * modअगरies bits in PMCSR रेजिस्टर in the PCI configuration space. This is not
 * enough on some SoCs like Intel Tangier. In such हाल PCI core sets a new
 * घातer state of the device in question through a PM hook रेजिस्टरed in काष्ठा
 * pci_platक्रमm_pm_ops (see drivers/pci/pci-mid.c).
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/पूर्णांकel-mid.h>

/* Registers */
#घोषणा PM_STS			0x00
#घोषणा PM_CMD			0x04
#घोषणा PM_ICS			0x08
#घोषणा PM_WKC(x)		(0x10 + (x) * 4)
#घोषणा PM_WKS(x)		(0x18 + (x) * 4)
#घोषणा PM_SSC(x)		(0x20 + (x) * 4)
#घोषणा PM_SSS(x)		(0x30 + (x) * 4)

/* Bits in PM_STS */
#घोषणा PM_STS_BUSY		(1 << 8)

/* Bits in PM_CMD */
#घोषणा PM_CMD_CMD(x)		((x) << 0)
#घोषणा PM_CMD_IOC		(1 << 8)
#घोषणा PM_CMD_CM_NOP		(0 << 9)
#घोषणा PM_CMD_CM_IMMEDIATE	(1 << 9)
#घोषणा PM_CMD_CM_DELAY		(2 << 9)
#घोषणा PM_CMD_CM_TRIGGER	(3 << 9)

/* System states */
#घोषणा PM_CMD_SYS_STATE_S5	(5 << 16)

/* Trigger variants */
#घोषणा PM_CMD_CFG_TRIGGER_NC	(3 << 19)

/* Message to रुको क्रम TRIGGER_NC हाल */
#घोषणा TRIGGER_NC_MSG_2	(2 << 22)

/* List of commands */
#घोषणा CMD_SET_CFG		0x01

/* Bits in PM_ICS */
#घोषणा PM_ICS_INT_STATUS(x)	((x) & 0xff)
#घोषणा PM_ICS_IE		(1 << 8)
#घोषणा PM_ICS_IP		(1 << 9)
#घोषणा PM_ICS_SW_INT_STS	(1 << 10)

/* List of पूर्णांकerrupts */
#घोषणा INT_INVALID		0
#घोषणा INT_CMD_COMPLETE	1
#घोषणा INT_CMD_ERR		2
#घोषणा INT_WAKE_EVENT		3
#घोषणा INT_LSS_POWER_ERR	4
#घोषणा INT_S0iX_MSG_ERR	5
#घोषणा INT_NO_C6		6
#घोषणा INT_TRIGGER_ERR		7
#घोषणा INT_INACTIVITY		8

/* South Complex devices */
#घोषणा LSS_MAX_SHARED_DEVS	4
#घोषणा LSS_MAX_DEVS		64

#घोषणा LSS_WS_BITS		1	/* wake state width */
#घोषणा LSS_PWS_BITS		2	/* घातer state width */

/* Supported device IDs */
#घोषणा PCI_DEVICE_ID_PENWELL	0x0828
#घोषणा PCI_DEVICE_ID_TANGIER	0x11a1

काष्ठा mid_pwr_dev अणु
	काष्ठा pci_dev *pdev;
	pci_घातer_t state;
पूर्ण;

काष्ठा mid_pwr अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	पूर्णांक irq;
	bool available;

	काष्ठा mutex lock;
	काष्ठा mid_pwr_dev lss[LSS_MAX_DEVS][LSS_MAX_SHARED_DEVS];
पूर्ण;

अटल काष्ठा mid_pwr *midpwr;

अटल u32 mid_pwr_get_state(काष्ठा mid_pwr *pwr, पूर्णांक reg)
अणु
	वापस पढ़ोl(pwr->regs + PM_SSS(reg));
पूर्ण

अटल व्योम mid_pwr_set_state(काष्ठा mid_pwr *pwr, पूर्णांक reg, u32 value)
अणु
	ग_लिखोl(value, pwr->regs + PM_SSC(reg));
पूर्ण

अटल व्योम mid_pwr_set_wake(काष्ठा mid_pwr *pwr, पूर्णांक reg, u32 value)
अणु
	ग_लिखोl(value, pwr->regs + PM_WKC(reg));
पूर्ण

अटल व्योम mid_pwr_पूर्णांकerrupt_disable(काष्ठा mid_pwr *pwr)
अणु
	ग_लिखोl(~PM_ICS_IE, pwr->regs + PM_ICS);
पूर्ण

अटल bool mid_pwr_is_busy(काष्ठा mid_pwr *pwr)
अणु
	वापस !!(पढ़ोl(pwr->regs + PM_STS) & PM_STS_BUSY);
पूर्ण

/* Wait 500ms that the latest PWRMU command finished */
अटल पूर्णांक mid_pwr_रुको(काष्ठा mid_pwr *pwr)
अणु
	अचिन्हित पूर्णांक count = 500000;
	bool busy;

	करो अणु
		busy = mid_pwr_is_busy(pwr);
		अगर (!busy)
			वापस 0;
		udelay(1);
	पूर्ण जबतक (--count);

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक mid_pwr_रुको_क्रम_cmd(काष्ठा mid_pwr *pwr, u8 cmd)
अणु
	ग_लिखोl(PM_CMD_CMD(cmd) | PM_CMD_CM_IMMEDIATE, pwr->regs + PM_CMD);
	वापस mid_pwr_रुको(pwr);
पूर्ण

अटल पूर्णांक __update_घातer_state(काष्ठा mid_pwr *pwr, पूर्णांक reg, पूर्णांक bit, पूर्णांक new)
अणु
	पूर्णांक curstate;
	u32 घातer;
	पूर्णांक ret;

	/* Check अगर the device is alपढ़ोy in desired state */
	घातer = mid_pwr_get_state(pwr, reg);
	curstate = (घातer >> bit) & 3;
	अगर (curstate == new)
		वापस 0;

	/* Update the घातer state */
	mid_pwr_set_state(pwr, reg, (घातer & ~(3 << bit)) | (new << bit));

	/* Send command to SCU */
	ret = mid_pwr_रुको_क्रम_cmd(pwr, CMD_SET_CFG);
	अगर (ret)
		वापस ret;

	/* Check अगर the device is alपढ़ोy in desired state */
	घातer = mid_pwr_get_state(pwr, reg);
	curstate = (घातer >> bit) & 3;
	अगर (curstate != new)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल pci_घातer_t __find_weakest_घातer_state(काष्ठा mid_pwr_dev *lss,
					      काष्ठा pci_dev *pdev,
					      pci_घातer_t state)
अणु
	pci_घातer_t weakest = PCI_D3hot;
	अचिन्हित पूर्णांक j;

	/* Find device in cache or first मुक्त cell */
	क्रम (j = 0; j < LSS_MAX_SHARED_DEVS; j++) अणु
		अगर (lss[j].pdev == pdev || !lss[j].pdev)
			अवरोध;
	पूर्ण

	/* Store the desired state in cache */
	अगर (j < LSS_MAX_SHARED_DEVS) अणु
		lss[j].pdev = pdev;
		lss[j].state = state;
	पूर्ण अन्यथा अणु
		dev_WARN(&pdev->dev, "No room for device in PWRMU LSS cache\n");
		weakest = state;
	पूर्ण

	/* Find the घातer state we may use */
	क्रम (j = 0; j < LSS_MAX_SHARED_DEVS; j++) अणु
		अगर (lss[j].state < weakest)
			weakest = lss[j].state;
	पूर्ण

	वापस weakest;
पूर्ण

अटल पूर्णांक __set_घातer_state(काष्ठा mid_pwr *pwr, काष्ठा pci_dev *pdev,
			     pci_घातer_t state, पूर्णांक id, पूर्णांक reg, पूर्णांक bit)
अणु
	स्थिर अक्षर *name;
	पूर्णांक ret;

	state = __find_weakest_घातer_state(pwr->lss[id], pdev, state);
	name = pci_घातer_name(state);

	ret = __update_घातer_state(pwr, reg, bit, (__क्रमce पूर्णांक)state);
	अगर (ret) अणु
		dev_warn(&pdev->dev, "Can't set power state %s: %d\n", name, ret);
		वापस ret;
	पूर्ण

	dev_vdbg(&pdev->dev, "Set power state %s\n", name);
	वापस 0;
पूर्ण

अटल पूर्णांक mid_pwr_set_घातer_state(काष्ठा mid_pwr *pwr, काष्ठा pci_dev *pdev,
				   pci_घातer_t state)
अणु
	पूर्णांक id, reg, bit;
	पूर्णांक ret;

	id = पूर्णांकel_mid_pwr_get_lss_id(pdev);
	अगर (id < 0)
		वापस id;

	reg = (id * LSS_PWS_BITS) / 32;
	bit = (id * LSS_PWS_BITS) % 32;

	/* We support states between PCI_D0 and PCI_D3hot */
	अगर (state < PCI_D0)
		state = PCI_D0;
	अगर (state > PCI_D3hot)
		state = PCI_D3hot;

	mutex_lock(&pwr->lock);
	ret = __set_घातer_state(pwr, pdev, state, id, reg, bit);
	mutex_unlock(&pwr->lock);
	वापस ret;
पूर्ण

पूर्णांक पूर्णांकel_mid_pci_set_घातer_state(काष्ठा pci_dev *pdev, pci_घातer_t state)
अणु
	काष्ठा mid_pwr *pwr = midpwr;
	पूर्णांक ret = 0;

	might_sleep();

	अगर (pwr && pwr->available)
		ret = mid_pwr_set_घातer_state(pwr, pdev, state);
	dev_vdbg(&pdev->dev, "set_power_state() returns %d\n", ret);

	वापस 0;
पूर्ण

pci_घातer_t पूर्णांकel_mid_pci_get_घातer_state(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mid_pwr *pwr = midpwr;
	पूर्णांक id, reg, bit;
	u32 घातer;

	अगर (!pwr || !pwr->available)
		वापस PCI_UNKNOWN;

	id = पूर्णांकel_mid_pwr_get_lss_id(pdev);
	अगर (id < 0)
		वापस PCI_UNKNOWN;

	reg = (id * LSS_PWS_BITS) / 32;
	bit = (id * LSS_PWS_BITS) % 32;
	घातer = mid_pwr_get_state(pwr, reg);
	वापस (__क्रमce pci_घातer_t)((घातer >> bit) & 3);
पूर्ण

व्योम पूर्णांकel_mid_pwr_घातer_off(व्योम)
अणु
	काष्ठा mid_pwr *pwr = midpwr;
	u32 cmd = PM_CMD_SYS_STATE_S5 |
		  PM_CMD_CMD(CMD_SET_CFG) |
		  PM_CMD_CM_TRIGGER |
		  PM_CMD_CFG_TRIGGER_NC |
		  TRIGGER_NC_MSG_2;

	/* Send command to SCU */
	ग_लिखोl(cmd, pwr->regs + PM_CMD);
	mid_pwr_रुको(pwr);
पूर्ण

पूर्णांक पूर्णांकel_mid_pwr_get_lss_id(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक vndr;
	u8 id;

	/*
	 * Mapping to PWRMU index is kept in the Logical SubSystem ID byte of
	 * Venकरोr capability.
	 */
	vndr = pci_find_capability(pdev, PCI_CAP_ID_VNDR);
	अगर (!vndr)
		वापस -EINVAL;

	/* Read the Logical SubSystem ID byte */
	pci_पढ़ो_config_byte(pdev, vndr + INTEL_MID_PWR_LSS_OFFSET, &id);
	अगर (!(id & INTEL_MID_PWR_LSS_TYPE))
		वापस -ENODEV;

	id &= ~INTEL_MID_PWR_LSS_TYPE;
	अगर (id >= LSS_MAX_DEVS)
		वापस -दुस्फल;

	वापस id;
पूर्ण

अटल irqवापस_t mid_pwr_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mid_pwr *pwr = dev_id;
	u32 ics;

	ics = पढ़ोl(pwr->regs + PM_ICS);
	अगर (!(ics & PM_ICS_IP))
		वापस IRQ_NONE;

	ग_लिखोl(ics | PM_ICS_IP, pwr->regs + PM_ICS);

	dev_warn(pwr->dev, "Unexpected IRQ: %#x\n", PM_ICS_INT_STATUS(ics));
	वापस IRQ_HANDLED;
पूर्ण

काष्ठा mid_pwr_device_info अणु
	पूर्णांक (*set_initial_state)(काष्ठा mid_pwr *pwr);
पूर्ण;

अटल पूर्णांक mid_pwr_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा mid_pwr_device_info *info = (व्योम *)id->driver_data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mid_pwr *pwr;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "error: could not enable device\n");
		वापस ret;
	पूर्ण

	ret = pcim_iomap_regions(pdev, 1 << 0, pci_name(pdev));
	अगर (ret) अणु
		dev_err(&pdev->dev, "I/O memory remapping failed\n");
		वापस ret;
	पूर्ण

	pwr = devm_kzalloc(dev, माप(*pwr), GFP_KERNEL);
	अगर (!pwr)
		वापस -ENOMEM;

	pwr->dev = dev;
	pwr->regs = pcim_iomap_table(pdev)[0];
	pwr->irq = pdev->irq;

	mutex_init(&pwr->lock);

	/* Disable पूर्णांकerrupts */
	mid_pwr_पूर्णांकerrupt_disable(pwr);

	अगर (info && info->set_initial_state) अणु
		ret = info->set_initial_state(pwr);
		अगर (ret)
			dev_warn(dev, "Can't set initial state: %d\n", ret);
	पूर्ण

	ret = devm_request_irq(dev, pdev->irq, mid_pwr_irq_handler,
			       IRQF_NO_SUSPEND, pci_name(pdev), pwr);
	अगर (ret)
		वापस ret;

	pwr->available = true;
	midpwr = pwr;

	pci_set_drvdata(pdev, pwr);
	वापस 0;
पूर्ण

अटल पूर्णांक mid_set_initial_state(काष्ठा mid_pwr *pwr, स्थिर u32 *states)
अणु
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret;

	/*
	 * Enable wake events.
	 *
	 * PWRMU supports up to 32 sources क्रम wake up the प्रणाली. Ungate them
	 * all here.
	 */
	mid_pwr_set_wake(pwr, 0, 0xffffffff);
	mid_pwr_set_wake(pwr, 1, 0xffffffff);

	/*
	 * Power off South Complex devices.
	 *
	 * There is a map (see a note below) of 64 devices with 2 bits per each
	 * on 32-bit HW रेजिस्टरs. The following calls set all devices to one
	 * known initial state, i.e. PCI_D3hot. This is करोne in conjunction
	 * with PMCSR setting in arch/x86/pci/पूर्णांकel_mid_pci.c.
	 *
	 * NOTE: The actual device mapping is provided by a platक्रमm at run
	 * समय using venकरोr capability of PCI configuration space.
	 */
	mid_pwr_set_state(pwr, 0, states[0]);
	mid_pwr_set_state(pwr, 1, states[1]);
	mid_pwr_set_state(pwr, 2, states[2]);
	mid_pwr_set_state(pwr, 3, states[3]);

	/* Send command to SCU */
	ret = mid_pwr_रुको_क्रम_cmd(pwr, CMD_SET_CFG);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < LSS_MAX_DEVS; i++) अणु
		क्रम (j = 0; j < LSS_MAX_SHARED_DEVS; j++)
			pwr->lss[i][j].state = PCI_D3hot;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pnw_set_initial_state(काष्ठा mid_pwr *pwr)
अणु
	/* On Penwell SRAM must stay घातered on */
	अटल स्थिर u32 states[] = अणु
		0xf00fffff,		/* PM_SSC(0) */
		0xffffffff,		/* PM_SSC(1) */
		0xffffffff,		/* PM_SSC(2) */
		0xffffffff,		/* PM_SSC(3) */
	पूर्ण;
	वापस mid_set_initial_state(pwr, states);
पूर्ण

अटल पूर्णांक tng_set_initial_state(काष्ठा mid_pwr *pwr)
अणु
	अटल स्थिर u32 states[] = अणु
		0xffffffff,		/* PM_SSC(0) */
		0xffffffff,		/* PM_SSC(1) */
		0xffffffff,		/* PM_SSC(2) */
		0xffffffff,		/* PM_SSC(3) */
	पूर्ण;
	वापस mid_set_initial_state(pwr, states);
पूर्ण

अटल स्थिर काष्ठा mid_pwr_device_info pnw_info = अणु
	.set_initial_state = pnw_set_initial_state,
पूर्ण;

अटल स्थिर काष्ठा mid_pwr_device_info tng_info = अणु
	.set_initial_state = tng_set_initial_state,
पूर्ण;

/* This table should be in sync with the one in drivers/pci/pci-mid.c */
अटल स्थिर काष्ठा pci_device_id mid_pwr_pci_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_PENWELL), (kernel_uदीर्घ_t)&pnw_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_TANGIER), (kernel_uदीर्घ_t)&tng_info पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा pci_driver mid_pwr_pci_driver = अणु
	.name		= "intel_mid_pwr",
	.probe		= mid_pwr_probe,
	.id_table	= mid_pwr_pci_ids,
पूर्ण;

builtin_pci_driver(mid_pwr_pci_driver);
