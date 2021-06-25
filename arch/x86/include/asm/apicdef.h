<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_APICDEF_H
#घोषणा _ASM_X86_APICDEF_H

/*
 * Constants क्रम various Intel APICs. (local APIC, IOAPIC, etc.)
 *
 * Alan Cox <Alan.Cox@linux.org>, 1995.
 * Ingo Molnar <mingo@redhat.com>, 1999, 2000
 */

#घोषणा IO_APIC_DEFAULT_PHYS_BASE	0xfec00000
#घोषणा	APIC_DEFAULT_PHYS_BASE		0xfee00000

/*
 * This is the IO-APIC रेजिस्टर space as specअगरied
 * by Intel करोcs:
 */
#घोषणा IO_APIC_SLOT_SIZE		1024

#घोषणा	APIC_ID		0x20

#घोषणा	APIC_LVR	0x30
#घोषणा		APIC_LVR_MASK		0xFF00FF
#घोषणा		APIC_LVR_सूचीECTED_EOI	(1 << 24)
#घोषणा		GET_APIC_VERSION(x)	((x) & 0xFFu)
#घोषणा		GET_APIC_MAXLVT(x)	(((x) >> 16) & 0xFFu)
#अगर_घोषित CONFIG_X86_32
#  define	APIC_INTEGRATED(x)	((x) & 0xF0u)
#अन्यथा
#  define	APIC_INTEGRATED(x)	(1)
#पूर्ण_अगर
#घोषणा		APIC_XAPIC(x)		((x) >= 0x14)
#घोषणा		APIC_EXT_SPACE(x)	((x) & 0x80000000)
#घोषणा	APIC_TASKPRI	0x80
#घोषणा		APIC_TPRI_MASK		0xFFu
#घोषणा	APIC_ARBPRI	0x90
#घोषणा		APIC_ARBPRI_MASK	0xFFu
#घोषणा	APIC_PROCPRI	0xA0
#घोषणा	APIC_EOI	0xB0
#घोषणा		APIC_EOI_ACK		0x0 /* Docs say 0 क्रम future compat. */
#घोषणा	APIC_RRR	0xC0
#घोषणा	APIC_LDR	0xD0
#घोषणा		APIC_LDR_MASK		(0xFFu << 24)
#घोषणा		GET_APIC_LOGICAL_ID(x)	(((x) >> 24) & 0xFFu)
#घोषणा		SET_APIC_LOGICAL_ID(x)	(((x) << 24))
#घोषणा		APIC_ALL_CPUS		0xFFu
#घोषणा	APIC_DFR	0xE0
#घोषणा		APIC_DFR_CLUSTER		0x0FFFFFFFul
#घोषणा		APIC_DFR_FLAT			0xFFFFFFFFul
#घोषणा	APIC_SPIV	0xF0
#घोषणा		APIC_SPIV_सूचीECTED_EOI		(1 << 12)
#घोषणा		APIC_SPIV_FOCUS_DISABLED	(1 << 9)
#घोषणा		APIC_SPIV_APIC_ENABLED		(1 << 8)
#घोषणा	APIC_ISR	0x100
#घोषणा	APIC_ISR_NR     0x8     /* Number of 32 bit ISR रेजिस्टरs. */
#घोषणा	APIC_TMR	0x180
#घोषणा	APIC_IRR	0x200
#घोषणा	APIC_ESR	0x280
#घोषणा		APIC_ESR_SEND_CS	0x00001
#घोषणा		APIC_ESR_RECV_CS	0x00002
#घोषणा		APIC_ESR_SEND_ACC	0x00004
#घोषणा		APIC_ESR_RECV_ACC	0x00008
#घोषणा		APIC_ESR_SENDILL	0x00020
#घोषणा		APIC_ESR_RECVILL	0x00040
#घोषणा		APIC_ESR_ILLREGA	0x00080
#घोषणा 	APIC_LVTCMCI	0x2f0
#घोषणा	APIC_ICR	0x300
#घोषणा		APIC_DEST_SELF		0x40000
#घोषणा		APIC_DEST_ALLINC	0x80000
#घोषणा		APIC_DEST_ALLBUT	0xC0000
#घोषणा		APIC_ICR_RR_MASK	0x30000
#घोषणा		APIC_ICR_RR_INVALID	0x00000
#घोषणा		APIC_ICR_RR_INPROG	0x10000
#घोषणा		APIC_ICR_RR_VALID	0x20000
#घोषणा		APIC_INT_LEVELTRIG	0x08000
#घोषणा		APIC_INT_ASSERT		0x04000
#घोषणा		APIC_ICR_BUSY		0x01000
#घोषणा		APIC_DEST_LOGICAL	0x00800
#घोषणा		APIC_DEST_PHYSICAL	0x00000
#घोषणा		APIC_DM_FIXED		0x00000
#घोषणा		APIC_DM_FIXED_MASK	0x00700
#घोषणा		APIC_DM_LOWEST		0x00100
#घोषणा		APIC_DM_SMI		0x00200
#घोषणा		APIC_DM_REMRD		0x00300
#घोषणा		APIC_DM_NMI		0x00400
#घोषणा		APIC_DM_INIT		0x00500
#घोषणा		APIC_DM_STARTUP		0x00600
#घोषणा		APIC_DM_EXTINT		0x00700
#घोषणा		APIC_VECTOR_MASK	0x000FF
#घोषणा	APIC_ICR2	0x310
#घोषणा		GET_APIC_DEST_FIELD(x)	(((x) >> 24) & 0xFF)
#घोषणा		SET_APIC_DEST_FIELD(x)	((x) << 24)
#घोषणा	APIC_LVTT	0x320
#घोषणा	APIC_LVTTHMR	0x330
#घोषणा	APIC_LVTPC	0x340
#घोषणा	APIC_LVT0	0x350
#घोषणा		APIC_LVT_TIMER_BASE_MASK	(0x3 << 18)
#घोषणा		GET_APIC_TIMER_BASE(x)		(((x) >> 18) & 0x3)
#घोषणा		SET_APIC_TIMER_BASE(x)		(((x) << 18))
#घोषणा		APIC_TIMER_BASE_CLKIN		0x0
#घोषणा		APIC_TIMER_BASE_TMBASE		0x1
#घोषणा		APIC_TIMER_BASE_DIV		0x2
#घोषणा		APIC_LVT_TIMER_ONESHOT		(0 << 17)
#घोषणा		APIC_LVT_TIMER_PERIODIC		(1 << 17)
#घोषणा		APIC_LVT_TIMER_TSCDEADLINE	(2 << 17)
#घोषणा		APIC_LVT_MASKED			(1 << 16)
#घोषणा		APIC_LVT_LEVEL_TRIGGER		(1 << 15)
#घोषणा		APIC_LVT_REMOTE_IRR		(1 << 14)
#घोषणा		APIC_INPUT_POLARITY		(1 << 13)
#घोषणा		APIC_SEND_PENDING		(1 << 12)
#घोषणा		APIC_MODE_MASK			0x700
#घोषणा		GET_APIC_DELIVERY_MODE(x)	(((x) >> 8) & 0x7)
#घोषणा		SET_APIC_DELIVERY_MODE(x, y)	(((x) & ~0x700) | ((y) << 8))
#घोषणा			APIC_MODE_FIXED		0x0
#घोषणा			APIC_MODE_NMI		0x4
#घोषणा			APIC_MODE_EXTINT	0x7
#घोषणा	APIC_LVT1	0x360
#घोषणा	APIC_LVTERR	0x370
#घोषणा	APIC_TMICT	0x380
#घोषणा	APIC_TMCCT	0x390
#घोषणा	APIC_TDCR	0x3E0
#घोषणा APIC_SELF_IPI	0x3F0
#घोषणा		APIC_TDR_DIV_TMBASE	(1 << 2)
#घोषणा		APIC_TDR_DIV_1		0xB
#घोषणा		APIC_TDR_DIV_2		0x0
#घोषणा		APIC_TDR_DIV_4		0x1
#घोषणा		APIC_TDR_DIV_8		0x2
#घोषणा		APIC_TDR_DIV_16		0x3
#घोषणा		APIC_TDR_DIV_32		0x8
#घोषणा		APIC_TDR_DIV_64		0x9
#घोषणा		APIC_TDR_DIV_128	0xA
#घोषणा	APIC_EFEAT	0x400
#घोषणा	APIC_ECTRL	0x410
#घोषणा APIC_EILVTn(n)	(0x500 + 0x10 * n)
#घोषणा		APIC_EILVT_NR_AMD_K8	1	/* # of extended पूर्णांकerrupts */
#घोषणा		APIC_EILVT_NR_AMD_10H	4
#घोषणा		APIC_EILVT_NR_MAX	APIC_EILVT_NR_AMD_10H
#घोषणा		APIC_EILVT_LVTOFF(x)	(((x) >> 4) & 0xF)
#घोषणा		APIC_EILVT_MSG_FIX	0x0
#घोषणा		APIC_EILVT_MSG_SMI	0x2
#घोषणा		APIC_EILVT_MSG_NMI	0x4
#घोषणा		APIC_EILVT_MSG_EXT	0x7
#घोषणा		APIC_EILVT_MASKED	(1 << 16)

