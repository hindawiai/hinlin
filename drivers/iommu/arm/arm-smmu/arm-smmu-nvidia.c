<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (C) 2019-2020 NVIDIA CORPORATION.  All rights reserved.

#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "arm-smmu.h"

/*
 * Tegra194 has three ARM MMU-500 Instances.
 * Two of them are used together and must be programmed identically क्रम
 * पूर्णांकerleaved IOVA accesses across them and translates accesses from
 * non-isochronous HW devices.
 * Third one is used क्रम translating accesses from isochronous HW devices.
 * This implementation supports programming of the two instances that must
 * be programmed identically.
 * The third instance usage is through standard arm-smmu driver itself and
 * is out of scope of this implementation.
 */
#घोषणा NUM_SMMU_INSTANCES 2

काष्ठा nvidia_smmu अणु
	काष्ठा arm_smmu_device	smmu;
	व्योम __iomem		*bases[NUM_SMMU_INSTANCES];
पूर्ण;

अटल अंतरभूत व्योम __iomem *nvidia_smmu_page(काष्ठा arm_smmu_device *smmu,
					     अचिन्हित पूर्णांक inst, पूर्णांक page)
अणु
	काष्ठा nvidia_smmu *nvidia_smmu;

	nvidia_smmu = container_of(smmu, काष्ठा nvidia_smmu, smmu);
	वापस nvidia_smmu->bases[inst] + (page << smmu->pgshअगरt);
पूर्ण

अटल u32 nvidia_smmu_पढ़ो_reg(काष्ठा arm_smmu_device *smmu,
				पूर्णांक page, पूर्णांक offset)
अणु
	व्योम __iomem *reg = nvidia_smmu_page(smmu, 0, page) + offset;

	वापस पढ़ोl_relaxed(reg);
पूर्ण

अटल व्योम nvidia_smmu_ग_लिखो_reg(काष्ठा arm_smmu_device *smmu,
				  पूर्णांक page, पूर्णांक offset, u32 val)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NUM_SMMU_INSTANCES; i++) अणु
		व्योम __iomem *reg = nvidia_smmu_page(smmu, i, page) + offset;

		ग_लिखोl_relaxed(val, reg);
	पूर्ण
पूर्ण

अटल u64 nvidia_smmu_पढ़ो_reg64(काष्ठा arm_smmu_device *smmu,
				  पूर्णांक page, पूर्णांक offset)
अणु
	व्योम __iomem *reg = nvidia_smmu_page(smmu, 0, page) + offset;

	वापस पढ़ोq_relaxed(reg);
पूर्ण

अटल व्योम nvidia_smmu_ग_लिखो_reg64(काष्ठा arm_smmu_device *smmu,
				    पूर्णांक page, पूर्णांक offset, u64 val)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NUM_SMMU_INSTANCES; i++) अणु
		व्योम __iomem *reg = nvidia_smmu_page(smmu, i, page) + offset;

		ग_लिखोq_relaxed(val, reg);
	पूर्ण
पूर्ण

अटल व्योम nvidia_smmu_tlb_sync(काष्ठा arm_smmu_device *smmu, पूर्णांक page,
				 पूर्णांक sync, पूर्णांक status)
अणु
	अचिन्हित पूर्णांक delay;

	arm_smmu_ग_लिखोl(smmu, page, sync, 0);

	क्रम (delay = 1; delay < TLB_LOOP_TIMEOUT; delay *= 2) अणु
		अचिन्हित पूर्णांक spin_cnt;

		क्रम (spin_cnt = TLB_SPIN_COUNT; spin_cnt > 0; spin_cnt--) अणु
			u32 val = 0;
			अचिन्हित पूर्णांक i;

			क्रम (i = 0; i < NUM_SMMU_INSTANCES; i++) अणु
				व्योम __iomem *reg;

				reg = nvidia_smmu_page(smmu, i, page) + status;
				val |= पढ़ोl_relaxed(reg);
			पूर्ण

			अगर (!(val & ARM_SMMU_sTLBGSTATUS_GSACTIVE))
				वापस;

			cpu_relax();
		पूर्ण

		udelay(delay);
	पूर्ण

	dev_err_ratelimited(smmu->dev,
			    "TLB sync timed out -- SMMU may be deadlocked\n");
पूर्ण

