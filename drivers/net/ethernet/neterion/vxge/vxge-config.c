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
 * vxge-config.c: Driver क्रम Exar Corp's X3100 Series 10GbE PCIe I/O
 *                Virtualized Server Adapter.
 * Copyright(c) 2002-2010 Exar Corp.
 ******************************************************************************/
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश "vxge-traffic.h"
#समावेश "vxge-config.h"
#समावेश "vxge-main.h"

#घोषणा VXGE_HW_VPATH_STATS_PIO_READ(offset) अणु				\
	status = __vxge_hw_vpath_stats_access(vpath,			\
					      VXGE_HW_STATS_OP_READ,	\
					      offset,			\
					      &val64);			\
	अगर (status != VXGE_HW_OK)					\
		वापस status;						\
पूर्ण

अटल व्योम
vxge_hw_vpath_set_zero_rx_frm_len(काष्ठा vxge_hw_vpath_reg __iomem *vp_reg)
अणु
	u64 val64;

	val64 = पढ़ोq(&vp_reg->rxmac_vcfg0);
	val64 &= ~VXGE_HW_RXMAC_VCFG0_RTS_MAX_FRM_LEN(0x3fff);
	ग_लिखोq(val64, &vp_reg->rxmac_vcfg0);
	val64 = पढ़ोq(&vp_reg->rxmac_vcfg0);
पूर्ण

/*
 * vxge_hw_vpath_रुको_receive_idle - Wait क्रम Rx to become idle
 */
पूर्णांक vxge_hw_vpath_रुको_receive_idle(काष्ठा __vxge_hw_device *hldev, u32 vp_id)
अणु
	काष्ठा vxge_hw_vpath_reg __iomem *vp_reg;
	काष्ठा __vxge_hw_भवpath *vpath;
	u64 val64, rxd_count, rxd_spat;
	पूर्णांक count = 0, total_count = 0;

	vpath = &hldev->भव_paths[vp_id];
	vp_reg = vpath->vp_reg;

	vxge_hw_vpath_set_zero_rx_frm_len(vp_reg);

	/* Check that the ring controller क्रम this vpath has enough मुक्त RxDs
	 * to send frames to the host.  This is करोne by पढ़ोing the
	 * PRC_RXD_DOORBELL_VPn रेजिस्टर and comparing the पढ़ो value to the
	 * RXD_SPAT value क्रम the vpath.
	 */
	val64 = पढ़ोq(&vp_reg->prc_cfg6);
	rxd_spat = VXGE_HW_PRC_CFG6_GET_RXD_SPAT(val64) + 1;
	/* Use a factor of 2 when comparing rxd_count against rxd_spat क्रम some
	 * leg room.
	 */
	rxd_spat *= 2;

	करो अणु
		mdelay(1);

		rxd_count = पढ़ोq(&vp_reg->prc_rxd_करोorbell);

		/* Check that the ring controller क्रम this vpath करोes
		 * not have any frame in its pipeline.
		 */
		val64 = पढ़ोq(&vp_reg->frm_in_progress_cnt);
		अगर ((rxd_count <= rxd_spat) || (val64 > 0))
			count = 0;
		अन्यथा
			count++;
		total_count++;
	पूर्ण जबतक ((count < VXGE_HW_MIN_SUCCESSIVE_IDLE_COUNT) &&
			(total_count < VXGE_HW_MAX_POLLING_COUNT));

	अगर (total_count >= VXGE_HW_MAX_POLLING_COUNT)
		prपूर्णांकk(KERN_ALERT "%s: Still Receiving traffic. Abort wait\n",
			__func__);

	वापस total_count;
पूर्ण

/* vxge_hw_device_रुको_receive_idle - This function रुकोs until all frames
 * stored in the frame buffer क्रम each vpath asचिन्हित to the given
 * function (hldev) have been sent to the host.
 */
व्योम vxge_hw_device_रुको_receive_idle(काष्ठा __vxge_hw_device *hldev)
अणु
	पूर्णांक i, total_count = 0;

	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
		अगर (!(hldev->vpaths_deployed & vxge_mBIT(i)))
			जारी;

		total_count += vxge_hw_vpath_रुको_receive_idle(hldev, i);
		अगर (total_count >= VXGE_HW_MAX_POLLING_COUNT)
			अवरोध;
	पूर्ण
पूर्ण

/*
 * __vxge_hw_device_रेजिस्टर_poll
 * Will poll certain रेजिस्टर क्रम specअगरied amount of समय.
 * Will poll until masked bit is not cleared.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_device_रेजिस्टर_poll(व्योम __iomem *reg, u64 mask, u32 max_millis)
अणु
	u64 val64;
	u32 i = 0;

	udelay(10);

	करो अणु
		val64 = पढ़ोq(reg);
		अगर (!(val64 & mask))
			वापस VXGE_HW_OK;
		udelay(100);
	पूर्ण जबतक (++i <= 9);

	i = 0;
	करो अणु
		val64 = पढ़ोq(reg);
		अगर (!(val64 & mask))
			वापस VXGE_HW_OK;
		mdelay(1);
	पूर्ण जबतक (++i <= max_millis);

	वापस VXGE_HW_FAIL;
पूर्ण

अटल अंतरभूत क्रमागत vxge_hw_status
__vxge_hw_pio_mem_ग_लिखो64(u64 val64, व्योम __iomem *addr,
			  u64 mask, u32 max_millis)
अणु
	__vxge_hw_pio_mem_ग_लिखो32_lower((u32)vxge_bVALn(val64, 32, 32), addr);
	wmb();
	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)vxge_bVALn(val64, 0, 32), addr);
	wmb();

	वापस __vxge_hw_device_रेजिस्टर_poll(addr, mask, max_millis);
पूर्ण

अटल क्रमागत vxge_hw_status
vxge_hw_vpath_fw_api(काष्ठा __vxge_hw_भवpath *vpath, u32 action,
		     u32 fw_memo, u32 offset, u64 *data0, u64 *data1,
		     u64 *steer_ctrl)
अणु
	काष्ठा vxge_hw_vpath_reg __iomem *vp_reg = vpath->vp_reg;
	क्रमागत vxge_hw_status status;
	u64 val64;
	u32 retry = 0, max_retry = 3;

	spin_lock(&vpath->lock);
	अगर (!vpath->vp_खोलो) अणु
		spin_unlock(&vpath->lock);
		max_retry = 100;
	पूर्ण

	ग_लिखोq(*data0, &vp_reg->rts_access_steer_data0);
	ग_लिखोq(*data1, &vp_reg->rts_access_steer_data1);
	wmb();

	val64 = VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION(action) |
		VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL(fw_memo) |
		VXGE_HW_RTS_ACCESS_STEER_CTRL_OFFSET(offset) |
		VXGE_HW_RTS_ACCESS_STEER_CTRL_STROBE |
		*steer_ctrl;

	status = __vxge_hw_pio_mem_ग_लिखो64(val64,
					   &vp_reg->rts_access_steer_ctrl,
					   VXGE_HW_RTS_ACCESS_STEER_CTRL_STROBE,
					   VXGE_HW_DEF_DEVICE_POLL_MILLIS);

	/* The __vxge_hw_device_रेजिस्टर_poll can udelay क्रम a signअगरicant
	 * amount of समय, blocking other process from the CPU.  If it delays
	 * क्रम ~5secs, a NMI error can occur.  A way around this is to give up
	 * the processor via msleep, but this is not allowed is under lock.
	 * So, only allow it to sleep क्रम ~4secs अगर खोलो.  Otherwise, delay क्रम
	 * 1sec and sleep क्रम 10ms until the firmware operation has completed
	 * or समयd-out.
	 */
	जबतक ((status != VXGE_HW_OK) && retry++ < max_retry) अणु
		अगर (!vpath->vp_खोलो)
			msleep(20);
		status = __vxge_hw_device_रेजिस्टर_poll(
					&vp_reg->rts_access_steer_ctrl,
					VXGE_HW_RTS_ACCESS_STEER_CTRL_STROBE,
					VXGE_HW_DEF_DEVICE_POLL_MILLIS);
	पूर्ण

	अगर (status != VXGE_HW_OK)
		जाओ out;

	val64 = पढ़ोq(&vp_reg->rts_access_steer_ctrl);
	अगर (val64 & VXGE_HW_RTS_ACCESS_STEER_CTRL_RMACJ_STATUS) अणु
		*data0 = पढ़ोq(&vp_reg->rts_access_steer_data0);
		*data1 = पढ़ोq(&vp_reg->rts_access_steer_data1);
		*steer_ctrl = val64;
	पूर्ण अन्यथा
		status = VXGE_HW_FAIL;

out:
	अगर (vpath->vp_खोलो)
		spin_unlock(&vpath->lock);
	वापस status;
पूर्ण

क्रमागत vxge_hw_status
vxge_hw_upgrade_पढ़ो_version(काष्ठा __vxge_hw_device *hldev, u32 *major,
			     u32 *minor, u32 *build)
अणु
	u64 data0 = 0, data1 = 0, steer_ctrl = 0;
	काष्ठा __vxge_hw_भवpath *vpath;
	क्रमागत vxge_hw_status status;

	vpath = &hldev->भव_paths[hldev->first_vp_id];

	status = vxge_hw_vpath_fw_api(vpath,
				      VXGE_HW_FW_UPGRADE_ACTION,
				      VXGE_HW_FW_UPGRADE_MEMO,
				      VXGE_HW_FW_UPGRADE_OFFSET_READ,
				      &data0, &data1, &steer_ctrl);
	अगर (status != VXGE_HW_OK)
		वापस status;

	*major = VXGE_HW_RTS_ACCESS_STEER_DATA0_GET_FW_VER_MAJOR(data0);
	*minor = VXGE_HW_RTS_ACCESS_STEER_DATA0_GET_FW_VER_MINOR(data0);
	*build = VXGE_HW_RTS_ACCESS_STEER_DATA0_GET_FW_VER_BUILD(data0);

	वापस status;
पूर्ण

क्रमागत vxge_hw_status vxge_hw_flash_fw(काष्ठा __vxge_hw_device *hldev)
अणु
	u64 data0 = 0, data1 = 0, steer_ctrl = 0;
	काष्ठा __vxge_hw_भवpath *vpath;
	क्रमागत vxge_hw_status status;
	u32 ret;

	vpath = &hldev->भव_paths[hldev->first_vp_id];

	status = vxge_hw_vpath_fw_api(vpath,
				      VXGE_HW_FW_UPGRADE_ACTION,
				      VXGE_HW_FW_UPGRADE_MEMO,
				      VXGE_HW_FW_UPGRADE_OFFSET_COMMIT,
				      &data0, &data1, &steer_ctrl);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR, "%s: FW upgrade failed", __func__);
		जाओ निकास;
	पूर्ण

	ret = VXGE_HW_RTS_ACCESS_STEER_CTRL_GET_ACTION(steer_ctrl) & 0x7F;
	अगर (ret != 1) अणु
		vxge_debug_init(VXGE_ERR, "%s: FW commit failed with error %d",
				__func__, ret);
		status = VXGE_HW_FAIL;
	पूर्ण

निकास:
	वापस status;
पूर्ण

क्रमागत vxge_hw_status
vxge_update_fw_image(काष्ठा __vxge_hw_device *hldev, स्थिर u8 *fwdata, पूर्णांक size)
अणु
	u64 data0 = 0, data1 = 0, steer_ctrl = 0;
	काष्ठा __vxge_hw_भवpath *vpath;
	क्रमागत vxge_hw_status status;
	पूर्णांक ret_code, sec_code;

	vpath = &hldev->भव_paths[hldev->first_vp_id];

	/* send upgrade start command */
	status = vxge_hw_vpath_fw_api(vpath,
				      VXGE_HW_FW_UPGRADE_ACTION,
				      VXGE_HW_FW_UPGRADE_MEMO,
				      VXGE_HW_FW_UPGRADE_OFFSET_START,
				      &data0, &data1, &steer_ctrl);
	अगर (status != VXGE_HW_OK) अणु
		vxge_debug_init(VXGE_ERR, " %s: Upgrade start cmd failed",
				__func__);
		वापस status;
	पूर्ण

	/* Transfer fw image to adapter 16 bytes at a समय */
	क्रम (; size > 0; size -= VXGE_HW_FW_UPGRADE_BLK_SIZE) अणु
		steer_ctrl = 0;

		/* The next 128bits of fwdata to be loaded onto the adapter */
		data0 = *((u64 *)fwdata);
		data1 = *((u64 *)fwdata + 1);

		status = vxge_hw_vpath_fw_api(vpath,
					      VXGE_HW_FW_UPGRADE_ACTION,
					      VXGE_HW_FW_UPGRADE_MEMO,
					      VXGE_HW_FW_UPGRADE_OFFSET_SEND,
					      &data0, &data1, &steer_ctrl);
		अगर (status != VXGE_HW_OK) अणु
			vxge_debug_init(VXGE_ERR, "%s: Upgrade send failed",
					__func__);
			जाओ out;
		पूर्ण

		ret_code = VXGE_HW_UPGRADE_GET_RET_ERR_CODE(data0);
		चयन (ret_code) अणु
		हाल VXGE_HW_FW_UPGRADE_OK:
			/* All OK, send next 16 bytes. */
			अवरोध;
		हाल VXGE_FW_UPGRADE_BYTES2SKIP:
			/* skip bytes in the stream */
			fwdata += (data0 >> 8) & 0xFFFFFFFF;
			अवरोध;
		हाल VXGE_HW_FW_UPGRADE_DONE:
			जाओ out;
		हाल VXGE_HW_FW_UPGRADE_ERR:
			sec_code = VXGE_HW_UPGRADE_GET_SEC_ERR_CODE(data0);
			चयन (sec_code) अणु
			हाल VXGE_HW_FW_UPGRADE_ERR_CORRUPT_DATA_1:
			हाल VXGE_HW_FW_UPGRADE_ERR_CORRUPT_DATA_7:
				prपूर्णांकk(KERN_ERR
				       "corrupted data from .ncf file\n");
				अवरोध;
			हाल VXGE_HW_FW_UPGRADE_ERR_INV_NCF_खाता_3:
			हाल VXGE_HW_FW_UPGRADE_ERR_INV_NCF_खाता_4:
			हाल VXGE_HW_FW_UPGRADE_ERR_INV_NCF_खाता_5:
			हाल VXGE_HW_FW_UPGRADE_ERR_INV_NCF_खाता_6:
			हाल VXGE_HW_FW_UPGRADE_ERR_INV_NCF_खाता_8:
				prपूर्णांकk(KERN_ERR "invalid .ncf file\n");
				अवरोध;
			हाल VXGE_HW_FW_UPGRADE_ERR_BUFFER_OVERFLOW:
				prपूर्णांकk(KERN_ERR "buffer overflow\n");
				अवरोध;
			हाल VXGE_HW_FW_UPGRADE_ERR_FAILED_TO_FLASH:
				prपूर्णांकk(KERN_ERR "failed to flash the image\n");
				अवरोध;
			हाल VXGE_HW_FW_UPGRADE_ERR_GENERIC_ERROR_UNKNOWN:
				prपूर्णांकk(KERN_ERR
				       "generic error. Unknown error type\n");
				अवरोध;
			शेष:
				prपूर्णांकk(KERN_ERR "Unknown error of type %d\n",
				       sec_code);
				अवरोध;
			पूर्ण
			status = VXGE_HW_FAIL;
			जाओ out;
		शेष:
			prपूर्णांकk(KERN_ERR "Unknown FW error: %d\n", ret_code);
			status = VXGE_HW_FAIL;
			जाओ out;
		पूर्ण
		/* poपूर्णांक to next 16 bytes */
		fwdata += VXGE_HW_FW_UPGRADE_BLK_SIZE;
	पूर्ण
out:
	वापस status;
पूर्ण

क्रमागत vxge_hw_status
vxge_hw_vpath_eprom_img_ver_get(काष्ठा __vxge_hw_device *hldev,
				काष्ठा eprom_image *img)
अणु
	u64 data0 = 0, data1 = 0, steer_ctrl = 0;
	काष्ठा __vxge_hw_भवpath *vpath;
	क्रमागत vxge_hw_status status;
	पूर्णांक i;

	vpath = &hldev->भव_paths[hldev->first_vp_id];

	क्रम (i = 0; i < VXGE_HW_MAX_ROM_IMAGES; i++) अणु
		data0 = VXGE_HW_RTS_ACCESS_STEER_ROM_IMAGE_INDEX(i);
		data1 = steer_ctrl = 0;

		status = vxge_hw_vpath_fw_api(vpath,
			VXGE_HW_FW_API_GET_EPROM_REV,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_FW_MEMO,
			0, &data0, &data1, &steer_ctrl);
		अगर (status != VXGE_HW_OK)
			अवरोध;

		img[i].is_valid = VXGE_HW_GET_EPROM_IMAGE_VALID(data0);
		img[i].index = VXGE_HW_GET_EPROM_IMAGE_INDEX(data0);
		img[i].type = VXGE_HW_GET_EPROM_IMAGE_TYPE(data0);
		img[i].version = VXGE_HW_GET_EPROM_IMAGE_REV(data0);
	पूर्ण

	वापस status;
पूर्ण

/*
 * __vxge_hw_channel_मुक्त - Free memory allocated क्रम channel
 * This function deallocates memory from the channel and various arrays
 * in the channel
 */
अटल व्योम __vxge_hw_channel_मुक्त(काष्ठा __vxge_hw_channel *channel)
अणु
	kमुक्त(channel->work_arr);
	kमुक्त(channel->मुक्त_arr);
	kमुक्त(channel->reserve_arr);
	kमुक्त(channel->orig_arr);
	kमुक्त(channel);
पूर्ण

/*
 * __vxge_hw_channel_initialize - Initialize a channel
 * This function initializes a channel by properly setting the
 * various references
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_channel_initialize(काष्ठा __vxge_hw_channel *channel)
अणु
	u32 i;
	काष्ठा __vxge_hw_भवpath *vpath;

	vpath = channel->vph->vpath;

	अगर ((channel->reserve_arr != शून्य) && (channel->orig_arr != शून्य)) अणु
		क्रम (i = 0; i < channel->length; i++)
			channel->orig_arr[i] = channel->reserve_arr[i];
	पूर्ण

	चयन (channel->type) अणु
	हाल VXGE_HW_CHANNEL_TYPE_FIFO:
		vpath->fअगरoh = (काष्ठा __vxge_hw_fअगरo *)channel;
		channel->stats = &((काष्ठा __vxge_hw_fअगरo *)
				channel)->stats->common_stats;
		अवरोध;
	हाल VXGE_HW_CHANNEL_TYPE_RING:
		vpath->ringh = (काष्ठा __vxge_hw_ring *)channel;
		channel->stats = &((काष्ठा __vxge_hw_ring *)
				channel)->stats->common_stats;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_channel_reset - Resets a channel
 * This function resets a channel by properly setting the various references
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_channel_reset(काष्ठा __vxge_hw_channel *channel)
अणु
	u32 i;

	क्रम (i = 0; i < channel->length; i++) अणु
		अगर (channel->reserve_arr != शून्य)
			channel->reserve_arr[i] = channel->orig_arr[i];
		अगर (channel->मुक्त_arr != शून्य)
			channel->मुक्त_arr[i] = शून्य;
		अगर (channel->work_arr != शून्य)
			channel->work_arr[i] = शून्य;
	पूर्ण
	channel->मुक्त_ptr = channel->length;
	channel->reserve_ptr = channel->length;
	channel->reserve_top = 0;
	channel->post_index = 0;
	channel->compl_index = 0;

	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_device_pci_e_init
 * Initialize certain PCI/PCI-X configuration रेजिस्टरs
 * with recommended values. Save config space क्रम future hw resets.
 */
अटल व्योम __vxge_hw_device_pci_e_init(काष्ठा __vxge_hw_device *hldev)
अणु
	u16 cmd = 0;

	/* Set the PErr Repconse bit and SERR in PCI command रेजिस्टर. */
	pci_पढ़ो_config_word(hldev->pdev, PCI_COMMAND, &cmd);
	cmd |= 0x140;
	pci_ग_लिखो_config_word(hldev->pdev, PCI_COMMAND, cmd);

	pci_save_state(hldev->pdev);
पूर्ण

/* __vxge_hw_device_vpath_reset_in_prog_check - Check अगर vpath reset
 * in progress
 * This routine checks the vpath reset in progress रेजिस्टर is turned zero
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_device_vpath_reset_in_prog_check(u64 __iomem *vpath_rst_in_prog)
अणु
	क्रमागत vxge_hw_status status;
	status = __vxge_hw_device_रेजिस्टर_poll(vpath_rst_in_prog,
			VXGE_HW_VPATH_RST_IN_PROG_VPATH_RST_IN_PROG(0x1ffff),
			VXGE_HW_DEF_DEVICE_POLL_MILLIS);
	वापस status;
पूर्ण

/*
 * _hw_legacy_swapper_set - Set the swapper bits क्रम the legacy secion.
 * Set the swapper bits appropriately क्रम the lagacy section.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_legacy_swapper_set(काष्ठा vxge_hw_legacy_reg __iomem *legacy_reg)
अणु
	u64 val64;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	val64 = पढ़ोq(&legacy_reg->toc_swapper_fb);

	wmb();

	चयन (val64) अणु
	हाल VXGE_HW_SWAPPER_INITIAL_VALUE:
		वापस status;

	हाल VXGE_HW_SWAPPER_BYTE_SWAPPED_BIT_FLIPPED:
		ग_लिखोq(VXGE_HW_SWAPPER_READ_BYTE_SWAP_ENABLE,
			&legacy_reg->pअगरm_rd_swap_en);
		ग_लिखोq(VXGE_HW_SWAPPER_READ_BIT_FLAP_ENABLE,
			&legacy_reg->pअगरm_rd_flip_en);
		ग_लिखोq(VXGE_HW_SWAPPER_WRITE_BYTE_SWAP_ENABLE,
			&legacy_reg->pअगरm_wr_swap_en);
		ग_लिखोq(VXGE_HW_SWAPPER_WRITE_BIT_FLAP_ENABLE,
			&legacy_reg->pअगरm_wr_flip_en);
		अवरोध;

	हाल VXGE_HW_SWAPPER_BYTE_SWAPPED:
		ग_लिखोq(VXGE_HW_SWAPPER_READ_BYTE_SWAP_ENABLE,
			&legacy_reg->pअगरm_rd_swap_en);
		ग_लिखोq(VXGE_HW_SWAPPER_WRITE_BYTE_SWAP_ENABLE,
			&legacy_reg->pअगरm_wr_swap_en);
		अवरोध;

	हाल VXGE_HW_SWAPPER_BIT_FLIPPED:
		ग_लिखोq(VXGE_HW_SWAPPER_READ_BIT_FLAP_ENABLE,
			&legacy_reg->pअगरm_rd_flip_en);
		ग_लिखोq(VXGE_HW_SWAPPER_WRITE_BIT_FLAP_ENABLE,
			&legacy_reg->pअगरm_wr_flip_en);
		अवरोध;
	पूर्ण

	wmb();

	val64 = पढ़ोq(&legacy_reg->toc_swapper_fb);

	अगर (val64 != VXGE_HW_SWAPPER_INITIAL_VALUE)
		status = VXGE_HW_ERR_SWAPPER_CTRL;

	वापस status;
पूर्ण

/*
 * __vxge_hw_device_toc_get
 * This routine sets the swapper and पढ़ोs the toc poपूर्णांकer and वापसs the
 * memory mapped address of the toc
 */
अटल काष्ठा vxge_hw_toc_reg __iomem *
__vxge_hw_device_toc_get(व्योम __iomem *bar0)
अणु
	u64 val64;
	काष्ठा vxge_hw_toc_reg __iomem *toc = शून्य;
	क्रमागत vxge_hw_status status;

	काष्ठा vxge_hw_legacy_reg __iomem *legacy_reg =
		(काष्ठा vxge_hw_legacy_reg __iomem *)bar0;

	status = __vxge_hw_legacy_swapper_set(legacy_reg);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	val64 =	पढ़ोq(&legacy_reg->toc_first_poपूर्णांकer);
	toc = bar0 + val64;
निकास:
	वापस toc;
पूर्ण

/*
 * __vxge_hw_device_reg_addr_get
 * This routine sets the swapper and पढ़ोs the toc poपूर्णांकer and initializes the
 * रेजिस्टर location poपूर्णांकers in the device object. It रुकोs until the ric is
 * completed initializing रेजिस्टरs.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_device_reg_addr_get(काष्ठा __vxge_hw_device *hldev)
अणु
	u64 val64;
	u32 i;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	hldev->legacy_reg = hldev->bar0;

	hldev->toc_reg = __vxge_hw_device_toc_get(hldev->bar0);
	अगर (hldev->toc_reg  == शून्य) अणु
		status = VXGE_HW_FAIL;
		जाओ निकास;
	पूर्ण

	val64 = पढ़ोq(&hldev->toc_reg->toc_common_poपूर्णांकer);
	hldev->common_reg = hldev->bar0 + val64;

	val64 = पढ़ोq(&hldev->toc_reg->toc_mrpcim_poपूर्णांकer);
	hldev->mrpcim_reg = hldev->bar0 + val64;

	क्रम (i = 0; i < VXGE_HW_TITAN_SRPCIM_REG_SPACES; i++) अणु
		val64 = पढ़ोq(&hldev->toc_reg->toc_srpcim_poपूर्णांकer[i]);
		hldev->srpcim_reg[i] = hldev->bar0 + val64;
	पूर्ण

	क्रम (i = 0; i < VXGE_HW_TITAN_VPMGMT_REG_SPACES; i++) अणु
		val64 = पढ़ोq(&hldev->toc_reg->toc_vpmgmt_poपूर्णांकer[i]);
		hldev->vpmgmt_reg[i] = hldev->bar0 + val64;
	पूर्ण

	क्रम (i = 0; i < VXGE_HW_TITAN_VPATH_REG_SPACES; i++) अणु
		val64 = पढ़ोq(&hldev->toc_reg->toc_vpath_poपूर्णांकer[i]);
		hldev->vpath_reg[i] = hldev->bar0 + val64;
	पूर्ण

	val64 = पढ़ोq(&hldev->toc_reg->toc_kdfc);

	चयन (VXGE_HW_TOC_GET_KDFC_INITIAL_BIR(val64)) अणु
	हाल 0:
		hldev->kdfc = hldev->bar0 + VXGE_HW_TOC_GET_KDFC_INITIAL_OFFSET(val64) ;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	status = __vxge_hw_device_vpath_reset_in_prog_check(
			(u64 __iomem *)&hldev->common_reg->vpath_rst_in_prog);
निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_device_access_rights_get: Get Access Rights of the driver
 * This routine वापसs the Access Rights of the driver
 */
अटल u32
__vxge_hw_device_access_rights_get(u32 host_type, u32 func_id)
अणु
	u32 access_rights = VXGE_HW_DEVICE_ACCESS_RIGHT_VPATH;

	चयन (host_type) अणु
	हाल VXGE_HW_NO_MR_NO_SR_NORMAL_FUNCTION:
		अगर (func_id == 0) अणु
			access_rights |= VXGE_HW_DEVICE_ACCESS_RIGHT_MRPCIM |
					VXGE_HW_DEVICE_ACCESS_RIGHT_SRPCIM;
		पूर्ण
		अवरोध;
	हाल VXGE_HW_MR_NO_SR_VH0_BASE_FUNCTION:
		access_rights |= VXGE_HW_DEVICE_ACCESS_RIGHT_MRPCIM |
				VXGE_HW_DEVICE_ACCESS_RIGHT_SRPCIM;
		अवरोध;
	हाल VXGE_HW_NO_MR_SR_VH0_FUNCTION0:
		access_rights |= VXGE_HW_DEVICE_ACCESS_RIGHT_MRPCIM |
				VXGE_HW_DEVICE_ACCESS_RIGHT_SRPCIM;
		अवरोध;
	हाल VXGE_HW_NO_MR_SR_VH0_VIRTUAL_FUNCTION:
	हाल VXGE_HW_SR_VH_VIRTUAL_FUNCTION:
	हाल VXGE_HW_MR_SR_VH0_INVALID_CONFIG:
		अवरोध;
	हाल VXGE_HW_SR_VH_FUNCTION0:
	हाल VXGE_HW_VH_NORMAL_FUNCTION:
		access_rights |= VXGE_HW_DEVICE_ACCESS_RIGHT_SRPCIM;
		अवरोध;
	पूर्ण

	वापस access_rights;
पूर्ण
/*
 * __vxge_hw_device_is_privilaged
 * This routine checks अगर the device function is privilaged or not
 */

क्रमागत vxge_hw_status
__vxge_hw_device_is_privilaged(u32 host_type, u32 func_id)
अणु
	अगर (__vxge_hw_device_access_rights_get(host_type,
		func_id) &
		VXGE_HW_DEVICE_ACCESS_RIGHT_MRPCIM)
		वापस VXGE_HW_OK;
	अन्यथा
		वापस VXGE_HW_ERR_PRIVILEGED_OPERATION;
पूर्ण

/*
 * __vxge_hw_vpath_func_id_get - Get the function id of the vpath.
 * Returns the function number of the vpath.
 */
अटल u32
__vxge_hw_vpath_func_id_get(काष्ठा vxge_hw_vpmgmt_reg __iomem *vpmgmt_reg)
अणु
	u64 val64;

	val64 = पढ़ोq(&vpmgmt_reg->vpath_to_func_map_cfg1);

	वापस
	 (u32)VXGE_HW_VPATH_TO_FUNC_MAP_CFG1_GET_VPATH_TO_FUNC_MAP_CFG1(val64);
पूर्ण

/*
 * __vxge_hw_device_host_info_get
 * This routine वापसs the host type assignments
 */
अटल व्योम __vxge_hw_device_host_info_get(काष्ठा __vxge_hw_device *hldev)
अणु
	u64 val64;
	u32 i;

	val64 = पढ़ोq(&hldev->common_reg->host_type_assignments);

	hldev->host_type =
	   (u32)VXGE_HW_HOST_TYPE_ASSIGNMENTS_GET_HOST_TYPE_ASSIGNMENTS(val64);

	hldev->vpath_assignments = पढ़ोq(&hldev->common_reg->vpath_assignments);

	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
		अगर (!(hldev->vpath_assignments & vxge_mBIT(i)))
			जारी;

		hldev->func_id =
			__vxge_hw_vpath_func_id_get(hldev->vpmgmt_reg[i]);

		hldev->access_rights = __vxge_hw_device_access_rights_get(
			hldev->host_type, hldev->func_id);

		hldev->भव_paths[i].vp_खोलो = VXGE_HW_VP_NOT_OPEN;
		hldev->भव_paths[i].vp_reg = hldev->vpath_reg[i];

		hldev->first_vp_id = i;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * __vxge_hw_verअगरy_pci_e_info - Validate the pci-e link parameters such as
 * link width and संकेतling rate.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_verअगरy_pci_e_info(काष्ठा __vxge_hw_device *hldev)
अणु
	काष्ठा pci_dev *dev = hldev->pdev;
	u16 lnk;

	/* Get the negotiated link width and speed from PCI config space */
	pcie_capability_पढ़ो_word(dev, PCI_EXP_LNKSTA, &lnk);

	अगर ((lnk & PCI_EXP_LNKSTA_CLS) != 1)
		वापस VXGE_HW_ERR_INVALID_PCI_INFO;

	चयन ((lnk & PCI_EXP_LNKSTA_NLW) >> 4) अणु
	हाल PCIE_LNK_WIDTH_RESRV:
	हाल PCIE_LNK_X1:
	हाल PCIE_LNK_X2:
	हाल PCIE_LNK_X4:
	हाल PCIE_LNK_X8:
		अवरोध;
	शेष:
		वापस VXGE_HW_ERR_INVALID_PCI_INFO;
	पूर्ण

	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_device_initialize
 * Initialize Titan-V hardware.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_device_initialize(काष्ठा __vxge_hw_device *hldev)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर (VXGE_HW_OK == __vxge_hw_device_is_privilaged(hldev->host_type,
				hldev->func_id)) अणु
		/* Validate the pci-e link width and speed */
		status = __vxge_hw_verअगरy_pci_e_info(hldev);
		अगर (status != VXGE_HW_OK)
			जाओ निकास;
	पूर्ण

निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_vpath_fw_ver_get - Get the fw version
 * Returns FW Version
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_fw_ver_get(काष्ठा __vxge_hw_भवpath *vpath,
			   काष्ठा vxge_hw_device_hw_info *hw_info)
अणु
	काष्ठा vxge_hw_device_version *fw_version = &hw_info->fw_version;
	काष्ठा vxge_hw_device_date *fw_date = &hw_info->fw_date;
	काष्ठा vxge_hw_device_version *flash_version = &hw_info->flash_version;
	काष्ठा vxge_hw_device_date *flash_date = &hw_info->flash_date;
	u64 data0 = 0, data1 = 0, steer_ctrl = 0;
	क्रमागत vxge_hw_status status;

	status = vxge_hw_vpath_fw_api(vpath,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_READ_ENTRY,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_FW_MEMO,
			0, &data0, &data1, &steer_ctrl);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	fw_date->day =
	    (u32) VXGE_HW_RTS_ACCESS_STEER_DATA0_GET_FW_VER_DAY(data0);
	fw_date->month =
	    (u32) VXGE_HW_RTS_ACCESS_STEER_DATA0_GET_FW_VER_MONTH(data0);
	fw_date->year =
	    (u32) VXGE_HW_RTS_ACCESS_STEER_DATA0_GET_FW_VER_YEAR(data0);

	snम_लिखो(fw_date->date, VXGE_HW_FW_STRLEN, "%2.2d/%2.2d/%4.4d",
		 fw_date->month, fw_date->day, fw_date->year);

	fw_version->major =
	    (u32) VXGE_HW_RTS_ACCESS_STEER_DATA0_GET_FW_VER_MAJOR(data0);
	fw_version->minor =
	    (u32) VXGE_HW_RTS_ACCESS_STEER_DATA0_GET_FW_VER_MINOR(data0);
	fw_version->build =
	    (u32) VXGE_HW_RTS_ACCESS_STEER_DATA0_GET_FW_VER_BUILD(data0);

	snम_लिखो(fw_version->version, VXGE_HW_FW_STRLEN, "%d.%d.%d",
		 fw_version->major, fw_version->minor, fw_version->build);

	flash_date->day =
	    (u32) VXGE_HW_RTS_ACCESS_STEER_DATA1_GET_FLASH_VER_DAY(data1);
	flash_date->month =
	    (u32) VXGE_HW_RTS_ACCESS_STEER_DATA1_GET_FLASH_VER_MONTH(data1);
	flash_date->year =
	    (u32) VXGE_HW_RTS_ACCESS_STEER_DATA1_GET_FLASH_VER_YEAR(data1);

	snम_लिखो(flash_date->date, VXGE_HW_FW_STRLEN, "%2.2d/%2.2d/%4.4d",
		 flash_date->month, flash_date->day, flash_date->year);

	flash_version->major =
	    (u32) VXGE_HW_RTS_ACCESS_STEER_DATA1_GET_FLASH_VER_MAJOR(data1);
	flash_version->minor =
	    (u32) VXGE_HW_RTS_ACCESS_STEER_DATA1_GET_FLASH_VER_MINOR(data1);
	flash_version->build =
	    (u32) VXGE_HW_RTS_ACCESS_STEER_DATA1_GET_FLASH_VER_BUILD(data1);

	snम_लिखो(flash_version->version, VXGE_HW_FW_STRLEN, "%d.%d.%d",
		 flash_version->major, flash_version->minor,
		 flash_version->build);

निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_vpath_card_info_get - Get the serial numbers,
 * part number and product description.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_card_info_get(काष्ठा __vxge_hw_भवpath *vpath,
			      काष्ठा vxge_hw_device_hw_info *hw_info)
अणु
	__be64 *serial_number = (व्योम *)hw_info->serial_number;
	__be64 *product_desc = (व्योम *)hw_info->product_desc;
	__be64 *part_number = (व्योम *)hw_info->part_number;
	क्रमागत vxge_hw_status status;
	u64 data0, data1 = 0, steer_ctrl = 0;
	u32 i, j = 0;

	data0 = VXGE_HW_RTS_ACCESS_STEER_DATA0_MEMO_ITEM_SERIAL_NUMBER;

	status = vxge_hw_vpath_fw_api(vpath,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_READ_MEMO_ENTRY,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_FW_MEMO,
			0, &data0, &data1, &steer_ctrl);
	अगर (status != VXGE_HW_OK)
		वापस status;

	serial_number[0] = cpu_to_be64(data0);
	serial_number[1] = cpu_to_be64(data1);

	data0 = VXGE_HW_RTS_ACCESS_STEER_DATA0_MEMO_ITEM_PART_NUMBER;
	data1 = steer_ctrl = 0;

	status = vxge_hw_vpath_fw_api(vpath,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_READ_MEMO_ENTRY,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_FW_MEMO,
			0, &data0, &data1, &steer_ctrl);
	अगर (status != VXGE_HW_OK)
		वापस status;

	part_number[0] = cpu_to_be64(data0);
	part_number[1] = cpu_to_be64(data1);

	क्रम (i = VXGE_HW_RTS_ACCESS_STEER_DATA0_MEMO_ITEM_DESC_0;
	     i <= VXGE_HW_RTS_ACCESS_STEER_DATA0_MEMO_ITEM_DESC_3; i++) अणु
		data0 = i;
		data1 = steer_ctrl = 0;

		status = vxge_hw_vpath_fw_api(vpath,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_READ_MEMO_ENTRY,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_FW_MEMO,
			0, &data0, &data1, &steer_ctrl);
		अगर (status != VXGE_HW_OK)
			वापस status;

		product_desc[j++] = cpu_to_be64(data0);
		product_desc[j++] = cpu_to_be64(data1);
	पूर्ण

	वापस status;
पूर्ण

/*
 * __vxge_hw_vpath_pci_func_mode_get - Get the pci mode
 * Returns pci function mode
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_pci_func_mode_get(काष्ठा __vxge_hw_भवpath *vpath,
				  काष्ठा vxge_hw_device_hw_info *hw_info)
अणु
	u64 data0, data1 = 0, steer_ctrl = 0;
	क्रमागत vxge_hw_status status;

	data0 = 0;

	status = vxge_hw_vpath_fw_api(vpath,
			VXGE_HW_FW_API_GET_FUNC_MODE,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_FW_MEMO,
			0, &data0, &data1, &steer_ctrl);
	अगर (status != VXGE_HW_OK)
		वापस status;

	hw_info->function_mode = VXGE_HW_GET_FUNC_MODE_VAL(data0);
	वापस status;
पूर्ण

/*
 * __vxge_hw_vpath_addr_get - Get the hw address entry क्रम this vpath
 *               from MAC address table.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_addr_get(काष्ठा __vxge_hw_भवpath *vpath,
			 u8 *macaddr, u8 *macaddr_mask)
अणु
	u64 action = VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_LIST_FIRST_ENTRY,
	    data0 = 0, data1 = 0, steer_ctrl = 0;
	क्रमागत vxge_hw_status status;
	पूर्णांक i;

	करो अणु
		status = vxge_hw_vpath_fw_api(vpath, action,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_DA,
			0, &data0, &data1, &steer_ctrl);
		अगर (status != VXGE_HW_OK)
			जाओ निकास;

		data0 = VXGE_HW_RTS_ACCESS_STEER_DATA0_GET_DA_MAC_ADDR(data0);
		data1 = VXGE_HW_RTS_ACCESS_STEER_DATA1_GET_DA_MAC_ADDR_MASK(
									data1);

		क्रम (i = ETH_ALEN; i > 0; i--) अणु
			macaddr[i - 1] = (u8) (data0 & 0xFF);
			data0 >>= 8;

			macaddr_mask[i - 1] = (u8) (data1 & 0xFF);
			data1 >>= 8;
		पूर्ण

		action = VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_LIST_NEXT_ENTRY;
		data0 = 0, data1 = 0, steer_ctrl = 0;

	पूर्ण जबतक (!is_valid_ether_addr(macaddr));
निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_device_hw_info_get - Get the hw inक्रमmation
 * @bar0: the bar
 * @hw_info: the hw_info काष्ठा
 *
 * Returns the vpath mask that has the bits set क्रम each vpath allocated
 * क्रम the driver, FW version inक्रमmation, and the first mac address क्रम
 * each vpath
 */
क्रमागत vxge_hw_status
vxge_hw_device_hw_info_get(व्योम __iomem *bar0,
			   काष्ठा vxge_hw_device_hw_info *hw_info)
अणु
	u32 i;
	u64 val64;
	काष्ठा vxge_hw_toc_reg __iomem *toc;
	काष्ठा vxge_hw_mrpcim_reg __iomem *mrpcim_reg;
	काष्ठा vxge_hw_common_reg __iomem *common_reg;
	काष्ठा vxge_hw_vpmgmt_reg __iomem *vpmgmt_reg;
	क्रमागत vxge_hw_status status;
	काष्ठा __vxge_hw_भवpath vpath;

	स_रखो(hw_info, 0, माप(काष्ठा vxge_hw_device_hw_info));

	toc = __vxge_hw_device_toc_get(bar0);
	अगर (toc == शून्य) अणु
		status = VXGE_HW_ERR_CRITICAL;
		जाओ निकास;
	पूर्ण

	val64 = पढ़ोq(&toc->toc_common_poपूर्णांकer);
	common_reg = bar0 + val64;

	status = __vxge_hw_device_vpath_reset_in_prog_check(
		(u64 __iomem *)&common_reg->vpath_rst_in_prog);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	hw_info->vpath_mask = पढ़ोq(&common_reg->vpath_assignments);

	val64 = पढ़ोq(&common_reg->host_type_assignments);

	hw_info->host_type =
	   (u32)VXGE_HW_HOST_TYPE_ASSIGNMENTS_GET_HOST_TYPE_ASSIGNMENTS(val64);

	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
		अगर (!((hw_info->vpath_mask) & vxge_mBIT(i)))
			जारी;

		val64 = पढ़ोq(&toc->toc_vpmgmt_poपूर्णांकer[i]);

		vpmgmt_reg = bar0 + val64;

		hw_info->func_id = __vxge_hw_vpath_func_id_get(vpmgmt_reg);
		अगर (__vxge_hw_device_access_rights_get(hw_info->host_type,
			hw_info->func_id) &
			VXGE_HW_DEVICE_ACCESS_RIGHT_MRPCIM) अणु

			val64 = पढ़ोq(&toc->toc_mrpcim_poपूर्णांकer);

			mrpcim_reg = bar0 + val64;

			ग_लिखोq(0, &mrpcim_reg->xgmac_gen_fw_memo_mask);
			wmb();
		पूर्ण

		val64 = पढ़ोq(&toc->toc_vpath_poपूर्णांकer[i]);

		spin_lock_init(&vpath.lock);
		vpath.vp_reg = bar0 + val64;
		vpath.vp_खोलो = VXGE_HW_VP_NOT_OPEN;

		status = __vxge_hw_vpath_pci_func_mode_get(&vpath, hw_info);
		अगर (status != VXGE_HW_OK)
			जाओ निकास;

		status = __vxge_hw_vpath_fw_ver_get(&vpath, hw_info);
		अगर (status != VXGE_HW_OK)
			जाओ निकास;

		status = __vxge_hw_vpath_card_info_get(&vpath, hw_info);
		अगर (status != VXGE_HW_OK)
			जाओ निकास;

		अवरोध;
	पूर्ण

	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
		अगर (!((hw_info->vpath_mask) & vxge_mBIT(i)))
			जारी;

		val64 = पढ़ोq(&toc->toc_vpath_poपूर्णांकer[i]);
		vpath.vp_reg = bar0 + val64;
		vpath.vp_खोलो = VXGE_HW_VP_NOT_OPEN;

		status =  __vxge_hw_vpath_addr_get(&vpath,
				hw_info->mac_addrs[i],
				hw_info->mac_addr_masks[i]);
		अगर (status != VXGE_HW_OK)
			जाओ निकास;
	पूर्ण
निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_blockpool_destroy - Deallocates the block pool
 */
अटल व्योम __vxge_hw_blockpool_destroy(काष्ठा __vxge_hw_blockpool *blockpool)
अणु
	काष्ठा __vxge_hw_device *hldev;
	काष्ठा list_head *p, *n;

	अगर (!blockpool)
		वापस;

	hldev = blockpool->hldev;

	list_क्रम_each_safe(p, n, &blockpool->मुक्त_block_list) अणु
		dma_unmap_single(&hldev->pdev->dev,
				 ((काष्ठा __vxge_hw_blockpool_entry *)p)->dma_addr,
				 ((काष्ठा __vxge_hw_blockpool_entry *)p)->length,
				 DMA_BIसूचीECTIONAL);

		vxge_os_dma_मुक्त(hldev->pdev,
			((काष्ठा __vxge_hw_blockpool_entry *)p)->memblock,
			&((काष्ठा __vxge_hw_blockpool_entry *)p)->acc_handle);

		list_del(&((काष्ठा __vxge_hw_blockpool_entry *)p)->item);
		kमुक्त(p);
		blockpool->pool_size--;
	पूर्ण

	list_क्रम_each_safe(p, n, &blockpool->मुक्त_entry_list) अणु
		list_del(&((काष्ठा __vxge_hw_blockpool_entry *)p)->item);
		kमुक्त(p);
	पूर्ण

	वापस;
पूर्ण

/*
 * __vxge_hw_blockpool_create - Create block pool
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_blockpool_create(काष्ठा __vxge_hw_device *hldev,
			   काष्ठा __vxge_hw_blockpool *blockpool,
			   u32 pool_size,
			   u32 pool_max)
अणु
	u32 i;
	काष्ठा __vxge_hw_blockpool_entry *entry = शून्य;
	व्योम *memblock;
	dma_addr_t dma_addr;
	काष्ठा pci_dev *dma_handle;
	काष्ठा pci_dev *acc_handle;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर (blockpool == शून्य) अणु
		status = VXGE_HW_FAIL;
		जाओ blockpool_create_निकास;
	पूर्ण

	blockpool->hldev = hldev;
	blockpool->block_size = VXGE_HW_BLOCK_SIZE;
	blockpool->pool_size = 0;
	blockpool->pool_max = pool_max;
	blockpool->req_out = 0;

	INIT_LIST_HEAD(&blockpool->मुक्त_block_list);
	INIT_LIST_HEAD(&blockpool->मुक्त_entry_list);

	क्रम (i = 0; i < pool_size + pool_max; i++) अणु
		entry = kzalloc(माप(काष्ठा __vxge_hw_blockpool_entry),
				GFP_KERNEL);
		अगर (entry == शून्य) अणु
			__vxge_hw_blockpool_destroy(blockpool);
			status = VXGE_HW_ERR_OUT_OF_MEMORY;
			जाओ blockpool_create_निकास;
		पूर्ण
		list_add(&entry->item, &blockpool->मुक्त_entry_list);
	पूर्ण

	क्रम (i = 0; i < pool_size; i++) अणु
		memblock = vxge_os_dma_दो_स्मृति(
				hldev->pdev,
				VXGE_HW_BLOCK_SIZE,
				&dma_handle,
				&acc_handle);
		अगर (memblock == शून्य) अणु
			__vxge_hw_blockpool_destroy(blockpool);
			status = VXGE_HW_ERR_OUT_OF_MEMORY;
			जाओ blockpool_create_निकास;
		पूर्ण

		dma_addr = dma_map_single(&hldev->pdev->dev, memblock,
					  VXGE_HW_BLOCK_SIZE,
					  DMA_BIसूचीECTIONAL);
		अगर (unlikely(dma_mapping_error(&hldev->pdev->dev, dma_addr))) अणु
			vxge_os_dma_मुक्त(hldev->pdev, memblock, &acc_handle);
			__vxge_hw_blockpool_destroy(blockpool);
			status = VXGE_HW_ERR_OUT_OF_MEMORY;
			जाओ blockpool_create_निकास;
		पूर्ण

		अगर (!list_empty(&blockpool->मुक्त_entry_list))
			entry = (काष्ठा __vxge_hw_blockpool_entry *)
				list_first_entry(&blockpool->मुक्त_entry_list,
					काष्ठा __vxge_hw_blockpool_entry,
					item);

		अगर (entry == शून्य)
			entry =
			    kzalloc(माप(काष्ठा __vxge_hw_blockpool_entry),
					GFP_KERNEL);
		अगर (entry != शून्य) अणु
			list_del(&entry->item);
			entry->length = VXGE_HW_BLOCK_SIZE;
			entry->memblock = memblock;
			entry->dma_addr = dma_addr;
			entry->acc_handle = acc_handle;
			entry->dma_handle = dma_handle;
			list_add(&entry->item,
					  &blockpool->मुक्त_block_list);
			blockpool->pool_size++;
		पूर्ण अन्यथा अणु
			__vxge_hw_blockpool_destroy(blockpool);
			status = VXGE_HW_ERR_OUT_OF_MEMORY;
			जाओ blockpool_create_निकास;
		पूर्ण
	पूर्ण

blockpool_create_निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_device_fअगरo_config_check - Check fअगरo configuration.
 * Check the fअगरo configuration
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_device_fअगरo_config_check(काष्ठा vxge_hw_fअगरo_config *fअगरo_config)
अणु
	अगर ((fअगरo_config->fअगरo_blocks < VXGE_HW_MIN_FIFO_BLOCKS) ||
	    (fअगरo_config->fअगरo_blocks > VXGE_HW_MAX_FIFO_BLOCKS))
		वापस VXGE_HW_BADCFG_FIFO_BLOCKS;

	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_device_vpath_config_check - Check vpath configuration.
 * Check the vpath configuration
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_device_vpath_config_check(काष्ठा vxge_hw_vp_config *vp_config)
अणु
	क्रमागत vxge_hw_status status;

	अगर ((vp_config->min_bandwidth < VXGE_HW_VPATH_BANDWIDTH_MIN) ||
	    (vp_config->min_bandwidth >	VXGE_HW_VPATH_BANDWIDTH_MAX))
		वापस VXGE_HW_BADCFG_VPATH_MIN_BANDWIDTH;

	status = __vxge_hw_device_fअगरo_config_check(&vp_config->fअगरo);
	अगर (status != VXGE_HW_OK)
		वापस status;

	अगर ((vp_config->mtu != VXGE_HW_VPATH_USE_FLASH_DEFAULT_INITIAL_MTU) &&
		((vp_config->mtu < VXGE_HW_VPATH_MIN_INITIAL_MTU) ||
		(vp_config->mtu > VXGE_HW_VPATH_MAX_INITIAL_MTU)))
		वापस VXGE_HW_BADCFG_VPATH_MTU;

	अगर ((vp_config->rpa_strip_vlan_tag !=
		VXGE_HW_VPATH_RPA_STRIP_VLAN_TAG_USE_FLASH_DEFAULT) &&
		(vp_config->rpa_strip_vlan_tag !=
		VXGE_HW_VPATH_RPA_STRIP_VLAN_TAG_ENABLE) &&
		(vp_config->rpa_strip_vlan_tag !=
		VXGE_HW_VPATH_RPA_STRIP_VLAN_TAG_DISABLE))
		वापस VXGE_HW_BADCFG_VPATH_RPA_STRIP_VLAN_TAG;

	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_device_config_check - Check device configuration.
 * Check the device configuration
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_device_config_check(काष्ठा vxge_hw_device_config *new_config)
अणु
	u32 i;
	क्रमागत vxge_hw_status status;

	अगर ((new_config->पूर्णांकr_mode != VXGE_HW_INTR_MODE_IRQLINE) &&
	    (new_config->पूर्णांकr_mode != VXGE_HW_INTR_MODE_MSIX) &&
	    (new_config->पूर्णांकr_mode != VXGE_HW_INTR_MODE_MSIX_ONE_SHOT) &&
	    (new_config->पूर्णांकr_mode != VXGE_HW_INTR_MODE_DEF))
		वापस VXGE_HW_BADCFG_INTR_MODE;

	अगर ((new_config->rts_mac_en != VXGE_HW_RTS_MAC_DISABLE) &&
	    (new_config->rts_mac_en != VXGE_HW_RTS_MAC_ENABLE))
		वापस VXGE_HW_BADCFG_RTS_MAC_EN;

	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
		status = __vxge_hw_device_vpath_config_check(
				&new_config->vp_config[i]);
		अगर (status != VXGE_HW_OK)
			वापस status;
	पूर्ण

	वापस VXGE_HW_OK;
पूर्ण

/*
 * vxge_hw_device_initialize - Initialize Titan device.
 * Initialize Titan device. Note that all the arguments of this खुला API
 * are 'IN', including @hldev. Driver cooperates with
 * OS to find new Titan device, locate its PCI and memory spaces.
 *
 * When करोne, the driver allocates माप(काष्ठा __vxge_hw_device) bytes क्रम HW
 * to enable the latter to perक्रमm Titan hardware initialization.
 */
