<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __MIPS_ASM_SYNC_H__
#घोषणा __MIPS_ASM_SYNC_H__

/*
 * sync types are defined by the MIPS64 Inकाष्ठाion Set करोcumentation in Volume
 * II-A of the MIPS Architecture Reference Manual, which can be found here:
 *
 *   https://www.mips.com/?करो-करोwnload=the-mips64-inकाष्ठाion-set-v6-06
 *
 * Two types of barrier are provided:
 *
 *   1) Completion barriers, which ensure that a memory operation has actually
 *      completed & often involve stalling the CPU pipeline to करो so.
 *
 *   2) Ordering barriers, which only ensure that affected memory operations
 *      won't be reordered in the CPU pipeline in a manner that violates the
 *      restrictions imposed by the barrier.
 *
 * Ordering barriers can be more efficient than completion barriers, since:
 *
 *   a) Ordering barriers only require memory access inकाष्ठाions which preceed
 *      them in program order (older inकाष्ठाions) to reach a poपूर्णांक in the
 *      load/store datapath beyond which reordering is not possible beक्रमe
 *      allowing memory access inकाष्ठाions which follow them (younger
 *      inकाष्ठाions) to be perक्रमmed.  That is, older inकाष्ठाions करोn't
 *      actually need to complete - they just need to get far enough that all
 *      other coherent CPUs will observe their completion beक्रमe they observe
 *      the effects of younger inकाष्ठाions.
 *
 *   b) Multiple variants of ordering barrier are provided which allow the
 *      effects to be restricted to dअगरferent combinations of older or younger
 *      loads or stores. By way of example, अगर we only care that stores older
 *      than a barrier are observed prior to stores that are younger than a
 *      barrier & करोn't care about the ordering of loads then the 'wmb'
 *      ordering barrier can be used. Limiting the barrier's effects to stores
 *      allows loads to जारी unaffected & potentially allows the CPU to
 *      make progress faster than अगर younger loads had to रुको क्रम older stores
 *      to complete.
 */

/*
 * No sync inकाष्ठाion at all; used to allow code to nullअगरy the effect of the
 * __SYNC() macro without needing lots of #अगर_घोषितery.
 */
#घोषणा __SYNC_none	-1

/*
 * A full completion barrier; all memory accesses appearing prior to this sync
 * inकाष्ठाion in program order must complete beक्रमe any memory accesses
 * appearing after this sync inकाष्ठाion in program order.
 */
#घोषणा __SYNC_full	0x00

/*
 * For now we use a full completion barrier to implement all sync types, until
 * we're satisfied that lightweight ordering barriers defined by MIPSr6 are
 * sufficient to uphold our desired memory model.
 */
#घोषणा __SYNC_aq	__SYNC_full
#घोषणा __SYNC_rl	__SYNC_full
#घोषणा __SYNC_mb	__SYNC_full

/*
 * ...except on Cavium Octeon CPUs, which have been using the 'wmb' ordering
 * barrier since 2010 & omit 'rmb' barriers because the CPUs don't perक्रमm
 * speculative पढ़ोs.
 */
#अगर_घोषित CONFIG_CPU_CAVIUM_OCTEON
# define __SYNC_rmb	__SYNC_none
# define __SYNC_wmb	0x04
#अन्यथा
# define __SYNC_rmb	__SYNC_full
# define __SYNC_wmb	__SYNC_full
#पूर्ण_अगर

/*
 * A GINV sync is a little dअगरferent; it करोesn't relate directly to loads or
 * stores, but instead causes synchronization of an icache or TLB global
 * invalidation operation triggered by the ginvi or ginvt inकाष्ठाions
 * respectively. In हालs where we need to know that a ginvi or ginvt operation
 * has been perक्रमmed by all coherent CPUs, we must issue a sync inकाष्ठाion of
 * this type. Once this inकाष्ठाion graduates all coherent CPUs will have
 * observed the invalidation.
 */
#घोषणा __SYNC_ginv	0x14

/* Trivial; indicate that we always need this sync inकाष्ठाion. */
#घोषणा __SYNC_always	(1 << 0)

/*
 * Indicate that we need this sync inकाष्ठाion only on प्रणालीs with weakly
 * ordered memory access. In general this is most MIPS प्रणालीs, but there are
 * exceptions which provide strongly ordered memory.
 */
#अगर_घोषित CONFIG_WEAK_ORDERING
# define __SYNC_weak_ordering	(1 << 1)
#अन्यथा
# define __SYNC_weak_ordering	0
#पूर्ण_अगर

/*
 * Indicate that we need this sync inकाष्ठाion only on प्रणालीs where LL/SC
 * करोn't implicitly provide a memory barrier. In general this is most MIPS
 * प्रणालीs.
 */
