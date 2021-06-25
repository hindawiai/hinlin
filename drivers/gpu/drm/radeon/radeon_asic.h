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
#अगर_अघोषित __RADEON_ASIC_H__
#घोषणा __RADEON_ASIC_H__

/*
 * common functions
 */
uपूर्णांक32_t radeon_legacy_get_engine_घड़ी(काष्ठा radeon_device *rdev);
व्योम radeon_legacy_set_engine_घड़ी(काष्ठा radeon_device *rdev, uपूर्णांक32_t eng_घड़ी);
uपूर्णांक32_t radeon_legacy_get_memory_घड़ी(काष्ठा radeon_device *rdev);
व्योम radeon_legacy_set_घड़ी_gating(काष्ठा radeon_device *rdev, पूर्णांक enable);

uपूर्णांक32_t radeon_atom_get_engine_घड़ी(काष्ठा radeon_device *rdev);
व्योम radeon_atom_set_engine_घड़ी(काष्ठा radeon_device *rdev, uपूर्णांक32_t eng_घड़ी);
uपूर्णांक32_t radeon_atom_get_memory_घड़ी(काष्ठा radeon_device *rdev);
व्योम radeon_atom_set_memory_घड़ी(काष्ठा radeon_device *rdev, uपूर्णांक32_t mem_घड़ी);
व्योम radeon_atom_set_घड़ी_gating(काष्ठा radeon_device *rdev, पूर्णांक enable);

व्योम atombios_set_backlight_level(काष्ठा radeon_encoder *radeon_encoder, u8 level);
u8 atombios_get_backlight_level(काष्ठा radeon_encoder *radeon_encoder);
व्योम radeon_legacy_set_backlight_level(काष्ठा radeon_encoder *radeon_encoder, u8 level);
u8 radeon_legacy_get_backlight_level(काष्ठा radeon_encoder *radeon_encoder);

/*
 * r100,rv100,rs100,rv200,rs200
 */
काष्ठा r100_mc_save अणु
	u32	GENMO_WT;
	u32	CRTC_EXT_CNTL;
	u32	CRTC_GEN_CNTL;
	u32	CRTC2_GEN_CNTL;
	u32	CUR_OFFSET;
	u32	CUR2_OFFSET;
पूर्ण;
पूर्णांक r100_init(काष्ठा radeon_device *rdev);
व्योम r100_fini(काष्ठा radeon_device *rdev);
पूर्णांक r100_suspend(काष्ठा radeon_device *rdev);
पूर्णांक r100_resume(काष्ठा radeon_device *rdev);
व्योम r100_vga_set_state(काष्ठा radeon_device *rdev, bool state);
bool r100_gpu_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
पूर्णांक r100_asic_reset(काष्ठा radeon_device *rdev, bool hard);
u32 r100_get_vblank_counter(काष्ठा radeon_device *rdev, पूर्णांक crtc);
व्योम r100_pci_gart_tlb_flush(काष्ठा radeon_device *rdev);
uपूर्णांक64_t r100_pci_gart_get_page_entry(uपूर्णांक64_t addr, uपूर्णांक32_t flags);
व्योम r100_pci_gart_set_page(काष्ठा radeon_device *rdev, अचिन्हित i,
			    uपूर्णांक64_t entry);
व्योम r100_ring_start(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
पूर्णांक r100_irq_set(काष्ठा radeon_device *rdev);
पूर्णांक r100_irq_process(काष्ठा radeon_device *rdev);
व्योम r100_fence_ring_emit(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_fence *fence);
bool r100_semaphore_ring_emit(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_ring *cp,
			      काष्ठा radeon_semaphore *semaphore,
			      bool emit_रुको);
पूर्णांक r100_cs_parse(काष्ठा radeon_cs_parser *p);
व्योम r100_pll_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v);
uपूर्णांक32_t r100_pll_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg);
काष्ठा radeon_fence *r100_copy_blit(काष्ठा radeon_device *rdev,
				    uपूर्णांक64_t src_offset,
				    uपूर्णांक64_t dst_offset,
				    अचिन्हित num_gpu_pages,
				    काष्ठा dma_resv *resv);
पूर्णांक r100_set_surface_reg(काष्ठा radeon_device *rdev, पूर्णांक reg,
			 uपूर्णांक32_t tiling_flags, uपूर्णांक32_t pitch,
			 uपूर्णांक32_t offset, uपूर्णांक32_t obj_size);
व्योम r100_clear_surface_reg(काष्ठा radeon_device *rdev, पूर्णांक reg);
व्योम r100_bandwidth_update(काष्ठा radeon_device *rdev);
व्योम r100_ring_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
पूर्णांक r100_ring_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
व्योम r100_hpd_init(काष्ठा radeon_device *rdev);
व्योम r100_hpd_fini(काष्ठा radeon_device *rdev);
bool r100_hpd_sense(काष्ठा radeon_device *rdev, क्रमागत radeon_hpd_id hpd);
व्योम r100_hpd_set_polarity(काष्ठा radeon_device *rdev,
			   क्रमागत radeon_hpd_id hpd);
व्योम r100_debugfs_rbbm_init(काष्ठा radeon_device *rdev);
व्योम r100_debugfs_cp_init(काष्ठा radeon_device *rdev);
व्योम r100_cp_disable(काष्ठा radeon_device *rdev);
पूर्णांक r100_cp_init(काष्ठा radeon_device *rdev, अचिन्हित ring_size);
व्योम r100_cp_fini(काष्ठा radeon_device *rdev);
पूर्णांक r100_pci_gart_init(काष्ठा radeon_device *rdev);
व्योम r100_pci_gart_fini(काष्ठा radeon_device *rdev);
पूर्णांक r100_pci_gart_enable(काष्ठा radeon_device *rdev);
व्योम r100_pci_gart_disable(काष्ठा radeon_device *rdev);
व्योम  r100_debugfs_mc_info_init(काष्ठा radeon_device *rdev);
पूर्णांक r100_gui_रुको_क्रम_idle(काष्ठा radeon_device *rdev);
पूर्णांक r100_ib_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
व्योम r100_irq_disable(काष्ठा radeon_device *rdev);
व्योम r100_mc_stop(काष्ठा radeon_device *rdev, काष्ठा r100_mc_save *save);
व्योम r100_mc_resume(काष्ठा radeon_device *rdev, काष्ठा r100_mc_save *save);
व्योम r100_vram_init_sizes(काष्ठा radeon_device *rdev);
पूर्णांक r100_cp_reset(काष्ठा radeon_device *rdev);
व्योम r100_vga_render_disable(काष्ठा radeon_device *rdev);
व्योम r100_restore_sanity(काष्ठा radeon_device *rdev);
पूर्णांक r100_cs_track_check_pkt3_indx_buffer(काष्ठा radeon_cs_parser *p,
					 काष्ठा radeon_cs_packet *pkt,
					 काष्ठा radeon_bo *robj);
पूर्णांक r100_cs_parse_packet0(काष्ठा radeon_cs_parser *p,
			  काष्ठा radeon_cs_packet *pkt,
			  स्थिर अचिन्हित *auth, अचिन्हित n,
			  radeon_packet0_check_t check);
पूर्णांक r100_cs_packet_parse(काष्ठा radeon_cs_parser *p,
			 काष्ठा radeon_cs_packet *pkt,
			 अचिन्हित idx);
व्योम r100_enable_bm(काष्ठा radeon_device *rdev);
व्योम r100_set_common_regs(काष्ठा radeon_device *rdev);
व्योम r100_bm_disable(काष्ठा radeon_device *rdev);
बाह्य bool r100_gui_idle(काष्ठा radeon_device *rdev);
बाह्य व्योम r100_pm_misc(काष्ठा radeon_device *rdev);
बाह्य व्योम r100_pm_prepare(काष्ठा radeon_device *rdev);
बाह्य व्योम r100_pm_finish(काष्ठा radeon_device *rdev);
बाह्य व्योम r100_pm_init_profile(काष्ठा radeon_device *rdev);
बाह्य व्योम r100_pm_get_dynpm_state(काष्ठा radeon_device *rdev);
बाह्य व्योम r100_page_flip(काष्ठा radeon_device *rdev, पूर्णांक crtc,
			   u64 crtc_base, bool async);
बाह्य bool r100_page_flip_pending(काष्ठा radeon_device *rdev, पूर्णांक crtc);
बाह्य व्योम r100_रुको_क्रम_vblank(काष्ठा radeon_device *rdev, पूर्णांक crtc);
बाह्य पूर्णांक r100_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev);

u32 r100_gfx_get_rptr(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_ring *ring);
u32 r100_gfx_get_wptr(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_ring *ring);
व्योम r100_gfx_set_wptr(काष्ठा radeon_device *rdev,
		       काष्ठा radeon_ring *ring);

/*
 * r200,rv250,rs300,rv280
 */
काष्ठा radeon_fence *r200_copy_dma(काष्ठा radeon_device *rdev,
				   uपूर्णांक64_t src_offset,
				   uपूर्णांक64_t dst_offset,
				   अचिन्हित num_gpu_pages,
				   काष्ठा dma_resv *resv);
व्योम r200_set_safe_रेजिस्टरs(काष्ठा radeon_device *rdev);

/*
 * r300,r350,rv350,rv380
 */
बाह्य पूर्णांक r300_init(काष्ठा radeon_device *rdev);
बाह्य व्योम r300_fini(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक r300_suspend(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक r300_resume(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक r300_asic_reset(काष्ठा radeon_device *rdev, bool hard);
बाह्य व्योम r300_ring_start(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
बाह्य व्योम r300_fence_ring_emit(काष्ठा radeon_device *rdev,
				काष्ठा radeon_fence *fence);
बाह्य पूर्णांक r300_cs_parse(काष्ठा radeon_cs_parser *p);
बाह्य व्योम rv370_pcie_gart_tlb_flush(काष्ठा radeon_device *rdev);
बाह्य uपूर्णांक64_t rv370_pcie_gart_get_page_entry(uपूर्णांक64_t addr, uपूर्णांक32_t flags);
बाह्य व्योम rv370_pcie_gart_set_page(काष्ठा radeon_device *rdev, अचिन्हित i,
				     uपूर्णांक64_t entry);
बाह्य व्योम rv370_set_pcie_lanes(काष्ठा radeon_device *rdev, पूर्णांक lanes);
बाह्य पूर्णांक rv370_get_pcie_lanes(काष्ठा radeon_device *rdev);
बाह्य व्योम r300_set_reg_safe(काष्ठा radeon_device *rdev);
बाह्य व्योम r300_mc_program(काष्ठा radeon_device *rdev);
बाह्य व्योम r300_mc_init(काष्ठा radeon_device *rdev);
बाह्य व्योम r300_घड़ी_startup(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक r300_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक rv370_pcie_gart_init(काष्ठा radeon_device *rdev);
बाह्य व्योम rv370_pcie_gart_fini(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक rv370_pcie_gart_enable(काष्ठा radeon_device *rdev);
बाह्य व्योम rv370_pcie_gart_disable(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक r300_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev);

/*
 * r420,r423,rv410
 */
बाह्य पूर्णांक r420_init(काष्ठा radeon_device *rdev);
बाह्य व्योम r420_fini(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक r420_suspend(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक r420_resume(काष्ठा radeon_device *rdev);
बाह्य व्योम r420_pm_init_profile(काष्ठा radeon_device *rdev);
बाह्य u32 r420_mc_rreg(काष्ठा radeon_device *rdev, u32 reg);
बाह्य व्योम r420_mc_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v);
बाह्य व्योम r420_debugfs_pipes_info_init(काष्ठा radeon_device *rdev);
बाह्य व्योम r420_pipes_init(काष्ठा radeon_device *rdev);

/*
 * rs400,rs480
 */
बाह्य पूर्णांक rs400_init(काष्ठा radeon_device *rdev);
बाह्य व्योम rs400_fini(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक rs400_suspend(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक rs400_resume(काष्ठा radeon_device *rdev);
व्योम rs400_gart_tlb_flush(काष्ठा radeon_device *rdev);
uपूर्णांक64_t rs400_gart_get_page_entry(uपूर्णांक64_t addr, uपूर्णांक32_t flags);
व्योम rs400_gart_set_page(काष्ठा radeon_device *rdev, अचिन्हित i,
			 uपूर्णांक64_t entry);
uपूर्णांक32_t rs400_mc_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg);
व्योम rs400_mc_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v);
पूर्णांक rs400_gart_init(काष्ठा radeon_device *rdev);
पूर्णांक rs400_gart_enable(काष्ठा radeon_device *rdev);
व्योम rs400_gart_adjust_size(काष्ठा radeon_device *rdev);
व्योम rs400_gart_disable(काष्ठा radeon_device *rdev);
व्योम rs400_gart_fini(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक rs400_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev);

/*
 * rs600.
 */
बाह्य पूर्णांक rs600_asic_reset(काष्ठा radeon_device *rdev, bool hard);
बाह्य पूर्णांक rs600_init(काष्ठा radeon_device *rdev);
बाह्य व्योम rs600_fini(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक rs600_suspend(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक rs600_resume(काष्ठा radeon_device *rdev);
पूर्णांक rs600_irq_set(काष्ठा radeon_device *rdev);
पूर्णांक rs600_irq_process(काष्ठा radeon_device *rdev);
व्योम rs600_irq_disable(काष्ठा radeon_device *rdev);
u32 rs600_get_vblank_counter(काष्ठा radeon_device *rdev, पूर्णांक crtc);
व्योम rs600_gart_tlb_flush(काष्ठा radeon_device *rdev);
uपूर्णांक64_t rs600_gart_get_page_entry(uपूर्णांक64_t addr, uपूर्णांक32_t flags);
व्योम rs600_gart_set_page(काष्ठा radeon_device *rdev, अचिन्हित i,
			 uपूर्णांक64_t entry);
uपूर्णांक32_t rs600_mc_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg);
व्योम rs600_mc_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v);
व्योम rs600_bandwidth_update(काष्ठा radeon_device *rdev);
व्योम rs600_hpd_init(काष्ठा radeon_device *rdev);
व्योम rs600_hpd_fini(काष्ठा radeon_device *rdev);
bool rs600_hpd_sense(काष्ठा radeon_device *rdev, क्रमागत radeon_hpd_id hpd);
व्योम rs600_hpd_set_polarity(काष्ठा radeon_device *rdev,
			    क्रमागत radeon_hpd_id hpd);
बाह्य व्योम rs600_pm_misc(काष्ठा radeon_device *rdev);
बाह्य व्योम rs600_pm_prepare(काष्ठा radeon_device *rdev);
बाह्य व्योम rs600_pm_finish(काष्ठा radeon_device *rdev);
बाह्य व्योम rs600_page_flip(काष्ठा radeon_device *rdev, पूर्णांक crtc,
			    u64 crtc_base, bool async);
बाह्य bool rs600_page_flip_pending(काष्ठा radeon_device *rdev, पूर्णांक crtc);
व्योम rs600_set_safe_रेजिस्टरs(काष्ठा radeon_device *rdev);
बाह्य व्योम avivo_रुको_क्रम_vblank(काष्ठा radeon_device *rdev, पूर्णांक crtc);
बाह्य पूर्णांक rs600_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev);

/*
 * rs690,rs740
 */
पूर्णांक rs690_init(काष्ठा radeon_device *rdev);
व्योम rs690_fini(काष्ठा radeon_device *rdev);
पूर्णांक rs690_resume(काष्ठा radeon_device *rdev);
पूर्णांक rs690_suspend(काष्ठा radeon_device *rdev);
uपूर्णांक32_t rs690_mc_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg);
व्योम rs690_mc_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v);
व्योम rs690_bandwidth_update(काष्ठा radeon_device *rdev);
व्योम rs690_line_buffer_adjust(काष्ठा radeon_device *rdev,
					काष्ठा drm_display_mode *mode1,
					काष्ठा drm_display_mode *mode2);
बाह्य पूर्णांक rs690_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev);

/*
 * rv515
 */
काष्ठा rv515_mc_save अणु
	u32 vga_render_control;
	u32 vga_hdp_control;
	bool crtc_enabled[2];
पूर्ण;

पूर्णांक rv515_init(काष्ठा radeon_device *rdev);
व्योम rv515_fini(काष्ठा radeon_device *rdev);
uपूर्णांक32_t rv515_mc_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg);
व्योम rv515_mc_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v);
व्योम rv515_ring_start(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
व्योम rv515_bandwidth_update(काष्ठा radeon_device *rdev);
पूर्णांक rv515_resume(काष्ठा radeon_device *rdev);
पूर्णांक rv515_suspend(काष्ठा radeon_device *rdev);
व्योम rv515_bandwidth_avivo_update(काष्ठा radeon_device *rdev);
व्योम rv515_vga_render_disable(काष्ठा radeon_device *rdev);
व्योम rv515_set_safe_रेजिस्टरs(काष्ठा radeon_device *rdev);
व्योम rv515_mc_stop(काष्ठा radeon_device *rdev, काष्ठा rv515_mc_save *save);
व्योम rv515_mc_resume(काष्ठा radeon_device *rdev, काष्ठा rv515_mc_save *save);
व्योम rv515_घड़ी_startup(काष्ठा radeon_device *rdev);
व्योम rv515_debugfs(काष्ठा radeon_device *rdev);
पूर्णांक rv515_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev);

/*
 * r520,rv530,rv560,rv570,r580
 */
पूर्णांक r520_init(काष्ठा radeon_device *rdev);
पूर्णांक r520_resume(काष्ठा radeon_device *rdev);
पूर्णांक r520_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev);

