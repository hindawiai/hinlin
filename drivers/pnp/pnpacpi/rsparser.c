<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pnpacpi -- PnP ACPI driver
 *
 * Copyright (c) 2004 Matthieu Castet <castet.matthieu@मुक्त.fr>
 * Copyright (c) 2004 Li Shaohua <shaohua.li@पूर्णांकel.com>
 * Copyright (C) 2008 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pci.h>
#समावेश <linux/pnp.h>
#समावेश <linux/slab.h>
#समावेश "../base.h"
#समावेश "pnpacpi.h"

अटल व्योम decode_irq_flags(काष्ठा pnp_dev *dev, पूर्णांक flags, u8 *triggering,
			     u8 *polarity, u8 *shareable)
अणु
	चयन (flags & (IORESOURCE_IRQ_LOWLEVEL | IORESOURCE_IRQ_HIGHLEVEL |
			 IORESOURCE_IRQ_LOWEDGE  | IORESOURCE_IRQ_HIGHEDGE)) अणु
	हाल IORESOURCE_IRQ_LOWLEVEL:
		*triggering = ACPI_LEVEL_SENSITIVE;
		*polarity = ACPI_ACTIVE_LOW;
		अवरोध;
	हाल IORESOURCE_IRQ_HIGHLEVEL:
		*triggering = ACPI_LEVEL_SENSITIVE;
		*polarity = ACPI_ACTIVE_HIGH;
		अवरोध;
	हाल IORESOURCE_IRQ_LOWEDGE:
		*triggering = ACPI_EDGE_SENSITIVE;
		*polarity = ACPI_ACTIVE_LOW;
		अवरोध;
	हाल IORESOURCE_IRQ_HIGHEDGE:
		*triggering = ACPI_EDGE_SENSITIVE;
		*polarity = ACPI_ACTIVE_HIGH;
		अवरोध;
	शेष:
		dev_err(&dev->dev, "can't encode invalid IRQ mode %#x\n",
			flags);
		*triggering = ACPI_EDGE_SENSITIVE;
		*polarity = ACPI_ACTIVE_HIGH;
		अवरोध;
	पूर्ण

	अगर (flags & IORESOURCE_IRQ_SHAREABLE)
		*shareable = ACPI_SHARED;
	अन्यथा
		*shareable = ACPI_EXCLUSIVE;
पूर्ण

अटल पूर्णांक dma_flags(काष्ठा pnp_dev *dev, पूर्णांक type, पूर्णांक bus_master,
		     पूर्णांक transfer)
अणु
	पूर्णांक flags = 0;

	अगर (bus_master)
		flags |= IORESOURCE_DMA_MASTER;
	चयन (type) अणु
	हाल ACPI_COMPATIBILITY:
		flags |= IORESOURCE_DMA_COMPATIBLE;
		अवरोध;
	हाल ACPI_TYPE_A:
		flags |= IORESOURCE_DMA_TYPEA;
		अवरोध;
	हाल ACPI_TYPE_B:
		flags |= IORESOURCE_DMA_TYPEB;
		अवरोध;
	हाल ACPI_TYPE_F:
		flags |= IORESOURCE_DMA_TYPEF;
		अवरोध;
	शेष:
		/* Set a शेष value ? */
		flags |= IORESOURCE_DMA_COMPATIBLE;
		dev_err(&dev->dev, "invalid DMA type %d\n", type);
	पूर्ण
	चयन (transfer) अणु
	हाल ACPI_TRANSFER_8:
		flags |= IORESOURCE_DMA_8BIT;
		अवरोध;
	हाल ACPI_TRANSFER_8_16:
		flags |= IORESOURCE_DMA_8AND16BIT;
		अवरोध;
	हाल ACPI_TRANSFER_16:
		flags |= IORESOURCE_DMA_16BIT;
		अवरोध;
	शेष:
		/* Set a शेष value ? */
		flags |= IORESOURCE_DMA_8AND16BIT;
		dev_err(&dev->dev, "invalid DMA transfer type %d\n", transfer);
	पूर्ण

	वापस flags;
पूर्ण

/*
 * Allocated Resources
 */

अटल व्योम pnpacpi_add_irqresource(काष्ठा pnp_dev *dev, काष्ठा resource *r)
अणु
	अगर (!(r->flags & IORESOURCE_DISABLED))
		pcibios_penalize_isa_irq(r->start, 1);

	pnp_add_resource(dev, r);
पूर्ण

/*
 * Device CSRs that करो not appear in PCI config space should be described
 * via ACPI.  This would normally be करोne with Address Space Descriptors
 * marked as "consumer-only," but old versions of Winकरोws and Linux ignore
 * the producer/consumer flag, so HP invented a venकरोr-defined resource to
 * describe the location and size of CSR space.
 */
अटल काष्ठा acpi_venकरोr_uuid hp_ccsr_uuid = अणु
	.subtype = 2,
	.data = अणु 0xf9, 0xad, 0xe9, 0x69, 0x4f, 0x92, 0x5f, 0xab, 0xf6, 0x4a,
	    0x24, 0xd2, 0x01, 0x37, 0x0e, 0xad पूर्ण,
पूर्ण;

अटल पूर्णांक venकरोr_resource_matches(काष्ठा pnp_dev *dev,
				   काष्ठा acpi_resource_venकरोr_typed *venकरोr,
				   काष्ठा acpi_venकरोr_uuid *match,
				   पूर्णांक expected_len)
अणु
	पूर्णांक uuid_len = माप(venकरोr->uuid);
	u8 uuid_subtype = venकरोr->uuid_subtype;
	u8 *uuid = venकरोr->uuid;
	पूर्णांक actual_len;

	/* byte_length includes uuid_subtype and uuid */
	actual_len = venकरोr->byte_length - uuid_len - 1;

	अगर (uuid_subtype == match->subtype &&
	    uuid_len == माप(match->data) &&
	    स_भेद(uuid, match->data, uuid_len) == 0) अणु
		अगर (expected_len && expected_len != actual_len) अणु
			dev_err(&dev->dev,
				"wrong vendor descriptor size; expected %d, found %d bytes\n",
				expected_len, actual_len);
			वापस 0;
		पूर्ण

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pnpacpi_parse_allocated_venकरोr(काष्ठा pnp_dev *dev,
				    काष्ठा acpi_resource_venकरोr_typed *venकरोr)
अणु
	अगर (venकरोr_resource_matches(dev, venकरोr, &hp_ccsr_uuid, 16)) अणु
		u64 start, length;

		स_नकल(&start, venकरोr->byte_data, माप(start));
		स_नकल(&length, venकरोr->byte_data + 8, माप(length));

		pnp_add_mem_resource(dev, start, start + length - 1, 0);
	पूर्ण
पूर्ण

अटल acpi_status pnpacpi_allocated_resource(काष्ठा acpi_resource *res,
					      व्योम *data)
अणु
	काष्ठा pnp_dev *dev = data;
	काष्ठा acpi_resource_dma *dma;
	काष्ठा acpi_resource_venकरोr_typed *venकरोr_typed;
	काष्ठा acpi_resource_gpio *gpio;
	काष्ठा resource_win win = अणुअणु0पूर्ण, 0पूर्ण;
	काष्ठा resource *r = &win.res;
	पूर्णांक i, flags;

	अगर (acpi_dev_resource_address_space(res, &win)
	    || acpi_dev_resource_ext_address_space(res, &win)) अणु
		pnp_add_resource(dev, &win.res);
		वापस AE_OK;
	पूर्ण

	r->flags = 0;
	अगर (acpi_dev_resource_पूर्णांकerrupt(res, 0, r)) अणु
		pnpacpi_add_irqresource(dev, r);
		क्रम (i = 1; acpi_dev_resource_पूर्णांकerrupt(res, i, r); i++)
			pnpacpi_add_irqresource(dev, r);

		अगर (i > 1) अणु
			/*
			 * The IRQ encoder माला_दो a single पूर्णांकerrupt in each
			 * descriptor, so अगर a _CRS descriptor has more than
			 * one पूर्णांकerrupt, we won't be able to re-encode it.
			 */
			अगर (pnp_can_ग_लिखो(dev)) अणु
				dev_warn(&dev->dev,
					 "multiple interrupts in _CRS descriptor; configuration can't be changed\n");
				dev->capabilities &= ~PNP_WRITE;
			पूर्ण
		पूर्ण
		वापस AE_OK;
	पूर्ण अन्यथा अगर (acpi_gpio_get_irq_resource(res, &gpio)) अणु
		/*
		 * If the resource is GpioInt() type then extract the IRQ
		 * from GPIO resource and fill it पूर्णांकo IRQ resource type.
		 */
		i = acpi_dev_gpio_irq_get(dev->data, 0);
		अगर (i >= 0) अणु
			flags = acpi_dev_irq_flags(gpio->triggering,
						   gpio->polarity,
						   gpio->shareable);
		पूर्ण अन्यथा अणु
			flags = IORESOURCE_DISABLED;
		पूर्ण
		pnp_add_irq_resource(dev, i, flags);
		वापस AE_OK;
	पूर्ण अन्यथा अगर (r->flags & IORESOURCE_DISABLED) अणु
		pnp_add_irq_resource(dev, 0, IORESOURCE_DISABLED);
		वापस AE_OK;
	पूर्ण

	चयन (res->type) अणु
	हाल ACPI_RESOURCE_TYPE_MEMORY24:
	हाल ACPI_RESOURCE_TYPE_MEMORY32:
	हाल ACPI_RESOURCE_TYPE_FIXED_MEMORY32:
		अगर (acpi_dev_resource_memory(res, r))
			pnp_add_resource(dev, r);
		अवरोध;
	हाल ACPI_RESOURCE_TYPE_IO:
	हाल ACPI_RESOURCE_TYPE_FIXED_IO:
		अगर (acpi_dev_resource_io(res, r))
			pnp_add_resource(dev, r);
		अवरोध;
	हाल ACPI_RESOURCE_TYPE_DMA:
		dma = &res->data.dma;
		अगर (dma->channel_count > 0 && dma->channels[0] != (u8) -1)
			flags = dma_flags(dev, dma->type, dma->bus_master,
					  dma->transfer);
		अन्यथा
			flags = IORESOURCE_DISABLED;
		pnp_add_dma_resource(dev, dma->channels[0], flags);
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_START_DEPENDENT:
	हाल ACPI_RESOURCE_TYPE_END_DEPENDENT:
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_VENDOR:
		venकरोr_typed = &res->data.venकरोr_typed;
		pnpacpi_parse_allocated_venकरोr(dev, venकरोr_typed);
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_END_TAG:
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_GENERIC_REGISTER:
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_SERIAL_BUS:
		/* serial bus connections (I2C/SPI/UART) are not pnp */
		अवरोध;

	शेष:
		dev_warn(&dev->dev, "unknown resource type %d in _CRS\n",
			 res->type);
		वापस AE_ERROR;
	पूर्ण

	वापस AE_OK;
