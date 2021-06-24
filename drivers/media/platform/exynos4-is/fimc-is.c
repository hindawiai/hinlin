<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subप्रणाली) driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *
 * Authors: Sylwester Nawrocki <s.nawrocki@samsung.com>
 *          Younghwan Joo <yhwan.joo@samsung.com>
 */
#घोषणा pr_fmt(fmt) "%s:%d " fmt, __func__, __LINE__

#समावेश <linux/device.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "media-dev.h"
#समावेश "fimc-is.h"
#समावेश "fimc-is-command.h"
#समावेश "fimc-is-errno.h"
#समावेश "fimc-is-i2c.h"
#समावेश "fimc-is-param.h"
#समावेश "fimc-is-regs.h"


अटल अक्षर *fimc_is_घड़ीs[ISS_CLKS_MAX] = अणु
	[ISS_CLK_PPMUISPX]		= "ppmuispx",
	[ISS_CLK_PPMUISPMX]		= "ppmuispmx",
	[ISS_CLK_LITE0]			= "lite0",
	[ISS_CLK_LITE1]			= "lite1",
	[ISS_CLK_MPLL]			= "mpll",
	[ISS_CLK_ISP]			= "isp",
	[ISS_CLK_DRC]			= "drc",
	[ISS_CLK_FD]			= "fd",
	[ISS_CLK_MCUISP]		= "mcuisp",
	[ISS_CLK_GICISP]		= "gicisp",
	[ISS_CLK_PWM_ISP]		= "pwm_isp",
	[ISS_CLK_MCUCTL_ISP]		= "mcuctl_isp",
	[ISS_CLK_UART]			= "uart",
	[ISS_CLK_ISP_DIV0]		= "ispdiv0",
	[ISS_CLK_ISP_DIV1]		= "ispdiv1",
	[ISS_CLK_MCUISP_DIV0]		= "mcuispdiv0",
	[ISS_CLK_MCUISP_DIV1]		= "mcuispdiv1",
	[ISS_CLK_ACLK200]		= "aclk200",
	[ISS_CLK_ACLK200_DIV]		= "div_aclk200",
	[ISS_CLK_ACLK400MCUISP]		= "aclk400mcuisp",
	[ISS_CLK_ACLK400MCUISP_DIV]	= "div_aclk400mcuisp",
पूर्ण;

अटल व्योम fimc_is_put_घड़ीs(काष्ठा fimc_is *is)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ISS_CLKS_MAX; i++) अणु
		अगर (IS_ERR(is->घड़ीs[i]))
			जारी;
		clk_put(is->घड़ीs[i]);
		is->घड़ीs[i] = ERR_PTR(-EINVAL);
	पूर्ण
पूर्ण

अटल पूर्णांक fimc_is_get_घड़ीs(काष्ठा fimc_is *is)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ISS_CLKS_MAX; i++)
		is->घड़ीs[i] = ERR_PTR(-EINVAL);

	क्रम (i = 0; i < ISS_CLKS_MAX; i++) अणु
		is->घड़ीs[i] = clk_get(&is->pdev->dev, fimc_is_घड़ीs[i]);
		अगर (IS_ERR(is->घड़ीs[i])) अणु
			ret = PTR_ERR(is->घड़ीs[i]);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	fimc_is_put_घड़ीs(is);
	dev_err(&is->pdev->dev, "failed to get clock: %s\n",
		fimc_is_घड़ीs[i]);
	वापस ret;
पूर्ण

अटल पूर्णांक fimc_is_setup_घड़ीs(काष्ठा fimc_is *is)
अणु
	पूर्णांक ret;

	ret = clk_set_parent(is->घड़ीs[ISS_CLK_ACLK200],
					is->घड़ीs[ISS_CLK_ACLK200_DIV]);
	अगर (ret < 0)
		वापस ret;

	ret = clk_set_parent(is->घड़ीs[ISS_CLK_ACLK400MCUISP],
					is->घड़ीs[ISS_CLK_ACLK400MCUISP_DIV]);
	अगर (ret < 0)
		वापस ret;

	ret = clk_set_rate(is->घड़ीs[ISS_CLK_ISP_DIV0], ACLK_AXI_FREQUENCY);
	अगर (ret < 0)
		वापस ret;

	ret = clk_set_rate(is->घड़ीs[ISS_CLK_ISP_DIV1], ACLK_AXI_FREQUENCY);
	अगर (ret < 0)
		वापस ret;

	ret = clk_set_rate(is->घड़ीs[ISS_CLK_MCUISP_DIV0],
					ATCLK_MCUISP_FREQUENCY);
	अगर (ret < 0)
		वापस ret;

	वापस clk_set_rate(is->घड़ीs[ISS_CLK_MCUISP_DIV1],
					ATCLK_MCUISP_FREQUENCY);