क्रमागत vxge_hw_status
vxge_hw_device_initialize(
	काष्ठा __vxge_hw_device **devh,
	काष्ठा vxge_hw_device_attr *attr,
	काष्ठा vxge_hw_device_config *device_config)
अणु
	u32 i;
	u32 nblocks = 0;
	काष्ठा __vxge_hw_device *hldev = शून्य;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	status = __vxge_hw_device_config_check(device_config);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	hldev = vzalloc(माप(काष्ठा __vxge_hw_device));
	अगर (hldev == शून्य) अणु
		status = VXGE_HW_ERR_OUT_OF_MEMORY;
		जाओ निकास;
	पूर्ण

	hldev->magic = VXGE_HW_DEVICE_MAGIC;

	vxge_hw_device_debug_set(hldev, VXGE_ERR, VXGE_COMPONENT_ALL);

	/* apply config */
	स_नकल(&hldev->config, device_config,
		माप(काष्ठा vxge_hw_device_config));

	hldev->bar0 = attr->bar0;
	hldev->pdev = attr->pdev;

	hldev->uld_callbacks = attr->uld_callbacks;

	__vxge_hw_device_pci_e_init(hldev);

	status = __vxge_hw_device_reg_addr_get(hldev);
	अगर (status != VXGE_HW_OK) अणु
		vमुक्त(hldev);
		जाओ निकास;
	पूर्ण

	__vxge_hw_device_host_info_get(hldev);

	/* Incrementing क्रम stats blocks */
	nblocks++;

	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
		अगर (!(hldev->vpath_assignments & vxge_mBIT(i)))
			जारी;

		अगर (device_config->vp_config[i].ring.enable ==
			VXGE_HW_RING_ENABLE)
			nblocks += device_config->vp_config[i].ring.ring_blocks;

		अगर (device_config->vp_config[i].fअगरo.enable ==
			VXGE_HW_FIFO_ENABLE)
			nblocks += device_config->vp_config[i].fअगरo.fअगरo_blocks;
		nblocks++;
	पूर्ण

	अगर (__vxge_hw_blockpool_create(hldev,
		&hldev->block_pool,
		device_config->dma_blockpool_initial + nblocks,
		device_config->dma_blockpool_max + nblocks) != VXGE_HW_OK) अणु

		vxge_hw_device_terminate(hldev);
		status = VXGE_HW_ERR_OUT_OF_MEMORY;
		जाओ निकास;
	पूर्ण

	status = __vxge_hw_device_initialize(hldev);
	अगर (status != VXGE_HW_OK) अणु
		vxge_hw_device_terminate(hldev);
		जाओ निकास;
	पूर्ण

	*devh = hldev;
निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_device_terminate - Terminate Titan device.
 * Terminate HW device.
 */
व्योम
vxge_hw_device_terminate(काष्ठा __vxge_hw_device *hldev)
अणु
	vxge_निश्चित(hldev->magic == VXGE_HW_DEVICE_MAGIC);

	hldev->magic = VXGE_HW_DEVICE_DEAD;
	__vxge_hw_blockpool_destroy(&hldev->block_pool);
	vमुक्त(hldev);
पूर्ण

/*
 * __vxge_hw_vpath_stats_access - Get the statistics from the given location
 *                           and offset and perक्रमm an operation
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_stats_access(काष्ठा __vxge_hw_भवpath *vpath,
			     u32 operation, u32 offset, u64 *stat)
अणु
	u64 val64;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा vxge_hw_vpath_reg __iomem *vp_reg;

	अगर (vpath->vp_खोलो == VXGE_HW_VP_NOT_OPEN) अणु
		status = VXGE_HW_ERR_VPATH_NOT_OPEN;
		जाओ vpath_stats_access_निकास;
	पूर्ण

	vp_reg = vpath->vp_reg;

	val64 =  VXGE_HW_XMAC_STATS_ACCESS_CMD_OP(operation) |
		 VXGE_HW_XMAC_STATS_ACCESS_CMD_STROBE |
		 VXGE_HW_XMAC_STATS_ACCESS_CMD_OFFSET_SEL(offset);

	status = __vxge_hw_pio_mem_ग_लिखो64(val64,
				&vp_reg->xmac_stats_access_cmd,
				VXGE_HW_XMAC_STATS_ACCESS_CMD_STROBE,
				vpath->hldev->config.device_poll_millis);
	अगर ((status == VXGE_HW_OK) && (operation == VXGE_HW_STATS_OP_READ))
		*stat = पढ़ोq(&vp_reg->xmac_stats_access_data);
	अन्यथा
		*stat = 0;

vpath_stats_access_निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_vpath_xmac_tx_stats_get - Get the TX Statistics of a vpath
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_xmac_tx_stats_get(काष्ठा __vxge_hw_भवpath *vpath,
			काष्ठा vxge_hw_xmac_vpath_tx_stats *vpath_tx_stats)
अणु
	u64 *val64;
	पूर्णांक i;
	u32 offset = VXGE_HW_STATS_VPATH_TX_OFFSET;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	val64 = (u64 *)vpath_tx_stats;

	अगर (vpath->vp_खोलो == VXGE_HW_VP_NOT_OPEN) अणु
		status = VXGE_HW_ERR_VPATH_NOT_OPEN;
		जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < माप(काष्ठा vxge_hw_xmac_vpath_tx_stats) / 8; i++) अणु
		status = __vxge_hw_vpath_stats_access(vpath,
					VXGE_HW_STATS_OP_READ,
					offset, val64);
		अगर (status != VXGE_HW_OK)
			जाओ निकास;
		offset++;
		val64++;
	पूर्ण
निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_vpath_xmac_rx_stats_get - Get the RX Statistics of a vpath
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_xmac_rx_stats_get(काष्ठा __vxge_hw_भवpath *vpath,
			काष्ठा vxge_hw_xmac_vpath_rx_stats *vpath_rx_stats)
अणु
	u64 *val64;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	पूर्णांक i;
	u32 offset = VXGE_HW_STATS_VPATH_RX_OFFSET;
	val64 = (u64 *) vpath_rx_stats;

	अगर (vpath->vp_खोलो == VXGE_HW_VP_NOT_OPEN) अणु
		status = VXGE_HW_ERR_VPATH_NOT_OPEN;
		जाओ निकास;
	पूर्ण
	क्रम (i = 0; i < माप(काष्ठा vxge_hw_xmac_vpath_rx_stats) / 8; i++) अणु
		status = __vxge_hw_vpath_stats_access(vpath,
					VXGE_HW_STATS_OP_READ,
					offset >> 3, val64);
		अगर (status != VXGE_HW_OK)
			जाओ निकास;

		offset += 8;
		val64++;
	पूर्ण
निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_vpath_stats_get - Get the vpath hw statistics.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_stats_get(काष्ठा __vxge_hw_भवpath *vpath,
			  काष्ठा vxge_hw_vpath_stats_hw_info *hw_stats)
अणु
	u64 val64;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा vxge_hw_vpath_reg __iomem *vp_reg;

	अगर (vpath->vp_खोलो == VXGE_HW_VP_NOT_OPEN) अणु
		status = VXGE_HW_ERR_VPATH_NOT_OPEN;
		जाओ निकास;
	पूर्ण
	vp_reg = vpath->vp_reg;

	val64 = पढ़ोq(&vp_reg->vpath_debug_stats0);
	hw_stats->ini_num_mwr_sent =
		(u32)VXGE_HW_VPATH_DEBUG_STATS0_GET_INI_NUM_MWR_SENT(val64);

	val64 = पढ़ोq(&vp_reg->vpath_debug_stats1);
	hw_stats->ini_num_mrd_sent =
		(u32)VXGE_HW_VPATH_DEBUG_STATS1_GET_INI_NUM_MRD_SENT(val64);

	val64 = पढ़ोq(&vp_reg->vpath_debug_stats2);
	hw_stats->ini_num_cpl_rcvd =
		(u32)VXGE_HW_VPATH_DEBUG_STATS2_GET_INI_NUM_CPL_RCVD(val64);

	val64 = पढ़ोq(&vp_reg->vpath_debug_stats3);
	hw_stats->ini_num_mwr_byte_sent =
		VXGE_HW_VPATH_DEBUG_STATS3_GET_INI_NUM_MWR_BYTE_SENT(val64);

	val64 = पढ़ोq(&vp_reg->vpath_debug_stats4);
	hw_stats->ini_num_cpl_byte_rcvd =
		VXGE_HW_VPATH_DEBUG_STATS4_GET_INI_NUM_CPL_BYTE_RCVD(val64);

	val64 = पढ़ोq(&vp_reg->vpath_debug_stats5);
	hw_stats->wrcrdtarb_xoff =
		(u32)VXGE_HW_VPATH_DEBUG_STATS5_GET_WRCRDTARB_XOFF(val64);

	val64 = पढ़ोq(&vp_reg->vpath_debug_stats6);
	hw_stats->rdcrdtarb_xoff =
		(u32)VXGE_HW_VPATH_DEBUG_STATS6_GET_RDCRDTARB_XOFF(val64);

	val64 = पढ़ोq(&vp_reg->vpath_genstats_count01);
	hw_stats->vpath_genstats_count0 =
	(u32)VXGE_HW_VPATH_GENSTATS_COUNT01_GET_PPIF_VPATH_GENSTATS_COUNT0(
		val64);

	val64 = पढ़ोq(&vp_reg->vpath_genstats_count01);
	hw_stats->vpath_genstats_count1 =
	(u32)VXGE_HW_VPATH_GENSTATS_COUNT01_GET_PPIF_VPATH_GENSTATS_COUNT1(
		val64);

	val64 = पढ़ोq(&vp_reg->vpath_genstats_count23);
	hw_stats->vpath_genstats_count2 =
	(u32)VXGE_HW_VPATH_GENSTATS_COUNT23_GET_PPIF_VPATH_GENSTATS_COUNT2(
		val64);

	val64 = पढ़ोq(&vp_reg->vpath_genstats_count01);
	hw_stats->vpath_genstats_count3 =
	(u32)VXGE_HW_VPATH_GENSTATS_COUNT23_GET_PPIF_VPATH_GENSTATS_COUNT3(
		val64);

	val64 = पढ़ोq(&vp_reg->vpath_genstats_count4);
	hw_stats->vpath_genstats_count4 =
	(u32)VXGE_HW_VPATH_GENSTATS_COUNT4_GET_PPIF_VPATH_GENSTATS_COUNT4(
		val64);

	val64 = पढ़ोq(&vp_reg->vpath_genstats_count5);
	hw_stats->vpath_genstats_count5 =
	(u32)VXGE_HW_VPATH_GENSTATS_COUNT5_GET_PPIF_VPATH_GENSTATS_COUNT5(
		val64);

	status = __vxge_hw_vpath_xmac_tx_stats_get(vpath, &hw_stats->tx_stats);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	status = __vxge_hw_vpath_xmac_rx_stats_get(vpath, &hw_stats->rx_stats);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	VXGE_HW_VPATH_STATS_PIO_READ(
		VXGE_HW_STATS_VPATH_PROG_EVENT_VNUM0_OFFSET);

	hw_stats->prog_event_vnum0 =
			(u32)VXGE_HW_STATS_GET_VPATH_PROG_EVENT_VNUM0(val64);

	hw_stats->prog_event_vnum1 =
			(u32)VXGE_HW_STATS_GET_VPATH_PROG_EVENT_VNUM1(val64);

	VXGE_HW_VPATH_STATS_PIO_READ(
		VXGE_HW_STATS_VPATH_PROG_EVENT_VNUM2_OFFSET);

	hw_stats->prog_event_vnum2 =
			(u32)VXGE_HW_STATS_GET_VPATH_PROG_EVENT_VNUM2(val64);

	hw_stats->prog_event_vnum3 =
			(u32)VXGE_HW_STATS_GET_VPATH_PROG_EVENT_VNUM3(val64);

	val64 = पढ़ोq(&vp_reg->rx_multi_cast_stats);
	hw_stats->rx_multi_cast_frame_discard =
		(u16)VXGE_HW_RX_MULTI_CAST_STATS_GET_FRAME_DISCARD(val64);

	val64 = पढ़ोq(&vp_reg->rx_frm_transferred);
	hw_stats->rx_frm_transferred =
		(u32)VXGE_HW_RX_FRM_TRANSFERRED_GET_RX_FRM_TRANSFERRED(val64);

	val64 = पढ़ोq(&vp_reg->rxd_वापसed);
	hw_stats->rxd_वापसed =
		(u16)VXGE_HW_RXD_RETURNED_GET_RXD_RETURNED(val64);

	val64 = पढ़ोq(&vp_reg->dbg_stats_rx_mpa);
	hw_stats->rx_mpa_len_fail_frms =
		(u16)VXGE_HW_DBG_STATS_GET_RX_MPA_LEN_FAIL_FRMS(val64);
	hw_stats->rx_mpa_mrk_fail_frms =
		(u16)VXGE_HW_DBG_STATS_GET_RX_MPA_MRK_FAIL_FRMS(val64);
	hw_stats->rx_mpa_crc_fail_frms =
		(u16)VXGE_HW_DBG_STATS_GET_RX_MPA_CRC_FAIL_FRMS(val64);

	val64 = पढ़ोq(&vp_reg->dbg_stats_rx_fau);
	hw_stats->rx_permitted_frms =
		(u16)VXGE_HW_DBG_STATS_GET_RX_FAU_RX_PERMITTED_FRMS(val64);
	hw_stats->rx_vp_reset_discarded_frms =
	(u16)VXGE_HW_DBG_STATS_GET_RX_FAU_RX_VP_RESET_DISCARDED_FRMS(val64);
	hw_stats->rx_wol_frms =
		(u16)VXGE_HW_DBG_STATS_GET_RX_FAU_RX_WOL_FRMS(val64);

	val64 = पढ़ोq(&vp_reg->tx_vp_reset_discarded_frms);
	hw_stats->tx_vp_reset_discarded_frms =
	(u16)VXGE_HW_TX_VP_RESET_DISCARDED_FRMS_GET_TX_VP_RESET_DISCARDED_FRMS(
		val64);
निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_device_stats_get - Get the device hw statistics.
 * Returns the vpath h/w stats क्रम the device.
 */
क्रमागत vxge_hw_status
vxge_hw_device_stats_get(काष्ठा __vxge_hw_device *hldev,
			काष्ठा vxge_hw_device_stats_hw_info *hw_stats)
अणु
	u32 i;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
		अगर (!(hldev->vpaths_deployed & vxge_mBIT(i)) ||
			(hldev->भव_paths[i].vp_खोलो ==
				VXGE_HW_VP_NOT_OPEN))
			जारी;

		स_नकल(hldev->भव_paths[i].hw_stats_sav,
				hldev->भव_paths[i].hw_stats,
				माप(काष्ठा vxge_hw_vpath_stats_hw_info));

		status = __vxge_hw_vpath_stats_get(
			&hldev->भव_paths[i],
			hldev->भव_paths[i].hw_stats);
	पूर्ण

	स_नकल(hw_stats, &hldev->stats.hw_dev_info_stats,
			माप(काष्ठा vxge_hw_device_stats_hw_info));

	वापस status;
पूर्ण

/*
 * vxge_hw_driver_stats_get - Get the device sw statistics.
 * Returns the vpath s/w stats क्रम the device.
 */
क्रमागत vxge_hw_status vxge_hw_driver_stats_get(
			काष्ठा __vxge_hw_device *hldev,
			काष्ठा vxge_hw_device_stats_sw_info *sw_stats)
अणु
	स_नकल(sw_stats, &hldev->stats.sw_dev_info_stats,
		माप(काष्ठा vxge_hw_device_stats_sw_info));

	वापस VXGE_HW_OK;
पूर्ण

/*
 * vxge_hw_mrpcim_stats_access - Access the statistics from the given location
 *                           and offset and perक्रमm an operation
 * Get the statistics from the given location and offset.
 */
क्रमागत vxge_hw_status
vxge_hw_mrpcim_stats_access(काष्ठा __vxge_hw_device *hldev,
			    u32 operation, u32 location, u32 offset, u64 *stat)
अणु
	u64 val64;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	status = __vxge_hw_device_is_privilaged(hldev->host_type,
			hldev->func_id);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	val64 = VXGE_HW_XMAC_STATS_SYS_CMD_OP(operation) |
		VXGE_HW_XMAC_STATS_SYS_CMD_STROBE |
		VXGE_HW_XMAC_STATS_SYS_CMD_LOC_SEL(location) |
		VXGE_HW_XMAC_STATS_SYS_CMD_OFFSET_SEL(offset);

	status = __vxge_hw_pio_mem_ग_लिखो64(val64,
				&hldev->mrpcim_reg->xmac_stats_sys_cmd,
				VXGE_HW_XMAC_STATS_SYS_CMD_STROBE,
				hldev->config.device_poll_millis);

	अगर ((status == VXGE_HW_OK) && (operation == VXGE_HW_STATS_OP_READ))
		*stat = पढ़ोq(&hldev->mrpcim_reg->xmac_stats_sys_data);
	अन्यथा
		*stat = 0;
निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_device_xmac_aggr_stats_get - Get the Statistics on aggregate port
 * Get the Statistics on aggregate port
 */
अटल क्रमागत vxge_hw_status
vxge_hw_device_xmac_aggr_stats_get(काष्ठा __vxge_hw_device *hldev, u32 port,
				   काष्ठा vxge_hw_xmac_aggr_stats *aggr_stats)
अणु
	u64 *val64;
	पूर्णांक i;
	u32 offset = VXGE_HW_STATS_AGGRn_OFFSET;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	val64 = (u64 *)aggr_stats;

	status = __vxge_hw_device_is_privilaged(hldev->host_type,
			hldev->func_id);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	क्रम (i = 0; i < माप(काष्ठा vxge_hw_xmac_aggr_stats) / 8; i++) अणु
		status = vxge_hw_mrpcim_stats_access(hldev,
					VXGE_HW_STATS_OP_READ,
					VXGE_HW_STATS_LOC_AGGR,
					((offset + (104 * port)) >> 3), val64);
		अगर (status != VXGE_HW_OK)
			जाओ निकास;

		offset += 8;
		val64++;
	पूर्ण
निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_device_xmac_port_stats_get - Get the Statistics on a port
 * Get the Statistics on port
 */
अटल क्रमागत vxge_hw_status
vxge_hw_device_xmac_port_stats_get(काष्ठा __vxge_hw_device *hldev, u32 port,
				   काष्ठा vxge_hw_xmac_port_stats *port_stats)
अणु
	u64 *val64;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	पूर्णांक i;
	u32 offset = 0x0;
	val64 = (u64 *) port_stats;

	status = __vxge_hw_device_is_privilaged(hldev->host_type,
			hldev->func_id);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	क्रम (i = 0; i < माप(काष्ठा vxge_hw_xmac_port_stats) / 8; i++) अणु
		status = vxge_hw_mrpcim_stats_access(hldev,
					VXGE_HW_STATS_OP_READ,
					VXGE_HW_STATS_LOC_AGGR,
					((offset + (608 * port)) >> 3), val64);
		अगर (status != VXGE_HW_OK)
			जाओ निकास;

		offset += 8;
		val64++;
	पूर्ण

निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_device_xmac_stats_get - Get the XMAC Statistics
 * Get the XMAC Statistics
 */
क्रमागत vxge_hw_status
vxge_hw_device_xmac_stats_get(काष्ठा __vxge_hw_device *hldev,
			      काष्ठा vxge_hw_xmac_stats *xmac_stats)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	u32 i;

	status = vxge_hw_device_xmac_aggr_stats_get(hldev,
					0, &xmac_stats->aggr_stats[0]);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	status = vxge_hw_device_xmac_aggr_stats_get(hldev,
				1, &xmac_stats->aggr_stats[1]);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	क्रम (i = 0; i <= VXGE_HW_MAC_MAX_MAC_PORT_ID; i++) अणु

		status = vxge_hw_device_xmac_port_stats_get(hldev,
					i, &xmac_stats->port_stats[i]);
		अगर (status != VXGE_HW_OK)
			जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु

		अगर (!(hldev->vpaths_deployed & vxge_mBIT(i)))
			जारी;

		status = __vxge_hw_vpath_xmac_tx_stats_get(
					&hldev->भव_paths[i],
					&xmac_stats->vpath_tx_stats[i]);
		अगर (status != VXGE_HW_OK)
			जाओ निकास;

		status = __vxge_hw_vpath_xmac_rx_stats_get(
					&hldev->भव_paths[i],
					&xmac_stats->vpath_rx_stats[i]);
		अगर (status != VXGE_HW_OK)
			जाओ निकास;
	पूर्ण
निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_device_debug_set - Set the debug module, level and बारtamp
 * This routine is used to dynamically change the debug output
 */
व्योम vxge_hw_device_debug_set(काष्ठा __vxge_hw_device *hldev,
			      क्रमागत vxge_debug_level level, u32 mask)
अणु
	अगर (hldev == शून्य)
		वापस;

#अगर defined(VXGE_DEBUG_TRACE_MASK) || \
	defined(VXGE_DEBUG_ERR_MASK)
	hldev->debug_module_mask = mask;
	hldev->debug_level = level;
#पूर्ण_अगर

#अगर defined(VXGE_DEBUG_ERR_MASK)
	hldev->level_err = level & VXGE_ERR;
#पूर्ण_अगर

#अगर defined(VXGE_DEBUG_TRACE_MASK)
	hldev->level_trace = level & VXGE_TRACE;
