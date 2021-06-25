<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Based on net/mac80211/trace.h */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mac802154

#अगर !defined(__MAC802154_DRIVER_TRACE) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __MAC802154_DRIVER_TRACE

#समावेश <linux/tracepoपूर्णांक.h>

#समावेश <net/mac802154.h>
#समावेश "ieee802154_i.h"

#घोषणा MAXNAME		32
#घोषणा LOCAL_ENTRY	__array(अक्षर, wpan_phy_name, MAXNAME)
#घोषणा LOCAL_ASSIGN	strlcpy(__entry->wpan_phy_name, \
				wpan_phy_name(local->hw.phy), MAXNAME)
#घोषणा LOCAL_PR_FMT	"%s"
#घोषणा LOCAL_PR_ARG	__entry->wpan_phy_name

#घोषणा CCA_ENTRY __field(क्रमागत nl802154_cca_modes, cca_mode) \
		  __field(क्रमागत nl802154_cca_opts, cca_opt)
#घोषणा CCA_ASSIGN \
	करो अणु                                     \
		(__entry->cca_mode) = cca->mode; \
		(__entry->cca_opt) = cca->opt;   \
	पूर्ण जबतक (0)
#घोषणा CCA_PR_FMT "cca_mode: %d, cca_opt: %d"
#घोषणा CCA_PR_ARG __entry->cca_mode, __entry->cca_opt

#घोषणा BOOL_TO_STR(bo) (bo) ? "true" : "false"

/* Tracing क्रम driver callbacks */

DECLARE_EVENT_CLASS(local_only_evt4,
	TP_PROTO(काष्ठा ieee802154_local *local),
	TP_ARGS(local),
	TP_STRUCT__entry(
		LOCAL_ENTRY
	),
	TP_fast_assign(
		LOCAL_ASSIGN;
	),
	TP_prपूर्णांकk(LOCAL_PR_FMT, LOCAL_PR_ARG)
);

DEFINE_EVENT(local_only_evt4, 802154_drv_वापस_व्योम,
	TP_PROTO(काष्ठा ieee802154_local *local),
	TP_ARGS(local)
);

TRACE_EVENT(802154_drv_वापस_पूर्णांक,
	TP_PROTO(काष्ठा ieee802154_local *local, पूर्णांक ret),
	TP_ARGS(local, ret),
	TP_STRUCT__entry(
		LOCAL_ENTRY
		__field(पूर्णांक, ret)
	),
	TP_fast_assign(
		LOCAL_ASSIGN;
		__entry->ret = ret;
	),
	TP_prपूर्णांकk(LOCAL_PR_FMT ", returned: %d", LOCAL_PR_ARG,
		  __entry->ret)
);

DEFINE_EVENT(local_only_evt4, 802154_drv_start,
	TP_PROTO(काष्ठा ieee802154_local *local),
	TP_ARGS(local)
);

DEFINE_EVENT(local_only_evt4, 802154_drv_stop,
	TP_PROTO(काष्ठा ieee802154_local *local),
	TP_ARGS(local)
);

TRACE_EVENT(802154_drv_set_channel,
	TP_PROTO(काष्ठा ieee802154_local *local, u8 page, u8 channel),
	TP_ARGS(local, page, channel),
	TP_STRUCT__entry(
		LOCAL_ENTRY
		__field(u8, page)
		__field(u8, channel)
	),
	TP_fast_assign(
		LOCAL_ASSIGN;
		__entry->page = page;
		__entry->channel = channel;
	),
	TP_prपूर्णांकk(LOCAL_PR_FMT ", page: %d, channel: %d", LOCAL_PR_ARG,
		  __entry->page, __entry->channel)
);

TRACE_EVENT(802154_drv_set_cca_mode,
	TP_PROTO(काष्ठा ieee802154_local *local,
		 स्थिर काष्ठा wpan_phy_cca *cca),
	TP_ARGS(local, cca),
	TP_STRUCT__entry(
		LOCAL_ENTRY
		CCA_ENTRY
	),
	TP_fast_assign(
		LOCAL_ASSIGN;
		CCA_ASSIGN;
	),
	TP_prपूर्णांकk(LOCAL_PR_FMT ", " CCA_PR_FMT, LOCAL_PR_ARG,
		  CCA_PR_ARG)
);

TRACE_EVENT(802154_drv_set_cca_ed_level,
	TP_PROTO(काष्ठा ieee802154_local *local, s32 mbm),
	TP_ARGS(local, mbm),
	TP_STRUCT__entry(
		LOCAL_ENTRY
		__field(s32, mbm)
	),
	TP_fast_assign(
		LOCAL_ASSIGN;
		__entry->mbm = mbm;
	),
	TP_prपूर्णांकk(LOCAL_PR_FMT ", ed level: %d", LOCAL_PR_ARG,
		  __entry->mbm)
);

TRACE_EVENT(802154_drv_set_tx_घातer,
	TP_PROTO(काष्ठा ieee802154_local *local, s32 घातer),
	TP_ARGS(local, घातer),
	TP_STRUCT__entry(
		LOCAL_ENTRY
		__field(s32, घातer)
	),
	TP_fast_assign(
		LOCAL_ASSIGN;
		__entry->घातer = घातer;
	),
	TP_prपूर्णांकk(LOCAL_PR_FMT ", mbm: %d", LOCAL_PR_ARG,
		 __entry->घातer)
);

