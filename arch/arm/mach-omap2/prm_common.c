<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP2+ common Power & Reset Management (PRM) IP block functions
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Tero Kristo <t-kristo@ti.com>
 *
 * For historical purposes, the API used to configure the PRM
 * पूर्णांकerrupt handler refers to it as the "PRCM interrupt."  The
 * underlying रेजिस्टरs are located in the PRM on OMAP3/4.
 *
 * XXX This code should eventually be moved to a PRM driver.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/ti.h>

#समावेश "soc.h"
#समावेश "prm2xxx_3xxx.h"
#समावेश "prm2xxx.h"
#समावेश "prm3xxx.h"
#समावेश "prm33xx.h"
#समावेश "prm44xx.h"
#समावेश "prm54xx.h"
#समावेश "prm7xx.h"
#समावेश "prcm43xx.h"
#समावेश "common.h"
#समावेश "clock.h"
#समावेश "cm.h"
#समावेश "control.h"

/*
 * OMAP_PRCM_MAX_NR_PENDING_REG: maximum number of PRM_IRQ*_MPU regs
 * XXX this is technically not needed, since
 * omap_prcm_रेजिस्टर_chain_handler() could allocate this based on the
 * actual amount of memory needed क्रम the SoC
 */
#घोषणा OMAP_PRCM_MAX_NR_PENDING_REG		2

/*
 * prcm_irq_chips: an array of all of the "generic IRQ chips" in use
 * by the PRCM पूर्णांकerrupt handler code.  There will be one 'chip' per
 * PRM_अणुIRQSTATUS,IRQENABLEपूर्ण_MPU रेजिस्टर pair.  (So OMAP3 will have
 * one "chip" and OMAP4 will have two.)
 */
अटल काष्ठा irq_chip_generic **prcm_irq_chips;

/*
 * prcm_irq_setup: the PRCM IRQ parameters क्रम the hardware the code
 * is currently running on.  Defined and passed by initialization code
 * that calls omap_prcm_रेजिस्टर_chain_handler().
 */
अटल काष्ठा omap_prcm_irq_setup *prcm_irq_setup;

/* prm_base: base भव address of the PRM IP block */
काष्ठा omap_करोमुख्य_base prm_base;

u16 prm_features;

/*
 * prm_ll_data: function poपूर्णांकers to SoC-specअगरic implementations of
 * common PRM functions
 */
अटल काष्ठा prm_ll_data null_prm_ll_data;
अटल काष्ठा prm_ll_data *prm_ll_data = &null_prm_ll_data;

/* Private functions */

/*
 * Move priority events from events to priority_events array
 */
अटल व्योम omap_prcm_events_filter_priority(अचिन्हित दीर्घ *events,
	अचिन्हित दीर्घ *priority_events)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < prcm_irq_setup->nr_regs; i++) अणु
		priority_events[i] =
			events[i] & prcm_irq_setup->priority_mask[i];
		events[i] ^= priority_events[i];
	पूर्ण
पूर्ण

/*
 * PRCM Interrupt Handler
 *
 * This is a common handler क्रम the OMAP PRCM पूर्णांकerrupts. Pending
 * पूर्णांकerrupts are detected by a call to prcm_pending_events and
 * dispatched accordingly. Clearing of the wakeup events should be
 * करोne by the SoC specअगरic inभागidual handlers.
 */
