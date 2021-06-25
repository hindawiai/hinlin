<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 पूर्णांकerrupt routines.
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006 Sony Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/smp.h>

#समावेश "platform.h"

#अगर defined(DEBUG)
#घोषणा DBG udbg_म_लिखो
#घोषणा FAIL udbg_म_लिखो
#अन्यथा
#घोषणा DBG pr_devel
#घोषणा FAIL pr_debug
#पूर्ण_अगर

/**
 * काष्ठा ps3_bmp - a per cpu irq status and mask biपंचांगap काष्ठाure
 * @status: 256 bit status biपंचांगap indexed by plug
 * @unused_1: Alignment
 * @mask: 256 bit mask biपंचांगap indexed by plug
 * @unused_2: Alignment
 *
 * The HV मुख्यtains per SMT thपढ़ो mappings of HV outlet to HV plug on
 * behalf of the guest.  These mappings are implemented as 256 bit guest
 * supplied biपंचांगaps indexed by plug number.  The addresses of the biपंचांगaps
 * are रेजिस्टरed with the HV through lv1_configure_irq_state_biपंचांगap().
 * The HV requires that the 512 bits of status + mask not cross a page
 * boundary.  PS3_BMP_MINALIGN is used to define this minimal 64 byte
 * alignment.
 *
 * The HV supports 256 plugs per thपढ़ो, asचिन्हित as अणु0..255पूर्ण, क्रम a total
 * of 512 plugs supported on a processor.  To simplअगरy the logic this
 * implementation equates HV plug value to Linux virq value, स्थिरrains each
 * पूर्णांकerrupt to have a प्रणाली wide unique plug number, and limits the range
 * of the plug values to map पूर्णांकo the first dword of the biपंचांगaps.  This
 * gives a usable range of plug values of  अणुNUM_ISA_INTERRUPTS..63पूर्ण.  Note
 * that there is no स्थिरraपूर्णांक on how many in this set an inभागidual thपढ़ो
 * can acquire.
 *
 * The mask is declared as अचिन्हित दीर्घ so we can use set/clear_bit on it.
 */

#घोषणा PS3_BMP_MINALIGN 64

काष्ठा ps3_bmp अणु
	काष्ठा अणु
		u64 status;
		u64 unused_1[3];
		अचिन्हित दीर्घ mask;
		u64 unused_2[3];
	पूर्ण;
पूर्ण;

/**
 * काष्ठा ps3_निजी - a per cpu data काष्ठाure
 * @bmp: ps3_bmp काष्ठाure
 * @bmp_lock: Synchronize access to bmp.
 * @ipi_debug_brk_mask: Mask क्रम debug अवरोध IPIs
 * @ppe_id: HV logical_ppe_id
 * @thपढ़ो_id: HV thपढ़ो_id
 * @ipi_mask: Mask of IPI virqs
 */

काष्ठा ps3_निजी अणु
	काष्ठा ps3_bmp bmp __attribute__ ((aligned (PS3_BMP_MINALIGN)));
	spinlock_t bmp_lock;
	u64 ppe_id;
	u64 thपढ़ो_id;
	अचिन्हित दीर्घ ipi_debug_brk_mask;
	अचिन्हित दीर्घ ipi_mask;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा ps3_निजी, ps3_निजी);

/**
 * ps3_chip_mask - Set an पूर्णांकerrupt mask bit in ps3_bmp.
 * @virq: The asचिन्हित Linux virq.
 *
 * Sets ps3_bmp.mask and calls lv1_did_update_पूर्णांकerrupt_mask().
 */

अटल व्योम ps3_chip_mask(काष्ठा irq_data *d)
अणु
	काष्ठा ps3_निजी *pd = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;

	DBG("%s:%d: thread_id %llu, virq %d\n", __func__, __LINE__,
		pd->thपढ़ो_id, d->irq);

	local_irq_save(flags);
	clear_bit(63 - d->irq, &pd->bmp.mask);
	lv1_did_update_पूर्णांकerrupt_mask(pd->ppe_id, pd->thपढ़ो_id);
	local_irq_restore(flags);
पूर्ण

