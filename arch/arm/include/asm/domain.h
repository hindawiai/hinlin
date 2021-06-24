<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/करोमुख्य.h
 *
 *  Copyright (C) 1999 Russell King.
 */
#अगर_अघोषित __ASM_PROC_DOMAIN_H
#घोषणा __ASM_PROC_DOMAIN_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#पूर्ण_अगर

/*
 * Doमुख्य numbers
 *
 *  DOMAIN_IO     - करोमुख्य 2 includes all IO only
 *  DOMAIN_USER   - करोमुख्य 1 includes all user memory only
 *  DOMAIN_KERNEL - करोमुख्य 0 includes all kernel memory only
 *
 * The करोमुख्य numbering depends on whether we support 36 physical
 * address क्रम I/O or not.  Addresses above the 32 bit boundary can
 * only be mapped using supersections and supersections can only
 * be set क्रम करोमुख्य 0.  We could just शेष to DOMAIN_IO as zero,
 * but there may be प्रणालीs with supersection support and no 36-bit
 * addressing.  In such हालs, we want to map प्रणाली memory with
 * supersections to reduce TLB misses and footprपूर्णांक.
 *
 * 36-bit addressing and supersections are only available on
 * CPUs based on ARMv6+ or the Intel XSC3 core.
 */
#अगर_अघोषित CONFIG_IO_36
#घोषणा DOMAIN_KERNEL	0
#घोषणा DOMAIN_USER	1
#घोषणा DOMAIN_IO	2
#अन्यथा
#घोषणा DOMAIN_KERNEL	2
#घोषणा DOMAIN_USER	1
#घोषणा DOMAIN_IO	0
#पूर्ण_अगर
#घोषणा DOMAIN_VECTORS	3

/*
 * Doमुख्य types
 */
#घोषणा DOMAIN_NOACCESS	0
#घोषणा DOMAIN_CLIENT	1
#अगर_घोषित CONFIG_CPU_USE_DOMAINS
#घोषणा DOMAIN_MANAGER	3
#अन्यथा
#घोषणा DOMAIN_MANAGER	1
#पूर्ण_अगर

#घोषणा करोमुख्य_mask(करोm)	((3) << (2 * (करोm)))
#घोषणा करोमुख्य_val(करोm,type)	((type) << (2 * (करोm)))

#अगर_घोषित CONFIG_CPU_SW_DOMAIN_PAN
#घोषणा DACR_INIT \
	(करोमुख्य_val(DOMAIN_USER, DOMAIN_NOACCESS) | \
	 करोमुख्य_val(DOMAIN_KERNEL, DOMAIN_MANAGER) | \
	 करोमुख्य_val(DOMAIN_IO, DOMAIN_CLIENT) | \
	 करोमुख्य_val(DOMAIN_VECTORS, DOMAIN_CLIENT))
#अन्यथा
#घोषणा DACR_INIT \
	(करोमुख्य_val(DOMAIN_USER, DOMAIN_CLIENT) | \
	 करोमुख्य_val(DOMAIN_KERNEL, DOMAIN_MANAGER) | \
	 करोमुख्य_val(DOMAIN_IO, DOMAIN_CLIENT) | \
	 करोमुख्य_val(DOMAIN_VECTORS, DOMAIN_CLIENT))
#पूर्ण_अगर

#घोषणा __DACR_DEFAULT \
	करोमुख्य_val(DOMAIN_KERNEL, DOMAIN_CLIENT) | \
	करोमुख्य_val(DOMAIN_IO, DOMAIN_CLIENT) | \
	करोमुख्य_val(DOMAIN_VECTORS, DOMAIN_CLIENT)

#घोषणा DACR_UACCESS_DISABLE	\
	(__DACR_DEFAULT | करोमुख्य_val(DOMAIN_USER, DOMAIN_NOACCESS))
#घोषणा DACR_UACCESS_ENABLE	\
	(__DACR_DEFAULT | करोमुख्य_val(DOMAIN_USER, DOMAIN_CLIENT))

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_CPU_CP15_MMU
अटल __always_अंतरभूत अचिन्हित पूर्णांक get_करोमुख्य(व्योम)
अणु
	अचिन्हित पूर्णांक करोमुख्य;

	यंत्र(
	"mrc	p15, 0, %0, c3, c0	@ get domain"
	 : "=r" (करोमुख्य)
	 : "m" (current_thपढ़ो_info()->cpu_करोमुख्य));

	वापस करोमुख्य;
पूर्ण

अटल __always_अंतरभूत व्योम set_करोमुख्य(अचिन्हित पूर्णांक val)
अणु
	यंत्र अस्थिर(
	"mcr	p15, 0, %0, c3, c0	@ set domain"
	  : : "r" (val) : "memory");
	isb();
पूर्ण
#अन्यथा
अटल __always_अंतरभूत अचिन्हित पूर्णांक get_करोमुख्य(व्योम)
अणु
	वापस 0;
पूर्ण

अटल __always_अंतरभूत व्योम set_करोमुख्य(अचिन्हित पूर्णांक val)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_USE_DOMAINS
#घोषणा modअगरy_करोमुख्य(करोm,type)					\
	करो अणु							\
		अचिन्हित पूर्णांक करोमुख्य = get_करोमुख्य();		\
		करोमुख्य &= ~करोमुख्य_mask(करोm);			\
		करोमुख्य = करोमुख्य | करोमुख्य_val(करोm, type);	\
		set_करोमुख्य(करोमुख्य);				\
	पूर्ण जबतक (0)

#अन्यथा
अटल अंतरभूत व्योम modअगरy_करोमुख्य(अचिन्हित करोm, अचिन्हित type)	अणु पूर्ण
#पूर्ण_अगर

/*
 * Generate the T (user) versions of the LDR/STR and related
 * inकाष्ठाions (अंतरभूत assembly)
 */
#अगर_घोषित CONFIG_CPU_USE_DOMAINS
#घोषणा TUSER(instr)		TUSERCOND(instr, )
#घोषणा TUSERCOND(instr, cond)	#instr "t" #cond
#अन्यथा
#घोषणा TUSER(instr)		TUSERCOND(instr, )
#घोषणा TUSERCOND(instr, cond)	#instr #cond
#पूर्ण_अगर

#अन्यथा /* __ASSEMBLY__ */

/*
 * Generate the T (user) versions of the LDR/STR and related
 * inकाष्ठाions
 */
#अगर_घोषित CONFIG_CPU_USE_DOMAINS
#घोषणा TUSER(instr)	instr ## t
#अन्यथा
#घोषणा TUSER(instr)	instr
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* !__ASM_PROC_DOMAIN_H */
