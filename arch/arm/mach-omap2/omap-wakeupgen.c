<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP WakeupGen Source file
 *
 * OMAP WakeupGen is the पूर्णांकerrupt controller extension used aदीर्घ
 * with ARM GIC to wake the CPU out from low घातer states on
 * बाह्यal पूर्णांकerrupts. It is responsible क्रम generating wakeup
 * event from the incoming पूर्णांकerrupts and enable bits. It is
 * implemented in MPU always ON घातer करोमुख्य. During normal operation,
 * WakeupGen delivers बाह्यal पूर्णांकerrupts directly to the GIC.
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 *	Santosh Shilimkar <santosh.shilimkar@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/cpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/cpu_pm.h>

#समावेश "omap-wakeupgen.h"
#समावेश "omap-secure.h"

#समावेश "soc.h"
#समावेश "omap4-sar-layout.h"
#समावेश "common.h"
#समावेश "pm.h"

#घोषणा AM43XX_NR_REG_BANKS	7
#घोषणा AM43XX_IRQS		224
#घोषणा MAX_NR_REG_BANKS	AM43XX_NR_REG_BANKS
#घोषणा MAX_IRQS		AM43XX_IRQS
#घोषणा DEFAULT_NR_REG_BANKS	5
#घोषणा DEFAULT_IRQS		160
#घोषणा WKG_MASK_ALL		0x00000000
#घोषणा WKG_UNMASK_ALL		0xffffffff
#घोषणा CPU_ENA_OFFSET		0x400
#घोषणा CPU0_ID			0x0
#घोषणा CPU1_ID			0x1
#घोषणा OMAP4_NR_BANKS		4
#घोषणा OMAP4_NR_IRQS		128

#घोषणा SYS_NIRQ1_EXT_SYS_IRQ_1	7
#घोषणा SYS_NIRQ2_EXT_SYS_IRQ_2	119

अटल व्योम __iomem *wakeupgen_base;
अटल व्योम __iomem *sar_base;
अटल DEFINE_RAW_SPINLOCK(wakeupgen_lock);
अटल अचिन्हित पूर्णांक irq_target_cpu[MAX_IRQS];
अटल अचिन्हित पूर्णांक irq_banks = DEFAULT_NR_REG_BANKS;
अटल अचिन्हित पूर्णांक max_irqs = DEFAULT_IRQS;
अटल अचिन्हित पूर्णांक omap_secure_apis;

#अगर_घोषित CONFIG_CPU_PM
अटल अचिन्हित पूर्णांक wakeupgen_context[MAX_NR_REG_BANKS];
#पूर्ण_अगर

काष्ठा omap_wakeupgen_ops अणु
	व्योम (*save_context)(व्योम);
	व्योम (*restore_context)(व्योम);
पूर्ण;

अटल काष्ठा omap_wakeupgen_ops *wakeupgen_ops;

/*
 * Static helper functions.
 */
अटल अंतरभूत u32 wakeupgen_पढ़ोl(u8 idx, u32 cpu)
अणु
	वापस पढ़ोl_relaxed(wakeupgen_base + OMAP_WKG_ENB_A_0 +
				(cpu * CPU_ENA_OFFSET) + (idx * 4));
पूर्ण

अटल अंतरभूत व्योम wakeupgen_ग_लिखोl(u32 val, u8 idx, u32 cpu)
अणु
	ग_लिखोl_relaxed(val, wakeupgen_base + OMAP_WKG_ENB_A_0 +
				(cpu * CPU_ENA_OFFSET) + (idx * 4));
पूर्ण

अटल अंतरभूत व्योम sar_ग_लिखोl(u32 val, u32 offset, u8 idx)
अणु
	ग_लिखोl_relaxed(val, sar_base + offset + (idx * 4));
पूर्ण

अटल अंतरभूत पूर्णांक _wakeupgen_get_irq_info(u32 irq, u32 *bit_posn, u8 *reg_index)
अणु
	/*
	 * Each WakeupGen रेजिस्टर controls 32 पूर्णांकerrupt.
	 * i.e. 1 bit per SPI IRQ
	 */
	*reg_index = irq >> 5;
	*bit_posn = irq %= 32;

	वापस 0;
