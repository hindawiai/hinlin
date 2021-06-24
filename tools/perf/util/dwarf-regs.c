<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dwarf-regs.c : Mapping of DWARF debug रेजिस्टर numbers पूर्णांकo रेजिस्टर names.
 *
 * Written by: Masami Hiramatsu <mhiramat@kernel.org>
 */

#समावेश <debug.h>
#समावेश <dwarf-regs.h>
#समावेश <elf.h>
#समावेश <linux/kernel.h>

#अगर_अघोषित EM_AARCH64
#घोषणा EM_AARCH64	183  /* ARM 64 bit */
#पूर्ण_अगर

/* Define स्थिर अक्षर * अणुarchपूर्ण_रेजिस्टर_tbl[] */
#घोषणा DEFINE_DWARF_REGSTR_TABLE
#समावेश "../arch/x86/include/dwarf-regs-table.h"
#समावेश "../arch/arm/include/dwarf-regs-table.h"
#समावेश "../arch/arm64/include/dwarf-regs-table.h"
#समावेश "../arch/sh/include/dwarf-regs-table.h"
#समावेश "../arch/powerpc/include/dwarf-regs-table.h"
#समावेश "../arch/s390/include/dwarf-regs-table.h"
#समावेश "../arch/sparc/include/dwarf-regs-table.h"
#समावेश "../arch/xtensa/include/dwarf-regs-table.h"
#समावेश "../arch/mips/include/dwarf-regs-table.h"

#घोषणा __get_dwarf_regstr(tbl, n) (((n) < ARRAY_SIZE(tbl)) ? (tbl)[(n)] : शून्य)

/* Return architecture dependent रेजिस्टर string (क्रम kprobe-tracer) */
स्थिर अक्षर *get_dwarf_regstr(अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक machine)
अणु
	चयन (machine) अणु
	हाल EM_NONE:	/* Generic arch - use host arch */
		वापस get_arch_regstr(n);
	हाल EM_386:
		वापस __get_dwarf_regstr(x86_32_regstr_tbl, n);
	हाल EM_X86_64:
		वापस __get_dwarf_regstr(x86_64_regstr_tbl, n);
	हाल EM_ARM:
		वापस __get_dwarf_regstr(arm_regstr_tbl, n);
	हाल EM_AARCH64:
		वापस __get_dwarf_regstr(aarch64_regstr_tbl, n);
	हाल EM_SH:
		वापस __get_dwarf_regstr(sh_regstr_tbl, n);
	हाल EM_S390:
		वापस __get_dwarf_regstr(s390_regstr_tbl, n);
	हाल EM_PPC:
	हाल EM_PPC64:
		वापस __get_dwarf_regstr(घातerpc_regstr_tbl, n);
	हाल EM_SPARC:
	हाल EM_SPARCV9:
		वापस __get_dwarf_regstr(sparc_regstr_tbl, n);
	हाल EM_XTENSA:
		वापस __get_dwarf_regstr(xtensa_regstr_tbl, n);
	हाल EM_MIPS:
		वापस __get_dwarf_regstr(mips_regstr_tbl, n);
	शेष:
		pr_err("ELF MACHINE %x is not supported.\n", machine);
	पूर्ण
	वापस शून्य;
पूर्ण
