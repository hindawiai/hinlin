<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  The NFC Controller Interface is the communication protocol between an
 *  NFC Controller (NFCC) and a Device Host (DH).
 *
 *  Copyright (C) 2011 Texas Instruments, Inc.
 *  Copyright (C) 2013 Intel Corporation. All rights reserved.
 *  Copyright (C) 2014 Marvell International Ltd.
 *
 *  Written by Ilan Elias <ilane@ti.com>
 *
 *  Acknowledgements:
 *  This file is based on hci_core.h, which was written
 *  by Maxim Krasnyansky.
 */

#अगर_अघोषित __NCI_CORE_H
#घोषणा __NCI_CORE_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/tty.h>

#समावेश <net/nfc/nfc.h>
#समावेश <net/nfc/nci.h>

/* NCI device flags */
क्रमागत nci_flag अणु
	NCI_INIT,
	NCI_UP,
	NCI_DATA_EXCHANGE,
	NCI_DATA_EXCHANGE_TO,
पूर्ण;

/* NCI device states */
क्रमागत nci_state अणु
	NCI_IDLE,
	NCI_DISCOVERY,
	NCI_W4_ALL_DISCOVERIES,
	NCI_W4_HOST_SELECT,
	NCI_POLL_ACTIVE,
	NCI_LISTEN_ACTIVE,
	NCI_LISTEN_SLEEP,
पूर्ण;

/* NCI समयouts */
#घोषणा NCI_RESET_TIMEOUT			5000
#घोषणा NCI_INIT_TIMEOUT			5000
#घोषणा NCI_SET_CONFIG_TIMEOUT			5000
#घोषणा NCI_RF_DISC_TIMEOUT			5000
#घोषणा NCI_RF_DISC_SELECT_TIMEOUT		5000
#घोषणा NCI_RF_DEACTIVATE_TIMEOUT		30000
#घोषणा NCI_CMD_TIMEOUT				5000
#घोषणा NCI_DATA_TIMEOUT			700

काष्ठा nci_dev;

काष्ठा nci_driver_ops अणु
	__u16 opcode;
	पूर्णांक (*rsp)(काष्ठा nci_dev *dev, काष्ठा sk_buff *skb);
	पूर्णांक (*ntf)(काष्ठा nci_dev *dev, काष्ठा sk_buff *skb);
पूर्ण;

काष्ठा nci_ops अणु
	पूर्णांक   (*init)(काष्ठा nci_dev *ndev);
	पूर्णांक   (*खोलो)(काष्ठा nci_dev *ndev);
	पूर्णांक   (*बंद)(काष्ठा nci_dev *ndev);
	पूर्णांक   (*send)(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb);
	पूर्णांक   (*setup)(काष्ठा nci_dev *ndev);
	पूर्णांक   (*post_setup)(काष्ठा nci_dev *ndev);
	पूर्णांक   (*fw_करोwnload)(काष्ठा nci_dev *ndev, स्थिर अक्षर *firmware_name);
	__u32 (*get_rfprotocol)(काष्ठा nci_dev *ndev, __u8 rf_protocol);
	पूर्णांक   (*discover_se)(काष्ठा nci_dev *ndev);
	पूर्णांक   (*disable_se)(काष्ठा nci_dev *ndev, u32 se_idx);
	पूर्णांक   (*enable_se)(काष्ठा nci_dev *ndev, u32 se_idx);
	पूर्णांक   (*se_io)(काष्ठा nci_dev *ndev, u32 se_idx,
				u8 *apdu, माप_प्रकार apdu_length,
				se_io_cb_t cb, व्योम *cb_context);
	पूर्णांक   (*hci_load_session)(काष्ठा nci_dev *ndev);
	व्योम  (*hci_event_received)(काष्ठा nci_dev *ndev, u8 pipe, u8 event,
				    काष्ठा sk_buff *skb);
	व्योम  (*hci_cmd_received)(काष्ठा nci_dev *ndev, u8 pipe, u8 cmd,
				  काष्ठा sk_buff *skb);

	काष्ठा nci_driver_ops *prop_ops;
	माप_प्रकार n_prop_ops;

	काष्ठा nci_driver_ops *core_ops;
	माप_प्रकार n_core_ops;
पूर्ण;

#घोषणा NCI_MAX_SUPPORTED_RF_INTERFACES		4
#घोषणा NCI_MAX_DISCOVERED_TARGETS		10
#घोषणा NCI_MAX_NUM_NFCEE   255
#घोषणा NCI_MAX_CONN_ID		7
#घोषणा NCI_MAX_PROPRIETARY_CMD 64

