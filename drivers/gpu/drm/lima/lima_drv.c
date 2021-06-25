<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_prime.h>
#समावेश <drm/lima_drm.h>

#समावेश "lima_device.h"
#समावेश "lima_drv.h"
#समावेश "lima_gem.h"
#समावेश "lima_vm.h"

पूर्णांक lima_sched_समयout_ms;
uपूर्णांक lima_heap_init_nr_pages = 8;
uपूर्णांक lima_max_error_tasks;
uपूर्णांक lima_job_hang_limit;

MODULE_PARM_DESC(sched_समयout_ms, "task run timeout in ms");
module_param_named(sched_समयout_ms, lima_sched_समयout_ms, पूर्णांक, 0444);

MODULE_PARM_DESC(heap_init_nr_pages, "heap buffer init number of pages");
module_param_named(heap_init_nr_pages, lima_heap_init_nr_pages, uपूर्णांक, 0444);

MODULE_PARM_DESC(max_error_tasks, "max number of error tasks to save");
module_param_named(max_error_tasks, lima_max_error_tasks, uपूर्णांक, 0644);

MODULE_PARM_DESC(job_hang_limit, "number of times to allow a job to hang before dropping it (default 0)");
module_param_named(job_hang_limit, lima_job_hang_limit, uपूर्णांक, 0444);

अटल पूर्णांक lima_ioctl_get_param(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file)
अणु
	काष्ठा drm_lima_get_param *args = data;
	काष्ठा lima_device *ldev = to_lima_dev(dev);

	अगर (args->pad)
		वापस -EINVAL;

	चयन (args->param) अणु
	हाल DRM_LIMA_PARAM_GPU_ID:
		चयन (ldev->id) अणु
		हाल lima_gpu_mali400:
			args->value = DRM_LIMA_PARAM_GPU_ID_MALI400;
			अवरोध;
		हाल lima_gpu_mali450:
			args->value = DRM_LIMA_PARAM_GPU_ID_MALI450;
			अवरोध;
		शेष:
			args->value = DRM_LIMA_PARAM_GPU_ID_UNKNOWN;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल DRM_LIMA_PARAM_NUM_PP:
		args->value = ldev->pipe[lima_pipe_pp].num_processor;
		अवरोध;

	हाल DRM_LIMA_PARAM_GP_VERSION:
		args->value = ldev->gp_version;
		अवरोध;

	हाल DRM_LIMA_PARAM_PP_VERSION:
		args->value = ldev->pp_version;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lima_ioctl_gem_create(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file)
अणु
	काष्ठा drm_lima_gem_create *args = data;

	अगर (args->pad)
		वापस -EINVAL;

	अगर (args->flags & ~(LIMA_BO_FLAG_HEAP))
		वापस -EINVAL;

	अगर (args->size == 0)
		वापस -EINVAL;

	वापस lima_gem_create_handle(dev, file, args->size, args->flags, &args->handle);
पूर्ण

अटल पूर्णांक lima_ioctl_gem_info(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file)
अणु
	काष्ठा drm_lima_gem_info *args = data;

	वापस lima_gem_get_info(file, args->handle, &args->va, &args->offset);
पूर्ण

