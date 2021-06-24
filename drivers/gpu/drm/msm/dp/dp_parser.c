<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/of_gpपन.स>
#समावेश <linux/phy/phy.h>

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "dp_parser.h"
#समावेश "dp_reg.h"

अटल स्थिर काष्ठा dp_regulator_cfg sdm845_dp_reg_cfg = अणु
	.num = 2,
	.regs = अणु
		अणु"vdda-1p2", 21800, 4 पूर्ण,	/* 1.2 V */
		अणु"vdda-0p9", 36000, 32 पूर्ण,	/* 0.9 V */
	पूर्ण,
पूर्ण;

अटल पूर्णांक msm_dss_ioremap(काष्ठा platक्रमm_device *pdev,
				काष्ठा dss_io_data *io_data)
अणु
	काष्ठा resource *res = शून्य;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		DRM_ERROR("%pS->%s: msm_dss_get_res failed\n",
			__builtin_वापस_address(0), __func__);
		वापस -ENODEV;
	पूर्ण

	io_data->len = (u32)resource_size(res);
	io_data->base = ioremap(res->start, io_data->len);
	अगर (!io_data->base) अणु
		DRM_ERROR("%pS->%s: ioremap failed\n",
			__builtin_वापस_address(0), __func__);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम msm_dss_iounmap(काष्ठा dss_io_data *io_data)
अणु
	अगर (io_data->base) अणु
		iounmap(io_data->base);
		io_data->base = शून्य;
	पूर्ण
	io_data->len = 0;
पूर्ण

अटल व्योम dp_parser_unmap_io_resources(काष्ठा dp_parser *parser)
अणु
	काष्ठा dp_io *io = &parser->io;

	msm_dss_iounmap(&io->dp_controller);
पूर्ण

अटल पूर्णांक dp_parser_ctrl_res(काष्ठा dp_parser *parser)
अणु
	पूर्णांक rc = 0;
	काष्ठा platक्रमm_device *pdev = parser->pdev;
	काष्ठा dp_io *io = &parser->io;

	rc = msm_dss_ioremap(pdev, &io->dp_controller);
	अगर (rc) अणु
		DRM_ERROR("unable to remap dp io resources, rc=%d\n", rc);
		जाओ err;
	पूर्ण

	io->phy = devm_phy_get(&pdev->dev, "dp");
	अगर (IS_ERR(io->phy)) अणु
		rc = PTR_ERR(io->phy);
		जाओ err;
	पूर्ण

	वापस 0;
err:
	dp_parser_unmap_io_resources(parser);
	वापस rc;
पूर्ण

अटल पूर्णांक dp_parser_misc(काष्ठा dp_parser *parser)
अणु
	काष्ठा device_node *of_node = parser->pdev->dev.of_node;
	पूर्णांक len = 0;
	स्थिर अक्षर *data_lane_property = "data-lanes";

	len = of_property_count_elems_of_size(of_node,
			 data_lane_property, माप(u32));
	अगर (len < 0) अणु
		DRM_WARN("Invalid property %s, default max DP lanes = %d\n",
				data_lane_property, DP_MAX_NUM_DP_LANES);
		len = DP_MAX_NUM_DP_LANES;
	पूर्ण

	parser->max_dp_lanes = len;
	वापस 0;
पूर्ण

अटल अंतरभूत bool dp_parser_check_prefix(स्थिर अक्षर *clk_prefix,
						स्थिर अक्षर *clk_name)
अणु
	वापस !म_भेदन(clk_prefix, clk_name, म_माप(clk_prefix));
पूर्ण

