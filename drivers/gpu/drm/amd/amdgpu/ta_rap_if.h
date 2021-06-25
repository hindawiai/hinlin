<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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

#अगर_अघोषित _TA_RAP_IF_H
#घोषणा _TA_RAP_IF_H

/* Responses have bit 31 set */
#घोषणा RSP_ID_MASK (1U << 31)
#घोषणा RSP_ID(cmdId) (((uपूर्णांक32_t)(cmdId)) | RSP_ID_MASK)

क्रमागत ta_rap_status अणु
	TA_RAP_STATUS__SUCCESS                              = 1,
	TA_RAP_STATUS__ERROR_GENERIC_FAILURE                = 2,
	TA_RAP_STATUS__ERROR_CMD_NOT_SUPPORTED              = 3,
	TA_RAP_STATUS__ERROR_INVALID_VALIDATION_METHOD      = 4,
	TA_RAP_STATUS__ERROR_शून्य_POINTER                   = 5,
	TA_RAP_STATUS__ERROR_NOT_INITIALIZED                = 6,
	TA_RAP_STATUS__ERROR_VALIDATION_FAILED              = 7,
	TA_RAP_STATUS__ERROR_ASIC_NOT_SUPPORTED             = 8,
	TA_RAP_STATUS__ERROR_OPERATION_NOT_PERMISSABLE      = 9,
	TA_RAP_STATUS__ERROR_ALREADY_INIT                   = 10,
पूर्ण;

क्रमागत ta_rap_cmd अणु
	TA_CMD_RAP__INITIALIZE              = 1,
	TA_CMD_RAP__VALIDATE_L0             = 2,
पूर्ण;

क्रमागत ta_rap_validation_method अणु
	METHOD_A           = 1,
पूर्ण;

काष्ठा ta_rap_cmd_input_data अणु
	uपूर्णांक8_t reserved[8];
पूर्ण;

काष्ठा ta_rap_cmd_output_data अणु
	uपूर्णांक32_t    last_subsection;
	uपूर्णांक32_t    num_total_validate;
	uपूर्णांक32_t    num_valid;
	uपूर्णांक32_t    last_validate_addr;
	uपूर्णांक32_t    last_validate_val;
	uपूर्णांक32_t    last_validate_val_exptd;
पूर्ण;

जोड़ ta_rap_cmd_input अणु
	काष्ठा ta_rap_cmd_input_data input;
पूर्ण;

जोड़ ta_rap_cmd_output अणु
	काष्ठा ta_rap_cmd_output_data output;
पूर्ण;

काष्ठा ta_rap_shared_memory अणु
	uपूर्णांक32_t                    cmd_id;
	uपूर्णांक32_t                    validation_method_id;
	uपूर्णांक32_t                    resp_id;
	क्रमागत ta_rap_status          rap_status;
	जोड़ ta_rap_cmd_input      rap_in_message;
	जोड़ ta_rap_cmd_output     rap_out_message;
	uपूर्णांक8_t                     reserved[64];
पूर्ण;

#पूर्ण_अगर  // #घोषणा _TA_RAP_IF_H
