<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * traps.h:  Format of entries क्रम the Sparc trap table.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित _UAPI_SPARC_TRAPS_H
#घोषणा _UAPI_SPARC_TRAPS_H

#घोषणा NUM_SPARC_TRAPS  255

#अगर_अघोषित __ASSEMBLY__
#पूर्ण_अगर /* !(__ASSEMBLY__) */

/* For patching the trap table at boot समय, we need to know how to
 * क्रमm various common Sparc inकाष्ठाions.  Thus these macros...
 */

#घोषणा SPARC_MOV_CONST_L3(स्थिर) (0xa6102000 | (स्थिर&0xfff))

/* The following assumes that the branch lies beक्रमe the place we
 * are branching to.  This is the हाल क्रम a trap vector...
 * You have been warned.
 */
#घोषणा SPARC_BRANCH(dest_addr, inst_addr) \
          (0x10800000 | (((dest_addr-inst_addr)>>2)&0x3fffff))

#घोषणा SPARC_RD_PSR_L0  (0xa1480000)
#घोषणा SPARC_RD_WIM_L3  (0xa7500000)
#घोषणा SPARC_NOP (0x01000000)

/* Various पूर्णांकeresting trap levels. */
/* First, hardware traps. */
#घोषणा SP_TRAP_TFLT    0x1          /* Text fault */
#घोषणा SP_TRAP_II      0x2          /* Illegal Inकाष्ठाion */
#घोषणा SP_TRAP_PI      0x3          /* Privileged Inकाष्ठाion */
#घोषणा SP_TRAP_FPD     0x4          /* Floating Poपूर्णांक Disabled */
#घोषणा SP_TRAP_WOVF    0x5          /* Winकरोw Overflow */
#घोषणा SP_TRAP_WUNF    0x6          /* Winकरोw Underflow */
#घोषणा SP_TRAP_MNA     0x7          /* Memory Address Unaligned */
#घोषणा SP_TRAP_FPE     0x8          /* Floating Poपूर्णांक Exception */
#घोषणा SP_TRAP_DFLT    0x9          /* Data Fault */
#घोषणा SP_TRAP_TOF     0xa          /* Tag Overflow */
#घोषणा SP_TRAP_WDOG    0xb          /* Watchpoपूर्णांक Detected */
#घोषणा SP_TRAP_IRQ1    0x11         /* IRQ level 1 */
#घोषणा SP_TRAP_IRQ2    0x12         /* IRQ level 2 */
#घोषणा SP_TRAP_IRQ3    0x13         /* IRQ level 3 */
#घोषणा SP_TRAP_IRQ4    0x14         /* IRQ level 4 */
#घोषणा SP_TRAP_IRQ5    0x15         /* IRQ level 5 */
#घोषणा SP_TRAP_IRQ6    0x16         /* IRQ level 6 */
#घोषणा SP_TRAP_IRQ7    0x17         /* IRQ level 7 */
#घोषणा SP_TRAP_IRQ8    0x18         /* IRQ level 8 */
#घोषणा SP_TRAP_IRQ9    0x19         /* IRQ level 9 */
#घोषणा SP_TRAP_IRQ10   0x1a         /* IRQ level 10 */
#घोषणा SP_TRAP_IRQ11   0x1b         /* IRQ level 11 */
#घोषणा SP_TRAP_IRQ12   0x1c         /* IRQ level 12 */
#घोषणा SP_TRAP_IRQ13   0x1d         /* IRQ level 13 */
#घोषणा SP_TRAP_IRQ14   0x1e         /* IRQ level 14 */
#घोषणा SP_TRAP_IRQ15   0x1f         /* IRQ level 15 Non-maskable */
#घोषणा SP_TRAP_RACC    0x20         /* Register Access Error ??? */
#घोषणा SP_TRAP_IACC    0x21         /* Inकाष्ठाion Access Error */
#घोषणा SP_TRAP_CPDIS   0x24         /* Co-Processor Disabled */
#घोषणा SP_TRAP_BADFL   0x25         /* Unimplemented Flush Inकाष्ठाion */
#घोषणा SP_TRAP_CPEXP   0x28         /* Co-Processor Exception */
#घोषणा SP_TRAP_DACC    0x29         /* Data Access Error */
#घोषणा SP_TRAP_DIVZ    0x2a         /* Divide By Zero */
#घोषणा SP_TRAP_DSTORE  0x2b         /* Data Store Error ??? */
#घोषणा SP_TRAP_DMM     0x2c         /* Data Access MMU Miss ??? */
#घोषणा SP_TRAP_IMM     0x3c         /* Inकाष्ठाion Access MMU Miss ??? */

