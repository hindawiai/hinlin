<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 * Author: Shujuan Chen <shujuan.chen@stericsson.com> क्रम ST-Ericsson.
 * Author: Jonas Linde <jonas.linde@stericsson.com> क्रम ST-Ericsson.
 * Author: Niklas Hernaeus <niklas.hernaeus@stericsson.com> क्रम ST-Ericsson.
 * Author: Joakim Bech <joakim.xx.bech@stericsson.com> क्रम ST-Ericsson.
 * Author: Berne Hebark <berne.herbark@stericsson.com> क्रम ST-Ericsson.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#समावेश "cryp_p.h"
#समावेश "cryp.h"

/*
 * cryp_रुको_until_करोne - रुको until the device logic is not busy
 */
व्योम cryp_रुको_until_करोne(काष्ठा cryp_device_data *device_data)
अणु
	जबतक (cryp_is_logic_busy(device_data))
		cpu_relax();
पूर्ण

/**
 * cryp_check - This routine checks Peripheral and PCell Id
 * @device_data: Poपूर्णांकer to the device data काष्ठा क्रम base address.
 */
पूर्णांक cryp_check(काष्ठा cryp_device_data *device_data)
अणु
	पूर्णांक peripheralid2 = 0;

	अगर (शून्य == device_data)
		वापस -EINVAL;

	peripheralid2 = पढ़ोl_relaxed(&device_data->base->periphId2);

	अगर (peripheralid2 != CRYP_PERIPHERAL_ID2_DB8500)
		वापस -EPERM;

	/* Check Peripheral and Pcell Id Register क्रम CRYP */
	अगर ((CRYP_PERIPHERAL_ID0 ==
		पढ़ोl_relaxed(&device_data->base->periphId0))
	    && (CRYP_PERIPHERAL_ID1 ==
		    पढ़ोl_relaxed(&device_data->base->periphId1))
	    && (CRYP_PERIPHERAL_ID3 ==
		    पढ़ोl_relaxed(&device_data->base->periphId3))
	    && (CRYP_PCELL_ID0 ==
		    पढ़ोl_relaxed(&device_data->base->pcellId0))
	    && (CRYP_PCELL_ID1 ==
		    पढ़ोl_relaxed(&device_data->base->pcellId1))
	    && (CRYP_PCELL_ID2 ==
		    पढ़ोl_relaxed(&device_data->base->pcellId2))
	    && (CRYP_PCELL_ID3 ==
		    पढ़ोl_relaxed(&device_data->base->pcellId3))) अणु
		वापस 0;
	पूर्ण

	वापस -EPERM;
पूर्ण

/**
 * cryp_activity - This routine enables/disable the cryptography function.
 * @device_data: Poपूर्णांकer to the device data काष्ठा क्रम base address.
 * @cryp_crypen: Enable/Disable functionality
 */
व्योम cryp_activity(काष्ठा cryp_device_data *device_data,
		   क्रमागत cryp_crypen cryp_crypen)
अणु
	CRYP_PUT_BITS(&device_data->base->cr,
		      cryp_crypen,
		      CRYP_CR_CRYPEN_POS,
		      CRYP_CR_CRYPEN_MASK);
पूर्ण

/**
 * cryp_flush_inoutfअगरo - Resets both the input and the output FIFOs
 * @device_data: Poपूर्णांकer to the device data काष्ठा क्रम base address.
 */
व्योम cryp_flush_inoutfअगरo(काष्ठा cryp_device_data *device_data)
अणु
	/*
	 * We always need to disable the hardware beक्रमe trying to flush the
	 * FIFO. This is something that isn't written in the design
	 * specअगरication, but we have been inक्रमmed by the hardware designers
	 * that this must be करोne.
	 */
	cryp_activity(device_data, CRYP_CRYPEN_DISABLE);
	cryp_रुको_until_करोne(device_data);

	CRYP_SET_BITS(&device_data->base->cr, CRYP_CR_FFLUSH_MASK);
	/*
	 * CRYP_SR_INFIFO_READY_MASK is the expected value on the status
	 * रेजिस्टर when starting a new calculation, which means Input FIFO is
	 * not full and input FIFO is empty.
	 */
	जबतक (पढ़ोl_relaxed(&device_data->base->sr) !=
	       CRYP_SR_INFIFO_READY_MASK)
		cpu_relax();
पूर्ण

