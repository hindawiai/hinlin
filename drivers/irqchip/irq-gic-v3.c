<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013-2017 ARM Limited, All Rights Reserved.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#घोषणा pr_fmt(fmt)	"GICv3: " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/percpu.h>
#समावेश <linux/refcount.h>
#समावेश <linux/slab.h>

#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/arm-gic-common.h>
#समावेश <linux/irqchip/arm-gic-v3.h>
#समावेश <linux/irqchip/irq-partition-percpu.h>

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/virt.h>

#समावेश "irq-gic-common.h"

#घोषणा GICD_INT_NMI_PRI	(GICD_INT_DEF_PRI & ~0x80)

#घोषणा FLAGS_WORKAROUND_GICR_WAKER_MSM8996	(1ULL << 0)
#घोषणा FLAGS_WORKAROUND_CAVIUM_ERRATUM_38539	(1ULL << 1)

#घोषणा GIC_IRQ_TYPE_PARTITION	(GIC_IRQ_TYPE_LPI + 1)

काष्ठा redist_region अणु
	व्योम __iomem		*redist_base;
	phys_addr_t		phys_base;
	bool			single_redist;
पूर्ण;

काष्ठा gic_chip_data अणु
	काष्ठा fwnode_handle	*fwnode;
	व्योम __iomem		*dist_base;
	काष्ठा redist_region	*redist_regions;
	काष्ठा rdists		rdists;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	u64			redist_stride;
	u32			nr_redist_regions;
	u64			flags;
	bool			has_rss;
	अचिन्हित पूर्णांक		ppi_nr;
	काष्ठा partition_desc	**ppi_descs;
पूर्ण;

अटल काष्ठा gic_chip_data gic_data __पढ़ो_mostly;
अटल DEFINE_STATIC_KEY_TRUE(supports_deactivate_key);

#घोषणा GIC_ID_NR	(1U << GICD_TYPER_ID_BITS(gic_data.rdists.gicd_typer))
#घोषणा GIC_LINE_NR	min(GICD_TYPER_SPIS(gic_data.rdists.gicd_typer), 1020U)
#घोषणा GIC_ESPI_NR	GICD_TYPER_ESPIS(gic_data.rdists.gicd_typer)

/*
 * The behaviours of RPR and PMR रेजिस्टरs dअगरfer depending on the value of
 * SCR_EL3.FIQ, and the behaviour of non-secure priority रेजिस्टरs of the
 * distributor and redistributors depends on whether security is enabled in the
 * GIC.
 *
 * When security is enabled, non-secure priority values from the (re)distributor
 * are presented to the GIC CPUIF as follow:
 *     (GIC_(R)DIST_PRI[irq] >> 1) | 0x80;
 *
 * If SCR_EL3.FIQ == 1, the values written to/पढ़ो from PMR and RPR at non-secure
 * EL1 are subject to a similar operation thus matching the priorities presented
 * from the (re)distributor when security is enabled. When SCR_EL3.FIQ == 0,
 * these values are unchanged by the GIC.
 *
 * see GICv3/GICv4 Architecture Specअगरication (IHI0069D):
 * - section 4.8.1 Non-secure accesses to रेजिस्टर fields क्रम Secure पूर्णांकerrupt
 *   priorities.
 * - Figure 4-7 Secure पढ़ो of the priority field क्रम a Non-secure Group 1
 *   पूर्णांकerrupt.
 */
अटल DEFINE_STATIC_KEY_FALSE(supports_pseuकरो_nmis);

/*
 * Global अटल key controlling whether an update to PMR allowing more
 * पूर्णांकerrupts requires to be propagated to the redistributor (DSB SY).
 * And this needs to be exported क्रम modules to be able to enable
 * पूर्णांकerrupts...
 */
DEFINE_STATIC_KEY_FALSE(gic_pmr_sync);
EXPORT_SYMBOL(gic_pmr_sync);

DEFINE_STATIC_KEY_FALSE(gic_nonsecure_priorities);
EXPORT_SYMBOL(gic_nonsecure_priorities);

/* ppi_nmi_refs[n] == number of cpus having ppi[n + 16] set as NMI */
अटल refcount_t *ppi_nmi_refs;

अटल काष्ठा gic_kvm_info gic_v3_kvm_info;
अटल DEFINE_PER_CPU(bool, has_rss);

#घोषणा MPIDR_RS(mpidr)			(((mpidr) & 0xF0UL) >> 4)
#घोषणा gic_data_rdist()		(this_cpu_ptr(gic_data.rdists.rdist))
#घोषणा gic_data_rdist_rd_base()	(gic_data_rdist()->rd_base)
#घोषणा gic_data_rdist_sgi_base()	(gic_data_rdist_rd_base() + SZ_64K)

/* Our शेष, arbitrary priority value. Linux only uses one anyway. */
#घोषणा DEFAULT_PMR_VALUE	0xf0

क्रमागत gic_पूर्णांकid_range अणु
	SGI_RANGE,
	PPI_RANGE,
	SPI_RANGE,
	EPPI_RANGE,
	ESPI_RANGE,
	LPI_RANGE,
	__INVALID_RANGE__
पूर्ण;

अटल क्रमागत gic_पूर्णांकid_range __get_पूर्णांकid_range(irq_hw_number_t hwirq)
अणु
	चयन (hwirq) अणु
	हाल 0 ... 15:
		वापस SGI_RANGE;
	हाल 16 ... 31:
		वापस PPI_RANGE;
	हाल 32 ... 1019:
		वापस SPI_RANGE;
	हाल EPPI_BASE_INTID ... (EPPI_BASE_INTID + 63):
		वापस EPPI_RANGE;
	हाल ESPI_BASE_INTID ... (ESPI_BASE_INTID + 1023):
		वापस ESPI_RANGE;
	हाल 8192 ... GENMASK(23, 0):
		वापस LPI_RANGE;
	शेष:
		वापस __INVALID_RANGE__;
	पूर्ण
पूर्ण

अटल क्रमागत gic_पूर्णांकid_range get_पूर्णांकid_range(काष्ठा irq_data *d)
अणु
	वापस __get_पूर्णांकid_range(d->hwirq);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक gic_irq(काष्ठा irq_data *d)
अणु
	वापस d->hwirq;
पूर्ण

अटल अंतरभूत bool gic_irq_in_rdist(काष्ठा irq_data *d)
अणु
	चयन (get_पूर्णांकid_range(d)) अणु
	हाल SGI_RANGE:
	हाल PPI_RANGE:
	हाल EPPI_RANGE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __iomem *gic_dist_base(काष्ठा irq_data *d)
अणु
	चयन (get_पूर्णांकid_range(d)) अणु
	हाल SGI_RANGE:
	हाल PPI_RANGE:
	हाल EPPI_RANGE:
		/* SGI+PPI -> SGI_base क्रम this CPU */
		वापस gic_data_rdist_sgi_base();

	हाल SPI_RANGE:
	हाल ESPI_RANGE:
		/* SPI -> dist_base */
		वापस gic_data.dist_base;

	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम gic_करो_रुको_क्रम_rwp(व्योम __iomem *base)
अणु
	u32 count = 1000000;	/* 1s! */

	जबतक (पढ़ोl_relaxed(base + GICD_CTLR) & GICD_CTLR_RWP) अणु
		count--;
		अगर (!count) अणु
			pr_err_ratelimited("RWP timeout, gone fishing\n");
			वापस;
		पूर्ण
		cpu_relax();
		udelay(1);
	पूर्ण
पूर्ण

/* Wait क्रम completion of a distributor change */
अटल व्योम gic_dist_रुको_क्रम_rwp(व्योम)
अणु
	gic_करो_रुको_क्रम_rwp(gic_data.dist_base);
पूर्ण

/* Wait क्रम completion of a redistributor change */
अटल व्योम gic_redist_रुको_क्रम_rwp(व्योम)
अणु
	gic_करो_रुको_क्रम_rwp(gic_data_rdist_rd_base());
पूर्ण

#अगर_घोषित CONFIG_ARM64

अटल u64 __maybe_unused gic_पढ़ो_iar(व्योम)
अणु
	अगर (cpus_have_स्थिर_cap(ARM64_WORKAROUND_CAVIUM_23154))
		वापस gic_पढ़ो_iar_cavium_thunderx();
	अन्यथा
		वापस gic_पढ़ो_iar_common();
पूर्ण
#पूर्ण_अगर

अटल व्योम gic_enable_redist(bool enable)
अणु
	व्योम __iomem *rbase;
	u32 count = 1000000;	/* 1s! */
	u32 val;

	अगर (gic_data.flags & FLAGS_WORKAROUND_GICR_WAKER_MSM8996)
		वापस;

	rbase = gic_data_rdist_rd_base();

	val = पढ़ोl_relaxed(rbase + GICR_WAKER);
	अगर (enable)
		/* Wake up this CPU redistributor */
		val &= ~GICR_WAKER_ProcessorSleep;
	अन्यथा
		val |= GICR_WAKER_ProcessorSleep;
	ग_लिखोl_relaxed(val, rbase + GICR_WAKER);

	अगर (!enable) अणु		/* Check that GICR_WAKER is ग_लिखोable */
		val = पढ़ोl_relaxed(rbase + GICR_WAKER);
		अगर (!(val & GICR_WAKER_ProcessorSleep))
			वापस;	/* No PM support in this redistributor */
	पूर्ण

	जबतक (--count) अणु
		val = पढ़ोl_relaxed(rbase + GICR_WAKER);
		अगर (enable ^ (bool)(val & GICR_WAKER_ChildrenAsleep))
			अवरोध;
		cpu_relax();
		udelay(1);
	पूर्ण
	अगर (!count)
		pr_err_ratelimited("redistributor failed to %s...\n",
				   enable ? "wakeup" : "sleep");
पूर्ण

/*
 * Routines to disable, enable, EOI and route पूर्णांकerrupts
 */
अटल u32 convert_offset_index(काष्ठा irq_data *d, u32 offset, u32 *index)
अणु
	चयन (get_पूर्णांकid_range(d)) अणु
	हाल SGI_RANGE:
	हाल PPI_RANGE:
	हाल SPI_RANGE:
		*index = d->hwirq;
		वापस offset;
	हाल EPPI_RANGE:
		/*
		 * Contrary to the ESPI range, the EPPI range is contiguous
		 * to the PPI range in the रेजिस्टरs, so let's adjust the
		 * displacement accordingly. Consistency is overrated.
		 */
		*index = d->hwirq - EPPI_BASE_INTID + 32;
		वापस offset;
	हाल ESPI_RANGE:
		*index = d->hwirq - ESPI_BASE_INTID;
		चयन (offset) अणु
		हाल GICD_ISENABLER:
			वापस GICD_ISENABLERnE;
		हाल GICD_ICENABLER:
			वापस GICD_ICENABLERnE;
		हाल GICD_ISPENDR:
			वापस GICD_ISPENDRnE;
		हाल GICD_ICPENDR:
			वापस GICD_ICPENDRnE;
		हाल GICD_ISACTIVER:
			वापस GICD_ISACTIVERnE;
		हाल GICD_ICACTIVER:
			वापस GICD_ICACTIVERnE;
		हाल GICD_IPRIORITYR:
			वापस GICD_IPRIORITYRnE;
		हाल GICD_ICFGR:
			वापस GICD_ICFGRnE;
		हाल GICD_IROUTER:
			वापस GICD_IROUTERnE;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	WARN_ON(1);
	*index = d->hwirq;
	वापस offset;
