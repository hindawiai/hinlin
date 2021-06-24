<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999, 2017
 */
#अगर_अघोषित _ASM_S390_SETUP_H
#घोषणा _ASM_S390_SETUP_H

#समावेश <linux/bits.h>
#समावेश <uapi/यंत्र/setup.h>
#समावेश <linux/build_bug.h>

#घोषणा EP_OFFSET		0x10008
#घोषणा EP_STRING		"S390EP"
#घोषणा PARMAREA		0x10400
#घोषणा EARLY_SCCB_OFFSET	0x11000
#घोषणा HEAD_END		0x12000

/*
 * Machine features detected in early.c
 */

#घोषणा MACHINE_FLAG_VM		BIT(0)
#घोषणा MACHINE_FLAG_KVM	BIT(1)
#घोषणा MACHINE_FLAG_LPAR	BIT(2)
#घोषणा MACHINE_FLAG_DIAG9C	BIT(3)
#घोषणा MACHINE_FLAG_ESOP	BIT(4)
#घोषणा MACHINE_FLAG_IDTE	BIT(5)
#घोषणा MACHINE_FLAG_EDAT1	BIT(7)
#घोषणा MACHINE_FLAG_EDAT2	BIT(8)
#घोषणा MACHINE_FLAG_TOPOLOGY	BIT(10)
#घोषणा MACHINE_FLAG_TE		BIT(11)
#घोषणा MACHINE_FLAG_TLB_LC	BIT(12)
#घोषणा MACHINE_FLAG_VX		BIT(13)
#घोषणा MACHINE_FLAG_TLB_GUEST	BIT(14)
#घोषणा MACHINE_FLAG_NX		BIT(15)
#घोषणा MACHINE_FLAG_GS		BIT(16)
#घोषणा MACHINE_FLAG_SCC	BIT(17)

#घोषणा LPP_MAGIC		BIT(31)
#घोषणा LPP_PID_MASK		_AC(0xffffffff, UL)

/* Offsets to entry poपूर्णांकs in kernel/head.S  */

#घोषणा STARTUP_NORMAL_OFFSET	0x10000
#घोषणा STARTUP_KDUMP_OFFSET	0x10010

/* Offsets to parameters in kernel/head.S  */

#घोषणा IPL_DEVICE_OFFSET	0x10400
#घोषणा INITRD_START_OFFSET	0x10408
#घोषणा INITRD_SIZE_OFFSET	0x10410
#घोषणा OLDMEM_BASE_OFFSET	0x10418
#घोषणा OLDMEM_SIZE_OFFSET	0x10420
#घोषणा KERNEL_VERSION_OFFSET	0x10428
#घोषणा COMMAND_LINE_OFFSET	0x10480

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/types.h>

#घोषणा IPL_DEVICE	(*(अचिन्हित दीर्घ *)  (IPL_DEVICE_OFFSET))
#घोषणा INITRD_START	(*(अचिन्हित दीर्घ *)  (INITRD_START_OFFSET))
#घोषणा INITRD_SIZE	(*(अचिन्हित दीर्घ *)  (INITRD_SIZE_OFFSET))
#घोषणा OLDMEM_BASE	(*(अचिन्हित दीर्घ *)  (OLDMEM_BASE_OFFSET))
#घोषणा OLDMEM_SIZE	(*(अचिन्हित दीर्घ *)  (OLDMEM_SIZE_OFFSET))
#घोषणा COMMAND_LINE	((अक्षर *)	     (COMMAND_LINE_OFFSET))

काष्ठा parmarea अणु
	अचिन्हित दीर्घ ipl_device;			/* 0x10400 */
	अचिन्हित दीर्घ initrd_start;			/* 0x10408 */
	अचिन्हित दीर्घ initrd_size;			/* 0x10410 */
	अचिन्हित दीर्घ oldmem_base;			/* 0x10418 */
	अचिन्हित दीर्घ oldmem_size;			/* 0x10420 */
	अचिन्हित दीर्घ kernel_version;			/* 0x10428 */
	अक्षर pad1[0x10480 - 0x10430];			/* 0x10430 - 0x10480 */
	अक्षर command_line[ARCH_COMMAND_LINE_SIZE];	/* 0x10480 */
पूर्ण;

बाह्य अचिन्हित पूर्णांक zlib_dfltcc_support;
#घोषणा ZLIB_DFLTCC_DISABLED		0
#घोषणा ZLIB_DFLTCC_FULL		1
#घोषणा ZLIB_DFLTCC_DEFLATE_ONLY	2
#घोषणा ZLIB_DFLTCC_INFLATE_ONLY	3
#घोषणा ZLIB_DFLTCC_FULL_DEBUG		4

बाह्य पूर्णांक noexec_disabled;
बाह्य अचिन्हित दीर्घ ident_map_size;
बाह्य अचिन्हित दीर्घ vदो_स्मृति_size;

/* The Write Back bit position in the physaddr is given by the SLPC PCI */
बाह्य अचिन्हित दीर्घ mio_wb_bit_mask;

#घोषणा MACHINE_IS_VM		(S390_lowcore.machine_flags & MACHINE_FLAG_VM)
#घोषणा MACHINE_IS_KVM		(S390_lowcore.machine_flags & MACHINE_FLAG_KVM)
#घोषणा MACHINE_IS_LPAR		(S390_lowcore.machine_flags & MACHINE_FLAG_LPAR)

