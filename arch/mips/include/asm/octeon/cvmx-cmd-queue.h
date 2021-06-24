<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2008 Cavium Networks
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this file; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a dअगरferent license from Cavium.
 * Contact Cavium Networks क्रम more inक्रमmation
 ***********************license end**************************************/

/*
 *
 * Support functions क्रम managing command queues used क्रम
 * various hardware blocks.
 *
 * The common command queue infraकाष्ठाure असलtracts out the
 * software necessary क्रम adding to Octeon's chained queue
 * काष्ठाures. These काष्ठाures are used क्रम commands to the
 * PKO, ZIP, DFA, RAID, and DMA engine blocks. Although each
 * hardware unit takes commands and CSRs of dअगरferent types,
 * they all use basic linked command buffers to store the
 * pending request. In general, users of the CVMX API करोn't
 * call cvmx-cmd-queue functions directly. Instead the hardware
 * unit specअगरic wrapper should be used. The wrappers perक्रमm
 * unit specअगरic validation and CSR ग_लिखोs to submit the
 * commands.
 *
 * Even though most software will never directly पूर्णांकeract with
 * cvmx-cmd-queue, knowledge of its पूर्णांकernal working can help
 * in diagnosing perक्रमmance problems and help with debugging.
 *
 * Command queue poपूर्णांकers are stored in a global named block
 * called "cvmx_cmd_queues". Except क्रम the PKO queues, each
 * hardware queue is stored in its own cache line to reduce SMP
 * contention on spin locks. The PKO queues are stored such that
 * every 16th queue is next to each other in memory. This scheme
 * allows क्रम queues being in separate cache lines when there
 * are low number of queues per port. With 16 queues per port,
 * the first queue क्रम each port is in the same cache area. The
 * second queues क्रम each port are in another area, etc. This
 * allows software to implement very efficient lockless PKO with
 * 16 queues per port using a minimum of cache lines per core.
 * All queues क्रम a given core will be isolated in the same
 * cache area.
 *
 * In addition to the memory poपूर्णांकer layout, cvmx-cmd-queue
 * provides an optimized fair ll/sc locking mechanism क्रम the
 * queues. The lock uses a "ticket / now serving" model to
 * मुख्यtain fair order on contended locks. In addition, it uses
 * predicted locking समय to limit cache contention. When a core
 * know it must रुको in line क्रम a lock, it spins on the
 * पूर्णांकernal cycle counter to completely eliminate any causes of
 * bus traffic.
 *
 */

#अगर_अघोषित __CVMX_CMD_QUEUE_H__
#घोषणा __CVMX_CMD_QUEUE_H__

#समावेश <linux/prefetch.h>

#समावेश <यंत्र/compiler.h>

#समावेश <यंत्र/octeon/cvmx-fpa.h>
/**
 * By शेष we disable the max depth support. Most programs
 * करोn't use it and it slows करोwn the command queue processing
 * signअगरicantly.
 */
#अगर_अघोषित CVMX_CMD_QUEUE_ENABLE_MAX_DEPTH
#घोषणा CVMX_CMD_QUEUE_ENABLE_MAX_DEPTH 0
#पूर्ण_अगर

/**
 * Enumeration representing all hardware blocks that use command
 * queues. Each hardware block has up to 65536 sub identअगरiers क्रम
 * multiple command queues. Not all chips support all hardware
 * units.
 */
प्रकार क्रमागत अणु
	CVMX_CMD_QUEUE_PKO_BASE = 0x00000,

#घोषणा CVMX_CMD_QUEUE_PKO(queue) \
	((cvmx_cmd_queue_id_t)(CVMX_CMD_QUEUE_PKO_BASE + (0xffff&(queue))))

	CVMX_CMD_QUEUE_ZIP = 0x10000,
	CVMX_CMD_QUEUE_DFA = 0x20000,
	CVMX_CMD_QUEUE_RAID = 0x30000,
	CVMX_CMD_QUEUE_DMA_BASE = 0x40000,

#घोषणा CVMX_CMD_QUEUE_DMA(queue) \
	((cvmx_cmd_queue_id_t)(CVMX_CMD_QUEUE_DMA_BASE + (0xffff&(queue))))

	CVMX_CMD_QUEUE_END = 0x50000,
पूर्ण cvmx_cmd_queue_id_t;