#अगर_घोषित CONFIG_WEAK_REORDERING_BEYOND_LLSC
# define __SYNC_weak_llsc	(1 << 2)
#अन्यथा
# define __SYNC_weak_llsc	0
#पूर्ण_अगर

/*
 * Some Loongson 3 CPUs have a bug wherein execution of a memory access (load,
 * store or prefetch) in between an LL & SC can cause the SC inकाष्ठाion to
 * erroneously succeed, अवरोधing atomicity. Whilst it's unusual to ग_लिखो code
 * containing such sequences, this bug bites harder than we might otherwise
 * expect due to reordering & speculation:
 *
 * 1) A memory access appearing prior to the LL in program order may actually
 *    be executed after the LL - this is the reordering हाल.
 *
 *    In order to aव्योम this we need to place a memory barrier (ie. a SYNC
 *    inकाष्ठाion) prior to every LL inकाष्ठाion, in between it and any earlier
 *    memory access inकाष्ठाions.
 *
 *    This reordering हाल is fixed by 3A R2 CPUs, ie. 3A2000 models and later.
 *
 * 2) If a conditional branch exists between an LL & SC with a target outside
 *    of the LL-SC loop, क्रम example an निकास upon value mismatch in cmpxchg()
 *    or similar, then misprediction of the branch may allow speculative
 *    execution of memory accesses from outside of the LL-SC loop.
 *
 *    In order to aव्योम this we need a memory barrier (ie. a SYNC inकाष्ठाion)
 *    at each affected branch target.
 *
 *    This हाल affects all current Loongson 3 CPUs.
 *
 * The above described हालs cause an error in the cache coherence protocol;
 * such that the Invalidate of a competing LL-SC goes 'missing' and SC
 * erroneously observes its core still has Exclusive state and lets the SC
 * proceed.
 *
 * Thereक्रमe the error only occurs on SMP प्रणालीs.
 */
#अगर_घोषित CONFIG_CPU_LOONGSON3_WORKAROUNDS
# define __SYNC_loongson3_war	(1 << 31)
#अन्यथा
# define __SYNC_loongson3_war	0
#पूर्ण_अगर

/*
 * Some Cavium Octeon CPUs suffer from a bug that causes a single wmb ordering
 * barrier to be ineffective, requiring the use of 2 in sequence to provide an
 * effective barrier as noted by commit 6b07d38aaa52 ("MIPS: Octeon: Use
 * optimized memory barrier primitives."). Here we specअगरy that the affected
 * sync inकाष्ठाions should be emitted twice.
 * Note that this expression is evaluated by the assembler (not the compiler),
 * and that the assembler evaluates '==' as 0 or -1, not 0 or 1.
 */
#अगर_घोषित CONFIG_CPU_CAVIUM_OCTEON
# define __SYNC_rpt(type)	(1 - (type == __SYNC_wmb))
#अन्यथा
# define __SYNC_rpt(type)	1
#पूर्ण_अगर

/*
 * The मुख्य event. Here we actually emit a sync inकाष्ठाion of a given type, अगर
 * reason is non-zero.
 *
 * In future we have the option of emitting entries in a fixups-style table
 * here that would allow us to opportunistically हटाओ some sync inकाष्ठाions
 * when we detect at runसमय that we're running on a CPU that doesn't need
 * them.
 */
#अगर_घोषित CONFIG_CPU_HAS_SYNC
# define ____SYNC(_type, _reason, _अन्यथा)			\
	.अगर	(( _type ) != -1) && ( _reason );		\
	.set	push;						\
	.set	MIPS_ISA_LEVEL_RAW;				\
	.rept	__SYNC_rpt(_type);				\
	sync	_type;						\
	.endr;							\
	.set	pop;						\
	.अन्यथा;							\
	_अन्यथा;							\
	.endअगर
#अन्यथा
# define ____SYNC(_type, _reason, _अन्यथा)
#पूर्ण_अगर

/*
 * Preprocessor magic to expand macros used as arguments beक्रमe we insert them
 * पूर्णांकo assembly code.
 */
#अगर_घोषित __ASSEMBLY__
# define ___SYNC(type, reason, अन्यथा)				\
	____SYNC(type, reason, अन्यथा)
#अन्यथा
# define ___SYNC(type, reason, अन्यथा)				\
	__stringअगरy(____SYNC(type, reason, अन्यथा))
#पूर्ण_अगर

#घोषणा __SYNC(type, reason)					\
	___SYNC(__SYNC_##type, __SYNC_##reason, )
#घोषणा __SYNC_ELSE(type, reason, अन्यथा)				\
	___SYNC(__SYNC_##type, __SYNC_##reason, अन्यथा)

#पूर्ण_अगर /* __MIPS_ASM_SYNC_H__ */