अटल पूर्णांक lima_ioctl_gem_submit(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file)
अणु
	काष्ठा drm_lima_gem_submit *args = data;
	काष्ठा lima_device *ldev = to_lima_dev(dev);
	काष्ठा lima_drm_priv *priv = file->driver_priv;
	काष्ठा drm_lima_gem_submit_bo *bos;
	काष्ठा lima_sched_pipe *pipe;
	काष्ठा lima_sched_task *task;
	काष्ठा lima_ctx *ctx;
	काष्ठा lima_submit submit = अणु0पूर्ण;
	माप_प्रकार size;
	पूर्णांक err = 0;

	अगर (args->pipe >= lima_pipe_num || args->nr_bos == 0)
		वापस -EINVAL;

	अगर (args->flags & ~(LIMA_SUBMIT_FLAG_EXPLICIT_FENCE))
		वापस -EINVAL;

	pipe = ldev->pipe + args->pipe;
	अगर (args->frame_size != pipe->frame_size)
		वापस -EINVAL;

	bos = kvसुस्मृति(args->nr_bos, माप(*submit.bos) + माप(*submit.lbos), GFP_KERNEL);
	अगर (!bos)
		वापस -ENOMEM;

	size = args->nr_bos * माप(*submit.bos);
	अगर (copy_from_user(bos, u64_to_user_ptr(args->bos), size)) अणु
		err = -EFAULT;
		जाओ out0;
	पूर्ण

	task = kmem_cache_zalloc(pipe->task_slab, GFP_KERNEL);
	अगर (!task) अणु
		err = -ENOMEM;
		जाओ out0;
	पूर्ण

	task->frame = task + 1;
	अगर (copy_from_user(task->frame, u64_to_user_ptr(args->frame), args->frame_size)) अणु
		err = -EFAULT;
		जाओ out1;
	पूर्ण

	err = pipe->task_validate(pipe, task);
	अगर (err)
		जाओ out1;

	ctx = lima_ctx_get(&priv->ctx_mgr, args->ctx);
	अगर (!ctx) अणु
		err = -ENOENT;
		जाओ out1;
	पूर्ण

	submit.pipe = args->pipe;
	submit.bos = bos;
	submit.lbos = (व्योम *)bos + size;
	submit.nr_bos = args->nr_bos;
	submit.task = task;
	submit.ctx = ctx;
	submit.flags = args->flags;
	submit.in_sync[0] = args->in_sync[0];
	submit.in_sync[1] = args->in_sync[1];
	submit.out_sync = args->out_sync;

	err = lima_gem_submit(file, &submit);

	lima_ctx_put(ctx);
out1:
	अगर (err)
		kmem_cache_मुक्त(pipe->task_slab, task);
out0:
	kvमुक्त(bos);
	वापस err;
पूर्ण

अटल पूर्णांक lima_ioctl_gem_रुको(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file)
अणु
	काष्ठा drm_lima_gem_रुको *args = data;

	अगर (args->op & ~(LIMA_GEM_WAIT_READ|LIMA_GEM_WAIT_WRITE))
		वापस -EINVAL;

	वापस lima_gem_रुको(file, args->handle, args->op, args->समयout_ns);
पूर्ण

अटल पूर्णांक lima_ioctl_ctx_create(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file)
अणु
	काष्ठा drm_lima_ctx_create *args = data;
	काष्ठा lima_drm_priv *priv = file->driver_priv;
	काष्ठा lima_device *ldev = to_lima_dev(dev);

	अगर (args->_pad)
		वापस -EINVAL;

	वापस lima_ctx_create(ldev, &priv->ctx_mgr, &args->id);
पूर्ण

अटल पूर्णांक lima_ioctl_ctx_मुक्त(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file)
अणु
	काष्ठा drm_lima_ctx_create *args = data;
	काष्ठा lima_drm_priv *priv = file->driver_priv;

	अगर (args->_pad)
		वापस -EINVAL;

	वापस lima_ctx_मुक्त(&priv->ctx_mgr, args->id);
पूर्ण

अटल पूर्णांक lima_drm_driver_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	पूर्णांक err;
	काष्ठा lima_drm_priv *priv;
	काष्ठा lima_device *ldev = to_lima_dev(dev);

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->vm = lima_vm_create(ldev);
	अगर (!priv->vm) अणु
		err = -ENOMEM;
		जाओ err_out0;
	पूर्ण

	lima_ctx_mgr_init(&priv->ctx_mgr);

	file->driver_priv = priv;
	वापस 0;

err_out0:
	kमुक्त(priv);
	वापस err;
पूर्ण

