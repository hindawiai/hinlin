<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_PARPORT_H
#घोषणा __ASM_GENERIC_PARPORT_H

/*
 * An ISA bus may have i8255 parallel ports at well-known
 * locations in the I/O space, which are scanned by
 * parport_pc_find_isa_ports.
 *
 * Without ISA support, the driver will only attach
 * to devices on the PCI bus.
 */

अटल पूर्णांक parport_pc_find_isa_ports(पूर्णांक स्वतःirq, पूर्णांक स्वतःdma);
अटल पूर्णांक parport_pc_find_nonpci_ports(पूर्णांक स्वतःirq, पूर्णांक स्वतःdma)
अणु
#अगर_घोषित CONFIG_ISA
	वापस parport_pc_find_isa_ports(स्वतःirq, स्वतःdma);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __ASM_GENERIC_PARPORT_H */
