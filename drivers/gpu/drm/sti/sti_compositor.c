<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Benjamin Gaignard <benjamin.gaignard@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          क्रम STMicroelectronics.
 */

#समावेश <linux/component.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_vblank.h>

#समावेश "sti_compositor.h"
#समावेश "sti_crtc.h"
#समावेश "sti_cursor.h"
#समावेश "sti_drv.h"
#समावेश "sti_gdp.h"
#समावेश "sti_plane.h"
#समावेश "sti_vid.h"
#समावेश "sti_vtg.h"

/*
 * stiH407 compositor properties
 */
अटल स्थिर काष्ठा sti_compositor_data stih407_compositor_data = अणु
	.nb_subdev = 8,
	.subdev_desc = अणु
			अणुSTI_CURSOR_SUBDEV, (पूर्णांक)STI_CURSOR, 0x000पूर्ण,
			अणुSTI_GPD_SUBDEV, (पूर्णांक)STI_GDP_0, 0x100पूर्ण,
			अणुSTI_GPD_SUBDEV, (पूर्णांक)STI_GDP_1, 0x200पूर्ण,
			अणुSTI_GPD_SUBDEV, (पूर्णांक)STI_GDP_2, 0x300पूर्ण,
			अणुSTI_GPD_SUBDEV, (पूर्णांक)STI_GDP_3, 0x400पूर्ण,
			अणुSTI_VID_SUBDEV, (पूर्णांक)STI_HQVDP_0, 0x700पूर्ण,
			अणुSTI_MIXER_MAIN_SUBDEV, STI_MIXER_MAIN, 0xC00पूर्ण,
			अणुSTI_MIXER_AUX_SUBDEV, STI_MIXER_AUX, 0xD00पूर्ण,
	पूर्ण,
पूर्ण;

व्योम sti_compositor_debugfs_init(काष्ठा sti_compositor *compo,
				 काष्ठा drm_minor *minor)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < STI_MAX_VID; i++)
		अगर (compo->vid[i])
			vid_debugfs_init(compo->vid[i], minor);

	क्रम (i = 0; i < STI_MAX_MIXER; i++)
		अगर (compo->mixer[i])
			sti_mixer_debugfs_init(compo->mixer[i], minor);
पूर्ण

अटल पूर्णांक sti_compositor_bind(काष्ठा device *dev,
			       काष्ठा device *master,
			       व्योम *data)
अणु
	काष्ठा sti_compositor *compo = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	अचिन्हित पूर्णांक i, mixer_id = 0, vid_id = 0, crtc_id = 0;
	काष्ठा sti_निजी *dev_priv = drm_dev->dev_निजी;
	काष्ठा drm_plane *cursor = शून्य;
	काष्ठा drm_plane *primary = शून्य;
	काष्ठा sti_compositor_subdev_descriptor *desc = compo->data.subdev_desc;
	अचिन्हित पूर्णांक array_size = compo->data.nb_subdev;

	dev_priv->compo = compo;

	/* Register mixer subdev and video subdev first */
	क्रम (i = 0; i < array_size; i++) अणु
		चयन (desc[i].type) अणु
		हाल STI_VID_SUBDEV:
			compo->vid[vid_id++] =
			    sti_vid_create(compo->dev, drm_dev, desc[i].id,
					   compo->regs + desc[i].offset);
			अवरोध;
		हाल STI_MIXER_MAIN_SUBDEV:
		हाल STI_MIXER_AUX_SUBDEV:
			compo->mixer[mixer_id++] =
			    sti_mixer_create(compo->dev, drm_dev, desc[i].id,
					     compo->regs + desc[i].offset);
			अवरोध;
		हाल STI_GPD_SUBDEV:
		हाल STI_CURSOR_SUBDEV:
			/* Nothing to करो, रुको क्रम the second round */
			अवरोध;
		शेष:
			DRM_ERROR("Unknown subdev component type\n");
			वापस 1;
		पूर्ण
	पूर्ण

	/* Register the other subdevs, create crtc and planes */
	क्रम (i = 0; i < array_size; i++) अणु
		क्रमागत drm_plane_type plane_type = DRM_PLANE_TYPE_OVERLAY;

		अगर (crtc_id < mixer_id)
			plane_type = DRM_PLANE_TYPE_PRIMARY;

		चयन (desc[i].type) अणु
		हाल STI_MIXER_MAIN_SUBDEV:
		हाल STI_MIXER_AUX_SUBDEV:
		हाल STI_VID_SUBDEV:
			/* Nothing to करो, alपढ़ोy करोne at the first round */
			अवरोध;
		हाल STI_CURSOR_SUBDEV:
			cursor = sti_cursor_create(drm_dev, compo->dev,
						   desc[i].id,
						   compo->regs + desc[i].offset,
						   1);
			अगर (!cursor) अणु
				DRM_ERROR("Can't create CURSOR plane\n");
				अवरोध;
			पूर्ण
			अवरोध;
		हाल STI_GPD_SUBDEV:
			primary = sti_gdp_create(drm_dev, compo->dev,
						 desc[i].id,
						 compo->regs + desc[i].offset,
						 (1 << mixer_id) - 1,
						 plane_type);
			अगर (!primary) अणु
				DRM_ERROR("Can't create GDP plane\n");
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			DRM_ERROR("Unknown subdev component type\n");
			वापस 1;
		पूर्ण

		/* The first planes are reserved क्रम primary planes*/
		अगर (crtc_id < mixer_id && primary) अणु
			sti_crtc_init(drm_dev, compo->mixer[crtc_id],
				      primary, cursor);
			crtc_id++;
			cursor = शून्य;
			primary = शून्य;
		पूर्ण
	पूर्ण

	drm_vblank_init(drm_dev, crtc_id);
	/* Allow usage of vblank without having to call drm_irq_install */
	drm_dev->irq_enabled = 1;

	वापस 0;
