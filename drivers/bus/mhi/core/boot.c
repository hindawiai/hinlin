<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/mhi.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश "internal.h"

/* Setup RDDM vector table क्रम RDDM transfer and program RXVEC */
व्योम mhi_rddm_prepare(काष्ठा mhi_controller *mhi_cntrl,
		      काष्ठा image_info *img_info)
अणु
	काष्ठा mhi_buf *mhi_buf = img_info->mhi_buf;
	काष्ठा bhi_vec_entry *bhi_vec = img_info->bhi_vec;
	व्योम __iomem *base = mhi_cntrl->bhie;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	u32 sequence_id;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < img_info->entries - 1; i++, mhi_buf++, bhi_vec++) अणु
		bhi_vec->dma_addr = mhi_buf->dma_addr;
		bhi_vec->size = mhi_buf->len;
	पूर्ण

	dev_dbg(dev, "BHIe programming for RDDM\n");

	mhi_ग_लिखो_reg(mhi_cntrl, base, BHIE_RXVECADDR_HIGH_OFFS,
		      upper_32_bits(mhi_buf->dma_addr));

	mhi_ग_लिखो_reg(mhi_cntrl, base, BHIE_RXVECADDR_LOW_OFFS,
		      lower_32_bits(mhi_buf->dma_addr));

	mhi_ग_लिखो_reg(mhi_cntrl, base, BHIE_RXVECSIZE_OFFS, mhi_buf->len);
	sequence_id = MHI_RANDOM_U32_NONZERO(BHIE_RXVECSTATUS_SEQNUM_BMSK);

	mhi_ग_लिखो_reg_field(mhi_cntrl, base, BHIE_RXVECDB_OFFS,
			    BHIE_RXVECDB_SEQNUM_BMSK, BHIE_RXVECDB_SEQNUM_SHFT,
			    sequence_id);

	dev_dbg(dev, "Address: %p and len: 0x%zx sequence: %u\n",
		&mhi_buf->dma_addr, mhi_buf->len, sequence_id);
पूर्ण

/* Collect RDDM buffer during kernel panic */
अटल पूर्णांक __mhi_करोwnload_rddm_in_panic(काष्ठा mhi_controller *mhi_cntrl)
अणु
	पूर्णांक ret;
	u32 rx_status;
	क्रमागत mhi_ee_type ee;
	स्थिर u32 delayus = 2000;
	u32 retry = (mhi_cntrl->समयout_ms * 1000) / delayus;
	स्थिर u32 rddm_समयout_us = 200000;
	पूर्णांक rddm_retry = rddm_समयout_us / delayus;
	व्योम __iomem *base = mhi_cntrl->bhie;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;

	dev_dbg(dev, "Entered with pm_state:%s dev_state:%s ee:%s\n",
		to_mhi_pm_state_str(mhi_cntrl->pm_state),
		TO_MHI_STATE_STR(mhi_cntrl->dev_state),
		TO_MHI_EXEC_STR(mhi_cntrl->ee));

	/*
	 * This should only be executing during a kernel panic, we expect all
	 * other cores to shutकरोwn जबतक we're collecting RDDM buffer. After
	 * वापसing from this function, we expect the device to reset.
	 *
	 * Normaly, we पढ़ो/ग_लिखो pm_state only after grabbing the
	 * pm_lock, since we're in a panic, skipping it. Also there is no
	 * gurantee that this state change would take effect since
	 * we're setting it w/o grabbing pm_lock
	 */
	mhi_cntrl->pm_state = MHI_PM_LD_ERR_FATAL_DETECT;
	/* update should take the effect immediately */
	smp_wmb();

	/*
	 * Make sure device is not alपढ़ोy in RDDM. In हाल the device निश्चितs
	 * and a kernel panic follows, device will alपढ़ोy be in RDDM.
	 * Do not trigger SYS ERR again and proceed with रुकोing क्रम
	 * image करोwnload completion.
	 */
	ee = mhi_get_exec_env(mhi_cntrl);
	अगर (ee == MHI_EE_MAX)
		जाओ error_निकास_rddm;

	अगर (ee != MHI_EE_RDDM) अणु
		dev_dbg(dev, "Trigger device into RDDM mode using SYS ERR\n");
		mhi_set_mhi_state(mhi_cntrl, MHI_STATE_SYS_ERR);

		dev_dbg(dev, "Waiting for device to enter RDDM\n");
		जबतक (rddm_retry--) अणु
			ee = mhi_get_exec_env(mhi_cntrl);
			अगर (ee == MHI_EE_RDDM)
				अवरोध;

			udelay(delayus);
		पूर्ण

		अगर (rddm_retry <= 0) अणु
			/* Hardware reset so क्रमce device to enter RDDM */
			dev_dbg(dev,
				"Did not enter RDDM, do a host req reset\n");
			mhi_ग_लिखो_reg(mhi_cntrl, mhi_cntrl->regs,
				      MHI_SOC_RESET_REQ_OFFSET,
				      MHI_SOC_RESET_REQ);
			udelay(delayus);
		पूर्ण

		ee = mhi_get_exec_env(mhi_cntrl);
	पूर्ण

	dev_dbg(dev,
		"Waiting for RDDM image download via BHIe, current EE:%s\n",
		TO_MHI_EXEC_STR(ee));

	जबतक (retry--) अणु
		ret = mhi_पढ़ो_reg_field(mhi_cntrl, base, BHIE_RXVECSTATUS_OFFS,
					 BHIE_RXVECSTATUS_STATUS_BMSK,
					 BHIE_RXVECSTATUS_STATUS_SHFT,
					 &rx_status);
		अगर (ret)
			वापस -EIO;

		अगर (rx_status == BHIE_RXVECSTATUS_STATUS_XFER_COMPL)
			वापस 0;

		udelay(delayus);
	पूर्ण

	ee = mhi_get_exec_env(mhi_cntrl);
	ret = mhi_पढ़ो_reg(mhi_cntrl, base, BHIE_RXVECSTATUS_OFFS, &rx_status);

	dev_err(dev, "RXVEC_STATUS: 0x%x\n", rx_status);

