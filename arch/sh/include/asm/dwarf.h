<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright (C) 2009 Matt Fleming <matt@console-pimps.org>
 */
#अगर_अघोषित __ASM_SH_DWARF_H
#घोषणा __ASM_SH_DWARF_H

#अगर_घोषित CONFIG_DWARF_UNWINDER

/*
 * DWARF expression operations
 */
#घोषणा DW_OP_addr	0x03
#घोषणा DW_OP_deref	0x06
#घोषणा DW_OP_स्थिर1u	0x08
#घोषणा DW_OP_स्थिर1s	0x09
#घोषणा DW_OP_स्थिर2u	0x0a
#घोषणा DW_OP_स्थिर2s	0x0b
#घोषणा DW_OP_स्थिर4u	0x0c
#घोषणा DW_OP_स्थिर4s	0x0d
#घोषणा DW_OP_स्थिर8u	0x0e
#घोषणा DW_OP_स्थिर8s	0x0f
#घोषणा DW_OP_स्थिरu	0x10
#घोषणा DW_OP_स्थिरs	0x11
#घोषणा DW_OP_dup	0x12
#घोषणा DW_OP_drop	0x13
#घोषणा DW_OP_over	0x14
#घोषणा DW_OP_pick	0x15
#घोषणा DW_OP_swap	0x16
#घोषणा DW_OP_rot	0x17
#घोषणा DW_OP_xderef	0x18
#घोषणा DW_OP_असल	0x19
#घोषणा DW_OP_and	0x1a
#घोषणा DW_OP_भाग	0x1b
#घोषणा DW_OP_minus	0x1c
#घोषणा DW_OP_mod	0x1d
#घोषणा DW_OP_mul	0x1e
#घोषणा DW_OP_neg	0x1f
#घोषणा DW_OP_not	0x20
#घोषणा DW_OP_or	0x21
#घोषणा DW_OP_plus	0x22
#घोषणा DW_OP_plus_uस्थिर	0x23
#घोषणा DW_OP_shl	0x24
#घोषणा DW_OP_shr	0x25
#घोषणा DW_OP_shra	0x26
#घोषणा DW_OP_xor	0x27
#घोषणा DW_OP_skip	0x2f
#घोषणा DW_OP_bra	0x28
#घोषणा DW_OP_eq	0x29
#घोषणा DW_OP_ge	0x2a
#घोषणा DW_OP_gt	0x2b
#घोषणा DW_OP_le	0x2c
#घोषणा DW_OP_lt	0x2d
#घोषणा DW_OP_ne	0x2e
#घोषणा DW_OP_lit0	0x30
#घोषणा DW_OP_lit1	0x31
#घोषणा DW_OP_lit2	0x32
#घोषणा DW_OP_lit3	0x33
#घोषणा DW_OP_lit4	0x34
#घोषणा DW_OP_lit5	0x35
#घोषणा DW_OP_lit6	0x36
#घोषणा DW_OP_lit7	0x37
#घोषणा DW_OP_lit8	0x38
#घोषणा DW_OP_lit9	0x39
#घोषणा DW_OP_lit10	0x3a
#घोषणा DW_OP_lit11	0x3b
#घोषणा DW_OP_lit12	0x3c
#घोषणा DW_OP_lit13	0x3d
#घोषणा DW_OP_lit14	0x3e
#घोषणा DW_OP_lit15	0x3f
#घोषणा DW_OP_lit16	0x40
#घोषणा DW_OP_lit17	0x41
#घोषणा DW_OP_lit18	0x42
#घोषणा DW_OP_lit19	0x43
#घोषणा DW_OP_lit20	0x44
#घोषणा DW_OP_lit21	0x45
#घोषणा DW_OP_lit22	0x46
#घोषणा DW_OP_lit23	0x47
#घोषणा DW_OP_lit24	0x48
#घोषणा DW_OP_lit25	0x49
#घोषणा DW_OP_lit26	0x4a
#घोषणा DW_OP_lit27	0x4b
#घोषणा DW_OP_lit28	0x4c
#घोषणा DW_OP_lit29	0x4d
#घोषणा DW_OP_lit30	0x4e
#घोषणा DW_OP_lit31	0x4f
#घोषणा DW_OP_reg0	0x50
#घोषणा DW_OP_reg1	0x51
#घोषणा DW_OP_reg2	0x52
#घोषणा DW_OP_reg3	0x53
#घोषणा DW_OP_reg4	0x54
#घोषणा DW_OP_reg5	0x55
#घोषणा DW_OP_reg6	0x56
#घोषणा DW_OP_reg7	0x57
#घोषणा DW_OP_reg8	0x58
#घोषणा DW_OP_reg9	0x59
#घोषणा DW_OP_reg10	0x5a
#घोषणा DW_OP_reg11	0x5b
#घोषणा DW_OP_reg12	0x5c
#घोषणा DW_OP_reg13	0x5d
#घोषणा DW_OP_reg14	0x5e
#घोषणा DW_OP_reg15	0x5f
#घोषणा DW_OP_reg16	0x60
#घोषणा DW_OP_reg17	0x61
#घोषणा DW_OP_reg18	0x62
#घोषणा DW_OP_reg19	0x63
#घोषणा DW_OP_reg20	0x64
#घोषणा DW_OP_reg21	0x65
#घोषणा DW_OP_reg22	0x66
#घोषणा DW_OP_reg23	0x67
#घोषणा DW_OP_reg24	0x68
#घोषणा DW_OP_reg25	0x69
#घोषणा DW_OP_reg26	0x6a
#घोषणा DW_OP_reg27	0x6b
#घोषणा DW_OP_reg28	0x6c
#घोषणा DW_OP_reg29	0x6d
#घोषणा DW_OP_reg30	0x6e
#घोषणा DW_OP_reg31	0x6f
#घोषणा DW_OP_breg0	0x70
#घोषणा DW_OP_breg1	0x71
#घोषणा DW_OP_breg2	0x72
#घोषणा DW_OP_breg3	0x73
#घोषणा DW_OP_breg4	0x74
#घोषणा DW_OP_breg5	0x75
#घोषणा DW_OP_breg6	0x76
#घोषणा DW_OP_breg7	0x77
#घोषणा DW_OP_breg8	0x78
#घोषणा DW_OP_breg9	0x79
#घोषणा DW_OP_breg10	0x7a
#घोषणा DW_OP_breg11	0x7b
#घोषणा DW_OP_breg12	0x7c
#घोषणा DW_OP_breg13	0x7d
#घोषणा DW_OP_breg14	0x7e
#घोषणा DW_OP_breg15	0x7f
#घोषणा DW_OP_breg16	0x80
#घोषणा DW_OP_breg17	0x81
#घोषणा DW_OP_breg18	0x82
#घोषणा DW_OP_breg19	0x83
#घोषणा DW_OP_breg20	0x84
#घोषणा DW_OP_breg21	0x85
#घोषणा DW_OP_breg22	0x86
#घोषणा DW_OP_breg23	0x87
#घोषणा DW_OP_breg24	0x88
#घोषणा DW_OP_breg25	0x89
#घोषणा DW_OP_breg26	0x8a
#घोषणा DW_OP_breg27	0x8b
#घोषणा DW_OP_breg28	0x8c
#घोषणा DW_OP_breg29	0x8d
#घोषणा DW_OP_breg30	0x8e
#घोषणा DW_OP_breg31	0x8f
#घोषणा DW_OP_regx	0x90
#घोषणा DW_OP_fbreg	0x91
#घोषणा DW_OP_bregx	0x92
#घोषणा DW_OP_piece	0x93
#घोषणा DW_OP_deref_size	0x94
#घोषणा DW_OP_xderef_size	0x95
#घोषणा DW_OP_nop	0x96
#घोषणा DW_OP_push_object_address	0x97
#घोषणा DW_OP_call2	0x98
#घोषणा DW_OP_call4	0x99
#घोषणा DW_OP_call_ref	0x9a
#घोषणा DW_OP_क्रमm_tls_address	0x9b
#घोषणा DW_OP_call_frame_cfa	0x9c
#घोषणा DW_OP_bit_piece	0x9d
#घोषणा DW_OP_lo_user	0xe0
#घोषणा DW_OP_hi_user	0xff

