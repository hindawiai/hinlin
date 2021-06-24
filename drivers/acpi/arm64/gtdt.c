<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARM Specअगरic GTDT table Support
 *
 * Copyright (C) 2016, Linaro Ltd.
 * Author: Daniel Lezcano <daniel.lezcano@linaro.org>
 *         Fu Wei <fu.wei@linaro.org>
 *         Hanjun Guo <hanjun.guo@linaro.org>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <घड़ीsource/arm_arch_समयr.h>

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "ACPI GTDT: " fmt

/**
 * काष्ठा acpi_gtdt_descriptor - Store the key info of GTDT क्रम all functions
 * @gtdt:	The poपूर्णांकer to the काष्ठा acpi_table_gtdt of GTDT table.
 * @gtdt_end:	The poपूर्णांकer to the end of GTDT table.
 * @platक्रमm_समयr:	The poपूर्णांकer to the start of Platक्रमm Timer Structure
 *
 * The काष्ठा store the key info of GTDT table, it should be initialized by
 * acpi_gtdt_init.
 */
काष्ठा acpi_gtdt_descriptor अणु
	काष्ठा acpi_table_gtdt *gtdt;
	व्योम *gtdt_end;
	व्योम *platक्रमm_समयr;
पूर्ण;

अटल काष्ठा acpi_gtdt_descriptor acpi_gtdt_desc __initdata;

अटल अंतरभूत व्योम *next_platक्रमm_समयr(व्योम *platक्रमm_समयr)
अणु
	काष्ठा acpi_gtdt_header *gh = platक्रमm_समयr;

	platक्रमm_समयr += gh->length;
	अगर (platक्रमm_समयr < acpi_gtdt_desc.gtdt_end)
		वापस platक्रमm_समयr;

	वापस शून्य;
पूर्ण

#घोषणा क्रम_each_platक्रमm_समयr(_g)				\
	क्रम (_g = acpi_gtdt_desc.platक्रमm_समयr; _g;	\
	     _g = next_platक्रमm_समयr(_g))

अटल अंतरभूत bool is_समयr_block(व्योम *platक्रमm_समयr)
अणु
	काष्ठा acpi_gtdt_header *gh = platक्रमm_समयr;

	वापस gh->type == ACPI_GTDT_TYPE_TIMER_BLOCK;
पूर्ण

अटल अंतरभूत bool is_non_secure_watchकरोg(व्योम *platक्रमm_समयr)
अणु
	काष्ठा acpi_gtdt_header *gh = platक्रमm_समयr;
	काष्ठा acpi_gtdt_watchकरोg *wd = platक्रमm_समयr;

	अगर (gh->type != ACPI_GTDT_TYPE_WATCHDOG)
		वापस false;

	वापस !(wd->समयr_flags & ACPI_GTDT_WATCHDOG_SECURE);
पूर्ण

अटल पूर्णांक __init map_gt_gsi(u32 पूर्णांकerrupt, u32 flags)
अणु
	पूर्णांक trigger, polarity;

	trigger = (flags & ACPI_GTDT_INTERRUPT_MODE) ? ACPI_EDGE_SENSITIVE
			: ACPI_LEVEL_SENSITIVE;

	polarity = (flags & ACPI_GTDT_INTERRUPT_POLARITY) ? ACPI_ACTIVE_LOW
			: ACPI_ACTIVE_HIGH;

	वापस acpi_रेजिस्टर_gsi(शून्य, पूर्णांकerrupt, trigger, polarity);
पूर्ण

/**
 * acpi_gtdt_map_ppi() - Map the PPIs of per-cpu arch_समयr.
 * @type:	the type of PPI.
 *
 * Note: Secure state is not managed by the kernel on ARM64 प्रणालीs.
 * So we only handle the non-secure समयr PPIs,
 * ARCH_TIMER_PHYS_SECURE_PPI is treated as invalid type.
 *
 * Return: the mapped PPI value, 0 अगर error.
 */
पूर्णांक __init acpi_gtdt_map_ppi(पूर्णांक type)
अणु
	काष्ठा acpi_table_gtdt *gtdt = acpi_gtdt_desc.gtdt;

	चयन (type) अणु
	हाल ARCH_TIMER_PHYS_NONSECURE_PPI:
		वापस map_gt_gsi(gtdt->non_secure_el1_पूर्णांकerrupt,
				  gtdt->non_secure_el1_flags);
	हाल ARCH_TIMER_VIRT_PPI:
		वापस map_gt_gsi(gtdt->भव_समयr_पूर्णांकerrupt,
				  gtdt->भव_समयr_flags);

	हाल ARCH_TIMER_HYP_PPI:
		वापस map_gt_gsi(gtdt->non_secure_el2_पूर्णांकerrupt,
				  gtdt->non_secure_el2_flags);
	शेष:
		pr_err("Failed to map timer interrupt: invalid type.\n");
	पूर्ण

	वापस 0;
