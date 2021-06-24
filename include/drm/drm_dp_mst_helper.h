<शैली गुरु>
/*
 * Copyright तऊ 2014 Red Hat.
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */
#अगर_अघोषित _DRM_DP_MST_HELPER_H_
#घोषणा _DRM_DP_MST_HELPER_H_

#समावेश <linux/types.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_atomic.h>

#अगर IS_ENABLED(CONFIG_DRM_DEBUG_DP_MST_TOPOLOGY_REFS)
#समावेश <linux/stackdepot.h>
#समावेश <linux/समयkeeping.h>

क्रमागत drm_dp_mst_topology_ref_type अणु
	DRM_DP_MST_TOPOLOGY_REF_GET,
	DRM_DP_MST_TOPOLOGY_REF_PUT,
पूर्ण;

काष्ठा drm_dp_mst_topology_ref_history अणु
	काष्ठा drm_dp_mst_topology_ref_entry अणु
		क्रमागत drm_dp_mst_topology_ref_type type;
		पूर्णांक count;
		kसमय_प्रकार ts_nsec;
		depot_stack_handle_t backtrace;
	पूर्ण *entries;
	पूर्णांक len;
पूर्ण;
#पूर्ण_अगर /* IS_ENABLED(CONFIG_DRM_DEBUG_DP_MST_TOPOLOGY_REFS) */

काष्ठा drm_dp_mst_branch;

/**
 * काष्ठा drm_dp_vcpi - Virtual Channel Payload Identअगरier
 * @vcpi: Virtual channel ID.
 * @pbn: Payload Bandwidth Number क्रम this channel
 * @aligned_pbn: PBN aligned with slot size
 * @num_slots: number of slots क्रम this PBN
 */
काष्ठा drm_dp_vcpi अणु
	पूर्णांक vcpi;
	पूर्णांक pbn;
	पूर्णांक aligned_pbn;
	पूर्णांक num_slots;
पूर्ण;

/**
 * काष्ठा drm_dp_mst_port - MST port
 * @port_num: port number
 * @input: अगर this port is an input port. Protected by
 * &drm_dp_mst_topology_mgr.base.lock.
 * @mcs: message capability status - DP 1.2 spec. Protected by
 * &drm_dp_mst_topology_mgr.base.lock.
 * @ddps: DisplayPort Device Plug Status - DP 1.2. Protected by
 * &drm_dp_mst_topology_mgr.base.lock.
 * @pdt: Peer Device Type. Protected by
 * &drm_dp_mst_topology_mgr.base.lock.
 * @ldps: Legacy Device Plug Status. Protected by
 * &drm_dp_mst_topology_mgr.base.lock.
 * @dpcd_rev: DPCD revision of device on this port. Protected by
 * &drm_dp_mst_topology_mgr.base.lock.
 * @num_sdp_streams: Number of simultaneous streams. Protected by
 * &drm_dp_mst_topology_mgr.base.lock.
 * @num_sdp_stream_sinks: Number of stream sinks. Protected by
 * &drm_dp_mst_topology_mgr.base.lock.
 * @full_pbn: Max possible bandwidth क्रम this port. Protected by
 * &drm_dp_mst_topology_mgr.base.lock.
 * @next: link to next port on this branch device
 * @aux: i2c aux transport to talk to device connected to this port, रक्षित
 * by &drm_dp_mst_topology_mgr.base.lock.
 * @parent: branch device parent of this port
 * @vcpi: Virtual Channel Payload info क्रम this port.
 * @connector: DRM connector this port is connected to. Protected by
 * &drm_dp_mst_topology_mgr.base.lock.
 * @mgr: topology manager this port lives under.
 *
 * This काष्ठाure represents an MST port endpoपूर्णांक on a device somewhere
 * in the MST topology.
 */
काष्ठा drm_dp_mst_port अणु
	/**
	 * @topology_kref: refcount क्रम this port's lअगरeसमय in the topology,
	 * only the DP MST helpers should need to touch this
	 */
	काष्ठा kref topology_kref;

	/**
	 * @दो_स्मृति_kref: refcount क्रम the memory allocation containing this
	 * काष्ठाure. See drm_dp_mst_get_port_दो_स्मृति() and
	 * drm_dp_mst_put_port_दो_स्मृति().
	 */
	काष्ठा kref दो_स्मृति_kref;

#अगर IS_ENABLED(CONFIG_DRM_DEBUG_DP_MST_TOPOLOGY_REFS)
	/**
	 * @topology_ref_history: A history of each topology
	 * reference/dereference. See CONFIG_DRM_DEBUG_DP_MST_TOPOLOGY_REFS.
	 */
	काष्ठा drm_dp_mst_topology_ref_history topology_ref_history;
#पूर्ण_अगर

	u8 port_num;
	bool input;
	bool mcs;
	bool ddps;
	u8 pdt;
	bool ldps;
	u8 dpcd_rev;
	u8 num_sdp_streams;
	u8 num_sdp_stream_sinks;
	uपूर्णांक16_t full_pbn;
	काष्ठा list_head next;
	/**
	 * @mstb: the branch device connected to this port, अगर there is one.
	 * This should be considered रक्षित क्रम पढ़ोing by
	 * &drm_dp_mst_topology_mgr.lock. There are two exceptions to this:
	 * &drm_dp_mst_topology_mgr.up_req_work and
	 * &drm_dp_mst_topology_mgr.work, which करो not grab
	 * &drm_dp_mst_topology_mgr.lock during पढ़ोs but are the only
	 * updaters of this list and are रक्षित from writing concurrently
	 * by &drm_dp_mst_topology_mgr.probe_lock.
	 */
	काष्ठा drm_dp_mst_branch *mstb;
	काष्ठा drm_dp_aux aux; /* i2c bus क्रम this port? */
	काष्ठा drm_dp_mst_branch *parent;

	काष्ठा drm_dp_vcpi vcpi;
	काष्ठा drm_connector *connector;
	काष्ठा drm_dp_mst_topology_mgr *mgr;

	/**
	 * @cached_edid: क्रम DP logical ports - make tiling work by ensuring
	 * that the EDID क्रम all connectors is पढ़ो immediately.
	 */
	काष्ठा edid *cached_edid;
	/**
	 * @has_audio: Tracks whether the sink connector to this port is
	 * audio-capable.
	 */
	bool has_audio;

	/**
	 * @fec_capable: bool indicating अगर FEC can be supported up to that
	 * poपूर्णांक in the MST topology.
	 */
	bool fec_capable;
पूर्ण;

/* sideband msg header - not bit काष्ठा */
काष्ठा drm_dp_sideband_msg_hdr अणु
	u8 lct;
	u8 lcr;
	u8 rad[8];
	bool broadcast;
	bool path_msg;
	u8 msg_len;
	bool somt;
	bool eomt;
	bool seqno;
पूर्ण;

काष्ठा drm_dp_sideband_msg_rx अणु
	u8 chunk[48];
	u8 msg[256];
	u8 curchunk_len;
	u8 curchunk_idx; /* chunk we are parsing now */
	u8 curchunk_hdrlen;
	u8 curlen; /* total length of the msg */
	bool have_somt;
	bool have_eomt;
	काष्ठा drm_dp_sideband_msg_hdr initial_hdr;
पूर्ण;

/**
 * काष्ठा drm_dp_mst_branch - MST branch device.
 * @rad: Relative Address to talk to this branch device.
 * @lct: Link count total to talk to this branch device.
 * @num_ports: number of ports on the branch.
 * @port_parent: poपूर्णांकer to the port parent, शून्य अगर toplevel.
 * @mgr: topology manager क्रम this branch device.
 * @link_address_sent: अगर a link address message has been sent to this device yet.
 * @guid: guid क्रम DP 1.2 branch device. port under this branch can be
 * identअगरied by port #.
 *
 * This काष्ठाure represents an MST branch device, there is one
 * primary branch device at the root, aदीर्घ with any other branches connected
 * to करोwnstream port of parent branches.
 */
काष्ठा drm_dp_mst_branch अणु
	/**
	 * @topology_kref: refcount क्रम this branch device's lअगरeसमय in the
	 * topology, only the DP MST helpers should need to touch this
	 */
	काष्ठा kref topology_kref;

	/**
	 * @दो_स्मृति_kref: refcount क्रम the memory allocation containing this
	 * काष्ठाure. See drm_dp_mst_get_mstb_दो_स्मृति() and
	 * drm_dp_mst_put_mstb_दो_स्मृति().
	 */
	काष्ठा kref दो_स्मृति_kref;

#अगर IS_ENABLED(CONFIG_DRM_DEBUG_DP_MST_TOPOLOGY_REFS)
	/**
	 * @topology_ref_history: A history of each topology
	 * reference/dereference. See CONFIG_DRM_DEBUG_DP_MST_TOPOLOGY_REFS.
	 */
	काष्ठा drm_dp_mst_topology_ref_history topology_ref_history;
#पूर्ण_अगर

	/**
	 * @destroy_next: linked-list entry used by
	 * drm_dp_delayed_destroy_work()
	 */
	काष्ठा list_head destroy_next;

	u8 rad[8];
	u8 lct;
	पूर्णांक num_ports;

	/**
	 * @ports: the list of ports on this branch device. This should be
	 * considered रक्षित क्रम पढ़ोing by &drm_dp_mst_topology_mgr.lock.
	 * There are two exceptions to this:
	 * &drm_dp_mst_topology_mgr.up_req_work and
	 * &drm_dp_mst_topology_mgr.work, which करो not grab
	 * &drm_dp_mst_topology_mgr.lock during पढ़ोs but are the only
	 * updaters of this list and are रक्षित from updating the list
	 * concurrently by @drm_dp_mst_topology_mgr.probe_lock
	 */
	काष्ठा list_head ports;

	काष्ठा drm_dp_mst_port *port_parent;
	काष्ठा drm_dp_mst_topology_mgr *mgr;

	bool link_address_sent;

	/* global unique identअगरier to identअगरy branch devices */
	u8 guid[16];
पूर्ण;


काष्ठा drm_dp_nak_reply अणु
	u8 guid[16];
	u8 reason;
	u8 nak_data;
पूर्ण;

काष्ठा drm_dp_link_address_ack_reply अणु
	u8 guid[16];
	u8 nports;
	काष्ठा drm_dp_link_addr_reply_port अणु
		bool input_port;
		u8 peer_device_type;
		u8 port_number;
		bool mcs;
		bool ddps;
		bool legacy_device_plug_status;
		u8 dpcd_revision;
		u8 peer_guid[16];
		u8 num_sdp_streams;
		u8 num_sdp_stream_sinks;
	पूर्ण ports[16];
पूर्ण;

काष्ठा drm_dp_remote_dpcd_पढ़ो_ack_reply अणु
	u8 port_number;
	u8 num_bytes;
	u8 bytes[255];
पूर्ण;

काष्ठा drm_dp_remote_dpcd_ग_लिखो_ack_reply अणु
	u8 port_number;
पूर्ण;

काष्ठा drm_dp_remote_dpcd_ग_लिखो_nak_reply अणु
	u8 port_number;
	u8 reason;
	u8 bytes_written_beक्रमe_failure;
पूर्ण;

काष्ठा drm_dp_remote_i2c_पढ़ो_ack_reply अणु
	u8 port_number;
	u8 num_bytes;
	u8 bytes[255];
पूर्ण;

काष्ठा drm_dp_remote_i2c_पढ़ो_nak_reply अणु
	u8 port_number;
	u8 nak_reason;
	u8 i2c_nak_transaction;
पूर्ण;

काष्ठा drm_dp_remote_i2c_ग_लिखो_ack_reply अणु
	u8 port_number;
पूर्ण;

काष्ठा drm_dp_query_stream_enc_status_ack_reply अणु
	/* Bit[23:16]- Stream Id */
	u8 stream_id;

	/* Bit[15]- Signed */
	bool reply_चिन्हित;

	/* Bit[10:8]- Stream Output Sink Type */
	bool unauthorizable_device_present;
	bool legacy_device_present;
	bool query_capable_device_present;

	/* Bit[12:11]- Stream Output CP Type */
	bool hdcp_1x_device_present;
	bool hdcp_2x_device_present;

	/* Bit[4]- Stream Authentication */
	bool auth_completed;

	/* Bit[3]- Stream Encryption */
	bool encryption_enabled;

	/* Bit[2]- Stream Repeater Function Present */
	bool repeater_present;

	/* Bit[1:0]- Stream State */
	u8 state;
पूर्ण;

#घोषणा DRM_DP_MAX_SDP_STREAMS 16
काष्ठा drm_dp_allocate_payload अणु
	u8 port_number;
	u8 number_sdp_streams;
	u8 vcpi;
	u16 pbn;
	u8 sdp_stream_sink[DRM_DP_MAX_SDP_STREAMS];
पूर्ण;

काष्ठा drm_dp_allocate_payload_ack_reply अणु
	u8 port_number;
	u8 vcpi;
	u16 allocated_pbn;
पूर्ण;

काष्ठा drm_dp_connection_status_notअगरy अणु
	u8 guid[16];
	u8 port_number;
	bool legacy_device_plug_status;
	bool displayport_device_plug_status;
	bool message_capability_status;
	bool input_port;
	u8 peer_device_type;
पूर्ण;

काष्ठा drm_dp_remote_dpcd_पढ़ो अणु
	u8 port_number;
	u32 dpcd_address;
	u8 num_bytes;
पूर्ण;

काष्ठा drm_dp_remote_dpcd_ग_लिखो अणु
	u8 port_number;
	u32 dpcd_address;
	u8 num_bytes;
	u8 *bytes;
पूर्ण;

#घोषणा DP_REMOTE_I2C_READ_MAX_TRANSACTIONS 4
काष्ठा drm_dp_remote_i2c_पढ़ो अणु
	u8 num_transactions;
	u8 port_number;
	काष्ठा drm_dp_remote_i2c_पढ़ो_tx अणु
		u8 i2c_dev_id;
		u8 num_bytes;
		u8 *bytes;
		u8 no_stop_bit;
		u8 i2c_transaction_delay;
	पूर्ण transactions[DP_REMOTE_I2C_READ_MAX_TRANSACTIONS];
	u8 पढ़ो_i2c_device_id;
	u8 num_bytes_पढ़ो;
पूर्ण;

काष्ठा drm_dp_remote_i2c_ग_लिखो अणु
	u8 port_number;
	u8 ग_लिखो_i2c_device_id;
	u8 num_bytes;
	u8 *bytes;
पूर्ण;

काष्ठा drm_dp_query_stream_enc_status अणु
	u8 stream_id;
	u8 client_id[7];	/* 56-bit nonce */
	u8 stream_event;
	bool valid_stream_event;
	u8 stream_behavior;
	u8 valid_stream_behavior;
पूर्ण;

/* this covers ENUM_RESOURCES, POWER_DOWN_PHY, POWER_UP_PHY */
काष्ठा drm_dp_port_number_req अणु
	u8 port_number;
पूर्ण;

काष्ठा drm_dp_क्रमागत_path_resources_ack_reply अणु
	u8 port_number;
	bool fec_capable;
	u16 full_payload_bw_number;
	u16 avail_payload_bw_number;
पूर्ण;

/* covers POWER_DOWN_PHY, POWER_UP_PHY */
काष्ठा drm_dp_port_number_rep अणु
	u8 port_number;
पूर्ण;

काष्ठा drm_dp_query_payload अणु
	u8 port_number;
	u8 vcpi;
पूर्ण;

काष्ठा drm_dp_resource_status_notअगरy अणु
	u8 port_number;
	u8 guid[16];
	u16 available_pbn;
पूर्ण;

काष्ठा drm_dp_query_payload_ack_reply अणु
	u8 port_number;
	u16 allocated_pbn;
पूर्ण;

काष्ठा drm_dp_sideband_msg_req_body अणु
	u8 req_type;
	जोड़ ack_req अणु
		काष्ठा drm_dp_connection_status_notअगरy conn_stat;
		काष्ठा drm_dp_port_number_req port_num;
		काष्ठा drm_dp_resource_status_notअगरy resource_stat;

		काष्ठा drm_dp_query_payload query_payload;
		काष्ठा drm_dp_allocate_payload allocate_payload;

		काष्ठा drm_dp_remote_dpcd_पढ़ो dpcd_पढ़ो;
		काष्ठा drm_dp_remote_dpcd_ग_लिखो dpcd_ग_लिखो;

		काष्ठा drm_dp_remote_i2c_पढ़ो i2c_पढ़ो;
		काष्ठा drm_dp_remote_i2c_ग_लिखो i2c_ग_लिखो;

		काष्ठा drm_dp_query_stream_enc_status enc_status;
	पूर्ण u;
पूर्ण;

काष्ठा drm_dp_sideband_msg_reply_body अणु
	u8 reply_type;
	u8 req_type;
	जोड़ ack_replies अणु
		काष्ठा drm_dp_nak_reply nak;
		काष्ठा drm_dp_link_address_ack_reply link_addr;
		काष्ठा drm_dp_port_number_rep port_number;

		काष्ठा drm_dp_क्रमागत_path_resources_ack_reply path_resources;
		काष्ठा drm_dp_allocate_payload_ack_reply allocate_payload;
		काष्ठा drm_dp_query_payload_ack_reply query_payload;

		काष्ठा drm_dp_remote_dpcd_पढ़ो_ack_reply remote_dpcd_पढ़ो_ack;
		काष्ठा drm_dp_remote_dpcd_ग_लिखो_ack_reply remote_dpcd_ग_लिखो_ack;
		काष्ठा drm_dp_remote_dpcd_ग_लिखो_nak_reply remote_dpcd_ग_लिखो_nack;

		काष्ठा drm_dp_remote_i2c_पढ़ो_ack_reply remote_i2c_पढ़ो_ack;
		काष्ठा drm_dp_remote_i2c_पढ़ो_nak_reply remote_i2c_पढ़ो_nack;
		काष्ठा drm_dp_remote_i2c_ग_लिखो_ack_reply remote_i2c_ग_लिखो_ack;

		काष्ठा drm_dp_query_stream_enc_status_ack_reply enc_status;
	पूर्ण u;
पूर्ण;

/* msg is queued to be put पूर्णांकo a slot */
#घोषणा DRM_DP_SIDEBAND_TX_QUEUED 0
/* msg has started transmitting on a slot - still on msgq */
#घोषणा DRM_DP_SIDEBAND_TX_START_SEND 1
/* msg has finished transmitting on a slot - हटाओd from msgq only in slot */
#घोषणा DRM_DP_SIDEBAND_TX_SENT 2
/* msg has received a response - हटाओd from slot */
#घोषणा DRM_DP_SIDEBAND_TX_RX 3
#घोषणा DRM_DP_SIDEBAND_TX_TIMEOUT 4

काष्ठा drm_dp_sideband_msg_tx अणु
	u8 msg[256];
	u8 chunk[48];
	u8 cur_offset;
	u8 cur_len;
	काष्ठा drm_dp_mst_branch *dst;
	काष्ठा list_head next;
	पूर्णांक seqno;
	पूर्णांक state;
	bool path_msg;
	काष्ठा drm_dp_sideband_msg_reply_body reply;
पूर्ण;

/* sideband msg handler */
काष्ठा drm_dp_mst_topology_mgr;
काष्ठा drm_dp_mst_topology_cbs अणु
	/* create a connector क्रम a port */
	काष्ठा drm_connector *(*add_connector)(काष्ठा drm_dp_mst_topology_mgr *mgr, काष्ठा drm_dp_mst_port *port, स्थिर अक्षर *path);
	/*
	 * Checks क्रम any pending MST पूर्णांकerrupts, passing them to MST core क्रम
	 * processing, the same way an HPD IRQ pulse handler would करो this.
	 * If provided MST core calls this callback from a poll-रुकोing loop
	 * when रुकोing क्रम MST करोwn message replies. The driver is expected
	 * to guard against a race between this callback and the driver's HPD
	 * IRQ pulse handler.
	 */
	व्योम (*poll_hpd_irq)(काष्ठा drm_dp_mst_topology_mgr *mgr);
पूर्ण;

#घोषणा DP_MAX_PAYLOAD (माप(अचिन्हित दीर्घ) * 8)

#घोषणा DP_PAYLOAD_LOCAL 1
#घोषणा DP_PAYLOAD_REMOTE 2
#घोषणा DP_PAYLOAD_DELETE_LOCAL 3

काष्ठा drm_dp_payload अणु
	पूर्णांक payload_state;
	पूर्णांक start_slot;
	पूर्णांक num_slots;
	पूर्णांक vcpi;
पूर्ण;

#घोषणा to_dp_mst_topology_state(x) container_of(x, काष्ठा drm_dp_mst_topology_state, base)

काष्ठा drm_dp_vcpi_allocation अणु
	काष्ठा drm_dp_mst_port *port;
	पूर्णांक vcpi;
	पूर्णांक pbn;
	bool dsc_enabled;
	काष्ठा list_head next;
पूर्ण;

काष्ठा drm_dp_mst_topology_state अणु
	काष्ठा drm_निजी_state base;
	काष्ठा list_head vcpis;
	काष्ठा drm_dp_mst_topology_mgr *mgr;
पूर्ण;

#घोषणा to_dp_mst_topology_mgr(x) container_of(x, काष्ठा drm_dp_mst_topology_mgr, base)

/**
 * काष्ठा drm_dp_mst_topology_mgr - DisplayPort MST manager
 *
 * This काष्ठा represents the toplevel displayport MST topology manager.
 * There should be one instance of this क्रम every MST capable DP connector
 * on the GPU.
 */
काष्ठा drm_dp_mst_topology_mgr अणु
	/**
	 * @base: Base निजी object क्रम atomic
	 */
	काष्ठा drm_निजी_obj base;

	/**
	 * @dev: device poपूर्णांकer क्रम adding i2c devices etc.
	 */
	काष्ठा drm_device *dev;
	/**
	 * @cbs: callbacks क्रम connector addition and deकाष्ठाion.
	 */
	स्थिर काष्ठा drm_dp_mst_topology_cbs *cbs;
	/**
	 * @max_dpcd_transaction_bytes: maximum number of bytes to पढ़ो/ग_लिखो
	 * in one go.
	 */
	पूर्णांक max_dpcd_transaction_bytes;
	/**
	 * @aux: AUX channel क्रम the DP MST connector this topolgy mgr is
	 * controlling.
	 */
	काष्ठा drm_dp_aux *aux;
	/**
	 * @max_payloads: maximum number of payloads the GPU can generate.
	 */
	पूर्णांक max_payloads;
	/**
	 * @conn_base_id: DRM connector ID this mgr is connected to. Only used
	 * to build the MST connector path value.
	 */
	पूर्णांक conn_base_id;

	/**
	 * @up_req_recv: Message receiver state क्रम up requests.
	 */
	काष्ठा drm_dp_sideband_msg_rx up_req_recv;

	/**
	 * @करोwn_rep_recv: Message receiver state क्रम replies to करोwn
	 * requests.
	 */
	काष्ठा drm_dp_sideband_msg_rx करोwn_rep_recv;

	/**
	 * @lock: protects @mst_state, @mst_primary, @dpcd, and
	 * @payload_id_table_cleared.
	 */
	काष्ठा mutex lock;

	/**
	 * @probe_lock: Prevents @work and @up_req_work, the only ग_लिखोrs of
	 * &drm_dp_mst_port.mstb and &drm_dp_mst_branch.ports, from racing
	 * जबतक they update the topology.
	 */
	काष्ठा mutex probe_lock;

	/**
	 * @mst_state: If this manager is enabled क्रम an MST capable port. False
	 * अगर no MST sink/branch devices is connected.
	 */
	bool mst_state : 1;

	/**
	 * @payload_id_table_cleared: Whether or not we've cleared the payload
	 * ID table क्रम @mst_primary. Protected by @lock.
	 */
	bool payload_id_table_cleared : 1;

	/**
	 * @mst_primary: Poपूर्णांकer to the primary/first branch device.
	 */
	काष्ठा drm_dp_mst_branch *mst_primary;

	/**
	 * @dpcd: Cache of DPCD क्रम primary port.
	 */
	u8 dpcd[DP_RECEIVER_CAP_SIZE];
	/**
	 * @sink_count: Sink count from DEVICE_SERVICE_IRQ_VECTOR_ESI0.
	 */
	u8 sink_count;
	/**
	 * @pbn_भाग: PBN to slots भागisor.
	 */
	पूर्णांक pbn_भाग;

	/**
	 * @funcs: Atomic helper callbacks
	 */
	स्थिर काष्ठा drm_निजी_state_funcs *funcs;

	/**
	 * @qlock: protects @tx_msg_करोwnq and &drm_dp_sideband_msg_tx.state
	 */
	काष्ठा mutex qlock;

	/**
	 * @tx_msg_करोwnq: List of pending करोwn requests
	 */
	काष्ठा list_head tx_msg_करोwnq;

	/**
	 * @payload_lock: Protect payload inक्रमmation.
	 */
	काष्ठा mutex payload_lock;
	/**
	 * @proposed_vcpis: Array of poपूर्णांकers क्रम the new VCPI allocation. The
	 * VCPI काष्ठाure itself is &drm_dp_mst_port.vcpi, and the size of
	 * this array is determined by @max_payloads.
	 */
	काष्ठा drm_dp_vcpi **proposed_vcpis;
	/**
	 * @payloads: Array of payloads. The size of this array is determined
	 * by @max_payloads.
	 */
	काष्ठा drm_dp_payload *payloads;
	/**
	 * @payload_mask: Elements of @payloads actually in use. Since
	 * पुनः_स्मृतिation of active outमाला_दो isn't possible gaps can be created by
	 * disabling outमाला_दो out of order compared to how they've been enabled.
	 */
	अचिन्हित दीर्घ payload_mask;
	/**
	 * @vcpi_mask: Similar to @payload_mask, but क्रम @proposed_vcpis.
	 */
	अचिन्हित दीर्घ vcpi_mask;

	/**
	 * @tx_रुकोq: Wait to queue stall क्रम the tx worker.
	 */
	रुको_queue_head_t tx_रुकोq;
	/**
	 * @work: Probe work.
	 */
	काष्ठा work_काष्ठा work;
	/**
	 * @tx_work: Sideband transmit worker. This can nest within the मुख्य
	 * @work worker क्रम each transaction @work launches.
	 */
	काष्ठा work_काष्ठा tx_work;

	/**
	 * @destroy_port_list: List of to be destroyed connectors.
	 */
	काष्ठा list_head destroy_port_list;
	/**
	 * @destroy_branch_device_list: List of to be destroyed branch
	 * devices.
	 */
	काष्ठा list_head destroy_branch_device_list;
	/**
	 * @delayed_destroy_lock: Protects @destroy_port_list and
	 * @destroy_branch_device_list.
	 */
	काष्ठा mutex delayed_destroy_lock;

	/**
	 * @delayed_destroy_wq: Workqueue used क्रम delayed_destroy_work items.
	 * A dedicated WQ makes it possible to drain any requeued work items
	 * on it.
	 */
	काष्ठा workqueue_काष्ठा *delayed_destroy_wq;

	/**
	 * @delayed_destroy_work: Work item to destroy MST port and branch
	 * devices, needed to aव्योम locking inversion.
	 */
	काष्ठा work_काष्ठा delayed_destroy_work;

	/**
	 * @up_req_list: List of pending up requests from the topology that
	 * need to be processed, in chronological order.
	 */
	काष्ठा list_head up_req_list;
	/**
	 * @up_req_lock: Protects @up_req_list
	 */
	काष्ठा mutex up_req_lock;
	/**
	 * @up_req_work: Work item to process up requests received from the
	 * topology. Needed to aव्योम blocking hotplug handling and sideband
	 * transmissions.
	 */
	काष्ठा work_काष्ठा up_req_work;

#अगर IS_ENABLED(CONFIG_DRM_DEBUG_DP_MST_TOPOLOGY_REFS)
	/**
	 * @topology_ref_history_lock: protects
	 * &drm_dp_mst_port.topology_ref_history and
	 * &drm_dp_mst_branch.topology_ref_history.
	 */
	काष्ठा mutex topology_ref_history_lock;
#पूर्ण_अगर
पूर्ण;

पूर्णांक drm_dp_mst_topology_mgr_init(काष्ठा drm_dp_mst_topology_mgr *mgr,
				 काष्ठा drm_device *dev, काष्ठा drm_dp_aux *aux,
				 पूर्णांक max_dpcd_transaction_bytes,
				 पूर्णांक max_payloads, पूर्णांक conn_base_id);

व्योम drm_dp_mst_topology_mgr_destroy(काष्ठा drm_dp_mst_topology_mgr *mgr);

bool drm_dp_पढ़ो_mst_cap(काष्ठा drm_dp_aux *aux, स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE]);
पूर्णांक drm_dp_mst_topology_mgr_set_mst(काष्ठा drm_dp_mst_topology_mgr *mgr, bool mst_state);

पूर्णांक drm_dp_mst_hpd_irq(काष्ठा drm_dp_mst_topology_mgr *mgr, u8 *esi, bool *handled);


पूर्णांक
drm_dp_mst_detect_port(काष्ठा drm_connector *connector,
		       काष्ठा drm_modeset_acquire_ctx *ctx,
		       काष्ठा drm_dp_mst_topology_mgr *mgr,
		       काष्ठा drm_dp_mst_port *port);

काष्ठा edid *drm_dp_mst_get_edid(काष्ठा drm_connector *connector, काष्ठा drm_dp_mst_topology_mgr *mgr, काष्ठा drm_dp_mst_port *port);

पूर्णांक drm_dp_get_vc_payload_bw(पूर्णांक link_rate, पूर्णांक link_lane_count);

पूर्णांक drm_dp_calc_pbn_mode(पूर्णांक घड़ी, पूर्णांक bpp, bool dsc);

bool drm_dp_mst_allocate_vcpi(काष्ठा drm_dp_mst_topology_mgr *mgr,
			      काष्ठा drm_dp_mst_port *port, पूर्णांक pbn, पूर्णांक slots);

पूर्णांक drm_dp_mst_get_vcpi_slots(काष्ठा drm_dp_mst_topology_mgr *mgr, काष्ठा drm_dp_mst_port *port);


व्योम drm_dp_mst_reset_vcpi_slots(काष्ठा drm_dp_mst_topology_mgr *mgr, काष्ठा drm_dp_mst_port *port);


व्योम drm_dp_mst_deallocate_vcpi(काष्ठा drm_dp_mst_topology_mgr *mgr,
				काष्ठा drm_dp_mst_port *port);


पूर्णांक drm_dp_find_vcpi_slots(काष्ठा drm_dp_mst_topology_mgr *mgr,
			   पूर्णांक pbn);


पूर्णांक drm_dp_update_payload_part1(काष्ठा drm_dp_mst_topology_mgr *mgr);


पूर्णांक drm_dp_update_payload_part2(काष्ठा drm_dp_mst_topology_mgr *mgr);

पूर्णांक drm_dp_check_act_status(काष्ठा drm_dp_mst_topology_mgr *mgr);

व्योम drm_dp_mst_dump_topology(काष्ठा seq_file *m,
			      काष्ठा drm_dp_mst_topology_mgr *mgr);

व्योम drm_dp_mst_topology_mgr_suspend(काष्ठा drm_dp_mst_topology_mgr *mgr);
पूर्णांक __must_check
drm_dp_mst_topology_mgr_resume(काष्ठा drm_dp_mst_topology_mgr *mgr,
			       bool sync);

sमाप_प्रकार drm_dp_mst_dpcd_पढ़ो(काष्ठा drm_dp_aux *aux,
			     अचिन्हित पूर्णांक offset, व्योम *buffer, माप_प्रकार size);
sमाप_प्रकार drm_dp_mst_dpcd_ग_लिखो(काष्ठा drm_dp_aux *aux,
			      अचिन्हित पूर्णांक offset, व्योम *buffer, माप_प्रकार size);

पूर्णांक drm_dp_mst_connector_late_रेजिस्टर(काष्ठा drm_connector *connector,
				       काष्ठा drm_dp_mst_port *port);
व्योम drm_dp_mst_connector_early_unरेजिस्टर(काष्ठा drm_connector *connector,
					   काष्ठा drm_dp_mst_port *port);

काष्ठा drm_dp_mst_topology_state *drm_atomic_get_mst_topology_state(काष्ठा drm_atomic_state *state,
								    काष्ठा drm_dp_mst_topology_mgr *mgr);
पूर्णांक __must_check
drm_dp_atomic_find_vcpi_slots(काष्ठा drm_atomic_state *state,
			      काष्ठा drm_dp_mst_topology_mgr *mgr,
			      काष्ठा drm_dp_mst_port *port, पूर्णांक pbn,
			      पूर्णांक pbn_भाग);
पूर्णांक drm_dp_mst_atomic_enable_dsc(काष्ठा drm_atomic_state *state,
				 काष्ठा drm_dp_mst_port *port,
				 पूर्णांक pbn, पूर्णांक pbn_भाग,
				 bool enable);
पूर्णांक __must_check
drm_dp_mst_add_affected_dsc_crtcs(काष्ठा drm_atomic_state *state,
				  काष्ठा drm_dp_mst_topology_mgr *mgr);
पूर्णांक __must_check
drm_dp_atomic_release_vcpi_slots(काष्ठा drm_atomic_state *state,
				 काष्ठा drm_dp_mst_topology_mgr *mgr,
				 काष्ठा drm_dp_mst_port *port);
पूर्णांक drm_dp_send_घातer_upकरोwn_phy(काष्ठा drm_dp_mst_topology_mgr *mgr,
				 काष्ठा drm_dp_mst_port *port, bool घातer_up);
पूर्णांक drm_dp_send_query_stream_enc_status(काष्ठा drm_dp_mst_topology_mgr *mgr,
		काष्ठा drm_dp_mst_port *port,
		काष्ठा drm_dp_query_stream_enc_status_ack_reply *status);
पूर्णांक __must_check drm_dp_mst_atomic_check(काष्ठा drm_atomic_state *state);

व्योम drm_dp_mst_get_port_दो_स्मृति(काष्ठा drm_dp_mst_port *port);
व्योम drm_dp_mst_put_port_दो_स्मृति(काष्ठा drm_dp_mst_port *port);