/*
 * Addresses used in FDE entries in the .eh_frame section may be encoded
 * using one of the following encodings.
 */
#घोषणा DW_EH_PE_असलptr	0x00
#घोषणा DW_EH_PE_omit	0xff
#घोषणा DW_EH_PE_uleb128	0x01
#घोषणा DW_EH_PE_udata2	0x02
#घोषणा DW_EH_PE_udata4	0x03
#घोषणा DW_EH_PE_udata8	0x04
#घोषणा DW_EH_PE_sleb128	0x09
#घोषणा DW_EH_PE_sdata2	0x0a
#घोषणा DW_EH_PE_sdata4	0x0b
#घोषणा DW_EH_PE_sdata8	0x0c
#घोषणा DW_EH_PE_चिन्हित	0x09

#घोषणा DW_EH_PE_pcrel	0x10

/*
 * The architecture-specअगरic रेजिस्टर number that contains the वापस
 * address in the .debug_frame table.
 */
#घोषणा DWARF_ARCH_RA_REG	17

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/compiler.h>
#समावेश <linux/bug.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>

/*
 * Read either the frame poपूर्णांकer (r14) or the stack poपूर्णांकer (r15).
 * NOTE: this MUST be अंतरभूतd.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ dwarf_पढ़ो_arch_reg(अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित दीर्घ value = 0;

	चयन (reg) अणु
	हाल 14:
		__यंत्र__ __अस्थिर__("mov r14, %0\n" : "=r" (value));
		अवरोध;
	हाल 15:
		__यंत्र__ __अस्थिर__("mov r15, %0\n" : "=r" (value));
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस value;
पूर्ण

/**
 *	dwarf_cie - Common Inक्रमmation Entry
 */
