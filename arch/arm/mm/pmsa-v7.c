<शैली गुरु>
/*
 * Based on linux/arch/arm/mm/nommu.c
 *
 * ARM PMSAv7 supporting functions.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/memblock.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/mpu.h>
#समावेश <यंत्र/sections.h>

#समावेश "mm.h"

काष्ठा region अणु
	phys_addr_t base;
	phys_addr_t size;
	अचिन्हित दीर्घ subreg;
पूर्ण;

अटल काष्ठा region __initdata mem[MPU_MAX_REGIONS];
#अगर_घोषित CONFIG_XIP_KERNEL
अटल काष्ठा region __initdata xip[MPU_MAX_REGIONS];
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक __initdata mpu_min_region_order;
अटल अचिन्हित पूर्णांक __initdata mpu_max_regions;

अटल पूर्णांक __init __mpu_min_region_order(व्योम);
अटल पूर्णांक __init __mpu_max_regions(व्योम);

#अगर_अघोषित CONFIG_CPU_V7M

#घोषणा DRBAR	__ACCESS_CP15(c6, 0, c1, 0)
#घोषणा IRBAR	__ACCESS_CP15(c6, 0, c1, 1)
#घोषणा DRSR	__ACCESS_CP15(c6, 0, c1, 2)
#घोषणा IRSR	__ACCESS_CP15(c6, 0, c1, 3)
#घोषणा DRACR	__ACCESS_CP15(c6, 0, c1, 4)
#घोषणा IRACR	__ACCESS_CP15(c6, 0, c1, 5)
#घोषणा RNGNR	__ACCESS_CP15(c6, 0, c2, 0)

/* Region number */
अटल अंतरभूत व्योम rgnr_ग_लिखो(u32 v)
अणु
	ग_लिखो_sysreg(v, RNGNR);
पूर्ण

/* Data-side / unअगरied region attributes */

/* Region access control रेजिस्टर */
अटल अंतरभूत व्योम dracr_ग_लिखो(u32 v)
अणु
	ग_लिखो_sysreg(v, DRACR);
पूर्ण

/* Region size रेजिस्टर */
अटल अंतरभूत व्योम drsr_ग_लिखो(u32 v)
अणु
	ग_लिखो_sysreg(v, DRSR);
पूर्ण

/* Region base address रेजिस्टर */
अटल अंतरभूत व्योम drbar_ग_लिखो(u32 v)
अणु
	ग_लिखो_sysreg(v, DRBAR);
पूर्ण

अटल अंतरभूत u32 drbar_पढ़ो(व्योम)
अणु
	वापस पढ़ो_sysreg(DRBAR);
पूर्ण
/* Optional inकाष्ठाion-side region attributes */

/* I-side Region access control रेजिस्टर */
अटल अंतरभूत व्योम iracr_ग_लिखो(u32 v)
अणु
	ग_लिखो_sysreg(v, IRACR);
पूर्ण

/* I-side Region size रेजिस्टर */
अटल अंतरभूत व्योम irsr_ग_लिखो(u32 v)
अणु
	ग_लिखो_sysreg(v, IRSR);
पूर्ण

/* I-side Region base address रेजिस्टर */
अटल अंतरभूत व्योम irbar_ग_लिखो(u32 v)
अणु
	ग_लिखो_sysreg(v, IRBAR);
पूर्ण

अटल अंतरभूत u32 irbar_पढ़ो(व्योम)
अणु
	वापस पढ़ो_sysreg(IRBAR);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम rgnr_ग_लिखो(u32 v)
अणु
	ग_लिखोl_relaxed(v, BASEADDR_V7M_SCB + PMSAv7_RNR);
पूर्ण

/* Data-side / unअगरied region attributes */

/* Region access control रेजिस्टर */
अटल अंतरभूत व्योम dracr_ग_लिखो(u32 v)
अणु
	u32 rsr = पढ़ोl_relaxed(BASEADDR_V7M_SCB + PMSAv7_RASR) & GENMASK(15, 0);

	ग_लिखोl_relaxed((v << 16) | rsr, BASEADDR_V7M_SCB + PMSAv7_RASR);
पूर्ण

/* Region size रेजिस्टर */
अटल अंतरभूत व्योम drsr_ग_लिखो(u32 v)
अणु
	u32 racr = पढ़ोl_relaxed(BASEADDR_V7M_SCB + PMSAv7_RASR) & GENMASK(31, 16);

	ग_लिखोl_relaxed(v | racr, BASEADDR_V7M_SCB + PMSAv7_RASR);
पूर्ण

