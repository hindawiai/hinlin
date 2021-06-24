<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_MPSPEC_DEF_H
#घोषणा _ASM_X86_MPSPEC_DEF_H

/*
 * Structure definitions क्रम SMP machines following the
 * Intel Multiprocessing Specअगरication 1.1 and 1.4.
 */

/*
 * This tag identअगरies where the SMP configuration
 * inक्रमmation is.
 */

#घोषणा SMP_MAGIC_IDENT	(('_'<<24) | ('P'<<16) | ('M'<<8) | '_')

#अगर_घोषित CONFIG_X86_32
# define MAX_MPC_ENTRY 1024
#पूर्ण_अगर

/* Intel MP Floating Poपूर्णांकer Structure */
काष्ठा mpf_पूर्णांकel अणु
	अक्षर signature[4];		/* "_MP_"			*/
	अचिन्हित पूर्णांक physptr;		/* Configuration table address	*/
	अचिन्हित अक्षर length;		/* Our length (paragraphs)	*/
	अचिन्हित अक्षर specअगरication;	/* Specअगरication version	*/
	अचिन्हित अक्षर checksum;		/* Checksum (makes sum 0)	*/
	अचिन्हित अक्षर feature1;		/* Standard or configuration ?	*/
	अचिन्हित अक्षर feature2;		/* Bit7 set क्रम IMCR|PIC	*/
	अचिन्हित अक्षर feature3;		/* Unused (0)			*/
	अचिन्हित अक्षर feature4;		/* Unused (0)			*/
	अचिन्हित अक्षर feature5;		/* Unused (0)			*/
पूर्ण;

#घोषणा MPC_SIGNATURE "PCMP"

काष्ठा mpc_table अणु
	अक्षर signature[4];
	अचिन्हित लघु length;		/* Size of table */
	अक्षर spec;			/* 0x01 */
	अक्षर checksum;
	अक्षर oem[8];
	अक्षर productid[12];
	अचिन्हित पूर्णांक oemptr;		/* 0 अगर not present */
	अचिन्हित लघु oemsize;		/* 0 अगर not present */
	अचिन्हित लघु oemcount;
	अचिन्हित पूर्णांक lapic;		/* APIC address */
	अचिन्हित पूर्णांक reserved;
पूर्ण;

/* Followed by entries */

#घोषणा	MP_PROCESSOR		0
#घोषणा	MP_BUS			1
#घोषणा	MP_IOAPIC		2
#घोषणा	MP_INTSRC		3
#घोषणा	MP_LINTSRC		4
/* Used by IBM NUMA-Q to describe node locality */
#घोषणा	MP_TRANSLATION		192

#घोषणा CPU_ENABLED		1	/* Processor is available */
#घोषणा CPU_BOOTPROCESSOR	2	/* Processor is the boot CPU */

#घोषणा CPU_STEPPING_MASK	0x000F
#घोषणा CPU_MODEL_MASK		0x00F0
#घोषणा CPU_FAMILY_MASK		0x0F00

काष्ठा mpc_cpu अणु
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर apicid;		/* Local APIC number */
	अचिन्हित अक्षर apicver;		/* Its versions */
	अचिन्हित अक्षर cpuflag;
	अचिन्हित पूर्णांक cpufeature;
	अचिन्हित पूर्णांक featureflag;	/* CPUID feature value */
	अचिन्हित पूर्णांक reserved[2];
पूर्ण;

काष्ठा mpc_bus अणु
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर busid;
	अचिन्हित अक्षर bustype[6];
पूर्ण;