अटल व्योम omap_prcm_irq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित दीर्घ pending[OMAP_PRCM_MAX_NR_PENDING_REG];
	अचिन्हित दीर्घ priority_pending[OMAP_PRCM_MAX_NR_PENDING_REG];
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक virtirq;
	पूर्णांक nr_irq = prcm_irq_setup->nr_regs * 32;

	/*
	 * If we are suspended, mask all पूर्णांकerrupts from PRCM level,
	 * this करोes not ack them, and they will be pending until we
	 * re-enable the पूर्णांकerrupts, at which poपूर्णांक the
	 * omap_prcm_irq_handler will be executed again.  The
	 * _save_and_clear_irqen() function must ensure that the PRM
	 * ग_लिखो to disable all IRQs has reached the PRM beक्रमe
	 * वापसing, or spurious PRCM पूर्णांकerrupts may occur during
	 * suspend.
	 */
	अगर (prcm_irq_setup->suspended) अणु
		prcm_irq_setup->save_and_clear_irqen(prcm_irq_setup->saved_mask);
		prcm_irq_setup->suspend_save_flag = true;
	पूर्ण

	/*
	 * Loop until all pending irqs are handled, since
	 * generic_handle_irq() can cause new irqs to come
	 */
	जबतक (!prcm_irq_setup->suspended) अणु
		prcm_irq_setup->पढ़ो_pending_irqs(pending);

		/* No bit set, then all IRQs are handled */
		अगर (find_first_bit(pending, nr_irq) >= nr_irq)
			अवरोध;

		omap_prcm_events_filter_priority(pending, priority_pending);

		/*
		 * Loop on all currently pending irqs so that new irqs
		 * cannot starve previously pending irqs
		 */

		/* Serve priority events first */
		क्रम_each_set_bit(virtirq, priority_pending, nr_irq)
			generic_handle_irq(prcm_irq_setup->base_irq + virtirq);

		/* Serve normal events next */
		क्रम_each_set_bit(virtirq, pending, nr_irq)
			generic_handle_irq(prcm_irq_setup->base_irq + virtirq);
	पूर्ण
	अगर (chip->irq_ack)
		chip->irq_ack(&desc->irq_data);
	अगर (chip->irq_eoi)
		chip->irq_eoi(&desc->irq_data);
	chip->irq_unmask(&desc->irq_data);

	prcm_irq_setup->ocp_barrier(); /* aव्योम spurious IRQs */
पूर्ण

/* Public functions */

/**
 * omap_prcm_event_to_irq - given a PRCM event name, वापसs the
 * corresponding IRQ on which the handler should be रेजिस्टरed
 * @name: name of the PRCM पूर्णांकerrupt bit to look up - see काष्ठा omap_prcm_irq
 *
 * Returns the Linux पूर्णांकernal IRQ ID corresponding to @name upon success,
 * or -ENOENT upon failure.
 */
