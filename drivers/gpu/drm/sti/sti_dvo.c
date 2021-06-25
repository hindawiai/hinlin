<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Author: Vincent Abriou <vincent.abriou@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "sti_awg_utils.h"
#समावेश "sti_drv.h"
#समावेश "sti_mixer.h"

/* DVO रेजिस्टरs */
#घोषणा DVO_AWG_DIGSYNC_CTRL      0x0000
#घोषणा DVO_DOF_CFG               0x0004
#घोषणा DVO_LUT_PROG_LOW          0x0008
#घोषणा DVO_LUT_PROG_MID          0x000C
#घोषणा DVO_LUT_PROG_HIGH         0x0010
#घोषणा DVO_DIGSYNC_INSTR_I       0x0100

#घोषणा DVO_AWG_CTRL_EN           BIT(0)
#घोषणा DVO_AWG_FRAME_BASED_SYNC  BIT(2)

#घोषणा DVO_DOF_EN_LOWBYTE        BIT(0)
#घोषणा DVO_DOF_EN_MIDBYTE        BIT(1)
#घोषणा DVO_DOF_EN_HIGHBYTE       BIT(2)
#घोषणा DVO_DOF_EN                BIT(6)
#घोषणा DVO_DOF_MOD_COUNT_SHIFT   8

#घोषणा DVO_LUT_ZERO              0
#घोषणा DVO_LUT_Y_G               1
#घोषणा DVO_LUT_Y_G_DEL           2
#घोषणा DVO_LUT_CB_B              3
#घोषणा DVO_LUT_CB_B_DEL          4
#घोषणा DVO_LUT_CR_R              5
#घोषणा DVO_LUT_CR_R_DEL          6
#घोषणा DVO_LUT_HOLD              7

काष्ठा dvo_config अणु
	u32 flags;
	u32 lowbyte;
	u32 midbyte;
	u32 highbyte;
	पूर्णांक (*awg_fwgen_fct)(
			काष्ठा awg_code_generation_params *fw_gen_params,
			काष्ठा awg_timing *timing);
पूर्ण;

अटल काष्ठा dvo_config rgb_24bit_de_cfg = अणु
	.flags         = (0L << DVO_DOF_MOD_COUNT_SHIFT),
	.lowbyte       = DVO_LUT_CR_R,
	.midbyte       = DVO_LUT_Y_G,
	.highbyte      = DVO_LUT_CB_B,
	.awg_fwgen_fct = sti_awg_generate_code_data_enable_mode,
पूर्ण;

/*
 * STI digital video output काष्ठाure
 *
 * @dev: driver device
 * @drm_dev: poपूर्णांकer to drm device
 * @mode: current display mode selected
 * @regs: dvo रेजिस्टरs
 * @clk_pix: pixel घड़ी क्रम dvo
 * @clk: घड़ी क्रम dvo
 * @clk_मुख्य_parent: dvo parent घड़ी अगर मुख्य path used
 * @clk_aux_parent: dvo parent घड़ी अगर aux path used
 * @panel_node: panel node reference from device tree
 * @panel: reference to the panel connected to the dvo
 * @enabled: true अगर dvo is enabled अन्यथा false
 * @encoder: drm_encoder it is bound
 */
काष्ठा sti_dvo अणु
	काष्ठा device dev;
	काष्ठा drm_device *drm_dev;
	काष्ठा drm_display_mode mode;
	व्योम __iomem *regs;
	काष्ठा clk *clk_pix;
	काष्ठा clk *clk;
	काष्ठा clk *clk_मुख्य_parent;
	काष्ठा clk *clk_aux_parent;
	काष्ठा device_node *panel_node;
	काष्ठा drm_panel *panel;
	काष्ठा dvo_config *config;
	bool enabled;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_bridge *bridge;
पूर्ण;

काष्ठा sti_dvo_connector अणु
	काष्ठा drm_connector drm_connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा sti_dvo *dvo;
पूर्ण;

#घोषणा to_sti_dvo_connector(x) \
	container_of(x, काष्ठा sti_dvo_connector, drm_connector)