#पूर्ण_अगर
पूर्ण

/*
 * vxge_hw_device_error_level_get - Get the error level
 * This routine वापसs the current error level set
 */
u32 vxge_hw_device_error_level_get(काष्ठा __vxge_hw_device *hldev)
अणु
#अगर defined(VXGE_DEBUG_ERR_MASK)
	अगर (hldev == शून्य)
		वापस VXGE_ERR;
	अन्यथा
		वापस hldev->level_err;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/*
 * vxge_hw_device_trace_level_get - Get the trace level
 * This routine वापसs the current trace level set
 */
u32 vxge_hw_device_trace_level_get(काष्ठा __vxge_hw_device *hldev)
अणु
#अगर defined(VXGE_DEBUG_TRACE_MASK)
	अगर (hldev == शून्य)
		वापस VXGE_TRACE;
	अन्यथा
		वापस hldev->level_trace;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/*
 * vxge_hw_getछोड़ो_data -Pause frame frame generation and reception.
 * Returns the Pause frame generation and reception capability of the NIC.
 */
क्रमागत vxge_hw_status vxge_hw_device_getछोड़ो_data(काष्ठा __vxge_hw_device *hldev,
						 u32 port, u32 *tx, u32 *rx)
अणु
	u64 val64;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर ((hldev == शून्य) || (hldev->magic != VXGE_HW_DEVICE_MAGIC)) अणु
		status = VXGE_HW_ERR_INVALID_DEVICE;
		जाओ निकास;
	पूर्ण

	अगर (port > VXGE_HW_MAC_MAX_MAC_PORT_ID) अणु
		status = VXGE_HW_ERR_INVALID_PORT;
		जाओ निकास;
	पूर्ण

	अगर (!(hldev->access_rights & VXGE_HW_DEVICE_ACCESS_RIGHT_MRPCIM)) अणु
		status = VXGE_HW_ERR_PRIVILEGED_OPERATION;
		जाओ निकास;
	पूर्ण

	val64 = पढ़ोq(&hldev->mrpcim_reg->rxmac_छोड़ो_cfg_port[port]);
	अगर (val64 & VXGE_HW_RXMAC_PAUSE_CFG_PORT_GEN_EN)
		*tx = 1;
	अगर (val64 & VXGE_HW_RXMAC_PAUSE_CFG_PORT_RCV_EN)
		*rx = 1;
निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_device_setछोड़ो_data -  set/reset छोड़ो frame generation.
 * It can be used to set or reset Pause frame generation or reception
 * support of the NIC.
 */
क्रमागत vxge_hw_status vxge_hw_device_setछोड़ो_data(काष्ठा __vxge_hw_device *hldev,
						 u32 port, u32 tx, u32 rx)
अणु
	u64 val64;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर ((hldev == शून्य) || (hldev->magic != VXGE_HW_DEVICE_MAGIC)) अणु
		status = VXGE_HW_ERR_INVALID_DEVICE;
		जाओ निकास;
	पूर्ण

	अगर (port > VXGE_HW_MAC_MAX_MAC_PORT_ID) अणु
		status = VXGE_HW_ERR_INVALID_PORT;
		जाओ निकास;
	पूर्ण

	status = __vxge_hw_device_is_privilaged(hldev->host_type,
			hldev->func_id);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	val64 = पढ़ोq(&hldev->mrpcim_reg->rxmac_छोड़ो_cfg_port[port]);
	अगर (tx)
		val64 |= VXGE_HW_RXMAC_PAUSE_CFG_PORT_GEN_EN;
	अन्यथा
		val64 &= ~VXGE_HW_RXMAC_PAUSE_CFG_PORT_GEN_EN;
	अगर (rx)
		val64 |= VXGE_HW_RXMAC_PAUSE_CFG_PORT_RCV_EN;
	अन्यथा
		val64 &= ~VXGE_HW_RXMAC_PAUSE_CFG_PORT_RCV_EN;

	ग_लिखोq(val64, &hldev->mrpcim_reg->rxmac_छोड़ो_cfg_port[port]);
निकास:
	वापस status;
पूर्ण

u16 vxge_hw_device_link_width_get(काष्ठा __vxge_hw_device *hldev)
अणु
	काष्ठा pci_dev *dev = hldev->pdev;
	u16 lnk;

	pcie_capability_पढ़ो_word(dev, PCI_EXP_LNKSTA, &lnk);
	वापस (lnk & VXGE_HW_PCI_EXP_LNKCAP_LNK_WIDTH) >> 4;
पूर्ण

/*
 * __vxge_hw_ring_block_memblock_idx - Return the memblock index
 * This function वापसs the index of memory block
 */
अटल अंतरभूत u32
__vxge_hw_ring_block_memblock_idx(u8 *block)
अणु
	वापस (u32)*((u64 *)(block + VXGE_HW_RING_MEMBLOCK_IDX_OFFSET));
पूर्ण

/*
 * __vxge_hw_ring_block_memblock_idx_set - Sets the memblock index
 * This function sets index to a memory block
 */
अटल अंतरभूत व्योम
__vxge_hw_ring_block_memblock_idx_set(u8 *block, u32 memblock_idx)
अणु
	*((u64 *)(block + VXGE_HW_RING_MEMBLOCK_IDX_OFFSET)) = memblock_idx;
पूर्ण

/*
 * __vxge_hw_ring_block_next_poपूर्णांकer_set - Sets the next block poपूर्णांकer
 * in RxD block
 * Sets the next block poपूर्णांकer in RxD block
 */
अटल अंतरभूत व्योम
__vxge_hw_ring_block_next_poपूर्णांकer_set(u8 *block, dma_addr_t dma_next)
अणु
	*((u64 *)(block + VXGE_HW_RING_NEXT_BLOCK_POINTER_OFFSET)) = dma_next;
पूर्ण

/*
 * __vxge_hw_ring_first_block_address_get - Returns the dma address of the
 *             first block
 * Returns the dma address of the first RxD block
 */
अटल u64 __vxge_hw_ring_first_block_address_get(काष्ठा __vxge_hw_ring *ring)
अणु
	काष्ठा vxge_hw_mempool_dma *dma_object;

	dma_object = ring->mempool->memblocks_dma_arr;
	vxge_निश्चित(dma_object != शून्य);

	वापस dma_object->addr;
पूर्ण

/*
 * __vxge_hw_ring_item_dma_addr - Return the dma address of an item
 * This function वापसs the dma address of a given item
 */
अटल dma_addr_t __vxge_hw_ring_item_dma_addr(काष्ठा vxge_hw_mempool *mempoolh,
					       व्योम *item)
अणु
	u32 memblock_idx;
	व्योम *memblock;
	काष्ठा vxge_hw_mempool_dma *memblock_dma_object;
	सूचक_भेद_प्रकार dma_item_offset;

	/* get owner memblock index */
	memblock_idx = __vxge_hw_ring_block_memblock_idx(item);

	/* get owner memblock by memblock index */
	memblock = mempoolh->memblocks_arr[memblock_idx];

	/* get memblock DMA object by memblock index */
	memblock_dma_object = mempoolh->memblocks_dma_arr + memblock_idx;

	/* calculate offset in the memblock of this item */
	dma_item_offset = (u8 *)item - (u8 *)memblock;

	वापस memblock_dma_object->addr + dma_item_offset;
पूर्ण

/*
 * __vxge_hw_ring_rxdblock_link - Link the RxD blocks
 * This function वापसs the dma address of a given item
 */
अटल व्योम __vxge_hw_ring_rxdblock_link(काष्ठा vxge_hw_mempool *mempoolh,
					 काष्ठा __vxge_hw_ring *ring, u32 from,
					 u32 to)
अणु
	u8 *to_item , *from_item;
	dma_addr_t to_dma;

	/* get "from" RxD block */
	from_item = mempoolh->items_arr[from];
	vxge_निश्चित(from_item);

	/* get "to" RxD block */
	to_item = mempoolh->items_arr[to];
	vxge_निश्चित(to_item);

	/* वापस address of the beginning of previous RxD block */
	to_dma = __vxge_hw_ring_item_dma_addr(mempoolh, to_item);

	/* set next poपूर्णांकer क्रम this RxD block to poपूर्णांक on
	 * previous item's DMA start address */
	__vxge_hw_ring_block_next_poपूर्णांकer_set(from_item, to_dma);
पूर्ण

/*
 * __vxge_hw_ring_mempool_item_alloc - Allocate List blocks क्रम RxD
 * block callback
 * This function is callback passed to __vxge_hw_mempool_create to create memory
 * pool क्रम RxD block
 */
अटल व्योम
__vxge_hw_ring_mempool_item_alloc(काष्ठा vxge_hw_mempool *mempoolh,
				  u32 memblock_index,
				  काष्ठा vxge_hw_mempool_dma *dma_object,
				  u32 index, u32 is_last)
अणु
	u32 i;
	व्योम *item = mempoolh->items_arr[index];
	काष्ठा __vxge_hw_ring *ring =
		(काष्ठा __vxge_hw_ring *)mempoolh->userdata;

	/* क्रमmat rxds array */
	क्रम (i = 0; i < ring->rxds_per_block; i++) अणु
		व्योम *rxdblock_priv;
		व्योम *uld_priv;
		काष्ठा vxge_hw_ring_rxd_1 *rxdp;

		u32 reserve_index = ring->channel.reserve_ptr -
				(index * ring->rxds_per_block + i + 1);
		u32 memblock_item_idx;

		ring->channel.reserve_arr[reserve_index] = ((u8 *)item) +
						i * ring->rxd_size;

		/* Note: memblock_item_idx is index of the item within
		 *       the memblock. For instance, in हाल of three RxD-blocks
		 *       per memblock this value can be 0, 1 or 2. */
		rxdblock_priv = __vxge_hw_mempool_item_priv(mempoolh,
					memblock_index, item,
					&memblock_item_idx);

		rxdp = ring->channel.reserve_arr[reserve_index];

		uld_priv = ((u8 *)rxdblock_priv + ring->rxd_priv_size * i);

		/* pre-क्रमmat Host_Control */
		rxdp->host_control = (u64)(माप_प्रकार)uld_priv;
	पूर्ण

	__vxge_hw_ring_block_memblock_idx_set(item, memblock_index);

	अगर (is_last) अणु
		/* link last one with first one */
		__vxge_hw_ring_rxdblock_link(mempoolh, ring, index, 0);
	पूर्ण

	अगर (index > 0) अणु
		/* link this RxD block with previous one */
		__vxge_hw_ring_rxdblock_link(mempoolh, ring, index - 1, index);
	पूर्ण
पूर्ण

/*
 * __vxge_hw_ring_replenish - Initial replenish of RxDs
 * This function replenishes the RxDs from reserve array to work array
 */
अटल क्रमागत vxge_hw_status
vxge_hw_ring_replenish(काष्ठा __vxge_hw_ring *ring)
अणु
	व्योम *rxd;
	काष्ठा __vxge_hw_channel *channel;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	channel = &ring->channel;

	जबतक (vxge_hw_channel_dtr_count(channel) > 0) अणु

		status = vxge_hw_ring_rxd_reserve(ring, &rxd);

		vxge_निश्चित(status == VXGE_HW_OK);

		अगर (ring->rxd_init) अणु
			status = ring->rxd_init(rxd, channel->userdata);
			अगर (status != VXGE_HW_OK) अणु
				vxge_hw_ring_rxd_मुक्त(ring, rxd);
				जाओ निकास;
			पूर्ण
		पूर्ण

		vxge_hw_ring_rxd_post(ring, rxd);
	पूर्ण
	status = VXGE_HW_OK;
निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_channel_allocate - Allocate memory क्रम channel
 * This function allocates required memory क्रम the channel and various arrays
 * in the channel
 */
अटल काष्ठा __vxge_hw_channel *
__vxge_hw_channel_allocate(काष्ठा __vxge_hw_vpath_handle *vph,
			   क्रमागत __vxge_hw_channel_type type,
			   u32 length, u32 per_dtr_space,
			   व्योम *userdata)
अणु
	काष्ठा __vxge_hw_channel *channel;
	काष्ठा __vxge_hw_device *hldev;
	पूर्णांक size = 0;
	u32 vp_id;

	hldev = vph->vpath->hldev;
	vp_id = vph->vpath->vp_id;

	चयन (type) अणु
	हाल VXGE_HW_CHANNEL_TYPE_FIFO:
		size = माप(काष्ठा __vxge_hw_fअगरo);
		अवरोध;
	हाल VXGE_HW_CHANNEL_TYPE_RING:
		size = माप(काष्ठा __vxge_hw_ring);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	channel = kzalloc(size, GFP_KERNEL);
	अगर (channel == शून्य)
		जाओ निकास0;
	INIT_LIST_HEAD(&channel->item);

	channel->common_reg = hldev->common_reg;
	channel->first_vp_id = hldev->first_vp_id;
	channel->type = type;
	channel->devh = hldev;
	channel->vph = vph;
	channel->userdata = userdata;
	channel->per_dtr_space = per_dtr_space;
	channel->length = length;
	channel->vp_id = vp_id;

	channel->work_arr = kसुस्मृति(length, माप(व्योम *), GFP_KERNEL);
	अगर (channel->work_arr == शून्य)
		जाओ निकास1;

	channel->मुक्त_arr = kसुस्मृति(length, माप(व्योम *), GFP_KERNEL);
	अगर (channel->मुक्त_arr == शून्य)
		जाओ निकास1;
	channel->मुक्त_ptr = length;

	channel->reserve_arr = kसुस्मृति(length, माप(व्योम *), GFP_KERNEL);
	अगर (channel->reserve_arr == शून्य)
		जाओ निकास1;
	channel->reserve_ptr = length;
	channel->reserve_top = 0;

	channel->orig_arr = kसुस्मृति(length, माप(व्योम *), GFP_KERNEL);
	अगर (channel->orig_arr == शून्य)
		जाओ निकास1;

	वापस channel;
निकास1:
	__vxge_hw_channel_मुक्त(channel);

निकास0:
	वापस शून्य;
पूर्ण

/*
 * vxge_hw_blockpool_block_add - callback क्रम vxge_os_dma_दो_स्मृति_async
 * Adds a block to block pool
 */
अटल व्योम vxge_hw_blockpool_block_add(काष्ठा __vxge_hw_device *devh,
					व्योम *block_addr,
					u32 length,
					काष्ठा pci_dev *dma_h,
					काष्ठा pci_dev *acc_handle)
अणु
	काष्ठा __vxge_hw_blockpool *blockpool;
	काष्ठा __vxge_hw_blockpool_entry *entry = शून्य;
	dma_addr_t dma_addr;

	blockpool = &devh->block_pool;

	अगर (block_addr == शून्य) अणु
		blockpool->req_out--;
		जाओ निकास;
	पूर्ण

	dma_addr = dma_map_single(&devh->pdev->dev, block_addr, length,
				  DMA_BIसूचीECTIONAL);

	अगर (unlikely(dma_mapping_error(&devh->pdev->dev, dma_addr))) अणु
		vxge_os_dma_मुक्त(devh->pdev, block_addr, &acc_handle);
		blockpool->req_out--;
		जाओ निकास;
	पूर्ण

	अगर (!list_empty(&blockpool->मुक्त_entry_list))
		entry = (काष्ठा __vxge_hw_blockpool_entry *)
			list_first_entry(&blockpool->मुक्त_entry_list,
				काष्ठा __vxge_hw_blockpool_entry,
				item);

	अगर (entry == शून्य)
		entry =	vदो_स्मृति(माप(काष्ठा __vxge_hw_blockpool_entry));
	अन्यथा
		list_del(&entry->item);

	अगर (entry) अणु
		entry->length = length;
		entry->memblock = block_addr;
		entry->dma_addr = dma_addr;
		entry->acc_handle = acc_handle;
		entry->dma_handle = dma_h;
		list_add(&entry->item, &blockpool->मुक्त_block_list);
		blockpool->pool_size++;
	पूर्ण

	blockpool->req_out--;

निकास:
	वापस;
पूर्ण

अटल अंतरभूत व्योम
vxge_os_dma_दो_स्मृति_async(काष्ठा pci_dev *pdev, व्योम *devh, अचिन्हित दीर्घ size)
अणु
	व्योम *vaddr;

	vaddr = kदो_स्मृति(size, GFP_KERNEL | GFP_DMA);
	vxge_hw_blockpool_block_add(devh, vaddr, size, pdev, pdev);
पूर्ण

/*
 * __vxge_hw_blockpool_blocks_add - Request additional blocks
 */
अटल
व्योम __vxge_hw_blockpool_blocks_add(काष्ठा __vxge_hw_blockpool *blockpool)
अणु
	u32 nreq = 0, i;

	अगर ((blockpool->pool_size  +  blockpool->req_out) <
		VXGE_HW_MIN_DMA_BLOCK_POOL_SIZE) अणु
		nreq = VXGE_HW_INCR_DMA_BLOCK_POOL_SIZE;
		blockpool->req_out += nreq;
	पूर्ण

	क्रम (i = 0; i < nreq; i++)
		vxge_os_dma_दो_स्मृति_async(
			(blockpool->hldev)->pdev,
			blockpool->hldev, VXGE_HW_BLOCK_SIZE);
पूर्ण

/*
 * __vxge_hw_blockpool_दो_स्मृति - Allocate a memory block from pool
 * Allocates a block of memory of given size, either from block pool
 * or by calling vxge_os_dma_दो_स्मृति()
 */
अटल व्योम *__vxge_hw_blockpool_दो_स्मृति(काष्ठा __vxge_hw_device *devh, u32 size,
					काष्ठा vxge_hw_mempool_dma *dma_object)
अणु
	काष्ठा __vxge_hw_blockpool_entry *entry = शून्य;
	काष्ठा __vxge_hw_blockpool  *blockpool;
	व्योम *memblock = शून्य;

	blockpool = &devh->block_pool;

	अगर (size != blockpool->block_size) अणु

		memblock = vxge_os_dma_दो_स्मृति(devh->pdev, size,
						&dma_object->handle,
						&dma_object->acc_handle);

		अगर (!memblock)
			जाओ निकास;

		dma_object->addr = dma_map_single(&devh->pdev->dev, memblock,
						  size, DMA_BIसूचीECTIONAL);

		अगर (unlikely(dma_mapping_error(&devh->pdev->dev, dma_object->addr))) अणु
			vxge_os_dma_मुक्त(devh->pdev, memblock,
				&dma_object->acc_handle);
			memblock = शून्य;
			जाओ निकास;
		पूर्ण

	पूर्ण अन्यथा अणु

		अगर (!list_empty(&blockpool->मुक्त_block_list))
			entry = (काष्ठा __vxge_hw_blockpool_entry *)
				list_first_entry(&blockpool->मुक्त_block_list,
					काष्ठा __vxge_hw_blockpool_entry,
					item);

		अगर (entry != शून्य) अणु
			list_del(&entry->item);
			dma_object->addr = entry->dma_addr;
			dma_object->handle = entry->dma_handle;
			dma_object->acc_handle = entry->acc_handle;
			memblock = entry->memblock;

			list_add(&entry->item,
				&blockpool->मुक्त_entry_list);
			blockpool->pool_size--;
		पूर्ण

		अगर (memblock != शून्य)
			__vxge_hw_blockpool_blocks_add(blockpool);
	पूर्ण
निकास:
	वापस memblock;
पूर्ण

/*
 * __vxge_hw_blockpool_blocks_हटाओ - Free additional blocks
 */
अटल व्योम
__vxge_hw_blockpool_blocks_हटाओ(काष्ठा __vxge_hw_blockpool *blockpool)
अणु
	काष्ठा list_head *p, *n;

	list_क्रम_each_safe(p, n, &blockpool->मुक्त_block_list) अणु

		अगर (blockpool->pool_size < blockpool->pool_max)
			अवरोध;

		dma_unmap_single(&(blockpool->hldev)->pdev->dev,
				 ((काष्ठा __vxge_hw_blockpool_entry *)p)->dma_addr,
				 ((काष्ठा __vxge_hw_blockpool_entry *)p)->length,
				 DMA_BIसूचीECTIONAL);

		vxge_os_dma_मुक्त(
			(blockpool->hldev)->pdev,
			((काष्ठा __vxge_hw_blockpool_entry *)p)->memblock,
			&((काष्ठा __vxge_hw_blockpool_entry *)p)->acc_handle);

		list_del(&((काष्ठा __vxge_hw_blockpool_entry *)p)->item);

		list_add(p, &blockpool->मुक्त_entry_list);

		blockpool->pool_size--;

	पूर्ण
पूर्ण

/*
 * __vxge_hw_blockpool_मुक्त - Frees the memory allcoated with
 *				__vxge_hw_blockpool_दो_स्मृति
 */
अटल व्योम __vxge_hw_blockpool_मुक्त(काष्ठा __vxge_hw_device *devh,
				     व्योम *memblock, u32 size,
				     काष्ठा vxge_hw_mempool_dma *dma_object)
अणु
	काष्ठा __vxge_hw_blockpool_entry *entry = शून्य;
	काष्ठा __vxge_hw_blockpool  *blockpool;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	blockpool = &devh->block_pool;

	अगर (size != blockpool->block_size) अणु
		dma_unmap_single(&devh->pdev->dev, dma_object->addr, size,
				 DMA_BIसूचीECTIONAL);
		vxge_os_dma_मुक्त(devh->pdev, memblock, &dma_object->acc_handle);
	पूर्ण अन्यथा अणु

		अगर (!list_empty(&blockpool->मुक्त_entry_list))
			entry = (काष्ठा __vxge_hw_blockpool_entry *)
				list_first_entry(&blockpool->मुक्त_entry_list,
					काष्ठा __vxge_hw_blockpool_entry,
					item);

		अगर (entry == शून्य)
			entry =	vदो_स्मृति(माप(
					काष्ठा __vxge_hw_blockpool_entry));
		अन्यथा
			list_del(&entry->item);

		अगर (entry != शून्य) अणु
			entry->length = size;
			entry->memblock = memblock;
			entry->dma_addr = dma_object->addr;
			entry->acc_handle = dma_object->acc_handle;
			entry->dma_handle = dma_object->handle;
			list_add(&entry->item,
					&blockpool->मुक्त_block_list);
			blockpool->pool_size++;
			status = VXGE_HW_OK;
		पूर्ण अन्यथा
			status = VXGE_HW_ERR_OUT_OF_MEMORY;

		अगर (status == VXGE_HW_OK)
			__vxge_hw_blockpool_blocks_हटाओ(blockpool);
	पूर्ण
पूर्ण

/*
 * vxge_hw_mempool_destroy
 */
अटल व्योम __vxge_hw_mempool_destroy(काष्ठा vxge_hw_mempool *mempool)
अणु
	u32 i, j;
	काष्ठा __vxge_hw_device *devh = mempool->devh;

	क्रम (i = 0; i < mempool->memblocks_allocated; i++) अणु
		काष्ठा vxge_hw_mempool_dma *dma_object;

		vxge_निश्चित(mempool->memblocks_arr[i]);
		vxge_निश्चित(mempool->memblocks_dma_arr + i);

		dma_object = mempool->memblocks_dma_arr + i;

		क्रम (j = 0; j < mempool->items_per_memblock; j++) अणु
			u32 index = i * mempool->items_per_memblock + j;

			/* to skip last partially filled(अगर any) memblock */
			अगर (index >= mempool->items_current)
				अवरोध;
		पूर्ण

		vमुक्त(mempool->memblocks_priv_arr[i]);

		__vxge_hw_blockpool_मुक्त(devh, mempool->memblocks_arr[i],
				mempool->memblock_size, dma_object);
	पूर्ण

	vमुक्त(mempool->items_arr);
	vमुक्त(mempool->memblocks_dma_arr);
	vमुक्त(mempool->memblocks_priv_arr);
	vमुक्त(mempool->memblocks_arr);
	vमुक्त(mempool);
पूर्ण

