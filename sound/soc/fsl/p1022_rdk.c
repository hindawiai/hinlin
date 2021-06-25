<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Freescale P1022RDK ALSA SoC Machine driver
//
// Author: Timur Tabi <timur@मुक्तscale.com>
//
// Copyright 2012 Freescale Semiconductor, Inc.
//
// Note: in order क्रम audio to work correctly, the output controls need
// to be enabled, because they control the घड़ी.  So क्रम playback, क्रम
// example:
//
//      amixer sset 'Left Output Mixer PCM' on
//      amixer sset 'Right Output Mixer PCM' on

#समावेश <linux/module.h>
#समावेश <linux/fsl/guts.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <sound/soc.h>

#समावेश "fsl_dma.h"
#समावेश "fsl_ssi.h"
#समावेश "fsl_utils.h"

/* P1022-specअगरic PMUXCR and DMUXCR bit definitions */

#घोषणा CCSR_GUTS_PMUXCR_UART0_I2C1_MASK	0x0001c000
#घोषणा CCSR_GUTS_PMUXCR_UART0_I2C1_UART0_SSI	0x00010000
#घोषणा CCSR_GUTS_PMUXCR_UART0_I2C1_SSI		0x00018000

#घोषणा CCSR_GUTS_PMUXCR_SSI_DMA_TDM_MASK	0x00000c00
#घोषणा CCSR_GUTS_PMUXCR_SSI_DMA_TDM_SSI	0x00000000

#घोषणा CCSR_GUTS_DMUXCR_PAD	1	/* DMA controller/channel set to pad */
#घोषणा CCSR_GUTS_DMUXCR_SSI	2	/* DMA controller/channel set to SSI */

/*
 * Set the DMACR रेजिस्टर in the GUTS
 *
 * The DMACR रेजिस्टर determines the source of initiated transfers क्रम each
 * channel on each DMA controller.  Rather than have a bunch of repetitive
 * macros क्रम the bit patterns, we just have a function that calculates
 * them.
 *
 * guts: Poपूर्णांकer to GUTS काष्ठाure
 * co: The DMA controller (0 or 1)
 * ch: The channel on the DMA controller (0, 1, 2, or 3)
 * device: The device to set as the target (CCSR_GUTS_DMUXCR_xxx)
 */
अटल अंतरभूत व्योम guts_set_dmuxcr(काष्ठा ccsr_guts __iomem *guts,
	अचिन्हित पूर्णांक co, अचिन्हित पूर्णांक ch, अचिन्हित पूर्णांक device)
अणु
	अचिन्हित पूर्णांक shअगरt = 16 + (8 * (1 - co) + 2 * (3 - ch));

	clrsetbits_be32(&guts->dmuxcr, 3 << shअगरt, device << shअगरt);
पूर्ण

/* There's only one global utilities रेजिस्टर */
अटल phys_addr_t guts_phys;

/**
 * machine_data: machine-specअगरic ASoC device data
 *
 * This काष्ठाure contains data क्रम a single sound platक्रमm device on an
 * P1022 RDK.  Some of the data is taken from the device tree.
 */
काष्ठा machine_data अणु
	काष्ठा snd_soc_dai_link dai[2];
	काष्ठा snd_soc_card card;
	अचिन्हित पूर्णांक dai_क्रमmat;
	अचिन्हित पूर्णांक codec_clk_direction;
	अचिन्हित पूर्णांक cpu_clk_direction;
	अचिन्हित पूर्णांक clk_frequency;
	अचिन्हित पूर्णांक dma_id[2];		/* 0 = DMA1, 1 = DMA2, etc */
	अचिन्हित पूर्णांक dma_channel_id[2]; /* 0 = ch 0, 1 = ch 1, etc*/
	अक्षर platक्रमm_name[2][DAI_NAME_SIZE]; /* One क्रम each DMA channel */
पूर्ण;

/**
 * p1022_rdk_machine_probe: initialize the board
 *
 * This function is used to initialize the board-specअगरic hardware.
 *
 * Here we program the DMACR and PMUXCR रेजिस्टरs.
 */
