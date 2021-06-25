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

/**
 *
 * Interface to the hardware Packet Output unit.
 *
 * Starting with SDK 1.7.0, the PKO output functions now support
 * two types of locking. CVMX_PKO_LOCK_ATOMIC_TAG जारीs to
 * function similarly to previous SDKs by using POW atomic tags
 * to preserve ordering and exclusivity. As a new option, you
 * can now pass CVMX_PKO_LOCK_CMD_QUEUE which uses a ll/sc
 * memory based locking instead. This locking has the advantage
 * of not affecting the tag state but करोesn't preserve packet
 * ordering. CVMX_PKO_LOCK_CMD_QUEUE is appropriate in most
 * generic code जबतक CVMX_PKO_LOCK_CMD_QUEUE should be used
 * with hand tuned fast path code.
 *
 * Some of other SDK dअगरferences visible to the command queuing:
 * - PKO indexes are no दीर्घer stored in the FAU. A large
 *   percentage of the FAU रेजिस्टर block used to be tied up
 *   मुख्यtaining PKO queue poपूर्णांकers. These are now stored in a
 *   global named block.
 * - The PKO <b>use_locking</b> parameter can now have a global
 *   effect. Since all application use the same named block,
 *   queue locking correctly applies across all operating
 *   प्रणालीs when using CVMX_PKO_LOCK_CMD_QUEUE.
 * - PKO 3 word commands are now supported. Use
 *   cvmx_pko_send_packet_finish3().
 *
 */

#अगर_अघोषित __CVMX_PKO_H__
#घोषणा __CVMX_PKO_H__

#समावेश <यंत्र/octeon/cvmx-fpa.h>
#समावेश <यंत्र/octeon/cvmx-घात.h>
#समावेश <यंत्र/octeon/cvmx-cmd-queue.h>
#समावेश <यंत्र/octeon/cvmx-pko-defs.h>

/* Adjust the command buffer size by 1 word so that in the हाल of using only
 * two word PKO commands no command words stradle buffers.  The useful values
 * क्रम this are 0 and 1. */
#घोषणा CVMX_PKO_COMMAND_BUFFER_SIZE_ADJUST (1)

#घोषणा CVMX_PKO_MAX_OUTPUT_QUEUES_STATIC 256
#घोषणा CVMX_PKO_MAX_OUTPUT_QUEUES	((OCTEON_IS_MODEL(OCTEON_CN31XX) || \
	OCTEON_IS_MODEL(OCTEON_CN3010) || OCTEON_IS_MODEL(OCTEON_CN3005) || \
	OCTEON_IS_MODEL(OCTEON_CN50XX)) ? 32 : \
		(OCTEON_IS_MODEL(OCTEON_CN58XX) || \
		OCTEON_IS_MODEL(OCTEON_CN56XX)) ? 256 : 128)
#घोषणा CVMX_PKO_NUM_OUTPUT_PORTS	40
/* use this क्रम queues that are not used */
#घोषणा CVMX_PKO_MEM_QUEUE_PTRS_ILLEGAL_PID 63
#घोषणा CVMX_PKO_QUEUE_STATIC_PRIORITY	9
#घोषणा CVMX_PKO_ILLEGAL_QUEUE	0xFFFF
#घोषणा CVMX_PKO_MAX_QUEUE_DEPTH 0

प्रकार क्रमागत अणु
	CVMX_PKO_SUCCESS,
	CVMX_PKO_INVALID_PORT,
	CVMX_PKO_INVALID_QUEUE,
	CVMX_PKO_INVALID_PRIORITY,
	CVMX_PKO_NO_MEMORY,
	CVMX_PKO_PORT_ALREADY_SETUP,
	CVMX_PKO_CMD_QUEUE_INIT_ERROR
पूर्ण cvmx_pko_status_t;

/**
 * This क्रमागतeration represents the dअगरfernet locking modes supported by PKO.
 */
