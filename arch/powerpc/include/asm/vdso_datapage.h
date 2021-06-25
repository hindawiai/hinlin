<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _VDSO_DATAPAGE_H
#घोषणा _VDSO_DATAPAGE_H
#अगर_घोषित __KERNEL__

/*
 * Copyright (C) 2002 Peter Bergner <bergner@vnet.ibm.com>, IBM
 * Copyright (C) 2005 Benjamin Herrenschmidy <benh@kernel.crashing.org>,
 * 		      IBM Corp.
 */


/*
 * Note about this काष्ठाure:
 *
 * This काष्ठाure was historically called प्रणालीcfg and exposed to
 * userland via /proc/ppc64/प्रणालीcfg. Unक्रमtunately, this became an
 * ABI issue as some proprietary software started relying on being able
 * to mmap() it, thus we have to keep the base layout at least क्रम a
 * few kernel versions.
 *
 * However, since ppc32 करोesn't suffer from this backward handicap,
 * a simpler version of the data काष्ठाure is used there with only the
 * fields actually used by the vDSO.
 *
 */

/*
 * If the major version changes we are incompatible.
 * Minor version changes are a hपूर्णांक.
 */
#घोषणा SYSTEMCFG_MAJOR 1
#घोषणा SYSTEMCFG_MINOR 1

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/unistd.h>
#समावेश <linux/समय.स>
#समावेश <vdso/datapage.h>

#घोषणा SYSCALL_MAP_SIZE      ((NR_syscalls + 31) / 32)

/*
 * So here is the ppc64 backward compatible version
 */

#अगर_घोषित CONFIG_PPC64

काष्ठा vdso_arch_data अणु
	__u8  eye_catcher[16];		/* Eyecatcher: SYSTEMCFG:PPC64	0x00 */
	काष्ठा अणु			/* Systemcfg version numbers	     */
		__u32 major;		/* Major number			0x10 */
		__u32 minor;		/* Minor number			0x14 */
	पूर्ण version;

	/* Note about the platक्रमm flags: it now only contains the lpar
	 * bit. The actual platक्रमm number is dead and buried
	 */
	__u32 platक्रमm;			/* Platक्रमm flags		0x18 */
	__u32 processor;		/* Processor type		0x1C */
	__u64 processorCount;		/* # of physical processors	0x20 */
	__u64 physicalMemorySize;	/* Size of real memory(B)	0x28 */
	__u64 tb_orig_stamp;		/* (NU) Timebase at boot	0x30 */
	__u64 tb_ticks_per_sec;		/* Timebase tics / sec		0x38 */
	__u64 tb_to_xs;			/* (NU) Inverse of TB to 2^20	0x40 */
	__u64 stamp_xsec;		/* (NU)				0x48 */
	__u64 tb_update_count;		/* (NU) Timebase atomicity ctr	0x50 */
	__u32 tz_minuteswest;		/* (NU) Min. west of Greenwich	0x58 */
	__u32 tz_dstसमय;		/* (NU) Type of dst correction	0x5C */
	__u32 dcache_size;		/* L1 d-cache size		0x60 */
	__u32 dcache_line_size;		/* L1 d-cache line size		0x64 */
	__u32 icache_size;		/* L1 i-cache size		0x68 */
	__u32 icache_line_size;		/* L1 i-cache line size		0x6C */

	/* those additional ones करोn't have to be located anywhere
	 * special as they were not part of the original प्रणालीcfg
	 */
	__u32 dcache_block_size;		/* L1 d-cache block size     */
	__u32 icache_block_size;		/* L1 i-cache block size     */
	__u32 dcache_log_block_size;		/* L1 d-cache log block size */
	__u32 icache_log_block_size;		/* L1 i-cache log block size */
	__u32 syscall_map[SYSCALL_MAP_SIZE];	/* Map of syscalls  */
	__u32 compat_syscall_map[SYSCALL_MAP_SIZE];	/* Map of compat syscalls */

	काष्ठा vdso_data data[CS_BASES];
पूर्ण;

#अन्यथा /* CONFIG_PPC64 */

/*
 * And here is the simpler 32 bits version
 */
काष्ठा vdso_arch_data अणु
	__u64 tb_ticks_per_sec;		/* Timebase tics / sec		0x38 */
	__u32 syscall_map[SYSCALL_MAP_SIZE]; /* Map of syscalls */
	__u32 compat_syscall_map[0];	/* No compat syscalls on PPC32 */
	काष्ठा vdso_data data[CS_BASES];
पूर्ण;

#पूर्ण_अगर /* CONFIG_PPC64 */

बाह्य काष्ठा vdso_arch_data *vdso_data;

#अन्यथा /* __ASSEMBLY__ */

.macro get_datapage ptr
	bcl	20, 31, .+4
999:
	mflr	\ptr
	addis	\ptr, \ptr, (_vdso_datapage - 999b)@ha
	addi	\ptr, \ptr, (_vdso_datapage - 999b)@l
.endm

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _SYSTEMCFG_H */
