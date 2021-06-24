<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hyperv

#अगर !defined(_HV_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _HV_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(vmbus_hdr_msg,
	TP_PROTO(स्थिर काष्ठा vmbus_channel_message_header *hdr),
	TP_ARGS(hdr),
	TP_STRUCT__entry(__field(अचिन्हित पूर्णांक, msgtype)),
	TP_fast_assign(__entry->msgtype = hdr->msgtype;),
	TP_prपूर्णांकk("msgtype=%u", __entry->msgtype)
);

DEFINE_EVENT(vmbus_hdr_msg, vmbus_on_msg_dpc,
	TP_PROTO(स्थिर काष्ठा vmbus_channel_message_header *hdr),
	TP_ARGS(hdr)
);

DEFINE_EVENT(vmbus_hdr_msg, vmbus_on_message,
	TP_PROTO(स्थिर काष्ठा vmbus_channel_message_header *hdr),
	TP_ARGS(hdr)
);

TRACE_EVENT(vmbus_onoffer,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_offer_channel *offer),
	    TP_ARGS(offer),
	    TP_STRUCT__entry(
		    __field(u32, child_relid)
		    __field(u8, monitorid)
		    __field(u16, is_ddc_पूर्णांक)
		    __field(u32, connection_id)
		    __array(अक्षर, अगर_type, 16)
		    __array(अक्षर, अगर_instance, 16)
		    __field(u16, chn_flags)
		    __field(u16, mmio_mb)
		    __field(u16, sub_idx)
		    ),
	    TP_fast_assign(__entry->child_relid = offer->child_relid;
			   __entry->monitorid = offer->monitorid;
			   __entry->is_ddc_पूर्णांक = offer->is_dedicated_पूर्णांकerrupt;
			   __entry->connection_id = offer->connection_id;
			   export_guid(__entry->अगर_type, &offer->offer.अगर_type);
			   export_guid(__entry->अगर_instance, &offer->offer.अगर_instance);
			   __entry->chn_flags = offer->offer.chn_flags;
			   __entry->mmio_mb = offer->offer.mmio_megabytes;
			   __entry->sub_idx = offer->offer.sub_channel_index;
		    ),
	    TP_prपूर्णांकk("child_relid 0x%x, monitorid 0x%x, is_dedicated %d, "
		      "connection_id 0x%x, if_type %pUl, if_instance %pUl, "
		      "chn_flags 0x%x, mmio_megabytes %d, sub_channel_index %d",
		      __entry->child_relid, __entry->monitorid,
		      __entry->is_ddc_पूर्णांक, __entry->connection_id,
		      __entry->अगर_type, __entry->अगर_instance,
		      __entry->chn_flags, __entry->mmio_mb,
		      __entry->sub_idx
		    )
	);

TRACE_EVENT(vmbus_onoffer_rescind,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_rescind_offer *offer),
	    TP_ARGS(offer),
	    TP_STRUCT__entry(__field(u32, child_relid)),
	    TP_fast_assign(__entry->child_relid = offer->child_relid),
	    TP_prपूर्णांकk("child_relid 0x%x", __entry->child_relid)
	);

TRACE_EVENT(vmbus_onखोलो_result,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_खोलो_result *result),
	    TP_ARGS(result),
	    TP_STRUCT__entry(
		    __field(u32, child_relid)
		    __field(u32, खोलोid)
		    __field(u32, status)
		    ),
	    TP_fast_assign(__entry->child_relid = result->child_relid;
			   __entry->खोलोid = result->खोलोid;
			   __entry->status = result->status;
		    ),
	    TP_prपूर्णांकk("child_relid 0x%x, openid %d, status %d",
		      __entry->child_relid,  __entry->खोलोid,  __entry->status
		    )
	);

TRACE_EVENT(vmbus_ongpadl_created,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_gpadl_created *gpadlcreated),
	    TP_ARGS(gpadlcreated),
	    TP_STRUCT__entry(
		    __field(u32, child_relid)
		    __field(u32, gpadl)
		    __field(u32, status)
		    ),
	    TP_fast_assign(__entry->child_relid = gpadlcreated->child_relid;
			   __entry->gpadl = gpadlcreated->gpadl;
			   __entry->status = gpadlcreated->creation_status;
		    ),
	    TP_prपूर्णांकk("child_relid 0x%x, gpadl 0x%x, creation_status %d",
		      __entry->child_relid,  __entry->gpadl,  __entry->status
		    )
	);

TRACE_EVENT(vmbus_onmodअगरychannel_response,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_modअगरychannel_response *response),
	    TP_ARGS(response),
	    TP_STRUCT__entry(
		    __field(u32, child_relid)
		    __field(u32, status)
		    ),
	    TP_fast_assign(__entry->child_relid = response->child_relid;
			   __entry->status = response->status;
		    ),
	    TP_prपूर्णांकk("child_relid 0x%x, status %d",
		      __entry->child_relid,  __entry->status
		    )
	);

TRACE_EVENT(vmbus_ongpadl_tornकरोwn,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_gpadl_tornकरोwn *gpadltornकरोwn),
	    TP_ARGS(gpadltornकरोwn),
	    TP_STRUCT__entry(__field(u32, gpadl)),
	    TP_fast_assign(__entry->gpadl = gpadltornकरोwn->gpadl),
	    TP_prपूर्णांकk("gpadl 0x%x", __entry->gpadl)
	);

TRACE_EVENT(vmbus_onversion_response,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_version_response *response),
	    TP_ARGS(response),
	    TP_STRUCT__entry(
		    __field(u8, ver)
		    ),
	    TP_fast_assign(__entry->ver = response->version_supported;
		    ),
	    TP_prपूर्णांकk("version_supported %d", __entry->ver)
	);

TRACE_EVENT(vmbus_request_offers,
	    TP_PROTO(पूर्णांक ret),
	    TP_ARGS(ret),
	    TP_STRUCT__entry(__field(पूर्णांक, ret)),
	    TP_fast_assign(__entry->ret = ret),
	    TP_prपूर्णांकk("sending ret %d", __entry->ret)
	);

TRACE_EVENT(vmbus_खोलो,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_खोलो_channel *msg, पूर्णांक ret),
	    TP_ARGS(msg, ret),
	    TP_STRUCT__entry(
		    __field(u32, child_relid)
		    __field(u32, खोलोid)
		    __field(u32, gpadlhandle)
		    __field(u32, target_vp)
		    __field(u32, offset)
		    __field(पूर्णांक, ret)
		    ),
	    TP_fast_assign(
		    __entry->child_relid = msg->child_relid;
		    __entry->खोलोid = msg->खोलोid;
		    __entry->gpadlhandle = msg->ringbuffer_gpadlhandle;
		    __entry->target_vp = msg->target_vp;
		    __entry->offset = msg->करोwnstream_ringbuffer_pageoffset;
		    __entry->ret = ret;
		    ),
	    TP_prपूर्णांकk("sending child_relid 0x%x, openid %d, "
		      "gpadlhandle 0x%x, target_vp 0x%x, offset 0x%x, ret %d",
		      __entry->child_relid,  __entry->खोलोid,
		      __entry->gpadlhandle, __entry->target_vp,
		      __entry->offset, __entry->ret
		    )
	);

TRACE_EVENT(vmbus_बंद_पूर्णांकernal,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_बंद_channel *msg, पूर्णांक ret),
	    TP_ARGS(msg, ret),
	    TP_STRUCT__entry(
		    __field(u32, child_relid)
		    __field(पूर्णांक, ret)
		    ),
	    TP_fast_assign(
		    __entry->child_relid = msg->child_relid;
		    __entry->ret = ret;
		    ),
	    TP_prपूर्णांकk("sending child_relid 0x%x, ret %d", __entry->child_relid,
		    __entry->ret)
	);

TRACE_EVENT(vmbus_establish_gpadl_header,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_gpadl_header *msg, पूर्णांक ret),
	    TP_ARGS(msg, ret),
	    TP_STRUCT__entry(
		    __field(u32, child_relid)
		    __field(u32, gpadl)
		    __field(u16, range_buflen)
		    __field(u16, rangecount)
		    __field(पूर्णांक, ret)
		    ),
	    TP_fast_assign(
		    __entry->child_relid = msg->child_relid;
		    __entry->gpadl = msg->gpadl;
		    __entry->range_buflen = msg->range_buflen;
		    __entry->rangecount = msg->rangecount;
		    __entry->ret = ret;
		    ),
	    TP_prपूर्णांकk("sending child_relid 0x%x, gpadl 0x%x, range_buflen %d "
		      "rangecount %d, ret %d",
		      __entry->child_relid, __entry->gpadl,
		      __entry->range_buflen, __entry->rangecount, __entry->ret
		    )
	);

TRACE_EVENT(vmbus_establish_gpadl_body,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_gpadl_body *msg, पूर्णांक ret),
	    TP_ARGS(msg, ret),
	    TP_STRUCT__entry(
		    __field(u32, msgnumber)
		    __field(u32, gpadl)
		    __field(पूर्णांक, ret)
		    ),
	    TP_fast_assign(
		    __entry->msgnumber = msg->msgnumber;
		    __entry->gpadl = msg->gpadl;
		    __entry->ret = ret;
		    ),
	    TP_prपूर्णांकk("sending msgnumber %d, gpadl 0x%x, ret %d",
		      __entry->msgnumber, __entry->gpadl, __entry->ret
		    )
	);

TRACE_EVENT(vmbus_tearकरोwn_gpadl,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_gpadl_tearकरोwn *msg, पूर्णांक ret),
	    TP_ARGS(msg, ret),
	    TP_STRUCT__entry(
		    __field(u32, child_relid)
		    __field(u32, gpadl)
		    __field(पूर्णांक, ret)
		    ),
	    TP_fast_assign(
		    __entry->child_relid = msg->child_relid;
		    __entry->gpadl = msg->gpadl;
		    __entry->ret = ret;
		    ),
	    TP_prपूर्णांकk("sending child_relid 0x%x, gpadl 0x%x, ret %d",
		      __entry->child_relid, __entry->gpadl, __entry->ret
		    )
	);

TRACE_EVENT(vmbus_negotiate_version,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_initiate_contact *msg, पूर्णांक ret),
	    TP_ARGS(msg, ret),
	    TP_STRUCT__entry(
		    __field(u32, ver)
		    __field(u32, target_vcpu)
		    __field(पूर्णांक, ret)
		    __field(u64, पूर्णांक_page)
		    __field(u64, mon_page1)
		    __field(u64, mon_page2)
		    ),
	    TP_fast_assign(
		    __entry->ver = msg->vmbus_version_requested;
		    __entry->target_vcpu = msg->target_vcpu;
		    __entry->पूर्णांक_page = msg->पूर्णांकerrupt_page;
		    __entry->mon_page1 = msg->monitor_page1;
		    __entry->mon_page2 = msg->monitor_page2;
		    __entry->ret = ret;
		    ),
	    TP_prपूर्णांकk("sending vmbus_version_requested %d, target_vcpu 0x%x, "
		      "pages %llx:%llx:%llx, ret %d",
		      __entry->ver, __entry->target_vcpu, __entry->पूर्णांक_page,
		      __entry->mon_page1, __entry->mon_page2, __entry->ret
		    )
	);

TRACE_EVENT(vmbus_release_relid,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_relid_released *msg, पूर्णांक ret),
	    TP_ARGS(msg, ret),
	    TP_STRUCT__entry(
		    __field(u32, child_relid)
		    __field(पूर्णांक, ret)
		    ),
	    TP_fast_assign(
		    __entry->child_relid = msg->child_relid;
		    __entry->ret = ret;
		    ),
	    TP_prपूर्णांकk("sending child_relid 0x%x, ret %d",
		      __entry->child_relid, __entry->ret
		    )
	);

TRACE_EVENT(vmbus_send_tl_connect_request,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_tl_connect_request *msg,
		     पूर्णांक ret),
	    TP_ARGS(msg, ret),
	    TP_STRUCT__entry(
		    __array(अक्षर, guest_id, 16)
		    __array(अक्षर, host_id, 16)
		    __field(पूर्णांक, ret)
		    ),
	    TP_fast_assign(
		    export_guid(__entry->guest_id, &msg->guest_endpoपूर्णांक_id);
		    export_guid(__entry->host_id, &msg->host_service_id);
		    __entry->ret = ret;
		    ),
	    TP_prपूर्णांकk("sending guest_endpoint_id %pUl, host_service_id %pUl, "
		      "ret %d",
		      __entry->guest_id, __entry->host_id, __entry->ret
		    )
	);

TRACE_EVENT(vmbus_send_modअगरychannel,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel_modअगरychannel *msg,
		     पूर्णांक ret),
	    TP_ARGS(msg, ret),
	    TP_STRUCT__entry(
		    __field(u32, child_relid)
		    __field(u32, target_vp)
		    __field(पूर्णांक, ret)
		    ),
	    TP_fast_assign(
		    __entry->child_relid = msg->child_relid;
		    __entry->target_vp = msg->target_vp;
		    __entry->ret = ret;
		    ),
	    TP_prपूर्णांकk("binding child_relid 0x%x to target_vp 0x%x, ret %d",
		      __entry->child_relid, __entry->target_vp, __entry->ret
		    )
	);

DECLARE_EVENT_CLASS(vmbus_channel,
	TP_PROTO(स्थिर काष्ठा vmbus_channel *channel),
	TP_ARGS(channel),
	TP_STRUCT__entry(__field(u32, relid)),
	TP_fast_assign(__entry->relid = channel->offermsg.child_relid),
	TP_prपूर्णांकk("relid 0x%x", __entry->relid)
);

DEFINE_EVENT(vmbus_channel, vmbus_chan_sched,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel *channel),
	    TP_ARGS(channel)
);

DEFINE_EVENT(vmbus_channel, vmbus_setevent,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel *channel),
	    TP_ARGS(channel)
);

DEFINE_EVENT(vmbus_channel, vmbus_on_event,
	    TP_PROTO(स्थिर काष्ठा vmbus_channel *channel),
	    TP_ARGS(channel)
);

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता hv_trace
#पूर्ण_अगर /* _HV_TRACE_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
