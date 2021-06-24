<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
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
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */

#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "atom.h"
#समावेश "r520d.h"

/* This files gather functions specअगरics to: r520,rv530,rv560,rv570,r580 */

पूर्णांक r520_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;
	uपूर्णांक32_t पंचांगp;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		/* पढ़ो MC_STATUS */
		पंचांगp = RREG32_MC(R520_MC_STATUS);
		अगर (पंचांगp & R520_MC_STATUS_IDLE) अणु
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम r520_gpu_init(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित pipe_select_current, gb_pipe_select, पंचांगp;

	rv515_vga_render_disable(rdev);
	/*
	 * DST_PIPE_CONFIG		0x170C
	 * GB_TILE_CONFIG		0x4018
	 * GB_FIFO_SIZE			0x4024
	 * GB_PIPE_SELECT		0x402C
	 * GB_PIPE_SELECT2              0x4124
	 *	Z_PIPE_SHIFT			0
	 *	Z_PIPE_MASK			0x000000003
	 * GB_FIFO_SIZE2                0x4128
	 *	SC_SFIFO_SIZE_SHIFT		0
	 *	SC_SFIFO_SIZE_MASK		0x000000003
	 *	SC_MFIFO_SIZE_SHIFT		2
	 *	SC_MFIFO_SIZE_MASK		0x00000000C
	 *	FG_SFIFO_SIZE_SHIFT		4
	 *	FG_SFIFO_SIZE_MASK		0x000000030
	 *	ZB_MFIFO_SIZE_SHIFT		6
	 *	ZB_MFIFO_SIZE_MASK		0x0000000C0
	 * GA_ENHANCE			0x4274
	 * SU_REG_DEST			0x42C8
	 */
	/* workaround क्रम RV530 */
	अगर (rdev->family == CHIP_RV530) अणु
		WREG32(0x4128, 0xFF);
	पूर्ण
	r420_pipes_init(rdev);
	gb_pipe_select = RREG32(R400_GB_PIPE_SELECT);
	पंचांगp = RREG32(R300_DST_PIPE_CONFIG);
	pipe_select_current = (पंचांगp >> 2) & 3;
	पंचांगp = (1 << pipe_select_current) |
	      (((gb_pipe_select >> 8) & 0xF) << 4);
	WREG32_PLL(0x000D, पंचांगp);
	अगर (r520_mc_रुको_क्रम_idle(rdev)) अणु
		pr_warn("Failed to wait MC idle while programming pipes. Bad things might happen.\n");
	पूर्ण
पूर्ण

अटल व्योम r520_vram_get_type(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t पंचांगp;

	rdev->mc.vram_width = 128;
	rdev->mc.vram_is_ddr = true;
	पंचांगp = RREG32_MC(R520_MC_CNTL0);
	चयन ((पंचांगp & R520_MEM_NUM_CHANNELS_MASK) >> R520_MEM_NUM_CHANNELS_SHIFT) अणु
	हाल 0:
		rdev->mc.vram_width = 32;
		अवरोध;
	हाल 1:
		rdev->mc.vram_width = 64;
		अवरोध;
	हाल 2:
		rdev->mc.vram_width = 128;
		अवरोध;
	हाल 3:
		rdev->mc.vram_width = 256;
		अवरोध;
	शेष:
		rdev->mc.vram_width = 128;
		अवरोध;
	पूर्ण
	अगर (पंचांगp & R520_MC_CHANNEL_SIZE)
		rdev->mc.vram_width *= 2;
पूर्ण

अटल व्योम r520_mc_init(काष्ठा radeon_device *rdev)
अणु

	r520_vram_get_type(rdev);
	r100_vram_init_sizes(rdev);
	radeon_vram_location(rdev, &rdev->mc, 0);
	rdev->mc.gtt_base_align = 0;
	अगर (!(rdev->flags & RADEON_IS_AGP))
		radeon_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);
पूर्ण

अटल व्योम r520_mc_program(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv515_mc_save save;

	/* Stops all mc clients */
	rv515_mc_stop(rdev, &save);

	/* Wait क्रम mc idle */
	अगर (r520_mc_रुको_क्रम_idle(rdev))
		dev_warn(rdev->dev, "Wait MC idle timeout before updating MC.\n");
	/* Write VRAM size in हाल we are limiting it */
	WREG32(R_0000F8_CONFIG_MEMSIZE, rdev->mc.real_vram_size);
	/* Program MC, should be a 32bits limited address space */
	WREG32_MC(R_000004_MC_FB_LOCATION,
			S_000004_MC_FB_START(rdev->mc.vram_start >> 16) |
			S_000004_MC_FB_TOP(rdev->mc.vram_end >> 16));
	WREG32(R_000134_HDP_FB_LOCATION,
		S_000134_HDP_FB_START(rdev->mc.vram_start >> 16));
	अगर (rdev->flags & RADEON_IS_AGP) अणु
		WREG32_MC(R_000005_MC_AGP_LOCATION,
			S_000005_MC_AGP_START(rdev->mc.gtt_start >> 16) |
			S_000005_MC_AGP_TOP(rdev->mc.gtt_end >> 16));
		WREG32_MC(R_000006_AGP_BASE, lower_32_bits(rdev->mc.agp_base));
		WREG32_MC(R_000007_AGP_BASE_2,
			S_000007_AGP_BASE_ADDR_2(upper_32_bits(rdev->mc.agp_base)));
	पूर्ण अन्यथा अणु
		WREG32_MC(R_000005_MC_AGP_LOCATION, 0xFFFFFFFF);
		WREG32_MC(R_000006_AGP_BASE, 0);
		WREG32_MC(R_000007_AGP_BASE_2, 0);
	पूर्ण

	rv515_mc_resume(rdev, &save);
पूर्ण

अटल पूर्णांक r520_startup(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	r520_mc_program(rdev);
	/* Resume घड़ी */
	rv515_घड़ी_startup(rdev);
	/* Initialize GPU configuration (# pipes, ...) */
	r520_gpu_init(rdev);
	/* Initialize GART (initialize after TTM so we can allocate
	 * memory through TTM but finalize after TTM) */
	अगर (rdev->flags & RADEON_IS_PCIE) अणु
		r = rv370_pcie_gart_enable(rdev);
		अगर (r)
			वापस r;
	पूर्ण

	/* allocate wb buffer */
	r = radeon_wb_init(rdev);
	अगर (r)
		वापस r;

	r = radeon_fence_driver_start_ring(rdev, RADEON_RING_TYPE_GFX_INDEX);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		वापस r;
	पूर्ण

	/* Enable IRQ */
	अगर (!rdev->irq.installed) अणु
		r = radeon_irq_kms_init(rdev);
		अगर (r)
			वापस r;
	पूर्ण

	rs600_irq_set(rdev);
	rdev->config.r300.hdp_cntl = RREG32(RADEON_HOST_PATH_CNTL);
	/* 1M ring buffer */
	r = r100_cp_init(rdev, 1024 * 1024);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing CP (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_ib_pool_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "IB initialization failed (%d).\n", r);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक r520_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Make sur GART are not working */
	अगर (rdev->flags & RADEON_IS_PCIE)
		rv370_pcie_gart_disable(rdev);
	/* Resume घड़ी beक्रमe करोing reset */
	rv515_घड़ी_startup(rdev);
	/* Reset gpu beक्रमe posting otherwise ATOM will enter infinite loop */
	अगर (radeon_asic_reset(rdev)) अणु
		dev_warn(rdev->dev, "GPU reset failed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			RREG32(R_000E40_RBBM_STATUS),
			RREG32(R_0007C0_CP_STAT));
	पूर्ण
	/* post */
	atom_asic_init(rdev->mode_info.atom_context);
	/* Resume घड़ी after posting */
	rv515_घड़ी_startup(rdev);
	/* Initialize surface रेजिस्टरs */
	radeon_surface_init(rdev);

	rdev->accel_working = true;
	r = r520_startup(rdev);
	अगर (r) अणु
		rdev->accel_working = false;
	पूर्ण
	वापस r;
पूर्ण

पूर्णांक r520_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Initialize scratch रेजिस्टरs */
	radeon_scratch_init(rdev);
	/* Initialize surface रेजिस्टरs */
	radeon_surface_init(rdev);
	/* restore some रेजिस्टर to sane शेषs */
	r100_restore_sanity(rdev);
	/* TODO: disable VGA need to use VGA request */
	/* BIOS*/
	अगर (!radeon_get_bios(rdev)) अणु
		अगर (ASIC_IS_AVIVO(rdev))
			वापस -EINVAL;
	पूर्ण
	अगर (rdev->is_atom_bios) अणु
		r = radeon_atombios_init(rdev);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अणु
		dev_err(rdev->dev, "Expecting atombios for RV515 GPU\n");
		वापस -EINVAL;
	पूर्ण
	/* Reset gpu beक्रमe posting otherwise ATOM will enter infinite loop */
	अगर (radeon_asic_reset(rdev)) अणु
		dev_warn(rdev->dev,
			"GPU reset failed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			RREG32(R_000E40_RBBM_STATUS),
			RREG32(R_0007C0_CP_STAT));
	पूर्ण
	/* check अगर cards are posted or not */
	अगर (radeon_boot_test_post_card(rdev) == false)
		वापस -EINVAL;

	अगर (!radeon_card_posted(rdev) && rdev->bios) अणु
		DRM_INFO("GPU not posted. posting now...\n");
		atom_asic_init(rdev->mode_info.atom_context);
	पूर्ण
	/* Initialize घड़ीs */
	radeon_get_घड़ी_info(rdev->ddev);
	/* initialize AGP */
	अगर (rdev->flags & RADEON_IS_AGP) अणु
		r = radeon_agp_init(rdev);
		अगर (r) अणु
			radeon_agp_disable(rdev);
		पूर्ण
	पूर्ण
	/* initialize memory controller */
	r520_mc_init(rdev);
	rv515_debugfs(rdev);
	/* Fence driver */
	r = radeon_fence_driver_init(rdev);
	अगर (r)
		वापस r;
	/* Memory manager */
	r = radeon_bo_init(rdev);
	अगर (r)
		वापस r;
	r = rv370_pcie_gart_init(rdev);
	अगर (r)
		वापस r;
	rv515_set_safe_रेजिस्टरs(rdev);

	/* Initialize घातer management */
	radeon_pm_init(rdev);

	rdev->accel_working = true;
	r = r520_startup(rdev);
	अगर (r) अणु
		/* Somethings want wront with the accel init stop accel */
		dev_err(rdev->dev, "Disabling GPU acceleration\n");
		r100_cp_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		radeon_irq_kms_fini(rdev);
		rv370_pcie_gart_fini(rdev);
		radeon_agp_fini(rdev);
		rdev->accel_working = false;
	पूर्ण
	वापस 0;
पूर्ण