पूर्ण

अटल व्योम _wakeupgen_clear(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक cpu)
अणु
	u32 val, bit_number;
	u8 i;

	अगर (_wakeupgen_get_irq_info(irq, &bit_number, &i))
		वापस;

	val = wakeupgen_पढ़ोl(i, cpu);
	val &= ~BIT(bit_number);
	wakeupgen_ग_लिखोl(val, i, cpu);
पूर्ण

अटल व्योम _wakeupgen_set(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक cpu)
अणु
	u32 val, bit_number;
	u8 i;

	अगर (_wakeupgen_get_irq_info(irq, &bit_number, &i))
		वापस;

	val = wakeupgen_पढ़ोl(i, cpu);
	val |= BIT(bit_number);
	wakeupgen_ग_लिखोl(val, i, cpu);
पूर्ण

/*
 * Architecture specअगरic Mask extension
 */
अटल व्योम wakeupgen_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&wakeupgen_lock, flags);
	_wakeupgen_clear(d->hwirq, irq_target_cpu[d->hwirq]);
	raw_spin_unlock_irqrestore(&wakeupgen_lock, flags);
	irq_chip_mask_parent(d);
पूर्ण

/*
 * Architecture specअगरic Unmask extension
 */
अटल व्योम wakeupgen_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&wakeupgen_lock, flags);
	_wakeupgen_set(d->hwirq, irq_target_cpu[d->hwirq]);
	raw_spin_unlock_irqrestore(&wakeupgen_lock, flags);
	irq_chip_unmask_parent(d);
पूर्ण

/*
 * The sys_nirq pins bypass peripheral modules and are wired directly
 * to MPUSS wakeupgen. They get स्वतःmatically inverted क्रम GIC.
 */
अटल पूर्णांक wakeupgen_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	bool inverted = false;

	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_LOW:
		type &= ~IRQ_TYPE_LEVEL_MASK;
		type |= IRQ_TYPE_LEVEL_HIGH;
		inverted = true;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		type &= ~IRQ_TYPE_EDGE_BOTH;
		type |= IRQ_TYPE_EDGE_RISING;
		inverted = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (inverted && d->hwirq != SYS_NIRQ1_EXT_SYS_IRQ_1 &&
	    d->hwirq != SYS_NIRQ2_EXT_SYS_IRQ_2)
		pr_warn("wakeupgen: irq%li polarity inverted in dts\n",
			d->hwirq);

	वापस irq_chip_set_type_parent(d, type);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल DEFINE_PER_CPU(u32 [MAX_NR_REG_BANKS], irqmasks);

अटल व्योम _wakeupgen_save_masks(अचिन्हित पूर्णांक cpu)
अणु
	u8 i;

	क्रम (i = 0; i < irq_banks; i++)
		per_cpu(irqmasks, cpu)[i] = wakeupgen_पढ़ोl(i, cpu);
पूर्ण

अटल व्योम _wakeupgen_restore_masks(अचिन्हित पूर्णांक cpu)
अणु
	u8 i;

	क्रम (i = 0; i < irq_banks; i++)
		wakeupgen_ग_लिखोl(per_cpu(irqmasks, cpu)[i], i, cpu);
पूर्ण

अटल व्योम _wakeupgen_set_all(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक reg)
अणु
	u8 i;

	क्रम (i = 0; i < irq_banks; i++)
		wakeupgen_ग_लिखोl(reg, i, cpu);
पूर्ण

/*
 * Mask or unmask all पूर्णांकerrupts on given CPU.
 *	0 = Mask all पूर्णांकerrupts on the 'cpu'
 *	1 = Unmask all पूर्णांकerrupts on the 'cpu'
 * Ensure that the initial mask is मुख्यtained. This is faster than
 * iterating through GIC रेजिस्टरs to arrive at the correct masks.
 */
अटल व्योम wakeupgen_irqmask_all(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक set)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&wakeupgen_lock, flags);
	अगर (set) अणु
		_wakeupgen_save_masks(cpu);
		_wakeupgen_set_all(cpu, WKG_MASK_ALL);
	पूर्ण अन्यथा अणु
		_wakeupgen_set_all(cpu, WKG_UNMASK_ALL);
		_wakeupgen_restore_masks(cpu);
	पूर्ण
	raw_spin_unlock_irqrestore(&wakeupgen_lock, flags);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_PM
