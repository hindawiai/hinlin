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

#अगर_अघोषित MOD_HDCP_H_
#घोषणा MOD_HDCP_H_

#समावेश "os_types.h"
#समावेश "signal_types.h"

/* Forward Declarations */
काष्ठा mod_hdcp;

#घोषणा MAX_NUM_OF_DISPLAYS 6
#घोषणा MAX_NUM_OF_ATTEMPTS 4
#घोषणा MAX_NUM_OF_ERROR_TRACE 10

/* detailed वापस status */
क्रमागत mod_hdcp_status अणु
	MOD_HDCP_STATUS_SUCCESS = 0,
	MOD_HDCP_STATUS_FAILURE,
	MOD_HDCP_STATUS_RESET_NEEDED,
	MOD_HDCP_STATUS_DISPLAY_OUT_OF_BOUND,
	MOD_HDCP_STATUS_DISPLAY_NOT_FOUND,
	MOD_HDCP_STATUS_INVALID_STATE,
	MOD_HDCP_STATUS_NOT_IMPLEMENTED,
	MOD_HDCP_STATUS_INTERNAL_POLICY_FAILURE,
	MOD_HDCP_STATUS_UPDATE_TOPOLOGY_FAILURE,
	MOD_HDCP_STATUS_CREATE_PSP_SERVICE_FAILURE,
	MOD_HDCP_STATUS_DESTROY_PSP_SERVICE_FAILURE,
	MOD_HDCP_STATUS_HDCP1_CREATE_SESSION_FAILURE,
	MOD_HDCP_STATUS_HDCP1_DESTROY_SESSION_FAILURE,
	MOD_HDCP_STATUS_HDCP1_VALIDATE_ENCRYPTION_FAILURE,
	MOD_HDCP_STATUS_HDCP1_NOT_HDCP_REPEATER,
	MOD_HDCP_STATUS_HDCP1_NOT_CAPABLE,
	MOD_HDCP_STATUS_HDCP1_R0_PRIME_PENDING,
	MOD_HDCP_STATUS_HDCP1_VALIDATE_RX_FAILURE,
	MOD_HDCP_STATUS_HDCP1_BKSV_REVOKED,
	MOD_HDCP_STATUS_HDCP1_KSV_LIST_NOT_READY,
	MOD_HDCP_STATUS_HDCP1_VALIDATE_KSV_LIST_FAILURE,
	MOD_HDCP_STATUS_HDCP1_KSV_LIST_REVOKED,
	MOD_HDCP_STATUS_HDCP1_ENABLE_ENCRYPTION_FAILURE,
	MOD_HDCP_STATUS_HDCP1_ENABLE_STREAM_ENCRYPTION_FAILURE,
	MOD_HDCP_STATUS_HDCP1_MAX_CASCADE_EXCEEDED_FAILURE,
	MOD_HDCP_STATUS_HDCP1_MAX_DEVS_EXCEEDED_FAILURE,
	MOD_HDCP_STATUS_HDCP1_DEVICE_COUNT_MISMATCH_FAILURE,
	MOD_HDCP_STATUS_HDCP1_LINK_INTEGRITY_FAILURE,
	MOD_HDCP_STATUS_HDCP1_REAUTH_REQUEST_ISSUED,
	MOD_HDCP_STATUS_HDCP1_LINK_MAINTEन_अंकCE_FAILURE,
	MOD_HDCP_STATUS_HDCP1_INVALID_BKSV,
	MOD_HDCP_STATUS_DDC_FAILURE, /* TODO: specअगरic errors */
	MOD_HDCP_STATUS_INVALID_OPERATION,
	MOD_HDCP_STATUS_HDCP2_NOT_CAPABLE,
	MOD_HDCP_STATUS_HDCP2_CREATE_SESSION_FAILURE,
	MOD_HDCP_STATUS_HDCP2_DESTROY_SESSION_FAILURE,
	MOD_HDCP_STATUS_HDCP2_PREP_AKE_INIT_FAILURE,
	MOD_HDCP_STATUS_HDCP2_AKE_CERT_PENDING,
	MOD_HDCP_STATUS_HDCP2_H_PRIME_PENDING,
	MOD_HDCP_STATUS_HDCP2_PAIRING_INFO_PENDING,
	MOD_HDCP_STATUS_HDCP2_VALIDATE_AKE_CERT_FAILURE,
	MOD_HDCP_STATUS_HDCP2_AKE_CERT_REVOKED,
	MOD_HDCP_STATUS_HDCP2_VALIDATE_H_PRIME_FAILURE,
	MOD_HDCP_STATUS_HDCP2_VALIDATE_PAIRING_INFO_FAILURE,
	MOD_HDCP_STATUS_HDCP2_PREP_LC_INIT_FAILURE,
	MOD_HDCP_STATUS_HDCP2_L_PRIME_PENDING,
	MOD_HDCP_STATUS_HDCP2_VALIDATE_L_PRIME_FAILURE,
	MOD_HDCP_STATUS_HDCP2_PREP_EKS_FAILURE,
	MOD_HDCP_STATUS_HDCP2_ENABLE_ENCRYPTION_FAILURE,
	MOD_HDCP_STATUS_HDCP2_RX_ID_LIST_NOT_READY,
	MOD_HDCP_STATUS_HDCP2_VALIDATE_RX_ID_LIST_FAILURE,
	MOD_HDCP_STATUS_HDCP2_RX_ID_LIST_REVOKED,
	MOD_HDCP_STATUS_HDCP2_ENABLE_STREAM_ENCRYPTION_FAILURE,
	MOD_HDCP_STATUS_HDCP2_STREAM_READY_PENDING,
	MOD_HDCP_STATUS_HDCP2_VALIDATE_STREAM_READY_FAILURE,
	MOD_HDCP_STATUS_HDCP2_PREPARE_STREAM_MANAGEMENT_FAILURE,
	MOD_HDCP_STATUS_HDCP2_REAUTH_REQUEST,
	MOD_HDCP_STATUS_HDCP2_REAUTH_LINK_INTEGRITY_FAILURE,
	MOD_HDCP_STATUS_HDCP2_DEVICE_COUNT_MISMATCH_FAILURE,
