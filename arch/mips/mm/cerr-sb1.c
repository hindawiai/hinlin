<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2001,2002,2003 Broadcom Corporation
 */
#समावेश <linux/sched.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/sibyte/sb1250.h>
#समावेश <यंत्र/sibyte/sb1250_regs.h>

#अगर !defined(CONFIG_SIBYTE_BUS_WATCHER) || defined(CONFIG_SIBYTE_BW_TRACE)
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sibyte/sb1250_scd.h>
#पूर्ण_अगर

/*
 * We'd like to dump the L2_ECC_TAG रेजिस्टर on errors, but errata make
 * that unsafe... So क्रम now we करोn't.	(BCM1250/BCM112x erratum SOC-48.)
 */
#अघोषित DUMP_L2_ECC_TAG_ON_ERROR

/* SB1 definitions */

/* XXX should come from config1 XXX */
#घोषणा SB1_CACHE_INDEX_MASK   0x1fe0

#घोषणा CP0_ERRCTL_RECOVERABLE (1 << 31)
#घोषणा CP0_ERRCTL_DCACHE      (1 << 30)
#घोषणा CP0_ERRCTL_ICACHE      (1 << 29)
#घोषणा CP0_ERRCTL_MULTIBUS    (1 << 23)
#घोषणा CP0_ERRCTL_MC_TLB      (1 << 15)
#घोषणा CP0_ERRCTL_MC_TIMEOUT  (1 << 14)

#घोषणा CP0_CERRI_TAG_PARITY   (1 << 29)
#घोषणा CP0_CERRI_DATA_PARITY  (1 << 28)
#घोषणा CP0_CERRI_EXTERNAL     (1 << 26)

#घोषणा CP0_CERRI_IDX_VALID(c) (!((c) & CP0_CERRI_EXTERNAL))
#घोषणा CP0_CERRI_DATA	       (CP0_CERRI_DATA_PARITY)

#घोषणा CP0_CERRD_MULTIPLE     (1 << 31)
#घोषणा CP0_CERRD_TAG_STATE    (1 << 30)
#घोषणा CP0_CERRD_TAG_ADDRESS  (1 << 29)
#घोषणा CP0_CERRD_DATA_SBE     (1 << 28)
#घोषणा CP0_CERRD_DATA_DBE     (1 << 27)
#घोषणा CP0_CERRD_EXTERNAL     (1 << 26)
#घोषणा CP0_CERRD_LOAD	       (1 << 25)
#घोषणा CP0_CERRD_STORE	       (1 << 24)
#घोषणा CP0_CERRD_FILLWB       (1 << 23)
#घोषणा CP0_CERRD_COHERENCY    (1 << 22)
#घोषणा CP0_CERRD_DUPTAG       (1 << 21)

#घोषणा CP0_CERRD_DPA_VALID(c) (!((c) & CP0_CERRD_EXTERNAL))
#घोषणा CP0_CERRD_IDX_VALID(c) \
   (((c) & (CP0_CERRD_LOAD | CP0_CERRD_STORE)) ? (!((c) & CP0_CERRD_EXTERNAL)) : 0)
#घोषणा CP0_CERRD_CAUSES \
   (CP0_CERRD_LOAD | CP0_CERRD_STORE | CP0_CERRD_FILLWB | CP0_CERRD_COHERENCY | CP0_CERRD_DUPTAG)
#घोषणा CP0_CERRD_TYPES \
   (CP0_CERRD_TAG_STATE | CP0_CERRD_TAG_ADDRESS | CP0_CERRD_DATA_SBE | CP0_CERRD_DATA_DBE | CP0_CERRD_EXTERNAL)
#घोषणा CP0_CERRD_DATA	       (CP0_CERRD_DATA_SBE | CP0_CERRD_DATA_DBE)

अटल uपूर्णांक32_t extract_ic(अचिन्हित लघु addr, पूर्णांक data);
अटल uपूर्णांक32_t extract_dc(अचिन्हित लघु addr, पूर्णांक data);

