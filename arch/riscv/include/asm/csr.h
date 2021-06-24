<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_CSR_H
#घोषणा _ASM_RISCV_CSR_H

#समावेश <यंत्र/यंत्र.h>
#समावेश <linux/स्थिर.h>

/* Status रेजिस्टर flags */
#घोषणा SR_SIE		_AC(0x00000002, UL) /* Supervisor Interrupt Enable */
#घोषणा SR_MIE		_AC(0x00000008, UL) /* Machine Interrupt Enable */
#घोषणा SR_SPIE		_AC(0x00000020, UL) /* Previous Supervisor IE */
#घोषणा SR_MPIE		_AC(0x00000080, UL) /* Previous Machine IE */
#घोषणा SR_SPP		_AC(0x00000100, UL) /* Previously Supervisor */
#घोषणा SR_MPP		_AC(0x00001800, UL) /* Previously Machine */
#घोषणा SR_SUM		_AC(0x00040000, UL) /* Supervisor User Memory Access */

#घोषणा SR_FS		_AC(0x00006000, UL) /* Floating-poपूर्णांक Status */
#घोषणा SR_FS_OFF	_AC(0x00000000, UL)
#घोषणा SR_FS_INITIAL	_AC(0x00002000, UL)
#घोषणा SR_FS_CLEAN	_AC(0x00004000, UL)
#घोषणा SR_FS_सूचीTY	_AC(0x00006000, UL)

#घोषणा SR_XS		_AC(0x00018000, UL) /* Extension Status */
#घोषणा SR_XS_OFF	_AC(0x00000000, UL)
#घोषणा SR_XS_INITIAL	_AC(0x00008000, UL)
#घोषणा SR_XS_CLEAN	_AC(0x00010000, UL)
#घोषणा SR_XS_सूचीTY	_AC(0x00018000, UL)

#अगर_अघोषित CONFIG_64BIT
#घोषणा SR_SD		_AC(0x80000000, UL) /* FS/XS dirty */
#अन्यथा
#घोषणा SR_SD		_AC(0x8000000000000000, UL) /* FS/XS dirty */
#पूर्ण_अगर

/* SATP flags */
#अगर_अघोषित CONFIG_64BIT
#घोषणा SATP_PPN	_AC(0x003FFFFF, UL)
#घोषणा SATP_MODE_32	_AC(0x80000000, UL)
#घोषणा SATP_MODE	SATP_MODE_32
#घोषणा SATP_ASID_BITS	9
#घोषणा SATP_ASID_SHIFT	22
#घोषणा SATP_ASID_MASK	_AC(0x1FF, UL)
#अन्यथा
#घोषणा SATP_PPN	_AC(0x00000FFFFFFFFFFF, UL)
#घोषणा SATP_MODE_39	_AC(0x8000000000000000, UL)
#घोषणा SATP_MODE	SATP_MODE_39
#घोषणा SATP_ASID_BITS	16
#घोषणा SATP_ASID_SHIFT	44
#घोषणा SATP_ASID_MASK	_AC(0xFFFF, UL)
#पूर्ण_अगर

/* Exception cause high bit - is an पूर्णांकerrupt अगर set */
#घोषणा CAUSE_IRQ_FLAG		(_AC(1, UL) << (__riscv_xlen - 1))

/* Interrupt causes (minus the high bit) */
#घोषणा IRQ_S_SOFT		1
#घोषणा IRQ_M_SOFT		3
#घोषणा IRQ_S_TIMER		5
#घोषणा IRQ_M_TIMER		7
#घोषणा IRQ_S_EXT		9
#घोषणा IRQ_M_EXT		11

/* Exception causes */
#घोषणा EXC_INST_MISALIGNED	0
#घोषणा EXC_INST_ACCESS		1
#घोषणा EXC_BREAKPOINT		3
#घोषणा EXC_LOAD_ACCESS		5
#घोषणा EXC_STORE_ACCESS	7
#घोषणा EXC_SYSCALL		8
#घोषणा EXC_INST_PAGE_FAULT	12
#घोषणा EXC_LOAD_PAGE_FAULT	13
#घोषणा EXC_STORE_PAGE_FAULT	15

/* PMP configuration */
#घोषणा PMP_R			0x01
#घोषणा PMP_W			0x02
#घोषणा PMP_X			0x04
#घोषणा PMP_A			0x18
#घोषणा PMP_A_TOR		0x08
#घोषणा PMP_A_NA4		0x10
#घोषणा PMP_A_NAPOT		0x18
#घोषणा PMP_L			0x80

/* symbolic CSR names: */
#घोषणा CSR_CYCLE		0xc00
#घोषणा CSR_TIME		0xc01
#घोषणा CSR_INSTRET		0xc02
#घोषणा CSR_CYCLEH		0xc80
#घोषणा CSR_TIMEH		0xc81
#घोषणा CSR_INSTRETH		0xc82

#घोषणा CSR_SSTATUS		0x100
#घोषणा CSR_SIE			0x104
#घोषणा CSR_STVEC		0x105
#घोषणा CSR_SCOUNTEREN		0x106
#घोषणा CSR_SSCRATCH		0x140
#घोषणा CSR_SEPC		0x141
#घोषणा CSR_SCAUSE		0x142
#घोषणा CSR_STVAL		0x143
#घोषणा CSR_SIP			0x144
#घोषणा CSR_SATP		0x180

