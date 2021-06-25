<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015-2016 MediaTek Inc.
 * Author: Houदीर्घ Wei <houदीर्घ.wei@mediatek.com>
 *         Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/workqueue.h>
#समावेश <soc/mediatek/smi.h>

#समावेश "mtk_mdp_core.h"
#समावेश "mtk_mdp_m2m.h"
#समावेश "mtk_vpu.h"

/* MDP debug log level (0-3). 3 shows all the logs. */
पूर्णांक mtk_mdp_dbg_level;
EXPORT_SYMBOL(mtk_mdp_dbg_level);

module_param(mtk_mdp_dbg_level, पूर्णांक, 0644);

अटल स्थिर काष्ठा of_device_id mtk_mdp_comp_dt_ids[] = अणु
	अणु
		.compatible = "mediatek,mt8173-mdp-rdma",
		.data = (व्योम *)MTK_MDP_RDMA
	पूर्ण, अणु
		.compatible = "mediatek,mt8173-mdp-rsz",
		.data = (व्योम *)MTK_MDP_RSZ
	पूर्ण, अणु
		.compatible = "mediatek,mt8173-mdp-wdma",
		.data = (व्योम *)MTK_MDP_WDMA
	पूर्ण, अणु
		.compatible = "mediatek,mt8173-mdp-wrot",
		.data = (व्योम *)MTK_MDP_WROT
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_mdp_of_ids[] = अणु
	अणु .compatible = "mediatek,mt8173-mdp", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_mdp_of_ids);

अटल व्योम mtk_mdp_घड़ी_on(काष्ठा mtk_mdp_dev *mdp)
अणु
	काष्ठा device *dev = &mdp->pdev->dev;
	काष्ठा mtk_mdp_comp *comp_node;

	list_क्रम_each_entry(comp_node, &mdp->comp_list, node)
		mtk_mdp_comp_घड़ी_on(dev, comp_node);
पूर्ण

अटल व्योम mtk_mdp_घड़ी_off(काष्ठा mtk_mdp_dev *mdp)
अणु
	काष्ठा device *dev = &mdp->pdev->dev;
	काष्ठा mtk_mdp_comp *comp_node;

	list_क्रम_each_entry(comp_node, &mdp->comp_list, node)
		mtk_mdp_comp_घड़ी_off(dev, comp_node);
पूर्ण

अटल व्योम mtk_mdp_wdt_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mtk_mdp_dev *mdp =
			container_of(work, काष्ठा mtk_mdp_dev, wdt_work);
	काष्ठा mtk_mdp_ctx *ctx;

	mtk_mdp_err("Watchdog timeout");

	list_क्रम_each_entry(ctx, &mdp->ctx_list, list) अणु
		mtk_mdp_dbg(0, "[%d] Change as state error", ctx->id);
		mtk_mdp_ctx_state_lock_set(ctx, MTK_MDP_CTX_ERROR);
	पूर्ण
पूर्ण

अटल व्योम mtk_mdp_reset_handler(व्योम *priv)
अणु
	काष्ठा mtk_mdp_dev *mdp = priv;

	queue_work(mdp->wdt_wq, &mdp->wdt_work);
पूर्ण

व्योम mtk_mdp_रेजिस्टर_component(काष्ठा mtk_mdp_dev *mdp,
				काष्ठा mtk_mdp_comp *comp)
अणु
	list_add(&comp->node, &mdp->comp_list);
पूर्ण

व्योम mtk_mdp_unरेजिस्टर_component(काष्ठा mtk_mdp_dev *mdp,
				  काष्ठा mtk_mdp_comp *comp)
अणु
	list_del(&comp->node);
पूर्ण