/**
 * cryp_set_configuration - This routine set the cr CRYP IP
 * @device_data: Poपूर्णांकer to the device data काष्ठा क्रम base address.
 * @cryp_config: Poपूर्णांकer to the configuration parameter
 * @control_रेजिस्टर: The control रेजिस्टर to be written later on.
 */
पूर्णांक cryp_set_configuration(काष्ठा cryp_device_data *device_data,
			   काष्ठा cryp_config *cryp_config,
			   u32 *control_रेजिस्टर)
अणु
	u32 cr_क्रम_kse;

	अगर (शून्य == device_data || शून्य == cryp_config)
		वापस -EINVAL;

	*control_रेजिस्टर |= (cryp_config->keysize << CRYP_CR_KEYSIZE_POS);

	/* Prepare key क्रम decryption in AES_ECB and AES_CBC mode. */
	अगर ((CRYP_ALGORITHM_DECRYPT == cryp_config->algodir) &&
	    ((CRYP_ALGO_AES_ECB == cryp_config->algomode) ||
	     (CRYP_ALGO_AES_CBC == cryp_config->algomode))) अणु
		cr_क्रम_kse = *control_रेजिस्टर;
		/*
		 * This seems a bit odd, but it is indeed needed to set this to
		 * encrypt even though it is a decryption that we are करोing. It
		 * also mentioned in the design spec that you need to करो this.
		 * After the keyprepartion क्रम decrypting is करोne you should set
		 * algodir back to decryption, which is करोne outside this अगर
		 * statement.
		 *
		 * According to design specअगरication we should set mode ECB
		 * during key preparation even though we might be running CBC
		 * when enter this function.
		 *
		 * Writing to KSE_ENABLED will drop CRYPEN when key preparation
		 * is करोne. Thereक्रमe we need to set CRYPEN again outside this
		 * अगर statement when running decryption.
		 */
		cr_क्रम_kse |= ((CRYP_ALGORITHM_ENCRYPT << CRYP_CR_ALGOसूची_POS) |
			       (CRYP_ALGO_AES_ECB << CRYP_CR_ALGOMODE_POS) |
			       (CRYP_CRYPEN_ENABLE << CRYP_CR_CRYPEN_POS) |
			       (KSE_ENABLED << CRYP_CR_KSE_POS));

		ग_लिखोl_relaxed(cr_क्रम_kse, &device_data->base->cr);
		cryp_रुको_until_करोne(device_data);
	पूर्ण

	*control_रेजिस्टर |=
		((cryp_config->algomode << CRYP_CR_ALGOMODE_POS) |
		 (cryp_config->algodir << CRYP_CR_ALGOसूची_POS));

	वापस 0;
पूर्ण

/**
 * cryp_configure_protection - set the protection bits in the CRYP logic.
 * @device_data: Poपूर्णांकer to the device data काष्ठा क्रम base address.
 * @p_protect_config:	Poपूर्णांकer to the protection mode and
 *			secure mode configuration
 */
पूर्णांक cryp_configure_protection(काष्ठा cryp_device_data *device_data,
			      काष्ठा cryp_protection_config *p_protect_config)
अणु
	अगर (शून्य == p_protect_config)
		वापस -EINVAL;

	CRYP_WRITE_BIT(&device_data->base->cr,
		       (u32) p_protect_config->secure_access,
		       CRYP_CR_SECURE_MASK);
	CRYP_PUT_BITS(&device_data->base->cr,
		      p_protect_config->privilege_access,
		      CRYP_CR_PRLG_POS,
		      CRYP_CR_PRLG_MASK);

	वापस 0;
पूर्ण

/**
 * cryp_is_logic_busy - वापसs the busy status of the CRYP logic
 * @device_data: Poपूर्णांकer to the device data काष्ठा क्रम base address.
 */
पूर्णांक cryp_is_logic_busy(काष्ठा cryp_device_data *device_data)
अणु
	वापस CRYP_TEST_BITS(&device_data->base->sr,
			      CRYP_SR_BUSY_MASK);
पूर्ण

/**
 * cryp_configure_क्रम_dma - configures the CRYP IP क्रम DMA operation
 * @device_data: Poपूर्णांकer to the device data काष्ठा क्रम base address.
 * @dma_req: Specअगरies the DMA request type value.
 */
व्योम cryp_configure_क्रम_dma(काष्ठा cryp_device_data *device_data,
			    क्रमागत cryp_dma_req_type dma_req)
अणु
	CRYP_SET_BITS(&device_data->base->dmacr,
		      (u32) dma_req);
पूर्ण