error_निकास_rddm:
	dev_err(dev, "RDDM transfer failed. Current EE: %s\n",
		TO_MHI_EXEC_STR(ee));

	वापस -EIO;
पूर्ण

/* Download RDDM image from device */
पूर्णांक mhi_करोwnload_rddm_image(काष्ठा mhi_controller *mhi_cntrl, bool in_panic)
अणु
	व्योम __iomem *base = mhi_cntrl->bhie;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	u32 rx_status;

	अगर (in_panic)
		वापस __mhi_करोwnload_rddm_in_panic(mhi_cntrl);

	dev_dbg(dev, "Waiting for RDDM image download via BHIe\n");

	/* Wait क्रम the image करोwnload to complete */
	रुको_event_समयout(mhi_cntrl->state_event,
			   mhi_पढ़ो_reg_field(mhi_cntrl, base,
					      BHIE_RXVECSTATUS_OFFS,
					      BHIE_RXVECSTATUS_STATUS_BMSK,
					      BHIE_RXVECSTATUS_STATUS_SHFT,
					      &rx_status) || rx_status,
			   msecs_to_jअगरfies(mhi_cntrl->समयout_ms));

	वापस (rx_status == BHIE_RXVECSTATUS_STATUS_XFER_COMPL) ? 0 : -EIO;
पूर्ण
EXPORT_SYMBOL_GPL(mhi_करोwnload_rddm_image);

अटल पूर्णांक mhi_fw_load_bhie(काष्ठा mhi_controller *mhi_cntrl,
			    स्थिर काष्ठा mhi_buf *mhi_buf)
अणु
	व्योम __iomem *base = mhi_cntrl->bhie;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	rwlock_t *pm_lock = &mhi_cntrl->pm_lock;
	u32 tx_status, sequence_id;
	पूर्णांक ret;

	पढ़ो_lock_bh(pm_lock);
	अगर (!MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state)) अणु
		पढ़ो_unlock_bh(pm_lock);
		वापस -EIO;
	पूर्ण

	sequence_id = MHI_RANDOM_U32_NONZERO(BHIE_TXVECSTATUS_SEQNUM_BMSK);
	dev_dbg(dev, "Starting image download via BHIe. Sequence ID: %u\n",
		sequence_id);
	mhi_ग_लिखो_reg(mhi_cntrl, base, BHIE_TXVECADDR_HIGH_OFFS,
		      upper_32_bits(mhi_buf->dma_addr));

	mhi_ग_लिखो_reg(mhi_cntrl, base, BHIE_TXVECADDR_LOW_OFFS,
		      lower_32_bits(mhi_buf->dma_addr));

	mhi_ग_लिखो_reg(mhi_cntrl, base, BHIE_TXVECSIZE_OFFS, mhi_buf->len);

	mhi_ग_लिखो_reg_field(mhi_cntrl, base, BHIE_TXVECDB_OFFS,
			    BHIE_TXVECDB_SEQNUM_BMSK, BHIE_TXVECDB_SEQNUM_SHFT,
			    sequence_id);
	पढ़ो_unlock_bh(pm_lock);

	/* Wait क्रम the image करोwnload to complete */
	ret = रुको_event_समयout(mhi_cntrl->state_event,
				 MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state) ||
				 mhi_पढ़ो_reg_field(mhi_cntrl, base,
						   BHIE_TXVECSTATUS_OFFS,
						   BHIE_TXVECSTATUS_STATUS_BMSK,
						   BHIE_TXVECSTATUS_STATUS_SHFT,
						   &tx_status) || tx_status,
				 msecs_to_jअगरfies(mhi_cntrl->समयout_ms));
	अगर (MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state) ||
	    tx_status != BHIE_TXVECSTATUS_STATUS_XFER_COMPL)
		वापस -EIO;

	वापस (!ret) ? -ETIMEDOUT : 0;