काष्ठा dwarf_cie अणु
	अचिन्हित दीर्घ length;
	अचिन्हित दीर्घ cie_id;
	अचिन्हित अक्षर version;
	स्थिर अक्षर *augmentation;
	अचिन्हित पूर्णांक code_alignment_factor;
	पूर्णांक data_alignment_factor;

	/* Which column in the rule table represents वापस addr of func. */
	अचिन्हित पूर्णांक वापस_address_reg;

	अचिन्हित अक्षर *initial_inकाष्ठाions;
	अचिन्हित अक्षर *inकाष्ठाions_end;

	अचिन्हित अक्षर encoding;

	अचिन्हित दीर्घ cie_poपूर्णांकer;

	अचिन्हित दीर्घ flags;
#घोषणा DWARF_CIE_Z_AUGMENTATION	(1 << 0)

	/* linked-list entry अगर this CIE is from a module */
	काष्ठा list_head link;

	काष्ठा rb_node node;
पूर्ण;

/**
 *	dwarf_fde - Frame Description Entry
 */
काष्ठा dwarf_fde अणु
	अचिन्हित दीर्घ length;
	अचिन्हित दीर्घ cie_poपूर्णांकer;
	काष्ठा dwarf_cie *cie;
	अचिन्हित दीर्घ initial_location;
	अचिन्हित दीर्घ address_range;
	अचिन्हित अक्षर *inकाष्ठाions;
	अचिन्हित अक्षर *end;

	/* linked-list entry अगर this FDE is from a module */
	काष्ठा list_head link;

	काष्ठा rb_node node;
पूर्ण;

/**
 *	dwarf_frame - DWARF inक्रमmation क्रम a frame in the call stack
 */
काष्ठा dwarf_frame अणु
	काष्ठा dwarf_frame *prev, *next;

	अचिन्हित दीर्घ pc;

	काष्ठा list_head reg_list;

	अचिन्हित दीर्घ cfa;

	/* Valid when DW_FRAME_CFA_REG_OFFSET is set in flags */
	अचिन्हित पूर्णांक cfa_रेजिस्टर;
	अचिन्हित पूर्णांक cfa_offset;

	/* Valid when DW_FRAME_CFA_REG_EXP is set in flags */
	अचिन्हित अक्षर *cfa_expr;
	अचिन्हित पूर्णांक cfa_expr_len;

	अचिन्हित दीर्घ flags;
#घोषणा DWARF_FRAME_CFA_REG_OFFSET	(1 << 0)
#घोषणा DWARF_FRAME_CFA_REG_EXP		(1 << 1)

	अचिन्हित दीर्घ वापस_addr;
पूर्ण;

/**
 *	dwarf_reg - DWARF रेजिस्टर
 *	@flags: Describes how to calculate the value of this रेजिस्टर
 */
काष्ठा dwarf_reg अणु
	काष्ठा list_head link;

	अचिन्हित पूर्णांक number;

	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ flags;
#घोषणा DWARF_REG_OFFSET	(1 << 0)
#घोषणा DWARF_VAL_OFFSET	(1 << 1)
#घोषणा DWARF_UNDEFINED		(1 << 2)
पूर्ण;

/*
 * Call Frame inकाष्ठाion opcodes.
 */
