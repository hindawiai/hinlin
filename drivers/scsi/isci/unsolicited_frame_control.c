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

#समावेश "host.h"
#समावेश "unsolicited_frame_control.h"
#समावेश "registers.h"

व्योम sci_unsolicited_frame_control_स्थिरruct(काष्ठा isci_host *ihost)
अणु
	काष्ठा sci_unsolicited_frame_control *uf_control = &ihost->uf_control;
	काष्ठा sci_unsolicited_frame *uf;
	dma_addr_t dma = ihost->ufi_dma;
	व्योम *virt = ihost->ufi_buf;
	पूर्णांक i;

	/*
	 * The Unsolicited Frame buffers are set at the start of the UF
	 * memory descriptor entry. The headers and address table will be
	 * placed after the buffers.
	 */

	/*
	 * Program the location of the UF header table पूर्णांकo the SCU.
	 * Notes:
	 * - The address must align on a 64-byte boundary. Guaranteed to be
	 *   on 64-byte boundary alपढ़ोy 1KB boundary क्रम unsolicited frames.
	 * - Program unused header entries to overlap with the last
	 *   unsolicited frame.  The silicon will never DMA to these unused
	 *   headers, since we program the UF address table poपूर्णांकers to
	 *   शून्य.
	 */
	uf_control->headers.physical_address = dma + SCI_UFI_BUF_SIZE;
	uf_control->headers.array = virt + SCI_UFI_BUF_SIZE;

	/*
	 * Program the location of the UF address table पूर्णांकo the SCU.
	 * Notes:
	 * - The address must align on a 64-bit boundary. Guaranteed to be on 64
	 *   byte boundary alपढ़ोy due to above programming headers being on a
	 *   64-bit boundary and headers are on a 64-bytes in size.
	 */
	uf_control->address_table.physical_address = dma + SCI_UFI_BUF_SIZE + SCI_UFI_HDR_SIZE;
	uf_control->address_table.array = virt + SCI_UFI_BUF_SIZE + SCI_UFI_HDR_SIZE;
	uf_control->get = 0;

	/*
	 * UF buffer requirements are:
	 * - The last entry in the UF queue is not शून्य.
	 * - There is a घातer of 2 number of entries (शून्य or not-शून्य)
	 *   programmed पूर्णांकo the queue.
	 * - Aligned on a 1KB boundary. */

	/*
	 * Program the actual used UF buffers पूर्णांकo the UF address table and
	 * the controller's array of UFs.
	 */
	क्रम (i = 0; i < SCU_MAX_UNSOLICITED_FRAMES; i++) अणु
		uf = &uf_control->buffers.array[i];

		uf_control->address_table.array[i] = dma;

		uf->buffer = virt;
		uf->header = &uf_control->headers.array[i];
		uf->state  = UNSOLICITED_FRAME_EMPTY;

		/*
		 * Increment the address of the physical and भव memory
		 * poपूर्णांकers. Everything is aligned on 1k boundary with an
		 * increment of 1k.
		 */
		virt += SCU_UNSOLICITED_FRAME_BUFFER_SIZE;
		dma += SCU_UNSOLICITED_FRAME_BUFFER_SIZE;
	पूर्ण
पूर्ण

क्रमागत sci_status sci_unsolicited_frame_control_get_header(काष्ठा sci_unsolicited_frame_control *uf_control,
							 u32 frame_index,
							 व्योम **frame_header)
अणु
	अगर (frame_index < SCU_MAX_UNSOLICITED_FRAMES) अणु
		/* Skip the first word in the frame since this is a controll word used
		 * by the hardware.
		 */
		*frame_header = &uf_control->buffers.array[frame_index].header->data;

		वापस SCI_SUCCESS;
	पूर्ण

	वापस SCI_FAILURE_INVALID_PARAMETER_VALUE;
पूर्ण

क्रमागत sci_status sci_unsolicited_frame_control_get_buffer(काष्ठा sci_unsolicited_frame_control *uf_control,
							 u32 frame_index,
							 व्योम **frame_buffer)
अणु
	अगर (frame_index < SCU_MAX_UNSOLICITED_FRAMES) अणु
		*frame_buffer = uf_control->buffers.array[frame_index].buffer;

		वापस SCI_SUCCESS;
	पूर्ण

	वापस SCI_FAILURE_INVALID_PARAMETER_VALUE;
पूर्ण

bool sci_unsolicited_frame_control_release_frame(काष्ठा sci_unsolicited_frame_control *uf_control,
						 u32 frame_index)
अणु
	u32 frame_get;
	u32 frame_cycle;

	frame_get   = uf_control->get & (SCU_MAX_UNSOLICITED_FRAMES - 1);
	frame_cycle = uf_control->get & SCU_MAX_UNSOLICITED_FRAMES;

	/*
	 * In the event there are शून्य entries in the UF table, we need to
	 * advance the get poपूर्णांकer in order to find out अगर this frame should
	 * be released (i.e. update the get poपूर्णांकer)
	 */
	जबतक (lower_32_bits(uf_control->address_table.array[frame_get]) == 0 &&
	       upper_32_bits(uf_control->address_table.array[frame_get]) == 0 &&
	       frame_get < SCU_MAX_UNSOLICITED_FRAMES)
		frame_get++;

	/*
	 * The table has a शून्य entry as it's last element.  This is
	 * illegal.
	 */
	BUG_ON(frame_get >= SCU_MAX_UNSOLICITED_FRAMES);
	अगर (frame_index >= SCU_MAX_UNSOLICITED_FRAMES)
		वापस false;

	uf_control->buffers.array[frame_index].state = UNSOLICITED_FRAME_RELEASED;

	अगर (frame_get != frame_index) अणु
		/*
		 * Frames reमुख्य in use until we advance the get poपूर्णांकer
		 * so there is nothing we can करो here
		 */
		वापस false;
	पूर्ण

	/*
	 * The frame index is equal to the current get poपूर्णांकer so we
	 * can now मुक्त up all of the frame entries that
	 */
	जबतक (uf_control->buffers.array[frame_get].state == UNSOLICITED_FRAME_RELEASED) अणु
		uf_control->buffers.array[frame_get].state = UNSOLICITED_FRAME_EMPTY;

		अगर (frame_get+1 == SCU_MAX_UNSOLICITED_FRAMES-1) अणु
			frame_cycle ^= SCU_MAX_UNSOLICITED_FRAMES;
			frame_get = 0;
		पूर्ण अन्यथा
			frame_get++;
	पूर्ण

	uf_control->get = SCU_UFQGP_GEN_BIT(ENABLE_BIT) | frame_cycle | frame_get;

	वापस true;
पूर्ण
