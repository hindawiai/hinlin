<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/pm_opp.h>
#समावेश "a5xx_gpu.h"

/*
 * The GPMU data block is a block of shared रेजिस्टरs that can be used to
 * communicate back and क्रमth. These "registers" are by convention with the GPMU
 * firwmare and not bound to any specअगरic hardware design
 */

#घोषणा AGC_INIT_BASE REG_A5XX_GPMU_DATA_RAM_BASE
#घोषणा AGC_INIT_MSG_MAGIC (AGC_INIT_BASE + 5)
#घोषणा AGC_MSG_BASE (AGC_INIT_BASE + 7)

#घोषणा AGC_MSG_STATE (AGC_MSG_BASE + 0)
#घोषणा AGC_MSG_COMMAND (AGC_MSG_BASE + 1)
#घोषणा AGC_MSG_PAYLOAD_SIZE (AGC_MSG_BASE + 3)
#घोषणा AGC_MSG_PAYLOAD(_o) ((AGC_MSG_BASE + 5) + (_o))

#घोषणा AGC_POWER_CONFIG_PRODUCTION_ID 1
#घोषणा AGC_INIT_MSG_VALUE 0xBABEFACE

/* AGC_LM_CONFIG (A540+) */
#घोषणा AGC_LM_CONFIG (136/4)
#घोषणा AGC_LM_CONFIG_GPU_VERSION_SHIFT 17
#घोषणा AGC_LM_CONFIG_ENABLE_GPMU_ADAPTIVE 1
#घोषणा AGC_LM_CONFIG_THROTTLE_DISABLE (2 << 8)
#घोषणा AGC_LM_CONFIG_ISENSE_ENABLE (1 << 4)
#घोषणा AGC_LM_CONFIG_ENABLE_ERROR (3 << 4)
#घोषणा AGC_LM_CONFIG_LLM_ENABLED (1 << 16)
#घोषणा AGC_LM_CONFIG_BCL_DISABLED (1 << 24)

#घोषणा AGC_LEVEL_CONFIG (140/4)

अटल काष्ठा अणु
	uपूर्णांक32_t reg;
	uपूर्णांक32_t value;
पूर्ण a5xx_sequence_regs[] = अणु
	अणु 0xB9A1, 0x00010303 पूर्ण,
	अणु 0xB9A2, 0x13000000 पूर्ण,
	अणु 0xB9A3, 0x00460020 पूर्ण,
	अणु 0xB9A4, 0x10000000 पूर्ण,
	अणु 0xB9A5, 0x040A1707 पूर्ण,
	अणु 0xB9A6, 0x00010000 पूर्ण,
	अणु 0xB9A7, 0x0E000904 पूर्ण,
	अणु 0xB9A8, 0x10000000 पूर्ण,
	अणु 0xB9A9, 0x01165000 पूर्ण,
	अणु 0xB9AA, 0x000E0002 पूर्ण,
	अणु 0xB9AB, 0x03884141 पूर्ण,
	अणु 0xB9AC, 0x10000840 पूर्ण,
	अणु 0xB9AD, 0x572A5000 पूर्ण,
	अणु 0xB9AE, 0x00000003 पूर्ण,
	अणु 0xB9AF, 0x00000000 पूर्ण,
	अणु 0xB9B0, 0x10000000 पूर्ण,
	अणु 0xB828, 0x6C204010 पूर्ण,
	अणु 0xB829, 0x6C204011 पूर्ण,
	अणु 0xB82A, 0x6C204012 पूर्ण,
	अणु 0xB82B, 0x6C204013 पूर्ण,
	अणु 0xB82C, 0x6C204014 पूर्ण,
	अणु 0xB90F, 0x00000004 पूर्ण,
	अणु 0xB910, 0x00000002 पूर्ण,
	अणु 0xB911, 0x00000002 पूर्ण,
	अणु 0xB912, 0x00000002 पूर्ण,
	अणु 0xB913, 0x00000002 पूर्ण,
	अणु 0xB92F, 0x00000004 पूर्ण,
	अणु 0xB930, 0x00000005 पूर्ण,
	अणु 0xB931, 0x00000005 पूर्ण,
	अणु 0xB932, 0x00000005 पूर्ण,
	अणु 0xB933, 0x00000005 पूर्ण,
	अणु 0xB96F, 0x00000001 पूर्ण,
	अणु 0xB970, 0x00000003 पूर्ण,
	अणु 0xB94F, 0x00000004 पूर्ण,
	अणु 0xB950, 0x0000000B पूर्ण,
	अणु 0xB951, 0x0000000B पूर्ण,
	अणु 0xB952, 0x0000000B पूर्ण,
	अणु 0xB953, 0x0000000B पूर्ण,
	अणु 0xB907, 0x00000019 पूर्ण,
	अणु 0xB927, 0x00000019 पूर्ण,
	अणु 0xB947, 0x00000019 पूर्ण,
	अणु 0xB967, 0x00000019 पूर्ण,
	अणु 0xB987, 0x00000019 पूर्ण,
	अणु 0xB906, 0x00220001 पूर्ण,
	अणु 0xB926, 0x00220001 पूर्ण,
	अणु 0xB946, 0x00220001 पूर्ण,
	अणु 0xB966, 0x00220001 पूर्ण,
	अणु 0xB986, 0x00300000 पूर्ण,
	अणु 0xAC40, 0x0340FF41 पूर्ण,
	अणु 0xAC41, 0x03BEFED0 पूर्ण,
	अणु 0xAC42, 0x00331FED पूर्ण,
	अणु 0xAC43, 0x021FFDD3 पूर्ण,
	अणु 0xAC44, 0x5555AAAA पूर्ण,
	अणु 0xAC45, 0x5555AAAA पूर्ण,
	अणु 0xB9BA, 0x00000008 पूर्ण,