/* List of Bus Type string values, Intel MP Spec. */
#घोषणा BUSTYPE_EISA	"EISA"
#घोषणा BUSTYPE_ISA	"ISA"
#घोषणा BUSTYPE_INTERN	"INTERN"	/* Internal BUS */
#घोषणा BUSTYPE_MCA	"MCA"		/* Obsolete */
#घोषणा BUSTYPE_VL	"VL"		/* Local bus */
#घोषणा BUSTYPE_PCI	"PCI"
#घोषणा BUSTYPE_PCMCIA	"PCMCIA"
#घोषणा BUSTYPE_CBUS	"CBUS"
#घोषणा BUSTYPE_CBUSII	"CBUSII"
#घोषणा BUSTYPE_FUTURE	"FUTURE"
#घोषणा BUSTYPE_MBI	"MBI"
#घोषणा BUSTYPE_MBII	"MBII"
#घोषणा BUSTYPE_MPI	"MPI"
#घोषणा BUSTYPE_MPSA	"MPSA"
#घोषणा BUSTYPE_NUBUS	"NUBUS"
#घोषणा BUSTYPE_TC	"TC"
#घोषणा BUSTYPE_VME	"VME"
#घोषणा BUSTYPE_XPRESS	"XPRESS"

#घोषणा MPC_APIC_USABLE		0x01

काष्ठा mpc_ioapic अणु
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर apicid;
	अचिन्हित अक्षर apicver;
	अचिन्हित अक्षर flags;
	अचिन्हित पूर्णांक apicaddr;
पूर्ण;

काष्ठा mpc_पूर्णांकsrc अणु
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर irqtype;
	अचिन्हित लघु irqflag;
	अचिन्हित अक्षर srcbus;
	अचिन्हित अक्षर srcbusirq;
	अचिन्हित अक्षर dstapic;
	अचिन्हित अक्षर dstirq;
पूर्ण;

क्रमागत mp_irq_source_types अणु
	mp_INT = 0,
	mp_NMI = 1,
	mp_SMI = 2,
	mp_ExtINT = 3
पूर्ण;

#घोषणा MP_IRQPOL_DEFAULT	0x0
#घोषणा MP_IRQPOL_ACTIVE_HIGH	0x1
#घोषणा MP_IRQPOL_RESERVED	0x2
#घोषणा MP_IRQPOL_ACTIVE_LOW	0x3
#घोषणा MP_IRQPOL_MASK		0x3

#घोषणा MP_IRQTRIG_DEFAULT	0x0
#घोषणा MP_IRQTRIG_EDGE		0x4
#घोषणा MP_IRQTRIG_RESERVED	0x8
#घोषणा MP_IRQTRIG_LEVEL	0xc
#घोषणा MP_IRQTRIG_MASK		0xc

#घोषणा MP_APIC_ALL	0xFF

काष्ठा mpc_lपूर्णांकsrc अणु
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर irqtype;
	अचिन्हित लघु irqflag;
	अचिन्हित अक्षर srcbusid;
	अचिन्हित अक्षर srcbusirq;
	अचिन्हित अक्षर destapic;
	अचिन्हित अक्षर destapiclपूर्णांक;
पूर्ण;

#घोषणा MPC_OEM_SIGNATURE "_OEM"

काष्ठा mpc_oemtable अणु
	अक्षर signature[4];
	अचिन्हित लघु length;		/* Size of table */
	अक्षर  rev;			/* 0x01 */
	अक्षर  checksum;
	अक्षर  mpc[8];
पूर्ण;

/*
 *	Default configurations
 *
 *	1	2 CPU ISA 82489DX
 *	2	2 CPU EISA 82489DX neither IRQ 0 समयr nor IRQ 13 DMA chaining
 *	3	2 CPU EISA 82489DX
 *	4	2 CPU MCA 82489DX
 *	5	2 CPU ISA+PCI
 *	6	2 CPU EISA+PCI
 *	7	2 CPU MCA+PCI
 */

क्रमागत mp_bustype अणु
	MP_BUS_ISA = 1,
	MP_BUS_EISA,
	MP_BUS_PCI,
पूर्ण;
#पूर्ण_अगर /* _ASM_X86_MPSPEC_DEF_H */