/*
 * __vxge_hw_mempool_grow
 * Will resize mempool up to %num_allocate value.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_mempool_grow(काष्ठा vxge_hw_mempool *mempool, u32 num_allocate,
		       u32 *num_allocated)
अणु
	u32 i, first_समय = mempool->memblocks_allocated == 0 ? 1 : 0;
	u32 n_items = mempool->items_per_memblock;
	u32 start_block_idx = mempool->memblocks_allocated;
	u32 end_block_idx = mempool->memblocks_allocated + num_allocate;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	*num_allocated = 0;

	अगर (end_block_idx > mempool->memblocks_max) अणु
		status = VXGE_HW_ERR_OUT_OF_MEMORY;
		जाओ निकास;
	पूर्ण

	क्रम (i = start_block_idx; i < end_block_idx; i++) अणु
		u32 j;
		u32 is_last = ((end_block_idx - 1) == i);
		काष्ठा vxge_hw_mempool_dma *dma_object =
			mempool->memblocks_dma_arr + i;
		व्योम *the_memblock;

		/* allocate memblock's निजी part. Each DMA memblock
		 * has a space allocated क्रम item's निजी usage upon
		 * mempool's user request. Each समय mempool grows, it will
		 * allocate new memblock and its निजी part at once.
		 * This helps to minimize memory usage a lot. */
		mempool->memblocks_priv_arr[i] =
			vzalloc(array_size(mempool->items_priv_size, n_items));
		अगर (mempool->memblocks_priv_arr[i] == शून्य) अणु
			status = VXGE_HW_ERR_OUT_OF_MEMORY;
			जाओ निकास;
		पूर्ण

		/* allocate DMA-capable memblock */
		mempool->memblocks_arr[i] =
			__vxge_hw_blockpool_दो_स्मृति(mempool->devh,
				mempool->memblock_size, dma_object);
		अगर (mempool->memblocks_arr[i] == शून्य) अणु
			vमुक्त(mempool->memblocks_priv_arr[i]);
			status = VXGE_HW_ERR_OUT_OF_MEMORY;
			जाओ निकास;
		पूर्ण

		(*num_allocated)++;
		mempool->memblocks_allocated++;

		स_रखो(mempool->memblocks_arr[i], 0, mempool->memblock_size);

		the_memblock = mempool->memblocks_arr[i];

		/* fill the items hash array */
		क्रम (j = 0; j < n_items; j++) अणु
			u32 index = i * n_items + j;

			अगर (first_समय && index >= mempool->items_initial)
				अवरोध;

			mempool->items_arr[index] =
				((अक्षर *)the_memblock + j*mempool->item_size);

			/* let caller to करो more job on each item */
			अगर (mempool->item_func_alloc != शून्य)
				mempool->item_func_alloc(mempool, i,
					dma_object, index, is_last);

			mempool->items_current = index + 1;
		पूर्ण

		अगर (first_समय && mempool->items_current ==
					mempool->items_initial)
			अवरोध;
	पूर्ण
निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_mempool_create
 * This function will create memory pool object. Pool may grow but will
 * never shrink. Pool consists of number of dynamically allocated blocks
 * with size enough to hold %items_initial number of items. Memory is
 * DMA-able but client must map/unmap beक्रमe पूर्णांकeroperating with the device.
 */
अटल काष्ठा vxge_hw_mempool *
__vxge_hw_mempool_create(काष्ठा __vxge_hw_device *devh,
			 u32 memblock_size,
			 u32 item_size,
			 u32 items_priv_size,
			 u32 items_initial,
			 u32 items_max,
			 स्थिर काष्ठा vxge_hw_mempool_cbs *mp_callback,
			 व्योम *userdata)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	u32 memblocks_to_allocate;
	काष्ठा vxge_hw_mempool *mempool = शून्य;
	u32 allocated;

	अगर (memblock_size < item_size) अणु
		status = VXGE_HW_FAIL;
		जाओ निकास;
	पूर्ण

	mempool = vzalloc(माप(काष्ठा vxge_hw_mempool));
	अगर (mempool == शून्य) अणु
		status = VXGE_HW_ERR_OUT_OF_MEMORY;
		जाओ निकास;
	पूर्ण

	mempool->devh			= devh;
	mempool->memblock_size		= memblock_size;
	mempool->items_max		= items_max;
	mempool->items_initial		= items_initial;
	mempool->item_size		= item_size;
	mempool->items_priv_size	= items_priv_size;
	mempool->item_func_alloc	= mp_callback->item_func_alloc;
	mempool->userdata		= userdata;

	mempool->memblocks_allocated = 0;

	mempool->items_per_memblock = memblock_size / item_size;

	mempool->memblocks_max = (items_max + mempool->items_per_memblock - 1) /
					mempool->items_per_memblock;

	/* allocate array of memblocks */
	mempool->memblocks_arr =
		vzalloc(array_size(माप(व्योम *), mempool->memblocks_max));
	अगर (mempool->memblocks_arr == शून्य) अणु
		__vxge_hw_mempool_destroy(mempool);
		status = VXGE_HW_ERR_OUT_OF_MEMORY;
		mempool = शून्य;
		जाओ निकास;
	पूर्ण

	/* allocate array of निजी parts of items per memblocks */
	mempool->memblocks_priv_arr =
		vzalloc(array_size(माप(व्योम *), mempool->memblocks_max));
	अगर (mempool->memblocks_priv_arr == शून्य) अणु
		__vxge_hw_mempool_destroy(mempool);
		status = VXGE_HW_ERR_OUT_OF_MEMORY;
		mempool = शून्य;
		जाओ निकास;
	पूर्ण

	/* allocate array of memblocks DMA objects */
	mempool->memblocks_dma_arr =
		vzalloc(array_size(माप(काष्ठा vxge_hw_mempool_dma),
				   mempool->memblocks_max));
	अगर (mempool->memblocks_dma_arr == शून्य) अणु
		__vxge_hw_mempool_destroy(mempool);
		status = VXGE_HW_ERR_OUT_OF_MEMORY;
		mempool = शून्य;
		जाओ निकास;
	पूर्ण

	/* allocate hash array of items */
	mempool->items_arr = vzalloc(array_size(माप(व्योम *),
						mempool->items_max));
	अगर (mempool->items_arr == शून्य) अणु
		__vxge_hw_mempool_destroy(mempool);
		status = VXGE_HW_ERR_OUT_OF_MEMORY;
		mempool = शून्य;
		जाओ निकास;
	पूर्ण

	/* calculate initial number of memblocks */
	memblocks_to_allocate = (mempool->items_initial +
				 mempool->items_per_memblock - 1) /
						mempool->items_per_memblock;

	/* pre-allocate the mempool */
	status = __vxge_hw_mempool_grow(mempool, memblocks_to_allocate,
					&allocated);
	अगर (status != VXGE_HW_OK) अणु
		__vxge_hw_mempool_destroy(mempool);
		status = VXGE_HW_ERR_OUT_OF_MEMORY;
		mempool = शून्य;
		जाओ निकास;
	पूर्ण

निकास:
	वापस mempool;
पूर्ण

/*
 * __vxge_hw_ring_पात - Returns the RxD
 * This function terminates the RxDs of ring
 */
अटल क्रमागत vxge_hw_status __vxge_hw_ring_पात(काष्ठा __vxge_hw_ring *ring)
अणु
	व्योम *rxdh;
	काष्ठा __vxge_hw_channel *channel;

	channel = &ring->channel;

	क्रम (;;) अणु
		vxge_hw_channel_dtr_try_complete(channel, &rxdh);

		अगर (rxdh == शून्य)
			अवरोध;

		vxge_hw_channel_dtr_complete(channel);

		अगर (ring->rxd_term)
			ring->rxd_term(rxdh, VXGE_HW_RXD_STATE_POSTED,
				channel->userdata);

		vxge_hw_channel_dtr_मुक्त(channel, rxdh);
	पूर्ण

	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_ring_reset - Resets the ring
 * This function resets the ring during vpath reset operation
 */
अटल क्रमागत vxge_hw_status __vxge_hw_ring_reset(काष्ठा __vxge_hw_ring *ring)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा __vxge_hw_channel *channel;

	channel = &ring->channel;

	__vxge_hw_ring_पात(ring);

	status = __vxge_hw_channel_reset(channel);

	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	अगर (ring->rxd_init) अणु
		status = vxge_hw_ring_replenish(ring);
		अगर (status != VXGE_HW_OK)
			जाओ निकास;
	पूर्ण
निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_ring_delete - Removes the ring
 * This function मुक्तup the memory pool and हटाओs the ring
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_ring_delete(काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	काष्ठा __vxge_hw_ring *ring = vp->vpath->ringh;

	__vxge_hw_ring_पात(ring);

	अगर (ring->mempool)
		__vxge_hw_mempool_destroy(ring->mempool);

	vp->vpath->ringh = शून्य;
	__vxge_hw_channel_मुक्त(&ring->channel);

	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_ring_create - Create a Ring
 * This function creates Ring and initializes it.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_ring_create(काष्ठा __vxge_hw_vpath_handle *vp,
		      काष्ठा vxge_hw_ring_attr *attr)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा __vxge_hw_ring *ring;
	u32 ring_length;
	काष्ठा vxge_hw_ring_config *config;
	काष्ठा __vxge_hw_device *hldev;
	u32 vp_id;
	अटल स्थिर काष्ठा vxge_hw_mempool_cbs ring_mp_callback = अणु
		.item_func_alloc = __vxge_hw_ring_mempool_item_alloc,
	पूर्ण;

	अगर ((vp == शून्य) || (attr == शून्य)) अणु
		status = VXGE_HW_FAIL;
		जाओ निकास;
	पूर्ण

	hldev = vp->vpath->hldev;
	vp_id = vp->vpath->vp_id;

	config = &hldev->config.vp_config[vp_id].ring;

	ring_length = config->ring_blocks *
			vxge_hw_ring_rxds_per_block_get(config->buffer_mode);

	ring = (काष्ठा __vxge_hw_ring *)__vxge_hw_channel_allocate(vp,
						VXGE_HW_CHANNEL_TYPE_RING,
						ring_length,
						attr->per_rxd_space,
						attr->userdata);
	अगर (ring == शून्य) अणु
		status = VXGE_HW_ERR_OUT_OF_MEMORY;
		जाओ निकास;
	पूर्ण

	vp->vpath->ringh = ring;
	ring->vp_id = vp_id;
	ring->vp_reg = vp->vpath->vp_reg;
	ring->common_reg = hldev->common_reg;
	ring->stats = &vp->vpath->sw_stats->ring_stats;
	ring->config = config;
	ring->callback = attr->callback;
	ring->rxd_init = attr->rxd_init;
	ring->rxd_term = attr->rxd_term;
	ring->buffer_mode = config->buffer_mode;
	ring->tim_rti_cfg1_saved = vp->vpath->tim_rti_cfg1_saved;
	ring->tim_rti_cfg3_saved = vp->vpath->tim_rti_cfg3_saved;
	ring->rxds_limit = config->rxds_limit;

	ring->rxd_size = vxge_hw_ring_rxd_size_get(config->buffer_mode);
	ring->rxd_priv_size =
		माप(काष्ठा __vxge_hw_ring_rxd_priv) + attr->per_rxd_space;
	ring->per_rxd_space = attr->per_rxd_space;

	ring->rxd_priv_size =
		((ring->rxd_priv_size + VXGE_CACHE_LINE_SIZE - 1) /
		VXGE_CACHE_LINE_SIZE) * VXGE_CACHE_LINE_SIZE;

	/* how many RxDs can fit पूर्णांकo one block. Depends on configured
	 * buffer_mode. */
	ring->rxds_per_block =
		vxge_hw_ring_rxds_per_block_get(config->buffer_mode);

	/* calculate actual RxD block निजी size */
	ring->rxdblock_priv_size = ring->rxd_priv_size * ring->rxds_per_block;
	ring->mempool = __vxge_hw_mempool_create(hldev,
				VXGE_HW_BLOCK_SIZE,
				VXGE_HW_BLOCK_SIZE,
				ring->rxdblock_priv_size,
				ring->config->ring_blocks,
				ring->config->ring_blocks,
				&ring_mp_callback,
				ring);
	अगर (ring->mempool == शून्य) अणु
		__vxge_hw_ring_delete(vp);
		वापस VXGE_HW_ERR_OUT_OF_MEMORY;
	पूर्ण

	status = __vxge_hw_channel_initialize(&ring->channel);
	अगर (status != VXGE_HW_OK) अणु
		__vxge_hw_ring_delete(vp);
		जाओ निकास;
	पूर्ण

	/* Note:
	 * Specअगरying rxd_init callback means two things:
	 * 1) rxds need to be initialized by driver at channel-खोलो समय;
	 * 2) rxds need to be posted at channel-खोलो समय
	 *    (that's what the initial_replenish() below करोes)
	 * Currently we करोn't have a हाल when the 1) is करोne without the 2).
	 */
	अगर (ring->rxd_init) अणु
		status = vxge_hw_ring_replenish(ring);
		अगर (status != VXGE_HW_OK) अणु
			__vxge_hw_ring_delete(vp);
			जाओ निकास;
		पूर्ण
	पूर्ण

	/* initial replenish will increment the counter in its post() routine,
	 * we have to reset it */
	ring->stats->common_stats.usage_cnt = 0;
निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_device_config_शेष_get - Initialize device config with शेषs.
 * Initialize Titan device config with शेष values.
 */
क्रमागत vxge_hw_status
vxge_hw_device_config_शेष_get(काष्ठा vxge_hw_device_config *device_config)
अणु
	u32 i;

	device_config->dma_blockpool_initial =
					VXGE_HW_INITIAL_DMA_BLOCK_POOL_SIZE;
	device_config->dma_blockpool_max = VXGE_HW_MAX_DMA_BLOCK_POOL_SIZE;
	device_config->पूर्णांकr_mode = VXGE_HW_INTR_MODE_DEF;
	device_config->rth_en = VXGE_HW_RTH_DEFAULT;
	device_config->rth_it_type = VXGE_HW_RTH_IT_TYPE_DEFAULT;
	device_config->device_poll_millis =  VXGE_HW_DEF_DEVICE_POLL_MILLIS;
	device_config->rts_mac_en =  VXGE_HW_RTS_MAC_DEFAULT;

	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
		device_config->vp_config[i].vp_id = i;

		device_config->vp_config[i].min_bandwidth =
				VXGE_HW_VPATH_BANDWIDTH_DEFAULT;

		device_config->vp_config[i].ring.enable = VXGE_HW_RING_DEFAULT;

		device_config->vp_config[i].ring.ring_blocks =
				VXGE_HW_DEF_RING_BLOCKS;

		device_config->vp_config[i].ring.buffer_mode =
				VXGE_HW_RING_RXD_BUFFER_MODE_DEFAULT;

		device_config->vp_config[i].ring.scatter_mode =
				VXGE_HW_RING_SCATTER_MODE_USE_FLASH_DEFAULT;

		device_config->vp_config[i].ring.rxds_limit =
				VXGE_HW_DEF_RING_RXDS_LIMIT;

		device_config->vp_config[i].fअगरo.enable = VXGE_HW_FIFO_ENABLE;

		device_config->vp_config[i].fअगरo.fअगरo_blocks =
				VXGE_HW_MIN_FIFO_BLOCKS;

		device_config->vp_config[i].fअगरo.max_frags =
				VXGE_HW_MAX_FIFO_FRAGS;

		device_config->vp_config[i].fअगरo.memblock_size =
				VXGE_HW_DEF_FIFO_MEMBLOCK_SIZE;

		device_config->vp_config[i].fअगरo.alignment_size =
				VXGE_HW_DEF_FIFO_ALIGNMENT_SIZE;

		device_config->vp_config[i].fअगरo.पूर्णांकr =
				VXGE_HW_FIFO_QUEUE_INTR_DEFAULT;

		device_config->vp_config[i].fअगरo.no_snoop_bits =
				VXGE_HW_FIFO_NO_SNOOP_DEFAULT;
		device_config->vp_config[i].tti.पूर्णांकr_enable =
				VXGE_HW_TIM_INTR_DEFAULT;

		device_config->vp_config[i].tti.bसमयr_val =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].tti.समयr_ac_en =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].tti.समयr_ci_en =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].tti.समयr_ri_en =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].tti.rसमयr_val =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].tti.util_sel =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].tti.lसमयr_val =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].tti.urange_a =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].tti.uec_a =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].tti.urange_b =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].tti.uec_b =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].tti.urange_c =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].tti.uec_c =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].tti.uec_d =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].rti.पूर्णांकr_enable =
				VXGE_HW_TIM_INTR_DEFAULT;

		device_config->vp_config[i].rti.bसमयr_val =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].rti.समयr_ac_en =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].rti.समयr_ci_en =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].rti.समयr_ri_en =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].rti.rसमयr_val =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].rti.util_sel =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].rti.lसमयr_val =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].rti.urange_a =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].rti.uec_a =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].rti.urange_b =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].rti.uec_b =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].rti.urange_c =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].rti.uec_c =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].rti.uec_d =
				VXGE_HW_USE_FLASH_DEFAULT;

		device_config->vp_config[i].mtu =
				VXGE_HW_VPATH_USE_FLASH_DEFAULT_INITIAL_MTU;

		device_config->vp_config[i].rpa_strip_vlan_tag =
			VXGE_HW_VPATH_RPA_STRIP_VLAN_TAG_USE_FLASH_DEFAULT;
	पूर्ण

	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_vpath_swapper_set - Set the swapper bits क्रम the vpath.
 * Set the swapper bits appropriately क्रम the vpath.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_swapper_set(काष्ठा vxge_hw_vpath_reg __iomem *vpath_reg)
अणु
#अगर_अघोषित __BIG_ENDIAN
	u64 val64;

	val64 = पढ़ोq(&vpath_reg->vpath_general_cfg1);
	wmb();
	val64 |= VXGE_HW_VPATH_GENERAL_CFG1_CTL_BYTE_SWAPEN;
	ग_लिखोq(val64, &vpath_reg->vpath_general_cfg1);
	wmb();
#पूर्ण_अगर
	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_kdfc_swapper_set - Set the swapper bits क्रम the kdfc.
 * Set the swapper bits appropriately क्रम the vpath.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_kdfc_swapper_set(काष्ठा vxge_hw_legacy_reg __iomem *legacy_reg,
			   काष्ठा vxge_hw_vpath_reg __iomem *vpath_reg)
अणु
	u64 val64;

	val64 = पढ़ोq(&legacy_reg->pअगरm_wr_swap_en);

	अगर (val64 == VXGE_HW_SWAPPER_WRITE_BYTE_SWAP_ENABLE) अणु
		val64 = पढ़ोq(&vpath_reg->kdfcctl_cfg0);
		wmb();

		val64 |= VXGE_HW_KDFCCTL_CFG0_BYTE_SWAPEN_FIFO0	|
			VXGE_HW_KDFCCTL_CFG0_BYTE_SWAPEN_FIFO1	|
			VXGE_HW_KDFCCTL_CFG0_BYTE_SWAPEN_FIFO2;

		ग_लिखोq(val64, &vpath_reg->kdfcctl_cfg0);
		wmb();
	पूर्ण

	वापस VXGE_HW_OK;
पूर्ण

/*
 * vxge_hw_mgmt_reg_पढ़ो - Read Titan रेजिस्टर.
 */
क्रमागत vxge_hw_status
vxge_hw_mgmt_reg_पढ़ो(काष्ठा __vxge_hw_device *hldev,
		      क्रमागत vxge_hw_mgmt_reg_type type,
		      u32 index, u32 offset, u64 *value)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर ((hldev == शून्य) || (hldev->magic != VXGE_HW_DEVICE_MAGIC)) अणु
		status = VXGE_HW_ERR_INVALID_DEVICE;
		जाओ निकास;
	पूर्ण

	चयन (type) अणु
	हाल vxge_hw_mgmt_reg_type_legacy:
		अगर (offset > माप(काष्ठा vxge_hw_legacy_reg) - 8) अणु
			status = VXGE_HW_ERR_INVALID_OFFSET;
			अवरोध;
		पूर्ण
		*value = पढ़ोq((व्योम __iomem *)hldev->legacy_reg + offset);
		अवरोध;
	हाल vxge_hw_mgmt_reg_type_toc:
		अगर (offset > माप(काष्ठा vxge_hw_toc_reg) - 8) अणु
			status = VXGE_HW_ERR_INVALID_OFFSET;
			अवरोध;
		पूर्ण
		*value = पढ़ोq((व्योम __iomem *)hldev->toc_reg + offset);
		अवरोध;
	हाल vxge_hw_mgmt_reg_type_common:
		अगर (offset > माप(काष्ठा vxge_hw_common_reg) - 8) अणु
			status = VXGE_HW_ERR_INVALID_OFFSET;
			अवरोध;
		पूर्ण
		*value = पढ़ोq((व्योम __iomem *)hldev->common_reg + offset);
		अवरोध;
	हाल vxge_hw_mgmt_reg_type_mrpcim:
		अगर (!(hldev->access_rights &
			VXGE_HW_DEVICE_ACCESS_RIGHT_MRPCIM)) अणु
			status = VXGE_HW_ERR_PRIVILEGED_OPERATION;
			अवरोध;
		पूर्ण
		अगर (offset > माप(काष्ठा vxge_hw_mrpcim_reg) - 8) अणु
			status = VXGE_HW_ERR_INVALID_OFFSET;
			अवरोध;
		पूर्ण
		*value = पढ़ोq((व्योम __iomem *)hldev->mrpcim_reg + offset);
		अवरोध;
	हाल vxge_hw_mgmt_reg_type_srpcim:
		अगर (!(hldev->access_rights &
			VXGE_HW_DEVICE_ACCESS_RIGHT_SRPCIM)) अणु
			status = VXGE_HW_ERR_PRIVILEGED_OPERATION;
			अवरोध;
		पूर्ण
		अगर (index > VXGE_HW_TITAN_SRPCIM_REG_SPACES - 1) अणु
			status = VXGE_HW_ERR_INVALID_INDEX;
			अवरोध;
		पूर्ण
		अगर (offset > माप(काष्ठा vxge_hw_srpcim_reg) - 8) अणु
			status = VXGE_HW_ERR_INVALID_OFFSET;
			अवरोध;
		पूर्ण
		*value = पढ़ोq((व्योम __iomem *)hldev->srpcim_reg[index] +
				offset);
		अवरोध;
	हाल vxge_hw_mgmt_reg_type_vpmgmt:
		अगर ((index > VXGE_HW_TITAN_VPMGMT_REG_SPACES - 1) ||
			(!(hldev->vpath_assignments & vxge_mBIT(index)))) अणु
			status = VXGE_HW_ERR_INVALID_INDEX;
			अवरोध;
		पूर्ण
		अगर (offset > माप(काष्ठा vxge_hw_vpmgmt_reg) - 8) अणु
			status = VXGE_HW_ERR_INVALID_OFFSET;
			अवरोध;
		पूर्ण
		*value = पढ़ोq((व्योम __iomem *)hldev->vpmgmt_reg[index] +
				offset);
		अवरोध;
	हाल vxge_hw_mgmt_reg_type_vpath:
		अगर ((index > VXGE_HW_TITAN_VPATH_REG_SPACES - 1) ||
			(!(hldev->vpath_assignments & vxge_mBIT(index)))) अणु
			status = VXGE_HW_ERR_INVALID_INDEX;
			अवरोध;
		पूर्ण
		अगर (index > VXGE_HW_TITAN_VPATH_REG_SPACES - 1) अणु
			status = VXGE_HW_ERR_INVALID_INDEX;
			अवरोध;
		पूर्ण
		अगर (offset > माप(काष्ठा vxge_hw_vpath_reg) - 8) अणु
			status = VXGE_HW_ERR_INVALID_OFFSET;
			अवरोध;
		पूर्ण
		*value = पढ़ोq((व्योम __iomem *)hldev->vpath_reg[index] +
				offset);
		अवरोध;
	शेष:
		status = VXGE_HW_ERR_INVALID_TYPE;
		अवरोध;
	पूर्ण

निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_vpath_strip_fcs_check - Check क्रम FCS strip.
 */
क्रमागत vxge_hw_status
vxge_hw_vpath_strip_fcs_check(काष्ठा __vxge_hw_device *hldev, u64 vpath_mask)
अणु
	काष्ठा vxge_hw_vpmgmt_reg       __iomem *vpmgmt_reg;
	पूर्णांक i = 0, j = 0;

	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
		अगर (!((vpath_mask) & vxge_mBIT(i)))
			जारी;
		vpmgmt_reg = hldev->vpmgmt_reg[i];
		क्रम (j = 0; j < VXGE_HW_MAC_MAX_MAC_PORT_ID; j++) अणु
			अगर (पढ़ोq(&vpmgmt_reg->rxmac_cfg0_port_vpmgmt_clone[j])
			& VXGE_HW_RXMAC_CFG0_PORT_VPMGMT_CLONE_STRIP_FCS)
				वापस VXGE_HW_FAIL;
		पूर्ण
	पूर्ण
	वापस VXGE_HW_OK;
पूर्ण
/*
 * vxge_hw_mgmt_reg_Write - Write Titan रेजिस्टर.
 */
