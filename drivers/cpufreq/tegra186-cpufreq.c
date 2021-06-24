<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017, NVIDIA CORPORATION. All rights reserved
 */

#समावेश <linux/cpufreq.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <soc/tegra/bpmp.h>
#समावेश <soc/tegra/bpmp-abi.h>

#घोषणा TEGRA186_NUM_CLUSTERS		2
#घोषणा EDVD_OFFSET_A57(core)		((SZ_64K * 6) + (0x20 + (core) * 0x4))
#घोषणा EDVD_OFFSET_DENVER(core)	((SZ_64K * 7) + (0x20 + (core) * 0x4))
#घोषणा EDVD_CORE_VOLT_FREQ_F_SHIFT	0
#घोषणा EDVD_CORE_VOLT_FREQ_F_MASK	0xffff
#घोषणा EDVD_CORE_VOLT_FREQ_V_SHIFT	16

काष्ठा tegra186_cpufreq_cpu अणु
	अचिन्हित पूर्णांक bpmp_cluster_id;
	अचिन्हित पूर्णांक edvd_offset;
पूर्ण;

अटल स्थिर काष्ठा tegra186_cpufreq_cpu tegra186_cpus[] = अणु
	/* CPU0 - A57 Cluster */
	अणु
		.bpmp_cluster_id = 1,
		.edvd_offset = EDVD_OFFSET_A57(0)
	पूर्ण,
	/* CPU1 - Denver Cluster */
	अणु
		.bpmp_cluster_id = 0,
		.edvd_offset = EDVD_OFFSET_DENVER(0)
	पूर्ण,
	/* CPU2 - Denver Cluster */
	अणु
		.bpmp_cluster_id = 0,
		.edvd_offset = EDVD_OFFSET_DENVER(1)
	पूर्ण,
	/* CPU3 - A57 Cluster */
	अणु
		.bpmp_cluster_id = 1,
		.edvd_offset = EDVD_OFFSET_A57(1)
	पूर्ण,
	/* CPU4 - A57 Cluster */
	अणु
		.bpmp_cluster_id = 1,
		.edvd_offset = EDVD_OFFSET_A57(2)
	पूर्ण,
	/* CPU5 - A57 Cluster */
	अणु
		.bpmp_cluster_id = 1,
		.edvd_offset = EDVD_OFFSET_A57(3)
	पूर्ण,
पूर्ण;

काष्ठा tegra186_cpufreq_cluster अणु
	काष्ठा cpufreq_frequency_table *table;
	u32 ref_clk_khz;
	u32 भाग;
पूर्ण;

काष्ठा tegra186_cpufreq_data अणु
	व्योम __iomem *regs;
	काष्ठा tegra186_cpufreq_cluster *clusters;
	स्थिर काष्ठा tegra186_cpufreq_cpu *cpus;
पूर्ण;

