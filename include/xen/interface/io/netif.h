<शैली गुरु>
/******************************************************************************
 * xen_netअगर.h
 *
 * Unअगरied network-device I/O पूर्णांकerface क्रम Xen guest OSes.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Copyright (c) 2003-2004, Keir Fraser
 */

#अगर_अघोषित __XEN_PUBLIC_IO_XEN_NETIF_H__
#घोषणा __XEN_PUBLIC_IO_XEN_NETIF_H__

#समावेश "ring.h"
#समावेश "../grant_table.h"

/*
 * Older implementation of Xen network frontend / backend has an
 * implicit dependency on the MAX_SKB_FRAGS as the maximum number of
 * ring slots a skb can use. Netfront / netback may not work as
 * expected when frontend and backend have dअगरferent MAX_SKB_FRAGS.
 *
 * A better approach is to add mechanism क्रम netfront / netback to
 * negotiate this value. However we cannot fix all possible
 * frontends, so we need to define a value which states the minimum
 * slots backend must support.
 *
 * The minimum value derives from older Linux kernel's MAX_SKB_FRAGS
 * (18), which is proved to work with most frontends. Any new backend
 * which करोesn't negotiate with frontend should expect frontend to
 * send a valid packet using slots up to this value.
 */
#घोषणा XEN_NETIF_NR_SLOTS_MIN 18

/*
 * Notअगरications after enqueuing any type of message should be conditional on
 * the appropriate req_event or rsp_event field in the shared ring.
 * If the client sends notअगरication क्रम rx requests then it should specअगरy
 * feature 'feature-rx-notify' via xenbus. Otherwise the backend will assume
 * that it cannot safely queue packets (as it may not be kicked to send them).
 */

/*
 * "feature-split-event-channels" is पूर्णांकroduced to separate guest TX
 * and RX notअगरication. Backend either करोesn't support this feature or
 * advertises it via xenstore as 0 (disabled) or 1 (enabled).
 *
 * To make use of this feature, frontend should allocate two event
 * channels क्रम TX and RX, advertise them to backend as
 * "event-channel-tx" and "event-channel-rx" respectively. If frontend
 * करोesn't want to use this feature, it just ग_लिखोs "event-channel"
 * node as beक्रमe.
 */

/*
 * Multiple transmit and receive queues:
 * If supported, the backend will ग_लिखो the key "multi-queue-max-queues" to
 * the directory क्रम that vअगर, and set its value to the maximum supported
 * number of queues.
 * Frontends that are aware of this feature and wish to use it can ग_लिखो the
 * key "multi-queue-num-queues", set to the number they wish to use, which
 * must be greater than zero, and no more than the value reported by the backend
 * in "multi-queue-max-queues".
 *
 * Queues replicate the shared rings and event channels.
 * "feature-split-event-channels" may optionally be used when using
 * multiple queues, but is not mandatory.
 *
 * Each queue consists of one shared ring pair, i.e. there must be the same
 * number of tx and rx rings.
 *
 * For frontends requesting just one queue, the usual event-channel and
 * ring-ref keys are written as beक्रमe, simplअगरying the backend processing
 * to aव्योम distinguishing between a frontend that करोesn't understand the
 * multi-queue feature, and one that करोes, but requested only one queue.
 *
 * Frontends requesting two or more queues must not ग_लिखो the toplevel
 * event-channel (or event-channel-अणुtx,rxपूर्ण) and अणुtx,rxपूर्ण-ring-ref keys,
 * instead writing those keys under sub-keys having the name "queue-N" where
 * N is the पूर्णांकeger ID of the queue क्रम which those keys beदीर्घ. Queues
 * are indexed from zero. For example, a frontend with two queues and split
 * event channels must ग_लिखो the following set of queue-related keys:
 *
 * /local/करोमुख्य/1/device/vअगर/0/multi-queue-num-queues = "2"
 * /local/करोमुख्य/1/device/vअगर/0/queue-0 = ""
 * /local/करोमुख्य/1/device/vअगर/0/queue-0/tx-ring-ref = "<ring-ref-tx0>"
 * /local/करोमुख्य/1/device/vअगर/0/queue-0/rx-ring-ref = "<ring-ref-rx0>"
 * /local/करोमुख्य/1/device/vअगर/0/queue-0/event-channel-tx = "<evtchn-tx0>"
 * /local/करोमुख्य/1/device/vअगर/0/queue-0/event-channel-rx = "<evtchn-rx0>"
 * /local/करोमुख्य/1/device/vअगर/0/queue-1 = ""
 * /local/करोमुख्य/1/device/vअगर/0/queue-1/tx-ring-ref = "<ring-ref-tx1>"
 * /local/करोमुख्य/1/device/vअगर/0/queue-1/rx-ring-ref = "<ring-ref-rx1"
 * /local/करोमुख्य/1/device/vअगर/0/queue-1/event-channel-tx = "<evtchn-tx1>"
 * /local/करोमुख्य/1/device/vअगर/0/queue-1/event-channel-rx = "<evtchn-rx1>"
 *
 * If there is any inconsistency in the XenStore data, the backend may
 * choose not to connect any queues, instead treating the request as an
 * error. This includes scenarios where more (or fewer) queues were
 * requested than the frontend provided details क्रम.
 *
 * Mapping of packets to queues is considered to be a function of the
 * transmitting प्रणाली (backend or frontend) and is not negotiated
 * between the two. Guests are मुक्त to transmit packets on any queue
 * they choose, provided it has been set up correctly. Guests must be
 * prepared to receive packets on any queue they have requested be set up.
 */

