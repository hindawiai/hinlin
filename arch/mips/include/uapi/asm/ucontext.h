<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __MIPS_UAPI_ASM_UCONTEXT_H
#घोषणा __MIPS_UAPI_ASM_UCONTEXT_H

/**
 * काष्ठा extcontext - extended context header काष्ठाure
 * @magic:	magic value identअगरying the type of extended context
 * @size:	the size in bytes of the enclosing काष्ठाure
 *
 * Extended context काष्ठाures provide context which करोes not fit within काष्ठा
 * sigcontext. They are placed sequentially in memory at the end of काष्ठा
 * ucontext and काष्ठा sigframe, with each extended context काष्ठाure beginning
 * with a header defined by this काष्ठा. The type of context represented is
 * indicated by the magic field. Userland may check each extended context
 * काष्ठाure against magic values that it recognises. The size field allows any
 * unrecognised context to be skipped, allowing क्रम future expansion. The end
 * of the extended context data is indicated by the magic value
 * END_EXTCONTEXT_MAGIC.
 */
काष्ठा extcontext अणु
	अचिन्हित पूर्णांक		magic;
	अचिन्हित पूर्णांक		size;
पूर्ण;

/**
 * काष्ठा msa_extcontext - MSA extended context काष्ठाure
 * @ext:	the extended context header, with magic == MSA_EXTCONTEXT_MAGIC
 * @wr:		the most signअगरicant 64 bits of each MSA vector रेजिस्टर
 * @csr:	the value of the MSA control & status रेजिस्टर
 *
 * If MSA context is live क्रम a task at the समय a संकेत is delivered to it,
 * this काष्ठाure will hold the MSA context of the task as it was prior to the
 * संकेत delivery.
 */
काष्ठा msa_extcontext अणु
	काष्ठा extcontext	ext;
#घोषणा MSA_EXTCONTEXT_MAGIC	0x784d5341	/* xMSA */

	अचिन्हित दीर्घ दीर्घ	wr[32];
	अचिन्हित पूर्णांक		csr;
पूर्ण;

#घोषणा END_EXTCONTEXT_MAGIC	0x78454e44	/* xEND */

/**
 * काष्ठा ucontext - user context काष्ठाure
 * @uc_flags:
 * @uc_link:
 * @uc_stack:
 * @uc_mcontext:	holds basic processor state
 * @uc_sigmask:
 * @uc_extcontext:	holds extended processor state
 */
काष्ठा ucontext अणु
	/* Historic fields matching यंत्र-generic */
	अचिन्हित दीर्घ		uc_flags;
	काष्ठा ucontext		*uc_link;
	stack_t			uc_stack;
	काष्ठा sigcontext	uc_mcontext;
	sigset_t		uc_sigmask;

	/* Extended context काष्ठाures may follow ucontext */
	अचिन्हित दीर्घ दीर्घ	uc_extcontext[0];
पूर्ण;

#पूर्ण_अगर /* __MIPS_UAPI_ASM_UCONTEXT_H */
