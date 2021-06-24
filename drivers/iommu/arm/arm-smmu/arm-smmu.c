<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IOMMU API क्रम ARM architected SMMU implementations.
 *
 * Copyright (C) 2013 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 *
 * This driver currently supports:
 *	- SMMUv1 and v2 implementations
 *	- Stream-matching and stream-indexing
 *	- v7/v8 दीर्घ-descriptor क्रमmat
 *	- Non-secure access to the SMMU
 *	- Context fault reporting
 *	- Extended Stream ID (16 bit)
 */

#घोषणा pr_fmt(fmt) "arm-smmu: " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/acpi_iort.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_iommu.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/ratelimit.h>
#समावेश <linux/slab.h>

#समावेश <linux/amba/bus.h>
#समावेश <linux/fsl/mc.h>

#समावेश "arm-smmu.h"

/*
 * Apparently, some Qualcomm arm64 platक्रमms which appear to expose their SMMU
 * global रेजिस्टर space are still, in fact, using a hypervisor to mediate it
 * by trapping and emulating रेजिस्टर accesses. Sadly, some deployed versions
 * of said trapping code have bugs wherein they go horribly wrong क्रम stores
 * using r31 (i.e. XZR/WZR) as the source रेजिस्टर.
 */
#घोषणा QCOM_DUMMY_VAL -1

#घोषणा MSI_IOVA_BASE			0x8000000
#घोषणा MSI_IOVA_LENGTH			0x100000

अटल पूर्णांक क्रमce_stage;
module_param(क्रमce_stage, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(क्रमce_stage,
	"Force SMMU mappings to be installed at a particular stage of translation. A value of '1' or '2' forces the corresponding stage. All other values are ignored (i.e. no stage is forced). Note that selecting a specific stage will disable support for nested translation.");
अटल bool disable_bypass =
	IS_ENABLED(CONFIG_ARM_SMMU_DISABLE_BYPASS_BY_DEFAULT);
module_param(disable_bypass, bool, S_IRUGO);
MODULE_PARM_DESC(disable_bypass,
	"Disable bypass streams such that incoming transactions from devices that are not attached to an iommu domain will report an abort back to the device and will not be allowed to pass through the SMMU.");

#घोषणा s2cr_init_val (काष्ठा arm_smmu_s2cr)अणु				\
	.type = disable_bypass ? S2CR_TYPE_FAULT : S2CR_TYPE_BYPASS,	\
पूर्ण

अटल bool using_legacy_binding, using_generic_binding;

अटल अंतरभूत पूर्णांक arm_smmu_rpm_get(काष्ठा arm_smmu_device *smmu)
अणु
	अगर (pm_runसमय_enabled(smmu->dev))
		वापस pm_runसमय_get_sync(smmu->dev);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम arm_smmu_rpm_put(काष्ठा arm_smmu_device *smmu)
अणु
	अगर (pm_runसमय_enabled(smmu->dev))
		pm_runसमय_put_स्वतःsuspend(smmu->dev);
पूर्ण

अटल काष्ठा arm_smmu_करोमुख्य *to_smmu_करोमुख्य(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा arm_smmu_करोमुख्य, करोमुख्य);
पूर्ण

अटल काष्ठा platक्रमm_driver arm_smmu_driver;
अटल काष्ठा iommu_ops arm_smmu_ops;

#अगर_घोषित CONFIG_ARM_SMMU_LEGACY_DT_BINDINGS
अटल पूर्णांक arm_smmu_bus_init(काष्ठा iommu_ops *ops);

अटल काष्ठा device_node *dev_get_dev_node(काष्ठा device *dev)
अणु
	अगर (dev_is_pci(dev)) अणु
		काष्ठा pci_bus *bus = to_pci_dev(dev)->bus;

		जबतक (!pci_is_root_bus(bus))
			bus = bus->parent;
		वापस of_node_get(bus->bridge->parent->of_node);
	पूर्ण

	वापस of_node_get(dev->of_node);
पूर्ण

अटल पूर्णांक __arm_smmu_get_pci_sid(काष्ठा pci_dev *pdev, u16 alias, व्योम *data)
अणु
	*((__be32 *)data) = cpu_to_be32(alias);
	वापस 0; /* Continue walking */
पूर्ण

अटल पूर्णांक __find_legacy_master_phandle(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा of_phandle_iterator *it = *(व्योम **)data;
	काष्ठा device_node *np = it->node;
	पूर्णांक err;

	of_क्रम_each_phandle(it, err, dev->of_node, "mmu-masters",
			    "#stream-id-cells", -1)
		अगर (it->node == np) अणु
			*(व्योम **)data = dev;
			वापस 1;
		पूर्ण
	it->node = np;
	वापस err == -ENOENT ? 0 : err;
पूर्ण

अटल पूर्णांक arm_smmu_रेजिस्टर_legacy_master(काष्ठा device *dev,
					   काष्ठा arm_smmu_device **smmu)
अणु
	काष्ठा device *smmu_dev;
	काष्ठा device_node *np;
	काष्ठा of_phandle_iterator it;
	व्योम *data = &it;
	u32 *sids;
	__be32 pci_sid;
	पूर्णांक err;

	np = dev_get_dev_node(dev);
	अगर (!np || !of_find_property(np, "#stream-id-cells", शून्य)) अणु
		of_node_put(np);
		वापस -ENODEV;
	पूर्ण

	it.node = np;
	err = driver_क्रम_each_device(&arm_smmu_driver.driver, शून्य, &data,
				     __find_legacy_master_phandle);
	smmu_dev = data;
	of_node_put(np);
	अगर (err == 0)
		वापस -ENODEV;
	अगर (err < 0)
		वापस err;

	अगर (dev_is_pci(dev)) अणु
		/* "mmu-masters" assumes Stream ID == Requester ID */
		pci_क्रम_each_dma_alias(to_pci_dev(dev), __arm_smmu_get_pci_sid,
				       &pci_sid);
		it.cur = &pci_sid;
		it.cur_count = 1;
	पूर्ण

	err = iommu_fwspec_init(dev, &smmu_dev->of_node->fwnode,
				&arm_smmu_ops);
	अगर (err)
		वापस err;

	sids = kसुस्मृति(it.cur_count, माप(*sids), GFP_KERNEL);
	अगर (!sids)
		वापस -ENOMEM;

	*smmu = dev_get_drvdata(smmu_dev);
	of_phandle_iterator_args(&it, sids, it.cur_count);
	err = iommu_fwspec_add_ids(dev, sids, it.cur_count);
	kमुक्त(sids);
	वापस err;
पूर्ण

/*
 * With the legacy DT binding in play, we have no guarantees about
 * probe order, but then we're also not करोing शेष करोमुख्यs, so we can
 * delay setting bus ops until we're sure every possible SMMU is पढ़ोy,
 * and that way ensure that no probe_device() calls get missed.
 */
अटल पूर्णांक arm_smmu_legacy_bus_init(व्योम)
अणु
	अगर (using_legacy_binding)
		वापस arm_smmu_bus_init(&arm_smmu_ops);
	वापस 0;
पूर्ण
device_initcall_sync(arm_smmu_legacy_bus_init);
#अन्यथा
अटल पूर्णांक arm_smmu_रेजिस्टर_legacy_master(काष्ठा device *dev,
					   काष्ठा arm_smmu_device **smmu)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARM_SMMU_LEGACY_DT_BINDINGS */

अटल व्योम __arm_smmu_मुक्त_biपंचांगap(अचिन्हित दीर्घ *map, पूर्णांक idx)
अणु
	clear_bit(idx, map);
पूर्ण

/* Wait क्रम any pending TLB invalidations to complete */
अटल व्योम __arm_smmu_tlb_sync(काष्ठा arm_smmu_device *smmu, पूर्णांक page,
				पूर्णांक sync, पूर्णांक status)
अणु
	अचिन्हित पूर्णांक spin_cnt, delay;
	u32 reg;

	अगर (smmu->impl && unlikely(smmu->impl->tlb_sync))
		वापस smmu->impl->tlb_sync(smmu, page, sync, status);

	arm_smmu_ग_लिखोl(smmu, page, sync, QCOM_DUMMY_VAL);
	क्रम (delay = 1; delay < TLB_LOOP_TIMEOUT; delay *= 2) अणु
		क्रम (spin_cnt = TLB_SPIN_COUNT; spin_cnt > 0; spin_cnt--) अणु
			reg = arm_smmu_पढ़ोl(smmu, page, status);
			अगर (!(reg & ARM_SMMU_sTLBGSTATUS_GSACTIVE))
				वापस;
			cpu_relax();
		पूर्ण
		udelay(delay);
	पूर्ण
	dev_err_ratelimited(smmu->dev,
			    "TLB sync timed out -- SMMU may be deadlocked\n");
पूर्ण

अटल व्योम arm_smmu_tlb_sync_global(काष्ठा arm_smmu_device *smmu)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&smmu->global_sync_lock, flags);
	__arm_smmu_tlb_sync(smmu, ARM_SMMU_GR0, ARM_SMMU_GR0_sTLBGSYNC,
			    ARM_SMMU_GR0_sTLBGSTATUS);
	spin_unlock_irqrestore(&smmu->global_sync_lock, flags);
पूर्ण

अटल व्योम arm_smmu_tlb_sync_context(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य)
अणु
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&smmu_करोमुख्य->cb_lock, flags);
	__arm_smmu_tlb_sync(smmu, ARM_SMMU_CB(smmu, smmu_करोमुख्य->cfg.cbndx),
			    ARM_SMMU_CB_TLBSYNC, ARM_SMMU_CB_TLBSTATUS);
	spin_unlock_irqrestore(&smmu_करोमुख्य->cb_lock, flags);
पूर्ण

अटल व्योम arm_smmu_tlb_inv_context_s1(व्योम *cookie)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = cookie;
	/*
	 * The TLBI ग_लिखो may be relaxed, so ensure that PTEs cleared by the
	 * current CPU are visible beक्रमehand.
	 */
	wmb();
	arm_smmu_cb_ग_लिखो(smmu_करोमुख्य->smmu, smmu_करोमुख्य->cfg.cbndx,
			  ARM_SMMU_CB_S1_TLBIASID, smmu_करोमुख्य->cfg.asid);
	arm_smmu_tlb_sync_context(smmu_करोमुख्य);
पूर्ण

अटल व्योम arm_smmu_tlb_inv_context_s2(व्योम *cookie)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = cookie;
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;

	/* See above */
	wmb();
	arm_smmu_gr0_ग_लिखो(smmu, ARM_SMMU_GR0_TLBIVMID, smmu_करोमुख्य->cfg.vmid);
	arm_smmu_tlb_sync_global(smmu);
पूर्ण

अटल व्योम arm_smmu_tlb_inv_range_s1(अचिन्हित दीर्घ iova, माप_प्रकार size,
				      माप_प्रकार granule, व्योम *cookie, पूर्णांक reg)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = cookie;
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;
	काष्ठा arm_smmu_cfg *cfg = &smmu_करोमुख्य->cfg;
	पूर्णांक idx = cfg->cbndx;

	अगर (smmu->features & ARM_SMMU_FEAT_COHERENT_WALK)
		wmb();

	अगर (cfg->fmt != ARM_SMMU_CTX_FMT_AARCH64) अणु
		iova = (iova >> 12) << 12;
		iova |= cfg->asid;
		करो अणु
			arm_smmu_cb_ग_लिखो(smmu, idx, reg, iova);
			iova += granule;
		पूर्ण जबतक (size -= granule);
	पूर्ण अन्यथा अणु
		iova >>= 12;
		iova |= (u64)cfg->asid << 48;
		करो अणु
			arm_smmu_cb_ग_लिखोq(smmu, idx, reg, iova);
			iova += granule >> 12;
		पूर्ण जबतक (size -= granule);
	पूर्ण
पूर्ण

अटल व्योम arm_smmu_tlb_inv_range_s2(अचिन्हित दीर्घ iova, माप_प्रकार size,
				      माप_प्रकार granule, व्योम *cookie, पूर्णांक reg)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = cookie;
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;
	पूर्णांक idx = smmu_करोमुख्य->cfg.cbndx;

	अगर (smmu->features & ARM_SMMU_FEAT_COHERENT_WALK)
		wmb();

	iova >>= 12;
	करो अणु
		अगर (smmu_करोमुख्य->cfg.fmt == ARM_SMMU_CTX_FMT_AARCH64)
			arm_smmu_cb_ग_लिखोq(smmu, idx, reg, iova);
		अन्यथा
			arm_smmu_cb_ग_लिखो(smmu, idx, reg, iova);
		iova += granule >> 12;
	पूर्ण जबतक (size -= granule);
