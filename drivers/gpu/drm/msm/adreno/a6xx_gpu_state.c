<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018-2019 The Linux Foundation. All rights reserved. */

#समावेश <linux/ascii85.h>
#समावेश "msm_gem.h"
#समावेश "a6xx_gpu.h"
#समावेश "a6xx_gmu.h"
#समावेश "a6xx_gpu_state.h"
#समावेश "a6xx_gmu.xml.h"

काष्ठा a6xx_gpu_state_obj अणु
	स्थिर व्योम *handle;
	u32 *data;
पूर्ण;

काष्ठा a6xx_gpu_state अणु
	काष्ठा msm_gpu_state base;

	काष्ठा a6xx_gpu_state_obj *gmu_रेजिस्टरs;
	पूर्णांक nr_gmu_रेजिस्टरs;

	काष्ठा a6xx_gpu_state_obj *रेजिस्टरs;
	पूर्णांक nr_रेजिस्टरs;

	काष्ठा a6xx_gpu_state_obj *shaders;
	पूर्णांक nr_shaders;

	काष्ठा a6xx_gpu_state_obj *clusters;
	पूर्णांक nr_clusters;

	काष्ठा a6xx_gpu_state_obj *dbgahb_clusters;
	पूर्णांक nr_dbgahb_clusters;

	काष्ठा a6xx_gpu_state_obj *indexed_regs;
	पूर्णांक nr_indexed_regs;

	काष्ठा a6xx_gpu_state_obj *debugbus;
	पूर्णांक nr_debugbus;

	काष्ठा a6xx_gpu_state_obj *vbअगर_debugbus;

	काष्ठा a6xx_gpu_state_obj *cx_debugbus;
	पूर्णांक nr_cx_debugbus;

	काष्ठा list_head objs;
पूर्ण;

अटल अंतरभूत पूर्णांक CRASHDUMP_WRITE(u64 *in, u32 reg, u32 val)
अणु
	in[0] = val;
	in[1] = (((u64) reg) << 44 | (1 << 21) | 1);

	वापस 2;
पूर्ण

अटल अंतरभूत पूर्णांक CRASHDUMP_READ(u64 *in, u32 reg, u32 dwords, u64 target)
अणु
	in[0] = target;
	in[1] = (((u64) reg) << 44 | dwords);

	वापस 2;
पूर्ण

अटल अंतरभूत पूर्णांक CRASHDUMP_FINI(u64 *in)
अणु
	in[0] = 0;
	in[1] = 0;

	वापस 2;
पूर्ण

काष्ठा a6xx_crashdumper अणु
	व्योम *ptr;
	काष्ठा drm_gem_object *bo;
	u64 iova;
पूर्ण;

काष्ठा a6xx_state_memobj अणु
	काष्ठा list_head node;
	अचिन्हित दीर्घ दीर्घ data[];
पूर्ण;

अटल व्योम *state_kसुस्मृति(काष्ठा a6xx_gpu_state *a6xx_state, पूर्णांक nr, माप_प्रकार objsize)
अणु
	काष्ठा a6xx_state_memobj *obj =
		kzalloc((nr * objsize) + माप(*obj), GFP_KERNEL);

	अगर (!obj)
		वापस शून्य;

	list_add_tail(&obj->node, &a6xx_state->objs);
	वापस &obj->data;
पूर्ण

अटल व्योम *state_kmemdup(काष्ठा a6xx_gpu_state *a6xx_state, व्योम *src,
		माप_प्रकार size)
अणु
	व्योम *dst = state_kसुस्मृति(a6xx_state, 1, size);

	अगर (dst)
		स_नकल(dst, src, size);
	वापस dst;
पूर्ण

/*
 * Allocate 1MB क्रम the crashdumper scratch region - 8k क्रम the script and
 * the rest क्रम the data
 */
#घोषणा A6XX_CD_DATA_OFFSET 8192
#घोषणा A6XX_CD_DATA_SIZE  (SZ_1M - 8192)

अटल पूर्णांक a6xx_crashdumper_init(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_crashdumper *dumper)
अणु
	dumper->ptr = msm_gem_kernel_new_locked(gpu->dev,
		SZ_1M, MSM_BO_UNCACHED, gpu->aspace,
		&dumper->bo, &dumper->iova);

	अगर (!IS_ERR(dumper->ptr))
		msm_gem_object_set_name(dumper->bo, "crashdump");

	वापस PTR_ERR_OR_ZERO(dumper->ptr);
पूर्ण

अटल पूर्णांक a6xx_crashdumper_run(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_crashdumper *dumper)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	u32 val;
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(dumper->ptr))
		वापस -EINVAL;

	अगर (!a6xx_gmu_sptprac_is_on(&a6xx_gpu->gmu))
		वापस -EINVAL;

	/* Make sure all pending memory ग_लिखोs are posted */
	wmb();

	gpu_ग_लिखो64(gpu, REG_A6XX_CP_CRASH_SCRIPT_BASE_LO,
		REG_A6XX_CP_CRASH_SCRIPT_BASE_HI, dumper->iova);

	gpu_ग_लिखो(gpu, REG_A6XX_CP_CRASH_DUMP_CNTL, 1);

	ret = gpu_poll_समयout(gpu, REG_A6XX_CP_CRASH_DUMP_STATUS, val,
		val & 0x02, 100, 10000);

	gpu_ग_लिखो(gpu, REG_A6XX_CP_CRASH_DUMP_CNTL, 0);

	वापस ret;
पूर्ण

/* पढ़ो a value from the GX debug bus */
अटल पूर्णांक debugbus_पढ़ो(काष्ठा msm_gpu *gpu, u32 block, u32 offset,
		u32 *data)
अणु
	u32 reg = A6XX_DBGC_CFG_DBGBUS_SEL_D_PING_INDEX(offset) |
		A6XX_DBGC_CFG_DBGBUS_SEL_D_PING_BLK_SEL(block);

	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_SEL_A, reg);
	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_SEL_B, reg);
	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_SEL_C, reg);
	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_SEL_D, reg);

	/* Wait 1 us to make sure the data is flowing */
	udelay(1);

	data[0] = gpu_पढ़ो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_TRACE_BUF2);
	data[1] = gpu_पढ़ो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_TRACE_BUF1);

	वापस 2;