/* Now the Software Traps... */
#घोषणा SP_TRAP_SUNOS   0x80         /* SunOS System Call */
#घोषणा SP_TRAP_SBPT    0x81         /* Software Breakpoपूर्णांक */
#घोषणा SP_TRAP_SDIVZ   0x82         /* Software Divide-by-Zero trap */
#घोषणा SP_TRAP_FWIN    0x83         /* Flush Winकरोws */
#घोषणा SP_TRAP_CWIN    0x84         /* Clean Winकरोws */
#घोषणा SP_TRAP_RCHK    0x85         /* Range Check */
#घोषणा SP_TRAP_FUNA    0x86         /* Fix Unaligned Access */
#घोषणा SP_TRAP_IOWFL   0x87         /* Integer Overflow */
#घोषणा SP_TRAP_SOLARIS 0x88         /* Solaris System Call */
#घोषणा SP_TRAP_NETBSD  0x89         /* NetBSD System Call */
#घोषणा SP_TRAP_LINUX   0x90         /* Linux System Call */

/* Names used क्रम compatibility with SunOS */
#घोषणा ST_SYSCALL              0x00
#घोषणा ST_BREAKPOINT           0x01
#घोषणा ST_DIV0                 0x02
#घोषणा ST_FLUSH_WINDOWS        0x03
#घोषणा ST_CLEAN_WINDOWS        0x04
#घोषणा ST_RANGE_CHECK          0x05
#घोषणा ST_FIX_ALIGN            0x06
#घोषणा ST_INT_OVERFLOW         0x07

/* Special traps... */
#घोषणा SP_TRAP_KBPT1   0xfe         /* KADB/PROM Breakpoपूर्णांक one */
#घोषणा SP_TRAP_KBPT2   0xff         /* KADB/PROM Breakpoपूर्णांक two */

/* Handy Macros */
/* Is this a trap we never expect to get? */
#घोषणा BAD_TRAP_P(level) \
        ((level > SP_TRAP_WDOG && level < SP_TRAP_IRQ1) || \
	 (level > SP_TRAP_IACC && level < SP_TRAP_CPDIS) || \
	 (level > SP_TRAP_BADFL && level < SP_TRAP_CPEXP) || \
	 (level > SP_TRAP_DMM && level < SP_TRAP_IMM) || \
	 (level > SP_TRAP_IMM && level < SP_TRAP_SUNOS) || \
	 (level > SP_TRAP_LINUX && level < SP_TRAP_KBPT1))

/* Is this a Hardware trap? */
#घोषणा HW_TRAP_P(level) ((level > 0) && (level < SP_TRAP_SUNOS))

/* Is this a Software trap? */
#घोषणा SW_TRAP_P(level) ((level >= SP_TRAP_SUNOS) && (level <= SP_TRAP_KBPT2))

/* Is this a प्रणाली call क्रम some OS we know about? */
#घोषणा SCALL_TRAP_P(level) ((level == SP_TRAP_SUNOS) || \
			     (level == SP_TRAP_SOLARIS) || \
			     (level == SP_TRAP_NETBSD) || \
			     (level == SP_TRAP_LINUX))

#पूर्ण_अगर /* _UAPI_SPARC_TRAPS_H */
