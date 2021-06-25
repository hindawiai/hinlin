<शैली गुरु>
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

#समावेश <drm/amdgpu_drm.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/drm_managed.h>
#समावेश "amdgpu_drv.h"

#समावेश <drm/drm_pciids.h>
#समावेश <linux/console.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/vga_चयनeroo.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/suspend.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_irq.h"
#समावेश "amdgpu_dma_buf.h"
#समावेश "amdgpu_sched.h"

#समावेश "amdgpu_amdkfd.h"

#समावेश "amdgpu_ras.h"
#समावेश "amdgpu_xgmi.h"
#समावेश "amdgpu_reset.h"

/*
 * KMS wrapper.
 * - 3.0.0 - initial driver
 * - 3.1.0 - allow पढ़ोing more status रेजिस्टरs (GRBM, SRBM, SDMA, CP)
 * - 3.2.0 - GFX8: Uses EOP_TC_WB_ACTION_EN, so UMDs करोn't have to करो the same
 *           at the end of IBs.
 * - 3.3.0 - Add VM support क्रम UVD on supported hardware.
 * - 3.4.0 - Add AMDGPU_INFO_NUM_EVICTIONS.
 * - 3.5.0 - Add support क्रम new UVD_NO_OP रेजिस्टर.
 * - 3.6.0 - kmd involves use CONTEXT_CONTROL in ring buffer.
 * - 3.7.0 - Add support क्रम VCE घड़ी list packet
 * - 3.8.0 - Add support raster config init in the kernel
 * - 3.9.0 - Add support क्रम memory query info about VRAM and GTT.
 * - 3.10.0 - Add support क्रम new fences ioctl, new gem ioctl flags
 * - 3.11.0 - Add support क्रम sensor query info (घड़ीs, temp, etc).
 * - 3.12.0 - Add query क्रम द्विगुन offchip LDS buffers
 * - 3.13.0 - Add PRT support
 * - 3.14.0 - Fix race in amdgpu_ctx_get_fence() and note new functionality
 * - 3.15.0 - Export more gpu info क्रम gfx9
 * - 3.16.0 - Add reserved vmid support
 * - 3.17.0 - Add AMDGPU_NUM_VRAM_CPU_PAGE_FAULTS.
 * - 3.18.0 - Export gpu always on cu biपंचांगap
 * - 3.19.0 - Add support क्रम UVD MJPEG decode
 * - 3.20.0 - Add support क्रम local BOs
 * - 3.21.0 - Add DRM_AMDGPU_FENCE_TO_HANDLE ioctl
 * - 3.22.0 - Add DRM_AMDGPU_SCHED ioctl
 * - 3.23.0 - Add query क्रम VRAM lost counter
 * - 3.24.0 - Add high priority compute support क्रम gfx9
 * - 3.25.0 - Add support क्रम sensor query info (stable pstate sclk/mclk).
 * - 3.26.0 - GFX9: Process AMDGPU_IB_FLAG_TC_WB_NOT_INVALIDATE.
 * - 3.27.0 - Add new chunk to to AMDGPU_CS to enable BO_LIST creation.
 * - 3.28.0 - Add AMDGPU_CHUNK_ID_SCHEDULED_DEPENDENCIES
 * - 3.29.0 - Add AMDGPU_IB_FLAG_RESET_GDS_MAX_WAVE_ID
 * - 3.30.0 - Add AMDGPU_SCHED_OP_CONTEXT_PRIORITY_OVERRIDE.
 * - 3.31.0 - Add support क्रम per-flip tiling attribute changes with DC
 * - 3.32.0 - Add syncobj समयline support to AMDGPU_CS.
 * - 3.33.0 - Fixes क्रम GDS ENOMEM failures in AMDGPU_CS.
 * - 3.34.0 - Non-DC can flip correctly between buffers with dअगरferent pitches
 * - 3.35.0 - Add drm_amdgpu_info_device::tcc_disabled_mask
 * - 3.36.0 - Allow पढ़ोing more status रेजिस्टरs on si/cik
 * - 3.37.0 - L2 is invalidated beक्रमe SDMA IBs, needed क्रम correctness
 * - 3.38.0 - Add AMDGPU_IB_FLAG_EMIT_MEM_SYNC
 * - 3.39.0 - DMABUF implicit sync करोes a full pipeline sync
 * - 3.40.0 - Add AMDGPU_IDS_FLAGS_TMZ
 * - 3.41.0 - Add video codec query
 */
#घोषणा KMS_DRIVER_MAJOR	3
#घोषणा KMS_DRIVER_MINOR	41
#घोषणा KMS_DRIVER_PATCHLEVEL	0

पूर्णांक amdgpu_vram_limit;
पूर्णांक amdgpu_vis_vram_limit;
पूर्णांक amdgpu_gart_size = -1; /* स्वतः */
पूर्णांक amdgpu_gtt_size = -1; /* स्वतः */
पूर्णांक amdgpu_moverate = -1; /* स्वतः */
पूर्णांक amdgpu_benchmarking;
पूर्णांक amdgpu_testing;
पूर्णांक amdgpu_audio = -1;
पूर्णांक amdgpu_disp_priority;
पूर्णांक amdgpu_hw_i2c;
पूर्णांक amdgpu_pcie_gen2 = -1;
पूर्णांक amdgpu_msi = -1;
अक्षर amdgpu_lockup_समयout[AMDGPU_MAX_TIMEOUT_PARAM_LENGTH];
पूर्णांक amdgpu_dpm = -1;
पूर्णांक amdgpu_fw_load_type = -1;
पूर्णांक amdgpu_aspm = -1;
पूर्णांक amdgpu_runसमय_pm = -1;
uपूर्णांक amdgpu_ip_block_mask = 0xffffffff;
पूर्णांक amdgpu_bapm = -1;
पूर्णांक amdgpu_deep_color;
पूर्णांक amdgpu_vm_size = -1;
पूर्णांक amdgpu_vm_fragment_size = -1;
पूर्णांक amdgpu_vm_block_size = -1;
पूर्णांक amdgpu_vm_fault_stop;
पूर्णांक amdgpu_vm_debug;
पूर्णांक amdgpu_vm_update_mode = -1;
पूर्णांक amdgpu_exp_hw_support;
पूर्णांक amdgpu_dc = -1;
पूर्णांक amdgpu_sched_jobs = 32;
पूर्णांक amdgpu_sched_hw_submission = 2;
uपूर्णांक amdgpu_pcie_gen_cap;
uपूर्णांक amdgpu_pcie_lane_cap;
uपूर्णांक amdgpu_cg_mask = 0xffffffff;
uपूर्णांक amdgpu_pg_mask = 0xffffffff;
uपूर्णांक amdgpu_sdma_phase_quantum = 32;
अक्षर *amdgpu_disable_cu = शून्य;
अक्षर *amdgpu_भव_display = शून्य;

/*
 * OverDrive(bit 14) disabled by शेष
 * GFX DCS(bit 19) disabled by शेष
 */
uपूर्णांक amdgpu_pp_feature_mask = 0xfff7bfff;
uपूर्णांक amdgpu_क्रमce_दीर्घ_training;
पूर्णांक amdgpu_job_hang_limit;
पूर्णांक amdgpu_lbpw = -1;
पूर्णांक amdgpu_compute_multipipe = -1;
पूर्णांक amdgpu_gpu_recovery = -1; /* स्वतः */
पूर्णांक amdgpu_emu_mode;
uपूर्णांक amdgpu_smu_memory_pool_size;
पूर्णांक amdgpu_smu_pptable_id = -1;
/*
 * FBC (bit 0) disabled by शेष
 * MULTI_MON_PP_MCLK_SWITCH (bit 1) enabled by शेष
 *   - With this, क्रम multiple monitors in sync(e.g. with the same model),
 *     mclk चयनing will be allowed. And the mclk will be not foced to the
 *     highest. That helps saving some idle घातer.
 * DISABLE_FRACTIONAL_PWM (bit 2) disabled by शेष
 * PSR (bit 3) disabled by शेष
 */
uपूर्णांक amdgpu_dc_feature_mask = 2;
uपूर्णांक amdgpu_dc_debug_mask;
पूर्णांक amdgpu_async_gfx_ring = 1;
पूर्णांक amdgpu_mcbp;
पूर्णांक amdgpu_discovery = -1;
पूर्णांक amdgpu_mes;
पूर्णांक amdgpu_noretry = -1;
पूर्णांक amdgpu_क्रमce_asic_type = -1;
पूर्णांक amdgpu_पंचांगz = -1; /* स्वतः */
uपूर्णांक amdgpu_मुक्तsync_vid_mode;
पूर्णांक amdgpu_reset_method = -1; /* स्वतः */
पूर्णांक amdgpu_num_kcq = -1;

अटल व्योम amdgpu_drv_delayed_reset_work_handler(काष्ठा work_काष्ठा *work);

काष्ठा amdgpu_mgpu_info mgpu_info = अणु
	.mutex = __MUTEX_INITIALIZER(mgpu_info.mutex),
	.delayed_reset_work = __DELAYED_WORK_INITIALIZER(
			mgpu_info.delayed_reset_work,
			amdgpu_drv_delayed_reset_work_handler, 0),
पूर्ण;
पूर्णांक amdgpu_ras_enable = -1;
uपूर्णांक amdgpu_ras_mask = 0xffffffff;
पूर्णांक amdgpu_bad_page_threshold = -1;
काष्ठा amdgpu_watchकरोg_समयr amdgpu_watchकरोg_समयr = अणु
	.समयout_fatal_disable = false,
	.period = 0x0, /* शेष to 0x0 (समयout disable) */
पूर्ण;

/**
 * DOC: vramlimit (पूर्णांक)
 * Restrict the total amount of VRAM in MiB क्रम testing.  The शेष is 0 (Use full VRAM).
 */
MODULE_PARM_DESC(vramlimit, "Restrict VRAM for testing, in megabytes");
module_param_named(vramlimit, amdgpu_vram_limit, पूर्णांक, 0600);

/**
 * DOC: vis_vramlimit (पूर्णांक)
 * Restrict the amount of CPU visible VRAM in MiB क्रम testing.  The शेष is 0 (Use full CPU visible VRAM).
 */
MODULE_PARM_DESC(vis_vramlimit, "Restrict visible VRAM for testing, in megabytes");
module_param_named(vis_vramlimit, amdgpu_vis_vram_limit, पूर्णांक, 0444);

/**
 * DOC: gartsize (uपूर्णांक)
 * Restrict the size of GART in Mib (32, 64, etc.) क्रम testing. The शेष is -1 (The size depends on asic).
 */