पूर्ण

#घोषणा cxdbg_ग_लिखो(ptr, offset, val) \
	msm_ग_लिखोl((val), (ptr) + ((offset) << 2))

#घोषणा cxdbg_पढ़ो(ptr, offset) \
	msm_पढ़ोl((ptr) + ((offset) << 2))

/* पढ़ो a value from the CX debug bus */
अटल पूर्णांक cx_debugbus_पढ़ो(व्योम *__iomem cxdbg, u32 block, u32 offset,
		u32 *data)
अणु
	u32 reg = A6XX_CX_DBGC_CFG_DBGBUS_SEL_A_PING_INDEX(offset) |
		A6XX_CX_DBGC_CFG_DBGBUS_SEL_A_PING_BLK_SEL(block);

	cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_SEL_A, reg);
	cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_SEL_B, reg);
	cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_SEL_C, reg);
	cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_SEL_D, reg);

	/* Wait 1 us to make sure the data is flowing */
	udelay(1);

	data[0] = cxdbg_पढ़ो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_TRACE_BUF2);
	data[1] = cxdbg_पढ़ो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_TRACE_BUF1);

	वापस 2;
पूर्ण

/* Read a chunk of data from the VBIF debug bus */
अटल पूर्णांक vbअगर_debugbus_पढ़ो(काष्ठा msm_gpu *gpu, u32 ctrl0, u32 ctrl1,
		u32 reg, पूर्णांक count, u32 *data)
अणु
	पूर्णांक i;

	gpu_ग_लिखो(gpu, ctrl0, reg);

	क्रम (i = 0; i < count; i++) अणु
		gpu_ग_लिखो(gpu, ctrl1, i);
		data[i] = gpu_पढ़ो(gpu, REG_A6XX_VBIF_TEST_BUS_OUT);
	पूर्ण

	वापस count;
पूर्ण

#घोषणा AXI_ARB_BLOCKS 2
#घोषणा XIN_AXI_BLOCKS 5
#घोषणा XIN_CORE_BLOCKS 4

#घोषणा VBIF_DEBUGBUS_BLOCK_SIZE \
	((16 * AXI_ARB_BLOCKS) + \
	 (18 * XIN_AXI_BLOCKS) + \
	 (12 * XIN_CORE_BLOCKS))

अटल व्योम a6xx_get_vbअगर_debugbus_block(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state,
		काष्ठा a6xx_gpu_state_obj *obj)
अणु
	u32 clk, *ptr;
	पूर्णांक i;

	obj->data = state_kसुस्मृति(a6xx_state, VBIF_DEBUGBUS_BLOCK_SIZE,
		माप(u32));
	अगर (!obj->data)
		वापस;

	obj->handle = शून्य;

	/* Get the current घड़ी setting */
	clk = gpu_पढ़ो(gpu, REG_A6XX_VBIF_CLKON);

	/* Force on the bus so we can पढ़ो it */
	gpu_ग_लिखो(gpu, REG_A6XX_VBIF_CLKON,
		clk | A6XX_VBIF_CLKON_FORCE_ON_TESTBUS);

	/* We will पढ़ो from BUS2 first, so disable BUS1 */
	gpu_ग_लिखो(gpu, REG_A6XX_VBIF_TEST_BUS1_CTRL0, 0);

	/* Enable the VBIF bus क्रम पढ़ोing */
	gpu_ग_लिखो(gpu, REG_A6XX_VBIF_TEST_BUS_OUT_CTRL, 1);

	ptr = obj->data;

	क्रम (i = 0; i < AXI_ARB_BLOCKS; i++)
		ptr += vbअगर_debugbus_पढ़ो(gpu,
			REG_A6XX_VBIF_TEST_BUS2_CTRL0,
			REG_A6XX_VBIF_TEST_BUS2_CTRL1,
			1 << (i + 16), 16, ptr);

	क्रम (i = 0; i < XIN_AXI_BLOCKS; i++)
		ptr += vbअगर_debugbus_पढ़ो(gpu,
			REG_A6XX_VBIF_TEST_BUS2_CTRL0,
			REG_A6XX_VBIF_TEST_BUS2_CTRL1,
			1 << i, 18, ptr);

	/* Stop BUS2 so we can turn on BUS1 */
	gpu_ग_लिखो(gpu, REG_A6XX_VBIF_TEST_BUS2_CTRL0, 0);

	क्रम (i = 0; i < XIN_CORE_BLOCKS; i++)
		ptr += vbअगर_debugbus_पढ़ो(gpu,
			REG_A6XX_VBIF_TEST_BUS1_CTRL0,
			REG_A6XX_VBIF_TEST_BUS1_CTRL1,
			1 << i, 12, ptr);

	/* Restore the VBIF घड़ी setting */
	gpu_ग_लिखो(gpu, REG_A6XX_VBIF_CLKON, clk);
पूर्ण

अटल व्योम a6xx_get_debugbus_block(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state,
		स्थिर काष्ठा a6xx_debugbus_block *block,
		काष्ठा a6xx_gpu_state_obj *obj)
अणु
	पूर्णांक i;
	u32 *ptr;

	obj->data = state_kसुस्मृति(a6xx_state, block->count, माप(u64));
	अगर (!obj->data)
		वापस;

	obj->handle = block;

	क्रम (ptr = obj->data, i = 0; i < block->count; i++)
		ptr += debugbus_पढ़ो(gpu, block->id, i, ptr);
पूर्ण

अटल व्योम a6xx_get_cx_debugbus_block(व्योम __iomem *cxdbg,
		काष्ठा a6xx_gpu_state *a6xx_state,
		स्थिर काष्ठा a6xx_debugbus_block *block,
		काष्ठा a6xx_gpu_state_obj *obj)