अटल पूर्णांक dp_parser_init_clk_data(काष्ठा dp_parser *parser)
अणु
	पूर्णांक num_clk, i, rc;
	पूर्णांक core_clk_count = 0, ctrl_clk_count = 0, stream_clk_count = 0;
	स्थिर अक्षर *clk_name;
	काष्ठा device *dev = &parser->pdev->dev;
	काष्ठा dss_module_घातer *core_घातer = &parser->mp[DP_CORE_PM];
	काष्ठा dss_module_घातer *ctrl_घातer = &parser->mp[DP_CTRL_PM];
	काष्ठा dss_module_घातer *stream_घातer = &parser->mp[DP_STREAM_PM];

	num_clk = of_property_count_strings(dev->of_node, "clock-names");
	अगर (num_clk <= 0) अणु
		DRM_ERROR("no clocks are defined\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num_clk; i++) अणु
		rc = of_property_पढ़ो_string_index(dev->of_node,
				"clock-names", i, &clk_name);
		अगर (rc < 0)
			वापस rc;

		अगर (dp_parser_check_prefix("core", clk_name))
			core_clk_count++;

		अगर (dp_parser_check_prefix("ctrl", clk_name))
			ctrl_clk_count++;

		अगर (dp_parser_check_prefix("stream", clk_name))
			stream_clk_count++;
	पूर्ण

	/* Initialize the CORE घातer module */
	अगर (core_clk_count == 0) अणु
		DRM_ERROR("no core clocks are defined\n");
		वापस -EINVAL;
	पूर्ण

	core_घातer->num_clk = core_clk_count;
	core_घातer->clk_config = devm_kzalloc(dev,
			माप(काष्ठा dss_clk) * core_घातer->num_clk,
			GFP_KERNEL);
	अगर (!core_घातer->clk_config)
		वापस -EINVAL;

	/* Initialize the CTRL घातer module */
	अगर (ctrl_clk_count == 0) अणु
		DRM_ERROR("no ctrl clocks are defined\n");
		वापस -EINVAL;
	पूर्ण

	ctrl_घातer->num_clk = ctrl_clk_count;
	ctrl_घातer->clk_config = devm_kzalloc(dev,
			माप(काष्ठा dss_clk) * ctrl_घातer->num_clk,
			GFP_KERNEL);
	अगर (!ctrl_घातer->clk_config) अणु
		ctrl_घातer->num_clk = 0;
		वापस -EINVAL;
	पूर्ण

	/* Initialize the STREAM घातer module */
	अगर (stream_clk_count == 0) अणु
		DRM_ERROR("no stream (pixel) clocks are defined\n");
		वापस -EINVAL;
	पूर्ण

	stream_घातer->num_clk = stream_clk_count;
	stream_घातer->clk_config = devm_kzalloc(dev,
			माप(काष्ठा dss_clk) * stream_घातer->num_clk,
			GFP_KERNEL);
	अगर (!stream_घातer->clk_config) अणु
		stream_घातer->num_clk = 0;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dp_parser_घड़ी(काष्ठा dp_parser *parser)
अणु
	पूर्णांक rc = 0, i = 0;
	पूर्णांक num_clk = 0;
	पूर्णांक core_clk_index = 0, ctrl_clk_index = 0, stream_clk_index = 0;
	पूर्णांक core_clk_count = 0, ctrl_clk_count = 0, stream_clk_count = 0;
	स्थिर अक्षर *clk_name;
	काष्ठा device *dev = &parser->pdev->dev;
	काष्ठा dss_module_घातer *core_घातer = &parser->mp[DP_CORE_PM];
	काष्ठा dss_module_घातer *ctrl_घातer = &parser->mp[DP_CTRL_PM];
	काष्ठा dss_module_घातer *stream_घातer = &parser->mp[DP_STREAM_PM];

	rc =  dp_parser_init_clk_data(parser);
	अगर (rc) अणु
		DRM_ERROR("failed to initialize power data %d\n", rc);
		वापस -EINVAL;
	पूर्ण

	core_clk_count = core_घातer->num_clk;
	ctrl_clk_count = ctrl_घातer->num_clk;
	stream_clk_count = stream_घातer->num_clk;

	num_clk = core_clk_count + ctrl_clk_count + stream_clk_count;

	क्रम (i = 0; i < num_clk; i++) अणु
		rc = of_property_पढ़ो_string_index(dev->of_node, "clock-names",
				i, &clk_name);
		अगर (rc) अणु
			DRM_ERROR("error reading clock-names %d\n", rc);
			वापस rc;
		पूर्ण
		अगर (dp_parser_check_prefix("core", clk_name) &&
				core_clk_index < core_clk_count) अणु
			काष्ठा dss_clk *clk =
				&core_घातer->clk_config[core_clk_index];
			strlcpy(clk->clk_name, clk_name, माप(clk->clk_name));
			clk->type = DSS_CLK_AHB;
			core_clk_index++;
		पूर्ण अन्यथा अगर (dp_parser_check_prefix("stream", clk_name) &&
				stream_clk_index < stream_clk_count) अणु
			काष्ठा dss_clk *clk =
				&stream_घातer->clk_config[stream_clk_index];
			strlcpy(clk->clk_name, clk_name, माप(clk->clk_name));
			clk->type = DSS_CLK_PCLK;
			stream_clk_index++;
		पूर्ण अन्यथा अगर (dp_parser_check_prefix("ctrl", clk_name) &&
			   ctrl_clk_index < ctrl_clk_count) अणु
			काष्ठा dss_clk *clk =
				&ctrl_घातer->clk_config[ctrl_clk_index];
			strlcpy(clk->clk_name, clk_name, माप(clk->clk_name));
			ctrl_clk_index++;
			अगर (dp_parser_check_prefix("ctrl_link", clk_name) ||
			    dp_parser_check_prefix("stream_pixel", clk_name))
				clk->type = DSS_CLK_PCLK;
			अन्यथा
				clk->type = DSS_CLK_AHB;
		पूर्ण
	पूर्ण

	DRM_DEBUG_DP("clock parsing successful\n");

	वापस 0;
पूर्ण

अटल पूर्णांक dp_parser_parse(काष्ठा dp_parser *parser)
अणु
	पूर्णांक rc = 0;

	अगर (!parser) अणु
		DRM_ERROR("invalid input\n");
		वापस -EINVAL;
	पूर्ण

	rc = dp_parser_ctrl_res(parser);
	अगर (rc)
		वापस rc;

	rc = dp_parser_misc(parser);
	अगर (rc)
		वापस rc;

	rc = dp_parser_घड़ी(parser);
	अगर (rc)
		वापस rc;

	/* Map the corresponding regulator inक्रमmation according to
	 * version. Currently, since we only have one supported platक्रमm,
	 * mapping the regulator directly.
	 */
	parser->regulator_cfg = &sdm845_dp_reg_cfg;

	वापस 0;
पूर्ण

काष्ठा dp_parser *dp_parser_get(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dp_parser *parser;

	parser = devm_kzalloc(&pdev->dev, माप(*parser), GFP_KERNEL);
	अगर (!parser)
		वापस ERR_PTR(-ENOMEM);

	parser->parse = dp_parser_parse;
	parser->pdev = pdev;

	वापस parser;
पूर्ण
