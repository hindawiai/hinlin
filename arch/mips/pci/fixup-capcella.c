<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  fixup-cappcela.c, The ZAO Networks Capcella specअगरic PCI fixups.
 *
 *  Copyright (C) 2002,2004  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/vr41xx/capcella.h>

/*
 * Shortcuts
 */
#घोषणा INT1	RTL8139_1_IRQ
#घोषणा INT2	RTL8139_2_IRQ
#घोषणा INTA	PC104PLUS_INTA_IRQ
#घोषणा INTB	PC104PLUS_INTB_IRQ
#घोषणा INTC	PC104PLUS_INTC_IRQ
#घोषणा INTD	PC104PLUS_INTD_IRQ

अटल अक्षर irq_tab_capcella[][5] = अणु
 [11] = अणु -1, INT1, INT1, INT1, INT1 पूर्ण,
 [12] = अणु -1, INT2, INT2, INT2, INT2 पूर्ण,
 [14] = अणु -1, INTA, INTB, INTC, INTD पूर्ण
पूर्ण;

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	वापस irq_tab_capcella[slot][pin];
पूर्ण

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण
