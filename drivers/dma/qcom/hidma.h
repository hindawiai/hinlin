<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Qualcomm Technologies HIDMA data काष्ठाures
 *
 * Copyright (c) 2014-2016, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित QCOM_HIDMA_H
#घोषणा QCOM_HIDMA_H

#समावेश <linux/kfअगरo.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dmaengine.h>

#घोषणा HIDMA_TRE_SIZE			32 /* each TRE is 32 bytes  */
#घोषणा HIDMA_TRE_CFG_IDX		0
#घोषणा HIDMA_TRE_LEN_IDX		1
#घोषणा HIDMA_TRE_SRC_LOW_IDX		2
#घोषणा HIDMA_TRE_SRC_HI_IDX		3
#घोषणा HIDMA_TRE_DEST_LOW_IDX		4
#घोषणा HIDMA_TRE_DEST_HI_IDX		5

क्रमागत tre_type अणु
	HIDMA_TRE_MEMCPY = 3,
	HIDMA_TRE_MEMSET = 4,
पूर्ण;

काष्ठा hidma_tre अणु
	atomic_t allocated;		/* अगर this channel is allocated	    */
	bool queued;			/* flag whether this is pending     */
	u16 status;			/* status			    */
	u32 idx;			/* index of the tre		    */
	u32 dma_sig;			/* signature of the tre		    */
	स्थिर अक्षर *dev_name;		/* name of the device		    */
	व्योम (*callback)(व्योम *data);	/* requester callback		    */
	व्योम *data;			/* Data associated with this channel*/
	काष्ठा hidma_lldev *lldev;	/* lldma device poपूर्णांकer		    */
	u32 tre_local[HIDMA_TRE_SIZE / माप(u32) + 1]; /* TRE local copy  */
	u32 tre_index;			/* the offset where this was written*/
	u32 पूर्णांक_flags;			/* पूर्णांकerrupt flags		    */
	u8 err_info;			/* error record in this transfer    */
	u8 err_code;			/* completion code		    */
पूर्ण;

काष्ठा hidma_lldev अणु
	bool msi_support;		/* flag indicating MSI support    */
	bool initialized;		/* initialized flag               */
	u8 trch_state;			/* trch_state of the device	  */
	u8 evch_state;			/* evch_state of the device	  */
	u8 chidx;			/* channel index in the core	  */
	u32 nr_tres;			/* max number of configs          */
	spinlock_t lock;		/* reentrancy                     */
	काष्ठा hidma_tre *trepool;	/* trepool of user configs */
	काष्ठा device *dev;		/* device			  */
	व्योम __iomem *trca;		/* Transfer Channel address       */
	व्योम __iomem *evca;		/* Event Channel address          */
	काष्ठा hidma_tre
		**pending_tre_list;	/* Poपूर्णांकers to pending TREs	  */
	atomic_t pending_tre_count;	/* Number of TREs pending	  */

	व्योम *tre_ring;			/* TRE ring			  */
	dma_addr_t tre_dma;		/* TRE ring to be shared with HW  */
	u32 tre_ring_size;		/* Byte size of the ring	  */
	u32 tre_processed_off;		/* last processed TRE		  */

	व्योम *evre_ring;		/* EVRE ring			   */
	dma_addr_t evre_dma;		/* EVRE ring to be shared with HW  */
	u32 evre_ring_size;		/* Byte size of the ring	   */
	u32 evre_processed_off;		/* last processed EVRE		   */

	u32 tre_ग_लिखो_offset;           /* TRE ग_लिखो location              */
	काष्ठा tasklet_काष्ठा task;	/* task delivering notअगरications   */
	DECLARE_KFIFO_PTR(hanकरोff_fअगरo,
		काष्ठा hidma_tre *);    /* pending TREs FIFO               */
पूर्ण;

काष्ठा hidma_desc अणु
	काष्ठा dma_async_tx_descriptor	desc;
	/* link list node क्रम this channel*/
	काष्ठा list_head		node;
	u32				tre_ch;