पूर्ण

अटल पूर्णांक mhi_fw_load_bhi(काष्ठा mhi_controller *mhi_cntrl,
			   dma_addr_t dma_addr,
			   माप_प्रकार size)
अणु
	u32 tx_status, val, session_id;
	पूर्णांक i, ret;
	व्योम __iomem *base = mhi_cntrl->bhi;
	rwlock_t *pm_lock = &mhi_cntrl->pm_lock;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	काष्ठा अणु
		अक्षर *name;
		u32 offset;
	पूर्ण error_reg[] = अणु
		अणु "ERROR_CODE", BHI_ERRCODE पूर्ण,
		अणु "ERROR_DBG1", BHI_ERRDBG1 पूर्ण,
		अणु "ERROR_DBG2", BHI_ERRDBG2 पूर्ण,
		अणु "ERROR_DBG3", BHI_ERRDBG3 पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण;

	पढ़ो_lock_bh(pm_lock);
	अगर (!MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state)) अणु
		पढ़ो_unlock_bh(pm_lock);
		जाओ invalid_pm_state;
	पूर्ण

	session_id = MHI_RANDOM_U32_NONZERO(BHI_TXDB_SEQNUM_BMSK);
	dev_dbg(dev, "Starting image download via BHI. Session ID: %u\n",
		session_id);
	mhi_ग_लिखो_reg(mhi_cntrl, base, BHI_STATUS, 0);
	mhi_ग_लिखो_reg(mhi_cntrl, base, BHI_IMGADDR_HIGH,
		      upper_32_bits(dma_addr));
	mhi_ग_लिखो_reg(mhi_cntrl, base, BHI_IMGADDR_LOW,
		      lower_32_bits(dma_addr));
	mhi_ग_लिखो_reg(mhi_cntrl, base, BHI_IMGSIZE, size);
	mhi_ग_लिखो_reg(mhi_cntrl, base, BHI_IMGTXDB, session_id);
	पढ़ो_unlock_bh(pm_lock);

	/* Wait क्रम the image करोwnload to complete */
	ret = रुको_event_समयout(mhi_cntrl->state_event,
			   MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state) ||
			   mhi_पढ़ो_reg_field(mhi_cntrl, base, BHI_STATUS,
					      BHI_STATUS_MASK, BHI_STATUS_SHIFT,
					      &tx_status) || tx_status,
			   msecs_to_jअगरfies(mhi_cntrl->समयout_ms));
	अगर (MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state))
		जाओ invalid_pm_state;

	अगर (tx_status == BHI_STATUS_ERROR) अणु
		dev_err(dev, "Image transfer failed\n");
		पढ़ो_lock_bh(pm_lock);
		अगर (MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state)) अणु
			क्रम (i = 0; error_reg[i].name; i++) अणु
				ret = mhi_पढ़ो_reg(mhi_cntrl, base,
						   error_reg[i].offset, &val);
				अगर (ret)
					अवरोध;
				dev_err(dev, "Reg: %s value: 0x%x\n",
					error_reg[i].name, val);
			पूर्ण
		पूर्ण
		पढ़ो_unlock_bh(pm_lock);
		जाओ invalid_pm_state;
	पूर्ण

	वापस (!ret) ? -ETIMEDOUT : 0;

invalid_pm_state:

	वापस -EIO;
पूर्ण

व्योम mhi_मुक्त_bhie_table(काष्ठा mhi_controller *mhi_cntrl,
			 काष्ठा image_info *image_info)
अणु
	पूर्णांक i;
	काष्ठा mhi_buf *mhi_buf = image_info->mhi_buf;

	क्रम (i = 0; i < image_info->entries; i++, mhi_buf++)
		mhi_मुक्त_coherent(mhi_cntrl, mhi_buf->len, mhi_buf->buf,
				  mhi_buf->dma_addr);

	kमुक्त(image_info->mhi_buf);
	kमुक्त(image_info);