अटल अंतरभूत व्योम अवरोधout_errctl(अचिन्हित पूर्णांक val)
अणु
	अगर (val & CP0_ERRCTL_RECOVERABLE)
		prपूर्णांकk(" recoverable");
	अगर (val & CP0_ERRCTL_DCACHE)
		prपूर्णांकk(" dcache");
	अगर (val & CP0_ERRCTL_ICACHE)
		prपूर्णांकk(" icache");
	अगर (val & CP0_ERRCTL_MULTIBUS)
		prपूर्णांकk(" multiple-buserr");
	prपूर्णांकk("\n");
पूर्ण

अटल अंतरभूत व्योम अवरोधout_cerri(अचिन्हित पूर्णांक val)
अणु
	अगर (val & CP0_CERRI_TAG_PARITY)
		prपूर्णांकk(" tag-parity");
	अगर (val & CP0_CERRI_DATA_PARITY)
		prपूर्णांकk(" data-parity");
	अगर (val & CP0_CERRI_EXTERNAL)
		prपूर्णांकk(" external");
	prपूर्णांकk("\n");
पूर्ण

अटल अंतरभूत व्योम अवरोधout_cerrd(अचिन्हित पूर्णांक val)
अणु
	चयन (val & CP0_CERRD_CAUSES) अणु
	हाल CP0_CERRD_LOAD:
		prपूर्णांकk(" load,");
		अवरोध;
	हाल CP0_CERRD_STORE:
		prपूर्णांकk(" store,");
		अवरोध;
	हाल CP0_CERRD_FILLWB:
		prपूर्णांकk(" fill/wb,");
		अवरोध;
	हाल CP0_CERRD_COHERENCY:
		prपूर्णांकk(" coherency,");
		अवरोध;
	हाल CP0_CERRD_DUPTAG:
		prपूर्णांकk(" duptags,");
		अवरोध;
	शेष:
		prपूर्णांकk(" NO CAUSE,");
		अवरोध;
	पूर्ण
	अगर (!(val & CP0_CERRD_TYPES))
		prपूर्णांकk(" NO TYPE");
	अन्यथा अणु
		अगर (val & CP0_CERRD_MULTIPLE)
			prपूर्णांकk(" multi-err");
		अगर (val & CP0_CERRD_TAG_STATE)
			prपूर्णांकk(" tag-state");
		अगर (val & CP0_CERRD_TAG_ADDRESS)
			prपूर्णांकk(" tag-address");
		अगर (val & CP0_CERRD_DATA_SBE)
			prपूर्णांकk(" data-SBE");
		अगर (val & CP0_CERRD_DATA_DBE)
			prपूर्णांकk(" data-DBE");
		अगर (val & CP0_CERRD_EXTERNAL)
			prपूर्णांकk(" external");
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण

#अगर_अघोषित CONFIG_SIBYTE_BUS_WATCHER

अटल व्योम check_bus_watcher(व्योम)
अणु
	uपूर्णांक32_t status, l2_err, memio_err;
#अगर_घोषित DUMP_L2_ECC_TAG_ON_ERROR
	uपूर्णांक64_t l2_tag;
#पूर्ण_अगर

	/* Deकाष्ठाive पढ़ो, clears रेजिस्टर and पूर्णांकerrupt */
	status = csr_in32(IOADDR(A_SCD_BUS_ERR_STATUS));
	/* Bit 31 is always on, but there's no #घोषणा क्रम that */
	अगर (status & ~(1UL << 31)) अणु
		l2_err = csr_in32(IOADDR(A_BUS_L2_ERRORS));
#अगर_घोषित DUMP_L2_ECC_TAG_ON_ERROR
		l2_tag = in64(IOADDR(A_L2_ECC_TAG));
