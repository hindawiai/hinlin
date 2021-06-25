<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 Instituto Nokia de Tecnologia
 *
 * Authors:
 *    Lauro Ramos Venancio <lauro.venancio@खोलोbossa.org>
 *    Aloisio Almeida Jr <aloisio.almeida@खोलोbossa.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": %s: " fmt, __func__

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/nfc.h>

#समावेश <net/genetlink.h>

#समावेश "nfc.h"

#घोषणा VERSION "0.1"

#घोषणा NFC_CHECK_PRES_FREQ_MS	2000

पूर्णांक nfc_devlist_generation;
DEFINE_MUTEX(nfc_devlist_mutex);

/* NFC device ID biपंचांगap */
अटल DEFINE_IDA(nfc_index_ida);

पूर्णांक nfc_fw_करोwnload(काष्ठा nfc_dev *dev, स्थिर अक्षर *firmware_name)
अणु
	पूर्णांक rc = 0;

	pr_debug("%s do firmware %s\n", dev_name(&dev->dev), firmware_name);

	device_lock(&dev->dev);

	अगर (!device_is_रेजिस्टरed(&dev->dev)) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (dev->dev_up) अणु
		rc = -EBUSY;
		जाओ error;
	पूर्ण

	अगर (!dev->ops->fw_करोwnload) अणु
		rc = -EOPNOTSUPP;
		जाओ error;
	पूर्ण

	dev->fw_करोwnload_in_progress = true;
	rc = dev->ops->fw_करोwnload(dev, firmware_name);
	अगर (rc)
		dev->fw_करोwnload_in_progress = false;

error:
	device_unlock(&dev->dev);
	वापस rc;
पूर्ण

/**
 * nfc_fw_करोwnload_करोne - inक्रमm that a firmware करोwnload was completed
 *
 * @dev: The nfc device to which firmware was करोwnloaded
 * @firmware_name: The firmware filename
 * @result: The positive value of a standard त्रुटि_सं value
 */
पूर्णांक nfc_fw_करोwnload_करोne(काष्ठा nfc_dev *dev, स्थिर अक्षर *firmware_name,
			 u32 result)
अणु
	dev->fw_करोwnload_in_progress = false;

	वापस nfc_genl_fw_करोwnload_करोne(dev, firmware_name, result);
पूर्ण
EXPORT_SYMBOL(nfc_fw_करोwnload_करोne);

/**
 * nfc_dev_up - turn on the NFC device
 *
 * @dev: The nfc device to be turned on
 *
 * The device reमुख्यs up until the nfc_dev_करोwn function is called.
 */
पूर्णांक nfc_dev_up(काष्ठा nfc_dev *dev)
अणु
	पूर्णांक rc = 0;

	pr_debug("dev_name=%s\n", dev_name(&dev->dev));

	device_lock(&dev->dev);

	अगर (dev->rfसमाप्त && rfसमाप्त_blocked(dev->rfसमाप्त)) अणु
		rc = -ERFKILL;
		जाओ error;
	पूर्ण

	अगर (!device_is_रेजिस्टरed(&dev->dev)) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (dev->fw_करोwnload_in_progress) अणु
		rc = -EBUSY;
		जाओ error;
	पूर्ण

	अगर (dev->dev_up) अणु
		rc = -EALREADY;
		जाओ error;
	पूर्ण

	अगर (dev->ops->dev_up)
		rc = dev->ops->dev_up(dev);

	अगर (!rc)
		dev->dev_up = true;

	/* We have to enable the device beक्रमe discovering SEs */
	अगर (dev->ops->discover_se && dev->ops->discover_se(dev))
		pr_err("SE discovery failed\n");

error:
	device_unlock(&dev->dev);
	वापस rc;
पूर्ण

/**
 * nfc_dev_करोwn - turn off the NFC device
 *
 * @dev: The nfc device to be turned off
 */
पूर्णांक nfc_dev_करोwn(काष्ठा nfc_dev *dev)
अणु
	पूर्णांक rc = 0;

	pr_debug("dev_name=%s\n", dev_name(&dev->dev));

	device_lock(&dev->dev);

	अगर (!device_is_रेजिस्टरed(&dev->dev)) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (!dev->dev_up) अणु
		rc = -EALREADY;
		जाओ error;
	पूर्ण

	अगर (dev->polling || dev->active_target) अणु
		rc = -EBUSY;
		जाओ error;
	पूर्ण

	अगर (dev->ops->dev_करोwn)
		dev->ops->dev_करोwn(dev);

	dev->dev_up = false;

error:
	device_unlock(&dev->dev);
	वापस rc;
पूर्ण

