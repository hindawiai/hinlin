<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2017 The Linux Foundation. All rights reserved. */

#अगर_अघोषित _A6XX_GMU_H_
#घोषणा _A6XX_GMU_H_

#समावेश <linux/iopoll.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "msm_drv.h"
#समावेश "a6xx_hfi.h"

काष्ठा a6xx_gmu_bo अणु
	काष्ठा drm_gem_object *obj;
	व्योम *virt;
	माप_प्रकार size;
	u64 iova;
पूर्ण;

/*
 * These define the dअगरferent GMU wake up options - these define how both the
 * CPU and the GMU bring up the hardware
 */

/* THe GMU has alपढ़ोy been booted and the rentention रेजिस्टरs are active */
#घोषणा GMU_WARM_BOOT 0

/* the GMU is coming up क्रम the first समय or back from a घातer collapse */
#घोषणा GMU_COLD_BOOT 1

/*
 * These define the level of control that the GMU has - the higher the number
 * the more things that the GMU hardware controls on its own.
 */

/* The GMU करोes not करो any idle state management */
#घोषणा GMU_IDLE_STATE_ACTIVE 0

/* The GMU manages SPTP घातer collapse */
#घोषणा GMU_IDLE_STATE_SPTP 2

/* The GMU करोes स्वतःmatic IFPC (पूर्णांकra-frame घातer collapse) */
#घोषणा GMU_IDLE_STATE_IFPC 3

काष्ठा a6xx_gmu अणु
	काष्ठा device *dev;

	काष्ठा msm_gem_address_space *aspace;

	व्योम * __iomem mmio;
	व्योम * __iomem rscc;

	पूर्णांक hfi_irq;
	पूर्णांक gmu_irq;

	काष्ठा device *gxpd;

	पूर्णांक idle_level;

	काष्ठा a6xx_gmu_bo hfi;
	काष्ठा a6xx_gmu_bo debug;
	काष्ठा a6xx_gmu_bo icache;
	काष्ठा a6xx_gmu_bo dcache;
	काष्ठा a6xx_gmu_bo dummy;
	काष्ठा a6xx_gmu_bo log;

	पूर्णांक nr_घड़ीs;
	काष्ठा clk_bulk_data *घड़ीs;
	काष्ठा clk *core_clk;

	/* current perक्रमmance index set बाह्यally */
	पूर्णांक current_perf_index;

	पूर्णांक nr_gpu_freqs;
	अचिन्हित दीर्घ gpu_freqs[16];
	u32 gx_arc_votes[16];

	पूर्णांक nr_gmu_freqs;
	अचिन्हित दीर्घ gmu_freqs[4];
	u32 cx_arc_votes[4];

	अचिन्हित दीर्घ freq;

	काष्ठा a6xx_hfi_queue queues[2];

	bool initialized;
	bool hung;
	bool legacy; /* a618 or a630 */
पूर्ण;

अटल अंतरभूत u32 gmu_पढ़ो(काष्ठा a6xx_gmu *gmu, u32 offset)
अणु
	वापस msm_पढ़ोl(gmu->mmio + (offset << 2));
पूर्ण

अटल अंतरभूत व्योम gmu_ग_लिखो(काष्ठा a6xx_gmu *gmu, u32 offset, u32 value)
अणु
	वापस msm_ग_लिखोl(value, gmu->mmio + (offset << 2));
पूर्ण

अटल अंतरभूत व्योम
gmu_ग_लिखो_bulk(काष्ठा a6xx_gmu *gmu, u32 offset, स्थिर u32 *data, u32 size)
अणु
	स_नकल_toio(gmu->mmio + (offset << 2), data, size);
	wmb();
पूर्ण

अटल अंतरभूत व्योम gmu_rmw(काष्ठा a6xx_gmu *gmu, u32 reg, u32 mask, u32 or)
अणु
	u32 val = gmu_पढ़ो(gmu, reg);

	val &= ~mask;

	gmu_ग_लिखो(gmu, reg, val | or);
पूर्ण

अटल अंतरभूत u64 gmu_पढ़ो64(काष्ठा a6xx_gmu *gmu, u32 lo, u32 hi)
अणु
	u64 val;

	val = (u64) msm_पढ़ोl(gmu->mmio + (lo << 2));
	val |= ((u64) msm_पढ़ोl(gmu->mmio + (hi << 2)) << 32);

	वापस val;
पूर्ण

#घोषणा gmu_poll_समयout(gmu, addr, val, cond, पूर्णांकerval, समयout) \
	पढ़ोl_poll_समयout((gmu)->mmio + ((addr) << 2), val, cond, \
		पूर्णांकerval, समयout)

अटल अंतरभूत u32 gmu_पढ़ो_rscc(काष्ठा a6xx_gmu *gmu, u32 offset)
अणु
	वापस msm_पढ़ोl(gmu->rscc + (offset << 2));
पूर्ण

अटल अंतरभूत व्योम gmu_ग_लिखो_rscc(काष्ठा a6xx_gmu *gmu, u32 offset, u32 value)
अणु
	वापस msm_ग_लिखोl(value, gmu->rscc + (offset << 2));
पूर्ण

#घोषणा gmu_poll_समयout_rscc(gmu, addr, val, cond, पूर्णांकerval, समयout) \
	पढ़ोl_poll_समयout((gmu)->rscc + ((addr) << 2), val, cond, \
		पूर्णांकerval, समयout)

/*
 * These are the available OOB (out of band requests) to the GMU where "out of
 * band" means that the CPU talks to the GMU directly and not through HFI.
 * Normally this works by writing a ITCM/DTCM रेजिस्टर and then triggering a
 * पूर्णांकerrupt (the "request" bit) and रुकोing क्रम an acknowledgment (the "ack"
 * bit). The state is cleared by writing the "clear' bit to the GMU पूर्णांकerrupt.
 *
 * These are used to क्रमce the GMU/GPU to stay on during a critical sequence or
 * क्रम hardware workarounds.
 */

क्रमागत a6xx_gmu_oob_state अणु
	/*
	 * Let the GMU know that a boot or slumber operation has started. The value in
	 * REG_A6XX_GMU_BOOT_SLUMBER_OPTION lets the GMU know which operation we are
	 * करोing
	 */
	GMU_OOB_BOOT_SLUMBER = 0,
	/*
	 * Let the GMU know to not turn off any GPU रेजिस्टरs जबतक the CPU is in a
	 * critical section
	 */
	GMU_OOB_GPU_SET,
	/*
	 * Set a new घातer level क्रम the GPU when the CPU is करोing frequency scaling
	 */
	GMU_OOB_DCVS_SET,
	/*
	 * Used to keep the GPU on क्रम CPU-side पढ़ोs of perक्रमmance counters.
	 */
	GMU_OOB_PERFCOUNTER_SET,
पूर्ण;

व्योम a6xx_hfi_init(काष्ठा a6xx_gmu *gmu);
पूर्णांक a6xx_hfi_start(काष्ठा a6xx_gmu *gmu, पूर्णांक boot_state);
व्योम a6xx_hfi_stop(काष्ठा a6xx_gmu *gmu);
पूर्णांक a6xx_hfi_send_prep_slumber(काष्ठा a6xx_gmu *gmu);
पूर्णांक a6xx_hfi_set_freq(काष्ठा a6xx_gmu *gmu, पूर्णांक index);

bool a6xx_gmu_gx_is_on(काष्ठा a6xx_gmu *gmu);
bool a6xx_gmu_sptprac_is_on(काष्ठा a6xx_gmu *gmu);

#पूर्ण_अगर
