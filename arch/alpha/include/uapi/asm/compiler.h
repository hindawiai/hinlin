<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__ALPHA_COMPILER_H
#घोषणा _UAPI__ALPHA_COMPILER_H

/* 
 * Herein are macros we use when describing various patterns we want to GCC.
 * In all हालs we can get better schedules out of the compiler अगर we hide
 * as little as possible inside अंतरभूत assembly.  However, we want to be
 * able to know what we'll get out beक्रमe giving up अंतरभूत assembly.  Thus
 * these tests and macros.
 */

#अगर __GNUC__ == 3 && __GNUC_MINOR__ >= 4 || __GNUC__ > 3
# define __kernel_insbl(val, shअगरt)	__builtin_alpha_insbl(val, shअगरt)
# define __kernel_inswl(val, shअगरt)	__builtin_alpha_inswl(val, shअगरt)
# define __kernel_insql(val, shअगरt)	__builtin_alpha_insql(val, shअगरt)
# define __kernel_inslh(val, shअगरt)	__builtin_alpha_inslh(val, shअगरt)
# define __kernel_extbl(val, shअगरt)	__builtin_alpha_extbl(val, shअगरt)
# define __kernel_extwl(val, shअगरt)	__builtin_alpha_extwl(val, shअगरt)
# define __kernel_cmpbge(a, b)		__builtin_alpha_cmpbge(a, b)
#अन्यथा
# define __kernel_insbl(val, shअगरt)					\
  (अणु अचिन्हित दीर्घ __kir;						\
     __यंत्र__("insbl %2,%1,%0" : "=r"(__kir) : "rI"(shअगरt), "r"(val));	\
     __kir; पूर्ण)
# define __kernel_inswl(val, shअगरt)					\
  (अणु अचिन्हित दीर्घ __kir;						\
     __यंत्र__("inswl %2,%1,%0" : "=r"(__kir) : "rI"(shअगरt), "r"(val));	\
     __kir; पूर्ण)
# define __kernel_insql(val, shअगरt)					\
  (अणु अचिन्हित दीर्घ __kir;						\
     __यंत्र__("insql %2,%1,%0" : "=r"(__kir) : "rI"(shअगरt), "r"(val));	\
     __kir; पूर्ण)
# define __kernel_inslh(val, shअगरt)					\
  (अणु अचिन्हित दीर्घ __kir;						\
     __यंत्र__("inslh %2,%1,%0" : "=r"(__kir) : "rI"(shअगरt), "r"(val));	\
     __kir; पूर्ण)
# define __kernel_extbl(val, shअगरt)					\
  (अणु अचिन्हित दीर्घ __kir;						\
     __यंत्र__("extbl %2,%1,%0" : "=r"(__kir) : "rI"(shअगरt), "r"(val));	\
     __kir; पूर्ण)
# define __kernel_extwl(val, shअगरt)					\
  (अणु अचिन्हित दीर्घ __kir;						\
     __यंत्र__("extwl %2,%1,%0" : "=r"(__kir) : "rI"(shअगरt), "r"(val));	\
     __kir; पूर्ण)
# define __kernel_cmpbge(a, b)						\
  (अणु अचिन्हित दीर्घ __kir;						\
     __यंत्र__("cmpbge %r2,%1,%0" : "=r"(__kir) : "rI"(b), "rJ"(a));	\
     __kir; पूर्ण)
#पूर्ण_अगर

#अगर_घोषित __alpha_cix__
# अगर __GNUC__ == 3 && __GNUC_MINOR__ >= 4 || __GNUC__ > 3
#  define __kernel_cttz(x)		__builtin_ctzl(x)
#  define __kernel_ctlz(x)		__builtin_clzl(x)
#  define __kernel_ctpop(x)		__builtin_popcountl(x)
# अन्यथा
#  define __kernel_cttz(x)						\
   (अणु अचिन्हित दीर्घ __kir;						\
      __यंत्र__("cttz %1,%0" : "=r"(__kir) : "r"(x));			\
      __kir; पूर्ण)
#  define __kernel_ctlz(x)						\
   (अणु अचिन्हित दीर्घ __kir;						\
      __यंत्र__("ctlz %1,%0" : "=r"(__kir) : "r"(x));			\
      __kir; पूर्ण)
#  define __kernel_ctpop(x)						\
   (अणु अचिन्हित दीर्घ __kir;						\
      __यंत्र__("ctpop %1,%0" : "=r"(__kir) : "r"(x));			\
      __kir; पूर्ण)
# endअगर
#अन्यथा
# define __kernel_cttz(x)						\
  (अणु अचिन्हित दीर्घ __kir;						\
     __यंत्र__(".arch ev67; cttz %1,%0" : "=r"(__kir) : "r"(x));		\
     __kir; पूर्ण)
# define __kernel_ctlz(x)						\
  (अणु अचिन्हित दीर्घ __kir;						\
     __यंत्र__(".arch ev67; ctlz %1,%0" : "=r"(__kir) : "r"(x));		\
     __kir; पूर्ण)
# define __kernel_ctpop(x)						\
  (अणु अचिन्हित दीर्घ __kir;						\
     __यंत्र__(".arch ev67; ctpop %1,%0" : "=r"(__kir) : "r"(x));		\
     __kir; पूर्ण)
#पूर्ण_अगर


/* 
 * Beginning with EGCS 1.1, GCC defines __alpha_bwx__ when the BWX 
 * extension is enabled.  Previous versions did not define anything
 * we could test during compilation -- too bad, so sad.
 */

#अगर defined(__alpha_bwx__)
#घोषणा __kernel_ldbu(mem)	(mem)
#घोषणा __kernel_ldwu(mem)	(mem)
#घोषणा __kernel_stb(val,mem)	((mem) = (val))
#घोषणा __kernel_stw(val,mem)	((mem) = (val))
#अन्यथा
#घोषणा __kernel_ldbu(mem)				\
  (अणु अचिन्हित अक्षर __kir;				\
     __यंत्र__(".arch ev56;				\
	      ldbu %0,%1" : "=r"(__kir) : "m"(mem));	\
     __kir; पूर्ण)
#घोषणा __kernel_ldwu(mem)				\
  (अणु अचिन्हित लघु __kir;				\
     __यंत्र__(".arch ev56;				\
	      ldwu %0,%1" : "=r"(__kir) : "m"(mem));	\
     __kir; पूर्ण)
#घोषणा __kernel_stb(val,mem)				\
  __यंत्र__(".arch ev56;					\
	   stb %1,%0" : "=m"(mem) : "r"(val))
#घोषणा __kernel_stw(val,mem)				\
  __यंत्र__(".arch ev56;					\
	   stw %1,%0" : "=m"(mem) : "r"(val))
#पूर्ण_अगर


#पूर्ण_अगर /* _UAPI__ALPHA_COMPILER_H */
