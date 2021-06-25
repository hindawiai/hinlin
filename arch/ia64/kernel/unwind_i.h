<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2000, 2002-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *
 * Kernel unwind support.
 */

#घोषणा UNW_VER(x)		((x) >> 48)
#घोषणा UNW_FLAG_MASK		0x0000ffff00000000
#घोषणा UNW_FLAG_OSMASK		0x0000f00000000000
#घोषणा UNW_FLAG_EHANDLER(x)	((x) & 0x0000000100000000L)
#घोषणा UNW_FLAG_UHANDLER(x)	((x) & 0x0000000200000000L)
#घोषणा UNW_LENGTH(x)		((x) & 0x00000000ffffffffL)

क्रमागत unw_रेजिस्टर_index अणु
	/* primary unat: */
	UNW_REG_PRI_UNAT_GR,
	UNW_REG_PRI_UNAT_MEM,

	/* रेजिस्टर stack */
	UNW_REG_BSP,					/* रेजिस्टर stack poपूर्णांकer */
	UNW_REG_BSPSTORE,
	UNW_REG_PFS,					/* previous function state */
	UNW_REG_RNAT,
	/* memory stack */
	UNW_REG_PSP,					/* previous memory stack poपूर्णांकer */
	/* वापस poपूर्णांकer: */
	UNW_REG_RP,

	/* preserved रेजिस्टरs: */
	UNW_REG_R4, UNW_REG_R5, UNW_REG_R6, UNW_REG_R7,
	UNW_REG_UNAT, UNW_REG_PR, UNW_REG_LC, UNW_REG_FPSR,
	UNW_REG_B1, UNW_REG_B2, UNW_REG_B3, UNW_REG_B4, UNW_REG_B5,
	UNW_REG_F2, UNW_REG_F3, UNW_REG_F4, UNW_REG_F5,
	UNW_REG_F16, UNW_REG_F17, UNW_REG_F18, UNW_REG_F19,
	UNW_REG_F20, UNW_REG_F21, UNW_REG_F22, UNW_REG_F23,
	UNW_REG_F24, UNW_REG_F25, UNW_REG_F26, UNW_REG_F27,
	UNW_REG_F28, UNW_REG_F29, UNW_REG_F30, UNW_REG_F31,
	UNW_NUM_REGS
पूर्ण;

काष्ठा unw_info_block अणु
	u64 header;
	u64 desc[];		/* unwind descriptors */
	/* personality routine and language-specअगरic data follow behind descriptors */
पूर्ण;

काष्ठा unw_table अणु
	काष्ठा unw_table *next;		/* must be first member! */
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ gp;		/* global poपूर्णांकer क्रम this load-module */
	अचिन्हित दीर्घ segment_base;	/* base क्रम offsets in the unwind table entries */
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	स्थिर काष्ठा unw_table_entry *array;
	अचिन्हित दीर्घ length;
पूर्ण;

क्रमागत unw_where अणु
	UNW_WHERE_NONE,			/* रेजिस्टर isn't saved at all */
	UNW_WHERE_GR,			/* रेजिस्टर is saved in a general रेजिस्टर */
	UNW_WHERE_FR,			/* रेजिस्टर is saved in a भग्नing-poपूर्णांक रेजिस्टर */
	UNW_WHERE_BR,			/* रेजिस्टर is saved in a branch रेजिस्टर */
	UNW_WHERE_SPREL,		/* रेजिस्टर is saved on memstack (sp-relative) */
	UNW_WHERE_PSPREL,		/* रेजिस्टर is saved on memstack (psp-relative) */
	/*
	 * At the end of each prologue these locations get resolved to
	 * UNW_WHERE_PSPREL and UNW_WHERE_GR, respectively:
	 */
	UNW_WHERE_SPILL_HOME,		/* रेजिस्टर is saved in its spill home */
	UNW_WHERE_GR_SAVE		/* रेजिस्टर is saved in next general रेजिस्टर */
पूर्ण;

#घोषणा UNW_WHEN_NEVER	0x7fffffff

काष्ठा unw_reg_info अणु
	अचिन्हित दीर्घ val;		/* save location: रेजिस्टर number or offset */
	क्रमागत unw_where where;		/* where the रेजिस्टर माला_लो saved */
	पूर्णांक when;			/* when the रेजिस्टर माला_लो saved */
पूर्ण;

काष्ठा unw_reg_state अणु
	काष्ठा unw_reg_state *next;		/* next (outer) element on state stack */
	काष्ठा unw_reg_info reg[UNW_NUM_REGS];	/* रेजिस्टर save locations */
पूर्ण;

