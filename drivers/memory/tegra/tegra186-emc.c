<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2019 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <soc/tegra/bpmp.h>

काष्ठा tegra186_emc_dvfs अणु
	अचिन्हित दीर्घ latency;
	अचिन्हित दीर्घ rate;
पूर्ण;

काष्ठा tegra186_emc अणु
	काष्ठा tegra_bpmp *bpmp;
	काष्ठा device *dev;
	काष्ठा clk *clk;

	काष्ठा tegra186_emc_dvfs *dvfs;
	अचिन्हित पूर्णांक num_dvfs;

	काष्ठा अणु
		काष्ठा dentry *root;
		अचिन्हित दीर्घ min_rate;
		अचिन्हित दीर्घ max_rate;
	पूर्ण debugfs;
पूर्ण;

/*
 * debugfs पूर्णांकerface
 *
 * The memory controller driver exposes some files in debugfs that can be used
 * to control the EMC frequency. The top-level directory can be found here:
 *
 *   /sys/kernel/debug/emc
 *
 * It contains the following files:
 *
 *   - available_rates: This file contains a list of valid, space-separated
 *     EMC frequencies.
 *
 *   - min_rate: Writing a value to this file sets the given frequency as the
 *       न्यूनमान of the permitted range. If this is higher than the currently
 *       configured EMC frequency, this will cause the frequency to be
 *       increased so that it stays within the valid range.
 *
 *   - max_rate: Similarily to the min_rate file, writing a value to this file
 *       sets the given frequency as the उच्चमानing of the permitted range. If
 *       the value is lower than the currently configured EMC frequency, this
 *       will cause the frequency to be decreased so that it stays within the
 *       valid range.
 */

अटल bool tegra186_emc_validate_rate(काष्ठा tegra186_emc *emc,
				       अचिन्हित दीर्घ rate)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < emc->num_dvfs; i++)
		अगर (rate == emc->dvfs[i].rate)
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक tegra186_emc_debug_available_rates_show(काष्ठा seq_file *s,
						   व्योम *data)
अणु
	काष्ठा tegra186_emc *emc = s->निजी;
	स्थिर अक्षर *prefix = "";
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < emc->num_dvfs; i++) अणु
		seq_म_लिखो(s, "%s%lu", prefix, emc->dvfs[i].rate);
		prefix = " ";
	पूर्ण

	seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_emc_debug_available_rates_खोलो(काष्ठा inode *inode,
						   काष्ठा file *file)
