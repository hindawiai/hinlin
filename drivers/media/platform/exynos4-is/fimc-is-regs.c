<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subप्रणाली) driver
 *
 * Copyright (C) 2012 - 2013 Samsung Electronics Co., Ltd.
 *
 * Authors: Younghwan Joo <yhwan.joo@samsung.com>
 *          Sylwester Nawrocki <s.nawrocki@samsung.com>
 */
#समावेश <linux/delay.h>

#समावेश "fimc-is.h"
#समावेश "fimc-is-command.h"
#समावेश "fimc-is-regs.h"
#समावेश "fimc-is-sensor.h"

व्योम fimc_is_fw_clear_irq1(काष्ठा fimc_is *is, अचिन्हित पूर्णांक nr)
अणु
	mcuctl_ग_लिखो(1UL << nr, is, MCUCTL_REG_INTCR1);
पूर्ण

व्योम fimc_is_fw_clear_irq2(काष्ठा fimc_is *is)
अणु
	u32 cfg = mcuctl_पढ़ो(is, MCUCTL_REG_INTSR2);
	mcuctl_ग_लिखो(cfg, is, MCUCTL_REG_INTCR2);
पूर्ण

व्योम fimc_is_hw_set_पूर्णांकgr0_gd0(काष्ठा fimc_is *is)
अणु
	mcuctl_ग_लिखो(INTGR0_INTGD(0), is, MCUCTL_REG_INTGR0);
पूर्ण

पूर्णांक fimc_is_hw_रुको_पूर्णांकmsr0_पूर्णांकmsd0(काष्ठा fimc_is *is)
अणु
	अचिन्हित पूर्णांक समयout = 2000;
	u32 cfg, status;

	करो अणु
		cfg = mcuctl_पढ़ो(is, MCUCTL_REG_INTMSR0);
		status = INTMSR0_GET_INTMSD(0, cfg);

		अगर (--समयout == 0) अणु
			dev_warn(&is->pdev->dev, "%s timeout\n",
				 __func__);
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(1);
	पूर्ण जबतक (status != 0);

	वापस 0;
पूर्ण

पूर्णांक fimc_is_hw_set_param(काष्ठा fimc_is *is)
अणु
	काष्ठा chain_config *config = &is->config[is->config_index];
	अचिन्हित पूर्णांक param_count = __get_pending_param_count(is);

	fimc_is_hw_रुको_पूर्णांकmsr0_पूर्णांकmsd0(is);

	mcuctl_ग_लिखो(HIC_SET_PARAMETER, is, MCUCTL_REG_ISSR(0));
	mcuctl_ग_लिखो(is->sensor_index, is, MCUCTL_REG_ISSR(1));
	mcuctl_ग_लिखो(is->config_index, is, MCUCTL_REG_ISSR(2));

	mcuctl_ग_लिखो(param_count, is, MCUCTL_REG_ISSR(3));
	mcuctl_ग_लिखो(config->p_region_index[0], is, MCUCTL_REG_ISSR(4));
	mcuctl_ग_लिखो(config->p_region_index[1], is, MCUCTL_REG_ISSR(5));

	fimc_is_hw_set_पूर्णांकgr0_gd0(is);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused fimc_is_hw_set_tune(काष्ठा fimc_is *is)
अणु
	fimc_is_hw_रुको_पूर्णांकmsr0_पूर्णांकmsd0(is);

	mcuctl_ग_लिखो(HIC_SET_TUNE, is, MCUCTL_REG_ISSR(0));
	mcuctl_ग_लिखो(is->sensor_index, is, MCUCTL_REG_ISSR(1));
	mcuctl_ग_लिखो(is->h2i_cmd.entry_id, is, MCUCTL_REG_ISSR(2));

	fimc_is_hw_set_पूर्णांकgr0_gd0(is);
	वापस 0;
पूर्ण

#घोषणा FIMC_IS_MAX_PARAMS	4

पूर्णांक fimc_is_hw_get_params(काष्ठा fimc_is *is, अचिन्हित पूर्णांक num_args)
अणु
	पूर्णांक i;

	अगर (num_args > FIMC_IS_MAX_PARAMS)
		वापस -EINVAL;

	is->i2h_cmd.num_args = num_args;

	क्रम (i = 0; i < FIMC_IS_MAX_PARAMS; i++) अणु
		अगर (i < num_args)
			is->i2h_cmd.args[i] = mcuctl_पढ़ो(is,
					MCUCTL_REG_ISSR(12 + i));
		अन्यथा
			is->i2h_cmd.args[i] = 0;
	पूर्ण
	वापस 0;
पूर्ण

व्योम fimc_is_hw_set_isp_buf_mask(काष्ठा fimc_is *is, अचिन्हित पूर्णांक mask)
अणु
	अगर (hweight32(mask) == 1) अणु
		dev_err(&is->pdev->dev, "%s(): not enough buffers (mask %#x)\n",
							__func__, mask);
		वापस;
	पूर्ण

	अगर (mcuctl_पढ़ो(is, MCUCTL_REG_ISSR(23)) != 0)
		dev_dbg(&is->pdev->dev, "non-zero DMA buffer mask\n");

	mcuctl_ग_लिखो(mask, is, MCUCTL_REG_ISSR(23));
पूर्ण

व्योम fimc_is_hw_set_sensor_num(काष्ठा fimc_is *is)
अणु
	pr_debug("setting sensor index to: %d\n", is->sensor_index);

	mcuctl_ग_लिखो(IH_REPLY_DONE, is, MCUCTL_REG_ISSR(0));
	mcuctl_ग_लिखो(is->sensor_index, is, MCUCTL_REG_ISSR(1));
	mcuctl_ग_लिखो(IHC_GET_SENSOR_NUM, is, MCUCTL_REG_ISSR(2));
	mcuctl_ग_लिखो(FIMC_IS_SENSORS_NUM, is, MCUCTL_REG_ISSR(3));
पूर्ण

व्योम fimc_is_hw_बंद_sensor(काष्ठा fimc_is *is, अचिन्हित पूर्णांक index)
अणु
	अगर (is->sensor_index != index)
		वापस;

	fimc_is_hw_रुको_पूर्णांकmsr0_पूर्णांकmsd0(is);
	mcuctl_ग_लिखो(HIC_CLOSE_SENSOR, is, MCUCTL_REG_ISSR(0));
	mcuctl_ग_लिखो(is->sensor_index, is, MCUCTL_REG_ISSR(1));
	mcuctl_ग_लिखो(is->sensor_index, is, MCUCTL_REG_ISSR(2));
	fimc_is_hw_set_पूर्णांकgr0_gd0(is);
पूर्ण

व्योम fimc_is_hw_get_setfile_addr(काष्ठा fimc_is *is)
अणु
	fimc_is_hw_रुको_पूर्णांकmsr0_पूर्णांकmsd0(is);
	mcuctl_ग_लिखो(HIC_GET_SET_खाता_ADDR, is, MCUCTL_REG_ISSR(0));
	mcuctl_ग_लिखो(is->sensor_index, is, MCUCTL_REG_ISSR(1));
	fimc_is_hw_set_पूर्णांकgr0_gd0(is);
पूर्ण

व्योम fimc_is_hw_load_setfile(काष्ठा fimc_is *is)
अणु
	fimc_is_hw_रुको_पूर्णांकmsr0_पूर्णांकmsd0(is);
	mcuctl_ग_लिखो(HIC_LOAD_SET_खाता, is, MCUCTL_REG_ISSR(0));
	mcuctl_ग_लिखो(is->sensor_index, is, MCUCTL_REG_ISSR(1));
	fimc_is_hw_set_पूर्णांकgr0_gd0(is);