#घोषणा APIC_BASE (fix_to_virt(FIX_APIC_BASE))
#घोषणा APIC_BASE_MSR	0x800
#घोषणा XAPIC_ENABLE	(1UL << 11)
#घोषणा X2APIC_ENABLE	(1UL << 10)

#अगर_घोषित CONFIG_X86_32
# define MAX_IO_APICS 64
# define MAX_LOCAL_APIC 256
#अन्यथा
# define MAX_IO_APICS 128
# define MAX_LOCAL_APIC 32768
#पूर्ण_अगर

/*
 * All x86-64 प्रणालीs are xAPIC compatible.
 * In the following, "apicid" is a physical APIC ID.
 */
#घोषणा XAPIC_DEST_CPUS_SHIFT	4
#घोषणा XAPIC_DEST_CPUS_MASK	((1u << XAPIC_DEST_CPUS_SHIFT) - 1)
#घोषणा XAPIC_DEST_CLUSTER_MASK	(XAPIC_DEST_CPUS_MASK << XAPIC_DEST_CPUS_SHIFT)
#घोषणा APIC_CLUSTER(apicid)	((apicid) & XAPIC_DEST_CLUSTER_MASK)
#घोषणा APIC_CLUSTERID(apicid)	(APIC_CLUSTER(apicid) >> XAPIC_DEST_CPUS_SHIFT)
#घोषणा APIC_CPUID(apicid)	((apicid) & XAPIC_DEST_CPUS_MASK)
#घोषणा NUM_APIC_CLUSTERS	((BAD_APICID + 1) >> XAPIC_DEST_CPUS_SHIFT)

