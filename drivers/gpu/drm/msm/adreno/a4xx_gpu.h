<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2014 The Linux Foundation. All rights reserved.
 */
#अगर_अघोषित __A4XX_GPU_H__
#घोषणा __A4XX_GPU_H__

#समावेश "adreno_gpu.h"

/* arrg, somehow fb.h is getting pulled in: */
#अघोषित ROP_COPY
#अघोषित ROP_XOR

#समावेश "a4xx.xml.h"

काष्ठा a4xx_gpu अणु
	काष्ठा adreno_gpu base;

	/* अगर OCMEM is used क्रम GMEM: */
	काष्ठा adreno_ocmem ocmem;
पूर्ण;
#घोषणा to_a4xx_gpu(x) container_of(x, काष्ठा a4xx_gpu, base)

#पूर्ण_अगर /* __A4XX_GPU_H__ */