पूर्ण;

/*
 * Get the actual voltage value क्रम the operating poपूर्णांक at the specअगरied
 * frequency
 */
अटल अंतरभूत uपूर्णांक32_t _get_mvolts(काष्ठा msm_gpu *gpu, uपूर्णांक32_t freq)
अणु
	काष्ठा drm_device *dev = gpu->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा platक्रमm_device *pdev = priv->gpu_pdev;
	काष्ठा dev_pm_opp *opp;
	u32 ret = 0;

	opp = dev_pm_opp_find_freq_exact(&pdev->dev, freq, true);

	अगर (!IS_ERR(opp)) अणु
		ret = dev_pm_opp_get_voltage(opp) / 1000;
		dev_pm_opp_put(opp);
	पूर्ण

	वापस ret;
पूर्ण

/* Setup thermal limit management */
अटल व्योम a530_lm_setup(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	अचिन्हित पूर्णांक i;

	/* Write the block of sequence रेजिस्टरs */
	क्रम (i = 0; i < ARRAY_SIZE(a5xx_sequence_regs); i++)
		gpu_ग_लिखो(gpu, a5xx_sequence_regs[i].reg,
			a5xx_sequence_regs[i].value);

	/* Hard code the A530 GPU thermal sensor ID क्रम the GPMU */
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_TEMP_SENSOR_ID, 0x60007);
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_DELTA_TEMP_THRESHOLD, 0x01);
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_TEMP_SENSOR_CONFIG, 0x01);

	/* Until we get घड़ी scaling 0 is always the active घातer level */
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_GPMU_VOLTAGE, 0x80000000 | 0);

	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_BASE_LEAKAGE, a5xx_gpu->lm_leakage);

	/* The threshold is fixed at 6000 क्रम A530 */
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_GPMU_PWR_THRESHOLD, 0x80000000 | 6000);

	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_BEC_ENABLE, 0x10001FFF);
	gpu_ग_लिखो(gpu, REG_A5XX_GDPM_CONFIG1, 0x00201FF1);

	/* Write the voltage table */
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_BEC_ENABLE, 0x10001FFF);
	gpu_ग_लिखो(gpu, REG_A5XX_GDPM_CONFIG1, 0x201FF1);

	gpu_ग_लिखो(gpu, AGC_MSG_STATE, 1);
	gpu_ग_लिखो(gpu, AGC_MSG_COMMAND, AGC_POWER_CONFIG_PRODUCTION_ID);

	/* Write the max घातer - hard coded to 5448 क्रम A530 */
	gpu_ग_लिखो(gpu, AGC_MSG_PAYLOAD(0), 5448);
	gpu_ग_लिखो(gpu, AGC_MSG_PAYLOAD(1), 1);

	/*
	 * For now just ग_लिखो the one voltage level - we will करो more when we
	 * can करो scaling
	 */
	gpu_ग_लिखो(gpu, AGC_MSG_PAYLOAD(2), _get_mvolts(gpu, gpu->fast_rate));
	gpu_ग_लिखो(gpu, AGC_MSG_PAYLOAD(3), gpu->fast_rate / 1000000);

	gpu_ग_लिखो(gpu, AGC_MSG_PAYLOAD_SIZE, 4 * माप(uपूर्णांक32_t));
	gpu_ग_लिखो(gpu, AGC_INIT_MSG_MAGIC, AGC_INIT_MSG_VALUE);
