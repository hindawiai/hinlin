<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_IO_H
#घोषणा _ASM_POWERPC_IO_H
#अगर_घोषित __KERNEL__

#घोषणा ARCH_HAS_IOREMAP_WC
#अगर_घोषित CONFIG_PPC32
#घोषणा ARCH_HAS_IOREMAP_WT
#पूर्ण_अगर

/*
 */

/* Check of existence of legacy devices */
बाह्य पूर्णांक check_legacy_ioport(अचिन्हित दीर्घ base_port);
#घोषणा I8042_DATA_REG	0x60
#घोषणा FDC_BASE	0x3f0

#अगर defined(CONFIG_PPC64) && defined(CONFIG_PCI)
बाह्य काष्ठा pci_dev *isa_bridge_pcidev;
/*
 * has legacy ISA devices ?
 */
#घोषणा arch_has_dev_port()	(isa_bridge_pcidev != शून्य || isa_io_special)
#पूर्ण_अगर

#समावेश <linux/device.h>
#समावेश <linux/compiler.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/synch.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/mmiowb.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/ppc_यंत्र.h>

#घोषणा SIO_CONFIG_RA	0x398
#घोषणा SIO_CONFIG_RD	0x399

#घोषणा SLOW_DOWN_IO

/* 32 bits uses slightly dअगरferent variables क्रम the various IO
 * bases. Most of this file only uses _IO_BASE though which we
 * define properly based on the platक्रमm
 */
#अगर_अघोषित CONFIG_PCI
#घोषणा _IO_BASE	0
#घोषणा _ISA_MEM_BASE	0
#घोषणा PCI_DRAM_OFFSET 0
#या_अगर defined(CONFIG_PPC32)
#घोषणा _IO_BASE	isa_io_base
#घोषणा _ISA_MEM_BASE	isa_mem_base
#घोषणा PCI_DRAM_OFFSET	pci_dram_offset
#अन्यथा
#घोषणा _IO_BASE	pci_io_base
#घोषणा _ISA_MEM_BASE	isa_mem_base
#घोषणा PCI_DRAM_OFFSET	0
#पूर्ण_अगर

बाह्य अचिन्हित दीर्घ isa_io_base;
बाह्य अचिन्हित दीर्घ pci_io_base;
बाह्य अचिन्हित दीर्घ pci_dram_offset;

बाह्य resource_माप_प्रकार isa_mem_base;

/* Boolean set by platक्रमm अगर PIO accesses are suppored जबतक _IO_BASE
 * is not set or addresses cannot be translated to MMIO. This is typically
 * set when the platक्रमm supports "special" PIO accesses via a non memory
 * mapped mechanism, and allows things like the early udbg UART code to
 * function.
 */
बाह्य bool isa_io_special;

#अगर_घोषित CONFIG_PPC32
#अगर defined(CONFIG_PPC_INसूचीECT_PIO) || defined(CONFIG_PPC_INसूचीECT_MMIO)
#त्रुटि CONFIG_PPC_INसूचीECT_अणुPIO,MMIOपूर्ण are not yet supported on 32 bits
#पूर्ण_अगर
#पूर्ण_अगर

/*
 *
 * Low level MMIO accessors
 *
 * This provides the non-bus specअगरic accessors to MMIO. Those are PowerPC
 * specअगरic and thus shouldn't be used in generic code. The accessors
 * provided here are:
 *
 *	in_8, in_le16, in_be16, in_le32, in_be32, in_le64, in_be64
 *	out_8, out_le16, out_be16, out_le32, out_be32, out_le64, out_be64
 *	_insb, _insw_ns, _insl_ns, _outsb, _outsw_ns, _outsl_ns
 *
 * Those operate directly on a kernel भव address. Note that the prototype
 * क्रम the out_* accessors has the arguments in opposite order from the usual
 * linux PCI accessors. Unlike those, they take the address first and the value
 * next.
 *
 * Note: I might drop the _ns suffix on the stream operations soon as it is
 * simply normal क्रम stream operations to not swap in the first place.
 *
 */

#घोषणा DEF_MMIO_IN_X(name, size, insn)				\
अटल अंतरभूत u##size name(स्थिर अस्थिर u##size __iomem *addr)	\
अणु									\
	u##size ret;							\
	__यंत्र__ __अस्थिर__("sync;"#insn" %0,%y1;twi 0,%0,0;isync"	\
		: "=r" (ret) : "Z" (*addr) : "memory");			\
	वापस ret;							\
पूर्ण

