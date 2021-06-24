<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 OR MIT */
/*
 * rseq-skip.h
 *
 * (C) Copyright 2017-2018 - Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 */

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_storev(पूर्णांकptr_t *v, पूर्णांकptr_t expect, पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpnev_storeoffp_load(पूर्णांकptr_t *v, पूर्णांकptr_t expectnot,
			       off_t voffp, पूर्णांकptr_t *load, पूर्णांक cpu)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_addv(पूर्णांकptr_t *v, पूर्णांकptr_t count, पूर्णांक cpu)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_trystorev_storev(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
				 पूर्णांकptr_t *v2, पूर्णांकptr_t newv2,
				 पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_trystorev_storev_release(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
					 पूर्णांकptr_t *v2, पूर्णांकptr_t newv2,
					 पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_cmpeqv_storev(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
			      पूर्णांकptr_t *v2, पूर्णांकptr_t expect2,
			      पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_tryस_नकल_storev(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
				 व्योम *dst, व्योम *src, माप_प्रकार len,
				 पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_tryस_नकल_storev_release(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
					 व्योम *dst, व्योम *src, माप_प्रकार len,
					 पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	वापस -1;
पूर्ण
