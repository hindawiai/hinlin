<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __TOOLS_LINUX_KERNEL_H
#घोषणा __TOOLS_LINUX_KERNEL_H

#समावेश <मानकतर्क.स>
#समावेश <मानकघोष.स>
#समावेश <निश्चित.स>
#समावेश <linux/build_bug.h>
#समावेश <linux/compiler.h>
#समावेश <endian.h>
#समावेश <byteswap.h>

#अगर_अघोषित अच_पूर्णांक_उच्च
#घोषणा अच_पूर्णांक_उच्च	(~0U)
#पूर्ण_अगर

#घोषणा DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

#घोषणा PERF_ALIGN(x, a)	__PERF_ALIGN_MASK(x, (typeof(x))(a)-1)
#घोषणा __PERF_ALIGN_MASK(x, mask)	(((x)+(mask))&~(mask))

#अगर_अघोषित दुरत्व
#घोषणा दुरत्व(TYPE, MEMBER) ((माप_प्रकार) &((TYPE *)0)->MEMBER)
#पूर्ण_अगर

#अगर_अघोषित container_of
/**
 * container_of - cast a member of a काष्ठाure out to the containing काष्ठाure
 * @ptr:	the poपूर्णांकer to the member.
 * @type:	the type of the container काष्ठा this is embedded in.
 * @member:	the name of the member within the काष्ठा.
 *
 */
#घोषणा container_of(ptr, type, member) (अणु			\
	स्थिर typeof(((type *)0)->member) * __mptr = (ptr);	\
	(type *)((अक्षर *)__mptr - दुरत्व(type, member)); पूर्ण)
#पूर्ण_अगर

#अगर_अघोषित max
#घोषणा max(x, y) (अणु				\
	typeof(x) _max1 = (x);			\
	typeof(y) _max2 = (y);			\
	(व्योम) (&_max1 == &_max2);		\
	_max1 > _max2 ? _max1 : _max2; पूर्ण)
#पूर्ण_अगर

#अगर_अघोषित min
#घोषणा min(x, y) (अणु				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(व्योम) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; पूर्ण)
#पूर्ण_अगर

#अगर_अघोषित roundup
#घोषणा roundup(x, y) (                                \
अणु                                                      \
	स्थिर typeof(y) __y = y;		       \
	(((x) + (__y - 1)) / __y) * __y;	       \
पूर्ण                                                      \
)
#पूर्ण_अगर

#अगर_अघोषित BUG_ON
#अगर_घोषित न_संशोधन
#घोषणा BUG_ON(cond) करो अणु अगर (cond) अणुपूर्ण पूर्ण जबतक (0)
#अन्यथा
#घोषणा BUG_ON(cond) निश्चित(!(cond))
#पूर्ण_अगर
#पूर्ण_अगर
#घोषणा BUG()	BUG_ON(1)

#अगर __BYTE_ORDER == __BIG_ENDIAN
#घोषणा cpu_to_le16 bswap_16
#घोषणा cpu_to_le32 bswap_32
#घोषणा cpu_to_le64 bswap_64
#घोषणा le16_to_cpu bswap_16
#घोषणा le32_to_cpu bswap_32
#घोषणा le64_to_cpu bswap_64
#घोषणा cpu_to_be16
#घोषणा cpu_to_be32
#घोषणा cpu_to_be64
#घोषणा be16_to_cpu
#घोषणा be32_to_cpu
#घोषणा be64_to_cpu
#अन्यथा
#घोषणा cpu_to_le16
#घोषणा cpu_to_le32
#घोषणा cpu_to_le64
#घोषणा le16_to_cpu
#घोषणा le32_to_cpu
#घोषणा le64_to_cpu
#घोषणा cpu_to_be16 bswap_16
#घोषणा cpu_to_be32 bswap_32
#घोषणा cpu_to_be64 bswap_64
#घोषणा be16_to_cpu bswap_16
#घोषणा be32_to_cpu bswap_32
#घोषणा be64_to_cpu bswap_64
#पूर्ण_अगर

पूर्णांक vscnम_लिखो(अक्षर *buf, माप_प्रकार size, स्थिर अक्षर *fmt, बहु_सूची args);
पूर्णांक scnम_लिखो(अक्षर * buf, माप_प्रकार size, स्थिर अक्षर * fmt, ...);
पूर्णांक scnम_लिखो_pad(अक्षर * buf, माप_प्रकार size, स्थिर अक्षर * fmt, ...);

#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]) + __must_be_array(arr))

/*
 * This looks more complex than it should be. But we need to
 * get the type क्रम the ~ right in round_करोwn (it needs to be
 * as wide as the result!), and we want to evaluate the macro
 * arguments just once each.
 */
#घोषणा __round_mask(x, y) ((__typeof__(x))((y)-1))
#घोषणा round_up(x, y) ((((x)-1) | __round_mask(x, y))+1)
#घोषणा round_करोwn(x, y) ((x) & ~__round_mask(x, y))

#घोषणा current_gfp_context(k) 0
#घोषणा synchronize_rcu()

#पूर्ण_अगर