MODULE_PARM_DESC(gartsize, "Size of GART to setup in megabytes (32, 64, etc., -1=auto)");
module_param_named(gartsize, amdgpu_gart_size, uपूर्णांक, 0600);

/**
 * DOC: gttsize (पूर्णांक)
 * Restrict the size of GTT करोमुख्य in MiB क्रम testing. The शेष is -1 (It's VRAM size अगर 3GB < VRAM < 3/4 RAM,
 * otherwise 3/4 RAM size).
 */
MODULE_PARM_DESC(gttsize, "Size of the GTT domain in megabytes (-1 = auto)");
module_param_named(gttsize, amdgpu_gtt_size, पूर्णांक, 0600);

/**
 * DOC: moverate (पूर्णांक)
 * Set maximum buffer migration rate in MB/s. The शेष is -1 (8 MB/s).
 */
MODULE_PARM_DESC(moverate, "Maximum buffer migration rate in MB/s. (32, 64, etc., -1=auto, 0=1=disabled)");
module_param_named(moverate, amdgpu_moverate, पूर्णांक, 0600);

/**
 * DOC: benchmark (पूर्णांक)
 * Run benchmarks. The शेष is 0 (Skip benchmarks).
 */
MODULE_PARM_DESC(benchmark, "Run benchmark");
module_param_named(benchmark, amdgpu_benchmarking, पूर्णांक, 0444);

/**
 * DOC: test (पूर्णांक)
 * Test BO GTT->VRAM and VRAM->GTT GPU copies. The शेष is 0 (Skip test, only set 1 to run test).
 */
MODULE_PARM_DESC(test, "Run tests");
module_param_named(test, amdgpu_testing, पूर्णांक, 0444);

/**
 * DOC: audio (पूर्णांक)
 * Set HDMI/DPAudio. Only affects non-DC display handling. The शेष is -1 (Enabled), set 0 to disabled it.
 */
MODULE_PARM_DESC(audio, "Audio enable (-1 = auto, 0 = disable, 1 = enable)");
module_param_named(audio, amdgpu_audio, पूर्णांक, 0444);

/**
 * DOC: disp_priority (पूर्णांक)
 * Set display Priority (1 = normal, 2 = high). Only affects non-DC display handling. The शेष is 0 (स्वतः).
 */
MODULE_PARM_DESC(disp_priority, "Display Priority (0 = auto, 1 = normal, 2 = high)");
module_param_named(disp_priority, amdgpu_disp_priority, पूर्णांक, 0444);

/**
 * DOC: hw_i2c (पूर्णांक)
 * To enable hw i2c engine. Only affects non-DC display handling. The शेष is 0 (Disabled).
 */
MODULE_PARM_DESC(hw_i2c, "hw i2c engine enable (0 = disable)");
module_param_named(hw_i2c, amdgpu_hw_i2c, पूर्णांक, 0444);

/**
 * DOC: pcie_gen2 (पूर्णांक)
 * To disable PCIE Gen2/3 mode (0 = disable, 1 = enable). The शेष is -1 (स्वतः, enabled).
 */
MODULE_PARM_DESC(pcie_gen2, "PCIE Gen2 mode (-1 = auto, 0 = disable, 1 = enable)");
module_param_named(pcie_gen2, amdgpu_pcie_gen2, पूर्णांक, 0444);

/**
 * DOC: msi (पूर्णांक)
 * To disable Message Signaled Interrupts (MSI) functionality (1 = enable, 0 = disable). The शेष is -1 (स्वतः, enabled).
 */
MODULE_PARM_DESC(msi, "MSI support (1 = enable, 0 = disable, -1 = auto)");
module_param_named(msi, amdgpu_msi, पूर्णांक, 0444);

/**
 * DOC: lockup_समयout (string)
 * Set GPU scheduler समयout value in ms.
 *
 * The क्रमmat can be [Non-Compute] or [GFX,Compute,SDMA,Video]. That is there can be one or
 * multiple values specअगरied. 0 and negative values are invalidated. They will be adjusted
 * to the शेष समयout.
 *
 * - With one value specअगरied, the setting will apply to all non-compute jobs.
 * - With multiple values specअगरied, the first one will be क्रम GFX.
 *   The second one is क्रम Compute. The third and fourth ones are
 *   क्रम SDMA and Video.
 *
 * By शेष(with no lockup_समयout settings), the समयout क्रम all non-compute(GFX, SDMA and Video)
 * jobs is 10000. And there is no समयout enक्रमced on compute jobs.
 */
MODULE_PARM_DESC(lockup_समयout, "GPU lockup timeout in ms (default: for bare metal 10000 for non-compute jobs and infinity timeout for compute jobs; "
		"for passthrough or sriov, 10000 for all jobs."
		" 0: keep default value. negative: infinity timeout), "
		"format: for bare metal [Non-Compute] or [GFX,Compute,SDMA,Video]; "
		"for passthrough or sriov [all jobs] or [GFX,Compute,SDMA,Video].");
module_param_string(lockup_समयout, amdgpu_lockup_समयout, माप(amdgpu_lockup_समयout), 0444);

/**
 * DOC: dpm (पूर्णांक)
 * Override क्रम dynamic घातer management setting
 * (0 = disable, 1 = enable)
 * The शेष is -1 (स्वतः).
 */
MODULE_PARM_DESC(dpm, "DPM support (1 = enable, 0 = disable, -1 = auto)");
module_param_named(dpm, amdgpu_dpm, पूर्णांक, 0444);

/**
 * DOC: fw_load_type (पूर्णांक)
 * Set dअगरferent firmware loading type क्रम debugging (0 = direct, 1 = SMU, 2 = PSP). The शेष is -1 (स्वतः).
 */
MODULE_PARM_DESC(fw_load_type, "firmware loading type (0 = direct, 1 = SMU, 2 = PSP, -1 = auto)");
module_param_named(fw_load_type, amdgpu_fw_load_type, पूर्णांक, 0444);

/**
 * DOC: aspm (पूर्णांक)
 * To disable ASPM (1 = enable, 0 = disable). The शेष is -1 (स्वतः, enabled).
 */
MODULE_PARM_DESC(aspm, "ASPM support (1 = enable, 0 = disable, -1 = auto)");
module_param_named(aspm, amdgpu_aspm, पूर्णांक, 0444);

/**
 * DOC: runpm (पूर्णांक)
 * Override क्रम runसमय घातer management control क्रम dGPUs in PX/HG laptops. The amdgpu driver can dynamically घातer करोwn
 * the dGPU on PX/HG laptops when it is idle. The शेष is -1 (स्वतः enable). Setting the value to 0 disables this functionality.
 */
MODULE_PARM_DESC(runpm, "PX runtime pm (2 = force enable with BAMACO, 1 = force enable with BACO, 0 = disable, -1 = PX only default)");
module_param_named(runpm, amdgpu_runसमय_pm, पूर्णांक, 0444);

/**
 * DOC: ip_block_mask (uपूर्णांक)
 * Override what IP blocks are enabled on the GPU. Each GPU is a collection of IP blocks (gfx, display, video, etc.).
 * Use this parameter to disable specअगरic blocks. Note that the IP blocks करो not have a fixed index. Some asics may not have
 * some IPs or may include multiple instances of an IP so the ordering various from asic to asic. See the driver output in
 * the kernel log क्रम the list of IPs on the asic. The शेष is 0xffffffff (enable all blocks on a device).
 */
MODULE_PARM_DESC(ip_block_mask, "IP Block Mask (all blocks enabled (default))");
module_param_named(ip_block_mask, amdgpu_ip_block_mask, uपूर्णांक, 0444);

/**
 * DOC: bapm (पूर्णांक)
 * Bidirectional Application Power Management (BAPM) used to dynamically share TDP between CPU and GPU. Set value 0 to disable it.
 * The शेष -1 (स्वतः, enabled)
 */
MODULE_PARM_DESC(bapm, "BAPM support (1 = enable, 0 = disable, -1 = auto)");
module_param_named(bapm, amdgpu_bapm, पूर्णांक, 0444);

/**
 * DOC: deep_color (पूर्णांक)
 * Set 1 to enable Deep Color support. Only affects non-DC display handling. The शेष is 0 (disabled).
 */
MODULE_PARM_DESC(deep_color, "Deep Color support (1 = enable, 0 = disable (default))");
module_param_named(deep_color, amdgpu_deep_color, पूर्णांक, 0444);

/**
 * DOC: vm_size (पूर्णांक)
 * Override the size of the GPU's per client भव address space in GiB.  The शेष is -1 (स्वतःmatic क्रम each asic).
 */
MODULE_PARM_DESC(vm_size, "VM address space size in gigabytes (default 64GB)");
module_param_named(vm_size, amdgpu_vm_size, पूर्णांक, 0444);

/**
 * DOC: vm_fragment_size (पूर्णांक)
 * Override VM fragment size in bits (4, 5, etc. 4 = 64K, 9 = 2M). The शेष is -1 (स्वतःmatic क्रम each asic).
 */
MODULE_PARM_DESC(vm_fragment_size, "VM fragment size in bits (4, 5, etc. 4 = 64K (default), Max 9 = 2M)");
module_param_named(vm_fragment_size, amdgpu_vm_fragment_size, पूर्णांक, 0444);

/**
 * DOC: vm_block_size (पूर्णांक)
 * Override VM page table size in bits (शेष depending on vm_size and hw setup). The शेष is -1 (स्वतःmatic क्रम each asic).
 */
MODULE_PARM_DESC(vm_block_size, "VM page table size in bits (default depending on vm_size)");
module_param_named(vm_block_size, amdgpu_vm_block_size, पूर्णांक, 0444);

/**
 * DOC: vm_fault_stop (पूर्णांक)
 * Stop on VM fault क्रम debugging (0 = never, 1 = prपूर्णांक first, 2 = always). The शेष is 0 (No stop).
 */
MODULE_PARM_DESC(vm_fault_stop, "Stop on VM fault (0 = never (default), 1 = print first, 2 = always)");
module_param_named(vm_fault_stop, amdgpu_vm_fault_stop, पूर्णांक, 0444);

/**
 * DOC: vm_debug (पूर्णांक)
 * Debug VM handling (0 = disabled, 1 = enabled). The शेष is 0 (Disabled).
 */
MODULE_PARM_DESC(vm_debug, "Debug VM handling (0 = disabled (default), 1 = enabled)");
module_param_named(vm_debug, amdgpu_vm_debug, पूर्णांक, 0644);

/**
 * DOC: vm_update_mode (पूर्णांक)
 * Override VM update mode. VM updated by using CPU (0 = never, 1 = Graphics only, 2 = Compute only, 3 = Both). The शेष
 * is -1 (Only in large BAR(LB) प्रणालीs Compute VM tables will be updated by CPU, otherwise 0, never).
 */
