<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2004 - 2010 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00
	Abstract: rt2x00 queue dataकाष्ठाures and routines
 */

#अगर_अघोषित RT2X00QUEUE_H
#घोषणा RT2X00QUEUE_H

#समावेश <linux/prefetch.h>

/**
 * DOC: Entry frame size
 *
 * Ralink PCI devices demand the Frame size to be a multiple of 128 bytes,
 * क्रम USB devices this restriction करोes not apply, but the value of
 * 2432 makes sense since it is big enough to contain the maximum fragment
 * size according to the ieee802.11 specs.
 * The aggregation size depends on support from the driver, but should
 * be something around 3840 bytes.
 */
#घोषणा DATA_FRAME_SIZE		2432
#घोषणा MGMT_FRAME_SIZE		256
#घोषणा AGGREGATION_SIZE	3840

/**
 * क्रमागत data_queue_qid: Queue identअगरication
 *
 * @QID_AC_VO: AC VO queue
 * @QID_AC_VI: AC VI queue
 * @QID_AC_BE: AC BE queue
 * @QID_AC_BK: AC BK queue
 * @QID_HCCA: HCCA queue
 * @QID_MGMT: MGMT queue (prio queue)
 * @QID_RX: RX queue
 * @QID_OTHER: None of the above (करोn't use, only present क्रम completeness)
 * @QID_BEACON: Beacon queue (value unspecअगरied, करोn't send it to device)
 * @QID_ATIM: Atim queue (value unspecअगरied, करोn't send it to device)
 */
क्रमागत data_queue_qid अणु
	QID_AC_VO = 0,
	QID_AC_VI = 1,
	QID_AC_BE = 2,
	QID_AC_BK = 3,
	QID_HCCA = 4,
	QID_MGMT = 13,
	QID_RX = 14,
	QID_OTHER = 15,
	QID_BEACON,
	QID_ATIM,
पूर्ण;

/**
 * क्रमागत skb_frame_desc_flags: Flags क्रम &काष्ठा skb_frame_desc
 *
 * @SKBDESC_DMA_MAPPED_RX: &skb_dma field has been mapped क्रम RX
 * @SKBDESC_DMA_MAPPED_TX: &skb_dma field has been mapped क्रम TX
 * @SKBDESC_IV_STRIPPED: Frame contained a IV/EIV provided by
 *	mac80211 but was stripped क्रम processing by the driver.
 * @SKBDESC_NOT_MAC80211: Frame didn't originate from mac80211,
 *	करोn't try to pass it back.
 * @SKBDESC_DESC_IN_SKB: The descriptor is at the start of the
 *	skb, instead of in the desc field.
 */
क्रमागत skb_frame_desc_flags अणु
	SKBDESC_DMA_MAPPED_RX = 1 << 0,
	SKBDESC_DMA_MAPPED_TX = 1 << 1,
	SKBDESC_IV_STRIPPED = 1 << 2,
	SKBDESC_NOT_MAC80211 = 1 << 3,
	SKBDESC_DESC_IN_SKB = 1 << 4,
पूर्ण;

/**
 * काष्ठा skb_frame_desc: Descriptor inक्रमmation क्रम the skb buffer
 *
 * This काष्ठाure is placed over the driver_data array, this means that
 * this काष्ठाure should not exceed the size of that array (40 bytes).
 *
 * @flags: Frame flags, see &क्रमागत skb_frame_desc_flags.
 * @desc_len: Length of the frame descriptor.
 * @tx_rate_idx: the index of the TX rate, used क्रम TX status reporting
 * @tx_rate_flags: the TX rate flags, used क्रम TX status reporting
 * @desc: Poपूर्णांकer to descriptor part of the frame.
 *	Note that this poपूर्णांकer could poपूर्णांक to something outside
 *	of the scope of the skb->data poपूर्णांकer.
 * @iv: IV/EIV data used during encryption/decryption.
 * @skb_dma: (PCI-only) the DMA address associated with the sk buffer.
 * @sta: The station where sk buffer was sent.
 */
काष्ठा skb_frame_desc अणु
	u8 flags;

	u8 desc_len;
	u8 tx_rate_idx;
	u8 tx_rate_flags;

	व्योम *desc;

	__le32 iv[2];

	dma_addr_t skb_dma;
	काष्ठा ieee80211_sta *sta;
