<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <मानककोष.स>
#अगर defined(__i386__) || defined(__x86_64__)
#घोषणा barrier() यंत्र अस्थिर("" ::: "memory")
#घोषणा virt_mb() __sync_synchronize()
#घोषणा virt_rmb() barrier()
#घोषणा virt_wmb() barrier()
/* Atomic store should be enough, but gcc generates worse code in that हाल. */
#घोषणा virt_store_mb(var, value)  करो अणु \
	typeof(var) virt_store_mb_value = (value); \
	__atomic_exchange(&(var), &virt_store_mb_value, &virt_store_mb_value, \
			  __ATOMIC_SEQ_CST); \
	barrier(); \
पूर्ण जबतक (0);
/* Weak barriers should be used. If not - it's a bug */
# define mb() पात()
# define dma_rmb() पात()
# define dma_wmb() पात()
#या_अगर defined(__aarch64__)
#घोषणा dmb(opt) यंत्र अस्थिर("dmb " #opt : : : "memory")
#घोषणा virt_mb() __sync_synchronize()
#घोषणा virt_rmb() dmb(ishld)
#घोषणा virt_wmb() dmb(ishst)
#घोषणा virt_store_mb(var, value)  करो अणु WRITE_ONCE(var, value); dmb(ish); पूर्ण जबतक (0)
/* Weak barriers should be used. If not - it's a bug */
# define mb() पात()
# define dma_rmb() पात()
# define dma_wmb() पात()
#अन्यथा
#त्रुटि Please fill in barrier macros
#पूर्ण_अगर