MODULE_PARM_DESC(vm_update_mode, "VM update using CPU (0 = never (default except for large BAR(LB)), 1 = Graphics only, 2 = Compute only (default for LB), 3 = Both");
module_param_named(vm_update_mode, amdgpu_vm_update_mode, पूर्णांक, 0444);

/**
 * DOC: exp_hw_support (पूर्णांक)
 * Enable experimental hw support (1 = enable). The शेष is 0 (disabled).
 */
MODULE_PARM_DESC(exp_hw_support, "experimental hw support (1 = enable, 0 = disable (default))");
module_param_named(exp_hw_support, amdgpu_exp_hw_support, पूर्णांक, 0444);

/**
 * DOC: dc (पूर्णांक)
 * Disable/Enable Display Core driver क्रम debugging (1 = enable, 0 = disable). The शेष is -1 (स्वतःmatic क्रम each asic).
 */
MODULE_PARM_DESC(dc, "Display Core driver (1 = enable, 0 = disable, -1 = auto (default))");
module_param_named(dc, amdgpu_dc, पूर्णांक, 0444);

/**
 * DOC: sched_jobs (पूर्णांक)
 * Override the max number of jobs supported in the sw queue. The शेष is 32.
 */
MODULE_PARM_DESC(sched_jobs, "the max number of jobs supported in the sw queue (default 32)");
module_param_named(sched_jobs, amdgpu_sched_jobs, पूर्णांक, 0444);

/**
 * DOC: sched_hw_submission (पूर्णांक)
 * Override the max number of HW submissions. The शेष is 2.
 */
MODULE_PARM_DESC(sched_hw_submission, "the max number of HW submissions (default 2)");
module_param_named(sched_hw_submission, amdgpu_sched_hw_submission, पूर्णांक, 0444);

/**
 * DOC: ppfeaturemask (hexपूर्णांक)
 * Override घातer features enabled. See क्रमागत PP_FEATURE_MASK in drivers/gpu/drm/amd/include/amd_shared.h.
 * The शेष is the current set of stable घातer features.
 */
MODULE_PARM_DESC(ppfeaturemask, "all power features enabled (default))");
module_param_named(ppfeaturemask, amdgpu_pp_feature_mask, hexपूर्णांक, 0444);

/**
 * DOC: क्रमceदीर्घtraining (uपूर्णांक)
 * Force दीर्घ memory training in resume.
 * The शेष is zero, indicates लघु training in resume.
 */
MODULE_PARM_DESC(क्रमceदीर्घtraining, "force memory long training");
module_param_named(क्रमceदीर्घtraining, amdgpu_क्रमce_दीर्घ_training, uपूर्णांक, 0444);

/**
 * DOC: pcie_gen_cap (uपूर्णांक)
 * Override PCIE gen speed capabilities. See the CAIL flags in drivers/gpu/drm/amd/include/amd_pcie.h.
 * The शेष is 0 (स्वतःmatic क्रम each asic).
 */
MODULE_PARM_DESC(pcie_gen_cap, "PCIE Gen Caps (0: autodetect (default))");
module_param_named(pcie_gen_cap, amdgpu_pcie_gen_cap, uपूर्णांक, 0444);

/**
 * DOC: pcie_lane_cap (uपूर्णांक)
 * Override PCIE lanes capabilities. See the CAIL flags in drivers/gpu/drm/amd/include/amd_pcie.h.
 * The शेष is 0 (स्वतःmatic क्रम each asic).
 */
MODULE_PARM_DESC(pcie_lane_cap, "PCIE Lane Caps (0: autodetect (default))");
module_param_named(pcie_lane_cap, amdgpu_pcie_lane_cap, uपूर्णांक, 0444);

/**
 * DOC: cg_mask (uपूर्णांक)
 * Override Clockgating features enabled on GPU (0 = disable घड़ी gating). See the AMD_CG_SUPPORT flags in
 * drivers/gpu/drm/amd/include/amd_shared.h. The शेष is 0xffffffff (all enabled).
 */
MODULE_PARM_DESC(cg_mask, "Clockgating flags mask (0 = disable clock gating)");
module_param_named(cg_mask, amdgpu_cg_mask, uपूर्णांक, 0444);

/**
 * DOC: pg_mask (uपूर्णांक)
 * Override Powergating features enabled on GPU (0 = disable घातer gating). See the AMD_PG_SUPPORT flags in
 * drivers/gpu/drm/amd/include/amd_shared.h. The शेष is 0xffffffff (all enabled).
 */
MODULE_PARM_DESC(pg_mask, "Powergating flags mask (0 = disable power gating)");
module_param_named(pg_mask, amdgpu_pg_mask, uपूर्णांक, 0444);

/**
 * DOC: sdma_phase_quantum (uपूर्णांक)
 * Override SDMA context चयन phase quantum (x 1K GPU घड़ी cycles, 0 = no change). The शेष is 32.
 */
MODULE_PARM_DESC(sdma_phase_quantum, "SDMA context switch phase quantum (x 1K GPU clock cycles, 0 = no change (default 32))");
module_param_named(sdma_phase_quantum, amdgpu_sdma_phase_quantum, uपूर्णांक, 0444);

/**
 * DOC: disable_cu (अक्षरp)
 * Set to disable CUs (It's set like se.sh.cu,...). The शेष is शून्य.
 */
MODULE_PARM_DESC(disable_cu, "Disable CUs (se.sh.cu,...)");
module_param_named(disable_cu, amdgpu_disable_cu, अक्षरp, 0444);

/**
 * DOC: भव_display (अक्षरp)
 * Set to enable भव display feature. This feature provides a भव display hardware on headless boards
 * or in भवized environments. It will be set like xxxx:xx:xx.x,x;xxxx:xx:xx.x,x. It's the pci address of
 * the device, plus the number of crtcs to expose. E.g., 0000:26:00.0,4 would enable 4 भव crtcs on the pci
 * device at 26:00.0. The शेष is शून्य.
 */
MODULE_PARM_DESC(भव_display,
		 "Enable virtual display feature (the virtual_display will be set like xxxx:xx:xx.x,x;xxxx:xx:xx.x,x)");
module_param_named(भव_display, amdgpu_भव_display, अक्षरp, 0444);

/**
 * DOC: job_hang_limit (पूर्णांक)
 * Set how much समय allow a job hang and not drop it. The शेष is 0.
 */
MODULE_PARM_DESC(job_hang_limit, "how much time allow a job hang and not drop it (default 0)");
module_param_named(job_hang_limit, amdgpu_job_hang_limit, पूर्णांक ,0444);

/**
 * DOC: lbpw (पूर्णांक)
 * Override Load Balancing Per Watt (LBPW) support (1 = enable, 0 = disable). The शेष is -1 (स्वतः, enabled).
 */
MODULE_PARM_DESC(lbpw, "Load Balancing Per Watt (LBPW) support (1 = enable, 0 = disable, -1 = auto)");
module_param_named(lbpw, amdgpu_lbpw, पूर्णांक, 0444);

MODULE_PARM_DESC(compute_multipipe, "Force compute queues to be spread across pipes (1 = enable, 0 = disable, -1 = auto)");
module_param_named(compute_multipipe, amdgpu_compute_multipipe, पूर्णांक, 0444);

/**
 * DOC: gpu_recovery (पूर्णांक)
 * Set to enable GPU recovery mechanism (1 = enable, 0 = disable). The शेष is -1 (स्वतः, disabled except SRIOV).
 */
MODULE_PARM_DESC(gpu_recovery, "Enable GPU recovery mechanism, (2 = advanced tdr mode, 1 = enable, 0 = disable, -1 = auto)");
module_param_named(gpu_recovery, amdgpu_gpu_recovery, पूर्णांक, 0444);

/**
 * DOC: emu_mode (पूर्णांक)
 * Set value 1 to enable emulation mode. This is only needed when running on an emulator. The शेष is 0 (disabled).
 */
MODULE_PARM_DESC(emu_mode, "Emulation mode, (1 = enable, 0 = disable)");
module_param_named(emu_mode, amdgpu_emu_mode, पूर्णांक, 0444);

/**
 * DOC: ras_enable (पूर्णांक)
 * Enable RAS features on the GPU (0 = disable, 1 = enable, -1 = स्वतः (शेष))
 */
MODULE_PARM_DESC(ras_enable, "Enable RAS features on the GPU (0 = disable, 1 = enable, -1 = auto (default))");
module_param_named(ras_enable, amdgpu_ras_enable, पूर्णांक, 0444);

/**
 * DOC: ras_mask (uपूर्णांक)
 * Mask of RAS features to enable (शेष 0xffffffff), only valid when ras_enable == 1
 * See the flags in drivers/gpu/drm/amd/amdgpu/amdgpu_ras.h
 */
MODULE_PARM_DESC(ras_mask, "Mask of RAS features to enable (default 0xffffffff), only valid when ras_enable == 1");
module_param_named(ras_mask, amdgpu_ras_mask, uपूर्णांक, 0444);

/**
 * DOC: समयout_fatal_disable (bool)
 * Disable Watchकरोg समयout fatal error event
 */
MODULE_PARM_DESC(समयout_fatal_disable, "disable watchdog timeout fatal error (false = default)");
module_param_named(समयout_fatal_disable, amdgpu_watchकरोg_समयr.समयout_fatal_disable, bool, 0644);

/**
 * DOC: समयout_period (uपूर्णांक)
 * Modअगरy the watchकरोg समयout max_cycles as (1 << period)
 */
MODULE_PARM_DESC(समयout_period, "watchdog timeout period (0 = timeout disabled, 1 ~ 0x23 = timeout maxcycles = (1 << period)");
module_param_named(समयout_period, amdgpu_watchकरोg_समयr.period, uपूर्णांक, 0644);

/**
 * DOC: si_support (पूर्णांक)
 * Set SI support driver. This parameter works after set config CONFIG_DRM_AMDGPU_SI. For SI asic, when radeon driver is enabled,
 * set value 0 to use radeon driver, जबतक set value 1 to use amdgpu driver. The शेष is using radeon driver when it available,
 * otherwise using amdgpu driver.
 */
#अगर_घोषित CONFIG_DRM_AMDGPU_SI

#अगर defined(CONFIG_DRM_RADEON) || defined(CONFIG_DRM_RADEON_MODULE)
पूर्णांक amdgpu_si_support = 0;
MODULE_PARM_DESC(si_support, "SI support (1 = enabled, 0 = disabled (default))");
#अन्यथा
पूर्णांक amdgpu_si_support = 1;
MODULE_PARM_DESC(si_support, "SI support (1 = enabled (default), 0 = disabled)");
#पूर्ण_अगर

