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
 * Support functions क्रम managing command queues used क्रम
 * various hardware blocks.
 */

#समावेश <linux/kernel.h>

#समावेश <यंत्र/octeon/octeon.h>

#समावेश <यंत्र/octeon/cvmx-config.h>
#समावेश <यंत्र/octeon/cvmx-fpa.h>
#समावेश <यंत्र/octeon/cvmx-cmd-queue.h>

#समावेश <यंत्र/octeon/cvmx-npei-defs.h>
#समावेश <यंत्र/octeon/cvmx-pexp-defs.h>
#समावेश <यंत्र/octeon/cvmx-pko-defs.h>

/**
 * This application uses this poपूर्णांकer to access the global queue
 * state. It poपूर्णांकs to a booपंचांगem named block.
 */
__cvmx_cmd_queue_all_state_t *__cvmx_cmd_queue_state_ptr;
EXPORT_SYMBOL_GPL(__cvmx_cmd_queue_state_ptr);

/**
 * Initialize the Global queue state poपूर्णांकer.
 *
 * Returns CVMX_CMD_QUEUE_SUCCESS or a failure code
 */
अटल cvmx_cmd_queue_result_t __cvmx_cmd_queue_init_state_ptr(व्योम)
अणु
	अक्षर *alloc_name = "cvmx_cmd_queues";
#अगर defined(CONFIG_CAVIUM_RESERVE32) && CONFIG_CAVIUM_RESERVE32
	बाह्य uपूर्णांक64_t octeon_reserve32_memory;
#पूर्ण_अगर

	अगर (likely(__cvmx_cmd_queue_state_ptr))
		वापस CVMX_CMD_QUEUE_SUCCESS;

#अगर defined(CONFIG_CAVIUM_RESERVE32) && CONFIG_CAVIUM_RESERVE32
	अगर (octeon_reserve32_memory)
		__cvmx_cmd_queue_state_ptr =
		    cvmx_booपंचांगem_alloc_named_range(माप(*__cvmx_cmd_queue_state_ptr),
						   octeon_reserve32_memory,
						   octeon_reserve32_memory +
						   (CONFIG_CAVIUM_RESERVE32 <<
						    20) - 1, 128, alloc_name);
	अन्यथा
#पूर्ण_अगर
		__cvmx_cmd_queue_state_ptr =
		    cvmx_booपंचांगem_alloc_named(माप(*__cvmx_cmd_queue_state_ptr),
					    128,
					    alloc_name);
	अगर (__cvmx_cmd_queue_state_ptr)
		स_रखो(__cvmx_cmd_queue_state_ptr, 0,
		       माप(*__cvmx_cmd_queue_state_ptr));
	अन्यथा अणु
		काष्ठा cvmx_booपंचांगem_named_block_desc *block_desc =
		    cvmx_booपंचांगem_find_named_block(alloc_name);
		अगर (block_desc)
			__cvmx_cmd_queue_state_ptr =
			    cvmx_phys_to_ptr(block_desc->base_addr);
		अन्यथा अणु
			cvmx_dम_लिखो
			    ("ERROR: cvmx_cmd_queue_initialize: Unable to get named block %s.\n",
			     alloc_name);
			वापस CVMX_CMD_QUEUE_NO_MEMORY;
		पूर्ण
	पूर्ण
	वापस CVMX_CMD_QUEUE_SUCCESS;
पूर्ण

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
						  पूर्णांक pool_size)
