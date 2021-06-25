<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

/* For profiling, userspace can:
 *
 *   tail -f /sys/kernel/debug/dri/<minor>/gpu
 *
 * This will enable perक्रमmance counters/profiling to track the busy समय
 * and any gpu specअगरic perक्रमmance counters that are supported.
 */

#अगर_घोषित CONFIG_DEBUG_FS

#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_file.h>

#समावेश "msm_drv.h"
#समावेश "msm_gpu.h"

काष्ठा msm_perf_state अणु
	काष्ठा drm_device *dev;

	bool खोलो;
	पूर्णांक cnt;
	काष्ठा mutex पढ़ो_lock;

	अक्षर buf[256];
	पूर्णांक buftot, bufpos;

	अचिन्हित दीर्घ next_jअगरfies;
पूर्ण;

#घोषणा SAMPLE_TIME (HZ/4)

/* रुको क्रम next sample समय: */
अटल पूर्णांक रुको_sample(काष्ठा msm_perf_state *perf)
अणु
	अचिन्हित दीर्घ start_jअगरfies = jअगरfies;

	अगर (समय_after(perf->next_jअगरfies, start_jअगरfies)) अणु
		अचिन्हित दीर्घ reमुख्यing_jअगरfies =
			perf->next_jअगरfies - start_jअगरfies;
		पूर्णांक ret = schedule_समयout_पूर्णांकerruptible(reमुख्यing_jअगरfies);
		अगर (ret > 0) अणु
			/* पूर्णांकerrupted */
			वापस -ERESTARTSYS;
		पूर्ण
	पूर्ण
	perf->next_jअगरfies += SAMPLE_TIME;
	वापस 0;
पूर्ण

अटल पूर्णांक refill_buf(काष्ठा msm_perf_state *perf)
अणु
	काष्ठा msm_drm_निजी *priv = perf->dev->dev_निजी;
	काष्ठा msm_gpu *gpu = priv->gpu;
	अक्षर *ptr = perf->buf;
	पूर्णांक rem = माप(perf->buf);
	पूर्णांक i, n;

	अगर ((perf->cnt++ % 32) == 0) अणु
		/* Header line: */
		n = snम_लिखो(ptr, rem, "%%BUSY");
		ptr += n;
		rem -= n;

		क्रम (i = 0; i < gpu->num_perfcntrs; i++) अणु
			स्थिर काष्ठा msm_gpu_perfcntr *perfcntr = &gpu->perfcntrs[i];
			n = snम_लिखो(ptr, rem, "\t%s", perfcntr->name);
			ptr += n;
			rem -= n;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Sample line: */
		uपूर्णांक32_t activeसमय = 0, totalसमय = 0;
		uपूर्णांक32_t cntrs[5];
		uपूर्णांक32_t val;
		पूर्णांक ret;

		/* sleep until next sample समय: */
		ret = रुको_sample(perf);
		अगर (ret)
			वापस ret;

		ret = msm_gpu_perfcntr_sample(gpu, &activeसमय, &totalसमय,
				ARRAY_SIZE(cntrs), cntrs);
		अगर (ret < 0)
			वापस ret;

		val = totalसमय ? 1000 * activeसमय / totalसमय : 0;
		n = snम_लिखो(ptr, rem, "%3d.%d%%", val / 10, val % 10);
		ptr += n;
		rem -= n;

		क्रम (i = 0; i < ret; i++) अणु
			/* cycle counters (I think).. convert to MHz.. */
			val = cntrs[i] / 10000;
			n = snम_लिखो(ptr, rem, "\t%5d.%02d",
					val / 100, val % 100);
			ptr += n;
			rem -= n;
		पूर्ण
	पूर्ण

	n = snम_लिखो(ptr, rem, "\n");
	ptr += n;
	rem -= n;

	perf->bufpos = 0;
	perf->buftot = ptr - perf->buf;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार perf_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		माप_प्रकार sz, loff_t *ppos)
अणु
	काष्ठा msm_perf_state *perf = file->निजी_data;
	पूर्णांक n = 0, ret = 0;

	mutex_lock(&perf->पढ़ो_lock);

	अगर (perf->bufpos >= perf->buftot) अणु
		ret = refill_buf(perf);
		अगर (ret)
			जाओ out;
	पूर्ण

	n = min((पूर्णांक)sz, perf->buftot - perf->bufpos);
	अगर (copy_to_user(buf, &perf->buf[perf->bufpos], n)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	perf->bufpos += n;
	*ppos += n;

out:
	mutex_unlock(&perf->पढ़ो_lock);
	अगर (ret)
		वापस ret;
	वापस n;
पूर्ण

अटल पूर्णांक perf_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा msm_perf_state *perf = inode->i_निजी;
	काष्ठा drm_device *dev = perf->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_gpu *gpu = priv->gpu;
	पूर्णांक ret = 0;

	mutex_lock(&dev->काष्ठा_mutex);

	अगर (perf->खोलो || !gpu) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	file->निजी_data = perf;
	perf->खोलो = true;
	perf->cnt = 0;
	perf->buftot = 0;
	perf->bufpos = 0;
	msm_gpu_perfcntr_start(gpu);
	perf->next_jअगरfies = jअगरfies + SAMPLE_TIME;

out:
	mutex_unlock(&dev->काष्ठा_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक perf_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा msm_perf_state *perf = inode->i_निजी;
	काष्ठा msm_drm_निजी *priv = perf->dev->dev_निजी;
	msm_gpu_perfcntr_stop(priv->gpu);
	perf->खोलो = false;
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा file_operations perf_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = perf_खोलो,
	.पढ़ो = perf_पढ़ो,
	.llseek = no_llseek,
	.release = perf_release,
पूर्ण;

पूर्णांक msm_perf_debugfs_init(काष्ठा drm_minor *minor)
अणु
	काष्ठा msm_drm_निजी *priv = minor->dev->dev_निजी;
	काष्ठा msm_perf_state *perf;

	/* only create on first minor: */
	अगर (priv->perf)
		वापस 0;

	perf = kzalloc(माप(*perf), GFP_KERNEL);
	अगर (!perf)
		वापस -ENOMEM;

	perf->dev = minor->dev;

	mutex_init(&perf->पढ़ो_lock);
	priv->perf = perf;

	debugfs_create_file("perf", S_IFREG | S_IRUGO, minor->debugfs_root,
			    perf, &perf_debugfs_fops);
	वापस 0;
पूर्ण

व्योम msm_perf_debugfs_cleanup(काष्ठा msm_drm_निजी *priv)
अणु
	काष्ठा msm_perf_state *perf = priv->perf;

	अगर (!perf)
		वापस;

	priv->perf = शून्य;

	mutex_destroy(&perf->पढ़ो_lock);

	kमुक्त(perf);
पूर्ण

#पूर्ण_अगर