काष्ठा nci_conn_info अणु
	काष्ठा list_head list;
	/* NCI specअगरication 4.4.2 Connection Creation
	 * The combination of destination type and destination specअगरic
	 * parameters shall uniquely identअगरy a single destination क्रम the
	 * Logical Connection
	 */
	काष्ठा dest_spec_params *dest_params;
	__u8	dest_type;
	__u8	conn_id;
	__u8	max_pkt_payload_len;

	atomic_t credits_cnt;
	__u8	 initial_num_credits;

	data_exchange_cb_t	data_exchange_cb;
	व्योम *data_exchange_cb_context;

	काष्ठा sk_buff *rx_skb;
पूर्ण;

#घोषणा NCI_INVALID_CONN_ID 0x80

#घोषणा NCI_HCI_ANY_OPEN_PIPE      0x03

/* Gates */
#घोषणा NCI_HCI_ADMIN_GATE         0x00
#घोषणा NCI_HCI_LOOPBACK_GATE	   0x04
#घोषणा NCI_HCI_IDENTITY_MGMT_GATE 0x05
#घोषणा NCI_HCI_LINK_MGMT_GATE     0x06

/* Pipes */
#घोषणा NCI_HCI_LINK_MGMT_PIPE             0x00
#घोषणा NCI_HCI_ADMIN_PIPE                 0x01

/* Generic responses */
#घोषणा NCI_HCI_ANY_OK                     0x00
#घोषणा NCI_HCI_ANY_E_NOT_CONNECTED        0x01
#घोषणा NCI_HCI_ANY_E_CMD_PAR_UNKNOWN      0x02
#घोषणा NCI_HCI_ANY_E_NOK                  0x03
#घोषणा NCI_HCI_ANY_E_PIPES_FULL           0x04
#घोषणा NCI_HCI_ANY_E_REG_PAR_UNKNOWN      0x05
#घोषणा NCI_HCI_ANY_E_PIPE_NOT_OPENED      0x06
#घोषणा NCI_HCI_ANY_E_CMD_NOT_SUPPORTED    0x07
#घोषणा NCI_HCI_ANY_E_INHIBITED            0x08
#घोषणा NCI_HCI_ANY_E_TIMEOUT              0x09
#घोषणा NCI_HCI_ANY_E_REG_ACCESS_DENIED    0x0a
#घोषणा NCI_HCI_ANY_E_PIPE_ACCESS_DENIED   0x0b

#घोषणा NCI_HCI_DO_NOT_OPEN_PIPE           0x81
#घोषणा NCI_HCI_INVALID_PIPE               0x80
#घोषणा NCI_HCI_INVALID_GATE               0xFF
#घोषणा NCI_HCI_INVALID_HOST               0x80

#घोषणा NCI_HCI_MAX_CUSTOM_GATES   50
/*
 * According to specअगरication 102 622 chapter 4.4 Pipes,
 * the pipe identअगरier is 7 bits दीर्घ.
 */
#घोषणा NCI_HCI_MAX_PIPES          128

काष्ठा nci_hci_gate अणु
	u8 gate;
	u8 pipe;
	u8 dest_host;
पूर्ण __packed;

काष्ठा nci_hci_pipe अणु
	u8 gate;
	u8 host;
पूर्ण __packed;

काष्ठा nci_hci_init_data अणु
	u8 gate_count;
	काष्ठा nci_hci_gate gates[NCI_HCI_MAX_CUSTOM_GATES];
	अक्षर session_id[9];
पूर्ण;

#घोषणा NCI_HCI_MAX_GATES          256

काष्ठा nci_hci_dev अणु
	u8 nfcee_id;
	काष्ठा nci_dev *ndev;
	काष्ठा nci_conn_info *conn_info;

	काष्ठा nci_hci_init_data init_data;
	काष्ठा nci_hci_pipe pipes[NCI_HCI_MAX_PIPES];
	u8 gate2pipe[NCI_HCI_MAX_GATES];
	पूर्णांक expected_pipes;
	पूर्णांक count_pipes;

	काष्ठा sk_buff_head rx_hcp_frags;
	काष्ठा work_काष्ठा msg_rx_work;
	काष्ठा sk_buff_head msg_rx_queue;
पूर्ण;

