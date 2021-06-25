<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (c) 2011, The Linux Foundation. All rights reserved.
 */
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश "mmci.h"

/* Registers */
#घोषणा DML_CONFIG			0x00
#घोषणा PRODUCER_CRCI_MSK		GENMASK(1, 0)
#घोषणा PRODUCER_CRCI_DISABLE		0
#घोषणा PRODUCER_CRCI_X_SEL		BIT(0)
#घोषणा PRODUCER_CRCI_Y_SEL		BIT(1)
#घोषणा CONSUMER_CRCI_MSK		GENMASK(3, 2)
#घोषणा CONSUMER_CRCI_DISABLE		0
#घोषणा CONSUMER_CRCI_X_SEL		BIT(2)
#घोषणा CONSUMER_CRCI_Y_SEL		BIT(3)
#घोषणा PRODUCER_TRANS_END_EN		BIT(4)
#घोषणा BYPASS				BIT(16)
#घोषणा सूचीECT_MODE			BIT(17)
#घोषणा INFINITE_CONS_TRANS		BIT(18)

#घोषणा DML_SW_RESET			0x08
#घोषणा DML_PRODUCER_START		0x0c
#घोषणा DML_CONSUMER_START		0x10
#घोषणा DML_PRODUCER_PIPE_LOGICAL_SIZE	0x14
#घोषणा DML_CONSUMER_PIPE_LOGICAL_SIZE	0x18
#घोषणा DML_PIPE_ID			0x1c
#घोषणा PRODUCER_PIPE_ID_SHFT		0
#घोषणा PRODUCER_PIPE_ID_MSK		GENMASK(4, 0)
#घोषणा CONSUMER_PIPE_ID_SHFT		16
#घोषणा CONSUMER_PIPE_ID_MSK		GENMASK(20, 16)

#घोषणा DML_PRODUCER_BAM_BLOCK_SIZE	0x24
#घोषणा DML_PRODUCER_BAM_TRANS_SIZE	0x28

/* other definitions */
#घोषणा PRODUCER_PIPE_LOGICAL_SIZE	4096
#घोषणा CONSUMER_PIPE_LOGICAL_SIZE	4096

#घोषणा DML_OFFSET			0x800

अटल पूर्णांक qcom_dma_start(काष्ठा mmci_host *host, अचिन्हित पूर्णांक *datactrl)
अणु
	u32 config;
	व्योम __iomem *base = host->base + DML_OFFSET;
	काष्ठा mmc_data *data = host->data;
	पूर्णांक ret = mmci_dmae_start(host, datactrl);

	अगर (ret)
		वापस ret;

	अगर (data->flags & MMC_DATA_READ) अणु
		/* Read operation: configure DML क्रम producer operation */
		/* Set producer CRCI-x and disable consumer CRCI */
		config = पढ़ोl_relaxed(base + DML_CONFIG);
		config = (config & ~PRODUCER_CRCI_MSK) | PRODUCER_CRCI_X_SEL;
		config = (config & ~CONSUMER_CRCI_MSK) | CONSUMER_CRCI_DISABLE;
		ग_लिखोl_relaxed(config, base + DML_CONFIG);

		/* Set the Producer BAM block size */
		ग_लिखोl_relaxed(data->blksz, base + DML_PRODUCER_BAM_BLOCK_SIZE);

		/* Set Producer BAM Transaction size */
		ग_लिखोl_relaxed(data->blocks * data->blksz,
			       base + DML_PRODUCER_BAM_TRANS_SIZE);
		/* Set Producer Transaction End bit */
		config = पढ़ोl_relaxed(base + DML_CONFIG);
		config |= PRODUCER_TRANS_END_EN;
		ग_लिखोl_relaxed(config, base + DML_CONFIG);
		/* Trigger producer */
		ग_लिखोl_relaxed(1, base + DML_PRODUCER_START);
	पूर्ण अन्यथा अणु
		/* Write operation: configure DML क्रम consumer operation */
		/* Set consumer CRCI-x and disable producer CRCI*/
		config = पढ़ोl_relaxed(base + DML_CONFIG);
		config = (config & ~CONSUMER_CRCI_MSK) | CONSUMER_CRCI_X_SEL;
		config = (config & ~PRODUCER_CRCI_MSK) | PRODUCER_CRCI_DISABLE;
		ग_लिखोl_relaxed(config, base + DML_CONFIG);
		/* Clear Producer Transaction End bit */
		config = पढ़ोl_relaxed(base + DML_CONFIG);
		config &= ~PRODUCER_TRANS_END_EN;
		ग_लिखोl_relaxed(config, base + DML_CONFIG);
		/* Trigger consumer */
		ग_लिखोl_relaxed(1, base + DML_CONSUMER_START);
	पूर्ण

	/* make sure the dml is configured beक्रमe dma is triggered */
	wmb();
	वापस 0;
