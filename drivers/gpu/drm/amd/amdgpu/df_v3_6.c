<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
 */
#समावेश "amdgpu.h"
#समावेश "df_v3_6.h"

#समावेश "df/df_3_6_default.h"
#समावेश "df/df_3_6_offset.h"
#समावेश "df/df_3_6_sh_mask.h"

#घोषणा DF_3_6_SMN_REG_INST_DIST        0x8
#घोषणा DF_3_6_INST_CNT                 8

/* Defined in global_features.h as FTI_PERFMON_VISIBLE */
#घोषणा DF_V3_6_MAX_COUNTERS		4

/* get flags from df perfmon config */
#घोषणा DF_V3_6_GET_EVENT(x)		(x & 0xFFUL)
#घोषणा DF_V3_6_GET_INSTANCE(x)		((x >> 8) & 0xFFUL)
#घोषणा DF_V3_6_GET_UNITMASK(x)		((x >> 16) & 0xFFUL)
#घोषणा DF_V3_6_PERFMON_OVERFLOW	0xFFFFFFFFFFFFULL

अटल u32 df_v3_6_channel_number[] = अणु1, 2, 0, 4, 0, 8, 0,
				       16, 32, 0, 0, 0, 2, 4, 8पूर्ण;

अटल uपूर्णांक64_t df_v3_6_get_fica(काष्ठा amdgpu_device *adev,
				 uपूर्णांक32_t ficaa_val)
अणु
	अचिन्हित दीर्घ flags, address, data;
	uपूर्णांक32_t ficadl_val, ficadh_val;

	address = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(address, smnDF_PIE_AON_FabricIndirectConfigAccessAddress3);
	WREG32(data, ficaa_val);

	WREG32(address, smnDF_PIE_AON_FabricIndirectConfigAccessDataLo3);
	ficadl_val = RREG32(data);

	WREG32(address, smnDF_PIE_AON_FabricIndirectConfigAccessDataHi3);
	ficadh_val = RREG32(data);

	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);

	वापस (((ficadh_val & 0xFFFFFFFFFFFFFFFF) << 32) | ficadl_val);
पूर्ण

अटल व्योम df_v3_6_set_fica(काष्ठा amdgpu_device *adev, uपूर्णांक32_t ficaa_val,
			     uपूर्णांक32_t ficadl_val, uपूर्णांक32_t ficadh_val)
अणु
	अचिन्हित दीर्घ flags, address, data;

	address = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(address, smnDF_PIE_AON_FabricIndirectConfigAccessAddress3);
	WREG32(data, ficaa_val);

	WREG32(address, smnDF_PIE_AON_FabricIndirectConfigAccessDataLo3);
	WREG32(data, ficadl_val);

	WREG32(address, smnDF_PIE_AON_FabricIndirectConfigAccessDataHi3);
	WREG32(data, ficadh_val);

	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
पूर्ण

/*
 * df_v3_6_perfmon_rreg - पढ़ो perfmon lo and hi
 *
 * required to be atomic.  no mmio method provided so subsequent पढ़ोs क्रम lo
 * and hi require to preserve df finite state machine
 */
अटल व्योम df_v3_6_perfmon_rreg(काष्ठा amdgpu_device *adev,
			    uपूर्णांक32_t lo_addr, uपूर्णांक32_t *lo_val,
			    uपूर्णांक32_t hi_addr, uपूर्णांक32_t *hi_val)
अणु
	अचिन्हित दीर्घ flags, address, data;

	address = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(address, lo_addr);
	*lo_val = RREG32(data);
	WREG32(address, hi_addr);
	*hi_val = RREG32(data);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
पूर्ण

/*
 * df_v3_6_perfmon_wreg - ग_लिखो to perfmon lo and hi
 *
 * required to be atomic.  no mmio method provided so subsequent पढ़ोs after
 * data ग_लिखोs cannot occur to preserve data fabrics finite state machine.
 */
अटल व्योम df_v3_6_perfmon_wreg(काष्ठा amdgpu_device *adev, uपूर्णांक32_t lo_addr,
			    uपूर्णांक32_t lo_val, uपूर्णांक32_t hi_addr, uपूर्णांक32_t hi_val)