अणु
	पूर्णांक i;
	u32 *ptr;

	obj->data = state_kसुस्मृति(a6xx_state, block->count, माप(u64));
	अगर (!obj->data)
		वापस;

	obj->handle = block;

	क्रम (ptr = obj->data, i = 0; i < block->count; i++)
		ptr += cx_debugbus_पढ़ो(cxdbg, block->id, i, ptr);
पूर्ण

अटल व्योम a6xx_get_debugbus(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state)
अणु
	काष्ठा resource *res;
	व्योम __iomem *cxdbg = शून्य;
	पूर्णांक nr_debugbus_blocks;

	/* Set up the GX debug bus */

	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_CNTLT,
		A6XX_DBGC_CFG_DBGBUS_CNTLT_SEGT(0xf));

	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_CNTLM,
		A6XX_DBGC_CFG_DBGBUS_CNTLM_ENABLE(0xf));

	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_IVTL_0, 0);
	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_IVTL_1, 0);
	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_IVTL_2, 0);
	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_IVTL_3, 0);

	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_BYTEL_0, 0x76543210);
	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_BYTEL_1, 0xFEDCBA98);

	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_MASKL_0, 0);
	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_MASKL_1, 0);
	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_MASKL_2, 0);
	gpu_ग_लिखो(gpu, REG_A6XX_DBGC_CFG_DBGBUS_MASKL_3, 0);

	/* Set up the CX debug bus - it lives अन्यथाwhere in the प्रणाली so करो a
	 * temporary ioremap क्रम the रेजिस्टरs
	 */
	res = platक्रमm_get_resource_byname(gpu->pdev, IORESOURCE_MEM,
			"cx_dbgc");

	अगर (res)
		cxdbg = ioremap(res->start, resource_size(res));

	अगर (cxdbg) अणु
		cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_CNTLT,
			A6XX_DBGC_CFG_DBGBUS_CNTLT_SEGT(0xf));

		cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_CNTLM,
			A6XX_DBGC_CFG_DBGBUS_CNTLM_ENABLE(0xf));

		cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_IVTL_0, 0);
		cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_IVTL_1, 0);
		cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_IVTL_2, 0);
		cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_IVTL_3, 0);

		cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_BYTEL_0,
			0x76543210);
		cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_BYTEL_1,
			0xFEDCBA98);

		cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_MASKL_0, 0);
		cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_MASKL_1, 0);
		cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_MASKL_2, 0);
		cxdbg_ग_लिखो(cxdbg, REG_A6XX_CX_DBGC_CFG_DBGBUS_MASKL_3, 0);
	पूर्ण

	nr_debugbus_blocks = ARRAY_SIZE(a6xx_debugbus_blocks) +
		(a6xx_has_gbअगर(to_adreno_gpu(gpu)) ? 1 : 0);

	a6xx_state->debugbus = state_kसुस्मृति(a6xx_state, nr_debugbus_blocks,
			माप(*a6xx_state->debugbus));

	अगर (a6xx_state->debugbus) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(a6xx_debugbus_blocks); i++)
			a6xx_get_debugbus_block(gpu,
				a6xx_state,
				&a6xx_debugbus_blocks[i],
				&a6xx_state->debugbus[i]);

		a6xx_state->nr_debugbus = ARRAY_SIZE(a6xx_debugbus_blocks);

		/*
		 * GBIF has same debugbus as of other GPU blocks, fall back to
		 * शेष path अगर GPU uses GBIF, also GBIF uses exactly same
		 * ID as of VBIF.
		 */
		अगर (a6xx_has_gbअगर(to_adreno_gpu(gpu))) अणु
			a6xx_get_debugbus_block(gpu, a6xx_state,
				&a6xx_gbअगर_debugbus_block,
				&a6xx_state->debugbus[i]);

			a6xx_state->nr_debugbus += 1;
		पूर्ण
	पूर्ण

	/*  Dump the VBIF debugbus on applicable tarमाला_लो */
	अगर (!a6xx_has_gbअगर(to_adreno_gpu(gpu))) अणु
		a6xx_state->vbअगर_debugbus =
			state_kसुस्मृति(a6xx_state, 1,
					माप(*a6xx_state->vbअगर_debugbus));

		अगर (a6xx_state->vbअगर_debugbus)
			a6xx_get_vbअगर_debugbus_block(gpu, a6xx_state,
					a6xx_state->vbअगर_debugbus);
	पूर्ण

	अगर (cxdbg) अणु
		a6xx_state->cx_debugbus =
			state_kसुस्मृति(a6xx_state,
			ARRAY_SIZE(a6xx_cx_debugbus_blocks),
			माप(*a6xx_state->cx_debugbus));

		अगर (a6xx_state->cx_debugbus) अणु
			पूर्णांक i;

			क्रम (i = 0; i < ARRAY_SIZE(a6xx_cx_debugbus_blocks); i++)
				a6xx_get_cx_debugbus_block(cxdbg,
					a6xx_state,
					&a6xx_cx_debugbus_blocks[i],
					&a6xx_state->cx_debugbus[i]);

			a6xx_state->nr_cx_debugbus =
				ARRAY_SIZE(a6xx_cx_debugbus_blocks);
		पूर्ण

		iounmap(cxdbg);
	पूर्ण
पूर्ण

#घोषणा RANGE(reg, a) ((reg)[(a) + 1] - (reg)[(a)] + 1)

/* Read a data cluster from behind the AHB aperture */
अटल व्योम a6xx_get_dbgahb_cluster(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state,
		स्थिर काष्ठा a6xx_dbgahb_cluster *dbgahb,
		काष्ठा a6xx_gpu_state_obj *obj,
		काष्ठा a6xx_crashdumper *dumper)