पूर्णांक omap_prcm_event_to_irq(स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	अगर (!prcm_irq_setup || !name)
		वापस -ENOENT;

	क्रम (i = 0; i < prcm_irq_setup->nr_irqs; i++)
		अगर (!म_भेद(prcm_irq_setup->irqs[i].name, name))
			वापस prcm_irq_setup->base_irq +
				prcm_irq_setup->irqs[i].offset;

	वापस -ENOENT;
पूर्ण

/**
 * omap_prcm_irq_cleanup - reverses memory allocated and other steps
 * करोne by omap_prcm_रेजिस्टर_chain_handler()
 *
 * No वापस value.
 */
व्योम omap_prcm_irq_cleanup(व्योम)
अणु
	अचिन्हित पूर्णांक irq;
	पूर्णांक i;

	अगर (!prcm_irq_setup) अणु
		pr_err("PRCM: IRQ handler not initialized; cannot cleanup\n");
		वापस;
	पूर्ण

	अगर (prcm_irq_chips) अणु
		क्रम (i = 0; i < prcm_irq_setup->nr_regs; i++) अणु
			अगर (prcm_irq_chips[i])
				irq_हटाओ_generic_chip(prcm_irq_chips[i],
					0xffffffff, 0, 0);
			prcm_irq_chips[i] = शून्य;
		पूर्ण
		kमुक्त(prcm_irq_chips);
		prcm_irq_chips = शून्य;
	पूर्ण

	kमुक्त(prcm_irq_setup->saved_mask);
	prcm_irq_setup->saved_mask = शून्य;

	kमुक्त(prcm_irq_setup->priority_mask);
	prcm_irq_setup->priority_mask = शून्य;

	irq = prcm_irq_setup->irq;
	irq_set_chained_handler(irq, शून्य);

	अगर (prcm_irq_setup->base_irq > 0)
		irq_मुक्त_descs(prcm_irq_setup->base_irq,
			prcm_irq_setup->nr_regs * 32);
	prcm_irq_setup->base_irq = 0;
पूर्ण

व्योम omap_prcm_irq_prepare(व्योम)
अणु
	prcm_irq_setup->suspended = true;
पूर्ण

व्योम omap_prcm_irq_complete(व्योम)
अणु
	prcm_irq_setup->suspended = false;

	/* If we have not saved the masks, करो not attempt to restore */
	अगर (!prcm_irq_setup->suspend_save_flag)
		वापस;

	prcm_irq_setup->suspend_save_flag = false;

	/*
	 * Re-enable all masked PRCM irq sources, this causes the PRCM
	 * पूर्णांकerrupt to fire immediately अगर the events were masked
	 * previously in the chain handler
	 */
	prcm_irq_setup->restore_irqen(prcm_irq_setup->saved_mask);
पूर्ण

/**
 * omap_prcm_रेजिस्टर_chain_handler - initializes the prcm chained पूर्णांकerrupt
 * handler based on provided parameters
 * @irq_setup: hardware data about the underlying PRM/PRCM
 *
 * Set up the PRCM chained पूर्णांकerrupt handler on the PRCM IRQ.  Sets up
 * one generic IRQ chip per PRM पूर्णांकerrupt status/enable रेजिस्टर pair.
 * Returns 0 upon success, -EINVAL अगर called twice or अगर invalid
 * arguments are passed, or -ENOMEM on any other error.
 */
पूर्णांक omap_prcm_रेजिस्टर_chain_handler(काष्ठा omap_prcm_irq_setup *irq_setup)
अणु
	पूर्णांक nr_regs;
	u32 mask[OMAP_PRCM_MAX_NR_PENDING_REG];
	पूर्णांक offset, i, irq;
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;

	अगर (!irq_setup)
		वापस -EINVAL;

	nr_regs = irq_setup->nr_regs;

	अगर (prcm_irq_setup) अणु
		pr_err("PRCM: already initialized; won't reinitialize\n");
		वापस -EINVAL;
	पूर्ण

	अगर (nr_regs > OMAP_PRCM_MAX_NR_PENDING_REG) अणु
		pr_err("PRCM: nr_regs too large\n");
		वापस -EINVAL;
	पूर्ण

	prcm_irq_setup = irq_setup;

	prcm_irq_chips = kसुस्मृति(nr_regs, माप(व्योम *), GFP_KERNEL);
	prcm_irq_setup->saved_mask = kसुस्मृति(nr_regs, माप(u32),
					     GFP_KERNEL);
	prcm_irq_setup->priority_mask = kसुस्मृति(nr_regs, माप(u32),
						GFP_KERNEL);

	अगर (!prcm_irq_chips || !prcm_irq_setup->saved_mask ||
	    !prcm_irq_setup->priority_mask)
		जाओ err;

	स_रखो(mask, 0, माप(mask));

	क्रम (i = 0; i < irq_setup->nr_irqs; i++) अणु
		offset = irq_setup->irqs[i].offset;
		mask[offset >> 5] |= 1 << (offset & 0x1f);
		अगर (irq_setup->irqs[i].priority)
			irq_setup->priority_mask[offset >> 5] |=
				1 << (offset & 0x1f);
	पूर्ण

	irq = irq_setup->irq;
	irq_set_chained_handler(irq, omap_prcm_irq_handler);

	irq_setup->base_irq = irq_alloc_descs(-1, 0, irq_setup->nr_regs * 32,
		0);

	अगर (irq_setup->base_irq < 0) अणु
		pr_err("PRCM: failed to allocate irq descs: %d\n",
			irq_setup->base_irq);
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < irq_setup->nr_regs; i++) अणु
		gc = irq_alloc_generic_chip("PRCM", 1,
			irq_setup->base_irq + i * 32, prm_base.va,
			handle_level_irq);

		अगर (!gc) अणु
			pr_err("PRCM: failed to allocate generic chip\n");
			जाओ err;
		पूर्ण
		ct = gc->chip_types;
		ct->chip.irq_ack = irq_gc_ack_set_bit;
		ct->chip.irq_mask = irq_gc_mask_clr_bit;
		ct->chip.irq_unmask = irq_gc_mask_set_bit;

		ct->regs.ack = irq_setup->ack + i * 4;
		ct->regs.mask = irq_setup->mask + i * 4;

		irq_setup_generic_chip(gc, mask[i], 0, IRQ_NOREQUEST, 0);
		prcm_irq_chips[i] = gc;
	पूर्ण

	irq = omap_prcm_event_to_irq("io");
	omap_pcs_legacy_init(irq, irq_setup->reconfigure_io_chain);

	वापस 0;

err:
	omap_prcm_irq_cleanup();
	वापस -ENOMEM;
पूर्ण

/**
 * omap2_set_globals_prm - set the PRM base address (क्रम early use)
 * @prm: PRM base भव address
 *
 * XXX Will be replaced when the PRM/CM drivers are completed.
 */