/*
 * r600,rv610,rv630,rv620,rv635,rv670,rs780,rs880
 */
पूर्णांक r600_init(काष्ठा radeon_device *rdev);
व्योम r600_fini(काष्ठा radeon_device *rdev);
पूर्णांक r600_suspend(काष्ठा radeon_device *rdev);
पूर्णांक r600_resume(काष्ठा radeon_device *rdev);
व्योम r600_vga_set_state(काष्ठा radeon_device *rdev, bool state);
पूर्णांक r600_wb_init(काष्ठा radeon_device *rdev);
व्योम r600_wb_fini(काष्ठा radeon_device *rdev);
व्योम r600_pcie_gart_tlb_flush(काष्ठा radeon_device *rdev);
uपूर्णांक32_t r600_pciep_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg);
व्योम r600_pciep_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v);
पूर्णांक r600_cs_parse(काष्ठा radeon_cs_parser *p);
पूर्णांक r600_dma_cs_parse(काष्ठा radeon_cs_parser *p);
व्योम r600_fence_ring_emit(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_fence *fence);
bool r600_semaphore_ring_emit(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_ring *cp,
			      काष्ठा radeon_semaphore *semaphore,
			      bool emit_रुको);
व्योम r600_dma_fence_ring_emit(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_fence *fence);
bool r600_dma_semaphore_ring_emit(काष्ठा radeon_device *rdev,
				  काष्ठा radeon_ring *ring,
				  काष्ठा radeon_semaphore *semaphore,
				  bool emit_रुको);
व्योम r600_dma_ring_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
bool r600_dma_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
bool r600_gfx_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
पूर्णांक r600_asic_reset(काष्ठा radeon_device *rdev, bool hard);
पूर्णांक r600_set_surface_reg(काष्ठा radeon_device *rdev, पूर्णांक reg,
			 uपूर्णांक32_t tiling_flags, uपूर्णांक32_t pitch,
			 uपूर्णांक32_t offset, uपूर्णांक32_t obj_size);
व्योम r600_clear_surface_reg(काष्ठा radeon_device *rdev, पूर्णांक reg);
पूर्णांक r600_ib_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
पूर्णांक r600_dma_ib_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
व्योम r600_ring_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
पूर्णांक r600_ring_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
पूर्णांक r600_dma_ring_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
काष्ठा radeon_fence *r600_copy_cpdma(काष्ठा radeon_device *rdev,
				     uपूर्णांक64_t src_offset, uपूर्णांक64_t dst_offset,
				     अचिन्हित num_gpu_pages,
				     काष्ठा dma_resv *resv);
काष्ठा radeon_fence *r600_copy_dma(काष्ठा radeon_device *rdev,
				   uपूर्णांक64_t src_offset, uपूर्णांक64_t dst_offset,
				   अचिन्हित num_gpu_pages,
				   काष्ठा dma_resv *resv);
व्योम r600_hpd_init(काष्ठा radeon_device *rdev);
व्योम r600_hpd_fini(काष्ठा radeon_device *rdev);
bool r600_hpd_sense(काष्ठा radeon_device *rdev, क्रमागत radeon_hpd_id hpd);
व्योम r600_hpd_set_polarity(काष्ठा radeon_device *rdev,
			   क्रमागत radeon_hpd_id hpd);
बाह्य व्योम r600_mmio_hdp_flush(काष्ठा radeon_device *rdev);
बाह्य bool r600_gui_idle(काष्ठा radeon_device *rdev);
बाह्य व्योम r600_pm_misc(काष्ठा radeon_device *rdev);
बाह्य व्योम r600_pm_init_profile(काष्ठा radeon_device *rdev);
बाह्य व्योम rs780_pm_init_profile(काष्ठा radeon_device *rdev);
बाह्य uपूर्णांक32_t rs780_mc_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg);
बाह्य व्योम rs780_mc_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v);
बाह्य व्योम r600_pm_get_dynpm_state(काष्ठा radeon_device *rdev);
बाह्य व्योम r600_set_pcie_lanes(काष्ठा radeon_device *rdev, पूर्णांक lanes);
बाह्य पूर्णांक r600_get_pcie_lanes(काष्ठा radeon_device *rdev);
bool r600_card_posted(काष्ठा radeon_device *rdev);
व्योम r600_cp_stop(काष्ठा radeon_device *rdev);
पूर्णांक r600_cp_start(काष्ठा radeon_device *rdev);
व्योम r600_ring_init(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp, अचिन्हित ring_size);
पूर्णांक r600_cp_resume(काष्ठा radeon_device *rdev);
व्योम r600_cp_fini(काष्ठा radeon_device *rdev);
पूर्णांक r600_count_pipe_bits(uपूर्णांक32_t val);
पूर्णांक r600_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev);
पूर्णांक r600_pcie_gart_init(काष्ठा radeon_device *rdev);
व्योम r600_scratch_init(काष्ठा radeon_device *rdev);
पूर्णांक r600_init_microcode(काष्ठा radeon_device *rdev);
u32 r600_gfx_get_rptr(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_ring *ring);
u32 r600_gfx_get_wptr(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_ring *ring);
व्योम r600_gfx_set_wptr(काष्ठा radeon_device *rdev,
		       काष्ठा radeon_ring *ring);
पूर्णांक r600_get_allowed_info_रेजिस्टर(काष्ठा radeon_device *rdev,
				   u32 reg, u32 *val);
