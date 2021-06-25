<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __HARDWARE_H
#घोषणा __HARDWARE_H

#समावेश <यंत्र/types.h>

/*
 * Note about PCI IO space mappings
 *
 * To make IO space accesses efficient, we store भव addresses in
 * the IO resources.
 *
 * The PCI IO space is located at भव 0xfe000000 from physical
 * 0x90000000. The PCI BARs must be programmed with physical addresses,
 * but when we पढ़ो them, we convert them to भव addresses. See
 * arch/arm/plat-iop/pci.c.
 */

#अगर_अघोषित __ASSEMBLY__
व्योम iop32x_init_irq(व्योम);
#पूर्ण_अगर


/*
 * Generic chipset bits
 */
#समावेश "iop3xx.h"

/*
 * Board specअगरic bits
 */
#समावेश "glantank.h"
#समावेश "iq80321.h"
#समावेश "iq31244.h"
#समावेश "n2100.h"


#पूर्ण_अगर
