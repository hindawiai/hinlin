<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Etnaviv Project
 * Copyright (C) 2017 Zodiac Inflight Innovations
 */

#समावेश "common.xml.h"
#समावेश "etnaviv_gpu.h"
#समावेश "etnaviv_perfmon.h"
#समावेश "state_hi.xml.h"

काष्ठा etnaviv_pm_करोमुख्य;

काष्ठा etnaviv_pm_संकेत अणु
	अक्षर name[64];
	u32 data;

	u32 (*sample)(काष्ठा etnaviv_gpu *gpu,
		      स्थिर काष्ठा etnaviv_pm_करोमुख्य *करोमुख्य,
		      स्थिर काष्ठा etnaviv_pm_संकेत *संकेत);
पूर्ण;

काष्ठा etnaviv_pm_करोमुख्य अणु
	अक्षर name[64];

	/* profile रेजिस्टर */
	u32 profile_पढ़ो;
	u32 profile_config;

	u8 nr_संकेतs;
	स्थिर काष्ठा etnaviv_pm_संकेत *संकेत;
पूर्ण;

काष्ठा etnaviv_pm_करोमुख्य_meta अणु
	अचिन्हित पूर्णांक feature;
	स्थिर काष्ठा etnaviv_pm_करोमुख्य *करोमुख्यs;
	u32 nr_करोमुख्यs;
पूर्ण;

अटल u32 perf_reg_पढ़ो(काष्ठा etnaviv_gpu *gpu,
	स्थिर काष्ठा etnaviv_pm_करोमुख्य *करोमुख्य,
	स्थिर काष्ठा etnaviv_pm_संकेत *संकेत)
अणु
	gpu_ग_लिखो(gpu, करोमुख्य->profile_config, संकेत->data);

	वापस gpu_पढ़ो(gpu, करोमुख्य->profile_पढ़ो);
पूर्ण

अटल अंतरभूत व्योम pipe_select(काष्ठा etnaviv_gpu *gpu, u32 घड़ी, अचिन्हित pipe)
अणु
	घड़ी &= ~(VIVS_HI_CLOCK_CONTROL_DEBUG_PIXEL_PIPE__MASK);
	घड़ी |= VIVS_HI_CLOCK_CONTROL_DEBUG_PIXEL_PIPE(pipe);

	gpu_ग_लिखो(gpu, VIVS_HI_CLOCK_CONTROL, घड़ी);
पूर्ण

अटल u32 pipe_perf_reg_पढ़ो(काष्ठा etnaviv_gpu *gpu,
	स्थिर काष्ठा etnaviv_pm_करोमुख्य *करोमुख्य,
	स्थिर काष्ठा etnaviv_pm_संकेत *संकेत)
अणु
	u32 घड़ी = gpu_पढ़ो(gpu, VIVS_HI_CLOCK_CONTROL);
	u32 value = 0;
	अचिन्हित i;

	क्रम (i = 0; i < gpu->identity.pixel_pipes; i++) अणु
		pipe_select(gpu, घड़ी, i);
		value += perf_reg_पढ़ो(gpu, करोमुख्य, संकेत);
	पूर्ण

	/* चयन back to pixel pipe 0 to prevent GPU hang */
	pipe_select(gpu, घड़ी, 0);

	वापस value;
पूर्ण

अटल u32 pipe_reg_पढ़ो(काष्ठा etnaviv_gpu *gpu,
	स्थिर काष्ठा etnaviv_pm_करोमुख्य *करोमुख्य,
	स्थिर काष्ठा etnaviv_pm_संकेत *संकेत)
अणु
	u32 घड़ी = gpu_पढ़ो(gpu, VIVS_HI_CLOCK_CONTROL);
	u32 value = 0;
	अचिन्हित i;

	क्रम (i = 0; i < gpu->identity.pixel_pipes; i++) अणु
		pipe_select(gpu, घड़ी, i);
		value += gpu_पढ़ो(gpu, संकेत->data);
	पूर्ण

	/* चयन back to pixel pipe 0 to prevent GPU hang */
	pipe_select(gpu, घड़ी, 0);

	वापस value;
पूर्ण

अटल u32 hi_total_cycle_पढ़ो(काष्ठा etnaviv_gpu *gpu,
	स्थिर काष्ठा etnaviv_pm_करोमुख्य *करोमुख्य,
	स्थिर काष्ठा etnaviv_pm_संकेत *संकेत)
अणु
	u32 reg = VIVS_HI_PROखाता_TOTAL_CYCLES;

	अगर (gpu->identity.model == chipModel_GC880 ||
		gpu->identity.model == chipModel_GC2000 ||
		gpu->identity.model == chipModel_GC2100)
		reg = VIVS_MC_PROखाता_CYCLE_COUNTER;

	वापस gpu_पढ़ो(gpu, reg);
पूर्ण

अटल u32 hi_total_idle_cycle_पढ़ो(काष्ठा etnaviv_gpu *gpu,
	स्थिर काष्ठा etnaviv_pm_करोमुख्य *करोमुख्य,
	स्थिर काष्ठा etnaviv_pm_संकेत *संकेत)
अणु
	u32 reg = VIVS_HI_PROखाता_IDLE_CYCLES;

	अगर (gpu->identity.model == chipModel_GC880 ||
		gpu->identity.model == chipModel_GC2000 ||
		gpu->identity.model == chipModel_GC2100)
		reg = VIVS_HI_PROखाता_TOTAL_CYCLES;

	वापस gpu_पढ़ो(gpu, reg);
पूर्ण