अणु
	u64 *in = dumper->ptr;
	u64 out = dumper->iova + A6XX_CD_DATA_OFFSET;
	माप_प्रकार datasize;
	पूर्णांक i, regcount = 0;

	क्रम (i = 0; i < A6XX_NUM_CONTEXTS; i++) अणु
		पूर्णांक j;

		in += CRASHDUMP_WRITE(in, REG_A6XX_HLSQ_DBG_READ_SEL,
			(dbgahb->statetype + i * 2) << 8);

		क्रम (j = 0; j < dbgahb->count; j += 2) अणु
			पूर्णांक count = RANGE(dbgahb->रेजिस्टरs, j);
			u32 offset = REG_A6XX_HLSQ_DBG_AHB_READ_APERTURE +
				dbgahb->रेजिस्टरs[j] - (dbgahb->base >> 2);

			in += CRASHDUMP_READ(in, offset, count, out);

			out += count * माप(u32);

			अगर (i == 0)
				regcount += count;
		पूर्ण
	पूर्ण

	CRASHDUMP_FINI(in);

	datasize = regcount * A6XX_NUM_CONTEXTS * माप(u32);

	अगर (WARN_ON(datasize > A6XX_CD_DATA_SIZE))
		वापस;

	अगर (a6xx_crashdumper_run(gpu, dumper))
		वापस;

	obj->handle = dbgahb;
	obj->data = state_kmemdup(a6xx_state, dumper->ptr + A6XX_CD_DATA_OFFSET,
		datasize);
पूर्ण

अटल व्योम a6xx_get_dbgahb_clusters(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state,
		काष्ठा a6xx_crashdumper *dumper)
अणु
	पूर्णांक i;

	a6xx_state->dbgahb_clusters = state_kसुस्मृति(a6xx_state,
		ARRAY_SIZE(a6xx_dbgahb_clusters),
		माप(*a6xx_state->dbgahb_clusters));

	अगर (!a6xx_state->dbgahb_clusters)
		वापस;

	a6xx_state->nr_dbgahb_clusters = ARRAY_SIZE(a6xx_dbgahb_clusters);

	क्रम (i = 0; i < ARRAY_SIZE(a6xx_dbgahb_clusters); i++)
		a6xx_get_dbgahb_cluster(gpu, a6xx_state,
			&a6xx_dbgahb_clusters[i],
			&a6xx_state->dbgahb_clusters[i], dumper);
पूर्ण

/* Read a data cluster from the CP aperture with the crashdumper */
अटल व्योम a6xx_get_cluster(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state,
		स्थिर काष्ठा a6xx_cluster *cluster,
		काष्ठा a6xx_gpu_state_obj *obj,
		काष्ठा a6xx_crashdumper *dumper)
अणु
	u64 *in = dumper->ptr;
	u64 out = dumper->iova + A6XX_CD_DATA_OFFSET;
	माप_प्रकार datasize;
	पूर्णांक i, regcount = 0;

	/* Some clusters need a selector रेजिस्टर to be programmed too */
	अगर (cluster->sel_reg)
		in += CRASHDUMP_WRITE(in, cluster->sel_reg, cluster->sel_val);

	क्रम (i = 0; i < A6XX_NUM_CONTEXTS; i++) अणु
		पूर्णांक j;

		in += CRASHDUMP_WRITE(in, REG_A6XX_CP_APERTURE_CNTL_CD,
			(cluster->id << 8) | (i << 4) | i);

		क्रम (j = 0; j < cluster->count; j += 2) अणु
			पूर्णांक count = RANGE(cluster->रेजिस्टरs, j);

			in += CRASHDUMP_READ(in, cluster->रेजिस्टरs[j],
				count, out);

			out += count * माप(u32);

			अगर (i == 0)
				regcount += count;
		पूर्ण
	पूर्ण

	CRASHDUMP_FINI(in);

	datasize = regcount * A6XX_NUM_CONTEXTS * माप(u32);

	अगर (WARN_ON(datasize > A6XX_CD_DATA_SIZE))
		वापस;

	अगर (a6xx_crashdumper_run(gpu, dumper))
		वापस;

	obj->handle = cluster;
	obj->data = state_kmemdup(a6xx_state, dumper->ptr + A6XX_CD_DATA_OFFSET,
		datasize);
पूर्ण

अटल व्योम a6xx_get_clusters(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state,
		काष्ठा a6xx_crashdumper *dumper)
अणु
	पूर्णांक i;

	a6xx_state->clusters = state_kसुस्मृति(a6xx_state,
		ARRAY_SIZE(a6xx_clusters), माप(*a6xx_state->clusters));

	अगर (!a6xx_state->clusters)
		वापस;

	a6xx_state->nr_clusters = ARRAY_SIZE(a6xx_clusters);

	क्रम (i = 0; i < ARRAY_SIZE(a6xx_clusters); i++)
		a6xx_get_cluster(gpu, a6xx_state, &a6xx_clusters[i],
			&a6xx_state->clusters[i], dumper);
पूर्ण

/* Read a shader / debug block from the HLSQ aperture with the crashdumper */
अटल व्योम a6xx_get_shader_block(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state,
		स्थिर काष्ठा a6xx_shader_block *block,
		काष्ठा a6xx_gpu_state_obj *obj,
		काष्ठा a6xx_crashdumper *dumper)
अणु
	u64 *in = dumper->ptr;
	माप_प्रकार datasize = block->size * A6XX_NUM_SHADER_BANKS * माप(u32);
	पूर्णांक i;

	अगर (WARN_ON(datasize > A6XX_CD_DATA_SIZE))
		वापस;

	क्रम (i = 0; i < A6XX_NUM_SHADER_BANKS; i++) अणु
		in += CRASHDUMP_WRITE(in, REG_A6XX_HLSQ_DBG_READ_SEL,
			(block->type << 8) | i);

		in += CRASHDUMP_READ(in, REG_A6XX_HLSQ_DBG_AHB_READ_APERTURE,
			block->size, dumper->iova + A6XX_CD_DATA_OFFSET);
	पूर्ण

	CRASHDUMP_FINI(in);

	अगर (a6xx_crashdumper_run(gpu, dumper))
		वापस;

	obj->handle = block;
	obj->data = state_kmemdup(a6xx_state, dumper->ptr + A6XX_CD_DATA_OFFSET,
		datasize);
पूर्ण

अटल व्योम a6xx_get_shaders(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state,
		काष्ठा a6xx_crashdumper *dumper)
