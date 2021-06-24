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

#समावेश <linux/pci.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>

#समावेश "atom.h"
#समावेश "r100d.h"
#समावेश "r420_reg_safe.h"
#समावेश "r420d.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_reg.h"

व्योम r420_pm_init_profile(काष्ठा radeon_device *rdev)
अणु
	/* शेष */
	rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_ps_idx = rdev->pm.शेष_घातer_state_index;
	rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
	rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_DEFAULT_IDX].dpms_on_cm_idx = 0;
	/* low sh */
	rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_ps_idx = 0;
	rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_ps_idx = 0;
	rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_LOW_SH_IDX].dpms_on_cm_idx = 0;
	/* mid sh */
	rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_ps_idx = 0;
	rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_ps_idx = 1;
	rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_MID_SH_IDX].dpms_on_cm_idx = 0;
	/* high sh */
	rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_ps_idx = 0;
	rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
	rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_HIGH_SH_IDX].dpms_on_cm_idx = 0;
	/* low mh */
	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_ps_idx = 0;
	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_LOW_MH_IDX].dpms_on_cm_idx = 0;
	/* mid mh */
	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_ps_idx = 0;
	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_MID_MH_IDX].dpms_on_cm_idx = 0;
	/* high mh */
	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_ps_idx = 0;
	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_ps_idx = rdev->pm.शेष_घातer_state_index;
	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_off_cm_idx = 0;
	rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_cm_idx = 0;
पूर्ण

अटल व्योम r420_set_reg_safe(काष्ठा radeon_device *rdev)
अणु
	rdev->config.r300.reg_safe_bm = r420_reg_safe_bm;
	rdev->config.r300.reg_safe_bm_size = ARRAY_SIZE(r420_reg_safe_bm);
पूर्ण

व्योम r420_pipes_init(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित पंचांगp;
	अचिन्हित gb_pipe_select;
	अचिन्हित num_pipes;

	/* GA_ENHANCE workaround TCL deadlock issue */
	WREG32(R300_GA_ENHANCE, R300_GA_DEADLOCK_CNTL | R300_GA_FASTSYNC_CNTL |
	       (1 << 2) | (1 << 3));
	/* add idle रुको as per मुक्तdesktop.org bug 24041 */
	अगर (r100_gui_रुको_क्रम_idle(rdev)) अणु
		pr_warn("Failed to wait GUI idle while programming pipes. Bad things might happen.\n");
	पूर्ण
	/* get max number of pipes */
	gb_pipe_select = RREG32(R400_GB_PIPE_SELECT);
	num_pipes = ((gb_pipe_select >> 12) & 3) + 1;

	/* SE chips have 1 pipe */
	अगर ((rdev->pdev->device == 0x5e4c) ||
	    (rdev->pdev->device == 0x5e4f))
		num_pipes = 1;

	rdev->num_gb_pipes = num_pipes;
	पंचांगp = 0;
	चयन (num_pipes) अणु
	शेष:
		/* क्रमce to 1 pipe */
		num_pipes = 1;
		fallthrough;
	हाल 1:
		पंचांगp = (0 << 1);
		अवरोध;
	हाल 2:
		पंचांगp = (3 << 1);
		अवरोध;
	हाल 3:
		पंचांगp = (6 << 1);
		अवरोध;
	हाल 4:
		पंचांगp = (7 << 1);
		अवरोध;
	पूर्ण
	WREG32(R500_SU_REG_DEST, (1 << num_pipes) - 1);
	/* Sub pixel 1/12 so we can have 4K rendering according to करोc */
	पंचांगp |= R300_TILE_SIZE_16 | R300_ENABLE_TILING;
	WREG32(R300_GB_TILE_CONFIG, पंचांगp);
	अगर (r100_gui_रुको_क्रम_idle(rdev)) अणु
		pr_warn("Failed to wait GUI idle while programming pipes. Bad things might happen.\n");
	पूर्ण

	पंचांगp = RREG32(R300_DST_PIPE_CONFIG);
	WREG32(R300_DST_PIPE_CONFIG, पंचांगp | R300_PIPE_AUTO_CONFIG);

	WREG32(R300_RB2D_DSTCACHE_MODE,
	       RREG32(R300_RB2D_DSTCACHE_MODE) |
	       R300_DC_AUTOFLUSH_ENABLE |
	       R300_DC_DC_DISABLE_IGNORE_PE);

	अगर (r100_gui_रुको_क्रम_idle(rdev)) अणु
		pr_warn("Failed to wait GUI idle while programming pipes. Bad things might happen.\n");
	पूर्ण

	अगर (rdev->family == CHIP_RV530) अणु
		पंचांगp = RREG32(RV530_GB_PIPE_SELECT2);
		अगर ((पंचांगp & 3) == 3)
			rdev->num_z_pipes = 2;
		अन्यथा
			rdev->num_z_pipes = 1;
	पूर्ण अन्यथा
		rdev->num_z_pipes = 1;

	DRM_INFO("radeon: %d quad pipes, %d z pipes initialized.\n",
		 rdev->num_gb_pipes, rdev->num_z_pipes);
पूर्ण

u32 r420_mc_rreg(काष्ठा radeon_device *rdev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&rdev->mc_idx_lock, flags);
	WREG32(R_0001F8_MC_IND_INDEX, S_0001F8_MC_IND_ADDR(reg));
	r = RREG32(R_0001FC_MC_IND_DATA);
	spin_unlock_irqrestore(&rdev->mc_idx_lock, flags);
	वापस r;
पूर्ण

व्योम r420_mc_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->mc_idx_lock, flags);
	WREG32(R_0001F8_MC_IND_INDEX, S_0001F8_MC_IND_ADDR(reg) |
		S_0001F8_MC_IND_WR_EN(1));
	WREG32(R_0001FC_MC_IND_DATA, v);
	spin_unlock_irqrestore(&rdev->mc_idx_lock, flags);
