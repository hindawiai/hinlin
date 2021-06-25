<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM ufs

#अगर !defined(_TRACE_UFS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_UFS_H

#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा str_opcode(opcode)						\
	__prपूर्णांक_symbolic(opcode,					\
		अणु WRITE_16,		"WRITE_16" पूर्ण,			\
		अणु WRITE_10,		"WRITE_10" पूर्ण,			\
		अणु READ_16,		"READ_16" पूर्ण,			\
		अणु READ_10,		"READ_10" पूर्ण,			\
		अणु SYNCHRONIZE_CACHE,	"SYNC" पूर्ण,			\
		अणु UNMAP,		"UNMAP" पूर्ण)

#घोषणा UFS_LINK_STATES						\
	EM(UIC_LINK_OFF_STATE,		"UIC_LINK_OFF_STATE")		\
	EM(UIC_LINK_ACTIVE_STATE,	"UIC_LINK_ACTIVE_STATE")	\
	EMe(UIC_LINK_HIBERN8_STATE,	"UIC_LINK_HIBERN8_STATE")

#घोषणा UFS_PWR_MODES							\
	EM(UFS_ACTIVE_PWR_MODE,		"UFS_ACTIVE_PWR_MODE")		\
	EM(UFS_SLEEP_PWR_MODE,		"UFS_SLEEP_PWR_MODE")		\
	EM(UFS_POWERDOWN_PWR_MODE,	"UFS_POWERDOWN_PWR_MODE")	\
	EMe(UFS_DEEPSLEEP_PWR_MODE,	"UFS_DEEPSLEEP_PWR_MODE")

#घोषणा UFSCHD_CLK_GATING_STATES				\
	EM(CLKS_OFF,			"CLKS_OFF")		\
	EM(CLKS_ON,			"CLKS_ON")		\
	EM(REQ_CLKS_OFF,		"REQ_CLKS_OFF")		\
	EMe(REQ_CLKS_ON,		"REQ_CLKS_ON")

#घोषणा UFS_CMD_TRACE_STRINGS					\
	EM(UFS_CMD_SEND,	"send_req")			\
	EM(UFS_CMD_COMP,	"complete_rsp")			\
	EM(UFS_DEV_COMP,	"dev_complete")			\
	EM(UFS_QUERY_SEND,	"query_send")			\
	EM(UFS_QUERY_COMP,	"query_complete")		\
	EM(UFS_QUERY_ERR,	"query_complete_err")		\
	EM(UFS_TM_SEND,		"tm_send")			\
	EM(UFS_TM_COMP,		"tm_complete")			\
	EMe(UFS_TM_ERR,		"tm_complete_err")

#घोषणा UFS_CMD_TRACE_TSF_TYPES					\
	EM(UFS_TSF_CDB,		"CDB")		                \
	EM(UFS_TSF_OSF,		"OSF")		                \
	EM(UFS_TSF_TM_INPUT,	"TM_INPUT")                     \
	EMe(UFS_TSF_TM_OUTPUT,	"TM_OUTPUT")

/* Enums require being exported to userspace, क्रम user tool parsing */
#अघोषित EM
#अघोषित EMe
#घोषणा EM(a, b)	TRACE_DEFINE_ENUM(a);
#घोषणा EMe(a, b)	TRACE_DEFINE_ENUM(a);

UFS_LINK_STATES;
UFS_PWR_MODES;
UFSCHD_CLK_GATING_STATES;
UFS_CMD_TRACE_STRINGS
UFS_CMD_TRACE_TSF_TYPES

/*
 * Now redefine the EM() and EMe() macros to map the क्रमागतs to the strings
 * that will be prपूर्णांकed in the output.
 */
#अघोषित EM
#अघोषित EMe
#घोषणा EM(a, b)	अणुa, bपूर्ण,
#घोषणा EMe(a, b)	अणुa, bपूर्ण

#घोषणा show_ufs_cmd_trace_str(str_t)	\
				__prपूर्णांक_symbolic(str_t, UFS_CMD_TRACE_STRINGS)