अटल पूर्णांक nfc_rfसमाप्त_set_block(व्योम *data, bool blocked)
अणु
	काष्ठा nfc_dev *dev = data;

	pr_debug("%s blocked %d", dev_name(&dev->dev), blocked);

	अगर (!blocked)
		वापस 0;

	nfc_dev_करोwn(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops nfc_rfसमाप्त_ops = अणु
	.set_block = nfc_rfसमाप्त_set_block,
पूर्ण;

/**
 * nfc_start_poll - start polling क्रम nfc tarमाला_लो
 *
 * @dev: The nfc device that must start polling
 * @im_protocols: bitset of nfc initiator protocols to be used क्रम polling
 * @पंचांग_protocols: bitset of nfc transport protocols to be used क्रम polling
 *
 * The device reमुख्यs polling क्रम tarमाला_लो until a target is found or
 * the nfc_stop_poll function is called.
 */
पूर्णांक nfc_start_poll(काष्ठा nfc_dev *dev, u32 im_protocols, u32 पंचांग_protocols)
अणु
	पूर्णांक rc;

	pr_debug("dev_name %s initiator protocols 0x%x target protocols 0x%x\n",
		 dev_name(&dev->dev), im_protocols, पंचांग_protocols);

	अगर (!im_protocols && !पंचांग_protocols)
		वापस -EINVAL;

	device_lock(&dev->dev);

	अगर (!device_is_रेजिस्टरed(&dev->dev)) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (!dev->dev_up) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (dev->polling) अणु
		rc = -EBUSY;
		जाओ error;
	पूर्ण

	rc = dev->ops->start_poll(dev, im_protocols, पंचांग_protocols);
	अगर (!rc) अणु
		dev->polling = true;
		dev->rf_mode = NFC_RF_NONE;
	पूर्ण

error:
	device_unlock(&dev->dev);
	वापस rc;
पूर्ण

/**
 * nfc_stop_poll - stop polling क्रम nfc tarमाला_लो
 *
 * @dev: The nfc device that must stop polling
 */
पूर्णांक nfc_stop_poll(काष्ठा nfc_dev *dev)
अणु
	पूर्णांक rc = 0;

	pr_debug("dev_name=%s\n", dev_name(&dev->dev));

	device_lock(&dev->dev);

	अगर (!device_is_रेजिस्टरed(&dev->dev)) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (!dev->polling) अणु
		rc = -EINVAL;
		जाओ error;
	पूर्ण

	dev->ops->stop_poll(dev);
	dev->polling = false;
	dev->rf_mode = NFC_RF_NONE;

error:
	device_unlock(&dev->dev);
	वापस rc;
पूर्ण

अटल काष्ठा nfc_target *nfc_find_target(काष्ठा nfc_dev *dev, u32 target_idx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev->n_tarमाला_लो; i++) अणु
		अगर (dev->tarमाला_लो[i].idx == target_idx)
			वापस &dev->tarमाला_लो[i];
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक nfc_dep_link_up(काष्ठा nfc_dev *dev, पूर्णांक target_index, u8 comm_mode)
अणु
	पूर्णांक rc = 0;
	u8 *gb;
	माप_प्रकार gb_len;
	काष्ठा nfc_target *target;

	pr_debug("dev_name=%s comm %d\n", dev_name(&dev->dev), comm_mode);

	अगर (!dev->ops->dep_link_up)
		वापस -EOPNOTSUPP;

	device_lock(&dev->dev);

	अगर (!device_is_रेजिस्टरed(&dev->dev)) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (dev->dep_link_up == true) अणु
		rc = -EALREADY;
		जाओ error;
	पूर्ण

	gb = nfc_llcp_general_bytes(dev, &gb_len);
	अगर (gb_len > NFC_MAX_GT_LEN) अणु
		rc = -EINVAL;
		जाओ error;
	पूर्ण

	target = nfc_find_target(dev, target_index);
	अगर (target == शून्य) अणु
		rc = -ENOTCONN;
		जाओ error;
	पूर्ण

	rc = dev->ops->dep_link_up(dev, target, comm_mode, gb, gb_len);
	अगर (!rc) अणु
		dev->active_target = target;
		dev->rf_mode = NFC_RF_INITIATOR;
	पूर्ण

error:
	device_unlock(&dev->dev);
	वापस rc;
पूर्ण

पूर्णांक nfc_dep_link_करोwn(काष्ठा nfc_dev *dev)
अणु
	पूर्णांक rc = 0;

	pr_debug("dev_name=%s\n", dev_name(&dev->dev));

	अगर (!dev->ops->dep_link_करोwn)
		वापस -EOPNOTSUPP;

	device_lock(&dev->dev);

	अगर (!device_is_रेजिस्टरed(&dev->dev)) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (dev->dep_link_up == false) अणु
		rc = -EALREADY;
		जाओ error;
	पूर्ण

	rc = dev->ops->dep_link_करोwn(dev);
	अगर (!rc) अणु
		dev->dep_link_up = false;
		dev->active_target = शून्य;
		dev->rf_mode = NFC_RF_NONE;
		nfc_llcp_mac_is_करोwn(dev);
		nfc_genl_dep_link_करोwn_event(dev);
	पूर्ण

error:
	device_unlock(&dev->dev);

	वापस rc;
पूर्ण

पूर्णांक nfc_dep_link_is_up(काष्ठा nfc_dev *dev, u32 target_idx,
		       u8 comm_mode, u8 rf_mode)
अणु
	dev->dep_link_up = true;

	अगर (!dev->active_target && rf_mode == NFC_RF_INITIATOR) अणु
		काष्ठा nfc_target *target;

		target = nfc_find_target(dev, target_idx);
		अगर (target == शून्य)
			वापस -ENOTCONN;

		dev->active_target = target;
	पूर्ण

	dev->polling = false;
	dev->rf_mode = rf_mode;

	nfc_llcp_mac_is_up(dev, target_idx, comm_mode, rf_mode);

	वापस nfc_genl_dep_link_up_event(dev, target_idx, comm_mode, rf_mode);
पूर्ण
EXPORT_SYMBOL(nfc_dep_link_is_up);

/**
 * nfc_activate_target - prepare the target क्रम data exchange
 *
 * @dev: The nfc device that found the target
 * @target_idx: index of the target that must be activated
 * @protocol: nfc protocol that will be used क्रम data exchange
 */
पूर्णांक nfc_activate_target(काष्ठा nfc_dev *dev, u32 target_idx, u32 protocol)
अणु
	पूर्णांक rc;
	काष्ठा nfc_target *target;

	pr_debug("dev_name=%s target_idx=%u protocol=%u\n",
		 dev_name(&dev->dev), target_idx, protocol);

	device_lock(&dev->dev);

	अगर (!device_is_रेजिस्टरed(&dev->dev)) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (dev->active_target) अणु
		rc = -EBUSY;
		जाओ error;
	पूर्ण

	target = nfc_find_target(dev, target_idx);
	अगर (target == शून्य) अणु
		rc = -ENOTCONN;
		जाओ error;
	पूर्ण

	rc = dev->ops->activate_target(dev, target, protocol);
	अगर (!rc) अणु
		dev->active_target = target;
		dev->rf_mode = NFC_RF_INITIATOR;

		अगर (dev->ops->check_presence && !dev->shutting_करोwn)
			mod_समयr(&dev->check_pres_समयr, jअगरfies +
				  msecs_to_jअगरfies(NFC_CHECK_PRES_FREQ_MS));
	पूर्ण

error:
	device_unlock(&dev->dev);
	वापस rc;
पूर्ण

/**
 * nfc_deactivate_target - deactivate a nfc target
 *
 * @dev: The nfc device that found the target
 * @target_idx: index of the target that must be deactivated
 * @mode: idle or sleep?
 */
पूर्णांक nfc_deactivate_target(काष्ठा nfc_dev *dev, u32 target_idx, u8 mode)
अणु
	पूर्णांक rc = 0;

	pr_debug("dev_name=%s target_idx=%u\n",
		 dev_name(&dev->dev), target_idx);

	device_lock(&dev->dev);

	अगर (!device_is_रेजिस्टरed(&dev->dev)) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (dev->active_target == शून्य) अणु
		rc = -ENOTCONN;
		जाओ error;
	पूर्ण

	अगर (dev->active_target->idx != target_idx) अणु
		rc = -ENOTCONN;
		जाओ error;
	पूर्ण

	अगर (dev->ops->check_presence)
		del_समयr_sync(&dev->check_pres_समयr);

	dev->ops->deactivate_target(dev, dev->active_target, mode);
	dev->active_target = शून्य;

error:
	device_unlock(&dev->dev);
	वापस rc;
पूर्ण

/**
 * nfc_data_exchange - transceive data
 *
 * @dev: The nfc device that found the target
 * @target_idx: index of the target
 * @skb: data to be sent
 * @cb: callback called when the response is received
 * @cb_context: parameter क्रम the callback function
 *
 * The user must रुको क्रम the callback beक्रमe calling this function again.
 */
पूर्णांक nfc_data_exchange(काष्ठा nfc_dev *dev, u32 target_idx, काष्ठा sk_buff *skb,
		      data_exchange_cb_t cb, व्योम *cb_context)
अणु
	पूर्णांक rc;

	pr_debug("dev_name=%s target_idx=%u skb->len=%u\n",
		 dev_name(&dev->dev), target_idx, skb->len);

	device_lock(&dev->dev);

	अगर (!device_is_रेजिस्टरed(&dev->dev)) अणु
		rc = -ENODEV;
		kमुक्त_skb(skb);
		जाओ error;
	पूर्ण

	अगर (dev->rf_mode == NFC_RF_INITIATOR && dev->active_target != शून्य) अणु
		अगर (dev->active_target->idx != target_idx) अणु
			rc = -EADDRNOTAVAIL;
			kमुक्त_skb(skb);
			जाओ error;
		पूर्ण

		अगर (dev->ops->check_presence)
			del_समयr_sync(&dev->check_pres_समयr);

		rc = dev->ops->im_transceive(dev, dev->active_target, skb, cb,
					     cb_context);

		अगर (!rc && dev->ops->check_presence && !dev->shutting_करोwn)
			mod_समयr(&dev->check_pres_समयr, jअगरfies +
				  msecs_to_jअगरfies(NFC_CHECK_PRES_FREQ_MS));
	पूर्ण अन्यथा अगर (dev->rf_mode == NFC_RF_TARGET && dev->ops->पंचांग_send != शून्य) अणु
		rc = dev->ops->पंचांग_send(dev, skb);
	पूर्ण अन्यथा अणु
		rc = -ENOTCONN;
		kमुक्त_skb(skb);
		जाओ error;
	पूर्ण


error:
	device_unlock(&dev->dev);
	वापस rc;
पूर्ण

काष्ठा nfc_se *nfc_find_se(काष्ठा nfc_dev *dev, u32 se_idx)
अणु
	काष्ठा nfc_se *se;

	list_क्रम_each_entry(se, &dev->secure_elements, list)
		अगर (se->idx == se_idx)
			वापस se;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(nfc_find_se);

पूर्णांक nfc_enable_se(काष्ठा nfc_dev *dev, u32 se_idx)
अणु
	काष्ठा nfc_se *se;
	पूर्णांक rc;

	pr_debug("%s se index %d\n", dev_name(&dev->dev), se_idx);

	device_lock(&dev->dev);

	अगर (!device_is_रेजिस्टरed(&dev->dev)) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (!dev->dev_up) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (dev->polling) अणु
		rc = -EBUSY;
		जाओ error;
	पूर्ण

	अगर (!dev->ops->enable_se || !dev->ops->disable_se) अणु
		rc = -EOPNOTSUPP;
		जाओ error;
	पूर्ण

	se = nfc_find_se(dev, se_idx);
	अगर (!se) अणु
		rc = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (se->state == NFC_SE_ENABLED) अणु
		rc = -EALREADY;
		जाओ error;
	पूर्ण

	rc = dev->ops->enable_se(dev, se_idx);
	अगर (rc >= 0)
		se->state = NFC_SE_ENABLED;

error:
	device_unlock(&dev->dev);
	वापस rc;
पूर्ण

पूर्णांक nfc_disable_se(काष्ठा nfc_dev *dev, u32 se_idx)
अणु
	काष्ठा nfc_se *se;
	पूर्णांक rc;

	pr_debug("%s se index %d\n", dev_name(&dev->dev), se_idx);

	device_lock(&dev->dev);

	अगर (!device_is_रेजिस्टरed(&dev->dev)) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (!dev->dev_up) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (!dev->ops->enable_se || !dev->ops->disable_se) अणु
		rc = -EOPNOTSUPP;
		जाओ error;
	पूर्ण

	se = nfc_find_se(dev, se_idx);
	अगर (!se) अणु
		rc = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (se->state == NFC_SE_DISABLED) अणु
		rc = -EALREADY;
		जाओ error;
	पूर्ण

	rc = dev->ops->disable_se(dev, se_idx);
	अगर (rc >= 0)
		se->state = NFC_SE_DISABLED;

error:
	device_unlock(&dev->dev);
	वापस rc;
पूर्ण

पूर्णांक nfc_set_remote_general_bytes(काष्ठा nfc_dev *dev, u8 *gb, u8 gb_len)
अणु
	pr_debug("dev_name=%s gb_len=%d\n", dev_name(&dev->dev), gb_len);

	वापस nfc_llcp_set_remote_gb(dev, gb, gb_len);
पूर्ण
EXPORT_SYMBOL(nfc_set_remote_general_bytes);

u8 *nfc_get_local_general_bytes(काष्ठा nfc_dev *dev, माप_प्रकार *gb_len)
अणु
	pr_debug("dev_name=%s\n", dev_name(&dev->dev));

	वापस nfc_llcp_general_bytes(dev, gb_len);
पूर्ण
EXPORT_SYMBOL(nfc_get_local_general_bytes);

पूर्णांक nfc_पंचांग_data_received(काष्ठा nfc_dev *dev, काष्ठा sk_buff *skb)
अणु
	/* Only LLCP target mode क्रम now */
	अगर (dev->dep_link_up == false) अणु
		kमुक्त_skb(skb);
		वापस -ENOLINK;
	पूर्ण

	वापस nfc_llcp_data_received(dev, skb);
पूर्ण
EXPORT_SYMBOL(nfc_पंचांग_data_received);

पूर्णांक nfc_पंचांग_activated(काष्ठा nfc_dev *dev, u32 protocol, u8 comm_mode,
		     u8 *gb, माप_प्रकार gb_len)
अणु
	पूर्णांक rc;

	device_lock(&dev->dev);

	dev->polling = false;

	अगर (gb != शून्य) अणु
		rc = nfc_set_remote_general_bytes(dev, gb, gb_len);
		अगर (rc < 0)
			जाओ out;
	पूर्ण

	dev->rf_mode = NFC_RF_TARGET;

	अगर (protocol == NFC_PROTO_NFC_DEP_MASK)
		nfc_dep_link_is_up(dev, 0, comm_mode, NFC_RF_TARGET);

	rc = nfc_genl_पंचांग_activated(dev, protocol);

out:
	device_unlock(&dev->dev);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(nfc_पंचांग_activated);

पूर्णांक nfc_पंचांग_deactivated(काष्ठा nfc_dev *dev)
अणु
	dev->dep_link_up = false;
	dev->rf_mode = NFC_RF_NONE;

	वापस nfc_genl_पंचांग_deactivated(dev);
पूर्ण
EXPORT_SYMBOL(nfc_पंचांग_deactivated);

/**
 * nfc_alloc_send_skb - allocate a skb क्रम data exchange responses
 *
 * @dev: device sending the response
 * @sk: socket sending the response
 * @flags: MSG_DONTWAIT flag
 * @size: size to allocate
 * @err: poपूर्णांकer to memory to store the error code
 */
काष्ठा sk_buff *nfc_alloc_send_skb(काष्ठा nfc_dev *dev, काष्ठा sock *sk,
				   अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक size,
				   अचिन्हित पूर्णांक *err)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक total_size;

	total_size = size +
		dev->tx_headroom + dev->tx_tailroom + NFC_HEADER_SIZE;

	skb = sock_alloc_send_skb(sk, total_size, flags & MSG_DONTWAIT, err);
	अगर (skb)
		skb_reserve(skb, dev->tx_headroom + NFC_HEADER_SIZE);

	वापस skb;
पूर्ण

/**
 * nfc_alloc_recv_skb - allocate a skb क्रम data exchange responses
 *
 * @size: size to allocate
 * @gfp: gfp flags
 */
काष्ठा sk_buff *nfc_alloc_recv_skb(अचिन्हित पूर्णांक size, gfp_t gfp)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक total_size;

	total_size = size + 1;
	skb = alloc_skb(total_size, gfp);

	अगर (skb)
		skb_reserve(skb, 1);

	वापस skb;
पूर्ण
EXPORT_SYMBOL(nfc_alloc_recv_skb);

/**
 * nfc_tarमाला_लो_found - inक्रमm that tarमाला_लो were found
 *
 * @dev: The nfc device that found the tarमाला_लो
 * @tarमाला_लो: array of nfc tarमाला_लो found
 * @n_tarमाला_लो: tarमाला_लो array size
 *
 * The device driver must call this function when one or many nfc tarमाला_लो
 * are found. After calling this function, the device driver must stop
 * polling क्रम tarमाला_लो.
 * NOTE: This function can be called with tarमाला_लो=शून्य and n_tarमाला_लो=0 to
 * notअगरy a driver error, meaning that the polling operation cannot complete.
 * IMPORTANT: this function must not be called from an atomic context.
 * In addition, it must also not be called from a context that would prevent
 * the NFC Core to call other nfc ops entry poपूर्णांक concurrently.
 */
पूर्णांक nfc_tarमाला_लो_found(काष्ठा nfc_dev *dev,
		      काष्ठा nfc_target *tarमाला_लो, पूर्णांक n_tarमाला_लो)
अणु
	पूर्णांक i;

	pr_debug("dev_name=%s n_targets=%d\n", dev_name(&dev->dev), n_tarमाला_लो);

	क्रम (i = 0; i < n_tarमाला_लो; i++)
		tarमाला_लो[i].idx = dev->target_next_idx++;

	device_lock(&dev->dev);

	अगर (dev->polling == false) अणु
		device_unlock(&dev->dev);
		वापस 0;
	पूर्ण

	dev->polling = false;

	dev->tarमाला_लो_generation++;

	kमुक्त(dev->tarमाला_लो);
	dev->tarमाला_लो = शून्य;

	अगर (tarमाला_लो) अणु
		dev->tarमाला_लो = kmemdup(tarमाला_लो,
				       n_tarमाला_लो * माप(काष्ठा nfc_target),
				       GFP_ATOMIC);

		अगर (!dev->tarमाला_लो) अणु
			dev->n_tarमाला_लो = 0;
			device_unlock(&dev->dev);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	dev->n_tarमाला_लो = n_tarमाला_लो;
	device_unlock(&dev->dev);

	nfc_genl_tarमाला_लो_found(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nfc_tarमाला_लो_found);

/**
 * nfc_target_lost - inक्रमm that an activated target went out of field
 *
 * @dev: The nfc device that had the activated target in field
 * @target_idx: the nfc index of the target
 *
 * The device driver must call this function when the activated target
 * goes out of the field.
 * IMPORTANT: this function must not be called from an atomic context.
 * In addition, it must also not be called from a context that would prevent
 * the NFC Core to call other nfc ops entry poपूर्णांक concurrently.
 */
पूर्णांक nfc_target_lost(काष्ठा nfc_dev *dev, u32 target_idx)
अणु
	काष्ठा nfc_target *tg;
	पूर्णांक i;

	pr_debug("dev_name %s n_target %d\n", dev_name(&dev->dev), target_idx);

	device_lock(&dev->dev);

	क्रम (i = 0; i < dev->n_tarमाला_लो; i++) अणु
		tg = &dev->tarमाला_लो[i];
		अगर (tg->idx == target_idx)
			अवरोध;
	पूर्ण

	अगर (i == dev->n_tarमाला_लो) अणु
		device_unlock(&dev->dev);
		वापस -EINVAL;
	पूर्ण

	dev->tarमाला_लो_generation++;
	dev->n_tarमाला_लो--;
	dev->active_target = शून्य;

	अगर (dev->n_tarमाला_लो) अणु
		स_नकल(&dev->tarमाला_लो[i], &dev->tarमाला_लो[i + 1],
		       (dev->n_tarमाला_लो - i) * माप(काष्ठा nfc_target));
	पूर्ण अन्यथा अणु
		kमुक्त(dev->tarमाला_लो);
		dev->tarमाला_लो = शून्य;
	पूर्ण

	device_unlock(&dev->dev);

	nfc_genl_target_lost(dev, target_idx);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nfc_target_lost);

अंतरभूत व्योम nfc_driver_failure(काष्ठा nfc_dev *dev, पूर्णांक err)
अणु
	nfc_tarमाला_लो_found(dev, शून्य, 0);
पूर्ण
EXPORT_SYMBOL(nfc_driver_failure);

पूर्णांक nfc_add_se(काष्ठा nfc_dev *dev, u32 se_idx, u16 type)
अणु
	काष्ठा nfc_se *se;
	पूर्णांक rc;

	pr_debug("%s se index %d\n", dev_name(&dev->dev), se_idx);

	se = nfc_find_se(dev, se_idx);
	अगर (se)
		वापस -EALREADY;

	se = kzalloc(माप(काष्ठा nfc_se), GFP_KERNEL);
	अगर (!se)
		वापस -ENOMEM;

	se->idx = se_idx;
	se->type = type;
	se->state = NFC_SE_DISABLED;
	INIT_LIST_HEAD(&se->list);

	list_add(&se->list, &dev->secure_elements);

	rc = nfc_genl_se_added(dev, se_idx, type);
	अगर (rc < 0) अणु
		list_del(&se->list);
		kमुक्त(se);

		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nfc_add_se);

पूर्णांक nfc_हटाओ_se(काष्ठा nfc_dev *dev, u32 se_idx)
अणु
	काष्ठा nfc_se *se, *n;
	पूर्णांक rc;

	pr_debug("%s se index %d\n", dev_name(&dev->dev), se_idx);

	list_क्रम_each_entry_safe(se, n, &dev->secure_elements, list)
		अगर (se->idx == se_idx) अणु
			rc = nfc_genl_se_हटाओd(dev, se_idx);
			अगर (rc < 0)
				वापस rc;

			list_del(&se->list);
			kमुक्त(se);

			वापस 0;
		पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(nfc_हटाओ_se);

