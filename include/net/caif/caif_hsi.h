<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:  Daniel Martensson / daniel.martensson@stericsson.com
 *	    Dmitry.Tarnyagin  / dmitry.tarnyagin@stericsson.com
 */

#अगर_अघोषित CAIF_HSI_H_
#घोषणा CAIF_HSI_H_

#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/caअगर_device.h>
#समावेश <linux/atomic.h>

/*
 * Maximum number of CAIF frames that can reside in the same HSI frame.
 */
#घोषणा CFHSI_MAX_PKTS 15

/*
 * Maximum number of bytes used क्रम the frame that can be embedded in the
 * HSI descriptor.
 */
#घोषणा CFHSI_MAX_EMB_FRM_SZ 96

/*
 * Decides अगर HSI buffers should be prefilled with 0xFF pattern क्रम easier
 * debugging. Both TX and RX buffers will be filled beक्रमe the transfer.
 */
#घोषणा CFHSI_DBG_PREFILL		0

/* Structure describing a HSI packet descriptor. */
#आशय pack(1) /* Byte alignment. */
काष्ठा cfhsi_desc अणु
	u8 header;
	u8 offset;
	u16 cffrm_len[CFHSI_MAX_PKTS];
	u8 emb_frm[CFHSI_MAX_EMB_FRM_SZ];
पूर्ण;
#आशय pack() /* Default alignment. */

/* Size of the complete HSI packet descriptor. */
#घोषणा CFHSI_DESC_SZ (माप(काष्ठा cfhsi_desc))

/*
 * Size of the complete HSI packet descriptor excluding the optional embedded
 * CAIF frame.
 */
#घोषणा CFHSI_DESC_SHORT_SZ (CFHSI_DESC_SZ - CFHSI_MAX_EMB_FRM_SZ)

/*
 * Maximum bytes transferred in one transfer.
 */
#घोषणा CFHSI_MAX_CAIF_FRAME_SZ 4096

#घोषणा CFHSI_MAX_PAYLOAD_SZ (CFHSI_MAX_PKTS * CFHSI_MAX_CAIF_FRAME_SZ)

/* Size of the complete HSI TX buffer. */
#घोषणा CFHSI_BUF_SZ_TX (CFHSI_DESC_SZ + CFHSI_MAX_PAYLOAD_SZ)

/* Size of the complete HSI RX buffer. */
#घोषणा CFHSI_BUF_SZ_RX ((2 * CFHSI_DESC_SZ) + CFHSI_MAX_PAYLOAD_SZ)

/* Biपंचांगasks क्रम the HSI descriptor. */
#घोषणा CFHSI_PIGGY_DESC		(0x01 << 7)

#घोषणा CFHSI_TX_STATE_IDLE			0
#घोषणा CFHSI_TX_STATE_XFER			1

#घोषणा CFHSI_RX_STATE_DESC			0
#घोषणा CFHSI_RX_STATE_PAYLOAD			1

/* Biपंचांगasks क्रम घातer management. */
#घोषणा CFHSI_WAKE_UP				0
#घोषणा CFHSI_WAKE_UP_ACK			1
#घोषणा CFHSI_WAKE_DOWN_ACK			2
#घोषणा CFHSI_AWAKE				3
#घोषणा CFHSI_WAKELOCK_HELD			4
#घोषणा CFHSI_SHUTDOWN				5
#घोषणा CFHSI_FLUSH_FIFO			6

#अगर_अघोषित CFHSI_INACTIVITY_TOUT
#घोषणा CFHSI_INACTIVITY_TOUT			(1 * HZ)
#पूर्ण_अगर /* CFHSI_INACTIVITY_TOUT */

#अगर_अघोषित CFHSI_WAKE_TOUT
#घोषणा CFHSI_WAKE_TOUT			(3 * HZ)
#पूर्ण_अगर /* CFHSI_WAKE_TOUT */

#अगर_अघोषित CFHSI_MAX_RX_RETRIES
#घोषणा CFHSI_MAX_RX_RETRIES		(10 * HZ)
#पूर्ण_अगर

/* Structure implemented by the CAIF HSI driver. */
काष्ठा cfhsi_cb_ops अणु
	व्योम (*tx_करोne_cb) (काष्ठा cfhsi_cb_ops *drv);
	व्योम (*rx_करोne_cb) (काष्ठा cfhsi_cb_ops *drv);
	व्योम (*wake_up_cb) (काष्ठा cfhsi_cb_ops *drv);
	व्योम (*wake_करोwn_cb) (काष्ठा cfhsi_cb_ops *drv);
पूर्ण;