TRACE_EVENT(802154_drv_set_lbt_mode,
	TP_PROTO(काष्ठा ieee802154_local *local, bool mode),
	TP_ARGS(local, mode),
	TP_STRUCT__entry(
		LOCAL_ENTRY
		__field(bool, mode)
	),
	TP_fast_assign(
		LOCAL_ASSIGN;
		__entry->mode = mode;
	),
	TP_prपूर्णांकk(LOCAL_PR_FMT ", lbt mode: %s", LOCAL_PR_ARG,
		  BOOL_TO_STR(__entry->mode))
);

TRACE_EVENT(802154_drv_set_लघु_addr,
	TP_PROTO(काष्ठा ieee802154_local *local, __le16 लघु_addr),
	TP_ARGS(local, लघु_addr),
	TP_STRUCT__entry(
		LOCAL_ENTRY
		__field(__le16, लघु_addr)
	),
	TP_fast_assign(
		LOCAL_ASSIGN;
		__entry->लघु_addr = लघु_addr;
	),
	TP_prपूर्णांकk(LOCAL_PR_FMT ", short addr: 0x%04x", LOCAL_PR_ARG,
		  le16_to_cpu(__entry->लघु_addr))
);

TRACE_EVENT(802154_drv_set_pan_id,
	TP_PROTO(काष्ठा ieee802154_local *local, __le16 pan_id),
	TP_ARGS(local, pan_id),
	TP_STRUCT__entry(
		LOCAL_ENTRY
		__field(__le16, pan_id)
	),
	TP_fast_assign(
		LOCAL_ASSIGN;
		__entry->pan_id = pan_id;
	),
	TP_prपूर्णांकk(LOCAL_PR_FMT ", pan id: 0x%04x", LOCAL_PR_ARG,
		  le16_to_cpu(__entry->pan_id))
);

TRACE_EVENT(802154_drv_set_extended_addr,
	TP_PROTO(काष्ठा ieee802154_local *local, __le64 extended_addr),
	TP_ARGS(local, extended_addr),
	TP_STRUCT__entry(
		LOCAL_ENTRY
		__field(__le64, extended_addr)
	),
	TP_fast_assign(
		LOCAL_ASSIGN;
		__entry->extended_addr = extended_addr;
	),
	TP_prपूर्णांकk(LOCAL_PR_FMT ", extended addr: 0x%llx", LOCAL_PR_ARG,
		  le64_to_cpu(__entry->extended_addr))
);

TRACE_EVENT(802154_drv_set_pan_coord,
	TP_PROTO(काष्ठा ieee802154_local *local, bool is_coord),
	TP_ARGS(local, is_coord),
	TP_STRUCT__entry(
		LOCAL_ENTRY
		__field(bool, is_coord)
	),
	TP_fast_assign(
		LOCAL_ASSIGN;
		__entry->is_coord = is_coord;
	),
	TP_prपूर्णांकk(LOCAL_PR_FMT ", is_coord: %s", LOCAL_PR_ARG,
		  BOOL_TO_STR(__entry->is_coord))
);

TRACE_EVENT(802154_drv_set_csma_params,
	TP_PROTO(काष्ठा ieee802154_local *local, u8 min_be, u8 max_be,
		 u8 max_csma_backoffs),
	TP_ARGS(local, min_be, max_be, max_csma_backoffs),
	TP_STRUCT__entry(
		LOCAL_ENTRY
		__field(u8, min_be)
		__field(u8, max_be)
		__field(u8, max_csma_backoffs)
	),
	TP_fast_assign(
		LOCAL_ASSIGN,
		__entry->min_be = min_be;
		__entry->max_be = max_be;
		__entry->max_csma_backoffs = max_csma_backoffs;
	),
	TP_prपूर्णांकk(LOCAL_PR_FMT ", min be: %d, max be: %d, max csma backoffs: %d",
		  LOCAL_PR_ARG, __entry->min_be, __entry->max_be,
		  __entry->max_csma_backoffs)
);

TRACE_EVENT(802154_drv_set_max_frame_retries,
	TP_PROTO(काष्ठा ieee802154_local *local, s8 max_frame_retries),
	TP_ARGS(local, max_frame_retries),
	TP_STRUCT__entry(
		LOCAL_ENTRY
		__field(s8, max_frame_retries)
	),
	TP_fast_assign(
		LOCAL_ASSIGN;
		__entry->max_frame_retries = max_frame_retries;
	),
	TP_prपूर्णांकk(LOCAL_PR_FMT ", max frame retries: %d", LOCAL_PR_ARG,
		  __entry->max_frame_retries)
);

TRACE_EVENT(802154_drv_set_promiscuous_mode,
	TP_PROTO(काष्ठा ieee802154_local *local, bool on),
	TP_ARGS(local, on),
	TP_STRUCT__entry(
		LOCAL_ENTRY
		__field(bool, on)
	),
	TP_fast_assign(
		LOCAL_ASSIGN;
		__entry->on = on;
	),
	TP_prपूर्णांकk(LOCAL_PR_FMT ", promiscuous mode: %s", LOCAL_PR_ARG,
		  BOOL_TO_STR(__entry->on))
);

#पूर्ण_अगर /* !__MAC802154_DRIVER_TRACE || TRACE_HEADER_MULTI_READ */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace
#समावेश <trace/define_trace.h>