अटल स्थिर काष्ठा etnaviv_pm_करोमुख्य करोms_3d[] = अणु
	अणु
		.name = "HI",
		.profile_पढ़ो = VIVS_MC_PROखाता_HI_READ,
		.profile_config = VIVS_MC_PROखाता_CONFIG2,
		.nr_संकेतs = 7,
		.संकेत = (स्थिर काष्ठा etnaviv_pm_संकेत[]) अणु
			अणु
				"TOTAL_READ_BYTES8",
				VIVS_HI_PROखाता_READ_BYTES8,
				&pipe_reg_पढ़ो,
			पूर्ण,
			अणु
				"TOTAL_WRITE_BYTES8",
				VIVS_HI_PROखाता_WRITE_BYTES8,
				&pipe_reg_पढ़ो,
			पूर्ण,
			अणु
				"TOTAL_CYCLES",
				0,
				&hi_total_cycle_पढ़ो
			पूर्ण,
			अणु
				"IDLE_CYCLES",
				0,
				&hi_total_idle_cycle_पढ़ो
			पूर्ण,
			अणु
				"AXI_CYCLES_READ_REQUEST_STALLED",
				VIVS_MC_PROखाता_CONFIG2_HI_AXI_CYCLES_READ_REQUEST_STALLED,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"AXI_CYCLES_WRITE_REQUEST_STALLED",
				VIVS_MC_PROखाता_CONFIG2_HI_AXI_CYCLES_WRITE_REQUEST_STALLED,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"AXI_CYCLES_WRITE_DATA_STALLED",
				VIVS_MC_PROखाता_CONFIG2_HI_AXI_CYCLES_WRITE_DATA_STALLED,
				&perf_reg_पढ़ो
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.name = "PE",
		.profile_पढ़ो = VIVS_MC_PROखाता_PE_READ,
		.profile_config = VIVS_MC_PROखाता_CONFIG0,
		.nr_संकेतs = 4,
		.संकेत = (स्थिर काष्ठा etnaviv_pm_संकेत[]) अणु
			अणु
				"PIXEL_COUNT_KILLED_BY_COLOR_PIPE",
				VIVS_MC_PROखाता_CONFIG0_PE_PIXEL_COUNT_KILLED_BY_COLOR_PIPE,
				&pipe_perf_reg_पढ़ो
			पूर्ण,
			अणु
				"PIXEL_COUNT_KILLED_BY_DEPTH_PIPE",
				VIVS_MC_PROखाता_CONFIG0_PE_PIXEL_COUNT_KILLED_BY_DEPTH_PIPE,
				&pipe_perf_reg_पढ़ो
			पूर्ण,
			अणु
				"PIXEL_COUNT_DRAWN_BY_COLOR_PIPE",
				VIVS_MC_PROखाता_CONFIG0_PE_PIXEL_COUNT_DRAWN_BY_COLOR_PIPE,
				&pipe_perf_reg_पढ़ो
			पूर्ण,
			अणु
				"PIXEL_COUNT_DRAWN_BY_DEPTH_PIPE",
				VIVS_MC_PROखाता_CONFIG0_PE_PIXEL_COUNT_DRAWN_BY_DEPTH_PIPE,
				&pipe_perf_reg_पढ़ो
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.name = "SH",
		.profile_पढ़ो = VIVS_MC_PROखाता_SH_READ,
		.profile_config = VIVS_MC_PROखाता_CONFIG0,
		.nr_संकेतs = 9,
		.संकेत = (स्थिर काष्ठा etnaviv_pm_संकेत[]) अणु
			अणु
				"SHADER_CYCLES",
				VIVS_MC_PROखाता_CONFIG0_SH_SHADER_CYCLES,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"PS_INST_COUNTER",
				VIVS_MC_PROखाता_CONFIG0_SH_PS_INST_COUNTER,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"RENDERED_PIXEL_COUNTER",
				VIVS_MC_PROखाता_CONFIG0_SH_RENDERED_PIXEL_COUNTER,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"VS_INST_COUNTER",
				VIVS_MC_PROखाता_CONFIG0_SH_VS_INST_COUNTER,
				&pipe_perf_reg_पढ़ो
			पूर्ण,
			अणु
				"RENDERED_VERTICE_COUNTER",
				VIVS_MC_PROखाता_CONFIG0_SH_RENDERED_VERTICE_COUNTER,
				&pipe_perf_reg_पढ़ो
			पूर्ण,
			अणु
				"VTX_BRANCH_INST_COUNTER",
				VIVS_MC_PROखाता_CONFIG0_SH_VTX_BRANCH_INST_COUNTER,
				&pipe_perf_reg_पढ़ो
			पूर्ण,
			अणु
				"VTX_TEXLD_INST_COUNTER",
				VIVS_MC_PROखाता_CONFIG0_SH_VTX_TEXLD_INST_COUNTER,
				&pipe_perf_reg_पढ़ो
			पूर्ण,
			अणु
				"PXL_BRANCH_INST_COUNTER",
				VIVS_MC_PROखाता_CONFIG0_SH_PXL_BRANCH_INST_COUNTER,
				&pipe_perf_reg_पढ़ो
			पूर्ण,
			अणु
				"PXL_TEXLD_INST_COUNTER",
				VIVS_MC_PROखाता_CONFIG0_SH_PXL_TEXLD_INST_COUNTER,
				&pipe_perf_reg_पढ़ो
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.name = "PA",
		.profile_पढ़ो = VIVS_MC_PROखाता_PA_READ,
		.profile_config = VIVS_MC_PROखाता_CONFIG1,
		.nr_संकेतs = 6,
		.संकेत = (स्थिर काष्ठा etnaviv_pm_संकेत[]) अणु
			अणु
				"INPUT_VTX_COUNTER",
				VIVS_MC_PROखाता_CONFIG1_PA_INPUT_VTX_COUNTER,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"INPUT_PRIM_COUNTER",
				VIVS_MC_PROखाता_CONFIG1_PA_INPUT_PRIM_COUNTER,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"OUTPUT_PRIM_COUNTER",
				VIVS_MC_PROखाता_CONFIG1_PA_OUTPUT_PRIM_COUNTER,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"DEPTH_CLIPPED_COUNTER",
				VIVS_MC_PROखाता_CONFIG1_PA_DEPTH_CLIPPED_COUNTER,
				&pipe_perf_reg_पढ़ो
			पूर्ण,
			अणु
				"TRIVIAL_REJECTED_COUNTER",
				VIVS_MC_PROखाता_CONFIG1_PA_TRIVIAL_REJECTED_COUNTER,
				&pipe_perf_reg_पढ़ो
			पूर्ण,
			अणु
				"CULLED_COUNTER",
				VIVS_MC_PROखाता_CONFIG1_PA_CULLED_COUNTER,
				&pipe_perf_reg_पढ़ो
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.name = "SE",
		.profile_पढ़ो = VIVS_MC_PROखाता_SE_READ,
		.profile_config = VIVS_MC_PROखाता_CONFIG1,
		.nr_संकेतs = 2,
		.संकेत = (स्थिर काष्ठा etnaviv_pm_संकेत[]) अणु
			अणु
				"CULLED_TRIANGLE_COUNT",
				VIVS_MC_PROखाता_CONFIG1_SE_CULLED_TRIANGLE_COUNT,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"CULLED_LINES_COUNT",
				VIVS_MC_PROखाता_CONFIG1_SE_CULLED_LINES_COUNT,
				&perf_reg_पढ़ो
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.name = "RA",
		.profile_पढ़ो = VIVS_MC_PROखाता_RA_READ,
		.profile_config = VIVS_MC_PROखाता_CONFIG1,
		.nr_संकेतs = 7,
		.संकेत = (स्थिर काष्ठा etnaviv_pm_संकेत[]) अणु
			अणु
				"VALID_PIXEL_COUNT",
				VIVS_MC_PROखाता_CONFIG1_RA_VALID_PIXEL_COUNT,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"TOTAL_QUAD_COUNT",
				VIVS_MC_PROखाता_CONFIG1_RA_TOTAL_QUAD_COUNT,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"VALID_QUAD_COUNT_AFTER_EARLY_Z",
				VIVS_MC_PROखाता_CONFIG1_RA_VALID_QUAD_COUNT_AFTER_EARLY_Z,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"TOTAL_PRIMITIVE_COUNT",
				VIVS_MC_PROखाता_CONFIG1_RA_TOTAL_PRIMITIVE_COUNT,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"PIPE_CACHE_MISS_COUNTER",
				VIVS_MC_PROखाता_CONFIG1_RA_PIPE_CACHE_MISS_COUNTER,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"PREFETCH_CACHE_MISS_COUNTER",
				VIVS_MC_PROखाता_CONFIG1_RA_PREFETCH_CACHE_MISS_COUNTER,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"CULLED_QUAD_COUNT",
				VIVS_MC_PROखाता_CONFIG1_RA_CULLED_QUAD_COUNT,
				&perf_reg_पढ़ो
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.name = "TX",
		.profile_पढ़ो = VIVS_MC_PROखाता_TX_READ,
		.profile_config = VIVS_MC_PROखाता_CONFIG1,
		.nr_संकेतs = 9,
		.संकेत = (स्थिर काष्ठा etnaviv_pm_संकेत[]) अणु
			अणु
				"TOTAL_BILINEAR_REQUESTS",
				VIVS_MC_PROखाता_CONFIG1_TX_TOTAL_BILINEAR_REQUESTS,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"TOTAL_TRILINEAR_REQUESTS",
				VIVS_MC_PROखाता_CONFIG1_TX_TOTAL_TRILINEAR_REQUESTS,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"TOTAL_DISCARDED_TEXTURE_REQUESTS",
				VIVS_MC_PROखाता_CONFIG1_TX_TOTAL_DISCARDED_TEXTURE_REQUESTS,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"TOTAL_TEXTURE_REQUESTS",
				VIVS_MC_PROखाता_CONFIG1_TX_TOTAL_TEXTURE_REQUESTS,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"MEM_READ_COUNT",
				VIVS_MC_PROखाता_CONFIG1_TX_MEM_READ_COUNT,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"MEM_READ_IN_8B_COUNT",
				VIVS_MC_PROखाता_CONFIG1_TX_MEM_READ_IN_8B_COUNT,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"CACHE_MISS_COUNT",
				VIVS_MC_PROखाता_CONFIG1_TX_CACHE_MISS_COUNT,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"CACHE_HIT_TEXEL_COUNT",
				VIVS_MC_PROखाता_CONFIG1_TX_CACHE_HIT_TEXEL_COUNT,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"CACHE_MISS_TEXEL_COUNT",
				VIVS_MC_PROखाता_CONFIG1_TX_CACHE_MISS_TEXEL_COUNT,
				&perf_reg_पढ़ो
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.name = "MC",
		.profile_पढ़ो = VIVS_MC_PROखाता_MC_READ,
		.profile_config = VIVS_MC_PROखाता_CONFIG2,
		.nr_संकेतs = 3,
		.संकेत = (स्थिर काष्ठा etnaviv_pm_संकेत[]) अणु
			अणु
				"TOTAL_READ_REQ_8B_FROM_PIPELINE",
				VIVS_MC_PROखाता_CONFIG2_MC_TOTAL_READ_REQ_8B_FROM_PIPELINE,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"TOTAL_READ_REQ_8B_FROM_IP",
				VIVS_MC_PROखाता_CONFIG2_MC_TOTAL_READ_REQ_8B_FROM_IP,
				&perf_reg_पढ़ो
			पूर्ण,
			अणु
				"TOTAL_WRITE_REQ_8B_FROM_PIPELINE",
				VIVS_MC_PROखाता_CONFIG2_MC_TOTAL_WRITE_REQ_8B_FROM_PIPELINE,
				&perf_reg_पढ़ो
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा etnaviv_pm_करोमुख्य करोms_2d[] = अणु
	अणु
		.name = "PE",
		.profile_पढ़ो = VIVS_MC_PROखाता_PE_READ,
		.profile_config = VIVS_MC_PROखाता_CONFIG0,
		.nr_संकेतs = 1,
		.संकेत = (स्थिर काष्ठा etnaviv_pm_संकेत[]) अणु
			अणु
				"PIXELS_RENDERED_2D",
				VIVS_MC_PROखाता_CONFIG0_PE_PIXELS_RENDERED_2D,
				&pipe_perf_reg_पढ़ो
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा etnaviv_pm_करोमुख्य करोms_vg[] = अणु
पूर्ण;