/**
 * ps3_chip_unmask - Clear an पूर्णांकerrupt mask bit in ps3_bmp.
 * @virq: The asचिन्हित Linux virq.
 *
 * Clears ps3_bmp.mask and calls lv1_did_update_पूर्णांकerrupt_mask().
 */

अटल व्योम ps3_chip_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा ps3_निजी *pd = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;

	DBG("%s:%d: thread_id %llu, virq %d\n", __func__, __LINE__,
		pd->thपढ़ो_id, d->irq);

	local_irq_save(flags);
	set_bit(63 - d->irq, &pd->bmp.mask);
	lv1_did_update_पूर्णांकerrupt_mask(pd->ppe_id, pd->thपढ़ो_id);
	local_irq_restore(flags);
पूर्ण

/**
 * ps3_chip_eoi - HV end-of-पूर्णांकerrupt.
 * @virq: The asचिन्हित Linux virq.
 *
 * Calls lv1_end_of_पूर्णांकerrupt_ext().
 */

अटल व्योम ps3_chip_eoi(काष्ठा irq_data *d)
अणु
	स्थिर काष्ठा ps3_निजी *pd = irq_data_get_irq_chip_data(d);

	/* non-IPIs are EOIed here. */

	अगर (!test_bit(63 - d->irq, &pd->ipi_mask))
		lv1_end_of_पूर्णांकerrupt_ext(pd->ppe_id, pd->thपढ़ो_id, d->irq);
पूर्ण

/**
 * ps3_irq_chip - Represents the ps3_bmp as a Linux काष्ठा irq_chip.
 */

अटल काष्ठा irq_chip ps3_irq_chip = अणु
	.name = "ps3",
	.irq_mask = ps3_chip_mask,
	.irq_unmask = ps3_chip_unmask,
	.irq_eoi = ps3_chip_eoi,
पूर्ण;

/**
 * ps3_virq_setup - virq related setup.
 * @cpu: क्रमागत ps3_cpu_binding indicating the cpu the पूर्णांकerrupt should be
 * serviced on.
 * @outlet: The HV outlet from the various create outlet routines.
 * @virq: The asचिन्हित Linux virq.
 *
 * Calls irq_create_mapping() to get a virq and sets the chip data to
 * ps3_निजी data.
 */

अटल पूर्णांक ps3_virq_setup(क्रमागत ps3_cpu_binding cpu, अचिन्हित दीर्घ outlet,
			  अचिन्हित पूर्णांक *virq)
अणु
	पूर्णांक result;
	काष्ठा ps3_निजी *pd;

	/* This defines the शेष पूर्णांकerrupt distribution policy. */

	अगर (cpu == PS3_BINDING_CPU_ANY)
		cpu = 0;

	pd = &per_cpu(ps3_निजी, cpu);

	*virq = irq_create_mapping(शून्य, outlet);

	अगर (!*virq) अणु
		FAIL("%s:%d: irq_create_mapping failed: outlet %lu\n",
			__func__, __LINE__, outlet);
		result = -ENOMEM;
		जाओ fail_create;
	पूर्ण

	DBG("%s:%d: outlet %lu => cpu %u, virq %u\n", __func__, __LINE__,
		outlet, cpu, *virq);

	result = irq_set_chip_data(*virq, pd);

	अगर (result) अणु
		FAIL("%s:%d: irq_set_chip_data failed\n",
			__func__, __LINE__);
		जाओ fail_set;
	पूर्ण

	ps3_chip_mask(irq_get_irq_data(*virq));

	वापस result;

fail_set:
	irq_dispose_mapping(*virq);
fail_create:
	वापस result;
पूर्ण

/**
 * ps3_virq_destroy - virq related tearकरोwn.
 * @virq: The asचिन्हित Linux virq.
 *
 * Clears chip data and calls irq_dispose_mapping() क्रम the virq.
 */

अटल पूर्णांक ps3_virq_destroy(अचिन्हित पूर्णांक virq)
अणु
	स्थिर काष्ठा ps3_निजी *pd = irq_get_chip_data(virq);

	DBG("%s:%d: ppe_id %llu, thread_id %llu, virq %u\n", __func__,
		__LINE__, pd->ppe_id, pd->thपढ़ो_id, virq);

	irq_set_chip_data(virq, शून्य);
	irq_dispose_mapping(virq);

	DBG("%s:%d <-\n", __func__, __LINE__);
	वापस 0;