प्रकार क्रमागत अणु
	/*
	 * PKO करोesn't करो any locking. It is the responsibility of the
	 * application to make sure that no other core is accessing
	 * the same queue at the same समय
	 */
	CVMX_PKO_LOCK_NONE = 0,
	/*
	 * PKO perक्रमms an atomic tagचयन to insure exclusive access
	 * to the output queue. This will मुख्यtain packet ordering on
	 * output.
	 */
	CVMX_PKO_LOCK_ATOMIC_TAG = 1,
	/*
	 * PKO uses the common command queue locks to insure exclusive
	 * access to the output queue. This is a memory based
	 * ll/sc. This is the most portable locking mechanism.
	 */
	CVMX_PKO_LOCK_CMD_QUEUE = 2,
पूर्ण cvmx_pko_lock_t;

प्रकार काष्ठा अणु
	uपूर्णांक32_t packets;
	uपूर्णांक64_t octets;
	uपूर्णांक64_t करोorbell;
पूर्ण cvmx_pko_port_status_t;

/**
 * This काष्ठाure defines the address to use on a packet enqueue
 */
प्रकार जोड़ अणु
	uपूर्णांक64_t u64;
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/* Must CVMX_IO_SEG */
		uपूर्णांक64_t mem_space:2;
		/* Must be zero */
		uपूर्णांक64_t reserved:13;
		/* Must be one */
		uपूर्णांक64_t is_io:1;
		/* The ID of the device on the non-coherent bus */
		uपूर्णांक64_t did:8;
		/* Must be zero */
		uपूर्णांक64_t reserved2:4;
		/* Must be zero */
		uपूर्णांक64_t reserved3:18;
		/*
		 * The hardware likes to have the output port in
		 * addition to the output queue,
		 */
		uपूर्णांक64_t port:6;
		/*
		 * The output queue to send the packet to (0-127 are
		 * legal)
		 */
		uपूर्णांक64_t queue:9;
		/* Must be zero */
		uपूर्णांक64_t reserved4:3;
#अन्यथा
	        uपूर्णांक64_t reserved4:3;
	        uपूर्णांक64_t queue:9;
	        uपूर्णांक64_t port:9;
	        uपूर्णांक64_t reserved3:15;
	        uपूर्णांक64_t reserved2:4;
	        uपूर्णांक64_t did:8;
	        uपूर्णांक64_t is_io:1;
	        uपूर्णांक64_t reserved:13;
	        uपूर्णांक64_t mem_space:2;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण cvmx_pko_करोorbell_address_t;

/**
 * Structure of the first packet output command word.
 */
जोड़ cvmx_pko_command_word0 अणु
	uपूर्णांक64_t u64;
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/*
		 * The size of the reg1 operation - could be 8, 16,
		 * 32, or 64 bits.
		 */
		uपूर्णांक64_t size1:2;
		/*
		 * The size of the reg0 operation - could be 8, 16,
		 * 32, or 64 bits.
		 */
		uपूर्णांक64_t size0:2;
		/*
		 * If set, subtract 1, अगर clear, subtract packet
		 * size.
		 */
		uपूर्णांक64_t subone1:1;
		/*
		 * The रेजिस्टर, subtract will be करोne अगर reg1 is
		 * non-zero.
		 */
		uपूर्णांक64_t reg1:11;
		/* If set, subtract 1, अगर clear, subtract packet size */
		uपूर्णांक64_t subone0:1;
		/* The रेजिस्टर, subtract will be करोne अगर reg0 is non-zero */
		uपूर्णांक64_t reg0:11;
		/*
		 * When set, पूर्णांकerpret segment poपूर्णांकer and segment
		 * bytes in little endian order.
		 */
		uपूर्णांक64_t le:1;
		/*
		 * When set, packet data not allocated in L2 cache by
		 * PKO.
		 */
		uपूर्णांक64_t n2:1;
		/*
		 * If set and rsp is set, word3 contains a poपूर्णांकer to
		 * a work queue entry.
		 */
		uपूर्णांक64_t wqp:1;
		/* If set, the hardware will send a response when करोne */
		uपूर्णांक64_t rsp:1;
		/*
		 * If set, the supplied pkt_ptr is really a poपूर्णांकer to
		 * a list of pkt_ptr's.
		 */
		uपूर्णांक64_t gather:1;
		/*
		 * If ipoffp1 is non zero, (ipoffp1-1) is the number
		 * of bytes to IP header, and the hardware will
		 * calculate and insert the UDP/TCP checksum.
		 */
		uपूर्णांक64_t ipoffp1:7;
		/*
		 * If set, ignore the I bit (क्रमce to zero) from all
		 * poपूर्णांकer काष्ठाures.
		 */
		uपूर्णांक64_t ignore_i:1;
		/*
		 * If clear, the hardware will attempt to मुक्त the
		 * buffers containing the packet.
		 */
		uपूर्णांक64_t करोntमुक्त:1;
		/*
		 * The total number of segs in the packet, अगर gather
		 * set, also gather list length.
		 */
		uपूर्णांक64_t segs:6;
		/* Including L2, but no trailing CRC */
		uपूर्णांक64_t total_bytes:16;
