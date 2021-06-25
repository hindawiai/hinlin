<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * support.c - standard functions क्रम the use of pnp protocol drivers
 *
 * Copyright 2003 Adam Belay <ambx1@neo.rr.com>
 * Copyright (C) 2008 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/pnp.h>
#समावेश "base.h"

/**
 * pnp_is_active - Determines अगर a device is active based on its current
 *	resources
 * @dev: poपूर्णांकer to the desired PnP device
 */
पूर्णांक pnp_is_active(काष्ठा pnp_dev *dev)
अणु
	/*
	 * I करोn't think this is very reliable because pnp_disable_dev()
	 * only clears out स्वतः-asचिन्हित resources.
	 */
	अगर (!pnp_port_start(dev, 0) && pnp_port_len(dev, 0) <= 1 &&
	    !pnp_mem_start(dev, 0) && pnp_mem_len(dev, 0) <= 1 &&
	    pnp_irq(dev, 0) == -1 && pnp_dma(dev, 0) == -1)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

EXPORT_SYMBOL(pnp_is_active);

/*
 * Functionally similar to acpi_ex_eisa_id_to_string(), but that's
 * buried in the ACPI CA, and we can't depend on it being present.
 */
व्योम pnp_eisa_id_to_string(u32 id, अक्षर *str)
अणु
	id = be32_to_cpu(id);

	/*
	 * According to the specs, the first three अक्षरacters are five-bit
	 * compressed ASCII, and the left-over high order bit should be zero.
	 * However, the Linux ISAPNP code historically used six bits क्रम the
	 * first अक्षरacter, and there seem to be IDs that depend on that,
	 * e.g., "nEC8241" in the Linux 8250_pnp serial driver and the
	 * FreeBSD sys/pc98/cbus/sio_cbus.c driver.
	 */
	str[0] = 'A' + ((id >> 26) & 0x3f) - 1;
	str[1] = 'A' + ((id >> 21) & 0x1f) - 1;
	str[2] = 'A' + ((id >> 16) & 0x1f) - 1;
	str[3] = hex_asc_hi(id >> 8);
	str[4] = hex_asc_lo(id >> 8);
	str[5] = hex_asc_hi(id);
	str[6] = hex_asc_lo(id);
	str[7] = '\0';
पूर्ण

अक्षर *pnp_resource_type_name(काष्ठा resource *res)
अणु
	चयन (pnp_resource_type(res)) अणु
	हाल IORESOURCE_IO:
		वापस "io";
	हाल IORESOURCE_MEM:
		वापस "mem";
	हाल IORESOURCE_IRQ:
		वापस "irq";
	हाल IORESOURCE_DMA:
		वापस "dma";
	हाल IORESOURCE_BUS:
		वापस "bus";
	पूर्ण
	वापस "unknown";
पूर्ण

व्योम dbg_pnp_show_resources(काष्ठा pnp_dev *dev, अक्षर *desc)
अणु
	काष्ठा pnp_resource *pnp_res;

	अगर (list_empty(&dev->resources))
		pnp_dbg(&dev->dev, "%s: no current resources\n", desc);
	अन्यथा अणु
		pnp_dbg(&dev->dev, "%s: current resources:\n", desc);
		list_क्रम_each_entry(pnp_res, &dev->resources, list)
			pnp_dbg(&dev->dev, "%pr\n", &pnp_res->res);
	पूर्ण
पूर्ण

अक्षर *pnp_option_priority_name(काष्ठा pnp_option *option)
अणु
	चयन (pnp_option_priority(option)) अणु
	हाल PNP_RES_PRIORITY_PREFERRED:
		वापस "preferred";
	हाल PNP_RES_PRIORITY_ACCEPTABLE:
		वापस "acceptable";
	हाल PNP_RES_PRIORITY_FUNCTIONAL:
		वापस "functional";
	पूर्ण
	वापस "invalid";
पूर्ण

व्योम dbg_pnp_show_option(काष्ठा pnp_dev *dev, काष्ठा pnp_option *option)
अणु
	अक्षर buf[128];
	पूर्णांक len = 0, i;
	काष्ठा pnp_port *port;
	काष्ठा pnp_mem *mem;
	काष्ठा pnp_irq *irq;
	काष्ठा pnp_dma *dma;

	अगर (pnp_option_is_dependent(option))
		len += scnम_लिखो(buf + len, माप(buf) - len,
				 "  dependent set %d (%s) ",
				 pnp_option_set(option),
				 pnp_option_priority_name(option));
	अन्यथा
		len += scnम_लिखो(buf + len, माप(buf) - len,
				 "  independent ");

	चयन (option->type) अणु
	हाल IORESOURCE_IO:
		port = &option->u.port;
		len += scnम_लिखो(buf + len, माप(buf) - len, "io  min %#llx "
				 "max %#llx align %lld size %lld flags %#x",
				 (अचिन्हित दीर्घ दीर्घ) port->min,
				 (अचिन्हित दीर्घ दीर्घ) port->max,
				 (अचिन्हित दीर्घ दीर्घ) port->align,
				 (अचिन्हित दीर्घ दीर्घ) port->size, port->flags);
		अवरोध;
	हाल IORESOURCE_MEM:
		mem = &option->u.mem;
		len += scnम_लिखो(buf + len, माप(buf) - len, "mem min %#llx "
				 "max %#llx align %lld size %lld flags %#x",
				 (अचिन्हित दीर्घ दीर्घ) mem->min,
				 (अचिन्हित दीर्घ दीर्घ) mem->max,
				 (अचिन्हित दीर्घ दीर्घ) mem->align,
				 (अचिन्हित दीर्घ दीर्घ) mem->size, mem->flags);
		अवरोध;
	हाल IORESOURCE_IRQ:
		irq = &option->u.irq;
		len += scnम_लिखो(buf + len, माप(buf) - len, "irq");
		अगर (biपंचांगap_empty(irq->map.bits, PNP_IRQ_NR))
			len += scnम_लिखो(buf + len, माप(buf) - len,
					 " <none>");
		अन्यथा अणु
			क्रम (i = 0; i < PNP_IRQ_NR; i++)
				अगर (test_bit(i, irq->map.bits))
					len += scnम_लिखो(buf + len,
							 माप(buf) - len,
							 " %d", i);
		पूर्ण
		len += scnम_लिखो(buf + len, माप(buf) - len, " flags %#x",
				 irq->flags);
		अगर (irq->flags & IORESOURCE_IRQ_OPTIONAL)
			len += scnम_लिखो(buf + len, माप(buf) - len,
					 " (optional)");
		अवरोध;
	हाल IORESOURCE_DMA:
		dma = &option->u.dma;
		len += scnम_लिखो(buf + len, माप(buf) - len, "dma");
		अगर (!dma->map)
			len += scnम_लिखो(buf + len, माप(buf) - len,
					 " <none>");
		अन्यथा अणु
			क्रम (i = 0; i < 8; i++)
				अगर (dma->map & (1 << i))
					len += scnम_लिखो(buf + len,
							 माप(buf) - len,
							 " %d", i);
		पूर्ण
		len += scnम_लिखो(buf + len, माप(buf) - len, " (bitmask %#x) "
				 "flags %#x", dma->map, dma->flags);
		अवरोध;
	पूर्ण
	pnp_dbg(&dev->dev, "%s\n", buf);
पूर्ण