#घोषणा BLANKING_LEVEL 16
अटल पूर्णांक dvo_awg_generate_code(काष्ठा sti_dvo *dvo, u8 *ram_size, u32 *ram_code)
अणु
	काष्ठा drm_display_mode *mode = &dvo->mode;
	काष्ठा dvo_config *config = dvo->config;
	काष्ठा awg_code_generation_params fw_gen_params;
	काष्ठा awg_timing timing;

	fw_gen_params.ram_code = ram_code;
	fw_gen_params.inकाष्ठाion_offset = 0;

	timing.total_lines = mode->vtotal;
	timing.active_lines = mode->vdisplay;
	timing.blanking_lines = mode->vsync_start - mode->vdisplay;
	timing.trailing_lines = mode->vtotal - mode->vsync_start;
	timing.total_pixels = mode->htotal;
	timing.active_pixels = mode->hdisplay;
	timing.blanking_pixels = mode->hsync_start - mode->hdisplay;
	timing.trailing_pixels = mode->htotal - mode->hsync_start;
	timing.blanking_level = BLANKING_LEVEL;

	अगर (config->awg_fwgen_fct(&fw_gen_params, &timing)) अणु
		DRM_ERROR("AWG firmware not properly generated\n");
		वापस -EINVAL;
	पूर्ण

	*ram_size = fw_gen_params.inकाष्ठाion_offset;

	वापस 0;
पूर्ण

/* Configure AWG, writing inकाष्ठाions
 *
 * @dvo: poपूर्णांकer to DVO काष्ठाure
 * @awg_ram_code: poपूर्णांकer to AWG inकाष्ठाions table
 * @nb: nb of AWG inकाष्ठाions
 */
अटल व्योम dvo_awg_configure(काष्ठा sti_dvo *dvo, u32 *awg_ram_code, पूर्णांक nb)
अणु
	पूर्णांक i;

	DRM_DEBUG_DRIVER("\n");

	क्रम (i = 0; i < nb; i++)
		ग_लिखोl(awg_ram_code[i],
		       dvo->regs + DVO_DIGSYNC_INSTR_I + i * 4);
	क्रम (i = nb; i < AWG_MAX_INST; i++)
		ग_लिखोl(0, dvo->regs + DVO_DIGSYNC_INSTR_I + i * 4);

	ग_लिखोl(DVO_AWG_CTRL_EN, dvo->regs + DVO_AWG_DIGSYNC_CTRL);
पूर्ण

#घोषणा DBGFS_DUMP(reg) seq_म_लिखो(s, "\n  %-25s 0x%08X", #reg, \
				   पढ़ोl(dvo->regs + reg))

अटल व्योम dvo_dbg_awg_microcode(काष्ठा seq_file *s, व्योम __iomem *reg)
अणु
	अचिन्हित पूर्णांक i;

	seq_माला_दो(s, "\n\n");
	seq_माला_दो(s, "  DVO AWG microcode:");
	क्रम (i = 0; i < AWG_MAX_INST; i++) अणु
		अगर (i % 8 == 0)
			seq_म_लिखो(s, "\n  %04X:", i);
		seq_म_लिखो(s, " %04X", पढ़ोl(reg + i * 4));
	पूर्ण
पूर्ण

अटल पूर्णांक dvo_dbg_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा sti_dvo *dvo = (काष्ठा sti_dvo *)node->info_ent->data;

	seq_म_लिखो(s, "DVO: (vaddr = 0x%p)", dvo->regs);
	DBGFS_DUMP(DVO_AWG_DIGSYNC_CTRL);
	DBGFS_DUMP(DVO_DOF_CFG);
	DBGFS_DUMP(DVO_LUT_PROG_LOW);
	DBGFS_DUMP(DVO_LUT_PROG_MID);
	DBGFS_DUMP(DVO_LUT_PROG_HIGH);
	dvo_dbg_awg_microcode(s, dvo->regs + DVO_DIGSYNC_INSTR_I);
	seq_अ_दो(s, '\n');
	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list dvo_debugfs_files[] = अणु
	अणु "dvo", dvo_dbg_show, 0, शून्य पूर्ण,
पूर्ण;

अटल व्योम dvo_debugfs_init(काष्ठा sti_dvo *dvo, काष्ठा drm_minor *minor)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dvo_debugfs_files); i++)
		dvo_debugfs_files[i].data = dvo;

	drm_debugfs_create_files(dvo_debugfs_files,
				 ARRAY_SIZE(dvo_debugfs_files),
				 minor->debugfs_root, minor);
पूर्ण

