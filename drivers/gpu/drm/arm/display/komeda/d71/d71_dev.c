<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */

#समावेश <drm/drm_prपूर्णांक.h>
#समावेश "d71_dev.h"
#समावेश "malidp_io.h"

अटल u64 get_lpu_event(काष्ठा d71_pipeline *d71_pipeline)
अणु
	u32 __iomem *reg = d71_pipeline->lpu_addr;
	u32 status, raw_status;
	u64 evts = 0ULL;

	raw_status = malidp_पढ़ो32(reg, BLK_IRQ_RAW_STATUS);
	अगर (raw_status & LPU_IRQ_IBSY)
		evts |= KOMEDA_EVENT_IBSY;
	अगर (raw_status & LPU_IRQ_EOW)
		evts |= KOMEDA_EVENT_EOW;
	अगर (raw_status & LPU_IRQ_OVR)
		evts |= KOMEDA_EVENT_OVR;

	अगर (raw_status & (LPU_IRQ_ERR | LPU_IRQ_IBSY | LPU_IRQ_OVR)) अणु
		u32 restore = 0, tbu_status;
		/* Check error of LPU status */
		status = malidp_पढ़ो32(reg, BLK_STATUS);
		अगर (status & LPU_STATUS_AXIE) अणु
			restore |= LPU_STATUS_AXIE;
			evts |= KOMEDA_ERR_AXIE;
		पूर्ण
		अगर (status & LPU_STATUS_ACE0) अणु
			restore |= LPU_STATUS_ACE0;
			evts |= KOMEDA_ERR_ACE0;
		पूर्ण
		अगर (status & LPU_STATUS_ACE1) अणु
			restore |= LPU_STATUS_ACE1;
			evts |= KOMEDA_ERR_ACE1;
		पूर्ण
		अगर (status & LPU_STATUS_ACE2) अणु
			restore |= LPU_STATUS_ACE2;
			evts |= KOMEDA_ERR_ACE2;
		पूर्ण
		अगर (status & LPU_STATUS_ACE3) अणु
			restore |= LPU_STATUS_ACE3;
			evts |= KOMEDA_ERR_ACE3;
		पूर्ण
		अगर (status & LPU_STATUS_FEMPTY) अणु
			restore |= LPU_STATUS_FEMPTY;
			evts |= KOMEDA_EVENT_EMPTY;
		पूर्ण
		अगर (status & LPU_STATUS_FFULL) अणु
			restore |= LPU_STATUS_FFULL;
			evts |= KOMEDA_EVENT_FULL;
		पूर्ण

		अगर (restore != 0)
			malidp_ग_लिखो32_mask(reg, BLK_STATUS, restore, 0);

		restore = 0;
		/* Check errors of TBU status */
		tbu_status = malidp_पढ़ो32(reg, LPU_TBU_STATUS);
		अगर (tbu_status & LPU_TBU_STATUS_TCF) अणु
			restore |= LPU_TBU_STATUS_TCF;
			evts |= KOMEDA_ERR_TCF;
		पूर्ण
		अगर (tbu_status & LPU_TBU_STATUS_TTNG) अणु
			restore |= LPU_TBU_STATUS_TTNG;
			evts |= KOMEDA_ERR_TTNG;
		पूर्ण
		अगर (tbu_status & LPU_TBU_STATUS_TITR) अणु
			restore |= LPU_TBU_STATUS_TITR;
			evts |= KOMEDA_ERR_TITR;
		पूर्ण
		अगर (tbu_status & LPU_TBU_STATUS_TEMR) अणु
			restore |= LPU_TBU_STATUS_TEMR;
			evts |= KOMEDA_ERR_TEMR;
		पूर्ण
		अगर (tbu_status & LPU_TBU_STATUS_TTF) अणु
			restore |= LPU_TBU_STATUS_TTF;
			evts |= KOMEDA_ERR_TTF;
		पूर्ण
		अगर (restore != 0)
			malidp_ग_लिखो32_mask(reg, LPU_TBU_STATUS, restore, 0);
	पूर्ण

	malidp_ग_लिखो32(reg, BLK_IRQ_CLEAR, raw_status);
	वापस evts;
पूर्ण

