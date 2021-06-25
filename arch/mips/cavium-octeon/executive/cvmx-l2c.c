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

/*
 * Implementation of the Level 2 Cache (L2C) control,
 * measurement, and debugging facilities.
 */

#समावेश <linux/compiler.h>
#समावेश <linux/irqflags.h>
#समावेश <यंत्र/octeon/cvmx.h>
#समावेश <यंत्र/octeon/cvmx-l2c.h>
#समावेश <यंत्र/octeon/cvmx-spinlock.h>

/*
 * This spinlock is used पूर्णांकernally to ensure that only one core is
 * perक्रमming certain L2 operations at a समय.
 *
 * NOTE: This only protects calls from within a single application -
 * अगर multiple applications or operating प्रणालीs are running, then it
 * is up to the user program to coordinate between them.
 */
अटल cvmx_spinlock_t cvmx_l2c_spinlock;

पूर्णांक cvmx_l2c_get_core_way_partition(uपूर्णांक32_t core)
अणु
	uपूर्णांक32_t field;

	/* Validate the core number */
	अगर (core >= cvmx_octeon_num_cores())
		वापस -1;

	अगर (OCTEON_IS_MODEL(OCTEON_CN63XX))
		वापस cvmx_पढ़ो_csr(CVMX_L2C_WPAR_PPX(core)) & 0xffff;

	/*
	 * Use the lower two bits of the coreNumber to determine the
	 * bit offset of the UMSK[] field in the L2C_SPAR रेजिस्टर.
	 */
	field = (core & 0x3) * 8;

	/*
	 * Return the UMSK[] field from the appropriate L2C_SPAR
	 * रेजिस्टर based on the coreNumber.
	 */

	चयन (core & 0xC) अणु
	हाल 0x0:
		वापस (cvmx_पढ़ो_csr(CVMX_L2C_SPAR0) & (0xFF << field)) >> field;
	हाल 0x4:
		वापस (cvmx_पढ़ो_csr(CVMX_L2C_SPAR1) & (0xFF << field)) >> field;
	हाल 0x8:
		वापस (cvmx_पढ़ो_csr(CVMX_L2C_SPAR2) & (0xFF << field)) >> field;
	हाल 0xC:
		वापस (cvmx_पढ़ो_csr(CVMX_L2C_SPAR3) & (0xFF << field)) >> field;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cvmx_l2c_set_core_way_partition(uपूर्णांक32_t core, uपूर्णांक32_t mask)
अणु
	uपूर्णांक32_t field;
	uपूर्णांक32_t valid_mask;

	valid_mask = (0x1 << cvmx_l2c_get_num_assoc()) - 1;

	mask &= valid_mask;

	/* A UMSK setting which blocks all L2C Ways is an error on some chips */
	अगर (mask == valid_mask && !OCTEON_IS_MODEL(OCTEON_CN63XX))
		वापस -1;

	/* Validate the core number */
	अगर (core >= cvmx_octeon_num_cores())
		वापस -1;

	अगर (OCTEON_IS_MODEL(OCTEON_CN63XX)) अणु
		cvmx_ग_लिखो_csr(CVMX_L2C_WPAR_PPX(core), mask);
		वापस 0;
	पूर्ण

	/*
	 * Use the lower two bits of core to determine the bit offset of the
	 * UMSK[] field in the L2C_SPAR रेजिस्टर.
	 */
	field = (core & 0x3) * 8;

	/*
	 * Assign the new mask setting to the UMSK[] field in the appropriate
	 * L2C_SPAR रेजिस्टर based on the core_num.
	 *
	 */
	चयन (core & 0xC) अणु
	हाल 0x0:
		cvmx_ग_लिखो_csr(CVMX_L2C_SPAR0,
			       (cvmx_पढ़ो_csr(CVMX_L2C_SPAR0) & ~(0xFF << field)) |
			       mask << field);
		अवरोध;
	हाल 0x4:
		cvmx_ग_लिखो_csr(CVMX_L2C_SPAR1,
			       (cvmx_पढ़ो_csr(CVMX_L2C_SPAR1) & ~(0xFF << field)) |
			       mask << field);
		अवरोध;
	हाल 0x8:
		cvmx_ग_लिखो_csr(CVMX_L2C_SPAR2,
			       (cvmx_पढ़ो_csr(CVMX_L2C_SPAR2) & ~(0xFF << field)) |
			       mask << field);
		अवरोध;
	हाल 0xC:
		cvmx_ग_लिखो_csr(CVMX_L2C_SPAR3,
			       (cvmx_पढ़ो_csr(CVMX_L2C_SPAR3) & ~(0xFF << field)) |
			       mask << field);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cvmx_l2c_set_hw_way_partition(uपूर्णांक32_t mask)
अणु
	uपूर्णांक32_t valid_mask;

	valid_mask = (0x1 << cvmx_l2c_get_num_assoc()) - 1;
	mask &= valid_mask;

	/* A UMSK setting which blocks all L2C Ways is an error on some chips */
	अगर (mask == valid_mask	&& !OCTEON_IS_MODEL(OCTEON_CN63XX))
		वापस -1;

	अगर (OCTEON_IS_MODEL(OCTEON_CN63XX))
		cvmx_ग_लिखो_csr(CVMX_L2C_WPAR_IOBX(0), mask);
	अन्यथा
		cvmx_ग_लिखो_csr(CVMX_L2C_SPAR4,
			       (cvmx_पढ़ो_csr(CVMX_L2C_SPAR4) & ~0xFF) | mask);
	वापस 0;
