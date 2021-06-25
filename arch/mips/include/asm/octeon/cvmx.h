<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2017 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this file; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a dअगरferent license from Cavium.
 * Contact Cavium Networks क्रम more inक्रमmation
 ***********************license end**************************************/

#अगर_अघोषित __CVMX_H__
#घोषणा __CVMX_H__

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>

क्रमागत cvmx_mips_space अणु
	CVMX_MIPS_SPACE_XKSEG = 3LL,
	CVMX_MIPS_SPACE_XKPHYS = 2LL,
	CVMX_MIPS_SPACE_XSSEG = 1LL,
	CVMX_MIPS_SPACE_XUSEG = 0LL
पूर्ण;

/* These macros क्रम use when using 32 bit poपूर्णांकers. */
#घोषणा CVMX_MIPS32_SPACE_KSEG0 1l
#घोषणा CVMX_ADD_SEG32(segment, add) \
	(((पूर्णांक32_t)segment << 31) | (पूर्णांक32_t)(add))

#घोषणा CVMX_IO_SEG CVMX_MIPS_SPACE_XKPHYS

/* These macros simplअगरy the process of creating common IO addresses */
#घोषणा CVMX_ADD_SEG(segment, add) \
	((((uपूर्णांक64_t)segment) << 62) | (add))
#अगर_अघोषित CVMX_ADD_IO_SEG
#घोषणा CVMX_ADD_IO_SEG(add) CVMX_ADD_SEG(CVMX_IO_SEG, (add))
#पूर्ण_अगर

#समावेश <यंत्र/octeon/cvmx-यंत्र.h>
#समावेश <यंत्र/octeon/cvmx-packet.h>
#समावेश <यंत्र/octeon/cvmx-sysinfo.h>

#समावेश <यंत्र/octeon/cvmx-ciu-defs.h>
#समावेश <यंत्र/octeon/cvmx-ciu3-defs.h>
#समावेश <यंत्र/octeon/cvmx-gpio-defs.h>
#समावेश <यंत्र/octeon/cvmx-iob-defs.h>
#समावेश <यंत्र/octeon/cvmx-ipd-defs.h>
#समावेश <यंत्र/octeon/cvmx-l2c-defs.h>
#समावेश <यंत्र/octeon/cvmx-l2d-defs.h>
#समावेश <यंत्र/octeon/cvmx-l2t-defs.h>
#समावेश <यंत्र/octeon/cvmx-led-defs.h>
#समावेश <यंत्र/octeon/cvmx-mio-defs.h>
#समावेश <यंत्र/octeon/cvmx-घात-defs.h>

#समावेश <यंत्र/octeon/cvmx-bootinfo.h>
#समावेश <यंत्र/octeon/cvmx-booपंचांगem.h>
#समावेश <यंत्र/octeon/cvmx-l2c.h>

#अगर_अघोषित CVMX_ENABLE_DEBUG_PRINTS
#घोषणा CVMX_ENABLE_DEBUG_PRINTS 1
#पूर्ण_अगर

#अगर CVMX_ENABLE_DEBUG_PRINTS
#घोषणा cvmx_dम_लिखो	    prपूर्णांकk
#अन्यथा
#घोषणा cvmx_dम_लिखो(...)   अणुपूर्ण
#पूर्ण_अगर

#घोषणा CVMX_MAX_CORES		(16)
#घोषणा CVMX_CACHE_LINE_SIZE	(128)	/* In bytes */
#घोषणा CVMX_CACHE_LINE_MASK	(CVMX_CACHE_LINE_SIZE - 1)	/* In bytes */
#घोषणा CVMX_CACHE_LINE_ALIGNED __attribute__ ((aligned(CVMX_CACHE_LINE_SIZE)))
#घोषणा CAST64(v) ((दीर्घ दीर्घ)(दीर्घ)(v))
#घोषणा CASTPTR(type, v) ((type *)(दीर्घ)(v))

/*
 * Returns processor ID, dअगरferent Linux and simple exec versions
 * provided in the cvmx-app-init*.c files.
 */
अटल अंतरभूत uपूर्णांक32_t cvmx_get_proc_id(व्योम) __attribute__ ((pure));
अटल अंतरभूत uपूर्णांक32_t cvmx_get_proc_id(व्योम)
अणु
	uपूर्णांक32_t id;
	यंत्र("mfc0 %0, $15,0" : "=r"(id));
	वापस id;
पूर्ण

/* turn the variable name पूर्णांकo a string */
#घोषणा CVMX_TMP_STR(x) CVMX_TMP_STR2(x)
#घोषणा CVMX_TMP_STR2(x) #x

