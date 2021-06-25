<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2017 Samsung Electronics Co., Ltd.
 */

#अगर_अघोषित _EXYNOS_DRM_IPP_H_
#घोषणा _EXYNOS_DRM_IPP_H_

काष्ठा exynos_drm_ipp;
काष्ठा exynos_drm_ipp_task;

/**
 * काष्ठा exynos_drm_ipp_funcs - exynos_drm_ipp control functions
 */
काष्ठा exynos_drm_ipp_funcs अणु
	/**
	 * @commit:
	 *
	 * This is the मुख्य entry poपूर्णांक to start framebuffer processing
	 * in the hardware. The exynos_drm_ipp_task has been alपढ़ोy validated.
	 * This function must not रुको until the device finishes processing.
	 * When the driver finishes processing, it has to call
	 * exynos_exynos_drm_ipp_task_करोne() function.
	 *
	 * RETURNS:
	 *
	 * 0 on success or negative error codes in हाल of failure.
	 */
	पूर्णांक (*commit)(काष्ठा exynos_drm_ipp *ipp,
		      काष्ठा exynos_drm_ipp_task *task);

	/**
	 * @पात:
	 *
	 * Inक्रमms the driver that it has to पात the currently running
	 * task as soon as possible (i.e. as soon as it can stop the device
	 * safely), even अगर the task would not have been finished by then.
	 * After the driver perक्रमms the necessary steps, it has to call
	 * exynos_drm_ipp_task_करोne() (as अगर the task ended normally).
	 * This function करोes not have to (and will usually not) रुको
	 * until the device enters a state when it can be stopped.
	 */
	व्योम (*पात)(काष्ठा exynos_drm_ipp *ipp,
		      काष्ठा exynos_drm_ipp_task *task);
पूर्ण;

/**
 * काष्ठा exynos_drm_ipp - central picture processor module काष्ठाure
 */
काष्ठा exynos_drm_ipp अणु
	काष्ठा drm_device *drm_dev;
	काष्ठा device *dev;
	काष्ठा list_head head;
	अचिन्हित पूर्णांक id;

	स्थिर अक्षर *name;
	स्थिर काष्ठा exynos_drm_ipp_funcs *funcs;
	अचिन्हित पूर्णांक capabilities;
	स्थिर काष्ठा exynos_drm_ipp_क्रमmats *क्रमmats;
	अचिन्हित पूर्णांक num_क्रमmats;
	atomic_t sequence;

	spinlock_t lock;
	काष्ठा exynos_drm_ipp_task *task;
	काष्ठा list_head toकरो_list;
	रुको_queue_head_t करोne_wq;
पूर्ण;

काष्ठा exynos_drm_ipp_buffer अणु
	काष्ठा drm_exynos_ipp_task_buffer buf;
	काष्ठा drm_exynos_ipp_task_rect rect;

	काष्ठा exynos_drm_gem *exynos_gem[MAX_FB_BUFFER];
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat;
	dma_addr_t dma_addr[MAX_FB_BUFFER];
पूर्ण;

/**
 * काष्ठा exynos_drm_ipp_task - a काष्ठाure describing transक्रमmation that
 * has to be perक्रमmed by the picture processor hardware module
 */
काष्ठा exynos_drm_ipp_task अणु
	काष्ठा device *dev;
	काष्ठा exynos_drm_ipp *ipp;
	काष्ठा list_head head;

	काष्ठा exynos_drm_ipp_buffer src;
	काष्ठा exynos_drm_ipp_buffer dst;

	काष्ठा drm_exynos_ipp_task_transक्रमm transक्रमm;
	काष्ठा drm_exynos_ipp_task_alpha alpha;

	काष्ठा work_काष्ठा cleanup_work;
	अचिन्हित पूर्णांक flags;
	पूर्णांक ret;

	काष्ठा drm_pending_exynos_ipp_event *event;
पूर्ण;

#घोषणा DRM_EXYNOS_IPP_TASK_DONE	(1 << 0)
#घोषणा DRM_EXYNOS_IPP_TASK_ASYNC	(1 << 1)

काष्ठा exynos_drm_ipp_क्रमmats अणु
	uपूर्णांक32_t fourcc;
	uपूर्णांक32_t type;
	uपूर्णांक64_t modअगरier;
	स्थिर काष्ठा drm_exynos_ipp_limit *limits;
	अचिन्हित पूर्णांक num_limits;
पूर्ण;

/* helper macros to set exynos_drm_ipp_क्रमmats काष्ठाure and limits*/
#घोषणा IPP_SRCDST_MFORMAT(f, m, l) \
	.fourcc = DRM_FORMAT_##f, .modअगरier = m, .limits = l, \
	.num_limits = ARRAY_SIZE(l), \
	.type = (DRM_EXYNOS_IPP_FORMAT_SOURCE | \
		 DRM_EXYNOS_IPP_FORMAT_DESTINATION)

#घोषणा IPP_SRCDST_FORMAT(f, l) IPP_SRCDST_MFORMAT(f, 0, l)

#घोषणा IPP_SIZE_LIMIT(l, val...)	\
	.type = (DRM_EXYNOS_IPP_LIMIT_TYPE_SIZE | \
		 DRM_EXYNOS_IPP_LIMIT_SIZE_##l), val

#घोषणा IPP_SCALE_LIMIT(val...)		\
	.type = (DRM_EXYNOS_IPP_LIMIT_TYPE_SCALE), val

पूर्णांक exynos_drm_ipp_रेजिस्टर(काष्ठा device *dev, काष्ठा exynos_drm_ipp *ipp,
		स्थिर काष्ठा exynos_drm_ipp_funcs *funcs, अचिन्हित पूर्णांक caps,
		स्थिर काष्ठा exynos_drm_ipp_क्रमmats *क्रमmats,
		अचिन्हित पूर्णांक num_क्रमmats, स्थिर अक्षर *name);
व्योम exynos_drm_ipp_unरेजिस्टर(काष्ठा device *dev,
			       काष्ठा exynos_drm_ipp *ipp);

व्योम exynos_drm_ipp_task_करोne(काष्ठा exynos_drm_ipp_task *task, पूर्णांक ret);

#अगर_घोषित CONFIG_DRM_EXYNOS_IPP
पूर्णांक exynos_drm_ipp_get_res_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file_priv);
पूर्णांक exynos_drm_ipp_get_caps_ioctl(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file_priv);
पूर्णांक exynos_drm_ipp_get_limits_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file_priv);
पूर्णांक exynos_drm_ipp_commit_ioctl(काष्ठा drm_device *dev,
				व्योम *data, काष्ठा drm_file *file_priv);
#अन्यथा
अटल अंतरभूत पूर्णांक exynos_drm_ipp_get_res_ioctl(काष्ठा drm_device *dev,
	 व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_exynos_ioctl_ipp_get_res *resp = data;

	resp->count_ipps = 0;
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक exynos_drm_ipp_get_caps_ioctl(काष्ठा drm_device *dev,
	 व्योम *data, काष्ठा drm_file *file_priv)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक exynos_drm_ipp_get_limits_ioctl(काष्ठा drm_device *dev,
	 व्योम *data, काष्ठा drm_file *file_priv)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक exynos_drm_ipp_commit_ioctl(काष्ठा drm_device *dev,
	 व्योम *data, काष्ठा drm_file *file_priv)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
