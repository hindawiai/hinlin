<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/designware_i2s.h>
#समावेश <sound/pcm.h>

#समावेश "amdgpu.h"
#समावेश "atom.h"
#समावेश "amdgpu_acp.h"

#समावेश "acp_gfx_if.h"

#घोषणा ACP_TILE_ON_MASK			0x03
#घोषणा ACP_TILE_OFF_MASK			0x02
#घोषणा ACP_TILE_ON_RETAIN_REG_MASK		0x1f
#घोषणा ACP_TILE_OFF_RETAIN_REG_MASK		0x20

#घोषणा ACP_TILE_P1_MASK			0x3e
#घोषणा ACP_TILE_P2_MASK			0x3d
#घोषणा ACP_TILE_DSP0_MASK			0x3b
#घोषणा ACP_TILE_DSP1_MASK			0x37

#घोषणा ACP_TILE_DSP2_MASK			0x2f

#घोषणा ACP_DMA_REGS_END			0x146c0
#घोषणा ACP_I2S_PLAY_REGS_START			0x14840
#घोषणा ACP_I2S_PLAY_REGS_END			0x148b4
#घोषणा ACP_I2S_CAP_REGS_START			0x148b8
#घोषणा ACP_I2S_CAP_REGS_END			0x1496c

#घोषणा ACP_I2S_COMP1_CAP_REG_OFFSET		0xac
#घोषणा ACP_I2S_COMP2_CAP_REG_OFFSET		0xa8
#घोषणा ACP_I2S_COMP1_PLAY_REG_OFFSET		0x6c
#घोषणा ACP_I2S_COMP2_PLAY_REG_OFFSET		0x68
#घोषणा ACP_BT_PLAY_REGS_START			0x14970
#घोषणा ACP_BT_PLAY_REGS_END			0x14a24
#घोषणा ACP_BT_COMP1_REG_OFFSET			0xac
#घोषणा ACP_BT_COMP2_REG_OFFSET			0xa8

#घोषणा mmACP_PGFSM_RETAIN_REG			0x51c9
#घोषणा mmACP_PGFSM_CONFIG_REG			0x51ca
#घोषणा mmACP_PGFSM_READ_REG_0			0x51cc

#घोषणा mmACP_MEM_SHUT_DOWN_REQ_LO		0x51f8
#घोषणा mmACP_MEM_SHUT_DOWN_REQ_HI		0x51f9
#घोषणा mmACP_MEM_SHUT_DOWN_STS_LO		0x51fa
#घोषणा mmACP_MEM_SHUT_DOWN_STS_HI		0x51fb

#घोषणा mmACP_CONTROL				0x5131
#घोषणा mmACP_STATUS				0x5133
#घोषणा mmACP_SOFT_RESET			0x5134
#घोषणा ACP_CONTROL__ClkEn_MASK			0x1
#घोषणा ACP_SOFT_RESET__SoftResetAud_MASK	0x100
#घोषणा ACP_SOFT_RESET__SoftResetAudDone_MASK	0x1000000
#घोषणा ACP_CLOCK_EN_TIME_OUT_VALUE		0x000000FF
#घोषणा ACP_SOFT_RESET_DONE_TIME_OUT_VALUE	0x000000FF

#घोषणा ACP_TIMEOUT_LOOP			0x000000FF
#घोषणा ACP_DEVS				4
#घोषणा ACP_SRC_ID				162

क्रमागत अणु
	ACP_TILE_P1 = 0,
	ACP_TILE_P2,
	ACP_TILE_DSP0,
	ACP_TILE_DSP1,
	ACP_TILE_DSP2,
पूर्ण;

अटल पूर्णांक acp_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->acp.parent = adev->dev;

	adev->acp.cgs_device =
		amdgpu_cgs_create_device(adev);
	अगर (!adev->acp.cgs_device)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक acp_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev->acp.cgs_device)
		amdgpu_cgs_destroy_device(adev->acp.cgs_device);

	वापस 0;
पूर्ण

काष्ठा acp_pm_करोमुख्य अणु
	व्योम *adev;
	काष्ठा generic_pm_करोमुख्य gpd;
पूर्ण;