/* Region base address रेजिस्टर */
अटल अंतरभूत व्योम drbar_ग_लिखो(u32 v)
अणु
	ग_लिखोl_relaxed(v, BASEADDR_V7M_SCB + PMSAv7_RBAR);
पूर्ण

अटल अंतरभूत u32 drbar_पढ़ो(व्योम)
अणु
	वापस पढ़ोl_relaxed(BASEADDR_V7M_SCB + PMSAv7_RBAR);
पूर्ण

/* ARMv7-M only supports a unअगरied MPU, so I-side operations are nop */

अटल अंतरभूत व्योम iracr_ग_लिखो(u32 v) अणुपूर्ण
अटल अंतरभूत व्योम irsr_ग_लिखो(u32 v) अणुपूर्ण
अटल अंतरभूत व्योम irbar_ग_लिखो(u32 v) अणुपूर्ण
अटल अंतरभूत अचिन्हित दीर्घ irbar_पढ़ो(व्योम) अणुवापस 0;पूर्ण

#पूर्ण_अगर

अटल bool __init try_split_region(phys_addr_t base, phys_addr_t size, काष्ठा region *region)
अणु
	अचिन्हित दीर्घ  subreg, bslots, sslots;
	phys_addr_t abase = base & ~(size - 1);
	phys_addr_t asize = base + size - abase;
	phys_addr_t p2size = 1 << __fls(asize);
	phys_addr_t bdअगरf, sdअगरf;

	अगर (p2size != asize)
		p2size *= 2;

	bdअगरf = base - abase;
	sdअगरf = p2size - asize;
	subreg = p2size / PMSAv7_NR_SUBREGS;

	अगर ((bdअगरf % subreg) || (sdअगरf % subreg))
		वापस false;

	bslots = bdअगरf / subreg;
	sslots = sdअगरf / subreg;

	अगर (bslots || sslots) अणु
		पूर्णांक i;

		अगर (subreg < PMSAv7_MIN_SUBREG_SIZE)
			वापस false;

		अगर (bslots + sslots > PMSAv7_NR_SUBREGS)
			वापस false;

		क्रम (i = 0; i < bslots; i++)
			_set_bit(i, &region->subreg);

		क्रम (i = 1; i <= sslots; i++)
			_set_bit(PMSAv7_NR_SUBREGS - i, &region->subreg);
	पूर्ण

	region->base = abase;
	region->size = p2size;

	वापस true;
पूर्ण

अटल पूर्णांक __init allocate_region(phys_addr_t base, phys_addr_t size,
				  अचिन्हित पूर्णांक limit, काष्ठा region *regions)
अणु
	पूर्णांक count = 0;
	phys_addr_t dअगरf = size;
	पूर्णांक attempts = MPU_MAX_REGIONS;

	जबतक (dअगरf) अणु
		/* Try cover region as is (maybe with help of subregions) */
		अगर (try_split_region(base, size, &regions[count])) अणु
			count++;
			base += size;
			dअगरf -= size;
			size = dअगरf;
		पूर्ण अन्यथा अणु
			/*
			 * Maximum aligned region might overflow phys_addr_t
			 * अगर "base" is 0. Hence we keep everything below 4G
			 * until we take the smaller of the aligned region
			 * size ("asize") and rounded region size ("p2size"),
			 * one of which is guaranteed to be smaller than the
			 * maximum physical address.
			 */
			phys_addr_t asize = (base - 1) ^ base;
			phys_addr_t p2size = (1 <<  __fls(dअगरf)) - 1;

			size = asize < p2size ? asize + 1 : p2size + 1;
		पूर्ण

		अगर (count > limit)
			अवरोध;

		अगर (!attempts)
			अवरोध;

		attempts--;
	पूर्ण

	वापस count;
पूर्ण

/* MPU initialisation functions */
व्योम __init pmsav7_adjust_lowmem_bounds(व्योम)
अणु
	phys_addr_t  specअगरied_mem_size = 0, total_mem_size = 0;
	phys_addr_t mem_start;
	phys_addr_t mem_end;
	phys_addr_t reg_start, reg_end;
	अचिन्हित पूर्णांक mem_max_regions;
	bool first = true;
	पूर्णांक num;
	u64 i;

	/* Free-up PMSAv7_PROBE_REGION */
	mpu_min_region_order = __mpu_min_region_order();

	/* How many regions are supported */
	mpu_max_regions = __mpu_max_regions();

	mem_max_regions = min((अचिन्हित पूर्णांक)MPU_MAX_REGIONS, mpu_max_regions);

	/* We need to keep one slot क्रम background region */
	mem_max_regions--;