व्योम __init omap2_set_globals_prm(व्योम __iomem *prm)
अणु
	prm_base.va = prm;
पूर्ण

/**
 * prm_पढ़ो_reset_sources - वापस the sources of the SoC's last reset
 *
 * Return a u32 biपंचांगask representing the reset sources that caused the
 * SoC to reset.  The low-level per-SoC functions called by this
 * function remap the SoC-specअगरic reset source bits पूर्णांकo an
 * OMAP-common set of reset source bits, defined in
 * arch/arm/mach-omap2/prm.h.  Returns the standardized reset source
 * u32 biपंचांगask from the hardware upon success, or वापसs (1 <<
 * OMAP_UNKNOWN_RST_SRC_ID_SHIFT) अगर no low-level पढ़ो_reset_sources()
 * function was रेजिस्टरed.
 */
u32 prm_पढ़ो_reset_sources(व्योम)
अणु
	u32 ret = 1 << OMAP_UNKNOWN_RST_SRC_ID_SHIFT;

	अगर (prm_ll_data->पढ़ो_reset_sources)
		ret = prm_ll_data->पढ़ो_reset_sources();
	अन्यथा
		WARN_ONCE(1, "prm: %s: no mapping function defined for reset sources\n", __func__);

	वापस ret;
पूर्ण

/**
 * prm_was_any_context_lost_old - was device context lost? (old API)
 * @part: PRM partition ID (e.g., OMAP4430_PRM_PARTITION)
 * @inst: PRM instance offset (e.g., OMAP4430_PRM_MPU_INST)
 * @idx: CONTEXT रेजिस्टर offset
 *
 * Return 1 अगर any bits were set in the *_CONTEXT_* रेजिस्टर
 * identअगरied by (@part, @inst, @idx), which means that some context
 * was lost क्रम that module; otherwise, वापस 0.  XXX Deprecated;
 * callers need to use a less-SoC-dependent way to identअगरy hardware
 * IP blocks.
 */
bool prm_was_any_context_lost_old(u8 part, s16 inst, u16 idx)
अणु
	bool ret = true;

	अगर (prm_ll_data->was_any_context_lost_old)
		ret = prm_ll_data->was_any_context_lost_old(part, inst, idx);
	अन्यथा
		WARN_ONCE(1, "prm: %s: no mapping function defined\n",
			  __func__);

	वापस ret;
पूर्ण

/**
 * prm_clear_context_lost_flags_old - clear context loss flags (old API)
 * @part: PRM partition ID (e.g., OMAP4430_PRM_PARTITION)
 * @inst: PRM instance offset (e.g., OMAP4430_PRM_MPU_INST)
 * @idx: CONTEXT रेजिस्टर offset
 *
 * Clear hardware context loss bits क्रम the module identअगरied by
 * (@part, @inst, @idx).  No वापस value.  XXX Deprecated; callers
 * need to use a less-SoC-dependent way to identअगरy hardware IP
 * blocks.
 */
व्योम prm_clear_context_loss_flags_old(u8 part, s16 inst, u16 idx)
अणु
	अगर (prm_ll_data->clear_context_loss_flags_old)
		prm_ll_data->clear_context_loss_flags_old(part, inst, idx);
	अन्यथा
		WARN_ONCE(1, "prm: %s: no mapping function defined\n",
			  __func__);
पूर्ण

/**
 * omap_prm_निश्चित_hardreset - निश्चित hardreset क्रम an IP block
 * @shअगरt: रेजिस्टर bit shअगरt corresponding to the reset line
 * @part: PRM partition
 * @prm_mod: PRM submodule base or instance offset
 * @offset: रेजिस्टर offset
 *
 * Asserts a hardware reset line क्रम an IP block.
 */
पूर्णांक omap_prm_निश्चित_hardreset(u8 shअगरt, u8 part, s16 prm_mod, u16 offset)
अणु
	अगर (!prm_ll_data->निश्चित_hardreset) अणु
		WARN_ONCE(1, "prm: %s: no mapping function defined\n",
			  __func__);
		वापस -EINVAL;
	पूर्ण

	वापस prm_ll_data->निश्चित_hardreset(shअगरt, part, prm_mod, offset);
पूर्ण

