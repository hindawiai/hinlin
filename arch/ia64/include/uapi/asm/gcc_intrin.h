<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *
 * Copyright (C) 2002,2003 Jun Nakajima <jun.nakajima@पूर्णांकel.com>
 * Copyright (C) 2002,2003 Suresh Siddha <suresh.b.siddha@पूर्णांकel.com>
 */
#अगर_अघोषित _UAPI_ASM_IA64_GCC_INTRIN_H
#घोषणा _UAPI_ASM_IA64_GCC_INTRIN_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>

/* define this macro to get some यंत्र sपंचांगts included in 'c' files */
#घोषणा ASM_SUPPORTED

/* Optimization barrier */
/* The "volatile" is due to gcc bugs */
#घोषणा ia64_barrier()	यंत्र अस्थिर ("":::"memory")

#घोषणा ia64_stop()	यंत्र अस्थिर (";;"::)

#घोषणा ia64_invala_gr(regnum)	यंत्र अस्थिर ("invala.e r%0" :: "i"(regnum))

#घोषणा ia64_invala_fr(regnum)	यंत्र अस्थिर ("invala.e f%0" :: "i"(regnum))

#घोषणा ia64_flushrs() यंत्र अस्थिर ("flushrs;;":::"memory")

#घोषणा ia64_loadrs() यंत्र अस्थिर ("loadrs;;":::"memory")

बाह्य व्योम ia64_bad_param_क्रम_setreg (व्योम);
बाह्य व्योम ia64_bad_param_क्रम_getreg (व्योम);


#घोषणा ia64_setreg(regnum, val)						\
(अणु										\
	चयन (regnum) अणु							\
	    हाल _IA64_REG_PSR_L:						\
		    यंत्र अस्थिर ("mov psr.l=%0" :: "r"(val) : "memory");	\
		    अवरोध;							\
	    हाल _IA64_REG_AR_KR0 ... _IA64_REG_AR_EC:				\
		    यंत्र अस्थिर ("mov ar%0=%1" ::				\
		    			  "i" (regnum - _IA64_REG_AR_KR0),	\
					  "r"(val): "memory");			\
		    अवरोध;							\
	    हाल _IA64_REG_CR_DCR ... _IA64_REG_CR_LRR1:			\
		    यंत्र अस्थिर ("mov cr%0=%1" ::				\
				          "i" (regnum - _IA64_REG_CR_DCR),	\
					  "r"(val): "memory" );			\
		    अवरोध;							\
	    हाल _IA64_REG_SP:							\
		    यंत्र अस्थिर ("mov r12=%0" ::				\
			    		  "r"(val): "memory");			\
		    अवरोध;							\
	    हाल _IA64_REG_GP:							\
		    यंत्र अस्थिर ("mov gp=%0" :: "r"(val) : "memory");		\
		अवरोध;								\
	    शेष:								\
		    ia64_bad_param_क्रम_setreg();				\
		    अवरोध;							\
	पूर्ण									\
पूर्ण)

#घोषणा ia64_getreg(regnum)							\
(अणु										\
	__u64 ia64_पूर्णांकri_res;							\
										\
	चयन (regnum) अणु							\
	हाल _IA64_REG_GP:							\
		यंत्र अस्थिर ("mov %0=gp" : "=r"(ia64_पूर्णांकri_res));		\
		अवरोध;								\
	हाल _IA64_REG_IP:							\
		यंत्र अस्थिर ("mov %0=ip" : "=r"(ia64_पूर्णांकri_res));		\
		अवरोध;								\
	हाल _IA64_REG_PSR:							\
		यंत्र अस्थिर ("mov %0=psr" : "=r"(ia64_पूर्णांकri_res));		\
		अवरोध;								\
	हाल _IA64_REG_TP:	/* क्रम current() */				\
		ia64_पूर्णांकri_res = ia64_r13;					\
		अवरोध;								\
	हाल _IA64_REG_AR_KR0 ... _IA64_REG_AR_EC:				\
		यंत्र अस्थिर ("mov %0=ar%1" : "=r" (ia64_पूर्णांकri_res)		\
				      : "i"(regnum - _IA64_REG_AR_KR0));	\
		अवरोध;								\
	हाल _IA64_REG_CR_DCR ... _IA64_REG_CR_LRR1:				\
		यंत्र अस्थिर ("mov %0=cr%1" : "=r" (ia64_पूर्णांकri_res)		\
				      : "i" (regnum - _IA64_REG_CR_DCR));	\
		अवरोध;								\
	हाल _IA64_REG_SP:							\
		यंत्र अस्थिर ("mov %0=sp" : "=r" (ia64_पूर्णांकri_res));		\
		अवरोध;								\
	शेष:								\
		ia64_bad_param_क्रम_getreg();					\
		अवरोध;								\
	पूर्ण									\
	ia64_पूर्णांकri_res;								\
पूर्ण)

