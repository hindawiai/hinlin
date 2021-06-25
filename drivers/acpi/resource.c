<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/acpi/resource.c - ACPI device resources पूर्णांकerpretation.
 *
 * Copyright (C) 2012, Intel Corp.
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>

#अगर_घोषित CONFIG_X86
#घोषणा valid_IRQ(i) (((i) != 0) && ((i) != 2))
अटल अंतरभूत bool acpi_iospace_resource_valid(काष्ठा resource *res)
अणु
	/* On X86 IO space is limited to the [0 - 64K] IO port range */
	वापस res->end < 0x10003;
पूर्ण
#अन्यथा
#घोषणा valid_IRQ(i) (true)
/*
 * ACPI IO descriptors on arches other than X86 contain MMIO CPU physical
 * addresses mapping IO space in CPU physical address space, IO space
 * resources can be placed anywhere in the 64-bit physical address space.
 */
अटल अंतरभूत bool
acpi_iospace_resource_valid(काष्ठा resource *res) अणु वापस true; पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_ACPI_GENERIC_GSI)
अटल अंतरभूत bool is_gsi(काष्ठा acpi_resource_extended_irq *ext_irq)
अणु
	वापस ext_irq->resource_source.string_length == 0 &&
	       ext_irq->producer_consumer == ACPI_CONSUMER;
पूर्ण
#अन्यथा
अटल अंतरभूत bool is_gsi(काष्ठा acpi_resource_extended_irq *ext_irq)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल bool acpi_dev_resource_len_valid(u64 start, u64 end, u64 len, bool io)
अणु
	u64 reslen = end - start + 1;

	/*
	 * CHECKME: len might be required to check versus a minimum
	 * length as well. 1 क्रम io is fine, but क्रम memory it करोes
	 * not make any sense at all.
	 * Note: some BIOSes report incorrect length क्रम ACPI address space
	 * descriptor, so हटाओ check of 'reslen == len' to aव्योम regression.
	 */
	अगर (len && reslen && start <= end)
		वापस true;

	pr_debug("ACPI: invalid or unassigned resource %s [%016llx - %016llx] length [%016llx]\n",
		io ? "io" : "mem", start, end, len);

	वापस false;
पूर्ण

अटल व्योम acpi_dev_memresource_flags(काष्ठा resource *res, u64 len,
				       u8 ग_लिखो_protect)
अणु
	res->flags = IORESOURCE_MEM;

	अगर (!acpi_dev_resource_len_valid(res->start, res->end, len, false))
		res->flags |= IORESOURCE_DISABLED | IORESOURCE_UNSET;

	अगर (ग_लिखो_protect == ACPI_READ_WRITE_MEMORY)
		res->flags |= IORESOURCE_MEM_WRITEABLE;
पूर्ण

अटल व्योम acpi_dev_get_memresource(काष्ठा resource *res, u64 start, u64 len,
				     u8 ग_लिखो_protect)
अणु
	res->start = start;
	res->end = start + len - 1;
	acpi_dev_memresource_flags(res, len, ग_लिखो_protect);
पूर्ण

/**
 * acpi_dev_resource_memory - Extract ACPI memory resource inक्रमmation.
 * @ares: Input ACPI resource object.
 * @res: Output generic resource object.
 *
 * Check अगर the given ACPI resource object represents a memory resource and
 * अगर that's the हाल, use the inक्रमmation in it to populate the generic
 * resource object poपूर्णांकed to by @res.
 *
 * Return:
 * 1) false with res->flags setting to zero: not the expected resource type
 * 2) false with IORESOURCE_DISABLED in res->flags: valid unasचिन्हित resource
 * 3) true: valid asचिन्हित resource
 */
bool acpi_dev_resource_memory(काष्ठा acpi_resource *ares, काष्ठा resource *res)
अणु
	काष्ठा acpi_resource_memory24 *memory24;
	काष्ठा acpi_resource_memory32 *memory32;
	काष्ठा acpi_resource_fixed_memory32 *fixed_memory32;

	चयन (ares->type) अणु
	हाल ACPI_RESOURCE_TYPE_MEMORY24:
		memory24 = &ares->data.memory24;
		acpi_dev_get_memresource(res, memory24->minimum << 8,
					 memory24->address_length << 8,
					 memory24->ग_लिखो_protect);
		अवरोध;
	हाल ACPI_RESOURCE_TYPE_MEMORY32:
		memory32 = &ares->data.memory32;
		acpi_dev_get_memresource(res, memory32->minimum,
					 memory32->address_length,
					 memory32->ग_लिखो_protect);
		अवरोध;
	हाल ACPI_RESOURCE_TYPE_FIXED_MEMORY32:
		fixed_memory32 = &ares->data.fixed_memory32;
		acpi_dev_get_memresource(res, fixed_memory32->address,
					 fixed_memory32->address_length,
					 fixed_memory32->ग_लिखो_protect);
		अवरोध;
	शेष:
		res->flags = 0;
		वापस false;
	पूर्ण

	वापस !(res->flags & IORESOURCE_DISABLED);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_resource_memory);

अटल व्योम acpi_dev_ioresource_flags(काष्ठा resource *res, u64 len,
				      u8 io_decode, u8 translation_type)
अणु
	res->flags = IORESOURCE_IO;

	अगर (!acpi_dev_resource_len_valid(res->start, res->end, len, true))
		res->flags |= IORESOURCE_DISABLED | IORESOURCE_UNSET;

	अगर (!acpi_iospace_resource_valid(res))
		res->flags |= IORESOURCE_DISABLED | IORESOURCE_UNSET;

	अगर (io_decode == ACPI_DECODE_16)
		res->flags |= IORESOURCE_IO_16BIT_ADDR;
	अगर (translation_type == ACPI_SPARSE_TRANSLATION)
		res->flags |= IORESOURCE_IO_SPARSE;
पूर्ण

अटल व्योम acpi_dev_get_ioresource(काष्ठा resource *res, u64 start, u64 len,
				    u8 io_decode)
अणु
	res->start = start;
	res->end = start + len - 1;
	acpi_dev_ioresource_flags(res, len, io_decode, 0);
पूर्ण

/**
 * acpi_dev_resource_io - Extract ACPI I/O resource inक्रमmation.
 * @ares: Input ACPI resource object.
 * @res: Output generic resource object.
 *
 * Check अगर the given ACPI resource object represents an I/O resource and
 * अगर that's the हाल, use the inक्रमmation in it to populate the generic
 * resource object poपूर्णांकed to by @res.
 *
 * Return:
 * 1) false with res->flags setting to zero: not the expected resource type
 * 2) false with IORESOURCE_DISABLED in res->flags: valid unasचिन्हित resource
 * 3) true: valid asचिन्हित resource
 */
bool acpi_dev_resource_io(काष्ठा acpi_resource *ares, काष्ठा resource *res)
अणु
	काष्ठा acpi_resource_io *io;
	काष्ठा acpi_resource_fixed_io *fixed_io;

	चयन (ares->type) अणु
	हाल ACPI_RESOURCE_TYPE_IO:
		io = &ares->data.io;
		acpi_dev_get_ioresource(res, io->minimum,
					io->address_length,
					io->io_decode);
		अवरोध;
	हाल ACPI_RESOURCE_TYPE_FIXED_IO:
		fixed_io = &ares->data.fixed_io;
		acpi_dev_get_ioresource(res, fixed_io->address,
					fixed_io->address_length,
					ACPI_DECODE_10);
		अवरोध;
	शेष:
		res->flags = 0;
		वापस false;
	पूर्ण

	वापस !(res->flags & IORESOURCE_DISABLED);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_resource_io);

अटल bool acpi_decode_space(काष्ठा resource_win *win,
			      काष्ठा acpi_resource_address *addr,
			      काष्ठा acpi_address64_attribute *attr)
अणु
	u8 iodec = attr->granularity == 0xfff ? ACPI_DECODE_10 : ACPI_DECODE_16;
	bool wp = addr->info.mem.ग_लिखो_protect;
	u64 len = attr->address_length;
	u64 start, end, offset = 0;
	काष्ठा resource *res = &win->res;

	/*
	 * Filter out invalid descriptor according to ACPI Spec 5.0, section
	 * 6.4.3.5 Address Space Resource Descriptors.
	 */
	अगर ((addr->min_address_fixed != addr->max_address_fixed && len) ||
	    (addr->min_address_fixed && addr->max_address_fixed && !len))
		pr_debug("ACPI: Invalid address space min_addr_fix %d, max_addr_fix %d, len %llx\n",
			 addr->min_address_fixed, addr->max_address_fixed, len);

	/*
	 * For bridges that translate addresses across the bridge,
	 * translation_offset is the offset that must be added to the
	 * address on the secondary side to obtain the address on the
	 * primary side. Non-bridge devices must list 0 क्रम all Address
	 * Translation offset bits.
	 */
	अगर (addr->producer_consumer == ACPI_PRODUCER)
		offset = attr->translation_offset;
	अन्यथा अगर (attr->translation_offset)
		pr_debug("ACPI: translation_offset(%lld) is invalid for non-bridge device.\n",
			 attr->translation_offset);
	start = attr->minimum + offset;
	end = attr->maximum + offset;

	win->offset = offset;
	res->start = start;
	res->end = end;
	अगर (माप(resource_माप_प्रकार) < माप(u64) &&
	    (offset != win->offset || start != res->start || end != res->end)) अणु
		pr_warn("acpi resource window ([%#llx-%#llx] ignored, not CPU addressable)\n",
			attr->minimum, attr->maximum);
		वापस false;
	पूर्ण

	चयन (addr->resource_type) अणु
	हाल ACPI_MEMORY_RANGE:
		acpi_dev_memresource_flags(res, len, wp);
		अवरोध;
	हाल ACPI_IO_RANGE:
		acpi_dev_ioresource_flags(res, len, iodec,
					  addr->info.io.translation_type);
		अवरोध;
	हाल ACPI_BUS_NUMBER_RANGE:
		res->flags = IORESOURCE_BUS;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर (addr->producer_consumer == ACPI_PRODUCER)
		res->flags |= IORESOURCE_WINDOW;

	अगर (addr->info.mem.caching == ACPI_PREFETCHABLE_MEMORY)
		res->flags |= IORESOURCE_PREFETCH;

	वापस !(res->flags & IORESOURCE_DISABLED);
पूर्ण

/**
 * acpi_dev_resource_address_space - Extract ACPI address space inक्रमmation.
 * @ares: Input ACPI resource object.
 * @win: Output generic resource object.
 *
 * Check अगर the given ACPI resource object represents an address space resource
 * and अगर that's the हाल, use the inक्रमmation in it to populate the generic
 * resource object poपूर्णांकed to by @win.
 *
 * Return:
 * 1) false with win->res.flags setting to zero: not the expected resource type
 * 2) false with IORESOURCE_DISABLED in win->res.flags: valid unasचिन्हित
 *    resource
 * 3) true: valid asचिन्हित resource
 */
bool acpi_dev_resource_address_space(काष्ठा acpi_resource *ares,
				     काष्ठा resource_win *win)
अणु
	काष्ठा acpi_resource_address64 addr;

	win->res.flags = 0;
	अगर (ACPI_FAILURE(acpi_resource_to_address64(ares, &addr)))
		वापस false;

	वापस acpi_decode_space(win, (काष्ठा acpi_resource_address *)&addr,
				 &addr.address);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_resource_address_space);

/**
 * acpi_dev_resource_ext_address_space - Extract ACPI address space inक्रमmation.
 * @ares: Input ACPI resource object.
 * @win: Output generic resource object.
 *
 * Check अगर the given ACPI resource object represents an extended address space
 * resource and अगर that's the हाल, use the inक्रमmation in it to populate the
 * generic resource object poपूर्णांकed to by @win.
 *
 * Return:
 * 1) false with win->res.flags setting to zero: not the expected resource type
 * 2) false with IORESOURCE_DISABLED in win->res.flags: valid unasचिन्हित
 *    resource
 * 3) true: valid asचिन्हित resource
 */
bool acpi_dev_resource_ext_address_space(काष्ठा acpi_resource *ares,
					 काष्ठा resource_win *win)
अणु
	काष्ठा acpi_resource_extended_address64 *ext_addr;

	win->res.flags = 0;
	अगर (ares->type != ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64)
		वापस false;

	ext_addr = &ares->data.ext_address64;

	वापस acpi_decode_space(win, (काष्ठा acpi_resource_address *)ext_addr,
				 &ext_addr->address);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_resource_ext_address_space);

/**
 * acpi_dev_irq_flags - Determine IRQ resource flags.
 * @triggering: Triggering type as provided by ACPI.
 * @polarity: Interrupt polarity as provided by ACPI.
 * @shareable: Whether or not the पूर्णांकerrupt is shareable.
 */