/**
 * omap_prm_deनिश्चित_hardreset - deनिश्चित hardreset क्रम an IP block
 * @shअगरt: रेजिस्टर bit shअगरt corresponding to the reset line
 * @st_shअगरt: reset status bit shअगरt corresponding to the reset line
 * @part: PRM partition
 * @prm_mod: PRM submodule base or instance offset
 * @offset: रेजिस्टर offset
 * @st_offset: status रेजिस्टर offset
 *
 * Deनिश्चितs a hardware reset line क्रम an IP block.
 */
पूर्णांक omap_prm_deनिश्चित_hardreset(u8 shअगरt, u8 st_shअगरt, u8 part, s16 prm_mod,
				u16 offset, u16 st_offset)
अणु
	अगर (!prm_ll_data->deनिश्चित_hardreset) अणु
		WARN_ONCE(1, "prm: %s: no mapping function defined\n",
			  __func__);
		वापस -EINVAL;
	पूर्ण

	वापस prm_ll_data->deनिश्चित_hardreset(shअगरt, st_shअगरt, part, prm_mod,
					       offset, st_offset);
पूर्ण

/**
 * omap_prm_is_hardreset_निश्चितed - check the hardreset status क्रम an IP block
 * @shअगरt: रेजिस्टर bit shअगरt corresponding to the reset line
 * @part: PRM partition
 * @prm_mod: PRM submodule base or instance offset
 * @offset: रेजिस्टर offset
 *
 * Checks अगर a hardware reset line क्रम an IP block is enabled or not.
 */
पूर्णांक omap_prm_is_hardreset_निश्चितed(u8 shअगरt, u8 part, s16 prm_mod, u16 offset)
अणु
	अगर (!prm_ll_data->is_hardreset_निश्चितed) अणु
		WARN_ONCE(1, "prm: %s: no mapping function defined\n",
			  __func__);
		वापस -EINVAL;
	पूर्ण

	वापस prm_ll_data->is_hardreset_निश्चितed(shअगरt, part, prm_mod, offset);
पूर्ण

/**
 * omap_prm_reconfigure_io_chain - clear latches and reconfigure I/O chain
 *
 * Clear any previously-latched I/O wakeup events and ensure that the
 * I/O wakeup gates are aligned with the current mux settings.
 * Calls SoC specअगरic I/O chain reconfigure function अगर available,
 * otherwise करोes nothing.
 */
व्योम omap_prm_reconfigure_io_chain(व्योम)
अणु
	अगर (!prcm_irq_setup || !prcm_irq_setup->reconfigure_io_chain)
		वापस;

	prcm_irq_setup->reconfigure_io_chain();
पूर्ण

/**
 * omap_prm_reset_प्रणाली - trigger global SW reset
 *
 * Triggers SoC specअगरic global warm reset to reboot the device.
 */
व्योम omap_prm_reset_प्रणाली(व्योम)
अणु
	अगर (!prm_ll_data->reset_प्रणाली) अणु
		WARN_ONCE(1, "prm: %s: no mapping function defined\n",
			  __func__);
		वापस;
	पूर्ण

	prm_ll_data->reset_प्रणाली();

	जबतक (1) अणु
		cpu_relax();
		wfe();
	पूर्ण
पूर्ण

/**
 * omap_prm_clear_mod_irqs - clear wake-up events from PRCM पूर्णांकerrupt
 * @module: PRM module to clear wakeups from
 * @regs: रेजिस्टर to clear
 * @wkst_mask: wkst bits to clear
 *
 * Clears any wakeup events क्रम the module and रेजिस्टर set defined.
 * Uses SoC specअगरic implementation to करो the actual wakeup status
 * clearing.
 */
पूर्णांक omap_prm_clear_mod_irqs(s16 module, u8 regs, u32 wkst_mask)
अणु
	अगर (!prm_ll_data->clear_mod_irqs) अणु
		WARN_ONCE(1, "prm: %s: no mapping function defined\n",
			  __func__);
		वापस -EINVAL;
	पूर्ण

	वापस prm_ll_data->clear_mod_irqs(module, regs, wkst_mask);
पूर्ण

/**
 * omap_prm_vp_check_txकरोne - check voltage processor TX करोne status
 *
 * Checks अगर voltage processor transmission has been completed.
 * Returns non-zero अगर a transmission has completed, 0 otherwise.
 */
u32 omap_prm_vp_check_txकरोne(u8 vp_id)
अणु
	अगर (!prm_ll_data->vp_check_txकरोne) अणु
		WARN_ONCE(1, "prm: %s: no mapping function defined\n",
			  __func__);
		वापस 0;
	पूर्ण

	वापस prm_ll_data->vp_check_txकरोne(vp_id);