#पूर्ण_अगर
		memio_err = csr_in32(IOADDR(A_BUS_MEM_IO_ERRORS));
		prपूर्णांकk("Bus watcher error counters: %08x %08x\n", l2_err, memio_err);
		prपूर्णांकk("\nLast recorded signature:\n");
		prपूर्णांकk("Request %02x from %d, answered by %d with Dcode %d\n",
		       (अचिन्हित पूर्णांक)(G_SCD_BERR_TID(status) & 0x3f),
		       (पूर्णांक)(G_SCD_BERR_TID(status) >> 6),
		       (पूर्णांक)G_SCD_BERR_RID(status),
		       (पूर्णांक)G_SCD_BERR_DCODE(status));
#अगर_घोषित DUMP_L2_ECC_TAG_ON_ERROR
		prपूर्णांकk("Last L2 tag w/ bad ECC: %016llx\n", l2_tag);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		prपूर्णांकk("Bus watcher indicates no error\n");
	पूर्ण
पूर्ण
#अन्यथा
बाह्य व्योम check_bus_watcher(व्योम);
#पूर्ण_अगर

यंत्रlinkage व्योम sb1_cache_error(व्योम)
अणु
	uपूर्णांक32_t errctl, cerr_i, cerr_d, dpalo, dpahi, eepc, res;
	अचिन्हित दीर्घ दीर्घ cerr_dpa;

#अगर_घोषित CONFIG_SIBYTE_BW_TRACE
	/* Freeze the trace buffer now */
	csr_out32(M_SCD_TRACE_CFG_FREEZE, IOADDR(A_SCD_TRACE_CFG));
	prपूर्णांकk("Trace buffer frozen\n");
#पूर्ण_अगर

	prपूर्णांकk("Cache error exception on CPU %x:\n",
	       (पढ़ो_c0_prid() >> 25) & 0x7);

	__यंत्र__ __अस्थिर__ (
	"	.set	push\n\t"
	"	.set	mips64\n\t"
	"	.set	noat\n\t"
	"	mfc0	%0, $26\n\t"
	"	mfc0	%1, $27\n\t"
	"	mfc0	%2, $27, 1\n\t"
	"	dmfc0	$1, $27, 3\n\t"
	"	dsrl32	%3, $1, 0 \n\t"
	"	sll	%4, $1, 0 \n\t"
	"	mfc0	%5, $30\n\t"
	"	.set	pop"
	: "=r" (errctl), "=r" (cerr_i), "=r" (cerr_d),
	  "=r" (dpahi), "=r" (dpalo), "=r" (eepc));

	cerr_dpa = (((uपूर्णांक64_t)dpahi) << 32) | dpalo;
	prपूर्णांकk(" c0_errorepc ==	  %08x\n", eepc);
	prपूर्णांकk(" c0_errctl   ==	  %08x", errctl);
	अवरोधout_errctl(errctl);
	अगर (errctl & CP0_ERRCTL_ICACHE) अणु
		prपूर्णांकk(" c0_cerr_i   ==	  %08x", cerr_i);
		अवरोधout_cerri(cerr_i);
		अगर (CP0_CERRI_IDX_VALID(cerr_i)) अणु
			/* Check index of EPC, allowing क्रम delay slot */
			अगर (((eepc & SB1_CACHE_INDEX_MASK) != (cerr_i & SB1_CACHE_INDEX_MASK)) &&
			    ((eepc & SB1_CACHE_INDEX_MASK) != ((cerr_i & SB1_CACHE_INDEX_MASK) - 4)))
				prपूर्णांकk(" cerr_i idx doesn't match eepc\n");
			अन्यथा अणु
				res = extract_ic(cerr_i & SB1_CACHE_INDEX_MASK,
						 (cerr_i & CP0_CERRI_DATA) != 0);
				अगर (!(res & cerr_i))
					prपूर्णांकk("...didn't see indicated icache problem\n");
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (errctl & CP0_ERRCTL_DCACHE) अणु
		prपूर्णांकk(" c0_cerr_d   ==	  %08x", cerr_d);
		अवरोधout_cerrd(cerr_d);
		अगर (CP0_CERRD_DPA_VALID(cerr_d)) अणु
			prपूर्णांकk(" c0_cerr_dpa == %010llx\n", cerr_dpa);
			अगर (!CP0_CERRD_IDX_VALID(cerr_d)) अणु
				res = extract_dc(cerr_dpa & SB1_CACHE_INDEX_MASK,
						 (cerr_d & CP0_CERRD_DATA) != 0);
				अगर (!(res & cerr_d))
					prपूर्णांकk("...didn't see indicated dcache problem\n");
			पूर्ण अन्यथा अणु
				अगर ((cerr_dpa & SB1_CACHE_INDEX_MASK) != (cerr_d & SB1_CACHE_INDEX_MASK))
					prपूर्णांकk(" cerr_d idx doesn't match cerr_dpa\n");
				अन्यथा अणु
					res = extract_dc(cerr_d & SB1_CACHE_INDEX_MASK,
							 (cerr_d & CP0_CERRD_DATA) != 0);
					अगर (!(res & cerr_d))
						prपूर्णांकk("...didn't see indicated problem\n");
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	check_bus_watcher();

	/*
	 * Calling panic() when a fatal cache error occurs scrambles the
	 * state of the प्रणाली (and the cache), making it dअगरficult to
	 * investigate after the fact.	However, अगर you just stall the CPU,
	 * the other CPU may keep on running, which is typically very
	 * undesirable.
	 */
