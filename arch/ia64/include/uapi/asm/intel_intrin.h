<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_IA64_INTEL_INTRIN_H
#घोषणा _ASM_IA64_INTEL_INTRIN_H
/*
 * Intel Compiler Intrinsics
 *
 * Copyright (C) 2002,2003 Jun Nakajima <jun.nakajima@पूर्णांकel.com>
 * Copyright (C) 2002,2003 Suresh Siddha <suresh.b.siddha@पूर्णांकel.com>
 * Copyright (C) 2005,2006 Hongjiu Lu <hongjiu.lu@पूर्णांकel.com>
 *
 */
#समावेश <ia64पूर्णांकrin.h>

#घोषणा ia64_barrier()		__memory_barrier()

#घोषणा ia64_stop()	/* Nothing: As of now stop bit is generated क्रम each
		 	 * पूर्णांकrinsic
		 	 */

#घोषणा ia64_getreg		__getReg
#घोषणा ia64_setreg		__setReg

#घोषणा ia64_hपूर्णांक		__hपूर्णांक
#घोषणा ia64_hपूर्णांक_छोड़ो		__hपूर्णांक_छोड़ो

#घोषणा ia64_mux1_brcst		_m64_mux1_brcst
#घोषणा ia64_mux1_mix		_m64_mux1_mix
#घोषणा ia64_mux1_shuf		_m64_mux1_shuf
#घोषणा ia64_mux1_alt		_m64_mux1_alt
#घोषणा ia64_mux1_rev		_m64_mux1_rev

#घोषणा ia64_mux1(x,v)		_m_to_पूर्णांक64(_m64_mux1(_m_from_पूर्णांक64(x), (v)))
#घोषणा ia64_popcnt		_m64_popcnt
#घोषणा ia64_getf_exp		__getf_exp
#घोषणा ia64_shrp		_m64_shrp

#घोषणा ia64_tpa		__tpa
#घोषणा ia64_invala		__invala
#घोषणा ia64_invala_gr		__invala_gr
#घोषणा ia64_invala_fr		__invala_fr
#घोषणा ia64_nop		__nop
#घोषणा ia64_sum		__sum
#घोषणा ia64_ssm		__ssm
#घोषणा ia64_rum		__rum
#घोषणा ia64_rsm		__rsm
#घोषणा ia64_fc			__fc

#घोषणा ia64_ldfs		__ldfs
#घोषणा ia64_ldfd		__ldfd
#घोषणा ia64_ldfe		__ldfe
#घोषणा ia64_ldf8		__ldf8
#घोषणा ia64_ldf_fill		__ldf_fill

#घोषणा ia64_stfs		__stfs
#घोषणा ia64_stfd		__stfd
#घोषणा ia64_stfe		__stfe
#घोषणा ia64_stf8		__stf8
#घोषणा ia64_stf_spill		__stf_spill

#घोषणा ia64_mf			__mf
#घोषणा ia64_mfa		__mfa

#घोषणा ia64_fetchadd4_acq	__fetchadd4_acq
#घोषणा ia64_fetchadd4_rel	__fetchadd4_rel
#घोषणा ia64_fetchadd8_acq	__fetchadd8_acq
#घोषणा ia64_fetchadd8_rel	__fetchadd8_rel

#घोषणा ia64_xchg1		_InterlockedExchange8
#घोषणा ia64_xchg2		_InterlockedExchange16
#घोषणा ia64_xchg4		_InterlockedExchange
#घोषणा ia64_xchg8		_InterlockedExchange64

#घोषणा ia64_cmpxchg1_rel	_InterlockedCompareExchange8_rel
#घोषणा ia64_cmpxchg1_acq	_InterlockedCompareExchange8_acq
#घोषणा ia64_cmpxchg2_rel	_InterlockedCompareExchange16_rel
#घोषणा ia64_cmpxchg2_acq	_InterlockedCompareExchange16_acq
#घोषणा ia64_cmpxchg4_rel	_InterlockedCompareExchange_rel
#घोषणा ia64_cmpxchg4_acq	_InterlockedCompareExchange_acq
#घोषणा ia64_cmpxchg8_rel	_InterlockedCompareExchange64_rel
#घोषणा ia64_cmpxchg8_acq	_InterlockedCompareExchange64_acq

#घोषणा __ia64_set_dbr(index, val)	\
		__setIndReg(_IA64_REG_INDR_DBR, index, val)