#घोषणा MACHINE_HAS_DIAG9C	(S390_lowcore.machine_flags & MACHINE_FLAG_DIAG9C)
#घोषणा MACHINE_HAS_ESOP	(S390_lowcore.machine_flags & MACHINE_FLAG_ESOP)
#घोषणा MACHINE_HAS_IDTE	(S390_lowcore.machine_flags & MACHINE_FLAG_IDTE)
#घोषणा MACHINE_HAS_EDAT1	(S390_lowcore.machine_flags & MACHINE_FLAG_EDAT1)
#घोषणा MACHINE_HAS_EDAT2	(S390_lowcore.machine_flags & MACHINE_FLAG_EDAT2)
#घोषणा MACHINE_HAS_TOPOLOGY	(S390_lowcore.machine_flags & MACHINE_FLAG_TOPOLOGY)
#घोषणा MACHINE_HAS_TE		(S390_lowcore.machine_flags & MACHINE_FLAG_TE)
#घोषणा MACHINE_HAS_TLB_LC	(S390_lowcore.machine_flags & MACHINE_FLAG_TLB_LC)
#घोषणा MACHINE_HAS_VX		(S390_lowcore.machine_flags & MACHINE_FLAG_VX)
#घोषणा MACHINE_HAS_TLB_GUEST	(S390_lowcore.machine_flags & MACHINE_FLAG_TLB_GUEST)
#घोषणा MACHINE_HAS_NX		(S390_lowcore.machine_flags & MACHINE_FLAG_NX)
#घोषणा MACHINE_HAS_GS		(S390_lowcore.machine_flags & MACHINE_FLAG_GS)
#घोषणा MACHINE_HAS_SCC		(S390_lowcore.machine_flags & MACHINE_FLAG_SCC)

/*
 * Console mode. Override with conmode=
 */
बाह्य अचिन्हित पूर्णांक console_mode;
बाह्य अचिन्हित पूर्णांक console_devno;
बाह्य अचिन्हित पूर्णांक console_irq;

#घोषणा CONSOLE_IS_UNDEFINED	(console_mode == 0)
#घोषणा CONSOLE_IS_SCLP		(console_mode == 1)
#घोषणा CONSOLE_IS_3215		(console_mode == 2)
#घोषणा CONSOLE_IS_3270		(console_mode == 3)
#घोषणा CONSOLE_IS_VT220	(console_mode == 4)
#घोषणा CONSOLE_IS_HVC		(console_mode == 5)
#घोषणा SET_CONSOLE_SCLP	करो अणु console_mode = 1; पूर्ण जबतक (0)
#घोषणा SET_CONSOLE_3215	करो अणु console_mode = 2; पूर्ण जबतक (0)
#घोषणा SET_CONSOLE_3270	करो अणु console_mode = 3; पूर्ण जबतक (0)
#घोषणा SET_CONSOLE_VT220	करो अणु console_mode = 4; पूर्ण जबतक (0)
#घोषणा SET_CONSOLE_HVC		करो अणु console_mode = 5; पूर्ण जबतक (0)

#अगर_घोषित CONFIG_PFAULT
बाह्य पूर्णांक pfault_init(व्योम);
बाह्य व्योम pfault_fini(व्योम);
#अन्यथा /* CONFIG_PFAULT */
#घोषणा pfault_init()		(अणु-1;पूर्ण)
#घोषणा pfault_fini()		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_PFAULT */

#अगर_घोषित CONFIG_VMCP
व्योम vmcp_cma_reserve(व्योम);
#अन्यथा
अटल अंतरभूत व्योम vmcp_cma_reserve(व्योम) अणु पूर्ण
#पूर्ण_अगर

व्योम report_user_fault(काष्ठा pt_regs *regs, दीर्घ signr, पूर्णांक is_mm_fault);

व्योम cmma_init(व्योम);
व्योम cmma_init_nodat(व्योम);

बाह्य व्योम (*_machine_restart)(अक्षर *command);
बाह्य व्योम (*_machine_halt)(व्योम);
बाह्य व्योम (*_machine_घातer_off)(व्योम);

बाह्य अचिन्हित दीर्घ __kaslr_offset;
अटल अंतरभूत अचिन्हित दीर्घ kaslr_offset(व्योम)
अणु
	वापस __kaslr_offset;
पूर्ण

अटल अंतरभूत u32 gen_lpswe(अचिन्हित दीर्घ addr)
अणु
	BUILD_BUG_ON(addr > 0xfff);
	वापस 0xb2b20000 | addr;
पूर्ण

#अन्यथा /* __ASSEMBLY__ */

#घोषणा IPL_DEVICE	(IPL_DEVICE_OFFSET)
#घोषणा INITRD_START	(INITRD_START_OFFSET)
#घोषणा INITRD_SIZE	(INITRD_SIZE_OFFSET)
#घोषणा OLDMEM_BASE	(OLDMEM_BASE_OFFSET)
#घोषणा OLDMEM_SIZE	(OLDMEM_SIZE_OFFSET)
#घोषणा COMMAND_LINE	(COMMAND_LINE_OFFSET)

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_S390_SETUP_H */
