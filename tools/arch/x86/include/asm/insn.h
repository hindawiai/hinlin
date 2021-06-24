<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_X86_INSN_H
#घोषणा _ASM_X86_INSN_H
/*
 * x86 inकाष्ठाion analysis
 *
 * Copyright (C) IBM Corporation, 2009
 */

#समावेश <यंत्र/byteorder.h>
/* insn_attr_t is defined in inat.h */
#समावेश "inat.h" /* __ignore_sync_check__ */

#अगर defined(__BYTE_ORDER) ? __BYTE_ORDER == __LITTLE_ENDIAN : defined(__LITTLE_ENDIAN)

काष्ठा insn_field अणु
	जोड़ अणु
		insn_value_t value;
		insn_byte_t bytes[4];
	पूर्ण;
	/* !0 अगर we've run insn_get_xxx() क्रम this field */
	अचिन्हित अक्षर got;
	अचिन्हित अक्षर nbytes;
पूर्ण;

अटल अंतरभूत व्योम insn_field_set(काष्ठा insn_field *p, insn_value_t v,
				  अचिन्हित अक्षर n)
अणु
	p->value = v;
	p->nbytes = n;
पूर्ण

अटल अंतरभूत व्योम insn_set_byte(काष्ठा insn_field *p, अचिन्हित अक्षर n,
				 insn_byte_t v)
अणु
	p->bytes[n] = v;
पूर्ण

#अन्यथा

काष्ठा insn_field अणु
	insn_value_t value;
	जोड़ अणु
		insn_value_t little;
		insn_byte_t bytes[4];
	पूर्ण;
	/* !0 अगर we've run insn_get_xxx() क्रम this field */
	अचिन्हित अक्षर got;
	अचिन्हित अक्षर nbytes;
पूर्ण;

अटल अंतरभूत व्योम insn_field_set(काष्ठा insn_field *p, insn_value_t v,
				  अचिन्हित अक्षर n)
अणु
	p->value = v;
	p->little = __cpu_to_le32(v);
	p->nbytes = n;
पूर्ण

अटल अंतरभूत व्योम insn_set_byte(काष्ठा insn_field *p, अचिन्हित अक्षर n,
				 insn_byte_t v)
अणु
	p->bytes[n] = v;
	p->value = __le32_to_cpu(p->little);
पूर्ण
#पूर्ण_अगर

काष्ठा insn अणु
	काष्ठा insn_field prefixes;	/*
					 * Prefixes
					 * prefixes.bytes[3]: last prefix
					 */
	काष्ठा insn_field rex_prefix;	/* REX prefix */
	काष्ठा insn_field vex_prefix;	/* VEX prefix */
	काष्ठा insn_field opcode;	/*
					 * opcode.bytes[0]: opcode1
					 * opcode.bytes[1]: opcode2
					 * opcode.bytes[2]: opcode3
					 */
	काष्ठा insn_field modrm;
	काष्ठा insn_field sib;
	काष्ठा insn_field displacement;
	जोड़ अणु
		काष्ठा insn_field immediate;
		काष्ठा insn_field moffset1;	/* क्रम 64bit MOV */
		काष्ठा insn_field immediate1;	/* क्रम 64bit imm or off16/32 */
	पूर्ण;
	जोड़ अणु
		काष्ठा insn_field moffset2;	/* क्रम 64bit MOV */
		काष्ठा insn_field immediate2;	/* क्रम 64bit imm or seg16 */
	पूर्ण;

	पूर्णांक	emulate_prefix_size;
	insn_attr_t attr;
	अचिन्हित अक्षर opnd_bytes;
	अचिन्हित अक्षर addr_bytes;
	अचिन्हित अक्षर length;
	अचिन्हित अक्षर x86_64;

	स्थिर insn_byte_t *kaddr;	/* kernel address of insn to analyze */
	स्थिर insn_byte_t *end_kaddr;	/* kernel address of last insn in buffer */
	स्थिर insn_byte_t *next_byte;
पूर्ण;

#घोषणा MAX_INSN_SIZE	15

#घोषणा X86_MODRM_MOD(modrm) (((modrm) & 0xc0) >> 6)
#घोषणा X86_MODRM_REG(modrm) (((modrm) & 0x38) >> 3)
#घोषणा X86_MODRM_RM(modrm) ((modrm) & 0x07)