पूर्ण;

काष्ठा hidma_chan अणु
	bool				छोड़ोd;
	bool				allocated;
	अक्षर				dbg_name[16];
	u32				dma_sig;
	dma_cookie_t			last_success;

	/*
	 * active descriptor on this channel
	 * It is used by the DMA complete notअगरication to
	 * locate the descriptor that initiated the transfer.
	 */
	काष्ठा hidma_dev		*dmadev;
	काष्ठा hidma_desc		*running;

	काष्ठा dma_chan			chan;
	काष्ठा list_head		मुक्त;
	काष्ठा list_head		prepared;
	काष्ठा list_head		queued;
	काष्ठा list_head		active;
	काष्ठा list_head		completed;

	/* Lock क्रम this काष्ठाure */
	spinlock_t			lock;
पूर्ण;

काष्ठा hidma_dev अणु
	पूर्णांक				irq;
	पूर्णांक				chidx;
	u32				nr_descriptors;
	पूर्णांक				msi_virqbase;

	काष्ठा hidma_lldev		*lldev;
	व्योम				__iomem *dev_trca;
	काष्ठा resource			*trca_resource;
	व्योम				__iomem *dev_evca;
	काष्ठा resource			*evca_resource;

	/* used to protect the pending channel list*/
	spinlock_t			lock;
	काष्ठा dma_device		ddev;

	काष्ठा dentry			*debugfs;

	/* sysfs entry क्रम the channel id */
	काष्ठा device_attribute		*chid_attrs;

	/* Task delivering issue_pending */
	काष्ठा tasklet_काष्ठा		task;
पूर्ण;

पूर्णांक hidma_ll_request(काष्ठा hidma_lldev *llhndl, u32 dev_id,
			स्थिर अक्षर *dev_name,
			व्योम (*callback)(व्योम *data), व्योम *data, u32 *tre_ch);

व्योम hidma_ll_मुक्त(काष्ठा hidma_lldev *llhndl, u32 tre_ch);
क्रमागत dma_status hidma_ll_status(काष्ठा hidma_lldev *llhndl, u32 tre_ch);
bool hidma_ll_isenabled(काष्ठा hidma_lldev *llhndl);
व्योम hidma_ll_queue_request(काष्ठा hidma_lldev *llhndl, u32 tre_ch);
व्योम hidma_ll_start(काष्ठा hidma_lldev *llhndl);
पूर्णांक hidma_ll_disable(काष्ठा hidma_lldev *lldev);
पूर्णांक hidma_ll_enable(काष्ठा hidma_lldev *llhndl);
व्योम hidma_ll_set_transfer_params(काष्ठा hidma_lldev *llhndl, u32 tre_ch,
	dma_addr_t src, dma_addr_t dest, u32 len, u32 flags, u32 txntype);
व्योम hidma_ll_setup_irq(काष्ठा hidma_lldev *lldev, bool msi);
पूर्णांक hidma_ll_setup(काष्ठा hidma_lldev *lldev);
काष्ठा hidma_lldev *hidma_ll_init(काष्ठा device *dev, u32 max_channels,
			व्योम __iomem *trca, व्योम __iomem *evca,
			u8 chidx);
पूर्णांक hidma_ll_uninit(काष्ठा hidma_lldev *llhndl);
irqवापस_t hidma_ll_पूर्णांकhandler(पूर्णांक irq, व्योम *arg);
irqवापस_t hidma_ll_पूर्णांकhandler_msi(पूर्णांक irq, व्योम *arg, पूर्णांक cause);
व्योम hidma_cleanup_pending_tre(काष्ठा hidma_lldev *llhndl, u8 err_info,
				u8 err_code);
व्योम hidma_debug_init(काष्ठा hidma_dev *dmadev);
व्योम hidma_debug_uninit(काष्ठा hidma_dev *dmadev);
#पूर्ण_अगर
