<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2015 - 2020 Intel Corporation */
#समावेश <linux/delay.h>
#समावेश "adf_accel_devices.h"
#समावेश "adf_common_drv.h"
#समावेश "adf_pf2vf_msg.h"

#घोषणा ADF_DH895XCC_EP_OFFSET	0x3A000
#घोषणा ADF_DH895XCC_ERRMSK3	(ADF_DH895XCC_EP_OFFSET + 0x1C)
#घोषणा ADF_DH895XCC_ERRMSK3_VF2PF_L_MASK(vf_mask) ((vf_mask & 0xFFFF) << 9)
#घोषणा ADF_DH895XCC_ERRMSK5	(ADF_DH895XCC_EP_OFFSET + 0xDC)
#घोषणा ADF_DH895XCC_ERRMSK5_VF2PF_U_MASK(vf_mask) (vf_mask >> 16)

व्योम adf_enable_pf2vf_पूर्णांकerrupts(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_accel_pci *pci_info = &accel_dev->accel_pci_dev;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	व्योम __iomem *pmisc_bar_addr =
		pci_info->pci_bars[hw_data->get_misc_bar_id(hw_data)].virt_addr;

	ADF_CSR_WR(pmisc_bar_addr, hw_data->get_vपूर्णांकmsk_offset(0), 0x0);
पूर्ण

व्योम adf_disable_pf2vf_पूर्णांकerrupts(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_accel_pci *pci_info = &accel_dev->accel_pci_dev;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	व्योम __iomem *pmisc_bar_addr =
		pci_info->pci_bars[hw_data->get_misc_bar_id(hw_data)].virt_addr;

	ADF_CSR_WR(pmisc_bar_addr, hw_data->get_vपूर्णांकmsk_offset(0), 0x2);
पूर्ण

व्योम adf_enable_vf2pf_पूर्णांकerrupts(काष्ठा adf_accel_dev *accel_dev,
				 u32 vf_mask)
अणु
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	काष्ठा adf_bar *pmisc =
			&GET_BARS(accel_dev)[hw_data->get_misc_bar_id(hw_data)];
	व्योम __iomem *pmisc_addr = pmisc->virt_addr;
	u32 reg;

	/* Enable VF2PF Messaging Ints - VFs 1 through 16 per vf_mask[15:0] */
	अगर (vf_mask & 0xFFFF) अणु
		reg = ADF_CSR_RD(pmisc_addr, ADF_DH895XCC_ERRMSK3);
		reg &= ~ADF_DH895XCC_ERRMSK3_VF2PF_L_MASK(vf_mask);
		ADF_CSR_WR(pmisc_addr, ADF_DH895XCC_ERRMSK3, reg);
	पूर्ण

	/* Enable VF2PF Messaging Ints - VFs 17 through 32 per vf_mask[31:16] */
	अगर (vf_mask >> 16) अणु
		reg = ADF_CSR_RD(pmisc_addr, ADF_DH895XCC_ERRMSK5);
		reg &= ~ADF_DH895XCC_ERRMSK5_VF2PF_U_MASK(vf_mask);
		ADF_CSR_WR(pmisc_addr, ADF_DH895XCC_ERRMSK5, reg);
	पूर्ण
पूर्ण

व्योम adf_disable_vf2pf_पूर्णांकerrupts(काष्ठा adf_accel_dev *accel_dev, u32 vf_mask)
अणु
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	काष्ठा adf_bar *pmisc =
			&GET_BARS(accel_dev)[hw_data->get_misc_bar_id(hw_data)];
	व्योम __iomem *pmisc_addr = pmisc->virt_addr;
	u32 reg;

	/* Disable VF2PF पूर्णांकerrupts क्रम VFs 1 through 16 per vf_mask[15:0] */
	अगर (vf_mask & 0xFFFF) अणु
		reg = ADF_CSR_RD(pmisc_addr, ADF_DH895XCC_ERRMSK3) |
			ADF_DH895XCC_ERRMSK3_VF2PF_L_MASK(vf_mask);
		ADF_CSR_WR(pmisc_addr, ADF_DH895XCC_ERRMSK3, reg);
	पूर्ण

	/* Disable VF2PF पूर्णांकerrupts क्रम VFs 17 through 32 per vf_mask[31:16] */
	अगर (vf_mask >> 16) अणु
		reg = ADF_CSR_RD(pmisc_addr, ADF_DH895XCC_ERRMSK5) |
			ADF_DH895XCC_ERRMSK5_VF2PF_U_MASK(vf_mask);
		ADF_CSR_WR(pmisc_addr, ADF_DH895XCC_ERRMSK5, reg);
	पूर्ण
पूर्ण

अटल पूर्णांक __adf_iov_puपंचांगsg(काष्ठा adf_accel_dev *accel_dev, u32 msg, u8 vf_nr)
अणु
	काष्ठा adf_accel_pci *pci_info = &accel_dev->accel_pci_dev;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	व्योम __iomem *pmisc_bar_addr =
		pci_info->pci_bars[hw_data->get_misc_bar_id(hw_data)].virt_addr;
	u32 val, pf2vf_offset, count = 0;
	u32 local_in_use_mask, local_in_use_pattern;
	u32 remote_in_use_mask, remote_in_use_pattern;
	काष्ठा mutex *lock;	/* lock preventing concurrent acces of CSR */
	u32 पूर्णांक_bit;
	पूर्णांक ret = 0;

	अगर (accel_dev->is_vf) अणु
		pf2vf_offset = hw_data->get_pf2vf_offset(0);
		lock = &accel_dev->vf.vf2pf_lock;
		local_in_use_mask = ADF_VF2PF_IN_USE_BY_VF_MASK;
		local_in_use_pattern = ADF_VF2PF_IN_USE_BY_VF;
		remote_in_use_mask = ADF_PF2VF_IN_USE_BY_PF_MASK;
		remote_in_use_pattern = ADF_PF2VF_IN_USE_BY_PF;
		पूर्णांक_bit = ADF_VF2PF_INT;
	पूर्ण अन्यथा अणु
		pf2vf_offset = hw_data->get_pf2vf_offset(vf_nr);
		lock = &accel_dev->pf.vf_info[vf_nr].pf2vf_lock;
		local_in_use_mask = ADF_PF2VF_IN_USE_BY_PF_MASK;
		local_in_use_pattern = ADF_PF2VF_IN_USE_BY_PF;
		remote_in_use_mask = ADF_VF2PF_IN_USE_BY_VF_MASK;
		remote_in_use_pattern = ADF_VF2PF_IN_USE_BY_VF;
		पूर्णांक_bit = ADF_PF2VF_INT;
	पूर्ण

	mutex_lock(lock);

	/* Check अगर PF2VF CSR is in use by remote function */
	val = ADF_CSR_RD(pmisc_bar_addr, pf2vf_offset);
	अगर ((val & remote_in_use_mask) == remote_in_use_pattern) अणु
		dev_dbg(&GET_DEV(accel_dev),
			"PF2VF CSR in use by remote function\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/* Attempt to get ownership of PF2VF CSR */
	msg &= ~local_in_use_mask;
	msg |= local_in_use_pattern;
	ADF_CSR_WR(pmisc_bar_addr, pf2vf_offset, msg);

	/* Wait in हाल remote func also attempting to get ownership */
	msleep(ADF_IOV_MSG_COLLISION_DETECT_DELAY);

	val = ADF_CSR_RD(pmisc_bar_addr, pf2vf_offset);
	अगर ((val & local_in_use_mask) != local_in_use_pattern) अणु
		dev_dbg(&GET_DEV(accel_dev),
			"PF2VF CSR in use by remote - collision detected\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * This function now owns the PV2VF CSR.  The IN_USE_BY pattern must
	 * reमुख्य in the PF2VF CSR क्रम all ग_लिखोs including ACK from remote
	 * until this local function relinquishes the CSR.  Send the message
	 * by पूर्णांकerrupting the remote.
	 */
	ADF_CSR_WR(pmisc_bar_addr, pf2vf_offset, msg | पूर्णांक_bit);

	/* Wait क्रम confirmation from remote func it received the message */
	करो अणु
		msleep(ADF_IOV_MSG_ACK_DELAY);
		val = ADF_CSR_RD(pmisc_bar_addr, pf2vf_offset);
	पूर्ण जबतक ((val & पूर्णांक_bit) && (count++ < ADF_IOV_MSG_ACK_MAX_RETRY));

	अगर (val & पूर्णांक_bit) अणु
		dev_dbg(&GET_DEV(accel_dev), "ACK not received from remote\n");
		val &= ~पूर्णांक_bit;
		ret = -EIO;
	पूर्ण

	/* Finished with PF2VF CSR; relinquish it and leave msg in CSR */
	ADF_CSR_WR(pmisc_bar_addr, pf2vf_offset, val & ~local_in_use_mask);
out:
	mutex_unlock(lock);
	वापस ret;
पूर्ण

/**
 * adf_iov_puपंचांगsg() - send PF2VF message
 * @accel_dev:  Poपूर्णांकer to acceleration device.
 * @msg:	Message to send
 * @vf_nr:	VF number to which the message will be sent
 *
 * Function sends a message from the PF to a VF
 *
 * Return: 0 on success, error code otherwise.
 */
पूर्णांक adf_iov_puपंचांगsg(काष्ठा adf_accel_dev *accel_dev, u32 msg, u8 vf_nr)
अणु
	u32 count = 0;
	पूर्णांक ret;

	करो अणु
		ret = __adf_iov_puपंचांगsg(accel_dev, msg, vf_nr);
		अगर (ret)
			msleep(ADF_IOV_MSG_RETRY_DELAY);
	पूर्ण जबतक (ret && (count++ < ADF_IOV_MSG_MAX_RETRIES));

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(adf_iov_puपंचांगsg);

व्योम adf_vf2pf_req_hndl(काष्ठा adf_accel_vf_info *vf_info)
अणु
	काष्ठा adf_accel_dev *accel_dev = vf_info->accel_dev;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	पूर्णांक bar_id = hw_data->get_misc_bar_id(hw_data);
	काष्ठा adf_bar *pmisc = &GET_BARS(accel_dev)[bar_id];
	व्योम __iomem *pmisc_addr = pmisc->virt_addr;
	u32 msg, resp = 0, vf_nr = vf_info->vf_nr;

	/* Read message from the VF */
	msg = ADF_CSR_RD(pmisc_addr, hw_data->get_pf2vf_offset(vf_nr));

	/* To ACK, clear the VF2PFINT bit */
	msg &= ~ADF_VF2PF_INT;
	ADF_CSR_WR(pmisc_addr, hw_data->get_pf2vf_offset(vf_nr), msg);

	अगर (!(msg & ADF_VF2PF_MSGORIGIN_SYSTEM))
		/* Ignore legacy non-प्रणाली (non-kernel) VF2PF messages */
		जाओ err;

	चयन ((msg & ADF_VF2PF_MSGTYPE_MASK) >> ADF_VF2PF_MSGTYPE_SHIFT) अणु
	हाल ADF_VF2PF_MSGTYPE_COMPAT_VER_REQ:
		अणु
		u8 vf_compat_ver = msg >> ADF_VF2PF_COMPAT_VER_REQ_SHIFT;

		resp = (ADF_PF2VF_MSGORIGIN_SYSTEM |
			 (ADF_PF2VF_MSGTYPE_VERSION_RESP <<
			  ADF_PF2VF_MSGTYPE_SHIFT) |
			 (ADF_PFVF_COMPATIBILITY_VERSION <<
			  ADF_PF2VF_VERSION_RESP_VERS_SHIFT));

		dev_dbg(&GET_DEV(accel_dev),
			"Compatibility Version Request from VF%d vers=%u\n",
			vf_nr + 1, vf_compat_ver);

		अगर (vf_compat_ver < hw_data->min_iov_compat_ver) अणु
			dev_err(&GET_DEV(accel_dev),
				"VF (vers %d) incompatible with PF (vers %d)\n",
				vf_compat_ver, ADF_PFVF_COMPATIBILITY_VERSION);
			resp |= ADF_PF2VF_VF_INCOMPATIBLE <<
				ADF_PF2VF_VERSION_RESP_RESULT_SHIFT;
		पूर्ण अन्यथा अगर (vf_compat_ver > ADF_PFVF_COMPATIBILITY_VERSION) अणु
			dev_err(&GET_DEV(accel_dev),
				"VF (vers %d) compat with PF (vers %d) unkn.\n",
				vf_compat_ver, ADF_PFVF_COMPATIBILITY_VERSION);
			resp |= ADF_PF2VF_VF_COMPAT_UNKNOWN <<
				ADF_PF2VF_VERSION_RESP_RESULT_SHIFT;
		पूर्ण अन्यथा अणु
			dev_dbg(&GET_DEV(accel_dev),
				"VF (vers %d) compatible with PF (vers %d)\n",
				vf_compat_ver, ADF_PFVF_COMPATIBILITY_VERSION);
			resp |= ADF_PF2VF_VF_COMPATIBLE <<
				ADF_PF2VF_VERSION_RESP_RESULT_SHIFT;
		पूर्ण
		पूर्ण
		अवरोध;
	हाल ADF_VF2PF_MSGTYPE_VERSION_REQ:
		dev_dbg(&GET_DEV(accel_dev),
			"Legacy VersionRequest received from VF%d 0x%x\n",
			vf_nr + 1, msg);
		resp = (ADF_PF2VF_MSGORIGIN_SYSTEM |
			 (ADF_PF2VF_MSGTYPE_VERSION_RESP <<
			  ADF_PF2VF_MSGTYPE_SHIFT) |
			 (ADF_PFVF_COMPATIBILITY_VERSION <<
			  ADF_PF2VF_VERSION_RESP_VERS_SHIFT));
		resp |= ADF_PF2VF_VF_COMPATIBLE <<
			ADF_PF2VF_VERSION_RESP_RESULT_SHIFT;
		/* Set legacy major and minor version num */
		resp |= 1 << ADF_PF2VF_MAJORVERSION_SHIFT |
			1 << ADF_PF2VF_MINORVERSION_SHIFT;
		अवरोध;
	हाल ADF_VF2PF_MSGTYPE_INIT:
		अणु
		dev_dbg(&GET_DEV(accel_dev),
			"Init message received from VF%d 0x%x\n",
			vf_nr + 1, msg);
		vf_info->init = true;
		पूर्ण
		अवरोध;
	हाल ADF_VF2PF_MSGTYPE_SHUTDOWN:
		अणु
		dev_dbg(&GET_DEV(accel_dev),
			"Shutdown message received from VF%d 0x%x\n",
			vf_nr + 1, msg);
		vf_info->init = false;
		पूर्ण
		अवरोध;
	शेष:
		जाओ err;
	पूर्ण

	अगर (resp && adf_iov_puपंचांगsg(accel_dev, resp, vf_nr))
		dev_err(&GET_DEV(accel_dev), "Failed to send response to VF\n");

	/* re-enable पूर्णांकerrupt on PF from this VF */
	adf_enable_vf2pf_पूर्णांकerrupts(accel_dev, (1 << vf_nr));
	वापस;
err:
	dev_dbg(&GET_DEV(accel_dev), "Unknown message from VF%d (0x%x);\n",
		vf_nr + 1, msg);
पूर्ण

व्योम adf_pf2vf_notअगरy_restarting(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_accel_vf_info *vf;
	u32 msg = (ADF_PF2VF_MSGORIGIN_SYSTEM |
		(ADF_PF2VF_MSGTYPE_RESTARTING << ADF_PF2VF_MSGTYPE_SHIFT));
	पूर्णांक i, num_vfs = pci_num_vf(accel_to_pci_dev(accel_dev));

	क्रम (i = 0, vf = accel_dev->pf.vf_info; i < num_vfs; i++, vf++) अणु
		अगर (vf->init && adf_iov_puपंचांगsg(accel_dev, msg, i))
			dev_err(&GET_DEV(accel_dev),
				"Failed to send restarting msg to VF%d\n", i);
	पूर्ण
पूर्ण

अटल पूर्णांक adf_vf2pf_request_version(काष्ठा adf_accel_dev *accel_dev)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(ADF_IOV_MSG_RESP_TIMEOUT);
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	u32 msg = 0;
	पूर्णांक ret;

	msg = ADF_VF2PF_MSGORIGIN_SYSTEM;
	msg |= ADF_VF2PF_MSGTYPE_COMPAT_VER_REQ << ADF_VF2PF_MSGTYPE_SHIFT;
	msg |= ADF_PFVF_COMPATIBILITY_VERSION << ADF_VF2PF_COMPAT_VER_REQ_SHIFT;
	BUILD_BUG_ON(ADF_PFVF_COMPATIBILITY_VERSION > 255);

	/* Send request from VF to PF */
	ret = adf_iov_puपंचांगsg(accel_dev, msg, 0);
	अगर (ret) अणु
		dev_err(&GET_DEV(accel_dev),
			"Failed to send Compatibility Version Request.\n");
		वापस ret;
	पूर्ण

	/* Wait क्रम response */
	अगर (!रुको_क्रम_completion_समयout(&accel_dev->vf.iov_msg_completion,
					 समयout)) अणु
		dev_err(&GET_DEV(accel_dev),
			"IOV request/response message timeout expired\n");
		वापस -EIO;
	पूर्ण

	/* Response from PF received, check compatibility */
	चयन (accel_dev->vf.compatible) अणु
	हाल ADF_PF2VF_VF_COMPATIBLE:
		अवरोध;
	हाल ADF_PF2VF_VF_COMPAT_UNKNOWN:
		/* VF is newer than PF and decides whether it is compatible */
		अगर (accel_dev->vf.pf_version >= hw_data->min_iov_compat_ver)
			अवरोध;
		fallthrough;
	हाल ADF_PF2VF_VF_INCOMPATIBLE:
		dev_err(&GET_DEV(accel_dev),
			"PF (vers %d) and VF (vers %d) are not compatible\n",
			accel_dev->vf.pf_version,
			ADF_PFVF_COMPATIBILITY_VERSION);
		वापस -EINVAL;
	शेष:
		dev_err(&GET_DEV(accel_dev),
			"Invalid response from PF; assume not compatible\n");
		वापस -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * adf_enable_vf2pf_comms() - Function enables communication from vf to pf
 *
 * @accel_dev: Poपूर्णांकer to acceleration device भव function.
 *
 * Return: 0 on success, error code otherwise.
 */
पूर्णांक adf_enable_vf2pf_comms(काष्ठा adf_accel_dev *accel_dev)
अणु
	adf_enable_pf2vf_पूर्णांकerrupts(accel_dev);
	वापस adf_vf2pf_request_version(accel_dev);
पूर्ण
EXPORT_SYMBOL_GPL(adf_enable_vf2pf_comms);