पूर्ण

/**
 * ps3_irq_plug_setup - Generic outlet and virq related setup.
 * @cpu: क्रमागत ps3_cpu_binding indicating the cpu the पूर्णांकerrupt should be
 * serviced on.
 * @outlet: The HV outlet from the various create outlet routines.
 * @virq: The asचिन्हित Linux virq.
 *
 * Sets up virq and connects the irq plug.
 */

पूर्णांक ps3_irq_plug_setup(क्रमागत ps3_cpu_binding cpu, अचिन्हित दीर्घ outlet,
	अचिन्हित पूर्णांक *virq)
अणु
	पूर्णांक result;
	काष्ठा ps3_निजी *pd;

	result = ps3_virq_setup(cpu, outlet, virq);

	अगर (result) अणु
		FAIL("%s:%d: ps3_virq_setup failed\n", __func__, __LINE__);
		जाओ fail_setup;
	पूर्ण

	pd = irq_get_chip_data(*virq);

	/* Binds outlet to cpu + virq. */

	result = lv1_connect_irq_plug_ext(pd->ppe_id, pd->thपढ़ो_id, *virq,
		outlet, 0);

	अगर (result) अणु
		FAIL("%s:%d: lv1_connect_irq_plug_ext failed: %s\n",
		__func__, __LINE__, ps3_result(result));
		result = -EPERM;
		जाओ fail_connect;
	पूर्ण

	वापस result;

fail_connect:
	ps3_virq_destroy(*virq);
fail_setup:
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_irq_plug_setup);

/**
 * ps3_irq_plug_destroy - Generic outlet and virq related tearकरोwn.
 * @virq: The asचिन्हित Linux virq.
 *
 * Disconnects the irq plug and tears करोwn virq.
 * Do not call क्रम प्रणाली bus event पूर्णांकerrupts setup with
 * ps3_sb_event_receive_port_setup().
 */

पूर्णांक ps3_irq_plug_destroy(अचिन्हित पूर्णांक virq)
अणु
	पूर्णांक result;
	स्थिर काष्ठा ps3_निजी *pd = irq_get_chip_data(virq);

	DBG("%s:%d: ppe_id %llu, thread_id %llu, virq %u\n", __func__,
		__LINE__, pd->ppe_id, pd->thपढ़ो_id, virq);

	ps3_chip_mask(irq_get_irq_data(virq));

	result = lv1_disconnect_irq_plug_ext(pd->ppe_id, pd->thपढ़ो_id, virq);

	अगर (result)
		FAIL("%s:%d: lv1_disconnect_irq_plug_ext failed: %s\n",
		__func__, __LINE__, ps3_result(result));

	ps3_virq_destroy(virq);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_irq_plug_destroy);

/**
 * ps3_event_receive_port_setup - Setup an event receive port.
 * @cpu: क्रमागत ps3_cpu_binding indicating the cpu the पूर्णांकerrupt should be
 * serviced on.
 * @virq: The asचिन्हित Linux virq.
 *
 * The virq can be used with lv1_connect_पूर्णांकerrupt_event_receive_port() to
 * arrange to receive पूर्णांकerrupts from प्रणाली-bus devices, or with
 * ps3_send_event_locally() to संकेत events.
 */

पूर्णांक ps3_event_receive_port_setup(क्रमागत ps3_cpu_binding cpu, अचिन्हित पूर्णांक *virq)
अणु
	पूर्णांक result;
	u64 outlet;

	result = lv1_स्थिरruct_event_receive_port(&outlet);

	अगर (result) अणु
		FAIL("%s:%d: lv1_construct_event_receive_port failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		*virq = 0;
		वापस result;
	पूर्ण

	result = ps3_irq_plug_setup(cpu, outlet, virq);
	BUG_ON(result);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_event_receive_port_setup);

/**
 * ps3_event_receive_port_destroy - Destroy an event receive port.
 * @virq: The asचिन्हित Linux virq.
 *
 * Since ps3_event_receive_port_destroy destroys the receive port outlet,
 * SB devices need to call disconnect_पूर्णांकerrupt_event_receive_port() beक्रमe
 * this.
 */