/**
 * Command ग_लिखो operations can fail अगर the command queue needs
 * a new buffer and the associated FPA pool is empty. It can also
 * fail अगर the number of queued command words reaches the maximum
 * set at initialization.
 */
प्रकार क्रमागत अणु
	CVMX_CMD_QUEUE_SUCCESS = 0,
	CVMX_CMD_QUEUE_NO_MEMORY = -1,
	CVMX_CMD_QUEUE_FULL = -2,
	CVMX_CMD_QUEUE_INVALID_PARAM = -3,
	CVMX_CMD_QUEUE_ALREADY_SETUP = -4,
पूर्ण cvmx_cmd_queue_result_t;

प्रकार काष्ठा अणु
	/* You have lock when this is your ticket */
	uपूर्णांक8_t now_serving;
	uपूर्णांक64_t unused1:24;
	/* Maximum outstanding command words */
	uपूर्णांक32_t max_depth;
	/* FPA pool buffers come from */
	uपूर्णांक64_t fpa_pool:3;
	/* Top of command buffer poपूर्णांकer shअगरted 7 */
	uपूर्णांक64_t base_ptr_भाग128:29;
	uपूर्णांक64_t unused2:6;
	/* FPA buffer size in 64bit words minus 1 */
	uपूर्णांक64_t pool_size_m1:13;
	/* Number of commands alपढ़ोy used in buffer */
	uपूर्णांक64_t index:13;
पूर्ण __cvmx_cmd_queue_state_t;

/**
 * This काष्ठाure contains the global state of all command queues.
 * It is stored in a booपंचांगem named block and shared by all
 * applications running on Octeon. Tickets are stored in a dअगरfernet
 * cache line that queue inक्रमmation to reduce the contention on the
 * ll/sc used to get a ticket. If this is not the हाल, the update
 * of queue state causes the ll/sc to fail quite often.
 */
प्रकार काष्ठा अणु
	uपूर्णांक64_t ticket[(CVMX_CMD_QUEUE_END >> 16) * 256];
	__cvmx_cmd_queue_state_t state[(CVMX_CMD_QUEUE_END >> 16) * 256];
पूर्ण __cvmx_cmd_queue_all_state_t;

/**
 * Initialize a command queue क्रम use. The initial FPA buffer is
 * allocated and the hardware unit is configured to poपूर्णांक to the
 * new command queue.
 *
 * @queue_id:  Hardware command queue to initialize.
 * @max_depth: Maximum outstanding commands that can be queued.
 * @fpa_pool:  FPA pool the command queues should come from.
 * @pool_size: Size of each buffer in the FPA pool (bytes)
 *
 * Returns CVMX_CMD_QUEUE_SUCCESS or a failure code
 */
cvmx_cmd_queue_result_t cvmx_cmd_queue_initialize(cvmx_cmd_queue_id_t queue_id,
						  पूर्णांक max_depth, पूर्णांक fpa_pool,
						  पूर्णांक pool_size);

/**
 * Shutकरोwn a queue a मुक्त it's command buffers to the FPA. The
 * hardware connected to the queue must be stopped beक्रमe this
 * function is called.
 *
 * @queue_id: Queue to shutकरोwn
 *
 * Returns CVMX_CMD_QUEUE_SUCCESS or a failure code
 */
cvmx_cmd_queue_result_t cvmx_cmd_queue_shutकरोwn(cvmx_cmd_queue_id_t queue_id);

/**
 * Return the number of command words pending in the queue. This
 * function may be relatively slow क्रम some hardware units.
 *
 * @queue_id: Hardware command queue to query
 *
 * Returns Number of outstanding commands
 */
पूर्णांक cvmx_cmd_queue_length(cvmx_cmd_queue_id_t queue_id);

/**
 * Return the command buffer to be written to. The purpose of this
 * function is to allow CVMX routine access t othe low level buffer
 * क्रम initial hardware setup. User applications should not call this
 * function directly.
 *
 * @queue_id: Command queue to query
 *
 * Returns Command buffer or शून्य on failure
 */
व्योम *cvmx_cmd_queue_buffer(cvmx_cmd_queue_id_t queue_id);

/**
 * Get the index पूर्णांकo the state arrays क्रम the supplied queue id.
 *
 * @queue_id: Queue ID to get an index क्रम
 *
 * Returns Index पूर्णांकo the state arrays
 */