पूर्णांक nfc_se_transaction(काष्ठा nfc_dev *dev, u8 se_idx,
		       काष्ठा nfc_evt_transaction *evt_transaction)
अणु
	पूर्णांक rc;

	pr_debug("transaction: %x\n", se_idx);

	device_lock(&dev->dev);

	अगर (!evt_transaction) अणु
		rc = -EPROTO;
		जाओ out;
	पूर्ण

	rc = nfc_genl_se_transaction(dev, se_idx, evt_transaction);
out:
	device_unlock(&dev->dev);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(nfc_se_transaction);

पूर्णांक nfc_se_connectivity(काष्ठा nfc_dev *dev, u8 se_idx)
अणु
	पूर्णांक rc;

	pr_debug("connectivity: %x\n", se_idx);

	device_lock(&dev->dev);
	rc = nfc_genl_se_connectivity(dev, se_idx);
	device_unlock(&dev->dev);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(nfc_se_connectivity);

अटल व्योम nfc_release(काष्ठा device *d)
अणु
	काष्ठा nfc_dev *dev = to_nfc_dev(d);
	काष्ठा nfc_se *se, *n;

	pr_debug("dev_name=%s\n", dev_name(&dev->dev));

	nfc_genl_data_निकास(&dev->genl_data);
	kमुक्त(dev->tarमाला_लो);

	list_क्रम_each_entry_safe(se, n, &dev->secure_elements, list) अणु
			nfc_genl_se_हटाओd(dev, se->idx);
			list_del(&se->list);
			kमुक्त(se);
	पूर्ण

	ida_simple_हटाओ(&nfc_index_ida, dev->idx);

	kमुक्त(dev);