पूर्ण

अटल व्योम r420_debugfs(काष्ठा radeon_device *rdev)
अणु
	r100_debugfs_rbbm_init(rdev);
	r420_debugfs_pipes_info_init(rdev);
पूर्ण

अटल व्योम r420_घड़ी_resume(काष्ठा radeon_device *rdev)
अणु
	u32 sclk_cntl;

	अगर (radeon_dynclks != -1 && radeon_dynclks)
		radeon_atom_set_घड़ी_gating(rdev, 1);
	sclk_cntl = RREG32_PLL(R_00000D_SCLK_CNTL);
	sclk_cntl |= S_00000D_FORCE_CP(1) | S_00000D_FORCE_VIP(1);
	अगर (rdev->family == CHIP_R420)
		sclk_cntl |= S_00000D_FORCE_PX(1) | S_00000D_FORCE_TX(1);
	WREG32_PLL(R_00000D_SCLK_CNTL, sclk_cntl);
पूर्ण

अटल व्योम r420_cp_errata_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];

	/* RV410 and R420 can lock up अगर CP DMA to host memory happens
	 * जबतक the 2D engine is busy.
	 *
	 * The proper workaround is to queue a RESYNC at the beginning
	 * of the CP init, apparently.
	 */
	radeon_scratch_get(rdev, &rdev->config.r300.resync_scratch);
	r = radeon_ring_lock(rdev, ring, 8);
	WARN_ON(r);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_CP_RESYNC_ADDR, 1));
	radeon_ring_ग_लिखो(ring, rdev->config.r300.resync_scratch);
	radeon_ring_ग_लिखो(ring, 0xDEADBEEF);
	radeon_ring_unlock_commit(rdev, ring, false);
पूर्ण

