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

#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>

#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "rs400d.h"

/* This files gather functions specअगरics to : rs400,rs480 */
अटल व्योम rs400_debugfs_pcie_gart_info_init(काष्ठा radeon_device *rdev);

व्योम rs400_gart_adjust_size(काष्ठा radeon_device *rdev)
अणु
	/* Check gart size */
	चयन (rdev->mc.gtt_size/(1024*1024)) अणु
	हाल 32:
	हाल 64:
	हाल 128:
	हाल 256:
	हाल 512:
	हाल 1024:
	हाल 2048:
		अवरोध;
	शेष:
		DRM_ERROR("Unable to use IGP GART size %uM\n",
			  (अचिन्हित)(rdev->mc.gtt_size >> 20));
		DRM_ERROR("Valid GART size for IGP are 32M,64M,128M,256M,512M,1G,2G\n");
		DRM_ERROR("Forcing to 32M GART size\n");
		rdev->mc.gtt_size = 32 * 1024 * 1024;
		वापस;
	पूर्ण
पूर्ण

व्योम rs400_gart_tlb_flush(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t पंचांगp;
	अचिन्हित पूर्णांक समयout = rdev->usec_समयout;

	WREG32_MC(RS480_GART_CACHE_CNTRL, RS480_GART_CACHE_INVALIDATE);
	करो अणु
		पंचांगp = RREG32_MC(RS480_GART_CACHE_CNTRL);
		अगर ((पंचांगp & RS480_GART_CACHE_INVALIDATE) == 0)
			अवरोध;
		udelay(1);
		समयout--;
	पूर्ण जबतक (समयout > 0);
	WREG32_MC(RS480_GART_CACHE_CNTRL, 0);
पूर्ण

पूर्णांक rs400_gart_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (rdev->gart.ptr) अणु
		WARN(1, "RS400 GART already initialized\n");
		वापस 0;
	पूर्ण
	/* Check gart size */
	चयन(rdev->mc.gtt_size / (1024 * 1024)) अणु
	हाल 32:
	हाल 64:
	हाल 128:
	हाल 256:
	हाल 512:
	हाल 1024:
	हाल 2048:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	/* Initialize common gart काष्ठाure */
	r = radeon_gart_init(rdev);
	अगर (r)
		वापस r;
	rs400_debugfs_pcie_gart_info_init(rdev);
	rdev->gart.table_size = rdev->gart.num_gpu_pages * 4;
	वापस radeon_gart_table_ram_alloc(rdev);
पूर्ण

पूर्णांक rs400_gart_enable(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t size_reg;
	uपूर्णांक32_t पंचांगp;

	पंचांगp = RREG32_MC(RS690_AIC_CTRL_SCRATCH);
	पंचांगp |= RS690_DIS_OUT_OF_PCI_GART_ACCESS;
	WREG32_MC(RS690_AIC_CTRL_SCRATCH, पंचांगp);
	/* Check gart size */
	चयन(rdev->mc.gtt_size / (1024 * 1024)) अणु
	हाल 32:
		size_reg = RS480_VA_SIZE_32MB;
		अवरोध;
	हाल 64:
		size_reg = RS480_VA_SIZE_64MB;
		अवरोध;
	हाल 128:
		size_reg = RS480_VA_SIZE_128MB;
		अवरोध;
	हाल 256:
		size_reg = RS480_VA_SIZE_256MB;
		अवरोध;
	हाल 512:
		size_reg = RS480_VA_SIZE_512MB;
		अवरोध;
	हाल 1024:
		size_reg = RS480_VA_SIZE_1GB;
		अवरोध;
	हाल 2048:
		size_reg = RS480_VA_SIZE_2GB;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	/* It should be fine to program it to max value */
	अगर (rdev->family == CHIP_RS690 || (rdev->family == CHIP_RS740)) अणु
		WREG32_MC(RS690_MCCFG_AGP_BASE, 0xFFFFFFFF);
		WREG32_MC(RS690_MCCFG_AGP_BASE_2, 0);
	पूर्ण अन्यथा अणु
		WREG32(RADEON_AGP_BASE, 0xFFFFFFFF);
		WREG32(RS480_AGP_BASE_2, 0);
	पूर्ण
	पंचांगp = REG_SET(RS690_MC_AGP_TOP, rdev->mc.gtt_end >> 16);
	पंचांगp |= REG_SET(RS690_MC_AGP_START, rdev->mc.gtt_start >> 16);
	अगर ((rdev->family == CHIP_RS690) || (rdev->family == CHIP_RS740)) अणु
		WREG32_MC(RS690_MCCFG_AGP_LOCATION, पंचांगp);
		पंचांगp = RREG32(RADEON_BUS_CNTL) & ~RS600_BUS_MASTER_DIS;
		WREG32(RADEON_BUS_CNTL, पंचांगp);
	पूर्ण अन्यथा अणु
		WREG32(RADEON_MC_AGP_LOCATION, पंचांगp);
		पंचांगp = RREG32(RADEON_BUS_CNTL) & ~RADEON_BUS_MASTER_DIS;
		WREG32(RADEON_BUS_CNTL, पंचांगp);
	पूर्ण
	/* Table should be in 32bits address space so ignore bits above. */
	पंचांगp = (u32)rdev->gart.table_addr & 0xfffff000;
	पंचांगp |= (upper_32_bits(rdev->gart.table_addr) & 0xff) << 4;

	WREG32_MC(RS480_GART_BASE, पंचांगp);
	/* TODO: more tweaking here */
	WREG32_MC(RS480_GART_FEATURE_ID,
		  (RS480_TLB_ENABLE |
		   RS480_GTW_LAC_EN | RS480_1LEVEL_GART));
	/* Disable snooping */
	WREG32_MC(RS480_AGP_MODE_CNTL,
		  (1 << RS480_REQ_TYPE_SNOOP_SHIFT) | RS480_REQ_TYPE_SNOOP_DIS);
	/* Disable AGP mode */
	/* FIXME: according to करोc we should set HIDE_MMCFG_BAR=0,
	 * AGPMODE30=0 & AGP30ENHANCED=0 in NB_CNTL */
	अगर ((rdev->family == CHIP_RS690) || (rdev->family == CHIP_RS740)) अणु
		पंचांगp = RREG32_MC(RS480_MC_MISC_CNTL);
		पंचांगp |= RS480_GART_INDEX_REG_EN | RS690_BLOCK_GFX_D3_EN;
		WREG32_MC(RS480_MC_MISC_CNTL, पंचांगp);
	पूर्ण अन्यथा अणु
		पंचांगp = RREG32_MC(RS480_MC_MISC_CNTL);
		पंचांगp |= RS480_GART_INDEX_REG_EN;
		WREG32_MC(RS480_MC_MISC_CNTL, पंचांगp);
	पूर्ण
	/* Enable gart */
	WREG32_MC(RS480_AGP_ADDRESS_SPACE_SIZE, (RS480_GART_EN | size_reg));
	rs400_gart_tlb_flush(rdev);
	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (अचिन्हित)(rdev->mc.gtt_size >> 20),
		 (अचिन्हित दीर्घ दीर्घ)rdev->gart.table_addr);
	rdev->gart.पढ़ोy = true;
	वापस 0;
पूर्ण

व्योम rs400_gart_disable(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t पंचांगp;

	पंचांगp = RREG32_MC(RS690_AIC_CTRL_SCRATCH);
	पंचांगp |= RS690_DIS_OUT_OF_PCI_GART_ACCESS;
	WREG32_MC(RS690_AIC_CTRL_SCRATCH, पंचांगp);
	WREG32_MC(RS480_AGP_ADDRESS_SPACE_SIZE, 0);
पूर्ण

व्योम rs400_gart_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_gart_fini(rdev);
	rs400_gart_disable(rdev);
	radeon_gart_table_ram_मुक्त(rdev);
पूर्ण

#घोषणा RS400_PTE_UNSNOOPED (1 << 0)
#घोषणा RS400_PTE_WRITEABLE (1 << 2)
#घोषणा RS400_PTE_READABLE  (1 << 3)

uपूर्णांक64_t rs400_gart_get_page_entry(uपूर्णांक64_t addr, uपूर्णांक32_t flags)
अणु
	uपूर्णांक32_t entry;

	entry = (lower_32_bits(addr) & PAGE_MASK) |
		((upper_32_bits(addr) & 0xff) << 4);
	अगर (flags & RADEON_GART_PAGE_READ)
		entry |= RS400_PTE_READABLE;
	अगर (flags & RADEON_GART_PAGE_WRITE)
		entry |= RS400_PTE_WRITEABLE;
	अगर (!(flags & RADEON_GART_PAGE_SNOOP))
		entry |= RS400_PTE_UNSNOOPED;
	वापस entry;
पूर्ण

व्योम rs400_gart_set_page(काष्ठा radeon_device *rdev, अचिन्हित i,
			 uपूर्णांक64_t entry)
अणु
	u32 *gtt = rdev->gart.ptr;
	gtt[i] = cpu_to_le32(lower_32_bits(entry));
पूर्ण

पूर्णांक rs400_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;
	uपूर्णांक32_t पंचांगp;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		/* पढ़ो MC_STATUS */
		पंचांगp = RREG32(RADEON_MC_STATUS);
		अगर (पंचांगp & RADEON_MC_IDLE) अणु
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम rs400_gpu_init(काष्ठा radeon_device *rdev)
अणु
	/* FIXME: is this correct ? */
	r420_pipes_init(rdev);
	अगर (rs400_mc_रुको_क्रम_idle(rdev)) अणु
		pr_warn("rs400: Failed to wait MC idle while programming pipes. Bad things might happen. %08x\n",
			RREG32(RADEON_MC_STATUS));
	पूर्ण
पूर्ण

अटल व्योम rs400_mc_init(काष्ठा radeon_device *rdev)
अणु
	u64 base;

	rs400_gart_adjust_size(rdev);
	rdev->mc.igp_sideport_enabled = radeon_combios_sideport_present(rdev);
	/* DDR क्रम all card after R300 & IGP */
	rdev->mc.vram_is_ddr = true;
	rdev->mc.vram_width = 128;
	r100_vram_init_sizes(rdev);
	base = (RREG32(RADEON_NB_TOM) & 0xffff) << 16;
	radeon_vram_location(rdev, &rdev->mc, base);
	rdev->mc.gtt_base_align = rdev->mc.gtt_size - 1;
	radeon_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);
पूर्ण

uपूर्णांक32_t rs400_mc_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t r;

	spin_lock_irqsave(&rdev->mc_idx_lock, flags);
	WREG32(RS480_NB_MC_INDEX, reg & 0xff);
	r = RREG32(RS480_NB_MC_DATA);
	WREG32(RS480_NB_MC_INDEX, 0xff);
	spin_unlock_irqrestore(&rdev->mc_idx_lock, flags);
	वापस r;
पूर्ण

व्योम rs400_mc_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->mc_idx_lock, flags);
	WREG32(RS480_NB_MC_INDEX, ((reg) & 0xff) | RS480_NB_MC_IND_WR_EN);
	WREG32(RS480_NB_MC_DATA, (v));
	WREG32(RS480_NB_MC_INDEX, 0xff);
	spin_unlock_irqrestore(&rdev->mc_idx_lock, flags);
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)
अटल पूर्णांक rs400_debugfs_gart_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;
	uपूर्णांक32_t पंचांगp;

	पंचांगp = RREG32(RADEON_HOST_PATH_CNTL);
	seq_म_लिखो(m, "HOST_PATH_CNTL 0x%08x\n", पंचांगp);
	पंचांगp = RREG32(RADEON_BUS_CNTL);
	seq_म_लिखो(m, "BUS_CNTL 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(RS690_AIC_CTRL_SCRATCH);
	seq_म_लिखो(m, "AIC_CTRL_SCRATCH 0x%08x\n", पंचांगp);
	अगर (rdev->family == CHIP_RS690 || (rdev->family == CHIP_RS740)) अणु
		पंचांगp = RREG32_MC(RS690_MCCFG_AGP_BASE);
		seq_म_लिखो(m, "MCCFG_AGP_BASE 0x%08x\n", पंचांगp);
		पंचांगp = RREG32_MC(RS690_MCCFG_AGP_BASE_2);
		seq_म_लिखो(m, "MCCFG_AGP_BASE_2 0x%08x\n", पंचांगp);
		पंचांगp = RREG32_MC(RS690_MCCFG_AGP_LOCATION);
		seq_म_लिखो(m, "MCCFG_AGP_LOCATION 0x%08x\n", पंचांगp);
		पंचांगp = RREG32_MC(RS690_MCCFG_FB_LOCATION);
		seq_म_लिखो(m, "MCCFG_FB_LOCATION 0x%08x\n", पंचांगp);
		पंचांगp = RREG32(RS690_HDP_FB_LOCATION);
		seq_म_लिखो(m, "HDP_FB_LOCATION 0x%08x\n", पंचांगp);
	पूर्ण अन्यथा अणु
		पंचांगp = RREG32(RADEON_AGP_BASE);
		seq_म_लिखो(m, "AGP_BASE 0x%08x\n", पंचांगp);
		पंचांगp = RREG32(RS480_AGP_BASE_2);
		seq_म_लिखो(m, "AGP_BASE_2 0x%08x\n", पंचांगp);
		पंचांगp = RREG32(RADEON_MC_AGP_LOCATION);
		seq_म_लिखो(m, "MC_AGP_LOCATION 0x%08x\n", पंचांगp);
	पूर्ण
	पंचांगp = RREG32_MC(RS480_GART_BASE);
	seq_म_लिखो(m, "GART_BASE 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(RS480_GART_FEATURE_ID);
	seq_म_लिखो(m, "GART_FEATURE_ID 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(RS480_AGP_MODE_CNTL);
	seq_म_लिखो(m, "AGP_MODE_CONTROL 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(RS480_MC_MISC_CNTL);
	seq_म_लिखो(m, "MC_MISC_CNTL 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(0x5F);
	seq_म_लिखो(m, "MC_MISC_UMA_CNTL 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(RS480_AGP_ADDRESS_SPACE_SIZE);
	seq_म_लिखो(m, "AGP_ADDRESS_SPACE_SIZE 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(RS480_GART_CACHE_CNTRL);
	seq_म_लिखो(m, "GART_CACHE_CNTRL 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(0x3B);
	seq_म_लिखो(m, "MC_GART_ERROR_ADDRESS 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(0x3C);
	seq_म_लिखो(m, "MC_GART_ERROR_ADDRESS_HI 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(0x30);
	seq_म_लिखो(m, "GART_ERROR_0 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(0x31);
	seq_म_लिखो(m, "GART_ERROR_1 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(0x32);
	seq_म_लिखो(m, "GART_ERROR_2 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(0x33);
	seq_म_लिखो(m, "GART_ERROR_3 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(0x34);
	seq_म_लिखो(m, "GART_ERROR_4 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(0x35);
	seq_म_लिखो(m, "GART_ERROR_5 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(0x36);
	seq_म_लिखो(m, "GART_ERROR_6 0x%08x\n", पंचांगp);
	पंचांगp = RREG32_MC(0x37);
	seq_म_लिखो(m, "GART_ERROR_7 0x%08x\n", पंचांगp);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(rs400_debugfs_gart_info);
#पूर्ण_अगर

अटल व्योम rs400_debugfs_pcie_gart_info_init(काष्ठा radeon_device *rdev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry *root = rdev->ddev->primary->debugfs_root;

	debugfs_create_file("rs400_gart_info", 0444, root, rdev,
			    &rs400_debugfs_gart_info_fops);
#पूर्ण_अगर
पूर्ण

अटल व्योम rs400_mc_program(काष्ठा radeon_device *rdev)
अणु
	काष्ठा r100_mc_save save;

	/* Stops all mc clients */
	r100_mc_stop(rdev, &save);

	/* Wait क्रम mc idle */
	अगर (rs400_mc_रुको_क्रम_idle(rdev))
		dev_warn(rdev->dev, "rs400: Wait MC idle timeout before updating MC.\n");
	WREG32(R_000148_MC_FB_LOCATION,
		S_000148_MC_FB_START(rdev->mc.vram_start >> 16) |
		S_000148_MC_FB_TOP(rdev->mc.vram_end >> 16));

	r100_mc_resume(rdev, &save);
पूर्ण

अटल पूर्णांक rs400_startup(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	r100_set_common_regs(rdev);

	rs400_mc_program(rdev);
	/* Resume घड़ी */
	r300_घड़ी_startup(rdev);
	/* Initialize GPU configuration (# pipes, ...) */
	rs400_gpu_init(rdev);
	r100_enable_bm(rdev);
	/* Initialize GART (initialize after TTM so we can allocate
	 * memory through TTM but finalize after TTM) */
	r = rs400_gart_enable(rdev);
	अगर (r)
		वापस r;

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

पूर्णांक rs400_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Make sur GART are not working */
	rs400_gart_disable(rdev);
	/* Resume घड़ी beक्रमe करोing reset */
	r300_घड़ी_startup(rdev);
	/* setup MC beक्रमe calling post tables */
	rs400_mc_program(rdev);
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
	r = rs400_startup(rdev);
	अगर (r) अणु
		rdev->accel_working = false;
	पूर्ण
	वापस r;
पूर्ण

पूर्णांक rs400_suspend(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_suspend(rdev);
	r100_cp_disable(rdev);
	radeon_wb_disable(rdev);
	r100_irq_disable(rdev);
	rs400_gart_disable(rdev);
	वापस 0;
पूर्ण

व्योम rs400_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_fini(rdev);
	r100_cp_fini(rdev);
	radeon_wb_fini(rdev);
	radeon_ib_pool_fini(rdev);
	radeon_gem_fini(rdev);
	rs400_gart_fini(rdev);
	radeon_irq_kms_fini(rdev);
	radeon_fence_driver_fini(rdev);
	radeon_bo_fini(rdev);
	radeon_atombios_fini(rdev);
	kमुक्त(rdev->bios);
	rdev->bios = शून्य;
पूर्ण

पूर्णांक rs400_init(काष्ठा radeon_device *rdev)
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

	/* Initialize घड़ीs */
	radeon_get_घड़ी_info(rdev->ddev);
	/* initialize memory controller */
	rs400_mc_init(rdev);
	/* Fence driver */
	r = radeon_fence_driver_init(rdev);
	अगर (r)
		वापस r;
	/* Memory manager */
	r = radeon_bo_init(rdev);
	अगर (r)
		वापस r;
	r = rs400_gart_init(rdev);
	अगर (r)
		वापस r;
	r300_set_reg_safe(rdev);

	/* Initialize घातer management */
	radeon_pm_init(rdev);

	rdev->accel_working = true;
	r = rs400_startup(rdev);
	अगर (r) अणु
		/* Somethings want wront with the accel init stop accel */
		dev_err(rdev->dev, "Disabling GPU acceleration\n");
		r100_cp_fini(rdev);
		radeon_wb_fini(rdev);
		radeon_ib_pool_fini(rdev);
		rs400_gart_fini(rdev);
		radeon_irq_kms_fini(rdev);
		rdev->accel_working = false;
	पूर्ण
	वापस 0;
पूर्ण
