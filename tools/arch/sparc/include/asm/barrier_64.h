<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __TOOLS_LINUX_SPARC64_BARRIER_H
#घोषणा __TOOLS_LINUX_SPARC64_BARRIER_H

/* Copied from the kernel sources to tools/:
 *
 * These are here in an efक्रमt to more fully work around Spitfire Errata
 * #51.  Essentially, अगर a memory barrier occurs soon after a mispredicted
 * branch, the chip can stop executing inकाष्ठाions until a trap occurs.
 * Thereक्रमe, अगर पूर्णांकerrupts are disabled, the chip can hang क्रमever.
 *
 * It used to be believed that the memory barrier had to be right in the
 * delay slot, but a हाल has been traced recently wherein the memory barrier
 * was one inकाष्ठाion after the branch delay slot and the chip still hung.
 * The offending sequence was the following in sym_wakeup_करोne() of the
 * sym53c8xx_2 driver:
 *
 *	call	sym_ccb_from_dsa, 0
 *	 movge	%icc, 0, %l0
 *	brz,pn	%o0, .LL1303
 *	 mov	%o0, %l2
 *	membar	#LoadLoad
 *
 * The branch has to be mispredicted क्रम the bug to occur.  Thereक्रमe, we put
 * the memory barrier explicitly पूर्णांकo a "branch always, predicted taken"
 * delay slot to aव्योम the problem हाल.
 */
#घोषणा membar_safe(type) \
करो अणु	__यंत्र__ __अस्थिर__("ba,pt	%%xcc, 1f\n\t" \
			     " membar	" type "\n" \
			     "1:\n" \
			     : : : "memory"); \
पूर्ण जबतक (0)

/* The kernel always executes in TSO memory model these days,
 * and furthermore most sparc64 chips implement more stringent
 * memory ordering than required by the specअगरications.
 */
#घोषणा mb()	membar_safe("#StoreLoad")
#घोषणा rmb()	__यंत्र__ __अस्थिर__("":::"memory")
#घोषणा wmb()	__यंत्र__ __अस्थिर__("":::"memory")

#घोषणा smp_store_release(p, v)			\
करो अणु						\
	barrier();				\
	WRITE_ONCE(*p, v);			\
पूर्ण जबतक (0)

#घोषणा smp_load_acquire(p)			\
(अणु						\
	typeof(*p) ___p1 = READ_ONCE(*p);	\
	barrier();				\
	___p1;					\
पूर्ण)

#पूर्ण_अगर /* !(__TOOLS_LINUX_SPARC64_BARRIER_H) */