#अगर_घोषित CONFIG_SB1_CERR_STALL
	जबतक (1)
		;
#अन्यथा
	panic("unhandled cache error");
#पूर्ण_अगर
पूर्ण


/* Parity lookup table. */
अटल स्थिर uपूर्णांक8_t parity[256] = अणु
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0
पूर्ण;

/* Masks to select bits क्रम Hamming parity, mask_72_64[i] क्रम bit[i] */
अटल स्थिर uपूर्णांक64_t mask_72_64[8] = अणु
	0x0738C808099264FFULL,
	0x38C808099264FF07ULL,
	0xC808099264FF0738ULL,
	0x08099264FF0738C8ULL,
	0x099264FF0738C808ULL,
	0x9264FF0738C80809ULL,
	0x64FF0738C8080992ULL,
	0xFF0738C808099264ULL
पूर्ण;

/* Calculate the parity on a range of bits */
अटल अक्षर range_parity(uपूर्णांक64_t dword, पूर्णांक max, पूर्णांक min)
अणु
	अक्षर parity = 0;
	पूर्णांक i;
	dword >>= min;
	क्रम (i=max-min; i>=0; i--) अणु
		अगर (dword & 0x1)
			parity = !parity;
		dword >>= 1;
	पूर्ण
	वापस parity;
पूर्ण

/* Calculate the 4-bit even byte-parity क्रम an inकाष्ठाion */
अटल अचिन्हित अक्षर inst_parity(uपूर्णांक32_t word)
अणु
	पूर्णांक i, j;
	अक्षर parity = 0;
	क्रम (j=0; j<4; j++) अणु
		अक्षर byte_parity = 0;
		क्रम (i=0; i<8; i++) अणु
			अगर (word & 0x80000000)
				byte_parity = !byte_parity;
			word <<= 1;
		पूर्ण
		parity <<= 1;
		parity |= byte_parity;
	पूर्ण
	वापस parity;
पूर्ण

