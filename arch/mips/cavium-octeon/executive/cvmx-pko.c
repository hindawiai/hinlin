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
 * Support library क्रम the hardware Packet Output unit.
 */

#समावेश <यंत्र/octeon/octeon.h>

#समावेश <यंत्र/octeon/cvmx-config.h>
#समावेश <यंत्र/octeon/cvmx-pko.h>
#समावेश <यंत्र/octeon/cvmx-helper.h>

/**
 * Internal state of packet output
 */

अटल पूर्णांक __cvmx_pko_पूर्णांक(पूर्णांक पूर्णांकerface, पूर्णांक index)
अणु
	चयन (पूर्णांकerface) अणु
	हाल 0:
		वापस index;
	हाल 1:
		वापस 4;
	हाल 2:
		वापस index + 0x08;
	हाल 3:
		वापस index + 0x0c;
	हाल 4:
		वापस index + 0x10;
	हाल 5:
		वापस 0x1c;
	हाल 6:
		वापस 0x1d;
	हाल 7:
		वापस 0x1e;
	हाल 8:
		वापस 0x1f;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल व्योम __cvmx_pko_iport_config(पूर्णांक pko_port)
अणु
	पूर्णांक queue;
	स्थिर पूर्णांक num_queues = 1;
	स्थिर पूर्णांक base_queue = pko_port;
	स्थिर पूर्णांक अटल_priority_end = 1;
	स्थिर पूर्णांक अटल_priority_base = 1;

	क्रम (queue = 0; queue < num_queues; queue++) अणु
		जोड़ cvmx_pko_mem_iqueue_ptrs config;
		cvmx_cmd_queue_result_t cmd_res;
		uपूर्णांक64_t *buf_ptr;

		config.u64		= 0;
		config.s.index		= queue;
		config.s.qid		= base_queue + queue;
		config.s.ipid		= pko_port;
		config.s.tail		= (queue == (num_queues - 1));
		config.s.s_tail		= (queue == अटल_priority_end);
		config.s.अटल_p	= (अटल_priority_base >= 0);
		config.s.अटल_q	= (queue <= अटल_priority_end);
		config.s.qos_mask	= 0xff;

		cmd_res = cvmx_cmd_queue_initialize(
				CVMX_CMD_QUEUE_PKO(base_queue + queue),
				CVMX_PKO_MAX_QUEUE_DEPTH,
				CVMX_FPA_OUTPUT_BUFFER_POOL,
				(CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE -
				 CVMX_PKO_COMMAND_BUFFER_SIZE_ADJUST * 8));

		WARN(cmd_res,
		     "%s: cmd_res=%d pko_port=%d base_queue=%d num_queues=%d queue=%d\n",
			__func__, (पूर्णांक)cmd_res, pko_port, base_queue,
			num_queues, queue);

		buf_ptr = (uपूर्णांक64_t *)cvmx_cmd_queue_buffer(
				CVMX_CMD_QUEUE_PKO(base_queue + queue));
		config.s.buf_ptr = cvmx_ptr_to_phys(buf_ptr) >> 7;
		CVMX_SYNCWS;
		cvmx_ग_लिखो_csr(CVMX_PKO_MEM_IQUEUE_PTRS, config.u64);
	पूर्ण
पूर्ण

अटल व्योम __cvmx_pko_queue_alloc_o68(व्योम)
अणु
	पूर्णांक port;

	क्रम (port = 0; port < 48; port++)
		__cvmx_pko_iport_config(port);
पूर्ण

अटल व्योम __cvmx_pko_port_map_o68(व्योम)
अणु
	पूर्णांक port;
	पूर्णांक पूर्णांकerface, index;
	cvmx_helper_पूर्णांकerface_mode_t mode;
	जोड़ cvmx_pko_mem_iport_ptrs config;

	/*
	 * Initialize every iport with the invalid eid.
	 */
	config.u64 = 0;
	config.s.eid = 31; /* Invalid */
	क्रम (port = 0; port < 128; port++) अणु
		config.s.ipid = port;
		cvmx_ग_लिखो_csr(CVMX_PKO_MEM_IPORT_PTRS, config.u64);
	पूर्ण

	/*
	 * Set up PKO_MEM_IPORT_PTRS
	 */
	क्रम (port = 0; port < 48; port++) अणु
		पूर्णांकerface = cvmx_helper_get_पूर्णांकerface_num(port);
		index = cvmx_helper_get_पूर्णांकerface_index_num(port);
		mode = cvmx_helper_पूर्णांकerface_get_mode(पूर्णांकerface);
		अगर (mode == CVMX_HELPER_INTERFACE_MODE_DISABLED)
			जारी;

		config.s.ipid = port;
		config.s.qos_mask = 0xff;
		config.s.crc = 1;
		config.s.min_pkt = 1;
		config.s.पूर्णांकr = __cvmx_pko_पूर्णांक(पूर्णांकerface, index);
		config.s.eid = config.s.पूर्णांकr;
		config.s.pipe = (mode == CVMX_HELPER_INTERFACE_MODE_LOOP) ?
			index : port;
		cvmx_ग_लिखो_csr(CVMX_PKO_MEM_IPORT_PTRS, config.u64);
	पूर्ण