अटल अंतरभूत पूर्णांक __cvmx_cmd_queue_get_index(cvmx_cmd_queue_id_t queue_id)
अणु
	/*
	 * Warning: This code currently only works with devices that
	 * have 256 queues or less. Devices with more than 16 queues
	 * are laid out in memory to allow cores quick access to
	 * every 16th queue. This reduces cache thrashing when you are
	 * running 16 queues per port to support lockless operation.
	 */
	पूर्णांक unit = queue_id >> 16;
	पूर्णांक q = (queue_id >> 4) & 0xf;
	पूर्णांक core = queue_id & 0xf;
	वापस unit * 256 + core * 16 + q;
पूर्ण

/**
 * Lock the supplied queue so nobody अन्यथा is updating it at the same
 * समय as us.
 *
 * @queue_id: Queue ID to lock
 * @qptr:     Poपूर्णांकer to the queue's global state
 */
अटल अंतरभूत व्योम __cvmx_cmd_queue_lock(cvmx_cmd_queue_id_t queue_id,
					 __cvmx_cmd_queue_state_t *qptr)
अणु
	बाह्य __cvmx_cmd_queue_all_state_t
	    *__cvmx_cmd_queue_state_ptr;
	पूर्णांक पंचांगp;
	पूर्णांक my_ticket;
	prefetch(qptr);
	यंत्र अस्थिर (
		".set push\n"
		".set noreorder\n"
		"1:\n"
		/* Atomic add one to ticket_ptr */
		"ll	%[my_ticket], %[ticket_ptr]\n"
		/* and store the original value */
		"li	%[ticket], 1\n"
		/* in my_ticket */
		"baddu	%[ticket], %[my_ticket]\n"
		"sc	%[ticket], %[ticket_ptr]\n"
		"beqz	%[ticket], 1b\n"
		" nop\n"
		/* Load the current now_serving ticket */
		"lbu	%[ticket], %[now_serving]\n"
		"2:\n"
		/* Jump out अगर now_serving == my_ticket */
		"beq	%[ticket], %[my_ticket], 4f\n"
		/* Find out how many tickets are in front of me */
		" subu	 %[ticket], %[my_ticket], %[ticket]\n"
		/* Use tickets in front of me minus one to delay */
		"subu  %[ticket], 1\n"
		/* Delay will be ((tickets in front)-1)*32 loops */
		"cins	%[ticket], %[ticket], 5, 7\n"
		"3:\n"
		/* Loop here until our ticket might be up */
		"bnez	%[ticket], 3b\n"
		" subu	%[ticket], 1\n"
		/* Jump back up to check out ticket again */
		"b	2b\n"
		/* Load the current now_serving ticket */
		" lbu	%[ticket], %[now_serving]\n"
		"4:\n"
		".set pop\n" :
		[ticket_ptr] "=" GCC_OFF_SMALL_ASM()(__cvmx_cmd_queue_state_ptr->ticket[__cvmx_cmd_queue_get_index(queue_id)]),
		[now_serving] "=m"(qptr->now_serving), [ticket] "=r"(पंचांगp),
		[my_ticket] "=r"(my_ticket)
	    );
पूर्ण

/**
 * Unlock the queue, flushing all ग_लिखोs.
 *
 * @qptr:   Queue to unlock
 */
अटल अंतरभूत व्योम __cvmx_cmd_queue_unlock(__cvmx_cmd_queue_state_t *qptr)
अणु
	qptr->now_serving++;
	CVMX_SYNCWS;
पूर्ण

/**
 * Get the queue state काष्ठाure क्रम the given queue id
 *
 * @queue_id: Queue id to get
 *
 * Returns Queue काष्ठाure or शून्य on failure
 */
अटल अंतरभूत __cvmx_cmd_queue_state_t
    *__cvmx_cmd_queue_get_state(cvmx_cmd_queue_id_t queue_id)
अणु
	बाह्य __cvmx_cmd_queue_all_state_t
	    *__cvmx_cmd_queue_state_ptr;
	वापस &__cvmx_cmd_queue_state_ptr->
	    state[__cvmx_cmd_queue_get_index(queue_id)];
पूर्ण