अटल uपूर्णांक32_t extract_ic(अचिन्हित लघु addr, पूर्णांक data)
अणु
	अचिन्हित लघु way;
	पूर्णांक valid;
	uपूर्णांक32_t taghi, taglolo, taglohi;
	अचिन्हित दीर्घ दीर्घ taglo, va;
	uपूर्णांक64_t tlo_पंचांगp;
	uपूर्णांक8_t lru;
	पूर्णांक res = 0;

	prपूर्णांकk("Icache index 0x%04x  ", addr);
	क्रम (way = 0; way < 4; way++) अणु
		/* Index-load-tag-I */
		__यंत्र__ __अस्थिर__ (
		"	.set	push		\n\t"
		"	.set	noreorder	\n\t"
		"	.set	mips64		\n\t"
		"	.set	noat		\n\t"
		"	cache	4, 0(%3)	\n\t"
		"	mfc0	%0, $29		\n\t"
		"	dmfc0	$1, $28		\n\t"
		"	dsrl32	%1, $1, 0	\n\t"
		"	sll	%2, $1, 0	\n\t"
		"	.set	pop"
		: "=r" (taghi), "=r" (taglohi), "=r" (taglolo)
		: "r" ((way << 13) | addr));

		taglo = ((अचिन्हित दीर्घ दीर्घ)taglohi << 32) | taglolo;
		अगर (way == 0) अणु
			lru = (taghi >> 14) & 0xff;
			prपूर्णांकk("[Bank %d Set 0x%02x]  LRU > %d %d %d %d > MRU\n",
				    ((addr >> 5) & 0x3), /* bank */
				    ((addr >> 7) & 0x3f), /* index */
				    (lru & 0x3),
				    ((lru >> 2) & 0x3),
				    ((lru >> 4) & 0x3),
				    ((lru >> 6) & 0x3));
		पूर्ण
		va = (taglo & 0xC0000FFFFFFFE000ULL) | addr;
		अगर ((taglo & (1 << 31)) && (((taglo >> 62) & 0x3) == 3))
			va |= 0x3FFFF00000000000ULL;
		valid = ((taghi >> 29) & 1);
		अगर (valid) अणु
			tlo_पंचांगp = taglo & 0xfff3ff;
			अगर (((taglo >> 10) & 1) ^ range_parity(tlo_पंचांगp, 23, 0)) अणु
				prपूर्णांकk("   ** bad parity in VTag0/G/ASID\n");
				res |= CP0_CERRI_TAG_PARITY;
			पूर्ण
			अगर (((taglo >> 11) & 1) ^ range_parity(taglo, 63, 24)) अणु
				prपूर्णांकk("   ** bad parity in R/VTag1\n");
				res |= CP0_CERRI_TAG_PARITY;
			पूर्ण
		पूर्ण
		अगर (valid ^ ((taghi >> 27) & 1)) अणु
			prपूर्णांकk("   ** bad parity for valid bit\n");
			res |= CP0_CERRI_TAG_PARITY;
		पूर्ण
		prपूर्णांकk(" %d  [VA %016llx]  [Vld? %d]  raw tags: %08X-%016llX\n",
			    way, va, valid, taghi, taglo);

		अगर (data) अणु
			uपूर्णांक32_t datahi, insta, instb;
			uपूर्णांक8_t predecode;
			पूर्णांक offset;

			/* (hit all banks and ways) */
			क्रम (offset = 0; offset < 4; offset++) अणु
				/* Index-load-data-I */
				__यंत्र__ __अस्थिर__ (
				"	.set	push\n\t"
				"	.set	noreorder\n\t"
				"	.set	mips64\n\t"
				"	.set	noat\n\t"
				"	cache	6, 0(%3)  \n\t"
				"	mfc0	%0, $29, 1\n\t"
				"	dmfc0  $1, $28, 1\n\t"
				"	dsrl32 %1, $1, 0 \n\t"
				"	sll    %2, $1, 0 \n\t"
				"	.set	pop	    \n"
				: "=r" (datahi), "=r" (insta), "=r" (instb)
				: "r" ((way << 13) | addr | (offset << 3)));
				predecode = (datahi >> 8) & 0xff;
				अगर (((datahi >> 16) & 1) != (uपूर्णांक32_t)range_parity(predecode, 7, 0)) अणु
					prपूर्णांकk("   ** bad parity in predecode\n");
					res |= CP0_CERRI_DATA_PARITY;
				पूर्ण
				/* XXXKW should/could check predecode bits themselves */
				अगर (((datahi >> 4) & 0xf) ^ inst_parity(insta)) अणु
					prपूर्णांकk("   ** bad parity in instruction a\n");
					res |= CP0_CERRI_DATA_PARITY;
				पूर्ण
				अगर ((datahi & 0xf) ^ inst_parity(instb)) अणु
					prपूर्णांकk("   ** bad parity in instruction b\n");
					res |= CP0_CERRI_DATA_PARITY;
				पूर्ण
				prपूर्णांकk("  %05X-%08X%08X", datahi, insta, instb);
			पूर्ण
			prपूर्णांकk("\n");
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

