<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Freescale MPC8610HPCD ALSA SoC Machine driver
//
// Author: Timur Tabi <timur@मुक्तscale.com>
//
// Copyright 2007-2010 Freescale Semiconductor, Inc.

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fsl/guts.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <sound/soc.h>

#समावेश "fsl_dma.h"
#समावेश "fsl_ssi.h"
#समावेश "fsl_utils.h"

/* There's only one global utilities रेजिस्टर */
अटल phys_addr_t guts_phys;

/**
 * mpc8610_hpcd_data: machine-specअगरic ASoC device data
 *
 * This काष्ठाure contains data क्रम a single sound platक्रमm device on an
 * MPC8610 HPCD.  Some of the data is taken from the device tree.
 */
काष्ठा mpc8610_hpcd_data अणु
	काष्ठा snd_soc_dai_link dai[2];
	काष्ठा snd_soc_card card;
	अचिन्हित पूर्णांक dai_क्रमmat;
	अचिन्हित पूर्णांक codec_clk_direction;
	अचिन्हित पूर्णांक cpu_clk_direction;
	अचिन्हित पूर्णांक clk_frequency;
	अचिन्हित पूर्णांक ssi_id;		/* 0 = SSI1, 1 = SSI2, etc */
	अचिन्हित पूर्णांक dma_id[2];		/* 0 = DMA1, 1 = DMA2, etc */
	अचिन्हित पूर्णांक dma_channel_id[2]; /* 0 = ch 0, 1 = ch 1, etc*/
	अक्षर codec_dai_name[DAI_NAME_SIZE];
	अक्षर platक्रमm_name[2][DAI_NAME_SIZE]; /* One क्रम each DMA channel */
पूर्ण;

/**
 * mpc8610_hpcd_machine_probe: initialize the board
 *
 * This function is used to initialize the board-specअगरic hardware.
 *
 * Here we program the DMACR and PMUXCR रेजिस्टरs.
 */
अटल पूर्णांक mpc8610_hpcd_machine_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा mpc8610_hpcd_data *machine_data =
		container_of(card, काष्ठा mpc8610_hpcd_data, card);
	काष्ठा ccsr_guts __iomem *guts;

	guts = ioremap(guts_phys, माप(काष्ठा ccsr_guts));
	अगर (!guts) अणु
		dev_err(card->dev, "could not map global utilities\n");
		वापस -ENOMEM;
	पूर्ण

	/* Program the संकेत routing between the SSI and the DMA */
	guts_set_dmacr(guts, machine_data->dma_id[0],
		       machine_data->dma_channel_id[0],
		       CCSR_GUTS_DMACR_DEV_SSI);
	guts_set_dmacr(guts, machine_data->dma_id[1],
		       machine_data->dma_channel_id[1],
		       CCSR_GUTS_DMACR_DEV_SSI);

	guts_set_pmuxcr_dma(guts, machine_data->dma_id[0],
			    machine_data->dma_channel_id[0], 0);
	guts_set_pmuxcr_dma(guts, machine_data->dma_id[1],
			    machine_data->dma_channel_id[1], 0);

	चयन (machine_data->ssi_id) अणु
	हाल 0:
		clrsetbits_be32(&guts->pmuxcr,
			CCSR_GUTS_PMUXCR_SSI1_MASK, CCSR_GUTS_PMUXCR_SSI1_SSI);
		अवरोध;
	हाल 1:
		clrsetbits_be32(&guts->pmuxcr,
			CCSR_GUTS_PMUXCR_SSI2_MASK, CCSR_GUTS_PMUXCR_SSI2_SSI);
		अवरोध;
	पूर्ण

	iounmap(guts);

	वापस 0;
पूर्ण

/**
 * mpc8610_hpcd_startup: program the board with various hardware parameters
 *
 * This function takes board-specअगरic inक्रमmation, like घड़ी frequencies
 * and serial data क्रमmats, and passes that inक्रमmation to the codec and
 * transport drivers.
 */