क्रमागत vxge_hw_status
vxge_hw_mgmt_reg_ग_लिखो(काष्ठा __vxge_hw_device *hldev,
		      क्रमागत vxge_hw_mgmt_reg_type type,
		      u32 index, u32 offset, u64 value)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर ((hldev == शून्य) || (hldev->magic != VXGE_HW_DEVICE_MAGIC)) अणु
		status = VXGE_HW_ERR_INVALID_DEVICE;
		जाओ निकास;
	पूर्ण

	चयन (type) अणु
	हाल vxge_hw_mgmt_reg_type_legacy:
		अगर (offset > माप(काष्ठा vxge_hw_legacy_reg) - 8) अणु
			status = VXGE_HW_ERR_INVALID_OFFSET;
			अवरोध;
		पूर्ण
		ग_लिखोq(value, (व्योम __iomem *)hldev->legacy_reg + offset);
		अवरोध;
	हाल vxge_hw_mgmt_reg_type_toc:
		अगर (offset > माप(काष्ठा vxge_hw_toc_reg) - 8) अणु
			status = VXGE_HW_ERR_INVALID_OFFSET;
			अवरोध;
		पूर्ण
		ग_लिखोq(value, (व्योम __iomem *)hldev->toc_reg + offset);
		अवरोध;
	हाल vxge_hw_mgmt_reg_type_common:
		अगर (offset > माप(काष्ठा vxge_hw_common_reg) - 8) अणु
			status = VXGE_HW_ERR_INVALID_OFFSET;
			अवरोध;
		पूर्ण
		ग_लिखोq(value, (व्योम __iomem *)hldev->common_reg + offset);
		अवरोध;
	हाल vxge_hw_mgmt_reg_type_mrpcim:
		अगर (!(hldev->access_rights &
			VXGE_HW_DEVICE_ACCESS_RIGHT_MRPCIM)) अणु
			status = VXGE_HW_ERR_PRIVILEGED_OPERATION;
			अवरोध;
		पूर्ण
		अगर (offset > माप(काष्ठा vxge_hw_mrpcim_reg) - 8) अणु
			status = VXGE_HW_ERR_INVALID_OFFSET;
			अवरोध;
		पूर्ण
		ग_लिखोq(value, (व्योम __iomem *)hldev->mrpcim_reg + offset);
		अवरोध;
	हाल vxge_hw_mgmt_reg_type_srpcim:
		अगर (!(hldev->access_rights &
			VXGE_HW_DEVICE_ACCESS_RIGHT_SRPCIM)) अणु
			status = VXGE_HW_ERR_PRIVILEGED_OPERATION;
			अवरोध;
		पूर्ण
		अगर (index > VXGE_HW_TITAN_SRPCIM_REG_SPACES - 1) अणु
			status = VXGE_HW_ERR_INVALID_INDEX;
			अवरोध;
		पूर्ण
		अगर (offset > माप(काष्ठा vxge_hw_srpcim_reg) - 8) अणु
			status = VXGE_HW_ERR_INVALID_OFFSET;
			अवरोध;
		पूर्ण
		ग_लिखोq(value, (व्योम __iomem *)hldev->srpcim_reg[index] +
			offset);

		अवरोध;
	हाल vxge_hw_mgmt_reg_type_vpmgmt:
		अगर ((index > VXGE_HW_TITAN_VPMGMT_REG_SPACES - 1) ||
			(!(hldev->vpath_assignments & vxge_mBIT(index)))) अणु
			status = VXGE_HW_ERR_INVALID_INDEX;
			अवरोध;
		पूर्ण
		अगर (offset > माप(काष्ठा vxge_hw_vpmgmt_reg) - 8) अणु
			status = VXGE_HW_ERR_INVALID_OFFSET;
			अवरोध;
		पूर्ण
		ग_लिखोq(value, (व्योम __iomem *)hldev->vpmgmt_reg[index] +
			offset);
		अवरोध;
	हाल vxge_hw_mgmt_reg_type_vpath:
		अगर ((index > VXGE_HW_TITAN_VPATH_REG_SPACES-1) ||
			(!(hldev->vpath_assignments & vxge_mBIT(index)))) अणु
			status = VXGE_HW_ERR_INVALID_INDEX;
			अवरोध;
		पूर्ण
		अगर (offset > माप(काष्ठा vxge_hw_vpath_reg) - 8) अणु
			status = VXGE_HW_ERR_INVALID_OFFSET;
			अवरोध;
		पूर्ण
		ग_लिखोq(value, (व्योम __iomem *)hldev->vpath_reg[index] +
			offset);
		अवरोध;
	शेष:
		status = VXGE_HW_ERR_INVALID_TYPE;
		अवरोध;
	पूर्ण
निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_fअगरo_पात - Returns the TxD
 * This function terminates the TxDs of fअगरo
 */
अटल क्रमागत vxge_hw_status __vxge_hw_fअगरo_पात(काष्ठा __vxge_hw_fअगरo *fअगरo)
अणु
	व्योम *txdlh;

	क्रम (;;) अणु
		vxge_hw_channel_dtr_try_complete(&fअगरo->channel, &txdlh);

		अगर (txdlh == शून्य)
			अवरोध;

		vxge_hw_channel_dtr_complete(&fअगरo->channel);

		अगर (fअगरo->txdl_term) अणु
			fअगरo->txdl_term(txdlh,
			VXGE_HW_TXDL_STATE_POSTED,
			fअगरo->channel.userdata);
		पूर्ण

		vxge_hw_channel_dtr_मुक्त(&fअगरo->channel, txdlh);
	पूर्ण

	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_fअगरo_reset - Resets the fअगरo
 * This function resets the fअगरo during vpath reset operation
 */
अटल क्रमागत vxge_hw_status __vxge_hw_fअगरo_reset(काष्ठा __vxge_hw_fअगरo *fअगरo)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	__vxge_hw_fअगरo_पात(fअगरo);
	status = __vxge_hw_channel_reset(&fअगरo->channel);

	वापस status;
पूर्ण

/*
 * __vxge_hw_fअगरo_delete - Removes the FIFO
 * This function मुक्तup the memory pool and हटाओs the FIFO
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_fअगरo_delete(काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	काष्ठा __vxge_hw_fअगरo *fअगरo = vp->vpath->fअगरoh;

	__vxge_hw_fअगरo_पात(fअगरo);

	अगर (fअगरo->mempool)
		__vxge_hw_mempool_destroy(fअगरo->mempool);

	vp->vpath->fअगरoh = शून्य;

	__vxge_hw_channel_मुक्त(&fअगरo->channel);

	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_fअगरo_mempool_item_alloc - Allocate List blocks क्रम TxD
 * list callback
 * This function is callback passed to __vxge_hw_mempool_create to create memory
 * pool क्रम TxD list
 */
अटल व्योम
__vxge_hw_fअगरo_mempool_item_alloc(
	काष्ठा vxge_hw_mempool *mempoolh,
	u32 memblock_index, काष्ठा vxge_hw_mempool_dma *dma_object,
	u32 index, u32 is_last)
अणु
	u32 memblock_item_idx;
	काष्ठा __vxge_hw_fअगरo_txdl_priv *txdl_priv;
	काष्ठा vxge_hw_fअगरo_txd *txdp =
		(काष्ठा vxge_hw_fअगरo_txd *)mempoolh->items_arr[index];
	काष्ठा __vxge_hw_fअगरo *fअगरo =
			(काष्ठा __vxge_hw_fअगरo *)mempoolh->userdata;
	व्योम *memblock = mempoolh->memblocks_arr[memblock_index];

	vxge_निश्चित(txdp);

	txdp->host_control = (u64) (माप_प्रकार)
	__vxge_hw_mempool_item_priv(mempoolh, memblock_index, txdp,
					&memblock_item_idx);

	txdl_priv = __vxge_hw_fअगरo_txdl_priv(fअगरo, txdp);

	vxge_निश्चित(txdl_priv);

	fअगरo->channel.reserve_arr[fअगरo->channel.reserve_ptr - 1 - index] = txdp;

	/* pre-क्रमmat HW's TxDL's निजी */
	txdl_priv->dma_offset = (अक्षर *)txdp - (अक्षर *)memblock;
	txdl_priv->dma_addr = dma_object->addr + txdl_priv->dma_offset;
	txdl_priv->dma_handle = dma_object->handle;
	txdl_priv->memblock   = memblock;
	txdl_priv->first_txdp = txdp;
	txdl_priv->next_txdl_priv = शून्य;
	txdl_priv->alloc_frags = 0;
पूर्ण

/*
 * __vxge_hw_fअगरo_create - Create a FIFO
 * This function creates FIFO and initializes it.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_fअगरo_create(काष्ठा __vxge_hw_vpath_handle *vp,
		      काष्ठा vxge_hw_fअगरo_attr *attr)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा __vxge_hw_fअगरo *fअगरo;
	काष्ठा vxge_hw_fअगरo_config *config;
	u32 txdl_size, txdl_per_memblock;
	काष्ठा vxge_hw_mempool_cbs fअगरo_mp_callback;
	काष्ठा __vxge_hw_भवpath *vpath;

	अगर ((vp == शून्य) || (attr == शून्य)) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण
	vpath = vp->vpath;
	config = &vpath->hldev->config.vp_config[vpath->vp_id].fअगरo;

	txdl_size = config->max_frags * माप(काष्ठा vxge_hw_fअगरo_txd);

	txdl_per_memblock = config->memblock_size / txdl_size;

	fअगरo = (काष्ठा __vxge_hw_fअगरo *)__vxge_hw_channel_allocate(vp,
					VXGE_HW_CHANNEL_TYPE_FIFO,
					config->fअगरo_blocks * txdl_per_memblock,
					attr->per_txdl_space, attr->userdata);

	अगर (fअगरo == शून्य) अणु
		status = VXGE_HW_ERR_OUT_OF_MEMORY;
		जाओ निकास;
	पूर्ण

	vpath->fअगरoh = fअगरo;
	fअगरo->nofl_db = vpath->nofl_db;

	fअगरo->vp_id = vpath->vp_id;
	fअगरo->vp_reg = vpath->vp_reg;
	fअगरo->stats = &vpath->sw_stats->fअगरo_stats;

	fअगरo->config = config;

	/* apply "interrupts per txdl" attribute */
	fअगरo->पूर्णांकerrupt_type = VXGE_HW_FIFO_TXD_INT_TYPE_UTILZ;
	fअगरo->tim_tti_cfg1_saved = vpath->tim_tti_cfg1_saved;
	fअगरo->tim_tti_cfg3_saved = vpath->tim_tti_cfg3_saved;

	अगर (fअगरo->config->पूर्णांकr)
		fअगरo->पूर्णांकerrupt_type = VXGE_HW_FIFO_TXD_INT_TYPE_PER_LIST;

	fअगरo->no_snoop_bits = config->no_snoop_bits;

	/*
	 * FIFO memory management strategy:
	 *
	 * TxDL split पूर्णांकo three independent parts:
	 *	- set of TxD's
	 *	- TxD HW निजी part
	 *	- driver निजी part
	 *
	 * Adaptative memory allocation used. i.e. Memory allocated on
	 * demand with the size which will fit पूर्णांकo one memory block.
	 * One memory block may contain more than one TxDL.
	 *
	 * During "reserve" operations more memory can be allocated on demand
	 * क्रम example due to FIFO full condition.
	 *
	 * Pool of memory memblocks never shrinks except in __vxge_hw_fअगरo_बंद
	 * routine which will essentially stop the channel and मुक्त resources.
	 */

	/* TxDL common निजी size == TxDL निजी  +  driver निजी */
	fअगरo->priv_size =
		माप(काष्ठा __vxge_hw_fअगरo_txdl_priv) + attr->per_txdl_space;
	fअगरo->priv_size = ((fअगरo->priv_size  +  VXGE_CACHE_LINE_SIZE - 1) /
			VXGE_CACHE_LINE_SIZE) * VXGE_CACHE_LINE_SIZE;

	fअगरo->per_txdl_space = attr->per_txdl_space;

	/* recompute txdl size to be cacheline aligned */
	fअगरo->txdl_size = txdl_size;
	fअगरo->txdl_per_memblock = txdl_per_memblock;

	fअगरo->txdl_term = attr->txdl_term;
	fअगरo->callback = attr->callback;

	अगर (fअगरo->txdl_per_memblock == 0) अणु
		__vxge_hw_fअगरo_delete(vp);
		status = VXGE_HW_ERR_INVALID_BLOCK_SIZE;
		जाओ निकास;
	पूर्ण

	fअगरo_mp_callback.item_func_alloc = __vxge_hw_fअगरo_mempool_item_alloc;

	fअगरo->mempool =
		__vxge_hw_mempool_create(vpath->hldev,
			fअगरo->config->memblock_size,
			fअगरo->txdl_size,
			fअगरo->priv_size,
			(fअगरo->config->fअगरo_blocks * fअगरo->txdl_per_memblock),
			(fअगरo->config->fअगरo_blocks * fअगरo->txdl_per_memblock),
			&fअगरo_mp_callback,
			fअगरo);

	अगर (fअगरo->mempool == शून्य) अणु
		__vxge_hw_fअगरo_delete(vp);
		status = VXGE_HW_ERR_OUT_OF_MEMORY;
		जाओ निकास;
	पूर्ण

	status = __vxge_hw_channel_initialize(&fअगरo->channel);
	अगर (status != VXGE_HW_OK) अणु
		__vxge_hw_fअगरo_delete(vp);
		जाओ निकास;
	पूर्ण

	vxge_निश्चित(fअगरo->channel.reserve_ptr);
निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_vpath_pci_पढ़ो - Read the content of given address
 *                          in pci config space.
 * Read from the vpath pci config space.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_pci_पढ़ो(काष्ठा __vxge_hw_भवpath *vpath,
			 u32 phy_func_0, u32 offset, u32 *val)
अणु
	u64 val64;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा vxge_hw_vpath_reg __iomem *vp_reg = vpath->vp_reg;

	val64 =	VXGE_HW_PCI_CONFIG_ACCESS_CFG1_ADDRESS(offset);

	अगर (phy_func_0)
		val64 |= VXGE_HW_PCI_CONFIG_ACCESS_CFG1_SEL_FUNC0;

	ग_लिखोq(val64, &vp_reg->pci_config_access_cfg1);
	wmb();
	ग_लिखोq(VXGE_HW_PCI_CONFIG_ACCESS_CFG2_REQ,
			&vp_reg->pci_config_access_cfg2);
	wmb();

	status = __vxge_hw_device_रेजिस्टर_poll(
			&vp_reg->pci_config_access_cfg2,
			VXGE_HW_INTR_MASK_ALL, VXGE_HW_DEF_DEVICE_POLL_MILLIS);

	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	val64 = पढ़ोq(&vp_reg->pci_config_access_status);

	अगर (val64 & VXGE_HW_PCI_CONFIG_ACCESS_STATUS_ACCESS_ERR) अणु
		status = VXGE_HW_FAIL;
		*val = 0;
	पूर्ण अन्यथा
		*val = (u32)vxge_bVALn(val64, 32, 32);
निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_device_flick_link_led - Flick (blink) link LED.
 * @hldev: HW device.
 * @on_off: TRUE अगर flickering to be on, FALSE to be off
 *
 * Flicker the link LED.
 */
क्रमागत vxge_hw_status
vxge_hw_device_flick_link_led(काष्ठा __vxge_hw_device *hldev, u64 on_off)
अणु
	काष्ठा __vxge_hw_भवpath *vpath;
	u64 data0, data1 = 0, steer_ctrl = 0;
	क्रमागत vxge_hw_status status;

	अगर (hldev == शून्य) अणु
		status = VXGE_HW_ERR_INVALID_DEVICE;
		जाओ निकास;
	पूर्ण

	vpath = &hldev->भव_paths[hldev->first_vp_id];

	data0 = on_off;
	status = vxge_hw_vpath_fw_api(vpath,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_LED_CONTROL,
			VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_FW_MEMO,
			0, &data0, &data1, &steer_ctrl);
निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_vpath_rts_table_get - Get the entries from RTS access tables
 */
क्रमागत vxge_hw_status
__vxge_hw_vpath_rts_table_get(काष्ठा __vxge_hw_vpath_handle *vp,
			      u32 action, u32 rts_table, u32 offset,
			      u64 *data0, u64 *data1)
अणु
	क्रमागत vxge_hw_status status;
	u64 steer_ctrl = 0;

	अगर (vp == शून्य) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	अगर ((rts_table ==
	     VXGE_HW_RTS_ACS_STEER_CTRL_DATA_STRUCT_SEL_RTH_SOLO_IT) ||
	    (rts_table ==
	     VXGE_HW_RTS_ACS_STEER_CTRL_DATA_STRUCT_SEL_RTH_MULTI_IT) ||
	    (rts_table ==
	     VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_RTH_MASK) ||
	    (rts_table ==
	     VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_RTH_KEY)) अणु
		steer_ctrl = VXGE_HW_RTS_ACCESS_STEER_CTRL_TABLE_SEL;
	पूर्ण

	status = vxge_hw_vpath_fw_api(vp->vpath, action, rts_table, offset,
				      data0, data1, &steer_ctrl);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	अगर ((rts_table != VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_DA) &&
	    (rts_table !=
	     VXGE_HW_RTS_ACS_STEER_CTRL_DATA_STRUCT_SEL_RTH_MULTI_IT))
		*data1 = 0;
निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_vpath_rts_table_set - Set the entries of RTS access tables
 */
क्रमागत vxge_hw_status
__vxge_hw_vpath_rts_table_set(काष्ठा __vxge_hw_vpath_handle *vp, u32 action,
			      u32 rts_table, u32 offset, u64 steer_data0,
			      u64 steer_data1)
अणु
	u64 data0, data1 = 0, steer_ctrl = 0;
	क्रमागत vxge_hw_status status;

	अगर (vp == शून्य) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	data0 = steer_data0;

	अगर ((rts_table == VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_DA) ||
	    (rts_table ==
	     VXGE_HW_RTS_ACS_STEER_CTRL_DATA_STRUCT_SEL_RTH_MULTI_IT))
		data1 = steer_data1;

	status = vxge_hw_vpath_fw_api(vp->vpath, action, rts_table, offset,
				      &data0, &data1, &steer_ctrl);
निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_vpath_rts_rth_set - Set/configure RTS hashing.
 */
क्रमागत vxge_hw_status vxge_hw_vpath_rts_rth_set(
			काष्ठा __vxge_hw_vpath_handle *vp,
			क्रमागत vxge_hw_rth_algoriपंचांगs algorithm,
			काष्ठा vxge_hw_rth_hash_types *hash_type,
			u16 bucket_size)
अणु
	u64 data0, data1;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर (vp == शून्य) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	status = __vxge_hw_vpath_rts_table_get(vp,
		     VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_READ_ENTRY,
		     VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_RTH_GEN_CFG,
			0, &data0, &data1);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	data0 &= ~(VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_GEN_BUCKET_SIZE(0xf) |
			VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_GEN_ALG_SEL(0x3));

	data0 |= VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_GEN_RTH_EN |
	VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_GEN_BUCKET_SIZE(bucket_size) |
	VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_GEN_ALG_SEL(algorithm);

	अगर (hash_type->hash_type_tcpipv4_en)
		data0 |= VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_GEN_RTH_TCP_IPV4_EN;

	अगर (hash_type->hash_type_ipv4_en)
		data0 |= VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_GEN_RTH_IPV4_EN;

	अगर (hash_type->hash_type_tcpipv6_en)
		data0 |= VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_GEN_RTH_TCP_IPV6_EN;

	अगर (hash_type->hash_type_ipv6_en)
		data0 |= VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_GEN_RTH_IPV6_EN;

	अगर (hash_type->hash_type_tcpipv6ex_en)
		data0 |=
		VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_GEN_RTH_TCP_IPV6_EX_EN;

	अगर (hash_type->hash_type_ipv6ex_en)
		data0 |= VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_GEN_RTH_IPV6_EX_EN;

	अगर (VXGE_HW_RTS_ACCESS_STEER_DATA0_GET_RTH_GEN_ACTIVE_TABLE(data0))
		data0 &= ~VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_GEN_ACTIVE_TABLE;
	अन्यथा
		data0 |= VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_GEN_ACTIVE_TABLE;

	status = __vxge_hw_vpath_rts_table_set(vp,
		VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_WRITE_ENTRY,
		VXGE_HW_RTS_ACCESS_STEER_CTRL_DATA_STRUCT_SEL_RTH_GEN_CFG,
		0, data0, 0);
निकास:
	वापस status;
पूर्ण

अटल व्योम
vxge_hw_rts_rth_data0_data1_get(u32 j, u64 *data0, u64 *data1,
				u16 flag, u8 *itable)
अणु
	चयन (flag) अणु
	हाल 1:
		*data0 = VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_ITEM0_BUCKET_NUM(j)|
			VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_ITEM0_ENTRY_EN |
			VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_ITEM0_BUCKET_DATA(
			itable[j]);
		fallthrough;
	हाल 2:
		*data0 |=
			VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_ITEM1_BUCKET_NUM(j)|
			VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_ITEM1_ENTRY_EN |
			VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_ITEM1_BUCKET_DATA(
			itable[j]);
		fallthrough;
	हाल 3:
		*data1 = VXGE_HW_RTS_ACCESS_STEER_DATA1_RTH_ITEM0_BUCKET_NUM(j)|
			VXGE_HW_RTS_ACCESS_STEER_DATA1_RTH_ITEM0_ENTRY_EN |
			VXGE_HW_RTS_ACCESS_STEER_DATA1_RTH_ITEM0_BUCKET_DATA(
			itable[j]);
		fallthrough;
	हाल 4:
		*data1 |=
			VXGE_HW_RTS_ACCESS_STEER_DATA1_RTH_ITEM1_BUCKET_NUM(j)|
			VXGE_HW_RTS_ACCESS_STEER_DATA1_RTH_ITEM1_ENTRY_EN |
			VXGE_HW_RTS_ACCESS_STEER_DATA1_RTH_ITEM1_BUCKET_DATA(
			itable[j]);
	शेष:
		वापस;
	पूर्ण
पूर्ण
/*
 * vxge_hw_vpath_rts_rth_itable_set - Set/configure indirection table (IT).
 */
क्रमागत vxge_hw_status vxge_hw_vpath_rts_rth_itable_set(
			काष्ठा __vxge_hw_vpath_handle **vpath_handles,
			u32 vpath_count,
			u8 *mtable,
			u8 *itable,
			u32 itable_size)
अणु
	u32 i, j, action, rts_table;
	u64 data0;
	u64 data1;
	u32 max_entries;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा __vxge_hw_vpath_handle *vp = vpath_handles[0];

	अगर (vp == शून्य) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण

	max_entries = (((u32)1) << itable_size);

	अगर (vp->vpath->hldev->config.rth_it_type
				== VXGE_HW_RTH_IT_TYPE_SOLO_IT) अणु
		action = VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_WRITE_ENTRY;
		rts_table =
			VXGE_HW_RTS_ACS_STEER_CTRL_DATA_STRUCT_SEL_RTH_SOLO_IT;

		क्रम (j = 0; j < max_entries; j++) अणु

			data1 = 0;

			data0 =
			VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_SOLO_IT_BUCKET_DATA(
				itable[j]);

			status = __vxge_hw_vpath_rts_table_set(vpath_handles[0],
				action, rts_table, j, data0, data1);

			अगर (status != VXGE_HW_OK)
				जाओ निकास;
		पूर्ण

		क्रम (j = 0; j < max_entries; j++) अणु

			data1 = 0;

			data0 =
			VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_SOLO_IT_ENTRY_EN |
			VXGE_HW_RTS_ACCESS_STEER_DATA0_RTH_SOLO_IT_BUCKET_DATA(
				itable[j]);

			status = __vxge_hw_vpath_rts_table_set(
				vpath_handles[mtable[itable[j]]], action,
				rts_table, j, data0, data1);

			अगर (status != VXGE_HW_OK)
				जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		action = VXGE_HW_RTS_ACCESS_STEER_CTRL_ACTION_WRITE_ENTRY;
		rts_table =
			VXGE_HW_RTS_ACS_STEER_CTRL_DATA_STRUCT_SEL_RTH_MULTI_IT;
		क्रम (i = 0; i < vpath_count; i++) अणु

			क्रम (j = 0; j < max_entries;) अणु

				data0 = 0;
				data1 = 0;

				जबतक (j < max_entries) अणु
					अगर (mtable[itable[j]] != i) अणु
						j++;
						जारी;
					पूर्ण
					vxge_hw_rts_rth_data0_data1_get(j,
						&data0, &data1, 1, itable);
					j++;
					अवरोध;
				पूर्ण

				जबतक (j < max_entries) अणु
					अगर (mtable[itable[j]] != i) अणु
						j++;
						जारी;
					पूर्ण
					vxge_hw_rts_rth_data0_data1_get(j,
						&data0, &data1, 2, itable);
					j++;
					अवरोध;
				पूर्ण

				जबतक (j < max_entries) अणु
					अगर (mtable[itable[j]] != i) अणु
						j++;
						जारी;
					पूर्ण
					vxge_hw_rts_rth_data0_data1_get(j,
						&data0, &data1, 3, itable);
					j++;
					अवरोध;
				पूर्ण

				जबतक (j < max_entries) अणु
					अगर (mtable[itable[j]] != i) अणु
						j++;
						जारी;
					पूर्ण
					vxge_hw_rts_rth_data0_data1_get(j,
						&data0, &data1, 4, itable);
					j++;
					अवरोध;
				पूर्ण

				अगर (data0 != 0) अणु
					status = __vxge_hw_vpath_rts_table_set(
							vpath_handles[i],
							action, rts_table,
							0, data0, data1);

					अगर (status != VXGE_HW_OK)
						जाओ निकास;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
