<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_X86_INAT_H
#घोषणा _ASM_X86_INAT_H
/*
 * x86 inकाष्ठाion attributes
 *
 * Written by Masami Hiramatsu <mhiramat@redhat.com>
 */
#समावेश <यंत्र/inat_types.h> /* __ignore_sync_check__ */

/*
 * Internal bits. Don't use biपंचांगasks directly, because these bits are
 * unstable. You should use checking functions.
 */

#घोषणा INAT_OPCODE_TABLE_SIZE 256
#घोषणा INAT_GROUP_TABLE_SIZE 8

/* Legacy last prefixes */
#घोषणा INAT_PFX_OPNDSZ	1	/* 0x66 */ /* LPFX1 */
#घोषणा INAT_PFX_REPE	2	/* 0xF3 */ /* LPFX2 */
#घोषणा INAT_PFX_REPNE	3	/* 0xF2 */ /* LPFX3 */
/* Other Legacy prefixes */
#घोषणा INAT_PFX_LOCK	4	/* 0xF0 */
#घोषणा INAT_PFX_CS	5	/* 0x2E */
#घोषणा INAT_PFX_DS	6	/* 0x3E */
#घोषणा INAT_PFX_ES	7	/* 0x26 */
#घोषणा INAT_PFX_FS	8	/* 0x64 */
#घोषणा INAT_PFX_GS	9	/* 0x65 */
#घोषणा INAT_PFX_SS	10	/* 0x36 */
#घोषणा INAT_PFX_ADDRSZ	11	/* 0x67 */
/* x86-64 REX prefix */
#घोषणा INAT_PFX_REX	12	/* 0x4X */
/* AVX VEX prefixes */
#घोषणा INAT_PFX_VEX2	13	/* 2-bytes VEX prefix */
#घोषणा INAT_PFX_VEX3	14	/* 3-bytes VEX prefix */
#घोषणा INAT_PFX_EVEX	15	/* EVEX prefix */

#घोषणा INAT_LSTPFX_MAX	3
#घोषणा INAT_LGCPFX_MAX	11

/* Immediate size */
#घोषणा INAT_IMM_BYTE		1
#घोषणा INAT_IMM_WORD		2
#घोषणा INAT_IMM_DWORD		3
#घोषणा INAT_IMM_QWORD		4
#घोषणा INAT_IMM_PTR		5
#घोषणा INAT_IMM_VWORD32	6
#घोषणा INAT_IMM_VWORD		7

/* Legacy prefix */
#घोषणा INAT_PFX_OFFS	0
#घोषणा INAT_PFX_BITS	4
#घोषणा INAT_PFX_MAX    ((1 << INAT_PFX_BITS) - 1)
#घोषणा INAT_PFX_MASK	(INAT_PFX_MAX << INAT_PFX_OFFS)
/* Escape opcodes */
#घोषणा INAT_ESC_OFFS	(INAT_PFX_OFFS + INAT_PFX_BITS)
#घोषणा INAT_ESC_BITS	2
#घोषणा INAT_ESC_MAX	((1 << INAT_ESC_BITS) - 1)
#घोषणा INAT_ESC_MASK	(INAT_ESC_MAX << INAT_ESC_OFFS)
/* Group opcodes (1-16) */
#घोषणा INAT_GRP_OFFS	(INAT_ESC_OFFS + INAT_ESC_BITS)
#घोषणा INAT_GRP_BITS	5
#घोषणा INAT_GRP_MAX	((1 << INAT_GRP_BITS) - 1)
#घोषणा INAT_GRP_MASK	(INAT_GRP_MAX << INAT_GRP_OFFS)
/* Immediates */
#घोषणा INAT_IMM_OFFS	(INAT_GRP_OFFS + INAT_GRP_BITS)
#घोषणा INAT_IMM_BITS	3
#घोषणा INAT_IMM_MASK	(((1 << INAT_IMM_BITS) - 1) << INAT_IMM_OFFS)
/* Flags */
#घोषणा INAT_FLAG_OFFS	(INAT_IMM_OFFS + INAT_IMM_BITS)
#घोषणा INAT_MODRM	(1 << (INAT_FLAG_OFFS))
#घोषणा INAT_FORCE64	(1 << (INAT_FLAG_OFFS + 1))
#घोषणा INAT_SCNDIMM	(1 << (INAT_FLAG_OFFS + 2))
#घोषणा INAT_MOFFSET	(1 << (INAT_FLAG_OFFS + 3))
#घोषणा INAT_VARIANT	(1 << (INAT_FLAG_OFFS + 4))
#घोषणा INAT_VEXOK	(1 << (INAT_FLAG_OFFS + 5))
#घोषणा INAT_VEXONLY	(1 << (INAT_FLAG_OFFS + 6))
#घोषणा INAT_EVEXONLY	(1 << (INAT_FLAG_OFFS + 7))
/* Attribute making macros क्रम attribute tables */
#घोषणा INAT_MAKE_PREFIX(pfx)	(pfx << INAT_PFX_OFFS)
#घोषणा INAT_MAKE_ESCAPE(esc)	(esc << INAT_ESC_OFFS)
#घोषणा INAT_MAKE_GROUP(grp)	((grp << INAT_GRP_OFFS) | INAT_MODRM)
#घोषणा INAT_MAKE_IMM(imm)	(imm << INAT_IMM_OFFS)