पूर्ण

पूर्णांक cvmx_l2c_get_hw_way_partition(व्योम)
अणु
	अगर (OCTEON_IS_MODEL(OCTEON_CN63XX))
		वापस cvmx_पढ़ो_csr(CVMX_L2C_WPAR_IOBX(0)) & 0xffff;
	अन्यथा
		वापस cvmx_पढ़ो_csr(CVMX_L2C_SPAR4) & (0xFF);
पूर्ण

व्योम cvmx_l2c_config_perf(uपूर्णांक32_t counter, क्रमागत cvmx_l2c_event event,
			  uपूर्णांक32_t clear_on_पढ़ो)
अणु
	अगर (OCTEON_IS_MODEL(OCTEON_CN5XXX) || OCTEON_IS_MODEL(OCTEON_CN3XXX)) अणु
		जोड़ cvmx_l2c_pfctl pfctl;

		pfctl.u64 = cvmx_पढ़ो_csr(CVMX_L2C_PFCTL);

		चयन (counter) अणु
		हाल 0:
			pfctl.s.cnt0sel = event;
			pfctl.s.cnt0ena = 1;
			pfctl.s.cnt0rdclr = clear_on_पढ़ो;
			अवरोध;
		हाल 1:
			pfctl.s.cnt1sel = event;
			pfctl.s.cnt1ena = 1;
			pfctl.s.cnt1rdclr = clear_on_पढ़ो;
			अवरोध;
		हाल 2:
			pfctl.s.cnt2sel = event;
			pfctl.s.cnt2ena = 1;
			pfctl.s.cnt2rdclr = clear_on_पढ़ो;
			अवरोध;
		हाल 3:
		शेष:
			pfctl.s.cnt3sel = event;
			pfctl.s.cnt3ena = 1;
			pfctl.s.cnt3rdclr = clear_on_पढ़ो;
			अवरोध;
		पूर्ण

		cvmx_ग_लिखो_csr(CVMX_L2C_PFCTL, pfctl.u64);
	पूर्ण अन्यथा अणु
		जोड़ cvmx_l2c_tadx_prf l2c_tadx_prf;
		पूर्णांक tad;

		cvmx_dम_लिखो("L2C performance counter events are different for this chip, mapping 'event' to cvmx_l2c_tad_event_t\n");
		अगर (clear_on_पढ़ो)
			cvmx_dम_लिखो("L2C counters don't support clear on read for this chip\n");

		l2c_tadx_prf.u64 = cvmx_पढ़ो_csr(CVMX_L2C_TADX_PRF(0));

		चयन (counter) अणु
		हाल 0:
			l2c_tadx_prf.s.cnt0sel = event;
			अवरोध;
		हाल 1:
			l2c_tadx_prf.s.cnt1sel = event;
			अवरोध;
		हाल 2:
			l2c_tadx_prf.s.cnt2sel = event;
			अवरोध;
		शेष:
		हाल 3:
			l2c_tadx_prf.s.cnt3sel = event;
			अवरोध;
		पूर्ण
		क्रम (tad = 0; tad < CVMX_L2C_TADS; tad++)
			cvmx_ग_लिखो_csr(CVMX_L2C_TADX_PRF(tad),
				       l2c_tadx_prf.u64);
	पूर्ण
पूर्ण

uपूर्णांक64_t cvmx_l2c_पढ़ो_perf(uपूर्णांक32_t counter)
अणु
	चयन (counter) अणु
	हाल 0:
		अगर (OCTEON_IS_MODEL(OCTEON_CN5XXX) || OCTEON_IS_MODEL(OCTEON_CN3XXX))
			वापस cvmx_पढ़ो_csr(CVMX_L2C_PFC0);
		अन्यथा अणु
			uपूर्णांक64_t counter = 0;
			पूर्णांक tad;

			क्रम (tad = 0; tad < CVMX_L2C_TADS; tad++)
				counter += cvmx_पढ़ो_csr(CVMX_L2C_TADX_PFC0(tad));
			वापस counter;
		पूर्ण
	हाल 1:
		अगर (OCTEON_IS_MODEL(OCTEON_CN5XXX) || OCTEON_IS_MODEL(OCTEON_CN3XXX))
			वापस cvmx_पढ़ो_csr(CVMX_L2C_PFC1);
		अन्यथा अणु
			uपूर्णांक64_t counter = 0;
			पूर्णांक tad;

			क्रम (tad = 0; tad < CVMX_L2C_TADS; tad++)
				counter += cvmx_पढ़ो_csr(CVMX_L2C_TADX_PFC1(tad));
			वापस counter;
		पूर्ण
	हाल 2:
		अगर (OCTEON_IS_MODEL(OCTEON_CN5XXX) || OCTEON_IS_MODEL(OCTEON_CN3XXX))
			वापस cvmx_पढ़ो_csr(CVMX_L2C_PFC2);
		अन्यथा अणु
			uपूर्णांक64_t counter = 0;
			पूर्णांक tad;

			क्रम (tad = 0; tad < CVMX_L2C_TADS; tad++)
				counter += cvmx_पढ़ो_csr(CVMX_L2C_TADX_PFC2(tad));
			वापस counter;
		पूर्ण
	हाल 3:
	शेष:
		अगर (OCTEON_IS_MODEL(OCTEON_CN5XXX) || OCTEON_IS_MODEL(OCTEON_CN3XXX))
			वापस cvmx_पढ़ो_csr(CVMX_L2C_PFC3);
		अन्यथा अणु
			uपूर्णांक64_t counter = 0;
			पूर्णांक tad;

			क्रम (tad = 0; tad < CVMX_L2C_TADS; tad++)
				counter += cvmx_पढ़ो_csr(CVMX_L2C_TADX_PFC3(tad));
			वापस counter;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * @INTERNAL
 * Helper function use to fault in cache lines क्रम L2 cache locking
 *
 * @addr:   Address of base of memory region to पढ़ो पूर्णांकo L2 cache
 * @len:    Length (in bytes) of region to fault in
 */
