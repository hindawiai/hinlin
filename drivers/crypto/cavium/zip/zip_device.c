<शैली गुरु>
/***********************license start************************************
 * Copyright (c) 2003-2017 Cavium, Inc.
 * All rights reserved.
 *
 * License: one of 'Cavium License' or 'GNU General Public License Version 2'
 *
 * This file is provided under the terms of the Cavium License (see below)
 * or under the terms of GNU General Public License, Version 2, as
 * published by the Free Software Foundation. When using or redistributing
 * this file, you may करो so under either license.
 *
 * Cavium License:  Redistribution and use in source and binary क्रमms, with
 * or without modअगरication, are permitted provided that the following
 * conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary क्रमm must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the करोcumentation and/or other materials provided
 *    with the distribution.
 *
 *  * Neither the name of Cavium Inc. nor the names of its contributors may be
 *    used to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * This Software, including technical data, may be subject to U.S. export
 * control laws, including the U.S. Export Administration Act and its
 * associated regulations, and may be subject to export or import
 * regulations in other countries.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS
 * OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
 * RESPECT TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
 * REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
 * DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY)
 * WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A
 * PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
 * ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE
 * ENTIRE  RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES
 * WITH YOU.
 ***********************license end**************************************/

#समावेश "common.h"
#समावेश "zip_deflate.h"

/**
 * zip_cmd_queue_consumed - Calculates the space consumed in the command queue.
 *
 * @zip_dev: Poपूर्णांकer to zip device काष्ठाure
 * @queue:   Queue number
 *
 * Return: Bytes consumed in the command queue buffer.
 */
अटल अंतरभूत u32 zip_cmd_queue_consumed(काष्ठा zip_device *zip_dev, पूर्णांक queue)
अणु
	वापस ((zip_dev->iq[queue].sw_head - zip_dev->iq[queue].sw_tail) *
		माप(u64 *));
पूर्ण

/**
 * zip_load_instr - Submits the inकाष्ठाion पूर्णांकo the ZIP command queue
 * @instr:      Poपूर्णांकer to the inकाष्ठाion to be submitted
 * @zip_dev:    Poपूर्णांकer to ZIP device काष्ठाure to which the inकाष्ठाion is to
 *              be submitted
 *
 * This function copies the ZIP inकाष्ठाion to the command queue and rings the
 * करोorbell to notअगरy the engine of the inकाष्ठाion submission. The command
 * queue is मुख्यtained in a circular fashion. When there is space क्रम exactly
 * one inकाष्ठाion in the queue, next chunk poपूर्णांकer of the queue is made to
 * poपूर्णांक to the head of the queue, thus मुख्यtaining a circular queue.
 *
 * Return: Queue number to which the inकाष्ठाion was submitted
 */
u32 zip_load_instr(जोड़ zip_inst_s *instr,
		   काष्ठा zip_device *zip_dev)