अटल व्योम r420_cp_errata_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;
	काष्ठा radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];

	/* Catch the RESYNC we dispatched all the way back,
	 * at the very beginning of the CP init.
	 */
	r = radeon_ring_lock(rdev, ring, 8);
	WARN_ON(r);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_RB3D_DSTCACHE_CTLSTAT, 0));
	radeon_ring_ग_लिखो(ring, R300_RB3D_DC_FINISH);
	radeon_ring_unlock_commit(rdev, ring, false);
	radeon_scratch_मुक्त(rdev, rdev->config.r300.resync_scratch);
पूर्ण

अटल पूर्णांक r420_startup(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* set common regs */
	r100_set_common_regs(rdev);
	/* program mc */
	r300_mc_program(rdev);
	/* Resume घड़ी */
	r420_घड़ी_resume(rdev);
	/* Initialize GART (initialize after TTM so we can allocate
	 * memory through TTM but finalize after TTM) */
	अगर (rdev->flags & RADEON_IS_PCIE) अणु
		r = rv370_pcie_gart_enable(rdev);
		अगर (r)
			वापस r;
	पूर्ण
	अगर (rdev->flags & RADEON_IS_PCI) अणु
		r = r100_pci_gart_enable(rdev);
		अगर (r)
			वापस r;
	पूर्ण
	r420_pipes_init(rdev);

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

	r100_irq_set(rdev);
	rdev->config.r300.hdp_cntl = RREG32(RADEON_HOST_PATH_CNTL);
	/* 1M ring buffer */
	r = r100_cp_init(rdev, 1024 * 1024);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing CP (%d).\n", r);
		वापस r;
	पूर्ण
	r420_cp_errata_init(rdev);

	r = radeon_ib_pool_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "IB initialization failed (%d).\n", r);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक r420_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Make sur GART are not working */
	अगर (rdev->flags & RADEON_IS_PCIE)
		rv370_pcie_gart_disable(rdev);
	अगर (rdev->flags & RADEON_IS_PCI)
		r100_pci_gart_disable(rdev);
	/* Resume घड़ी beक्रमe करोing reset */
	r420_घड़ी_resume(rdev);
	/* Reset gpu beक्रमe posting otherwise ATOM will enter infinite loop */
	अगर (radeon_asic_reset(rdev)) अणु
		dev_warn(rdev->dev, "GPU reset failed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			RREG32(R_000E40_RBBM_STATUS),
			RREG32(R_0007C0_CP_STAT));
	पूर्ण
	/* check अगर cards are posted or not */
	अगर (rdev->is_atom_bios) अणु
		atom_asic_init(rdev->mode_info.atom_context);
	पूर्ण अन्यथा अणु
		radeon_combios_asic_init(rdev->ddev);
	पूर्ण
	/* Resume घड़ी after posting */
	r420_घड़ी_resume(rdev);
	/* Initialize surface रेजिस्टरs */
	radeon_surface_init(rdev);

	rdev->accel_working = true;
	r = r420_startup(rdev);
	अगर (r) अणु
		rdev->accel_working = false;
	पूर्ण
	वापस r;
पूर्ण

