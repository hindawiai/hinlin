<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/of_reserved_स्मृति.स>

#समावेश "tegra210-emc.h"

#घोषणा TEGRA_EMC_MAX_FREQS		16

अटल पूर्णांक tegra210_emc_table_device_init(काष्ठा reserved_mem *rmem,
					  काष्ठा device *dev)
अणु
	काष्ठा tegra210_emc *emc = dev_get_drvdata(dev);
	काष्ठा tegra210_emc_timing *timings;
	अचिन्हित पूर्णांक i, count = 0;

	timings = memremap(rmem->base, rmem->size, MEMREMAP_WB);
	अगर (!timings) अणु
		dev_err(dev, "failed to map EMC table\n");
		वापस -ENOMEM;
	पूर्ण

	count = 0;

	क्रम (i = 0; i < TEGRA_EMC_MAX_FREQS; i++) अणु
		अगर (timings[i].revision == 0)
			अवरोध;

		count++;
	पूर्ण

	/* only the nominal and derated tables are expected */
	अगर (emc->derated) अणु
		dev_warn(dev, "excess EMC table '%s'\n", rmem->name);
		जाओ out;
	पूर्ण

	अगर (emc->nominal) अणु
		अगर (count != emc->num_timings) अणु
			dev_warn(dev, "%u derated vs. %u nominal entries\n",
				 count, emc->num_timings);
			memunmap(timings);
			वापस -EINVAL;
		पूर्ण

		emc->derated = timings;
	पूर्ण अन्यथा अणु
		emc->num_timings = count;
		emc->nominal = timings;
	पूर्ण

out:
	/* keep track of which table this is */
	rmem->priv = timings;

	वापस 0;
पूर्ण

अटल व्योम tegra210_emc_table_device_release(काष्ठा reserved_mem *rmem,
					      काष्ठा device *dev)
अणु
	काष्ठा tegra210_emc_timing *timings = rmem->priv;
	काष्ठा tegra210_emc *emc = dev_get_drvdata(dev);

	अगर ((emc->nominal && timings != emc->nominal) &&
	    (emc->derated && timings != emc->derated))
		dev_warn(dev, "trying to release unassigned EMC table '%s'\n",
			 rmem->name);

	memunmap(timings);
पूर्ण

अटल स्थिर काष्ठा reserved_mem_ops tegra210_emc_table_ops = अणु
	.device_init = tegra210_emc_table_device_init,
	.device_release = tegra210_emc_table_device_release,
पूर्ण;

अटल पूर्णांक tegra210_emc_table_init(काष्ठा reserved_mem *rmem)
अणु
	pr_debug("Tegra210 EMC table at %pa, size %lu bytes\n", &rmem->base,
		 (अचिन्हित दीर्घ)rmem->size);

	rmem->ops = &tegra210_emc_table_ops;

	वापस 0;
पूर्ण
RESERVEDMEM_OF_DECLARE(tegra210_emc_table, "nvidia,tegra210-emc-table",
		       tegra210_emc_table_init);