#अन्यथा
	        uपूर्णांक64_t total_bytes:16;
	        uपूर्णांक64_t segs:6;
	        uपूर्णांक64_t करोntमुक्त:1;
	        uपूर्णांक64_t ignore_i:1;
	        uपूर्णांक64_t ipoffp1:7;
	        uपूर्णांक64_t gather:1;
	        uपूर्णांक64_t rsp:1;
	        uपूर्णांक64_t wqp:1;
	        uपूर्णांक64_t n2:1;
	        uपूर्णांक64_t le:1;
	        uपूर्णांक64_t reg0:11;
	        uपूर्णांक64_t subone0:1;
	        uपूर्णांक64_t reg1:11;
	        uपूर्णांक64_t subone1:1;
	        uपूर्णांक64_t size0:2;
	        uपूर्णांक64_t size1:2;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/* CSR प्रकारs have been moved to cvmx-csr-*.h */

/**
 * Definition of पूर्णांकernal state क्रम Packet output processing
 */
प्रकार काष्ठा अणु
	/* ptr to start of buffer, offset kept in FAU reg */
	uपूर्णांक64_t *start_ptr;
पूर्ण cvmx_pko_state_elem_t;

/**
 * Call beक्रमe any other calls to initialize the packet
 * output प्रणाली.
 */
बाह्य व्योम cvmx_pko_initialize_global(व्योम);
बाह्य पूर्णांक cvmx_pko_initialize_local(व्योम);

/**
 * Enables the packet output hardware. It must alपढ़ोy be
 * configured.
 */
बाह्य व्योम cvmx_pko_enable(व्योम);

/**
 * Disables the packet output. Does not affect any configuration.
 */
बाह्य व्योम cvmx_pko_disable(व्योम);

/**
 * Shutकरोwn and मुक्त resources required by packet output.
 */

बाह्य व्योम cvmx_pko_shutकरोwn(व्योम);

/**
 * Configure a output port and the associated queues क्रम use.
 *
 * @port:	Port to configure.
 * @base_queue: First queue number to associate with this port.
 * @num_queues: Number of queues t oassociate with this port
 * @priority:	Array of priority levels क्रम each queue. Values are
 *		     allowed to be 1-8. A value of 8 get 8 बार the traffic
 *		     of a value of 1. There must be num_queues elements in the
 *		     array.
 */
बाह्य cvmx_pko_status_t cvmx_pko_config_port(uपूर्णांक64_t port,
					      uपूर्णांक64_t base_queue,
					      uपूर्णांक64_t num_queues,
					      स्थिर uपूर्णांक64_t priority[]);

/**
 * Ring the packet output करोorbell. This tells the packet
 * output hardware that "len" command words have been added
 * to its pending list.	 This command includes the required
 * CVMX_SYNCWS beक्रमe the करोorbell ring.
 *
 * @port:   Port the packet is क्रम
 * @queue:  Queue the packet is क्रम
 * @len:    Length of the command in 64 bit words
 */
