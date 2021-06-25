<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#समावेश <linux/पन.स>
#समावेश <linux/iommu.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/dma-mapping.h>
#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#पूर्ण_अगर

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "komeda_dev.h"

अटल पूर्णांक komeda_रेजिस्टर_show(काष्ठा seq_file *sf, व्योम *x)
अणु
	काष्ठा komeda_dev *mdev = sf->निजी;
	पूर्णांक i;

	seq_माला_दो(sf, "\n====== Komeda register dump =========\n");

	pm_runसमय_get_sync(mdev->dev);

	अगर (mdev->funcs->dump_रेजिस्टर)
		mdev->funcs->dump_रेजिस्टर(mdev, sf);

	क्रम (i = 0; i < mdev->n_pipelines; i++)
		komeda_pipeline_dump_रेजिस्टर(mdev->pipelines[i], sf);

	pm_runसमय_put(mdev->dev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(komeda_रेजिस्टर);

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम komeda_debugfs_init(काष्ठा komeda_dev *mdev)
अणु
	अगर (!debugfs_initialized())
		वापस;

	mdev->debugfs_root = debugfs_create_dir("komeda", शून्य);
	debugfs_create_file("register", 0444, mdev->debugfs_root,
			    mdev, &komeda_रेजिस्टर_fops);
	debugfs_create_x16("err_verbosity", 0664, mdev->debugfs_root,
			   &mdev->err_verbosity);
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार
core_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा komeda_dev *mdev = dev_to_mdev(dev);

	वापस sysfs_emit(buf, "0x%08x\n", mdev->chip.core_id);
पूर्ण
अटल DEVICE_ATTR_RO(core_id);

अटल sमाप_प्रकार
config_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा komeda_dev *mdev = dev_to_mdev(dev);
	काष्ठा komeda_pipeline *pipe = mdev->pipelines[0];
	जोड़ komeda_config_id config_id;
	पूर्णांक i;

	स_रखो(&config_id, 0, माप(config_id));

	config_id.max_line_sz = pipe->layers[0]->hsize_in.end;
	config_id.n_pipelines = mdev->n_pipelines;
	config_id.n_scalers = pipe->n_scalers;
	config_id.n_layers = pipe->n_layers;
	config_id.n_richs = 0;
	क्रम (i = 0; i < pipe->n_layers; i++) अणु
		अगर (pipe->layers[i]->layer_type == KOMEDA_FMT_RICH_LAYER)
			config_id.n_richs++;
	पूर्ण
	वापस sysfs_emit(buf, "0x%08x\n", config_id.value);
पूर्ण
अटल DEVICE_ATTR_RO(config_id);

अटल sमाप_प्रकार
aclk_hz_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा komeda_dev *mdev = dev_to_mdev(dev);

	वापस sysfs_emit(buf, "%lu\n", clk_get_rate(mdev->aclk));
पूर्ण
अटल DEVICE_ATTR_RO(aclk_hz);

अटल काष्ठा attribute *komeda_sysfs_entries[] = अणु
	&dev_attr_core_id.attr,
	&dev_attr_config_id.attr,
	&dev_attr_aclk_hz.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group komeda_sysfs_attr_group = अणु
	.attrs = komeda_sysfs_entries,
पूर्ण;

अटल पूर्णांक komeda_parse_pipe_dt(काष्ठा komeda_pipeline *pipe)
अणु
	काष्ठा device_node *np = pipe->of_node;
	काष्ठा clk *clk;

	clk = of_clk_get_by_name(np, "pxclk");
	अगर (IS_ERR(clk)) अणु
		DRM_ERROR("get pxclk for pipeline %d failed!\n", pipe->id);
		वापस PTR_ERR(clk);
	पूर्ण
	pipe->pxlclk = clk;

	/* क्रमागत ports */
	pipe->of_output_links[0] =
		of_graph_get_remote_node(np, KOMEDA_OF_PORT_OUTPUT, 0);
	pipe->of_output_links[1] =
		of_graph_get_remote_node(np, KOMEDA_OF_PORT_OUTPUT, 1);
	pipe->of_output_port =
		of_graph_get_port_by_id(np, KOMEDA_OF_PORT_OUTPUT);

	pipe->dual_link = pipe->of_output_links[0] && pipe->of_output_links[1];

	वापस 0;
पूर्ण

अटल पूर्णांक komeda_parse_dt(काष्ठा device *dev, काष्ठा komeda_dev *mdev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा device_node *child, *np = dev->of_node;
	काष्ठा komeda_pipeline *pipe;
	u32 pipe_id = U32_MAX;
	पूर्णांक ret = -1;

	mdev->irq  = platक्रमm_get_irq(pdev, 0);
	अगर (mdev->irq < 0) अणु
		DRM_ERROR("could not get IRQ number.\n");
		वापस mdev->irq;
	पूर्ण

	/* Get the optional framebuffer memory resource */
	ret = of_reserved_mem_device_init(dev);
	अगर (ret && ret != -ENODEV)
		वापस ret;

	क्रम_each_available_child_of_node(np, child) अणु
		अगर (of_node_name_eq(child, "pipeline")) अणु
			of_property_पढ़ो_u32(child, "reg", &pipe_id);
			अगर (pipe_id >= mdev->n_pipelines) अणु
				DRM_WARN("Skip the redundant DT node: pipeline-%u.\n",
					 pipe_id);
				जारी;
			पूर्ण
			mdev->pipelines[pipe_id]->of_node = of_node_get(child);
		पूर्ण
	पूर्ण

	क्रम (pipe_id = 0; pipe_id < mdev->n_pipelines; pipe_id++) अणु
		pipe = mdev->pipelines[pipe_id];

		अगर (!pipe->of_node) अणु
			DRM_ERROR("Pipeline-%d doesn't have a DT node.\n",
				  pipe->id);
			वापस -EINVAL;
		पूर्ण
		ret = komeda_parse_pipe_dt(pipe);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा komeda_dev *komeda_dev_create(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	komeda_identअगरy_func komeda_identअगरy;
	काष्ठा komeda_dev *mdev;
	पूर्णांक err = 0;

	komeda_identअगरy = of_device_get_match_data(dev);
	अगर (!komeda_identअगरy)
		वापस ERR_PTR(-ENODEV);

	mdev = devm_kzalloc(dev, माप(*mdev), GFP_KERNEL);
	अगर (!mdev)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&mdev->lock);

	mdev->dev = dev;
	mdev->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mdev->reg_base)) अणु
		DRM_ERROR("Map register space failed.\n");
		err = PTR_ERR(mdev->reg_base);
		mdev->reg_base = शून्य;
		जाओ err_cleanup;
	पूर्ण

	mdev->aclk = devm_clk_get(dev, "aclk");
	अगर (IS_ERR(mdev->aclk)) अणु
		DRM_ERROR("Get engine clk failed.\n");
		err = PTR_ERR(mdev->aclk);
		mdev->aclk = शून्य;
		जाओ err_cleanup;
	पूर्ण

	clk_prepare_enable(mdev->aclk);

	mdev->funcs = komeda_identअगरy(mdev->reg_base, &mdev->chip);
	अगर (!mdev->funcs) अणु
		DRM_ERROR("Failed to identify the HW.\n");
		err = -ENODEV;
		जाओ disable_clk;
	पूर्ण

	DRM_INFO("Found ARM Mali-D%x version r%dp%d\n",
		 MALIDP_CORE_ID_PRODUCT_ID(mdev->chip.core_id),
		 MALIDP_CORE_ID_MAJOR(mdev->chip.core_id),
		 MALIDP_CORE_ID_MINOR(mdev->chip.core_id));

	mdev->funcs->init_क्रमmat_table(mdev);

	err = mdev->funcs->क्रमागत_resources(mdev);
	अगर (err) अणु
		DRM_ERROR("enumerate display resource failed.\n");
		जाओ disable_clk;
	पूर्ण

	err = komeda_parse_dt(dev, mdev);
	अगर (err) अणु
		DRM_ERROR("parse device tree failed.\n");
		जाओ disable_clk;
	पूर्ण

	err = komeda_assemble_pipelines(mdev);
	अगर (err) अणु
		DRM_ERROR("assemble display pipelines failed.\n");
		जाओ disable_clk;
	पूर्ण

	dma_set_max_seg_size(dev, U32_MAX);

	mdev->iommu = iommu_get_करोमुख्य_क्रम_dev(mdev->dev);
	अगर (!mdev->iommu)
		DRM_INFO("continue without IOMMU support!\n");

	clk_disable_unprepare(mdev->aclk);

	err = sysfs_create_group(&dev->kobj, &komeda_sysfs_attr_group);
	अगर (err) अणु
		DRM_ERROR("create sysfs group failed.\n");
		जाओ err_cleanup;
	पूर्ण

	mdev->err_verbosity = KOMEDA_DEV_PRINT_ERR_EVENTS;

