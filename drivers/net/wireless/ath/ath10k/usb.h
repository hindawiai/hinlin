<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2004-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 * Copyright (c) 2016-2017 Erik Stromdahl <erik.stromdahl@gmail.com>
 */

#अगर_अघोषित _USB_H_
#घोषणा _USB_H_

/* स्थिरants */
#घोषणा TX_URB_COUNT               32
#घोषणा RX_URB_COUNT               32
#घोषणा ATH10K_USB_RX_BUFFER_SIZE  4096

#घोषणा ATH10K_USB_PIPE_INVALID ATH10K_USB_PIPE_MAX

/* USB endpoपूर्णांक definitions */
#घोषणा ATH10K_USB_EP_ADDR_APP_CTRL_IN          0x81
#घोषणा ATH10K_USB_EP_ADDR_APP_DATA_IN          0x82
#घोषणा ATH10K_USB_EP_ADDR_APP_DATA2_IN         0x83
#घोषणा ATH10K_USB_EP_ADDR_APP_INT_IN           0x84

#घोषणा ATH10K_USB_EP_ADDR_APP_CTRL_OUT         0x01
#घोषणा ATH10K_USB_EP_ADDR_APP_DATA_LP_OUT      0x02
#घोषणा ATH10K_USB_EP_ADDR_APP_DATA_MP_OUT      0x03
#घोषणा ATH10K_USB_EP_ADDR_APP_DATA_HP_OUT      0x04

/* diagnostic command defnitions */
#घोषणा ATH10K_USB_CONTROL_REQ_SEND_BMI_CMD        1
#घोषणा ATH10K_USB_CONTROL_REQ_RECV_BMI_RESP       2
#घोषणा ATH10K_USB_CONTROL_REQ_DIAG_CMD            3
#घोषणा ATH10K_USB_CONTROL_REQ_DIAG_RESP           4

#घोषणा ATH10K_USB_CTRL_DIAG_CC_READ               0
#घोषणा ATH10K_USB_CTRL_DIAG_CC_WRITE              1

#घोषणा ATH10K_USB_IS_BULK_EP(attr) (((attr) & 3) == 0x02)
#घोषणा ATH10K_USB_IS_INT_EP(attr)  (((attr) & 3) == 0x03)
#घोषणा ATH10K_USB_IS_ISOC_EP(attr) (((attr) & 3) == 0x01)
#घोषणा ATH10K_USB_IS_सूची_IN(addr)  ((addr) & 0x80)

काष्ठा ath10k_usb_ctrl_diag_cmd_ग_लिखो अणु
	__le32 cmd;
	__le32 address;
	__le32 value;
	__le32 padding;
पूर्ण __packed;

काष्ठा ath10k_usb_ctrl_diag_cmd_पढ़ो अणु
	__le32 cmd;
	__le32 address;
पूर्ण __packed;

काष्ठा ath10k_usb_ctrl_diag_resp_पढ़ो अणु
	u8 value[4];
पूर्ण __packed;

/* tx/rx pipes क्रम usb */
क्रमागत ath10k_usb_pipe_id अणु
	ATH10K_USB_PIPE_TX_CTRL = 0,
	ATH10K_USB_PIPE_TX_DATA_LP,
	ATH10K_USB_PIPE_TX_DATA_MP,
	ATH10K_USB_PIPE_TX_DATA_HP,
	ATH10K_USB_PIPE_RX_CTRL,
	ATH10K_USB_PIPE_RX_DATA,
	ATH10K_USB_PIPE_RX_DATA2,
	ATH10K_USB_PIPE_RX_INT,
	ATH10K_USB_PIPE_MAX
पूर्ण;

काष्ठा ath10k_usb_pipe अणु
	काष्ठा list_head urb_list_head;
	काष्ठा usb_anchor urb_submitted;
	u32 urb_alloc;
	u32 urb_cnt;
	u32 urb_cnt_thresh;
	अचिन्हित पूर्णांक usb_pipe_handle;
	u32 flags;
	u8 ep_address;
	u8 logical_pipe_num;
	काष्ठा ath10k_usb *ar_usb;
	u16 max_packet_size;
	काष्ठा work_काष्ठा io_complete_work;
	काष्ठा sk_buff_head io_comp_queue;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc;
पूर्ण;

#घोषणा ATH10K_USB_PIPE_FLAG_TX BIT(0)

/* usb device object */
काष्ठा ath10k_usb अणु
	/* protects pipe->urb_list_head and  pipe->urb_cnt */
	spinlock_t cs_lock;

	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	काष्ठा ath10k_usb_pipe pipes[ATH10K_USB_PIPE_MAX];
	u8 *diag_cmd_buffer;
	u8 *diag_resp_buffer;
	काष्ठा ath10k *ar;
पूर्ण;

/* usb urb object */
काष्ठा ath10k_urb_context अणु
	काष्ठा list_head link;
	काष्ठा ath10k_usb_pipe *pipe;
	काष्ठा sk_buff *skb;
	काष्ठा ath10k *ar;
पूर्ण;

अटल अंतरभूत काष्ठा ath10k_usb *ath10k_usb_priv(काष्ठा ath10k *ar)
अणु
	वापस (काष्ठा ath10k_usb *)ar->drv_priv;
पूर्ण

#पूर्ण_अगर
