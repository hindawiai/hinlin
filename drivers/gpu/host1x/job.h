<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Tegra host1x Job
 *
 * Copyright (c) 2011-2013, NVIDIA Corporation.
 */

#अगर_अघोषित __HOST1X_JOB_H
#घोषणा __HOST1X_JOB_H

#समावेश <linux/dma-direction.h>

काष्ठा host1x_job_gather अणु
	अचिन्हित पूर्णांक words;
	dma_addr_t base;
	काष्ठा host1x_bo *bo;
	अचिन्हित पूर्णांक offset;
	bool handled;
पूर्ण;

काष्ठा host1x_job_unpin_data अणु
	काष्ठा host1x_bo *bo;
	काष्ठा sg_table *sgt;
	काष्ठा device *dev;
	माप_प्रकार size;
	क्रमागत dma_data_direction dir;
पूर्ण;

/*
 * Dump contents of job to debug output.
 */
व्योम host1x_job_dump(काष्ठा device *dev, काष्ठा host1x_job *job);

#पूर्ण_अगर
