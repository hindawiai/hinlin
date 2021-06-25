<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 NVIDIA Corporation
 */

#अगर_अघोषित __SOC_TEGRA_MC_H__
#घोषणा __SOC_TEGRA_MC_H__

#समावेश <linux/bits.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerconnect-provider.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/types.h>

काष्ठा clk;
काष्ठा device;
काष्ठा page;

काष्ठा tegra_smmu_enable अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक bit;
पूर्ण;

काष्ठा tegra_mc_timing अणु
	अचिन्हित दीर्घ rate;

	u32 *emem_data;
पूर्ण;

/* latency allowance */
काष्ठा tegra_mc_la अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक def;
पूर्ण;

काष्ठा tegra_mc_client अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक swgroup;

	अचिन्हित पूर्णांक fअगरo_size;

	काष्ठा tegra_smmu_enable smmu;
	काष्ठा tegra_mc_la la;
पूर्ण;

काष्ठा tegra_smmu_swgroup अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक swgroup;
	अचिन्हित पूर्णांक reg;
पूर्ण;

काष्ठा tegra_smmu_group_soc अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *swgroups;
	अचिन्हित पूर्णांक num_swgroups;
पूर्ण;

काष्ठा tegra_smmu_soc अणु
	स्थिर काष्ठा tegra_mc_client *clients;
	अचिन्हित पूर्णांक num_clients;

	स्थिर काष्ठा tegra_smmu_swgroup *swgroups;
	अचिन्हित पूर्णांक num_swgroups;

	स्थिर काष्ठा tegra_smmu_group_soc *groups;
	अचिन्हित पूर्णांक num_groups;

	bool supports_round_robin_arbitration;
	bool supports_request_limit;

	अचिन्हित पूर्णांक num_tlb_lines;
	अचिन्हित पूर्णांक num_asids;
पूर्ण;

काष्ठा tegra_mc;
काष्ठा tegra_smmu;
काष्ठा gart_device;

#अगर_घोषित CONFIG_TEGRA_IOMMU_SMMU
काष्ठा tegra_smmu *tegra_smmu_probe(काष्ठा device *dev,
				    स्थिर काष्ठा tegra_smmu_soc *soc,
				    काष्ठा tegra_mc *mc);
व्योम tegra_smmu_हटाओ(काष्ठा tegra_smmu *smmu);
#अन्यथा
अटल अंतरभूत काष्ठा tegra_smmu *
tegra_smmu_probe(काष्ठा device *dev, स्थिर काष्ठा tegra_smmu_soc *soc,
		 काष्ठा tegra_mc *mc)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम tegra_smmu_हटाओ(काष्ठा tegra_smmu *smmu)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_TEGRA_IOMMU_GART
काष्ठा gart_device *tegra_gart_probe(काष्ठा device *dev, काष्ठा tegra_mc *mc);
पूर्णांक tegra_gart_suspend(काष्ठा gart_device *gart);
पूर्णांक tegra_gart_resume(काष्ठा gart_device *gart);
#अन्यथा
अटल अंतरभूत काष्ठा gart_device *
tegra_gart_probe(काष्ठा device *dev, काष्ठा tegra_mc *mc)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत पूर्णांक tegra_gart_suspend(काष्ठा gart_device *gart)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक tegra_gart_resume(काष्ठा gart_device *gart)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

काष्ठा tegra_mc_reset अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ id;
	अचिन्हित पूर्णांक control;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक reset;
	अचिन्हित पूर्णांक bit;
पूर्ण;

काष्ठा tegra_mc_reset_ops अणु
	पूर्णांक (*hotreset_निश्चित)(काष्ठा tegra_mc *mc,
			       स्थिर काष्ठा tegra_mc_reset *rst);
	पूर्णांक (*hotreset_deनिश्चित)(काष्ठा tegra_mc *mc,
				 स्थिर काष्ठा tegra_mc_reset *rst);
	पूर्णांक (*block_dma)(काष्ठा tegra_mc *mc,
			 स्थिर काष्ठा tegra_mc_reset *rst);
	bool (*dma_idling)(काष्ठा tegra_mc *mc,
			   स्थिर काष्ठा tegra_mc_reset *rst);
	पूर्णांक (*unblock_dma)(काष्ठा tegra_mc *mc,
			   स्थिर काष्ठा tegra_mc_reset *rst);
	पूर्णांक (*reset_status)(काष्ठा tegra_mc *mc,
			    स्थिर काष्ठा tegra_mc_reset *rst);
पूर्ण;

#घोषणा TEGRA_MC_ICC_TAG_DEFAULT				0
#घोषणा TEGRA_MC_ICC_TAG_ISO					BIT(0)

काष्ठा tegra_mc_icc_ops अणु
	पूर्णांक (*set)(काष्ठा icc_node *src, काष्ठा icc_node *dst);
	पूर्णांक (*aggregate)(काष्ठा icc_node *node, u32 tag, u32 avg_bw,
			 u32 peak_bw, u32 *agg_avg, u32 *agg_peak);
	काष्ठा icc_node_data *(*xlate_extended)(काष्ठा of_phandle_args *spec,
						व्योम *data);
पूर्ण;

काष्ठा tegra_mc_soc अणु
	स्थिर काष्ठा tegra_mc_client *clients;
	अचिन्हित पूर्णांक num_clients;

	स्थिर अचिन्हित दीर्घ *emem_regs;
	अचिन्हित पूर्णांक num_emem_regs;

	अचिन्हित पूर्णांक num_address_bits;
	अचिन्हित पूर्णांक atom_size;

	u8 client_id_mask;

	स्थिर काष्ठा tegra_smmu_soc *smmu;

	u32 पूर्णांकmask;

	स्थिर काष्ठा tegra_mc_reset_ops *reset_ops;
	स्थिर काष्ठा tegra_mc_reset *resets;
	अचिन्हित पूर्णांक num_resets;

	स्थिर काष्ठा tegra_mc_icc_ops *icc_ops;

	पूर्णांक (*init)(काष्ठा tegra_mc *mc);
पूर्ण;

काष्ठा tegra_mc अणु
	काष्ठा device *dev;
	काष्ठा tegra_smmu *smmu;
	काष्ठा gart_device *gart;
	व्योम __iomem *regs;
	काष्ठा clk *clk;
	पूर्णांक irq;

	स्थिर काष्ठा tegra_mc_soc *soc;
	अचिन्हित दीर्घ tick;

	काष्ठा tegra_mc_timing *timings;
	अचिन्हित पूर्णांक num_timings;

	काष्ठा reset_controller_dev reset;

	काष्ठा icc_provider provider;

	spinlock_t lock;

	काष्ठा अणु
		काष्ठा dentry *root;
	पूर्ण debugfs;
पूर्ण;

पूर्णांक tegra_mc_ग_लिखो_emem_configuration(काष्ठा tegra_mc *mc, अचिन्हित दीर्घ rate);
अचिन्हित पूर्णांक tegra_mc_get_emem_device_count(काष्ठा tegra_mc *mc);

#अगर_घोषित CONFIG_TEGRA_MC
काष्ठा tegra_mc *devm_tegra_memory_controller_get(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत काष्ठा tegra_mc *
devm_tegra_memory_controller_get(काष्ठा device *dev)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __SOC_TEGRA_MC_H__ */