#घोषणा ia64_hपूर्णांक_छोड़ो 0

#घोषणा ia64_hपूर्णांक(mode)						\
(अणु								\
	चयन (mode) अणु						\
	हाल ia64_hपूर्णांक_छोड़ो:					\
		यंत्र अस्थिर ("hint @pause" ::: "memory");	\
		अवरोध;						\
	पूर्ण							\
पूर्ण)


/* Integer values क्रम mux1 inकाष्ठाion */
#घोषणा ia64_mux1_brcst 0
#घोषणा ia64_mux1_mix   8
#घोषणा ia64_mux1_shuf  9
#घोषणा ia64_mux1_alt  10
#घोषणा ia64_mux1_rev  11

#घोषणा ia64_mux1(x, mode)							\
(अणु										\
	__u64 ia64_पूर्णांकri_res;							\
										\
	चयन (mode) अणु								\
	हाल ia64_mux1_brcst:							\
		यंत्र ("mux1 %0=%1,@brcst" : "=r" (ia64_पूर्णांकri_res) : "r" (x));	\
		अवरोध;								\
	हाल ia64_mux1_mix:							\
		यंत्र ("mux1 %0=%1,@mix" : "=r" (ia64_पूर्णांकri_res) : "r" (x));	\
		अवरोध;								\
	हाल ia64_mux1_shuf:							\
		यंत्र ("mux1 %0=%1,@shuf" : "=r" (ia64_पूर्णांकri_res) : "r" (x));	\
		अवरोध;								\
	हाल ia64_mux1_alt:							\
		यंत्र ("mux1 %0=%1,@alt" : "=r" (ia64_पूर्णांकri_res) : "r" (x));	\
		अवरोध;								\
	हाल ia64_mux1_rev:							\
		यंत्र ("mux1 %0=%1,@rev" : "=r" (ia64_पूर्णांकri_res) : "r" (x));	\
		अवरोध;								\
	पूर्ण									\
	ia64_पूर्णांकri_res;								\
पूर्ण)

#अगर __GNUC__ >= 4 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
# define ia64_popcnt(x)		__builtin_popcountl(x)
#अन्यथा
# define ia64_popcnt(x)						\
  (अणु								\
	__u64 ia64_पूर्णांकri_res;					\
	यंत्र ("popcnt %0=%1" : "=r" (ia64_पूर्णांकri_res) : "r" (x));	\
								\
	ia64_पूर्णांकri_res;						\
  पूर्ण)
#पूर्ण_अगर

#घोषणा ia64_getf_exp(x)					\
(अणु								\
	दीर्घ ia64_पूर्णांकri_res;					\
								\
	यंत्र ("getf.exp %0=%1" : "=r"(ia64_पूर्णांकri_res) : "f"(x));	\
								\
	ia64_पूर्णांकri_res;						\
पूर्ण)

#घोषणा ia64_shrp(a, b, count)								\
(अणु											\
	__u64 ia64_पूर्णांकri_res;								\
	यंत्र ("shrp %0=%1,%2,%3" : "=r"(ia64_पूर्णांकri_res) : "r"(a), "r"(b), "i"(count));	\
	ia64_पूर्णांकri_res;									\
पूर्ण)