पूर्ण

अटल व्योम __cvmx_pko_chip_init(व्योम)
अणु
	पूर्णांक i;

	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX)) अणु
		__cvmx_pko_port_map_o68();
		__cvmx_pko_queue_alloc_o68();
		वापस;
	पूर्ण

	/*
	 * Initialize queues
	 */
	क्रम (i = 0; i < CVMX_PKO_MAX_OUTPUT_QUEUES; i++) अणु
		स्थिर uपूर्णांक64_t priority = 8;

		cvmx_pko_config_port(CVMX_PKO_MEM_QUEUE_PTRS_ILLEGAL_PID, i, 1,
				     &priority);
	पूर्ण
पूर्ण

/**
 * Call beक्रमe any other calls to initialize the packet
 * output प्रणाली.  This करोes chip global config, and should only be
 * करोne by one core.
 */

व्योम cvmx_pko_initialize_global(व्योम)
अणु
	जोड़ cvmx_pko_reg_cmd_buf config;

	/*
	 * Set the size of the PKO command buffers to an odd number of
	 * 64bit words. This allows the normal two word send to stay
	 * aligned and never span a command word buffer.
	 */
	config.u64 = 0;
	config.s.pool = CVMX_FPA_OUTPUT_BUFFER_POOL;
	config.s.size = CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE / 8 - 1;

	cvmx_ग_लिखो_csr(CVMX_PKO_REG_CMD_BUF, config.u64);

	/*
	 * Chip-specअगरic setup.
	 */
	__cvmx_pko_chip_init();

	/*
	 * If we aren't using all of the queues optimize PKO's
	 * पूर्णांकernal memory.
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN38XX) || OCTEON_IS_MODEL(OCTEON_CN58XX)
	    || OCTEON_IS_MODEL(OCTEON_CN56XX)
	    || OCTEON_IS_MODEL(OCTEON_CN52XX)) अणु
		पूर्णांक num_पूर्णांकerfaces = cvmx_helper_get_number_of_पूर्णांकerfaces();
		पूर्णांक last_port =
		    cvmx_helper_get_last_ipd_port(num_पूर्णांकerfaces - 1);
		पूर्णांक max_queues =
		    cvmx_pko_get_base_queue(last_port) +
		    cvmx_pko_get_num_queues(last_port);
		अगर (OCTEON_IS_MODEL(OCTEON_CN38XX)) अणु
			अगर (max_queues <= 32)
				cvmx_ग_लिखो_csr(CVMX_PKO_REG_QUEUE_MODE, 2);
			अन्यथा अगर (max_queues <= 64)
				cvmx_ग_लिखो_csr(CVMX_PKO_REG_QUEUE_MODE, 1);
		पूर्ण अन्यथा अणु
			अगर (max_queues <= 64)
				cvmx_ग_लिखो_csr(CVMX_PKO_REG_QUEUE_MODE, 2);
			अन्यथा अगर (max_queues <= 128)
				cvmx_ग_लिखो_csr(CVMX_PKO_REG_QUEUE_MODE, 1);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * This function करोes per-core initialization required by the PKO routines.
 * This must be called on all cores that will करो packet output, and must
 * be called after the FPA has been initialized and filled with pages.
 *
 * Returns 0 on success
 *	   !0 on failure
 */
पूर्णांक cvmx_pko_initialize_local(व्योम)
अणु
	/* Nothing to करो */
	वापस 0;
पूर्ण

/**
 * Enables the packet output hardware. It must alपढ़ोy be
 * configured.
 */