अटल अंतरभूत व्योम omap4_irq_save_context(व्योम)
अणु
	u32 i, val;

	अगर (omap_rev() == OMAP4430_REV_ES1_0)
		वापस;

	क्रम (i = 0; i < irq_banks; i++) अणु
		/* Save the CPUx पूर्णांकerrupt mask क्रम IRQ 0 to 127 */
		val = wakeupgen_पढ़ोl(i, 0);
		sar_ग_लिखोl(val, WAKEUPGENENB_OFFSET_CPU0, i);
		val = wakeupgen_पढ़ोl(i, 1);
		sar_ग_लिखोl(val, WAKEUPGENENB_OFFSET_CPU1, i);

		/*
		 * Disable the secure पूर्णांकerrupts क्रम CPUx. The restore
		 * code blindly restores secure and non-secure पूर्णांकerrupt
		 * masks from SAR RAM. Secure पूर्णांकerrupts are not suppose
		 * to be enabled from HLOS. So overग_लिखो the SAR location
		 * so that the secure पूर्णांकerrupt reमुख्यs disabled.
		 */
		sar_ग_लिखोl(0x0, WAKEUPGENENB_SECURE_OFFSET_CPU0, i);
		sar_ग_लिखोl(0x0, WAKEUPGENENB_SECURE_OFFSET_CPU1, i);
	पूर्ण

	/* Save AuxBoot* रेजिस्टरs */
	val = पढ़ोl_relaxed(wakeupgen_base + OMAP_AUX_CORE_BOOT_0);
	ग_लिखोl_relaxed(val, sar_base + AUXCOREBOOT0_OFFSET);
	val = पढ़ोl_relaxed(wakeupgen_base + OMAP_AUX_CORE_BOOT_1);
	ग_लिखोl_relaxed(val, sar_base + AUXCOREBOOT1_OFFSET);

	/* Save SyncReq generation logic */
	val = पढ़ोl_relaxed(wakeupgen_base + OMAP_PTMSYNCREQ_MASK);
	ग_लिखोl_relaxed(val, sar_base + PTMSYNCREQ_MASK_OFFSET);
	val = पढ़ोl_relaxed(wakeupgen_base + OMAP_PTMSYNCREQ_EN);
	ग_लिखोl_relaxed(val, sar_base + PTMSYNCREQ_EN_OFFSET);

	/* Set the Backup Bit Mask status */
	val = पढ़ोl_relaxed(sar_base + SAR_BACKUP_STATUS_OFFSET);
	val |= SAR_BACKUP_STATUS_WAKEUPGEN;
	ग_लिखोl_relaxed(val, sar_base + SAR_BACKUP_STATUS_OFFSET);

पूर्ण

अटल अंतरभूत व्योम omap5_irq_save_context(व्योम)
अणु
	u32 i, val;

	क्रम (i = 0; i < irq_banks; i++) अणु
		/* Save the CPUx पूर्णांकerrupt mask क्रम IRQ 0 to 159 */
		val = wakeupgen_पढ़ोl(i, 0);
		sar_ग_लिखोl(val, OMAP5_WAKEUPGENENB_OFFSET_CPU0, i);
		val = wakeupgen_पढ़ोl(i, 1);
		sar_ग_लिखोl(val, OMAP5_WAKEUPGENENB_OFFSET_CPU1, i);
		sar_ग_लिखोl(0x0, OMAP5_WAKEUPGENENB_SECURE_OFFSET_CPU0, i);
		sar_ग_लिखोl(0x0, OMAP5_WAKEUPGENENB_SECURE_OFFSET_CPU1, i);
	पूर्ण

	/* Save AuxBoot* रेजिस्टरs */
	val = पढ़ोl_relaxed(wakeupgen_base + OMAP_AUX_CORE_BOOT_0);
	ग_लिखोl_relaxed(val, sar_base + OMAP5_AUXCOREBOOT0_OFFSET);
	val = पढ़ोl_relaxed(wakeupgen_base + OMAP_AUX_CORE_BOOT_0);
	ग_लिखोl_relaxed(val, sar_base + OMAP5_AUXCOREBOOT1_OFFSET);

	/* Set the Backup Bit Mask status */
	val = पढ़ोl_relaxed(sar_base + OMAP5_SAR_BACKUP_STATUS_OFFSET);
	val |= SAR_BACKUP_STATUS_WAKEUPGEN;
	ग_लिखोl_relaxed(val, sar_base + OMAP5_SAR_BACKUP_STATUS_OFFSET);