module_param_named(si_support, amdgpu_si_support, पूर्णांक, 0444);
#पूर्ण_अगर

/**
 * DOC: cik_support (पूर्णांक)
 * Set CIK support driver. This parameter works after set config CONFIG_DRM_AMDGPU_CIK. For CIK asic, when radeon driver is enabled,
 * set value 0 to use radeon driver, जबतक set value 1 to use amdgpu driver. The शेष is using radeon driver when it available,
 * otherwise using amdgpu driver.
 */
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK

#अगर defined(CONFIG_DRM_RADEON) || defined(CONFIG_DRM_RADEON_MODULE)
पूर्णांक amdgpu_cik_support = 0;
MODULE_PARM_DESC(cik_support, "CIK support (1 = enabled, 0 = disabled (default))");
#अन्यथा
पूर्णांक amdgpu_cik_support = 1;
MODULE_PARM_DESC(cik_support, "CIK support (1 = enabled (default), 0 = disabled)");
#पूर्ण_अगर

module_param_named(cik_support, amdgpu_cik_support, पूर्णांक, 0444);
#पूर्ण_अगर

/**
 * DOC: smu_memory_pool_size (uपूर्णांक)
 * It is used to reserve gtt क्रम smu debug usage, setting value 0 to disable it. The actual size is value * 256MiB.
 * E.g. 0x1 = 256Mbyte, 0x2 = 512Mbyte, 0x4 = 1 Gbyte, 0x8 = 2GByte. The शेष is 0 (disabled).
 */
MODULE_PARM_DESC(smu_memory_pool_size,
	"reserve gtt for smu debug usage, 0 = disable,"
		"0x1 = 256Mbyte, 0x2 = 512Mbyte, 0x4 = 1 Gbyte, 0x8 = 2GByte");
module_param_named(smu_memory_pool_size, amdgpu_smu_memory_pool_size, uपूर्णांक, 0444);

/**
 * DOC: async_gfx_ring (पूर्णांक)
 * It is used to enable gfx rings that could be configured with dअगरferent prioritites or equal priorities
 */
MODULE_PARM_DESC(async_gfx_ring,
	"Asynchronous GFX rings that could be configured with either different priorities (HP3D ring and LP3D ring), or equal priorities (0 = disabled, 1 = enabled (default))");
module_param_named(async_gfx_ring, amdgpu_async_gfx_ring, पूर्णांक, 0444);

/**
 * DOC: mcbp (पूर्णांक)
 * It is used to enable mid command buffer preemption. (0 = disabled (शेष), 1 = enabled)
 */
MODULE_PARM_DESC(mcbp,
	"Enable Mid-command buffer preemption (0 = disabled (default), 1 = enabled)");
module_param_named(mcbp, amdgpu_mcbp, पूर्णांक, 0444);

/**
 * DOC: discovery (पूर्णांक)
 * Allow driver to discover hardware IP inक्रमmation from IP Discovery table at the top of VRAM.
 * (-1 = स्वतः (शेष), 0 = disabled, 1 = enabled)
 */
MODULE_PARM_DESC(discovery,
	"Allow driver to discover hardware IPs from IP Discovery table at the top of VRAM");
module_param_named(discovery, amdgpu_discovery, पूर्णांक, 0444);

/**
 * DOC: mes (पूर्णांक)
 * Enable Micro Engine Scheduler. This is a new hw scheduling engine क्रम gfx, sdma, and compute.
 * (0 = disabled (शेष), 1 = enabled)
 */
MODULE_PARM_DESC(mes,
	"Enable Micro Engine Scheduler (0 = disabled (default), 1 = enabled)");
module_param_named(mes, amdgpu_mes, पूर्णांक, 0444);

/**
 * DOC: noretry (पूर्णांक)
 * Disable retry faults in the GPU memory controller.
 * (0 = retry enabled, 1 = retry disabled, -1 स्वतः (शेष))
 */
MODULE_PARM_DESC(noretry,
	"Disable retry faults (0 = retry enabled, 1 = retry disabled, -1 auto (default))");
module_param_named(noretry, amdgpu_noretry, पूर्णांक, 0644);

/**
 * DOC: क्रमce_asic_type (पूर्णांक)
 * A non negative value used to specअगरy the asic type क्रम all supported GPUs.
 */
MODULE_PARM_DESC(क्रमce_asic_type,
	"A non negative value used to specify the asic type for all supported GPUs");
module_param_named(क्रमce_asic_type, amdgpu_क्रमce_asic_type, पूर्णांक, 0444);



#अगर_घोषित CONFIG_HSA_AMD
/**
 * DOC: sched_policy (पूर्णांक)
 * Set scheduling policy. Default is HWS(hardware scheduling) with over-subscription.
 * Setting 1 disables over-subscription. Setting 2 disables HWS and अटलally
 * assigns queues to HQDs.
 */
पूर्णांक sched_policy = KFD_SCHED_POLICY_HWS;
module_param(sched_policy, पूर्णांक, 0444);
MODULE_PARM_DESC(sched_policy,
	"Scheduling policy (0 = HWS (Default), 1 = HWS without over-subscription, 2 = Non-HWS (Used for debugging only)");

/**
 * DOC: hws_max_conc_proc (पूर्णांक)
 * Maximum number of processes that HWS can schedule concurrently. The maximum is the
 * number of VMIDs asचिन्हित to the HWS, which is also the शेष.
 */
पूर्णांक hws_max_conc_proc = 8;
module_param(hws_max_conc_proc, पूर्णांक, 0444);
MODULE_PARM_DESC(hws_max_conc_proc,
	"Max # processes HWS can execute concurrently when sched_policy=0 (0 = no concurrency, #VMIDs for KFD = Maximum(default))");

/**
 * DOC: cwsr_enable (पूर्णांक)
 * CWSR(compute wave store and resume) allows the GPU to preempt shader execution in
 * the middle of a compute wave. Default is 1 to enable this feature. Setting 0
 * disables it.
 */