व्योम cvmx_pko_enable(व्योम)
अणु
	जोड़ cvmx_pko_reg_flags flags;

	flags.u64 = cvmx_पढ़ो_csr(CVMX_PKO_REG_FLAGS);
	अगर (flags.s.ena_pko)
		cvmx_dम_लिखो
		    ("Warning: Enabling PKO when PKO already enabled.\n");

	flags.s.ena_dwb = 1;
	flags.s.ena_pko = 1;
	/*
	 * always enable big endian क्रम 3-word command. Does nothing
	 * क्रम 2-word.
	 */
	flags.s.store_be = 1;
	cvmx_ग_लिखो_csr(CVMX_PKO_REG_FLAGS, flags.u64);
पूर्ण

/**
 * Disables the packet output. Does not affect any configuration.
 */
व्योम cvmx_pko_disable(व्योम)
अणु
	जोड़ cvmx_pko_reg_flags pko_reg_flags;
	pko_reg_flags.u64 = cvmx_पढ़ो_csr(CVMX_PKO_REG_FLAGS);
	pko_reg_flags.s.ena_pko = 0;
	cvmx_ग_लिखो_csr(CVMX_PKO_REG_FLAGS, pko_reg_flags.u64);
पूर्ण
EXPORT_SYMBOL_GPL(cvmx_pko_disable);

/**
 * Reset the packet output.
 */
अटल व्योम __cvmx_pko_reset(व्योम)
अणु
	जोड़ cvmx_pko_reg_flags pko_reg_flags;
	pko_reg_flags.u64 = cvmx_पढ़ो_csr(CVMX_PKO_REG_FLAGS);
	pko_reg_flags.s.reset = 1;
	cvmx_ग_लिखो_csr(CVMX_PKO_REG_FLAGS, pko_reg_flags.u64);
पूर्ण

/**
 * Shutकरोwn and मुक्त resources required by packet output.
 */
व्योम cvmx_pko_shutकरोwn(व्योम)
अणु
	जोड़ cvmx_pko_mem_queue_ptrs config;
	पूर्णांक queue;

	cvmx_pko_disable();

	क्रम (queue = 0; queue < CVMX_PKO_MAX_OUTPUT_QUEUES; queue++) अणु
		config.u64 = 0;
		config.s.tail = 1;
		config.s.index = 0;
		config.s.port = CVMX_PKO_MEM_QUEUE_PTRS_ILLEGAL_PID;
		config.s.queue = queue & 0x7f;
		config.s.qos_mask = 0;
		config.s.buf_ptr = 0;
		अगर (!OCTEON_IS_MODEL(OCTEON_CN3XXX)) अणु
			जोड़ cvmx_pko_reg_queue_ptrs1 config1;
			config1.u64 = 0;
			config1.s.qid7 = queue >> 7;
			cvmx_ग_लिखो_csr(CVMX_PKO_REG_QUEUE_PTRS1, config1.u64);
		पूर्ण
		cvmx_ग_लिखो_csr(CVMX_PKO_MEM_QUEUE_PTRS, config.u64);
		cvmx_cmd_queue_shutकरोwn(CVMX_CMD_QUEUE_PKO(queue));
	पूर्ण
	__cvmx_pko_reset();
पूर्ण
EXPORT_SYMBOL_GPL(cvmx_pko_shutकरोwn);

/**
 * Configure a output port and the associated queues क्रम use.
 *
 * @port:	Port to configure.
 * @base_queue: First queue number to associate with this port.
 * @num_queues: Number of queues to associate with this port
 * @priority:	Array of priority levels क्रम each queue. Values are
 *		     allowed to be 0-8. A value of 8 get 8 बार the traffic
 *		     of a value of 1.  A value of 0 indicates that no rounds
 *		     will be participated in. These priorities can be changed
 *		     on the fly जबतक the pko is enabled. A priority of 9
 *		     indicates that अटल priority should be used.  If अटल
 *		     priority is used all queues with अटल priority must be
 *		     contiguous starting at the base_queue, and lower numbered
 *		     queues have higher priority than higher numbered queues.
 *		     There must be num_queues elements in the array.
 */
cvmx_pko_status_t cvmx_pko_config_port(uपूर्णांक64_t port, uपूर्णांक64_t base_queue,
				       uपूर्णांक64_t num_queues,
				       स्थिर uपूर्णांक64_t priority[])