अटल व्योम fault_in(uपूर्णांक64_t addr, पूर्णांक len)
अणु
	अक्षर *ptr;

	/*
	 * Adjust addr and length so we get all cache lines even क्रम
	 * small ranges spanning two cache lines.
	 */
	len += addr & CVMX_CACHE_LINE_MASK;
	addr &= ~CVMX_CACHE_LINE_MASK;
	ptr = cvmx_phys_to_ptr(addr);
	/*
	 * Invalidate L1 cache to make sure all loads result in data
	 * being in L2.
	 */
	CVMX_DCACHE_INVALIDATE;
	जबतक (len > 0) अणु
		READ_ONCE(*ptr);
		len -= CVMX_CACHE_LINE_SIZE;
		ptr += CVMX_CACHE_LINE_SIZE;
	पूर्ण
पूर्ण

पूर्णांक cvmx_l2c_lock_line(uपूर्णांक64_t addr)
अणु
	अगर (OCTEON_IS_MODEL(OCTEON_CN63XX)) अणु
		पूर्णांक shअगरt = CVMX_L2C_TAG_ADDR_ALIAS_SHIFT;
		uपूर्णांक64_t assoc = cvmx_l2c_get_num_assoc();
		uपूर्णांक64_t tag = addr >> shअगरt;
		uपूर्णांक64_t index = CVMX_ADD_SEG(CVMX_MIPS_SPACE_XKPHYS, cvmx_l2c_address_to_index(addr) << CVMX_L2C_IDX_ADDR_SHIFT);
		uपूर्णांक64_t way;
		जोड़ cvmx_l2c_tadx_tag l2c_tadx_tag;

		CVMX_CACHE_LCKL2(CVMX_ADD_SEG(CVMX_MIPS_SPACE_XKPHYS, addr), 0);

		/* Make sure we were able to lock the line */
		क्रम (way = 0; way < assoc; way++) अणु
			CVMX_CACHE_LTGL2I(index | (way << shअगरt), 0);
			/* make sure CVMX_L2C_TADX_TAG is updated */
			CVMX_SYNC;
			l2c_tadx_tag.u64 = cvmx_पढ़ो_csr(CVMX_L2C_TADX_TAG(0));
			अगर (l2c_tadx_tag.s.valid && l2c_tadx_tag.s.tag == tag)
				अवरोध;
		पूर्ण

		/* Check अगर a valid line is found */
		अगर (way >= assoc) अणु
			/* cvmx_dम_लिखो("ERROR: cvmx_l2c_lock_line: line not found for locking at 0x%llx address\n", (अचिन्हित दीर्घ दीर्घ)addr); */
			वापस -1;
		पूर्ण

		/* Check अगर lock bit is not set */
		अगर (!l2c_tadx_tag.s.lock) अणु
			/* cvmx_dम_लिखो("ERROR: cvmx_l2c_lock_line: Not able to lock at 0x%llx address\n", (अचिन्हित दीर्घ दीर्घ)addr); */
			वापस -1;
		पूर्ण
		वापस way;
	पूर्ण अन्यथा अणु
		पूर्णांक retval = 0;
		जोड़ cvmx_l2c_dbg l2cdbg;
		जोड़ cvmx_l2c_lckbase lckbase;
		जोड़ cvmx_l2c_lckoff lckoff;
		जोड़ cvmx_l2t_err l2t_err;

		cvmx_spinlock_lock(&cvmx_l2c_spinlock);

		l2cdbg.u64 = 0;
		lckbase.u64 = 0;
		lckoff.u64 = 0;

		/* Clear l2t error bits अगर set */
		l2t_err.u64 = cvmx_पढ़ो_csr(CVMX_L2T_ERR);
		l2t_err.s.lckerr = 1;
		l2t_err.s.lckerr2 = 1;
		cvmx_ग_लिखो_csr(CVMX_L2T_ERR, l2t_err.u64);

		addr &= ~CVMX_CACHE_LINE_MASK;

		/* Set this core as debug core */
		l2cdbg.s.ppnum = cvmx_get_core_num();
		CVMX_SYNC;
		cvmx_ग_लिखो_csr(CVMX_L2C_DBG, l2cdbg.u64);
		cvmx_पढ़ो_csr(CVMX_L2C_DBG);

		lckoff.s.lck_offset = 0; /* Only lock 1 line at a समय */
		cvmx_ग_लिखो_csr(CVMX_L2C_LCKOFF, lckoff.u64);
		cvmx_पढ़ो_csr(CVMX_L2C_LCKOFF);

		अगर (((जोड़ cvmx_l2c_cfg)(cvmx_पढ़ो_csr(CVMX_L2C_CFG))).s.idxalias) अणु
			पूर्णांक alias_shअगरt = CVMX_L2C_IDX_ADDR_SHIFT + 2 * CVMX_L2_SET_BITS - 1;
			uपूर्णांक64_t addr_पंचांगp = addr ^ (addr & ((1 << alias_shअगरt) - 1)) >> CVMX_L2_SET_BITS;

			lckbase.s.lck_base = addr_पंचांगp >> 7;

		पूर्ण अन्यथा अणु
			lckbase.s.lck_base = addr >> 7;
		पूर्ण

		lckbase.s.lck_ena = 1;
		cvmx_ग_लिखो_csr(CVMX_L2C_LCKBASE, lckbase.u64);
		/* Make sure it माला_लो there */
		cvmx_पढ़ो_csr(CVMX_L2C_LCKBASE);

		fault_in(addr, CVMX_CACHE_LINE_SIZE);

		lckbase.s.lck_ena = 0;
		cvmx_ग_लिखो_csr(CVMX_L2C_LCKBASE, lckbase.u64);
		/* Make sure it माला_लो there */
		cvmx_पढ़ो_csr(CVMX_L2C_LCKBASE);

		/* Stop being debug core */
		cvmx_ग_लिखो_csr(CVMX_L2C_DBG, 0);
		cvmx_पढ़ो_csr(CVMX_L2C_DBG);

		l2t_err.u64 = cvmx_पढ़ो_csr(CVMX_L2T_ERR);
		अगर (l2t_err.s.lckerr || l2t_err.s.lckerr2)
			retval = 1;  /* We were unable to lock the line */

		cvmx_spinlock_unlock(&cvmx_l2c_spinlock);
		वापस retval;
	पूर्ण
