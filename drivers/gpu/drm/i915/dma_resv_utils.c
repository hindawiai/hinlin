<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <linux/dma-resv.h>

#समावेश "dma_resv_utils.h"

व्योम dma_resv_prune(काष्ठा dma_resv *resv)
अणु
	अगर (dma_resv_trylock(resv)) अणु
		अगर (dma_resv_test_संकेतed_rcu(resv, true))
			dma_resv_add_excl_fence(resv, शून्य);
		dma_resv_unlock(resv);
	पूर्ण
पूर्ण