पूर्णांक ps3_event_receive_port_destroy(अचिन्हित पूर्णांक virq)
अणु
	पूर्णांक result;

	DBG(" -> %s:%d virq %u\n", __func__, __LINE__, virq);

	ps3_chip_mask(irq_get_irq_data(virq));

	result = lv1_deकाष्ठा_event_receive_port(virq_to_hw(virq));

	अगर (result)
		FAIL("%s:%d: lv1_destruct_event_receive_port failed: %s\n",
			__func__, __LINE__, ps3_result(result));

	/*
	 * Don't call ps3_virq_destroy() here since ps3_smp_cleanup_cpu()
	 * calls from पूर्णांकerrupt context (smp_call_function) when kexecing.
	 */

	DBG(" <- %s:%d\n", __func__, __LINE__);
	वापस result;
पूर्ण

पूर्णांक ps3_send_event_locally(अचिन्हित पूर्णांक virq)
अणु
	वापस lv1_send_event_locally(virq_to_hw(virq));
पूर्ण

/**
 * ps3_sb_event_receive_port_setup - Setup a प्रणाली bus event receive port.
 * @cpu: क्रमागत ps3_cpu_binding indicating the cpu the पूर्णांकerrupt should be
 * serviced on.
 * @dev: The प्रणाली bus device instance.
 * @virq: The asचिन्हित Linux virq.
 *
 * An event irq represents a भव device पूर्णांकerrupt.  The पूर्णांकerrupt_id
 * coresponds to the software पूर्णांकerrupt number.
 */

पूर्णांक ps3_sb_event_receive_port_setup(काष्ठा ps3_प्रणाली_bus_device *dev,
	क्रमागत ps3_cpu_binding cpu, अचिन्हित पूर्णांक *virq)
अणु
	/* this should go in प्रणाली-bus.c */

	पूर्णांक result;

	result = ps3_event_receive_port_setup(cpu, virq);

	अगर (result)
		वापस result;

	result = lv1_connect_पूर्णांकerrupt_event_receive_port(dev->bus_id,
		dev->dev_id, virq_to_hw(*virq), dev->पूर्णांकerrupt_id);

	अगर (result) अणु
		FAIL("%s:%d: lv1_connect_interrupt_event_receive_port"
			" failed: %s\n", __func__, __LINE__,
			ps3_result(result));
		ps3_event_receive_port_destroy(*virq);
		*virq = 0;
		वापस result;
	पूर्ण

	DBG("%s:%d: interrupt_id %u, virq %u\n", __func__, __LINE__,
		dev->पूर्णांकerrupt_id, *virq);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ps3_sb_event_receive_port_setup);

पूर्णांक ps3_sb_event_receive_port_destroy(काष्ठा ps3_प्रणाली_bus_device *dev,
	अचिन्हित पूर्णांक virq)
अणु
	/* this should go in प्रणाली-bus.c */

	पूर्णांक result;

	DBG(" -> %s:%d: interrupt_id %u, virq %u\n", __func__, __LINE__,
		dev->पूर्णांकerrupt_id, virq);

	result = lv1_disconnect_पूर्णांकerrupt_event_receive_port(dev->bus_id,
		dev->dev_id, virq_to_hw(virq), dev->पूर्णांकerrupt_id);

	अगर (result)
		FAIL("%s:%d: lv1_disconnect_interrupt_event_receive_port"
			" failed: %s\n", __func__, __LINE__,
			ps3_result(result));

	result = ps3_event_receive_port_destroy(virq);
	BUG_ON(result);

	/*
	 * ps3_event_receive_port_destroy() destroys the IRQ plug,
	 * so करोn't call ps3_irq_plug_destroy() here.
	 */

	result = ps3_virq_destroy(virq);
	BUG_ON(result);

	DBG(" <- %s:%d\n", __func__, __LINE__);
	वापस result;
पूर्ण
EXPORT_SYMBOL(ps3_sb_event_receive_port_destroy);