पूर्णांक r420_suspend(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_suspend(rdev);
	r420_cp_errata_fini(rdev);
	r100_cp_disable(rdev);
	radeon_wb_disable(rdev);
	r100_irq_disable(rdev);
	अगर (rdev->flags & RADEON_IS_PCIE)
		rv370_pcie_gart_disable(rdev);
	अगर (rdev->flags & RADEON_IS_PCI)
		r100_pci_gart_disable(rdev);
	वापस 0;
पूर्ण

व्योम r420_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_fini(rdev);
	r100_cp_fini(rdev);
	radeon_wb_fini(rdev);
	radeon_ib_pool_fini(rdev);
	radeon_gem_fini(rdev);
	अगर (rdev->flags & RADEON_IS_PCIE)
		rv370_pcie_gart_fini(rdev);
	अगर (rdev->flags & RADEON_IS_PCI)
		r100_pci_gart_fini(rdev);
	radeon_agp_fini(rdev);
	radeon_irq_kms_fini(rdev);
	radeon_fence_driver_fini(rdev);
	radeon_bo_fini(rdev);
	अगर (rdev->is_atom_bios) अणु
		radeon_atombios_fini(rdev);
	पूर्ण अन्यथा अणु
		radeon_combios_fini(rdev);
	पूर्ण
	kमुक्त(rdev->bios);
	rdev->bios = शून्य;
पूर्ण

पूर्णांक r420_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Initialize scratch रेजिस्टरs */
	radeon_scratch_init(rdev);
	/* Initialize surface रेजिस्टरs */
	radeon_surface_init(rdev);
	/* TODO: disable VGA need to use VGA request */
	/* restore some रेजिस्टर to sane शेषs */
	r100_restore_sanity(rdev);
	/* BIOS*/
	अगर (!radeon_get_bios(rdev)) अणु
		अगर (ASIC_IS_AVIVO(rdev))
			वापस -EINVAL;
	पूर्ण
	अगर (rdev->is_atom_bios) अणु
		r = radeon_atombios_init(rdev);
		अगर (r) अणु
			वापस r;
		पूर्ण
	पूर्ण अन्यथा अणु
		r = radeon_combios_init(rdev);
		अगर (r) अणु
			वापस r;
		पूर्ण
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
	r300_mc_init(rdev);
	r420_debugfs(rdev);
	/* Fence driver */
	r = radeon_fence_driver_init(rdev);
	अगर (r) अणु
		वापस r;
	पूर्ण
	/* Memory manager */
	r = radeon_bo_init(rdev);
	अगर (r) अणु
		वापस r;
	पूर्ण
	अगर (rdev->family == CHIP_R420)
		r100_enable_bm(rdev);

	अगर (rdev->flags & RADEON_IS_PCIE) अणु
		r = rv370_pcie_gart_init(rdev);
		अगर (r)
			वापस r;
	पूर्ण
	अगर (rdev->flags & RADEON_IS_PCI) अणु
		r = r100_pci_gart_init(rdev);
		अगर (r)
			वापस r;
	पूर्ण
	r420_set_reg_safe(rdev);

	/* Initialize घातer management */
	radeon_pm_init(rdev);

	rdev->accel_working = true;
	r = r420_startup(rdev);
	अगर (r) अणु
		/* Somethings want wront with the accel init stop accel */
		dev_err(rdev->dev, "Disabling GPU acceleration\n");
		r100_cp_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		radeon_irq_kms_fini(rdev);
		अगर (rdev->flags & RADEON_IS_PCIE)
			rv370_pcie_gart_fini(rdev);
		अगर (rdev->flags & RADEON_IS_PCI)
			r100_pci_gart_fini(rdev);
		radeon_agp_fini(rdev);
		rdev->accel_working = false;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Debugfs info
 */
#अगर defined(CONFIG_DEBUG_FS)
अटल पूर्णांक r420_debugfs_pipes_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;
	uपूर्णांक32_t पंचांगp;

	पंचांगp = RREG32(R400_GB_PIPE_SELECT);
	seq_म_लिखो(m, "GB_PIPE_SELECT 0x%08x\n", पंचांगp);
	पंचांगp = RREG32(R300_GB_TILE_CONFIG);
	seq_म_लिखो(m, "GB_TILE_CONFIG 0x%08x\n", पंचांगp);
	पंचांगp = RREG32(R300_DST_PIPE_CONFIG);
	seq_म_लिखो(m, "DST_PIPE_CONFIG 0x%08x\n", पंचांगp);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(r420_debugfs_pipes_info);
#पूर्ण_अगर

व्योम r420_debugfs_pipes_info_init(काष्ठा radeon_device *rdev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry *root = rdev->ddev->primary->debugfs_root;

	debugfs_create_file("r420_pipes_info", 0444, root, rdev,
			    &r420_debugfs_pipes_info_fops);
#पूर्ण_अगर
पूर्ण