अटल अंतरभूत व्योम cvmx_pko_करोorbell(uपूर्णांक64_t port, uपूर्णांक64_t queue,
				     uपूर्णांक64_t len)
अणु
	cvmx_pko_करोorbell_address_t ptr;

	ptr.u64 = 0;
	ptr.s.mem_space = CVMX_IO_SEG;
	ptr.s.did = CVMX_OCT_DID_PKT_SEND;
	ptr.s.is_io = 1;
	ptr.s.port = port;
	ptr.s.queue = queue;
	/*
	 * Need to make sure output queue data is in DRAM beक्रमe
	 * करोorbell ग_लिखो.
	 */
	CVMX_SYNCWS;
	cvmx_ग_लिखो_io(ptr.u64, len);
पूर्ण

/**
 * Prepare to send a packet.  This may initiate a tag चयन to
 * get exclusive access to the output queue काष्ठाure, and
 * perक्रमms other prep work क्रम the packet send operation.
 *
 * cvmx_pko_send_packet_finish() MUST be called after this function is called,
 * and must be called with the same port/queue/use_locking arguments.
 *
 * The use_locking parameter allows the caller to use three
 * possible locking modes.
 * - CVMX_PKO_LOCK_NONE
 *	- PKO करोesn't करो any locking. It is the responsibility
 *	    of the application to make sure that no other core
 *	    is accessing the same queue at the same समय.
 * - CVMX_PKO_LOCK_ATOMIC_TAG
 *	- PKO perक्रमms an atomic tagचयन to insure exclusive
 *	    access to the output queue. This will मुख्यtain
 *	    packet ordering on output.
 * - CVMX_PKO_LOCK_CMD_QUEUE
 *	- PKO uses the common command queue locks to insure
 *	    exclusive access to the output queue. This is a
 *	    memory based ll/sc. This is the most portable
 *	    locking mechanism.
 *
 * NOTE: If atomic locking is used, the POW entry CANNOT be
 * descheduled, as it करोes not contain a valid WQE poपूर्णांकer.
 *
 * @port:   Port to send it on
 * @queue:  Queue to use
 * @use_locking: CVMX_PKO_LOCK_NONE, CVMX_PKO_LOCK_ATOMIC_TAG, or
 *		 CVMX_PKO_LOCK_CMD_QUEUE
 */

अटल अंतरभूत व्योम cvmx_pko_send_packet_prepare(uपूर्णांक64_t port, uपूर्णांक64_t queue,
						cvmx_pko_lock_t use_locking)
अणु
	अगर (use_locking == CVMX_PKO_LOCK_ATOMIC_TAG) अणु
		/*
		 * Must करो a full चयन here to handle all हालs.  We
		 * use a fake WQE poपूर्णांकer, as the POW करोes not access
		 * this memory.	 The WQE poपूर्णांकer and group are only
		 * used अगर this work is descheduled, which is not
		 * supported by the
		 * cvmx_pko_send_packet_prepare/cvmx_pko_send_packet_finish
		 * combination.	 Note that this is a special हाल in
		 * which these fake values can be used - this is not a
		 * general technique.
		 */
		uपूर्णांक32_t tag =
		    CVMX_TAG_SW_BITS_INTERNAL << CVMX_TAG_SW_SHIFT |
		    CVMX_TAG_SUBGROUP_PKO << CVMX_TAG_SUBGROUP_SHIFT |
		    (CVMX_TAG_SUBGROUP_MASK & queue);
		cvmx_घात_tag_sw_full((काष्ठा cvmx_wqe *) cvmx_phys_to_ptr(0x80), tag,
				     CVMX_POW_TAG_TYPE_ATOMIC, 0);
	पूर्ण
पूर्ण