पूर्ण

अटल पूर्णांक gic_peek_irq(काष्ठा irq_data *d, u32 offset)
अणु
	व्योम __iomem *base;
	u32 index, mask;

	offset = convert_offset_index(d, offset, &index);
	mask = 1 << (index % 32);

	अगर (gic_irq_in_rdist(d))
		base = gic_data_rdist_sgi_base();
	अन्यथा
		base = gic_data.dist_base;

	वापस !!(पढ़ोl_relaxed(base + offset + (index / 32) * 4) & mask);
पूर्ण

अटल व्योम gic_poke_irq(काष्ठा irq_data *d, u32 offset)
अणु
	व्योम (*rwp_रुको)(व्योम);
	व्योम __iomem *base;
	u32 index, mask;

	offset = convert_offset_index(d, offset, &index);
	mask = 1 << (index % 32);

	अगर (gic_irq_in_rdist(d)) अणु
		base = gic_data_rdist_sgi_base();
		rwp_रुको = gic_redist_रुको_क्रम_rwp;
	पूर्ण अन्यथा अणु
		base = gic_data.dist_base;
		rwp_रुको = gic_dist_रुको_क्रम_rwp;
	पूर्ण

	ग_लिखोl_relaxed(mask, base + offset + (index / 32) * 4);
	rwp_रुको();
पूर्ण

अटल व्योम gic_mask_irq(काष्ठा irq_data *d)
अणु
	gic_poke_irq(d, GICD_ICENABLER);
पूर्ण

अटल व्योम gic_eoimode1_mask_irq(काष्ठा irq_data *d)
अणु
	gic_mask_irq(d);
	/*
	 * When masking a क्रमwarded पूर्णांकerrupt, make sure it is
	 * deactivated as well.
	 *
	 * This ensures that an पूर्णांकerrupt that is getting
	 * disabled/masked will not get "stuck", because there is
	 * noone to deactivate it (guest is being terminated).
	 */
	अगर (irqd_is_क्रमwarded_to_vcpu(d))
		gic_poke_irq(d, GICD_ICACTIVER);
पूर्ण

अटल व्योम gic_unmask_irq(काष्ठा irq_data *d)
अणु
	gic_poke_irq(d, GICD_ISENABLER);
पूर्ण

अटल अंतरभूत bool gic_supports_nmi(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARM64_PSEUDO_NMI) &&
	       अटल_branch_likely(&supports_pseuकरो_nmis);
पूर्ण

अटल पूर्णांक gic_irq_set_irqchip_state(काष्ठा irq_data *d,
				     क्रमागत irqchip_irq_state which, bool val)
अणु
	u32 reg;

	अगर (d->hwirq >= 8192) /* SGI/PPI/SPI only */
		वापस -EINVAL;

	चयन (which) अणु
	हाल IRQCHIP_STATE_PENDING:
		reg = val ? GICD_ISPENDR : GICD_ICPENDR;
		अवरोध;

	हाल IRQCHIP_STATE_ACTIVE:
		reg = val ? GICD_ISACTIVER : GICD_ICACTIVER;
		अवरोध;

	हाल IRQCHIP_STATE_MASKED:
		reg = val ? GICD_ICENABLER : GICD_ISENABLER;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	gic_poke_irq(d, reg);
	वापस 0;
पूर्ण

अटल पूर्णांक gic_irq_get_irqchip_state(काष्ठा irq_data *d,
				     क्रमागत irqchip_irq_state which, bool *val)
अणु
	अगर (d->hwirq >= 8192) /* PPI/SPI only */
		वापस -EINVAL;

	चयन (which) अणु
	हाल IRQCHIP_STATE_PENDING:
		*val = gic_peek_irq(d, GICD_ISPENDR);
		अवरोध;

	हाल IRQCHIP_STATE_ACTIVE:
		*val = gic_peek_irq(d, GICD_ISACTIVER);
		अवरोध;

	हाल IRQCHIP_STATE_MASKED:
		*val = !gic_peek_irq(d, GICD_ISENABLER);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gic_irq_set_prio(काष्ठा irq_data *d, u8 prio)
अणु
	व्योम __iomem *base = gic_dist_base(d);
	u32 offset, index;

	offset = convert_offset_index(d, GICD_IPRIORITYR, &index);

	ग_लिखोb_relaxed(prio, base + offset + index);
पूर्ण

अटल u32 gic_get_ppi_index(काष्ठा irq_data *d)
अणु
	चयन (get_पूर्णांकid_range(d)) अणु
	हाल PPI_RANGE:
		वापस d->hwirq - 16;
	हाल EPPI_RANGE:
		वापस d->hwirq - EPPI_BASE_INTID + 16;
	शेष:
		unreachable();
	पूर्ण
पूर्ण

अटल पूर्णांक gic_irq_nmi_setup(काष्ठा irq_data *d)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(d->irq);

	अगर (!gic_supports_nmi())
		वापस -EINVAL;

	अगर (gic_peek_irq(d, GICD_ISENABLER)) अणु
		pr_err("Cannot set NMI property of enabled IRQ %u\n", d->irq);
		वापस -EINVAL;
	पूर्ण

	/*
	 * A secondary irq_chip should be in अक्षरge of LPI request,
	 * it should not be possible to get there
	 */
	अगर (WARN_ON(gic_irq(d) >= 8192))
		वापस -EINVAL;

	/* desc lock should alपढ़ोy be held */
	अगर (gic_irq_in_rdist(d)) अणु
		u32 idx = gic_get_ppi_index(d);

		/* Setting up PPI as NMI, only चयन handler क्रम first NMI */
		अगर (!refcount_inc_not_zero(&ppi_nmi_refs[idx])) अणु
			refcount_set(&ppi_nmi_refs[idx], 1);
			desc->handle_irq = handle_percpu_devid_fasteoi_nmi;
		पूर्ण
	पूर्ण अन्यथा अणु
		desc->handle_irq = handle_fasteoi_nmi;
	पूर्ण

	gic_irq_set_prio(d, GICD_INT_NMI_PRI);

	वापस 0;
पूर्ण

अटल व्योम gic_irq_nmi_tearकरोwn(काष्ठा irq_data *d)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(d->irq);

	अगर (WARN_ON(!gic_supports_nmi()))
		वापस;

	अगर (gic_peek_irq(d, GICD_ISENABLER)) अणु
		pr_err("Cannot set NMI property of enabled IRQ %u\n", d->irq);
		वापस;
	पूर्ण

	/*
	 * A secondary irq_chip should be in अक्षरge of LPI request,
	 * it should not be possible to get there
	 */
	अगर (WARN_ON(gic_irq(d) >= 8192))
		वापस;

	/* desc lock should alपढ़ोy be held */
	अगर (gic_irq_in_rdist(d)) अणु
		u32 idx = gic_get_ppi_index(d);

		/* Tearing करोwn NMI, only चयन handler क्रम last NMI */
		अगर (refcount_dec_and_test(&ppi_nmi_refs[idx]))
			desc->handle_irq = handle_percpu_devid_irq;
	पूर्ण अन्यथा अणु
		desc->handle_irq = handle_fasteoi_irq;
	पूर्ण

	gic_irq_set_prio(d, GICD_INT_DEF_PRI);
पूर्ण

अटल व्योम gic_eoi_irq(काष्ठा irq_data *d)
अणु
	gic_ग_लिखो_eoir(gic_irq(d));
पूर्ण

अटल व्योम gic_eoimode1_eoi_irq(काष्ठा irq_data *d)
अणु
	/*
	 * No need to deactivate an LPI, or an पूर्णांकerrupt that
	 * is is getting क्रमwarded to a vcpu.
	 */
	अगर (gic_irq(d) >= 8192 || irqd_is_क्रमwarded_to_vcpu(d))
		वापस;
	gic_ग_लिखो_dir(gic_irq(d));
पूर्ण

अटल पूर्णांक gic_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	क्रमागत gic_पूर्णांकid_range range;
	अचिन्हित पूर्णांक irq = gic_irq(d);
	व्योम (*rwp_रुको)(व्योम);
	व्योम __iomem *base;
	u32 offset, index;
	पूर्णांक ret;

	range = get_पूर्णांकid_range(d);

	/* Interrupt configuration क्रम SGIs can't be changed */
	अगर (range == SGI_RANGE)
		वापस type != IRQ_TYPE_EDGE_RISING ? -EINVAL : 0;

	/* SPIs have restrictions on the supported types */
	अगर ((range == SPI_RANGE || range == ESPI_RANGE) &&
	    type != IRQ_TYPE_LEVEL_HIGH && type != IRQ_TYPE_EDGE_RISING)
		वापस -EINVAL;

	अगर (gic_irq_in_rdist(d)) अणु
		base = gic_data_rdist_sgi_base();
		rwp_रुको = gic_redist_रुको_क्रम_rwp;
	पूर्ण अन्यथा अणु
		base = gic_data.dist_base;
		rwp_रुको = gic_dist_रुको_क्रम_rwp;
	पूर्ण

	offset = convert_offset_index(d, GICD_ICFGR, &index);

	ret = gic_configure_irq(index, type, base + offset, rwp_रुको);
	अगर (ret && (range == PPI_RANGE || range == EPPI_RANGE)) अणु
		/* Misconfigured PPIs are usually not fatal */
		pr_warn("GIC: PPI INTID%d is secure or misconfigured\n", irq);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gic_irq_set_vcpu_affinity(काष्ठा irq_data *d, व्योम *vcpu)
अणु
	अगर (get_पूर्णांकid_range(d) == SGI_RANGE)
		वापस -EINVAL;

	अगर (vcpu)
		irqd_set_क्रमwarded_to_vcpu(d);
	अन्यथा
		irqd_clr_क्रमwarded_to_vcpu(d);
	वापस 0;
पूर्ण

अटल u64 gic_mpidr_to_affinity(अचिन्हित दीर्घ mpidr)
अणु
	u64 aff;

	aff = ((u64)MPIDR_AFFINITY_LEVEL(mpidr, 3) << 32 |
	       MPIDR_AFFINITY_LEVEL(mpidr, 2) << 16 |
	       MPIDR_AFFINITY_LEVEL(mpidr, 1) << 8  |
	       MPIDR_AFFINITY_LEVEL(mpidr, 0));

	वापस aff;
