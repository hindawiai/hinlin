<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Common समयbase prototypes and such क्रम all ppc machines.
 */

#अगर_अघोषित _ASM_POWERPC_VDSO_TIMEBASE_H
#घोषणा _ASM_POWERPC_VDSO_TIMEBASE_H

#समावेश <यंत्र/reg.h>

/*
 * We use __घातerpc64__ here because we want the compat VDSO to use the 32-bit
 * version below in the अन्यथा हाल of the अगरdef.
 */
#अगर defined(__घातerpc64__) && (defined(CONFIG_PPC_CELL) || defined(CONFIG_E500))
#घोषणा mftb()		(अणुअचिन्हित दीर्घ rval;				\
			यंत्र अस्थिर(					\
				"90:	mfspr %0, %2;\n"		\
				ASM_FTR_IFSET(				\
					"97:	cmpwi %0,0;\n"		\
					"	beq- 90b;\n", "", %1)	\
			: "=r" (rval) \
			: "i" (CPU_FTR_CELL_TB_BUG), "i" (SPRN_TBRL) : "cr0"); \
			rval;पूर्ण)
#या_अगर defined(CONFIG_PPC_8xx)
#घोषणा mftb()		(अणुअचिन्हित दीर्घ rval;	\
			यंत्र अस्थिर("mftbl %0" : "=r" (rval)); rval;पूर्ण)
#अन्यथा
#घोषणा mftb()		(अणुअचिन्हित दीर्घ rval;	\
			यंत्र अस्थिर("mfspr %0, %1" : \
				     "=r" (rval) : "i" (SPRN_TBRL)); rval;पूर्ण)
#पूर्ण_अगर /* !CONFIG_PPC_CELL */

#अगर defined(CONFIG_PPC_8xx)
#घोषणा mftbu()		(अणुअचिन्हित दीर्घ rval;	\
			यंत्र अस्थिर("mftbu %0" : "=r" (rval)); rval;पूर्ण)
#अन्यथा
#घोषणा mftbu()		(अणुअचिन्हित दीर्घ rval;	\
			यंत्र अस्थिर("mfspr %0, %1" : "=r" (rval) : \
				"i" (SPRN_TBRU)); rval;पूर्ण)
#पूर्ण_अगर

#घोषणा mttbl(v)	यंत्र अस्थिर("mttbl %0":: "r"(v))
#घोषणा mttbu(v)	यंत्र अस्थिर("mttbu %0":: "r"(v))

अटल __always_अंतरभूत u64 get_tb(व्योम)
अणु
	अचिन्हित पूर्णांक tbhi, tblo, tbhi2;

	/*
	 * We use __घातerpc64__ here not CONFIG_PPC64 because we want the compat
	 * VDSO to use the 32-bit compatible version in the जबतक loop below.
	 */
	अगर (__is_defined(__घातerpc64__))
		वापस mftb();

	करो अणु
		tbhi = mftbu();
		tblo = mftb();
		tbhi2 = mftbu();
	पूर्ण जबतक (tbhi != tbhi2);

	वापस ((u64)tbhi << 32) | tblo;
पूर्ण

अटल अंतरभूत व्योम set_tb(अचिन्हित पूर्णांक upper, अचिन्हित पूर्णांक lower)
अणु
	mtspr(SPRN_TBWL, 0);
	mtspr(SPRN_TBWU, upper);
	mtspr(SPRN_TBWL, lower);
पूर्ण

#पूर्ण_अगर /* _ASM_POWERPC_VDSO_TIMEBASE_H */
