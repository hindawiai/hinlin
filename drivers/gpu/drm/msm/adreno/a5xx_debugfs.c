<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016-2017 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश <linux/debugfs.h>

#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "a5xx_gpu.h"

अटल व्योम pfp_prपूर्णांक(काष्ठा msm_gpu *gpu, काष्ठा drm_prपूर्णांकer *p)
अणु
	पूर्णांक i;

	drm_म_लिखो(p, "PFP state:\n");

	क्रम (i = 0; i < 36; i++) अणु
		gpu_ग_लिखो(gpu, REG_A5XX_CP_PFP_STAT_ADDR, i);
		drm_म_लिखो(p, "  %02x: %08x\n", i,
			gpu_पढ़ो(gpu, REG_A5XX_CP_PFP_STAT_DATA));
	पूर्ण
पूर्ण

अटल व्योम me_prपूर्णांक(काष्ठा msm_gpu *gpu, काष्ठा drm_prपूर्णांकer *p)
अणु
	पूर्णांक i;

	drm_म_लिखो(p, "ME state:\n");

	क्रम (i = 0; i < 29; i++) अणु
		gpu_ग_लिखो(gpu, REG_A5XX_CP_ME_STAT_ADDR, i);
		drm_म_लिखो(p, "  %02x: %08x\n", i,
			gpu_पढ़ो(gpu, REG_A5XX_CP_ME_STAT_DATA));
	पूर्ण
पूर्ण

अटल व्योम meq_prपूर्णांक(काष्ठा msm_gpu *gpu, काष्ठा drm_prपूर्णांकer *p)
अणु
	पूर्णांक i;

	drm_म_लिखो(p, "MEQ state:\n");
	gpu_ग_लिखो(gpu, REG_A5XX_CP_MEQ_DBG_ADDR, 0);

	क्रम (i = 0; i < 64; i++) अणु
		drm_म_लिखो(p, "  %02x: %08x\n", i,
			gpu_पढ़ो(gpu, REG_A5XX_CP_MEQ_DBG_DATA));
	पूर्ण
पूर्ण

अटल व्योम roq_prपूर्णांक(काष्ठा msm_gpu *gpu, काष्ठा drm_prपूर्णांकer *p)
अणु
	पूर्णांक i;

	drm_म_लिखो(p, "ROQ state:\n");
	gpu_ग_लिखो(gpu, REG_A5XX_CP_ROQ_DBG_ADDR, 0);

	क्रम (i = 0; i < 512 / 4; i++) अणु
		uपूर्णांक32_t val[4];
		पूर्णांक j;
		क्रम (j = 0; j < 4; j++)
			val[j] = gpu_पढ़ो(gpu, REG_A5XX_CP_ROQ_DBG_DATA);
		drm_म_लिखो(p, "  %02x: %08x %08x %08x %08x\n", i,
			val[0], val[1], val[2], val[3]);
	पूर्ण
पूर्ण

अटल पूर्णांक show(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);
	व्योम (*show)(काष्ठा msm_gpu *gpu, काष्ठा drm_prपूर्णांकer *p) =
		node->info_ent->data;

	show(priv->gpu, &p);
	वापस 0;
पूर्ण

#घोषणा ENT(n) अणु .name = #n, .show = show, .data = n ##_prपूर्णांक पूर्ण
अटल काष्ठा drm_info_list a5xx_debugfs_list[] = अणु
	ENT(pfp),
	ENT(me),
	ENT(meq),
	ENT(roq),
पूर्ण;

/* क्रम debugfs files that can be written to, we can't use drm helper: */
अटल पूर्णांक
reset_set(व्योम *data, u64 val)
अणु
	काष्ठा drm_device *dev = data;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_gpu *gpu = priv->gpu;
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EINVAL;

	/* TODO करो we care about trying to make sure the GPU is idle?
	 * Since this is just a debug feature limited to CAP_SYS_ADMIN,
	 * maybe it is fine to let the user keep both pieces अगर they
	 * try to reset an active GPU.
	 */

	mutex_lock(&dev->काष्ठा_mutex);

	release_firmware(adreno_gpu->fw[ADRENO_FW_PM4]);
	adreno_gpu->fw[ADRENO_FW_PM4] = शून्य;

	release_firmware(adreno_gpu->fw[ADRENO_FW_PFP]);
	adreno_gpu->fw[ADRENO_FW_PFP] = शून्य;

	अगर (a5xx_gpu->pm4_bo) अणु
		msm_gem_unpin_iova(a5xx_gpu->pm4_bo, gpu->aspace);
		drm_gem_object_put_locked(a5xx_gpu->pm4_bo);
		a5xx_gpu->pm4_bo = शून्य;
	पूर्ण

	अगर (a5xx_gpu->pfp_bo) अणु
		msm_gem_unpin_iova(a5xx_gpu->pfp_bo, gpu->aspace);
		drm_gem_object_put_locked(a5xx_gpu->pfp_bo);
		a5xx_gpu->pfp_bo = शून्य;
	पूर्ण

	gpu->needs_hw_init = true;

	pm_runसमय_get_sync(&gpu->pdev->dev);
	gpu->funcs->recover(gpu);

	pm_runसमय_put_sync(&gpu->pdev->dev);
	mutex_unlock(&dev->काष्ठा_mutex);

	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(reset_fops, शून्य, reset_set, "%llx\n");


व्योम a5xx_debugfs_init(काष्ठा msm_gpu *gpu, काष्ठा drm_minor *minor)
अणु
	काष्ठा drm_device *dev;

	अगर (!minor)
		वापस;

	dev = minor->dev;

	drm_debugfs_create_files(a5xx_debugfs_list,
				 ARRAY_SIZE(a5xx_debugfs_list),
				 minor->debugfs_root, minor);

	debugfs_create_file("reset", S_IWUGO, minor->debugfs_root, dev,
			    &reset_fops);
पूर्ण