अचिन्हित दीर्घ acpi_dev_irq_flags(u8 triggering, u8 polarity, u8 shareable)
अणु
	अचिन्हित दीर्घ flags;

	अगर (triggering == ACPI_LEVEL_SENSITIVE)
		flags = polarity == ACPI_ACTIVE_LOW ?
			IORESOURCE_IRQ_LOWLEVEL : IORESOURCE_IRQ_HIGHLEVEL;
	अन्यथा
		flags = polarity == ACPI_ACTIVE_LOW ?
			IORESOURCE_IRQ_LOWEDGE : IORESOURCE_IRQ_HIGHEDGE;

	अगर (shareable == ACPI_SHARED)
		flags |= IORESOURCE_IRQ_SHAREABLE;

	वापस flags | IORESOURCE_IRQ;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_irq_flags);

/**
 * acpi_dev_get_irq_type - Determine irq type.
 * @triggering: Triggering type as provided by ACPI.
 * @polarity: Interrupt polarity as provided by ACPI.
 */
अचिन्हित पूर्णांक acpi_dev_get_irq_type(पूर्णांक triggering, पूर्णांक polarity)
अणु
	चयन (polarity) अणु
	हाल ACPI_ACTIVE_LOW:
		वापस triggering == ACPI_EDGE_SENSITIVE ?
		       IRQ_TYPE_EDGE_FALLING :
		       IRQ_TYPE_LEVEL_LOW;
	हाल ACPI_ACTIVE_HIGH:
		वापस triggering == ACPI_EDGE_SENSITIVE ?
		       IRQ_TYPE_EDGE_RISING :
		       IRQ_TYPE_LEVEL_HIGH;
	हाल ACPI_ACTIVE_BOTH:
		अगर (triggering == ACPI_EDGE_SENSITIVE)
			वापस IRQ_TYPE_EDGE_BOTH;
		fallthrough;
	शेष:
		वापस IRQ_TYPE_NONE;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_get_irq_type);

अटल व्योम acpi_dev_get_irqresource(काष्ठा resource *res, u32 gsi,
				     u8 triggering, u8 polarity, u8 shareable,
				     bool legacy)
अणु
	पूर्णांक irq, p, t;

	अगर (!valid_IRQ(gsi)) अणु
		irqresource_disabled(res, gsi);
		वापस;
	पूर्ण

	/*
	 * In IO-APIC mode, use overridden attribute. Two reasons:
	 * 1. BIOS bug in DSDT
	 * 2. BIOS uses IO-APIC mode Interrupt Source Override
	 *
	 * We करो this only अगर we are dealing with IRQ() or IRQNoFlags()
	 * resource (the legacy ISA resources). With modern ACPI 5 devices
	 * using extended IRQ descriptors we take the IRQ configuration
	 * from _CRS directly.
	 */
	अगर (legacy && !acpi_get_override_irq(gsi, &t, &p)) अणु
		u8 trig = t ? ACPI_LEVEL_SENSITIVE : ACPI_EDGE_SENSITIVE;
		u8 pol = p ? ACPI_ACTIVE_LOW : ACPI_ACTIVE_HIGH;

		अगर (triggering != trig || polarity != pol) अणु
			pr_warn("ACPI: IRQ %d override to %s, %s\n", gsi,
				t ? "level" : "edge", p ? "low" : "high");
			triggering = trig;
			polarity = pol;
		पूर्ण
	पूर्ण

	res->flags = acpi_dev_irq_flags(triggering, polarity, shareable);
	irq = acpi_रेजिस्टर_gsi(शून्य, gsi, triggering, polarity);
	अगर (irq >= 0) अणु
		res->start = irq;
		res->end = irq;
	पूर्ण अन्यथा अणु
		irqresource_disabled(res, gsi);
	पूर्ण
पूर्ण

/**
 * acpi_dev_resource_पूर्णांकerrupt - Extract ACPI पूर्णांकerrupt resource inक्रमmation.
 * @ares: Input ACPI resource object.
 * @index: Index पूर्णांकo the array of GSIs represented by the resource.
 * @res: Output generic resource object.
 *
 * Check अगर the given ACPI resource object represents an पूर्णांकerrupt resource
 * and @index करोes not exceed the resource's पूर्णांकerrupt count (true is वापसed
 * in that हाल regardless of the results of the other checks)).  If that's the
 * हाल, रेजिस्टर the GSI corresponding to @index from the array of पूर्णांकerrupts
 * represented by the resource and populate the generic resource object poपूर्णांकed
 * to by @res accordingly.  If the registration of the GSI is not successful,
 * IORESOURCE_DISABLED will be set it that object's flags.
 *
 * Return:
 * 1) false with res->flags setting to zero: not the expected resource type
 * 2) false with IORESOURCE_DISABLED in res->flags: valid unasचिन्हित resource
 * 3) true: valid asचिन्हित resource
 */
bool acpi_dev_resource_पूर्णांकerrupt(काष्ठा acpi_resource *ares, पूर्णांक index,
				 काष्ठा resource *res)
अणु
	काष्ठा acpi_resource_irq *irq;
	काष्ठा acpi_resource_extended_irq *ext_irq;

	चयन (ares->type) अणु
	हाल ACPI_RESOURCE_TYPE_IRQ:
		/*
		 * Per spec, only one पूर्णांकerrupt per descriptor is allowed in
		 * _CRS, but some firmware violates this, so parse them all.
		 */
		irq = &ares->data.irq;
		अगर (index >= irq->पूर्णांकerrupt_count) अणु
			irqresource_disabled(res, 0);
			वापस false;
		पूर्ण
		acpi_dev_get_irqresource(res, irq->पूर्णांकerrupts[index],
					 irq->triggering, irq->polarity,
					 irq->shareable, true);
		अवरोध;
	हाल ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
		ext_irq = &ares->data.extended_irq;
		अगर (index >= ext_irq->पूर्णांकerrupt_count) अणु
			irqresource_disabled(res, 0);
			वापस false;
		पूर्ण
		अगर (is_gsi(ext_irq))
			acpi_dev_get_irqresource(res, ext_irq->पूर्णांकerrupts[index],
					 ext_irq->triggering, ext_irq->polarity,
					 ext_irq->shareable, false);
		अन्यथा
			irqresource_disabled(res, 0);
		अवरोध;
	शेष:
		res->flags = 0;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_resource_पूर्णांकerrupt);

/**
 * acpi_dev_मुक्त_resource_list - Free resource from %acpi_dev_get_resources().
 * @list: The head of the resource list to मुक्त.
 */
व्योम acpi_dev_मुक्त_resource_list(काष्ठा list_head *list)
अणु
	resource_list_मुक्त(list);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_मुक्त_resource_list);

काष्ठा res_proc_context अणु
	काष्ठा list_head *list;
	पूर्णांक (*preproc)(काष्ठा acpi_resource *, व्योम *);
	व्योम *preproc_data;
	पूर्णांक count;
	पूर्णांक error;
पूर्ण;

अटल acpi_status acpi_dev_new_resource_entry(काष्ठा resource_win *win,
					       काष्ठा res_proc_context *c)
अणु
	काष्ठा resource_entry *rentry;

	rentry = resource_list_create_entry(शून्य, 0);
	अगर (!rentry) अणु
		c->error = -ENOMEM;
		वापस AE_NO_MEMORY;
	पूर्ण
	*rentry->res = win->res;
	rentry->offset = win->offset;
	resource_list_add_tail(rentry, c->list);
	c->count++;
	वापस AE_OK;
पूर्ण

अटल acpi_status acpi_dev_process_resource(काष्ठा acpi_resource *ares,
					     व्योम *context)
अणु
	काष्ठा res_proc_context *c = context;
	काष्ठा resource_win win;
	काष्ठा resource *res = &win.res;
	पूर्णांक i;

	अगर (c->preproc) अणु
		पूर्णांक ret;

		ret = c->preproc(ares, c->preproc_data);
		अगर (ret < 0) अणु
			c->error = ret;
			वापस AE_ABORT_METHOD;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			वापस AE_OK;
		पूर्ण
	पूर्ण

	स_रखो(&win, 0, माप(win));

	अगर (acpi_dev_resource_memory(ares, res)
	    || acpi_dev_resource_io(ares, res)
	    || acpi_dev_resource_address_space(ares, &win)
	    || acpi_dev_resource_ext_address_space(ares, &win))
		वापस acpi_dev_new_resource_entry(&win, c);

	क्रम (i = 0; acpi_dev_resource_पूर्णांकerrupt(ares, i, res); i++) अणु
		acpi_status status;

		status = acpi_dev_new_resource_entry(&win, c);
		अगर (ACPI_FAILURE(status))
			वापस status;
	पूर्ण

	वापस AE_OK;
पूर्ण

अटल पूर्णांक __acpi_dev_get_resources(काष्ठा acpi_device *adev,
				    काष्ठा list_head *list,
				    पूर्णांक (*preproc)(काष्ठा acpi_resource *, व्योम *),
				    व्योम *preproc_data, अक्षर *method)
अणु
	काष्ठा res_proc_context c;
	acpi_status status;

	अगर (!adev || !adev->handle || !list_empty(list))
		वापस -EINVAL;

	अगर (!acpi_has_method(adev->handle, method))
		वापस 0;

	c.list = list;
	c.preproc = preproc;
	c.preproc_data = preproc_data;
	c.count = 0;
	c.error = 0;
	status = acpi_walk_resources(adev->handle, method,
				     acpi_dev_process_resource, &c);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_dev_मुक्त_resource_list(list);
		वापस c.error ? c.error : -EIO;
	पूर्ण

	वापस c.count;
पूर्ण

/**
 * acpi_dev_get_resources - Get current resources of a device.
 * @adev: ACPI device node to get the resources क्रम.
 * @list: Head of the resultant list of resources (must be empty).
 * @preproc: The caller's preprocessing routine.
 * @preproc_data: Poपूर्णांकer passed to the caller's preprocessing routine.
 *
 * Evaluate the _CRS method क्रम the given device node and process its output by
 * (1) executing the @preproc() routine provided by the caller, passing the
 * resource poपूर्णांकer and @preproc_data to it as arguments, क्रम each ACPI resource
 * वापसed and (2) converting all of the वापसed ACPI resources पूर्णांकo काष्ठा
 * resource objects अगर possible.  If the वापस value of @preproc() in step (1)
 * is dअगरferent from 0, step (2) is not applied to the given ACPI resource and
 * अगर that value is negative, the whole processing is पातed and that value is
 * वापसed as the final error code.
 *
 * The resultant काष्ठा resource objects are put on the list poपूर्णांकed to by
 * @list, that must be empty initially, as members of काष्ठा resource_entry
 * objects.  Callers of this routine should use %acpi_dev_मुक्त_resource_list() to
 * मुक्त that list.
 *
 * The number of resources in the output list is वापसed on success, an error
 * code reflecting the error condition is वापसed otherwise.
 */
पूर्णांक acpi_dev_get_resources(काष्ठा acpi_device *adev, काष्ठा list_head *list,
			   पूर्णांक (*preproc)(काष्ठा acpi_resource *, व्योम *),
			   व्योम *preproc_data)
अणु
	वापस __acpi_dev_get_resources(adev, list, preproc, preproc_data,
					METHOD_NAME__CRS);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_get_resources);

अटल पूर्णांक is_memory(काष्ठा acpi_resource *ares, व्योम *not_used)
अणु
	काष्ठा resource_win win;
	काष्ठा resource *res = &win.res;

	स_रखो(&win, 0, माप(win));

	वापस !(acpi_dev_resource_memory(ares, res)
	       || acpi_dev_resource_address_space(ares, &win)
	       || acpi_dev_resource_ext_address_space(ares, &win));
पूर्ण

/**
 * acpi_dev_get_dma_resources - Get current DMA resources of a device.
 * @adev: ACPI device node to get the resources क्रम.
 * @list: Head of the resultant list of resources (must be empty).
 *
 * Evaluate the _DMA method क्रम the given device node and process its
 * output.
 *
 * The resultant काष्ठा resource objects are put on the list poपूर्णांकed to
 * by @list, that must be empty initially, as members of काष्ठा
 * resource_entry objects.  Callers of this routine should use
 * %acpi_dev_मुक्त_resource_list() to मुक्त that list.
 *
 * The number of resources in the output list is वापसed on success,
 * an error code reflecting the error condition is वापसed otherwise.
 */
पूर्णांक acpi_dev_get_dma_resources(काष्ठा acpi_device *adev, काष्ठा list_head *list)
अणु
	वापस __acpi_dev_get_resources(adev, list, is_memory, शून्य,
					METHOD_NAME__DMA);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_get_dma_resources);

/**
 * acpi_dev_filter_resource_type - Filter ACPI resource according to resource
 *				   types
 * @ares: Input ACPI resource object.
 * @types: Valid resource types of IORESOURCE_XXX
 *
 * This is a helper function to support acpi_dev_get_resources(), which filters
 * ACPI resource objects according to resource types.
 */
पूर्णांक acpi_dev_filter_resource_type(काष्ठा acpi_resource *ares,
				  अचिन्हित दीर्घ types)
अणु
	अचिन्हित दीर्घ type = 0;

	चयन (ares->type) अणु
	हाल ACPI_RESOURCE_TYPE_MEMORY24:
	हाल ACPI_RESOURCE_TYPE_MEMORY32:
	हाल ACPI_RESOURCE_TYPE_FIXED_MEMORY32:
		type = IORESOURCE_MEM;
		अवरोध;
	हाल ACPI_RESOURCE_TYPE_IO:
	हाल ACPI_RESOURCE_TYPE_FIXED_IO:
		type = IORESOURCE_IO;
		अवरोध;
	हाल ACPI_RESOURCE_TYPE_IRQ:
	हाल ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
		type = IORESOURCE_IRQ;
		अवरोध;
	हाल ACPI_RESOURCE_TYPE_DMA:
	हाल ACPI_RESOURCE_TYPE_FIXED_DMA:
		type = IORESOURCE_DMA;
		अवरोध;
	हाल ACPI_RESOURCE_TYPE_GENERIC_REGISTER:
		type = IORESOURCE_REG;
		अवरोध;
	हाल ACPI_RESOURCE_TYPE_ADDRESS16:
	हाल ACPI_RESOURCE_TYPE_ADDRESS32:
	हाल ACPI_RESOURCE_TYPE_ADDRESS64:
	हाल ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64:
		अगर (ares->data.address.resource_type == ACPI_MEMORY_RANGE)
			type = IORESOURCE_MEM;
		अन्यथा अगर (ares->data.address.resource_type == ACPI_IO_RANGE)
			type = IORESOURCE_IO;
		अन्यथा अगर (ares->data.address.resource_type ==
			 ACPI_BUS_NUMBER_RANGE)
			type = IORESOURCE_BUS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस (type & types) ? 0 : 1;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_filter_resource_type);

अटल पूर्णांक acpi_dev_consumes_res(काष्ठा acpi_device *adev, काष्ठा resource *res)
अणु
	काष्ठा list_head resource_list;
	काष्ठा resource_entry *rentry;
	पूर्णांक ret, found = 0;

	INIT_LIST_HEAD(&resource_list);
	ret = acpi_dev_get_resources(adev, &resource_list, शून्य, शून्य);
	अगर (ret < 0)
		वापस 0;

	list_क्रम_each_entry(rentry, &resource_list, node) अणु
		अगर (resource_contains(rentry->res, res)) अणु
			found = 1;
			अवरोध;
		पूर्ण

	पूर्ण

	acpi_dev_मुक्त_resource_list(&resource_list);
	वापस found;
पूर्ण

अटल acpi_status acpi_res_consumer_cb(acpi_handle handle, u32 depth,
					 व्योम *context, व्योम **ret)
अणु
	काष्ठा resource *res = context;
	काष्ठा acpi_device **consumer = (काष्ठा acpi_device **) ret;
	काष्ठा acpi_device *adev;

	अगर (acpi_bus_get_device(handle, &adev))
		वापस AE_OK;

	अगर (acpi_dev_consumes_res(adev, res)) अणु
		*consumer = adev;
		वापस AE_CTRL_TERMINATE;
	पूर्ण

	वापस AE_OK;
पूर्ण

/**
 * acpi_resource_consumer - Find the ACPI device that consumes @res.
 * @res: Resource to search क्रम.
 *
 * Search the current resource settings (_CRS) of every ACPI device node
 * क्रम @res.  If we find an ACPI device whose _CRS includes @res, वापस
 * it.  Otherwise, वापस शून्य.
 */
काष्ठा acpi_device *acpi_resource_consumer(काष्ठा resource *res)
अणु
	काष्ठा acpi_device *consumer = शून्य;

	acpi_get_devices(शून्य, acpi_res_consumer_cb, res, (व्योम **) &consumer);
	वापस consumer;
पूर्ण