अटल पूर्णांक nvidia_smmu_reset(काष्ठा arm_smmu_device *smmu)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NUM_SMMU_INSTANCES; i++) अणु
		u32 val;
		व्योम __iomem *reg = nvidia_smmu_page(smmu, i, ARM_SMMU_GR0) +
				    ARM_SMMU_GR0_sGFSR;

		/* clear global FSR */
		val = पढ़ोl_relaxed(reg);
		ग_लिखोl_relaxed(val, reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t nvidia_smmu_global_fault_inst(पूर्णांक irq,
						 काष्ठा arm_smmu_device *smmu,
						 पूर्णांक inst)
अणु
	u32 gfsr, gfsynr0, gfsynr1, gfsynr2;
	व्योम __iomem *gr0_base = nvidia_smmu_page(smmu, inst, 0);

	gfsr = पढ़ोl_relaxed(gr0_base + ARM_SMMU_GR0_sGFSR);
	अगर (!gfsr)
		वापस IRQ_NONE;

	gfsynr0 = पढ़ोl_relaxed(gr0_base + ARM_SMMU_GR0_sGFSYNR0);
	gfsynr1 = पढ़ोl_relaxed(gr0_base + ARM_SMMU_GR0_sGFSYNR1);
	gfsynr2 = पढ़ोl_relaxed(gr0_base + ARM_SMMU_GR0_sGFSYNR2);

	dev_err_ratelimited(smmu->dev,
			    "Unexpected global fault, this could be serious\n");
	dev_err_ratelimited(smmu->dev,
			    "\tGFSR 0x%08x, GFSYNR0 0x%08x, GFSYNR1 0x%08x, GFSYNR2 0x%08x\n",
			    gfsr, gfsynr0, gfsynr1, gfsynr2);

	ग_लिखोl_relaxed(gfsr, gr0_base + ARM_SMMU_GR0_sGFSR);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t nvidia_smmu_global_fault(पूर्णांक irq, व्योम *dev)
अणु
	अचिन्हित पूर्णांक inst;
	irqवापस_t ret = IRQ_NONE;
	काष्ठा arm_smmu_device *smmu = dev;

	क्रम (inst = 0; inst < NUM_SMMU_INSTANCES; inst++) अणु
		irqवापस_t irq_ret;

		irq_ret = nvidia_smmu_global_fault_inst(irq, smmu, inst);
		अगर (irq_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t nvidia_smmu_context_fault_bank(पूर्णांक irq,
						  काष्ठा arm_smmu_device *smmu,
						  पूर्णांक idx, पूर्णांक inst)
अणु
	u32 fsr, fsynr, cbfrsynra;
	अचिन्हित दीर्घ iova;
	व्योम __iomem *gr1_base = nvidia_smmu_page(smmu, inst, 1);
	व्योम __iomem *cb_base = nvidia_smmu_page(smmu, inst, smmu->numpage + idx);

	fsr = पढ़ोl_relaxed(cb_base + ARM_SMMU_CB_FSR);
	अगर (!(fsr & ARM_SMMU_FSR_FAULT))
		वापस IRQ_NONE;

	fsynr = पढ़ोl_relaxed(cb_base + ARM_SMMU_CB_FSYNR0);
	iova = पढ़ोq_relaxed(cb_base + ARM_SMMU_CB_FAR);
	cbfrsynra = पढ़ोl_relaxed(gr1_base + ARM_SMMU_GR1_CBFRSYNRA(idx));

	dev_err_ratelimited(smmu->dev,
			    "Unhandled context fault: fsr=0x%x, iova=0x%08lx, fsynr=0x%x, cbfrsynra=0x%x, cb=%d\n",
			    fsr, iova, fsynr, cbfrsynra, idx);

	ग_लिखोl_relaxed(fsr, cb_base + ARM_SMMU_CB_FSR);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t nvidia_smmu_context_fault(पूर्णांक irq, व्योम *dev)
अणु
	पूर्णांक idx;
	अचिन्हित पूर्णांक inst;
	irqवापस_t ret = IRQ_NONE;
	काष्ठा arm_smmu_device *smmu;
	काष्ठा iommu_करोमुख्य *करोमुख्य = dev;
	काष्ठा arm_smmu_करोमुख्य *smmu_करोमुख्य;

	smmu_करोमुख्य = container_of(करोमुख्य, काष्ठा arm_smmu_करोमुख्य, करोमुख्य);
	smmu = smmu_करोमुख्य->smmu;

	क्रम (inst = 0; inst < NUM_SMMU_INSTANCES; inst++) अणु
		irqवापस_t irq_ret;

		/*
		 * Interrupt line is shared between all contexts.
		 * Check क्रम faults across all contexts.
		 */
		क्रम (idx = 0; idx < smmu->num_context_banks; idx++) अणु
			irq_ret = nvidia_smmu_context_fault_bank(irq, smmu,
								 idx, inst);
			अगर (irq_ret == IRQ_HANDLED)
				ret = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा arm_smmu_impl nvidia_smmu_impl = अणु
	.पढ़ो_reg = nvidia_smmu_पढ़ो_reg,
	.ग_लिखो_reg = nvidia_smmu_ग_लिखो_reg,
	.पढ़ो_reg64 = nvidia_smmu_पढ़ो_reg64,
	.ग_लिखो_reg64 = nvidia_smmu_ग_लिखो_reg64,
	.reset = nvidia_smmu_reset,
	.tlb_sync = nvidia_smmu_tlb_sync,
	.global_fault = nvidia_smmu_global_fault,
	.context_fault = nvidia_smmu_context_fault,
पूर्ण;

काष्ठा arm_smmu_device *nvidia_smmu_impl_init(काष्ठा arm_smmu_device *smmu)
अणु
	काष्ठा resource *res;
	काष्ठा device *dev = smmu->dev;
	काष्ठा nvidia_smmu *nvidia_smmu;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	nvidia_smmu = devm_kपुनः_स्मृति(dev, smmu, माप(*nvidia_smmu), GFP_KERNEL);
	अगर (!nvidia_smmu)
		वापस ERR_PTR(-ENOMEM);

	/* Instance 0 is ioremapped by arm-smmu.c. */
	nvidia_smmu->bases[0] = smmu->base;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res)
		वापस ERR_PTR(-ENODEV);

	nvidia_smmu->bases[1] = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(nvidia_smmu->bases[1]))
		वापस ERR_CAST(nvidia_smmu->bases[1]);

	nvidia_smmu->smmu.impl = &nvidia_smmu_impl;

	वापस &nvidia_smmu->smmu;
पूर्ण