/*
 * the local APIC रेजिस्टर काष्ठाure, memory mapped. Not terribly well
 * tested, but we might eventually use this one in the future - the
 * problem why we cannot use it right now is the P5 APIC, it has an
 * errata which cannot take 8-bit पढ़ोs and ग_लिखोs, only 32-bit ones ...
 */
#घोषणा u32 अचिन्हित पूर्णांक

काष्ठा local_apic अणु

/*000*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_01;

/*010*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_02;

/*020*/	काष्ठा अणु /* APIC ID Register */
		u32   __reserved_1	: 24,
			phys_apic_id	:  4,
			__reserved_2	:  4;
		u32 __reserved[3];
	पूर्ण id;

/*030*/	स्थिर
	काष्ठा अणु /* APIC Version Register */
		u32   version		:  8,
			__reserved_1	:  8,
			max_lvt		:  8,
			__reserved_2	:  8;
		u32 __reserved[3];
	पूर्ण version;

/*040*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_03;

/*050*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_04;

/*060*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_05;

/*070*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_06;

/*080*/	काष्ठा अणु /* Task Priority Register */
		u32   priority	:  8,
			__reserved_1	: 24;
		u32 __reserved_2[3];
	पूर्ण tpr;

/*090*/	स्थिर
	काष्ठा अणु /* Arbitration Priority Register */
		u32   priority	:  8,
			__reserved_1	: 24;
		u32 __reserved_2[3];
	पूर्ण apr;