पूर्ण

अटल अंतरभूत व्योम am43xx_irq_save_context(व्योम)
अणु
	u32 i;

	क्रम (i = 0; i < irq_banks; i++) अणु
		wakeupgen_context[i] = wakeupgen_पढ़ोl(i, 0);
		wakeupgen_ग_लिखोl(0, i, CPU0_ID);
	पूर्ण
पूर्ण

/*
 * Save WakeupGen पूर्णांकerrupt context in SAR BANK3. Restore is करोne by
 * ROM code. WakeupGen IP is पूर्णांकegrated aदीर्घ with GIC to manage the
 * पूर्णांकerrupt wakeups from CPU low घातer states. It manages
 * masking/unmasking of Shared peripheral पूर्णांकerrupts(SPI). So the
 * पूर्णांकerrupt enable/disable control should be in sync and consistent
 * at WakeupGen and GIC so that पूर्णांकerrupts are not lost.
 */
अटल व्योम irq_save_context(व्योम)
अणु
	/* DRA7 has no SAR to save */
	अगर (soc_is_dra7xx())
		वापस;

	अगर (wakeupgen_ops && wakeupgen_ops->save_context)
		wakeupgen_ops->save_context();
पूर्ण

/*
 * Clear WakeupGen SAR backup status.
 */
अटल व्योम irq_sar_clear(व्योम)
अणु
	u32 val;
	u32 offset = SAR_BACKUP_STATUS_OFFSET;
	/* DRA7 has no SAR to save */
	अगर (soc_is_dra7xx())
		वापस;

	अगर (soc_is_omap54xx())
		offset = OMAP5_SAR_BACKUP_STATUS_OFFSET;

	val = पढ़ोl_relaxed(sar_base + offset);
	val &= ~SAR_BACKUP_STATUS_WAKEUPGEN;
	ग_लिखोl_relaxed(val, sar_base + offset);
पूर्ण

अटल व्योम am43xx_irq_restore_context(व्योम)
अणु
	u32 i;

	क्रम (i = 0; i < irq_banks; i++)
		wakeupgen_ग_लिखोl(wakeupgen_context[i], i, CPU0_ID);
पूर्ण

अटल व्योम irq_restore_context(व्योम)
अणु
	अगर (wakeupgen_ops && wakeupgen_ops->restore_context)
		wakeupgen_ops->restore_context();
पूर्ण

/*
 * Save GIC and Wakeupgen पूर्णांकerrupt context using secure API
 * क्रम HS/EMU devices.
 */
अटल व्योम irq_save_secure_context(व्योम)
अणु
	u32 ret;
	ret = omap_secure_dispatcher(OMAP4_HAL_SAVEGIC_INDEX,
				FLAG_START_CRITICAL,
				0, 0, 0, 0, 0);
	अगर (ret != API_HAL_RET_VALUE_OK)
		pr_err("GIC and Wakeupgen context save failed\n");
पूर्ण

/* Define ops क्रम context save and restore क्रम each SoC */
अटल काष्ठा omap_wakeupgen_ops omap4_wakeupgen_ops = अणु
	.save_context = omap4_irq_save_context,
	.restore_context = irq_sar_clear,
पूर्ण;

अटल काष्ठा omap_wakeupgen_ops omap5_wakeupgen_ops = अणु
	.save_context = omap5_irq_save_context,
	.restore_context = irq_sar_clear,
पूर्ण;

अटल काष्ठा omap_wakeupgen_ops am43xx_wakeupgen_ops = अणु
	.save_context = am43xx_irq_save_context,
	.restore_context = am43xx_irq_restore_context,