पूर्ण

पूर्णांक pnpacpi_parse_allocated_resource(काष्ठा pnp_dev *dev)
अणु
	काष्ठा acpi_device *acpi_dev = dev->data;
	acpi_handle handle = acpi_dev->handle;
	acpi_status status;

	pnp_dbg(&dev->dev, "parse allocated resources\n");

	pnp_init_resources(dev);

	status = acpi_walk_resources(handle, METHOD_NAME__CRS,
				     pnpacpi_allocated_resource, dev);

	अगर (ACPI_FAILURE(status)) अणु
		अगर (status != AE_NOT_FOUND)
			dev_err(&dev->dev, "can't evaluate _CRS: %d", status);
		वापस -EPERM;
	पूर्ण
	वापस 0;
पूर्ण

अटल __init व्योम pnpacpi_parse_dma_option(काष्ठा pnp_dev *dev,
					    अचिन्हित पूर्णांक option_flags,
					    काष्ठा acpi_resource_dma *p)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर map = 0, flags;

	क्रम (i = 0; i < p->channel_count; i++)
		map |= 1 << p->channels[i];

	flags = dma_flags(dev, p->type, p->bus_master, p->transfer);
	pnp_रेजिस्टर_dma_resource(dev, option_flags, map, flags);
पूर्ण

अटल __init व्योम pnpacpi_parse_irq_option(काष्ठा pnp_dev *dev,
					    अचिन्हित पूर्णांक option_flags,
					    काष्ठा acpi_resource_irq *p)
अणु
	पूर्णांक i;
	pnp_irq_mask_t map;
	अचिन्हित अक्षर flags;

	biपंचांगap_zero(map.bits, PNP_IRQ_NR);
	क्रम (i = 0; i < p->पूर्णांकerrupt_count; i++)
		अगर (p->पूर्णांकerrupts[i])
			__set_bit(p->पूर्णांकerrupts[i], map.bits);

	flags = acpi_dev_irq_flags(p->triggering, p->polarity, p->shareable);
	pnp_रेजिस्टर_irq_resource(dev, option_flags, &map, flags);
पूर्ण

अटल __init व्योम pnpacpi_parse_ext_irq_option(काष्ठा pnp_dev *dev,
					अचिन्हित पूर्णांक option_flags,
					काष्ठा acpi_resource_extended_irq *p)
अणु
	पूर्णांक i;
	pnp_irq_mask_t map;
	अचिन्हित अक्षर flags;

	biपंचांगap_zero(map.bits, PNP_IRQ_NR);
	क्रम (i = 0; i < p->पूर्णांकerrupt_count; i++) अणु
		अगर (p->पूर्णांकerrupts[i]) अणु
			अगर (p->पूर्णांकerrupts[i] < PNP_IRQ_NR)
				__set_bit(p->पूर्णांकerrupts[i], map.bits);
			अन्यथा
				dev_err(&dev->dev,
					"ignoring IRQ %d option (too large for %d entry bitmap)\n",
					p->पूर्णांकerrupts[i], PNP_IRQ_NR);
		पूर्ण
	पूर्ण

	flags = acpi_dev_irq_flags(p->triggering, p->polarity, p->shareable);
	pnp_रेजिस्टर_irq_resource(dev, option_flags, &map, flags);
पूर्ण

अटल __init व्योम pnpacpi_parse_port_option(काष्ठा pnp_dev *dev,
					     अचिन्हित पूर्णांक option_flags,
					     काष्ठा acpi_resource_io *io)
अणु
	अचिन्हित अक्षर flags = 0;

	अगर (io->io_decode == ACPI_DECODE_16)
		flags = IORESOURCE_IO_16BIT_ADDR;
	pnp_रेजिस्टर_port_resource(dev, option_flags, io->minimum, io->maximum,
				   io->alignment, io->address_length, flags);
पूर्ण

अटल __init व्योम pnpacpi_parse_fixed_port_option(काष्ठा pnp_dev *dev,
					अचिन्हित पूर्णांक option_flags,
					काष्ठा acpi_resource_fixed_io *io)