पूर्ण

पूर्णांक cvmx_l2c_lock_mem_region(uपूर्णांक64_t start, uपूर्णांक64_t len)
अणु
	पूर्णांक retval = 0;

	/* Round start/end to cache line boundaries */
	len += start & CVMX_CACHE_LINE_MASK;
	start &= ~CVMX_CACHE_LINE_MASK;
	len = (len + CVMX_CACHE_LINE_MASK) & ~CVMX_CACHE_LINE_MASK;

	जबतक (len) अणु
		retval += cvmx_l2c_lock_line(start);
		start += CVMX_CACHE_LINE_SIZE;
		len -= CVMX_CACHE_LINE_SIZE;
	पूर्ण
	वापस retval;
पूर्ण

व्योम cvmx_l2c_flush(व्योम)
अणु
	uपूर्णांक64_t assoc, set;
	uपूर्णांक64_t n_assoc, n_set;

	n_set = cvmx_l2c_get_num_sets();
	n_assoc = cvmx_l2c_get_num_assoc();

	अगर (OCTEON_IS_MODEL(OCTEON_CN6XXX)) अणु
		uपूर्णांक64_t address;
		/* These may look like स्थिरants, but they aren't... */
		पूर्णांक assoc_shअगरt = CVMX_L2C_TAG_ADDR_ALIAS_SHIFT;
		पूर्णांक set_shअगरt = CVMX_L2C_IDX_ADDR_SHIFT;

		क्रम (set = 0; set < n_set; set++) अणु
			क्रम (assoc = 0; assoc < n_assoc; assoc++) अणु
				address = CVMX_ADD_SEG(CVMX_MIPS_SPACE_XKPHYS,
						       (assoc << assoc_shअगरt) | (set << set_shअगरt));
				CVMX_CACHE_WBIL2I(address, 0);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (set = 0; set < n_set; set++)
			क्रम (assoc = 0; assoc < n_assoc; assoc++)
				cvmx_l2c_flush_line(assoc, set);
	पूर्ण
पूर्ण


पूर्णांक cvmx_l2c_unlock_line(uपूर्णांक64_t address)
अणु

	अगर (OCTEON_IS_MODEL(OCTEON_CN63XX)) अणु
		पूर्णांक assoc;
		जोड़ cvmx_l2c_tag tag;
		uपूर्णांक32_t tag_addr;
		uपूर्णांक32_t index = cvmx_l2c_address_to_index(address);

		tag_addr = ((address >> CVMX_L2C_TAG_ADDR_ALIAS_SHIFT) & ((1 << CVMX_L2C_TAG_ADDR_ALIAS_SHIFT) - 1));

		/*
		 * For 63XX, we can flush a line by using the physical
		 * address directly, so finding the cache line used by
		 * the address is only required to provide the proper
		 * वापस value क्रम the function.
		 */
		क्रम (assoc = 0; assoc < CVMX_L2_ASSOC; assoc++) अणु
			tag = cvmx_l2c_get_tag(assoc, index);

			अगर (tag.s.V && (tag.s.addr == tag_addr)) अणु
				CVMX_CACHE_WBIL2(CVMX_ADD_SEG(CVMX_MIPS_SPACE_XKPHYS, address), 0);
				वापस tag.s.L;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक assoc;
		जोड़ cvmx_l2c_tag tag;
		uपूर्णांक32_t tag_addr;

		uपूर्णांक32_t index = cvmx_l2c_address_to_index(address);

		/* Compute portion of address that is stored in tag */
		tag_addr = ((address >> CVMX_L2C_TAG_ADDR_ALIAS_SHIFT) & ((1 << CVMX_L2C_TAG_ADDR_ALIAS_SHIFT) - 1));
		क्रम (assoc = 0; assoc < CVMX_L2_ASSOC; assoc++) अणु
			tag = cvmx_l2c_get_tag(assoc, index);

			अगर (tag.s.V && (tag.s.addr == tag_addr)) अणु
				cvmx_l2c_flush_line(assoc, index);
				वापस tag.s.L;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cvmx_l2c_unlock_mem_region(uपूर्णांक64_t start, uपूर्णांक64_t len)
