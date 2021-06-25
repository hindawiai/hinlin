<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Mapping of DWARF debug रेजिस्टर numbers पूर्णांकo रेजिस्टर names.
 *
 * Copyright (C) 2010 Will Deacon, ARM Ltd.
 */

#समावेश <मानकघोष.स>
#समावेश <linux/stringअगरy.h>
#समावेश <dwarf-regs.h>

काष्ठा pt_regs_dwarfnum अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक dwarfnum;
पूर्ण;

#घोषणा REG_DWARFNUM_NAME(r, num) अणु.name = r, .dwarfnum = numपूर्ण
#घोषणा GPR_DWARFNUM_NAME(num) \
	अणु.name = __stringअगरy(%r##num), .dwarfnum = numपूर्ण
#घोषणा REG_DWARFNUM_END अणु.name = शून्य, .dwarfnum = 0पूर्ण

/*
 * Reference:
 * http://infocenter.arm.com/help/topic/com.arm.करोc.ihi0040a/IHI0040A_aadwarf.pdf
 */
अटल स्थिर काष्ठा pt_regs_dwarfnum regdwarfnum_table[] = अणु
	GPR_DWARFNUM_NAME(0),
	GPR_DWARFNUM_NAME(1),
	GPR_DWARFNUM_NAME(2),
	GPR_DWARFNUM_NAME(3),
	GPR_DWARFNUM_NAME(4),
	GPR_DWARFNUM_NAME(5),
	GPR_DWARFNUM_NAME(6),
	GPR_DWARFNUM_NAME(7),
	GPR_DWARFNUM_NAME(8),
	GPR_DWARFNUM_NAME(9),
	GPR_DWARFNUM_NAME(10),
	REG_DWARFNUM_NAME("%fp", 11),
	REG_DWARFNUM_NAME("%ip", 12),
	REG_DWARFNUM_NAME("%sp", 13),
	REG_DWARFNUM_NAME("%lr", 14),
	REG_DWARFNUM_NAME("%pc", 15),
	REG_DWARFNUM_END,
पूर्ण;

/**
 * get_arch_regstr() - lookup रेजिस्टर name from it's DWARF रेजिस्टर number
 * @n:	the DWARF रेजिस्टर number
 *
 * get_arch_regstr() वापसs the name of the रेजिस्टर in काष्ठा
 * regdwarfnum_table from it's DWARF रेजिस्टर number. If the रेजिस्टर is not
 * found in the table, this वापसs शून्य;
 */
स्थिर अक्षर *get_arch_regstr(अचिन्हित पूर्णांक n)
अणु
	स्थिर काष्ठा pt_regs_dwarfnum *roff;
	क्रम (roff = regdwarfnum_table; roff->name != शून्य; roff++)
		अगर (roff->dwarfnum == n)
			वापस roff->name;
	वापस शून्य;
पूर्ण