पूर्ण

अटल व्योम arm_smmu_tlb_inv_walk_s1(अचिन्हित दीर्घ iova, माप_प्रकार size,
				     माप_प्रकार granule, व्योम *cookie)
अणु
	arm_smmu_tlb_inv_range_s1(iova, size, granule, cookie,
				  ARM_SMMU_CB_S1_TLBIVA);
	arm_smmu_tlb_sync_context(cookie);
पूर्ण

अटल व्योम arm_smmu_tlb_add_page_s1(काष्ठा iommu_iotlb_gather *gather,
				     अचिन्हित दीर्घ iova, माप_प्रकार granule,
				     व्योम *cookie)
अणु
	arm_smmu_tlb_inv_range_s1(iova, granule, granule, cookie,
				  ARM_SMMU_CB_S1_TLBIVAL);
पूर्ण

अटल व्योम arm_smmu_tlb_inv_walk_s2(अचिन्हित दीर्घ iova, माप_प्रकार size,
				     माप_प्रकार granule, व्योम *cookie)
अणु
	arm_smmu_tlb_inv_range_s2(iova, size, granule, cookie,
				  ARM_SMMU_CB_S2_TLBIIPAS2);
	arm_smmu_tlb_sync_context(cookie);
पूर्ण

अटल व्योम arm_smmu_tlb_add_page_s2(काष्ठा iommu_iotlb_gather *gather,
				     अचिन्हित दीर्घ iova, माप_प्रकार granule,
				     व्योम *cookie)
अणु
	arm_smmu_tlb_inv_range_s2(iova, granule, granule, cookie,
				  ARM_SMMU_CB_S2_TLBIIPAS2L);
पूर्ण

अटल व्योम arm_smmu_tlb_inv_walk_s2_v1(अचिन्हित दीर्घ iova, माप_प्रकार size,
					माप_प्रकार granule, व्योम *cookie)
अणु
	arm_smmu_tlb_inv_context_s2(cookie);
पूर्ण
/*
 * On MMU-401 at least, the cost of firing off multiple TLBIVMIDs appears
 * almost negligible, but the benefit of getting the first one in as far ahead
 * of the sync as possible is signअगरicant, hence we करोn't just make this a
 * no-op and call arm_smmu_tlb_inv_context_s2() from .iotlb_sync as you might
 * think.
 */
अटल व्योम arm_smmu_tlb_add_page_s2_v1(काष्ठा iommu_iotlb_gather *gather,
					अचिन्हित दीर्घ iova, माप_प्रकार granule,
					व्योम *cookie)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = cookie;
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;

	अगर (smmu->features & ARM_SMMU_FEAT_COHERENT_WALK)
		wmb();

	arm_smmu_gr0_ग_लिखो(smmu, ARM_SMMU_GR0_TLBIVMID, smmu_करोमुख्य->cfg.vmid);
पूर्ण

अटल स्थिर काष्ठा iommu_flush_ops arm_smmu_s1_tlb_ops = अणु
	.tlb_flush_all	= arm_smmu_tlb_inv_context_s1,
	.tlb_flush_walk	= arm_smmu_tlb_inv_walk_s1,
	.tlb_add_page	= arm_smmu_tlb_add_page_s1,
पूर्ण;

अटल स्थिर काष्ठा iommu_flush_ops arm_smmu_s2_tlb_ops_v2 = अणु
	.tlb_flush_all	= arm_smmu_tlb_inv_context_s2,
	.tlb_flush_walk	= arm_smmu_tlb_inv_walk_s2,
	.tlb_add_page	= arm_smmu_tlb_add_page_s2,
पूर्ण;

अटल स्थिर काष्ठा iommu_flush_ops arm_smmu_s2_tlb_ops_v1 = अणु
	.tlb_flush_all	= arm_smmu_tlb_inv_context_s2,
	.tlb_flush_walk	= arm_smmu_tlb_inv_walk_s2_v1,
	.tlb_add_page	= arm_smmu_tlb_add_page_s2_v1,
पूर्ण;

अटल irqवापस_t arm_smmu_context_fault(पूर्णांक irq, व्योम *dev)
अणु
	u32 fsr, fsynr, cbfrsynra;
	अचिन्हित दीर्घ iova;
	काष्ठा iommu_करोमुख्य *करोमुख्य = dev;
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;
	पूर्णांक idx = smmu_करोमुख्य->cfg.cbndx;

	fsr = arm_smmu_cb_पढ़ो(smmu, idx, ARM_SMMU_CB_FSR);
	अगर (!(fsr & ARM_SMMU_FSR_FAULT))
		वापस IRQ_NONE;

	fsynr = arm_smmu_cb_पढ़ो(smmu, idx, ARM_SMMU_CB_FSYNR0);
	iova = arm_smmu_cb_पढ़ोq(smmu, idx, ARM_SMMU_CB_FAR);
	cbfrsynra = arm_smmu_gr1_पढ़ो(smmu, ARM_SMMU_GR1_CBFRSYNRA(idx));

	dev_err_ratelimited(smmu->dev,
	"Unhandled context fault: fsr=0x%x, iova=0x%08lx, fsynr=0x%x, cbfrsynra=0x%x, cb=%d\n",
			    fsr, iova, fsynr, cbfrsynra, idx);

	arm_smmu_cb_ग_लिखो(smmu, idx, ARM_SMMU_CB_FSR, fsr);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t arm_smmu_global_fault(पूर्णांक irq, व्योम *dev)
अणु
	u32 gfsr, gfsynr0, gfsynr1, gfsynr2;
	काष्ठा arm_smmu_device *smmu = dev;
	अटल DEFINE_RATELIMIT_STATE(rs, DEFAULT_RATELIMIT_INTERVAL,
				      DEFAULT_RATELIMIT_BURST);

	gfsr = arm_smmu_gr0_पढ़ो(smmu, ARM_SMMU_GR0_sGFSR);
	gfsynr0 = arm_smmu_gr0_पढ़ो(smmu, ARM_SMMU_GR0_sGFSYNR0);
	gfsynr1 = arm_smmu_gr0_पढ़ो(smmu, ARM_SMMU_GR0_sGFSYNR1);
	gfsynr2 = arm_smmu_gr0_पढ़ो(smmu, ARM_SMMU_GR0_sGFSYNR2);

	अगर (!gfsr)
		वापस IRQ_NONE;

	अगर (__ratelimit(&rs)) अणु
		अगर (IS_ENABLED(CONFIG_ARM_SMMU_DISABLE_BYPASS_BY_DEFAULT) &&
		    (gfsr & ARM_SMMU_sGFSR_USF))
			dev_err(smmu->dev,
				"Blocked unknown Stream ID 0x%hx; boot with \"arm-smmu.disable_bypass=0\" to allow, but this may have security implications\n",
				(u16)gfsynr1);
		अन्यथा
			dev_err(smmu->dev,
				"Unexpected global fault, this could be serious\n");
		dev_err(smmu->dev,
			"\tGFSR 0x%08x, GFSYNR0 0x%08x, GFSYNR1 0x%08x, GFSYNR2 0x%08x\n",
			gfsr, gfsynr0, gfsynr1, gfsynr2);
	पूर्ण

	arm_smmu_gr0_ग_लिखो(smmu, ARM_SMMU_GR0_sGFSR, gfsr);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम arm_smmu_init_context_bank(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य,
				       काष्ठा io_pgtable_cfg *pgtbl_cfg)
अणु
	काष्ठा arm_smmu_cfg *cfg = &smmu_करोमुख्य->cfg;
	काष्ठा arm_smmu_cb *cb = &smmu_करोमुख्य->smmu->cbs[cfg->cbndx];
	bool stage1 = cfg->cbar != CBAR_TYPE_S2_TRANS;

	cb->cfg = cfg;

	/* TCR */
	अगर (stage1) अणु
		अगर (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH32_S) अणु
			cb->tcr[0] = pgtbl_cfg->arm_v7s_cfg.tcr;
		पूर्ण अन्यथा अणु
			cb->tcr[0] = arm_smmu_lpae_tcr(pgtbl_cfg);
			cb->tcr[1] = arm_smmu_lpae_tcr2(pgtbl_cfg);
			अगर (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH64)
				cb->tcr[1] |= ARM_SMMU_TCR2_AS;
			अन्यथा
				cb->tcr[0] |= ARM_SMMU_TCR_EAE;
		पूर्ण
	पूर्ण अन्यथा अणु
		cb->tcr[0] = arm_smmu_lpae_vtcr(pgtbl_cfg);
	पूर्ण

	/* TTBRs */
	अगर (stage1) अणु
		अगर (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH32_S) अणु
			cb->ttbr[0] = pgtbl_cfg->arm_v7s_cfg.ttbr;
			cb->ttbr[1] = 0;
		पूर्ण अन्यथा अणु
			cb->ttbr[0] = FIELD_PREP(ARM_SMMU_TTBRn_ASID,
						 cfg->asid);
			cb->ttbr[1] = FIELD_PREP(ARM_SMMU_TTBRn_ASID,
						 cfg->asid);

			अगर (pgtbl_cfg->quirks & IO_PGTABLE_QUIRK_ARM_TTBR1)
				cb->ttbr[1] |= pgtbl_cfg->arm_lpae_s1_cfg.ttbr;
			अन्यथा
				cb->ttbr[0] |= pgtbl_cfg->arm_lpae_s1_cfg.ttbr;
		पूर्ण
	पूर्ण अन्यथा अणु
		cb->ttbr[0] = pgtbl_cfg->arm_lpae_s2_cfg.vttbr;
	पूर्ण

	/* MAIRs (stage-1 only) */
	अगर (stage1) अणु
		अगर (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH32_S) अणु
			cb->mair[0] = pgtbl_cfg->arm_v7s_cfg.prrr;
			cb->mair[1] = pgtbl_cfg->arm_v7s_cfg.nmrr;
		पूर्ण अन्यथा अणु
			cb->mair[0] = pgtbl_cfg->arm_lpae_s1_cfg.mair;
			cb->mair[1] = pgtbl_cfg->arm_lpae_s1_cfg.mair >> 32;
		पूर्ण
	पूर्ण
पूर्ण

