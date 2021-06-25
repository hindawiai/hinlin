<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2019 Collabora Ltd */
#अगर_अघोषित __PANFROST_PERFCNT_H__
#घोषणा __PANFROST_PERFCNT_H__

#समावेश "panfrost_device.h"

व्योम panfrost_perfcnt_sample_करोne(काष्ठा panfrost_device *pfdev);
व्योम panfrost_perfcnt_clean_cache_करोne(काष्ठा panfrost_device *pfdev);
पूर्णांक panfrost_perfcnt_init(काष्ठा panfrost_device *pfdev);
व्योम panfrost_perfcnt_fini(काष्ठा panfrost_device *pfdev);
व्योम panfrost_perfcnt_बंद(काष्ठा drm_file *file_priv);
पूर्णांक panfrost_ioctl_perfcnt_enable(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file_priv);
पूर्णांक panfrost_ioctl_perfcnt_dump(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_priv);

#पूर्ण_अगर