पूर्ण

पूर्णांक mhi_alloc_bhie_table(काष्ठा mhi_controller *mhi_cntrl,
			 काष्ठा image_info **image_info,
			 माप_प्रकार alloc_size)
अणु
	माप_प्रकार seg_size = mhi_cntrl->seg_len;
	पूर्णांक segments = DIV_ROUND_UP(alloc_size, seg_size) + 1;
	पूर्णांक i;
	काष्ठा image_info *img_info;
	काष्ठा mhi_buf *mhi_buf;

	img_info = kzalloc(माप(*img_info), GFP_KERNEL);
	अगर (!img_info)
		वापस -ENOMEM;

	/* Allocate memory क्रम entries */
	img_info->mhi_buf = kसुस्मृति(segments, माप(*img_info->mhi_buf),
				    GFP_KERNEL);
	अगर (!img_info->mhi_buf)
		जाओ error_alloc_mhi_buf;

	/* Allocate and populate vector table */
	mhi_buf = img_info->mhi_buf;
	क्रम (i = 0; i < segments; i++, mhi_buf++) अणु
		माप_प्रकार vec_size = seg_size;

		/* Vector table is the last entry */
		अगर (i == segments - 1)
			vec_size = माप(काष्ठा bhi_vec_entry) * i;

		mhi_buf->len = vec_size;
		mhi_buf->buf = mhi_alloc_coherent(mhi_cntrl, vec_size,
						  &mhi_buf->dma_addr,
						  GFP_KERNEL);
		अगर (!mhi_buf->buf)
			जाओ error_alloc_segment;
	पूर्ण

	img_info->bhi_vec = img_info->mhi_buf[segments - 1].buf;
	img_info->entries = segments;
	*image_info = img_info;

	वापस 0;

error_alloc_segment:
	क्रम (--i, --mhi_buf; i >= 0; i--, mhi_buf--)
		mhi_मुक्त_coherent(mhi_cntrl, mhi_buf->len, mhi_buf->buf,
				  mhi_buf->dma_addr);

error_alloc_mhi_buf:
	kमुक्त(img_info);

	वापस -ENOMEM;
पूर्ण

अटल व्योम mhi_firmware_copy(काष्ठा mhi_controller *mhi_cntrl,
			      स्थिर काष्ठा firmware *firmware,
			      काष्ठा image_info *img_info)
अणु
	माप_प्रकार reमुख्यder = firmware->size;
	माप_प्रकार to_cpy;
	स्थिर u8 *buf = firmware->data;
	काष्ठा mhi_buf *mhi_buf = img_info->mhi_buf;
	काष्ठा bhi_vec_entry *bhi_vec = img_info->bhi_vec;

	जबतक (reमुख्यder) अणु
		to_cpy = min(reमुख्यder, mhi_buf->len);
		स_नकल(mhi_buf->buf, buf, to_cpy);
		bhi_vec->dma_addr = mhi_buf->dma_addr;
		bhi_vec->size = to_cpy;

		buf += to_cpy;
		reमुख्यder -= to_cpy;
		bhi_vec++;
		mhi_buf++;
	पूर्ण
पूर्ण