व्योम arm_smmu_ग_लिखो_context_bank(काष्ठा arm_smmu_device *smmu, पूर्णांक idx)
अणु
	u32 reg;
	bool stage1;
	काष्ठा arm_smmu_cb *cb = &smmu->cbs[idx];
	काष्ठा arm_smmu_cfg *cfg = cb->cfg;

	/* Unasचिन्हित context banks only need disabling */
	अगर (!cfg) अणु
		arm_smmu_cb_ग_लिखो(smmu, idx, ARM_SMMU_CB_SCTLR, 0);
		वापस;
	पूर्ण

	stage1 = cfg->cbar != CBAR_TYPE_S2_TRANS;

	/* CBA2R */
	अगर (smmu->version > ARM_SMMU_V1) अणु
		अगर (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH64)
			reg = ARM_SMMU_CBA2R_VA64;
		अन्यथा
			reg = 0;
		/* 16-bit VMIDs live in CBA2R */
		अगर (smmu->features & ARM_SMMU_FEAT_VMID16)
			reg |= FIELD_PREP(ARM_SMMU_CBA2R_VMID16, cfg->vmid);

		arm_smmu_gr1_ग_लिखो(smmu, ARM_SMMU_GR1_CBA2R(idx), reg);
	पूर्ण

	/* CBAR */
	reg = FIELD_PREP(ARM_SMMU_CBAR_TYPE, cfg->cbar);
	अगर (smmu->version < ARM_SMMU_V2)
		reg |= FIELD_PREP(ARM_SMMU_CBAR_IRPTNDX, cfg->irptndx);

	/*
	 * Use the weakest shareability/memory types, so they are
	 * overridden by the ttbcr/pte.
	 */
	अगर (stage1) अणु
		reg |= FIELD_PREP(ARM_SMMU_CBAR_S1_BPSHCFG,
				  ARM_SMMU_CBAR_S1_BPSHCFG_NSH) |
		       FIELD_PREP(ARM_SMMU_CBAR_S1_MEMATTR,
				  ARM_SMMU_CBAR_S1_MEMATTR_WB);
	पूर्ण अन्यथा अगर (!(smmu->features & ARM_SMMU_FEAT_VMID16)) अणु
		/* 8-bit VMIDs live in CBAR */
		reg |= FIELD_PREP(ARM_SMMU_CBAR_VMID, cfg->vmid);
	पूर्ण
	arm_smmu_gr1_ग_लिखो(smmu, ARM_SMMU_GR1_CBAR(idx), reg);

	/*
	 * TCR
	 * We must ग_लिखो this beक्रमe the TTBRs, since it determines the
	 * access behaviour of some fields (in particular, ASID[15:8]).
	 */
	अगर (stage1 && smmu->version > ARM_SMMU_V1)
		arm_smmu_cb_ग_लिखो(smmu, idx, ARM_SMMU_CB_TCR2, cb->tcr[1]);
	arm_smmu_cb_ग_लिखो(smmu, idx, ARM_SMMU_CB_TCR, cb->tcr[0]);

	/* TTBRs */
	अगर (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH32_S) अणु
		arm_smmu_cb_ग_लिखो(smmu, idx, ARM_SMMU_CB_CONTEXTIDR, cfg->asid);
		arm_smmu_cb_ग_लिखो(smmu, idx, ARM_SMMU_CB_TTBR0, cb->ttbr[0]);
		arm_smmu_cb_ग_लिखो(smmu, idx, ARM_SMMU_CB_TTBR1, cb->ttbr[1]);
	पूर्ण अन्यथा अणु
		arm_smmu_cb_ग_लिखोq(smmu, idx, ARM_SMMU_CB_TTBR0, cb->ttbr[0]);
		अगर (stage1)
			arm_smmu_cb_ग_लिखोq(smmu, idx, ARM_SMMU_CB_TTBR1,
					   cb->ttbr[1]);
	पूर्ण

	/* MAIRs (stage-1 only) */
	अगर (stage1) अणु
		arm_smmu_cb_ग_लिखो(smmu, idx, ARM_SMMU_CB_S1_MAIR0, cb->mair[0]);
		arm_smmu_cb_ग_लिखो(smmu, idx, ARM_SMMU_CB_S1_MAIR1, cb->mair[1]);
	पूर्ण

	/* SCTLR */
	reg = ARM_SMMU_SCTLR_CFIE | ARM_SMMU_SCTLR_CFRE | ARM_SMMU_SCTLR_AFE |
	      ARM_SMMU_SCTLR_TRE | ARM_SMMU_SCTLR_M;
	अगर (stage1)
		reg |= ARM_SMMU_SCTLR_S1_ASIDPNE;
	अगर (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		reg |= ARM_SMMU_SCTLR_E;

	अगर (smmu->impl && smmu->impl->ग_लिखो_sctlr)
		smmu->impl->ग_लिखो_sctlr(smmu, idx, reg);
	अन्यथा
		arm_smmu_cb_ग_लिखो(smmu, idx, ARM_SMMU_CB_SCTLR, reg);
पूर्ण

अटल पूर्णांक arm_smmu_alloc_context_bank(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य,
				       काष्ठा arm_smmu_device *smmu,
				       काष्ठा device *dev, अचिन्हित पूर्णांक start)
अणु
	अगर (smmu->impl && smmu->impl->alloc_context_bank)
		वापस smmu->impl->alloc_context_bank(smmu_करोमुख्य, smmu, dev, start);

	वापस __arm_smmu_alloc_biपंचांगap(smmu->context_map, start, smmu->num_context_banks);
पूर्ण

अटल पूर्णांक arm_smmu_init_करोमुख्य_context(काष्ठा iommu_करोमुख्य *करोमुख्य,
					काष्ठा arm_smmu_device *smmu,
					काष्ठा device *dev)
अणु
	पूर्णांक irq, start, ret = 0;
	अचिन्हित दीर्घ ias, oas;
	काष्ठा io_pgtable_ops *pgtbl_ops;
	काष्ठा io_pgtable_cfg pgtbl_cfg;
	क्रमागत io_pgtable_fmt fmt;
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);
	काष्ठा arm_smmu_cfg *cfg = &smmu_करोमुख्य->cfg;
	irqवापस_t (*context_fault)(पूर्णांक irq, व्योम *dev);

	mutex_lock(&smmu_करोमुख्य->init_mutex);
	अगर (smmu_करोमुख्य->smmu)
		जाओ out_unlock;

	अगर (करोमुख्य->type == IOMMU_DOMAIN_IDENTITY) अणु
		smmu_करोमुख्य->stage = ARM_SMMU_DOMAIN_BYPASS;
		smmu_करोमुख्य->smmu = smmu;
		जाओ out_unlock;
	पूर्ण

	/*
	 * Mapping the requested stage onto what we support is surprisingly
	 * complicated, मुख्यly because the spec allows S1+S2 SMMUs without
	 * support क्रम nested translation. That means we end up with the
	 * following table:
	 *
	 * Requested        Supported        Actual
	 *     S1               N              S1
	 *     S1             S1+S2            S1
	 *     S1               S2             S2
	 *     S1               S1             S1
	 *     N                N              N
	 *     N              S1+S2            S2
	 *     N                S2             S2
	 *     N                S1             S1
	 *
	 * Note that you can't actually request stage-2 mappings.
	 */
	अगर (!(smmu->features & ARM_SMMU_FEAT_TRANS_S1))
		smmu_करोमुख्य->stage = ARM_SMMU_DOMAIN_S2;
	अगर (!(smmu->features & ARM_SMMU_FEAT_TRANS_S2))
		smmu_करोमुख्य->stage = ARM_SMMU_DOMAIN_S1;

	/*
	 * Choosing a suitable context क्रमmat is even more fiddly. Until we
	 * grow some way क्रम the caller to express a preference, and/or move
	 * the decision पूर्णांकo the io-pgtable code where it arguably beदीर्घs,
	 * just aim क्रम the बंदst thing to the rest of the प्रणाली, and hope
	 * that the hardware isn't esoteric enough that we can't assume AArch64
	 * support to be a superset of AArch32 support...
	 */
	अगर (smmu->features & ARM_SMMU_FEAT_FMT_AARCH32_L)
		cfg->fmt = ARM_SMMU_CTX_FMT_AARCH32_L;
	अगर (IS_ENABLED(CONFIG_IOMMU_IO_PGTABLE_ARMV7S) &&
	    !IS_ENABLED(CONFIG_64BIT) && !IS_ENABLED(CONFIG_ARM_LPAE) &&
	    (smmu->features & ARM_SMMU_FEAT_FMT_AARCH32_S) &&
	    (smmu_करोमुख्य->stage == ARM_SMMU_DOMAIN_S1))
		cfg->fmt = ARM_SMMU_CTX_FMT_AARCH32_S;
	अगर ((IS_ENABLED(CONFIG_64BIT) || cfg->fmt == ARM_SMMU_CTX_FMT_NONE) &&
	    (smmu->features & (ARM_SMMU_FEAT_FMT_AARCH64_64K |
			       ARM_SMMU_FEAT_FMT_AARCH64_16K |
			       ARM_SMMU_FEAT_FMT_AARCH64_4K)))
		cfg->fmt = ARM_SMMU_CTX_FMT_AARCH64;

	अगर (cfg->fmt == ARM_SMMU_CTX_FMT_NONE) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	चयन (smmu_करोमुख्य->stage) अणु
	हाल ARM_SMMU_DOMAIN_S1:
		cfg->cbar = CBAR_TYPE_S1_TRANS_S2_BYPASS;
		start = smmu->num_s2_context_banks;
		ias = smmu->va_size;
		oas = smmu->ipa_size;
		अगर (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH64) अणु
			fmt = ARM_64_LPAE_S1;
		पूर्ण अन्यथा अगर (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH32_L) अणु
			fmt = ARM_32_LPAE_S1;
			ias = min(ias, 32UL);
			oas = min(oas, 40UL);
		पूर्ण अन्यथा अणु
			fmt = ARM_V7S;
			ias = min(ias, 32UL);
			oas = min(oas, 32UL);
		पूर्ण
		smmu_करोमुख्य->flush_ops = &arm_smmu_s1_tlb_ops;
		अवरोध;
	हाल ARM_SMMU_DOMAIN_NESTED:
		/*
		 * We will likely want to change this अगर/when KVM माला_लो
		 * involved.
		 */
	हाल ARM_SMMU_DOMAIN_S2:
		cfg->cbar = CBAR_TYPE_S2_TRANS;
		start = 0;
		ias = smmu->ipa_size;
		oas = smmu->pa_size;
		अगर (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH64) अणु
			fmt = ARM_64_LPAE_S2;
		पूर्ण अन्यथा अणु
			fmt = ARM_32_LPAE_S2;
			ias = min(ias, 40UL);
			oas = min(oas, 40UL);
		पूर्ण
		अगर (smmu->version == ARM_SMMU_V2)
			smmu_करोमुख्य->flush_ops = &arm_smmu_s2_tlb_ops_v2;
		अन्यथा
			smmu_करोमुख्य->flush_ops = &arm_smmu_s2_tlb_ops_v1;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	ret = arm_smmu_alloc_context_bank(smmu_करोमुख्य, smmu, dev, start);
	अगर (ret < 0) अणु
		जाओ out_unlock;
	पूर्ण

	smmu_करोमुख्य->smmu = smmu;

	cfg->cbndx = ret;
	अगर (smmu->version < ARM_SMMU_V2) अणु
		cfg->irptndx = atomic_inc_वापस(&smmu->irptndx);
		cfg->irptndx %= smmu->num_context_irqs;
	पूर्ण अन्यथा अणु
		cfg->irptndx = cfg->cbndx;
	पूर्ण

	अगर (smmu_करोमुख्य->stage == ARM_SMMU_DOMAIN_S2)
		cfg->vmid = cfg->cbndx + 1;
	अन्यथा
		cfg->asid = cfg->cbndx;

	pgtbl_cfg = (काष्ठा io_pgtable_cfg) अणु
		.pgsize_biपंचांगap	= smmu->pgsize_biपंचांगap,
		.ias		= ias,
		.oas		= oas,
		.coherent_walk	= smmu->features & ARM_SMMU_FEAT_COHERENT_WALK,
		.tlb		= smmu_करोमुख्य->flush_ops,
		.iommu_dev	= smmu->dev,
	पूर्ण;

	अगर (!iommu_get_dma_strict(करोमुख्य))
		pgtbl_cfg.quirks |= IO_PGTABLE_QUIRK_NON_STRICT;

	अगर (smmu->impl && smmu->impl->init_context) अणु
		ret = smmu->impl->init_context(smmu_करोमुख्य, &pgtbl_cfg, dev);
		अगर (ret)
			जाओ out_clear_smmu;
	पूर्ण

	अगर (smmu_करोमुख्य->pgtbl_quirks)
		pgtbl_cfg.quirks |= smmu_करोमुख्य->pgtbl_quirks;

	pgtbl_ops = alloc_io_pgtable_ops(fmt, &pgtbl_cfg, smmu_करोमुख्य);
	अगर (!pgtbl_ops) अणु
		ret = -ENOMEM;
		जाओ out_clear_smmu;
	पूर्ण

	/* Update the करोमुख्य's page sizes to reflect the page table क्रमmat */
	करोमुख्य->pgsize_biपंचांगap = pgtbl_cfg.pgsize_biपंचांगap;

	अगर (pgtbl_cfg.quirks & IO_PGTABLE_QUIRK_ARM_TTBR1) अणु
		करोमुख्य->geometry.aperture_start = ~0UL << ias;
		करोमुख्य->geometry.aperture_end = ~0UL;
	पूर्ण अन्यथा अणु
		करोमुख्य->geometry.aperture_end = (1UL << ias) - 1;
	पूर्ण

	करोमुख्य->geometry.क्रमce_aperture = true;

	/* Initialise the context bank with our page table cfg */
	arm_smmu_init_context_bank(smmu_करोमुख्य, &pgtbl_cfg);
	arm_smmu_ग_लिखो_context_bank(smmu, cfg->cbndx);

	/*
	 * Request context fault पूर्णांकerrupt. Do this last to aव्योम the
	 * handler seeing a half-initialised करोमुख्य state.
	 */
	irq = smmu->irqs[smmu->num_global_irqs + cfg->irptndx];

	अगर (smmu->impl && smmu->impl->context_fault)
		context_fault = smmu->impl->context_fault;
	अन्यथा
		context_fault = arm_smmu_context_fault;

	ret = devm_request_irq(smmu->dev, irq, context_fault,
			       IRQF_SHARED, "arm-smmu-context-fault", करोमुख्य);
	अगर (ret < 0) अणु
		dev_err(smmu->dev, "failed to request context IRQ %d (%u)\n",
			cfg->irptndx, irq);
		cfg->irptndx = ARM_SMMU_INVALID_IRPTNDX;
	पूर्ण

	mutex_unlock(&smmu_करोमुख्य->init_mutex);

	/* Publish page table ops क्रम map/unmap */
	smmu_करोमुख्य->pgtbl_ops = pgtbl_ops;
	वापस 0;

