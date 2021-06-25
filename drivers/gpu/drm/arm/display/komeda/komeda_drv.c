<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/component.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <drm/drm_of.h>
#समावेश "komeda_dev.h"
#समावेश "komeda_kms.h"

काष्ठा komeda_drv अणु
	काष्ठा komeda_dev *mdev;
	काष्ठा komeda_kms_dev *kms;
पूर्ण;

काष्ठा komeda_dev *dev_to_mdev(काष्ठा device *dev)
अणु
	काष्ठा komeda_drv *mdrv = dev_get_drvdata(dev);

	वापस mdrv ? mdrv->mdev : शून्य;
पूर्ण

अटल व्योम komeda_unbind(काष्ठा device *dev)
अणु
	काष्ठा komeda_drv *mdrv = dev_get_drvdata(dev);

	अगर (!mdrv)
		वापस;

	komeda_kms_detach(mdrv->kms);

	अगर (pm_runसमय_enabled(dev))
		pm_runसमय_disable(dev);
	अन्यथा
		komeda_dev_suspend(mdrv->mdev);

	komeda_dev_destroy(mdrv->mdev);

	dev_set_drvdata(dev, शून्य);
	devm_kमुक्त(dev, mdrv);
पूर्ण

अटल पूर्णांक komeda_bind(काष्ठा device *dev)
अणु
	काष्ठा komeda_drv *mdrv;
	पूर्णांक err;

	mdrv = devm_kzalloc(dev, माप(*mdrv), GFP_KERNEL);
	अगर (!mdrv)
		वापस -ENOMEM;

	mdrv->mdev = komeda_dev_create(dev);
	अगर (IS_ERR(mdrv->mdev)) अणु
		err = PTR_ERR(mdrv->mdev);
		जाओ मुक्त_mdrv;
	पूर्ण

	pm_runसमय_enable(dev);
	अगर (!pm_runसमय_enabled(dev))
		komeda_dev_resume(mdrv->mdev);

	mdrv->kms = komeda_kms_attach(mdrv->mdev);
	अगर (IS_ERR(mdrv->kms)) अणु
		err = PTR_ERR(mdrv->kms);
		जाओ destroy_mdev;
	पूर्ण

	dev_set_drvdata(dev, mdrv);

	वापस 0;

destroy_mdev:
	अगर (pm_runसमय_enabled(dev))
		pm_runसमय_disable(dev);
	अन्यथा
		komeda_dev_suspend(mdrv->mdev);

	komeda_dev_destroy(mdrv->mdev);

मुक्त_mdrv:
	devm_kमुक्त(dev, mdrv);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा component_master_ops komeda_master_ops = अणु
	.bind	= komeda_bind,
	.unbind	= komeda_unbind,
पूर्ण;

अटल पूर्णांक compare_of(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev->of_node == data;
पूर्ण

अटल व्योम komeda_add_slave(काष्ठा device *master,
			     काष्ठा component_match **match,
			     काष्ठा device_node *np,
			     u32 port, u32 endpoपूर्णांक)
अणु
	काष्ठा device_node *remote;

	remote = of_graph_get_remote_node(np, port, endpoपूर्णांक);
	अगर (remote) अणु
		drm_of_component_match_add(master, match, compare_of, remote);
		of_node_put(remote);
	पूर्ण
पूर्ण

अटल पूर्णांक komeda_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा component_match *match = शून्य;
	काष्ठा device_node *child;

	अगर (!dev->of_node)
		वापस -ENODEV;

	क्रम_each_available_child_of_node(dev->of_node, child) अणु
		अगर (of_node_cmp(child->name, "pipeline") != 0)
			जारी;

		/* add connector */
		komeda_add_slave(dev, &match, child, KOMEDA_OF_PORT_OUTPUT, 0);
		komeda_add_slave(dev, &match, child, KOMEDA_OF_PORT_OUTPUT, 1);
	पूर्ण

	वापस component_master_add_with_match(dev, &komeda_master_ops, match);
पूर्ण

अटल पूर्णांक komeda_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_master_del(&pdev->dev, &komeda_master_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id komeda_of_match[] = अणु
	अणु .compatible = "arm,mali-d71", .data = d71_identअगरy, पूर्ण,
	अणु .compatible = "arm,mali-d32", .data = d71_identअगरy, पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, komeda_of_match);

अटल पूर्णांक __maybe_unused komeda_rt_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा komeda_drv *mdrv = dev_get_drvdata(dev);

	वापस komeda_dev_suspend(mdrv->mdev);
पूर्ण

अटल पूर्णांक __maybe_unused komeda_rt_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा komeda_drv *mdrv = dev_get_drvdata(dev);

	वापस komeda_dev_resume(mdrv->mdev);
पूर्ण

अटल पूर्णांक __maybe_unused komeda_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा komeda_drv *mdrv = dev_get_drvdata(dev);
	पूर्णांक res;

	res = drm_mode_config_helper_suspend(&mdrv->kms->base);

	अगर (!pm_runसमय_status_suspended(dev))
		komeda_dev_suspend(mdrv->mdev);

	वापस res;
पूर्ण

अटल पूर्णांक __maybe_unused komeda_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा komeda_drv *mdrv = dev_get_drvdata(dev);

	अगर (!pm_runसमय_status_suspended(dev))
		komeda_dev_resume(mdrv->mdev);

	वापस drm_mode_config_helper_resume(&mdrv->kms->base);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops komeda_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(komeda_pm_suspend, komeda_pm_resume)
	SET_RUNTIME_PM_OPS(komeda_rt_pm_suspend, komeda_rt_pm_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver komeda_platक्रमm_driver = अणु
	.probe	= komeda_platक्रमm_probe,
	.हटाओ	= komeda_platक्रमm_हटाओ,
	.driver	= अणु
		.name = "komeda",
		.of_match_table	= komeda_of_match,
		.pm = &komeda_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(komeda_platक्रमm_driver);

MODULE_AUTHOR("James.Qian.Wang <james.qian.wang@arm.com>");
MODULE_DESCRIPTION("Komeda KMS driver");
MODULE_LICENSE("GPL v2");
