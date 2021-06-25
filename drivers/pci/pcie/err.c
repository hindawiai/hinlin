<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file implements the error recovery as a core part of PCIe error
 * reporting. When a PCIe error is delivered, an error message will be
 * collected and prपूर्णांकed to console, then, an error recovery procedure
 * will be executed by following the PCI error recovery rules.
 *
 * Copyright (C) 2006 Intel Corp.
 *	Tom Long Nguyen (tom.l.nguyen@पूर्णांकel.com)
 *	Zhang Yanmin (yanmin.zhang@पूर्णांकel.com)
 */

#घोषणा dev_fmt(fmt) "AER: " fmt

#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/aer.h>
#समावेश "portdrv.h"
#समावेश "../pci.h"

अटल pci_ers_result_t merge_result(क्रमागत pci_ers_result orig,
				  क्रमागत pci_ers_result new)
अणु
	अगर (new == PCI_ERS_RESULT_NO_AER_DRIVER)
		वापस PCI_ERS_RESULT_NO_AER_DRIVER;

	अगर (new == PCI_ERS_RESULT_NONE)
		वापस orig;

	चयन (orig) अणु
	हाल PCI_ERS_RESULT_CAN_RECOVER:
	हाल PCI_ERS_RESULT_RECOVERED:
		orig = new;
		अवरोध;
	हाल PCI_ERS_RESULT_DISCONNECT:
		अगर (new == PCI_ERS_RESULT_NEED_RESET)
			orig = PCI_ERS_RESULT_NEED_RESET;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस orig;
पूर्ण

अटल पूर्णांक report_error_detected(काष्ठा pci_dev *dev,
				 pci_channel_state_t state,
				 क्रमागत pci_ers_result *result)
अणु
	pci_ers_result_t vote;
	स्थिर काष्ठा pci_error_handlers *err_handler;

	device_lock(&dev->dev);
	अगर (!pci_dev_set_io_state(dev, state) ||
		!dev->driver ||
		!dev->driver->err_handler ||
		!dev->driver->err_handler->error_detected) अणु
		/*
		 * If any device in the subtree करोes not have an error_detected
		 * callback, PCI_ERS_RESULT_NO_AER_DRIVER prevents subsequent
		 * error callbacks of "any" device in the subtree, and will
		 * निकास in the disconnected error state.
		 */
		अगर (dev->hdr_type != PCI_HEADER_TYPE_BRIDGE) अणु
			vote = PCI_ERS_RESULT_NO_AER_DRIVER;
			pci_info(dev, "can't recover (no error_detected callback)\n");
		पूर्ण अन्यथा अणु
			vote = PCI_ERS_RESULT_NONE;
		पूर्ण
	पूर्ण अन्यथा अणु
		err_handler = dev->driver->err_handler;
		vote = err_handler->error_detected(dev, state);
	पूर्ण
	pci_uevent_ers(dev, vote);
	*result = merge_result(*result, vote);
	device_unlock(&dev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक report_frozen_detected(काष्ठा pci_dev *dev, व्योम *data)
अणु
	वापस report_error_detected(dev, pci_channel_io_frozen, data);
पूर्ण

अटल पूर्णांक report_normal_detected(काष्ठा pci_dev *dev, व्योम *data)
अणु
	वापस report_error_detected(dev, pci_channel_io_normal, data);
पूर्ण

अटल पूर्णांक report_mmio_enabled(काष्ठा pci_dev *dev, व्योम *data)
अणु
	pci_ers_result_t vote, *result = data;
	स्थिर काष्ठा pci_error_handlers *err_handler;

	device_lock(&dev->dev);
	अगर (!dev->driver ||
		!dev->driver->err_handler ||
		!dev->driver->err_handler->mmio_enabled)
		जाओ out;

	err_handler = dev->driver->err_handler;
	vote = err_handler->mmio_enabled(dev);
	*result = merge_result(*result, vote);
out:
	device_unlock(&dev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक report_slot_reset(काष्ठा pci_dev *dev, व्योम *data)
अणु
	pci_ers_result_t vote, *result = data;
	स्थिर काष्ठा pci_error_handlers *err_handler;

	device_lock(&dev->dev);
	अगर (!dev->driver ||
		!dev->driver->err_handler ||
		!dev->driver->err_handler->slot_reset)
		जाओ out;

	err_handler = dev->driver->err_handler;
	vote = err_handler->slot_reset(dev);
	*result = merge_result(*result, vote);
out:
	device_unlock(&dev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक report_resume(काष्ठा pci_dev *dev, व्योम *data)
अणु
	स्थिर काष्ठा pci_error_handlers *err_handler;

	device_lock(&dev->dev);
	अगर (!pci_dev_set_io_state(dev, pci_channel_io_normal) ||
		!dev->driver ||
		!dev->driver->err_handler ||
		!dev->driver->err_handler->resume)
		जाओ out;

	err_handler = dev->driver->err_handler;
	err_handler->resume(dev);
out:
	pci_uevent_ers(dev, PCI_ERS_RESULT_RECOVERED);
	device_unlock(&dev->dev);
	वापस 0;
पूर्ण

/**
 * pci_walk_bridge - walk bridges potentially AER affected
 * @bridge:	bridge which may be a Port, an RCEC, or an RCiEP
 * @cb:		callback to be called क्रम each device found
 * @userdata:	arbitrary poपूर्णांकer to be passed to callback
 *
 * If the device provided is a bridge, walk the subordinate bus, including
 * any bridged devices on buses under this bus.  Call the provided callback
 * on each device found.
 *
 * If the device provided has no subordinate bus, e.g., an RCEC or RCiEP,
 * call the callback on the device itself.
 */
अटल व्योम pci_walk_bridge(काष्ठा pci_dev *bridge,
			    पूर्णांक (*cb)(काष्ठा pci_dev *, व्योम *),
			    व्योम *userdata)
अणु
	अगर (bridge->subordinate)
		pci_walk_bus(bridge->subordinate, cb, userdata);
	अन्यथा
		cb(bridge, userdata);
पूर्ण

pci_ers_result_t pcie_करो_recovery(काष्ठा pci_dev *dev,
		pci_channel_state_t state,
		pci_ers_result_t (*reset_subordinates)(काष्ठा pci_dev *pdev))
अणु
	पूर्णांक type = pci_pcie_type(dev);
	काष्ठा pci_dev *bridge;
	pci_ers_result_t status = PCI_ERS_RESULT_CAN_RECOVER;
	काष्ठा pci_host_bridge *host = pci_find_host_bridge(dev->bus);

	/*
	 * If the error was detected by a Root Port, Downstream Port, RCEC,
	 * or RCiEP, recovery runs on the device itself.  For Ports, that
	 * also includes any subordinate devices.
	 *
	 * If it was detected by another device (Endpoपूर्णांक, etc), recovery
	 * runs on the device and anything अन्यथा under the same Port, i.e.,
	 * everything under "bridge".
	 */
	अगर (type == PCI_EXP_TYPE_ROOT_PORT ||
	    type == PCI_EXP_TYPE_DOWNSTREAM ||
	    type == PCI_EXP_TYPE_RC_EC ||
	    type == PCI_EXP_TYPE_RC_END)
		bridge = dev;
	अन्यथा
		bridge = pci_upstream_bridge(dev);

	pci_dbg(bridge, "broadcast error_detected message\n");
	अगर (state == pci_channel_io_frozen) अणु
		pci_walk_bridge(bridge, report_frozen_detected, &status);
		अगर (reset_subordinates(bridge) != PCI_ERS_RESULT_RECOVERED) अणु
			pci_warn(bridge, "subordinate device reset failed\n");
			जाओ failed;
		पूर्ण
	पूर्ण अन्यथा अणु
		pci_walk_bridge(bridge, report_normal_detected, &status);
	पूर्ण

	अगर (status == PCI_ERS_RESULT_CAN_RECOVER) अणु
		status = PCI_ERS_RESULT_RECOVERED;
		pci_dbg(bridge, "broadcast mmio_enabled message\n");
		pci_walk_bridge(bridge, report_mmio_enabled, &status);
	पूर्ण

	अगर (status == PCI_ERS_RESULT_NEED_RESET) अणु
		/*
		 * TODO: Should call platक्रमm-specअगरic
		 * functions to reset slot beक्रमe calling
		 * drivers' slot_reset callbacks?
		 */
		status = PCI_ERS_RESULT_RECOVERED;
		pci_dbg(bridge, "broadcast slot_reset message\n");
		pci_walk_bridge(bridge, report_slot_reset, &status);
	पूर्ण

	अगर (status != PCI_ERS_RESULT_RECOVERED)
		जाओ failed;

	pci_dbg(bridge, "broadcast resume message\n");
	pci_walk_bridge(bridge, report_resume, &status);

	/*
	 * If we have native control of AER, clear error status in the device
	 * that detected the error.  If the platक्रमm retained control of AER,
	 * it is responsible क्रम clearing this status.  In that हाल, the
	 * संकेतing device may not even be visible to the OS.
	 */
	अगर (host->native_aer || pcie_ports_native) अणु
		pcie_clear_device_status(dev);
		pci_aer_clear_nonfatal_status(dev);
	पूर्ण
	pci_info(bridge, "device recovery successful\n");
	वापस status;

failed:
	pci_uevent_ers(bridge, PCI_ERS_RESULT_DISCONNECT);

	/* TODO: Should kernel panic here? */
	pci_info(bridge, "device recovery failed\n");

	वापस status;
पूर्ण
