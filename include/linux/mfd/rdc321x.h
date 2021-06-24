<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __RDC321X_MFD_H
#घोषणा __RDC321X_MFD_H

#समावेश <linux/types.h>
#समावेश <linux/pci.h>

/* Offsets to be accessed in the southbridge PCI
 * device configuration रेजिस्टर */
#घोषणा RDC321X_WDT_CTRL	0x44
#घोषणा RDC321X_GPIO_CTRL_REG1	0x48
#घोषणा RDC321X_GPIO_DATA_REG1	0x4c
#घोषणा RDC321X_GPIO_CTRL_REG2	0x84
#घोषणा RDC321X_GPIO_DATA_REG2	0x88

#घोषणा RDC321X_NUM_GPIO	59

काष्ठा rdc321x_gpio_pdata अणु
	काष्ठा pci_dev *sb_pdev;
	अचिन्हित max_gpios;
पूर्ण;

काष्ठा rdc321x_wdt_pdata अणु
	काष्ठा pci_dev *sb_pdev;
पूर्ण;

#पूर्ण_अगर /* __RDC321X_MFD_H */
