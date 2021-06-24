<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2009 Cavium Networks
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

/**
 * Typedefs and defines क्रम working with Octeon physical addresses.
 *
 */
#अगर_अघोषित __CVMX_ADDRESS_H__
#घोषणा __CVMX_ADDRESS_H__

#अगर 0
प्रकार क्रमागत अणु
	CVMX_MIPS_SPACE_XKSEG = 3LL,
	CVMX_MIPS_SPACE_XKPHYS = 2LL,
	CVMX_MIPS_SPACE_XSSEG = 1LL,
	CVMX_MIPS_SPACE_XUSEG = 0LL
पूर्ण cvmx_mips_space_t;
#पूर्ण_अगर

प्रकार क्रमागत अणु
	CVMX_MIPS_XKSEG_SPACE_KSEG0 = 0LL,
	CVMX_MIPS_XKSEG_SPACE_KSEG1 = 1LL,
	CVMX_MIPS_XKSEG_SPACE_SSEG = 2LL,
	CVMX_MIPS_XKSEG_SPACE_KSEG3 = 3LL
पूर्ण cvmx_mips_xkseg_space_t;

/* decodes <14:13> of a kseg3 winकरोw address */
प्रकार क्रमागत अणु
	CVMX_ADD_WIN_SCR = 0L,
	/* see cvmx_add_win_dma_dec_t क्रम further decode */
	CVMX_ADD_WIN_DMA = 1L,
	CVMX_ADD_WIN_UNUSED = 2L,
	CVMX_ADD_WIN_UNUSED2 = 3L
पूर्ण cvmx_add_win_dec_t;

/* decode within DMA space */
प्रकार क्रमागत अणु
	/*
	 * Add store data to the ग_लिखो buffer entry, allocating it अगर
	 * necessary.
	 */
	CVMX_ADD_WIN_DMA_ADD = 0L,
	/* send out the ग_लिखो buffer entry to DRAM */
	CVMX_ADD_WIN_DMA_SENDMEM = 1L,
	/* store data must be normal DRAM memory space address in this हाल */
	/* send out the ग_लिखो buffer entry as an IOBDMA command */
	CVMX_ADD_WIN_DMA_SENDDMA = 2L,
	/* see CVMX_ADD_WIN_DMA_SEND_DEC क्रम data contents */
	/* send out the ग_लिखो buffer entry as an IO ग_लिखो */
	CVMX_ADD_WIN_DMA_SENDIO = 3L,
	/* store data must be normal IO space address in this हाल */
	/* send out a single-tick command on the NCB bus */
	CVMX_ADD_WIN_DMA_SENDSINGLE = 4L,
	/* no ग_लिखो buffer data needed/used */
पूर्ण cvmx_add_win_dma_dec_t;

/*
 *   Physical Address Decode
 *
 * Octeon-I HW never पूर्णांकerprets this X (<39:36> reserved
 * क्रम future expansion), software should set to 0.
 *
 *  - 0x0 XXX0 0000 0000 to	 DRAM	      Cached
 *  - 0x0 XXX0 0FFF FFFF
 *
 *  - 0x0 XXX0 1000 0000 to	 Boot Bus     Uncached	(Converted to 0x1 00X0 1000 0000
 *  - 0x0 XXX0 1FFF FFFF	 + EJTAG			   to 0x1 00X0 1FFF FFFF)
 *
 *  - 0x0 XXX0 2000 0000 to	 DRAM	      Cached
 *  - 0x0 XXXF FFFF FFFF
 *
 *  - 0x1 00X0 0000 0000 to	 Boot Bus     Uncached
 *  - 0x1 00XF FFFF FFFF
 *
 *  - 0x1 01X0 0000 0000 to	 Other NCB    Uncached
 *  - 0x1 FFXF FFFF FFFF	 devices
 *
 * Decode of all Octeon addresses
 */
