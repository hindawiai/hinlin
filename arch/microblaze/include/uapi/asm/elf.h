<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _UAPI_ASM_MICROBLAZE_ELF_H
#घोषणा _UAPI_ASM_MICROBLAZE_ELF_H

#समावेश <linux/elf-em.h>

/*
 * Note there is no "official" ELF designation क्रम Microblaze.
 * I've snaffled the value from the microblaze binutils source code
 * /binutils/microblaze/include/elf/microblaze.h
 */
#घोषणा EM_MICROBLAZE_OLD	0xbaab
#घोषणा ELF_ARCH		EM_MICROBLAZE

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x)	((x)->e_machine == EM_MICROBLAZE \
				 || (x)->e_machine == EM_MICROBLAZE_OLD)

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS32

#अगर_अघोषित __uClinux__

/*
 * ELF रेजिस्टर definitions..
 */

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/byteorder.h>

#अगर_अघोषित ELF_GREG_T
#घोषणा ELF_GREG_T
प्रकार अचिन्हित दीर्घ elf_greg_t;
#पूर्ण_अगर

#अगर_अघोषित ELF_NGREG
#घोषणा ELF_NGREG (माप(काष्ठा pt_regs) / माप(elf_greg_t))
#पूर्ण_अगर

#अगर_अघोषित ELF_GREGSET_T
#घोषणा ELF_GREGSET_T
प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];
#पूर्ण_अगर

#अगर_अघोषित ELF_FPREGSET_T
#घोषणा ELF_FPREGSET_T

/* TBD */
#घोषणा ELF_NFPREG	33	/* includes fsr */
प्रकार अचिन्हित दीर्घ elf_fpreg_t;
प्रकार elf_fpreg_t elf_fpregset_t[ELF_NFPREG];

/* प्रकार काष्ठा user_fpu_काष्ठा elf_fpregset_t; */
#पूर्ण_अगर

/* This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
 * use of this is to invoke "./ld.so someprog" to test out a new version of
 * the loader.  We need to make sure that it is out of the way of the program
 * that it will "exec", and that there is sufficient room क्रम the brk.
 */

#घोषणा ELF_ET_DYN_BASE         (0x08000000)

#अगर_घोषित __MICROBLAZEEL__
#घोषणा ELF_DATA	ELFDATA2LSB
#अन्यथा
#घोषणा ELF_DATA	ELFDATA2MSB
#पूर्ण_अगर

#घोषणा ELF_EXEC_PAGESIZE	PAGE_SIZE


#घोषणा ELF_CORE_COPY_REGS(_dest, _regs)			\
	स_नकल((अक्षर *) &_dest, (अक्षर *) _regs,		\
	माप(काष्ठा pt_regs));

/* This yields a mask that user programs can use to figure out what
 * inकाष्ठाion set this CPU supports.  This could be करोne in user space,
 * but it's not easy, and we've alपढ़ोy करोne it here.
 */
#घोषणा ELF_HWCAP	(0)

/* This yields a string that ld.so will use to load implementation
 * specअगरic libraries क्रम optimization.  This is more specअगरic in
 * पूर्णांकent than poking at uname or /proc/cpuinfo.

 * For the moment, we have only optimizations क्रम the Intel generations,
 * but that could change...
 */
#घोषणा ELF_PLATFORM  (शून्य)

/* Added _f parameter. Is this definition correct: TBD */
#घोषणा ELF_PLAT_INIT(_r, _f)				\
करो अणु							\
	_r->r0 =  _r->r1 =  _r->r2 =  _r->r3 =		\
	_r->r4 =  _r->r5 =  _r->r6 =  _r->r7 =		\
	_r->r8 =  _r->r9 =  _r->r10 = _r->r11 =		\
	_r->r12 = _r->r13 = _r->r14 = _r->r15 =		\
	_r->r16 = _r->r17 = _r->r18 = _r->r19 =		\
	_r->r20 = _r->r21 = _r->r22 = _r->r23 =		\
	_r->r24 = _r->r25 = _r->r26 = _r->r27 =		\
	_r->r28 = _r->r29 = _r->r30 = _r->r31 =		\
	0;						\
पूर्ण जबतक (0)


#पूर्ण_अगर /* __uClinux__ */

#पूर्ण_अगर /* _UAPI_ASM_MICROBLAZE_ELF_H */
