<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_घोषित DEFINE_DWARF_REGSTR_TABLE
/* This is included in perf/util/dwarf-regs.c */

/*
 * Reference:
 * http://refspecs.linuxfoundation.org/ELF/ppc64/PPC-elf64abi-1.9.hपंचांगl
 * http://refspecs.linux-foundation.org/elf/elfspec_ppc.pdf
 */
#घोषणा REG_DWARFNUM_NAME(reg, idx)	[idx] = "%" #reg

अटल स्थिर अक्षर * स्थिर घातerpc_regstr_tbl[] = अणु
	"%gpr0", "%gpr1", "%gpr2", "%gpr3", "%gpr4",
	"%gpr5", "%gpr6", "%gpr7", "%gpr8", "%gpr9",
	"%gpr10", "%gpr11", "%gpr12", "%gpr13", "%gpr14",
	"%gpr15", "%gpr16", "%gpr17", "%gpr18", "%gpr19",
	"%gpr20", "%gpr21", "%gpr22", "%gpr23", "%gpr24",
	"%gpr25", "%gpr26", "%gpr27", "%gpr28", "%gpr29",
	"%gpr30", "%gpr31",
	REG_DWARFNUM_NAME(msr,   66),
	REG_DWARFNUM_NAME(ctr,   109),
	REG_DWARFNUM_NAME(link,  108),
	REG_DWARFNUM_NAME(xer,   101),
	REG_DWARFNUM_NAME(dar,   119),
	REG_DWARFNUM_NAME(dsisr, 118),
पूर्ण;

#पूर्ण_अगर
