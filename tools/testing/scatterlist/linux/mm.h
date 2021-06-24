<शैली गुरु>
#अगर_अघोषित _LINUX_MM_H
#घोषणा _LINUX_MM_H

#समावेश <निश्चित.स>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>
#समावेश <मानकपन.स>

प्रकार अचिन्हित दीर्घ dma_addr_t;

#घोषणा unlikely

#घोषणा BUG_ON(x) निश्चित(!(x))

#घोषणा WARN_ON(condition) (अणु                                           \
	पूर्णांक __ret_warn_on = !!(condition);                              \
	unlikely(__ret_warn_on);                                        \
पूर्ण)

#घोषणा WARN_ON_ONCE(condition) (अणु                              \
	पूर्णांक __ret_warn_on = !!(condition);                      \
	अगर (unlikely(__ret_warn_on))                            \
		निश्चित(0);                                      \
	unlikely(__ret_warn_on);                                \
पूर्ण)

#घोषणा PAGE_SIZE	(4096)
#घोषणा PAGE_SHIFT	(12)
#घोषणा PAGE_MASK	(~(PAGE_SIZE-1))

#घोषणा __ALIGN_KERNEL(x, a)		__ALIGN_KERNEL_MASK(x, (typeof(x))(a) - 1)
#घोषणा __ALIGN_KERNEL_MASK(x, mask)	(((x) + (mask)) & ~(mask))
#घोषणा ALIGN(x, a)			__ALIGN_KERNEL((x), (a))
#घोषणा ALIGN_DOWN(x, a)		__ALIGN_KERNEL((x) - ((a) - 1), (a))

#घोषणा PAGE_ALIGN(addr) ALIGN(addr, PAGE_SIZE)

#घोषणा offset_in_page(p)	((अचिन्हित दीर्घ)(p) & ~PAGE_MASK)

#घोषणा virt_to_page(x)	((व्योम *)x)
#घोषणा page_address(x)	((व्योम *)x)

अटल अंतरभूत अचिन्हित दीर्घ page_to_phys(काष्ठा page *page)
अणु
	निश्चित(0);

	वापस 0;
पूर्ण

#घोषणा page_to_pfn(page) ((अचिन्हित दीर्घ)(page) / PAGE_SIZE)
#घोषणा pfn_to_page(pfn) (व्योम *)((pfn) * PAGE_SIZE)
#घोषणा nth_page(page,n) pfn_to_page(page_to_pfn((page)) + (n))

#घोषणा __min(t1, t2, min1, min2, x, y) (अणु              \
	t1 min1 = (x);                                  \
	t2 min2 = (y);                                  \
	(व्योम) (&min1 == &min2);                        \
	min1 < min2 ? min1 : min2; पूर्ण)

#घोषणा ___PASTE(a,b) a##b
#घोषणा __PASTE(a,b) ___PASTE(a,b)

#घोषणा __UNIQUE_ID(prefix) __PASTE(__PASTE(__UNIQUE_ID_, prefix), __COUNTER__)

#घोषणा min(x, y)                                       \
	__min(typeof(x), typeof(y),                     \
	      __UNIQUE_ID(min1_), __UNIQUE_ID(min2_),   \
	      x, y)

#घोषणा min_t(type, x, y)                               \
	__min(type, type,                               \
	      __UNIQUE_ID(min1_), __UNIQUE_ID(min2_),   \
	      x, y)

#घोषणा preemptible() (1)

अटल अंतरभूत व्योम *kmap(काष्ठा page *page)
अणु
	निश्चित(0);

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम *kmap_atomic(काष्ठा page *page)
अणु
	निश्चित(0);

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम kunmap(व्योम *addr)
अणु
	निश्चित(0);
पूर्ण

अटल अंतरभूत व्योम kunmap_atomic(व्योम *addr)
अणु
	निश्चित(0);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __get_मुक्त_page(अचिन्हित पूर्णांक flags)
अणु
	वापस (अचिन्हित दीर्घ)दो_स्मृति(PAGE_SIZE);
पूर्ण

अटल अंतरभूत व्योम मुक्त_page(अचिन्हित दीर्घ page)
अणु
	मुक्त((व्योम *)page);
पूर्ण

अटल अंतरभूत व्योम *kदो_स्मृति(अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक flags)
अणु
	वापस दो_स्मृति(size);
पूर्ण

अटल अंतरभूत व्योम *
kदो_स्मृति_array(अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक flags)
अणु
	वापस दो_स्मृति(n * size);
पूर्ण

#घोषणा kमुक्त(x) मुक्त(x)

#घोषणा kmemleak_alloc(a, b, c, d)
#घोषणा kmemleak_मुक्त(a)

#घोषणा PageSlab(p) (0)
#घोषणा flush_kernel_dcache_page(p)

#घोषणा MAX_ERRNO	4095

#घोषणा IS_ERR_VALUE(x) unlikely((अचिन्हित दीर्घ)(व्योम *)(x) >= (अचिन्हित दीर्घ)-MAX_ERRNO)

अटल अंतरभूत व्योम * __must_check ERR_PTR(दीर्घ error)
अणु
	वापस (व्योम *) error;
पूर्ण

अटल अंतरभूत दीर्घ __must_check PTR_ERR(__क्रमce स्थिर व्योम *ptr)
अणु
	वापस (दीर्घ) ptr;
पूर्ण

अटल अंतरभूत bool __must_check IS_ERR(__क्रमce स्थिर व्योम *ptr)
अणु
	वापस IS_ERR_VALUE((अचिन्हित दीर्घ)ptr);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check PTR_ERR_OR_ZERO(__क्रमce स्थिर व्योम *ptr)
अणु
	अगर (IS_ERR(ptr))
		वापस PTR_ERR(ptr);
	अन्यथा
		वापस 0;
पूर्ण

#घोषणा IS_ENABLED(x) (0)

#पूर्ण_अगर
