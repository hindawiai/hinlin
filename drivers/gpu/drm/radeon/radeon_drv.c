<शैली गुरु>
/*
 * \पile radeon_drv.c
 * ATI Radeon driver
 *
 * \चuthor Gareth Hughes <gareth@valinux.com>
 */

/*
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */


#समावेश <linux/compat.h>
#समावेश <linux/console.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/vga_चयनeroo.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_pciids.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon_drv.h"
#समावेश "radeon.h"
#समावेश "radeon_kms.h"
#समावेश "radeon_ttm.h"
#समावेश "radeon_device.h"
#समावेश "radeon_prime.h"

/*
 * KMS wrapper.
 * - 2.0.0 - initial पूर्णांकerface
 * - 2.1.0 - add square tiling पूर्णांकerface
 * - 2.2.0 - add r6xx/r7xx स्थिर buffer support
 * - 2.3.0 - add MSPOS + 3D texture + r500 VAP regs
 * - 2.4.0 - add crtc id query
 * - 2.5.0 - add get accel 2 to work around ddx अवरोधage क्रम evergreen
 * - 2.6.0 - add tiling config query (r6xx+), add initial HiZ support (r300->r500)
 *   2.7.0 - fixups क्रम r600 2D tiling support. (no बाह्यal ABI change), add eg dyn gpr regs
 *   2.8.0 - pageflip support, r500 US_FORMAT regs. r500 ARGB2101010 colorbuf, r300->r500 CMASK, घड़ी crystal query
 *   2.9.0 - r600 tiling (s3tc,rgtc) working, SET_PREDICATION packet 3 on r600 + eg, backend query
 *   2.10.0 - fusion 2D tiling
 *   2.11.0 - backend map, initial compute support क्रम the CS checker
 *   2.12.0 - RADEON_CS_KEEP_TILING_FLAGS
 *   2.13.0 - भव memory support, streamout
 *   2.14.0 - add evergreen tiling inक्रमmations
 *   2.15.0 - add max_pipes query
 *   2.16.0 - fix evergreen 2D tiled surface calculation
 *   2.17.0 - add STRMOUT_BASE_UPDATE क्रम r7xx
 *   2.18.0 - r600-eg: allow "invalid" DB क्रमmats
 *   2.19.0 - r600-eg: MSAA textures
 *   2.20.0 - r600-si: RADEON_INFO_TIMESTAMP query
 *   2.21.0 - r600-r700: FMASK and CMASK
 *   2.22.0 - r600 only: RESOLVE_BOX allowed
 *   2.23.0 - allow STRMOUT_BASE_UPDATE on RS780 and RS880
 *   2.24.0 - eg only: allow MIP_ADDRESS=0 क्रम MSAA textures
 *   2.25.0 - eg+: new info request क्रम num SE and num SH
 *   2.26.0 - r600-eg: fix htile size computation
 *   2.27.0 - r600-SI: Add CS ioctl support क्रम async DMA
 *   2.28.0 - r600-eg: Add MEM_WRITE packet support
 *   2.29.0 - R500 FP16 color clear रेजिस्टरs
 *   2.30.0 - fix क्रम FMASK texturing
 *   2.31.0 - Add fastfb support क्रम rs690
 *   2.32.0 - new info request क्रम rings working
 *   2.33.0 - Add SI tiling mode array query
 *   2.34.0 - Add CIK tiling mode array query
 *   2.35.0 - Add CIK macrotile mode array query
 *   2.36.0 - Fix CIK DCE tiling setup
 *   2.37.0 - allow GS ring setup on r6xx/r7xx
 *   2.38.0 - RADEON_GEM_OP (GET_INITIAL_DOMAIN, SET_INITIAL_DOMAIN),
 *            CIK: 1D and linear tiling modes contain valid PIPE_CONFIG
 *   2.39.0 - Add INFO query क्रम number of active CUs
 *   2.40.0 - Add RADEON_GEM_GTT_WC/UC, flush HDP cache beक्रमe submitting
 *            CS to GPU on >= r600
 *   2.41.0 - evergreen/cayman: Add SET_BASE/DRAW_INसूचीECT command parsing support
 *   2.42.0 - Add VCE/VUI (Video Usability Inक्रमmation) support
 *   2.43.0 - RADEON_INFO_GPU_RESET_COUNTER
 *   2.44.0 - SET_APPEND_CNT packet3 support
 *   2.45.0 - Allow setting shader रेजिस्टरs using DMA/COPY packet3 on SI
 *   2.46.0 - Add PFP_SYNC_ME support on evergreen
 *   2.47.0 - Add UVD_NO_OP रेजिस्टर support
 *   2.48.0 - TA_CS_BC_BASE_ADDR allowed on SI
 *   2.49.0 - DRM_RADEON_GEM_INFO ioctl वापसs correct vram_size/visible values
 *   2.50.0 - Allows unaligned shader loads on CIK. (needed by OpenGL)
 */
