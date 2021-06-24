<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * HSI core header file.
 *
 * Copyright (C) 2010 Nokia Corporation. All rights reserved.
 *
 * Contact: Carlos Chinea <carlos.chinea@nokia.com>
 */

#अगर_अघोषित __LINUX_HSI_H__
#घोषणा __LINUX_HSI_H__

#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>

/* HSI message ttype */
#घोषणा HSI_MSG_READ	0
#घोषणा HSI_MSG_WRITE	1

/* HSI configuration values */
क्रमागत अणु
	HSI_MODE_STREAM	= 1,
	HSI_MODE_FRAME,
पूर्ण;

क्रमागत अणु
	HSI_FLOW_SYNC,	/* Synchronized flow */
	HSI_FLOW_PIPE,	/* Pipelined flow */
पूर्ण;

क्रमागत अणु
	HSI_ARB_RR,	/* Round-robin arbitration */
	HSI_ARB_PRIO,	/* Channel priority arbitration */
पूर्ण;

#घोषणा HSI_MAX_CHANNELS	16

/* HSI message status codes */
क्रमागत अणु
	HSI_STATUS_COMPLETED,	/* Message transfer is completed */
	HSI_STATUS_PENDING,	/* Message pending to be पढ़ो/ग_लिखो (POLL) */
	HSI_STATUS_PROCEEDING,	/* Message transfer is ongoing */
	HSI_STATUS_QUEUED,	/* Message रुकोing to be served */
	HSI_STATUS_ERROR,	/* Error when message transfer was ongoing */
पूर्ण;

/* HSI port event codes */
क्रमागत अणु
	HSI_EVENT_START_RX,
	HSI_EVENT_STOP_RX,
पूर्ण;

/**
 * काष्ठा hsi_channel - channel resource used by the hsi clients
 * @id: Channel number
 * @name: Channel name
 */
काष्ठा hsi_channel अणु
	अचिन्हित पूर्णांक	id;
	स्थिर अक्षर	*name;
पूर्ण;

/**
 * काष्ठा hsi_config - Configuration क्रम RX/TX HSI modules
 * @mode: Bit transmission mode (STREAM or FRAME)
 * @channels: Channel resources used by the client
 * @num_channels: Number of channel resources
 * @num_hw_channels: Number of channels the transceiver is configured क्रम [1..16]
 * @speed: Max bit transmission speed (Kbit/s)
 * @flow: RX flow type (SYNCHRONIZED or PIPELINE)
 * @arb_mode: Arbitration mode क्रम TX frame (Round robin, priority)
 */
काष्ठा hsi_config अणु
	अचिन्हित पूर्णांक		mode;
	काष्ठा hsi_channel	*channels;
	अचिन्हित पूर्णांक		num_channels;
	अचिन्हित पूर्णांक		num_hw_channels;
	अचिन्हित पूर्णांक		speed;
	जोड़ अणु
		अचिन्हित पूर्णांक	flow;		/* RX only */
		अचिन्हित पूर्णांक	arb_mode;	/* TX only */
	पूर्ण;
पूर्ण;

/**
 * काष्ठा hsi_board_info - HSI client board info
 * @name: Name क्रम the HSI device
 * @hsi_id: HSI controller id where the client sits
 * @port: Port number in the controller where the client sits
 * @tx_cfg: HSI TX configuration
 * @rx_cfg: HSI RX configuration
 * @platक्रमm_data: Platक्रमm related data
 * @archdata: Architecture-dependent device data
 */
काष्ठा hsi_board_info अणु
	स्थिर अक्षर		*name;
	अचिन्हित पूर्णांक		hsi_id;
	अचिन्हित पूर्णांक		port;
	काष्ठा hsi_config	tx_cfg;
	काष्ठा hsi_config	rx_cfg;
	व्योम			*platक्रमm_data;
	काष्ठा dev_archdata	*archdata;
पूर्ण;

#अगर_घोषित CONFIG_HSI_BOARDINFO
बाह्य पूर्णांक hsi_रेजिस्टर_board_info(काष्ठा hsi_board_info स्थिर *info,
							अचिन्हित पूर्णांक len);
#अन्यथा
अटल अंतरभूत पूर्णांक hsi_रेजिस्टर_board_info(काष्ठा hsi_board_info स्थिर *info,
							अचिन्हित पूर्णांक len)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_HSI_BOARDINFO */

