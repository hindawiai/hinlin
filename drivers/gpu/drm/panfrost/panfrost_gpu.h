<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2018 Marty E. Plummer <hanetzer@starपंचांगail.com> */
/* Copyright 2019 Collabora ltd. */

#अगर_अघोषित __PANFROST_GPU_H__
#घोषणा __PANFROST_GPU_H__

काष्ठा panfrost_device;

पूर्णांक panfrost_gpu_init(काष्ठा panfrost_device *pfdev);
व्योम panfrost_gpu_fini(काष्ठा panfrost_device *pfdev);

u32 panfrost_gpu_get_latest_flush_id(काष्ठा panfrost_device *pfdev);

पूर्णांक panfrost_gpu_soft_reset(काष्ठा panfrost_device *pfdev);
व्योम panfrost_gpu_घातer_on(काष्ठा panfrost_device *pfdev);
व्योम panfrost_gpu_घातer_off(काष्ठा panfrost_device *pfdev);

व्योम panfrost_gpu_amlogic_quirk(काष्ठा panfrost_device *pfdev);

#पूर्ण_अगर