अटल पूर्णांक mpc8610_hpcd_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा mpc8610_hpcd_data *machine_data =
		container_of(rtd->card, काष्ठा mpc8610_hpcd_data, card);
	काष्ठा device *dev = rtd->card->dev;
	पूर्णांक ret = 0;

	/* Tell the codec driver what the serial protocol is. */
	ret = snd_soc_dai_set_fmt(asoc_rtd_to_codec(rtd, 0), machine_data->dai_क्रमmat);
	अगर (ret < 0) अणु
		dev_err(dev, "could not set codec driver audio format\n");
		वापस ret;
	पूर्ण

	/*
	 * Tell the codec driver what the MCLK frequency is, and whether it's
	 * a slave or master.
	 */
	ret = snd_soc_dai_set_sysclk(asoc_rtd_to_codec(rtd, 0), 0,
				     machine_data->clk_frequency,
				     machine_data->codec_clk_direction);
	अगर (ret < 0) अणु
		dev_err(dev, "could not set codec driver clock params\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mpc8610_hpcd_machine_हटाओ: Remove the sound device
 *
 * This function is called to हटाओ the sound device क्रम one SSI.  We
 * de-program the DMACR and PMUXCR रेजिस्टर.
 */
अटल पूर्णांक mpc8610_hpcd_machine_हटाओ(काष्ठा snd_soc_card *card)
अणु
	काष्ठा mpc8610_hpcd_data *machine_data =
		container_of(card, काष्ठा mpc8610_hpcd_data, card);
	काष्ठा ccsr_guts __iomem *guts;

	guts = ioremap(guts_phys, माप(काष्ठा ccsr_guts));
	अगर (!guts) अणु
		dev_err(card->dev, "could not map global utilities\n");
		वापस -ENOMEM;
	पूर्ण

	/* Restore the संकेत routing */

	guts_set_dmacr(guts, machine_data->dma_id[0],
		       machine_data->dma_channel_id[0], 0);
	guts_set_dmacr(guts, machine_data->dma_id[1],
		       machine_data->dma_channel_id[1], 0);

	चयन (machine_data->ssi_id) अणु
	हाल 0:
		clrsetbits_be32(&guts->pmuxcr,
			CCSR_GUTS_PMUXCR_SSI1_MASK, CCSR_GUTS_PMUXCR_SSI1_LA);
		अवरोध;
	हाल 1:
		clrsetbits_be32(&guts->pmuxcr,
			CCSR_GUTS_PMUXCR_SSI2_MASK, CCSR_GUTS_PMUXCR_SSI2_LA);
		अवरोध;
	पूर्ण

	iounmap(guts);

	वापस 0;
पूर्ण

/**
 * mpc8610_hpcd_ops: ASoC machine driver operations
 */
अटल स्थिर काष्ठा snd_soc_ops mpc8610_hpcd_ops = अणु
	.startup = mpc8610_hpcd_startup,
पूर्ण;

/**
 * mpc8610_hpcd_probe: platक्रमm probe function क्रम the machine driver
 *
 * Although this is a machine driver, the SSI node is the "master" node with
 * respect to audio hardware connections.  Thereक्रमe, we create a new ASoC
 * device क्रम each new SSI node that has a codec attached.
 */
अटल पूर्णांक mpc8610_hpcd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = pdev->dev.parent;
	/* ssi_pdev is the platक्रमm device क्रम the SSI node that probed us */
	काष्ठा platक्रमm_device *ssi_pdev = to_platक्रमm_device(dev);
	काष्ठा device_node *np = ssi_pdev->dev.of_node;
	काष्ठा device_node *codec_np = शून्य;
	काष्ठा mpc8610_hpcd_data *machine_data;
	काष्ठा snd_soc_dai_link_component *comp;
	पूर्णांक ret;
	स्थिर अक्षर *sprop;
	स्थिर u32 *iprop;

	/* Find the codec node क्रम this SSI. */
	codec_np = of_parse_phandle(np, "codec-handle", 0);
	अगर (!codec_np) अणु
		dev_err(dev, "invalid codec node\n");
		वापस -EINVAL;
	पूर्ण

	machine_data = kzalloc(माप(काष्ठा mpc8610_hpcd_data), GFP_KERNEL);
	अगर (!machine_data) अणु
		ret = -ENOMEM;
		जाओ error_alloc;
	पूर्ण

	comp = devm_kzalloc(&pdev->dev, 6 * माप(*comp), GFP_KERNEL);
	अगर (!comp) अणु
		ret = -ENOMEM;
		जाओ error_alloc;
	पूर्ण

	machine_data->dai[0].cpus	= &comp[0];
	machine_data->dai[0].codecs	= &comp[1];
	machine_data->dai[0].platक्रमms	= &comp[2];

	machine_data->dai[0].num_cpus		= 1;
	machine_data->dai[0].num_codecs		= 1;
	machine_data->dai[0].num_platक्रमms	= 1;

	machine_data->dai[1].cpus	= &comp[3];
	machine_data->dai[1].codecs	= &comp[4];
	machine_data->dai[1].platक्रमms	= &comp[5];

	machine_data->dai[1].num_cpus		= 1;
	machine_data->dai[1].num_codecs		= 1;
	machine_data->dai[1].num_platक्रमms	= 1;

	machine_data->dai[0].cpus->dai_name = dev_name(&ssi_pdev->dev);
	machine_data->dai[0].ops = &mpc8610_hpcd_ops;

	/* ASoC core can match codec with device node */
	machine_data->dai[0].codecs->of_node = codec_np;

	/* The DAI name from the codec (snd_soc_dai_driver.name) */
	machine_data->dai[0].codecs->dai_name = "cs4270-hifi";

	/* We रेजिस्टर two DAIs per SSI, one क्रम playback and the other क्रम
	 * capture.  Currently, we only support codecs that have one DAI क्रम
	 * both playback and capture.
	 */
	स_नकल(&machine_data->dai[1], &machine_data->dai[0],
	       माप(काष्ठा snd_soc_dai_link));

	/* Get the device ID */
	iprop = of_get_property(np, "cell-index", शून्य);
	अगर (!iprop) अणु
		dev_err(&pdev->dev, "cell-index property not found\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण
	machine_data->ssi_id = be32_to_cpup(iprop);

	/* Get the serial क्रमmat and घड़ी direction. */
	sprop = of_get_property(np, "fsl,mode", शून्य);
	अगर (!sprop) अणु
		dev_err(&pdev->dev, "fsl,mode property not found\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (strहालcmp(sprop, "i2s-slave") == 0) अणु
		machine_data->dai_क्रमmat =
			SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBM_CFM;
		machine_data->codec_clk_direction = SND_SOC_CLOCK_OUT;
		machine_data->cpu_clk_direction = SND_SOC_CLOCK_IN;

		/* In i2s-slave mode, the codec has its own घड़ी source, so we
		 * need to get the frequency from the device tree and pass it to
		 * the codec driver.
		 */
		iprop = of_get_property(codec_np, "clock-frequency", शून्य);
		अगर (!iprop || !*iprop) अणु
			dev_err(&pdev->dev, "codec bus-frequency "
				"property is missing or invalid\n");
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		machine_data->clk_frequency = be32_to_cpup(iprop);
	पूर्ण अन्यथा अगर (strहालcmp(sprop, "i2s-master") == 0) अणु
		machine_data->dai_क्रमmat =
			SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS;
		machine_data->codec_clk_direction = SND_SOC_CLOCK_IN;
		machine_data->cpu_clk_direction = SND_SOC_CLOCK_OUT;
	पूर्ण अन्यथा अगर (strहालcmp(sprop, "lj-slave") == 0) अणु
		machine_data->dai_क्रमmat =
			SND_SOC_DAIFMT_LEFT_J | SND_SOC_DAIFMT_CBM_CFM;
		machine_data->codec_clk_direction = SND_SOC_CLOCK_OUT;
		machine_data->cpu_clk_direction = SND_SOC_CLOCK_IN;
	पूर्ण अन्यथा अगर (strहालcmp(sprop, "lj-master") == 0) अणु
		machine_data->dai_क्रमmat =
			SND_SOC_DAIFMT_LEFT_J | SND_SOC_DAIFMT_CBS_CFS;
		machine_data->codec_clk_direction = SND_SOC_CLOCK_IN;
		machine_data->cpu_clk_direction = SND_SOC_CLOCK_OUT;
	पूर्ण अन्यथा अगर (strहालcmp(sprop, "rj-slave") == 0) अणु
		machine_data->dai_क्रमmat =
			SND_SOC_DAIFMT_RIGHT_J | SND_SOC_DAIFMT_CBM_CFM;
		machine_data->codec_clk_direction = SND_SOC_CLOCK_OUT;
		machine_data->cpu_clk_direction = SND_SOC_CLOCK_IN;
	पूर्ण अन्यथा अगर (strहालcmp(sprop, "rj-master") == 0) अणु
		machine_data->dai_क्रमmat =
			SND_SOC_DAIFMT_RIGHT_J | SND_SOC_DAIFMT_CBS_CFS;
		machine_data->codec_clk_direction = SND_SOC_CLOCK_IN;
		machine_data->cpu_clk_direction = SND_SOC_CLOCK_OUT;
	पूर्ण अन्यथा अगर (strहालcmp(sprop, "ac97-slave") == 0) अणु
		machine_data->dai_क्रमmat =
			SND_SOC_DAIFMT_AC97 | SND_SOC_DAIFMT_CBM_CFM;
		machine_data->codec_clk_direction = SND_SOC_CLOCK_OUT;
		machine_data->cpu_clk_direction = SND_SOC_CLOCK_IN;
	पूर्ण अन्यथा अगर (strहालcmp(sprop, "ac97-master") == 0) अणु
		machine_data->dai_क्रमmat =
			SND_SOC_DAIFMT_AC97 | SND_SOC_DAIFMT_CBS_CFS;
		machine_data->codec_clk_direction = SND_SOC_CLOCK_IN;
		machine_data->cpu_clk_direction = SND_SOC_CLOCK_OUT;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev,
			"unrecognized fsl,mode property '%s'\n", sprop);
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (!machine_data->clk_frequency) अणु
		dev_err(&pdev->dev, "unknown clock frequency\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/* Find the playback DMA channel to use. */
	machine_data->dai[0].platक्रमms->name = machine_data->platक्रमm_name[0];
	ret = fsl_asoc_get_dma_channel(np, "fsl,playback-dma",
				       &machine_data->dai[0],
				       &machine_data->dma_channel_id[0],
				       &machine_data->dma_id[0]);
	अगर (ret) अणु
		dev_err(&pdev->dev, "missing/invalid playback DMA phandle\n");
		जाओ error;
	पूर्ण

	/* Find the capture DMA channel to use. */
	machine_data->dai[1].platक्रमms->name = machine_data->platक्रमm_name[1];
	ret = fsl_asoc_get_dma_channel(np, "fsl,capture-dma",
				       &machine_data->dai[1],
				       &machine_data->dma_channel_id[1],
				       &machine_data->dma_id[1]);
	अगर (ret) अणु
		dev_err(&pdev->dev, "missing/invalid capture DMA phandle\n");
		जाओ error;
	पूर्ण

	/* Initialize our DAI data काष्ठाure.  */
	machine_data->dai[0].stream_name = "playback";
	machine_data->dai[1].stream_name = "capture";
	machine_data->dai[0].name = machine_data->dai[0].stream_name;
	machine_data->dai[1].name = machine_data->dai[1].stream_name;

	machine_data->card.probe = mpc8610_hpcd_machine_probe;
	machine_data->card.हटाओ = mpc8610_hpcd_machine_हटाओ;
	machine_data->card.name = pdev->name; /* The platक्रमm driver name */
	machine_data->card.owner = THIS_MODULE;
	machine_data->card.dev = &pdev->dev;
	machine_data->card.num_links = 2;
	machine_data->card.dai_link = machine_data->dai;

	/* Register with ASoC */
	ret = snd_soc_रेजिस्टर_card(&machine_data->card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not register card\n");
		जाओ error;
	पूर्ण

	of_node_put(codec_np);

	वापस 0;

error:
	kमुक्त(machine_data);
error_alloc:
	of_node_put(codec_np);
	वापस ret;
पूर्ण

/**
 * mpc8610_hpcd_हटाओ: हटाओ the platक्रमm device
 *
 * This function is called when the platक्रमm device is हटाओd.
 */
अटल पूर्णांक mpc8610_hpcd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);
	काष्ठा mpc8610_hpcd_data *machine_data =
		container_of(card, काष्ठा mpc8610_hpcd_data, card);

	snd_soc_unरेजिस्टर_card(card);
	kमुक्त(machine_data);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mpc8610_hpcd_driver = अणु
	.probe = mpc8610_hpcd_probe,
	.हटाओ = mpc8610_hpcd_हटाओ,
	.driver = अणु
		/* The name must match 'compatible' property in the device tree,
		 * in lowerहाल letters.
		 */
		.name = "snd-soc-mpc8610hpcd",
	पूर्ण,
पूर्ण;

/**
 * mpc8610_hpcd_init: machine driver initialization.
 *
 * This function is called when this module is loaded.
 */
अटल पूर्णांक __init mpc8610_hpcd_init(व्योम)
अणु
	काष्ठा device_node *guts_np;
	काष्ठा resource res;

	pr_info("Freescale MPC8610 HPCD ALSA SoC machine driver\n");

	/* Get the physical address of the global utilities रेजिस्टरs */
	guts_np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc8610-guts");
	अगर (of_address_to_resource(guts_np, 0, &res)) अणु
		pr_err("mpc8610-hpcd: missing/invalid global utilities node\n");
		of_node_put(guts_np);
		वापस -EINVAL;
	पूर्ण
	guts_phys = res.start;
	of_node_put(guts_np);

	वापस platक्रमm_driver_रेजिस्टर(&mpc8610_hpcd_driver);
पूर्ण

/**
 * mpc8610_hpcd_निकास: machine driver निकास
 *
 * This function is called when this driver is unloaded.
 */
अटल व्योम __निकास mpc8610_hpcd_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mpc8610_hpcd_driver);
पूर्ण

module_init(mpc8610_hpcd_init);
module_निकास(mpc8610_hpcd_निकास);

MODULE_AUTHOR("Timur Tabi <timur@freescale.com>");
MODULE_DESCRIPTION("Freescale MPC8610 HPCD ALSA SoC machine driver");
MODULE_LICENSE("GPL v2");
