<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St - Fअगरth Floor, Boston, MA 02110-1301 USA.
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * BSD LICENSE
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the करोcumentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _SCU_COMPLETION_CODES_HEADER_
#घोषणा _SCU_COMPLETION_CODES_HEADER_

/**
 * This file contains the स्थिरants and macros क्रम the SCU hardware completion
 *    codes.
 *
 *
 */

#घोषणा SCU_COMPLETION_TYPE_SHIFT      28
#घोषणा SCU_COMPLETION_TYPE_MASK       0x70000000

/**
 * SCU_COMPLETION_TYPE() -
 *
 * This macro स्थिरructs an SCU completion type
 */
#घोषणा SCU_COMPLETION_TYPE(type) \
	((u32)(type) << SCU_COMPLETION_TYPE_SHIFT)

/**
 * SCU_COMPLETION_TYPE() -
 *
 * These macros contain the SCU completion types SCU_COMPLETION_TYPE
 */
#घोषणा SCU_COMPLETION_TYPE_TASK       SCU_COMPLETION_TYPE(0)
#घोषणा SCU_COMPLETION_TYPE_SDMA       SCU_COMPLETION_TYPE(1)
#घोषणा SCU_COMPLETION_TYPE_UFI        SCU_COMPLETION_TYPE(2)
#घोषणा SCU_COMPLETION_TYPE_EVENT      SCU_COMPLETION_TYPE(3)
#घोषणा SCU_COMPLETION_TYPE_NOTIFY     SCU_COMPLETION_TYPE(4)

/**
 *
 *
 * These स्थिरants provide the shअगरt and mask values क्रम the various parts of
 * an SCU completion code.
 */
#घोषणा SCU_COMPLETION_STATUS_MASK       0x0FFC0000
#घोषणा SCU_COMPLETION_TL_STATUS_MASK    0x0FC00000
#घोषणा SCU_COMPLETION_TL_STATUS_SHIFT   22
#घोषणा SCU_COMPLETION_SDMA_STATUS_MASK  0x003C0000
#घोषणा SCU_COMPLETION_PEG_MASK          0x00010000
#घोषणा SCU_COMPLETION_PORT_MASK         0x00007000
#घोषणा SCU_COMPLETION_PE_MASK           SCU_COMPLETION_PORT_MASK
#घोषणा SCU_COMPLETION_PE_SHIFT          12
#घोषणा SCU_COMPLETION_INDEX_MASK        0x00000FFF

/**
 * SCU_GET_COMPLETION_TYPE() -
 *
 * This macro वापसs the SCU completion type.
 */
#घोषणा SCU_GET_COMPLETION_TYPE(completion_code) \
	((completion_code) & SCU_COMPLETION_TYPE_MASK)

/**
 * SCU_GET_COMPLETION_STATUS() -
 *
 * This macro वापसs the SCU completion status.
 */
#घोषणा SCU_GET_COMPLETION_STATUS(completion_code) \
	((completion_code) & SCU_COMPLETION_STATUS_MASK)

/**
 * SCU_GET_COMPLETION_TL_STATUS() -
 *
 * This macro वापसs the transport layer completion status.
 */
#घोषणा SCU_GET_COMPLETION_TL_STATUS(completion_code) \
	((completion_code) & SCU_COMPLETION_TL_STATUS_MASK)

/**
 * SCU_MAKE_COMPLETION_STATUS() -
 *
 * This macro takes a completion code and perक्रमms the shअगरt and mask
 * operations to turn it पूर्णांकo a completion code that can be compared to a
 * SCU_GET_COMPLETION_TL_STATUS.
 */
#घोषणा SCU_MAKE_COMPLETION_STATUS(completion_code) \
	((u32)(completion_code) << SCU_COMPLETION_TL_STATUS_SHIFT)

/**
 * SCU_NORMALIZE_COMPLETION_STATUS() -
 *
 * This macro takes a SCU_GET_COMPLETION_TL_STATUS and normalizes it क्रम a
 * वापस code.
 */
#घोषणा SCU_NORMALIZE_COMPLETION_STATUS(completion_code) \
	(\
		((completion_code) & SCU_COMPLETION_TL_STATUS_MASK) \
		>> SCU_COMPLETION_TL_STATUS_SHIFT \
	)

/**
 * SCU_GET_COMPLETION_SDMA_STATUS() -
 *
 * This macro वापसs the SDMA completion status.
 */
