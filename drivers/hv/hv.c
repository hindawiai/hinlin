<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2009, Microsoft Corporation.
 *
 * Authors:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 *   Hank Janssen  <hjanssen@microsoft.com>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <घड़ीsource/hyperv_समयr.h>
#समावेश <यंत्र/mshyperv.h>
#समावेश "hyperv_vmbus.h"

/* The one and only */
काष्ठा hv_context hv_context;

/*
 * hv_init - Main initialization routine.
 *
 * This routine must be called beक्रमe any other routines in here are called
 */
पूर्णांक hv_init(व्योम)
अणु
	hv_context.cpu_context = alloc_percpu(काष्ठा hv_per_cpu_context);
	अगर (!hv_context.cpu_context)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/*
 * Functions क्रम allocating and मुक्तing memory with size and
 * alignment HV_HYP_PAGE_SIZE. These functions are needed because
 * the guest page size may not be the same as the Hyper-V page
 * size. We depend upon kदो_स्मृति() aligning घातer-of-two size
 * allocations to the allocation size boundary, so that the
 * allocated memory appears to Hyper-V as a page of the size
 * it expects.
 */

व्योम *hv_alloc_hyperv_page(व्योम)
अणु
	BUILD_BUG_ON(PAGE_SIZE <  HV_HYP_PAGE_SIZE);

	अगर (PAGE_SIZE == HV_HYP_PAGE_SIZE)
		वापस (व्योम *)__get_मुक्त_page(GFP_KERNEL);
	अन्यथा
		वापस kदो_स्मृति(HV_HYP_PAGE_SIZE, GFP_KERNEL);
पूर्ण

व्योम *hv_alloc_hyperv_zeroed_page(व्योम)
अणु
	अगर (PAGE_SIZE == HV_HYP_PAGE_SIZE)
		वापस (व्योम *)__get_मुक्त_page(GFP_KERNEL | __GFP_ZERO);
	अन्यथा
		वापस kzalloc(HV_HYP_PAGE_SIZE, GFP_KERNEL);
पूर्ण

व्योम hv_मुक्त_hyperv_page(अचिन्हित दीर्घ addr)
अणु
	अगर (PAGE_SIZE == HV_HYP_PAGE_SIZE)
		मुक्त_page(addr);
	अन्यथा
		kमुक्त((व्योम *)addr);
पूर्ण

/*
 * hv_post_message - Post a message using the hypervisor message IPC.
 *
 * This involves a hypercall.
 */
पूर्णांक hv_post_message(जोड़ hv_connection_id connection_id,
		  क्रमागत hv_message_type message_type,
		  व्योम *payload, माप_प्रकार payload_size)
अणु
	काष्ठा hv_input_post_message *aligned_msg;
	काष्ठा hv_per_cpu_context *hv_cpu;
	u64 status;

	अगर (payload_size > HV_MESSAGE_PAYLOAD_BYTE_COUNT)
		वापस -EMSGSIZE;

	hv_cpu = get_cpu_ptr(hv_context.cpu_context);
	aligned_msg = hv_cpu->post_msg_page;
	aligned_msg->connectionid = connection_id;
	aligned_msg->reserved = 0;
	aligned_msg->message_type = message_type;
	aligned_msg->payload_size = payload_size;
	स_नकल((व्योम *)aligned_msg->payload, payload, payload_size);

	status = hv_करो_hypercall(HVCALL_POST_MESSAGE, aligned_msg, शून्य);

	/* Preemption must reमुख्य disabled until after the hypercall
	 * so some other thपढ़ो can't get scheduled onto this cpu and
	 * corrupt the per-cpu post_msg_page
	 */
	put_cpu_ptr(hv_cpu);

	वापस hv_result(status);
पूर्ण