/* r600 irq */
पूर्णांक r600_irq_process(काष्ठा radeon_device *rdev);
पूर्णांक r600_irq_init(काष्ठा radeon_device *rdev);
व्योम r600_irq_fini(काष्ठा radeon_device *rdev);
व्योम r600_ih_ring_init(काष्ठा radeon_device *rdev, अचिन्हित ring_size);
पूर्णांक r600_irq_set(काष्ठा radeon_device *rdev);
व्योम r600_irq_suspend(काष्ठा radeon_device *rdev);
व्योम r600_disable_पूर्णांकerrupts(काष्ठा radeon_device *rdev);
व्योम r600_rlc_stop(काष्ठा radeon_device *rdev);
/* r600 audio */
व्योम r600_audio_fini(काष्ठा radeon_device *rdev);
व्योम r600_audio_set_dto(काष्ठा drm_encoder *encoder, u32 घड़ी);
व्योम r600_hdmi_update_avi_infoframe(काष्ठा drm_encoder *encoder, व्योम *buffer,
				    माप_प्रकार size);
व्योम r600_hdmi_update_ACR(काष्ठा drm_encoder *encoder, uपूर्णांक32_t घड़ी);
व्योम r600_hdmi_audio_workaround(काष्ठा drm_encoder *encoder);
पूर्णांक r600_hdmi_buffer_status_changed(काष्ठा drm_encoder *encoder);
व्योम r600_hdmi_update_audio_settings(काष्ठा drm_encoder *encoder);
पूर्णांक r600_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev);
u32 r600_get_xclk(काष्ठा radeon_device *rdev);
uपूर्णांक64_t r600_get_gpu_घड़ी_counter(काष्ठा radeon_device *rdev);
पूर्णांक rv6xx_get_temp(काष्ठा radeon_device *rdev);
पूर्णांक r600_set_uvd_घड़ीs(काष्ठा radeon_device *rdev, u32 vclk, u32 dclk);
पूर्णांक r600_dpm_pre_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम r600_dpm_post_set_घातer_state(काष्ठा radeon_device *rdev);
पूर्णांक r600_dpm_late_enable(काष्ठा radeon_device *rdev);
/* r600 dma */
uपूर्णांक32_t r600_dma_get_rptr(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ring *ring);
uपूर्णांक32_t r600_dma_get_wptr(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ring *ring);
व्योम r600_dma_set_wptr(काष्ठा radeon_device *rdev,
		       काष्ठा radeon_ring *ring);
/* rv6xx dpm */
पूर्णांक rv6xx_dpm_init(काष्ठा radeon_device *rdev);
पूर्णांक rv6xx_dpm_enable(काष्ठा radeon_device *rdev);
व्योम rv6xx_dpm_disable(काष्ठा radeon_device *rdev);
पूर्णांक rv6xx_dpm_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम rv6xx_setup_asic(काष्ठा radeon_device *rdev);
व्योम rv6xx_dpm_display_configuration_changed(काष्ठा radeon_device *rdev);
व्योम rv6xx_dpm_fini(काष्ठा radeon_device *rdev);
u32 rv6xx_dpm_get_sclk(काष्ठा radeon_device *rdev, bool low);
u32 rv6xx_dpm_get_mclk(काष्ठा radeon_device *rdev, bool low);
व्योम rv6xx_dpm_prपूर्णांक_घातer_state(काष्ठा radeon_device *rdev,
				 काष्ठा radeon_ps *ps);
व्योम rv6xx_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
						       काष्ठा seq_file *m);
पूर्णांक rv6xx_dpm_क्रमce_perक्रमmance_level(काष्ठा radeon_device *rdev,
				      क्रमागत radeon_dpm_क्रमced_level level);
u32 rv6xx_dpm_get_current_sclk(काष्ठा radeon_device *rdev);
u32 rv6xx_dpm_get_current_mclk(काष्ठा radeon_device *rdev);
/* rs780 dpm */
पूर्णांक rs780_dpm_init(काष्ठा radeon_device *rdev);
पूर्णांक rs780_dpm_enable(काष्ठा radeon_device *rdev);
व्योम rs780_dpm_disable(काष्ठा radeon_device *rdev);
पूर्णांक rs780_dpm_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम rs780_dpm_setup_asic(काष्ठा radeon_device *rdev);
व्योम rs780_dpm_display_configuration_changed(काष्ठा radeon_device *rdev);
व्योम rs780_dpm_fini(काष्ठा radeon_device *rdev);
u32 rs780_dpm_get_sclk(काष्ठा radeon_device *rdev, bool low);
u32 rs780_dpm_get_mclk(काष्ठा radeon_device *rdev, bool low);
व्योम rs780_dpm_prपूर्णांक_घातer_state(काष्ठा radeon_device *rdev,
				 काष्ठा radeon_ps *ps);
व्योम rs780_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
						       काष्ठा seq_file *m);
पूर्णांक rs780_dpm_क्रमce_perक्रमmance_level(काष्ठा radeon_device *rdev,
				      क्रमागत radeon_dpm_क्रमced_level level);
u32 rs780_dpm_get_current_sclk(काष्ठा radeon_device *rdev);
u32 rs780_dpm_get_current_mclk(काष्ठा radeon_device *rdev);

/*
 * rv770,rv730,rv710,rv740
 */
पूर्णांक rv770_init(काष्ठा radeon_device *rdev);
व्योम rv770_fini(काष्ठा radeon_device *rdev);
पूर्णांक rv770_suspend(काष्ठा radeon_device *rdev);
पूर्णांक rv770_resume(काष्ठा radeon_device *rdev);
व्योम rv770_pm_misc(काष्ठा radeon_device *rdev);
व्योम rv770_page_flip(काष्ठा radeon_device *rdev, पूर्णांक crtc, u64 crtc_base,
		     bool async);
bool rv770_page_flip_pending(काष्ठा radeon_device *rdev, पूर्णांक crtc);
व्योम r700_vram_gtt_location(काष्ठा radeon_device *rdev, काष्ठा radeon_mc *mc);
व्योम r700_cp_stop(काष्ठा radeon_device *rdev);
व्योम r700_cp_fini(काष्ठा radeon_device *rdev);
काष्ठा radeon_fence *rv770_copy_dma(काष्ठा radeon_device *rdev,
				    uपूर्णांक64_t src_offset, uपूर्णांक64_t dst_offset,
				    अचिन्हित num_gpu_pages,
				    काष्ठा dma_resv *resv);
u32 rv770_get_xclk(काष्ठा radeon_device *rdev);
पूर्णांक rv770_set_uvd_घड़ीs(काष्ठा radeon_device *rdev, u32 vclk, u32 dclk);
पूर्णांक rv770_get_temp(काष्ठा radeon_device *rdev);
/* rv7xx pm */
पूर्णांक rv770_dpm_init(काष्ठा radeon_device *rdev);
पूर्णांक rv770_dpm_enable(काष्ठा radeon_device *rdev);
पूर्णांक rv770_dpm_late_enable(काष्ठा radeon_device *rdev);
व्योम rv770_dpm_disable(काष्ठा radeon_device *rdev);
पूर्णांक rv770_dpm_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम rv770_dpm_setup_asic(काष्ठा radeon_device *rdev);
व्योम rv770_dpm_display_configuration_changed(काष्ठा radeon_device *rdev);
व्योम rv770_dpm_fini(काष्ठा radeon_device *rdev);
u32 rv770_dpm_get_sclk(काष्ठा radeon_device *rdev, bool low);
u32 rv770_dpm_get_mclk(काष्ठा radeon_device *rdev, bool low);
व्योम rv770_dpm_prपूर्णांक_घातer_state(काष्ठा radeon_device *rdev,
				 काष्ठा radeon_ps *ps);