#घोषणा KMS_DRIVER_MAJOR	2
#घोषणा KMS_DRIVER_MINOR	50
#घोषणा KMS_DRIVER_PATCHLEVEL	0
पूर्णांक radeon_suspend_kms(काष्ठा drm_device *dev, bool suspend,
		       bool fbcon, bool मुक्तze);
पूर्णांक radeon_resume_kms(काष्ठा drm_device *dev, bool resume, bool fbcon);
बाह्य पूर्णांक radeon_get_crtc_scanoutpos(काष्ठा drm_device *dev, अचिन्हित पूर्णांक crtc,
				      अचिन्हित पूर्णांक flags, पूर्णांक *vpos, पूर्णांक *hpos,
				      kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
				      स्थिर काष्ठा drm_display_mode *mode);
बाह्य bool radeon_is_px(काष्ठा drm_device *dev);
पूर्णांक radeon_mode_dumb_mmap(काष्ठा drm_file *filp,
			  काष्ठा drm_device *dev,
			  uपूर्णांक32_t handle, uपूर्णांक64_t *offset_p);
पूर्णांक radeon_mode_dumb_create(काष्ठा drm_file *file_priv,
			    काष्ठा drm_device *dev,
			    काष्ठा drm_mode_create_dumb *args);

/* atpx handler */
#अगर defined(CONFIG_VGA_SWITCHEROO)
व्योम radeon_रेजिस्टर_atpx_handler(व्योम);
व्योम radeon_unरेजिस्टर_atpx_handler(व्योम);
bool radeon_has_atpx_dgpu_घातer_cntl(व्योम);
bool radeon_is_atpx_hybrid(व्योम);
#अन्यथा
अटल अंतरभूत व्योम radeon_रेजिस्टर_atpx_handler(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम radeon_unरेजिस्टर_atpx_handler(व्योम) अणुपूर्ण
अटल अंतरभूत bool radeon_has_atpx_dgpu_घातer_cntl(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool radeon_is_atpx_hybrid(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

पूर्णांक radeon_no_wb;
पूर्णांक radeon_modeset = -1;
पूर्णांक radeon_dynclks = -1;
पूर्णांक radeon_r4xx_atom = 0;
पूर्णांक radeon_agpmode = -1;
पूर्णांक radeon_vram_limit = 0;
पूर्णांक radeon_gart_size = -1; /* स्वतः */
पूर्णांक radeon_benchmarking = 0;
पूर्णांक radeon_testing = 0;
पूर्णांक radeon_connector_table = 0;
पूर्णांक radeon_tv = 1;
पूर्णांक radeon_audio = -1;
पूर्णांक radeon_disp_priority = 0;
पूर्णांक radeon_hw_i2c = 0;
पूर्णांक radeon_pcie_gen2 = -1;
पूर्णांक radeon_msi = -1;
पूर्णांक radeon_lockup_समयout = 10000;
पूर्णांक radeon_fastfb = 0;
पूर्णांक radeon_dpm = -1;
पूर्णांक radeon_aspm = -1;
पूर्णांक radeon_runसमय_pm = -1;
पूर्णांक radeon_hard_reset = 0;
पूर्णांक radeon_vm_size = 8;
पूर्णांक radeon_vm_block_size = -1;
पूर्णांक radeon_deep_color = 0;
पूर्णांक radeon_use_pflipirq = 2;
पूर्णांक radeon_bapm = -1;
पूर्णांक radeon_backlight = -1;
पूर्णांक radeon_auxch = -1;
पूर्णांक radeon_mst = 0;
पूर्णांक radeon_uvd = 1;
पूर्णांक radeon_vce = 1;

MODULE_PARM_DESC(no_wb, "Disable AGP writeback for scratch registers");
module_param_named(no_wb, radeon_no_wb, पूर्णांक, 0444);

MODULE_PARM_DESC(modeset, "Disable/Enable modesetting");
module_param_named(modeset, radeon_modeset, पूर्णांक, 0400);

MODULE_PARM_DESC(dynclks, "Disable/Enable dynamic clocks");
module_param_named(dynclks, radeon_dynclks, पूर्णांक, 0444);

MODULE_PARM_DESC(r4xx_atom, "Enable ATOMBIOS modesetting for R4xx");
module_param_named(r4xx_atom, radeon_r4xx_atom, पूर्णांक, 0444);

MODULE_PARM_DESC(vramlimit, "Restrict VRAM for testing, in megabytes");
module_param_named(vramlimit, radeon_vram_limit, पूर्णांक, 0600);

MODULE_PARM_DESC(agpmode, "AGP Mode (-1 == PCI)");
module_param_named(agpmode, radeon_agpmode, पूर्णांक, 0444);

MODULE_PARM_DESC(gartsize, "Size of PCIE/IGP gart to setup in megabytes (32, 64, etc., -1 = auto)");
module_param_named(gartsize, radeon_gart_size, पूर्णांक, 0600);

MODULE_PARM_DESC(benchmark, "Run benchmark");
module_param_named(benchmark, radeon_benchmarking, पूर्णांक, 0444);

MODULE_PARM_DESC(test, "Run tests");
module_param_named(test, radeon_testing, पूर्णांक, 0444);

MODULE_PARM_DESC(connector_table, "Force connector table");
module_param_named(connector_table, radeon_connector_table, पूर्णांक, 0444);

MODULE_PARM_DESC(tv, "TV enable (0 = disable)");
module_param_named(tv, radeon_tv, पूर्णांक, 0444);

MODULE_PARM_DESC(audio, "Audio enable (-1 = auto, 0 = disable, 1 = enable)");
module_param_named(audio, radeon_audio, पूर्णांक, 0444);

MODULE_PARM_DESC(disp_priority, "Display Priority (0 = auto, 1 = normal, 2 = high)");
module_param_named(disp_priority, radeon_disp_priority, पूर्णांक, 0444);

MODULE_PARM_DESC(hw_i2c, "hw i2c engine enable (0 = disable)");
module_param_named(hw_i2c, radeon_hw_i2c, पूर्णांक, 0444);

MODULE_PARM_DESC(pcie_gen2, "PCIE Gen2 mode (-1 = auto, 0 = disable, 1 = enable)");
module_param_named(pcie_gen2, radeon_pcie_gen2, पूर्णांक, 0444);

MODULE_PARM_DESC(msi, "MSI support (1 = enable, 0 = disable, -1 = auto)");
module_param_named(msi, radeon_msi, पूर्णांक, 0444);

MODULE_PARM_DESC(lockup_समयout, "GPU lockup timeout in ms (default 10000 = 10 seconds, 0 = disable)");
module_param_named(lockup_समयout, radeon_lockup_समयout, पूर्णांक, 0444);

MODULE_PARM_DESC(fastfb, "Direct FB access for IGP chips (0 = disable, 1 = enable)");
module_param_named(fastfb, radeon_fastfb, पूर्णांक, 0444);

MODULE_PARM_DESC(dpm, "DPM support (1 = enable, 0 = disable, -1 = auto)");
module_param_named(dpm, radeon_dpm, पूर्णांक, 0444);

MODULE_PARM_DESC(aspm, "ASPM support (1 = enable, 0 = disable, -1 = auto)");
module_param_named(aspm, radeon_aspm, पूर्णांक, 0444);

MODULE_PARM_DESC(runpm, "PX runtime pm (1 = force enable, 0 = disable, -1 = PX only default)");
module_param_named(runpm, radeon_runसमय_pm, पूर्णांक, 0444);

MODULE_PARM_DESC(hard_reset, "PCI config reset (1 = force enable, 0 = disable (default))");
module_param_named(hard_reset, radeon_hard_reset, पूर्णांक, 0444);

MODULE_PARM_DESC(vm_size, "VM address space size in gigabytes (default 4GB)");
module_param_named(vm_size, radeon_vm_size, पूर्णांक, 0444);

MODULE_PARM_DESC(vm_block_size, "VM page table size in bits (default depending on vm_size)");
module_param_named(vm_block_size, radeon_vm_block_size, पूर्णांक, 0444);

MODULE_PARM_DESC(deep_color, "Deep Color support (1 = enable, 0 = disable (default))");
module_param_named(deep_color, radeon_deep_color, पूर्णांक, 0444);

MODULE_PARM_DESC(use_pflipirq, "Pflip irqs for pageflip completion (0 = disable, 1 = as fallback, 2 = exclusive (default))");
module_param_named(use_pflipirq, radeon_use_pflipirq, पूर्णांक, 0444);

MODULE_PARM_DESC(bapm, "BAPM support (1 = enable, 0 = disable, -1 = auto)");
module_param_named(bapm, radeon_bapm, पूर्णांक, 0444);

MODULE_PARM_DESC(backlight, "backlight support (1 = enable, 0 = disable, -1 = auto)");
module_param_named(backlight, radeon_backlight, पूर्णांक, 0444);

MODULE_PARM_DESC(auxch, "Use native auxch experimental support (1 = enable, 0 = disable, -1 = auto)");
module_param_named(auxch, radeon_auxch, पूर्णांक, 0444);

MODULE_PARM_DESC(mst, "DisplayPort MST experimental support (1 = enable, 0 = disable)");
module_param_named(mst, radeon_mst, पूर्णांक, 0444);

MODULE_PARM_DESC(uvd, "uvd enable/disable uvd support (1 = enable, 0 = disable)");
module_param_named(uvd, radeon_uvd, पूर्णांक, 0444);

MODULE_PARM_DESC(vce, "vce enable/disable vce support (1 = enable, 0 = disable)");
module_param_named(vce, radeon_vce, पूर्णांक, 0444);

पूर्णांक radeon_si_support = 1;
MODULE_PARM_DESC(si_support, "SI support (1 = enabled (default), 0 = disabled)");
module_param_named(si_support, radeon_si_support, पूर्णांक, 0444);

पूर्णांक radeon_cik_support = 1;
MODULE_PARM_DESC(cik_support, "CIK support (1 = enabled (default), 0 = disabled)");
module_param_named(cik_support, radeon_cik_support, पूर्णांक, 0444);

अटल काष्ठा pci_device_id pciidlist[] = अणु
	radeon_PCI_IDS
पूर्ण;

MODULE_DEVICE_TABLE(pci, pciidlist);

अटल स्थिर काष्ठा drm_driver kms_driver;

अटल पूर्णांक radeon_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा drm_device *dev;
	पूर्णांक ret;

	अगर (!ent)
		वापस -ENODEV; /* Aव्योम शून्य-ptr deref in drm_get_pci_dev */

	flags = ent->driver_data;

	अगर (!radeon_si_support) अणु
		चयन (flags & RADEON_FAMILY_MASK) अणु
		हाल CHIP_TAHITI:
		हाल CHIP_PITCAIRN:
		हाल CHIP_VERDE:
		हाल CHIP_OLAND:
		हाल CHIP_HAIन_अंक:
			dev_info(&pdev->dev,
				 "SI support disabled by module param\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	अगर (!radeon_cik_support) अणु
		चयन (flags & RADEON_FAMILY_MASK) अणु
		हाल CHIP_KAVERI:
		हाल CHIP_BONAIRE:
		हाल CHIP_HAWAII:
		हाल CHIP_KABINI:
		हाल CHIP_MULLINS:
			dev_info(&pdev->dev,
				 "CIK support disabled by module param\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (vga_चयनeroo_client_probe_defer(pdev))
		वापस -EPROBE_DEFER;

	/* Get rid of things like offb */
	ret = drm_fb_helper_हटाओ_conflicting_pci_framebuffers(pdev, "radeondrmfb");
	अगर (ret)
		वापस ret;

	dev = drm_dev_alloc(&kms_driver, &pdev->dev);
	अगर (IS_ERR(dev))
		वापस PTR_ERR(dev);

	ret = pci_enable_device(pdev);
	अगर (ret)
		जाओ err_मुक्त;

	pci_set_drvdata(pdev, dev);

	अगर (pci_find_capability(pdev, PCI_CAP_ID_AGP))
		dev->agp = drm_agp_init(dev);
	अगर (dev->agp) अणु
		dev->agp->agp_mtrr = arch_phys_wc_add(
			dev->agp->agp_info.aper_base,
			dev->agp->agp_info.aper_size *
			1024 * 1024);
	पूर्ण

	ret = drm_dev_रेजिस्टर(dev, ent->driver_data);
	अगर (ret)
		जाओ err_agp;

	वापस 0;

err_agp:
	अगर (dev->agp)
		arch_phys_wc_del(dev->agp->agp_mtrr);
	kमुक्त(dev->agp);
	pci_disable_device(pdev);
err_मुक्त:
	drm_dev_put(dev);
	वापस ret;
पूर्ण

अटल व्योम
radeon_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

	drm_put_dev(dev);
पूर्ण

अटल व्योम
radeon_pci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	/* अगर we are running in a VM, make sure the device
	 * torn करोwn properly on reboot/shutकरोwn
	 */
	अगर (radeon_device_is_भव())
		radeon_pci_हटाओ(pdev);

#अगर_घोषित CONFIG_PPC64
	/*
	 * Some adapters need to be suspended beक्रमe a
	 * shutकरोwn occurs in order to prevent an error
	 * during kexec.
	 * Make this घातer specअगरic becauase it अवरोधs
	 * some non-घातer boards.
	 */
	radeon_suspend_kms(pci_get_drvdata(pdev), true, true, false);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक radeon_pmops_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	वापस radeon_suspend_kms(drm_dev, true, true, false);
पूर्ण

अटल पूर्णांक radeon_pmops_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	/* GPU comes up enabled by the bios on resume */
	अगर (radeon_is_px(drm_dev)) अणु
		pm_runसमय_disable(dev);
		pm_runसमय_set_active(dev);
		pm_runसमय_enable(dev);
	पूर्ण

	वापस radeon_resume_kms(drm_dev, true, true);
पूर्ण

अटल पूर्णांक radeon_pmops_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	वापस radeon_suspend_kms(drm_dev, false, true, true);
पूर्ण

अटल पूर्णांक radeon_pmops_thaw(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	वापस radeon_resume_kms(drm_dev, false, true);
पूर्ण

अटल पूर्णांक radeon_pmops_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *drm_dev = pci_get_drvdata(pdev);

	अगर (!radeon_is_px(drm_dev)) अणु
		pm_runसमय_क्रमbid(dev);
		वापस -EBUSY;
	पूर्ण

	drm_dev->चयन_घातer_state = DRM_SWITCH_POWER_CHANGING;
	drm_kms_helper_poll_disable(drm_dev);

	radeon_suspend_kms(drm_dev, false, false, false);
	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_ignore_hotplug(pdev);
	अगर (radeon_is_atpx_hybrid())
		pci_set_घातer_state(pdev, PCI_D3cold);
	अन्यथा अगर (!radeon_has_atpx_dgpu_घातer_cntl())
		pci_set_घातer_state(pdev, PCI_D3hot);
	drm_dev->चयन_घातer_state = DRM_SWITCH_POWER_DYNAMIC_OFF;

	वापस 0;
पूर्ण

अटल पूर्णांक radeon_pmops_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *drm_dev = pci_get_drvdata(pdev);
	पूर्णांक ret;

	अगर (!radeon_is_px(drm_dev))
		वापस -EINVAL;

	drm_dev->चयन_घातer_state = DRM_SWITCH_POWER_CHANGING;

	अगर (radeon_is_atpx_hybrid() ||
	    !radeon_has_atpx_dgpu_घातer_cntl())
		pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;
	pci_set_master(pdev);

	ret = radeon_resume_kms(drm_dev, false, false);
	drm_kms_helper_poll_enable(drm_dev);
	drm_dev->चयन_घातer_state = DRM_SWITCH_POWER_ON;
	वापस 0;
पूर्ण

अटल पूर्णांक radeon_pmops_runसमय_idle(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	काष्ठा drm_crtc *crtc;

	अगर (!radeon_is_px(drm_dev)) अणु
		pm_runसमय_क्रमbid(dev);
		वापस -EBUSY;
	पूर्ण

	list_क्रम_each_entry(crtc, &drm_dev->mode_config.crtc_list, head) अणु
		अगर (crtc->enabled) अणु
			DRM_DEBUG_DRIVER("failing to power off - crtc active\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_स्वतःsuspend(dev);
	/* we करोn't want the मुख्य rpm_idle to call suspend - we want to स्वतःsuspend */
	वापस 1;
पूर्ण

दीर्घ radeon_drm_ioctl(काष्ठा file *filp,
		      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा drm_file *file_priv = filp->निजी_data;
	काष्ठा drm_device *dev;
	दीर्घ ret;
	dev = file_priv->minor->dev;
	ret = pm_runसमय_get_sync(dev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(dev->dev);
		वापस ret;
	पूर्ण

	ret = drm_ioctl(filp, cmd, arg);

	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ radeon_kms_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अचिन्हित पूर्णांक nr = DRM_IOCTL_NR(cmd);
	पूर्णांक ret;

	अगर (nr < DRM_COMMAND_BASE)
		वापस drm_compat_ioctl(filp, cmd, arg);

	ret = radeon_drm_ioctl(filp, cmd, arg);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops radeon_pm_ops = अणु
	.suspend = radeon_pmops_suspend,
	.resume = radeon_pmops_resume,
	.मुक्तze = radeon_pmops_मुक्तze,
	.thaw = radeon_pmops_thaw,
	.घातeroff = radeon_pmops_मुक्तze,
	.restore = radeon_pmops_resume,
	.runसमय_suspend = radeon_pmops_runसमय_suspend,
	.runसमय_resume = radeon_pmops_runसमय_resume,
	.runसमय_idle = radeon_pmops_runसमय_idle,
पूर्ण;

अटल स्थिर काष्ठा file_operations radeon_driver_kms_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drm_खोलो,
	.release = drm_release,
	.unlocked_ioctl = radeon_drm_ioctl,
	.mmap = radeon_mmap,
	.poll = drm_poll,
	.पढ़ो = drm_पढ़ो,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = radeon_kms_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा drm_ioctl_desc radeon_ioctls_kms[] = अणु
	DRM_IOCTL_DEF_DRV(RADEON_CP_INIT, drm_invalid_op, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(RADEON_CP_START, drm_invalid_op, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(RADEON_CP_STOP, drm_invalid_op, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(RADEON_CP_RESET, drm_invalid_op, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(RADEON_CP_IDLE, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_CP_RESUME, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_RESET, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_FULLSCREEN, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_SWAP, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_CLEAR, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_VERTEX, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_INDICES, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_TEXTURE, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_STIPPLE, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_INसूचीECT, drm_invalid_op, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(RADEON_VERTEX2, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_CMDBUF, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_GETPARAM, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_FLIP, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_ALLOC, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_FREE, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_INIT_HEAP, drm_invalid_op, DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(RADEON_IRQ_EMIT, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_IRQ_WAIT, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_SETPARAM, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_SURF_ALLOC, drm_invalid_op, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_SURF_FREE, drm_invalid_op, DRM_AUTH),
	/* KMS */
	DRM_IOCTL_DEF_DRV(RADEON_GEM_INFO, radeon_gem_info_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(RADEON_GEM_CREATE, radeon_gem_create_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(RADEON_GEM_MMAP, radeon_gem_mmap_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(RADEON_GEM_SET_DOMAIN, radeon_gem_set_करोमुख्य_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(RADEON_GEM_PREAD, radeon_gem_pपढ़ो_ioctl, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_GEM_PWRITE, radeon_gem_pग_लिखो_ioctl, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(RADEON_GEM_WAIT_IDLE, radeon_gem_रुको_idle_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(RADEON_CS, radeon_cs_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(RADEON_INFO, radeon_info_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(RADEON_GEM_SET_TILING, radeon_gem_set_tiling_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(RADEON_GEM_GET_TILING, radeon_gem_get_tiling_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(RADEON_GEM_BUSY, radeon_gem_busy_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(RADEON_GEM_VA, radeon_gem_va_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(RADEON_GEM_OP, radeon_gem_op_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(RADEON_GEM_USERPTR, radeon_gem_userptr_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
पूर्ण;

अटल स्थिर काष्ठा drm_driver kms_driver = अणु
	.driver_features =
	    DRIVER_GEM | DRIVER_RENDER | DRIVER_MODESET,
	.load = radeon_driver_load_kms,
	.खोलो = radeon_driver_खोलो_kms,
	.postबंद = radeon_driver_postबंद_kms,
	.lastबंद = radeon_driver_lastबंद_kms,
	.unload = radeon_driver_unload_kms,
	.irq_preinstall = radeon_driver_irq_preinstall_kms,
	.irq_postinstall = radeon_driver_irq_postinstall_kms,
	.irq_uninstall = radeon_driver_irq_uninstall_kms,
	.irq_handler = radeon_driver_irq_handler_kms,
	.ioctls = radeon_ioctls_kms,
	.num_ioctls = ARRAY_SIZE(radeon_ioctls_kms),
	.dumb_create = radeon_mode_dumb_create,
	.dumb_map_offset = radeon_mode_dumb_mmap,
	.fops = &radeon_driver_kms_fops,

	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_import_sg_table = radeon_gem_prime_import_sg_table,

	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = KMS_DRIVER_MAJOR,
	.minor = KMS_DRIVER_MINOR,
	.patchlevel = KMS_DRIVER_PATCHLEVEL,
पूर्ण;

अटल काष्ठा pci_driver radeon_kms_pci_driver = अणु
	.name = DRIVER_NAME,
	.id_table = pciidlist,
	.probe = radeon_pci_probe,
	.हटाओ = radeon_pci_हटाओ,
	.shutकरोwn = radeon_pci_shutकरोwn,
	.driver.pm = &radeon_pm_ops,
पूर्ण;

अटल पूर्णांक __init radeon_module_init(व्योम)
अणु
	अगर (vgacon_text_क्रमce() && radeon_modeset == -1) अणु
		DRM_INFO("VGACON disable radeon kernel modesetting.\n");
		radeon_modeset = 0;
	पूर्ण

	अगर (radeon_modeset == 0) अणु
		DRM_ERROR("No UMS support in radeon module!\n");
		वापस -EINVAL;
	पूर्ण

	DRM_INFO("radeon kernel modesetting enabled.\n");
	radeon_रेजिस्टर_atpx_handler();

	वापस pci_रेजिस्टर_driver(&radeon_kms_pci_driver);
पूर्ण

अटल व्योम __निकास radeon_module_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&radeon_kms_pci_driver);
	radeon_unरेजिस्टर_atpx_handler();
	mmu_notअगरier_synchronize();
पूर्ण

module_init(radeon_module_init);
module_निकास(radeon_module_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL and additional rights");
