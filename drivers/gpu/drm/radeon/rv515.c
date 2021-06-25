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

#समावेश "atom.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "rv515_reg_safe.h"
#समावेश "rv515d.h"

/* This files gather functions specअगरics to: rv515 */
अटल व्योम rv515_gpu_init(काष्ठा radeon_device *rdev);
पूर्णांक rv515_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev);

अटल स्थिर u32 crtc_offsets[2] =
अणु
	0,
	AVIVO_D2CRTC_H_TOTAL - AVIVO_D1CRTC_H_TOTAL
पूर्ण;

व्योम rv515_ring_start(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	पूर्णांक r;

	r = radeon_ring_lock(rdev, ring, 64);
	अगर (r) अणु
		वापस;
	पूर्ण
	radeon_ring_ग_लिखो(ring, PACKET0(ISYNC_CNTL, 0));
	radeon_ring_ग_लिखो(ring,
			  ISYNC_ANY2D_IDLE3D |
			  ISYNC_ANY3D_IDLE2D |
			  ISYNC_WAIT_IDLEGUI |
			  ISYNC_CPSCRATCH_IDLEGUI);
	radeon_ring_ग_लिखो(ring, PACKET0(WAIT_UNTIL, 0));
	radeon_ring_ग_लिखो(ring, WAIT_2D_IDLECLEAN | WAIT_3D_IDLECLEAN);
	radeon_ring_ग_लिखो(ring, PACKET0(R300_DST_PIPE_CONFIG, 0));
	radeon_ring_ग_लिखो(ring, R300_PIPE_AUTO_CONFIG);
	radeon_ring_ग_लिखो(ring, PACKET0(GB_SELECT, 0));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, PACKET0(GB_ENABLE, 0));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, PACKET0(R500_SU_REG_DEST, 0));
	radeon_ring_ग_लिखो(ring, (1 << rdev->num_gb_pipes) - 1);
	radeon_ring_ग_लिखो(ring, PACKET0(VAP_INDEX_OFFSET, 0));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, PACKET0(RB3D_DSTCACHE_CTLSTAT, 0));
	radeon_ring_ग_लिखो(ring, RB3D_DC_FLUSH | RB3D_DC_FREE);
	radeon_ring_ग_लिखो(ring, PACKET0(ZB_ZCACHE_CTLSTAT, 0));
	radeon_ring_ग_लिखो(ring, ZC_FLUSH | ZC_FREE);
	radeon_ring_ग_लिखो(ring, PACKET0(WAIT_UNTIL, 0));
	radeon_ring_ग_लिखो(ring, WAIT_2D_IDLECLEAN | WAIT_3D_IDLECLEAN);
	radeon_ring_ग_लिखो(ring, PACKET0(GB_AA_CONFIG, 0));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, PACKET0(RB3D_DSTCACHE_CTLSTAT, 0));
	radeon_ring_ग_लिखो(ring, RB3D_DC_FLUSH | RB3D_DC_FREE);
	radeon_ring_ग_लिखो(ring, PACKET0(ZB_ZCACHE_CTLSTAT, 0));
	radeon_ring_ग_लिखो(ring, ZC_FLUSH | ZC_FREE);
	radeon_ring_ग_लिखो(ring, PACKET0(GB_MSPOS0, 0));
	radeon_ring_ग_लिखो(ring,
			  ((6 << MS_X0_SHIFT) |
			   (6 << MS_Y0_SHIFT) |
			   (6 << MS_X1_SHIFT) |
			   (6 << MS_Y1_SHIFT) |
			   (6 << MS_X2_SHIFT) |
			   (6 << MS_Y2_SHIFT) |
			   (6 << MSBD0_Y_SHIFT) |
			   (6 << MSBD0_X_SHIFT)));
	radeon_ring_ग_लिखो(ring, PACKET0(GB_MSPOS1, 0));
	radeon_ring_ग_लिखो(ring,
			  ((6 << MS_X3_SHIFT) |
			   (6 << MS_Y3_SHIFT) |
			   (6 << MS_X4_SHIFT) |
			   (6 << MS_Y4_SHIFT) |
			   (6 << MS_X5_SHIFT) |
			   (6 << MS_Y5_SHIFT) |
			   (6 << MSBD1_SHIFT)));
	radeon_ring_ग_लिखो(ring, PACKET0(GA_ENHANCE, 0));
	radeon_ring_ग_लिखो(ring, GA_DEADLOCK_CNTL | GA_FASTSYNC_CNTL);
	radeon_ring_ग_लिखो(ring, PACKET0(GA_POLY_MODE, 0));
	radeon_ring_ग_लिखो(ring, FRONT_PTYPE_TRIANGE | BACK_PTYPE_TRIANGE);
	radeon_ring_ग_लिखो(ring, PACKET0(GA_ROUND_MODE, 0));
	radeon_ring_ग_लिखो(ring, GEOMETRY_ROUND_NEAREST | COLOR_ROUND_NEAREST);
	radeon_ring_ग_लिखो(ring, PACKET0(0x20C8, 0));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_unlock_commit(rdev, ring, false);
पूर्ण

पूर्णांक rv515_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;
	uपूर्णांक32_t पंचांगp;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		/* पढ़ो MC_STATUS */
		पंचांगp = RREG32_MC(MC_STATUS);
		अगर (पंचांगp & MC_STATUS_IDLE) अणु
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस -1;
पूर्ण

व्योम rv515_vga_render_disable(काष्ठा radeon_device *rdev)
अणु
	WREG32(R_000300_VGA_RENDER_CONTROL,
		RREG32(R_000300_VGA_RENDER_CONTROL) & C_000300_VGA_VSTATUS_CNTL);
पूर्ण

