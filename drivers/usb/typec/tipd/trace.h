<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम TI TPS6598x USB Power Delivery controller family
 *
 * Copyright (C) 2020 Purism SPC
 * Author: Guiकरो Gथञnther <agx@sigxcpu.org>
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM tps6598x

#अगर !defined(_TPS6598X_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TPS6598X_TRACE_H_

#समावेश "tps6598x.h"

#समावेश <linux/stringअगरy.h>
#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा show_irq_flags(flags) \
	__prपूर्णांक_flags_u64(flags, "|", \
		अणु TPS_REG_INT_PD_SOFT_RESET,			"PD_SOFT_RESET" पूर्ण, \
		अणु TPS_REG_INT_HARD_RESET,			"HARD_RESET" पूर्ण, \
		अणु TPS_REG_INT_PLUG_EVENT,			"PLUG_EVENT" पूर्ण, \
		अणु TPS_REG_INT_PR_SWAP_COMPLETE,			"PR_SWAP_COMPLETE" पूर्ण, \
		अणु TPS_REG_INT_DR_SWAP_COMPLETE,			"DR_SWAP_COMPLETE" पूर्ण, \
		अणु TPS_REG_INT_RDO_RECEIVED_FROM_SINK,		"RDO_RECEIVED_FROM_SINK" पूर्ण, \
		अणु TPS_REG_INT_BIST,				"BIST" पूर्ण, \
		अणु TPS_REG_INT_OVERCURRENT,			"OVERCURRENT" पूर्ण, \
		अणु TPS_REG_INT_ATTENTION_RECEIVED,		"ATTENTION_RECEIVED" पूर्ण, \
		अणु TPS_REG_INT_VDM_RECEIVED,			"VDM_RECEIVED" पूर्ण, \
		अणु TPS_REG_INT_NEW_CONTRACT_AS_CONSUMER,		"NEW_CONTRACT_AS_CONSUMER" पूर्ण, \
		अणु TPS_REG_INT_NEW_CONTRACT_AS_PROVIDER,		"NEW_CONTRACT_AS_PROVIDER" पूर्ण, \
		अणु TPS_REG_INT_SOURCE_CAP_MESSAGE_READY,		"SOURCE_CAP_MESSAGE_READY" पूर्ण, \
		अणु TPS_REG_INT_SINK_CAP_MESSAGE_READY,		"SINK_CAP_MESSAGE_READY" पूर्ण, \
		अणु TPS_REG_INT_PR_SWAP_REQUESTED,		"PR_SWAP_REQUESTED" पूर्ण, \
		अणु TPS_REG_INT_GOTO_MIN_RECEIVED,		"GOTO_MIN_RECEIVED" पूर्ण, \
		अणु TPS_REG_INT_USB_HOST_PRESENT,			"USB_HOST_PRESENT" पूर्ण, \
		अणु TPS_REG_INT_USB_HOST_PRESENT_NO_LONGER,	"USB_HOST_PRESENT_NO_LONGER" पूर्ण, \
		अणु TPS_REG_INT_HIGH_VOLTAGE_WARNING,		"HIGH_VOLTAGE_WARNING" पूर्ण, \
		अणु TPS_REG_INT_PP_SWITCH_CHANGED,		"PP_SWITCH_CHANGED" पूर्ण, \
		अणु TPS_REG_INT_POWER_STATUS_UPDATE,		"POWER_STATUS_UPDATE" पूर्ण, \
		अणु TPS_REG_INT_DATA_STATUS_UPDATE,		"DATA_STATUS_UPDATE" पूर्ण, \
		अणु TPS_REG_INT_STATUS_UPDATE,			"STATUS_UPDATE" पूर्ण, \
		अणु TPS_REG_INT_PD_STATUS_UPDATE,			"PD_STATUS_UPDATE" पूर्ण, \
		अणु TPS_REG_INT_ADC_LOW_THRESHOLD,		"ADC_LOW_THRESHOLD" पूर्ण, \
		अणु TPS_REG_INT_ADC_HIGH_THRESHOLD,		"ADC_HIGH_THRESHOLD" पूर्ण, \
		अणु TPS_REG_INT_CMD1_COMPLETE,			"CMD1_COMPLETE" पूर्ण, \
		अणु TPS_REG_INT_CMD2_COMPLETE,			"CMD2_COMPLETE" पूर्ण, \
		अणु TPS_REG_INT_ERROR_DEVICE_INCOMPATIBLE,	"ERROR_DEVICE_INCOMPATIBLE" पूर्ण, \
		अणु TPS_REG_INT_ERROR_CANNOT_PROVIDE_PWR,		"ERROR_CANNOT_PROVIDE_PWR" पूर्ण, \
		अणु TPS_REG_INT_ERROR_CAN_PROVIDE_PWR_LATER,	"ERROR_CAN_PROVIDE_PWR_LATER" पूर्ण, \
		अणु TPS_REG_INT_ERROR_POWER_EVENT_OCCURRED,	"ERROR_POWER_EVENT_OCCURRED" पूर्ण, \
		अणु TPS_REG_INT_ERROR_MISSING_GET_CAP_MESSAGE,	"ERROR_MISSING_GET_CAP_MESSAGE" पूर्ण, \
		अणु TPS_REG_INT_ERROR_PROTOCOL_ERROR,		"ERROR_PROTOCOL_ERROR" पूर्ण, \
		अणु TPS_REG_INT_ERROR_MESSAGE_DATA,		"ERROR_MESSAGE_DATA" पूर्ण, \
		अणु TPS_REG_INT_ERROR_DISCHARGE_FAILED,		"ERROR_DISCHARGE_FAILED" पूर्ण, \
		अणु TPS_REG_INT_SRC_TRANSITION,			"SRC_TRANSITION" पूर्ण, \
		अणु TPS_REG_INT_ERROR_UNABLE_TO_SOURCE,		"ERROR_UNABLE_TO_SOURCE" पूर्ण, \
		अणु TPS_REG_INT_VDM_ENTERED_MODE,			"VDM_ENTERED_MODE" पूर्ण, \
		अणु TPS_REG_INT_VDM_MSG_SENT,			"VDM_MSG_SENT" पूर्ण, \
		अणु TPS_REG_INT_DISCOVER_MODES_COMPLETE,		"DISCOVER_MODES_COMPLETE" पूर्ण, \
		अणु TPS_REG_INT_EXIT_MODES_COMPLETE,		"EXIT_MODES_COMPLETE" पूर्ण, \
		अणु TPS_REG_INT_USER_VID_ALT_MODE_ENTERED,	"USER_VID_ALT_MODE_ENTERED" पूर्ण, \
		अणु TPS_REG_INT_USER_VID_ALT_MODE_EXIT,		"USER_VID_ALT_MODE_EXIT" पूर्ण, \
		अणु TPS_REG_INT_USER_VID_ALT_MODE_ATTN_VDM,	"USER_VID_ALT_MODE_ATTN_VDM" पूर्ण, \
		अणु TPS_REG_INT_USER_VID_ALT_MODE_OTHER_VDM,	"USER_VID_ALT_MODE_OTHER_VDM" पूर्ण)

