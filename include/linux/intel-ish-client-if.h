<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Intel ISH client Interface definitions
 *
 * Copyright (c) 2019, Intel Corporation.
 */

#अगर_अघोषित _INTEL_ISH_CLIENT_IF_H_
#घोषणा _INTEL_ISH_CLIENT_IF_H_

काष्ठा ishtp_cl_device;
काष्ठा ishtp_device;
काष्ठा ishtp_cl;
काष्ठा ishtp_fw_client;

/* Client state */
क्रमागत cl_state अणु
	ISHTP_CL_INITIALIZING = 0,
	ISHTP_CL_CONNECTING,
	ISHTP_CL_CONNECTED,
	ISHTP_CL_DISCONNECTING,
	ISHTP_CL_DISCONNECTED
पूर्ण;

/**
 * काष्ठा ishtp_cl_device - ISHTP device handle
 * @driver:	driver instance on a bus
 * @name:	Name of the device क्रम probe
 * @probe:	driver callback क्रम device probe
 * @हटाओ:	driver callback on device removal
 *
 * Client drivers defines to get probed/हटाओd क्रम ISHTP client device.
 */
काष्ठा ishtp_cl_driver अणु
	काष्ठा device_driver driver;
	स्थिर अक्षर *name;
	स्थिर guid_t *guid;
	पूर्णांक (*probe)(काष्ठा ishtp_cl_device *dev);
	पूर्णांक (*हटाओ)(काष्ठा ishtp_cl_device *dev);
	पूर्णांक (*reset)(काष्ठा ishtp_cl_device *dev);
	स्थिर काष्ठा dev_pm_ops *pm;
पूर्ण;

/**
 * काष्ठा ishtp_msg_data - ISHTP message data काष्ठा
 * @size:	Size of data in the *data
 * @data:	Poपूर्णांकer to data
 */
काष्ठा ishtp_msg_data अणु
	uपूर्णांक32_t size;
	अचिन्हित अक्षर *data;
पूर्ण;

/*
 * काष्ठा ishtp_cl_rb - request block काष्ठाure
 * @list:	Link to list members
 * @cl:		ISHTP client instance
 * @buffer:	message header
 * @buf_idx:	Index पूर्णांकo buffer
 * @पढ़ो_समय:	 unused at this समय
 */
काष्ठा ishtp_cl_rb अणु
	काष्ठा list_head list;
	काष्ठा ishtp_cl *cl;
	काष्ठा ishtp_msg_data buffer;
	अचिन्हित दीर्घ buf_idx;
	अचिन्हित दीर्घ पढ़ो_समय;
पूर्ण;

पूर्णांक ishtp_cl_driver_रेजिस्टर(काष्ठा ishtp_cl_driver *driver,
			     काष्ठा module *owner);
व्योम ishtp_cl_driver_unरेजिस्टर(काष्ठा ishtp_cl_driver *driver);
पूर्णांक ishtp_रेजिस्टर_event_cb(काष्ठा ishtp_cl_device *device,
			    व्योम (*पढ़ो_cb)(काष्ठा ishtp_cl_device *));

/* Get the device * from ishtp device instance */
काष्ठा device *ishtp_device(काष्ठा ishtp_cl_device *cl_device);
/* Trace पूर्णांकerface क्रम clients */
व्योम *ishtp_trace_callback(काष्ठा ishtp_cl_device *cl_device);
/* Get device poपूर्णांकer of PCI device क्रम DMA acces */
काष्ठा device *ishtp_get_pci_device(काष्ठा ishtp_cl_device *cl_device);

काष्ठा ishtp_cl *ishtp_cl_allocate(काष्ठा ishtp_cl_device *cl_device);
व्योम ishtp_cl_मुक्त(काष्ठा ishtp_cl *cl);
पूर्णांक ishtp_cl_link(काष्ठा ishtp_cl *cl);
व्योम ishtp_cl_unlink(काष्ठा ishtp_cl *cl);
पूर्णांक ishtp_cl_disconnect(काष्ठा ishtp_cl *cl);
पूर्णांक ishtp_cl_connect(काष्ठा ishtp_cl *cl);
पूर्णांक ishtp_cl_send(काष्ठा ishtp_cl *cl, uपूर्णांक8_t *buf, माप_प्रकार length);
पूर्णांक ishtp_cl_flush_queues(काष्ठा ishtp_cl *cl);
पूर्णांक ishtp_cl_io_rb_recycle(काष्ठा ishtp_cl_rb *rb);
bool ishtp_cl_tx_empty(काष्ठा ishtp_cl *cl);
काष्ठा ishtp_cl_rb *ishtp_cl_rx_get_rb(काष्ठा ishtp_cl *cl);
व्योम *ishtp_get_client_data(काष्ठा ishtp_cl *cl);
व्योम ishtp_set_client_data(काष्ठा ishtp_cl *cl, व्योम *data);
काष्ठा ishtp_device *ishtp_get_ishtp_device(काष्ठा ishtp_cl *cl);
व्योम ishtp_set_tx_ring_size(काष्ठा ishtp_cl *cl, पूर्णांक size);
व्योम ishtp_set_rx_ring_size(काष्ठा ishtp_cl *cl, पूर्णांक size);
व्योम ishtp_set_connection_state(काष्ठा ishtp_cl *cl, पूर्णांक state);
व्योम ishtp_cl_set_fw_client_id(काष्ठा ishtp_cl *cl, पूर्णांक fw_client_id);

व्योम ishtp_put_device(काष्ठा ishtp_cl_device *cl_dev);
व्योम ishtp_get_device(काष्ठा ishtp_cl_device *cl_dev);
व्योम ishtp_set_drvdata(काष्ठा ishtp_cl_device *cl_device, व्योम *data);
व्योम *ishtp_get_drvdata(काष्ठा ishtp_cl_device *cl_device);
काष्ठा ishtp_cl_device *ishtp_dev_to_cl_device(काष्ठा device *dev);
पूर्णांक ishtp_रेजिस्टर_event_cb(काष्ठा ishtp_cl_device *device,
				व्योम (*पढ़ो_cb)(काष्ठा ishtp_cl_device *));
काष्ठा	ishtp_fw_client *ishtp_fw_cl_get_client(काष्ठा ishtp_device *dev,
						स्थिर guid_t *uuid);
पूर्णांक ishtp_get_fw_client_id(काष्ठा ishtp_fw_client *fw_client);
पूर्णांक ish_hw_reset(काष्ठा ishtp_device *dev);
#पूर्ण_अगर /* _INTEL_ISH_CLIENT_IF_H_ */