अटल पूर्णांक acp_घातeroff(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा acp_pm_करोमुख्य *apd;
	काष्ठा amdgpu_device *adev;

	apd = container_of(genpd, काष्ठा acp_pm_करोमुख्य, gpd);
	अगर (apd != शून्य) अणु
		adev = apd->adev;
	/* call smu to POWER GATE ACP block
	 * smu will
	 * 1. turn off the acp घड़ी
	 * 2. घातer off the acp tiles
	 * 3. check and enter ulv state
	 */
		amdgpu_dpm_set_घातergating_by_smu(adev, AMD_IP_BLOCK_TYPE_ACP, true);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acp_घातeron(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा acp_pm_करोमुख्य *apd;
	काष्ठा amdgpu_device *adev;

	apd = container_of(genpd, काष्ठा acp_pm_करोमुख्य, gpd);
	अगर (apd != शून्य) अणु
		adev = apd->adev;
	/* call smu to UNGATE ACP block
	 * smu will
	 * 1. निकास ulv
	 * 2. turn on acp घड़ी
	 * 3. घातer on acp tiles
	 */
		amdgpu_dpm_set_घातergating_by_smu(adev, AMD_IP_BLOCK_TYPE_ACP, false);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा device *get_mfd_cell_dev(स्थिर अक्षर *device_name, पूर्णांक r)
अणु
	अक्षर स्वतः_dev_name[25];
	काष्ठा device *dev;

	snम_लिखो(स्वतः_dev_name, माप(स्वतः_dev_name),
		 "%s.%d.auto", device_name, r);
	dev = bus_find_device_by_name(&platक्रमm_bus_type, शून्य, स्वतः_dev_name);
	dev_info(dev, "device %s added to pm domain\n", स्वतः_dev_name);

	वापस dev;
पूर्ण

/**
 * acp_hw_init - start and test ACP block
 *
 * @handle: handle used to pass amdgpu_device poपूर्णांकer
 *
 */
अटल पूर्णांक acp_hw_init(व्योम *handle)
अणु
	पूर्णांक r, i;
	uपूर्णांक64_t acp_base;
	u32 val = 0;
	u32 count = 0;
	काष्ठा device *dev;
	काष्ठा i2s_platक्रमm_data *i2s_pdata = शून्य;

	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	स्थिर काष्ठा amdgpu_ip_block *ip_block =
		amdgpu_device_ip_get_ip_block(adev, AMD_IP_BLOCK_TYPE_ACP);

	अगर (!ip_block)
		वापस -EINVAL;

	r = amd_acp_hw_init(adev->acp.cgs_device,
			    ip_block->version->major, ip_block->version->minor);
	/* -ENODEV means board uses AZ rather than ACP */
	अगर (r == -ENODEV) अणु
		amdgpu_dpm_set_घातergating_by_smu(adev, AMD_IP_BLOCK_TYPE_ACP, true);
		वापस 0;
	पूर्ण अन्यथा अगर (r) अणु
		वापस r;
	पूर्ण

	अगर (adev->rmmio_size == 0 || adev->rmmio_size < 0x5289)
		वापस -EINVAL;

	acp_base = adev->rmmio_base;


	adev->acp.acp_genpd = kzalloc(माप(काष्ठा acp_pm_करोमुख्य), GFP_KERNEL);
	अगर (adev->acp.acp_genpd == शून्य)
		वापस -ENOMEM;

	adev->acp.acp_genpd->gpd.name = "ACP_AUDIO";
	adev->acp.acp_genpd->gpd.घातer_off = acp_घातeroff;
	adev->acp.acp_genpd->gpd.घातer_on = acp_घातeron;


	adev->acp.acp_genpd->adev = adev;

	pm_genpd_init(&adev->acp.acp_genpd->gpd, शून्य, false);

	adev->acp.acp_cell = kसुस्मृति(ACP_DEVS, माप(काष्ठा mfd_cell),
							GFP_KERNEL);

	अगर (adev->acp.acp_cell == शून्य) अणु
		r = -ENOMEM;
		जाओ failure;
	पूर्ण

	adev->acp.acp_res = kसुस्मृति(5, माप(काष्ठा resource), GFP_KERNEL);
	अगर (adev->acp.acp_res == शून्य) अणु
		r = -ENOMEM;
		जाओ failure;
	पूर्ण

	i2s_pdata = kसुस्मृति(3, माप(काष्ठा i2s_platक्रमm_data), GFP_KERNEL);
	अगर (i2s_pdata == शून्य) अणु
		r = -ENOMEM;
		जाओ failure;
	पूर्ण

	चयन (adev->asic_type) अणु
	हाल CHIP_STONEY:
		i2s_pdata[0].quirks = DW_I2S_QUIRK_COMP_REG_OFFSET |
			DW_I2S_QUIRK_16BIT_IDX_OVERRIDE;
		अवरोध;
	शेष:
		i2s_pdata[0].quirks = DW_I2S_QUIRK_COMP_REG_OFFSET;
	पूर्ण
	i2s_pdata[0].cap = DWC_I2S_PLAY;
	i2s_pdata[0].snd_rates = SNDRV_PCM_RATE_8000_96000;
	i2s_pdata[0].i2s_reg_comp1 = ACP_I2S_COMP1_PLAY_REG_OFFSET;
	i2s_pdata[0].i2s_reg_comp2 = ACP_I2S_COMP2_PLAY_REG_OFFSET;
	चयन (adev->asic_type) अणु
	हाल CHIP_STONEY:
		i2s_pdata[1].quirks = DW_I2S_QUIRK_COMP_REG_OFFSET |
			DW_I2S_QUIRK_COMP_PARAM1 |
			DW_I2S_QUIRK_16BIT_IDX_OVERRIDE;
		अवरोध;
	शेष:
		i2s_pdata[1].quirks = DW_I2S_QUIRK_COMP_REG_OFFSET |
			DW_I2S_QUIRK_COMP_PARAM1;
	पूर्ण

	i2s_pdata[1].cap = DWC_I2S_RECORD;
	i2s_pdata[1].snd_rates = SNDRV_PCM_RATE_8000_96000;
	i2s_pdata[1].i2s_reg_comp1 = ACP_I2S_COMP1_CAP_REG_OFFSET;
	i2s_pdata[1].i2s_reg_comp2 = ACP_I2S_COMP2_CAP_REG_OFFSET;

	i2s_pdata[2].quirks = DW_I2S_QUIRK_COMP_REG_OFFSET;
	चयन (adev->asic_type) अणु
	हाल CHIP_STONEY:
		i2s_pdata[2].quirks |= DW_I2S_QUIRK_16BIT_IDX_OVERRIDE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	i2s_pdata[2].cap = DWC_I2S_PLAY | DWC_I2S_RECORD;
	i2s_pdata[2].snd_rates = SNDRV_PCM_RATE_8000_96000;
	i2s_pdata[2].i2s_reg_comp1 = ACP_BT_COMP1_REG_OFFSET;
	i2s_pdata[2].i2s_reg_comp2 = ACP_BT_COMP2_REG_OFFSET;

	adev->acp.acp_res[0].name = "acp2x_dma";
	adev->acp.acp_res[0].flags = IORESOURCE_MEM;
	adev->acp.acp_res[0].start = acp_base;
	adev->acp.acp_res[0].end = acp_base + ACP_DMA_REGS_END;

	adev->acp.acp_res[1].name = "acp2x_dw_i2s_play";
	adev->acp.acp_res[1].flags = IORESOURCE_MEM;
	adev->acp.acp_res[1].start = acp_base + ACP_I2S_PLAY_REGS_START;
	adev->acp.acp_res[1].end = acp_base + ACP_I2S_PLAY_REGS_END;

	adev->acp.acp_res[2].name = "acp2x_dw_i2s_cap";
	adev->acp.acp_res[2].flags = IORESOURCE_MEM;
	adev->acp.acp_res[2].start = acp_base + ACP_I2S_CAP_REGS_START;
	adev->acp.acp_res[2].end = acp_base + ACP_I2S_CAP_REGS_END;

	adev->acp.acp_res[3].name = "acp2x_dw_bt_i2s_play_cap";
	adev->acp.acp_res[3].flags = IORESOURCE_MEM;
	adev->acp.acp_res[3].start = acp_base + ACP_BT_PLAY_REGS_START;
	adev->acp.acp_res[3].end = acp_base + ACP_BT_PLAY_REGS_END;

	adev->acp.acp_res[4].name = "acp2x_dma_irq";
	adev->acp.acp_res[4].flags = IORESOURCE_IRQ;
	adev->acp.acp_res[4].start = amdgpu_irq_create_mapping(adev, 162);
	adev->acp.acp_res[4].end = adev->acp.acp_res[4].start;

	adev->acp.acp_cell[0].name = "acp_audio_dma";
	adev->acp.acp_cell[0].num_resources = 5;
	adev->acp.acp_cell[0].resources = &adev->acp.acp_res[0];
	adev->acp.acp_cell[0].platक्रमm_data = &adev->asic_type;
	adev->acp.acp_cell[0].pdata_size = माप(adev->asic_type);

	adev->acp.acp_cell[1].name = "designware-i2s";
	adev->acp.acp_cell[1].num_resources = 1;
	adev->acp.acp_cell[1].resources = &adev->acp.acp_res[1];
	adev->acp.acp_cell[1].platक्रमm_data = &i2s_pdata[0];
	adev->acp.acp_cell[1].pdata_size = माप(काष्ठा i2s_platक्रमm_data);

	adev->acp.acp_cell[2].name = "designware-i2s";
	adev->acp.acp_cell[2].num_resources = 1;
	adev->acp.acp_cell[2].resources = &adev->acp.acp_res[2];
	adev->acp.acp_cell[2].platक्रमm_data = &i2s_pdata[1];
	adev->acp.acp_cell[2].pdata_size = माप(काष्ठा i2s_platक्रमm_data);

	adev->acp.acp_cell[3].name = "designware-i2s";
	adev->acp.acp_cell[3].num_resources = 1;
	adev->acp.acp_cell[3].resources = &adev->acp.acp_res[3];
	adev->acp.acp_cell[3].platक्रमm_data = &i2s_pdata[2];
	adev->acp.acp_cell[3].pdata_size = माप(काष्ठा i2s_platक्रमm_data);

	r = mfd_add_hotplug_devices(adev->acp.parent, adev->acp.acp_cell,
								ACP_DEVS);
	अगर (r)
		जाओ failure;

	क्रम (i = 0; i < ACP_DEVS ; i++) अणु
		dev = get_mfd_cell_dev(adev->acp.acp_cell[i].name, i);
		r = pm_genpd_add_device(&adev->acp.acp_genpd->gpd, dev);
		अगर (r) अणु
			dev_err(dev, "Failed to add dev to genpd\n");
			जाओ failure;
		पूर्ण
	पूर्ण


	/* Assert Soft reset of ACP */
	val = cgs_पढ़ो_रेजिस्टर(adev->acp.cgs_device, mmACP_SOFT_RESET);

	val |= ACP_SOFT_RESET__SoftResetAud_MASK;
	cgs_ग_लिखो_रेजिस्टर(adev->acp.cgs_device, mmACP_SOFT_RESET, val);

	count = ACP_SOFT_RESET_DONE_TIME_OUT_VALUE;
	जबतक (true) अणु
		val = cgs_पढ़ो_रेजिस्टर(adev->acp.cgs_device, mmACP_SOFT_RESET);
		अगर (ACP_SOFT_RESET__SoftResetAudDone_MASK ==
		    (val & ACP_SOFT_RESET__SoftResetAudDone_MASK))
			अवरोध;
		अगर (--count == 0) अणु
			dev_err(&adev->pdev->dev, "Failed to reset ACP\n");
			r = -ETIMEDOUT;
			जाओ failure;
		पूर्ण
		udelay(100);
	पूर्ण
	/* Enable घड़ी to ACP and रुको until the घड़ी is enabled */
	val = cgs_पढ़ो_रेजिस्टर(adev->acp.cgs_device, mmACP_CONTROL);
	val = val | ACP_CONTROL__ClkEn_MASK;
	cgs_ग_लिखो_रेजिस्टर(adev->acp.cgs_device, mmACP_CONTROL, val);

	count = ACP_CLOCK_EN_TIME_OUT_VALUE;

	जबतक (true) अणु
		val = cgs_पढ़ो_रेजिस्टर(adev->acp.cgs_device, mmACP_STATUS);
		अगर (val & (u32) 0x1)
			अवरोध;
		अगर (--count == 0) अणु
			dev_err(&adev->pdev->dev, "Failed to reset ACP\n");
			r = -ETIMEDOUT;
			जाओ failure;
		पूर्ण
		udelay(100);
	पूर्ण
	/* Deनिश्चित the SOFT RESET flags */
	val = cgs_पढ़ो_रेजिस्टर(adev->acp.cgs_device, mmACP_SOFT_RESET);
	val &= ~ACP_SOFT_RESET__SoftResetAud_MASK;
	cgs_ग_लिखो_रेजिस्टर(adev->acp.cgs_device, mmACP_SOFT_RESET, val);
	वापस 0;

failure:
	kमुक्त(i2s_pdata);
	kमुक्त(adev->acp.acp_res);
	kमुक्त(adev->acp.acp_cell);
	kमुक्त(adev->acp.acp_genpd);
	वापस r;
पूर्ण

/**
 * acp_hw_fini - stop the hardware block
 *
 * @handle: handle used to pass amdgpu_device poपूर्णांकer
 *
 */
अटल पूर्णांक acp_hw_fini(व्योम *handle)
अणु
	पूर्णांक i, ret;
	u32 val = 0;
	u32 count = 0;
	काष्ठा device *dev;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* वापस early अगर no ACP */
	अगर (!adev->acp.acp_genpd) अणु
		amdgpu_dpm_set_घातergating_by_smu(adev, AMD_IP_BLOCK_TYPE_ACP, false);
		वापस 0;
	पूर्ण

	/* Assert Soft reset of ACP */
	val = cgs_पढ़ो_रेजिस्टर(adev->acp.cgs_device, mmACP_SOFT_RESET);

	val |= ACP_SOFT_RESET__SoftResetAud_MASK;
	cgs_ग_लिखो_रेजिस्टर(adev->acp.cgs_device, mmACP_SOFT_RESET, val);

	count = ACP_SOFT_RESET_DONE_TIME_OUT_VALUE;
	जबतक (true) अणु
		val = cgs_पढ़ो_रेजिस्टर(adev->acp.cgs_device, mmACP_SOFT_RESET);
		अगर (ACP_SOFT_RESET__SoftResetAudDone_MASK ==
		    (val & ACP_SOFT_RESET__SoftResetAudDone_MASK))
			अवरोध;
		अगर (--count == 0) अणु
			dev_err(&adev->pdev->dev, "Failed to reset ACP\n");
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(100);
	पूर्ण
	/* Disable ACP घड़ी */
	val = cgs_पढ़ो_रेजिस्टर(adev->acp.cgs_device, mmACP_CONTROL);
	val &= ~ACP_CONTROL__ClkEn_MASK;
	cgs_ग_लिखो_रेजिस्टर(adev->acp.cgs_device, mmACP_CONTROL, val);

	count = ACP_CLOCK_EN_TIME_OUT_VALUE;

	जबतक (true) अणु
		val = cgs_पढ़ो_रेजिस्टर(adev->acp.cgs_device, mmACP_STATUS);
		अगर (val & (u32) 0x1)
			अवरोध;
		अगर (--count == 0) अणु
			dev_err(&adev->pdev->dev, "Failed to reset ACP\n");
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(100);
	पूर्ण

	क्रम (i = 0; i < ACP_DEVS ; i++) अणु
		dev = get_mfd_cell_dev(adev->acp.acp_cell[i].name, i);
		ret = pm_genpd_हटाओ_device(dev);
		/* If removal fails, करोnt giveup and try rest */
		अगर (ret)
			dev_err(dev, "remove dev from genpd failed\n");
	पूर्ण

	mfd_हटाओ_devices(adev->acp.parent);
	kमुक्त(adev->acp.acp_res);
	kमुक्त(adev->acp.acp_genpd);
	kमुक्त(adev->acp.acp_cell);

	वापस 0;
पूर्ण

अटल पूर्णांक acp_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* घातer up on suspend */
	अगर (!adev->acp.acp_cell)
		amdgpu_dpm_set_घातergating_by_smu(adev, AMD_IP_BLOCK_TYPE_ACP, false);
	वापस 0;
पूर्ण

अटल पूर्णांक acp_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* घातer करोwn again on resume */
	अगर (!adev->acp.acp_cell)
		amdgpu_dpm_set_घातergating_by_smu(adev, AMD_IP_BLOCK_TYPE_ACP, true);
	वापस 0;
पूर्ण

अटल पूर्णांक acp_early_init(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल bool acp_is_idle(व्योम *handle)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक acp_रुको_क्रम_idle(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक acp_soft_reset(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक acp_set_घड़ीgating_state(व्योम *handle,
				     क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक acp_set_घातergating_state(व्योम *handle,
				     क्रमागत amd_घातergating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	bool enable = (state == AMD_PG_STATE_GATE);

	amdgpu_dpm_set_घातergating_by_smu(adev, AMD_IP_BLOCK_TYPE_ACP, enable);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs acp_ip_funcs = अणु
	.name = "acp_ip",
	.early_init = acp_early_init,
	.late_init = शून्य,
	.sw_init = acp_sw_init,
	.sw_fini = acp_sw_fini,
	.hw_init = acp_hw_init,
	.hw_fini = acp_hw_fini,
	.suspend = acp_suspend,
	.resume = acp_resume,
	.is_idle = acp_is_idle,
	.रुको_क्रम_idle = acp_रुको_क्रम_idle,
	.soft_reset = acp_soft_reset,
	.set_घड़ीgating_state = acp_set_घड़ीgating_state,
	.set_घातergating_state = acp_set_घातergating_state,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version acp_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_ACP,
	.major = 2,
	.minor = 2,
	.rev = 0,
	.funcs = &acp_ip_funcs,
पूर्ण;
