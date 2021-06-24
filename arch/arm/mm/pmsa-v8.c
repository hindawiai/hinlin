<शैली गुरु>
/*
 * Based on linux/arch/arm/pmsa-v7.c
 *
 * ARM PMSAv8 supporting functions.
 */

#समावेश <linux/memblock.h>
#समावेश <linux/range.h>

#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/mpu.h>

#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/sections.h>

#समावेश "mm.h"

#अगर_अघोषित CONFIG_CPU_V7M

#घोषणा PRSEL	__ACCESS_CP15(c6, 0, c2, 1)
#घोषणा PRBAR	__ACCESS_CP15(c6, 0, c3, 0)
#घोषणा PRLAR	__ACCESS_CP15(c6, 0, c3, 1)

अटल अंतरभूत u32 prlar_पढ़ो(व्योम)
अणु
	वापस पढ़ो_sysreg(PRLAR);
पूर्ण

अटल अंतरभूत u32 prbar_पढ़ो(व्योम)
अणु
	वापस पढ़ो_sysreg(PRBAR);
पूर्ण

अटल अंतरभूत व्योम prsel_ग_लिखो(u32 v)
अणु
	ग_लिखो_sysreg(v, PRSEL);
पूर्ण

अटल अंतरभूत व्योम prbar_ग_लिखो(u32 v)
अणु
	ग_लिखो_sysreg(v, PRBAR);
पूर्ण

अटल अंतरभूत व्योम prlar_ग_लिखो(u32 v)
अणु
	ग_लिखो_sysreg(v, PRLAR);
पूर्ण
#अन्यथा

अटल अंतरभूत u32 prlar_पढ़ो(व्योम)
अणु
	वापस पढ़ोl_relaxed(BASEADDR_V7M_SCB + PMSAv8_RLAR);
पूर्ण

अटल अंतरभूत u32 prbar_पढ़ो(व्योम)
अणु
	वापस पढ़ोl_relaxed(BASEADDR_V7M_SCB + PMSAv8_RBAR);
पूर्ण

अटल अंतरभूत व्योम prsel_ग_लिखो(u32 v)
अणु
	ग_लिखोl_relaxed(v, BASEADDR_V7M_SCB + PMSAv8_RNR);
पूर्ण

अटल अंतरभूत व्योम prbar_ग_लिखो(u32 v)
अणु
	ग_लिखोl_relaxed(v, BASEADDR_V7M_SCB + PMSAv8_RBAR);
पूर्ण

अटल अंतरभूत व्योम prlar_ग_लिखो(u32 v)
अणु
	ग_लिखोl_relaxed(v, BASEADDR_V7M_SCB + PMSAv8_RLAR);
पूर्ण

#पूर्ण_अगर

अटल काष्ठा range __initdata io[MPU_MAX_REGIONS];
अटल काष्ठा range __initdata mem[MPU_MAX_REGIONS];

अटल अचिन्हित पूर्णांक __initdata mpu_max_regions;

अटल __init bool is_region_fixed(पूर्णांक number)
अणु
	चयन (number) अणु
	हाल PMSAv8_XIP_REGION:
	हाल PMSAv8_KERNEL_REGION:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

व्योम __init pmsav8_adjust_lowmem_bounds(व्योम)
अणु
	phys_addr_t mem_end;
	phys_addr_t reg_start, reg_end;
	bool first = true;
	u64 i;

	क्रम_each_mem_range(i, &reg_start, &reg_end) अणु
		अगर (first) अणु
			phys_addr_t phys_offset = PHYS_OFFSET;

			/*
			 * Initially only use memory continuous from
			 * PHYS_OFFSET */
			अगर (reg_start != phys_offset)
				panic("First memory bank must be contiguous from PHYS_OFFSET");
			mem_end = reg_end;
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
पूर्ण

अटल पूर्णांक __init __mpu_max_regions(व्योम)
अणु
	अटल पूर्णांक max_regions;
	u32 mpuir;

	अगर (max_regions)
		वापस max_regions;

	mpuir = पढ़ो_cpuid_mputype();

	max_regions  = (mpuir & MPUIR_DREGION_SZMASK) >> MPUIR_DREGION;

	वापस max_regions;
पूर्ण

अटल पूर्णांक __init __pmsav8_setup_region(अचिन्हित पूर्णांक number, u32 bar, u32 lar)
अणु
	अगर (number > mpu_max_regions
	    || number >= MPU_MAX_REGIONS)
		वापस -ENOENT;

	dsb();
	prsel_ग_लिखो(number);
	isb();
	prbar_ग_लिखो(bar);
	prlar_ग_लिखो(lar);

	mpu_rgn_info.rgns[number].prbar = bar;
	mpu_rgn_info.rgns[number].prlar = lar;

	mpu_rgn_info.used++;

	वापस 0;
पूर्ण

अटल पूर्णांक __init pmsav8_setup_ram(अचिन्हित पूर्णांक number, phys_addr_t start,phys_addr_t end)
अणु
	u32 bar, lar;

	अगर (is_region_fixed(number))
		वापस -EINVAL;

	bar = start;
	lar = (end - 1) & ~(PMSAv8_MINALIGN - 1);

	bar |= PMSAv8_AP_PL1RW_PL0RW | PMSAv8_RGN_SHARED;
	lar |= PMSAv8_LAR_IDX(PMSAv8_RGN_NORMAL) | PMSAv8_LAR_EN;

	वापस __pmsav8_setup_region(number, bar, lar);
पूर्ण

