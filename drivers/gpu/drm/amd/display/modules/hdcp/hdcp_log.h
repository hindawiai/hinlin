<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित MOD_HDCP_LOG_H_
#घोषणा MOD_HDCP_LOG_H_

#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
#घोषणा HDCP_LOG_ERR(hdcp, ...) DRM_DEBUG_KMS(__VA_ARGS__)
#घोषणा HDCP_LOG_VER(hdcp, ...) DRM_DEBUG_KMS(__VA_ARGS__)
#घोषणा HDCP_LOG_FSM(hdcp, ...) DRM_DEBUG_KMS(__VA_ARGS__)
#घोषणा HDCP_LOG_TOP(hdcp, ...) pr_debug("[HDCP_TOP]:"__VA_ARGS__)
#घोषणा HDCP_LOG_DDC(hdcp, ...) pr_debug("[HDCP_DDC]:"__VA_ARGS__)
#पूर्ण_अगर

/* शेष logs */
#घोषणा HDCP_ERROR_TRACE(hdcp, status) \
		HDCP_LOG_ERR(hdcp, \
			"[Link %d] WARNING %s IN STATE %s STAY COUNT %d", \
			hdcp->config.index, \
			mod_hdcp_status_to_str(status), \
			mod_hdcp_state_id_to_str(hdcp->state.id), \
			hdcp->state.stay_count)
#घोषणा HDCP_HDCP1_ENABLED_TRACE(hdcp, displayIndex) \
		HDCP_LOG_VER(hdcp, \
			"[Link %d] HDCP 1.4 enabled on display %d", \
			hdcp->config.index, displayIndex)
#घोषणा HDCP_HDCP2_ENABLED_TRACE(hdcp, displayIndex) \
		HDCP_LOG_VER(hdcp, \
			"[Link %d] HDCP 2.2 enabled on display %d", \
			hdcp->config.index, displayIndex)
#घोषणा HDCP_HDCP1_DISABLED_TRACE(hdcp, displayIndex) \
		HDCP_LOG_VER(hdcp, \
			"[Link %d] HDCP 1.4 disabled on display %d", \
			hdcp->config.index, displayIndex)
#घोषणा HDCP_HDCP2_DISABLED_TRACE(hdcp, displayIndex) \
		HDCP_LOG_VER(hdcp, \
			"[Link %d] HDCP 2.2 disabled on display %d", \
			hdcp->config.index, displayIndex)

/* state machine logs */
#घोषणा HDCP_REMOVE_DISPLAY_TRACE(hdcp, displayIndex) \
		HDCP_LOG_FSM(hdcp, \
			"[Link %d] HDCP_REMOVE_DISPLAY index %d", \
			hdcp->config.index, displayIndex)
#घोषणा HDCP_INPUT_PASS_TRACE(hdcp, str) \
		HDCP_LOG_FSM(hdcp, \
			"[Link %d]\tPASS %s", \
			hdcp->config.index, str)
#घोषणा HDCP_INPUT_FAIL_TRACE(hdcp, str) \
		HDCP_LOG_FSM(hdcp, \
			"[Link %d]\tFAIL %s", \
			hdcp->config.index, str)
#घोषणा HDCP_NEXT_STATE_TRACE(hdcp, id, output) करो अणु \
		अगर (output->watchकरोg_समयr_needed) \
			HDCP_LOG_FSM(hdcp, \
				"[Link %d] > %s with %d ms watchdog", \
				hdcp->config.index, \
				mod_hdcp_state_id_to_str(id), output->watchकरोg_समयr_delay); \
		अन्यथा \
			HDCP_LOG_FSM(hdcp, \
				"[Link %d] > %s", hdcp->config.index, \
				mod_hdcp_state_id_to_str(id)); \
पूर्ण जबतक (0)
#घोषणा HDCP_TIMEOUT_TRACE(hdcp) \
		HDCP_LOG_FSM(hdcp, "[Link %d] --> TIMEOUT", hdcp->config.index)
#घोषणा HDCP_CPIRQ_TRACE(hdcp) \
		HDCP_LOG_FSM(hdcp, "[Link %d] --> CPIRQ", hdcp->config.index)
#घोषणा HDCP_EVENT_TRACE(hdcp, event) \
		अगर (event == MOD_HDCP_EVENT_WATCHDOG_TIMEOUT) \
			HDCP_TIMEOUT_TRACE(hdcp); \
		अन्यथा अगर (event == MOD_HDCP_EVENT_CPIRQ) \
			HDCP_CPIRQ_TRACE(hdcp)