अणु
	cvmx_pko_status_t result_code;
	uपूर्णांक64_t queue;
	जोड़ cvmx_pko_mem_queue_ptrs config;
	जोड़ cvmx_pko_reg_queue_ptrs1 config1;
	पूर्णांक अटल_priority_base = -1;
	पूर्णांक अटल_priority_end = -1;

	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX))
		वापस CVMX_PKO_SUCCESS;

	अगर ((port >= CVMX_PKO_NUM_OUTPUT_PORTS)
	    && (port != CVMX_PKO_MEM_QUEUE_PTRS_ILLEGAL_PID)) अणु
		cvmx_dम_लिखो("ERROR: cvmx_pko_config_port: Invalid port %llu\n",
			     (अचिन्हित दीर्घ दीर्घ)port);
		वापस CVMX_PKO_INVALID_PORT;
	पूर्ण

	अगर (base_queue + num_queues > CVMX_PKO_MAX_OUTPUT_QUEUES) अणु
		cvmx_dम_लिखो
		    ("ERROR: cvmx_pko_config_port: Invalid queue range %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)(base_queue + num_queues));
		वापस CVMX_PKO_INVALID_QUEUE;
	पूर्ण

	अगर (port != CVMX_PKO_MEM_QUEUE_PTRS_ILLEGAL_PID) अणु
		/*
		 * Validate the अटल queue priority setup and set
		 * अटल_priority_base and अटल_priority_end
		 * accordingly.
		 */
		क्रम (queue = 0; queue < num_queues; queue++) अणु
			/* Find first queue of अटल priority */
			अगर (अटल_priority_base == -1
			    && priority[queue] ==
			    CVMX_PKO_QUEUE_STATIC_PRIORITY)
				अटल_priority_base = queue;
			/* Find last queue of अटल priority */
			अगर (अटल_priority_base != -1
			    && अटल_priority_end == -1
			    && priority[queue] != CVMX_PKO_QUEUE_STATIC_PRIORITY
			    && queue)
				अटल_priority_end = queue - 1;
			अन्यथा अगर (अटल_priority_base != -1
				 && अटल_priority_end == -1
				 && queue == num_queues - 1)
				/* all queues are अटल priority */
				अटल_priority_end = queue;
			/*
			 * Check to make sure all अटल priority
			 * queues are contiguous.  Also catches some
			 * हालs of अटल priorites not starting at
			 * queue 0.
			 */
			अगर (अटल_priority_end != -1
			    && (पूर्णांक)queue > अटल_priority_end
			    && priority[queue] ==
			    CVMX_PKO_QUEUE_STATIC_PRIORITY) अणु
				cvmx_dम_लिखो("ERROR: cvmx_pko_config_port: "
					     "Static priority queues aren't "
					     "contiguous or don't start at "
					     "base queue. q: %d, eq: %d\n",
					(पूर्णांक)queue, अटल_priority_end);
				वापस CVMX_PKO_INVALID_PRIORITY;
			पूर्ण
		पूर्ण
		अगर (अटल_priority_base > 0) अणु
			cvmx_dम_लिखो("ERROR: cvmx_pko_config_port: Static "
				     "priority queues don't start at base "
				     "queue. sq: %d\n",
				अटल_priority_base);
			वापस CVMX_PKO_INVALID_PRIORITY;
		पूर्ण
#अगर 0
		cvmx_dम_लिखो("Port %d: Static priority queue base: %d, "
			     "end: %d\n", port,
			अटल_priority_base, अटल_priority_end);
#पूर्ण_अगर
	पूर्ण
	/*
	 * At this poपूर्णांक, अटल_priority_base and अटल_priority_end
	 * are either both -1, or are valid start/end queue
	 * numbers.
	 */

	result_code = CVMX_PKO_SUCCESS;

#अगर_घोषित PKO_DEBUG
	cvmx_dम_लिखो("num queues: %d (%lld,%lld)\n", num_queues,
		     CVMX_PKO_QUEUES_PER_PORT_INTERFACE0,
		     CVMX_PKO_QUEUES_PER_PORT_INTERFACE1);
#पूर्ण_अगर

	क्रम (queue = 0; queue < num_queues; queue++) अणु
		uपूर्णांक64_t *buf_ptr = शून्य;

		config1.u64 = 0;
		config1.s.idx3 = queue >> 3;
		config1.s.qid7 = (base_queue + queue) >> 7;

		config.u64 = 0;
		config.s.tail = queue == (num_queues - 1);
		config.s.index = queue;
		config.s.port = port;
		config.s.queue = base_queue + queue;

		अगर (!cvmx_octeon_is_pass1()) अणु
			config.s.अटल_p = अटल_priority_base >= 0;
			config.s.अटल_q = (पूर्णांक)queue <= अटल_priority_end;
			config.s.s_tail = (पूर्णांक)queue == अटल_priority_end;
		पूर्ण
		/*
		 * Convert the priority पूर्णांकo an enable bit field. Try
		 * to space the bits out evenly so the packet करोn't
		 * get grouped up
		 */
		चयन ((पूर्णांक)priority[queue]) अणु
		हाल 0:
			config.s.qos_mask = 0x00;
			अवरोध;
		हाल 1:
			config.s.qos_mask = 0x01;
			अवरोध;
		हाल 2:
			config.s.qos_mask = 0x11;
			अवरोध;
		हाल 3:
			config.s.qos_mask = 0x49;
			अवरोध;
		हाल 4:
			config.s.qos_mask = 0x55;
			अवरोध;
		हाल 5:
			config.s.qos_mask = 0x57;
			अवरोध;
		हाल 6:
			config.s.qos_mask = 0x77;
			अवरोध;
		हाल 7:
			config.s.qos_mask = 0x7f;
			अवरोध;
		हाल 8:
			config.s.qos_mask = 0xff;
			अवरोध;
		हाल CVMX_PKO_QUEUE_STATIC_PRIORITY:
			अगर (!cvmx_octeon_is_pass1()) अणु
				config.s.qos_mask = 0xff;
				अवरोध;
			पूर्ण
			fallthrough;	/* to the error हाल, when Pass 1 */
		शेष:
			cvmx_dम_लिखो("ERROR: cvmx_pko_config_port: Invalid "
				     "priority %llu\n",
				(अचिन्हित दीर्घ दीर्घ)priority[queue]);
			config.s.qos_mask = 0xff;
			result_code = CVMX_PKO_INVALID_PRIORITY;
			अवरोध;
		पूर्ण

		अगर (port != CVMX_PKO_MEM_QUEUE_PTRS_ILLEGAL_PID) अणु
			cvmx_cmd_queue_result_t cmd_res =
			    cvmx_cmd_queue_initialize(CVMX_CMD_QUEUE_PKO
						      (base_queue + queue),
						      CVMX_PKO_MAX_QUEUE_DEPTH,
						      CVMX_FPA_OUTPUT_BUFFER_POOL,
						      CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE
						      -
						      CVMX_PKO_COMMAND_BUFFER_SIZE_ADJUST
						      * 8);
			अगर (cmd_res != CVMX_CMD_QUEUE_SUCCESS) अणु
				चयन (cmd_res) अणु
				हाल CVMX_CMD_QUEUE_NO_MEMORY:
					cvmx_dम_लिखो("ERROR: "
						     "cvmx_pko_config_port: "
						     "Unable to allocate "
						     "output buffer.\n");
					वापस CVMX_PKO_NO_MEMORY;
				हाल CVMX_CMD_QUEUE_ALREADY_SETUP:
					cvmx_dम_लिखो
					    ("ERROR: cvmx_pko_config_port: Port already setup.\n");
					वापस CVMX_PKO_PORT_ALREADY_SETUP;
				हाल CVMX_CMD_QUEUE_INVALID_PARAM:
				शेष:
					cvmx_dम_लिखो
					    ("ERROR: cvmx_pko_config_port: Command queue initialization failed.\n");
					वापस CVMX_PKO_CMD_QUEUE_INIT_ERROR;
				पूर्ण
			पूर्ण

			buf_ptr =
			    (uपूर्णांक64_t *)
			    cvmx_cmd_queue_buffer(CVMX_CMD_QUEUE_PKO
						  (base_queue + queue));
			config.s.buf_ptr = cvmx_ptr_to_phys(buf_ptr);
		पूर्ण अन्यथा
			config.s.buf_ptr = 0;

		CVMX_SYNCWS;

		अगर (!OCTEON_IS_MODEL(OCTEON_CN3XXX))
			cvmx_ग_लिखो_csr(CVMX_PKO_REG_QUEUE_PTRS1, config1.u64);
		cvmx_ग_लिखो_csr(CVMX_PKO_MEM_QUEUE_PTRS, config.u64);
	पूर्ण

	वापस result_code;
पूर्ण

#अगर_घोषित PKO_DEBUG
/**
 * Show map of ports -> queues क्रम dअगरferent cores.
 */
व्योम cvmx_pko_show_queue_map()
अणु
	पूर्णांक core, port;
	पूर्णांक pko_output_ports = 36;

	cvmx_dम_लिखो("port");
	क्रम (port = 0; port < pko_output_ports; port++)
		cvmx_dम_लिखो("%3d ", port);
	cvmx_dम_लिखो("\n");

	क्रम (core = 0; core < CVMX_MAX_CORES; core++) अणु
		cvmx_dम_लिखो("\n%2d: ", core);
		क्रम (port = 0; port < pko_output_ports; port++) अणु
			cvmx_dम_लिखो("%3d ",
				     cvmx_pko_get_base_queue_per_core(port,
								      core));
		पूर्ण
	पूर्ण
	cvmx_dम_लिखो("\n");
पूर्ण
#पूर्ण_अगर

/**
 * Rate limit a PKO port to a max packets/sec. This function is only
 * supported on CN51XX and higher, excluding CN58XX.
 *
 * @port:      Port to rate limit
 * @packets_s: Maximum packet/sec
 * @burst:     Maximum number of packets to burst in a row beक्रमe rate
 *		    limiting cuts in.
 *
 * Returns Zero on success, negative on failure
 */
पूर्णांक cvmx_pko_rate_limit_packets(पूर्णांक port, पूर्णांक packets_s, पूर्णांक burst)
अणु
	जोड़ cvmx_pko_mem_port_rate0 pko_mem_port_rate0;
	जोड़ cvmx_pko_mem_port_rate1 pko_mem_port_rate1;

	pko_mem_port_rate0.u64 = 0;
	pko_mem_port_rate0.s.pid = port;
	pko_mem_port_rate0.s.rate_pkt =
	    cvmx_sysinfo_get()->cpu_घड़ी_hz / packets_s / 16;
	/* No cost per word since we are limited by packets/sec, not bits/sec */
	pko_mem_port_rate0.s.rate_word = 0;

	pko_mem_port_rate1.u64 = 0;
	pko_mem_port_rate1.s.pid = port;
	pko_mem_port_rate1.s.rate_lim =
	    ((uपूर्णांक64_t) pko_mem_port_rate0.s.rate_pkt * burst) >> 8;

	cvmx_ग_लिखो_csr(CVMX_PKO_MEM_PORT_RATE0, pko_mem_port_rate0.u64);
	cvmx_ग_लिखो_csr(CVMX_PKO_MEM_PORT_RATE1, pko_mem_port_rate1.u64);
	वापस 0;
पूर्ण

/**
 * Rate limit a PKO port to a max bits/sec. This function is only
 * supported on CN51XX and higher, excluding CN58XX.
 *
 * @port:   Port to rate limit
 * @bits_s: PKO rate limit in bits/sec
 * @burst:  Maximum number of bits to burst beक्रमe rate
 *		 limiting cuts in.
 *
 * Returns Zero on success, negative on failure
 */
पूर्णांक cvmx_pko_rate_limit_bits(पूर्णांक port, uपूर्णांक64_t bits_s, पूर्णांक burst)
अणु
	जोड़ cvmx_pko_mem_port_rate0 pko_mem_port_rate0;
	जोड़ cvmx_pko_mem_port_rate1 pko_mem_port_rate1;
	uपूर्णांक64_t घड़ी_rate = cvmx_sysinfo_get()->cpu_घड़ी_hz;
	uपूर्णांक64_t tokens_per_bit = घड़ी_rate * 16 / bits_s;

	pko_mem_port_rate0.u64 = 0;
	pko_mem_port_rate0.s.pid = port;
	/*
	 * Each packet has a 12 bytes of पूर्णांकerframe gap, an 8 byte
	 * preamble, and a 4 byte CRC. These are not included in the
	 * per word count. Multiply by 8 to covert to bits and भागide
	 * by 256 क्रम limit granularity.
	 */
	pko_mem_port_rate0.s.rate_pkt = (12 + 8 + 4) * 8 * tokens_per_bit / 256;
	/* Each 8 byte word has 64bits */
	pko_mem_port_rate0.s.rate_word = 64 * tokens_per_bit;

	pko_mem_port_rate1.u64 = 0;
	pko_mem_port_rate1.s.pid = port;
	pko_mem_port_rate1.s.rate_lim = tokens_per_bit * burst / 256;

	cvmx_ग_लिखो_csr(CVMX_PKO_MEM_PORT_RATE0, pko_mem_port_rate0.u64);
	cvmx_ग_लिखो_csr(CVMX_PKO_MEM_PORT_RATE1, pko_mem_port_rate1.u64);
	वापस 0;
पूर्ण
