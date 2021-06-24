<शैली गुरु>
/******************************************************************************
 * This software may be used and distributed according to the terms of
 * the GNU General Public License (GPL), incorporated herein by reference.
 * Drivers based on or derived from this code fall under the GPL and must
 * retain the authorship, copyright and license notice.  This file is not
 * a complete program and may only be used when the entire operating
 * प्रणाली is licensed under the GPL.
 * See the file COPYING in this distribution क्रम more inक्रमmation.
 *
 * vxge-traffic.c: Driver क्रम Exar Corp's X3100 Series 10GbE PCIe I/O
 *                 Virtualized Server Adapter.
 * Copyright(c) 2002-2010 Exar Corp.
 ******************************************************************************/
#समावेश <linux/etherdevice.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/prefetch.h>

#समावेश "vxge-traffic.h"
#समावेश "vxge-config.h"
#समावेश "vxge-main.h"

/*
 * vxge_hw_vpath_पूर्णांकr_enable - Enable vpath पूर्णांकerrupts.
 * @vp: Virtual Path handle.
 *
 * Enable vpath पूर्णांकerrupts. The function is to be executed the last in
 * vpath initialization sequence.
 *
 * See also: vxge_hw_vpath_पूर्णांकr_disable()
 */
क्रमागत vxge_hw_status vxge_hw_vpath_पूर्णांकr_enable(काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	काष्ठा __vxge_hw_भवpath *vpath;
	काष्ठा vxge_hw_vpath_reg __iomem *vp_reg;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	अगर (vp == शून्य) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	vpath = vp->vpath;

	अगर (vpath->vp_खोलो == VXGE_HW_VP_NOT_OPEN) अणु
		status = VXGE_HW_ERR_VPATH_NOT_OPEN;
		जाओ निकास;
	पूर्ण

	vp_reg = vpath->vp_reg;

	ग_लिखोq(VXGE_HW_INTR_MASK_ALL, &vp_reg->kdfcctl_errors_reg);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->general_errors_reg);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->pci_config_errors_reg);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->mrpcim_to_vpath_alarm_reg);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->srpcim_to_vpath_alarm_reg);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->vpath_ppअगर_पूर्णांक_status);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->srpcim_msg_to_vpath_reg);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->vpath_pcipअगर_पूर्णांक_status);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->prc_alarm_reg);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->wrdma_alarm_status);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->asic_ntwk_vp_err_reg);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->xgmac_vp_पूर्णांक_status);

	पढ़ोq(&vp_reg->vpath_general_पूर्णांक_status);

	/* Mask unwanted पूर्णांकerrupts */

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->vpath_pcipअगर_पूर्णांक_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->srpcim_msg_to_vpath_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->srpcim_to_vpath_alarm_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->mrpcim_to_vpath_alarm_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->pci_config_errors_mask);

	/* Unmask the inभागidual पूर्णांकerrupts */

	ग_लिखोq((u32)vxge_bVALn((VXGE_HW_GENERAL_ERRORS_REG_DBLGEN_FIFO1_OVRFLOW|
		VXGE_HW_GENERAL_ERRORS_REG_DBLGEN_FIFO2_OVRFLOW|
		VXGE_HW_GENERAL_ERRORS_REG_STATSB_DROP_TIMEOUT_REQ|
		VXGE_HW_GENERAL_ERRORS_REG_STATSB_PIF_CHAIN_ERR), 0, 32),
		&vp_reg->general_errors_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper(
		(u32)vxge_bVALn((VXGE_HW_KDFCCTL_ERRORS_REG_KDFCCTL_FIFO1_OVRWR|
		VXGE_HW_KDFCCTL_ERRORS_REG_KDFCCTL_FIFO2_OVRWR|
		VXGE_HW_KDFCCTL_ERRORS_REG_KDFCCTL_FIFO1_POISON|
		VXGE_HW_KDFCCTL_ERRORS_REG_KDFCCTL_FIFO2_POISON|
		VXGE_HW_KDFCCTL_ERRORS_REG_KDFCCTL_FIFO1_DMA_ERR|
		VXGE_HW_KDFCCTL_ERRORS_REG_KDFCCTL_FIFO2_DMA_ERR), 0, 32),
		&vp_reg->kdfcctl_errors_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper(0, &vp_reg->vpath_ppअगर_पूर्णांक_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper(
		(u32)vxge_bVALn(VXGE_HW_PRC_ALARM_REG_PRC_RING_BUMP, 0, 32),
		&vp_reg->prc_alarm_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper(0, &vp_reg->wrdma_alarm_mask);
	__vxge_hw_pio_mem_ग_लिखो32_upper(0, &vp_reg->xgmac_vp_पूर्णांक_mask);

	अगर (vpath->hldev->first_vp_id != vpath->vp_id)
		__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->asic_ntwk_vp_err_mask);
	अन्यथा
		__vxge_hw_pio_mem_ग_लिखो32_upper((u32)vxge_bVALn((
		VXGE_HW_ASIC_NTWK_VP_ERR_REG_XMACJ_NTWK_REAFFIRMED_FAULT |
		VXGE_HW_ASIC_NTWK_VP_ERR_REG_XMACJ_NTWK_REAFFIRMED_OK), 0, 32),
		&vp_reg->asic_ntwk_vp_err_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper(0,
		&vp_reg->vpath_general_पूर्णांक_mask);
निकास:
	वापस status;

पूर्ण

/*
 * vxge_hw_vpath_पूर्णांकr_disable - Disable vpath पूर्णांकerrupts.
 * @vp: Virtual Path handle.
 *
 * Disable vpath पूर्णांकerrupts. The function is to be executed the last in
 * vpath initialization sequence.
 *
 * See also: vxge_hw_vpath_पूर्णांकr_enable()
 */
क्रमागत vxge_hw_status vxge_hw_vpath_पूर्णांकr_disable(
			काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	काष्ठा __vxge_hw_भवpath *vpath;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा vxge_hw_vpath_reg __iomem *vp_reg;
	अगर (vp == शून्य) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	vpath = vp->vpath;

	अगर (vpath->vp_खोलो == VXGE_HW_VP_NOT_OPEN) अणु
		status = VXGE_HW_ERR_VPATH_NOT_OPEN;
		जाओ निकास;
	पूर्ण
	vp_reg = vpath->vp_reg;

	__vxge_hw_pio_mem_ग_लिखो32_upper(
		(u32)VXGE_HW_INTR_MASK_ALL,
		&vp_reg->vpath_general_पूर्णांक_mask);

	ग_लिखोq(VXGE_HW_INTR_MASK_ALL, &vp_reg->kdfcctl_errors_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->general_errors_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->pci_config_errors_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->mrpcim_to_vpath_alarm_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->srpcim_to_vpath_alarm_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->vpath_ppअगर_पूर्णांक_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->srpcim_msg_to_vpath_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->vpath_pcipअगर_पूर्णांक_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->wrdma_alarm_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->prc_alarm_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->xgmac_vp_पूर्णांक_mask);

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)VXGE_HW_INTR_MASK_ALL,
			&vp_reg->asic_ntwk_vp_err_mask);

निकास:
	वापस status;
पूर्ण

व्योम vxge_hw_vpath_tti_ci_set(काष्ठा __vxge_hw_fअगरo *fअगरo)
अणु
	काष्ठा vxge_hw_vpath_reg __iomem *vp_reg;
	काष्ठा vxge_hw_vp_config *config;
	u64 val64;

	अगर (fअगरo->config->enable != VXGE_HW_FIFO_ENABLE)
		वापस;

	vp_reg = fअगरo->vp_reg;
	config = container_of(fअगरo->config, काष्ठा vxge_hw_vp_config, fअगरo);

	अगर (config->tti.समयr_ci_en != VXGE_HW_TIM_TIMER_CI_ENABLE) अणु
		config->tti.समयr_ci_en = VXGE_HW_TIM_TIMER_CI_ENABLE;
		val64 = पढ़ोq(&vp_reg->tim_cfg1_पूर्णांक_num[VXGE_HW_VPATH_INTR_TX]);
		val64 |= VXGE_HW_TIM_CFG1_INT_NUM_TIMER_CI;
		fअगरo->tim_tti_cfg1_saved = val64;
		ग_लिखोq(val64, &vp_reg->tim_cfg1_पूर्णांक_num[VXGE_HW_VPATH_INTR_TX]);
	पूर्ण
पूर्ण

व्योम vxge_hw_vpath_dynamic_rti_ci_set(काष्ठा __vxge_hw_ring *ring)
अणु
	u64 val64 = ring->tim_rti_cfg1_saved;

	val64 |= VXGE_HW_TIM_CFG1_INT_NUM_TIMER_CI;
	ring->tim_rti_cfg1_saved = val64;
	ग_लिखोq(val64, &ring->vp_reg->tim_cfg1_पूर्णांक_num[VXGE_HW_VPATH_INTR_RX]);
पूर्ण

व्योम vxge_hw_vpath_dynamic_tti_rसमयr_set(काष्ठा __vxge_hw_fअगरo *fअगरo)
अणु
	u64 val64 = fअगरo->tim_tti_cfg3_saved;
	u64 समयr = (fअगरo->rसमयr * 1000) / 272;

	val64 &= ~VXGE_HW_TIM_CFG3_INT_NUM_RTIMER_VAL(0x3ffffff);
	अगर (समयr)
		val64 |= VXGE_HW_TIM_CFG3_INT_NUM_RTIMER_VAL(समयr) |
			VXGE_HW_TIM_CFG3_INT_NUM_RTIMER_EVENT_SF(5);

	ग_लिखोq(val64, &fअगरo->vp_reg->tim_cfg3_पूर्णांक_num[VXGE_HW_VPATH_INTR_TX]);
	/* tti_cfg3_saved is not updated again because it is
	 * initialized at one place only - init समय.
	 */
पूर्ण

व्योम vxge_hw_vpath_dynamic_rti_rसमयr_set(काष्ठा __vxge_hw_ring *ring)
अणु
	u64 val64 = ring->tim_rti_cfg3_saved;
	u64 समयr = (ring->rसमयr * 1000) / 272;

	val64 &= ~VXGE_HW_TIM_CFG3_INT_NUM_RTIMER_VAL(0x3ffffff);
	अगर (समयr)
		val64 |= VXGE_HW_TIM_CFG3_INT_NUM_RTIMER_VAL(समयr) |
			VXGE_HW_TIM_CFG3_INT_NUM_RTIMER_EVENT_SF(4);

	ग_लिखोq(val64, &ring->vp_reg->tim_cfg3_पूर्णांक_num[VXGE_HW_VPATH_INTR_RX]);
	/* rti_cfg3_saved is not updated again because it is
	 * initialized at one place only - init समय.
	 */
पूर्ण

/**
 * vxge_hw_channel_msix_mask - Mask MSIX Vector.
 * @channel: Channel क्रम rx or tx handle
 * @msix_id:  MSIX ID
 *
 * The function masks the msix पूर्णांकerrupt क्रम the given msix_id
 *
 * Returns: 0
 */
व्योम vxge_hw_channel_msix_mask(काष्ठा __vxge_hw_channel *channel, पूर्णांक msix_id)
अणु

	__vxge_hw_pio_mem_ग_लिखो32_upper(
		(u32)vxge_bVALn(vxge_mBIT(msix_id >> 2), 0, 32),
		&channel->common_reg->set_msix_mask_vect[msix_id%4]);
पूर्ण

/**
 * vxge_hw_channel_msix_unmask - Unmask the MSIX Vector.
 * @channel: Channel क्रम rx or tx handle
 * @msix_id:  MSI ID
 *
 * The function unmasks the msix पूर्णांकerrupt क्रम the given msix_id
 *
 * Returns: 0
 */
व्योम
vxge_hw_channel_msix_unmask(काष्ठा __vxge_hw_channel *channel, पूर्णांक msix_id)
अणु

	__vxge_hw_pio_mem_ग_लिखो32_upper(
		(u32)vxge_bVALn(vxge_mBIT(msix_id >> 2), 0, 32),
		&channel->common_reg->clear_msix_mask_vect[msix_id%4]);
पूर्ण

/**
 * vxge_hw_channel_msix_clear - Unmask the MSIX Vector.
 * @channel: Channel क्रम rx or tx handle
 * @msix_id:  MSI ID
 *
 * The function unmasks the msix पूर्णांकerrupt क्रम the given msix_id
 * अगर configured in MSIX oneshot mode
 *
 * Returns: 0
 */
व्योम vxge_hw_channel_msix_clear(काष्ठा __vxge_hw_channel *channel, पूर्णांक msix_id)
अणु
	__vxge_hw_pio_mem_ग_लिखो32_upper(
		(u32) vxge_bVALn(vxge_mBIT(msix_id >> 2), 0, 32),
		&channel->common_reg->clr_msix_one_shot_vec[msix_id % 4]);
पूर्ण

/**
 * vxge_hw_device_set_पूर्णांकr_type - Updates the configuration
 *		with new पूर्णांकerrupt type.
 * @hldev: HW device handle.
 * @पूर्णांकr_mode: New पूर्णांकerrupt type
 */
u32 vxge_hw_device_set_पूर्णांकr_type(काष्ठा __vxge_hw_device *hldev, u32 पूर्णांकr_mode)
अणु

	अगर ((पूर्णांकr_mode != VXGE_HW_INTR_MODE_IRQLINE) &&
	   (पूर्णांकr_mode != VXGE_HW_INTR_MODE_MSIX) &&
	   (पूर्णांकr_mode != VXGE_HW_INTR_MODE_MSIX_ONE_SHOT) &&
	   (पूर्णांकr_mode != VXGE_HW_INTR_MODE_DEF))
		पूर्णांकr_mode = VXGE_HW_INTR_MODE_IRQLINE;

	hldev->config.पूर्णांकr_mode = पूर्णांकr_mode;
	वापस पूर्णांकr_mode;
पूर्ण

/**
 * vxge_hw_device_पूर्णांकr_enable - Enable पूर्णांकerrupts.
 * @hldev: HW device handle.
 *
 * Enable Titan पूर्णांकerrupts. The function is to be executed the last in
 * Titan initialization sequence.
 *
 * See also: vxge_hw_device_पूर्णांकr_disable()
 */
व्योम vxge_hw_device_पूर्णांकr_enable(काष्ठा __vxge_hw_device *hldev)
अणु
	u32 i;
	u64 val64;
	u32 val32;

	vxge_hw_device_mask_all(hldev);

	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु

		अगर (!(hldev->vpaths_deployed & vxge_mBIT(i)))
			जारी;

		vxge_hw_vpath_पूर्णांकr_enable(
			VXGE_HW_VIRTUAL_PATH_HANDLE(&hldev->भव_paths[i]));
	पूर्ण

	अगर (hldev->config.पूर्णांकr_mode == VXGE_HW_INTR_MODE_IRQLINE) अणु
		val64 = hldev->tim_पूर्णांक_mask0[VXGE_HW_VPATH_INTR_TX] |
			hldev->tim_पूर्णांक_mask0[VXGE_HW_VPATH_INTR_RX];

		अगर (val64 != 0) अणु
			ग_लिखोq(val64, &hldev->common_reg->tim_पूर्णांक_status0);

			ग_लिखोq(~val64, &hldev->common_reg->tim_पूर्णांक_mask0);
		पूर्ण

		val32 = hldev->tim_पूर्णांक_mask1[VXGE_HW_VPATH_INTR_TX] |
			hldev->tim_पूर्णांक_mask1[VXGE_HW_VPATH_INTR_RX];

		अगर (val32 != 0) अणु
			__vxge_hw_pio_mem_ग_लिखो32_upper(val32,
					&hldev->common_reg->tim_पूर्णांक_status1);

			__vxge_hw_pio_mem_ग_लिखो32_upper(~val32,
					&hldev->common_reg->tim_पूर्णांक_mask1);
		पूर्ण
	पूर्ण

	val64 = पढ़ोq(&hldev->common_reg->titan_general_पूर्णांक_status);

	vxge_hw_device_unmask_all(hldev);
पूर्ण

/**
 * vxge_hw_device_पूर्णांकr_disable - Disable Titan पूर्णांकerrupts.
 * @hldev: HW device handle.
 *
 * Disable Titan पूर्णांकerrupts.
 *
 * See also: vxge_hw_device_पूर्णांकr_enable()
 */
व्योम vxge_hw_device_पूर्णांकr_disable(काष्ठा __vxge_hw_device *hldev)
अणु
	u32 i;

	vxge_hw_device_mask_all(hldev);

	/* mask all the tim पूर्णांकerrupts */
	ग_लिखोq(VXGE_HW_INTR_MASK_ALL, &hldev->common_reg->tim_पूर्णांक_mask0);
	__vxge_hw_pio_mem_ग_लिखो32_upper(VXGE_HW_DEFAULT_32,
		&hldev->common_reg->tim_पूर्णांक_mask1);

	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु

		अगर (!(hldev->vpaths_deployed & vxge_mBIT(i)))
			जारी;

		vxge_hw_vpath_पूर्णांकr_disable(
			VXGE_HW_VIRTUAL_PATH_HANDLE(&hldev->भव_paths[i]));
	पूर्ण
पूर्ण

/**
 * vxge_hw_device_mask_all - Mask all device पूर्णांकerrupts.
 * @hldev: HW device handle.
 *
 * Mask	all device पूर्णांकerrupts.
 *
 * See also: vxge_hw_device_unmask_all()
 */
व्योम vxge_hw_device_mask_all(काष्ठा __vxge_hw_device *hldev)
अणु
	u64 val64;

	val64 = VXGE_HW_TITAN_MASK_ALL_INT_ALARM |
		VXGE_HW_TITAN_MASK_ALL_INT_TRAFFIC;

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)vxge_bVALn(val64, 0, 32),
				&hldev->common_reg->titan_mask_all_पूर्णांक);
पूर्ण

/**
 * vxge_hw_device_unmask_all - Unmask all device पूर्णांकerrupts.
 * @hldev: HW device handle.
 *
 * Unmask all device पूर्णांकerrupts.
 *
 * See also: vxge_hw_device_mask_all()
 */
व्योम vxge_hw_device_unmask_all(काष्ठा __vxge_hw_device *hldev)
अणु
	u64 val64 = 0;

	अगर (hldev->config.पूर्णांकr_mode == VXGE_HW_INTR_MODE_IRQLINE)
		val64 =  VXGE_HW_TITAN_MASK_ALL_INT_TRAFFIC;

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)vxge_bVALn(val64, 0, 32),
			&hldev->common_reg->titan_mask_all_पूर्णांक);
