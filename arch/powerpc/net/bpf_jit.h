<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * bpf_jit.h: BPF JIT compiler क्रम PPC
 *
 * Copyright 2011 Matt Evans <matt@ozद_असल.org>, IBM Corporation
 * 	     2016 Naveen N. Rao <naveen.n.rao@linux.vnet.ibm.com>
 */
#अगर_अघोषित _BPF_JIT_H
#घोषणा _BPF_JIT_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/ppc-opcode.h>

#अगर_घोषित PPC64_ELF_ABI_v1
#घोषणा FUNCTION_DESCR_SIZE	24
#अन्यथा
#घोषणा FUNCTION_DESCR_SIZE	0
#पूर्ण_अगर

#घोषणा PLANT_INSTR(d, idx, instr)					      \
	करो अणु अगर (d) अणु (d)[idx] = instr; पूर्ण idx++; पूर्ण जबतक (0)
#घोषणा EMIT(instr)		PLANT_INSTR(image, ctx->idx, instr)

/* Long jump; (unconditional 'branch') */
#घोषणा PPC_JMP(dest)		EMIT(PPC_INST_BRANCH |			      \
				     (((dest) - (ctx->idx * 4)) & 0x03fffffc))
/* blr; (unconditional 'branch' with link) to असलolute address */
#घोषणा PPC_BL_ABS(dest)	EMIT(PPC_INST_BL |			      \
				     (((dest) - (अचिन्हित दीर्घ)(image + ctx->idx)) & 0x03fffffc))
/* "cond" here covers BO:BI fields. */
#घोषणा PPC_BCC_SHORT(cond, dest)	EMIT(PPC_INST_BRANCH_COND |	      \
					     (((cond) & 0x3ff) << 16) |	      \
					     (((dest) - (ctx->idx * 4)) &     \
					      0xfffc))
/* Sign-extended 32-bit immediate load */
#घोषणा PPC_LI32(d, i)		करो अणु					      \
		अगर ((पूर्णांक)(uपूर्णांकptr_t)(i) >= -32768 &&			      \
				(पूर्णांक)(uपूर्णांकptr_t)(i) < 32768)		      \
			EMIT(PPC_RAW_LI(d, i));				      \
		अन्यथा अणु							      \
			EMIT(PPC_RAW_LIS(d, IMM_H(i)));			      \
			अगर (IMM_L(i))					      \
				EMIT(PPC_RAW_ORI(d, d, IMM_L(i)));	      \
		पूर्ण पूर्ण जबतक(0)

#अगर_घोषित CONFIG_PPC32
#घोषणा PPC_EX32(r, i)		EMIT(PPC_RAW_LI((r), (i) < 0 ? -1 : 0))
#पूर्ण_अगर

#घोषणा PPC_LI64(d, i)		करो अणु					      \
		अगर ((दीर्घ)(i) >= -2147483648 &&				      \
				(दीर्घ)(i) < 2147483648)			      \
			PPC_LI32(d, i);					      \
		अन्यथा अणु							      \
			अगर (!((uपूर्णांकptr_t)(i) & 0xffff800000000000ULL))	      \
				EMIT(PPC_RAW_LI(d, ((uपूर्णांकptr_t)(i) >> 32) &   \
						0xffff));		      \
			अन्यथा अणु						      \
				EMIT(PPC_RAW_LIS(d, ((uपूर्णांकptr_t)(i) >> 48))); \
				अगर ((uपूर्णांकptr_t)(i) & 0x0000ffff00000000ULL)   \
					EMIT(PPC_RAW_ORI(d, d,		      \
					  ((uपूर्णांकptr_t)(i) >> 32) & 0xffff));  \
			पूर्ण						      \
			EMIT(PPC_RAW_SLDI(d, d, 32));			      \
			अगर ((uपूर्णांकptr_t)(i) & 0x00000000ffff0000ULL)	      \
				EMIT(PPC_RAW_ORIS(d, d,			      \
					 ((uपूर्णांकptr_t)(i) >> 16) & 0xffff));   \
			अगर ((uपूर्णांकptr_t)(i) & 0x000000000000ffffULL)	      \
				EMIT(PPC_RAW_ORI(d, d, (uपूर्णांकptr_t)(i) &       \
							0xffff));             \
		पूर्ण पूर्ण जबतक (0)

#अगर_घोषित CONFIG_PPC64
#घोषणा PPC_FUNC_ADDR(d,i) करो अणु PPC_LI64(d, i); पूर्ण जबतक(0)
#अन्यथा
#घोषणा PPC_FUNC_ADDR(d,i) करो अणु PPC_LI32(d, i); पूर्ण जबतक(0)
#पूर्ण_अगर

अटल अंतरभूत bool is_nearbranch(पूर्णांक offset)
अणु
	वापस (offset < 32768) && (offset >= -32768);
पूर्ण

