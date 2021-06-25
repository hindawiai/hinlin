<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017-2019, The Linux Foundation. All rights reserved.
 *
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/qcom/llcc-qcom.h>

#घोषणा ACTIVATE                      BIT(0)
#घोषणा DEACTIVATE                    BIT(1)
#घोषणा ACT_CTRL_OPCODE_ACTIVATE      BIT(0)
#घोषणा ACT_CTRL_OPCODE_DEACTIVATE    BIT(1)
#घोषणा ACT_CTRL_ACT_TRIG             BIT(0)
#घोषणा ACT_CTRL_OPCODE_SHIFT         0x01
#घोषणा ATTR1_PROBE_TARGET_WAYS_SHIFT 0x02
#घोषणा ATTR1_FIXED_SIZE_SHIFT        0x03
#घोषणा ATTR1_PRIORITY_SHIFT          0x04
#घोषणा ATTR1_MAX_CAP_SHIFT           0x10
#घोषणा ATTR0_RES_WAYS_MASK           GENMASK(11, 0)
#घोषणा ATTR0_BONUS_WAYS_MASK         GENMASK(27, 16)
#घोषणा ATTR0_BONUS_WAYS_SHIFT        0x10
#घोषणा LLCC_STATUS_READ_DELAY        100

#घोषणा CACHE_LINE_SIZE_SHIFT         6

#घोषणा LLCC_COMMON_HW_INFO           0x00030000
#घोषणा LLCC_MAJOR_VERSION_MASK       GENMASK(31, 24)

#घोषणा LLCC_COMMON_STATUS0           0x0003000c
#घोषणा LLCC_LB_CNT_MASK              GENMASK(31, 28)
#घोषणा LLCC_LB_CNT_SHIFT             28

#घोषणा MAX_CAP_TO_BYTES(n)           (n * SZ_1K)
#घोषणा LLCC_TRP_ACT_CTRLn(n)         (n * SZ_4K)
#घोषणा LLCC_TRP_STATUSn(n)           (4 + n * SZ_4K)
#घोषणा LLCC_TRP_ATTR0_CFGn(n)        (0x21000 + SZ_8 * n)
#घोषणा LLCC_TRP_ATTR1_CFGn(n)        (0x21004 + SZ_8 * n)

#घोषणा LLCC_TRP_SCID_DIS_CAP_ALLOC   0x21f00
#घोषणा LLCC_TRP_PCB_ACT              0x21f04
#घोषणा LLCC_TRP_WRSC_EN              0x21f20

#घोषणा BANK_OFFSET_STRIDE	      0x80000

/**
 * काष्ठा llcc_slice_config - Data associated with the llcc slice
 * @useहाल_id: Unique id क्रम the client's use हाल
 * @slice_id: llcc slice id क्रम each client
 * @max_cap: The maximum capacity of the cache slice provided in KB
 * @priority: Priority of the client used to select victim line क्रम replacement
 * @fixed_size: Boolean indicating अगर the slice has a fixed capacity
 * @bonus_ways: Bonus ways are additional ways to be used क्रम any slice,
 *		अगर client ends up using more than reserved cache ways. Bonus
 *		ways are allocated only अगर they are not reserved क्रम some
 *		other client.
 * @res_ways: Reserved ways क्रम the cache slice, the reserved ways cannot
 *		be used by any other client than the one its asचिन्हित to.
 * @cache_mode: Each slice operates as a cache, this controls the mode of the
 *             slice: normal or TCM(Tightly Coupled Memory)
 * @probe_target_ways: Determines what ways to probe क्रम access hit. When
 *                    configured to 1 only bonus and reserved ways are probed.
 *                    When configured to 0 all ways in llcc are probed.
 * @dis_cap_alloc: Disable capacity based allocation क्रम a client
 * @retain_on_pc: If this bit is set and client has मुख्यtained active vote
 *               then the ways asचिन्हित to this client are not flushed on घातer
 *               collapse.
 * @activate_on_init: Activate the slice immediately after it is programmed
 * @ग_लिखो_scid_en: Bit enables ग_लिखो cache support क्रम a given scid.
 */