अटल पूर्णांक tegra186_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा tegra186_cpufreq_data *data = cpufreq_get_driver_data();
	अचिन्हित पूर्णांक cluster = data->cpus[policy->cpu].bpmp_cluster_id;

	policy->freq_table = data->clusters[cluster].table;
	policy->cpuinfo.transition_latency = 300 * 1000;
	policy->driver_data = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_cpufreq_set_target(काष्ठा cpufreq_policy *policy,
				       अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra186_cpufreq_data *data = cpufreq_get_driver_data();
	काष्ठा cpufreq_frequency_table *tbl = policy->freq_table + index;
	अचिन्हित पूर्णांक edvd_offset = data->cpus[policy->cpu].edvd_offset;
	u32 edvd_val = tbl->driver_data;

	ग_लिखोl(edvd_val, data->regs + edvd_offset);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक tegra186_cpufreq_get(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा tegra186_cpufreq_data *data = cpufreq_get_driver_data();
	काष्ठा tegra186_cpufreq_cluster *cluster;
	काष्ठा cpufreq_policy *policy;
	अचिन्हित पूर्णांक edvd_offset, cluster_id;
	u32 nभाग;

	policy = cpufreq_cpu_get(cpu);
	अगर (!policy)
		वापस 0;

	edvd_offset = data->cpus[policy->cpu].edvd_offset;
	nभाग = पढ़ोl(data->regs + edvd_offset) & EDVD_CORE_VOLT_FREQ_F_MASK;
	cluster_id = data->cpus[policy->cpu].bpmp_cluster_id;
	cluster = &data->clusters[cluster_id];
	cpufreq_cpu_put(policy);

	वापस (cluster->ref_clk_khz * nभाग) / cluster->भाग;
पूर्ण

अटल काष्ठा cpufreq_driver tegra186_cpufreq_driver = अणु
	.name = "tegra186",
	.flags = CPUFREQ_HAVE_GOVERNOR_PER_POLICY |
			CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.get = tegra186_cpufreq_get,
	.verअगरy = cpufreq_generic_frequency_table_verअगरy,
	.target_index = tegra186_cpufreq_set_target,
	.init = tegra186_cpufreq_init,
	.attr = cpufreq_generic_attr,
पूर्ण;

अटल काष्ठा cpufreq_frequency_table *init_vhपूर्णांक_table(
	काष्ठा platक्रमm_device *pdev, काष्ठा tegra_bpmp *bpmp,
	काष्ठा tegra186_cpufreq_cluster *cluster, अचिन्हित पूर्णांक cluster_id)
अणु
	काष्ठा cpufreq_frequency_table *table;
	काष्ठा mrq_cpu_vhपूर्णांक_request req;
	काष्ठा tegra_bpmp_message msg;
	काष्ठा cpu_vhपूर्णांक_data *data;
	पूर्णांक err, i, j, num_rates = 0;
	dma_addr_t phys;
	व्योम *virt;

	virt = dma_alloc_coherent(bpmp->dev, माप(*data), &phys,
				  GFP_KERNEL);
	अगर (!virt)
		वापस ERR_PTR(-ENOMEM);

	data = (काष्ठा cpu_vhपूर्णांक_data *)virt;

	स_रखो(&req, 0, माप(req));
	req.addr = phys;
	req.cluster_id = cluster_id;

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_CPU_VHINT;
	msg.tx.data = &req;
	msg.tx.size = माप(req);

	err = tegra_bpmp_transfer(bpmp, &msg);
	अगर (err) अणु
		table = ERR_PTR(err);
		जाओ मुक्त;
	पूर्ण

	क्रम (i = data->vन्यूनमान; i <= data->vउच्चमान; i++) अणु
		u16 nभाग = data->nभाग[i];

		अगर (nभाग < data->nभाग_min || nभाग > data->nभाग_max)
			जारी;

		/* Only store lowest voltage index क्रम each rate */
		अगर (i > 0 && nभाग == data->nभाग[i - 1])
			जारी;

		num_rates++;
	पूर्ण

	table = devm_kसुस्मृति(&pdev->dev, num_rates + 1, माप(*table),
			     GFP_KERNEL);
	अगर (!table) अणु
		table = ERR_PTR(-ENOMEM);
		जाओ मुक्त;
	पूर्ण

	cluster->ref_clk_khz = data->ref_clk_hz / 1000;
	cluster->भाग = data->pभाग * data->mभाग;

	क्रम (i = data->vन्यूनमान, j = 0; i <= data->vउच्चमान; i++) अणु
		काष्ठा cpufreq_frequency_table *poपूर्णांक;
		u16 nभाग = data->nभाग[i];
		u32 edvd_val = 0;

		अगर (nभाग < data->nभाग_min || nभाग > data->nभाग_max)
			जारी;

		/* Only store lowest voltage index क्रम each rate */
		अगर (i > 0 && nभाग == data->nभाग[i - 1])
			जारी;

		edvd_val |= i << EDVD_CORE_VOLT_FREQ_V_SHIFT;
		edvd_val |= nभाग << EDVD_CORE_VOLT_FREQ_F_SHIFT;

		poपूर्णांक = &table[j++];
		poपूर्णांक->driver_data = edvd_val;
		poपूर्णांक->frequency = (cluster->ref_clk_khz * nभाग) / cluster->भाग;
	पूर्ण

	table[j].frequency = CPUFREQ_TABLE_END;

मुक्त:
	dma_मुक्त_coherent(bpmp->dev, माप(*data), virt, phys);

	वापस table;
पूर्ण

अटल पूर्णांक tegra186_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra186_cpufreq_data *data;
	काष्ठा tegra_bpmp *bpmp;
	अचिन्हित पूर्णांक i = 0, err;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->clusters = devm_kसुस्मृति(&pdev->dev, TEGRA186_NUM_CLUSTERS,
				      माप(*data->clusters), GFP_KERNEL);
	अगर (!data->clusters)
		वापस -ENOMEM;

	data->cpus = tegra186_cpus;

	bpmp = tegra_bpmp_get(&pdev->dev);
	अगर (IS_ERR(bpmp))
		वापस PTR_ERR(bpmp);

	data->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->regs)) अणु
		err = PTR_ERR(data->regs);
		जाओ put_bpmp;
	पूर्ण

	क्रम (i = 0; i < TEGRA186_NUM_CLUSTERS; i++) अणु
		काष्ठा tegra186_cpufreq_cluster *cluster = &data->clusters[i];

		cluster->table = init_vhपूर्णांक_table(pdev, bpmp, cluster, i);
		अगर (IS_ERR(cluster->table)) अणु
			err = PTR_ERR(cluster->table);
			जाओ put_bpmp;
		पूर्ण
	पूर्ण

	tegra186_cpufreq_driver.driver_data = data;

	err = cpufreq_रेजिस्टर_driver(&tegra186_cpufreq_driver);

put_bpmp:
	tegra_bpmp_put(bpmp);

	वापस err;
पूर्ण

अटल पूर्णांक tegra186_cpufreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	cpufreq_unरेजिस्टर_driver(&tegra186_cpufreq_driver);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra186_cpufreq_of_match[] = अणु
	अणु .compatible = "nvidia,tegra186-ccplex-cluster", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra186_cpufreq_of_match);

अटल काष्ठा platक्रमm_driver tegra186_cpufreq_platक्रमm_driver = अणु
	.driver = अणु
		.name = "tegra186-cpufreq",
		.of_match_table = tegra186_cpufreq_of_match,
	पूर्ण,
	.probe = tegra186_cpufreq_probe,
	.हटाओ = tegra186_cpufreq_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra186_cpufreq_platक्रमm_driver);

MODULE_AUTHOR("Mikko Perttunen <mperttunen@nvidia.com>");
MODULE_DESCRIPTION("NVIDIA Tegra186 cpufreq driver");
MODULE_LICENSE("GPL v2");