#घोषणा show_ufs_cmd_trace_tsf(tsf)	\
				__prपूर्णांक_symbolic(tsf, UFS_CMD_TRACE_TSF_TYPES)

TRACE_EVENT(ufshcd_clk_gating,

	TP_PROTO(स्थिर अक्षर *dev_name, पूर्णांक state),

	TP_ARGS(dev_name, state),

	TP_STRUCT__entry(
		__string(dev_name, dev_name)
		__field(पूर्णांक, state)
	),

	TP_fast_assign(
		__assign_str(dev_name, dev_name);
		__entry->state = state;
	),

	TP_prपूर्णांकk("%s: gating state changed to %s",
		__get_str(dev_name),
		__prपूर्णांक_symbolic(__entry->state, UFSCHD_CLK_GATING_STATES))
);

TRACE_EVENT(ufshcd_clk_scaling,

	TP_PROTO(स्थिर अक्षर *dev_name, स्थिर अक्षर *state, स्थिर अक्षर *clk,
		u32 prev_state, u32 curr_state),

	TP_ARGS(dev_name, state, clk, prev_state, curr_state),

	TP_STRUCT__entry(
		__string(dev_name, dev_name)
		__string(state, state)
		__string(clk, clk)
		__field(u32, prev_state)
		__field(u32, curr_state)
	),

	TP_fast_assign(
		__assign_str(dev_name, dev_name);
		__assign_str(state, state);
		__assign_str(clk, clk);
		__entry->prev_state = prev_state;
		__entry->curr_state = curr_state;
	),

	TP_prपूर्णांकk("%s: %s %s from %u to %u Hz",
		__get_str(dev_name), __get_str(state), __get_str(clk),
		__entry->prev_state, __entry->curr_state)
);

TRACE_EVENT(ufshcd_स्वतः_bkops_state,

	TP_PROTO(स्थिर अक्षर *dev_name, स्थिर अक्षर *state),

	TP_ARGS(dev_name, state),

	TP_STRUCT__entry(
		__string(dev_name, dev_name)
		__string(state, state)
	),

	TP_fast_assign(
		__assign_str(dev_name, dev_name);
		__assign_str(state, state);
	),

	TP_prपूर्णांकk("%s: auto bkops - %s",
		__get_str(dev_name), __get_str(state))
);

DECLARE_EVENT_CLASS(ufshcd_profiling_ढाँचा,
	TP_PROTO(स्थिर अक्षर *dev_name, स्थिर अक्षर *profile_info, s64 समय_us,
		 पूर्णांक err),

	TP_ARGS(dev_name, profile_info, समय_us, err),

	TP_STRUCT__entry(
		__string(dev_name, dev_name)
		__string(profile_info, profile_info)
		__field(s64, समय_us)
		__field(पूर्णांक, err)
	),

	TP_fast_assign(
		__assign_str(dev_name, dev_name);
		__assign_str(profile_info, profile_info);
		__entry->समय_us = समय_us;
		__entry->err = err;
	),

	TP_prपूर्णांकk("%s: %s: took %lld usecs, err %d",
		__get_str(dev_name), __get_str(profile_info),
		__entry->समय_us, __entry->err)
);

DEFINE_EVENT(ufshcd_profiling_ढाँचा, ufshcd_profile_hibern8,
	TP_PROTO(स्थिर अक्षर *dev_name, स्थिर अक्षर *profile_info, s64 समय_us,
		 पूर्णांक err),
	TP_ARGS(dev_name, profile_info, समय_us, err));

DEFINE_EVENT(ufshcd_profiling_ढाँचा, ufshcd_profile_clk_gating,
	TP_PROTO(स्थिर अक्षर *dev_name, स्थिर अक्षर *profile_info, s64 समय_us,
		 पूर्णांक err),
	TP_ARGS(dev_name, profile_info, समय_us, err));

DEFINE_EVENT(ufshcd_profiling_ढाँचा, ufshcd_profile_clk_scaling,
	TP_PROTO(स्थिर अक्षर *dev_name, स्थिर अक्षर *profile_info, s64 समय_us,
		 पूर्णांक err),
	TP_ARGS(dev_name, profile_info, समय_us, err));