पूर्ण

अटल व्योम gic_deactivate_unhandled(u32 irqnr)
अणु
	अगर (अटल_branch_likely(&supports_deactivate_key)) अणु
		अगर (irqnr < 8192)
			gic_ग_लिखो_dir(irqnr);
	पूर्ण अन्यथा अणु
		gic_ग_लिखो_eoir(irqnr);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम gic_handle_nmi(u32 irqnr, काष्ठा pt_regs *regs)
अणु
	bool irqs_enabled = पूर्णांकerrupts_enabled(regs);
	पूर्णांक err;

	अगर (irqs_enabled)
		nmi_enter();

	अगर (अटल_branch_likely(&supports_deactivate_key))
		gic_ग_लिखो_eoir(irqnr);
	/*
	 * Leave the PSR.I bit set to prevent other NMIs to be
	 * received जबतक handling this one.
	 * PSR.I will be restored when we ERET to the
	 * पूर्णांकerrupted context.
	 */
	err = handle_करोमुख्य_nmi(gic_data.करोमुख्य, irqnr, regs);
	अगर (err)
		gic_deactivate_unhandled(irqnr);

	अगर (irqs_enabled)
		nmi_निकास();
पूर्ण

अटल u32 करो_पढ़ो_iar(काष्ठा pt_regs *regs)
अणु
	u32 iar;

	अगर (gic_supports_nmi() && unlikely(!पूर्णांकerrupts_enabled(regs))) अणु
		u64 pmr;

		/*
		 * We were in a context with IRQs disabled. However, the
		 * entry code has set PMR to a value that allows any
		 * पूर्णांकerrupt to be acknowledged, and not just NMIs. This can
		 * lead to surprising effects अगर the NMI has been retired in
		 * the meanसमय, and that there is an IRQ pending. The IRQ
		 * would then be taken in NMI context, something that nobody
		 * wants to debug twice.
		 *
		 * Until we sort this, drop PMR again to a level that will
		 * actually only allow NMIs beक्रमe पढ़ोing IAR, and then
		 * restore it to what it was.
		 */
		pmr = gic_पढ़ो_pmr();
		gic_pmr_mask_irqs();
		isb();

		iar = gic_पढ़ो_iar();

		gic_ग_लिखो_pmr(pmr);
	पूर्ण अन्यथा अणु
		iar = gic_पढ़ो_iar();
	पूर्ण

	वापस iar;
पूर्ण

अटल यंत्रlinkage व्योम __exception_irq_entry gic_handle_irq(काष्ठा pt_regs *regs)
अणु
	u32 irqnr;

	irqnr = करो_पढ़ो_iar(regs);

	/* Check क्रम special IDs first */
	अगर ((irqnr >= 1020 && irqnr <= 1023))
		वापस;

	अगर (gic_supports_nmi() &&
	    unlikely(gic_पढ़ो_rpr() == GICD_INT_NMI_PRI)) अणु
		gic_handle_nmi(irqnr, regs);
		वापस;
	पूर्ण

	अगर (gic_prio_masking_enabled()) अणु
		gic_pmr_mask_irqs();
		gic_arch_enable_irqs();
	पूर्ण

	अगर (अटल_branch_likely(&supports_deactivate_key))
		gic_ग_लिखो_eoir(irqnr);
	अन्यथा
		isb();

	अगर (handle_करोमुख्य_irq(gic_data.करोमुख्य, irqnr, regs)) अणु
		WARN_ONCE(true, "Unexpected interrupt received!\n");
		gic_deactivate_unhandled(irqnr);
	पूर्ण
पूर्ण

अटल u32 gic_get_pribits(व्योम)
अणु
	u32 pribits;

	pribits = gic_पढ़ो_ctlr();
	pribits &= ICC_CTLR_EL1_PRI_BITS_MASK;
	pribits >>= ICC_CTLR_EL1_PRI_BITS_SHIFT;
	pribits++;

	वापस pribits;
पूर्ण

अटल bool gic_has_group0(व्योम)
अणु
	u32 val;
	u32 old_pmr;

	old_pmr = gic_पढ़ो_pmr();

	/*
	 * Let's find out अगर Group0 is under control of EL3 or not by
	 * setting the highest possible, non-zero priority in PMR.
	 *
	 * If SCR_EL3.FIQ is set, the priority माला_लो shअगरted करोwn in
	 * order क्रम the CPU पूर्णांकerface to set bit 7, and keep the
	 * actual priority in the non-secure range. In the process, it
	 * looses the least signअगरicant bit and the actual priority
	 * becomes 0x80. Reading it back वापसs 0, indicating that
	 * we're don't have access to Group0.
	 */
	gic_ग_लिखो_pmr(BIT(8 - gic_get_pribits()));
	val = gic_पढ़ो_pmr();

	gic_ग_लिखो_pmr(old_pmr);

	वापस val != 0;
पूर्ण

अटल व्योम __init gic_dist_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	u64 affinity;
	व्योम __iomem *base = gic_data.dist_base;
	u32 val;

	/* Disable the distributor */
	ग_लिखोl_relaxed(0, base + GICD_CTLR);
	gic_dist_रुको_क्रम_rwp();

	/*
	 * Configure SPIs as non-secure Group-1. This will only matter
	 * अगर the GIC only has a single security state. This will not
	 * करो the right thing अगर the kernel is running in secure mode,
	 * but that's not the पूर्णांकended use हाल anyway.
	 */
	क्रम (i = 32; i < GIC_LINE_NR; i += 32)
		ग_लिखोl_relaxed(~0, base + GICD_IGROUPR + i / 8);

	/* Extended SPI range, not handled by the GICv2/GICv3 common code */
	क्रम (i = 0; i < GIC_ESPI_NR; i += 32) अणु
		ग_लिखोl_relaxed(~0U, base + GICD_ICENABLERnE + i / 8);
		ग_लिखोl_relaxed(~0U, base + GICD_ICACTIVERnE + i / 8);
	पूर्ण

	क्रम (i = 0; i < GIC_ESPI_NR; i += 32)
		ग_लिखोl_relaxed(~0U, base + GICD_IGROUPRnE + i / 8);

	क्रम (i = 0; i < GIC_ESPI_NR; i += 16)
		ग_लिखोl_relaxed(0, base + GICD_ICFGRnE + i / 4);

	क्रम (i = 0; i < GIC_ESPI_NR; i += 4)
		ग_लिखोl_relaxed(GICD_INT_DEF_PRI_X4, base + GICD_IPRIORITYRnE + i);

	/* Now करो the common stuff, and रुको क्रम the distributor to drain */
	gic_dist_config(base, GIC_LINE_NR, gic_dist_रुको_क्रम_rwp);

	val = GICD_CTLR_ARE_NS | GICD_CTLR_ENABLE_G1A | GICD_CTLR_ENABLE_G1;
	अगर (gic_data.rdists.gicd_typer2 & GICD_TYPER2_nASSGIcap) अणु
		pr_info("Enabling SGIs without active state\n");
		val |= GICD_CTLR_nASSGIreq;
	पूर्ण

	/* Enable distributor with ARE, Group1 */
	ग_लिखोl_relaxed(val, base + GICD_CTLR);

	/*
	 * Set all global पूर्णांकerrupts to the boot CPU only. ARE must be
	 * enabled.
	 */
	affinity = gic_mpidr_to_affinity(cpu_logical_map(smp_processor_id()));
	क्रम (i = 32; i < GIC_LINE_NR; i++)
		gic_ग_लिखो_irouter(affinity, base + GICD_IROUTER + i * 8);

	क्रम (i = 0; i < GIC_ESPI_NR; i++)
		gic_ग_लिखो_irouter(affinity, base + GICD_IROUTERnE + i * 8);
पूर्ण

अटल पूर्णांक gic_iterate_rdists(पूर्णांक (*fn)(काष्ठा redist_region *, व्योम __iomem *))
अणु
	पूर्णांक ret = -ENODEV;
	पूर्णांक i;

	क्रम (i = 0; i < gic_data.nr_redist_regions; i++) अणु
		व्योम __iomem *ptr = gic_data.redist_regions[i].redist_base;
		u64 typer;
		u32 reg;

		reg = पढ़ोl_relaxed(ptr + GICR_PIDR2) & GIC_PIDR2_ARCH_MASK;
		अगर (reg != GIC_PIDR2_ARCH_GICv3 &&
		    reg != GIC_PIDR2_ARCH_GICv4) अणु /* We're in trouble... */
			pr_warn("No redistributor present @%p\n", ptr);
			अवरोध;
		पूर्ण

		करो अणु
			typer = gic_पढ़ो_typer(ptr + GICR_TYPER);
			ret = fn(gic_data.redist_regions + i, ptr);
			अगर (!ret)
				वापस 0;

			अगर (gic_data.redist_regions[i].single_redist)
				अवरोध;

			अगर (gic_data.redist_stride) अणु
				ptr += gic_data.redist_stride;
			पूर्ण अन्यथा अणु
				ptr += SZ_64K * 2; /* Skip RD_base + SGI_base */
				अगर (typer & GICR_TYPER_VLPIS)
					ptr += SZ_64K * 2; /* Skip VLPI_base + reserved page */
			पूर्ण
		पूर्ण जबतक (!(typer & GICR_TYPER_LAST));
	पूर्ण

	वापस ret ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक __gic_populate_rdist(काष्ठा redist_region *region, व्योम __iomem *ptr)
अणु
	अचिन्हित दीर्घ mpidr = cpu_logical_map(smp_processor_id());
	u64 typer;
	u32 aff;

	/*
	 * Convert affinity to a 32bit value that can be matched to
	 * GICR_TYPER bits [63:32].
	 */
	aff = (MPIDR_AFFINITY_LEVEL(mpidr, 3) << 24 |
	       MPIDR_AFFINITY_LEVEL(mpidr, 2) << 16 |
	       MPIDR_AFFINITY_LEVEL(mpidr, 1) << 8 |
	       MPIDR_AFFINITY_LEVEL(mpidr, 0));

	typer = gic_पढ़ो_typer(ptr + GICR_TYPER);
	अगर ((typer >> 32) == aff) अणु
		u64 offset = ptr - region->redist_base;
		raw_spin_lock_init(&gic_data_rdist()->rd_lock);
		gic_data_rdist_rd_base() = ptr;
		gic_data_rdist()->phys_base = region->phys_base + offset;

		pr_info("CPU%d: found redistributor %lx region %d:%pa\n",
			smp_processor_id(), mpidr,
			(पूर्णांक)(region - gic_data.redist_regions),
			&gic_data_rdist()->phys_base);
		वापस 0;
	पूर्ण

	/* Try next one */
	वापस 1;