प्रकार जोड़ अणु

	uपूर्णांक64_t u64;
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	/* mapped or unmapped भव address */
	काष्ठा अणु
		uपूर्णांक64_t R:2;
		uपूर्णांक64_t offset:62;
	पूर्ण sva;

	/* mapped USEG भव addresses (typically) */
	काष्ठा अणु
		uपूर्णांक64_t zeroes:33;
		uपूर्णांक64_t offset:31;
	पूर्ण suseg;

	/* mapped or unmapped भव address */
	काष्ठा अणु
		uपूर्णांक64_t ones:33;
		uपूर्णांक64_t sp:2;
		uपूर्णांक64_t offset:29;
	पूर्ण sxkseg;

	/*
	 * physical address accessed through xkphys unmapped भव
	 * address.
	 */
	काष्ठा अणु
		uपूर्णांक64_t R:2;	/* CVMX_MIPS_SPACE_XKPHYS in this हाल */
		uपूर्णांक64_t cca:3; /* ignored by octeon */
		uपूर्णांक64_t mbz:10;
		uपूर्णांक64_t pa:49; /* physical address */
	पूर्ण sxkphys;

	/* physical address */
	काष्ठा अणु
		uपूर्णांक64_t mbz:15;
		/* अगर set, the address is uncached and resides on MCB bus */
		uपूर्णांक64_t is_io:1;
		/*
		 * the hardware ignores this field when is_io==0, अन्यथा
		 * device ID.
		 */
		uपूर्णांक64_t did:8;
		/* the hardware ignores <39:36> in Octeon I */
		uपूर्णांक64_t unaddr:4;
		uपूर्णांक64_t offset:36;
	पूर्ण sphys;

	/* physical mem address */
	काष्ठा अणु
		/* technically, <47:40> are करोnt-cares */
		uपूर्णांक64_t zeroes:24;
		/* the hardware ignores <39:36> in Octeon I */
		uपूर्णांक64_t unaddr:4;
		uपूर्णांक64_t offset:36;
	पूर्ण smem;

	/* physical IO address */
	काष्ठा अणु
		uपूर्णांक64_t mem_region:2;
		uपूर्णांक64_t mbz:13;
		/* 1 in this हाल */
		uपूर्णांक64_t is_io:1;
		/*
		 * The hardware ignores this field when is_io==0, अन्यथा
		 * device ID.
		 */
		uपूर्णांक64_t did:8;
		/* the hardware ignores <39:36> in Octeon I */
		uपूर्णांक64_t unaddr:4;
		uपूर्णांक64_t offset:36;
	पूर्ण sio;

	/*
	 * Scratchpad भव address - accessed through a winकरोw at
	 * the end of kseg3
	 */
	काष्ठा अणु
		uपूर्णांक64_t ones:49;
		/* CVMX_ADD_WIN_SCR (0) in this हाल */
		cvmx_add_win_dec_t csrdec:2;
		uपूर्णांक64_t addr:13;
	पूर्ण sscr;

	/* there should only be stores to IOBDMA space, no loads */
	/*
	 * IOBDMA भव address - accessed through a winकरोw at the
	 * end of kseg3
	 */
	काष्ठा अणु
		uपूर्णांक64_t ones:49;
		uपूर्णांक64_t csrdec:2;	/* CVMX_ADD_WIN_DMA (1) in this हाल */
		uपूर्णांक64_t unused2:3;
		uपूर्णांक64_t type:3;
		uपूर्णांक64_t addr:7;
	पूर्ण sdma;

	काष्ठा अणु
		uपूर्णांक64_t didspace:24;
		uपूर्णांक64_t unused:40;
	पूर्ण sfilldidspace;