/* Compute the ECC क्रम a data द्विगुनword */
अटल uपूर्णांक8_t dc_ecc(uपूर्णांक64_t dword)
अणु
	uपूर्णांक64_t t;
	uपूर्णांक32_t w;
	uपूर्णांक8_t	 p;
	पूर्णांक	 i;

	p = 0;
	क्रम (i = 7; i >= 0; i--)
	अणु
		p <<= 1;
		t = dword & mask_72_64[i];
		w = (uपूर्णांक32_t)(t >> 32);
		p ^= (parity[w>>24] ^ parity[(w>>16) & 0xFF]
		      ^ parity[(w>>8) & 0xFF] ^ parity[w & 0xFF]);
		w = (uपूर्णांक32_t)(t & 0xFFFFFFFF);
		p ^= (parity[w>>24] ^ parity[(w>>16) & 0xFF]
		      ^ parity[(w>>8) & 0xFF] ^ parity[w & 0xFF]);
	पूर्ण
	वापस p;
पूर्ण

काष्ठा dc_state अणु
	अचिन्हित अक्षर val;
	अक्षर *name;
पूर्ण;

अटल काष्ठा dc_state dc_states[] = अणु
	अणु 0x00, "INVALID" पूर्ण,
	अणु 0x0f, "COH-SHD" पूर्ण,
	अणु 0x13, "NCO-E-C" पूर्ण,
	अणु 0x19, "NCO-E-D" पूर्ण,
	अणु 0x16, "COH-E-C" पूर्ण,
	अणु 0x1c, "COH-E-D" पूर्ण,
	अणु 0xff, "*ERROR*" पूर्ण
पूर्ण;

#घोषणा DC_TAG_VALID(state) \
    (((state) == 0x0) || ((state) == 0xf) || ((state) == 0x13) || \
     ((state) == 0x19) || ((state) == 0x16) || ((state) == 0x1c))

अटल अक्षर *dc_state_str(अचिन्हित अक्षर state)
अणु
	काष्ठा dc_state *dsc = dc_states;
	जबतक (dsc->val != 0xff) अणु
		अगर (dsc->val == state)
			अवरोध;
		dsc++;
	पूर्ण
	वापस dsc->name;
पूर्ण