#अगर_अघोषित CONFIG_CPU_V7M
	/* ... and one क्रम vectors */
	mem_max_regions--;
#पूर्ण_अगर

#अगर_घोषित CONFIG_XIP_KERNEL
	/* plus some regions to cover XIP ROM */
	num = allocate_region(CONFIG_XIP_PHYS_ADDR, __pa(_exiprom) - CONFIG_XIP_PHYS_ADDR,
			      mem_max_regions, xip);

	mem_max_regions -= num;
#पूर्ण_अगर

	क्रम_each_mem_range(i, &reg_start, &reg_end) अणु
		अगर (first) अणु
			phys_addr_t phys_offset = PHYS_OFFSET;

			/*
			 * Initially only use memory continuous from
			 * PHYS_OFFSET */
			अगर (reg_start != phys_offset)
				panic("First memory bank must be contiguous from PHYS_OFFSET");

			mem_start = reg_start;
			mem_end = reg_end;
			specअगरied_mem_size = mem_end - mem_start;
			first = false;
		पूर्ण अन्यथा अणु
			/*
			 * memblock स्वतः merges contiguous blocks, हटाओ
			 * all blocks afterwards in one go (we can't हटाओ
			 * blocks separately जबतक iterating)
			 */
			pr_notice("Ignoring RAM after %pa, memory at %pa ignored\n",
				  &mem_end, &reg_start);
			memblock_हटाओ(reg_start, 0 - reg_start);
			अवरोध;
		पूर्ण
	पूर्ण

	स_रखो(mem, 0, माप(mem));
	num = allocate_region(mem_start, specअगरied_mem_size, mem_max_regions, mem);

	क्रम (i = 0; i < num; i++) अणु
		अचिन्हित दीर्घ  subreg = mem[i].size / PMSAv7_NR_SUBREGS;

		total_mem_size += mem[i].size - subreg * hweight_दीर्घ(mem[i].subreg);

		pr_debug("MPU: base %pa size %pa disable subregions: %*pbl\n",
			 &mem[i].base, &mem[i].size, PMSAv7_NR_SUBREGS, &mem[i].subreg);
	पूर्ण

	अगर (total_mem_size != specअगरied_mem_size) अणु
		pr_warn("Truncating memory from %pa to %pa (MPU region constraints)",
				&specअगरied_mem_size, &total_mem_size);
		memblock_हटाओ(mem_start + total_mem_size,
				specअगरied_mem_size - total_mem_size);
	पूर्ण
पूर्ण

अटल पूर्णांक __init __mpu_max_regions(व्योम)
अणु
	/*
	 * We करोn't support a dअगरferent number of I/D side regions so अगर we
	 * have separate inकाष्ठाion and data memory maps then वापस
	 * whichever side has a smaller number of supported regions.
	 */
	u32 dregions, iregions, mpuir;

	mpuir = पढ़ो_cpuid_mputype();

	dregions = iregions = (mpuir & MPUIR_DREGION_SZMASK) >> MPUIR_DREGION;

	/* Check क्रम separate d-side and i-side memory maps */
	अगर (mpuir & MPUIR_nU)
		iregions = (mpuir & MPUIR_IREGION_SZMASK) >> MPUIR_IREGION;

	/* Use the smallest of the two maxima */
	वापस min(dregions, iregions);
पूर्ण

अटल पूर्णांक __init mpu_iside_independent(व्योम)
अणु
	/* MPUIR.nU specअगरies whether there is *not* a unअगरied memory map */
	वापस पढ़ो_cpuid_mputype() & MPUIR_nU;
पूर्ण

अटल पूर्णांक __init __mpu_min_region_order(व्योम)
अणु
	u32 drbar_result, irbar_result;

	/* We've kept a region मुक्त क्रम this probing */
	rgnr_ग_लिखो(PMSAv7_PROBE_REGION);
	isb();
	/*
	 * As per ARM ARM, ग_लिखो 0xFFFFFFFC to DRBAR to find the minimum
	 * region order
	*/
	drbar_ग_लिखो(0xFFFFFFFC);
	drbar_result = irbar_result = drbar_पढ़ो();
	drbar_ग_लिखो(0x0);
	/* If the MPU is non-unअगरied, we use the larger of the two minima*/
	अगर (mpu_iside_independent()) अणु
		irbar_ग_लिखो(0xFFFFFFFC);
		irbar_result = irbar_पढ़ो();
		irbar_ग_लिखो(0x0);
	पूर्ण
	isb(); /* Ensure that MPU region operations have completed */
	/* Return whichever result is larger */

	वापस __ffs(max(drbar_result, irbar_result));