/*0A0*/	स्थिर
	काष्ठा अणु /* Processor Priority Register */
		u32   priority	:  8,
			__reserved_1	: 24;
		u32 __reserved_2[3];
	पूर्ण ppr;

/*0B0*/	काष्ठा अणु /* End Of Interrupt Register */
		u32   eoi;
		u32 __reserved[3];
	पूर्ण eoi;

/*0C0*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_07;

/*0D0*/	काष्ठा अणु /* Logical Destination Register */
		u32   __reserved_1	: 24,
			logical_dest	:  8;
		u32 __reserved_2[3];
	पूर्ण ldr;

/*0E0*/	काष्ठा अणु /* Destination Format Register */
		u32   __reserved_1	: 28,
			model		:  4;
		u32 __reserved_2[3];
	पूर्ण dfr;

/*0F0*/	काष्ठा अणु /* Spurious Interrupt Vector Register */
		u32	spurious_vector	:  8,
			apic_enabled	:  1,
			focus_cpu	:  1,
			__reserved_2	: 22;
		u32 __reserved_3[3];
	पूर्ण svr;

/*100*/	काष्ठा अणु /* In Service Register */
/*170*/		u32 bitfield;
		u32 __reserved[3];
	पूर्ण isr [8];

/*180*/	काष्ठा अणु /* Trigger Mode Register */
/*1F0*/		u32 bitfield;
		u32 __reserved[3];
	पूर्ण पंचांगr [8];

/*200*/	काष्ठा अणु /* Interrupt Request Register */
/*270*/		u32 bitfield;
		u32 __reserved[3];
	पूर्ण irr [8];

/*280*/	जोड़ अणु /* Error Status Register */
		काष्ठा अणु
			u32   send_cs_error			:  1,
				receive_cs_error		:  1,
				send_accept_error		:  1,
				receive_accept_error		:  1,
				__reserved_1			:  1,
				send_illegal_vector		:  1,
				receive_illegal_vector		:  1,
				illegal_रेजिस्टर_address	:  1,
				__reserved_2			: 24;
			u32 __reserved_3[3];
		पूर्ण error_bits;
		काष्ठा अणु
			u32 errors;
			u32 __reserved_3[3];
		पूर्ण all_errors;
	पूर्ण esr;

/*290*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_08;

/*2A0*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_09;

/*2B0*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_10;

/*2C0*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_11;

/*2D0*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_12;

/*2E0*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_13;

/*2F0*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_14;

/*300*/	काष्ठा अणु /* Interrupt Command Register 1 */
		u32   vector			:  8,
			delivery_mode		:  3,
			destination_mode	:  1,
			delivery_status		:  1,
			__reserved_1		:  1,
			level			:  1,
			trigger			:  1,
			__reserved_2		:  2,
			लघुhand		:  2,
			__reserved_3		:  12;
		u32 __reserved_4[3];
	पूर्ण icr1;

/*310*/	काष्ठा अणु /* Interrupt Command Register 2 */
		जोड़ अणु
			u32   __reserved_1	: 24,
				phys_dest	:  4,
				__reserved_2	:  4;
			u32   __reserved_3	: 24,
				logical_dest	:  8;
		पूर्ण dest;
		u32 __reserved_4[3];
	पूर्ण icr2;