DECLARE_EVENT_CLASS(ufshcd_ढाँचा,
	TP_PROTO(स्थिर अक्षर *dev_name, पूर्णांक err, s64 usecs,
		 पूर्णांक dev_state, पूर्णांक link_state),

	TP_ARGS(dev_name, err, usecs, dev_state, link_state),

	TP_STRUCT__entry(
		__field(s64, usecs)
		__field(पूर्णांक, err)
		__string(dev_name, dev_name)
		__field(पूर्णांक, dev_state)
		__field(पूर्णांक, link_state)
	),

	TP_fast_assign(
		__entry->usecs = usecs;
		__entry->err = err;
		__assign_str(dev_name, dev_name);
		__entry->dev_state = dev_state;
		__entry->link_state = link_state;
	),

	TP_prपूर्णांकk(
		"%s: took %lld usecs, dev_state: %s, link_state: %s, err %d",
		__get_str(dev_name),
		__entry->usecs,
		__prपूर्णांक_symbolic(__entry->dev_state, UFS_PWR_MODES),
		__prपूर्णांक_symbolic(__entry->link_state, UFS_LINK_STATES),
		__entry->err
	)
);

DEFINE_EVENT(ufshcd_ढाँचा, ufshcd_प्रणाली_suspend,
	     TP_PROTO(स्थिर अक्षर *dev_name, पूर्णांक err, s64 usecs,
		      पूर्णांक dev_state, पूर्णांक link_state),
	     TP_ARGS(dev_name, err, usecs, dev_state, link_state));

DEFINE_EVENT(ufshcd_ढाँचा, ufshcd_प्रणाली_resume,
	     TP_PROTO(स्थिर अक्षर *dev_name, पूर्णांक err, s64 usecs,
		      पूर्णांक dev_state, पूर्णांक link_state),
	     TP_ARGS(dev_name, err, usecs, dev_state, link_state));

DEFINE_EVENT(ufshcd_ढाँचा, ufshcd_runसमय_suspend,
	     TP_PROTO(स्थिर अक्षर *dev_name, पूर्णांक err, s64 usecs,
		      पूर्णांक dev_state, पूर्णांक link_state),
	     TP_ARGS(dev_name, err, usecs, dev_state, link_state));

DEFINE_EVENT(ufshcd_ढाँचा, ufshcd_runसमय_resume,
	     TP_PROTO(स्थिर अक्षर *dev_name, पूर्णांक err, s64 usecs,
		      पूर्णांक dev_state, पूर्णांक link_state),
	     TP_ARGS(dev_name, err, usecs, dev_state, link_state));

DEFINE_EVENT(ufshcd_ढाँचा, ufshcd_init,
	     TP_PROTO(स्थिर अक्षर *dev_name, पूर्णांक err, s64 usecs,
		      पूर्णांक dev_state, पूर्णांक link_state),
	     TP_ARGS(dev_name, err, usecs, dev_state, link_state));

TRACE_EVENT(ufshcd_command,
	TP_PROTO(स्थिर अक्षर *dev_name, क्रमागत ufs_trace_str_t str_t,
		 अचिन्हित पूर्णांक tag, u32 करोorbell, पूर्णांक transfer_len, u32 पूर्णांकr,
		 u64 lba, u8 opcode, u8 group_id),

	TP_ARGS(dev_name, str_t, tag, करोorbell, transfer_len,
				पूर्णांकr, lba, opcode, group_id),

	TP_STRUCT__entry(
		__string(dev_name, dev_name)
		__field(क्रमागत ufs_trace_str_t, str_t)
		__field(अचिन्हित पूर्णांक, tag)
		__field(u32, करोorbell)
		__field(पूर्णांक, transfer_len)
		__field(u32, पूर्णांकr)
		__field(u64, lba)
		__field(u8, opcode)
		__field(u8, group_id)
	),

	TP_fast_assign(
		__assign_str(dev_name, dev_name);
		__entry->str_t = str_t;
		__entry->tag = tag;
		__entry->करोorbell = करोorbell;
		__entry->transfer_len = transfer_len;
		__entry->पूर्णांकr = पूर्णांकr;
		__entry->lba = lba;
		__entry->opcode = opcode;
		__entry->group_id = group_id;
	),

	TP_prपूर्णांकk(
		"%s: %s: tag: %u, DB: 0x%x, size: %d, IS: %u, LBA: %llu, opcode: 0x%x (%s), group_id: 0x%x",
		show_ufs_cmd_trace_str(__entry->str_t), __get_str(dev_name),
		__entry->tag, __entry->करोorbell, __entry->transfer_len,
		__entry->पूर्णांकr, __entry->lba, (u32)__entry->opcode,
		str_opcode(__entry->opcode), (u32)__entry->group_id
	)
);