पूर्ण

पूर्णांक fimc_is_hw_change_mode(काष्ठा fimc_is *is)
अणु
	अटल स्थिर u8 cmd[] = अणु
		HIC_PREVIEW_STILL, HIC_PREVIEW_VIDEO,
		HIC_CAPTURE_STILL, HIC_CAPTURE_VIDEO,
	पूर्ण;

	अगर (WARN_ON(is->config_index >= ARRAY_SIZE(cmd)))
		वापस -EINVAL;

	mcuctl_ग_लिखो(cmd[is->config_index], is, MCUCTL_REG_ISSR(0));
	mcuctl_ग_लिखो(is->sensor_index, is, MCUCTL_REG_ISSR(1));
	mcuctl_ग_लिखो(is->setfile.sub_index, is, MCUCTL_REG_ISSR(2));
	fimc_is_hw_set_पूर्णांकgr0_gd0(is);
	वापस 0;
पूर्ण

व्योम fimc_is_hw_stream_on(काष्ठा fimc_is *is)
अणु
	fimc_is_hw_रुको_पूर्णांकmsr0_पूर्णांकmsd0(is);
	mcuctl_ग_लिखो(HIC_STREAM_ON, is, MCUCTL_REG_ISSR(0));
	mcuctl_ग_लिखो(is->sensor_index, is, MCUCTL_REG_ISSR(1));
	mcuctl_ग_लिखो(0, is, MCUCTL_REG_ISSR(2));
	fimc_is_hw_set_पूर्णांकgr0_gd0(is);
पूर्ण

व्योम fimc_is_hw_stream_off(काष्ठा fimc_is *is)
अणु
	fimc_is_hw_रुको_पूर्णांकmsr0_पूर्णांकmsd0(is);
	mcuctl_ग_लिखो(HIC_STREAM_OFF, is, MCUCTL_REG_ISSR(0));
	mcuctl_ग_लिखो(is->sensor_index, is, MCUCTL_REG_ISSR(1));
	fimc_is_hw_set_पूर्णांकgr0_gd0(is);
पूर्ण

व्योम fimc_is_hw_subip_घातer_off(काष्ठा fimc_is *is)
अणु
	fimc_is_hw_रुको_पूर्णांकmsr0_पूर्णांकmsd0(is);
	mcuctl_ग_लिखो(HIC_POWER_DOWN, is, MCUCTL_REG_ISSR(0));
	mcuctl_ग_लिखो(is->sensor_index, is, MCUCTL_REG_ISSR(1));
	fimc_is_hw_set_पूर्णांकgr0_gd0(is);
पूर्ण

पूर्णांक fimc_is_itf_s_param(काष्ठा fimc_is *is, bool update)
अणु
	पूर्णांक ret;

	अगर (update)
		__is_hw_update_params(is);

	fimc_is_mem_barrier();

	clear_bit(IS_ST_BLOCK_CMD_CLEARED, &is->state);
	fimc_is_hw_set_param(is);
	ret = fimc_is_रुको_event(is, IS_ST_BLOCK_CMD_CLEARED, 1,
				FIMC_IS_CONFIG_TIMEOUT);
	अगर (ret < 0)
		dev_err(&is->pdev->dev, "%s() timeout\n", __func__);

	वापस ret;
पूर्ण

पूर्णांक fimc_is_itf_mode_change(काष्ठा fimc_is *is)
अणु
	पूर्णांक ret;

	clear_bit(IS_ST_CHANGE_MODE, &is->state);
	fimc_is_hw_change_mode(is);
	ret = fimc_is_रुको_event(is, IS_ST_CHANGE_MODE, 1,
				FIMC_IS_CONFIG_TIMEOUT);
	अगर (ret < 0)
		dev_err(&is->pdev->dev, "%s(): mode change (%d) timeout\n",
			__func__, is->config_index);
	वापस ret;
पूर्ण
