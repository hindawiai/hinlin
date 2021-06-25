<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_HYPERVISOR_H
#घोषणा _SPARC64_HYPERVISOR_H

/* Sun4v hypervisor पूर्णांकerfaces and defines.
 *
 * Hypervisor calls are made via traps to software traps number 0x80
 * and above.  Registers %o0 to %o5 serve as argument, status, and
 * वापस value रेजिस्टरs.
 *
 * There are two kinds of these traps.  First there are the normal
 * "fast traps" which use software trap 0x80 and encode the function
 * to invoke by number in रेजिस्टर %o5.  Argument and वापस value
 * handling is as follows:
 *
 * -----------------------------------------------
 * |  %o5  | function number |     undefined     |
 * |  %o0  |   argument 0    |   वापस status   |
 * |  %o1  |   argument 1    |   वापस value 1  |
 * |  %o2  |   argument 2    |   वापस value 2  |
 * |  %o3  |   argument 3    |   वापस value 3  |
 * |  %o4  |   argument 4    |   वापस value 4  |
 * -----------------------------------------------
 *
 * The second type are "hyper-fast traps" which encode the function
 * number in the software trap number itself.  So these use trap
 * numbers > 0x80.  The रेजिस्टर usage क्रम hyper-fast traps is as
 * follows:
 *
 * -----------------------------------------------
 * |  %o0  |   argument 0    |   वापस status   |
 * |  %o1  |   argument 1    |   वापस value 1  |
 * |  %o2  |   argument 2    |   वापस value 2  |
 * |  %o3  |   argument 3    |   वापस value 3  |
 * |  %o4  |   argument 4    |   वापस value 4  |
 * -----------------------------------------------
 *
 * Registers providing explicit arguments to the hypervisor calls
 * are अस्थिर across the call.  Upon वापस their values are
 * undefined unless explicitly specअगरied as containing a particular
 * वापस value by the specअगरic call.  The वापस status is always
 * वापसed in रेजिस्टर %o0, zero indicates a successful execution of
 * the hypervisor call and other values indicate an error status as
 * defined below.  So, क्रम example, अगर a hyper-fast trap takes
 * arguments 0, 1, and 2, then %o0, %o1, and %o2 are अस्थिर across
 * the call and %o3, %o4, and %o5 would be preserved.
 *
 * If the hypervisor trap is invalid, or the fast trap function number
 * is invalid, HV_EBADTRAP will be वापसed in %o0.  Also, all 64-bits
 * of the argument and वापस values are signअगरicant.
 */

/* Trap numbers.  */
#घोषणा HV_FAST_TRAP		0x80
#घोषणा HV_MMU_MAP_ADDR_TRAP	0x83
#घोषणा HV_MMU_UNMAP_ADDR_TRAP	0x84
#घोषणा HV_TTRACE_ADDENTRY_TRAP	0x85
#घोषणा HV_CORE_TRAP		0xff

/* Error codes.  */
#घोषणा HV_EOK				0  /* Successful वापस            */
#घोषणा HV_ENOCPU			1  /* Invalid CPU id               */
#घोषणा HV_ENORADDR			2  /* Invalid real address         */
#घोषणा HV_ENOINTR			3  /* Invalid पूर्णांकerrupt id         */
#घोषणा HV_EBADPGSZ			4  /* Invalid pagesize encoding    */
#घोषणा HV_EBADTSB			5  /* Invalid TSB description      */
#घोषणा HV_EINVAL			6  /* Invalid argument             */
#घोषणा HV_EBADTRAP			7  /* Invalid function number      */
#घोषणा HV_EBADALIGN			8  /* Invalid address alignment    */
#घोषणा HV_EWOULDBLOCK			9  /* Cannot complete w/o blocking */
#घोषणा HV_ENOACCESS			10 /* No access to resource        */
#घोषणा HV_EIO				11 /* I/O error                    */
#घोषणा HV_ECPUERROR			12 /* CPU in error state           */
#घोषणा HV_ENOTSUPPORTED		13 /* Function not supported       */
#घोषणा HV_ENOMAP			14 /* No mapping found             */
#घोषणा HV_ETOOMANY			15 /* Too many items specअगरied     */
#घोषणा HV_ECHANNEL			16 /* Invalid LDC channel          */
#घोषणा HV_EBUSY			17 /* Resource busy                */
#घोषणा HV_EUNAVAILABLE			23 /* Resource or operation not
					    * currently available, but may
					    * become available in the future
					    */

/* mach_निकास()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MACH_EXIT
 * ARG0:	निकास code
 * ERRORS:	This service करोes not वापस.
 *
 * Stop all CPUs in the भव करोमुख्य and place them पूर्णांकo the stopped
 * state.  The 64-bit निकास code may be passed to a service entity as
 * the करोमुख्य's निकास status.  On प्रणालीs without a service entity, the
 * करोमुख्य will undergo a reset, and the boot firmware will be
 * reloaded.
 *
 * This function will never वापस to the guest that invokes it.
 *
 * Note: By convention an निकास code of zero denotes a successful निकास by
 *       the guest code.  A non-zero निकास code denotes a guest specअगरic
 *       error indication.
 *
 */
#घोषणा HV_FAST_MACH_EXIT		0x00

#अगर_अघोषित __ASSEMBLY__
व्योम sun4v_mach_निकास(अचिन्हित दीर्घ निकास_code);
#पूर्ण_अगर

/* Doमुख्य services.  */

/* mach_desc()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MACH_DESC
 * ARG0:	buffer
 * ARG1:	length
 * RET0:	status
 * RET1:	length
 * ERRORS:	HV_EBADALIGN	Buffer is badly aligned
 *		HV_ENORADDR	Buffer is to an illegal real address.
 *		HV_EINVAL	Buffer length is too small क्रम complete
 *				machine description.
 *
 * Copy the most current machine description पूर्णांकo the buffer indicated
 * by the real address in ARG0.  The buffer provided must be 16 byte
 * aligned.  Upon success or HV_EINVAL, this service वापसs the
 * actual size of the machine description in the RET1 वापस value.
 *
 * Note: A method of determining the appropriate buffer size क्रम the
 *       machine description is to first call this service with a buffer
 *       length of 0 bytes.
 */
#घोषणा HV_FAST_MACH_DESC		0x01

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_mach_desc(अचिन्हित दीर्घ buffer_pa,
			      अचिन्हित दीर्घ buf_len,
			      अचिन्हित दीर्घ *real_buf_len);
#पूर्ण_अगर

/* mach_sir()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MACH_SIR
 * ERRORS:	This service करोes not वापस.
 *
 * Perक्रमm a software initiated reset of the भव machine करोमुख्य.
 * All CPUs are captured as soon as possible, all hardware devices are
 * वापसed to the entry शेष state, and the करोमुख्य is restarted at
 * the SIR (trap type 0x04) real trap table (RTBA) entry poपूर्णांक on one
 * of the CPUs.  The single CPU restarted is selected as determined by
 * platक्रमm specअगरic policy.  Memory is preserved across this
 * operation.
 */
#घोषणा HV_FAST_MACH_SIR		0x02

#अगर_अघोषित __ASSEMBLY__
व्योम sun4v_mach_sir(व्योम);
#पूर्ण_अगर

/* mach_set_watchकरोg()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MACH_SET_WATCHDOG
 * ARG0:	समयout in milliseconds
 * RET0:	status
 * RET1:	समय reमुख्यing in milliseconds
 *
 * A guest uses this API to set a watchकरोg समयr.  Once the gues has set
 * the समयr, it must call the समयr service again either to disable or
 * postpone the expiration.  If the समयr expires beक्रमe being reset or
 * disabled, then the hypervisor take a platक्रमm specअगरic action leading
 * to guest termination within a bounded समय period.  The platक्रमm action
 * may include recovery actions such as reporting the expiration to a
 * Service Processor, and/or स्वतःmatically restarting the gues.
 *
 * The 'timeout' parameter is specअगरied in milliseconds, however the
 * implementated granularity is given by the 'watchdog-resolution'
 * property in the 'platform' node of the guest's machine description.
 * The largest allowed समयout value is specअगरied by the
 * 'watchdog-max-timeout' property of the 'platform' node.
 *
 * If the 'timeout' argument is not zero, the watchकरोg समयr is set to
 * expire after a minimum of 'timeout' milliseconds.
 *
 * If the 'timeout' argument is zero, the watchकरोg समयr is disabled.
 *
 * If the 'timeout' value exceeds the value of the 'max-watchdog-timeout'
 * property, the hypervisor leaves the watchकरोg समयr state unchanged,
 * and वापसs a status of EINVAL.
 *
 * The 'time remaining' वापस value is valid regardless of whether the
 * वापस status is EOK or EINVAL.  A non-zero वापस value indicates the
 * number of milliseconds that were reमुख्यing until the समयr was to expire.
 * If less than one millisecond reमुख्यs, the वापस value is '1'.  If the
 * watchकरोg समयr was disabled at the समय of the call, the वापस value is
 * zero.
 *
 * If the hypervisor cannot support the exact समयout value requested, but
 * can support a larger समयout value, the hypervisor may round the actual
 * समयout to a value larger than the requested समयout, consequently the
 * 'time remaining' वापस value may be larger than the previously requested
 * समयout value.
 *
 * Any guest OS debugger should be aware that the watchकरोg service may be in
 * use.  Consequently, it is recommended that the watchकरोg service is
 * disabled upon debugger entry (e.g. reaching a अवरोधpoपूर्णांक), and then
 * re-enabled upon वापसing to normal execution.  The API has been deचिन्हित
 * with this in mind, and the 'time remaining' result of the disable call may
 * be used directly as the समयout argument of the re-enable call.
 */
#घोषणा HV_FAST_MACH_SET_WATCHDOG	0x05

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_mach_set_watchकरोg(अचिन्हित दीर्घ समयout,
				      अचिन्हित दीर्घ *orig_समयout);
#पूर्ण_अगर

/* CPU services.
 *
 * CPUs represent devices that can execute software thपढ़ोs.  A single
 * chip that contains multiple cores or stअक्रमs is represented as
 * multiple CPUs with unique CPU identअगरiers.  CPUs are exported to
 * OBP via the machine description (and to the OS via the OBP device
 * tree).  CPUs are always in one of three states: stopped, running,
 * or error.
 *
 * A CPU ID is a pre-asचिन्हित 16-bit value that uniquely identअगरies a
 * CPU within a logical करोमुख्य.  Operations that are to be perक्रमmed
 * on multiple CPUs specअगरy them via a CPU list.  A CPU list is an
 * array in real memory, of which each 16-bit word is a CPU ID.  CPU
 * lists are passed through the API as two arguments.  The first is
 * the number of entries (16-bit words) in the CPU list, and the
 * second is the (real address) poपूर्णांकer to the CPU ID list.
 */

/* cpu_start()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_CPU_START
 * ARG0:	CPU ID
 * ARG1:	PC
 * ARG2:	RTBA
 * ARG3:	target ARG0
 * RET0:	status
 * ERRORS:	ENOCPU		Invalid CPU ID
 *		EINVAL		Target CPU ID is not in the stopped state
 *		ENORADDR	Invalid PC or RTBA real address
 *		EBADALIGN	Unaligned PC or unaligned RTBA
 *		EWOULDBLOCK	Starting resources are not available
 *
 * Start CPU with given CPU ID with PC in %pc and with a real trap
 * base address value of RTBA.  The indicated CPU must be in the
 * stopped state.  The supplied RTBA must be aligned on a 256 byte
 * boundary.  On successful completion, the specअगरied CPU will be in
 * the running state and will be supplied with "target ARG0" in %o0
 * and RTBA in %tba.
 */
#घोषणा HV_FAST_CPU_START		0x10

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_cpu_start(अचिन्हित दीर्घ cpuid,
			      अचिन्हित दीर्घ pc,
			      अचिन्हित दीर्घ rtba,
			      अचिन्हित दीर्घ arg0);
#पूर्ण_अगर

/* cpu_stop()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_CPU_STOP
 * ARG0:	CPU ID
 * RET0:	status
 * ERRORS:	ENOCPU		Invalid CPU ID
 *		EINVAL		Target CPU ID is the current cpu
 *		EINVAL		Target CPU ID is not in the running state
 *		EWOULDBLOCK	Stopping resources are not available
 *		ENOTSUPPORTED	Not supported on this platक्रमm
 *
 * The specअगरied CPU is stopped.  The indicated CPU must be in the
 * running state.  On completion, it will be in the stopped state.  It
 * is not legal to stop the current CPU.
 *
 * Note: As this service cannot be used to stop the current cpu, this service
 *       may not be used to stop the last running CPU in a करोमुख्य.  To stop
 *       and निकास a running करोमुख्य, a guest must use the mach_निकास() service.
 */
#घोषणा HV_FAST_CPU_STOP		0x11

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_cpu_stop(अचिन्हित दीर्घ cpuid);
#पूर्ण_अगर

/* cpu_yield()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_CPU_YIELD
 * RET0:	status
 * ERRORS:	No possible error.
 *
 * Suspend execution on the current CPU.  Execution will resume when
 * an पूर्णांकerrupt (device, %stick_compare, or cross-call) is targeted to
 * the CPU.  On some CPUs, this API may be used by the hypervisor to
 * save घातer by disabling hardware stअक्रमs.
 */
#घोषणा HV_FAST_CPU_YIELD		0x12

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_cpu_yield(व्योम);
#पूर्ण_अगर

/* cpu_poke()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_CPU_POKE
 * RET0:	status
 * ERRORS:	ENOCPU		cpuid refers to a CPU that करोes not exist
 *		EINVAL		cpuid is current CPU
 *
 * Poke CPU cpuid. If the target CPU is currently suspended having
 * invoked the cpu-yield service, that vCPU will be resumed.
 * Poke पूर्णांकerrupts may only be sent to valid, non-local CPUs.
 * It is not legal to poke the current vCPU.
 */
#घोषणा HV_FAST_CPU_POKE                0x13

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_cpu_poke(अचिन्हित दीर्घ cpuid);
#पूर्ण_अगर

/* cpu_qconf()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_CPU_QCONF
 * ARG0:	queue
 * ARG1:	base real address
 * ARG2:	number of entries
 * RET0:	status
 * ERRORS:	ENORADDR	Invalid base real address
 *		EINVAL		Invalid queue or number of entries is less
 *				than 2 or too large.
 *		EBADALIGN	Base real address is not correctly aligned
 *				क्रम size.
 *
 * Configure the given queue to be placed at the given base real
 * address, with the given number of entries.  The number of entries
 * must be a घातer of 2.  The base real address must be aligned
 * exactly to match the queue size.  Each queue entry is 64 bytes
 * दीर्घ, so क्रम example a 32 entry queue must be aligned on a 2048
 * byte real address boundary.
 *
 * The specअगरied queue is unconfigured अगर the number of entries is given
 * as zero.
 *
 * For the current version of this API service, the argument queue is defined
 * as follows:
 *
 *	queue		description
 *	-----		-------------------------
 *	0x3c		cpu monकरो queue
 *	0x3d		device monकरो queue
 *	0x3e		resumable error queue
 *	0x3f		non-resumable error queue
 *
 * Note: The maximum number of entries क्रम each queue क्रम a specअगरic cpu may
 *       be determined from the machine description.
 */
#घोषणा HV_FAST_CPU_QCONF		0x14
#घोषणा  HV_CPU_QUEUE_CPU_MONDO		 0x3c
#घोषणा  HV_CPU_QUEUE_DEVICE_MONDO	 0x3d
#घोषणा  HV_CPU_QUEUE_RES_ERROR		 0x3e
#घोषणा  HV_CPU_QUEUE_NONRES_ERROR	 0x3f

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_cpu_qconf(अचिन्हित दीर्घ type,
			      अचिन्हित दीर्घ queue_paddr,
			      अचिन्हित दीर्घ num_queue_entries);
#पूर्ण_अगर

/* cpu_qinfo()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_CPU_QINFO
 * ARG0:	queue
 * RET0:	status
 * RET1:	base real address
 * RET1:	number of entries
 * ERRORS:	EINVAL		Invalid queue
 *
 * Return the configuration info क्रम the given queue.  The base real
 * address and number of entries of the defined queue are वापसed.
 * The queue argument values are the same as क्रम cpu_qconf() above.
 *
 * If the specअगरied queue is a valid queue number, but no queue has
 * been defined, the number of entries will be set to zero and the
 * base real address वापसed is undefined.
 */
#घोषणा HV_FAST_CPU_QINFO		0x15

/* cpu_monकरो_send()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_CPU_MONDO_SEND
 * ARG0-1:	CPU list
 * ARG2:	data real address
 * RET0:	status
 * ERRORS:	EBADALIGN	Monकरो data is not 64-byte aligned or CPU list
 *				is not 2-byte aligned.
 *		ENORADDR	Invalid data monकरो address, or invalid cpu list
 *				address.
 *		ENOCPU		Invalid cpu in CPU list
 *		EWOULDBLOCK	Some or all of the listed CPUs did not receive
 *				the monकरो
 *		ECPUERROR	One or more of the listed CPUs are in error
 *				state, use HV_FAST_CPU_STATE to see which ones
 *		EINVAL		CPU list includes caller's CPU ID
 *
 * Send a monकरो पूर्णांकerrupt to the CPUs in the given CPU list with the
 * 64-bytes at the given data real address.  The data must be 64-byte
 * aligned.  The monकरो data will be delivered to the cpu_monकरो queues
 * of the recipient CPUs.
 *
 * In all हालs, error or not, the CPUs in the CPU list to which the
 * monकरो has been successfully delivered will be indicated by having
 * their entry in CPU list updated with the value 0xffff.
 */
#घोषणा HV_FAST_CPU_MONDO_SEND		0x42

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_cpu_monकरो_send(अचिन्हित दीर्घ cpu_count,
				   अचिन्हित दीर्घ cpu_list_pa,
				   अचिन्हित दीर्घ monकरो_block_pa);
#पूर्ण_अगर

/* cpu_myid()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_CPU_MYID
 * RET0:	status
 * RET1:	CPU ID
 * ERRORS:	No errors defined.
 *
 * Return the hypervisor ID handle क्रम the current CPU.  Use by a
 * भव CPU to discover it's own identity.
 */
#घोषणा HV_FAST_CPU_MYID		0x16

/* cpu_state()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_CPU_STATE
 * ARG0:	CPU ID
 * RET0:	status
 * RET1:	state
 * ERRORS:	ENOCPU		Invalid CPU ID
 *
 * Retrieve the current state of the CPU with the given CPU ID.
 */
#घोषणा HV_FAST_CPU_STATE		0x17
#घोषणा  HV_CPU_STATE_STOPPED		 0x01
#घोषणा  HV_CPU_STATE_RUNNING		 0x02
#घोषणा  HV_CPU_STATE_ERROR		 0x03

#अगर_अघोषित __ASSEMBLY__
दीर्घ sun4v_cpu_state(अचिन्हित दीर्घ cpuid);
#पूर्ण_अगर

/* cpu_set_rtba()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_CPU_SET_RTBA
 * ARG0:	RTBA
 * RET0:	status
 * RET1:	previous RTBA
 * ERRORS:	ENORADDR	Invalid RTBA real address
 *		EBADALIGN	RTBA is incorrectly aligned क्रम a trap table
 *
 * Set the real trap base address of the local cpu to the given RTBA.
 * The supplied RTBA must be aligned on a 256 byte boundary.  Upon
 * success the previous value of the RTBA is वापसed in RET1.
 *
 * Note: This service करोes not affect %tba
 */
#घोषणा HV_FAST_CPU_SET_RTBA		0x18

/* cpu_set_rtba()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_CPU_GET_RTBA
 * RET0:	status
 * RET1:	previous RTBA
 * ERRORS:	No possible error.
 *
 * Returns the current value of RTBA in RET1.
 */
#घोषणा HV_FAST_CPU_GET_RTBA		0x19

/* MMU services.
 *
 * Layout of a TSB description क्रम mmu_tsb_ctxअणु,nonपूर्ण0() calls.
 */
#अगर_अघोषित __ASSEMBLY__
काष्ठा hv_tsb_descr अणु
	अचिन्हित लघु		pgsz_idx;
	अचिन्हित लघु		assoc;
	अचिन्हित पूर्णांक		num_ttes;	/* in TTEs */
	अचिन्हित पूर्णांक		ctx_idx;
	अचिन्हित पूर्णांक		pgsz_mask;
	अचिन्हित दीर्घ		tsb_base;
	अचिन्हित दीर्घ		resv;
पूर्ण;
#पूर्ण_अगर
#घोषणा HV_TSB_DESCR_PGSZ_IDX_OFFSET	0x00
#घोषणा HV_TSB_DESCR_ASSOC_OFFSET	0x02
#घोषणा HV_TSB_DESCR_NUM_TTES_OFFSET	0x04
#घोषणा HV_TSB_DESCR_CTX_IDX_OFFSET	0x08
#घोषणा HV_TSB_DESCR_PGSZ_MASK_OFFSET	0x0c
#घोषणा HV_TSB_DESCR_TSB_BASE_OFFSET	0x10
#घोषणा HV_TSB_DESCR_RESV_OFFSET	0x18

/* Page size biपंचांगask.  */
#घोषणा HV_PGSZ_MASK_8K			(1 << 0)
#घोषणा HV_PGSZ_MASK_64K		(1 << 1)
#घोषणा HV_PGSZ_MASK_512K		(1 << 2)
#घोषणा HV_PGSZ_MASK_4MB		(1 << 3)
#घोषणा HV_PGSZ_MASK_32MB		(1 << 4)
#घोषणा HV_PGSZ_MASK_256MB		(1 << 5)
#घोषणा HV_PGSZ_MASK_2GB		(1 << 6)
#घोषणा HV_PGSZ_MASK_16GB		(1 << 7)

/* Page size index.  The value given in the TSB descriptor must correspond
 * to the smallest page size specअगरied in the pgsz_mask page size biपंचांगask.
 */
#घोषणा HV_PGSZ_IDX_8K			0
#घोषणा HV_PGSZ_IDX_64K			1
#घोषणा HV_PGSZ_IDX_512K		2
#घोषणा HV_PGSZ_IDX_4MB			3
#घोषणा HV_PGSZ_IDX_32MB		4
#घोषणा HV_PGSZ_IDX_256MB		5
#घोषणा HV_PGSZ_IDX_2GB			6
#घोषणा HV_PGSZ_IDX_16GB		7

/* MMU fault status area.
 *
 * MMU related faults have their status and fault address inक्रमmation
 * placed पूर्णांकo a memory region made available by privileged code.  Each
 * भव processor must make a mmu_fault_area_conf() call to tell the
 * hypervisor where that processor's fault status should be stored.
 *
 * The fault status block is a multiple of 64-bytes and must be aligned
 * on a 64-byte boundary.
 */
#अगर_अघोषित __ASSEMBLY__
काष्ठा hv_fault_status अणु
	अचिन्हित दीर्घ		i_fault_type;
	अचिन्हित दीर्घ		i_fault_addr;
	अचिन्हित दीर्घ		i_fault_ctx;
	अचिन्हित दीर्घ		i_reserved[5];
	अचिन्हित दीर्घ		d_fault_type;
	अचिन्हित दीर्घ		d_fault_addr;
	अचिन्हित दीर्घ		d_fault_ctx;
	अचिन्हित दीर्घ		d_reserved[5];
पूर्ण;
#पूर्ण_अगर
#घोषणा HV_FAULT_I_TYPE_OFFSET	0x00
#घोषणा HV_FAULT_I_ADDR_OFFSET	0x08
#घोषणा HV_FAULT_I_CTX_OFFSET	0x10
#घोषणा HV_FAULT_D_TYPE_OFFSET	0x40
#घोषणा HV_FAULT_D_ADDR_OFFSET	0x48
#घोषणा HV_FAULT_D_CTX_OFFSET	0x50

#घोषणा HV_FAULT_TYPE_FAST_MISS	1
#घोषणा HV_FAULT_TYPE_FAST_PROT	2
#घोषणा HV_FAULT_TYPE_MMU_MISS	3
#घोषणा HV_FAULT_TYPE_INV_RA	4
#घोषणा HV_FAULT_TYPE_PRIV_VIOL	5
#घोषणा HV_FAULT_TYPE_PROT_VIOL	6
#घोषणा HV_FAULT_TYPE_NFO	7
#घोषणा HV_FAULT_TYPE_NFO_SEFF	8
#घोषणा HV_FAULT_TYPE_INV_VA	9
#घोषणा HV_FAULT_TYPE_INV_ASI	10
#घोषणा HV_FAULT_TYPE_NC_ATOMIC	11
#घोषणा HV_FAULT_TYPE_PRIV_ACT	12
#घोषणा HV_FAULT_TYPE_RESV1	13
#घोषणा HV_FAULT_TYPE_UNALIGNED	14
#घोषणा HV_FAULT_TYPE_INV_PGSZ	15
#घोषणा HV_FAULT_TYPE_MCD	17
#घोषणा HV_FAULT_TYPE_MCD_DIS	18
/* Values 16 --> -2 are reserved.  */
#घोषणा HV_FAULT_TYPE_MULTIPLE	-1

/* Flags argument क्रम mmu_अणुmap,unmapपूर्ण_addr(), mmu_demap_अणुpage,context,allपूर्ण(),
 * and mmu_अणुmap,unmapपूर्ण_perm_addr().
 */
#घोषणा HV_MMU_DMMU			0x01
#घोषणा HV_MMU_IMMU			0x02
#घोषणा HV_MMU_ALL			(HV_MMU_DMMU | HV_MMU_IMMU)

/* mmu_map_addr()
 * TRAP:	HV_MMU_MAP_ADDR_TRAP
 * ARG0:	भव address
 * ARG1:	mmu context
 * ARG2:	TTE
 * ARG3:	flags (HV_MMU_अणुIMMU,DMMUपूर्ण)
 * ERRORS:	EINVAL		Invalid भव address, mmu context, or flags
 *		EBADPGSZ	Invalid page size value
 *		ENORADDR	Invalid real address in TTE
 *
 * Create a non-permanent mapping using the given TTE, भव
 * address, and mmu context.  The flags argument determines which
 * (data, or inकाष्ठाion, or both) TLB the mapping माला_लो loaded पूर्णांकo.
 *
 * The behavior is undefined अगर the valid bit is clear in the TTE.
 *
 * Note: This API call is क्रम privileged code to specअगरy temporary translation
 *       mappings without the need to create and manage a TSB.
 */

/* mmu_unmap_addr()
 * TRAP:	HV_MMU_UNMAP_ADDR_TRAP
 * ARG0:	भव address
 * ARG1:	mmu context
 * ARG2:	flags (HV_MMU_अणुIMMU,DMMUपूर्ण)
 * ERRORS:	EINVAL		Invalid भव address, mmu context, or flags
 *
 * Demaps the given भव address in the given mmu context on this
 * CPU.  This function is पूर्णांकended to be used to demap pages mapped
 * with mmu_map_addr.  This service is equivalent to invoking
 * mmu_demap_page() with only the current CPU in the CPU list. The
 * flags argument determines which (data, or inकाष्ठाion, or both) TLB
 * the mapping माला_लो unmapped from.
 *
 * Attempting to perक्रमm an unmap operation क्रम a previously defined
 * permanent mapping will have undefined results.
 */

/* mmu_tsb_ctx0()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MMU_TSB_CTX0
 * ARG0:	number of TSB descriptions
 * ARG1:	TSB descriptions poपूर्णांकer
 * RET0:	status
 * ERRORS:	ENORADDR		Invalid TSB descriptions poपूर्णांकer or
 *					TSB base within a descriptor
 *		EBADALIGN		TSB descriptions poपूर्णांकer is not aligned
 *					to an 8-byte boundary, or TSB base
 *					within a descriptor is not aligned क्रम
 *					the given TSB size
 *		EBADPGSZ		Invalid page size in a TSB descriptor
 *		EBADTSB			Invalid associativity or size in a TSB
 *					descriptor
 *		EINVAL			Invalid number of TSB descriptions, or
 *					invalid context index in a TSB
 *					descriptor, or index page size not
 *					equal to smallest page size in page
 *					size biपंचांगask field.
 *
 * Configures the TSBs क्रम the current CPU क्रम भव addresses with
 * context zero.  The TSB descriptions poपूर्णांकer is a poपूर्णांकer to an
 * array of the given number of TSB descriptions.
 *
 * Note: The maximum number of TSBs available to a भव CPU is given by the
 *       mmu-max-#tsbs property of the cpu's corresponding "cpu" node in the
 *       machine description.
 */
#घोषणा HV_FAST_MMU_TSB_CTX0		0x20

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_mmu_tsb_ctx0(अचिन्हित दीर्घ num_descriptions,
				 अचिन्हित दीर्घ tsb_desc_ra);
#पूर्ण_अगर

/* mmu_tsb_ctxnon0()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MMU_TSB_CTXNON0
 * ARG0:	number of TSB descriptions
 * ARG1:	TSB descriptions poपूर्णांकer
 * RET0:	status
 * ERRORS:	Same as क्रम mmu_tsb_ctx0() above.
 *
 * Configures the TSBs क्रम the current CPU क्रम भव addresses with
 * non-zero contexts.  The TSB descriptions poपूर्णांकer is a poपूर्णांकer to an
 * array of the given number of TSB descriptions.
 *
 * Note: A maximum of 16 TSBs may be specअगरied in the TSB description list.
 */
#घोषणा HV_FAST_MMU_TSB_CTXNON0		0x21

/* mmu_demap_page()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MMU_DEMAP_PAGE
 * ARG0:	reserved, must be zero
 * ARG1:	reserved, must be zero
 * ARG2:	भव address
 * ARG3:	mmu context
 * ARG4:	flags (HV_MMU_अणुIMMU,DMMUपूर्ण)
 * RET0:	status
 * ERRORS:	EINVAL			Invalid भव address, context, or
 *					flags value
 *		ENOTSUPPORTED		ARG0 or ARG1 is non-zero
 *
 * Demaps any page mapping of the given भव address in the given
 * mmu context क्रम the current भव CPU.  Any भवly tagged
 * caches are guaranteed to be kept consistent.  The flags argument
 * determines which TLB (inकाष्ठाion, or data, or both) participate in
 * the operation.
 *
 * ARG0 and ARG1 are both reserved and must be set to zero.
 */
#घोषणा HV_FAST_MMU_DEMAP_PAGE		0x22

/* mmu_demap_ctx()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MMU_DEMAP_CTX
 * ARG0:	reserved, must be zero
 * ARG1:	reserved, must be zero
 * ARG2:	mmu context
 * ARG3:	flags (HV_MMU_अणुIMMU,DMMUपूर्ण)
 * RET0:	status
 * ERRORS:	EINVAL			Invalid context or flags value
 *		ENOTSUPPORTED		ARG0 or ARG1 is non-zero
 *
 * Demaps all non-permanent भव page mappings previously specअगरied
 * क्रम the given context क्रम the current भव CPU.  Any भव
 * tagged caches are guaranteed to be kept consistent.  The flags
 * argument determines which TLB (inकाष्ठाion, or data, or both)
 * participate in the operation.
 *
 * ARG0 and ARG1 are both reserved and must be set to zero.
 */
#घोषणा HV_FAST_MMU_DEMAP_CTX		0x23

/* mmu_demap_all()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MMU_DEMAP_ALL
 * ARG0:	reserved, must be zero
 * ARG1:	reserved, must be zero
 * ARG2:	flags (HV_MMU_अणुIMMU,DMMUपूर्ण)
 * RET0:	status
 * ERRORS:	EINVAL			Invalid flags value
 *		ENOTSUPPORTED		ARG0 or ARG1 is non-zero
 *
 * Demaps all non-permanent भव page mappings previously specअगरied
 * क्रम the current भव CPU.  Any भव tagged caches are
 * guaranteed to be kept consistent.  The flags argument determines
 * which TLB (inकाष्ठाion, or data, or both) participate in the
 * operation.
 *
 * ARG0 and ARG1 are both reserved and must be set to zero.
 */
#घोषणा HV_FAST_MMU_DEMAP_ALL		0x24

#अगर_अघोषित __ASSEMBLY__
व्योम sun4v_mmu_demap_all(व्योम);
#पूर्ण_अगर

/* mmu_map_perm_addr()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MMU_MAP_PERM_ADDR
 * ARG0:	भव address
 * ARG1:	reserved, must be zero
 * ARG2:	TTE
 * ARG3:	flags (HV_MMU_अणुIMMU,DMMUपूर्ण)
 * RET0:	status
 * ERRORS:	EINVAL			Invalid भव address or flags value
 *		EBADPGSZ		Invalid page size value
 *		ENORADDR		Invalid real address in TTE
 *		ETOOMANY		Too many mappings (max of 8 reached)
 *
 * Create a permanent mapping using the given TTE and भव address
 * क्रम context 0 on the calling भव CPU.  A maximum of 8 such
 * permanent mappings may be specअगरied by privileged code.  Mappings
 * may be हटाओd with mmu_unmap_perm_addr().
 *
 * The behavior is undefined अगर a TTE with the valid bit clear is given.
 *
 * Note: This call is used to specअगरy address space mappings क्रम which
 *       privileged code करोes not expect to receive misses.  For example,
 *       this mechanism can be used to map kernel nucleus code and data.
 */
#घोषणा HV_FAST_MMU_MAP_PERM_ADDR	0x25

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_mmu_map_perm_addr(अचिन्हित दीर्घ vaddr,
				      अचिन्हित दीर्घ set_to_zero,
				      अचिन्हित दीर्घ tte,
				      अचिन्हित दीर्घ flags);
#पूर्ण_अगर

/* mmu_fault_area_conf()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MMU_FAULT_AREA_CONF
 * ARG0:	real address
 * RET0:	status
 * RET1:	previous mmu fault area real address
 * ERRORS:	ENORADDR		Invalid real address
 *		EBADALIGN		Invalid alignment क्रम fault area
 *
 * Configure the MMU fault status area क्रम the calling CPU.  A 64-byte
 * aligned real address specअगरies where MMU fault status inक्रमmation
 * is placed.  The वापस value is the previously specअगरied area, or 0
 * क्रम the first invocation.  Specअगरying a fault area at real address
 * 0 is not allowed.
 */
#घोषणा HV_FAST_MMU_FAULT_AREA_CONF	0x26

/* mmu_enable()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MMU_ENABLE
 * ARG0:	enable flag
 * ARG1:	वापस target address
 * RET0:	status
 * ERRORS:	ENORADDR		Invalid real address when disabling
 *					translation.
 *		EBADALIGN		The वापस target address is not
 *					aligned to an inकाष्ठाion.
 *		EINVAL			The enable flag request the current
 *					operating mode (e.g. disable अगर alपढ़ोy
 *					disabled)
 *
 * Enable or disable भव address translation क्रम the calling CPU
 * within the भव machine करोमुख्य.  If the enable flag is zero,
 * translation is disabled, any non-zero value will enable
 * translation.
 *
 * When this function वापसs, the newly selected translation mode
 * will be active.  If the mmu is being enabled, then the वापस
 * target address is a भव address अन्यथा it is a real address.
 *
 * Upon successful completion, control will be वापसed to the given
 * वापस target address (ie. the cpu will jump to that address).  On
 * failure, the previous mmu mode reमुख्यs and the trap simply वापसs
 * as normal with the appropriate error code in RET0.
 */
#घोषणा HV_FAST_MMU_ENABLE		0x27

/* mmu_unmap_perm_addr()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MMU_UNMAP_PERM_ADDR
 * ARG0:	भव address
 * ARG1:	reserved, must be zero
 * ARG2:	flags (HV_MMU_अणुIMMU,DMMUपूर्ण)
 * RET0:	status
 * ERRORS:	EINVAL			Invalid भव address or flags value
 *		ENOMAP			Specअगरied mapping was not found
 *
 * Demaps any permanent page mapping (established via
 * mmu_map_perm_addr()) at the given भव address क्रम context 0 on
 * the current भव CPU.  Any भव tagged caches are guaranteed
 * to be kept consistent.
 */
#घोषणा HV_FAST_MMU_UNMAP_PERM_ADDR	0x28

/* mmu_tsb_ctx0_info()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MMU_TSB_CTX0_INFO
 * ARG0:	max TSBs
 * ARG1:	buffer poपूर्णांकer
 * RET0:	status
 * RET1:	number of TSBs
 * ERRORS:	EINVAL			Supplied buffer is too small
 *		EBADALIGN		The buffer poपूर्णांकer is badly aligned
 *		ENORADDR		Invalid real address क्रम buffer poपूर्णांकer
 *
 * Return the TSB configuration as previous defined by mmu_tsb_ctx0()
 * पूर्णांकo the provided buffer.  The size of the buffer is given in ARG1
 * in terms of the number of TSB description entries.
 *
 * Upon वापस, RET1 always contains the number of TSB descriptions
 * previously configured.  If zero TSBs were configured, EOK is
 * वापसed with RET1 containing 0.
 */
#घोषणा HV_FAST_MMU_TSB_CTX0_INFO	0x29

/* mmu_tsb_ctxnon0_info()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MMU_TSB_CTXNON0_INFO
 * ARG0:	max TSBs
 * ARG1:	buffer poपूर्णांकer
 * RET0:	status
 * RET1:	number of TSBs
 * ERRORS:	EINVAL			Supplied buffer is too small
 *		EBADALIGN		The buffer poपूर्णांकer is badly aligned
 *		ENORADDR		Invalid real address क्रम buffer poपूर्णांकer
 *
 * Return the TSB configuration as previous defined by
 * mmu_tsb_ctxnon0() पूर्णांकo the provided buffer.  The size of the buffer
 * is given in ARG1 in terms of the number of TSB description entries.
 *
 * Upon वापस, RET1 always contains the number of TSB descriptions
 * previously configured.  If zero TSBs were configured, EOK is
 * वापसed with RET1 containing 0.
 */
#घोषणा HV_FAST_MMU_TSB_CTXNON0_INFO	0x2a

/* mmu_fault_area_info()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MMU_FAULT_AREA_INFO
 * RET0:	status
 * RET1:	fault area real address
 * ERRORS:	No errors defined.
 *
 * Return the currently defined MMU fault status area क्रम the current
 * CPU.  The real address of the fault status area is वापसed in
 * RET1, or 0 is वापसed in RET1 अगर no fault status area is defined.
 *
 * Note: mmu_fault_area_conf() may be called with the वापस value (RET1)
 *       from this service अगर there is a need to save and restore the fault
 *	 area क्रम a cpu.
 */
#घोषणा HV_FAST_MMU_FAULT_AREA_INFO	0x2b

/* Cache and Memory services. */

/* mem_scrub()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MEM_SCRUB
 * ARG0:	real address
 * ARG1:	length
 * RET0:	status
 * RET1:	length scrubbed
 * ERRORS:	ENORADDR	Invalid real address
 *		EBADALIGN	Start address or length are not correctly
 *				aligned
 *		EINVAL		Length is zero
 *
 * Zero the memory contents in the range real address to real address
 * plus length minus 1.  Also, valid ECC will be generated क्रम that
 * memory address range.  Scrubbing is started at the given real
 * address, but may not scrub the entire given length.  The actual
 * length scrubbed will be वापसed in RET1.
 *
 * The real address and length must be aligned on an 8K boundary, or
 * contain the start address and length from a sun4v error report.
 *
 * Note: There are two uses क्रम this function.  The first use is to block clear
 *       and initialize memory and the second is to scrub an u ncorrectable
 *       error reported via a resumable or non-resumable trap.  The second
 *       use requires the arguments to be equal to the real address and length
 *       provided in a sun4v memory error report.
 */
#घोषणा HV_FAST_MEM_SCRUB		0x31

/* mem_sync()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MEM_SYNC
 * ARG0:	real address
 * ARG1:	length
 * RET0:	status
 * RET1:	length synced
 * ERRORS:	ENORADDR	Invalid real address
 *		EBADALIGN	Start address or length are not correctly
 *				aligned
 *		EINVAL		Length is zero
 *
 * Force the next access within the real address to real address plus
 * length minus 1 to be fetches from मुख्य प्रणाली memory.  Less than
 * the given length may be synced, the actual amount synced is
 * वापसed in RET1.  The real address and length must be aligned on
 * an 8K boundary.
 */
#घोषणा HV_FAST_MEM_SYNC		0x32

/* Coprocessor services
 *
 * M7 and later processors provide an on-chip coprocessor which
 * accelerates database operations, and is known पूर्णांकernally as
 * DAX.
 */

/* ccb_submit()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_CCB_SUBMIT
 * ARG0:	address of CCB array
 * ARG1:	size (in bytes) of CCB array being submitted
 * ARG2:	flags
 * ARG3:	reserved
 * RET0:	status (success or error code)
 * RET1:	size (in bytes) of CCB array that was accepted (might be less
 *		than arg1)
 * RET2:	status data
 *		अगर status == ENOMAP or ENOACCESS, identअगरies the VA in question
 *		अगर status == EUNAVAILBLE, unavailable code
 * RET3:	reserved
 *
 * ERRORS:	EOK		successful submission (check size)
 *		EWOULDBLOCK	could not finish submissions, try again
 *		EBADALIGN	array not 64B aligned or size not 64B multiple
 *		ENORADDR	invalid RA क्रम array or in CCB
 *		ENOMAP		could not translate address (see status data)
 *		EINVAL		invalid ccb or arguments
 *		ETOOMANY	too many ccbs with all-or-nothing flag
 *		ENOACCESS	guest has no access to submit ccbs or address
 *				in CCB करोes not have correct permissions (check
 *				status data)
 *		EUNAVAILABLE	ccb operation could not be perक्रमmed at this
 *				समय (check status data)
 *				Status data codes:
 *					0 - exact CCB could not be executed
 *					1 - CCB opcode cannot be executed
 *					2 - CCB version cannot be executed
 *					3 - vcpu cannot execute CCBs
 *					4 - no CCBs can be executed
 */

#घोषणा HV_CCB_SUBMIT               0x34
#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_ccb_submit(अचिन्हित दीर्घ ccb_buf,
			       अचिन्हित दीर्घ len,
			       अचिन्हित दीर्घ flags,
			       अचिन्हित दीर्घ reserved,
			       व्योम *submitted_len,
			       व्योम *status_data);
#पूर्ण_अगर

/* flags (ARG2) */
#घोषणा HV_CCB_QUERY_CMD		BIT(1)
#घोषणा HV_CCB_ARG0_TYPE_REAL		0UL
#घोषणा HV_CCB_ARG0_TYPE_PRIMARY	BIT(4)
#घोषणा HV_CCB_ARG0_TYPE_SECONDARY	BIT(5)
#घोषणा HV_CCB_ARG0_TYPE_NUCLEUS	GENMASK(5, 4)
#घोषणा HV_CCB_ARG0_PRIVILEGED		BIT(6)
#घोषणा HV_CCB_ALL_OR_NOTHING		BIT(7)
#घोषणा HV_CCB_QUEUE_INFO		BIT(8)
#घोषणा HV_CCB_VA_REJECT		0UL
#घोषणा HV_CCB_VA_SECONDARY		BIT(13)
#घोषणा HV_CCB_VA_NUCLEUS		GENMASK(13, 12)
#घोषणा HV_CCB_VA_PRIVILEGED		BIT(14)
#घोषणा HV_CCB_VA_READ_ADI_DISABLE	BIT(15)	/* DAX2 only */

/* ccb_info()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_CCB_INFO
 * ARG0:	real address of CCB completion area
 * RET0:	status (success or error code)
 * RET1:	info array
 *			- RET1[0]: CCB state
 *			- RET1[1]: dax unit
 *			- RET1[2]: queue number
 *			- RET1[3]: queue position
 *
 * ERRORS:	EOK		operation successful
 *		EBADALIGN	address not 64B aligned
 *		ENORADDR	RA in address not valid
 *		EINVAL		CA not valid
 *		EWOULDBLOCK	info not available क्रम this CCB currently, try
 *				again
 *		ENOACCESS	guest cannot use dax
 */

#घोषणा HV_CCB_INFO                 0x35
#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_ccb_info(अचिन्हित दीर्घ ca,
			     व्योम *info_arr);
#पूर्ण_अगर

/* info array byte offsets (RET1) */
#घोषणा CCB_INFO_OFFSET_CCB_STATE	0
#घोषणा CCB_INFO_OFFSET_DAX_UNIT	2
#घोषणा CCB_INFO_OFFSET_QUEUE_NUM	4
#घोषणा CCB_INFO_OFFSET_QUEUE_POS	6

/* CCB state (RET1[0]) */
#घोषणा HV_CCB_STATE_COMPLETED      0
#घोषणा HV_CCB_STATE_ENQUEUED       1
#घोषणा HV_CCB_STATE_INPROGRESS     2
#घोषणा HV_CCB_STATE_NOTFOUND       3

/* ccb_समाप्त()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_CCB_KILL
 * ARG0:	real address of CCB completion area
 * RET0:	status (success or error code)
 * RET1:	CCB समाप्त status
 *
 * ERRORS:	EOK		operation successful
 *		EBADALIGN	address not 64B aligned
 *		ENORADDR	RA in address not valid
 *		EINVAL		CA not valid
 *		EWOULDBLOCK	समाप्त not available क्रम this CCB currently, try
 *				again
 *		ENOACCESS	guest cannot use dax
 */

#घोषणा HV_CCB_KILL                 0x36
#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_ccb_समाप्त(अचिन्हित दीर्घ ca,
			     व्योम *समाप्त_status);
#पूर्ण_अगर

/* CCB समाप्त status (RET1) */
#घोषणा HV_CCB_KILL_COMPLETED       0
#घोषणा HV_CCB_KILL_DEQUEUED        1
#घोषणा HV_CCB_KILL_KILLED          2
#घोषणा HV_CCB_KILL_NOTFOUND        3

/* Time of day services.
 *
 * The hypervisor मुख्यtains the समय of day on a per-करोमुख्य basis.
 * Changing the समय of day in one करोमुख्य करोes not affect the समय of
 * day on any other करोमुख्य.
 *
 * Time is described by a single अचिन्हित 64-bit word which is the
 * number of seconds since the UNIX Epoch (00:00:00 UTC, January 1,
 * 1970).
 */

/* tod_get()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_TOD_GET
 * RET0:	status
 * RET1:	TOD
 * ERRORS:	EWOULDBLOCK	TOD resource is temporarily unavailable
 *		ENOTSUPPORTED	If TOD not supported on this platक्रमm
 *
 * Return the current समय of day.  May block अगर TOD access is
 * temporarily not possible.
 */
#घोषणा HV_FAST_TOD_GET			0x50

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_tod_get(अचिन्हित दीर्घ *समय);
#पूर्ण_अगर

/* tod_set()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_TOD_SET
 * ARG0:	TOD
 * RET0:	status
 * ERRORS:	EWOULDBLOCK	TOD resource is temporarily unavailable
 *		ENOTSUPPORTED	If TOD not supported on this platक्रमm
 *
 * The current समय of day is set to the value specअगरied in ARG0.  May
 * block अगर TOD access is temporarily not possible.
 */
#घोषणा HV_FAST_TOD_SET			0x51

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_tod_set(अचिन्हित दीर्घ समय);
#पूर्ण_अगर

/* Console services */

/* con_अक्षर_लो()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_CONS_GETCHAR
 * RET0:	status
 * RET1:	अक्षरacter
 * ERRORS:	EWOULDBLOCK	No अक्षरacter available.
 *
 * Returns a अक्षरacter from the console device.  If no अक्षरacter is
 * available then an EWOULDBLOCK error is वापसed.  If a अक्षरacter is
 * available, then the वापसed status is EOK and the अक्षरacter value
 * is in RET1.
 *
 * A भव BREAK is represented by the 64-bit value -1.
 *
 * A भव HUP संकेत is represented by the 64-bit value -2.
 */
#घोषणा HV_FAST_CONS_GETCHAR		0x60

/* con_अक्षर_दो()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_CONS_PUTCHAR
 * ARG0:	अक्षरacter
 * RET0:	status
 * ERRORS:	EINVAL		Illegal अक्षरacter
 *		EWOULDBLOCK	Output buffer currently full, would block
 *
 * Send a अक्षरacter to the console device.  Only अक्षरacter values
 * between 0 and 255 may be used.  Values outside this range are
 * invalid except क्रम the 64-bit value -1 which is used to send a
 * भव BREAK.
 */
#घोषणा HV_FAST_CONS_PUTCHAR		0x61

/* con_पढ़ो()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_CONS_READ
 * ARG0:	buffer real address
 * ARG1:	buffer size in bytes
 * RET0:	status
 * RET1:	bytes पढ़ो or BREAK or HUP
 * ERRORS:	EWOULDBLOCK	No अक्षरacter available.
 *
 * Reads अक्षरacters पूर्णांकo a buffer from the console device.  If no
 * अक्षरacter is available then an EWOULDBLOCK error is वापसed.
 * If a अक्षरacter is available, then the वापसed status is EOK
 * and the number of bytes पढ़ो पूर्णांकo the given buffer is provided
 * in RET1.
 *
 * A भव BREAK is represented by the 64-bit RET1 value -1.
 *
 * A भव HUP संकेत is represented by the 64-bit RET1 value -2.
 *
 * If BREAK or HUP are indicated, no bytes were पढ़ो पूर्णांकo buffer.
 */
#घोषणा HV_FAST_CONS_READ		0x62

/* con_ग_लिखो()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_CONS_WRITE
 * ARG0:	buffer real address
 * ARG1:	buffer size in bytes
 * RET0:	status
 * RET1:	bytes written
 * ERRORS:	EWOULDBLOCK	Output buffer currently full, would block
 *
 * Send a अक्षरacters in buffer to the console device.  Breaks must be
 * sent using con_अक्षर_दो().
 */
#घोषणा HV_FAST_CONS_WRITE		0x63

#अगर_अघोषित __ASSEMBLY__
दीर्घ sun4v_con_अक्षर_लो(दीर्घ *status);
दीर्घ sun4v_con_अक्षर_दो(दीर्घ c);
दीर्घ sun4v_con_पढ़ो(अचिन्हित दीर्घ buffer,
		    अचिन्हित दीर्घ size,
		    अचिन्हित दीर्घ *bytes_पढ़ो);
अचिन्हित दीर्घ sun4v_con_ग_लिखो(अचिन्हित दीर्घ buffer,
			      अचिन्हित दीर्घ size,
			      अचिन्हित दीर्घ *bytes_written);
#पूर्ण_अगर

/* mach_set_soft_state()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MACH_SET_SOFT_STATE
 * ARG0:	software state
 * ARG1:	software state description poपूर्णांकer
 * RET0:	status
 * ERRORS:	EINVAL		software state not valid or software state
 *				description is not शून्य terminated
 *		ENORADDR	software state description poपूर्णांकer is not a
 *				valid real address
 *		EBADALIGNED	software state description is not correctly
 *				aligned
 *
 * This allows the guest to report it's soft state to the hypervisor.  There
 * are two primary components to this state.  The first part states whether
 * the guest software is running or not.  The second contaपूर्णांकs optional
 * details specअगरic to the software.
 *
 * The software state argument is defined below in HV_SOFT_STATE_*, and
 * indicates whether the guest is operating normally or in a transitional
 * state.
 *
 * The software state description argument is a real address of a data buffer
 * of size 32-bytes aligned on a 32-byte boundary.  It is treated as a शून्य
 * terminated 7-bit ASCII string of up to 31 अक्षरacters not including the
 * शून्य termination.
 */
#घोषणा HV_FAST_MACH_SET_SOFT_STATE	0x70
#घोषणा  HV_SOFT_STATE_NORMAL		 0x01
#घोषणा  HV_SOFT_STATE_TRANSITION	 0x02

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_mach_set_soft_state(अचिन्हित दीर्घ soft_state,
				        अचिन्हित दीर्घ msg_string_ra);
#पूर्ण_अगर

/* mach_get_soft_state()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MACH_GET_SOFT_STATE
 * ARG0:	software state description poपूर्णांकer
 * RET0:	status
 * RET1:	software state
 * ERRORS:	ENORADDR	software state description poपूर्णांकer is not a
 *				valid real address
 *		EBADALIGNED	software state description is not correctly
 *				aligned
 *
 * Retrieve the current value of the guest's software state.  The rules
 * क्रम the software state poपूर्णांकer are the same as क्रम mach_set_soft_state()
 * above.
 */
#घोषणा HV_FAST_MACH_GET_SOFT_STATE	0x71

/* svc_send()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_SVC_SEND
 * ARG0:	service ID
 * ARG1:	buffer real address
 * ARG2:	buffer size
 * RET0:	STATUS
 * RET1:	sent_bytes
 *
 * Be careful, all output रेजिस्टरs are clobbered by this operation,
 * so क्रम example it is not possible to save away a value in %o4
 * across the trap.
 */
#घोषणा HV_FAST_SVC_SEND		0x80

/* svc_recv()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_SVC_RECV
 * ARG0:	service ID
 * ARG1:	buffer real address
 * ARG2:	buffer size
 * RET0:	STATUS
 * RET1:	recv_bytes
 *
 * Be careful, all output रेजिस्टरs are clobbered by this operation,
 * so क्रम example it is not possible to save away a value in %o4
 * across the trap.
 */
#घोषणा HV_FAST_SVC_RECV		0x81

/* svc_माला_लोtatus()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_SVC_GETSTATUS
 * ARG0:	service ID
 * RET0:	STATUS
 * RET1:	status bits
 */
#घोषणा HV_FAST_SVC_GETSTATUS		0x82

/* svc_setstatus()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_SVC_SETSTATUS
 * ARG0:	service ID
 * ARG1:	bits to set
 * RET0:	STATUS
 */
#घोषणा HV_FAST_SVC_SETSTATUS		0x83

/* svc_clrstatus()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_SVC_CLRSTATUS
 * ARG0:	service ID
 * ARG1:	bits to clear
 * RET0:	STATUS
 */
#घोषणा HV_FAST_SVC_CLRSTATUS		0x84

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_svc_send(अचिन्हित दीर्घ svc_id,
			     अचिन्हित दीर्घ buffer,
			     अचिन्हित दीर्घ buffer_size,
			     अचिन्हित दीर्घ *sent_bytes);
अचिन्हित दीर्घ sun4v_svc_recv(अचिन्हित दीर्घ svc_id,
			     अचिन्हित दीर्घ buffer,
			     अचिन्हित दीर्घ buffer_size,
			     अचिन्हित दीर्घ *recv_bytes);
अचिन्हित दीर्घ sun4v_svc_माला_लोtatus(अचिन्हित दीर्घ svc_id,
				  अचिन्हित दीर्घ *status_bits);
अचिन्हित दीर्घ sun4v_svc_setstatus(अचिन्हित दीर्घ svc_id,
				  अचिन्हित दीर्घ status_bits);
अचिन्हित दीर्घ sun4v_svc_clrstatus(अचिन्हित दीर्घ svc_id,
				  अचिन्हित दीर्घ status_bits);
#पूर्ण_अगर

/* Trap trace services.
 *
 * The hypervisor provides a trap tracing capability क्रम privileged
 * code running on each भव CPU.  Privileged code provides a
 * round-robin trap trace queue within which the hypervisor ग_लिखोs
 * 64-byte entries detailing hyperprivileged traps taken n behalf of
 * privileged code.  This is provided as a debugging capability क्रम
 * privileged code.
 *
 * The trap trace control काष्ठाure is 64-bytes दीर्घ and placed at the
 * start (offset 0) of the trap trace buffer, and is described as
 * follows:
 */
#अगर_अघोषित __ASSEMBLY__
काष्ठा hv_trap_trace_control अणु
	अचिन्हित दीर्घ		head_offset;
	अचिन्हित दीर्घ		tail_offset;
	अचिन्हित दीर्घ		__reserved[0x30 / माप(अचिन्हित दीर्घ)];
पूर्ण;
#पूर्ण_अगर
#घोषणा HV_TRAP_TRACE_CTRL_HEAD_OFFSET	0x00
#घोषणा HV_TRAP_TRACE_CTRL_TAIL_OFFSET	0x08

/* The head offset is the offset of the most recently completed entry
 * in the trap-trace buffer.  The tail offset is the offset of the
 * next entry to be written.  The control काष्ठाure is owned and
 * modअगरied by the hypervisor.  A guest may not modअगरy the control
 * काष्ठाure contents.  Attempts to करो so will result in undefined
 * behavior क्रम the guest.
 *
 * Each trap trace buffer entry is laid out as follows:
 */
#अगर_अघोषित __ASSEMBLY__
काष्ठा hv_trap_trace_entry अणु
	अचिन्हित अक्षर	type;		/* Hypervisor or guest entry?	*/
	अचिन्हित अक्षर	hpstate;	/* Hyper-privileged state	*/
	अचिन्हित अक्षर	tl;		/* Trap level			*/
	अचिन्हित अक्षर	gl;		/* Global रेजिस्टर level	*/
	अचिन्हित लघु	tt;		/* Trap type			*/
	अचिन्हित लघु	tag;		/* Extended trap identअगरier	*/
	अचिन्हित दीर्घ	tstate;		/* Trap state			*/
	अचिन्हित दीर्घ	tick;		/* Tick				*/
	अचिन्हित दीर्घ	tpc;		/* Trap PC			*/
	अचिन्हित दीर्घ	f1;		/* Entry specअगरic		*/
	अचिन्हित दीर्घ	f2;		/* Entry specअगरic		*/
	अचिन्हित दीर्घ	f3;		/* Entry specअगरic		*/
	अचिन्हित दीर्घ	f4;		/* Entry specअगरic		*/
पूर्ण;
#पूर्ण_अगर
#घोषणा HV_TRAP_TRACE_ENTRY_TYPE	0x00
#घोषणा HV_TRAP_TRACE_ENTRY_HPSTATE	0x01
#घोषणा HV_TRAP_TRACE_ENTRY_TL		0x02
#घोषणा HV_TRAP_TRACE_ENTRY_GL		0x03
#घोषणा HV_TRAP_TRACE_ENTRY_TT		0x04
#घोषणा HV_TRAP_TRACE_ENTRY_TAG		0x06
#घोषणा HV_TRAP_TRACE_ENTRY_TSTATE	0x08
#घोषणा HV_TRAP_TRACE_ENTRY_TICK	0x10
#घोषणा HV_TRAP_TRACE_ENTRY_TPC		0x18
#घोषणा HV_TRAP_TRACE_ENTRY_F1		0x20
#घोषणा HV_TRAP_TRACE_ENTRY_F2		0x28
#घोषणा HV_TRAP_TRACE_ENTRY_F3		0x30
#घोषणा HV_TRAP_TRACE_ENTRY_F4		0x38

/* The type field is encoded as follows.  */
#घोषणा HV_TRAP_TYPE_UNDEF		0x00 /* Entry content undefined     */
#घोषणा HV_TRAP_TYPE_HV			0x01 /* Hypervisor trap entry       */
#घोषणा HV_TRAP_TYPE_GUEST		0xff /* Added via ttrace_addentry() */

/* ttrace_buf_conf()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_TTRACE_BUF_CONF
 * ARG0:	real address
 * ARG1:	number of entries
 * RET0:	status
 * RET1:	number of entries
 * ERRORS:	ENORADDR	Invalid real address
 *		EINVAL		Size is too small
 *		EBADALIGN	Real address not aligned on 64-byte boundary
 *
 * Requests hypervisor trap tracing and declares a भव CPU's trap
 * trace buffer to the hypervisor.  The real address supplies the real
 * base address of the trap trace queue and must be 64-byte aligned.
 * Specअगरying a value of 0 क्रम the number of entries disables trap
 * tracing क्रम the calling भव CPU.  The buffer allocated must be
 * sized क्रम a घातer of two number of 64-byte trap trace entries plus
 * an initial 64-byte control काष्ठाure.
 *
 * This may be invoked any number of बार so that a भव CPU may
 * relocate a trap trace buffer or create "snapshots" of inक्रमmation.
 *
 * If the real address is illegal or badly aligned, then trap tracing
 * is disabled and an error is वापसed.
 *
 * Upon failure with EINVAL, this service call वापसs in RET1 the
 * minimum number of buffer entries required.  Upon other failures
 * RET1 is undefined.
 */
#घोषणा HV_FAST_TTRACE_BUF_CONF		0x90

/* ttrace_buf_info()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_TTRACE_BUF_INFO
 * RET0:	status
 * RET1:	real address
 * RET2:	size
 * ERRORS:	None defined.
 *
 * Returns the size and location of the previously declared trap-trace
 * buffer.  In the event that no buffer was previously defined, or the
 * buffer is disabled, this call will वापस a size of zero bytes.
 */
#घोषणा HV_FAST_TTRACE_BUF_INFO		0x91

/* ttrace_enable()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_TTRACE_ENABLE
 * ARG0:	enable
 * RET0:	status
 * RET1:	previous enable state
 * ERRORS:	EINVAL		No trap trace buffer currently defined
 *
 * Enable or disable trap tracing, and वापस the previous enabled
 * state in RET1.  Future प्रणालीs may define various flags क्रम the
 * enable argument (ARG0), क्रम the moment a guest should pass
 * "(uint64_t) -1" to enable, and "(uint64_t) 0" to disable all
 * tracing - which will ensure future compatibility.
 */
#घोषणा HV_FAST_TTRACE_ENABLE		0x92

/* ttrace_मुक्तze()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_TTRACE_FREEZE
 * ARG0:	मुक्तze
 * RET0:	status
 * RET1:	previous मुक्तze state
 * ERRORS:	EINVAL		No trap trace buffer currently defined
 *
 * Freeze or unमुक्तze trap tracing, वापसing the previous मुक्तze
 * state in RET1.  A guest should pass a non-zero value to मुक्तze and
 * a zero value to unमुक्तze all tracing.  The वापसed previous state
 * is 0 क्रम not frozen and 1 क्रम frozen.
 */
#घोषणा HV_FAST_TTRACE_FREEZE		0x93

/* ttrace_addentry()
 * TRAP:	HV_TTRACE_ADDENTRY_TRAP
 * ARG0:	tag (16-bits)
 * ARG1:	data word 0
 * ARG2:	data word 1
 * ARG3:	data word 2
 * ARG4:	data word 3
 * RET0:	status
 * ERRORS:	EINVAL		No trap trace buffer currently defined
 *
 * Add an entry to the trap trace buffer.  Upon वापस only ARG0/RET0
 * is modअगरied - none of the other रेजिस्टरs holding arguments are
 * अस्थिर across this hypervisor service.
 */

/* Core dump services.
 *
 * Since the hypervisor viraulizes and thus obscures a lot of the
 * physical machine layout and state, traditional OS crash dumps can
 * be dअगरficult to diagnose especially when the problem is a
 * configuration error of some sort.
 *
 * The dump services provide an opaque buffer पूर्णांकo which the
 * hypervisor can place it's पूर्णांकernal state in order to assist in
 * debugging such situations.  The contents are opaque and extremely
 * platक्रमm and hypervisor implementation specअगरic.  The guest, during
 * a core dump, requests that the hypervisor update any inक्रमmation in
 * the dump buffer in preparation to being dumped as part of the
 * करोमुख्य's memory image.
 */

/* dump_buf_update()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_DUMP_BUF_UPDATE
 * ARG0:	real address
 * ARG1:	size
 * RET0:	status
 * RET1:	required size of dump buffer
 * ERRORS:	ENORADDR	Invalid real address
 *		EBADALIGN	Real address is not aligned on a 64-byte
 *				boundary
 *		EINVAL		Size is non-zero but less than minimum size
 *				required
 *		ENOTSUPPORTED	Operation not supported on current logical
 *				करोमुख्य
 *
 * Declare a करोमुख्य dump buffer to the hypervisor.  The real address
 * provided क्रम the करोमुख्य dump buffer must be 64-byte aligned.  The
 * size specअगरies the size of the dump buffer and may be larger than
 * the minimum size specअगरied in the machine description.  The
 * hypervisor will fill the dump buffer with opaque data.
 *
 * Note: A guest may elect to include dump buffer contents as part of a crash
 *       dump to assist with debugging.  This function may be called any number
 *       of बार so that a guest may relocate a dump buffer, or create
 *       "snapshots" of any dump-buffer inक्रमmation.  Each call to
 *       dump_buf_update() atomically declares the new dump buffer to the
 *       hypervisor.
 *
 * A specअगरied size of 0 unconfigures the dump buffer.  If the real
 * address is illegal or badly aligned, then any currently active dump
 * buffer is disabled and an error is वापसed.
 *
 * In the event that the call fails with EINVAL, RET1 contains the
 * minimum size requires by the hypervisor क्रम a valid dump buffer.
 */
#घोषणा HV_FAST_DUMP_BUF_UPDATE		0x94

/* dump_buf_info()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_DUMP_BUF_INFO
 * RET0:	status
 * RET1:	real address of current dump buffer
 * RET2:	size of current dump buffer
 * ERRORS:	No errors defined.
 *
 * Return the currently configures dump buffer description.  A
 * वापसed size of 0 bytes indicates an undefined dump buffer.  In
 * this हाल the वापस address in RET1 is undefined.
 */
#घोषणा HV_FAST_DUMP_BUF_INFO		0x95

/* Device पूर्णांकerrupt services.
 *
 * Device पूर्णांकerrupts are allocated to प्रणाली bus bridges by the hypervisor,
 * and described to OBP in the machine description.  OBP then describes
 * these पूर्णांकerrupts to the OS via properties in the device tree.
 *
 * Terminology:
 *
 *	cpuid		Unique opaque value which represents a target cpu.
 *
 *	devhandle	Device handle.  It uniquely identअगरies a device, and
 *			consistes of the lower 28-bits of the hi-cell of the
 *			first entry of the device's "reg" property in the
 *			OBP device tree.
 *
 *	devino		Device पूर्णांकerrupt number.  Specअगरies the relative
 *			पूर्णांकerrupt number within the device.  The unique
 *			combination of devhandle and devino are used to
 *			identअगरy a specअगरic device पूर्णांकerrupt.
 *
 *			Note: The devino value is the same as the values in the
 *			      "interrupts" property or "interrupt-map" property
 *			      in the OBP device tree क्रम that device.
 *
 *	sysino		System पूर्णांकerrupt number.  A 64-bit अचिन्हित पूर्णांकerger
 *			representing a unique पूर्णांकerrupt within a भव
 *			machine.
 *
 *	पूर्णांकr_state	A flag representing the पूर्णांकerrupt state क्रम a given
 *			sysino.  The state values are defined below.
 *
 *	पूर्णांकr_enabled	A flag representing the 'enabled' state क्रम a given
 *			sysino.  The enable values are defined below.
 */

#घोषणा HV_INTR_STATE_IDLE		0 /* Nothing pending */
#घोषणा HV_INTR_STATE_RECEIVED		1 /* Interrupt received by hardware */
#घोषणा HV_INTR_STATE_DELIVERED		2 /* Interrupt delivered to queue */

#घोषणा HV_INTR_DISABLED		0 /* sysino not enabled */
#घोषणा HV_INTR_ENABLED			1 /* sysino enabled */

/* पूर्णांकr_devino_to_sysino()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_INTR_DEVINO2SYSINO
 * ARG0:	devhandle
 * ARG1:	devino
 * RET0:	status
 * RET1:	sysino
 * ERRORS:	EINVAL		Invalid devhandle/devino
 *
 * Converts a device specअगरic पूर्णांकerrupt number of the given
 * devhandle/devino पूर्णांकo a प्रणाली specअगरic ino (sysino).
 */
#घोषणा HV_FAST_INTR_DEVINO2SYSINO	0xa0

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_devino_to_sysino(अचिन्हित दीर्घ devhandle,
				     अचिन्हित दीर्घ devino);
#पूर्ण_अगर

/* पूर्णांकr_getenabled()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_INTR_GETENABLED
 * ARG0:	sysino
 * RET0:	status
 * RET1:	पूर्णांकr_enabled (HV_INTR_अणुDISABLED,ENABLEDपूर्ण)
 * ERRORS:	EINVAL		Invalid sysino
 *
 * Returns पूर्णांकerrupt enabled state in RET1 क्रम the पूर्णांकerrupt defined
 * by the given sysino.
 */
#घोषणा HV_FAST_INTR_GETENABLED		0xa1

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_पूर्णांकr_getenabled(अचिन्हित दीर्घ sysino);
#पूर्ण_अगर

/* पूर्णांकr_setenabled()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_INTR_SETENABLED
 * ARG0:	sysino
 * ARG1:	पूर्णांकr_enabled (HV_INTR_अणुDISABLED,ENABLEDपूर्ण)
 * RET0:	status
 * ERRORS:	EINVAL		Invalid sysino or पूर्णांकr_enabled value
 *
 * Set the 'enabled' state of the पूर्णांकerrupt sysino.
 */
#घोषणा HV_FAST_INTR_SETENABLED		0xa2

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_पूर्णांकr_setenabled(अचिन्हित दीर्घ sysino,
				    अचिन्हित दीर्घ पूर्णांकr_enabled);
#पूर्ण_अगर

/* पूर्णांकr_माला_लोtate()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_INTR_GETSTATE
 * ARG0:	sysino
 * RET0:	status
 * RET1:	पूर्णांकr_state (HV_INTR_STATE_*)
 * ERRORS:	EINVAL		Invalid sysino
 *
 * Returns current state of the पूर्णांकerrupt defined by the given sysino.
 */
#घोषणा HV_FAST_INTR_GETSTATE		0xa3

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_पूर्णांकr_माला_लोtate(अचिन्हित दीर्घ sysino);
#पूर्ण_अगर

/* पूर्णांकr_setstate()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_INTR_SETSTATE
 * ARG0:	sysino
 * ARG1:	पूर्णांकr_state (HV_INTR_STATE_*)
 * RET0:	status
 * ERRORS:	EINVAL		Invalid sysino or पूर्णांकr_state value
 *
 * Sets the current state of the पूर्णांकerrupt described by the given sysino
 * value.
 *
 * Note: Setting the state to HV_INTR_STATE_IDLE clears any pending
 *       पूर्णांकerrupt क्रम sysino.
 */
#घोषणा HV_FAST_INTR_SETSTATE		0xa4

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_पूर्णांकr_setstate(अचिन्हित दीर्घ sysino, अचिन्हित दीर्घ पूर्णांकr_state);
#पूर्ण_अगर

/* पूर्णांकr_gettarget()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_INTR_GETTARGET
 * ARG0:	sysino
 * RET0:	status
 * RET1:	cpuid
 * ERRORS:	EINVAL		Invalid sysino
 *
 * Returns CPU that is the current target of the पूर्णांकerrupt defined by
 * the given sysino.  The CPU value वापसed is undefined अगर the target
 * has not been set via पूर्णांकr_settarget().
 */
#घोषणा HV_FAST_INTR_GETTARGET		0xa5

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_पूर्णांकr_gettarget(अचिन्हित दीर्घ sysino);
#पूर्ण_अगर

/* पूर्णांकr_settarget()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_INTR_SETTARGET
 * ARG0:	sysino
 * ARG1:	cpuid
 * RET0:	status
 * ERRORS:	EINVAL		Invalid sysino
 *		ENOCPU		Invalid cpuid
 *
 * Set the target CPU क्रम the पूर्णांकerrupt defined by the given sysino.
 */
#घोषणा HV_FAST_INTR_SETTARGET		0xa6

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_पूर्णांकr_settarget(अचिन्हित दीर्घ sysino, अचिन्हित दीर्घ cpuid);
#पूर्ण_अगर

/* vपूर्णांकr_get_cookie()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_VINTR_GET_COOKIE
 * ARG0:	device handle
 * ARG1:	device ino
 * RET0:	status
 * RET1:	cookie
 */
#घोषणा HV_FAST_VINTR_GET_COOKIE	0xa7

/* vपूर्णांकr_set_cookie()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_VINTR_SET_COOKIE
 * ARG0:	device handle
 * ARG1:	device ino
 * ARG2:	cookie
 * RET0:	status
 */
#घोषणा HV_FAST_VINTR_SET_COOKIE	0xa8

/* vपूर्णांकr_get_valid()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_VINTR_GET_VALID
 * ARG0:	device handle
 * ARG1:	device ino
 * RET0:	status
 * RET1:	valid state
 */
#घोषणा HV_FAST_VINTR_GET_VALID		0xa9

/* vपूर्णांकr_set_valid()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_VINTR_SET_VALID
 * ARG0:	device handle
 * ARG1:	device ino
 * ARG2:	valid state
 * RET0:	status
 */
#घोषणा HV_FAST_VINTR_SET_VALID		0xaa

/* vपूर्णांकr_get_state()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_VINTR_GET_STATE
 * ARG0:	device handle
 * ARG1:	device ino
 * RET0:	status
 * RET1:	state
 */
#घोषणा HV_FAST_VINTR_GET_STATE		0xab

/* vपूर्णांकr_set_state()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_VINTR_SET_STATE
 * ARG0:	device handle
 * ARG1:	device ino
 * ARG2:	state
 * RET0:	status
 */
#घोषणा HV_FAST_VINTR_SET_STATE		0xac

/* vपूर्णांकr_get_target()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_VINTR_GET_TARGET
 * ARG0:	device handle
 * ARG1:	device ino
 * RET0:	status
 * RET1:	cpuid
 */
#घोषणा HV_FAST_VINTR_GET_TARGET	0xad

/* vपूर्णांकr_set_target()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_VINTR_SET_TARGET
 * ARG0:	device handle
 * ARG1:	device ino
 * ARG2:	cpuid
 * RET0:	status
 */