पूर्ण

अटल पूर्णांक __init mpu_setup_region(अचिन्हित पूर्णांक number, phys_addr_t start,
				   अचिन्हित पूर्णांक size_order, अचिन्हित पूर्णांक properties,
				   अचिन्हित पूर्णांक subregions, bool need_flush)
अणु
	u32 size_data;

	/* We kept a region मुक्त क्रम probing resolution of MPU regions*/
	अगर (number > mpu_max_regions
	    || number >= MPU_MAX_REGIONS)
		वापस -ENOENT;

	अगर (size_order > 32)
		वापस -ENOMEM;

	अगर (size_order < mpu_min_region_order)
		वापस -ENOMEM;

	/* Writing N to bits 5:1 (RSR_SZ)  specअगरies region size 2^N+1 */
	size_data = ((size_order - 1) << PMSAv7_RSR_SZ) | 1 << PMSAv7_RSR_EN;
	size_data |= subregions << PMSAv7_RSR_SD;

	अगर (need_flush)
		flush_cache_all();

	dsb(); /* Ensure all previous data accesses occur with old mappings */
	rgnr_ग_लिखो(number);
	isb();
	drbar_ग_लिखो(start);
	dracr_ग_लिखो(properties);
	isb(); /* Propagate properties beक्रमe enabling region */
	drsr_ग_लिखो(size_data);

	/* Check क्रम independent I-side रेजिस्टरs */
	अगर (mpu_iside_independent()) अणु
		irbar_ग_लिखो(start);
		iracr_ग_लिखो(properties);
		isb();
		irsr_ग_लिखो(size_data);
	पूर्ण
	isb();

	/* Store region info (we treat i/d side the same, so only store d) */
	mpu_rgn_info.rgns[number].dracr = properties;
	mpu_rgn_info.rgns[number].drbar = start;
	mpu_rgn_info.rgns[number].drsr = size_data;

	mpu_rgn_info.used++;

	वापस 0;
पूर्ण

/*
* Set up शेष MPU regions, करोing nothing अगर there is no MPU
*/
व्योम __init pmsav7_setup(व्योम)
अणु
	पूर्णांक i, region = 0, err = 0;

	/* Setup MPU (order is important) */

	/* Background */
	err |= mpu_setup_region(region++, 0, 32,
				PMSAv7_ACR_XN | PMSAv7_RGN_STRONGLY_ORDERED | PMSAv7_AP_PL1RW_PL0RW,
				0, false);

#अगर_घोषित CONFIG_XIP_KERNEL
	/* ROM */
	क्रम (i = 0; i < ARRAY_SIZE(xip); i++) अणु
		/*
                 * In हाल we overग_लिखो RAM region we set earlier in
                 * head-nommu.S (which is cachable) all subsequent
                 * data access till we setup RAM bellow would be करोne
                 * with BG region (which is uncachable), thus we need
                 * to clean and invalidate cache.
		 */
		bool need_flush = region == PMSAv7_RAM_REGION;

		अगर (!xip[i].size)
			जारी;

		err |= mpu_setup_region(region++, xip[i].base, ilog2(xip[i].size),
					PMSAv7_AP_PL1RO_PL0NA | PMSAv7_RGN_NORMAL,
					xip[i].subreg, need_flush);
	पूर्ण
#पूर्ण_अगर

	/* RAM */
	क्रम (i = 0; i < ARRAY_SIZE(mem); i++) अणु
		अगर (!mem[i].size)
			जारी;

		err |= mpu_setup_region(region++, mem[i].base, ilog2(mem[i].size),
					PMSAv7_AP_PL1RW_PL0RW | PMSAv7_RGN_NORMAL,
					mem[i].subreg, false);
	पूर्ण

	/* Vectors */
#अगर_अघोषित CONFIG_CPU_V7M
	err |= mpu_setup_region(region++, vectors_base, ilog2(2 * PAGE_SIZE),
				PMSAv7_AP_PL1RW_PL0NA | PMSAv7_RGN_NORMAL,
				0, false);
#पूर्ण_अगर
	अगर (err) अणु
		panic("MPU region initialization failure! %d", err);
	पूर्ण अन्यथा अणु
		pr_info("Using ARMv7 PMSA Compliant MPU. "
			 "Region independence: %s, Used %d of %d regions\n",
			mpu_iside_independent() ? "Yes" : "No",
			mpu_rgn_info.used, mpu_max_regions);
	पूर्ण
पूर्ण