अटल व्योम rv515_gpu_init(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित pipe_select_current, gb_pipe_select, पंचांगp;

	अगर (r100_gui_रुको_क्रम_idle(rdev)) अणु
		pr_warn("Failed to wait GUI idle while resetting GPU. Bad things might happen.\n");
	पूर्ण
	rv515_vga_render_disable(rdev);
	r420_pipes_init(rdev);
	gb_pipe_select = RREG32(R400_GB_PIPE_SELECT);
	पंचांगp = RREG32(R300_DST_PIPE_CONFIG);
	pipe_select_current = (पंचांगp >> 2) & 3;
	पंचांगp = (1 << pipe_select_current) |
	      (((gb_pipe_select >> 8) & 0xF) << 4);
	WREG32_PLL(0x000D, पंचांगp);
	अगर (r100_gui_रुको_क्रम_idle(rdev)) अणु
		pr_warn("Failed to wait GUI idle while resetting GPU. Bad things might happen.\n");
	पूर्ण
	अगर (rv515_mc_रुको_क्रम_idle(rdev)) अणु
		pr_warn("Failed to wait MC idle while programming pipes. Bad things might happen.\n");
	पूर्ण
पूर्ण

अटल व्योम rv515_vram_get_type(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t पंचांगp;

	rdev->mc.vram_width = 128;
	rdev->mc.vram_is_ddr = true;
	पंचांगp = RREG32_MC(RV515_MC_CNTL) & MEM_NUM_CHANNELS_MASK;
	चयन (पंचांगp) अणु
	हाल 0:
		rdev->mc.vram_width = 64;
		अवरोध;
	हाल 1:
		rdev->mc.vram_width = 128;
		अवरोध;
	शेष:
		rdev->mc.vram_width = 128;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rv515_mc_init(काष्ठा radeon_device *rdev)
अणु

	rv515_vram_get_type(rdev);
	r100_vram_init_sizes(rdev);
	radeon_vram_location(rdev, &rdev->mc, 0);
	rdev->mc.gtt_base_align = 0;
	अगर (!(rdev->flags & RADEON_IS_AGP))
		radeon_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);
पूर्ण

uपूर्णांक32_t rv515_mc_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t r;

	spin_lock_irqsave(&rdev->mc_idx_lock, flags);
	WREG32(MC_IND_INDEX, 0x7f0000 | (reg & 0xffff));
	r = RREG32(MC_IND_DATA);
	WREG32(MC_IND_INDEX, 0);
	spin_unlock_irqrestore(&rdev->mc_idx_lock, flags);

	वापस r;
पूर्ण

व्योम rv515_mc_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->mc_idx_lock, flags);
	WREG32(MC_IND_INDEX, 0xff0000 | ((reg) & 0xffff));
	WREG32(MC_IND_DATA, (v));
	WREG32(MC_IND_INDEX, 0);
	spin_unlock_irqrestore(&rdev->mc_idx_lock, flags);
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)
अटल पूर्णांक rv515_debugfs_pipes_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;
	uपूर्णांक32_t पंचांगp;

	पंचांगp = RREG32(GB_PIPE_SELECT);
	seq_म_लिखो(m, "GB_PIPE_SELECT 0x%08x\n", पंचांगp);
	पंचांगp = RREG32(SU_REG_DEST);
	seq_म_लिखो(m, "SU_REG_DEST 0x%08x\n", पंचांगp);
	पंचांगp = RREG32(GB_TILE_CONFIG);
	seq_म_लिखो(m, "GB_TILE_CONFIG 0x%08x\n", पंचांगp);
	पंचांगp = RREG32(DST_PIPE_CONFIG);
	seq_म_लिखो(m, "DST_PIPE_CONFIG 0x%08x\n", पंचांगp);
	वापस 0;
पूर्ण

अटल पूर्णांक rv515_debugfs_ga_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;
	uपूर्णांक32_t पंचांगp;

	पंचांगp = RREG32(0x2140);
	seq_म_लिखो(m, "VAP_CNTL_STATUS 0x%08x\n", पंचांगp);
	radeon_asic_reset(rdev);
	पंचांगp = RREG32(0x425C);
	seq_म_लिखो(m, "GA_IDLE 0x%08x\n", पंचांगp);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(rv515_debugfs_pipes_info);
DEFINE_SHOW_ATTRIBUTE(rv515_debugfs_ga_info);
#पूर्ण_अगर