अणु
	पूर्णांक num_unlocked = 0;
	/* Round start/end to cache line boundaries */
	len += start & CVMX_CACHE_LINE_MASK;
	start &= ~CVMX_CACHE_LINE_MASK;
	len = (len + CVMX_CACHE_LINE_MASK) & ~CVMX_CACHE_LINE_MASK;
	जबतक (len > 0) अणु
		num_unlocked += cvmx_l2c_unlock_line(start);
		start += CVMX_CACHE_LINE_SIZE;
		len -= CVMX_CACHE_LINE_SIZE;
	पूर्ण

	वापस num_unlocked;
पूर्ण

/*
 * Internal l2c tag types.  These are converted to a generic काष्ठाure
 * that can be used on all chips.
 */
जोड़ __cvmx_l2c_tag अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_l2c_tag_cn50xx अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved:40,
		__BITFIELD_FIELD(uपूर्णांक64_t V:1,		/* Line valid */
		__BITFIELD_FIELD(uपूर्णांक64_t D:1,		/* Line dirty */
		__BITFIELD_FIELD(uपूर्णांक64_t L:1,		/* Line locked */
		__BITFIELD_FIELD(uपूर्णांक64_t U:1,		/* Use, LRU eviction */
		__BITFIELD_FIELD(uपूर्णांक64_t addr:20,	/* Phys addr (33..14) */
		;))))))
	पूर्ण cn50xx;
	काष्ठा cvmx_l2c_tag_cn30xx अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved:41,
		__BITFIELD_FIELD(uपूर्णांक64_t V:1,		/* Line valid */
		__BITFIELD_FIELD(uपूर्णांक64_t D:1,		/* Line dirty */
		__BITFIELD_FIELD(uपूर्णांक64_t L:1,		/* Line locked */
		__BITFIELD_FIELD(uपूर्णांक64_t U:1,		/* Use, LRU eviction */
		__BITFIELD_FIELD(uपूर्णांक64_t addr:19,	/* Phys addr (33..15) */
		;))))))
	पूर्ण cn30xx;
	काष्ठा cvmx_l2c_tag_cn31xx अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved:42,
		__BITFIELD_FIELD(uपूर्णांक64_t V:1,		/* Line valid */
		__BITFIELD_FIELD(uपूर्णांक64_t D:1,		/* Line dirty */
		__BITFIELD_FIELD(uपूर्णांक64_t L:1,		/* Line locked */
		__BITFIELD_FIELD(uपूर्णांक64_t U:1,		/* Use, LRU eviction */
		__BITFIELD_FIELD(uपूर्णांक64_t addr:18,	/* Phys addr (33..16) */
		;))))))
	पूर्ण cn31xx;
	काष्ठा cvmx_l2c_tag_cn38xx अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved:43,
		__BITFIELD_FIELD(uपूर्णांक64_t V:1,		/* Line valid */
		__BITFIELD_FIELD(uपूर्णांक64_t D:1,		/* Line dirty */
		__BITFIELD_FIELD(uपूर्णांक64_t L:1,		/* Line locked */
		__BITFIELD_FIELD(uपूर्णांक64_t U:1,		/* Use, LRU eviction */
		__BITFIELD_FIELD(uपूर्णांक64_t addr:17,	/* Phys addr (33..17) */
		;))))))
	पूर्ण cn38xx;
	काष्ठा cvmx_l2c_tag_cn58xx अणु
		__BITFIELD_FIELD(uपूर्णांक64_t reserved:44,
		__BITFIELD_FIELD(uपूर्णांक64_t V:1,		/* Line valid */
		__BITFIELD_FIELD(uपूर्णांक64_t D:1,		/* Line dirty */
		__BITFIELD_FIELD(uपूर्णांक64_t L:1,		/* Line locked */
		__BITFIELD_FIELD(uपूर्णांक64_t U:1,		/* Use, LRU eviction */
		__BITFIELD_FIELD(uपूर्णांक64_t addr:16,	/* Phys addr (33..18) */
		;))))))
	पूर्ण cn58xx;
	काष्ठा cvmx_l2c_tag_cn58xx cn56xx;	/* 2048 sets */
	काष्ठा cvmx_l2c_tag_cn31xx cn52xx;	/* 512 sets */
पूर्ण;


/**
 * @INTERNAL
 * Function to पढ़ो a L2C tag.  This code make the current core
 * the 'debug core' क्रम the L2.  This code must only be executed by
 * 1 core at a समय.
 *
 * @assoc:  Association (way) of the tag to dump
 * @index:  Index of the cacheline
 *
 * Returns The Octeon model specअगरic tag काष्ठाure.  This is
 *	   translated by a wrapper function to a generic क्रमm that is
 *	   easier क्रम applications to use.
 */
