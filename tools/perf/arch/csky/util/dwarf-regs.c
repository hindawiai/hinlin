<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2019 Hangzhou C-SKY Microप्रणालीs co.,ltd.
// Mapping of DWARF debug रेजिस्टर numbers पूर्णांकo रेजिस्टर names.

#समावेश <मानकघोष.स>
#समावेश <dwarf-regs.h>

#अगर defined(__CSKYABIV2__)
#घोषणा CSKY_MAX_REGS 73
स्थिर अक्षर *csky_dwarf_regs_table[CSKY_MAX_REGS] = अणु
	/* r0 ~ r8 */
	"%a0", "%a1", "%a2", "%a3", "%regs0", "%regs1", "%regs2", "%regs3",
	/* r9 ~ r15 */
	"%regs4", "%regs5", "%regs6", "%regs7", "%regs8", "%regs9", "%sp",
	"%lr",
	/* r16 ~ r23 */
	"%exregs0", "%exregs1", "%exregs2", "%exregs3", "%exregs4",
	"%exregs5", "%exregs6", "%exregs7",
	/* r24 ~ r31 */
	"%exregs8", "%exregs9", "%exregs10", "%exregs11", "%exregs12",
	"%exregs13", "%exregs14", "%tls",
	"%pc", शून्य, शून्य, शून्य, "%hi", "%lo", शून्य, शून्य,
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	"%epc",
पूर्ण;
#अन्यथा
#घोषणा CSKY_MAX_REGS 57
स्थिर अक्षर *csky_dwarf_regs_table[CSKY_MAX_REGS] = अणु
	/* r0 ~ r8 */
	"%sp", "%regs9", "%a0", "%a1", "%a2", "%a3", "%regs0", "%regs1",
	/* r9 ~ r15 */
	"%regs2", "%regs3", "%regs4", "%regs5", "%regs6", "%regs7", "%regs8",
	"%lr",
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
	"%epc",
पूर्ण;
#पूर्ण_अगर

स्थिर अक्षर *get_arch_regstr(अचिन्हित पूर्णांक n)
अणु
	वापस (n < CSKY_MAX_REGS) ? csky_dwarf_regs_table[n] : शून्य;
पूर्ण
