<शैली गुरु>
#अगर_अघोषित _TOOLS_LINUX_RING_BUFFER_H_
#घोषणा _TOOLS_LINUX_RING_BUFFER_H_

#समावेश <यंत्र/barrier.h>
#समावेश <linux/perf_event.h>

/*
 * Contract with kernel क्रम walking the perf ring buffer from
 * user space requires the following barrier pairing (quote
 * from kernel/events/ring_buffer.c):
 *
 *   Since the mmap() consumer (userspace) can run on a
 *   dअगरferent CPU:
 *
 *   kernel                             user
 *
 *   अगर (LOAD ->data_tail) अणु            LOAD ->data_head
 *                      (A)             smp_rmb()       (C)
 *      STORE $data                     LOAD $data
 *      smp_wmb()       (B)             smp_mb()        (D)
 *      STORE ->data_head               STORE ->data_tail
 *   पूर्ण
 *
 *   Where A pairs with D, and B pairs with C.
 *
 *   In our हाल A is a control dependency that separates the
 *   load of the ->data_tail and the stores of $data. In हाल
 *   ->data_tail indicates there is no room in the buffer to
 *   store $data we करो not.
 *
 *   D needs to be a full barrier since it separates the data
 *   READ from the tail WRITE.
 *
 *   For B a WMB is sufficient since it separates two WRITEs,
 *   and क्रम C an RMB is sufficient since it separates two READs.
 *
 * Note, instead of B, C, D we could also use smp_store_release()
 * in B and D as well as smp_load_acquire() in C.
 *
 * However, this optimization करोes not make sense क्रम all kernel
 * supported architectures since क्रम a fair number it would
 * resolve पूर्णांकo READ_ONCE() + smp_mb() pair क्रम smp_load_acquire(),
 * and smp_mb() + WRITE_ONCE() pair क्रम smp_store_release().
 *
 * Thus क्रम those smp_wmb() in B and smp_rmb() in C would still
 * be less expensive. For the हाल of D this has either the same
 * cost or is less expensive, क्रम example, due to TSO x86 can
 * aव्योम the CPU barrier entirely.
 */

अटल अंतरभूत u64 ring_buffer_पढ़ो_head(काष्ठा perf_event_mmap_page *base)
अणु
/*
 * Architectures where smp_load_acquire() करोes not fallback to
 * READ_ONCE() + smp_mb() pair.
 */
#अगर defined(__x86_64__) || defined(__aarch64__) || defined(__घातerpc64__) || \
    defined(__ia64__) || defined(__sparc__) && defined(__arch64__)
	वापस smp_load_acquire(&base->data_head);
#अन्यथा
	u64 head = READ_ONCE(base->data_head);

	smp_rmb();
	वापस head;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम ring_buffer_ग_लिखो_tail(काष्ठा perf_event_mmap_page *base,
					  u64 tail)
अणु
	smp_store_release(&base->data_tail, tail);
पूर्ण

#पूर्ण_अगर /* _TOOLS_LINUX_RING_BUFFER_H_ */
