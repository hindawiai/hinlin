<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* drivers/aपंचांग/tonga.h - Efficient Networks Tonga (PCI bridge) declarations */
 
/* Written 1995 by Werner Almesberger, EPFL LRC */
 

#अगर_अघोषित DRIVER_ATM_TONGA_H
#घोषणा DRIVER_ATM_TONGA_H

#घोषणा PCI_TONGA_CTRL	0x60	/* control रेजिस्टर */

#घोषणा END_SWAP_DMA	0x80	/* endian swap on DMA */
#घोषणा END_SWAP_BYTE	0x40	/* endian swap on slave byte accesses */
#घोषणा END_SWAP_WORD	0x20	/* endian swap on slave word accesses */
#घोषणा SEPROM_MAGIC	0x0c	/* obscure required pattern (ASIC only) */
#घोषणा SEPROM_DATA	0x02	/* serial EEPROM data (ASIC only) */
#घोषणा SEPROM_CLK	0x01	/* serial EEPROM घड़ी (ASIC only) */

#घोषणा SEPROM_ESI_BASE	64	/* start of ESI in serial EEPROM */

#पूर्ण_अगर
