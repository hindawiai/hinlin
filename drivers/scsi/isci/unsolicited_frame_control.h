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

#अगर_अघोषित _SCIC_SDS_UNSOLICITED_FRAME_CONTROL_H_
#घोषणा _SCIC_SDS_UNSOLICITED_FRAME_CONTROL_H_

#समावेश "isci.h"

#घोषणा SCU_UNSOLICITED_FRAME_HEADER_DATA_DWORDS 15

/**
 * काष्ठा scu_unsolicited_frame_header -
 *
 * This काष्ठाure delineates the क्रमmat of an unsolicited frame header. The
 * first DWORD are UF attributes defined by the silicon architecture. The data
 * depicts actual header inक्रमmation received on the link.
 */
काष्ठा scu_unsolicited_frame_header अणु
	/**
	 * This field indicates अगर there is an Initiator Index Table entry with
	 * which this header is associated.
	 */
	u32 iit_exists:1;

	/**
	 * This field simply indicates the protocol type (i.e. SSP, STP, SMP).
	 */
	u32 protocol_type:3;

	/**
	 * This field indicates अगर the frame is an address frame (IAF or OAF)
	 * or अगर it is a inक्रमmation unit frame.
	 */
	u32 is_address_frame:1;

	/**
	 * This field simply indicates the connection rate at which the frame
	 * was received.
	 */
	u32 connection_rate:4;

	u32 reserved:23;

	/**
	 * This field represents the actual header data received on the link.
	 */
	u32 data[SCU_UNSOLICITED_FRAME_HEADER_DATA_DWORDS];

पूर्ण;



/**
 * क्रमागत unsolicited_frame_state -
 *
 * This क्रमागतeration represents the current unsolicited frame state.  The
 * controller object can not updtate the hardware unsolicited frame put poपूर्णांकer
 * unless it has alपढ़ोy processed the priror unsolicited frames.
 */
क्रमागत unsolicited_frame_state अणु
	/**
	 * This state is when the frame is empty and not in use.  It is
	 * dअगरferent from the released state in that the hardware could DMA
	 * data to this frame buffer.
	 */
	UNSOLICITED_FRAME_EMPTY,

	/**
	 * This state is set when the frame buffer is in use by by some
	 * object in the प्रणाली.
	 */
	UNSOLICITED_FRAME_IN_USE,

	/**
	 * This state is set when the frame is वापसed to the मुक्त pool
	 * but one or more frames prior to this one are still in use.
	 * Once all of the frame beक्रमe this one are मुक्तd it will go to
	 * the empty state.
	 */
	UNSOLICITED_FRAME_RELEASED,

	UNSOLICITED_FRAME_MAX_STATES
पूर्ण;

/**
 * काष्ठा sci_unsolicited_frame -
 *
 * This is the unsolicited frame data काष्ठाure it acts as the container क्रम
 * the current frame state, frame header and frame buffer.
 */
काष्ठा sci_unsolicited_frame अणु
	/**
	 * This field contains the current frame state
	 */
	क्रमागत unsolicited_frame_state state;

	/**
	 * This field poपूर्णांकs to the frame header data.
	 */
	काष्ठा scu_unsolicited_frame_header *header;

	/**
	 * This field poपूर्णांकs to the frame buffer data.
	 */
	व्योम *buffer;

पूर्ण;

/**
 * काष्ठा sci_uf_header_array -
 *
 * This काष्ठाure contains all of the unsolicited frame header inक्रमmation.
 */
काष्ठा sci_uf_header_array अणु
	/**
	 * This field is represents a भव poपूर्णांकer to the start
	 * address of the UF address table.  The table contains
	 * 64-bit poपूर्णांकers as required by the hardware.
	 */
	काष्ठा scu_unsolicited_frame_header *array;

	/**
	 * This field specअगरies the physical address location क्रम the UF
	 * buffer array.
	 */
	dma_addr_t physical_address;

पूर्ण;

/**
 * काष्ठा sci_uf_buffer_array -
 *
 * This काष्ठाure contains all of the unsolicited frame buffer (actual payload)
 * inक्रमmation.
 */
काष्ठा sci_uf_buffer_array अणु
	/**
	 * This field is the unsolicited frame data its used to manage
	 * the data क्रम the unsolicited frame requests.  It also represents
	 * the भव address location that corresponds to the
	 * physical_address field.
	 */
	काष्ठा sci_unsolicited_frame array[SCU_MAX_UNSOLICITED_FRAMES];

	/**
	 * This field specअगरies the physical address location क्रम the UF
	 * buffer array.
	 */
	dma_addr_t physical_address;
पूर्ण;

/**
 * काष्ठा sci_uf_address_table_array -
 *
 * This object मुख्यtains all of the unsolicited frame address table specअगरic
 * data.  The address table is a collection of 64-bit poपूर्णांकers that poपूर्णांक to
 * 1KB buffers पूर्णांकo which the silicon will DMA unsolicited frames.
 */
काष्ठा sci_uf_address_table_array अणु
	/**
	 * This field represents a भव poपूर्णांकer that refers to the
	 * starting address of the UF address table.
	 * 64-bit poपूर्णांकers are required by the hardware.
	 */
	u64 *array;

	/**
	 * This field specअगरies the physical address location क्रम the UF
	 * address table.
	 */
	dma_addr_t physical_address;

पूर्ण;

/**
 * काष्ठा sci_unsolicited_frame_control -
 *
 * This object contains all of the data necessary to handle unsolicited frames.
 */
काष्ठा sci_unsolicited_frame_control अणु
	/**
	 * This field is the software copy of the unsolicited frame queue
	 * get poपूर्णांकer.  The controller object ग_लिखोs this value to the
	 * hardware to let the hardware put more unsolicited frame entries.
	 */
	u32 get;

	/**
	 * This field contains all of the unsolicited frame header
	 * specअगरic fields.
	 */
	काष्ठा sci_uf_header_array headers;

	/**
	 * This field contains all of the unsolicited frame buffer
	 * specअगरic fields.
	 */
	काष्ठा sci_uf_buffer_array buffers;

	/**
	 * This field contains all of the unsolicited frame address table
	 * specअगरic fields.
	 */
	काष्ठा sci_uf_address_table_array address_table;

पूर्ण;

#घोषणा SCI_UFI_BUF_SIZE (SCU_MAX_UNSOLICITED_FRAMES * SCU_UNSOLICITED_FRAME_BUFFER_SIZE)
#घोषणा SCI_UFI_HDR_SIZE (SCU_MAX_UNSOLICITED_FRAMES * माप(काष्ठा scu_unsolicited_frame_header))
#घोषणा SCI_UFI_TOTAL_SIZE (SCI_UFI_BUF_SIZE + SCI_UFI_HDR_SIZE + SCU_MAX_UNSOLICITED_FRAMES * माप(u64))

काष्ठा isci_host;

व्योम sci_unsolicited_frame_control_स्थिरruct(काष्ठा isci_host *ihost);

क्रमागत sci_status sci_unsolicited_frame_control_get_header(
	काष्ठा sci_unsolicited_frame_control *uf_control,
	u32 frame_index,
	व्योम **frame_header);

क्रमागत sci_status sci_unsolicited_frame_control_get_buffer(
	काष्ठा sci_unsolicited_frame_control *uf_control,
	u32 frame_index,
	व्योम **frame_buffer);

bool sci_unsolicited_frame_control_release_frame(
	काष्ठा sci_unsolicited_frame_control *uf_control,
	u32 frame_index);

#पूर्ण_अगर /* _SCIC_SDS_UNSOLICITED_FRAME_CONTROL_H_ */