#घोषणा SCU_GET_COMPLETION_SDMA_STATUS(completion_code)	\
	((completion_code) & SCU_COMPLETION_SDMA_STATUS_MASK)

/**
 * SCU_GET_COMPLETION_PEG() -
 *
 * This macro वापसs the Protocol Engine Group from the completion code.
 */
#घोषणा SCU_GET_COMPLETION_PEG(completion_code)	\
	((completion_code) & SCU_COMPLETION_PEG_MASK)

/**
 * SCU_GET_COMPLETION_PORT() -
 *
 * This macro reuturns the logical port index from the completion code.
 */
#घोषणा SCU_GET_COMPLETION_PORT(completion_code) \
	((completion_code) & SCU_COMPLETION_PORT_MASK)

/**
 * SCU_GET_PROTOCOL_ENGINE_INDEX() -
 *
 * This macro वापसs the PE index from the completion code.
 */
#घोषणा SCU_GET_PROTOCOL_ENGINE_INDEX(completion_code) \
	(((completion_code) & SCU_COMPLETION_PE_MASK) >> SCU_COMPLETION_PE_SHIFT)

/**
 * SCU_GET_COMPLETION_INDEX() -
 *
 * This macro वापसs the index of the completion which is either a TCi or an
 * RNi depending on the completion type.
 */
#घोषणा SCU_GET_COMPLETION_INDEX(completion_code) \
	((completion_code) & SCU_COMPLETION_INDEX_MASK)

#घोषणा SCU_UNSOLICITED_FRAME_MASK     0x0FFF0000
#घोषणा SCU_UNSOLICITED_FRAME_SHIFT    16

/**
 * SCU_GET_FRAME_INDEX() -
 *
 * This macro वापसs a normalized frame index from an unsolicited frame
 * completion.
 */
#घोषणा SCU_GET_FRAME_INDEX(completion_code) \
	(\
		((completion_code) & SCU_UNSOLICITED_FRAME_MASK) \
		>> SCU_UNSOLICITED_FRAME_SHIFT \
	)

#घोषणा SCU_UNSOLICITED_FRAME_ERROR_MASK  0x00008000

/**
 * SCU_GET_FRAME_ERROR() -
 *
 * This macro वापसs a zero (0) value अगर there is no frame error otherwise it
 * वापसs non-zero (!0).
 */
#घोषणा SCU_GET_FRAME_ERROR(completion_code) \
	((completion_code) & SCU_UNSOLICITED_FRAME_ERROR_MASK)

/**
 *
 *
 * These स्थिरants represent normalized completion codes which must be shअगरted
 * 18 bits to match it with the hardware completion code. In a 16-bit compiler,
 * immediate स्थिरants are 16-bit values (the size of an पूर्णांक). If we shअगरt
 * those by 18 bits, we completely lose the value. To ensure the value is a
 * 32-bit value like we want, each immediate value must be cast to a u32.
 */