पूर्ण

/**
 * vxge_hw_device_flush_io - Flush io ग_लिखोs.
 * @hldev: HW device handle.
 *
 * The function	perक्रमms a पढ़ो operation to flush io ग_लिखोs.
 *
 * Returns: व्योम
 */
व्योम vxge_hw_device_flush_io(काष्ठा __vxge_hw_device *hldev)
अणु
	पढ़ोl(&hldev->common_reg->titan_general_पूर्णांक_status);
पूर्ण

/**
 * __vxge_hw_device_handle_error - Handle error
 * @hldev: HW device
 * @vp_id: Vpath Id
 * @type: Error type. Please see क्रमागत vxge_hw_eventअणुपूर्ण
 *
 * Handle error.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_device_handle_error(काष्ठा __vxge_hw_device *hldev, u32 vp_id,
			      क्रमागत vxge_hw_event type)
अणु
	चयन (type) अणु
	हाल VXGE_HW_EVENT_UNKNOWN:
		अवरोध;
	हाल VXGE_HW_EVENT_RESET_START:
	हाल VXGE_HW_EVENT_RESET_COMPLETE:
	हाल VXGE_HW_EVENT_LINK_DOWN:
	हाल VXGE_HW_EVENT_LINK_UP:
		जाओ out;
	हाल VXGE_HW_EVENT_ALARM_CLEARED:
		जाओ out;
	हाल VXGE_HW_EVENT_ECCERR:
	हाल VXGE_HW_EVENT_MRPCIM_ECCERR:
		जाओ out;
	हाल VXGE_HW_EVENT_FIFO_ERR:
	हाल VXGE_HW_EVENT_VPATH_ERR:
	हाल VXGE_HW_EVENT_CRITICAL_ERR:
	हाल VXGE_HW_EVENT_SERR:
		अवरोध;
	हाल VXGE_HW_EVENT_SRPCIM_SERR:
	हाल VXGE_HW_EVENT_MRPCIM_SERR:
		जाओ out;
	हाल VXGE_HW_EVENT_SLOT_FREEZE:
		अवरोध;
	शेष:
		vxge_निश्चित(0);
		जाओ out;
	पूर्ण

	/* notअगरy driver */
	अगर (hldev->uld_callbacks->crit_err)
		hldev->uld_callbacks->crit_err(hldev,
			type, vp_id);
out:

	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_device_handle_link_करोwn_ind
 * @hldev: HW device handle.
 *
 * Link करोwn indication handler. The function is invoked by HW when
 * Titan indicates that the link is करोwn.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_device_handle_link_करोwn_ind(काष्ठा __vxge_hw_device *hldev)
अणु
	/*
	 * If the previous link state is not करोwn, वापस.
	 */
	अगर (hldev->link_state == VXGE_HW_LINK_DOWN)
		जाओ निकास;

	hldev->link_state = VXGE_HW_LINK_DOWN;

	/* notअगरy driver */
	अगर (hldev->uld_callbacks->link_करोwn)
		hldev->uld_callbacks->link_करोwn(hldev);
निकास:
	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_device_handle_link_up_ind
 * @hldev: HW device handle.
 *
 * Link up indication handler. The function is invoked by HW when
 * Titan indicates that the link is up क्रम programmable amount of समय.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_device_handle_link_up_ind(काष्ठा __vxge_hw_device *hldev)
अणु
	/*
	 * If the previous link state is not करोwn, वापस.
	 */
	अगर (hldev->link_state == VXGE_HW_LINK_UP)
		जाओ निकास;

	hldev->link_state = VXGE_HW_LINK_UP;

	/* notअगरy driver */
	अगर (hldev->uld_callbacks->link_up)
		hldev->uld_callbacks->link_up(hldev);
निकास:
	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_vpath_alarm_process - Process Alarms.
 * @vpath: Virtual Path.
 * @skip_alarms: Do not clear the alarms
 *
 * Process vpath alarms.
 *
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_alarm_process(काष्ठा __vxge_hw_भवpath *vpath,
			      u32 skip_alarms)
