<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2011-2013 Solarflare Communications Inc.
 */

/* Theory of operation:
 *
 * PTP support is assisted by firmware running on the MC, which provides
 * the hardware बारtamping capabilities.  Both transmitted and received
 * PTP event packets are queued onto पूर्णांकernal queues क्रम subsequent processing;
 * this is because the MC operations are relatively दीर्घ and would block
 * block NAPI/पूर्णांकerrupt operation.
 *
 * Receive event processing:
 *	The event contains the packet's UUID and sequence number, together
 *	with the hardware बारtamp.  The PTP receive packet queue is searched
 *	क्रम this UUID/sequence number and, अगर found, put on a pending queue.
 *	Packets not matching are delivered without बारtamps (MCDI events will
 *	always arrive after the actual packet).
 *	It is important क्रम the operation of the PTP protocol that the ordering
 *	of packets between the event and general port is मुख्यtained.
 *
 * Work queue processing:
 *	If work रुकोing, synchronise host/hardware समय
 *
 *	Transmit: send packet through MC, which वापसs the transmission समय
 *	that is converted to an appropriate बारtamp.
 *
 *	Receive: the packet's reception समय is converted to an appropriate
 *	बारtamp.
 */
#समावेश <linux/ip.h>
#समावेश <linux/udp.h>
#समावेश <linux/समय.स>
#समावेश <linux/kसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/pps_kernel.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश "net_driver.h"
#समावेश "efx.h"
#समावेश "mcdi.h"
#समावेश "mcdi_pcol.h"
#समावेश "io.h"
#समावेश "farch_regs.h"
#समावेश "tx.h"
#समावेश "nic.h" /* indirectly includes ptp.h */

/* Maximum number of events expected to make up a PTP event */
#घोषणा	MAX_EVENT_FRAGS			3

/* Maximum delay, ms, to begin synchronisation */
#घोषणा	MAX_SYNCHRONISE_WAIT_MS		2

/* How दीर्घ, at most, to spend synchronising */
#घोषणा	SYNCHRONISE_PERIOD_NS		250000

/* How often to update the shared memory समय */
#घोषणा	SYNCHRONISATION_GRANULARITY_NS	200

/* Minimum permitted length of a (corrected) synchronisation समय */
#घोषणा	DEFAULT_MIN_SYNCHRONISATION_NS	120

/* Maximum permitted length of a (corrected) synchronisation समय */
#घोषणा	MAX_SYNCHRONISATION_NS		1000

/* How many (MC) receive events that can be queued */
#घोषणा	MAX_RECEIVE_EVENTS		8

/* Length of (modअगरied) moving average. */
#घोषणा	AVERAGE_LENGTH			16

/* How दीर्घ an unmatched event or packet can be held */
#घोषणा PKT_EVENT_LIFETIME_MS		10

/* Offsets पूर्णांकo PTP packet क्रम identअगरication.  These offsets are from the
 * start of the IP header, not the MAC header.  Note that neither PTP V1 nor
 * PTP V2 permit the use of IPV4 options.
 */
#घोषणा PTP_DPORT_OFFSET	22

#घोषणा PTP_V1_VERSION_LENGTH	2
#घोषणा PTP_V1_VERSION_OFFSET	28

#घोषणा PTP_V1_UUID_LENGTH	6
#घोषणा PTP_V1_UUID_OFFSET	50

#घोषणा PTP_V1_SEQUENCE_LENGTH	2
#घोषणा PTP_V1_SEQUENCE_OFFSET	58

/* The minimum length of a PTP V1 packet क्रम offsets, etc. to be valid:
 * includes IP header.
 */
#घोषणा	PTP_V1_MIN_LENGTH	64

#घोषणा PTP_V2_VERSION_LENGTH	1
#घोषणा PTP_V2_VERSION_OFFSET	29

#घोषणा PTP_V2_UUID_LENGTH	8
#घोषणा PTP_V2_UUID_OFFSET	48

/* Although PTP V2 UUIDs are comprised a ClockIdentity (8) and PortNumber (2),
 * the MC only captures the last six bytes of the घड़ी identity. These values
 * reflect those, not the ones used in the standard.  The standard permits
 * mapping of V1 UUIDs to V2 UUIDs with these same values.
 */
#घोषणा PTP_V2_MC_UUID_LENGTH	6
#घोषणा PTP_V2_MC_UUID_OFFSET	50

#घोषणा PTP_V2_SEQUENCE_LENGTH	2
#घोषणा PTP_V2_SEQUENCE_OFFSET	58

/* The minimum length of a PTP V2 packet क्रम offsets, etc. to be valid:
 * includes IP header.
 */
#घोषणा	PTP_V2_MIN_LENGTH	63

#घोषणा	PTP_MIN_LENGTH		63

#घोषणा PTP_ADDRESS		0xe0000181	/* 224.0.1.129 */
#घोषणा PTP_EVENT_PORT		319
#घोषणा PTP_GENERAL_PORT	320

/* Annoyingly the क्रमmat of the version numbers are dअगरferent between
 * versions 1 and 2 so it isn't possible to simply look क्रम 1 or 2.
 */
#घोषणा	PTP_VERSION_V1		1

#घोषणा	PTP_VERSION_V2		2
#घोषणा	PTP_VERSION_V2_MASK	0x0f

क्रमागत ptp_packet_state अणु
	PTP_PACKET_STATE_UNMATCHED = 0,
	PTP_PACKET_STATE_MATCHED,
	PTP_PACKET_STATE_TIMED_OUT,
	PTP_PACKET_STATE_MATCH_UNWANTED
पूर्ण;

/* NIC synchronised with single word of समय only comprising
 * partial seconds and full nanoseconds: 10^9 ~ 2^30 so 2 bits क्रम seconds.
 */
#घोषणा	MC_न_अंकOSECOND_BITS	30
#घोषणा	MC_न_अंकOSECOND_MASK	((1 << MC_न_अंकOSECOND_BITS) - 1)
#घोषणा	MC_SECOND_MASK		((1 << (32 - MC_न_अंकOSECOND_BITS)) - 1)

/* Maximum parts-per-billion adjusपंचांगent that is acceptable */
#घोषणा MAX_PPB			1000000

/* Precalculate scale word to aव्योम दीर्घ दीर्घ भागision at runसमय */
/* This is equivalent to 2^66 / 10^9. */
#घोषणा PPB_SCALE_WORD  ((1LL << (57)) / 1953125LL)

/* How much to shअगरt करोwn after scaling to convert to FP40 */
#घोषणा PPB_SHIFT_FP40		26
/* ... and FP44. */
#घोषणा PPB_SHIFT_FP44		22

#घोषणा PTP_SYNC_ATTEMPTS	4

/**
 * काष्ठा efx_ptp_match - Matching काष्ठाure, stored in sk_buff's cb area.
 * @words: UUID and (partial) sequence number
 * @expiry: Time after which the packet should be delivered irrespective of
 *            event arrival.
 * @state: The state of the packet - whether it is पढ़ोy क्रम processing or
 *         whether that is of no पूर्णांकerest.
 */
काष्ठा efx_ptp_match अणु
	u32 words[DIV_ROUND_UP(PTP_V1_UUID_LENGTH, 4)];
	अचिन्हित दीर्घ expiry;
	क्रमागत ptp_packet_state state;
पूर्ण;

/**
 * काष्ठा efx_ptp_event_rx - A PTP receive event (from MC)
 * @link: list of events
 * @seq0: First part of (PTP) UUID
 * @seq1: Second part of (PTP) UUID and sequence number
 * @hwबारtamp: Event बारtamp
 * @expiry: Time which the packet arrived
 */
काष्ठा efx_ptp_event_rx अणु
	काष्ठा list_head link;
	u32 seq0;
	u32 seq1;
	kसमय_प्रकार hwबारtamp;
	अचिन्हित दीर्घ expiry;
पूर्ण;

/**
 * काष्ठा efx_ptp_बारet - Synchronisation between host and MC
 * @host_start: Host समय immediately beक्रमe hardware बारtamp taken
 * @major: Hardware बारtamp, major
 * @minor: Hardware बारtamp, minor
 * @host_end: Host समय immediately after hardware बारtamp taken
 * @रुको: Number of NIC घड़ी ticks between hardware बारtamp being पढ़ो and
 *          host end समय being seen
 * @winकरोw: Dअगरference of host_end and host_start
 * @valid: Whether this बारet is valid
 */
काष्ठा efx_ptp_बारet अणु
	u32 host_start;
	u32 major;
	u32 minor;
	u32 host_end;
	u32 रुको;
	u32 winकरोw;	/* Derived: end - start, allowing क्रम wrap */
पूर्ण;

/**
 * काष्ठा efx_ptp_data - Precision Time Protocol (PTP) state
 * @efx: The NIC context
 * @channel: The PTP channel (Siena only)
 * @rx_ts_अंतरभूत: Flag क्रम whether RX बारtamps are अंतरभूत (अन्यथा they are
 *	separate events)
 * @rxq: Receive SKB queue (aरुकोing बारtamps)
 * @txq: Transmit SKB queue
 * @evt_list: List of MC receive events aरुकोing packets
 * @evt_मुक्त_list: List of मुक्त events
 * @evt_lock: Lock क्रम manipulating evt_list and evt_मुक्त_list
 * @rx_evts: Instantiated events (on evt_list and evt_मुक्त_list)
 * @workwq: Work queue क्रम processing pending PTP operations
 * @work: Work task
 * @reset_required: A serious error has occurred and the PTP task needs to be
 *                  reset (disable, enable).
 * @rxfilter_event: Receive filter when operating
 * @rxfilter_general: Receive filter when operating
 * @rxfilter_installed: Receive filter installed
 * @config: Current बारtamp configuration
 * @enabled: PTP operation enabled
 * @mode: Mode in which PTP operating (PTP version)
 * @ns_to_nic_समय: Function to convert from scalar nanoseconds to NIC समय
 * @nic_to_kernel_समय: Function to convert from NIC to kernel समय
 * @nic_समय: contains समय details
 * @nic_समय.minor_max: Wrap poपूर्णांक क्रम NIC minor बार
 * @nic_समय.sync_event_dअगरf_min: Minimum acceptable dअगरference between समय
 * in packet prefix and last MCDI समय sync event i.e. how much earlier than
 * the last sync event समय a packet बारtamp can be.
 * @nic_समय.sync_event_dअगरf_max: Maximum acceptable dअगरference between समय
 * in packet prefix and last MCDI समय sync event i.e. how much later than
 * the last sync event समय a packet बारtamp can be.
 * @nic_समय.sync_event_minor_shअगरt: Shअगरt required to make minor समय from
 * field in MCDI समय sync event.
 * @min_synchronisation_ns: Minimum acceptable corrected sync winकरोw
 * @capabilities: Capabilities flags from the NIC
 * @ts_corrections: contains corrections details
 * @ts_corrections.ptp_tx: Required driver correction of PTP packet transmit
 *                         बारtamps
 * @ts_corrections.ptp_rx: Required driver correction of PTP packet receive
 *                         बारtamps
 * @ts_corrections.pps_out: PPS output error (inक्रमmation only)
 * @ts_corrections.pps_in: Required driver correction of PPS input बारtamps
 * @ts_corrections.general_tx: Required driver correction of general packet
 *                             transmit बारtamps
 * @ts_corrections.general_rx: Required driver correction of general packet
 *                             receive बारtamps
 * @evt_frags: Partly assembled PTP events
 * @evt_frag_idx: Current fragment number
 * @evt_code: Last event code
 * @start: Address at which MC indicates पढ़ोy क्रम synchronisation
 * @host_समय_pps: Host समय at last PPS
 * @adjfreq_ppb_shअगरt: Shअगरt required to convert scaled parts-per-billion
 * frequency adjusपंचांगent पूर्णांकo a fixed poपूर्णांक fractional nanosecond क्रमmat.
 * @current_adjfreq: Current ppb adjusपंचांगent.
 * @phc_घड़ी: Poपूर्णांकer to रेजिस्टरed phc device (अगर primary function)
 * @phc_घड़ी_info: Registration काष्ठाure क्रम phc device
 * @pps_work: pps work task क्रम handling pps events
 * @pps_workwq: pps work queue
 * @nic_ts_enabled: Flag indicating अगर NIC generated TS events are handled
 * @txbuf: Buffer क्रम use when transmitting (PTP) packets to MC (aव्योमs
 *         allocations in मुख्य data path).
 * @good_syncs: Number of successful synchronisations.
 * @fast_syncs: Number of synchronisations requiring लघु delay
 * @bad_syncs: Number of failed synchronisations.
 * @sync_समयouts: Number of synchronisation समयouts
 * @no_समय_syncs: Number of synchronisations with no good बार.
 * @invalid_sync_winकरोws: Number of sync winकरोws with bad durations.
 * @undersize_sync_winकरोws: Number of corrected sync winकरोws that are too small
 * @oversize_sync_winकरोws: Number of corrected sync winकरोws that are too large
 * @rx_no_बारtamp: Number of packets received without a बारtamp.
 * @बारet: Last set of synchronisation statistics.
 * @xmit_skb: Transmit SKB function.
 */
काष्ठा efx_ptp_data अणु
	काष्ठा efx_nic *efx;
	काष्ठा efx_channel *channel;
	bool rx_ts_अंतरभूत;
	काष्ठा sk_buff_head rxq;
	काष्ठा sk_buff_head txq;
	काष्ठा list_head evt_list;
	काष्ठा list_head evt_मुक्त_list;
	spinlock_t evt_lock;
	काष्ठा efx_ptp_event_rx rx_evts[MAX_RECEIVE_EVENTS];
	काष्ठा workqueue_काष्ठा *workwq;
	काष्ठा work_काष्ठा work;
	bool reset_required;
	u32 rxfilter_event;
	u32 rxfilter_general;
	bool rxfilter_installed;
	काष्ठा hwtstamp_config config;
	bool enabled;
	अचिन्हित पूर्णांक mode;
	व्योम (*ns_to_nic_समय)(s64 ns, u32 *nic_major, u32 *nic_minor);
	kसमय_प्रकार (*nic_to_kernel_समय)(u32 nic_major, u32 nic_minor,
				      s32 correction);
	काष्ठा अणु
		u32 minor_max;
		u32 sync_event_dअगरf_min;
		u32 sync_event_dअगरf_max;
		अचिन्हित पूर्णांक sync_event_minor_shअगरt;
	पूर्ण nic_समय;
	अचिन्हित पूर्णांक min_synchronisation_ns;
	अचिन्हित पूर्णांक capabilities;
	काष्ठा अणु
		s32 ptp_tx;
		s32 ptp_rx;
		s32 pps_out;
		s32 pps_in;
		s32 general_tx;
		s32 general_rx;
	पूर्ण ts_corrections;
	efx_qword_t evt_frags[MAX_EVENT_FRAGS];
	पूर्णांक evt_frag_idx;
	पूर्णांक evt_code;
	काष्ठा efx_buffer start;
	काष्ठा pps_event_समय host_समय_pps;
	अचिन्हित पूर्णांक adjfreq_ppb_shअगरt;
	s64 current_adjfreq;
	काष्ठा ptp_घड़ी *phc_घड़ी;
	काष्ठा ptp_घड़ी_info phc_घड़ी_info;
	काष्ठा work_काष्ठा pps_work;
	काष्ठा workqueue_काष्ठा *pps_workwq;
	bool nic_ts_enabled;
	efx_dword_t txbuf[MCDI_TX_BUF_LEN(MC_CMD_PTP_IN_TRANSMIT_LENMAX)];

	अचिन्हित पूर्णांक good_syncs;
	अचिन्हित पूर्णांक fast_syncs;
	अचिन्हित पूर्णांक bad_syncs;
	अचिन्हित पूर्णांक sync_समयouts;
	अचिन्हित पूर्णांक no_समय_syncs;
	अचिन्हित पूर्णांक invalid_sync_winकरोws;
	अचिन्हित पूर्णांक undersize_sync_winकरोws;
	अचिन्हित पूर्णांक oversize_sync_winकरोws;
	अचिन्हित पूर्णांक rx_no_बारtamp;
	काष्ठा efx_ptp_बारet
	बारet[MC_CMD_PTP_OUT_SYNCHRONIZE_TIMESET_MAXNUM];
	व्योम (*xmit_skb)(काष्ठा efx_nic *efx, काष्ठा sk_buff *skb);
पूर्ण;

अटल पूर्णांक efx_phc_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 delta);
अटल पूर्णांक efx_phc_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta);
अटल पूर्णांक efx_phc_समय_लो(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts);
अटल पूर्णांक efx_phc_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			   स्थिर काष्ठा बारpec64 *e_ts);
अटल पूर्णांक efx_phc_enable(काष्ठा ptp_घड़ी_info *ptp,
			  काष्ठा ptp_घड़ी_request *request, पूर्णांक on);

bool efx_ptp_use_mac_tx_बारtamps(काष्ठा efx_nic *efx)
अणु
	वापस efx_has_cap(efx, TX_MAC_TIMESTAMPING);
पूर्ण

/* PTP 'extra' channel is still a traffic channel, but we only create TX queues
 * अगर PTP uses MAC TX बारtamps, not अगर PTP uses the MC directly to transmit.
 */
अटल bool efx_ptp_want_txqs(काष्ठा efx_channel *channel)
अणु
	वापस efx_ptp_use_mac_tx_बारtamps(channel->efx);
पूर्ण

#घोषणा PTP_SW_STAT(ext_name, field_name)				\
	अणु #ext_name, 0, दुरत्व(काष्ठा efx_ptp_data, field_name) पूर्ण
#घोषणा PTP_MC_STAT(ext_name, mcdi_name)				\
	अणु #ext_name, 32, MC_CMD_PTP_OUT_STATUS_STATS_ ## mcdi_name ## _OFST पूर्ण
अटल स्थिर काष्ठा efx_hw_stat_desc efx_ptp_stat_desc[] = अणु
	PTP_SW_STAT(ptp_good_syncs, good_syncs),
	PTP_SW_STAT(ptp_fast_syncs, fast_syncs),
	PTP_SW_STAT(ptp_bad_syncs, bad_syncs),
	PTP_SW_STAT(ptp_sync_समयouts, sync_समयouts),
	PTP_SW_STAT(ptp_no_समय_syncs, no_समय_syncs),
	PTP_SW_STAT(ptp_invalid_sync_winकरोws, invalid_sync_winकरोws),
	PTP_SW_STAT(ptp_undersize_sync_winकरोws, undersize_sync_winकरोws),
	PTP_SW_STAT(ptp_oversize_sync_winकरोws, oversize_sync_winकरोws),
	PTP_SW_STAT(ptp_rx_no_बारtamp, rx_no_बारtamp),
	PTP_MC_STAT(ptp_tx_बारtamp_packets, TX),
	PTP_MC_STAT(ptp_rx_बारtamp_packets, RX),
	PTP_MC_STAT(ptp_बारtamp_packets, TS),
	PTP_MC_STAT(ptp_filter_matches, FM),
	PTP_MC_STAT(ptp_non_filter_matches, NFM),
पूर्ण;
#घोषणा PTP_STAT_COUNT ARRAY_SIZE(efx_ptp_stat_desc)
अटल स्थिर अचिन्हित दीर्घ efx_ptp_stat_mask[] = अणु
	[0 ... BITS_TO_LONGS(PTP_STAT_COUNT) - 1] = ~0UL,
पूर्ण;

माप_प्रकार efx_ptp_describe_stats(काष्ठा efx_nic *efx, u8 *strings)
अणु
	अगर (!efx->ptp_data)
		वापस 0;

	वापस efx_nic_describe_stats(efx_ptp_stat_desc, PTP_STAT_COUNT,
				      efx_ptp_stat_mask, strings);
पूर्ण

माप_प्रकार efx_ptp_update_stats(काष्ठा efx_nic *efx, u64 *stats)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_PTP_IN_STATUS_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_PTP_OUT_STATUS_LEN);
	माप_प्रकार i;
	पूर्णांक rc;

	अगर (!efx->ptp_data)
		वापस 0;

	/* Copy software statistics */
	क्रम (i = 0; i < PTP_STAT_COUNT; i++) अणु
		अगर (efx_ptp_stat_desc[i].dma_width)
			जारी;
		stats[i] = *(अचिन्हित पूर्णांक *)((अक्षर *)efx->ptp_data +
					     efx_ptp_stat_desc[i].offset);
	पूर्ण

	/* Fetch MC statistics.  We *must* fill in all statistics or
	 * risk leaking kernel memory to userland, so अगर the MCDI
	 * request fails we pretend we got zeroes.
	 */
	MCDI_SET_DWORD(inbuf, PTP_IN_OP, MC_CMD_PTP_OP_STATUS);
	MCDI_SET_DWORD(inbuf, PTP_IN_PERIPH_ID, 0);
	rc = efx_mcdi_rpc(efx, MC_CMD_PTP, inbuf, माप(inbuf),
			  outbuf, माप(outbuf), शून्य);
	अगर (rc)
		स_रखो(outbuf, 0, माप(outbuf));
	efx_nic_update_stats(efx_ptp_stat_desc, PTP_STAT_COUNT,
			     efx_ptp_stat_mask,
			     stats, _MCDI_PTR(outbuf, 0), false);

	वापस PTP_STAT_COUNT;
पूर्ण

/* For Siena platक्रमms NIC समय is s and ns */
अटल व्योम efx_ptp_ns_to_s_ns(s64 ns, u32 *nic_major, u32 *nic_minor)
अणु
	काष्ठा बारpec64 ts = ns_to_बारpec64(ns);
	*nic_major = (u32)ts.tv_sec;
	*nic_minor = ts.tv_nsec;
पूर्ण

अटल kसमय_प्रकार efx_ptp_s_ns_to_kसमय_correction(u32 nic_major, u32 nic_minor,
						s32 correction)
अणु
	kसमय_प्रकार kt = kसमय_set(nic_major, nic_minor);
	अगर (correction >= 0)
		kt = kसमय_add_ns(kt, (u64)correction);
	अन्यथा
		kt = kसमय_sub_ns(kt, (u64)-correction);
	वापस kt;
पूर्ण

/* To convert from s27 क्रमmat to ns we multiply then भागide by a घातer of 2.
 * For the conversion from ns to s27, the operation is also converted to a
 * multiply and shअगरt.
 */
#घोषणा S27_TO_NS_SHIFT	(27)
#घोषणा NS_TO_S27_MULT	(((1ULL << 63) + NSEC_PER_SEC / 2) / NSEC_PER_SEC)
#घोषणा NS_TO_S27_SHIFT	(63 - S27_TO_NS_SHIFT)
#घोषणा S27_MINOR_MAX	(1 << S27_TO_NS_SHIFT)

/* For Huntington platक्रमms NIC समय is in seconds and fractions of a second
 * where the minor रेजिस्टर only uses 27 bits in units of 2^-27s.
 */
अटल व्योम efx_ptp_ns_to_s27(s64 ns, u32 *nic_major, u32 *nic_minor)
अणु
	काष्ठा बारpec64 ts = ns_to_बारpec64(ns);
	u32 maj = (u32)ts.tv_sec;
	u32 min = (u32)(((u64)ts.tv_nsec * NS_TO_S27_MULT +
			 (1ULL << (NS_TO_S27_SHIFT - 1))) >> NS_TO_S27_SHIFT);

	/* The conversion can result in the minor value exceeding the maximum.
	 * In this हाल, round up to the next second.
	 */
	अगर (min >= S27_MINOR_MAX) अणु
		min -= S27_MINOR_MAX;
		maj++;
	पूर्ण

	*nic_major = maj;
	*nic_minor = min;
पूर्ण

अटल अंतरभूत kसमय_प्रकार efx_ptp_s27_to_kसमय(u32 nic_major, u32 nic_minor)
अणु
	u32 ns = (u32)(((u64)nic_minor * NSEC_PER_SEC +
			(1ULL << (S27_TO_NS_SHIFT - 1))) >> S27_TO_NS_SHIFT);
	वापस kसमय_set(nic_major, ns);
पूर्ण

अटल kसमय_प्रकार efx_ptp_s27_to_kसमय_correction(u32 nic_major, u32 nic_minor,
					       s32 correction)
अणु
	/* Apply the correction and deal with carry */
	nic_minor += correction;
	अगर ((s32)nic_minor < 0) अणु
		nic_minor += S27_MINOR_MAX;
		nic_major--;
	पूर्ण अन्यथा अगर (nic_minor >= S27_MINOR_MAX) अणु
		nic_minor -= S27_MINOR_MAX;
		nic_major++;
	पूर्ण

	वापस efx_ptp_s27_to_kसमय(nic_major, nic_minor);
पूर्ण

/* For Medक्रमd2 platक्रमms the समय is in seconds and quarter nanoseconds. */
अटल व्योम efx_ptp_ns_to_s_qns(s64 ns, u32 *nic_major, u32 *nic_minor)
अणु
	काष्ठा बारpec64 ts = ns_to_बारpec64(ns);

	*nic_major = (u32)ts.tv_sec;
	*nic_minor = ts.tv_nsec * 4;
पूर्ण

अटल kसमय_प्रकार efx_ptp_s_qns_to_kसमय_correction(u32 nic_major, u32 nic_minor,
						 s32 correction)
अणु
	kसमय_प्रकार kt;

	nic_minor = DIV_ROUND_CLOSEST(nic_minor, 4);
	correction = DIV_ROUND_CLOSEST(correction, 4);

	kt = kसमय_set(nic_major, nic_minor);

	अगर (correction >= 0)
		kt = kसमय_add_ns(kt, (u64)correction);
	अन्यथा
		kt = kसमय_sub_ns(kt, (u64)-correction);
	वापस kt;
पूर्ण

काष्ठा efx_channel *efx_ptp_channel(काष्ठा efx_nic *efx)
अणु
	वापस efx->ptp_data ? efx->ptp_data->channel : शून्य;
पूर्ण

अटल u32 last_sync_बारtamp_major(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel = efx_ptp_channel(efx);
	u32 major = 0;

	अगर (channel)
		major = channel->sync_बारtamp_major;
	वापस major;
पूर्ण

/* The 8000 series and later can provide the समय from the MAC, which is only
 * 48 bits दीर्घ and provides meta-inक्रमmation in the top 2 bits.
 */
अटल kसमय_प्रकार
efx_ptp_mac_nic_to_kसमय_correction(काष्ठा efx_nic *efx,
				    काष्ठा efx_ptp_data *ptp,
				    u32 nic_major, u32 nic_minor,
				    s32 correction)
अणु
	u32 sync_बारtamp;
	kसमय_प्रकार kt = अणु 0 पूर्ण;
	s16 delta;

	अगर (!(nic_major & 0x80000000)) अणु
		WARN_ON_ONCE(nic_major >> 16);

		/* Medक्रमd provides 48 bits of बारtamp, so we must get the top
		 * 16 bits from the बारync event state.
		 *
		 * We only have the lower 16 bits of the समय now, but we करो
		 * have a full resolution बारtamp at some poपूर्णांक in past. As
		 * दीर्घ as the dअगरference between the (real) now and the sync
		 * is less than 2^15, then we can reस्थिरruct the dअगरference
		 * between those two numbers using only the lower 16 bits of
		 * each.
		 *
		 * Put another way
		 *
		 * a - b = ((a mod k) - b) mod k
		 *
		 * when -k/2 < (a-b) < k/2. In our हाल k is 2^16. We know
		 * (a mod k) and b, so can calculate the delta, a - b.
		 *
		 */
		sync_बारtamp = last_sync_बारtamp_major(efx);

		/* Because delta is s16 this करोes an implicit mask करोwn to
		 * 16 bits which is what we need, assuming
		 * MEDFORD_TX_SECS_EVENT_BITS is 16. delta is चिन्हित so that
		 * we can deal with the (unlikely) हाल of sync बारtamps
		 * arriving from the future.
		 */
		delta = nic_major - sync_बारtamp;

		/* Recover the fully specअगरied समय now, by applying the offset
		 * to the (fully specअगरied) sync समय.
		 */
		nic_major = sync_बारtamp + delta;

		kt = ptp->nic_to_kernel_समय(nic_major, nic_minor,
					     correction);
	पूर्ण
	वापस kt;
पूर्ण

kसमय_प्रकार efx_ptp_nic_to_kernel_समय(काष्ठा efx_tx_queue *tx_queue)
अणु
	काष्ठा efx_nic *efx = tx_queue->efx;
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;
	kसमय_प्रकार kt;

	अगर (efx_ptp_use_mac_tx_बारtamps(efx))
		kt = efx_ptp_mac_nic_to_kसमय_correction(efx, ptp,
				tx_queue->completed_बारtamp_major,
				tx_queue->completed_बारtamp_minor,
				ptp->ts_corrections.general_tx);
	अन्यथा
		kt = ptp->nic_to_kernel_समय(
				tx_queue->completed_बारtamp_major,
				tx_queue->completed_बारtamp_minor,
				ptp->ts_corrections.general_tx);
	वापस kt;
पूर्ण

/* Get PTP attributes and set up समय conversions */
अटल पूर्णांक efx_ptp_get_attributes(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_PTP_IN_GET_ATTRIBUTES_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_PTP_OUT_GET_ATTRIBUTES_LEN);
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;
	पूर्णांक rc;
	u32 fmt;
	माप_प्रकार out_len;

	/* Get the PTP attributes. If the NIC करोesn't support the operation we
	 * use the शेष क्रमmat क्रम compatibility with older NICs i.e.
	 * seconds and nanoseconds.
	 */
	MCDI_SET_DWORD(inbuf, PTP_IN_OP, MC_CMD_PTP_OP_GET_ATTRIBUTES);
	MCDI_SET_DWORD(inbuf, PTP_IN_PERIPH_ID, 0);
	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_PTP, inbuf, माप(inbuf),
				outbuf, माप(outbuf), &out_len);
	अगर (rc == 0) अणु
		fmt = MCDI_DWORD(outbuf, PTP_OUT_GET_ATTRIBUTES_TIME_FORMAT);
	पूर्ण अन्यथा अगर (rc == -EINVAL) अणु
		fmt = MC_CMD_PTP_OUT_GET_ATTRIBUTES_SECONDS_न_अंकOSECONDS;
	पूर्ण अन्यथा अगर (rc == -EPERM) अणु
		netअगर_info(efx, probe, efx->net_dev, "no PTP support\n");
		वापस rc;
	पूर्ण अन्यथा अणु
		efx_mcdi_display_error(efx, MC_CMD_PTP, माप(inbuf),
				       outbuf, माप(outbuf), rc);
		वापस rc;
	पूर्ण

	चयन (fmt) अणु
	हाल MC_CMD_PTP_OUT_GET_ATTRIBUTES_SECONDS_27FRACTION:
		ptp->ns_to_nic_समय = efx_ptp_ns_to_s27;
		ptp->nic_to_kernel_समय = efx_ptp_s27_to_kसमय_correction;
		ptp->nic_समय.minor_max = 1 << 27;
		ptp->nic_समय.sync_event_minor_shअगरt = 19;
		अवरोध;
	हाल MC_CMD_PTP_OUT_GET_ATTRIBUTES_SECONDS_न_अंकOSECONDS:
		ptp->ns_to_nic_समय = efx_ptp_ns_to_s_ns;
		ptp->nic_to_kernel_समय = efx_ptp_s_ns_to_kसमय_correction;
		ptp->nic_समय.minor_max = 1000000000;
		ptp->nic_समय.sync_event_minor_shअगरt = 22;
		अवरोध;
	हाल MC_CMD_PTP_OUT_GET_ATTRIBUTES_SECONDS_QTR_न_अंकOSECONDS:
		ptp->ns_to_nic_समय = efx_ptp_ns_to_s_qns;
		ptp->nic_to_kernel_समय = efx_ptp_s_qns_to_kसमय_correction;
		ptp->nic_समय.minor_max = 4000000000UL;
		ptp->nic_समय.sync_event_minor_shअगरt = 24;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	/* Precalculate acceptable dअगरference between the minor समय in the
	 * packet prefix and the last MCDI समय sync event. We expect the
	 * packet prefix बारtamp to be after of sync event by up to one
	 * sync event पूर्णांकerval (0.25s) but we allow it to exceed this by a
	 * fuzz factor of (0.1s)
	 */
	ptp->nic_समय.sync_event_dअगरf_min = ptp->nic_समय.minor_max
		- (ptp->nic_समय.minor_max / 10);
	ptp->nic_समय.sync_event_dअगरf_max = (ptp->nic_समय.minor_max / 4)
		+ (ptp->nic_समय.minor_max / 10);

	/* MC_CMD_PTP_OP_GET_ATTRIBUTES has been extended twice from an older
	 * operation MC_CMD_PTP_OP_GET_TIME_FORMAT. The function now may वापस
	 * a value to use क्रम the minimum acceptable corrected synchronization
	 * winकरोw and may वापस further capabilities.
	 * If we have the extra inक्रमmation store it. For older firmware that
	 * करोes not implement the extended command use the शेष value.
	 */
	अगर (rc == 0 &&
	    out_len >= MC_CMD_PTP_OUT_GET_ATTRIBUTES_CAPABILITIES_OFST)
		ptp->min_synchronisation_ns =
			MCDI_DWORD(outbuf,
				   PTP_OUT_GET_ATTRIBUTES_SYNC_WINDOW_MIN);
	अन्यथा
		ptp->min_synchronisation_ns = DEFAULT_MIN_SYNCHRONISATION_NS;

	अगर (rc == 0 &&
	    out_len >= MC_CMD_PTP_OUT_GET_ATTRIBUTES_LEN)
		ptp->capabilities = MCDI_DWORD(outbuf,
					PTP_OUT_GET_ATTRIBUTES_CAPABILITIES);
	अन्यथा
		ptp->capabilities = 0;

	/* Set up the shअगरt क्रम conversion between frequency
	 * adjusपंचांगents in parts-per-billion and the fixed-poपूर्णांक
	 * fractional ns क्रमmat that the adapter uses.
	 */
	अगर (ptp->capabilities & (1 << MC_CMD_PTP_OUT_GET_ATTRIBUTES_FP44_FREQ_ADJ_LBN))
		ptp->adjfreq_ppb_shअगरt = PPB_SHIFT_FP44;
	अन्यथा
		ptp->adjfreq_ppb_shअगरt = PPB_SHIFT_FP40;

	वापस 0;
पूर्ण

/* Get PTP बारtamp corrections */
अटल पूर्णांक efx_ptp_get_बारtamp_corrections(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_PTP_IN_GET_TIMESTAMP_CORRECTIONS_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_PTP_OUT_GET_TIMESTAMP_CORRECTIONS_V2_LEN);
	पूर्णांक rc;
	माप_प्रकार out_len;

	/* Get the बारtamp corrections from the NIC. If this operation is
	 * not supported (older NICs) then no correction is required.
	 */
	MCDI_SET_DWORD(inbuf, PTP_IN_OP,
		       MC_CMD_PTP_OP_GET_TIMESTAMP_CORRECTIONS);
	MCDI_SET_DWORD(inbuf, PTP_IN_PERIPH_ID, 0);

	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_PTP, inbuf, माप(inbuf),
				outbuf, माप(outbuf), &out_len);
	अगर (rc == 0) अणु
		efx->ptp_data->ts_corrections.ptp_tx = MCDI_DWORD(outbuf,
			PTP_OUT_GET_TIMESTAMP_CORRECTIONS_TRANSMIT);
		efx->ptp_data->ts_corrections.ptp_rx = MCDI_DWORD(outbuf,
			PTP_OUT_GET_TIMESTAMP_CORRECTIONS_RECEIVE);
		efx->ptp_data->ts_corrections.pps_out = MCDI_DWORD(outbuf,
			PTP_OUT_GET_TIMESTAMP_CORRECTIONS_PPS_OUT);
		efx->ptp_data->ts_corrections.pps_in = MCDI_DWORD(outbuf,
			PTP_OUT_GET_TIMESTAMP_CORRECTIONS_PPS_IN);

		अगर (out_len >= MC_CMD_PTP_OUT_GET_TIMESTAMP_CORRECTIONS_V2_LEN) अणु
			efx->ptp_data->ts_corrections.general_tx = MCDI_DWORD(
				outbuf,
				PTP_OUT_GET_TIMESTAMP_CORRECTIONS_V2_GENERAL_TX);
			efx->ptp_data->ts_corrections.general_rx = MCDI_DWORD(
				outbuf,
				PTP_OUT_GET_TIMESTAMP_CORRECTIONS_V2_GENERAL_RX);
		पूर्ण अन्यथा अणु
			efx->ptp_data->ts_corrections.general_tx =
				efx->ptp_data->ts_corrections.ptp_tx;
			efx->ptp_data->ts_corrections.general_rx =
				efx->ptp_data->ts_corrections.ptp_rx;
		पूर्ण
	पूर्ण अन्यथा अगर (rc == -EINVAL) अणु
		efx->ptp_data->ts_corrections.ptp_tx = 0;
		efx->ptp_data->ts_corrections.ptp_rx = 0;
		efx->ptp_data->ts_corrections.pps_out = 0;
		efx->ptp_data->ts_corrections.pps_in = 0;
		efx->ptp_data->ts_corrections.general_tx = 0;
		efx->ptp_data->ts_corrections.general_rx = 0;
	पूर्ण अन्यथा अणु
		efx_mcdi_display_error(efx, MC_CMD_PTP, माप(inbuf), outbuf,
				       माप(outbuf), rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

/* Enable MCDI PTP support. */
अटल पूर्णांक efx_ptp_enable(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_PTP_IN_ENABLE_LEN);
	MCDI_DECLARE_BUF_ERR(outbuf);
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, PTP_IN_OP, MC_CMD_PTP_OP_ENABLE);
	MCDI_SET_DWORD(inbuf, PTP_IN_PERIPH_ID, 0);
	MCDI_SET_DWORD(inbuf, PTP_IN_ENABLE_QUEUE,
		       efx->ptp_data->channel ?
		       efx->ptp_data->channel->channel : 0);
	MCDI_SET_DWORD(inbuf, PTP_IN_ENABLE_MODE, efx->ptp_data->mode);

	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_PTP, inbuf, माप(inbuf),
				outbuf, माप(outbuf), शून्य);
	rc = (rc == -EALREADY) ? 0 : rc;
	अगर (rc)
		efx_mcdi_display_error(efx, MC_CMD_PTP,
				       MC_CMD_PTP_IN_ENABLE_LEN,
				       outbuf, माप(outbuf), rc);
	वापस rc;
पूर्ण

/* Disable MCDI PTP support.
 *
 * Note that this function should never rely on the presence of ptp_data -
 * may be called beक्रमe that exists.
 */
अटल पूर्णांक efx_ptp_disable(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_PTP_IN_DISABLE_LEN);
	MCDI_DECLARE_BUF_ERR(outbuf);
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, PTP_IN_OP, MC_CMD_PTP_OP_DISABLE);
	MCDI_SET_DWORD(inbuf, PTP_IN_PERIPH_ID, 0);
	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_PTP, inbuf, माप(inbuf),
				outbuf, माप(outbuf), शून्य);
	rc = (rc == -EALREADY) ? 0 : rc;
	/* If we get ENOSYS, the NIC करोesn't support PTP, and thus this function
	 * should only have been called during probe.
	 */
	अगर (rc == -ENOSYS || rc == -EPERM)
		netअगर_info(efx, probe, efx->net_dev, "no PTP support\n");
	अन्यथा अगर (rc)
		efx_mcdi_display_error(efx, MC_CMD_PTP,
				       MC_CMD_PTP_IN_DISABLE_LEN,
				       outbuf, माप(outbuf), rc);
	वापस rc;
पूर्ण

अटल व्योम efx_ptp_deliver_rx_queue(काष्ठा sk_buff_head *q)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(q))) अणु
		local_bh_disable();
		netअगर_receive_skb(skb);
		local_bh_enable();
	पूर्ण
पूर्ण

अटल व्योम efx_ptp_handle_no_channel(काष्ठा efx_nic *efx)
अणु
	netअगर_err(efx, drv, efx->net_dev,
		  "ERROR: PTP requires MSI-X and 1 additional interrupt"
		  "vector. PTP disabled\n");
पूर्ण

/* Repeatedly send the host समय to the MC which will capture the hardware
 * समय.
 */
अटल व्योम efx_ptp_send_बार(काष्ठा efx_nic *efx,
			       काष्ठा pps_event_समय *last_समय)
अणु
	काष्ठा pps_event_समय now;
	काष्ठा बारpec64 limit;
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;
	पूर्णांक *mc_running = ptp->start.addr;

	pps_get_ts(&now);
	limit = now.ts_real;
	बारpec64_add_ns(&limit, SYNCHRONISE_PERIOD_NS);

	/* Write host समय क्रम specअगरied period or until MC is करोne */
	जबतक ((बारpec64_compare(&now.ts_real, &limit) < 0) &&
	       READ_ONCE(*mc_running)) अणु
		काष्ठा बारpec64 update_समय;
		अचिन्हित पूर्णांक host_समय;

		/* Don't update continuously to aव्योम saturating the PCIe bus */
		update_समय = now.ts_real;
		बारpec64_add_ns(&update_समय, SYNCHRONISATION_GRANULARITY_NS);
		करो अणु
			pps_get_ts(&now);
		पूर्ण जबतक ((बारpec64_compare(&now.ts_real, &update_समय) < 0) &&
			 READ_ONCE(*mc_running));

		/* Synchronise NIC with single word of समय only */
		host_समय = (now.ts_real.tv_sec << MC_न_अंकOSECOND_BITS |
			     now.ts_real.tv_nsec);
		/* Update host समय in NIC memory */
		efx->type->ptp_ग_लिखो_host_समय(efx, host_समय);
	पूर्ण
	*last_समय = now;
पूर्ण

/* Read a बारet from the MC's results and partial process. */
अटल व्योम efx_ptp_पढ़ो_बारet(MCDI_DECLARE_STRUCT_PTR(data),
				 काष्ठा efx_ptp_बारet *बारet)
अणु
	अचिन्हित start_ns, end_ns;

	बारet->host_start = MCDI_DWORD(data, PTP_OUT_SYNCHRONIZE_HOSTSTART);
	बारet->major = MCDI_DWORD(data, PTP_OUT_SYNCHRONIZE_MAJOR);
	बारet->minor = MCDI_DWORD(data, PTP_OUT_SYNCHRONIZE_MINOR);
	बारet->host_end = MCDI_DWORD(data, PTP_OUT_SYNCHRONIZE_HOSTEND),
	बारet->रुको = MCDI_DWORD(data, PTP_OUT_SYNCHRONIZE_WAITNS);

	/* Ignore seconds */
	start_ns = बारet->host_start & MC_न_अंकOSECOND_MASK;
	end_ns = बारet->host_end & MC_न_अंकOSECOND_MASK;
	/* Allow क्रम rollover */
	अगर (end_ns < start_ns)
		end_ns += NSEC_PER_SEC;
	/* Determine duration of operation */
	बारet->winकरोw = end_ns - start_ns;
पूर्ण

/* Process बार received from MC.
 *
 * Extract बार from वापसed results, and establish the minimum value
 * seen.  The minimum value represents the "best" possible समय and events
 * too much greater than this are rejected - the machine is, perhaps, too
 * busy. A number of पढ़ोings are taken so that, hopefully, at least one good
 * synchronisation will be seen in the results.
 */
अटल पूर्णांक
efx_ptp_process_बार(काष्ठा efx_nic *efx, MCDI_DECLARE_STRUCT_PTR(synch_buf),
		      माप_प्रकार response_length,
		      स्थिर काष्ठा pps_event_समय *last_समय)
अणु
	अचिन्हित number_पढ़ोings =
		MCDI_VAR_ARRAY_LEN(response_length,
				   PTP_OUT_SYNCHRONIZE_TIMESET);
	अचिन्हित i;
	अचिन्हित ngood = 0;
	अचिन्हित last_good = 0;
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;
	u32 last_sec;
	u32 start_sec;
	काष्ठा बारpec64 delta;
	kसमय_प्रकार mc_समय;

	अगर (number_पढ़ोings == 0)
		वापस -EAGAIN;

	/* Read the set of results and find the last good host-MC
	 * synchronization result. The MC बार when it finishes पढ़ोing the
	 * host समय so the corrected winकरोw समय should be fairly स्थिरant
	 * क्रम a given platक्रमm. Increment stats क्रम any results that appear
	 * to be erroneous.
	 */
	क्रम (i = 0; i < number_पढ़ोings; i++) अणु
		s32 winकरोw, corrected;
		काष्ठा बारpec64 रुको;

		efx_ptp_पढ़ो_बारet(
			MCDI_ARRAY_STRUCT_PTR(synch_buf,
					      PTP_OUT_SYNCHRONIZE_TIMESET, i),
			&ptp->बारet[i]);

		रुको = kसमय_प्रकारo_बारpec64(
			ptp->nic_to_kernel_समय(0, ptp->बारet[i].रुको, 0));
		winकरोw = ptp->बारet[i].winकरोw;
		corrected = winकरोw - रुको.tv_nsec;

		/* We expect the uncorrected synchronization winकरोw to be at
		 * least as large as the पूर्णांकerval between host start and end
		 * बार. If it is smaller than this then this is mostly likely
		 * to be a consequence of the host's समय being adjusted.
		 * Check that the corrected sync winकरोw is in a reasonable
		 * range. If it is out of range it is likely to be because an
		 * पूर्णांकerrupt or other delay occurred between पढ़ोing the प्रणाली
		 * समय and writing it to MC memory.
		 */
		अगर (winकरोw < SYNCHRONISATION_GRANULARITY_NS) अणु
			++ptp->invalid_sync_winकरोws;
		पूर्ण अन्यथा अगर (corrected >= MAX_SYNCHRONISATION_NS) अणु
			++ptp->oversize_sync_winकरोws;
		पूर्ण अन्यथा अगर (corrected < ptp->min_synchronisation_ns) अणु
			++ptp->undersize_sync_winकरोws;
		पूर्ण अन्यथा अणु
			ngood++;
			last_good = i;
		पूर्ण
	पूर्ण

	अगर (ngood == 0) अणु
		netअगर_warn(efx, drv, efx->net_dev,
			   "PTP no suitable synchronisations\n");
		वापस -EAGAIN;
	पूर्ण

	/* Calculate delay from last good sync (host समय) to last_समय.
	 * It is possible that the seconds rolled over between taking
	 * the start पढ़ोing and the last value written by the host.  The
	 * बारcales are such that a gap of more than one second is never
	 * expected.  delta is *not* normalised.
	 */
	start_sec = ptp->बारet[last_good].host_start >> MC_न_अंकOSECOND_BITS;
	last_sec = last_समय->ts_real.tv_sec & MC_SECOND_MASK;
	अगर (start_sec != last_sec &&
	    ((start_sec + 1) & MC_SECOND_MASK) != last_sec) अणु
		netअगर_warn(efx, hw, efx->net_dev,
			   "PTP bad synchronisation seconds\n");
		वापस -EAGAIN;
	पूर्ण
	delta.tv_sec = (last_sec - start_sec) & 1;
	delta.tv_nsec =
		last_समय->ts_real.tv_nsec -
		(ptp->बारet[last_good].host_start & MC_न_अंकOSECOND_MASK);

	/* Convert the NIC समय at last good sync पूर्णांकo kernel समय.
	 * No correction is required - this समय is the output of a
	 * firmware process.
	 */
	mc_समय = ptp->nic_to_kernel_समय(ptp->बारet[last_good].major,
					  ptp->बारet[last_good].minor, 0);

	/* Calculate delay from NIC top of second to last_समय */
	delta.tv_nsec += kसमय_प्रकारo_बारpec64(mc_समय).tv_nsec;

	/* Set PPS बारtamp to match NIC top of second */
	ptp->host_समय_pps = *last_समय;
	pps_sub_ts(&ptp->host_समय_pps, delta);

	वापस 0;
पूर्ण

/* Synchronize बार between the host and the MC */
अटल पूर्णांक efx_ptp_synchronize(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक num_पढ़ोings)
अणु
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;
	MCDI_DECLARE_BUF(synch_buf, MC_CMD_PTP_OUT_SYNCHRONIZE_LENMAX);
	माप_प्रकार response_length;
	पूर्णांक rc;
	अचिन्हित दीर्घ समयout;
	काष्ठा pps_event_समय last_समय = अणुपूर्ण;
	अचिन्हित पूर्णांक loops = 0;
	पूर्णांक *start = ptp->start.addr;

	MCDI_SET_DWORD(synch_buf, PTP_IN_OP, MC_CMD_PTP_OP_SYNCHRONIZE);
	MCDI_SET_DWORD(synch_buf, PTP_IN_PERIPH_ID, 0);
	MCDI_SET_DWORD(synch_buf, PTP_IN_SYNCHRONIZE_NUMTIMESETS,
		       num_पढ़ोings);
	MCDI_SET_QWORD(synch_buf, PTP_IN_SYNCHRONIZE_START_ADDR,
		       ptp->start.dma_addr);

	/* Clear flag that संकेतs MC पढ़ोy */
	WRITE_ONCE(*start, 0);
	rc = efx_mcdi_rpc_start(efx, MC_CMD_PTP, synch_buf,
				MC_CMD_PTP_IN_SYNCHRONIZE_LEN);
	EFX_WARN_ON_ONCE_PARANOID(rc);

	/* Wait क्रम start from MCDI (or समयout) */
	समयout = jअगरfies + msecs_to_jअगरfies(MAX_SYNCHRONISE_WAIT_MS);
	जबतक (!READ_ONCE(*start) && (समय_beक्रमe(jअगरfies, समयout))) अणु
		udelay(20);	/* Usually start MCDI execution quickly */
		loops++;
	पूर्ण

	अगर (loops <= 1)
		++ptp->fast_syncs;
	अगर (!समय_beक्रमe(jअगरfies, समयout))
		++ptp->sync_समयouts;

	अगर (READ_ONCE(*start))
		efx_ptp_send_बार(efx, &last_समय);

	/* Collect results */
	rc = efx_mcdi_rpc_finish(efx, MC_CMD_PTP,
				 MC_CMD_PTP_IN_SYNCHRONIZE_LEN,
				 synch_buf, माप(synch_buf),
				 &response_length);
	अगर (rc == 0) अणु
		rc = efx_ptp_process_बार(efx, synch_buf, response_length,
					   &last_समय);
		अगर (rc == 0)
			++ptp->good_syncs;
		अन्यथा
			++ptp->no_समय_syncs;
	पूर्ण

	/* Increment the bad syncs counter अगर the synchronize fails, whatever
	 * the reason.
	 */
	अगर (rc != 0)
		++ptp->bad_syncs;

	वापस rc;
पूर्ण

/* Transmit a PTP packet via the dedicated hardware बारtamped queue. */
अटल व्योम efx_ptp_xmit_skb_queue(काष्ठा efx_nic *efx, काष्ठा sk_buff *skb)
अणु
	काष्ठा efx_ptp_data *ptp_data = efx->ptp_data;
	u8 type = efx_tx_csum_type_skb(skb);
	काष्ठा efx_tx_queue *tx_queue;

	tx_queue = efx_channel_get_tx_queue(ptp_data->channel, type);
	अगर (tx_queue && tx_queue->बारtamping) अणु
		efx_enqueue_skb(tx_queue, skb);
	पूर्ण अन्यथा अणु
		WARN_ONCE(1, "PTP channel has no timestamped tx queue\n");
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

/* Transmit a PTP packet, via the MCDI पूर्णांकerface, to the wire. */
अटल व्योम efx_ptp_xmit_skb_mc(काष्ठा efx_nic *efx, काष्ठा sk_buff *skb)
अणु
	काष्ठा efx_ptp_data *ptp_data = efx->ptp_data;
	काष्ठा skb_shared_hwtstamps बारtamps;
	पूर्णांक rc = -EIO;
	MCDI_DECLARE_BUF(txसमय, MC_CMD_PTP_OUT_TRANSMIT_LEN);
	माप_प्रकार len;

	MCDI_SET_DWORD(ptp_data->txbuf, PTP_IN_OP, MC_CMD_PTP_OP_TRANSMIT);
	MCDI_SET_DWORD(ptp_data->txbuf, PTP_IN_PERIPH_ID, 0);
	MCDI_SET_DWORD(ptp_data->txbuf, PTP_IN_TRANSMIT_LENGTH, skb->len);
	अगर (skb_shinfo(skb)->nr_frags != 0) अणु
		rc = skb_linearize(skb);
		अगर (rc != 0)
			जाओ fail;
	पूर्ण

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		rc = skb_checksum_help(skb);
		अगर (rc != 0)
			जाओ fail;
	पूर्ण
	skb_copy_from_linear_data(skb,
				  MCDI_PTR(ptp_data->txbuf,
					   PTP_IN_TRANSMIT_PACKET),
				  skb->len);
	rc = efx_mcdi_rpc(efx, MC_CMD_PTP,
			  ptp_data->txbuf, MC_CMD_PTP_IN_TRANSMIT_LEN(skb->len),
			  txसमय, माप(txसमय), &len);
	अगर (rc != 0)
		जाओ fail;

	स_रखो(&बारtamps, 0, माप(बारtamps));
	बारtamps.hwtstamp = ptp_data->nic_to_kernel_समय(
		MCDI_DWORD(txसमय, PTP_OUT_TRANSMIT_MAJOR),
		MCDI_DWORD(txसमय, PTP_OUT_TRANSMIT_MINOR),
		ptp_data->ts_corrections.ptp_tx);

	skb_tstamp_tx(skb, &बारtamps);

	rc = 0;

fail:
	dev_kमुक्त_skb_any(skb);

	वापस;
पूर्ण

अटल व्योम efx_ptp_drop_समय_expired_events(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;
	काष्ठा list_head *cursor;
	काष्ठा list_head *next;

	अगर (ptp->rx_ts_अंतरभूत)
		वापस;

	/* Drop समय-expired events */
	spin_lock_bh(&ptp->evt_lock);
	list_क्रम_each_safe(cursor, next, &ptp->evt_list) अणु
		काष्ठा efx_ptp_event_rx *evt;

		evt = list_entry(cursor, काष्ठा efx_ptp_event_rx,
				 link);
		अगर (समय_after(jअगरfies, evt->expiry)) अणु
			list_move(&evt->link, &ptp->evt_मुक्त_list);
			netअगर_warn(efx, hw, efx->net_dev,
				   "PTP rx event dropped\n");
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ptp->evt_lock);
पूर्ण

अटल क्रमागत ptp_packet_state efx_ptp_match_rx(काष्ठा efx_nic *efx,
					      काष्ठा sk_buff *skb)
अणु
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;
	bool evts_रुकोing;
	काष्ठा list_head *cursor;
	काष्ठा list_head *next;
	काष्ठा efx_ptp_match *match;
	क्रमागत ptp_packet_state rc = PTP_PACKET_STATE_UNMATCHED;

	WARN_ON_ONCE(ptp->rx_ts_अंतरभूत);

	spin_lock_bh(&ptp->evt_lock);
	evts_रुकोing = !list_empty(&ptp->evt_list);
	spin_unlock_bh(&ptp->evt_lock);

	अगर (!evts_रुकोing)
		वापस PTP_PACKET_STATE_UNMATCHED;

	match = (काष्ठा efx_ptp_match *)skb->cb;
	/* Look क्रम a matching बारtamp in the event queue */
	spin_lock_bh(&ptp->evt_lock);
	list_क्रम_each_safe(cursor, next, &ptp->evt_list) अणु
		काष्ठा efx_ptp_event_rx *evt;

		evt = list_entry(cursor, काष्ठा efx_ptp_event_rx, link);
		अगर ((evt->seq0 == match->words[0]) &&
		    (evt->seq1 == match->words[1])) अणु
			काष्ठा skb_shared_hwtstamps *बारtamps;

			/* Match - add in hardware बारtamp */
			बारtamps = skb_hwtstamps(skb);
			बारtamps->hwtstamp = evt->hwबारtamp;

			match->state = PTP_PACKET_STATE_MATCHED;
			rc = PTP_PACKET_STATE_MATCHED;
			list_move(&evt->link, &ptp->evt_मुक्त_list);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ptp->evt_lock);

	वापस rc;
पूर्ण

/* Process any queued receive events and corresponding packets
 *
 * q is वापसed with all the packets that are पढ़ोy क्रम delivery.
 */
अटल व्योम efx_ptp_process_events(काष्ठा efx_nic *efx, काष्ठा sk_buff_head *q)
अणु
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&ptp->rxq))) अणु
		काष्ठा efx_ptp_match *match;

		match = (काष्ठा efx_ptp_match *)skb->cb;
		अगर (match->state == PTP_PACKET_STATE_MATCH_UNWANTED) अणु
			__skb_queue_tail(q, skb);
		पूर्ण अन्यथा अगर (efx_ptp_match_rx(efx, skb) ==
			   PTP_PACKET_STATE_MATCHED) अणु
			__skb_queue_tail(q, skb);
		पूर्ण अन्यथा अगर (समय_after(jअगरfies, match->expiry)) अणु
			match->state = PTP_PACKET_STATE_TIMED_OUT;
			++ptp->rx_no_बारtamp;
			__skb_queue_tail(q, skb);
		पूर्ण अन्यथा अणु
			/* Replace unprocessed entry and stop */
			skb_queue_head(&ptp->rxq, skb);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* Complete processing of a received packet */
अटल अंतरभूत व्योम efx_ptp_process_rx(काष्ठा efx_nic *efx, काष्ठा sk_buff *skb)
अणु
	local_bh_disable();
	netअगर_receive_skb(skb);
	local_bh_enable();
पूर्ण

