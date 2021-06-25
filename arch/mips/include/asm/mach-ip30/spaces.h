<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2016 Joshua Kinard <kumba@gentoo.org>
 *
 */
#अगर_अघोषित _ASM_MACH_IP30_SPACES_H
#घोषणा _ASM_MACH_IP30_SPACES_H

/*
 * Memory in IP30/Octane is offset 512MB in the physical address space.
 */
#घोषणा PHYS_OFFSET	_AC(0x20000000, UL)

#अगर_घोषित CONFIG_64BIT
#घोषणा CAC_BASE	_AC(0xA800000000000000, UL)
#पूर्ण_अगर

#समावेश <यंत्र/mach-generic/spaces.h>

#पूर्ण_अगर /* _ASM_MACH_IP30_SPACES_H */