पूर्ण;
#अन्यथा
अटल काष्ठा omap_wakeupgen_ops omap4_wakeupgen_ops = अणुपूर्ण;
अटल काष्ठा omap_wakeupgen_ops omap5_wakeupgen_ops = अणुपूर्ण;
अटल काष्ठा omap_wakeupgen_ops am43xx_wakeupgen_ops = अणुपूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल पूर्णांक omap_wakeupgen_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	wakeupgen_irqmask_all(cpu, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_wakeupgen_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	wakeupgen_irqmask_all(cpu, 1);
	वापस 0;
पूर्ण

अटल व्योम __init irq_hotplug_init(व्योम)
अणु
	cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN, "arm/omap-wake:online",
				  omap_wakeupgen_cpu_online, शून्य);
	cpuhp_setup_state_nocalls(CPUHP_ARM_OMAP_WAKE_DEAD,
				  "arm/omap-wake:dead", शून्य,
				  omap_wakeupgen_cpu_dead);
पूर्ण
#अन्यथा
अटल व्योम __init irq_hotplug_init(व्योम)
अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_PM
अटल पूर्णांक irq_notअगरier(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd,	व्योम *v)
अणु
	चयन (cmd) अणु
	हाल CPU_CLUSTER_PM_ENTER:
		अगर (omap_type() == OMAP2_DEVICE_TYPE_GP || soc_is_am43xx())
			irq_save_context();
		अन्यथा
			irq_save_secure_context();
		अवरोध;
	हाल CPU_CLUSTER_PM_EXIT:
		अगर (omap_type() == OMAP2_DEVICE_TYPE_GP || soc_is_am43xx())
			irq_restore_context();
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block irq_notअगरier_block = अणु
	.notअगरier_call = irq_notअगरier,
पूर्ण;

अटल व्योम __init irq_pm_init(व्योम)
अणु
	/* FIXME: Remove this when MPU OSWR support is added */
	अगर (!IS_PM44XX_ERRATUM(PM_OMAP4_CPU_OSWR_DISABLE))
		cpu_pm_रेजिस्टर_notअगरier(&irq_notअगरier_block);
पूर्ण
#अन्यथा
अटल व्योम __init irq_pm_init(व्योम)
अणुपूर्ण
#पूर्ण_अगर

व्योम __iomem *omap_get_wakeupgen_base(व्योम)
अणु
	वापस wakeupgen_base;
पूर्ण

पूर्णांक omap_secure_apis_support(व्योम)
अणु
	वापस omap_secure_apis;
पूर्ण

अटल काष्ठा irq_chip wakeupgen_chip = अणु
	.name			= "WUGEN",
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_mask		= wakeupgen_mask,
	.irq_unmask		= wakeupgen_unmask,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_set_type		= wakeupgen_irq_set_type,
	.flags			= IRQCHIP_SKIP_SET_WAKE | IRQCHIP_MASK_ON_SUSPEND,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity	= irq_chip_set_affinity_parent,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक wakeupgen_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
				      काष्ठा irq_fwspec *fwspec,
				      अचिन्हित दीर्घ *hwirq,
				      अचिन्हित पूर्णांक *type)
अणु
	अगर (is_of_node(fwspec->fwnode)) अणु
		अगर (fwspec->param_count != 3)
			वापस -EINVAL;

		/* No PPI should poपूर्णांक to this करोमुख्य */
		अगर (fwspec->param[0] != 0)
			वापस -EINVAL;

		*hwirq = fwspec->param[1];
		*type = fwspec->param[2];
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wakeupgen_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				  अचिन्हित पूर्णांक virq,
				  अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	काष्ठा irq_fwspec *fwspec = data;
	काष्ठा irq_fwspec parent_fwspec;
	irq_hw_number_t hwirq;
	पूर्णांक i;

	अगर (fwspec->param_count != 3)
		वापस -EINVAL;	/* Not GIC compliant */
	अगर (fwspec->param[0] != 0)
		वापस -EINVAL;	/* No PPI should poपूर्णांक to this करोमुख्य */

	hwirq = fwspec->param[1];
	अगर (hwirq >= MAX_IRQS)
		वापस -EINVAL;	/* Can't deal with this */

	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i, hwirq + i,
					      &wakeupgen_chip, शून्य);

	parent_fwspec = *fwspec;
	parent_fwspec.fwnode = करोमुख्य->parent->fwnode;
	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs,
					    &parent_fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops wakeupgen_करोमुख्य_ops = अणु
	.translate	= wakeupgen_करोमुख्य_translate,
	.alloc		= wakeupgen_करोमुख्य_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

