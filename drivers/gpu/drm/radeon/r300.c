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

#समावेश <drm/drm.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/radeon_drm.h>

#समावेश "r100_track.h"
#समावेश "r300_reg_safe.h"
#समावेश "r300d.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_reg.h"
#समावेश "rv350d.h"

/* This files gather functions specअगरics to: r300,r350,rv350,rv370,rv380
 *
 * GPU Errata:
 * - HOST_PATH_CNTL: r300 family seems to dislike ग_लिखो to HOST_PATH_CNTL
 *   using MMIO to flush host path पढ़ो cache, this lead to HARDLOCKUP.
 *   However, scheduling such ग_लिखो to the ring seems harmless, i suspect
 *   the CP पढ़ो collide with the flush somehow, or maybe the MC, hard to
 *   tell. (Jerome Glisse)
 */

/*
 * Indirect रेजिस्टरs accessor
 */
uपूर्णांक32_t rv370_pcie_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t r;

	spin_lock_irqsave(&rdev->pcie_idx_lock, flags);
	WREG32(RADEON_PCIE_INDEX, ((reg) & rdev->pcie_reg_mask));
	r = RREG32(RADEON_PCIE_DATA);
	spin_unlock_irqrestore(&rdev->pcie_idx_lock, flags);
	वापस r;
पूर्ण

व्योम rv370_pcie_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->pcie_idx_lock, flags);
	WREG32(RADEON_PCIE_INDEX, ((reg) & rdev->pcie_reg_mask));
	WREG32(RADEON_PCIE_DATA, (v));
	spin_unlock_irqrestore(&rdev->pcie_idx_lock, flags);
पूर्ण

/*
 * rv370,rv380 PCIE GART
 */
अटल व्योम rv370_debugfs_pcie_gart_info_init(काष्ठा radeon_device *rdev);

व्योम rv370_pcie_gart_tlb_flush(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t पंचांगp;
	पूर्णांक i;

	/* Workaround HW bug करो flush 2 बार */
	क्रम (i = 0; i < 2; i++) अणु
		पंचांगp = RREG32_PCIE(RADEON_PCIE_TX_GART_CNTL);
		WREG32_PCIE(RADEON_PCIE_TX_GART_CNTL, पंचांगp | RADEON_PCIE_TX_GART_INVALIDATE_TLB);
		(व्योम)RREG32_PCIE(RADEON_PCIE_TX_GART_CNTL);
		WREG32_PCIE(RADEON_PCIE_TX_GART_CNTL, पंचांगp);
	पूर्ण
	mb();
पूर्ण

#घोषणा R300_PTE_UNSNOOPED (1 << 0)
#घोषणा R300_PTE_WRITEABLE (1 << 2)
#घोषणा R300_PTE_READABLE  (1 << 3)

uपूर्णांक64_t rv370_pcie_gart_get_page_entry(uपूर्णांक64_t addr, uपूर्णांक32_t flags)
अणु
	addr = (lower_32_bits(addr) >> 8) |
		((upper_32_bits(addr) & 0xff) << 24);
	अगर (flags & RADEON_GART_PAGE_READ)
		addr |= R300_PTE_READABLE;
	अगर (flags & RADEON_GART_PAGE_WRITE)
		addr |= R300_PTE_WRITEABLE;
	अगर (!(flags & RADEON_GART_PAGE_SNOOP))
		addr |= R300_PTE_UNSNOOPED;
	वापस addr;
पूर्ण

व्योम rv370_pcie_gart_set_page(काष्ठा radeon_device *rdev, अचिन्हित i,
			      uपूर्णांक64_t entry)
अणु
	व्योम __iomem *ptr = rdev->gart.ptr;

	/* on x86 we want this to be CPU endian, on घातerpc
	 * on घातerpc without HW swappers, it'll get swapped on way
	 * पूर्णांकo VRAM - so no need क्रम cpu_to_le32 on VRAM tables */
	ग_लिखोl(entry, ((व्योम __iomem *)ptr) + (i * 4));
पूर्ण

पूर्णांक rv370_pcie_gart_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (rdev->gart.robj) अणु
		WARN(1, "RV370 PCIE GART already initialized\n");
		वापस 0;
	पूर्ण
	/* Initialize common gart काष्ठाure */
	r = radeon_gart_init(rdev);
	अगर (r)
		वापस r;
	rv370_debugfs_pcie_gart_info_init(rdev);

	rdev->gart.table_size = rdev->gart.num_gpu_pages * 4;
	rdev->asic->gart.tlb_flush = &rv370_pcie_gart_tlb_flush;
	rdev->asic->gart.get_page_entry = &rv370_pcie_gart_get_page_entry;
	rdev->asic->gart.set_page = &rv370_pcie_gart_set_page;
	वापस radeon_gart_table_vram_alloc(rdev);
पूर्ण

पूर्णांक rv370_pcie_gart_enable(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t table_addr;
	uपूर्णांक32_t पंचांगp;
	पूर्णांक r;

	अगर (rdev->gart.robj == शून्य) अणु
		dev_err(rdev->dev, "No VRAM object for PCIE GART.\n");
		वापस -EINVAL;
	पूर्ण
	r = radeon_gart_table_vram_pin(rdev);
	अगर (r)
		वापस r;
	/* discard memory request outside of configured range */
	पंचांगp = RADEON_PCIE_TX_GART_UNMAPPED_ACCESS_DISCARD;
	WREG32_PCIE(RADEON_PCIE_TX_GART_CNTL, पंचांगp);
	WREG32_PCIE(RADEON_PCIE_TX_GART_START_LO, rdev->mc.gtt_start);
	पंचांगp = rdev->mc.gtt_end & ~RADEON_GPU_PAGE_MASK;
	WREG32_PCIE(RADEON_PCIE_TX_GART_END_LO, पंचांगp);
	WREG32_PCIE(RADEON_PCIE_TX_GART_START_HI, 0);
	WREG32_PCIE(RADEON_PCIE_TX_GART_END_HI, 0);
	table_addr = rdev->gart.table_addr;
	WREG32_PCIE(RADEON_PCIE_TX_GART_BASE, table_addr);
	/* FIXME: setup शेष page */
	WREG32_PCIE(RADEON_PCIE_TX_DISCARD_RD_ADDR_LO, rdev->mc.vram_start);
	WREG32_PCIE(RADEON_PCIE_TX_DISCARD_RD_ADDR_HI, 0);
	/* Clear error */
	WREG32_PCIE(RADEON_PCIE_TX_GART_ERROR, 0);
	पंचांगp = RREG32_PCIE(RADEON_PCIE_TX_GART_CNTL);
	पंचांगp |= RADEON_PCIE_TX_GART_EN;
	पंचांगp |= RADEON_PCIE_TX_GART_UNMAPPED_ACCESS_DISCARD;
	WREG32_PCIE(RADEON_PCIE_TX_GART_CNTL, पंचांगp);
	rv370_pcie_gart_tlb_flush(rdev);
	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (अचिन्हित)(rdev->mc.gtt_size >> 20),
		 (अचिन्हित दीर्घ दीर्घ)table_addr);
	rdev->gart.पढ़ोy = true;
	वापस 0;
पूर्ण

व्योम rv370_pcie_gart_disable(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	WREG32_PCIE(RADEON_PCIE_TX_GART_START_LO, 0);
	WREG32_PCIE(RADEON_PCIE_TX_GART_END_LO, 0);
	WREG32_PCIE(RADEON_PCIE_TX_GART_START_HI, 0);
	WREG32_PCIE(RADEON_PCIE_TX_GART_END_HI, 0);
	पंचांगp = RREG32_PCIE(RADEON_PCIE_TX_GART_CNTL);
	पंचांगp |= RADEON_PCIE_TX_GART_UNMAPPED_ACCESS_DISCARD;
	WREG32_PCIE(RADEON_PCIE_TX_GART_CNTL, पंचांगp & ~RADEON_PCIE_TX_GART_EN);
	radeon_gart_table_vram_unpin(rdev);
पूर्ण

व्योम rv370_pcie_gart_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_gart_fini(rdev);
	rv370_pcie_gart_disable(rdev);
	radeon_gart_table_vram_मुक्त(rdev);
पूर्ण

व्योम r300_fence_ring_emit(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_fence *fence)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[fence->ring];

	/* Who ever call radeon_fence_emit should call ring_lock and ask
	 * क्रम enough space (today caller are ib schedule and buffer move) */
	/* Write SC रेजिस्टर so SC & US निश्चित idle */
	radeon_ring_ग_लिखो(ring, PACKET0(R300_RE_SCISSORS_TL, 0));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_RE_SCISSORS_BR, 0));
	radeon_ring_ग_लिखो(ring, 0);
	/* Flush 3D cache */
	radeon_ring_ग_लिखो(ring, PACKET0(R300_RB3D_DSTCACHE_CTLSTAT, 0));
	radeon_ring_ग_लिखो(ring, R300_RB3D_DC_FLUSH);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_RB3D_ZCACHE_CTLSTAT, 0));
	radeon_ring_ग_लिखो(ring, R300_ZC_FLUSH);
	/* Wait until IDLE & CLEAN */
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_WAIT_UNTIL, 0));
	radeon_ring_ग_लिखो(ring, (RADEON_WAIT_3D_IDLECLEAN |
				 RADEON_WAIT_2D_IDLECLEAN |
				 RADEON_WAIT_DMA_GUI_IDLE));
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_HOST_PATH_CNTL, 0));
	radeon_ring_ग_लिखो(ring, rdev->config.r300.hdp_cntl |
				RADEON_HDP_READ_BUFFER_INVALIDATE);
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_HOST_PATH_CNTL, 0));
	radeon_ring_ग_लिखो(ring, rdev->config.r300.hdp_cntl);
	/* Emit fence sequence & fire IRQ */
	radeon_ring_ग_लिखो(ring, PACKET0(rdev->fence_drv[fence->ring].scratch_reg, 0));
	radeon_ring_ग_लिखो(ring, fence->seq);
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_GEN_INT_STATUS, 0));
	radeon_ring_ग_लिखो(ring, RADEON_SW_INT_FIRE);
पूर्ण

व्योम r300_ring_start(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	अचिन्हित gb_tile_config;
	पूर्णांक r;

	/* Sub pixel 1/12 so we can have 4K rendering according to करोc */
	gb_tile_config = (R300_ENABLE_TILING | R300_TILE_SIZE_16);
	चयन(rdev->num_gb_pipes) अणु
	हाल 2:
		gb_tile_config |= R300_PIPE_COUNT_R300;
		अवरोध;
	हाल 3:
		gb_tile_config |= R300_PIPE_COUNT_R420_3P;
		अवरोध;
	हाल 4:
		gb_tile_config |= R300_PIPE_COUNT_R420;
		अवरोध;
	हाल 1:
	शेष:
		gb_tile_config |= R300_PIPE_COUNT_RV350;
		अवरोध;
	पूर्ण

	r = radeon_ring_lock(rdev, ring, 64);
	अगर (r) अणु
		वापस;
	पूर्ण
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_ISYNC_CNTL, 0));
	radeon_ring_ग_लिखो(ring,
			  RADEON_ISYNC_ANY2D_IDLE3D |
			  RADEON_ISYNC_ANY3D_IDLE2D |
			  RADEON_ISYNC_WAIT_IDLEGUI |
			  RADEON_ISYNC_CPSCRATCH_IDLEGUI);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_GB_TILE_CONFIG, 0));
	radeon_ring_ग_लिखो(ring, gb_tile_config);
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_WAIT_UNTIL, 0));
	radeon_ring_ग_लिखो(ring,
			  RADEON_WAIT_2D_IDLECLEAN |
			  RADEON_WAIT_3D_IDLECLEAN);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_DST_PIPE_CONFIG, 0));
	radeon_ring_ग_लिखो(ring, R300_PIPE_AUTO_CONFIG);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_GB_SELECT, 0));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_GB_ENABLE, 0));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_RB3D_DSTCACHE_CTLSTAT, 0));
	radeon_ring_ग_लिखो(ring, R300_RB3D_DC_FLUSH | R300_RB3D_DC_FREE);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_RB3D_ZCACHE_CTLSTAT, 0));
	radeon_ring_ग_लिखो(ring, R300_ZC_FLUSH | R300_ZC_FREE);
	radeon_ring_ग_लिखो(ring, PACKET0(RADEON_WAIT_UNTIL, 0));
	radeon_ring_ग_लिखो(ring,
			  RADEON_WAIT_2D_IDLECLEAN |
			  RADEON_WAIT_3D_IDLECLEAN);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_GB_AA_CONFIG, 0));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_RB3D_DSTCACHE_CTLSTAT, 0));
	radeon_ring_ग_लिखो(ring, R300_RB3D_DC_FLUSH | R300_RB3D_DC_FREE);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_RB3D_ZCACHE_CTLSTAT, 0));
	radeon_ring_ग_लिखो(ring, R300_ZC_FLUSH | R300_ZC_FREE);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_GB_MSPOS0, 0));
	radeon_ring_ग_लिखो(ring,
			  ((6 << R300_MS_X0_SHIFT) |
			   (6 << R300_MS_Y0_SHIFT) |
			   (6 << R300_MS_X1_SHIFT) |
			   (6 << R300_MS_Y1_SHIFT) |
			   (6 << R300_MS_X2_SHIFT) |
			   (6 << R300_MS_Y2_SHIFT) |
			   (6 << R300_MSBD0_Y_SHIFT) |
			   (6 << R300_MSBD0_X_SHIFT)));
	radeon_ring_ग_लिखो(ring, PACKET0(R300_GB_MSPOS1, 0));
	radeon_ring_ग_लिखो(ring,
			  ((6 << R300_MS_X3_SHIFT) |
			   (6 << R300_MS_Y3_SHIFT) |
			   (6 << R300_MS_X4_SHIFT) |
			   (6 << R300_MS_Y4_SHIFT) |
			   (6 << R300_MS_X5_SHIFT) |
			   (6 << R300_MS_Y5_SHIFT) |
			   (6 << R300_MSBD1_SHIFT)));
	radeon_ring_ग_लिखो(ring, PACKET0(R300_GA_ENHANCE, 0));
	radeon_ring_ग_लिखो(ring, R300_GA_DEADLOCK_CNTL | R300_GA_FASTSYNC_CNTL);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_GA_POLY_MODE, 0));
	radeon_ring_ग_लिखो(ring,
			  R300_FRONT_PTYPE_TRIANGE | R300_BACK_PTYPE_TRIANGE);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_GA_ROUND_MODE, 0));
	radeon_ring_ग_लिखो(ring,
			  R300_GEOMETRY_ROUND_NEAREST |
			  R300_COLOR_ROUND_NEAREST);
	radeon_ring_unlock_commit(rdev, ring, false);
पूर्ण

अटल व्योम r300_errata(काष्ठा radeon_device *rdev)
अणु
	rdev->pll_errata = 0;

	अगर (rdev->family == CHIP_R300 &&
	    (RREG32(RADEON_CONFIG_CNTL) & RADEON_CFG_ATI_REV_ID_MASK) == RADEON_CFG_ATI_REV_A11) अणु
		rdev->pll_errata |= CHIP_ERRATA_R300_CG;
	पूर्ण
पूर्ण

पूर्णांक r300_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;
	uपूर्णांक32_t पंचांगp;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		/* पढ़ो MC_STATUS */
		पंचांगp = RREG32(RADEON_MC_STATUS);
		अगर (पंचांगp & R300_MC_IDLE) अणु
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम r300_gpu_init(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t gb_tile_config, पंचांगp;

	अगर ((rdev->family == CHIP_R300 && rdev->pdev->device != 0x4144) ||
	    (rdev->family == CHIP_R350 && rdev->pdev->device != 0x4148)) अणु
		/* r300,r350 */
		rdev->num_gb_pipes = 2;
	पूर्ण अन्यथा अणु
		/* rv350,rv370,rv380,r300 AD, r350 AH */
		rdev->num_gb_pipes = 1;
	पूर्ण
	rdev->num_z_pipes = 1;
	gb_tile_config = (R300_ENABLE_TILING | R300_TILE_SIZE_16);
	चयन (rdev->num_gb_pipes) अणु
	हाल 2:
		gb_tile_config |= R300_PIPE_COUNT_R300;
		अवरोध;
	हाल 3:
		gb_tile_config |= R300_PIPE_COUNT_R420_3P;
		अवरोध;
	हाल 4:
		gb_tile_config |= R300_PIPE_COUNT_R420;
		अवरोध;
	शेष:
	हाल 1:
		gb_tile_config |= R300_PIPE_COUNT_RV350;
		अवरोध;
	पूर्ण
	WREG32(R300_GB_TILE_CONFIG, gb_tile_config);

	अगर (r100_gui_रुको_क्रम_idle(rdev)) अणु
		pr_warn("Failed to wait GUI idle while programming pipes. Bad things might happen.\n");
	पूर्ण

	पंचांगp = RREG32(R300_DST_PIPE_CONFIG);
	WREG32(R300_DST_PIPE_CONFIG, पंचांगp | R300_PIPE_AUTO_CONFIG);

	WREG32(R300_RB2D_DSTCACHE_MODE,
	       R300_DC_AUTOFLUSH_ENABLE |
	       R300_DC_DC_DISABLE_IGNORE_PE);

	अगर (r100_gui_रुको_क्रम_idle(rdev)) अणु
		pr_warn("Failed to wait GUI idle while programming pipes. Bad things might happen.\n");
	पूर्ण
	अगर (r300_mc_रुको_क्रम_idle(rdev)) अणु
		pr_warn("Failed to wait MC idle while programming pipes. Bad things might happen.\n");
	पूर्ण
	DRM_INFO("radeon: %d quad pipes, %d Z pipes initialized\n",
		 rdev->num_gb_pipes, rdev->num_z_pipes);
पूर्ण

पूर्णांक r300_asic_reset(काष्ठा radeon_device *rdev, bool hard)
अणु
	काष्ठा r100_mc_save save;
	u32 status, पंचांगp;
	पूर्णांक ret = 0;

	status = RREG32(R_000E40_RBBM_STATUS);
	अगर (!G_000E40_GUI_ACTIVE(status)) अणु
		वापस 0;
	पूर्ण
	r100_mc_stop(rdev, &save);
	status = RREG32(R_000E40_RBBM_STATUS);
	dev_info(rdev->dev, "(%s:%d) RBBM_STATUS=0x%08X\n", __func__, __LINE__, status);
	/* stop CP */
	WREG32(RADEON_CP_CSQ_CNTL, 0);
	पंचांगp = RREG32(RADEON_CP_RB_CNTL);
	WREG32(RADEON_CP_RB_CNTL, पंचांगp | RADEON_RB_RPTR_WR_ENA);
	WREG32(RADEON_CP_RB_RPTR_WR, 0);
	WREG32(RADEON_CP_RB_WPTR, 0);
	WREG32(RADEON_CP_RB_CNTL, पंचांगp);
	/* save PCI state */
	pci_save_state(rdev->pdev);
	/* disable bus mastering */
	r100_bm_disable(rdev);
	WREG32(R_0000F0_RBBM_SOFT_RESET, S_0000F0_SOFT_RESET_VAP(1) |
					S_0000F0_SOFT_RESET_GA(1));
	RREG32(R_0000F0_RBBM_SOFT_RESET);
	mdelay(500);
	WREG32(R_0000F0_RBBM_SOFT_RESET, 0);
	mdelay(1);
	status = RREG32(R_000E40_RBBM_STATUS);
	dev_info(rdev->dev, "(%s:%d) RBBM_STATUS=0x%08X\n", __func__, __LINE__, status);
	/* resetting the CP seems to be problematic someबार it end up
	 * hard locking the computer, but it's necessary क्रम successful
	 * reset more test & playing is needed on R3XX/R4XX to find a
	 * reliable (अगर any solution)
	 */
	WREG32(R_0000F0_RBBM_SOFT_RESET, S_0000F0_SOFT_RESET_CP(1));
	RREG32(R_0000F0_RBBM_SOFT_RESET);
	mdelay(500);
	WREG32(R_0000F0_RBBM_SOFT_RESET, 0);
	mdelay(1);
	status = RREG32(R_000E40_RBBM_STATUS);
	dev_info(rdev->dev, "(%s:%d) RBBM_STATUS=0x%08X\n", __func__, __LINE__, status);
	/* restore PCI & busmastering */
	pci_restore_state(rdev->pdev);
	r100_enable_bm(rdev);
	/* Check अगर GPU is idle */
	अगर (G_000E40_GA_BUSY(status) || G_000E40_VAP_BUSY(status)) अणु
		dev_err(rdev->dev, "failed to reset GPU\n");
		ret = -1;
	पूर्ण अन्यथा
		dev_info(rdev->dev, "GPU reset succeed\n");
	r100_mc_resume(rdev, &save);
	वापस ret;
पूर्ण

/*
 * r300,r350,rv350,rv380 VRAM info
 */
व्योम r300_mc_init(काष्ठा radeon_device *rdev)
अणु
	u64 base;
	u32 पंचांगp;

	/* DDR क्रम all card after R300 & IGP */
	rdev->mc.vram_is_ddr = true;
	पंचांगp = RREG32(RADEON_MEM_CNTL);
	पंचांगp &= R300_MEM_NUM_CHANNELS_MASK;
	चयन (पंचांगp) अणु
	हाल 0: rdev->mc.vram_width = 64; अवरोध;
	हाल 1: rdev->mc.vram_width = 128; अवरोध;
	हाल 2: rdev->mc.vram_width = 256; अवरोध;
	शेष:  rdev->mc.vram_width = 128; अवरोध;
	पूर्ण
	r100_vram_init_sizes(rdev);
	base = rdev->mc.aper_base;
	अगर (rdev->flags & RADEON_IS_IGP)
		base = (RREG32(RADEON_NB_TOM) & 0xffff) << 16;
	radeon_vram_location(rdev, &rdev->mc, base);
	rdev->mc.gtt_base_align = 0;
	अगर (!(rdev->flags & RADEON_IS_AGP))
		radeon_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);