पूर्ण

अटल पूर्णांक gic_populate_rdist(व्योम)
अणु
	अगर (gic_iterate_rdists(__gic_populate_rdist) == 0)
		वापस 0;

	/* We couldn't even deal with ourselves... */
	WARN(true, "CPU%d: mpidr %lx has no re-distributor!\n",
	     smp_processor_id(),
	     (अचिन्हित दीर्घ)cpu_logical_map(smp_processor_id()));
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक __gic_update_rdist_properties(काष्ठा redist_region *region,
					 व्योम __iomem *ptr)
अणु
	u64 typer = gic_पढ़ो_typer(ptr + GICR_TYPER);

	gic_data.rdists.has_vlpis &= !!(typer & GICR_TYPER_VLPIS);

	/* RVPEID implies some क्रमm of DirectLPI, no matter what the करोc says... :-/ */
	gic_data.rdists.has_rvpeid &= !!(typer & GICR_TYPER_RVPEID);
	gic_data.rdists.has_direct_lpi &= (!!(typer & GICR_TYPER_DirectLPIS) |
					   gic_data.rdists.has_rvpeid);
	gic_data.rdists.has_vpend_valid_dirty &= !!(typer & GICR_TYPER_सूचीTY);

	/* Detect non-sensical configurations */
	अगर (WARN_ON_ONCE(gic_data.rdists.has_rvpeid && !gic_data.rdists.has_vlpis)) अणु
		gic_data.rdists.has_direct_lpi = false;
		gic_data.rdists.has_vlpis = false;
		gic_data.rdists.has_rvpeid = false;
	पूर्ण

	gic_data.ppi_nr = min(GICR_TYPER_NR_PPIS(typer), gic_data.ppi_nr);

	वापस 1;
पूर्ण

अटल व्योम gic_update_rdist_properties(व्योम)
अणु
	gic_data.ppi_nr = अच_पूर्णांक_उच्च;
	gic_iterate_rdists(__gic_update_rdist_properties);
	अगर (WARN_ON(gic_data.ppi_nr == अच_पूर्णांक_उच्च))
		gic_data.ppi_nr = 0;
	pr_info("%d PPIs implemented\n", gic_data.ppi_nr);
	अगर (gic_data.rdists.has_vlpis)
		pr_info("GICv4 features: %s%s%s\n",
			gic_data.rdists.has_direct_lpi ? "DirectLPI " : "",
			gic_data.rdists.has_rvpeid ? "RVPEID " : "",
			gic_data.rdists.has_vpend_valid_dirty ? "Valid+Dirty " : "");
पूर्ण

/* Check whether it's single security state view */
अटल अंतरभूत bool gic_dist_security_disabled(व्योम)
अणु
	वापस पढ़ोl_relaxed(gic_data.dist_base + GICD_CTLR) & GICD_CTLR_DS;
पूर्ण

अटल व्योम gic_cpu_sys_reg_init(व्योम)
अणु
	पूर्णांक i, cpu = smp_processor_id();
	u64 mpidr = cpu_logical_map(cpu);
	u64 need_rss = MPIDR_RS(mpidr);
	bool group0;
	u32 pribits;

	/*
	 * Need to check that the SRE bit has actually been set. If
	 * not, it means that SRE is disabled at EL2. We're going to
	 * die painfully, and there is nothing we can करो about it.
	 *
	 * Kindly inक्रमm the luser.
	 */
	अगर (!gic_enable_sre())
		pr_err("GIC: unable to set SRE (disabled at EL2), panic ahead\n");

	pribits = gic_get_pribits();

	group0 = gic_has_group0();

	/* Set priority mask रेजिस्टर */
	अगर (!gic_prio_masking_enabled()) अणु
		ग_लिखो_gicreg(DEFAULT_PMR_VALUE, ICC_PMR_EL1);
	पूर्ण अन्यथा अगर (gic_supports_nmi()) अणु
		/*
		 * Mismatch configuration with boot CPU, the प्रणाली is likely
		 * to die as पूर्णांकerrupt masking will not work properly on all
		 * CPUs
		 *
		 * The boot CPU calls this function beक्रमe enabling NMI support,
		 * and as a result we'll never see this warning in the boot path
		 * क्रम that CPU.
		 */
		अगर (अटल_branch_unlikely(&gic_nonsecure_priorities))
			WARN_ON(!group0 || gic_dist_security_disabled());
		अन्यथा
			WARN_ON(group0 && !gic_dist_security_disabled());
	पूर्ण

	/*
	 * Some firmwares hand over to the kernel with the BPR changed from
	 * its reset value (and with a value large enough to prevent
	 * any pre-emptive पूर्णांकerrupts from working at all). Writing a zero
	 * to BPR restores is reset value.
	 */
	gic_ग_लिखो_bpr1(0);

	अगर (अटल_branch_likely(&supports_deactivate_key)) अणु
		/* EOI drops priority only (mode 1) */
		gic_ग_लिखो_ctlr(ICC_CTLR_EL1_EOImode_drop);
	पूर्ण अन्यथा अणु
		/* EOI deactivates पूर्णांकerrupt too (mode 0) */
		gic_ग_लिखो_ctlr(ICC_CTLR_EL1_EOImode_drop_dir);
	पूर्ण

	/* Always whack Group0 beक्रमe Group1 */
	अगर (group0) अणु
		चयन(pribits) अणु
		हाल 8:
		हाल 7:
			ग_लिखो_gicreg(0, ICC_AP0R3_EL1);
			ग_लिखो_gicreg(0, ICC_AP0R2_EL1);
			fallthrough;
		हाल 6:
			ग_लिखो_gicreg(0, ICC_AP0R1_EL1);
			fallthrough;
		हाल 5:
		हाल 4:
			ग_लिखो_gicreg(0, ICC_AP0R0_EL1);
		पूर्ण

		isb();
	पूर्ण

	चयन(pribits) अणु
	हाल 8:
	हाल 7:
		ग_लिखो_gicreg(0, ICC_AP1R3_EL1);
		ग_लिखो_gicreg(0, ICC_AP1R2_EL1);
		fallthrough;
	हाल 6:
		ग_लिखो_gicreg(0, ICC_AP1R1_EL1);
		fallthrough;
	हाल 5:
	हाल 4:
		ग_लिखो_gicreg(0, ICC_AP1R0_EL1);
	पूर्ण

	isb();

	/* ... and let's hit the road... */
	gic_ग_लिखो_grpen1(1);

	/* Keep the RSS capability status in per_cpu variable */
	per_cpu(has_rss, cpu) = !!(gic_पढ़ो_ctlr() & ICC_CTLR_EL1_RSS);

	/* Check all the CPUs have capable of sending SGIs to other CPUs */
	क्रम_each_online_cpu(i) अणु
		bool have_rss = per_cpu(has_rss, i) && per_cpu(has_rss, cpu);

		need_rss |= MPIDR_RS(cpu_logical_map(i));
		अगर (need_rss && (!have_rss))
			pr_crit("CPU%d (%lx) can't SGI CPU%d (%lx), no RSS\n",
				cpu, (अचिन्हित दीर्घ)mpidr,
				i, (अचिन्हित दीर्घ)cpu_logical_map(i));
	पूर्ण

	/**
	 * GIC spec says, when ICC_CTLR_EL1.RSS==1 and GICD_TYPER.RSS==0,
	 * writing ICC_ASGI1R_EL1 रेजिस्टर with RS != 0 is a CONSTRAINED
	 * UNPREDICTABLE choice of :
	 *   - The ग_लिखो is ignored.
	 *   - The RS field is treated as 0.
	 */
	अगर (need_rss && (!gic_data.has_rss))
		pr_crit_once("RSS is required but GICD doesn't support it\n");
पूर्ण

अटल bool gicv3_nolpi;

अटल पूर्णांक __init gicv3_nolpi_cfg(अक्षर *buf)
अणु
	वापस strtobool(buf, &gicv3_nolpi);
पूर्ण
early_param("irqchip.gicv3_nolpi", gicv3_nolpi_cfg);

अटल पूर्णांक gic_dist_supports_lpis(व्योम)
अणु
	वापस (IS_ENABLED(CONFIG_ARM_GIC_V3_ITS) &&
		!!(पढ़ोl_relaxed(gic_data.dist_base + GICD_TYPER) & GICD_TYPER_LPIS) &&
		!gicv3_nolpi);
पूर्ण

अटल व्योम gic_cpu_init(व्योम)
अणु
	व्योम __iomem *rbase;
	पूर्णांक i;

	/* Register ourselves with the rest of the world */
	अगर (gic_populate_rdist())
		वापस;

	gic_enable_redist(true);

	WARN((gic_data.ppi_nr > 16 || GIC_ESPI_NR != 0) &&
	     !(gic_पढ़ो_ctlr() & ICC_CTLR_EL1_ExtRange),
	     "Distributor has extended ranges, but CPU%d doesn't\n",
	     smp_processor_id());

	rbase = gic_data_rdist_sgi_base();

	/* Configure SGIs/PPIs as non-secure Group-1 */
	क्रम (i = 0; i < gic_data.ppi_nr + 16; i += 32)
		ग_लिखोl_relaxed(~0, rbase + GICR_IGROUPR0 + i / 8);

	gic_cpu_config(rbase, gic_data.ppi_nr + 16, gic_redist_रुको_क्रम_rwp);

	/* initialise प्रणाली रेजिस्टरs */
	gic_cpu_sys_reg_init();
पूर्ण

#अगर_घोषित CONFIG_SMP

#घोषणा MPIDR_TO_SGI_RS(mpidr)	(MPIDR_RS(mpidr) << ICC_SGI1R_RS_SHIFT)
#घोषणा MPIDR_TO_SGI_CLUSTER_ID(mpidr)	((mpidr) & ~0xFUL)

अटल पूर्णांक gic_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	gic_cpu_init();

	अगर (gic_dist_supports_lpis())
		its_cpu_init();

	वापस 0;
पूर्ण

अटल u16 gic_compute_target_list(पूर्णांक *base_cpu, स्थिर काष्ठा cpumask *mask,
				   अचिन्हित दीर्घ cluster_id)
अणु
	पूर्णांक next_cpu, cpu = *base_cpu;
	अचिन्हित दीर्घ mpidr = cpu_logical_map(cpu);
	u16 tlist = 0;

	जबतक (cpu < nr_cpu_ids) अणु
		tlist |= 1 << (mpidr & 0xf);

		next_cpu = cpumask_next(cpu, mask);
		अगर (next_cpu >= nr_cpu_ids)
			जाओ out;
		cpu = next_cpu;

		mpidr = cpu_logical_map(cpu);

		अगर (cluster_id != MPIDR_TO_SGI_CLUSTER_ID(mpidr)) अणु
			cpu--;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	*base_cpu = cpu;
	वापस tlist;