#घोषणा HV_FAST_VINTR_SET_TARGET	0xae

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_vपूर्णांकr_get_cookie(अचिन्हित दीर्घ dev_handle,
				     अचिन्हित दीर्घ dev_ino,
				     अचिन्हित दीर्घ *cookie);
अचिन्हित दीर्घ sun4v_vपूर्णांकr_set_cookie(अचिन्हित दीर्घ dev_handle,
				     अचिन्हित दीर्घ dev_ino,
				     अचिन्हित दीर्घ cookie);
अचिन्हित दीर्घ sun4v_vपूर्णांकr_get_valid(अचिन्हित दीर्घ dev_handle,
				    अचिन्हित दीर्घ dev_ino,
				    अचिन्हित दीर्घ *valid);
अचिन्हित दीर्घ sun4v_vपूर्णांकr_set_valid(अचिन्हित दीर्घ dev_handle,
				    अचिन्हित दीर्घ dev_ino,
				    अचिन्हित दीर्घ valid);
अचिन्हित दीर्घ sun4v_vपूर्णांकr_get_state(अचिन्हित दीर्घ dev_handle,
				    अचिन्हित दीर्घ dev_ino,
				    अचिन्हित दीर्घ *state);
अचिन्हित दीर्घ sun4v_vपूर्णांकr_set_state(अचिन्हित दीर्घ dev_handle,
				    अचिन्हित दीर्घ dev_ino,
				    अचिन्हित दीर्घ state);
अचिन्हित दीर्घ sun4v_vपूर्णांकr_get_target(अचिन्हित दीर्घ dev_handle,
				     अचिन्हित दीर्घ dev_ino,
				     अचिन्हित दीर्घ *cpuid);
अचिन्हित दीर्घ sun4v_vपूर्णांकr_set_target(अचिन्हित दीर्घ dev_handle,
				     अचिन्हित दीर्घ dev_ino,
				     अचिन्हित दीर्घ cpuid);
#पूर्ण_अगर

/* PCI IO services.
 *
 * See the terminology descriptions in the device पूर्णांकerrupt services
 * section above as those apply here too.  Here are terminology
 * definitions specअगरic to these PCI IO services:
 *
 *	tsbnum		TSB number.  Indentअगरies which io-tsb is used.
 *			For this version of the specअगरication, tsbnum
 *			must be zero.
 *
 *	tsbindex	TSB index.  Identअगरies which entry in the TSB
 *			is used.  The first entry is zero.
 *
 *	tsbid		A 64-bit aligned data काष्ठाure which contains
 *			a tsbnum and a tsbindex.  Bits 63:32 contain the
 *			tsbnum and bits 31:00 contain the tsbindex.
 *
 *			Use the HV_PCI_TSBID() macro to स्थिरruct such
 * 			values.
 *
 *	io_attributes	IO attributes क्रम IOMMU mappings.  One of more
 *			of the attritbute bits are stores in a 64-bit
 *			value.  The values are defined below.
 *
 *	r_addr		64-bit real address
 *
 *	pci_device	PCI device address.  A PCI device address identअगरies
 *			a specअगरic device on a specअगरic PCI bus segment.
 *			A PCI device address ia a 32-bit अचिन्हित पूर्णांकeger
 *			with the following क्रमmat:
 *
 *				00000000.bbbbbbbb.dddddfff.00000000
 *
 *			Use the HV_PCI_DEVICE_BUILD() macro to स्थिरruct
 *			such values.
 *
 *	pci_config_offset
 *			PCI configureation space offset.  For conventional
 *			PCI a value between 0 and 255.  For extended
 *			configuration space, a value between 0 and 4095.
 *
 *			Note: For PCI configuration space accesses, the offset
 *			      must be aligned to the access size.
 *
 *	error_flag	A वापस value which specअगरies अगर the action succeeded
 *			or failed.  0 means no error, non-0 means some error
 *			occurred जबतक perक्रमming the service.
 *
 *	io_sync_direction
 *			Direction definition क्रम pci_dma_sync(), defined
 *			below in HV_PCI_SYNC_*.
 *
 *	io_page_list	A list of io_page_addresses, an io_page_address is
 *			a real address.
 *
 *	io_page_list_p	A poपूर्णांकer to an io_page_list.
 *
 *	"size based byte swap" - Some functions करो size based byte swapping
 *				 which allows sw to access poपूर्णांकers and
 *				 counters in native क्रमm when the processor
 *				 operates in a dअगरferent endianness than the
 *				 IO bus.  Size-based byte swapping converts a
 *				 multi-byte field between big-endian and
 *				 little-endian क्रमmat.
 */

#घोषणा HV_PCI_MAP_ATTR_READ		0x01
#घोषणा HV_PCI_MAP_ATTR_WRITE		0x02
#घोषणा HV_PCI_MAP_ATTR_RELAXED_ORDER	0x04

#घोषणा HV_PCI_DEVICE_BUILD(b,d,f)	\
	((((b) & 0xff) << 16) | \
	 (((d) & 0x1f) << 11) | \
	 (((f) & 0x07) <<  8))

#घोषणा HV_PCI_TSBID(__tsb_num, __tsb_index) \
	((((u64)(__tsb_num)) << 32UL) | ((u64)(__tsb_index)))

#घोषणा HV_PCI_SYNC_FOR_DEVICE		0x01
#घोषणा HV_PCI_SYNC_FOR_CPU		0x02

/* pci_iommu_map()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_IOMMU_MAP
 * ARG0:	devhandle
 * ARG1:	tsbid
 * ARG2:	#ttes
 * ARG3:	io_attributes
 * ARG4:	io_page_list_p
 * RET0:	status
 * RET1:	#ttes mapped
 * ERRORS:	EINVAL		Invalid devhandle/tsbnum/tsbindex/io_attributes
 *		EBADALIGN	Improperly aligned real address
 *		ENORADDR	Invalid real address
 *
 * Create IOMMU mappings in the sun4v device defined by the given
 * devhandle.  The mappings are created in the TSB defined by the
 * tsbnum component of the given tsbid.  The first mapping is created
 * in the TSB i ndex defined by the tsbindex component of the given tsbid.
 * The call creates up to #ttes mappings, the first one at tsbnum, tsbindex,
 * the second at tsbnum, tsbindex + 1, etc.
 *
 * All mappings are created with the attributes defined by the io_attributes
 * argument.  The page mapping addresses are described in the io_page_list
 * defined by the given io_page_list_p, which is a poपूर्णांकer to the io_page_list.
 * The first entry in the io_page_list is the address क्रम the first iotte, the
 * 2nd क्रम the 2nd iotte, and so on.
 *
 * Each io_page_address in the io_page_list must be appropriately aligned.
 * #ttes must be greater than zero.  For this version of the spec, the tsbnum
 * component of the given tsbid must be zero.
 *
 * Returns the actual number of mappings creates, which may be less than
 * or equal to the argument #ttes.  If the function वापसs a value which
 * is less than the #ttes, the caller may continus to call the function with
 * an updated tsbid, #ttes, io_page_list_p arguments until all pages are
 * mapped.
 *
 * Note: This function करोes not imply an iotte cache flush.  The guest must
 *       demap an entry beक्रमe re-mapping it.
 */
#घोषणा HV_FAST_PCI_IOMMU_MAP		0xb0

/* pci_iommu_demap()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_IOMMU_DEMAP
 * ARG0:	devhandle
 * ARG1:	tsbid
 * ARG2:	#ttes
 * RET0:	status
 * RET1:	#ttes demapped
 * ERRORS:	EINVAL		Invalid devhandle/tsbnum/tsbindex
 *
 * Demap and flush IOMMU mappings in the device defined by the given
 * devhandle.  Demaps up to #ttes entries in the TSB defined by the tsbnum
 * component of the given tsbid, starting at the TSB index defined by the
 * tsbindex component of the given tsbid.
 *
 * For this version of the spec, the tsbnum of the given tsbid must be zero.
 * #ttes must be greater than zero.
 *
 * Returns the actual number of ttes demapped, which may be less than or equal
 * to the argument #ttes.  If #ttes demapped is less than #ttes, the caller
 * may जारी to call this function with updated tsbid and #ttes arguments
 * until all pages are demapped.
 *
 * Note: Entries करो not have to be mapped to be demapped.  A demap of an
 *       unmapped page will flush the entry from the tte cache.
 */
#घोषणा HV_FAST_PCI_IOMMU_DEMAP		0xb1

/* pci_iommu_geपंचांगap()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_IOMMU_GETMAP
 * ARG0:	devhandle
 * ARG1:	tsbid
 * RET0:	status
 * RET1:	io_attributes
 * RET2:	real address
 * ERRORS:	EINVAL		Invalid devhandle/tsbnum/tsbindex
 *		ENOMAP		Mapping is not valid, no translation exists
 *
 * Read and वापस the mapping in the device described by the given devhandle
 * and tsbid.  If successful, the io_attributes shall be वापसed in RET1
 * and the page address of the mapping shall be वापसed in RET2.
 *
 * For this version of the spec, the tsbnum component of the given tsbid
 * must be zero.
 */
#घोषणा HV_FAST_PCI_IOMMU_GETMAP	0xb2

/* pci_iommu_getbypass()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_IOMMU_GETBYPASS
 * ARG0:	devhandle
 * ARG1:	real address
 * ARG2:	io_attributes
 * RET0:	status
 * RET1:	io_addr
 * ERRORS:	EINVAL		Invalid devhandle/io_attributes
 *		ENORADDR	Invalid real address
 *		ENOTSUPPORTED	Function not supported in this implementation.
 *
 * Create a "special" mapping in the device described by the given devhandle,
 * क्रम the given real address and attributes.  Return the IO address in RET1
 * अगर successful.
 */
#घोषणा HV_FAST_PCI_IOMMU_GETBYPASS	0xb3

/* pci_config_get()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_CONFIG_GET
 * ARG0:	devhandle
 * ARG1:	pci_device
 * ARG2:	pci_config_offset
 * ARG3:	size
 * RET0:	status
 * RET1:	error_flag
 * RET2:	data
 * ERRORS:	EINVAL		Invalid devhandle/pci_device/offset/size
 *		EBADALIGN	pci_config_offset not size aligned
 *		ENOACCESS	Access to this offset is not permitted
 *
 * Read PCI configuration space क्रम the adapter described by the given
 * devhandle.  Read size (1, 2, or 4) bytes of data from the given
 * pci_device, at pci_config_offset from the beginning of the device's
 * configuration space.  If there was no error, RET1 is set to zero and
 * RET2 is set to the data पढ़ो.  Insignअगरicant bits in RET2 are not
 * guaranteed to have any specअगरic value and thereक्रमe must be ignored.
 *
 * The data वापसed in RET2 is size based byte swapped.
 *
 * If an error occurs during the पढ़ो, set RET1 to a non-zero value.  The
 * given pci_config_offset must be 'size' aligned.
 */
#घोषणा HV_FAST_PCI_CONFIG_GET		0xb4

/* pci_config_put()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_CONFIG_PUT
 * ARG0:	devhandle
 * ARG1:	pci_device
 * ARG2:	pci_config_offset
 * ARG3:	size
 * ARG4:	data
 * RET0:	status
 * RET1:	error_flag
 * ERRORS:	EINVAL		Invalid devhandle/pci_device/offset/size
 *		EBADALIGN	pci_config_offset not size aligned
 *		ENOACCESS	Access to this offset is not permitted
 *
 * Write PCI configuration space क्रम the adapter described by the given
 * devhandle.  Write size (1, 2, or 4) bytes of data in a single operation,
 * at pci_config_offset from the beginning of the device's configuration
 * space.  The data argument contains the data to be written to configuration
 * space.  Prior to writing, the data is size based byte swapped.
 *
 * If an error occurs during the ग_लिखो access, करो not generate an error
 * report, करो set RET1 to a non-zero value.  Otherwise RET1 is zero.
 * The given pci_config_offset must be 'size' aligned.
 *
 * This function is permitted to पढ़ो from offset zero in the configuration
 * space described by the given pci_device अगर necessary to ensure that the
 * ग_लिखो access to config space completes.
 */
#घोषणा HV_FAST_PCI_CONFIG_PUT		0xb5

/* pci_peek()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_PEEK
 * ARG0:	devhandle
 * ARG1:	real address
 * ARG2:	size
 * RET0:	status
 * RET1:	error_flag
 * RET2:	data
 * ERRORS:	EINVAL		Invalid devhandle or size
 *		EBADALIGN	Improperly aligned real address
 *		ENORADDR	Bad real address
 *		ENOACCESS	Guest access prohibited
 *
 * Attempt to पढ़ो the IO address given by the given devhandle, real address,
 * and size.  Size must be 1, 2, 4, or 8.  The पढ़ो is perक्रमmed as a single
 * access operation using the given size.  If an error occurs when पढ़ोing
 * from the given location, करो not generate an error report, but वापस a
 * non-zero value in RET1.  If the पढ़ो was successful, वापस zero in RET1
 * and वापस the actual data पढ़ो in RET2.  The data वापसed is size based
 * byte swapped.
 *
 * Non-signअगरicant bits in RET2 are not guaranteed to have any specअगरic value
 * and thereक्रमe must be ignored.  If RET1 is वापसed as non-zero, the data
 * value is not guaranteed to have any specअगरic value and should be ignored.
 *
 * The caller must have permission to पढ़ो from the given devhandle, real
 * address, which must be an IO address.  The argument real address must be a
 * size aligned address.
 *
 * The hypervisor implementation of this function must block access to any
 * IO address that the guest करोes not have explicit permission to access.
 */
#घोषणा HV_FAST_PCI_PEEK		0xb6

/* pci_poke()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_POKE
 * ARG0:	devhandle
 * ARG1:	real address
 * ARG2:	size
 * ARG3:	data
 * ARG4:	pci_device
 * RET0:	status
 * RET1:	error_flag
 * ERRORS:	EINVAL		Invalid devhandle, size, or pci_device
 *		EBADALIGN	Improperly aligned real address
 *		ENORADDR	Bad real address
 *		ENOACCESS	Guest access prohibited
 *		ENOTSUPPORTED	Function is not supported by implementation
 *
 * Attempt to ग_लिखो data to the IO address given by the given devhandle,
 * real address, and size.  Size must be 1, 2, 4, or 8.  The ग_लिखो is
 * perक्रमmed as a single access operation using the given size. Prior to
 * writing the data is size based swapped.
 *
 * If an error occurs when writing to the given location, करो not generate an
 * error report, but वापस a non-zero value in RET1.  If the ग_लिखो was
 * successful, वापस zero in RET1.
 *
 * pci_device describes the configuration address of the device being
 * written to.  The implementation may safely पढ़ो from offset 0 with
 * the configuration space of the device described by devhandle and
 * pci_device in order to guarantee that the ग_लिखो portion of the operation
 * completes
 *
 * Any error that occurs due to the पढ़ो shall be reported using the normal
 * error reporting mechanisms .. the पढ़ो error is not suppressed.
 *
 * The caller must have permission to ग_लिखो to the given devhandle, real
 * address, which must be an IO address.  The argument real address must be a
 * size aligned address.  The caller must have permission to पढ़ो from
 * the given devhandle, pci_device cofiguration space offset 0.
 *
 * The hypervisor implementation of this function must block access to any
 * IO address that the guest करोes not have explicit permission to access.
 */
#घोषणा HV_FAST_PCI_POKE		0xb7

/* pci_dma_sync()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_DMA_SYNC
 * ARG0:	devhandle
 * ARG1:	real address
 * ARG2:	size
 * ARG3:	io_sync_direction
 * RET0:	status
 * RET1:	#synced
 * ERRORS:	EINVAL		Invalid devhandle or io_sync_direction
 *		ENORADDR	Bad real address
 *
 * Synchronize a memory region described by the given real address and size,
 * क्रम the device defined by the given devhandle using the direction(s)
 * defined by the given io_sync_direction.  The argument size is the size of
 * the memory region in bytes.
 *
 * Return the actual number of bytes synchronized in the वापस value #synced,
 * which may be less than or equal to the argument size.  If the वापस
 * value #synced is less than size, the caller must जारी to call this
 * function with updated real address and size arguments until the entire
 * memory region is synchronized.
 */
#घोषणा HV_FAST_PCI_DMA_SYNC		0xb8

/* PCI MSI services.  */

#घोषणा HV_MSITYPE_MSI32		0x00
#घोषणा HV_MSITYPE_MSI64		0x01

#घोषणा HV_MSIQSTATE_IDLE		0x00
#घोषणा HV_MSIQSTATE_ERROR		0x01

#घोषणा HV_MSIQ_INVALID			0x00
#घोषणा HV_MSIQ_VALID			0x01

#घोषणा HV_MSISTATE_IDLE		0x00
#घोषणा HV_MSISTATE_DELIVERED		0x01

#घोषणा HV_MSIVALID_INVALID		0x00
#घोषणा HV_MSIVALID_VALID		0x01

#घोषणा HV_PCIE_MSGTYPE_PME_MSG		0x18
#घोषणा HV_PCIE_MSGTYPE_PME_ACK_MSG	0x1b
#घोषणा HV_PCIE_MSGTYPE_CORR_MSG	0x30
#घोषणा HV_PCIE_MSGTYPE_NONFATAL_MSG	0x31
#घोषणा HV_PCIE_MSGTYPE_FATAL_MSG	0x33

#घोषणा HV_MSG_INVALID			0x00
#घोषणा HV_MSG_VALID			0x01

/* pci_msiq_conf()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_CONF
 * ARG0:	devhandle
 * ARG1:	msiqid
 * ARG2:	real address
 * ARG3:	number of entries
 * RET0:	status
 * ERRORS:	EINVAL		Invalid devhandle, msiqid or nentries
 *		EBADALIGN	Improperly aligned real address
 *		ENORADDR	Bad real address
 *
 * Configure the MSI queue given by the devhandle and msiqid arguments,
 * and to be placed at the given real address and be of the given
 * number of entries.  The real address must be aligned exactly to match
 * the queue size.  Each queue entry is 64-bytes दीर्घ, so f.e. a 32 entry
 * queue must be aligned on a 2048 byte real address boundary.  The MSI-EQ
 * Head and Tail are initialized so that the MSI-EQ is 'empty'.
 *
 * Implementation Note: Certain implementations have fixed sized queues.  In
 *                      that हाल, number of entries must contain the correct
 *                      value.
 */
#घोषणा HV_FAST_PCI_MSIQ_CONF		0xc0