अटल जोड़ __cvmx_l2c_tag __पढ़ो_l2_tag(uपूर्णांक64_t assoc, uपूर्णांक64_t index)
अणु

	uपूर्णांक64_t debug_tag_addr = CVMX_ADD_SEG(CVMX_MIPS_SPACE_XKPHYS, (index << 7) + 96);
	uपूर्णांक64_t core = cvmx_get_core_num();
	जोड़ __cvmx_l2c_tag tag_val;
	uपूर्णांक64_t dbg_addr = CVMX_L2C_DBG;
	अचिन्हित दीर्घ flags;
	जोड़ cvmx_l2c_dbg debug_val;

	debug_val.u64 = 0;
	/*
	 * For low core count parts, the core number is always small
	 * enough to stay in the correct field and not set any
	 * reserved bits.
	 */
	debug_val.s.ppnum = core;
	debug_val.s.l2t = 1;
	debug_val.s.set = assoc;

	local_irq_save(flags);
	/*
	 * Make sure core is quiet (no prefetches, etc.) beक्रमe
	 * entering debug mode.
	 */
	CVMX_SYNC;
	/* Flush L1 to make sure debug load misses L1 */
	CVMX_DCACHE_INVALIDATE;

	/*
	 * The following must be करोne in assembly as when in debug
	 * mode all data loads from L2 वापस special debug data, not
	 * normal memory contents.  Also, पूर्णांकerrupts must be disabled,
	 * since अगर an पूर्णांकerrupt occurs जबतक in debug mode the ISR
	 * will get debug data from all its memory * पढ़ोs instead of
	 * the contents of memory.
	 */

	यंत्र अस्थिर (
		".set push\n\t"
		".set mips64\n\t"
		".set noreorder\n\t"
		"sd    %[dbg_val], 0(%[dbg_addr])\n\t"	 /* Enter debug mode, रुको क्रम store */
		"ld    $0, 0(%[dbg_addr])\n\t"
		"ld    %[tag_val], 0(%[tag_addr])\n\t"	 /* Read L2C tag data */
		"sd    $0, 0(%[dbg_addr])\n\t"		/* Exit debug mode, रुको क्रम store */
		"ld    $0, 0(%[dbg_addr])\n\t"
		"cache 9, 0($0)\n\t"		 /* Invalidate dcache to discard debug data */
		".set pop"
		: [tag_val] "=r" (tag_val)
		: [dbg_addr] "r" (dbg_addr), [dbg_val] "r" (debug_val), [tag_addr] "r" (debug_tag_addr)
		: "memory");

	local_irq_restore(flags);

	वापस tag_val;
पूर्ण


जोड़ cvmx_l2c_tag cvmx_l2c_get_tag(uपूर्णांक32_t association, uपूर्णांक32_t index)
अणु
	जोड़ cvmx_l2c_tag tag;

	tag.u64 = 0;
	अगर ((पूर्णांक)association >= cvmx_l2c_get_num_assoc()) अणु
		cvmx_dम_लिखो("ERROR: cvmx_l2c_get_tag association out of range\n");
		वापस tag;
	पूर्ण
	अगर ((पूर्णांक)index >= cvmx_l2c_get_num_sets()) अणु
		cvmx_dम_लिखो("ERROR: cvmx_l2c_get_tag index out of range (arg: %d, max: %d)\n",
			     (पूर्णांक)index, cvmx_l2c_get_num_sets());
		वापस tag;
	पूर्ण
	अगर (OCTEON_IS_MODEL(OCTEON_CN63XX)) अणु
		जोड़ cvmx_l2c_tadx_tag l2c_tadx_tag;
		uपूर्णांक64_t address = CVMX_ADD_SEG(CVMX_MIPS_SPACE_XKPHYS,
						(association << CVMX_L2C_TAG_ADDR_ALIAS_SHIFT) |
						(index << CVMX_L2C_IDX_ADDR_SHIFT));
		/*
		 * Use L2 cache Index load tag cache inकाष्ठाion, as
		 * hardware loads the भव tag क्रम the L2 cache
		 * block with the contents of L2C_TAD0_TAG
		 * रेजिस्टर.
		 */
		CVMX_CACHE_LTGL2I(address, 0);
		CVMX_SYNC;   /* make sure CVMX_L2C_TADX_TAG is updated */
		l2c_tadx_tag.u64 = cvmx_पढ़ो_csr(CVMX_L2C_TADX_TAG(0));

		tag.s.V	    = l2c_tadx_tag.s.valid;
		tag.s.D	    = l2c_tadx_tag.s.dirty;
		tag.s.L	    = l2c_tadx_tag.s.lock;
		tag.s.U	    = l2c_tadx_tag.s.use;
		tag.s.addr  = l2c_tadx_tag.s.tag;
	पूर्ण अन्यथा अणु
		जोड़ __cvmx_l2c_tag पंचांगp_tag;
		/* __पढ़ो_l2_tag is पूर्णांकended क्रम पूर्णांकernal use only */
		पंचांगp_tag = __पढ़ो_l2_tag(association, index);

		/*
		 * Convert all tag काष्ठाure types to generic version,
		 * as it can represent all models.
		 */
		अगर (OCTEON_IS_MODEL(OCTEON_CN58XX) || OCTEON_IS_MODEL(OCTEON_CN56XX)) अणु
			tag.s.V	   = पंचांगp_tag.cn58xx.V;
			tag.s.D	   = पंचांगp_tag.cn58xx.D;
			tag.s.L	   = पंचांगp_tag.cn58xx.L;
			tag.s.U	   = पंचांगp_tag.cn58xx.U;
			tag.s.addr = पंचांगp_tag.cn58xx.addr;
		पूर्ण अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN38XX)) अणु
			tag.s.V	   = पंचांगp_tag.cn38xx.V;
			tag.s.D	   = पंचांगp_tag.cn38xx.D;
			tag.s.L	   = पंचांगp_tag.cn38xx.L;
			tag.s.U	   = पंचांगp_tag.cn38xx.U;
			tag.s.addr = पंचांगp_tag.cn38xx.addr;
		पूर्ण अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN31XX) || OCTEON_IS_MODEL(OCTEON_CN52XX)) अणु
			tag.s.V	   = पंचांगp_tag.cn31xx.V;
			tag.s.D	   = पंचांगp_tag.cn31xx.D;
			tag.s.L	   = पंचांगp_tag.cn31xx.L;
			tag.s.U	   = पंचांगp_tag.cn31xx.U;
			tag.s.addr = पंचांगp_tag.cn31xx.addr;
		पूर्ण अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN30XX)) अणु
			tag.s.V	   = पंचांगp_tag.cn30xx.V;
			tag.s.D	   = पंचांगp_tag.cn30xx.D;
			tag.s.L	   = पंचांगp_tag.cn30xx.L;
			tag.s.U	   = पंचांगp_tag.cn30xx.U;
			tag.s.addr = पंचांगp_tag.cn30xx.addr;
		पूर्ण अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN50XX)) अणु
			tag.s.V	   = पंचांगp_tag.cn50xx.V;
			tag.s.D	   = पंचांगp_tag.cn50xx.D;
			tag.s.L	   = पंचांगp_tag.cn50xx.L;
			tag.s.U	   = पंचांगp_tag.cn50xx.U;
			tag.s.addr = पंचांगp_tag.cn50xx.addr;
		पूर्ण अन्यथा अणु
			cvmx_dम_लिखो("Unsupported OCTEON Model in %s\n", __func__);
		पूर्ण
	पूर्ण
	वापस tag;