काष्ठा llcc_slice_config अणु
	u32 useहाल_id;
	u32 slice_id;
	u32 max_cap;
	u32 priority;
	bool fixed_size;
	u32 bonus_ways;
	u32 res_ways;
	u32 cache_mode;
	u32 probe_target_ways;
	bool dis_cap_alloc;
	bool retain_on_pc;
	bool activate_on_init;
	bool ग_लिखो_scid_en;
पूर्ण;

काष्ठा qcom_llcc_config अणु
	स्थिर काष्ठा llcc_slice_config *sct_data;
	पूर्णांक size;
	bool need_llcc_cfg;
पूर्ण;

अटल स्थिर काष्ठा llcc_slice_config sc7180_data[] =  अणु
	अणु LLCC_CPUSS,    1,  256, 1, 0, 0xf, 0x0, 0, 0, 0, 1, 1 पूर्ण,
	अणु LLCC_MDM,      8,  128, 1, 0, 0xf, 0x0, 0, 0, 0, 1, 0 पूर्ण,
	अणु LLCC_GPUHTW,   11, 128, 1, 0, 0xf, 0x0, 0, 0, 0, 1, 0 पूर्ण,
	अणु LLCC_GPU,      12, 128, 1, 0, 0xf, 0x0, 0, 0, 0, 1, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा llcc_slice_config sc7280_data[] =  अणु
	अणु LLCC_CPUSS,    1,  768, 1, 0, 0x3f, 0x0, 0, 0, 0, 1, 1, 0पूर्ण,
	अणु LLCC_MDMHPGRW, 7,  512, 2, 1, 0x3f, 0x0, 0, 0, 0, 1, 0, 0पूर्ण,
	अणु LLCC_CMPT,     10, 768, 1, 1, 0x3f, 0x0, 0, 0, 0, 1, 0, 0पूर्ण,
	अणु LLCC_GPUHTW,   11, 256, 1, 1, 0x3f, 0x0, 0, 0, 0, 1, 0, 0पूर्ण,
	अणु LLCC_GPU,      12, 512, 1, 0, 0x3f, 0x0, 0, 0, 0, 1, 0, 0पूर्ण,
	अणु LLCC_MMUHWT,   13, 256, 1, 1, 0x3f, 0x0, 0, 0, 0, 1, 1, 0पूर्ण,
	अणु LLCC_MDMPNG,   21, 768, 0, 1, 0x3f, 0x0, 0, 0, 0, 1, 0, 0पूर्ण,
	अणु LLCC_WLHW,     24, 256, 1, 1, 0x3f, 0x0, 0, 0, 0, 1, 0, 0पूर्ण,
	अणु LLCC_MODPE,    29, 64,  1, 1, 0x3f, 0x0, 0, 0, 0, 1, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा llcc_slice_config sdm845_data[] =  अणु
	अणु LLCC_CPUSS,    1,  2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 1 पूर्ण,
	अणु LLCC_VIDSC0,   2,  512,  2, 1, 0x0,   0x0f0, 0, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_VIDSC1,   3,  512,  2, 1, 0x0,   0x0f0, 0, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_ROTATOR,  4,  563,  2, 1, 0x0,   0x00e, 2, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_VOICE,    5,  2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_AUDIO,    6,  2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_MDMHPGRW, 7,  1024, 2, 0, 0xfc,  0xf00, 0, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_MDM,      8,  2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_CMPT,     10, 2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_GPUHTW,   11, 512,  1, 1, 0xc,   0x0,   0, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_GPU,      12, 2304, 1, 0, 0xff0, 0x2,   0, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_MMUHWT,   13, 256,  2, 0, 0x0,   0x1,   0, 0, 1, 0, 1 पूर्ण,
	अणु LLCC_CMPTDMA,  15, 2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_DISP,     16, 2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_VIDFW,    17, 2816, 1, 0, 0xffc, 0x2,   0, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_MDMHPFX,  20, 1024, 2, 1, 0x0,   0xf00, 0, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_MDMPNG,   21, 1024, 0, 1, 0x1e,  0x0,   0, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_AUDHW,    22, 1024, 1, 1, 0xffc, 0x2,   0, 0, 1, 1, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा llcc_slice_config sm8150_data[] =  अणु
	अणु  LLCC_CPUSS,    1, 3072, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 1 पूर्ण,
	अणु  LLCC_VIDSC0,   2, 512,  2, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_VIDSC1,   3, 512,  2, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_AUDIO,    6, 1024, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_MDMHPGRW, 7, 3072, 1, 0, 0xFF,  0xF00, 0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_MDM,      8, 3072, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_MODHW,    9, 1024, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_CMPT,    10, 3072, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_GPUHTW , 11, 512,  1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_GPU,     12, 2560, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_MMUHWT,  13, 1024, 1, 1, 0xFFF, 0x0,   0, 0, 0, 0, 1 पूर्ण,
	अणु  LLCC_CMPTDMA, 15, 3072, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_DISP,    16, 3072, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_MDMHPFX, 20, 1024, 2, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_MDMHPFX, 21, 1024, 0, 1, 0xF,   0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_AUDHW,   22, 1024, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_NPU,     23, 3072, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_WLHW,    24, 3072, 1, 1, 0xFFF, 0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_MODPE,   29, 256,  1, 1, 0xF,   0x0,   0, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_APTCM,   30, 256,  3, 1, 0x0,   0x1,   1, 0, 0, 1, 0 पूर्ण,
	अणु  LLCC_WRCACHE, 31, 128,  1, 1, 0xFFF, 0x0,   0, 0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा llcc_slice_config sm8250_data[] =  अणु
	अणु LLCC_CPUSS,    1, 3072, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 1, 0 पूर्ण,
	अणु LLCC_VIDSC0,   2, 512,  3, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 पूर्ण,
	अणु LLCC_AUDIO,    6, 1024, 1, 0, 0xfff, 0x0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु LLCC_CMPT,    10, 1024, 1, 0, 0xfff, 0x0, 0, 0, 0, 0, 0, 0 पूर्ण,
	अणु LLCC_GPUHTW,  11, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 पूर्ण,
	अणु LLCC_GPU,     12, 1024, 1, 0, 0xfff, 0x0, 0, 0, 0, 1, 0, 1 पूर्ण,
	अणु LLCC_MMUHWT,  13, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 पूर्ण,
	अणु LLCC_CMPTDMA, 15, 1024, 1, 0, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 पूर्ण,
	अणु LLCC_DISP,    16, 3072, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 पूर्ण,
	अणु LLCC_VIDFW,   17, 512,  1, 0, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 पूर्ण,
	अणु LLCC_AUDHW,   22, 1024, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 पूर्ण,
	अणु LLCC_NPU,     23, 3072, 1, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 पूर्ण,
	अणु LLCC_WLHW,    24, 1024, 1, 0, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 पूर्ण,
	अणु LLCC_CVP,     28, 256,  3, 1, 0xfff, 0x0, 0, 0, 0, 1, 0, 0 पूर्ण,
	अणु LLCC_APTCM,   30, 128,  3, 0, 0x0,   0x3, 1, 0, 0, 1, 0, 0 पूर्ण,
	अणु LLCC_WRCACHE, 31, 256,  1, 1, 0xfff, 0x0, 0, 0, 0, 0, 1, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा qcom_llcc_config sc7180_cfg = अणु
	.sct_data	= sc7180_data,
	.size		= ARRAY_SIZE(sc7180_data),
	.need_llcc_cfg	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_llcc_config sc7280_cfg = अणु
	.sct_data	= sc7280_data,
	.size		= ARRAY_SIZE(sc7280_data),
	.need_llcc_cfg	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_llcc_config sdm845_cfg = अणु
	.sct_data	= sdm845_data,
	.size		= ARRAY_SIZE(sdm845_data),
	.need_llcc_cfg	= false,
