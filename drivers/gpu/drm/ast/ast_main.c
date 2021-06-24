<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */
/*
 * Authors: Dave Airlie <airlied@redhat.com>
 */

#समावेश <linux/pci.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_gem_vram_helper.h>
#समावेश <drm/drm_managed.h>

#समावेश "ast_drv.h"

व्योम ast_set_index_reg_mask(काष्ठा ast_निजी *ast,
			    uपूर्णांक32_t base, uपूर्णांक8_t index,
			    uपूर्णांक8_t mask, uपूर्णांक8_t val)
अणु
	u8 पंचांगp;
	ast_io_ग_लिखो8(ast, base, index);
	पंचांगp = (ast_io_पढ़ो8(ast, base + 1) & mask) | val;
	ast_set_index_reg(ast, base, index, पंचांगp);
पूर्ण

uपूर्णांक8_t ast_get_index_reg(काष्ठा ast_निजी *ast,
			  uपूर्णांक32_t base, uपूर्णांक8_t index)
अणु
	uपूर्णांक8_t ret;
	ast_io_ग_लिखो8(ast, base, index);
	ret = ast_io_पढ़ो8(ast, base + 1);
	वापस ret;
पूर्ण

uपूर्णांक8_t ast_get_index_reg_mask(काष्ठा ast_निजी *ast,
			       uपूर्णांक32_t base, uपूर्णांक8_t index, uपूर्णांक8_t mask)
अणु
	uपूर्णांक8_t ret;
	ast_io_ग_लिखो8(ast, base, index);
	ret = ast_io_पढ़ो8(ast, base + 1) & mask;
	वापस ret;
पूर्ण

अटल व्योम ast_detect_config_mode(काष्ठा drm_device *dev, u32 *scu_rev)
अणु
	काष्ठा device_node *np = dev->dev->of_node;
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	uपूर्णांक32_t data, jregd0, jregd1;

	/* Defaults */
	ast->config_mode = ast_use_शेषs;
	*scu_rev = 0xffffffff;

	/* Check अगर we have device-tree properties */
	अगर (np && !of_property_पढ़ो_u32(np, "aspeed,scu-revision-id",
					scu_rev)) अणु
		/* We करो, disable P2A access */
		ast->config_mode = ast_use_dt;
		drm_info(dev, "Using device-tree for configuration\n");
		वापस;
	पूर्ण

	/* Not all families have a P2A bridge */
	अगर (pdev->device != PCI_CHIP_AST2000)
		वापस;

	/*
	 * The BMC will set SCU 0x40 D[12] to 1 अगर the P2 bridge
	 * is disabled. We क्रमce using P2A अगर VGA only mode bit
	 * is set D[7]
	 */
	jregd0 = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd0, 0xff);
	jregd1 = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd1, 0xff);
	अगर (!(jregd0 & 0x80) || !(jregd1 & 0x10)) अणु
		/* Double check it's actually working */
		data = ast_पढ़ो32(ast, 0xf004);
		अगर (data != 0xFFFFFFFF) अणु
			/* P2A works, grab silicon revision */
			ast->config_mode = ast_use_p2a;

			drm_info(dev, "Using P2A bridge for configuration\n");

			/* Read SCU7c (silicon revision रेजिस्टर) */
			ast_ग_लिखो32(ast, 0xf004, 0x1e6e0000);
			ast_ग_लिखो32(ast, 0xf000, 0x1);
			*scu_rev = ast_पढ़ो32(ast, 0x1207c);
			वापस;
		पूर्ण
	पूर्ण

	/* We have a P2A bridge but it's disabled */
	drm_info(dev, "P2A bridge disabled, using default configuration\n");
पूर्ण

