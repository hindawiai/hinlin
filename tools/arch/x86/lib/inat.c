<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * x86 inकाष्ठाion attribute tables
 *
 * Written by Masami Hiramatsu <mhiramat@redhat.com>
 */
#समावेश "../include/asm/insn.h" /* __ignore_sync_check__ */

/* Attribute tables are generated from opcode map */
#समावेश "inat-tables.c"

/* Attribute search APIs */
insn_attr_t inat_get_opcode_attribute(insn_byte_t opcode)
अणु
	वापस inat_primary_table[opcode];
पूर्ण

पूर्णांक inat_get_last_prefix_id(insn_byte_t last_pfx)
अणु
	insn_attr_t lpfx_attr;

	lpfx_attr = inat_get_opcode_attribute(last_pfx);
	वापस inat_last_prefix_id(lpfx_attr);
पूर्ण

insn_attr_t inat_get_escape_attribute(insn_byte_t opcode, पूर्णांक lpfx_id,
				      insn_attr_t esc_attr)
अणु
	स्थिर insn_attr_t *table;
	पूर्णांक n;

	n = inat_escape_id(esc_attr);

	table = inat_escape_tables[n][0];
	अगर (!table)
		वापस 0;
	अगर (inat_has_variant(table[opcode]) && lpfx_id) अणु
		table = inat_escape_tables[n][lpfx_id];
		अगर (!table)
			वापस 0;
	पूर्ण
	वापस table[opcode];
पूर्ण

insn_attr_t inat_get_group_attribute(insn_byte_t modrm, पूर्णांक lpfx_id,
				     insn_attr_t grp_attr)
अणु
	स्थिर insn_attr_t *table;
	पूर्णांक n;

	n = inat_group_id(grp_attr);

	table = inat_group_tables[n][0];
	अगर (!table)
		वापस inat_group_common_attribute(grp_attr);
	अगर (inat_has_variant(table[X86_MODRM_REG(modrm)]) && lpfx_id) अणु
		table = inat_group_tables[n][lpfx_id];
		अगर (!table)
			वापस inat_group_common_attribute(grp_attr);
	पूर्ण
	वापस table[X86_MODRM_REG(modrm)] |
	       inat_group_common_attribute(grp_attr);
पूर्ण

insn_attr_t inat_get_avx_attribute(insn_byte_t opcode, insn_byte_t vex_m,
				   insn_byte_t vex_p)
अणु
	स्थिर insn_attr_t *table;
	अगर (vex_m > X86_VEX_M_MAX || vex_p > INAT_LSTPFX_MAX)
		वापस 0;
	/* At first, this checks the master table */
	table = inat_avx_tables[vex_m][0];
	अगर (!table)
		वापस 0;
	अगर (!inat_is_group(table[opcode]) && vex_p) अणु
		/* If this is not a group, get attribute directly */
		table = inat_avx_tables[vex_m][vex_p];
		अगर (!table)
			वापस 0;
	पूर्ण
	वापस table[opcode];
पूर्ण