पूर्ण

अटल व्योम nfc_check_pres_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nfc_dev *dev = container_of(work, काष्ठा nfc_dev,
					   check_pres_work);
	पूर्णांक rc;

	device_lock(&dev->dev);

	अगर (dev->active_target && समयr_pending(&dev->check_pres_समयr) == 0) अणु
		rc = dev->ops->check_presence(dev, dev->active_target);
		अगर (rc == -EOPNOTSUPP)
			जाओ निकास;
		अगर (rc) अणु
			u32 active_target_idx = dev->active_target->idx;
			device_unlock(&dev->dev);
			nfc_target_lost(dev, active_target_idx);
			वापस;
		पूर्ण

		अगर (!dev->shutting_करोwn)
			mod_समयr(&dev->check_pres_समयr, jअगरfies +
				  msecs_to_jअगरfies(NFC_CHECK_PRES_FREQ_MS));
	पूर्ण

निकास:
	device_unlock(&dev->dev);
पूर्ण

अटल व्योम nfc_check_pres_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा nfc_dev *dev = from_समयr(dev, t, check_pres_समयr);

	schedule_work(&dev->check_pres_work);
पूर्ण

काष्ठा class nfc_class = अणु
	.name = "nfc",
	.dev_release = nfc_release,
पूर्ण;
EXPORT_SYMBOL(nfc_class);

