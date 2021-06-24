<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only WITH Linux-syscall-note */
/*
 * Copyright (C) 2012 ARM Ltd.
 * Copyright (C) 2015 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _UAPI_ASM_RISCV_AUXVEC_H
#घोषणा _UAPI_ASM_RISCV_AUXVEC_H

/* vDSO location */
#घोषणा AT_SYSINFO_EHDR 33

/*
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

/* entries in ARCH_DLINFO */
#घोषणा AT_VECTOR_SIZE_ARCH	7

#पूर्ण_अगर /* _UAPI_ASM_RISCV_AUXVEC_H */