/* TODO: find some way to tell अगर logging is off to save समय */
#घोषणा HDCP_DDC_READ_TRACE(hdcp, msg_name, msg, msg_size) करो अणु \
		mod_hdcp_dump_binary_message(msg, msg_size, hdcp->buf, \
				माप(hdcp->buf)); \
		HDCP_LOG_DDC(hdcp, "[Link %d] Read %s%s", hdcp->config.index, \
				msg_name, hdcp->buf); \
पूर्ण जबतक (0)
#घोषणा HDCP_DDC_WRITE_TRACE(hdcp, msg_name, msg, msg_size) करो अणु \
		mod_hdcp_dump_binary_message(msg, msg_size, hdcp->buf, \
				माप(hdcp->buf)); \
		HDCP_LOG_DDC(hdcp, "[Link %d] Write %s%s", \
				hdcp->config.index, msg_name,\
				hdcp->buf); \
पूर्ण जबतक (0)
#घोषणा HDCP_FULL_DDC_TRACE(hdcp) करो अणु \
	अगर (is_hdcp1(hdcp)) अणु \
		HDCP_DDC_READ_TRACE(hdcp, "BKSV", hdcp->auth.msg.hdcp1.bksv, \
				माप(hdcp->auth.msg.hdcp1.bksv)); \
		HDCP_DDC_READ_TRACE(hdcp, "BCAPS", &hdcp->auth.msg.hdcp1.bcaps, \
				माप(hdcp->auth.msg.hdcp1.bcaps)); \
		HDCP_DDC_READ_TRACE(hdcp, "BSTATUS", \
				(uपूर्णांक8_t *)&hdcp->auth.msg.hdcp1.bstatus, \
				माप(hdcp->auth.msg.hdcp1.bstatus)); \
		HDCP_DDC_WRITE_TRACE(hdcp, "AN", hdcp->auth.msg.hdcp1.an, \
				माप(hdcp->auth.msg.hdcp1.an)); \
		HDCP_DDC_WRITE_TRACE(hdcp, "AKSV", hdcp->auth.msg.hdcp1.aksv, \
				माप(hdcp->auth.msg.hdcp1.aksv)); \
		HDCP_DDC_WRITE_TRACE(hdcp, "AINFO", &hdcp->auth.msg.hdcp1.ainfo, \
				माप(hdcp->auth.msg.hdcp1.ainfo)); \
		HDCP_DDC_READ_TRACE(hdcp, "RI' / R0'", \
				(uपूर्णांक8_t *)&hdcp->auth.msg.hdcp1.r0p, \
				माप(hdcp->auth.msg.hdcp1.r0p)); \
		HDCP_DDC_READ_TRACE(hdcp, "BINFO", \
				(uपूर्णांक8_t *)&hdcp->auth.msg.hdcp1.binfo_dp, \
				माप(hdcp->auth.msg.hdcp1.binfo_dp)); \
		HDCP_DDC_READ_TRACE(hdcp, "KSVLIST", hdcp->auth.msg.hdcp1.ksvlist, \
				hdcp->auth.msg.hdcp1.ksvlist_size); \
		HDCP_DDC_READ_TRACE(hdcp, "V'", hdcp->auth.msg.hdcp1.vp, \
				माप(hdcp->auth.msg.hdcp1.vp)); \
	पूर्ण अन्यथा अणु \
		HDCP_DDC_READ_TRACE(hdcp, "HDCP2Version", \
				&hdcp->auth.msg.hdcp2.hdcp2version_hdmi, \
				माप(hdcp->auth.msg.hdcp2.hdcp2version_hdmi)); \
		HDCP_DDC_READ_TRACE(hdcp, "Rx Caps", hdcp->auth.msg.hdcp2.rxcaps_dp, \
				माप(hdcp->auth.msg.hdcp2.rxcaps_dp)); \
		HDCP_DDC_WRITE_TRACE(hdcp, "AKE Init", hdcp->auth.msg.hdcp2.ake_init, \
				माप(hdcp->auth.msg.hdcp2.ake_init)); \
		HDCP_DDC_READ_TRACE(hdcp, "AKE Cert", hdcp->auth.msg.hdcp2.ake_cert, \
				माप(hdcp->auth.msg.hdcp2.ake_cert)); \
		HDCP_DDC_WRITE_TRACE(hdcp, "Stored KM", \
				hdcp->auth.msg.hdcp2.ake_stored_km, \
				माप(hdcp->auth.msg.hdcp2.ake_stored_km)); \
		HDCP_DDC_WRITE_TRACE(hdcp, "No Stored KM", \
				hdcp->auth.msg.hdcp2.ake_no_stored_km, \
				माप(hdcp->auth.msg.hdcp2.ake_no_stored_km)); \
		HDCP_DDC_READ_TRACE(hdcp, "H'", hdcp->auth.msg.hdcp2.ake_h_prime, \
				माप(hdcp->auth.msg.hdcp2.ake_h_prime)); \
		HDCP_DDC_READ_TRACE(hdcp, "Pairing Info", \
				hdcp->auth.msg.hdcp2.ake_pairing_info, \
				माप(hdcp->auth.msg.hdcp2.ake_pairing_info)); \
		HDCP_DDC_WRITE_TRACE(hdcp, "LC Init", hdcp->auth.msg.hdcp2.lc_init, \
				माप(hdcp->auth.msg.hdcp2.lc_init)); \
		HDCP_DDC_READ_TRACE(hdcp, "L'", hdcp->auth.msg.hdcp2.lc_l_prime, \
				माप(hdcp->auth.msg.hdcp2.lc_l_prime)); \
		HDCP_DDC_WRITE_TRACE(hdcp, "Exchange KS", hdcp->auth.msg.hdcp2.ske_eks, \
				माप(hdcp->auth.msg.hdcp2.ske_eks)); \
		HDCP_DDC_READ_TRACE(hdcp, "Rx Status", \
				(uपूर्णांक8_t *)&hdcp->auth.msg.hdcp2.rxstatus, \
				माप(hdcp->auth.msg.hdcp2.rxstatus)); \
		HDCP_DDC_READ_TRACE(hdcp, "Rx Id List", \
				hdcp->auth.msg.hdcp2.rx_id_list, \
				hdcp->auth.msg.hdcp2.rx_id_list_size); \
		HDCP_DDC_WRITE_TRACE(hdcp, "Rx Id List Ack", \
				hdcp->auth.msg.hdcp2.repeater_auth_ack, \
				माप(hdcp->auth.msg.hdcp2.repeater_auth_ack)); \
		HDCP_DDC_WRITE_TRACE(hdcp, "Content Stream Management", \
				hdcp->auth.msg.hdcp2.repeater_auth_stream_manage, \
				hdcp->auth.msg.hdcp2.stream_manage_size); \
		HDCP_DDC_READ_TRACE(hdcp, "Stream Ready", \
				hdcp->auth.msg.hdcp2.repeater_auth_stream_पढ़ोy, \
				माप(hdcp->auth.msg.hdcp2.repeater_auth_stream_पढ़ोy)); \
		HDCP_DDC_WRITE_TRACE(hdcp, "Content Stream Type", \
				hdcp->auth.msg.hdcp2.content_stream_type_dp, \
				माप(hdcp->auth.msg.hdcp2.content_stream_type_dp)); \
	पूर्ण \