अणु
	अचिन्हित दीर्घ flags, address, data;

	address = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(address, lo_addr);
	WREG32(data, lo_val);
	WREG32(address, hi_addr);
	WREG32(data, hi_val);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
पूर्ण

/* same as perfmon_wreg but वापस status on ग_लिखो value check */
अटल पूर्णांक df_v3_6_perfmon_arm_with_status(काष्ठा amdgpu_device *adev,
					  uपूर्णांक32_t lo_addr, uपूर्णांक32_t lo_val,
					  uपूर्णांक32_t hi_addr, uपूर्णांक32_t  hi_val)
अणु
	अचिन्हित दीर्घ flags, address, data;
	uपूर्णांक32_t lo_val_rb, hi_val_rb;

	address = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(address, lo_addr);
	WREG32(data, lo_val);
	WREG32(address, hi_addr);
	WREG32(data, hi_val);

	WREG32(address, lo_addr);
	lo_val_rb = RREG32(data);
	WREG32(address, hi_addr);
	hi_val_rb = RREG32(data);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);

	अगर (!(lo_val == lo_val_rb && hi_val == hi_val_rb))
		वापस -EBUSY;

	वापस 0;
पूर्ण


/*
 * retry arming counters every 100 usecs within 1 millisecond पूर्णांकerval.
 * अगर retry fails after समय out, वापस error.
 */
#घोषणा ARM_RETRY_USEC_TIMEOUT	1000
#घोषणा ARM_RETRY_USEC_INTERVAL	100
अटल पूर्णांक df_v3_6_perfmon_arm_with_retry(काष्ठा amdgpu_device *adev,
					  uपूर्णांक32_t lo_addr, uपूर्णांक32_t lo_val,
					  uपूर्णांक32_t hi_addr, uपूर्णांक32_t  hi_val)
अणु
	पूर्णांक countकरोwn = ARM_RETRY_USEC_TIMEOUT;

	जबतक (countकरोwn) अणु

		अगर (!df_v3_6_perfmon_arm_with_status(adev, lo_addr, lo_val,
						     hi_addr, hi_val))
			अवरोध;

		countकरोwn -= ARM_RETRY_USEC_INTERVAL;
		udelay(ARM_RETRY_USEC_INTERVAL);
	पूर्ण

	वापस countकरोwn > 0 ? 0 : -ETIME;
पूर्ण

