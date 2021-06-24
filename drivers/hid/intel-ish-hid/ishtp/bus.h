<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ISHTP bus definitions
 *
 * Copyright (c) 2014-2016, Intel Corporation.
 */
#अगर_अघोषित _LINUX_ISHTP_CL_BUS_H
#घोषणा _LINUX_ISHTP_CL_BUS_H

#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/पूर्णांकel-ish-client-अगर.h>

काष्ठा ishtp_cl;
काष्ठा ishtp_cl_device;
काष्ठा ishtp_device;
काष्ठा ishtp_msg_hdr;

/**
 * काष्ठा ishtp_cl_device - ISHTP device handle
 * @dev:	device poपूर्णांकer
 * @ishtp_dev:	poपूर्णांकer to ishtp device काष्ठाure to primarily to access
 *		hw device operation callbacks and properties
 * @fw_client:	fw_client poपूर्णांकer to get fw inक्रमmation like protocol name
 *		max message length etc.
 * @device_link: Link to next client in the list on a bus
 * @event_work:	Used to schedule rx event क्रम client
 * @driver_data: Storage driver निजी data
 * @reference_count:	Used क्रम get/put device
 * @event_cb:	Callback to driver to send events
 *
 * An ishtp_cl_device poपूर्णांकer is वापसed from ishtp_add_device()
 * and links ISHTP bus clients to their actual host client poपूर्णांकer.
 * Drivers क्रम ISHTP devices will get an ishtp_cl_device poपूर्णांकer
 * when being probed and shall use it क्रम करोing bus I/O.
 */
काष्ठा ishtp_cl_device अणु
	काष्ठा device		dev;
	काष्ठा ishtp_device	*ishtp_dev;
	काष्ठा ishtp_fw_client	*fw_client;
	काष्ठा list_head	device_link;
	काष्ठा work_काष्ठा	event_work;
	व्योम			*driver_data;
	पूर्णांक			reference_count;
	व्योम (*event_cb)(काष्ठा ishtp_cl_device *device);
पूर्ण;

पूर्णांक	ishtp_bus_new_client(काष्ठा ishtp_device *dev);
व्योम	ishtp_हटाओ_all_clients(काष्ठा ishtp_device *dev);
पूर्णांक	ishtp_cl_device_bind(काष्ठा ishtp_cl *cl);
व्योम	ishtp_cl_bus_rx_event(काष्ठा ishtp_cl_device *device);

/* Write a multi-fragment message */
पूर्णांक	ishtp_send_msg(काष्ठा ishtp_device *dev,
		       काष्ठा ishtp_msg_hdr *hdr, व्योम *msg,
		       व्योम (*ipc_send_compl)(व्योम *),
		       व्योम *ipc_send_compl_prm);

/* Write a single-fragment message */
पूर्णांक	ishtp_ग_लिखो_message(काष्ठा ishtp_device *dev,
			    काष्ठा ishtp_msg_hdr *hdr,
			    व्योम *buf);

/* Use DMA to send/receive messages */
पूर्णांक ishtp_use_dma_transfer(व्योम);

/* Exported functions */
व्योम	ishtp_bus_हटाओ_all_clients(काष्ठा ishtp_device *ishtp_dev,
				     bool warm_reset);

व्योम	ishtp_recv(काष्ठा ishtp_device *dev);
व्योम	ishtp_reset_handler(काष्ठा ishtp_device *dev);
व्योम	ishtp_reset_compl_handler(काष्ठा ishtp_device *dev);

पूर्णांक	ishtp_fw_cl_by_uuid(काष्ठा ishtp_device *dev, स्थिर guid_t *cuuid);
#पूर्ण_अगर /* _LINUX_ISHTP_CL_BUS_H */