/*320*/	काष्ठा अणु /* LVT - Timer */
		u32   vector		:  8,
			__reserved_1	:  4,
			delivery_status	:  1,
			__reserved_2	:  3,
			mask		:  1,
			समयr_mode	:  1,
			__reserved_3	: 14;
		u32 __reserved_4[3];
	पूर्ण lvt_समयr;

/*330*/	काष्ठा अणु /* LVT - Thermal Sensor */
		u32  vector		:  8,
			delivery_mode	:  3,
			__reserved_1	:  1,
			delivery_status	:  1,
			__reserved_2	:  3,
			mask		:  1,
			__reserved_3	: 15;
		u32 __reserved_4[3];
	पूर्ण lvt_thermal;

/*340*/	काष्ठा अणु /* LVT - Perक्रमmance Counter */
		u32   vector		:  8,
			delivery_mode	:  3,
			__reserved_1	:  1,
			delivery_status	:  1,
			__reserved_2	:  3,
			mask		:  1,
			__reserved_3	: 15;
		u32 __reserved_4[3];
	पूर्ण lvt_pc;

/*350*/	काष्ठा अणु /* LVT - LINT0 */
		u32   vector		:  8,
			delivery_mode	:  3,
			__reserved_1	:  1,
			delivery_status	:  1,
			polarity	:  1,
			remote_irr	:  1,
			trigger		:  1,
			mask		:  1,
			__reserved_2	: 15;
		u32 __reserved_3[3];
	पूर्ण lvt_lपूर्णांक0;

/*360*/	काष्ठा अणु /* LVT - LINT1 */
		u32   vector		:  8,
			delivery_mode	:  3,
			__reserved_1	:  1,
			delivery_status	:  1,
			polarity	:  1,
			remote_irr	:  1,
			trigger		:  1,
			mask		:  1,
			__reserved_2	: 15;
		u32 __reserved_3[3];
	पूर्ण lvt_lपूर्णांक1;

/*370*/	काष्ठा अणु /* LVT - Error */
		u32   vector		:  8,
			__reserved_1	:  4,
			delivery_status	:  1,
			__reserved_2	:  3,
			mask		:  1,
			__reserved_3	: 15;
		u32 __reserved_4[3];
	पूर्ण lvt_error;

/*380*/	काष्ठा अणु /* Timer Initial Count Register */
		u32   initial_count;
		u32 __reserved_2[3];
	पूर्ण समयr_icr;

/*390*/	स्थिर
	काष्ठा अणु /* Timer Current Count Register */
		u32   curr_count;
		u32 __reserved_2[3];
	पूर्ण समयr_ccr;

/*3A0*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_16;

/*3B0*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_17;

/*3C0*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_18;

/*3D0*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_19;

/*3E0*/	काष्ठा अणु /* Timer Divide Configuration Register */
		u32   भागisor		:  4,
			__reserved_1	: 28;
		u32 __reserved_2[3];
	पूर्ण समयr_dcr;

/*3F0*/	काष्ठा अणु u32 __reserved[4]; पूर्ण __reserved_20;

पूर्ण __attribute__ ((packed));

#अघोषित u32

#अगर_घोषित CONFIG_X86_32
 #घोषणा BAD_APICID 0xFFu
#अन्यथा
 #घोषणा BAD_APICID 0xFFFFu
#पूर्ण_अगर

क्रमागत apic_delivery_modes अणु
	APIC_DELIVERY_MODE_FIXED	= 0,
	APIC_DELIVERY_MODE_LOWESTPRIO   = 1,
	APIC_DELIVERY_MODE_SMI		= 2,
	APIC_DELIVERY_MODE_NMI		= 4,
	APIC_DELIVERY_MODE_INIT		= 5,
	APIC_DELIVERY_MODE_EXTINT	= 7,
पूर्ण;

#पूर्ण_अगर /* _ASM_X86_APICDEF_H */
