<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2005-2014, 2018-2019 Intel Corporation
 */
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

#समावेश "iwl-drv.h"
#समावेश "iwl-debug.h"
#समावेश "iwl-eeprom-read.h"
#समावेश "iwl-io.h"
#समावेश "iwl-prph.h"
#समावेश "iwl-csr.h"

/*
 * EEPROM access समय values:
 *
 * Driver initiates EEPROM पढ़ो by writing byte address << 1 to CSR_EEPROM_REG.
 * Driver then polls CSR_EEPROM_REG क्रम CSR_EEPROM_REG_READ_VALID_MSK (0x1).
 * When polling, रुको 10 uSec between polling loops, up to a maximum 5000 uSec.
 * Driver पढ़ोs 16-bit value from bits 31-16 of CSR_EEPROM_REG.
 */
#घोषणा IWL_EEPROM_ACCESS_TIMEOUT	5000 /* uSec */

#घोषणा IWL_EEPROM_SEM_TIMEOUT		10   /* microseconds */
#घोषणा IWL_EEPROM_SEM_RETRY_LIMIT	1000 /* number of attempts (not समय) */


/*
 * The device's EEPROM semaphore prevents conflicts between driver and uCode
 * when accessing the EEPROM; each access is a series of pulses to/from the
 * EEPROM chip, not a single event, so even पढ़ोs could conflict अगर they
 * weren't arbitrated by the semaphore.
 */

#घोषणा	EEPROM_SEM_TIMEOUT 10		/* milliseconds */
#घोषणा EEPROM_SEM_RETRY_LIMIT 1000	/* number of attempts (not समय) */

अटल पूर्णांक iwl_eeprom_acquire_semaphore(काष्ठा iwl_trans *trans)
अणु
	u16 count;
	पूर्णांक ret;

	क्रम (count = 0; count < EEPROM_SEM_RETRY_LIMIT; count++) अणु
		/* Request semaphore */
		iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
			    CSR_HW_IF_CONFIG_REG_BIT_EEPROM_OWN_SEM);

		/* See अगर we got it */
		ret = iwl_poll_bit(trans, CSR_HW_IF_CONFIG_REG,
				CSR_HW_IF_CONFIG_REG_BIT_EEPROM_OWN_SEM,
				CSR_HW_IF_CONFIG_REG_BIT_EEPROM_OWN_SEM,
				EEPROM_SEM_TIMEOUT);
		अगर (ret >= 0) अणु
			IWL_DEBUG_EEPROM(trans->dev,
					 "Acquired semaphore after %d tries.\n",
					 count+1);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम iwl_eeprom_release_semaphore(काष्ठा iwl_trans *trans)
अणु
	iwl_clear_bit(trans, CSR_HW_IF_CONFIG_REG,
		      CSR_HW_IF_CONFIG_REG_BIT_EEPROM_OWN_SEM);
पूर्ण

अटल पूर्णांक iwl_eeprom_verअगरy_signature(काष्ठा iwl_trans *trans, bool nvm_is_otp)
अणु
	u32 gp = iwl_पढ़ो32(trans, CSR_EEPROM_GP) & CSR_EEPROM_GP_VALID_MSK;

	IWL_DEBUG_EEPROM(trans->dev, "EEPROM signature=0x%08x\n", gp);

	चयन (gp) अणु
	हाल CSR_EEPROM_GP_BAD_SIG_EEP_GOOD_SIG_OTP:
		अगर (!nvm_is_otp) अणु
			IWL_ERR(trans, "EEPROM with bad signature: 0x%08x\n",
				gp);
			वापस -ENOENT;
		पूर्ण
		वापस 0;
	हाल CSR_EEPROM_GP_GOOD_SIG_EEP_LESS_THAN_4K:
	हाल CSR_EEPROM_GP_GOOD_SIG_EEP_MORE_THAN_4K:
		अगर (nvm_is_otp) अणु
			IWL_ERR(trans, "OTP with bad signature: 0x%08x\n", gp);
			वापस -ENOENT;
		पूर्ण
		वापस 0;
	हाल CSR_EEPROM_GP_BAD_SIGNATURE_BOTH_EEP_AND_OTP:
	शेष:
		IWL_ERR(trans,
			"bad EEPROM/OTP signature, type=%s, EEPROM_GP=0x%08x\n",
			nvm_is_otp ? "OTP" : "EEPROM", gp);
		वापस -ENOENT;
	पूर्ण