अटल स्थिर काष्ठा etnaviv_pm_करोमुख्य_meta करोms_meta[] = अणु
	अणु
		.feature = chipFeatures_PIPE_3D,
		.nr_करोमुख्यs = ARRAY_SIZE(करोms_3d),
		.करोमुख्यs = &करोms_3d[0]
	पूर्ण,
	अणु
		.feature = chipFeatures_PIPE_2D,
		.nr_करोमुख्यs = ARRAY_SIZE(करोms_2d),
		.करोमुख्यs = &करोms_2d[0]
	पूर्ण,
	अणु
		.feature = chipFeatures_PIPE_VG,
		.nr_करोमुख्यs = ARRAY_SIZE(करोms_vg),
		.करोमुख्यs = &करोms_vg[0]
	पूर्ण
पूर्ण;

अटल अचिन्हित पूर्णांक num_pm_करोमुख्यs(स्थिर काष्ठा etnaviv_gpu *gpu)
अणु
	अचिन्हित पूर्णांक num = 0, i;

	क्रम (i = 0; i < ARRAY_SIZE(करोms_meta); i++) अणु
		स्थिर काष्ठा etnaviv_pm_करोमुख्य_meta *meta = &करोms_meta[i];

		अगर (gpu->identity.features & meta->feature)
			num += meta->nr_करोमुख्यs;
	पूर्ण

	वापस num;