/**
 * Complete packet output. cvmx_pko_send_packet_prepare() must be
 * called exactly once beक्रमe this, and the same parameters must be
 * passed to both cvmx_pko_send_packet_prepare() and
 * cvmx_pko_send_packet_finish().
 *
 * @port:   Port to send it on
 * @queue:  Queue to use
 * @pko_command:
 *		 PKO HW command word
 * @packet: Packet to send
 * @use_locking: CVMX_PKO_LOCK_NONE, CVMX_PKO_LOCK_ATOMIC_TAG, or
 *		 CVMX_PKO_LOCK_CMD_QUEUE
 *
 * Returns: CVMX_PKO_SUCCESS on success, or error code on
 * failure of output
 */
अटल अंतरभूत cvmx_pko_status_t cvmx_pko_send_packet_finish(
	uपूर्णांक64_t port,
	uपूर्णांक64_t queue,
	जोड़ cvmx_pko_command_word0 pko_command,
	जोड़ cvmx_buf_ptr packet,
	cvmx_pko_lock_t use_locking)
अणु
	cvmx_cmd_queue_result_t result;
	अगर (use_locking == CVMX_PKO_LOCK_ATOMIC_TAG)
		cvmx_घात_tag_sw_रुको();
	result = cvmx_cmd_queue_ग_लिखो2(CVMX_CMD_QUEUE_PKO(queue),
				       (use_locking == CVMX_PKO_LOCK_CMD_QUEUE),
				       pko_command.u64, packet.u64);
	अगर (likely(result == CVMX_CMD_QUEUE_SUCCESS)) अणु
		cvmx_pko_करोorbell(port, queue, 2);
		वापस CVMX_PKO_SUCCESS;
	पूर्ण अन्यथा अगर ((result == CVMX_CMD_QUEUE_NO_MEMORY)
		   || (result == CVMX_CMD_QUEUE_FULL)) अणु
		वापस CVMX_PKO_NO_MEMORY;
	पूर्ण अन्यथा अणु
		वापस CVMX_PKO_INVALID_QUEUE;
	पूर्ण
पूर्ण

/**
 * Complete packet output. cvmx_pko_send_packet_prepare() must be
 * called exactly once beक्रमe this, and the same parameters must be
 * passed to both cvmx_pko_send_packet_prepare() and
 * cvmx_pko_send_packet_finish().
 *
 * @port:   Port to send it on
 * @queue:  Queue to use
 * @pko_command:
 *		 PKO HW command word
 * @packet: Packet to send
 * @addr: Plysical address of a work queue entry or physical address
 *	  to zero on complete.
 * @use_locking: CVMX_PKO_LOCK_NONE, CVMX_PKO_LOCK_ATOMIC_TAG, or
 *		 CVMX_PKO_LOCK_CMD_QUEUE
 *
 * Returns: CVMX_PKO_SUCCESS on success, or error code on
 * failure of output
 */
अटल अंतरभूत cvmx_pko_status_t cvmx_pko_send_packet_finish3(
	uपूर्णांक64_t port,
	uपूर्णांक64_t queue,
	जोड़ cvmx_pko_command_word0 pko_command,
	जोड़ cvmx_buf_ptr packet,
	uपूर्णांक64_t addr,
	cvmx_pko_lock_t use_locking)
अणु
	cvmx_cmd_queue_result_t result;
	अगर (use_locking == CVMX_PKO_LOCK_ATOMIC_TAG)
		cvmx_घात_tag_sw_रुको();
	result = cvmx_cmd_queue_ग_लिखो3(CVMX_CMD_QUEUE_PKO(queue),
				       (use_locking == CVMX_PKO_LOCK_CMD_QUEUE),
				       pko_command.u64, packet.u64, addr);
	अगर (likely(result == CVMX_CMD_QUEUE_SUCCESS)) अणु
		cvmx_pko_करोorbell(port, queue, 3);
		वापस CVMX_PKO_SUCCESS;
	पूर्ण अन्यथा अगर ((result == CVMX_CMD_QUEUE_NO_MEMORY)
		   || (result == CVMX_CMD_QUEUE_FULL)) अणु
		वापस CVMX_PKO_NO_MEMORY;
	पूर्ण अन्यथा अणु
		वापस CVMX_PKO_INVALID_QUEUE;
	पूर्ण
