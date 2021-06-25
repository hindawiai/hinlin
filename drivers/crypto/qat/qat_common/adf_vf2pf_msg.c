<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2015 - 2020 Intel Corporation */
#समावेश "adf_accel_devices.h"
#समावेश "adf_common_drv.h"
#समावेश "adf_pf2vf_msg.h"

/**
 * adf_vf2pf_init() - send init msg to PF
 * @accel_dev:  Poपूर्णांकer to acceleration VF device.
 *
 * Function sends an init message from the VF to a PF
 *
 * Return: 0 on success, error code otherwise.
 */
पूर्णांक adf_vf2pf_init(काष्ठा adf_accel_dev *accel_dev)
अणु
	u32 msg = (ADF_VF2PF_MSGORIGIN_SYSTEM |
		(ADF_VF2PF_MSGTYPE_INIT << ADF_VF2PF_MSGTYPE_SHIFT));

	अगर (adf_iov_puपंचांगsg(accel_dev, msg, 0)) अणु
		dev_err(&GET_DEV(accel_dev),
			"Failed to send Init event to PF\n");
		वापस -EFAULT;
	पूर्ण
	set_bit(ADF_STATUS_PF_RUNNING, &accel_dev->status);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adf_vf2pf_init);

/**
 * adf_vf2pf_shutकरोwn() - send shutकरोwn msg to PF
 * @accel_dev:  Poपूर्णांकer to acceleration VF device.
 *
 * Function sends a shutकरोwn message from the VF to a PF
 *
 * Return: व्योम
 */
व्योम adf_vf2pf_shutकरोwn(काष्ठा adf_accel_dev *accel_dev)
अणु
	u32 msg = (ADF_VF2PF_MSGORIGIN_SYSTEM |
	    (ADF_VF2PF_MSGTYPE_SHUTDOWN << ADF_VF2PF_MSGTYPE_SHIFT));

	अगर (test_bit(ADF_STATUS_PF_RUNNING, &accel_dev->status))
		अगर (adf_iov_puपंचांगsg(accel_dev, msg, 0))
			dev_err(&GET_DEV(accel_dev),
				"Failed to send Shutdown event to PF\n");
पूर्ण
EXPORT_SYMBOL_GPL(adf_vf2pf_shutकरोwn);
