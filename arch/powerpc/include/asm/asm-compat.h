<शैली गुरु>
#अगर_अघोषित _ASM_POWERPC_ASM_COMPAT_H
#घोषणा _ASM_POWERPC_ASM_COMPAT_H

#समावेश <यंत्र/यंत्र-स्थिर.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/ppc-opcode.h>

#अगर_घोषित __घातerpc64__

/* operations क्रम दीर्घs and poपूर्णांकers */
#घोषणा PPC_LL		stringअगरy_in_c(ld)
#घोषणा PPC_STL		stringअगरy_in_c(std)
#घोषणा PPC_STLU	stringअगरy_in_c(stdu)
#घोषणा PPC_LCMPI	stringअगरy_in_c(cmpdi)
#घोषणा PPC_LCMPLI	stringअगरy_in_c(cmpldi)
#घोषणा PPC_LCMP	stringअगरy_in_c(cmpd)
#घोषणा PPC_LONG	stringअगरy_in_c(.8byte)
#घोषणा PPC_LONG_ALIGN	stringअगरy_in_c(.balign 8)
#घोषणा PPC_TLNEI	stringअगरy_in_c(tdnei)
#घोषणा PPC_LLARX(t, a, b, eh)	PPC_LDARX(t, a, b, eh)
#घोषणा PPC_STLCX	stringअगरy_in_c(stdcx.)
#घोषणा PPC_CNTLZL	stringअगरy_in_c(cntlzd)
#घोषणा PPC_MTOCRF(FXM, RS) MTOCRF((FXM), RS)
#घोषणा PPC_LR_STKOFF	16
#घोषणा PPC_MIN_STKFRM	112

#अगर_घोषित __BIG_ENDIAN__
#घोषणा LHZX_BE	stringअगरy_in_c(lhzx)
#घोषणा LWZX_BE	stringअगरy_in_c(lwzx)
#घोषणा LDX_BE	stringअगरy_in_c(ldx)
#घोषणा STWX_BE	stringअगरy_in_c(stwx)
#घोषणा STDX_BE	stringअगरy_in_c(stdx)
#अन्यथा
#घोषणा LHZX_BE	stringअगरy_in_c(lhbrx)
#घोषणा LWZX_BE	stringअगरy_in_c(lwbrx)
#घोषणा LDX_BE	stringअगरy_in_c(ldbrx)
#घोषणा STWX_BE	stringअगरy_in_c(stwbrx)
#घोषणा STDX_BE	stringअगरy_in_c(stdbrx)
#पूर्ण_अगर

#अन्यथा /* 32-bit */

/* operations क्रम दीर्घs and poपूर्णांकers */
#घोषणा PPC_LL		stringअगरy_in_c(lwz)
#घोषणा PPC_STL		stringअगरy_in_c(stw)
#घोषणा PPC_STLU	stringअगरy_in_c(stwu)
#घोषणा PPC_LCMPI	stringअगरy_in_c(cmpwi)
#घोषणा PPC_LCMPLI	stringअगरy_in_c(cmplwi)
#घोषणा PPC_LCMP	stringअगरy_in_c(cmpw)
#घोषणा PPC_LONG	stringअगरy_in_c(.दीर्घ)
#घोषणा PPC_LONG_ALIGN	stringअगरy_in_c(.balign 4)
#घोषणा PPC_TLNEI	stringअगरy_in_c(twnei)
#घोषणा PPC_LLARX(t, a, b, eh)	PPC_LWARX(t, a, b, eh)
#घोषणा PPC_STLCX	stringअगरy_in_c(stwcx.)
#घोषणा PPC_CNTLZL	stringअगरy_in_c(cntlzw)
#घोषणा PPC_MTOCRF	stringअगरy_in_c(mtcrf)
#घोषणा PPC_LR_STKOFF	4
#घोषणा PPC_MIN_STKFRM	16

#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_POWERPC_ASM_COMPAT_H */