/**
 * Write an arbitrary number of command words to a command queue.
 * This is a generic function; the fixed number of command word
 * functions yield higher perक्रमmance.
 *
 * @queue_id:  Hardware command queue to ग_लिखो to
 * @use_locking:
 *		    Use पूर्णांकernal locking to ensure exclusive access क्रम queue
 *		    updates. If you करोn't use this locking you must ensure
 *		    exclusivity some other way. Locking is strongly recommended.
 * @cmd_count: Number of command words to ग_लिखो
 * @cmds:      Array of commands to ग_लिखो
 *
 * Returns CVMX_CMD_QUEUE_SUCCESS or a failure code
 */
अटल अंतरभूत cvmx_cmd_queue_result_t cvmx_cmd_queue_ग_लिखो(cvmx_cmd_queue_id_t
							   queue_id,
							   पूर्णांक use_locking,
							   पूर्णांक cmd_count,
							   uपूर्णांक64_t *cmds)
अणु
	__cvmx_cmd_queue_state_t *qptr = __cvmx_cmd_queue_get_state(queue_id);

	/* Make sure nobody अन्यथा is updating the same queue */
	अगर (likely(use_locking))
		__cvmx_cmd_queue_lock(queue_id, qptr);

	/*
	 * If a max queue length was specअगरied then make sure we करोn't
	 * exceed it. If any part of the command would be below the
	 * limit we allow it.
	 */
	अगर (CVMX_CMD_QUEUE_ENABLE_MAX_DEPTH && unlikely(qptr->max_depth)) अणु
		अगर (unlikely
		    (cvmx_cmd_queue_length(queue_id) > (पूर्णांक)qptr->max_depth)) अणु
			अगर (likely(use_locking))
				__cvmx_cmd_queue_unlock(qptr);
			वापस CVMX_CMD_QUEUE_FULL;
		पूर्ण
	पूर्ण

	/*
	 * Normally there is plenty of room in the current buffer क्रम
	 * the command.
	 */
	अगर (likely(qptr->index + cmd_count < qptr->pool_size_m1)) अणु
		uपूर्णांक64_t *ptr =
		    (uपूर्णांक64_t *) cvmx_phys_to_ptr((uपूर्णांक64_t) qptr->
						  base_ptr_भाग128 << 7);
		ptr += qptr->index;
		qptr->index += cmd_count;
		जबतक (cmd_count--)
			*ptr++ = *cmds++;
	पूर्ण अन्यथा अणु
		uपूर्णांक64_t *ptr;
		पूर्णांक count;
		/*
		 * We need a new command buffer. Fail अगर there isn't
		 * one available.
		 */
		uपूर्णांक64_t *new_buffer =
		    (uपूर्णांक64_t *) cvmx_fpa_alloc(qptr->fpa_pool);
		अगर (unlikely(new_buffer == शून्य)) अणु
			अगर (likely(use_locking))
				__cvmx_cmd_queue_unlock(qptr);
			वापस CVMX_CMD_QUEUE_NO_MEMORY;
		पूर्ण
		ptr =
		    (uपूर्णांक64_t *) cvmx_phys_to_ptr((uपूर्णांक64_t) qptr->
						  base_ptr_भाग128 << 7);
		/*
		 * Figure out how many command words will fit in this
		 * buffer. One location will be needed क्रम the next
		 * buffer poपूर्णांकer.
		 */
		count = qptr->pool_size_m1 - qptr->index;
		ptr += qptr->index;
		cmd_count -= count;
		जबतक (count--)
			*ptr++ = *cmds++;
		*ptr = cvmx_ptr_to_phys(new_buffer);
		/*
		 * The current buffer is full and has a link to the
		 * next buffer. Time to ग_लिखो the rest of the commands
		 * पूर्णांकo the new buffer.
		 */
		qptr->base_ptr_भाग128 = *ptr >> 7;
		qptr->index = cmd_count;
		ptr = new_buffer;
		जबतक (cmd_count--)
			*ptr++ = *cmds++;
	पूर्ण

	/* All updates are complete. Release the lock and वापस */
	अगर (likely(use_locking))
		__cvmx_cmd_queue_unlock(qptr);
	वापस CVMX_CMD_QUEUE_SUCCESS;
पूर्ण

