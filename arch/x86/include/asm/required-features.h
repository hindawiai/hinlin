<शैली गुरु>
#अगर_अघोषित _ASM_X86_REQUIRED_FEATURES_H
#घोषणा _ASM_X86_REQUIRED_FEATURES_H

/* Define minimum CPUID feature set क्रम kernel These bits are checked
   really early to actually display a visible error message beक्रमe the
   kernel dies.  Make sure to assign features to the proper mask!

   Some requirements that are not in CPUID yet are also in the
   CONFIG_X86_MINIMUM_CPU_FAMILY which is checked too.

   The real inक्रमmation is in arch/x86/Kconfig.cpu, this just converts
   the CONFIGs पूर्णांकo a biपंचांगask */

#अगर_अघोषित CONFIG_MATH_EMULATION
# define NEED_FPU	(1<<(X86_FEATURE_FPU & 31))
#अन्यथा
# define NEED_FPU	0
#पूर्ण_अगर

#अगर defined(CONFIG_X86_PAE) || defined(CONFIG_X86_64)
# define NEED_PAE	(1<<(X86_FEATURE_PAE & 31))
#अन्यथा
# define NEED_PAE	0
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_CMPXCHG64
# define NEED_CX8	(1<<(X86_FEATURE_CX8 & 31))
#अन्यथा
# define NEED_CX8	0
#पूर्ण_अगर

#अगर defined(CONFIG_X86_CMOV) || defined(CONFIG_X86_64)
# define NEED_CMOV	(1<<(X86_FEATURE_CMOV & 31))
#अन्यथा
# define NEED_CMOV	0
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_USE_3DNOW
# define NEED_3DNOW	(1<<(X86_FEATURE_3DNOW & 31))
#अन्यथा
# define NEED_3DNOW	0
#पूर्ण_अगर

#अगर defined(CONFIG_X86_P6_NOP) || defined(CONFIG_X86_64)
# define NEED_NOPL	(1<<(X86_FEATURE_NOPL & 31))
#अन्यथा
# define NEED_NOPL	0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MATOM
# define NEED_MOVBE	(1<<(X86_FEATURE_MOVBE & 31))
#अन्यथा
# define NEED_MOVBE	0
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_64
#अगर_घोषित CONFIG_PARAVIRT_XXL
/* Paraभवized प्रणालीs may not have PSE or PGE available */
#घोषणा NEED_PSE	0
#घोषणा NEED_PGE	0
#अन्यथा
#घोषणा NEED_PSE	(1<<(X86_FEATURE_PSE) & 31)
#घोषणा NEED_PGE	(1<<(X86_FEATURE_PGE) & 31)
#पूर्ण_अगर
#घोषणा NEED_MSR	(1<<(X86_FEATURE_MSR & 31))
#घोषणा NEED_FXSR	(1<<(X86_FEATURE_FXSR & 31))
#घोषणा NEED_XMM	(1<<(X86_FEATURE_XMM & 31))
#घोषणा NEED_XMM2	(1<<(X86_FEATURE_XMM2 & 31))
#घोषणा NEED_LM		(1<<(X86_FEATURE_LM & 31))
#अन्यथा
#घोषणा NEED_PSE	0
#घोषणा NEED_MSR	0
#घोषणा NEED_PGE	0
#घोषणा NEED_FXSR	0
#घोषणा NEED_XMM	0
#घोषणा NEED_XMM2	0
#घोषणा NEED_LM		0
#पूर्ण_अगर

#घोषणा REQUIRED_MASK0	(NEED_FPU|NEED_PSE|NEED_MSR|NEED_PAE|\
			 NEED_CX8|NEED_PGE|NEED_FXSR|NEED_CMOV|\
			 NEED_XMM|NEED_XMM2)
#घोषणा SSE_MASK	(NEED_XMM|NEED_XMM2)

#घोषणा REQUIRED_MASK1	(NEED_LM|NEED_3DNOW)

#घोषणा REQUIRED_MASK2	0
#घोषणा REQUIRED_MASK3	(NEED_NOPL)
#घोषणा REQUIRED_MASK4	(NEED_MOVBE)
#घोषणा REQUIRED_MASK5	0
#घोषणा REQUIRED_MASK6	0
#घोषणा REQUIRED_MASK7	0
#घोषणा REQUIRED_MASK8	0
#घोषणा REQUIRED_MASK9	0
#घोषणा REQUIRED_MASK10	0
#घोषणा REQUIRED_MASK11	0
#घोषणा REQUIRED_MASK12	0
#घोषणा REQUIRED_MASK13	0
#घोषणा REQUIRED_MASK14	0
#घोषणा REQUIRED_MASK15	0
#घोषणा REQUIRED_MASK16	0
#घोषणा REQUIRED_MASK17	0
#घोषणा REQUIRED_MASK18	0
#घोषणा REQUIRED_MASK19	0
#घोषणा REQUIRED_MASK_CHECK BUILD_BUG_ON_ZERO(NCAPINTS != 20)

#पूर्ण_अगर /* _ASM_X86_REQUIRED_FEATURES_H */