अटल u64 get_cu_event(काष्ठा d71_pipeline *d71_pipeline)
अणु
	u32 __iomem *reg = d71_pipeline->cu_addr;
	u32 status, raw_status;
	u64 evts = 0ULL;

	raw_status = malidp_पढ़ो32(reg, BLK_IRQ_RAW_STATUS);
	अगर (raw_status & CU_IRQ_OVR)
		evts |= KOMEDA_EVENT_OVR;

	अगर (raw_status & (CU_IRQ_ERR | CU_IRQ_OVR)) अणु
		status = malidp_पढ़ो32(reg, BLK_STATUS) & 0x7FFFFFFF;
		अगर (status & CU_STATUS_CPE)
			evts |= KOMEDA_ERR_CPE;
		अगर (status & CU_STATUS_ZME)
			evts |= KOMEDA_ERR_ZME;
		अगर (status & CU_STATUS_CFGE)
			evts |= KOMEDA_ERR_CFGE;
		अगर (status)
			malidp_ग_लिखो32_mask(reg, BLK_STATUS, status, 0);
	पूर्ण

	malidp_ग_लिखो32(reg, BLK_IRQ_CLEAR, raw_status);

	वापस evts;
पूर्ण

अटल u64 get_करोu_event(काष्ठा d71_pipeline *d71_pipeline)
अणु
	u32 __iomem *reg = d71_pipeline->करोu_addr;
	u32 status, raw_status;
	u64 evts = 0ULL;

	raw_status = malidp_पढ़ो32(reg, BLK_IRQ_RAW_STATUS);
	अगर (raw_status & DOU_IRQ_PL0)
		evts |= KOMEDA_EVENT_VSYNC;
	अगर (raw_status & DOU_IRQ_UND)
		evts |= KOMEDA_EVENT_URUN;

	अगर (raw_status & (DOU_IRQ_ERR | DOU_IRQ_UND)) अणु
		u32 restore  = 0;

		status = malidp_पढ़ो32(reg, BLK_STATUS);
		अगर (status & DOU_STATUS_DRIFTTO) अणु
			restore |= DOU_STATUS_DRIFTTO;
			evts |= KOMEDA_ERR_DRIFTTO;
		पूर्ण
		अगर (status & DOU_STATUS_FRAMETO) अणु
			restore |= DOU_STATUS_FRAMETO;
			evts |= KOMEDA_ERR_FRAMETO;
		पूर्ण
		अगर (status & DOU_STATUS_TETO) अणु
			restore |= DOU_STATUS_TETO;
			evts |= KOMEDA_ERR_TETO;
		पूर्ण
		अगर (status & DOU_STATUS_CSCE) अणु
			restore |= DOU_STATUS_CSCE;
			evts |= KOMEDA_ERR_CSCE;
		पूर्ण

		अगर (restore != 0)
			malidp_ग_लिखो32_mask(reg, BLK_STATUS, restore, 0);
	पूर्ण

	malidp_ग_लिखो32(reg, BLK_IRQ_CLEAR, raw_status);
	वापस evts;
पूर्ण

अटल u64 get_pipeline_event(काष्ठा d71_pipeline *d71_pipeline, u32 gcu_status)
अणु
	u32 evts = 0ULL;

	अगर (gcu_status & (GLB_IRQ_STATUS_LPU0 | GLB_IRQ_STATUS_LPU1))
		evts |= get_lpu_event(d71_pipeline);

	अगर (gcu_status & (GLB_IRQ_STATUS_CU0 | GLB_IRQ_STATUS_CU1))
		evts |= get_cu_event(d71_pipeline);

	अगर (gcu_status & (GLB_IRQ_STATUS_DOU0 | GLB_IRQ_STATUS_DOU1))
		evts |= get_करोu_event(d71_pipeline);

	वापस evts;
पूर्ण

