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

#समावेश "mtk_vcodec_enc_pm.h"
#समावेश "mtk_vcodec_util.h"

पूर्णांक mtk_vcodec_init_enc_pm(काष्ठा mtk_vcodec_dev *mtkdev)
अणु
	काष्ठा device_node *node;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा mtk_vcodec_pm *pm;
	काष्ठा mtk_vcodec_clk *enc_clk;
	काष्ठा mtk_vcodec_clk_info *clk_info;
	पूर्णांक ret = 0, i = 0;
	काष्ठा device *dev;

	pdev = mtkdev->plat_dev;
	pm = &mtkdev->pm;
	स_रखो(pm, 0, माप(काष्ठा mtk_vcodec_pm));
	pm->mtkdev = mtkdev;
	pm->dev = &pdev->dev;
	dev = &pdev->dev;
	enc_clk = &pm->venc_clk;

	node = of_parse_phandle(dev->of_node, "mediatek,larb", 0);
	अगर (!node) अणु
		mtk_v4l2_err("no mediatek,larb found");
		वापस -ENODEV;
	पूर्ण
	pdev = of_find_device_by_node(node);
	of_node_put(node);
	अगर (!pdev) अणु
		mtk_v4l2_err("no mediatek,larb device found");
		वापस -ENODEV;
	पूर्ण
	pm->larbvenc = &pdev->dev;
	pdev = mtkdev->plat_dev;
	pm->dev = &pdev->dev;

	enc_clk->clk_num = of_property_count_strings(pdev->dev.of_node,
		"clock-names");
	अगर (enc_clk->clk_num > 0) अणु
		enc_clk->clk_info = devm_kसुस्मृति(&pdev->dev,
			enc_clk->clk_num, माप(*clk_info),
			GFP_KERNEL);
		अगर (!enc_clk->clk_info) अणु
			ret = -ENOMEM;
			जाओ put_larbvenc;
		पूर्ण
	पूर्ण अन्यथा अणु
		mtk_v4l2_err("Failed to get venc clock count");
		ret = -EINVAL;
		जाओ put_larbvenc;
	पूर्ण

	क्रम (i = 0; i < enc_clk->clk_num; i++) अणु
		clk_info = &enc_clk->clk_info[i];
		ret = of_property_पढ़ो_string_index(pdev->dev.of_node,
			"clock-names", i, &clk_info->clk_name);
		अगर (ret) अणु
			mtk_v4l2_err("venc failed to get clk name %d", i);
			जाओ put_larbvenc;
		पूर्ण
		clk_info->vcodec_clk = devm_clk_get(&pdev->dev,
			clk_info->clk_name);
		अगर (IS_ERR(clk_info->vcodec_clk)) अणु
			mtk_v4l2_err("venc devm_clk_get (%d)%s fail", i,
				clk_info->clk_name);
			ret = PTR_ERR(clk_info->vcodec_clk);
			जाओ put_larbvenc;
		पूर्ण
	पूर्ण

	वापस 0;

put_larbvenc:
	put_device(pm->larbvenc);
	वापस ret;
पूर्ण

व्योम mtk_vcodec_release_enc_pm(काष्ठा mtk_vcodec_dev *mtkdev)
अणु
	pm_runसमय_disable(mtkdev->pm.dev);
	put_device(mtkdev->pm.larbvenc);
पूर्ण


व्योम mtk_vcodec_enc_घड़ी_on(काष्ठा mtk_vcodec_pm *pm)
अणु
	काष्ठा mtk_vcodec_clk *enc_clk = &pm->venc_clk;
	पूर्णांक ret, i = 0;

	क्रम (i = 0; i < enc_clk->clk_num; i++) अणु
		ret = clk_prepare_enable(enc_clk->clk_info[i].vcodec_clk);
		अगर (ret) अणु
			mtk_v4l2_err("venc clk_prepare_enable %d %s fail %d", i,
				enc_clk->clk_info[i].clk_name, ret);
			जाओ clkerr;
		पूर्ण
	पूर्ण

	ret = mtk_smi_larb_get(pm->larbvenc);
	अगर (ret) अणु
		mtk_v4l2_err("mtk_smi_larb_get larb3 fail %d", ret);
		जाओ clkerr;
	पूर्ण
	वापस;

clkerr:
	क्रम (i -= 1; i >= 0; i--)
		clk_disable_unprepare(enc_clk->clk_info[i].vcodec_clk);
पूर्ण

व्योम mtk_vcodec_enc_घड़ी_off(काष्ठा mtk_vcodec_pm *pm)
अणु
	काष्ठा mtk_vcodec_clk *enc_clk = &pm->venc_clk;
	पूर्णांक i = 0;

	mtk_smi_larb_put(pm->larbvenc);
	क्रम (i = enc_clk->clk_num - 1; i >= 0; i--)
		clk_disable_unprepare(enc_clk->clk_info[i].vcodec_clk);
पूर्ण