#घोषणा TPS6598X_STATUS_FLAGS_MASK (GENMASK(31, 0) ^ (TPS_STATUS_CONN_STATE_MASK | \
						      TPS_STATUS_PP_5V0_SWITCH_MASK | \
						      TPS_STATUS_PP_HV_SWITCH_MASK | \
						      TPS_STATUS_PP_EXT_SWITCH_MASK | \
						      TPS_STATUS_PP_CABLE_SWITCH_MASK | \
						      TPS_STATUS_POWER_SOURCE_MASK | \
						      TPS_STATUS_VBUS_STATUS_MASK | \
						      TPS_STATUS_USB_HOST_PRESENT_MASK | \
						      TPS_STATUS_LEGACY_MASK))

#घोषणा show_status_conn_state(status) \
	__prपूर्णांक_symbolic(TPS_STATUS_CONN_STATE((status)), \
		अणु TPS_STATUS_CONN_STATE_CONN_WITH_R_A,	"conn-Ra"  पूर्ण, \
		अणु TPS_STATUS_CONN_STATE_CONN_NO_R_A,	"conn-no-Ra" पूर्ण, \
		अणु TPS_STATUS_CONN_STATE_NO_CONN_R_A,	"no-conn-Ra" पूर्ण,	\
		अणु TPS_STATUS_CONN_STATE_DEBUG_CONN,	"debug"	 पूर्ण, \
		अणु TPS_STATUS_CONN_STATE_AUDIO_CONN,	"audio"	 पूर्ण, \
		अणु TPS_STATUS_CONN_STATE_DISABLED,	"disabled" पूर्ण, \
		अणु TPS_STATUS_CONN_STATE_NO_CONN,	"no-conn" पूर्ण)

