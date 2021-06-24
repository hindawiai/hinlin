<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Most ISHTP provider device and ISHTP logic declarations
 *
 * Copyright (c) 2003-2016, Intel Corporation.
 */

#अगर_अघोषित _ISHTP_DEV_H_
#घोषणा _ISHTP_DEV_H_

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश "bus.h"
#समावेश "hbm.h"

#घोषणा	IPC_PAYLOAD_SIZE	128
#घोषणा ISHTP_RD_MSG_BUF_SIZE	IPC_PAYLOAD_SIZE
#घोषणा	IPC_FULL_MSG_SIZE	132

/* Number of messages to be held in ISR->BH FIFO */
#घोषणा	RD_INT_FIFO_SIZE	64

/*
 * Number of IPC messages to be held in Tx FIFO, to be sent by ISR -
 * Tx complete पूर्णांकerrupt or RX_COMPLETE handler
 */
#घोषणा	IPC_TX_FIFO_SIZE	512

/*
 * Number of Maximum ISHTP Clients
 */
#घोषणा ISHTP_CLIENTS_MAX 256

/*
 * Number of File descriptors/handles
 * that can be खोलोed to the driver.
 *
 * Limit to 255: 256 Total Clients
 * minus पूर्णांकernal client क्रम ISHTP Bus Messages
 */
#घोषणा ISHTP_MAX_OPEN_HANDLE_COUNT (ISHTP_CLIENTS_MAX - 1)

/* Internal Clients Number */
#घोषणा ISHTP_HOST_CLIENT_ID_ANY		(-1)
#घोषणा ISHTP_HBM_HOST_CLIENT_ID		0

#घोषणा	MAX_DMA_DELAY	20

/* ISHTP device states */
क्रमागत ishtp_dev_state अणु
	ISHTP_DEV_INITIALIZING = 0,
	ISHTP_DEV_INIT_CLIENTS,
	ISHTP_DEV_ENABLED,
	ISHTP_DEV_RESETTING,
	ISHTP_DEV_DISABLED,
	ISHTP_DEV_POWER_DOWN,
	ISHTP_DEV_POWER_UP
पूर्ण;
स्थिर अक्षर *ishtp_dev_state_str(पूर्णांक state);

काष्ठा ishtp_cl;

/**
 * काष्ठा ishtp_fw_client - representation of fw client
 *
 * @props - client properties
 * @client_id - fw client id
 */
काष्ठा ishtp_fw_client अणु
	काष्ठा ishtp_client_properties props;
	uपूर्णांक8_t client_id;
पूर्ण;

/*
 * Control info क्रम IPC messages ISHTP/IPC sending FIFO -
 * list with अंतरभूत data buffer
 * This काष्ठाure will be filled with parameters submitted
 * by the caller glue layer
 * 'buf' may be pointing to the external buffer or to 'inline_data'
 * 'offset' will be initialized to 0 by submitting
 *
 * 'ipc_send_compl' is पूर्णांकended क्रम use by clients that send fragmented
 * messages. When a fragment is sent करोwn to IPC msg regs,
 * it will be called.
 * If it has more fragments to send, it will करो it. With last fragment
 * it will send appropriate ISHTP "message-complete" flag.
 * It will हटाओ the outstanding message
 * (mark outstanding buffer as available).
 * If counting flow control is in work and there are more flow control
 * credits, it can put the next client message queued in cl.
 * काष्ठाure क्रम IPC processing.
 *
 */
काष्ठा wr_msg_ctl_info अणु
	/* Will be called with 'ipc_send_compl_prm' as parameter */
	व्योम (*ipc_send_compl)(व्योम *);

	व्योम *ipc_send_compl_prm;
	माप_प्रकार length;
	काष्ठा list_head	link;
	अचिन्हित अक्षर	अंतरभूत_data[IPC_FULL_MSG_SIZE];
पूर्ण;

/*
 * The ISHTP layer talks to hardware IPC message using the following
 * callbacks
 */
काष्ठा ishtp_hw_ops अणु
	पूर्णांक	(*hw_reset)(काष्ठा ishtp_device *dev);
	पूर्णांक	(*ipc_reset)(काष्ठा ishtp_device *dev);
	uपूर्णांक32_t (*ipc_get_header)(काष्ठा ishtp_device *dev, पूर्णांक length,
				   पूर्णांक busy);
	पूर्णांक	(*ग_लिखो)(काष्ठा ishtp_device *dev,
		व्योम (*ipc_send_compl)(व्योम *), व्योम *ipc_send_compl_prm,
		अचिन्हित अक्षर *msg, पूर्णांक length);
	uपूर्णांक32_t	(*ishtp_पढ़ो_hdr)(स्थिर काष्ठा ishtp_device *dev);
	पूर्णांक	(*ishtp_पढ़ो)(काष्ठा ishtp_device *dev, अचिन्हित अक्षर *buffer,
			अचिन्हित दीर्घ buffer_length);
	uपूर्णांक32_t	(*get_fw_status)(काष्ठा ishtp_device *dev);
	व्योम	(*sync_fw_घड़ी)(काष्ठा ishtp_device *dev);
पूर्ण;

