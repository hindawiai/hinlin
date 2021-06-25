<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Media driver क्रम Freescale i.MX5/6 SOC
 *
 * Open Firmware parsing.
 *
 * Copyright (c) 2016 Mentor Graphics Inc.
 */
#समावेश <linux/of_platक्रमm.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <linux/of_graph.h>
#समावेश <video/imx-ipu-v3.h>
#समावेश "imx-media.h"

पूर्णांक imx_media_of_add_csi(काष्ठा imx_media_dev *imxmd,
			 काष्ठा device_node *csi_np)
अणु
	काष्ठा v4l2_async_subdev *asd;
	पूर्णांक ret = 0;

	अगर (!of_device_is_available(csi_np)) अणु
		dev_dbg(imxmd->md.dev, "%s: %pOFn not enabled\n", __func__,
			csi_np);
		वापस -ENODEV;
	पूर्ण

	/* add CSI fwnode to async notअगरier */
	asd = v4l2_async_notअगरier_add_fwnode_subdev(&imxmd->notअगरier,
						    of_fwnode_handle(csi_np),
						    काष्ठा v4l2_async_subdev);
	अगर (IS_ERR(asd)) अणु
		ret = PTR_ERR(asd);
		अगर (ret == -EEXIST)
			dev_dbg(imxmd->md.dev, "%s: already added %pOFn\n",
				__func__, csi_np);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_of_add_csi);

पूर्णांक imx_media_add_of_subdevs(काष्ठा imx_media_dev *imxmd,
			     काष्ठा device_node *np)
अणु
	काष्ठा device_node *csi_np;
	पूर्णांक i, ret;

	क्रम (i = 0; ; i++) अणु
		csi_np = of_parse_phandle(np, "ports", i);
		अगर (!csi_np)
			अवरोध;

		ret = imx_media_of_add_csi(imxmd, csi_np);
		अगर (ret) अणु
			/* unavailable or alपढ़ोy added is not an error */
			अगर (ret == -ENODEV || ret == -EEXIST) अणु
				of_node_put(csi_np);
				जारी;
			पूर्ण

			/* other error, can't जारी */
			जाओ err_out;
		पूर्ण
	पूर्ण

	वापस 0;

err_out:
	of_node_put(csi_np);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(imx_media_add_of_subdevs);