#घोषणा ia64_set_ibr(index, val)	\
		__setIndReg(_IA64_REG_INDR_IBR, index, val)
#घोषणा ia64_set_pkr(index, val)	\
		__setIndReg(_IA64_REG_INDR_PKR, index, val)
#घोषणा ia64_set_pmc(index, val)	\
		__setIndReg(_IA64_REG_INDR_PMC, index, val)
#घोषणा ia64_set_pmd(index, val)	\
		__setIndReg(_IA64_REG_INDR_PMD, index, val)
#घोषणा ia64_set_rr(index, val)		\
		__setIndReg(_IA64_REG_INDR_RR, index, val)

#घोषणा ia64_get_cpuid(index)	\
		__getIndReg(_IA64_REG_INDR_CPUID, index)
#घोषणा __ia64_get_dbr(index)		__getIndReg(_IA64_REG_INDR_DBR, index)
#घोषणा ia64_get_ibr(index)		__getIndReg(_IA64_REG_INDR_IBR, index)
#घोषणा ia64_get_pkr(index)		__getIndReg(_IA64_REG_INDR_PKR, index)
#घोषणा ia64_get_pmc(index)		__getIndReg(_IA64_REG_INDR_PMC, index)
#घोषणा ia64_get_pmd(index)		__getIndReg(_IA64_REG_INDR_PMD, index)
#घोषणा ia64_get_rr(index)		__getIndReg(_IA64_REG_INDR_RR, index)

#घोषणा ia64_srlz_d		__dsrlz
#घोषणा ia64_srlz_i		__isrlz

#घोषणा ia64_dv_serialize_data()
#घोषणा ia64_dv_serialize_inकाष्ठाion()

#घोषणा ia64_st1_rel		__st1_rel
#घोषणा ia64_st2_rel		__st2_rel
#घोषणा ia64_st4_rel		__st4_rel
#घोषणा ia64_st8_rel		__st8_rel

/* FIXME: need st4.rel.nta पूर्णांकrinsic */
#घोषणा ia64_st4_rel_nta	__st4_rel

#घोषणा ia64_ld1_acq		__ld1_acq
#घोषणा ia64_ld2_acq		__ld2_acq
#घोषणा ia64_ld4_acq		__ld4_acq
#घोषणा ia64_ld8_acq		__ld8_acq

#घोषणा ia64_sync_i		__synci
#घोषणा ia64_thash		__thash
#घोषणा ia64_ttag		__ttag
#घोषणा ia64_itcd		__itcd
#घोषणा ia64_itci		__itci
#घोषणा ia64_itrd		__itrd
#घोषणा ia64_itri		__itri
#घोषणा ia64_ptce		__ptce
#घोषणा ia64_ptcl		__ptcl
#घोषणा ia64_ptcg		__ptcg
#घोषणा ia64_ptcga		__ptcga
#घोषणा ia64_ptri		__ptri
#घोषणा ia64_ptrd		__ptrd
#घोषणा ia64_dep_mi		_m64_dep_mi

/* Values क्रम lfhपूर्णांक in __lfetch and __lfetch_fault */

#घोषणा ia64_lfhपूर्णांक_none	__lfhपूर्णांक_none
#घोषणा ia64_lfhपूर्णांक_nt1		__lfhपूर्णांक_nt1
#घोषणा ia64_lfhपूर्णांक_nt2		__lfhपूर्णांक_nt2
#घोषणा ia64_lfhपूर्णांक_nta		__lfhपूर्णांक_nta

#घोषणा ia64_lfetch		__lfetch
#घोषणा ia64_lfetch_excl	__lfetch_excl
#घोषणा ia64_lfetch_fault	__lfetch_fault
#घोषणा ia64_lfetch_fault_excl	__lfetch_fault_excl

#घोषणा ia64_पूर्णांकrin_local_irq_restore(x)		\
करो अणु							\
	अगर ((x) != 0) अणु					\
		ia64_ssm(IA64_PSR_I);			\
		ia64_srlz_d();				\
	पूर्ण अन्यथा अणु					\
		ia64_rsm(IA64_PSR_I);			\
	पूर्ण						\
पूर्ण जबतक (0)

#घोषणा __builtin_trap()	__अवरोध(0);

#पूर्ण_अगर /* _ASM_IA64_INTEL_INTRIN_H */