अटल व्योम lima_drm_driver_postबंद(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा lima_drm_priv *priv = file->driver_priv;

	lima_ctx_mgr_fini(&priv->ctx_mgr);
	lima_vm_put(priv->vm);
	kमुक्त(priv);
पूर्ण

अटल स्थिर काष्ठा drm_ioctl_desc lima_drm_driver_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(LIMA_GET_PARAM, lima_ioctl_get_param, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(LIMA_GEM_CREATE, lima_ioctl_gem_create, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(LIMA_GEM_INFO, lima_ioctl_gem_info, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(LIMA_GEM_SUBMIT, lima_ioctl_gem_submit, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(LIMA_GEM_WAIT, lima_ioctl_gem_रुको, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(LIMA_CTX_CREATE, lima_ioctl_ctx_create, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(LIMA_CTX_FREE, lima_ioctl_ctx_मुक्त, DRM_RENDER_ALLOW),
पूर्ण;

DEFINE_DRM_GEM_FOPS(lima_drm_driver_fops);

/*
 * Changelog:
 *
 * - 1.1.0 - add heap buffer support
 */

अटल स्थिर काष्ठा drm_driver lima_drm_driver = अणु
	.driver_features    = DRIVER_RENDER | DRIVER_GEM | DRIVER_SYNCOBJ,
	.खोलो               = lima_drm_driver_खोलो,
	.postबंद          = lima_drm_driver_postबंद,
	.ioctls             = lima_drm_driver_ioctls,
	.num_ioctls         = ARRAY_SIZE(lima_drm_driver_ioctls),
	.fops               = &lima_drm_driver_fops,
	.name               = "lima",
	.desc               = "lima DRM",
	.date               = "20191231",
	.major              = 1,
	.minor              = 1,
	.patchlevel         = 0,

	.gem_create_object  = lima_gem_create_object,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_import_sg_table = drm_gem_shmem_prime_import_sg_table,
	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.gem_prime_mmap = drm_gem_prime_mmap,
पूर्ण;

काष्ठा lima_block_पढ़ोer अणु
	व्योम *dst;
	माप_प्रकार base;
	माप_प्रकार count;
	माप_प्रकार off;
	sमाप_प्रकार पढ़ो;
पूर्ण;

अटल bool lima_पढ़ो_block(काष्ठा lima_block_पढ़ोer *पढ़ोer,
			    व्योम *src, माप_प्रकार src_size)
अणु
	माप_प्रकार max_off = पढ़ोer->base + src_size;

	अगर (पढ़ोer->off < max_off) अणु
		माप_प्रकार size = min_t(माप_प्रकार, max_off - पढ़ोer->off,
				    पढ़ोer->count);

		स_नकल(पढ़ोer->dst, src + (पढ़ोer->off - पढ़ोer->base), size);

		पढ़ोer->dst += size;
		पढ़ोer->off += size;
		पढ़ोer->पढ़ो += size;
		पढ़ोer->count -= size;
	पूर्ण

	पढ़ोer->base = max_off;

	वापस !!पढ़ोer->count;
पूर्ण

अटल sमाप_प्रकार lima_error_state_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				     काष्ठा bin_attribute *attr, अक्षर *buf,
				     loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा lima_device *ldev = dev_get_drvdata(dev);
	काष्ठा lima_sched_error_task *et;
	काष्ठा lima_block_पढ़ोer पढ़ोer = अणु
		.dst = buf,
		.count = count,
		.off = off,
	पूर्ण;

	mutex_lock(&ldev->error_task_list_lock);

	अगर (lima_पढ़ो_block(&पढ़ोer, &ldev->dump, माप(ldev->dump))) अणु
		list_क्रम_each_entry(et, &ldev->error_task_list, list) अणु
			अगर (!lima_पढ़ो_block(&पढ़ोer, et->data, et->size))
				अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&ldev->error_task_list_lock);
	वापस पढ़ोer.पढ़ो;
पूर्ण

अटल sमाप_प्रकार lima_error_state_ग_लिखो(काष्ठा file *file, काष्ठा kobject *kobj,
				      काष्ठा bin_attribute *attr, अक्षर *buf,
				      loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा lima_device *ldev = dev_get_drvdata(dev);
	काष्ठा lima_sched_error_task *et, *पंचांगp;

	mutex_lock(&ldev->error_task_list_lock);

	list_क्रम_each_entry_safe(et, पंचांगp, &ldev->error_task_list, list) अणु
		list_del(&et->list);
		kvमुक्त(et);
	पूर्ण

	ldev->dump.size = 0;
	ldev->dump.num_tasks = 0;

	mutex_unlock(&ldev->error_task_list_lock);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा bin_attribute lima_error_state_attr = अणु
	.attr.name = "error",
	.attr.mode = 0600,
	.size = 0,
	.पढ़ो = lima_error_state_पढ़ो,
	.ग_लिखो = lima_error_state_ग_लिखो,
पूर्ण;

अटल पूर्णांक lima_pdev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lima_device *ldev;
	काष्ठा drm_device *ddev;
	पूर्णांक err;

	err = lima_sched_slab_init();
	अगर (err)
		वापस err;

	ldev = devm_kzalloc(&pdev->dev, माप(*ldev), GFP_KERNEL);
	अगर (!ldev) अणु
		err = -ENOMEM;
		जाओ err_out0;
	पूर्ण

	ldev->dev = &pdev->dev;
	ldev->id = (क्रमागत lima_gpu_id)of_device_get_match_data(&pdev->dev);

	platक्रमm_set_drvdata(pdev, ldev);

	/* Allocate and initialize the DRM device. */
	ddev = drm_dev_alloc(&lima_drm_driver, &pdev->dev);
	अगर (IS_ERR(ddev))
		वापस PTR_ERR(ddev);

	ddev->dev_निजी = ldev;
	ldev->ddev = ddev;

	err = lima_device_init(ldev);
	अगर (err)
		जाओ err_out1;

	err = lima_devfreq_init(ldev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Fatal error during devfreq init\n");
		जाओ err_out2;
	पूर्ण

	pm_runसमय_set_active(ldev->dev);
	pm_runसमय_mark_last_busy(ldev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(ldev->dev, 200);
	pm_runसमय_use_स्वतःsuspend(ldev->dev);
	pm_runसमय_enable(ldev->dev);

	/*
	 * Register the DRM device with the core and the connectors with
	 * sysfs.
	 */
	err = drm_dev_रेजिस्टर(ddev, 0);
	अगर (err < 0)
		जाओ err_out3;

	अगर (sysfs_create_bin_file(&ldev->dev->kobj, &lima_error_state_attr))
		dev_warn(ldev->dev, "fail to create error state sysfs\n");

	वापस 0;

err_out3:
	pm_runसमय_disable(ldev->dev);
	lima_devfreq_fini(ldev);
err_out2:
	lima_device_fini(ldev);
err_out1:
	drm_dev_put(ddev);
err_out0:
	lima_sched_slab_fini();
	वापस err;
पूर्ण

अटल पूर्णांक lima_pdev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lima_device *ldev = platक्रमm_get_drvdata(pdev);
	काष्ठा drm_device *ddev = ldev->ddev;

	sysfs_हटाओ_bin_file(&ldev->dev->kobj, &lima_error_state_attr);

	drm_dev_unरेजिस्टर(ddev);

	/* stop स्वतःsuspend to make sure device is in active state */
	pm_runसमय_set_स्वतःsuspend_delay(ldev->dev, -1);
	pm_runसमय_disable(ldev->dev);

	lima_devfreq_fini(ldev);
	lima_device_fini(ldev);

	drm_dev_put(ddev);
	lima_sched_slab_fini();
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dt_match[] = अणु
	अणु .compatible = "arm,mali-400", .data = (व्योम *)lima_gpu_mali400 पूर्ण,
	अणु .compatible = "arm,mali-450", .data = (व्योम *)lima_gpu_mali450 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dt_match);

अटल स्थिर काष्ठा dev_pm_ops lima_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend, pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(lima_device_suspend, lima_device_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver lima_platक्रमm_driver = अणु
	.probe      = lima_pdev_probe,
	.हटाओ     = lima_pdev_हटाओ,
	.driver     = अणु
		.name   = "lima",
		.pm	= &lima_pm_ops,
		.of_match_table = dt_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(lima_platक्रमm_driver);

MODULE_AUTHOR("Lima Project Developers");
MODULE_DESCRIPTION("Lima DRM Driver");
MODULE_LICENSE("GPL v2");