#घोषणा SCU_TASK_DONE_GOOD                                  ((u32)0x00)
#घोषणा SCU_TASK_DONE_TX_RAW_CMD_ERR                        ((u32)0x08)
#घोषणा SCU_TASK_DONE_CRC_ERR                               ((u32)0x14)
#घोषणा SCU_TASK_DONE_CHECK_RESPONSE                        ((u32)0x14)
#घोषणा SCU_TASK_DONE_GEN_RESPONSE                          ((u32)0x15)
#घोषणा SCU_TASK_DONE_NAK_CMD_ERR                           ((u32)0x16)
#घोषणा SCU_TASK_DONE_CMD_LL_R_ERR                          ((u32)0x16)
#घोषणा SCU_TASK_DONE_LL_R_ERR                              ((u32)0x17)
#घोषणा SCU_TASK_DONE_ACK_NAK_TO                            ((u32)0x17)
#घोषणा SCU_TASK_DONE_LL_PERR                               ((u32)0x18)
#घोषणा SCU_TASK_DONE_LL_SY_TERM                            ((u32)0x19)
#घोषणा SCU_TASK_DONE_NAK_ERR                               ((u32)0x19)
#घोषणा SCU_TASK_DONE_LL_LF_TERM                            ((u32)0x1A)
#घोषणा SCU_TASK_DONE_DATA_LEN_ERR                          ((u32)0x1A)
#घोषणा SCU_TASK_DONE_LL_CL_TERM                            ((u32)0x1B)
#घोषणा SCU_TASK_DONE_BREAK_RCVD                            ((u32)0x1B)
#घोषणा SCU_TASK_DONE_LL_ABORT_ERR                          ((u32)0x1B)
#घोषणा SCU_TASK_DONE_SEQ_INV_TYPE                          ((u32)0x1C)
#घोषणा SCU_TASK_DONE_UNEXP_XR                              ((u32)0x1C)
#घोषणा SCU_TASK_DONE_INV_FIS_TYPE                          ((u32)0x1D)
#घोषणा SCU_TASK_DONE_XR_IU_LEN_ERR                         ((u32)0x1D)
#घोषणा SCU_TASK_DONE_INV_FIS_LEN                           ((u32)0x1E)
#घोषणा SCU_TASK_DONE_XR_WD_LEN                             ((u32)0x1E)
#घोषणा SCU_TASK_DONE_SDMA_ERR                              ((u32)0x1F)
#घोषणा SCU_TASK_DONE_OFFSET_ERR                            ((u32)0x20)
#घोषणा SCU_TASK_DONE_MAX_PLD_ERR                           ((u32)0x21)
#घोषणा SCU_TASK_DONE_EXCESS_DATA                           ((u32)0x22)
#घोषणा SCU_TASK_DONE_LF_ERR                                ((u32)0x23)
#घोषणा SCU_TASK_DONE_UNEXP_FIS                             ((u32)0x24)
#घोषणा SCU_TASK_DONE_UNEXP_RESP                            ((u32)0x24)
#घोषणा SCU_TASK_DONE_EARLY_RESP                            ((u32)0x25)
#घोषणा SCU_TASK_DONE_SMP_RESP_TO_ERR                       ((u32)0x26)
#घोषणा SCU_TASK_DONE_DMASETUP_सूचीERR                       ((u32)0x27)
#घोषणा SCU_TASK_DONE_SMP_UFI_ERR                           ((u32)0x27)
#घोषणा SCU_TASK_DONE_XFERCNT_ERR                           ((u32)0x28)
#घोषणा SCU_TASK_DONE_SMP_FRM_TYPE_ERR                      ((u32)0x28)
#घोषणा SCU_TASK_DONE_SMP_LL_RX_ERR                         ((u32)0x29)
#घोषणा SCU_TASK_DONE_RESP_LEN_ERR                          ((u32)0x2A)
#घोषणा SCU_TASK_DONE_UNEXP_DATA                            ((u32)0x2B)
#घोषणा SCU_TASK_DONE_OPEN_FAIL                             ((u32)0x2C)
#घोषणा SCU_TASK_DONE_UNEXP_SDBFIS                          ((u32)0x2D)
#घोषणा SCU_TASK_DONE_REG_ERR                               ((u32)0x2E)
#घोषणा SCU_TASK_DONE_SDB_ERR                               ((u32)0x2F)
#घोषणा SCU_TASK_DONE_TASK_ABORT                            ((u32)0x30)
#घोषणा SCU_TASK_DONE_CMD_SDMA_ERR                          ((U32)0x32)
#घोषणा SCU_TASK_DONE_CMD_LL_ABORT_ERR                      ((U32)0x33)
#घोषणा SCU_TASK_OPEN_REJECT_WRONG_DESTINATION              ((u32)0x34)
#घोषणा SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_1             ((u32)0x35)
#घोषणा SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_2             ((u32)0x36)
#घोषणा SCU_TASK_OPEN_REJECT_RESERVED_ABANDON_3             ((u32)0x37)
#घोषणा SCU_TASK_OPEN_REJECT_BAD_DESTINATION                ((u32)0x38)
#घोषणा SCU_TASK_OPEN_REJECT_ZONE_VIOLATION                 ((u32)0x39)
#घोषणा SCU_TASK_DONE_VIIT_ENTRY_NV                         ((u32)0x3A)
#घोषणा SCU_TASK_DONE_IIT_ENTRY_NV                          ((u32)0x3B)
#घोषणा SCU_TASK_DONE_RNCNV_OUTBOUND                        ((u32)0x3C)
#घोषणा SCU_TASK_OPEN_REJECT_STP_RESOURCES_BUSY             ((u32)0x3D)
#घोषणा SCU_TASK_OPEN_REJECT_PROTOCOL_NOT_SUPPORTED         ((u32)0x3E)
#घोषणा SCU_TASK_OPEN_REJECT_CONNECTION_RATE_NOT_SUPPORTED  ((u32)0x3F)

#पूर्ण_अगर /* _SCU_COMPLETION_CODES_HEADER_ */
