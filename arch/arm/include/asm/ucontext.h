<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASMARM_UCONTEXT_H
#घोषणा _ASMARM_UCONTEXT_H

#समावेश <यंत्र/fpstate.h>
#समावेश <यंत्र/user.h>

/*
 * काष्ठा sigcontext only has room क्रम the basic रेजिस्टरs, but काष्ठा
 * ucontext now has room क्रम all रेजिस्टरs which need to be saved and
 * restored.  Coprocessor रेजिस्टरs are stored in uc_regspace.  Each
 * coprocessor's saved state should start with a करोcumented 32-bit magic
 * number, followed by a 32-bit word giving the coproccesor's saved size.
 * uc_regspace may be expanded अगर necessary, although this takes some
 * coordination with glibc.
 */

काष्ठा ucontext अणु
	अचिन्हित दीर्घ	  uc_flags;
	काष्ठा ucontext  *uc_link;
	stack_t		  uc_stack;
	काष्ठा sigcontext uc_mcontext;
	sigset_t	  uc_sigmask;
	/* Allow क्रम uc_sigmask growth.  Glibc uses a 1024-bit sigset_t.  */
	पूर्णांक		  __unused[32 - (माप (sigset_t) / माप (पूर्णांक))];
	/* Last क्रम extensibility.  Eight byte aligned because some
	   coprocessors require eight byte alignment.  */
 	अचिन्हित दीर्घ	  uc_regspace[128] __attribute__((__aligned__(8)));
पूर्ण;

#अगर_घोषित __KERNEL__

/*
 * Coprocessor save state.  The magic values and specअगरic
 * coprocessor's layouts are part of the userspace ABI.  Each one of
 * these should be a multiple of eight bytes and aligned to eight
 * bytes, to prevent unpredictable padding in the संकेत frame.
 */

/*
 * Dummy padding block: अगर this magic is encountered, the block should
 * be skipped using the corresponding size field.
 */
#घोषणा DUMMY_MAGIC		0xb0d9ed01

#अगर_घोषित CONFIG_CRUNCH
#घोषणा CRUNCH_MAGIC		0x5065cf03
#घोषणा CRUNCH_STORAGE_SIZE	(CRUNCH_SIZE + 8)

काष्ठा crunch_sigframe अणु
	अचिन्हित दीर्घ	magic;
	अचिन्हित दीर्घ	size;
	काष्ठा crunch_state	storage;
पूर्ण __attribute__((__aligned__(8)));
#पूर्ण_अगर

#अगर_घोषित CONFIG_IWMMXT
/* iwmmxt_area is 0x98 bytes दीर्घ, preceded by 8 bytes of signature */
#घोषणा IWMMXT_MAGIC		0x12ef842a
#घोषणा IWMMXT_STORAGE_SIZE	(IWMMXT_SIZE + 8)

काष्ठा iwmmxt_sigframe अणु
	अचिन्हित दीर्घ	magic;
	अचिन्हित दीर्घ	size;
	काष्ठा iwmmxt_काष्ठा storage;
पूर्ण __attribute__((__aligned__(8)));
#पूर्ण_अगर /* CONFIG_IWMMXT */

#अगर_घोषित CONFIG_VFP
#घोषणा VFP_MAGIC		0x56465001

काष्ठा vfp_sigframe
अणु
	अचिन्हित दीर्घ		magic;
	अचिन्हित दीर्घ		size;
	काष्ठा user_vfp		ufp;
	काष्ठा user_vfp_exc	ufp_exc;
पूर्ण __attribute__((__aligned__(8)));

/*
 *  8 byte क्रम magic and size, 264 byte क्रम ufp, 12 bytes क्रम ufp_exc,
 *  4 bytes padding.
 */
#घोषणा VFP_STORAGE_SIZE	माप(काष्ठा vfp_sigframe)

#पूर्ण_अगर /* CONFIG_VFP */

/*
 * Auxiliary संकेत frame.  This saves stuff like FP state.
 * The layout of this काष्ठाure is not part of the user ABI,
 * because the config options aren't.  uc_regspace is really
 * one of these.
 */
काष्ठा aux_sigframe अणु
#अगर_घोषित CONFIG_CRUNCH
	काष्ठा crunch_sigframe	crunch;
#पूर्ण_अगर
#अगर_घोषित CONFIG_IWMMXT
	काष्ठा iwmmxt_sigframe	iwmmxt;
#पूर्ण_अगर
#अगर_घोषित CONFIG_VFP
	काष्ठा vfp_sigframe	vfp;
#पूर्ण_अगर
	/* Something that isn't a valid magic number क्रम any coprocessor.  */
	अचिन्हित दीर्घ		end_magic;
पूर्ण __attribute__((__aligned__(8)));

#पूर्ण_अगर

#पूर्ण_अगर /* !_ASMARM_UCONTEXT_H */