/*
 * Initialise the wakeupgen module.
 */
अटल पूर्णांक __init wakeupgen_init(काष्ठा device_node *node,
				 काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *parent_करोमुख्य, *करोमुख्य;
	पूर्णांक i;
	अचिन्हित पूर्णांक boot_cpu = smp_processor_id();
	u32 val;

	अगर (!parent) अणु
		pr_err("%pOF: no parent, giving up\n", node);
		वापस -ENODEV;
	पूर्ण

	parent_करोमुख्य = irq_find_host(parent);
	अगर (!parent_करोमुख्य) अणु
		pr_err("%pOF: unable to obtain parent domain\n", node);
		वापस -ENXIO;
	पूर्ण
	/* Not supported on OMAP4 ES1.0 silicon */
	अगर (omap_rev() == OMAP4430_REV_ES1_0) अणु
		WARN(1, "WakeupGen: Not supported on OMAP4430 ES1.0\n");
		वापस -EPERM;
	पूर्ण

	/* Static mapping, never released */
	wakeupgen_base = of_iomap(node, 0);
	अगर (WARN_ON(!wakeupgen_base))
		वापस -ENOMEM;

	अगर (cpu_is_omap44xx()) अणु
		irq_banks = OMAP4_NR_BANKS;
		max_irqs = OMAP4_NR_IRQS;
		omap_secure_apis = 1;
		wakeupgen_ops = &omap4_wakeupgen_ops;
	पूर्ण अन्यथा अगर (soc_is_omap54xx()) अणु
		wakeupgen_ops = &omap5_wakeupgen_ops;
	पूर्ण अन्यथा अगर (soc_is_am43xx()) अणु
		irq_banks = AM43XX_NR_REG_BANKS;
		max_irqs = AM43XX_IRQS;
		wakeupgen_ops = &am43xx_wakeupgen_ops;
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_hierarchy(parent_करोमुख्य, 0, max_irqs,
					  node, &wakeupgen_करोमुख्य_ops,
					  शून्य);
	अगर (!करोमुख्य) अणु
		iounmap(wakeupgen_base);
		वापस -ENOMEM;
	पूर्ण

	/* Clear all IRQ biपंचांगasks at wakeupGen level */
	क्रम (i = 0; i < irq_banks; i++) अणु
		wakeupgen_ग_लिखोl(0, i, CPU0_ID);
		अगर (!soc_is_am43xx())
			wakeupgen_ग_लिखोl(0, i, CPU1_ID);
	पूर्ण

	/*
	 * FIXME: Add support to set_smp_affinity() once the core
	 * GIC code has necessary hooks in place.
	 */

	/* Associate all the IRQs to boot CPU like GIC init करोes. */
	क्रम (i = 0; i < max_irqs; i++)
		irq_target_cpu[i] = boot_cpu;

	/*
	 * Enables OMAP5 ES2 PM Mode using ES2_PM_MODE in AMBA_IF_MODE
	 * 0x0:	ES1 behavior, CPU cores would enter and निकास OFF mode together.
	 * 0x1:	ES2 behavior, CPU cores are allowed to enter/निकास OFF mode
	 * independently.
	 * This needs to be set one समय thanks to always ON करोमुख्य.
	 *
	 * We करो not support ES1 behavior anymore. OMAP5 is assumed to be
	 * ES2.0, and the same is applicable क्रम DRA7.
	 */
	अगर (soc_is_omap54xx() || soc_is_dra7xx()) अणु
		val = __raw_पढ़ोl(wakeupgen_base + OMAP_AMBA_IF_MODE);
		val |= BIT(5);
		omap_smc1(OMAP5_MON_AMBA_IF_INDEX, val);
	पूर्ण

	irq_hotplug_init();
	irq_pm_init();

	sar_base = omap4_get_sar_ram_base();

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(ti_wakeupgen, "ti,omap4-wugen-mpu", wakeupgen_init);
