<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	matrox_w1.c
 *
 * Copyright (c) 2004 Evgeniy Polyakov <zbr@ioremap.net>
 */

#समावेश <यंत्र/types.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/पन.स>

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/pci.h>

#समावेश <linux/w1.h>

/*
 * Matrox G400 DDC रेजिस्टरs.
 */

#घोषणा MATROX_G400_DDC_CLK		(1<<4)
#घोषणा MATROX_G400_DDC_DATA		(1<<1)

#घोषणा MATROX_BASE			0x3C00
#घोषणा MATROX_STATUS			0x1e14

#घोषणा MATROX_PORT_INDEX_OFFSET	0x00
#घोषणा MATROX_PORT_DATA_OFFSET		0x0A

#घोषणा MATROX_GET_CONTROL		0x2A
#घोषणा MATROX_GET_DATA			0x2B
#घोषणा MATROX_CURSOR_CTL		0x06

काष्ठा matrox_device
अणु
	व्योम __iomem *base_addr;
	व्योम __iomem *port_index;
	व्योम __iomem *port_data;
	u8 data_mask;

	अचिन्हित दीर्घ phys_addr;
	व्योम __iomem *virt_addr;
	अचिन्हित दीर्घ found;

	काष्ठा w1_bus_master *bus_master;
पूर्ण;

/*
 * These functions पढ़ो and ग_लिखो DDC Data bit.
 *
 * Using tristate pins, since i can't find any खोलो-drain pin in whole motherboard.
 * Unक्रमtunately we can't connect to Intel's 82801xx IO controller
 * since we करोn't know motherboard schema, which has pretty unused(may be not) GPIO.
 *
 * I've heard that PIIX also has खोलो drain pin.
 *
 * Port mapping.
 */
अटल __अंतरभूत__ u8 matrox_w1_पढ़ो_reg(काष्ठा matrox_device *dev, u8 reg)
अणु
	u8 ret;

	ग_लिखोb(reg, dev->port_index);
	ret = पढ़ोb(dev->port_data);
	barrier();

	वापस ret;
पूर्ण

अटल __अंतरभूत__ व्योम matrox_w1_ग_लिखो_reg(काष्ठा matrox_device *dev, u8 reg, u8 val)
अणु
	ग_लिखोb(reg, dev->port_index);
	ग_लिखोb(val, dev->port_data);
	wmb();
पूर्ण

अटल व्योम matrox_w1_ग_लिखो_ddc_bit(व्योम *data, u8 bit)
अणु
	u8 ret;
	काष्ठा matrox_device *dev = data;

	अगर (bit)
		bit = 0;
	अन्यथा
		bit = dev->data_mask;

	ret = matrox_w1_पढ़ो_reg(dev, MATROX_GET_CONTROL);
	matrox_w1_ग_लिखो_reg(dev, MATROX_GET_CONTROL, ((ret & ~dev->data_mask) | bit));
	matrox_w1_ग_लिखो_reg(dev, MATROX_GET_DATA, 0x00);
पूर्ण

अटल u8 matrox_w1_पढ़ो_ddc_bit(व्योम *data)
अणु
	u8 ret;
	काष्ठा matrox_device *dev = data;

	ret = matrox_w1_पढ़ो_reg(dev, MATROX_GET_DATA);

	वापस ret;
पूर्ण

अटल व्योम matrox_w1_hw_init(काष्ठा matrox_device *dev)
अणु
	matrox_w1_ग_लिखो_reg(dev, MATROX_GET_DATA, 0xFF);
	matrox_w1_ग_लिखो_reg(dev, MATROX_GET_CONTROL, 0x00);
पूर्ण

अटल पूर्णांक matrox_w1_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा matrox_device *dev;
	पूर्णांक err;

	अगर (pdev->venकरोr != PCI_VENDOR_ID_MATROX || pdev->device != PCI_DEVICE_ID_MATROX_G400)
		वापस -ENODEV;

	dev = kzalloc(माप(काष्ठा matrox_device) +
		       माप(काष्ठा w1_bus_master), GFP_KERNEL);
	अगर (!dev) अणु
		dev_err(&pdev->dev,
			"%s: Failed to create new matrox_device object.\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण


	dev->bus_master = (काष्ठा w1_bus_master *)(dev + 1);

	/*
	 * True क्रम G400, क्रम some other we need resource 0, see drivers/video/matrox/matroxfb_base.c
	 */

	dev->phys_addr = pci_resource_start(pdev, 1);

	dev->virt_addr = ioremap(dev->phys_addr, 16384);
	अगर (!dev->virt_addr) अणु
		dev_err(&pdev->dev, "%s: failed to ioremap(0x%lx, %d).\n",
			__func__, dev->phys_addr, 16384);
		err = -EIO;
		जाओ err_out_मुक्त_device;
	पूर्ण

	dev->base_addr = dev->virt_addr + MATROX_BASE;
	dev->port_index = dev->base_addr + MATROX_PORT_INDEX_OFFSET;
	dev->port_data = dev->base_addr + MATROX_PORT_DATA_OFFSET;
	dev->data_mask = (MATROX_G400_DDC_DATA);

	matrox_w1_hw_init(dev);

	dev->bus_master->data = dev;
	dev->bus_master->पढ़ो_bit = &matrox_w1_पढ़ो_ddc_bit;
	dev->bus_master->ग_लिखो_bit = &matrox_w1_ग_लिखो_ddc_bit;

	err = w1_add_master_device(dev->bus_master);
	अगर (err)
		जाओ err_out_मुक्त_device;

	pci_set_drvdata(pdev, dev);

	dev->found = 1;

	dev_info(&pdev->dev, "Matrox G400 GPIO transport layer for 1-wire.\n");

	वापस 0;

err_out_मुक्त_device:
	अगर (dev->virt_addr)
		iounmap(dev->virt_addr);
	kमुक्त(dev);

	वापस err;
पूर्ण

अटल व्योम matrox_w1_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा matrox_device *dev = pci_get_drvdata(pdev);

	अगर (dev->found) अणु
		w1_हटाओ_master_device(dev->bus_master);
		iounmap(dev->virt_addr);
	पूर्ण
	kमुक्त(dev);
पूर्ण

अटल काष्ठा pci_device_id matrox_w1_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MATROX, PCI_DEVICE_ID_MATROX_G400) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, matrox_w1_tbl);

अटल काष्ठा pci_driver matrox_w1_pci_driver = अणु
	.name = "matrox_w1",
	.id_table = matrox_w1_tbl,
	.probe = matrox_w1_probe,
	.हटाओ = matrox_w1_हटाओ,
पूर्ण;
module_pci_driver(matrox_w1_pci_driver);

MODULE_AUTHOR("Evgeniy Polyakov <zbr@ioremap.net>");
MODULE_DESCRIPTION("Driver for transport(Dallas 1-wire protocol) over VGA DDC(matrox gpio).");
MODULE_LICENSE("GPL");