/**
 * काष्ठा hsi_client - HSI client attached to an HSI port
 * @device: Driver model representation of the device
 * @tx_cfg: HSI TX configuration
 * @rx_cfg: HSI RX configuration
 */
काष्ठा hsi_client अणु
	काष्ठा device		device;
	काष्ठा hsi_config	tx_cfg;
	काष्ठा hsi_config	rx_cfg;
	/* निजी: */
	व्योम			(*ehandler)(काष्ठा hsi_client *, अचिन्हित दीर्घ);
	अचिन्हित पूर्णांक		pclaimed:1;
	काष्ठा notअगरier_block	nb;
पूर्ण;

#घोषणा to_hsi_client(dev) container_of(dev, काष्ठा hsi_client, device)

अटल अंतरभूत व्योम hsi_client_set_drvdata(काष्ठा hsi_client *cl, व्योम *data)
अणु
	dev_set_drvdata(&cl->device, data);
पूर्ण

अटल अंतरभूत व्योम *hsi_client_drvdata(काष्ठा hsi_client *cl)
अणु
	वापस dev_get_drvdata(&cl->device);
पूर्ण

पूर्णांक hsi_रेजिस्टर_port_event(काष्ठा hsi_client *cl,
			व्योम (*handler)(काष्ठा hsi_client *, अचिन्हित दीर्घ));
पूर्णांक hsi_unरेजिस्टर_port_event(काष्ठा hsi_client *cl);

/**
 * काष्ठा hsi_client_driver - Driver associated to an HSI client
 * @driver: Driver model representation of the driver
 */
काष्ठा hsi_client_driver अणु
	काष्ठा device_driver	driver;
पूर्ण;

#घोषणा to_hsi_client_driver(drv) container_of(drv, काष्ठा hsi_client_driver,\
									driver)

पूर्णांक hsi_रेजिस्टर_client_driver(काष्ठा hsi_client_driver *drv);

अटल अंतरभूत व्योम hsi_unरेजिस्टर_client_driver(काष्ठा hsi_client_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण

/**
 * काष्ठा hsi_msg - HSI message descriptor
 * @link: Free to use by the current descriptor owner
 * @cl: HSI device client that issues the transfer
 * @sgt: Head of the scatterlist array
 * @context: Client context data associated to the transfer
 * @complete: Transfer completion callback
 * @deकाष्ठाor: Deकाष्ठाor to मुक्त resources when flushing
 * @status: Status of the transfer when completed
 * @actual_len: Actual length of data transferred on completion
 * @channel: Channel were to TX/RX the message
 * @ttype: Transfer type (TX अगर set, RX otherwise)
 * @अवरोध_frame: अगर true HSI will send/receive a अवरोध frame. Data buffers are
 *		ignored in the request.
 */
काष्ठा hsi_msg अणु
	काष्ठा list_head	link;
	काष्ठा hsi_client	*cl;
	काष्ठा sg_table		sgt;
	व्योम			*context;

	व्योम			(*complete)(काष्ठा hsi_msg *msg);
	व्योम			(*deकाष्ठाor)(काष्ठा hsi_msg *msg);

	पूर्णांक			status;
	अचिन्हित पूर्णांक		actual_len;
	अचिन्हित पूर्णांक		channel;
	अचिन्हित पूर्णांक		ttype:1;
	अचिन्हित पूर्णांक		अवरोध_frame:1;
पूर्ण;

काष्ठा hsi_msg *hsi_alloc_msg(अचिन्हित पूर्णांक n_frag, gfp_t flags);
व्योम hsi_मुक्त_msg(काष्ठा hsi_msg *msg);

/**
 * काष्ठा hsi_port - HSI port device
 * @device: Driver model representation of the device
 * @tx_cfg: Current TX path configuration
 * @rx_cfg: Current RX path configuration
 * @num: Port number
 * @shared: Set when port can be shared by dअगरferent clients
 * @claimed: Reference count of clients which claimed the port
 * @lock: Serialize port claim
 * @async: Asynchronous transfer callback
 * @setup: Callback to set the HSI client configuration
 * @flush: Callback to clean the HW state and destroy all pending transfers
 * @start_tx: Callback to inक्रमm that a client wants to TX data
 * @stop_tx: Callback to inक्रमm that a client no दीर्घer wishes to TX data
 * @release: Callback to inक्रमm that a client no दीर्घer uses the port
 * @n_head: Notअगरier chain क्रम संकेतing port events to the clients.
 */
काष्ठा hsi_port अणु
	काष्ठा device			device;
	काष्ठा hsi_config		tx_cfg;
	काष्ठा hsi_config		rx_cfg;
	अचिन्हित पूर्णांक			num;
	अचिन्हित पूर्णांक			shared:1;
	पूर्णांक				claimed;
	काष्ठा mutex			lock;
	पूर्णांक				(*async)(काष्ठा hsi_msg *msg);
	पूर्णांक				(*setup)(काष्ठा hsi_client *cl);
	पूर्णांक				(*flush)(काष्ठा hsi_client *cl);
	पूर्णांक				(*start_tx)(काष्ठा hsi_client *cl);
	पूर्णांक				(*stop_tx)(काष्ठा hsi_client *cl);
	पूर्णांक				(*release)(काष्ठा hsi_client *cl);
	/* निजी */
	काष्ठा blocking_notअगरier_head	n_head;
पूर्ण;

#घोषणा to_hsi_port(dev) container_of(dev, काष्ठा hsi_port, device)
#घोषणा hsi_get_port(cl) to_hsi_port((cl)->device.parent)

पूर्णांक hsi_event(काष्ठा hsi_port *port, अचिन्हित दीर्घ event);
पूर्णांक hsi_claim_port(काष्ठा hsi_client *cl, अचिन्हित पूर्णांक share);
व्योम hsi_release_port(काष्ठा hsi_client *cl);

अटल अंतरभूत पूर्णांक hsi_port_claimed(काष्ठा hsi_client *cl)
अणु
	वापस cl->pclaimed;
पूर्ण

अटल अंतरभूत व्योम hsi_port_set_drvdata(काष्ठा hsi_port *port, व्योम *data)
अणु
	dev_set_drvdata(&port->device, data);
पूर्ण

अटल अंतरभूत व्योम *hsi_port_drvdata(काष्ठा hsi_port *port)
अणु
	वापस dev_get_drvdata(&port->device);
पूर्ण

/**
 * काष्ठा hsi_controller - HSI controller device
 * @device: Driver model representation of the device
 * @owner: Poपूर्णांकer to the module owning the controller
 * @id: HSI controller ID
 * @num_ports: Number of ports in the HSI controller
 * @port: Array of HSI ports
 */
काष्ठा hsi_controller अणु
	काष्ठा device		device;
	काष्ठा module		*owner;
	अचिन्हित पूर्णांक		id;
	अचिन्हित पूर्णांक		num_ports;
	काष्ठा hsi_port		**port;
पूर्ण;

#घोषणा to_hsi_controller(dev) container_of(dev, काष्ठा hsi_controller, device)

काष्ठा hsi_controller *hsi_alloc_controller(अचिन्हित पूर्णांक n_ports, gfp_t flags);
व्योम hsi_put_controller(काष्ठा hsi_controller *hsi);
पूर्णांक hsi_रेजिस्टर_controller(काष्ठा hsi_controller *hsi);
व्योम hsi_unरेजिस्टर_controller(काष्ठा hsi_controller *hsi);
काष्ठा hsi_client *hsi_new_client(काष्ठा hsi_port *port,
						काष्ठा hsi_board_info *info);
पूर्णांक hsi_हटाओ_client(काष्ठा device *dev, व्योम *data);
व्योम hsi_port_unरेजिस्टर_clients(काष्ठा hsi_port *port);

#अगर_घोषित CONFIG_OF
व्योम hsi_add_clients_from_dt(काष्ठा hsi_port *port,
			     काष्ठा device_node *clients);
#अन्यथा
अटल अंतरभूत व्योम hsi_add_clients_from_dt(काष्ठा hsi_port *port,
					   काष्ठा device_node *clients)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम hsi_controller_set_drvdata(काष्ठा hsi_controller *hsi,
								व्योम *data)
अणु
	dev_set_drvdata(&hsi->device, data);
पूर्ण

अटल अंतरभूत व्योम *hsi_controller_drvdata(काष्ठा hsi_controller *hsi)
अणु
	वापस dev_get_drvdata(&hsi->device);
पूर्ण

अटल अंतरभूत काष्ठा hsi_port *hsi_find_port_num(काष्ठा hsi_controller *hsi,
							अचिन्हित पूर्णांक num)
अणु
	वापस (num < hsi->num_ports) ? hsi->port[num] : शून्य;
पूर्ण

/*
 * API क्रम HSI clients
 */
पूर्णांक hsi_async(काष्ठा hsi_client *cl, काष्ठा hsi_msg *msg);

पूर्णांक hsi_get_channel_id_by_name(काष्ठा hsi_client *cl, अक्षर *name);

/**
 * hsi_id - Get HSI controller ID associated to a client
 * @cl: Poपूर्णांकer to a HSI client
 *
 * Return the controller id where the client is attached to
 */
अटल अंतरभूत अचिन्हित पूर्णांक hsi_id(काष्ठा hsi_client *cl)
अणु
	वापस	to_hsi_controller(cl->device.parent->parent)->id;
पूर्ण

/**
 * hsi_port_id - Gets the port number a client is attached to
 * @cl: Poपूर्णांकer to HSI client
 *
 * Return the port number associated to the client
 */
अटल अंतरभूत अचिन्हित पूर्णांक hsi_port_id(काष्ठा hsi_client *cl)
अणु
	वापस	to_hsi_port(cl->device.parent)->num;
पूर्ण

/**
 * hsi_setup - Configure the client's port
 * @cl: Poपूर्णांकer to the HSI client
 *
 * When sharing ports, clients should either relay on a single
 * client setup or have the same setup क्रम all of them.
 *
 * Return -त्रुटि_सं on failure, 0 on success
 */
अटल अंतरभूत पूर्णांक hsi_setup(काष्ठा hsi_client *cl)
अणु
	अगर (!hsi_port_claimed(cl))
		वापस -EACCES;
	वापस	hsi_get_port(cl)->setup(cl);
पूर्ण

/**
 * hsi_flush - Flush all pending transactions on the client's port
 * @cl: Poपूर्णांकer to the HSI client
 *
 * This function will destroy all pending hsi_msg in the port and reset
 * the HW port so it is पढ़ोy to receive and transmit from a clean state.
 *
 * Return -त्रुटि_सं on failure, 0 on success
 */
अटल अंतरभूत पूर्णांक hsi_flush(काष्ठा hsi_client *cl)
अणु
	अगर (!hsi_port_claimed(cl))
		वापस -EACCES;
	वापस hsi_get_port(cl)->flush(cl);
पूर्ण

/**
 * hsi_async_पढ़ो - Submit a पढ़ो transfer
 * @cl: Poपूर्णांकer to the HSI client
 * @msg: HSI message descriptor of the transfer
 *
 * Return -त्रुटि_सं on failure, 0 on success
 */
अटल अंतरभूत पूर्णांक hsi_async_पढ़ो(काष्ठा hsi_client *cl, काष्ठा hsi_msg *msg)
अणु
	msg->ttype = HSI_MSG_READ;
	वापस hsi_async(cl, msg);
पूर्ण

/**
 * hsi_async_ग_लिखो - Submit a ग_लिखो transfer
 * @cl: Poपूर्णांकer to the HSI client
 * @msg: HSI message descriptor of the transfer
 *
 * Return -त्रुटि_सं on failure, 0 on success
 */
अटल अंतरभूत पूर्णांक hsi_async_ग_लिखो(काष्ठा hsi_client *cl, काष्ठा hsi_msg *msg)
अणु
	msg->ttype = HSI_MSG_WRITE;
	वापस hsi_async(cl, msg);
पूर्ण

/**
 * hsi_start_tx - Signal the port that the client wants to start a TX
 * @cl: Poपूर्णांकer to the HSI client
 *
 * Return -त्रुटि_सं on failure, 0 on success
 */
अटल अंतरभूत पूर्णांक hsi_start_tx(काष्ठा hsi_client *cl)
अणु
	अगर (!hsi_port_claimed(cl))
		वापस -EACCES;
	वापस hsi_get_port(cl)->start_tx(cl);
पूर्ण

/**
 * hsi_stop_tx - Signal the port that the client no दीर्घer wants to transmit
 * @cl: Poपूर्णांकer to the HSI client
 *
 * Return -त्रुटि_सं on failure, 0 on success
 */
अटल अंतरभूत पूर्णांक hsi_stop_tx(काष्ठा hsi_client *cl)
अणु
	अगर (!hsi_port_claimed(cl))
		वापस -EACCES;
	वापस hsi_get_port(cl)->stop_tx(cl);
पूर्ण
#पूर्ण_अगर /* __LINUX_HSI_H__ */