पूर्णांक cwsr_enable = 1;
module_param(cwsr_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(cwsr_enable, "CWSR enable (0 = Off, 1 = On (Default))");

/**
 * DOC: max_num_of_queues_per_device (पूर्णांक)
 * Maximum number of queues per device. Valid setting is between 1 and 4096. Default
 * is 4096.
 */
पूर्णांक max_num_of_queues_per_device = KFD_MAX_NUM_OF_QUEUES_PER_DEVICE_DEFAULT;
module_param(max_num_of_queues_per_device, पूर्णांक, 0444);
MODULE_PARM_DESC(max_num_of_queues_per_device,
	"Maximum number of supported queues per device (1 = Minimum, 4096 = default)");

/**
 * DOC: send_sigterm (पूर्णांक)
 * Send sigterm to HSA process on unhandled exceptions. Default is not to send sigterm
 * but just prपूर्णांक errors on dmesg. Setting 1 enables sending sigterm.
 */
पूर्णांक send_sigterm;
module_param(send_sigterm, पूर्णांक, 0444);
MODULE_PARM_DESC(send_sigterm,
	"Send sigterm to HSA process on unhandled exception (0 = disable, 1 = enable)");

/**
 * DOC: debug_largebar (पूर्णांक)
 * Set debug_largebar as 1 to enable simulating large-bar capability on non-large bar
 * प्रणाली. This limits the VRAM size reported to ROCm applications to the visible
 * size, usually 256MB.
 * Default value is 0, diabled.
 */
पूर्णांक debug_largebar;
module_param(debug_largebar, पूर्णांक, 0444);
MODULE_PARM_DESC(debug_largebar,
	"Debug large-bar flag used to simulate large-bar capability on non-large bar machine (0 = disable, 1 = enable)");

/**
 * DOC: ignore_crat (पूर्णांक)
 * Ignore CRAT table during KFD initialization. By शेष, KFD uses the ACPI CRAT
 * table to get inक्रमmation about AMD APUs. This option can serve as a workaround on
 * प्रणालीs with a broken CRAT table.
 *
 * Default is स्वतः (according to asic type, iommu_v2, and crat table, to decide
 * whehter use CRAT)
 */
पूर्णांक ignore_crat;
module_param(ignore_crat, पूर्णांक, 0444);
MODULE_PARM_DESC(ignore_crat,
	"Ignore CRAT table during KFD initialization (0 = auto (default), 1 = ignore CRAT)");

/**
 * DOC: halt_अगर_hws_hang (पूर्णांक)
 * Halt अगर HWS hang is detected. Default value, 0, disables the halt on hang.
 * Setting 1 enables halt on hang.
 */
पूर्णांक halt_अगर_hws_hang;
module_param(halt_अगर_hws_hang, पूर्णांक, 0644);
MODULE_PARM_DESC(halt_अगर_hws_hang, "Halt if HWS hang is detected (0 = off (default), 1 = on)");

/**
 * DOC: hws_gws_support(bool)
 * Assume that HWS supports GWS barriers regardless of what firmware version
 * check says. Default value: false (rely on MEC2 firmware version check).
 */
bool hws_gws_support;
module_param(hws_gws_support, bool, 0444);
MODULE_PARM_DESC(hws_gws_support, "Assume MEC2 FW supports GWS barriers (false = rely on FW version check (Default), true = force supported)");

/**
  * DOC: queue_preemption_समयout_ms (पूर्णांक)
  * queue preemption समयout in ms (1 = Minimum, 9000 = शेष)
  */
पूर्णांक queue_preemption_समयout_ms = 9000;
module_param(queue_preemption_समयout_ms, पूर्णांक, 0644);
MODULE_PARM_DESC(queue_preemption_समयout_ms, "queue preemption timeout in ms (1 = Minimum, 9000 = default)");

/**
 * DOC: debug_evictions(bool)
 * Enable extra debug messages to help determine the cause of evictions
 */
bool debug_evictions;
module_param(debug_evictions, bool, 0644);
MODULE_PARM_DESC(debug_evictions, "enable eviction debug messages (false = default)");

/**
 * DOC: no_प्रणाली_mem_limit(bool)
 * Disable प्रणाली memory limit, to support multiple process shared memory
 */
bool no_प्रणाली_mem_limit;
module_param(no_प्रणाली_mem_limit, bool, 0644);
MODULE_PARM_DESC(no_प्रणाली_mem_limit, "disable system memory limit (false = default)");

/**
 * DOC: no_queue_eviction_on_vm_fault (पूर्णांक)
 * If set, process queues will not be evicted on gpuvm fault. This is to keep the wavefront context क्रम debugging (0 = queue eviction, 1 = no queue eviction). The शेष is 0 (queue eviction).
 */
पूर्णांक amdgpu_no_queue_eviction_on_vm_fault = 0;
MODULE_PARM_DESC(no_queue_eviction_on_vm_fault, "No queue eviction on VM fault (0 = queue eviction, 1 = no queue eviction)");
module_param_named(no_queue_eviction_on_vm_fault, amdgpu_no_queue_eviction_on_vm_fault, पूर्णांक, 0444);
#पूर्ण_अगर

/**
 * DOC: dcfeaturemask (uपूर्णांक)
 * Override display features enabled. See क्रमागत DC_FEATURE_MASK in drivers/gpu/drm/amd/include/amd_shared.h.
 * The शेष is the current set of stable display features.
 */
MODULE_PARM_DESC(dcfeaturemask, "all stable DC features enabled (default))");
module_param_named(dcfeaturemask, amdgpu_dc_feature_mask, uपूर्णांक, 0444);

/**
 * DOC: dcdebugmask (uपूर्णांक)
 * Override display features enabled. See क्रमागत DC_DEBUG_MASK in drivers/gpu/drm/amd/include/amd_shared.h.
 */
MODULE_PARM_DESC(dcdebugmask, "all debug options disabled (default))");
module_param_named(dcdebugmask, amdgpu_dc_debug_mask, uपूर्णांक, 0444);

/**
 * DOC: abmlevel (uपूर्णांक)
 * Override the शेष ABM (Adaptive Backlight Management) level used क्रम DC
 * enabled hardware. Requires DMCU to be supported and loaded.
 * Valid levels are 0-4. A value of 0 indicates that ABM should be disabled by
 * शेष. Values 1-4 control the maximum allowable brightness reduction via
 * the ABM algorithm, with 1 being the least reduction and 4 being the most
 * reduction.
 *
 * Defaults to 0, or disabled. Userspace can still override this level later
 * after boot.
 */
uपूर्णांक amdgpu_dm_abm_level;
MODULE_PARM_DESC(abmlevel, "ABM level (0 = off (default), 1-4 = backlight reduction level) ");
module_param_named(abmlevel, amdgpu_dm_abm_level, uपूर्णांक, 0444);

पूर्णांक amdgpu_backlight = -1;
MODULE_PARM_DESC(backlight, "Backlight control (0 = pwm, 1 = aux, -1 auto (default))");
module_param_named(backlight, amdgpu_backlight, bपूर्णांक, 0444);

/**
 * DOC: पंचांगz (पूर्णांक)
 * Trusted Memory Zone (TMZ) is a method to protect data being written
 * to or पढ़ो from memory.
 *
 * The शेष value: 0 (off).  TODO: change to स्वतः till it is completed.
 */
MODULE_PARM_DESC(पंचांगz, "Enable TMZ feature (-1 = auto (default), 0 = off, 1 = on)");
module_param_named(पंचांगz, amdgpu_पंचांगz, पूर्णांक, 0444);

/**
 * DOC: मुक्तsync_video (uपूर्णांक)
 * Enabled the optimization to adjust front porch timing to achieve seamless mode change experience
 * when setting a मुक्तsync supported mode क्रम which full modeset is not needed.
 * The शेष value: 0 (off).
 */
MODULE_PARM_DESC(
	मुक्तsync_video,
	"Enable freesync modesetting optimization feature (0 = off (default), 1 = on)");
module_param_named(मुक्तsync_video, amdgpu_मुक्तsync_vid_mode, uपूर्णांक, 0444);

/**
 * DOC: reset_method (पूर्णांक)
 * GPU reset method (-1 = स्वतः (शेष), 0 = legacy, 1 = mode0, 2 = mode1, 3 = mode2, 4 = baco, 5 = pci)
 */
MODULE_PARM_DESC(reset_method, "GPU reset method (-1 = auto (default), 0 = legacy, 1 = mode0, 2 = mode1, 3 = mode2, 4 = baco/bamaco, 5 = pci)");
module_param_named(reset_method, amdgpu_reset_method, पूर्णांक, 0444);

/**
 * DOC: bad_page_threshold (पूर्णांक)
 * Bad page threshold is to specअगरy the threshold value of faulty pages
 * detected by RAS ECC, that may result in GPU entering bad status अगर total
 * faulty pages by ECC exceed threshold value and leave it क्रम user's further
 * check.
 */
MODULE_PARM_DESC(bad_page_threshold, "Bad page threshold(-1 = auto(default value), 0 = disable bad page retirement)");
module_param_named(bad_page_threshold, amdgpu_bad_page_threshold, पूर्णांक, 0444);

MODULE_PARM_DESC(num_kcq, "number of kernel compute queue user want to setup (8 if set to greater than 8 or less than 0, only affect gfx 8+)");
module_param_named(num_kcq, amdgpu_num_kcq, पूर्णांक, 0444);

/**
 * DOC: smu_pptable_id (पूर्णांक)
 * Used to override pptable id. id = 0 use VBIOS pptable.
 * id > 0 use the soft pptable with specicfied id.
 */
MODULE_PARM_DESC(smu_pptable_id,
	"specify pptable id to be used (-1 = auto(default) value, 0 = use pptable from vbios, > 0 = soft pptable id)");
module_param_named(smu_pptable_id, amdgpu_smu_pptable_id, पूर्णांक, 0444);

अटल स्थिर काष्ठा pci_device_id pciidlist[] = अणु
#अगर_घोषित  CONFIG_DRM_AMDGPU_SI
	अणु0x1002, 0x6780, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITIपूर्ण,
	अणु0x1002, 0x6784, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITIपूर्ण,
	अणु0x1002, 0x6788, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITIपूर्ण,
	अणु0x1002, 0x678A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITIपूर्ण,
	अणु0x1002, 0x6790, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITIपूर्ण,
	अणु0x1002, 0x6791, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITIपूर्ण,
	अणु0x1002, 0x6792, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITIपूर्ण,
	अणु0x1002, 0x6798, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITIपूर्ण,
	अणु0x1002, 0x6799, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITIपूर्ण,
	अणु0x1002, 0x679A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITIपूर्ण,
	अणु0x1002, 0x679B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITIपूर्ण,
	अणु0x1002, 0x679E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITIपूर्ण,
	अणु0x1002, 0x679F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TAHITIपूर्ण,
	अणु0x1002, 0x6800, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIRN|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6801, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIRN|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6802, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIRN|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6806, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIRNपूर्ण,
	अणु0x1002, 0x6808, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIRNपूर्ण,
	अणु0x1002, 0x6809, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIRNपूर्ण,
	अणु0x1002, 0x6810, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIRNपूर्ण,
	अणु0x1002, 0x6811, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIRNपूर्ण,
	अणु0x1002, 0x6816, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIRNपूर्ण,
	अणु0x1002, 0x6817, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIRNपूर्ण,
	अणु0x1002, 0x6818, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIRNपूर्ण,
	अणु0x1002, 0x6819, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_PITCAIRNपूर्ण,
	अणु0x1002, 0x6600, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLAND|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6601, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLAND|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6602, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLAND|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6603, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLAND|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6604, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLAND|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6605, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLAND|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6606, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLAND|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6607, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLAND|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6608, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLANDपूर्ण,
	अणु0x1002, 0x6610, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLANDपूर्ण,
	अणु0x1002, 0x6611, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLANDपूर्ण,
	अणु0x1002, 0x6613, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLANDपूर्ण,
	अणु0x1002, 0x6617, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLAND|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6620, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLAND|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6621, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLAND|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6623, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLAND|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6631, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_OLANDपूर्ण,
	अणु0x1002, 0x6820, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6821, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6822, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6823, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6824, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6825, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6826, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6827, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6828, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDEपूर्ण,
	अणु0x1002, 0x6829, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDEपूर्ण,
	अणु0x1002, 0x682A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x682B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x682C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDEपूर्ण,
	अणु0x1002, 0x682D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x682F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6830, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6831, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6835, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDEपूर्ण,
	अणु0x1002, 0x6837, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDEपूर्ण,
	अणु0x1002, 0x6838, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDEपूर्ण,
	अणु0x1002, 0x6839, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDEपूर्ण,
	अणु0x1002, 0x683B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDEपूर्ण,
	अणु0x1002, 0x683D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDEपूर्ण,
	अणु0x1002, 0x683F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VERDEपूर्ण,
	अणु0x1002, 0x6660, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAIन_अंक|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6663, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAIन_अंक|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6664, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAIन_अंक|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6665, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAIन_अंक|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6667, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAIन_अंक|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x666F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAIन_अंक|AMD_IS_MOBILITYपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
	/* Kaveri */
	अणु0x1002, 0x1304, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x1305, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x1306, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x1307, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x1309, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x130A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x130B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x130C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x130D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x130E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x130F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x1310, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x1311, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x1312, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x1313, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x1315, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x1316, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x1317, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x1318, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x131B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x131C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x131D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KAVERI|AMD_IS_APUपूर्ण,
	/* Bonaire */
	अणु0x1002, 0x6640, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIRE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6641, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIRE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6646, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIRE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6647, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIRE|AMD_IS_MOBILITYपूर्ण,
	अणु0x1002, 0x6649, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIREपूर्ण,
	अणु0x1002, 0x6650, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIREपूर्ण,
	अणु0x1002, 0x6651, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIREपूर्ण,
	अणु0x1002, 0x6658, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIREपूर्ण,
	अणु0x1002, 0x665c, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIREपूर्ण,
	अणु0x1002, 0x665d, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIREपूर्ण,
	अणु0x1002, 0x665f, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_BONAIREपूर्ण,
	/* Hawaii */
	अणु0x1002, 0x67A0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAIIपूर्ण,
	अणु0x1002, 0x67A1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAIIपूर्ण,
	अणु0x1002, 0x67A2, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAIIपूर्ण,
	अणु0x1002, 0x67A8, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAIIपूर्ण,
	अणु0x1002, 0x67A9, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAIIपूर्ण,
	अणु0x1002, 0x67AA, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAIIपूर्ण,
	अणु0x1002, 0x67B0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAIIपूर्ण,
	अणु0x1002, 0x67B1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAIIपूर्ण,
	अणु0x1002, 0x67B8, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAIIपूर्ण,
	अणु0x1002, 0x67B9, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAIIपूर्ण,
	अणु0x1002, 0x67BA, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAIIपूर्ण,
	अणु0x1002, 0x67BE, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_HAWAIIपूर्ण,
	/* Kabini */
	अणु0x1002, 0x9830, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9831, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9832, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9833, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9834, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9835, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9836, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9837, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9838, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9839, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x983a, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x983b, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x983c, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x983d, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x983e, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x983f, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_KABINI|AMD_IS_APUपूर्ण,
	/* mullins */
	अणु0x1002, 0x9850, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9851, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9852, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9853, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9854, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9855, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9856, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9857, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9858, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9859, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x985A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x985B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x985C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x985D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x985E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x985F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_MULLINS|AMD_IS_MOBILITY|AMD_IS_APUपूर्ण,
#पूर्ण_अगर
	/* topaz */
	अणु0x1002, 0x6900, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TOPAZपूर्ण,
	अणु0x1002, 0x6901, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TOPAZपूर्ण,
	अणु0x1002, 0x6902, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TOPAZपूर्ण,
	अणु0x1002, 0x6903, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TOPAZपूर्ण,
	अणु0x1002, 0x6907, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TOPAZपूर्ण,
	/* tonga */
	अणु0x1002, 0x6920, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGAपूर्ण,
	अणु0x1002, 0x6921, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGAपूर्ण,
	अणु0x1002, 0x6928, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGAपूर्ण,
	अणु0x1002, 0x6929, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGAपूर्ण,
	अणु0x1002, 0x692B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGAपूर्ण,
	अणु0x1002, 0x692F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGAपूर्ण,
	अणु0x1002, 0x6930, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGAपूर्ण,
	अणु0x1002, 0x6938, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGAपूर्ण,
	अणु0x1002, 0x6939, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_TONGAपूर्ण,
	/* fiji */
	अणु0x1002, 0x7300, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_FIJIपूर्ण,
	अणु0x1002, 0x730F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_FIJIपूर्ण,
	/* carrizo */
	अणु0x1002, 0x9870, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_CARRIZO|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9874, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_CARRIZO|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9875, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_CARRIZO|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9876, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_CARRIZO|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x9877, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_CARRIZO|AMD_IS_APUपूर्ण,
	/* stoney */
	अणु0x1002, 0x98E4, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_STONEY|AMD_IS_APUपूर्ण,
	/* Polaris11 */
	अणु0x1002, 0x67E0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS11पूर्ण,
	अणु0x1002, 0x67E3, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS11पूर्ण,
	अणु0x1002, 0x67E8, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS11पूर्ण,
	अणु0x1002, 0x67EB, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS11पूर्ण,
	अणु0x1002, 0x67EF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS11पूर्ण,
	अणु0x1002, 0x67FF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS11पूर्ण,
	अणु0x1002, 0x67E1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS11पूर्ण,
	अणु0x1002, 0x67E7, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS11पूर्ण,
	अणु0x1002, 0x67E9, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS11पूर्ण,
	/* Polaris10 */
	अणु0x1002, 0x67C0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS10पूर्ण,
	अणु0x1002, 0x67C1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS10पूर्ण,
	अणु0x1002, 0x67C2, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS10पूर्ण,
	अणु0x1002, 0x67C4, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS10पूर्ण,
	अणु0x1002, 0x67C7, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS10पूर्ण,
	अणु0x1002, 0x67D0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS10पूर्ण,
	अणु0x1002, 0x67DF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS10पूर्ण,
	अणु0x1002, 0x67C8, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS10पूर्ण,
	अणु0x1002, 0x67C9, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS10पूर्ण,
	अणु0x1002, 0x67CA, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS10पूर्ण,
	अणु0x1002, 0x67CC, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS10पूर्ण,
	अणु0x1002, 0x67CF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS10पूर्ण,
	अणु0x1002, 0x6FDF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS10पूर्ण,
	/* Polaris12 */
	अणु0x1002, 0x6980, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS12पूर्ण,
	अणु0x1002, 0x6981, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS12पूर्ण,
	अणु0x1002, 0x6985, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS12पूर्ण,
	अणु0x1002, 0x6986, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS12पूर्ण,
	अणु0x1002, 0x6987, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS12पूर्ण,
	अणु0x1002, 0x6995, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS12पूर्ण,
	अणु0x1002, 0x6997, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS12पूर्ण,
	अणु0x1002, 0x699F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_POLARIS12पूर्ण,
	/* VEGAM */
	अणु0x1002, 0x694C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGAMपूर्ण,
	अणु0x1002, 0x694E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGAMपूर्ण,
	अणु0x1002, 0x694F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGAMपूर्ण,
	/* Vega 10 */
	अणु0x1002, 0x6860, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10पूर्ण,
	अणु0x1002, 0x6861, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10पूर्ण,
	अणु0x1002, 0x6862, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10पूर्ण,
	अणु0x1002, 0x6863, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10पूर्ण,
	अणु0x1002, 0x6864, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10पूर्ण,
	अणु0x1002, 0x6867, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10पूर्ण,
	अणु0x1002, 0x6868, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10पूर्ण,
	अणु0x1002, 0x6869, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10पूर्ण,
	अणु0x1002, 0x686a, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10पूर्ण,
	अणु0x1002, 0x686b, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10पूर्ण,
	अणु0x1002, 0x686c, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10पूर्ण,
	अणु0x1002, 0x686d, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10पूर्ण,
	अणु0x1002, 0x686e, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10पूर्ण,
	अणु0x1002, 0x686f, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10पूर्ण,
	अणु0x1002, 0x687f, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA10पूर्ण,
	/* Vega 12 */
	अणु0x1002, 0x69A0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA12पूर्ण,
	अणु0x1002, 0x69A1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA12पूर्ण,
	अणु0x1002, 0x69A2, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA12पूर्ण,
	अणु0x1002, 0x69A3, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA12पूर्ण,
	अणु0x1002, 0x69AF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA12पूर्ण,
	/* Vega 20 */
	अणु0x1002, 0x66A0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA20पूर्ण,
	अणु0x1002, 0x66A1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA20पूर्ण,
	अणु0x1002, 0x66A2, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA20पूर्ण,
	अणु0x1002, 0x66A3, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA20पूर्ण,
	अणु0x1002, 0x66A4, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA20पूर्ण,
	अणु0x1002, 0x66A7, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA20पूर्ण,
	अणु0x1002, 0x66AF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VEGA20पूर्ण,
	/* Raven */
	अणु0x1002, 0x15dd, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_RAVEN|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x15d8, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_RAVEN|AMD_IS_APUपूर्ण,
	/* Arcturus */
	अणु0x1002, 0x738C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_ARCTURUSपूर्ण,
	अणु0x1002, 0x7388, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_ARCTURUSपूर्ण,
	अणु0x1002, 0x738E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_ARCTURUSपूर्ण,
	अणु0x1002, 0x7390, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_ARCTURUSपूर्ण,
	/* Navi10 */
	अणु0x1002, 0x7310, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10पूर्ण,
	अणु0x1002, 0x7312, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10पूर्ण,
	अणु0x1002, 0x7318, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10पूर्ण,
	अणु0x1002, 0x7319, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10पूर्ण,
	अणु0x1002, 0x731A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10पूर्ण,
	अणु0x1002, 0x731B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10पूर्ण,
	अणु0x1002, 0x731E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10पूर्ण,
	अणु0x1002, 0x731F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI10पूर्ण,
	/* Navi14 */
	अणु0x1002, 0x7340, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI14पूर्ण,
	अणु0x1002, 0x7341, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI14पूर्ण,
	अणु0x1002, 0x7347, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI14पूर्ण,
	अणु0x1002, 0x734F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI14पूर्ण,

	/* Renoir */
	अणु0x1002, 0x1636, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_RENOIR|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x1638, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_RENOIR|AMD_IS_APUपूर्ण,
	अणु0x1002, 0x164C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_RENOIR|AMD_IS_APUपूर्ण,

	/* Navi12 */
	अणु0x1002, 0x7360, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI12पूर्ण,
	अणु0x1002, 0x7362, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVI12पूर्ण,

	/* Sienna_Cichlid */
	अणु0x1002, 0x73A0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHLIDपूर्ण,
	अणु0x1002, 0x73A1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHLIDपूर्ण,
	अणु0x1002, 0x73A2, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHLIDपूर्ण,
	अणु0x1002, 0x73A3, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHLIDपूर्ण,
	अणु0x1002, 0x73AB, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHLIDपूर्ण,
	अणु0x1002, 0x73AE, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHLIDपूर्ण,
	अणु0x1002, 0x73AF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHLIDपूर्ण,
	अणु0x1002, 0x73BF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_SIENNA_CICHLIDपूर्ण,

	/* Van Gogh */
	अणु0x1002, 0x163F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_VANGOGH|AMD_IS_APUपूर्ण,

	/* Navy_Flounder */
	अणु0x1002, 0x73C0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVY_FLOUNDERपूर्ण,
	अणु0x1002, 0x73C1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVY_FLOUNDERपूर्ण,
	अणु0x1002, 0x73C3, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVY_FLOUNDERपूर्ण,
	अणु0x1002, 0x73DF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_NAVY_FLOUNDERपूर्ण,

	/* DIMGREY_CAVEFISH */
	अणु0x1002, 0x73E0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGREY_CAVEFISHपूर्ण,
	अणु0x1002, 0x73E1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGREY_CAVEFISHपूर्ण,
	अणु0x1002, 0x73E2, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGREY_CAVEFISHपूर्ण,
	अणु0x1002, 0x73FF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_DIMGREY_CAVEFISHपूर्ण,

	/* Aldebaran */
	अणु0x1002, 0x7408, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_ALDEBARAN|AMD_EXP_HW_SUPPORTपूर्ण,
	अणु0x1002, 0x740C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_ALDEBARAN|AMD_EXP_HW_SUPPORTपूर्ण,
	अणु0x1002, 0x740F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CHIP_ALDEBARAN|AMD_EXP_HW_SUPPORTपूर्ण,

	अणु0, 0, 0पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pciidlist);