काष्ठा unw_labeled_state अणु
	काष्ठा unw_labeled_state *next;		/* next labeled state (or शून्य) */
	अचिन्हित दीर्घ label;			/* label क्रम this state */
	काष्ठा unw_reg_state saved_state;
पूर्ण;

काष्ठा unw_state_record अणु
	अचिन्हित पूर्णांक first_region : 1;	/* is this the first region? */
	अचिन्हित पूर्णांक करोne : 1;		/* are we करोne scanning descriptors? */
	अचिन्हित पूर्णांक any_spills : 1;	/* got any रेजिस्टर spills? */
	अचिन्हित पूर्णांक in_body : 1;	/* are we inside a body (as opposed to a prologue)? */
	अचिन्हित दीर्घ flags;		/* see UNW_FLAG_* in unwind.h */

	u8 *imask;			/* imask of spill_mask record or शून्य */
	अचिन्हित दीर्घ pr_val;		/* predicate values */
	अचिन्हित दीर्घ pr_mask;		/* predicate mask */
	दीर्घ spill_offset;		/* psp-relative offset क्रम spill base */
	पूर्णांक region_start;
	पूर्णांक region_len;
	पूर्णांक epilogue_start;
	पूर्णांक epilogue_count;
	पूर्णांक when_target;

	u8 gr_save_loc;			/* next general रेजिस्टर to use क्रम saving a रेजिस्टर */
	u8 वापस_link_reg;		/* branch रेजिस्टर in which the वापस link is passed */

	काष्ठा unw_labeled_state *labeled_states;	/* list of all labeled states */
	काष्ठा unw_reg_state curr;	/* current state */
पूर्ण;

क्रमागत unw_nat_type अणु
	UNW_NAT_NONE,		/* NaT not represented */
	UNW_NAT_VAL,		/* NaT represented by NaT value (fp reg) */
	UNW_NAT_MEMSTK,		/* NaT value is in unat word at offset OFF  */
	UNW_NAT_REGSTK		/* NaT is in rnat */
पूर्ण;

क्रमागत unw_insn_opcode अणु
	UNW_INSN_ADD,			/* s[dst] += val */
	UNW_INSN_ADD_PSP,		/* s[dst] = (s.psp + val) */
	UNW_INSN_ADD_SP,		/* s[dst] = (s.sp + val) */
	UNW_INSN_MOVE,			/* s[dst] = s[val] */
	UNW_INSN_MOVE2,			/* s[dst] = s[val]; s[dst+1] = s[val+1] */
	UNW_INSN_MOVE_STACKED,		/* s[dst] = ia64_rse_skip(*s.bsp, val) */
	UNW_INSN_SETNAT_MEMSTK,		/* s[dst+1].nat.type = MEMSTK;
					   s[dst+1].nat.off = *s.pri_unat - s[dst] */
	UNW_INSN_SETNAT_TYPE,		/* s[dst+1].nat.type = val */
	UNW_INSN_LOAD,			/* s[dst] = *s[val] */
	UNW_INSN_MOVE_SCRATCH,		/* s[dst] = scratch reg "val" */
	UNW_INSN_MOVE_CONST,            /* s[dst] = स्थिरant reg "val" */
पूर्ण;

काष्ठा unw_insn अणु
	अचिन्हित पूर्णांक opc	:  4;
	अचिन्हित पूर्णांक dst	:  9;
	चिन्हित पूर्णांक val		: 19;
पूर्ण;

/*
 * Preserved general अटल रेजिस्टरs (r4-r7) give rise to two script
 * inकाष्ठाions; everything अन्यथा yields at most one inकाष्ठाion; at
 * the end of the script, the psp माला_लो popped, accounting क्रम one more
 * inकाष्ठाion.
 */
#घोषणा UNW_MAX_SCRIPT_LEN	(UNW_NUM_REGS + 5)

काष्ठा unw_script अणु
	अचिन्हित दीर्घ ip;		/* ip this script is क्रम */
	अचिन्हित दीर्घ pr_mask;		/* mask of predicates script depends on */
	अचिन्हित दीर्घ pr_val;		/* predicate values this script is क्रम */
	rwlock_t lock;
	अचिन्हित पूर्णांक flags;		/* see UNW_FLAG_* in unwind.h */
	अचिन्हित लघु lru_chain;	/* used क्रम least-recently-used chain */
	अचिन्हित लघु coll_chain;	/* used क्रम hash collisions */
	अचिन्हित लघु hपूर्णांक;		/* hपूर्णांक क्रम next script to try (or -1) */
	अचिन्हित लघु count;		/* number of inकाष्ठाions in script */
	काष्ठा unw_insn insn[UNW_MAX_SCRIPT_LEN];
पूर्ण;
