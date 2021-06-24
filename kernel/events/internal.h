<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _KERNEL_EVENTS_INTERNAL_H
#घोषणा _KERNEL_EVENTS_INTERNAL_H

#समावेश <linux/hardirq.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/refcount.h>

/* Buffer handling */

#घोषणा RING_BUFFER_WRITABLE		0x01

काष्ठा perf_buffer अणु
	refcount_t			refcount;
	काष्ठा rcu_head			rcu_head;
#अगर_घोषित CONFIG_PERF_USE_VMALLOC
	काष्ठा work_काष्ठा		work;
	पूर्णांक				page_order;	/* allocation order  */
#पूर्ण_अगर
	पूर्णांक				nr_pages;	/* nr of data pages  */
	पूर्णांक				overग_लिखो;	/* can overग_लिखो itself */
	पूर्णांक				छोड़ोd;		/* can ग_लिखो पूर्णांकo ring buffer */

	atomic_t			poll;		/* POLL_ क्रम wakeups */

	local_t				head;		/* ग_लिखो position    */
	अचिन्हित पूर्णांक			nest;		/* nested ग_लिखोrs    */
	local_t				events;		/* event limit       */
	local_t				wakeup;		/* wakeup stamp      */
	local_t				lost;		/* nr records lost   */

	दीर्घ				watermark;	/* wakeup watermark  */
	दीर्घ				aux_watermark;
	/* poll crap */
	spinlock_t			event_lock;
	काष्ठा list_head		event_list;

	atomic_t			mmap_count;
	अचिन्हित दीर्घ			mmap_locked;
	काष्ठा user_काष्ठा		*mmap_user;

	/* AUX area */
	दीर्घ				aux_head;
	अचिन्हित पूर्णांक			aux_nest;
	दीर्घ				aux_wakeup;	/* last aux_watermark boundary crossed by aux_head */
	अचिन्हित दीर्घ			aux_pgoff;
	पूर्णांक				aux_nr_pages;
	पूर्णांक				aux_overग_लिखो;
	atomic_t			aux_mmap_count;
	अचिन्हित दीर्घ			aux_mmap_locked;
	व्योम				(*मुक्त_aux)(व्योम *);
	refcount_t			aux_refcount;
	पूर्णांक				aux_in_sampling;
	व्योम				**aux_pages;
	व्योम				*aux_priv;

	काष्ठा perf_event_mmap_page	*user_page;
	व्योम				*data_pages[];
पूर्ण;

बाह्य व्योम rb_मुक्त(काष्ठा perf_buffer *rb);

अटल अंतरभूत व्योम rb_मुक्त_rcu(काष्ठा rcu_head *rcu_head)
अणु
	काष्ठा perf_buffer *rb;

	rb = container_of(rcu_head, काष्ठा perf_buffer, rcu_head);
	rb_मुक्त(rb);
पूर्ण

अटल अंतरभूत व्योम rb_toggle_छोड़ोd(काष्ठा perf_buffer *rb, bool छोड़ो)
अणु
	अगर (!छोड़ो && rb->nr_pages)
		rb->छोड़ोd = 0;
	अन्यथा
		rb->छोड़ोd = 1;
पूर्ण

बाह्य काष्ठा perf_buffer *
rb_alloc(पूर्णांक nr_pages, दीर्घ watermark, पूर्णांक cpu, पूर्णांक flags);
बाह्य व्योम perf_event_wakeup(काष्ठा perf_event *event);
बाह्य पूर्णांक rb_alloc_aux(काष्ठा perf_buffer *rb, काष्ठा perf_event *event,
			pgoff_t pgoff, पूर्णांक nr_pages, दीर्घ watermark, पूर्णांक flags);
बाह्य व्योम rb_मुक्त_aux(काष्ठा perf_buffer *rb);
बाह्य काष्ठा perf_buffer *ring_buffer_get(काष्ठा perf_event *event);
बाह्य व्योम ring_buffer_put(काष्ठा perf_buffer *rb);

अटल अंतरभूत bool rb_has_aux(काष्ठा perf_buffer *rb)
अणु
	वापस !!rb->aux_nr_pages;
पूर्ण

व्योम perf_event_aux_event(काष्ठा perf_event *event, अचिन्हित दीर्घ head,
			  अचिन्हित दीर्घ size, u64 flags);

बाह्य काष्ठा page *
perf_mmap_to_page(काष्ठा perf_buffer *rb, अचिन्हित दीर्घ pgoff);

#अगर_घोषित CONFIG_PERF_USE_VMALLOC
/*
 * Back perf_mmap() with vदो_स्मृति memory.
 *
 * Required क्रम architectures that have d-cache aliasing issues.
 */

