<शैली गुरु>
#अगर_अघोषित _ASM_X86_DISABLED_FEATURES_H
#घोषणा _ASM_X86_DISABLED_FEATURES_H

/* These features, although they might be available in a CPU
 * will not be used because the compile options to support
 * them are not present.
 *
 * This code allows them to be checked and disabled at
 * compile समय without an explicit #अगर_घोषित.  Use
 * cpu_feature_enabled().
 */

#अगर_घोषित CONFIG_X86_SMAP
# define DISABLE_SMAP	0
#अन्यथा
# define DISABLE_SMAP	(1<<(X86_FEATURE_SMAP & 31))
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_UMIP
# define DISABLE_UMIP	0
#अन्यथा
# define DISABLE_UMIP	(1<<(X86_FEATURE_UMIP & 31))
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_64
# define DISABLE_VME		(1<<(X86_FEATURE_VME & 31))
# define DISABLE_K6_MTRR	(1<<(X86_FEATURE_K6_MTRR & 31))
# define DISABLE_CYRIX_ARR	(1<<(X86_FEATURE_CYRIX_ARR & 31))
# define DISABLE_CENTAUR_MCR	(1<<(X86_FEATURE_CENTAUR_MCR & 31))
# define DISABLE_PCID		0
#अन्यथा
# define DISABLE_VME		0
# define DISABLE_K6_MTRR	0
# define DISABLE_CYRIX_ARR	0
# define DISABLE_CENTAUR_MCR	0
# define DISABLE_PCID		(1<<(X86_FEATURE_PCID & 31))
#पूर्ण_अगर /* CONFIG_X86_64 */

#अगर_घोषित CONFIG_X86_INTEL_MEMORY_PROTECTION_KEYS
# define DISABLE_PKU		0
# define DISABLE_OSPKE		0
#अन्यथा
# define DISABLE_PKU		(1<<(X86_FEATURE_PKU & 31))
# define DISABLE_OSPKE		(1<<(X86_FEATURE_OSPKE & 31))
#पूर्ण_अगर /* CONFIG_X86_INTEL_MEMORY_PROTECTION_KEYS */

#अगर_घोषित CONFIG_X86_5LEVEL
# define DISABLE_LA57	0
#अन्यथा
# define DISABLE_LA57	(1<<(X86_FEATURE_LA57 & 31))
#पूर्ण_अगर

#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
# define DISABLE_PTI		0
#अन्यथा
# define DISABLE_PTI		(1 << (X86_FEATURE_PTI & 31))
#पूर्ण_अगर

/* Force disable because it's broken beyond repair */
#घोषणा DISABLE_ENQCMD		(1 << (X86_FEATURE_ENQCMD & 31))

#अगर_घोषित CONFIG_X86_SGX
# define DISABLE_SGX	0
#अन्यथा
# define DISABLE_SGX	(1 << (X86_FEATURE_SGX & 31))
#पूर्ण_अगर

/*
 * Make sure to add features to the correct mask
 */
#घोषणा DISABLED_MASK0	(DISABLE_VME)
#घोषणा DISABLED_MASK1	0
#घोषणा DISABLED_MASK2	0
#घोषणा DISABLED_MASK3	(DISABLE_CYRIX_ARR|DISABLE_CENTAUR_MCR|DISABLE_K6_MTRR)
#घोषणा DISABLED_MASK4	(DISABLE_PCID)
#घोषणा DISABLED_MASK5	0
#घोषणा DISABLED_MASK6	0
#घोषणा DISABLED_MASK7	(DISABLE_PTI)
#घोषणा DISABLED_MASK8	0
#घोषणा DISABLED_MASK9	(DISABLE_SMAP|DISABLE_SGX)
#घोषणा DISABLED_MASK10	0
#घोषणा DISABLED_MASK11	0
#घोषणा DISABLED_MASK12	0
#घोषणा DISABLED_MASK13	0
#घोषणा DISABLED_MASK14	0
#घोषणा DISABLED_MASK15	0
#घोषणा DISABLED_MASK16	(DISABLE_PKU|DISABLE_OSPKE|DISABLE_LA57|DISABLE_UMIP| \
			 DISABLE_ENQCMD)
#घोषणा DISABLED_MASK17	0
#घोषणा DISABLED_MASK18	0
#घोषणा DISABLED_MASK19	0
#घोषणा DISABLED_MASK_CHECK BUILD_BUG_ON_ZERO(NCAPINTS != 20)

#पूर्ण_अगर /* _ASM_X86_DISABLED_FEATURES_H */