अटल पूर्णांक p1022_rdk_machine_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा machine_data *mdata =
		container_of(card, काष्ठा machine_data, card);
	काष्ठा ccsr_guts __iomem *guts;

	guts = ioremap(guts_phys, माप(काष्ठा ccsr_guts));
	अगर (!guts) अणु
		dev_err(card->dev, "could not map global utilities\n");
		वापस -ENOMEM;
	पूर्ण

	/* Enable SSI Tx संकेत */
	clrsetbits_be32(&guts->pmuxcr, CCSR_GUTS_PMUXCR_UART0_I2C1_MASK,
			CCSR_GUTS_PMUXCR_UART0_I2C1_UART0_SSI);

	/* Enable SSI Rx संकेत */
	clrsetbits_be32(&guts->pmuxcr, CCSR_GUTS_PMUXCR_SSI_DMA_TDM_MASK,
			CCSR_GUTS_PMUXCR_SSI_DMA_TDM_SSI);

	/* Enable DMA Channel क्रम SSI */
	guts_set_dmuxcr(guts, mdata->dma_id[0], mdata->dma_channel_id[0],
			CCSR_GUTS_DMUXCR_SSI);

	guts_set_dmuxcr(guts, mdata->dma_id[1], mdata->dma_channel_id[1],
			CCSR_GUTS_DMUXCR_SSI);

	iounmap(guts);

	वापस 0;
पूर्ण

/**
 * p1022_rdk_startup: program the board with various hardware parameters
 *
 * This function takes board-specअगरic inक्रमmation, like घड़ी frequencies
 * and serial data क्रमmats, and passes that inक्रमmation to the codec and
 * transport drivers.
 */