/* NCI Core काष्ठाures */
काष्ठा nci_dev अणु
	काष्ठा nfc_dev		*nfc_dev;
	काष्ठा nci_ops		*ops;
	काष्ठा nci_hci_dev	*hci_dev;

	पूर्णांक			tx_headroom;
	पूर्णांक			tx_tailroom;

	atomic_t		state;
	अचिन्हित दीर्घ		flags;

	atomic_t		cmd_cnt;
	__u8			cur_conn_id;

	काष्ठा list_head	conn_info_list;
	काष्ठा nci_conn_info	*rf_conn_info;

	काष्ठा समयr_list	cmd_समयr;
	काष्ठा समयr_list	data_समयr;

	काष्ठा workqueue_काष्ठा	*cmd_wq;
	काष्ठा work_काष्ठा	cmd_work;

	काष्ठा workqueue_काष्ठा	*rx_wq;
	काष्ठा work_काष्ठा	rx_work;

	काष्ठा workqueue_काष्ठा	*tx_wq;
	काष्ठा work_काष्ठा	tx_work;

	काष्ठा sk_buff_head	cmd_q;
	काष्ठा sk_buff_head	rx_q;
	काष्ठा sk_buff_head	tx_q;

	काष्ठा mutex		req_lock;
	काष्ठा completion	req_completion;
	__u32			req_status;
	__u32			req_result;

	व्योम			*driver_data;

	__u32			poll_prots;
	__u32			target_active_prot;

	काष्ठा nfc_target	tarमाला_लो[NCI_MAX_DISCOVERED_TARGETS];
	पूर्णांक			n_tarमाला_लो;

	/* received during NCI_OP_CORE_RESET_RSP */
	__u8			nci_ver;

	/* received during NCI_OP_CORE_INIT_RSP */
	__u32			nfcc_features;
	__u8			num_supported_rf_पूर्णांकerfaces;
	__u8			supported_rf_पूर्णांकerfaces
				[NCI_MAX_SUPPORTED_RF_INTERFACES];
	__u8			max_logical_connections;
	__u16			max_routing_table_size;
	__u8			max_ctrl_pkt_payload_len;
	__u16			max_size_क्रम_large_params;
	__u8			manufact_id;
	__u32			manufact_specअगरic_info;

	/* Save RF Discovery ID or NFCEE ID under conn_create */
	काष्ठा dest_spec_params cur_params;
	/* Save destination type under conn_create */
	__u8			cur_dest_type;

	/* stored during nci_data_exchange */
	काष्ठा sk_buff		*rx_data_reassembly;

	/* stored during पूर्णांकf_activated_ntf */
	__u8 remote_gb[NFC_MAX_GT_LEN];
	__u8 remote_gb_len;
पूर्ण;

/* ----- NCI Devices ----- */
काष्ठा nci_dev *nci_allocate_device(काष्ठा nci_ops *ops,
				    __u32 supported_protocols,
				    पूर्णांक tx_headroom,
				    पूर्णांक tx_tailroom);
व्योम nci_मुक्त_device(काष्ठा nci_dev *ndev);
पूर्णांक nci_रेजिस्टर_device(काष्ठा nci_dev *ndev);
व्योम nci_unरेजिस्टर_device(काष्ठा nci_dev *ndev);
पूर्णांक nci_request(काष्ठा nci_dev *ndev,
		व्योम (*req)(काष्ठा nci_dev *ndev,
			    अचिन्हित दीर्घ opt),
		अचिन्हित दीर्घ opt, __u32 समयout);
पूर्णांक nci_prop_cmd(काष्ठा nci_dev *ndev, __u8 oid, माप_प्रकार len, __u8 *payload);
पूर्णांक nci_core_cmd(काष्ठा nci_dev *ndev, __u16 opcode, माप_प्रकार len, __u8 *payload);
पूर्णांक nci_core_reset(काष्ठा nci_dev *ndev);
पूर्णांक nci_core_init(काष्ठा nci_dev *ndev);

पूर्णांक nci_recv_frame(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb);
पूर्णांक nci_send_frame(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb);
पूर्णांक nci_set_config(काष्ठा nci_dev *ndev, __u8 id, माप_प्रकार len, __u8 *val);

पूर्णांक nci_nfcee_discover(काष्ठा nci_dev *ndev, u8 action);
पूर्णांक nci_nfcee_mode_set(काष्ठा nci_dev *ndev, u8 nfcee_id, u8 nfcee_mode);
पूर्णांक nci_core_conn_create(काष्ठा nci_dev *ndev, u8 destination_type,
			 u8 number_destination_params,
			 माप_प्रकार params_len,
			 काष्ठा core_conn_create_dest_spec_params *params);
