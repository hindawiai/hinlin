<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R-Car Generation 2 support
 *
 * Copyright (C) 2013  Renesas Solutions Corp.
 * Copyright (C) 2013  Magnus Damm
 * Copyright (C) 2014  Ulrich Hecht
 */

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/psci.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/secure_cntvoff.h>
#समावेश "common.h"
#समावेश "rcar-gen2.h"

अटल स्थिर काष्ठा of_device_id cpg_matches[] __initस्थिर = अणु
	अणु .compatible = "renesas,r8a7742-cpg-mssr", .data = "extal" पूर्ण,
	अणु .compatible = "renesas,r8a7743-cpg-mssr", .data = "extal" पूर्ण,
	अणु .compatible = "renesas,r8a7744-cpg-mssr", .data = "extal" पूर्ण,
	अणु .compatible = "renesas,r8a7790-cpg-mssr", .data = "extal" पूर्ण,
	अणु .compatible = "renesas,r8a7791-cpg-mssr", .data = "extal" पूर्ण,
	अणु .compatible = "renesas,r8a7793-cpg-mssr", .data = "extal" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल अचिन्हित पूर्णांक __init get_extal_freq(व्योम)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *cpg, *extal;
	u32 freq = 20000000;
	पूर्णांक idx = 0;

	cpg = of_find_matching_node_and_match(शून्य, cpg_matches, &match);
	अगर (!cpg)
		वापस freq;

	अगर (match->data)
		idx = of_property_match_string(cpg, "clock-names", match->data);
	extal = of_parse_phandle(cpg, "clocks", idx);
	of_node_put(cpg);
	अगर (!extal)
		वापस freq;

	of_property_पढ़ो_u32(extal, "clock-frequency", &freq);
	of_node_put(extal);
	वापस freq;
पूर्ण

#घोषणा CNTCR 0
#घोषणा CNTFID0 0x20

अटल व्योम __init rcar_gen2_समयr_init(व्योम)
अणु
	bool need_update = true;
	व्योम __iomem *base;
	u32 freq;

	/*
	 * If PSCI is available then most likely we are running on PSCI-enabled
	 * U-Boot which, we assume, has alपढ़ोy taken care of resetting CNTVOFF
	 * and updating counter module beक्रमe चयनing to non-secure mode
	 * and we करोn't need to.
	 */
#अगर_घोषित CONFIG_ARM_PSCI_FW
	अगर (psci_ops.cpu_on)
		need_update = false;
#पूर्ण_अगर

	अगर (need_update == false)
		जाओ skip_update;

	secure_cntvoff_init();

	अगर (of_machine_is_compatible("renesas,r8a7745") ||
	    of_machine_is_compatible("renesas,r8a77470") ||
	    of_machine_is_compatible("renesas,r8a7792") ||
	    of_machine_is_compatible("renesas,r8a7794")) अणु
		freq = 260000000 / 8;	/* ZS / 8 */
	पूर्ण अन्यथा अणु
		/* At Linux boot समय the r8a7790 arch समयr comes up
		 * with the counter disabled. Moreover, it may also report
		 * a potentially incorrect fixed 13 MHz frequency. To be
		 * correct these रेजिस्टरs need to be updated to use the
		 * frequency EXTAL / 2.
		 */
		freq = get_extal_freq() / 2;
	पूर्ण

	/* Remap "armgcnt address map" space */
	base = ioremap(0xe6080000, PAGE_SIZE);

	/*
	 * Update the समयr अगर it is either not running, or is not at the
	 * right frequency. The समयr is only configurable in secure mode
	 * so this aव्योमs an पात अगर the loader started the समयr and
	 * entered the kernel in non-secure mode.
	 */

	अगर ((ioपढ़ो32(base + CNTCR) & 1) == 0 ||
	    ioपढ़ो32(base + CNTFID0) != freq) अणु
		/* Update रेजिस्टरs with correct frequency */
		ioग_लिखो32(freq, base + CNTFID0);
		यंत्र अस्थिर("mcr p15, 0, %0, c14, c0, 0" : : "r" (freq));

		/* make sure arch समयr is started by setting bit 0 of CNTCR */
		ioग_लिखो32(1, base + CNTCR);
	पूर्ण

	iounmap(base);