पूर्णांक hv_synic_alloc(व्योम)
अणु
	पूर्णांक cpu;
	काष्ठा hv_per_cpu_context *hv_cpu;

	/*
	 * First, zero all per-cpu memory areas so hv_synic_मुक्त() can
	 * detect what memory has been allocated and cleanup properly
	 * after any failures.
	 */
	क्रम_each_present_cpu(cpu) अणु
		hv_cpu = per_cpu_ptr(hv_context.cpu_context, cpu);
		स_रखो(hv_cpu, 0, माप(*hv_cpu));
	पूर्ण

	hv_context.hv_numa_map = kसुस्मृति(nr_node_ids, माप(काष्ठा cpumask),
					 GFP_KERNEL);
	अगर (hv_context.hv_numa_map == शून्य) अणु
		pr_err("Unable to allocate NUMA map\n");
		जाओ err;
	पूर्ण

	क्रम_each_present_cpu(cpu) अणु
		hv_cpu = per_cpu_ptr(hv_context.cpu_context, cpu);

		tasklet_init(&hv_cpu->msg_dpc,
			     vmbus_on_msg_dpc, (अचिन्हित दीर्घ) hv_cpu);

		hv_cpu->synic_message_page =
			(व्योम *)get_zeroed_page(GFP_ATOMIC);
		अगर (hv_cpu->synic_message_page == शून्य) अणु
			pr_err("Unable to allocate SYNIC message page\n");
			जाओ err;
		पूर्ण

		hv_cpu->synic_event_page = (व्योम *)get_zeroed_page(GFP_ATOMIC);
		अगर (hv_cpu->synic_event_page == शून्य) अणु
			pr_err("Unable to allocate SYNIC event page\n");
			जाओ err;
		पूर्ण

		hv_cpu->post_msg_page = (व्योम *)get_zeroed_page(GFP_ATOMIC);
		अगर (hv_cpu->post_msg_page == शून्य) अणु
			pr_err("Unable to allocate post msg page\n");
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	/*
	 * Any memory allocations that succeeded will be मुक्तd when
	 * the caller cleans up by calling hv_synic_मुक्त()
	 */
	वापस -ENOMEM;
पूर्ण