पूर्णांक nci_core_conn_बंद(काष्ठा nci_dev *ndev, u8 conn_id);
पूर्णांक nci_nfcc_loopback(काष्ठा nci_dev *ndev, व्योम *data, माप_प्रकार data_len,
		      काष्ठा sk_buff **resp);

काष्ठा nci_hci_dev *nci_hci_allocate(काष्ठा nci_dev *ndev);
व्योम nci_hci_deallocate(काष्ठा nci_dev *ndev);
पूर्णांक nci_hci_send_event(काष्ठा nci_dev *ndev, u8 gate, u8 event,
		       स्थिर u8 *param, माप_प्रकार param_len);
पूर्णांक nci_hci_send_cmd(काष्ठा nci_dev *ndev, u8 gate,
		     u8 cmd, स्थिर u8 *param, माप_प्रकार param_len,
		     काष्ठा sk_buff **skb);
पूर्णांक nci_hci_खोलो_pipe(काष्ठा nci_dev *ndev, u8 pipe);
पूर्णांक nci_hci_connect_gate(काष्ठा nci_dev *ndev, u8 dest_host,
			 u8 dest_gate, u8 pipe);
पूर्णांक nci_hci_set_param(काष्ठा nci_dev *ndev, u8 gate, u8 idx,
		      स्थिर u8 *param, माप_प्रकार param_len);
पूर्णांक nci_hci_get_param(काष्ठा nci_dev *ndev, u8 gate, u8 idx,
		      काष्ठा sk_buff **skb);
पूर्णांक nci_hci_clear_all_pipes(काष्ठा nci_dev *ndev);
पूर्णांक nci_hci_dev_session_init(काष्ठा nci_dev *ndev);

अटल अंतरभूत काष्ठा sk_buff *nci_skb_alloc(काष्ठा nci_dev *ndev,
					    अचिन्हित पूर्णांक len,
					    gfp_t how)
अणु
	काष्ठा sk_buff *skb;

	skb = alloc_skb(len + ndev->tx_headroom + ndev->tx_tailroom, how);
	अगर (skb)
		skb_reserve(skb, ndev->tx_headroom);

	वापस skb;
पूर्ण

अटल अंतरभूत व्योम nci_set_parent_dev(काष्ठा nci_dev *ndev, काष्ठा device *dev)
अणु
	nfc_set_parent_dev(ndev->nfc_dev, dev);
पूर्ण

अटल अंतरभूत व्योम nci_set_drvdata(काष्ठा nci_dev *ndev, व्योम *data)
अणु
	ndev->driver_data = data;
पूर्ण

अटल अंतरभूत व्योम *nci_get_drvdata(काष्ठा nci_dev *ndev)
अणु
	वापस ndev->driver_data;
पूर्ण

अटल अंतरभूत पूर्णांक nci_set_venकरोr_cmds(काष्ठा nci_dev *ndev,
				      काष्ठा nfc_venकरोr_cmd *cmds,
				      पूर्णांक n_cmds)
अणु
	वापस nfc_set_venकरोr_cmds(ndev->nfc_dev, cmds, n_cmds);
पूर्ण

व्योम nci_rsp_packet(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb);
व्योम nci_ntf_packet(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb);
पूर्णांक nci_prop_rsp_packet(काष्ठा nci_dev *ndev, __u16 opcode,
			काष्ठा sk_buff *skb);
पूर्णांक nci_prop_ntf_packet(काष्ठा nci_dev *ndev, __u16 opcode,
			काष्ठा sk_buff *skb);
पूर्णांक nci_core_rsp_packet(काष्ठा nci_dev *ndev, __u16 opcode,
			काष्ठा sk_buff *skb);
पूर्णांक nci_core_ntf_packet(काष्ठा nci_dev *ndev, __u16 opcode,
			काष्ठा sk_buff *skb);
व्योम nci_rx_data_packet(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb);
पूर्णांक nci_send_cmd(काष्ठा nci_dev *ndev, __u16 opcode, __u8 plen, व्योम *payload);
पूर्णांक nci_send_data(काष्ठा nci_dev *ndev, __u8 conn_id, काष्ठा sk_buff *skb);
पूर्णांक nci_conn_max_data_pkt_payload_size(काष्ठा nci_dev *ndev, __u8 conn_id);
व्योम nci_data_exchange_complete(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb,
				__u8 conn_id, पूर्णांक err);