अटल पूर्णांक mtk_mdp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_mdp_dev *mdp;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node, *parent;
	काष्ठा mtk_mdp_comp *comp, *comp_temp;
	पूर्णांक ret = 0;

	mdp = devm_kzalloc(dev, माप(*mdp), GFP_KERNEL);
	अगर (!mdp)
		वापस -ENOMEM;

	mdp->id = pdev->id;
	mdp->pdev = pdev;
	INIT_LIST_HEAD(&mdp->comp_list);
	INIT_LIST_HEAD(&mdp->ctx_list);

	mutex_init(&mdp->lock);
	mutex_init(&mdp->vpulock);

	/* Old dts had the components as child nodes */
	node = of_get_next_child(dev->of_node, शून्य);
	अगर (node) अणु
		of_node_put(node);
		parent = dev->of_node;
		dev_warn(dev, "device tree is out of date\n");
	पूर्ण अन्यथा अणु
		parent = dev->of_node->parent;
	पूर्ण

	/* Iterate over sibling MDP function blocks */
	क्रम_each_child_of_node(parent, node) अणु
		स्थिर काष्ठा of_device_id *of_id;
		क्रमागत mtk_mdp_comp_type comp_type;

		of_id = of_match_node(mtk_mdp_comp_dt_ids, node);
		अगर (!of_id)
			जारी;

		अगर (!of_device_is_available(node)) अणु
			dev_err(dev, "Skipping disabled component %pOF\n",
				node);
			जारी;
		पूर्ण

		comp_type = (क्रमागत mtk_mdp_comp_type)of_id->data;

		comp = devm_kzalloc(dev, माप(*comp), GFP_KERNEL);
		अगर (!comp) अणु
			ret = -ENOMEM;
			of_node_put(node);
			जाओ err_comp;
		पूर्ण

		ret = mtk_mdp_comp_init(dev, node, comp, comp_type);
		अगर (ret) अणु
			of_node_put(node);
			जाओ err_comp;
		पूर्ण

		mtk_mdp_रेजिस्टर_component(mdp, comp);
	पूर्ण

	mdp->job_wq = create_singlethपढ़ो_workqueue(MTK_MDP_MODULE_NAME);
	अगर (!mdp->job_wq) अणु
		dev_err(&pdev->dev, "unable to alloc job workqueue\n");
		ret = -ENOMEM;
		जाओ err_alloc_job_wq;
	पूर्ण

	mdp->wdt_wq = create_singlethपढ़ो_workqueue("mdp_wdt_wq");
	अगर (!mdp->wdt_wq) अणु
		dev_err(&pdev->dev, "unable to alloc wdt workqueue\n");
		ret = -ENOMEM;
		जाओ err_alloc_wdt_wq;
	पूर्ण
	INIT_WORK(&mdp->wdt_work, mtk_mdp_wdt_worker);

	ret = v4l2_device_रेजिस्टर(dev, &mdp->v4l2_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register v4l2 device\n");
		ret = -EINVAL;
		जाओ err_dev_रेजिस्टर;
	पूर्ण

	ret = mtk_mdp_रेजिस्टर_m2m_device(mdp);
	अगर (ret) अणु
		v4l2_err(&mdp->v4l2_dev, "Failed to init mem2mem device\n");
		जाओ err_m2m_रेजिस्टर;
	पूर्ण

	mdp->vpu_dev = vpu_get_plat_device(pdev);
	ret = vpu_wdt_reg_handler(mdp->vpu_dev, mtk_mdp_reset_handler, mdp,
				  VPU_RST_MDP);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register reset handler\n");
		जाओ err_m2m_रेजिस्टर;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mdp);

	ret = vb2_dma_contig_set_max_seg_size(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to set vb2 dma mag seg size\n");
		जाओ err_m2m_रेजिस्टर;
	पूर्ण

	pm_runसमय_enable(dev);
	dev_dbg(dev, "mdp-%d registered successfully\n", mdp->id);

	वापस 0;

err_m2m_रेजिस्टर:
	v4l2_device_unरेजिस्टर(&mdp->v4l2_dev);

err_dev_रेजिस्टर:
	destroy_workqueue(mdp->wdt_wq);

err_alloc_wdt_wq:
	destroy_workqueue(mdp->job_wq);

err_alloc_job_wq:

err_comp:
	list_क्रम_each_entry_safe(comp, comp_temp, &mdp->comp_list, node) अणु
		mtk_mdp_unरेजिस्टर_component(mdp, comp);
		mtk_mdp_comp_deinit(dev, comp);
	पूर्ण

	dev_dbg(dev, "err %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_mdp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_mdp_dev *mdp = platक्रमm_get_drvdata(pdev);
	काष्ठा mtk_mdp_comp *comp, *comp_temp;

	pm_runसमय_disable(&pdev->dev);
	vb2_dma_contig_clear_max_seg_size(&pdev->dev);
	mtk_mdp_unरेजिस्टर_m2m_device(mdp);
	v4l2_device_unरेजिस्टर(&mdp->v4l2_dev);

	flush_workqueue(mdp->wdt_wq);
	destroy_workqueue(mdp->wdt_wq);

	flush_workqueue(mdp->job_wq);
	destroy_workqueue(mdp->job_wq);

	list_क्रम_each_entry_safe(comp, comp_temp, &mdp->comp_list, node) अणु
		mtk_mdp_unरेजिस्टर_component(mdp, comp);
		mtk_mdp_comp_deinit(&pdev->dev, comp);
	पूर्ण

	dev_dbg(&pdev->dev, "%s driver unloaded\n", pdev->name);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_mdp_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_mdp_dev *mdp = dev_get_drvdata(dev);

	mtk_mdp_घड़ी_off(mdp);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_mdp_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_mdp_dev *mdp = dev_get_drvdata(dev);

	mtk_mdp_घड़ी_on(mdp);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_mdp_suspend(काष्ठा device *dev)
अणु
	अगर (pm_runसमय_suspended(dev))
		वापस 0;

	वापस mtk_mdp_pm_suspend(dev);
पूर्ण

अटल पूर्णांक __maybe_unused mtk_mdp_resume(काष्ठा device *dev)
अणु
	अगर (pm_runसमय_suspended(dev))
		वापस 0;

	वापस mtk_mdp_pm_resume(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mtk_mdp_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mtk_mdp_suspend, mtk_mdp_resume)
	SET_RUNTIME_PM_OPS(mtk_mdp_pm_suspend, mtk_mdp_pm_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver mtk_mdp_driver = अणु
	.probe		= mtk_mdp_probe,
	.हटाओ		= mtk_mdp_हटाओ,
	.driver = अणु
		.name	= MTK_MDP_MODULE_NAME,
		.pm	= &mtk_mdp_pm_ops,
		.of_match_table = mtk_mdp_of_ids,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(mtk_mdp_driver);

MODULE_AUTHOR("Houlong Wei <houlong.wei@mediatek.com>");
MODULE_DESCRIPTION("Mediatek image processor driver");
MODULE_LICENSE("GPL v2");