TRACE_EVENT(ufshcd_uic_command,
	TP_PROTO(स्थिर अक्षर *dev_name, क्रमागत ufs_trace_str_t str_t, u32 cmd,
		 u32 arg1, u32 arg2, u32 arg3),

	TP_ARGS(dev_name, str_t, cmd, arg1, arg2, arg3),

	TP_STRUCT__entry(
		__string(dev_name, dev_name)
		__field(क्रमागत ufs_trace_str_t, str_t)
		__field(u32, cmd)
		__field(u32, arg1)
		__field(u32, arg2)
		__field(u32, arg3)
	),

	TP_fast_assign(
		__assign_str(dev_name, dev_name);
		__entry->str_t = str_t;
		__entry->cmd = cmd;
		__entry->arg1 = arg1;
		__entry->arg2 = arg2;
		__entry->arg3 = arg3;
	),

	TP_prपूर्णांकk(
		"%s: %s: cmd: 0x%x, arg1: 0x%x, arg2: 0x%x, arg3: 0x%x",
		show_ufs_cmd_trace_str(__entry->str_t), __get_str(dev_name),
		__entry->cmd, __entry->arg1, __entry->arg2, __entry->arg3
	)
);

TRACE_EVENT(ufshcd_upiu,
	TP_PROTO(स्थिर अक्षर *dev_name, क्रमागत ufs_trace_str_t str_t, व्योम *hdr,
		 व्योम *tsf, क्रमागत ufs_trace_tsf_t tsf_t),

	TP_ARGS(dev_name, str_t, hdr, tsf, tsf_t),

	TP_STRUCT__entry(
		__string(dev_name, dev_name)
		__field(क्रमागत ufs_trace_str_t, str_t)
		__array(अचिन्हित अक्षर, hdr, 12)
		__array(अचिन्हित अक्षर, tsf, 16)
		__field(क्रमागत ufs_trace_tsf_t, tsf_t)
	),

	TP_fast_assign(
		__assign_str(dev_name, dev_name);
		__entry->str_t = str_t;
		स_नकल(__entry->hdr, hdr, माप(__entry->hdr));
		स_नकल(__entry->tsf, tsf, माप(__entry->tsf));
		__entry->tsf_t = tsf_t;
	),

	TP_prपूर्णांकk(
		"%s: %s: HDR:%s, %s:%s",
		show_ufs_cmd_trace_str(__entry->str_t), __get_str(dev_name),
		__prपूर्णांक_hex(__entry->hdr, माप(__entry->hdr)),
		show_ufs_cmd_trace_tsf(__entry->tsf_t),
		__prपूर्णांक_hex(__entry->tsf, माप(__entry->tsf))
	)
);

TRACE_EVENT(ufshcd_exception_event,

	TP_PROTO(स्थिर अक्षर *dev_name, u16 status),

	TP_ARGS(dev_name, status),

	TP_STRUCT__entry(
		__string(dev_name, dev_name)
		__field(u16, status)
	),

	TP_fast_assign(
		__assign_str(dev_name, dev_name);
		__entry->status = status;
	),

	TP_prपूर्णांकk("%s: status 0x%x",
		__get_str(dev_name), __entry->status
	)
);

#पूर्ण_अगर /* अगर !defined(_TRACE_UFS_H) || defined(TRACE_HEADER_MULTI_READ) */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