व्योम nci_hci_data_received_cb(व्योम *context, काष्ठा sk_buff *skb, पूर्णांक err);

व्योम nci_clear_target_list(काष्ठा nci_dev *ndev);

/* ----- NCI requests ----- */
#घोषणा NCI_REQ_DONE		0
#घोषणा NCI_REQ_PEND		1
#घोषणा NCI_REQ_CANCELED	2

व्योम nci_req_complete(काष्ठा nci_dev *ndev, पूर्णांक result);
काष्ठा nci_conn_info *nci_get_conn_info_by_conn_id(काष्ठा nci_dev *ndev,
						   पूर्णांक conn_id);
पूर्णांक nci_get_conn_info_by_dest_type_params(काष्ठा nci_dev *ndev, u8 dest_type,
					  काष्ठा dest_spec_params *params);

/* ----- NCI status code ----- */
पूर्णांक nci_to_त्रुटि_सं(__u8 code);

/* ----- NCI over SPI acknowledge modes ----- */
#घोषणा NCI_SPI_CRC_DISABLED	0x00
#घोषणा NCI_SPI_CRC_ENABLED	0x01

/* ----- NCI SPI काष्ठाures ----- */
काष्ठा nci_spi अणु
	काष्ठा nci_dev		*ndev;
	काष्ठा spi_device	*spi;

	अचिन्हित पूर्णांक		xfer_udelay;	/* microseconds delay between
						  transactions */

	अचिन्हित पूर्णांक		xfer_speed_hz; /*
						* SPI घड़ी frequency
						* 0 => शेष घड़ी
						*/

	u8			acknowledge_mode;

	काष्ठा completion	req_completion;
	u8			req_result;
पूर्ण;

/* ----- NCI SPI ----- */
काष्ठा nci_spi *nci_spi_allocate_spi(काष्ठा spi_device *spi,
				     u8 acknowledge_mode, अचिन्हित पूर्णांक delay,
				     काष्ठा nci_dev *ndev);
पूर्णांक nci_spi_send(काष्ठा nci_spi *nspi,
		 काष्ठा completion *ग_लिखो_handshake_completion,
		 काष्ठा sk_buff *skb);
काष्ठा sk_buff *nci_spi_पढ़ो(काष्ठा nci_spi *nspi);

/* ----- NCI UART ---- */

/* Ioctl */
#घोषणा NCIUARTSETDRIVER	_IOW('U', 0, अक्षर *)

क्रमागत nci_uart_driver अणु
	NCI_UART_DRIVER_MARVELL = 0,
	NCI_UART_DRIVER_MAX
पूर्ण;

काष्ठा nci_uart;

काष्ठा nci_uart_ops अणु
	पूर्णांक (*खोलो)(काष्ठा nci_uart *nci_uart);
	व्योम (*बंद)(काष्ठा nci_uart *nci_uart);
	पूर्णांक (*recv)(काष्ठा nci_uart *nci_uart, काष्ठा sk_buff *skb);
	पूर्णांक (*send)(काष्ठा nci_uart *nci_uart, काष्ठा sk_buff *skb);
	व्योम (*tx_start)(काष्ठा nci_uart *nci_uart);
	व्योम (*tx_करोne)(काष्ठा nci_uart *nci_uart);
पूर्ण;

काष्ठा nci_uart अणु
	काष्ठा module		*owner;
	काष्ठा nci_uart_ops	ops;
	स्थिर अक्षर		*name;
	क्रमागत nci_uart_driver	driver;

	/* Dynamic data */
	काष्ठा nci_dev		*ndev;
	spinlock_t		rx_lock;
	काष्ठा work_काष्ठा	ग_लिखो_work;
	काष्ठा tty_काष्ठा	*tty;
	अचिन्हित दीर्घ		tx_state;
	काष्ठा sk_buff_head	tx_q;
	काष्ठा sk_buff		*tx_skb;
	काष्ठा sk_buff		*rx_skb;
	पूर्णांक			rx_packet_len;
	व्योम			*drv_data;
पूर्ण;

पूर्णांक nci_uart_रेजिस्टर(काष्ठा nci_uart *nu);
व्योम nci_uart_unरेजिस्टर(काष्ठा nci_uart *nu);
व्योम nci_uart_set_config(काष्ठा nci_uart *nu, पूर्णांक baudrate, पूर्णांक flow_ctrl);

#पूर्ण_अगर /* __NCI_CORE_H */