/* pci_msiq_info()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_INFO
 * ARG0:	devhandle
 * ARG1:	msiqid
 * RET0:	status
 * RET1:	real address
 * RET2:	number of entries
 * ERRORS:	EINVAL		Invalid devhandle or msiqid
 *
 * Return the configuration inक्रमmation क्रम the MSI queue described
 * by the given devhandle and msiqid.  The base address of the queue
 * is वापसed in ARG1 and the number of entries is वापसed in ARG2.
 * If the queue is unconfigured, the real address is undefined and the
 * number of entries will be वापसed as zero.
 */
#घोषणा HV_FAST_PCI_MSIQ_INFO		0xc1

/* pci_msiq_getvalid()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_GETVALID
 * ARG0:	devhandle
 * ARG1:	msiqid
 * RET0:	status
 * RET1:	msiqvalid	(HV_MSIQ_VALID or HV_MSIQ_INVALID)
 * ERRORS:	EINVAL		Invalid devhandle or msiqid
 *
 * Get the valid state of the MSI-EQ described by the given devhandle and
 * msiqid.
 */
#घोषणा HV_FAST_PCI_MSIQ_GETVALID	0xc2

/* pci_msiq_setvalid()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_SETVALID
 * ARG0:	devhandle
 * ARG1:	msiqid
 * ARG2:	msiqvalid	(HV_MSIQ_VALID or HV_MSIQ_INVALID)
 * RET0:	status
 * ERRORS:	EINVAL		Invalid devhandle or msiqid or msiqvalid
 *				value or MSI EQ is uninitialized
 *
 * Set the valid state of the MSI-EQ described by the given devhandle and
 * msiqid to the given msiqvalid.
 */
#घोषणा HV_FAST_PCI_MSIQ_SETVALID	0xc3

/* pci_msiq_माला_लोtate()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_GETSTATE
 * ARG0:	devhandle
 * ARG1:	msiqid
 * RET0:	status
 * RET1:	msiqstate	(HV_MSIQSTATE_IDLE or HV_MSIQSTATE_ERROR)
 * ERRORS:	EINVAL		Invalid devhandle or msiqid
 *
 * Get the state of the MSI-EQ described by the given devhandle and
 * msiqid.
 */
#घोषणा HV_FAST_PCI_MSIQ_GETSTATE	0xc4

/* pci_msiq_getvalid()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_GETVALID
 * ARG0:	devhandle
 * ARG1:	msiqid
 * ARG2:	msiqstate	(HV_MSIQSTATE_IDLE or HV_MSIQSTATE_ERROR)
 * RET0:	status
 * ERRORS:	EINVAL		Invalid devhandle or msiqid or msiqstate
 *				value or MSI EQ is uninitialized
 *
 * Set the state of the MSI-EQ described by the given devhandle and
 * msiqid to the given msiqvalid.
 */
#घोषणा HV_FAST_PCI_MSIQ_SETSTATE	0xc5

/* pci_msiq_gethead()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_GETHEAD
 * ARG0:	devhandle
 * ARG1:	msiqid
 * RET0:	status
 * RET1:	msiqhead
 * ERRORS:	EINVAL		Invalid devhandle or msiqid
 *
 * Get the current MSI EQ queue head क्रम the MSI-EQ described by the
 * given devhandle and msiqid.
 */
#घोषणा HV_FAST_PCI_MSIQ_GETHEAD	0xc6

/* pci_msiq_sethead()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_SETHEAD
 * ARG0:	devhandle
 * ARG1:	msiqid
 * ARG2:	msiqhead
 * RET0:	status
 * ERRORS:	EINVAL		Invalid devhandle or msiqid or msiqhead,
 *				or MSI EQ is uninitialized
 *
 * Set the current MSI EQ queue head क्रम the MSI-EQ described by the
 * given devhandle and msiqid.
 */
#घोषणा HV_FAST_PCI_MSIQ_SETHEAD	0xc7

/* pci_msiq_gettail()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_GETTAIL
 * ARG0:	devhandle
 * ARG1:	msiqid
 * RET0:	status
 * RET1:	msiqtail
 * ERRORS:	EINVAL		Invalid devhandle or msiqid
 *
 * Get the current MSI EQ queue tail क्रम the MSI-EQ described by the
 * given devhandle and msiqid.
 */
#घोषणा HV_FAST_PCI_MSIQ_GETTAIL	0xc8

/* pci_msi_getvalid()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSI_GETVALID
 * ARG0:	devhandle
 * ARG1:	msinum
 * RET0:	status
 * RET1:	msivalidstate
 * ERRORS:	EINVAL		Invalid devhandle or msinum
 *
 * Get the current valid/enabled state क्रम the MSI defined by the
 * given devhandle and msinum.
 */
#घोषणा HV_FAST_PCI_MSI_GETVALID	0xc9

/* pci_msi_setvalid()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSI_SETVALID
 * ARG0:	devhandle
 * ARG1:	msinum
 * ARG2:	msivalidstate
 * RET0:	status
 * ERRORS:	EINVAL		Invalid devhandle or msinum or msivalidstate
 *
 * Set the current valid/enabled state क्रम the MSI defined by the
 * given devhandle and msinum.
 */
#घोषणा HV_FAST_PCI_MSI_SETVALID	0xca

/* pci_msi_geपंचांगsiq()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSI_GETMSIQ
 * ARG0:	devhandle
 * ARG1:	msinum
 * RET0:	status
 * RET1:	msiqid
 * ERRORS:	EINVAL		Invalid devhandle or msinum or MSI is unbound
 *
 * Get the MSI EQ that the MSI defined by the given devhandle and
 * msinum is bound to.
 */
#घोषणा HV_FAST_PCI_MSI_GETMSIQ		0xcb

/* pci_msi_seपंचांगsiq()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSI_SETMSIQ
 * ARG0:	devhandle
 * ARG1:	msinum
 * ARG2:	msitype
 * ARG3:	msiqid
 * RET0:	status
 * ERRORS:	EINVAL		Invalid devhandle or msinum or msiqid
 *
 * Set the MSI EQ that the MSI defined by the given devhandle and
 * msinum is bound to.
 */
#घोषणा HV_FAST_PCI_MSI_SETMSIQ		0xcc

/* pci_msi_माला_लोtate()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSI_GETSTATE
 * ARG0:	devhandle
 * ARG1:	msinum
 * RET0:	status
 * RET1:	msistate
 * ERRORS:	EINVAL		Invalid devhandle or msinum
 *
 * Get the state of the MSI defined by the given devhandle and msinum.
 * If not initialized, वापस HV_MSISTATE_IDLE.
 */
#घोषणा HV_FAST_PCI_MSI_GETSTATE	0xcd

/* pci_msi_setstate()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSI_SETSTATE
 * ARG0:	devhandle
 * ARG1:	msinum
 * ARG2:	msistate
 * RET0:	status
 * ERRORS:	EINVAL		Invalid devhandle or msinum or msistate
 *
 * Set the state of the MSI defined by the given devhandle and msinum.
 */
#घोषणा HV_FAST_PCI_MSI_SETSTATE	0xce

/* pci_msg_geपंचांगsiq()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSG_GETMSIQ
 * ARG0:	devhandle
 * ARG1:	msgtype
 * RET0:	status
 * RET1:	msiqid
 * ERRORS:	EINVAL		Invalid devhandle or msgtype
 *
 * Get the MSI EQ of the MSG defined by the given devhandle and msgtype.
 */
#घोषणा HV_FAST_PCI_MSG_GETMSIQ		0xd0

/* pci_msg_seपंचांगsiq()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSG_SETMSIQ
 * ARG0:	devhandle
 * ARG1:	msgtype
 * ARG2:	msiqid
 * RET0:	status
 * ERRORS:	EINVAL		Invalid devhandle, msgtype, or msiqid
 *
 * Set the MSI EQ of the MSG defined by the given devhandle and msgtype.
 */
#घोषणा HV_FAST_PCI_MSG_SETMSIQ		0xd1

/* pci_msg_getvalid()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSG_GETVALID
 * ARG0:	devhandle
 * ARG1:	msgtype
 * RET0:	status
 * RET1:	msgvalidstate
 * ERRORS:	EINVAL		Invalid devhandle or msgtype
 *
 * Get the valid/enabled state of the MSG defined by the given
 * devhandle and msgtype.
 */
#घोषणा HV_FAST_PCI_MSG_GETVALID	0xd2

/* pci_msg_setvalid()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_MSG_SETVALID
 * ARG0:	devhandle
 * ARG1:	msgtype
 * ARG2:	msgvalidstate
 * RET0:	status
 * ERRORS:	EINVAL		Invalid devhandle or msgtype or msgvalidstate
 *
 * Set the valid/enabled state of the MSG defined by the given
 * devhandle and msgtype.
 */
#घोषणा HV_FAST_PCI_MSG_SETVALID	0xd3

/* PCI IOMMU v2 definitions and services
 *
 * While the PCI IO definitions above is valid IOMMU v2 adds new PCI IO
 * definitions and services.
 *
 *	CTE		Clump Table Entry. First level table entry in the ATU.
 *
 *	pci_device_list
 *			A 32-bit aligned list of pci_devices.
 *
 *	pci_device_listp
 *			real address of a pci_device_list. 32-bit aligned.
 *
 *	iotte		IOMMU translation table entry.
 *
 *	iotte_attributes
 *			IO Attributes क्रम IOMMU v2 mappings. In addition to
 *			पढ़ो, ग_लिखो IOMMU v2 supports relax ordering
 *
 *	io_page_list	A 64-bit aligned list of real addresses. Each real
 *			address in an io_page_list must be properly aligned
 *			to the pagesize of the given IOTSB.
 *
 *	io_page_list_p	Real address of an io_page_list, 64-bit aligned.
 *
 *	IOTSB		IO Translation Storage Buffer. An aligned table of
 *			IOTTEs. Each IOTSB has a pagesize, table size, and
 *			भव address associated with it that must match
 *			a pagesize and table size supported by the un-derlying
 *			hardware implementation. The alignment requirements
 *			क्रम an IOTSB depend on the pagesize used क्रम that IOTSB.
 *			Each IOTTE in an IOTSB maps one pagesize-sized page.
 *			The size of the IOTSB dictates how large of a भव
 *			address space the IOTSB is capable of mapping.
 *
 *	iotsb_handle	An opaque identअगरier क्रम an IOTSB. A devhandle plus
 *			iotsb_handle represents a binding of an IOTSB to a
 *			PCI root complex.
 *
 *	iotsb_index	Zero-based IOTTE number within an IOTSB.
 */

/* The index_count argument consists of two fields:
 * bits 63:48 #iottes and bits 47:0 iotsb_index
 */
#घोषणा HV_PCI_IOTSB_INDEX_COUNT(__iottes, __iotsb_index) \
	(((u64)(__iottes) << 48UL) | ((u64)(__iotsb_index)))

/* pci_iotsb_conf()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_CONF
 * ARG0:	devhandle
 * ARG1:	r_addr
 * ARG2:	size
 * ARG3:	pagesize
 * ARG4:	iova
 * RET0:	status
 * RET1:	iotsb_handle
 * ERRORS:	EINVAL		Invalid devhandle, size, iova, or pagesize
 *		EBADALIGN	r_addr is not properly aligned
 *		ENORADDR	r_addr is not a valid real address
 *		ETOOMANY	No further IOTSBs may be configured
 *		EBUSY		Duplicate devhandle, raddir, iova combination
 *
 * Create an IOTSB suitable क्रम the PCI root complex identअगरied by devhandle,
 * क्रम the DMA भव address defined by the argument iova.
 *
 * r_addr is the properly aligned base address of the IOTSB and size is the
 * IOTSB (table) size in bytes.The IOTSB is required to be zeroed prior to
 * being configured. If it contains any values other than zeros then the
 * behavior is undefined.
 *
 * pagesize is the size of each page in the IOTSB. Note that the combination of
 * size (table size) and pagesize must be valid.
 *
 * virt is the DMA भव address this IOTSB will map.
 *
 * If successful, the opaque 64-bit handle iotsb_handle is वापसed in ret1.
 * Once configured, privileged access to the IOTSB memory is prohibited and
 * creates undefined behavior. The only permitted access is indirect via these
 * services.
 */
#घोषणा HV_FAST_PCI_IOTSB_CONF		0x190

/* pci_iotsb_info()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_INFO
 * ARG0:	devhandle
 * ARG1:	iotsb_handle
 * RET0:	status
 * RET1:	r_addr
 * RET2:	size
 * RET3:	pagesize
 * RET4:	iova
 * RET5:	#bound
 * ERRORS:	EINVAL	Invalid devhandle or iotsb_handle
 *
 * This service वापसs configuration inक्रमmation about an IOTSB previously
 * created with pci_iotsb_conf.
 *
 * iotsb_handle value 0 may be used with this service to inquire about the
 * legacy IOTSB that may or may not exist. If the service succeeds, the वापस
 * values describe the legacy IOTSB and I/O भव addresses mapped by that
 * table. However, the table base address r_addr may contain the value -1 which
 * indicates a memory range that cannot be accessed or be reclaimed.
 *
 * The वापस value #bound contains the number of PCI devices that iotsb_handle
 * is currently bound to.
 */
#घोषणा HV_FAST_PCI_IOTSB_INFO		0x191

/* pci_iotsb_unconf()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_UNCONF
 * ARG0:	devhandle
 * ARG1:	iotsb_handle
 * RET0:	status
 * ERRORS:	EINVAL	Invalid devhandle or iotsb_handle
 *		EBUSY	The IOTSB is bound and may not be unconfigured
 *
 * This service unconfigures the IOTSB identअगरied by the devhandle and
 * iotsb_handle arguments, previously created with pci_iotsb_conf.
 * The IOTSB must not be currently bound to any device or the service will fail
 *
 * If the call succeeds, iotsb_handle is no दीर्घer valid.
 */
#घोषणा HV_FAST_PCI_IOTSB_UNCONF	0x192

/* pci_iotsb_bind()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_BIND
 * ARG0:	devhandle
 * ARG1:	iotsb_handle
 * ARG2:	pci_device
 * RET0:	status
 * ERRORS:	EINVAL	Invalid devhandle, iotsb_handle, or pci_device
 *		EBUSY	A PCI function is alपढ़ोy bound to an IOTSB at the same
 *			address range as specअगरied by devhandle, iotsb_handle.
 *
 * This service binds the PCI function specअगरied by the argument pci_device to
 * the IOTSB specअगरied by the arguments devhandle and iotsb_handle.
 *
 * The PCI device function is bound to the specअगरied IOTSB with the IOVA range
 * specअगरied when the IOTSB was configured via pci_iotsb_conf. If the function
 * is alपढ़ोy bound then it is unbound first.
 */
#घोषणा HV_FAST_PCI_IOTSB_BIND		0x193

/* pci_iotsb_unbind()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_UNBIND
 * ARG0:	devhandle
 * ARG1:	iotsb_handle
 * ARG2:	pci_device
 * RET0:	status
 * ERRORS:	EINVAL	Invalid devhandle, iotsb_handle, or pci_device
 *		ENOMAP	The PCI function was not bound to the specअगरied IOTSB
 *
 * This service unbinds the PCI device specअगरied by the argument pci_device
 * from the IOTSB identअगरied  * by the arguments devhandle and iotsb_handle.
 *
 * If the PCI device is not bound to the specअगरied IOTSB then this service will
 * fail with status ENOMAP
 */
#घोषणा HV_FAST_PCI_IOTSB_UNBIND	0x194

/* pci_iotsb_get_binding()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_GET_BINDING
 * ARG0:	devhandle
 * ARG1:	iotsb_handle
 * ARG2:	iova
 * RET0:	status
 * RET1:	iotsb_handle
 * ERRORS:	EINVAL	Invalid devhandle, pci_device, or iova
 *		ENOMAP	The PCI function is not bound to an IOTSB at iova
 *
 * This service वापसs the IOTSB binding, iotsb_handle, क्रम a given pci_device
 * and DMA भव address, iova.
 *
 * iova must be the base address of a DMA भव address range as defined by
 * the iommu-address-ranges property in the root complex device node defined
 * by the argument devhandle.
 */
#घोषणा HV_FAST_PCI_IOTSB_GET_BINDING	0x195

/* pci_iotsb_map()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_MAP
 * ARG0:	devhandle
 * ARG1:	iotsb_handle
 * ARG2:	index_count
 * ARG3:	iotte_attributes
 * ARG4:	io_page_list_p
 * RET0:	status
 * RET1:	#mapped
 * ERRORS:	EINVAL		Invalid devhandle, iotsb_handle, #iottes,
 *				iotsb_index or iotte_attributes
 *		EBADALIGN	Improperly aligned io_page_list_p or I/O page
 *				address in the I/O page list.
 *		ENORADDR	Invalid io_page_list_p or I/O page address in
 *				the I/O page list.
 *
 * This service creates and flushes mappings in the IOTSB defined by the
 * arguments devhandle, iotsb.
 *
 * The index_count argument consists of two fields. Bits 63:48 contain #iotte
 * and bits 47:0 contain iotsb_index
 *
 * The first mapping is created in the IOTSB index specअगरied by iotsb_index.
 * Subsequent mappings are  created at iotsb_index+1 and so on.
 *
 * The attributes of each mapping are defined by the argument iotte_attributes.
 *
 * The io_page_list_p specअगरies the real address of the 64-bit-aligned list of
 * #iottes I/O page addresses. Each page address must be a properly aligned
 * real address of a page to be mapped in the IOTSB. The first entry in the I/O
 * page list contains the real address of the first page, the 2nd entry क्रम the
 * 2nd page, and so on.
 *
 * #iottes must be greater than zero.
 *
 * The वापस value #mapped is the actual number of mappings created, which may
 * be less than or equal to the argument #iottes. If the function वापसs
 * successfully with a #mapped value less than the requested #iottes then the
 * caller should जारी to invoke the service with updated iotsb_index,
 * #iottes, and io_page_list_p arguments until all pages are mapped.
 *
 * This service must not be used to demap a mapping. In other words, all
 * mappings must be valid and have  one or both of the RW attribute bits set.
 *
 * Note:
 * It is implementation-defined whether I/O page real address validity checking
 * is करोne at समय mappings are established or deferred until they are
 * accessed.
 */
#घोषणा HV_FAST_PCI_IOTSB_MAP		0x196