पूर्ण

#घोषणा MPIDR_TO_SGI_AFFINITY(cluster_id, level) \
	(MPIDR_AFFINITY_LEVEL(cluster_id, level) \
		<< ICC_SGI1R_AFFINITY_## level ##_SHIFT)

अटल व्योम gic_send_sgi(u64 cluster_id, u16 tlist, अचिन्हित पूर्णांक irq)
अणु
	u64 val;

	val = (MPIDR_TO_SGI_AFFINITY(cluster_id, 3)	|
	       MPIDR_TO_SGI_AFFINITY(cluster_id, 2)	|
	       irq << ICC_SGI1R_SGI_ID_SHIFT		|
	       MPIDR_TO_SGI_AFFINITY(cluster_id, 1)	|
	       MPIDR_TO_SGI_RS(cluster_id)		|
	       tlist << ICC_SGI1R_TARGET_LIST_SHIFT);

	pr_devel("CPU%d: ICC_SGI1R_EL1 %llx\n", smp_processor_id(), val);
	gic_ग_लिखो_sgi1r(val);
पूर्ण

अटल व्योम gic_ipi_send_mask(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *mask)
अणु
	पूर्णांक cpu;

	अगर (WARN_ON(d->hwirq >= 16))
		वापस;

	/*
	 * Ensure that stores to Normal memory are visible to the
	 * other CPUs beक्रमe issuing the IPI.
	 */
	wmb();

	क्रम_each_cpu(cpu, mask) अणु
		u64 cluster_id = MPIDR_TO_SGI_CLUSTER_ID(cpu_logical_map(cpu));
		u16 tlist;

		tlist = gic_compute_target_list(&cpu, mask, cluster_id);
		gic_send_sgi(cluster_id, tlist, d->hwirq);
	पूर्ण

	/* Force the above ग_लिखोs to ICC_SGI1R_EL1 to be executed */
	isb();
पूर्ण

अटल व्योम __init gic_smp_init(व्योम)
अणु
	काष्ठा irq_fwspec sgi_fwspec = अणु
		.fwnode		= gic_data.fwnode,
		.param_count	= 1,
	पूर्ण;
	पूर्णांक base_sgi;

	cpuhp_setup_state_nocalls(CPUHP_AP_IRQ_GIC_STARTING,
				  "irqchip/arm/gicv3:starting",
				  gic_starting_cpu, शून्य);

	/* Register all 8 non-secure SGIs */
	base_sgi = __irq_करोमुख्य_alloc_irqs(gic_data.करोमुख्य, -1, 8,
					   NUMA_NO_NODE, &sgi_fwspec,
					   false, शून्य);
	अगर (WARN_ON(base_sgi <= 0))
		वापस;

	set_smp_ipi_range(base_sgi, 8);
पूर्ण

अटल पूर्णांक gic_set_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *mask_val,
			    bool क्रमce)
अणु
	अचिन्हित पूर्णांक cpu;
	u32 offset, index;
	व्योम __iomem *reg;
	पूर्णांक enabled;
	u64 val;

	अगर (क्रमce)
		cpu = cpumask_first(mask_val);
	अन्यथा
		cpu = cpumask_any_and(mask_val, cpu_online_mask);

	अगर (cpu >= nr_cpu_ids)
		वापस -EINVAL;

	अगर (gic_irq_in_rdist(d))
		वापस -EINVAL;

	/* If पूर्णांकerrupt was enabled, disable it first */
	enabled = gic_peek_irq(d, GICD_ISENABLER);
	अगर (enabled)
		gic_mask_irq(d);

	offset = convert_offset_index(d, GICD_IROUTER, &index);
	reg = gic_dist_base(d) + offset + (index * 8);
	val = gic_mpidr_to_affinity(cpu_logical_map(cpu));

	gic_ग_लिखो_irouter(val, reg);

	/*
	 * If the पूर्णांकerrupt was enabled, enabled it again. Otherwise,
	 * just रुको क्रम the distributor to have digested our changes.
	 */
	अगर (enabled)
		gic_unmask_irq(d);
	अन्यथा
		gic_dist_रुको_क्रम_rwp();

	irq_data_update_effective_affinity(d, cpumask_of(cpu));

	वापस IRQ_SET_MASK_OK_DONE;
पूर्ण
#अन्यथा
#घोषणा gic_set_affinity	शून्य
#घोषणा gic_ipi_send_mask	शून्य
#घोषणा gic_smp_init()		करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल पूर्णांक gic_retrigger(काष्ठा irq_data *data)
अणु
	वापस !gic_irq_set_irqchip_state(data, IRQCHIP_STATE_PENDING, true);
पूर्ण

#अगर_घोषित CONFIG_CPU_PM
अटल पूर्णांक gic_cpu_pm_notअगरier(काष्ठा notअगरier_block *self,
			       अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	अगर (cmd == CPU_PM_EXIT) अणु
		अगर (gic_dist_security_disabled())
			gic_enable_redist(true);
		gic_cpu_sys_reg_init();
	पूर्ण अन्यथा अगर (cmd == CPU_PM_ENTER && gic_dist_security_disabled()) अणु
		gic_ग_लिखो_grpen1(0);
		gic_enable_redist(false);
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block gic_cpu_pm_notअगरier_block = अणु
	.notअगरier_call = gic_cpu_pm_notअगरier,
पूर्ण;

अटल व्योम gic_cpu_pm_init(व्योम)
अणु
	cpu_pm_रेजिस्टर_notअगरier(&gic_cpu_pm_notअगरier_block);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम gic_cpu_pm_init(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_PM */

अटल काष्ठा irq_chip gic_chip = अणु
	.name			= "GICv3",
	.irq_mask		= gic_mask_irq,
	.irq_unmask		= gic_unmask_irq,
	.irq_eoi		= gic_eoi_irq,
	.irq_set_type		= gic_set_type,
	.irq_set_affinity	= gic_set_affinity,
	.irq_retrigger          = gic_retrigger,
	.irq_get_irqchip_state	= gic_irq_get_irqchip_state,
	.irq_set_irqchip_state	= gic_irq_set_irqchip_state,
	.irq_nmi_setup		= gic_irq_nmi_setup,
	.irq_nmi_tearकरोwn	= gic_irq_nmi_tearकरोwn,
	.ipi_send_mask		= gic_ipi_send_mask,
	.flags			= IRQCHIP_SET_TYPE_MASKED |
				  IRQCHIP_SKIP_SET_WAKE |
				  IRQCHIP_MASK_ON_SUSPEND,
पूर्ण;

अटल काष्ठा irq_chip gic_eoimode1_chip = अणु
	.name			= "GICv3",
	.irq_mask		= gic_eoimode1_mask_irq,
	.irq_unmask		= gic_unmask_irq,
	.irq_eoi		= gic_eoimode1_eoi_irq,
	.irq_set_type		= gic_set_type,
	.irq_set_affinity	= gic_set_affinity,
	.irq_retrigger          = gic_retrigger,
	.irq_get_irqchip_state	= gic_irq_get_irqchip_state,
	.irq_set_irqchip_state	= gic_irq_set_irqchip_state,
	.irq_set_vcpu_affinity	= gic_irq_set_vcpu_affinity,
	.irq_nmi_setup		= gic_irq_nmi_setup,
	.irq_nmi_tearकरोwn	= gic_irq_nmi_tearकरोwn,
	.ipi_send_mask		= gic_ipi_send_mask,
	.flags			= IRQCHIP_SET_TYPE_MASKED |
				  IRQCHIP_SKIP_SET_WAKE |
				  IRQCHIP_MASK_ON_SUSPEND,
पूर्ण;

अटल पूर्णांक gic_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
			      irq_hw_number_t hw)
अणु
	काष्ठा irq_chip *chip = &gic_chip;
	काष्ठा irq_data *irqd = irq_desc_get_irq_data(irq_to_desc(irq));

	अगर (अटल_branch_likely(&supports_deactivate_key))
		chip = &gic_eoimode1_chip;

	चयन (__get_पूर्णांकid_range(hw)) अणु
	हाल SGI_RANGE:
	हाल PPI_RANGE:
	हाल EPPI_RANGE:
		irq_set_percpu_devid(irq);
		irq_करोमुख्य_set_info(d, irq, hw, chip, d->host_data,
				    handle_percpu_devid_irq, शून्य, शून्य);
		अवरोध;

	हाल SPI_RANGE:
	हाल ESPI_RANGE:
		irq_करोमुख्य_set_info(d, irq, hw, chip, d->host_data,
				    handle_fasteoi_irq, शून्य, शून्य);
		irq_set_probe(irq);
		irqd_set_single_target(irqd);
		अवरोध;

	हाल LPI_RANGE:
		अगर (!gic_dist_supports_lpis())
			वापस -EPERM;
		irq_करोमुख्य_set_info(d, irq, hw, chip, d->host_data,
				    handle_fasteoi_irq, शून्य, शून्य);
		अवरोध;

	शेष:
		वापस -EPERM;
	पूर्ण

	/* Prevents SW retriggers which mess up the ACK/EOI ordering */
	irqd_set_handle_enक्रमce_irqctx(irqd);
	वापस 0;
पूर्ण

अटल पूर्णांक gic_irq_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
				    काष्ठा irq_fwspec *fwspec,
				    अचिन्हित दीर्घ *hwirq,
				    अचिन्हित पूर्णांक *type)