अणु
	पूर्णांक i;

	a6xx_state->shaders = state_kसुस्मृति(a6xx_state,
		ARRAY_SIZE(a6xx_shader_blocks), माप(*a6xx_state->shaders));

	अगर (!a6xx_state->shaders)
		वापस;

	a6xx_state->nr_shaders = ARRAY_SIZE(a6xx_shader_blocks);

	क्रम (i = 0; i < ARRAY_SIZE(a6xx_shader_blocks); i++)
		a6xx_get_shader_block(gpu, a6xx_state, &a6xx_shader_blocks[i],
			&a6xx_state->shaders[i], dumper);
पूर्ण

/* Read रेजिस्टरs from behind the HLSQ aperture with the crashdumper */
अटल व्योम a6xx_get_crashdumper_hlsq_रेजिस्टरs(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state,
		स्थिर काष्ठा a6xx_रेजिस्टरs *regs,
		काष्ठा a6xx_gpu_state_obj *obj,
		काष्ठा a6xx_crashdumper *dumper)

अणु
	u64 *in = dumper->ptr;
	u64 out = dumper->iova + A6XX_CD_DATA_OFFSET;
	पूर्णांक i, regcount = 0;

	in += CRASHDUMP_WRITE(in, REG_A6XX_HLSQ_DBG_READ_SEL, regs->val1);

	क्रम (i = 0; i < regs->count; i += 2) अणु
		u32 count = RANGE(regs->रेजिस्टरs, i);
		u32 offset = REG_A6XX_HLSQ_DBG_AHB_READ_APERTURE +
			regs->रेजिस्टरs[i] - (regs->val0 >> 2);

		in += CRASHDUMP_READ(in, offset, count, out);

		out += count * माप(u32);
		regcount += count;
	पूर्ण

	CRASHDUMP_FINI(in);

	अगर (WARN_ON((regcount * माप(u32)) > A6XX_CD_DATA_SIZE))
		वापस;

	अगर (a6xx_crashdumper_run(gpu, dumper))
		वापस;

	obj->handle = regs;
	obj->data = state_kmemdup(a6xx_state, dumper->ptr + A6XX_CD_DATA_OFFSET,
		regcount * माप(u32));
पूर्ण

/* Read a block of रेजिस्टरs using the crashdumper */
अटल व्योम a6xx_get_crashdumper_रेजिस्टरs(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state,
		स्थिर काष्ठा a6xx_रेजिस्टरs *regs,
		काष्ठा a6xx_gpu_state_obj *obj,
		काष्ठा a6xx_crashdumper *dumper)

अणु
	u64 *in = dumper->ptr;
	u64 out = dumper->iova + A6XX_CD_DATA_OFFSET;
	पूर्णांक i, regcount = 0;

	/* Some blocks might need to program a selector रेजिस्टर first */
	अगर (regs->val0)
		in += CRASHDUMP_WRITE(in, regs->val0, regs->val1);

	क्रम (i = 0; i < regs->count; i += 2) अणु
		u32 count = RANGE(regs->रेजिस्टरs, i);

		in += CRASHDUMP_READ(in, regs->रेजिस्टरs[i], count, out);

		out += count * माप(u32);
		regcount += count;
	पूर्ण

	CRASHDUMP_FINI(in);

	अगर (WARN_ON((regcount * माप(u32)) > A6XX_CD_DATA_SIZE))
		वापस;

	अगर (a6xx_crashdumper_run(gpu, dumper))
		वापस;

	obj->handle = regs;
	obj->data = state_kmemdup(a6xx_state, dumper->ptr + A6XX_CD_DATA_OFFSET,
		regcount * माप(u32));
पूर्ण

/* Read a block of रेजिस्टरs via AHB */
अटल व्योम a6xx_get_ahb_gpu_रेजिस्टरs(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state,
		स्थिर काष्ठा a6xx_रेजिस्टरs *regs,
		काष्ठा a6xx_gpu_state_obj *obj)
अणु
	पूर्णांक i, regcount = 0, index = 0;

	क्रम (i = 0; i < regs->count; i += 2)
		regcount += RANGE(regs->रेजिस्टरs, i);

	obj->handle = (स्थिर व्योम *) regs;
	obj->data = state_kसुस्मृति(a6xx_state, regcount, माप(u32));
	अगर (!obj->data)
		वापस;

	क्रम (i = 0; i < regs->count; i += 2) अणु
		u32 count = RANGE(regs->रेजिस्टरs, i);
		पूर्णांक j;

		क्रम (j = 0; j < count; j++)
			obj->data[index++] = gpu_पढ़ो(gpu,
				regs->रेजिस्टरs[i] + j);
	पूर्ण
पूर्ण

/* Read a block of GMU रेजिस्टरs */
अटल व्योम _a6xx_get_gmu_रेजिस्टरs(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state,
		स्थिर काष्ठा a6xx_रेजिस्टरs *regs,
		काष्ठा a6xx_gpu_state_obj *obj,
		bool rscc)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	काष्ठा a6xx_gmu *gmu = &a6xx_gpu->gmu;
	पूर्णांक i, regcount = 0, index = 0;

	क्रम (i = 0; i < regs->count; i += 2)
		regcount += RANGE(regs->रेजिस्टरs, i);

	obj->handle = (स्थिर व्योम *) regs;
	obj->data = state_kसुस्मृति(a6xx_state, regcount, माप(u32));
	अगर (!obj->data)
		वापस;

	क्रम (i = 0; i < regs->count; i += 2) अणु
		u32 count = RANGE(regs->रेजिस्टरs, i);
		पूर्णांक j;

		क्रम (j = 0; j < count; j++) अणु
			u32 offset = regs->रेजिस्टरs[i] + j;
			u32 val;

			अगर (rscc)
				val = gmu_पढ़ो_rscc(gmu, offset);
			अन्यथा
				val = gmu_पढ़ो(gmu, offset);

			obj->data[index++] = val;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम a6xx_get_gmu_रेजिस्टरs(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);

	a6xx_state->gmu_रेजिस्टरs = state_kसुस्मृति(a6xx_state,
		2, माप(*a6xx_state->gmu_रेजिस्टरs));

	अगर (!a6xx_state->gmu_रेजिस्टरs)
		वापस;

	a6xx_state->nr_gmu_रेजिस्टरs = 2;

	/* Get the CX GMU रेजिस्टरs from AHB */
	_a6xx_get_gmu_रेजिस्टरs(gpu, a6xx_state, &a6xx_gmu_reglist[0],
		&a6xx_state->gmu_रेजिस्टरs[0], false);
	_a6xx_get_gmu_रेजिस्टरs(gpu, a6xx_state, &a6xx_gmu_reglist[1],
		&a6xx_state->gmu_रेजिस्टरs[1], true);

	अगर (!a6xx_gmu_gx_is_on(&a6xx_gpu->gmu))
		वापस;

	/* Set the fence to ALLOW mode so we can access the रेजिस्टरs */
	gpu_ग_लिखो(gpu, REG_A6XX_GMU_AO_AHB_FENCE_CTRL, 0);

	_a6xx_get_gmu_रेजिस्टरs(gpu, a6xx_state, &a6xx_gmu_reglist[2],
		&a6xx_state->gmu_रेजिस्टरs[2], false);
