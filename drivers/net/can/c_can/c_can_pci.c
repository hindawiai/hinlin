<शैली गुरु>
/*
 * PCI bus driver क्रम Bosch C_CAN/D_CAN controller
 *
 * Copyright (C) 2012 Federico Vaga <federico.vaga@gmail.com>
 *
 * Borrowed from c_can_platक्रमm.c
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>

#समावेश <linux/can/dev.h>

#समावेश "c_can.h"

#घोषणा PCI_DEVICE_ID_PCH_CAN	0x8818
#घोषणा PCH_PCI_SOFT_RESET	0x01fc

क्रमागत c_can_pci_reg_align अणु
	C_CAN_REG_ALIGN_16,
	C_CAN_REG_ALIGN_32,
	C_CAN_REG_32,
पूर्ण;

काष्ठा c_can_pci_data अणु
	/* Specअगरy अगर is C_CAN or D_CAN */
	क्रमागत c_can_dev_id type;
	/* Number of message objects */
	अचिन्हित पूर्णांक msg_obj_num;
	/* Set the रेजिस्टर alignment in the memory */
	क्रमागत c_can_pci_reg_align reg_align;
	/* Set the frequency */
	अचिन्हित पूर्णांक freq;
	/* PCI bar number */
	पूर्णांक bar;
	/* Callback क्रम reset */
	व्योम (*init)(स्थिर काष्ठा c_can_priv *priv, bool enable);
पूर्ण;

/* 16-bit c_can रेजिस्टरs can be arranged dअगरferently in the memory
 * architecture of dअगरferent implementations. For example: 16-bit
 * रेजिस्टरs can be aligned to a 16-bit boundary or 32-bit boundary etc.
 * Handle the same by providing a common पढ़ो/ग_लिखो पूर्णांकerface.
 */
अटल u16 c_can_pci_पढ़ो_reg_aligned_to_16bit(स्थिर काष्ठा c_can_priv *priv,
					       क्रमागत reg index)
अणु
	वापस पढ़ोw(priv->base + priv->regs[index]);
पूर्ण

अटल व्योम c_can_pci_ग_लिखो_reg_aligned_to_16bit(स्थिर काष्ठा c_can_priv *priv,
						 क्रमागत reg index, u16 val)
अणु
	ग_लिखोw(val, priv->base + priv->regs[index]);
पूर्ण

अटल u16 c_can_pci_पढ़ो_reg_aligned_to_32bit(स्थिर काष्ठा c_can_priv *priv,
					       क्रमागत reg index)
अणु
	वापस पढ़ोw(priv->base + 2 * priv->regs[index]);
पूर्ण

अटल व्योम c_can_pci_ग_लिखो_reg_aligned_to_32bit(स्थिर काष्ठा c_can_priv *priv,
						 क्रमागत reg index, u16 val)
अणु
	ग_लिखोw(val, priv->base + 2 * priv->regs[index]);
पूर्ण

अटल u16 c_can_pci_पढ़ो_reg_32bit(स्थिर काष्ठा c_can_priv *priv,
				    क्रमागत reg index)
अणु
	वापस (u16)ioपढ़ो32(priv->base + 2 * priv->regs[index]);
पूर्ण

अटल व्योम c_can_pci_ग_लिखो_reg_32bit(स्थिर काष्ठा c_can_priv *priv,
				      क्रमागत reg index, u16 val)
अणु
	ioग_लिखो32((u32)val, priv->base + 2 * priv->regs[index]);
पूर्ण

अटल u32 c_can_pci_पढ़ो_reg32(स्थिर काष्ठा c_can_priv *priv, क्रमागत reg index)
अणु
	u32 val;

	val = priv->पढ़ो_reg(priv, index);
	val |= ((u32)priv->पढ़ो_reg(priv, index + 1)) << 16;

	वापस val;
पूर्ण

अटल व्योम c_can_pci_ग_लिखो_reg32(स्थिर काष्ठा c_can_priv *priv, क्रमागत reg index,
				  u32 val)
अणु
	priv->ग_लिखो_reg(priv, index + 1, val >> 16);
	priv->ग_लिखो_reg(priv, index, val);
पूर्ण

अटल व्योम c_can_pci_reset_pch(स्थिर काष्ठा c_can_priv *priv, bool enable)
अणु
	अगर (enable) अणु
		u32 __iomem *addr = priv->base + PCH_PCI_SOFT_RESET;

		/* ग_लिखो to sw reset रेजिस्टर */
		ioग_लिखो32(1, addr);
		ioग_लिखो32(0, addr);
	पूर्ण
पूर्ण

