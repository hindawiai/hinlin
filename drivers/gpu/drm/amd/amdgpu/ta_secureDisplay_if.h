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

#अगर_अघोषित _TA_SECUREDISPLAY_IF_H
#घोषणा _TA_SECUREDISPLAY_IF_H

/** Secure Display related क्रमागतerations */
/**********************************************************/

/** @क्रमागत ta_securedisplay_command
 *    Secure Display Command ID
 */
क्रमागत ta_securedisplay_command अणु
	/* Query whether TA is responding used only क्रम validation purpose */
	TA_SECUREDISPLAY_COMMAND__QUERY_TA              = 1,
	/* Send region of Interest and CRC value to I2C */
	TA_SECUREDISPLAY_COMMAND__SEND_ROI_CRC          = 2,
	/* Maximum Command ID */
	TA_SECUREDISPLAY_COMMAND__MAX_ID                = 0x7FFFFFFF,
पूर्ण;

/** @क्रमागत ta_securedisplay_status
 *    Secure Display status वापसs in shared buffer status
 */
क्रमागत ta_securedisplay_status अणु
	TA_SECUREDISPLAY_STATUS__SUCCESS                 = 0x00,         /* Success */
	TA_SECUREDISPLAY_STATUS__GENERIC_FAILURE         = 0x01,         /* Generic Failure */
	TA_SECUREDISPLAY_STATUS__INVALID_PARAMETER       = 0x02,         /* Invalid Parameter */
	TA_SECUREDISPLAY_STATUS__शून्य_POINTER            = 0x03,         /* Null Poपूर्णांकer*/
	TA_SECUREDISPLAY_STATUS__I2C_WRITE_ERROR         = 0x04,         /* Fail to Write to I2C */
	TA_SECUREDISPLAY_STATUS__READ_DIO_SCRATCH_ERROR  = 0x05, /*Fail Read DIO Scratch Register*/
	TA_SECUREDISPLAY_STATUS__READ_CRC_ERROR          = 0x06,         /* Fail to Read CRC*/
	TA_SECUREDISPLAY_STATUS__I2C_INIT_ERROR          = 0x07,     /* Failed to initialize I2C */

	TA_SECUREDISPLAY_STATUS__MAX                     = 0x7FFFFFFF,/* Maximum Value क्रम status*/
पूर्ण;

/** @क्रमागत ta_securedisplay_max_phy
 *    Physical ID number to use क्रम पढ़ोing corresponding DIO Scratch रेजिस्टर क्रम ROI
 */
क्रमागत  ta_securedisplay_max_phy अणु
	TA_SECUREDISPLAY_PHY0                           = 0,
	TA_SECUREDISPLAY_PHY1                           = 1,
	TA_SECUREDISPLAY_PHY2                           = 2,
	TA_SECUREDISPLAY_PHY3                           = 3,
	TA_SECUREDISPLAY_MAX_PHY                        = 4,
पूर्ण;

/** @क्रमागत ta_securedisplay_ta_query_cmd_ret
 *    A predefined specअगरic reteurn value which is 0xAB only used to validate
 *    communication to Secure Display TA is functional.
 *    This value is used to validate whether TA is responding successfully
 */
क्रमागत ta_securedisplay_ta_query_cmd_ret अणु
	/* This is a value to validate अगर TA is loaded successfully */
	TA_SECUREDISPLAY_QUERY_CMD_RET                 = 0xAB,
पूर्ण;

/** @क्रमागत ta_securedisplay_buffer_size
 *    I2C Buffer size which contains 8 bytes of ROI  (X start, X end, Y start, Y end)
 *    and 6 bytes of CRC( R,G,B) and 1  byte क्रम physical ID
 */
क्रमागत ta_securedisplay_buffer_size अणु
	/* 15 bytes = 8 byte (ROI) + 6 byte(CRC) + 1 byte(phy_id) */
	TA_SECUREDISPLAY_I2C_BUFFER_SIZE                = 15,
पूर्ण;

/** Input/output काष्ठाures क्रम Secure Display commands */
/**********************************************************/
/**
 * Input काष्ठाures
 */

/** @काष्ठा ta_securedisplay_send_roi_crc_input
 *    Physical ID to determine which DIO scratch रेजिस्टर should be used to get ROI
 */
काष्ठा ta_securedisplay_send_roi_crc_input अणु
	uपूर्णांक32_t  phy_id;  /* Physical ID */
पूर्ण;

/** @जोड़ ta_securedisplay_cmd_input
 *    Input buffer
 */
जोड़ ta_securedisplay_cmd_input अणु
	/* send ROI and CRC input buffer क्रमmat */
	काष्ठा ta_securedisplay_send_roi_crc_input        send_roi_crc;
	uपूर्णांक32_t                                          reserved[4];
पूर्ण;

/**
 * Output काष्ठाures
 */

/** @काष्ठा ta_securedisplay_query_ta_output
 *  Output buffer क्रमmat क्रम query TA whether TA is responding used only क्रम validation purpose
 */
काष्ठा ta_securedisplay_query_ta_output अणु
	/* वापस value from TA when it is queried क्रम validation purpose only */
	uपूर्णांक32_t  query_cmd_ret;
पूर्ण;

/** @काष्ठा ta_securedisplay_send_roi_crc_output
 *  Output buffer क्रमmat क्रम send ROI CRC command which will pass I2c buffer created inside TA
 *  and used to ग_लिखो to I2C used only क्रम validation purpose
 */
काष्ठा ta_securedisplay_send_roi_crc_output अणु
	uपूर्णांक8_t  i2c_buf[TA_SECUREDISPLAY_I2C_BUFFER_SIZE];  /* I2C buffer */
	uपूर्णांक8_t  reserved;
पूर्ण;

/** @जोड़ ta_securedisplay_cmd_output
 *    Output buffer
 */
जोड़ ta_securedisplay_cmd_output अणु
	/* Query TA output buffer क्रमmat used only क्रम validation purpose*/
	काष्ठा ta_securedisplay_query_ta_output            query_ta;
	/* Send ROI CRC output buffer क्रमmat used only क्रम validation purpose */
	काष्ठा ta_securedisplay_send_roi_crc_output        send_roi_crc;
	uपूर्णांक32_t                                           reserved[4];
पूर्ण;

/** @काष्ठा securedisplay_cmd
 *    Secure Display Command which is shared buffer memory
 */
काष्ठा securedisplay_cmd अणु
	uपूर्णांक32_t                             cmd_id;                    /* +0  Bytes Command ID */
	क्रमागत ta_securedisplay_status         status;     /* +4  Bytes Status of Secure Display TA */
	uपूर्णांक32_t                             reserved[2];               /* +8  Bytes Reserved */
	जोड़ ta_securedisplay_cmd_input     securedisplay_in_message;  /* +16 Bytes Input Buffer */
	जोड़ ta_securedisplay_cmd_output    securedisplay_out_message;/* +32 Bytes Output Buffer */
	/**@note Total 48 Bytes */
पूर्ण;

#पूर्ण_अगर   //_TA_SECUREDISPLAY_IF_H