पूर्ण

uपूर्णांक32_t cvmx_l2c_address_to_index(uपूर्णांक64_t addr)
अणु
	uपूर्णांक64_t idx = addr >> CVMX_L2C_IDX_ADDR_SHIFT;
	पूर्णांक indxalias = 0;

	अगर (OCTEON_IS_MODEL(OCTEON_CN6XXX)) अणु
		जोड़ cvmx_l2c_ctl l2c_ctl;

		l2c_ctl.u64 = cvmx_पढ़ो_csr(CVMX_L2C_CTL);
		indxalias = !l2c_ctl.s.disidxalias;
	पूर्ण अन्यथा अणु
		जोड़ cvmx_l2c_cfg l2c_cfg;

		l2c_cfg.u64 = cvmx_पढ़ो_csr(CVMX_L2C_CFG);
		indxalias = l2c_cfg.s.idxalias;
	पूर्ण

	अगर (indxalias) अणु
		अगर (OCTEON_IS_MODEL(OCTEON_CN63XX)) अणु
			uपूर्णांक32_t a_14_12 = (idx / (CVMX_L2C_MEMBANK_SELECT_SIZE/(1<<CVMX_L2C_IDX_ADDR_SHIFT))) & 0x7;

			idx ^= idx / cvmx_l2c_get_num_sets();
			idx ^= a_14_12;
		पूर्ण अन्यथा अणु
			idx ^= ((addr & CVMX_L2C_ALIAS_MASK) >> CVMX_L2C_TAG_ADDR_ALIAS_SHIFT);
		पूर्ण
	पूर्ण
	idx &= CVMX_L2C_IDX_MASK;
	वापस idx;
पूर्ण

पूर्णांक cvmx_l2c_get_cache_size_bytes(व्योम)
अणु
	वापस cvmx_l2c_get_num_sets() * cvmx_l2c_get_num_assoc() *
		CVMX_CACHE_LINE_SIZE;
पूर्ण

/**
 * Return log base 2 of the number of sets in the L2 cache
 * Returns
 */
पूर्णांक cvmx_l2c_get_set_bits(व्योम)
अणु
	पूर्णांक l2_set_bits;

	अगर (OCTEON_IS_MODEL(OCTEON_CN56XX) || OCTEON_IS_MODEL(OCTEON_CN58XX))
		l2_set_bits = 11;	/* 2048 sets */
	अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN38XX) || OCTEON_IS_MODEL(OCTEON_CN63XX))
		l2_set_bits = 10;	/* 1024 sets */
	अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN31XX) || OCTEON_IS_MODEL(OCTEON_CN52XX))
		l2_set_bits = 9;	/* 512 sets */
	अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN30XX))
		l2_set_bits = 8;	/* 256 sets */
	अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN50XX))
		l2_set_bits = 7;	/* 128 sets */
	अन्यथा अणु
		cvmx_dम_लिखो("Unsupported OCTEON Model in %s\n", __func__);
		l2_set_bits = 11;	/* 2048 sets */
	पूर्ण
	वापस l2_set_bits;
पूर्ण

/* Return the number of sets in the L2 Cache */
पूर्णांक cvmx_l2c_get_num_sets(व्योम)
अणु
	वापस 1 << cvmx_l2c_get_set_bits();
पूर्ण