/*
 * "feature-no-csum-offload" should be used to turn IPv4 TCP/UDP checksum
 * offload off or on. If it is missing then the feature is assumed to be on.
 * "feature-ipv6-csum-offload" should be used to turn IPv6 TCP/UDP checksum
 * offload on or off. If it is missing then the feature is assumed to be off.
 */

/*
 * "feature-gso-tcpv4" and "feature-gso-tcpv6" advertise the capability to
 * handle large TCP packets (in IPv4 or IPv6 क्रमm respectively). Neither
 * frontends nor backends are assumed to be capable unless the flags are
 * present.
 */

/*
 * "feature-multicast-control" and "feature-dynamic-multicast-control"
 * advertise the capability to filter ethernet multicast packets in the
 * backend. If the frontend wishes to take advantage of this feature then
 * it may set "request-multicast-control". If the backend only advertises
 * "feature-multicast-control" then "request-multicast-control" must be set
 * beक्रमe the frontend moves पूर्णांकo the connected state. The backend will
 * sample the value on this state transition and any subsequent change in
 * value will have no effect. However, अगर the backend also advertises
 * "feature-dynamic-multicast-control" then "request-multicast-control"
 * may be set by the frontend at any समय. In this हाल, the backend will
 * watch the value and re-sample on watch events.
 *
 * If the sampled value of "request-multicast-control" is set then the
 * backend transmit side should no दीर्घer flood multicast packets to the
 * frontend, it should instead drop any multicast packet that करोes not
 * match in a filter list.
 * The list is amended by the frontend by sending dummy transmit requests
 * containing XEN_NETIF_EXTRA_TYPE_MCAST_अणुADD,DELपूर्ण extra-info fragments as
 * specअगरied below.
 * Note that the filter list may be amended even अगर the sampled value of
 * "request-multicast-control" is not set, however the filter should only
 * be applied अगर it is set.
 */

/*
 * "xdp-headroom" is used to request that extra space is added
 * क्रम XDP processing.  The value is measured in bytes and passed by
 * the frontend to be consistent between both ends.
 * If the value is greater than zero that means that
 * an RX response is going to be passed to an XDP program क्रम processing.
 * XEN_NETIF_MAX_XDP_HEADROOM defines the maximum headroom offset in bytes
 *
 * "feature-xdp-headroom" is set to "1" by the netback side like other features
 * so a guest can check अगर an XDP program can be processed.
 */
#घोषणा XEN_NETIF_MAX_XDP_HEADROOM 0x7FFF

/*
 * Control ring
 * ============
 *
 * Some features, such as hashing (detailed below), require a
 * signअगरicant amount of out-of-band data to be passed from frontend to
 * backend. Use of xenstore is not suitable क्रम large quantities of data
 * because of quota limitations and so a dedicated 'control ring' is used.
 * The ability of the backend to use a control ring is advertised by
 * setting:
 *
 * /local/करोमुख्य/X/backend/<करोmid>/<vअगर>/feature-ctrl-ring = "1"
 *
 * The frontend provides a control ring to the backend by setting:
 *
 * /local/करोमुख्य/<करोmid>/device/vअगर/<vअगर>/ctrl-ring-ref = <gref>
 * /local/करोमुख्य/<करोmid>/device/vअगर/<vअगर>/event-channel-ctrl = <port>
 *
 * where <gref> is the grant reference of the shared page used to
 * implement the control ring and <port> is an event channel to be used
 * as a mailbox पूर्णांकerrupt. These keys must be set beक्रमe the frontend
 * moves पूर्णांकo the connected state.
 *
 * The control ring uses a fixed request/response message size and is
 * balanced (i.e. one request to one response), so operationally it is much
 * the same as a transmit or receive ring.
 * Note that there is no requirement that responses are issued in the same
 * order as requests.
 */

/*
 * Hash types
 * ==========
 *
 * For the purposes of the definitions below, 'Packet[]' is an array of
 * octets containing an IP packet without options, 'Array[X..Y]' means a
 * sub-array of 'Array' containing bytes X thru Y inclusive, and '+' is
 * used to indicate concatenation of arrays.
 */

/*
 * A hash calculated over an IP version 4 header as follows:
 *
 * Buffer[0..8] = Packet[12..15] (source address) +
 *                Packet[16..19] (destination address)
 *
 * Result = Hash(Buffer, 8)
 */
#घोषणा _XEN_NETIF_CTRL_HASH_TYPE_IPV4 0
#घोषणा XEN_NETIF_CTRL_HASH_TYPE_IPV4 \
	(1 << _XEN_NETIF_CTRL_HASH_TYPE_IPV4)

/*
 * A hash calculated over an IP version 4 header and TCP header as
 * follows:
 *
 * Buffer[0..12] = Packet[12..15] (source address) +
 *                 Packet[16..19] (destination address) +
 *                 Packet[20..21] (source port) +
 *                 Packet[22..23] (destination port)
 *
 * Result = Hash(Buffer, 12)
 */
#घोषणा _XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP 1
#घोषणा XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP \
	(1 << _XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP)

/*
 * A hash calculated over an IP version 6 header as follows:
 *
 * Buffer[0..32] = Packet[8..23]  (source address ) +
 *                 Packet[24..39] (destination address)
 *
 * Result = Hash(Buffer, 32)
 */
#घोषणा _XEN_NETIF_CTRL_HASH_TYPE_IPV6 2
#घोषणा XEN_NETIF_CTRL_HASH_TYPE_IPV6 \
	(1 << _XEN_NETIF_CTRL_HASH_TYPE_IPV6)

/*
 * A hash calculated over an IP version 6 header and TCP header as
 * follows:
 *
 * Buffer[0..36] = Packet[8..23]  (source address) +
 *                 Packet[24..39] (destination address) +
 *                 Packet[40..41] (source port) +
 *                 Packet[42..43] (destination port)
 *
 * Result = Hash(Buffer, 36)
 */
#घोषणा _XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP 3
#घोषणा XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP \
	(1 << _XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP)

/*
 * Hash algorithms
 * ===============
 */

#घोषणा XEN_NETIF_CTRL_HASH_ALGORITHM_NONE 0

/*
 * Toeplitz hash:
 */

#घोषणा XEN_NETIF_CTRL_HASH_ALGORITHM_TOEPLITZ 1

/*
 * This algorithm uses a 'key' as well as the data buffer itself.
 * (Buffer[] and Key[] are treated as shअगरt-रेजिस्टरs where the MSB of
 * Buffer/Key[0] is considered 'left-most' and the LSB of Buffer/Key[N-1]
 * is the 'right-most').
 *
 * Value = 0
 * For number of bits in Buffer[]
 *    If (left-most bit of Buffer[] is 1)
 *        Value ^= left-most 32 bits of Key[]
 *    Key[] << 1
 *    Buffer[] << 1
 *
 * The code below is provided क्रम convenience where an operating प्रणाली
 * करोes not alपढ़ोy provide an implementation.
 */
#अगर_घोषित XEN_NETIF_DEFINE_TOEPLITZ
अटल uपूर्णांक32_t xen_netअगर_toeplitz_hash(स्थिर uपूर्णांक8_t *key,
					अचिन्हित पूर्णांक keylen,
					स्थिर uपूर्णांक8_t *buf, अचिन्हित पूर्णांक buflen)
अणु
	अचिन्हित पूर्णांक keyi, bufi;
	uपूर्णांक64_t prefix = 0;
	uपूर्णांक64_t hash = 0;

	/* Pre-load prefix with the first 8 bytes of the key */
	क्रम (keyi = 0; keyi < 8; keyi++) अणु
		prefix <<= 8;
		prefix |= (keyi < keylen) ? key[keyi] : 0;
	पूर्ण

	क्रम (bufi = 0; bufi < buflen; bufi++) अणु
		uपूर्णांक8_t byte = buf[bufi];
		अचिन्हित पूर्णांक bit;

		क्रम (bit = 0; bit < 8; bit++) अणु
			अगर (byte & 0x80)
				hash ^= prefix;
			prefix <<= 1;
			byte <<= 1;
		पूर्ण

		/*
		 * 'prefix' has now been left-shअगरted by 8, so
		 * OR in the next byte.
		 */
		prefix |= (keyi < keylen) ? key[keyi] : 0;
		keyi++;
	पूर्ण

	/* The valid part of the hash is in the upper 32 bits. */
	वापस hash >> 32;
पूर्ण
#पूर्ण_अगर				/* XEN_NETIF_DEFINE_TOEPLITZ */

/*
 * Control requests (काष्ठा xen_netअगर_ctrl_request)
 * ================================================
 *
 * All requests have the following क्रमmat:
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |    id     |   type    |         data[0]       |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |         data[1]       |         data[2]       |
 * +-----+-----+-----+-----+-----------------------+
 *
 * id: the request identअगरier, echoed in response.
 * type: the type of request (see below)
 * data[]: any data associated with the request (determined by type)
 */

काष्ठा xen_netअगर_ctrl_request अणु
	uपूर्णांक16_t id;
	uपूर्णांक16_t type;

#घोषणा XEN_NETIF_CTRL_TYPE_INVALID               0
#घोषणा XEN_NETIF_CTRL_TYPE_GET_HASH_FLAGS        1
#घोषणा XEN_NETIF_CTRL_TYPE_SET_HASH_FLAGS        2
#घोषणा XEN_NETIF_CTRL_TYPE_SET_HASH_KEY          3
#घोषणा XEN_NETIF_CTRL_TYPE_GET_HASH_MAPPING_SIZE 4
#घोषणा XEN_NETIF_CTRL_TYPE_SET_HASH_MAPPING_SIZE 5
#घोषणा XEN_NETIF_CTRL_TYPE_SET_HASH_MAPPING      6
#घोषणा XEN_NETIF_CTRL_TYPE_SET_HASH_ALGORITHM    7

	uपूर्णांक32_t data[3];
पूर्ण;

/*
 * Control responses (काष्ठा xen_netअगर_ctrl_response)
 * ==================================================
 *
 * All responses have the following क्रमmat:
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |    id     |   type    |         status        |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |         data          |
 * +-----+-----+-----+-----+
 *
 * id: the corresponding request identअगरier
 * type: the type of the corresponding request
 * status: the status of request processing
 * data: any data associated with the response (determined by type and
 *       status)
 */

काष्ठा xen_netअगर_ctrl_response अणु
	uपूर्णांक16_t id;
	uपूर्णांक16_t type;
	uपूर्णांक32_t status;

#घोषणा XEN_NETIF_CTRL_STATUS_SUCCESS           0
#घोषणा XEN_NETIF_CTRL_STATUS_NOT_SUPPORTED     1
#घोषणा XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER 2
#घोषणा XEN_NETIF_CTRL_STATUS_BUFFER_OVERFLOW   3

	uपूर्णांक32_t data;
पूर्ण;

/*
 * Control messages
 * ================
 *
 * XEN_NETIF_CTRL_TYPE_SET_HASH_ALGORITHM
 * --------------------------------------
 *
 * This is sent by the frontend to set the desired hash algorithm.
 *
 * Request:
 *
 *  type    = XEN_NETIF_CTRL_TYPE_SET_HASH_ALGORITHM
 *  data[0] = a XEN_NETIF_CTRL_HASH_ALGORITHM_* value
 *  data[1] = 0
 *  data[2] = 0
 *
 * Response:
 *
 *  status = XEN_NETIF_CTRL_STATUS_NOT_SUPPORTED     - Operation not
 *                                                     supported
 *           XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER - The algorithm is not
 *                                                     supported
 *           XEN_NETIF_CTRL_STATUS_SUCCESS           - Operation successful
 *
 * NOTE: Setting data[0] to XEN_NETIF_CTRL_HASH_ALGORITHM_NONE disables
 *       hashing and the backend is मुक्त to choose how it steers packets
 *       to queues (which is the शेष behaviour).
 *
 * XEN_NETIF_CTRL_TYPE_GET_HASH_FLAGS
 * ----------------------------------
 *
 * This is sent by the frontend to query the types of hash supported by
 * the backend.
 *
 * Request:
 *
 *  type    = XEN_NETIF_CTRL_TYPE_GET_HASH_FLAGS
 *  data[0] = 0
 *  data[1] = 0
 *  data[2] = 0
 *
 * Response:
 *
 *  status = XEN_NETIF_CTRL_STATUS_NOT_SUPPORTED - Operation not supported
 *           XEN_NETIF_CTRL_STATUS_SUCCESS       - Operation successful
 *  data   = supported hash types (अगर operation was successful)
 *
 * NOTE: A valid hash algorithm must be selected beक्रमe this operation can
 *       succeed.
 *
 * XEN_NETIF_CTRL_TYPE_SET_HASH_FLAGS
 * ----------------------------------
 *
 * This is sent by the frontend to set the types of hash that the backend
 * should calculate. (See above क्रम hash type definitions).
 * Note that the 'maximal' type of hash should always be chosen. For
 * example, अगर the frontend sets both IPV4 and IPV4_TCP hash types then
 * the latter hash type should be calculated क्रम any TCP packet and the
 * क्रमmer only calculated क्रम non-TCP packets.
 *
 * Request:
 *
 *  type    = XEN_NETIF_CTRL_TYPE_SET_HASH_FLAGS
 *  data[0] = bitwise OR of XEN_NETIF_CTRL_HASH_TYPE_* values
 *  data[1] = 0
 *  data[2] = 0
 *
 * Response:
 *
 *  status = XEN_NETIF_CTRL_STATUS_NOT_SUPPORTED     - Operation not
 *                                                     supported
 *           XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER - One or more flag
 *                                                     value is invalid or
 *                                                     unsupported
 *           XEN_NETIF_CTRL_STATUS_SUCCESS           - Operation successful
 *  data   = 0
 *
 * NOTE: A valid hash algorithm must be selected beक्रमe this operation can
 *       succeed.
 *       Also, setting data[0] to zero disables hashing and the backend
 *       is मुक्त to choose how it steers packets to queues.
 *
 * XEN_NETIF_CTRL_TYPE_SET_HASH_KEY
 * --------------------------------
 *
 * This is sent by the frontend to set the key of the hash अगर the algorithm
 * requires it. (See hash algorithms above).
 *
 * Request:
 *
 *  type    = XEN_NETIF_CTRL_TYPE_SET_HASH_KEY
 *  data[0] = grant reference of page containing the key (assumed to
 *            start at beginning of grant)
 *  data[1] = size of key in octets
 *  data[2] = 0
 *
 * Response:
 *
 *  status = XEN_NETIF_CTRL_STATUS_NOT_SUPPORTED     - Operation not
 *                                                     supported
 *           XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER - Key size is invalid
 *           XEN_NETIF_CTRL_STATUS_BUFFER_OVERFLOW   - Key size is larger
 *                                                     than the backend
 *                                                     supports
 *           XEN_NETIF_CTRL_STATUS_SUCCESS           - Operation successful
 *  data   = 0
 *
 * NOTE: Any key octets not specअगरied are assumed to be zero (the key
 *       is assumed to be empty by शेष) and specअगरying a new key
 *       invalidates any previous key, hence specअगरying a key size of
 *       zero will clear the key (which ensures that the calculated hash
 *       will always be zero).
 *       The maximum size of key is algorithm and backend specअगरic, but
 *       is also limited by the single grant reference.
 *       The grant reference may be पढ़ो-only and must reमुख्य valid until
 *       the response has been processed.
 *
 * XEN_NETIF_CTRL_TYPE_GET_HASH_MAPPING_SIZE
 * -----------------------------------------
 *
 * This is sent by the frontend to query the maximum size of mapping
 * table supported by the backend. The size is specअगरied in terms of
 * table entries.
 *
 * Request:
 *
 *  type    = XEN_NETIF_CTRL_TYPE_GET_HASH_MAPPING_SIZE
 *  data[0] = 0
 *  data[1] = 0
 *  data[2] = 0
 *
 * Response:
 *
 *  status = XEN_NETIF_CTRL_STATUS_NOT_SUPPORTED - Operation not supported
 *           XEN_NETIF_CTRL_STATUS_SUCCESS       - Operation successful
 *  data   = maximum number of entries allowed in the mapping table
 *           (अगर operation was successful) or zero अगर a mapping table is
 *           not supported (i.e. hash mapping is करोne only by modular
 *           arithmetic).
 *
 * XEN_NETIF_CTRL_TYPE_SET_HASH_MAPPING_SIZE
 * -------------------------------------
 *
 * This is sent by the frontend to set the actual size of the mapping
 * table to be used by the backend. The size is specअगरied in terms of
 * table entries.
 * Any previous table is invalidated by this message and any new table
 * is assumed to be zero filled.
 *
 * Request:
 *
 *  type    = XEN_NETIF_CTRL_TYPE_SET_HASH_MAPPING_SIZE
 *  data[0] = number of entries in mapping table
 *  data[1] = 0
 *  data[2] = 0
 *
 * Response:
 *
 *  status = XEN_NETIF_CTRL_STATUS_NOT_SUPPORTED     - Operation not
 *                                                     supported
 *           XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER - Table size is invalid
 *           XEN_NETIF_CTRL_STATUS_SUCCESS           - Operation successful
 *  data   = 0
 *
 * NOTE: Setting data[0] to 0 means that hash mapping should be करोne
 *       using modular arithmetic.
 *
 * XEN_NETIF_CTRL_TYPE_SET_HASH_MAPPING
 * ------------------------------------
 *
 * This is sent by the frontend to set the content of the table mapping
 * hash value to queue number. The backend should calculate the hash from
 * the packet header, use it as an index पूर्णांकo the table (modulo the size
 * of the table) and then steer the packet to the queue number found at
 * that index.
 *
 * Request:
 *
 *  type    = XEN_NETIF_CTRL_TYPE_SET_HASH_MAPPING
 *  data[0] = grant reference of page containing the mapping (sub-)table
 *            (assumed to start at beginning of grant)
 *  data[1] = size of (sub-)table in entries
 *  data[2] = offset, in entries, of sub-table within overall table
 *
 * Response:
 *
 *  status = XEN_NETIF_CTRL_STATUS_NOT_SUPPORTED     - Operation not
 *                                                     supported
 *           XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER - Table size or content
 *                                                     is invalid
 *           XEN_NETIF_CTRL_STATUS_BUFFER_OVERFLOW   - Table size is larger
 *                                                     than the backend
 *                                                     supports
 *           XEN_NETIF_CTRL_STATUS_SUCCESS           - Operation successful
 *  data   = 0
 *
 * NOTE: The overall table has the following क्रमmat:
 *
 *          0     1     2     3     4     5     6     7  octet
 *       +-----+-----+-----+-----+-----+-----+-----+-----+
 *       |       mapping[0]      |       mapping[1]      |
 *       +-----+-----+-----+-----+-----+-----+-----+-----+
 *       |                       .                       |
 *       |                       .                       |
 *       |                       .                       |
 *       +-----+-----+-----+-----+-----+-----+-----+-----+
 *       |      mapping[N-2]     |      mapping[N-1]     |
 *       +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 *       where N is specअगरied by a XEN_NETIF_CTRL_TYPE_SET_HASH_MAPPING_SIZE
 *       message and each  mapping must specअगरies a queue between 0 and
 *       "multi-queue-num-queues" (see above).
 *       The backend may support a mapping table larger than can be
 *       mapped by a single grant reference. Thus sub-tables within a
 *       larger table can be inभागidually set by sending multiple messages
 *       with dअगरfering offset values. Specअगरying a new sub-table करोes not
 *       invalidate any table data outside that range.
 *       The grant reference may be पढ़ो-only and must reमुख्य valid until
 *       the response has been processed.
 */

DEFINE_RING_TYPES(xen_netअगर_ctrl,
		  काष्ठा xen_netअगर_ctrl_request,
		  काष्ठा xen_netअगर_ctrl_response);

/*
 * Guest transmit
 * ==============
 *
 * This is the 'wire' क्रमmat क्रम transmit (frontend -> backend) packets:
 *
 *  Fragment 1: xen_netअगर_tx_request_t  - flags = XEN_NETTXF_*
 *                                    size = total packet size
 * [Extra 1: xen_netअगर_extra_info_t]    - (only अगर fragment 1 flags include
 *                                     XEN_NETTXF_extra_info)
 *  ...
 * [Extra N: xen_netअगर_extra_info_t]    - (only अगर extra N-1 flags include
 *                                     XEN_NETIF_EXTRA_MORE)
 *  ...
 *  Fragment N: xen_netअगर_tx_request_t  - (only अगर fragment N-1 flags include
 *                                     XEN_NETTXF_more_data - flags on preceding
 *                                     extras are not relevant here)
 *                                    flags = 0
 *                                    size = fragment size
 *
 * NOTE:
 *
 * This क्रमmat slightly is dअगरferent from that used क्रम receive
 * (backend -> frontend) packets. Specअगरically, in a multi-fragment
 * packet the actual size of fragment 1 can only be determined by
 * subtracting the sizes of fragments 2..N from the total packet size.
 *
 * Ring slot size is 12 octets, however not all request/response
 * काष्ठाs use the full size.
 *
 * tx request data (xen_netअगर_tx_request_t)
 * ------------------------------------
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | grant ref             | offset    | flags     |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | id        | size      |
 * +-----+-----+-----+-----+
 *
 * grant ref: Reference to buffer page.
 * offset: Offset within buffer page.
 * flags: XEN_NETTXF_*.
 * id: request identअगरier, echoed in response.
 * size: packet size in bytes.
 *
 * tx response (xen_netअगर_tx_response_t)
 * ---------------------------------
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | id        | status    | unused                |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | unused                |
 * +-----+-----+-----+-----+
 *
 * id: reflects id in transmit request
 * status: XEN_NETIF_RSP_*
 *
 * Guest receive
 * =============
 *
 * This is the 'wire' क्रमmat क्रम receive (backend -> frontend) packets:
 *
 *  Fragment 1: xen_netअगर_rx_request_t  - flags = XEN_NETRXF_*
 *                                    size = fragment size
 * [Extra 1: xen_netअगर_extra_info_t]    - (only अगर fragment 1 flags include
 *                                     XEN_NETRXF_extra_info)
 *  ...
 * [Extra N: xen_netअगर_extra_info_t]    - (only अगर extra N-1 flags include
 *                                     XEN_NETIF_EXTRA_MORE)
 *  ...
 *  Fragment N: xen_netअगर_rx_request_t  - (only अगर fragment N-1 flags include
 *                                     XEN_NETRXF_more_data - flags on preceding
 *                                     extras are not relevant here)
 *                                    flags = 0
 *                                    size = fragment size
 *
 * NOTE:
 *
 * This क्रमmat slightly is dअगरferent from that used क्रम transmit
 * (frontend -> backend) packets. Specअगरically, in a multi-fragment
 * packet the size of the packet can only be determined by summing the
 * sizes of fragments 1..N.
 *
 * Ring slot size is 8 octets.
 *
 * rx request (xen_netअगर_rx_request_t)
 * -------------------------------
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | id        | pad       | gref                  |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 * id: request identअगरier, echoed in response.
 * gref: reference to incoming granted frame.
 *
 * rx response (xen_netअगर_rx_response_t)
 * ---------------------------------
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | id        | offset    | flags     | status    |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 * id: reflects id in receive request
 * offset: offset in page of start of received packet
 * flags: XEN_NETRXF_*
 * status: -ve: XEN_NETIF_RSP_*; +ve: Rx'ed pkt size.
 *
 * NOTE: Historically, to support GSO on the frontend receive side, Linux
 *       netfront करोes not make use of the rx response id (because, as
 *       described below, extra info काष्ठाures overlay the id field).
 *       Instead it assumes that responses always appear in the same ring
 *       slot as their corresponding request. Thus, to मुख्यtain
 *       compatibility, backends must make sure this is the हाल.
 *
 * Extra Info
 * ==========
 *
 * Can be present अगर initial request or response has NETअणुT,Rपूर्णXF_extra_info,
 * or previous extra request has XEN_NETIF_EXTRA_MORE.
 *
 * The काष्ठा thereक्रमe needs to fit पूर्णांकo either a tx or rx slot and
 * is thereक्रमe limited to 8 octets.
 *
 * NOTE: Because extra info data overlays the usual request/response
 *       काष्ठाures, there is no id inक्रमmation in the opposite direction.
 *       So, अगर an extra info overlays an rx response the frontend can
 *       assume that it is in the same ring slot as the request that was
 *       consumed to make the slot available, and the backend must ensure
 *       this assumption is true.
 *
 * extra info (xen_netअगर_extra_info_t)
 * -------------------------------
 *
 * General क्रमmat:
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |type |flags| type specअगरic data                |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * | padding क्रम tx        |
 * +-----+-----+-----+-----+
 *
 * type: XEN_NETIF_EXTRA_TYPE_*
 * flags: XEN_NETIF_EXTRA_FLAG_*
 * padding क्रम tx: present only in the tx हाल due to 8 octet limit
 *                 from rx हाल. Not shown in type specअगरic entries
 *                 below.
 *
 * XEN_NETIF_EXTRA_TYPE_GSO:
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |type |flags| size      |type | pad | features  |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 * type: Must be XEN_NETIF_EXTRA_TYPE_GSO
 * flags: XEN_NETIF_EXTRA_FLAG_*
 * size: Maximum payload size of each segment. For example,
 *       क्रम TCP this is just the path MSS.
 * type: XEN_NETIF_GSO_TYPE_*: This determines the protocol of
 *       the packet and any extra features required to segment the
 *       packet properly.
 * features: EN_XEN_NETIF_GSO_FEAT_*: This specअगरies any extra GSO
 *           features required to process this packet, such as ECN
 *           support क्रम TCPv4.
 *
 * XEN_NETIF_EXTRA_TYPE_MCAST_अणुADD,DELपूर्ण:
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |type |flags| addr                              |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 * type: Must be XEN_NETIF_EXTRA_TYPE_MCAST_अणुADD,DELपूर्ण
 * flags: XEN_NETIF_EXTRA_FLAG_*
 * addr: address to add/हटाओ
 *
 * XEN_NETIF_EXTRA_TYPE_HASH:
 *
 * A backend that supports teoplitz hashing is assumed to accept
 * this type of extra info in transmit packets.
 * A frontend that enables hashing is assumed to accept
 * this type of extra info in receive packets.
 *
 *    0     1     2     3     4     5     6     7  octet
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |type |flags|htype| alg |LSB ---- value ---- MSB|
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 * type: Must be XEN_NETIF_EXTRA_TYPE_HASH
 * flags: XEN_NETIF_EXTRA_FLAG_*
 * htype: Hash type (one of _XEN_NETIF_CTRL_HASH_TYPE_* - see above)
 * alg: The algorithm used to calculate the hash (one of
 *      XEN_NETIF_CTRL_HASH_TYPE_ALGORITHM_* - see above)
 * value: Hash value
 */

/* Protocol checksum field is blank in the packet (hardware offload)? */
#घोषणा _XEN_NETTXF_csum_blank     (0)
#घोषणा  XEN_NETTXF_csum_blank     (1U<<_XEN_NETTXF_csum_blank)

/* Packet data has been validated against protocol checksum. */
#घोषणा _XEN_NETTXF_data_validated (1)
#घोषणा  XEN_NETTXF_data_validated (1U<<_XEN_NETTXF_data_validated)

/* Packet जारीs in the next request descriptor. */
#घोषणा _XEN_NETTXF_more_data      (2)
#घोषणा  XEN_NETTXF_more_data      (1U<<_XEN_NETTXF_more_data)

/* Packet to be followed by extra descriptor(s). */
#घोषणा _XEN_NETTXF_extra_info     (3)
#घोषणा  XEN_NETTXF_extra_info     (1U<<_XEN_NETTXF_extra_info)

#घोषणा XEN_NETIF_MAX_TX_SIZE 0xFFFF
काष्ठा xen_netअगर_tx_request अणु
	grant_ref_t gref;
	uपूर्णांक16_t offset;
	uपूर्णांक16_t flags;
	uपूर्णांक16_t id;
	uपूर्णांक16_t size;
पूर्ण;

/* Types of xen_netअगर_extra_info descriptors. */
#घोषणा XEN_NETIF_EXTRA_TYPE_NONE      (0)	/* Never used - invalid */
#घोषणा XEN_NETIF_EXTRA_TYPE_GSO       (1)	/* u.gso */
#घोषणा XEN_NETIF_EXTRA_TYPE_MCAST_ADD (2)	/* u.mcast */
#घोषणा XEN_NETIF_EXTRA_TYPE_MCAST_DEL (3)	/* u.mcast */
#घोषणा XEN_NETIF_EXTRA_TYPE_HASH      (4)	/* u.hash */
#घोषणा XEN_NETIF_EXTRA_TYPE_XDP       (5)	/* u.xdp */
#घोषणा XEN_NETIF_EXTRA_TYPE_MAX       (6)