/* Structure implemented by HSI device. */
काष्ठा cfhsi_ops अणु
	पूर्णांक (*cfhsi_up) (काष्ठा cfhsi_ops *dev);
	पूर्णांक (*cfhsi_करोwn) (काष्ठा cfhsi_ops *dev);
	पूर्णांक (*cfhsi_tx) (u8 *ptr, पूर्णांक len, काष्ठा cfhsi_ops *dev);
	पूर्णांक (*cfhsi_rx) (u8 *ptr, पूर्णांक len, काष्ठा cfhsi_ops *dev);
	पूर्णांक (*cfhsi_wake_up) (काष्ठा cfhsi_ops *dev);
	पूर्णांक (*cfhsi_wake_करोwn) (काष्ठा cfhsi_ops *dev);
	पूर्णांक (*cfhsi_get_peer_wake) (काष्ठा cfhsi_ops *dev, bool *status);
	पूर्णांक (*cfhsi_fअगरo_occupancy) (काष्ठा cfhsi_ops *dev, माप_प्रकार *occupancy);
	पूर्णांक (*cfhsi_rx_cancel)(काष्ठा cfhsi_ops *dev);
	काष्ठा cfhsi_cb_ops *cb_ops;
पूर्ण;

/* Structure holds status of received CAIF frames processing */
काष्ठा cfhsi_rx_state अणु
	पूर्णांक state;
	पूर्णांक nfrms;
	पूर्णांक pld_len;
	पूर्णांक retries;
	bool piggy_desc;
पूर्ण;

/* Priority mapping */
क्रमागत अणु
	CFHSI_PRIO_CTL = 0,
	CFHSI_PRIO_VI,
	CFHSI_PRIO_VO,
	CFHSI_PRIO_BEBK,
	CFHSI_PRIO_LAST,
पूर्ण;

काष्ठा cfhsi_config अणु
	u32 inactivity_समयout;
	u32 aggregation_समयout;
	u32 head_align;
	u32 tail_align;
	u32 q_high_mark;
	u32 q_low_mark;
पूर्ण;

/* Structure implemented by CAIF HSI drivers. */
काष्ठा cfhsi अणु
	काष्ठा caअगर_dev_common cfdev;
	काष्ठा net_device *ndev;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा sk_buff_head qhead[CFHSI_PRIO_LAST];
	काष्ठा cfhsi_cb_ops cb_ops;
	काष्ठा cfhsi_ops *ops;
	पूर्णांक tx_state;
	काष्ठा cfhsi_rx_state rx_state;
	काष्ठा cfhsi_config cfg;
	पूर्णांक rx_len;
	u8 *rx_ptr;
	u8 *tx_buf;
	u8 *rx_buf;
	u8 *rx_flip_buf;
	spinlock_t lock;
	पूर्णांक flow_off_sent;
	काष्ठा list_head list;
	काष्ठा work_काष्ठा wake_up_work;
	काष्ठा work_काष्ठा wake_करोwn_work;
	काष्ठा work_काष्ठा out_of_sync_work;
	काष्ठा workqueue_काष्ठा *wq;
	रुको_queue_head_t wake_up_रुको;
	रुको_queue_head_t wake_करोwn_रुको;
	रुको_queue_head_t flush_fअगरo_रुको;
	काष्ठा समयr_list inactivity_समयr;
	काष्ठा समयr_list rx_slowpath_समयr;

	/* TX aggregation */
	पूर्णांक aggregation_len;
	काष्ठा समयr_list aggregation_समयr;

	अचिन्हित दीर्घ bits;
पूर्ण;
बाह्य काष्ठा platक्रमm_driver cfhsi_driver;

/**
 * क्रमागत अगरla_caअगर_hsi - CAIF HSI NetlinkRT parameters.
 * @IFLA_CAIF_HSI_INACTIVITY_TOUT: Inactivity समयout beक्रमe
 *			taking the HSI wakeline करोwn, in milliseconds.
 * When using RT Netlink to create, destroy or configure a CAIF HSI पूर्णांकerface,
 * क्रमागत अगरla_caअगर_hsi is used to specअगरy the configuration attributes.
 */
क्रमागत अगरla_caअगर_hsi अणु
	__IFLA_CAIF_HSI_UNSPEC,
	__IFLA_CAIF_HSI_INACTIVITY_TOUT,
	__IFLA_CAIF_HSI_AGGREGATION_TOUT,
	__IFLA_CAIF_HSI_HEAD_ALIGN,
	__IFLA_CAIF_HSI_TAIL_ALIGN,
	__IFLA_CAIF_HSI_QHIGH_WATERMARK,
	__IFLA_CAIF_HSI_QLOW_WATERMARK,
	__IFLA_CAIF_HSI_MAX
पूर्ण;

काष्ठा cfhsi_ops *cfhsi_get_ops(व्योम);

#पूर्ण_अगर		/* CAIF_HSI_H_ */
