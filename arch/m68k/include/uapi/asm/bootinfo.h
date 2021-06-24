<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * यंत्र/bootinfo.h -- Definition of the Linux/m68k boot inक्रमmation काष्ठाure
 *
 * Copyright 1992 by Greg Harp
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _UAPI_ASM_M68K_BOOTINFO_H
#घोषणा _UAPI_ASM_M68K_BOOTINFO_H


#समावेश <linux/types.h>


#अगर_अघोषित __ASSEMBLY__

    /*
     *  Bootinfo definitions
     *
     *  This is an easily parsable and extendable काष्ठाure containing all
     *  inक्रमmation to be passed from the bootstrap to the kernel.
     *
     *  This way I hope to keep all future changes back/क्रमewards compatible.
     *  Thus, keep your fingers crossed...
     *
     *  This काष्ठाure is copied right after the kernel by the bootstrap
     *  routine.
     */

काष्ठा bi_record अणु
	__be16 tag;			/* tag ID */
	__be16 size;			/* size of record (in bytes) */
	__be32 data[0];			/* data */
पूर्ण;


काष्ठा mem_info अणु
	__be32 addr;			/* physical address of memory chunk */
	__be32 size;			/* length of memory chunk (in bytes) */
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */


    /*
     *  Tag Definitions
     *
     *  Machine independent tags start counting from 0x0000
     *  Machine dependent tags start counting from 0x8000
     */

#घोषणा BI_LAST			0x0000	/* last record (sentinel) */
#घोषणा BI_MACHTYPE		0x0001	/* machine type (__be32) */
#घोषणा BI_CPUTYPE		0x0002	/* cpu type (__be32) */
#घोषणा BI_FPUTYPE		0x0003	/* fpu type (__be32) */
#घोषणा BI_MMUTYPE		0x0004	/* mmu type (__be32) */
#घोषणा BI_MEMCHUNK		0x0005	/* memory chunk address and size */
					/* (काष्ठा mem_info) */
#घोषणा BI_RAMDISK		0x0006	/* ramdisk address and size */
					/* (काष्ठा mem_info) */
#घोषणा BI_COMMAND_LINE		0x0007	/* kernel command line parameters */
					/* (string) */


    /*
     *  Linux/m68k Architectures (BI_MACHTYPE)
     */

#घोषणा MACH_AMIGA		1
#घोषणा MACH_ATARI		2
#घोषणा MACH_MAC		3
#घोषणा MACH_APOLLO		4
#घोषणा MACH_SUN3		5
#घोषणा MACH_MVME147		6
#घोषणा MACH_MVME16x		7
#घोषणा MACH_BVME6000		8
#घोषणा MACH_HP300		9
#घोषणा MACH_Q40		10
#घोषणा MACH_SUN3X		11
#घोषणा MACH_M54XX		12
#घोषणा MACH_M5441X		13


    /*
     *  CPU, FPU and MMU types (BI_CPUTYPE, BI_FPUTYPE, BI_MMUTYPE)
     *
     *  Note: we may rely on the following equalities:
     *
     *      CPU_68020 == MMU_68851
     *      CPU_68030 == MMU_68030
     *      CPU_68040 == FPU_68040 == MMU_68040
     *      CPU_68060 == FPU_68060 == MMU_68060
     */

#घोषणा CPUB_68020		0
#घोषणा CPUB_68030		1
#घोषणा CPUB_68040		2
#घोषणा CPUB_68060		3
#घोषणा CPUB_COLDFIRE		4

#घोषणा CPU_68020		(1 << CPUB_68020)
#घोषणा CPU_68030		(1 << CPUB_68030)
#घोषणा CPU_68040		(1 << CPUB_68040)
#घोषणा CPU_68060		(1 << CPUB_68060)
#घोषणा CPU_COLDFIRE		(1 << CPUB_COLDFIRE)

#घोषणा FPUB_68881		0
#घोषणा FPUB_68882		1
#घोषणा FPUB_68040		2	/* Internal FPU */
#घोषणा FPUB_68060		3	/* Internal FPU */
#घोषणा FPUB_SUNFPA		4	/* Sun-3 FPA */
#घोषणा FPUB_COLDFIRE		5	/* ColdFire FPU */

#घोषणा FPU_68881		(1 << FPUB_68881)
#घोषणा FPU_68882		(1 << FPUB_68882)
#घोषणा FPU_68040		(1 << FPUB_68040)
#घोषणा FPU_68060		(1 << FPUB_68060)
#घोषणा FPU_SUNFPA		(1 << FPUB_SUNFPA)
#घोषणा FPU_COLDFIRE		(1 << FPUB_COLDFIRE)

#घोषणा MMUB_68851		0
#घोषणा MMUB_68030		1	/* Internal MMU */
#घोषणा MMUB_68040		2	/* Internal MMU */
#घोषणा MMUB_68060		3	/* Internal MMU */
#घोषणा MMUB_APOLLO		4	/* Custom Apollo */
#घोषणा MMUB_SUN3		5	/* Custom Sun-3 */
#घोषणा MMUB_COLDFIRE		6	/* Internal MMU */

#घोषणा MMU_68851		(1 << MMUB_68851)
#घोषणा MMU_68030		(1 << MMUB_68030)
#घोषणा MMU_68040		(1 << MMUB_68040)
#घोषणा MMU_68060		(1 << MMUB_68060)
#घोषणा MMU_SUN3		(1 << MMUB_SUN3)
#घोषणा MMU_APOLLO		(1 << MMUB_APOLLO)
#घोषणा MMU_COLDFIRE		(1 << MMUB_COLDFIRE)


    /*
     * Stuff क्रम bootinfo पूर्णांकerface versioning
     *
     * At the start of kernel code, a 'struct bootversion' is located.
     * bootstrap checks क्रम a matching version of the पूर्णांकerface beक्रमe booting
     * a kernel, to aव्योम user confusion अगर kernel and bootstrap करोn't work
     * together :-)
     *
     * If incompatible changes are made to the bootinfo पूर्णांकerface, the major
     * number below should be stepped (and the minor reset to 0) क्रम the
     * appropriate machine. If a change is backward-compatible, the minor
     * should be stepped. "Backwards-compatible" means that booting will work,
     * but certain features may not.
     */

#घोषणा BOOTINFOV_MAGIC			0x4249561A	/* 'BIV^Z' */
#घोषणा MK_BI_VERSION(major, minor)	(((major) << 16) + (minor))
#घोषणा BI_VERSION_MAJOR(v)		(((v) >> 16) & 0xffff)
#घोषणा BI_VERSION_MINOR(v)		((v) & 0xffff)

#अगर_अघोषित __ASSEMBLY__

काष्ठा bootversion अणु
	__be16 branch;
	__be32 magic;
	काष्ठा अणु
		__be32 machtype;
		__be32 version;
	पूर्ण machversions[0];
पूर्ण __packed;

#पूर्ण_अगर /* __ASSEMBLY__ */


#पूर्ण_अगर /* _UAPI_ASM_M68K_BOOTINFO_H */