अणु
	u64 val64;
	u64 alarm_status;
	u64 pic_status;
	काष्ठा __vxge_hw_device *hldev = शून्य;
	क्रमागत vxge_hw_event alarm_event = VXGE_HW_EVENT_UNKNOWN;
	u64 mask64;
	काष्ठा vxge_hw_vpath_stats_sw_info *sw_stats;
	काष्ठा vxge_hw_vpath_reg __iomem *vp_reg;

	अगर (vpath == शून्य) अणु
		alarm_event = VXGE_HW_SET_LEVEL(VXGE_HW_EVENT_UNKNOWN,
			alarm_event);
		जाओ out2;
	पूर्ण

	hldev = vpath->hldev;
	vp_reg = vpath->vp_reg;
	alarm_status = पढ़ोq(&vp_reg->vpath_general_पूर्णांक_status);

	अगर (alarm_status == VXGE_HW_ALL_FOXES) अणु
		alarm_event = VXGE_HW_SET_LEVEL(VXGE_HW_EVENT_SLOT_FREEZE,
			alarm_event);
		जाओ out;
	पूर्ण

	sw_stats = vpath->sw_stats;

	अगर (alarm_status & ~(
		VXGE_HW_VPATH_GENERAL_INT_STATUS_PIC_INT |
		VXGE_HW_VPATH_GENERAL_INT_STATUS_PCI_INT |
		VXGE_HW_VPATH_GENERAL_INT_STATUS_WRDMA_INT |
		VXGE_HW_VPATH_GENERAL_INT_STATUS_XMAC_INT)) अणु
		sw_stats->error_stats.unknown_alarms++;

		alarm_event = VXGE_HW_SET_LEVEL(VXGE_HW_EVENT_UNKNOWN,
			alarm_event);
		जाओ out;
	पूर्ण

	अगर (alarm_status & VXGE_HW_VPATH_GENERAL_INT_STATUS_XMAC_INT) अणु

		val64 = पढ़ोq(&vp_reg->xgmac_vp_पूर्णांक_status);

		अगर (val64 &
		VXGE_HW_XGMAC_VP_INT_STATUS_ASIC_NTWK_VP_ERR_ASIC_NTWK_VP_INT) अणु

			val64 = पढ़ोq(&vp_reg->asic_ntwk_vp_err_reg);

			अगर (((val64 &
			      VXGE_HW_ASIC_NW_VP_ERR_REG_XMACJ_STN_FLT) &&
			     (!(val64 &
				VXGE_HW_ASIC_NW_VP_ERR_REG_XMACJ_STN_OK))) ||
			    ((val64 &
			     VXGE_HW_ASIC_NW_VP_ERR_REG_XMACJ_STN_FLT_OCCURR) &&
			     (!(val64 &
				VXGE_HW_ASIC_NW_VP_ERR_REG_XMACJ_STN_OK_OCCURR)
				     ))) अणु
				sw_stats->error_stats.network_sustained_fault++;

				ग_लिखोq(
				VXGE_HW_ASIC_NW_VP_ERR_REG_XMACJ_STN_FLT,
					&vp_reg->asic_ntwk_vp_err_mask);

				__vxge_hw_device_handle_link_करोwn_ind(hldev);
				alarm_event = VXGE_HW_SET_LEVEL(
					VXGE_HW_EVENT_LINK_DOWN, alarm_event);
			पूर्ण

			अगर (((val64 &
			      VXGE_HW_ASIC_NW_VP_ERR_REG_XMACJ_STN_OK) &&
			     (!(val64 &
				VXGE_HW_ASIC_NW_VP_ERR_REG_XMACJ_STN_FLT))) ||
			    ((val64 &
			      VXGE_HW_ASIC_NW_VP_ERR_REG_XMACJ_STN_OK_OCCURR) &&
			     (!(val64 &
				VXGE_HW_ASIC_NW_VP_ERR_REG_XMACJ_STN_FLT_OCCURR)
				     ))) अणु

				sw_stats->error_stats.network_sustained_ok++;

				ग_लिखोq(
				VXGE_HW_ASIC_NW_VP_ERR_REG_XMACJ_STN_OK,
					&vp_reg->asic_ntwk_vp_err_mask);

				__vxge_hw_device_handle_link_up_ind(hldev);
				alarm_event = VXGE_HW_SET_LEVEL(
					VXGE_HW_EVENT_LINK_UP, alarm_event);
			पूर्ण

			ग_लिखोq(VXGE_HW_INTR_MASK_ALL,
				&vp_reg->asic_ntwk_vp_err_reg);

			alarm_event = VXGE_HW_SET_LEVEL(
				VXGE_HW_EVENT_ALARM_CLEARED, alarm_event);

			अगर (skip_alarms)
				वापस VXGE_HW_OK;
		पूर्ण
	पूर्ण

	अगर (alarm_status & VXGE_HW_VPATH_GENERAL_INT_STATUS_PIC_INT) अणु

		pic_status = पढ़ोq(&vp_reg->vpath_ppअगर_पूर्णांक_status);

		अगर (pic_status &
		    VXGE_HW_VPATH_PPIF_INT_STATUS_GENERAL_ERRORS_GENERAL_INT) अणु

			val64 = पढ़ोq(&vp_reg->general_errors_reg);
			mask64 = पढ़ोq(&vp_reg->general_errors_mask);

			अगर ((val64 &
				VXGE_HW_GENERAL_ERRORS_REG_INI_SERR_DET) &
				~mask64) अणु
				sw_stats->error_stats.ini_serr_det++;

				alarm_event = VXGE_HW_SET_LEVEL(
					VXGE_HW_EVENT_SERR, alarm_event);
			पूर्ण

			अगर ((val64 &
			    VXGE_HW_GENERAL_ERRORS_REG_DBLGEN_FIFO0_OVRFLOW) &
				~mask64) अणु
				sw_stats->error_stats.dblgen_fअगरo0_overflow++;

				alarm_event = VXGE_HW_SET_LEVEL(
					VXGE_HW_EVENT_FIFO_ERR, alarm_event);
			पूर्ण

			अगर ((val64 &
			    VXGE_HW_GENERAL_ERRORS_REG_STATSB_PIF_CHAIN_ERR) &
				~mask64)
				sw_stats->error_stats.statsb_pअगर_chain_error++;

			अगर ((val64 &
			   VXGE_HW_GENERAL_ERRORS_REG_STATSB_DROP_TIMEOUT_REQ) &
				~mask64)
				sw_stats->error_stats.statsb_drop_समयout++;

			अगर ((val64 &
				VXGE_HW_GENERAL_ERRORS_REG_TGT_ILLEGAL_ACCESS) &
				~mask64)
				sw_stats->error_stats.target_illegal_access++;

			अगर (!skip_alarms) अणु
				ग_लिखोq(VXGE_HW_INTR_MASK_ALL,
					&vp_reg->general_errors_reg);
				alarm_event = VXGE_HW_SET_LEVEL(
					VXGE_HW_EVENT_ALARM_CLEARED,
					alarm_event);
			पूर्ण
		पूर्ण

		अगर (pic_status &
		    VXGE_HW_VPATH_PPIF_INT_STATUS_KDFCCTL_ERRORS_KDFCCTL_INT) अणु

			val64 = पढ़ोq(&vp_reg->kdfcctl_errors_reg);
			mask64 = पढ़ोq(&vp_reg->kdfcctl_errors_mask);

			अगर ((val64 &
			    VXGE_HW_KDFCCTL_ERRORS_REG_KDFCCTL_FIFO0_OVRWR) &
				~mask64) अणु
				sw_stats->error_stats.kdfcctl_fअगरo0_overग_लिखो++;

				alarm_event = VXGE_HW_SET_LEVEL(
					VXGE_HW_EVENT_FIFO_ERR,
					alarm_event);
			पूर्ण

			अगर ((val64 &
			    VXGE_HW_KDFCCTL_ERRORS_REG_KDFCCTL_FIFO0_POISON) &
				~mask64) अणु
				sw_stats->error_stats.kdfcctl_fअगरo0_poison++;

				alarm_event = VXGE_HW_SET_LEVEL(
					VXGE_HW_EVENT_FIFO_ERR,
					alarm_event);
			पूर्ण

			अगर ((val64 &
			    VXGE_HW_KDFCCTL_ERRORS_REG_KDFCCTL_FIFO0_DMA_ERR) &
				~mask64) अणु
				sw_stats->error_stats.kdfcctl_fअगरo0_dma_error++;

				alarm_event = VXGE_HW_SET_LEVEL(
					VXGE_HW_EVENT_FIFO_ERR,
					alarm_event);
			पूर्ण

			अगर (!skip_alarms) अणु
				ग_लिखोq(VXGE_HW_INTR_MASK_ALL,
					&vp_reg->kdfcctl_errors_reg);
				alarm_event = VXGE_HW_SET_LEVEL(
					VXGE_HW_EVENT_ALARM_CLEARED,
					alarm_event);
			पूर्ण
		पूर्ण

	पूर्ण

	अगर (alarm_status & VXGE_HW_VPATH_GENERAL_INT_STATUS_WRDMA_INT) अणु

		val64 = पढ़ोq(&vp_reg->wrdma_alarm_status);

		अगर (val64 & VXGE_HW_WRDMA_ALARM_STATUS_PRC_ALARM_PRC_INT) अणु

			val64 = पढ़ोq(&vp_reg->prc_alarm_reg);
			mask64 = पढ़ोq(&vp_reg->prc_alarm_mask);

			अगर ((val64 & VXGE_HW_PRC_ALARM_REG_PRC_RING_BUMP)&
				~mask64)
				sw_stats->error_stats.prc_ring_bumps++;

			अगर ((val64 & VXGE_HW_PRC_ALARM_REG_PRC_RXDCM_SC_ERR) &
				~mask64) अणु
				sw_stats->error_stats.prc_rxdcm_sc_err++;

				alarm_event = VXGE_HW_SET_LEVEL(
					VXGE_HW_EVENT_VPATH_ERR,
					alarm_event);
			पूर्ण

			अगर ((val64 & VXGE_HW_PRC_ALARM_REG_PRC_RXDCM_SC_ABORT)
				& ~mask64) अणु
				sw_stats->error_stats.prc_rxdcm_sc_पात++;

				alarm_event = VXGE_HW_SET_LEVEL(
						VXGE_HW_EVENT_VPATH_ERR,
						alarm_event);
			पूर्ण

			अगर ((val64 & VXGE_HW_PRC_ALARM_REG_PRC_QUANTA_SIZE_ERR)
				 & ~mask64) अणु
				sw_stats->error_stats.prc_quanta_size_err++;

				alarm_event = VXGE_HW_SET_LEVEL(
					VXGE_HW_EVENT_VPATH_ERR,
					alarm_event);
			पूर्ण

			अगर (!skip_alarms) अणु
				ग_लिखोq(VXGE_HW_INTR_MASK_ALL,
					&vp_reg->prc_alarm_reg);
				alarm_event = VXGE_HW_SET_LEVEL(
						VXGE_HW_EVENT_ALARM_CLEARED,
						alarm_event);
			पूर्ण
		पूर्ण
	पूर्ण
out:
	hldev->stats.sw_dev_err_stats.vpath_alarms++;
out2:
	अगर ((alarm_event == VXGE_HW_EVENT_ALARM_CLEARED) ||
		(alarm_event == VXGE_HW_EVENT_UNKNOWN))
		वापस VXGE_HW_OK;

	__vxge_hw_device_handle_error(hldev, vpath->vp_id, alarm_event);

	अगर (alarm_event == VXGE_HW_EVENT_SERR)
		वापस VXGE_HW_ERR_CRITICAL;

	वापस (alarm_event == VXGE_HW_EVENT_SLOT_FREEZE) ?
		VXGE_HW_ERR_SLOT_FREEZE :
		(alarm_event == VXGE_HW_EVENT_FIFO_ERR) ? VXGE_HW_ERR_FIFO :
		VXGE_HW_ERR_VPATH;
पूर्ण

/**
 * vxge_hw_device_begin_irq - Begin IRQ processing.
 * @hldev: HW device handle.
 * @skip_alarms: Do not clear the alarms
 * @reason: "Reason" क्रम the पूर्णांकerrupt, the value of Titan's
 *	general_पूर्णांक_status रेजिस्टर.
 *
 * The function	perक्रमms two actions, It first checks whether (shared IRQ) the
 * पूर्णांकerrupt was उठाओd	by the device. Next, it	masks the device पूर्णांकerrupts.
 *
 * Note:
 * vxge_hw_device_begin_irq() करोes not flush MMIO ग_लिखोs through the
 * bridge. Thereक्रमe, two back-to-back पूर्णांकerrupts are potentially possible.
 *
 * Returns: 0, अगर the पूर्णांकerrupt	is not "ours" (note that in this हाल the
 * device reमुख्य enabled).
 * Otherwise, vxge_hw_device_begin_irq() वापसs 64bit general adapter
 * status.
 */
क्रमागत vxge_hw_status vxge_hw_device_begin_irq(काष्ठा __vxge_hw_device *hldev,
					     u32 skip_alarms, u64 *reason)