पूर्ण

#घोषणा PAYLOAD_SIZE(_size) ((_size) * माप(u32))
#घोषणा LM_DCVS_LIMIT 1
#घोषणा LEVEL_CONFIG ~(0x303)

अटल व्योम a540_lm_setup(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	u32 config;

	/* The battery current limiter isn't enabled क्रम A540 */
	config = AGC_LM_CONFIG_BCL_DISABLED;
	config |= adreno_gpu->rev.patchid << AGC_LM_CONFIG_GPU_VERSION_SHIFT;

	/* For now disable GPMU side throttling */
	config |= AGC_LM_CONFIG_THROTTLE_DISABLE;

	/* Until we get घड़ी scaling 0 is always the active घातer level */
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_GPMU_VOLTAGE, 0x80000000 | 0);

	/* Fixed at 6000 क्रम now */
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_GPMU_PWR_THRESHOLD, 0x80000000 | 6000);

	gpu_ग_लिखो(gpu, AGC_MSG_STATE, 0x80000001);
	gpu_ग_लिखो(gpu, AGC_MSG_COMMAND, AGC_POWER_CONFIG_PRODUCTION_ID);

	gpu_ग_लिखो(gpu, AGC_MSG_PAYLOAD(0), 5448);
	gpu_ग_लिखो(gpu, AGC_MSG_PAYLOAD(1), 1);

	gpu_ग_लिखो(gpu, AGC_MSG_PAYLOAD(2), _get_mvolts(gpu, gpu->fast_rate));
	gpu_ग_लिखो(gpu, AGC_MSG_PAYLOAD(3), gpu->fast_rate / 1000000);

	gpu_ग_लिखो(gpu, AGC_MSG_PAYLOAD(AGC_LM_CONFIG), config);
	gpu_ग_लिखो(gpu, AGC_MSG_PAYLOAD(AGC_LEVEL_CONFIG), LEVEL_CONFIG);
	gpu_ग_लिखो(gpu, AGC_MSG_PAYLOAD_SIZE,
	PAYLOAD_SIZE(AGC_LEVEL_CONFIG + 1));

	gpu_ग_लिखो(gpu, AGC_INIT_MSG_MAGIC, AGC_INIT_MSG_VALUE);
पूर्ण

/* Enable SP/TP cघातer collapse */
अटल व्योम a5xx_pc_init(काष्ठा msm_gpu *gpu)
अणु
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_PWR_COL_INTER_FRAME_CTRL, 0x7F);
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_PWR_COL_BINNING_CTRL, 0);
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_PWR_COL_INTER_FRAME_HYST, 0xA0080);
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_PWR_COL_STAGGER_DELAY, 0x600040);
पूर्ण

/* Enable the GPMU microcontroller */
अटल पूर्णांक a5xx_gpmu_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	काष्ठा msm_ringbuffer *ring = gpu->rb[0];

	अगर (!a5xx_gpu->gpmu_dwords)
		वापस 0;

	/* Turn off रक्षित mode क्रम this operation */
	OUT_PKT7(ring, CP_SET_PROTECTED_MODE, 1);
	OUT_RING(ring, 0);

	/* Kick off the IB to load the GPMU microcode */
	OUT_PKT7(ring, CP_INसूचीECT_BUFFER_PFE, 3);
	OUT_RING(ring, lower_32_bits(a5xx_gpu->gpmu_iova));
	OUT_RING(ring, upper_32_bits(a5xx_gpu->gpmu_iova));
	OUT_RING(ring, a5xx_gpu->gpmu_dwords);

	/* Turn back on रक्षित mode */
	OUT_PKT7(ring, CP_SET_PROTECTED_MODE, 1);
	OUT_RING(ring, 1);

	a5xx_flush(gpu, ring, true);

	अगर (!a5xx_idle(gpu, ring)) अणु
		DRM_ERROR("%s: Unable to load GPMU firmware. GPMU will not be active\n",
			gpu->name);
		वापस -EINVAL;
	पूर्ण

	अगर (adreno_is_a530(adreno_gpu))
		gpu_ग_लिखो(gpu, REG_A5XX_GPMU_WFI_CONFIG, 0x4014);

	/* Kick off the GPMU */
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_CM3_SYSRESET, 0x0);

	/*
	 * Wait क्रम the GPMU to respond. It isn't fatal if it doesn't, we just
	 * won't have advanced घातer collapse.
	 */
	अगर (spin_usecs(gpu, 25, REG_A5XX_GPMU_GENERAL_0, 0xFFFFFFFF,
		0xBABEFACE))
		DRM_ERROR("%s: GPMU firmware initialization timed out\n",
			gpu->name);

	अगर (!adreno_is_a530(adreno_gpu)) अणु
		u32 val = gpu_पढ़ो(gpu, REG_A5XX_GPMU_GENERAL_1);

		अगर (val)
			DRM_ERROR("%s: GPMU firmware initialization failed: %d\n",
				  gpu->name, val);
	पूर्ण

	वापस 0;
