<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Red Hat, Inc.
 * Author: Michael S. Tsirkin <mst@redhat.com>
 *
 * Common macros and functions क्रम ring benchmarking.
 */
#अगर_अघोषित MAIN_H
#घोषणा MAIN_H

#समावेश <stdbool.h>

बाह्य पूर्णांक param;

बाह्य bool करो_निकास;

#अगर defined(__x86_64__) || defined(__i386__)
#समावेश "x86intrin.h"

अटल अंतरभूत व्योम रुको_cycles(अचिन्हित दीर्घ दीर्घ cycles)
अणु
	अचिन्हित दीर्घ दीर्घ t;

	t = __rdtsc();
	जबतक (__rdtsc() - t < cycles) अणुपूर्ण
पूर्ण

#घोषणा VMEXIT_CYCLES 500
#घोषणा VMENTRY_CYCLES 500

#या_अगर defined(__s390x__)
अटल अंतरभूत व्योम रुको_cycles(अचिन्हित दीर्घ दीर्घ cycles)
अणु
	यंत्र अस्थिर("0: brctg %0,0b" : : "d" (cycles));
पूर्ण

/* tweak me */
#घोषणा VMEXIT_CYCLES 200
#घोषणा VMENTRY_CYCLES 200

#अन्यथा
अटल अंतरभूत व्योम रुको_cycles(अचिन्हित दीर्घ दीर्घ cycles)
अणु
	_Exit(5);
पूर्ण
#घोषणा VMEXIT_CYCLES 0
#घोषणा VMENTRY_CYCLES 0
#पूर्ण_अगर

अटल अंतरभूत व्योम vmनिकास(व्योम)
अणु
	अगर (!करो_निकास)
		वापस;
	
	रुको_cycles(VMEXIT_CYCLES);
पूर्ण
अटल अंतरभूत व्योम vmentry(व्योम)
अणु
	अगर (!करो_निकास)
		वापस;
	
	रुको_cycles(VMENTRY_CYCLES);
पूर्ण

/* implemented by ring */
व्योम alloc_ring(व्योम);
/* guest side */
पूर्णांक add_inbuf(अचिन्हित, व्योम *, व्योम *);
व्योम *get_buf(अचिन्हित *, व्योम **);
व्योम disable_call();
bool used_empty();
bool enable_call();
व्योम kick_available();
/* host side */
व्योम disable_kick();
bool avail_empty();
bool enable_kick();
bool use_buf(अचिन्हित *, व्योम **);
व्योम call_used();

/* implemented by मुख्य */
बाह्य bool करो_sleep;
व्योम kick(व्योम);
व्योम रुको_क्रम_kick(व्योम);
व्योम call(व्योम);
व्योम रुको_क्रम_call(व्योम);

बाह्य अचिन्हित ring_size;

/* Compiler barrier - similar to what Linux uses */
#घोषणा barrier() यंत्र अस्थिर("" ::: "memory")

/* Is there a portable way to करो this? */
#अगर defined(__x86_64__) || defined(__i386__)
#घोषणा cpu_relax() यंत्र ("rep; nop" ::: "memory")
#या_अगर defined(__s390x__)
#घोषणा cpu_relax() barrier()
#अन्यथा
#घोषणा cpu_relax() निश्चित(0)
#पूर्ण_अगर

बाह्य bool करो_relax;

अटल अंतरभूत व्योम busy_रुको(व्योम)
अणु
	अगर (करो_relax)
		cpu_relax();
	अन्यथा
		/* prevent compiler from removing busy loops */
		barrier();
पूर्ण 

#अगर defined(__x86_64__) || defined(__i386__)
#घोषणा smp_mb()     यंत्र अस्थिर("lock; addl $0,-132(%%rsp)" ::: "memory", "cc")
#अन्यथा
/*
 * Not using __ATOMIC_SEQ_CST since gcc करोcs say they are only synchronized
 * with other __ATOMIC_SEQ_CST calls.
 */