पूर्ण

/**
 * omap_prm_vp_clear_txकरोne - clears voltage processor TX करोne status
 *
 * Clears the status bit क्रम completed voltage processor transmission
 * वापसed by prm_vp_check_txकरोne.
 */
व्योम omap_prm_vp_clear_txकरोne(u8 vp_id)
अणु
	अगर (!prm_ll_data->vp_clear_txकरोne) अणु
		WARN_ONCE(1, "prm: %s: no mapping function defined\n",
			  __func__);
		वापस;
	पूर्ण

	prm_ll_data->vp_clear_txकरोne(vp_id);
पूर्ण

/**
 * prm_रेजिस्टर - रेजिस्टर per-SoC low-level data with the PRM
 * @pld: low-level per-SoC OMAP PRM data & function poपूर्णांकers to रेजिस्टर
 *
 * Register per-SoC low-level OMAP PRM data and function poपूर्णांकers with
 * the OMAP PRM common पूर्णांकerface.  The caller must keep the data
 * poपूर्णांकed to by @pld valid until it calls prm_unरेजिस्टर() and
 * it वापसs successfully.  Returns 0 upon success, -EINVAL अगर @pld
 * is शून्य, or -EEXIST अगर prm_रेजिस्टर() has alपढ़ोy been called
 * without an पूर्णांकervening prm_unरेजिस्टर().
 */
पूर्णांक prm_रेजिस्टर(काष्ठा prm_ll_data *pld)
अणु
	अगर (!pld)
		वापस -EINVAL;

	अगर (prm_ll_data != &null_prm_ll_data)
		वापस -EEXIST;

	prm_ll_data = pld;

	वापस 0;
पूर्ण

/**
 * prm_unरेजिस्टर - unरेजिस्टर per-SoC low-level data & function poपूर्णांकers
 * @pld: low-level per-SoC OMAP PRM data & function poपूर्णांकers to unरेजिस्टर
 *
 * Unरेजिस्टर per-SoC low-level OMAP PRM data and function poपूर्णांकers
 * that were previously रेजिस्टरed with prm_रेजिस्टर().  The
 * caller may not destroy any of the data poपूर्णांकed to by @pld until
 * this function वापसs successfully.  Returns 0 upon success, or
 * -EINVAL अगर @pld is शून्य or अगर @pld करोes not match the काष्ठा
 * prm_ll_data * previously रेजिस्टरed by prm_रेजिस्टर().
 */
पूर्णांक prm_unरेजिस्टर(काष्ठा prm_ll_data *pld)
अणु
	अगर (!pld || prm_ll_data != pld)
		वापस -EINVAL;

	prm_ll_data = &null_prm_ll_data;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ARCH_OMAP2
अटल काष्ठा omap_prcm_init_data omap2_prm_data __initdata = अणु
	.index = TI_CLKM_PRM,
	.init = omap2xxx_prm_init,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP3
अटल काष्ठा omap_prcm_init_data omap3_prm_data __initdata = अणु
	.index = TI_CLKM_PRM,
	.init = omap3xxx_prm_init,

	/*
	 * IVA2 offset is a negative value, must offset the prm_base
	 * address by this to get it to positive
	 */
	.offset = -OMAP3430_IVA2_MOD,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_SOC_AM33XX) || defined(CONFIG_SOC_TI81XX)
अटल काष्ठा omap_prcm_init_data am3_prm_data __initdata = अणु
	.index = TI_CLKM_PRM,
	.init = am33xx_prm_init,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_TI81XX
अटल काष्ठा omap_prcm_init_data dm814_pllss_data __initdata = अणु
	.index = TI_CLKM_PLLSS,
	.init = am33xx_prm_init,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP4
अटल काष्ठा omap_prcm_init_data omap4_prm_data __initdata = अणु
	.index = TI_CLKM_PRM,
	.init = omap44xx_prm_init,
	.device_inst_offset = OMAP4430_PRM_DEVICE_INST,
	.flags = PRM_HAS_IO_WAKEUP | PRM_HAS_VOLTAGE,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_OMAP5
अटल काष्ठा omap_prcm_init_data omap5_prm_data __initdata = अणु
	.index = TI_CLKM_PRM,
	.init = omap44xx_prm_init,
	.device_inst_offset = OMAP54XX_PRM_DEVICE_INST,
	.flags = PRM_HAS_IO_WAKEUP | PRM_HAS_VOLTAGE,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_DRA7XX
