<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2018 Etnaviv Project
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-fence.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/thermal.h>

#समावेश "etnaviv_cmdbuf.h"
#समावेश "etnaviv_dump.h"
#समावेश "etnaviv_gpu.h"
#समावेश "etnaviv_gem.h"
#समावेश "etnaviv_mmu.h"
#समावेश "etnaviv_perfmon.h"
#समावेश "etnaviv_sched.h"
#समावेश "common.xml.h"
#समावेश "state.xml.h"
#समावेश "state_hi.xml.h"
#समावेश "cmdstream.xml.h"

#अगर_अघोषित PHYS_OFFSET
#घोषणा PHYS_OFFSET 0
#पूर्ण_अगर

अटल स्थिर काष्ठा platक्रमm_device_id gpu_ids[] = अणु
	अणु .name = "etnaviv-gpu,2d" पूर्ण,
	अणु पूर्ण,
पूर्ण;

/*
 * Driver functions:
 */

पूर्णांक etnaviv_gpu_get_param(काष्ठा etnaviv_gpu *gpu, u32 param, u64 *value)
अणु
	काष्ठा etnaviv_drm_निजी *priv = gpu->drm->dev_निजी;

	चयन (param) अणु
	हाल ETNAVIV_PARAM_GPU_MODEL:
		*value = gpu->identity.model;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_REVISION:
		*value = gpu->identity.revision;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_FEATURES_0:
		*value = gpu->identity.features;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_FEATURES_1:
		*value = gpu->identity.minor_features0;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_FEATURES_2:
		*value = gpu->identity.minor_features1;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_FEATURES_3:
		*value = gpu->identity.minor_features2;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_FEATURES_4:
		*value = gpu->identity.minor_features3;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_FEATURES_5:
		*value = gpu->identity.minor_features4;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_FEATURES_6:
		*value = gpu->identity.minor_features5;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_FEATURES_7:
		*value = gpu->identity.minor_features6;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_FEATURES_8:
		*value = gpu->identity.minor_features7;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_FEATURES_9:
		*value = gpu->identity.minor_features8;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_FEATURES_10:
		*value = gpu->identity.minor_features9;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_FEATURES_11:
		*value = gpu->identity.minor_features10;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_FEATURES_12:
		*value = gpu->identity.minor_features11;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_STREAM_COUNT:
		*value = gpu->identity.stream_count;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_REGISTER_MAX:
		*value = gpu->identity.रेजिस्टर_max;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_THREAD_COUNT:
		*value = gpu->identity.thपढ़ो_count;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_VERTEX_CACHE_SIZE:
		*value = gpu->identity.vertex_cache_size;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_SHADER_CORE_COUNT:
		*value = gpu->identity.shader_core_count;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_PIXEL_PIPES:
		*value = gpu->identity.pixel_pipes;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_VERTEX_OUTPUT_BUFFER_SIZE:
		*value = gpu->identity.vertex_output_buffer_size;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_BUFFER_SIZE:
		*value = gpu->identity.buffer_size;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_INSTRUCTION_COUNT:
		*value = gpu->identity.inकाष्ठाion_count;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_NUM_CONSTANTS:
		*value = gpu->identity.num_स्थिरants;
		अवरोध;

	हाल ETNAVIV_PARAM_GPU_NUM_VARYINGS:
		*value = gpu->identity.varyings_count;
		अवरोध;

	हाल ETNAVIV_PARAM_SOFTPIN_START_ADDR:
		अगर (priv->mmu_global->version == ETNAVIV_IOMMU_V2)
			*value = ETNAVIV_SOFTPIN_START_ADDRESS;
		अन्यथा
			*value = ~0ULL;
		अवरोध;

	शेष:
		DBG("%s: invalid param: %u", dev_name(gpu->dev), param);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


#घोषणा etnaviv_is_model_rev(gpu, mod, rev) \
	((gpu)->identity.model == chipModel_##mod && \
	 (gpu)->identity.revision == rev)