/**
 * Simple function to ग_लिखो two command words to a command
 * queue.
 *
 * @queue_id: Hardware command queue to ग_लिखो to
 * @use_locking:
 *		   Use पूर्णांकernal locking to ensure exclusive access क्रम queue
 *		   updates. If you करोn't use this locking you must ensure
 *		   exclusivity some other way. Locking is strongly recommended.
 * @cmd1:     Command
 * @cmd2:     Command
 *
 * Returns CVMX_CMD_QUEUE_SUCCESS or a failure code
 */
अटल अंतरभूत cvmx_cmd_queue_result_t cvmx_cmd_queue_ग_लिखो2(cvmx_cmd_queue_id_t
							    queue_id,
							    पूर्णांक use_locking,
							    uपूर्णांक64_t cmd1,
							    uपूर्णांक64_t cmd2)
अणु
	__cvmx_cmd_queue_state_t *qptr = __cvmx_cmd_queue_get_state(queue_id);

	/* Make sure nobody अन्यथा is updating the same queue */
	अगर (likely(use_locking))
		__cvmx_cmd_queue_lock(queue_id, qptr);

	/*
	 * If a max queue length was specअगरied then make sure we करोn't
	 * exceed it. If any part of the command would be below the
	 * limit we allow it.
	 */
	अगर (CVMX_CMD_QUEUE_ENABLE_MAX_DEPTH && unlikely(qptr->max_depth)) अणु
		अगर (unlikely
		    (cvmx_cmd_queue_length(queue_id) > (पूर्णांक)qptr->max_depth)) अणु
			अगर (likely(use_locking))
				__cvmx_cmd_queue_unlock(qptr);
			वापस CVMX_CMD_QUEUE_FULL;
		पूर्ण
	पूर्ण

	/*
	 * Normally there is plenty of room in the current buffer क्रम
	 * the command.
	 */
	अगर (likely(qptr->index + 2 < qptr->pool_size_m1)) अणु
		uपूर्णांक64_t *ptr =
		    (uपूर्णांक64_t *) cvmx_phys_to_ptr((uपूर्णांक64_t) qptr->
						  base_ptr_भाग128 << 7);
		ptr += qptr->index;
		qptr->index += 2;
		ptr[0] = cmd1;
		ptr[1] = cmd2;
	पूर्ण अन्यथा अणु
		uपूर्णांक64_t *ptr;
		/*
		 * Figure out how many command words will fit in this
		 * buffer. One location will be needed क्रम the next
		 * buffer poपूर्णांकer.
		 */
		पूर्णांक count = qptr->pool_size_m1 - qptr->index;
		/*
		 * We need a new command buffer. Fail अगर there isn't
		 * one available.
		 */
		uपूर्णांक64_t *new_buffer =
		    (uपूर्णांक64_t *) cvmx_fpa_alloc(qptr->fpa_pool);
		अगर (unlikely(new_buffer == शून्य)) अणु
			अगर (likely(use_locking))
				__cvmx_cmd_queue_unlock(qptr);
			वापस CVMX_CMD_QUEUE_NO_MEMORY;
		पूर्ण
		count--;
		ptr =
		    (uपूर्णांक64_t *) cvmx_phys_to_ptr((uपूर्णांक64_t) qptr->
						  base_ptr_भाग128 << 7);
		ptr += qptr->index;
		*ptr++ = cmd1;
		अगर (likely(count))
			*ptr++ = cmd2;
		*ptr = cvmx_ptr_to_phys(new_buffer);
		/*
		 * The current buffer is full and has a link to the
		 * next buffer. Time to ग_लिखो the rest of the commands
		 * पूर्णांकo the new buffer.
		 */
		qptr->base_ptr_भाग128 = *ptr >> 7;
		qptr->index = 0;
		अगर (unlikely(count == 0)) अणु
			qptr->index = 1;
			new_buffer[0] = cmd2;
		पूर्ण
	पूर्ण

	/* All updates are complete. Release the lock and वापस */
	अगर (likely(use_locking))
		__cvmx_cmd_queue_unlock(qptr);
	वापस CVMX_CMD_QUEUE_SUCCESS;
पूर्ण