#घोषणा smp_mb() __sync_synchronize()
#पूर्ण_अगर

/*
 * This abuses the atomic builtins क्रम thपढ़ो fences, and
 * adds a compiler barrier.
 */
#घोषणा smp_release() करो अणु \
    barrier(); \
    __atomic_thपढ़ो_fence(__ATOMIC_RELEASE); \
पूर्ण जबतक (0)

#घोषणा smp_acquire() करो अणु \
    __atomic_thपढ़ो_fence(__ATOMIC_ACQUIRE); \
    barrier(); \
पूर्ण जबतक (0)

#अगर defined(__i386__) || defined(__x86_64__) || defined(__s390x__)
#घोषणा smp_wmb() barrier()
#अन्यथा
#घोषणा smp_wmb() smp_release()
#पूर्ण_अगर

#अगर_घोषित __alpha__
#घोषणा smp_पढ़ो_barrier_depends() smp_acquire()
#अन्यथा
#घोषणा smp_पढ़ो_barrier_depends() करो अणुपूर्ण जबतक(0)
#पूर्ण_अगर

अटल __always_अंतरभूत
व्योम __पढ़ो_once_size(स्थिर अस्थिर व्योम *p, व्योम *res, पूर्णांक size)
अणु
        चयन (size) अणु                                                 \
        हाल 1: *(अचिन्हित अक्षर *)res = *(अस्थिर अचिन्हित अक्षर *)p; अवरोध;              \
        हाल 2: *(अचिन्हित लघु *)res = *(अस्थिर अचिन्हित लघु *)p; अवरोध;            \
        हाल 4: *(अचिन्हित पूर्णांक *)res = *(अस्थिर अचिन्हित पूर्णांक *)p; अवरोध;            \
        हाल 8: *(अचिन्हित दीर्घ दीर्घ *)res = *(अस्थिर अचिन्हित दीर्घ दीर्घ *)p; अवरोध;            \
        शेष:                                                        \
                barrier();                                              \
                __builtin_स_नकल((व्योम *)res, (स्थिर व्योम *)p, size);   \
                barrier();                                              \
        पूर्ण                                                               \
पूर्ण

अटल __always_अंतरभूत व्योम __ग_लिखो_once_size(अस्थिर व्योम *p, व्योम *res, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1: *(अस्थिर अचिन्हित अक्षर *)p = *(अचिन्हित अक्षर *)res; अवरोध;
	हाल 2: *(अस्थिर अचिन्हित लघु *)p = *(अचिन्हित लघु *)res; अवरोध;
	हाल 4: *(अस्थिर अचिन्हित पूर्णांक *)p = *(अचिन्हित पूर्णांक *)res; अवरोध;
	हाल 8: *(अस्थिर अचिन्हित दीर्घ दीर्घ *)p = *(अचिन्हित दीर्घ दीर्घ *)res; अवरोध;
	शेष:
		barrier();
		__builtin_स_नकल((व्योम *)p, (स्थिर व्योम *)res, size);
		barrier();
	पूर्ण
पूर्ण

#घोषणा READ_ONCE(x) \
(अणु									\
	जोड़ अणु typeof(x) __val; अक्षर __c[1]; पूर्ण __u;			\
	__पढ़ो_once_size(&(x), __u.__c, माप(x));		\
	smp_पढ़ो_barrier_depends(); /* Enक्रमce dependency ordering from x */ \
	__u.__val;							\
पूर्ण)

#घोषणा WRITE_ONCE(x, val) \
(अणु							\
	जोड़ अणु typeof(x) __val; अक्षर __c[1]; पूर्ण __u =	\
		अणु .__val = (typeof(x)) (val) पूर्ण; \
	__ग_लिखो_once_size(&(x), __u.__c, माप(x));	\
	__u.__val;					\
पूर्ण)

#पूर्ण_अगर