/**
 * ps3_io_irq_setup - Setup a प्रणाली bus io irq.
 * @cpu: क्रमागत ps3_cpu_binding indicating the cpu the पूर्णांकerrupt should be
 * serviced on.
 * @पूर्णांकerrupt_id: The device पूर्णांकerrupt id पढ़ो from the प्रणाली repository.
 * @virq: The asचिन्हित Linux virq.
 *
 * An io irq represents a non-भवized device पूर्णांकerrupt.  पूर्णांकerrupt_id
 * coresponds to the पूर्णांकerrupt number of the पूर्णांकerrupt controller.
 */

पूर्णांक ps3_io_irq_setup(क्रमागत ps3_cpu_binding cpu, अचिन्हित पूर्णांक पूर्णांकerrupt_id,
	अचिन्हित पूर्णांक *virq)
अणु
	पूर्णांक result;
	u64 outlet;

	result = lv1_स्थिरruct_io_irq_outlet(पूर्णांकerrupt_id, &outlet);

	अगर (result) अणु
		FAIL("%s:%d: lv1_construct_io_irq_outlet failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		वापस result;
	पूर्ण

	result = ps3_irq_plug_setup(cpu, outlet, virq);
	BUG_ON(result);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_io_irq_setup);

पूर्णांक ps3_io_irq_destroy(अचिन्हित पूर्णांक virq)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ outlet = virq_to_hw(virq);

	ps3_chip_mask(irq_get_irq_data(virq));

	/*
	 * lv1_deकाष्ठा_io_irq_outlet() will destroy the IRQ plug,
	 * so call ps3_irq_plug_destroy() first.
	 */

	result = ps3_irq_plug_destroy(virq);
	BUG_ON(result);

	result = lv1_deकाष्ठा_io_irq_outlet(outlet);

	अगर (result)
		FAIL("%s:%d: lv1_destruct_io_irq_outlet failed: %s\n",
			__func__, __LINE__, ps3_result(result));

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_io_irq_destroy);

/**
 * ps3_vuart_irq_setup - Setup the प्रणाली भव uart virq.
 * @cpu: क्रमागत ps3_cpu_binding indicating the cpu the पूर्णांकerrupt should be
 * serviced on.
 * @virt_addr_bmp: The caller supplied भव uart पूर्णांकerrupt biपंचांगap.
 * @virq: The asचिन्हित Linux virq.
 *
 * The प्रणाली supports only a single भव uart, so multiple calls without
 * मुक्तing the पूर्णांकerrupt will वापस a wrong state error.
 */

पूर्णांक ps3_vuart_irq_setup(क्रमागत ps3_cpu_binding cpu, व्योम* virt_addr_bmp,
	अचिन्हित पूर्णांक *virq)
अणु
	पूर्णांक result;
	u64 outlet;
	u64 lpar_addr;

	BUG_ON(!is_kernel_addr((u64)virt_addr_bmp));

	lpar_addr = ps3_mm_phys_to_lpar(__pa(virt_addr_bmp));

	result = lv1_configure_भव_uart_irq(lpar_addr, &outlet);

	अगर (result) अणु
		FAIL("%s:%d: lv1_configure_virtual_uart_irq failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		वापस result;
	पूर्ण

	result = ps3_irq_plug_setup(cpu, outlet, virq);
	BUG_ON(result);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_vuart_irq_setup);

पूर्णांक ps3_vuart_irq_destroy(अचिन्हित पूर्णांक virq)
अणु
	पूर्णांक result;

	ps3_chip_mask(irq_get_irq_data(virq));
	result = lv1_deconfigure_भव_uart_irq();

	अगर (result) अणु
		FAIL("%s:%d: lv1_configure_virtual_uart_irq failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		वापस result;
	पूर्ण

	result = ps3_irq_plug_destroy(virq);
	BUG_ON(result);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_vuart_irq_destroy);

/**
 * ps3_spe_irq_setup - Setup an spe virq.
 * @cpu: क्रमागत ps3_cpu_binding indicating the cpu the पूर्णांकerrupt should be
 * serviced on.
 * @spe_id: The spe_id वापसed from lv1_स्थिरruct_logical_spe().
 * @class: The spe पूर्णांकerrupt class अणु0,1,2पूर्ण.
 * @virq: The asचिन्हित Linux virq.
 *
 */

पूर्णांक ps3_spe_irq_setup(क्रमागत ps3_cpu_binding cpu, अचिन्हित दीर्घ spe_id,
	अचिन्हित पूर्णांक class, अचिन्हित पूर्णांक *virq)
अणु
	पूर्णांक result;
	u64 outlet;

	BUG_ON(class > 2);

	result = lv1_get_spe_irq_outlet(spe_id, class, &outlet);

	अगर (result) अणु
		FAIL("%s:%d: lv1_get_spe_irq_outlet failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		वापस result;
	पूर्ण

	result = ps3_irq_plug_setup(cpu, outlet, virq);
	BUG_ON(result);

	वापस result;
पूर्ण

पूर्णांक ps3_spe_irq_destroy(अचिन्हित पूर्णांक virq)
अणु
	पूर्णांक result;

	ps3_chip_mask(irq_get_irq_data(virq));

	result = ps3_irq_plug_destroy(virq);
	BUG_ON(result);

	वापस result;
पूर्ण


#घोषणा PS3_INVALID_OUTLET ((irq_hw_number_t)-1)
#घोषणा PS3_PLUG_MAX 63

#अगर defined(DEBUG)
अटल व्योम _dump_64_bmp(स्थिर अक्षर *header, स्थिर u64 *p, अचिन्हित cpu,
	स्थिर अक्षर* func, पूर्णांक line)
अणु
	pr_debug("%s:%d: %s %u {%04llx_%04llx_%04llx_%04llx}\n",
		func, line, header, cpu,
		*p >> 48, (*p >> 32) & 0xffff, (*p >> 16) & 0xffff,
		*p & 0xffff);
पूर्ण

अटल व्योम __maybe_unused _dump_256_bmp(स्थिर अक्षर *header,
	स्थिर u64 *p, अचिन्हित cpu, स्थिर अक्षर* func, पूर्णांक line)
अणु
	pr_debug("%s:%d: %s %u {%016llx:%016llx:%016llx:%016llx}\n",
		func, line, header, cpu, p[0], p[1], p[2], p[3]);
पूर्ण

#घोषणा dump_bmp(_x) _dump_bmp(_x, __func__, __LINE__)
अटल व्योम _dump_bmp(काष्ठा ps3_निजी* pd, स्थिर अक्षर* func, पूर्णांक line)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pd->bmp_lock, flags);
	_dump_64_bmp("stat", &pd->bmp.status, pd->thपढ़ो_id, func, line);
	_dump_64_bmp("mask", (u64*)&pd->bmp.mask, pd->thपढ़ो_id, func, line);
	spin_unlock_irqrestore(&pd->bmp_lock, flags);
पूर्ण

#घोषणा dump_mask(_x) _dump_mask(_x, __func__, __LINE__)
अटल व्योम __maybe_unused _dump_mask(काष्ठा ps3_निजी *pd,
	स्थिर अक्षर* func, पूर्णांक line)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pd->bmp_lock, flags);
	_dump_64_bmp("mask", (u64*)&pd->bmp.mask, pd->thपढ़ो_id, func, line);
	spin_unlock_irqrestore(&pd->bmp_lock, flags);
पूर्ण
#अन्यथा
अटल व्योम dump_bmp(काष्ठा ps3_निजी* pd) अणुपूर्ण;
#पूर्ण_अगर /* defined(DEBUG) */

अटल पूर्णांक ps3_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
	irq_hw_number_t hwirq)
अणु
	DBG("%s:%d: hwirq %lu, virq %u\n", __func__, __LINE__, hwirq,
		virq);

	irq_set_chip_and_handler(virq, &ps3_irq_chip, handle_fasteoi_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक ps3_host_match(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *np,
			  क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	/* Match all */
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ps3_host_ops = अणु
	.map = ps3_host_map,
	.match = ps3_host_match,
पूर्ण;

व्योम __init ps3_रेजिस्टर_ipi_debug_brk(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक virq)
अणु
	काष्ठा ps3_निजी *pd = &per_cpu(ps3_निजी, cpu);

	set_bit(63 - virq, &pd->ipi_debug_brk_mask);

	DBG("%s:%d: cpu %u, virq %u, mask %lxh\n", __func__, __LINE__,
		cpu, virq, pd->ipi_debug_brk_mask);
पूर्ण

व्योम __init ps3_रेजिस्टर_ipi_irq(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक virq)
अणु
	काष्ठा ps3_निजी *pd = &per_cpu(ps3_निजी, cpu);

	set_bit(63 - virq, &pd->ipi_mask);

	DBG("%s:%d: cpu %u, virq %u, ipi_mask %lxh\n", __func__, __LINE__,
		cpu, virq, pd->ipi_mask);
पूर्ण

अटल अचिन्हित पूर्णांक ps3_get_irq(व्योम)
अणु
	काष्ठा ps3_निजी *pd = this_cpu_ptr(&ps3_निजी);
	u64 x = (pd->bmp.status & pd->bmp.mask);
	अचिन्हित पूर्णांक plug;

	/* check क्रम ipi अवरोध first to stop this cpu ASAP */

	अगर (x & pd->ipi_debug_brk_mask)
		x &= pd->ipi_debug_brk_mask;

	यंत्र अस्थिर("cntlzd %0,%1" : "=r" (plug) : "r" (x));
	plug &= 0x3f;

	अगर (unlikely(!plug)) अणु
		DBG("%s:%d: no plug found: thread_id %llu\n", __func__,
			__LINE__, pd->thपढ़ो_id);
		dump_bmp(&per_cpu(ps3_निजी, 0));
		dump_bmp(&per_cpu(ps3_निजी, 1));
		वापस 0;
	पूर्ण

#अगर defined(DEBUG)
	अगर (unlikely(plug < NUM_ISA_INTERRUPTS || plug > PS3_PLUG_MAX)) अणु
		dump_bmp(&per_cpu(ps3_निजी, 0));
		dump_bmp(&per_cpu(ps3_निजी, 1));
		BUG();
	पूर्ण
#पूर्ण_अगर

	/* IPIs are EOIed here. */

	अगर (test_bit(63 - plug, &pd->ipi_mask))
		lv1_end_of_पूर्णांकerrupt_ext(pd->ppe_id, pd->thपढ़ो_id, plug);

	वापस plug;
पूर्ण

व्योम __init ps3_init_IRQ(व्योम)
अणु
	पूर्णांक result;
	अचिन्हित cpu;
	काष्ठा irq_करोमुख्य *host;

	host = irq_करोमुख्य_add_nomap(शून्य, PS3_PLUG_MAX + 1, &ps3_host_ops, शून्य);
	irq_set_शेष_host(host);

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा ps3_निजी *pd = &per_cpu(ps3_निजी, cpu);

		lv1_get_logical_ppe_id(&pd->ppe_id);
		pd->thपढ़ो_id = get_hard_smp_processor_id(cpu);
		spin_lock_init(&pd->bmp_lock);

		DBG("%s:%d: ppe_id %llu, thread_id %llu, bmp %lxh\n",
			__func__, __LINE__, pd->ppe_id, pd->thपढ़ो_id,
			ps3_mm_phys_to_lpar(__pa(&pd->bmp)));

		result = lv1_configure_irq_state_biपंचांगap(pd->ppe_id,
			pd->thपढ़ो_id, ps3_mm_phys_to_lpar(__pa(&pd->bmp)));

		अगर (result)
			FAIL("%s:%d: lv1_configure_irq_state_bitmap failed:"
				" %s\n", __func__, __LINE__,
				ps3_result(result));
	पूर्ण

	ppc_md.get_irq = ps3_get_irq;
पूर्ण

व्योम ps3_shutकरोwn_IRQ(पूर्णांक cpu)
अणु
	पूर्णांक result;
	u64 ppe_id;
	u64 thपढ़ो_id = get_hard_smp_processor_id(cpu);

	lv1_get_logical_ppe_id(&ppe_id);
	result = lv1_configure_irq_state_biपंचांगap(ppe_id, thपढ़ो_id, 0);

	DBG("%s:%d: lv1_configure_irq_state_bitmap (%llu:%llu/%d) %s\n", __func__,
		__LINE__, ppe_id, thपढ़ो_id, cpu, ps3_result(result));
पूर्ण