out_clear_smmu:
	__arm_smmu_मुक्त_biपंचांगap(smmu->context_map, cfg->cbndx);
	smmu_करोमुख्य->smmu = शून्य;
out_unlock:
	mutex_unlock(&smmu_करोमुख्य->init_mutex);
	वापस ret;
पूर्ण

अटल व्योम arm_smmu_destroy_करोमुख्य_context(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;
	काष्ठा arm_smmu_cfg *cfg = &smmu_करोमुख्य->cfg;
	पूर्णांक ret, irq;

	अगर (!smmu || करोमुख्य->type == IOMMU_DOMAIN_IDENTITY)
		वापस;

	ret = arm_smmu_rpm_get(smmu);
	अगर (ret < 0)
		वापस;

	/*
	 * Disable the context bank and मुक्त the page tables beक्रमe मुक्तing
	 * it.
	 */
	smmu->cbs[cfg->cbndx].cfg = शून्य;
	arm_smmu_ग_लिखो_context_bank(smmu, cfg->cbndx);

	अगर (cfg->irptndx != ARM_SMMU_INVALID_IRPTNDX) अणु
		irq = smmu->irqs[smmu->num_global_irqs + cfg->irptndx];
		devm_मुक्त_irq(smmu->dev, irq, करोमुख्य);
	पूर्ण

	मुक्त_io_pgtable_ops(smmu_करोमुख्य->pgtbl_ops);
	__arm_smmu_मुक्त_biपंचांगap(smmu->context_map, cfg->cbndx);

	arm_smmu_rpm_put(smmu);
पूर्ण

अटल काष्ठा iommu_करोमुख्य *arm_smmu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य;

	अगर (type != IOMMU_DOMAIN_UNMANAGED &&
	    type != IOMMU_DOMAIN_DMA &&
	    type != IOMMU_DOMAIN_IDENTITY)
		वापस शून्य;
	/*
	 * Allocate the करोमुख्य and initialise some of its data काष्ठाures.
	 * We can't really do anything meaningful until we've added a
	 * master.
	 */
	smmu_करोमुख्य = kzalloc(माप(*smmu_करोमुख्य), GFP_KERNEL);
	अगर (!smmu_करोमुख्य)
		वापस शून्य;

	अगर (type == IOMMU_DOMAIN_DMA && (using_legacy_binding ||
	    iommu_get_dma_cookie(&smmu_करोमुख्य->करोमुख्य))) अणु
		kमुक्त(smmu_करोमुख्य);
		वापस शून्य;
	पूर्ण

	mutex_init(&smmu_करोमुख्य->init_mutex);
	spin_lock_init(&smmu_करोमुख्य->cb_lock);

	वापस &smmu_करोमुख्य->करोमुख्य;
पूर्ण

अटल व्योम arm_smmu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);

	/*
	 * Free the करोमुख्य resources. We assume that all devices have
	 * alपढ़ोy been detached.
	 */
	iommu_put_dma_cookie(करोमुख्य);
	arm_smmu_destroy_करोमुख्य_context(करोमुख्य);
	kमुक्त(smmu_करोमुख्य);
पूर्ण

अटल व्योम arm_smmu_ग_लिखो_smr(काष्ठा arm_smmu_device *smmu, पूर्णांक idx)
अणु
	काष्ठा arm_smmu_smr *smr = smmu->smrs + idx;
	u32 reg = FIELD_PREP(ARM_SMMU_SMR_ID, smr->id) |
		  FIELD_PREP(ARM_SMMU_SMR_MASK, smr->mask);

	अगर (!(smmu->features & ARM_SMMU_FEAT_EXIDS) && smr->valid)
		reg |= ARM_SMMU_SMR_VALID;
	arm_smmu_gr0_ग_लिखो(smmu, ARM_SMMU_GR0_SMR(idx), reg);
पूर्ण

अटल व्योम arm_smmu_ग_लिखो_s2cr(काष्ठा arm_smmu_device *smmu, पूर्णांक idx)
अणु
	काष्ठा arm_smmu_s2cr *s2cr = smmu->s2crs + idx;
	u32 reg;

	अगर (smmu->impl && smmu->impl->ग_लिखो_s2cr) अणु
		smmu->impl->ग_लिखो_s2cr(smmu, idx);
		वापस;
	पूर्ण

	reg = FIELD_PREP(ARM_SMMU_S2CR_TYPE, s2cr->type) |
	      FIELD_PREP(ARM_SMMU_S2CR_CBNDX, s2cr->cbndx) |
	      FIELD_PREP(ARM_SMMU_S2CR_PRIVCFG, s2cr->privcfg);

	अगर (smmu->features & ARM_SMMU_FEAT_EXIDS && smmu->smrs &&
	    smmu->smrs[idx].valid)
		reg |= ARM_SMMU_S2CR_EXIDVALID;
	arm_smmu_gr0_ग_लिखो(smmu, ARM_SMMU_GR0_S2CR(idx), reg);
पूर्ण

अटल व्योम arm_smmu_ग_लिखो_sme(काष्ठा arm_smmu_device *smmu, पूर्णांक idx)
अणु
	arm_smmu_ग_लिखो_s2cr(smmu, idx);
	अगर (smmu->smrs)
		arm_smmu_ग_लिखो_smr(smmu, idx);
पूर्ण

/*
 * The width of SMR's mask field depends on sCR0_EXIDENABLE, so this function
 * should be called after sCR0 is written.
 */
अटल व्योम arm_smmu_test_smr_masks(काष्ठा arm_smmu_device *smmu)
अणु
	u32 smr;
	पूर्णांक i;

	अगर (!smmu->smrs)
		वापस;
	/*
	 * If we've had to accommodate firmware memory regions, we may
	 * have live SMRs by now; tपढ़ो carefully...
	 *
	 * Somewhat perversely, not having a मुक्त SMR क्रम this test implies we
	 * can get away without it anyway, as we'll only be able to 'allocate'
	 * these SMRs क्रम the ID/mask values we're alपढ़ोy trusting to be OK.
	 */
	क्रम (i = 0; i < smmu->num_mapping_groups; i++)
		अगर (!smmu->smrs[i].valid)
			जाओ smr_ok;
	वापस;
smr_ok:
	/*
	 * SMR.ID bits may not be preserved अगर the corresponding MASK
	 * bits are set, so check each one separately. We can reject
	 * masters later अगर they try to claim IDs outside these masks.
	 */
	smr = FIELD_PREP(ARM_SMMU_SMR_ID, smmu->streamid_mask);
	arm_smmu_gr0_ग_लिखो(smmu, ARM_SMMU_GR0_SMR(i), smr);
	smr = arm_smmu_gr0_पढ़ो(smmu, ARM_SMMU_GR0_SMR(i));
	smmu->streamid_mask = FIELD_GET(ARM_SMMU_SMR_ID, smr);

	smr = FIELD_PREP(ARM_SMMU_SMR_MASK, smmu->streamid_mask);
	arm_smmu_gr0_ग_लिखो(smmu, ARM_SMMU_GR0_SMR(i), smr);
	smr = arm_smmu_gr0_पढ़ो(smmu, ARM_SMMU_GR0_SMR(i));
	smmu->smr_mask_mask = FIELD_GET(ARM_SMMU_SMR_MASK, smr);
पूर्ण

अटल पूर्णांक arm_smmu_find_sme(काष्ठा arm_smmu_device *smmu, u16 id, u16 mask)
अणु
	काष्ठा arm_smmu_smr *smrs = smmu->smrs;
	पूर्णांक i, मुक्त_idx = -ENOSPC;

	/* Stream indexing is blissfully easy */
	अगर (!smrs)
		वापस id;

	/* Validating SMRs is... less so */
	क्रम (i = 0; i < smmu->num_mapping_groups; ++i) अणु
		अगर (!smrs[i].valid) अणु
			/*
			 * Note the first मुक्त entry we come across, which
			 * we'll claim in the end अगर nothing अन्यथा matches.
			 */
			अगर (मुक्त_idx < 0)
				मुक्त_idx = i;
			जारी;
		पूर्ण
		/*
		 * If the new entry is _entirely_ matched by an existing entry,
		 * then reuse that, with the guarantee that there also cannot
		 * be any subsequent conflicting entries. In normal use we'd
		 * expect simply identical entries क्रम this हाल, but there's
		 * no harm in accommodating the generalisation.
		 */
		अगर ((mask & smrs[i].mask) == mask &&
		    !((id ^ smrs[i].id) & ~smrs[i].mask))
			वापस i;
		/*
		 * If the new entry has any other overlap with an existing one,
		 * though, then there always exists at least one stream ID
		 * which would cause a conflict, and we can't allow that risk.
		 */
		अगर (!((id ^ smrs[i].id) & ~(smrs[i].mask | mask)))
			वापस -EINVAL;
	पूर्ण

	वापस मुक्त_idx;
पूर्ण

अटल bool arm_smmu_मुक्त_sme(काष्ठा arm_smmu_device *smmu, पूर्णांक idx)
अणु
	अगर (--smmu->s2crs[idx].count)
		वापस false;

	smmu->s2crs[idx] = s2cr_init_val;
	अगर (smmu->smrs)
		smmu->smrs[idx].valid = false;

	वापस true;
पूर्ण

