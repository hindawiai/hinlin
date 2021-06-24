<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2004-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 * Copyright (c) 2016-2017 Erik Stromdahl <erik.stromdahl@gmail.com>
 */

#अगर_अघोषित _SDIO_H_
#घोषणा _SDIO_H_

#घोषणा ATH10K_HIF_MBOX_BLOCK_SIZE              256

#घोषणा ATH10K_SDIO_MAX_BUFFER_SIZE             4096 /*Unsure of this स्थिरant*/

/* Mailbox address in SDIO address space */
#घोषणा ATH10K_HIF_MBOX_BASE_ADDR               0x1000
#घोषणा ATH10K_HIF_MBOX_WIDTH                   0x800

#घोषणा ATH10K_HIF_MBOX_TOT_WIDTH \
	(ATH10K_HIF_MBOX_NUM_MAX * ATH10K_HIF_MBOX_WIDTH)

#घोषणा ATH10K_HIF_MBOX0_EXT_BASE_ADDR          0x5000
#घोषणा ATH10K_HIF_MBOX0_EXT_WIDTH              (36 * 1024)
#घोषणा ATH10K_HIF_MBOX0_EXT_WIDTH_ROME_2_0     (56 * 1024)
#घोषणा ATH10K_HIF_MBOX1_EXT_WIDTH              (36 * 1024)
#घोषणा ATH10K_HIF_MBOX_DUMMY_SPACE_SIZE        (2 * 1024)

#घोषणा ATH10K_HTC_MBOX_MAX_PAYLOAD_LENGTH \
	(ATH10K_SDIO_MAX_BUFFER_SIZE - माप(काष्ठा ath10k_htc_hdr))

#घोषणा ATH10K_HIF_MBOX_NUM_MAX                 4
#घोषणा ATH10K_SDIO_BUS_REQUEST_MAX_NUM         1024

#घोषणा ATH10K_SDIO_HIF_COMMUNICATION_TIMEOUT_HZ (100 * HZ)

/* HTC runs over mailbox 0 */
#घोषणा ATH10K_HTC_MAILBOX                      0
#घोषणा ATH10K_HTC_MAILBOX_MASK                 BIT(ATH10K_HTC_MAILBOX)

/* GMBOX addresses */
#घोषणा ATH10K_HIF_GMBOX_BASE_ADDR              0x7000
#घोषणा ATH10K_HIF_GMBOX_WIDTH                  0x4000

/* Modअगरied versions of the sdपन.स macros.
 * The macros in sdपन.स can't be used easily with the FIELD_अणुPREP|GETपूर्ण
 * macros in bitfield.h, so we define our own macros here.
 */
#घोषणा ATH10K_SDIO_DRIVE_DTSX_MASK \
	(SDIO_DRIVE_DTSx_MASK << SDIO_DRIVE_DTSx_SHIFT)

#घोषणा ATH10K_SDIO_DRIVE_DTSX_TYPE_B           0
#घोषणा ATH10K_SDIO_DRIVE_DTSX_TYPE_A           1
#घोषणा ATH10K_SDIO_DRIVE_DTSX_TYPE_C           2
#घोषणा ATH10K_SDIO_DRIVE_DTSX_TYPE_D           3

/* SDIO CCCR रेजिस्टर definitions */
#घोषणा CCCR_SDIO_IRQ_MODE_REG                  0xF0
#घोषणा CCCR_SDIO_IRQ_MODE_REG_SDIO3            0x16

#घोषणा CCCR_SDIO_DRIVER_STRENGTH_ENABLE_ADDR   0xF2

#घोषणा CCCR_SDIO_DRIVER_STRENGTH_ENABLE_A      0x02
#घोषणा CCCR_SDIO_DRIVER_STRENGTH_ENABLE_C      0x04
#घोषणा CCCR_SDIO_DRIVER_STRENGTH_ENABLE_D      0x08

#घोषणा CCCR_SDIO_ASYNC_INT_DELAY_ADDRESS       0xF0
#घोषणा CCCR_SDIO_ASYNC_INT_DELAY_MASK          0xC0

/* mode to enable special 4-bit पूर्णांकerrupt निश्चितion without घड़ी */
#घोषणा SDIO_IRQ_MODE_ASYNC_4BIT_IRQ            BIT(0)
#घोषणा SDIO_IRQ_MODE_ASYNC_4BIT_IRQ_SDIO3      BIT(1)

#घोषणा ATH10K_SDIO_TARGET_DEBUG_INTR_MASK      0x01

/* The theoretical maximum number of RX messages that can be fetched
 * from the mbox पूर्णांकerrupt handler in one loop is derived in the following
 * way:
 *
 * Let's assume that each packet in a bundle of the maximum bundle size
 * (HTC_HOST_MAX_MSG_PER_RX_BUNDLE) has the HTC header bundle count set
 * to the maximum value (HTC_HOST_MAX_MSG_PER_RX_BUNDLE).
 *
 * in this हाल the driver must allocate
 * (HTC_HOST_MAX_MSG_PER_RX_BUNDLE * 2) skb's.
 */
#घोषणा ATH10K_SDIO_MAX_RX_MSGS \
	(HTC_HOST_MAX_MSG_PER_RX_BUNDLE * 2)

#घोषणा ATH10K_FIFO_TIMEOUT_AND_CHIP_CONTROL   0x00000868u
#घोषणा ATH10K_FIFO_TIMEOUT_AND_CHIP_CONTROL_DISABLE_SLEEP_OFF 0xFFFEFFFF
#घोषणा ATH10K_FIFO_TIMEOUT_AND_CHIP_CONTROL_DISABLE_SLEEP_ON 0x10000

क्रमागत sdio_mbox_state अणु
	SDIO_MBOX_UNKNOWN_STATE = 0,
	SDIO_MBOX_REQUEST_TO_SLEEP_STATE = 1,
	SDIO_MBOX_SLEEP_STATE = 2,
	SDIO_MBOX_AWAKE_STATE = 3,
पूर्ण;

#घोषणा ATH10K_CIS_READ_WAIT_4_RTC_CYCLE_IN_US	125
#घोषणा ATH10K_CIS_RTC_STATE_ADDR		0x1138
#घोषणा ATH10K_CIS_RTC_STATE_ON			0x01
#घोषणा ATH10K_CIS_XTAL_SETTLE_DURATION_IN_US	1500
#घोषणा ATH10K_CIS_READ_RETRY			10
#घोषणा ATH10K_MIN_SLEEP_INACTIVITY_TIME_MS	50

/* TODO: हटाओ this and use skb->cb instead, much cleaner approach */
काष्ठा ath10k_sdio_bus_request अणु
	काष्ठा list_head list;

	/* sdio address */
	u32 address;

	काष्ठा sk_buff *skb;
	क्रमागत ath10k_htc_ep_id eid;
	पूर्णांक status;
	/* Specअगरies अगर the current request is an HTC message.
	 * If not, the eid is not applicable an the TX completion handler
	 * associated with the endpoपूर्णांक will not be invoked.
	 */
	bool htc_msg;
	/* Completion that (अगर set) will be invoked क्रम non HTC requests
	 * (htc_msg == false) when the request has been processed.
	 */
	काष्ठा completion *comp;
पूर्ण;

काष्ठा ath10k_sdio_rx_data अणु
	काष्ठा sk_buff *skb;
	माप_प्रकार alloc_len;
	माप_प्रकार act_len;
	क्रमागत ath10k_htc_ep_id eid;
	bool part_of_bundle;
	bool last_in_bundle;
	bool trailer_only;
पूर्ण;

