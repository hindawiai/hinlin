<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/fpu.h>

#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) \
  ((sl) = (al) + (bl), (sh) = (ah) + (bh) + ((sl) < (al)))

#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) \
  ((sl) = (al) - (bl), (sh) = (ah) - (bh) - ((al) < (bl)))

#घोषणा umul_ppmm(wh, wl, u, v)			\
  __यंत्र__ ("mulq %2,%3,%1; umulh %2,%3,%0"	\
	   : "=r" ((UDItype)(wh)),		\
	     "=&r" ((UDItype)(wl))		\
	   : "r" ((UDItype)(u)),		\
	     "r" ((UDItype)(v)))

#घोषणा uभाग_qrnnd(q, r, n1, n0, d)				\
  करो अणु अचिन्हित दीर्घ __r;					\
    (q) = __uभाग_qrnnd (&__r, (n1), (n0), (d));			\
    (r) = __r;							\
  पूर्ण जबतक (0)
बाह्य अचिन्हित दीर्घ __uभाग_qrnnd (अचिन्हित दीर्घ *, अचिन्हित दीर्घ,
				   अचिन्हित दीर्घ , अचिन्हित दीर्घ);

#घोषणा UDIV_NEEDS_NORMALIZATION 1  

#घोषणा पात()			जाओ bad_insn

#अगर_अघोषित __LITTLE_ENDIAN
#घोषणा __LITTLE_ENDIAN -1
#पूर्ण_अगर
#घोषणा __BYTE_ORDER __LITTLE_ENDIAN
