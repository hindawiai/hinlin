<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// eukrea-tlv320.c  --  SoC audio क्रम eukrea_cpuimxXX in I2S mode
//
// Copyright 2010 Eric Bथऊnard, Eukrथऊa Electromatique <eric@eukrea.com>
//
// based on sound/soc/s3c24xx/s3c24xx_simtec_tlv320aic23.c
// which is Copyright 2009 Simtec Electronics
// and on sound/soc/imx/phycore-ac97.c which is
// Copyright 2009 Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "../codecs/tlv320aic23.h"
#समावेश "imx-ssi.h"
#समावेश "imx-audmux.h"

#घोषणा CODEC_CLOCK 12000000

अटल पूर्णांक eukrea_tlv320_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(codec_dai, 0,
				     CODEC_CLOCK, SND_SOC_CLOCK_OUT);
	अगर (ret) अणु
		dev_err(cpu_dai->dev,
			"Failed to set the codec sysclk.\n");
		वापस ret;
	पूर्ण

	snd_soc_dai_set_tdm_slot(cpu_dai, 0x3, 0x3, 2, 0);

	ret = snd_soc_dai_set_sysclk(cpu_dai, IMX_SSP_SYS_CLK, 0,
				SND_SOC_CLOCK_IN);
	/* fsl_ssi lacks the set_sysclk ops */
	अगर (ret && ret != -EINVAL) अणु
		dev_err(cpu_dai->dev,
			"Can't set the IMX_SSP_SYS_CLK CPU system clock.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops eukrea_tlv320_snd_ops = अणु
	.hw_params	= eukrea_tlv320_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEFS(hअगरi,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "tlv320aic23-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link eukrea_tlv320_dai = अणु
	.name		= "tlv320aic23",
	.stream_name	= "TLV320AIC23",
	.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			  SND_SOC_DAIFMT_CBM_CFM,
	.ops		= &eukrea_tlv320_snd_ops,
	SND_SOC_DAILINK_REG(hअगरi),
पूर्ण;

अटल काष्ठा snd_soc_card eukrea_tlv320 = अणु
	.owner		= THIS_MODULE,
	.dai_link	= &eukrea_tlv320_dai,
	.num_links	= 1,
पूर्ण;

अटल पूर्णांक eukrea_tlv320_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	पूर्णांक पूर्णांक_port = 0, ext_port;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *ssi_np = शून्य, *codec_np = शून्य;

	eukrea_tlv320.dev = &pdev->dev;
	अगर (np) अणु
		ret = snd_soc_of_parse_card_name(&eukrea_tlv320,
						 "eukrea,model");
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"eukrea,model node missing or invalid.\n");
			जाओ err;
		पूर्ण

		ssi_np = of_parse_phandle(pdev->dev.of_node,
					  "ssi-controller", 0);
		अगर (!ssi_np) अणु
			dev_err(&pdev->dev,
				"ssi-controller missing or invalid.\n");
			ret = -ENODEV;
			जाओ err;
		पूर्ण

		codec_np = of_parse_phandle(ssi_np, "codec-handle", 0);
		अगर (codec_np)
			eukrea_tlv320_dai.codecs->of_node = codec_np;
		अन्यथा
			dev_err(&pdev->dev, "codec-handle node missing or invalid.\n");

		ret = of_property_पढ़ो_u32(np, "fsl,mux-int-port", &पूर्णांक_port);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"fsl,mux-int-port node missing or invalid.\n");
			जाओ err;
		पूर्ण
		ret = of_property_पढ़ो_u32(np, "fsl,mux-ext-port", &ext_port);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"fsl,mux-ext-port node missing or invalid.\n");
			जाओ err;
		पूर्ण

		/*
		 * The port numbering in the hardware manual starts at 1, जबतक
		 * the audmux API expects it starts at 0.
		 */
		पूर्णांक_port--;
		ext_port--;

		eukrea_tlv320_dai.cpus->of_node = ssi_np;
		eukrea_tlv320_dai.platक्रमms->of_node = ssi_np;
	पूर्ण अन्यथा अणु
		eukrea_tlv320_dai.cpus->dai_name = "imx-ssi.0";
		eukrea_tlv320_dai.platक्रमms->name = "imx-ssi.0";
		eukrea_tlv320_dai.codecs->name = "tlv320aic23-codec.0-001a";
		eukrea_tlv320.name = "cpuimx-audio";
	पूर्ण

	अगर (machine_is_eukrea_cpuimx27() ||
	    of_find_compatible_node(शून्य, शून्य, "fsl,imx21-audmux")) अणु
		imx_audmux_v1_configure_port(MX27_AUDMUX_HPCR1_SSI0,
			IMX_AUDMUX_V1_PCR_SYN |
			IMX_AUDMUX_V1_PCR_TFSसूची |
			IMX_AUDMUX_V1_PCR_TCLKसूची |
			IMX_AUDMUX_V1_PCR_RFSसूची |
			IMX_AUDMUX_V1_PCR_RCLKसूची |
			IMX_AUDMUX_V1_PCR_TFCSEL(MX27_AUDMUX_HPCR3_SSI_PINS_4) |
			IMX_AUDMUX_V1_PCR_RFCSEL(MX27_AUDMUX_HPCR3_SSI_PINS_4) |
			IMX_AUDMUX_V1_PCR_RXDSEL(MX27_AUDMUX_HPCR3_SSI_PINS_4)
		);
		imx_audmux_v1_configure_port(MX27_AUDMUX_HPCR3_SSI_PINS_4,
			IMX_AUDMUX_V1_PCR_SYN |
			IMX_AUDMUX_V1_PCR_RXDSEL(MX27_AUDMUX_HPCR1_SSI0)
		);
	पूर्ण अन्यथा अगर (machine_is_eukrea_cpuimx25sd() ||
		   machine_is_eukrea_cpuimx35sd() ||
		   machine_is_eukrea_cpuimx51sd() ||
		   of_find_compatible_node(शून्य, शून्य, "fsl,imx31-audmux")) अणु
		अगर (!np)
			ext_port = machine_is_eukrea_cpuimx25sd() ?
				4 : 3;

		imx_audmux_v2_configure_port(पूर्णांक_port,
			IMX_AUDMUX_V2_PTCR_SYN |
			IMX_AUDMUX_V2_PTCR_TFSसूची |
			IMX_AUDMUX_V2_PTCR_TFSEL(ext_port) |
			IMX_AUDMUX_V2_PTCR_TCLKसूची |
			IMX_AUDMUX_V2_PTCR_TCSEL(ext_port),
			IMX_AUDMUX_V2_PDCR_RXDSEL(ext_port)
		);
		imx_audmux_v2_configure_port(ext_port,
			IMX_AUDMUX_V2_PTCR_SYN,
			IMX_AUDMUX_V2_PDCR_RXDSEL(पूर्णांक_port)
		);
	पूर्ण अन्यथा अणु
		अगर (np) अणु
			/* The eukrea,asoc-tlv320 driver was explicitly
			 * requested (through the device tree).
			 */
			dev_err(&pdev->dev,
				"Missing or invalid audmux DT node.\n");
			वापस -ENODEV;
		पूर्ण अन्यथा अणु
			/* Return happy.
			 * We might run on a totally dअगरferent machine.
			 */
			वापस 0;
		पूर्ण
	पूर्ण

	ret = snd_soc_रेजिस्टर_card(&eukrea_tlv320);
err:
	अगर (ret)
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n", ret);
	of_node_put(ssi_np);

	वापस ret;
पूर्ण

अटल पूर्णांक eukrea_tlv320_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	snd_soc_unरेजिस्टर_card(&eukrea_tlv320);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_tlv320_dt_ids[] = अणु
	अणु .compatible = "eukrea,asoc-tlv320"पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_tlv320_dt_ids);

अटल काष्ठा platक्रमm_driver eukrea_tlv320_driver = अणु
	.driver = अणु
		.name = "eukrea_tlv320",
		.of_match_table = imx_tlv320_dt_ids,
	पूर्ण,
	.probe = eukrea_tlv320_probe,
	.हटाओ = eukrea_tlv320_हटाओ,
पूर्ण;

module_platक्रमm_driver(eukrea_tlv320_driver);

MODULE_AUTHOR("Eric Bथऊnard <eric@eukrea.com>");
MODULE_DESCRIPTION("CPUIMX ALSA SoC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:eukrea_tlv320");
