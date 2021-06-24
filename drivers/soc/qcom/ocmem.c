<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * The On Chip Memory (OCMEM) allocator allows various clients to allocate
 * memory from OCMEM based on perक्रमmance, latency and घातer requirements.
 * This is typically used by the GPU, camera/video, and audio components on
 * some Snapdragon SoCs.
 *
 * Copyright (C) 2019 Brian Masney <masneyb@onstation.org>
 * Copyright (C) 2015 Red Hat. Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/qcom_scm.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <soc/qcom/ocस्मृति.स>

क्रमागत region_mode अणु
	WIDE_MODE = 0x0,
	THIN_MODE,
	MODE_DEFAULT = WIDE_MODE,
पूर्ण;

क्रमागत ocmem_macro_state अणु
	PASSTHROUGH = 0,
	PERI_ON = 1,
	CORE_ON = 2,
	CLK_OFF = 4,
पूर्ण;

काष्ठा ocmem_region अणु
	bool पूर्णांकerleaved;
	क्रमागत region_mode mode;
	अचिन्हित पूर्णांक num_macros;
	क्रमागत ocmem_macro_state macro_state[4];
	अचिन्हित दीर्घ macro_size;
	अचिन्हित दीर्घ region_size;
पूर्ण;

काष्ठा ocmem_config अणु
	uपूर्णांक8_t num_regions;
	अचिन्हित दीर्घ macro_size;
पूर्ण;

काष्ठा ocmem अणु
	काष्ठा device *dev;
	स्थिर काष्ठा ocmem_config *config;
	काष्ठा resource *memory;
	व्योम __iomem *mmio;
	अचिन्हित पूर्णांक num_ports;
	अचिन्हित पूर्णांक num_macros;
	bool पूर्णांकerleaved;
	काष्ठा ocmem_region *regions;
	अचिन्हित दीर्घ active_allocations;
पूर्ण;

#घोषणा OCMEM_MIN_ALIGN				SZ_64K
#घोषणा OCMEM_MIN_ALLOC				SZ_64K

#घोषणा OCMEM_REG_HW_VERSION			0x00000000
#घोषणा OCMEM_REG_HW_PROखाता			0x00000004

#घोषणा OCMEM_REG_REGION_MODE_CTL		0x00001000
#घोषणा OCMEM_REGION_MODE_CTL_REG0_THIN		0x00000001
#घोषणा OCMEM_REGION_MODE_CTL_REG1_THIN		0x00000002
#घोषणा OCMEM_REGION_MODE_CTL_REG2_THIN		0x00000004
#घोषणा OCMEM_REGION_MODE_CTL_REG3_THIN		0x00000008

#घोषणा OCMEM_REG_GFX_MPU_START			0x00001004
#घोषणा OCMEM_REG_GFX_MPU_END			0x00001008

#घोषणा OCMEM_HW_PROखाता_NUM_PORTS(val)		FIELD_PREP(0x0000000f, (val))
#घोषणा OCMEM_HW_PROखाता_NUM_MACROS(val)	FIELD_PREP(0x00003f00, (val))

#घोषणा OCMEM_HW_PROखाता_LAST_REGN_HALFSIZE	0x00010000
#घोषणा OCMEM_HW_PROखाता_INTERLEAVING		0x00020000
#घोषणा OCMEM_REG_GEN_STATUS			0x0000000c

#घोषणा OCMEM_REG_PSGSC_STATUS			0x00000038
#घोषणा OCMEM_REG_PSGSC_CTL(i0)			(0x0000003c + 0x1*(i0))

#घोषणा OCMEM_PSGSC_CTL_MACRO0_MODE(val)	FIELD_PREP(0x00000007, (val))
#घोषणा OCMEM_PSGSC_CTL_MACRO1_MODE(val)	FIELD_PREP(0x00000070, (val))
#घोषणा OCMEM_PSGSC_CTL_MACRO2_MODE(val)	FIELD_PREP(0x00000700, (val))
#घोषणा OCMEM_PSGSC_CTL_MACRO3_MODE(val)	FIELD_PREP(0x00007000, (val))

#घोषणा OCMEM_CLK_CORE_IDX			0
अटल काष्ठा clk_bulk_data ocmem_clks[] = अणु
	अणु
		.id = "core",
	पूर्ण,
	अणु
		.id = "iface",
	पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम ocmem_ग_लिखो(काष्ठा ocmem *ocmem, u32 reg, u32 data)
अणु
	ग_लिखोl(data, ocmem->mmio + reg);
पूर्ण

अटल अंतरभूत u32 ocmem_पढ़ो(काष्ठा ocmem *ocmem, u32 reg)
अणु
	वापस पढ़ोl(ocmem->mmio + reg);
पूर्ण

अटल व्योम update_ocmem(काष्ठा ocmem *ocmem)
अणु
	uपूर्णांक32_t region_mode_ctrl = 0x0;
	पूर्णांक i;

	अगर (!qcom_scm_ocmem_lock_available()) अणु
		क्रम (i = 0; i < ocmem->config->num_regions; i++) अणु
			काष्ठा ocmem_region *region = &ocmem->regions[i];

			अगर (region->mode == THIN_MODE)
				region_mode_ctrl |= BIT(i);
		पूर्ण

		dev_dbg(ocmem->dev, "ocmem_region_mode_control %x\n",
			region_mode_ctrl);
		ocmem_ग_लिखो(ocmem, OCMEM_REG_REGION_MODE_CTL, region_mode_ctrl);
	पूर्ण

	क्रम (i = 0; i < ocmem->config->num_regions; i++) अणु
		काष्ठा ocmem_region *region = &ocmem->regions[i];
		u32 data;

		data = OCMEM_PSGSC_CTL_MACRO0_MODE(region->macro_state[0]) |
			OCMEM_PSGSC_CTL_MACRO1_MODE(region->macro_state[1]) |
			OCMEM_PSGSC_CTL_MACRO2_MODE(region->macro_state[2]) |
			OCMEM_PSGSC_CTL_MACRO3_MODE(region->macro_state[3]);

		ocmem_ग_लिखो(ocmem, OCMEM_REG_PSGSC_CTL(i), data);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ phys_to_offset(काष्ठा ocmem *ocmem,
				    अचिन्हित दीर्घ addr)
अणु
	अगर (addr < ocmem->memory->start || addr >= ocmem->memory->end)
		वापस 0;

	वापस addr - ocmem->memory->start;
पूर्ण

अटल अचिन्हित दीर्घ device_address(काष्ठा ocmem *ocmem,
				    क्रमागत ocmem_client client,
				    अचिन्हित दीर्घ addr)
अणु
	WARN_ON(client != OCMEM_GRAPHICS);

	/* TODO: gpu uses phys_to_offset, but others करो not.. */
	वापस phys_to_offset(ocmem, addr);
पूर्ण

अटल व्योम update_range(काष्ठा ocmem *ocmem, काष्ठा ocmem_buf *buf,
			 क्रमागत ocmem_macro_state mstate, क्रमागत region_mode rmode)
अणु
	अचिन्हित दीर्घ offset = 0;
	पूर्णांक i, j;

	क्रम (i = 0; i < ocmem->config->num_regions; i++) अणु
		काष्ठा ocmem_region *region = &ocmem->regions[i];

		अगर (buf->offset <= offset && offset < buf->offset + buf->len)
			region->mode = rmode;

		क्रम (j = 0; j < region->num_macros; j++) अणु
			अगर (buf->offset <= offset &&
			    offset < buf->offset + buf->len)
				region->macro_state[j] = mstate;

			offset += region->macro_size;
		पूर्ण
	पूर्ण

	update_ocmem(ocmem);
पूर्ण

काष्ठा ocmem *of_get_ocmem(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *devnode;
	काष्ठा ocmem *ocmem;

	devnode = of_parse_phandle(dev->of_node, "sram", 0);
	अगर (!devnode || !devnode->parent) अणु
		dev_err(dev, "Cannot look up sram phandle\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	pdev = of_find_device_by_node(devnode->parent);
	अगर (!pdev) अणु
		dev_err(dev, "Cannot find device node %s\n", devnode->name);
		वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	ocmem = platक्रमm_get_drvdata(pdev);
	अगर (!ocmem) अणु
		dev_err(dev, "Cannot get ocmem\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	वापस ocmem;
पूर्ण
EXPORT_SYMBOL(of_get_ocmem);

काष्ठा ocmem_buf *ocmem_allocate(काष्ठा ocmem *ocmem, क्रमागत ocmem_client client,
				 अचिन्हित दीर्घ size)
अणु
	काष्ठा ocmem_buf *buf;
	पूर्णांक ret;

	/* TODO: add support क्रम other clients... */
	अगर (WARN_ON(client != OCMEM_GRAPHICS))
		वापस ERR_PTR(-ENODEV);

	अगर (size < OCMEM_MIN_ALLOC || !IS_ALIGNED(size, OCMEM_MIN_ALIGN))
		वापस ERR_PTR(-EINVAL);

	अगर (test_and_set_bit_lock(BIT(client), &ocmem->active_allocations))
		वापस ERR_PTR(-EBUSY);

	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	buf->offset = 0;
	buf->addr = device_address(ocmem, client, buf->offset);
	buf->len = size;

	update_range(ocmem, buf, CORE_ON, WIDE_MODE);

	अगर (qcom_scm_ocmem_lock_available()) अणु
		ret = qcom_scm_ocmem_lock(QCOM_SCM_OCMEM_GRAPHICS_ID,
					  buf->offset, buf->len, WIDE_MODE);
		अगर (ret) अणु
			dev_err(ocmem->dev, "could not lock: %d\n", ret);
			ret = -EINVAL;
			जाओ err_kमुक्त;
		पूर्ण
	पूर्ण अन्यथा अणु
		ocmem_ग_लिखो(ocmem, OCMEM_REG_GFX_MPU_START, buf->offset);
		ocmem_ग_लिखो(ocmem, OCMEM_REG_GFX_MPU_END,
			    buf->offset + buf->len);
	पूर्ण

	dev_dbg(ocmem->dev, "using %ldK of OCMEM at 0x%08lx for client %d\n",
		size / 1024, buf->addr, client);

	वापस buf;

err_kमुक्त:
	kमुक्त(buf);
err_unlock:
	clear_bit_unlock(BIT(client), &ocmem->active_allocations);

	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(ocmem_allocate);

व्योम ocmem_मुक्त(काष्ठा ocmem *ocmem, क्रमागत ocmem_client client,
		काष्ठा ocmem_buf *buf)
अणु
	/* TODO: add support क्रम other clients... */
	अगर (WARN_ON(client != OCMEM_GRAPHICS))
		वापस;

	update_range(ocmem, buf, CLK_OFF, MODE_DEFAULT);

	अगर (qcom_scm_ocmem_lock_available()) अणु
		पूर्णांक ret;

		ret = qcom_scm_ocmem_unlock(QCOM_SCM_OCMEM_GRAPHICS_ID,
					    buf->offset, buf->len);
		अगर (ret)
			dev_err(ocmem->dev, "could not unlock: %d\n", ret);
	पूर्ण अन्यथा अणु
		ocmem_ग_लिखो(ocmem, OCMEM_REG_GFX_MPU_START, 0x0);
		ocmem_ग_लिखो(ocmem, OCMEM_REG_GFX_MPU_END, 0x0);
	पूर्ण

	kमुक्त(buf);

	clear_bit_unlock(BIT(client), &ocmem->active_allocations);
पूर्ण
EXPORT_SYMBOL(ocmem_मुक्त);

अटल पूर्णांक ocmem_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	अचिन्हित दीर्घ reg, region_size;
	पूर्णांक i, j, ret, num_banks;
	काष्ठा resource *res;
	काष्ठा ocmem *ocmem;

	अगर (!qcom_scm_is_available())
		वापस -EPROBE_DEFER;

	ocmem = devm_kzalloc(dev, माप(*ocmem), GFP_KERNEL);
	अगर (!ocmem)
		वापस -ENOMEM;

	ocmem->dev = dev;
	ocmem->config = device_get_match_data(dev);

	ret = devm_clk_bulk_get(dev, ARRAY_SIZE(ocmem_clks), ocmem_clks);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Unable to get clocks\n");

		वापस ret;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "ctrl");
	ocmem->mmio = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ocmem->mmio)) अणु
		dev_err(&pdev->dev, "Failed to ioremap ocmem_ctrl resource\n");
		वापस PTR_ERR(ocmem->mmio);
	पूर्ण

	ocmem->memory = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						     "mem");
	अगर (!ocmem->memory) अणु
		dev_err(dev, "Could not get mem region\n");
		वापस -ENXIO;
	पूर्ण

	/* The core घड़ी is synchronous with graphics */
	WARN_ON(clk_set_rate(ocmem_clks[OCMEM_CLK_CORE_IDX].clk, 1000) < 0);

	ret = clk_bulk_prepare_enable(ARRAY_SIZE(ocmem_clks), ocmem_clks);
	अगर (ret) अणु
		dev_info(ocmem->dev, "Failed to enable clocks\n");
		वापस ret;
	पूर्ण

	अगर (qcom_scm_restore_sec_cfg_available()) अणु
		dev_dbg(dev, "configuring scm\n");
		ret = qcom_scm_restore_sec_cfg(QCOM_SCM_OCMEM_DEV_ID, 0);
		अगर (ret) अणु
			dev_err(dev, "Could not enable secure configuration\n");
			जाओ err_clk_disable;
		पूर्ण
	पूर्ण

	reg = ocmem_पढ़ो(ocmem, OCMEM_REG_HW_PROखाता);
	ocmem->num_ports = OCMEM_HW_PROखाता_NUM_PORTS(reg);
	ocmem->num_macros = OCMEM_HW_PROखाता_NUM_MACROS(reg);
	ocmem->पूर्णांकerleaved = !!(reg & OCMEM_HW_PROखाता_INTERLEAVING);

	num_banks = ocmem->num_ports / 2;
	region_size = ocmem->config->macro_size * num_banks;

	dev_info(dev, "%u ports, %u regions, %u macros, %sinterleaved\n",
		 ocmem->num_ports, ocmem->config->num_regions,
		 ocmem->num_macros, ocmem->पूर्णांकerleaved ? "" : "not ");

	ocmem->regions = devm_kसुस्मृति(dev, ocmem->config->num_regions,
				      माप(काष्ठा ocmem_region), GFP_KERNEL);
	अगर (!ocmem->regions) अणु
		ret = -ENOMEM;
		जाओ err_clk_disable;
	पूर्ण

	क्रम (i = 0; i < ocmem->config->num_regions; i++) अणु
		काष्ठा ocmem_region *region = &ocmem->regions[i];

		अगर (WARN_ON(num_banks > ARRAY_SIZE(region->macro_state))) अणु
			ret = -EINVAL;
			जाओ err_clk_disable;
		पूर्ण

		region->mode = MODE_DEFAULT;
		region->num_macros = num_banks;

		अगर (i == (ocmem->config->num_regions - 1) &&
		    reg & OCMEM_HW_PROखाता_LAST_REGN_HALFSIZE) अणु
			region->macro_size = ocmem->config->macro_size / 2;
			region->region_size = region_size / 2;
		पूर्ण अन्यथा अणु
			region->macro_size = ocmem->config->macro_size;
			region->region_size = region_size;
		पूर्ण

		क्रम (j = 0; j < ARRAY_SIZE(region->macro_state); j++)
			region->macro_state[j] = CLK_OFF;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ocmem);

	वापस 0;

err_clk_disable:
	clk_bulk_disable_unprepare(ARRAY_SIZE(ocmem_clks), ocmem_clks);
	वापस ret;
पूर्ण

अटल पूर्णांक ocmem_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	clk_bulk_disable_unprepare(ARRAY_SIZE(ocmem_clks), ocmem_clks);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ocmem_config ocmem_8974_config = अणु
	.num_regions = 3,
	.macro_size = SZ_128K,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ocmem_of_match[] = अणु
	अणु .compatible = "qcom,msm8974-ocmem", .data = &ocmem_8974_config पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, ocmem_of_match);

अटल काष्ठा platक्रमm_driver ocmem_driver = अणु
	.probe = ocmem_dev_probe,
	.हटाओ = ocmem_dev_हटाओ,
	.driver = अणु
		.name = "ocmem",
		.of_match_table = ocmem_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ocmem_driver);

MODULE_DESCRIPTION("On Chip Memory (OCMEM) allocator for some Snapdragon SoCs");
MODULE_LICENSE("GPL v2");