/* Identअगरiers क्रम segment रेजिस्टरs */
#घोषणा INAT_SEG_REG_IGNORE	0
#घोषणा INAT_SEG_REG_DEFAULT	1
#घोषणा INAT_SEG_REG_CS		2
#घोषणा INAT_SEG_REG_SS		3
#घोषणा INAT_SEG_REG_DS		4
#घोषणा INAT_SEG_REG_ES		5
#घोषणा INAT_SEG_REG_FS		6
#घोषणा INAT_SEG_REG_GS		7

/* Attribute search APIs */
बाह्य insn_attr_t inat_get_opcode_attribute(insn_byte_t opcode);
बाह्य पूर्णांक inat_get_last_prefix_id(insn_byte_t last_pfx);
बाह्य insn_attr_t inat_get_escape_attribute(insn_byte_t opcode,
					     पूर्णांक lpfx_id,
					     insn_attr_t esc_attr);
बाह्य insn_attr_t inat_get_group_attribute(insn_byte_t modrm,
					    पूर्णांक lpfx_id,
					    insn_attr_t esc_attr);
बाह्य insn_attr_t inat_get_avx_attribute(insn_byte_t opcode,
					  insn_byte_t vex_m,
					  insn_byte_t vex_pp);

/* Attribute checking functions */
अटल अंतरभूत पूर्णांक inat_is_legacy_prefix(insn_attr_t attr)
अणु
	attr &= INAT_PFX_MASK;
	वापस attr && attr <= INAT_LGCPFX_MAX;
पूर्ण

अटल अंतरभूत पूर्णांक inat_is_address_size_prefix(insn_attr_t attr)
अणु
	वापस (attr & INAT_PFX_MASK) == INAT_PFX_ADDRSZ;
पूर्ण

अटल अंतरभूत पूर्णांक inat_is_opeअक्रम_size_prefix(insn_attr_t attr)
अणु
	वापस (attr & INAT_PFX_MASK) == INAT_PFX_OPNDSZ;
पूर्ण

अटल अंतरभूत पूर्णांक inat_is_rex_prefix(insn_attr_t attr)
अणु
	वापस (attr & INAT_PFX_MASK) == INAT_PFX_REX;
पूर्ण

अटल अंतरभूत पूर्णांक inat_last_prefix_id(insn_attr_t attr)
अणु
	अगर ((attr & INAT_PFX_MASK) > INAT_LSTPFX_MAX)
		वापस 0;
	अन्यथा
		वापस attr & INAT_PFX_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक inat_is_vex_prefix(insn_attr_t attr)
अणु
	attr &= INAT_PFX_MASK;
	वापस attr == INAT_PFX_VEX2 || attr == INAT_PFX_VEX3 ||
	       attr == INAT_PFX_EVEX;
पूर्ण

अटल अंतरभूत पूर्णांक inat_is_evex_prefix(insn_attr_t attr)
अणु
	वापस (attr & INAT_PFX_MASK) == INAT_PFX_EVEX;
पूर्ण

अटल अंतरभूत पूर्णांक inat_is_vex3_prefix(insn_attr_t attr)
अणु
	वापस (attr & INAT_PFX_MASK) == INAT_PFX_VEX3;
पूर्ण

अटल अंतरभूत पूर्णांक inat_is_escape(insn_attr_t attr)
अणु
	वापस attr & INAT_ESC_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक inat_escape_id(insn_attr_t attr)
अणु
	वापस (attr & INAT_ESC_MASK) >> INAT_ESC_OFFS;
पूर्ण

अटल अंतरभूत पूर्णांक inat_is_group(insn_attr_t attr)
अणु
	वापस attr & INAT_GRP_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक inat_group_id(insn_attr_t attr)
अणु
	वापस (attr & INAT_GRP_MASK) >> INAT_GRP_OFFS;
पूर्ण

अटल अंतरभूत पूर्णांक inat_group_common_attribute(insn_attr_t attr)
अणु
	वापस attr & ~INAT_GRP_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक inat_has_immediate(insn_attr_t attr)
अणु
	वापस attr & INAT_IMM_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक inat_immediate_size(insn_attr_t attr)
अणु
	वापस (attr & INAT_IMM_MASK) >> INAT_IMM_OFFS;
पूर्ण

अटल अंतरभूत पूर्णांक inat_has_modrm(insn_attr_t attr)
अणु
	वापस attr & INAT_MODRM;
पूर्ण

अटल अंतरभूत पूर्णांक inat_is_क्रमce64(insn_attr_t attr)
अणु
	वापस attr & INAT_FORCE64;
पूर्ण

अटल अंतरभूत पूर्णांक inat_has_second_immediate(insn_attr_t attr)
अणु
	वापस attr & INAT_SCNDIMM;
पूर्ण

अटल अंतरभूत पूर्णांक inat_has_moffset(insn_attr_t attr)
अणु
	वापस attr & INAT_MOFFSET;
पूर्ण

अटल अंतरभूत पूर्णांक inat_has_variant(insn_attr_t attr)
अणु
	वापस attr & INAT_VARIANT;
पूर्ण

अटल अंतरभूत पूर्णांक inat_accept_vex(insn_attr_t attr)
अणु
	वापस attr & INAT_VEXOK;
पूर्ण

अटल अंतरभूत पूर्णांक inat_must_vex(insn_attr_t attr)
अणु
	वापस attr & (INAT_VEXONLY | INAT_EVEXONLY);
पूर्ण

अटल अंतरभूत पूर्णांक inat_must_evex(insn_attr_t attr)
अणु
	वापस attr & INAT_EVEXONLY;
पूर्ण
#पूर्ण_अगर