अणु
	__cvmx_cmd_queue_state_t *qstate;
	cvmx_cmd_queue_result_t result = __cvmx_cmd_queue_init_state_ptr();
	अगर (result != CVMX_CMD_QUEUE_SUCCESS)
		वापस result;

	qstate = __cvmx_cmd_queue_get_state(queue_id);
	अगर (qstate == शून्य)
		वापस CVMX_CMD_QUEUE_INVALID_PARAM;

	/*
	 * We artअगरicially limit max_depth to 1<<20 words. It is an
	 * arbitrary limit.
	 */
	अगर (CVMX_CMD_QUEUE_ENABLE_MAX_DEPTH) अणु
		अगर ((max_depth < 0) || (max_depth > 1 << 20))
			वापस CVMX_CMD_QUEUE_INVALID_PARAM;
	पूर्ण अन्यथा अगर (max_depth != 0)
		वापस CVMX_CMD_QUEUE_INVALID_PARAM;

	अगर ((fpa_pool < 0) || (fpa_pool > 7))
		वापस CVMX_CMD_QUEUE_INVALID_PARAM;
	अगर ((pool_size < 128) || (pool_size > 65536))
		वापस CVMX_CMD_QUEUE_INVALID_PARAM;

	/* See अगर someone अन्यथा has alपढ़ोy initialized the queue */
	अगर (qstate->base_ptr_भाग128) अणु
		अगर (max_depth != (पूर्णांक)qstate->max_depth) अणु
			cvmx_dम_लिखो("ERROR: cvmx_cmd_queue_initialize: "
				"Queue already initialized with different "
				"max_depth (%d).\n",
			     (पूर्णांक)qstate->max_depth);
			वापस CVMX_CMD_QUEUE_INVALID_PARAM;
		पूर्ण
		अगर (fpa_pool != qstate->fpa_pool) अणु
			cvmx_dम_लिखो("ERROR: cvmx_cmd_queue_initialize: "
				"Queue already initialized with different "
				"FPA pool (%u).\n",
			     qstate->fpa_pool);
			वापस CVMX_CMD_QUEUE_INVALID_PARAM;
		पूर्ण
		अगर ((pool_size >> 3) - 1 != qstate->pool_size_m1) अणु
			cvmx_dम_लिखो("ERROR: cvmx_cmd_queue_initialize: "
				"Queue already initialized with different "
				"FPA pool size (%u).\n",
			     (qstate->pool_size_m1 + 1) << 3);
			वापस CVMX_CMD_QUEUE_INVALID_PARAM;
		पूर्ण
		CVMX_SYNCWS;
		वापस CVMX_CMD_QUEUE_ALREADY_SETUP;
	पूर्ण अन्यथा अणु
		जोड़ cvmx_fpa_ctl_status status;
		व्योम *buffer;

		status.u64 = cvmx_पढ़ो_csr(CVMX_FPA_CTL_STATUS);
		अगर (!status.s.enb) अणु
			cvmx_dम_लिखो("ERROR: cvmx_cmd_queue_initialize: "
				     "FPA is not enabled.\n");
			वापस CVMX_CMD_QUEUE_NO_MEMORY;
		पूर्ण
		buffer = cvmx_fpa_alloc(fpa_pool);
		अगर (buffer == शून्य) अणु
			cvmx_dम_लिखो("ERROR: cvmx_cmd_queue_initialize: "
				     "Unable to allocate initial buffer.\n");
			वापस CVMX_CMD_QUEUE_NO_MEMORY;
		पूर्ण

		स_रखो(qstate, 0, माप(*qstate));
		qstate->max_depth = max_depth;
		qstate->fpa_pool = fpa_pool;
		qstate->pool_size_m1 = (pool_size >> 3) - 1;
		qstate->base_ptr_भाग128 = cvmx_ptr_to_phys(buffer) / 128;
		/*
		 * We zeroed the now serving field so we need to also
		 * zero the ticket.
		 */
		__cvmx_cmd_queue_state_ptr->
		    ticket[__cvmx_cmd_queue_get_index(queue_id)] = 0;
		CVMX_SYNCWS;
		वापस CVMX_CMD_QUEUE_SUCCESS;
	पूर्ण
पूर्ण

/**
 * Shutकरोwn a queue a मुक्त it's command buffers to the FPA. The
 * hardware connected to the queue must be stopped beक्रमe this
 * function is called.
 *
 * @queue_id: Queue to shutकरोwn
 *
 * Returns CVMX_CMD_QUEUE_SUCCESS or a failure code
 */