व्योम hv_synic_मुक्त(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_present_cpu(cpu) अणु
		काष्ठा hv_per_cpu_context *hv_cpu
			= per_cpu_ptr(hv_context.cpu_context, cpu);

		मुक्त_page((अचिन्हित दीर्घ)hv_cpu->synic_event_page);
		मुक्त_page((अचिन्हित दीर्घ)hv_cpu->synic_message_page);
		मुक्त_page((अचिन्हित दीर्घ)hv_cpu->post_msg_page);
	पूर्ण

	kमुक्त(hv_context.hv_numa_map);
पूर्ण

/*
 * hv_synic_init - Initialize the Synthetic Interrupt Controller.
 *
 * If it is alपढ़ोy initialized by another entity (ie x2v shim), we need to
 * retrieve the initialized message and event pages.  Otherwise, we create and
 * initialize the message and event pages.
 */
व्योम hv_synic_enable_regs(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा hv_per_cpu_context *hv_cpu
		= per_cpu_ptr(hv_context.cpu_context, cpu);
	जोड़ hv_synic_simp simp;
	जोड़ hv_synic_siefp siefp;
	जोड़ hv_synic_sपूर्णांक shared_sपूर्णांक;
	जोड़ hv_synic_scontrol sctrl;

	/* Setup the Synic's message page */
	simp.as_uपूर्णांक64 = hv_get_रेजिस्टर(HV_REGISTER_SIMP);
	simp.simp_enabled = 1;
	simp.base_simp_gpa = virt_to_phys(hv_cpu->synic_message_page)
		>> HV_HYP_PAGE_SHIFT;

	hv_set_रेजिस्टर(HV_REGISTER_SIMP, simp.as_uपूर्णांक64);

	/* Setup the Synic's event page */
	siefp.as_uपूर्णांक64 = hv_get_रेजिस्टर(HV_REGISTER_SIEFP);
	siefp.siefp_enabled = 1;
	siefp.base_siefp_gpa = virt_to_phys(hv_cpu->synic_event_page)
		>> HV_HYP_PAGE_SHIFT;

	hv_set_रेजिस्टर(HV_REGISTER_SIEFP, siefp.as_uपूर्णांक64);

	/* Setup the shared SINT. */
	अगर (vmbus_irq != -1)
		enable_percpu_irq(vmbus_irq, 0);
	shared_sपूर्णांक.as_uपूर्णांक64 = hv_get_रेजिस्टर(HV_REGISTER_SINT0 +
					VMBUS_MESSAGE_SINT);

	shared_sपूर्णांक.vector = vmbus_पूर्णांकerrupt;
	shared_sपूर्णांक.masked = false;

	/*
	 * On architectures where Hyper-V करोesn't support AEOI (e.g., ARM64),
	 * it करोesn't provide a recommendation flag and AEOI must be disabled.
	 */
#अगर_घोषित HV_DEPRECATING_AEOI_RECOMMENDED
	shared_sपूर्णांक.स्वतः_eoi =
			!(ms_hyperv.hपूर्णांकs & HV_DEPRECATING_AEOI_RECOMMENDED);
#अन्यथा
	shared_sपूर्णांक.स्वतः_eoi = 0;
#पूर्ण_अगर
	hv_set_रेजिस्टर(HV_REGISTER_SINT0 + VMBUS_MESSAGE_SINT,
				shared_sपूर्णांक.as_uपूर्णांक64);

	/* Enable the global synic bit */
	sctrl.as_uपूर्णांक64 = hv_get_रेजिस्टर(HV_REGISTER_SCONTROL);
	sctrl.enable = 1;

	hv_set_रेजिस्टर(HV_REGISTER_SCONTROL, sctrl.as_uपूर्णांक64);
पूर्ण

पूर्णांक hv_synic_init(अचिन्हित पूर्णांक cpu)
अणु
	hv_synic_enable_regs(cpu);

	hv_sसमयr_legacy_init(cpu, VMBUS_MESSAGE_SINT);

	वापस 0;
पूर्ण

/*
 * hv_synic_cleanup - Cleanup routine क्रम hv_synic_init().
 */
व्योम hv_synic_disable_regs(अचिन्हित पूर्णांक cpu)
अणु
	जोड़ hv_synic_sपूर्णांक shared_sपूर्णांक;
	जोड़ hv_synic_simp simp;
	जोड़ hv_synic_siefp siefp;
	जोड़ hv_synic_scontrol sctrl;

	shared_sपूर्णांक.as_uपूर्णांक64 = hv_get_रेजिस्टर(HV_REGISTER_SINT0 +
					VMBUS_MESSAGE_SINT);

	shared_sपूर्णांक.masked = 1;

	/* Need to correctly cleanup in the हाल of SMP!!! */
	/* Disable the पूर्णांकerrupt */
	hv_set_रेजिस्टर(HV_REGISTER_SINT0 + VMBUS_MESSAGE_SINT,
				shared_sपूर्णांक.as_uपूर्णांक64);

	simp.as_uपूर्णांक64 = hv_get_रेजिस्टर(HV_REGISTER_SIMP);
	simp.simp_enabled = 0;
	simp.base_simp_gpa = 0;

	hv_set_रेजिस्टर(HV_REGISTER_SIMP, simp.as_uपूर्णांक64);

	siefp.as_uपूर्णांक64 = hv_get_रेजिस्टर(HV_REGISTER_SIEFP);
	siefp.siefp_enabled = 0;
	siefp.base_siefp_gpa = 0;

	hv_set_रेजिस्टर(HV_REGISTER_SIEFP, siefp.as_uपूर्णांक64);

	/* Disable the global synic bit */
	sctrl.as_uपूर्णांक64 = hv_get_रेजिस्टर(HV_REGISTER_SCONTROL);
	sctrl.enable = 0;
	hv_set_रेजिस्टर(HV_REGISTER_SCONTROL, sctrl.as_uपूर्णांक64);

	अगर (vmbus_irq != -1)
		disable_percpu_irq(vmbus_irq);
पूर्ण

#घोषणा HV_MAX_TRIES 3
/*
 * Scan the event flags page of 'this' CPU looking क्रम any bit that is set.  If we find one
 * bit set, then रुको क्रम a few milliseconds.  Repeat these steps क्रम a maximum of 3 बार.
 * Return 'true', if there is still any set bit after this operation; 'false', otherwise.
 *
 * If a bit is set, that means there is a pending channel पूर्णांकerrupt.  The expectation is
 * that the normal पूर्णांकerrupt handling mechanism will find and process the channel पूर्णांकerrupt
 * "very soon", and in the process clear the bit.
 */
अटल bool hv_synic_event_pending(व्योम)
अणु
	काष्ठा hv_per_cpu_context *hv_cpu = this_cpu_ptr(hv_context.cpu_context);
	जोड़ hv_synic_event_flags *event =
		(जोड़ hv_synic_event_flags *)hv_cpu->synic_event_page + VMBUS_MESSAGE_SINT;
	अचिन्हित दीर्घ *recv_पूर्णांक_page = event->flags; /* assumes VMBus version >= VERSION_WIN8 */
	bool pending;
	u32 relid;
	पूर्णांक tries = 0;

retry:
	pending = false;
	क्रम_each_set_bit(relid, recv_पूर्णांक_page, HV_EVENT_FLAGS_COUNT) अणु
		/* Special हाल - VMBus channel protocol messages */
		अगर (relid == 0)
			जारी;
		pending = true;
		अवरोध;
	पूर्ण
	अगर (pending && tries++ < HV_MAX_TRIES) अणु
		usleep_range(10000, 20000);
		जाओ retry;
	पूर्ण
	वापस pending;
पूर्ण

पूर्णांक hv_synic_cleanup(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा vmbus_channel *channel, *sc;
	bool channel_found = false;

	अगर (vmbus_connection.conn_state != CONNECTED)
		जाओ always_cleanup;

	/*
	 * Hyper-V करोes not provide a way to change the connect CPU once
	 * it is set; we must prevent the connect CPU from going offline
	 * जबतक the VM is running normally. But in the panic or kexec()
	 * path where the vmbus is alपढ़ोy disconnected, the CPU must be
	 * allowed to shut करोwn.
	 */
	अगर (cpu == VMBUS_CONNECT_CPU)
		वापस -EBUSY;

	/*
	 * Search क्रम channels which are bound to the CPU we're about to
	 * cleanup.  In हाल we find one and vmbus is still connected, we
	 * fail; this will effectively prevent CPU offlining.
	 *
	 * TODO: Re-bind the channels to dअगरferent CPUs.
	 */
	mutex_lock(&vmbus_connection.channel_mutex);
	list_क्रम_each_entry(channel, &vmbus_connection.chn_list, listentry) अणु
		अगर (channel->target_cpu == cpu) अणु
			channel_found = true;
			अवरोध;
		पूर्ण
		list_क्रम_each_entry(sc, &channel->sc_list, sc_list) अणु
			अगर (sc->target_cpu == cpu) अणु
				channel_found = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (channel_found)
			अवरोध;
	पूर्ण
	mutex_unlock(&vmbus_connection.channel_mutex);

	अगर (channel_found)
		वापस -EBUSY;

	/*
	 * channel_found == false means that any channels that were previously
	 * asचिन्हित to the CPU have been reasचिन्हित अन्यथाwhere with a call of
	 * vmbus_send_modअगरychannel().  Scan the event flags page looking क्रम
	 * bits that are set and रुकोing with a समयout क्रम vmbus_chan_sched()
	 * to process such bits.  If bits are still set after this operation
	 * and VMBus is connected, fail the CPU offlining operation.
	 */
	अगर (vmbus_proto_version >= VERSION_WIN10_V4_1 && hv_synic_event_pending())
		वापस -EBUSY;

always_cleanup:
	hv_sसमयr_legacy_cleanup(cpu);

	hv_synic_disable_regs(cpu);

	वापस 0;
पूर्ण
