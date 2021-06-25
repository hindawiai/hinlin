<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Specअगरic M_CAN Glue
 *
 * Copyright (C) 2018-2020 Intel Corporation
 * Author: Felipe Balbi (Intel)
 * Author: Jarkko Nikula <jarkko.nikula@linux.पूर्णांकel.com>
 * Author: Raymond Tan <raymond.tan@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "m_can.h"

#घोषणा M_CAN_PCI_MMIO_BAR		0

#घोषणा M_CAN_CLOCK_FREQ_EHL		100000000
#घोषणा CTL_CSR_INT_CTL_OFFSET		0x508

काष्ठा m_can_pci_priv अणु
	काष्ठा m_can_classdev cdev;

	व्योम __iomem *base;
पूर्ण;

अटल अंतरभूत काष्ठा m_can_pci_priv *cdev_to_priv(काष्ठा m_can_classdev *cdev)
अणु
	वापस container_of(cdev, काष्ठा m_can_pci_priv, cdev);
पूर्ण

अटल u32 iomap_पढ़ो_reg(काष्ठा m_can_classdev *cdev, पूर्णांक reg)
अणु
	काष्ठा m_can_pci_priv *priv = cdev_to_priv(cdev);

	वापस पढ़ोl(priv->base + reg);
पूर्ण

अटल u32 iomap_पढ़ो_fअगरo(काष्ठा m_can_classdev *cdev, पूर्णांक offset)
अणु
	काष्ठा m_can_pci_priv *priv = cdev_to_priv(cdev);

	वापस पढ़ोl(priv->base + offset);
पूर्ण

अटल पूर्णांक iomap_ग_लिखो_reg(काष्ठा m_can_classdev *cdev, पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा m_can_pci_priv *priv = cdev_to_priv(cdev);

	ग_लिखोl(val, priv->base + reg);

	वापस 0;
पूर्ण

अटल पूर्णांक iomap_ग_लिखो_fअगरo(काष्ठा m_can_classdev *cdev, पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा m_can_pci_priv *priv = cdev_to_priv(cdev);

	ग_लिखोl(val, priv->base + offset);

	वापस 0;
पूर्ण

अटल काष्ठा m_can_ops m_can_pci_ops = अणु
	.पढ़ो_reg = iomap_पढ़ो_reg,
	.ग_लिखो_reg = iomap_ग_लिखो_reg,
	.ग_लिखो_fअगरo = iomap_ग_लिखो_fअगरo,
	.पढ़ो_fअगरo = iomap_पढ़ो_fअगरo,
पूर्ण;

अटल पूर्णांक m_can_pci_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device *dev = &pci->dev;
	काष्ठा m_can_classdev *mcan_class;
	काष्ठा m_can_pci_priv *priv;
	व्योम __iomem *base;
	पूर्णांक ret;

	ret = pcim_enable_device(pci);
	अगर (ret)
		वापस ret;

	pci_set_master(pci);

	ret = pcim_iomap_regions(pci, BIT(M_CAN_PCI_MMIO_BAR), pci_name(pci));
	अगर (ret)
		वापस ret;

	base = pcim_iomap_table(pci)[M_CAN_PCI_MMIO_BAR];

	अगर (!base) अणु
		dev_err(dev, "failed to map BARs\n");
		वापस -ENOMEM;
	पूर्ण

	mcan_class = m_can_class_allocate_dev(&pci->dev,
					      माप(काष्ठा m_can_pci_priv));
	अगर (!mcan_class)
		वापस -ENOMEM;

	priv = cdev_to_priv(mcan_class);

	priv->base = base;

	ret = pci_alloc_irq_vectors(pci, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (ret < 0)
		वापस ret;

	mcan_class->dev = &pci->dev;
	mcan_class->net->irq = pci_irq_vector(pci, 0);
	mcan_class->pm_घड़ी_support = 1;
	mcan_class->can.घड़ी.freq = id->driver_data;
	mcan_class->ops = &m_can_pci_ops;

	pci_set_drvdata(pci, mcan_class);

	ret = m_can_class_रेजिस्टर(mcan_class);
	अगर (ret)
		जाओ err;

	/* Enable पूर्णांकerrupt control at CAN wrapper IP */
	ग_लिखोl(0x1, base + CTL_CSR_INT_CTL_OFFSET);

	pm_runसमय_set_स्वतःsuspend_delay(dev, 1000);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_put_noidle(dev);
	pm_runसमय_allow(dev);

	वापस 0;

err:
	pci_मुक्त_irq_vectors(pci);
	वापस ret;
पूर्ण

अटल व्योम m_can_pci_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा m_can_classdev *mcan_class = pci_get_drvdata(pci);
	काष्ठा m_can_pci_priv *priv = cdev_to_priv(mcan_class);

	pm_runसमय_क्रमbid(&pci->dev);
	pm_runसमय_get_noresume(&pci->dev);

	/* Disable पूर्णांकerrupt control at CAN wrapper IP */
	ग_लिखोl(0x0, priv->base + CTL_CSR_INT_CTL_OFFSET);

	m_can_class_unरेजिस्टर(mcan_class);
	pci_मुक्त_irq_vectors(pci);
पूर्ण

अटल __maybe_unused पूर्णांक m_can_pci_suspend(काष्ठा device *dev)
अणु
	वापस m_can_class_suspend(dev);
पूर्ण

अटल __maybe_unused पूर्णांक m_can_pci_resume(काष्ठा device *dev)
अणु
	वापस m_can_class_resume(dev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(m_can_pci_pm_ops,
			 m_can_pci_suspend, m_can_pci_resume);

अटल स्थिर काष्ठा pci_device_id m_can_pci_id_table[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x4bc1), M_CAN_CLOCK_FREQ_EHL, पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4bc2), M_CAN_CLOCK_FREQ_EHL, पूर्ण,
	अणु  पूर्ण	/* Terminating Entry */
पूर्ण;
MODULE_DEVICE_TABLE(pci, m_can_pci_id_table);

अटल काष्ठा pci_driver m_can_pci_driver = अणु
	.name = "m_can_pci",
	.probe = m_can_pci_probe,
	.हटाओ = m_can_pci_हटाओ,
	.id_table = m_can_pci_id_table,
	.driver = अणु
		.pm = &m_can_pci_pm_ops,
	पूर्ण,
पूर्ण;

module_pci_driver(m_can_pci_driver);

MODULE_AUTHOR("Felipe Balbi (Intel)");
MODULE_AUTHOR("Jarkko Nikula <jarkko.nikula@linux.intel.com>");
MODULE_AUTHOR("Raymond Tan <raymond.tan@intel.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CAN bus driver for Bosch M_CAN controller on PCI bus");