पूर्ण

अटल स्थिर काष्ठा etnaviv_pm_करोमुख्य *pm_करोमुख्य(स्थिर काष्ठा etnaviv_gpu *gpu,
	अचिन्हित पूर्णांक index)
अणु
	स्थिर काष्ठा etnaviv_pm_करोमुख्य *करोमुख्य = शून्य;
	अचिन्हित पूर्णांक offset = 0, i;

	क्रम (i = 0; i < ARRAY_SIZE(करोms_meta); i++) अणु
		स्थिर काष्ठा etnaviv_pm_करोमुख्य_meta *meta = &करोms_meta[i];

		अगर (!(gpu->identity.features & meta->feature))
			जारी;

		अगर (index - offset >= meta->nr_करोमुख्यs) अणु
			offset += meta->nr_करोमुख्यs;
			जारी;
		पूर्ण

		करोमुख्य = meta->करोमुख्यs + (index - offset);
	पूर्ण

	वापस करोमुख्य;
पूर्ण

पूर्णांक etnaviv_pm_query_करोm(काष्ठा etnaviv_gpu *gpu,
	काष्ठा drm_etnaviv_pm_करोमुख्य *करोमुख्य)
अणु
	स्थिर अचिन्हित पूर्णांक nr_करोमुख्यs = num_pm_करोमुख्यs(gpu);
	स्थिर काष्ठा etnaviv_pm_करोमुख्य *करोm;

	अगर (करोमुख्य->iter >= nr_करोमुख्यs)
		वापस -EINVAL;

	करोm = pm_करोमुख्य(gpu, करोमुख्य->iter);
	अगर (!करोm)
		वापस -EINVAL;

	करोमुख्य->id = करोमुख्य->iter;
	करोमुख्य->nr_संकेतs = करोm->nr_संकेतs;
	म_नकलन(करोमुख्य->name, करोm->name, माप(करोमुख्य->name));

	करोमुख्य->iter++;
	अगर (करोमुख्य->iter == nr_करोमुख्यs)
		करोमुख्य->iter = 0xff;

	वापस 0;
