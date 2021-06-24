<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_ARCHRANDOM_H
#घोषणा _ASM_POWERPC_ARCHRANDOM_H

#अगर_घोषित CONFIG_ARCH_RANDOM

#समावेश <यंत्र/machdep.h>

अटल अंतरभूत bool __must_check arch_get_अक्रमom_दीर्घ(अचिन्हित दीर्घ *v)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool __must_check arch_get_अक्रमom_पूर्णांक(अचिन्हित पूर्णांक *v)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool __must_check arch_get_अक्रमom_seed_दीर्घ(अचिन्हित दीर्घ *v)
अणु
	अगर (ppc_md.get_अक्रमom_seed)
		वापस ppc_md.get_अक्रमom_seed(v);

	वापस false;
पूर्ण

अटल अंतरभूत bool __must_check arch_get_अक्रमom_seed_पूर्णांक(अचिन्हित पूर्णांक *v)
अणु
	अचिन्हित दीर्घ val;
	bool rc;

	rc = arch_get_अक्रमom_seed_दीर्घ(&val);
	अगर (rc)
		*v = val;

	वापस rc;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_RANDOM */

#अगर_घोषित CONFIG_PPC_POWERNV
पूर्णांक घातernv_hwrng_present(व्योम);
पूर्णांक घातernv_get_अक्रमom_दीर्घ(अचिन्हित दीर्घ *v);
पूर्णांक घातernv_get_अक्रमom_real_mode(अचिन्हित दीर्घ *v);
#अन्यथा
अटल अंतरभूत पूर्णांक घातernv_hwrng_present(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक घातernv_get_अक्रमom_real_mode(अचिन्हित दीर्घ *v) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_POWERPC_ARCHRANDOM_H */