पूर्ण;

काष्ठा mod_hdcp_displayport अणु
	uपूर्णांक8_t rev;
	uपूर्णांक8_t assr_enabled;
	uपूर्णांक8_t mst_enabled;
पूर्ण;

काष्ठा mod_hdcp_hdmi अणु
	uपूर्णांक8_t reserved;
पूर्ण;
क्रमागत mod_hdcp_operation_mode अणु
	MOD_HDCP_MODE_OFF,
	MOD_HDCP_MODE_DEFAULT,
	MOD_HDCP_MODE_DP
पूर्ण;

क्रमागत mod_hdcp_display_state अणु
	MOD_HDCP_DISPLAY_INACTIVE = 0,
	MOD_HDCP_DISPLAY_ACTIVE,
	MOD_HDCP_DISPLAY_ENCRYPTION_ENABLED
पूर्ण;

क्रमागत mod_hdcp_display_disable_option अणु
	MOD_HDCP_DISPLAY_NOT_DISABLE = 0,
	MOD_HDCP_DISPLAY_DISABLE_AUTHENTICATION,
	MOD_HDCP_DISPLAY_DISABLE_ENCRYPTION,
पूर्ण;

काष्ठा mod_hdcp_ddc अणु
	व्योम *handle;
	काष्ठा अणु
		bool (*पढ़ो_i2c)(व्योम *handle,
				uपूर्णांक32_t address,
				uपूर्णांक8_t offset,
				uपूर्णांक8_t *data,
				uपूर्णांक32_t size);
		bool (*ग_लिखो_i2c)(व्योम *handle,
				uपूर्णांक32_t address,
				स्थिर uपूर्णांक8_t *data,
				uपूर्णांक32_t size);
		bool (*पढ़ो_dpcd)(व्योम *handle,
				uपूर्णांक32_t address,
				uपूर्णांक8_t *data,
				uपूर्णांक32_t size);
		bool (*ग_लिखो_dpcd)(व्योम *handle,
				uपूर्णांक32_t address,
				स्थिर uपूर्णांक8_t *data,
				uपूर्णांक32_t size);
	पूर्ण funcs;
