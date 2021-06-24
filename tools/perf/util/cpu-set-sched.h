<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
// Definitions taken from glibc क्रम use with older प्रणालीs, same licensing.
#अगर_अघोषित _CPU_SET_SCHED_PERF_H
#घोषणा _CPU_SET_SCHED_PERF_H

#समावेश <features.h>
#समावेश <sched.h>

#अगर_अघोषित CPU_EQUAL
#अगर_अघोषित __CPU_EQUAL_S
#अगर __GNUC_PREREQ (2, 91)
# define __CPU_EQUAL_S(setsize, cpusetp1, cpusetp2) \
  (__builtin_स_भेद (cpusetp1, cpusetp2, setsize) == 0)
#अन्यथा
# define __CPU_EQUAL_S(setsize, cpusetp1, cpusetp2) \
  (__extension__							      \
   (अणु स्थिर __cpu_mask *__arr1 = (cpusetp1)->__bits;			      \
      स्थिर __cpu_mask *__arr2 = (cpusetp2)->__bits;			      \
      माप_प्रकार __imax = (setsize) / माप (__cpu_mask);			      \
      माप_प्रकार __i;							      \
      क्रम (__i = 0; __i < __imax; ++__i)				      \
	अगर (__arr1[__i] != __arr2[__i])					      \
	  अवरोध;							      \
      __i == __imax; पूर्ण))
#पूर्ण_अगर
#पूर्ण_अगर // __CPU_EQUAL_S

#घोषणा CPU_EQUAL(cpusetp1, cpusetp2) \
  __CPU_EQUAL_S (माप (cpu_set_t), cpusetp1, cpusetp2)
#पूर्ण_अगर // CPU_EQUAL

#अगर_अघोषित CPU_OR
#अगर_अघोषित __CPU_OP_S
#घोषणा __CPU_OP_S(setsize, destset, srcset1, srcset2, op) \
  (__extension__							      \
   (अणु cpu_set_t *__dest = (destset);					      \
      स्थिर __cpu_mask *__arr1 = (srcset1)->__bits;			      \
      स्थिर __cpu_mask *__arr2 = (srcset2)->__bits;			      \
      माप_प्रकार __imax = (setsize) / माप (__cpu_mask);			      \
      माप_प्रकार __i;							      \
      क्रम (__i = 0; __i < __imax; ++__i)				      \
	((__cpu_mask *) __dest->__bits)[__i] = __arr1[__i] op __arr2[__i];    \
      __dest; पूर्ण))
#पूर्ण_अगर // __CPU_OP_S

#घोषणा CPU_OR(destset, srcset1, srcset2) \
  __CPU_OP_S (माप (cpu_set_t), destset, srcset1, srcset2, |)
#पूर्ण_अगर // CPU_OR

#पूर्ण_अगर // _CPU_SET_SCHED_PERF_H