अटल irqवापस_t
d71_irq_handler(काष्ठा komeda_dev *mdev, काष्ठा komeda_events *evts)
अणु
	काष्ठा d71_dev *d71 = mdev->chip_data;
	u32 status, gcu_status, raw_status;

	gcu_status = malidp_पढ़ो32(d71->gcu_addr, GLB_IRQ_STATUS);

	अगर (gcu_status & GLB_IRQ_STATUS_GCU) अणु
		raw_status = malidp_पढ़ो32(d71->gcu_addr, BLK_IRQ_RAW_STATUS);
		अगर (raw_status & GCU_IRQ_CVAL0)
			evts->pipes[0] |= KOMEDA_EVENT_FLIP;
		अगर (raw_status & GCU_IRQ_CVAL1)
			evts->pipes[1] |= KOMEDA_EVENT_FLIP;
		अगर (raw_status & GCU_IRQ_ERR) अणु
			status = malidp_पढ़ो32(d71->gcu_addr, BLK_STATUS);
			अगर (status & GCU_STATUS_MERR) अणु
				evts->global |= KOMEDA_ERR_MERR;
				malidp_ग_लिखो32_mask(d71->gcu_addr, BLK_STATUS,
						    GCU_STATUS_MERR, 0);
			पूर्ण
		पूर्ण

		malidp_ग_लिखो32(d71->gcu_addr, BLK_IRQ_CLEAR, raw_status);
	पूर्ण

	अगर (gcu_status & GLB_IRQ_STATUS_PIPE0)
		evts->pipes[0] |= get_pipeline_event(d71->pipes[0], gcu_status);

	अगर (gcu_status & GLB_IRQ_STATUS_PIPE1)
		evts->pipes[1] |= get_pipeline_event(d71->pipes[1], gcu_status);

	वापस IRQ_RETVAL(gcu_status);
पूर्ण

#घोषणा ENABLED_GCU_IRQS	(GCU_IRQ_CVAL0 | GCU_IRQ_CVAL1 | \
				 GCU_IRQ_MODE | GCU_IRQ_ERR)
#घोषणा ENABLED_LPU_IRQS	(LPU_IRQ_IBSY | LPU_IRQ_ERR | LPU_IRQ_EOW)
#घोषणा ENABLED_CU_IRQS		(CU_IRQ_OVR | CU_IRQ_ERR)
#घोषणा ENABLED_DOU_IRQS	(DOU_IRQ_UND | DOU_IRQ_ERR)

अटल पूर्णांक d71_enable_irq(काष्ठा komeda_dev *mdev)
अणु
	काष्ठा d71_dev *d71 = mdev->chip_data;
	काष्ठा d71_pipeline *pipe;
	u32 i;

	malidp_ग_लिखो32_mask(d71->gcu_addr, BLK_IRQ_MASK,
			    ENABLED_GCU_IRQS, ENABLED_GCU_IRQS);
	क्रम (i = 0; i < d71->num_pipelines; i++) अणु
		pipe = d71->pipes[i];
		malidp_ग_लिखो32_mask(pipe->cu_addr,  BLK_IRQ_MASK,
				    ENABLED_CU_IRQS, ENABLED_CU_IRQS);
		malidp_ग_लिखो32_mask(pipe->lpu_addr, BLK_IRQ_MASK,
				    ENABLED_LPU_IRQS, ENABLED_LPU_IRQS);
		malidp_ग_लिखो32_mask(pipe->करोu_addr, BLK_IRQ_MASK,
				    ENABLED_DOU_IRQS, ENABLED_DOU_IRQS);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक d71_disable_irq(काष्ठा komeda_dev *mdev)