पूर्ण

पूर्णांक etnaviv_pm_query_sig(काष्ठा etnaviv_gpu *gpu,
	काष्ठा drm_etnaviv_pm_संकेत *संकेत)
अणु
	स्थिर अचिन्हित पूर्णांक nr_करोमुख्यs = num_pm_करोमुख्यs(gpu);
	स्थिर काष्ठा etnaviv_pm_करोमुख्य *करोm;
	स्थिर काष्ठा etnaviv_pm_संकेत *sig;

	अगर (संकेत->करोमुख्य >= nr_करोमुख्यs)
		वापस -EINVAL;

	करोm = pm_करोमुख्य(gpu, संकेत->करोमुख्य);
	अगर (!करोm)
		वापस -EINVAL;

	अगर (संकेत->iter >= करोm->nr_संकेतs)
		वापस -EINVAL;

	sig = &करोm->संकेत[संकेत->iter];

	संकेत->id = संकेत->iter;
	म_नकलन(संकेत->name, sig->name, माप(संकेत->name));

	संकेत->iter++;
	अगर (संकेत->iter == करोm->nr_संकेतs)
		संकेत->iter = 0xffff;

	वापस 0;
पूर्ण

पूर्णांक etnaviv_pm_req_validate(स्थिर काष्ठा drm_etnaviv_gem_submit_pmr *r,
	u32 exec_state)
अणु
	स्थिर काष्ठा etnaviv_pm_करोमुख्य_meta *meta = &करोms_meta[exec_state];
	स्थिर काष्ठा etnaviv_pm_करोमुख्य *करोm;

	अगर (r->करोमुख्य >= meta->nr_करोमुख्यs)
		वापस -EINVAL;

	करोm = meta->करोमुख्यs + r->करोमुख्य;

	अगर (r->संकेत >= करोm->nr_संकेतs)
		वापस -EINVAL;

	वापस 0;
पूर्ण

व्योम etnaviv_perfmon_process(काष्ठा etnaviv_gpu *gpu,
	स्थिर काष्ठा etnaviv_perfmon_request *pmr, u32 exec_state)
अणु
	स्थिर काष्ठा etnaviv_pm_करोमुख्य_meta *meta = &करोms_meta[exec_state];
	स्थिर काष्ठा etnaviv_pm_करोमुख्य *करोm;
	स्थिर काष्ठा etnaviv_pm_संकेत *sig;
	u32 *bo = pmr->bo_vma;
	u32 val;

	करोm = meta->करोमुख्यs + pmr->करोमुख्य;
	sig = &करोm->संकेत[pmr->संकेत];
	val = sig->sample(gpu, करोm, sig);

	*(bo + pmr->offset) = val;
पूर्ण