व्योम rv770_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
						       काष्ठा seq_file *m);
पूर्णांक rv770_dpm_क्रमce_perक्रमmance_level(काष्ठा radeon_device *rdev,
				      क्रमागत radeon_dpm_क्रमced_level level);
bool rv770_dpm_vblank_too_लघु(काष्ठा radeon_device *rdev);
u32 rv770_dpm_get_current_sclk(काष्ठा radeon_device *rdev);
u32 rv770_dpm_get_current_mclk(काष्ठा radeon_device *rdev);

/*
 * evergreen
 */
काष्ठा evergreen_mc_save अणु
	u32 vga_render_control;
	u32 vga_hdp_control;
	bool crtc_enabled[RADEON_MAX_CRTCS];
पूर्ण;

व्योम evergreen_pcie_gart_tlb_flush(काष्ठा radeon_device *rdev);
पूर्णांक evergreen_init(काष्ठा radeon_device *rdev);
व्योम evergreen_fini(काष्ठा radeon_device *rdev);
पूर्णांक evergreen_suspend(काष्ठा radeon_device *rdev);
पूर्णांक evergreen_resume(काष्ठा radeon_device *rdev);
bool evergreen_gfx_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
bool evergreen_dma_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
पूर्णांक evergreen_asic_reset(काष्ठा radeon_device *rdev, bool hard);
व्योम evergreen_bandwidth_update(काष्ठा radeon_device *rdev);
व्योम evergreen_ring_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
व्योम evergreen_hpd_init(काष्ठा radeon_device *rdev);
व्योम evergreen_hpd_fini(काष्ठा radeon_device *rdev);
bool evergreen_hpd_sense(काष्ठा radeon_device *rdev, क्रमागत radeon_hpd_id hpd);
व्योम evergreen_hpd_set_polarity(काष्ठा radeon_device *rdev,
				क्रमागत radeon_hpd_id hpd);
u32 evergreen_get_vblank_counter(काष्ठा radeon_device *rdev, पूर्णांक crtc);
पूर्णांक evergreen_irq_set(काष्ठा radeon_device *rdev);
पूर्णांक evergreen_irq_process(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक evergreen_cs_parse(काष्ठा radeon_cs_parser *p);
बाह्य पूर्णांक evergreen_dma_cs_parse(काष्ठा radeon_cs_parser *p);
बाह्य व्योम evergreen_pm_misc(काष्ठा radeon_device *rdev);
बाह्य व्योम evergreen_pm_prepare(काष्ठा radeon_device *rdev);
बाह्य व्योम evergreen_pm_finish(काष्ठा radeon_device *rdev);
बाह्य व्योम sumo_pm_init_profile(काष्ठा radeon_device *rdev);
बाह्य व्योम btc_pm_init_profile(काष्ठा radeon_device *rdev);
पूर्णांक sumo_set_uvd_घड़ीs(काष्ठा radeon_device *rdev, u32 vclk, u32 dclk);
पूर्णांक evergreen_set_uvd_घड़ीs(काष्ठा radeon_device *rdev, u32 vclk, u32 dclk);
बाह्य व्योम evergreen_page_flip(काष्ठा radeon_device *rdev, पूर्णांक crtc,
				u64 crtc_base, bool async);
बाह्य bool evergreen_page_flip_pending(काष्ठा radeon_device *rdev, पूर्णांक crtc);
बाह्य व्योम dce4_रुको_क्रम_vblank(काष्ठा radeon_device *rdev, पूर्णांक crtc);
व्योम evergreen_disable_पूर्णांकerrupt_state(काष्ठा radeon_device *rdev);
पूर्णांक evergreen_mc_रुको_क्रम_idle(काष्ठा radeon_device *rdev);
व्योम evergreen_dma_fence_ring_emit(काष्ठा radeon_device *rdev,
				   काष्ठा radeon_fence *fence);
व्योम evergreen_dma_ring_ib_execute(काष्ठा radeon_device *rdev,
				   काष्ठा radeon_ib *ib);
काष्ठा radeon_fence *evergreen_copy_dma(काष्ठा radeon_device *rdev,
					uपूर्णांक64_t src_offset, uपूर्णांक64_t dst_offset,
					अचिन्हित num_gpu_pages,
					काष्ठा dma_resv *resv);
पूर्णांक evergreen_get_temp(काष्ठा radeon_device *rdev);
पूर्णांक evergreen_get_allowed_info_रेजिस्टर(काष्ठा radeon_device *rdev,
					u32 reg, u32 *val);
पूर्णांक sumo_get_temp(काष्ठा radeon_device *rdev);
पूर्णांक tn_get_temp(काष्ठा radeon_device *rdev);
पूर्णांक cypress_dpm_init(काष्ठा radeon_device *rdev);
व्योम cypress_dpm_setup_asic(काष्ठा radeon_device *rdev);
पूर्णांक cypress_dpm_enable(काष्ठा radeon_device *rdev);
व्योम cypress_dpm_disable(काष्ठा radeon_device *rdev);
पूर्णांक cypress_dpm_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम cypress_dpm_display_configuration_changed(काष्ठा radeon_device *rdev);
व्योम cypress_dpm_fini(काष्ठा radeon_device *rdev);
bool cypress_dpm_vblank_too_लघु(काष्ठा radeon_device *rdev);
पूर्णांक btc_dpm_init(काष्ठा radeon_device *rdev);
व्योम btc_dpm_setup_asic(काष्ठा radeon_device *rdev);
पूर्णांक btc_dpm_enable(काष्ठा radeon_device *rdev);
व्योम btc_dpm_disable(काष्ठा radeon_device *rdev);
पूर्णांक btc_dpm_pre_set_घातer_state(काष्ठा radeon_device *rdev);
पूर्णांक btc_dpm_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम btc_dpm_post_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम btc_dpm_fini(काष्ठा radeon_device *rdev);
u32 btc_dpm_get_sclk(काष्ठा radeon_device *rdev, bool low);
u32 btc_dpm_get_mclk(काष्ठा radeon_device *rdev, bool low);
bool btc_dpm_vblank_too_लघु(काष्ठा radeon_device *rdev);
व्योम btc_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
						     काष्ठा seq_file *m);
u32 btc_dpm_get_current_sclk(काष्ठा radeon_device *rdev);
u32 btc_dpm_get_current_mclk(काष्ठा radeon_device *rdev);
पूर्णांक sumo_dpm_init(काष्ठा radeon_device *rdev);
पूर्णांक sumo_dpm_enable(काष्ठा radeon_device *rdev);
पूर्णांक sumo_dpm_late_enable(काष्ठा radeon_device *rdev);
व्योम sumo_dpm_disable(काष्ठा radeon_device *rdev);
पूर्णांक sumo_dpm_pre_set_घातer_state(काष्ठा radeon_device *rdev);
पूर्णांक sumo_dpm_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम sumo_dpm_post_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम sumo_dpm_setup_asic(काष्ठा radeon_device *rdev);
व्योम sumo_dpm_display_configuration_changed(काष्ठा radeon_device *rdev);
व्योम sumo_dpm_fini(काष्ठा radeon_device *rdev);
u32 sumo_dpm_get_sclk(काष्ठा radeon_device *rdev, bool low);
u32 sumo_dpm_get_mclk(काष्ठा radeon_device *rdev, bool low);
व्योम sumo_dpm_prपूर्णांक_घातer_state(काष्ठा radeon_device *rdev,
				काष्ठा radeon_ps *ps);
व्योम sumo_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
						      काष्ठा seq_file *m);
पूर्णांक sumo_dpm_क्रमce_perक्रमmance_level(काष्ठा radeon_device *rdev,
				     क्रमागत radeon_dpm_क्रमced_level level);