अणु
	pnp_रेजिस्टर_port_resource(dev, option_flags, io->address, io->address,
				   0, io->address_length, IORESOURCE_IO_FIXED);
पूर्ण

अटल __init व्योम pnpacpi_parse_mem24_option(काष्ठा pnp_dev *dev,
					      अचिन्हित पूर्णांक option_flags,
					      काष्ठा acpi_resource_memory24 *p)
अणु
	अचिन्हित अक्षर flags = 0;

	अगर (p->ग_लिखो_protect == ACPI_READ_WRITE_MEMORY)
		flags = IORESOURCE_MEM_WRITEABLE;
	pnp_रेजिस्टर_mem_resource(dev, option_flags, p->minimum, p->maximum,
				  p->alignment, p->address_length, flags);
पूर्ण

अटल __init व्योम pnpacpi_parse_mem32_option(काष्ठा pnp_dev *dev,
					      अचिन्हित पूर्णांक option_flags,
					      काष्ठा acpi_resource_memory32 *p)
अणु
	अचिन्हित अक्षर flags = 0;

	अगर (p->ग_लिखो_protect == ACPI_READ_WRITE_MEMORY)
		flags = IORESOURCE_MEM_WRITEABLE;
	pnp_रेजिस्टर_mem_resource(dev, option_flags, p->minimum, p->maximum,
				  p->alignment, p->address_length, flags);
पूर्ण

अटल __init व्योम pnpacpi_parse_fixed_mem32_option(काष्ठा pnp_dev *dev,
					अचिन्हित पूर्णांक option_flags,
					काष्ठा acpi_resource_fixed_memory32 *p)
अणु
	अचिन्हित अक्षर flags = 0;

	अगर (p->ग_लिखो_protect == ACPI_READ_WRITE_MEMORY)
		flags = IORESOURCE_MEM_WRITEABLE;
	pnp_रेजिस्टर_mem_resource(dev, option_flags, p->address, p->address,
				  0, p->address_length, flags);
पूर्ण

अटल __init व्योम pnpacpi_parse_address_option(काष्ठा pnp_dev *dev,
						अचिन्हित पूर्णांक option_flags,
						काष्ठा acpi_resource *r)
अणु
	काष्ठा acpi_resource_address64 addr, *p = &addr;
	acpi_status status;
	अचिन्हित अक्षर flags = 0;

	status = acpi_resource_to_address64(r, p);
	अगर (ACPI_FAILURE(status)) अणु
		dev_warn(&dev->dev, "can't convert resource type %d\n",
			 r->type);
		वापस;
	पूर्ण

	अगर (p->resource_type == ACPI_MEMORY_RANGE) अणु
		अगर (p->info.mem.ग_लिखो_protect == ACPI_READ_WRITE_MEMORY)
			flags = IORESOURCE_MEM_WRITEABLE;
		pnp_रेजिस्टर_mem_resource(dev, option_flags, p->address.minimum,
					  p->address.minimum, 0, p->address.address_length,
					  flags);
	पूर्ण अन्यथा अगर (p->resource_type == ACPI_IO_RANGE)
		pnp_रेजिस्टर_port_resource(dev, option_flags, p->address.minimum,
					   p->address.minimum, 0, p->address.address_length,
					   IORESOURCE_IO_FIXED);
पूर्ण

अटल __init व्योम pnpacpi_parse_ext_address_option(काष्ठा pnp_dev *dev,
						    अचिन्हित पूर्णांक option_flags,
						    काष्ठा acpi_resource *r)
अणु
	काष्ठा acpi_resource_extended_address64 *p = &r->data.ext_address64;
	अचिन्हित अक्षर flags = 0;

	अगर (p->resource_type == ACPI_MEMORY_RANGE) अणु
		अगर (p->info.mem.ग_लिखो_protect == ACPI_READ_WRITE_MEMORY)
			flags = IORESOURCE_MEM_WRITEABLE;
		pnp_रेजिस्टर_mem_resource(dev, option_flags, p->address.minimum,
					  p->address.minimum, 0, p->address.address_length,
					  flags);
	पूर्ण अन्यथा अगर (p->resource_type == ACPI_IO_RANGE)
		pnp_रेजिस्टर_port_resource(dev, option_flags, p->address.minimum,
					   p->address.minimum, 0, p->address.address_length,
					   IORESOURCE_IO_FIXED);
पूर्ण

काष्ठा acpipnp_parse_option_s अणु
	काष्ठा pnp_dev *dev;
	अचिन्हित पूर्णांक option_flags;
पूर्ण;

अटल __init acpi_status pnpacpi_option_resource(काष्ठा acpi_resource *res,
						  व्योम *data)