पूर्ण

अटल पूर्णांक of_get_dml_pipe_index(काष्ठा device_node *np, स्थिर अक्षर *name)
अणु
	पूर्णांक index;
	काष्ठा of_phandle_args	dma_spec;

	index = of_property_match_string(np, "dma-names", name);

	अगर (index < 0)
		वापस -ENODEV;

	अगर (of_parse_phandle_with_args(np, "dmas", "#dma-cells", index,
				       &dma_spec))
		वापस -ENODEV;

	अगर (dma_spec.args_count)
		वापस dma_spec.args[0];

	वापस -ENODEV;
पूर्ण

/* Initialize the dml hardware connected to SD Card controller */
अटल पूर्णांक qcom_dma_setup(काष्ठा mmci_host *host)
अणु
	u32 config;
	व्योम __iomem *base;
	पूर्णांक consumer_id, producer_id;
	काष्ठा device_node *np = host->mmc->parent->of_node;

	अगर (mmci_dmae_setup(host))
		वापस -EINVAL;

	consumer_id = of_get_dml_pipe_index(np, "tx");
	producer_id = of_get_dml_pipe_index(np, "rx");

	अगर (producer_id < 0 || consumer_id < 0) अणु
		mmci_dmae_release(host);
		वापस -EINVAL;
	पूर्ण

	base = host->base + DML_OFFSET;

	/* Reset the DML block */
	ग_लिखोl_relaxed(1, base + DML_SW_RESET);

	/* Disable the producer and consumer CRCI */
	config = (PRODUCER_CRCI_DISABLE | CONSUMER_CRCI_DISABLE);
	/*
	 * Disable the bypass mode. Bypass mode will only be used
	 * अगर data transfer is to happen in PIO mode and करोn't
	 * want the BAM पूर्णांकerface to connect with SDCC-DML.
	 */
	config &= ~BYPASS;
	/*
	 * Disable direct mode as we करोn't DML to MASTER the AHB bus.
	 * BAM connected with DML should MASTER the AHB bus.
	 */
	config &= ~सूचीECT_MODE;
	/*
	 * Disable infinite mode transfer as we won't be करोing any
	 * infinite size data transfers. All data transfer will be
	 * of finite data size.
	 */
	config &= ~INFINITE_CONS_TRANS;
	ग_लिखोl_relaxed(config, base + DML_CONFIG);

	/*
	 * Initialize the logical BAM pipe size क्रम producer
	 * and consumer.
	 */
	ग_लिखोl_relaxed(PRODUCER_PIPE_LOGICAL_SIZE,
		       base + DML_PRODUCER_PIPE_LOGICAL_SIZE);
	ग_लिखोl_relaxed(CONSUMER_PIPE_LOGICAL_SIZE,
		       base + DML_CONSUMER_PIPE_LOGICAL_SIZE);

	/* Initialize Producer/consumer pipe id */
	ग_लिखोl_relaxed(producer_id | (consumer_id << CONSUMER_PIPE_ID_SHFT),
		       base + DML_PIPE_ID);

	/* Make sure dml initialization is finished */
	mb();

	वापस 0;
पूर्ण

अटल u32 qcom_get_dctrl_cfg(काष्ठा mmci_host *host)
अणु
	वापस MCI_DPSM_ENABLE | (host->data->blksz << 4);
पूर्ण

अटल काष्ठा mmci_host_ops qcom_variant_ops = अणु
	.prep_data = mmci_dmae_prep_data,
	.unprep_data = mmci_dmae_unprep_data,
	.get_datactrl_cfg = qcom_get_dctrl_cfg,
	.get_next_data = mmci_dmae_get_next_data,
	.dma_setup = qcom_dma_setup,
	.dma_release = mmci_dmae_release,
	.dma_start = qcom_dma_start,
	.dma_finalize = mmci_dmae_finalize,
	.dma_error = mmci_dmae_error,
पूर्ण;

व्योम qcom_variant_init(काष्ठा mmci_host *host)
अणु
	host->ops = &qcom_variant_ops;
पूर्ण
