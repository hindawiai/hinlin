<शैली गुरु>
/* orinoco_pci.h
 *
 * Common code क्रम all Orinoco drivers क्रम PCI devices, including
 * both native PCI and PCMCIA-to-PCI bridges.
 *
 * Copyright (C) 2005, Pavel Roskin.
 * See मुख्य.c क्रम license.
 */

#अगर_अघोषित _ORINOCO_PCI_H
#घोषणा _ORINOCO_PCI_H

#समावेश <linux/netdevice.h>

/* Driver specअगरic data */
काष्ठा orinoco_pci_card अणु
	व्योम __iomem *bridge_io;
	व्योम __iomem *attr_io;
पूर्ण;

अटल पूर्णांक __maybe_unused orinoco_pci_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा orinoco_निजी *priv = pci_get_drvdata(pdev);

	orinoco_करोwn(priv);
	मुक्त_irq(pdev->irq, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused orinoco_pci_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा orinoco_निजी *priv = pci_get_drvdata(pdev);
	काष्ठा net_device *dev = priv->ndev;
	पूर्णांक err;

	err = request_irq(pdev->irq, orinoco_पूर्णांकerrupt, IRQF_SHARED,
			  dev->name, priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: cannot re-allocate IRQ on resume\n",
		       dev->name);
		वापस -EBUSY;
	पूर्ण

	वापस orinoco_up(priv);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(orinoco_pci_pm_ops,
			 orinoco_pci_suspend,
			 orinoco_pci_resume);

#पूर्ण_अगर /* _ORINOCO_PCI_H */