अटल पूर्णांक p1022_rdk_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा machine_data *mdata =
		container_of(rtd->card, काष्ठा machine_data, card);
	काष्ठा device *dev = rtd->card->dev;
	पूर्णांक ret = 0;

	/* Tell the codec driver what the serial protocol is. */
	ret = snd_soc_dai_set_fmt(asoc_rtd_to_codec(rtd, 0), mdata->dai_क्रमmat);
	अगर (ret < 0) अणु
		dev_err(dev, "could not set codec driver audio format (ret=%i)\n",
			ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_pll(asoc_rtd_to_codec(rtd, 0), 0, 0, mdata->clk_frequency,
		mdata->clk_frequency);
	अगर (ret < 0) अणु
		dev_err(dev, "could not set codec PLL frequency (ret=%i)\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * p1022_rdk_machine_हटाओ: Remove the sound device
 *
 * This function is called to हटाओ the sound device क्रम one SSI.  We
 * de-program the DMACR and PMUXCR रेजिस्टर.
 */
अटल पूर्णांक p1022_rdk_machine_हटाओ(काष्ठा snd_soc_card *card)
अणु
	काष्ठा machine_data *mdata =
		container_of(card, काष्ठा machine_data, card);
	काष्ठा ccsr_guts __iomem *guts;

	guts = ioremap(guts_phys, माप(काष्ठा ccsr_guts));
	अगर (!guts) अणु
		dev_err(card->dev, "could not map global utilities\n");
		वापस -ENOMEM;
	पूर्ण

	/* Restore the संकेत routing */
	clrbits32(&guts->pmuxcr, CCSR_GUTS_PMUXCR_UART0_I2C1_MASK);
	clrbits32(&guts->pmuxcr, CCSR_GUTS_PMUXCR_SSI_DMA_TDM_MASK);
	guts_set_dmuxcr(guts, mdata->dma_id[0], mdata->dma_channel_id[0], 0);
	guts_set_dmuxcr(guts, mdata->dma_id[1], mdata->dma_channel_id[1], 0);

	iounmap(guts);

	वापस 0;
पूर्ण

/**
 * p1022_rdk_ops: ASoC machine driver operations
 */
अटल स्थिर काष्ठा snd_soc_ops p1022_rdk_ops = अणु
	.startup = p1022_rdk_startup,
पूर्ण;

/**
 * p1022_rdk_probe: platक्रमm probe function क्रम the machine driver
 *
 * Although this is a machine driver, the SSI node is the "master" node with
 * respect to audio hardware connections.  Thereक्रमe, we create a new ASoC
 * device क्रम each new SSI node that has a codec attached.
 */
अटल पूर्णांक p1022_rdk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = pdev->dev.parent;
	/* ssi_pdev is the platक्रमm device क्रम the SSI node that probed us */
	काष्ठा platक्रमm_device *ssi_pdev = to_platक्रमm_device(dev);
	काष्ठा device_node *np = ssi_pdev->dev.of_node;
	काष्ठा device_node *codec_np = शून्य;
	काष्ठा machine_data *mdata;
	काष्ठा snd_soc_dai_link_component *comp;
	स्थिर u32 *iprop;
	पूर्णांक ret;

	/* Find the codec node क्रम this SSI. */
	codec_np = of_parse_phandle(np, "codec-handle", 0);
	अगर (!codec_np) अणु
		dev_err(dev, "could not find codec node\n");
		वापस -EINVAL;
	पूर्ण

	mdata = kzalloc(माप(काष्ठा machine_data), GFP_KERNEL);
	अगर (!mdata) अणु
		ret = -ENOMEM;
		जाओ error_put;
	पूर्ण

	comp = devm_kzalloc(&pdev->dev, 6 * माप(*comp), GFP_KERNEL);
	अगर (!comp) अणु
		ret = -ENOMEM;
		जाओ error_put;
	पूर्ण

	mdata->dai[0].cpus	= &comp[0];
	mdata->dai[0].codecs	= &comp[1];
	mdata->dai[0].platक्रमms	= &comp[2];

	mdata->dai[0].num_cpus		= 1;
	mdata->dai[0].num_codecs	= 1;
	mdata->dai[0].num_platक्रमms	= 1;

	mdata->dai[1].cpus	= &comp[3];
	mdata->dai[1].codecs	= &comp[4];
	mdata->dai[1].platक्रमms	= &comp[5];

	mdata->dai[1].num_cpus		= 1;
	mdata->dai[1].num_codecs	= 1;
	mdata->dai[1].num_platक्रमms	= 1;

	mdata->dai[0].cpus->dai_name = dev_name(&ssi_pdev->dev);
	mdata->dai[0].ops = &p1022_rdk_ops;

	/* ASoC core can match codec with device node */
	mdata->dai[0].codecs->of_node = codec_np;

	/*
	 * We रेजिस्टर two DAIs per SSI, one क्रम playback and the other क्रम
	 * capture.  We support codecs that have separate DAIs क्रम both playback
	 * and capture.
	 */
	स_नकल(&mdata->dai[1], &mdata->dai[0], माप(काष्ठा snd_soc_dai_link));

	/* The DAI names from the codec (snd_soc_dai_driver.name) */
	mdata->dai[0].codecs->dai_name = "wm8960-hifi";
	mdata->dai[1].codecs->dai_name = mdata->dai[0].codecs->dai_name;

	/*
	 * Configure the SSI क्रम I2S slave mode.  Older device trees have
	 * an fsl,mode property, but we ignore that since there's really
	 * only one way to configure the SSI.
	 */
	mdata->dai_क्रमmat = SND_SOC_DAIFMT_NB_NF |
		SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBM_CFM;
	mdata->codec_clk_direction = SND_SOC_CLOCK_OUT;
	mdata->cpu_clk_direction = SND_SOC_CLOCK_IN;

	/*
	 * In i2s-slave mode, the codec has its own घड़ी source, so we
	 * need to get the frequency from the device tree and pass it to
	 * the codec driver.
	 */
	iprop = of_get_property(codec_np, "clock-frequency", शून्य);
	अगर (!iprop || !*iprop) अणु
		dev_err(&pdev->dev, "codec bus-frequency property is missing or invalid\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण
	mdata->clk_frequency = be32_to_cpup(iprop);

	अगर (!mdata->clk_frequency) अणु
		dev_err(&pdev->dev, "unknown clock frequency\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/* Find the playback DMA channel to use. */
	mdata->dai[0].platक्रमms->name = mdata->platक्रमm_name[0];
	ret = fsl_asoc_get_dma_channel(np, "fsl,playback-dma", &mdata->dai[0],
				       &mdata->dma_channel_id[0],
				       &mdata->dma_id[0]);
	अगर (ret) अणु
		dev_err(&pdev->dev, "missing/invalid playback DMA phandle (ret=%i)\n",
			ret);
		जाओ error;
	पूर्ण

	/* Find the capture DMA channel to use. */
	mdata->dai[1].platक्रमms->name = mdata->platक्रमm_name[1];
	ret = fsl_asoc_get_dma_channel(np, "fsl,capture-dma", &mdata->dai[1],
				       &mdata->dma_channel_id[1],
				       &mdata->dma_id[1]);
	अगर (ret) अणु
		dev_err(&pdev->dev, "missing/invalid capture DMA phandle (ret=%i)\n",
			ret);
		जाओ error;
	पूर्ण

	/* Initialize our DAI data काष्ठाure.  */
	mdata->dai[0].stream_name = "playback";
	mdata->dai[1].stream_name = "capture";
	mdata->dai[0].name = mdata->dai[0].stream_name;
	mdata->dai[1].name = mdata->dai[1].stream_name;

	mdata->card.probe = p1022_rdk_machine_probe;
	mdata->card.हटाओ = p1022_rdk_machine_हटाओ;
	mdata->card.name = pdev->name; /* The platक्रमm driver name */
	mdata->card.owner = THIS_MODULE;
	mdata->card.dev = &pdev->dev;
	mdata->card.num_links = 2;
	mdata->card.dai_link = mdata->dai;

	/* Register with ASoC */
	ret = snd_soc_रेजिस्टर_card(&mdata->card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not register card (ret=%i)\n", ret);
		जाओ error;
	पूर्ण

	वापस 0;

error:
	kमुक्त(mdata);
error_put:
	of_node_put(codec_np);
	वापस ret;
पूर्ण

/**
 * p1022_rdk_हटाओ: हटाओ the platक्रमm device
 *
 * This function is called when the platक्रमm device is हटाओd.
 */
अटल पूर्णांक p1022_rdk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);
	काष्ठा machine_data *mdata =
		container_of(card, काष्ठा machine_data, card);

	snd_soc_unरेजिस्टर_card(card);
	kमुक्त(mdata);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver p1022_rdk_driver = अणु
	.probe = p1022_rdk_probe,
	.हटाओ = p1022_rdk_हटाओ,
	.driver = अणु
		/*
		 * The name must match 'compatible' property in the device tree,
		 * in lowerहाल letters.
		 */
		.name = "snd-soc-p1022rdk",
	पूर्ण,
पूर्ण;

/**
 * p1022_rdk_init: machine driver initialization.
 *
 * This function is called when this module is loaded.
 */
अटल पूर्णांक __init p1022_rdk_init(व्योम)
अणु
	काष्ठा device_node *guts_np;
	काष्ठा resource res;

	/* Get the physical address of the global utilities रेजिस्टरs */
	guts_np = of_find_compatible_node(शून्य, शून्य, "fsl,p1022-guts");
	अगर (of_address_to_resource(guts_np, 0, &res)) अणु
		pr_err("snd-soc-p1022rdk: missing/invalid global utils node\n");
		of_node_put(guts_np);
		वापस -EINVAL;
	पूर्ण
	guts_phys = res.start;
	of_node_put(guts_np);

	वापस platक्रमm_driver_रेजिस्टर(&p1022_rdk_driver);
पूर्ण

/**
 * p1022_rdk_निकास: machine driver निकास
 *
 * This function is called when this driver is unloaded.
 */
अटल व्योम __निकास p1022_rdk_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&p1022_rdk_driver);
पूर्ण

late_initcall(p1022_rdk_init);
module_निकास(p1022_rdk_निकास);

MODULE_AUTHOR("Timur Tabi <timur@freescale.com>");
MODULE_DESCRIPTION("Freescale / iVeia P1022 RDK ALSA SoC machine driver");
MODULE_LICENSE("GPL v2");
