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
 */

#अगर_अघोषित _TA_RAS_IF_H
#घोषणा _TA_RAS_IF_H

#घोषणा RAS_TA_HOST_IF_VER	0

/* Responses have bit 31 set */
#घोषणा RSP_ID_MASK (1U << 31)
#घोषणा RSP_ID(cmdId) (((uपूर्णांक32_t)(cmdId)) | RSP_ID_MASK)

/* RAS related क्रमागतerations */
/**********************************************************/
क्रमागत ras_command अणु
	TA_RAS_COMMAND__ENABLE_FEATURES = 0,
	TA_RAS_COMMAND__DISABLE_FEATURES,
	TA_RAS_COMMAND__TRIGGER_ERROR,
पूर्ण;

क्रमागत ta_ras_status
अणु
	TA_RAS_STATUS__SUCCESS                          = 0x00,
	TA_RAS_STATUS__RESET_NEEDED                     = 0xA001,
	TA_RAS_STATUS__ERROR_INVALID_PARAMETER          = 0xA002,
	TA_RAS_STATUS__ERROR_RAS_NOT_AVAILABLE          = 0xA003,
	TA_RAS_STATUS__ERROR_RAS_DUPLICATE_CMD          = 0xA004,
	TA_RAS_STATUS__ERROR_INJECTION_FAILED           = 0xA005,
	TA_RAS_STATUS__ERROR_ASD_READ_WRITE             = 0xA006,
	TA_RAS_STATUS__ERROR_TOGGLE_DF_CSTATE           = 0xA007,
	TA_RAS_STATUS__ERROR_TIMEOUT                    = 0xA008,
	TA_RAS_STATUS__ERROR_BLOCK_DISABLED             = 0XA009,
	TA_RAS_STATUS__ERROR_GENERIC                    = 0xA00A,
	TA_RAS_STATUS__ERROR_RAS_MMHUB_INIT             = 0xA00B,
	TA_RAS_STATUS__ERROR_GET_DEV_INFO               = 0xA00C,
	TA_RAS_STATUS__ERROR_UNSUPPORTED_DEV            = 0xA00D,
	TA_RAS_STATUS__ERROR_NOT_INITIALIZED            = 0xA00E,
	TA_RAS_STATUS__ERROR_TEE_INTERNAL               = 0xA00F
पूर्ण;

क्रमागत ta_ras_block अणु
	TA_RAS_BLOCK__UMC = 0,
	TA_RAS_BLOCK__SDMA,
	TA_RAS_BLOCK__GFX,
	TA_RAS_BLOCK__MMHUB,
	TA_RAS_BLOCK__ATHUB,
	TA_RAS_BLOCK__PCIE_BIF,
	TA_RAS_BLOCK__HDP,
	TA_RAS_BLOCK__XGMI_WAFL,
	TA_RAS_BLOCK__DF,
	TA_RAS_BLOCK__SMN,
	TA_RAS_BLOCK__SEM,
	TA_RAS_BLOCK__MP0,
	TA_RAS_BLOCK__MP1,
	TA_RAS_BLOCK__FUSE,
	TA_NUM_BLOCK_MAX
पूर्ण;

क्रमागत ta_ras_error_type अणु
	TA_RAS_ERROR__NONE			= 0,
	TA_RAS_ERROR__PARITY			= 1,
	TA_RAS_ERROR__SINGLE_CORRECTABLE	= 2,
	TA_RAS_ERROR__MULTI_UNCORRECTABLE	= 4,
	TA_RAS_ERROR__POISON			= 8,
पूर्ण;

/* Input/output काष्ठाures क्रम RAS commands */
/**********************************************************/

काष्ठा ta_ras_enable_features_input अणु
	क्रमागत ta_ras_block	block_id;
	क्रमागत ta_ras_error_type	error_type;
पूर्ण;

काष्ठा ta_ras_disable_features_input अणु
	क्रमागत ta_ras_block	block_id;
	क्रमागत ta_ras_error_type	error_type;
पूर्ण;

काष्ठा ta_ras_trigger_error_input अणु
	क्रमागत ta_ras_block	block_id;		// ras-block. i.e. umc, gfx
	क्रमागत ta_ras_error_type	inject_error_type;	// type of error. i.e. single_correctable
	uपूर्णांक32_t		sub_block_index;	// mem block. i.e. hbm, sram etc.
	uपूर्णांक64_t		address;		// explicit address of error
	uपूर्णांक64_t		value;			// method अगर error injection. i.e persistent, coherent etc.
पूर्ण;

काष्ठा ta_ras_output_flags
अणु
	uपूर्णांक8_t    ras_init_success_flag;
	uपूर्णांक8_t    err_inject_चयन_disable_flag;
	uपूर्णांक8_t    reg_access_failure_flag;
पूर्ण;

/* Common input काष्ठाure क्रम RAS callbacks */
/**********************************************************/
जोड़ ta_ras_cmd_input अणु
	काष्ठा ta_ras_enable_features_input	enable_features;
	काष्ठा ta_ras_disable_features_input	disable_features;
	काष्ठा ta_ras_trigger_error_input	trigger_error;

	uपूर्णांक32_t	reserve_pad[256];
पूर्ण;

जोड़ ta_ras_cmd_output
अणु
	काष्ठा ta_ras_output_flags  flags;

	uपूर्णांक32_t	reserve_pad[256];
पूर्ण;

/* Shared Memory काष्ठाures */
/**********************************************************/
काष्ठा ta_ras_shared_memory अणु
	uपूर्णांक32_t		    cmd_id;
	uपूर्णांक32_t		    resp_id;
	uपूर्णांक32_t	    	    ras_status;
	uपूर्णांक32_t		    अगर_version;
	जोड़ ta_ras_cmd_input	    ras_in_message;
	जोड़ ta_ras_cmd_output     ras_out_message;
पूर्ण;

#पूर्ण_अगर // TL_RAS_IF_H_