#अगर_घोषित CONFIG_DEBUG_FS
	komeda_debugfs_init(mdev);
#पूर्ण_अगर

	वापस mdev;

disable_clk:
	clk_disable_unprepare(mdev->aclk);
err_cleanup:
	komeda_dev_destroy(mdev);
	वापस ERR_PTR(err);
पूर्ण

व्योम komeda_dev_destroy(काष्ठा komeda_dev *mdev)
अणु
	काष्ठा device *dev = mdev->dev;
	स्थिर काष्ठा komeda_dev_funcs *funcs = mdev->funcs;
	पूर्णांक i;

	sysfs_हटाओ_group(&dev->kobj, &komeda_sysfs_attr_group);

#अगर_घोषित CONFIG_DEBUG_FS
	debugfs_हटाओ_recursive(mdev->debugfs_root);
#पूर्ण_अगर

	अगर (mdev->aclk)
		clk_prepare_enable(mdev->aclk);

	क्रम (i = 0; i < mdev->n_pipelines; i++) अणु
		komeda_pipeline_destroy(mdev, mdev->pipelines[i]);
		mdev->pipelines[i] = शून्य;
	पूर्ण

	mdev->n_pipelines = 0;

	of_reserved_mem_device_release(dev);

	अगर (funcs && funcs->cleanup)
		funcs->cleanup(mdev);

	अगर (mdev->reg_base) अणु
		devm_iounmap(dev, mdev->reg_base);
		mdev->reg_base = शून्य;
	पूर्ण

	अगर (mdev->aclk) अणु
		clk_disable_unprepare(mdev->aclk);
		devm_clk_put(dev, mdev->aclk);
		mdev->aclk = शून्य;
	पूर्ण

	devm_kमुक्त(dev, mdev);
पूर्ण

पूर्णांक komeda_dev_resume(काष्ठा komeda_dev *mdev)
अणु
	clk_prepare_enable(mdev->aclk);

	mdev->funcs->enable_irq(mdev);

	अगर (mdev->iommu && mdev->funcs->connect_iommu)
		अगर (mdev->funcs->connect_iommu(mdev))
			DRM_ERROR("connect iommu failed.\n");

	वापस 0;
पूर्ण

पूर्णांक komeda_dev_suspend(काष्ठा komeda_dev *mdev)
अणु
	अगर (mdev->iommu && mdev->funcs->disconnect_iommu)
		अगर (mdev->funcs->disconnect_iommu(mdev))
			DRM_ERROR("disconnect iommu failed.\n");

	mdev->funcs->disable_irq(mdev);

	clk_disable_unprepare(mdev->aclk);

	वापस 0;
पूर्ण
