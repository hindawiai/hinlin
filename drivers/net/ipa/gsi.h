<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2021 Linaro Ltd.
 */
#अगर_अघोषित _GSI_H_
#घोषणा _GSI_H_

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/completion.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/netdevice.h>

#समावेश "ipa_version.h"

/* Maximum number of channels and event rings supported by the driver */
#घोषणा GSI_CHANNEL_COUNT_MAX	23
#घोषणा GSI_EVT_RING_COUNT_MAX	20

/* Maximum TLV FIFO size क्रम a channel; 64 here is arbitrary (and high) */
#घोषणा GSI_TLV_MAX		64

काष्ठा device;
काष्ठा scatterlist;
काष्ठा platक्रमm_device;

काष्ठा gsi;
काष्ठा gsi_trans;
काष्ठा gsi_channel_data;
काष्ठा ipa_gsi_endpoपूर्णांक_data;

/* Execution environment IDs */
क्रमागत gsi_ee_id अणु
	GSI_EE_AP				= 0x0,
	GSI_EE_MODEM				= 0x1,
	GSI_EE_UC				= 0x2,
	GSI_EE_TZ				= 0x3,
पूर्ण;

काष्ठा gsi_ring अणु
	व्योम *virt;			/* ring array base address */
	dma_addr_t addr;		/* primarily low 32 bits used */
	u32 count;			/* number of elements in ring */

	/* The ring index value indicates the next "open" entry in the ring.
	 *
	 * A channel ring consists of TRE entries filled by the AP and passed
	 * to the hardware क्रम processing.  For a channel ring, the ring index
	 * identअगरies the next unused entry to be filled by the AP.
	 *
	 * An event ring consists of event काष्ठाures filled by the hardware
	 * and passed to the AP.  For event rings, the ring index identअगरies
	 * the next ring entry that is not known to have been filled by the
	 * hardware.
	 */
	u32 index;
पूर्ण;

/* Transactions use several resources that can be allocated dynamically
 * but taken from a fixed-size pool.  The number of elements required क्रम
 * the pool is limited by the total number of TREs that can be outstanding.
 *
 * If sufficient TREs are available to reserve क्रम a transaction,
 * allocation from these pools is guaranteed to succeed.  Furthermore,
 * these resources are implicitly मुक्तd whenever the TREs in the
 * transaction they're associated with are released.
 *
 * The result of a pool allocation of multiple elements is always
 * contiguous.
 */
काष्ठा gsi_trans_pool अणु
	व्योम *base;			/* base address of element pool */
	u32 count;			/* # elements in the pool */
	u32 मुक्त;			/* next मुक्त element in pool (modulo) */
	u32 size;			/* size (bytes) of an element */
	u32 max_alloc;			/* max allocation request */
	dma_addr_t addr;		/* DMA address अगर DMA pool (or 0) */
पूर्ण;

काष्ठा gsi_trans_info अणु
	atomic_t tre_avail;		/* TREs available क्रम allocation */
	काष्ठा gsi_trans_pool pool;	/* transaction pool */
	काष्ठा gsi_trans_pool sg_pool;	/* scatterlist pool */
	काष्ठा gsi_trans_pool cmd_pool;	/* command payload DMA pool */
	काष्ठा gsi_trans_pool info_pool;/* command inक्रमmation pool */
	काष्ठा gsi_trans **map;		/* TRE -> transaction map */

	spinlock_t spinlock;		/* protects updates to the lists */
	काष्ठा list_head alloc;		/* allocated, not committed */
	काष्ठा list_head pending;	/* committed, aरुकोing completion */
	काष्ठा list_head complete;	/* completed, aरुकोing poll */
	काष्ठा list_head polled;	/* वापसed by gsi_channel_poll_one() */
पूर्ण;

/* Hardware values signअगरying the state of a channel */
क्रमागत gsi_channel_state अणु
	GSI_CHANNEL_STATE_NOT_ALLOCATED		= 0x0,
	GSI_CHANNEL_STATE_ALLOCATED		= 0x1,
	GSI_CHANNEL_STATE_STARTED		= 0x2,
	GSI_CHANNEL_STATE_STOPPED		= 0x3,
	GSI_CHANNEL_STATE_STOP_IN_PROC		= 0x4,
	GSI_CHANNEL_STATE_ERROR			= 0xf,
पूर्ण;

/* We only care about channels between IPA and AP */
काष्ठा gsi_channel अणु
	काष्ठा gsi *gsi;
	bool toward_ipa;
	bool command;			/* AP command TX channel or not */

	u8 tlv_count;			/* # entries in TLV FIFO */
	u16 tre_count;
	u16 event_count;

	काष्ठा completion completion;	/* संकेतs channel command completion */

	काष्ठा gsi_ring tre_ring;
	u32 evt_ring_id;

	u64 byte_count;			/* total # bytes transferred */
	u64 trans_count;		/* total # transactions */
	/* The following counts are used only क्रम TX endpoपूर्णांकs */
	u64 queued_byte_count;		/* last reported queued byte count */
	u64 queued_trans_count;		/* ...and queued trans count */
	u64 compl_byte_count;		/* last reported completed byte count */
	u64 compl_trans_count;		/* ...and completed trans count */

	काष्ठा gsi_trans_info trans_info;

	काष्ठा napi_काष्ठा napi;
पूर्ण;

/* Hardware values signअगरying the state of an event ring */
क्रमागत gsi_evt_ring_state अणु
	GSI_EVT_RING_STATE_NOT_ALLOCATED	= 0x0,
	GSI_EVT_RING_STATE_ALLOCATED		= 0x1,
	GSI_EVT_RING_STATE_ERROR		= 0xf,
पूर्ण;

काष्ठा gsi_evt_ring अणु
	काष्ठा gsi_channel *channel;
	काष्ठा completion completion;	/* संकेतs event ring state changes */
	काष्ठा gsi_ring ring;
पूर्ण;

काष्ठा gsi अणु
	काष्ठा device *dev;		/* Same as IPA device */
	क्रमागत ipa_version version;
	काष्ठा net_device dummy_dev;	/* needed क्रम NAPI */
	व्योम __iomem *virt_raw;		/* I/O mapped address range */
	व्योम __iomem *virt;		/* Adjusted क्रम most रेजिस्टरs */
	u32 irq;
	u32 channel_count;
	u32 evt_ring_count;
	काष्ठा gsi_channel channel[GSI_CHANNEL_COUNT_MAX];
	काष्ठा gsi_evt_ring evt_ring[GSI_EVT_RING_COUNT_MAX];
	u32 event_biपंचांगap;		/* allocated event rings */
	u32 modem_channel_biपंचांगap;	/* modem channels to allocate */
	u32 type_enabled_biपंचांगap;	/* GSI IRQ types enabled */
	u32 ieob_enabled_biपंचांगap;	/* IEOB IRQ enabled (event rings) */
	काष्ठा completion completion;	/* क्रम global EE commands */
	पूर्णांक result;			/* Negative त्रुटि_सं (generic commands) */
	काष्ठा mutex mutex;		/* protects commands, programming */
पूर्ण;

/**
 * gsi_setup() - Set up the GSI subप्रणाली
 * @gsi:	Address of GSI काष्ठाure embedded in an IPA काष्ठाure
 *
 * Return:	0 अगर successful, or a negative error code
 *
 * Perक्रमms initialization that must रुको until the GSI hardware is
 * पढ़ोy (including firmware loaded).
 */
पूर्णांक gsi_setup(काष्ठा gsi *gsi);

/**
 * gsi_tearकरोwn() - Tear करोwn GSI subप्रणाली
 * @gsi:	GSI address previously passed to a successful gsi_setup() call
 */
व्योम gsi_tearकरोwn(काष्ठा gsi *gsi);

/**
 * gsi_channel_tre_max() - Channel maximum number of in-flight TREs
 * @gsi:	GSI poपूर्णांकer
 * @channel_id:	Channel whose limit is to be वापसed
 *
 * Return:	 The maximum number of TREs oustanding on the channel
 */
u32 gsi_channel_tre_max(काष्ठा gsi *gsi, u32 channel_id);

/**
 * gsi_channel_trans_tre_max() - Maximum TREs in a single transaction
 * @gsi:	GSI poपूर्णांकer
 * @channel_id:	Channel whose limit is to be वापसed
 *
 * Return:	 The maximum TRE count per transaction on the channel
 */
u32 gsi_channel_trans_tre_max(काष्ठा gsi *gsi, u32 channel_id);

/**
 * gsi_channel_start() - Start an allocated GSI channel
 * @gsi:	GSI poपूर्णांकer
 * @channel_id:	Channel to start
 *
 * Return:	0 अगर successful, or a negative error code
 */
पूर्णांक gsi_channel_start(काष्ठा gsi *gsi, u32 channel_id);

/**
 * gsi_channel_stop() - Stop a started GSI channel
 * @gsi:	GSI poपूर्णांकer वापसed by gsi_setup()
 * @channel_id:	Channel to stop
 *
 * Return:	0 अगर successful, or a negative error code
 */
पूर्णांक gsi_channel_stop(काष्ठा gsi *gsi, u32 channel_id);

/**
 * gsi_channel_reset() - Reset an allocated GSI channel
 * @gsi:	GSI poपूर्णांकer
 * @channel_id:	Channel to be reset
 * @करोorbell:	Whether to (possibly) enable the करोorbell engine
 *
 * Reset a channel and reconfigure it.  The @करोorbell flag indicates
 * that the करोorbell engine should be enabled अगर needed.
 *
 * GSI hardware relinquishes ownership of all pending receive buffer
 * transactions and they will complete with their cancelled flag set.
 */
व्योम gsi_channel_reset(काष्ठा gsi *gsi, u32 channel_id, bool करोorbell);

पूर्णांक gsi_channel_suspend(काष्ठा gsi *gsi, u32 channel_id, bool stop);
पूर्णांक gsi_channel_resume(काष्ठा gsi *gsi, u32 channel_id, bool start);

/**
 * gsi_init() - Initialize the GSI subप्रणाली
 * @gsi:	Address of GSI काष्ठाure embedded in an IPA काष्ठाure
 * @pdev:	IPA platक्रमm device
 * @version:	IPA hardware version (implies GSI version)
 * @count:	Number of entries in the configuration data array
 * @data:	Endpoपूर्णांक and channel configuration data
 *
 * Return:	0 अगर successful, or a negative error code
 *
 * Early stage initialization of the GSI subप्रणाली, perक्रमming tasks
 * that can be करोne beक्रमe the GSI hardware is पढ़ोy to use.
 */
पूर्णांक gsi_init(काष्ठा gsi *gsi, काष्ठा platक्रमm_device *pdev,
	     क्रमागत ipa_version version, u32 count,
	     स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *data);

/**
 * gsi_निकास() - Exit the GSI subप्रणाली
 * @gsi:	GSI address previously passed to a successful gsi_init() call
 */
व्योम gsi_निकास(काष्ठा gsi *gsi);

#पूर्ण_अगर /* _GSI_H_ */
