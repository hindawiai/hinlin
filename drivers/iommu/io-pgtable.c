<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic page table allocator क्रम IOMMUs.
 *
 * Copyright (C) 2014 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */

#समावेश <linux/bug.h>
#समावेश <linux/io-pgtable.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

अटल स्थिर काष्ठा io_pgtable_init_fns *
io_pgtable_init_table[IO_PGTABLE_NUM_FMTS] = अणु
#अगर_घोषित CONFIG_IOMMU_IO_PGTABLE_LPAE
	[ARM_32_LPAE_S1] = &io_pgtable_arm_32_lpae_s1_init_fns,
	[ARM_32_LPAE_S2] = &io_pgtable_arm_32_lpae_s2_init_fns,
	[ARM_64_LPAE_S1] = &io_pgtable_arm_64_lpae_s1_init_fns,
	[ARM_64_LPAE_S2] = &io_pgtable_arm_64_lpae_s2_init_fns,
	[ARM_MALI_LPAE] = &io_pgtable_arm_mali_lpae_init_fns,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IOMMU_IO_PGTABLE_ARMV7S
	[ARM_V7S] = &io_pgtable_arm_v7s_init_fns,
#पूर्ण_अगर
#अगर_घोषित CONFIG_AMD_IOMMU
	[AMD_IOMMU_V1] = &io_pgtable_amd_iommu_v1_init_fns,
#पूर्ण_अगर
पूर्ण;

काष्ठा io_pgtable_ops *alloc_io_pgtable_ops(क्रमागत io_pgtable_fmt fmt,
					    काष्ठा io_pgtable_cfg *cfg,
					    व्योम *cookie)
अणु
	काष्ठा io_pgtable *iop;
	स्थिर काष्ठा io_pgtable_init_fns *fns;

	अगर (fmt >= IO_PGTABLE_NUM_FMTS)
		वापस शून्य;

	fns = io_pgtable_init_table[fmt];
	अगर (!fns)
		वापस शून्य;

	iop = fns->alloc(cfg, cookie);
	अगर (!iop)
		वापस शून्य;

	iop->fmt	= fmt;
	iop->cookie	= cookie;
	iop->cfg	= *cfg;

	वापस &iop->ops;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_io_pgtable_ops);

/*
 * It is the IOMMU driver's responsibility to ensure that the page table
 * is no दीर्घer accessible to the walker by this poपूर्णांक.
 */
व्योम मुक्त_io_pgtable_ops(काष्ठा io_pgtable_ops *ops)
अणु
	काष्ठा io_pgtable *iop;

	अगर (!ops)
		वापस;

	iop = io_pgtable_ops_to_pgtable(ops);
	io_pgtable_tlb_flush_all(iop);
	io_pgtable_init_table[iop->fmt]->मुक्त(iop);
पूर्ण
EXPORT_SYMBOL_GPL(मुक्त_io_pgtable_ops);
