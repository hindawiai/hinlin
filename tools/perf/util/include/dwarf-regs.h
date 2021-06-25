<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_DWARF_REGS_H_
#घोषणा _PERF_DWARF_REGS_H_

#अगर_घोषित HAVE_DWARF_SUPPORT
स्थिर अक्षर *get_arch_regstr(अचिन्हित पूर्णांक n);
/*
 * get_dwarf_regstr - Returns ftrace रेजिस्टर string from DWARF regnum
 * n: DWARF रेजिस्टर number
 * machine: ELF machine signature (EM_*)
 */
स्थिर अक्षर *get_dwarf_regstr(अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक machine);
#पूर्ण_अगर

#अगर_घोषित HAVE_ARCH_REGS_QUERY_REGISTER_OFFSET
/*
 * Arch should support fetching the offset of a रेजिस्टर in pt_regs
 * by its name. See kernel's regs_query_रेजिस्टर_offset in
 * arch/xxx/kernel/ptrace.c.
 */
पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name);
#पूर्ण_अगर
#पूर्ण_अगर
