<शैली गुरु>
/******************************************************************************
 * vcpu.h
 *
 * VCPU initialisation, query, and hotplug.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Copyright (c) 2005, Keir Fraser <keir@xensource.com>
 */

#अगर_अघोषित __XEN_PUBLIC_VCPU_H__
#घोषणा __XEN_PUBLIC_VCPU_H__

/*
 * Prototype क्रम this hypercall is:
 *	पूर्णांक vcpu_op(पूर्णांक cmd, पूर्णांक vcpuid, व्योम *extra_args)
 * @cmd		   == VCPUOP_??? (VCPU operation).
 * @vcpuid	   == VCPU to operate on.
 * @extra_args == Operation-specअगरic extra arguments (शून्य अगर none).
 */

/*
 * Initialise a VCPU. Each VCPU can be initialised only once. A
 * newly-initialised VCPU will not run until it is brought up by VCPUOP_up.
 *
 * @extra_arg == poपूर्णांकer to vcpu_guest_context काष्ठाure containing initial
 *				 state क्रम the VCPU.
 */
#घोषणा VCPUOP_initialise			 0

/*
 * Bring up a VCPU. This makes the VCPU runnable. This operation will fail
 * अगर the VCPU has not been initialised (VCPUOP_initialise).
 */
#घोषणा VCPUOP_up					 1

/*
 * Bring करोwn a VCPU (i.e., make it non-runnable).
 * There are a few caveats that callers should observe:
 *	1. This operation may वापस, and VCPU_is_up may वापस false, beक्रमe the
 *	   VCPU stops running (i.e., the command is asynchronous). It is a good
 *	   idea to ensure that the VCPU has entered a non-critical loop beक्रमe
 *	   bringing it करोwn. Alternatively, this operation is guaranteed
 *	   synchronous अगर invoked by the VCPU itself.
 *	2. After a VCPU is initialised, there is currently no way to drop all its
 *	   references to करोमुख्य memory. Even a VCPU that is करोwn still holds
 *	   memory references via its pagetable base poपूर्णांकer and GDT. It is good
 *	   practise to move a VCPU onto an 'idle' or शेष page table, LDT and
 *	   GDT beक्रमe bringing it करोwn.
 */
#घोषणा VCPUOP_करोwn					 2

/* Returns 1 अगर the given VCPU is up. */
#घोषणा VCPUOP_is_up				 3

/*
 * Return inक्रमmation about the state and running समय of a VCPU.
 * @extra_arg == poपूर्णांकer to vcpu_runstate_info काष्ठाure.
 */
#घोषणा VCPUOP_get_runstate_info	 4
काष्ठा vcpu_runstate_info अणु
	/* VCPU's current state (RUNSTATE_*). */
	पूर्णांक		 state;
	/* When was current state entered (प्रणाली समय, ns)? */
	uपूर्णांक64_t state_entry_समय;
	/*
	 * Update indicator set in state_entry_समय:
	 * When activated via VMASST_TYPE_runstate_update_flag, set during
	 * updates in guest memory mapped copy of vcpu_runstate_info.
	 */
#घोषणा XEN_RUNSTATE_UPDATE	(1ULL << 63)
	/*
	 * Time spent in each RUNSTATE_* (ns). The sum of these बार is
	 * guaranteed not to drअगरt from प्रणाली समय.
	 */
	uपूर्णांक64_t समय[4];
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(vcpu_runstate_info);

/* VCPU is currently running on a physical CPU. */
#घोषणा RUNSTATE_running  0

/* VCPU is runnable, but not currently scheduled on any physical CPU. */
#घोषणा RUNSTATE_runnable 1

/* VCPU is blocked (a.k.a. idle). It is thereक्रमe not runnable. */
#घोषणा RUNSTATE_blocked  2

/*
 * VCPU is not runnable, but it is not blocked.
 * This is a 'catch all' state क्रम things like hotplug and छोड़ोs by the
 * प्रणाली administrator (or क्रम critical sections in the hypervisor).
 * RUNSTATE_blocked करोminates this state (it is the preferred state).
 */
#घोषणा RUNSTATE_offline  3

/*
 * Register a shared memory area from which the guest may obtain its own
 * runstate inक्रमmation without needing to execute a hypercall.
 * Notes:
 *	1. The रेजिस्टरed address may be भव or physical, depending on the
 *	   platक्रमm. The भव address should be रेजिस्टरed on x86 प्रणालीs.
 *	2. Only one shared area may be रेजिस्टरed per VCPU. The shared area is
 *	   updated by the hypervisor each समय the VCPU is scheduled. Thus
 *	   runstate.state will always be RUNSTATE_running and
 *	   runstate.state_entry_समय will indicate the प्रणाली समय at which the
 *	   VCPU was last scheduled to run.
 * @extra_arg == poपूर्णांकer to vcpu_रेजिस्टर_runstate_memory_area काष्ठाure.
 */
#घोषणा VCPUOP_रेजिस्टर_runstate_memory_area 5
काष्ठा vcpu_रेजिस्टर_runstate_memory_area अणु
		जोड़ अणु
				GUEST_HANDLE(vcpu_runstate_info) h;
				काष्ठा vcpu_runstate_info *v;
				uपूर्णांक64_t p;
		पूर्ण addr;
पूर्ण;

/*
 * Set or stop a VCPU's periodic समयr. Every VCPU has one periodic समयr
 * which can be set via these commands. Periods smaller than one millisecond
 * may not be supported.
 */
#घोषणा VCPUOP_set_periodic_समयr	 6 /* arg == vcpu_set_periodic_समयr_t */
#घोषणा VCPUOP_stop_periodic_समयr	 7 /* arg == शून्य */
काष्ठा vcpu_set_periodic_समयr अणु
		uपूर्णांक64_t period_ns;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(vcpu_set_periodic_समयr);

/*
 * Set or stop a VCPU's single-shot समयr. Every VCPU has one single-shot
 * समयr which can be set via these commands.
 */
#घोषणा VCPUOP_set_singleshot_समयr	 8 /* arg == vcpu_set_singleshot_समयr_t */
#घोषणा VCPUOP_stop_singleshot_समयr 9 /* arg == शून्य */
काष्ठा vcpu_set_singleshot_समयr अणु
		uपूर्णांक64_t समयout_असल_ns;
		uपूर्णांक32_t flags;			   /* VCPU_SSHOTTMR_??? */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(vcpu_set_singleshot_समयr);

/* Flags to VCPUOP_set_singleshot_समयr. */
 /* Require the समयout to be in the future (वापस -ETIME अगर it's passed). */
#घोषणा _VCPU_SSHOTTMR_future (0)
#घोषणा VCPU_SSHOTTMR_future  (1U << _VCPU_SSHOTTMR_future)

/*
 * Register a memory location in the guest address space क्रम the
 * vcpu_info काष्ठाure.  This allows the guest to place the vcpu_info
 * काष्ठाure in a convenient place, such as in a per-cpu data area.
 * The poपूर्णांकer need not be page aligned, but the काष्ठाure must not
 * cross a page boundary.
 */
#घोषणा VCPUOP_रेजिस्टर_vcpu_info   10  /* arg == काष्ठा vcpu_info */
काष्ठा vcpu_रेजिस्टर_vcpu_info अणु
    uपूर्णांक64_t mfn;    /* mfn of page to place vcpu_info */
    uपूर्णांक32_t offset; /* offset within page */
    uपूर्णांक32_t rsvd;   /* unused */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(vcpu_रेजिस्टर_vcpu_info);

/* Send an NMI to the specअगरied VCPU. @extra_arg == शून्य. */
#घोषणा VCPUOP_send_nmi             11

/*
 * Get the physical ID inक्रमmation क्रम a pinned vcpu's underlying physical
 * processor.  The physical ID inक्रमmmation is architecture-specअगरic.
 * On x86: id[31:0]=apic_id, id[63:32]=acpi_id.
 * This command वापसs -EINVAL अगर it is not a valid operation क्रम this VCPU.
 */
#घोषणा VCPUOP_get_physid           12 /* arg == vcpu_get_physid_t */
काष्ठा vcpu_get_physid अणु
	uपूर्णांक64_t phys_id;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(vcpu_get_physid);
#घोषणा xen_vcpu_physid_to_x86_apicid(physid) ((uपूर्णांक32_t)(physid))
#घोषणा xen_vcpu_physid_to_x86_acpiid(physid) ((uपूर्णांक32_t)((physid) >> 32))

/*
 * Register a memory location to get a secondary copy of the vcpu समय
 * parameters.  The master copy still exists as part of the vcpu shared
 * memory area, and this secondary copy is updated whenever the master copy
 * is updated (and using the same versioning scheme क्रम synchronisation).
 *
 * The पूर्णांकent is that this copy may be mapped (RO) पूर्णांकo userspace so
 * that usermode can compute प्रणाली समय using the समय info and the
 * tsc.  Usermode will see an array of vcpu_समय_info काष्ठाures, one
 * क्रम each vcpu, and choose the right one by an existing mechanism
 * which allows it to get the current vcpu number (such as via a
 * segment limit).  It can then apply the normal algorithm to compute
 * प्रणाली समय from the tsc.
 *
 * @extra_arg == poपूर्णांकer to vcpu_रेजिस्टर_समय_info_memory_area काष्ठाure.
 */
#घोषणा VCPUOP_रेजिस्टर_vcpu_समय_memory_area   13
DEFINE_GUEST_HANDLE_STRUCT(vcpu_समय_info);
काष्ठा vcpu_रेजिस्टर_समय_memory_area अणु
	जोड़ अणु
		GUEST_HANDLE(vcpu_समय_info) h;
		काष्ठा pvघड़ी_vcpu_समय_info *v;
		uपूर्णांक64_t p;
	पूर्ण addr;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(vcpu_रेजिस्टर_समय_memory_area);

#पूर्ण_अगर /* __XEN_PUBLIC_VCPU_H__ */