पूर्ण

#घोषणा A6XX_GBIF_REGLIST_SIZE   1
अटल व्योम a6xx_get_रेजिस्टरs(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state,
		काष्ठा a6xx_crashdumper *dumper)
अणु
	पूर्णांक i, count = ARRAY_SIZE(a6xx_ahb_reglist) +
		ARRAY_SIZE(a6xx_reglist) +
		ARRAY_SIZE(a6xx_hlsq_reglist) + A6XX_GBIF_REGLIST_SIZE;
	पूर्णांक index = 0;
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);

	a6xx_state->रेजिस्टरs = state_kसुस्मृति(a6xx_state,
		count, माप(*a6xx_state->रेजिस्टरs));

	अगर (!a6xx_state->रेजिस्टरs)
		वापस;

	a6xx_state->nr_रेजिस्टरs = count;

	क्रम (i = 0; i < ARRAY_SIZE(a6xx_ahb_reglist); i++)
		a6xx_get_ahb_gpu_रेजिस्टरs(gpu,
			a6xx_state, &a6xx_ahb_reglist[i],
			&a6xx_state->रेजिस्टरs[index++]);

	अगर (a6xx_has_gbअगर(adreno_gpu))
		a6xx_get_ahb_gpu_रेजिस्टरs(gpu,
				a6xx_state, &a6xx_gbअगर_reglist,
				&a6xx_state->रेजिस्टरs[index++]);
	अन्यथा
		a6xx_get_ahb_gpu_रेजिस्टरs(gpu,
				a6xx_state, &a6xx_vbअगर_reglist,
				&a6xx_state->रेजिस्टरs[index++]);

	क्रम (i = 0; i < ARRAY_SIZE(a6xx_reglist); i++)
		a6xx_get_crashdumper_रेजिस्टरs(gpu,
			a6xx_state, &a6xx_reglist[i],
			&a6xx_state->रेजिस्टरs[index++],
			dumper);

	क्रम (i = 0; i < ARRAY_SIZE(a6xx_hlsq_reglist); i++)
		a6xx_get_crashdumper_hlsq_रेजिस्टरs(gpu,
			a6xx_state, &a6xx_hlsq_reglist[i],
			&a6xx_state->रेजिस्टरs[index++],
			dumper);
पूर्ण

/* Read a block of data from an indexed रेजिस्टर pair */
अटल व्योम a6xx_get_indexed_regs(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state,
		स्थिर काष्ठा a6xx_indexed_रेजिस्टरs *indexed,
		काष्ठा a6xx_gpu_state_obj *obj)
अणु
	पूर्णांक i;

	obj->handle = (स्थिर व्योम *) indexed;
	obj->data = state_kसुस्मृति(a6xx_state, indexed->count, माप(u32));
	अगर (!obj->data)
		वापस;

	/* All the indexed banks start at address 0 */
	gpu_ग_लिखो(gpu, indexed->addr, 0);

	/* Read the data - each पढ़ो increments the पूर्णांकernal address by 1 */
	क्रम (i = 0; i < indexed->count; i++)
		obj->data[i] = gpu_पढ़ो(gpu, indexed->data);
पूर्ण

अटल व्योम a6xx_get_indexed_रेजिस्टरs(काष्ठा msm_gpu *gpu,
		काष्ठा a6xx_gpu_state *a6xx_state)
अणु
	u32 mempool_size;
	पूर्णांक count = ARRAY_SIZE(a6xx_indexed_reglist) + 1;
	पूर्णांक i;

	a6xx_state->indexed_regs = state_kसुस्मृति(a6xx_state, count,
		माप(*a6xx_state->indexed_regs));
	अगर (!a6xx_state->indexed_regs)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(a6xx_indexed_reglist); i++)
		a6xx_get_indexed_regs(gpu, a6xx_state, &a6xx_indexed_reglist[i],
			&a6xx_state->indexed_regs[i]);

	/* Set the CP mempool size to 0 to stabilize it जबतक dumping */
	mempool_size = gpu_पढ़ो(gpu, REG_A6XX_CP_MEM_POOL_SIZE);
	gpu_ग_लिखो(gpu, REG_A6XX_CP_MEM_POOL_SIZE, 0);

	/* Get the contents of the CP mempool */
	a6xx_get_indexed_regs(gpu, a6xx_state, &a6xx_cp_mempool_indexed,
		&a6xx_state->indexed_regs[i]);

	/*
	 * Offset 0x2000 in the mempool is the size - copy the saved size over
	 * so the data is consistent
	 */
	a6xx_state->indexed_regs[i].data[0x2000] = mempool_size;

	/* Restore the size in the hardware */
	gpu_ग_लिखो(gpu, REG_A6XX_CP_MEM_POOL_SIZE, mempool_size);

	a6xx_state->nr_indexed_regs = count;
पूर्ण