अणु
	u32 i;
	u64 val64;
	u64 adapter_status;
	u64 vpath_mask;
	क्रमागत vxge_hw_status ret = VXGE_HW_OK;

	val64 = पढ़ोq(&hldev->common_reg->titan_general_पूर्णांक_status);

	अगर (unlikely(!val64)) अणु
		/* not Titan पूर्णांकerrupt	*/
		*reason	= 0;
		ret = VXGE_HW_ERR_WRONG_IRQ;
		जाओ निकास;
	पूर्ण

	अगर (unlikely(val64 == VXGE_HW_ALL_FOXES)) अणु

		adapter_status = पढ़ोq(&hldev->common_reg->adapter_status);

		अगर (adapter_status == VXGE_HW_ALL_FOXES) अणु

			__vxge_hw_device_handle_error(hldev,
				शून्य_VPID, VXGE_HW_EVENT_SLOT_FREEZE);
			*reason	= 0;
			ret = VXGE_HW_ERR_SLOT_FREEZE;
			जाओ निकास;
		पूर्ण
	पूर्ण

	hldev->stats.sw_dev_info_stats.total_पूर्णांकr_cnt++;

	*reason	= val64;

	vpath_mask = hldev->vpaths_deployed >>
				(64 - VXGE_HW_MAX_VIRTUAL_PATHS);

	अगर (val64 &
	    VXGE_HW_TITAN_GENERAL_INT_STATUS_VPATH_TRAFFIC_INT(vpath_mask)) अणु
		hldev->stats.sw_dev_info_stats.traffic_पूर्णांकr_cnt++;

		वापस VXGE_HW_OK;
	पूर्ण

	hldev->stats.sw_dev_info_stats.not_traffic_पूर्णांकr_cnt++;

	अगर (unlikely(val64 &
			VXGE_HW_TITAN_GENERAL_INT_STATUS_VPATH_ALARM_INT)) अणु

		क्रमागत vxge_hw_status error_level = VXGE_HW_OK;

		hldev->stats.sw_dev_err_stats.vpath_alarms++;

		क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु

			अगर (!(hldev->vpaths_deployed & vxge_mBIT(i)))
				जारी;

			ret = __vxge_hw_vpath_alarm_process(
				&hldev->भव_paths[i], skip_alarms);

			error_level = VXGE_HW_SET_LEVEL(ret, error_level);

			अगर (unlikely((ret == VXGE_HW_ERR_CRITICAL) ||
				(ret == VXGE_HW_ERR_SLOT_FREEZE)))
				अवरोध;
		पूर्ण

		ret = error_level;
	पूर्ण
निकास:
	वापस ret;
पूर्ण

/**
 * vxge_hw_device_clear_tx_rx - Acknowledge (that is, clear) the
 * condition that has caused the Tx and RX पूर्णांकerrupt.
 * @hldev: HW device.
 *
 * Acknowledge (that is, clear) the condition that has caused
 * the Tx and Rx पूर्णांकerrupt.
 * See also: vxge_hw_device_begin_irq(),
 * vxge_hw_device_mask_tx_rx(), vxge_hw_device_unmask_tx_rx().
 */
व्योम vxge_hw_device_clear_tx_rx(काष्ठा __vxge_hw_device *hldev)
अणु

	अगर ((hldev->tim_पूर्णांक_mask0[VXGE_HW_VPATH_INTR_TX] != 0) ||
	   (hldev->tim_पूर्णांक_mask0[VXGE_HW_VPATH_INTR_RX] != 0)) अणु
		ग_लिखोq((hldev->tim_पूर्णांक_mask0[VXGE_HW_VPATH_INTR_TX] |
				 hldev->tim_पूर्णांक_mask0[VXGE_HW_VPATH_INTR_RX]),
				&hldev->common_reg->tim_पूर्णांक_status0);
	पूर्ण

	अगर ((hldev->tim_पूर्णांक_mask1[VXGE_HW_VPATH_INTR_TX] != 0) ||
	   (hldev->tim_पूर्णांक_mask1[VXGE_HW_VPATH_INTR_RX] != 0)) अणु
		__vxge_hw_pio_mem_ग_लिखो32_upper(
				(hldev->tim_पूर्णांक_mask1[VXGE_HW_VPATH_INTR_TX] |
				 hldev->tim_पूर्णांक_mask1[VXGE_HW_VPATH_INTR_RX]),
				&hldev->common_reg->tim_पूर्णांक_status1);
	पूर्ण
पूर्ण

/*
 * vxge_hw_channel_dtr_alloc - Allocate a dtr from the channel
 * @channel: Channel
 * @dtrh: Buffer to वापस the DTR poपूर्णांकer
 *
 * Allocates a dtr from the reserve array. If the reserve array is empty,
 * it swaps the reserve and मुक्त arrays.
 *
 */
अटल क्रमागत vxge_hw_status
vxge_hw_channel_dtr_alloc(काष्ठा __vxge_hw_channel *channel, व्योम **dtrh)
अणु
	अगर (channel->reserve_ptr - channel->reserve_top > 0) अणु
_alloc_after_swap:
		*dtrh =	channel->reserve_arr[--channel->reserve_ptr];

		वापस VXGE_HW_OK;
	पूर्ण

	/* चयन between empty	and full arrays	*/

	/* the idea behind such	a design is that by having मुक्त	and reserved
	 * arrays separated we basically separated irq and non-irq parts.
	 * i.e.	no additional lock need	to be करोne when	we मुक्त	a resource */

	अगर (channel->length - channel->मुक्त_ptr > 0) अणु
		swap(channel->reserve_arr, channel->मुक्त_arr);
		channel->reserve_ptr = channel->length;
		channel->reserve_top = channel->मुक्त_ptr;
		channel->मुक्त_ptr = channel->length;

		channel->stats->reserve_मुक्त_swaps_cnt++;

		जाओ _alloc_after_swap;
	पूर्ण

	channel->stats->full_cnt++;

	*dtrh =	शून्य;
	वापस VXGE_HW_INF_OUT_OF_DESCRIPTORS;
पूर्ण

/*
 * vxge_hw_channel_dtr_post - Post a dtr to the channel
 * @channelh: Channel
 * @dtrh: DTR poपूर्णांकer
 *
 * Posts a dtr to work array.
 *
 */
अटल व्योम
vxge_hw_channel_dtr_post(काष्ठा __vxge_hw_channel *channel, व्योम *dtrh)
अणु
	vxge_निश्चित(channel->work_arr[channel->post_index] == शून्य);

	channel->work_arr[channel->post_index++] = dtrh;

	/* wrap-around */
	अगर (channel->post_index	== channel->length)
		channel->post_index = 0;
पूर्ण

/*
 * vxge_hw_channel_dtr_try_complete - Returns next completed dtr
 * @channel: Channel
 * @dtr: Buffer to वापस the next completed DTR poपूर्णांकer
 *
 * Returns the next completed dtr with out removing it from work array
 *
 */
व्योम
vxge_hw_channel_dtr_try_complete(काष्ठा __vxge_hw_channel *channel, व्योम **dtrh)
अणु
	vxge_निश्चित(channel->compl_index < channel->length);

	*dtrh =	channel->work_arr[channel->compl_index];
	prefetch(*dtrh);
पूर्ण

/*
 * vxge_hw_channel_dtr_complete - Removes next completed dtr from the work array
 * @channel: Channel handle
 *
 * Removes the next completed dtr from work array
 *
 */
व्योम vxge_hw_channel_dtr_complete(काष्ठा __vxge_hw_channel *channel)
अणु
	channel->work_arr[channel->compl_index]	= शून्य;

	/* wrap-around */
	अगर (++channel->compl_index == channel->length)
		channel->compl_index = 0;

	channel->stats->total_compl_cnt++;
पूर्ण

/*
 * vxge_hw_channel_dtr_मुक्त - Frees a dtr
 * @channel: Channel handle
 * @dtr:  DTR poपूर्णांकer
 *
 * Returns the dtr to मुक्त array
 *
 */
व्योम vxge_hw_channel_dtr_मुक्त(काष्ठा __vxge_hw_channel *channel, व्योम *dtrh)
अणु
	channel->मुक्त_arr[--channel->मुक्त_ptr] = dtrh;
पूर्ण

/*
 * vxge_hw_channel_dtr_count
 * @channel: Channel handle. Obtained via vxge_hw_channel_खोलो().
 *
 * Retrieve number of DTRs available. This function can not be called
 * from data path. ring_initial_replenishi() is the only user.
 */
पूर्णांक vxge_hw_channel_dtr_count(काष्ठा __vxge_hw_channel *channel)
अणु
	वापस (channel->reserve_ptr - channel->reserve_top) +
		(channel->length - channel->मुक्त_ptr);
पूर्ण

/**
 * vxge_hw_ring_rxd_reserve	- Reserve ring descriptor.
 * @ring: Handle to the ring object used क्रम receive
 * @rxdh: Reserved descriptor. On success HW fills this "out" parameter
 * with a valid handle.
 *
 * Reserve Rx descriptor क्रम the subsequent filling-in driver
 * and posting on the corresponding channel (@channelh)
 * via vxge_hw_ring_rxd_post().
 *
 * Returns: VXGE_HW_OK - success.
 * VXGE_HW_INF_OUT_OF_DESCRIPTORS - Currently no descriptors available.
 *
 */
क्रमागत vxge_hw_status vxge_hw_ring_rxd_reserve(काष्ठा __vxge_hw_ring *ring,
	व्योम **rxdh)
अणु
	क्रमागत vxge_hw_status status;
	काष्ठा __vxge_hw_channel *channel;

	channel = &ring->channel;

	status = vxge_hw_channel_dtr_alloc(channel, rxdh);

	अगर (status == VXGE_HW_OK) अणु
		काष्ठा vxge_hw_ring_rxd_1 *rxdp =
			(काष्ठा vxge_hw_ring_rxd_1 *)*rxdh;

		rxdp->control_0	= rxdp->control_1 = 0;
	पूर्ण

	वापस status;
पूर्ण

/**
 * vxge_hw_ring_rxd_मुक्त - Free descriptor.
 * @ring: Handle to the ring object used क्रम receive
 * @rxdh: Descriptor handle.
 *
 * Free	the reserved descriptor. This operation is "symmetrical" to
 * vxge_hw_ring_rxd_reserve. The "free-ing" completes the descriptor's
 * lअगरecycle.
 *
 * After मुक्त-ing (see vxge_hw_ring_rxd_मुक्त()) the descriptor again can
 * be:
 *
 * - reserved (vxge_hw_ring_rxd_reserve);
 *
 * - posted	(vxge_hw_ring_rxd_post);
 *
 * - completed (vxge_hw_ring_rxd_next_completed);
 *
 * - and recycled again	(vxge_hw_ring_rxd_मुक्त).
 *
 * For alternative state transitions and more details please refer to
 * the design करोc.
 *
 */
व्योम vxge_hw_ring_rxd_मुक्त(काष्ठा __vxge_hw_ring *ring, व्योम *rxdh)
अणु
	काष्ठा __vxge_hw_channel *channel;

	channel = &ring->channel;

	vxge_hw_channel_dtr_मुक्त(channel, rxdh);

पूर्ण

/**
 * vxge_hw_ring_rxd_pre_post - Prepare rxd and post
 * @ring: Handle to the ring object used क्रम receive
 * @rxdh: Descriptor handle.
 *
 * This routine prepares a rxd and posts
 */
व्योम vxge_hw_ring_rxd_pre_post(काष्ठा __vxge_hw_ring *ring, व्योम *rxdh)
अणु
	काष्ठा __vxge_hw_channel *channel;

	channel = &ring->channel;

	vxge_hw_channel_dtr_post(channel, rxdh);
पूर्ण

/**
 * vxge_hw_ring_rxd_post_post - Process rxd after post.
 * @ring: Handle to the ring object used क्रम receive
 * @rxdh: Descriptor handle.
 *
 * Processes rxd after post
 */
व्योम vxge_hw_ring_rxd_post_post(काष्ठा __vxge_hw_ring *ring, व्योम *rxdh)
अणु
	काष्ठा vxge_hw_ring_rxd_1 *rxdp = (काष्ठा vxge_hw_ring_rxd_1 *)rxdh;

	rxdp->control_0	= VXGE_HW_RING_RXD_LIST_OWN_ADAPTER;

	अगर (ring->stats->common_stats.usage_cnt > 0)
		ring->stats->common_stats.usage_cnt--;
पूर्ण

/**
 * vxge_hw_ring_rxd_post - Post descriptor on the ring.
 * @ring: Handle to the ring object used क्रम receive
 * @rxdh: Descriptor obtained via vxge_hw_ring_rxd_reserve().
 *
 * Post	descriptor on the ring.
 * Prior to posting the	descriptor should be filled in accordance with
 * Host/Titan पूर्णांकerface specअगरication क्रम a given service (LL, etc.).
 *
 */