पूर्ण

/******************************************************************************
 *
 * OTP related functions
 *
******************************************************************************/

अटल व्योम iwl_set_otp_access_असलolute(काष्ठा iwl_trans *trans)
अणु
	iwl_पढ़ो32(trans, CSR_OTP_GP_REG);

	iwl_clear_bit(trans, CSR_OTP_GP_REG,
		      CSR_OTP_GP_REG_OTP_ACCESS_MODE);
पूर्ण

अटल पूर्णांक iwl_nvm_is_otp(काष्ठा iwl_trans *trans)
अणु
	u32 otpgp;

	/* OTP only valid क्रम CP/PP and after */
	चयन (trans->hw_rev & CSR_HW_REV_TYPE_MSK) अणु
	हाल CSR_HW_REV_TYPE_NONE:
		IWL_ERR(trans, "Unknown hardware type\n");
		वापस -EIO;
	हाल CSR_HW_REV_TYPE_5300:
	हाल CSR_HW_REV_TYPE_5350:
	हाल CSR_HW_REV_TYPE_5100:
	हाल CSR_HW_REV_TYPE_5150:
		वापस 0;
	शेष:
		otpgp = iwl_पढ़ो32(trans, CSR_OTP_GP_REG);
		अगर (otpgp & CSR_OTP_GP_REG_DEVICE_SELECT)
			वापस 1;
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक iwl_init_otp_access(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक ret;

	ret = iwl_finish_nic_init(trans, trans->trans_cfg);
	अगर (ret)
		वापस ret;

	iwl_set_bits_prph(trans, APMG_PS_CTRL_REG,
			  APMG_PS_CTRL_VAL_RESET_REQ);
	udelay(5);
	iwl_clear_bits_prph(trans, APMG_PS_CTRL_REG,
			    APMG_PS_CTRL_VAL_RESET_REQ);

	/*
	 * CSR स्वतः घड़ी gate disable bit -
	 * this is only applicable क्रम HW with OTP shaकरोw RAM
	 */
	अगर (trans->trans_cfg->base_params->shaकरोw_ram_support)
		iwl_set_bit(trans, CSR_DBG_LINK_PWR_MGMT_REG,
			    CSR_RESET_LINK_PWR_MGMT_DISABLED);

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_पढ़ो_otp_word(काष्ठा iwl_trans *trans, u16 addr,
			     __le16 *eeprom_data)
अणु
	पूर्णांक ret = 0;
	u32 r;
	u32 otpgp;

	iwl_ग_लिखो32(trans, CSR_EEPROM_REG,
		    CSR_EEPROM_REG_MSK_ADDR & (addr << 1));
	ret = iwl_poll_bit(trans, CSR_EEPROM_REG,
				 CSR_EEPROM_REG_READ_VALID_MSK,
				 CSR_EEPROM_REG_READ_VALID_MSK,
				 IWL_EEPROM_ACCESS_TIMEOUT);
	अगर (ret < 0) अणु
		IWL_ERR(trans, "Time out reading OTP[%d]\n", addr);
		वापस ret;
	पूर्ण
	r = iwl_पढ़ो32(trans, CSR_EEPROM_REG);
	/* check क्रम ECC errors: */
	otpgp = iwl_पढ़ो32(trans, CSR_OTP_GP_REG);
	अगर (otpgp & CSR_OTP_GP_REG_ECC_UNCORR_STATUS_MSK) अणु
		/* stop in this हाल */
		/* set the uncorrectable OTP ECC bit क्रम acknowledgment */
		iwl_set_bit(trans, CSR_OTP_GP_REG,
			    CSR_OTP_GP_REG_ECC_UNCORR_STATUS_MSK);
		IWL_ERR(trans, "Uncorrectable OTP ECC error, abort OTP read\n");
		वापस -EINVAL;
	पूर्ण
	अगर (otpgp & CSR_OTP_GP_REG_ECC_CORR_STATUS_MSK) अणु
		/* जारी in this हाल */
		/* set the correctable OTP ECC bit क्रम acknowledgment */
		iwl_set_bit(trans, CSR_OTP_GP_REG,
			    CSR_OTP_GP_REG_ECC_CORR_STATUS_MSK);
		IWL_ERR(trans, "Correctable OTP ECC error, continue read\n");
	पूर्ण
	*eeprom_data = cpu_to_le16(r >> 16);
	वापस 0;
पूर्ण

/*
 * iwl_is_otp_empty: check क्रम empty OTP
 */
अटल bool iwl_is_otp_empty(काष्ठा iwl_trans *trans)
अणु
	u16 next_link_addr = 0;
	__le16 link_value;
	bool is_empty = false;

	/* locate the beginning of OTP link list */
	अगर (!iwl_पढ़ो_otp_word(trans, next_link_addr, &link_value)) अणु
		अगर (!link_value) अणु
			IWL_ERR(trans, "OTP is empty\n");
			is_empty = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		IWL_ERR(trans, "Unable to read first block of OTP list.\n");
		is_empty = true;
	पूर्ण

	वापस is_empty;
पूर्ण


/*
 * iwl_find_otp_image: find EEPROM image in OTP
 *   finding the OTP block that contains the EEPROM image.
 *   the last valid block on the link list (the block _beक्रमe_ the last block)
 *   is the block we should पढ़ो and used to configure the device.
 *   If all the available OTP blocks are full, the last block will be the block
 *   we should पढ़ो and used to configure the device.
 *   only perक्रमm this operation अगर shaकरोw RAM is disabled
 */
अटल पूर्णांक iwl_find_otp_image(काष्ठा iwl_trans *trans,
					u16 *validblockaddr)
अणु
	u16 next_link_addr = 0, valid_addr;
	__le16 link_value = 0;
	पूर्णांक usedblocks = 0;

	/* set addressing mode to असलolute to traverse the link list */
	iwl_set_otp_access_असलolute(trans);

	/* checking क्रम empty OTP or error */
	अगर (iwl_is_otp_empty(trans))
		वापस -EINVAL;

	/*
	 * start traverse link list
	 * until reach the max number of OTP blocks
	 * dअगरferent devices have dअगरferent number of OTP blocks
	 */
	करो अणु
		/* save current valid block address
		 * check क्रम more block on the link list
		 */
		valid_addr = next_link_addr;
		next_link_addr = le16_to_cpu(link_value) * माप(u16);
		IWL_DEBUG_EEPROM(trans->dev, "OTP blocks %d addr 0x%x\n",
				 usedblocks, next_link_addr);
		अगर (iwl_पढ़ो_otp_word(trans, next_link_addr, &link_value))
			वापस -EINVAL;
		अगर (!link_value) अणु
			/*
			 * reach the end of link list, वापस success and
			 * set address poपूर्णांक to the starting address
			 * of the image
			 */
			*validblockaddr = valid_addr;
			/* skip first 2 bytes (link list poपूर्णांकer) */
			*validblockaddr += 2;
			वापस 0;
		पूर्ण
		/* more in the link list, जारी */
		usedblocks++;
	पूर्ण जबतक (usedblocks <= trans->trans_cfg->base_params->max_ll_items);

	/* OTP has no valid blocks */
	IWL_DEBUG_EEPROM(trans->dev, "OTP has no valid blocks\n");
	वापस -EINVAL;
पूर्ण

/*
 * iwl_पढ़ो_eeprom - पढ़ो EEPROM contents
 *
 * Load the EEPROM contents from adapter and वापस it
 * and its size.
 *
 * NOTE:  This routine uses the non-debug IO access functions.
 */
पूर्णांक iwl_पढ़ो_eeprom(काष्ठा iwl_trans *trans, u8 **eeprom, माप_प्रकार *eeprom_size)
अणु
	__le16 *e;
	u32 gp = iwl_पढ़ो32(trans, CSR_EEPROM_GP);
	पूर्णांक sz;
	पूर्णांक ret;
	u16 addr;
	u16 validblockaddr = 0;
	u16 cache_addr = 0;
	पूर्णांक nvm_is_otp;

	अगर (!eeprom || !eeprom_size)
		वापस -EINVAL;

	nvm_is_otp = iwl_nvm_is_otp(trans);
	अगर (nvm_is_otp < 0)
		वापस nvm_is_otp;

	sz = trans->trans_cfg->base_params->eeprom_size;
	IWL_DEBUG_EEPROM(trans->dev, "NVM size = %d\n", sz);

	e = kदो_स्मृति(sz, GFP_KERNEL);
	अगर (!e)
		वापस -ENOMEM;

	ret = iwl_eeprom_verअगरy_signature(trans, nvm_is_otp);
	अगर (ret < 0) अणु
		IWL_ERR(trans, "EEPROM not found, EEPROM_GP=0x%08x\n", gp);
		जाओ err_मुक्त;
	पूर्ण

	/* Make sure driver (instead of uCode) is allowed to पढ़ो EEPROM */
	ret = iwl_eeprom_acquire_semaphore(trans);
	अगर (ret < 0) अणु
		IWL_ERR(trans, "Failed to acquire EEPROM semaphore.\n");
		जाओ err_मुक्त;
	पूर्ण

	अगर (nvm_is_otp) अणु
		ret = iwl_init_otp_access(trans);
		अगर (ret) अणु
			IWL_ERR(trans, "Failed to initialize OTP access.\n");
			जाओ err_unlock;
		पूर्ण

		iwl_ग_लिखो32(trans, CSR_EEPROM_GP,
			    iwl_पढ़ो32(trans, CSR_EEPROM_GP) &
			    ~CSR_EEPROM_GP_IF_OWNER_MSK);

		iwl_set_bit(trans, CSR_OTP_GP_REG,
			    CSR_OTP_GP_REG_ECC_CORR_STATUS_MSK |
			    CSR_OTP_GP_REG_ECC_UNCORR_STATUS_MSK);
		/* traversing the linked list अगर no shaकरोw ram supported */
		अगर (!trans->trans_cfg->base_params->shaकरोw_ram_support) अणु
			ret = iwl_find_otp_image(trans, &validblockaddr);
			अगर (ret)
				जाओ err_unlock;
		पूर्ण
		क्रम (addr = validblockaddr; addr < validblockaddr + sz;
		     addr += माप(u16)) अणु
			__le16 eeprom_data;

			ret = iwl_पढ़ो_otp_word(trans, addr, &eeprom_data);
			अगर (ret)
				जाओ err_unlock;
			e[cache_addr / 2] = eeprom_data;
			cache_addr += माप(u16);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* eeprom is an array of 16bit values */
		क्रम (addr = 0; addr < sz; addr += माप(u16)) अणु
			u32 r;

			iwl_ग_लिखो32(trans, CSR_EEPROM_REG,
				    CSR_EEPROM_REG_MSK_ADDR & (addr << 1));

			ret = iwl_poll_bit(trans, CSR_EEPROM_REG,
					   CSR_EEPROM_REG_READ_VALID_MSK,
					   CSR_EEPROM_REG_READ_VALID_MSK,
					   IWL_EEPROM_ACCESS_TIMEOUT);
			अगर (ret < 0) अणु
				IWL_ERR(trans,
					"Time out reading EEPROM[%d]\n", addr);
				जाओ err_unlock;
			पूर्ण
			r = iwl_पढ़ो32(trans, CSR_EEPROM_REG);
			e[addr / 2] = cpu_to_le16(r >> 16);
		पूर्ण
	पूर्ण

	IWL_DEBUG_EEPROM(trans->dev, "NVM Type: %s\n",
			 nvm_is_otp ? "OTP" : "EEPROM");

	iwl_eeprom_release_semaphore(trans);

	*eeprom_size = sz;
	*eeprom = (u8 *)e;
	वापस 0;

 err_unlock:
	iwl_eeprom_release_semaphore(trans);
 err_मुक्त:
	kमुक्त(e);

	वापस ret;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_पढ़ो_eeprom);
