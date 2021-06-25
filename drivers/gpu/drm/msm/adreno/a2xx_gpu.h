<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018 The Linux Foundation. All rights reserved. */

#अगर_अघोषित __A2XX_GPU_H__
#घोषणा __A2XX_GPU_H__

#समावेश "adreno_gpu.h"

/* arrg, somehow fb.h is getting pulled in: */
#अघोषित ROP_COPY
#अघोषित ROP_XOR

#समावेश "a2xx.xml.h"

काष्ठा a2xx_gpu अणु
	काष्ठा adreno_gpu base;
	bool pm_enabled;
पूर्ण;
#घोषणा to_a2xx_gpu(x) container_of(x, काष्ठा a2xx_gpu, base)

#पूर्ण_अगर /* __A2XX_GPU_H__ */