अणु
	वापस single_खोलो(file, tegra186_emc_debug_available_rates_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations tegra186_emc_debug_available_rates_fops = अणु
	.खोलो = tegra186_emc_debug_available_rates_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल पूर्णांक tegra186_emc_debug_min_rate_get(व्योम *data, u64 *rate)
अणु
	काष्ठा tegra186_emc *emc = data;

	*rate = emc->debugfs.min_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_emc_debug_min_rate_set(व्योम *data, u64 rate)
अणु
	काष्ठा tegra186_emc *emc = data;
	पूर्णांक err;

	अगर (!tegra186_emc_validate_rate(emc, rate))
		वापस -EINVAL;

	err = clk_set_min_rate(emc->clk, rate);
	अगर (err < 0)
		वापस err;

	emc->debugfs.min_rate = rate;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(tegra186_emc_debug_min_rate_fops,
			  tegra186_emc_debug_min_rate_get,
			  tegra186_emc_debug_min_rate_set, "%llu\n");

अटल पूर्णांक tegra186_emc_debug_max_rate_get(व्योम *data, u64 *rate)
अणु
	काष्ठा tegra186_emc *emc = data;

	*rate = emc->debugfs.max_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_emc_debug_max_rate_set(व्योम *data, u64 rate)
अणु
	काष्ठा tegra186_emc *emc = data;
	पूर्णांक err;

	अगर (!tegra186_emc_validate_rate(emc, rate))
		वापस -EINVAL;

	err = clk_set_max_rate(emc->clk, rate);
	अगर (err < 0)
		वापस err;

	emc->debugfs.max_rate = rate;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(tegra186_emc_debug_max_rate_fops,
			  tegra186_emc_debug_max_rate_get,
			  tegra186_emc_debug_max_rate_set, "%llu\n");

अटल पूर्णांक tegra186_emc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mrq_emc_dvfs_latency_response response;
	काष्ठा tegra_bpmp_message msg;
	काष्ठा tegra186_emc *emc;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	emc = devm_kzalloc(&pdev->dev, माप(*emc), GFP_KERNEL);
	अगर (!emc)
		वापस -ENOMEM;

	emc->bpmp = tegra_bpmp_get(&pdev->dev);
	अगर (IS_ERR(emc->bpmp))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(emc->bpmp), "failed to get BPMP\n");

	emc->clk = devm_clk_get(&pdev->dev, "emc");
	अगर (IS_ERR(emc->clk)) अणु
		err = PTR_ERR(emc->clk);
		dev_err(&pdev->dev, "failed to get EMC clock: %d\n", err);
		जाओ put_bpmp;
	पूर्ण

	platक्रमm_set_drvdata(pdev, emc);
	emc->dev = &pdev->dev;

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_EMC_DVFS_LATENCY;
	msg.tx.data = शून्य;
	msg.tx.size = 0;
	msg.rx.data = &response;
	msg.rx.size = माप(response);

	err = tegra_bpmp_transfer(emc->bpmp, &msg);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to EMC DVFS pairs: %d\n", err);
		जाओ put_bpmp;
	पूर्ण

	emc->debugfs.min_rate = अच_दीर्घ_उच्च;
	emc->debugfs.max_rate = 0;

	emc->num_dvfs = response.num_pairs;

	emc->dvfs = devm_kदो_स्मृति_array(&pdev->dev, emc->num_dvfs,
				       माप(*emc->dvfs), GFP_KERNEL);
	अगर (!emc->dvfs) अणु
		err = -ENOMEM;
		जाओ put_bpmp;
	पूर्ण

	dev_dbg(&pdev->dev, "%u DVFS pairs:\n", emc->num_dvfs);

	क्रम (i = 0; i < emc->num_dvfs; i++) अणु
		emc->dvfs[i].rate = response.pairs[i].freq * 1000;
		emc->dvfs[i].latency = response.pairs[i].latency;

		अगर (emc->dvfs[i].rate < emc->debugfs.min_rate)
			emc->debugfs.min_rate = emc->dvfs[i].rate;

		अगर (emc->dvfs[i].rate > emc->debugfs.max_rate)
			emc->debugfs.max_rate = emc->dvfs[i].rate;

		dev_dbg(&pdev->dev, "  %2u: %lu Hz -> %lu us\n", i,
			emc->dvfs[i].rate, emc->dvfs[i].latency);
	पूर्ण

	err = clk_set_rate_range(emc->clk, emc->debugfs.min_rate,
				 emc->debugfs.max_rate);
	अगर (err < 0) अणु
		dev_err(&pdev->dev,
			"failed to set rate range [%lu-%lu] for %pC\n",
			emc->debugfs.min_rate, emc->debugfs.max_rate,
			emc->clk);
		जाओ put_bpmp;
	पूर्ण

	emc->debugfs.root = debugfs_create_dir("emc", शून्य);
	debugfs_create_file("available_rates", S_IRUGO, emc->debugfs.root,
			    emc, &tegra186_emc_debug_available_rates_fops);
	debugfs_create_file("min_rate", S_IRUGO | S_IWUSR, emc->debugfs.root,
			    emc, &tegra186_emc_debug_min_rate_fops);
	debugfs_create_file("max_rate", S_IRUGO | S_IWUSR, emc->debugfs.root,
			    emc, &tegra186_emc_debug_max_rate_fops);

	वापस 0;

put_bpmp:
	tegra_bpmp_put(emc->bpmp);
	वापस err;
पूर्ण

अटल पूर्णांक tegra186_emc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra186_emc *emc = platक्रमm_get_drvdata(pdev);

	debugfs_हटाओ_recursive(emc->debugfs.root);
	tegra_bpmp_put(emc->bpmp);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra186_emc_of_match[] = अणु
#अगर defined(CONFIG_ARCH_TEGRA_186_SOC)
	अणु .compatible = "nvidia,tegra186-emc" पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_TEGRA_194_SOC)
	अणु .compatible = "nvidia,tegra194-emc" पूर्ण,
#पूर्ण_अगर
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra186_emc_of_match);

अटल काष्ठा platक्रमm_driver tegra186_emc_driver = अणु
	.driver = अणु
		.name = "tegra186-emc",
		.of_match_table = tegra186_emc_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = tegra186_emc_probe,
	.हटाओ = tegra186_emc_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra186_emc_driver);

MODULE_AUTHOR("Thierry Reding <treding@nvidia.com>");
MODULE_DESCRIPTION("NVIDIA Tegra186 External Memory Controller driver");
MODULE_LICENSE("GPL v2");