/* Return the number of associations in the L2 Cache */
पूर्णांक cvmx_l2c_get_num_assoc(व्योम)
अणु
	पूर्णांक l2_assoc;

	अगर (OCTEON_IS_MODEL(OCTEON_CN56XX) ||
	    OCTEON_IS_MODEL(OCTEON_CN52XX) ||
	    OCTEON_IS_MODEL(OCTEON_CN58XX) ||
	    OCTEON_IS_MODEL(OCTEON_CN50XX) ||
	    OCTEON_IS_MODEL(OCTEON_CN38XX))
		l2_assoc = 8;
	अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN63XX))
		l2_assoc = 16;
	अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN31XX) ||
		 OCTEON_IS_MODEL(OCTEON_CN30XX))
		l2_assoc = 4;
	अन्यथा अणु
		cvmx_dम_लिखो("Unsupported OCTEON Model in %s\n", __func__);
		l2_assoc = 8;
	पूर्ण

	/* Check to see अगर part of the cache is disabled */
	अगर (OCTEON_IS_MODEL(OCTEON_CN63XX)) अणु
		जोड़ cvmx_mio_fus_dat3 mio_fus_dat3;

		mio_fus_dat3.u64 = cvmx_पढ़ो_csr(CVMX_MIO_FUS_DAT3);
		/*
		 * cvmx_mio_fus_dat3.s.l2c_crip fuses map as follows
		 * <2> will be not used क्रम 63xx
		 * <1> disables 1/2 ways
		 * <0> disables 1/4 ways
		 * They are cumulative, so क्रम 63xx:
		 * <1> <0>
		 * 0 0 16-way 2MB cache
		 * 0 1 12-way 1.5MB cache
		 * 1 0 8-way 1MB cache
		 * 1 1 4-way 512KB cache
		 */

		अगर (mio_fus_dat3.s.l2c_crip == 3)
			l2_assoc = 4;
		अन्यथा अगर (mio_fus_dat3.s.l2c_crip == 2)
			l2_assoc = 8;
		अन्यथा अगर (mio_fus_dat3.s.l2c_crip == 1)
			l2_assoc = 12;
	पूर्ण अन्यथा अणु
		uपूर्णांक64_t l2d_fus3;

		l2d_fus3 = cvmx_पढ़ो_csr(CVMX_L2D_FUS3);
		/*
		 * Using shअगरts here, as bit position names are
		 * dअगरferent क्रम each model but they all mean the
		 * same.
		 */
		अगर ((l2d_fus3 >> 35) & 0x1)
			l2_assoc = l2_assoc >> 2;
		अन्यथा अगर ((l2d_fus3 >> 34) & 0x1)
			l2_assoc = l2_assoc >> 1;
	पूर्ण
	वापस l2_assoc;
पूर्ण

/**
 * Flush a line from the L2 cache
 * This should only be called from one core at a समय, as this routine
 * sets the core to the 'debug' core in order to flush the line.
 *
 * @assoc:  Association (or way) to flush
 * @index:  Index to flush
 */
व्योम cvmx_l2c_flush_line(uपूर्णांक32_t assoc, uपूर्णांक32_t index)
अणु
	/* Check the range of the index. */
	अगर (index > (uपूर्णांक32_t)cvmx_l2c_get_num_sets()) अणु
		cvmx_dम_लिखो("ERROR: cvmx_l2c_flush_line index out of range.\n");
		वापस;
	पूर्ण

	/* Check the range of association. */
	अगर (assoc > (uपूर्णांक32_t)cvmx_l2c_get_num_assoc()) अणु
		cvmx_dम_लिखो("ERROR: cvmx_l2c_flush_line association out of range.\n");
		वापस;
	पूर्ण

	अगर (OCTEON_IS_MODEL(OCTEON_CN63XX)) अणु
		uपूर्णांक64_t address;
		/* Create the address based on index and association.
		 * Bits<20:17> select the way of the cache block involved in
		 *	       the operation
		 * Bits<16:7> of the effect address select the index
		 */
		address = CVMX_ADD_SEG(CVMX_MIPS_SPACE_XKPHYS,
				(assoc << CVMX_L2C_TAG_ADDR_ALIAS_SHIFT) |
				(index << CVMX_L2C_IDX_ADDR_SHIFT));
		CVMX_CACHE_WBIL2I(address, 0);
	पूर्ण अन्यथा अणु
		जोड़ cvmx_l2c_dbg l2cdbg;

		l2cdbg.u64 = 0;
		अगर (!OCTEON_IS_MODEL(OCTEON_CN30XX))
			l2cdbg.s.ppnum = cvmx_get_core_num();
		l2cdbg.s.finv = 1;

		l2cdbg.s.set = assoc;
		cvmx_spinlock_lock(&cvmx_l2c_spinlock);
		/*
		 * Enter debug mode, and make sure all other ग_लिखोs
		 * complete beक्रमe we enter debug mode
		 */
		CVMX_SYNC;
		cvmx_ग_लिखो_csr(CVMX_L2C_DBG, l2cdbg.u64);
		cvmx_पढ़ो_csr(CVMX_L2C_DBG);

		CVMX_PREPARE_FOR_STORE(CVMX_ADD_SEG(CVMX_MIPS_SPACE_XKPHYS,
						    index * CVMX_CACHE_LINE_SIZE),
				       0);
		/* Exit debug mode */
		CVMX_SYNC;
		cvmx_ग_लिखो_csr(CVMX_L2C_DBG, 0);
		cvmx_पढ़ो_csr(CVMX_L2C_DBG);
		cvmx_spinlock_unlock(&cvmx_l2c_spinlock);
	पूर्ण
पूर्ण