पूर्ण जबतक (0)
#घोषणा HDCP_TOP_ADD_DISPLAY_TRACE(hdcp, i) \
		HDCP_LOG_TOP(hdcp, "[Link %d]\tadd display %d", \
				hdcp->config.index, i)
#घोषणा HDCP_TOP_REMOVE_DISPLAY_TRACE(hdcp, i) \
		HDCP_LOG_TOP(hdcp, "[Link %d]\tremove display %d", \
				hdcp->config.index, i)
#घोषणा HDCP_TOP_HDCP1_DESTROY_SESSION_TRACE(hdcp) \
		HDCP_LOG_TOP(hdcp, "[Link %d]\tdestroy hdcp1 session", \
				hdcp->config.index)
#घोषणा HDCP_TOP_HDCP2_DESTROY_SESSION_TRACE(hdcp) \
		HDCP_LOG_TOP(hdcp, "[Link %d]\tdestroy hdcp2 session", \
				hdcp->config.index)
#घोषणा HDCP_TOP_RESET_AUTH_TRACE(hdcp) \
		HDCP_LOG_TOP(hdcp, "[Link %d]\treset authentication", hdcp->config.index)
#घोषणा HDCP_TOP_RESET_CONN_TRACE(hdcp) \
		HDCP_LOG_TOP(hdcp, "[Link %d]\treset connection", hdcp->config.index)
#घोषणा HDCP_TOP_INTERFACE_TRACE(hdcp) करो अणु \
		HDCP_LOG_TOP(hdcp, "\n"); \
		HDCP_LOG_TOP(hdcp, "[Link %d] %s", hdcp->config.index, __func__); \
पूर्ण जबतक (0)
#घोषणा HDCP_TOP_INTERFACE_TRACE_WITH_INDEX(hdcp, i) करो अणु \
		HDCP_LOG_TOP(hdcp, "\n"); \
		HDCP_LOG_TOP(hdcp, "[Link %d] %s display %d", hdcp->config.index, __func__, i); \
पूर्ण जबतक (0)

#पूर्ण_अगर // MOD_HDCP_LOG_H_