पूर्ण;

काष्ठा mod_hdcp_psp अणु
	व्योम *handle;
	व्योम *funcs;
पूर्ण;

काष्ठा mod_hdcp_display_adjusपंचांगent अणु
	uपूर्णांक8_t disable			: 2;
	uपूर्णांक8_t reserved		: 6;
पूर्ण;

काष्ठा mod_hdcp_link_adjusपंचांगent_hdcp1 अणु
	uपूर्णांक8_t disable			: 1;
	uपूर्णांक8_t postpone_encryption	: 1;
	uपूर्णांक8_t min_auth_retries_wa : 1;
	uपूर्णांक8_t reserved		: 5;
पूर्ण;

क्रमागत mod_hdcp_क्रमce_hdcp_type अणु
	MOD_HDCP_FORCE_TYPE_MAX = 0,
	MOD_HDCP_FORCE_TYPE_0,
	MOD_HDCP_FORCE_TYPE_1
पूर्ण;

काष्ठा mod_hdcp_link_adjusपंचांगent_hdcp2 अणु
	uपूर्णांक8_t disable			: 1;
	uपूर्णांक8_t क्रमce_type		: 2;
	uपूर्णांक8_t क्रमce_no_stored_km	: 1;
	uपूर्णांक8_t increase_h_prime_समयout: 1;
	uपूर्णांक8_t reserved		: 3;
पूर्ण;

काष्ठा mod_hdcp_link_adjusपंचांगent अणु
	uपूर्णांक8_t auth_delay;
	काष्ठा mod_hdcp_link_adjusपंचांगent_hdcp1 hdcp1;
	काष्ठा mod_hdcp_link_adjusपंचांगent_hdcp2 hdcp2;
पूर्ण;

काष्ठा mod_hdcp_error अणु
	क्रमागत mod_hdcp_status status;
	uपूर्णांक8_t state_id;
पूर्ण;

काष्ठा mod_hdcp_trace अणु
	काष्ठा mod_hdcp_error errors[MAX_NUM_OF_ERROR_TRACE];
	uपूर्णांक8_t error_count;
पूर्ण;

क्रमागत mod_hdcp_encryption_status अणु
	MOD_HDCP_ENCRYPTION_STATUS_HDCP_OFF = 0,
	MOD_HDCP_ENCRYPTION_STATUS_HDCP1_ON,
	MOD_HDCP_ENCRYPTION_STATUS_HDCP2_TYPE0_ON,
	MOD_HDCP_ENCRYPTION_STATUS_HDCP2_TYPE1_ON,
	MOD_HDCP_ENCRYPTION_STATUS_HDCP2_ON
पूर्ण;

/* per link events dm has to notअगरy to hdcp module */
क्रमागत mod_hdcp_event अणु
	MOD_HDCP_EVENT_CALLBACK = 0,
	MOD_HDCP_EVENT_WATCHDOG_TIMEOUT,
	MOD_HDCP_EVENT_CPIRQ
पूर्ण;

/* output flags from module requesting समयr operations */
काष्ठा mod_hdcp_output अणु
	uपूर्णांक8_t callback_needed;
	uपूर्णांक8_t callback_stop;
	uपूर्णांक8_t watchकरोg_समयr_needed;
	uपूर्णांक8_t watchकरोg_समयr_stop;
	uपूर्णांक16_t callback_delay;
	uपूर्णांक16_t watchकरोg_समयr_delay;