व्योम rv515_debugfs(काष्ठा radeon_device *rdev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry *root = rdev->ddev->primary->debugfs_root;

	debugfs_create_file("rv515_pipes_info", 0444, root, rdev,
			    &rv515_debugfs_pipes_info_fops);
	debugfs_create_file("rv515_ga_info", 0444, root, rdev,
			    &rv515_debugfs_ga_info_fops);
#पूर्ण_अगर
	r100_debugfs_rbbm_init(rdev);
पूर्ण

व्योम rv515_mc_stop(काष्ठा radeon_device *rdev, काष्ठा rv515_mc_save *save)
अणु
	u32 crtc_enabled, पंचांगp, frame_count, blackout;
	पूर्णांक i, j;

	save->vga_render_control = RREG32(R_000300_VGA_RENDER_CONTROL);
	save->vga_hdp_control = RREG32(R_000328_VGA_HDP_CONTROL);

	/* disable VGA render */
	WREG32(R_000300_VGA_RENDER_CONTROL, 0);
	/* blank the display controllers */
	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		crtc_enabled = RREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[i]) & AVIVO_CRTC_EN;
		अगर (crtc_enabled) अणु
			save->crtc_enabled[i] = true;
			पंचांगp = RREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[i]);
			अगर (!(पंचांगp & AVIVO_CRTC_DISP_READ_REQUEST_DISABLE)) अणु
				radeon_रुको_क्रम_vblank(rdev, i);
				WREG32(AVIVO_D1CRTC_UPDATE_LOCK + crtc_offsets[i], 1);
				पंचांगp |= AVIVO_CRTC_DISP_READ_REQUEST_DISABLE;
				WREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[i], पंचांगp);
				WREG32(AVIVO_D1CRTC_UPDATE_LOCK + crtc_offsets[i], 0);
			पूर्ण
			/* रुको क्रम the next frame */
			frame_count = radeon_get_vblank_counter(rdev, i);
			क्रम (j = 0; j < rdev->usec_समयout; j++) अणु
				अगर (radeon_get_vblank_counter(rdev, i) != frame_count)
					अवरोध;
				udelay(1);
			पूर्ण

			/* XXX this is a hack to aव्योम strange behavior with EFI on certain प्रणालीs */
			WREG32(AVIVO_D1CRTC_UPDATE_LOCK + crtc_offsets[i], 1);
			पंचांगp = RREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[i]);
			पंचांगp &= ~AVIVO_CRTC_EN;
			WREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[i], पंचांगp);
			WREG32(AVIVO_D1CRTC_UPDATE_LOCK + crtc_offsets[i], 0);
			save->crtc_enabled[i] = false;
			/* ***** */
		पूर्ण अन्यथा अणु
			save->crtc_enabled[i] = false;
		पूर्ण
	पूर्ण

	radeon_mc_रुको_क्रम_idle(rdev);

	अगर (rdev->family >= CHIP_R600) अणु
		अगर (rdev->family >= CHIP_RV770)
			blackout = RREG32(R700_MC_CITF_CNTL);
		अन्यथा
			blackout = RREG32(R600_CITF_CNTL);
		अगर ((blackout & R600_BLACKOUT_MASK) != R600_BLACKOUT_MASK) अणु
			/* Block CPU access */
			WREG32(R600_BIF_FB_EN, 0);
			/* blackout the MC */
			blackout |= R600_BLACKOUT_MASK;
			अगर (rdev->family >= CHIP_RV770)
				WREG32(R700_MC_CITF_CNTL, blackout);
			अन्यथा
				WREG32(R600_CITF_CNTL, blackout);
		पूर्ण
	पूर्ण
	/* रुको क्रम the MC to settle */
	udelay(100);

	/* lock द्विगुन buffered regs */
	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		अगर (save->crtc_enabled[i]) अणु
			पंचांगp = RREG32(AVIVO_D1GRPH_UPDATE + crtc_offsets[i]);
			अगर (!(पंचांगp & AVIVO_D1GRPH_UPDATE_LOCK)) अणु
				पंचांगp |= AVIVO_D1GRPH_UPDATE_LOCK;
				WREG32(AVIVO_D1GRPH_UPDATE + crtc_offsets[i], पंचांगp);
			पूर्ण
			पंचांगp = RREG32(AVIVO_D1MODE_MASTER_UPDATE_LOCK + crtc_offsets[i]);
			अगर (!(पंचांगp & 1)) अणु
				पंचांगp |= 1;
				WREG32(AVIVO_D1MODE_MASTER_UPDATE_LOCK + crtc_offsets[i], पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम rv515_mc_resume(काष्ठा radeon_device *rdev, काष्ठा rv515_mc_save *save)
अणु
	u32 पंचांगp, frame_count;
	पूर्णांक i, j;

	/* update crtc base addresses */
	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		अगर (rdev->family >= CHIP_RV770) अणु
			अगर (i == 0) अणु
				WREG32(R700_D1GRPH_PRIMARY_SURFACE_ADDRESS_HIGH,
				       upper_32_bits(rdev->mc.vram_start));
				WREG32(R700_D1GRPH_SECONDARY_SURFACE_ADDRESS_HIGH,
				       upper_32_bits(rdev->mc.vram_start));
			पूर्ण अन्यथा अणु
				WREG32(R700_D2GRPH_PRIMARY_SURFACE_ADDRESS_HIGH,
				       upper_32_bits(rdev->mc.vram_start));
				WREG32(R700_D2GRPH_SECONDARY_SURFACE_ADDRESS_HIGH,
				       upper_32_bits(rdev->mc.vram_start));
			पूर्ण
		पूर्ण
		WREG32(R_006110_D1GRPH_PRIMARY_SURFACE_ADDRESS + crtc_offsets[i],
		       (u32)rdev->mc.vram_start);
		WREG32(R_006118_D1GRPH_SECONDARY_SURFACE_ADDRESS + crtc_offsets[i],
		       (u32)rdev->mc.vram_start);
	पूर्ण
	WREG32(R_000310_VGA_MEMORY_BASE_ADDRESS, (u32)rdev->mc.vram_start);

	/* unlock regs and रुको क्रम update */
	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		अगर (save->crtc_enabled[i]) अणु
			पंचांगp = RREG32(AVIVO_D1MODE_MASTER_UPDATE_MODE + crtc_offsets[i]);
			अगर ((पंचांगp & 0x7) != 3) अणु
				पंचांगp &= ~0x7;
				पंचांगp |= 0x3;
				WREG32(AVIVO_D1MODE_MASTER_UPDATE_MODE + crtc_offsets[i], पंचांगp);
			पूर्ण
			पंचांगp = RREG32(AVIVO_D1GRPH_UPDATE + crtc_offsets[i]);
			अगर (पंचांगp & AVIVO_D1GRPH_UPDATE_LOCK) अणु
				पंचांगp &= ~AVIVO_D1GRPH_UPDATE_LOCK;
				WREG32(AVIVO_D1GRPH_UPDATE + crtc_offsets[i], पंचांगp);
			पूर्ण
			पंचांगp = RREG32(AVIVO_D1MODE_MASTER_UPDATE_LOCK + crtc_offsets[i]);
			अगर (पंचांगp & 1) अणु
				पंचांगp &= ~1;
				WREG32(AVIVO_D1MODE_MASTER_UPDATE_LOCK + crtc_offsets[i], पंचांगp);
			पूर्ण
			क्रम (j = 0; j < rdev->usec_समयout; j++) अणु
				पंचांगp = RREG32(AVIVO_D1GRPH_UPDATE + crtc_offsets[i]);
				अगर ((पंचांगp & AVIVO_D1GRPH_SURFACE_UPDATE_PENDING) == 0)
					अवरोध;
				udelay(1);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rdev->family >= CHIP_R600) अणु
		/* unblackout the MC */
		अगर (rdev->family >= CHIP_RV770)
			पंचांगp = RREG32(R700_MC_CITF_CNTL);
		अन्यथा
			पंचांगp = RREG32(R600_CITF_CNTL);
		पंचांगp &= ~R600_BLACKOUT_MASK;
		अगर (rdev->family >= CHIP_RV770)
			WREG32(R700_MC_CITF_CNTL, पंचांगp);
		अन्यथा
			WREG32(R600_CITF_CNTL, पंचांगp);
		/* allow CPU access */
		WREG32(R600_BIF_FB_EN, R600_FB_READ_EN | R600_FB_WRITE_EN);
	पूर्ण

	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		अगर (save->crtc_enabled[i]) अणु
			पंचांगp = RREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[i]);
			पंचांगp &= ~AVIVO_CRTC_DISP_READ_REQUEST_DISABLE;
			WREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[i], पंचांगp);
			/* रुको क्रम the next frame */
			frame_count = radeon_get_vblank_counter(rdev, i);
			क्रम (j = 0; j < rdev->usec_समयout; j++) अणु
				अगर (radeon_get_vblank_counter(rdev, i) != frame_count)
					अवरोध;
				udelay(1);
			पूर्ण
		पूर्ण
	पूर्ण
	/* Unlock vga access */
	WREG32(R_000328_VGA_HDP_CONTROL, save->vga_hdp_control);
	mdelay(1);
	WREG32(R_000300_VGA_RENDER_CONTROL, save->vga_render_control);
पूर्ण