अणु
	काष्ठा d71_dev *d71 = mdev->chip_data;
	काष्ठा d71_pipeline *pipe;
	u32 i;

	malidp_ग_लिखो32_mask(d71->gcu_addr, BLK_IRQ_MASK, ENABLED_GCU_IRQS, 0);
	क्रम (i = 0; i < d71->num_pipelines; i++) अणु
		pipe = d71->pipes[i];
		malidp_ग_लिखो32_mask(pipe->cu_addr,  BLK_IRQ_MASK,
				    ENABLED_CU_IRQS, 0);
		malidp_ग_लिखो32_mask(pipe->lpu_addr, BLK_IRQ_MASK,
				    ENABLED_LPU_IRQS, 0);
		malidp_ग_लिखो32_mask(pipe->करोu_addr, BLK_IRQ_MASK,
				    ENABLED_DOU_IRQS, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम d71_on_off_vblank(काष्ठा komeda_dev *mdev, पूर्णांक master_pipe, bool on)
अणु
	काष्ठा d71_dev *d71 = mdev->chip_data;
	काष्ठा d71_pipeline *pipe = d71->pipes[master_pipe];

	malidp_ग_लिखो32_mask(pipe->करोu_addr, BLK_IRQ_MASK,
			    DOU_IRQ_PL0, on ? DOU_IRQ_PL0 : 0);
पूर्ण

अटल पूर्णांक to_d71_opmode(पूर्णांक core_mode)
अणु
	चयन (core_mode) अणु
	हाल KOMEDA_MODE_DISP0:
		वापस DO0_ACTIVE_MODE;
	हाल KOMEDA_MODE_DISP1:
		वापस DO1_ACTIVE_MODE;
	हाल KOMEDA_MODE_DUAL_DISP:
		वापस DO01_ACTIVE_MODE;
	हाल KOMEDA_MODE_INACTIVE:
		वापस INACTIVE_MODE;
	शेष:
		WARN(1, "Unknown operation mode");
		वापस INACTIVE_MODE;
	पूर्ण
पूर्ण

अटल पूर्णांक d71_change_opmode(काष्ठा komeda_dev *mdev, पूर्णांक new_mode)
अणु
	काष्ठा d71_dev *d71 = mdev->chip_data;
	u32 opmode = to_d71_opmode(new_mode);
	पूर्णांक ret;

	malidp_ग_लिखो32_mask(d71->gcu_addr, BLK_CONTROL, 0x7, opmode);

	ret = dp_रुको_cond(((malidp_पढ़ो32(d71->gcu_addr, BLK_CONTROL) & 0x7) == opmode),
			   100, 1000, 10000);

	वापस ret;
पूर्ण

अटल व्योम d71_flush(काष्ठा komeda_dev *mdev,
		      पूर्णांक master_pipe, u32 active_pipes)
अणु
	काष्ठा d71_dev *d71 = mdev->chip_data;
	u32 reg_offset = (master_pipe == 0) ?
			 GCU_CONFIG_VALID0 : GCU_CONFIG_VALID1;

	malidp_ग_लिखो32(d71->gcu_addr, reg_offset, GCU_CONFIG_CVAL);
पूर्ण

अटल पूर्णांक d71_reset(काष्ठा d71_dev *d71)
अणु
	u32 __iomem *gcu = d71->gcu_addr;
	पूर्णांक ret;

	malidp_ग_लिखो32_mask(gcu, BLK_CONTROL,
			    GCU_CONTROL_SRST, GCU_CONTROL_SRST);

	ret = dp_रुको_cond(!(malidp_पढ़ो32(gcu, BLK_CONTROL) & GCU_CONTROL_SRST),
			   100, 1000, 10000);

	वापस ret;
पूर्ण

व्योम d71_पढ़ो_block_header(u32 __iomem *reg, काष्ठा block_header *blk)
अणु
	पूर्णांक i;

	blk->block_info = malidp_पढ़ो32(reg, BLK_BLOCK_INFO);
	अगर (BLOCK_INFO_BLK_TYPE(blk->block_info) == D71_BLK_TYPE_RESERVED)
		वापस;

	blk->pipeline_info = malidp_पढ़ो32(reg, BLK_PIPELINE_INFO);

	/* get valid input and output ids */
	क्रम (i = 0; i < PIPELINE_INFO_N_VALID_INPUTS(blk->pipeline_info); i++)
		blk->input_ids[i] = malidp_पढ़ो32(reg + i, BLK_VALID_INPUT_ID0);
	क्रम (i = 0; i < PIPELINE_INFO_N_OUTPUTS(blk->pipeline_info); i++)
		blk->output_ids[i] = malidp_पढ़ो32(reg + i, BLK_OUTPUT_ID0);
पूर्ण

अटल व्योम d71_cleanup(काष्ठा komeda_dev *mdev)
अणु
	काष्ठा d71_dev *d71 = mdev->chip_data;

	अगर (!d71)
		वापस;

	devm_kमुक्त(mdev->dev, d71);
	mdev->chip_data = शून्य;
पूर्ण

अटल पूर्णांक d71_क्रमागत_resources(काष्ठा komeda_dev *mdev)
अणु
	काष्ठा d71_dev *d71;
	काष्ठा komeda_pipeline *pipe;
	काष्ठा block_header blk;
	u32 __iomem *blk_base;
	u32 i, value, offset;
	पूर्णांक err;

	d71 = devm_kzalloc(mdev->dev, माप(*d71), GFP_KERNEL);
	अगर (!d71)
		वापस -ENOMEM;

	mdev->chip_data = d71;
	d71->mdev = mdev;
	d71->gcu_addr = mdev->reg_base;
	d71->periph_addr = mdev->reg_base + (D71_BLOCK_OFFSET_PERIPH >> 2);

	err = d71_reset(d71);
	अगर (err) अणु
		DRM_ERROR("Fail to reset d71 device.\n");
		जाओ err_cleanup;
	पूर्ण

	/* probe GCU */
	value = malidp_पढ़ो32(d71->gcu_addr, GLB_CORE_INFO);
	d71->num_blocks = value & 0xFF;
	d71->num_pipelines = (value >> 8) & 0x7;

	अगर (d71->num_pipelines > D71_MAX_PIPELINE) अणु
		DRM_ERROR("d71 supports %d pipelines, but got: %d.\n",
			  D71_MAX_PIPELINE, d71->num_pipelines);
		err = -EINVAL;
		जाओ err_cleanup;
	पूर्ण

	/* Only the legacy HW has the periph block, the newer merges the periph
	 * पूर्णांकo GCU
	 */
	value = malidp_पढ़ो32(d71->periph_addr, BLK_BLOCK_INFO);
	अगर (BLOCK_INFO_BLK_TYPE(value) != D71_BLK_TYPE_PERIPH)
		d71->periph_addr = शून्य;

	अगर (d71->periph_addr) अणु
		/* probe PERIPHERAL in legacy HW */
		value = malidp_पढ़ो32(d71->periph_addr, PERIPH_CONFIGURATION_ID);

		d71->max_line_size	= value & PERIPH_MAX_LINE_SIZE ? 4096 : 2048;
		d71->max_vsize		= 4096;
		d71->num_rich_layers	= value & PERIPH_NUM_RICH_LAYERS ? 2 : 1;
		d71->supports_dual_link	= !!(value & PERIPH_SPLIT_EN);
		d71->पूर्णांकegrates_tbu	= !!(value & PERIPH_TBU_EN);
	पूर्ण अन्यथा अणु
		value = malidp_पढ़ो32(d71->gcu_addr, GCU_CONFIGURATION_ID0);
		d71->max_line_size	= GCU_MAX_LINE_SIZE(value);
		d71->max_vsize		= GCU_MAX_NUM_LINES(value);

		value = malidp_पढ़ो32(d71->gcu_addr, GCU_CONFIGURATION_ID1);
		d71->num_rich_layers	= GCU_NUM_RICH_LAYERS(value);
		d71->supports_dual_link	= GCU_DISPLAY_SPLIT_EN(value);
		d71->पूर्णांकegrates_tbu	= GCU_DISPLAY_TBU_EN(value);
	पूर्ण

	क्रम (i = 0; i < d71->num_pipelines; i++) अणु
		pipe = komeda_pipeline_add(mdev, माप(काष्ठा d71_pipeline),
					   &d71_pipeline_funcs);
		अगर (IS_ERR(pipe)) अणु
			err = PTR_ERR(pipe);
			जाओ err_cleanup;
		पूर्ण

		/* D71 HW करोesn't update shaकरोw रेजिस्टरs when display output
		 * is turning off, so when we disable all pipeline components
		 * together with display output disable by one flush or one
		 * operation, the disable operation updated रेजिस्टरs will not
		 * be flush to or valid in HW, which may leads problem.
		 * To workaround this problem, पूर्णांकroduce a two phase disable.
		 * Phase1: Disabling components with display is on to make sure
		 *	   the disable can be flushed to HW.
		 * Phase2: Only turn-off display output.
		 */
		value = KOMEDA_PIPELINE_IMPROCS |
			BIT(KOMEDA_COMPONENT_TIMING_CTRLR);

		pipe->standalone_disabled_comps = value;

		d71->pipes[i] = to_d71_pipeline(pipe);
	पूर्ण

	/* loop the रेजिस्टर blks and probe.
	 * NOTE: d71->num_blocks includes reserved blocks.
	 * d71->num_blocks = GCU + valid blocks + reserved blocks
	 */
	i = 1; /* exclude GCU */
	offset = D71_BLOCK_SIZE; /* skip GCU */
	जबतक (i < d71->num_blocks) अणु
		blk_base = mdev->reg_base + (offset >> 2);

		d71_पढ़ो_block_header(blk_base, &blk);
		अगर (BLOCK_INFO_BLK_TYPE(blk.block_info) != D71_BLK_TYPE_RESERVED) अणु
			err = d71_probe_block(d71, &blk, blk_base);
			अगर (err)
				जाओ err_cleanup;
		पूर्ण

		i++;
		offset += D71_BLOCK_SIZE;
	पूर्ण

	DRM_DEBUG("total %d (out of %d) blocks are found.\n",
		  i, d71->num_blocks);

	वापस 0;

err_cleanup:
	d71_cleanup(mdev);
	वापस err;
पूर्ण

#घोषणा __HW_ID(__group, __क्रमmat) \
	((((__group) & 0x7) << 3) | ((__क्रमmat) & 0x7))

#घोषणा RICH		KOMEDA_FMT_RICH_LAYER
#घोषणा SIMPLE		KOMEDA_FMT_SIMPLE_LAYER
#घोषणा RICH_SIMPLE	(KOMEDA_FMT_RICH_LAYER | KOMEDA_FMT_SIMPLE_LAYER)
#घोषणा RICH_WB		(KOMEDA_FMT_RICH_LAYER | KOMEDA_FMT_WB_LAYER)
#घोषणा RICH_SIMPLE_WB	(RICH_SIMPLE | KOMEDA_FMT_WB_LAYER)

#घोषणा Rot_0		DRM_MODE_ROTATE_0
#घोषणा Flip_H_V	(DRM_MODE_REFLECT_X | DRM_MODE_REFLECT_Y | Rot_0)
#घोषणा Rot_ALL_H_V	(DRM_MODE_ROTATE_MASK | Flip_H_V)

#घोषणा LYT_NM		BIT(AFBC_FORMAT_MOD_BLOCK_SIZE_16x16)
#घोषणा LYT_WB		BIT(AFBC_FORMAT_MOD_BLOCK_SIZE_32x8)
#घोषणा LYT_NM_WB	(LYT_NM | LYT_WB)

#घोषणा AFB_TH		AFBC(_TILED | _SPARSE)
#घोषणा AFB_TH_SC_YTR	AFBC(_TILED | _SC | _SPARSE | _YTR)
#घोषणा AFB_TH_SC_YTR_BS AFBC(_TILED | _SC | _SPARSE | _YTR | _SPLIT)

अटल काष्ठा komeda_क्रमmat_caps d71_क्रमmat_caps_table[] = अणु
	/*   HW_ID    |        fourcc         |   layer_types |   rots    | afbc_layouts | afbc_features */
	/* ABGR_2101010*/
	अणु__HW_ID(0, 0),	DRM_FORMAT_ARGB2101010,	RICH_SIMPLE_WB,	Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(0, 1),	DRM_FORMAT_ABGR2101010,	RICH_SIMPLE_WB,	Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(0, 1),	DRM_FORMAT_ABGR2101010,	RICH_SIMPLE,	Rot_ALL_H_V,	LYT_NM_WB, AFB_TH_SC_YTR_BSपूर्ण, /* afbc */
	अणु__HW_ID(0, 2),	DRM_FORMAT_RGBA1010102,	RICH_SIMPLE_WB,	Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(0, 3),	DRM_FORMAT_BGRA1010102,	RICH_SIMPLE_WB,	Flip_H_V,		0, 0पूर्ण,
	/* ABGR_8888*/
	अणु__HW_ID(1, 0),	DRM_FORMAT_ARGB8888,	RICH_SIMPLE_WB,	Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(1, 1),	DRM_FORMAT_ABGR8888,	RICH_SIMPLE_WB,	Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(1, 1),	DRM_FORMAT_ABGR8888,	RICH_SIMPLE,	Rot_ALL_H_V,	LYT_NM_WB, AFB_TH_SC_YTR_BSपूर्ण, /* afbc */
	अणु__HW_ID(1, 2),	DRM_FORMAT_RGBA8888,	RICH_SIMPLE_WB,	Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(1, 3),	DRM_FORMAT_BGRA8888,	RICH_SIMPLE_WB,	Flip_H_V,		0, 0पूर्ण,
	/* XBGB_8888 */
	अणु__HW_ID(2, 0),	DRM_FORMAT_XRGB8888,	RICH_SIMPLE_WB,	Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(2, 1),	DRM_FORMAT_XBGR8888,	RICH_SIMPLE_WB,	Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(2, 2),	DRM_FORMAT_RGBX8888,	RICH_SIMPLE_WB,	Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(2, 3),	DRM_FORMAT_BGRX8888,	RICH_SIMPLE_WB,	Flip_H_V,		0, 0पूर्ण,
	/* BGR_888 */ /* none-afbc RGB888 करोesn't support rotation and flip */
	अणु__HW_ID(3, 0),	DRM_FORMAT_RGB888,	RICH_SIMPLE_WB,	Rot_0,			0, 0पूर्ण,
	अणु__HW_ID(3, 1),	DRM_FORMAT_BGR888,	RICH_SIMPLE_WB,	Rot_0,			0, 0पूर्ण,
	अणु__HW_ID(3, 1),	DRM_FORMAT_BGR888,	RICH_SIMPLE,	Rot_ALL_H_V,	LYT_NM_WB, AFB_TH_SC_YTR_BSपूर्ण, /* afbc */
	/* BGR 16bpp */
	अणु__HW_ID(4, 0),	DRM_FORMAT_RGBA5551,	RICH_SIMPLE,	Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(4, 1),	DRM_FORMAT_ABGR1555,	RICH_SIMPLE,	Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(4, 1),	DRM_FORMAT_ABGR1555,	RICH_SIMPLE,	Rot_ALL_H_V,	LYT_NM_WB, AFB_TH_SC_YTRपूर्ण, /* afbc */
	अणु__HW_ID(4, 2),	DRM_FORMAT_RGB565,	RICH_SIMPLE,	Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(4, 3),	DRM_FORMAT_BGR565,	RICH_SIMPLE,	Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(4, 3),	DRM_FORMAT_BGR565,	RICH_SIMPLE,	Rot_ALL_H_V,	LYT_NM_WB, AFB_TH_SC_YTRपूर्ण, /* afbc */
	अणु__HW_ID(4, 4), DRM_FORMAT_R8,		SIMPLE,		Rot_0,			0, 0पूर्ण,
	/* YUV 444/422/420 8bit  */
	अणु__HW_ID(5, 1),	DRM_FORMAT_YUYV,	RICH,		Rot_ALL_H_V,	LYT_NM, AFB_THपूर्ण, /* afbc */
	अणु__HW_ID(5, 2),	DRM_FORMAT_YUYV,	RICH,		Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(5, 3),	DRM_FORMAT_UYVY,	RICH,		Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(5, 6),	DRM_FORMAT_NV12,	RICH,		Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(5, 6),	DRM_FORMAT_YUV420_8BIT,	RICH,		Rot_ALL_H_V,	LYT_NM, AFB_THपूर्ण, /* afbc */
	अणु__HW_ID(5, 7),	DRM_FORMAT_YUV420,	RICH,		Flip_H_V,		0, 0पूर्ण,
	/* YUV 10bit*/
	अणु__HW_ID(6, 6),	DRM_FORMAT_X0L2,	RICH,		Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(6, 7),	DRM_FORMAT_P010,	RICH,		Flip_H_V,		0, 0पूर्ण,
	अणु__HW_ID(6, 7),	DRM_FORMAT_YUV420_10BIT, RICH,		Rot_ALL_H_V,	LYT_NM, AFB_THपूर्ण,
पूर्ण;

अटल bool d71_क्रमmat_mod_supported(स्थिर काष्ठा komeda_क्रमmat_caps *caps,
				     u32 layer_type, u64 modअगरier, u32 rot)
अणु
	uपूर्णांक64_t layout = modअगरier & AFBC_FORMAT_MOD_BLOCK_SIZE_MASK;

	अगर ((layout == AFBC_FORMAT_MOD_BLOCK_SIZE_32x8) &&
	    drm_rotation_90_or_270(rot)) अणु
		DRM_DEBUG_ATOMIC("D71 doesn't support ROT90 for WB-AFBC.\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम d71_init_fmt_tbl(काष्ठा komeda_dev *mdev)
अणु
	काष्ठा komeda_क्रमmat_caps_table *table = &mdev->fmt_tbl;

	table->क्रमmat_caps = d71_क्रमmat_caps_table;
	table->क्रमmat_mod_supported = d71_क्रमmat_mod_supported;
	table->n_क्रमmats = ARRAY_SIZE(d71_क्रमmat_caps_table);
पूर्ण

अटल पूर्णांक d71_connect_iommu(काष्ठा komeda_dev *mdev)
अणु
	काष्ठा d71_dev *d71 = mdev->chip_data;
	u32 __iomem *reg = d71->gcu_addr;
	u32 check_bits = (d71->num_pipelines == 2) ?
			 GCU_STATUS_TCS0 | GCU_STATUS_TCS1 : GCU_STATUS_TCS0;
	पूर्णांक i, ret;

	अगर (!d71->पूर्णांकegrates_tbu)
		वापस -1;

	malidp_ग_लिखो32_mask(reg, BLK_CONTROL, 0x7, TBU_CONNECT_MODE);

	ret = dp_रुको_cond(has_bits(check_bits, malidp_पढ़ो32(reg, BLK_STATUS)),
			100, 1000, 1000);
	अगर (ret < 0) अणु
		DRM_ERROR("timed out connecting to TCU!\n");
		malidp_ग_लिखो32_mask(reg, BLK_CONTROL, 0x7, INACTIVE_MODE);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < d71->num_pipelines; i++)
		malidp_ग_लिखो32_mask(d71->pipes[i]->lpu_addr, LPU_TBU_CONTROL,
				    LPU_TBU_CTRL_TLBPEN, LPU_TBU_CTRL_TLBPEN);
	वापस 0;
पूर्ण

अटल पूर्णांक d71_disconnect_iommu(काष्ठा komeda_dev *mdev)
अणु
	काष्ठा d71_dev *d71 = mdev->chip_data;
	u32 __iomem *reg = d71->gcu_addr;
	u32 check_bits = (d71->num_pipelines == 2) ?
			 GCU_STATUS_TCS0 | GCU_STATUS_TCS1 : GCU_STATUS_TCS0;
	पूर्णांक ret;

	malidp_ग_लिखो32_mask(reg, BLK_CONTROL, 0x7, TBU_DISCONNECT_MODE);

	ret = dp_रुको_cond(((malidp_पढ़ो32(reg, BLK_STATUS) & check_bits) == 0),
			100, 1000, 1000);
	अगर (ret < 0) अणु
		DRM_ERROR("timed out disconnecting from TCU!\n");
		malidp_ग_लिखो32_mask(reg, BLK_CONTROL, 0x7, INACTIVE_MODE);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा komeda_dev_funcs d71_chip_funcs = अणु
	.init_क्रमmat_table	= d71_init_fmt_tbl,
	.क्रमागत_resources		= d71_क्रमागत_resources,
	.cleanup		= d71_cleanup,
	.irq_handler		= d71_irq_handler,
	.enable_irq		= d71_enable_irq,
	.disable_irq		= d71_disable_irq,
	.on_off_vblank		= d71_on_off_vblank,
	.change_opmode		= d71_change_opmode,
	.flush			= d71_flush,
	.connect_iommu		= d71_connect_iommu,
	.disconnect_iommu	= d71_disconnect_iommu,
	.dump_रेजिस्टर		= d71_dump,
पूर्ण;

स्थिर काष्ठा komeda_dev_funcs *
d71_identअगरy(u32 __iomem *reg_base, काष्ठा komeda_chip_info *chip)
अणु
	स्थिर काष्ठा komeda_dev_funcs *funcs;
	u32 product_id;

	chip->core_id = malidp_पढ़ो32(reg_base, GLB_CORE_ID);

	product_id = MALIDP_CORE_ID_PRODUCT_ID(chip->core_id);

	चयन (product_id) अणु
	हाल MALIDP_D71_PRODUCT_ID:
	हाल MALIDP_D32_PRODUCT_ID:
		funcs = &d71_chip_funcs;
		अवरोध;
	शेष:
		DRM_ERROR("Unsupported product: 0x%x\n", product_id);
		वापस शून्य;
	पूर्ण

	chip->arch_id	= malidp_पढ़ो32(reg_base, GLB_ARCH_ID);
	chip->core_info	= malidp_पढ़ो32(reg_base, GLB_CORE_INFO);
	chip->bus_width	= D71_BUS_WIDTH_16_BYTES;

	वापस funcs;
पूर्ण