/* pci_iotsb_map_one()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_MAP_ONE
 * ARG0:	devhandle
 * ARG1:	iotsb_handle
 * ARG2:	iotsb_index
 * ARG3:	iotte_attributes
 * ARG4:	r_addr
 * RET0:	status
 * ERRORS:	EINVAL		Invalid devhandle,iotsb_handle, iotsb_index
 *				or iotte_attributes
 *		EBADALIGN	Improperly aligned r_addr
 *		ENORADDR	Invalid r_addr
 *
 * This service creates and flushes a single mapping in the IOTSB defined by the
 * arguments devhandle, iotsb.
 *
 * The mapping क्रम the page at r_addr is created at the IOTSB index specअगरied by
 * iotsb_index with  the attributes iotte_attributes.
 *
 * This service must not be used to demap a mapping. In other words, the mapping
 * must be valid and have one or both of the RW attribute bits set.
 *
 * Note:
 * It is implementation-defined whether I/O page real address validity checking
 * is करोne at समय mappings are established or deferred until they are
 * accessed.
 */
#घोषणा HV_FAST_PCI_IOTSB_MAP_ONE	0x197

/* pci_iotsb_demap()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_DEMAP
 * ARG0:	devhandle
 * ARG1:	iotsb_handle
 * ARG2:	iotsb_index
 * ARG3:	#iottes
 * RET0:	status
 * RET1:	#unmapped
 * ERRORS:	EINVAL	Invalid devhandle, iotsb_handle, iotsb_index or #iottes
 *
 * This service unmaps and flushes up to #iottes mappings starting at index
 * iotsb_index from the IOTSB defined by the arguments devhandle, iotsb.
 *
 * #iottes must be greater than zero.
 *
 * The actual number of IOTTEs unmapped is वापसed in #unmapped and may be less
 * than or equal to the requested number of IOTTEs, #iottes.
 *
 * If #unmapped is less than #iottes, the caller should जारी to invoke this
 * service with updated iotsb_index and #iottes arguments until all pages are
 * demapped.
 */
#घोषणा HV_FAST_PCI_IOTSB_DEMAP		0x198

/* pci_iotsb_geपंचांगap()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_GETMAP
 * ARG0:	devhandle
 * ARG1:	iotsb_handle
 * ARG2:	iotsb_index
 * RET0:	status
 * RET1:	r_addr
 * RET2:	iotte_attributes
 * ERRORS:	EINVAL	Invalid devhandle, iotsb_handle, or iotsb_index
 *		ENOMAP	No mapping was found
 *
 * This service वापसs the mapping specअगरied by index iotsb_index from the
 * IOTSB defined by the arguments devhandle, iotsb.
 *
 * Upon success, the real address of the mapping shall be वापसed in
 * r_addr and thethe IOTTE mapping attributes shall be वापसed in
 * iotte_attributes.
 *
 * The वापस value iotte_attributes may not include optional features used in
 * the call to create the  mapping.
 */
#घोषणा HV_FAST_PCI_IOTSB_GETMAP	0x199

/* pci_iotsb_sync_mappings()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_SYNC_MAPPINGS
 * ARG0:	devhandle
 * ARG1:	iotsb_handle
 * ARG2:	iotsb_index
 * ARG3:	#iottes
 * RET0:	status
 * RET1:	#synced
 * ERROS:	EINVAL	Invalid devhandle, iotsb_handle, iotsb_index, or #iottes
 *
 * This service synchronizes #iottes mappings starting at index iotsb_index in
 * the IOTSB defined by the arguments devhandle, iotsb.
 *
 * #iottes must be greater than zero.
 *
 * The actual number of IOTTEs synchronized is वापसed in #synced, which may
 * be less than or equal to the requested number, #iottes.
 *
 * Upon a successful वापस, #synced is less than #iottes, the caller should
 * जारी to invoke this service with updated iotsb_index and #iottes
 * arguments until all pages are synchronized.
 */
#घोषणा HV_FAST_PCI_IOTSB_SYNC_MAPPINGS	0x19a

/* Logical Doमुख्य Channel services.  */

#घोषणा LDC_CHANNEL_DOWN		0
#घोषणा LDC_CHANNEL_UP			1
#घोषणा LDC_CHANNEL_RESETTING		2

/* ldc_tx_qconf()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_LDC_TX_QCONF
 * ARG0:	channel ID
 * ARG1:	real address base of queue
 * ARG2:	num entries in queue
 * RET0:	status
 *
 * Configure transmit queue क्रम the LDC endpoपूर्णांक specअगरied by the
 * given channel ID, to be placed at the given real address, and
 * be of the given num entries.  Num entries must be a घातer of two.
 * The real address base of the queue must be aligned on the queue
 * size.  Each queue entry is 64-bytes, so क्रम example, a 32 entry
 * queue must be aligned on a 2048 byte real address boundary.
 *
 * Upon configuration of a valid transmit queue the head and tail
 * poपूर्णांकers are set to a hypervisor specअगरic identical value indicating
 * that the queue initially is empty.
 *
 * The endpoपूर्णांक's transmit queue is un-configured अगर num entries is zero.
 *
 * The maximum number of entries क्रम each queue क्रम a specअगरic cpu may be
 * determined from the machine description.  A transmit queue may be
 * specअगरied even in the event that the LDC is करोwn (peer endpoपूर्णांक has no
 * receive queue specअगरied).  Transmission will begin as soon as the peer
 * endpoपूर्णांक defines a receive queue.
 *
 * It is recommended that a guest रुको क्रम a transmit queue to empty prior
 * to reconfiguring it, or un-configuring it.  Re or un-configuring of a
 * non-empty transmit queue behaves exactly as defined above, however it
 * is undefined as to how many of the pending entries in the original queue
 * will be delivered prior to the re-configuration taking effect.
 * Furthermore, as the queue configuration causes a reset of the head and
 * tail poपूर्णांकers there is no way क्रम a guest to determine how many entries
 * have been sent after the configuration operation.
 */
#घोषणा HV_FAST_LDC_TX_QCONF		0xe0

/* ldc_tx_qinfo()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_LDC_TX_QINFO
 * ARG0:	channel ID
 * RET0:	status
 * RET1:	real address base of queue
 * RET2:	num entries in queue
 *
 * Return the configuration info क्रम the transmit queue of LDC endpoपूर्णांक
 * defined by the given channel ID.  The real address is the currently
 * defined real address base of the defined queue, and num entries is the
 * size of the queue in terms of number of entries.
 *
 * If the specअगरied channel ID is a valid endpoपूर्णांक number, but no transmit
 * queue has been defined this service will वापस success, but with num
 * entries set to zero and the real address will have an undefined value.
 */
#घोषणा HV_FAST_LDC_TX_QINFO		0xe1

/* ldc_tx_get_state()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_LDC_TX_GET_STATE
 * ARG0:	channel ID
 * RET0:	status
 * RET1:	head offset
 * RET2:	tail offset
 * RET3:	channel state
 *
 * Return the transmit state, and the head and tail queue poपूर्णांकers, क्रम
 * the transmit queue of the LDC endpoपूर्णांक defined by the given channel ID.
 * The head and tail values are the byte offset of the head and tail
 * positions of the transmit queue क्रम the specअगरied endpoपूर्णांक.
 */
#घोषणा HV_FAST_LDC_TX_GET_STATE	0xe2

/* ldc_tx_set_qtail()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_LDC_TX_SET_QTAIL
 * ARG0:	channel ID
 * ARG1:	tail offset
 * RET0:	status
 *
 * Update the tail poपूर्णांकer क्रम the transmit queue associated with the LDC
 * endpoपूर्णांक defined by the given channel ID.  The tail offset specअगरied
 * must be aligned on a 64 byte boundary, and calculated so as to increase
 * the number of pending entries on the transmit queue.  Any attempt to
 * decrease the number of pending transmit queue entires is considered
 * an invalid tail offset and will result in an EINVAL error.
 *
 * Since the tail of the transmit queue may not be moved backwards, the
 * transmit queue may be flushed by configuring a new transmit queue,
 * whereupon the hypervisor will configure the initial transmit head and
 * tail poपूर्णांकers to be equal.
 */
#घोषणा HV_FAST_LDC_TX_SET_QTAIL	0xe3

/* ldc_rx_qconf()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_LDC_RX_QCONF
 * ARG0:	channel ID
 * ARG1:	real address base of queue
 * ARG2:	num entries in queue
 * RET0:	status
 *
 * Configure receive queue क्रम the LDC endpoपूर्णांक specअगरied by the
 * given channel ID, to be placed at the given real address, and
 * be of the given num entries.  Num entries must be a घातer of two.
 * The real address base of the queue must be aligned on the queue
 * size.  Each queue entry is 64-bytes, so क्रम example, a 32 entry
 * queue must be aligned on a 2048 byte real address boundary.
 *
 * The endpoपूर्णांक's transmit queue is un-configured अगर num entries is zero.
 *
 * If a valid receive queue is specअगरied क्रम a local endpoपूर्णांक the LDC is
 * in the up state क्रम the purpose of transmission to this endpoपूर्णांक.
 *
 * The maximum number of entries क्रम each queue क्रम a specअगरic cpu may be
 * determined from the machine description.
 *
 * As receive queue configuration causes a reset of the queue's head and
 * tail poपूर्णांकers there is no way क्रम a gues to determine how many entries
 * have been received between a preceding ldc_get_rx_state() API call
 * and the completion of the configuration operation.  It should be noted
 * that datagram delivery is not guaranteed via करोमुख्य channels anyway,
 * and thereक्रमe any higher protocol should be resilient to datagram
 * loss अगर necessary.  However, to overcome this specअगरic race potential
 * it is recommended, क्रम example, that a higher level protocol be employed
 * to ensure either retransmission, or ensure that no datagrams are pending
 * on the peer endpoपूर्णांक's transmit queue prior to the configuration process.
 */
#घोषणा HV_FAST_LDC_RX_QCONF		0xe4

/* ldc_rx_qinfo()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_LDC_RX_QINFO
 * ARG0:	channel ID
 * RET0:	status
 * RET1:	real address base of queue
 * RET2:	num entries in queue
 *
 * Return the configuration info क्रम the receive queue of LDC endpoपूर्णांक
 * defined by the given channel ID.  The real address is the currently
 * defined real address base of the defined queue, and num entries is the
 * size of the queue in terms of number of entries.
 *
 * If the specअगरied channel ID is a valid endpoपूर्णांक number, but no receive
 * queue has been defined this service will वापस success, but with num
 * entries set to zero and the real address will have an undefined value.
 */
#घोषणा HV_FAST_LDC_RX_QINFO		0xe5

/* ldc_rx_get_state()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_LDC_RX_GET_STATE
 * ARG0:	channel ID
 * RET0:	status
 * RET1:	head offset
 * RET2:	tail offset
 * RET3:	channel state
 *
 * Return the receive state, and the head and tail queue poपूर्णांकers, क्रम
 * the receive queue of the LDC endpoपूर्णांक defined by the given channel ID.
 * The head and tail values are the byte offset of the head and tail
 * positions of the receive queue क्रम the specअगरied endpoपूर्णांक.
 */
#घोषणा HV_FAST_LDC_RX_GET_STATE	0xe6

/* ldc_rx_set_qhead()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_LDC_RX_SET_QHEAD
 * ARG0:	channel ID
 * ARG1:	head offset
 * RET0:	status
 *
 * Update the head poपूर्णांकer क्रम the receive queue associated with the LDC
 * endpoपूर्णांक defined by the given channel ID.  The head offset specअगरied
 * must be aligned on a 64 byte boundary, and calculated so as to decrease
 * the number of pending entries on the receive queue.  Any attempt to
 * increase the number of pending receive queue entires is considered
 * an invalid head offset and will result in an EINVAL error.
 *
 * The receive queue may be flushed by setting the head offset equal
 * to the current tail offset.
 */
#घोषणा HV_FAST_LDC_RX_SET_QHEAD	0xe7

/* LDC Map Table Entry.  Each slot is defined by a translation table
 * entry, as specअगरied by the LDC_MTE_* bits below, and a 64-bit
 * hypervisor invalidation cookie.
 */
#घोषणा LDC_MTE_PADDR	0x0fffffffffffe000 /* pa[55:13]          */
#घोषणा LDC_MTE_COPY_W	0x0000000000000400 /* copy ग_लिखो access  */
#घोषणा LDC_MTE_COPY_R	0x0000000000000200 /* copy पढ़ो access   */
#घोषणा LDC_MTE_IOMMU_W	0x0000000000000100 /* IOMMU ग_लिखो access */
#घोषणा LDC_MTE_IOMMU_R	0x0000000000000080 /* IOMMU पढ़ो access  */
#घोषणा LDC_MTE_EXEC	0x0000000000000040 /* execute            */
#घोषणा LDC_MTE_WRITE	0x0000000000000020 /* पढ़ो               */
#घोषणा LDC_MTE_READ	0x0000000000000010 /* ग_लिखो              */
#घोषणा LDC_MTE_SZALL	0x000000000000000f /* page size bits     */
#घोषणा LDC_MTE_SZ16GB	0x0000000000000007 /* 16GB page          */
#घोषणा LDC_MTE_SZ2GB	0x0000000000000006 /* 2GB page           */
#घोषणा LDC_MTE_SZ256MB	0x0000000000000005 /* 256MB page         */
#घोषणा LDC_MTE_SZ32MB	0x0000000000000004 /* 32MB page          */
#घोषणा LDC_MTE_SZ4MB	0x0000000000000003 /* 4MB page           */
#घोषणा LDC_MTE_SZ512K	0x0000000000000002 /* 512K page          */
#घोषणा LDC_MTE_SZ64K	0x0000000000000001 /* 64K page           */
#घोषणा LDC_MTE_SZ8K	0x0000000000000000 /* 8K page            */

#अगर_अघोषित __ASSEMBLY__
काष्ठा ldc_mtable_entry अणु
	अचिन्हित दीर्घ	mte;
	अचिन्हित दीर्घ	cookie;
पूर्ण;
#पूर्ण_अगर

/* ldc_set_map_table()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_LDC_SET_MAP_TABLE
 * ARG0:	channel ID
 * ARG1:	table real address
 * ARG2:	num entries
 * RET0:	status
 *
 * Register the MTE table at the given table real address, with the
 * specअगरied num entries, क्रम the LDC indicated by the given channel
 * ID.
 */
#घोषणा HV_FAST_LDC_SET_MAP_TABLE	0xea

/* ldc_get_map_table()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_LDC_GET_MAP_TABLE
 * ARG0:	channel ID
 * RET0:	status
 * RET1:	table real address
 * RET2:	num entries
 *
 * Return the configuration of the current mapping table रेजिस्टरed
 * क्रम the given channel ID.
 */
#घोषणा HV_FAST_LDC_GET_MAP_TABLE	0xeb

#घोषणा LDC_COPY_IN	0
#घोषणा LDC_COPY_OUT	1

/* ldc_copy()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_LDC_COPY
 * ARG0:	channel ID
 * ARG1:	LDC_COPY_* direction code
 * ARG2:	target real address
 * ARG3:	local real address
 * ARG4:	length in bytes
 * RET0:	status
 * RET1:	actual length in bytes
 */
#घोषणा HV_FAST_LDC_COPY		0xec

#घोषणा LDC_MEM_READ	1
#घोषणा LDC_MEM_WRITE	2
#घोषणा LDC_MEM_EXEC	4

/* ldc_mapin()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_LDC_MAPIN
 * ARG0:	channel ID
 * ARG1:	cookie
 * RET0:	status
 * RET1:	real address
 * RET2:	LDC_MEM_* permissions
 */
#घोषणा HV_FAST_LDC_MAPIN		0xed

/* ldc_unmap()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_LDC_UNMAP
 * ARG0:	real address
 * RET0:	status
 */
#घोषणा HV_FAST_LDC_UNMAP		0xee

/* ldc_revoke()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_LDC_REVOKE
 * ARG0:	channel ID
 * ARG1:	cookie
 * ARG2:	ldc_mtable_entry cookie
 * RET0:	status
 */
#घोषणा HV_FAST_LDC_REVOKE		0xef

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_ldc_tx_qconf(अचिन्हित दीर्घ channel,
				 अचिन्हित दीर्घ ra,
				 अचिन्हित दीर्घ num_entries);
अचिन्हित दीर्घ sun4v_ldc_tx_qinfo(अचिन्हित दीर्घ channel,
				 अचिन्हित दीर्घ *ra,
				 अचिन्हित दीर्घ *num_entries);
अचिन्हित दीर्घ sun4v_ldc_tx_get_state(अचिन्हित दीर्घ channel,
				     अचिन्हित दीर्घ *head_off,
				     अचिन्हित दीर्घ *tail_off,
				     अचिन्हित दीर्घ *chan_state);
अचिन्हित दीर्घ sun4v_ldc_tx_set_qtail(अचिन्हित दीर्घ channel,
				     अचिन्हित दीर्घ tail_off);
अचिन्हित दीर्घ sun4v_ldc_rx_qconf(अचिन्हित दीर्घ channel,
				 अचिन्हित दीर्घ ra,
				 अचिन्हित दीर्घ num_entries);
अचिन्हित दीर्घ sun4v_ldc_rx_qinfo(अचिन्हित दीर्घ channel,
				 अचिन्हित दीर्घ *ra,
				 अचिन्हित दीर्घ *num_entries);
अचिन्हित दीर्घ sun4v_ldc_rx_get_state(अचिन्हित दीर्घ channel,
				     अचिन्हित दीर्घ *head_off,
				     अचिन्हित दीर्घ *tail_off,
				     अचिन्हित दीर्घ *chan_state);
अचिन्हित दीर्घ sun4v_ldc_rx_set_qhead(अचिन्हित दीर्घ channel,
				     अचिन्हित दीर्घ head_off);
अचिन्हित दीर्घ sun4v_ldc_set_map_table(अचिन्हित दीर्घ channel,
				      अचिन्हित दीर्घ ra,
				      अचिन्हित दीर्घ num_entries);
अचिन्हित दीर्घ sun4v_ldc_get_map_table(अचिन्हित दीर्घ channel,
				      अचिन्हित दीर्घ *ra,
				      अचिन्हित दीर्घ *num_entries);
अचिन्हित दीर्घ sun4v_ldc_copy(अचिन्हित दीर्घ channel,
			     अचिन्हित दीर्घ dir_code,
			     अचिन्हित दीर्घ tgt_raddr,
			     अचिन्हित दीर्घ lcl_raddr,
			     अचिन्हित दीर्घ len,
			     अचिन्हित दीर्घ *actual_len);
अचिन्हित दीर्घ sun4v_ldc_mapin(अचिन्हित दीर्घ channel,
			      अचिन्हित दीर्घ cookie,
			      अचिन्हित दीर्घ *ra,
			      अचिन्हित दीर्घ *perm);
अचिन्हित दीर्घ sun4v_ldc_unmap(अचिन्हित दीर्घ ra);
अचिन्हित दीर्घ sun4v_ldc_revoke(अचिन्हित दीर्घ channel,
			       अचिन्हित दीर्घ cookie,
			       अचिन्हित दीर्घ mte_cookie);
