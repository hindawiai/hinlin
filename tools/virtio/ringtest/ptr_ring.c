<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश "main.h"
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <pthपढ़ो.h>
#समावेश <दो_स्मृति.h>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>

#घोषणा SMP_CACHE_BYTES 64
#घोषणा cache_line_size() SMP_CACHE_BYTES
#घोषणा ____cacheline_aligned_in_smp __attribute__ ((aligned (SMP_CACHE_BYTES)))
#घोषणा unlikely(x)    (__builtin_expect(!!(x), 0))
#घोषणा likely(x)    (__builtin_expect(!!(x), 1))
#घोषणा ALIGN(x, a) (((x) + (a) - 1) / (a) * (a))
#घोषणा SIZE_MAX        (~(माप_प्रकार)0)
#घोषणा KMALLOC_MAX_SIZE SIZE_MAX

प्रकार pthपढ़ो_spinlock_t  spinlock_t;

प्रकार पूर्णांक gfp_t;
#घोषणा __GFP_ZERO 0x1

अटल व्योम *kदो_स्मृति(अचिन्हित size, gfp_t gfp)
अणु
	व्योम *p = memalign(64, size);
	अगर (!p)
		वापस p;

	अगर (gfp & __GFP_ZERO)
		स_रखो(p, 0, size);
	वापस p;
पूर्ण

अटल अंतरभूत व्योम *kzalloc(अचिन्हित size, gfp_t flags)
अणु
	वापस kदो_स्मृति(size, flags | __GFP_ZERO);
पूर्ण

अटल अंतरभूत व्योम *kदो_स्मृति_array(माप_प्रकार n, माप_प्रकार size, gfp_t flags)
अणु
	अगर (size != 0 && n > SIZE_MAX / size)
		वापस शून्य;
	वापस kदो_स्मृति(n * size, flags);
पूर्ण

अटल अंतरभूत व्योम *kसुस्मृति(माप_प्रकार n, माप_प्रकार size, gfp_t flags)
अणु
	वापस kदो_स्मृति_array(n, size, flags | __GFP_ZERO);
पूर्ण

अटल व्योम kमुक्त(व्योम *p)
अणु
	अगर (p)
		मुक्त(p);
पूर्ण

#घोषणा kvदो_स्मृति_array kदो_स्मृति_array
#घोषणा kvमुक्त kमुक्त

अटल व्योम spin_lock_init(spinlock_t *lock)
अणु
	पूर्णांक r = pthपढ़ो_spin_init(lock, 0);
	निश्चित(!r);
पूर्ण

अटल व्योम spin_lock(spinlock_t *lock)
अणु
	पूर्णांक ret = pthपढ़ो_spin_lock(lock);
	निश्चित(!ret);
पूर्ण

अटल व्योम spin_unlock(spinlock_t *lock)
अणु
	पूर्णांक ret = pthपढ़ो_spin_unlock(lock);
	निश्चित(!ret);
पूर्ण

अटल व्योम spin_lock_bh(spinlock_t *lock)
अणु
	spin_lock(lock);
पूर्ण

अटल व्योम spin_unlock_bh(spinlock_t *lock)
अणु
	spin_unlock(lock);
पूर्ण

अटल व्योम spin_lock_irq(spinlock_t *lock)
अणु
	spin_lock(lock);
पूर्ण

अटल व्योम spin_unlock_irq(spinlock_t *lock)
अणु
	spin_unlock(lock);
पूर्ण

अटल व्योम spin_lock_irqsave(spinlock_t *lock, अचिन्हित दीर्घ f)
अणु
	spin_lock(lock);
पूर्ण

अटल व्योम spin_unlock_irqrestore(spinlock_t *lock, अचिन्हित दीर्घ f)
अणु
	spin_unlock(lock);
पूर्ण

#समावेश "../../../include/linux/ptr_ring.h"

अटल अचिन्हित दीर्घ दीर्घ headcnt, tailcnt;
अटल काष्ठा ptr_ring array ____cacheline_aligned_in_smp;

/* implemented by ring */
व्योम alloc_ring(व्योम)
अणु
	पूर्णांक ret = ptr_ring_init(&array, ring_size, 0);
	निश्चित(!ret);
	/* Hacky way to poke at ring पूर्णांकernals. Useful क्रम testing though. */
	अगर (param)
		array.batch = param;
पूर्ण

/* guest side */
पूर्णांक add_inbuf(अचिन्हित len, व्योम *buf, व्योम *datap)
अणु
	पूर्णांक ret;

	ret = __ptr_ring_produce(&array, buf);
	अगर (ret >= 0) अणु
		ret = 0;
		headcnt++;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * ptr_ring API provides no way क्रम producer to find out whether a given
 * buffer was consumed.  Our tests merely require that a successful get_buf
 * implies that add_inbuf succeed in the past, and that add_inbuf will succeed,
 * fake it accordingly.
 */
व्योम *get_buf(अचिन्हित *lenp, व्योम **bufp)
अणु
	व्योम *datap;

	अगर (tailcnt == headcnt || __ptr_ring_full(&array))
		datap = शून्य;
	अन्यथा अणु
		datap = "Buffer\n";
		++tailcnt;
	पूर्ण

	वापस datap;
पूर्ण

bool used_empty()
अणु
	वापस (tailcnt == headcnt || __ptr_ring_full(&array));
पूर्ण

व्योम disable_call()
अणु
	निश्चित(0);
पूर्ण

bool enable_call()
अणु
	निश्चित(0);
पूर्ण

व्योम kick_available(व्योम)
अणु
	निश्चित(0);
पूर्ण

/* host side */
व्योम disable_kick()
अणु
	निश्चित(0);
पूर्ण

bool enable_kick()
अणु
	निश्चित(0);
पूर्ण

bool avail_empty()
अणु
	वापस __ptr_ring_empty(&array);
पूर्ण

bool use_buf(अचिन्हित *lenp, व्योम **bufp)
अणु
	व्योम *ptr;

	ptr = __ptr_ring_consume(&array);

	वापस ptr;
पूर्ण

व्योम call_used(व्योम)
अणु
	निश्चित(0);
पूर्ण