व्योम vxge_hw_ring_rxd_post(काष्ठा __vxge_hw_ring *ring, व्योम *rxdh)
अणु
	काष्ठा vxge_hw_ring_rxd_1 *rxdp = (काष्ठा vxge_hw_ring_rxd_1 *)rxdh;
	काष्ठा __vxge_hw_channel *channel;

	channel = &ring->channel;

	wmb();
	rxdp->control_0	= VXGE_HW_RING_RXD_LIST_OWN_ADAPTER;

	vxge_hw_channel_dtr_post(channel, rxdh);

	अगर (ring->stats->common_stats.usage_cnt > 0)
		ring->stats->common_stats.usage_cnt--;
पूर्ण

/**
 * vxge_hw_ring_rxd_post_post_wmb - Process rxd after post with memory barrier.
 * @ring: Handle to the ring object used क्रम receive
 * @rxdh: Descriptor handle.
 *
 * Processes rxd after post with memory barrier.
 */
व्योम vxge_hw_ring_rxd_post_post_wmb(काष्ठा __vxge_hw_ring *ring, व्योम *rxdh)
अणु
	wmb();
	vxge_hw_ring_rxd_post_post(ring, rxdh);
पूर्ण

/**
 * vxge_hw_ring_rxd_next_completed - Get the _next_ completed descriptor.
 * @ring: Handle to the ring object used क्रम receive
 * @rxdh: Descriptor handle. Returned by HW.
 * @t_code:	Transfer code, as per Titan User Guide,
 *	 Receive Descriptor Format. Returned by HW.
 *
 * Retrieve the	_next_ completed descriptor.
 * HW uses ring callback (*vxge_hw_ring_callback_f) to notअगरiy
 * driver of new completed descriptors. After that
 * the driver can use vxge_hw_ring_rxd_next_completed to retrieve the rest
 * completions (the very first completion is passed by HW via
 * vxge_hw_ring_callback_f).
 *
 * Implementation-wise, the driver is मुक्त to call
 * vxge_hw_ring_rxd_next_completed either immediately from inside the
 * ring callback, or in a deferred fashion and separate (from HW)
 * context.
 *
 * Non-zero @t_code means failure to fill-in receive buffer(s)
 * of the descriptor.
 * For instance, parity	error detected during the data transfer.
 * In this हाल	Titan will complete the descriptor and indicate
 * क्रम the host	that the received data is not to be used.
 * For details please refer to Titan User Guide.
 *
 * Returns: VXGE_HW_OK - success.
 * VXGE_HW_INF_NO_MORE_COMPLETED_DESCRIPTORS - No completed descriptors
 * are currently available क्रम processing.
 *
 * See also: vxge_hw_ring_callback_fअणुपूर्ण,
 * vxge_hw_fअगरo_rxd_next_completed(), क्रमागत vxge_hw_statusअणुपूर्ण.
 */
क्रमागत vxge_hw_status vxge_hw_ring_rxd_next_completed(
	काष्ठा __vxge_hw_ring *ring, व्योम **rxdh, u8 *t_code)
अणु
	काष्ठा __vxge_hw_channel *channel;
	काष्ठा vxge_hw_ring_rxd_1 *rxdp;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	u64 control_0, own;

	channel = &ring->channel;

	vxge_hw_channel_dtr_try_complete(channel, rxdh);

	rxdp = *rxdh;
	अगर (rxdp == शून्य) अणु
		status = VXGE_HW_INF_NO_MORE_COMPLETED_DESCRIPTORS;
		जाओ निकास;
	पूर्ण

	control_0 = rxdp->control_0;
	own = control_0 & VXGE_HW_RING_RXD_LIST_OWN_ADAPTER;
	*t_code	= (u8)VXGE_HW_RING_RXD_T_CODE_GET(control_0);

	/* check whether it is not the end */
	अगर (!own || *t_code == VXGE_HW_RING_T_CODE_FRM_DROP) अणु

		vxge_निश्चित((rxdp)->host_control !=
				0);

		++ring->cmpl_cnt;
		vxge_hw_channel_dtr_complete(channel);

		vxge_निश्चित(*t_code != VXGE_HW_RING_RXD_T_CODE_UNUSED);

		ring->stats->common_stats.usage_cnt++;
		अगर (ring->stats->common_stats.usage_max <
				ring->stats->common_stats.usage_cnt)
			ring->stats->common_stats.usage_max =
				ring->stats->common_stats.usage_cnt;

		status = VXGE_HW_OK;
		जाओ निकास;
	पूर्ण

	/* reset it. since we करोn't want to वापस
	 * garbage to the driver */
	*rxdh =	शून्य;
	status = VXGE_HW_INF_NO_MORE_COMPLETED_DESCRIPTORS;
निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_ring_handle_tcode - Handle transfer code.
 * @ring: Handle to the ring object used क्रम receive
 * @rxdh: Descriptor handle.
 * @t_code: One of the क्रमागतerated (and करोcumented in the Titan user guide)
 * "transfer codes".
 *
 * Handle descriptor's transfer code. The latter comes with each completed
 * descriptor.
 *
 * Returns: one of the क्रमागत vxge_hw_statusअणुपूर्ण क्रमागतerated types.
 * VXGE_HW_OK			- क्रम success.
 * VXGE_HW_ERR_CRITICAL         - when encounters critical error.
 */
क्रमागत vxge_hw_status vxge_hw_ring_handle_tcode(
	काष्ठा __vxge_hw_ring *ring, व्योम *rxdh, u8 t_code)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	/* If the t_code is not supported and अगर the
	 * t_code is other than 0x5 (unparseable packet
	 * such as unknown UPV6 header), Drop it !!!
	 */

	अगर (t_code ==  VXGE_HW_RING_T_CODE_OK ||
		t_code == VXGE_HW_RING_T_CODE_L3_PKT_ERR) अणु
		status = VXGE_HW_OK;
		जाओ निकास;
	पूर्ण

	अगर (t_code > VXGE_HW_RING_T_CODE_MULTI_ERR) अणु
		status = VXGE_HW_ERR_INVALID_TCODE;
		जाओ निकास;
	पूर्ण

	ring->stats->rxd_t_code_err_cnt[t_code]++;
निकास:
	वापस status;
पूर्ण

/**
 * __vxge_hw_non_offload_db_post - Post non offload करोorbell
 *
 * @fअगरo: fअगरohandle
 * @txdl_ptr: The starting location of the TxDL in host memory
 * @num_txds: The highest TxD in this TxDL (0 to 255 means 1 to 256)
 * @no_snoop: No snoop flags
 *
 * This function posts a non-offload करोorbell to करोorbell FIFO
 *
 */
अटल व्योम __vxge_hw_non_offload_db_post(काष्ठा __vxge_hw_fअगरo *fअगरo,
	u64 txdl_ptr, u32 num_txds, u32 no_snoop)
अणु
	ग_लिखोq(VXGE_HW_NODBW_TYPE(VXGE_HW_NODBW_TYPE_NODBW) |
		VXGE_HW_NODBW_LAST_TXD_NUMBER(num_txds) |
		VXGE_HW_NODBW_GET_NO_SNOOP(no_snoop),
		&fअगरo->nofl_db->control_0);

	ग_लिखोq(txdl_ptr, &fअगरo->nofl_db->txdl_ptr);
पूर्ण

/**
 * vxge_hw_fअगरo_मुक्त_txdl_count_get - वापसs the number of txdls available in
 * the fअगरo
 * @fअगरoh: Handle to the fअगरo object used क्रम non offload send
 */
u32 vxge_hw_fअगरo_मुक्त_txdl_count_get(काष्ठा __vxge_hw_fअगरo *fअगरoh)
अणु
	वापस vxge_hw_channel_dtr_count(&fअगरoh->channel);
पूर्ण

/**
 * vxge_hw_fअगरo_txdl_reserve - Reserve fअगरo descriptor.
 * @fअगरo: Handle to the fअगरo object used क्रम non offload send
 * @txdlh: Reserved descriptor. On success HW fills this "out" parameter
 *        with a valid handle.
 * @txdl_priv: Buffer to वापस the poपूर्णांकer to per txdl space
 *
 * Reserve a single TxDL (that is, fअगरo descriptor)
 * क्रम the subsequent filling-in by driver)
 * and posting on the corresponding channel (@channelh)
 * via vxge_hw_fअगरo_txdl_post().
 *
 * Note: it is the responsibility of driver to reserve multiple descriptors
 * क्रम lengthy (e.g., LSO) transmit operation. A single fअगरo descriptor
 * carries up to configured number (fअगरo.max_frags) of contiguous buffers.
 *
 * Returns: VXGE_HW_OK - success;
 * VXGE_HW_INF_OUT_OF_DESCRIPTORS - Currently no descriptors available
 *
 */
क्रमागत vxge_hw_status vxge_hw_fअगरo_txdl_reserve(
	काष्ठा __vxge_hw_fअगरo *fअगरo,
	व्योम **txdlh, व्योम **txdl_priv)
अणु
	काष्ठा __vxge_hw_channel *channel;
	क्रमागत vxge_hw_status status;
	पूर्णांक i;

	channel = &fअगरo->channel;

	status = vxge_hw_channel_dtr_alloc(channel, txdlh);

	अगर (status == VXGE_HW_OK) अणु
		काष्ठा vxge_hw_fअगरo_txd *txdp =
			(काष्ठा vxge_hw_fअगरo_txd *)*txdlh;
		काष्ठा __vxge_hw_fअगरo_txdl_priv *priv;

		priv = __vxge_hw_fअगरo_txdl_priv(fअगरo, txdp);

		/* reset the TxDL's निजी */
		priv->align_dma_offset = 0;
		priv->align_vaddr_start = priv->align_vaddr;
		priv->align_used_frags = 0;
		priv->frags = 0;
		priv->alloc_frags = fअगरo->config->max_frags;
		priv->next_txdl_priv = शून्य;

		*txdl_priv = (व्योम *)(माप_प्रकार)txdp->host_control;

		क्रम (i = 0; i < fअगरo->config->max_frags; i++) अणु
			txdp = ((काष्ठा vxge_hw_fअगरo_txd *)*txdlh) + i;
			txdp->control_0 = txdp->control_1 = 0;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/**
 * vxge_hw_fअगरo_txdl_buffer_set - Set transmit buffer poपूर्णांकer in the
 * descriptor.
 * @fअगरo: Handle to the fअगरo object used क्रम non offload send
 * @txdlh: Descriptor handle.
 * @frag_idx: Index of the data buffer in the caller's scatter-gather list
 *            (of buffers).
 * @dma_poपूर्णांकer: DMA address of the data buffer referenced by @frag_idx.
 * @size: Size of the data buffer (in bytes).
 *
 * This API is part of the preparation of the transmit descriptor क्रम posting
 * (via vxge_hw_fअगरo_txdl_post()). The related "preparation" APIs include
 * vxge_hw_fअगरo_txdl_mss_set() and vxge_hw_fअगरo_txdl_cksum_set_bits().
 * All three APIs fill in the fields of the fअगरo descriptor,
 * in accordance with the Titan specअगरication.
 *
 */
व्योम vxge_hw_fअगरo_txdl_buffer_set(काष्ठा __vxge_hw_fअगरo *fअगरo,
				  व्योम *txdlh, u32 frag_idx,
				  dma_addr_t dma_poपूर्णांकer, u32 size)