अटल स्थिर काष्ठा drm_driver amdgpu_kms_driver;

अटल पूर्णांक amdgpu_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा drm_device *ddev;
	काष्ठा amdgpu_device *adev;
	अचिन्हित दीर्घ flags = ent->driver_data;
	पूर्णांक ret, retry = 0;
	bool supports_atomic = false;

	अगर (!amdgpu_भव_display &&
	    amdgpu_device_asic_has_dc_support(flags & AMD_ASIC_MASK))
		supports_atomic = true;

	अगर ((flags & AMD_EXP_HW_SUPPORT) && !amdgpu_exp_hw_support) अणु
		DRM_INFO("This hardware requires experimental hardware support.\n"
			 "See modparam exp_hw_support\n");
		वापस -ENODEV;
	पूर्ण

	/* Due to hardware bugs, S/G Display on raven requires a 1:1 IOMMU mapping,
	 * however, SME requires an indirect IOMMU mapping because the encryption
	 * bit is beyond the DMA mask of the chip.
	 */
	अगर (mem_encrypt_active() && ((flags & AMD_ASIC_MASK) == CHIP_RAVEN)) अणु
		dev_info(&pdev->dev,
			 "SME is not compatible with RAVEN\n");
		वापस -ENOTSUPP;
	पूर्ण