अणु
	अगर (fwspec->param_count == 1 && fwspec->param[0] < 16) अणु
		*hwirq = fwspec->param[0];
		*type = IRQ_TYPE_EDGE_RISING;
		वापस 0;
	पूर्ण

	अगर (is_of_node(fwspec->fwnode)) अणु
		अगर (fwspec->param_count < 3)
			वापस -EINVAL;

		चयन (fwspec->param[0]) अणु
		हाल 0:			/* SPI */
			*hwirq = fwspec->param[1] + 32;
			अवरोध;
		हाल 1:			/* PPI */
			*hwirq = fwspec->param[1] + 16;
			अवरोध;
		हाल 2:			/* ESPI */
			*hwirq = fwspec->param[1] + ESPI_BASE_INTID;
			अवरोध;
		हाल 3:			/* EPPI */
			*hwirq = fwspec->param[1] + EPPI_BASE_INTID;
			अवरोध;
		हाल GIC_IRQ_TYPE_LPI:	/* LPI */
			*hwirq = fwspec->param[1];
			अवरोध;
		हाल GIC_IRQ_TYPE_PARTITION:
			*hwirq = fwspec->param[1];
			अगर (fwspec->param[1] >= 16)
				*hwirq += EPPI_BASE_INTID - 16;
			अन्यथा
				*hwirq += 16;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;

		/*
		 * Make it clear that broken DTs are... broken.
		 * Partitioned PPIs are an unक्रमtunate exception.
		 */
		WARN_ON(*type == IRQ_TYPE_NONE &&
			fwspec->param[0] != GIC_IRQ_TYPE_PARTITION);
		वापस 0;
	पूर्ण

	अगर (is_fwnode_irqchip(fwspec->fwnode)) अणु
		अगर(fwspec->param_count != 2)
			वापस -EINVAL;

		*hwirq = fwspec->param[0];
		*type = fwspec->param[1];

		WARN_ON(*type == IRQ_TYPE_NONE);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gic_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	पूर्णांक i, ret;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type = IRQ_TYPE_NONE;
	काष्ठा irq_fwspec *fwspec = arg;

	ret = gic_irq_करोमुख्य_translate(करोमुख्य, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		ret = gic_irq_करोमुख्य_map(करोमुख्य, virq + i, hwirq + i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gic_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				अचिन्हित पूर्णांक nr_irqs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq + i);
		irq_set_handler(virq + i, शून्य);
		irq_करोमुख्य_reset_irq_data(d);
	पूर्ण
पूर्ण

अटल पूर्णांक gic_irq_करोमुख्य_select(काष्ठा irq_करोमुख्य *d,
				 काष्ठा irq_fwspec *fwspec,
				 क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	/* Not क्रम us */
        अगर (fwspec->fwnode != d->fwnode)
		वापस 0;

	/* If this is not DT, then we have a single करोमुख्य */
	अगर (!is_of_node(fwspec->fwnode))
		वापस 1;

	/*
	 * If this is a PPI and we have a 4th (non-null) parameter,
	 * then we need to match the partition करोमुख्य.
	 */
	अगर (fwspec->param_count >= 4 &&
	    fwspec->param[0] == 1 && fwspec->param[3] != 0 &&
	    gic_data.ppi_descs)
		वापस d == partition_get_करोमुख्य(gic_data.ppi_descs[fwspec->param[1]]);

	वापस d == gic_data.करोमुख्य;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops gic_irq_करोमुख्य_ops = अणु
	.translate = gic_irq_करोमुख्य_translate,
	.alloc = gic_irq_करोमुख्य_alloc,
	.मुक्त = gic_irq_करोमुख्य_मुक्त,
	.select = gic_irq_करोमुख्य_select,
पूर्ण;

अटल पूर्णांक partition_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
				      काष्ठा irq_fwspec *fwspec,
				      अचिन्हित दीर्घ *hwirq,
				      अचिन्हित पूर्णांक *type)
अणु
	काष्ठा device_node *np;
	पूर्णांक ret;

	अगर (!gic_data.ppi_descs)
		वापस -ENOMEM;

	np = of_find_node_by_phandle(fwspec->param[3]);
	अगर (WARN_ON(!np))
		वापस -EINVAL;

	ret = partition_translate_id(gic_data.ppi_descs[fwspec->param[1]],
				     of_node_to_fwnode(np));
	अगर (ret < 0)
		वापस ret;

	*hwirq = ret;
	*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops partition_करोमुख्य_ops = अणु
	.translate = partition_करोमुख्य_translate,
	.select = gic_irq_करोमुख्य_select,
पूर्ण;

अटल bool gic_enable_quirk_msm8996(व्योम *data)
अणु
	काष्ठा gic_chip_data *d = data;

	d->flags |= FLAGS_WORKAROUND_GICR_WAKER_MSM8996;

	वापस true;
पूर्ण

अटल bool gic_enable_quirk_cavium_38539(व्योम *data)
अणु
	काष्ठा gic_chip_data *d = data;

	d->flags |= FLAGS_WORKAROUND_CAVIUM_ERRATUM_38539;

	वापस true;
पूर्ण

अटल bool gic_enable_quirk_hip06_07(व्योम *data)
अणु
	काष्ठा gic_chip_data *d = data;

	/*
	 * HIP06 GICD_IIDR clashes with GIC-600 product number (despite
	 * not being an actual ARM implementation). The saving grace is
	 * that GIC-600 करोesn't have ESPI, so nothing to करो in that हाल.
	 * HIP07 करोesn't even have a proper IIDR, and still pretends to
	 * have ESPI. In both हालs, put them right.
	 */
	अगर (d->rdists.gicd_typer & GICD_TYPER_ESPI) अणु
		/* Zero both ESPI and the RES0 field next to it... */
		d->rdists.gicd_typer &= ~GENMASK(9, 8);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा gic_quirk gic_quirks[] = अणु
	अणु
		.desc	= "GICv3: Qualcomm MSM8996 broken firmware",
		.compatible = "qcom,msm8996-gic-v3",
		.init	= gic_enable_quirk_msm8996,
	पूर्ण,
	अणु
		.desc	= "GICv3: HIP06 erratum 161010803",
		.iidr	= 0x0204043b,
		.mask	= 0xffffffff,
		.init	= gic_enable_quirk_hip06_07,
	पूर्ण,
	अणु
		.desc	= "GICv3: HIP07 erratum 161010803",
		.iidr	= 0x00000000,
		.mask	= 0xffffffff,
		.init	= gic_enable_quirk_hip06_07,
	पूर्ण,
	अणु
		/*
		 * Reserved रेजिस्टर accesses generate a Synchronous
		 * External Abort. This erratum applies to:
		 * - ThunderX: CN88xx
		 * - OCTEON TX: CN83xx, CN81xx
		 * - OCTEON TX2: CN93xx, CN96xx, CN98xx, CNF95xx*
		 */
		.desc	= "GICv3: Cavium erratum 38539",
		.iidr	= 0xa000034c,
		.mask	= 0xe8f00fff,
		.init	= gic_enable_quirk_cavium_38539,
	पूर्ण,
	अणु
	पूर्ण
पूर्ण;

अटल व्योम gic_enable_nmi_support(व्योम)
अणु
	पूर्णांक i;

	अगर (!gic_prio_masking_enabled())
		वापस;

	ppi_nmi_refs = kसुस्मृति(gic_data.ppi_nr, माप(*ppi_nmi_refs), GFP_KERNEL);
	अगर (!ppi_nmi_refs)
		वापस;

	क्रम (i = 0; i < gic_data.ppi_nr; i++)
		refcount_set(&ppi_nmi_refs[i], 0);

	/*
	 * Linux itself करोesn't use 1:N distribution, so has no need to
	 * set PMHE. The only reason to have it set is अगर EL3 requires it
	 * (and we can't change it).
	 */
	अगर (gic_पढ़ो_ctlr() & ICC_CTLR_EL1_PMHE_MASK)
		अटल_branch_enable(&gic_pmr_sync);

	pr_info("Pseudo-NMIs enabled using %s ICC_PMR_EL1 synchronisation\n",
		अटल_branch_unlikely(&gic_pmr_sync) ? "forced" : "relaxed");

	/*
	 * How priority values are used by the GIC depends on two things:
	 * the security state of the GIC (controlled by the GICD_CTRL.DS bit)
	 * and अगर Group 0 पूर्णांकerrupts can be delivered to Linux in the non-secure
	 * world as FIQs (controlled by the SCR_EL3.FIQ bit). These affect the
	 * the ICC_PMR_EL1 रेजिस्टर and the priority that software assigns to
	 * पूर्णांकerrupts:
	 *
	 * GICD_CTRL.DS | SCR_EL3.FIQ | ICC_PMR_EL1 | Group 1 priority
	 * -----------------------------------------------------------
	 *      1       |      -      |  unchanged  |    unchanged
	 * -----------------------------------------------------------
	 *      0       |      1      |  non-secure |    non-secure
	 * -----------------------------------------------------------
	 *      0       |      0      |  unchanged  |    non-secure
	 *
	 * where non-secure means that the value is right-shअगरted by one and the
	 * MSB bit set, to make it fit in the non-secure priority range.
	 *
	 * In the first two हालs, where ICC_PMR_EL1 and the पूर्णांकerrupt priority
	 * are both either modअगरied or unchanged, we can use the same set of
	 * priorities.
	 *
	 * In the last हाल, where only the पूर्णांकerrupt priorities are modअगरied to
	 * be in the non-secure range, we use a dअगरferent PMR value to mask IRQs
	 * and the rest of the values that we use reमुख्य unchanged.
	 */
	अगर (gic_has_group0() && !gic_dist_security_disabled())
		अटल_branch_enable(&gic_nonsecure_priorities);

	अटल_branch_enable(&supports_pseuकरो_nmis);

	अगर (अटल_branch_likely(&supports_deactivate_key))
		gic_eoimode1_chip.flags |= IRQCHIP_SUPPORTS_NMI;
	अन्यथा
		gic_chip.flags |= IRQCHIP_SUPPORTS_NMI;
पूर्ण

अटल पूर्णांक __init gic_init_bases(व्योम __iomem *dist_base,
				 काष्ठा redist_region *rdist_regs,
				 u32 nr_redist_regions,
				 u64 redist_stride,
				 काष्ठा fwnode_handle *handle)
अणु
	u32 typer;
	पूर्णांक err;

	अगर (!is_hyp_mode_available())
		अटल_branch_disable(&supports_deactivate_key);

	अगर (अटल_branch_likely(&supports_deactivate_key))
		pr_info("GIC: Using split EOI/Deactivate mode\n");

	gic_data.fwnode = handle;
	gic_data.dist_base = dist_base;
	gic_data.redist_regions = rdist_regs;
	gic_data.nr_redist_regions = nr_redist_regions;
	gic_data.redist_stride = redist_stride;

	/*
	 * Find out how many पूर्णांकerrupts are supported.
	 */
	typer = पढ़ोl_relaxed(gic_data.dist_base + GICD_TYPER);
	gic_data.rdists.gicd_typer = typer;

	gic_enable_quirks(पढ़ोl_relaxed(gic_data.dist_base + GICD_IIDR),
			  gic_quirks, &gic_data);

	pr_info("%d SPIs implemented\n", GIC_LINE_NR - 32);
	pr_info("%d Extended SPIs implemented\n", GIC_ESPI_NR);

	/*
	 * ThunderX1 explodes on पढ़ोing GICD_TYPER2, in violation of the
	 * architecture spec (which says that reserved रेजिस्टरs are RES0).
	 */
	अगर (!(gic_data.flags & FLAGS_WORKAROUND_CAVIUM_ERRATUM_38539))
		gic_data.rdists.gicd_typer2 = पढ़ोl_relaxed(gic_data.dist_base + GICD_TYPER2);

	gic_data.करोमुख्य = irq_करोमुख्य_create_tree(handle, &gic_irq_करोमुख्य_ops,
						 &gic_data);
	gic_data.rdists.rdist = alloc_percpu(typeof(*gic_data.rdists.rdist));
	gic_data.rdists.has_rvpeid = true;
	gic_data.rdists.has_vlpis = true;
	gic_data.rdists.has_direct_lpi = true;
	gic_data.rdists.has_vpend_valid_dirty = true;

	अगर (WARN_ON(!gic_data.करोमुख्य) || WARN_ON(!gic_data.rdists.rdist)) अणु
		err = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	irq_करोमुख्य_update_bus_token(gic_data.करोमुख्य, DOMAIN_BUS_WIRED);

	gic_data.has_rss = !!(typer & GICD_TYPER_RSS);
	pr_info("Distributor has %sRange Selector support\n",
		gic_data.has_rss ? "" : "no ");

	अगर (typer & GICD_TYPER_MBIS) अणु
		err = mbi_init(handle, gic_data.करोमुख्य);
		अगर (err)
			pr_err("Failed to initialize MBIs\n");
	पूर्ण

	set_handle_irq(gic_handle_irq);

	gic_update_rdist_properties();

	gic_dist_init();
	gic_cpu_init();
	gic_smp_init();
	gic_cpu_pm_init();

	अगर (gic_dist_supports_lpis()) अणु
		its_init(handle, &gic_data.rdists, gic_data.करोमुख्य);
		its_cpu_init();
	पूर्ण अन्यथा अणु
		अगर (IS_ENABLED(CONFIG_ARM_GIC_V2M))
			gicv2m_init(handle, gic_data.करोमुख्य);
	पूर्ण

	gic_enable_nmi_support();

	वापस 0;

out_मुक्त:
	अगर (gic_data.करोमुख्य)
		irq_करोमुख्य_हटाओ(gic_data.करोमुख्य);
	मुक्त_percpu(gic_data.rdists.rdist);
	वापस err;
पूर्ण

अटल पूर्णांक __init gic_validate_dist_version(व्योम __iomem *dist_base)
अणु
	u32 reg = पढ़ोl_relaxed(dist_base + GICD_PIDR2) & GIC_PIDR2_ARCH_MASK;

	अगर (reg != GIC_PIDR2_ARCH_GICv3 && reg != GIC_PIDR2_ARCH_GICv4)
		वापस -ENODEV;

	वापस 0;
पूर्ण

/* Create all possible partitions at boot समय */
अटल व्योम __init gic_populate_ppi_partitions(काष्ठा device_node *gic_node)
अणु
	काष्ठा device_node *parts_node, *child_part;
	पूर्णांक part_idx = 0, i;
	पूर्णांक nr_parts;
	काष्ठा partition_affinity *parts;

	parts_node = of_get_child_by_name(gic_node, "ppi-partitions");
	अगर (!parts_node)
		वापस;

	gic_data.ppi_descs = kसुस्मृति(gic_data.ppi_nr, माप(*gic_data.ppi_descs), GFP_KERNEL);
	अगर (!gic_data.ppi_descs)
		वापस;

	nr_parts = of_get_child_count(parts_node);

	अगर (!nr_parts)
		जाओ out_put_node;

	parts = kसुस्मृति(nr_parts, माप(*parts), GFP_KERNEL);
	अगर (WARN_ON(!parts))
		जाओ out_put_node;

	क्रम_each_child_of_node(parts_node, child_part) अणु
		काष्ठा partition_affinity *part;
		पूर्णांक n;

		part = &parts[part_idx];

		part->partition_id = of_node_to_fwnode(child_part);

		pr_info("GIC: PPI partition %pOFn[%d] { ",
			child_part, part_idx);

		n = of_property_count_elems_of_size(child_part, "affinity",
						    माप(u32));
		WARN_ON(n <= 0);

		क्रम (i = 0; i < n; i++) अणु
			पूर्णांक err, cpu;
			u32 cpu_phandle;
			काष्ठा device_node *cpu_node;

			err = of_property_पढ़ो_u32_index(child_part, "affinity",
							 i, &cpu_phandle);
			अगर (WARN_ON(err))
				जारी;

			cpu_node = of_find_node_by_phandle(cpu_phandle);
			अगर (WARN_ON(!cpu_node))
				जारी;

			cpu = of_cpu_node_to_id(cpu_node);
			अगर (WARN_ON(cpu < 0))
				जारी;

			pr_cont("%pOF[%d] ", cpu_node, cpu);

			cpumask_set_cpu(cpu, &part->mask);
		पूर्ण

		pr_cont("}\n");
		part_idx++;
	पूर्ण

	क्रम (i = 0; i < gic_data.ppi_nr; i++) अणु
		अचिन्हित पूर्णांक irq;
		काष्ठा partition_desc *desc;
		काष्ठा irq_fwspec ppi_fwspec = अणु
			.fwnode		= gic_data.fwnode,
			.param_count	= 3,
			.param		= अणु
				[0]	= GIC_IRQ_TYPE_PARTITION,
				[1]	= i,
				[2]	= IRQ_TYPE_NONE,
			पूर्ण,
		पूर्ण;

		irq = irq_create_fwspec_mapping(&ppi_fwspec);
		अगर (WARN_ON(!irq))
			जारी;
		desc = partition_create_desc(gic_data.fwnode, parts, nr_parts,
					     irq, &partition_करोमुख्य_ops);
		अगर (WARN_ON(!desc))
			जारी;

		gic_data.ppi_descs[i] = desc;
	पूर्ण

out_put_node:
	of_node_put(parts_node);
पूर्ण

अटल व्योम __init gic_of_setup_kvm_info(काष्ठा device_node *node)
अणु
	पूर्णांक ret;
	काष्ठा resource r;
	u32 gicv_idx;

	gic_v3_kvm_info.type = GIC_V3;

	gic_v3_kvm_info.मुख्यt_irq = irq_of_parse_and_map(node, 0);
	अगर (!gic_v3_kvm_info.मुख्यt_irq)
		वापस;

	अगर (of_property_पढ़ो_u32(node, "#redistributor-regions",
				 &gicv_idx))
		gicv_idx = 1;

	gicv_idx += 3;	/* Also skip GICD, GICC, GICH */
	ret = of_address_to_resource(node, gicv_idx, &r);
	अगर (!ret)
		gic_v3_kvm_info.vcpu = r;

	gic_v3_kvm_info.has_v4 = gic_data.rdists.has_vlpis;
	gic_v3_kvm_info.has_v4_1 = gic_data.rdists.has_rvpeid;
	gic_set_kvm_info(&gic_v3_kvm_info);
पूर्ण

अटल पूर्णांक __init gic_of_init(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	व्योम __iomem *dist_base;
	काष्ठा redist_region *rdist_regs;
	u64 redist_stride;
	u32 nr_redist_regions;
	पूर्णांक err, i;

	dist_base = of_iomap(node, 0);
	अगर (!dist_base) अणु
		pr_err("%pOF: unable to map gic dist registers\n", node);
		वापस -ENXIO;
	पूर्ण

	err = gic_validate_dist_version(dist_base);
	अगर (err) अणु
		pr_err("%pOF: no distributor detected, giving up\n", node);
		जाओ out_unmap_dist;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "#redistributor-regions", &nr_redist_regions))
		nr_redist_regions = 1;

	rdist_regs = kसुस्मृति(nr_redist_regions, माप(*rdist_regs),
			     GFP_KERNEL);
	अगर (!rdist_regs) अणु
		err = -ENOMEM;
		जाओ out_unmap_dist;
	पूर्ण

	क्रम (i = 0; i < nr_redist_regions; i++) अणु
		काष्ठा resource res;
		पूर्णांक ret;

		ret = of_address_to_resource(node, 1 + i, &res);
		rdist_regs[i].redist_base = of_iomap(node, 1 + i);
		अगर (ret || !rdist_regs[i].redist_base) अणु
			pr_err("%pOF: couldn't map region %d\n", node, i);
			err = -ENODEV;
			जाओ out_unmap_rdist;
		पूर्ण
		rdist_regs[i].phys_base = res.start;
	पूर्ण

	अगर (of_property_पढ़ो_u64(node, "redistributor-stride", &redist_stride))
		redist_stride = 0;

	gic_enable_of_quirks(node, gic_quirks, &gic_data);

	err = gic_init_bases(dist_base, rdist_regs, nr_redist_regions,
			     redist_stride, &node->fwnode);
	अगर (err)
		जाओ out_unmap_rdist;

	gic_populate_ppi_partitions(node);

	अगर (अटल_branch_likely(&supports_deactivate_key))
		gic_of_setup_kvm_info(node);
	वापस 0;