निकास:
	वापस status;
पूर्ण

/**
 * vxge_hw_vpath_check_leak - Check क्रम memory leak
 * @ring: Handle to the ring object used क्रम receive
 *
 * If PRC_RXD_DOORBELL_VPn.NEW_QW_CNT is larger or equal to
 * PRC_CFG6_VPn.RXD_SPAT then a leak has occurred.
 * Returns: VXGE_HW_FAIL, अगर leak has occurred.
 *
 */
क्रमागत vxge_hw_status
vxge_hw_vpath_check_leak(काष्ठा __vxge_hw_ring *ring)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	u64 rxd_new_count, rxd_spat;

	अगर (ring == शून्य)
		वापस status;

	rxd_new_count = पढ़ोl(&ring->vp_reg->prc_rxd_करोorbell);
	rxd_spat = पढ़ोq(&ring->vp_reg->prc_cfg6);
	rxd_spat = VXGE_HW_PRC_CFG6_RXD_SPAT(rxd_spat);

	अगर (rxd_new_count >= rxd_spat)
		status = VXGE_HW_FAIL;

	वापस status;
पूर्ण

/*
 * __vxge_hw_vpath_mgmt_पढ़ो
 * This routine पढ़ोs the vpath_mgmt रेजिस्टरs
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_mgmt_पढ़ो(
	काष्ठा __vxge_hw_device *hldev,
	काष्ठा __vxge_hw_भवpath *vpath)
अणु
	u32 i, mtu = 0, max_pyld = 0;
	u64 val64;

	क्रम (i = 0; i < VXGE_HW_MAC_MAX_MAC_PORT_ID; i++) अणु

		val64 = पढ़ोq(&vpath->vpmgmt_reg->
				rxmac_cfg0_port_vpmgmt_clone[i]);
		max_pyld =
			(u32)
			VXGE_HW_RXMAC_CFG0_PORT_VPMGMT_CLONE_GET_MAX_PYLD_LEN
			(val64);
		अगर (mtu < max_pyld)
			mtu = max_pyld;
	पूर्ण

	vpath->max_mtu = mtu + VXGE_HW_MAC_HEADER_MAX_SIZE;

	val64 = पढ़ोq(&vpath->vpmgmt_reg->xmac_vsport_choices_vp);

	क्रम (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) अणु
		अगर (val64 & vxge_mBIT(i))
			vpath->vsport_number = i;
	पूर्ण

	val64 = पढ़ोq(&vpath->vpmgmt_reg->xgmac_gen_status_vpmgmt_clone);

	अगर (val64 & VXGE_HW_XGMAC_GEN_STATUS_VPMGMT_CLONE_XMACJ_NTWK_OK)
		VXGE_HW_DEVICE_LINK_STATE_SET(vpath->hldev, VXGE_HW_LINK_UP);
	अन्यथा
		VXGE_HW_DEVICE_LINK_STATE_SET(vpath->hldev, VXGE_HW_LINK_DOWN);

	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_vpath_reset_check - Check अगर resetting the vpath completed
 * This routine checks the vpath_rst_in_prog रेजिस्टर to see अगर
 * adapter completed the reset process क्रम the vpath
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_reset_check(काष्ठा __vxge_hw_भवpath *vpath)
अणु
	क्रमागत vxge_hw_status status;

	status = __vxge_hw_device_रेजिस्टर_poll(
			&vpath->hldev->common_reg->vpath_rst_in_prog,
			VXGE_HW_VPATH_RST_IN_PROG_VPATH_RST_IN_PROG(
				1 << (16 - vpath->vp_id)),
			vpath->hldev->config.device_poll_millis);

	वापस status;
पूर्ण

/*
 * __vxge_hw_vpath_reset
 * This routine resets the vpath on the device
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_reset(काष्ठा __vxge_hw_device *hldev, u32 vp_id)
अणु
	u64 val64;

	val64 = VXGE_HW_CMN_RSTHDLR_CFG0_SW_RESET_VPATH(1 << (16 - vp_id));

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)vxge_bVALn(val64, 0, 32),
				&hldev->common_reg->cmn_rsthdlr_cfg0);

	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_vpath_sw_reset
 * This routine resets the vpath काष्ठाures
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_sw_reset(काष्ठा __vxge_hw_device *hldev, u32 vp_id)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा __vxge_hw_भवpath *vpath;

	vpath = &hldev->भव_paths[vp_id];

	अगर (vpath->ringh) अणु
		status = __vxge_hw_ring_reset(vpath->ringh);
		अगर (status != VXGE_HW_OK)
			जाओ निकास;
	पूर्ण

	अगर (vpath->fअगरoh)
		status = __vxge_hw_fअगरo_reset(vpath->fअगरoh);
निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_vpath_prc_configure
 * This routine configures the prc रेजिस्टरs of भव path using the config
 * passed
 */
अटल व्योम
__vxge_hw_vpath_prc_configure(काष्ठा __vxge_hw_device *hldev, u32 vp_id)
अणु
	u64 val64;
	काष्ठा __vxge_hw_भवpath *vpath;
	काष्ठा vxge_hw_vp_config *vp_config;
	काष्ठा vxge_hw_vpath_reg __iomem *vp_reg;

	vpath = &hldev->भव_paths[vp_id];
	vp_reg = vpath->vp_reg;
	vp_config = vpath->vp_config;

	अगर (vp_config->ring.enable == VXGE_HW_RING_DISABLE)
		वापस;

	val64 = पढ़ोq(&vp_reg->prc_cfg1);
	val64 |= VXGE_HW_PRC_CFG1_RTI_TINT_DISABLE;
	ग_लिखोq(val64, &vp_reg->prc_cfg1);

	val64 = पढ़ोq(&vpath->vp_reg->prc_cfg6);
	val64 |= VXGE_HW_PRC_CFG6_DOORBELL_MODE_EN;
	ग_लिखोq(val64, &vpath->vp_reg->prc_cfg6);

	val64 = पढ़ोq(&vp_reg->prc_cfg7);

	अगर (vpath->vp_config->ring.scatter_mode !=
		VXGE_HW_RING_SCATTER_MODE_USE_FLASH_DEFAULT) अणु

		val64 &= ~VXGE_HW_PRC_CFG7_SCATTER_MODE(0x3);

		चयन (vpath->vp_config->ring.scatter_mode) अणु
		हाल VXGE_HW_RING_SCATTER_MODE_A:
			val64 |= VXGE_HW_PRC_CFG7_SCATTER_MODE(
					VXGE_HW_PRC_CFG7_SCATTER_MODE_A);
			अवरोध;
		हाल VXGE_HW_RING_SCATTER_MODE_B:
			val64 |= VXGE_HW_PRC_CFG7_SCATTER_MODE(
					VXGE_HW_PRC_CFG7_SCATTER_MODE_B);
			अवरोध;
		हाल VXGE_HW_RING_SCATTER_MODE_C:
			val64 |= VXGE_HW_PRC_CFG7_SCATTER_MODE(
					VXGE_HW_PRC_CFG7_SCATTER_MODE_C);
			अवरोध;
		पूर्ण
	पूर्ण

	ग_लिखोq(val64, &vp_reg->prc_cfg7);

	ग_लिखोq(VXGE_HW_PRC_CFG5_RXD0_ADD(
				__vxge_hw_ring_first_block_address_get(
					vpath->ringh) >> 3), &vp_reg->prc_cfg5);

	val64 = पढ़ोq(&vp_reg->prc_cfg4);
	val64 |= VXGE_HW_PRC_CFG4_IN_SVC;
	val64 &= ~VXGE_HW_PRC_CFG4_RING_MODE(0x3);

	val64 |= VXGE_HW_PRC_CFG4_RING_MODE(
			VXGE_HW_PRC_CFG4_RING_MODE_ONE_BUFFER);

	अगर (hldev->config.rth_en == VXGE_HW_RTH_DISABLE)
		val64 |= VXGE_HW_PRC_CFG4_RTH_DISABLE;
	अन्यथा
		val64 &= ~VXGE_HW_PRC_CFG4_RTH_DISABLE;

	ग_लिखोq(val64, &vp_reg->prc_cfg4);
पूर्ण

/*
 * __vxge_hw_vpath_kdfc_configure
 * This routine configures the kdfc रेजिस्टरs of भव path using the
 * config passed
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_kdfc_configure(काष्ठा __vxge_hw_device *hldev, u32 vp_id)
अणु
	u64 val64;
	u64 vpath_stride;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा __vxge_hw_भवpath *vpath;
	काष्ठा vxge_hw_vpath_reg __iomem *vp_reg;

	vpath = &hldev->भव_paths[vp_id];
	vp_reg = vpath->vp_reg;
	status = __vxge_hw_kdfc_swapper_set(hldev->legacy_reg, vp_reg);

	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	val64 = पढ़ोq(&vp_reg->kdfc_drbl_triplet_total);

	vpath->max_kdfc_db =
		(u32)VXGE_HW_KDFC_DRBL_TRIPLET_TOTAL_GET_KDFC_MAX_SIZE(
			val64+1)/2;

	अगर (vpath->vp_config->fअगरo.enable == VXGE_HW_FIFO_ENABLE) अणु

		vpath->max_nofl_db = vpath->max_kdfc_db;

		अगर (vpath->max_nofl_db <
			((vpath->vp_config->fअगरo.memblock_size /
			(vpath->vp_config->fअगरo.max_frags *
			माप(काष्ठा vxge_hw_fअगरo_txd))) *
			vpath->vp_config->fअगरo.fअगरo_blocks)) अणु

			वापस VXGE_HW_BADCFG_FIFO_BLOCKS;
		पूर्ण
		val64 = VXGE_HW_KDFC_FIFO_TRPL_PARTITION_LENGTH_0(
				(vpath->max_nofl_db*2)-1);
	पूर्ण

	ग_लिखोq(val64, &vp_reg->kdfc_fअगरo_trpl_partition);

	ग_लिखोq(VXGE_HW_KDFC_FIFO_TRPL_CTRL_TRIPLET_ENABLE,
		&vp_reg->kdfc_fअगरo_trpl_ctrl);

	val64 = पढ़ोq(&vp_reg->kdfc_trpl_fअगरo_0_ctrl);

	val64 &= ~(VXGE_HW_KDFC_TRPL_FIFO_0_CTRL_MODE(0x3) |
		   VXGE_HW_KDFC_TRPL_FIFO_0_CTRL_SELECT(0xFF));

	val64 |= VXGE_HW_KDFC_TRPL_FIFO_0_CTRL_MODE(
		 VXGE_HW_KDFC_TRPL_FIFO_0_CTRL_MODE_NON_OFFLOAD_ONLY) |
#अगर_अघोषित __BIG_ENDIAN
		 VXGE_HW_KDFC_TRPL_FIFO_0_CTRL_SWAP_EN |
#पूर्ण_अगर
		 VXGE_HW_KDFC_TRPL_FIFO_0_CTRL_SELECT(0);

	ग_लिखोq(val64, &vp_reg->kdfc_trpl_fअगरo_0_ctrl);
	ग_लिखोq((u64)0, &vp_reg->kdfc_trpl_fअगरo_0_wb_address);
	wmb();
	vpath_stride = पढ़ोq(&hldev->toc_reg->toc_kdfc_vpath_stride);

	vpath->nofl_db =
		(काष्ठा __vxge_hw_non_offload_db_wrapper __iomem *)
		(hldev->kdfc + (vp_id *
		VXGE_HW_TOC_KDFC_VPATH_STRIDE_GET_TOC_KDFC_VPATH_STRIDE(
					vpath_stride)));
निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_vpath_mac_configure
 * This routine configures the mac of भव path using the config passed
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_mac_configure(काष्ठा __vxge_hw_device *hldev, u32 vp_id)
अणु
	u64 val64;
	काष्ठा __vxge_hw_भवpath *vpath;
	काष्ठा vxge_hw_vp_config *vp_config;
	काष्ठा vxge_hw_vpath_reg __iomem *vp_reg;

	vpath = &hldev->भव_paths[vp_id];
	vp_reg = vpath->vp_reg;
	vp_config = vpath->vp_config;

	ग_लिखोq(VXGE_HW_XMAC_VSPORT_CHOICE_VSPORT_NUMBER(
			vpath->vsport_number), &vp_reg->xmac_vsport_choice);

	अगर (vp_config->ring.enable == VXGE_HW_RING_ENABLE) अणु

		val64 = पढ़ोq(&vp_reg->xmac_rpa_vcfg);

		अगर (vp_config->rpa_strip_vlan_tag !=
			VXGE_HW_VPATH_RPA_STRIP_VLAN_TAG_USE_FLASH_DEFAULT) अणु
			अगर (vp_config->rpa_strip_vlan_tag)
				val64 |= VXGE_HW_XMAC_RPA_VCFG_STRIP_VLAN_TAG;
			अन्यथा
				val64 &= ~VXGE_HW_XMAC_RPA_VCFG_STRIP_VLAN_TAG;
		पूर्ण

		ग_लिखोq(val64, &vp_reg->xmac_rpa_vcfg);
		val64 = पढ़ोq(&vp_reg->rxmac_vcfg0);

		अगर (vp_config->mtu !=
				VXGE_HW_VPATH_USE_FLASH_DEFAULT_INITIAL_MTU) अणु
			val64 &= ~VXGE_HW_RXMAC_VCFG0_RTS_MAX_FRM_LEN(0x3fff);
			अगर ((vp_config->mtu  +
				VXGE_HW_MAC_HEADER_MAX_SIZE) < vpath->max_mtu)
				val64 |= VXGE_HW_RXMAC_VCFG0_RTS_MAX_FRM_LEN(
					vp_config->mtu  +
					VXGE_HW_MAC_HEADER_MAX_SIZE);
			अन्यथा
				val64 |= VXGE_HW_RXMAC_VCFG0_RTS_MAX_FRM_LEN(
					vpath->max_mtu);
		पूर्ण

		ग_लिखोq(val64, &vp_reg->rxmac_vcfg0);

		val64 = पढ़ोq(&vp_reg->rxmac_vcfg1);

		val64 &= ~(VXGE_HW_RXMAC_VCFG1_RTS_RTH_MULTI_IT_BD_MODE(0x3) |
			VXGE_HW_RXMAC_VCFG1_RTS_RTH_MULTI_IT_EN_MODE);

		अगर (hldev->config.rth_it_type ==
				VXGE_HW_RTH_IT_TYPE_MULTI_IT) अणु
			val64 |= VXGE_HW_RXMAC_VCFG1_RTS_RTH_MULTI_IT_BD_MODE(
				0x2) |
				VXGE_HW_RXMAC_VCFG1_RTS_RTH_MULTI_IT_EN_MODE;
		पूर्ण

		ग_लिखोq(val64, &vp_reg->rxmac_vcfg1);
	पूर्ण
	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_vpath_tim_configure
 * This routine configures the tim रेजिस्टरs of भव path using the config
 * passed
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_tim_configure(काष्ठा __vxge_hw_device *hldev, u32 vp_id)
अणु
	u64 val64;
	काष्ठा __vxge_hw_भवpath *vpath;
	काष्ठा vxge_hw_vpath_reg __iomem *vp_reg;
	काष्ठा vxge_hw_vp_config *config;

	vpath = &hldev->भव_paths[vp_id];
	vp_reg = vpath->vp_reg;
	config = vpath->vp_config;

	ग_लिखोq(0, &vp_reg->tim_dest_addr);
	ग_लिखोq(0, &vp_reg->tim_vpath_map);
	ग_लिखोq(0, &vp_reg->tim_biपंचांगap);
	ग_लिखोq(0, &vp_reg->tim_remap);

	अगर (config->ring.enable == VXGE_HW_RING_ENABLE)
		ग_लिखोq(VXGE_HW_TIM_RING_ASSN_INT_NUM(
			(vp_id * VXGE_HW_MAX_INTR_PER_VP) +
			VXGE_HW_VPATH_INTR_RX), &vp_reg->tim_ring_assn);

	val64 = पढ़ोq(&vp_reg->tim_pci_cfg);
	val64 |= VXGE_HW_TIM_PCI_CFG_ADD_PAD;
	ग_लिखोq(val64, &vp_reg->tim_pci_cfg);

	अगर (config->fअगरo.enable == VXGE_HW_FIFO_ENABLE) अणु

		val64 = पढ़ोq(&vp_reg->tim_cfg1_पूर्णांक_num[VXGE_HW_VPATH_INTR_TX]);

		अगर (config->tti.bसमयr_val != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG1_INT_NUM_BTIMER_VAL(
				0x3ffffff);
			val64 |= VXGE_HW_TIM_CFG1_INT_NUM_BTIMER_VAL(
					config->tti.bसमयr_val);
		पूर्ण

		val64 &= ~VXGE_HW_TIM_CFG1_INT_NUM_BITMP_EN;

		अगर (config->tti.समयr_ac_en != VXGE_HW_USE_FLASH_DEFAULT) अणु
			अगर (config->tti.समयr_ac_en)
				val64 |= VXGE_HW_TIM_CFG1_INT_NUM_TIMER_AC;
			अन्यथा
				val64 &= ~VXGE_HW_TIM_CFG1_INT_NUM_TIMER_AC;
		पूर्ण

		अगर (config->tti.समयr_ci_en != VXGE_HW_USE_FLASH_DEFAULT) अणु
			अगर (config->tti.समयr_ci_en)
				val64 |= VXGE_HW_TIM_CFG1_INT_NUM_TIMER_CI;
			अन्यथा
				val64 &= ~VXGE_HW_TIM_CFG1_INT_NUM_TIMER_CI;
		पूर्ण

		अगर (config->tti.urange_a != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG1_INT_NUM_URNG_A(0x3f);
			val64 |= VXGE_HW_TIM_CFG1_INT_NUM_URNG_A(
					config->tti.urange_a);
		पूर्ण

		अगर (config->tti.urange_b != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG1_INT_NUM_URNG_B(0x3f);
			val64 |= VXGE_HW_TIM_CFG1_INT_NUM_URNG_B(
					config->tti.urange_b);
		पूर्ण

		अगर (config->tti.urange_c != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG1_INT_NUM_URNG_C(0x3f);
			val64 |= VXGE_HW_TIM_CFG1_INT_NUM_URNG_C(
					config->tti.urange_c);
		पूर्ण

		ग_लिखोq(val64, &vp_reg->tim_cfg1_पूर्णांक_num[VXGE_HW_VPATH_INTR_TX]);
		vpath->tim_tti_cfg1_saved = val64;

		val64 = पढ़ोq(&vp_reg->tim_cfg2_पूर्णांक_num[VXGE_HW_VPATH_INTR_TX]);

		अगर (config->tti.uec_a != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG2_INT_NUM_UEC_A(0xffff);
			val64 |= VXGE_HW_TIM_CFG2_INT_NUM_UEC_A(
						config->tti.uec_a);
		पूर्ण

		अगर (config->tti.uec_b != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG2_INT_NUM_UEC_B(0xffff);
			val64 |= VXGE_HW_TIM_CFG2_INT_NUM_UEC_B(
						config->tti.uec_b);
		पूर्ण

		अगर (config->tti.uec_c != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG2_INT_NUM_UEC_C(0xffff);
			val64 |= VXGE_HW_TIM_CFG2_INT_NUM_UEC_C(
						config->tti.uec_c);
		पूर्ण

		अगर (config->tti.uec_d != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG2_INT_NUM_UEC_D(0xffff);
			val64 |= VXGE_HW_TIM_CFG2_INT_NUM_UEC_D(
						config->tti.uec_d);
		पूर्ण

		ग_लिखोq(val64, &vp_reg->tim_cfg2_पूर्णांक_num[VXGE_HW_VPATH_INTR_TX]);
		val64 = पढ़ोq(&vp_reg->tim_cfg3_पूर्णांक_num[VXGE_HW_VPATH_INTR_TX]);

		अगर (config->tti.समयr_ri_en != VXGE_HW_USE_FLASH_DEFAULT) अणु
			अगर (config->tti.समयr_ri_en)
				val64 |= VXGE_HW_TIM_CFG3_INT_NUM_TIMER_RI;
			अन्यथा
				val64 &= ~VXGE_HW_TIM_CFG3_INT_NUM_TIMER_RI;
		पूर्ण

		अगर (config->tti.rसमयr_val != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG3_INT_NUM_RTIMER_VAL(
					0x3ffffff);
			val64 |= VXGE_HW_TIM_CFG3_INT_NUM_RTIMER_VAL(
					config->tti.rसमयr_val);
		पूर्ण

		अगर (config->tti.util_sel != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG3_INT_NUM_UTIL_SEL(0x3f);
			val64 |= VXGE_HW_TIM_CFG3_INT_NUM_UTIL_SEL(vp_id);
		पूर्ण

		अगर (config->tti.lसमयr_val != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG3_INT_NUM_LTIMER_VAL(
					0x3ffffff);
			val64 |= VXGE_HW_TIM_CFG3_INT_NUM_LTIMER_VAL(
					config->tti.lसमयr_val);
		पूर्ण

		ग_लिखोq(val64, &vp_reg->tim_cfg3_पूर्णांक_num[VXGE_HW_VPATH_INTR_TX]);
		vpath->tim_tti_cfg3_saved = val64;
	पूर्ण

	अगर (config->ring.enable == VXGE_HW_RING_ENABLE) अणु

		val64 = पढ़ोq(&vp_reg->tim_cfg1_पूर्णांक_num[VXGE_HW_VPATH_INTR_RX]);

		अगर (config->rti.bसमयr_val != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG1_INT_NUM_BTIMER_VAL(
					0x3ffffff);
			val64 |= VXGE_HW_TIM_CFG1_INT_NUM_BTIMER_VAL(
					config->rti.bसमयr_val);
		पूर्ण

		val64 &= ~VXGE_HW_TIM_CFG1_INT_NUM_BITMP_EN;

		अगर (config->rti.समयr_ac_en != VXGE_HW_USE_FLASH_DEFAULT) अणु
			अगर (config->rti.समयr_ac_en)
				val64 |= VXGE_HW_TIM_CFG1_INT_NUM_TIMER_AC;
			अन्यथा
				val64 &= ~VXGE_HW_TIM_CFG1_INT_NUM_TIMER_AC;
		पूर्ण

		अगर (config->rti.समयr_ci_en != VXGE_HW_USE_FLASH_DEFAULT) अणु
			अगर (config->rti.समयr_ci_en)
				val64 |= VXGE_HW_TIM_CFG1_INT_NUM_TIMER_CI;
			अन्यथा
				val64 &= ~VXGE_HW_TIM_CFG1_INT_NUM_TIMER_CI;
		पूर्ण

		अगर (config->rti.urange_a != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG1_INT_NUM_URNG_A(0x3f);
			val64 |= VXGE_HW_TIM_CFG1_INT_NUM_URNG_A(
					config->rti.urange_a);
		पूर्ण

		अगर (config->rti.urange_b != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG1_INT_NUM_URNG_B(0x3f);
			val64 |= VXGE_HW_TIM_CFG1_INT_NUM_URNG_B(
					config->rti.urange_b);
		पूर्ण

		अगर (config->rti.urange_c != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG1_INT_NUM_URNG_C(0x3f);
			val64 |= VXGE_HW_TIM_CFG1_INT_NUM_URNG_C(
					config->rti.urange_c);
		पूर्ण

		ग_लिखोq(val64, &vp_reg->tim_cfg1_पूर्णांक_num[VXGE_HW_VPATH_INTR_RX]);
		vpath->tim_rti_cfg1_saved = val64;

		val64 = पढ़ोq(&vp_reg->tim_cfg2_पूर्णांक_num[VXGE_HW_VPATH_INTR_RX]);

		अगर (config->rti.uec_a != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG2_INT_NUM_UEC_A(0xffff);
			val64 |= VXGE_HW_TIM_CFG2_INT_NUM_UEC_A(
						config->rti.uec_a);
		पूर्ण

		अगर (config->rti.uec_b != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG2_INT_NUM_UEC_B(0xffff);
			val64 |= VXGE_HW_TIM_CFG2_INT_NUM_UEC_B(
						config->rti.uec_b);
		पूर्ण

		अगर (config->rti.uec_c != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG2_INT_NUM_UEC_C(0xffff);
			val64 |= VXGE_HW_TIM_CFG2_INT_NUM_UEC_C(
						config->rti.uec_c);
		पूर्ण

		अगर (config->rti.uec_d != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG2_INT_NUM_UEC_D(0xffff);
			val64 |= VXGE_HW_TIM_CFG2_INT_NUM_UEC_D(
						config->rti.uec_d);
		पूर्ण

		ग_लिखोq(val64, &vp_reg->tim_cfg2_पूर्णांक_num[VXGE_HW_VPATH_INTR_RX]);
		val64 = पढ़ोq(&vp_reg->tim_cfg3_पूर्णांक_num[VXGE_HW_VPATH_INTR_RX]);

		अगर (config->rti.समयr_ri_en != VXGE_HW_USE_FLASH_DEFAULT) अणु
			अगर (config->rti.समयr_ri_en)
				val64 |= VXGE_HW_TIM_CFG3_INT_NUM_TIMER_RI;
			अन्यथा
				val64 &= ~VXGE_HW_TIM_CFG3_INT_NUM_TIMER_RI;
		पूर्ण

		अगर (config->rti.rसमयr_val != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG3_INT_NUM_RTIMER_VAL(
					0x3ffffff);
			val64 |= VXGE_HW_TIM_CFG3_INT_NUM_RTIMER_VAL(
					config->rti.rसमयr_val);
		पूर्ण

		अगर (config->rti.util_sel != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG3_INT_NUM_UTIL_SEL(0x3f);
			val64 |= VXGE_HW_TIM_CFG3_INT_NUM_UTIL_SEL(vp_id);
		पूर्ण

		अगर (config->rti.lसमयr_val != VXGE_HW_USE_FLASH_DEFAULT) अणु
			val64 &= ~VXGE_HW_TIM_CFG3_INT_NUM_LTIMER_VAL(
					0x3ffffff);
			val64 |= VXGE_HW_TIM_CFG3_INT_NUM_LTIMER_VAL(
					config->rti.lसमयr_val);
		पूर्ण

		ग_लिखोq(val64, &vp_reg->tim_cfg3_पूर्णांक_num[VXGE_HW_VPATH_INTR_RX]);
		vpath->tim_rti_cfg3_saved = val64;
	पूर्ण

	val64 = 0;
	ग_लिखोq(val64, &vp_reg->tim_cfg1_पूर्णांक_num[VXGE_HW_VPATH_INTR_EINTA]);
	ग_लिखोq(val64, &vp_reg->tim_cfg2_पूर्णांक_num[VXGE_HW_VPATH_INTR_EINTA]);
	ग_लिखोq(val64, &vp_reg->tim_cfg3_पूर्णांक_num[VXGE_HW_VPATH_INTR_EINTA]);
	ग_लिखोq(val64, &vp_reg->tim_cfg1_पूर्णांक_num[VXGE_HW_VPATH_INTR_BMAP]);
	ग_लिखोq(val64, &vp_reg->tim_cfg2_पूर्णांक_num[VXGE_HW_VPATH_INTR_BMAP]);
	ग_लिखोq(val64, &vp_reg->tim_cfg3_पूर्णांक_num[VXGE_HW_VPATH_INTR_BMAP]);

	val64 = VXGE_HW_TIM_WRKLD_CLC_WRKLD_EVAL_PRD(150);
	val64 |= VXGE_HW_TIM_WRKLD_CLC_WRKLD_EVAL_DIV(0);
	val64 |= VXGE_HW_TIM_WRKLD_CLC_CNT_RX_TX(3);
	ग_लिखोq(val64, &vp_reg->tim_wrkld_clc);

	वापस VXGE_HW_OK;
पूर्ण

/*
 * __vxge_hw_vpath_initialize
 * This routine is the final phase of init which initializes the
 * रेजिस्टरs of the vpath using the configuration passed.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vpath_initialize(काष्ठा __vxge_hw_device *hldev, u32 vp_id)
अणु
	u64 val64;
	u32 val32;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा __vxge_hw_भवpath *vpath;
	काष्ठा vxge_hw_vpath_reg __iomem *vp_reg;

	vpath = &hldev->भव_paths[vp_id];

	अगर (!(hldev->vpath_assignments & vxge_mBIT(vp_id))) अणु
		status = VXGE_HW_ERR_VPATH_NOT_AVAILABLE;
		जाओ निकास;
	पूर्ण
	vp_reg = vpath->vp_reg;

	status =  __vxge_hw_vpath_swapper_set(vpath->vp_reg);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	status =  __vxge_hw_vpath_mac_configure(hldev, vp_id);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	status =  __vxge_hw_vpath_kdfc_configure(hldev, vp_id);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	status = __vxge_hw_vpath_tim_configure(hldev, vp_id);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	val64 = पढ़ोq(&vp_reg->rtdma_rd_optimization_ctrl);

	/* Get MRRS value from device control */
	status  = __vxge_hw_vpath_pci_पढ़ो(vpath, 1, 0x78, &val32);
	अगर (status == VXGE_HW_OK) अणु
		val32 = (val32 & VXGE_HW_PCI_EXP_DEVCTL_READRQ) >> 12;
		val64 &=
		    ~(VXGE_HW_RTDMA_RD_OPTIMIZATION_CTRL_FB_FILL_THRESH(7));
		val64 |=
		    VXGE_HW_RTDMA_RD_OPTIMIZATION_CTRL_FB_FILL_THRESH(val32);

		val64 |= VXGE_HW_RTDMA_RD_OPTIMIZATION_CTRL_FB_WAIT_FOR_SPACE;
	पूर्ण

	val64 &= ~(VXGE_HW_RTDMA_RD_OPTIMIZATION_CTRL_FB_ADDR_BDRY(7));
	val64 |=
	    VXGE_HW_RTDMA_RD_OPTIMIZATION_CTRL_FB_ADDR_BDRY(
		    VXGE_HW_MAX_PAYLOAD_SIZE_512);

	val64 |= VXGE_HW_RTDMA_RD_OPTIMIZATION_CTRL_FB_ADDR_BDRY_EN;
	ग_लिखोq(val64, &vp_reg->rtdma_rd_optimization_ctrl);

निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_vp_terminate - Terminate Virtual Path काष्ठाure
 * This routine बंदs all channels it खोलोed and मुक्तup memory
 */
अटल व्योम __vxge_hw_vp_terminate(काष्ठा __vxge_hw_device *hldev, u32 vp_id)
अणु
	काष्ठा __vxge_hw_भवpath *vpath;

	vpath = &hldev->भव_paths[vp_id];

	अगर (vpath->vp_खोलो == VXGE_HW_VP_NOT_OPEN)
		जाओ निकास;

	VXGE_HW_DEVICE_TIM_INT_MASK_RESET(vpath->hldev->tim_पूर्णांक_mask0,
		vpath->hldev->tim_पूर्णांक_mask1, vpath->vp_id);
	hldev->stats.hw_dev_info_stats.vpath_info[vpath->vp_id] = शून्य;

	/* If the whole काष्ठा __vxge_hw_भवpath is zeroed, nothing will
	 * work after the पूर्णांकerface is brought करोwn.
	 */
	spin_lock(&vpath->lock);
	vpath->vp_खोलो = VXGE_HW_VP_NOT_OPEN;
	spin_unlock(&vpath->lock);

	vpath->vpmgmt_reg = शून्य;
	vpath->nofl_db = शून्य;
	vpath->max_mtu = 0;
	vpath->vsport_number = 0;
	vpath->max_kdfc_db = 0;
	vpath->max_nofl_db = 0;
	vpath->ringh = शून्य;
	vpath->fअगरoh = शून्य;
	स_रखो(&vpath->vpath_handles, 0, माप(काष्ठा list_head));
	vpath->stats_block = शून्य;
	vpath->hw_stats = शून्य;
	vpath->hw_stats_sav = शून्य;
	vpath->sw_stats = शून्य;

निकास:
	वापस;
पूर्ण

/*
 * __vxge_hw_vp_initialize - Initialize Virtual Path काष्ठाure
 * This routine is the initial phase of init which resets the vpath and
 * initializes the software support काष्ठाures.
 */
अटल क्रमागत vxge_hw_status
__vxge_hw_vp_initialize(काष्ठा __vxge_hw_device *hldev, u32 vp_id,
			काष्ठा vxge_hw_vp_config *config)
अणु
	काष्ठा __vxge_hw_भवpath *vpath;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	अगर (!(hldev->vpath_assignments & vxge_mBIT(vp_id))) अणु
		status = VXGE_HW_ERR_VPATH_NOT_AVAILABLE;
		जाओ निकास;
	पूर्ण

	vpath = &hldev->भव_paths[vp_id];

	spin_lock_init(&vpath->lock);
	vpath->vp_id = vp_id;
	vpath->vp_खोलो = VXGE_HW_VP_OPEN;
	vpath->hldev = hldev;
	vpath->vp_config = config;
	vpath->vp_reg = hldev->vpath_reg[vp_id];
	vpath->vpmgmt_reg = hldev->vpmgmt_reg[vp_id];

	__vxge_hw_vpath_reset(hldev, vp_id);

	status = __vxge_hw_vpath_reset_check(vpath);
	अगर (status != VXGE_HW_OK) अणु
		स_रखो(vpath, 0, माप(काष्ठा __vxge_hw_भवpath));
		जाओ निकास;
	पूर्ण

	status = __vxge_hw_vpath_mgmt_पढ़ो(hldev, vpath);
	अगर (status != VXGE_HW_OK) अणु
		स_रखो(vpath, 0, माप(काष्ठा __vxge_hw_भवpath));
		जाओ निकास;
	पूर्ण

	INIT_LIST_HEAD(&vpath->vpath_handles);

	vpath->sw_stats = &hldev->stats.sw_dev_info_stats.vpath_info[vp_id];

	VXGE_HW_DEVICE_TIM_INT_MASK_SET(hldev->tim_पूर्णांक_mask0,
		hldev->tim_पूर्णांक_mask1, vp_id);

	status = __vxge_hw_vpath_initialize(hldev, vp_id);
	अगर (status != VXGE_HW_OK)
		__vxge_hw_vp_terminate(hldev, vp_id);
निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_vpath_mtu_set - Set MTU.
 * Set new MTU value. Example, to use jumbo frames:
 * vxge_hw_vpath_mtu_set(my_device, 9600);
 */
क्रमागत vxge_hw_status
vxge_hw_vpath_mtu_set(काष्ठा __vxge_hw_vpath_handle *vp, u32 new_mtu)
अणु
	u64 val64;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा __vxge_hw_भवpath *vpath;

	अगर (vp == शून्य) अणु
		status = VXGE_HW_ERR_INVALID_HANDLE;
		जाओ निकास;
	पूर्ण
	vpath = vp->vpath;

	new_mtu += VXGE_HW_MAC_HEADER_MAX_SIZE;

	अगर ((new_mtu < VXGE_HW_MIN_MTU) || (new_mtu > vpath->max_mtu))
		status = VXGE_HW_ERR_INVALID_MTU_SIZE;

	val64 = पढ़ोq(&vpath->vp_reg->rxmac_vcfg0);

	val64 &= ~VXGE_HW_RXMAC_VCFG0_RTS_MAX_FRM_LEN(0x3fff);
	val64 |= VXGE_HW_RXMAC_VCFG0_RTS_MAX_FRM_LEN(new_mtu);

	ग_लिखोq(val64, &vpath->vp_reg->rxmac_vcfg0);

	vpath->vp_config->mtu = new_mtu - VXGE_HW_MAC_HEADER_MAX_SIZE;

निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_vpath_stats_enable - Enable vpath h/wstatistics.
 * Enable the DMA vpath statistics. The function is to be called to re-enable
 * the adapter to update stats पूर्णांकo the host memory
 */
अटल क्रमागत vxge_hw_status
vxge_hw_vpath_stats_enable(काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	क्रमागत vxge_hw_status status = VXGE_HW_OK;
	काष्ठा __vxge_hw_भवpath *vpath;

	vpath = vp->vpath;

	अगर (vpath->vp_खोलो == VXGE_HW_VP_NOT_OPEN) अणु
		status = VXGE_HW_ERR_VPATH_NOT_OPEN;
		जाओ निकास;
	पूर्ण

	स_नकल(vpath->hw_stats_sav, vpath->hw_stats,
			माप(काष्ठा vxge_hw_vpath_stats_hw_info));

	status = __vxge_hw_vpath_stats_get(vpath, vpath->hw_stats);
निकास:
	वापस status;
पूर्ण

/*
 * __vxge_hw_blockpool_block_allocate - Allocates a block from block pool
 * This function allocates a block from block pool or from the प्रणाली
 */
अटल काष्ठा __vxge_hw_blockpool_entry *
__vxge_hw_blockpool_block_allocate(काष्ठा __vxge_hw_device *devh, u32 size)
अणु
	काष्ठा __vxge_hw_blockpool_entry *entry = शून्य;
	काष्ठा __vxge_hw_blockpool  *blockpool;

	blockpool = &devh->block_pool;

	अगर (size == blockpool->block_size) अणु

		अगर (!list_empty(&blockpool->मुक्त_block_list))
			entry = (काष्ठा __vxge_hw_blockpool_entry *)
				list_first_entry(&blockpool->मुक्त_block_list,
					काष्ठा __vxge_hw_blockpool_entry,
					item);

		अगर (entry != शून्य) अणु
			list_del(&entry->item);
			blockpool->pool_size--;
		पूर्ण
	पूर्ण

	अगर (entry != शून्य)
		__vxge_hw_blockpool_blocks_add(blockpool);

	वापस entry;
पूर्ण

/*
 * vxge_hw_vpath_खोलो - Open a भव path on a given adapter
 * This function is used to खोलो access to भव path of an
 * adapter क्रम offload, GRO operations. This function वापसs
 * synchronously.
 */
क्रमागत vxge_hw_status
vxge_hw_vpath_खोलो(काष्ठा __vxge_hw_device *hldev,
		   काष्ठा vxge_hw_vpath_attr *attr,
		   काष्ठा __vxge_hw_vpath_handle **vpath_handle)
अणु
	काष्ठा __vxge_hw_भवpath *vpath;
	काष्ठा __vxge_hw_vpath_handle *vp;
	क्रमागत vxge_hw_status status;

	vpath = &hldev->भव_paths[attr->vp_id];

	अगर (vpath->vp_खोलो == VXGE_HW_VP_OPEN) अणु
		status = VXGE_HW_ERR_INVALID_STATE;
		जाओ vpath_खोलो_निकास1;
	पूर्ण

	status = __vxge_hw_vp_initialize(hldev, attr->vp_id,
			&hldev->config.vp_config[attr->vp_id]);
	अगर (status != VXGE_HW_OK)
		जाओ vpath_खोलो_निकास1;

	vp = vzalloc(माप(काष्ठा __vxge_hw_vpath_handle));
	अगर (vp == शून्य) अणु
		status = VXGE_HW_ERR_OUT_OF_MEMORY;
		जाओ vpath_खोलो_निकास2;
	पूर्ण

	vp->vpath = vpath;

	अगर (vpath->vp_config->fअगरo.enable == VXGE_HW_FIFO_ENABLE) अणु
		status = __vxge_hw_fअगरo_create(vp, &attr->fअगरo_attr);
		अगर (status != VXGE_HW_OK)
			जाओ vpath_खोलो_निकास6;
	पूर्ण

	अगर (vpath->vp_config->ring.enable == VXGE_HW_RING_ENABLE) अणु
		status = __vxge_hw_ring_create(vp, &attr->ring_attr);
		अगर (status != VXGE_HW_OK)
			जाओ vpath_खोलो_निकास7;

		__vxge_hw_vpath_prc_configure(hldev, attr->vp_id);
	पूर्ण

	vpath->fअगरoh->tx_पूर्णांकr_num =
		(attr->vp_id * VXGE_HW_MAX_INTR_PER_VP)  +
			VXGE_HW_VPATH_INTR_TX;

	vpath->stats_block = __vxge_hw_blockpool_block_allocate(hldev,
				VXGE_HW_BLOCK_SIZE);
	अगर (vpath->stats_block == शून्य) अणु
		status = VXGE_HW_ERR_OUT_OF_MEMORY;
		जाओ vpath_खोलो_निकास8;
	पूर्ण

	vpath->hw_stats = vpath->stats_block->memblock;
	स_रखो(vpath->hw_stats, 0,
		माप(काष्ठा vxge_hw_vpath_stats_hw_info));

	hldev->stats.hw_dev_info_stats.vpath_info[attr->vp_id] =
						vpath->hw_stats;

	vpath->hw_stats_sav =
		&hldev->stats.hw_dev_info_stats.vpath_info_sav[attr->vp_id];
	स_रखो(vpath->hw_stats_sav, 0,
			माप(काष्ठा vxge_hw_vpath_stats_hw_info));

	ग_लिखोq(vpath->stats_block->dma_addr, &vpath->vp_reg->stats_cfg);

	status = vxge_hw_vpath_stats_enable(vp);
	अगर (status != VXGE_HW_OK)
		जाओ vpath_खोलो_निकास8;

	list_add(&vp->item, &vpath->vpath_handles);

	hldev->vpaths_deployed |= vxge_mBIT(vpath->vp_id);

	*vpath_handle = vp;

	attr->fअगरo_attr.userdata = vpath->fअगरoh;
	attr->ring_attr.userdata = vpath->ringh;

	वापस VXGE_HW_OK;

vpath_खोलो_निकास8:
	अगर (vpath->ringh != शून्य)
		__vxge_hw_ring_delete(vp);
vpath_खोलो_निकास7:
	अगर (vpath->fअगरoh != शून्य)
		__vxge_hw_fअगरo_delete(vp);
vpath_खोलो_निकास6:
	vमुक्त(vp);
vpath_खोलो_निकास2:
	__vxge_hw_vp_terminate(hldev, attr->vp_id);
vpath_खोलो_निकास1:

	वापस status;
पूर्ण

/**
 * vxge_hw_vpath_rx_करोorbell_post - Close the handle got from previous vpath
 * (vpath) खोलो
 * @vp: Handle got from previous vpath खोलो
 *
 * This function is used to बंद access to भव path खोलोed
 * earlier.
 */
व्योम vxge_hw_vpath_rx_करोorbell_init(काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	काष्ठा __vxge_hw_भवpath *vpath = vp->vpath;
	काष्ठा __vxge_hw_ring *ring = vpath->ringh;
	काष्ठा vxgedev *vdev = netdev_priv(vpath->hldev->ndev);
	u64 new_count, val64, val164;

	अगर (vdev->titan1) अणु
		new_count = पढ़ोq(&vpath->vp_reg->rxdmem_size);
		new_count &= 0x1fff;
	पूर्ण अन्यथा
		new_count = ring->config->ring_blocks * VXGE_HW_BLOCK_SIZE / 8;

	val164 = VXGE_HW_RXDMEM_SIZE_PRC_RXDMEM_SIZE(new_count);

	ग_लिखोq(VXGE_HW_PRC_RXD_DOORBELL_NEW_QW_CNT(val164),
		&vpath->vp_reg->prc_rxd_करोorbell);
	पढ़ोl(&vpath->vp_reg->prc_rxd_करोorbell);

	val164 /= 2;
	val64 = पढ़ोq(&vpath->vp_reg->prc_cfg6);
	val64 = VXGE_HW_PRC_CFG6_RXD_SPAT(val64);
	val64 &= 0x1ff;

	/*
	 * Each RxD is of 4 qwords
	 */
	new_count -= (val64 + 1);
	val64 = min(val164, new_count) / 4;

	ring->rxds_limit = min(ring->rxds_limit, val64);
	अगर (ring->rxds_limit < 4)
		ring->rxds_limit = 4;
पूर्ण

/*
 * __vxge_hw_blockpool_block_मुक्त - Frees a block from block pool
 * @devh: Hal device
 * @entry: Entry of block to be मुक्तd
 *
 * This function मुक्तs a block from block pool
 */
अटल व्योम
__vxge_hw_blockpool_block_मुक्त(काष्ठा __vxge_hw_device *devh,
			       काष्ठा __vxge_hw_blockpool_entry *entry)
अणु
	काष्ठा __vxge_hw_blockpool  *blockpool;

	blockpool = &devh->block_pool;

	अगर (entry->length == blockpool->block_size) अणु
		list_add(&entry->item, &blockpool->मुक्त_block_list);
		blockpool->pool_size++;
	पूर्ण

	__vxge_hw_blockpool_blocks_हटाओ(blockpool);
पूर्ण

/*
 * vxge_hw_vpath_बंद - Close the handle got from previous vpath (vpath) खोलो
 * This function is used to बंद access to भव path खोलोed
 * earlier.
 */
क्रमागत vxge_hw_status vxge_hw_vpath_बंद(काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	काष्ठा __vxge_hw_भवpath *vpath = शून्य;
	काष्ठा __vxge_hw_device *devh = शून्य;
	u32 vp_id = vp->vpath->vp_id;
	u32 is_empty = TRUE;
	क्रमागत vxge_hw_status status = VXGE_HW_OK;

	vpath = vp->vpath;
	devh = vpath->hldev;

	अगर (vpath->vp_खोलो == VXGE_HW_VP_NOT_OPEN) अणु
		status = VXGE_HW_ERR_VPATH_NOT_OPEN;
		जाओ vpath_बंद_निकास;
	पूर्ण

	list_del(&vp->item);

	अगर (!list_empty(&vpath->vpath_handles)) अणु
		list_add(&vp->item, &vpath->vpath_handles);
		is_empty = FALSE;
	पूर्ण

	अगर (!is_empty) अणु
		status = VXGE_HW_FAIL;
		जाओ vpath_बंद_निकास;
	पूर्ण

	devh->vpaths_deployed &= ~vxge_mBIT(vp_id);

	अगर (vpath->ringh != शून्य)
		__vxge_hw_ring_delete(vp);

	अगर (vpath->fअगरoh != शून्य)
		__vxge_hw_fअगरo_delete(vp);

	अगर (vpath->stats_block != शून्य)
		__vxge_hw_blockpool_block_मुक्त(devh, vpath->stats_block);

	vमुक्त(vp);

	__vxge_hw_vp_terminate(devh, vp_id);

vpath_बंद_निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_vpath_reset - Resets vpath
 * This function is used to request a reset of vpath
 */
क्रमागत vxge_hw_status vxge_hw_vpath_reset(काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	क्रमागत vxge_hw_status status;
	u32 vp_id;
	काष्ठा __vxge_hw_भवpath *vpath = vp->vpath;

	vp_id = vpath->vp_id;

	अगर (vpath->vp_खोलो == VXGE_HW_VP_NOT_OPEN) अणु
		status = VXGE_HW_ERR_VPATH_NOT_OPEN;
		जाओ निकास;
	पूर्ण

	status = __vxge_hw_vpath_reset(vpath->hldev, vp_id);
	अगर (status == VXGE_HW_OK)
		vpath->sw_stats->soft_reset_cnt++;
निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_vpath_recover_from_reset - Poll क्रम reset complete and re-initialize.
 * This function poll's क्रम the vpath reset completion and re initializes
 * the vpath.
 */
क्रमागत vxge_hw_status
vxge_hw_vpath_recover_from_reset(काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	काष्ठा __vxge_hw_भवpath *vpath = शून्य;
	क्रमागत vxge_hw_status status;
	काष्ठा __vxge_hw_device *hldev;
	u32 vp_id;

	vp_id = vp->vpath->vp_id;
	vpath = vp->vpath;
	hldev = vpath->hldev;

	अगर (vpath->vp_खोलो == VXGE_HW_VP_NOT_OPEN) अणु
		status = VXGE_HW_ERR_VPATH_NOT_OPEN;
		जाओ निकास;
	पूर्ण

	status = __vxge_hw_vpath_reset_check(vpath);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	status = __vxge_hw_vpath_sw_reset(hldev, vp_id);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	status = __vxge_hw_vpath_initialize(hldev, vp_id);
	अगर (status != VXGE_HW_OK)
		जाओ निकास;

	अगर (vpath->ringh != शून्य)
		__vxge_hw_vpath_prc_configure(hldev, vp_id);

	स_रखो(vpath->hw_stats, 0,
		माप(काष्ठा vxge_hw_vpath_stats_hw_info));

	स_रखो(vpath->hw_stats_sav, 0,
		माप(काष्ठा vxge_hw_vpath_stats_hw_info));

	ग_लिखोq(vpath->stats_block->dma_addr,
		&vpath->vp_reg->stats_cfg);

	status = vxge_hw_vpath_stats_enable(vp);

निकास:
	वापस status;
पूर्ण

/*
 * vxge_hw_vpath_enable - Enable vpath.
 * This routine clears the vpath reset thereby enabling a vpath
 * to start क्रमwarding frames and generating पूर्णांकerrupts.
 */
व्योम
vxge_hw_vpath_enable(काष्ठा __vxge_hw_vpath_handle *vp)
अणु
	काष्ठा __vxge_hw_device *hldev;
	u64 val64;

	hldev = vp->vpath->hldev;

	val64 = VXGE_HW_CMN_RSTHDLR_CFG1_CLR_VPATH_RESET(
		1 << (16 - vp->vpath->vp_id));

	__vxge_hw_pio_mem_ग_लिखो32_upper((u32)vxge_bVALn(val64, 0, 32),
		&hldev->common_reg->cmn_rsthdlr_cfg1);
पूर्ण