#घोषणा CSR_MSTATUS		0x300
#घोषणा CSR_MISA		0x301
#घोषणा CSR_MIE			0x304
#घोषणा CSR_MTVEC		0x305
#घोषणा CSR_MSCRATCH		0x340
#घोषणा CSR_MEPC		0x341
#घोषणा CSR_MCAUSE		0x342
#घोषणा CSR_MTVAL		0x343
#घोषणा CSR_MIP			0x344
#घोषणा CSR_PMPCFG0		0x3a0
#घोषणा CSR_PMPADDR0		0x3b0
#घोषणा CSR_MVENDORID		0xf11
#घोषणा CSR_MARCHID		0xf12
#घोषणा CSR_MIMPID		0xf13
#घोषणा CSR_MHARTID		0xf14

#अगर_घोषित CONFIG_RISCV_M_MODE
# define CSR_STATUS	CSR_MSTATUS
# define CSR_IE		CSR_MIE
# define CSR_TVEC	CSR_MTVEC
# define CSR_SCRATCH	CSR_MSCRATCH
# define CSR_EPC	CSR_MEPC
# define CSR_CAUSE	CSR_MCAUSE
# define CSR_TVAL	CSR_MTVAL
# define CSR_IP		CSR_MIP

# define SR_IE		SR_MIE
# define SR_PIE		SR_MPIE
# define SR_PP		SR_MPP

# define RV_IRQ_SOFT		IRQ_M_SOFT
# define RV_IRQ_TIMER	IRQ_M_TIMER
# define RV_IRQ_EXT		IRQ_M_EXT
#अन्यथा /* CONFIG_RISCV_M_MODE */
# define CSR_STATUS	CSR_SSTATUS
# define CSR_IE		CSR_SIE
# define CSR_TVEC	CSR_STVEC
# define CSR_SCRATCH	CSR_SSCRATCH
# define CSR_EPC	CSR_SEPC
# define CSR_CAUSE	CSR_SCAUSE
# define CSR_TVAL	CSR_STVAL
# define CSR_IP		CSR_SIP

# define SR_IE		SR_SIE
# define SR_PIE		SR_SPIE
# define SR_PP		SR_SPP

# define RV_IRQ_SOFT		IRQ_S_SOFT
# define RV_IRQ_TIMER	IRQ_S_TIMER
# define RV_IRQ_EXT		IRQ_S_EXT
#पूर्ण_अगर /* CONFIG_RISCV_M_MODE */

/* IE/IP (Supervisor/Machine Interrupt Enable/Pending) flags */
#घोषणा IE_SIE		(_AC(0x1, UL) << RV_IRQ_SOFT)
#घोषणा IE_TIE		(_AC(0x1, UL) << RV_IRQ_TIMER)
#घोषणा IE_EIE		(_AC(0x1, UL) << RV_IRQ_EXT)

#अगर_अघोषित __ASSEMBLY__

#घोषणा csr_swap(csr, val)					\
(अणु								\
	अचिन्हित दीर्घ __v = (अचिन्हित दीर्घ)(val);		\
	__यंत्र__ __अस्थिर__ ("csrrw %0, " __ASM_STR(csr) ", %1"\
			      : "=r" (__v) : "rK" (__v)		\
			      : "memory");			\
	__v;							\
पूर्ण)

#घोषणा csr_पढ़ो(csr)						\
(अणु								\
	रेजिस्टर अचिन्हित दीर्घ __v;				\
	__यंत्र__ __अस्थिर__ ("csrr %0, " __ASM_STR(csr)	\
			      : "=r" (__v) :			\
			      : "memory");			\
	__v;							\
पूर्ण)

#घोषणा csr_ग_लिखो(csr, val)					\
(अणु								\
	अचिन्हित दीर्घ __v = (अचिन्हित दीर्घ)(val);		\
	__यंत्र__ __अस्थिर__ ("csrw " __ASM_STR(csr) ", %0"	\
			      : : "rK" (__v)			\
			      : "memory");			\
पूर्ण)

#घोषणा csr_पढ़ो_set(csr, val)					\
(अणु								\
	अचिन्हित दीर्घ __v = (अचिन्हित दीर्घ)(val);		\
	__यंत्र__ __अस्थिर__ ("csrrs %0, " __ASM_STR(csr) ", %1"\
			      : "=r" (__v) : "rK" (__v)		\
			      : "memory");			\
	__v;							\
पूर्ण)

#घोषणा csr_set(csr, val)					\
(अणु								\
	अचिन्हित दीर्घ __v = (अचिन्हित दीर्घ)(val);		\
	__यंत्र__ __अस्थिर__ ("csrs " __ASM_STR(csr) ", %0"	\
			      : : "rK" (__v)			\
			      : "memory");			\
पूर्ण)

#घोषणा csr_पढ़ो_clear(csr, val)				\
(अणु								\
	अचिन्हित दीर्घ __v = (अचिन्हित दीर्घ)(val);		\
	__यंत्र__ __अस्थिर__ ("csrrc %0, " __ASM_STR(csr) ", %1"\
			      : "=r" (__v) : "rK" (__v)		\
			      : "memory");			\
	__v;							\
पूर्ण)

#घोषणा csr_clear(csr, val)					\
(अणु								\
	अचिन्हित दीर्घ __v = (अचिन्हित दीर्घ)(val);		\
	__यंत्र__ __अस्थिर__ ("csrc " __ASM_STR(csr) ", %0"	\
			      : : "rK" (__v)			\
			      : "memory");			\
पूर्ण)

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_RISCV_CSR_H */