पूर्ण;

/**
 * get_skb_frame_desc - Obtain the rt2x00 frame descriptor from a sk_buff.
 * @skb: &काष्ठा sk_buff from where we obtain the &काष्ठा skb_frame_desc
 */
अटल अंतरभूत काष्ठा skb_frame_desc* get_skb_frame_desc(काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा skb_frame_desc) >
		     IEEE80211_TX_INFO_DRIVER_DATA_SIZE);
	वापस (काष्ठा skb_frame_desc *)&IEEE80211_SKB_CB(skb)->driver_data;
पूर्ण

/**
 * क्रमागत rxकरोne_entry_desc_flags: Flags क्रम &काष्ठा rxकरोne_entry_desc
 *
 * @RXDONE_SIGNAL_PLCP: Signal field contains the plcp value.
 * @RXDONE_SIGNAL_BITRATE: Signal field contains the bitrate value.
 * @RXDONE_SIGNAL_MCS: Signal field contains the mcs value.
 * @RXDONE_MY_BSS: Does this frame originate from device's BSS.
 * @RXDONE_CRYPTO_IV: Driver provided IV/EIV data.
 * @RXDONE_CRYPTO_ICV: Driver provided ICV data.
 * @RXDONE_L2PAD: 802.11 payload has been padded to 4-byte boundary.
 */
क्रमागत rxकरोne_entry_desc_flags अणु
	RXDONE_SIGNAL_PLCP = BIT(0),
	RXDONE_SIGNAL_BITRATE = BIT(1),
	RXDONE_SIGNAL_MCS = BIT(2),
	RXDONE_MY_BSS = BIT(3),
	RXDONE_CRYPTO_IV = BIT(4),
	RXDONE_CRYPTO_ICV = BIT(5),
	RXDONE_L2PAD = BIT(6),
पूर्ण;

/**
 * RXDONE_SIGNAL_MASK - Define to mask off all &rxकरोne_entry_desc_flags flags
 * except क्रम the RXDONE_SIGNAL_* flags. This is useful to convert the dev_flags
 * from &rxकरोne_entry_desc to a संकेत value type.
 */
#घोषणा RXDONE_SIGNAL_MASK \
	( RXDONE_SIGNAL_PLCP | RXDONE_SIGNAL_BITRATE | RXDONE_SIGNAL_MCS )

/**
 * काष्ठा rxकरोne_entry_desc: RX Entry descriptor
 *
 * Summary of inक्रमmation that has been पढ़ो from the RX frame descriptor.
 *
 * @बारtamp: RX Timestamp
 * @संकेत: Signal of the received frame.
 * @rssi: RSSI of the received frame.
 * @size: Data size of the received frame.
 * @flags: MAC80211 receive flags (See &क्रमागत mac80211_rx_flags).
 * @dev_flags: Ralink receive flags (See &क्रमागत rxकरोne_entry_desc_flags).
 * @rate_mode: Rate mode (See @क्रमागत rate_modulation).
 * @cipher: Cipher type used during decryption.
 * @cipher_status: Decryption status.
 * @iv: IV/EIV data used during decryption.
 * @icv: ICV data used during decryption.
 */
काष्ठा rxकरोne_entry_desc अणु
	u64 बारtamp;
	पूर्णांक संकेत;
	पूर्णांक rssi;
	पूर्णांक size;
	पूर्णांक flags;
	पूर्णांक dev_flags;
	u16 rate_mode;
	u16 enc_flags;
	क्रमागत mac80211_rx_encoding encoding;
	क्रमागत rate_info_bw bw;
	u8 cipher;
	u8 cipher_status;

	__le32 iv[2];
	__le32 icv;
पूर्ण;

/**
 * क्रमागत txकरोne_entry_desc_flags: Flags क्रम &काष्ठा txकरोne_entry_desc
 *
 * Every txकरोne report has to contain the basic result of the
 * transmission, either &TXDONE_UNKNOWN, &TXDONE_SUCCESS or
 * &TXDONE_FAILURE. The flag &TXDONE_FALLBACK can be used in
 * conjunction with all of these flags but should only be set
 * अगर retires > 0. The flag &TXDONE_EXCESSIVE_RETRY can only be used
 * in conjunction with &TXDONE_FAILURE.
 *
 * @TXDONE_UNKNOWN: Hardware could not determine success of transmission.
 * @TXDONE_SUCCESS: Frame was successfully send
 * @TXDONE_FALLBACK: Hardware used fallback rates क्रम retries
 * @TXDONE_FAILURE: Frame was not successfully send
 * @TXDONE_EXCESSIVE_RETRY: In addition to &TXDONE_FAILURE, the
 *	frame transmission failed due to excessive retries.
 */
क्रमागत txकरोne_entry_desc_flags अणु
	TXDONE_UNKNOWN,
	TXDONE_SUCCESS,
	TXDONE_FALLBACK,
	TXDONE_FAILURE,
	TXDONE_EXCESSIVE_RETRY,
	TXDONE_AMPDU,
	TXDONE_NO_ACK_REQ,
पूर्ण;

/**
 * काष्ठा txकरोne_entry_desc: TX करोne entry descriptor
 *
 * Summary of inक्रमmation that has been पढ़ो from the TX frame descriptor
 * after the device is करोne with transmission.
 *
 * @flags: TX करोne flags (See &क्रमागत txकरोne_entry_desc_flags).
 * @retry: Retry count.
 */
काष्ठा txकरोne_entry_desc अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक retry;
पूर्ण;

/**
 * क्रमागत txentry_desc_flags: Status flags क्रम TX entry descriptor
 *
 * @ENTRY_TXD_RTS_FRAME: This frame is a RTS frame.
 * @ENTRY_TXD_CTS_FRAME: This frame is a CTS-to-self frame.
 * @ENTRY_TXD_GENERATE_SEQ: This frame requires sequence counter.
 * @ENTRY_TXD_FIRST_FRAGMENT: This is the first frame.
 * @ENTRY_TXD_MORE_FRAG: This frame is followed by another fragment.
 * @ENTRY_TXD_REQ_TIMESTAMP: Require बारtamp to be inserted.
 * @ENTRY_TXD_BURST: This frame beदीर्घs to the same burst event.
 * @ENTRY_TXD_ACK: An ACK is required क्रम this frame.
 * @ENTRY_TXD_RETRY_MODE: When set, the दीर्घ retry count is used.
 * @ENTRY_TXD_ENCRYPT: This frame should be encrypted.
 * @ENTRY_TXD_ENCRYPT_PAIRWISE: Use pairwise key table (instead of shared).
 * @ENTRY_TXD_ENCRYPT_IV: Generate IV/EIV in hardware.
 * @ENTRY_TXD_ENCRYPT_MMIC: Generate MIC in hardware.
 * @ENTRY_TXD_HT_AMPDU: This frame is part of an AMPDU.
 * @ENTRY_TXD_HT_BW_40: Use 40MHz Bandwidth.
 * @ENTRY_TXD_HT_SHORT_GI: Use लघु GI.
 * @ENTRY_TXD_HT_MIMO_PS: The receiving STA is in dynamic SM PS mode.
 */
क्रमागत txentry_desc_flags अणु
	ENTRY_TXD_RTS_FRAME,
	ENTRY_TXD_CTS_FRAME,
	ENTRY_TXD_GENERATE_SEQ,
	ENTRY_TXD_FIRST_FRAGMENT,
	ENTRY_TXD_MORE_FRAG,
	ENTRY_TXD_REQ_TIMESTAMP,
	ENTRY_TXD_BURST,
	ENTRY_TXD_ACK,
	ENTRY_TXD_RETRY_MODE,
	ENTRY_TXD_ENCRYPT,
	ENTRY_TXD_ENCRYPT_PAIRWISE,
	ENTRY_TXD_ENCRYPT_IV,
	ENTRY_TXD_ENCRYPT_MMIC,
	ENTRY_TXD_HT_AMPDU,
	ENTRY_TXD_HT_BW_40,
	ENTRY_TXD_HT_SHORT_GI,
	ENTRY_TXD_HT_MIMO_PS,
पूर्ण;

/**
 * काष्ठा txentry_desc: TX Entry descriptor
 *
 * Summary of inक्रमmation क्रम the frame descriptor beक्रमe sending a TX frame.
 *
 * @flags: Descriptor flags (See &क्रमागत queue_entry_flags).
 * @length: Length of the entire frame.
 * @header_length: Length of 802.11 header.
 * @length_high: PLCP length high word.
 * @length_low: PLCP length low word.
 * @संकेत: PLCP संकेत.
 * @service: PLCP service.
 * @msc: MCS.
 * @stbc: Use Space Time Block Coding (only available क्रम MCS rates < 8).
 * @ba_size: Size of the recepients RX reorder buffer - 1.
 * @rate_mode: Rate mode (See @क्रमागत rate_modulation).
 * @mpdu_density: MDPU density.
 * @retry_limit: Max number of retries.
 * @अगरs: IFS value.
 * @txop: IFS value क्रम 11n capable chips.
 * @cipher: Cipher type used क्रम encryption.
 * @key_idx: Key index used क्रम encryption.
 * @iv_offset: Position where IV should be inserted by hardware.
 * @iv_len: Length of IV data.
 */
काष्ठा txentry_desc अणु
	अचिन्हित दीर्घ flags;

	u16 length;
	u16 header_length;

	जोड़ अणु
		काष्ठा अणु
			u16 length_high;
			u16 length_low;
			u16 संकेत;
			u16 service;
			क्रमागत अगरs अगरs;
		पूर्ण plcp;

		काष्ठा अणु
			u16 mcs;
			u8 stbc;
			u8 ba_size;
			u8 mpdu_density;
			क्रमागत txop txop;
			पूर्णांक wcid;
		पूर्ण ht;
	पूर्ण u;

	क्रमागत rate_modulation rate_mode;

	लघु retry_limit;

	क्रमागत cipher cipher;
	u16 key_idx;
	u16 iv_offset;
	u16 iv_len;
पूर्ण;

/**
 * क्रमागत queue_entry_flags: Status flags क्रम queue entry
 *
 * @ENTRY_BCN_ASSIGNED: This entry has been asचिन्हित to an पूर्णांकerface.
 *	As दीर्घ as this bit is set, this entry may only be touched
 *	through the पूर्णांकerface काष्ठाure.
 * @ENTRY_OWNER_DEVICE_DATA: This entry is owned by the device क्रम data
 *	transfer (either TX or RX depending on the queue). The entry should
 *	only be touched after the device has संकेतed it is करोne with it.
 * @ENTRY_DATA_PENDING: This entry contains a valid frame and is रुकोing
 *	क्रम the संकेत to start sending.
 * @ENTRY_DATA_IO_FAILED: Hardware indicated that an IO error occurred
 *	जबतक transferring the data to the hardware. No TX status report will
 *	be expected from the hardware.
 * @ENTRY_DATA_STATUS_PENDING: The entry has been send to the device and
 *	वापसed. It is now रुकोing क्रम the status reporting beक्रमe the
 *	entry can be reused again.
 */
क्रमागत queue_entry_flags अणु
	ENTRY_BCN_ASSIGNED,
	ENTRY_BCN_ENABLED,
	ENTRY_OWNER_DEVICE_DATA,
	ENTRY_DATA_PENDING,
	ENTRY_DATA_IO_FAILED,
	ENTRY_DATA_STATUS_PENDING,
पूर्ण;

/**
 * काष्ठा queue_entry: Entry inside the &काष्ठा data_queue
 *
 * @flags: Entry flags, see &क्रमागत queue_entry_flags.
 * @last_action: Timestamp of last change.
 * @queue: The data queue (&काष्ठा data_queue) to which this entry beदीर्घs.
 * @skb: The buffer which is currently being transmitted (क्रम TX queue),
 *	or used to directly receive data in (क्रम RX queue).
 * @entry_idx: The entry index number.
 * @priv_data: Private data beदीर्घing to this queue entry. The poपूर्णांकer
 *	poपूर्णांकs to data specअगरic to a particular driver and queue type.
 * @status: Device specअगरic status
 */
काष्ठा queue_entry अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ last_action;

	काष्ठा data_queue *queue;

	काष्ठा sk_buff *skb;

	अचिन्हित पूर्णांक entry_idx;

	व्योम *priv_data;
पूर्ण;

/**
 * क्रमागत queue_index: Queue index type
 *
 * @Q_INDEX: Index poपूर्णांकer to the current entry in the queue, अगर this entry is
 *	owned by the hardware then the queue is considered to be full.
 * @Q_INDEX_DMA_DONE: Index poपूर्णांकer क्रम the next entry which will have been
 *	transferred to the hardware.
 * @Q_INDEX_DONE: Index poपूर्णांकer to the next entry which will be completed by
 *	the hardware and क्रम which we need to run the txकरोne handler. If this
 *	entry is not owned by the hardware the queue is considered to be empty.
 * @Q_INDEX_MAX: Keep last, used in &काष्ठा data_queue to determine the size
 *	of the index array.
 */
क्रमागत queue_index अणु
	Q_INDEX,
	Q_INDEX_DMA_DONE,
	Q_INDEX_DONE,
	Q_INDEX_MAX,
पूर्ण;

/**
 * क्रमागत data_queue_flags: Status flags क्रम data queues
 *
 * @QUEUE_STARTED: The queue has been started. Fox RX queues this means the
 *	device might be DMA'ing skbuffers. TX queues will accept skbuffers to
 *	be transmitted and beacon queues will start beaconing the configured
 *	beacons.
 * @QUEUE_PAUSED: The queue has been started but is currently छोड़ोd.
 *	When this bit is set, the queue has been stopped in mac80211,
 *	preventing new frames to be enqueued. However, a few frames
 *	might still appear लघुly after the pausing...
 */
क्रमागत data_queue_flags अणु
	QUEUE_STARTED,
	QUEUE_PAUSED,
पूर्ण;

/**
 * काष्ठा data_queue: Data queue
 *
 * @rt2x00dev: Poपूर्णांकer to मुख्य &काष्ठा rt2x00dev where this queue beदीर्घs to.
 * @entries: Base address of the &काष्ठा queue_entry which are
 *	part of this queue.
 * @qid: The queue identअगरication, see &क्रमागत data_queue_qid.
 * @flags: Entry flags, see &क्रमागत queue_entry_flags.
 * @status_lock: The mutex क्रम protecting the start/stop/flush
 *	handling on this queue.
 * @tx_lock: Spinlock to serialize tx operations on this queue.
 * @index_lock: Spinlock to protect index handling. Whenever @index, @index_करोne or
 *	@index_crypt needs to be changed this lock should be grabbed to prevent
 *	index corruption due to concurrency.
 * @count: Number of frames handled in the queue.
 * @limit: Maximum number of entries in the queue.
 * @threshold: Minimum number of मुक्त entries beक्रमe queue is kicked by क्रमce.
 * @length: Number of frames in queue.
 * @index: Index poपूर्णांकers to entry positions in the queue,
 *	use &क्रमागत queue_index to get a specअगरic index field.
 * @wd_count: watchकरोg counter number of बार entry करोes change
 *      in the queue
 * @wd_idx: index of queue entry saved by watchकरोg
 * @txop: maximum burst समय.
 * @aअगरs: The aअगरs value क्रम outgoing frames (field ignored in RX queue).
 * @cw_min: The cw min value क्रम outgoing frames (field ignored in RX queue).
 * @cw_max: The cw max value क्रम outgoing frames (field ignored in RX queue).
 * @data_size: Maximum data size क्रम the frames in this queue.
 * @desc_size: Hardware descriptor size क्रम the data in this queue.
 * @priv_size: Size of per-queue_entry निजी data.
 * @usb_endpoपूर्णांक: Device endpoपूर्णांक used क्रम communication (USB only)
 * @usb_maxpacket: Max packet size क्रम given endpoपूर्णांक (USB only)
 */
काष्ठा data_queue अणु
	काष्ठा rt2x00_dev *rt2x00dev;
	काष्ठा queue_entry *entries;

	क्रमागत data_queue_qid qid;
	अचिन्हित दीर्घ flags;

	काष्ठा mutex status_lock;
	spinlock_t tx_lock;
	spinlock_t index_lock;

	अचिन्हित पूर्णांक count;
	अचिन्हित लघु limit;
	अचिन्हित लघु threshold;
	अचिन्हित लघु length;
	अचिन्हित लघु index[Q_INDEX_MAX];

	अचिन्हित लघु wd_count;
	अचिन्हित पूर्णांक wd_idx;

	अचिन्हित लघु txop;
	अचिन्हित लघु aअगरs;
	अचिन्हित लघु cw_min;
	अचिन्हित लघु cw_max;

	अचिन्हित लघु data_size;
	अचिन्हित अक्षर  desc_size;
	अचिन्हित अक्षर  winfo_size;
	अचिन्हित लघु priv_size;

	अचिन्हित लघु usb_endpoपूर्णांक;
	अचिन्हित लघु usb_maxpacket;
पूर्ण;

/**
 * queue_end - Return poपूर्णांकer to the last queue (HELPER MACRO).
 * @__dev: Poपूर्णांकer to &काष्ठा rt2x00_dev
 *
 * Using the base rx poपूर्णांकer and the maximum number of available queues,
 * this macro will वापस the address of 1 position beyond  the end of the
 * queues array.
 */
#घोषणा queue_end(__dev) \
	&(__dev)->rx[(__dev)->data_queues]

/**
 * tx_queue_end - Return poपूर्णांकer to the last TX queue (HELPER MACRO).
 * @__dev: Poपूर्णांकer to &काष्ठा rt2x00_dev
 *
 * Using the base tx poपूर्णांकer and the maximum number of available TX
 * queues, this macro will वापस the address of 1 position beyond
 * the end of the TX queue array.
 */
#घोषणा tx_queue_end(__dev) \
	&(__dev)->tx[(__dev)->ops->tx_queues]

/**
 * queue_next - Return poपूर्णांकer to next queue in list (HELPER MACRO).
 * @__queue: Current queue क्रम which we need the next queue
 *
 * Using the current queue address we take the address directly
 * after the queue to take the next queue. Note that this macro
 * should be used carefully since it करोes not protect against
 * moving past the end of the list. (See macros &queue_end and
 * &tx_queue_end क्रम determining the end of the queue).
 */
#घोषणा queue_next(__queue) \
	&(__queue)[1]

/**
 * queue_loop - Loop through the queues within a specअगरic range (HELPER MACRO).
 * @__entry: Poपूर्णांकer where the current queue entry will be stored in.
 * @__start: Start queue poपूर्णांकer.
 * @__end: End queue poपूर्णांकer.
 *
 * This macro will loop through all queues between &__start and &__end.
 */
#घोषणा queue_loop(__entry, __start, __end)			\
	क्रम ((__entry) = (__start);				\
	     prefetch(queue_next(__entry)), (__entry) != (__end);\
	     (__entry) = queue_next(__entry))

/**
 * queue_क्रम_each - Loop through all queues
 * @__dev: Poपूर्णांकer to &काष्ठा rt2x00_dev
 * @__entry: Poपूर्णांकer where the current queue entry will be stored in.
 *
 * This macro will loop through all available queues.
 */
#घोषणा queue_क्रम_each(__dev, __entry) \
	queue_loop(__entry, (__dev)->rx, queue_end(__dev))

/**
 * tx_queue_क्रम_each - Loop through the TX queues
 * @__dev: Poपूर्णांकer to &काष्ठा rt2x00_dev
 * @__entry: Poपूर्णांकer where the current queue entry will be stored in.
 *
 * This macro will loop through all TX related queues excluding
 * the Beacon and Atim queues.
 */
#घोषणा tx_queue_क्रम_each(__dev, __entry) \
	queue_loop(__entry, (__dev)->tx, tx_queue_end(__dev))

/**
 * txall_queue_क्रम_each - Loop through all TX related queues
 * @__dev: Poपूर्णांकer to &काष्ठा rt2x00_dev
 * @__entry: Poपूर्णांकer where the current queue entry will be stored in.
 *
 * This macro will loop through all TX related queues including
 * the Beacon and Atim queues.
 */
#घोषणा txall_queue_क्रम_each(__dev, __entry) \
	queue_loop(__entry, (__dev)->tx, queue_end(__dev))