#घोषणा ia64_ldfs(regnum, x)					\
(अणु								\
	रेजिस्टर द्विगुन __f__ यंत्र ("f"#regnum);			\
	यंत्र अस्थिर ("ldfs %0=[%1]" :"=f"(__f__): "r"(x));	\
पूर्ण)

#घोषणा ia64_ldfd(regnum, x)					\
(अणु								\
	रेजिस्टर द्विगुन __f__ यंत्र ("f"#regnum);			\
	यंत्र अस्थिर ("ldfd %0=[%1]" :"=f"(__f__): "r"(x));	\
पूर्ण)

#घोषणा ia64_ldfe(regnum, x)					\
(अणु								\
	रेजिस्टर द्विगुन __f__ यंत्र ("f"#regnum);			\
	यंत्र अस्थिर ("ldfe %0=[%1]" :"=f"(__f__): "r"(x));	\
पूर्ण)

#घोषणा ia64_ldf8(regnum, x)					\
(अणु								\
	रेजिस्टर द्विगुन __f__ यंत्र ("f"#regnum);			\
	यंत्र अस्थिर ("ldf8 %0=[%1]" :"=f"(__f__): "r"(x));	\
पूर्ण)

#घोषणा ia64_ldf_fill(regnum, x)				\
(अणु								\
	रेजिस्टर द्विगुन __f__ यंत्र ("f"#regnum);			\
	यंत्र अस्थिर ("ldf.fill %0=[%1]" :"=f"(__f__): "r"(x));	\
पूर्ण)

#घोषणा ia64_st4_rel_nta(m, val)					\
(अणु									\
	यंत्र अस्थिर ("st4.rel.nta [%0] = %1\n\t" :: "r"(m), "r"(val));	\
पूर्ण)

#घोषणा ia64_stfs(x, regnum)						\
(अणु									\
	रेजिस्टर द्विगुन __f__ यंत्र ("f"#regnum);				\
	यंत्र अस्थिर ("stfs [%0]=%1" :: "r"(x), "f"(__f__) : "memory");	\
पूर्ण)

#घोषणा ia64_stfd(x, regnum)						\
(अणु									\
	रेजिस्टर द्विगुन __f__ यंत्र ("f"#regnum);				\
	यंत्र अस्थिर ("stfd [%0]=%1" :: "r"(x), "f"(__f__) : "memory");	\
पूर्ण)

#घोषणा ia64_stfe(x, regnum)						\
(अणु									\
	रेजिस्टर द्विगुन __f__ यंत्र ("f"#regnum);				\
	यंत्र अस्थिर ("stfe [%0]=%1" :: "r"(x), "f"(__f__) : "memory");	\
पूर्ण)

#घोषणा ia64_stf8(x, regnum)						\
(अणु									\
	रेजिस्टर द्विगुन __f__ यंत्र ("f"#regnum);				\
	यंत्र अस्थिर ("stf8 [%0]=%1" :: "r"(x), "f"(__f__) : "memory");	\
पूर्ण)

#घोषणा ia64_stf_spill(x, regnum)						\
(अणु										\
	रेजिस्टर द्विगुन __f__ यंत्र ("f"#regnum);					\
	यंत्र अस्थिर ("stf.spill [%0]=%1" :: "r"(x), "f"(__f__) : "memory");	\
पूर्ण)

#घोषणा ia64_fetchadd4_acq(p, inc)						\
(अणु										\
										\
	__u64 ia64_पूर्णांकri_res;							\
	यंत्र अस्थिर ("fetchadd4.acq %0=[%1],%2"				\
				: "=r"(ia64_पूर्णांकri_res) : "r"(p), "i" (inc)	\
				: "memory");					\
										\
	ia64_पूर्णांकri_res;								\
पूर्ण)

#घोषणा ia64_fetchadd4_rel(p, inc)						\
(अणु										\
	__u64 ia64_पूर्णांकri_res;							\
	यंत्र अस्थिर ("fetchadd4.rel %0=[%1],%2"				\
				: "=r"(ia64_पूर्णांकri_res) : "r"(p), "i" (inc)	\
				: "memory");					\
										\
	ia64_पूर्णांकri_res;								\
पूर्ण)

#घोषणा ia64_fetchadd8_acq(p, inc)						\
(अणु										\
										\
	__u64 ia64_पूर्णांकri_res;							\
	यंत्र अस्थिर ("fetchadd8.acq %0=[%1],%2"				\
				: "=r"(ia64_पूर्णांकri_res) : "r"(p), "i" (inc)	\
				: "memory");					\
										\
	ia64_पूर्णांकri_res;								\
पूर्ण)

#घोषणा ia64_fetchadd8_rel(p, inc)						\
(अणु										\
	__u64 ia64_पूर्णांकri_res;							\
	यंत्र अस्थिर ("fetchadd8.rel %0=[%1],%2"				\
				: "=r"(ia64_पूर्णांकri_res) : "r"(p), "i" (inc)	\
				: "memory");					\
										\
	ia64_पूर्णांकri_res;								\
पूर्ण)

#घोषणा ia64_xchg1(ptr,x)							\
(अणु										\
	__u64 ia64_पूर्णांकri_res;							\
	यंत्र अस्थिर ("xchg1 %0=[%1],%2"					\
		      : "=r" (ia64_पूर्णांकri_res) : "r" (ptr), "r" (x) : "memory");	\
	ia64_पूर्णांकri_res;								\
पूर्ण)

#घोषणा ia64_xchg2(ptr,x)						\
(अणु									\
	__u64 ia64_पूर्णांकri_res;						\
	यंत्र अस्थिर ("xchg2 %0=[%1],%2" : "=r" (ia64_पूर्णांकri_res)	\
		      : "r" (ptr), "r" (x) : "memory");			\
	ia64_पूर्णांकri_res;							\
पूर्ण)

#घोषणा ia64_xchg4(ptr,x)						\
(अणु									\
	__u64 ia64_पूर्णांकri_res;						\
	यंत्र अस्थिर ("xchg4 %0=[%1],%2" : "=r" (ia64_पूर्णांकri_res)	\
		      : "r" (ptr), "r" (x) : "memory");			\
	ia64_पूर्णांकri_res;							\
पूर्ण)

#घोषणा ia64_xchg8(ptr,x)						\
(अणु									\
	__u64 ia64_पूर्णांकri_res;						\
	यंत्र अस्थिर ("xchg8 %0=[%1],%2" : "=r" (ia64_पूर्णांकri_res)	\
		      : "r" (ptr), "r" (x) : "memory");			\
	ia64_पूर्णांकri_res;							\
पूर्ण)

#घोषणा ia64_cmpxchg1_acq(ptr, new, old)						\
(अणु											\
	__u64 ia64_पूर्णांकri_res;								\
	यंत्र अस्थिर ("mov ar.ccv=%0;;" :: "rO"(old));					\
	यंत्र अस्थिर ("cmpxchg1.acq %0=[%1],%2,ar.ccv":					\
			      "=r"(ia64_पूर्णांकri_res) : "r"(ptr), "r"(new) : "memory");	\
	ia64_पूर्णांकri_res;									\
पूर्ण)

#घोषणा ia64_cmpxchg1_rel(ptr, new, old)						\
(अणु											\
	__u64 ia64_पूर्णांकri_res;								\
	यंत्र अस्थिर ("mov ar.ccv=%0;;" :: "rO"(old));					\
	यंत्र अस्थिर ("cmpxchg1.rel %0=[%1],%2,ar.ccv":					\
			      "=r"(ia64_पूर्णांकri_res) : "r"(ptr), "r"(new) : "memory");	\
	ia64_पूर्णांकri_res;									\
पूर्ण)

#घोषणा ia64_cmpxchg2_acq(ptr, new, old)						\
(अणु											\
	__u64 ia64_पूर्णांकri_res;								\
	यंत्र अस्थिर ("mov ar.ccv=%0;;" :: "rO"(old));					\
	यंत्र अस्थिर ("cmpxchg2.acq %0=[%1],%2,ar.ccv":					\
			      "=r"(ia64_पूर्णांकri_res) : "r"(ptr), "r"(new) : "memory");	\
	ia64_पूर्णांकri_res;									\
पूर्ण)

#घोषणा ia64_cmpxchg2_rel(ptr, new, old)						\
(अणु											\
	__u64 ia64_पूर्णांकri_res;								\
	यंत्र अस्थिर ("mov ar.ccv=%0;;" :: "rO"(old));					\
											\
	यंत्र अस्थिर ("cmpxchg2.rel %0=[%1],%2,ar.ccv":					\
			      "=r"(ia64_पूर्णांकri_res) : "r"(ptr), "r"(new) : "memory");	\
	ia64_पूर्णांकri_res;									\
पूर्ण)

#घोषणा ia64_cmpxchg4_acq(ptr, new, old)						\
(अणु											\
	__u64 ia64_पूर्णांकri_res;								\
	यंत्र अस्थिर ("mov ar.ccv=%0;;" :: "rO"(old));					\
	यंत्र अस्थिर ("cmpxchg4.acq %0=[%1],%2,ar.ccv":					\
			      "=r"(ia64_पूर्णांकri_res) : "r"(ptr), "r"(new) : "memory");	\
	ia64_पूर्णांकri_res;									\
पूर्ण)

#घोषणा ia64_cmpxchg4_rel(ptr, new, old)						\
(अणु											\
	__u64 ia64_पूर्णांकri_res;								\
	यंत्र अस्थिर ("mov ar.ccv=%0;;" :: "rO"(old));					\
	यंत्र अस्थिर ("cmpxchg4.rel %0=[%1],%2,ar.ccv":					\
			      "=r"(ia64_पूर्णांकri_res) : "r"(ptr), "r"(new) : "memory");	\
	ia64_पूर्णांकri_res;									\
पूर्ण)

#घोषणा ia64_cmpxchg8_acq(ptr, new, old)						\
(अणु											\
	__u64 ia64_पूर्णांकri_res;								\
	यंत्र अस्थिर ("mov ar.ccv=%0;;" :: "rO"(old));					\
	यंत्र अस्थिर ("cmpxchg8.acq %0=[%1],%2,ar.ccv":					\
			      "=r"(ia64_पूर्णांकri_res) : "r"(ptr), "r"(new) : "memory");	\
	ia64_पूर्णांकri_res;									\
पूर्ण)

#घोषणा ia64_cmpxchg8_rel(ptr, new, old)						\
(अणु											\
	__u64 ia64_पूर्णांकri_res;								\
	यंत्र अस्थिर ("mov ar.ccv=%0;;" :: "rO"(old));					\
											\
	यंत्र अस्थिर ("cmpxchg8.rel %0=[%1],%2,ar.ccv":					\
			      "=r"(ia64_पूर्णांकri_res) : "r"(ptr), "r"(new) : "memory");	\
	ia64_पूर्णांकri_res;									\
पूर्ण)

#घोषणा ia64_mf()	यंत्र अस्थिर ("mf" ::: "memory")
#घोषणा ia64_mfa()	यंत्र अस्थिर ("mf.a" ::: "memory")

#घोषणा ia64_invala() यंत्र अस्थिर ("invala" ::: "memory")

#घोषणा ia64_thash(addr)							\
(अणु										\
	अचिन्हित दीर्घ ia64_पूर्णांकri_res;						\
	यंत्र अस्थिर ("thash %0=%1" : "=r"(ia64_पूर्णांकri_res) : "r" (addr));	\
	ia64_पूर्णांकri_res;								\
पूर्ण)

#घोषणा ia64_srlz_i()	यंत्र अस्थिर (";; srlz.i ;;" ::: "memory")
#घोषणा ia64_srlz_d()	यंत्र अस्थिर (";; srlz.d" ::: "memory");

#अगर_घोषित HAVE_SERIALIZE_सूचीECTIVE
# define ia64_dv_serialize_data()		यंत्र अस्थिर (".serialize.data");
# define ia64_dv_serialize_inकाष्ठाion()	यंत्र अस्थिर (".serialize.instruction");
#अन्यथा
# define ia64_dv_serialize_data()
# define ia64_dv_serialize_inकाष्ठाion()
#पूर्ण_अगर

#घोषणा ia64_nop(x)	यंत्र अस्थिर ("nop %0"::"i"(x));

#घोषणा ia64_itci(addr)	यंत्र अस्थिर ("itc.i %0;;" :: "r"(addr) : "memory")

#घोषणा ia64_itcd(addr)	यंत्र अस्थिर ("itc.d %0;;" :: "r"(addr) : "memory")


#घोषणा ia64_itri(trnum, addr) यंत्र अस्थिर ("itr.i itr[%0]=%1"				\
					     :: "r"(trnum), "r"(addr) : "memory")

#घोषणा ia64_itrd(trnum, addr) यंत्र अस्थिर ("itr.d dtr[%0]=%1"				\
					     :: "r"(trnum), "r"(addr) : "memory")

#घोषणा ia64_tpa(addr)								\
(अणु										\
	अचिन्हित दीर्घ ia64_pa;							\
	यंत्र अस्थिर ("tpa %0 = %1" : "=r"(ia64_pa) : "r"(addr) : "memory");	\
	ia64_pa;								\
पूर्ण)

#घोषणा __ia64_set_dbr(index, val)						\
	यंत्र अस्थिर ("mov dbr[%0]=%1" :: "r"(index), "r"(val) : "memory")

#घोषणा ia64_set_ibr(index, val)						\
	यंत्र अस्थिर ("mov ibr[%0]=%1" :: "r"(index), "r"(val) : "memory")

#घोषणा ia64_set_pkr(index, val)						\
	यंत्र अस्थिर ("mov pkr[%0]=%1" :: "r"(index), "r"(val) : "memory")

#घोषणा ia64_set_pmc(index, val)						\
	यंत्र अस्थिर ("mov pmc[%0]=%1" :: "r"(index), "r"(val) : "memory")

#घोषणा ia64_set_pmd(index, val)						\
	यंत्र अस्थिर ("mov pmd[%0]=%1" :: "r"(index), "r"(val) : "memory")

#घोषणा ia64_set_rr(index, val)							\
	यंत्र अस्थिर ("mov rr[%0]=%1" :: "r"(index), "r"(val) : "memory");

#घोषणा ia64_get_cpuid(index)								\
(अणु											\
	अचिन्हित दीर्घ ia64_पूर्णांकri_res;							\
	यंत्र अस्थिर ("mov %0=cpuid[%r1]" : "=r"(ia64_पूर्णांकri_res) : "rO"(index));	\
	ia64_पूर्णांकri_res;									\
पूर्ण)

#घोषणा __ia64_get_dbr(index)							\
(अणु										\
	अचिन्हित दीर्घ ia64_पूर्णांकri_res;						\
	यंत्र अस्थिर ("mov %0=dbr[%1]" : "=r"(ia64_पूर्णांकri_res) : "r"(index));	\
	ia64_पूर्णांकri_res;								\
पूर्ण)

#घोषणा ia64_get_ibr(index)							\
(अणु										\
	अचिन्हित दीर्घ ia64_पूर्णांकri_res;						\
	यंत्र अस्थिर ("mov %0=ibr[%1]" : "=r"(ia64_पूर्णांकri_res) : "r"(index));	\
	ia64_पूर्णांकri_res;								\
पूर्ण)

#घोषणा ia64_get_pkr(index)							\
(अणु										\
	अचिन्हित दीर्घ ia64_पूर्णांकri_res;						\
	यंत्र अस्थिर ("mov %0=pkr[%1]" : "=r"(ia64_पूर्णांकri_res) : "r"(index));	\
	ia64_पूर्णांकri_res;								\
पूर्ण)

#घोषणा ia64_get_pmc(index)							\
(अणु										\
	अचिन्हित दीर्घ ia64_पूर्णांकri_res;						\
	यंत्र अस्थिर ("mov %0=pmc[%1]" : "=r"(ia64_पूर्णांकri_res) : "r"(index));	\
	ia64_पूर्णांकri_res;								\
पूर्ण)


#घोषणा ia64_get_pmd(index)							\
(अणु										\
	अचिन्हित दीर्घ ia64_पूर्णांकri_res;						\
	यंत्र अस्थिर ("mov %0=pmd[%1]" : "=r"(ia64_पूर्णांकri_res) : "r"(index));	\
	ia64_पूर्णांकri_res;								\
पूर्ण)

#घोषणा ia64_get_rr(index)							\
(अणु										\
	अचिन्हित दीर्घ ia64_पूर्णांकri_res;						\
	यंत्र अस्थिर ("mov %0=rr[%1]" : "=r"(ia64_पूर्णांकri_res) : "r" (index));	\
	ia64_पूर्णांकri_res;								\
पूर्ण)

#घोषणा ia64_fc(addr)	यंत्र अस्थिर ("fc %0" :: "r"(addr) : "memory")


#घोषणा ia64_sync_i()	यंत्र अस्थिर (";; sync.i" ::: "memory")

#घोषणा ia64_ssm(mask)	यंत्र अस्थिर ("ssm %0":: "i"((mask)) : "memory")
#घोषणा ia64_rsm(mask)	यंत्र अस्थिर ("rsm %0":: "i"((mask)) : "memory")
#घोषणा ia64_sum(mask)	यंत्र अस्थिर ("sum %0":: "i"((mask)) : "memory")
#घोषणा ia64_rum(mask)	यंत्र अस्थिर ("rum %0":: "i"((mask)) : "memory")

#घोषणा ia64_ptce(addr)	यंत्र अस्थिर ("ptc.e %0" :: "r"(addr))

#घोषणा ia64_ptcga(addr, size)							\
करो अणु										\
	यंत्र अस्थिर ("ptc.ga %0,%1" :: "r"(addr), "r"(size) : "memory");	\
	ia64_dv_serialize_data();						\
पूर्ण जबतक (0)

#घोषणा ia64_ptcl(addr, size)							\
करो अणु										\
	यंत्र अस्थिर ("ptc.l %0,%1" :: "r"(addr), "r"(size) : "memory");	\
	ia64_dv_serialize_data();						\
पूर्ण जबतक (0)

#घोषणा ia64_ptri(addr, size)						\
	यंत्र अस्थिर ("ptr.i %0,%1" :: "r"(addr), "r"(size) : "memory")

#घोषणा ia64_ptrd(addr, size)						\
	यंत्र अस्थिर ("ptr.d %0,%1" :: "r"(addr), "r"(size) : "memory")

#घोषणा ia64_ttag(addr)							\
(अणु									  \
	__u64 ia64_पूर्णांकri_res;						   \
	यंत्र अस्थिर ("ttag %0=%1" : "=r"(ia64_पूर्णांकri_res) : "r" (addr));   \
	ia64_पूर्णांकri_res;							 \
पूर्ण)


/* Values क्रम lfhपूर्णांक in ia64_lfetch and ia64_lfetch_fault */

#घोषणा ia64_lfhपूर्णांक_none   0
#घोषणा ia64_lfhपूर्णांक_nt1    1
#घोषणा ia64_lfhपूर्णांक_nt2    2
#घोषणा ia64_lfhपूर्णांक_nta    3

#घोषणा ia64_lfetch(lfhपूर्णांक, y)					\
(अणु								\
        चयन (lfhपूर्णांक) अणु					\
        हाल ia64_lfhपूर्णांक_none:					\
                यंत्र अस्थिर ("lfetch [%0]" : : "r"(y));	\
                अवरोध;						\
        हाल ia64_lfhपूर्णांक_nt1:					\
                यंत्र अस्थिर ("lfetch.nt1 [%0]" : : "r"(y));	\
                अवरोध;						\
        हाल ia64_lfhपूर्णांक_nt2:					\
                यंत्र अस्थिर ("lfetch.nt2 [%0]" : : "r"(y));	\
                अवरोध;						\
        हाल ia64_lfhपूर्णांक_nta:					\
                यंत्र अस्थिर ("lfetch.nta [%0]" : : "r"(y));	\
                अवरोध;						\
        पूर्ण							\
पूर्ण)

#घोषणा ia64_lfetch_excl(lfhपूर्णांक, y)					\
(अणु									\
        चयन (lfhपूर्णांक) अणु						\
        हाल ia64_lfhपूर्णांक_none:						\
                यंत्र अस्थिर ("lfetch.excl [%0]" :: "r"(y));		\
                अवरोध;							\
        हाल ia64_lfhपूर्णांक_nt1:						\
                यंत्र अस्थिर ("lfetch.excl.nt1 [%0]" :: "r"(y));	\
                अवरोध;							\
        हाल ia64_lfhपूर्णांक_nt2:						\
                यंत्र अस्थिर ("lfetch.excl.nt2 [%0]" :: "r"(y));	\
                अवरोध;							\
        हाल ia64_lfhपूर्णांक_nta:						\
                यंत्र अस्थिर ("lfetch.excl.nta [%0]" :: "r"(y));	\
                अवरोध;							\
        पूर्ण								\
पूर्ण)

#घोषणा ia64_lfetch_fault(lfhपूर्णांक, y)					\
(अणु									\
        चयन (lfhपूर्णांक) अणु						\
        हाल ia64_lfhपूर्णांक_none:						\
                यंत्र अस्थिर ("lfetch.fault [%0]" : : "r"(y));		\
                अवरोध;							\
        हाल ia64_lfhपूर्णांक_nt1:						\
                यंत्र अस्थिर ("lfetch.fault.nt1 [%0]" : : "r"(y));	\
                अवरोध;							\
        हाल ia64_lfhपूर्णांक_nt2:						\
                यंत्र अस्थिर ("lfetch.fault.nt2 [%0]" : : "r"(y));	\
                अवरोध;							\
        हाल ia64_lfhपूर्णांक_nta:						\
                यंत्र अस्थिर ("lfetch.fault.nta [%0]" : : "r"(y));	\
                अवरोध;							\
        पूर्ण								\
पूर्ण)

#घोषणा ia64_lfetch_fault_excl(lfhपूर्णांक, y)				\
(अणु									\
        चयन (lfhपूर्णांक) अणु						\
        हाल ia64_lfhपूर्णांक_none:						\
                यंत्र अस्थिर ("lfetch.fault.excl [%0]" :: "r"(y));	\
                अवरोध;							\
        हाल ia64_lfhपूर्णांक_nt1:						\
                यंत्र अस्थिर ("lfetch.fault.excl.nt1 [%0]" :: "r"(y));	\
                अवरोध;							\
        हाल ia64_lfhपूर्णांक_nt2:						\
                यंत्र अस्थिर ("lfetch.fault.excl.nt2 [%0]" :: "r"(y));	\
                अवरोध;							\
        हाल ia64_lfhपूर्णांक_nta:						\
                यंत्र अस्थिर ("lfetch.fault.excl.nta [%0]" :: "r"(y));	\
                अवरोध;							\
        पूर्ण								\
पूर्ण)

#घोषणा ia64_पूर्णांकrin_local_irq_restore(x)			\
करो अणु								\
	यंत्र अस्थिर (";;   cmp.ne p6,p7=%0,r0;;"		\
		      "(p6) ssm psr.i;"				\
		      "(p7) rsm psr.i;;"			\
		      "(p6) srlz.d"				\
		      :: "r"((x)) : "p6", "p7", "memory");	\
पूर्ण जबतक (0)

#पूर्ण_अगर /* _UAPI_ASM_IA64_GCC_INTRIN_H */
