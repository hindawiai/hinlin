<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * vimc-core.c Virtual Media Controller Driver
 *
 * Copyright (C) 2015-2017 Helen Koike <helen.क्रमnazier@gmail.com>
 */

#समावेश <linux/font.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <media/media-device.h>
#समावेश <media/tpg/v4l2-tpg.h>
#समावेश <media/v4l2-device.h>

#समावेश "vimc-common.h"

#घोषणा VIMC_MDEV_MODEL_NAME "VIMC MDEV"

#घोषणा VIMC_ENT_LINK(src, srcpad, sink, sinkpad, link_flags) अणु	\
	.src_ent = src,						\
	.src_pad = srcpad,					\
	.sink_ent = sink,					\
	.sink_pad = sinkpad,					\
	.flags = link_flags,					\
पूर्ण

/* Structure which describes links between entities */
काष्ठा vimc_ent_link अणु
	अचिन्हित पूर्णांक src_ent;
	u16 src_pad;
	अचिन्हित पूर्णांक sink_ent;
	u16 sink_pad;
	u32 flags;
पूर्ण;

/* Structure which describes the whole topology */
काष्ठा vimc_pipeline_config अणु
	स्थिर काष्ठा vimc_ent_config *ents;
	माप_प्रकार num_ents;
	स्थिर काष्ठा vimc_ent_link *links;
	माप_प्रकार num_links;
पूर्ण;

/* --------------------------------------------------------------------------
 * Topology Configuration
 */

अटल काष्ठा vimc_ent_config ent_config[] = अणु
	अणु
		.name = "Sensor A",
		.type = &vimc_sen_type
	पूर्ण,
	अणु
		.name = "Sensor B",
		.type = &vimc_sen_type
	पूर्ण,
	अणु
		.name = "Debayer A",
		.type = &vimc_deb_type
	पूर्ण,
	अणु
		.name = "Debayer B",
		.type = &vimc_deb_type
	पूर्ण,
	अणु
		.name = "Raw Capture 0",
		.type = &vimc_cap_type
	पूर्ण,
	अणु
		.name = "Raw Capture 1",
		.type = &vimc_cap_type
	पूर्ण,
	अणु
		/* TODO: change this to vimc-input when it is implemented */
		.name = "RGB/YUV Input",
		.type = &vimc_sen_type
	पूर्ण,
	अणु
		.name = "Scaler",
		.type = &vimc_sca_type
	पूर्ण,
	अणु
		.name = "RGB/YUV Capture",
		.type = &vimc_cap_type
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vimc_ent_link ent_links[] = अणु
	/* Link: Sensor A (Pad 0)->(Pad 0) Debayer A */
	VIMC_ENT_LINK(0, 0, 2, 0, MEDIA_LNK_FL_ENABLED | MEDIA_LNK_FL_IMMUTABLE),
	/* Link: Sensor A (Pad 0)->(Pad 0) Raw Capture 0 */
	VIMC_ENT_LINK(0, 0, 4, 0, MEDIA_LNK_FL_ENABLED | MEDIA_LNK_FL_IMMUTABLE),
	/* Link: Sensor B (Pad 0)->(Pad 0) Debayer B */
	VIMC_ENT_LINK(1, 0, 3, 0, MEDIA_LNK_FL_ENABLED | MEDIA_LNK_FL_IMMUTABLE),
	/* Link: Sensor B (Pad 0)->(Pad 0) Raw Capture 1 */
	VIMC_ENT_LINK(1, 0, 5, 0, MEDIA_LNK_FL_ENABLED | MEDIA_LNK_FL_IMMUTABLE),
	/* Link: Debayer A (Pad 1)->(Pad 0) Scaler */
	VIMC_ENT_LINK(2, 1, 7, 0, MEDIA_LNK_FL_ENABLED),
	/* Link: Debayer B (Pad 1)->(Pad 0) Scaler */
	VIMC_ENT_LINK(3, 1, 7, 0, 0),
	/* Link: RGB/YUV Input (Pad 0)->(Pad 0) Scaler */
	VIMC_ENT_LINK(6, 0, 7, 0, 0),
	/* Link: Scaler (Pad 1)->(Pad 0) RGB/YUV Capture */
	VIMC_ENT_LINK(7, 1, 8, 0, MEDIA_LNK_FL_ENABLED | MEDIA_LNK_FL_IMMUTABLE),
पूर्ण;