अणु
	काष्ठा __vxge_hw_fअगरo_txdl_priv *txdl_priv;
	काष्ठा vxge_hw_fअगरo_txd *txdp, *txdp_last;

	txdl_priv = __vxge_hw_fअगरo_txdl_priv(fअगरo, txdlh);
	txdp = (काष्ठा vxge_hw_fअगरo_txd *)txdlh  +  txdl_priv->frags;

	अगर (frag_idx != 0)
		txdp->control_0 = txdp->control_1 = 0;
	अन्यथा अणु
		txdp->control_0 |= VXGE_HW_FIFO_TXD_GATHER_CODE(
			VXGE_HW_FIFO_TXD_GATHER_CODE_FIRST);
		txdp->control_1 |= fअगरo->पूर्णांकerrupt_type;
		txdp->control_1 |= VXGE_HW_FIFO_TXD_INT_NUMBER(
			fअगरo->tx_पूर्णांकr_num);
		अगर (txdl_priv->frags) अणु
			txdp_last = (काष्ठा vxge_hw_fअगरo_txd *)txdlh  +
			(txdl_priv->frags - 1);
			txdp_last->control_0 |= VXGE_HW_FIFO_TXD_GATHER_CODE(
				VXGE_HW_FIFO_TXD_GATHER_CODE_LAST);
		पूर्ण
	पूर्ण

	vxge_निश्चित(frag_idx < txdl_priv->alloc_frags);

	txdp->buffer_poपूर्णांकer = (u64)dma_poपूर्णांकer;
	txdp->control_0 |= VXGE_HW_FIFO_TXD_BUFFER_SIZE(size);
	fअगरo->stats->total_buffers++;
	txdl_priv->frags++;
पूर्ण

/**
 * vxge_hw_fअगरo_txdl_post - Post descriptor on the fअगरo channel.
 * @fअगरo: Handle to the fअगरo object used क्रम non offload send
 * @txdlh: Descriptor obtained via vxge_hw_fअगरo_txdl_reserve()
 *
 * Post descriptor on the 'fifo' type channel क्रम transmission.
 * Prior to posting the descriptor should be filled in accordance with
 * Host/Titan पूर्णांकerface specअगरication क्रम a given service (LL, etc.).
 *
 */
व्योम vxge_hw_fअगरo_txdl_post(काष्ठा __vxge_hw_fअगरo *fअगरo, व्योम *txdlh)
अणु
	काष्ठा __vxge_hw_fअगरo_txdl_priv *txdl_priv;
	काष्ठा vxge_hw_fअगरo_txd *txdp_last;
	काष्ठा vxge_hw_fअगरo_txd *txdp_first;

	txdl_priv = __vxge_hw_fअगरo_txdl_priv(fअगरo, txdlh);
	txdp_first = txdlh;

	txdp_last = (काष्ठा vxge_hw_fअगरo_txd *)txdlh  +  (txdl_priv->frags - 1);
	txdp_last->control_0 |=
	      VXGE_HW_FIFO_TXD_GATHER_CODE(VXGE_HW_FIFO_TXD_GATHER_CODE_LAST);
	txdp_first->control_0 |= VXGE_HW_FIFO_TXD_LIST_OWN_ADAPTER;

	vxge_hw_channel_dtr_post(&fअगरo->channel, txdlh);

	__vxge_hw_non_offload_db_post(fअगरo,
		(u64)txdl_priv->dma_addr,
		txdl_priv->frags - 1,
		fअगरo->no_snoop_bits);

	fअगरo->stats->total_posts++;
	fअगरo->stats->common_stats.usage_cnt++;
	अगर (fअगरo->stats->common_stats.usage_max <
		fअगरo->stats->common_stats.usage_cnt)
		fअगरo->stats->common_stats.usage_max =
			fअगरo->stats->common_stats.usage_cnt;
पूर्ण

/**
 * vxge_hw_fअगरo_txdl_next_completed - Retrieve next completed descriptor.
 * @fअगरo: Handle to the fअगरo object used क्रम non offload send
 * @txdlh: Descriptor handle. Returned by HW.
 * @t_code: Transfer code, as per Titan User Guide,
 *          Transmit Descriptor Format.
 *          Returned by HW.
 *
 * Retrieve the _next_ completed descriptor.
 * HW uses channel callback (*vxge_hw_channel_callback_f) to notअगरiy
 * driver of new completed descriptors. After that
 * the driver can use vxge_hw_fअगरo_txdl_next_completed to retrieve the rest
 * completions (the very first completion is passed by HW via
 * vxge_hw_channel_callback_f).
 *
 * Implementation-wise, the driver is मुक्त to call
 * vxge_hw_fअगरo_txdl_next_completed either immediately from inside the
 * channel callback, or in a deferred fashion and separate (from HW)
 * context.
 *
 * Non-zero @t_code means failure to process the descriptor.
 * The failure could happen, क्रम instance, when the link is
 * करोwn, in which हाल Titan completes the descriptor because it
 * is not able to send the data out.
 *
 * For details please refer to Titan User Guide.
 *
 * Returns: VXGE_HW_OK - success.
 * VXGE_HW_INF_NO_MORE_COMPLETED_DESCRIPTORS - No completed descriptors
 * are currently available क्रम processing.
 *
 */
क्रमागत vxge_hw_status vxge_hw_fअगरo_txdl_next_completed(
	काष्ठा __vxge_hw_fअगरo *fअगरo, व्योम **txdlh,
	क्रमागत vxge_hw_fअगरo_tcode *t_code)
अणु
	काष्ठा __vxge_hw_channel *channel;
	काष्ठा vxge_hw_fअगरo_txd *txdp;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	channel = &fअगरo->channel;

	vxge_hw_channel_dtr_try_complete(channel, txdlh);

	txdp = *txdlh;
	अगर (txdp == शून्य) अणु
		status = VXGE_HW_INF_NO_MORE_COMPLETED_DESCRIPTORS;
		जाओ निकास;
	पूर्ण

	/* check whether host owns it */
	अगर (!(txdp->control_0 & VXGE_HW_FIFO_TXD_LIST_OWN_ADAPTER)) अणु

		vxge_निश्चित(txdp->host_control != 0);

		vxge_hw_channel_dtr_complete(channel);

		*t_code = (u8)VXGE_HW_FIFO_TXD_T_CODE_GET(txdp->control_0);

		अगर (fअगरo->stats->common_stats.usage_cnt > 0)
			fअगरo->stats->common_stats.usage_cnt--;

		status = VXGE_HW_OK;
		जाओ निकास;
	पूर्ण

	/* no more completions */
	*txdlh = शून्य;
	status = VXGE_HW_INF_NO_MORE_COMPLETED_DESCRIPTORS;
निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_fअगरo_handle_tcode - Handle transfer code.
 * @fअगरo: Handle to the fअगरo object used क्रम non offload send
 * @txdlh: Descriptor handle.
 * @t_code: One of the क्रमागतerated (and करोcumented in the Titan user guide)
 *          "transfer codes".
 *
 * Handle descriptor's transfer code. The latter comes with each completed
 * descriptor.
 *
 * Returns: one of the क्रमागत vxge_hw_statusअणुपूर्ण क्रमागतerated types.
 * VXGE_HW_OK - क्रम success.
 * VXGE_HW_ERR_CRITICAL - when encounters critical error.
 */
क्रमागत vxge_hw_status vxge_hw_fअगरo_handle_tcode(काष्ठा __vxge_hw_fअगरo *fअगरo,
					      व्योम *txdlh,
					      क्रमागत vxge_hw_fअगरo_tcode t_code)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर (((t_code & 0x7) < 0) || ((t_code & 0x7) > 0x4)) अणु
		status = VXGE_HW_ERR_INVALID_TCODE;
		जाओ निकास;
	पूर्ण

	fअगरo->stats->txd_t_code_err_cnt[t_code]++;
निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_fअगरo_txdl_मुक्त - Free descriptor.
 * @fअगरo: Handle to the fअगरo object used क्रम non offload send
 * @txdlh: Descriptor handle.
 *
 * Free the reserved descriptor. This operation is "symmetrical" to
 * vxge_hw_fअगरo_txdl_reserve. The "free-ing" completes the descriptor's
 * lअगरecycle.
 *
 * After मुक्त-ing (see vxge_hw_fअगरo_txdl_मुक्त()) the descriptor again can
 * be:
 *
 * - reserved (vxge_hw_fअगरo_txdl_reserve);
 *
 * - posted (vxge_hw_fअगरo_txdl_post);
 *
 * - completed (vxge_hw_fअगरo_txdl_next_completed);
 *
 * - and recycled again (vxge_hw_fअगरo_txdl_मुक्त).
 *
 * For alternative state transitions and more details please refer to
 * the design करोc.
 *
 */
व्योम vxge_hw_fअगरo_txdl_मुक्त(काष्ठा __vxge_hw_fअगरo *fअगरo, व्योम *txdlh)
अणु
	काष्ठा __vxge_hw_channel *channel;

	channel = &fअगरo->channel;

	vxge_hw_channel_dtr_मुक्त(channel, txdlh);
पूर्ण

/**
 * vxge_hw_vpath_mac_addr_add - Add the mac address entry क्रम this vpath to MAC address table.
 * @vp: Vpath handle.
 * @macaddr: MAC address to be added क्रम this vpath पूर्णांकo the list
 * @macaddr_mask: MAC address mask क्रम macaddr
 * @duplicate_mode: Duplicate MAC address add mode. Please see
 *             क्रमागत vxge_hw_vpath_mac_addr_add_modeअणुपूर्ण
 *
 * Adds the given mac address and mac address mask पूर्णांकo the list क्रम this
 * vpath.
 * see also: vxge_hw_vpath_mac_addr_delete, vxge_hw_vpath_mac_addr_get and
 * vxge_hw_vpath_mac_addr_get_next
 *
 */
क्रमागत vxge_hw_status
vxge_hw_vpath_mac_addr_add(
	काष्ठा __vxge_hw_vpath_handle *vp,
	u8 *macaddr,
	u8 *macaddr_mask,
	क्रमागत vxge_hw_vpath_mac_addr_add_mode duplicate_mode)
अणु
	u32 i;
	u64 data1 = 0ULL;
	u64 data2 = 0ULL;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर (vp == शून्य) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		data1 <<= 8;
		data1 |= (u8)macaddr[i];

		data2 <<= 8;
		data2 |= (u8)macaddr_mask[i];
	पूर्ण

	चयन (duplicate_mode) अणु
	हाल VXGE_HW_VPATH_MAC_ADDR_ADD_DUPLICATE:
		i = 0;
		अवरोध;
	हाल VXGE_HW_VPATH_MAC_ADDR_DISCARD_DUPLICATE:
		i = 1;
		अवरोध;
	हाल VXGE_HW_VPATH_MAC_ADDR_REPLACE_DUPLICATE:
		i = 2;
		अवरोध;
	शेष:
		i = 0;
		अवरोध;
	पूर्ण

	status = __vxge_hw_vpath_rts_table_set(vp,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_ADD_ENTRY,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_DA,
			0,
			VXGE_HW_RTS_ACCESS_STEER_DATA0_DA_MAC_ADDR(data1),
			VXGE_HW_RTS_ACCESS_STEER_DATA1_DA_MAC_ADDR_MASK(data2)|
			VXGE_HW_RTS_ACCESS_STEER_DATA1_DA_MAC_ADDR_MODE(i));
निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_vpath_mac_addr_get - Get the first mac address entry
 * @vp: Vpath handle.
 * @macaddr: First MAC address entry क्रम this vpath in the list
 * @macaddr_mask: MAC address mask क्रम macaddr
 *
 * Get the first mac address entry क्रम this vpath from MAC address table.
 * Return: the first mac address and mac address mask in the list क्रम this
 * vpath.
 * see also: vxge_hw_vpath_mac_addr_get_next
 *
 */
क्रमागत vxge_hw_status
vxge_hw_vpath_mac_addr_get(
	काष्ठा __vxge_hw_vpath_handle *vp,
	u8 *macaddr,
	u8 *macaddr_mask)
अणु
	u32 i;
	u64 data1 = 0ULL;
	u64 data2 = 0ULL;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर (vp == शून्य) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	status = __vxge_hw_vpath_rts_table_get(vp,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_LIST_FIRST_ENTRY,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_DA,
			0, &data1, &data2);

	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	data1 = VXGE_HW_RTS_ACCESS_STEER_DATA0_GET_DA_MAC_ADDR(data1);

	data2 = VXGE_HW_RTS_ACCESS_STEER_DATA1_GET_DA_MAC_ADDR_MASK(data2);

	क्रम (i = ETH_ALEN; i > 0; i--) अणु
		macaddr[i-1] = (u8)(data1 & 0xFF);
		data1 >>= 8;

		macaddr_mask[i-1] = (u8)(data2 & 0xFF);
		data2 >>= 8;
	पूर्ण
निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_vpath_mac_addr_get_next - Get the next mac address entry
 * @vp: Vpath handle.
 * @macaddr: Next MAC address entry क्रम this vpath in the list
 * @macaddr_mask: MAC address mask क्रम macaddr
 *
 * Get the next mac address entry क्रम this vpath from MAC address table.
 * Return: the next mac address and mac address mask in the list क्रम this
 * vpath.
 * see also: vxge_hw_vpath_mac_addr_get
 *
 */
क्रमागत vxge_hw_status
vxge_hw_vpath_mac_addr_get_next(
	काष्ठा __vxge_hw_vpath_handle *vp,
	u8 *macaddr,
	u8 *macaddr_mask)
अणु
	u32 i;
	u64 data1 = 0ULL;
	u64 data2 = 0ULL;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर (vp == शून्य) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	status = __vxge_hw_vpath_rts_table_get(vp,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_LIST_NEXT_ENTRY,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_DA,
			0, &data1, &data2);

	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	data1 = VXGE_HW_RTS_ACCESS_STEER_DATA0_GET_DA_MAC_ADDR(data1);

	data2 = VXGE_HW_RTS_ACCESS_STEER_DATA1_GET_DA_MAC_ADDR_MASK(data2);

	क्रम (i = ETH_ALEN; i > 0; i--) अणु
		macaddr[i-1] = (u8)(data1 & 0xFF);
		data1 >>= 8;

		macaddr_mask[i-1] = (u8)(data2 & 0xFF);
		data2 >>= 8;
	पूर्ण

निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_vpath_mac_addr_delete - Delete the mac address entry क्रम this vpath to MAC address table.
 * @vp: Vpath handle.
 * @macaddr: MAC address to be added क्रम this vpath पूर्णांकo the list
 * @macaddr_mask: MAC address mask क्रम macaddr
 *
 * Delete the given mac address and mac address mask पूर्णांकo the list क्रम this
 * vpath.
 * see also: vxge_hw_vpath_mac_addr_add, vxge_hw_vpath_mac_addr_get and
 * vxge_hw_vpath_mac_addr_get_next
 *
 */
क्रमागत vxge_hw_status
vxge_hw_vpath_mac_addr_delete(
	काष्ठा __vxge_hw_vpath_handle *vp,
	u8 *macaddr,
	u8 *macaddr_mask)
अणु
	u32 i;
	u64 data1 = 0ULL;
	u64 data2 = 0ULL;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर (vp == शून्य) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		data1 <<= 8;
		data1 |= (u8)macaddr[i];

		data2 <<= 8;
		data2 |= (u8)macaddr_mask[i];
	पूर्ण

	status = __vxge_hw_vpath_rts_table_set(vp,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_DELETE_ENTRY,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_DA,
			0,
			VXGE_HW_RTS_ACCESS_STEER_DATA0_DA_MAC_ADDR(data1),
			VXGE_HW_RTS_ACCESS_STEER_DATA1_DA_MAC_ADDR_MASK(data2));
निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_vpath_vid_add - Add the vlan id entry क्रम this vpath to vlan id table.
 * @vp: Vpath handle.
 * @vid: vlan id to be added क्रम this vpath पूर्णांकo the list
 *
 * Adds the given vlan id पूर्णांकo the list क्रम this  vpath.
 * see also: vxge_hw_vpath_vid_delete
 *
 */
क्रमागत vxge_hw_status
vxge_hw_vpath_vid_add(काष्ठा __vxge_hw_vpath_handle *vp, u64 vid)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर (vp == शून्य) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	status = __vxge_hw_vpath_rts_table_set(vp,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_ADD_ENTRY,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_VID,
			0, VXGE_HW_RTS_ACCESS_STEER_DATA0_VLAN_ID(vid), 0);
निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_vpath_vid_delete - Delete the vlan id entry क्रम this vpath
 *               to vlan id table.
 * @vp: Vpath handle.
 * @vid: vlan id to be added क्रम this vpath पूर्णांकo the list
 *
 * Adds the given vlan id पूर्णांकo the list क्रम this  vpath.
 * see also: vxge_hw_vpath_vid_add
 *
 */
क्रमागत vxge_hw_status
vxge_hw_vpath_vid_delete(काष्ठा __vxge_hw_vpath_handle *vp, u64 vid)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर (vp == शून्य) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	status = __vxge_hw_vpath_rts_table_set(vp,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_DELETE_ENTRY,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_VID,
			0, VXGE_HW_RTS_ACCESS_STEER_DATA0_VLAN_ID(vid), 0);
निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_vpath_promisc_enable - Enable promiscuous mode.
 * @vp: Vpath handle.
 *
 * Enable promiscuous mode of Titan-e operation.
 *
 * See also: vxge_hw_vpath_promisc_disable().
 */