/* get the number of df counters available */
अटल sमाप_प्रकार df_v3_6_get_df_cntr_avail(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev;
	काष्ठा drm_device *ddev;
	पूर्णांक i, count;

	ddev = dev_get_drvdata(dev);
	adev = drm_to_adev(ddev);
	count = 0;

	क्रम (i = 0; i < DF_V3_6_MAX_COUNTERS; i++) अणु
		अगर (adev->df_perfmon_config_assign_mask[i] == 0)
			count++;
	पूर्ण

	वापस sysfs_emit(buf, "%i\n", count);
पूर्ण

/* device attr क्रम available perfmon counters */
अटल DEVICE_ATTR(df_cntr_avail, S_IRUGO, df_v3_6_get_df_cntr_avail, शून्य);

अटल व्योम df_v3_6_query_hashes(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp;

	adev->df.hash_status.hash_64k = false;
	adev->df.hash_status.hash_2m = false;
	adev->df.hash_status.hash_1g = false;

	अगर (adev->asic_type != CHIP_ARCTURUS)
		वापस;

	/* encoding क्रम hash-enabled on Arcturus */
	अगर (adev->df.funcs->get_fb_channel_number(adev) == 0xe) अणु
		पंचांगp = RREG32_SOC15(DF, 0, mmDF_CS_UMC_AON0_DfGlobalCtrl);
		adev->df.hash_status.hash_64k = REG_GET_FIELD(पंचांगp,
						DF_CS_UMC_AON0_DfGlobalCtrl,
						GlbHashIntlvCtl64K);
		adev->df.hash_status.hash_2m = REG_GET_FIELD(पंचांगp,
						DF_CS_UMC_AON0_DfGlobalCtrl,
						GlbHashIntlvCtl2M);
		adev->df.hash_status.hash_1g = REG_GET_FIELD(पंचांगp,
						DF_CS_UMC_AON0_DfGlobalCtrl,
						GlbHashIntlvCtl1G);
	पूर्ण
पूर्ण

/* init perfmons */
अटल व्योम df_v3_6_sw_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, ret;

	ret = device_create_file(adev->dev, &dev_attr_df_cntr_avail);
	अगर (ret)
		DRM_ERROR("failed to create file for available df counters\n");

	क्रम (i = 0; i < AMDGPU_MAX_DF_PERFMONS; i++)
		adev->df_perfmon_config_assign_mask[i] = 0;

	df_v3_6_query_hashes(adev);
पूर्ण

अटल व्योम df_v3_6_sw_fini(काष्ठा amdgpu_device *adev)
अणु

	device_हटाओ_file(adev->dev, &dev_attr_df_cntr_avail);

पूर्ण

अटल व्योम df_v3_6_enable_broadcast_mode(काष्ठा amdgpu_device *adev,
					  bool enable)
अणु
	u32 पंचांगp;

	अगर (enable) अणु
		पंचांगp = RREG32_SOC15(DF, 0, mmFabricConfigAccessControl);
		पंचांगp &= ~FabricConfigAccessControl__CfgRegInstAccEn_MASK;
		WREG32_SOC15(DF, 0, mmFabricConfigAccessControl, पंचांगp);
	पूर्ण अन्यथा
		WREG32_SOC15(DF, 0, mmFabricConfigAccessControl,
			     mmFabricConfigAccessControl_DEFAULT);
पूर्ण

अटल u32 df_v3_6_get_fb_channel_number(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32_SOC15(DF, 0, mmDF_CS_UMC_AON0_DramBaseAddress0);
	पंचांगp &= DF_CS_UMC_AON0_DramBaseAddress0__IntLvNumChan_MASK;
	पंचांगp >>= DF_CS_UMC_AON0_DramBaseAddress0__IntLvNumChan__SHIFT;

	वापस पंचांगp;
पूर्ण

अटल u32 df_v3_6_get_hbm_channel_number(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक fb_channel_number;

	fb_channel_number = adev->df.funcs->get_fb_channel_number(adev);
	अगर (fb_channel_number >= ARRAY_SIZE(df_v3_6_channel_number))
		fb_channel_number = 0;

	वापस df_v3_6_channel_number[fb_channel_number];
पूर्ण

अटल व्योम df_v3_6_update_medium_grain_घड़ी_gating(काष्ठा amdgpu_device *adev,
						     bool enable)
अणु
	u32 पंचांगp;

	अगर (adev->cg_flags & AMD_CG_SUPPORT_DF_MGCG) अणु
		/* Put DF on broadcast mode */
		adev->df.funcs->enable_broadcast_mode(adev, true);

		अगर (enable) अणु
			पंचांगp = RREG32_SOC15(DF, 0,
					mmDF_PIE_AON0_DfGlobalClkGater);
			पंचांगp &= ~DF_PIE_AON0_DfGlobalClkGater__MGCGMode_MASK;
			पंचांगp |= DF_V3_6_MGCG_ENABLE_15_CYCLE_DELAY;
			WREG32_SOC15(DF, 0,
					mmDF_PIE_AON0_DfGlobalClkGater, पंचांगp);
		पूर्ण अन्यथा अणु
			पंचांगp = RREG32_SOC15(DF, 0,
					mmDF_PIE_AON0_DfGlobalClkGater);
			पंचांगp &= ~DF_PIE_AON0_DfGlobalClkGater__MGCGMode_MASK;
			पंचांगp |= DF_V3_6_MGCG_DISABLE;
			WREG32_SOC15(DF, 0,
					mmDF_PIE_AON0_DfGlobalClkGater, पंचांगp);
		पूर्ण

		/* Exit broadcast mode */
		adev->df.funcs->enable_broadcast_mode(adev, false);
	पूर्ण
पूर्ण

अटल व्योम df_v3_6_get_घड़ीgating_state(काष्ठा amdgpu_device *adev,
					  u32 *flags)
अणु
	u32 पंचांगp;

	/* AMD_CG_SUPPORT_DF_MGCG */
	पंचांगp = RREG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGlobalClkGater);
	अगर (पंचांगp & DF_V3_6_MGCG_ENABLE_15_CYCLE_DELAY)
		*flags |= AMD_CG_SUPPORT_DF_MGCG;
पूर्ण

/* get asचिन्हित df perfmon ctr as पूर्णांक */
अटल bool df_v3_6_pmc_has_counter(काष्ठा amdgpu_device *adev,
				      uपूर्णांक64_t config,
				      पूर्णांक counter_idx)
अणु

	वापस ((config & 0x0FFFFFFUL) ==
			adev->df_perfmon_config_assign_mask[counter_idx]);

पूर्ण

/* get address based on counter assignment */
अटल व्योम df_v3_6_pmc_get_addr(काष्ठा amdgpu_device *adev,
				 uपूर्णांक64_t config,
				 पूर्णांक counter_idx,
				 पूर्णांक is_ctrl,
				 uपूर्णांक32_t *lo_base_addr,
				 uपूर्णांक32_t *hi_base_addr)
अणु
	अगर (!df_v3_6_pmc_has_counter(adev, config, counter_idx))
		वापस;

	चयन (counter_idx) अणु

	हाल 0:
		*lo_base_addr = is_ctrl ? smnPerfMonCtlLo4 : smnPerfMonCtrLo4;
		*hi_base_addr = is_ctrl ? smnPerfMonCtlHi4 : smnPerfMonCtrHi4;
		अवरोध;
	हाल 1:
		*lo_base_addr = is_ctrl ? smnPerfMonCtlLo5 : smnPerfMonCtrLo5;
		*hi_base_addr = is_ctrl ? smnPerfMonCtlHi5 : smnPerfMonCtrHi5;
		अवरोध;
	हाल 2:
		*lo_base_addr = is_ctrl ? smnPerfMonCtlLo6 : smnPerfMonCtrLo6;
		*hi_base_addr = is_ctrl ? smnPerfMonCtlHi6 : smnPerfMonCtrHi6;
		अवरोध;
	हाल 3:
		*lo_base_addr = is_ctrl ? smnPerfMonCtlLo7 : smnPerfMonCtrLo7;
		*hi_base_addr = is_ctrl ? smnPerfMonCtlHi7 : smnPerfMonCtrHi7;
		अवरोध;

	पूर्ण

पूर्ण

/* get पढ़ो counter address */
अटल व्योम df_v3_6_pmc_get_पढ़ो_settings(काष्ठा amdgpu_device *adev,
					  uपूर्णांक64_t config,
					  पूर्णांक counter_idx,
					  uपूर्णांक32_t *lo_base_addr,
					  uपूर्णांक32_t *hi_base_addr)
अणु
	df_v3_6_pmc_get_addr(adev, config, counter_idx, 0, lo_base_addr,
								hi_base_addr);
पूर्ण

/* get control counter settings i.e. address and values to set */
अटल पूर्णांक df_v3_6_pmc_get_ctrl_settings(काष्ठा amdgpu_device *adev,
					  uपूर्णांक64_t config,
					  पूर्णांक counter_idx,
					  uपूर्णांक32_t *lo_base_addr,
					  uपूर्णांक32_t *hi_base_addr,
					  uपूर्णांक32_t *lo_val,
					  uपूर्णांक32_t *hi_val,
					  bool is_enable)
अणु

	uपूर्णांक32_t eventsel, instance, uniपंचांगask;
	uपूर्णांक32_t instance_10, instance_5432, instance_76;

	df_v3_6_pmc_get_addr(adev, config, counter_idx, 1, lo_base_addr,
				hi_base_addr);

	अगर ((*lo_base_addr == 0) || (*hi_base_addr == 0)) अणु
		DRM_ERROR("[DF PMC] addressing not retrieved! Lo: %x, Hi: %x",
				*lo_base_addr, *hi_base_addr);
		वापस -ENXIO;
	पूर्ण

	eventsel = DF_V3_6_GET_EVENT(config) & 0x3f;
	uniपंचांगask = DF_V3_6_GET_UNITMASK(config) & 0xf;
	instance = DF_V3_6_GET_INSTANCE(config);

	instance_10 = instance & 0x3;
	instance_5432 = (instance >> 2) & 0xf;
	instance_76 = (instance >> 6) & 0x3;

	*lo_val = (uniपंचांगask << 8) | (instance_10 << 6) | eventsel;
	*lo_val = is_enable ? *lo_val | (1 << 22) : *lo_val & ~(1 << 22);
	*hi_val = (instance_76 << 29) | instance_5432;

	DRM_DEBUG_DRIVER("config=%llx addr=%08x:%08x val=%08x:%08x",
		config, *lo_base_addr, *hi_base_addr, *lo_val, *hi_val);

	वापस 0;
पूर्ण

/* add df perक्रमmance counters क्रम पढ़ो */
अटल पूर्णांक df_v3_6_pmc_add_cntr(काष्ठा amdgpu_device *adev,
				   uपूर्णांक64_t config)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DF_V3_6_MAX_COUNTERS; i++) अणु
		अगर (adev->df_perfmon_config_assign_mask[i] == 0U) अणु
			adev->df_perfmon_config_assign_mask[i] =
							config & 0x0FFFFFFUL;
			वापस i;
		पूर्ण
	पूर्ण

	वापस -ENOSPC;
पूर्ण

#घोषणा DEFERRED_ARM_MASK	(1 << 31)
अटल पूर्णांक df_v3_6_pmc_set_deferred(काष्ठा amdgpu_device *adev,
				    पूर्णांक counter_idx, uपूर्णांक64_t config,
				    bool is_deferred)
अणु

	अगर (!df_v3_6_pmc_has_counter(adev, config, counter_idx))
		वापस -EINVAL;

	अगर (is_deferred)
		adev->df_perfmon_config_assign_mask[counter_idx] |=
							DEFERRED_ARM_MASK;
	अन्यथा
		adev->df_perfmon_config_assign_mask[counter_idx] &=
							~DEFERRED_ARM_MASK;

	वापस 0;
पूर्ण

अटल bool df_v3_6_pmc_is_deferred(काष्ठा amdgpu_device *adev,
				    पूर्णांक counter_idx,
				    uपूर्णांक64_t config)
अणु
	वापस	(df_v3_6_pmc_has_counter(adev, config, counter_idx) &&
			(adev->df_perfmon_config_assign_mask[counter_idx]
				& DEFERRED_ARM_MASK));

पूर्ण

/* release perक्रमmance counter */
अटल व्योम df_v3_6_pmc_release_cntr(काष्ठा amdgpu_device *adev,
				     uपूर्णांक64_t config,
				     पूर्णांक counter_idx)
अणु
	अगर (df_v3_6_pmc_has_counter(adev, config, counter_idx))
		adev->df_perfmon_config_assign_mask[counter_idx] = 0ULL;
पूर्ण


अटल व्योम df_v3_6_reset_perfmon_cntr(काष्ठा amdgpu_device *adev,
					 uपूर्णांक64_t config,
					 पूर्णांक counter_idx)
अणु
	uपूर्णांक32_t lo_base_addr = 0, hi_base_addr = 0;

	df_v3_6_pmc_get_पढ़ो_settings(adev, config, counter_idx, &lo_base_addr,
				      &hi_base_addr);

	अगर ((lo_base_addr == 0) || (hi_base_addr == 0))
		वापस;

	df_v3_6_perfmon_wreg(adev, lo_base_addr, 0, hi_base_addr, 0);
पूर्ण

/* वापस available counter अगर is_add == 1 otherwise वापस error status. */
अटल पूर्णांक df_v3_6_pmc_start(काष्ठा amdgpu_device *adev, uपूर्णांक64_t config,
			     पूर्णांक counter_idx, पूर्णांक is_add)
अणु
	uपूर्णांक32_t lo_base_addr, hi_base_addr, lo_val, hi_val;
	पूर्णांक err = 0, ret = 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA20:
	हाल CHIP_ARCTURUS:
		अगर (is_add)
			वापस df_v3_6_pmc_add_cntr(adev, config);

		ret = df_v3_6_pmc_get_ctrl_settings(adev,
					config,
					counter_idx,
					&lo_base_addr,
					&hi_base_addr,
					&lo_val,
					&hi_val,
					true);

		अगर (ret)
			वापस ret;

		err = df_v3_6_perfmon_arm_with_retry(adev,
						     lo_base_addr,
						     lo_val,
						     hi_base_addr,
						     hi_val);

		अगर (err)
			ret = df_v3_6_pmc_set_deferred(adev, config,
							counter_idx, true);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक df_v3_6_pmc_stop(काष्ठा amdgpu_device *adev, uपूर्णांक64_t config,
			    पूर्णांक counter_idx, पूर्णांक is_हटाओ)
अणु
	uपूर्णांक32_t lo_base_addr, hi_base_addr, lo_val, hi_val;
	पूर्णांक ret = 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA20:
	हाल CHIP_ARCTURUS:
		ret = df_v3_6_pmc_get_ctrl_settings(adev,
			config,
			counter_idx,
			&lo_base_addr,
			&hi_base_addr,
			&lo_val,
			&hi_val,
			false);

		अगर (ret)
			वापस ret;

		df_v3_6_perfmon_wreg(adev, lo_base_addr, lo_val,
							hi_base_addr, hi_val);

		अगर (is_हटाओ) अणु
			df_v3_6_reset_perfmon_cntr(adev, config, counter_idx);
			df_v3_6_pmc_release_cntr(adev, config, counter_idx);
		पूर्ण

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम df_v3_6_pmc_get_count(काष्ठा amdgpu_device *adev,
				  uपूर्णांक64_t config,
				  पूर्णांक counter_idx,
				  uपूर्णांक64_t *count)
अणु
	uपूर्णांक32_t lo_base_addr = 0, hi_base_addr = 0, lo_val = 0, hi_val = 0;
	*count = 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA20:
	हाल CHIP_ARCTURUS:
		df_v3_6_pmc_get_पढ़ो_settings(adev, config, counter_idx,
						&lo_base_addr, &hi_base_addr);

		अगर ((lo_base_addr == 0) || (hi_base_addr == 0))
			वापस;

		/* rearm the counter or throw away count value on failure */
		अगर (df_v3_6_pmc_is_deferred(adev, config, counter_idx)) अणु
			पूर्णांक rearm_err = df_v3_6_perfmon_arm_with_status(adev,
							lo_base_addr, lo_val,
							hi_base_addr, hi_val);

			अगर (rearm_err)
				वापस;

			df_v3_6_pmc_set_deferred(adev, config, counter_idx,
									false);
		पूर्ण

		df_v3_6_perfmon_rreg(adev, lo_base_addr, &lo_val,
				hi_base_addr, &hi_val);

		*count  = ((hi_val | 0ULL) << 32) | (lo_val | 0ULL);

		अगर (*count >= DF_V3_6_PERFMON_OVERFLOW)
			*count = 0;

		DRM_DEBUG_DRIVER("config=%llx addr=%08x:%08x val=%08x:%08x",
			 config, lo_base_addr, hi_base_addr, lo_val, hi_val);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

स्थिर काष्ठा amdgpu_df_funcs df_v3_6_funcs = अणु
	.sw_init = df_v3_6_sw_init,
	.sw_fini = df_v3_6_sw_fini,
	.enable_broadcast_mode = df_v3_6_enable_broadcast_mode,
	.get_fb_channel_number = df_v3_6_get_fb_channel_number,
	.get_hbm_channel_number = df_v3_6_get_hbm_channel_number,
	.update_medium_grain_घड़ी_gating =
			df_v3_6_update_medium_grain_घड़ी_gating,
	.get_घड़ीgating_state = df_v3_6_get_घड़ीgating_state,
	.pmc_start = df_v3_6_pmc_start,
	.pmc_stop = df_v3_6_pmc_stop,
	.pmc_get_count = df_v3_6_pmc_get_count,
	.get_fica = df_v3_6_get_fica,
	.set_fica = df_v3_6_set_fica,
पूर्ण;