#घोषणा show_status_pp_चयन_state(status) \
	__prपूर्णांक_symbolic(status, \
		अणु TPS_STATUS_PP_SWITCH_STATE_IN,	"in" पूर्ण, \
		अणु TPS_STATUS_PP_SWITCH_STATE_OUT,	"out" पूर्ण, \
		अणु TPS_STATUS_PP_SWITCH_STATE_FAULT,	"fault" पूर्ण, \
		अणु TPS_STATUS_PP_SWITCH_STATE_DISABLED,	"off" पूर्ण)

#घोषणा show_status_घातer_sources(status) \
	__prपूर्णांक_symbolic(TPS_STATUS_POWER_SOURCE(status), \
		अणु TPS_STATUS_POWER_SOURCE_VBUS,		"vbus" पूर्ण, \
		अणु TPS_STATUS_POWER_SOURCE_VIN_3P3,	"vin-3p3" पूर्ण, \
		अणु TPS_STATUS_POWER_SOURCE_DEAD_BAT,	"dead-battery" पूर्ण, \
		अणु TPS_STATUS_POWER_SOURCE_UNKNOWN,	"unknown" पूर्ण)

#घोषणा show_status_vbus_status(status) \
	__prपूर्णांक_symbolic(TPS_STATUS_VBUS_STATUS(status), \
		अणु TPS_STATUS_VBUS_STATUS_VSAFE0V,	"vSafe0V" पूर्ण, \
		अणु TPS_STATUS_VBUS_STATUS_VSAFE5V,	"vSafe5V" पूर्ण, \
		अणु TPS_STATUS_VBUS_STATUS_PD,		"pd" पूर्ण, \
		अणु TPS_STATUS_VBUS_STATUS_FAULT,		"fault" पूर्ण)

#घोषणा show_status_usb_host_present(status) \
	__prपूर्णांक_symbolic(TPS_STATUS_USB_HOST_PRESENT(status), \
		अणु TPS_STATUS_USB_HOST_PRESENT_PD_USB,	 "pd-usb" पूर्ण, \
		अणु TPS_STATUS_USB_HOST_PRESENT_NO_PD,	 "no-pd" पूर्ण, \
		अणु TPS_STATUS_USB_HOST_PRESENT_PD_NO_USB, "pd-no-usb" पूर्ण, \
		अणु TPS_STATUS_USB_HOST_PRESENT_NO,	 "no" पूर्ण)

#घोषणा show_status_legacy(status) \
	__prपूर्णांक_symbolic(TPS_STATUS_LEGACY(status),	     \
		अणु TPS_STATUS_LEGACY_SOURCE,		 "source" पूर्ण, \
		अणु TPS_STATUS_LEGACY_SINK,		 "sink" पूर्ण, \
		अणु TPS_STATUS_LEGACY_NO,			 "no" पूर्ण)

#घोषणा show_status_flags(flags) \
	__prपूर्णांक_flags((flags & TPS6598X_STATUS_FLAGS_MASK), "|", \
		      अणु TPS_STATUS_PLUG_PRESENT,	"PLUG_PRESENT" पूर्ण, \
		      अणु TPS_STATUS_PLUG_UPSIDE_DOWN,	"UPSIDE_DOWN" पूर्ण, \
		      अणु TPS_STATUS_PORTROLE,		"PORTROLE" पूर्ण, \
		      अणु TPS_STATUS_DATAROLE,		"DATAROLE" पूर्ण, \
		      अणु TPS_STATUS_VCONN,		"VCONN" पूर्ण, \
		      अणु TPS_STATUS_OVERCURRENT,		"OVERCURRENT" पूर्ण, \
		      अणु TPS_STATUS_GOTO_MIN_ACTIVE,	"GOTO_MIN_ACTIVE" पूर्ण, \
		      अणु TPS_STATUS_BIST,		"BIST" पूर्ण, \
		      अणु TPS_STATUS_HIGH_VOLAGE_WARNING,	"HIGH_VOLAGE_WARNING" पूर्ण, \
		      अणु TPS_STATUS_HIGH_LOW_VOLTAGE_WARNING, "HIGH_LOW_VOLTAGE_WARNING" पूर्ण)