#घोषणा X86_SIB_SCALE(sib) (((sib) & 0xc0) >> 6)
#घोषणा X86_SIB_INDEX(sib) (((sib) & 0x38) >> 3)
#घोषणा X86_SIB_BASE(sib) ((sib) & 0x07)

#घोषणा X86_REX_W(rex) ((rex) & 8)
#घोषणा X86_REX_R(rex) ((rex) & 4)
#घोषणा X86_REX_X(rex) ((rex) & 2)
#घोषणा X86_REX_B(rex) ((rex) & 1)

/* VEX bit flags  */
#घोषणा X86_VEX_W(vex)	((vex) & 0x80)	/* VEX3 Byte2 */
#घोषणा X86_VEX_R(vex)	((vex) & 0x80)	/* VEX2/3 Byte1 */
#घोषणा X86_VEX_X(vex)	((vex) & 0x40)	/* VEX3 Byte1 */
#घोषणा X86_VEX_B(vex)	((vex) & 0x20)	/* VEX3 Byte1 */
#घोषणा X86_VEX_L(vex)	((vex) & 0x04)	/* VEX3 Byte2, VEX2 Byte1 */
/* VEX bit fields */
#घोषणा X86_EVEX_M(vex)	((vex) & 0x03)		/* EVEX Byte1 */
#घोषणा X86_VEX3_M(vex)	((vex) & 0x1f)		/* VEX3 Byte1 */
#घोषणा X86_VEX2_M	1			/* VEX2.M always 1 */
#घोषणा X86_VEX_V(vex)	(((vex) & 0x78) >> 3)	/* VEX3 Byte2, VEX2 Byte1 */
#घोषणा X86_VEX_P(vex)	((vex) & 0x03)		/* VEX3 Byte2, VEX2 Byte1 */
#घोषणा X86_VEX_M_MAX	0x1f			/* VEX3.M Maximum value */

बाह्य व्योम insn_init(काष्ठा insn *insn, स्थिर व्योम *kaddr, पूर्णांक buf_len, पूर्णांक x86_64);
बाह्य पूर्णांक insn_get_prefixes(काष्ठा insn *insn);
बाह्य पूर्णांक insn_get_opcode(काष्ठा insn *insn);
बाह्य पूर्णांक insn_get_modrm(काष्ठा insn *insn);
बाह्य पूर्णांक insn_get_sib(काष्ठा insn *insn);
बाह्य पूर्णांक insn_get_displacement(काष्ठा insn *insn);
बाह्य पूर्णांक insn_get_immediate(काष्ठा insn *insn);
बाह्य पूर्णांक insn_get_length(काष्ठा insn *insn);

क्रमागत insn_mode अणु
	INSN_MODE_32,
	INSN_MODE_64,
	/* Mode is determined by the current kernel build. */
	INSN_MODE_KERN,
	INSN_NUM_MODES,
पूर्ण;

बाह्य पूर्णांक insn_decode(काष्ठा insn *insn, स्थिर व्योम *kaddr, पूर्णांक buf_len, क्रमागत insn_mode m);

#घोषणा insn_decode_kernel(_insn, _ptr) insn_decode((_insn), (_ptr), MAX_INSN_SIZE, INSN_MODE_KERN)

/* Attribute will be determined after getting ModRM (क्रम opcode groups) */
अटल अंतरभूत व्योम insn_get_attribute(काष्ठा insn *insn)
अणु
	insn_get_modrm(insn);
पूर्ण

/* Inकाष्ठाion uses RIP-relative addressing */
बाह्य पूर्णांक insn_rip_relative(काष्ठा insn *insn);

अटल अंतरभूत पूर्णांक insn_is_avx(काष्ठा insn *insn)
अणु
	अगर (!insn->prefixes.got)
		insn_get_prefixes(insn);
	वापस (insn->vex_prefix.value != 0);
पूर्ण

अटल अंतरभूत पूर्णांक insn_is_evex(काष्ठा insn *insn)
अणु
	अगर (!insn->prefixes.got)
		insn_get_prefixes(insn);
	वापस (insn->vex_prefix.nbytes == 4);
पूर्ण

अटल अंतरभूत पूर्णांक insn_has_emulate_prefix(काष्ठा insn *insn)
अणु
	वापस !!insn->emulate_prefix_size;
पूर्ण

अटल अंतरभूत insn_byte_t insn_vex_m_bits(काष्ठा insn *insn)
अणु
	अगर (insn->vex_prefix.nbytes == 2)	/* 2 bytes VEX */
		वापस X86_VEX2_M;
	अन्यथा अगर (insn->vex_prefix.nbytes == 3)	/* 3 bytes VEX */
		वापस X86_VEX3_M(insn->vex_prefix.bytes[1]);
	अन्यथा					/* EVEX */
		वापस X86_EVEX_M(insn->vex_prefix.bytes[1]);