अटल पूर्णांक __init pmsav8_setup_io(अचिन्हित पूर्णांक number, phys_addr_t start,phys_addr_t end)
अणु
	u32 bar, lar;

	अगर (is_region_fixed(number))
		वापस -EINVAL;

	bar = start;
	lar = (end - 1) & ~(PMSAv8_MINALIGN - 1);

	bar |= PMSAv8_AP_PL1RW_PL0RW | PMSAv8_RGN_SHARED | PMSAv8_BAR_XN;
	lar |= PMSAv8_LAR_IDX(PMSAv8_RGN_DEVICE_nGnRnE) | PMSAv8_LAR_EN;

	वापस __pmsav8_setup_region(number, bar, lar);
पूर्ण

अटल पूर्णांक __init pmsav8_setup_fixed(अचिन्हित पूर्णांक number, phys_addr_t start,phys_addr_t end)
अणु
	u32 bar, lar;

	अगर (!is_region_fixed(number))
		वापस -EINVAL;

	bar = start;
	lar = (end - 1) & ~(PMSAv8_MINALIGN - 1);

	bar |= PMSAv8_AP_PL1RW_PL0NA | PMSAv8_RGN_SHARED;
	lar |= PMSAv8_LAR_IDX(PMSAv8_RGN_NORMAL) | PMSAv8_LAR_EN;

	prsel_ग_लिखो(number);
	isb();

	अगर (prbar_पढ़ो() != bar || prlar_पढ़ो() != lar)
		वापस -EINVAL;

	/* Reserved region was set up early, we just need a record क्रम secondaries */
	mpu_rgn_info.rgns[number].prbar = bar;
	mpu_rgn_info.rgns[number].prlar = lar;

	mpu_rgn_info.used++;

	वापस 0;
पूर्ण

#अगर_अघोषित CONFIG_CPU_V7M
अटल पूर्णांक __init pmsav8_setup_vector(अचिन्हित पूर्णांक number, phys_addr_t start,phys_addr_t end)
अणु
	u32 bar, lar;

	अगर (number == PMSAv8_KERNEL_REGION)
		वापस -EINVAL;

	bar = start;
	lar = (end - 1) & ~(PMSAv8_MINALIGN - 1);

	bar |= PMSAv8_AP_PL1RW_PL0NA | PMSAv8_RGN_SHARED;
	lar |= PMSAv8_LAR_IDX(PMSAv8_RGN_NORMAL) | PMSAv8_LAR_EN;

	वापस __pmsav8_setup_region(number, bar, lar);
पूर्ण
#पूर्ण_अगर

व्योम __init pmsav8_setup(व्योम)
अणु
	पूर्णांक i, err = 0;
	पूर्णांक region = PMSAv8_KERNEL_REGION;

	/* How many regions are supported ? */
	mpu_max_regions = __mpu_max_regions();

	/* RAM: single chunk of memory */
	add_range(mem,  ARRAY_SIZE(mem), 0,  memblock.memory.regions[0].base,
		  memblock.memory.regions[0].base + memblock.memory.regions[0].size);

	/* IO: cover full 4G range */
	add_range(io, ARRAY_SIZE(io), 0, 0, 0xffffffff);

	/* RAM and IO: exclude kernel */
	subtract_range(mem, ARRAY_SIZE(mem), __pa(KERNEL_START), __pa(KERNEL_END));
	subtract_range(io, ARRAY_SIZE(io),  __pa(KERNEL_START), __pa(KERNEL_END));

#अगर_घोषित CONFIG_XIP_KERNEL
	/* RAM and IO: exclude xip */
	subtract_range(mem, ARRAY_SIZE(mem), CONFIG_XIP_PHYS_ADDR, __pa(_exiprom));
	subtract_range(io, ARRAY_SIZE(io), CONFIG_XIP_PHYS_ADDR, __pa(_exiprom));
#पूर्ण_अगर

#अगर_अघोषित CONFIG_CPU_V7M
	/* RAM and IO: exclude vectors */
	subtract_range(mem, ARRAY_SIZE(mem),  vectors_base, vectors_base + 2 * PAGE_SIZE);
	subtract_range(io, ARRAY_SIZE(io),  vectors_base, vectors_base + 2 * PAGE_SIZE);
#पूर्ण_अगर
	/* IO: exclude RAM */
	क्रम (i = 0; i < ARRAY_SIZE(mem); i++)
		subtract_range(io, ARRAY_SIZE(io), mem[i].start, mem[i].end);

	/* Now program MPU */

#अगर_घोषित CONFIG_XIP_KERNEL
	/* ROM */
	err |= pmsav8_setup_fixed(PMSAv8_XIP_REGION, CONFIG_XIP_PHYS_ADDR, __pa(_exiprom));
#पूर्ण_अगर
	/* Kernel */
	err |= pmsav8_setup_fixed(region++, __pa(KERNEL_START), __pa(KERNEL_END));


	/* IO */
	क्रम (i = 0; i < ARRAY_SIZE(io); i++) अणु
		अगर (!io[i].end)
			जारी;

		err |= pmsav8_setup_io(region++, io[i].start, io[i].end);
	पूर्ण

	/* RAM */
	क्रम (i = 0; i < ARRAY_SIZE(mem); i++) अणु
		अगर (!mem[i].end)
			जारी;

		err |= pmsav8_setup_ram(region++, mem[i].start, mem[i].end);
	पूर्ण

	/* Vectors */
#अगर_अघोषित CONFIG_CPU_V7M
	err |= pmsav8_setup_vector(region++, vectors_base, vectors_base + 2 * PAGE_SIZE);
#पूर्ण_अगर
	अगर (err)
		pr_warn("MPU region initialization failure! %d", err);
	अन्यथा
		pr_info("Using ARM PMSAv8 Compliant MPU. Used %d of %d regions\n",
			mpu_rgn_info.used, mpu_max_regions);
पूर्ण