काष्ठा ath10k_sdio_irq_proc_regs अणु
	u8 host_पूर्णांक_status;
	u8 cpu_पूर्णांक_status;
	u8 error_पूर्णांक_status;
	u8 counter_पूर्णांक_status;
	u8 mbox_frame;
	u8 rx_lookahead_valid;
	u8 host_पूर्णांक_status2;
	u8 gmbox_rx_avail;
	__le32 rx_lookahead[2 * ATH10K_HIF_MBOX_NUM_MAX];
	__le32 पूर्णांक_status_enable;
पूर्ण;

काष्ठा ath10k_sdio_irq_enable_regs अणु
	u8 पूर्णांक_status_en;
	u8 cpu_पूर्णांक_status_en;
	u8 err_पूर्णांक_status_en;
	u8 cntr_पूर्णांक_status_en;
पूर्ण;

काष्ठा ath10k_sdio_irq_data अणु
	/* protects irq_proc_reg and irq_en_reg below.
	 * We use a mutex here and not a spinlock since we will have the
	 * mutex locked जबतक calling the sdio_स_नकल_ functions.
	 * These function require non atomic context, and hence, spinlocks
	 * can be held जबतक calling these functions.
	 */
	काष्ठा mutex mtx;
	काष्ठा ath10k_sdio_irq_proc_regs *irq_proc_reg;
	काष्ठा ath10k_sdio_irq_enable_regs *irq_en_reg;
पूर्ण;

काष्ठा ath10k_mbox_ext_info अणु
	u32 htc_ext_addr;
	u32 htc_ext_sz;
पूर्ण;

काष्ठा ath10k_mbox_info अणु
	u32 htc_addr;
	काष्ठा ath10k_mbox_ext_info ext_info[2];
	u32 block_size;
	u32 block_mask;
	u32 gmbox_addr;
	u32 gmbox_sz;
पूर्ण;

काष्ठा ath10k_sdio अणु
	काष्ठा sdio_func *func;

	काष्ठा ath10k_mbox_info mbox_info;
	bool swap_mbox;
	u32 mbox_addr[ATH10K_HTC_EP_COUNT];
	u32 mbox_size[ATH10K_HTC_EP_COUNT];

	/* available bus requests */
	काष्ठा ath10k_sdio_bus_request bus_req[ATH10K_SDIO_BUS_REQUEST_MAX_NUM];
	/* मुक्त list of bus requests */
	काष्ठा list_head bus_req_मुक्तq;

	काष्ठा sk_buff_head rx_head;

	/* protects access to bus_req_मुक्तq */
	spinlock_t lock;

	काष्ठा ath10k_sdio_rx_data rx_pkts[ATH10K_SDIO_MAX_RX_MSGS];
	माप_प्रकार n_rx_pkts;

	काष्ठा ath10k *ar;
	काष्ठा ath10k_sdio_irq_data irq_data;

	/* temporary buffer क्रम sdio पढ़ो.
	 * It is allocated when probe, and used क्रम receive bundled packets,
	 * the पढ़ो क्रम bundled packets is not parallel, so it करोes not need
	 * रक्षित.
	 */
	u8 *vsg_buffer;

	/* temporary buffer क्रम BMI requests */
	u8 *bmi_buf;

	bool is_disabled;

	काष्ठा workqueue_काष्ठा *workqueue;
	काष्ठा work_काष्ठा wr_async_work;
	काष्ठा list_head wr_asyncq;
	/* protects access to wr_asyncq */
	spinlock_t wr_async_lock;

	काष्ठा work_काष्ठा async_work_rx;
	काष्ठा समयr_list sleep_समयr;
	क्रमागत sdio_mbox_state mbox_state;
पूर्ण;

अटल अंतरभूत काष्ठा ath10k_sdio *ath10k_sdio_priv(काष्ठा ath10k *ar)
अणु
	वापस (काष्ठा ath10k_sdio *)ar->drv_priv;
पूर्ण

#पूर्ण_अगर