/*
 * The fly in the oपूर्णांकment of code size changing from pass to pass is
 * aव्योमed by padding the लघु branch हाल with a NOP.	 If code size dअगरfers
 * with dअगरferent branch reaches we will have the issue of code moving from
 * one pass to the next and will need a few passes to converge on a stable
 * state.
 */
#घोषणा PPC_BCC(cond, dest)	करो अणु					      \
		अगर (is_nearbranch((dest) - (ctx->idx * 4))) अणु		      \
			PPC_BCC_SHORT(cond, dest);			      \
			EMIT(PPC_RAW_NOP());				      \
		पूर्ण अन्यथा अणु						      \
			/* Flip the 'T or F' bit to invert comparison */      \
			PPC_BCC_SHORT(cond ^ COND_CMP_TRUE, (ctx->idx+2)*4);  \
			PPC_JMP(dest);					      \
		पूर्ण पूर्ण जबतक(0)

/* To create a branch condition, select a bit of cr0... */
#घोषणा CR0_LT		0
#घोषणा CR0_GT		1
#घोषणा CR0_EQ		2
/* ...and modअगरy BO[3] */
#घोषणा COND_CMP_TRUE	0x100
#घोषणा COND_CMP_FALSE	0x000
/* Together, they make all required comparisons: */
#घोषणा COND_GT		(CR0_GT | COND_CMP_TRUE)
#घोषणा COND_GE		(CR0_LT | COND_CMP_FALSE)
#घोषणा COND_EQ		(CR0_EQ | COND_CMP_TRUE)
#घोषणा COND_NE		(CR0_EQ | COND_CMP_FALSE)
#घोषणा COND_LT		(CR0_LT | COND_CMP_TRUE)
#घोषणा COND_LE		(CR0_GT | COND_CMP_FALSE)

#घोषणा SEEN_FUNC	0x20000000 /* might call बाह्यal helpers */
#घोषणा SEEN_STACK	0x40000000 /* uses BPF stack */
#घोषणा SEEN_TAILCALL	0x80000000 /* uses tail calls */

#घोषणा SEEN_VREG_MASK	0x1ff80000 /* Volatile रेजिस्टरs r3-r12 */
#घोषणा SEEN_NVREG_MASK	0x0003ffff /* Non अस्थिर रेजिस्टरs r14-r31 */

#अगर_घोषित CONFIG_PPC64
बाह्य स्थिर पूर्णांक b2p[MAX_BPF_JIT_REG + 2];
#अन्यथा
बाह्य स्थिर पूर्णांक b2p[MAX_BPF_JIT_REG + 1];
#पूर्ण_अगर

काष्ठा codegen_context अणु
	/*
	 * This is used to track रेजिस्टर usage as well
	 * as calls to बाह्यal helpers.
	 * - रेजिस्टर usage is tracked with corresponding
	 *   bits (r3-r31)
	 * - rest of the bits can be used to track other
	 *   things -- क्रम now, we use bits 0 to 2
	 *   encoded in SEEN_* macros above
	 */
	अचिन्हित पूर्णांक seen;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक stack_size;
	पूर्णांक b2p[ARRAY_SIZE(b2p)];
पूर्ण;

अटल अंतरभूत व्योम bpf_flush_icache(व्योम *start, व्योम *end)
अणु
	smp_wmb();	/* smp ग_लिखो barrier */
	flush_icache_range((अचिन्हित दीर्घ)start, (अचिन्हित दीर्घ)end);
पूर्ण

अटल अंतरभूत bool bpf_is_seen_रेजिस्टर(काष्ठा codegen_context *ctx, पूर्णांक i)
अणु
	वापस ctx->seen & (1 << (31 - i));
पूर्ण

अटल अंतरभूत व्योम bpf_set_seen_रेजिस्टर(काष्ठा codegen_context *ctx, पूर्णांक i)
अणु
	ctx->seen |= 1 << (31 - i);
पूर्ण

अटल अंतरभूत व्योम bpf_clear_seen_रेजिस्टर(काष्ठा codegen_context *ctx, पूर्णांक i)
अणु
	ctx->seen &= ~(1 << (31 - i));
पूर्ण

व्योम bpf_jit_emit_func_call_rel(u32 *image, काष्ठा codegen_context *ctx, u64 func);
पूर्णांक bpf_jit_build_body(काष्ठा bpf_prog *fp, u32 *image, काष्ठा codegen_context *ctx,
		       u32 *addrs, bool extra_pass);
व्योम bpf_jit_build_prologue(u32 *image, काष्ठा codegen_context *ctx);
व्योम bpf_jit_build_epilogue(u32 *image, काष्ठा codegen_context *ctx);
व्योम bpf_jit_पुनः_स्मृति_regs(काष्ठा codegen_context *ctx);

#पूर्ण_अगर

#पूर्ण_अगर