पूर्ण

अटल अंतरभूत insn_byte_t insn_vex_p_bits(काष्ठा insn *insn)
अणु
	अगर (insn->vex_prefix.nbytes == 2)	/* 2 bytes VEX */
		वापस X86_VEX_P(insn->vex_prefix.bytes[1]);
	अन्यथा
		वापस X86_VEX_P(insn->vex_prefix.bytes[2]);
पूर्ण

/* Get the last prefix id from last prefix or VEX prefix */
अटल अंतरभूत पूर्णांक insn_last_prefix_id(काष्ठा insn *insn)
अणु
	अगर (insn_is_avx(insn))
		वापस insn_vex_p_bits(insn);	/* VEX_p is a SIMD prefix id */

	अगर (insn->prefixes.bytes[3])
		वापस inat_get_last_prefix_id(insn->prefixes.bytes[3]);

	वापस 0;
पूर्ण

/* Offset of each field from kaddr */
अटल अंतरभूत पूर्णांक insn_offset_rex_prefix(काष्ठा insn *insn)
अणु
	वापस insn->prefixes.nbytes;
पूर्ण
अटल अंतरभूत पूर्णांक insn_offset_vex_prefix(काष्ठा insn *insn)
अणु
	वापस insn_offset_rex_prefix(insn) + insn->rex_prefix.nbytes;
पूर्ण
अटल अंतरभूत पूर्णांक insn_offset_opcode(काष्ठा insn *insn)
अणु
	वापस insn_offset_vex_prefix(insn) + insn->vex_prefix.nbytes;
पूर्ण
अटल अंतरभूत पूर्णांक insn_offset_modrm(काष्ठा insn *insn)
अणु
	वापस insn_offset_opcode(insn) + insn->opcode.nbytes;
पूर्ण
अटल अंतरभूत पूर्णांक insn_offset_sib(काष्ठा insn *insn)
अणु
	वापस insn_offset_modrm(insn) + insn->modrm.nbytes;
पूर्ण
अटल अंतरभूत पूर्णांक insn_offset_displacement(काष्ठा insn *insn)
अणु
	वापस insn_offset_sib(insn) + insn->sib.nbytes;
पूर्ण
अटल अंतरभूत पूर्णांक insn_offset_immediate(काष्ठा insn *insn)
अणु
	वापस insn_offset_displacement(insn) + insn->displacement.nbytes;
पूर्ण

/**
 * क्रम_each_insn_prefix() -- Iterate prefixes in the inकाष्ठाion
 * @insn: Poपूर्णांकer to काष्ठा insn.
 * @idx:  Index storage.
 * @prefix: Prefix byte.
 *
 * Iterate prefix bytes of given @insn. Each prefix byte is stored in @prefix
 * and the index is stored in @idx (note that this @idx is just क्रम a cursor,
 * करो not change it.)
 * Since prefixes.nbytes can be bigger than 4 अगर some prefixes
 * are repeated, it cannot be used क्रम looping over the prefixes.
 */
#घोषणा क्रम_each_insn_prefix(insn, idx, prefix)	\
	क्रम (idx = 0; idx < ARRAY_SIZE(insn->prefixes.bytes) && (prefix = insn->prefixes.bytes[idx]) != 0; idx++)

#घोषणा POP_SS_OPCODE 0x1f
#घोषणा MOV_SREG_OPCODE 0x8e

/*
 * Intel SDM Vol.3A 6.8.3 states;
 * "Any single-step trap that would be delivered following the MOV to SS
 * inकाष्ठाion or POP to SS inकाष्ठाion (because EFLAGS.TF is 1) is
 * suppressed."
 * This function वापसs true अगर @insn is MOV SS or POP SS. On these
 * inकाष्ठाions, single stepping is suppressed.
 */
अटल अंतरभूत पूर्णांक insn_masking_exception(काष्ठा insn *insn)
अणु
	वापस insn->opcode.bytes[0] == POP_SS_OPCODE ||
		(insn->opcode.bytes[0] == MOV_SREG_OPCODE &&
		 X86_MODRM_REG(insn->modrm.bytes[0]) == 2);
पूर्ण

#पूर्ण_अगर /* _ASM_X86_INSN_H */