पूर्ण

व्योम rv370_set_pcie_lanes(काष्ठा radeon_device *rdev, पूर्णांक lanes)
अणु
	uपूर्णांक32_t link_width_cntl, mask;

	अगर (rdev->flags & RADEON_IS_IGP)
		वापस;

	अगर (!(rdev->flags & RADEON_IS_PCIE))
		वापस;

	/* FIXME रुको क्रम idle */

	चयन (lanes) अणु
	हाल 0:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X0;
		अवरोध;
	हाल 1:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X1;
		अवरोध;
	हाल 2:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X2;
		अवरोध;
	हाल 4:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X4;
		अवरोध;
	हाल 8:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X8;
		अवरोध;
	हाल 12:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X12;
		अवरोध;
	हाल 16:
	शेष:
		mask = RADEON_PCIE_LC_LINK_WIDTH_X16;
		अवरोध;
	पूर्ण

	link_width_cntl = RREG32_PCIE(RADEON_PCIE_LC_LINK_WIDTH_CNTL);

	अगर ((link_width_cntl & RADEON_PCIE_LC_LINK_WIDTH_RD_MASK) ==
	    (mask << RADEON_PCIE_LC_LINK_WIDTH_RD_SHIFT))
		वापस;

	link_width_cntl &= ~(RADEON_PCIE_LC_LINK_WIDTH_MASK |
			     RADEON_PCIE_LC_RECONFIG_NOW |
			     RADEON_PCIE_LC_RECONFIG_LATER |
			     RADEON_PCIE_LC_SHORT_RECONFIG_EN);
	link_width_cntl |= mask;
	WREG32_PCIE(RADEON_PCIE_LC_LINK_WIDTH_CNTL, link_width_cntl);
	WREG32_PCIE(RADEON_PCIE_LC_LINK_WIDTH_CNTL, (link_width_cntl |
						     RADEON_PCIE_LC_RECONFIG_NOW));

	/* रुको क्रम lane set to complete */
	link_width_cntl = RREG32_PCIE(RADEON_PCIE_LC_LINK_WIDTH_CNTL);
	जबतक (link_width_cntl == 0xffffffff)
		link_width_cntl = RREG32_PCIE(RADEON_PCIE_LC_LINK_WIDTH_CNTL);

पूर्ण