पूर्ण

अटल पूर्णांक fimc_is_enable_घड़ीs(काष्ठा fimc_is *is)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ISS_GATE_CLKS_MAX; i++) अणु
		अगर (IS_ERR(is->घड़ीs[i]))
			जारी;
		ret = clk_prepare_enable(is->घड़ीs[i]);
		अगर (ret < 0) अणु
			dev_err(&is->pdev->dev, "clock %s enable failed\n",
				fimc_is_घड़ीs[i]);
			क्रम (--i; i >= 0; i--)
				clk_disable(is->घड़ीs[i]);
			वापस ret;
		पूर्ण
		pr_debug("enabled clock: %s\n", fimc_is_घड़ीs[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम fimc_is_disable_घड़ीs(काष्ठा fimc_is *is)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ISS_GATE_CLKS_MAX; i++) अणु
		अगर (!IS_ERR(is->घड़ीs[i])) अणु
			clk_disable_unprepare(is->घड़ीs[i]);
			pr_debug("disabled clock: %s\n", fimc_is_घड़ीs[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक fimc_is_parse_sensor_config(काष्ठा fimc_is *is, अचिन्हित पूर्णांक index,
						काष्ठा device_node *node)
अणु
	काष्ठा fimc_is_sensor *sensor = &is->sensor[index];
	काष्ठा device_node *ep, *port;
	u32 पंचांगp = 0;
	पूर्णांक ret;

	sensor->drvdata = fimc_is_sensor_get_drvdata(node);
	अगर (!sensor->drvdata) अणु
		dev_err(&is->pdev->dev, "no driver data found for: %pOF\n",
							 node);
		वापस -EINVAL;
	पूर्ण

	ep = of_graph_get_next_endpoपूर्णांक(node, शून्य);
	अगर (!ep)
		वापस -ENXIO;

	port = of_graph_get_remote_port(ep);
	of_node_put(ep);
	अगर (!port)
		वापस -ENXIO;

	/* Use MIPI-CSIS channel id to determine the ISP I2C bus index. */
	ret = of_property_पढ़ो_u32(port, "reg", &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(&is->pdev->dev, "reg property not found at: %pOF\n",
							 port);
		of_node_put(port);
		वापस ret;
	पूर्ण

	of_node_put(port);
	sensor->i2c_bus = पंचांगp - FIMC_INPUT_MIPI_CSI2_0;
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_is_रेजिस्टर_subdevs(काष्ठा fimc_is *is)
अणु
	काष्ठा device_node *i2c_bus, *child;
	पूर्णांक ret, index = 0;

	ret = fimc_isp_subdev_create(&is->isp);
	अगर (ret < 0)
		वापस ret;

	क्रम_each_compatible_node(i2c_bus, शून्य, FIMC_IS_I2C_COMPATIBLE) अणु
		क्रम_each_available_child_of_node(i2c_bus, child) अणु
			ret = fimc_is_parse_sensor_config(is, index, child);

			अगर (ret < 0 || index >= FIMC_IS_SENSORS_NUM) अणु
				of_node_put(child);
				वापस ret;
			पूर्ण
			index++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_is_unरेजिस्टर_subdevs(काष्ठा fimc_is *is)
अणु
	fimc_isp_subdev_destroy(&is->isp);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_is_load_setfile(काष्ठा fimc_is *is, अक्षर *file_name)
अणु
	स्थिर काष्ठा firmware *fw;
	व्योम *buf;
	पूर्णांक ret;

	ret = request_firmware(&fw, file_name, &is->pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&is->pdev->dev, "firmware request failed (%d)\n", ret);
		वापस ret;
	पूर्ण
	buf = is->memory.vaddr + is->setfile.base;
	स_नकल(buf, fw->data, fw->size);
	fimc_is_mem_barrier();
	is->setfile.size = fw->size;

	pr_debug("mem vaddr: %p, setfile buf: %p\n", is->memory.vaddr, buf);

	स_नकल(is->fw.setfile_info,
		fw->data + fw->size - FIMC_IS_SETखाता_INFO_LEN,
		FIMC_IS_SETखाता_INFO_LEN - 1);

	is->fw.setfile_info[FIMC_IS_SETखाता_INFO_LEN - 1] = '\0';
	is->setfile.state = 1;

	pr_debug("FIMC-IS setfile loaded: base: %#x, size: %zu B\n",
		 is->setfile.base, fw->size);

	release_firmware(fw);
	वापस ret;
पूर्ण

पूर्णांक fimc_is_cpu_set_घातer(काष्ठा fimc_is *is, पूर्णांक on)
अणु
	अचिन्हित पूर्णांक समयout = FIMC_IS_POWER_ON_TIMEOUT;

	अगर (on) अणु
		/* Disable watchकरोg */
		mcuctl_ग_लिखो(0, is, REG_WDT_ISP);

		/* Cortex-A5 start address setting */
		mcuctl_ग_लिखो(is->memory.addr, is, MCUCTL_REG_BBOAR);

		/* Enable and start Cortex-A5 */
		pmuisp_ग_लिखो(0x18000, is, REG_PMU_ISP_ARM_OPTION);
		pmuisp_ग_लिखो(0x1, is, REG_PMU_ISP_ARM_CONFIGURATION);
	पूर्ण अन्यथा अणु
		/* A5 घातer off */
		pmuisp_ग_लिखो(0x10000, is, REG_PMU_ISP_ARM_OPTION);
		pmuisp_ग_लिखो(0x0, is, REG_PMU_ISP_ARM_CONFIGURATION);

		जबतक (pmuisp_पढ़ो(is, REG_PMU_ISP_ARM_STATUS) & 1) अणु
			अगर (समयout == 0)
				वापस -ETIME;
			समयout--;
			udelay(1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Wait until @bit of @is->state is set to @state in the पूर्णांकerrupt handler. */
पूर्णांक fimc_is_रुको_event(काष्ठा fimc_is *is, अचिन्हित दीर्घ bit,
		       अचिन्हित पूर्णांक state, अचिन्हित पूर्णांक समयout)
अणु

	पूर्णांक ret = रुको_event_समयout(is->irq_queue,
				     !state ^ test_bit(bit, &is->state),
				     समयout);
	अगर (ret == 0) अणु
		dev_WARN(&is->pdev->dev, "%s() timed out\n", __func__);
		वापस -ETIME;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक fimc_is_start_firmware(काष्ठा fimc_is *is)
अणु
	काष्ठा device *dev = &is->pdev->dev;
	पूर्णांक ret;

	अगर (is->fw.f_w == शून्य) अणु
		dev_err(dev, "firmware is not loaded\n");
		वापस -EINVAL;
	पूर्ण

	स_नकल(is->memory.vaddr, is->fw.f_w->data, is->fw.f_w->size);
	wmb();

	ret = fimc_is_cpu_set_घातer(is, 1);
	अगर (ret < 0)
		वापस ret;

	ret = fimc_is_रुको_event(is, IS_ST_A5_PWR_ON, 1,
				 msecs_to_jअगरfies(FIMC_IS_FW_LOAD_TIMEOUT));
	अगर (ret < 0)
		dev_err(dev, "FIMC-IS CPU power on failed\n");

	वापस ret;
पूर्ण

/* Allocate working memory क्रम the FIMC-IS CPU. */
अटल पूर्णांक fimc_is_alloc_cpu_memory(काष्ठा fimc_is *is)
अणु
	काष्ठा device *dev = &is->pdev->dev;

	is->memory.vaddr = dma_alloc_coherent(dev, FIMC_IS_CPU_MEM_SIZE,
					      &is->memory.addr, GFP_KERNEL);
	अगर (is->memory.vaddr == शून्य)
		वापस -ENOMEM;

	is->memory.size = FIMC_IS_CPU_MEM_SIZE;

	dev_info(dev, "FIMC-IS CPU memory base: %pad\n", &is->memory.addr);

	अगर (((u32)is->memory.addr) & FIMC_IS_FW_ADDR_MASK) अणु
		dev_err(dev, "invalid firmware memory alignment: %#x\n",
			(u32)is->memory.addr);
		dma_मुक्त_coherent(dev, is->memory.size, is->memory.vaddr,
				  is->memory.addr);
		वापस -EIO;
	पूर्ण

	is->is_p_region = (काष्ठा is_region *)(is->memory.vaddr +
				FIMC_IS_CPU_MEM_SIZE - FIMC_IS_REGION_SIZE);

	is->is_dma_p_region = is->memory.addr +
				FIMC_IS_CPU_MEM_SIZE - FIMC_IS_REGION_SIZE;

	is->is_shared_region = (काष्ठा is_share_region *)(is->memory.vaddr +
				FIMC_IS_SHARED_REGION_OFFSET);
	वापस 0;
पूर्ण

अटल व्योम fimc_is_मुक्त_cpu_memory(काष्ठा fimc_is *is)
अणु
	काष्ठा device *dev = &is->pdev->dev;

	अगर (is->memory.vaddr == शून्य)
		वापस;

	dma_मुक्त_coherent(dev, is->memory.size, is->memory.vaddr,
			  is->memory.addr);
पूर्ण

अटल व्योम fimc_is_load_firmware(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा fimc_is *is = context;
	काष्ठा device *dev = &is->pdev->dev;
	व्योम *buf;
	पूर्णांक ret;

	अगर (fw == शून्य) अणु
		dev_err(dev, "firmware request failed\n");
		वापस;
	पूर्ण
	mutex_lock(&is->lock);

	अगर (fw->size < FIMC_IS_FW_SIZE_MIN || fw->size > FIMC_IS_FW_SIZE_MAX) अणु
		dev_err(dev, "wrong firmware size: %zu\n", fw->size);
		जाओ करोne;
	पूर्ण

	is->fw.size = fw->size;

	ret = fimc_is_alloc_cpu_memory(is);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to allocate FIMC-IS CPU memory\n");
		जाओ करोne;
	पूर्ण

	स_नकल(is->memory.vaddr, fw->data, fw->size);
	wmb();

	/* Read firmware description. */
	buf = (व्योम *)(is->memory.vaddr + fw->size - FIMC_IS_FW_DESC_LEN);
	स_नकल(&is->fw.info, buf, FIMC_IS_FW_INFO_LEN);
	is->fw.info[FIMC_IS_FW_INFO_LEN] = 0;

	buf = (व्योम *)(is->memory.vaddr + fw->size - FIMC_IS_FW_VER_LEN);
	स_नकल(&is->fw.version, buf, FIMC_IS_FW_VER_LEN);
	is->fw.version[FIMC_IS_FW_VER_LEN - 1] = 0;

	is->fw.state = 1;

	dev_info(dev, "loaded firmware: %s, rev. %s\n",
		 is->fw.info, is->fw.version);
	dev_dbg(dev, "FW size: %zu, DMA addr: %pad\n", fw->size, &is->memory.addr);

	is->is_shared_region->chip_id = 0xe4412;
	is->is_shared_region->chip_rev_no = 1;

	fimc_is_mem_barrier();

	/*
	 * FIXME: The firmware is not being released क्रम now, as it is
	 * needed around क्रम copying to the IS working memory every
	 * समय beक्रमe the Cortex-A5 is restarted.
	 */
	release_firmware(is->fw.f_w);
	is->fw.f_w = fw;
करोne:
	mutex_unlock(&is->lock);
पूर्ण

अटल पूर्णांक fimc_is_request_firmware(काष्ठा fimc_is *is, स्थिर अक्षर *fw_name)
अणु
	वापस request_firmware_noरुको(THIS_MODULE,
				FW_ACTION_HOTPLUG, fw_name, &is->pdev->dev,
				GFP_KERNEL, is, fimc_is_load_firmware);
पूर्ण

/* General IS पूर्णांकerrupt handler */
अटल व्योम fimc_is_general_irq_handler(काष्ठा fimc_is *is)
अणु
	is->i2h_cmd.cmd = mcuctl_पढ़ो(is, MCUCTL_REG_ISSR(10));

	चयन (is->i2h_cmd.cmd) अणु
	हाल IHC_GET_SENSOR_NUM:
		fimc_is_hw_get_params(is, 1);
		fimc_is_hw_रुको_पूर्णांकmsr0_पूर्णांकmsd0(is);
		fimc_is_hw_set_sensor_num(is);
		pr_debug("ISP FW version: %#x\n", is->i2h_cmd.args[0]);
		अवरोध;
	हाल IHC_SET_FACE_MARK:
	हाल IHC_FRAME_DONE:
		fimc_is_hw_get_params(is, 2);
		अवरोध;
	हाल IHC_SET_SHOT_MARK:
	हाल IHC_AA_DONE:
	हाल IH_REPLY_DONE:
		fimc_is_hw_get_params(is, 3);
		अवरोध;
	हाल IH_REPLY_NOT_DONE:
		fimc_is_hw_get_params(is, 4);
		अवरोध;
	हाल IHC_NOT_READY:
		अवरोध;
	शेष:
		pr_info("unknown command: %#x\n", is->i2h_cmd.cmd);
	पूर्ण

	fimc_is_fw_clear_irq1(is, FIMC_IS_INT_GENERAL);

	चयन (is->i2h_cmd.cmd) अणु
	हाल IHC_GET_SENSOR_NUM:
		fimc_is_hw_set_पूर्णांकgr0_gd0(is);
		set_bit(IS_ST_A5_PWR_ON, &is->state);
		अवरोध;

	हाल IHC_SET_SHOT_MARK:
		अवरोध;

	हाल IHC_SET_FACE_MARK:
		is->fd_header.count = is->i2h_cmd.args[0];
		is->fd_header.index = is->i2h_cmd.args[1];
		is->fd_header.offset = 0;
		अवरोध;

	हाल IHC_FRAME_DONE:
		अवरोध;

	हाल IHC_AA_DONE:
		pr_debug("AA_DONE - %d, %d, %d\n", is->i2h_cmd.args[0],
			 is->i2h_cmd.args[1], is->i2h_cmd.args[2]);
		अवरोध;

	हाल IH_REPLY_DONE:
		pr_debug("ISR_DONE: args[0]: %#x\n", is->i2h_cmd.args[0]);

		चयन (is->i2h_cmd.args[0]) अणु
		हाल HIC_PREVIEW_STILL...HIC_CAPTURE_VIDEO:
			/* Get CAC margin */
			set_bit(IS_ST_CHANGE_MODE, &is->state);
			is->isp.cac_margin_x = is->i2h_cmd.args[1];
			is->isp.cac_margin_y = is->i2h_cmd.args[2];
			pr_debug("CAC margin (x,y): (%d,%d)\n",
				 is->isp.cac_margin_x, is->isp.cac_margin_y);
			अवरोध;

		हाल HIC_STREAM_ON:
			clear_bit(IS_ST_STREAM_OFF, &is->state);
			set_bit(IS_ST_STREAM_ON, &is->state);
			अवरोध;

		हाल HIC_STREAM_OFF:
			clear_bit(IS_ST_STREAM_ON, &is->state);
			set_bit(IS_ST_STREAM_OFF, &is->state);
			अवरोध;

		हाल HIC_SET_PARAMETER:
			is->config[is->config_index].p_region_index[0] = 0;
			is->config[is->config_index].p_region_index[1] = 0;
			set_bit(IS_ST_BLOCK_CMD_CLEARED, &is->state);
			pr_debug("HIC_SET_PARAMETER\n");
			अवरोध;

		हाल HIC_GET_PARAMETER:
			अवरोध;

		हाल HIC_SET_TUNE:
			अवरोध;

		हाल HIC_GET_STATUS:
			अवरोध;

		हाल HIC_OPEN_SENSOR:
			set_bit(IS_ST_OPEN_SENSOR, &is->state);
			pr_debug("data lanes: %d, settle line: %d\n",
				 is->i2h_cmd.args[2], is->i2h_cmd.args[1]);
			अवरोध;

		हाल HIC_CLOSE_SENSOR:
			clear_bit(IS_ST_OPEN_SENSOR, &is->state);
			is->sensor_index = 0;
			अवरोध;

		हाल HIC_MSG_TEST:
			pr_debug("config MSG level completed\n");
			अवरोध;

		हाल HIC_POWER_DOWN:
			clear_bit(IS_ST_PWR_SUBIP_ON, &is->state);
			अवरोध;

		हाल HIC_GET_SET_खाता_ADDR:
			is->setfile.base = is->i2h_cmd.args[1];
			set_bit(IS_ST_SETखाता_LOADED, &is->state);
			अवरोध;

		हाल HIC_LOAD_SET_खाता:
			set_bit(IS_ST_SETखाता_LOADED, &is->state);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल IH_REPLY_NOT_DONE:
		pr_err("ISR_NDONE: %d: %#x, %s\n", is->i2h_cmd.args[0],
		       is->i2h_cmd.args[1],
		       fimc_is_strerr(is->i2h_cmd.args[1]));

		अगर (is->i2h_cmd.args[1] & IS_ERROR_TIME_OUT_FLAG)
			pr_err("IS_ERROR_TIME_OUT\n");

		चयन (is->i2h_cmd.args[1]) अणु
		हाल IS_ERROR_SET_PARAMETER:
			fimc_is_mem_barrier();
		पूर्ण

		चयन (is->i2h_cmd.args[0]) अणु
		हाल HIC_SET_PARAMETER:
			is->config[is->config_index].p_region_index[0] = 0;
			is->config[is->config_index].p_region_index[1] = 0;
			set_bit(IS_ST_BLOCK_CMD_CLEARED, &is->state);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल IHC_NOT_READY:
		pr_err("IS control sequence error: Not Ready\n");
		अवरोध;
	पूर्ण

	wake_up(&is->irq_queue);
पूर्ण

अटल irqवापस_t fimc_is_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा fimc_is *is = priv;
	अचिन्हित दीर्घ flags;
	u32 status;

	spin_lock_irqsave(&is->slock, flags);
	status = mcuctl_पढ़ो(is, MCUCTL_REG_INTSR1);

	अगर (status & (1UL << FIMC_IS_INT_GENERAL))
		fimc_is_general_irq_handler(is);

	अगर (status & (1UL << FIMC_IS_INT_FRAME_DONE_ISP))
		fimc_isp_irq_handler(is);

	spin_unlock_irqrestore(&is->slock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fimc_is_hw_खोलो_sensor(काष्ठा fimc_is *is,
				  काष्ठा fimc_is_sensor *sensor)
अणु
	काष्ठा sensor_खोलो_extended *soe = (व्योम *)&is->is_p_region->shared;

	fimc_is_hw_रुको_पूर्णांकmsr0_पूर्णांकmsd0(is);

	soe->self_calibration_mode = 1;
	soe->actuator_type = 0;
	soe->mipi_lane_num = 0;
	soe->mclk = 0;
	soe->mipi_speed	= 0;
	soe->fast_खोलो_sensor = 0;
	soe->i2c_sclk = 88000000;

	fimc_is_mem_barrier();

	/*
	 * Some user space use हालs hang up here without this
	 * empirically chosen delay.
	 */
	udelay(100);

	mcuctl_ग_लिखो(HIC_OPEN_SENSOR, is, MCUCTL_REG_ISSR(0));
	mcuctl_ग_लिखो(is->sensor_index, is, MCUCTL_REG_ISSR(1));
	mcuctl_ग_लिखो(sensor->drvdata->id, is, MCUCTL_REG_ISSR(2));
	mcuctl_ग_लिखो(sensor->i2c_bus, is, MCUCTL_REG_ISSR(3));
	mcuctl_ग_लिखो(is->is_dma_p_region, is, MCUCTL_REG_ISSR(4));

	fimc_is_hw_set_पूर्णांकgr0_gd0(is);

	वापस fimc_is_रुको_event(is, IS_ST_OPEN_SENSOR, 1,
				  sensor->drvdata->खोलो_समयout);
पूर्ण


पूर्णांक fimc_is_hw_initialize(काष्ठा fimc_is *is)
अणु
	अटल स्थिर पूर्णांक config_ids[] = अणु
		IS_SC_PREVIEW_STILL, IS_SC_PREVIEW_VIDEO,
		IS_SC_CAPTURE_STILL, IS_SC_CAPTURE_VIDEO
	पूर्ण;
	काष्ठा device *dev = &is->pdev->dev;
	u32 prev_id;
	पूर्णांक i, ret;

	/* Sensor initialization. Only one sensor is currently supported. */
	ret = fimc_is_hw_खोलो_sensor(is, &is->sensor[0]);
	अगर (ret < 0)
		वापस ret;

	/* Get the setfile address. */
	fimc_is_hw_get_setfile_addr(is);

	ret = fimc_is_रुको_event(is, IS_ST_SETखाता_LOADED, 1,
				 FIMC_IS_CONFIG_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(dev, "get setfile address timed out\n");
		वापस ret;
	पूर्ण
	pr_debug("setfile.base: %#x\n", is->setfile.base);

	/* Load the setfile. */
	fimc_is_load_setfile(is, FIMC_IS_SETखाता_6A3);
	clear_bit(IS_ST_SETखाता_LOADED, &is->state);
	fimc_is_hw_load_setfile(is);
	ret = fimc_is_रुको_event(is, IS_ST_SETखाता_LOADED, 1,
				 FIMC_IS_CONFIG_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(dev, "loading setfile timed out\n");
		वापस ret;
	पूर्ण

	pr_debug("setfile: base: %#x, size: %d\n",
		 is->setfile.base, is->setfile.size);
	pr_info("FIMC-IS Setfile info: %s\n", is->fw.setfile_info);

	/* Check magic number. */
	अगर (is->is_p_region->shared[MAX_SHARED_COUNT - 1] !=
	    FIMC_IS_MAGIC_NUMBER) अणु
		dev_err(dev, "magic number error!\n");
		वापस -EIO;
	पूर्ण

	pr_debug("shared region: %pad, parameter region: %pad\n",
		 &is->memory.addr + FIMC_IS_SHARED_REGION_OFFSET,
		 &is->is_dma_p_region);

	is->setfile.sub_index = 0;

	/* Stream off. */
	fimc_is_hw_stream_off(is);
	ret = fimc_is_रुको_event(is, IS_ST_STREAM_OFF, 1,
				 FIMC_IS_CONFIG_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(dev, "stream off timeout\n");
		वापस ret;
	पूर्ण

	/* Preserve previous mode. */
	prev_id = is->config_index;

	/* Set initial parameter values. */
	क्रम (i = 0; i < ARRAY_SIZE(config_ids); i++) अणु
		is->config_index = config_ids[i];
		fimc_is_set_initial_params(is);
		ret = fimc_is_itf_s_param(is, true);
		अगर (ret < 0) अणु
			is->config_index = prev_id;
			वापस ret;
		पूर्ण
	पूर्ण
	is->config_index = prev_id;

	set_bit(IS_ST_INIT_DONE, &is->state);
	dev_info(dev, "initialization sequence completed (%d)\n",
						is->config_index);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_is_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा fimc_is *is = s->निजी;
	स्थिर u8 *buf = is->memory.vaddr + FIMC_IS_DEBUG_REGION_OFFSET;

	अगर (is->memory.vaddr == शून्य) अणु
		dev_err(&is->pdev->dev, "firmware memory is not initialized\n");
		वापस -EIO;
	पूर्ण

	seq_म_लिखो(s, "%s\n", buf);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(fimc_is);

अटल व्योम fimc_is_debugfs_हटाओ(काष्ठा fimc_is *is)
अणु
	debugfs_हटाओ_recursive(is->debugfs_entry);
	is->debugfs_entry = शून्य;
पूर्ण

अटल व्योम fimc_is_debugfs_create(काष्ठा fimc_is *is)
अणु
	is->debugfs_entry = debugfs_create_dir("fimc_is", शून्य);

	debugfs_create_file("fw_log", S_IRUGO, is->debugfs_entry, is,
			    &fimc_is_fops);
पूर्ण

अटल पूर्णांक fimc_is_runसमय_resume(काष्ठा device *dev);
अटल पूर्णांक fimc_is_runसमय_suspend(काष्ठा device *dev);

अटल पूर्णांक fimc_is_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fimc_is *is;
	काष्ठा resource res;
	काष्ठा device_node *node;
	पूर्णांक ret;

	is = devm_kzalloc(&pdev->dev, माप(*is), GFP_KERNEL);
	अगर (!is)
		वापस -ENOMEM;

	is->pdev = pdev;
	is->isp.pdev = pdev;

	init_रुकोqueue_head(&is->irq_queue);
	spin_lock_init(&is->slock);
	mutex_init(&is->lock);

	ret = of_address_to_resource(dev->of_node, 0, &res);
	अगर (ret < 0)
		वापस ret;

	is->regs = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(is->regs))
		वापस PTR_ERR(is->regs);

	node = of_get_child_by_name(dev->of_node, "pmu");
	अगर (!node)
		वापस -ENODEV;

	is->pmu_regs = of_iomap(node, 0);
	of_node_put(node);
	अगर (!is->pmu_regs)
		वापस -ENOMEM;

	is->irq = irq_of_parse_and_map(dev->of_node, 0);
	अगर (!is->irq) अणु
		dev_err(dev, "no irq found\n");
		ret = -EINVAL;
		जाओ err_iounmap;
	पूर्ण

	ret = fimc_is_get_घड़ीs(is);
	अगर (ret < 0)
		जाओ err_iounmap;

	platक्रमm_set_drvdata(pdev, is);

	ret = request_irq(is->irq, fimc_is_irq_handler, 0, dev_name(dev), is);
	अगर (ret < 0) अणु
		dev_err(dev, "irq request failed\n");
		जाओ err_clk;
	पूर्ण
	pm_runसमय_enable(dev);

	अगर (!pm_runसमय_enabled(dev)) अणु
		ret = fimc_is_runसमय_resume(dev);
		अगर (ret < 0)
			जाओ err_irq;
	पूर्ण

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0)
		जाओ err_pm;

	vb2_dma_contig_set_max_seg_size(dev, DMA_BIT_MASK(32));

	ret = devm_of_platक्रमm_populate(dev);
	अगर (ret < 0)
		जाओ err_pm;

	/*
	 * Register FIMC-IS V4L2 subdevs to this driver. The video nodes
	 * will be created within the subdev's रेजिस्टरed() callback.
	 */
	ret = fimc_is_रेजिस्टर_subdevs(is);
	अगर (ret < 0)
		जाओ err_pm;

	fimc_is_debugfs_create(is);

	ret = fimc_is_request_firmware(is, FIMC_IS_FW_खाताNAME);
	अगर (ret < 0)
		जाओ err_dfs;

	pm_runसमय_put_sync(dev);

	dev_dbg(dev, "FIMC-IS registered successfully\n");
	वापस 0;

err_dfs:
	fimc_is_debugfs_हटाओ(is);
	fimc_is_unरेजिस्टर_subdevs(is);
err_pm:
	pm_runसमय_put_noidle(dev);
	अगर (!pm_runसमय_enabled(dev))
		fimc_is_runसमय_suspend(dev);
err_irq:
	मुक्त_irq(is->irq, is);
err_clk:
	fimc_is_put_घड़ीs(is);
err_iounmap:
	iounmap(is->pmu_regs);
	वापस ret;
पूर्ण

अटल पूर्णांक fimc_is_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fimc_is *is = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = fimc_is_setup_घड़ीs(is);
	अगर (ret)
		वापस ret;

	वापस fimc_is_enable_घड़ीs(is);
पूर्ण

अटल पूर्णांक fimc_is_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fimc_is *is = dev_get_drvdata(dev);

	fimc_is_disable_घड़ीs(is);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक fimc_is_resume(काष्ठा device *dev)
अणु
	/* TODO: */
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_is_suspend(काष्ठा device *dev)
अणु
	काष्ठा fimc_is *is = dev_get_drvdata(dev);

	/* TODO: */
	अगर (test_bit(IS_ST_A5_PWR_ON, &is->state))
		वापस -EBUSY;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक fimc_is_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fimc_is *is = dev_get_drvdata(dev);

	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	अगर (!pm_runसमय_status_suspended(dev))
		fimc_is_runसमय_suspend(dev);
	मुक्त_irq(is->irq, is);
	fimc_is_unरेजिस्टर_subdevs(is);
	vb2_dma_contig_clear_max_seg_size(dev);
	fimc_is_put_घड़ीs(is);
	iounmap(is->pmu_regs);
	fimc_is_debugfs_हटाओ(is);
	release_firmware(is->fw.f_w);
	fimc_is_मुक्त_cpu_memory(is);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fimc_is_of_match[] = अणु
	अणु .compatible = "samsung,exynos4212-fimc-is" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fimc_is_of_match);

अटल स्थिर काष्ठा dev_pm_ops fimc_is_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(fimc_is_suspend, fimc_is_resume)
	SET_RUNTIME_PM_OPS(fimc_is_runसमय_suspend, fimc_is_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver fimc_is_driver = अणु
	.probe		= fimc_is_probe,
	.हटाओ		= fimc_is_हटाओ,
	.driver = अणु
		.of_match_table	= fimc_is_of_match,
		.name		= FIMC_IS_DRV_NAME,
		.pm		= &fimc_is_pm_ops,
	पूर्ण
पूर्ण;

अटल पूर्णांक fimc_is_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = fimc_is_रेजिस्टर_i2c_driver();
	अगर (ret < 0)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&fimc_is_driver);

	अगर (ret < 0)
		fimc_is_unरेजिस्टर_i2c_driver();

	वापस ret;
पूर्ण

अटल व्योम fimc_is_module_निकास(व्योम)
अणु
	fimc_is_unरेजिस्टर_i2c_driver();
	platक्रमm_driver_unरेजिस्टर(&fimc_is_driver);
पूर्ण

module_init(fimc_is_module_init);
module_निकास(fimc_is_module_निकास);

MODULE_ALIAS("platform:" FIMC_IS_DRV_NAME);
MODULE_AUTHOR("Younghwan Joo <yhwan.joo@samsung.com>");
MODULE_AUTHOR("Sylwester Nawrocki <s.nawrocki@samsung.com>");
MODULE_LICENSE("GPL v2");
