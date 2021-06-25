<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Definitions क्रम Device tree / OpenFirmware handling on X86
 *
 * based on arch/घातerpc/include/यंत्र/prom.h which is
 *         Copyright (C) 1996-2005 Paul Mackerras.
 */

#अगर_अघोषित _ASM_X86_PROM_H
#घोषणा _ASM_X86_PROM_H
#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/of.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/irq.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/setup.h>

#अगर_घोषित CONFIG_OF
बाह्य पूर्णांक of_ioapic;
बाह्य u64 initial_dtb;
बाह्य व्योम add_dtb(u64 data);
व्योम x86_of_pci_init(व्योम);
व्योम x86_dtb_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम add_dtb(u64 data) अणु पूर्ण
अटल अंतरभूत व्योम x86_of_pci_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम x86_dtb_init(व्योम) अणु पूर्ण
#घोषणा of_ioapic 0
#पूर्ण_अगर

बाह्य अक्षर cmd_line[COMMAND_LINE_SIZE];

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर
