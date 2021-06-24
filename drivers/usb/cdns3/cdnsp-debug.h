<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Cadence CDNSP DRD Driver.
 *
 * Copyright (C) 2020 Cadence.
 *
 * Author: Pawel Laszczak <pawell@cadence.com>
 *
 */
#अगर_अघोषित __LINUX_CDNSP_DEBUG
#घोषणा __LINUX_CDNSP_DEBUG

अटल अंतरभूत स्थिर अक्षर *cdnsp_trb_comp_code_string(u8 status)
अणु
	चयन (status) अणु
	हाल COMP_INVALID:
		वापस "Invalid";
	हाल COMP_SUCCESS:
		वापस "Success";
	हाल COMP_DATA_BUFFER_ERROR:
		वापस "Data Buffer Error";
	हाल COMP_BABBLE_DETECTED_ERROR:
		वापस "Babble Detected";
	हाल COMP_TRB_ERROR:
		वापस "TRB Error";
	हाल COMP_RESOURCE_ERROR:
		वापस "Resource Error";
	हाल COMP_NO_SLOTS_AVAILABLE_ERROR:
		वापस "No Slots Available Error";
	हाल COMP_INVALID_STREAM_TYPE_ERROR:
		वापस "Invalid Stream Type Error";
	हाल COMP_SLOT_NOT_ENABLED_ERROR:
		वापस "Slot Not Enabled Error";
	हाल COMP_ENDPOINT_NOT_ENABLED_ERROR:
		वापस "Endpoint Not Enabled Error";
	हाल COMP_SHORT_PACKET:
		वापस "Short Packet";
	हाल COMP_RING_UNDERRUN:
		वापस "Ring Underrun";
	हाल COMP_RING_OVERRUN:
		वापस "Ring Overrun";
	हाल COMP_VF_EVENT_RING_FULL_ERROR:
		वापस "VF Event Ring Full Error";
	हाल COMP_PARAMETER_ERROR:
		वापस "Parameter Error";
	हाल COMP_CONTEXT_STATE_ERROR:
		वापस "Context State Error";
	हाल COMP_EVENT_RING_FULL_ERROR:
		वापस "Event Ring Full Error";
	हाल COMP_INCOMPATIBLE_DEVICE_ERROR:
		वापस "Incompatible Device Error";
	हाल COMP_MISSED_SERVICE_ERROR:
		वापस "Missed Service Error";
	हाल COMP_COMMAND_RING_STOPPED:
		वापस "Command Ring Stopped";
	हाल COMP_COMMAND_ABORTED:
		वापस "Command Aborted";
	हाल COMP_STOPPED:
		वापस "Stopped";
	हाल COMP_STOPPED_LENGTH_INVALID:
		वापस "Stopped - Length Invalid";
	हाल COMP_STOPPED_SHORT_PACKET:
		वापस "Stopped - Short Packet";
	हाल COMP_MAX_EXIT_LATENCY_TOO_LARGE_ERROR:
		वापस "Max Exit Latency Too Large Error";
	हाल COMP_ISOCH_BUFFER_OVERRUN:
		वापस "Isoch Buffer Overrun";
	हाल COMP_EVENT_LOST_ERROR:
		वापस "Event Lost Error";
	हाल COMP_UNDEFINED_ERROR:
		वापस "Undefined Error";
	हाल COMP_INVALID_STREAM_ID_ERROR:
		वापस "Invalid Stream ID Error";
	शेष:
		वापस "Unknown!!";
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *cdnsp_trb_type_string(u8 type)
अणु
	चयन (type) अणु
	हाल TRB_NORMAL:
		वापस "Normal";
	हाल TRB_SETUP:
		वापस "Setup Stage";
	हाल TRB_DATA:
		वापस "Data Stage";
	हाल TRB_STATUS:
		वापस "Status Stage";
	हाल TRB_ISOC:
		वापस "Isoch";
	हाल TRB_LINK:
		वापस "Link";
	हाल TRB_EVENT_DATA:
		वापस "Event Data";
	हाल TRB_TR_NOOP:
		वापस "No-Op";
	हाल TRB_ENABLE_SLOT:
		वापस "Enable Slot Command";
	हाल TRB_DISABLE_SLOT:
		वापस "Disable Slot Command";
	हाल TRB_ADDR_DEV:
		वापस "Address Device Command";
	हाल TRB_CONFIG_EP:
		वापस "Configure Endpoint Command";
	हाल TRB_EVAL_CONTEXT:
		वापस "Evaluate Context Command";
	हाल TRB_RESET_EP:
		वापस "Reset Endpoint Command";
	हाल TRB_STOP_RING:
		वापस "Stop Ring Command";
	हाल TRB_SET_DEQ:
		वापस "Set TR Dequeue Pointer Command";
	हाल TRB_RESET_DEV:
		वापस "Reset Device Command";
	हाल TRB_FORCE_HEADER:
		वापस "Force Header Command";
	हाल TRB_CMD_NOOP:
		वापस "No-Op Command";
	हाल TRB_TRANSFER:
		वापस "Transfer Event";
	हाल TRB_COMPLETION:
		वापस "Command Completion Event";
	हाल TRB_PORT_STATUS:
		वापस "Port Status Change Event";
	हाल TRB_HC_EVENT:
		वापस "Device Controller Event";
	हाल TRB_MFINDEX_WRAP:
		वापस "MFINDEX Wrap Event";
	हाल TRB_ENDPOINT_NRDY:
		वापस "Endpoint Not ready";
	हाल TRB_HALT_ENDPOINT:
		वापस "Halt Endpoint";
	हाल TRB_FLUSH_ENDPOINT:
		वापस "FLush Endpoint";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *cdnsp_ring_type_string(क्रमागत cdnsp_ring_type type)
अणु
	चयन (type) अणु
	हाल TYPE_CTRL:
		वापस "CTRL";
	हाल TYPE_ISOC:
		वापस "ISOC";
	हाल TYPE_BULK:
		वापस "BULK";
	हाल TYPE_INTR:
		वापस "INTR";
	हाल TYPE_STREAM:
		वापस "STREAM";
	हाल TYPE_COMMAND:
		वापस "CMD";
	हाल TYPE_EVENT:
		वापस "EVENT";
	पूर्ण

	वापस "UNKNOWN";
पूर्ण

अटल अंतरभूत अक्षर *cdnsp_slot_state_string(u32 state)
अणु
	चयन (state) अणु
	हाल SLOT_STATE_ENABLED:
		वापस "enabled/disabled";
	हाल SLOT_STATE_DEFAULT:
		वापस "default";
	हाल SLOT_STATE_ADDRESSED:
		वापस "addressed";
	हाल SLOT_STATE_CONFIGURED:
		वापस "configured";
	शेष:
		वापस "reserved";
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *cdnsp_decode_trb(अक्षर *str, माप_प्रकार size, u32 field0,
					   u32 field1, u32 field2, u32 field3)
अणु
	पूर्णांक ep_id = TRB_TO_EP_INDEX(field3) - 1;
	पूर्णांक type = TRB_FIELD_TO_TYPE(field3);
	अचिन्हित पूर्णांक ep_num;
	पूर्णांक ret = 0;
	u32 temp;

	ep_num = DIV_ROUND_UP(ep_id, 2);

	चयन (type) अणु
	हाल TRB_LINK:
		ret += snम_लिखो(str, size,
				"LINK %08x%08x intr %ld type '%s' flags %c:%c:%c:%c",
				field1, field0, GET_INTR_TARGET(field2),
				cdnsp_trb_type_string(type),
				field3 & TRB_IOC ? 'I' : 'i',
				field3 & TRB_CHAIN ? 'C' : 'c',
				field3 & TRB_TC ? 'T' : 't',
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_TRANSFER:
	हाल TRB_COMPLETION:
	हाल TRB_PORT_STATUS:
	हाल TRB_HC_EVENT:
		ret += snम_लिखो(str, size,
				"ep%d%s(%d) type '%s' TRB %08x%08x status '%s'"
				" len %ld slot %ld flags %c:%c",
				ep_num, ep_id % 2 ? "out" : "in",
				TRB_TO_EP_INDEX(field3),
				cdnsp_trb_type_string(type), field1, field0,
				cdnsp_trb_comp_code_string(GET_COMP_CODE(field2)),
				EVENT_TRB_LEN(field2), TRB_TO_SLOT_ID(field3),
				field3 & EVENT_DATA ? 'E' : 'e',
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_MFINDEX_WRAP:
		ret += snम_लिखो(str, size, "%s: flags %c",
				cdnsp_trb_type_string(type),
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_SETUP:
		ret += snम_लिखो(str, size,
				"type '%s' bRequestType %02x bRequest %02x "
				"wValue %02x%02x wIndex %02x%02x wLength %d "
				"length %ld TD size %ld intr %ld Setup ID %ld "
				"flags %c:%c:%c",
				cdnsp_trb_type_string(type),
				field0 & 0xff,
				(field0 & 0xff00) >> 8,
				(field0 & 0xff000000) >> 24,
				(field0 & 0xff0000) >> 16,
				(field1 & 0xff00) >> 8,
				field1 & 0xff,
				(field1 & 0xff000000) >> 16 |
				(field1 & 0xff0000) >> 16,
				TRB_LEN(field2), GET_TD_SIZE(field2),
				GET_INTR_TARGET(field2),
				TRB_SETUPID_TO_TYPE(field3),
				field3 & TRB_IDT ? 'D' : 'd',
				field3 & TRB_IOC ? 'I' : 'i',
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_DATA:
		ret += snम_लिखो(str, size,
				"type '%s' Buffer %08x%08x length %ld TD size %ld "
				"intr %ld flags %c:%c:%c:%c:%c:%c:%c",
				cdnsp_trb_type_string(type),
				field1, field0, TRB_LEN(field2),
				GET_TD_SIZE(field2),
				GET_INTR_TARGET(field2),
				field3 & TRB_IDT ? 'D' : 'i',
				field3 & TRB_IOC ? 'I' : 'i',
				field3 & TRB_CHAIN ? 'C' : 'c',
				field3 & TRB_NO_SNOOP ? 'S' : 's',
				field3 & TRB_ISP ? 'I' : 'i',
				field3 & TRB_ENT ? 'E' : 'e',
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_STATUS:
		ret += snम_लिखो(str, size,
				"Buffer %08x%08x length %ld TD size %ld intr"
				"%ld type '%s' flags %c:%c:%c:%c",
				field1, field0, TRB_LEN(field2),
				GET_TD_SIZE(field2),
				GET_INTR_TARGET(field2),
				cdnsp_trb_type_string(type),
				field3 & TRB_IOC ? 'I' : 'i',
				field3 & TRB_CHAIN ? 'C' : 'c',
				field3 & TRB_ENT ? 'E' : 'e',
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_NORMAL:
	हाल TRB_ISOC:
	हाल TRB_EVENT_DATA:
	हाल TRB_TR_NOOP:
		ret += snम_लिखो(str, size,
				"type '%s' Buffer %08x%08x length %ld "
				"TD size %ld intr %ld "
				"flags %c:%c:%c:%c:%c:%c:%c:%c:%c",
				cdnsp_trb_type_string(type),
				field1, field0, TRB_LEN(field2),
				GET_TD_SIZE(field2),
				GET_INTR_TARGET(field2),
				field3 & TRB_BEI ? 'B' : 'b',
				field3 & TRB_IDT ? 'T' : 't',
				field3 & TRB_IOC ? 'I' : 'i',
				field3 & TRB_CHAIN ? 'C' : 'c',
				field3 & TRB_NO_SNOOP ? 'S' : 's',
				field3 & TRB_ISP ? 'I' : 'i',
				field3 & TRB_ENT ? 'E' : 'e',
				field3 & TRB_CYCLE ? 'C' : 'c',
				!(field3 & TRB_EVENT_INVALIDATE) ? 'V' : 'v');
		अवरोध;
	हाल TRB_CMD_NOOP:
	हाल TRB_ENABLE_SLOT:
		ret += snम_लिखो(str, size, "%s: flags %c",
				cdnsp_trb_type_string(type),
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_DISABLE_SLOT:
		ret += snम_लिखो(str, size, "%s: slot %ld flags %c",
				cdnsp_trb_type_string(type),
				TRB_TO_SLOT_ID(field3),
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_ADDR_DEV:
		ret += snम_लिखो(str, size,
				"%s: ctx %08x%08x slot %ld flags %c:%c",
				cdnsp_trb_type_string(type), field1, field0,
				TRB_TO_SLOT_ID(field3),
				field3 & TRB_BSR ? 'B' : 'b',
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_CONFIG_EP:
		ret += snम_लिखो(str, size,
				"%s: ctx %08x%08x slot %ld flags %c:%c",
				cdnsp_trb_type_string(type), field1, field0,
				TRB_TO_SLOT_ID(field3),
				field3 & TRB_DC ? 'D' : 'd',
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_EVAL_CONTEXT:
		ret += snम_लिखो(str, size,
				"%s: ctx %08x%08x slot %ld flags %c",
				cdnsp_trb_type_string(type), field1, field0,
				TRB_TO_SLOT_ID(field3),
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_RESET_EP:
	हाल TRB_HALT_ENDPOINT:
	हाल TRB_FLUSH_ENDPOINT:
		ret += snम_लिखो(str, size,
				"%s: ep%d%s(%d) ctx %08x%08x slot %ld flags %c",
				cdnsp_trb_type_string(type),
				ep_num, ep_id % 2 ? "out" : "in",
				TRB_TO_EP_INDEX(field3), field1, field0,
				TRB_TO_SLOT_ID(field3),
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_STOP_RING:
		ret += snम_लिखो(str, size,
				"%s: ep%d%s(%d) slot %ld sp %d flags %c",
				cdnsp_trb_type_string(type),
				ep_num, ep_id % 2 ? "out" : "in",
				TRB_TO_EP_INDEX(field3),
				TRB_TO_SLOT_ID(field3),
				TRB_TO_SUSPEND_PORT(field3),
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_SET_DEQ:
		ret += snम_लिखो(str, size,
				"%s: ep%d%s(%d) deq %08x%08x stream %ld slot %ld  flags %c",
				cdnsp_trb_type_string(type),
				ep_num, ep_id % 2 ? "out" : "in",
				TRB_TO_EP_INDEX(field3), field1, field0,
				TRB_TO_STREAM_ID(field2),
				TRB_TO_SLOT_ID(field3),
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_RESET_DEV:
		ret += snम_लिखो(str, size, "%s: slot %ld flags %c",
				cdnsp_trb_type_string(type),
				TRB_TO_SLOT_ID(field3),
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	हाल TRB_ENDPOINT_NRDY:
		temp  = TRB_TO_HOST_STREAM(field2);

		ret += snम_लिखो(str, size,
				"%s: ep%d%s(%d) H_SID %x%s%s D_SID %lx flags %c:%c",
				cdnsp_trb_type_string(type),
				ep_num, ep_id % 2 ? "out" : "in",
				TRB_TO_EP_INDEX(field3), temp,
				temp == STREAM_PRIME_ACK ? "(PRIME)" : "",
				temp == STREAM_REJECTED ? "(REJECTED)" : "",
				TRB_TO_DEV_STREAM(field0),
				field3 & TRB_STAT ? 'S' : 's',
				field3 & TRB_CYCLE ? 'C' : 'c');
		अवरोध;
	शेष:
		ret += snम_लिखो(str, size,
				"type '%s' -> raw %08x %08x %08x %08x",
				cdnsp_trb_type_string(type),
				field0, field1, field2, field3);
	पूर्ण

	वापस str;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *cdnsp_decode_slot_context(u32 info, u32 info2,
						    u32 पूर्णांक_target, u32 state)
अणु
	अटल अक्षर str[1024];
	पूर्णांक ret = 0;
	u32 speed;
	अक्षर *s;

	speed = info & DEV_SPEED;

	चयन (speed) अणु
	हाल SLOT_SPEED_FS:
		s = "full-speed";
		अवरोध;
	हाल SLOT_SPEED_HS:
		s = "high-speed";
		अवरोध;
	हाल SLOT_SPEED_SS:
		s = "super-speed";
		अवरोध;
	हाल SLOT_SPEED_SSP:
		s = "super-speed plus";
		अवरोध;
	शेष:
		s = "UNKNOWN speed";
	पूर्ण

	ret = प्र_लिखो(str, "%s Ctx Entries %d",
		      s, (info & LAST_CTX_MASK) >> 27);

	ret += प्र_लिखो(str + ret, " [Intr %ld] Addr %ld State %s",
		       GET_INTR_TARGET(पूर्णांक_target), state & DEV_ADDR_MASK,
		       cdnsp_slot_state_string(GET_SLOT_STATE(state)));

	वापस str;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *cdnsp_portsc_link_state_string(u32 portsc)
अणु
	चयन (portsc & PORT_PLS_MASK) अणु
	हाल XDEV_U0:
		वापस "U0";
	हाल XDEV_U1:
		वापस "U1";
	हाल XDEV_U2:
		वापस "U2";
	हाल XDEV_U3:
		वापस "U3";
	हाल XDEV_DISABLED:
		वापस "Disabled";
	हाल XDEV_RXDETECT:
		वापस "RxDetect";
	हाल XDEV_INACTIVE:
		वापस "Inactive";
	हाल XDEV_POLLING:
		वापस "Polling";
	हाल XDEV_RECOVERY:
		वापस "Recovery";
	हाल XDEV_HOT_RESET:
		वापस "Hot Reset";
	हाल XDEV_COMP_MODE:
		वापस "Compliance mode";
	हाल XDEV_TEST_MODE:
		वापस "Test mode";
	हाल XDEV_RESUME:
		वापस "Resume";
	शेष:
		अवरोध;
	पूर्ण

	वापस "Unknown";
पूर्ण

अटल अंतरभूत स्थिर अक्षर *cdnsp_decode_portsc(अक्षर *str, माप_प्रकार size,
					      u32 portsc)
अणु
	पूर्णांक ret;

	ret = snम_लिखो(str, size, "%s %s %s Link:%s PortSpeed:%d ",
		       portsc & PORT_POWER ? "Powered" : "Powered-off",
		       portsc & PORT_CONNECT ? "Connected" : "Not-connected",
		       portsc & PORT_PED ? "Enabled" : "Disabled",
		       cdnsp_portsc_link_state_string(portsc),
		       DEV_PORT_SPEED(portsc));

	अगर (portsc & PORT_RESET)
		ret += snम_लिखो(str + ret, size - ret, "In-Reset ");

	ret += snम_लिखो(str + ret, size - ret, "Change: ");
	अगर (portsc & PORT_CSC)
		ret += snम_लिखो(str + ret, size - ret, "CSC ");
	अगर (portsc & PORT_WRC)
		ret += snम_लिखो(str + ret, size - ret, "WRC ");
	अगर (portsc & PORT_RC)
		ret += snम_लिखो(str + ret, size - ret, "PRC ");
	अगर (portsc & PORT_PLC)
		ret += snम_लिखो(str + ret, size - ret, "PLC ");
	अगर (portsc & PORT_CEC)
		ret += snम_लिखो(str + ret, size - ret, "CEC ");
	ret += snम_लिखो(str + ret, size - ret, "Wake: ");
	अगर (portsc & PORT_WKCONN_E)
		ret += snम_लिखो(str + ret, size - ret, "WCE ");
	अगर (portsc & PORT_WKDISC_E)
		ret += snम_लिखो(str + ret, size - ret, "WDE ");

	वापस str;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *cdnsp_ep_state_string(u8 state)
अणु
	चयन (state) अणु
	हाल EP_STATE_DISABLED:
		वापस "disabled";
	हाल EP_STATE_RUNNING:
		वापस "running";
	हाल EP_STATE_HALTED:
		वापस "halted";
	हाल EP_STATE_STOPPED:
		वापस "stopped";
	हाल EP_STATE_ERROR:
		वापस "error";
	शेष:
		वापस "INVALID";
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *cdnsp_ep_type_string(u8 type)
अणु
	चयन (type) अणु
	हाल ISOC_OUT_EP:
		वापस "Isoc OUT";
	हाल BULK_OUT_EP:
		वापस "Bulk OUT";
	हाल INT_OUT_EP:
		वापस "Int OUT";
	हाल CTRL_EP:
		वापस "Ctrl";
	हाल ISOC_IN_EP:
		वापस "Isoc IN";
	हाल BULK_IN_EP:
		वापस "Bulk IN";
	हाल INT_IN_EP:
		वापस "Int IN";
	शेष:
		वापस "INVALID";
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *cdnsp_decode_ep_context(अक्षर *str, माप_प्रकार size,
						  u32 info, u32 info2,
						  u64 deq, u32 tx_info)
अणु
	u8 max_pstr, ep_state, पूर्णांकerval, ep_type, burst, cerr, mult;
	bool lsa, hid;
	u16 maxp, avg;
	u32 esit;
	पूर्णांक ret;

	esit = CTX_TO_MAX_ESIT_PAYLOAD_HI(info) << 16 |
	       CTX_TO_MAX_ESIT_PAYLOAD_LO(tx_info);

	ep_state = info & EP_STATE_MASK;
	max_pstr = CTX_TO_EP_MAXPSTREAMS(info);
	पूर्णांकerval = CTX_TO_EP_INTERVAL(info);
	mult = CTX_TO_EP_MULT(info) + 1;
	lsa = !!(info & EP_HAS_LSA);

	cerr = (info2 & (3 << 1)) >> 1;
	ep_type = CTX_TO_EP_TYPE(info2);
	hid = !!(info2 & (1 << 7));
	burst = CTX_TO_MAX_BURST(info2);
	maxp = MAX_PACKET_DECODED(info2);

	avg = EP_AVG_TRB_LENGTH(tx_info);

	ret = snम_लिखो(str, size, "State %s mult %d max P. Streams %d %s",
		       cdnsp_ep_state_string(ep_state), mult,
		       max_pstr, lsa ? "LSA " : "");

	ret += snम_लिखो(str + ret, size - ret,
			"interval %d us max ESIT payload %d CErr %d ",
			(1 << पूर्णांकerval) * 125, esit, cerr);

	ret += snम_लिखो(str + ret, size - ret,
			"Type %s %sburst %d maxp %d deq %016llx ",
			cdnsp_ep_type_string(ep_type), hid ? "HID" : "",
			burst, maxp, deq);

	ret += snम_लिखो(str + ret, size - ret, "avg trb len %d", avg);

	वापस str;
पूर्ण

#पूर्ण_अगर /*__LINUX_CDNSP_DEBUG*/
