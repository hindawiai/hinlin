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

#समावेश "atom.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_audio.h"
#समावेश "rs690d.h"

पूर्णांक rs690_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;
	uपूर्णांक32_t पंचांगp;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		/* पढ़ो MC_STATUS */
		पंचांगp = RREG32_MC(R_000090_MC_SYSTEM_STATUS);
		अगर (G_000090_MC_SYSTEM_IDLE(पंचांगp))
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम rs690_gpu_init(काष्ठा radeon_device *rdev)
अणु
	/* FIXME: is this correct ? */
	r420_pipes_init(rdev);
	अगर (rs690_mc_रुको_क्रम_idle(rdev)) अणु
		pr_warn("Failed to wait MC idle while programming pipes. Bad things might happen.\n");
	पूर्ण
पूर्ण

जोड़ igp_info अणु
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO info;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V2 info_v2;
पूर्ण;

व्योम rs690_pm_info(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, IntegratedSystemInfo);
	जोड़ igp_info *info;
	uपूर्णांक16_t data_offset;
	uपूर्णांक8_t frev, crev;
	fixed20_12 पंचांगp;

	अगर (atom_parse_data_header(rdev->mode_info.atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		info = (जोड़ igp_info *)(rdev->mode_info.atom_context->bios + data_offset);

		/* Get various प्रणाली inक्रमmations from bios */
		चयन (crev) अणु
		हाल 1:
			पंचांगp.full = dfixed_स्थिर(100);
			rdev->pm.igp_sideport_mclk.full = dfixed_स्थिर(le32_to_cpu(info->info.ulBootUpMemoryClock));
			rdev->pm.igp_sideport_mclk.full = dfixed_भाग(rdev->pm.igp_sideport_mclk, पंचांगp);
			अगर (le16_to_cpu(info->info.usK8MemoryClock))
				rdev->pm.igp_प्रणाली_mclk.full = dfixed_स्थिर(le16_to_cpu(info->info.usK8MemoryClock));
			अन्यथा अगर (rdev->घड़ी.शेष_mclk) अणु
				rdev->pm.igp_प्रणाली_mclk.full = dfixed_स्थिर(rdev->घड़ी.शेष_mclk);
				rdev->pm.igp_प्रणाली_mclk.full = dfixed_भाग(rdev->pm.igp_प्रणाली_mclk, पंचांगp);
			पूर्ण अन्यथा
				rdev->pm.igp_प्रणाली_mclk.full = dfixed_स्थिर(400);
			rdev->pm.igp_ht_link_clk.full = dfixed_स्थिर(le16_to_cpu(info->info.usFSBClock));
			rdev->pm.igp_ht_link_width.full = dfixed_स्थिर(info->info.ucHTLinkWidth);
			अवरोध;
		हाल 2:
			पंचांगp.full = dfixed_स्थिर(100);
			rdev->pm.igp_sideport_mclk.full = dfixed_स्थिर(le32_to_cpu(info->info_v2.ulBootUpSidePortClock));
			rdev->pm.igp_sideport_mclk.full = dfixed_भाग(rdev->pm.igp_sideport_mclk, पंचांगp);
			अगर (le32_to_cpu(info->info_v2.ulBootUpUMAClock))
				rdev->pm.igp_प्रणाली_mclk.full = dfixed_स्थिर(le32_to_cpu(info->info_v2.ulBootUpUMAClock));
			अन्यथा अगर (rdev->घड़ी.शेष_mclk)
				rdev->pm.igp_प्रणाली_mclk.full = dfixed_स्थिर(rdev->घड़ी.शेष_mclk);
			अन्यथा
				rdev->pm.igp_प्रणाली_mclk.full = dfixed_स्थिर(66700);
			rdev->pm.igp_प्रणाली_mclk.full = dfixed_भाग(rdev->pm.igp_प्रणाली_mclk, पंचांगp);
			rdev->pm.igp_ht_link_clk.full = dfixed_स्थिर(le32_to_cpu(info->info_v2.ulHTLinkFreq));
			rdev->pm.igp_ht_link_clk.full = dfixed_भाग(rdev->pm.igp_ht_link_clk, पंचांगp);
			rdev->pm.igp_ht_link_width.full = dfixed_स्थिर(le16_to_cpu(info->info_v2.usMinHTLinkWidth));
			अवरोध;
		शेष:
			/* We assume the slower possible घड़ी ie worst हाल */
			rdev->pm.igp_sideport_mclk.full = dfixed_स्थिर(200);
			rdev->pm.igp_प्रणाली_mclk.full = dfixed_स्थिर(200);
			rdev->pm.igp_ht_link_clk.full = dfixed_स्थिर(1000);
			rdev->pm.igp_ht_link_width.full = dfixed_स्थिर(8);
			DRM_ERROR("No integrated system info for your GPU, using safe default\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* We assume the slower possible घड़ी ie worst हाल */
		rdev->pm.igp_sideport_mclk.full = dfixed_स्थिर(200);
		rdev->pm.igp_प्रणाली_mclk.full = dfixed_स्थिर(200);
		rdev->pm.igp_ht_link_clk.full = dfixed_स्थिर(1000);
		rdev->pm.igp_ht_link_width.full = dfixed_स्थिर(8);
		DRM_ERROR("No integrated system info for your GPU, using safe default\n");
	पूर्ण
	/* Compute various bandwidth */
	/* k8_bandwidth = (memory_clk / 2) * 2 * 8 * 0.5 = memory_clk * 4  */
	पंचांगp.full = dfixed_स्थिर(4);
	rdev->pm.k8_bandwidth.full = dfixed_mul(rdev->pm.igp_प्रणाली_mclk, पंचांगp);
	/* ht_bandwidth = ht_clk * 2 * ht_width / 8 * 0.8
	 *              = ht_clk * ht_width / 5
	 */
	पंचांगp.full = dfixed_स्थिर(5);
	rdev->pm.ht_bandwidth.full = dfixed_mul(rdev->pm.igp_ht_link_clk,
						rdev->pm.igp_ht_link_width);
	rdev->pm.ht_bandwidth.full = dfixed_भाग(rdev->pm.ht_bandwidth, पंचांगp);
	अगर (पंचांगp.full < rdev->pm.max_bandwidth.full) अणु
		/* HT link is a limiting factor */
		rdev->pm.max_bandwidth.full = पंचांगp.full;
	पूर्ण
	/* sideport_bandwidth = (sideport_clk / 2) * 2 * 2 * 0.7
	 *                    = (sideport_clk * 14) / 10
	 */
	पंचांगp.full = dfixed_स्थिर(14);
	rdev->pm.sideport_bandwidth.full = dfixed_mul(rdev->pm.igp_sideport_mclk, पंचांगp);
	पंचांगp.full = dfixed_स्थिर(10);
	rdev->pm.sideport_bandwidth.full = dfixed_भाग(rdev->pm.sideport_bandwidth, पंचांगp);
पूर्ण

अटल व्योम rs690_mc_init(काष्ठा radeon_device *rdev)
अणु
	u64 base;
	uपूर्णांक32_t h_addr, l_addr;
	अचिन्हित दीर्घ दीर्घ k8_addr;

	rs400_gart_adjust_size(rdev);
	rdev->mc.vram_is_ddr = true;
	rdev->mc.vram_width = 128;
	rdev->mc.real_vram_size = RREG32(RADEON_CONFIG_MEMSIZE);
	rdev->mc.mc_vram_size = rdev->mc.real_vram_size;
	rdev->mc.aper_base = pci_resource_start(rdev->pdev, 0);
	rdev->mc.aper_size = pci_resource_len(rdev->pdev, 0);
	rdev->mc.visible_vram_size = rdev->mc.aper_size;
	base = RREG32_MC(R_000100_MCCFG_FB_LOCATION);
	base = G_000100_MC_FB_START(base) << 16;
	rdev->mc.igp_sideport_enabled = radeon_atombios_sideport_present(rdev);
	/* Some boards seem to be configured क्रम 128MB of sideport memory,
	 * but really only have 64MB.  Just skip the sideport and use
	 * UMA memory.
	 */
	अगर (rdev->mc.igp_sideport_enabled &&
	    (rdev->mc.real_vram_size == (384 * 1024 * 1024))) अणु
		base += 128 * 1024 * 1024;
		rdev->mc.real_vram_size -= 128 * 1024 * 1024;
		rdev->mc.mc_vram_size = rdev->mc.real_vram_size;
	पूर्ण

	/* Use K8 direct mapping क्रम fast fb access. */ 
	rdev->fastfb_working = false;
	h_addr = G_00005F_K8_ADDR_EXT(RREG32_MC(R_00005F_MC_MISC_UMA_CNTL));
	l_addr = RREG32_MC(R_00001E_K8_FB_LOCATION);
	k8_addr = ((अचिन्हित दीर्घ दीर्घ)h_addr) << 32 | l_addr;
#अगर defined(CONFIG_X86_32) && !defined(CONFIG_X86_PAE)
	अगर (k8_addr + rdev->mc.visible_vram_size < 0x100000000ULL)	
#पूर्ण_अगर
	अणु
		/* FastFB shall be used with UMA memory. Here it is simply disabled when sideport 
		 * memory is present.
		 */
		अगर (!rdev->mc.igp_sideport_enabled && radeon_fastfb == 1) अणु
			DRM_INFO("Direct mapping: aper base at 0x%llx, replaced by direct mapping base 0x%llx.\n", 
					(अचिन्हित दीर्घ दीर्घ)rdev->mc.aper_base, k8_addr);
			rdev->mc.aper_base = (resource_माप_प्रकार)k8_addr;
			rdev->fastfb_working = true;
		पूर्ण
	पूर्ण  

	rs690_pm_info(rdev);
	radeon_vram_location(rdev, &rdev->mc, base);
	rdev->mc.gtt_base_align = rdev->mc.gtt_size - 1;
	radeon_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);
पूर्ण

व्योम rs690_line_buffer_adjust(काष्ठा radeon_device *rdev,
			      काष्ठा drm_display_mode *mode1,
			      काष्ठा drm_display_mode *mode2)
अणु
	u32 पंचांगp;

	/* Guess line buffer size to be 8192 pixels */
	u32 lb_size = 8192;

	/*
	 * Line Buffer Setup
	 * There is a single line buffer shared by both display controllers.
	 * R_006520_DC_LB_MEMORY_SPLIT controls how that line buffer is shared between
	 * the display controllers.  The paritioning can either be करोne
	 * manually or via one of four preset allocations specअगरied in bits 1:0:
	 *  0 - line buffer is भागided in half and shared between crtc
	 *  1 - D1 माला_लो 3/4 of the line buffer, D2 माला_लो 1/4
	 *  2 - D1 माला_लो the whole buffer
	 *  3 - D1 माला_लो 1/4 of the line buffer, D2 माला_लो 3/4
	 * Setting bit 2 of R_006520_DC_LB_MEMORY_SPLIT controls चयनes to manual
	 * allocation mode. In manual allocation mode, D1 always starts at 0,
	 * D1 end/2 is specअगरied in bits 14:4; D2 allocation follows D1.
	 */
	पंचांगp = RREG32(R_006520_DC_LB_MEMORY_SPLIT) & C_006520_DC_LB_MEMORY_SPLIT;
	पंचांगp &= ~C_006520_DC_LB_MEMORY_SPLIT_MODE;
	/* स्वतः */
	अगर (mode1 && mode2) अणु
		अगर (mode1->hdisplay > mode2->hdisplay) अणु
			अगर (mode1->hdisplay > 2560)
				पंचांगp |= V_006520_DC_LB_MEMORY_SPLIT_D1_3Q_D2_1Q;
			अन्यथा
				पंचांगp |= V_006520_DC_LB_MEMORY_SPLIT_D1HALF_D2HALF;
		पूर्ण अन्यथा अगर (mode2->hdisplay > mode1->hdisplay) अणु
			अगर (mode2->hdisplay > 2560)
				पंचांगp |= V_006520_DC_LB_MEMORY_SPLIT_D1_1Q_D2_3Q;
			अन्यथा
				पंचांगp |= V_006520_DC_LB_MEMORY_SPLIT_D1HALF_D2HALF;
		पूर्ण अन्यथा
			पंचांगp |= V_006520_DC_LB_MEMORY_SPLIT_D1HALF_D2HALF;
	पूर्ण अन्यथा अगर (mode1) अणु
		पंचांगp |= V_006520_DC_LB_MEMORY_SPLIT_D1_ONLY;
	पूर्ण अन्यथा अगर (mode2) अणु
		पंचांगp |= V_006520_DC_LB_MEMORY_SPLIT_D1_1Q_D2_3Q;
	पूर्ण
	WREG32(R_006520_DC_LB_MEMORY_SPLIT, पंचांगp);

	/* Save number of lines the linebuffer leads beक्रमe the scanout */
	अगर (mode1)
		rdev->mode_info.crtcs[0]->lb_vblank_lead_lines = DIV_ROUND_UP(lb_size, mode1->crtc_hdisplay);

	अगर (mode2)
		rdev->mode_info.crtcs[1]->lb_vblank_lead_lines = DIV_ROUND_UP(lb_size, mode2->crtc_hdisplay);
पूर्ण

काष्ठा rs690_watermark अणु
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

अटल व्योम rs690_crtc_bandwidth_compute(काष्ठा radeon_device *rdev,
					 काष्ठा radeon_crtc *crtc,
					 काष्ठा rs690_watermark *wm,
					 bool low)
अणु
	काष्ठा drm_display_mode *mode = &crtc->base.mode;
	fixed20_12 a, b, c;
	fixed20_12 pclk, request_fअगरo_depth, tolerable_latency, estimated_width;
	fixed20_12 consumption_समय, line_समय, chunk_समय, पढ़ो_delay_latency;
	fixed20_12 sclk, core_bandwidth, max_bandwidth;
	u32 selected_sclk;

	अगर (!crtc->base.enabled) अणु
		/* FIXME: wouldn't it better to set priority mark to maximum */
		wm->lb_request_fअगरo_depth = 4;
		वापस;
	पूर्ण

	अगर (((rdev->family == CHIP_RS780) || (rdev->family == CHIP_RS880)) &&
	    (rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled)
		selected_sclk = radeon_dpm_get_sclk(rdev, low);
	अन्यथा
		selected_sclk = rdev->pm.current_sclk;

	/* sclk in Mhz */
	a.full = dfixed_स्थिर(100);
	sclk.full = dfixed_स्थिर(selected_sclk);
	sclk.full = dfixed_भाग(sclk, a);

	/* core_bandwidth = sclk(Mhz) * 16 */
	a.full = dfixed_स्थिर(16);
	core_bandwidth.full = dfixed_भाग(rdev->pm.sclk, a);

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

	/* Maximun bandwidth is the minimun bandwidth of all component */
	max_bandwidth = core_bandwidth;
	अगर (rdev->mc.igp_sideport_enabled) अणु
		अगर (max_bandwidth.full > rdev->pm.sideport_bandwidth.full &&
			rdev->pm.sideport_bandwidth.full)
			max_bandwidth = rdev->pm.sideport_bandwidth;
		पढ़ो_delay_latency.full = dfixed_स्थिर(370 * 800);
		a.full = dfixed_स्थिर(1000);
		b.full = dfixed_भाग(rdev->pm.igp_sideport_mclk, a);
		पढ़ो_delay_latency.full = dfixed_भाग(पढ़ो_delay_latency, b);
		पढ़ो_delay_latency.full = dfixed_mul(पढ़ो_delay_latency, a);
	पूर्ण अन्यथा अणु
		अगर (max_bandwidth.full > rdev->pm.k8_bandwidth.full &&
			rdev->pm.k8_bandwidth.full)
			max_bandwidth = rdev->pm.k8_bandwidth;
		अगर (max_bandwidth.full > rdev->pm.ht_bandwidth.full &&
			rdev->pm.ht_bandwidth.full)
			max_bandwidth = rdev->pm.ht_bandwidth;
		पढ़ो_delay_latency.full = dfixed_स्थिर(5000);
	पूर्ण

	/* sclk = प्रणाली घड़ीs(ns) = 1000 / max_bandwidth / 16 */
	a.full = dfixed_स्थिर(16);
	sclk.full = dfixed_mul(max_bandwidth, a);
	a.full = dfixed_स्थिर(1000);
	sclk.full = dfixed_भाग(a, sclk);
	/* Determine chunk समय
	 * ChunkTime = the समय it takes the DCP to send one chunk of data
	 * to the LB which consists of pipeline delay and पूर्णांकer chunk gap
	 * sclk = प्रणाली घड़ी(ns)
	 */
	a.full = dfixed_स्थिर(256 * 13);
	chunk_समय.full = dfixed_mul(sclk, a);
	a.full = dfixed_स्थिर(10);
	chunk_समय.full = dfixed_भाग(chunk_समय, a);

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
		a.full = dfixed_स्थिर(2);
		wm->worst_हाल_latency.full = dfixed_mul(a, chunk_समय);
		wm->worst_हाल_latency.full += पढ़ो_delay_latency.full;
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
	wm->dbpp.full = dfixed_स्थिर(4 * 8);

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
		wm->priority_mark.full = dfixed_स्थिर(10);
	पूर्ण अन्यथा अणु
		a.full = dfixed_स्थिर(16);
		wm->priority_mark.full = dfixed_भाग(estimated_width, a);
		wm->priority_mark.full = dfixed_उच्चमान(wm->priority_mark);
		wm->priority_mark.full = wm->priority_mark_max.full - wm->priority_mark.full;
	पूर्ण
पूर्ण

अटल व्योम rs690_compute_mode_priority(काष्ठा radeon_device *rdev,
					काष्ठा rs690_watermark *wm0,
					काष्ठा rs690_watermark *wm1,
					काष्ठा drm_display_mode *mode0,
					काष्ठा drm_display_mode *mode1,
					u32 *d1mode_priority_a_cnt,
					u32 *d2mode_priority_a_cnt)
अणु
	fixed20_12 priority_mark02, priority_mark12, fill_rate;
	fixed20_12 a, b;

	*d1mode_priority_a_cnt = S_006548_D1MODE_PRIORITY_A_OFF(1);
	*d2mode_priority_a_cnt = S_006548_D1MODE_PRIORITY_A_OFF(1);

	अगर (mode0 && mode1) अणु
		अगर (dfixed_trunc(wm0->dbpp) > 64)
			a.full = dfixed_mul(wm0->dbpp, wm0->num_line_pair);
		अन्यथा
			a.full = wm0->num_line_pair.full;
		अगर (dfixed_trunc(wm1->dbpp) > 64)
			b.full = dfixed_mul(wm1->dbpp, wm1->num_line_pair);
		अन्यथा
			b.full = wm1->num_line_pair.full;
		a.full += b.full;
		fill_rate.full = dfixed_भाग(wm0->sclk, a);
		अगर (wm0->consumption_rate.full > fill_rate.full) अणु
			b.full = wm0->consumption_rate.full - fill_rate.full;
			b.full = dfixed_mul(b, wm0->active_समय);
			a.full = dfixed_mul(wm0->worst_हाल_latency,
						wm0->consumption_rate);
			a.full = a.full + b.full;
			b.full = dfixed_स्थिर(16 * 1000);
			priority_mark02.full = dfixed_भाग(a, b);
		पूर्ण अन्यथा अणु
			a.full = dfixed_mul(wm0->worst_हाल_latency,
						wm0->consumption_rate);
			b.full = dfixed_स्थिर(16 * 1000);
			priority_mark02.full = dfixed_भाग(a, b);
		पूर्ण
		अगर (wm1->consumption_rate.full > fill_rate.full) अणु
			b.full = wm1->consumption_rate.full - fill_rate.full;
			b.full = dfixed_mul(b, wm1->active_समय);
			a.full = dfixed_mul(wm1->worst_हाल_latency,
						wm1->consumption_rate);
			a.full = a.full + b.full;
			b.full = dfixed_स्थिर(16 * 1000);
			priority_mark12.full = dfixed_भाग(a, b);
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
			*d1mode_priority_a_cnt |= S_006548_D1MODE_PRIORITY_A_ALWAYS_ON(1);
			*d2mode_priority_a_cnt |= S_006D48_D2MODE_PRIORITY_A_ALWAYS_ON(1);
		पूर्ण
	पूर्ण अन्यथा अगर (mode0) अणु
		अगर (dfixed_trunc(wm0->dbpp) > 64)
			a.full = dfixed_mul(wm0->dbpp, wm0->num_line_pair);
		अन्यथा
			a.full = wm0->num_line_pair.full;
		fill_rate.full = dfixed_भाग(wm0->sclk, a);
		अगर (wm0->consumption_rate.full > fill_rate.full) अणु
			b.full = wm0->consumption_rate.full - fill_rate.full;
			b.full = dfixed_mul(b, wm0->active_समय);
			a.full = dfixed_mul(wm0->worst_हाल_latency,
						wm0->consumption_rate);
			a.full = a.full + b.full;
			b.full = dfixed_स्थिर(16 * 1000);
			priority_mark02.full = dfixed_भाग(a, b);
		पूर्ण अन्यथा अणु
			a.full = dfixed_mul(wm0->worst_हाल_latency,
						wm0->consumption_rate);
			b.full = dfixed_स्थिर(16 * 1000);
			priority_mark02.full = dfixed_भाग(a, b);
		पूर्ण
		अगर (wm0->priority_mark.full > priority_mark02.full)
			priority_mark02.full = wm0->priority_mark.full;
		अगर (wm0->priority_mark_max.full > priority_mark02.full)
			priority_mark02.full = wm0->priority_mark_max.full;
		*d1mode_priority_a_cnt = dfixed_trunc(priority_mark02);
		अगर (rdev->disp_priority == 2)
			*d1mode_priority_a_cnt |= S_006548_D1MODE_PRIORITY_A_ALWAYS_ON(1);
	पूर्ण अन्यथा अगर (mode1) अणु
		अगर (dfixed_trunc(wm1->dbpp) > 64)
			a.full = dfixed_mul(wm1->dbpp, wm1->num_line_pair);
		अन्यथा
			a.full = wm1->num_line_pair.full;
		fill_rate.full = dfixed_भाग(wm1->sclk, a);
		अगर (wm1->consumption_rate.full > fill_rate.full) अणु
			b.full = wm1->consumption_rate.full - fill_rate.full;
			b.full = dfixed_mul(b, wm1->active_समय);
			a.full = dfixed_mul(wm1->worst_हाल_latency,
						wm1->consumption_rate);
			a.full = a.full + b.full;
			b.full = dfixed_स्थिर(16 * 1000);
			priority_mark12.full = dfixed_भाग(a, b);
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
			*d2mode_priority_a_cnt |= S_006D48_D2MODE_PRIORITY_A_ALWAYS_ON(1);
	पूर्ण
पूर्ण

व्योम rs690_bandwidth_update(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_display_mode *mode0 = शून्य;
	काष्ठा drm_display_mode *mode1 = शून्य;
	काष्ठा rs690_watermark wm0_high, wm0_low;
	काष्ठा rs690_watermark wm1_high, wm1_low;
	u32 पंचांगp;
	u32 d1mode_priority_a_cnt, d1mode_priority_b_cnt;
	u32 d2mode_priority_a_cnt, d2mode_priority_b_cnt;

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
	    ((rdev->family == CHIP_RS690) || (rdev->family == CHIP_RS740))) अणु
		पंचांगp = RREG32_MC(R_000104_MC_INIT_MISC_LAT_TIMER);
		पंचांगp &= C_000104_MC_DISP0R_INIT_LAT;
		पंचांगp &= C_000104_MC_DISP1R_INIT_LAT;
		अगर (mode0)
			पंचांगp |= S_000104_MC_DISP0R_INIT_LAT(1);
		अगर (mode1)
			पंचांगp |= S_000104_MC_DISP1R_INIT_LAT(1);
		WREG32_MC(R_000104_MC_INIT_MISC_LAT_TIMER, पंचांगp);
	पूर्ण
	rs690_line_buffer_adjust(rdev, mode0, mode1);

	अगर ((rdev->family == CHIP_RS690) || (rdev->family == CHIP_RS740))
		WREG32(R_006C9C_DCP_CONTROL, 0);
	अगर ((rdev->family == CHIP_RS780) || (rdev->family == CHIP_RS880))
		WREG32(R_006C9C_DCP_CONTROL, 2);

	rs690_crtc_bandwidth_compute(rdev, rdev->mode_info.crtcs[0], &wm0_high, false);
	rs690_crtc_bandwidth_compute(rdev, rdev->mode_info.crtcs[1], &wm1_high, false);

	rs690_crtc_bandwidth_compute(rdev, rdev->mode_info.crtcs[0], &wm0_low, true);
	rs690_crtc_bandwidth_compute(rdev, rdev->mode_info.crtcs[1], &wm1_low, true);

	पंचांगp = (wm0_high.lb_request_fअगरo_depth - 1);
	पंचांगp |= (wm1_high.lb_request_fअगरo_depth - 1) << 16;
	WREG32(R_006D58_LB_MAX_REQ_OUTSTANDING, पंचांगp);

	rs690_compute_mode_priority(rdev,
				    &wm0_high, &wm1_high,
				    mode0, mode1,
				    &d1mode_priority_a_cnt, &d2mode_priority_a_cnt);
	rs690_compute_mode_priority(rdev,
				    &wm0_low, &wm1_low,
				    mode0, mode1,
				    &d1mode_priority_b_cnt, &d2mode_priority_b_cnt);

	WREG32(R_006548_D1MODE_PRIORITY_A_CNT, d1mode_priority_a_cnt);
	WREG32(R_00654C_D1MODE_PRIORITY_B_CNT, d1mode_priority_b_cnt);
	WREG32(R_006D48_D2MODE_PRIORITY_A_CNT, d2mode_priority_a_cnt);
	WREG32(R_006D4C_D2MODE_PRIORITY_B_CNT, d2mode_priority_b_cnt);
पूर्ण

uपूर्णांक32_t rs690_mc_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t r;

	spin_lock_irqsave(&rdev->mc_idx_lock, flags);
	WREG32(R_000078_MC_INDEX, S_000078_MC_IND_ADDR(reg));
	r = RREG32(R_00007C_MC_DATA);
	WREG32(R_000078_MC_INDEX, ~C_000078_MC_IND_ADDR);
	spin_unlock_irqrestore(&rdev->mc_idx_lock, flags);
	वापस r;
पूर्ण

व्योम rs690_mc_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rdev->mc_idx_lock, flags);
	WREG32(R_000078_MC_INDEX, S_000078_MC_IND_ADDR(reg) |
		S_000078_MC_IND_WR_EN(1));
	WREG32(R_00007C_MC_DATA, v);
	WREG32(R_000078_MC_INDEX, 0x7F);
	spin_unlock_irqrestore(&rdev->mc_idx_lock, flags);
पूर्ण

अटल व्योम rs690_mc_program(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv515_mc_save save;

	/* Stops all mc clients */
	rv515_mc_stop(rdev, &save);

	/* Wait क्रम mc idle */
	अगर (rs690_mc_रुको_क्रम_idle(rdev))
		dev_warn(rdev->dev, "Wait MC idle timeout before updating MC.\n");
	/* Program MC, should be a 32bits limited address space */
	WREG32_MC(R_000100_MCCFG_FB_LOCATION,
			S_000100_MC_FB_START(rdev->mc.vram_start >> 16) |
			S_000100_MC_FB_TOP(rdev->mc.vram_end >> 16));
	WREG32(R_000134_HDP_FB_LOCATION,
		S_000134_HDP_FB_START(rdev->mc.vram_start >> 16));

	rv515_mc_resume(rdev, &save);
पूर्ण

अटल पूर्णांक rs690_startup(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	rs690_mc_program(rdev);
	/* Resume घड़ी */
	rv515_घड़ी_startup(rdev);
	/* Initialize GPU configuration (# pipes, ...) */
	rs690_gpu_init(rdev);
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

	r = radeon_audio_init(rdev);
	अगर (r) अणु
		dev_err(rdev->dev, "failed initializing audio\n");
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rs690_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Make sur GART are not working */
	rs400_gart_disable(rdev);
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
	r = rs690_startup(rdev);
	अगर (r) अणु
		rdev->accel_working = false;
	पूर्ण
	वापस r;
पूर्ण

पूर्णांक rs690_suspend(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_suspend(rdev);
	radeon_audio_fini(rdev);
	r100_cp_disable(rdev);
	radeon_wb_disable(rdev);
	rs600_irq_disable(rdev);
	rs400_gart_disable(rdev);
	वापस 0;
पूर्ण

व्योम rs690_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_pm_fini(rdev);
	radeon_audio_fini(rdev);
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

पूर्णांक rs690_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* Disable VGA */
	rv515_vga_render_disable(rdev);
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

	/* Initialize घड़ीs */
	radeon_get_घड़ी_info(rdev->ddev);
	/* initialize memory controller */
	rs690_mc_init(rdev);
	rv515_debugfs(rdev);
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
	rs600_set_safe_रेजिस्टरs(rdev);

	/* Initialize घातer management */
	radeon_pm_init(rdev);

	rdev->accel_working = true;
	r = rs690_startup(rdev);
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