u32 sumo_dpm_get_current_sclk(काष्ठा radeon_device *rdev);
u32 sumo_dpm_get_current_mclk(काष्ठा radeon_device *rdev);
u16 sumo_dpm_get_current_vddc(काष्ठा radeon_device *rdev);

/*
 * cayman
 */
व्योम cayman_fence_ring_emit(काष्ठा radeon_device *rdev,
			    काष्ठा radeon_fence *fence);
व्योम cayman_pcie_gart_tlb_flush(काष्ठा radeon_device *rdev);
पूर्णांक cayman_init(काष्ठा radeon_device *rdev);
व्योम cayman_fini(काष्ठा radeon_device *rdev);
पूर्णांक cayman_suspend(काष्ठा radeon_device *rdev);
पूर्णांक cayman_resume(काष्ठा radeon_device *rdev);
पूर्णांक cayman_asic_reset(काष्ठा radeon_device *rdev, bool hard);
व्योम cayman_ring_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
पूर्णांक cayman_vm_init(काष्ठा radeon_device *rdev);
व्योम cayman_vm_fini(काष्ठा radeon_device *rdev);
व्योम cayman_vm_flush(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
		     अचिन्हित vm_id, uपूर्णांक64_t pd_addr);
uपूर्णांक32_t cayman_vm_page_flags(काष्ठा radeon_device *rdev, uपूर्णांक32_t flags);
पूर्णांक evergreen_ib_parse(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
पूर्णांक evergreen_dma_ib_parse(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
व्योम cayman_dma_ring_ib_execute(काष्ठा radeon_device *rdev,
				काष्ठा radeon_ib *ib);
bool cayman_gfx_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
bool cayman_dma_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);

व्योम cayman_dma_vm_copy_pages(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_ib *ib,
			      uपूर्णांक64_t pe, uपूर्णांक64_t src,
			      अचिन्हित count);
व्योम cayman_dma_vm_ग_लिखो_pages(काष्ठा radeon_device *rdev,
			       काष्ठा radeon_ib *ib,
			       uपूर्णांक64_t pe,
			       uपूर्णांक64_t addr, अचिन्हित count,
			       uपूर्णांक32_t incr, uपूर्णांक32_t flags);
व्योम cayman_dma_vm_set_pages(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_ib *ib,
			     uपूर्णांक64_t pe,
			     uपूर्णांक64_t addr, अचिन्हित count,
			     uपूर्णांक32_t incr, uपूर्णांक32_t flags);
व्योम cayman_dma_vm_pad_ib(काष्ठा radeon_ib *ib);

व्योम cayman_dma_vm_flush(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
			 अचिन्हित vm_id, uपूर्णांक64_t pd_addr);

u32 cayman_gfx_get_rptr(काष्ठा radeon_device *rdev,
			काष्ठा radeon_ring *ring);
u32 cayman_gfx_get_wptr(काष्ठा radeon_device *rdev,
			काष्ठा radeon_ring *ring);
व्योम cayman_gfx_set_wptr(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_ring *ring);
uपूर्णांक32_t cayman_dma_get_rptr(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_ring *ring);
uपूर्णांक32_t cayman_dma_get_wptr(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_ring *ring);
व्योम cayman_dma_set_wptr(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_ring *ring);
पूर्णांक cayman_get_allowed_info_रेजिस्टर(काष्ठा radeon_device *rdev,
				     u32 reg, u32 *val);

पूर्णांक ni_dpm_init(काष्ठा radeon_device *rdev);
व्योम ni_dpm_setup_asic(काष्ठा radeon_device *rdev);
पूर्णांक ni_dpm_enable(काष्ठा radeon_device *rdev);
व्योम ni_dpm_disable(काष्ठा radeon_device *rdev);
पूर्णांक ni_dpm_pre_set_घातer_state(काष्ठा radeon_device *rdev);
पूर्णांक ni_dpm_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम ni_dpm_post_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम ni_dpm_fini(काष्ठा radeon_device *rdev);
u32 ni_dpm_get_sclk(काष्ठा radeon_device *rdev, bool low);
u32 ni_dpm_get_mclk(काष्ठा radeon_device *rdev, bool low);
व्योम ni_dpm_prपूर्णांक_घातer_state(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_ps *ps);
व्योम ni_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
						    काष्ठा seq_file *m);
पूर्णांक ni_dpm_क्रमce_perक्रमmance_level(काष्ठा radeon_device *rdev,
				   क्रमागत radeon_dpm_क्रमced_level level);
bool ni_dpm_vblank_too_लघु(काष्ठा radeon_device *rdev);
u32 ni_dpm_get_current_sclk(काष्ठा radeon_device *rdev);
u32 ni_dpm_get_current_mclk(काष्ठा radeon_device *rdev);
पूर्णांक trinity_dpm_init(काष्ठा radeon_device *rdev);
पूर्णांक trinity_dpm_enable(काष्ठा radeon_device *rdev);
पूर्णांक trinity_dpm_late_enable(काष्ठा radeon_device *rdev);
व्योम trinity_dpm_disable(काष्ठा radeon_device *rdev);
पूर्णांक trinity_dpm_pre_set_घातer_state(काष्ठा radeon_device *rdev);
पूर्णांक trinity_dpm_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम trinity_dpm_post_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम trinity_dpm_setup_asic(काष्ठा radeon_device *rdev);
व्योम trinity_dpm_display_configuration_changed(काष्ठा radeon_device *rdev);
व्योम trinity_dpm_fini(काष्ठा radeon_device *rdev);
u32 trinity_dpm_get_sclk(काष्ठा radeon_device *rdev, bool low);
u32 trinity_dpm_get_mclk(काष्ठा radeon_device *rdev, bool low);
व्योम trinity_dpm_prपूर्णांक_घातer_state(काष्ठा radeon_device *rdev,
				   काष्ठा radeon_ps *ps);
व्योम trinity_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
							 काष्ठा seq_file *m);
पूर्णांक trinity_dpm_क्रमce_perक्रमmance_level(काष्ठा radeon_device *rdev,
					क्रमागत radeon_dpm_क्रमced_level level);
व्योम trinity_dpm_enable_bapm(काष्ठा radeon_device *rdev, bool enable);
u32 trinity_dpm_get_current_sclk(काष्ठा radeon_device *rdev);
u32 trinity_dpm_get_current_mclk(काष्ठा radeon_device *rdev);
पूर्णांक tn_set_vce_घड़ीs(काष्ठा radeon_device *rdev, u32 evclk, u32 ecclk);

/* DCE6 - SI */
व्योम dce6_bandwidth_update(काष्ठा radeon_device *rdev);
व्योम dce6_audio_fini(काष्ठा radeon_device *rdev);

/*
 * si
 */
व्योम si_fence_ring_emit(काष्ठा radeon_device *rdev,
			काष्ठा radeon_fence *fence);
व्योम si_pcie_gart_tlb_flush(काष्ठा radeon_device *rdev);
पूर्णांक si_init(काष्ठा radeon_device *rdev);
व्योम si_fini(काष्ठा radeon_device *rdev);
पूर्णांक si_suspend(काष्ठा radeon_device *rdev);
पूर्णांक si_resume(काष्ठा radeon_device *rdev);
bool si_gfx_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
bool si_dma_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
पूर्णांक si_asic_reset(काष्ठा radeon_device *rdev, bool hard);
व्योम si_ring_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
पूर्णांक si_irq_set(काष्ठा radeon_device *rdev);
पूर्णांक si_irq_process(काष्ठा radeon_device *rdev);
पूर्णांक si_vm_init(काष्ठा radeon_device *rdev);
व्योम si_vm_fini(काष्ठा radeon_device *rdev);
व्योम si_vm_flush(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
		 अचिन्हित vm_id, uपूर्णांक64_t pd_addr);