#घोषणा etnaviv_field(val, field) \
	(((val) & field##__MASK) >> field##__SHIFT)

अटल व्योम etnaviv_hw_specs(काष्ठा etnaviv_gpu *gpu)
अणु
	अगर (gpu->identity.minor_features0 &
	    chipMinorFeatures0_MORE_MINOR_FEATURES) अणु
		u32 specs[4];
		अचिन्हित पूर्णांक streams;

		specs[0] = gpu_पढ़ो(gpu, VIVS_HI_CHIP_SPECS);
		specs[1] = gpu_पढ़ो(gpu, VIVS_HI_CHIP_SPECS_2);
		specs[2] = gpu_पढ़ो(gpu, VIVS_HI_CHIP_SPECS_3);
		specs[3] = gpu_पढ़ो(gpu, VIVS_HI_CHIP_SPECS_4);

		gpu->identity.stream_count = etnaviv_field(specs[0],
					VIVS_HI_CHIP_SPECS_STREAM_COUNT);
		gpu->identity.रेजिस्टर_max = etnaviv_field(specs[0],
					VIVS_HI_CHIP_SPECS_REGISTER_MAX);
		gpu->identity.thपढ़ो_count = etnaviv_field(specs[0],
					VIVS_HI_CHIP_SPECS_THREAD_COUNT);
		gpu->identity.vertex_cache_size = etnaviv_field(specs[0],
					VIVS_HI_CHIP_SPECS_VERTEX_CACHE_SIZE);
		gpu->identity.shader_core_count = etnaviv_field(specs[0],
					VIVS_HI_CHIP_SPECS_SHADER_CORE_COUNT);
		gpu->identity.pixel_pipes = etnaviv_field(specs[0],
					VIVS_HI_CHIP_SPECS_PIXEL_PIPES);
		gpu->identity.vertex_output_buffer_size =
			etnaviv_field(specs[0],
				VIVS_HI_CHIP_SPECS_VERTEX_OUTPUT_BUFFER_SIZE);

		gpu->identity.buffer_size = etnaviv_field(specs[1],
					VIVS_HI_CHIP_SPECS_2_BUFFER_SIZE);
		gpu->identity.inकाष्ठाion_count = etnaviv_field(specs[1],
					VIVS_HI_CHIP_SPECS_2_INSTRUCTION_COUNT);
		gpu->identity.num_स्थिरants = etnaviv_field(specs[1],
					VIVS_HI_CHIP_SPECS_2_NUM_CONSTANTS);

		gpu->identity.varyings_count = etnaviv_field(specs[2],
					VIVS_HI_CHIP_SPECS_3_VARYINGS_COUNT);

		/* This overrides the value from older रेजिस्टर अगर non-zero */
		streams = etnaviv_field(specs[3],
					VIVS_HI_CHIP_SPECS_4_STREAM_COUNT);
		अगर (streams)
			gpu->identity.stream_count = streams;
	पूर्ण

	/* Fill in the stream count अगर not specअगरied */
	अगर (gpu->identity.stream_count == 0) अणु
		अगर (gpu->identity.model >= 0x1000)
			gpu->identity.stream_count = 4;
		अन्यथा
			gpu->identity.stream_count = 1;
	पूर्ण

	/* Convert the रेजिस्टर max value */
	अगर (gpu->identity.रेजिस्टर_max)
		gpu->identity.रेजिस्टर_max = 1 << gpu->identity.रेजिस्टर_max;
	अन्यथा अगर (gpu->identity.model == chipModel_GC400)
		gpu->identity.रेजिस्टर_max = 32;
	अन्यथा
		gpu->identity.रेजिस्टर_max = 64;

	/* Convert thपढ़ो count */
	अगर (gpu->identity.thपढ़ो_count)
		gpu->identity.thपढ़ो_count = 1 << gpu->identity.thपढ़ो_count;
	अन्यथा अगर (gpu->identity.model == chipModel_GC400)
		gpu->identity.thपढ़ो_count = 64;
	अन्यथा अगर (gpu->identity.model == chipModel_GC500 ||
		 gpu->identity.model == chipModel_GC530)
		gpu->identity.thपढ़ो_count = 128;
	अन्यथा
		gpu->identity.thपढ़ो_count = 256;

	अगर (gpu->identity.vertex_cache_size == 0)
		gpu->identity.vertex_cache_size = 8;

	अगर (gpu->identity.shader_core_count == 0) अणु
		अगर (gpu->identity.model >= 0x1000)
			gpu->identity.shader_core_count = 2;
		अन्यथा
			gpu->identity.shader_core_count = 1;
	पूर्ण

	अगर (gpu->identity.pixel_pipes == 0)
		gpu->identity.pixel_pipes = 1;

	/* Convert virtex buffer size */
	अगर (gpu->identity.vertex_output_buffer_size) अणु
		gpu->identity.vertex_output_buffer_size =
			1 << gpu->identity.vertex_output_buffer_size;
	पूर्ण अन्यथा अगर (gpu->identity.model == chipModel_GC400) अणु
		अगर (gpu->identity.revision < 0x4000)
			gpu->identity.vertex_output_buffer_size = 512;
		अन्यथा अगर (gpu->identity.revision < 0x4200)
			gpu->identity.vertex_output_buffer_size = 256;
		अन्यथा
			gpu->identity.vertex_output_buffer_size = 128;
	पूर्ण अन्यथा अणु
		gpu->identity.vertex_output_buffer_size = 512;
	पूर्ण

	चयन (gpu->identity.inकाष्ठाion_count) अणु
	हाल 0:
		अगर (etnaviv_is_model_rev(gpu, GC2000, 0x5108) ||
		    gpu->identity.model == chipModel_GC880)
			gpu->identity.inकाष्ठाion_count = 512;
		अन्यथा
			gpu->identity.inकाष्ठाion_count = 256;
		अवरोध;

	हाल 1:
		gpu->identity.inकाष्ठाion_count = 1024;
		अवरोध;

	हाल 2:
		gpu->identity.inकाष्ठाion_count = 2048;
		अवरोध;

	शेष:
		gpu->identity.inकाष्ठाion_count = 256;
		अवरोध;
	पूर्ण

	अगर (gpu->identity.num_स्थिरants == 0)
		gpu->identity.num_स्थिरants = 168;

	अगर (gpu->identity.varyings_count == 0) अणु
		अगर (gpu->identity.minor_features1 & chipMinorFeatures1_HALTI0)
			gpu->identity.varyings_count = 12;
		अन्यथा
			gpu->identity.varyings_count = 8;
	पूर्ण

	/*
	 * For some cores, two varyings are consumed क्रम position, so the
	 * maximum varying count needs to be reduced by one.
	 */
	अगर (etnaviv_is_model_rev(gpu, GC5000, 0x5434) ||
	    etnaviv_is_model_rev(gpu, GC4000, 0x5222) ||
	    etnaviv_is_model_rev(gpu, GC4000, 0x5245) ||
	    etnaviv_is_model_rev(gpu, GC4000, 0x5208) ||
	    etnaviv_is_model_rev(gpu, GC3000, 0x5435) ||
	    etnaviv_is_model_rev(gpu, GC2200, 0x5244) ||
	    etnaviv_is_model_rev(gpu, GC2100, 0x5108) ||
	    etnaviv_is_model_rev(gpu, GC2000, 0x5108) ||
	    etnaviv_is_model_rev(gpu, GC1500, 0x5246) ||
	    etnaviv_is_model_rev(gpu, GC880, 0x5107) ||
	    etnaviv_is_model_rev(gpu, GC880, 0x5106))
		gpu->identity.varyings_count -= 1;
पूर्ण

अटल व्योम etnaviv_hw_identअगरy(काष्ठा etnaviv_gpu *gpu)
अणु
	u32 chipIdentity;

	chipIdentity = gpu_पढ़ो(gpu, VIVS_HI_CHIP_IDENTITY);

	/* Special हाल क्रम older graphic cores. */
	अगर (etnaviv_field(chipIdentity, VIVS_HI_CHIP_IDENTITY_FAMILY) == 0x01) अणु
		gpu->identity.model    = chipModel_GC500;
		gpu->identity.revision = etnaviv_field(chipIdentity,
					 VIVS_HI_CHIP_IDENTITY_REVISION);
	पूर्ण अन्यथा अणु
		u32 chipDate = gpu_पढ़ो(gpu, VIVS_HI_CHIP_DATE);

		gpu->identity.model = gpu_पढ़ो(gpu, VIVS_HI_CHIP_MODEL);
		gpu->identity.revision = gpu_पढ़ो(gpu, VIVS_HI_CHIP_REV);
		gpu->identity.customer_id = gpu_पढ़ो(gpu, VIVS_HI_CHIP_CUSTOMER_ID);

		/*
		 * Reading these two रेजिस्टरs on GC600 rev 0x19 result in a
		 * unhandled fault: बाह्यal पात on non-linefetch
		 */
		अगर (!etnaviv_is_model_rev(gpu, GC600, 0x19)) अणु
			gpu->identity.product_id = gpu_पढ़ो(gpu, VIVS_HI_CHIP_PRODUCT_ID);
			gpu->identity.eco_id = gpu_पढ़ो(gpu, VIVS_HI_CHIP_ECO_ID);
		पूर्ण

		/*
		 * !!!! HACK ALERT !!!!
		 * Because people change device IDs without letting software
		 * know about it - here is the hack to make it all look the
		 * same.  Only क्रम GC400 family.
		 */
		अगर ((gpu->identity.model & 0xff00) == 0x0400 &&
		    gpu->identity.model != chipModel_GC420) अणु
			gpu->identity.model = gpu->identity.model & 0x0400;
		पूर्ण

		/* Another special हाल */
		अगर (etnaviv_is_model_rev(gpu, GC300, 0x2201)) अणु
			u32 chipTime = gpu_पढ़ो(gpu, VIVS_HI_CHIP_TIME);

			अगर (chipDate == 0x20080814 && chipTime == 0x12051100) अणु
				/*
				 * This IP has an ECO; put the correct
				 * revision in it.
				 */
				gpu->identity.revision = 0x1051;
			पूर्ण
		पूर्ण

		/*
		 * NXP likes to call the GPU on the i.MX6QP GC2000+, but in
		 * reality it's just a re-bअक्रमed GC3000. We can identअगरy this
		 * core by the upper half of the revision रेजिस्टर being all 1.
		 * Fix model/rev here, so all other places can refer to this
		 * core by its real identity.
		 */
		अगर (etnaviv_is_model_rev(gpu, GC2000, 0xffff5450)) अणु
			gpu->identity.model = chipModel_GC3000;
			gpu->identity.revision &= 0xffff;
		पूर्ण

		अगर (etnaviv_is_model_rev(gpu, GC1000, 0x5037) && (chipDate == 0x20120617))
			gpu->identity.eco_id = 1;

		अगर (etnaviv_is_model_rev(gpu, GC320, 0x5303) && (chipDate == 0x20140511))
			gpu->identity.eco_id = 1;
	पूर्ण

	dev_info(gpu->dev, "model: GC%x, revision: %x\n",
		 gpu->identity.model, gpu->identity.revision);

	gpu->idle_mask = ~VIVS_HI_IDLE_STATE_AXI_LP;
	/*
	 * If there is a match in the HWDB, we aren't पूर्णांकerested in the
	 * reमुख्यing रेजिस्टर values, as they might be wrong.
	 */
	अगर (etnaviv_fill_identity_from_hwdb(gpu))
		वापस;

	gpu->identity.features = gpu_पढ़ो(gpu, VIVS_HI_CHIP_FEATURE);

	/* Disable fast clear on GC700. */
	अगर (gpu->identity.model == chipModel_GC700)
		gpu->identity.features &= ~chipFeatures_FAST_CLEAR;

	अगर ((gpu->identity.model == chipModel_GC500 &&
	     gpu->identity.revision < 2) ||
	    (gpu->identity.model == chipModel_GC300 &&
	     gpu->identity.revision < 0x2000)) अणु

		/*
		 * GC500 rev 1.x and GC300 rev < 2.0 करोesn't have these
		 * रेजिस्टरs.
		 */
		gpu->identity.minor_features0 = 0;
		gpu->identity.minor_features1 = 0;
		gpu->identity.minor_features2 = 0;
		gpu->identity.minor_features3 = 0;
		gpu->identity.minor_features4 = 0;
		gpu->identity.minor_features5 = 0;
	पूर्ण अन्यथा
		gpu->identity.minor_features0 =
				gpu_पढ़ो(gpu, VIVS_HI_CHIP_MINOR_FEATURE_0);

	अगर (gpu->identity.minor_features0 &
	    chipMinorFeatures0_MORE_MINOR_FEATURES) अणु
		gpu->identity.minor_features1 =
				gpu_पढ़ो(gpu, VIVS_HI_CHIP_MINOR_FEATURE_1);
		gpu->identity.minor_features2 =
				gpu_पढ़ो(gpu, VIVS_HI_CHIP_MINOR_FEATURE_2);
		gpu->identity.minor_features3 =
				gpu_पढ़ो(gpu, VIVS_HI_CHIP_MINOR_FEATURE_3);
		gpu->identity.minor_features4 =
				gpu_पढ़ो(gpu, VIVS_HI_CHIP_MINOR_FEATURE_4);
		gpu->identity.minor_features5 =
				gpu_पढ़ो(gpu, VIVS_HI_CHIP_MINOR_FEATURE_5);
	पूर्ण

	/* GC600 idle रेजिस्टर reports zero bits where modules aren't present */
	अगर (gpu->identity.model == chipModel_GC600)
		gpu->idle_mask = VIVS_HI_IDLE_STATE_TX |
				 VIVS_HI_IDLE_STATE_RA |
				 VIVS_HI_IDLE_STATE_SE |
				 VIVS_HI_IDLE_STATE_PA |
				 VIVS_HI_IDLE_STATE_SH |
				 VIVS_HI_IDLE_STATE_PE |
				 VIVS_HI_IDLE_STATE_DE |
				 VIVS_HI_IDLE_STATE_FE;

	etnaviv_hw_specs(gpu);
पूर्ण

अटल व्योम etnaviv_gpu_load_घड़ी(काष्ठा etnaviv_gpu *gpu, u32 घड़ी)
अणु
	gpu_ग_लिखो(gpu, VIVS_HI_CLOCK_CONTROL, घड़ी |
		  VIVS_HI_CLOCK_CONTROL_FSCALE_CMD_LOAD);
	gpu_ग_लिखो(gpu, VIVS_HI_CLOCK_CONTROL, घड़ी);
पूर्ण

अटल व्योम etnaviv_gpu_update_घड़ी(काष्ठा etnaviv_gpu *gpu)
अणु
	अगर (gpu->identity.minor_features2 &
	    chipMinorFeatures2_DYNAMIC_FREQUENCY_SCALING) अणु
		clk_set_rate(gpu->clk_core,
			     gpu->base_rate_core >> gpu->freq_scale);
		clk_set_rate(gpu->clk_shader,
			     gpu->base_rate_shader >> gpu->freq_scale);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक fscale = 1 << (6 - gpu->freq_scale);
		u32 घड़ी = gpu_पढ़ो(gpu, VIVS_HI_CLOCK_CONTROL);

		घड़ी &= ~VIVS_HI_CLOCK_CONTROL_FSCALE_VAL__MASK;
		घड़ी |= VIVS_HI_CLOCK_CONTROL_FSCALE_VAL(fscale);
		etnaviv_gpu_load_घड़ी(gpu, घड़ी);
	पूर्ण
पूर्ण

अटल पूर्णांक etnaviv_hw_reset(काष्ठा etnaviv_gpu *gpu)
अणु
	u32 control, idle;
	अचिन्हित दीर्घ समयout;
	bool failed = true;

	/* We hope that the GPU resets in under one second */
	समयout = jअगरfies + msecs_to_jअगरfies(1000);

	जबतक (समय_is_after_jअगरfies(समयout)) अणु
		/* enable घड़ी */
		अचिन्हित पूर्णांक fscale = 1 << (6 - gpu->freq_scale);
		control = VIVS_HI_CLOCK_CONTROL_FSCALE_VAL(fscale);
		etnaviv_gpu_load_घड़ी(gpu, control);

		/* isolate the GPU. */
		control |= VIVS_HI_CLOCK_CONTROL_ISOLATE_GPU;
		gpu_ग_लिखो(gpu, VIVS_HI_CLOCK_CONTROL, control);

		अगर (gpu->sec_mode == ETNA_SEC_KERNEL) अणु
			gpu_ग_लिखो(gpu, VIVS_MMUv2_AHB_CONTROL,
			          VIVS_MMUv2_AHB_CONTROL_RESET);
		पूर्ण अन्यथा अणु
			/* set soft reset. */
			control |= VIVS_HI_CLOCK_CONTROL_SOFT_RESET;
			gpu_ग_लिखो(gpu, VIVS_HI_CLOCK_CONTROL, control);
		पूर्ण

		/* रुको क्रम reset. */
		usleep_range(10, 20);

		/* reset soft reset bit. */
		control &= ~VIVS_HI_CLOCK_CONTROL_SOFT_RESET;
		gpu_ग_लिखो(gpu, VIVS_HI_CLOCK_CONTROL, control);

		/* reset GPU isolation. */
		control &= ~VIVS_HI_CLOCK_CONTROL_ISOLATE_GPU;
		gpu_ग_लिखो(gpu, VIVS_HI_CLOCK_CONTROL, control);

		/* पढ़ो idle रेजिस्टर. */
		idle = gpu_पढ़ो(gpu, VIVS_HI_IDLE_STATE);

		/* try resetting again अगर FE is not idle */
		अगर ((idle & VIVS_HI_IDLE_STATE_FE) == 0) अणु
			dev_dbg(gpu->dev, "FE is not idle\n");
			जारी;
		पूर्ण

		/* पढ़ो reset रेजिस्टर. */
		control = gpu_पढ़ो(gpu, VIVS_HI_CLOCK_CONTROL);

		/* is the GPU idle? */
		अगर (((control & VIVS_HI_CLOCK_CONTROL_IDLE_3D) == 0) ||
		    ((control & VIVS_HI_CLOCK_CONTROL_IDLE_2D) == 0)) अणु
			dev_dbg(gpu->dev, "GPU is not idle\n");
			जारी;
		पूर्ण

		/* disable debug रेजिस्टरs, as they are not normally needed */
		control |= VIVS_HI_CLOCK_CONTROL_DISABLE_DEBUG_REGISTERS;
		gpu_ग_लिखो(gpu, VIVS_HI_CLOCK_CONTROL, control);

		failed = false;
		अवरोध;
	पूर्ण

	अगर (failed) अणु
		idle = gpu_पढ़ो(gpu, VIVS_HI_IDLE_STATE);
		control = gpu_पढ़ो(gpu, VIVS_HI_CLOCK_CONTROL);

		dev_err(gpu->dev, "GPU failed to reset: FE %sidle, 3D %sidle, 2D %sidle\n",
			idle & VIVS_HI_IDLE_STATE_FE ? "" : "not ",
			control & VIVS_HI_CLOCK_CONTROL_IDLE_3D ? "" : "not ",
			control & VIVS_HI_CLOCK_CONTROL_IDLE_2D ? "" : "not ");

		वापस -EBUSY;
	पूर्ण

	/* We rely on the GPU running, so program the घड़ी */
	etnaviv_gpu_update_घड़ी(gpu);

	वापस 0;
पूर्ण

अटल व्योम etnaviv_gpu_enable_mlcg(काष्ठा etnaviv_gpu *gpu)
अणु
	u32 pmc, ppc;

	/* enable घड़ी gating */
	ppc = gpu_पढ़ो(gpu, VIVS_PM_POWER_CONTROLS);
	ppc |= VIVS_PM_POWER_CONTROLS_ENABLE_MODULE_CLOCK_GATING;

	/* Disable stall module घड़ी gating क्रम 4.3.0.1 and 4.3.0.2 revs */
	अगर (gpu->identity.revision == 0x4301 ||
	    gpu->identity.revision == 0x4302)
		ppc |= VIVS_PM_POWER_CONTROLS_DISABLE_STALL_MODULE_CLOCK_GATING;

	gpu_ग_लिखो(gpu, VIVS_PM_POWER_CONTROLS, ppc);

	pmc = gpu_पढ़ो(gpu, VIVS_PM_MODULE_CONTROLS);

	/* Disable PA घड़ी gating क्रम GC400+ without bugfix except क्रम GC420 */
	अगर (gpu->identity.model >= chipModel_GC400 &&
	    gpu->identity.model != chipModel_GC420 &&
	    !(gpu->identity.minor_features3 & chipMinorFeatures3_BUG_FIXES12))
		pmc |= VIVS_PM_MODULE_CONTROLS_DISABLE_MODULE_CLOCK_GATING_PA;

	/*
	 * Disable PE घड़ी gating on revs < 5.0.0.0 when HZ is
	 * present without a bug fix.
	 */
	अगर (gpu->identity.revision < 0x5000 &&
	    gpu->identity.minor_features0 & chipMinorFeatures0_HZ &&
	    !(gpu->identity.minor_features1 &
	      chipMinorFeatures1_DISABLE_PE_GATING))
		pmc |= VIVS_PM_MODULE_CONTROLS_DISABLE_MODULE_CLOCK_GATING_PE;

	अगर (gpu->identity.revision < 0x5422)
		pmc |= BIT(15); /* Unknown bit */

	/* Disable TX घड़ी gating on affected core revisions. */
	अगर (etnaviv_is_model_rev(gpu, GC4000, 0x5222) ||
	    etnaviv_is_model_rev(gpu, GC2000, 0x5108))
		pmc |= VIVS_PM_MODULE_CONTROLS_DISABLE_MODULE_CLOCK_GATING_TX;

	pmc |= VIVS_PM_MODULE_CONTROLS_DISABLE_MODULE_CLOCK_GATING_RA_HZ;
	pmc |= VIVS_PM_MODULE_CONTROLS_DISABLE_MODULE_CLOCK_GATING_RA_EZ;

	gpu_ग_लिखो(gpu, VIVS_PM_MODULE_CONTROLS, pmc);
पूर्ण

व्योम etnaviv_gpu_start_fe(काष्ठा etnaviv_gpu *gpu, u32 address, u16 prefetch)
अणु
	gpu_ग_लिखो(gpu, VIVS_FE_COMMAND_ADDRESS, address);
	gpu_ग_लिखो(gpu, VIVS_FE_COMMAND_CONTROL,
		  VIVS_FE_COMMAND_CONTROL_ENABLE |
		  VIVS_FE_COMMAND_CONTROL_PREFETCH(prefetch));

	अगर (gpu->sec_mode == ETNA_SEC_KERNEL) अणु
		gpu_ग_लिखो(gpu, VIVS_MMUv2_SEC_COMMAND_CONTROL,
			  VIVS_MMUv2_SEC_COMMAND_CONTROL_ENABLE |
			  VIVS_MMUv2_SEC_COMMAND_CONTROL_PREFETCH(prefetch));
	पूर्ण
पूर्ण

अटल व्योम etnaviv_gpu_start_fe_idleloop(काष्ठा etnaviv_gpu *gpu)
अणु
	u32 address = etnaviv_cmdbuf_get_va(&gpu->buffer,
				&gpu->mmu_context->cmdbuf_mapping);
	u16 prefetch;

	/* setup the MMU */
	etnaviv_iommu_restore(gpu, gpu->mmu_context);

	/* Start command processor */
	prefetch = etnaviv_buffer_init(gpu);

	etnaviv_gpu_start_fe(gpu, address, prefetch);
पूर्ण

अटल व्योम etnaviv_gpu_setup_pulse_eater(काष्ठा etnaviv_gpu *gpu)
अणु
	/*
	 * Base value क्रम VIVS_PM_PULSE_EATER रेजिस्टर on models where it
	 * cannot be पढ़ो, extracted from vivante kernel driver.
	 */
	u32 pulse_eater = 0x01590880;

	अगर (etnaviv_is_model_rev(gpu, GC4000, 0x5208) ||
	    etnaviv_is_model_rev(gpu, GC4000, 0x5222)) अणु
		pulse_eater |= BIT(23);

	पूर्ण

	अगर (etnaviv_is_model_rev(gpu, GC1000, 0x5039) ||
	    etnaviv_is_model_rev(gpu, GC1000, 0x5040)) अणु
		pulse_eater &= ~BIT(16);
		pulse_eater |= BIT(17);
	पूर्ण

	अगर ((gpu->identity.revision > 0x5420) &&
	    (gpu->identity.features & chipFeatures_PIPE_3D))
	अणु
		/* Perक्रमmance fix: disable पूर्णांकernal DFS */
		pulse_eater = gpu_पढ़ो(gpu, VIVS_PM_PULSE_EATER);
		pulse_eater |= BIT(18);
	पूर्ण

	gpu_ग_लिखो(gpu, VIVS_PM_PULSE_EATER, pulse_eater);
पूर्ण

अटल व्योम etnaviv_gpu_hw_init(काष्ठा etnaviv_gpu *gpu)
अणु
	अगर ((etnaviv_is_model_rev(gpu, GC320, 0x5007) ||
	     etnaviv_is_model_rev(gpu, GC320, 0x5220)) &&
	    gpu_पढ़ो(gpu, VIVS_HI_CHIP_TIME) != 0x2062400) अणु
		u32 mc_memory_debug;

		mc_memory_debug = gpu_पढ़ो(gpu, VIVS_MC_DEBUG_MEMORY) & ~0xff;

		अगर (gpu->identity.revision == 0x5007)
			mc_memory_debug |= 0x0c;
		अन्यथा
			mc_memory_debug |= 0x08;

		gpu_ग_लिखो(gpu, VIVS_MC_DEBUG_MEMORY, mc_memory_debug);
	पूर्ण

	/* enable module-level घड़ी gating */
	etnaviv_gpu_enable_mlcg(gpu);

	/*
	 * Update GPU AXI cache atttribute to "cacheable, no allocate".
	 * This is necessary to prevent the iMX6 SoC locking up.
	 */
	gpu_ग_लिखो(gpu, VIVS_HI_AXI_CONFIG,
		  VIVS_HI_AXI_CONFIG_AWCACHE(2) |
		  VIVS_HI_AXI_CONFIG_ARCACHE(2));

	/* GC2000 rev 5108 needs a special bus config */
	अगर (etnaviv_is_model_rev(gpu, GC2000, 0x5108)) अणु
		u32 bus_config = gpu_पढ़ो(gpu, VIVS_MC_BUS_CONFIG);
		bus_config &= ~(VIVS_MC_BUS_CONFIG_FE_BUS_CONFIG__MASK |
				VIVS_MC_BUS_CONFIG_TX_BUS_CONFIG__MASK);
		bus_config |= VIVS_MC_BUS_CONFIG_FE_BUS_CONFIG(1) |
			      VIVS_MC_BUS_CONFIG_TX_BUS_CONFIG(0);
		gpu_ग_लिखो(gpu, VIVS_MC_BUS_CONFIG, bus_config);
	पूर्ण

	अगर (gpu->sec_mode == ETNA_SEC_KERNEL) अणु
		u32 val = gpu_पढ़ो(gpu, VIVS_MMUv2_AHB_CONTROL);
		val |= VIVS_MMUv2_AHB_CONTROL_NONSEC_ACCESS;
		gpu_ग_लिखो(gpu, VIVS_MMUv2_AHB_CONTROL, val);
	पूर्ण

	/* setup the pulse eater */
	etnaviv_gpu_setup_pulse_eater(gpu);

	gpu_ग_लिखो(gpu, VIVS_HI_INTR_ENBL, ~0U);
पूर्ण

पूर्णांक etnaviv_gpu_init(काष्ठा etnaviv_gpu *gpu)
अणु
	काष्ठा etnaviv_drm_निजी *priv = gpu->drm->dev_निजी;
	पूर्णांक ret, i;

	ret = pm_runसमय_get_sync(gpu->dev);
	अगर (ret < 0) अणु
		dev_err(gpu->dev, "Failed to enable GPU power domain\n");
		जाओ pm_put;
	पूर्ण

	etnaviv_hw_identअगरy(gpu);

	अगर (gpu->identity.model == 0) अणु
		dev_err(gpu->dev, "Unknown GPU model\n");
		ret = -ENXIO;
		जाओ fail;
	पूर्ण

	/* Exclude VG cores with FE2.0 */
	अगर (gpu->identity.features & chipFeatures_PIPE_VG &&
	    gpu->identity.features & chipFeatures_FE20) अणु
		dev_info(gpu->dev, "Ignoring GPU with VG and FE2.0\n");
		ret = -ENXIO;
		जाओ fail;
	पूर्ण

	/*
	 * On cores with security features supported, we claim control over the
	 * security states.
	 */
	अगर ((gpu->identity.minor_features7 & chipMinorFeatures7_BIT_SECURITY) &&
	    (gpu->identity.minor_features10 & chipMinorFeatures10_SECURITY_AHB))
		gpu->sec_mode = ETNA_SEC_KERNEL;

	ret = etnaviv_hw_reset(gpu);
	अगर (ret) अणु
		dev_err(gpu->dev, "GPU reset failed\n");
		जाओ fail;
	पूर्ण

	ret = etnaviv_iommu_global_init(gpu);
	अगर (ret)
		जाओ fail;

	/*
	 * Set the GPU linear winकरोw to be at the end of the DMA winकरोw, where
	 * the CMA area is likely to reside. This ensures that we are able to
	 * map the command buffers जबतक having the linear winकरोw overlap as
	 * much RAM as possible, so we can optimize mappings क्रम other buffers.
	 *
	 * For 3D cores only करो this अगर MC2.0 is present, as with MC1.0 it leads
	 * to dअगरferent views of the memory on the inभागidual engines.
	 */
	अगर (!(gpu->identity.features & chipFeatures_PIPE_3D) ||
	    (gpu->identity.minor_features0 & chipMinorFeatures0_MC20)) अणु
		u32 dma_mask = (u32)dma_get_required_mask(gpu->dev);
		अगर (dma_mask < PHYS_OFFSET + SZ_2G)
			priv->mmu_global->memory_base = PHYS_OFFSET;
		अन्यथा
			priv->mmu_global->memory_base = dma_mask - SZ_2G + 1;
	पूर्ण अन्यथा अगर (PHYS_OFFSET >= SZ_2G) अणु
		dev_info(gpu->dev, "Need to move linear window on MC1.0, disabling TS\n");
		priv->mmu_global->memory_base = PHYS_OFFSET;
		gpu->identity.features &= ~chipFeatures_FAST_CLEAR;
	पूर्ण

	/*
	 * If the GPU is part of a प्रणाली with DMA addressing limitations,
	 * request pages क्रम our SHM backend buffers from the DMA32 zone to
	 * hopefully aव्योम perक्रमmance समाप्तing SWIOTLB bounce buffering.
	 */
	अगर (dma_addressing_limited(gpu->dev))
		priv->shm_gfp_mask |= GFP_DMA32;

	/* Create buffer: */
	ret = etnaviv_cmdbuf_init(priv->cmdbuf_suballoc, &gpu->buffer,
				  PAGE_SIZE);
	अगर (ret) अणु
		dev_err(gpu->dev, "could not create command buffer\n");
		जाओ fail;
	पूर्ण

	/* Setup event management */
	spin_lock_init(&gpu->event_spinlock);
	init_completion(&gpu->event_मुक्त);
	biपंचांगap_zero(gpu->event_biपंचांगap, ETNA_NR_EVENTS);
	क्रम (i = 0; i < ARRAY_SIZE(gpu->event); i++)
		complete(&gpu->event_मुक्त);

	/* Now program the hardware */
	mutex_lock(&gpu->lock);
	etnaviv_gpu_hw_init(gpu);
	gpu->exec_state = -1;
	mutex_unlock(&gpu->lock);

	pm_runसमय_mark_last_busy(gpu->dev);
	pm_runसमय_put_स्वतःsuspend(gpu->dev);

	gpu->initialized = true;

	वापस 0;

fail:
	pm_runसमय_mark_last_busy(gpu->dev);
pm_put:
	pm_runसमय_put_स्वतःsuspend(gpu->dev);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
काष्ठा dma_debug अणु
	u32 address[2];
	u32 state[2];
पूर्ण;

अटल व्योम verअगरy_dma(काष्ठा etnaviv_gpu *gpu, काष्ठा dma_debug *debug)
अणु
	u32 i;

	debug->address[0] = gpu_पढ़ो(gpu, VIVS_FE_DMA_ADDRESS);
	debug->state[0]   = gpu_पढ़ो(gpu, VIVS_FE_DMA_DEBUG_STATE);

	क्रम (i = 0; i < 500; i++) अणु
		debug->address[1] = gpu_पढ़ो(gpu, VIVS_FE_DMA_ADDRESS);
		debug->state[1]   = gpu_पढ़ो(gpu, VIVS_FE_DMA_DEBUG_STATE);

		अगर (debug->address[0] != debug->address[1])
			अवरोध;

		अगर (debug->state[0] != debug->state[1])
			अवरोध;
	पूर्ण
पूर्ण

पूर्णांक etnaviv_gpu_debugfs(काष्ठा etnaviv_gpu *gpu, काष्ठा seq_file *m)
अणु
	काष्ठा dma_debug debug;
	u32 dma_lo, dma_hi, axi, idle;
	पूर्णांक ret;

	seq_म_लिखो(m, "%s Status:\n", dev_name(gpu->dev));

	ret = pm_runसमय_get_sync(gpu->dev);
	अगर (ret < 0)
		जाओ pm_put;

	dma_lo = gpu_पढ़ो(gpu, VIVS_FE_DMA_LOW);
	dma_hi = gpu_पढ़ो(gpu, VIVS_FE_DMA_HIGH);
	axi = gpu_पढ़ो(gpu, VIVS_HI_AXI_STATUS);
	idle = gpu_पढ़ो(gpu, VIVS_HI_IDLE_STATE);

	verअगरy_dma(gpu, &debug);

	seq_माला_दो(m, "\tidentity\n");
	seq_म_लिखो(m, "\t model: 0x%x\n", gpu->identity.model);
	seq_म_लिखो(m, "\t revision: 0x%x\n", gpu->identity.revision);
	seq_म_लिखो(m, "\t product_id: 0x%x\n", gpu->identity.product_id);
	seq_म_लिखो(m, "\t customer_id: 0x%x\n", gpu->identity.customer_id);
	seq_म_लिखो(m, "\t eco_id: 0x%x\n", gpu->identity.eco_id);

	seq_माला_दो(m, "\tfeatures\n");
	seq_म_लिखो(m, "\t major_features: 0x%08x\n",
		   gpu->identity.features);
	seq_म_लिखो(m, "\t minor_features0: 0x%08x\n",
		   gpu->identity.minor_features0);
	seq_म_लिखो(m, "\t minor_features1: 0x%08x\n",
		   gpu->identity.minor_features1);
	seq_म_लिखो(m, "\t minor_features2: 0x%08x\n",
		   gpu->identity.minor_features2);
	seq_म_लिखो(m, "\t minor_features3: 0x%08x\n",
		   gpu->identity.minor_features3);
	seq_म_लिखो(m, "\t minor_features4: 0x%08x\n",
		   gpu->identity.minor_features4);
	seq_म_लिखो(m, "\t minor_features5: 0x%08x\n",
		   gpu->identity.minor_features5);
	seq_म_लिखो(m, "\t minor_features6: 0x%08x\n",
		   gpu->identity.minor_features6);
	seq_म_लिखो(m, "\t minor_features7: 0x%08x\n",
		   gpu->identity.minor_features7);
	seq_म_लिखो(m, "\t minor_features8: 0x%08x\n",
		   gpu->identity.minor_features8);
	seq_म_लिखो(m, "\t minor_features9: 0x%08x\n",
		   gpu->identity.minor_features9);
	seq_म_लिखो(m, "\t minor_features10: 0x%08x\n",
		   gpu->identity.minor_features10);
	seq_म_लिखो(m, "\t minor_features11: 0x%08x\n",
		   gpu->identity.minor_features11);

	seq_माला_दो(m, "\tspecs\n");
	seq_म_लिखो(m, "\t stream_count:  %d\n",
			gpu->identity.stream_count);
	seq_म_लिखो(m, "\t register_max: %d\n",
			gpu->identity.रेजिस्टर_max);
	seq_म_लिखो(m, "\t thread_count: %d\n",
			gpu->identity.thपढ़ो_count);
	seq_म_लिखो(m, "\t vertex_cache_size: %d\n",
			gpu->identity.vertex_cache_size);
	seq_म_लिखो(m, "\t shader_core_count: %d\n",
			gpu->identity.shader_core_count);
	seq_म_लिखो(m, "\t pixel_pipes: %d\n",
			gpu->identity.pixel_pipes);
	seq_म_लिखो(m, "\t vertex_output_buffer_size: %d\n",
			gpu->identity.vertex_output_buffer_size);
	seq_म_लिखो(m, "\t buffer_size: %d\n",
			gpu->identity.buffer_size);
	seq_म_लिखो(m, "\t instruction_count: %d\n",
			gpu->identity.inकाष्ठाion_count);
	seq_म_लिखो(m, "\t num_constants: %d\n",
			gpu->identity.num_स्थिरants);
	seq_म_लिखो(m, "\t varyings_count: %d\n",
			gpu->identity.varyings_count);

	seq_म_लिखो(m, "\taxi: 0x%08x\n", axi);
	seq_म_लिखो(m, "\tidle: 0x%08x\n", idle);
	idle |= ~gpu->idle_mask & ~VIVS_HI_IDLE_STATE_AXI_LP;
	अगर ((idle & VIVS_HI_IDLE_STATE_FE) == 0)
		seq_माला_दो(m, "\t FE is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_DE) == 0)
		seq_माला_दो(m, "\t DE is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_PE) == 0)
		seq_माला_दो(m, "\t PE is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_SH) == 0)
		seq_माला_दो(m, "\t SH is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_PA) == 0)
		seq_माला_दो(m, "\t PA is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_SE) == 0)
		seq_माला_दो(m, "\t SE is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_RA) == 0)
		seq_माला_दो(m, "\t RA is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_TX) == 0)
		seq_माला_दो(m, "\t TX is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_VG) == 0)
		seq_माला_दो(m, "\t VG is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_IM) == 0)
		seq_माला_दो(m, "\t IM is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_FP) == 0)
		seq_माला_दो(m, "\t FP is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_TS) == 0)
		seq_माला_दो(m, "\t TS is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_BL) == 0)
		seq_माला_दो(m, "\t BL is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_ASYNCFE) == 0)
		seq_माला_दो(m, "\t ASYNCFE is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_MC) == 0)
		seq_माला_दो(m, "\t MC is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_PPA) == 0)
		seq_माला_दो(m, "\t PPA is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_WD) == 0)
		seq_माला_दो(m, "\t WD is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_NN) == 0)
		seq_माला_दो(m, "\t NN is not idle\n");
	अगर ((idle & VIVS_HI_IDLE_STATE_TP) == 0)
		seq_माला_दो(m, "\t TP is not idle\n");
	अगर (idle & VIVS_HI_IDLE_STATE_AXI_LP)
		seq_माला_दो(m, "\t AXI low power mode\n");

	अगर (gpu->identity.features & chipFeatures_DEBUG_MODE) अणु
		u32 पढ़ो0 = gpu_पढ़ो(gpu, VIVS_MC_DEBUG_READ0);
		u32 पढ़ो1 = gpu_पढ़ो(gpu, VIVS_MC_DEBUG_READ1);
		u32 ग_लिखो = gpu_पढ़ो(gpu, VIVS_MC_DEBUG_WRITE);

		seq_माला_दो(m, "\tMC\n");
		seq_म_लिखो(m, "\t read0: 0x%08x\n", पढ़ो0);
		seq_म_लिखो(m, "\t read1: 0x%08x\n", पढ़ो1);
		seq_म_लिखो(m, "\t write: 0x%08x\n", ग_लिखो);
	पूर्ण

	seq_माला_दो(m, "\tDMA ");

	अगर (debug.address[0] == debug.address[1] &&
	    debug.state[0] == debug.state[1]) अणु
		seq_माला_दो(m, "seems to be stuck\n");
	पूर्ण अन्यथा अगर (debug.address[0] == debug.address[1]) अणु
		seq_माला_दो(m, "address is constant\n");
	पूर्ण अन्यथा अणु
		seq_माला_दो(m, "is running\n");
	पूर्ण

	seq_म_लिखो(m, "\t address 0: 0x%08x\n", debug.address[0]);
	seq_म_लिखो(m, "\t address 1: 0x%08x\n", debug.address[1]);
	seq_म_लिखो(m, "\t state 0: 0x%08x\n", debug.state[0]);
	seq_म_लिखो(m, "\t state 1: 0x%08x\n", debug.state[1]);
	seq_म_लिखो(m, "\t last fetch 64 bit word: 0x%08x 0x%08x\n",
		   dma_lo, dma_hi);

	ret = 0;

	pm_runसमय_mark_last_busy(gpu->dev);
pm_put:
	pm_runसमय_put_स्वतःsuspend(gpu->dev);

	वापस ret;
पूर्ण
#पूर्ण_अगर

व्योम etnaviv_gpu_recover_hang(काष्ठा etnaviv_gpu *gpu)
अणु
	अचिन्हित पूर्णांक i = 0;

	dev_err(gpu->dev, "recover hung GPU!\n");

	अगर (pm_runसमय_get_sync(gpu->dev) < 0)
		जाओ pm_put;

	mutex_lock(&gpu->lock);

	etnaviv_hw_reset(gpu);

	/* complete all events, the GPU won't करो it after the reset */
	spin_lock(&gpu->event_spinlock);
	क्रम_each_set_bit_from(i, gpu->event_biपंचांगap, ETNA_NR_EVENTS)
		complete(&gpu->event_मुक्त);
	biपंचांगap_zero(gpu->event_biपंचांगap, ETNA_NR_EVENTS);
	spin_unlock(&gpu->event_spinlock);

	etnaviv_gpu_hw_init(gpu);
	gpu->exec_state = -1;
	gpu->mmu_context = शून्य;

	mutex_unlock(&gpu->lock);
	pm_runसमय_mark_last_busy(gpu->dev);
pm_put:
	pm_runसमय_put_स्वतःsuspend(gpu->dev);
पूर्ण

/* fence object management */
काष्ठा etnaviv_fence अणु
	काष्ठा etnaviv_gpu *gpu;
	काष्ठा dma_fence base;
पूर्ण;

अटल अंतरभूत काष्ठा etnaviv_fence *to_etnaviv_fence(काष्ठा dma_fence *fence)
अणु
	वापस container_of(fence, काष्ठा etnaviv_fence, base);
पूर्ण

अटल स्थिर अक्षर *etnaviv_fence_get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस "etnaviv";
पूर्ण

अटल स्थिर अक्षर *etnaviv_fence_get_समयline_name(काष्ठा dma_fence *fence)
अणु
	काष्ठा etnaviv_fence *f = to_etnaviv_fence(fence);

	वापस dev_name(f->gpu->dev);
पूर्ण

अटल bool etnaviv_fence_संकेतed(काष्ठा dma_fence *fence)
अणु
	काष्ठा etnaviv_fence *f = to_etnaviv_fence(fence);

	वापस (s32)(f->gpu->completed_fence - f->base.seqno) >= 0;
पूर्ण

अटल व्योम etnaviv_fence_release(काष्ठा dma_fence *fence)
अणु
	काष्ठा etnaviv_fence *f = to_etnaviv_fence(fence);

	kमुक्त_rcu(f, base.rcu);
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops etnaviv_fence_ops = अणु
	.get_driver_name = etnaviv_fence_get_driver_name,
	.get_समयline_name = etnaviv_fence_get_समयline_name,
	.संकेतed = etnaviv_fence_संकेतed,
	.release = etnaviv_fence_release,
पूर्ण;

अटल काष्ठा dma_fence *etnaviv_gpu_fence_alloc(काष्ठा etnaviv_gpu *gpu)
अणु
	काष्ठा etnaviv_fence *f;

	/*
	 * GPU lock must alपढ़ोy be held, otherwise fence completion order might
	 * not match the seqno order asचिन्हित here.
	 */
	lockdep_निश्चित_held(&gpu->lock);

	f = kzalloc(माप(*f), GFP_KERNEL);
	अगर (!f)
		वापस शून्य;

	f->gpu = gpu;

	dma_fence_init(&f->base, &etnaviv_fence_ops, &gpu->fence_spinlock,
		       gpu->fence_context, ++gpu->next_fence);

	वापस &f->base;
पूर्ण

/* वापसs true अगर fence a comes after fence b */
अटल अंतरभूत bool fence_after(u32 a, u32 b)
अणु
	वापस (s32)(a - b) > 0;
पूर्ण

/*
 * event management:
 */

अटल पूर्णांक event_alloc(काष्ठा etnaviv_gpu *gpu, अचिन्हित nr_events,
	अचिन्हित पूर्णांक *events)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(10 * 10000);
	अचिन्हित i, acquired = 0;

	क्रम (i = 0; i < nr_events; i++) अणु
		अचिन्हित दीर्घ ret;

		ret = रुको_क्रम_completion_समयout(&gpu->event_मुक्त, समयout);

		अगर (!ret) अणु
			dev_err(gpu->dev, "wait_for_completion_timeout failed");
			जाओ out;
		पूर्ण

		acquired++;
		समयout = ret;
	पूर्ण

	spin_lock(&gpu->event_spinlock);

	क्रम (i = 0; i < nr_events; i++) अणु
		पूर्णांक event = find_first_zero_bit(gpu->event_biपंचांगap, ETNA_NR_EVENTS);

		events[i] = event;
		स_रखो(&gpu->event[event], 0, माप(काष्ठा etnaviv_event));
		set_bit(event, gpu->event_biपंचांगap);
	पूर्ण

	spin_unlock(&gpu->event_spinlock);

	वापस 0;

out:
	क्रम (i = 0; i < acquired; i++)
		complete(&gpu->event_मुक्त);

	वापस -EBUSY;
पूर्ण

अटल व्योम event_मुक्त(काष्ठा etnaviv_gpu *gpu, अचिन्हित पूर्णांक event)
अणु
	अगर (!test_bit(event, gpu->event_biपंचांगap)) अणु
		dev_warn(gpu->dev, "event %u is already marked as free",
			 event);
	पूर्ण अन्यथा अणु
		clear_bit(event, gpu->event_biपंचांगap);
		complete(&gpu->event_मुक्त);
	पूर्ण
पूर्ण

/*
 * Cmdstream submission/retirement:
 */
पूर्णांक etnaviv_gpu_रुको_fence_पूर्णांकerruptible(काष्ठा etnaviv_gpu *gpu,
	u32 id, काष्ठा drm_etnaviv_बारpec *समयout)
अणु
	काष्ठा dma_fence *fence;
	पूर्णांक ret;

	/*
	 * Look up the fence and take a reference. We might still find a fence
	 * whose refcount has alपढ़ोy dropped to zero. dma_fence_get_rcu
	 * pretends we didn't find a fence in that हाल.
	 */
	rcu_पढ़ो_lock();
	fence = idr_find(&gpu->fence_idr, id);
	अगर (fence)
		fence = dma_fence_get_rcu(fence);
	rcu_पढ़ो_unlock();

	अगर (!fence)
		वापस 0;

	अगर (!समयout) अणु
		/* No समयout was requested: just test क्रम completion */
		ret = dma_fence_is_संकेतed(fence) ? 0 : -EBUSY;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ reमुख्यing = etnaviv_समयout_to_jअगरfies(समयout);

		ret = dma_fence_रुको_समयout(fence, true, reमुख्यing);
		अगर (ret == 0)
			ret = -ETIMEDOUT;
		अन्यथा अगर (ret != -ERESTARTSYS)
			ret = 0;

	पूर्ण

	dma_fence_put(fence);
	वापस ret;
पूर्ण

/*
 * Wait क्रम an object to become inactive.  This, on it's own, is not race
 * मुक्त: the object is moved by the scheduler off the active list, and
 * then the iova is put.  Moreover, the object could be re-submitted just
 * after we notice that it's become inactive.
 *
 * Although the retirement happens under the gpu lock, we करोn't want to hold
 * that lock in this function जबतक रुकोing.
 */
पूर्णांक etnaviv_gpu_रुको_obj_inactive(काष्ठा etnaviv_gpu *gpu,
	काष्ठा etnaviv_gem_object *etnaviv_obj,
	काष्ठा drm_etnaviv_बारpec *समयout)
अणु
	अचिन्हित दीर्घ reमुख्यing;
	दीर्घ ret;

	अगर (!समयout)
		वापस !is_active(etnaviv_obj) ? 0 : -EBUSY;

	reमुख्यing = etnaviv_समयout_to_jअगरfies(समयout);

	ret = रुको_event_पूर्णांकerruptible_समयout(gpu->fence_event,
					       !is_active(etnaviv_obj),
					       reमुख्यing);
	अगर (ret > 0)
		वापस 0;
	अन्यथा अगर (ret == -ERESTARTSYS)
		वापस -ERESTARTSYS;
	अन्यथा
		वापस -ETIMEDOUT;
पूर्ण

अटल व्योम sync_poपूर्णांक_perfmon_sample(काष्ठा etnaviv_gpu *gpu,
	काष्ठा etnaviv_event *event, अचिन्हित पूर्णांक flags)
अणु
	स्थिर काष्ठा etnaviv_gem_submit *submit = event->submit;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < submit->nr_pmrs; i++) अणु
		स्थिर काष्ठा etnaviv_perfmon_request *pmr = submit->pmrs + i;

		अगर (pmr->flags == flags)
			etnaviv_perfmon_process(gpu, pmr, submit->exec_state);
	पूर्ण
पूर्ण

अटल व्योम sync_poपूर्णांक_perfmon_sample_pre(काष्ठा etnaviv_gpu *gpu,
	काष्ठा etnaviv_event *event)
अणु
	u32 val;

	/* disable घड़ी gating */
	val = gpu_पढ़ो(gpu, VIVS_PM_POWER_CONTROLS);
	val &= ~VIVS_PM_POWER_CONTROLS_ENABLE_MODULE_CLOCK_GATING;
	gpu_ग_लिखो(gpu, VIVS_PM_POWER_CONTROLS, val);

	/* enable debug रेजिस्टर */
	val = gpu_पढ़ो(gpu, VIVS_HI_CLOCK_CONTROL);
	val &= ~VIVS_HI_CLOCK_CONTROL_DISABLE_DEBUG_REGISTERS;
	gpu_ग_लिखो(gpu, VIVS_HI_CLOCK_CONTROL, val);

	sync_poपूर्णांक_perfmon_sample(gpu, event, ETNA_PM_PROCESS_PRE);
पूर्ण

अटल व्योम sync_poपूर्णांक_perfmon_sample_post(काष्ठा etnaviv_gpu *gpu,
	काष्ठा etnaviv_event *event)
अणु
	स्थिर काष्ठा etnaviv_gem_submit *submit = event->submit;
	अचिन्हित पूर्णांक i;
	u32 val;

	sync_poपूर्णांक_perfmon_sample(gpu, event, ETNA_PM_PROCESS_POST);

	क्रम (i = 0; i < submit->nr_pmrs; i++) अणु
		स्थिर काष्ठा etnaviv_perfmon_request *pmr = submit->pmrs + i;

		*pmr->bo_vma = pmr->sequence;
	पूर्ण

	/* disable debug रेजिस्टर */
	val = gpu_पढ़ो(gpu, VIVS_HI_CLOCK_CONTROL);
	val |= VIVS_HI_CLOCK_CONTROL_DISABLE_DEBUG_REGISTERS;
	gpu_ग_लिखो(gpu, VIVS_HI_CLOCK_CONTROL, val);

	/* enable घड़ी gating */
	val = gpu_पढ़ो(gpu, VIVS_PM_POWER_CONTROLS);
	val |= VIVS_PM_POWER_CONTROLS_ENABLE_MODULE_CLOCK_GATING;
	gpu_ग_लिखो(gpu, VIVS_PM_POWER_CONTROLS, val);
पूर्ण


/* add bo's to gpu's ring, and kick gpu: */
काष्ठा dma_fence *etnaviv_gpu_submit(काष्ठा etnaviv_gem_submit *submit)
अणु
	काष्ठा etnaviv_gpu *gpu = submit->gpu;
	काष्ठा dma_fence *gpu_fence;
	अचिन्हित पूर्णांक i, nr_events = 1, event[3];
	पूर्णांक ret;

	अगर (!submit->runसमय_resumed) अणु
		ret = pm_runसमय_get_sync(gpu->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(gpu->dev);
			वापस शून्य;
		पूर्ण
		submit->runसमय_resumed = true;
	पूर्ण

	/*
	 * अगर there are perक्रमmance monitor requests we need to have
	 * - a sync poपूर्णांक to re-configure gpu and process ETNA_PM_PROCESS_PRE
	 *   requests.
	 * - a sync poपूर्णांक to re-configure gpu, process ETNA_PM_PROCESS_POST requests
	 *   and update the sequence number क्रम userspace.
	 */
	अगर (submit->nr_pmrs)
		nr_events = 3;

	ret = event_alloc(gpu, nr_events, event);
	अगर (ret) अणु
		DRM_ERROR("no free events\n");
		pm_runसमय_put_noidle(gpu->dev);
		वापस शून्य;
	पूर्ण

	mutex_lock(&gpu->lock);

	gpu_fence = etnaviv_gpu_fence_alloc(gpu);
	अगर (!gpu_fence) अणु
		क्रम (i = 0; i < nr_events; i++)
			event_मुक्त(gpu, event[i]);

		जाओ out_unlock;
	पूर्ण

	अगर (!gpu->mmu_context) अणु
		etnaviv_iommu_context_get(submit->mmu_context);
		gpu->mmu_context = submit->mmu_context;
		etnaviv_gpu_start_fe_idleloop(gpu);
	पूर्ण अन्यथा अणु
		etnaviv_iommu_context_get(gpu->mmu_context);
		submit->prev_mmu_context = gpu->mmu_context;
	पूर्ण

	अगर (submit->nr_pmrs) अणु
		gpu->event[event[1]].sync_poपूर्णांक = &sync_poपूर्णांक_perfmon_sample_pre;
		kref_get(&submit->refcount);
		gpu->event[event[1]].submit = submit;
		etnaviv_sync_poपूर्णांक_queue(gpu, event[1]);
	पूर्ण

	gpu->event[event[0]].fence = gpu_fence;
	submit->cmdbuf.user_size = submit->cmdbuf.size - 8;
	etnaviv_buffer_queue(gpu, submit->exec_state, submit->mmu_context,
			     event[0], &submit->cmdbuf);

	अगर (submit->nr_pmrs) अणु
		gpu->event[event[2]].sync_poपूर्णांक = &sync_poपूर्णांक_perfmon_sample_post;
		kref_get(&submit->refcount);
		gpu->event[event[2]].submit = submit;
		etnaviv_sync_poपूर्णांक_queue(gpu, event[2]);
	पूर्ण

out_unlock:
	mutex_unlock(&gpu->lock);

	वापस gpu_fence;
पूर्ण

अटल व्योम sync_poपूर्णांक_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा etnaviv_gpu *gpu = container_of(work, काष्ठा etnaviv_gpu,
					       sync_poपूर्णांक_work);
	काष्ठा etnaviv_event *event = &gpu->event[gpu->sync_poपूर्णांक_event];
	u32 addr = gpu_पढ़ो(gpu, VIVS_FE_DMA_ADDRESS);

	event->sync_poपूर्णांक(gpu, event);
	etnaviv_submit_put(event->submit);
	event_मुक्त(gpu, gpu->sync_poपूर्णांक_event);

	/* restart FE last to aव्योम GPU and IRQ racing against this worker */
	etnaviv_gpu_start_fe(gpu, addr + 2, 2);
पूर्ण

अटल व्योम dump_mmu_fault(काष्ठा etnaviv_gpu *gpu)
अणु
	u32 status_reg, status;
	पूर्णांक i;

	अगर (gpu->sec_mode == ETNA_SEC_NONE)
		status_reg = VIVS_MMUv2_STATUS;
	अन्यथा
		status_reg = VIVS_MMUv2_SEC_STATUS;

	status = gpu_पढ़ो(gpu, status_reg);
	dev_err_ratelimited(gpu->dev, "MMU fault status 0x%08x\n", status);

	क्रम (i = 0; i < 4; i++) अणु
		u32 address_reg;

		अगर (!(status & (VIVS_MMUv2_STATUS_EXCEPTION0__MASK << (i * 4))))
			जारी;

		अगर (gpu->sec_mode == ETNA_SEC_NONE)
			address_reg = VIVS_MMUv2_EXCEPTION_ADDR(i);
		अन्यथा
			address_reg = VIVS_MMUv2_SEC_EXCEPTION_ADDR;

		dev_err_ratelimited(gpu->dev, "MMU %d fault addr 0x%08x\n", i,
				    gpu_पढ़ो(gpu, address_reg));
	पूर्ण
पूर्ण

अटल irqवापस_t irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा etnaviv_gpu *gpu = data;
	irqवापस_t ret = IRQ_NONE;

	u32 पूर्णांकr = gpu_पढ़ो(gpu, VIVS_HI_INTR_ACKNOWLEDGE);

	अगर (पूर्णांकr != 0) अणु
		पूर्णांक event;

		pm_runसमय_mark_last_busy(gpu->dev);

		dev_dbg(gpu->dev, "intr 0x%08x\n", पूर्णांकr);

		अगर (पूर्णांकr & VIVS_HI_INTR_ACKNOWLEDGE_AXI_BUS_ERROR) अणु
			dev_err(gpu->dev, "AXI bus error\n");
			पूर्णांकr &= ~VIVS_HI_INTR_ACKNOWLEDGE_AXI_BUS_ERROR;
		पूर्ण

		अगर (पूर्णांकr & VIVS_HI_INTR_ACKNOWLEDGE_MMU_EXCEPTION) अणु
			dump_mmu_fault(gpu);
			पूर्णांकr &= ~VIVS_HI_INTR_ACKNOWLEDGE_MMU_EXCEPTION;
		पूर्ण

		जबतक ((event = ffs(पूर्णांकr)) != 0) अणु
			काष्ठा dma_fence *fence;

			event -= 1;

			पूर्णांकr &= ~(1 << event);

			dev_dbg(gpu->dev, "event %u\n", event);

			अगर (gpu->event[event].sync_poपूर्णांक) अणु
				gpu->sync_poपूर्णांक_event = event;
				queue_work(gpu->wq, &gpu->sync_poपूर्णांक_work);
			पूर्ण

			fence = gpu->event[event].fence;
			अगर (!fence)
				जारी;

			gpu->event[event].fence = शून्य;

			/*
			 * Events can be processed out of order.  Eg,
			 * - allocate and queue event 0
			 * - allocate event 1
			 * - event 0 completes, we process it
			 * - allocate and queue event 0
			 * - event 1 and event 0 complete
			 * we can end up processing event 0 first, then 1.
			 */
			अगर (fence_after(fence->seqno, gpu->completed_fence))
				gpu->completed_fence = fence->seqno;
			dma_fence_संकेत(fence);

			event_मुक्त(gpu, event);
		पूर्ण

		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक etnaviv_gpu_clk_enable(काष्ठा etnaviv_gpu *gpu)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(gpu->clk_reg);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(gpu->clk_bus);
	अगर (ret)
		जाओ disable_clk_reg;

	ret = clk_prepare_enable(gpu->clk_core);
	अगर (ret)
		जाओ disable_clk_bus;

	ret = clk_prepare_enable(gpu->clk_shader);
	अगर (ret)
		जाओ disable_clk_core;

	वापस 0;

disable_clk_core:
	clk_disable_unprepare(gpu->clk_core);
disable_clk_bus:
	clk_disable_unprepare(gpu->clk_bus);
disable_clk_reg:
	clk_disable_unprepare(gpu->clk_reg);

	वापस ret;
पूर्ण

अटल पूर्णांक etnaviv_gpu_clk_disable(काष्ठा etnaviv_gpu *gpu)
अणु
	clk_disable_unprepare(gpu->clk_shader);
	clk_disable_unprepare(gpu->clk_core);
	clk_disable_unprepare(gpu->clk_bus);
	clk_disable_unprepare(gpu->clk_reg);

	वापस 0;
पूर्ण

पूर्णांक etnaviv_gpu_रुको_idle(काष्ठा etnaviv_gpu *gpu, अचिन्हित पूर्णांक समयout_ms)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(समयout_ms);

	करो अणु
		u32 idle = gpu_पढ़ो(gpu, VIVS_HI_IDLE_STATE);

		अगर ((idle & gpu->idle_mask) == gpu->idle_mask)
			वापस 0;

		अगर (समय_is_beक्रमe_jअगरfies(समयout)) अणु
			dev_warn(gpu->dev,
				 "timed out waiting for idle: idle=0x%x\n",
				 idle);
			वापस -ETIMEDOUT;
		पूर्ण

		udelay(5);
	पूर्ण जबतक (1);
पूर्ण

अटल पूर्णांक etnaviv_gpu_hw_suspend(काष्ठा etnaviv_gpu *gpu)
अणु
	अगर (gpu->initialized && gpu->mmu_context) अणु
		/* Replace the last WAIT with END */
		mutex_lock(&gpu->lock);
		etnaviv_buffer_end(gpu);
		mutex_unlock(&gpu->lock);

		/*
		 * We know that only the FE is busy here, this should
		 * happen quickly (as the WAIT is only 200 cycles).  If
		 * we fail, just warn and जारी.
		 */
		etnaviv_gpu_रुको_idle(gpu, 100);

		etnaviv_iommu_context_put(gpu->mmu_context);
		gpu->mmu_context = शून्य;
	पूर्ण

	gpu->exec_state = -1;

	वापस etnaviv_gpu_clk_disable(gpu);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक etnaviv_gpu_hw_resume(काष्ठा etnaviv_gpu *gpu)
अणु
	पूर्णांक ret;

	ret = mutex_lock_समाप्तable(&gpu->lock);
	अगर (ret)
		वापस ret;

	etnaviv_gpu_update_घड़ी(gpu);
	etnaviv_gpu_hw_init(gpu);

	mutex_unlock(&gpu->lock);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
etnaviv_gpu_cooling_get_max_state(काष्ठा thermal_cooling_device *cdev,
				  अचिन्हित दीर्घ *state)
अणु
	*state = 6;

	वापस 0;
पूर्ण

अटल पूर्णांक
etnaviv_gpu_cooling_get_cur_state(काष्ठा thermal_cooling_device *cdev,
				  अचिन्हित दीर्घ *state)
अणु
	काष्ठा etnaviv_gpu *gpu = cdev->devdata;

	*state = gpu->freq_scale;

	वापस 0;
पूर्ण

अटल पूर्णांक
etnaviv_gpu_cooling_set_cur_state(काष्ठा thermal_cooling_device *cdev,
				  अचिन्हित दीर्घ state)
अणु
	काष्ठा etnaviv_gpu *gpu = cdev->devdata;

	mutex_lock(&gpu->lock);
	gpu->freq_scale = state;
	अगर (!pm_runसमय_suspended(gpu->dev))
		etnaviv_gpu_update_घड़ी(gpu);
	mutex_unlock(&gpu->lock);

	वापस 0;
पूर्ण

अटल काष्ठा thermal_cooling_device_ops cooling_ops = अणु
	.get_max_state = etnaviv_gpu_cooling_get_max_state,
	.get_cur_state = etnaviv_gpu_cooling_get_cur_state,
	.set_cur_state = etnaviv_gpu_cooling_set_cur_state,
पूर्ण;

अटल पूर्णांक etnaviv_gpu_bind(काष्ठा device *dev, काष्ठा device *master,
	व्योम *data)
अणु
	काष्ठा drm_device *drm = data;
	काष्ठा etnaviv_drm_निजी *priv = drm->dev_निजी;
	काष्ठा etnaviv_gpu *gpu = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (IS_ENABLED(CONFIG_DRM_ETNAVIV_THERMAL)) अणु
		gpu->cooling = thermal_of_cooling_device_रेजिस्टर(dev->of_node,
				(अक्षर *)dev_name(dev), gpu, &cooling_ops);
		अगर (IS_ERR(gpu->cooling))
			वापस PTR_ERR(gpu->cooling);
	पूर्ण

	gpu->wq = alloc_ordered_workqueue(dev_name(dev), 0);
	अगर (!gpu->wq) अणु
		ret = -ENOMEM;
		जाओ out_thermal;
	पूर्ण

	ret = etnaviv_sched_init(gpu);
	अगर (ret)
		जाओ out_workqueue;

#अगर_घोषित CONFIG_PM
	ret = pm_runसमय_get_sync(gpu->dev);
#अन्यथा
	ret = etnaviv_gpu_clk_enable(gpu);
#पूर्ण_अगर
	अगर (ret < 0)
		जाओ out_sched;


	gpu->drm = drm;
	gpu->fence_context = dma_fence_context_alloc(1);
	idr_init(&gpu->fence_idr);
	spin_lock_init(&gpu->fence_spinlock);

	INIT_WORK(&gpu->sync_poपूर्णांक_work, sync_poपूर्णांक_worker);
	init_रुकोqueue_head(&gpu->fence_event);

	priv->gpu[priv->num_gpus++] = gpu;

	pm_runसमय_mark_last_busy(gpu->dev);
	pm_runसमय_put_स्वतःsuspend(gpu->dev);

	वापस 0;

out_sched:
	etnaviv_sched_fini(gpu);

out_workqueue:
	destroy_workqueue(gpu->wq);

out_thermal:
	अगर (IS_ENABLED(CONFIG_DRM_ETNAVIV_THERMAL))
		thermal_cooling_device_unरेजिस्टर(gpu->cooling);

	वापस ret;
पूर्ण

अटल व्योम etnaviv_gpu_unbind(काष्ठा device *dev, काष्ठा device *master,
	व्योम *data)
अणु
	काष्ठा etnaviv_gpu *gpu = dev_get_drvdata(dev);

	DBG("%s", dev_name(gpu->dev));

	flush_workqueue(gpu->wq);
	destroy_workqueue(gpu->wq);

	etnaviv_sched_fini(gpu);

#अगर_घोषित CONFIG_PM
	pm_runसमय_get_sync(gpu->dev);
	pm_runसमय_put_sync_suspend(gpu->dev);
#अन्यथा
	etnaviv_gpu_hw_suspend(gpu);
#पूर्ण_अगर

	अगर (gpu->initialized) अणु
		etnaviv_cmdbuf_मुक्त(&gpu->buffer);
		etnaviv_iommu_global_fini(gpu);
		gpu->initialized = false;
	पूर्ण

	gpu->drm = शून्य;
	idr_destroy(&gpu->fence_idr);

	अगर (IS_ENABLED(CONFIG_DRM_ETNAVIV_THERMAL))
		thermal_cooling_device_unरेजिस्टर(gpu->cooling);
	gpu->cooling = शून्य;
पूर्ण

अटल स्थिर काष्ठा component_ops gpu_ops = अणु
	.bind = etnaviv_gpu_bind,
	.unbind = etnaviv_gpu_unbind,
पूर्ण;

अटल स्थिर काष्ठा of_device_id etnaviv_gpu_match[] = अणु
	अणु
		.compatible = "vivante,gc"
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, etnaviv_gpu_match);

अटल पूर्णांक etnaviv_gpu_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा etnaviv_gpu *gpu;
	पूर्णांक err;

	gpu = devm_kzalloc(dev, माप(*gpu), GFP_KERNEL);
	अगर (!gpu)
		वापस -ENOMEM;

	gpu->dev = &pdev->dev;
	mutex_init(&gpu->lock);
	mutex_init(&gpu->fence_lock);

	/* Map रेजिस्टरs: */
	gpu->mmio = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(gpu->mmio))
		वापस PTR_ERR(gpu->mmio);

	/* Get Interrupt: */
	gpu->irq = platक्रमm_get_irq(pdev, 0);
	अगर (gpu->irq < 0) अणु
		dev_err(dev, "failed to get irq: %d\n", gpu->irq);
		वापस gpu->irq;
	पूर्ण

	err = devm_request_irq(&pdev->dev, gpu->irq, irq_handler, 0,
			       dev_name(gpu->dev), gpu);
	अगर (err) अणु
		dev_err(dev, "failed to request IRQ%u: %d\n", gpu->irq, err);
		वापस err;
	पूर्ण

	/* Get Clocks: */
	gpu->clk_reg = devm_clk_get_optional(&pdev->dev, "reg");
	DBG("clk_reg: %p", gpu->clk_reg);
	अगर (IS_ERR(gpu->clk_reg))
		वापस PTR_ERR(gpu->clk_reg);

	gpu->clk_bus = devm_clk_get_optional(&pdev->dev, "bus");
	DBG("clk_bus: %p", gpu->clk_bus);
	अगर (IS_ERR(gpu->clk_bus))
		वापस PTR_ERR(gpu->clk_bus);

	gpu->clk_core = devm_clk_get(&pdev->dev, "core");
	DBG("clk_core: %p", gpu->clk_core);
	अगर (IS_ERR(gpu->clk_core))
		वापस PTR_ERR(gpu->clk_core);
	gpu->base_rate_core = clk_get_rate(gpu->clk_core);

	gpu->clk_shader = devm_clk_get_optional(&pdev->dev, "shader");
	DBG("clk_shader: %p", gpu->clk_shader);
	अगर (IS_ERR(gpu->clk_shader))
		वापस PTR_ERR(gpu->clk_shader);
	gpu->base_rate_shader = clk_get_rate(gpu->clk_shader);

	/* TODO: figure out max mapped size */
	dev_set_drvdata(dev, gpu);

	/*
	 * We treat the device as initially suspended.  The runसमय PM
	 * स्वतःsuspend delay is rather arbitary: no measurements have
	 * yet been perक्रमmed to determine an appropriate value.
	 */
	pm_runसमय_use_स्वतःsuspend(gpu->dev);
	pm_runसमय_set_स्वतःsuspend_delay(gpu->dev, 200);
	pm_runसमय_enable(gpu->dev);

	err = component_add(&pdev->dev, &gpu_ops);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to register component: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक etnaviv_gpu_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &gpu_ops);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक etnaviv_gpu_rpm_suspend(काष्ठा device *dev)
अणु
	काष्ठा etnaviv_gpu *gpu = dev_get_drvdata(dev);
	u32 idle, mask;

	/* If there are any jobs in the HW queue, we're not idle */
	अगर (atomic_पढ़ो(&gpu->sched.hw_rq_count))
		वापस -EBUSY;

	/* Check whether the hardware (except FE and MC) is idle */
	mask = gpu->idle_mask & ~(VIVS_HI_IDLE_STATE_FE |
				  VIVS_HI_IDLE_STATE_MC);
	idle = gpu_पढ़ो(gpu, VIVS_HI_IDLE_STATE) & mask;
	अगर (idle != mask) अणु
		dev_warn_ratelimited(dev, "GPU not yet idle, mask: 0x%08x\n",
				     idle);
		वापस -EBUSY;
	पूर्ण

	वापस etnaviv_gpu_hw_suspend(gpu);
पूर्ण

अटल पूर्णांक etnaviv_gpu_rpm_resume(काष्ठा device *dev)
अणु
	काष्ठा etnaviv_gpu *gpu = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = etnaviv_gpu_clk_enable(gpu);
	अगर (ret)
		वापस ret;

	/* Re-initialise the basic hardware state */
	अगर (gpu->drm && gpu->initialized) अणु
		ret = etnaviv_gpu_hw_resume(gpu);
		अगर (ret) अणु
			etnaviv_gpu_clk_disable(gpu);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops etnaviv_gpu_pm_ops = अणु
	SET_RUNTIME_PM_OPS(etnaviv_gpu_rpm_suspend, etnaviv_gpu_rpm_resume,
			   शून्य)
पूर्ण;

काष्ठा platक्रमm_driver etnaviv_gpu_driver = अणु
	.driver = अणु
		.name = "etnaviv-gpu",
		.owner = THIS_MODULE,
		.pm = &etnaviv_gpu_pm_ops,
		.of_match_table = etnaviv_gpu_match,
	पूर्ण,
	.probe = etnaviv_gpu_platक्रमm_probe,
	.हटाओ = etnaviv_gpu_platक्रमm_हटाओ,
	.id_table = gpu_ids,
पूर्ण;