अटल काष्ठा omap_prcm_init_data dra7_prm_data __initdata = अणु
	.index = TI_CLKM_PRM,
	.init = omap44xx_prm_init,
	.device_inst_offset = DRA7XX_PRM_DEVICE_INST,
	.flags = PRM_HAS_IO_WAKEUP,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_AM43XX
अटल काष्ठा omap_prcm_init_data am4_prm_data __initdata = अणु
	.index = TI_CLKM_PRM,
	.init = omap44xx_prm_init,
	.device_inst_offset = AM43XX_PRM_DEVICE_INST,
	.flags = PRM_HAS_IO_WAKEUP,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_OMAP4) || defined(CONFIG_SOC_OMAP5)
अटल काष्ठा omap_prcm_init_data scrm_data __initdata = अणु
	.index = TI_CLKM_SCRM,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id omap_prcm_dt_match_table[] __initस्थिर = अणु
#अगर_घोषित CONFIG_SOC_AM33XX
	अणु .compatible = "ti,am3-prcm", .data = &am3_prm_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_AM43XX
	अणु .compatible = "ti,am4-prcm", .data = &am4_prm_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_TI81XX
	अणु .compatible = "ti,dm814-prcm", .data = &am3_prm_data पूर्ण,
	अणु .compatible = "ti,dm814-pllss", .data = &dm814_pllss_data पूर्ण,
	अणु .compatible = "ti,dm816-prcm", .data = &am3_prm_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_OMAP2
	अणु .compatible = "ti,omap2-prcm", .data = &omap2_prm_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_OMAP3
	अणु .compatible = "ti,omap3-prm", .data = &omap3_prm_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_OMAP4
	अणु .compatible = "ti,omap4-prm", .data = &omap4_prm_data पूर्ण,
	अणु .compatible = "ti,omap4-scrm", .data = &scrm_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_OMAP5
	अणु .compatible = "ti,omap5-prm", .data = &omap5_prm_data पूर्ण,
	अणु .compatible = "ti,omap5-scrm", .data = &scrm_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_DRA7XX
	अणु .compatible = "ti,dra7-prm", .data = &dra7_prm_data पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

/**
 * omap2_prm_base_init - initialize iomappings क्रम the PRM driver
 *
 * Detects and initializes the iomappings क्रम the PRM driver, based
 * on the DT data. Returns 0 in success, negative error value
 * otherwise.
 */
पूर्णांक __init omap2_prm_base_init(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा omap_prcm_init_data *data;
	काष्ठा resource res;
	पूर्णांक ret;

	क्रम_each_matching_node_and_match(np, omap_prcm_dt_match_table, &match) अणु
		data = (काष्ठा omap_prcm_init_data *)match->data;

		ret = of_address_to_resource(np, 0, &res);
		अगर (ret)
			वापस ret;

		data->mem = ioremap(res.start, resource_size(&res));

		अगर (data->index == TI_CLKM_PRM) अणु
			prm_base.va = data->mem + data->offset;
			prm_base.pa = res.start + data->offset;
		पूर्ण

		data->np = np;

		अगर (data->init)
			data->init(data);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __init omap2_prcm_base_init(व्योम)
अणु
	पूर्णांक ret;

	ret = omap2_prm_base_init();
	अगर (ret)
		वापस ret;

	वापस omap2_cm_base_init();
पूर्ण

/**
 * omap_prcm_init - low level init क्रम the PRCM drivers
 *
 * Initializes the low level घड़ी infraकाष्ठाure क्रम PRCM drivers.
 * Returns 0 in success, negative error value in failure.
 */
पूर्णांक __init omap_prcm_init(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा omap_prcm_init_data *data;
	पूर्णांक ret;

	क्रम_each_matching_node_and_match(np, omap_prcm_dt_match_table, &match) अणु
		data = match->data;

		ret = omap2_clk_provider_init(np, data->index, शून्य, data->mem);
		अगर (ret)
			वापस ret;
	पूर्ण

	omap_cm_init();

	वापस 0;
पूर्ण

अटल पूर्णांक __init prm_late_init(व्योम)
अणु
	अगर (prm_ll_data->late_init)
		वापस prm_ll_data->late_init();
	वापस 0;
पूर्ण
subsys_initcall(prm_late_init);