पूर्णांक si_ib_parse(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
काष्ठा radeon_fence *si_copy_dma(काष्ठा radeon_device *rdev,
				 uपूर्णांक64_t src_offset, uपूर्णांक64_t dst_offset,
				 अचिन्हित num_gpu_pages,
				 काष्ठा dma_resv *resv);

व्योम si_dma_vm_copy_pages(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_ib *ib,
			  uपूर्णांक64_t pe, uपूर्णांक64_t src,
			  अचिन्हित count);
व्योम si_dma_vm_ग_लिखो_pages(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ib *ib,
			   uपूर्णांक64_t pe,
			   uपूर्णांक64_t addr, अचिन्हित count,
			   uपूर्णांक32_t incr, uपूर्णांक32_t flags);
व्योम si_dma_vm_set_pages(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_ib *ib,
			 uपूर्णांक64_t pe,
			 uपूर्णांक64_t addr, अचिन्हित count,
			 uपूर्णांक32_t incr, uपूर्णांक32_t flags);

व्योम si_dma_vm_flush(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
		     अचिन्हित vm_id, uपूर्णांक64_t pd_addr);
u32 si_get_xclk(काष्ठा radeon_device *rdev);
uपूर्णांक64_t si_get_gpu_घड़ी_counter(काष्ठा radeon_device *rdev);
पूर्णांक si_set_uvd_घड़ीs(काष्ठा radeon_device *rdev, u32 vclk, u32 dclk);
पूर्णांक si_set_vce_घड़ीs(काष्ठा radeon_device *rdev, u32 evclk, u32 ecclk);
पूर्णांक si_get_temp(काष्ठा radeon_device *rdev);
पूर्णांक si_get_allowed_info_रेजिस्टर(काष्ठा radeon_device *rdev,
				 u32 reg, u32 *val);
पूर्णांक si_dpm_init(काष्ठा radeon_device *rdev);
व्योम si_dpm_setup_asic(काष्ठा radeon_device *rdev);
पूर्णांक si_dpm_enable(काष्ठा radeon_device *rdev);
पूर्णांक si_dpm_late_enable(काष्ठा radeon_device *rdev);
व्योम si_dpm_disable(काष्ठा radeon_device *rdev);
पूर्णांक si_dpm_pre_set_घातer_state(काष्ठा radeon_device *rdev);
पूर्णांक si_dpm_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम si_dpm_post_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम si_dpm_fini(काष्ठा radeon_device *rdev);
व्योम si_dpm_display_configuration_changed(काष्ठा radeon_device *rdev);
व्योम si_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
						    काष्ठा seq_file *m);
पूर्णांक si_dpm_क्रमce_perक्रमmance_level(काष्ठा radeon_device *rdev,
				   क्रमागत radeon_dpm_क्रमced_level level);
पूर्णांक si_fan_ctrl_get_fan_speed_percent(काष्ठा radeon_device *rdev,
						 u32 *speed);
पूर्णांक si_fan_ctrl_set_fan_speed_percent(काष्ठा radeon_device *rdev,
						 u32 speed);
u32 si_fan_ctrl_get_mode(काष्ठा radeon_device *rdev);
व्योम si_fan_ctrl_set_mode(काष्ठा radeon_device *rdev, u32 mode);
u32 si_dpm_get_current_sclk(काष्ठा radeon_device *rdev);
u32 si_dpm_get_current_mclk(काष्ठा radeon_device *rdev);

/* DCE8 - CIK */
व्योम dce8_bandwidth_update(काष्ठा radeon_device *rdev);

/*
 * cik
 */
uपूर्णांक64_t cik_get_gpu_घड़ी_counter(काष्ठा radeon_device *rdev);
u32 cik_get_xclk(काष्ठा radeon_device *rdev);
uपूर्णांक32_t cik_pciep_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg);
व्योम cik_pciep_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v);
पूर्णांक cik_set_uvd_घड़ीs(काष्ठा radeon_device *rdev, u32 vclk, u32 dclk);
पूर्णांक cik_set_vce_घड़ीs(काष्ठा radeon_device *rdev, u32 evclk, u32 ecclk);
व्योम cik_sdma_fence_ring_emit(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_fence *fence);
bool cik_sdma_semaphore_ring_emit(काष्ठा radeon_device *rdev,
				  काष्ठा radeon_ring *ring,
				  काष्ठा radeon_semaphore *semaphore,
				  bool emit_रुको);
व्योम cik_sdma_ring_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
काष्ठा radeon_fence *cik_copy_dma(काष्ठा radeon_device *rdev,
				  uपूर्णांक64_t src_offset, uपूर्णांक64_t dst_offset,
				  अचिन्हित num_gpu_pages,
				  काष्ठा dma_resv *resv);
काष्ठा radeon_fence *cik_copy_cpdma(काष्ठा radeon_device *rdev,
				    uपूर्णांक64_t src_offset, uपूर्णांक64_t dst_offset,
				    अचिन्हित num_gpu_pages,
				    काष्ठा dma_resv *resv);
पूर्णांक cik_sdma_ring_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
पूर्णांक cik_sdma_ib_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
bool cik_sdma_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
व्योम cik_fence_gfx_ring_emit(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_fence *fence);
व्योम cik_fence_compute_ring_emit(काष्ठा radeon_device *rdev,
				 काष्ठा radeon_fence *fence);
bool cik_semaphore_ring_emit(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_ring *cp,
			     काष्ठा radeon_semaphore *semaphore,
			     bool emit_रुको);
व्योम cik_pcie_gart_tlb_flush(काष्ठा radeon_device *rdev);
पूर्णांक cik_init(काष्ठा radeon_device *rdev);
व्योम cik_fini(काष्ठा radeon_device *rdev);
पूर्णांक cik_suspend(काष्ठा radeon_device *rdev);
पूर्णांक cik_resume(काष्ठा radeon_device *rdev);
bool cik_gfx_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
पूर्णांक cik_asic_reset(काष्ठा radeon_device *rdev, bool hard);
व्योम cik_ring_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
पूर्णांक cik_ring_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
पूर्णांक cik_ib_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
पूर्णांक cik_irq_set(काष्ठा radeon_device *rdev);
पूर्णांक cik_irq_process(काष्ठा radeon_device *rdev);
पूर्णांक cik_vm_init(काष्ठा radeon_device *rdev);
व्योम cik_vm_fini(काष्ठा radeon_device *rdev);
व्योम cik_vm_flush(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
		  अचिन्हित vm_id, uपूर्णांक64_t pd_addr);

व्योम cik_sdma_vm_copy_pages(काष्ठा radeon_device *rdev,
			    काष्ठा radeon_ib *ib,
			    uपूर्णांक64_t pe, uपूर्णांक64_t src,
			    अचिन्हित count);
व्योम cik_sdma_vm_ग_लिखो_pages(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_ib *ib,
			     uपूर्णांक64_t pe,
			     uपूर्णांक64_t addr, अचिन्हित count,
			     uपूर्णांक32_t incr, uपूर्णांक32_t flags);
व्योम cik_sdma_vm_set_pages(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ib *ib,
			   uपूर्णांक64_t pe,
			   uपूर्णांक64_t addr, अचिन्हित count,
			   uपूर्णांक32_t incr, uपूर्णांक32_t flags);
व्योम cik_sdma_vm_pad_ib(काष्ठा radeon_ib *ib);

व्योम cik_dma_vm_flush(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
		      अचिन्हित vm_id, uपूर्णांक64_t pd_addr);