पूर्ण;

अटल स्थिर काष्ठा qcom_llcc_config sm8150_cfg = अणु
	.sct_data       = sm8150_data,
	.size           = ARRAY_SIZE(sm8150_data),
पूर्ण;

अटल स्थिर काष्ठा qcom_llcc_config sm8250_cfg = अणु
	.sct_data       = sm8250_data,
	.size           = ARRAY_SIZE(sm8250_data),
पूर्ण;

अटल काष्ठा llcc_drv_data *drv_data = (व्योम *) -EPROBE_DEFER;

/**
 * llcc_slice_getd - get llcc slice descriptor
 * @uid: useहाल_id क्रम the client
 *
 * A poपूर्णांकer to llcc slice descriptor will be वापसed on success and
 * and error poपूर्णांकer is वापसed on failure
 */
काष्ठा llcc_slice_desc *llcc_slice_getd(u32 uid)
अणु
	स्थिर काष्ठा llcc_slice_config *cfg;
	काष्ठा llcc_slice_desc *desc;
	u32 sz, count;

	अगर (IS_ERR(drv_data))
		वापस ERR_CAST(drv_data);

	cfg = drv_data->cfg;
	sz = drv_data->cfg_size;

	क्रम (count = 0; cfg && count < sz; count++, cfg++)
		अगर (cfg->useहाल_id == uid)
			अवरोध;

	अगर (count == sz || !cfg)
		वापस ERR_PTR(-ENODEV);

	desc = kzalloc(माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस ERR_PTR(-ENOMEM);

	desc->slice_id = cfg->slice_id;
	desc->slice_size = cfg->max_cap;

	वापस desc;
पूर्ण
EXPORT_SYMBOL_GPL(llcc_slice_getd);

/**
 * llcc_slice_putd - llcc slice descritpor
 * @desc: Poपूर्णांकer to llcc slice descriptor
 */
व्योम llcc_slice_putd(काष्ठा llcc_slice_desc *desc)
अणु
	अगर (!IS_ERR_OR_शून्य(desc))
		kमुक्त(desc);
पूर्ण
EXPORT_SYMBOL_GPL(llcc_slice_putd);

अटल पूर्णांक llcc_update_act_ctrl(u32 sid,
				u32 act_ctrl_reg_val, u32 status)
अणु
	u32 act_ctrl_reg;
	u32 status_reg;
	u32 slice_status;
	पूर्णांक ret;

	अगर (IS_ERR(drv_data))
		वापस PTR_ERR(drv_data);

	act_ctrl_reg = LLCC_TRP_ACT_CTRLn(sid);
	status_reg = LLCC_TRP_STATUSn(sid);

	/* Set the ACTIVE trigger */
	act_ctrl_reg_val |= ACT_CTRL_ACT_TRIG;
	ret = regmap_ग_लिखो(drv_data->bcast_regmap, act_ctrl_reg,
				act_ctrl_reg_val);
	अगर (ret)
		वापस ret;

	/* Clear the ACTIVE trigger */
	act_ctrl_reg_val &= ~ACT_CTRL_ACT_TRIG;
	ret = regmap_ग_लिखो(drv_data->bcast_regmap, act_ctrl_reg,
				act_ctrl_reg_val);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो_poll_समयout(drv_data->bcast_regmap, status_reg,
				      slice_status, !(slice_status & status),
				      0, LLCC_STATUS_READ_DELAY);
	वापस ret;
पूर्ण

/**
 * llcc_slice_activate - Activate the llcc slice
 * @desc: Poपूर्णांकer to llcc slice descriptor
 *
 * A value of zero will be वापसed on success and a negative त्रुटि_सं will
 * be वापसed in error हालs
 */
पूर्णांक llcc_slice_activate(काष्ठा llcc_slice_desc *desc)
अणु
	पूर्णांक ret;
	u32 act_ctrl_val;

	अगर (IS_ERR(drv_data))
		वापस PTR_ERR(drv_data);

	अगर (IS_ERR_OR_शून्य(desc))
		वापस -EINVAL;

	mutex_lock(&drv_data->lock);
	अगर (test_bit(desc->slice_id, drv_data->biपंचांगap)) अणु
		mutex_unlock(&drv_data->lock);
		वापस 0;
	पूर्ण

	act_ctrl_val = ACT_CTRL_OPCODE_ACTIVATE << ACT_CTRL_OPCODE_SHIFT;

	ret = llcc_update_act_ctrl(desc->slice_id, act_ctrl_val,
				  DEACTIVATE);
	अगर (ret) अणु
		mutex_unlock(&drv_data->lock);
		वापस ret;
	पूर्ण

	__set_bit(desc->slice_id, drv_data->biपंचांगap);
	mutex_unlock(&drv_data->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(llcc_slice_activate);

/**
 * llcc_slice_deactivate - Deactivate the llcc slice
 * @desc: Poपूर्णांकer to llcc slice descriptor
 *
 * A value of zero will be वापसed on success and a negative त्रुटि_सं will
 * be वापसed in error हालs
 */
पूर्णांक llcc_slice_deactivate(काष्ठा llcc_slice_desc *desc)
अणु
	u32 act_ctrl_val;
	पूर्णांक ret;

	अगर (IS_ERR(drv_data))
		वापस PTR_ERR(drv_data);

	अगर (IS_ERR_OR_शून्य(desc))
		वापस -EINVAL;

	mutex_lock(&drv_data->lock);
	अगर (!test_bit(desc->slice_id, drv_data->biपंचांगap)) अणु
		mutex_unlock(&drv_data->lock);
		वापस 0;
	पूर्ण
	act_ctrl_val = ACT_CTRL_OPCODE_DEACTIVATE << ACT_CTRL_OPCODE_SHIFT;

	ret = llcc_update_act_ctrl(desc->slice_id, act_ctrl_val,
				  ACTIVATE);
	अगर (ret) अणु
		mutex_unlock(&drv_data->lock);
		वापस ret;
	पूर्ण

	__clear_bit(desc->slice_id, drv_data->biपंचांगap);
	mutex_unlock(&drv_data->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(llcc_slice_deactivate);

/**
 * llcc_get_slice_id - वापस the slice id
 * @desc: Poपूर्णांकer to llcc slice descriptor
 */
पूर्णांक llcc_get_slice_id(काष्ठा llcc_slice_desc *desc)
अणु
	अगर (IS_ERR_OR_शून्य(desc))
		वापस -EINVAL;

	वापस desc->slice_id;
पूर्ण
EXPORT_SYMBOL_GPL(llcc_get_slice_id);

/**
 * llcc_get_slice_size - वापस the slice id
 * @desc: Poपूर्णांकer to llcc slice descriptor
 */
माप_प्रकार llcc_get_slice_size(काष्ठा llcc_slice_desc *desc)
अणु
	अगर (IS_ERR_OR_शून्य(desc))
		वापस 0;

	वापस desc->slice_size;
पूर्ण
EXPORT_SYMBOL_GPL(llcc_get_slice_size);

अटल पूर्णांक _qcom_llcc_cfg_program(स्थिर काष्ठा llcc_slice_config *config,
				  स्थिर काष्ठा qcom_llcc_config *cfg)
अणु
	पूर्णांक ret;
	u32 attr1_cfg;
	u32 attr0_cfg;
	u32 attr1_val;
	u32 attr0_val;
	u32 max_cap_cacheline;
	काष्ठा llcc_slice_desc desc;

	attr1_val = config->cache_mode;
	attr1_val |= config->probe_target_ways << ATTR1_PROBE_TARGET_WAYS_SHIFT;
	attr1_val |= config->fixed_size << ATTR1_FIXED_SIZE_SHIFT;
	attr1_val |= config->priority << ATTR1_PRIORITY_SHIFT;

	max_cap_cacheline = MAX_CAP_TO_BYTES(config->max_cap);

	/*
	 * LLCC instances can vary क्रम each target.
	 * The SW ग_लिखोs to broadcast रेजिस्टर which माला_लो propagated
	 * to each llcc instance (llcc0,.. llccN).
	 * Since the size of the memory is भागided equally amongst the
	 * llcc instances, we need to configure the max cap accordingly.
	 */
	max_cap_cacheline = max_cap_cacheline / drv_data->num_banks;
	max_cap_cacheline >>= CACHE_LINE_SIZE_SHIFT;
	attr1_val |= max_cap_cacheline << ATTR1_MAX_CAP_SHIFT;

	attr1_cfg = LLCC_TRP_ATTR1_CFGn(config->slice_id);

	ret = regmap_ग_लिखो(drv_data->bcast_regmap, attr1_cfg, attr1_val);
	अगर (ret)
		वापस ret;

	attr0_val = config->res_ways & ATTR0_RES_WAYS_MASK;
	attr0_val |= config->bonus_ways << ATTR0_BONUS_WAYS_SHIFT;

	attr0_cfg = LLCC_TRP_ATTR0_CFGn(config->slice_id);

	ret = regmap_ग_लिखो(drv_data->bcast_regmap, attr0_cfg, attr0_val);
	अगर (ret)
		वापस ret;

	अगर (cfg->need_llcc_cfg) अणु
		u32 disable_cap_alloc, retain_pc;

		disable_cap_alloc = config->dis_cap_alloc << config->slice_id;
		ret = regmap_ग_लिखो(drv_data->bcast_regmap,
				LLCC_TRP_SCID_DIS_CAP_ALLOC, disable_cap_alloc);
		अगर (ret)
			वापस ret;

		retain_pc = config->retain_on_pc << config->slice_id;
		ret = regmap_ग_लिखो(drv_data->bcast_regmap,
				LLCC_TRP_PCB_ACT, retain_pc);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (drv_data->major_version == 2) अणु
		u32 wren;

		wren = config->ग_लिखो_scid_en << config->slice_id;
		ret = regmap_update_bits(drv_data->bcast_regmap, LLCC_TRP_WRSC_EN,
					 BIT(config->slice_id), wren);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (config->activate_on_init) अणु
		desc.slice_id = config->slice_id;
		ret = llcc_slice_activate(&desc);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_llcc_cfg_program(काष्ठा platक्रमm_device *pdev,
				 स्थिर काष्ठा qcom_llcc_config *cfg)
अणु
	पूर्णांक i;
	u32 sz;
	पूर्णांक ret = 0;
	स्थिर काष्ठा llcc_slice_config *llcc_table;

	sz = drv_data->cfg_size;
	llcc_table = drv_data->cfg;

	क्रम (i = 0; i < sz; i++) अणु
		ret = _qcom_llcc_cfg_program(&llcc_table[i], cfg);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_llcc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	/* Set the global poपूर्णांकer to a error code to aव्योम referencing it */
	drv_data = ERR_PTR(-ENODEV);
	वापस 0;
पूर्ण

अटल काष्ठा regmap *qcom_llcc_init_mmio(काष्ठा platक्रमm_device *pdev,
		स्थिर अक्षर *name)
अणु
	व्योम __iomem *base;
	काष्ठा regmap_config llcc_regmap_config = अणु
		.reg_bits = 32,
		.reg_stride = 4,
		.val_bits = 32,
		.fast_io = true,
	पूर्ण;

	base = devm_platक्रमm_ioremap_resource_byname(pdev, name);
	अगर (IS_ERR(base))
		वापस ERR_CAST(base);

	llcc_regmap_config.name = name;
	वापस devm_regmap_init_mmio(&pdev->dev, base, &llcc_regmap_config);
पूर्ण

अटल पूर्णांक qcom_llcc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u32 num_banks;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret, i;
	काष्ठा platक्रमm_device *llcc_edac;
	स्थिर काष्ठा qcom_llcc_config *cfg;
	स्थिर काष्ठा llcc_slice_config *llcc_cfg;
	u32 sz;
	u32 version;

	drv_data = devm_kzalloc(dev, माप(*drv_data), GFP_KERNEL);
	अगर (!drv_data) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	drv_data->regmap = qcom_llcc_init_mmio(pdev, "llcc_base");
	अगर (IS_ERR(drv_data->regmap)) अणु
		ret = PTR_ERR(drv_data->regmap);
		जाओ err;
	पूर्ण

	drv_data->bcast_regmap =
		qcom_llcc_init_mmio(pdev, "llcc_broadcast_base");
	अगर (IS_ERR(drv_data->bcast_regmap)) अणु
		ret = PTR_ERR(drv_data->bcast_regmap);
		जाओ err;
	पूर्ण

	/* Extract major version of the IP */
	ret = regmap_पढ़ो(drv_data->bcast_regmap, LLCC_COMMON_HW_INFO, &version);
	अगर (ret)
		जाओ err;

	drv_data->major_version = FIELD_GET(LLCC_MAJOR_VERSION_MASK, version);

	ret = regmap_पढ़ो(drv_data->regmap, LLCC_COMMON_STATUS0,
						&num_banks);
	अगर (ret)
		जाओ err;

	num_banks &= LLCC_LB_CNT_MASK;
	num_banks >>= LLCC_LB_CNT_SHIFT;
	drv_data->num_banks = num_banks;

	cfg = of_device_get_match_data(&pdev->dev);
	llcc_cfg = cfg->sct_data;
	sz = cfg->size;

	क्रम (i = 0; i < sz; i++)
		अगर (llcc_cfg[i].slice_id > drv_data->max_slices)
			drv_data->max_slices = llcc_cfg[i].slice_id;

	drv_data->offsets = devm_kसुस्मृति(dev, num_banks, माप(u32),
							GFP_KERNEL);
	अगर (!drv_data->offsets) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < num_banks; i++)
		drv_data->offsets[i] = i * BANK_OFFSET_STRIDE;

	drv_data->biपंचांगap = devm_kसुस्मृति(dev,
	BITS_TO_LONGS(drv_data->max_slices), माप(अचिन्हित दीर्घ),
						GFP_KERNEL);
	अगर (!drv_data->biपंचांगap) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	drv_data->cfg = llcc_cfg;
	drv_data->cfg_size = sz;
	mutex_init(&drv_data->lock);
	platक्रमm_set_drvdata(pdev, drv_data);

	ret = qcom_llcc_cfg_program(pdev, cfg);
	अगर (ret)
		जाओ err;

	drv_data->ecc_irq = platक्रमm_get_irq(pdev, 0);
	अगर (drv_data->ecc_irq >= 0) अणु
		llcc_edac = platक्रमm_device_रेजिस्टर_data(&pdev->dev,
						"qcom_llcc_edac", -1, drv_data,
						माप(*drv_data));
		अगर (IS_ERR(llcc_edac))
			dev_err(dev, "Failed to register llcc edac driver\n");
	पूर्ण

	वापस 0;
err:
	drv_data = ERR_PTR(-ENODEV);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_llcc_of_match[] = अणु
	अणु .compatible = "qcom,sc7180-llcc", .data = &sc7180_cfg पूर्ण,
	अणु .compatible = "qcom,sc7280-llcc", .data = &sc7280_cfg पूर्ण,
	अणु .compatible = "qcom,sdm845-llcc", .data = &sdm845_cfg पूर्ण,
	अणु .compatible = "qcom,sm8150-llcc", .data = &sm8150_cfg पूर्ण,
	अणु .compatible = "qcom,sm8250-llcc", .data = &sm8250_cfg पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver qcom_llcc_driver = अणु
	.driver = अणु
		.name = "qcom-llcc",
		.of_match_table = qcom_llcc_of_match,
	पूर्ण,
	.probe = qcom_llcc_probe,
	.हटाओ = qcom_llcc_हटाओ,
पूर्ण;
module_platक्रमm_driver(qcom_llcc_driver);

MODULE_DESCRIPTION("Qualcomm Last Level Cache Controller");
MODULE_LICENSE("GPL v2");