out_unmap_rdist:
	क्रम (i = 0; i < nr_redist_regions; i++)
		अगर (rdist_regs[i].redist_base)
			iounmap(rdist_regs[i].redist_base);
	kमुक्त(rdist_regs);
out_unmap_dist:
	iounmap(dist_base);
	वापस err;
पूर्ण

IRQCHIP_DECLARE(gic_v3, "arm,gic-v3", gic_of_init);

#अगर_घोषित CONFIG_ACPI
अटल काष्ठा
अणु
	व्योम __iomem *dist_base;
	काष्ठा redist_region *redist_regs;
	u32 nr_redist_regions;
	bool single_redist;
	पूर्णांक enabled_rdists;
	u32 मुख्यt_irq;
	पूर्णांक मुख्यt_irq_mode;
	phys_addr_t vcpu_base;
पूर्ण acpi_data __initdata;

अटल व्योम __init
gic_acpi_रेजिस्टर_redist(phys_addr_t phys_base, व्योम __iomem *redist_base)
अणु
	अटल पूर्णांक count = 0;

	acpi_data.redist_regs[count].phys_base = phys_base;
	acpi_data.redist_regs[count].redist_base = redist_base;
	acpi_data.redist_regs[count].single_redist = acpi_data.single_redist;
	count++;
पूर्ण