अटल अंतरभूत पूर्णांक page_order(काष्ठा perf_buffer *rb)
अणु
	वापस rb->page_order;
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक page_order(काष्ठा perf_buffer *rb)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ perf_data_size(काष्ठा perf_buffer *rb)
अणु
	वापस rb->nr_pages << (PAGE_SHIFT + page_order(rb));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ perf_aux_size(काष्ठा perf_buffer *rb)
अणु
	वापस rb->aux_nr_pages << PAGE_SHIFT;
पूर्ण

#घोषणा __DEFINE_OUTPUT_COPY_BODY(advance_buf, स_नकल_func, ...)	\
अणु									\
	अचिन्हित दीर्घ size, written;					\
									\
	करो अणु								\
		size    = min(handle->size, len);			\
		written = स_नकल_func(__VA_ARGS__);			\
		written = size - written;				\
									\
		len -= written;						\
		handle->addr += written;				\
		अगर (advance_buf)					\
			buf += written;					\
		handle->size -= written;				\
		अगर (!handle->size) अणु					\
			काष्ठा perf_buffer *rb = handle->rb;	\
									\
			handle->page++;					\
			handle->page &= rb->nr_pages - 1;		\
			handle->addr = rb->data_pages[handle->page];	\
			handle->size = PAGE_SIZE << page_order(rb);	\
		पूर्ण							\
	पूर्ण जबतक (len && written == size);				\
									\
	वापस len;							\
पूर्ण

#घोषणा DEFINE_OUTPUT_COPY(func_name, स_नकल_func)			\
अटल अंतरभूत अचिन्हित दीर्घ						\
func_name(काष्ठा perf_output_handle *handle,				\
	  स्थिर व्योम *buf, अचिन्हित दीर्घ len)				\
__DEFINE_OUTPUT_COPY_BODY(true, स_नकल_func, handle->addr, buf, size)

अटल अंतरभूत अचिन्हित दीर्घ
__output_custom(काष्ठा perf_output_handle *handle, perf_copy_f copy_func,
		स्थिर व्योम *buf, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ orig_len = len;
	__DEFINE_OUTPUT_COPY_BODY(false, copy_func, handle->addr, buf,
				  orig_len - len, size)
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
स_नकल_common(व्योम *dst, स्थिर व्योम *src, अचिन्हित दीर्घ n)
अणु
	स_नकल(dst, src, n);
	वापस 0;
पूर्ण

DEFINE_OUTPUT_COPY(__output_copy, स_नकल_common)

अटल अंतरभूत अचिन्हित दीर्घ
स_नकल_skip(व्योम *dst, स्थिर व्योम *src, अचिन्हित दीर्घ n)
अणु
	वापस 0;
पूर्ण

DEFINE_OUTPUT_COPY(__output_skip, स_नकल_skip)

#अगर_अघोषित arch_perf_out_copy_user
#घोषणा arch_perf_out_copy_user arch_perf_out_copy_user

अटल अंतरभूत अचिन्हित दीर्घ
arch_perf_out_copy_user(व्योम *dst, स्थिर व्योम *src, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ ret;

	pagefault_disable();
	ret = __copy_from_user_inatomic(dst, src, n);
	pagefault_enable();

	वापस ret;
पूर्ण
#पूर्ण_अगर

DEFINE_OUTPUT_COPY(__output_copy_user, arch_perf_out_copy_user)

अटल अंतरभूत पूर्णांक get_recursion_context(पूर्णांक *recursion)
अणु
	अचिन्हित पूर्णांक pc = preempt_count();
	अचिन्हित अक्षर rctx = 0;

	rctx += !!(pc & (NMI_MASK));
	rctx += !!(pc & (NMI_MASK | HARसूचीQ_MASK));
	rctx += !!(pc & (NMI_MASK | HARसूचीQ_MASK | SOFTIRQ_OFFSET));

	अगर (recursion[rctx])
		वापस -1;

	recursion[rctx]++;
	barrier();

	वापस rctx;
पूर्ण

अटल अंतरभूत व्योम put_recursion_context(पूर्णांक *recursion, पूर्णांक rctx)
अणु
	barrier();
	recursion[rctx]--;
पूर्ण

#अगर_घोषित CONFIG_HAVE_PERF_USER_STACK_DUMP
अटल अंतरभूत bool arch_perf_have_user_stack_dump(व्योम)
अणु
	वापस true;
पूर्ण

#घोषणा perf_user_stack_poपूर्णांकer(regs) user_stack_poपूर्णांकer(regs)
#अन्यथा
अटल अंतरभूत bool arch_perf_have_user_stack_dump(व्योम)
अणु
	वापस false;
पूर्ण

#घोषणा perf_user_stack_poपूर्णांकer(regs) 0
#पूर्ण_अगर /* CONFIG_HAVE_PERF_USER_STACK_DUMP */

#पूर्ण_अगर /* _KERNEL_EVENTS_INTERNAL_H */