अणु
	पूर्णांक priority;
	काष्ठा acpipnp_parse_option_s *parse_data = data;
	काष्ठा pnp_dev *dev = parse_data->dev;
	अचिन्हित पूर्णांक option_flags = parse_data->option_flags;

	चयन (res->type) अणु
	हाल ACPI_RESOURCE_TYPE_IRQ:
		pnpacpi_parse_irq_option(dev, option_flags, &res->data.irq);
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_DMA:
		pnpacpi_parse_dma_option(dev, option_flags, &res->data.dma);
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_START_DEPENDENT:
		चयन (res->data.start_dpf.compatibility_priority) अणु
		हाल ACPI_GOOD_CONFIGURATION:
			priority = PNP_RES_PRIORITY_PREFERRED;
			अवरोध;

		हाल ACPI_ACCEPTABLE_CONFIGURATION:
			priority = PNP_RES_PRIORITY_ACCEPTABLE;
			अवरोध;

		हाल ACPI_SUB_OPTIMAL_CONFIGURATION:
			priority = PNP_RES_PRIORITY_FUNCTIONAL;
			अवरोध;
		शेष:
			priority = PNP_RES_PRIORITY_INVALID;
			अवरोध;
		पूर्ण
		parse_data->option_flags = pnp_new_dependent_set(dev, priority);
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_END_DEPENDENT:
		parse_data->option_flags = 0;
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_IO:
		pnpacpi_parse_port_option(dev, option_flags, &res->data.io);
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_FIXED_IO:
		pnpacpi_parse_fixed_port_option(dev, option_flags,
					        &res->data.fixed_io);
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_VENDOR:
	हाल ACPI_RESOURCE_TYPE_END_TAG:
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_MEMORY24:
		pnpacpi_parse_mem24_option(dev, option_flags,
					   &res->data.memory24);
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_MEMORY32:
		pnpacpi_parse_mem32_option(dev, option_flags,
					   &res->data.memory32);
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_FIXED_MEMORY32:
		pnpacpi_parse_fixed_mem32_option(dev, option_flags,
						 &res->data.fixed_memory32);
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_ADDRESS16:
	हाल ACPI_RESOURCE_TYPE_ADDRESS32:
	हाल ACPI_RESOURCE_TYPE_ADDRESS64:
		pnpacpi_parse_address_option(dev, option_flags, res);
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64:
		pnpacpi_parse_ext_address_option(dev, option_flags, res);
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
		pnpacpi_parse_ext_irq_option(dev, option_flags,
					     &res->data.extended_irq);
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_GENERIC_REGISTER:
		अवरोध;

	शेष:
		dev_warn(&dev->dev, "unknown resource type %d in _PRS\n",
			 res->type);
		वापस AE_ERROR;
	पूर्ण

	वापस AE_OK;
पूर्ण

पूर्णांक __init pnpacpi_parse_resource_option_data(काष्ठा pnp_dev *dev)
अणु
	काष्ठा acpi_device *acpi_dev = dev->data;
	acpi_handle handle = acpi_dev->handle;
	acpi_status status;
	काष्ठा acpipnp_parse_option_s parse_data;

	pnp_dbg(&dev->dev, "parse resource options\n");

	parse_data.dev = dev;
	parse_data.option_flags = 0;

	status = acpi_walk_resources(handle, METHOD_NAME__PRS,
				     pnpacpi_option_resource, &parse_data);

	अगर (ACPI_FAILURE(status)) अणु
		अगर (status != AE_NOT_FOUND)
			dev_err(&dev->dev, "can't evaluate _PRS: %d", status);
		वापस -EPERM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pnpacpi_supported_resource(काष्ठा acpi_resource *res)
अणु
	चयन (res->type) अणु
	हाल ACPI_RESOURCE_TYPE_IRQ:
	हाल ACPI_RESOURCE_TYPE_DMA:
	हाल ACPI_RESOURCE_TYPE_IO:
	हाल ACPI_RESOURCE_TYPE_FIXED_IO:
	हाल ACPI_RESOURCE_TYPE_MEMORY24:
	हाल ACPI_RESOURCE_TYPE_MEMORY32:
	हाल ACPI_RESOURCE_TYPE_FIXED_MEMORY32:
	हाल ACPI_RESOURCE_TYPE_ADDRESS16:
	हाल ACPI_RESOURCE_TYPE_ADDRESS32:
	हाल ACPI_RESOURCE_TYPE_ADDRESS64:
	हाल ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64:
	हाल ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Set resource
 */
अटल acpi_status pnpacpi_count_resources(काष्ठा acpi_resource *res,
					   व्योम *data)
अणु
	पूर्णांक *res_cnt = data;

	अगर (pnpacpi_supported_resource(res))
		(*res_cnt)++;
	वापस AE_OK;
पूर्ण

अटल acpi_status pnpacpi_type_resources(काष्ठा acpi_resource *res, व्योम *data)
अणु
	काष्ठा acpi_resource **resource = data;

	अगर (pnpacpi_supported_resource(res)) अणु
		(*resource)->type = res->type;
		(*resource)->length = माप(काष्ठा acpi_resource);
		अगर (res->type == ACPI_RESOURCE_TYPE_IRQ)
			(*resource)->data.irq.descriptor_length =
					res->data.irq.descriptor_length;
		(*resource)++;
	पूर्ण

	वापस AE_OK;
पूर्ण

पूर्णांक pnpacpi_build_resource_ढाँचा(काष्ठा pnp_dev *dev,
				    काष्ठा acpi_buffer *buffer)
अणु
	काष्ठा acpi_device *acpi_dev = dev->data;
	acpi_handle handle = acpi_dev->handle;
	काष्ठा acpi_resource *resource;
	पूर्णांक res_cnt = 0;
	acpi_status status;

	status = acpi_walk_resources(handle, METHOD_NAME__CRS,
				     pnpacpi_count_resources, &res_cnt);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&dev->dev, "can't evaluate _CRS: %d\n", status);
		वापस -EINVAL;
	पूर्ण
	अगर (!res_cnt)
		वापस -EINVAL;
	buffer->length = माप(काष्ठा acpi_resource) * (res_cnt + 1) + 1;
	buffer->poपूर्णांकer = kzalloc(buffer->length - 1, GFP_KERNEL);
	अगर (!buffer->poपूर्णांकer)
		वापस -ENOMEM;

	resource = (काष्ठा acpi_resource *)buffer->poपूर्णांकer;
	status = acpi_walk_resources(handle, METHOD_NAME__CRS,
				     pnpacpi_type_resources, &resource);
	अगर (ACPI_FAILURE(status)) अणु
		kमुक्त(buffer->poपूर्णांकer);
		dev_err(&dev->dev, "can't evaluate _CRS: %d\n", status);
		वापस -EINVAL;
	पूर्ण
	/* resource will poपूर्णांकer the end resource now */
	resource->type = ACPI_RESOURCE_TYPE_END_TAG;
	resource->length = माप(काष्ठा acpi_resource);

	वापस 0;
पूर्ण

अटल व्योम pnpacpi_encode_irq(काष्ठा pnp_dev *dev,
			       काष्ठा acpi_resource *resource,
			       काष्ठा resource *p)
अणु
	काष्ठा acpi_resource_irq *irq = &resource->data.irq;
	u8 triggering, polarity, shareable;

	अगर (!pnp_resource_enabled(p)) अणु
		irq->पूर्णांकerrupt_count = 0;
		pnp_dbg(&dev->dev, "  encode irq (%s)\n",
			p ? "disabled" : "missing");
		वापस;
	पूर्ण

	decode_irq_flags(dev, p->flags, &triggering, &polarity, &shareable);
	irq->triggering = triggering;
	irq->polarity = polarity;
	irq->shareable = shareable;
	irq->पूर्णांकerrupt_count = 1;
	irq->पूर्णांकerrupts[0] = p->start;

	pnp_dbg(&dev->dev, "  encode irq %d %s %s %s (%d-byte descriptor)\n",
		(पूर्णांक) p->start,
		triggering == ACPI_LEVEL_SENSITIVE ? "level" : "edge",
		polarity == ACPI_ACTIVE_LOW ? "low" : "high",
		irq->shareable == ACPI_SHARED ? "shared" : "exclusive",
		irq->descriptor_length);
पूर्ण

अटल व्योम pnpacpi_encode_ext_irq(काष्ठा pnp_dev *dev,
				   काष्ठा acpi_resource *resource,
				   काष्ठा resource *p)
अणु
	काष्ठा acpi_resource_extended_irq *extended_irq = &resource->data.extended_irq;
	u8 triggering, polarity, shareable;

	अगर (!pnp_resource_enabled(p)) अणु
		extended_irq->पूर्णांकerrupt_count = 0;
		pnp_dbg(&dev->dev, "  encode extended irq (%s)\n",
			p ? "disabled" : "missing");
		वापस;
	पूर्ण

	decode_irq_flags(dev, p->flags, &triggering, &polarity, &shareable);
	extended_irq->producer_consumer = ACPI_CONSUMER;
	extended_irq->triggering = triggering;
	extended_irq->polarity = polarity;
	extended_irq->shareable = shareable;
	extended_irq->पूर्णांकerrupt_count = 1;
	extended_irq->पूर्णांकerrupts[0] = p->start;

	pnp_dbg(&dev->dev, "  encode irq %d %s %s %s\n", (पूर्णांक) p->start,
		triggering == ACPI_LEVEL_SENSITIVE ? "level" : "edge",
		polarity == ACPI_ACTIVE_LOW ? "low" : "high",
		extended_irq->shareable == ACPI_SHARED ? "shared" : "exclusive");
पूर्ण

अटल व्योम pnpacpi_encode_dma(काष्ठा pnp_dev *dev,
			       काष्ठा acpi_resource *resource,
			       काष्ठा resource *p)
अणु
	काष्ठा acpi_resource_dma *dma = &resource->data.dma;

	अगर (!pnp_resource_enabled(p)) अणु
		dma->channel_count = 0;
		pnp_dbg(&dev->dev, "  encode dma (%s)\n",
			p ? "disabled" : "missing");
		वापस;
	पूर्ण

	/* Note: pnp_assign_dma will copy pnp_dma->flags पूर्णांकo p->flags */
	चयन (p->flags & IORESOURCE_DMA_SPEED_MASK) अणु
	हाल IORESOURCE_DMA_TYPEA:
		dma->type = ACPI_TYPE_A;
		अवरोध;
	हाल IORESOURCE_DMA_TYPEB:
		dma->type = ACPI_TYPE_B;
		अवरोध;
	हाल IORESOURCE_DMA_TYPEF:
		dma->type = ACPI_TYPE_F;
		अवरोध;
	शेष:
		dma->type = ACPI_COMPATIBILITY;
	पूर्ण

	चयन (p->flags & IORESOURCE_DMA_TYPE_MASK) अणु
	हाल IORESOURCE_DMA_8BIT:
		dma->transfer = ACPI_TRANSFER_8;
		अवरोध;
	हाल IORESOURCE_DMA_8AND16BIT:
		dma->transfer = ACPI_TRANSFER_8_16;
		अवरोध;
	शेष:
		dma->transfer = ACPI_TRANSFER_16;
	पूर्ण

	dma->bus_master = !!(p->flags & IORESOURCE_DMA_MASTER);
	dma->channel_count = 1;
	dma->channels[0] = p->start;

	pnp_dbg(&dev->dev, "  encode dma %d "
		"type %#x transfer %#x master %d\n",
		(पूर्णांक) p->start, dma->type, dma->transfer, dma->bus_master);
पूर्ण

अटल व्योम pnpacpi_encode_io(काष्ठा pnp_dev *dev,
			      काष्ठा acpi_resource *resource,
			      काष्ठा resource *p)
अणु
	काष्ठा acpi_resource_io *io = &resource->data.io;

	अगर (pnp_resource_enabled(p)) अणु
		/* Note: pnp_assign_port copies pnp_port->flags पूर्णांकo p->flags */
		io->io_decode = (p->flags & IORESOURCE_IO_16BIT_ADDR) ?
		    ACPI_DECODE_16 : ACPI_DECODE_10;
		io->minimum = p->start;
		io->maximum = p->end;
		io->alignment = 0;	/* Correct? */
		io->address_length = resource_size(p);
	पूर्ण अन्यथा अणु
		io->minimum = 0;
		io->address_length = 0;
	पूर्ण

	pnp_dbg(&dev->dev, "  encode io %#x-%#x decode %#x\n", io->minimum,
		io->minimum + io->address_length - 1, io->io_decode);
पूर्ण

अटल व्योम pnpacpi_encode_fixed_io(काष्ठा pnp_dev *dev,
				    काष्ठा acpi_resource *resource,
				    काष्ठा resource *p)
अणु
	काष्ठा acpi_resource_fixed_io *fixed_io = &resource->data.fixed_io;

	अगर (pnp_resource_enabled(p)) अणु
		fixed_io->address = p->start;
		fixed_io->address_length = resource_size(p);
	पूर्ण अन्यथा अणु
		fixed_io->address = 0;
		fixed_io->address_length = 0;
	पूर्ण

	pnp_dbg(&dev->dev, "  encode fixed_io %#x-%#x\n", fixed_io->address,
		fixed_io->address + fixed_io->address_length - 1);
पूर्ण

अटल व्योम pnpacpi_encode_mem24(काष्ठा pnp_dev *dev,
				 काष्ठा acpi_resource *resource,
				 काष्ठा resource *p)
अणु
	काष्ठा acpi_resource_memory24 *memory24 = &resource->data.memory24;

	अगर (pnp_resource_enabled(p)) अणु
		/* Note: pnp_assign_mem copies pnp_mem->flags पूर्णांकo p->flags */
		memory24->ग_लिखो_protect = p->flags & IORESOURCE_MEM_WRITEABLE ?
		    ACPI_READ_WRITE_MEMORY : ACPI_READ_ONLY_MEMORY;
		memory24->minimum = p->start;
		memory24->maximum = p->end;
		memory24->alignment = 0;
		memory24->address_length = resource_size(p);
	पूर्ण अन्यथा अणु
		memory24->minimum = 0;
		memory24->address_length = 0;
	पूर्ण

	pnp_dbg(&dev->dev, "  encode mem24 %#x-%#x write_protect %#x\n",
		memory24->minimum,
		memory24->minimum + memory24->address_length - 1,
		memory24->ग_लिखो_protect);
पूर्ण

अटल व्योम pnpacpi_encode_mem32(काष्ठा pnp_dev *dev,
				 काष्ठा acpi_resource *resource,
				 काष्ठा resource *p)
अणु
	काष्ठा acpi_resource_memory32 *memory32 = &resource->data.memory32;

	अगर (pnp_resource_enabled(p)) अणु
		memory32->ग_लिखो_protect = p->flags & IORESOURCE_MEM_WRITEABLE ?
		    ACPI_READ_WRITE_MEMORY : ACPI_READ_ONLY_MEMORY;
		memory32->minimum = p->start;
		memory32->maximum = p->end;
		memory32->alignment = 0;
		memory32->address_length = resource_size(p);
	पूर्ण अन्यथा अणु
		memory32->minimum = 0;
		memory32->alignment = 0;
	पूर्ण

	pnp_dbg(&dev->dev, "  encode mem32 %#x-%#x write_protect %#x\n",
		memory32->minimum,
		memory32->minimum + memory32->address_length - 1,
		memory32->ग_लिखो_protect);
पूर्ण

अटल व्योम pnpacpi_encode_fixed_mem32(काष्ठा pnp_dev *dev,
				       काष्ठा acpi_resource *resource,
				       काष्ठा resource *p)
अणु
	काष्ठा acpi_resource_fixed_memory32 *fixed_memory32 = &resource->data.fixed_memory32;

	अगर (pnp_resource_enabled(p)) अणु
		fixed_memory32->ग_लिखो_protect =
		    p->flags & IORESOURCE_MEM_WRITEABLE ?
		    ACPI_READ_WRITE_MEMORY : ACPI_READ_ONLY_MEMORY;
		fixed_memory32->address = p->start;
		fixed_memory32->address_length = resource_size(p);
	पूर्ण अन्यथा अणु
		fixed_memory32->address = 0;
		fixed_memory32->address_length = 0;
	पूर्ण

	pnp_dbg(&dev->dev, "  encode fixed_mem32 %#x-%#x write_protect %#x\n",
		fixed_memory32->address,
		fixed_memory32->address + fixed_memory32->address_length - 1,
		fixed_memory32->ग_लिखो_protect);
पूर्ण

पूर्णांक pnpacpi_encode_resources(काष्ठा pnp_dev *dev, काष्ठा acpi_buffer *buffer)
अणु
	पूर्णांक i = 0;
	/* pnpacpi_build_resource_ढाँचा allocates extra mem */
	पूर्णांक res_cnt = (buffer->length - 1) / माप(काष्ठा acpi_resource) - 1;
	काष्ठा acpi_resource *resource = buffer->poपूर्णांकer;
	अचिन्हित पूर्णांक port = 0, irq = 0, dma = 0, mem = 0;

	pnp_dbg(&dev->dev, "encode %d resources\n", res_cnt);
	जबतक (i < res_cnt) अणु
		चयन (resource->type) अणु
		हाल ACPI_RESOURCE_TYPE_IRQ:
			pnpacpi_encode_irq(dev, resource,
			       pnp_get_resource(dev, IORESOURCE_IRQ, irq));
			irq++;
			अवरोध;

		हाल ACPI_RESOURCE_TYPE_DMA:
			pnpacpi_encode_dma(dev, resource,
				pnp_get_resource(dev, IORESOURCE_DMA, dma));
			dma++;
			अवरोध;
		हाल ACPI_RESOURCE_TYPE_IO:
			pnpacpi_encode_io(dev, resource,
				pnp_get_resource(dev, IORESOURCE_IO, port));
			port++;
			अवरोध;
		हाल ACPI_RESOURCE_TYPE_FIXED_IO:
			pnpacpi_encode_fixed_io(dev, resource,
				pnp_get_resource(dev, IORESOURCE_IO, port));
			port++;
			अवरोध;
		हाल ACPI_RESOURCE_TYPE_MEMORY24:
			pnpacpi_encode_mem24(dev, resource,
				pnp_get_resource(dev, IORESOURCE_MEM, mem));
			mem++;
			अवरोध;
		हाल ACPI_RESOURCE_TYPE_MEMORY32:
			pnpacpi_encode_mem32(dev, resource,
				pnp_get_resource(dev, IORESOURCE_MEM, mem));
			mem++;
			अवरोध;
		हाल ACPI_RESOURCE_TYPE_FIXED_MEMORY32:
			pnpacpi_encode_fixed_mem32(dev, resource,
				pnp_get_resource(dev, IORESOURCE_MEM, mem));
			mem++;
			अवरोध;
		हाल ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
			pnpacpi_encode_ext_irq(dev, resource,
				pnp_get_resource(dev, IORESOURCE_IRQ, irq));
			irq++;
			अवरोध;
		हाल ACPI_RESOURCE_TYPE_START_DEPENDENT:
		हाल ACPI_RESOURCE_TYPE_END_DEPENDENT:
		हाल ACPI_RESOURCE_TYPE_VENDOR:
		हाल ACPI_RESOURCE_TYPE_END_TAG:
		हाल ACPI_RESOURCE_TYPE_ADDRESS16:
		हाल ACPI_RESOURCE_TYPE_ADDRESS32:
		हाल ACPI_RESOURCE_TYPE_ADDRESS64:
		हाल ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64:
		हाल ACPI_RESOURCE_TYPE_GENERIC_REGISTER:
		शेष:	/* other type */
			dev_warn(&dev->dev,
				 "can't encode unknown resource type %d\n",
				 resource->type);
			वापस -EINVAL;
		पूर्ण
		resource++;
		i++;
	पूर्ण
	वापस 0;
पूर्ण