अटल पूर्णांक ast_detect_chip(काष्ठा drm_device *dev, bool *need_post)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	uपूर्णांक32_t jreg, scu_rev;

	/*
	 * If VGA isn't enabled, we need to enable now or subsequent
	 * access to the scratch रेजिस्टरs will fail. We also inक्रमm
	 * our caller that it needs to POST the chip
	 * (Assumption: VGA not enabled -> need to POST)
	 */
	अगर (!ast_is_vga_enabled(dev)) अणु
		ast_enable_vga(dev);
		drm_info(dev, "VGA not enabled on entry, requesting chip POST\n");
		*need_post = true;
	पूर्ण अन्यथा
		*need_post = false;


	/* Enable extended रेजिस्टर access */
	ast_खोलो_key(ast);
	ast_enable_mmio(dev);

	/* Find out whether P2A works or whether to use device-tree */
	ast_detect_config_mode(dev, &scu_rev);

	/* Identअगरy chipset */
	अगर (pdev->revision >= 0x50) अणु
		ast->chip = AST2600;
		drm_info(dev, "AST 2600 detected\n");
	पूर्ण अन्यथा अगर (pdev->revision >= 0x40) अणु
		ast->chip = AST2500;
		drm_info(dev, "AST 2500 detected\n");
	पूर्ण अन्यथा अगर (pdev->revision >= 0x30) अणु
		ast->chip = AST2400;
		drm_info(dev, "AST 2400 detected\n");
	पूर्ण अन्यथा अगर (pdev->revision >= 0x20) अणु
		ast->chip = AST2300;
		drm_info(dev, "AST 2300 detected\n");
	पूर्ण अन्यथा अगर (pdev->revision >= 0x10) अणु
		चयन (scu_rev & 0x0300) अणु
		हाल 0x0200:
			ast->chip = AST1100;
			drm_info(dev, "AST 1100 detected\n");
			अवरोध;
		हाल 0x0100:
			ast->chip = AST2200;
			drm_info(dev, "AST 2200 detected\n");
			अवरोध;
		हाल 0x0000:
			ast->chip = AST2150;
			drm_info(dev, "AST 2150 detected\n");
			अवरोध;
		शेष:
			ast->chip = AST2100;
			drm_info(dev, "AST 2100 detected\n");
			अवरोध;
		पूर्ण
		ast->vga2_clone = false;
	पूर्ण अन्यथा अणु
		ast->chip = AST2000;
		drm_info(dev, "AST 2000 detected\n");
	पूर्ण

	/* Check अगर we support wide screen */
	चयन (ast->chip) अणु
	हाल AST2000:
		ast->support_wide_screen = false;
		अवरोध;
	शेष:
		jreg = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd0, 0xff);
		अगर (!(jreg & 0x80))
			ast->support_wide_screen = true;
		अन्यथा अगर (jreg & 0x01)
			ast->support_wide_screen = true;
		अन्यथा अणु
			ast->support_wide_screen = false;
			अगर (ast->chip == AST2300 &&
			    (scu_rev & 0x300) == 0x0) /* ast1300 */
				ast->support_wide_screen = true;
			अगर (ast->chip == AST2400 &&
			    (scu_rev & 0x300) == 0x100) /* ast1400 */
				ast->support_wide_screen = true;
			अगर (ast->chip == AST2500 &&
			    scu_rev == 0x100)           /* ast2510 */
				ast->support_wide_screen = true;
		पूर्ण
		अवरोध;
	पूर्ण

	/* Check 3rd Tx option (digital output afaik) */
	ast->tx_chip_type = AST_TX_NONE;

	/*
	 * VGACRA3 Enhanced Color Mode Register, check अगर DVO is alपढ़ोy
	 * enabled, in that हाल, assume we have a SIL164 TMDS transmitter
	 *
	 * Don't make that assumption if we the chip wasn't enabled and
	 * is at घातer-on reset, otherwise we'll incorrectly "detect" a
	 * SIL164 when there is none.
	 */
	अगर (!*need_post) अणु
		jreg = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xa3, 0xff);
		अगर (jreg & 0x80)
			ast->tx_chip_type = AST_TX_SIL164;
	पूर्ण

	अगर ((ast->chip == AST2300) || (ast->chip == AST2400)) अणु
		/*
		 * On AST2300 and 2400, look the configuration set by the SoC in
		 * the SOC scratch रेजिस्टर #1 bits 11:8 (पूर्णांकerestingly marked
		 * as "reserved" in the spec)
		 */
		jreg = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd1, 0xff);
		चयन (jreg) अणु
		हाल 0x04:
			ast->tx_chip_type = AST_TX_SIL164;
			अवरोध;
		हाल 0x08:
			ast->dp501_fw_addr = drmm_kzalloc(dev, 32*1024, GFP_KERNEL);
			अगर (ast->dp501_fw_addr) अणु
				/* backup firmware */
				अगर (ast_backup_fw(dev, ast->dp501_fw_addr, 32*1024)) अणु
					drmm_kमुक्त(dev, ast->dp501_fw_addr);
					ast->dp501_fw_addr = शून्य;
				पूर्ण
			पूर्ण
			fallthrough;
		हाल 0x0c:
			ast->tx_chip_type = AST_TX_DP501;
		पूर्ण
	पूर्ण

	/* Prपूर्णांक stuff क्रम diagnostic purposes */
	चयन(ast->tx_chip_type) अणु
	हाल AST_TX_SIL164:
		drm_info(dev, "Using Sil164 TMDS transmitter\n");
		अवरोध;
	हाल AST_TX_DP501:
		drm_info(dev, "Using DP501 DisplayPort transmitter\n");
		अवरोध;
	शेष:
		drm_info(dev, "Analog VGA only\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ast_get_dram_info(काष्ठा drm_device *dev)
अणु
	काष्ठा device_node *np = dev->dev->of_node;
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	uपूर्णांक32_t mcr_cfg, mcr_scu_mpll, mcr_scu_strap;
	uपूर्णांक32_t dक्रमागत, num, भाग, ref_pll, dsel;

	चयन (ast->config_mode) अणु
	हाल ast_use_dt:
		/*
		 * If some properties are missing, use reasonable
		 * शेषs क्रम AST2400
		 */
		अगर (of_property_पढ़ो_u32(np, "aspeed,mcr-configuration",
					 &mcr_cfg))
			mcr_cfg = 0x00000577;
		अगर (of_property_पढ़ो_u32(np, "aspeed,mcr-scu-mpll",
					 &mcr_scu_mpll))
			mcr_scu_mpll = 0x000050C0;
		अगर (of_property_पढ़ो_u32(np, "aspeed,mcr-scu-strap",
					 &mcr_scu_strap))
			mcr_scu_strap = 0;
		अवरोध;
	हाल ast_use_p2a:
		ast_ग_लिखो32(ast, 0xf004, 0x1e6e0000);
		ast_ग_लिखो32(ast, 0xf000, 0x1);
		mcr_cfg = ast_पढ़ो32(ast, 0x10004);
		mcr_scu_mpll = ast_पढ़ो32(ast, 0x10120);
		mcr_scu_strap = ast_पढ़ो32(ast, 0x10170);
		अवरोध;
	हाल ast_use_शेषs:
	शेष:
		ast->dram_bus_width = 16;
		ast->dram_type = AST_DRAM_1Gx16;
		अगर (ast->chip == AST2500)
			ast->mclk = 800;
		अन्यथा
			ast->mclk = 396;
		वापस 0;
	पूर्ण

	अगर (mcr_cfg & 0x40)
		ast->dram_bus_width = 16;
	अन्यथा
		ast->dram_bus_width = 32;

	अगर (ast->chip == AST2500) अणु
		चयन (mcr_cfg & 0x03) अणु
		हाल 0:
			ast->dram_type = AST_DRAM_1Gx16;
			अवरोध;
		शेष:
		हाल 1:
			ast->dram_type = AST_DRAM_2Gx16;
			अवरोध;
		हाल 2:
			ast->dram_type = AST_DRAM_4Gx16;
			अवरोध;
		हाल 3:
			ast->dram_type = AST_DRAM_8Gx16;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (ast->chip == AST2300 || ast->chip == AST2400) अणु
		चयन (mcr_cfg & 0x03) अणु
		हाल 0:
			ast->dram_type = AST_DRAM_512Mx16;
			अवरोध;
		शेष:
		हाल 1:
			ast->dram_type = AST_DRAM_1Gx16;
			अवरोध;
		हाल 2:
			ast->dram_type = AST_DRAM_2Gx16;
			अवरोध;
		हाल 3:
			ast->dram_type = AST_DRAM_4Gx16;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (mcr_cfg & 0x0c) अणु
		हाल 0:
		हाल 4:
			ast->dram_type = AST_DRAM_512Mx16;
			अवरोध;
		हाल 8:
			अगर (mcr_cfg & 0x40)
				ast->dram_type = AST_DRAM_1Gx16;
			अन्यथा
				ast->dram_type = AST_DRAM_512Mx32;
			अवरोध;
		हाल 0xc:
			ast->dram_type = AST_DRAM_1Gx32;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (mcr_scu_strap & 0x2000)
		ref_pll = 14318;
	अन्यथा
		ref_pll = 12000;

	dक्रमागत = mcr_scu_mpll & 0x1f;
	num = (mcr_scu_mpll & 0x3fe0) >> 5;
	dsel = (mcr_scu_mpll & 0xc000) >> 14;
	चयन (dsel) अणु
	हाल 3:
		भाग = 0x4;
		अवरोध;
	हाल 2:
	हाल 1:
		भाग = 0x2;
		अवरोध;
	शेष:
		भाग = 0x1;
		अवरोध;
	पूर्ण
	ast->mclk = ref_pll * (num + 2) / ((dक्रमागत + 2) * (भाग * 1000));
	वापस 0;
पूर्ण

/*
 * Run this function as part of the HW device cleanup; not
 * when the DRM device माला_लो released.
 */
अटल व्योम ast_device_release(व्योम *data)
अणु
	काष्ठा ast_निजी *ast = data;

	/* enable standard VGA decode */
	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa1, 0x04);
पूर्ण

काष्ठा ast_निजी *ast_device_create(स्थिर काष्ठा drm_driver *drv,
				      काष्ठा pci_dev *pdev,
				      अचिन्हित दीर्घ flags)
अणु
	काष्ठा drm_device *dev;
	काष्ठा ast_निजी *ast;
	bool need_post;
	पूर्णांक ret = 0;

	ast = devm_drm_dev_alloc(&pdev->dev, drv, काष्ठा ast_निजी, base);
	अगर (IS_ERR(ast))
		वापस ast;
	dev = &ast->base;

	pci_set_drvdata(pdev, dev);

	ast->regs = pci_iomap(pdev, 1, 0);
	अगर (!ast->regs)
		वापस ERR_PTR(-EIO);

	/*
	 * If we करोn't have IO space at all, use MMIO now and
	 * assume the chip has MMIO enabled by शेष (rev 0x20
	 * and higher).
	 */
	अगर (!(pci_resource_flags(pdev, 2) & IORESOURCE_IO)) अणु
		drm_info(dev, "platform has no IO space, trying MMIO\n");
		ast->ioregs = ast->regs + AST_IO_MM_OFFSET;
	पूर्ण

	/* "map" IO regs अगर the above hasn't करोne so alपढ़ोy */
	अगर (!ast->ioregs) अणु
		ast->ioregs = pci_iomap(pdev, 2, 0);
		अगर (!ast->ioregs)
			वापस ERR_PTR(-EIO);
	पूर्ण

	ast_detect_chip(dev, &need_post);

	ret = ast_get_dram_info(dev);
	अगर (ret)
		वापस ERR_PTR(ret);

	drm_info(dev, "dram MCLK=%u Mhz type=%d bus_width=%d\n",
		 ast->mclk, ast->dram_type, ast->dram_bus_width);

	अगर (need_post)
		ast_post_gpu(dev);

	ret = ast_mm_init(ast);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = ast_mode_config_init(ast);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = devm_add_action_or_reset(dev->dev, ast_device_release, ast);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस ast;
पूर्ण