#घोषणा show_घातer_status_source_sink(घातer_status) \
	__prपूर्णांक_symbolic(TPS_POWER_STATUS_SOURCESINK(घातer_status), \
		अणु 1, "sink" पूर्ण, \
		अणु 0, "source" पूर्ण)

#घोषणा show_घातer_status_typec_status(घातer_status) \
	__prपूर्णांक_symbolic(TPS_POWER_STATUS_PWROPMODE(घातer_status), \
		अणु TPS_POWER_STATUS_TYPEC_CURRENT_PD,  "pd" पूर्ण, \
		अणु TPS_POWER_STATUS_TYPEC_CURRENT_3A0, "3.0A" पूर्ण, \
		अणु TPS_POWER_STATUS_TYPEC_CURRENT_1A5, "1.5A" पूर्ण, \
		अणु TPS_POWER_STATUS_TYPEC_CURRENT_USB, "usb" पूर्ण)

#घोषणा show_घातer_status_bc12_status(घातer_status) \
	__prपूर्णांक_symbolic(TPS_POWER_STATUS_BC12_STATUS(घातer_status), \
		अणु TPS_POWER_STATUS_BC12_STATUS_DCP, "dcp" पूर्ण, \
		अणु TPS_POWER_STATUS_BC12_STATUS_CDP, "cdp" पूर्ण, \
		अणु TPS_POWER_STATUS_BC12_STATUS_SDP, "sdp" पूर्ण)

#घोषणा TPS_DATA_STATUS_FLAGS_MASK (GENMASK(31, 0) ^ (TPS_DATA_STATUS_DP_PIN_ASSIGNMENT_MASK | \
						      TPS_DATA_STATUS_TBT_CABLE_SPEED_MASK | \
						      TPS_DATA_STATUS_TBT_CABLE_GEN_MASK))

#घोषणा show_data_status_flags(data_status) \
	__prपूर्णांक_flags(data_status & TPS_DATA_STATUS_FLAGS_MASK, "|", \
		अणु TPS_DATA_STATUS_DATA_CONNECTION,	"DATA_CONNECTION" पूर्ण, \
		अणु TPS_DATA_STATUS_UPSIDE_DOWN,		"DATA_UPSIDE_DOWN" पूर्ण, \
		अणु TPS_DATA_STATUS_ACTIVE_CABLE,		"ACTIVE_CABLE" पूर्ण, \
		अणु TPS_DATA_STATUS_USB2_CONNECTION,	"USB2_CONNECTION" पूर्ण, \
		अणु TPS_DATA_STATUS_USB3_CONNECTION,	"USB3_CONNECTION" पूर्ण, \
		अणु TPS_DATA_STATUS_USB3_GEN2,		"USB3_GEN2" पूर्ण, \
		अणु TPS_DATA_STATUS_USB_DATA_ROLE,	"USB_DATA_ROLE" पूर्ण, \
		अणु TPS_DATA_STATUS_DP_CONNECTION,	"DP_CONNECTION" पूर्ण, \
		अणु TPS_DATA_STATUS_DP_SINK,		"DP_SINK" पूर्ण, \
		अणु TPS_DATA_STATUS_TBT_CONNECTION,	"TBT_CONNECTION" पूर्ण, \
		अणु TPS_DATA_STATUS_TBT_TYPE,		"TBT_TYPE" पूर्ण, \
		अणु TPS_DATA_STATUS_OPTICAL_CABLE,	"OPTICAL_CABLE" पूर्ण, \
		अणु TPS_DATA_STATUS_ACTIVE_LINK_TRAIN,	"ACTIVE_LINK_TRAIN" पूर्ण, \
		अणु TPS_DATA_STATUS_FORCE_LSX,		"FORCE_LSX" पूर्ण, \
		अणु TPS_DATA_STATUS_POWER_MISMATCH,	"POWER_MISMATCH" पूर्ण)