#घोषणा DEF_MMIO_OUT_X(name, size, insn)				\
अटल अंतरभूत व्योम name(अस्थिर u##size __iomem *addr, u##size val)	\
अणु									\
	__यंत्र__ __अस्थिर__("sync;"#insn" %1,%y0"			\
		: "=Z" (*addr) : "r" (val) : "memory");			\
	mmiowb_set_pending();						\
पूर्ण

#घोषणा DEF_MMIO_IN_D(name, size, insn)				\
अटल अंतरभूत u##size name(स्थिर अस्थिर u##size __iomem *addr)	\
अणु									\
	u##size ret;							\
	__यंत्र__ __अस्थिर__("sync;"#insn"%U1%X1 %0,%1;twi 0,%0,0;isync"\
		: "=r" (ret) : "m"UPD_CONSTR (*addr) : "memory");	\
	वापस ret;							\
पूर्ण

#घोषणा DEF_MMIO_OUT_D(name, size, insn)				\
अटल अंतरभूत व्योम name(अस्थिर u##size __iomem *addr, u##size val)	\
अणु									\
	__यंत्र__ __अस्थिर__("sync;"#insn"%U0%X0 %1,%0"			\
		: "=m"UPD_CONSTR (*addr) : "r" (val) : "memory");	\
	mmiowb_set_pending();						\
पूर्ण

DEF_MMIO_IN_D(in_8,     8, lbz);
DEF_MMIO_OUT_D(out_8,   8, stb);

#अगर_घोषित __BIG_ENDIAN__
DEF_MMIO_IN_D(in_be16, 16, lhz);
DEF_MMIO_IN_D(in_be32, 32, lwz);
DEF_MMIO_IN_X(in_le16, 16, lhbrx);
DEF_MMIO_IN_X(in_le32, 32, lwbrx);

DEF_MMIO_OUT_D(out_be16, 16, sth);
DEF_MMIO_OUT_D(out_be32, 32, stw);
DEF_MMIO_OUT_X(out_le16, 16, sthbrx);
DEF_MMIO_OUT_X(out_le32, 32, stwbrx);
#अन्यथा
DEF_MMIO_IN_X(in_be16, 16, lhbrx);
DEF_MMIO_IN_X(in_be32, 32, lwbrx);
DEF_MMIO_IN_D(in_le16, 16, lhz);
DEF_MMIO_IN_D(in_le32, 32, lwz);

DEF_MMIO_OUT_X(out_be16, 16, sthbrx);
DEF_MMIO_OUT_X(out_be32, 32, stwbrx);
DEF_MMIO_OUT_D(out_le16, 16, sth);
DEF_MMIO_OUT_D(out_le32, 32, stw);

#पूर्ण_अगर /* __BIG_ENDIAN */

#अगर_घोषित __घातerpc64__

#अगर_घोषित __BIG_ENDIAN__
DEF_MMIO_OUT_D(out_be64, 64, std);
DEF_MMIO_IN_D(in_be64, 64, ld);

/* There is no यंत्र inकाष्ठाions क्रम 64 bits reverse loads and stores */
अटल अंतरभूत u64 in_le64(स्थिर अस्थिर u64 __iomem *addr)
अणु
	वापस swab64(in_be64(addr));
पूर्ण

अटल अंतरभूत व्योम out_le64(अस्थिर u64 __iomem *addr, u64 val)
अणु
	out_be64(addr, swab64(val));
पूर्ण
#अन्यथा
DEF_MMIO_OUT_D(out_le64, 64, std);
DEF_MMIO_IN_D(in_le64, 64, ld);

/* There is no यंत्र inकाष्ठाions क्रम 64 bits reverse loads and stores */
अटल अंतरभूत u64 in_be64(स्थिर अस्थिर u64 __iomem *addr)
अणु
	वापस swab64(in_le64(addr));
पूर्ण

अटल अंतरभूत व्योम out_be64(अस्थिर u64 __iomem *addr, u64 val)
अणु
	out_le64(addr, swab64(val));
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर /* __घातerpc64__ */

/*
 * Low level IO stream inकाष्ठाions are defined out of line क्रम now
 */
बाह्य व्योम _insb(स्थिर अस्थिर u8 __iomem *addr, व्योम *buf, दीर्घ count);
बाह्य व्योम _outsb(अस्थिर u8 __iomem *addr,स्थिर व्योम *buf,दीर्घ count);
बाह्य व्योम _insw_ns(स्थिर अस्थिर u16 __iomem *addr, व्योम *buf, दीर्घ count);
बाह्य व्योम _outsw_ns(अस्थिर u16 __iomem *addr, स्थिर व्योम *buf, दीर्घ count);
बाह्य व्योम _insl_ns(स्थिर अस्थिर u32 __iomem *addr, व्योम *buf, दीर्घ count);
बाह्य व्योम _outsl_ns(अस्थिर u32 __iomem *addr, स्थिर व्योम *buf, दीर्घ count);

/* The _ns naming is historical and will be हटाओd. For now, just #घोषणा
 * the non _ns equivalent names
 */
#घोषणा _insw	_insw_ns
#घोषणा _insl	_insl_ns
#घोषणा _outsw	_outsw_ns
#घोषणा _outsl	_outsl_ns


/*
 * स_रखो_io, स_नकल_toio, स_नकल_fromio base implementations are out of line
 */

बाह्य व्योम _स_रखो_io(अस्थिर व्योम __iomem *addr, पूर्णांक c, अचिन्हित दीर्घ n);
बाह्य व्योम _स_नकल_fromio(व्योम *dest, स्थिर अस्थिर व्योम __iomem *src,
			   अचिन्हित दीर्घ n);
बाह्य व्योम _स_नकल_toio(अस्थिर व्योम __iomem *dest, स्थिर व्योम *src,
			 अचिन्हित दीर्घ n);

/*
 *
 * PCI and standard ISA accessors
 *
 * Those are globally defined linux accessors क्रम devices on PCI or ISA
 * busses. They follow the Linux defined semantics. The current implementation
 * क्रम PowerPC is as बंद as possible to the x86 version of these, and thus
 * provides fairly heavy weight barriers क्रम the non-raw versions
 *
 * In addition, they support a hook mechanism when CONFIG_PPC_INसूचीECT_MMIO
 * or CONFIG_PPC_INसूचीECT_PIO are set allowing the platक्रमm to provide its
 * own implementation of some or all of the accessors.
 */

/*
 * Include the EEH definitions when EEH is enabled only so they करोn't get
 * in the way when building क्रम 32 bits
 */
#अगर_घोषित CONFIG_EEH
#समावेश <यंत्र/eeh.h>
#पूर्ण_अगर

/* Shortcut to the MMIO argument poपूर्णांकer */
#घोषणा PCI_IO_ADDR	अस्थिर व्योम __iomem *

/* Indirect IO address tokens:
 *
 * When CONFIG_PPC_INसूचीECT_MMIO is set, the platक्रमm can provide hooks
 * on all MMIOs. (Note that this is all 64 bits only क्रम now)
 *
 * To help platक्रमms who may need to dअगरferentiate MMIO addresses in
 * their hooks, a bitfield is reserved क्रम use by the platक्रमm near the
 * top of MMIO addresses (not PIO, those have to cope the hard way).
 *
 * The highest address in the kernel भव space are:
 *
 *  d0003fffffffffff	# with Hash MMU
 *  c00fffffffffffff	# with Radix MMU
 *
 * The top 4 bits are reserved as the region ID on hash, leaving us 8 bits
 * that can be used क्रम the field.
 *
 * The direct IO mapping operations will then mask off those bits
 * beक्रमe करोing the actual access, though that only happen when
 * CONFIG_PPC_INसूचीECT_MMIO is set, thus be careful when you use that
 * mechanism
 *
 * For PIO, there is a separate CONFIG_PPC_INसूचीECT_PIO which makes
 * all PIO functions call through a hook.
 */

#अगर_घोषित CONFIG_PPC_INसूचीECT_MMIO
#घोषणा PCI_IO_IND_TOKEN_SHIFT	52
#घोषणा PCI_IO_IND_TOKEN_MASK	(0xfful << PCI_IO_IND_TOKEN_SHIFT)
#घोषणा PCI_FIX_ADDR(addr)						\
	((PCI_IO_ADDR)(((अचिन्हित दीर्घ)(addr)) & ~PCI_IO_IND_TOKEN_MASK))
#घोषणा PCI_GET_ADDR_TOKEN(addr)					\
	(((अचिन्हित दीर्घ)(addr) & PCI_IO_IND_TOKEN_MASK) >> 		\
		PCI_IO_IND_TOKEN_SHIFT)
#घोषणा PCI_SET_ADDR_TOKEN(addr, token) 				\
करो अणु									\
	अचिन्हित दीर्घ __a = (अचिन्हित दीर्घ)(addr);			\
	__a &= ~PCI_IO_IND_TOKEN_MASK;					\
	__a |= ((अचिन्हित दीर्घ)(token)) << PCI_IO_IND_TOKEN_SHIFT;	\
	(addr) = (व्योम __iomem *)__a;					\
पूर्ण जबतक(0)
#अन्यथा
#घोषणा PCI_FIX_ADDR(addr) (addr)
#पूर्ण_अगर


/*
 * Non ordered and non-swapping "raw" accessors
 */

अटल अंतरभूत अचिन्हित अक्षर __raw_पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस *(अस्थिर अचिन्हित अक्षर __क्रमce *)PCI_FIX_ADDR(addr);
पूर्ण
#घोषणा __raw_पढ़ोb __raw_पढ़ोb

अटल अंतरभूत अचिन्हित लघु __raw_पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस *(अस्थिर अचिन्हित लघु __क्रमce *)PCI_FIX_ADDR(addr);
पूर्ण
#घोषणा __raw_पढ़ोw __raw_पढ़ोw

अटल अंतरभूत अचिन्हित पूर्णांक __raw_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस *(अस्थिर अचिन्हित पूर्णांक __क्रमce *)PCI_FIX_ADDR(addr);
पूर्ण
#घोषणा __raw_पढ़ोl __raw_पढ़ोl

अटल अंतरभूत व्योम __raw_ग_लिखोb(अचिन्हित अक्षर v, अस्थिर व्योम __iomem *addr)
अणु
	*(अस्थिर अचिन्हित अक्षर __क्रमce *)PCI_FIX_ADDR(addr) = v;
पूर्ण
#घोषणा __raw_ग_लिखोb __raw_ग_लिखोb

अटल अंतरभूत व्योम __raw_ग_लिखोw(अचिन्हित लघु v, अस्थिर व्योम __iomem *addr)
अणु
	*(अस्थिर अचिन्हित लघु __क्रमce *)PCI_FIX_ADDR(addr) = v;
पूर्ण
#घोषणा __raw_ग_लिखोw __raw_ग_लिखोw

अटल अंतरभूत व्योम __raw_ग_लिखोl(अचिन्हित पूर्णांक v, अस्थिर व्योम __iomem *addr)
अणु
	*(अस्थिर अचिन्हित पूर्णांक __क्रमce *)PCI_FIX_ADDR(addr) = v;
पूर्ण
#घोषणा __raw_ग_लिखोl __raw_ग_लिखोl

#अगर_घोषित __घातerpc64__
अटल अंतरभूत अचिन्हित दीर्घ __raw_पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस *(अस्थिर अचिन्हित दीर्घ __क्रमce *)PCI_FIX_ADDR(addr);
पूर्ण
#घोषणा __raw_पढ़ोq __raw_पढ़ोq

अटल अंतरभूत व्योम __raw_ग_लिखोq(अचिन्हित दीर्घ v, अस्थिर व्योम __iomem *addr)
अणु
	*(अस्थिर अचिन्हित दीर्घ __क्रमce *)PCI_FIX_ADDR(addr) = v;
पूर्ण
#घोषणा __raw_ग_लिखोq __raw_ग_लिखोq

अटल अंतरभूत व्योम __raw_ग_लिखोq_be(अचिन्हित दीर्घ v, अस्थिर व्योम __iomem *addr)
अणु
	__raw_ग_लिखोq((__क्रमce अचिन्हित दीर्घ)cpu_to_be64(v), addr);
पूर्ण
#घोषणा __raw_ग_लिखोq_be __raw_ग_लिखोq_be

/*
 * Real mode versions of the above. Those inकाष्ठाions are only supposed
 * to be used in hypervisor real mode as per the architecture spec.
 */
अटल अंतरभूत व्योम __raw_rm_ग_लिखोb(u8 val, अस्थिर व्योम __iomem *paddr)
अणु
	__यंत्र__ __अस्थिर__("stbcix %0,0,%1"
		: : "r" (val), "r" (paddr) : "memory");
पूर्ण

अटल अंतरभूत व्योम __raw_rm_ग_लिखोw(u16 val, अस्थिर व्योम __iomem *paddr)
अणु
	__यंत्र__ __अस्थिर__("sthcix %0,0,%1"
		: : "r" (val), "r" (paddr) : "memory");
पूर्ण

अटल अंतरभूत व्योम __raw_rm_ग_लिखोl(u32 val, अस्थिर व्योम __iomem *paddr)
अणु
	__यंत्र__ __अस्थिर__("stwcix %0,0,%1"
		: : "r" (val), "r" (paddr) : "memory");
पूर्ण

अटल अंतरभूत व्योम __raw_rm_ग_लिखोq(u64 val, अस्थिर व्योम __iomem *paddr)
अणु
	__यंत्र__ __अस्थिर__("stdcix %0,0,%1"
		: : "r" (val), "r" (paddr) : "memory");
पूर्ण

अटल अंतरभूत व्योम __raw_rm_ग_लिखोq_be(u64 val, अस्थिर व्योम __iomem *paddr)
अणु
	__raw_rm_ग_लिखोq((__क्रमce u64)cpu_to_be64(val), paddr);
पूर्ण

अटल अंतरभूत u8 __raw_rm_पढ़ोb(अस्थिर व्योम __iomem *paddr)
अणु
	u8 ret;
	__यंत्र__ __अस्थिर__("lbzcix %0,0, %1"
			     : "=r" (ret) : "r" (paddr) : "memory");
	वापस ret;
पूर्ण

अटल अंतरभूत u16 __raw_rm_पढ़ोw(अस्थिर व्योम __iomem *paddr)
अणु
	u16 ret;
	__यंत्र__ __अस्थिर__("lhzcix %0,0, %1"
			     : "=r" (ret) : "r" (paddr) : "memory");
	वापस ret;
पूर्ण

अटल अंतरभूत u32 __raw_rm_पढ़ोl(अस्थिर व्योम __iomem *paddr)
अणु
	u32 ret;
	__यंत्र__ __अस्थिर__("lwzcix %0,0, %1"
			     : "=r" (ret) : "r" (paddr) : "memory");
	वापस ret;
पूर्ण

अटल अंतरभूत u64 __raw_rm_पढ़ोq(अस्थिर व्योम __iomem *paddr)
अणु
	u64 ret;
	__यंत्र__ __अस्थिर__("ldcix %0,0, %1"
			     : "=r" (ret) : "r" (paddr) : "memory");
	वापस ret;
पूर्ण
#पूर्ण_अगर /* __घातerpc64__ */

/*
 *
 * PCI PIO and MMIO accessors.
 *
 *
 * On 32 bits, PIO operations have a recovery mechanism in हाल they trigger
 * machine checks (which they occasionally करो when probing non existing
 * IO ports on some platक्रमms, like PowerMac and 8xx).
 * I always found it to be of dubious reliability and I am tempted to get
 * rid of it one of these days. So अगर you think it's important to keep it,
 * please voice up asap. We never had it क्रम 64 bits and I करो not पूर्णांकend
 * to port it over
 */

#अगर_घोषित CONFIG_PPC32

#घोषणा __करो_in_यंत्र(name, op)				\
अटल अंतरभूत अचिन्हित पूर्णांक name(अचिन्हित पूर्णांक port)	\
अणु							\
	अचिन्हित पूर्णांक x;					\
	__यंत्र__ __अस्थिर__(				\
		"sync\n"				\
		"0:"	op "	%0,0,%1\n"		\
		"1:	twi	0,%0,0\n"		\
		"2:	isync\n"			\
		"3:	nop\n"				\
		"4:\n"					\
		".section .fixup,\"ax\"\n"		\
		"5:	li	%0,-1\n"		\
		"	b	4b\n"			\
		".previous\n"				\
		EX_TABLE(0b, 5b)			\
		EX_TABLE(1b, 5b)			\
		EX_TABLE(2b, 5b)			\
		EX_TABLE(3b, 5b)			\
		: "=&r" (x)				\
		: "r" (port + _IO_BASE)			\
		: "memory");  				\
	वापस x;					\
पूर्ण

#घोषणा __करो_out_यंत्र(name, op)				\
अटल अंतरभूत व्योम name(अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक port) \
अणु							\
	__यंत्र__ __अस्थिर__(				\
		"sync\n"				\
		"0:" op " %0,0,%1\n"			\
		"1:	sync\n"				\
		"2:\n"					\
		EX_TABLE(0b, 2b)			\
		EX_TABLE(1b, 2b)			\
		: : "r" (val), "r" (port + _IO_BASE)	\
		: "memory");   	   	   		\
पूर्ण

__करो_in_यंत्र(_rec_inb, "lbzx")
__करो_in_यंत्र(_rec_inw, "lhbrx")
__करो_in_यंत्र(_rec_inl, "lwbrx")
__करो_out_यंत्र(_rec_outb, "stbx")
__करो_out_यंत्र(_rec_outw, "sthbrx")
__करो_out_यंत्र(_rec_outl, "stwbrx")

#पूर्ण_अगर /* CONFIG_PPC32 */

/* The "__do_*" operations below provide the actual "base" implementation
 * क्रम each of the defined accessors. Some of them use the out_* functions
 * directly, some of them still use EEH, though we might change that in the
 * future. Those macros below provide the necessary argument swapping and
 * handling of the IO base क्रम PIO.
 *
 * They are themselves used by the macros that define the actual accessors
 * and can be used by the hooks अगर any.
 *
 * Note that PIO operations are always defined in terms of their corresonding
 * MMIO operations. That allows platक्रमms like iSeries who want to modअगरy the
 * behaviour of both to only hook on the MMIO version and get both. It's also
 * possible to hook directly at the toplevel PIO operation अगर they have to
 * be handled dअगरferently
 */
#घोषणा __करो_ग_लिखोb(val, addr)	out_8(PCI_FIX_ADDR(addr), val)
#घोषणा __करो_ग_लिखोw(val, addr)	out_le16(PCI_FIX_ADDR(addr), val)
#घोषणा __करो_ग_लिखोl(val, addr)	out_le32(PCI_FIX_ADDR(addr), val)
#घोषणा __करो_ग_लिखोq(val, addr)	out_le64(PCI_FIX_ADDR(addr), val)
#घोषणा __करो_ग_लिखोw_be(val, addr) out_be16(PCI_FIX_ADDR(addr), val)
#घोषणा __करो_ग_लिखोl_be(val, addr) out_be32(PCI_FIX_ADDR(addr), val)
#घोषणा __करो_ग_लिखोq_be(val, addr) out_be64(PCI_FIX_ADDR(addr), val)

#अगर_घोषित CONFIG_EEH
#घोषणा __करो_पढ़ोb(addr)	eeh_पढ़ोb(PCI_FIX_ADDR(addr))
#घोषणा __करो_पढ़ोw(addr)	eeh_पढ़ोw(PCI_FIX_ADDR(addr))
#घोषणा __करो_पढ़ोl(addr)	eeh_पढ़ोl(PCI_FIX_ADDR(addr))
#घोषणा __करो_पढ़ोq(addr)	eeh_पढ़ोq(PCI_FIX_ADDR(addr))
#घोषणा __करो_पढ़ोw_be(addr)	eeh_पढ़ोw_be(PCI_FIX_ADDR(addr))
#घोषणा __करो_पढ़ोl_be(addr)	eeh_पढ़ोl_be(PCI_FIX_ADDR(addr))
#घोषणा __करो_पढ़ोq_be(addr)	eeh_पढ़ोq_be(PCI_FIX_ADDR(addr))
#अन्यथा /* CONFIG_EEH */
#घोषणा __करो_पढ़ोb(addr)	in_8(PCI_FIX_ADDR(addr))
#घोषणा __करो_पढ़ोw(addr)	in_le16(PCI_FIX_ADDR(addr))
#घोषणा __करो_पढ़ोl(addr)	in_le32(PCI_FIX_ADDR(addr))
#घोषणा __करो_पढ़ोq(addr)	in_le64(PCI_FIX_ADDR(addr))
#घोषणा __करो_पढ़ोw_be(addr)	in_be16(PCI_FIX_ADDR(addr))
#घोषणा __करो_पढ़ोl_be(addr)	in_be32(PCI_FIX_ADDR(addr))
#घोषणा __करो_पढ़ोq_be(addr)	in_be64(PCI_FIX_ADDR(addr))
#पूर्ण_अगर /* !defined(CONFIG_EEH) */

#अगर_घोषित CONFIG_PPC32
#घोषणा __करो_outb(val, port)	_rec_outb(val, port)
#घोषणा __करो_outw(val, port)	_rec_outw(val, port)
#घोषणा __करो_outl(val, port)	_rec_outl(val, port)
#घोषणा __करो_inb(port)		_rec_inb(port)
#घोषणा __करो_inw(port)		_rec_inw(port)
#घोषणा __करो_inl(port)		_rec_inl(port)
#अन्यथा /* CONFIG_PPC32 */
#घोषणा __करो_outb(val, port)	ग_लिखोb(val,(PCI_IO_ADDR)_IO_BASE+port);
#घोषणा __करो_outw(val, port)	ग_लिखोw(val,(PCI_IO_ADDR)_IO_BASE+port);
#घोषणा __करो_outl(val, port)	ग_लिखोl(val,(PCI_IO_ADDR)_IO_BASE+port);
#घोषणा __करो_inb(port)		पढ़ोb((PCI_IO_ADDR)_IO_BASE + port);
#घोषणा __करो_inw(port)		पढ़ोw((PCI_IO_ADDR)_IO_BASE + port);
#घोषणा __करो_inl(port)		पढ़ोl((PCI_IO_ADDR)_IO_BASE + port);
#पूर्ण_अगर /* !CONFIG_PPC32 */

#अगर_घोषित CONFIG_EEH
#घोषणा __करो_पढ़ोsb(a, b, n)	eeh_पढ़ोsb(PCI_FIX_ADDR(a), (b), (n))
#घोषणा __करो_पढ़ोsw(a, b, n)	eeh_पढ़ोsw(PCI_FIX_ADDR(a), (b), (n))
#घोषणा __करो_पढ़ोsl(a, b, n)	eeh_पढ़ोsl(PCI_FIX_ADDR(a), (b), (n))
#अन्यथा /* CONFIG_EEH */
#घोषणा __करो_पढ़ोsb(a, b, n)	_insb(PCI_FIX_ADDR(a), (b), (n))
#घोषणा __करो_पढ़ोsw(a, b, n)	_insw(PCI_FIX_ADDR(a), (b), (n))
#घोषणा __करो_पढ़ोsl(a, b, n)	_insl(PCI_FIX_ADDR(a), (b), (n))
#पूर्ण_अगर /* !CONFIG_EEH */
#घोषणा __करो_ग_लिखोsb(a, b, n)	_outsb(PCI_FIX_ADDR(a),(b),(n))
#घोषणा __करो_ग_लिखोsw(a, b, n)	_outsw(PCI_FIX_ADDR(a),(b),(n))
#घोषणा __करो_ग_लिखोsl(a, b, n)	_outsl(PCI_FIX_ADDR(a),(b),(n))

#घोषणा __करो_insb(p, b, n)	पढ़ोsb((PCI_IO_ADDR)_IO_BASE+(p), (b), (n))
#घोषणा __करो_insw(p, b, n)	पढ़ोsw((PCI_IO_ADDR)_IO_BASE+(p), (b), (n))
#घोषणा __करो_insl(p, b, n)	पढ़ोsl((PCI_IO_ADDR)_IO_BASE+(p), (b), (n))
#घोषणा __करो_outsb(p, b, n)	ग_लिखोsb((PCI_IO_ADDR)_IO_BASE+(p),(b),(n))
#घोषणा __करो_outsw(p, b, n)	ग_लिखोsw((PCI_IO_ADDR)_IO_BASE+(p),(b),(n))
#घोषणा __करो_outsl(p, b, n)	ग_लिखोsl((PCI_IO_ADDR)_IO_BASE+(p),(b),(n))

#घोषणा __करो_स_रखो_io(addr, c, n)	\
				_स_रखो_io(PCI_FIX_ADDR(addr), c, n)
#घोषणा __करो_स_नकल_toio(dst, src, n)	\
				_स_नकल_toio(PCI_FIX_ADDR(dst), src, n)

#अगर_घोषित CONFIG_EEH
#घोषणा __करो_स_नकल_fromio(dst, src, n)	\
				eeh_स_नकल_fromio(dst, PCI_FIX_ADDR(src), n)
#अन्यथा /* CONFIG_EEH */
#घोषणा __करो_स_नकल_fromio(dst, src, n)	\
				_स_नकल_fromio(dst,PCI_FIX_ADDR(src),n)
#पूर्ण_अगर /* !CONFIG_EEH */

#अगर_घोषित CONFIG_PPC_INसूचीECT_PIO
#घोषणा DEF_PCI_HOOK_pio(x)	x
#अन्यथा
#घोषणा DEF_PCI_HOOK_pio(x)	शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_INसूचीECT_MMIO
#घोषणा DEF_PCI_HOOK_mem(x)	x
#अन्यथा
#घोषणा DEF_PCI_HOOK_mem(x)	शून्य
#पूर्ण_अगर

/* Structure containing all the hooks */
बाह्य काष्ठा ppc_pci_io अणु

#घोषणा DEF_PCI_AC_RET(name, ret, at, al, space, aa)	ret (*name) at;
#घोषणा DEF_PCI_AC_NORET(name, at, al, space, aa)	व्योम (*name) at;

#समावेश <यंत्र/io-defs.h>

#अघोषित DEF_PCI_AC_RET
#अघोषित DEF_PCI_AC_NORET

पूर्ण ppc_pci_io;

/* The अंतरभूत wrappers */
#घोषणा DEF_PCI_AC_RET(name, ret, at, al, space, aa)		\
अटल अंतरभूत ret name at					\
अणु								\
	अगर (DEF_PCI_HOOK_##space(ppc_pci_io.name) != शून्य)	\
		वापस ppc_pci_io.name al;			\
	वापस __करो_##name al;					\
पूर्ण

#घोषणा DEF_PCI_AC_NORET(name, at, al, space, aa)		\
अटल अंतरभूत व्योम name at					\
अणु								\
	अगर (DEF_PCI_HOOK_##space(ppc_pci_io.name) != शून्य)		\
		ppc_pci_io.name al;				\
	अन्यथा							\
		__करो_##name al;					\
पूर्ण

#समावेश <यंत्र/io-defs.h>

#अघोषित DEF_PCI_AC_RET
#अघोषित DEF_PCI_AC_NORET

/* Some drivers check क्रम the presence of पढ़ोq & ग_लिखोq with
 * a #अगर_घोषित, so we make them happy here.
 */
#घोषणा पढ़ोb पढ़ोb
#घोषणा पढ़ोw पढ़ोw
#घोषणा पढ़ोl पढ़ोl
#घोषणा ग_लिखोb ग_लिखोb
#घोषणा ग_लिखोw ग_लिखोw
#घोषणा ग_लिखोl ग_लिखोl
#घोषणा पढ़ोsb पढ़ोsb
#घोषणा पढ़ोsw पढ़ोsw
#घोषणा पढ़ोsl पढ़ोsl
#घोषणा ग_लिखोsb ग_लिखोsb
#घोषणा ग_लिखोsw ग_लिखोsw
#घोषणा ग_लिखोsl ग_लिखोsl
#घोषणा inb inb
#घोषणा inw inw
#घोषणा inl inl
#घोषणा outb outb
#घोषणा outw outw
#घोषणा outl outl
#घोषणा insb insb
#घोषणा insw insw
#घोषणा insl insl
#घोषणा outsb outsb
#घोषणा outsw outsw
#घोषणा outsl outsl
#अगर_घोषित __घातerpc64__
#घोषणा पढ़ोq	पढ़ोq
#घोषणा ग_लिखोq	ग_लिखोq
#पूर्ण_अगर
#घोषणा स_रखो_io स_रखो_io
#घोषणा स_नकल_fromio स_नकल_fromio
#घोषणा स_नकल_toio स_नकल_toio

/*
 * Convert a physical poपूर्णांकer to a भव kernel poपूर्णांकer क्रम /dev/mem
 * access
 */
#घोषणा xlate_dev_mem_ptr(p)	__va(p)

/*
 * We करोn't करो relaxed operations yet, at least not with this semantic
 */
#घोषणा पढ़ोb_relaxed(addr)	पढ़ोb(addr)
#घोषणा पढ़ोw_relaxed(addr)	पढ़ोw(addr)
#घोषणा पढ़ोl_relaxed(addr)	पढ़ोl(addr)
#घोषणा पढ़ोq_relaxed(addr)	पढ़ोq(addr)
#घोषणा ग_लिखोb_relaxed(v, addr)	ग_लिखोb(v, addr)
#घोषणा ग_लिखोw_relaxed(v, addr)	ग_लिखोw(v, addr)
#घोषणा ग_लिखोl_relaxed(v, addr)	ग_लिखोl(v, addr)
#घोषणा ग_लिखोq_relaxed(v, addr)	ग_लिखोq(v, addr)

#अगर_घोषित CONFIG_GENERIC_IOMAP
#समावेश <यंत्र-generic/iomap.h>
#अन्यथा
/*
 * Here comes the implementation of the IOMAP पूर्णांकerfaces.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ioपढ़ो16be(स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोw_be(addr);
पूर्ण
#घोषणा ioपढ़ो16be ioपढ़ो16be

अटल अंतरभूत अचिन्हित पूर्णांक ioपढ़ो32be(स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोl_be(addr);
पूर्ण
#घोषणा ioपढ़ो32be ioपढ़ो32be

#अगर_घोषित __घातerpc64__
अटल अंतरभूत u64 ioपढ़ो64_lo_hi(स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोq(addr);
पूर्ण
#घोषणा ioपढ़ो64_lo_hi ioपढ़ो64_lo_hi

अटल अंतरभूत u64 ioपढ़ो64_hi_lo(स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोq(addr);
पूर्ण
#घोषणा ioपढ़ो64_hi_lo ioपढ़ो64_hi_lo

अटल अंतरभूत u64 ioपढ़ो64be(स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोq_be(addr);
पूर्ण
#घोषणा ioपढ़ो64be ioपढ़ो64be

अटल अंतरभूत u64 ioपढ़ो64be_lo_hi(स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोq_be(addr);
पूर्ण
#घोषणा ioपढ़ो64be_lo_hi ioपढ़ो64be_lo_hi

अटल अंतरभूत u64 ioपढ़ो64be_hi_lo(स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोq_be(addr);
पूर्ण
#घोषणा ioपढ़ो64be_hi_lo ioपढ़ो64be_hi_lo
#पूर्ण_अगर /* __घातerpc64__ */

अटल अंतरभूत व्योम ioग_लिखो16be(u16 val, व्योम __iomem *addr)
अणु
	ग_लिखोw_be(val, addr);
पूर्ण
#घोषणा ioग_लिखो16be ioग_लिखो16be

अटल अंतरभूत व्योम ioग_लिखो32be(u32 val, व्योम __iomem *addr)
अणु
	ग_लिखोl_be(val, addr);
पूर्ण
#घोषणा ioग_लिखो32be ioग_लिखो32be

#अगर_घोषित __घातerpc64__
अटल अंतरभूत व्योम ioग_लिखो64_lo_hi(u64 val, व्योम __iomem *addr)
अणु
	ग_लिखोq(val, addr);
पूर्ण
#घोषणा ioग_लिखो64_lo_hi ioग_लिखो64_lo_hi

अटल अंतरभूत व्योम ioग_लिखो64_hi_lo(u64 val, व्योम __iomem *addr)
अणु
	ग_लिखोq(val, addr);
पूर्ण
#घोषणा ioग_लिखो64_hi_lo ioग_लिखो64_hi_lo

अटल अंतरभूत व्योम ioग_लिखो64be(u64 val, व्योम __iomem *addr)
अणु
	ग_लिखोq_be(val, addr);
पूर्ण
#घोषणा ioग_लिखो64be ioग_लिखो64be

अटल अंतरभूत व्योम ioग_लिखो64be_lo_hi(u64 val, व्योम __iomem *addr)
अणु
	ग_लिखोq_be(val, addr);
पूर्ण
#घोषणा ioग_लिखो64be_lo_hi ioग_लिखो64be_lo_hi

अटल अंतरभूत व्योम ioग_लिखो64be_hi_lo(u64 val, व्योम __iomem *addr)
अणु
	ग_लिखोq_be(val, addr);
पूर्ण
#घोषणा ioग_लिखो64be_hi_lo ioग_लिखो64be_hi_lo
#पूर्ण_अगर /* __घातerpc64__ */

काष्ठा pci_dev;
व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem *addr);
#घोषणा pci_iounmap pci_iounmap
व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक len);
#घोषणा ioport_map ioport_map
#पूर्ण_अगर

अटल अंतरभूत व्योम iosync(व्योम)
अणु
        __यंत्र__ __अस्थिर__ ("sync" : : : "memory");
पूर्ण

/* Enक्रमce in-order execution of data I/O.
 * No distinction between पढ़ो/ग_लिखो on PPC; use eieio क्रम all three.
 * Those are fairly week though. They करोn't provide a barrier between
 * MMIO and cacheable storage nor करो they provide a barrier vs. locks,
 * they only provide barriers between 2 __raw MMIO operations and
 * possibly अवरोध ग_लिखो combining.
 */
#घोषणा iobarrier_rw() eieio()
#घोषणा iobarrier_r()  eieio()
#घोषणा iobarrier_w()  eieio()


/*
 * output छोड़ो versions need a delay at least क्रम the
 * w83c105 ide controller in a p610.
 */
#घोषणा inb_p(port)             inb(port)
#घोषणा outb_p(val, port)       (udelay(1), outb((val), (port)))
#घोषणा inw_p(port)             inw(port)
#घोषणा outw_p(val, port)       (udelay(1), outw((val), (port)))
#घोषणा inl_p(port)             inl(port)
#घोषणा outl_p(val, port)       (udelay(1), outl((val), (port)))


#घोषणा IO_SPACE_LIMIT ~(0UL)

/**
 * ioremap     -   map bus memory पूर्णांकo CPU space
 * @address:   bus address of the memory
 * @size:      size of the resource to map
 *
 * ioremap perक्रमms a platक्रमm specअगरic sequence of operations to
 * make bus memory CPU accessible via the पढ़ोb/पढ़ोw/पढ़ोl/ग_लिखोb/
 * ग_लिखोw/ग_लिखोl functions and the other mmio helpers. The वापसed
 * address is not guaranteed to be usable directly as a भव
 * address.
 *
 * We provide a few variations of it:
 *
 * * ioremap is the standard one and provides non-cacheable guarded mappings
 *   and can be hooked by the platक्रमm via ppc_md
 *
 * * ioremap_prot allows to specअगरy the page flags as an argument and can
 *   also be hooked by the platक्रमm via ppc_md.
 *
 * * ioremap_wc enables ग_लिखो combining
 *
 * * ioremap_wt enables ग_लिखो through
 *
 * * ioremap_coherent maps coherent cached memory
 *
 * * iounmap unकरोes such a mapping and can be hooked
 *
 * * __ioremap_caller is the same as above but takes an explicit caller
 *   reference rather than using __builtin_वापस_address(0)
 *
 */
बाह्य व्योम __iomem *ioremap(phys_addr_t address, अचिन्हित दीर्घ size);
बाह्य व्योम __iomem *ioremap_prot(phys_addr_t address, अचिन्हित दीर्घ size,
				  अचिन्हित दीर्घ flags);
बाह्य व्योम __iomem *ioremap_wc(phys_addr_t address, अचिन्हित दीर्घ size);
#घोषणा ioremap_wc ioremap_wc

#अगर_घोषित CONFIG_PPC32
व्योम __iomem *ioremap_wt(phys_addr_t address, अचिन्हित दीर्घ size);
#घोषणा ioremap_wt ioremap_wt
#पूर्ण_अगर

व्योम __iomem *ioremap_coherent(phys_addr_t address, अचिन्हित दीर्घ size);
#घोषणा ioremap_uc(addr, size)		ioremap((addr), (size))
#घोषणा ioremap_cache(addr, size) \
	ioremap_prot((addr), (size), pgprot_val(PAGE_KERNEL))

बाह्य व्योम iounmap(अस्थिर व्योम __iomem *addr);

व्योम __iomem *ioremap_phb(phys_addr_t paddr, अचिन्हित दीर्घ size);

पूर्णांक early_ioremap_range(अचिन्हित दीर्घ ea, phys_addr_t pa,
			अचिन्हित दीर्घ size, pgprot_t prot);
व्योम __iomem *करो_ioremap(phys_addr_t pa, phys_addr_t offset, अचिन्हित दीर्घ size,
			 pgprot_t prot, व्योम *caller);

बाह्य व्योम __iomem *__ioremap_caller(phys_addr_t, अचिन्हित दीर्घ size,
				      pgprot_t prot, व्योम *caller);

/*
 * When CONFIG_PPC_INसूचीECT_PIO is set, we use the generic iomap implementation
 * which needs some additional definitions here. They basically allow PIO
 * space overall to be 1GB. This will work as दीर्घ as we never try to use
 * iomap to map MMIO below 1GB which should be fine on ppc64
 */
#घोषणा HAVE_ARCH_PIO_SIZE		1
#घोषणा PIO_OFFSET			0x00000000UL
#घोषणा PIO_MASK			(FULL_IO_SIZE - 1)
#घोषणा PIO_RESERVED			(FULL_IO_SIZE)

#घोषणा mmio_पढ़ो16be(addr)		पढ़ोw_be(addr)
#घोषणा mmio_पढ़ो32be(addr)		पढ़ोl_be(addr)
#घोषणा mmio_पढ़ो64be(addr)		पढ़ोq_be(addr)
#घोषणा mmio_ग_लिखो16be(val, addr)	ग_लिखोw_be(val, addr)
#घोषणा mmio_ग_लिखो32be(val, addr)	ग_लिखोl_be(val, addr)
#घोषणा mmio_ग_लिखो64be(val, addr)	ग_लिखोq_be(val, addr)
#घोषणा mmio_insb(addr, dst, count)	पढ़ोsb(addr, dst, count)
#घोषणा mmio_insw(addr, dst, count)	पढ़ोsw(addr, dst, count)
#घोषणा mmio_insl(addr, dst, count)	पढ़ोsl(addr, dst, count)
#घोषणा mmio_outsb(addr, src, count)	ग_लिखोsb(addr, src, count)
#घोषणा mmio_outsw(addr, src, count)	ग_लिखोsw(addr, src, count)
#घोषणा mmio_outsl(addr, src, count)	ग_लिखोsl(addr, src, count)

/**
 *	virt_to_phys	-	map भव addresses to physical
 *	@address: address to remap
 *
 *	The वापसed physical address is the physical (CPU) mapping क्रम
 *	the memory address given. It is only valid to use this function on
 *	addresses directly mapped or allocated via kदो_स्मृति.
 *
 *	This function करोes not give bus mappings क्रम DMA transfers. In
 *	almost all conceivable हालs a device driver should not be using
 *	this function
 */
अटल अंतरभूत अचिन्हित दीर्घ virt_to_phys(अस्थिर व्योम * address)
अणु
	WARN_ON(IS_ENABLED(CONFIG_DEBUG_VIRTUAL) && !virt_addr_valid(address));

	वापस __pa((अचिन्हित दीर्घ)address);
पूर्ण
#घोषणा virt_to_phys virt_to_phys

/**
 *	phys_to_virt	-	map physical address to भव
 *	@address: address to remap
 *
 *	The वापसed भव address is a current CPU mapping क्रम
 *	the memory address given. It is only valid to use this function on
 *	addresses that have a kernel mapping
 *
 *	This function करोes not handle bus mappings क्रम DMA transfers. In
 *	almost all conceivable हालs a device driver should not be using
 *	this function
 */
अटल अंतरभूत व्योम * phys_to_virt(अचिन्हित दीर्घ address)
अणु
	वापस (व्योम *)__va(address);
पूर्ण
#घोषणा phys_to_virt phys_to_virt

/*
 * Change "struct page" to physical address.
 */
अटल अंतरभूत phys_addr_t page_to_phys(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ pfn = page_to_pfn(page);

	WARN_ON(IS_ENABLED(CONFIG_DEBUG_VIRTUAL) && !pfn_valid(pfn));

	वापस PFN_PHYS(pfn);
पूर्ण

/*
 * 32 bits still uses virt_to_bus() क्रम it's implementation of DMA
 * mappings se we have to keep it defined here. We also have some old
 * drivers (shame shame shame) that use bus_to_virt() and haven't been
 * fixed yet so I need to define it here.
 */
#अगर_घोषित CONFIG_PPC32

अटल अंतरभूत अचिन्हित दीर्घ virt_to_bus(अस्थिर व्योम * address)
अणु
        अगर (address == शून्य)
		वापस 0;
        वापस __pa(address) + PCI_DRAM_OFFSET;
पूर्ण
#घोषणा virt_to_bus virt_to_bus

अटल अंतरभूत व्योम * bus_to_virt(अचिन्हित दीर्घ address)
अणु
        अगर (address == 0)
		वापस शून्य;
        वापस __va(address - PCI_DRAM_OFFSET);
पूर्ण
#घोषणा bus_to_virt bus_to_virt

#घोषणा page_to_bus(page)	(page_to_phys(page) + PCI_DRAM_OFFSET)

#पूर्ण_अगर /* CONFIG_PPC32 */

/* access ports */
#घोषणा setbits32(_addr, _v) out_be32((_addr), in_be32(_addr) |  (_v))
#घोषणा clrbits32(_addr, _v) out_be32((_addr), in_be32(_addr) & ~(_v))

#घोषणा setbits16(_addr, _v) out_be16((_addr), in_be16(_addr) |  (_v))
#घोषणा clrbits16(_addr, _v) out_be16((_addr), in_be16(_addr) & ~(_v))

#घोषणा setbits8(_addr, _v) out_8((_addr), in_8(_addr) |  (_v))
#घोषणा clrbits8(_addr, _v) out_8((_addr), in_8(_addr) & ~(_v))

/* Clear and set bits in one shot.  These macros can be used to clear and
 * set multiple bits in a रेजिस्टर using a single पढ़ो-modअगरy-ग_लिखो.  These
 * macros can also be used to set a multiple-bit bit pattern using a mask,
 * by specअगरying the mask in the 'clear' parameter and the new bit pattern
 * in the 'set' parameter.
 */

#घोषणा clrsetbits(type, addr, clear, set) \
	out_##type((addr), (in_##type(addr) & ~(clear)) | (set))

#अगर_घोषित __घातerpc64__
#घोषणा clrsetbits_be64(addr, clear, set) clrsetbits(be64, addr, clear, set)
#घोषणा clrsetbits_le64(addr, clear, set) clrsetbits(le64, addr, clear, set)
#पूर्ण_अगर

#घोषणा clrsetbits_be32(addr, clear, set) clrsetbits(be32, addr, clear, set)
#घोषणा clrsetbits_le32(addr, clear, set) clrsetbits(le32, addr, clear, set)

#घोषणा clrsetbits_be16(addr, clear, set) clrsetbits(be16, addr, clear, set)
#घोषणा clrsetbits_le16(addr, clear, set) clrsetbits(le16, addr, clear, set)

#घोषणा clrsetbits_8(addr, clear, set) clrsetbits(8, addr, clear, set)

#समावेश <यंत्र-generic/पन.स>

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_POWERPC_IO_H */
