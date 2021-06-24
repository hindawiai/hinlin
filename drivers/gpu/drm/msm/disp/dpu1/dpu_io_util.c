<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2012-2015, 2017-2018, The Linux Foundation.
 * All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk/clk-conf.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "dpu_io_util.h"

व्योम msm_dss_put_clk(काष्ठा dss_clk *clk_arry, पूर्णांक num_clk)
अणु
	पूर्णांक i;

	क्रम (i = num_clk - 1; i >= 0; i--) अणु
		अगर (clk_arry[i].clk)
			clk_put(clk_arry[i].clk);
		clk_arry[i].clk = शून्य;
	पूर्ण
पूर्ण

पूर्णांक msm_dss_get_clk(काष्ठा device *dev, काष्ठा dss_clk *clk_arry, पूर्णांक num_clk)
अणु
	पूर्णांक i, rc = 0;

	क्रम (i = 0; i < num_clk; i++) अणु
		clk_arry[i].clk = clk_get(dev, clk_arry[i].clk_name);
		rc = PTR_ERR_OR_ZERO(clk_arry[i].clk);
		अगर (rc) अणु
			DEV_ERR("%pS->%s: '%s' get failed. rc=%d\n",
				__builtin_वापस_address(0), __func__,
				clk_arry[i].clk_name, rc);
			जाओ error;
		पूर्ण
	पूर्ण

	वापस rc;

error:
	क्रम (i--; i >= 0; i--) अणु
		अगर (clk_arry[i].clk)
			clk_put(clk_arry[i].clk);
		clk_arry[i].clk = शून्य;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक msm_dss_clk_set_rate(काष्ठा dss_clk *clk_arry, पूर्णांक num_clk)
अणु
	पूर्णांक i, rc = 0;

	क्रम (i = 0; i < num_clk; i++) अणु
		अगर (clk_arry[i].clk) अणु
			अगर (clk_arry[i].type != DSS_CLK_AHB) अणु
				DEV_DBG("%pS->%s: '%s' rate %ld\n",
					__builtin_वापस_address(0), __func__,
					clk_arry[i].clk_name,
					clk_arry[i].rate);
				rc = clk_set_rate(clk_arry[i].clk,
					clk_arry[i].rate);
				अगर (rc) अणु
					DEV_ERR("%pS->%s: %s failed. rc=%d\n",
						__builtin_वापस_address(0),
						__func__,
						clk_arry[i].clk_name, rc);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			DEV_ERR("%pS->%s: '%s' is not available\n",
				__builtin_वापस_address(0), __func__,
				clk_arry[i].clk_name);
			rc = -EPERM;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक msm_dss_enable_clk(काष्ठा dss_clk *clk_arry, पूर्णांक num_clk, पूर्णांक enable)
अणु
	पूर्णांक i, rc = 0;

	अगर (enable) अणु
		क्रम (i = 0; i < num_clk; i++) अणु
			DEV_DBG("%pS->%s: enable '%s'\n",
				__builtin_वापस_address(0), __func__,
				clk_arry[i].clk_name);
			rc = clk_prepare_enable(clk_arry[i].clk);
			अगर (rc)
				DEV_ERR("%pS->%s: %s en fail. rc=%d\n",
					__builtin_वापस_address(0),
					__func__,
					clk_arry[i].clk_name, rc);

			अगर (rc && i) अणु
				msm_dss_enable_clk(&clk_arry[i - 1],
					i - 1, false);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = num_clk - 1; i >= 0; i--) अणु
			DEV_DBG("%pS->%s: disable '%s'\n",
				__builtin_वापस_address(0), __func__,
				clk_arry[i].clk_name);

			clk_disable_unprepare(clk_arry[i].clk);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक msm_dss_parse_घड़ी(काष्ठा platक्रमm_device *pdev,
			काष्ठा dss_module_घातer *mp)
अणु
	u32 i, rc = 0;
	स्थिर अक्षर *घड़ी_name;
	पूर्णांक num_clk = 0;

	अगर (!pdev || !mp)
		वापस -EINVAL;

	mp->num_clk = 0;
	num_clk = of_property_count_strings(pdev->dev.of_node, "clock-names");
	अगर (num_clk <= 0) अणु
		pr_debug("clocks are not defined\n");
		वापस 0;
	पूर्ण

	mp->clk_config = devm_kसुस्मृति(&pdev->dev,
				      num_clk, माप(काष्ठा dss_clk),
				      GFP_KERNEL);
	अगर (!mp->clk_config)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_clk; i++) अणु
		rc = of_property_पढ़ो_string_index(pdev->dev.of_node,
						   "clock-names", i,
						   &घड़ी_name);
		अगर (rc) अणु
			DRM_DEV_ERROR(&pdev->dev, "Failed to get clock name for %d\n",
				i);
			अवरोध;
		पूर्ण
		strlcpy(mp->clk_config[i].clk_name, घड़ी_name,
			माप(mp->clk_config[i].clk_name));

		mp->clk_config[i].type = DSS_CLK_AHB;
	पूर्ण

	rc = msm_dss_get_clk(&pdev->dev, mp->clk_config, num_clk);
	अगर (rc) अणु
		DRM_DEV_ERROR(&pdev->dev, "Failed to get clock refs %d\n", rc);
		जाओ err;
	पूर्ण

	rc = of_clk_set_शेषs(pdev->dev.of_node, false);
	अगर (rc) अणु
		DRM_DEV_ERROR(&pdev->dev, "Failed to set clock defaults %d\n", rc);
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < num_clk; i++) अणु
		u32 rate = clk_get_rate(mp->clk_config[i].clk);
		अगर (!rate)
			जारी;
		mp->clk_config[i].rate = rate;
		mp->clk_config[i].type = DSS_CLK_PCLK;
		mp->clk_config[i].max_rate = rate;
	पूर्ण

	mp->num_clk = num_clk;
	वापस 0;

err:
	msm_dss_put_clk(mp->clk_config, num_clk);
	वापस rc;
पूर्ण