पूर्ण

/**
 * acpi_gtdt_c3stop() - Got c3stop info from GTDT according to the type of PPI.
 * @type:	the type of PPI.
 *
 * Return: true अगर the समयr HW state is lost when a CPU enters an idle state,
 * false otherwise
 */
bool __init acpi_gtdt_c3stop(पूर्णांक type)
अणु
	काष्ठा acpi_table_gtdt *gtdt = acpi_gtdt_desc.gtdt;

	चयन (type) अणु
	हाल ARCH_TIMER_PHYS_NONSECURE_PPI:
		वापस !(gtdt->non_secure_el1_flags & ACPI_GTDT_ALWAYS_ON);

	हाल ARCH_TIMER_VIRT_PPI:
		वापस !(gtdt->भव_समयr_flags & ACPI_GTDT_ALWAYS_ON);

	हाल ARCH_TIMER_HYP_PPI:
		वापस !(gtdt->non_secure_el2_flags & ACPI_GTDT_ALWAYS_ON);

	शेष:
		pr_err("Failed to get c3stop info: invalid type.\n");
	पूर्ण

	वापस false;
पूर्ण

/**
 * acpi_gtdt_init() - Get the info of GTDT table to prepare क्रम further init.
 * @table:			The poपूर्णांकer to GTDT table.
 * @platक्रमm_समयr_count:	It poपूर्णांकs to a पूर्णांकeger variable which is used
 *				क्रम storing the number of platक्रमm समयrs.
 *				This poपूर्णांकer could be शून्य, अगर the caller
 *				करोesn't need this info.
 *
 * Return: 0 अगर success, -EINVAL अगर error.
 */
पूर्णांक __init acpi_gtdt_init(काष्ठा acpi_table_header *table,
			  पूर्णांक *platक्रमm_समयr_count)
अणु
	व्योम *platक्रमm_समयr;
	काष्ठा acpi_table_gtdt *gtdt;

	gtdt = container_of(table, काष्ठा acpi_table_gtdt, header);
	acpi_gtdt_desc.gtdt = gtdt;
	acpi_gtdt_desc.gtdt_end = (व्योम *)table + table->length;
	acpi_gtdt_desc.platक्रमm_समयr = शून्य;
	अगर (platक्रमm_समयr_count)
		*platक्रमm_समयr_count = 0;

	अगर (table->revision < 2) अणु
		pr_warn("Revision:%d doesn't support Platform Timers.\n",
			table->revision);
		वापस 0;
	पूर्ण

	अगर (!gtdt->platक्रमm_समयr_count) अणु
		pr_debug("No Platform Timer.\n");
		वापस 0;
	पूर्ण

	platक्रमm_समयr = (व्योम *)gtdt + gtdt->platक्रमm_समयr_offset;
	अगर (platक्रमm_समयr < (व्योम *)table + माप(काष्ठा acpi_table_gtdt)) अणु
		pr_err(FW_BUG "invalid timer data.\n");
		वापस -EINVAL;
	पूर्ण
	acpi_gtdt_desc.platक्रमm_समयr = platक्रमm_समयr;
	अगर (platक्रमm_समयr_count)
		*platक्रमm_समयr_count = gtdt->platक्रमm_समयr_count;

	वापस 0;
पूर्ण

अटल पूर्णांक __init gtdt_parse_समयr_block(काष्ठा acpi_gtdt_समयr_block *block,
					 काष्ठा arch_समयr_mem *समयr_mem)
