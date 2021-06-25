<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/mach-ixp4xx/include/mach/hardware.h 
 *
 * Copyright (C) 2002 Intel Corporation.
 * Copyright (C) 2003-2004 MontaVista Software, Inc.
 */

/*
 * Hardware definitions क्रम IXP4xx based प्रणालीs
 */

#अगर_अघोषित __ASM_ARCH_HARDWARE_H__
#घोषणा __ASM_ARCH_HARDWARE_H__

#अगर_घोषित CONFIG_IXP4XX_INसूचीECT_PCI
#घोषणा PCIBIOS_MAX_MEM		0x4FFFFFFF
#अन्यथा
#घोषणा PCIBIOS_MAX_MEM		0x4BFFFFFF
#पूर्ण_अगर

/* Register locations and bits */
#समावेश "ixp4xx-regs.h"

#अगर_अघोषित __ASSEMBLER__
#समावेश <mach/cpu.h>
#पूर्ण_अगर

/* Platक्रमm helper functions and definitions */
#समावेश "platform.h"

#पूर्ण_अगर  /* _ASM_ARCH_HARDWARE_H */