पूर्ण

/**
 * Return the pko output queue associated with a port and a specअगरic core.
 * In normal mode (PKO lockless operation is disabled), the value वापसed
 * is the base queue.
 *
 * @port:   Port number
 * @core:   Core to get queue क्रम
 *
 * Returns Core-specअगरic output queue
 */
अटल अंतरभूत पूर्णांक cvmx_pko_get_base_queue_per_core(पूर्णांक port, पूर्णांक core)
अणु
#अगर_अघोषित CVMX_HELPER_PKO_MAX_PORTS_INTERFACE0
#घोषणा CVMX_HELPER_PKO_MAX_PORTS_INTERFACE0 16
#पूर्ण_अगर
#अगर_अघोषित CVMX_HELPER_PKO_MAX_PORTS_INTERFACE1
#घोषणा CVMX_HELPER_PKO_MAX_PORTS_INTERFACE1 16
#पूर्ण_अगर

	अगर (port < CVMX_PKO_MAX_PORTS_INTERFACE0)
		वापस port * CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 + core;
	अन्यथा अगर (port >= 16 && port < 16 + CVMX_PKO_MAX_PORTS_INTERFACE1)
		वापस CVMX_PKO_MAX_PORTS_INTERFACE0 *
		    CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 + (port -
							   16) *
		    CVMX_PKO_QUEUES_PER_PORT_INTERFACE1 + core;
	अन्यथा अगर ((port >= 32) && (port < 36))
		वापस CVMX_PKO_MAX_PORTS_INTERFACE0 *
		    CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 +
		    CVMX_PKO_MAX_PORTS_INTERFACE1 *
		    CVMX_PKO_QUEUES_PER_PORT_INTERFACE1 + (port -
							   32) *
		    CVMX_PKO_QUEUES_PER_PORT_PCI;
	अन्यथा अगर ((port >= 36) && (port < 40))
		वापस CVMX_PKO_MAX_PORTS_INTERFACE0 *
		    CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 +
		    CVMX_PKO_MAX_PORTS_INTERFACE1 *
		    CVMX_PKO_QUEUES_PER_PORT_INTERFACE1 +
		    4 * CVMX_PKO_QUEUES_PER_PORT_PCI + (port -
							36) *
		    CVMX_PKO_QUEUES_PER_PORT_LOOP;
	अन्यथा
		/* Given the limit on the number of ports we can map to
		 * CVMX_MAX_OUTPUT_QUEUES_STATIC queues (currently 256,
		 * भागided among all cores), the reमुख्यing unmapped ports
		 * are asचिन्हित an illegal queue number */
		वापस CVMX_PKO_ILLEGAL_QUEUE;
पूर्ण

/**
 * For a given port number, वापस the base pko output queue
 * क्रम the port.
 *
 * @port:   Port number
 * Returns Base output queue
 */
अटल अंतरभूत पूर्णांक cvmx_pko_get_base_queue(पूर्णांक port)
अणु
	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX))
		वापस port;

	वापस cvmx_pko_get_base_queue_per_core(port, 0);
पूर्ण

/**
 * For a given port number, वापस the number of pko output queues.
 *
 * @port:   Port number
 * Returns Number of output queues
 */
अटल अंतरभूत पूर्णांक cvmx_pko_get_num_queues(पूर्णांक port)
अणु
	अगर (port < 16)
		वापस CVMX_PKO_QUEUES_PER_PORT_INTERFACE0;
	अन्यथा अगर (port < 32)
		वापस CVMX_PKO_QUEUES_PER_PORT_INTERFACE1;
	अन्यथा अगर (port < 36)
		वापस CVMX_PKO_QUEUES_PER_PORT_PCI;
	अन्यथा अगर (port < 40)
		वापस CVMX_PKO_QUEUES_PER_PORT_LOOP;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * Get the status counters क्रम a port.
 *
 * @port_num: Port number to get statistics क्रम.
 * @clear:    Set to 1 to clear the counters after they are पढ़ो
 * @status:   Where to put the results.
 */