पूर्णांक rv370_get_pcie_lanes(काष्ठा radeon_device *rdev)
अणु
	u32 link_width_cntl;

	अगर (rdev->flags & RADEON_IS_IGP)
		वापस 0;

	अगर (!(rdev->flags & RADEON_IS_PCIE))
		वापस 0;

	/* FIXME रुको क्रम idle */

	link_width_cntl = RREG32_PCIE(RADEON_PCIE_LC_LINK_WIDTH_CNTL);

	चयन ((link_width_cntl & RADEON_PCIE_LC_LINK_WIDTH_RD_MASK) >> RADEON_PCIE_LC_LINK_WIDTH_RD_SHIFT) अणु
	हाल RADEON_PCIE_LC_LINK_WIDTH_X0:
		वापस 0;
	हाल RADEON_PCIE_LC_LINK_WIDTH_X1:
		वापस 1;
	हाल RADEON_PCIE_LC_LINK_WIDTH_X2:
		वापस 2;
	हाल RADEON_PCIE_LC_LINK_WIDTH_X4:
		वापस 4;
	हाल RADEON_PCIE_LC_LINK_WIDTH_X8:
		वापस 8;
	हाल RADEON_PCIE_LC_LINK_WIDTH_X16:
	शेष:
		वापस 16;
	पूर्ण
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)
अटल पूर्णांक rv370_debugfs_pcie_gart_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;
	uपूर्णांक32_t पंचांगp;

	पंचांगp = RREG32_PCIE(RADEON_PCIE_TX_GART_CNTL);
	seq_म_लिखो(m, "PCIE_TX_GART_CNTL 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_PCIE(RADEON_PCIE_TX_GART_BASE);
	seq_म_लिखो(m, "PCIE_TX_GART_BASE 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_PCIE(RADEON_PCIE_TX_GART_START_LO);
	seq_म_लिखो(m, "PCIE_TX_GART_START_LO 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_PCIE(RADEON_PCIE_TX_GART_START_HI);
	seq_म_लिखो(m, "PCIE_TX_GART_START_HI 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_PCIE(RADEON_PCIE_TX_GART_END_LO);
	seq_म_लिखो(m, "PCIE_TX_GART_END_LO 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_PCIE(RADEON_PCIE_TX_GART_END_HI);
	seq_म_लिखो(m, "PCIE_TX_GART_END_HI 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_PCIE(RADEON_PCIE_TX_GART_ERROR);
	seq_म_लिखो(m, "PCIE_TX_GART_ERROR 0x%08x\n", पंचांगp);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(rv370_debugfs_pcie_gart_info);
#पूर्ण_अगर

अटल व्योम rv370_debugfs_pcie_gart_info_init(काष्ठा radeon_device *rdev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry *root = rdev->ddev->primary->debugfs_root;

	debugfs_create_file("rv370_pcie_gart_info", 0444, root, rdev,
			    &rv370_debugfs_pcie_gart_info_fops);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक r300_packet0_check(काष्ठा radeon_cs_parser *p,
		काष्ठा radeon_cs_packet *pkt,
		अचिन्हित idx, अचिन्हित reg)
अणु
	काष्ठा radeon_bo_list *reloc;
	काष्ठा r100_cs_track *track;
	अस्थिर uपूर्णांक32_t *ib;
	uपूर्णांक32_t पंचांगp, tile_flags = 0;
	अचिन्हित i;
	पूर्णांक r;
	u32 idx_value;

	ib = p->ib.ptr;
	track = (काष्ठा r100_cs_track *)p->track;
	idx_value = radeon_get_ib_value(p, idx);

	चयन(reg) अणु
	हाल AVIVO_D1MODE_VLINE_START_END:
	हाल RADEON_CRTC_GUI_TRIG_VLINE:
		r = r100_cs_packet_parse_vline(p);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
					idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		अवरोध;
	हाल RADEON_DST_PITCH_OFFSET:
	हाल RADEON_SRC_PITCH_OFFSET:
		r = r100_reloc_pitch_offset(p, pkt, idx, reg);
		अगर (r)
			वापस r;
		अवरोध;
	हाल R300_RB3D_COLOROFFSET0:
	हाल R300_RB3D_COLOROFFSET1:
	हाल R300_RB3D_COLOROFFSET2:
	हाल R300_RB3D_COLOROFFSET3:
		i = (reg - R300_RB3D_COLOROFFSET0) >> 2;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
					idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		track->cb[i].robj = reloc->robj;
		track->cb[i].offset = idx_value;
		track->cb_dirty = true;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		अवरोध;
	हाल R300_ZB_DEPTHOFFSET:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
					idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		track->zb.robj = reloc->robj;
		track->zb.offset = idx_value;
		track->zb_dirty = true;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		अवरोध;
	हाल R300_TX_OFFSET_0:
	हाल R300_TX_OFFSET_0+4:
	हाल R300_TX_OFFSET_0+8:
	हाल R300_TX_OFFSET_0+12:
	हाल R300_TX_OFFSET_0+16:
	हाल R300_TX_OFFSET_0+20:
	हाल R300_TX_OFFSET_0+24:
	हाल R300_TX_OFFSET_0+28:
	हाल R300_TX_OFFSET_0+32:
	हाल R300_TX_OFFSET_0+36:
	हाल R300_TX_OFFSET_0+40:
	हाल R300_TX_OFFSET_0+44:
	हाल R300_TX_OFFSET_0+48:
	हाल R300_TX_OFFSET_0+52:
	हाल R300_TX_OFFSET_0+56:
	हाल R300_TX_OFFSET_0+60:
		i = (reg - R300_TX_OFFSET_0) >> 2;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
					idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण

		अगर (p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS) अणु
			ib[idx] = (idx_value & 31) | /* keep the 1st 5 bits */
				  ((idx_value & ~31) + (u32)reloc->gpu_offset);
		पूर्ण अन्यथा अणु
			अगर (reloc->tiling_flags & RADEON_TILING_MACRO)
				tile_flags |= R300_TXO_MACRO_TILE;
			अगर (reloc->tiling_flags & RADEON_TILING_MICRO)
				tile_flags |= R300_TXO_MICRO_TILE;
			अन्यथा अगर (reloc->tiling_flags & RADEON_TILING_MICRO_SQUARE)
				tile_flags |= R300_TXO_MICRO_TILE_SQUARE;

			पंचांगp = idx_value + ((u32)reloc->gpu_offset);
			पंचांगp |= tile_flags;
			ib[idx] = पंचांगp;
		पूर्ण
		track->textures[i].robj = reloc->robj;
		track->tex_dirty = true;
		अवरोध;
	/* Tracked रेजिस्टरs */
	हाल 0x2084:
		/* VAP_VF_CNTL */
		track->vap_vf_cntl = idx_value;
		अवरोध;
	हाल 0x20B4:
		/* VAP_VTX_SIZE */
		track->vtx_size = idx_value & 0x7F;
		अवरोध;
	हाल 0x2134:
		/* VAP_VF_MAX_VTX_INDX */
		track->max_indx = idx_value & 0x00FFFFFFUL;
		अवरोध;
	हाल 0x2088:
		/* VAP_ALT_NUM_VERTICES - only valid on r500 */
		अगर (p->rdev->family < CHIP_RV515)
			जाओ fail;
		track->vap_alt_nverts = idx_value & 0xFFFFFF;
		अवरोध;
	हाल 0x43E4:
		/* SC_SCISSOR1 */
		track->maxy = ((idx_value >> 13) & 0x1FFF) + 1;
		अगर (p->rdev->family < CHIP_RV515) अणु
			track->maxy -= 1440;
		पूर्ण
		track->cb_dirty = true;
		track->zb_dirty = true;
		अवरोध;
	हाल 0x4E00:
		/* RB3D_CCTL */
		अगर ((idx_value & (1 << 10)) && /* CMASK_ENABLE */
		    p->rdev->cmask_filp != p->filp) अणु
			DRM_ERROR("Invalid RB3D_CCTL: Cannot enable CMASK.\n");
			वापस -EINVAL;
		पूर्ण
		track->num_cb = ((idx_value >> 5) & 0x3) + 1;
		track->cb_dirty = true;
		अवरोध;
	हाल 0x4E38:
	हाल 0x4E3C:
	हाल 0x4E40:
	हाल 0x4E44:
		/* RB3D_COLORPITCH0 */
		/* RB3D_COLORPITCH1 */
		/* RB3D_COLORPITCH2 */
		/* RB3D_COLORPITCH3 */
		अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) अणु
			r = radeon_cs_packet_next_reloc(p, &reloc, 0);
			अगर (r) अणु
				DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
					  idx, reg);
				radeon_cs_dump_packet(p, pkt);
				वापस r;
			पूर्ण

			अगर (reloc->tiling_flags & RADEON_TILING_MACRO)
				tile_flags |= R300_COLOR_TILE_ENABLE;
			अगर (reloc->tiling_flags & RADEON_TILING_MICRO)
				tile_flags |= R300_COLOR_MICROTILE_ENABLE;
			अन्यथा अगर (reloc->tiling_flags & RADEON_TILING_MICRO_SQUARE)
				tile_flags |= R300_COLOR_MICROTILE_SQUARE_ENABLE;

			पंचांगp = idx_value & ~(0x7 << 16);
			पंचांगp |= tile_flags;
			ib[idx] = पंचांगp;
		पूर्ण
		i = (reg - 0x4E38) >> 2;
		track->cb[i].pitch = idx_value & 0x3FFE;
		चयन (((idx_value >> 21) & 0xF)) अणु
		हाल 9:
		हाल 11:
		हाल 12:
			track->cb[i].cpp = 1;
			अवरोध;
		हाल 3:
		हाल 4:
		हाल 13:
		हाल 15:
			track->cb[i].cpp = 2;
			अवरोध;
		हाल 5:
			अगर (p->rdev->family < CHIP_RV515) अणु
				DRM_ERROR("Invalid color buffer format (%d)!\n",
					  ((idx_value >> 21) & 0xF));
				वापस -EINVAL;
			पूर्ण
			fallthrough;
		हाल 6:
			track->cb[i].cpp = 4;
			अवरोध;
		हाल 10:
			track->cb[i].cpp = 8;
			अवरोध;
		हाल 7:
			track->cb[i].cpp = 16;
			अवरोध;
		शेष:
			DRM_ERROR("Invalid color buffer format (%d) !\n",
				  ((idx_value >> 21) & 0xF));
			वापस -EINVAL;
		पूर्ण
		track->cb_dirty = true;
		अवरोध;
	हाल 0x4F00:
		/* ZB_CNTL */
		अगर (idx_value & 2) अणु
			track->z_enabled = true;
		पूर्ण अन्यथा अणु
			track->z_enabled = false;
		पूर्ण
		track->zb_dirty = true;
		अवरोध;
	हाल 0x4F10:
		/* ZB_FORMAT */
		चयन ((idx_value & 0xF)) अणु
		हाल 0:
		हाल 1:
			track->zb.cpp = 2;
			अवरोध;
		हाल 2:
			track->zb.cpp = 4;
			अवरोध;
		शेष:
			DRM_ERROR("Invalid z buffer format (%d) !\n",
				  (idx_value & 0xF));
			वापस -EINVAL;
		पूर्ण
		track->zb_dirty = true;
		अवरोध;
	हाल 0x4F24:
		/* ZB_DEPTHPITCH */
		अगर (!(p->cs_flags & RADEON_CS_KEEP_TILING_FLAGS)) अणु
			r = radeon_cs_packet_next_reloc(p, &reloc, 0);
			अगर (r) अणु
				DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
					  idx, reg);
				radeon_cs_dump_packet(p, pkt);
				वापस r;
			पूर्ण

			अगर (reloc->tiling_flags & RADEON_TILING_MACRO)
				tile_flags |= R300_DEPTHMACROTILE_ENABLE;
			अगर (reloc->tiling_flags & RADEON_TILING_MICRO)
				tile_flags |= R300_DEPTHMICROTILE_TILED;
			अन्यथा अगर (reloc->tiling_flags & RADEON_TILING_MICRO_SQUARE)
				tile_flags |= R300_DEPTHMICROTILE_TILED_SQUARE;

			पंचांगp = idx_value & ~(0x7 << 16);
			पंचांगp |= tile_flags;
			ib[idx] = पंचांगp;
		पूर्ण
		track->zb.pitch = idx_value & 0x3FFC;
		track->zb_dirty = true;
		अवरोध;
	हाल 0x4104:
		/* TX_ENABLE */
		क्रम (i = 0; i < 16; i++) अणु
			bool enabled;

			enabled = !!(idx_value & (1 << i));
			track->textures[i].enabled = enabled;
		पूर्ण
		track->tex_dirty = true;
		अवरोध;
	हाल 0x44C0:
	हाल 0x44C4:
	हाल 0x44C8:
	हाल 0x44CC:
	हाल 0x44D0:
	हाल 0x44D4:
	हाल 0x44D8:
	हाल 0x44DC:
	हाल 0x44E0:
	हाल 0x44E4:
	हाल 0x44E8:
	हाल 0x44EC:
	हाल 0x44F0:
	हाल 0x44F4:
	हाल 0x44F8:
	हाल 0x44FC:
		/* TX_FORMAT1_[0-15] */
		i = (reg - 0x44C0) >> 2;
		पंचांगp = (idx_value >> 25) & 0x3;
		track->textures[i].tex_coord_type = पंचांगp;
		चयन ((idx_value & 0x1F)) अणु
		हाल R300_TX_FORMAT_X8:
		हाल R300_TX_FORMAT_Y4X4:
		हाल R300_TX_FORMAT_Z3Y3X2:
			track->textures[i].cpp = 1;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_NONE;
			अवरोध;
		हाल R300_TX_FORMAT_X16:
		हाल R300_TX_FORMAT_FL_I16:
		हाल R300_TX_FORMAT_Y8X8:
		हाल R300_TX_FORMAT_Z5Y6X5:
		हाल R300_TX_FORMAT_Z6Y5X5:
		हाल R300_TX_FORMAT_W4Z4Y4X4:
		हाल R300_TX_FORMAT_W1Z5Y5X5:
		हाल R300_TX_FORMAT_D3DMFT_CxV8U8:
		हाल R300_TX_FORMAT_B8G8_B8G8:
		हाल R300_TX_FORMAT_G8R8_G8B8:
			track->textures[i].cpp = 2;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_NONE;
			अवरोध;
		हाल R300_TX_FORMAT_Y16X16:
		हाल R300_TX_FORMAT_FL_I16A16:
		हाल R300_TX_FORMAT_Z11Y11X10:
		हाल R300_TX_FORMAT_Z10Y11X11:
		हाल R300_TX_FORMAT_W8Z8Y8X8:
		हाल R300_TX_FORMAT_W2Z10Y10X10:
		हाल 0x17:
		हाल R300_TX_FORMAT_FL_I32:
		हाल 0x1e:
			track->textures[i].cpp = 4;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_NONE;
			अवरोध;
		हाल R300_TX_FORMAT_W16Z16Y16X16:
		हाल R300_TX_FORMAT_FL_R16G16B16A16:
		हाल R300_TX_FORMAT_FL_I32A32:
			track->textures[i].cpp = 8;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_NONE;
			अवरोध;
		हाल R300_TX_FORMAT_FL_R32G32B32A32:
			track->textures[i].cpp = 16;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_NONE;
			अवरोध;
		हाल R300_TX_FORMAT_DXT1:
			track->textures[i].cpp = 1;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_DXT1;
			अवरोध;
		हाल R300_TX_FORMAT_ATI2N:
			अगर (p->rdev->family < CHIP_R420) अणु
				DRM_ERROR("Invalid texture format %u\n",
					  (idx_value & 0x1F));
				वापस -EINVAL;
			पूर्ण
			/* The same rules apply as क्रम DXT3/5. */
			fallthrough;
		हाल R300_TX_FORMAT_DXT3:
		हाल R300_TX_FORMAT_DXT5:
			track->textures[i].cpp = 1;
			track->textures[i].compress_क्रमmat = R100_TRACK_COMP_DXT35;
			अवरोध;
		शेष:
			DRM_ERROR("Invalid texture format %u\n",
				  (idx_value & 0x1F));
			वापस -EINVAL;
		पूर्ण
		track->tex_dirty = true;
		अवरोध;
	हाल 0x4400:
	हाल 0x4404:
	हाल 0x4408:
	हाल 0x440C:
	हाल 0x4410:
	हाल 0x4414:
	हाल 0x4418:
	हाल 0x441C:
	हाल 0x4420:
	हाल 0x4424:
	हाल 0x4428:
	हाल 0x442C:
	हाल 0x4430:
	हाल 0x4434:
	हाल 0x4438:
	हाल 0x443C:
		/* TX_FILTER0_[0-15] */
		i = (reg - 0x4400) >> 2;
		पंचांगp = idx_value & 0x7;
		अगर (पंचांगp == 2 || पंचांगp == 4 || पंचांगp == 6) अणु
			track->textures[i].roundup_w = false;
		पूर्ण
		पंचांगp = (idx_value >> 3) & 0x7;
		अगर (पंचांगp == 2 || पंचांगp == 4 || पंचांगp == 6) अणु
			track->textures[i].roundup_h = false;
		पूर्ण
		track->tex_dirty = true;
		अवरोध;
	हाल 0x4500:
	हाल 0x4504:
	हाल 0x4508:
	हाल 0x450C:
	हाल 0x4510:
	हाल 0x4514:
	हाल 0x4518:
	हाल 0x451C:
	हाल 0x4520:
	हाल 0x4524:
	हाल 0x4528:
	हाल 0x452C:
	हाल 0x4530:
	हाल 0x4534:
	हाल 0x4538:
	हाल 0x453C:
		/* TX_FORMAT2_[0-15] */
		i = (reg - 0x4500) >> 2;
		पंचांगp = idx_value & 0x3FFF;
		track->textures[i].pitch = पंचांगp + 1;
		अगर (p->rdev->family >= CHIP_RV515) अणु
			पंचांगp = ((idx_value >> 15) & 1) << 11;
			track->textures[i].width_11 = पंचांगp;
			पंचांगp = ((idx_value >> 16) & 1) << 11;
			track->textures[i].height_11 = पंचांगp;

			/* ATI1N */
			अगर (idx_value & (1 << 14)) अणु
				/* The same rules apply as क्रम DXT1. */
				track->textures[i].compress_क्रमmat =
					R100_TRACK_COMP_DXT1;
			पूर्ण
		पूर्ण अन्यथा अगर (idx_value & (1 << 14)) अणु
			DRM_ERROR("Forbidden bit TXFORMAT_MSB\n");
			वापस -EINVAL;
		पूर्ण
		track->tex_dirty = true;
		अवरोध;
	हाल 0x4480:
	हाल 0x4484:
	हाल 0x4488:
	हाल 0x448C:
	हाल 0x4490:
	हाल 0x4494:
	हाल 0x4498:
	हाल 0x449C:
	हाल 0x44A0:
	हाल 0x44A4:
	हाल 0x44A8:
	हाल 0x44AC:
	हाल 0x44B0:
	हाल 0x44B4:
	हाल 0x44B8:
	हाल 0x44BC:
		/* TX_FORMAT0_[0-15] */
		i = (reg - 0x4480) >> 2;
		पंचांगp = idx_value & 0x7FF;
		track->textures[i].width = पंचांगp + 1;
		पंचांगp = (idx_value >> 11) & 0x7FF;
		track->textures[i].height = पंचांगp + 1;
		पंचांगp = (idx_value >> 26) & 0xF;
		track->textures[i].num_levels = पंचांगp;
		पंचांगp = idx_value & (1 << 31);
		track->textures[i].use_pitch = !!पंचांगp;
		पंचांगp = (idx_value >> 22) & 0xF;
		track->textures[i].txdepth = पंचांगp;
		track->tex_dirty = true;
		अवरोध;
	हाल R300_ZB_ZPASS_ADDR:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
					idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		अवरोध;
	हाल 0x4e0c:
		/* RB3D_COLOR_CHANNEL_MASK */
		track->color_channel_mask = idx_value;
		track->cb_dirty = true;
		अवरोध;
	हाल 0x43a4:
		/* SC_HYPERZ_EN */
		/* r300c emits this रेजिस्टर - we need to disable hyperz क्रम it
		 * without complaining */
		अगर (p->rdev->hyperz_filp != p->filp) अणु
			अगर (idx_value & 0x1)
				ib[idx] = idx_value & ~1;
		पूर्ण
		अवरोध;
	हाल 0x4f1c:
		/* ZB_BW_CNTL */
		track->zb_cb_clear = !!(idx_value & (1 << 5));
		track->cb_dirty = true;
		track->zb_dirty = true;
		अगर (p->rdev->hyperz_filp != p->filp) अणु
			अगर (idx_value & (R300_HIZ_ENABLE |
					 R300_RD_COMP_ENABLE |
					 R300_WR_COMP_ENABLE |
					 R300_FAST_FILL_ENABLE))
				जाओ fail;
		पूर्ण
		अवरोध;
	हाल 0x4e04:
		/* RB3D_BLENDCNTL */
		track->blend_पढ़ो_enable = !!(idx_value & (1 << 2));
		track->cb_dirty = true;
		अवरोध;
	हाल R300_RB3D_AARESOLVE_OFFSET:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for ib[%d]=0x%04X\n",
				  idx, reg);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		track->aa.robj = reloc->robj;
		track->aa.offset = idx_value;
		track->aa_dirty = true;
		ib[idx] = idx_value + ((u32)reloc->gpu_offset);
		अवरोध;
	हाल R300_RB3D_AARESOLVE_PITCH:
		track->aa.pitch = idx_value & 0x3FFE;
		track->aa_dirty = true;
		अवरोध;
	हाल R300_RB3D_AARESOLVE_CTL:
		track->aaresolve = idx_value & 0x1;
		track->aa_dirty = true;
		अवरोध;
	हाल 0x4f30: /* ZB_MASK_OFFSET */
	हाल 0x4f34: /* ZB_ZMASK_PITCH */
	हाल 0x4f44: /* ZB_HIZ_OFFSET */
	हाल 0x4f54: /* ZB_HIZ_PITCH */
		अगर (idx_value && (p->rdev->hyperz_filp != p->filp))
			जाओ fail;
		अवरोध;
	हाल 0x4028:
		अगर (idx_value && (p->rdev->hyperz_filp != p->filp))
			जाओ fail;
		/* GB_Z_PEQ_CONFIG */
		अगर (p->rdev->family >= CHIP_RV350)
			अवरोध;
		जाओ fail;
		अवरोध;
	हाल 0x4be8:
		/* valid रेजिस्टर only on RV530 */
		अगर (p->rdev->family == CHIP_RV530)
			अवरोध;
		fallthrough;
		/* fallthrough करो not move */
	शेष:
		जाओ fail;
	पूर्ण
	वापस 0;
fail:
	pr_err("Forbidden register 0x%04X in cs at %d (val=%08x)\n",
	       reg, idx, idx_value);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक r300_packet3_check(काष्ठा radeon_cs_parser *p,
			      काष्ठा radeon_cs_packet *pkt)
अणु
	काष्ठा radeon_bo_list *reloc;
	काष्ठा r100_cs_track *track;
	अस्थिर uपूर्णांक32_t *ib;
	अचिन्हित idx;
	पूर्णांक r;

	ib = p->ib.ptr;
	idx = pkt->idx + 1;
	track = (काष्ठा r100_cs_track *)p->track;
	चयन(pkt->opcode) अणु
	हाल PACKET3_3D_LOAD_VBPNTR:
		r = r100_packet3_load_vbpntr(p, pkt, idx);
		अगर (r)
			वापस r;
		अवरोध;
	हाल PACKET3_INDX_BUFFER:
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		अगर (r) अणु
			DRM_ERROR("No reloc for packet3 %d\n", pkt->opcode);
			radeon_cs_dump_packet(p, pkt);
			वापस r;
		पूर्ण
		ib[idx+1] = radeon_get_ib_value(p, idx + 1) + ((u32)reloc->gpu_offset);
		r = r100_cs_track_check_pkt3_indx_buffer(p, pkt, reloc->robj);
		अगर (r) अणु
			वापस r;
		पूर्ण
		अवरोध;
	/* Draw packet */
	हाल PACKET3_3D_DRAW_IMMD:
		/* Number of dwords is vtx_size * (num_vertices - 1)
		 * PRIM_WALK must be equal to 3 vertex data in embedded
		 * in cmd stream */
		अगर (((radeon_get_ib_value(p, idx + 1) >> 4) & 0x3) != 3) अणु
			DRM_ERROR("PRIM_WALK must be 3 for IMMD draw\n");
			वापस -EINVAL;
		पूर्ण
		track->vap_vf_cntl = radeon_get_ib_value(p, idx + 1);
		track->immd_dwords = pkt->count - 1;
		r = r100_cs_track_check(p->rdev, track);
		अगर (r) अणु
			वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_3D_DRAW_IMMD_2:
		/* Number of dwords is vtx_size * (num_vertices - 1)
		 * PRIM_WALK must be equal to 3 vertex data in embedded
		 * in cmd stream */
		अगर (((radeon_get_ib_value(p, idx) >> 4) & 0x3) != 3) अणु
			DRM_ERROR("PRIM_WALK must be 3 for IMMD draw\n");
			वापस -EINVAL;
		पूर्ण
		track->vap_vf_cntl = radeon_get_ib_value(p, idx);
		track->immd_dwords = pkt->count;
		r = r100_cs_track_check(p->rdev, track);
		अगर (r) अणु
			वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_3D_DRAW_VBUF:
		track->vap_vf_cntl = radeon_get_ib_value(p, idx + 1);
		r = r100_cs_track_check(p->rdev, track);
		अगर (r) अणु
			वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_3D_DRAW_VBUF_2:
		track->vap_vf_cntl = radeon_get_ib_value(p, idx);
		r = r100_cs_track_check(p->rdev, track);
		अगर (r) अणु
			वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_3D_DRAW_INDX:
		track->vap_vf_cntl = radeon_get_ib_value(p, idx + 1);
		r = r100_cs_track_check(p->rdev, track);
		अगर (r) अणु
			वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_3D_DRAW_INDX_2:
		track->vap_vf_cntl = radeon_get_ib_value(p, idx);
		r = r100_cs_track_check(p->rdev, track);
		अगर (r) अणु
			वापस r;
		पूर्ण
		अवरोध;
	हाल PACKET3_3D_CLEAR_HIZ:
	हाल PACKET3_3D_CLEAR_ZMASK:
		अगर (p->rdev->hyperz_filp != p->filp)
			वापस -EINVAL;
		अवरोध;
	हाल PACKET3_3D_CLEAR_CMASK:
		अगर (p->rdev->cmask_filp != p->filp)
			वापस -EINVAL;
		अवरोध;
	हाल PACKET3_NOP:
		अवरोध;
	शेष:
		DRM_ERROR("Packet3 opcode %x not supported\n", pkt->opcode);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक r300_cs_parse(काष्ठा radeon_cs_parser *p)
अणु
	काष्ठा radeon_cs_packet pkt;
	काष्ठा r100_cs_track *track;
	पूर्णांक r;

	track = kzalloc(माप(*track), GFP_KERNEL);
	अगर (track == शून्य)
		वापस -ENOMEM;
	r100_cs_track_clear(p->rdev, track);
	p->track = track;
	करो अणु
		r = radeon_cs_packet_parse(p, &pkt, p->idx);
		अगर (r) अणु
			वापस r;
		पूर्ण
		p->idx += pkt.count + 2;
		चयन (pkt.type) अणु
		हाल RADEON_PACKET_TYPE0:
			r = r100_cs_parse_packet0(p, &pkt,
						  p->rdev->config.r300.reg_safe_bm,
						  p->rdev->config.r300.reg_safe_bm_size,
						  &r300_packet0_check);
			अवरोध;
		हाल RADEON_PACKET_TYPE2:
			अवरोध;
		हाल RADEON_PACKET_TYPE3:
			r = r300_packet3_check(p, &pkt);
			अवरोध;
		शेष:
			DRM_ERROR("Unknown packet type %d !\n", pkt.type);
			वापस -EINVAL;
		पूर्ण
		अगर (r) अणु
			वापस r;
		पूर्ण
	पूर्ण जबतक (p->idx < p->chunk_ib->length_dw);
	वापस 0;
पूर्ण

व्योम r300_set_reg_safe(काष्ठा radeon_device *rdev)
अणु
	rdev->config.r300.reg_safe_bm = r300_reg_safe_bm;
	rdev->config.r300.reg_safe_bm_size = ARRAY_SIZE(r300_reg_safe_bm);
पूर्ण

व्योम r300_mc_program(काष्ठा radeon_device *rdev)
अणु
	काष्ठा r100_mc_save save;

	r100_debugfs_mc_info_init(rdev);

	/* Stops all mc clients */
	r100_mc_stop(rdev, &save);
	अगर (rdev->flags & RADEON_IS_AGP) अणु
		WREG32(R_00014C_MC_AGP_LOCATION,
			S_00014C_MC_AGP_START(rdev->mc.gtt_start >> 16) |
			S_00014C_MC_AGP_TOP(rdev->mc.gtt_end >> 16));
		WREG32(R_000170_AGP_BASE, lower_32_bits(rdev->mc.agp_base));
		WREG32(R_00015C_AGP_BASE_2,
			upper_32_bits(rdev->mc.agp_base) & 0xff);
	पूर्ण अन्यथा अणु
		WREG32(R_00014C_MC_AGP_LOCATION, 0x0FFFFFFF);
		WREG32(R_000170_AGP_BASE, 0);
		WREG32(R_00015C_AGP_BASE_2, 0);
	पूर्ण
	/* Wait क्रम mc idle */
	अगर (r300_mc_रुको_क्रम_idle(rdev))
		DRM_INFO("Failed to wait MC idle before programming MC.\n");
	/* Program MC, should be a 32bits limited address space */
	WREG32(R_000148_MC_FB_LOCATION,
		S_000148_MC_FB_START(rdev->mc.vram_start >> 16) |
		S_000148_MC_FB_TOP(rdev->mc.vram_end >> 16));
	r100_mc_resume(rdev, &save);
पूर्ण

व्योम r300_घड़ी_startup(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	अगर (radeon_dynclks != -1 && radeon_dynclks)
		radeon_legacy_set_घड़ी_gating(rdev, 1);
	/* We need to क्रमce on some of the block */
	पंचांगp = RREG32_PLL(R_00000D_SCLK_CNTL);
	पंचांगp |= S_00000D_FORCE_CP(1) | S_00000D_FORCE_VIP(1);
	अगर ((rdev->family == CHIP_RV350) || (rdev->family == CHIP_RV380))
		पंचांगp |= S_00000D_FORCE_VAP(1);
	WREG32_PLL(R_00000D_SCLK_CNTL, पंचांगp);
पूर्ण

अटल पूर्णांक r300_startup(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* set common regs */
	r100_set_common_regs(rdev);
	/* program mc */
	r300_mc_program(rdev);
	/* Resume घड़ी */
	r300_घड़ी_startup(rdev);
	/* Initialize GPU configuration (# pipes, ...) */
	r300_gpu_init(rdev);
	/* Initialize GART (initialize after TTM so we can allocate
	 * memory through TTM but finalize after TTM) */
	अगर (rdev->flags & RADEON_IS_PCIE) अणु
		r = rv370_pcie_gart_enable(rdev);
		अगर (r)
			वापस r;
	पूर्ण

	अगर (rdev->family == CHIP_R300 ||
	    rdev->family == CHIP_R350 ||
	    rdev->family == CHIP_RV350)
		r100_enable_bm(rdev);

	अगर (rdev->flags & RADEON_IS_PCI) अणु
		r = r100_pci_gart_enable(rdev);
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

	r100_irq_set(rdev);
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

पूर्णांक r300_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Make sur GART are not working */
	अगर (rdev->flags & RADEON_IS_PCIE)
		rv370_pcie_gart_disable(rdev);
	अगर (rdev->flags & RADEON_IS_PCI)
		r100_pci_gart_disable(rdev);
	/* Resume घड़ी beक्रमe करोing reset */
	r300_घड़ी_startup(rdev);
	/* Reset gpu beक्रमe posting otherwise ATOM will enter infinite loop */
	अगर (radeon_asic_reset(rdev)) अणु
		dev_warn(rdev->dev, "GPU reset failed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			RREG32(R_000E40_RBBM_STATUS),
			RREG32(R_0007C0_CP_STAT));
	पूर्ण
	/* post */
	radeon_combios_asic_init(rdev->ddev);
	/* Resume घड़ी after posting */
	r300_घड़ी_startup(rdev);
	/* Initialize surface रेजिस्टरs */
	radeon_surface_init(rdev);

	rdev->accel_working = true;
	r = r300_startup(rdev);
	अगर (r) अणु
		rdev->accel_working = false;
	पूर्ण
	वापस r;
पूर्ण

पूर्णांक r300_suspend(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_suspend(rdev);
	r100_cp_disable(rdev);
	radeon_wb_disable(rdev);
	r100_irq_disable(rdev);
	अगर (rdev->flags & RADEON_IS_PCIE)
		rv370_pcie_gart_disable(rdev);
	अगर (rdev->flags & RADEON_IS_PCI)
		r100_pci_gart_disable(rdev);
	वापस 0;
पूर्ण

व्योम r300_fini(काष्ठा radeon_device *rdev)
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
	radeon_atombios_fini(rdev);
	kमुक्त(rdev->bios);
	rdev->bios = शून्य;
पूर्ण

पूर्णांक r300_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Disable VGA */
	r100_vga_render_disable(rdev);
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
		dev_err(rdev->dev, "Expecting combios for RS400/RS480 GPU\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		r = radeon_combios_init(rdev);
		अगर (r)
			वापस r;
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
	/* Set asic errata */
	r300_errata(rdev);
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
	/* Fence driver */
	r = radeon_fence_driver_init(rdev);
	अगर (r)
		वापस r;
	/* Memory manager */
	r = radeon_bo_init(rdev);
	अगर (r)
		वापस r;
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
	r300_set_reg_safe(rdev);

	/* Initialize घातer management */
	radeon_pm_init(rdev);

	rdev->accel_working = true;
	r = r300_startup(rdev);
	अगर (r) अणु
		/* Something went wrong with the accel init, so stop accel */
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