skip_update:
	of_clk_init(शून्य);
	समयr_probe();
पूर्ण

काष्ठा memory_reserve_config अणु
	u64 reserved;
	u64 base, size;
पूर्ण;

अटल पूर्णांक __init rcar_gen2_scan_mem(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				     पूर्णांक depth, व्योम *data)
अणु
	स्थिर अक्षर *type = of_get_flat_dt_prop(node, "device_type", शून्य);
	स्थिर __be32 *reg, *endp;
	पूर्णांक l;
	काष्ठा memory_reserve_config *mrc = data;
	u64 lpae_start = 1ULL << 32;

	/* We are scanning "memory" nodes only */
	अगर (type == शून्य || म_भेद(type, "memory"))
		वापस 0;

	reg = of_get_flat_dt_prop(node, "linux,usable-memory", &l);
	अगर (reg == शून्य)
		reg = of_get_flat_dt_prop(node, "reg", &l);
	अगर (reg == शून्य)
		वापस 0;

	endp = reg + (l / माप(__be32));
	जबतक ((endp - reg) >= (dt_root_addr_cells + dt_root_size_cells)) अणु
		u64 base, size;

		base = dt_mem_next_cell(dt_root_addr_cells, &reg);
		size = dt_mem_next_cell(dt_root_size_cells, &reg);

		अगर (base >= lpae_start)
			जारी;

		अगर ((base + size) >= lpae_start)
			size = lpae_start - base;

		अगर (size < mrc->reserved)
			जारी;

		अगर (base < mrc->base)
			जारी;

		/* keep the area at top near the 32-bit legacy limit */
		mrc->base = base + size - mrc->reserved;
		mrc->size = mrc->reserved;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init rcar_gen2_reserve(व्योम)
अणु
	काष्ठा memory_reserve_config mrc;

	/* reserve 256 MiB at the top of the physical legacy 32-bit space */
	स_रखो(&mrc, 0, माप(mrc));
	mrc.reserved = SZ_256M;

	of_scan_flat_dt(rcar_gen2_scan_mem, &mrc);
#अगर_घोषित CONFIG_DMA_CMA
	अगर (mrc.size && memblock_is_region_memory(mrc.base, mrc.size)) अणु
		अटल काष्ठा cma *rcar_gen2_dma_contiguous;

		dma_contiguous_reserve_area(mrc.size, mrc.base, 0,
					    &rcar_gen2_dma_contiguous, true);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल स्थिर अक्षर * स्थिर rcar_gen2_boards_compat_dt[] __initस्थिर = अणु
	"renesas,r8a7790",
	"renesas,r8a7791",
	"renesas,r8a7792",
	"renesas,r8a7793",
	"renesas,r8a7794",
	शून्य,
पूर्ण;

DT_MACHINE_START(RCAR_GEN2_DT, "Generic R-Car Gen2 (Flattened Device Tree)")
	.init_late	= shmobile_init_late,
	.init_समय	= rcar_gen2_समयr_init,
	.reserve	= rcar_gen2_reserve,
	.dt_compat	= rcar_gen2_boards_compat_dt,
MACHINE_END

अटल स्थिर अक्षर * स्थिर rz_g1_boards_compat_dt[] __initस्थिर = अणु
	"renesas,r8a7742",
	"renesas,r8a7743",
	"renesas,r8a7744",
	"renesas,r8a7745",
	"renesas,r8a77470",
	शून्य,
पूर्ण;

DT_MACHINE_START(RZ_G1_DT, "Generic RZ/G1 (Flattened Device Tree)")
	.init_late	= shmobile_init_late,
	.init_समय	= rcar_gen2_समयr_init,
	.reserve	= rcar_gen2_reserve,
	.dt_compat	= rz_g1_boards_compat_dt,
MACHINE_END
