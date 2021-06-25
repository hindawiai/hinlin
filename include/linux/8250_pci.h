<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम PCI support.
 */
#घोषणा FL_BASE_MASK		0x0007
#घोषणा FL_BASE0		0x0000
#घोषणा FL_BASE1		0x0001
#घोषणा FL_BASE2		0x0002
#घोषणा FL_BASE3		0x0003
#घोषणा FL_BASE4		0x0004
#घोषणा FL_GET_BASE(x)		(x & FL_BASE_MASK)

/* Use successive BARs (PCI base address रेजिस्टरs),
   अन्यथा use offset पूर्णांकo some specअगरied BAR */
#घोषणा FL_BASE_BARS		0x0008

/* करो not assign an irq */
#घोषणा FL_NOIRQ		0x0080

/* Use the Base address रेजिस्टर size to cap number of ports */
#घोषणा FL_REGION_SZ_CAP	0x0100

काष्ठा pciserial_board अणु
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक num_ports;
	अचिन्हित पूर्णांक base_baud;
	अचिन्हित पूर्णांक uart_offset;
	अचिन्हित पूर्णांक reg_shअगरt;
	अचिन्हित पूर्णांक first_offset;
पूर्ण;

काष्ठा serial_निजी;

काष्ठा serial_निजी *
pciserial_init_ports(काष्ठा pci_dev *dev, स्थिर काष्ठा pciserial_board *board);
व्योम pciserial_हटाओ_ports(काष्ठा serial_निजी *priv);
व्योम pciserial_suspend_ports(काष्ठा serial_निजी *priv);
व्योम pciserial_resume_ports(काष्ठा serial_निजी *priv);