cvmx_cmd_queue_result_t cvmx_cmd_queue_shutकरोwn(cvmx_cmd_queue_id_t queue_id)
अणु
	__cvmx_cmd_queue_state_t *qptr = __cvmx_cmd_queue_get_state(queue_id);
	अगर (qptr == शून्य) अणु
		cvmx_dम_लिखो("ERROR: cvmx_cmd_queue_shutdown: Unable to "
			     "get queue information.\n");
		वापस CVMX_CMD_QUEUE_INVALID_PARAM;
	पूर्ण

	अगर (cvmx_cmd_queue_length(queue_id) > 0) अणु
		cvmx_dम_लिखो("ERROR: cvmx_cmd_queue_shutdown: Queue still "
			     "has data in it.\n");
		वापस CVMX_CMD_QUEUE_FULL;
	पूर्ण

	__cvmx_cmd_queue_lock(queue_id, qptr);
	अगर (qptr->base_ptr_भाग128) अणु
		cvmx_fpa_मुक्त(cvmx_phys_to_ptr
			      ((uपूर्णांक64_t) qptr->base_ptr_भाग128 << 7),
			      qptr->fpa_pool, 0);
		qptr->base_ptr_भाग128 = 0;
	पूर्ण
	__cvmx_cmd_queue_unlock(qptr);

	वापस CVMX_CMD_QUEUE_SUCCESS;
पूर्ण

/**
 * Return the number of command words pending in the queue. This
 * function may be relatively slow क्रम some hardware units.
 *
 * @queue_id: Hardware command queue to query
 *
 * Returns Number of outstanding commands
 */
पूर्णांक cvmx_cmd_queue_length(cvmx_cmd_queue_id_t queue_id)
अणु
	अगर (CVMX_ENABLE_PARAMETER_CHECKING) अणु
		अगर (__cvmx_cmd_queue_get_state(queue_id) == शून्य)
			वापस CVMX_CMD_QUEUE_INVALID_PARAM;
	पूर्ण

	/*
	 * The cast is here so gcc with check that all values in the
	 * cvmx_cmd_queue_id_t क्रमागतeration are here.
	 */
	चयन ((cvmx_cmd_queue_id_t) (queue_id & 0xff0000)) अणु
	हाल CVMX_CMD_QUEUE_PKO_BASE:
		/*
		 * FIXME: Need atomic lock on
		 * CVMX_PKO_REG_READ_IDX. Right now we are normally
		 * called with the queue lock, so that is a SLIGHT
		 * amount of protection.
		 */
		cvmx_ग_लिखो_csr(CVMX_PKO_REG_READ_IDX, queue_id & 0xffff);
		अगर (OCTEON_IS_MODEL(OCTEON_CN3XXX)) अणु
			जोड़ cvmx_pko_mem_debug9 debug9;
			debug9.u64 = cvmx_पढ़ो_csr(CVMX_PKO_MEM_DEBUG9);
			वापस debug9.cn38xx.करोorbell;
		पूर्ण अन्यथा अणु
			जोड़ cvmx_pko_mem_debug8 debug8;
			debug8.u64 = cvmx_पढ़ो_csr(CVMX_PKO_MEM_DEBUG8);
			वापस debug8.cn50xx.करोorbell;
		पूर्ण
	हाल CVMX_CMD_QUEUE_ZIP:
	हाल CVMX_CMD_QUEUE_DFA:
	हाल CVMX_CMD_QUEUE_RAID:
		/* FIXME: Implement other lengths */
		वापस 0;
	हाल CVMX_CMD_QUEUE_DMA_BASE:
		अणु
			जोड़ cvmx_npei_dmax_counts dmax_counts;
			dmax_counts.u64 =
			    cvmx_पढ़ो_csr(CVMX_PEXP_NPEI_DMAX_COUNTS
					  (queue_id & 0x7));
			वापस dmax_counts.s.dbell;
		पूर्ण
	हाल CVMX_CMD_QUEUE_END:
		वापस CVMX_CMD_QUEUE_INVALID_PARAM;
	पूर्ण
	वापस CVMX_CMD_QUEUE_INVALID_PARAM;
पूर्ण

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
व्योम *cvmx_cmd_queue_buffer(cvmx_cmd_queue_id_t queue_id)
अणु
	__cvmx_cmd_queue_state_t *qptr = __cvmx_cmd_queue_get_state(queue_id);
	अगर (qptr && qptr->base_ptr_भाग128)
		वापस cvmx_phys_to_ptr((uपूर्णांक64_t) qptr->base_ptr_भाग128 << 7);
	अन्यथा
		वापस शून्य;
पूर्ण