/**
 * Builds a bit mask given the required size in bits.
 *
 * @bits:   Number of bits in the mask
 * Returns The mask
 */ अटल अंतरभूत uपूर्णांक64_t cvmx_build_mask(uपूर्णांक64_t bits)
अणु
	वापस ~((~0x0ull) << bits);
पूर्ण

/**
 * Builds a memory address क्रम I/O based on the Major and Sub DID.
 *
 * @major_did: 5 bit major did
 * @sub_did:   3 bit sub did
 * Returns I/O base address
 */
अटल अंतरभूत uपूर्णांक64_t cvmx_build_io_address(uपूर्णांक64_t major_did,
					     uपूर्णांक64_t sub_did)
अणु
	वापस (0x1ull << 48) | (major_did << 43) | (sub_did << 40);
पूर्ण

/**
 * Perक्रमm mask and shअगरt to place the supplied value पूर्णांकo
 * the supplied bit rage.
 *
 * Example: cvmx_build_bits(39,24,value)
 * <pre>
 * 6	   5	   4	   3	   3	   2	   1
 * 3	   5	   7	   9	   1	   3	   5	   7	  0
 * +-------+-------+-------+-------+-------+-------+-------+------+
 * 000000000000000000000000___________value000000000000000000000000
 * </pre>
 *
 * @high_bit: Highest bit value can occupy (inclusive) 0-63
 * @low_bit:  Lowest bit value can occupy inclusive 0-high_bit
 * @value:    Value to use
 * Returns Value masked and shअगरted
 */
अटल अंतरभूत uपूर्णांक64_t cvmx_build_bits(uपूर्णांक64_t high_bit,
				       uपूर्णांक64_t low_bit, uपूर्णांक64_t value)
अणु
	वापस (value & cvmx_build_mask(high_bit - low_bit + 1)) << low_bit;
पूर्ण

/**
 * Convert a memory poपूर्णांकer (व्योम*) पूर्णांकo a hardware compatible
 * memory address (uपूर्णांक64_t). Octeon hardware widमाला_लो करोn't
 * understand logical addresses.
 *
 * @ptr:    C style memory poपूर्णांकer
 * Returns Hardware physical address
 */
अटल अंतरभूत uपूर्णांक64_t cvmx_ptr_to_phys(व्योम *ptr)
अणु
	अगर (माप(व्योम *) == 8) अणु
		/*
		 * We're running in 64 bit mode. Normally this means
		 * that we can use 40 bits of address space (the
		 * hardware limit). Unक्रमtunately there is one हाल
		 * were we need to limit this to 30 bits, sign
		 * extended 32 bit. Although these are 64 bits wide,
		 * only 30 bits can be used.
		 */
		अगर ((CAST64(ptr) >> 62) == 3)
			वापस CAST64(ptr) & cvmx_build_mask(30);
		अन्यथा
			वापस CAST64(ptr) & cvmx_build_mask(40);
	पूर्ण अन्यथा अणु
		वापस (दीर्घ)(ptr) & 0x1fffffff;
	पूर्ण
पूर्ण

/**
 * Convert a hardware physical address (uपूर्णांक64_t) पूर्णांकo a
 * memory poपूर्णांकer (व्योम *).
 *
 * @physical_address:
 *		 Hardware physical address to memory
 * Returns Poपूर्णांकer to memory
 */
अटल अंतरभूत व्योम *cvmx_phys_to_ptr(uपूर्णांक64_t physical_address)
अणु
	अगर (माप(व्योम *) == 8) अणु
		/* Just set the top bit, aव्योमing any TLB ugliness */
		वापस CASTPTR(व्योम,
			       CVMX_ADD_SEG(CVMX_MIPS_SPACE_XKPHYS,
					    physical_address));
	पूर्ण अन्यथा अणु
		वापस CASTPTR(व्योम,
			       CVMX_ADD_SEG32(CVMX_MIPS32_SPACE_KSEG0,
					      physical_address));
	पूर्ण
पूर्ण

/* The following #अगर controls the definition of the macro
    CVMX_BUILD_WRITE64. This macro is used to build a store operation to
    a full 64bit address. With a 64bit ABI, this can be करोne with a simple
    poपूर्णांकer access. 32bit ABIs require more complicated assembly */

/* We have a full 64bit ABI. Writing to a 64bit address can be करोne with
    a simple अस्थिर poपूर्णांकer */
