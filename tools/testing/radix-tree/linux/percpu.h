<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा DECLARE_PER_CPU(type, val) बाह्य type val
#घोषणा DEFINE_PER_CPU(type, val) type val

#घोषणा __get_cpu_var(var)	var
#घोषणा this_cpu_ptr(var)	var
#घोषणा this_cpu_पढ़ो(var)	var
#घोषणा this_cpu_xchg(var, val)		uatomic_xchg(&var, val)
#घोषणा this_cpu_cmpxchg(var, old, new)	uatomic_cmpxchg(&var, old, new)
#घोषणा per_cpu_ptr(ptr, cpu)   (अणु (व्योम)(cpu); (ptr); पूर्ण)
#घोषणा per_cpu(var, cpu)	(*per_cpu_ptr(&(var), cpu))