पूर्णांक cik_ib_parse(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
u32 cik_gfx_get_rptr(काष्ठा radeon_device *rdev,
		     काष्ठा radeon_ring *ring);
u32 cik_gfx_get_wptr(काष्ठा radeon_device *rdev,
		     काष्ठा radeon_ring *ring);
व्योम cik_gfx_set_wptr(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_ring *ring);
u32 cik_compute_get_rptr(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_ring *ring);
u32 cik_compute_get_wptr(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_ring *ring);
व्योम cik_compute_set_wptr(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_ring *ring);
u32 cik_sdma_get_rptr(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_ring *ring);
u32 cik_sdma_get_wptr(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_ring *ring);
व्योम cik_sdma_set_wptr(काष्ठा radeon_device *rdev,
		       काष्ठा radeon_ring *ring);
पूर्णांक ci_get_temp(काष्ठा radeon_device *rdev);
पूर्णांक kv_get_temp(काष्ठा radeon_device *rdev);
पूर्णांक cik_get_allowed_info_रेजिस्टर(काष्ठा radeon_device *rdev,
				  u32 reg, u32 *val);

पूर्णांक ci_dpm_init(काष्ठा radeon_device *rdev);
पूर्णांक ci_dpm_enable(काष्ठा radeon_device *rdev);
पूर्णांक ci_dpm_late_enable(काष्ठा radeon_device *rdev);
व्योम ci_dpm_disable(काष्ठा radeon_device *rdev);
पूर्णांक ci_dpm_pre_set_घातer_state(काष्ठा radeon_device *rdev);
पूर्णांक ci_dpm_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम ci_dpm_post_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम ci_dpm_setup_asic(काष्ठा radeon_device *rdev);
व्योम ci_dpm_display_configuration_changed(काष्ठा radeon_device *rdev);
व्योम ci_dpm_fini(काष्ठा radeon_device *rdev);
u32 ci_dpm_get_sclk(काष्ठा radeon_device *rdev, bool low);
u32 ci_dpm_get_mclk(काष्ठा radeon_device *rdev, bool low);
व्योम ci_dpm_prपूर्णांक_घातer_state(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_ps *ps);
व्योम ci_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
						    काष्ठा seq_file *m);
पूर्णांक ci_dpm_क्रमce_perक्रमmance_level(काष्ठा radeon_device *rdev,
				   क्रमागत radeon_dpm_क्रमced_level level);
bool ci_dpm_vblank_too_लघु(काष्ठा radeon_device *rdev);
व्योम ci_dpm_घातergate_uvd(काष्ठा radeon_device *rdev, bool gate);
u32 ci_dpm_get_current_sclk(काष्ठा radeon_device *rdev);
u32 ci_dpm_get_current_mclk(काष्ठा radeon_device *rdev);

पूर्णांक ci_fan_ctrl_get_fan_speed_percent(काष्ठा radeon_device *rdev,
						 u32 *speed);
पूर्णांक ci_fan_ctrl_set_fan_speed_percent(काष्ठा radeon_device *rdev,
						 u32 speed);
u32 ci_fan_ctrl_get_mode(काष्ठा radeon_device *rdev);
व्योम ci_fan_ctrl_set_mode(काष्ठा radeon_device *rdev, u32 mode);

पूर्णांक kv_dpm_init(काष्ठा radeon_device *rdev);
पूर्णांक kv_dpm_enable(काष्ठा radeon_device *rdev);
पूर्णांक kv_dpm_late_enable(काष्ठा radeon_device *rdev);
व्योम kv_dpm_disable(काष्ठा radeon_device *rdev);
पूर्णांक kv_dpm_pre_set_घातer_state(काष्ठा radeon_device *rdev);
पूर्णांक kv_dpm_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम kv_dpm_post_set_घातer_state(काष्ठा radeon_device *rdev);
व्योम kv_dpm_setup_asic(काष्ठा radeon_device *rdev);
व्योम kv_dpm_display_configuration_changed(काष्ठा radeon_device *rdev);
व्योम kv_dpm_fini(काष्ठा radeon_device *rdev);
u32 kv_dpm_get_sclk(काष्ठा radeon_device *rdev, bool low);
u32 kv_dpm_get_mclk(काष्ठा radeon_device *rdev, bool low);
व्योम kv_dpm_prपूर्णांक_घातer_state(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_ps *ps);
व्योम kv_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
						    काष्ठा seq_file *m);
पूर्णांक kv_dpm_क्रमce_perक्रमmance_level(काष्ठा radeon_device *rdev,
				   क्रमागत radeon_dpm_क्रमced_level level);
व्योम kv_dpm_घातergate_uvd(काष्ठा radeon_device *rdev, bool gate);
व्योम kv_dpm_enable_bapm(काष्ठा radeon_device *rdev, bool enable);
u32 kv_dpm_get_current_sclk(काष्ठा radeon_device *rdev);
u32 kv_dpm_get_current_mclk(काष्ठा radeon_device *rdev);

/* uvd v1.0 */
uपूर्णांक32_t uvd_v1_0_get_rptr(काष्ठा radeon_device *rdev,
                           काष्ठा radeon_ring *ring);
uपूर्णांक32_t uvd_v1_0_get_wptr(काष्ठा radeon_device *rdev,
                           काष्ठा radeon_ring *ring);
व्योम uvd_v1_0_set_wptr(काष्ठा radeon_device *rdev,
                       काष्ठा radeon_ring *ring);
पूर्णांक uvd_v1_0_resume(काष्ठा radeon_device *rdev);

पूर्णांक uvd_v1_0_init(काष्ठा radeon_device *rdev);
व्योम uvd_v1_0_fini(काष्ठा radeon_device *rdev);
पूर्णांक uvd_v1_0_start(काष्ठा radeon_device *rdev);
व्योम uvd_v1_0_stop(काष्ठा radeon_device *rdev);

पूर्णांक uvd_v1_0_ring_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
व्योम uvd_v1_0_fence_emit(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_fence *fence);
पूर्णांक uvd_v1_0_ib_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
bool uvd_v1_0_semaphore_emit(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_ring *ring,
			     काष्ठा radeon_semaphore *semaphore,
			     bool emit_रुको);
व्योम uvd_v1_0_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);

/* uvd v2.2 */
पूर्णांक uvd_v2_2_resume(काष्ठा radeon_device *rdev);
व्योम uvd_v2_2_fence_emit(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_fence *fence);
bool uvd_v2_2_semaphore_emit(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_ring *ring,
			     काष्ठा radeon_semaphore *semaphore,
			     bool emit_रुको);

/* uvd v3.1 */
bool uvd_v3_1_semaphore_emit(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_ring *ring,
			     काष्ठा radeon_semaphore *semaphore,
			     bool emit_रुको);

/* uvd v4.2 */
पूर्णांक uvd_v4_2_resume(काष्ठा radeon_device *rdev);

/* vce v1.0 */
uपूर्णांक32_t vce_v1_0_get_rptr(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ring *ring);
uपूर्णांक32_t vce_v1_0_get_wptr(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ring *ring);
व्योम vce_v1_0_set_wptr(काष्ठा radeon_device *rdev,
		       काष्ठा radeon_ring *ring);
पूर्णांक vce_v1_0_load_fw(काष्ठा radeon_device *rdev, uपूर्णांक32_t *data);
अचिन्हित vce_v1_0_bo_size(काष्ठा radeon_device *rdev);
पूर्णांक vce_v1_0_resume(काष्ठा radeon_device *rdev);
पूर्णांक vce_v1_0_init(काष्ठा radeon_device *rdev);
पूर्णांक vce_v1_0_start(काष्ठा radeon_device *rdev);

/* vce v2.0 */
अचिन्हित vce_v2_0_bo_size(काष्ठा radeon_device *rdev);
पूर्णांक vce_v2_0_resume(काष्ठा radeon_device *rdev);

#पूर्ण_अगर