#घोषणा CVMX_BUILD_WRITE64(TYPE, ST)					\
अटल अंतरभूत व्योम cvmx_ग_लिखो64_##TYPE(uपूर्णांक64_t addr, TYPE##_t val)	\
अणु									\
    *CASTPTR(अस्थिर TYPE##_t, addr) = val;				\
पूर्ण


/* The following #अगर controls the definition of the macro
    CVMX_BUILD_READ64. This macro is used to build a load operation from
    a full 64bit address. With a 64bit ABI, this can be करोne with a simple
    poपूर्णांकer access. 32bit ABIs require more complicated assembly */

/* We have a full 64bit ABI. Writing to a 64bit address can be करोne with
    a simple अस्थिर poपूर्णांकer */
#घोषणा CVMX_BUILD_READ64(TYPE, LT)					\
अटल अंतरभूत TYPE##_t cvmx_पढ़ो64_##TYPE(uपूर्णांक64_t addr)		\
अणु									\
	वापस *CASTPTR(अस्थिर TYPE##_t, addr);			\
पूर्ण


/* The following defines 8 functions क्रम writing to a 64bit address. Each
    takes two arguments, the address and the value to ग_लिखो.
    cvmx_ग_लिखो64_पूर्णांक64	    cvmx_ग_लिखो64_uपूर्णांक64
    cvmx_ग_लिखो64_पूर्णांक32	    cvmx_ग_लिखो64_uपूर्णांक32
    cvmx_ग_लिखो64_पूर्णांक16	    cvmx_ग_लिखो64_uपूर्णांक16
    cvmx_ग_लिखो64_पूर्णांक8	    cvmx_ग_लिखो64_uपूर्णांक8 */
CVMX_BUILD_WRITE64(पूर्णांक64, "sd");
CVMX_BUILD_WRITE64(पूर्णांक32, "sw");
CVMX_BUILD_WRITE64(पूर्णांक16, "sh");
CVMX_BUILD_WRITE64(पूर्णांक8, "sb");
CVMX_BUILD_WRITE64(uपूर्णांक64, "sd");
CVMX_BUILD_WRITE64(uपूर्णांक32, "sw");
CVMX_BUILD_WRITE64(uपूर्णांक16, "sh");
CVMX_BUILD_WRITE64(uपूर्णांक8, "sb");
#घोषणा cvmx_ग_लिखो64 cvmx_ग_लिखो64_uपूर्णांक64

/* The following defines 8 functions क्रम पढ़ोing from a 64bit address. Each
    takes the address as the only argument
    cvmx_पढ़ो64_पूर्णांक64	    cvmx_पढ़ो64_uपूर्णांक64
    cvmx_पढ़ो64_पूर्णांक32	    cvmx_पढ़ो64_uपूर्णांक32
    cvmx_पढ़ो64_पूर्णांक16	    cvmx_पढ़ो64_uपूर्णांक16
    cvmx_पढ़ो64_पूर्णांक8	    cvmx_पढ़ो64_uपूर्णांक8 */
CVMX_BUILD_READ64(पूर्णांक64, "ld");
CVMX_BUILD_READ64(पूर्णांक32, "lw");
CVMX_BUILD_READ64(पूर्णांक16, "lh");
CVMX_BUILD_READ64(पूर्णांक8, "lb");
CVMX_BUILD_READ64(uपूर्णांक64, "ld");
CVMX_BUILD_READ64(uपूर्णांक32, "lw");
CVMX_BUILD_READ64(uपूर्णांक16, "lhu");
CVMX_BUILD_READ64(uपूर्णांक8, "lbu");
#घोषणा cvmx_पढ़ो64 cvmx_पढ़ो64_uपूर्णांक64


अटल अंतरभूत व्योम cvmx_ग_लिखो_csr(uपूर्णांक64_t csr_addr, uपूर्णांक64_t val)
अणु
	cvmx_ग_लिखो64(csr_addr, val);

	/*
	 * Perक्रमm an immediate पढ़ो after every ग_लिखो to an RSL
	 * रेजिस्टर to क्रमce the ग_लिखो to complete. It करोesn't matter
	 * what RSL पढ़ो we करो, so we choose CVMX_MIO_BOOT_BIST_STAT
	 * because it is fast and harmless.
	 */
	अगर (((csr_addr >> 40) & 0x7ffff) == (0x118))
		cvmx_पढ़ो64(CVMX_MIO_BOOT_BIST_STAT);
पूर्ण

अटल अंतरभूत व्योम cvmx_ग_लिखोq_csr(व्योम __iomem *csr_addr, uपूर्णांक64_t val)
अणु
	cvmx_ग_लिखो_csr((__क्रमce uपूर्णांक64_t)csr_addr, val);
पूर्ण

अटल अंतरभूत व्योम cvmx_ग_लिखो_io(uपूर्णांक64_t io_addr, uपूर्णांक64_t val)
अणु
	cvmx_ग_लिखो64(io_addr, val);

पूर्ण

अटल अंतरभूत uपूर्णांक64_t cvmx_पढ़ो_csr(uपूर्णांक64_t csr_addr)
अणु
	uपूर्णांक64_t val = cvmx_पढ़ो64(csr_addr);
	वापस val;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t cvmx_पढ़ोq_csr(व्योम __iomem *csr_addr)
अणु
	वापस cvmx_पढ़ो_csr((__क्रमce uपूर्णांक64_t) csr_addr);
पूर्ण

अटल अंतरभूत व्योम cvmx_send_single(uपूर्णांक64_t data)
अणु
	स्थिर uपूर्णांक64_t CVMX_IOBDMA_SENDSINGLE = 0xffffffffffffa200ull;
	cvmx_ग_लिखो64(CVMX_IOBDMA_SENDSINGLE, data);
पूर्ण

अटल अंतरभूत व्योम cvmx_पढ़ो_csr_async(uपूर्णांक64_t scraddr, uपूर्णांक64_t csr_addr)
अणु
	जोड़ अणु
		uपूर्णांक64_t u64;
		काष्ठा अणु
			uपूर्णांक64_t scraddr:8;
			uपूर्णांक64_t len:8;
			uपूर्णांक64_t addr:48;
		पूर्ण s;
	पूर्ण addr;
	addr.u64 = csr_addr;
	addr.s.scraddr = scraddr >> 3;
	addr.s.len = 1;
	cvmx_send_single(addr.u64);
पूर्ण

/* Return true अगर Octeon is CN38XX pass 1 */
अटल अंतरभूत पूर्णांक cvmx_octeon_is_pass1(व्योम)
अणु
#अगर OCTEON_IS_COMMON_BINARY()
	वापस 0;	/* Pass 1 isn't supported क्रम common binaries */
#अन्यथा
/* Now that we know we're built क्रम a specअगरic model, only check CN38XX */
#अगर OCTEON_IS_MODEL(OCTEON_CN38XX)
	वापस cvmx_get_proc_id() == OCTEON_CN38XX_PASS1;
#अन्यथा
	वापस 0;	/* Built क्रम non CN38XX chip, we're not CN38XX pass1 */
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cvmx_get_core_num(व्योम)
अणु
	अचिन्हित पूर्णांक core_num;
	CVMX_RDHWRNV(core_num, 0);
	वापस core_num;
पूर्ण

/* Maximum # of bits to define core in node */
#घोषणा CVMX_NODE_NO_SHIFT	7
#घोषणा CVMX_NODE_MASK		0x3
अटल अंतरभूत अचिन्हित पूर्णांक cvmx_get_node_num(व्योम)
अणु
	अचिन्हित पूर्णांक core_num = cvmx_get_core_num();

	वापस (core_num >> CVMX_NODE_NO_SHIFT) & CVMX_NODE_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cvmx_get_local_core_num(व्योम)
अणु
	वापस cvmx_get_core_num() & ((1 << CVMX_NODE_NO_SHIFT) - 1);
पूर्ण

#घोषणा CVMX_NODE_BITS         (2)     /* Number of bits to define a node */
#घोषणा CVMX_MAX_NODES         (1 << CVMX_NODE_BITS)
#घोषणा CVMX_NODE_IO_SHIFT     (36)
#घोषणा CVMX_NODE_MEM_SHIFT    (40)
#घोषणा CVMX_NODE_IO_MASK      ((uपूर्णांक64_t)CVMX_NODE_MASK << CVMX_NODE_IO_SHIFT)

अटल अंतरभूत व्योम cvmx_ग_लिखो_csr_node(uपूर्णांक64_t node, uपूर्णांक64_t csr_addr,
				       uपूर्णांक64_t val)
अणु
	uपूर्णांक64_t composite_csr_addr, node_addr;

	node_addr = (node & CVMX_NODE_MASK) << CVMX_NODE_IO_SHIFT;
	composite_csr_addr = (csr_addr & ~CVMX_NODE_IO_MASK) | node_addr;

	cvmx_ग_लिखो64_uपूर्णांक64(composite_csr_addr, val);
	अगर (((csr_addr >> 40) & 0x7ffff) == (0x118))
		cvmx_पढ़ो64_uपूर्णांक64(CVMX_MIO_BOOT_BIST_STAT | node_addr);
पूर्ण

अटल अंतरभूत uपूर्णांक64_t cvmx_पढ़ो_csr_node(uपूर्णांक64_t node, uपूर्णांक64_t csr_addr)
अणु
	uपूर्णांक64_t node_addr;

	node_addr = (csr_addr & ~CVMX_NODE_IO_MASK) |
		    (node & CVMX_NODE_MASK) << CVMX_NODE_IO_SHIFT;
	वापस cvmx_पढ़ो_csr(node_addr);
पूर्ण

/**
 * Returns the number of bits set in the provided value.
 * Simple wrapper क्रम POP inकाष्ठाion.
 *
 * @val:    32 bit value to count set bits in
 *
 * Returns Number of bits set
 */
अटल अंतरभूत uपूर्णांक32_t cvmx_pop(uपूर्णांक32_t val)
अणु
	uपूर्णांक32_t pop;
	CVMX_POP(pop, val);
	वापस pop;
पूर्ण

/**
 * Returns the number of bits set in the provided value.
 * Simple wrapper क्रम DPOP inकाष्ठाion.
 *
 * @val:    64 bit value to count set bits in
 *
 * Returns Number of bits set
 */
अटल अंतरभूत पूर्णांक cvmx_dpop(uपूर्णांक64_t val)
अणु
	पूर्णांक pop;
	CVMX_DPOP(pop, val);
	वापस pop;
पूर्ण

/**
 * Provide current cycle counter as a वापस value
 *
 * Returns current cycle counter
 */

अटल अंतरभूत uपूर्णांक64_t cvmx_get_cycle(व्योम)
अणु
	uपूर्णांक64_t cycle;
	CVMX_RDHWR(cycle, 31);
	वापस cycle;
पूर्ण

/**
 * Reads a chip global cycle counter.  This counts CPU cycles since
 * chip reset.	The counter is 64 bit.
 * This रेजिस्टर करोes not exist on CN38XX pass 1 silicion
 *
 * Returns Global chip cycle count since chip reset.
 */
अटल अंतरभूत uपूर्णांक64_t cvmx_get_cycle_global(व्योम)
अणु
	अगर (cvmx_octeon_is_pass1())
		वापस 0;
	अन्यथा
		वापस cvmx_पढ़ो64(CVMX_IPD_CLK_COUNT);
पूर्ण

/**
 * This macro spins on a field रुकोing क्रम it to reach a value. It
 * is common in code to need to रुको क्रम a specअगरic field in a CSR
 * to match a specअगरic value. Conceptually this macro expands to:
 *
 * 1) पढ़ो csr at "address" with a csr प्रकार of "type"
 * 2) Check अगर ("type".s."field" "op" "value")
 * 3) If #2 isn't true loop to #1 unless too much समय has passed.
 */
#घोषणा CVMX_WAIT_FOR_FIELD64(address, type, field, op, value, समयout_usec)\
    (									\
अणु									\
	पूर्णांक result;							\
	करो अणु								\
		uपूर्णांक64_t करोne = cvmx_get_cycle() + (uपूर्णांक64_t)समयout_usec * \
			cvmx_sysinfo_get()->cpu_घड़ी_hz / 1000000;	\
		type c;							\
		जबतक (1) अणु						\
			c.u64 = cvmx_पढ़ो_csr(address);			\
			अगर ((c.s.field) op(value)) अणु			\
				result = 0;				\
				अवरोध;					\
			पूर्ण अन्यथा अगर (cvmx_get_cycle() > करोne) अणु		\
				result = -1;				\
				अवरोध;					\
			पूर्ण अन्यथा						\
				__delay(100);				\
		पूर्ण							\
	पूर्ण जबतक (0);							\
	result;								\
पूर्ण)

/***************************************************************************/

/* Return the number of cores available in the chip */
अटल अंतरभूत uपूर्णांक32_t cvmx_octeon_num_cores(व्योम)
अणु
	u64 ciu_fuse_reg;
	u64 ciu_fuse;

	अगर (OCTEON_IS_OCTEON3() && !OCTEON_IS_MODEL(OCTEON_CN70XX))
		ciu_fuse_reg = CVMX_CIU3_FUSE;
	अन्यथा
		ciu_fuse_reg = CVMX_CIU_FUSE;
	ciu_fuse = cvmx_पढ़ो_csr(ciu_fuse_reg);
	वापस cvmx_dpop(ciu_fuse);
पूर्ण

#पूर्ण_अगर /*  __CVMX_H__  */