अटल व्योम sti_dvo_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा sti_dvo *dvo = bridge->driver_निजी;

	अगर (!dvo->enabled)
		वापस;

	DRM_DEBUG_DRIVER("\n");

	अगर (dvo->config->awg_fwgen_fct)
		ग_लिखोl(0x00000000, dvo->regs + DVO_AWG_DIGSYNC_CTRL);

	ग_लिखोl(0x00000000, dvo->regs + DVO_DOF_CFG);

	drm_panel_disable(dvo->panel);

	/* Disable/unprepare dvo घड़ी */
	clk_disable_unprepare(dvo->clk_pix);
	clk_disable_unprepare(dvo->clk);

	dvo->enabled = false;
पूर्ण

अटल व्योम sti_dvo_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा sti_dvo *dvo = bridge->driver_निजी;
	काष्ठा dvo_config *config = dvo->config;
	u32 val;

	DRM_DEBUG_DRIVER("\n");

	अगर (dvo->enabled)
		वापस;

	/* Make sure DVO is disabled */
	ग_लिखोl(0x00000000, dvo->regs + DVO_DOF_CFG);
	ग_लिखोl(0x00000000, dvo->regs + DVO_AWG_DIGSYNC_CTRL);

	अगर (config->awg_fwgen_fct) अणु
		u8 nb_instr;
		u32 awg_ram_code[AWG_MAX_INST];
		/* Configure AWG */
		अगर (!dvo_awg_generate_code(dvo, &nb_instr, awg_ram_code))
			dvo_awg_configure(dvo, awg_ram_code, nb_instr);
		अन्यथा
			वापस;
	पूर्ण

	/* Prepare/enable घड़ीs */
	अगर (clk_prepare_enable(dvo->clk_pix))
		DRM_ERROR("Failed to prepare/enable dvo_pix clk\n");
	अगर (clk_prepare_enable(dvo->clk))
		DRM_ERROR("Failed to prepare/enable dvo clk\n");

	drm_panel_enable(dvo->panel);

	/* Set LUT */
	ग_लिखोl(config->lowbyte,  dvo->regs + DVO_LUT_PROG_LOW);
	ग_लिखोl(config->midbyte,  dvo->regs + DVO_LUT_PROG_MID);
	ग_लिखोl(config->highbyte, dvo->regs + DVO_LUT_PROG_HIGH);

	/* Digital output क्रमmatter config */
	val = (config->flags | DVO_DOF_EN);
	ग_लिखोl(val, dvo->regs + DVO_DOF_CFG);

	dvo->enabled = true;
पूर्ण

