<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Freescale ALSA SoC Machine driver utility
//
// Author: Timur Tabi <timur@मुक्तscale.com>
//
// Copyright 2010 Freescale Semiconductor, Inc.

#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <sound/soc.h>

#समावेश "fsl_utils.h"

/**
 * fsl_asoc_get_dma_channel - determine the dma channel क्रम a SSI node
 *
 * @ssi_np: poपूर्णांकer to the SSI device tree node
 * @name: name of the phandle poपूर्णांकing to the dma channel
 * @dai: ASoC DAI link poपूर्णांकer to be filled with platक्रमm_name
 * @dma_channel_id: dma channel id to be वापसed
 * @dma_id: dma id to be वापसed
 *
 * This function determines the dma and channel id क्रम given SSI node.  It
 * also discovers the platक्रमm_name क्रम the ASoC DAI link.
 */
पूर्णांक fsl_asoc_get_dma_channel(काष्ठा device_node *ssi_np,
			     स्थिर अक्षर *name,
			     काष्ठा snd_soc_dai_link *dai,
			     अचिन्हित पूर्णांक *dma_channel_id,
			     अचिन्हित पूर्णांक *dma_id)
अणु
	काष्ठा resource res;
	काष्ठा device_node *dma_channel_np, *dma_np;
	स्थिर __be32 *iprop;
	पूर्णांक ret;

	dma_channel_np = of_parse_phandle(ssi_np, name, 0);
	अगर (!dma_channel_np)
		वापस -EINVAL;

	अगर (!of_device_is_compatible(dma_channel_np, "fsl,ssi-dma-channel")) अणु
		of_node_put(dma_channel_np);
		वापस -EINVAL;
	पूर्ण

	/* Determine the dev_name क्रम the device_node.  This code mimics the
	 * behavior of of_device_make_bus_id(). We need this because ASoC uses
	 * the dev_name() of the device to match the platक्रमm (DMA) device with
	 * the CPU (SSI) device.  It's all ugly and hackish, but it works (क्रम
	 * now).
	 *
	 * dai->platक्रमm name should alपढ़ोy poपूर्णांक to an allocated buffer.
	 */
	ret = of_address_to_resource(dma_channel_np, 0, &res);
	अगर (ret) अणु
		of_node_put(dma_channel_np);
		वापस ret;
	पूर्ण
	snम_लिखो((अक्षर *)dai->platक्रमms->name, DAI_NAME_SIZE, "%llx.%pOFn",
		 (अचिन्हित दीर्घ दीर्घ) res.start, dma_channel_np);

	iprop = of_get_property(dma_channel_np, "cell-index", शून्य);
	अगर (!iprop) अणु
		of_node_put(dma_channel_np);
		वापस -EINVAL;
	पूर्ण
	*dma_channel_id = be32_to_cpup(iprop);

	dma_np = of_get_parent(dma_channel_np);
	iprop = of_get_property(dma_np, "cell-index", शून्य);
	अगर (!iprop) अणु
		of_node_put(dma_np);
		of_node_put(dma_channel_np);
		वापस -EINVAL;
	पूर्ण
	*dma_id = be32_to_cpup(iprop);

	of_node_put(dma_np);
	of_node_put(dma_channel_np);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fsl_asoc_get_dma_channel);

MODULE_AUTHOR("Timur Tabi <timur@freescale.com>");
MODULE_DESCRIPTION("Freescale ASoC utility code");
MODULE_LICENSE("GPL v2");