अटल काष्ठा vimc_pipeline_config pipe_cfg = अणु
	.ents		= ent_config,
	.num_ents	= ARRAY_SIZE(ent_config),
	.links		= ent_links,
	.num_links	= ARRAY_SIZE(ent_links)
पूर्ण;

/* -------------------------------------------------------------------------- */

अटल व्योम vimc_rm_links(काष्ठा vimc_device *vimc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < vimc->pipe_cfg->num_ents; i++)
		media_entity_हटाओ_links(vimc->ent_devs[i]->ent);
पूर्ण

अटल पूर्णांक vimc_create_links(काष्ठा vimc_device *vimc)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Initialize the links between entities */
	क्रम (i = 0; i < vimc->pipe_cfg->num_links; i++) अणु
		स्थिर काष्ठा vimc_ent_link *link = &vimc->pipe_cfg->links[i];

		काष्ठा vimc_ent_device *ved_src =
			vimc->ent_devs[link->src_ent];
		काष्ठा vimc_ent_device *ved_sink =
			vimc->ent_devs[link->sink_ent];

		ret = media_create_pad_link(ved_src->ent, link->src_pad,
					    ved_sink->ent, link->sink_pad,
					    link->flags);
		अगर (ret)
			जाओ err_rm_links;
	पूर्ण

	वापस 0;

err_rm_links:
	vimc_rm_links(vimc);
	वापस ret;
पूर्ण

अटल व्योम vimc_release_subdevs(काष्ठा vimc_device *vimc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < vimc->pipe_cfg->num_ents; i++)
		अगर (vimc->ent_devs[i])
			vimc->pipe_cfg->ents[i].type->release(vimc->ent_devs[i]);
पूर्ण

अटल व्योम vimc_unरेजिस्टर_subdevs(काष्ठा vimc_device *vimc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < vimc->pipe_cfg->num_ents; i++)
		अगर (vimc->ent_devs[i] && vimc->pipe_cfg->ents[i].type->unरेजिस्टर)
			vimc->pipe_cfg->ents[i].type->unरेजिस्टर(vimc->ent_devs[i]);
पूर्ण

अटल पूर्णांक vimc_add_subdevs(काष्ठा vimc_device *vimc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < vimc->pipe_cfg->num_ents; i++) अणु
		dev_dbg(vimc->mdev.dev, "new entity for %s\n",
			vimc->pipe_cfg->ents[i].name);
		vimc->ent_devs[i] = vimc->pipe_cfg->ents[i].type->add(vimc,
					vimc->pipe_cfg->ents[i].name);
		अगर (IS_ERR(vimc->ent_devs[i])) अणु
			पूर्णांक err = PTR_ERR(vimc->ent_devs[i]);

			dev_err(vimc->mdev.dev, "adding entity %s failed (%d)\n",
				vimc->pipe_cfg->ents[i].name, err);
			vimc->ent_devs[i] = शून्य;
			vimc_unरेजिस्टर_subdevs(vimc);
			vimc_release_subdevs(vimc);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vimc_v4l2_dev_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा vimc_device *vimc =
		container_of(v4l2_dev, काष्ठा vimc_device, v4l2_dev);

	vimc_release_subdevs(vimc);
	media_device_cleanup(&vimc->mdev);
	kमुक्त(vimc->ent_devs);
	kमुक्त(vimc);
पूर्ण

अटल पूर्णांक vimc_रेजिस्टर_devices(काष्ठा vimc_device *vimc)
अणु
	पूर्णांक ret;

	/* Register the v4l2 काष्ठा */
	ret = v4l2_device_रेजिस्टर(vimc->mdev.dev, &vimc->v4l2_dev);
	अगर (ret) अणु
		dev_err(vimc->mdev.dev,
			"v4l2 device register failed (err=%d)\n", ret);
		वापस ret;
	पूर्ण
	/* allocate ent_devs */
	vimc->ent_devs = kसुस्मृति(vimc->pipe_cfg->num_ents,
				 माप(*vimc->ent_devs), GFP_KERNEL);
	अगर (!vimc->ent_devs) अणु
		ret = -ENOMEM;
		जाओ err_v4l2_unरेजिस्टर;
	पूर्ण

	/* Invoke entity config hooks to initialize and रेजिस्टर subdevs */
	ret = vimc_add_subdevs(vimc);
	अगर (ret)
		जाओ err_मुक्त_ent_devs;

	/* Initialize links */
	ret = vimc_create_links(vimc);
	अगर (ret)
		जाओ err_rm_subdevs;

	/* Register the media device */
	ret = media_device_रेजिस्टर(&vimc->mdev);
	अगर (ret) अणु
		dev_err(vimc->mdev.dev,
			"media device register failed (err=%d)\n", ret);
		जाओ err_rm_subdevs;
	पूर्ण

	/* Expose all subdev's nodes*/
	ret = v4l2_device_रेजिस्टर_subdev_nodes(&vimc->v4l2_dev);
	अगर (ret) अणु
		dev_err(vimc->mdev.dev,
			"vimc subdev nodes registration failed (err=%d)\n",
			ret);
		जाओ err_mdev_unरेजिस्टर;
	पूर्ण

	वापस 0;

