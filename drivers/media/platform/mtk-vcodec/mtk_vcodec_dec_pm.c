<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Tअगरfany Lin <tअगरfany.lin@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <soc/mediatek/smi.h>

#समावेश "mtk_vcodec_dec_pm.h"
#समावेश "mtk_vcodec_util.h"

पूर्णांक mtk_vcodec_init_dec_pm(काष्ठा mtk_vcodec_dev *mtkdev)
अणु
	काष्ठा device_node *node;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा mtk_vcodec_pm *pm;
	काष्ठा mtk_vcodec_clk *dec_clk;
	काष्ठा mtk_vcodec_clk_info *clk_info;
	पूर्णांक i = 0, ret = 0;

	pdev = mtkdev->plat_dev;
	pm = &mtkdev->pm;
	pm->mtkdev = mtkdev;
	dec_clk = &pm->vdec_clk;
	node = of_parse_phandle(pdev->dev.of_node, "mediatek,larb", 0);
	अगर (!node) अणु
		mtk_v4l2_err("of_parse_phandle mediatek,larb fail!");
		वापस -1;
	पूर्ण

	pdev = of_find_device_by_node(node);
	of_node_put(node);
	अगर (WARN_ON(!pdev)) अणु
		वापस -1;
	पूर्ण
	pm->larbvdec = &pdev->dev;
	pdev = mtkdev->plat_dev;
	pm->dev = &pdev->dev;

	dec_clk->clk_num =
		of_property_count_strings(pdev->dev.of_node, "clock-names");
	अगर (dec_clk->clk_num > 0) अणु
		dec_clk->clk_info = devm_kसुस्मृति(&pdev->dev,
			dec_clk->clk_num, माप(*clk_info),
			GFP_KERNEL);
		अगर (!dec_clk->clk_info) अणु
			ret = -ENOMEM;
			जाओ put_device;
		पूर्ण
	पूर्ण अन्यथा अणु
		mtk_v4l2_err("Failed to get vdec clock count");
		ret = -EINVAL;
		जाओ put_device;
	पूर्ण

	क्रम (i = 0; i < dec_clk->clk_num; i++) अणु
		clk_info = &dec_clk->clk_info[i];
		ret = of_property_पढ़ो_string_index(pdev->dev.of_node,
			"clock-names", i, &clk_info->clk_name);
		अगर (ret) अणु
			mtk_v4l2_err("Failed to get clock name id = %d", i);
			जाओ put_device;
		पूर्ण
		clk_info->vcodec_clk = devm_clk_get(&pdev->dev,
			clk_info->clk_name);
		अगर (IS_ERR(clk_info->vcodec_clk)) अणु
			mtk_v4l2_err("devm_clk_get (%d)%s fail", i,
				clk_info->clk_name);
			ret = PTR_ERR(clk_info->vcodec_clk);
			जाओ put_device;
		पूर्ण
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	वापस 0;
put_device:
	put_device(pm->larbvdec);
	वापस ret;
पूर्ण

व्योम mtk_vcodec_release_dec_pm(काष्ठा mtk_vcodec_dev *dev)
अणु
	pm_runसमय_disable(dev->pm.dev);
	put_device(dev->pm.larbvdec);
पूर्ण

व्योम mtk_vcodec_dec_pw_on(काष्ठा mtk_vcodec_pm *pm)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(pm->dev);
	अगर (ret)
		mtk_v4l2_err("pm_runtime_get_sync fail %d", ret);
पूर्ण

व्योम mtk_vcodec_dec_pw_off(काष्ठा mtk_vcodec_pm *pm)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_put_sync(pm->dev);
	अगर (ret)
		mtk_v4l2_err("pm_runtime_put_sync fail %d", ret);
पूर्ण

व्योम mtk_vcodec_dec_घड़ी_on(काष्ठा mtk_vcodec_pm *pm)
अणु
	काष्ठा mtk_vcodec_clk *dec_clk = &pm->vdec_clk;
	पूर्णांक ret, i = 0;

	क्रम (i = 0; i < dec_clk->clk_num; i++) अणु
		ret = clk_prepare_enable(dec_clk->clk_info[i].vcodec_clk);
		अगर (ret) अणु
			mtk_v4l2_err("clk_prepare_enable %d %s fail %d", i,
				dec_clk->clk_info[i].clk_name, ret);
			जाओ error;
		पूर्ण
	पूर्ण

	ret = mtk_smi_larb_get(pm->larbvdec);
	अगर (ret) अणु
		mtk_v4l2_err("mtk_smi_larb_get larbvdec fail %d", ret);
		जाओ error;
	पूर्ण
	वापस;

error:
	क्रम (i -= 1; i >= 0; i--)
		clk_disable_unprepare(dec_clk->clk_info[i].vcodec_clk);
पूर्ण

व्योम mtk_vcodec_dec_घड़ी_off(काष्ठा mtk_vcodec_pm *pm)
अणु
	काष्ठा mtk_vcodec_clk *dec_clk = &pm->vdec_clk;
	पूर्णांक i = 0;

	mtk_smi_larb_put(pm->larbvdec);
	क्रम (i = dec_clk->clk_num - 1; i >= 0; i--)
		clk_disable_unprepare(dec_clk->clk_info[i].vcodec_clk);
पूर्ण