#अन्यथा
	काष्ठा अणु
		uपूर्णांक64_t offset:62;
		uपूर्णांक64_t R:2;
	पूर्ण sva;

	काष्ठा अणु
		uपूर्णांक64_t offset:31;
		uपूर्णांक64_t zeroes:33;
	पूर्ण suseg;

	काष्ठा अणु
		uपूर्णांक64_t offset:29;
		uपूर्णांक64_t sp:2;
		uपूर्णांक64_t ones:33;
	पूर्ण sxkseg;

	काष्ठा अणु
		uपूर्णांक64_t pa:49;
		uपूर्णांक64_t mbz:10;
		uपूर्णांक64_t cca:3;
		uपूर्णांक64_t R:2;
	पूर्ण sxkphys;

	काष्ठा अणु
		uपूर्णांक64_t offset:36;
		uपूर्णांक64_t unaddr:4;
		uपूर्णांक64_t did:8;
		uपूर्णांक64_t is_io:1;
		uपूर्णांक64_t mbz:15;
	पूर्ण sphys;

	काष्ठा अणु
		uपूर्णांक64_t offset:36;
		uपूर्णांक64_t unaddr:4;
		uपूर्णांक64_t zeroes:24;
	पूर्ण smem;

	काष्ठा अणु
		uपूर्णांक64_t offset:36;
		uपूर्णांक64_t unaddr:4;
		uपूर्णांक64_t did:8;
		uपूर्णांक64_t is_io:1;
		uपूर्णांक64_t mbz:13;
		uपूर्णांक64_t mem_region:2;
	पूर्ण sio;

	काष्ठा अणु
		uपूर्णांक64_t addr:13;
		cvmx_add_win_dec_t csrdec:2;
		uपूर्णांक64_t ones:49;
	पूर्ण sscr;

	काष्ठा अणु
		uपूर्णांक64_t addr:7;
		uपूर्णांक64_t type:3;
		uपूर्णांक64_t unused2:3;
		uपूर्णांक64_t csrdec:2;
		uपूर्णांक64_t ones:49;
	पूर्ण sdma;

	काष्ठा अणु
		uपूर्णांक64_t unused:40;
		uपूर्णांक64_t didspace:24;
	पूर्ण sfilldidspace;
#पूर्ण_अगर

पूर्ण cvmx_addr_t;

/* These macros क्रम used by 32 bit applications */

#घोषणा CVMX_MIPS32_SPACE_KSEG0 1l
#घोषणा CVMX_ADD_SEG32(segment, add) \
	(((पूर्णांक32_t)segment << 31) | (पूर्णांक32_t)(add))

/*
 * Currently all IOs are perक्रमmed using XKPHYS addressing. Linux uses
 * the CvmMemCtl रेजिस्टर to enable XKPHYS addressing to IO space from
 * user mode.  Future OSes may need to change the upper bits of IO
 * addresses. The following define controls the upper two bits क्रम all
 * IO addresses generated by the simple executive library.
 */
#घोषणा CVMX_IO_SEG CVMX_MIPS_SPACE_XKPHYS

/* These macros simplअगरy the process of creating common IO addresses */
#घोषणा CVMX_ADD_SEG(segment, add) ((((uपूर्णांक64_t)segment) << 62) | (add))
#अगर_अघोषित CVMX_ADD_IO_SEG
#घोषणा CVMX_ADD_IO_SEG(add) CVMX_ADD_SEG(CVMX_IO_SEG, (add))
#पूर्ण_अगर
#घोषणा CVMX_ADDR_DIDSPACE(did) (((CVMX_IO_SEG) << 22) | ((1ULL) << 8) | (did))
#घोषणा CVMX_ADDR_DID(did) (CVMX_ADDR_DIDSPACE(did) << 40)
#घोषणा CVMX_FULL_DID(did, subdid) (((did) << 3) | (subdid))

  /* from include/ncb_rsl_id.v */