#अगर_घोषित CONFIG_DRM_AMDGPU_SI
	अगर (!amdgpu_si_support) अणु
		चयन (flags & AMD_ASIC_MASK) अणु
		हाल CHIP_TAHITI:
		हाल CHIP_PITCAIRN:
		हाल CHIP_VERDE:
		हाल CHIP_OLAND:
		हाल CHIP_HAIन_अंक:
			dev_info(&pdev->dev,
				 "SI support provided by radeon.\n");
			dev_info(&pdev->dev,
				 "Use radeon.si_support=0 amdgpu.si_support=1 to override.\n"
				);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
	अगर (!amdgpu_cik_support) अणु
		चयन (flags & AMD_ASIC_MASK) अणु
		हाल CHIP_KAVERI:
		हाल CHIP_BONAIRE:
		हाल CHIP_HAWAII:
		हाल CHIP_KABINI:
		हाल CHIP_MULLINS:
			dev_info(&pdev->dev,
				 "CIK support provided by radeon.\n");
			dev_info(&pdev->dev,
				 "Use radeon.cik_support=0 amdgpu.cik_support=1 to override.\n"
				);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Get rid of things like offb */
	ret = drm_fb_helper_हटाओ_conflicting_pci_framebuffers(pdev, "amdgpudrmfb");
	अगर (ret)
		वापस ret;

	adev = devm_drm_dev_alloc(&pdev->dev, &amdgpu_kms_driver, typeof(*adev), ddev);
	अगर (IS_ERR(adev))
		वापस PTR_ERR(adev);

	adev->dev  = &pdev->dev;
	adev->pdev = pdev;
	ddev = adev_to_drm(adev);

	अगर (!supports_atomic)
		ddev->driver_features &= ~DRIVER_ATOMIC;

	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;

	pci_set_drvdata(pdev, ddev);

	ret = amdgpu_driver_load_kms(adev, ent->driver_data);
	अगर (ret)
		जाओ err_pci;

retry_init:
	ret = drm_dev_रेजिस्टर(ddev, ent->driver_data);
	अगर (ret == -EAGAIN && ++retry <= 3) अणु
		DRM_INFO("retry init %d\n", retry);
		/* Don't request EX mode too frequently which is attacking */
		msleep(5000);
		जाओ retry_init;
	पूर्ण अन्यथा अगर (ret) अणु
		जाओ err_pci;
	पूर्ण

	ret = amdgpu_debugfs_init(adev);
	अगर (ret)
		DRM_ERROR("Creating debugfs files failed (%d).\n", ret);

	वापस 0;

err_pci:
	pci_disable_device(pdev);
	वापस ret;
पूर्ण

अटल व्योम
amdgpu_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

#अगर_घोषित MODULE
	अगर (THIS_MODULE->state != MODULE_STATE_GOING)
#पूर्ण_अगर
		DRM_ERROR("Hotplug removal is not supported\n");
	drm_dev_unplug(dev);
	amdgpu_driver_unload_kms(dev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

अटल व्योम
amdgpu_pci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);

	अगर (amdgpu_ras_पूर्णांकr_triggered())
		वापस;

	/* अगर we are running in a VM, make sure the device
	 * torn करोwn properly on reboot/shutकरोwn.
	 * unक्रमtunately we can't detect certain
	 * hypervisors so just करो this all the समय.
	 */
	अगर (!amdgpu_passthrough(adev))
		adev->mp1_state = PP_MP1_STATE_UNLOAD;
	amdgpu_device_ip_suspend(adev);
	adev->mp1_state = PP_MP1_STATE_NONE;
पूर्ण

/**
 * amdgpu_drv_delayed_reset_work_handler - work handler क्रम reset
 *
 * @work: work_काष्ठा.
 */
