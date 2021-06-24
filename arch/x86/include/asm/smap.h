<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Supervisor Mode Access Prevention support
 *
 * Copyright (C) 2012 Intel Corporation
 * Author: H. Peter Anvin <hpa@linux.पूर्णांकel.com>
 */

#अगर_अघोषित _ASM_X86_SMAP_H
#घोषणा _ASM_X86_SMAP_H

#समावेश <यंत्र/nops.h>
#समावेश <यंत्र/cpufeatures.h>
#समावेश <यंत्र/alternative.h>

/* "Raw" inकाष्ठाion opcodes */
#घोषणा __ASM_CLAC	".byte 0x0f,0x01,0xca"
#घोषणा __ASM_STAC	".byte 0x0f,0x01,0xcb"

#अगर_घोषित __ASSEMBLY__

#अगर_घोषित CONFIG_X86_SMAP

#घोषणा ASM_CLAC \
	ALTERNATIVE "", __ASM_CLAC, X86_FEATURE_SMAP

#घोषणा ASM_STAC \
	ALTERNATIVE "", __ASM_STAC, X86_FEATURE_SMAP

#अन्यथा /* CONFIG_X86_SMAP */

#घोषणा ASM_CLAC
#घोषणा ASM_STAC

#पूर्ण_अगर /* CONFIG_X86_SMAP */

#अन्यथा /* __ASSEMBLY__ */

#अगर_घोषित CONFIG_X86_SMAP

अटल __always_अंतरभूत व्योम clac(व्योम)
अणु
	/* Note: a barrier is implicit in alternative() */
	alternative("", __ASM_CLAC, X86_FEATURE_SMAP);
पूर्ण

अटल __always_अंतरभूत व्योम stac(व्योम)
अणु
	/* Note: a barrier is implicit in alternative() */
	alternative("", __ASM_STAC, X86_FEATURE_SMAP);
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ smap_save(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	यंत्र अस्थिर ("# smap_save\n\t"
		      ALTERNATIVE("", "pushf; pop %0; " __ASM_CLAC "\n\t",
				  X86_FEATURE_SMAP)
		      : "=rm" (flags) : : "memory", "cc");

	वापस flags;
पूर्ण

अटल __always_अंतरभूत व्योम smap_restore(अचिन्हित दीर्घ flags)
अणु
	यंत्र अस्थिर ("# smap_restore\n\t"
		      ALTERNATIVE("", "push %0; popf\n\t",
				  X86_FEATURE_SMAP)
		      : : "g" (flags) : "memory", "cc");
पूर्ण

/* These macros can be used in यंत्र() statements */
#घोषणा ASM_CLAC \
	ALTERNATIVE("", __ASM_CLAC, X86_FEATURE_SMAP)
#घोषणा ASM_STAC \
	ALTERNATIVE("", __ASM_STAC, X86_FEATURE_SMAP)

#अन्यथा /* CONFIG_X86_SMAP */

अटल अंतरभूत व्योम clac(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम stac(व्योम) अणु पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ smap_save(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम smap_restore(अचिन्हित दीर्घ flags) अणु पूर्ण

#घोषणा ASM_CLAC
#घोषणा ASM_STAC

#पूर्ण_अगर /* CONFIG_X86_SMAP */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_X86_SMAP_H */