/**
 * Simple function to ग_लिखो three command words to a command
 * queue.
 *
 * @queue_id: Hardware command queue to ग_लिखो to
 * @use_locking:
 *		   Use पूर्णांकernal locking to ensure exclusive access क्रम queue
 *		   updates. If you करोn't use this locking you must ensure
 *		   exclusivity some other way. Locking is strongly recommended.
 * @cmd1:     Command
 * @cmd2:     Command
 * @cmd3:     Command
 *
 * Returns CVMX_CMD_QUEUE_SUCCESS or a failure code
 */
अटल अंतरभूत cvmx_cmd_queue_result_t cvmx_cmd_queue_ग_लिखो3(cvmx_cmd_queue_id_t
							    queue_id,
							    पूर्णांक use_locking,
							    uपूर्णांक64_t cmd1,
							    uपूर्णांक64_t cmd2,
							    uपूर्णांक64_t cmd3)
अणु
	__cvmx_cmd_queue_state_t *qptr = __cvmx_cmd_queue_get_state(queue_id);

	/* Make sure nobody अन्यथा is updating the same queue */
	अगर (likely(use_locking))
		__cvmx_cmd_queue_lock(queue_id, qptr);

	/*
	 * If a max queue length was specअगरied then make sure we करोn't
	 * exceed it. If any part of the command would be below the
	 * limit we allow it.
	 */
	अगर (CVMX_CMD_QUEUE_ENABLE_MAX_DEPTH && unlikely(qptr->max_depth)) अणु
		अगर (unlikely
		    (cvmx_cmd_queue_length(queue_id) > (पूर्णांक)qptr->max_depth)) अणु
			अगर (likely(use_locking))
				__cvmx_cmd_queue_unlock(qptr);
			वापस CVMX_CMD_QUEUE_FULL;
		पूर्ण
	पूर्ण

	/*
	 * Normally there is plenty of room in the current buffer क्रम
	 * the command.
	 */
	अगर (likely(qptr->index + 3 < qptr->pool_size_m1)) अणु
		uपूर्णांक64_t *ptr =
		    (uपूर्णांक64_t *) cvmx_phys_to_ptr((uपूर्णांक64_t) qptr->
						  base_ptr_भाग128 << 7);
		ptr += qptr->index;
		qptr->index += 3;
		ptr[0] = cmd1;
		ptr[1] = cmd2;
		ptr[2] = cmd3;
	पूर्ण अन्यथा अणु
		uपूर्णांक64_t *ptr;
		/*
		 * Figure out how many command words will fit in this
		 * buffer. One location will be needed क्रम the next
		 * buffer poपूर्णांकer
		 */
		पूर्णांक count = qptr->pool_size_m1 - qptr->index;
		/*
		 * We need a new command buffer. Fail अगर there isn't
		 * one available
		 */
		uपूर्णांक64_t *new_buffer =
		    (uपूर्णांक64_t *) cvmx_fpa_alloc(qptr->fpa_pool);
		अगर (unlikely(new_buffer == शून्य)) अणु
			अगर (likely(use_locking))
				__cvmx_cmd_queue_unlock(qptr);
			वापस CVMX_CMD_QUEUE_NO_MEMORY;
		पूर्ण
		count--;
		ptr =
		    (uपूर्णांक64_t *) cvmx_phys_to_ptr((uपूर्णांक64_t) qptr->
						  base_ptr_भाग128 << 7);
		ptr += qptr->index;
		*ptr++ = cmd1;
		अगर (count) अणु
			*ptr++ = cmd2;
			अगर (count > 1)
				*ptr++ = cmd3;
		पूर्ण
		*ptr = cvmx_ptr_to_phys(new_buffer);
		/*
		 * The current buffer is full and has a link to the
		 * next buffer. Time to ग_लिखो the rest of the commands
		 * पूर्णांकo the new buffer.
		 */
		qptr->base_ptr_भाग128 = *ptr >> 7;
		qptr->index = 0;
		ptr = new_buffer;
		अगर (count == 0) अणु
			*ptr++ = cmd2;
			qptr->index++;
		पूर्ण
		अगर (count < 2) अणु
			*ptr++ = cmd3;
			qptr->index++;
		पूर्ण
	पूर्ण

	/* All updates are complete. Release the lock and वापस */
	अगर (likely(use_locking))
		__cvmx_cmd_queue_unlock(qptr);
	वापस CVMX_CMD_QUEUE_SUCCESS;
पूर्ण

#पूर्ण_अगर /* __CVMX_CMD_QUEUE_H__ */