अटल व्योम rv515_mc_program(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv515_mc_save save;

	/* Stops all mc clients */
	rv515_mc_stop(rdev, &save);

	/* Wait क्रम mc idle */
	अगर (rv515_mc_रुको_क्रम_idle(rdev))
		dev_warn(rdev->dev, "Wait MC idle timeout before updating MC.\n");
	/* Write VRAM size in हाल we are limiting it */
	WREG32(R_0000F8_CONFIG_MEMSIZE, rdev->mc.real_vram_size);
	/* Program MC, should be a 32bits limited address space */
	WREG32_MC(R_000001_MC_FB_LOCATION,
			S_000001_MC_FB_START(rdev->mc.vram_start >> 16) |
			S_000001_MC_FB_TOP(rdev->mc.vram_end >> 16));
	WREG32(R_000134_HDP_FB_LOCATION,
		S_000134_HDP_FB_START(rdev->mc.vram_start >> 16));
	अगर (rdev->flags & RADEON_IS_AGP) अणु
		WREG32_MC(R_000002_MC_AGP_LOCATION,
			S_000002_MC_AGP_START(rdev->mc.gtt_start >> 16) |
			S_000002_MC_AGP_TOP(rdev->mc.gtt_end >> 16));
		WREG32_MC(R_000003_MC_AGP_BASE, lower_32_bits(rdev->mc.agp_base));
		WREG32_MC(R_000004_MC_AGP_BASE_2,
			S_000004_AGP_BASE_ADDR_2(upper_32_bits(rdev->mc.agp_base)));
	पूर्ण अन्यथा अणु
		WREG32_MC(R_000002_MC_AGP_LOCATION, 0xFFFFFFFF);
		WREG32_MC(R_000003_MC_AGP_BASE, 0);
		WREG32_MC(R_000004_MC_AGP_BASE_2, 0);
	पूर्ण

	rv515_mc_resume(rdev, &save);
पूर्ण

व्योम rv515_घड़ी_startup(काष्ठा radeon_device *rdev)
अणु
	अगर (radeon_dynclks != -1 && radeon_dynclks)
		radeon_atom_set_घड़ी_gating(rdev, 1);
	/* We need to क्रमce on some of the block */
	WREG32_PLL(R_00000F_CP_DYN_CNTL,
		RREG32_PLL(R_00000F_CP_DYN_CNTL) | S_00000F_CP_FORCEON(1));
	WREG32_PLL(R_000011_E2_DYN_CNTL,
		RREG32_PLL(R_000011_E2_DYN_CNTL) | S_000011_E2_FORCEON(1));
	WREG32_PLL(R_000013_IDCT_DYN_CNTL,
		RREG32_PLL(R_000013_IDCT_DYN_CNTL) | S_000013_IDCT_FORCEON(1));
पूर्ण

अटल पूर्णांक rv515_startup(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	rv515_mc_program(rdev);
	/* Resume घड़ी */
	rv515_घड़ी_startup(rdev);
	/* Initialize GPU configuration (# pipes, ...) */
	rv515_gpu_init(rdev);
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

पूर्णांक rv515_resume(काष्ठा radeon_device *rdev)
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
	r =  rv515_startup(rdev);
	अगर (r) अणु
		rdev->accel_working = false;
	पूर्ण
	वापस r;
पूर्ण

पूर्णांक rv515_suspend(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_suspend(rdev);
	r100_cp_disable(rdev);
	radeon_wb_disable(rdev);
	rs600_irq_disable(rdev);
	अगर (rdev->flags & RADEON_IS_PCIE)
		rv370_pcie_gart_disable(rdev);
	वापस 0;
पूर्ण

व्योम rv515_set_safe_रेजिस्टरs(काष्ठा radeon_device *rdev)
अणु
	rdev->config.r300.reg_safe_bm = rv515_reg_safe_bm;
	rdev->config.r300.reg_safe_bm_size = ARRAY_SIZE(rv515_reg_safe_bm);
पूर्ण

व्योम rv515_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_fini(rdev);
	r100_cp_fini(rdev);
	radeon_wb_fini(rdev);
	radeon_ib_pool_fini(rdev);
	radeon_gem_fini(rdev);
	rv370_pcie_gart_fini(rdev);
	radeon_agp_fini(rdev);
	radeon_irq_kms_fini(rdev);
	radeon_fence_driver_fini(rdev);
	radeon_bo_fini(rdev);
	radeon_atombios_fini(rdev);
	kमुक्त(rdev->bios);
	rdev->bios = शून्य;
पूर्ण

पूर्णांक rv515_init(काष्ठा radeon_device *rdev)
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
	rv515_mc_init(rdev);
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
	r = rv515_startup(rdev);
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

व्योम atom_rv515_क्रमce_tv_scaler(काष्ठा radeon_device *rdev, काष्ठा radeon_crtc *crtc)
अणु
	पूर्णांक index_reg = 0x6578 + crtc->crtc_offset;
	पूर्णांक data_reg = 0x657c + crtc->crtc_offset;

	WREG32(0x659C + crtc->crtc_offset, 0x0);
	WREG32(0x6594 + crtc->crtc_offset, 0x705);
	WREG32(0x65A4 + crtc->crtc_offset, 0x10001);
	WREG32(0x65D8 + crtc->crtc_offset, 0x0);
	WREG32(0x65B0 + crtc->crtc_offset, 0x0);
	WREG32(0x65C0 + crtc->crtc_offset, 0x0);
	WREG32(0x65D4 + crtc->crtc_offset, 0x0);
	WREG32(index_reg, 0x0);
	WREG32(data_reg, 0x841880A8);
	WREG32(index_reg, 0x1);
	WREG32(data_reg, 0x84208680);
	WREG32(index_reg, 0x2);
	WREG32(data_reg, 0xBFF880B0);
	WREG32(index_reg, 0x100);
	WREG32(data_reg, 0x83D88088);
	WREG32(index_reg, 0x101);
	WREG32(data_reg, 0x84608680);
	WREG32(index_reg, 0x102);
	WREG32(data_reg, 0xBFF080D0);
	WREG32(index_reg, 0x200);
	WREG32(data_reg, 0x83988068);
	WREG32(index_reg, 0x201);
	WREG32(data_reg, 0x84A08680);
	WREG32(index_reg, 0x202);
	WREG32(data_reg, 0xBFF080F8);
	WREG32(index_reg, 0x300);
	WREG32(data_reg, 0x83588058);
	WREG32(index_reg, 0x301);
	WREG32(data_reg, 0x84E08660);
	WREG32(index_reg, 0x302);
	WREG32(data_reg, 0xBFF88120);
	WREG32(index_reg, 0x400);
	WREG32(data_reg, 0x83188040);
	WREG32(index_reg, 0x401);
	WREG32(data_reg, 0x85008660);
	WREG32(index_reg, 0x402);
	WREG32(data_reg, 0xBFF88150);
	WREG32(index_reg, 0x500);
	WREG32(data_reg, 0x82D88030);
	WREG32(index_reg, 0x501);
	WREG32(data_reg, 0x85408640);
	WREG32(index_reg, 0x502);
	WREG32(data_reg, 0xBFF88180);
	WREG32(index_reg, 0x600);
	WREG32(data_reg, 0x82A08018);
	WREG32(index_reg, 0x601);
	WREG32(data_reg, 0x85808620);
	WREG32(index_reg, 0x602);
	WREG32(data_reg, 0xBFF081B8);
	WREG32(index_reg, 0x700);
	WREG32(data_reg, 0x82608010);
	WREG32(index_reg, 0x701);
	WREG32(data_reg, 0x85A08600);
	WREG32(index_reg, 0x702);
	WREG32(data_reg, 0x800081F0);
	WREG32(index_reg, 0x800);
	WREG32(data_reg, 0x8228BFF8);
	WREG32(index_reg, 0x801);
	WREG32(data_reg, 0x85E085E0);
	WREG32(index_reg, 0x802);
	WREG32(data_reg, 0xBFF88228);
	WREG32(index_reg, 0x10000);
	WREG32(data_reg, 0x82A8BF00);
	WREG32(index_reg, 0x10001);
	WREG32(data_reg, 0x82A08CC0);
	WREG32(index_reg, 0x10002);
	WREG32(data_reg, 0x8008BEF8);
	WREG32(index_reg, 0x10100);
	WREG32(data_reg, 0x81F0BF28);
	WREG32(index_reg, 0x10101);
	WREG32(data_reg, 0x83608CA0);
	WREG32(index_reg, 0x10102);
	WREG32(data_reg, 0x8018BED0);
	WREG32(index_reg, 0x10200);
	WREG32(data_reg, 0x8148BF38);
	WREG32(index_reg, 0x10201);
	WREG32(data_reg, 0x84408C80);
	WREG32(index_reg, 0x10202);
	WREG32(data_reg, 0x8008BEB8);
	WREG32(index_reg, 0x10300);
	WREG32(data_reg, 0x80B0BF78);
	WREG32(index_reg, 0x10301);
	WREG32(data_reg, 0x85008C20);
	WREG32(index_reg, 0x10302);
	WREG32(data_reg, 0x8020BEA0);
	WREG32(index_reg, 0x10400);
	WREG32(data_reg, 0x8028BF90);
	WREG32(index_reg, 0x10401);
	WREG32(data_reg, 0x85E08BC0);
	WREG32(index_reg, 0x10402);
	WREG32(data_reg, 0x8018BE90);
	WREG32(index_reg, 0x10500);
	WREG32(data_reg, 0xBFB8BFB0);
	WREG32(index_reg, 0x10501);
	WREG32(data_reg, 0x86C08B40);
	WREG32(index_reg, 0x10502);
	WREG32(data_reg, 0x8010BE90);
	WREG32(index_reg, 0x10600);
	WREG32(data_reg, 0xBF58BFC8);
	WREG32(index_reg, 0x10601);
	WREG32(data_reg, 0x87A08AA0);
	WREG32(index_reg, 0x10602);
	WREG32(data_reg, 0x8010BE98);
	WREG32(index_reg, 0x10700);
	WREG32(data_reg, 0xBF10BFF0);
	WREG32(index_reg, 0x10701);
	WREG32(data_reg, 0x886089E0);
	WREG32(index_reg, 0x10702);
	WREG32(data_reg, 0x8018BEB0);
	WREG32(index_reg, 0x10800);
	WREG32(data_reg, 0xBED8BFE8);
	WREG32(index_reg, 0x10801);
	WREG32(data_reg, 0x89408940);
	WREG32(index_reg, 0x10802);
	WREG32(data_reg, 0xBFE8BED8);
	WREG32(index_reg, 0x20000);
	WREG32(data_reg, 0x80008000);
	WREG32(index_reg, 0x20001);
	WREG32(data_reg, 0x90008000);
	WREG32(index_reg, 0x20002);
	WREG32(data_reg, 0x80008000);
	WREG32(index_reg, 0x20003);
	WREG32(data_reg, 0x80008000);
	WREG32(index_reg, 0x20100);
	WREG32(data_reg, 0x80108000);
	WREG32(index_reg, 0x20101);
	WREG32(data_reg, 0x8FE0BF70);
	WREG32(index_reg, 0x20102);
	WREG32(data_reg, 0xBFE880C0);
	WREG32(index_reg, 0x20103);
	WREG32(data_reg, 0x80008000);
	WREG32(index_reg, 0x20200);
	WREG32(data_reg, 0x8018BFF8);
	WREG32(index_reg, 0x20201);
	WREG32(data_reg, 0x8F80BF08);
	WREG32(index_reg, 0x20202);
	WREG32(data_reg, 0xBFD081A0);
	WREG32(index_reg, 0x20203);
	WREG32(data_reg, 0xBFF88000);
	WREG32(index_reg, 0x20300);
	WREG32(data_reg, 0x80188000);
	WREG32(index_reg, 0x20301);
	WREG32(data_reg, 0x8EE0BEC0);
	WREG32(index_reg, 0x20302);
	WREG32(data_reg, 0xBFB082A0);
	WREG32(index_reg, 0x20303);
	WREG32(data_reg, 0x80008000);
	WREG32(index_reg, 0x20400);
	WREG32(data_reg, 0x80188000);
	WREG32(index_reg, 0x20401);
	WREG32(data_reg, 0x8E00BEA0);
	WREG32(index_reg, 0x20402);
	WREG32(data_reg, 0xBF8883C0);
	WREG32(index_reg, 0x20403);
	WREG32(data_reg, 0x80008000);
	WREG32(index_reg, 0x20500);
	WREG32(data_reg, 0x80188000);
	WREG32(index_reg, 0x20501);
	WREG32(data_reg, 0x8D00BE90);
	WREG32(index_reg, 0x20502);
	WREG32(data_reg, 0xBF588500);
	WREG32(index_reg, 0x20503);
	WREG32(data_reg, 0x80008008);
	WREG32(index_reg, 0x20600);
	WREG32(data_reg, 0x80188000);
	WREG32(index_reg, 0x20601);
	WREG32(data_reg, 0x8BC0BE98);
	WREG32(index_reg, 0x20602);
	WREG32(data_reg, 0xBF308660);
	WREG32(index_reg, 0x20603);
	WREG32(data_reg, 0x80008008);
	WREG32(index_reg, 0x20700);
	WREG32(data_reg, 0x80108000);
	WREG32(index_reg, 0x20701);
	WREG32(data_reg, 0x8A80BEB0);
	WREG32(index_reg, 0x20702);
	WREG32(data_reg, 0xBF0087C0);
	WREG32(index_reg, 0x20703);
	WREG32(data_reg, 0x80008008);
	WREG32(index_reg, 0x20800);
	WREG32(data_reg, 0x80108000);
	WREG32(index_reg, 0x20801);
	WREG32(data_reg, 0x8920BED0);
	WREG32(index_reg, 0x20802);
	WREG32(data_reg, 0xBED08920);
	WREG32(index_reg, 0x20803);
	WREG32(data_reg, 0x80008010);
	WREG32(index_reg, 0x30000);
	WREG32(data_reg, 0x90008000);
	WREG32(index_reg, 0x30001);
	WREG32(data_reg, 0x80008000);
	WREG32(index_reg, 0x30100);
	WREG32(data_reg, 0x8FE0BF90);
	WREG32(index_reg, 0x30101);
	WREG32(data_reg, 0xBFF880A0);
	WREG32(index_reg, 0x30200);
	WREG32(data_reg, 0x8F60BF40);
	WREG32(index_reg, 0x30201);
	WREG32(data_reg, 0xBFE88180);
	WREG32(index_reg, 0x30300);
	WREG32(data_reg, 0x8EC0BF00);
	WREG32(index_reg, 0x30301);
	WREG32(data_reg, 0xBFC88280);
	WREG32(index_reg, 0x30400);
	WREG32(data_reg, 0x8DE0BEE0);
	WREG32(index_reg, 0x30401);
	WREG32(data_reg, 0xBFA083A0);
	WREG32(index_reg, 0x30500);
	WREG32(data_reg, 0x8CE0BED0);
	WREG32(index_reg, 0x30501);
	WREG32(data_reg, 0xBF7884E0);
	WREG32(index_reg, 0x30600);
	WREG32(data_reg, 0x8BA0BED8);
	WREG32(index_reg, 0x30601);
	WREG32(data_reg, 0xBF508640);
	WREG32(index_reg, 0x30700);
	WREG32(data_reg, 0x8A60BEE8);
	WREG32(index_reg, 0x30701);
	WREG32(data_reg, 0xBF2087A0);
	WREG32(index_reg, 0x30800);
	WREG32(data_reg, 0x8900BF00);
	WREG32(index_reg, 0x30801);
	WREG32(data_reg, 0xBF008900);
पूर्ण

काष्ठा rv515_watermark अणु
	u32        lb_request_fअगरo_depth;
	fixed20_12 num_line_pair;
	fixed20_12 estimated_width;
	fixed20_12 worst_हाल_latency;
	fixed20_12 consumption_rate;
	fixed20_12 active_समय;
	fixed20_12 dbpp;
	fixed20_12 priority_mark_max;
	fixed20_12 priority_mark;
	fixed20_12 sclk;
पूर्ण;

अटल व्योम rv515_crtc_bandwidth_compute(काष्ठा radeon_device *rdev,
					 काष्ठा radeon_crtc *crtc,
					 काष्ठा rv515_watermark *wm,
					 bool low)
अणु
	काष्ठा drm_display_mode *mode = &crtc->base.mode;
	fixed20_12 a, b, c;
	fixed20_12 pclk, request_fअगरo_depth, tolerable_latency, estimated_width;
	fixed20_12 consumption_समय, line_समय, chunk_समय, पढ़ो_delay_latency;
	fixed20_12 sclk;
	u32 selected_sclk;

	अगर (!crtc->base.enabled) अणु
		/* FIXME: wouldn't it better to set priority mark to maximum */
		wm->lb_request_fअगरo_depth = 4;
		वापस;
	पूर्ण

	/* rv6xx, rv7xx */
	अगर ((rdev->family >= CHIP_RV610) &&
	    (rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled)
		selected_sclk = radeon_dpm_get_sclk(rdev, low);
	अन्यथा
		selected_sclk = rdev->pm.current_sclk;

	/* sclk in Mhz */
	a.full = dfixed_स्थिर(100);
	sclk.full = dfixed_स्थिर(selected_sclk);
	sclk.full = dfixed_भाग(sclk, a);

	अगर (crtc->vsc.full > dfixed_स्थिर(2))
		wm->num_line_pair.full = dfixed_स्थिर(2);
	अन्यथा
		wm->num_line_pair.full = dfixed_स्थिर(1);

	b.full = dfixed_स्थिर(mode->crtc_hdisplay);
	c.full = dfixed_स्थिर(256);
	a.full = dfixed_भाग(b, c);
	request_fअगरo_depth.full = dfixed_mul(a, wm->num_line_pair);
	request_fअगरo_depth.full = dfixed_उच्चमान(request_fअगरo_depth);
	अगर (a.full < dfixed_स्थिर(4)) अणु
		wm->lb_request_fअगरo_depth = 4;
	पूर्ण अन्यथा अणु
		wm->lb_request_fअगरo_depth = dfixed_trunc(request_fअगरo_depth);
	पूर्ण

	/* Determine consumption rate
	 *  pclk = pixel घड़ी period(ns) = 1000 / (mode.घड़ी / 1000)
	 *  vtaps = number of vertical taps,
	 *  vsc = vertical scaling ratio, defined as source/destination
	 *  hsc = horizontal scaling ration, defined as source/destination
	 */
	a.full = dfixed_स्थिर(mode->घड़ी);
	b.full = dfixed_स्थिर(1000);
	a.full = dfixed_भाग(a, b);
	pclk.full = dfixed_भाग(b, a);
	अगर (crtc->rmx_type != RMX_OFF) अणु
		b.full = dfixed_स्थिर(2);
		अगर (crtc->vsc.full > b.full)
			b.full = crtc->vsc.full;
		b.full = dfixed_mul(b, crtc->hsc);
		c.full = dfixed_स्थिर(2);
		b.full = dfixed_भाग(b, c);
		consumption_समय.full = dfixed_भाग(pclk, b);
	पूर्ण अन्यथा अणु
		consumption_समय.full = pclk.full;
	पूर्ण
	a.full = dfixed_स्थिर(1);
	wm->consumption_rate.full = dfixed_भाग(a, consumption_समय);


	/* Determine line समय
	 *  LineTime = total समय क्रम one line of displayhtotal
	 *  LineTime = total number of horizontal pixels
	 *  pclk = pixel घड़ी period(ns)
	 */
	a.full = dfixed_स्थिर(crtc->base.mode.crtc_htotal);
	line_समय.full = dfixed_mul(a, pclk);

	/* Determine active समय
	 *  ActiveTime = समय of active region of display within one line,
	 *  hactive = total number of horizontal active pixels
	 *  htotal = total number of horizontal pixels
	 */
	a.full = dfixed_स्थिर(crtc->base.mode.crtc_htotal);
	b.full = dfixed_स्थिर(crtc->base.mode.crtc_hdisplay);
	wm->active_समय.full = dfixed_mul(line_समय, b);
	wm->active_समय.full = dfixed_भाग(wm->active_समय, a);

	/* Determine chunk समय
	 * ChunkTime = the समय it takes the DCP to send one chunk of data
	 * to the LB which consists of pipeline delay and पूर्णांकer chunk gap
	 * sclk = प्रणाली घड़ी(Mhz)
	 */
	a.full = dfixed_स्थिर(600 * 1000);
	chunk_समय.full = dfixed_भाग(a, sclk);
	पढ़ो_delay_latency.full = dfixed_स्थिर(1000);

	/* Determine the worst हाल latency
	 * NumLinePair = Number of line pairs to request(1=2 lines, 2=4 lines)
	 * WorstCaseLatency = worst हाल समय from urgent to when the MC starts
	 *                    to वापस data
	 * READ_DELAY_IDLE_MAX = स्थिरant of 1us
	 * ChunkTime = समय it takes the DCP to send one chunk of data to the LB
	 *             which consists of pipeline delay and पूर्णांकer chunk gap
	 */
	अगर (dfixed_trunc(wm->num_line_pair) > 1) अणु
		a.full = dfixed_स्थिर(3);
		wm->worst_हाल_latency.full = dfixed_mul(a, chunk_समय);
		wm->worst_हाल_latency.full += पढ़ो_delay_latency.full;
	पूर्ण अन्यथा अणु
		wm->worst_हाल_latency.full = chunk_समय.full + पढ़ो_delay_latency.full;
	पूर्ण

	/* Determine the tolerable latency
	 * TolerableLatency = Any given request has only 1 line समय
	 *                    क्रम the data to be वापसed
	 * LBRequestFअगरoDepth = Number of chunk requests the LB can
	 *                      put पूर्णांकo the request FIFO क्रम a display
	 *  LineTime = total समय क्रम one line of display
	 *  ChunkTime = the समय it takes the DCP to send one chunk
	 *              of data to the LB which consists of
	 *  pipeline delay and पूर्णांकer chunk gap
	 */
	अगर ((2+wm->lb_request_fअगरo_depth) >= dfixed_trunc(request_fअगरo_depth)) अणु
		tolerable_latency.full = line_समय.full;
	पूर्ण अन्यथा अणु
		tolerable_latency.full = dfixed_स्थिर(wm->lb_request_fअगरo_depth - 2);
		tolerable_latency.full = request_fअगरo_depth.full - tolerable_latency.full;
		tolerable_latency.full = dfixed_mul(tolerable_latency, chunk_समय);
		tolerable_latency.full = line_समय.full - tolerable_latency.full;
	पूर्ण
	/* We assume worst हाल 32bits (4 bytes) */
	wm->dbpp.full = dfixed_स्थिर(2 * 16);

	/* Determine the maximum priority mark
	 *  width = viewport width in pixels
	 */
	a.full = dfixed_स्थिर(16);
	wm->priority_mark_max.full = dfixed_स्थिर(crtc->base.mode.crtc_hdisplay);
	wm->priority_mark_max.full = dfixed_भाग(wm->priority_mark_max, a);
	wm->priority_mark_max.full = dfixed_उच्चमान(wm->priority_mark_max);

	/* Determine estimated width */
	estimated_width.full = tolerable_latency.full - wm->worst_हाल_latency.full;
	estimated_width.full = dfixed_भाग(estimated_width, consumption_समय);
	अगर (dfixed_trunc(estimated_width) > crtc->base.mode.crtc_hdisplay) अणु
		wm->priority_mark.full = wm->priority_mark_max.full;
	पूर्ण अन्यथा अणु
		a.full = dfixed_स्थिर(16);
		wm->priority_mark.full = dfixed_भाग(estimated_width, a);
		wm->priority_mark.full = dfixed_उच्चमान(wm->priority_mark);
		wm->priority_mark.full = wm->priority_mark_max.full - wm->priority_mark.full;
	पूर्ण
पूर्ण

अटल व्योम rv515_compute_mode_priority(काष्ठा radeon_device *rdev,
					काष्ठा rv515_watermark *wm0,
					काष्ठा rv515_watermark *wm1,
					काष्ठा drm_display_mode *mode0,
					काष्ठा drm_display_mode *mode1,
					u32 *d1mode_priority_a_cnt,
					u32 *d2mode_priority_a_cnt)
अणु
	fixed20_12 priority_mark02, priority_mark12, fill_rate;
	fixed20_12 a, b;

	*d1mode_priority_a_cnt = MODE_PRIORITY_OFF;
	*d2mode_priority_a_cnt = MODE_PRIORITY_OFF;

	अगर (mode0 && mode1) अणु
		अगर (dfixed_trunc(wm0->dbpp) > 64)
			a.full = dfixed_भाग(wm0->dbpp, wm0->num_line_pair);
		अन्यथा
			a.full = wm0->num_line_pair.full;
		अगर (dfixed_trunc(wm1->dbpp) > 64)
			b.full = dfixed_भाग(wm1->dbpp, wm1->num_line_pair);
		अन्यथा
			b.full = wm1->num_line_pair.full;
		a.full += b.full;
		fill_rate.full = dfixed_भाग(wm0->sclk, a);
		अगर (wm0->consumption_rate.full > fill_rate.full) अणु
			b.full = wm0->consumption_rate.full - fill_rate.full;
			b.full = dfixed_mul(b, wm0->active_समय);
			a.full = dfixed_स्थिर(16);
			b.full = dfixed_भाग(b, a);
			a.full = dfixed_mul(wm0->worst_हाल_latency,
						wm0->consumption_rate);
			priority_mark02.full = a.full + b.full;
		पूर्ण अन्यथा अणु
			a.full = dfixed_mul(wm0->worst_हाल_latency,
						wm0->consumption_rate);
			b.full = dfixed_स्थिर(16 * 1000);
			priority_mark02.full = dfixed_भाग(a, b);
		पूर्ण
		अगर (wm1->consumption_rate.full > fill_rate.full) अणु
			b.full = wm1->consumption_rate.full - fill_rate.full;
			b.full = dfixed_mul(b, wm1->active_समय);
			a.full = dfixed_स्थिर(16);
			b.full = dfixed_भाग(b, a);
			a.full = dfixed_mul(wm1->worst_हाल_latency,
						wm1->consumption_rate);
			priority_mark12.full = a.full + b.full;
		पूर्ण अन्यथा अणु
			a.full = dfixed_mul(wm1->worst_हाल_latency,
						wm1->consumption_rate);
			b.full = dfixed_स्थिर(16 * 1000);
			priority_mark12.full = dfixed_भाग(a, b);
		पूर्ण
		अगर (wm0->priority_mark.full > priority_mark02.full)
			priority_mark02.full = wm0->priority_mark.full;
		अगर (wm0->priority_mark_max.full > priority_mark02.full)
			priority_mark02.full = wm0->priority_mark_max.full;
		अगर (wm1->priority_mark.full > priority_mark12.full)
			priority_mark12.full = wm1->priority_mark.full;
		अगर (wm1->priority_mark_max.full > priority_mark12.full)
			priority_mark12.full = wm1->priority_mark_max.full;
		*d1mode_priority_a_cnt = dfixed_trunc(priority_mark02);
		*d2mode_priority_a_cnt = dfixed_trunc(priority_mark12);
		अगर (rdev->disp_priority == 2) अणु
			*d1mode_priority_a_cnt |= MODE_PRIORITY_ALWAYS_ON;
			*d2mode_priority_a_cnt |= MODE_PRIORITY_ALWAYS_ON;
		पूर्ण
	पूर्ण अन्यथा अगर (mode0) अणु
		अगर (dfixed_trunc(wm0->dbpp) > 64)
			a.full = dfixed_भाग(wm0->dbpp, wm0->num_line_pair);
		अन्यथा
			a.full = wm0->num_line_pair.full;
		fill_rate.full = dfixed_भाग(wm0->sclk, a);
		अगर (wm0->consumption_rate.full > fill_rate.full) अणु
			b.full = wm0->consumption_rate.full - fill_rate.full;
			b.full = dfixed_mul(b, wm0->active_समय);
			a.full = dfixed_स्थिर(16);
			b.full = dfixed_भाग(b, a);
			a.full = dfixed_mul(wm0->worst_हाल_latency,
						wm0->consumption_rate);
			priority_mark02.full = a.full + b.full;
		पूर्ण अन्यथा अणु
			a.full = dfixed_mul(wm0->worst_हाल_latency,
						wm0->consumption_rate);
			b.full = dfixed_स्थिर(16);
			priority_mark02.full = dfixed_भाग(a, b);
		पूर्ण
		अगर (wm0->priority_mark.full > priority_mark02.full)
			priority_mark02.full = wm0->priority_mark.full;
		अगर (wm0->priority_mark_max.full > priority_mark02.full)
			priority_mark02.full = wm0->priority_mark_max.full;
		*d1mode_priority_a_cnt = dfixed_trunc(priority_mark02);
		अगर (rdev->disp_priority == 2)
			*d1mode_priority_a_cnt |= MODE_PRIORITY_ALWAYS_ON;
	पूर्ण अन्यथा अगर (mode1) अणु
		अगर (dfixed_trunc(wm1->dbpp) > 64)
			a.full = dfixed_भाग(wm1->dbpp, wm1->num_line_pair);
		अन्यथा
			a.full = wm1->num_line_pair.full;
		fill_rate.full = dfixed_भाग(wm1->sclk, a);
		अगर (wm1->consumption_rate.full > fill_rate.full) अणु
			b.full = wm1->consumption_rate.full - fill_rate.full;
			b.full = dfixed_mul(b, wm1->active_समय);
			a.full = dfixed_स्थिर(16);
			b.full = dfixed_भाग(b, a);
			a.full = dfixed_mul(wm1->worst_हाल_latency,
						wm1->consumption_rate);
			priority_mark12.full = a.full + b.full;
		पूर्ण अन्यथा अणु
			a.full = dfixed_mul(wm1->worst_हाल_latency,
						wm1->consumption_rate);
			b.full = dfixed_स्थिर(16 * 1000);
			priority_mark12.full = dfixed_भाग(a, b);
		पूर्ण
		अगर (wm1->priority_mark.full > priority_mark12.full)
			priority_mark12.full = wm1->priority_mark.full;
		अगर (wm1->priority_mark_max.full > priority_mark12.full)
			priority_mark12.full = wm1->priority_mark_max.full;
		*d2mode_priority_a_cnt = dfixed_trunc(priority_mark12);
		अगर (rdev->disp_priority == 2)
			*d2mode_priority_a_cnt |= MODE_PRIORITY_ALWAYS_ON;
	पूर्ण
पूर्ण

व्योम rv515_bandwidth_avivo_update(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_display_mode *mode0 = शून्य;
	काष्ठा drm_display_mode *mode1 = शून्य;
	काष्ठा rv515_watermark wm0_high, wm0_low;
	काष्ठा rv515_watermark wm1_high, wm1_low;
	u32 पंचांगp;
	u32 d1mode_priority_a_cnt, d1mode_priority_b_cnt;
	u32 d2mode_priority_a_cnt, d2mode_priority_b_cnt;

	अगर (rdev->mode_info.crtcs[0]->base.enabled)
		mode0 = &rdev->mode_info.crtcs[0]->base.mode;
	अगर (rdev->mode_info.crtcs[1]->base.enabled)
		mode1 = &rdev->mode_info.crtcs[1]->base.mode;
	rs690_line_buffer_adjust(rdev, mode0, mode1);

	rv515_crtc_bandwidth_compute(rdev, rdev->mode_info.crtcs[0], &wm0_high, false);
	rv515_crtc_bandwidth_compute(rdev, rdev->mode_info.crtcs[1], &wm1_high, false);

	rv515_crtc_bandwidth_compute(rdev, rdev->mode_info.crtcs[0], &wm0_low, false);
	rv515_crtc_bandwidth_compute(rdev, rdev->mode_info.crtcs[1], &wm1_low, false);

	पंचांगp = wm0_high.lb_request_fअगरo_depth;
	पंचांगp |= wm1_high.lb_request_fअगरo_depth << 16;
	WREG32(LB_MAX_REQ_OUTSTANDING, पंचांगp);

	rv515_compute_mode_priority(rdev,
				    &wm0_high, &wm1_high,
				    mode0, mode1,
				    &d1mode_priority_a_cnt, &d2mode_priority_a_cnt);
	rv515_compute_mode_priority(rdev,
				    &wm0_low, &wm1_low,
				    mode0, mode1,
				    &d1mode_priority_b_cnt, &d2mode_priority_b_cnt);

	WREG32(D1MODE_PRIORITY_A_CNT, d1mode_priority_a_cnt);
	WREG32(D1MODE_PRIORITY_B_CNT, d1mode_priority_b_cnt);
	WREG32(D2MODE_PRIORITY_A_CNT, d2mode_priority_a_cnt);
	WREG32(D2MODE_PRIORITY_B_CNT, d2mode_priority_b_cnt);
पूर्ण

व्योम rv515_bandwidth_update(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t पंचांगp;
	काष्ठा drm_display_mode *mode0 = शून्य;
	काष्ठा drm_display_mode *mode1 = शून्य;

	अगर (!rdev->mode_info.mode_config_initialized)
		वापस;

	radeon_update_display_priority(rdev);

	अगर (rdev->mode_info.crtcs[0]->base.enabled)
		mode0 = &rdev->mode_info.crtcs[0]->base.mode;
	अगर (rdev->mode_info.crtcs[1]->base.enabled)
		mode1 = &rdev->mode_info.crtcs[1]->base.mode;
	/*
	 * Set display0/1 priority up in the memory controller क्रम
	 * modes अगर the user specअगरies HIGH क्रम displaypriority
	 * option.
	 */
	अगर ((rdev->disp_priority == 2) &&
	    (rdev->family == CHIP_RV515)) अणु
		पंचांगp = RREG32_MC(MC_MISC_LAT_TIMER);
		पंचांगp &= ~MC_DISP1R_INIT_LAT_MASK;
		पंचांगp &= ~MC_DISP0R_INIT_LAT_MASK;
		अगर (mode1)
			पंचांगp |= (1 << MC_DISP1R_INIT_LAT_SHIFT);
		अगर (mode0)
			पंचांगp |= (1 << MC_DISP0R_INIT_LAT_SHIFT);
		WREG32_MC(MC_MISC_LAT_TIMER, पंचांगp);
	पूर्ण
	rv515_bandwidth_avivo_update(rdev);
पूर्ण