अटल पूर्णांक __init
gic_acpi_parse_madt_redist(जोड़ acpi_subtable_headers *header,
			   स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_generic_redistributor *redist =
			(काष्ठा acpi_madt_generic_redistributor *)header;
	व्योम __iomem *redist_base;

	redist_base = ioremap(redist->base_address, redist->length);
	अगर (!redist_base) अणु
		pr_err("Couldn't map GICR region @%llx\n", redist->base_address);
		वापस -ENOMEM;
	पूर्ण

	gic_acpi_रेजिस्टर_redist(redist->base_address, redist_base);
	वापस 0;
पूर्ण

अटल पूर्णांक __init
gic_acpi_parse_madt_gicc(जोड़ acpi_subtable_headers *header,
			 स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_generic_पूर्णांकerrupt *gicc =
				(काष्ठा acpi_madt_generic_पूर्णांकerrupt *)header;
	u32 reg = पढ़ोl_relaxed(acpi_data.dist_base + GICD_PIDR2) & GIC_PIDR2_ARCH_MASK;
	u32 size = reg == GIC_PIDR2_ARCH_GICv4 ? SZ_64K * 4 : SZ_64K * 2;
	व्योम __iomem *redist_base;

	/* GICC entry which has !ACPI_MADT_ENABLED is not unusable so skip */
	अगर (!(gicc->flags & ACPI_MADT_ENABLED))
		वापस 0;

	redist_base = ioremap(gicc->gicr_base_address, size);
	अगर (!redist_base)
		वापस -ENOMEM;

	gic_acpi_रेजिस्टर_redist(gicc->gicr_base_address, redist_base);
	वापस 0;
पूर्ण

अटल पूर्णांक __init gic_acpi_collect_gicr_base(व्योम)
अणु
	acpi_tbl_entry_handler redist_parser;
	क्रमागत acpi_madt_type type;

	अगर (acpi_data.single_redist) अणु
		type = ACPI_MADT_TYPE_GENERIC_INTERRUPT;
		redist_parser = gic_acpi_parse_madt_gicc;
	पूर्ण अन्यथा अणु
		type = ACPI_MADT_TYPE_GENERIC_REDISTRIBUTOR;
		redist_parser = gic_acpi_parse_madt_redist;
	पूर्ण

	/* Collect redistributor base addresses in GICR entries */
	अगर (acpi_table_parse_madt(type, redist_parser, 0) > 0)
		वापस 0;

	pr_info("No valid GICR entries exist\n");
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक __init gic_acpi_match_gicr(जोड़ acpi_subtable_headers *header,
				  स्थिर अचिन्हित दीर्घ end)
अणु
	/* Subtable presence means that redist exists, that's it */
	वापस 0;
पूर्ण

अटल पूर्णांक __init gic_acpi_match_gicc(जोड़ acpi_subtable_headers *header,
				      स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_generic_पूर्णांकerrupt *gicc =
				(काष्ठा acpi_madt_generic_पूर्णांकerrupt *)header;

	/*
	 * If GICC is enabled and has valid gicr base address, then it means
	 * GICR base is presented via GICC
	 */
	अगर ((gicc->flags & ACPI_MADT_ENABLED) && gicc->gicr_base_address) अणु
		acpi_data.enabled_rdists++;
		वापस 0;
	पूर्ण

	/*
	 * It's perfectly valid firmware can pass disabled GICC entry, driver
	 * should not treat as errors, skip the entry instead of probe fail.
	 */
	अगर (!(gicc->flags & ACPI_MADT_ENABLED))
		वापस 0;

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक __init gic_acpi_count_gicr_regions(व्योम)
अणु
	पूर्णांक count;

	/*
	 * Count how many redistributor regions we have. It is not allowed
	 * to mix redistributor description, GICR and GICC subtables have to be
	 * mutually exclusive.
	 */
	count = acpi_table_parse_madt(ACPI_MADT_TYPE_GENERIC_REDISTRIBUTOR,
				      gic_acpi_match_gicr, 0);
	अगर (count > 0) अणु
		acpi_data.single_redist = false;
		वापस count;
	पूर्ण

	count = acpi_table_parse_madt(ACPI_MADT_TYPE_GENERIC_INTERRUPT,
				      gic_acpi_match_gicc, 0);
	अगर (count > 0) अणु
		acpi_data.single_redist = true;
		count = acpi_data.enabled_rdists;
	पूर्ण

	वापस count;
पूर्ण

अटल bool __init acpi_validate_gic_table(काष्ठा acpi_subtable_header *header,
					   काष्ठा acpi_probe_entry *ape)
अणु
	काष्ठा acpi_madt_generic_distributor *dist;
	पूर्णांक count;

	dist = (काष्ठा acpi_madt_generic_distributor *)header;
	अगर (dist->version != ape->driver_data)
		वापस false;

	/* We need to करो that exercise anyway, the sooner the better */
	count = gic_acpi_count_gicr_regions();
	अगर (count <= 0)
		वापस false;

	acpi_data.nr_redist_regions = count;
	वापस true;
पूर्ण

अटल पूर्णांक __init gic_acpi_parse_virt_madt_gicc(जोड़ acpi_subtable_headers *header,
						स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_generic_पूर्णांकerrupt *gicc =
		(काष्ठा acpi_madt_generic_पूर्णांकerrupt *)header;
	पूर्णांक मुख्यt_irq_mode;
	अटल पूर्णांक first_madt = true;

	/* Skip unusable CPUs */
	अगर (!(gicc->flags & ACPI_MADT_ENABLED))
		वापस 0;

	मुख्यt_irq_mode = (gicc->flags & ACPI_MADT_VGIC_IRQ_MODE) ?
		ACPI_EDGE_SENSITIVE : ACPI_LEVEL_SENSITIVE;

	अगर (first_madt) अणु
		first_madt = false;

		acpi_data.मुख्यt_irq = gicc->vgic_पूर्णांकerrupt;
		acpi_data.मुख्यt_irq_mode = मुख्यt_irq_mode;
		acpi_data.vcpu_base = gicc->gicv_base_address;

		वापस 0;
	पूर्ण

	/*
	 * The मुख्यtenance पूर्णांकerrupt and GICV should be the same क्रम every CPU
	 */
	अगर ((acpi_data.मुख्यt_irq != gicc->vgic_पूर्णांकerrupt) ||
	    (acpi_data.मुख्यt_irq_mode != मुख्यt_irq_mode) ||
	    (acpi_data.vcpu_base != gicc->gicv_base_address))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल bool __init gic_acpi_collect_virt_info(व्योम)
अणु
	पूर्णांक count;

	count = acpi_table_parse_madt(ACPI_MADT_TYPE_GENERIC_INTERRUPT,
				      gic_acpi_parse_virt_madt_gicc, 0);

	वापस (count > 0);
पूर्ण

#घोषणा ACPI_GICV3_DIST_MEM_SIZE (SZ_64K)
#घोषणा ACPI_GICV2_VCTRL_MEM_SIZE	(SZ_4K)
#घोषणा ACPI_GICV2_VCPU_MEM_SIZE	(SZ_8K)

अटल व्योम __init gic_acpi_setup_kvm_info(व्योम)
अणु
	पूर्णांक irq;

	अगर (!gic_acpi_collect_virt_info()) अणु
		pr_warn("Unable to get hardware information used for virtualization\n");
		वापस;
	पूर्ण

	gic_v3_kvm_info.type = GIC_V3;

	irq = acpi_रेजिस्टर_gsi(शून्य, acpi_data.मुख्यt_irq,
				acpi_data.मुख्यt_irq_mode,
				ACPI_ACTIVE_HIGH);
	अगर (irq <= 0)
		वापस;

	gic_v3_kvm_info.मुख्यt_irq = irq;

	अगर (acpi_data.vcpu_base) अणु
		काष्ठा resource *vcpu = &gic_v3_kvm_info.vcpu;

		vcpu->flags = IORESOURCE_MEM;
		vcpu->start = acpi_data.vcpu_base;
		vcpu->end = vcpu->start + ACPI_GICV2_VCPU_MEM_SIZE - 1;
	पूर्ण

	gic_v3_kvm_info.has_v4 = gic_data.rdists.has_vlpis;
	gic_v3_kvm_info.has_v4_1 = gic_data.rdists.has_rvpeid;
	gic_set_kvm_info(&gic_v3_kvm_info);
पूर्ण

अटल पूर्णांक __init
gic_acpi_init(जोड़ acpi_subtable_headers *header, स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_generic_distributor *dist;
	काष्ठा fwnode_handle *करोमुख्य_handle;
	माप_प्रकार size;
	पूर्णांक i, err;

	/* Get distributor base address */
	dist = (काष्ठा acpi_madt_generic_distributor *)header;
	acpi_data.dist_base = ioremap(dist->base_address,
				      ACPI_GICV3_DIST_MEM_SIZE);
	अगर (!acpi_data.dist_base) अणु
		pr_err("Unable to map GICD registers\n");
		वापस -ENOMEM;
	पूर्ण

	err = gic_validate_dist_version(acpi_data.dist_base);
	अगर (err) अणु
		pr_err("No distributor detected at @%p, giving up\n",
		       acpi_data.dist_base);
		जाओ out_dist_unmap;
	पूर्ण

	size = माप(*acpi_data.redist_regs) * acpi_data.nr_redist_regions;
	acpi_data.redist_regs = kzalloc(size, GFP_KERNEL);
	अगर (!acpi_data.redist_regs) अणु
		err = -ENOMEM;
		जाओ out_dist_unmap;
	पूर्ण

	err = gic_acpi_collect_gicr_base();
	अगर (err)
		जाओ out_redist_unmap;

	करोमुख्य_handle = irq_करोमुख्य_alloc_fwnode(&dist->base_address);
	अगर (!करोमुख्य_handle) अणु
		err = -ENOMEM;
		जाओ out_redist_unmap;
	पूर्ण

	err = gic_init_bases(acpi_data.dist_base, acpi_data.redist_regs,
			     acpi_data.nr_redist_regions, 0, करोमुख्य_handle);
	अगर (err)
		जाओ out_fwhandle_मुक्त;

	acpi_set_irq_model(ACPI_IRQ_MODEL_GIC, करोमुख्य_handle);

	अगर (अटल_branch_likely(&supports_deactivate_key))
		gic_acpi_setup_kvm_info();

	वापस 0;

out_fwhandle_मुक्त:
	irq_करोमुख्य_मुक्त_fwnode(करोमुख्य_handle);
out_redist_unmap:
	क्रम (i = 0; i < acpi_data.nr_redist_regions; i++)
		अगर (acpi_data.redist_regs[i].redist_base)
			iounmap(acpi_data.redist_regs[i].redist_base);
	kमुक्त(acpi_data.redist_regs);
out_dist_unmap:
	iounmap(acpi_data.dist_base);
	वापस err;
पूर्ण
IRQCHIP_ACPI_DECLARE(gic_v3, ACPI_MADT_TYPE_GENERIC_DISTRIBUTOR,
		     acpi_validate_gic_table, ACPI_MADT_GIC_VERSION_V3,
		     gic_acpi_init);
IRQCHIP_ACPI_DECLARE(gic_v4, ACPI_MADT_TYPE_GENERIC_DISTRIBUTOR,
		     acpi_validate_gic_table, ACPI_MADT_GIC_VERSION_V4,
		     gic_acpi_init);
IRQCHIP_ACPI_DECLARE(gic_v3_or_v4, ACPI_MADT_TYPE_GENERIC_DISTRIBUTOR,
		     acpi_validate_gic_table, ACPI_MADT_GIC_VERSION_NONE,
		     gic_acpi_init);
#पूर्ण_अगर