अणु
	पूर्णांक i;
	काष्ठा arch_समयr_mem_frame *frame;
	काष्ठा acpi_gtdt_समयr_entry *gtdt_frame;

	अगर (!block->समयr_count) अणु
		pr_err(FW_BUG "GT block present, but frame count is zero.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (block->समयr_count > ARCH_TIMER_MEM_MAX_FRAMES) अणु
		pr_err(FW_BUG "GT block lists %d frames, ACPI spec only allows 8\n",
		       block->समयr_count);
		वापस -EINVAL;
	पूर्ण

	समयr_mem->cntctlbase = (phys_addr_t)block->block_address;
	/*
	 * The CNTCTLBase frame is 4KB (रेजिस्टर offsets 0x000 - 0xFFC).
	 * See ARM DDI 0487A.k_iss10775, page I1-5129, Table I1-3
	 * "CNTCTLBase memory map".
	 */
	समयr_mem->size = SZ_4K;

	gtdt_frame = (व्योम *)block + block->समयr_offset;
	अगर (gtdt_frame + block->समयr_count != (व्योम *)block + block->header.length)
		वापस -EINVAL;

	/*
	 * Get the GT समयr Frame data क्रम every GT Block Timer
	 */
	क्रम (i = 0; i < block->समयr_count; i++, gtdt_frame++) अणु
		अगर (gtdt_frame->common_flags & ACPI_GTDT_GT_IS_SECURE_TIMER)
			जारी;
		अगर (gtdt_frame->frame_number >= ARCH_TIMER_MEM_MAX_FRAMES ||
		    !gtdt_frame->base_address || !gtdt_frame->समयr_पूर्णांकerrupt)
			जाओ error;

		frame = &समयr_mem->frame[gtdt_frame->frame_number];

		/* duplicate frame */
		अगर (frame->valid)
			जाओ error;

		frame->phys_irq = map_gt_gsi(gtdt_frame->समयr_पूर्णांकerrupt,
					     gtdt_frame->समयr_flags);
		अगर (frame->phys_irq <= 0) अणु
			pr_warn("failed to map physical timer irq in frame %d.\n",
				gtdt_frame->frame_number);
			जाओ error;
		पूर्ण

		अगर (gtdt_frame->भव_समयr_पूर्णांकerrupt) अणु
			frame->virt_irq =
				map_gt_gsi(gtdt_frame->भव_समयr_पूर्णांकerrupt,
					   gtdt_frame->भव_समयr_flags);
			अगर (frame->virt_irq <= 0) अणु
				pr_warn("failed to map virtual timer irq in frame %d.\n",
					gtdt_frame->frame_number);
				जाओ error;
			पूर्ण
		पूर्ण अन्यथा अणु
			pr_debug("virtual timer in frame %d not implemented.\n",
				 gtdt_frame->frame_number);
		पूर्ण

		frame->cntbase = gtdt_frame->base_address;
		/*
		 * The CNTBaseN frame is 4KB (रेजिस्टर offsets 0x000 - 0xFFC).
		 * See ARM DDI 0487A.k_iss10775, page I1-5130, Table I1-4
		 * "CNTBaseN memory map".
		 */
		frame->size = SZ_4K;
		frame->valid = true;
	पूर्ण

	वापस 0;

error:
	करो अणु
		अगर (gtdt_frame->common_flags & ACPI_GTDT_GT_IS_SECURE_TIMER ||
		    gtdt_frame->frame_number >= ARCH_TIMER_MEM_MAX_FRAMES)
			जारी;

		frame = &समयr_mem->frame[gtdt_frame->frame_number];

		अगर (frame->phys_irq > 0)
			acpi_unरेजिस्टर_gsi(gtdt_frame->समयr_पूर्णांकerrupt);
		frame->phys_irq = 0;

		अगर (frame->virt_irq > 0)
			acpi_unरेजिस्टर_gsi(gtdt_frame->भव_समयr_पूर्णांकerrupt);
		frame->virt_irq = 0;
	पूर्ण जबतक (i-- >= 0 && gtdt_frame--);

	वापस -EINVAL;
पूर्ण

/**
 * acpi_arch_समयr_mem_init() - Get the info of all GT blocks in GTDT table.
 * @समयr_mem:	The poपूर्णांकer to the array of काष्ठा arch_समयr_mem क्रम वापसing
 *		the result of parsing. The element number of this array should
 *		be platक्रमm_समयr_count(the total number of platक्रमm समयrs).
 * @समयr_count: It poपूर्णांकs to a पूर्णांकeger variable which is used क्रम storing the
 *		number of GT blocks we have parsed.
 *
 * Return: 0 अगर success, -EINVAL/-ENODEV अगर error.
 */
पूर्णांक __init acpi_arch_समयr_mem_init(काष्ठा arch_समयr_mem *समयr_mem,
				    पूर्णांक *समयr_count)
अणु
	पूर्णांक ret;
	व्योम *platक्रमm_समयr;

	*समयr_count = 0;
	क्रम_each_platक्रमm_समयr(platक्रमm_समयr) अणु
		अगर (is_समयr_block(platक्रमm_समयr)) अणु
			ret = gtdt_parse_समयr_block(platक्रमm_समयr, समयr_mem);
			अगर (ret)
				वापस ret;
			समयr_mem++;
			(*समयr_count)++;
		पूर्ण
	पूर्ण

	अगर (*समयr_count)
		pr_info("found %d memory-mapped timer block(s).\n",
			*समयr_count);

	वापस 0;
पूर्ण

/*
 * Initialize a SBSA generic Watchकरोg platक्रमm device info from GTDT
 */
अटल पूर्णांक __init gtdt_import_sbsa_gwdt(काष्ठा acpi_gtdt_watchकरोg *wd,
					पूर्णांक index)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक irq;

	/*
	 * According to SBSA specअगरication the size of refresh and control
	 * frames of SBSA Generic Watchकरोg is SZ_4K(Offset 0x000 ै  0xFFF).
	 */
	काष्ठा resource res[] = अणु
		DEFINE_RES_MEM(wd->control_frame_address, SZ_4K),
		DEFINE_RES_MEM(wd->refresh_frame_address, SZ_4K),
		अणुपूर्ण,
	पूर्ण;
	पूर्णांक nr_res = ARRAY_SIZE(res);

	pr_debug("found a Watchdog (0x%llx/0x%llx gsi:%u flags:0x%x).\n",
		 wd->refresh_frame_address, wd->control_frame_address,
		 wd->समयr_पूर्णांकerrupt, wd->समयr_flags);

	अगर (!(wd->refresh_frame_address && wd->control_frame_address)) अणु
		pr_err(FW_BUG "failed to get the Watchdog base address.\n");
		वापस -EINVAL;
	पूर्ण

	irq = map_gt_gsi(wd->समयr_पूर्णांकerrupt, wd->समयr_flags);
	res[2] = (काष्ठा resource)DEFINE_RES_IRQ(irq);
	अगर (irq <= 0) अणु
		pr_warn("failed to map the Watchdog interrupt.\n");
		nr_res--;
	पूर्ण

	/*
	 * Add a platक्रमm device named "sbsa-gwdt" to match the platक्रमm driver.
	 * "sbsa-gwdt": SBSA(Server Base System Architecture) Generic Watchकरोg
	 * The platक्रमm driver can get device info below by matching this name.
	 */
	pdev = platक्रमm_device_रेजिस्टर_simple("sbsa-gwdt", index, res, nr_res);
	अगर (IS_ERR(pdev)) अणु
		अगर (irq > 0)
			acpi_unरेजिस्टर_gsi(wd->समयr_पूर्णांकerrupt);
		वापस PTR_ERR(pdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init gtdt_sbsa_gwdt_init(व्योम)
अणु
	व्योम *platक्रमm_समयr;
	काष्ठा acpi_table_header *table;
	पूर्णांक ret, समयr_count, gwdt_count = 0;

	अगर (acpi_disabled)
		वापस 0;

	अगर (ACPI_FAILURE(acpi_get_table(ACPI_SIG_GTDT, 0, &table)))
		वापस -EINVAL;

	/*
	 * Note: Even though the global variable acpi_gtdt_desc has been
	 * initialized by acpi_gtdt_init() जबतक initializing the arch समयrs,
	 * when we call this function to get SBSA watchकरोgs info from GTDT, the
	 * poपूर्णांकers stashed in it are stale (since they are early temporary
	 * mappings carried out beक्रमe acpi_permanent_mmap is set) and we need
	 * to re-initialize them with permanent mapped poपूर्णांकer values to let the
	 * GTDT parsing possible.
	 */
	ret = acpi_gtdt_init(table, &समयr_count);
	अगर (ret || !समयr_count)
		जाओ out_put_gtdt;

	क्रम_each_platक्रमm_समयr(platक्रमm_समयr) अणु
		अगर (is_non_secure_watchकरोg(platक्रमm_समयr)) अणु
			ret = gtdt_import_sbsa_gwdt(platक्रमm_समयr, gwdt_count);
			अगर (ret)
				अवरोध;
			gwdt_count++;
		पूर्ण
	पूर्ण

	अगर (gwdt_count)
		pr_info("found %d SBSA generic Watchdog(s).\n", gwdt_count);

out_put_gtdt:
	acpi_put_table(table);
	वापस ret;
पूर्ण

device_initcall(gtdt_sbsa_gwdt_init);