काष्ठा drm_dp_aux *drm_dp_mst_dsc_aux_क्रम_port(काष्ठा drm_dp_mst_port *port);

बाह्य स्थिर काष्ठा drm_निजी_state_funcs drm_dp_mst_topology_state_funcs;

/**
 * __drm_dp_mst_state_iter_get - निजी atomic state iterator function क्रम
 * macro-पूर्णांकernal use
 * @state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @mgr: poपूर्णांकer to the &काष्ठा drm_dp_mst_topology_mgr iteration cursor
 * @old_state: optional poपूर्णांकer to the old &काष्ठा drm_dp_mst_topology_state
 * iteration cursor
 * @new_state: optional poपूर्णांकer to the new &काष्ठा drm_dp_mst_topology_state
 * iteration cursor
 * @i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * Used by क्रम_each_oldnew_mst_mgr_in_state(),
 * क्रम_each_old_mst_mgr_in_state(), and क्रम_each_new_mst_mgr_in_state(). Don't
 * call this directly.
 *
 * Returns:
 * True अगर the current &काष्ठा drm_निजी_obj is a &काष्ठा
 * drm_dp_mst_topology_mgr, false otherwise.
 */
अटल अंतरभूत bool
__drm_dp_mst_state_iter_get(काष्ठा drm_atomic_state *state,
			    काष्ठा drm_dp_mst_topology_mgr **mgr,
			    काष्ठा drm_dp_mst_topology_state **old_state,
			    काष्ठा drm_dp_mst_topology_state **new_state,
			    पूर्णांक i)
अणु
	काष्ठा __drm_निजी_objs_state *objs_state = &state->निजी_objs[i];

	अगर (objs_state->ptr->funcs != &drm_dp_mst_topology_state_funcs)
		वापस false;

	*mgr = to_dp_mst_topology_mgr(objs_state->ptr);
	अगर (old_state)
		*old_state = to_dp_mst_topology_state(objs_state->old_state);
	अगर (new_state)
		*new_state = to_dp_mst_topology_state(objs_state->new_state);

	वापस true;
पूर्ण

/**
 * क्रम_each_oldnew_mst_mgr_in_state - iterate over all DP MST topology
 * managers in an atomic update
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @mgr: &काष्ठा drm_dp_mst_topology_mgr iteration cursor
 * @old_state: &काष्ठा drm_dp_mst_topology_state iteration cursor क्रम the old
 * state
 * @new_state: &काष्ठा drm_dp_mst_topology_state iteration cursor क्रम the new
 * state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all DRM DP MST topology managers in an atomic update,
 * tracking both old and new state. This is useful in places where the state
 * delta needs to be considered, क्रम example in atomic check functions.
 */
#घोषणा क्रम_each_oldnew_mst_mgr_in_state(__state, mgr, old_state, new_state, __i) \
	क्रम ((__i) = 0; (__i) < (__state)->num_निजी_objs; (__i)++) \
		क्रम_each_अगर(__drm_dp_mst_state_iter_get((__state), &(mgr), &(old_state), &(new_state), (__i)))

/**
 * क्रम_each_old_mst_mgr_in_state - iterate over all DP MST topology managers
 * in an atomic update
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @mgr: &काष्ठा drm_dp_mst_topology_mgr iteration cursor
 * @old_state: &काष्ठा drm_dp_mst_topology_state iteration cursor क्रम the old
 * state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all DRM DP MST topology managers in an atomic update,
 * tracking only the old state. This is useful in disable functions, where we
 * need the old state the hardware is still in.
 */
#घोषणा क्रम_each_old_mst_mgr_in_state(__state, mgr, old_state, __i) \
	क्रम ((__i) = 0; (__i) < (__state)->num_निजी_objs; (__i)++) \
		क्रम_each_अगर(__drm_dp_mst_state_iter_get((__state), &(mgr), &(old_state), शून्य, (__i)))

/**
 * क्रम_each_new_mst_mgr_in_state - iterate over all DP MST topology managers
 * in an atomic update
 * @__state: &काष्ठा drm_atomic_state poपूर्णांकer
 * @mgr: &काष्ठा drm_dp_mst_topology_mgr iteration cursor
 * @new_state: &काष्ठा drm_dp_mst_topology_state iteration cursor क्रम the new
 * state
 * @__i: पूर्णांक iteration cursor, क्रम macro-पूर्णांकernal use
 *
 * This iterates over all DRM DP MST topology managers in an atomic update,
 * tracking only the new state. This is useful in enable functions, where we
 * need the new state the hardware should be in when the atomic commit
 * operation has completed.
 */
#घोषणा क्रम_each_new_mst_mgr_in_state(__state, mgr, new_state, __i) \
	क्रम ((__i) = 0; (__i) < (__state)->num_निजी_objs; (__i)++) \
		क्रम_each_अगर(__drm_dp_mst_state_iter_get((__state), &(mgr), शून्य, &(new_state), (__i)))

#पूर्ण_अगर
