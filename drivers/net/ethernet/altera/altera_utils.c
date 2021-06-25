<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Altera TSE SGDMA and MSGDMA Linux driver
 * Copyright (C) 2014 Altera Corporation. All rights reserved
 */

#समावेश "altera_tse.h"
#समावेश "altera_utils.h"

व्योम tse_set_bit(व्योम __iomem *ioaddr, माप_प्रकार offs, u32 bit_mask)
अणु
	u32 value = csrrd32(ioaddr, offs);
	value |= bit_mask;
	csrwr32(value, ioaddr, offs);
पूर्ण

व्योम tse_clear_bit(व्योम __iomem *ioaddr, माप_प्रकार offs, u32 bit_mask)
अणु
	u32 value = csrrd32(ioaddr, offs);
	value &= ~bit_mask;
	csrwr32(value, ioaddr, offs);
पूर्ण

पूर्णांक tse_bit_is_set(व्योम __iomem *ioaddr, माप_प्रकार offs, u32 bit_mask)
अणु
	u32 value = csrrd32(ioaddr, offs);
	वापस (value & bit_mask) ? 1 : 0;
पूर्ण

पूर्णांक tse_bit_is_clear(व्योम __iomem *ioaddr, माप_प्रकार offs, u32 bit_mask)
अणु
	u32 value = csrrd32(ioaddr, offs);
	वापस (value & bit_mask) ? 0 : 1;
पूर्ण