क्रमागत vxge_hw_status vxge_hw_vpath_promisc_enable(
			काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	u64 val64;
	काष्ठा __vxge_hw_भवpath *vpath;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर ((vp == शून्य) || (vp->vpath->ringh == शून्य)) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	vpath = vp->vpath;

	/* Enable promiscuous mode क्रम function 0 only */
	अगर (!(vpath->hldev->access_rights &
		VXGE_HW_DEVICE_ACCESS_RIGHT_MRPCIM))
		वापस VXGE_HW_OK;

	val64 = पढ़ोq(&vpath->vp_reg->rxmac_vcfg0);

	अगर (!(val64 & VXGE_HW_RXMAC_VCFG0_UCAST_ALL_ADDR_EN)) अणु

		val64 |= VXGE_HW_RXMAC_VCFG0_UCAST_ALL_ADDR_EN |
			 VXGE_HW_RXMAC_VCFG0_MCAST_ALL_ADDR_EN |
			 VXGE_HW_RXMAC_VCFG0_BCAST_EN |
			 VXGE_HW_RXMAC_VCFG0_ALL_VID_EN;

		ग_लिखोq(val64, &vpath->vp_reg->rxmac_vcfg0);
	पूर्ण
निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_vpath_promisc_disable - Disable promiscuous mode.
 * @vp: Vpath handle.
 *
 * Disable promiscuous mode of Titan-e operation.
 *
 * See also: vxge_hw_vpath_promisc_enable().
 */
क्रमागत vxge_hw_status vxge_hw_vpath_promisc_disable(
			काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	u64 val64;
	काष्ठा __vxge_hw_भवpath *vpath;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर ((vp == शून्य) || (vp->vpath->ringh == शून्य)) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	vpath = vp->vpath;

	val64 = पढ़ोq(&vpath->vp_reg->rxmac_vcfg0);

	अगर (val64 & VXGE_HW_RXMAC_VCFG0_UCAST_ALL_ADDR_EN) अणु

		val64 &= ~(VXGE_HW_RXMAC_VCFG0_UCAST_ALL_ADDR_EN |
			   VXGE_HW_RXMAC_VCFG0_MCAST_ALL_ADDR_EN |
			   VXGE_HW_RXMAC_VCFG0_ALL_VID_EN);

		ग_लिखोq(val64, &vpath->vp_reg->rxmac_vcfg0);
	पूर्ण
निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_vpath_bcast_enable - Enable broadcast
 * @vp: Vpath handle.
 *
 * Enable receiving broadcasts.
 */
क्रमागत vxge_hw_status vxge_hw_vpath_bcast_enable(
			काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	u64 val64;
	काष्ठा __vxge_hw_भवpath *vpath;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर ((vp == शून्य) || (vp->vpath->ringh == शून्य)) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	vpath = vp->vpath;

	val64 = पढ़ोq(&vpath->vp_reg->rxmac_vcfg0);

	अगर (!(val64 & VXGE_HW_RXMAC_VCFG0_BCAST_EN)) अणु
		val64 |= VXGE_HW_RXMAC_VCFG0_BCAST_EN;
		ग_लिखोq(val64, &vpath->vp_reg->rxmac_vcfg0);
	पूर्ण
निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_vpath_mcast_enable - Enable multicast addresses.
 * @vp: Vpath handle.
 *
 * Enable Titan-e multicast addresses.
 * Returns: VXGE_HW_OK on success.
 *
 */
क्रमागत vxge_hw_status vxge_hw_vpath_mcast_enable(
			काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	u64 val64;
	काष्ठा __vxge_hw_भवpath *vpath;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर ((vp == शून्य) || (vp->vpath->ringh == शून्य)) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	vpath = vp->vpath;

	val64 = पढ़ोq(&vpath->vp_reg->rxmac_vcfg0);

	अगर (!(val64 & VXGE_HW_RXMAC_VCFG0_MCAST_ALL_ADDR_EN)) अणु
		val64 |= VXGE_HW_RXMAC_VCFG0_MCAST_ALL_ADDR_EN;
		ग_लिखोq(val64, &vpath->vp_reg->rxmac_vcfg0);
	पूर्ण
निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_vpath_mcast_disable - Disable  multicast addresses.
 * @vp: Vpath handle.
 *
 * Disable Titan-e multicast addresses.
 * Returns: VXGE_HW_OK - success.
 * VXGE_HW_ERR_INVALID_HANDLE - Invalid handle
 *
 */
क्रमागत vxge_hw_status
vxge_hw_vpath_mcast_disable(काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	u64 val64;
	काष्ठा __vxge_hw_भवpath *vpath;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर ((vp == शून्य) || (vp->vpath->ringh == शून्य)) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	vpath = vp->vpath;

	val64 = पढ़ोq(&vpath->vp_reg->rxmac_vcfg0);

	अगर (val64 & VXGE_HW_RXMAC_VCFG0_MCAST_ALL_ADDR_EN) अणु
		val64 &= ~VXGE_HW_RXMAC_VCFG0_MCAST_ALL_ADDR_EN;
		ग_लिखोq(val64, &vpath->vp_reg->rxmac_vcfg0);
	पूर्ण
निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_vpath_alarm_process - Process Alarms.
 * @vpath: Virtual Path.
 * @skip_alarms: Do not clear the alarms
 *
 * Process vpath alarms.
 *
 */
क्रमागत vxge_hw_status vxge_hw_vpath_alarm_process(
			काष्ठा __vxge_hw_vpath_handle *vp,
			u32 skip_alarms)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर (vp == शून्य) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	status = __vxge_hw_vpath_alarm_process(vp->vpath, skip_alarms);
निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_vpath_msix_set - Associate MSIX vectors with TIM पूर्णांकerrupts and
 *                            alrms
 * @vp: Virtual Path handle.
 * @tim_msix_id: MSIX vectors associated with VXGE_HW_MAX_INTR_PER_VP number of
 *             पूर्णांकerrupts(Can be repeated). If fअगरo or ring are not enabled
 *             the MSIX vector क्रम that should be set to 0
 * @alarm_msix_id: MSIX vector क्रम alarm.
 *
 * This API will associate a given MSIX vector numbers with the four TIM
 * पूर्णांकerrupts and alarm पूर्णांकerrupt.
 */
व्योम
vxge_hw_vpath_msix_set(काष्ठा __vxge_hw_vpath_handle *vp, पूर्णांक *tim_msix_id,
		       पूर्णांक alarm_msix_id)
अणु
	u64 val64;
	काष्ठा __vxge_hw_भवpath *vpath = vp->vpath;
	काष्ठा vxge_hw_vpath_reg __iomem *vp_reg = vpath->vp_reg;
	u32 vp_id = vp->vpath->vp_id;

	val64 =  VXGE_HW_INTERRUPT_CFG0_GROUP0_MSIX_FOR_TXTI(
		  (vp_id * 4) + tim_msix_id[0]) |
		 VXGE_HW_INTERRUPT_CFG0_GROUP1_MSIX_FOR_TXTI(
		  (vp_id * 4) + tim_msix_id[1]);

	ग_लिखोq(val64, &vp_reg->पूर्णांकerrupt_cfg0);

	ग_लिखोq(VXGE_HW_INTERRUPT_CFG2_ALARM_MAP_TO_MSG(
			(vpath->hldev->first_vp_id * 4) + alarm_msix_id),
			&vp_reg->पूर्णांकerrupt_cfg2);

	अगर (vpath->hldev->config.पूर्णांकr_mode ==
					VXGE_HW_INTR_MODE_MSIX_ONE_SHOT) अणु
		__vxge_hw_pio_mem_ग_लिखो32_upper((u32)vxge_bVALn(
				VXGE_HW_ONE_SHOT_VECT0_EN_ONE_SHOT_VECT0_EN,
				0, 32), &vp_reg->one_shot_vect0_en);
		__vxge_hw_pio_mem_ग_लिखो32_upper((u32)vxge_bVALn(
				VXGE_HW_ONE_SHOT_VECT1_EN_ONE_SHOT_VECT1_EN,
				0, 32), &vp_reg->one_shot_vect1_en);
		__vxge_hw_pio_mem_ग_लिखो32_upper((u32)vxge_bVALn(
				VXGE_HW_ONE_SHOT_VECT2_EN_ONE_SHOT_VECT2_EN,
				0, 32), &vp_reg->one_shot_vect2_en);
	पूर्ण
पूर्ण

/**
 * vxge_hw_vpath_msix_mask - Mask MSIX Vector.
 * @vp: Virtual Path handle.
 * @msix_id:  MSIX ID
 *
 * The function masks the msix पूर्णांकerrupt क्रम the given msix_id
 *
 * Returns: 0,
 * Otherwise, VXGE_HW_ERR_WRONG_IRQ अगर the msix index is out of range
 * status.
 * See also:
 */
व्योम
vxge_hw_vpath_msix_mask(काष्ठा __vxge_hw_vpath_handle *vp, पूर्णांक msix_id)
अणु
	काष्ठा __vxge_hw_device *hldev = vp->vpath->hldev;
	__vxge_hw_pio_mem_ग_लिखो32_upper(
		(u32) vxge_bVALn(vxge_mBIT(msix_id  >> 2), 0, 32),
		&hldev->common_reg->set_msix_mask_vect[msix_id % 4]);
पूर्ण

/**
 * vxge_hw_vpath_msix_clear - Clear MSIX Vector.
 * @vp: Virtual Path handle.
 * @msix_id:  MSI ID
 *
 * The function clears the msix पूर्णांकerrupt क्रम the given msix_id
 *
 * Returns: 0,
 * Otherwise, VXGE_HW_ERR_WRONG_IRQ अगर the msix index is out of range
 * status.
 * See also:
 */
व्योम vxge_hw_vpath_msix_clear(काष्ठा __vxge_hw_vpath_handle *vp, पूर्णांक msix_id)
अणु
	काष्ठा __vxge_hw_device *hldev = vp->vpath->hldev;

	अगर (hldev->config.पूर्णांकr_mode == VXGE_HW_INTR_MODE_MSIX_ONE_SHOT)
		__vxge_hw_pio_mem_ग_लिखो32_upper(
			(u32) vxge_bVALn(vxge_mBIT((msix_id >> 2)), 0, 32),
			&hldev->common_reg->clr_msix_one_shot_vec[msix_id % 4]);
	अन्यथा
		__vxge_hw_pio_mem_ग_लिखो32_upper(
			(u32) vxge_bVALn(vxge_mBIT((msix_id >> 2)), 0, 32),
			&hldev->common_reg->clear_msix_mask_vect[msix_id % 4]);
पूर्ण

/**
 * vxge_hw_vpath_msix_unmask - Unmask the MSIX Vector.
 * @vp: Virtual Path handle.
 * @msix_id:  MSI ID
 *
 * The function unmasks the msix पूर्णांकerrupt क्रम the given msix_id
 *
 * Returns: 0,
 * Otherwise, VXGE_HW_ERR_WRONG_IRQ अगर the msix index is out of range
 * status.
 * See also:
 */
व्योम
vxge_hw_vpath_msix_unmask(काष्ठा __vxge_hw_vpath_handle *vp, पूर्णांक msix_id)
अणु
	काष्ठा __vxge_hw_device *hldev = vp->vpath->hldev;
	__vxge_hw_pio_mem_ग_लिखो32_upper(
			(u32)vxge_bVALn(vxge_mBIT(msix_id >> 2), 0, 32),
			&hldev->common_reg->clear_msix_mask_vect[msix_id%4]);
पूर्ण

/**
 * vxge_hw_vpath_पूर्णांकa_mask_tx_rx - Mask Tx and Rx पूर्णांकerrupts.
 * @vp: Virtual Path handle.
 *
 * Mask Tx and Rx vpath पूर्णांकerrupts.
 *
 * See also: vxge_hw_vpath_पूर्णांकa_mask_tx_rx()
 */
व्योम vxge_hw_vpath_पूर्णांकa_mask_tx_rx(काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	u64	tim_पूर्णांक_mask0[4] = अणु[0 ...3] = 0पूर्ण;
	u32	tim_पूर्णांक_mask1[4] = अणु[0 ...3] = 0पूर्ण;
	u64	val64;
	काष्ठा __vxge_hw_device *hldev = vp->vpath->hldev;

	VXGE_HW_DEVICE_TIM_INT_MASK_SET(tim_पूर्णांक_mask0,
		tim_पूर्णांक_mask1, vp->vpath->vp_id);

	val64 = पढ़ोq(&hldev->common_reg->tim_पूर्णांक_mask0);

	अगर ((tim_पूर्णांक_mask0[VXGE_HW_VPATH_INTR_TX] != 0) ||
		(tim_पूर्णांक_mask0[VXGE_HW_VPATH_INTR_RX] != 0)) अणु
		ग_लिखोq((tim_पूर्णांक_mask0[VXGE_HW_VPATH_INTR_TX] |
			tim_पूर्णांक_mask0[VXGE_HW_VPATH_INTR_RX] | val64),
			&hldev->common_reg->tim_पूर्णांक_mask0);
	पूर्ण

	val64 = पढ़ोl(&hldev->common_reg->tim_पूर्णांक_mask1);

	अगर ((tim_पूर्णांक_mask1[VXGE_HW_VPATH_INTR_TX] != 0) ||
		(tim_पूर्णांक_mask1[VXGE_HW_VPATH_INTR_RX] != 0)) अणु
		__vxge_hw_pio_mem_ग_लिखो32_upper(
			(tim_पूर्णांक_mask1[VXGE_HW_VPATH_INTR_TX] |
			tim_पूर्णांक_mask1[VXGE_HW_VPATH_INTR_RX] | val64),
			&hldev->common_reg->tim_पूर्णांक_mask1);
	पूर्ण
पूर्ण

/**
 * vxge_hw_vpath_पूर्णांकa_unmask_tx_rx - Unmask Tx and Rx पूर्णांकerrupts.
 * @vp: Virtual Path handle.
 *
 * Unmask Tx and Rx vpath पूर्णांकerrupts.
 *
 * See also: vxge_hw_vpath_पूर्णांकa_mask_tx_rx()
 */
व्योम vxge_hw_vpath_पूर्णांकa_unmask_tx_rx(काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	u64	tim_पूर्णांक_mask0[4] = अणु[0 ...3] = 0पूर्ण;
	u32	tim_पूर्णांक_mask1[4] = अणु[0 ...3] = 0पूर्ण;
	u64	val64;
	काष्ठा __vxge_hw_device *hldev = vp->vpath->hldev;

	VXGE_HW_DEVICE_TIM_INT_MASK_SET(tim_पूर्णांक_mask0,
		tim_पूर्णांक_mask1, vp->vpath->vp_id);

	val64 = पढ़ोq(&hldev->common_reg->tim_पूर्णांक_mask0);

	अगर ((tim_पूर्णांक_mask0[VXGE_HW_VPATH_INTR_TX] != 0) ||
	   (tim_पूर्णांक_mask0[VXGE_HW_VPATH_INTR_RX] != 0)) अणु
		ग_लिखोq((~(tim_पूर्णांक_mask0[VXGE_HW_VPATH_INTR_TX] |
			tim_पूर्णांक_mask0[VXGE_HW_VPATH_INTR_RX])) & val64,
			&hldev->common_reg->tim_पूर्णांक_mask0);
	पूर्ण

	अगर ((tim_पूर्णांक_mask1[VXGE_HW_VPATH_INTR_TX] != 0) ||
	   (tim_पूर्णांक_mask1[VXGE_HW_VPATH_INTR_RX] != 0)) अणु
		__vxge_hw_pio_mem_ग_लिखो32_upper(
			(~(tim_पूर्णांक_mask1[VXGE_HW_VPATH_INTR_TX] |
			  tim_पूर्णांक_mask1[VXGE_HW_VPATH_INTR_RX])) & val64,
			&hldev->common_reg->tim_पूर्णांक_mask1);
	पूर्ण
पूर्ण

/**
 * vxge_hw_vpath_poll_rx - Poll Rx Virtual Path क्रम completed
 * descriptors and process the same.
 * @ring: Handle to the ring object used क्रम receive
 *
 * The function	polls the Rx क्रम the completed	descriptors and	calls
 * the driver via supplied completion	callback.
 *
 * Returns: VXGE_HW_OK, अगर the polling is completed successful.
 * VXGE_HW_COMPLETIONS_REMAIN: There are still more completed
 * descriptors available which are yet to be processed.
 *
 * See also: vxge_hw_vpath_poll_rx()
 */
क्रमागत vxge_hw_status vxge_hw_vpath_poll_rx(काष्ठा __vxge_hw_ring *ring)
अणु
	u8 t_code;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	व्योम *first_rxdh;
	पूर्णांक new_count = 0;

	ring->cmpl_cnt = 0;

	status = vxge_hw_ring_rxd_next_completed(ring, &first_rxdh, &t_code);
	अगर (status == VXGE_HW_OK)
		ring->callback(ring, first_rxdh,
			t_code, ring->channel.userdata);

	अगर (ring->cmpl_cnt != 0) अणु
		ring->करोorbell_cnt += ring->cmpl_cnt;
		अगर (ring->करोorbell_cnt >= ring->rxds_limit) अणु
			/*
			 * Each RxD is of 4 qwords, update the number of
			 * qwords replenished
			 */
			new_count = (ring->करोorbell_cnt * 4);

			/* For each block add 4 more qwords */
			ring->total_db_cnt += ring->करोorbell_cnt;
			अगर (ring->total_db_cnt >= ring->rxds_per_block) अणु
				new_count += 4;
				/* Reset total count */
				ring->total_db_cnt %= ring->rxds_per_block;
			पूर्ण
			ग_लिखोq(VXGE_HW_PRC_RXD_DOORBELL_NEW_QW_CNT(new_count),
				&ring->vp_reg->prc_rxd_करोorbell);
			पढ़ोl(&ring->common_reg->titan_general_पूर्णांक_status);
			ring->करोorbell_cnt = 0;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/**
 * vxge_hw_vpath_poll_tx - Poll Tx क्रम completed descriptors and process the same.
 * @fअगरo: Handle to the fअगरo object used क्रम non offload send
 * @skb_ptr: poपूर्णांकer to skb
 * @nr_skb: number of skbs
 * @more: more is coming
 *
 * The function polls the Tx क्रम the completed descriptors and calls
 * the driver via supplied completion callback.
 *
 * Returns: VXGE_HW_OK, अगर the polling is completed successful.
 * VXGE_HW_COMPLETIONS_REMAIN: There are still more completed
 * descriptors available which are yet to be processed.
 */
क्रमागत vxge_hw_status vxge_hw_vpath_poll_tx(काष्ठा __vxge_hw_fअगरo *fअगरo,
					काष्ठा sk_buff ***skb_ptr, पूर्णांक nr_skb,
					पूर्णांक *more)
अणु
	क्रमागत vxge_hw_fअगरo_tcode t_code;
	व्योम *first_txdlh;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा __vxge_hw_channel *channel;

	channel = &fअगरo->channel;

	status = vxge_hw_fअगरo_txdl_next_completed(fअगरo,
				&first_txdlh, &t_code);
	अगर (status == VXGE_HW_OK)
		अगर (fअगरo->callback(fअगरo, first_txdlh, t_code,
			channel->userdata, skb_ptr, nr_skb, more) != VXGE_HW_OK)
			status = VXGE_HW_COMPLETIONS_REMAIN;

	वापस status;
पूर्ण