अणु
	जोड़ zip_quex_करोorbell dbell;
	u32 queue = 0;
	u32 consumed = 0;
	u64 *ncb_ptr = शून्य;
	जोड़ zip_nptr_s ncp;

	/*
	 * Distribute the inकाष्ठाions between the enabled queues based on
	 * the CPU id.
	 */
	अगर (raw_smp_processor_id() % 2 == 0)
		queue = 0;
	अन्यथा
		queue = 1;

	zip_dbg("CPU Core: %d Queue number:%d", raw_smp_processor_id(), queue);

	/* Take cmd buffer lock */
	spin_lock(&zip_dev->iq[queue].lock);

	/*
	 * Command Queue implementation
	 * 1. If there is place क्रम new inकाष्ठाions, push the cmd at sw_head.
	 * 2. If there is place क्रम exactly one inकाष्ठाion, push the new cmd
	 *    at the sw_head. Make sw_head poपूर्णांक to the sw_tail to make it
	 *    circular. Write sw_head's physical address to the "Next-Chunk
	 *    Buffer Ptr" to make it cmd_hw_tail.
	 * 3. Ring the करोor bell.
	 */
	zip_dbg("sw_head : %lx", zip_dev->iq[queue].sw_head);
	zip_dbg("sw_tail : %lx", zip_dev->iq[queue].sw_tail);

	consumed = zip_cmd_queue_consumed(zip_dev, queue);
	/* Check अगर there is space to push just one cmd */
	अगर ((consumed + 128) == (ZIP_CMD_QBUF_SIZE - 8)) अणु
		zip_dbg("Cmd queue space available for single command");
		/* Space क्रम one cmd, pust it and make it circular queue */
		स_नकल((u8 *)zip_dev->iq[queue].sw_head, (u8 *)instr,
		       माप(जोड़ zip_inst_s));
		zip_dev->iq[queue].sw_head += 16; /* 16 64_bit words = 128B */

		/* Now, poपूर्णांक the "Next-Chunk Buffer Ptr" to sw_head */
		ncb_ptr = zip_dev->iq[queue].sw_head;

		zip_dbg("ncb addr :0x%lx sw_head addr :0x%lx",
			ncb_ptr, zip_dev->iq[queue].sw_head - 16);

		/* Using Circular command queue */
		zip_dev->iq[queue].sw_head = zip_dev->iq[queue].sw_tail;
		/* Mark this buffer क्रम मुक्त */
		zip_dev->iq[queue].मुक्त_flag = 1;

		/* Write new chunk buffer address at "Next-Chunk Buffer Ptr" */
		ncp.u_reg64 = 0ull;
		ncp.s.addr = __pa(zip_dev->iq[queue].sw_head);
		*ncb_ptr = ncp.u_reg64;
		zip_dbg("*ncb_ptr :0x%lx sw_head[phys] :0x%lx",
			*ncb_ptr, __pa(zip_dev->iq[queue].sw_head));

		zip_dev->iq[queue].pend_cnt++;

	पूर्ण अन्यथा अणु
		zip_dbg("Enough space is available for commands");
		/* Push this cmd to cmd queue buffer */
		स_नकल((u8 *)zip_dev->iq[queue].sw_head, (u8 *)instr,
		       माप(जोड़ zip_inst_s));
		zip_dev->iq[queue].sw_head += 16; /* 16 64_bit words = 128B */

		zip_dev->iq[queue].pend_cnt++;
	पूर्ण
	zip_dbg("sw_head :0x%lx sw_tail :0x%lx hw_tail :0x%lx",
		zip_dev->iq[queue].sw_head, zip_dev->iq[queue].sw_tail,
		zip_dev->iq[queue].hw_tail);

	zip_dbg(" Pushed the new cmd : pend_cnt : %d",
		zip_dev->iq[queue].pend_cnt);

	/* Ring the करोorbell */
	dbell.u_reg64     = 0ull;
	dbell.s.dbell_cnt = 1;
	zip_reg_ग_लिखो(dbell.u_reg64,
		      (zip_dev->reg_base + ZIP_QUEX_DOORBELL(queue)));

	/* Unlock cmd buffer lock */
	spin_unlock(&zip_dev->iq[queue].lock);

	वापस queue;
पूर्ण

/**
 * zip_update_cmd_bufs - Updates the queue statistics after posting the
 *                       inकाष्ठाion
 * @zip_dev: Poपूर्णांकer to zip device काष्ठाure
 * @queue:   Queue number
 */
व्योम zip_update_cmd_bufs(काष्ठा zip_device *zip_dev, u32 queue)
अणु
	/* Take cmd buffer lock */
	spin_lock(&zip_dev->iq[queue].lock);

	/* Check अगर the previous buffer can be मुक्तd */
	अगर (zip_dev->iq[queue].मुक्त_flag == 1) अणु
		zip_dbg("Free flag. Free cmd buffer, adjust sw head and tail");
		/* Reset the मुक्त flag */
		zip_dev->iq[queue].मुक्त_flag = 0;

		/* Poपूर्णांक the hw_tail to start of the new chunk buffer */
		zip_dev->iq[queue].hw_tail = zip_dev->iq[queue].sw_head;
	पूर्ण अन्यथा अणु
		zip_dbg("Free flag not set. increment hw tail");
		zip_dev->iq[queue].hw_tail += 16; /* 16 64_bit words = 128B */
	पूर्ण

	zip_dev->iq[queue].करोne_cnt++;
	zip_dev->iq[queue].pend_cnt--;

	zip_dbg("sw_head :0x%lx sw_tail :0x%lx hw_tail :0x%lx",
		zip_dev->iq[queue].sw_head, zip_dev->iq[queue].sw_tail,
		zip_dev->iq[queue].hw_tail);
	zip_dbg(" Got CC : pend_cnt : %d\n", zip_dev->iq[queue].pend_cnt);

	spin_unlock(&zip_dev->iq[queue].lock);
पूर्ण