अटल पूर्णांक match_idx(काष्ठा device *d, स्थिर व्योम *data)
अणु
	काष्ठा nfc_dev *dev = to_nfc_dev(d);
	स्थिर अचिन्हित पूर्णांक *idx = data;

	वापस dev->idx == *idx;
पूर्ण

काष्ठा nfc_dev *nfc_get_device(अचिन्हित पूर्णांक idx)
अणु
	काष्ठा device *d;

	d = class_find_device(&nfc_class, शून्य, &idx, match_idx);
	अगर (!d)
		वापस शून्य;

	वापस to_nfc_dev(d);
पूर्ण

/**
 * nfc_allocate_device - allocate a new nfc device
 *
 * @ops: device operations
 * @supported_protocols: NFC protocols supported by the device
 * @tx_headroom: reserved space at beginning of skb
 * @tx_tailroom: reserved space at end of skb
 */
काष्ठा nfc_dev *nfc_allocate_device(काष्ठा nfc_ops *ops,
				    u32 supported_protocols,
				    पूर्णांक tx_headroom, पूर्णांक tx_tailroom)
अणु
	काष्ठा nfc_dev *dev;
	पूर्णांक rc;

	अगर (!ops->start_poll || !ops->stop_poll || !ops->activate_target ||
	    !ops->deactivate_target || !ops->im_transceive)
		वापस शून्य;

	अगर (!supported_protocols)
		वापस शून्य;

	dev = kzalloc(माप(काष्ठा nfc_dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	rc = ida_simple_get(&nfc_index_ida, 0, 0, GFP_KERNEL);
	अगर (rc < 0)
		जाओ err_मुक्त_dev;
	dev->idx = rc;

	dev->dev.class = &nfc_class;
	dev_set_name(&dev->dev, "nfc%d", dev->idx);
	device_initialize(&dev->dev);

	dev->ops = ops;
	dev->supported_protocols = supported_protocols;
	dev->tx_headroom = tx_headroom;
	dev->tx_tailroom = tx_tailroom;
	INIT_LIST_HEAD(&dev->secure_elements);

	nfc_genl_data_init(&dev->genl_data);

	dev->rf_mode = NFC_RF_NONE;

	/* first generation must not be 0 */
	dev->tarमाला_लो_generation = 1;

	अगर (ops->check_presence) अणु
		समयr_setup(&dev->check_pres_समयr, nfc_check_pres_समयout, 0);
		INIT_WORK(&dev->check_pres_work, nfc_check_pres_work);
	पूर्ण

	वापस dev;

err_मुक्त_dev:
	kमुक्त(dev);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(nfc_allocate_device);

/**
 * nfc_रेजिस्टर_device - रेजिस्टर a nfc device in the nfc subप्रणाली
 *
 * @dev: The nfc device to रेजिस्टर
 */
पूर्णांक nfc_रेजिस्टर_device(काष्ठा nfc_dev *dev)
अणु
	पूर्णांक rc;

	pr_debug("dev_name=%s\n", dev_name(&dev->dev));

	mutex_lock(&nfc_devlist_mutex);
	nfc_devlist_generation++;
	rc = device_add(&dev->dev);
	mutex_unlock(&nfc_devlist_mutex);

	अगर (rc < 0)
		वापस rc;

	rc = nfc_llcp_रेजिस्टर_device(dev);
	अगर (rc)
		pr_err("Could not register llcp device\n");

	rc = nfc_genl_device_added(dev);
	अगर (rc)
		pr_debug("The userspace won't be notified that the device %s was added\n",
			 dev_name(&dev->dev));

	dev->rfसमाप्त = rfसमाप्त_alloc(dev_name(&dev->dev), &dev->dev,
				   RFKILL_TYPE_NFC, &nfc_rfसमाप्त_ops, dev);
	अगर (dev->rfसमाप्त) अणु
		अगर (rfसमाप्त_रेजिस्टर(dev->rfसमाप्त) < 0) अणु
			rfसमाप्त_destroy(dev->rfसमाप्त);
			dev->rfसमाप्त = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nfc_रेजिस्टर_device);

/**
 * nfc_unरेजिस्टर_device - unरेजिस्टर a nfc device in the nfc subप्रणाली
 *
 * @dev: The nfc device to unरेजिस्टर
 */
व्योम nfc_unरेजिस्टर_device(काष्ठा nfc_dev *dev)
अणु
	पूर्णांक rc;

	pr_debug("dev_name=%s\n", dev_name(&dev->dev));

	अगर (dev->rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(dev->rfसमाप्त);
		rfसमाप्त_destroy(dev->rfसमाप्त);
	पूर्ण

	अगर (dev->ops->check_presence) अणु
		device_lock(&dev->dev);
		dev->shutting_करोwn = true;
		device_unlock(&dev->dev);
		del_समयr_sync(&dev->check_pres_समयr);
		cancel_work_sync(&dev->check_pres_work);
	पूर्ण

	rc = nfc_genl_device_हटाओd(dev);
	अगर (rc)
		pr_debug("The userspace won't be notified that the device %s "
			 "was removed\n", dev_name(&dev->dev));

	nfc_llcp_unरेजिस्टर_device(dev);

	mutex_lock(&nfc_devlist_mutex);
	nfc_devlist_generation++;
	device_del(&dev->dev);
	mutex_unlock(&nfc_devlist_mutex);
पूर्ण
EXPORT_SYMBOL(nfc_unरेजिस्टर_device);

अटल पूर्णांक __init nfc_init(व्योम)
अणु
	पूर्णांक rc;

	pr_info("NFC Core ver %s\n", VERSION);

	rc = class_रेजिस्टर(&nfc_class);
	अगर (rc)
		वापस rc;

	rc = nfc_genl_init();
	अगर (rc)
		जाओ err_genl;

	/* the first generation must not be 0 */
	nfc_devlist_generation = 1;

	rc = rawsock_init();
	अगर (rc)
		जाओ err_rawsock;

	rc = nfc_llcp_init();
	अगर (rc)
		जाओ err_llcp_sock;

	rc = af_nfc_init();
	अगर (rc)
		जाओ err_af_nfc;

	वापस 0;

err_af_nfc:
	nfc_llcp_निकास();
err_llcp_sock:
	rawsock_निकास();
err_rawsock:
	nfc_genl_निकास();
err_genl:
	class_unरेजिस्टर(&nfc_class);
	वापस rc;
पूर्ण

अटल व्योम __निकास nfc_निकास(व्योम)
अणु
	af_nfc_निकास();
	nfc_llcp_निकास();
	rawsock_निकास();
	nfc_genl_निकास();
	class_unरेजिस्टर(&nfc_class);
पूर्ण

subsys_initcall(nfc_init);
module_निकास(nfc_निकास);

MODULE_AUTHOR("Lauro Ramos Venancio <lauro.venancio@openbossa.org>");
MODULE_DESCRIPTION("NFC Core ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_NFC);
MODULE_ALIAS_GENL_FAMILY(NFC_GENL_NAME);