#घोषणा show_data_status_dp_pin_assignment(data_status) \
	__prपूर्णांक_symbolic(TPS_DATA_STATUS_DP_SPEC_PIN_ASSIGNMENT(data_status), \
		अणु TPS_DATA_STATUS_DP_SPEC_PIN_ASSIGNMENT_E, "E" पूर्ण, \
		अणु TPS_DATA_STATUS_DP_SPEC_PIN_ASSIGNMENT_F, "F" पूर्ण, \
		अणु TPS_DATA_STATUS_DP_SPEC_PIN_ASSIGNMENT_C, "C" पूर्ण, \
		अणु TPS_DATA_STATUS_DP_SPEC_PIN_ASSIGNMENT_D, "D" पूर्ण, \
		अणु TPS_DATA_STATUS_DP_SPEC_PIN_ASSIGNMENT_A, "A" पूर्ण, \
		अणु TPS_DATA_STATUS_DP_SPEC_PIN_ASSIGNMENT_B, "B" पूर्ण)

#घोषणा maybe_show_data_status_dp_pin_assignment(data_status) \
	(data_status & TPS_DATA_STATUS_DP_CONNECTION ? \
	 show_data_status_dp_pin_assignment(data_status) : "")

TRACE_EVENT(tps6598x_irq,
	    TP_PROTO(u64 event1,
		     u64 event2),
	    TP_ARGS(event1, event2),

	    TP_STRUCT__entry(
			     __field(u64, event1)
			     __field(u64, event2)
			     ),

	    TP_fast_assign(
			   __entry->event1 = event1;
			   __entry->event2 = event2;
			   ),

	    TP_prपूर्णांकk("event1=%s, event2=%s",
		      show_irq_flags(__entry->event1),
		      show_irq_flags(__entry->event2))
);

TRACE_EVENT(tps6598x_status,
	    TP_PROTO(u32 status),
	    TP_ARGS(status),

	    TP_STRUCT__entry(
			     __field(u32, status)
			     ),

	    TP_fast_assign(
			   __entry->status = status;
			   ),

	    TP_prपूर्णांकk("conn: %s, pp_5v0: %s, pp_hv: %s, pp_ext: %s, pp_cable: %s, "
		      "pwr-src: %s, vbus: %s, usb-host: %s, legacy: %s, flags: %s",
		      show_status_conn_state(__entry->status),
		      show_status_pp_चयन_state(TPS_STATUS_PP_5V0_SWITCH(__entry->status)),
		      show_status_pp_चयन_state(TPS_STATUS_PP_HV_SWITCH(__entry->status)),
		      show_status_pp_चयन_state(TPS_STATUS_PP_EXT_SWITCH(__entry->status)),
		      show_status_pp_चयन_state(TPS_STATUS_PP_CABLE_SWITCH(__entry->status)),
		      show_status_घातer_sources(__entry->status),
		      show_status_vbus_status(__entry->status),
		      show_status_usb_host_present(__entry->status),
		      show_status_legacy(__entry->status),
		      show_status_flags(__entry->status)
		    )
);

TRACE_EVENT(tps6598x_घातer_status,
	    TP_PROTO(u16 घातer_status),
	    TP_ARGS(घातer_status),

	    TP_STRUCT__entry(
			     __field(u16, घातer_status)
			     ),

	    TP_fast_assign(
			   __entry->घातer_status = घातer_status;
			   ),

	    TP_prपूर्णांकk("conn: %d, pwr-role: %s, typec: %s, bc: %s",
		      !!TPS_POWER_STATUS_CONNECTION(__entry->घातer_status),
		      show_घातer_status_source_sink(__entry->घातer_status),
		      show_घातer_status_typec_status(__entry->घातer_status),
		      show_घातer_status_bc12_status(__entry->घातer_status)
		    )
);

TRACE_EVENT(tps6598x_data_status,
	    TP_PROTO(u32 data_status),
	    TP_ARGS(data_status),

	    TP_STRUCT__entry(
			     __field(u32, data_status)
			     ),

	    TP_fast_assign(
			   __entry->data_status = data_status;
			   ),

	    TP_prपूर्णांकk("%s%s%s",
		      show_data_status_flags(__entry->data_status),
		      __entry->data_status & TPS_DATA_STATUS_DP_CONNECTION ? ", DP pinout " : "",
		      maybe_show_data_status_dp_pin_assignment(__entry->data_status)
		    )
);

#पूर्ण_अगर /* _TPS6598X_TRACE_H_ */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#समावेश <trace/define_trace.h>
