<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_POWERPC_AUXVEC_H
#घोषणा _ASM_POWERPC_AUXVEC_H

/*
 * We need to put in some extra aux table entries to tell glibc what
 * the cache block size is, so it can use the dcbz inकाष्ठाion safely.
 */
#घोषणा AT_DCACHEBSIZE		19
#घोषणा AT_ICACHEBSIZE		20
#घोषणा AT_UCACHEBSIZE		21
/* A special ignored type value क्रम PPC, क्रम glibc compatibility.  */
#घोषणा AT_IGNOREPPC		22

/* The vDSO location. We have to use the same value as x86 क्रम glibc's
 * sake :-)
 */
#घोषणा AT_SYSINFO_EHDR		33

/*
 * AT_*CACHEBSIZE above represent the cache *block* size which is
 * the size that is affected by the cache management inकाष्ठाions.
 *
 * It करोesn't nececssarily matches the cache *line* size which is
 * more of a perक्रमmance tuning hपूर्णांक. Additionally the latter can
 * be dअगरferent क्रम the dअगरferent cache levels.
 *
 * The set of entries below represent more extensive inक्रमmation
 * about the caches, in the क्रमm of two entry per cache type,
 * one entry containing the cache size in bytes, and the other
 * containing the cache line size in bytes in the bottom 16 bits
 * and the cache associativity in the next 16 bits.
 *
 * The associativity is such that अगर N is the 16-bit value, the
 * cache is N way set associative. A value अगर 0xffff means fully
 * associative, a value of 1 means directly mapped.
 *
 * For all these fields, a value of 0 means that the inक्रमmation
 * is not known.
 */

#घोषणा AT_L1I_CACHESIZE	40
#घोषणा AT_L1I_CACHEGEOMETRY	41
#घोषणा AT_L1D_CACHESIZE	42
#घोषणा AT_L1D_CACHEGEOMETRY	43
#घोषणा AT_L2_CACHESIZE		44
#घोषणा AT_L2_CACHEGEOMETRY	45
#घोषणा AT_L3_CACHESIZE		46
#घोषणा AT_L3_CACHEGEOMETRY	47

#घोषणा AT_VECTOR_SIZE_ARCH	14 /* entries in ARCH_DLINFO */

#पूर्ण_अगर