काष्ठा msm_gpu_state *a6xx_gpu_state_get(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा a6xx_crashdumper dumper = अणु 0 पूर्ण;
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	काष्ठा a6xx_gpu_state *a6xx_state = kzalloc(माप(*a6xx_state),
		GFP_KERNEL);

	अगर (!a6xx_state)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&a6xx_state->objs);

	/* Get the generic state from the adreno core */
	adreno_gpu_state_get(gpu, &a6xx_state->base);

	a6xx_get_gmu_रेजिस्टरs(gpu, a6xx_state);

	/* If GX isn't on the rest of the data isn't going to be accessible */
	अगर (!a6xx_gmu_gx_is_on(&a6xx_gpu->gmu))
		वापस &a6xx_state->base;

	/* Get the banks of indexed रेजिस्टरs */
	a6xx_get_indexed_रेजिस्टरs(gpu, a6xx_state);

	/* Try to initialize the crashdumper */
	अगर (!a6xx_crashdumper_init(gpu, &dumper)) अणु
		a6xx_get_रेजिस्टरs(gpu, a6xx_state, &dumper);
		a6xx_get_shaders(gpu, a6xx_state, &dumper);
		a6xx_get_clusters(gpu, a6xx_state, &dumper);
		a6xx_get_dbgahb_clusters(gpu, a6xx_state, &dumper);

		msm_gem_kernel_put(dumper.bo, gpu->aspace, true);
	पूर्ण

	अगर (snapshot_debugbus)
		a6xx_get_debugbus(gpu, a6xx_state);

	वापस  &a6xx_state->base;
पूर्ण

अटल व्योम a6xx_gpu_state_destroy(काष्ठा kref *kref)
अणु
	काष्ठा a6xx_state_memobj *obj, *पंचांगp;
	काष्ठा msm_gpu_state *state = container_of(kref,
			काष्ठा msm_gpu_state, ref);
	काष्ठा a6xx_gpu_state *a6xx_state = container_of(state,
			काष्ठा a6xx_gpu_state, base);

	list_क्रम_each_entry_safe(obj, पंचांगp, &a6xx_state->objs, node)
		kमुक्त(obj);

	adreno_gpu_state_destroy(state);
	kमुक्त(a6xx_state);
पूर्ण

पूर्णांक a6xx_gpu_state_put(काष्ठा msm_gpu_state *state)
अणु
	अगर (IS_ERR_OR_शून्य(state))
		वापस 1;

	वापस kref_put(&state->ref, a6xx_gpu_state_destroy);
पूर्ण

अटल व्योम a6xx_show_रेजिस्टरs(स्थिर u32 *रेजिस्टरs, u32 *data, माप_प्रकार count,
		काष्ठा drm_prपूर्णांकer *p)
