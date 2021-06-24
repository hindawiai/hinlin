<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 Hangzhou C-SKY Microप्रणालीs co.,ltd.
 * Mapping of DWARF debug रेजिस्टर numbers पूर्णांकo रेजिस्टर names.
 */

#समावेश <मानकघोष.स>
#समावेश <त्रुटिसं.स> /* क्रम EINVAL */
#समावेश <माला.स> /* क्रम म_भेद */
#समावेश <dwarf-regs.h>

काष्ठा pt_regs_dwarfnum अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक dwarfnum;
पूर्ण;

#घोषणा REG_DWARFNUM_NAME(r, num) अणु.name = r, .dwarfnum = numपूर्ण
#घोषणा REG_DWARFNUM_END अणु.name = शून्य, .dwarfnum = 0पूर्ण

काष्ठा pt_regs_dwarfnum riscv_dwarf_regs_table[] = अणु
	REG_DWARFNUM_NAME("%zero", 0),
	REG_DWARFNUM_NAME("%ra", 1),
	REG_DWARFNUM_NAME("%sp", 2),
	REG_DWARFNUM_NAME("%gp", 3),
	REG_DWARFNUM_NAME("%tp", 4),
	REG_DWARFNUM_NAME("%t0", 5),
	REG_DWARFNUM_NAME("%t1", 6),
	REG_DWARFNUM_NAME("%t2", 7),
	REG_DWARFNUM_NAME("%s0", 8),
	REG_DWARFNUM_NAME("%s1", 9),
	REG_DWARFNUM_NAME("%a0", 10),
	REG_DWARFNUM_NAME("%a1", 11),
	REG_DWARFNUM_NAME("%a2", 12),
	REG_DWARFNUM_NAME("%a3", 13),
	REG_DWARFNUM_NAME("%a4", 14),
	REG_DWARFNUM_NAME("%a5", 15),
	REG_DWARFNUM_NAME("%a6", 16),
	REG_DWARFNUM_NAME("%a7", 17),
	REG_DWARFNUM_NAME("%s2", 18),
	REG_DWARFNUM_NAME("%s3", 19),
	REG_DWARFNUM_NAME("%s4", 20),
	REG_DWARFNUM_NAME("%s5", 21),
	REG_DWARFNUM_NAME("%s6", 22),
	REG_DWARFNUM_NAME("%s7", 23),
	REG_DWARFNUM_NAME("%s8", 24),
	REG_DWARFNUM_NAME("%s9", 25),
	REG_DWARFNUM_NAME("%s10", 26),
	REG_DWARFNUM_NAME("%s11", 27),
	REG_DWARFNUM_NAME("%t3", 28),
	REG_DWARFNUM_NAME("%t4", 29),
	REG_DWARFNUM_NAME("%t5", 30),
	REG_DWARFNUM_NAME("%t6", 31),
	REG_DWARFNUM_END,
पूर्ण;

#घोषणा RISCV_MAX_REGS ((माप(riscv_dwarf_regs_table) / \
		 माप(riscv_dwarf_regs_table[0])) - 1)

स्थिर अक्षर *get_arch_regstr(अचिन्हित पूर्णांक n)
अणु
	वापस (n < RISCV_MAX_REGS) ? riscv_dwarf_regs_table[n].name : शून्य;
पूर्ण

पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा pt_regs_dwarfnum *roff;

	क्रम (roff = riscv_dwarf_regs_table; roff->name; roff++)
		अगर (!म_भेद(roff->name, name))
			वापस roff->dwarfnum;
	वापस -EINVAL;
पूर्ण