अटल व्योम amdgpu_drv_delayed_reset_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा list_head device_list;
	काष्ठा amdgpu_device *adev;
	पूर्णांक i, r;
	काष्ठा amdgpu_reset_context reset_context;

	स_रखो(&reset_context, 0, माप(reset_context));

	mutex_lock(&mgpu_info.mutex);
	अगर (mgpu_info.pending_reset == true) अणु
		mutex_unlock(&mgpu_info.mutex);
		वापस;
	पूर्ण
	mgpu_info.pending_reset = true;
	mutex_unlock(&mgpu_info.mutex);

	/* Use a common context, just need to make sure full reset is करोne */
	reset_context.method = AMD_RESET_METHOD_NONE;
	set_bit(AMDGPU_NEED_FULL_RESET, &reset_context.flags);

	क्रम (i = 0; i < mgpu_info.num_dgpu; i++) अणु
		adev = mgpu_info.gpu_ins[i].adev;
		reset_context.reset_req_dev = adev;
		r = amdgpu_device_pre_asic_reset(adev, &reset_context);
		अगर (r) अणु
			dev_err(adev->dev, "GPU pre asic reset failed with err, %d for drm dev, %s ",
				r, adev_to_drm(adev)->unique);
		पूर्ण
		अगर (!queue_work(प्रणाली_unbound_wq, &adev->xgmi_reset_work))
			r = -EALREADY;
	पूर्ण
	क्रम (i = 0; i < mgpu_info.num_dgpu; i++) अणु
		adev = mgpu_info.gpu_ins[i].adev;
		flush_work(&adev->xgmi_reset_work);
		adev->gmc.xgmi.pending_reset = false;
	पूर्ण

	/* reset function will rebuild the xgmi hive info , clear it now */
	क्रम (i = 0; i < mgpu_info.num_dgpu; i++)
		amdgpu_xgmi_हटाओ_device(mgpu_info.gpu_ins[i].adev);

	INIT_LIST_HEAD(&device_list);

	क्रम (i = 0; i < mgpu_info.num_dgpu; i++)
		list_add_tail(&mgpu_info.gpu_ins[i].adev->reset_list, &device_list);

	/* unरेजिस्टर the GPU first, reset function will add them back */
	list_क्रम_each_entry(adev, &device_list, reset_list)
		amdgpu_unरेजिस्टर_gpu_instance(adev);

	/* Use a common context, just need to make sure full reset is करोne */
	set_bit(AMDGPU_SKIP_HW_RESET, &reset_context.flags);
	r = amdgpu_करो_asic_reset(&device_list, &reset_context);

	अगर (r) अणु
		DRM_ERROR("reinit gpus failure");
		वापस;
	पूर्ण
	क्रम (i = 0; i < mgpu_info.num_dgpu; i++) अणु
		adev = mgpu_info.gpu_ins[i].adev;
		अगर (!adev->kfd.init_complete)
			amdgpu_amdkfd_device_init(adev);
		amdgpu_tपंचांग_set_buffer_funcs_status(adev, true);
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक amdgpu_pmops_prepare(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	/* Return a positive number here so
	 * DPM_FLAG_SMART_SUSPEND works properly
	 */
	अगर (amdgpu_device_supports_boco(drm_dev))
		वापस pm_runसमय_suspended(dev) &&
			pm_suspend_via_firmware();

	वापस 0;
पूर्ण

अटल व्योम amdgpu_pmops_complete(काष्ठा device *dev)
अणु
	/* nothing to करो */
पूर्ण

अटल पूर्णांक amdgpu_pmops_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(drm_dev);
	पूर्णांक r;

	अगर (amdgpu_acpi_is_s0ix_supported(adev))
		adev->in_s0ix = true;
	adev->in_s3 = true;
	r = amdgpu_device_suspend(drm_dev, true);
	adev->in_s3 = false;

	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_pmops_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(drm_dev);
	पूर्णांक r;

	r = amdgpu_device_resume(drm_dev, true);
	अगर (amdgpu_acpi_is_s0ix_supported(adev))
		adev->in_s0ix = false;
	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_pmops_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(drm_dev);
	पूर्णांक r;

	adev->in_s4 = true;
	r = amdgpu_device_suspend(drm_dev, true);
	adev->in_s4 = false;
	अगर (r)
		वापस r;
	वापस amdgpu_asic_reset(adev);
पूर्ण

अटल पूर्णांक amdgpu_pmops_thaw(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	वापस amdgpu_device_resume(drm_dev, true);
पूर्ण

अटल पूर्णांक amdgpu_pmops_घातeroff(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	वापस amdgpu_device_suspend(drm_dev, true);
पूर्ण

अटल पूर्णांक amdgpu_pmops_restore(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	वापस amdgpu_device_resume(drm_dev, true);
पूर्ण

अटल पूर्णांक amdgpu_pmops_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *drm_dev = pci_get_drvdata(pdev);
	काष्ठा amdgpu_device *adev = drm_to_adev(drm_dev);
	पूर्णांक ret, i;

	अगर (!adev->runpm) अणु
		pm_runसमय_क्रमbid(dev);
		वापस -EBUSY;
	पूर्ण

	/* रुको क्रम all rings to drain beक्रमe suspending */
	क्रम (i = 0; i < AMDGPU_MAX_RINGS; i++) अणु
		काष्ठा amdgpu_ring *ring = adev->rings[i];
		अगर (ring && ring->sched.पढ़ोy) अणु
			ret = amdgpu_fence_रुको_empty(ring);
			अगर (ret)
				वापस -EBUSY;
		पूर्ण
	पूर्ण

	adev->in_runpm = true;
	अगर (amdgpu_device_supports_px(drm_dev))
		drm_dev->चयन_घातer_state = DRM_SWITCH_POWER_CHANGING;

	ret = amdgpu_device_suspend(drm_dev, false);
	अगर (ret) अणु
		adev->in_runpm = false;
		वापस ret;
	पूर्ण

	अगर (amdgpu_device_supports_px(drm_dev)) अणु
		/* Only need to handle PCI state in the driver क्रम ATPX
		 * PCI core handles it क्रम _PR3.
		 */
		amdgpu_device_cache_pci_state(pdev);
		pci_disable_device(pdev);
		pci_ignore_hotplug(pdev);
		pci_set_घातer_state(pdev, PCI_D3cold);
		drm_dev->चयन_घातer_state = DRM_SWITCH_POWER_DYNAMIC_OFF;
	पूर्ण अन्यथा अगर (amdgpu_device_supports_baco(drm_dev)) अणु
		amdgpu_device_baco_enter(drm_dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_pmops_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा drm_device *drm_dev = pci_get_drvdata(pdev);
	काष्ठा amdgpu_device *adev = drm_to_adev(drm_dev);
	पूर्णांक ret;

	अगर (!adev->runpm)
		वापस -EINVAL;

	अगर (amdgpu_device_supports_px(drm_dev)) अणु
		drm_dev->चयन_घातer_state = DRM_SWITCH_POWER_CHANGING;

		/* Only need to handle PCI state in the driver क्रम ATPX
		 * PCI core handles it क्रम _PR3.
		 */
		pci_set_घातer_state(pdev, PCI_D0);
		amdgpu_device_load_pci_state(pdev);
		ret = pci_enable_device(pdev);
		अगर (ret)
			वापस ret;
		pci_set_master(pdev);
	पूर्ण अन्यथा अगर (amdgpu_device_supports_boco(drm_dev)) अणु
		/* Only need to handle PCI state in the driver क्रम ATPX
		 * PCI core handles it क्रम _PR3.
		 */
		pci_set_master(pdev);
	पूर्ण अन्यथा अगर (amdgpu_device_supports_baco(drm_dev)) अणु
		amdgpu_device_baco_निकास(drm_dev);
	पूर्ण
	ret = amdgpu_device_resume(drm_dev, false);
	अगर (ret)
		वापस ret;

	अगर (amdgpu_device_supports_px(drm_dev))
		drm_dev->चयन_घातer_state = DRM_SWITCH_POWER_ON;
	adev->in_runpm = false;
	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_pmops_runसमय_idle(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(drm_dev);
	/* we करोn't want the मुख्य rpm_idle to call suspend - we want to स्वतःsuspend */
	पूर्णांक ret = 1;

	अगर (!adev->runpm) अणु
		pm_runसमय_क्रमbid(dev);
		वापस -EBUSY;
	पूर्ण

	अगर (amdgpu_device_has_dc_support(adev)) अणु
		काष्ठा drm_crtc *crtc;

		drm_modeset_lock_all(drm_dev);

		drm_क्रम_each_crtc(crtc, drm_dev) अणु
			अगर (crtc->state->active) अणु
				ret = -EBUSY;
				अवरोध;
			पूर्ण
		पूर्ण

		drm_modeset_unlock_all(drm_dev);

	पूर्ण अन्यथा अणु
		काष्ठा drm_connector *list_connector;
		काष्ठा drm_connector_list_iter iter;

		mutex_lock(&drm_dev->mode_config.mutex);
		drm_modeset_lock(&drm_dev->mode_config.connection_mutex, शून्य);

		drm_connector_list_iter_begin(drm_dev, &iter);
		drm_क्रम_each_connector_iter(list_connector, &iter) अणु
			अगर (list_connector->dpms ==  DRM_MODE_DPMS_ON) अणु
				ret = -EBUSY;
				अवरोध;
			पूर्ण
		पूर्ण

		drm_connector_list_iter_end(&iter);

		drm_modeset_unlock(&drm_dev->mode_config.connection_mutex);
		mutex_unlock(&drm_dev->mode_config.mutex);
	पूर्ण

	अगर (ret == -EBUSY)
		DRM_DEBUG_DRIVER("failing to power off - crtc active\n");

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_स्वतःsuspend(dev);
	वापस ret;
पूर्ण

दीर्घ amdgpu_drm_ioctl(काष्ठा file *filp,
		      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा drm_file *file_priv = filp->निजी_data;
	काष्ठा drm_device *dev;
	दीर्घ ret;
	dev = file_priv->minor->dev;
	ret = pm_runसमय_get_sync(dev->dev);
	अगर (ret < 0)
		जाओ out;

	ret = drm_ioctl(filp, cmd, arg);

	pm_runसमय_mark_last_busy(dev->dev);
out:
	pm_runसमय_put_स्वतःsuspend(dev->dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops amdgpu_pm_ops = अणु
	.prepare = amdgpu_pmops_prepare,
	.complete = amdgpu_pmops_complete,
	.suspend = amdgpu_pmops_suspend,
	.resume = amdgpu_pmops_resume,
	.मुक्तze = amdgpu_pmops_मुक्तze,
	.thaw = amdgpu_pmops_thaw,
	.घातeroff = amdgpu_pmops_घातeroff,
	.restore = amdgpu_pmops_restore,
	.runसमय_suspend = amdgpu_pmops_runसमय_suspend,
	.runसमय_resume = amdgpu_pmops_runसमय_resume,
	.runसमय_idle = amdgpu_pmops_runसमय_idle,
पूर्ण;

अटल पूर्णांक amdgpu_flush(काष्ठा file *f, fl_owner_t id)
अणु
	काष्ठा drm_file *file_priv = f->निजी_data;
	काष्ठा amdgpu_fpriv *fpriv = file_priv->driver_priv;
	दीर्घ समयout = MAX_WAIT_SCHED_ENTITY_Q_EMPTY;

	समयout = amdgpu_ctx_mgr_entity_flush(&fpriv->ctx_mgr, समयout);
	समयout = amdgpu_vm_रुको_idle(&fpriv->vm, समयout);

	वापस समयout >= 0 ? 0 : समयout;
पूर्ण

अटल स्थिर काष्ठा file_operations amdgpu_driver_kms_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drm_खोलो,
	.flush = amdgpu_flush,
	.release = drm_release,
	.unlocked_ioctl = amdgpu_drm_ioctl,
	.mmap = amdgpu_mmap,
	.poll = drm_poll,
	.पढ़ो = drm_पढ़ो,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = amdgpu_kms_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

पूर्णांक amdgpu_file_to_fpriv(काष्ठा file *filp, काष्ठा amdgpu_fpriv **fpriv)
अणु
	काष्ठा drm_file *file;

	अगर (!filp)
		वापस -EINVAL;

	अगर (filp->f_op != &amdgpu_driver_kms_fops) अणु
		वापस -EINVAL;
	पूर्ण

	file = filp->निजी_data;
	*fpriv = file->driver_priv;
	वापस 0;
पूर्ण

स्थिर काष्ठा drm_ioctl_desc amdgpu_ioctls_kms[] = अणु
	DRM_IOCTL_DEF_DRV(AMDGPU_GEM_CREATE, amdgpu_gem_create_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(AMDGPU_CTX, amdgpu_ctx_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(AMDGPU_VM, amdgpu_vm_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(AMDGPU_SCHED, amdgpu_sched_ioctl, DRM_MASTER),
	DRM_IOCTL_DEF_DRV(AMDGPU_BO_LIST, amdgpu_bo_list_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(AMDGPU_FENCE_TO_HANDLE, amdgpu_cs_fence_to_handle_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	/* KMS */
	DRM_IOCTL_DEF_DRV(AMDGPU_GEM_MMAP, amdgpu_gem_mmap_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(AMDGPU_GEM_WAIT_IDLE, amdgpu_gem_रुको_idle_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(AMDGPU_CS, amdgpu_cs_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(AMDGPU_INFO, amdgpu_info_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(AMDGPU_WAIT_CS, amdgpu_cs_रुको_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(AMDGPU_WAIT_FENCES, amdgpu_cs_रुको_fences_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(AMDGPU_GEM_METADATA, amdgpu_gem_metadata_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(AMDGPU_GEM_VA, amdgpu_gem_va_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(AMDGPU_GEM_OP, amdgpu_gem_op_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(AMDGPU_GEM_USERPTR, amdgpu_gem_userptr_ioctl, DRM_AUTH|DRM_RENDER_ALLOW),
पूर्ण;

अटल स्थिर काष्ठा drm_driver amdgpu_kms_driver = अणु
	.driver_features =
	    DRIVER_ATOMIC |
	    DRIVER_GEM |
	    DRIVER_RENDER | DRIVER_MODESET | DRIVER_SYNCOBJ |
	    DRIVER_SYNCOBJ_TIMELINE,
	.खोलो = amdgpu_driver_खोलो_kms,
	.postबंद = amdgpu_driver_postबंद_kms,
	.lastबंद = amdgpu_driver_lastबंद_kms,
	.irq_handler = amdgpu_irq_handler,
	.ioctls = amdgpu_ioctls_kms,
	.num_ioctls = ARRAY_SIZE(amdgpu_ioctls_kms),
	.dumb_create = amdgpu_mode_dumb_create,
	.dumb_map_offset = amdgpu_mode_dumb_mmap,
	.fops = &amdgpu_driver_kms_fops,

	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_import = amdgpu_gem_prime_import,
	.gem_prime_mmap = amdgpu_gem_prime_mmap,

	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = KMS_DRIVER_MAJOR,
	.minor = KMS_DRIVER_MINOR,
	.patchlevel = KMS_DRIVER_PATCHLEVEL,
पूर्ण;

अटल काष्ठा pci_error_handlers amdgpu_pci_err_handler = अणु
	.error_detected	= amdgpu_pci_error_detected,
	.mmio_enabled	= amdgpu_pci_mmio_enabled,
	.slot_reset	= amdgpu_pci_slot_reset,
	.resume		= amdgpu_pci_resume,
पूर्ण;

अटल काष्ठा pci_driver amdgpu_kms_pci_driver = अणु
	.name = DRIVER_NAME,
	.id_table = pciidlist,
	.probe = amdgpu_pci_probe,
	.हटाओ = amdgpu_pci_हटाओ,
	.shutकरोwn = amdgpu_pci_shutकरोwn,
	.driver.pm = &amdgpu_pm_ops,
	.err_handler = &amdgpu_pci_err_handler,
पूर्ण;

अटल पूर्णांक __init amdgpu_init(व्योम)
अणु
	पूर्णांक r;

	अगर (vgacon_text_क्रमce()) अणु
		DRM_ERROR("VGACON disables amdgpu kernel modesetting.\n");
		वापस -EINVAL;
	पूर्ण

	r = amdgpu_sync_init();
	अगर (r)
		जाओ error_sync;

	r = amdgpu_fence_slab_init();
	अगर (r)
		जाओ error_fence;

	DRM_INFO("amdgpu kernel modesetting enabled.\n");
	amdgpu_रेजिस्टर_atpx_handler();

	/* Ignore KFD init failures. Normal when CONFIG_HSA_AMD is not set. */
	amdgpu_amdkfd_init();

	/* let modprobe override vga console setting */
	वापस pci_रेजिस्टर_driver(&amdgpu_kms_pci_driver);

error_fence:
	amdgpu_sync_fini();

error_sync:
	वापस r;
पूर्ण

अटल व्योम __निकास amdgpu_निकास(व्योम)
अणु
	amdgpu_amdkfd_fini();
	pci_unरेजिस्टर_driver(&amdgpu_kms_pci_driver);
	amdgpu_unरेजिस्टर_atpx_handler();
	amdgpu_sync_fini();
	amdgpu_fence_slab_fini();
	mmu_notअगरier_synchronize();
पूर्ण

module_init(amdgpu_init);
module_निकास(amdgpu_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL and additional rights");