/**
 * काष्ठा ishtp_device - ISHTP निजी device काष्ठा
 */
काष्ठा ishtp_device अणु
	काष्ठा device *devc;	/* poपूर्णांकer to lowest device */
	काष्ठा pci_dev *pdev;	/* PCI device to get device ids */

	/* रुकोq क्रम रुकोing क्रम suspend response */
	रुको_queue_head_t suspend_रुको;
	bool suspend_flag;	/* Suspend is active */

	/* रुकोq क्रम रुकोing क्रम resume response */
	रुको_queue_head_t resume_रुको;
	bool resume_flag;	/*Resume is active */

	/*
	 * lock क्रम the device, क्रम everything that करोesn't have
	 * a dedicated spinlock
	 */
	spinlock_t device_lock;

	bool recvd_hw_पढ़ोy;
	काष्ठा hbm_version version;
	पूर्णांक transfer_path; /* Choice of transfer path: IPC or DMA */

	/* ishtp device states */
	क्रमागत ishtp_dev_state dev_state;
	क्रमागत ishtp_hbm_state hbm_state;

	/* driver पढ़ो queue */
	काष्ठा ishtp_cl_rb पढ़ो_list;
	spinlock_t पढ़ो_list_spinlock;

	/* list of ishtp_cl's */
	काष्ठा list_head cl_list;
	spinlock_t cl_list_lock;
	दीर्घ खोलो_handle_count;

	/* List of bus devices */
	काष्ठा list_head device_list;
	spinlock_t device_list_lock;

	/* रुकोing queues क्रम receive message from FW */
	रुको_queue_head_t रुको_hw_पढ़ोy;
	रुको_queue_head_t रुको_hbm_recvd_msg;

	/* FIFO क्रम input messages क्रम BH processing */
	अचिन्हित अक्षर rd_msg_fअगरo[RD_INT_FIFO_SIZE * IPC_PAYLOAD_SIZE];
	अचिन्हित पूर्णांक rd_msg_fअगरo_head, rd_msg_fअगरo_tail;
	spinlock_t rd_msg_spinlock;
	काष्ठा work_काष्ठा bh_hbm_work;

	/* IPC ग_लिखो queue */
	काष्ठा list_head wr_processing_list, wr_मुक्त_list;
	/* For both processing list  and मुक्त list */
	spinlock_t wr_processing_spinlock;

	काष्ठा ishtp_fw_client *fw_clients; /*Note:memory has to be allocated*/
	DECLARE_BITMAP(fw_clients_map, ISHTP_CLIENTS_MAX);
	DECLARE_BITMAP(host_clients_map, ISHTP_CLIENTS_MAX);
	uपूर्णांक8_t fw_clients_num;
	uपूर्णांक8_t fw_client_presentation_num;
	uपूर्णांक8_t fw_client_index;
	spinlock_t fw_clients_lock;

	/* TX DMA buffers and slots */
	पूर्णांक ishtp_host_dma_enabled;
	व्योम *ishtp_host_dma_tx_buf;
	अचिन्हित पूर्णांक ishtp_host_dma_tx_buf_size;
	uपूर्णांक64_t ishtp_host_dma_tx_buf_phys;
	पूर्णांक ishtp_dma_num_slots;

	/* map of 4k blocks in Tx dma buf: 0-मुक्त, 1-used */
	uपूर्णांक8_t *ishtp_dma_tx_map;
	spinlock_t ishtp_dma_tx_lock;

	/* RX DMA buffers and slots */
	व्योम *ishtp_host_dma_rx_buf;
	अचिन्हित पूर्णांक ishtp_host_dma_rx_buf_size;
	uपूर्णांक64_t ishtp_host_dma_rx_buf_phys;

	/* Dump to trace buffers अगर enabled*/
	__म_लिखो(2, 3) व्योम (*prपूर्णांक_log)(काष्ठा ishtp_device *dev,
					 स्थिर अक्षर *क्रमmat, ...);

	/* Debug stats */
	अचिन्हित पूर्णांक	ipc_rx_cnt;
	अचिन्हित दीर्घ दीर्घ	ipc_rx_bytes_cnt;
	अचिन्हित पूर्णांक	ipc_tx_cnt;
	अचिन्हित दीर्घ दीर्घ	ipc_tx_bytes_cnt;

	स्थिर काष्ठा ishtp_hw_ops *ops;
	माप_प्रकार	mtu;
	uपूर्णांक32_t	ishtp_msg_hdr;
	अक्षर hw[] __aligned(माप(व्योम *));
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ ishtp_secs_to_jअगरfies(अचिन्हित दीर्घ sec)
अणु
	वापस msecs_to_jअगरfies(sec * MSEC_PER_SEC);
पूर्ण

/*
 * Register Access Function
 */
अटल अंतरभूत पूर्णांक ish_ipc_reset(काष्ठा ishtp_device *dev)
अणु
	वापस dev->ops->ipc_reset(dev);
पूर्ण

/* Exported function */
व्योम	ishtp_device_init(काष्ठा ishtp_device *dev);
पूर्णांक	ishtp_start(काष्ठा ishtp_device *dev);

#पूर्ण_अगर /*_ISHTP_DEV_H_*/