अटल व्योम efx_ptp_हटाओ_multicast_filters(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;

	अगर (ptp->rxfilter_installed) अणु
		efx_filter_हटाओ_id_safe(efx, EFX_FILTER_PRI_REQUIRED,
					  ptp->rxfilter_general);
		efx_filter_हटाओ_id_safe(efx, EFX_FILTER_PRI_REQUIRED,
					  ptp->rxfilter_event);
		ptp->rxfilter_installed = false;
	पूर्ण
पूर्ण

अटल पूर्णांक efx_ptp_insert_multicast_filters(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;
	काष्ठा efx_filter_spec rxfilter;
	पूर्णांक rc;

	अगर (!ptp->channel || ptp->rxfilter_installed)
		वापस 0;

	/* Must filter on both event and general ports to ensure
	 * that there is no packet re-ordering.
	 */
	efx_filter_init_rx(&rxfilter, EFX_FILTER_PRI_REQUIRED, 0,
			   efx_rx_queue_index(
				   efx_channel_get_rx_queue(ptp->channel)));
	rc = efx_filter_set_ipv4_local(&rxfilter, IPPROTO_UDP,
				       htonl(PTP_ADDRESS),
				       htons(PTP_EVENT_PORT));
	अगर (rc != 0)
		वापस rc;

	rc = efx_filter_insert_filter(efx, &rxfilter, true);
	अगर (rc < 0)
		वापस rc;
	ptp->rxfilter_event = rc;

	efx_filter_init_rx(&rxfilter, EFX_FILTER_PRI_REQUIRED, 0,
			   efx_rx_queue_index(
				   efx_channel_get_rx_queue(ptp->channel)));
	rc = efx_filter_set_ipv4_local(&rxfilter, IPPROTO_UDP,
				       htonl(PTP_ADDRESS),
				       htons(PTP_GENERAL_PORT));
	अगर (rc != 0)
		जाओ fail;

	rc = efx_filter_insert_filter(efx, &rxfilter, true);
	अगर (rc < 0)
		जाओ fail;
	ptp->rxfilter_general = rc;

	ptp->rxfilter_installed = true;
	वापस 0;

fail:
	efx_filter_हटाओ_id_safe(efx, EFX_FILTER_PRI_REQUIRED,
				  ptp->rxfilter_event);
	वापस rc;
पूर्ण

अटल पूर्णांक efx_ptp_start(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;
	पूर्णांक rc;

	ptp->reset_required = false;

	rc = efx_ptp_insert_multicast_filters(efx);
	अगर (rc)
		वापस rc;

	rc = efx_ptp_enable(efx);
	अगर (rc != 0)
		जाओ fail;

	ptp->evt_frag_idx = 0;
	ptp->current_adjfreq = 0;

	वापस 0;

fail:
	efx_ptp_हटाओ_multicast_filters(efx);
	वापस rc;
पूर्ण

अटल पूर्णांक efx_ptp_stop(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;
	काष्ठा list_head *cursor;
	काष्ठा list_head *next;
	पूर्णांक rc;

	अगर (ptp == शून्य)
		वापस 0;

	rc = efx_ptp_disable(efx);

	efx_ptp_हटाओ_multicast_filters(efx);

	/* Make sure RX packets are really delivered */
	efx_ptp_deliver_rx_queue(&efx->ptp_data->rxq);
	skb_queue_purge(&efx->ptp_data->txq);

	/* Drop any pending receive events */
	spin_lock_bh(&efx->ptp_data->evt_lock);
	list_क्रम_each_safe(cursor, next, &efx->ptp_data->evt_list) अणु
		list_move(cursor, &efx->ptp_data->evt_मुक्त_list);
	पूर्ण
	spin_unlock_bh(&efx->ptp_data->evt_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक efx_ptp_restart(काष्ठा efx_nic *efx)
अणु
	अगर (efx->ptp_data && efx->ptp_data->enabled)
		वापस efx_ptp_start(efx);
	वापस 0;
पूर्ण

अटल व्योम efx_ptp_pps_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा efx_ptp_data *ptp =
		container_of(work, काष्ठा efx_ptp_data, pps_work);
	काष्ठा efx_nic *efx = ptp->efx;
	काष्ठा ptp_घड़ी_event ptp_evt;

	अगर (efx_ptp_synchronize(efx, PTP_SYNC_ATTEMPTS))
		वापस;

	ptp_evt.type = PTP_CLOCK_PPSUSR;
	ptp_evt.pps_बार = ptp->host_समय_pps;
	ptp_घड़ी_event(ptp->phc_घड़ी, &ptp_evt);
पूर्ण

अटल व्योम efx_ptp_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा efx_ptp_data *ptp_data =
		container_of(work, काष्ठा efx_ptp_data, work);
	काष्ठा efx_nic *efx = ptp_data->efx;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff_head tempq;

	अगर (ptp_data->reset_required) अणु
		efx_ptp_stop(efx);
		efx_ptp_start(efx);
		वापस;
	पूर्ण

	efx_ptp_drop_समय_expired_events(efx);

	__skb_queue_head_init(&tempq);
	efx_ptp_process_events(efx, &tempq);

	जबतक ((skb = skb_dequeue(&ptp_data->txq)))
		ptp_data->xmit_skb(efx, skb);

	जबतक ((skb = __skb_dequeue(&tempq)))
		efx_ptp_process_rx(efx, skb);
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info efx_phc_घड़ी_info = अणु
	.owner		= THIS_MODULE,
	.name		= "sfc",
	.max_adj	= MAX_PPB,
	.n_alarm	= 0,
	.n_ext_ts	= 0,
	.n_per_out	= 0,
	.n_pins		= 0,
	.pps		= 1,
	.adjfreq	= efx_phc_adjfreq,
	.adjसमय	= efx_phc_adjसमय,
	.समय_लो64	= efx_phc_समय_लो,
	.समय_रखो64	= efx_phc_समय_रखो,
	.enable		= efx_phc_enable,
पूर्ण;

/* Initialise PTP state. */
पूर्णांक efx_ptp_probe(काष्ठा efx_nic *efx, काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_ptp_data *ptp;
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक pos;

	ptp = kzalloc(माप(काष्ठा efx_ptp_data), GFP_KERNEL);
	efx->ptp_data = ptp;
	अगर (!efx->ptp_data)
		वापस -ENOMEM;

	ptp->efx = efx;
	ptp->channel = channel;
	ptp->rx_ts_अंतरभूत = efx_nic_rev(efx) >= EFX_REV_HUNT_A0;

	rc = efx_nic_alloc_buffer(efx, &ptp->start, माप(पूर्णांक), GFP_KERNEL);
	अगर (rc != 0)
		जाओ fail1;

	skb_queue_head_init(&ptp->rxq);
	skb_queue_head_init(&ptp->txq);
	ptp->workwq = create_singlethपढ़ो_workqueue("sfc_ptp");
	अगर (!ptp->workwq) अणु
		rc = -ENOMEM;
		जाओ fail2;
	पूर्ण

	अगर (efx_ptp_use_mac_tx_बारtamps(efx)) अणु
		ptp->xmit_skb = efx_ptp_xmit_skb_queue;
		/* Request sync events on this channel. */
		channel->sync_events_state = SYNC_EVENTS_QUIESCENT;
	पूर्ण अन्यथा अणु
		ptp->xmit_skb = efx_ptp_xmit_skb_mc;
	पूर्ण

	INIT_WORK(&ptp->work, efx_ptp_worker);
	ptp->config.flags = 0;
	ptp->config.tx_type = HWTSTAMP_TX_OFF;
	ptp->config.rx_filter = HWTSTAMP_FILTER_NONE;
	INIT_LIST_HEAD(&ptp->evt_list);
	INIT_LIST_HEAD(&ptp->evt_मुक्त_list);
	spin_lock_init(&ptp->evt_lock);
	क्रम (pos = 0; pos < MAX_RECEIVE_EVENTS; pos++)
		list_add(&ptp->rx_evts[pos].link, &ptp->evt_मुक्त_list);

	/* Get the NIC PTP attributes and set up समय conversions */
	rc = efx_ptp_get_attributes(efx);
	अगर (rc < 0)
		जाओ fail3;

	/* Get the बारtamp corrections */
	rc = efx_ptp_get_बारtamp_corrections(efx);
	अगर (rc < 0)
		जाओ fail3;

	अगर (efx->mcdi->fn_flags &
	    (1 << MC_CMD_DRV_ATTACH_EXT_OUT_FLAG_PRIMARY)) अणु
		ptp->phc_घड़ी_info = efx_phc_घड़ी_info;
		ptp->phc_घड़ी = ptp_घड़ी_रेजिस्टर(&ptp->phc_घड़ी_info,
						    &efx->pci_dev->dev);
		अगर (IS_ERR(ptp->phc_घड़ी)) अणु
			rc = PTR_ERR(ptp->phc_घड़ी);
			जाओ fail3;
		पूर्ण अन्यथा अगर (ptp->phc_घड़ी) अणु
			INIT_WORK(&ptp->pps_work, efx_ptp_pps_worker);
			ptp->pps_workwq = create_singlethपढ़ो_workqueue("sfc_pps");
			अगर (!ptp->pps_workwq) अणु
				rc = -ENOMEM;
				जाओ fail4;
			पूर्ण
		पूर्ण
	पूर्ण
	ptp->nic_ts_enabled = false;

	वापस 0;
fail4:
	ptp_घड़ी_unरेजिस्टर(efx->ptp_data->phc_घड़ी);

fail3:
	destroy_workqueue(efx->ptp_data->workwq);

fail2:
	efx_nic_मुक्त_buffer(efx, &ptp->start);

fail1:
	kमुक्त(efx->ptp_data);
	efx->ptp_data = शून्य;

	वापस rc;
पूर्ण

/* Initialise PTP channel.
 *
 * Setting core_index to zero causes the queue to be initialised and करोesn't
 * overlap with 'rxq0' because ptp.c doesn't use skb_record_rx_queue.
 */
अटल पूर्णांक efx_ptp_probe_channel(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	पूर्णांक rc;

	channel->irq_moderation_us = 0;
	channel->rx_queue.core_index = 0;

	rc = efx_ptp_probe(efx, channel);
	/* Failure to probe PTP is not fatal; this channel will just not be
	 * used क्रम anything.
	 * In the हाल of EPERM, efx_ptp_probe will prपूर्णांक its own message (in
	 * efx_ptp_get_attributes()), so we करोn't need to.
	 */
	अगर (rc && rc != -EPERM)
		netअगर_warn(efx, drv, efx->net_dev,
			   "Failed to probe PTP, rc=%d\n", rc);
	वापस 0;
पूर्ण

व्योम efx_ptp_हटाओ(काष्ठा efx_nic *efx)
अणु
	अगर (!efx->ptp_data)
		वापस;

	(व्योम)efx_ptp_disable(efx);

	cancel_work_sync(&efx->ptp_data->work);
	अगर (efx->ptp_data->pps_workwq)
		cancel_work_sync(&efx->ptp_data->pps_work);

	skb_queue_purge(&efx->ptp_data->rxq);
	skb_queue_purge(&efx->ptp_data->txq);

	अगर (efx->ptp_data->phc_घड़ी) अणु
		destroy_workqueue(efx->ptp_data->pps_workwq);
		ptp_घड़ी_unरेजिस्टर(efx->ptp_data->phc_घड़ी);
	पूर्ण

	destroy_workqueue(efx->ptp_data->workwq);

	efx_nic_मुक्त_buffer(efx, &efx->ptp_data->start);
	kमुक्त(efx->ptp_data);
	efx->ptp_data = शून्य;
पूर्ण

अटल व्योम efx_ptp_हटाओ_channel(काष्ठा efx_channel *channel)
अणु
	efx_ptp_हटाओ(channel->efx);
पूर्ण

अटल व्योम efx_ptp_get_channel_name(काष्ठा efx_channel *channel,
				     अक्षर *buf, माप_प्रकार len)
अणु
	snम_लिखो(buf, len, "%s-ptp", channel->efx->name);
पूर्ण

/* Determine whether this packet should be processed by the PTP module
 * or transmitted conventionally.
 */
bool efx_ptp_is_ptp_tx(काष्ठा efx_nic *efx, काष्ठा sk_buff *skb)
अणु
	वापस efx->ptp_data &&
		efx->ptp_data->enabled &&
		skb->len >= PTP_MIN_LENGTH &&
		skb->len <= MC_CMD_PTP_IN_TRANSMIT_PACKET_MAXNUM &&
		likely(skb->protocol == htons(ETH_P_IP)) &&
		skb_transport_header_was_set(skb) &&
		skb_network_header_len(skb) >= माप(काष्ठा iphdr) &&
		ip_hdr(skb)->protocol == IPPROTO_UDP &&
		skb_headlen(skb) >=
		skb_transport_offset(skb) + माप(काष्ठा udphdr) &&
		udp_hdr(skb)->dest == htons(PTP_EVENT_PORT);
पूर्ण

/* Receive a PTP packet.  Packets are queued until the arrival of
 * the receive बारtamp from the MC - this will probably occur after the
 * packet arrival because of the processing in the MC.
 */
अटल bool efx_ptp_rx(काष्ठा efx_channel *channel, काष्ठा sk_buff *skb)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;
	काष्ठा efx_ptp_match *match = (काष्ठा efx_ptp_match *)skb->cb;
	u8 *match_data_012, *match_data_345;
	अचिन्हित पूर्णांक version;
	u8 *data;

	match->expiry = jअगरfies + msecs_to_jअगरfies(PKT_EVENT_LIFETIME_MS);

	/* Correct version? */
	अगर (ptp->mode == MC_CMD_PTP_MODE_V1) अणु
		अगर (!pskb_may_pull(skb, PTP_V1_MIN_LENGTH)) अणु
			वापस false;
		पूर्ण
		data = skb->data;
		version = ntohs(*(__be16 *)&data[PTP_V1_VERSION_OFFSET]);
		अगर (version != PTP_VERSION_V1) अणु
			वापस false;
		पूर्ण

		/* PTP V1 uses all six bytes of the UUID to match the packet
		 * to the बारtamp
		 */
		match_data_012 = data + PTP_V1_UUID_OFFSET;
		match_data_345 = data + PTP_V1_UUID_OFFSET + 3;
	पूर्ण अन्यथा अणु
		अगर (!pskb_may_pull(skb, PTP_V2_MIN_LENGTH)) अणु
			वापस false;
		पूर्ण
		data = skb->data;
		version = data[PTP_V2_VERSION_OFFSET];
		अगर ((version & PTP_VERSION_V2_MASK) != PTP_VERSION_V2) अणु
			वापस false;
		पूर्ण

		/* The original V2 implementation uses bytes 2-7 of
		 * the UUID to match the packet to the बारtamp. This
		 * discards two of the bytes of the MAC address used
		 * to create the UUID (SF bug 33070).  The PTP V2
		 * enhanced mode fixes this issue and uses bytes 0-2
		 * and byte 5-7 of the UUID.
		 */
		match_data_345 = data + PTP_V2_UUID_OFFSET + 5;
		अगर (ptp->mode == MC_CMD_PTP_MODE_V2) अणु
			match_data_012 = data + PTP_V2_UUID_OFFSET + 2;
		पूर्ण अन्यथा अणु
			match_data_012 = data + PTP_V2_UUID_OFFSET + 0;
			BUG_ON(ptp->mode != MC_CMD_PTP_MODE_V2_ENHANCED);
		पूर्ण
	पूर्ण

	/* Does this packet require बारtamping? */
	अगर (ntohs(*(__be16 *)&data[PTP_DPORT_OFFSET]) == PTP_EVENT_PORT) अणु
		match->state = PTP_PACKET_STATE_UNMATCHED;

		/* We expect the sequence number to be in the same position in
		 * the packet क्रम PTP V1 and V2
		 */
		BUILD_BUG_ON(PTP_V1_SEQUENCE_OFFSET != PTP_V2_SEQUENCE_OFFSET);
		BUILD_BUG_ON(PTP_V1_SEQUENCE_LENGTH != PTP_V2_SEQUENCE_LENGTH);

		/* Extract UUID/Sequence inक्रमmation */
		match->words[0] = (match_data_012[0]         |
				   (match_data_012[1] << 8)  |
				   (match_data_012[2] << 16) |
				   (match_data_345[0] << 24));
		match->words[1] = (match_data_345[1]         |
				   (match_data_345[2] << 8)  |
				   (data[PTP_V1_SEQUENCE_OFFSET +
					 PTP_V1_SEQUENCE_LENGTH - 1] <<
				    16));
	पूर्ण अन्यथा अणु
		match->state = PTP_PACKET_STATE_MATCH_UNWANTED;
	पूर्ण

	skb_queue_tail(&ptp->rxq, skb);
	queue_work(ptp->workwq, &ptp->work);

	वापस true;
पूर्ण

/* Transmit a PTP packet.  This has to be transmitted by the MC
 * itself, through an MCDI call.  MCDI calls aren't permitted
 * in the transmit path so defer the actual transmission to a suitable worker.
 */
पूर्णांक efx_ptp_tx(काष्ठा efx_nic *efx, काष्ठा sk_buff *skb)
अणु
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;

	skb_queue_tail(&ptp->txq, skb);

	अगर ((udp_hdr(skb)->dest == htons(PTP_EVENT_PORT)) &&
	    (skb->len <= MC_CMD_PTP_IN_TRANSMIT_PACKET_MAXNUM))
		efx_xmit_hwtstamp_pending(skb);
	queue_work(ptp->workwq, &ptp->work);

	वापस NETDEV_TX_OK;
पूर्ण

पूर्णांक efx_ptp_get_mode(काष्ठा efx_nic *efx)
अणु
	वापस efx->ptp_data->mode;
पूर्ण

पूर्णांक efx_ptp_change_mode(काष्ठा efx_nic *efx, bool enable_wanted,
			अचिन्हित पूर्णांक new_mode)
अणु
	अगर ((enable_wanted != efx->ptp_data->enabled) ||
	    (enable_wanted && (efx->ptp_data->mode != new_mode))) अणु
		पूर्णांक rc = 0;

		अगर (enable_wanted) अणु
			/* Change of mode requires disable */
			अगर (efx->ptp_data->enabled &&
			    (efx->ptp_data->mode != new_mode)) अणु
				efx->ptp_data->enabled = false;
				rc = efx_ptp_stop(efx);
				अगर (rc != 0)
					वापस rc;
			पूर्ण

			/* Set new operating mode and establish
			 * baseline synchronisation, which must
			 * succeed.
			 */
			efx->ptp_data->mode = new_mode;
			अगर (netअगर_running(efx->net_dev))
				rc = efx_ptp_start(efx);
			अगर (rc == 0) अणु
				rc = efx_ptp_synchronize(efx,
							 PTP_SYNC_ATTEMPTS * 2);
				अगर (rc != 0)
					efx_ptp_stop(efx);
			पूर्ण
		पूर्ण अन्यथा अणु
			rc = efx_ptp_stop(efx);
		पूर्ण

		अगर (rc != 0)
			वापस rc;

		efx->ptp_data->enabled = enable_wanted;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक efx_ptp_ts_init(काष्ठा efx_nic *efx, काष्ठा hwtstamp_config *init)
अणु
	पूर्णांक rc;

	अगर (init->flags)
		वापस -EINVAL;

	अगर ((init->tx_type != HWTSTAMP_TX_OFF) &&
	    (init->tx_type != HWTSTAMP_TX_ON))
		वापस -दुस्फल;

	rc = efx->type->ptp_set_ts_config(efx, init);
	अगर (rc)
		वापस rc;

	efx->ptp_data->config = *init;
	वापस 0;
पूर्ण

व्योम efx_ptp_get_ts_info(काष्ठा efx_nic *efx, काष्ठा ethtool_ts_info *ts_info)
अणु
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;
	काष्ठा efx_nic *primary = efx->primary;

	ASSERT_RTNL();

	अगर (!ptp)
		वापस;

	ts_info->so_बारtamping |= (SOF_TIMESTAMPING_TX_HARDWARE |
				     SOF_TIMESTAMPING_RX_HARDWARE |
				     SOF_TIMESTAMPING_RAW_HARDWARE);
	/* Check licensed features.  If we करोn't have the license क्रम TX
	 * बारtamps, the NIC will not support them.
	 */
	अगर (efx_ptp_use_mac_tx_बारtamps(efx)) अणु
		काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

		अगर (!(nic_data->licensed_features &
		      (1 << LICENSED_V3_FEATURES_TX_TIMESTAMPS_LBN)))
			ts_info->so_बारtamping &=
				~SOF_TIMESTAMPING_TX_HARDWARE;
	पूर्ण
	अगर (primary && primary->ptp_data && primary->ptp_data->phc_घड़ी)
		ts_info->phc_index =
			ptp_घड़ी_index(primary->ptp_data->phc_घड़ी);
	ts_info->tx_types = 1 << HWTSTAMP_TX_OFF | 1 << HWTSTAMP_TX_ON;
	ts_info->rx_filters = ptp->efx->type->hwtstamp_filters;
पूर्ण

पूर्णांक efx_ptp_set_ts_config(काष्ठा efx_nic *efx, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;
	पूर्णांक rc;

	/* Not a PTP enabled port */
	अगर (!efx->ptp_data)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	rc = efx_ptp_ts_init(efx, &config);
	अगर (rc != 0)
		वापस rc;

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config))
		? -EFAULT : 0;
पूर्ण

पूर्णांक efx_ptp_get_ts_config(काष्ठा efx_nic *efx, काष्ठा अगरreq *अगरr)
अणु
	अगर (!efx->ptp_data)
		वापस -EOPNOTSUPP;

	वापस copy_to_user(अगरr->अगरr_data, &efx->ptp_data->config,
			    माप(efx->ptp_data->config)) ? -EFAULT : 0;
पूर्ण

अटल व्योम ptp_event_failure(काष्ठा efx_nic *efx, पूर्णांक expected_frag_len)
अणु
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;

	netअगर_err(efx, hw, efx->net_dev,
		"PTP unexpected event length: got %d expected %d\n",
		ptp->evt_frag_idx, expected_frag_len);
	ptp->reset_required = true;
	queue_work(ptp->workwq, &ptp->work);
पूर्ण

/* Process a completed receive event.  Put it on the event queue and
 * start worker thपढ़ो.  This is required because event and their
 * correspoding packets may come in either order.
 */
अटल व्योम ptp_event_rx(काष्ठा efx_nic *efx, काष्ठा efx_ptp_data *ptp)
अणु
	काष्ठा efx_ptp_event_rx *evt = शून्य;

	अगर (WARN_ON_ONCE(ptp->rx_ts_अंतरभूत))
		वापस;

	अगर (ptp->evt_frag_idx != 3) अणु
		ptp_event_failure(efx, 3);
		वापस;
	पूर्ण

	spin_lock_bh(&ptp->evt_lock);
	अगर (!list_empty(&ptp->evt_मुक्त_list)) अणु
		evt = list_first_entry(&ptp->evt_मुक्त_list,
				       काष्ठा efx_ptp_event_rx, link);
		list_del(&evt->link);

		evt->seq0 = EFX_QWORD_FIELD(ptp->evt_frags[2], MCDI_EVENT_DATA);
		evt->seq1 = (EFX_QWORD_FIELD(ptp->evt_frags[2],
					     MCDI_EVENT_SRC)        |
			     (EFX_QWORD_FIELD(ptp->evt_frags[1],
					      MCDI_EVENT_SRC) << 8) |
			     (EFX_QWORD_FIELD(ptp->evt_frags[0],
					      MCDI_EVENT_SRC) << 16));
		evt->hwबारtamp = efx->ptp_data->nic_to_kernel_समय(
			EFX_QWORD_FIELD(ptp->evt_frags[0], MCDI_EVENT_DATA),
			EFX_QWORD_FIELD(ptp->evt_frags[1], MCDI_EVENT_DATA),
			ptp->ts_corrections.ptp_rx);
		evt->expiry = jअगरfies + msecs_to_jअगरfies(PKT_EVENT_LIFETIME_MS);
		list_add_tail(&evt->link, &ptp->evt_list);

		queue_work(ptp->workwq, &ptp->work);
	पूर्ण अन्यथा अगर (net_ratelimit()) अणु
		/* Log a rate-limited warning message. */
		netअगर_err(efx, rx_err, efx->net_dev, "PTP event queue overflow\n");
	पूर्ण
	spin_unlock_bh(&ptp->evt_lock);
पूर्ण

अटल व्योम ptp_event_fault(काष्ठा efx_nic *efx, काष्ठा efx_ptp_data *ptp)
अणु
	पूर्णांक code = EFX_QWORD_FIELD(ptp->evt_frags[0], MCDI_EVENT_DATA);
	अगर (ptp->evt_frag_idx != 1) अणु
		ptp_event_failure(efx, 1);
		वापस;
	पूर्ण

	netअगर_err(efx, hw, efx->net_dev, "PTP error %d\n", code);
पूर्ण

अटल व्योम ptp_event_pps(काष्ठा efx_nic *efx, काष्ठा efx_ptp_data *ptp)
अणु
	अगर (ptp->nic_ts_enabled)
		queue_work(ptp->pps_workwq, &ptp->pps_work);
पूर्ण

व्योम efx_ptp_event(काष्ठा efx_nic *efx, efx_qword_t *ev)
अणु
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;
	पूर्णांक code = EFX_QWORD_FIELD(*ev, MCDI_EVENT_CODE);

	अगर (!ptp) अणु
		अगर (!efx->ptp_warned) अणु
			netअगर_warn(efx, drv, efx->net_dev,
				   "Received PTP event but PTP not set up\n");
			efx->ptp_warned = true;
		पूर्ण
		वापस;
	पूर्ण

	अगर (!ptp->enabled)
		वापस;

	अगर (ptp->evt_frag_idx == 0) अणु
		ptp->evt_code = code;
	पूर्ण अन्यथा अगर (ptp->evt_code != code) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "PTP out of sequence event %d\n", code);
		ptp->evt_frag_idx = 0;
	पूर्ण

	ptp->evt_frags[ptp->evt_frag_idx++] = *ev;
	अगर (!MCDI_EVENT_FIELD(*ev, CONT)) अणु
		/* Process resulting event */
		चयन (code) अणु
		हाल MCDI_EVENT_CODE_PTP_RX:
			ptp_event_rx(efx, ptp);
			अवरोध;
		हाल MCDI_EVENT_CODE_PTP_FAULT:
			ptp_event_fault(efx, ptp);
			अवरोध;
		हाल MCDI_EVENT_CODE_PTP_PPS:
			ptp_event_pps(efx, ptp);
			अवरोध;
		शेष:
			netअगर_err(efx, hw, efx->net_dev,
				  "PTP unknown event %d\n", code);
			अवरोध;
		पूर्ण
		ptp->evt_frag_idx = 0;
	पूर्ण अन्यथा अगर (MAX_EVENT_FRAGS == ptp->evt_frag_idx) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "PTP too many event fragments\n");
		ptp->evt_frag_idx = 0;
	पूर्ण
पूर्ण

व्योम efx_समय_sync_event(काष्ठा efx_channel *channel, efx_qword_t *ev)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;

	/* When extracting the sync बारtamp minor value, we should discard
	 * the least signअगरicant two bits. These are not required in order
	 * to reस्थिरruct full-range बारtamps and they are optionally used
	 * to report status depending on the options supplied when subscribing
	 * क्रम sync events.
	 */
	channel->sync_बारtamp_major = MCDI_EVENT_FIELD(*ev, PTP_TIME_MAJOR);
	channel->sync_बारtamp_minor =
		(MCDI_EVENT_FIELD(*ev, PTP_TIME_MINOR_MS_8BITS) & 0xFC)
			<< ptp->nic_समय.sync_event_minor_shअगरt;

	/* अगर sync events have been disabled then we want to silently ignore
	 * this event, so throw away result.
	 */
	(व्योम) cmpxchg(&channel->sync_events_state, SYNC_EVENTS_REQUESTED,
		       SYNC_EVENTS_VALID);
पूर्ण

अटल अंतरभूत u32 efx_rx_buf_बारtamp_minor(काष्ठा efx_nic *efx, स्थिर u8 *eh)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	वापस __le32_to_cpup((स्थिर __le32 *)(eh + efx->rx_packet_ts_offset));
#अन्यथा
	स्थिर u8 *data = eh + efx->rx_packet_ts_offset;
	वापस (u32)data[0]       |
	       (u32)data[1] << 8  |
	       (u32)data[2] << 16 |
	       (u32)data[3] << 24;
#पूर्ण_अगर
पूर्ण

व्योम __efx_rx_skb_attach_बारtamp(काष्ठा efx_channel *channel,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	काष्ठा efx_ptp_data *ptp = efx->ptp_data;
	u32 pkt_बारtamp_major, pkt_बारtamp_minor;
	u32 dअगरf, carry;
	काष्ठा skb_shared_hwtstamps *बारtamps;

	अगर (channel->sync_events_state != SYNC_EVENTS_VALID)
		वापस;

	pkt_बारtamp_minor = efx_rx_buf_बारtamp_minor(efx, skb_mac_header(skb));

	/* get the dअगरference between the packet and sync बारtamps,
	 * modulo one second
	 */
	dअगरf = pkt_बारtamp_minor - channel->sync_बारtamp_minor;
	अगर (pkt_बारtamp_minor < channel->sync_बारtamp_minor)
		dअगरf += ptp->nic_समय.minor_max;

	/* करो we roll over a second boundary and need to carry the one? */
	carry = (channel->sync_बारtamp_minor >= ptp->nic_समय.minor_max - dअगरf) ?
		1 : 0;

	अगर (dअगरf <= ptp->nic_समय.sync_event_dअगरf_max) अणु
		/* packet is ahead of the sync event by a quarter of a second or
		 * less (allowing क्रम fuzz)
		 */
		pkt_बारtamp_major = channel->sync_बारtamp_major + carry;
	पूर्ण अन्यथा अगर (dअगरf >= ptp->nic_समय.sync_event_dअगरf_min) अणु
		/* packet is behind the sync event but within the fuzz factor.
		 * This means the RX packet and sync event crossed as they were
		 * placed on the event queue, which can someबार happen.
		 */
		pkt_बारtamp_major = channel->sync_बारtamp_major - 1 + carry;
	पूर्ण अन्यथा अणु
		/* it's outside tolerance in both directions. this might be
		 * indicative of us missing sync events क्रम some reason, so
		 * we'll call it an error rather than risk giving a bogus
		 * बारtamp.
		 */
		netअगर_vdbg(efx, drv, efx->net_dev,
			  "packet timestamp %x too far from sync event %x:%x\n",
			  pkt_बारtamp_minor, channel->sync_बारtamp_major,
			  channel->sync_बारtamp_minor);
		वापस;
	पूर्ण

	/* attach the बारtamps to the skb */
	बारtamps = skb_hwtstamps(skb);
	बारtamps->hwtstamp =
		ptp->nic_to_kernel_समय(pkt_बारtamp_major,
					pkt_बारtamp_minor,
					ptp->ts_corrections.general_rx);
पूर्ण

अटल पूर्णांक efx_phc_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 delta)
अणु
	काष्ठा efx_ptp_data *ptp_data = container_of(ptp,
						     काष्ठा efx_ptp_data,
						     phc_घड़ी_info);
	काष्ठा efx_nic *efx = ptp_data->efx;
	MCDI_DECLARE_BUF(inadj, MC_CMD_PTP_IN_ADJUST_LEN);
	s64 adjusपंचांगent_ns;
	पूर्णांक rc;

	अगर (delta > MAX_PPB)
		delta = MAX_PPB;
	अन्यथा अगर (delta < -MAX_PPB)
		delta = -MAX_PPB;

	/* Convert ppb to fixed poपूर्णांक ns taking care to round correctly. */
	adjusपंचांगent_ns = ((s64)delta * PPB_SCALE_WORD +
			 (1 << (ptp_data->adjfreq_ppb_shअगरt - 1))) >>
			ptp_data->adjfreq_ppb_shअगरt;

	MCDI_SET_DWORD(inadj, PTP_IN_OP, MC_CMD_PTP_OP_ADJUST);
	MCDI_SET_DWORD(inadj, PTP_IN_PERIPH_ID, 0);
	MCDI_SET_QWORD(inadj, PTP_IN_ADJUST_FREQ, adjusपंचांगent_ns);
	MCDI_SET_DWORD(inadj, PTP_IN_ADJUST_SECONDS, 0);
	MCDI_SET_DWORD(inadj, PTP_IN_ADJUST_न_अंकOSECONDS, 0);
	rc = efx_mcdi_rpc(efx, MC_CMD_PTP, inadj, माप(inadj),
			  शून्य, 0, शून्य);
	अगर (rc != 0)
		वापस rc;

	ptp_data->current_adjfreq = adjusपंचांगent_ns;
	वापस 0;
पूर्ण

अटल पूर्णांक efx_phc_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	u32 nic_major, nic_minor;
	काष्ठा efx_ptp_data *ptp_data = container_of(ptp,
						     काष्ठा efx_ptp_data,
						     phc_घड़ी_info);
	काष्ठा efx_nic *efx = ptp_data->efx;
	MCDI_DECLARE_BUF(inbuf, MC_CMD_PTP_IN_ADJUST_LEN);

	efx->ptp_data->ns_to_nic_समय(delta, &nic_major, &nic_minor);

	MCDI_SET_DWORD(inbuf, PTP_IN_OP, MC_CMD_PTP_OP_ADJUST);
	MCDI_SET_DWORD(inbuf, PTP_IN_PERIPH_ID, 0);
	MCDI_SET_QWORD(inbuf, PTP_IN_ADJUST_FREQ, ptp_data->current_adjfreq);
	MCDI_SET_DWORD(inbuf, PTP_IN_ADJUST_MAJOR, nic_major);
	MCDI_SET_DWORD(inbuf, PTP_IN_ADJUST_MINOR, nic_minor);
	वापस efx_mcdi_rpc(efx, MC_CMD_PTP, inbuf, माप(inbuf),
			    शून्य, 0, शून्य);
पूर्ण

अटल पूर्णांक efx_phc_समय_लो(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	काष्ठा efx_ptp_data *ptp_data = container_of(ptp,
						     काष्ठा efx_ptp_data,
						     phc_घड़ी_info);
	काष्ठा efx_nic *efx = ptp_data->efx;
	MCDI_DECLARE_BUF(inbuf, MC_CMD_PTP_IN_READ_NIC_TIME_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_PTP_OUT_READ_NIC_TIME_LEN);
	पूर्णांक rc;
	kसमय_प्रकार kt;

	MCDI_SET_DWORD(inbuf, PTP_IN_OP, MC_CMD_PTP_OP_READ_NIC_TIME);
	MCDI_SET_DWORD(inbuf, PTP_IN_PERIPH_ID, 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_PTP, inbuf, माप(inbuf),
			  outbuf, माप(outbuf), शून्य);
	अगर (rc != 0)
		वापस rc;

	kt = ptp_data->nic_to_kernel_समय(
		MCDI_DWORD(outbuf, PTP_OUT_READ_NIC_TIME_MAJOR),
		MCDI_DWORD(outbuf, PTP_OUT_READ_NIC_TIME_MINOR), 0);
	*ts = kसमय_प्रकारo_बारpec64(kt);
	वापस 0;
पूर्ण

अटल पूर्णांक efx_phc_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			   स्थिर काष्ठा बारpec64 *e_ts)
अणु
	/* Get the current NIC समय, efx_phc_समय_लो.
	 * Subtract from the desired समय to get the offset
	 * call efx_phc_adjसमय with the offset
	 */
	पूर्णांक rc;
	काष्ठा बारpec64 समय_now;
	काष्ठा बारpec64 delta;

	rc = efx_phc_समय_लो(ptp, &समय_now);
	अगर (rc != 0)
		वापस rc;

	delta = बारpec64_sub(*e_ts, समय_now);

	rc = efx_phc_adjसमय(ptp, बारpec64_to_ns(&delta));
	अगर (rc != 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक efx_phc_enable(काष्ठा ptp_घड़ी_info *ptp,
			  काष्ठा ptp_घड़ी_request *request,
			  पूर्णांक enable)
अणु
	काष्ठा efx_ptp_data *ptp_data = container_of(ptp,
						     काष्ठा efx_ptp_data,
						     phc_घड़ी_info);
	अगर (request->type != PTP_CLK_REQ_PPS)
		वापस -EOPNOTSUPP;

	ptp_data->nic_ts_enabled = !!enable;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा efx_channel_type efx_ptp_channel_type = अणु
	.handle_no_channel	= efx_ptp_handle_no_channel,
	.pre_probe		= efx_ptp_probe_channel,
	.post_हटाओ		= efx_ptp_हटाओ_channel,
	.get_name		= efx_ptp_get_channel_name,
	/* no copy operation; there is no need to पुनः_स्मृतिate this channel */
	.receive_skb		= efx_ptp_rx,
	.want_txqs		= efx_ptp_want_txqs,
	.keep_eventq		= false,
पूर्ण;

व्योम efx_ptp_defer_probe_with_channel(काष्ठा efx_nic *efx)
अणु
	/* Check whether PTP is implemented on this NIC.  The DISABLE
	 * operation will succeed अगर and only अगर it is implemented.
	 */
	अगर (efx_ptp_disable(efx) == 0)
		efx->extra_channel_type[EFX_EXTRA_CHANNEL_PTP] =
			&efx_ptp_channel_type;
पूर्ण

व्योम efx_ptp_start_datapath(काष्ठा efx_nic *efx)
अणु
	अगर (efx_ptp_restart(efx))
		netअगर_err(efx, drv, efx->net_dev, "Failed to restart PTP.\n");
	/* re-enable बारtamping अगर it was previously enabled */
	अगर (efx->type->ptp_set_ts_sync_events)
		efx->type->ptp_set_ts_sync_events(efx, true, true);
पूर्ण

व्योम efx_ptp_stop_datapath(काष्ठा efx_nic *efx)
अणु
	/* temporarily disable बारtamping */
	अगर (efx->type->ptp_set_ts_sync_events)
		efx->type->ptp_set_ts_sync_events(efx, false, true);
	efx_ptp_stop(efx);
पूर्ण