अटल अंतरभूत व्योम cvmx_pko_get_port_status(uपूर्णांक64_t port_num, uपूर्णांक64_t clear,
					    cvmx_pko_port_status_t *status)
अणु
	जोड़ cvmx_pko_reg_पढ़ो_idx pko_reg_पढ़ो_idx;
	जोड़ cvmx_pko_mem_count0 pko_mem_count0;
	जोड़ cvmx_pko_mem_count1 pko_mem_count1;

	pko_reg_पढ़ो_idx.u64 = 0;
	pko_reg_पढ़ो_idx.s.index = port_num;
	cvmx_ग_लिखो_csr(CVMX_PKO_REG_READ_IDX, pko_reg_पढ़ो_idx.u64);

	pko_mem_count0.u64 = cvmx_पढ़ो_csr(CVMX_PKO_MEM_COUNT0);
	status->packets = pko_mem_count0.s.count;
	अगर (clear) अणु
		pko_mem_count0.s.count = port_num;
		cvmx_ग_लिखो_csr(CVMX_PKO_MEM_COUNT0, pko_mem_count0.u64);
	पूर्ण

	pko_mem_count1.u64 = cvmx_पढ़ो_csr(CVMX_PKO_MEM_COUNT1);
	status->octets = pko_mem_count1.s.count;
	अगर (clear) अणु
		pko_mem_count1.s.count = port_num;
		cvmx_ग_लिखो_csr(CVMX_PKO_MEM_COUNT1, pko_mem_count1.u64);
	पूर्ण

	अगर (OCTEON_IS_MODEL(OCTEON_CN3XXX)) अणु
		जोड़ cvmx_pko_mem_debug9 debug9;
		pko_reg_पढ़ो_idx.s.index = cvmx_pko_get_base_queue(port_num);
		cvmx_ग_लिखो_csr(CVMX_PKO_REG_READ_IDX, pko_reg_पढ़ो_idx.u64);
		debug9.u64 = cvmx_पढ़ो_csr(CVMX_PKO_MEM_DEBUG9);
		status->करोorbell = debug9.cn38xx.करोorbell;
	पूर्ण अन्यथा अणु
		जोड़ cvmx_pko_mem_debug8 debug8;
		pko_reg_पढ़ो_idx.s.index = cvmx_pko_get_base_queue(port_num);
		cvmx_ग_लिखो_csr(CVMX_PKO_REG_READ_IDX, pko_reg_पढ़ो_idx.u64);
		debug8.u64 = cvmx_पढ़ो_csr(CVMX_PKO_MEM_DEBUG8);
		status->करोorbell = debug8.cn50xx.करोorbell;
	पूर्ण
पूर्ण

/**
 * Rate limit a PKO port to a max packets/sec. This function is only
 * supported on CN57XX, CN56XX, CN55XX, and CN54XX.
 *
 * @port:      Port to rate limit
 * @packets_s: Maximum packet/sec
 * @burst:     Maximum number of packets to burst in a row beक्रमe rate
 *		    limiting cuts in.
 *
 * Returns Zero on success, negative on failure
 */
बाह्य पूर्णांक cvmx_pko_rate_limit_packets(पूर्णांक port, पूर्णांक packets_s, पूर्णांक burst);

/**
 * Rate limit a PKO port to a max bits/sec. This function is only
 * supported on CN57XX, CN56XX, CN55XX, and CN54XX.
 *
 * @port:   Port to rate limit
 * @bits_s: PKO rate limit in bits/sec
 * @burst:  Maximum number of bits to burst beक्रमe rate
 *		 limiting cuts in.
 *
 * Returns Zero on success, negative on failure
 */
बाह्य पूर्णांक cvmx_pko_rate_limit_bits(पूर्णांक port, uपूर्णांक64_t bits_s, पूर्णांक burst);

#पूर्ण_अगर /* __CVMX_PKO_H__ */