अणु
	पूर्णांक i, index = 0;

	अगर (!data)
		वापस;

	क्रम (i = 0; i < count; i += 2) अणु
		u32 count = RANGE(रेजिस्टरs, i);
		u32 offset = रेजिस्टरs[i];
		पूर्णांक j;

		क्रम (j = 0; j < count; index++, offset++, j++) अणु
			अगर (data[index] == 0xdeafbead)
				जारी;

			drm_म_लिखो(p, "  - { offset: 0x%06x, value: 0x%08x }\n",
				offset << 2, data[index]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_ascii85(काष्ठा drm_prपूर्णांकer *p, माप_प्रकार len, u32 *data)
अणु
	अक्षर out[ASCII85_BUFSZ];
	दीर्घ i, l, datalen = 0;

	क्रम (i = 0; i < len >> 2; i++) अणु
		अगर (data[i])
			datalen = (i + 1) << 2;
	पूर्ण

	अगर (datalen == 0)
		वापस;

	drm_माला_दो(p, "    data: !!ascii85 |\n");
	drm_माला_दो(p, "      ");


	l = ascii85_encode_len(datalen);

	क्रम (i = 0; i < l; i++)
		drm_माला_दो(p, ascii85_encode(data[i], out));

	drm_माला_दो(p, "\n");
पूर्ण

अटल व्योम prपूर्णांक_name(काष्ठा drm_prपूर्णांकer *p, स्थिर अक्षर *fmt, स्थिर अक्षर *name)
अणु
	drm_माला_दो(p, fmt);
	drm_माला_दो(p, name);
	drm_माला_दो(p, "\n");
पूर्ण

अटल व्योम a6xx_show_shader(काष्ठा a6xx_gpu_state_obj *obj,
		काष्ठा drm_prपूर्णांकer *p)
अणु
	स्थिर काष्ठा a6xx_shader_block *block = obj->handle;
	पूर्णांक i;

	अगर (!obj->handle)
		वापस;

	prपूर्णांक_name(p, "  - type: ", block->name);

	क्रम (i = 0; i < A6XX_NUM_SHADER_BANKS; i++) अणु
		drm_म_लिखो(p, "    - bank: %d\n", i);
		drm_म_लिखो(p, "      size: %d\n", block->size);

		अगर (!obj->data)
			जारी;

		prपूर्णांक_ascii85(p, block->size << 2,
			obj->data + (block->size * i));
	पूर्ण
पूर्ण

अटल व्योम a6xx_show_cluster_data(स्थिर u32 *रेजिस्टरs, पूर्णांक size, u32 *data,
		काष्ठा drm_prपूर्णांकer *p)
अणु
	पूर्णांक ctx, index = 0;

	क्रम (ctx = 0; ctx < A6XX_NUM_CONTEXTS; ctx++) अणु
		पूर्णांक j;

		drm_म_लिखो(p, "    - context: %d\n", ctx);

		क्रम (j = 0; j < size; j += 2) अणु
			u32 count = RANGE(रेजिस्टरs, j);
			u32 offset = रेजिस्टरs[j];
			पूर्णांक k;

			क्रम (k = 0; k < count; index++, offset++, k++) अणु
				अगर (data[index] == 0xdeafbead)
					जारी;

				drm_म_लिखो(p, "      - { offset: 0x%06x, value: 0x%08x }\n",
					offset << 2, data[index]);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम a6xx_show_dbgahb_cluster(काष्ठा a6xx_gpu_state_obj *obj,
		काष्ठा drm_prपूर्णांकer *p)
अणु
	स्थिर काष्ठा a6xx_dbgahb_cluster *dbgahb = obj->handle;

	अगर (dbgahb) अणु
		prपूर्णांक_name(p, "  - cluster-name: ", dbgahb->name);
		a6xx_show_cluster_data(dbgahb->रेजिस्टरs, dbgahb->count,
			obj->data, p);
	पूर्ण
पूर्ण

अटल व्योम a6xx_show_cluster(काष्ठा a6xx_gpu_state_obj *obj,
		काष्ठा drm_prपूर्णांकer *p)
अणु
	स्थिर काष्ठा a6xx_cluster *cluster = obj->handle;

	अगर (cluster) अणु
		prपूर्णांक_name(p, "  - cluster-name: ", cluster->name);
		a6xx_show_cluster_data(cluster->रेजिस्टरs, cluster->count,
			obj->data, p);
	पूर्ण
पूर्ण

अटल व्योम a6xx_show_indexed_regs(काष्ठा a6xx_gpu_state_obj *obj,
		काष्ठा drm_prपूर्णांकer *p)
अणु
	स्थिर काष्ठा a6xx_indexed_रेजिस्टरs *indexed = obj->handle;

	अगर (!indexed)
		वापस;

	prपूर्णांक_name(p, "  - regs-name: ", indexed->name);
	drm_म_लिखो(p, "    dwords: %d\n", indexed->count);

	prपूर्णांक_ascii85(p, indexed->count << 2, obj->data);
पूर्ण

अटल व्योम a6xx_show_debugbus_block(स्थिर काष्ठा a6xx_debugbus_block *block,
		u32 *data, काष्ठा drm_prपूर्णांकer *p)
अणु
	अगर (block) अणु
		prपूर्णांक_name(p, "  - debugbus-block: ", block->name);

		/*
		 * count क्रम regular debugbus data is in quadwords,
		 * but prपूर्णांक the size in dwords क्रम consistency
		 */
		drm_म_लिखो(p, "    count: %d\n", block->count << 1);

		prपूर्णांक_ascii85(p, block->count << 3, data);
	पूर्ण
पूर्ण

अटल व्योम a6xx_show_debugbus(काष्ठा a6xx_gpu_state *a6xx_state,
		काष्ठा drm_prपूर्णांकer *p)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < a6xx_state->nr_debugbus; i++) अणु
		काष्ठा a6xx_gpu_state_obj *obj = &a6xx_state->debugbus[i];

		a6xx_show_debugbus_block(obj->handle, obj->data, p);
	पूर्ण

	अगर (a6xx_state->vbअगर_debugbus) अणु
		काष्ठा a6xx_gpu_state_obj *obj = a6xx_state->vbअगर_debugbus;

		drm_माला_दो(p, "  - debugbus-block: A6XX_DBGBUS_VBIF\n");
		drm_म_लिखो(p, "    count: %d\n", VBIF_DEBUGBUS_BLOCK_SIZE);

		/* vbअगर debugbus data is in dwords.  Confusing, huh? */
		prपूर्णांक_ascii85(p, VBIF_DEBUGBUS_BLOCK_SIZE << 2, obj->data);
	पूर्ण

	क्रम (i = 0; i < a6xx_state->nr_cx_debugbus; i++) अणु
		काष्ठा a6xx_gpu_state_obj *obj = &a6xx_state->cx_debugbus[i];

		a6xx_show_debugbus_block(obj->handle, obj->data, p);
	पूर्ण
पूर्ण

व्योम a6xx_show(काष्ठा msm_gpu *gpu, काष्ठा msm_gpu_state *state,
		काष्ठा drm_prपूर्णांकer *p)
अणु
	काष्ठा a6xx_gpu_state *a6xx_state = container_of(state,
			काष्ठा a6xx_gpu_state, base);
	पूर्णांक i;

	अगर (IS_ERR_OR_शून्य(state))
		वापस;

	adreno_show(gpu, state, p);

	drm_माला_दो(p, "registers:\n");
	क्रम (i = 0; i < a6xx_state->nr_रेजिस्टरs; i++) अणु
		काष्ठा a6xx_gpu_state_obj *obj = &a6xx_state->रेजिस्टरs[i];
		स्थिर काष्ठा a6xx_रेजिस्टरs *regs = obj->handle;

		अगर (!obj->handle)
			जारी;

		a6xx_show_रेजिस्टरs(regs->रेजिस्टरs, obj->data, regs->count, p);
	पूर्ण

	drm_माला_दो(p, "registers-gmu:\n");
	क्रम (i = 0; i < a6xx_state->nr_gmu_रेजिस्टरs; i++) अणु
		काष्ठा a6xx_gpu_state_obj *obj = &a6xx_state->gmu_रेजिस्टरs[i];
		स्थिर काष्ठा a6xx_रेजिस्टरs *regs = obj->handle;

		अगर (!obj->handle)
			जारी;

		a6xx_show_रेजिस्टरs(regs->रेजिस्टरs, obj->data, regs->count, p);
	पूर्ण

	drm_माला_दो(p, "indexed-registers:\n");
	क्रम (i = 0; i < a6xx_state->nr_indexed_regs; i++)
		a6xx_show_indexed_regs(&a6xx_state->indexed_regs[i], p);

	drm_माला_दो(p, "shader-blocks:\n");
	क्रम (i = 0; i < a6xx_state->nr_shaders; i++)
		a6xx_show_shader(&a6xx_state->shaders[i], p);

	drm_माला_दो(p, "clusters:\n");
	क्रम (i = 0; i < a6xx_state->nr_clusters; i++)
		a6xx_show_cluster(&a6xx_state->clusters[i], p);

	क्रम (i = 0; i < a6xx_state->nr_dbgahb_clusters; i++)
		a6xx_show_dbgahb_cluster(&a6xx_state->dbgahb_clusters[i], p);

	drm_माला_दो(p, "debugbus:\n");
	a6xx_show_debugbus(a6xx_state, p);
पूर्ण
