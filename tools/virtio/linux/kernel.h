<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित KERNEL_H
#घोषणा KERNEL_H
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <मानकघोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <निश्चित.स>
#समावेश <मानकतर्क.स>

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/overflow.h>
#समावेश <linux/list.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/bug.h>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <यंत्र/barrier.h>

#घोषणा CONFIG_SMP

#घोषणा PAGE_SIZE getpagesize()
#घोषणा PAGE_MASK (~(PAGE_SIZE-1))
#घोषणा PAGE_ALIGN(x) ((x + PAGE_SIZE - 1) & PAGE_MASK)

/* generic data direction definitions */
#घोषणा READ                    0
#घोषणा WRITE                   1

प्रकार अचिन्हित दीर्घ दीर्घ phys_addr_t;
प्रकार अचिन्हित दीर्घ दीर्घ dma_addr_t;
प्रकार माप_प्रकार __kernel_माप_प्रकार;
प्रकार अचिन्हित पूर्णांक __wsum;

काष्ठा page अणु
	अचिन्हित दीर्घ दीर्घ dummy;
पूर्ण;

/* Physical == Virtual */
#घोषणा virt_to_phys(p) ((अचिन्हित दीर्घ)p)
#घोषणा phys_to_virt(a) ((व्योम *)(अचिन्हित दीर्घ)(a))
/* Page address: Virtual / 4K */
#घोषणा page_to_phys(p) ((dma_addr_t)(अचिन्हित दीर्घ)(p))
#घोषणा virt_to_page(p) ((काष्ठा page *)((अचिन्हित दीर्घ)p & PAGE_MASK))

#घोषणा offset_in_page(p) (((अचिन्हित दीर्घ)p) % PAGE_SIZE)

#घोषणा __म_लिखो(a,b) __attribute__((क्रमmat(म_लिखो,a,b)))

#घोषणा ARRAY_SIZE(x) (माप(x)/माप(x[0]))

बाह्य व्योम *__kदो_स्मृति_fake, *__kमुक्त_ignore_start, *__kमुक्त_ignore_end;
अटल अंतरभूत व्योम *kदो_स्मृति(माप_प्रकार s, gfp_t gfp)
अणु
	अगर (__kदो_स्मृति_fake)
		वापस __kदो_स्मृति_fake;
	वापस दो_स्मृति(s);
पूर्ण
अटल अंतरभूत व्योम *kदो_स्मृति_array(अचिन्हित n, माप_प्रकार s, gfp_t gfp)
अणु
	वापस kदो_स्मृति(n * s, gfp);
पूर्ण

अटल अंतरभूत व्योम *kzalloc(माप_प्रकार s, gfp_t gfp)
अणु
	व्योम *p = kदो_स्मृति(s, gfp);

	स_रखो(p, 0, s);
	वापस p;
पूर्ण

अटल अंतरभूत व्योम *alloc_pages_exact(माप_प्रकार s, gfp_t gfp)
अणु
	वापस kदो_स्मृति(s, gfp);
पूर्ण

अटल अंतरभूत व्योम kमुक्त(व्योम *p)
अणु
	अगर (p >= __kमुक्त_ignore_start && p < __kमुक्त_ignore_end)
		वापस;
	मुक्त(p);
पूर्ण

अटल अंतरभूत व्योम मुक्त_pages_exact(व्योम *p, माप_प्रकार s)
अणु
	kमुक्त(p);
पूर्ण

अटल अंतरभूत व्योम *kपुनः_स्मृति(व्योम *p, माप_प्रकार s, gfp_t gfp)
अणु
	वापस पुनः_स्मृति(p, s);
पूर्ण


अटल अंतरभूत अचिन्हित दीर्घ __get_मुक्त_page(gfp_t gfp)
अणु
	व्योम *p;

	posix_memalign(&p, PAGE_SIZE, PAGE_SIZE);
	वापस (अचिन्हित दीर्घ)p;
पूर्ण

अटल अंतरभूत व्योम मुक्त_page(अचिन्हित दीर्घ addr)
अणु
	मुक्त((व्योम *)addr);
पूर्ण

#घोषणा container_of(ptr, type, member) (अणु			\
	स्थिर typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (अक्षर *)__mptr - दुरत्व(type,member) );पूर्ण)

# अगरndef likely
#  define likely(x)	(__builtin_expect(!!(x), 1))
# endअगर
# अगरndef unlikely
#  define unlikely(x)	(__builtin_expect(!!(x), 0))
# endअगर

अटल अंतरभूत व्योम *kपुनः_स्मृति_array(व्योम *p, माप_प्रकार new_n, माप_प्रकार new_size, gfp_t gfp)
अणु
	माप_प्रकार bytes;

	अगर (unlikely(check_mul_overflow(new_n, new_size, &bytes)))
		वापस शून्य;

	वापस kपुनः_स्मृति(p, bytes, gfp);
पूर्ण

#घोषणा pr_err(क्रमmat, ...) ख_लिखो (मानक_त्रुटि, क्रमmat, ## __VA_ARGS__)
#अगर_घोषित DEBUG
#घोषणा pr_debug(क्रमmat, ...) ख_लिखो (मानक_त्रुटि, क्रमmat, ## __VA_ARGS__)
#अन्यथा
#घोषणा pr_debug(क्रमmat, ...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर
#घोषणा dev_err(dev, क्रमmat, ...) ख_लिखो (मानक_त्रुटि, क्रमmat, ## __VA_ARGS__)
#घोषणा dev_warn(dev, क्रमmat, ...) ख_लिखो (मानक_त्रुटि, क्रमmat, ## __VA_ARGS__)

#घोषणा min(x, y) (अणु				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(व्योम) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; पूर्ण)

#पूर्ण_अगर /* KERNEL_H */