पूर्ण

अटल व्योम sti_compositor_unbind(काष्ठा device *dev, काष्ठा device *master,
	व्योम *data)
अणु
	/* करो nothing */
पूर्ण

अटल स्थिर काष्ठा component_ops sti_compositor_ops = अणु
	.bind	= sti_compositor_bind,
	.unbind	= sti_compositor_unbind,
पूर्ण;

अटल स्थिर काष्ठा of_device_id compositor_of_match[] = अणु
	अणु
		.compatible = "st,stih407-compositor",
		.data = &stih407_compositor_data,
	पूर्ण, अणु
		/* end node */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, compositor_of_match);

अटल पूर्णांक sti_compositor_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *vtg_np;
	काष्ठा sti_compositor *compo;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक i;

	compo = devm_kzalloc(dev, माप(*compo), GFP_KERNEL);
	अगर (!compo) अणु
		DRM_ERROR("Failed to allocate compositor context\n");
		वापस -ENOMEM;
	पूर्ण
	compo->dev = dev;
	क्रम (i = 0; i < STI_MAX_MIXER; i++)
		compo->vtg_vblank_nb[i].notअगरier_call = sti_crtc_vblank_cb;

	/* populate data काष्ठाure depending on compatibility */
	BUG_ON(!of_match_node(compositor_of_match, np)->data);

	स_नकल(&compo->data, of_match_node(compositor_of_match, np)->data,
	       माप(काष्ठा sti_compositor_data));

	/* Get Memory ressources */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		DRM_ERROR("Get memory resource failed\n");
		वापस -ENXIO;
	पूर्ण
	compo->regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (compo->regs == शून्य) अणु
		DRM_ERROR("Register mapping failed\n");
		वापस -ENXIO;
	पूर्ण

	/* Get घड़ी resources */
	compo->clk_compo_मुख्य = devm_clk_get(dev, "compo_main");
	अगर (IS_ERR(compo->clk_compo_मुख्य)) अणु
		DRM_ERROR("Cannot get compo_main clock\n");
		वापस PTR_ERR(compo->clk_compo_मुख्य);
	पूर्ण

	compo->clk_compo_aux = devm_clk_get(dev, "compo_aux");
	अगर (IS_ERR(compo->clk_compo_aux)) अणु
		DRM_ERROR("Cannot get compo_aux clock\n");
		वापस PTR_ERR(compo->clk_compo_aux);
	पूर्ण

	compo->clk_pix_मुख्य = devm_clk_get(dev, "pix_main");
	अगर (IS_ERR(compo->clk_pix_मुख्य)) अणु
		DRM_ERROR("Cannot get pix_main clock\n");
		वापस PTR_ERR(compo->clk_pix_मुख्य);
	पूर्ण

	compo->clk_pix_aux = devm_clk_get(dev, "pix_aux");
	अगर (IS_ERR(compo->clk_pix_aux)) अणु
		DRM_ERROR("Cannot get pix_aux clock\n");
		वापस PTR_ERR(compo->clk_pix_aux);
	पूर्ण

	/* Get reset resources */
	compo->rst_मुख्य = devm_reset_control_get_shared(dev, "compo-main");
	/* Take compo मुख्य out of reset */
	अगर (!IS_ERR(compo->rst_मुख्य))
		reset_control_deनिश्चित(compo->rst_मुख्य);

	compo->rst_aux = devm_reset_control_get_shared(dev, "compo-aux");
	/* Take compo aux out of reset */
	अगर (!IS_ERR(compo->rst_aux))
		reset_control_deनिश्चित(compo->rst_aux);

	vtg_np = of_parse_phandle(pdev->dev.of_node, "st,vtg", 0);
	अगर (vtg_np)
		compo->vtg[STI_MIXER_MAIN] = of_vtg_find(vtg_np);
	of_node_put(vtg_np);

	vtg_np = of_parse_phandle(pdev->dev.of_node, "st,vtg", 1);
	अगर (vtg_np)
		compo->vtg[STI_MIXER_AUX] = of_vtg_find(vtg_np);
	of_node_put(vtg_np);

	platक्रमm_set_drvdata(pdev, compo);

	वापस component_add(&pdev->dev, &sti_compositor_ops);
पूर्ण

अटल पूर्णांक sti_compositor_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &sti_compositor_ops);
	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver sti_compositor_driver = अणु
	.driver = अणु
		.name = "sti-compositor",
		.of_match_table = compositor_of_match,
	पूर्ण,
	.probe = sti_compositor_probe,
	.हटाओ = sti_compositor_हटाओ,
पूर्ण;

MODULE_AUTHOR("Benjamin Gaignard <benjamin.gaignard@st.com>");
MODULE_DESCRIPTION("STMicroelectronics SoC DRM driver");
MODULE_LICENSE("GPL");