पूर्ण

/* Enable limits management */
अटल व्योम a5xx_lm_enable(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);

	/* This init sequence only applies to A530 */
	अगर (!adreno_is_a530(adreno_gpu))
		वापस;

	gpu_ग_लिखो(gpu, REG_A5XX_GDPM_INT_MASK, 0x0);
	gpu_ग_लिखो(gpu, REG_A5XX_GDPM_INT_EN, 0x0A);
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_GPMU_VOLTAGE_INTR_EN_MASK, 0x01);
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_TEMP_THRESHOLD_INTR_EN_MASK, 0x50000);
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_THROTTLE_UNMASK_FORCE_CTRL, 0x30000);

	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_CLOCK_THROTTLE_CTRL, 0x011);
पूर्ण

पूर्णांक a5xx_घातer_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	पूर्णांक ret;

	/* Not all A5xx chips have a GPMU */
	अगर (!(adreno_is_a530(adreno_gpu) || adreno_is_a540(adreno_gpu)))
		वापस 0;

	/* Set up the limits management */
	अगर (adreno_is_a530(adreno_gpu))
		a530_lm_setup(gpu);
	अन्यथा अगर (adreno_is_a540(adreno_gpu))
		a540_lm_setup(gpu);

	/* Set up SP/TP घातer collpase */
	a5xx_pc_init(gpu);

	/* Start the GPMU */
	ret = a5xx_gpmu_init(gpu);
	अगर (ret)
		वापस ret;

	/* Start the limits management */
	a5xx_lm_enable(gpu);

	वापस 0;
पूर्ण

व्योम a5xx_gpmu_ucode_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	काष्ठा drm_device *drm = gpu->dev;
	uपूर्णांक32_t dwords = 0, offset = 0, bosize;
	अचिन्हित पूर्णांक *data, *ptr, *cmds;
	अचिन्हित पूर्णांक cmds_size;

	अगर (!(adreno_is_a530(adreno_gpu) || adreno_is_a540(adreno_gpu)))
		वापस;

	अगर (a5xx_gpu->gpmu_bo)
		वापस;

	data = (अचिन्हित पूर्णांक *) adreno_gpu->fw[ADRENO_FW_GPMU]->data;

	/*
	 * The first dword is the size of the reमुख्यing data in dwords. Use it
	 * as a checksum of sorts and make sure it matches the actual size of
	 * the firmware that we पढ़ो
	 */

	अगर (adreno_gpu->fw[ADRENO_FW_GPMU]->size < 8 ||
		(data[0] < 2) || (data[0] >=
			(adreno_gpu->fw[ADRENO_FW_GPMU]->size >> 2)))
		वापस;

	/* The second dword is an ID - look क्रम 2 (GPMU_FIRMWARE_ID) */
	अगर (data[1] != 2)
		वापस;

	cmds = data + data[2] + 3;
	cmds_size = data[0] - data[2] - 2;

	/*
	 * A single type4 opcode can only have so many values attached so
	 * add enough opcodes to load the all the commands
	 */
	bosize = (cmds_size + (cmds_size / TYPE4_MAX_PAYLOAD) + 1) << 2;

	ptr = msm_gem_kernel_new_locked(drm, bosize,
		MSM_BO_UNCACHED | MSM_BO_GPU_READONLY, gpu->aspace,
		&a5xx_gpu->gpmu_bo, &a5xx_gpu->gpmu_iova);
	अगर (IS_ERR(ptr))
		वापस;

	msm_gem_object_set_name(a5xx_gpu->gpmu_bo, "gpmufw");

	जबतक (cmds_size > 0) अणु
		पूर्णांक i;
		uपूर्णांक32_t _size = cmds_size > TYPE4_MAX_PAYLOAD ?
			TYPE4_MAX_PAYLOAD : cmds_size;

		ptr[dwords++] = PKT4(REG_A5XX_GPMU_INST_RAM_BASE + offset,
			_size);

		क्रम (i = 0; i < _size; i++)
			ptr[dwords++] = *cmds++;

		offset += _size;
		cmds_size -= _size;
	पूर्ण

	msm_gem_put_vaddr(a5xx_gpu->gpmu_bo);
	a5xx_gpu->gpmu_dwords = dwords;
पूर्ण