/* xen_netअगर_extra_info_t flags. */
#घोषणा _XEN_NETIF_EXTRA_FLAG_MORE (0)
#घोषणा XEN_NETIF_EXTRA_FLAG_MORE  (1U<<_XEN_NETIF_EXTRA_FLAG_MORE)

/* GSO types */
#घोषणा XEN_NETIF_GSO_TYPE_NONE         (0)
#घोषणा XEN_NETIF_GSO_TYPE_TCPV4        (1)
#घोषणा XEN_NETIF_GSO_TYPE_TCPV6        (2)

/*
 * This काष्ठाure needs to fit within both xen_netअगर_tx_request_t and
 * xen_netअगर_rx_response_t क्रम compatibility.
 */
काष्ठा xen_netअगर_extra_info अणु
	uपूर्णांक8_t type;
	uपूर्णांक8_t flags;
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक16_t size;
			uपूर्णांक8_t type;
			uपूर्णांक8_t pad;
			uपूर्णांक16_t features;
		पूर्ण gso;
		काष्ठा अणु
			uपूर्णांक8_t addr[6];
		पूर्ण mcast;
		काष्ठा अणु
			uपूर्णांक8_t type;
			uपूर्णांक8_t algorithm;
			uपूर्णांक8_t value[4];
		पूर्ण hash;
		काष्ठा अणु
			uपूर्णांक16_t headroom;
			uपूर्णांक16_t pad[2];
		पूर्ण xdp;
		uपूर्णांक16_t pad[3];
	पूर्ण u;
पूर्ण;

काष्ठा xen_netअगर_tx_response अणु
	uपूर्णांक16_t id;
	पूर्णांक16_t status;
पूर्ण;

काष्ठा xen_netअगर_rx_request अणु
	uपूर्णांक16_t id;		/* Echoed in response message.        */
	uपूर्णांक16_t pad;
	grant_ref_t gref;
पूर्ण;

/* Packet data has been validated against protocol checksum. */
#घोषणा _XEN_NETRXF_data_validated (0)
#घोषणा  XEN_NETRXF_data_validated (1U<<_XEN_NETRXF_data_validated)

/* Protocol checksum field is blank in the packet (hardware offload)? */
#घोषणा _XEN_NETRXF_csum_blank     (1)
#घोषणा  XEN_NETRXF_csum_blank     (1U<<_XEN_NETRXF_csum_blank)

/* Packet जारीs in the next request descriptor. */
#घोषणा _XEN_NETRXF_more_data      (2)
#घोषणा  XEN_NETRXF_more_data      (1U<<_XEN_NETRXF_more_data)

/* Packet to be followed by extra descriptor(s). */
#घोषणा _XEN_NETRXF_extra_info     (3)
#घोषणा  XEN_NETRXF_extra_info     (1U<<_XEN_NETRXF_extra_info)

/* Packet has GSO prefix. Deprecated but included क्रम compatibility */
#घोषणा _XEN_NETRXF_gso_prefix     (4)
#घोषणा  XEN_NETRXF_gso_prefix     (1U<<_XEN_NETRXF_gso_prefix)

काष्ठा xen_netअगर_rx_response अणु
	uपूर्णांक16_t id;
	uपूर्णांक16_t offset;
	uपूर्णांक16_t flags;
	पूर्णांक16_t status;
पूर्ण;

/*
 * Generate xen_netअगर ring काष्ठाures and types.
 */

DEFINE_RING_TYPES(xen_netअगर_tx, काष्ठा xen_netअगर_tx_request,
		  काष्ठा xen_netअगर_tx_response);
DEFINE_RING_TYPES(xen_netअगर_rx, काष्ठा xen_netअगर_rx_request,
		  काष्ठा xen_netअगर_rx_response);

#घोषणा XEN_NETIF_RSP_DROPPED         -2
#घोषणा XEN_NETIF_RSP_ERROR           -1
#घोषणा XEN_NETIF_RSP_OKAY             0
/* No response: used क्रम auxiliary requests (e.g., xen_netअगर_extra_info_t). */
#घोषणा XEN_NETIF_RSP_शून्य             1

#पूर्ण_अगर