#घोषणा CVMX_OCT_DID_MIS 0ULL	/* misc stuff */
#घोषणा CVMX_OCT_DID_GMX0 1ULL
#घोषणा CVMX_OCT_DID_GMX1 2ULL
#घोषणा CVMX_OCT_DID_PCI 3ULL
#घोषणा CVMX_OCT_DID_KEY 4ULL
#घोषणा CVMX_OCT_DID_FPA 5ULL
#घोषणा CVMX_OCT_DID_DFA 6ULL
#घोषणा CVMX_OCT_DID_ZIP 7ULL
#घोषणा CVMX_OCT_DID_RNG 8ULL
#घोषणा CVMX_OCT_DID_IPD 9ULL
#घोषणा CVMX_OCT_DID_PKT 10ULL
#घोषणा CVMX_OCT_DID_TIM 11ULL
#घोषणा CVMX_OCT_DID_TAG 12ULL
  /* the rest are not on the IO bus */
#घोषणा CVMX_OCT_DID_L2C 16ULL
#घोषणा CVMX_OCT_DID_LMC 17ULL
#घोषणा CVMX_OCT_DID_SPX0 18ULL
#घोषणा CVMX_OCT_DID_SPX1 19ULL
#घोषणा CVMX_OCT_DID_PIP 20ULL
#घोषणा CVMX_OCT_DID_ASX0 22ULL
#घोषणा CVMX_OCT_DID_ASX1 23ULL
#घोषणा CVMX_OCT_DID_IOB 30ULL

#घोषणा CVMX_OCT_DID_PKT_SEND	    CVMX_FULL_DID(CVMX_OCT_DID_PKT, 2ULL)
#घोषणा CVMX_OCT_DID_TAG_SWTAG	    CVMX_FULL_DID(CVMX_OCT_DID_TAG, 0ULL)
#घोषणा CVMX_OCT_DID_TAG_TAG1	    CVMX_FULL_DID(CVMX_OCT_DID_TAG, 1ULL)
#घोषणा CVMX_OCT_DID_TAG_TAG2	    CVMX_FULL_DID(CVMX_OCT_DID_TAG, 2ULL)
#घोषणा CVMX_OCT_DID_TAG_TAG3	    CVMX_FULL_DID(CVMX_OCT_DID_TAG, 3ULL)
#घोषणा CVMX_OCT_DID_TAG_शून्य_RD    CVMX_FULL_DID(CVMX_OCT_DID_TAG, 4ULL)
#घोषणा CVMX_OCT_DID_TAG_CSR	    CVMX_FULL_DID(CVMX_OCT_DID_TAG, 7ULL)
#घोषणा CVMX_OCT_DID_FAU_FAI	    CVMX_FULL_DID(CVMX_OCT_DID_IOB, 0ULL)
#घोषणा CVMX_OCT_DID_TIM_CSR	    CVMX_FULL_DID(CVMX_OCT_DID_TIM, 0ULL)
#घोषणा CVMX_OCT_DID_KEY_RW	    CVMX_FULL_DID(CVMX_OCT_DID_KEY, 0ULL)
#घोषणा CVMX_OCT_DID_PCI_6	    CVMX_FULL_DID(CVMX_OCT_DID_PCI, 6ULL)
#घोषणा CVMX_OCT_DID_MIS_BOO	    CVMX_FULL_DID(CVMX_OCT_DID_MIS, 0ULL)
#घोषणा CVMX_OCT_DID_PCI_RML	    CVMX_FULL_DID(CVMX_OCT_DID_PCI, 0ULL)
#घोषणा CVMX_OCT_DID_IPD_CSR	    CVMX_FULL_DID(CVMX_OCT_DID_IPD, 7ULL)
#घोषणा CVMX_OCT_DID_DFA_CSR	    CVMX_FULL_DID(CVMX_OCT_DID_DFA, 7ULL)
#घोषणा CVMX_OCT_DID_MIS_CSR	    CVMX_FULL_DID(CVMX_OCT_DID_MIS, 7ULL)
#घोषणा CVMX_OCT_DID_ZIP_CSR	    CVMX_FULL_DID(CVMX_OCT_DID_ZIP, 0ULL)

#पूर्ण_अगर /* __CVMX_ADDRESS_H__ */