अटल पूर्णांक arm_smmu_master_alloc_smes(काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा arm_smmu_master_cfg *cfg = dev_iommu_priv_get(dev);
	काष्ठा arm_smmu_device *smmu = cfg->smmu;
	काष्ठा arm_smmu_smr *smrs = smmu->smrs;
	पूर्णांक i, idx, ret;

	mutex_lock(&smmu->stream_map_mutex);
	/* Figure out a viable stream map entry allocation */
	क्रम_each_cfg_sme(cfg, fwspec, i, idx) अणु
		u16 sid = FIELD_GET(ARM_SMMU_SMR_ID, fwspec->ids[i]);
		u16 mask = FIELD_GET(ARM_SMMU_SMR_MASK, fwspec->ids[i]);

		अगर (idx != INVALID_SMENDX) अणु
			ret = -EEXIST;
			जाओ out_err;
		पूर्ण

		ret = arm_smmu_find_sme(smmu, sid, mask);
		अगर (ret < 0)
			जाओ out_err;

		idx = ret;
		अगर (smrs && smmu->s2crs[idx].count == 0) अणु
			smrs[idx].id = sid;
			smrs[idx].mask = mask;
			smrs[idx].valid = true;
		पूर्ण
		smmu->s2crs[idx].count++;
		cfg->smendx[i] = (s16)idx;
	पूर्ण

	/* It worked! Now, poke the actual hardware */
	क्रम_each_cfg_sme(cfg, fwspec, i, idx)
		arm_smmu_ग_लिखो_sme(smmu, idx);

	mutex_unlock(&smmu->stream_map_mutex);
	वापस 0;

out_err:
	जबतक (i--) अणु
		arm_smmu_मुक्त_sme(smmu, cfg->smendx[i]);
		cfg->smendx[i] = INVALID_SMENDX;
	पूर्ण
	mutex_unlock(&smmu->stream_map_mutex);
	वापस ret;
पूर्ण

अटल व्योम arm_smmu_master_मुक्त_smes(काष्ठा arm_smmu_master_cfg *cfg,
				      काष्ठा iommu_fwspec *fwspec)
अणु
	काष्ठा arm_smmu_device *smmu = cfg->smmu;
	पूर्णांक i, idx;

	mutex_lock(&smmu->stream_map_mutex);
	क्रम_each_cfg_sme(cfg, fwspec, i, idx) अणु
		अगर (arm_smmu_मुक्त_sme(smmu, idx))
			arm_smmu_ग_लिखो_sme(smmu, idx);
		cfg->smendx[i] = INVALID_SMENDX;
	पूर्ण
	mutex_unlock(&smmu->stream_map_mutex);
पूर्ण

अटल पूर्णांक arm_smmu_करोमुख्य_add_master(काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य,
				      काष्ठा arm_smmu_master_cfg *cfg,
				      काष्ठा iommu_fwspec *fwspec)
अणु
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;
	काष्ठा arm_smmu_s2cr *s2cr = smmu->s2crs;
	u8 cbndx = smmu_करोमुख्य->cfg.cbndx;
	क्रमागत arm_smmu_s2cr_type type;
	पूर्णांक i, idx;

	अगर (smmu_करोमुख्य->stage == ARM_SMMU_DOMAIN_BYPASS)
		type = S2CR_TYPE_BYPASS;
	अन्यथा
		type = S2CR_TYPE_TRANS;

	क्रम_each_cfg_sme(cfg, fwspec, i, idx) अणु
		अगर (type == s2cr[idx].type && cbndx == s2cr[idx].cbndx)
			जारी;

		s2cr[idx].type = type;
		s2cr[idx].privcfg = S2CR_PRIVCFG_DEFAULT;
		s2cr[idx].cbndx = cbndx;
		arm_smmu_ग_लिखो_s2cr(smmu, idx);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक arm_smmu_attach_dev(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा arm_smmu_master_cfg *cfg;
	काष्ठा arm_smmu_device *smmu;
	पूर्णांक ret;

	अगर (!fwspec || fwspec->ops != &arm_smmu_ops) अणु
		dev_err(dev, "cannot attach to SMMU, is it on the same bus?\n");
		वापस -ENXIO;
	पूर्ण

	/*
	 * FIXME: The arch/arm DMA API code tries to attach devices to its own
	 * करोमुख्यs between of_xlate() and probe_device() - we have no way to cope
	 * with that, so until ARM माला_लो converted to rely on groups and शेष
	 * करोमुख्यs, just say no (but more politely than by dereferencing शून्य).
	 * This should be at least a WARN_ON once that's sorted.
	 */
	cfg = dev_iommu_priv_get(dev);
	अगर (!cfg)
		वापस -ENODEV;

	smmu = cfg->smmu;

	ret = arm_smmu_rpm_get(smmu);
	अगर (ret < 0)
		वापस ret;

	/* Ensure that the करोमुख्य is finalised */
	ret = arm_smmu_init_करोमुख्य_context(करोमुख्य, smmu, dev);
	अगर (ret < 0)
		जाओ rpm_put;

	/*
	 * Sanity check the करोमुख्य. We करोn't support करोमुख्यs across
	 * dअगरferent SMMUs.
	 */
	अगर (smmu_करोमुख्य->smmu != smmu) अणु
		dev_err(dev,
			"cannot attach to SMMU %s whilst already attached to domain on SMMU %s\n",
			dev_name(smmu_करोमुख्य->smmu->dev), dev_name(smmu->dev));
		ret = -EINVAL;
		जाओ rpm_put;
	पूर्ण

	/* Looks ok, so add the device to the करोमुख्य */
	ret = arm_smmu_करोमुख्य_add_master(smmu_करोमुख्य, cfg, fwspec);

	/*
	 * Setup an स्वतःsuspend delay to aव्योम bouncing runpm state.
	 * Otherwise, अगर a driver क्रम a suspended consumer device
	 * unmaps buffers, it will runpm resume/suspend क्रम each one.
	 *
	 * For example, when used by a GPU device, when an application
	 * or game निकासs, it can trigger unmapping 100s or 1000s of
	 * buffers.  With a runpm cycle क्रम each buffer, that adds up
	 * to 5-10sec worth of reprogramming the context bank, जबतक
	 * the प्रणाली appears to be locked up to the user.
	 */
	pm_runसमय_set_स्वतःsuspend_delay(smmu->dev, 20);
	pm_runसमय_use_स्वतःsuspend(smmu->dev);

rpm_put:
	arm_smmu_rpm_put(smmu);
	वापस ret;
पूर्ण

अटल पूर्णांक arm_smmu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा io_pgtable_ops *ops = to_smmu_करोमुख्य(करोमुख्य)->pgtbl_ops;
	काष्ठा arm_smmu_device *smmu = to_smmu_करोमुख्य(करोमुख्य)->smmu;
	पूर्णांक ret;

	अगर (!ops)
		वापस -ENODEV;

	arm_smmu_rpm_get(smmu);
	ret = ops->map(ops, iova, paddr, size, prot, gfp);
	arm_smmu_rpm_put(smmu);

	वापस ret;
पूर्ण

अटल माप_प्रकार arm_smmu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			     माप_प्रकार size, काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा io_pgtable_ops *ops = to_smmu_करोमुख्य(करोमुख्य)->pgtbl_ops;
	काष्ठा arm_smmu_device *smmu = to_smmu_करोमुख्य(करोमुख्य)->smmu;
	माप_प्रकार ret;

	अगर (!ops)
		वापस 0;

	arm_smmu_rpm_get(smmu);
	ret = ops->unmap(ops, iova, size, gather);
	arm_smmu_rpm_put(smmu);

	वापस ret;
पूर्ण

अटल व्योम arm_smmu_flush_iotlb_all(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;

	अगर (smmu_करोमुख्य->flush_ops) अणु
		arm_smmu_rpm_get(smmu);
		smmu_करोमुख्य->flush_ops->tlb_flush_all(smmu_करोमुख्य);
		arm_smmu_rpm_put(smmu);
	पूर्ण
पूर्ण

अटल व्योम arm_smmu_iotlb_sync(काष्ठा iommu_करोमुख्य *करोमुख्य,
				काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;

	अगर (!smmu)
		वापस;

	arm_smmu_rpm_get(smmu);
	अगर (smmu->version == ARM_SMMU_V2 ||
	    smmu_करोमुख्य->stage == ARM_SMMU_DOMAIN_S1)
		arm_smmu_tlb_sync_context(smmu_करोमुख्य);
	अन्यथा
		arm_smmu_tlb_sync_global(smmu);
	arm_smmu_rpm_put(smmu);
पूर्ण

अटल phys_addr_t arm_smmu_iova_to_phys_hard(काष्ठा iommu_करोमुख्य *करोमुख्य,
					      dma_addr_t iova)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);
	काष्ठा arm_smmu_device *smmu = smmu_करोमुख्य->smmu;
	काष्ठा arm_smmu_cfg *cfg = &smmu_करोमुख्य->cfg;
	काष्ठा io_pgtable_ops *ops= smmu_करोमुख्य->pgtbl_ops;
	काष्ठा device *dev = smmu->dev;
	व्योम __iomem *reg;
	u32 पंचांगp;
	u64 phys;
	अचिन्हित दीर्घ va, flags;
	पूर्णांक ret, idx = cfg->cbndx;

	ret = arm_smmu_rpm_get(smmu);
	अगर (ret < 0)
		वापस 0;

	spin_lock_irqsave(&smmu_करोमुख्य->cb_lock, flags);
	va = iova & ~0xfffUL;
	अगर (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH64)
		arm_smmu_cb_ग_लिखोq(smmu, idx, ARM_SMMU_CB_ATS1PR, va);
	अन्यथा
		arm_smmu_cb_ग_लिखो(smmu, idx, ARM_SMMU_CB_ATS1PR, va);

	reg = arm_smmu_page(smmu, ARM_SMMU_CB(smmu, idx)) + ARM_SMMU_CB_ATSR;
	अगर (पढ़ोl_poll_समयout_atomic(reg, पंचांगp, !(पंचांगp & ARM_SMMU_ATSR_ACTIVE),
				      5, 50)) अणु
		spin_unlock_irqrestore(&smmu_करोमुख्य->cb_lock, flags);
		dev_err(dev,
			"iova to phys timed out on %pad. Falling back to software table walk.\n",
			&iova);
		वापस ops->iova_to_phys(ops, iova);
	पूर्ण

	phys = arm_smmu_cb_पढ़ोq(smmu, idx, ARM_SMMU_CB_PAR);
	spin_unlock_irqrestore(&smmu_करोमुख्य->cb_lock, flags);
	अगर (phys & ARM_SMMU_CB_PAR_F) अणु
		dev_err(dev, "translation fault!\n");
		dev_err(dev, "PAR = 0x%llx\n", phys);
		वापस 0;
	पूर्ण

	arm_smmu_rpm_put(smmu);

	वापस (phys & GENMASK_ULL(39, 12)) | (iova & 0xfff);
पूर्ण

अटल phys_addr_t arm_smmu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
					dma_addr_t iova)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);
	काष्ठा io_pgtable_ops *ops = smmu_करोमुख्य->pgtbl_ops;

	अगर (करोमुख्य->type == IOMMU_DOMAIN_IDENTITY)
		वापस iova;

	अगर (!ops)
		वापस 0;

	अगर (smmu_करोमुख्य->smmu->features & ARM_SMMU_FEAT_TRANS_OPS &&
			smmu_करोमुख्य->stage == ARM_SMMU_DOMAIN_S1)
		वापस arm_smmu_iova_to_phys_hard(करोमुख्य, iova);

	वापस ops->iova_to_phys(ops, iova);
पूर्ण

अटल bool arm_smmu_capable(क्रमागत iommu_cap cap)
अणु
	चयन (cap) अणु
	हाल IOMMU_CAP_CACHE_COHERENCY:
		/*
		 * Return true here as the SMMU can always send out coherent
		 * requests.
		 */
		वापस true;
	हाल IOMMU_CAP_NOEXEC:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल
काष्ठा arm_smmu_device *arm_smmu_get_by_fwnode(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा device *dev = driver_find_device_by_fwnode(&arm_smmu_driver.driver,
							  fwnode);
	put_device(dev);
	वापस dev ? dev_get_drvdata(dev) : शून्य;
पूर्ण

अटल काष्ठा iommu_device *arm_smmu_probe_device(काष्ठा device *dev)
अणु
	काष्ठा arm_smmu_device *smmu = शून्य;
	काष्ठा arm_smmu_master_cfg *cfg;
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	पूर्णांक i, ret;

	अगर (using_legacy_binding) अणु
		ret = arm_smmu_रेजिस्टर_legacy_master(dev, &smmu);

		/*
		 * If dev->iommu_fwspec is initally शून्य, arm_smmu_रेजिस्टर_legacy_master()
		 * will allocate/initialise a new one. Thus we need to update fwspec क्रम
		 * later use.
		 */
		fwspec = dev_iommu_fwspec_get(dev);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण अन्यथा अगर (fwspec && fwspec->ops == &arm_smmu_ops) अणु
		smmu = arm_smmu_get_by_fwnode(fwspec->iommu_fwnode);
	पूर्ण अन्यथा अणु
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	ret = -EINVAL;
	क्रम (i = 0; i < fwspec->num_ids; i++) अणु
		u16 sid = FIELD_GET(ARM_SMMU_SMR_ID, fwspec->ids[i]);
		u16 mask = FIELD_GET(ARM_SMMU_SMR_MASK, fwspec->ids[i]);

		अगर (sid & ~smmu->streamid_mask) अणु
			dev_err(dev, "stream ID 0x%x out of range for SMMU (0x%x)\n",
				sid, smmu->streamid_mask);
			जाओ out_मुक्त;
		पूर्ण
		अगर (mask & ~smmu->smr_mask_mask) अणु
			dev_err(dev, "SMR mask 0x%x out of range for SMMU (0x%x)\n",
				mask, smmu->smr_mask_mask);
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	ret = -ENOMEM;
	cfg = kzalloc(दुरत्व(काष्ठा arm_smmu_master_cfg, smendx[i]),
		      GFP_KERNEL);
	अगर (!cfg)
		जाओ out_मुक्त;

	cfg->smmu = smmu;
	dev_iommu_priv_set(dev, cfg);
	जबतक (i--)
		cfg->smendx[i] = INVALID_SMENDX;

	ret = arm_smmu_rpm_get(smmu);
	अगर (ret < 0)
		जाओ out_cfg_मुक्त;

	ret = arm_smmu_master_alloc_smes(dev);
	arm_smmu_rpm_put(smmu);

	अगर (ret)
		जाओ out_cfg_मुक्त;

	device_link_add(dev, smmu->dev,
			DL_FLAG_PM_RUNTIME | DL_FLAG_AUTOREMOVE_SUPPLIER);

	वापस &smmu->iommu;

out_cfg_मुक्त:
	kमुक्त(cfg);
out_मुक्त:
	iommu_fwspec_मुक्त(dev);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम arm_smmu_release_device(काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा arm_smmu_master_cfg *cfg;
	काष्ठा arm_smmu_device *smmu;
	पूर्णांक ret;

	अगर (!fwspec || fwspec->ops != &arm_smmu_ops)
		वापस;

	cfg  = dev_iommu_priv_get(dev);
	smmu = cfg->smmu;

	ret = arm_smmu_rpm_get(smmu);
	अगर (ret < 0)
		वापस;

	arm_smmu_master_मुक्त_smes(cfg, fwspec);

	arm_smmu_rpm_put(smmu);

	dev_iommu_priv_set(dev, शून्य);
	kमुक्त(cfg);
	iommu_fwspec_मुक्त(dev);
पूर्ण

अटल काष्ठा iommu_group *arm_smmu_device_group(काष्ठा device *dev)
अणु
	काष्ठा arm_smmu_master_cfg *cfg = dev_iommu_priv_get(dev);
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा arm_smmu_device *smmu = cfg->smmu;
	काष्ठा iommu_group *group = शून्य;
	पूर्णांक i, idx;

	क्रम_each_cfg_sme(cfg, fwspec, i, idx) अणु
		अगर (group && smmu->s2crs[idx].group &&
		    group != smmu->s2crs[idx].group)
			वापस ERR_PTR(-EINVAL);

		group = smmu->s2crs[idx].group;
	पूर्ण

	अगर (group)
		वापस iommu_group_ref_get(group);

	अगर (dev_is_pci(dev))
		group = pci_device_group(dev);
	अन्यथा अगर (dev_is_fsl_mc(dev))
		group = fsl_mc_device_group(dev);
	अन्यथा
		group = generic_device_group(dev);

	/* Remember group क्रम faster lookups */
	अगर (!IS_ERR(group))
		क्रम_each_cfg_sme(cfg, fwspec, i, idx)
			smmu->s2crs[idx].group = group;

	वापस group;
पूर्ण

अटल पूर्णांक arm_smmu_enable_nesting(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);
	पूर्णांक ret = 0;

	mutex_lock(&smmu_करोमुख्य->init_mutex);
	अगर (smmu_करोमुख्य->smmu)
		ret = -EPERM;
	अन्यथा
		smmu_करोमुख्य->stage = ARM_SMMU_DOMAIN_NESTED;
	mutex_unlock(&smmu_करोमुख्य->init_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक arm_smmu_set_pgtable_quirks(काष्ठा iommu_करोमुख्य *करोमुख्य,
		अचिन्हित दीर्घ quirks)
अणु
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य = to_smmu_करोमुख्य(करोमुख्य);
	पूर्णांक ret = 0;

	mutex_lock(&smmu_करोमुख्य->init_mutex);
	अगर (smmu_करोमुख्य->smmu)
		ret = -EPERM;
	अन्यथा
		smmu_करोमुख्य->pgtbl_quirks = quirks;
	mutex_unlock(&smmu_करोमुख्य->init_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक arm_smmu_of_xlate(काष्ठा device *dev, काष्ठा of_phandle_args *args)
अणु
	u32 mask, fwid = 0;

	अगर (args->args_count > 0)
		fwid |= FIELD_PREP(ARM_SMMU_SMR_ID, args->args[0]);

	अगर (args->args_count > 1)
		fwid |= FIELD_PREP(ARM_SMMU_SMR_MASK, args->args[1]);
	अन्यथा अगर (!of_property_पढ़ो_u32(args->np, "stream-match-mask", &mask))
		fwid |= FIELD_PREP(ARM_SMMU_SMR_MASK, mask);

	वापस iommu_fwspec_add_ids(dev, &fwid, 1);
पूर्ण

अटल व्योम arm_smmu_get_resv_regions(काष्ठा device *dev,
				      काष्ठा list_head *head)
अणु
	काष्ठा iommu_resv_region *region;
	पूर्णांक prot = IOMMU_WRITE | IOMMU_NOEXEC | IOMMU_MMIO;

	region = iommu_alloc_resv_region(MSI_IOVA_BASE, MSI_IOVA_LENGTH,
					 prot, IOMMU_RESV_SW_MSI);
	अगर (!region)
		वापस;

	list_add_tail(&region->list, head);

	iommu_dma_get_resv_regions(dev, head);
पूर्ण

अटल पूर्णांक arm_smmu_def_करोमुख्य_type(काष्ठा device *dev)
अणु
	काष्ठा arm_smmu_master_cfg *cfg = dev_iommu_priv_get(dev);
	स्थिर काष्ठा arm_smmu_impl *impl = cfg->smmu->impl;

	अगर (impl && impl->def_करोमुख्य_type)
		वापस impl->def_करोमुख्य_type(dev);

	वापस 0;
पूर्ण

अटल काष्ठा iommu_ops arm_smmu_ops = अणु
	.capable		= arm_smmu_capable,
	.करोमुख्य_alloc		= arm_smmu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त		= arm_smmu_करोमुख्य_मुक्त,
	.attach_dev		= arm_smmu_attach_dev,
	.map			= arm_smmu_map,
	.unmap			= arm_smmu_unmap,
	.flush_iotlb_all	= arm_smmu_flush_iotlb_all,
	.iotlb_sync		= arm_smmu_iotlb_sync,
	.iova_to_phys		= arm_smmu_iova_to_phys,
	.probe_device		= arm_smmu_probe_device,
	.release_device		= arm_smmu_release_device,
	.device_group		= arm_smmu_device_group,
	.enable_nesting		= arm_smmu_enable_nesting,
	.set_pgtable_quirks	= arm_smmu_set_pgtable_quirks,
	.of_xlate		= arm_smmu_of_xlate,
	.get_resv_regions	= arm_smmu_get_resv_regions,
	.put_resv_regions	= generic_iommu_put_resv_regions,
	.def_करोमुख्य_type	= arm_smmu_def_करोमुख्य_type,
	.pgsize_biपंचांगap		= -1UL, /* Restricted during device attach */
	.owner			= THIS_MODULE,
पूर्ण;

अटल व्योम arm_smmu_device_reset(काष्ठा arm_smmu_device *smmu)
अणु
	पूर्णांक i;
	u32 reg;

	/* clear global FSR */
	reg = arm_smmu_gr0_पढ़ो(smmu, ARM_SMMU_GR0_sGFSR);
	arm_smmu_gr0_ग_लिखो(smmu, ARM_SMMU_GR0_sGFSR, reg);

	/*
	 * Reset stream mapping groups: Initial values mark all SMRn as
	 * invalid and all S2CRn as bypass unless overridden.
	 */
	क्रम (i = 0; i < smmu->num_mapping_groups; ++i)
		arm_smmu_ग_लिखो_sme(smmu, i);

	/* Make sure all context banks are disabled and clear CB_FSR  */
	क्रम (i = 0; i < smmu->num_context_banks; ++i) अणु
		arm_smmu_ग_लिखो_context_bank(smmu, i);
		arm_smmu_cb_ग_लिखो(smmu, i, ARM_SMMU_CB_FSR, ARM_SMMU_FSR_FAULT);
	पूर्ण

	/* Invalidate the TLB, just in हाल */
	arm_smmu_gr0_ग_लिखो(smmu, ARM_SMMU_GR0_TLBIALLH, QCOM_DUMMY_VAL);
	arm_smmu_gr0_ग_लिखो(smmu, ARM_SMMU_GR0_TLBIALLNSNH, QCOM_DUMMY_VAL);

	reg = arm_smmu_gr0_पढ़ो(smmu, ARM_SMMU_GR0_sCR0);

	/* Enable fault reporting */
	reg |= (ARM_SMMU_sCR0_GFRE | ARM_SMMU_sCR0_GFIE |
		ARM_SMMU_sCR0_GCFGFRE | ARM_SMMU_sCR0_GCFGFIE);

	/* Disable TLB broadcasting. */
	reg |= (ARM_SMMU_sCR0_VMIDPNE | ARM_SMMU_sCR0_PTM);

	/* Enable client access, handling unmatched streams as appropriate */
	reg &= ~ARM_SMMU_sCR0_CLIENTPD;
	अगर (disable_bypass)
		reg |= ARM_SMMU_sCR0_USFCFG;
	अन्यथा
		reg &= ~ARM_SMMU_sCR0_USFCFG;

	/* Disable क्रमced broadcasting */
	reg &= ~ARM_SMMU_sCR0_FB;

	/* Don't upgrade barriers */
	reg &= ~(ARM_SMMU_sCR0_BSU);

	अगर (smmu->features & ARM_SMMU_FEAT_VMID16)
		reg |= ARM_SMMU_sCR0_VMID16EN;

	अगर (smmu->features & ARM_SMMU_FEAT_EXIDS)
		reg |= ARM_SMMU_sCR0_EXIDENABLE;

	अगर (smmu->impl && smmu->impl->reset)
		smmu->impl->reset(smmu);

	/* Push the button */
	arm_smmu_tlb_sync_global(smmu);
	arm_smmu_gr0_ग_लिखो(smmu, ARM_SMMU_GR0_sCR0, reg);
पूर्ण

अटल पूर्णांक arm_smmu_id_माप_प्रकारo_bits(पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 0:
		वापस 32;
	हाल 1:
		वापस 36;
	हाल 2:
		वापस 40;
	हाल 3:
		वापस 42;
	हाल 4:
		वापस 44;
	हाल 5:
	शेष:
		वापस 48;
	पूर्ण
पूर्ण

अटल पूर्णांक arm_smmu_device_cfg_probe(काष्ठा arm_smmu_device *smmu)
अणु
	अचिन्हित पूर्णांक size;
	u32 id;
	bool cttw_reg, cttw_fw = smmu->features & ARM_SMMU_FEAT_COHERENT_WALK;
	पूर्णांक i, ret;

	dev_notice(smmu->dev, "probing hardware configuration...\n");
	dev_notice(smmu->dev, "SMMUv%d with:\n",
			smmu->version == ARM_SMMU_V2 ? 2 : 1);

	/* ID0 */
	id = arm_smmu_gr0_पढ़ो(smmu, ARM_SMMU_GR0_ID0);

	/* Restrict available stages based on module parameter */
	अगर (क्रमce_stage == 1)
		id &= ~(ARM_SMMU_ID0_S2TS | ARM_SMMU_ID0_NTS);
	अन्यथा अगर (क्रमce_stage == 2)
		id &= ~(ARM_SMMU_ID0_S1TS | ARM_SMMU_ID0_NTS);

	अगर (id & ARM_SMMU_ID0_S1TS) अणु
		smmu->features |= ARM_SMMU_FEAT_TRANS_S1;
		dev_notice(smmu->dev, "\tstage 1 translation\n");
	पूर्ण

	अगर (id & ARM_SMMU_ID0_S2TS) अणु
		smmu->features |= ARM_SMMU_FEAT_TRANS_S2;
		dev_notice(smmu->dev, "\tstage 2 translation\n");
	पूर्ण

	अगर (id & ARM_SMMU_ID0_NTS) अणु
		smmu->features |= ARM_SMMU_FEAT_TRANS_NESTED;
		dev_notice(smmu->dev, "\tnested translation\n");
	पूर्ण

	अगर (!(smmu->features &
		(ARM_SMMU_FEAT_TRANS_S1 | ARM_SMMU_FEAT_TRANS_S2))) अणु
		dev_err(smmu->dev, "\tno translation support!\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((id & ARM_SMMU_ID0_S1TS) &&
	    ((smmu->version < ARM_SMMU_V2) || !(id & ARM_SMMU_ID0_ATOSNS))) अणु
		smmu->features |= ARM_SMMU_FEAT_TRANS_OPS;
		dev_notice(smmu->dev, "\taddress translation ops\n");
	पूर्ण

	/*
	 * In order क्रम DMA API calls to work properly, we must defer to what
	 * the FW says about coherency, regardless of what the hardware claims.
	 * Fortunately, this also खोलोs up a workaround क्रम प्रणालीs where the
	 * ID रेजिस्टर value has ended up configured incorrectly.
	 */
	cttw_reg = !!(id & ARM_SMMU_ID0_CTTW);
	अगर (cttw_fw || cttw_reg)
		dev_notice(smmu->dev, "\t%scoherent table walk\n",
			   cttw_fw ? "" : "non-");
	अगर (cttw_fw != cttw_reg)
		dev_notice(smmu->dev,
			   "\t(IDR0.CTTW overridden by FW configuration)\n");

	/* Max. number of entries we have क्रम stream matching/indexing */
	अगर (smmu->version == ARM_SMMU_V2 && id & ARM_SMMU_ID0_EXIDS) अणु
		smmu->features |= ARM_SMMU_FEAT_EXIDS;
		size = 1 << 16;
	पूर्ण अन्यथा अणु
		size = 1 << FIELD_GET(ARM_SMMU_ID0_NUMSIDB, id);
	पूर्ण
	smmu->streamid_mask = size - 1;
	अगर (id & ARM_SMMU_ID0_SMS) अणु
		smmu->features |= ARM_SMMU_FEAT_STREAM_MATCH;
		size = FIELD_GET(ARM_SMMU_ID0_NUMSMRG, id);
		अगर (size == 0) अणु
			dev_err(smmu->dev,
				"stream-matching supported, but no SMRs present!\n");
			वापस -ENODEV;
		पूर्ण

		/* Zero-initialised to mark as invalid */
		smmu->smrs = devm_kसुस्मृति(smmu->dev, size, माप(*smmu->smrs),
					  GFP_KERNEL);
		अगर (!smmu->smrs)
			वापस -ENOMEM;

		dev_notice(smmu->dev,
			   "\tstream matching with %u register groups", size);
	पूर्ण
	/* s2cr->type == 0 means translation, so initialise explicitly */
	smmu->s2crs = devm_kदो_स्मृति_array(smmu->dev, size, माप(*smmu->s2crs),
					 GFP_KERNEL);
	अगर (!smmu->s2crs)
		वापस -ENOMEM;
	क्रम (i = 0; i < size; i++)
		smmu->s2crs[i] = s2cr_init_val;

	smmu->num_mapping_groups = size;
	mutex_init(&smmu->stream_map_mutex);
	spin_lock_init(&smmu->global_sync_lock);

	अगर (smmu->version < ARM_SMMU_V2 ||
	    !(id & ARM_SMMU_ID0_PTFS_NO_AARCH32)) अणु
		smmu->features |= ARM_SMMU_FEAT_FMT_AARCH32_L;
		अगर (!(id & ARM_SMMU_ID0_PTFS_NO_AARCH32S))
			smmu->features |= ARM_SMMU_FEAT_FMT_AARCH32_S;
	पूर्ण

	/* ID1 */
	id = arm_smmu_gr0_पढ़ो(smmu, ARM_SMMU_GR0_ID1);
	smmu->pgshअगरt = (id & ARM_SMMU_ID1_PAGESIZE) ? 16 : 12;

	/* Check क्रम size mismatch of SMMU address space from mapped region */
	size = 1 << (FIELD_GET(ARM_SMMU_ID1_NUMPAGENDXB, id) + 1);
	अगर (smmu->numpage != 2 * size << smmu->pgshअगरt)
		dev_warn(smmu->dev,
			"SMMU address space size (0x%x) differs from mapped region size (0x%x)!\n",
			2 * size << smmu->pgshअगरt, smmu->numpage);
	/* Now properly encode NUMPAGE to subsequently derive SMMU_CB_BASE */
	smmu->numpage = size;

	smmu->num_s2_context_banks = FIELD_GET(ARM_SMMU_ID1_NUMS2CB, id);
	smmu->num_context_banks = FIELD_GET(ARM_SMMU_ID1_NUMCB, id);
	अगर (smmu->num_s2_context_banks > smmu->num_context_banks) अणु
		dev_err(smmu->dev, "impossible number of S2 context banks!\n");
		वापस -ENODEV;
	पूर्ण
	dev_notice(smmu->dev, "\t%u context banks (%u stage-2 only)\n",
		   smmu->num_context_banks, smmu->num_s2_context_banks);
	smmu->cbs = devm_kसुस्मृति(smmu->dev, smmu->num_context_banks,
				 माप(*smmu->cbs), GFP_KERNEL);
	अगर (!smmu->cbs)
		वापस -ENOMEM;

	/* ID2 */
	id = arm_smmu_gr0_पढ़ो(smmu, ARM_SMMU_GR0_ID2);
	size = arm_smmu_id_माप_प्रकारo_bits(FIELD_GET(ARM_SMMU_ID2_IAS, id));
	smmu->ipa_size = size;

	/* The output mask is also applied क्रम bypass */
	size = arm_smmu_id_माप_प्रकारo_bits(FIELD_GET(ARM_SMMU_ID2_OAS, id));
	smmu->pa_size = size;

	अगर (id & ARM_SMMU_ID2_VMID16)
		smmu->features |= ARM_SMMU_FEAT_VMID16;

	/*
	 * What the page table walker can address actually depends on which
	 * descriptor क्रमmat is in use, but since a) we करोn't know that yet,
	 * and b) it can vary per context bank, this will have to करो...
	 */
	अगर (dma_set_mask_and_coherent(smmu->dev, DMA_BIT_MASK(size)))
		dev_warn(smmu->dev,
			 "failed to set DMA mask for table walker\n");

	अगर (smmu->version < ARM_SMMU_V2) अणु
		smmu->va_size = smmu->ipa_size;
		अगर (smmu->version == ARM_SMMU_V1_64K)
			smmu->features |= ARM_SMMU_FEAT_FMT_AARCH64_64K;
	पूर्ण अन्यथा अणु
		size = FIELD_GET(ARM_SMMU_ID2_UBS, id);
		smmu->va_size = arm_smmu_id_माप_प्रकारo_bits(size);
		अगर (id & ARM_SMMU_ID2_PTFS_4K)
			smmu->features |= ARM_SMMU_FEAT_FMT_AARCH64_4K;
		अगर (id & ARM_SMMU_ID2_PTFS_16K)
			smmu->features |= ARM_SMMU_FEAT_FMT_AARCH64_16K;
		अगर (id & ARM_SMMU_ID2_PTFS_64K)
			smmu->features |= ARM_SMMU_FEAT_FMT_AARCH64_64K;
	पूर्ण

	अगर (smmu->impl && smmu->impl->cfg_probe) अणु
		ret = smmu->impl->cfg_probe(smmu);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Now we've corralled the various formats, what'll it करो? */
	अगर (smmu->features & ARM_SMMU_FEAT_FMT_AARCH32_S)
		smmu->pgsize_biपंचांगap |= SZ_4K | SZ_64K | SZ_1M | SZ_16M;
	अगर (smmu->features &
	    (ARM_SMMU_FEAT_FMT_AARCH32_L | ARM_SMMU_FEAT_FMT_AARCH64_4K))
		smmu->pgsize_biपंचांगap |= SZ_4K | SZ_2M | SZ_1G;
	अगर (smmu->features & ARM_SMMU_FEAT_FMT_AARCH64_16K)
		smmu->pgsize_biपंचांगap |= SZ_16K | SZ_32M;
	अगर (smmu->features & ARM_SMMU_FEAT_FMT_AARCH64_64K)
		smmu->pgsize_biपंचांगap |= SZ_64K | SZ_512M;

	अगर (arm_smmu_ops.pgsize_biपंचांगap == -1UL)
		arm_smmu_ops.pgsize_biपंचांगap = smmu->pgsize_biपंचांगap;
	अन्यथा
		arm_smmu_ops.pgsize_biपंचांगap |= smmu->pgsize_biपंचांगap;
	dev_notice(smmu->dev, "\tSupported page sizes: 0x%08lx\n",
		   smmu->pgsize_biपंचांगap);


	अगर (smmu->features & ARM_SMMU_FEAT_TRANS_S1)
		dev_notice(smmu->dev, "\tStage-1: %lu-bit VA -> %lu-bit IPA\n",
			   smmu->va_size, smmu->ipa_size);

	अगर (smmu->features & ARM_SMMU_FEAT_TRANS_S2)
		dev_notice(smmu->dev, "\tStage-2: %lu-bit IPA -> %lu-bit PA\n",
			   smmu->ipa_size, smmu->pa_size);

	वापस 0;
पूर्ण

काष्ठा arm_smmu_match_data अणु
	क्रमागत arm_smmu_arch_version version;
	क्रमागत arm_smmu_implementation model;
पूर्ण;

#घोषणा ARM_SMMU_MATCH_DATA(name, ver, imp)	\
अटल स्थिर काष्ठा arm_smmu_match_data name = अणु .version = ver, .model = imp पूर्ण

ARM_SMMU_MATCH_DATA(smmu_generic_v1, ARM_SMMU_V1, GENERIC_SMMU);
ARM_SMMU_MATCH_DATA(smmu_generic_v2, ARM_SMMU_V2, GENERIC_SMMU);
ARM_SMMU_MATCH_DATA(arm_mmu401, ARM_SMMU_V1_64K, GENERIC_SMMU);
ARM_SMMU_MATCH_DATA(arm_mmu500, ARM_SMMU_V2, ARM_MMU500);
ARM_SMMU_MATCH_DATA(cavium_smmuv2, ARM_SMMU_V2, CAVIUM_SMMUV2);
ARM_SMMU_MATCH_DATA(qcom_smmuv2, ARM_SMMU_V2, QCOM_SMMUV2);

अटल स्थिर काष्ठा of_device_id arm_smmu_of_match[] = अणु
	अणु .compatible = "arm,smmu-v1", .data = &smmu_generic_v1 पूर्ण,
	अणु .compatible = "arm,smmu-v2", .data = &smmu_generic_v2 पूर्ण,
	अणु .compatible = "arm,mmu-400", .data = &smmu_generic_v1 पूर्ण,
	अणु .compatible = "arm,mmu-401", .data = &arm_mmu401 पूर्ण,
	अणु .compatible = "arm,mmu-500", .data = &arm_mmu500 पूर्ण,
	अणु .compatible = "cavium,smmu-v2", .data = &cavium_smmuv2 पूर्ण,
	अणु .compatible = "nvidia,smmu-500", .data = &arm_mmu500 पूर्ण,
	अणु .compatible = "qcom,smmu-v2", .data = &qcom_smmuv2 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, arm_smmu_of_match);

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक acpi_smmu_get_data(u32 model, काष्ठा arm_smmu_device *smmu)
अणु
	पूर्णांक ret = 0;

	चयन (model) अणु
	हाल ACPI_IORT_SMMU_V1:
	हाल ACPI_IORT_SMMU_CORELINK_MMU400:
		smmu->version = ARM_SMMU_V1;
		smmu->model = GENERIC_SMMU;
		अवरोध;
	हाल ACPI_IORT_SMMU_CORELINK_MMU401:
		smmu->version = ARM_SMMU_V1_64K;
		smmu->model = GENERIC_SMMU;
		अवरोध;
	हाल ACPI_IORT_SMMU_V2:
		smmu->version = ARM_SMMU_V2;
		smmu->model = GENERIC_SMMU;
		अवरोध;
	हाल ACPI_IORT_SMMU_CORELINK_MMU500:
		smmu->version = ARM_SMMU_V2;
		smmu->model = ARM_MMU500;
		अवरोध;
	हाल ACPI_IORT_SMMU_CAVIUM_THUNDERX:
		smmu->version = ARM_SMMU_V2;
		smmu->model = CAVIUM_SMMUV2;
		अवरोध;
	शेष:
		ret = -ENODEV;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक arm_smmu_device_acpi_probe(काष्ठा platक्रमm_device *pdev,
				      काष्ठा arm_smmu_device *smmu)
अणु
	काष्ठा device *dev = smmu->dev;
	काष्ठा acpi_iort_node *node =
		*(काष्ठा acpi_iort_node **)dev_get_platdata(dev);
	काष्ठा acpi_iort_smmu *iort_smmu;
	पूर्णांक ret;

	/* Retrieve SMMU1/2 specअगरic data */
	iort_smmu = (काष्ठा acpi_iort_smmu *)node->node_data;

	ret = acpi_smmu_get_data(iort_smmu->model, smmu);
	अगर (ret < 0)
		वापस ret;

	/* Ignore the configuration access पूर्णांकerrupt */
	smmu->num_global_irqs = 1;

	अगर (iort_smmu->flags & ACPI_IORT_SMMU_COHERENT_WALK)
		smmu->features |= ARM_SMMU_FEAT_COHERENT_WALK;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक arm_smmu_device_acpi_probe(काष्ठा platक्रमm_device *pdev,
					     काष्ठा arm_smmu_device *smmu)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक arm_smmu_device_dt_probe(काष्ठा platक्रमm_device *pdev,
				    काष्ठा arm_smmu_device *smmu)
अणु
	स्थिर काष्ठा arm_smmu_match_data *data;
	काष्ठा device *dev = &pdev->dev;
	bool legacy_binding;

	अगर (of_property_पढ़ो_u32(dev->of_node, "#global-interrupts",
				 &smmu->num_global_irqs)) अणु
		dev_err(dev, "missing #global-interrupts property\n");
		वापस -ENODEV;
	पूर्ण

	data = of_device_get_match_data(dev);
	smmu->version = data->version;
	smmu->model = data->model;

	legacy_binding = of_find_property(dev->of_node, "mmu-masters", शून्य);
	अगर (legacy_binding && !using_generic_binding) अणु
		अगर (!using_legacy_binding) अणु
			pr_notice("deprecated \"mmu-masters\" DT property in use; %s support unavailable\n",
				  IS_ENABLED(CONFIG_ARM_SMMU_LEGACY_DT_BINDINGS) ? "DMA API" : "SMMU");
		पूर्ण
		using_legacy_binding = true;
	पूर्ण अन्यथा अगर (!legacy_binding && !using_legacy_binding) अणु
		using_generic_binding = true;
	पूर्ण अन्यथा अणु
		dev_err(dev, "not probing due to mismatched DT properties\n");
		वापस -ENODEV;
	पूर्ण

	अगर (of_dma_is_coherent(dev->of_node))
		smmu->features |= ARM_SMMU_FEAT_COHERENT_WALK;

	वापस 0;
पूर्ण

अटल पूर्णांक arm_smmu_bus_init(काष्ठा iommu_ops *ops)
अणु
	पूर्णांक err;

	/* Oh, क्रम a proper bus असलtraction */
	अगर (!iommu_present(&platक्रमm_bus_type)) अणु
		err = bus_set_iommu(&platक्रमm_bus_type, ops);
		अगर (err)
			वापस err;
	पूर्ण
#अगर_घोषित CONFIG_ARM_AMBA
	अगर (!iommu_present(&amba_bustype)) अणु
		err = bus_set_iommu(&amba_bustype, ops);
		अगर (err)
			जाओ err_reset_platक्रमm_ops;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI
	अगर (!iommu_present(&pci_bus_type)) अणु
		err = bus_set_iommu(&pci_bus_type, ops);
		अगर (err)
			जाओ err_reset_amba_ops;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_FSL_MC_BUS
	अगर (!iommu_present(&fsl_mc_bus_type)) अणु
		err = bus_set_iommu(&fsl_mc_bus_type, ops);
		अगर (err)
			जाओ err_reset_pci_ops;
	पूर्ण
#पूर्ण_अगर
	वापस 0;

err_reset_pci_ops: __maybe_unused;
#अगर_घोषित CONFIG_PCI
	bus_set_iommu(&pci_bus_type, शून्य);
#पूर्ण_अगर
err_reset_amba_ops: __maybe_unused;
#अगर_घोषित CONFIG_ARM_AMBA
	bus_set_iommu(&amba_bustype, शून्य);
#पूर्ण_अगर
err_reset_platक्रमm_ops: __maybe_unused;
	bus_set_iommu(&platक्रमm_bus_type, शून्य);
	वापस err;
पूर्ण

अटल पूर्णांक arm_smmu_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	resource_माप_प्रकार ioaddr;
	काष्ठा arm_smmu_device *smmu;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक num_irqs, i, err;
	irqवापस_t (*global_fault)(पूर्णांक irq, व्योम *dev);

	smmu = devm_kzalloc(dev, माप(*smmu), GFP_KERNEL);
	अगर (!smmu) अणु
		dev_err(dev, "failed to allocate arm_smmu_device\n");
		वापस -ENOMEM;
	पूर्ण
	smmu->dev = dev;

	अगर (dev->of_node)
		err = arm_smmu_device_dt_probe(pdev, smmu);
	अन्यथा
		err = arm_smmu_device_acpi_probe(pdev, smmu);

	अगर (err)
		वापस err;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ioaddr = res->start;
	smmu->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(smmu->base))
		वापस PTR_ERR(smmu->base);
	/*
	 * The resource size should effectively match the value of SMMU_TOP;
	 * stash that temporarily until we know PAGESIZE to validate it with.
	 */
	smmu->numpage = resource_size(res);

	smmu = arm_smmu_impl_init(smmu);
	अगर (IS_ERR(smmu))
		वापस PTR_ERR(smmu);

	num_irqs = 0;
	जबतक ((res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, num_irqs))) अणु
		num_irqs++;
		अगर (num_irqs > smmu->num_global_irqs)
			smmu->num_context_irqs++;
	पूर्ण

	अगर (!smmu->num_context_irqs) अणु
		dev_err(dev, "found %d interrupts but expected at least %d\n",
			num_irqs, smmu->num_global_irqs + 1);
		वापस -ENODEV;
	पूर्ण

	smmu->irqs = devm_kसुस्मृति(dev, num_irqs, माप(*smmu->irqs),
				  GFP_KERNEL);
	अगर (!smmu->irqs) अणु
		dev_err(dev, "failed to allocate %d irqs\n", num_irqs);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < num_irqs; ++i) अणु
		पूर्णांक irq = platक्रमm_get_irq(pdev, i);

		अगर (irq < 0)
			वापस -ENODEV;
		smmu->irqs[i] = irq;
	पूर्ण

	err = devm_clk_bulk_get_all(dev, &smmu->clks);
	अगर (err < 0) अणु
		dev_err(dev, "failed to get clocks %d\n", err);
		वापस err;
	पूर्ण
	smmu->num_clks = err;

	err = clk_bulk_prepare_enable(smmu->num_clks, smmu->clks);
	अगर (err)
		वापस err;

	err = arm_smmu_device_cfg_probe(smmu);
	अगर (err)
		वापस err;

	अगर (smmu->version == ARM_SMMU_V2) अणु
		अगर (smmu->num_context_banks > smmu->num_context_irqs) अणु
			dev_err(dev,
			      "found only %d context irq(s) but %d required\n",
			      smmu->num_context_irqs, smmu->num_context_banks);
			वापस -ENODEV;
		पूर्ण

		/* Ignore superfluous पूर्णांकerrupts */
		smmu->num_context_irqs = smmu->num_context_banks;
	पूर्ण

	अगर (smmu->impl && smmu->impl->global_fault)
		global_fault = smmu->impl->global_fault;
	अन्यथा
		global_fault = arm_smmu_global_fault;

	क्रम (i = 0; i < smmu->num_global_irqs; ++i) अणु
		err = devm_request_irq(smmu->dev, smmu->irqs[i],
				       global_fault,
				       IRQF_SHARED,
				       "arm-smmu global fault",
				       smmu);
		अगर (err) अणु
			dev_err(dev, "failed to request global IRQ %d (%u)\n",
				i, smmu->irqs[i]);
			वापस err;
		पूर्ण
	पूर्ण

	err = iommu_device_sysfs_add(&smmu->iommu, smmu->dev, शून्य,
				     "smmu.%pa", &ioaddr);
	अगर (err) अणु
		dev_err(dev, "Failed to register iommu in sysfs\n");
		वापस err;
	पूर्ण

	err = iommu_device_रेजिस्टर(&smmu->iommu, &arm_smmu_ops, dev);
	अगर (err) अणु
		dev_err(dev, "Failed to register iommu\n");
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, smmu);
	arm_smmu_device_reset(smmu);
	arm_smmu_test_smr_masks(smmu);

	/*
	 * We want to aव्योम touching dev->घातer.lock in fastpaths unless
	 * it's really going to करो something useful - pm_runसमय_enabled()
	 * can serve as an ideal proxy क्रम that decision. So, conditionally
	 * enable pm_runसमय.
	 */
	अगर (dev->pm_करोमुख्य) अणु
		pm_runसमय_set_active(dev);
		pm_runसमय_enable(dev);
	पूर्ण

	/*
	 * For ACPI and generic DT bindings, an SMMU will be probed beक्रमe
	 * any device which might need it, so we want the bus ops in place
	 * पढ़ोy to handle शेष करोमुख्य setup as soon as any SMMU exists.
	 */
	अगर (!using_legacy_binding)
		वापस arm_smmu_bus_init(&arm_smmu_ops);

	वापस 0;
पूर्ण

अटल पूर्णांक arm_smmu_device_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arm_smmu_device *smmu = platक्रमm_get_drvdata(pdev);

	अगर (!smmu)
		वापस -ENODEV;

	अगर (!biपंचांगap_empty(smmu->context_map, ARM_SMMU_MAX_CBS))
		dev_notice(&pdev->dev, "disabling translation\n");

	arm_smmu_bus_init(शून्य);
	iommu_device_unरेजिस्टर(&smmu->iommu);
	iommu_device_sysfs_हटाओ(&smmu->iommu);

	arm_smmu_rpm_get(smmu);
	/* Turn the thing off */
	arm_smmu_gr0_ग_लिखो(smmu, ARM_SMMU_GR0_sCR0, ARM_SMMU_sCR0_CLIENTPD);
	arm_smmu_rpm_put(smmu);

	अगर (pm_runसमय_enabled(smmu->dev))
		pm_runसमय_क्रमce_suspend(smmu->dev);
	अन्यथा
		clk_bulk_disable(smmu->num_clks, smmu->clks);

	clk_bulk_unprepare(smmu->num_clks, smmu->clks);
	वापस 0;
पूर्ण

अटल व्योम arm_smmu_device_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	arm_smmu_device_हटाओ(pdev);
पूर्ण

अटल पूर्णांक __maybe_unused arm_smmu_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा arm_smmu_device *smmu = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_bulk_enable(smmu->num_clks, smmu->clks);
	अगर (ret)
		वापस ret;

	arm_smmu_device_reset(smmu);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused arm_smmu_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा arm_smmu_device *smmu = dev_get_drvdata(dev);

	clk_bulk_disable(smmu->num_clks, smmu->clks);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused arm_smmu_pm_resume(काष्ठा device *dev)
अणु
	अगर (pm_runसमय_suspended(dev))
		वापस 0;

	वापस arm_smmu_runसमय_resume(dev);
पूर्ण

अटल पूर्णांक __maybe_unused arm_smmu_pm_suspend(काष्ठा device *dev)
अणु
	अगर (pm_runसमय_suspended(dev))
		वापस 0;

	वापस arm_smmu_runसमय_suspend(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops arm_smmu_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(arm_smmu_pm_suspend, arm_smmu_pm_resume)
	SET_RUNTIME_PM_OPS(arm_smmu_runसमय_suspend,
			   arm_smmu_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver arm_smmu_driver = अणु
	.driver	= अणु
		.name			= "arm-smmu",
		.of_match_table		= arm_smmu_of_match,
		.pm			= &arm_smmu_pm_ops,
		.suppress_bind_attrs    = true,
	पूर्ण,
	.probe	= arm_smmu_device_probe,
	.हटाओ	= arm_smmu_device_हटाओ,
	.shutकरोwn = arm_smmu_device_shutकरोwn,
पूर्ण;
module_platक्रमm_driver(arm_smmu_driver);

MODULE_DESCRIPTION("IOMMU API for ARM architected SMMU implementations");
MODULE_AUTHOR("Will Deacon <will@kernel.org>");
MODULE_ALIAS("platform:arm-smmu");
MODULE_LICENSE("GPL v2");