पूर्ण;

/* used to represent per display info */
काष्ठा mod_hdcp_display अणु
	क्रमागत mod_hdcp_display_state state;
	uपूर्णांक8_t index;
	uपूर्णांक8_t controller;
	uपूर्णांक8_t dig_fe;
	जोड़ अणु
		uपूर्णांक8_t vc_id;
	पूर्ण;
	काष्ठा mod_hdcp_display_adjusपंचांगent adjust;
पूर्ण;

/* used to represent per link info */
/* in हाल a link has multiple displays, they share the same link info */
काष्ठा mod_hdcp_link अणु
	क्रमागत mod_hdcp_operation_mode mode;
	uपूर्णांक8_t dig_be;
	uपूर्णांक8_t ddc_line;
	जोड़ अणु
		काष्ठा mod_hdcp_displayport dp;
		काष्ठा mod_hdcp_hdmi hdmi;
	पूर्ण;
	काष्ठा mod_hdcp_link_adjusपंचांगent adjust;
पूर्ण;

/* a query काष्ठाure क्रम a display's hdcp inक्रमmation */
काष्ठा mod_hdcp_display_query अणु
	स्थिर काष्ठा mod_hdcp_display *display;
	स्थिर काष्ठा mod_hdcp_link *link;
	स्थिर काष्ठा mod_hdcp_trace *trace;
	क्रमागत mod_hdcp_encryption_status encryption_status;
पूर्ण;

/* contains values per on बाह्यal display configuration change */
काष्ठा mod_hdcp_config अणु
	काष्ठा mod_hdcp_psp psp;
	काष्ठा mod_hdcp_ddc ddc;
	uपूर्णांक8_t index;
पूर्ण;

/* dm allocates memory of mod_hdcp per dc_link on dm init based on memory size*/
माप_प्रकार mod_hdcp_get_memory_size(व्योम);

/* called per link on link creation */
क्रमागत mod_hdcp_status mod_hdcp_setup(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_config *config);

/* called per link on link destroy */
क्रमागत mod_hdcp_status mod_hdcp_tearकरोwn(काष्ठा mod_hdcp *hdcp);

/* called per display on cp_desired set to true */
क्रमागत mod_hdcp_status mod_hdcp_add_display(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_link *link, काष्ठा mod_hdcp_display *display,
		काष्ठा mod_hdcp_output *output);

/* called per display on cp_desired set to false */
क्रमागत mod_hdcp_status mod_hdcp_हटाओ_display(काष्ठा mod_hdcp *hdcp,
		uपूर्णांक8_t index, काष्ठा mod_hdcp_output *output);

/* called to query hdcp inक्रमmation on a specअगरic index */
क्रमागत mod_hdcp_status mod_hdcp_query_display(काष्ठा mod_hdcp *hdcp,
		uपूर्णांक8_t index, काष्ठा mod_hdcp_display_query *query);

/* called per link on connectivity change */
क्रमागत mod_hdcp_status mod_hdcp_reset_connection(काष्ठा mod_hdcp *hdcp,
		काष्ठा mod_hdcp_output *output);

/* called per link on events (i.e. callback, watchकरोg, CP_IRQ) */
क्रमागत mod_hdcp_status mod_hdcp_process_event(काष्ठा mod_hdcp *hdcp,
		क्रमागत mod_hdcp_event event, काष्ठा mod_hdcp_output *output);

/* called to convert क्रमागत mod_hdcp_status to c string */
अक्षर *mod_hdcp_status_to_str(पूर्णांक32_t status);

/* called to convert state id to c string */
अक्षर *mod_hdcp_state_id_to_str(पूर्णांक32_t id);

/* called to convert संकेत type to operation mode */
क्रमागत mod_hdcp_operation_mode mod_hdcp_संकेत_type_to_operation_mode(
		क्रमागत संकेत_type संकेत);
#पूर्ण_अगर /* MOD_HDCP_H_ */