err_mdev_unरेजिस्टर:
	media_device_unरेजिस्टर(&vimc->mdev);
err_rm_subdevs:
	vimc_unरेजिस्टर_subdevs(vimc);
	vimc_release_subdevs(vimc);
err_मुक्त_ent_devs:
	kमुक्त(vimc->ent_devs);
err_v4l2_unरेजिस्टर:
	v4l2_device_unरेजिस्टर(&vimc->v4l2_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक vimc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा font_desc *font = find_font("VGA8x16");
	काष्ठा vimc_device *vimc;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "probe");

	अगर (!font) अणु
		dev_err(&pdev->dev, "could not find font\n");
		वापस -ENODEV;
	पूर्ण

	tpg_set_font(font->data);

	vimc = kzalloc(माप(*vimc), GFP_KERNEL);
	अगर (!vimc)
		वापस -ENOMEM;

	vimc->pipe_cfg = &pipe_cfg;

	/* Link the media device within the v4l2_device */
	vimc->v4l2_dev.mdev = &vimc->mdev;

	/* Initialize media device */
	strscpy(vimc->mdev.model, VIMC_MDEV_MODEL_NAME,
		माप(vimc->mdev.model));
	snम_लिखो(vimc->mdev.bus_info, माप(vimc->mdev.bus_info),
		 "platform:%s", VIMC_PDEV_NAME);
	vimc->mdev.dev = &pdev->dev;
	media_device_init(&vimc->mdev);

	ret = vimc_रेजिस्टर_devices(vimc);
	अगर (ret) अणु
		media_device_cleanup(&vimc->mdev);
		kमुक्त(vimc);
		वापस ret;
	पूर्ण
	/*
	 * the release cb is set only after successful registration.
	 * अगर the registration fails, we release directly from probe
	 */

	vimc->v4l2_dev.release = vimc_v4l2_dev_release;
	platक्रमm_set_drvdata(pdev, vimc);
	वापस 0;
पूर्ण

अटल पूर्णांक vimc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vimc_device *vimc = platक्रमm_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "remove");

	vimc_unरेजिस्टर_subdevs(vimc);
	media_device_unरेजिस्टर(&vimc->mdev);
	v4l2_device_unरेजिस्टर(&vimc->v4l2_dev);
	v4l2_device_put(&vimc->v4l2_dev);

	वापस 0;
पूर्ण

अटल व्योम vimc_dev_release(काष्ठा device *dev)
अणु
पूर्ण

अटल काष्ठा platक्रमm_device vimc_pdev = अणु
	.name = VIMC_PDEV_NAME,
	.dev.release = vimc_dev_release,
पूर्ण;

अटल काष्ठा platक्रमm_driver vimc_pdrv = अणु
	.probe		= vimc_probe,
	.हटाओ		= vimc_हटाओ,
	.driver		= अणु
		.name	= VIMC_PDEV_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init vimc_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_device_रेजिस्टर(&vimc_pdev);
	अगर (ret) अणु
		dev_err(&vimc_pdev.dev,
			"platform device registration failed (err=%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&vimc_pdrv);
	अगर (ret) अणु
		dev_err(&vimc_pdev.dev,
			"platform driver registration failed (err=%d)\n", ret);
		platक्रमm_driver_unरेजिस्टर(&vimc_pdrv);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास vimc_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&vimc_pdrv);

	platक्रमm_device_unरेजिस्टर(&vimc_pdev);
पूर्ण

module_init(vimc_init);
module_निकास(vimc_निकास);

MODULE_DESCRIPTION("Virtual Media Controller Driver (VIMC)");
MODULE_AUTHOR("Helen Fornazier <helen.fornazier@gmail.com>");
MODULE_LICENSE("GPL");