#घोषणा DW_CFA_advance_loc	0x40
#घोषणा DW_CFA_offset		0x80
#घोषणा DW_CFA_restore		0xc0
#घोषणा DW_CFA_nop		0x00
#घोषणा DW_CFA_set_loc		0x01
#घोषणा DW_CFA_advance_loc1	0x02
#घोषणा DW_CFA_advance_loc2	0x03
#घोषणा DW_CFA_advance_loc4	0x04
#घोषणा DW_CFA_offset_extended	0x05
#घोषणा DW_CFA_restore_extended	0x06
#घोषणा DW_CFA_undefined	0x07
#घोषणा DW_CFA_same_value	0x08
#घोषणा DW_CFA_रेजिस्टर		0x09
#घोषणा DW_CFA_remember_state	0x0a
#घोषणा DW_CFA_restore_state	0x0b
#घोषणा DW_CFA_def_cfa		0x0c
#घोषणा DW_CFA_def_cfa_रेजिस्टर	0x0d
#घोषणा DW_CFA_def_cfa_offset	0x0e
#घोषणा DW_CFA_def_cfa_expression	0x0f
#घोषणा DW_CFA_expression	0x10
#घोषणा DW_CFA_offset_extended_sf	0x11
#घोषणा DW_CFA_def_cfa_sf	0x12
#घोषणा DW_CFA_def_cfa_offset_sf	0x13
#घोषणा DW_CFA_val_offset	0x14
#घोषणा DW_CFA_val_offset_sf	0x15
#घोषणा DW_CFA_val_expression	0x16
#घोषणा DW_CFA_lo_user		0x1c
#घोषणा DW_CFA_hi_user		0x3f

/* GNU extension opcodes  */
#घोषणा DW_CFA_GNU_args_size	0x2e
#घोषणा DW_CFA_GNU_negative_offset_extended 0x2f

/*
 * Some call frame inकाष्ठाions encode their opeअक्रमs in the opcode. We
 * need some helper functions to extract both the opcode and opeअक्रमs
 * from an inकाष्ठाion.
 */
अटल अंतरभूत अचिन्हित पूर्णांक DW_CFA_opcode(अचिन्हित दीर्घ insn)
अणु
	वापस (insn & 0xc0);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक DW_CFA_opeअक्रम(अचिन्हित दीर्घ insn)
अणु
	वापस (insn & 0x3f);
पूर्ण

#घोषणा DW_EH_FRAME_CIE	0		/* .eh_frame CIE IDs are 0 */
#घोषणा DW_CIE_ID	0xffffffff
#घोषणा DW64_CIE_ID	0xffffffffffffffffULL

/*
 * DWARF FDE/CIE length field values.
 */
#घोषणा DW_EXT_LO	0xfffffff0
#घोषणा DW_EXT_HI	0xffffffff
#घोषणा DW_EXT_DWARF64	DW_EXT_HI

बाह्य काष्ठा dwarf_frame *dwarf_unwind_stack(अचिन्हित दीर्घ,
					      काष्ठा dwarf_frame *);
बाह्य व्योम dwarf_मुक्त_frame(काष्ठा dwarf_frame *);

बाह्य पूर्णांक module_dwarf_finalize(स्थिर Elf_Ehdr *, स्थिर Elf_Shdr *,
				 काष्ठा module *);
बाह्य व्योम module_dwarf_cleanup(काष्ठा module *);

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा CFI_STARTPROC	.cfi_startproc
#घोषणा CFI_ENDPROC	.cfi_endproc
#घोषणा CFI_DEF_CFA	.cfi_def_cfa
#घोषणा CFI_REGISTER	.cfi_रेजिस्टर
#घोषणा CFI_REL_OFFSET	.cfi_rel_offset
#घोषणा CFI_UNDEFINED	.cfi_undefined

#अन्यथा

/*
 * Use the यंत्र comment अक्षरacter to ignore the rest of the line.
 */
#घोषणा CFI_IGNORE	!

#घोषणा CFI_STARTPROC	CFI_IGNORE
#घोषणा CFI_ENDPROC	CFI_IGNORE
#घोषणा CFI_DEF_CFA	CFI_IGNORE
#घोषणा CFI_REGISTER	CFI_IGNORE
#घोषणा CFI_REL_OFFSET	CFI_IGNORE
#घोषणा CFI_UNDEFINED	CFI_IGNORE

#अगर_अघोषित __ASSEMBLY__
अटल अंतरभूत व्योम dwarf_unwinder_init(व्योम)
अणु
पूर्ण

#घोषणा module_dwarf_finalize(hdr, sechdrs, me)	(0)
#घोषणा module_dwarf_cleanup(mod)		करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_DWARF_UNWINDER */

#पूर्ण_अगर /* __ASM_SH_DWARF_H */