/**
 * cryp_configure_key_values - configures the key values क्रम CRYP operations
 * @device_data: Poपूर्णांकer to the device data काष्ठा क्रम base address.
 * @key_reg_index: Key value index रेजिस्टर
 * @key_value: The key value काष्ठा
 */
पूर्णांक cryp_configure_key_values(काष्ठा cryp_device_data *device_data,
			      क्रमागत cryp_key_reg_index key_reg_index,
			      काष्ठा cryp_key_value key_value)
अणु
	जबतक (cryp_is_logic_busy(device_data))
		cpu_relax();

	चयन (key_reg_index) अणु
	हाल CRYP_KEY_REG_1:
		ग_लिखोl_relaxed(key_value.key_value_left,
				&device_data->base->key_1_l);
		ग_लिखोl_relaxed(key_value.key_value_right,
				&device_data->base->key_1_r);
		अवरोध;
	हाल CRYP_KEY_REG_2:
		ग_लिखोl_relaxed(key_value.key_value_left,
				&device_data->base->key_2_l);
		ग_लिखोl_relaxed(key_value.key_value_right,
				&device_data->base->key_2_r);
		अवरोध;
	हाल CRYP_KEY_REG_3:
		ग_लिखोl_relaxed(key_value.key_value_left,
				&device_data->base->key_3_l);
		ग_लिखोl_relaxed(key_value.key_value_right,
				&device_data->base->key_3_r);
		अवरोध;
	हाल CRYP_KEY_REG_4:
		ग_लिखोl_relaxed(key_value.key_value_left,
				&device_data->base->key_4_l);
		ग_लिखोl_relaxed(key_value.key_value_right,
				&device_data->base->key_4_r);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cryp_configure_init_vector - configures the initialization vector रेजिस्टर
 * @device_data: Poपूर्णांकer to the device data काष्ठा क्रम base address.
 * @init_vector_index: Specअगरies the index of the init vector.
 * @init_vector_value: Specअगरies the value क्रम the init vector.
 */
पूर्णांक cryp_configure_init_vector(काष्ठा cryp_device_data *device_data,
			       क्रमागत cryp_init_vector_index
			       init_vector_index,
			       काष्ठा cryp_init_vector_value
			       init_vector_value)
अणु
	जबतक (cryp_is_logic_busy(device_data))
		cpu_relax();

	चयन (init_vector_index) अणु
	हाल CRYP_INIT_VECTOR_INDEX_0:
		ग_लिखोl_relaxed(init_vector_value.init_value_left,
		       &device_data->base->init_vect_0_l);
		ग_लिखोl_relaxed(init_vector_value.init_value_right,
		       &device_data->base->init_vect_0_r);
		अवरोध;
	हाल CRYP_INIT_VECTOR_INDEX_1:
		ग_लिखोl_relaxed(init_vector_value.init_value_left,
		       &device_data->base->init_vect_1_l);
		ग_लिखोl_relaxed(init_vector_value.init_value_right,
		       &device_data->base->init_vect_1_r);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cryp_save_device_context -	Store hardware रेजिस्टरs and
 *				other device context parameter
 * @device_data: Poपूर्णांकer to the device data काष्ठा क्रम base address.
 * @ctx: Crypto device context
 * @cryp_mode: Mode: Polling, Interrupt or DMA
 */
व्योम cryp_save_device_context(काष्ठा cryp_device_data *device_data,
			      काष्ठा cryp_device_context *ctx,
			      पूर्णांक cryp_mode)