/**
 * rt2x00queue_क्रम_each_entry - Loop through all entries in the queue
 * @queue: Poपूर्णांकer to @data_queue
 * @start: &क्रमागत queue_index Poपूर्णांकer to start index
 * @end: &क्रमागत queue_index Poपूर्णांकer to end index
 * @data: Data to pass to the callback function
 * @fn: The function to call क्रम each &काष्ठा queue_entry
 *
 * This will walk through all entries in the queue, in chronological
 * order. This means it will start at the current @start poपूर्णांकer
 * and will walk through the queue until it reaches the @end poपूर्णांकer.
 *
 * If fn वापसs true क्रम an entry rt2x00queue_क्रम_each_entry will stop
 * processing and वापस true as well.
 */
bool rt2x00queue_क्रम_each_entry(काष्ठा data_queue *queue,
				क्रमागत queue_index start,
				क्रमागत queue_index end,
				व्योम *data,
				bool (*fn)(काष्ठा queue_entry *entry,
					   व्योम *data));

/**
 * rt2x00queue_empty - Check अगर the queue is empty.
 * @queue: Queue to check अगर empty.
 */
अटल अंतरभूत पूर्णांक rt2x00queue_empty(काष्ठा data_queue *queue)
अणु
	वापस queue->length == 0;
पूर्ण

/**
 * rt2x00queue_full - Check अगर the queue is full.
 * @queue: Queue to check अगर full.
 */
अटल अंतरभूत पूर्णांक rt2x00queue_full(काष्ठा data_queue *queue)
अणु
	वापस queue->length == queue->limit;
पूर्ण

/**
 * rt2x00queue_मुक्त - Check the number of available entries in queue.
 * @queue: Queue to check.
 */
अटल अंतरभूत पूर्णांक rt2x00queue_available(काष्ठा data_queue *queue)
अणु
	वापस queue->limit - queue->length;
पूर्ण

/**
 * rt2x00queue_threshold - Check अगर the queue is below threshold
 * @queue: Queue to check.
 */
अटल अंतरभूत पूर्णांक rt2x00queue_threshold(काष्ठा data_queue *queue)
अणु
	वापस rt2x00queue_available(queue) < queue->threshold;
पूर्ण
/**
 * rt2x00queue_dma_समयout - Check अगर a समयout occurred क्रम DMA transfers
 * @entry: Queue entry to check.
 */
अटल अंतरभूत पूर्णांक rt2x00queue_dma_समयout(काष्ठा queue_entry *entry)
अणु
	अगर (!test_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags))
		वापस false;
	वापस समय_after(jअगरfies, entry->last_action + msecs_to_jअगरfies(100));
पूर्ण

/**
 * _rt2x00_desc_पढ़ो - Read a word from the hardware descriptor.
 * @desc: Base descriptor address
 * @word: Word index from where the descriptor should be पढ़ो.
 */
अटल अंतरभूत __le32 _rt2x00_desc_पढ़ो(__le32 *desc, स्थिर u8 word)
अणु
	वापस desc[word];
पूर्ण

/**
 * rt2x00_desc_पढ़ो - Read a word from the hardware descriptor, this
 * function will take care of the byte ordering.
 * @desc: Base descriptor address
 * @word: Word index from where the descriptor should be पढ़ो.
 */
अटल अंतरभूत u32 rt2x00_desc_पढ़ो(__le32 *desc, स्थिर u8 word)
अणु
	वापस le32_to_cpu(_rt2x00_desc_पढ़ो(desc, word));
पूर्ण

/**
 * rt2x00_desc_ग_लिखो - ग_लिखो a word to the hardware descriptor, this
 * function will take care of the byte ordering.
 * @desc: Base descriptor address
 * @word: Word index from where the descriptor should be written.
 * @value: Value that should be written पूर्णांकo the descriptor.
 */
अटल अंतरभूत व्योम _rt2x00_desc_ग_लिखो(__le32 *desc, स्थिर u8 word, __le32 value)
अणु
	desc[word] = value;
पूर्ण

/**
 * rt2x00_desc_ग_लिखो - ग_लिखो a word to the hardware descriptor.
 * @desc: Base descriptor address
 * @word: Word index from where the descriptor should be written.
 * @value: Value that should be written पूर्णांकo the descriptor.
 */
अटल अंतरभूत व्योम rt2x00_desc_ग_लिखो(__le32 *desc, स्थिर u8 word, u32 value)
अणु
	_rt2x00_desc_ग_लिखो(desc, word, cpu_to_le32(value));
पूर्ण

#पूर्ण_अगर /* RT2X00QUEUE_H */