व्योम mhi_fw_load_handler(काष्ठा mhi_controller *mhi_cntrl)
अणु
	स्थिर काष्ठा firmware *firmware = शून्य;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	स्थिर अक्षर *fw_name;
	व्योम *buf;
	dma_addr_t dma_addr;
	माप_प्रकार size;
	पूर्णांक i, ret;

	अगर (MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state)) अणु
		dev_err(dev, "Device MHI is not in valid state\n");
		वापस;
	पूर्ण

	/* save hardware info from BHI */
	ret = mhi_पढ़ो_reg(mhi_cntrl, mhi_cntrl->bhi, BHI_SERIALNU,
			   &mhi_cntrl->serial_number);
	अगर (ret)
		dev_err(dev, "Could not capture serial number via BHI\n");

	क्रम (i = 0; i < ARRAY_SIZE(mhi_cntrl->oem_pk_hash); i++) अणु
		ret = mhi_पढ़ो_reg(mhi_cntrl, mhi_cntrl->bhi, BHI_OEMPKHASH(i),
				   &mhi_cntrl->oem_pk_hash[i]);
		अगर (ret) अणु
			dev_err(dev, "Could not capture OEM PK HASH via BHI\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/* रुको क्रम पढ़ोy on pass through or any other execution environment */
	अगर (mhi_cntrl->ee != MHI_EE_EDL && mhi_cntrl->ee != MHI_EE_PBL)
		जाओ fw_load_पढ़ोy_state;

	fw_name = (mhi_cntrl->ee == MHI_EE_EDL) ?
		mhi_cntrl->edl_image : mhi_cntrl->fw_image;

	अगर (!fw_name || (mhi_cntrl->fbc_करोwnload && (!mhi_cntrl->sbl_size ||
						     !mhi_cntrl->seg_len))) अणु
		dev_err(dev,
			"No firmware image defined or !sbl_size || !seg_len\n");
		जाओ error_fw_load;
	पूर्ण

	ret = request_firmware(&firmware, fw_name, dev);
	अगर (ret) अणु
		dev_err(dev, "Error loading firmware: %d\n", ret);
		जाओ error_fw_load;
	पूर्ण

	size = (mhi_cntrl->fbc_करोwnload) ? mhi_cntrl->sbl_size : firmware->size;

	/* SBL size provided is maximum size, not necessarily the image size */
	अगर (size > firmware->size)
		size = firmware->size;

	buf = mhi_alloc_coherent(mhi_cntrl, size, &dma_addr, GFP_KERNEL);
	अगर (!buf) अणु
		release_firmware(firmware);
		जाओ error_fw_load;
	पूर्ण

	/* Download image using BHI */
	स_नकल(buf, firmware->data, size);
	ret = mhi_fw_load_bhi(mhi_cntrl, dma_addr, size);
	mhi_मुक्त_coherent(mhi_cntrl, size, buf, dma_addr);

	/* Error or in EDL mode, we're करोne */
	अगर (ret) अणु
		dev_err(dev, "MHI did not load image over BHI, ret: %d\n", ret);
		release_firmware(firmware);
		जाओ error_fw_load;
	पूर्ण

	/* Wait क्रम पढ़ोy since EDL image was loaded */
	अगर (fw_name == mhi_cntrl->edl_image) अणु
		release_firmware(firmware);
		जाओ fw_load_पढ़ोy_state;
	पूर्ण

	ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
	mhi_cntrl->dev_state = MHI_STATE_RESET;
	ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);

	/*
	 * If we're करोing fbc, populate vector tables जबतक
	 * device transitioning पूर्णांकo MHI READY state
	 */
	अगर (mhi_cntrl->fbc_करोwnload) अणु
		ret = mhi_alloc_bhie_table(mhi_cntrl, &mhi_cntrl->fbc_image,
					   firmware->size);
		अगर (ret) अणु
			release_firmware(firmware);
			जाओ error_fw_load;
		पूर्ण

		/* Load the firmware पूर्णांकo BHIE vec table */
		mhi_firmware_copy(mhi_cntrl, firmware, mhi_cntrl->fbc_image);
	पूर्ण

	release_firmware(firmware);

fw_load_पढ़ोy_state:
	/* Transitioning पूर्णांकo MHI RESET->READY state */
	ret = mhi_पढ़ोy_state_transition(mhi_cntrl);
	अगर (ret) अणु
		dev_err(dev, "MHI did not enter READY state\n");
		जाओ error_पढ़ोy_state;
	पूर्ण

	dev_info(dev, "Wait for device to enter SBL or Mission mode\n");
	वापस;

error_पढ़ोy_state:
	अगर (mhi_cntrl->fbc_करोwnload) अणु
		mhi_मुक्त_bhie_table(mhi_cntrl, mhi_cntrl->fbc_image);
		mhi_cntrl->fbc_image = शून्य;
	पूर्ण

error_fw_load:
	mhi_cntrl->pm_state = MHI_PM_FW_DL_ERR;
	wake_up_all(&mhi_cntrl->state_event);
पूर्ण

पूर्णांक mhi_करोwnload_amss_image(काष्ठा mhi_controller *mhi_cntrl)
अणु
	काष्ठा image_info *image_info = mhi_cntrl->fbc_image;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	पूर्णांक ret;

	अगर (!image_info)
		वापस -EIO;

	ret = mhi_fw_load_bhie(mhi_cntrl,
			       /* Vector table is the last entry */
			       &image_info->mhi_buf[image_info->entries - 1]);
	अगर (ret) अणु
		dev_err(dev, "MHI did not load AMSS, ret:%d\n", ret);
		mhi_cntrl->pm_state = MHI_PM_FW_DL_ERR;
		wake_up_all(&mhi_cntrl->state_event);
	पूर्ण

	वापस ret;
पूर्ण