अणु
	क्रमागत cryp_algo_mode algomode;
	काष्ठा cryp_रेजिस्टर __iomem *src_reg = device_data->base;
	काष्ठा cryp_config *config =
		(काष्ठा cryp_config *)device_data->current_ctx;

	/*
	 * Always start by disable the hardware and रुको क्रम it to finish the
	 * ongoing calculations beक्रमe trying to reprogram it.
	 */
	cryp_activity(device_data, CRYP_CRYPEN_DISABLE);
	cryp_रुको_until_करोne(device_data);

	अगर (cryp_mode == CRYP_MODE_DMA)
		cryp_configure_क्रम_dma(device_data, CRYP_DMA_DISABLE_BOTH);

	अगर (CRYP_TEST_BITS(&src_reg->sr, CRYP_SR_IFEM_MASK) == 0)
		ctx->din = पढ़ोl_relaxed(&src_reg->din);

	ctx->cr = पढ़ोl_relaxed(&src_reg->cr) & CRYP_CR_CONTEXT_SAVE_MASK;

	चयन (config->keysize) अणु
	हाल CRYP_KEY_SIZE_256:
		ctx->key_4_l = पढ़ोl_relaxed(&src_reg->key_4_l);
		ctx->key_4_r = पढ़ोl_relaxed(&src_reg->key_4_r);
		fallthrough;

	हाल CRYP_KEY_SIZE_192:
		ctx->key_3_l = पढ़ोl_relaxed(&src_reg->key_3_l);
		ctx->key_3_r = पढ़ोl_relaxed(&src_reg->key_3_r);
		fallthrough;

	हाल CRYP_KEY_SIZE_128:
		ctx->key_2_l = पढ़ोl_relaxed(&src_reg->key_2_l);
		ctx->key_2_r = पढ़ोl_relaxed(&src_reg->key_2_r);
		fallthrough;

	शेष:
		ctx->key_1_l = पढ़ोl_relaxed(&src_reg->key_1_l);
		ctx->key_1_r = पढ़ोl_relaxed(&src_reg->key_1_r);
	पूर्ण

	/* Save IV क्रम CBC mode क्रम both AES and DES. */
	algomode = ((ctx->cr & CRYP_CR_ALGOMODE_MASK) >> CRYP_CR_ALGOMODE_POS);
	अगर (algomode == CRYP_ALGO_TDES_CBC ||
	    algomode == CRYP_ALGO_DES_CBC ||
	    algomode == CRYP_ALGO_AES_CBC) अणु
		ctx->init_vect_0_l = पढ़ोl_relaxed(&src_reg->init_vect_0_l);
		ctx->init_vect_0_r = पढ़ोl_relaxed(&src_reg->init_vect_0_r);
		ctx->init_vect_1_l = पढ़ोl_relaxed(&src_reg->init_vect_1_l);
		ctx->init_vect_1_r = पढ़ोl_relaxed(&src_reg->init_vect_1_r);
	पूर्ण
पूर्ण

/**
 * cryp_restore_device_context -	Restore hardware रेजिस्टरs and
 *					other device context parameter
 * @device_data: Poपूर्णांकer to the device data काष्ठा क्रम base address.
 * @ctx: Crypto device context
 */
व्योम cryp_restore_device_context(काष्ठा cryp_device_data *device_data,
				 काष्ठा cryp_device_context *ctx)
अणु
	काष्ठा cryp_रेजिस्टर __iomem *reg = device_data->base;
	काष्ठा cryp_config *config =
		(काष्ठा cryp_config *)device_data->current_ctx;

	/*
	 * Fall through क्रम all items in चयन statement. DES is captured in
	 * the शेष.
	 */
	चयन (config->keysize) अणु
	हाल CRYP_KEY_SIZE_256:
		ग_लिखोl_relaxed(ctx->key_4_l, &reg->key_4_l);
		ग_लिखोl_relaxed(ctx->key_4_r, &reg->key_4_r);
		fallthrough;

	हाल CRYP_KEY_SIZE_192:
		ग_लिखोl_relaxed(ctx->key_3_l, &reg->key_3_l);
		ग_लिखोl_relaxed(ctx->key_3_r, &reg->key_3_r);
		fallthrough;

	हाल CRYP_KEY_SIZE_128:
		ग_लिखोl_relaxed(ctx->key_2_l, &reg->key_2_l);
		ग_लिखोl_relaxed(ctx->key_2_r, &reg->key_2_r);
		fallthrough;

	शेष:
		ग_लिखोl_relaxed(ctx->key_1_l, &reg->key_1_l);
		ग_लिखोl_relaxed(ctx->key_1_r, &reg->key_1_r);
	पूर्ण

	/* Restore IV क्रम CBC mode क्रम AES and DES. */
	अगर (config->algomode == CRYP_ALGO_TDES_CBC ||
	    config->algomode == CRYP_ALGO_DES_CBC ||
	    config->algomode == CRYP_ALGO_AES_CBC) अणु
		ग_लिखोl_relaxed(ctx->init_vect_0_l, &reg->init_vect_0_l);
		ग_लिखोl_relaxed(ctx->init_vect_0_r, &reg->init_vect_0_r);
		ग_लिखोl_relaxed(ctx->init_vect_1_l, &reg->init_vect_1_l);
		ग_लिखोl_relaxed(ctx->init_vect_1_r, &reg->init_vect_1_r);
	पूर्ण
पूर्ण