अटल व्योम sti_dvo_set_mode(काष्ठा drm_bridge *bridge,
			     स्थिर काष्ठा drm_display_mode *mode,
			     स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा sti_dvo *dvo = bridge->driver_निजी;
	काष्ठा sti_mixer *mixer = to_sti_mixer(dvo->encoder->crtc);
	पूर्णांक rate = mode->घड़ी * 1000;
	काष्ठा clk *clkp;
	पूर्णांक ret;

	DRM_DEBUG_DRIVER("\n");

	स_नकल(&dvo->mode, mode, माप(काष्ठा drm_display_mode));

	/* According to the path used (मुख्य or aux), the dvo घड़ीs should
	 * have a dअगरferent parent घड़ी. */
	अगर (mixer->id == STI_MIXER_MAIN)
		clkp = dvo->clk_मुख्य_parent;
	अन्यथा
		clkp = dvo->clk_aux_parent;

	अगर (clkp) अणु
		clk_set_parent(dvo->clk_pix, clkp);
		clk_set_parent(dvo->clk, clkp);
	पूर्ण

	/* DVO घड़ीs = compositor घड़ी */
	ret = clk_set_rate(dvo->clk_pix, rate);
	अगर (ret < 0) अणु
		DRM_ERROR("Cannot set rate (%dHz) for dvo_pix clk\n", rate);
		वापस;
	पूर्ण

	ret = clk_set_rate(dvo->clk, rate);
	अगर (ret < 0) अणु
		DRM_ERROR("Cannot set rate (%dHz) for dvo clk\n", rate);
		वापस;
	पूर्ण

	/* For now, we only support 24bit data enable (DE) synchro क्रमmat */
	dvo->config = &rgb_24bit_de_cfg;
पूर्ण

अटल व्योम sti_dvo_bridge_nope(काष्ठा drm_bridge *bridge)
अणु
	/* करो nothing */
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs sti_dvo_bridge_funcs = अणु
	.pre_enable = sti_dvo_pre_enable,
	.enable = sti_dvo_bridge_nope,
	.disable = sti_dvo_disable,
	.post_disable = sti_dvo_bridge_nope,
	.mode_set = sti_dvo_set_mode,
पूर्ण;

अटल पूर्णांक sti_dvo_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा sti_dvo_connector *dvo_connector
		= to_sti_dvo_connector(connector);
	काष्ठा sti_dvo *dvo = dvo_connector->dvo;

	अगर (dvo->panel)
		वापस drm_panel_get_modes(dvo->panel, connector);

	वापस 0;
पूर्ण

#घोषणा CLK_TOLERANCE_HZ 50

अटल पूर्णांक sti_dvo_connector_mode_valid(काष्ठा drm_connector *connector,
					काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक target = mode->घड़ी * 1000;
	पूर्णांक target_min = target - CLK_TOLERANCE_HZ;
	पूर्णांक target_max = target + CLK_TOLERANCE_HZ;
	पूर्णांक result;
	काष्ठा sti_dvo_connector *dvo_connector
		= to_sti_dvo_connector(connector);
	काष्ठा sti_dvo *dvo = dvo_connector->dvo;

	result = clk_round_rate(dvo->clk_pix, target);

	DRM_DEBUG_DRIVER("target rate = %d => available rate = %d\n",
			 target, result);

	अगर ((result < target_min) || (result > target_max)) अणु
		DRM_DEBUG_DRIVER("dvo pixclk=%d not supported\n", target);
		वापस MODE_BAD;
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल स्थिर
काष्ठा drm_connector_helper_funcs sti_dvo_connector_helper_funcs = अणु
	.get_modes = sti_dvo_connector_get_modes,
	.mode_valid = sti_dvo_connector_mode_valid,
पूर्ण;

अटल क्रमागत drm_connector_status
sti_dvo_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा sti_dvo_connector *dvo_connector
		= to_sti_dvo_connector(connector);
	काष्ठा sti_dvo *dvo = dvo_connector->dvo;

	DRM_DEBUG_DRIVER("\n");

	अगर (!dvo->panel) अणु
		dvo->panel = of_drm_find_panel(dvo->panel_node);
		अगर (IS_ERR(dvo->panel))
			dvo->panel = शून्य;
	पूर्ण

	अगर (dvo->panel)
		वापस connector_status_connected;

	वापस connector_status_disconnected;
पूर्ण

अटल पूर्णांक sti_dvo_late_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा sti_dvo_connector *dvo_connector
		= to_sti_dvo_connector(connector);
	काष्ठा sti_dvo *dvo = dvo_connector->dvo;

	dvo_debugfs_init(dvo, dvo->drm_dev->primary);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs sti_dvo_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = sti_dvo_connector_detect,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.late_रेजिस्टर = sti_dvo_late_रेजिस्टर,
पूर्ण;

अटल काष्ठा drm_encoder *sti_dvo_find_encoder(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_encoder *encoder;

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (encoder->encoder_type == DRM_MODE_ENCODER_LVDS)
			वापस encoder;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक sti_dvo_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा sti_dvo *dvo = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा drm_encoder *encoder;
	काष्ठा sti_dvo_connector *connector;
	काष्ठा drm_connector *drm_connector;
	काष्ठा drm_bridge *bridge;
	पूर्णांक err;

	/* Set the drm device handle */
	dvo->drm_dev = drm_dev;

	encoder = sti_dvo_find_encoder(drm_dev);
	अगर (!encoder)
		वापस -ENOMEM;

	connector = devm_kzalloc(dev, माप(*connector), GFP_KERNEL);
	अगर (!connector)
		वापस -ENOMEM;

	connector->dvo = dvo;

	bridge = devm_kzalloc(dev, माप(*bridge), GFP_KERNEL);
	अगर (!bridge)
		वापस -ENOMEM;

	bridge->driver_निजी = dvo;
	bridge->funcs = &sti_dvo_bridge_funcs;
	bridge->of_node = dvo->dev.of_node;
	drm_bridge_add(bridge);

	err = drm_bridge_attach(encoder, bridge, शून्य, 0);
	अगर (err) अणु
		DRM_ERROR("Failed to attach bridge\n");
		वापस err;
	पूर्ण

	dvo->bridge = bridge;
	connector->encoder = encoder;
	dvo->encoder = encoder;

	drm_connector = (काष्ठा drm_connector *)connector;

	drm_connector->polled = DRM_CONNECTOR_POLL_HPD;

	drm_connector_init(drm_dev, drm_connector,
			   &sti_dvo_connector_funcs, DRM_MODE_CONNECTOR_LVDS);
	drm_connector_helper_add(drm_connector,
				 &sti_dvo_connector_helper_funcs);

	err = drm_connector_attach_encoder(drm_connector, encoder);
	अगर (err) अणु
		DRM_ERROR("Failed to attach a connector to a encoder\n");
		जाओ err_sysfs;
	पूर्ण

	वापस 0;

err_sysfs:
	drm_bridge_हटाओ(bridge);
	वापस -EINVAL;
पूर्ण

अटल व्योम sti_dvo_unbind(काष्ठा device *dev,
			   काष्ठा device *master, व्योम *data)
अणु
	काष्ठा sti_dvo *dvo = dev_get_drvdata(dev);

	drm_bridge_हटाओ(dvo->bridge);
पूर्ण

अटल स्थिर काष्ठा component_ops sti_dvo_ops = अणु
	.bind = sti_dvo_bind,
	.unbind = sti_dvo_unbind,
पूर्ण;

अटल पूर्णांक sti_dvo_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sti_dvo *dvo;
	काष्ठा resource *res;
	काष्ठा device_node *np = dev->of_node;

	DRM_INFO("%s\n", __func__);

	dvo = devm_kzalloc(dev, माप(*dvo), GFP_KERNEL);
	अगर (!dvo) अणु
		DRM_ERROR("Failed to allocate memory for DVO\n");
		वापस -ENOMEM;
	पूर्ण

	dvo->dev = pdev->dev;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dvo-reg");
	अगर (!res) अणु
		DRM_ERROR("Invalid dvo resource\n");
		वापस -ENOMEM;
	पूर्ण
	dvo->regs = devm_ioremap(dev, res->start,
			resource_size(res));
	अगर (!dvo->regs)
		वापस -ENOMEM;

	dvo->clk_pix = devm_clk_get(dev, "dvo_pix");
	अगर (IS_ERR(dvo->clk_pix)) अणु
		DRM_ERROR("Cannot get dvo_pix clock\n");
		वापस PTR_ERR(dvo->clk_pix);
	पूर्ण

	dvo->clk = devm_clk_get(dev, "dvo");
	अगर (IS_ERR(dvo->clk)) अणु
		DRM_ERROR("Cannot get dvo clock\n");
		वापस PTR_ERR(dvo->clk);
	पूर्ण

	dvo->clk_मुख्य_parent = devm_clk_get(dev, "main_parent");
	अगर (IS_ERR(dvo->clk_मुख्य_parent)) अणु
		DRM_DEBUG_DRIVER("Cannot get main_parent clock\n");
		dvo->clk_मुख्य_parent = शून्य;
	पूर्ण

	dvo->clk_aux_parent = devm_clk_get(dev, "aux_parent");
	अगर (IS_ERR(dvo->clk_aux_parent)) अणु
		DRM_DEBUG_DRIVER("Cannot get aux_parent clock\n");
		dvo->clk_aux_parent = शून्य;
	पूर्ण

	dvo->panel_node = of_parse_phandle(np, "sti,panel", 0);
	अगर (!dvo->panel_node)
		DRM_ERROR("No panel associated to the dvo output\n");
	of_node_put(dvo->panel_node);

	platक्रमm_set_drvdata(pdev, dvo);

	वापस component_add(&pdev->dev, &sti_dvo_ops);
पूर्ण

अटल पूर्णांक sti_dvo_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &sti_dvo_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dvo_of_match[] = अणु
	अणु .compatible = "st,stih407-dvo", पूर्ण,
	अणु /* end node */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dvo_of_match);

काष्ठा platक्रमm_driver sti_dvo_driver = अणु
	.driver = अणु
		.name = "sti-dvo",
		.owner = THIS_MODULE,
		.of_match_table = dvo_of_match,
	पूर्ण,
	.probe = sti_dvo_probe,
	.हटाओ = sti_dvo_हटाओ,
पूर्ण;

MODULE_AUTHOR("Benjamin Gaignard <benjamin.gaignard@st.com>");
MODULE_DESCRIPTION("STMicroelectronics SoC DRM driver");
MODULE_LICENSE("GPL");