अटल पूर्णांक c_can_pci_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा c_can_pci_data *c_can_pci_data = (व्योम *)ent->driver_data;
	काष्ठा c_can_priv *priv;
	काष्ठा net_device *dev;
	व्योम __iomem *addr;
	पूर्णांक ret;

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "pci_enable_device FAILED\n");
		जाओ out;
	पूर्ण

	ret = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (ret) अणु
		dev_err(&pdev->dev, "pci_request_regions FAILED\n");
		जाओ out_disable_device;
	पूर्ण

	ret = pci_enable_msi(pdev);
	अगर (!ret) अणु
		dev_info(&pdev->dev, "MSI enabled\n");
		pci_set_master(pdev);
	पूर्ण

	addr = pci_iomap(pdev, c_can_pci_data->bar,
			 pci_resource_len(pdev, c_can_pci_data->bar));
	अगर (!addr) अणु
		dev_err(&pdev->dev,
			"device has no PCI memory resources, failing adapter\n");
		ret = -ENOMEM;
		जाओ out_release_regions;
	पूर्ण

	/* allocate the c_can device */
	dev = alloc_c_can_dev(c_can_pci_data->msg_obj_num);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ out_iounmap;
	पूर्ण

	priv = netdev_priv(dev);
	pci_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	dev->irq = pdev->irq;
	priv->base = addr;
	priv->device = &pdev->dev;

	अगर (!c_can_pci_data->freq) अणु
		dev_err(&pdev->dev, "no clock frequency defined\n");
		ret = -ENODEV;
		जाओ out_मुक्त_c_can;
	पूर्ण अन्यथा अणु
		priv->can.घड़ी.freq = c_can_pci_data->freq;
	पूर्ण

	/* Configure CAN type */
	चयन (c_can_pci_data->type) अणु
	हाल BOSCH_C_CAN:
		priv->regs = reg_map_c_can;
		अवरोध;
	हाल BOSCH_D_CAN:
		priv->regs = reg_map_d_can;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out_मुक्त_c_can;
	पूर्ण

	priv->type = c_can_pci_data->type;

	/* Configure access to रेजिस्टरs */
	चयन (c_can_pci_data->reg_align) अणु
	हाल C_CAN_REG_ALIGN_32:
		priv->पढ़ो_reg = c_can_pci_पढ़ो_reg_aligned_to_32bit;
		priv->ग_लिखो_reg = c_can_pci_ग_लिखो_reg_aligned_to_32bit;
		अवरोध;
	हाल C_CAN_REG_ALIGN_16:
		priv->पढ़ो_reg = c_can_pci_पढ़ो_reg_aligned_to_16bit;
		priv->ग_लिखो_reg = c_can_pci_ग_लिखो_reg_aligned_to_16bit;
		अवरोध;
	हाल C_CAN_REG_32:
		priv->पढ़ो_reg = c_can_pci_पढ़ो_reg_32bit;
		priv->ग_लिखो_reg = c_can_pci_ग_लिखो_reg_32bit;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out_मुक्त_c_can;
	पूर्ण
	priv->पढ़ो_reg32 = c_can_pci_पढ़ो_reg32;
	priv->ग_लिखो_reg32 = c_can_pci_ग_लिखो_reg32;

	priv->raminit = c_can_pci_data->init;

	ret = रेजिस्टर_c_can_dev(dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "registering %s failed (err=%d)\n",
			KBUILD_MODNAME, ret);
		जाओ out_मुक्त_c_can;
	पूर्ण

	dev_dbg(&pdev->dev, "%s device registered (regs=%p, irq=%d)\n",
		KBUILD_MODNAME, priv->regs, dev->irq);

	वापस 0;

out_मुक्त_c_can:
	मुक्त_c_can_dev(dev);
out_iounmap:
	pci_iounmap(pdev, addr);
out_release_regions:
	pci_disable_msi(pdev);
	pci_clear_master(pdev);
	pci_release_regions(pdev);
out_disable_device:
	pci_disable_device(pdev);
out:
	वापस ret;
पूर्ण

अटल व्योम c_can_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	व्योम __iomem *addr = priv->base;

	unरेजिस्टर_c_can_dev(dev);

	मुक्त_c_can_dev(dev);

	pci_iounmap(pdev, addr);
	pci_disable_msi(pdev);
	pci_clear_master(pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा c_can_pci_data c_can_sta2x11 = अणु
	.type = BOSCH_C_CAN,
	.msg_obj_num = 32,
	.reg_align = C_CAN_REG_ALIGN_32,
	.freq = 52000000, /* 52 Mhz */
	.bar = 0,
पूर्ण;

अटल स्थिर काष्ठा c_can_pci_data c_can_pch = अणु
	.type = BOSCH_C_CAN,
	.msg_obj_num = 32,
	.reg_align = C_CAN_REG_32,
	.freq = 50000000, /* 50 MHz */
	.init = c_can_pci_reset_pch,
	.bar = 1,
पूर्ण;

#घोषणा C_CAN_ID(_vend, _dev, _driverdata) अणु		\
	PCI_DEVICE(_vend, _dev),			\
	.driver_data = (अचिन्हित दीर्घ)&(_driverdata),	\
पूर्ण

अटल स्थिर काष्ठा pci_device_id c_can_pci_tbl[] = अणु
	C_CAN_ID(PCI_VENDOR_ID_STMICRO, PCI_DEVICE_ID_STMICRO_CAN,
		 c_can_sta2x11),
	C_CAN_ID(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_PCH_CAN,
		 c_can_pch),
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा pci_driver c_can_pci_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = c_can_pci_tbl,
	.probe = c_can_pci_probe,
	.हटाओ = c_can_pci_हटाओ,
पूर्ण;

module_pci_driver(c_can_pci_driver);

MODULE_AUTHOR("Federico Vaga <federico.vaga@gmail.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("PCI CAN bus driver for Bosch C_CAN/D_CAN controller");
MODULE_DEVICE_TABLE(pci, c_can_pci_tbl);
