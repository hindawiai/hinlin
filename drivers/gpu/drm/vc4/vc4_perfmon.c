<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Broadcom
 */

/**
 * DOC: VC4 V3D perक्रमmance monitor module
 *
 * The V3D block provides 16 hardware counters which can count various events.
 */

#समावेश "vc4_drv.h"
#समावेश "vc4_regs.h"

#घोषणा VC4_PERFMONID_MIN	1
#घोषणा VC4_PERFMONID_MAX	U32_MAX

व्योम vc4_perfmon_get(काष्ठा vc4_perfmon *perfmon)
अणु
	अगर (perfmon)
		refcount_inc(&perfmon->refcnt);
पूर्ण

व्योम vc4_perfmon_put(काष्ठा vc4_perfmon *perfmon)
अणु
	अगर (perfmon && refcount_dec_and_test(&perfmon->refcnt))
		kमुक्त(perfmon);
पूर्ण

व्योम vc4_perfmon_start(काष्ठा vc4_dev *vc4, काष्ठा vc4_perfmon *perfmon)
अणु
	अचिन्हित पूर्णांक i;
	u32 mask;

	अगर (WARN_ON_ONCE(!perfmon || vc4->active_perfmon))
		वापस;

	क्रम (i = 0; i < perfmon->ncounters; i++)
		V3D_WRITE(V3D_PCTRS(i), perfmon->events[i]);

	mask = GENMASK(perfmon->ncounters - 1, 0);
	V3D_WRITE(V3D_PCTRC, mask);
	V3D_WRITE(V3D_PCTRE, V3D_PCTRE_EN | mask);
	vc4->active_perfmon = perfmon;
पूर्ण

व्योम vc4_perfmon_stop(काष्ठा vc4_dev *vc4, काष्ठा vc4_perfmon *perfmon,
		      bool capture)
अणु
	अचिन्हित पूर्णांक i;

	अगर (WARN_ON_ONCE(!vc4->active_perfmon ||
			 perfmon != vc4->active_perfmon))
		वापस;

	अगर (capture) अणु
		क्रम (i = 0; i < perfmon->ncounters; i++)
			perfmon->counters[i] += V3D_READ(V3D_PCTR(i));
	पूर्ण

	V3D_WRITE(V3D_PCTRE, 0);
	vc4->active_perfmon = शून्य;
पूर्ण

काष्ठा vc4_perfmon *vc4_perfmon_find(काष्ठा vc4_file *vc4file, पूर्णांक id)
अणु
	काष्ठा vc4_perfmon *perfmon;

	mutex_lock(&vc4file->perfmon.lock);
	perfmon = idr_find(&vc4file->perfmon.idr, id);
	vc4_perfmon_get(perfmon);
	mutex_unlock(&vc4file->perfmon.lock);

	वापस perfmon;
पूर्ण

व्योम vc4_perfmon_खोलो_file(काष्ठा vc4_file *vc4file)
अणु
	mutex_init(&vc4file->perfmon.lock);
	idr_init_base(&vc4file->perfmon.idr, VC4_PERFMONID_MIN);
पूर्ण

अटल पूर्णांक vc4_perfmon_idr_del(पूर्णांक id, व्योम *elem, व्योम *data)
अणु
	काष्ठा vc4_perfmon *perfmon = elem;

	vc4_perfmon_put(perfmon);

	वापस 0;
पूर्ण

व्योम vc4_perfmon_बंद_file(काष्ठा vc4_file *vc4file)
अणु
	mutex_lock(&vc4file->perfmon.lock);
	idr_क्रम_each(&vc4file->perfmon.idr, vc4_perfmon_idr_del, शून्य);
	idr_destroy(&vc4file->perfmon.idr);
	mutex_unlock(&vc4file->perfmon.lock);
पूर्ण

पूर्णांक vc4_perfmon_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file_priv)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_file *vc4file = file_priv->driver_priv;
	काष्ठा drm_vc4_perfmon_create *req = data;
	काष्ठा vc4_perfmon *perfmon;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!vc4->v3d) अणु
		DRM_DEBUG("Creating perfmon no VC4 V3D probed\n");
		वापस -ENODEV;
	पूर्ण

	/* Number of monitored counters cannot exceed HW limits. */
	अगर (req->ncounters > DRM_VC4_MAX_PERF_COUNTERS ||
	    !req->ncounters)
		वापस -EINVAL;

	/* Make sure all events are valid. */
	क्रम (i = 0; i < req->ncounters; i++) अणु
		अगर (req->events[i] >= VC4_PERFCNT_NUM_EVENTS)
			वापस -EINVAL;
	पूर्ण

	perfmon = kzalloc(काष्ठा_size(perfmon, counters, req->ncounters),
			  GFP_KERNEL);
	अगर (!perfmon)
		वापस -ENOMEM;

	क्रम (i = 0; i < req->ncounters; i++)
		perfmon->events[i] = req->events[i];

	perfmon->ncounters = req->ncounters;

	refcount_set(&perfmon->refcnt, 1);

	mutex_lock(&vc4file->perfmon.lock);
	ret = idr_alloc(&vc4file->perfmon.idr, perfmon, VC4_PERFMONID_MIN,
			VC4_PERFMONID_MAX, GFP_KERNEL);
	mutex_unlock(&vc4file->perfmon.lock);

	अगर (ret < 0) अणु
		kमुक्त(perfmon);
		वापस ret;
	पूर्ण

	req->id = ret;
	वापस 0;
पूर्ण

पूर्णांक vc4_perfmon_destroy_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file_priv)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_file *vc4file = file_priv->driver_priv;
	काष्ठा drm_vc4_perfmon_destroy *req = data;
	काष्ठा vc4_perfmon *perfmon;

	अगर (!vc4->v3d) अणु
		DRM_DEBUG("Destroying perfmon no VC4 V3D probed\n");
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&vc4file->perfmon.lock);
	perfmon = idr_हटाओ(&vc4file->perfmon.idr, req->id);
	mutex_unlock(&vc4file->perfmon.lock);

	अगर (!perfmon)
		वापस -EINVAL;

	vc4_perfmon_put(perfmon);
	वापस 0;
पूर्ण

पूर्णांक vc4_perfmon_get_values_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file_priv)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_file *vc4file = file_priv->driver_priv;
	काष्ठा drm_vc4_perfmon_get_values *req = data;
	काष्ठा vc4_perfmon *perfmon;
	पूर्णांक ret;

	अगर (!vc4->v3d) अणु
		DRM_DEBUG("Getting perfmon no VC4 V3D probed\n");
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&vc4file->perfmon.lock);
	perfmon = idr_find(&vc4file->perfmon.idr, req->id);
	vc4_perfmon_get(perfmon);
	mutex_unlock(&vc4file->perfmon.lock);

	अगर (!perfmon)
		वापस -EINVAL;

	अगर (copy_to_user(u64_to_user_ptr(req->values_ptr), perfmon->counters,
			 perfmon->ncounters * माप(u64)))
		ret = -EFAULT;
	अन्यथा
		ret = 0;

	vc4_perfmon_put(perfmon);
	वापस ret;
पूर्ण
