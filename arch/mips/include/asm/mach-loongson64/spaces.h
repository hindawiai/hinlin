<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_LOONGSON64_SPACES_H_
#घोषणा __ASM_MACH_LOONGSON64_SPACES_H_

#अगर defined(CONFIG_64BIT)
#घोषणा CAC_BASE        _AC(0x9800000000000000, UL)
#पूर्ण_अगर /* CONFIG_64BIT */

/* Skip 128k to trap शून्य poपूर्णांकer dereferences */
#घोषणा PCI_IOBASE	_AC(0xc000000000000000 + SZ_128K, UL)
#घोषणा PCI_IOSIZE	SZ_16M
#घोषणा MAP_BASE	(PCI_IOBASE + PCI_IOSIZE)

#घोषणा IO_SPACE_LIMIT  (PCI_IOSIZE - 1)

#समावेश <यंत्र/mach-generic/spaces.h>
#पूर्ण_अगर