#पूर्ण_अगर

/* Perक्रमmance counter services.  */

#घोषणा HV_PERF_JBUS_PERF_CTRL_REG	0x00
#घोषणा HV_PERF_JBUS_PERF_CNT_REG	0x01
#घोषणा HV_PERF_DRAM_PERF_CTRL_REG_0	0x02
#घोषणा HV_PERF_DRAM_PERF_CNT_REG_0	0x03
#घोषणा HV_PERF_DRAM_PERF_CTRL_REG_1	0x04
#घोषणा HV_PERF_DRAM_PERF_CNT_REG_1	0x05
#घोषणा HV_PERF_DRAM_PERF_CTRL_REG_2	0x06
#घोषणा HV_PERF_DRAM_PERF_CNT_REG_2	0x07
#घोषणा HV_PERF_DRAM_PERF_CTRL_REG_3	0x08
#घोषणा HV_PERF_DRAM_PERF_CNT_REG_3	0x09

/* get_perfreg()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_GET_PERFREG
 * ARG0:	perक्रमmance reg number
 * RET0:	status
 * RET1:	perक्रमmance reg value
 * ERRORS:	EINVAL		Invalid perक्रमmance रेजिस्टर number
 *		ENOACCESS	No access allowed to perक्रमmance counters
 *
 * Read the value of the given DRAM/JBUS perक्रमmance counter/control रेजिस्टर.
 */
#घोषणा HV_FAST_GET_PERFREG		0x100

/* set_perfreg()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_SET_PERFREG
 * ARG0:	perक्रमmance reg number
 * ARG1:	perक्रमmance reg value
 * RET0:	status
 * ERRORS:	EINVAL		Invalid perक्रमmance रेजिस्टर number
 *		ENOACCESS	No access allowed to perक्रमmance counters
 *
 * Write the given perक्रमmance reg value to the given DRAM/JBUS
 * perक्रमmance counter/control रेजिस्टर.
 */
#घोषणा HV_FAST_SET_PERFREG		0x101

#घोषणा HV_N2_PERF_SPARC_CTL		0x0
#घोषणा HV_N2_PERF_DRAM_CTL0		0x1
#घोषणा HV_N2_PERF_DRAM_CNT0		0x2
#घोषणा HV_N2_PERF_DRAM_CTL1		0x3
#घोषणा HV_N2_PERF_DRAM_CNT1		0x4
#घोषणा HV_N2_PERF_DRAM_CTL2		0x5
#घोषणा HV_N2_PERF_DRAM_CNT2		0x6
#घोषणा HV_N2_PERF_DRAM_CTL3		0x7
#घोषणा HV_N2_PERF_DRAM_CNT3		0x8

#घोषणा HV_FAST_N2_GET_PERFREG		0x104
#घोषणा HV_FAST_N2_SET_PERFREG		0x105

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_niagara_getperf(अचिन्हित दीर्घ reg,
				    अचिन्हित दीर्घ *val);
अचिन्हित दीर्घ sun4v_niagara_setperf(अचिन्हित दीर्घ reg,
				    अचिन्हित दीर्घ val);
अचिन्हित दीर्घ sun4v_niagara2_getperf(अचिन्हित दीर्घ reg,
				     अचिन्हित दीर्घ *val);
अचिन्हित दीर्घ sun4v_niagara2_setperf(अचिन्हित दीर्घ reg,
				     अचिन्हित दीर्घ val);
#पूर्ण_अगर

/* MMU statistics services.
 *
 * The hypervisor मुख्यtains MMU statistics and privileged code provides
 * a buffer where these statistics can be collected.  It is continually
 * updated once configured.  The layout is as follows:
 */
#अगर_अघोषित __ASSEMBLY__
काष्ठा hv_mmu_statistics अणु
	अचिन्हित दीर्घ immu_tsb_hits_ctx0_8k_tte;
	अचिन्हित दीर्घ immu_tsb_ticks_ctx0_8k_tte;
	अचिन्हित दीर्घ immu_tsb_hits_ctx0_64k_tte;
	अचिन्हित दीर्घ immu_tsb_ticks_ctx0_64k_tte;
	अचिन्हित दीर्घ __reserved1[2];
	अचिन्हित दीर्घ immu_tsb_hits_ctx0_4mb_tte;
	अचिन्हित दीर्घ immu_tsb_ticks_ctx0_4mb_tte;
	अचिन्हित दीर्घ __reserved2[2];
	अचिन्हित दीर्घ immu_tsb_hits_ctx0_256mb_tte;
	अचिन्हित दीर्घ immu_tsb_ticks_ctx0_256mb_tte;
	अचिन्हित दीर्घ __reserved3[4];
	अचिन्हित दीर्घ immu_tsb_hits_ctxnon0_8k_tte;
	अचिन्हित दीर्घ immu_tsb_ticks_ctxnon0_8k_tte;
	अचिन्हित दीर्घ immu_tsb_hits_ctxnon0_64k_tte;
	अचिन्हित दीर्घ immu_tsb_ticks_ctxnon0_64k_tte;
	अचिन्हित दीर्घ __reserved4[2];
	अचिन्हित दीर्घ immu_tsb_hits_ctxnon0_4mb_tte;
	अचिन्हित दीर्घ immu_tsb_ticks_ctxnon0_4mb_tte;
	अचिन्हित दीर्घ __reserved5[2];
	अचिन्हित दीर्घ immu_tsb_hits_ctxnon0_256mb_tte;
	अचिन्हित दीर्घ immu_tsb_ticks_ctxnon0_256mb_tte;
	अचिन्हित दीर्घ __reserved6[4];
	अचिन्हित दीर्घ dmmu_tsb_hits_ctx0_8k_tte;
	अचिन्हित दीर्घ dmmu_tsb_ticks_ctx0_8k_tte;
	अचिन्हित दीर्घ dmmu_tsb_hits_ctx0_64k_tte;
	अचिन्हित दीर्घ dmmu_tsb_ticks_ctx0_64k_tte;
	अचिन्हित दीर्घ __reserved7[2];
	अचिन्हित दीर्घ dmmu_tsb_hits_ctx0_4mb_tte;
	अचिन्हित दीर्घ dmmu_tsb_ticks_ctx0_4mb_tte;
	अचिन्हित दीर्घ __reserved8[2];
	अचिन्हित दीर्घ dmmu_tsb_hits_ctx0_256mb_tte;
	अचिन्हित दीर्घ dmmu_tsb_ticks_ctx0_256mb_tte;
	अचिन्हित दीर्घ __reserved9[4];
	अचिन्हित दीर्घ dmmu_tsb_hits_ctxnon0_8k_tte;
	अचिन्हित दीर्घ dmmu_tsb_ticks_ctxnon0_8k_tte;
	अचिन्हित दीर्घ dmmu_tsb_hits_ctxnon0_64k_tte;
	अचिन्हित दीर्घ dmmu_tsb_ticks_ctxnon0_64k_tte;
	अचिन्हित दीर्घ __reserved10[2];
	अचिन्हित दीर्घ dmmu_tsb_hits_ctxnon0_4mb_tte;
	अचिन्हित दीर्घ dmmu_tsb_ticks_ctxnon0_4mb_tte;
	अचिन्हित दीर्घ __reserved11[2];
	अचिन्हित दीर्घ dmmu_tsb_hits_ctxnon0_256mb_tte;
	अचिन्हित दीर्घ dmmu_tsb_ticks_ctxnon0_256mb_tte;
	अचिन्हित दीर्घ __reserved12[4];
पूर्ण;
#पूर्ण_अगर

/* mmustat_conf()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MMUSTAT_CONF
 * ARG0:	real address
 * RET0:	status
 * RET1:	real address
 * ERRORS:	ENORADDR	Invalid real address
 *		EBADALIGN	Real address not aligned on 64-byte boundary
 *		EBADTRAP	API not supported on this processor
 *
 * Enable MMU statistic gathering using the buffer at the given real
 * address on the current भव CPU.  The new buffer real address
 * is given in ARG1, and the previously specअगरied buffer real address
 * is वापसed in RET1, or is वापसed as zero क्रम the first invocation.
 *
 * If the passed in real address argument is zero, this will disable
 * MMU statistic collection on the current भव CPU.  If an error is
 * वापसed then no statistics are collected.
 *
 * The buffer contents should be initialized to all zeros beक्रमe being
 * given to the hypervisor or अन्यथा the statistics will be meaningless.
 */
#घोषणा HV_FAST_MMUSTAT_CONF		0x102

/* mmustat_info()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_MMUSTAT_INFO
 * RET0:	status
 * RET1:	real address
 * ERRORS:	EBADTRAP	API not supported on this processor
 *
 * Return the current state and real address of the currently configured
 * MMU statistics buffer on the current भव CPU.
 */
#घोषणा HV_FAST_MMUSTAT_INFO		0x103

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_mmustat_conf(अचिन्हित दीर्घ ra, अचिन्हित दीर्घ *orig_ra);
अचिन्हित दीर्घ sun4v_mmustat_info(अचिन्हित दीर्घ *ra);
#पूर्ण_अगर

/* NCS crypto services  */

/* ncs_request() sub-function numbers */
#घोषणा HV_NCS_QCONF			0x01
#घोषणा HV_NCS_QTAIL_UPDATE		0x02

#अगर_अघोषित __ASSEMBLY__
काष्ठा hv_ncs_queue_entry अणु
	/* MAU Control Register */
	अचिन्हित दीर्घ	mau_control;
#घोषणा MAU_CONTROL_INV_PARITY	0x0000000000002000
#घोषणा MAU_CONTROL_STRAND	0x0000000000001800
#घोषणा MAU_CONTROL_BUSY	0x0000000000000400
#घोषणा MAU_CONTROL_INT		0x0000000000000200
#घोषणा MAU_CONTROL_OP		0x00000000000001c0
#घोषणा MAU_CONTROL_OP_SHIFT	6
#घोषणा MAU_OP_LOAD_MA_MEMORY	0x0
#घोषणा MAU_OP_STORE_MA_MEMORY	0x1
#घोषणा MAU_OP_MODULAR_MULT	0x2
#घोषणा MAU_OP_MODULAR_REDUCE	0x3
#घोषणा MAU_OP_MODULAR_EXP_LOOP	0x4
#घोषणा MAU_CONTROL_LEN		0x000000000000003f
#घोषणा MAU_CONTROL_LEN_SHIFT	0

	/* Real address of bytes to load or store bytes
	 * पूर्णांकo/out-of the MAU.
	 */
	अचिन्हित दीर्घ	mau_mpa;

	/* Modular Arithmetic MA Offset Register.  */
	अचिन्हित दीर्घ	mau_ma;

	/* Modular Arithmetic N Prime Register.  */
	अचिन्हित दीर्घ	mau_np;
पूर्ण;

काष्ठा hv_ncs_qconf_arg अणु
	अचिन्हित दीर्घ	mid;      /* MAU ID, 1 per core on Niagara */
	अचिन्हित दीर्घ	base;     /* Real address base of queue */
	अचिन्हित दीर्घ	end;	  /* Real address end of queue */
	अचिन्हित दीर्घ	num_ents; /* Number of entries in queue */
पूर्ण;

काष्ठा hv_ncs_qtail_update_arg अणु
	अचिन्हित दीर्घ	mid;      /* MAU ID, 1 per core on Niagara */
	अचिन्हित दीर्घ	tail;     /* New tail index to use */
	अचिन्हित दीर्घ	syncflag; /* only SYNCFLAG_SYNC is implemented */
#घोषणा HV_NCS_SYNCFLAG_SYNC	0x00
#घोषणा HV_NCS_SYNCFLAG_ASYNC	0x01
पूर्ण;
#पूर्ण_अगर

/* ncs_request()
 * TRAP:	HV_FAST_TRAP
 * FUNCTION:	HV_FAST_NCS_REQUEST
 * ARG0:	NCS sub-function
 * ARG1:	sub-function argument real address
 * ARG2:	size in bytes of sub-function argument
 * RET0:	status
 *
 * The MAU chip of the Niagara processor is not directly accessible
 * to privileged code, instead it is programmed indirectly via this
 * hypervisor API.
 *
 * The पूर्णांकerfaces defines a queue of MAU operations to perक्रमm.
 * Privileged code रेजिस्टरs a queue with the hypervisor by invoking
 * this HVAPI with the HV_NCS_QCONF sub-function, which defines the
 * base, end, and number of entries of the queue.  Each queue entry
 * contains a MAU रेजिस्टर काष्ठा block.
 *
 * The privileged code then proceeds to add entries to the queue and
 * then invoke the HV_NCS_QTAIL_UPDATE sub-function.  Since only
 * synchronous operations are supported by the current hypervisor,
 * HV_NCS_QTAIL_UPDATE will run all the pending queue entries to
 * completion and वापस HV_EOK, or वापस an error code.
 *
 * The real address of the sub-function argument must be aligned on at
 * least an 8-byte boundary.
 *
 * The tail argument of HV_NCS_QTAIL_UPDATE is an index, not a byte
 * offset, पूर्णांकo the queue and must be less than or equal the 'num_ents'
 * argument given in the HV_NCS_QCONF call.
 */
#घोषणा HV_FAST_NCS_REQUEST		0x110

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_ncs_request(अचिन्हित दीर्घ request,
			        अचिन्हित दीर्घ arg_ra,
			        अचिन्हित दीर्घ arg_size);
#पूर्ण_अगर

#घोषणा HV_FAST_FIRE_GET_PERFREG	0x120
#घोषणा HV_FAST_FIRE_SET_PERFREG	0x121

#घोषणा HV_FAST_REBOOT_DATA_SET		0x172

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_reboot_data_set(अचिन्हित दीर्घ ra,
				    अचिन्हित दीर्घ len);
#पूर्ण_अगर

#घोषणा HV_FAST_VT_GET_PERFREG		0x184
#घोषणा HV_FAST_VT_SET_PERFREG		0x185

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_vt_get_perfreg(अचिन्हित दीर्घ reg_num,
				   अचिन्हित दीर्घ *reg_val);
अचिन्हित दीर्घ sun4v_vt_set_perfreg(अचिन्हित दीर्घ reg_num,
				   अचिन्हित दीर्घ reg_val);
#पूर्ण_अगर

#घोषणा	HV_FAST_T5_GET_PERFREG		0x1a8
#घोषणा	HV_FAST_T5_SET_PERFREG		0x1a9

#अगर_अघोषित	__ASSEMBLY__
अचिन्हित दीर्घ sun4v_t5_get_perfreg(अचिन्हित दीर्घ reg_num,
				   अचिन्हित दीर्घ *reg_val);
अचिन्हित दीर्घ sun4v_t5_set_perfreg(अचिन्हित दीर्घ reg_num,
				   अचिन्हित दीर्घ reg_val);
#पूर्ण_अगर


#घोषणा HV_FAST_M7_GET_PERFREG	0x43
#घोषणा HV_FAST_M7_SET_PERFREG	0x44

#अगर_अघोषित	__ASSEMBLY__
अचिन्हित दीर्घ sun4v_m7_get_perfreg(अचिन्हित दीर्घ reg_num,
				      अचिन्हित दीर्घ *reg_val);
अचिन्हित दीर्घ sun4v_m7_set_perfreg(अचिन्हित दीर्घ reg_num,
				      अचिन्हित दीर्घ reg_val);
#पूर्ण_अगर

/* Function numbers क्रम HV_CORE_TRAP.  */
#घोषणा HV_CORE_SET_VER			0x00
#घोषणा HV_CORE_PUTCHAR			0x01
#घोषणा HV_CORE_EXIT			0x02
#घोषणा HV_CORE_GET_VER			0x03

/* Hypervisor API groups क्रम use with HV_CORE_SET_VER and
 * HV_CORE_GET_VER.
 */
#घोषणा HV_GRP_SUN4V			0x0000
#घोषणा HV_GRP_CORE			0x0001
#घोषणा HV_GRP_INTR			0x0002
#घोषणा HV_GRP_SOFT_STATE		0x0003
#घोषणा HV_GRP_TM			0x0080
#घोषणा HV_GRP_PCI			0x0100
#घोषणा HV_GRP_LDOM			0x0101
#घोषणा HV_GRP_SVC_CHAN			0x0102
#घोषणा HV_GRP_NCS			0x0103
#घोषणा HV_GRP_RNG			0x0104
#घोषणा HV_GRP_PBOOT			0x0105
#घोषणा HV_GRP_TPM			0x0107
#घोषणा HV_GRP_SDIO			0x0108
#घोषणा HV_GRP_SDIO_ERR			0x0109
#घोषणा HV_GRP_REBOOT_DATA		0x0110
#घोषणा HV_GRP_ATU			0x0111
#घोषणा HV_GRP_DAX			0x0113
#घोषणा HV_GRP_M7_PERF			0x0114
#घोषणा HV_GRP_NIAG_PERF		0x0200
#घोषणा HV_GRP_FIRE_PERF		0x0201
#घोषणा HV_GRP_N2_CPU			0x0202
#घोषणा HV_GRP_NIU			0x0204
#घोषणा HV_GRP_VF_CPU			0x0205
#घोषणा HV_GRP_KT_CPU			0x0209
#घोषणा HV_GRP_VT_CPU			0x020c
#घोषणा HV_GRP_T5_CPU			0x0211
#घोषणा HV_GRP_DIAG			0x0300

#अगर_अघोषित __ASSEMBLY__
अचिन्हित दीर्घ sun4v_get_version(अचिन्हित दीर्घ group,
			        अचिन्हित दीर्घ *major,
			        अचिन्हित दीर्घ *minor);
अचिन्हित दीर्घ sun4v_set_version(अचिन्हित दीर्घ group,
			        अचिन्हित दीर्घ major,
			        अचिन्हित दीर्घ minor,
			        अचिन्हित दीर्घ *actual_minor);

पूर्णांक sun4v_hvapi_रेजिस्टर(अचिन्हित दीर्घ group, अचिन्हित दीर्घ major,
			 अचिन्हित दीर्घ *minor);
व्योम sun4v_hvapi_unरेजिस्टर(अचिन्हित दीर्घ group);
पूर्णांक sun4v_hvapi_get(अचिन्हित दीर्घ group,
		    अचिन्हित दीर्घ *major,
		    अचिन्हित दीर्घ *minor);
व्योम sun4v_hvapi_init(व्योम);
#पूर्ण_अगर

#पूर्ण_अगर /* !(_SPARC64_HYPERVISOR_H) */