अटल uपूर्णांक32_t extract_dc(अचिन्हित लघु addr, पूर्णांक data)
अणु
	पूर्णांक valid, way;
	अचिन्हित अक्षर state;
	uपूर्णांक32_t taghi, taglolo, taglohi;
	अचिन्हित दीर्घ दीर्घ taglo, pa;
	uपूर्णांक8_t ecc, lru;
	पूर्णांक res = 0;

	prपूर्णांकk("Dcache index 0x%04x  ", addr);
	क्रम (way = 0; way < 4; way++) अणु
		__यंत्र__ __अस्थिर__ (
		"	.set	push\n\t"
		"	.set	noreorder\n\t"
		"	.set	mips64\n\t"
		"	.set	noat\n\t"
		"	cache	5, 0(%3)\n\t"	/* Index-load-tag-D */
		"	mfc0	%0, $29, 2\n\t"
		"	dmfc0	$1, $28, 2\n\t"
		"	dsrl32	%1, $1, 0\n\t"
		"	sll	%2, $1, 0\n\t"
		"	.set	pop"
		: "=r" (taghi), "=r" (taglohi), "=r" (taglolo)
		: "r" ((way << 13) | addr));

		taglo = ((अचिन्हित दीर्घ दीर्घ)taglohi << 32) | taglolo;
		pa = (taglo & 0xFFFFFFE000ULL) | addr;
		अगर (way == 0) अणु
			lru = (taghi >> 14) & 0xff;
			prपूर्णांकk("[Bank %d Set 0x%02x]  LRU > %d %d %d %d > MRU\n",
				    ((addr >> 11) & 0x2) | ((addr >> 5) & 1), /* bank */
				    ((addr >> 6) & 0x3f), /* index */
				    (lru & 0x3),
				    ((lru >> 2) & 0x3),
				    ((lru >> 4) & 0x3),
				    ((lru >> 6) & 0x3));
		पूर्ण
		state = (taghi >> 25) & 0x1f;
		valid = DC_TAG_VALID(state);
		prपूर्णांकk(" %d  [PA %010llx]  [state %s (%02x)]  raw tags: %08X-%016llX\n",
			    way, pa, dc_state_str(state), state, taghi, taglo);
		अगर (valid) अणु
			अगर (((taglo >> 11) & 1) ^ range_parity(taglo, 39, 26)) अणु
				prपूर्णांकk("   ** bad parity in PTag1\n");
				res |= CP0_CERRD_TAG_ADDRESS;
			पूर्ण
			अगर (((taglo >> 10) & 1) ^ range_parity(taglo, 25, 13)) अणु
				prपूर्णांकk("   ** bad parity in PTag0\n");
				res |= CP0_CERRD_TAG_ADDRESS;
			पूर्ण
		पूर्ण अन्यथा अणु
			res |= CP0_CERRD_TAG_STATE;
		पूर्ण

		अगर (data) अणु
			uपूर्णांक32_t datalohi, datalolo, datahi;
			अचिन्हित दीर्घ दीर्घ datalo;
			पूर्णांक offset;
			अक्षर bad_ecc = 0;

			क्रम (offset = 0; offset < 4; offset++) अणु
				/* Index-load-data-D */
				__यंत्र__ __अस्थिर__ (
				"	.set	push\n\t"
				"	.set	noreorder\n\t"
				"	.set	mips64\n\t"
				"	.set	noat\n\t"
				"	cache	7, 0(%3)\n\t" /* Index-load-data-D */
				"	mfc0	%0, $29, 3\n\t"
				"	dmfc0	$1, $28, 3\n\t"
				"	dsrl32	%1, $1, 0 \n\t"
				"	sll	%2, $1, 0 \n\t"
				"	.set	pop"
				: "=r" (datahi), "=r" (datalohi), "=r" (datalolo)
				: "r" ((way << 13) | addr | (offset << 3)));
				datalo = ((अचिन्हित दीर्घ दीर्घ)datalohi << 32) | datalolo;
				ecc = dc_ecc(datalo);
				अगर (ecc != datahi) अणु
					पूर्णांक bits;
					bad_ecc |= 1 << (3-offset);
					ecc ^= datahi;
					bits = hweight8(ecc);
					res |= (bits == 1) ? CP0_CERRD_DATA_SBE : CP0_CERRD_DATA_DBE;
				पूर्ण
				prपूर्णांकk("  %02X-%016llX", datahi, datalo);
			पूर्ण
			prपूर्णांकk("\n");
			अगर (bad_ecc)
				prपूर्णांकk("  dwords w/ bad ECC: %d %d %d %d\n",
				       !!(bad_ecc & 8), !!(bad_ecc & 4),
				       !!(bad_ecc & 2), !!(bad_ecc & 1));
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण
