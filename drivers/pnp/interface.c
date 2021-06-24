<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * पूर्णांकerface.c - contains everything related to the user पूर्णांकerface
 *
 * Some code, especially possible resource dumping is based on isapnp_proc.c (c) Jaroslav Kysela <perex@perex.cz>
 * Copyright 2002 Adam Belay <ambx1@neo.rr.com>
 * Copyright (C) 2008 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

#समावेश <linux/pnp.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>

#समावेश <linux/uaccess.h>

#समावेश "base.h"

काष्ठा pnp_info_buffer अणु
	अक्षर *buffer;		/* poपूर्णांकer to begin of buffer */
	अक्षर *curr;		/* current position in buffer */
	अचिन्हित दीर्घ size;	/* current size */
	अचिन्हित दीर्घ len;	/* total length of buffer */
	पूर्णांक stop;		/* stop flag */
	पूर्णांक error;		/* error code */
पूर्ण;

प्रकार काष्ठा pnp_info_buffer pnp_info_buffer_t;

__म_लिखो(2, 3)
अटल पूर्णांक pnp_म_लिखो(pnp_info_buffer_t * buffer, अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक res;

	अगर (buffer->stop || buffer->error)
		वापस 0;
	बहु_शुरू(args, fmt);
	res = vsnम_लिखो(buffer->curr, buffer->len - buffer->size, fmt, args);
	बहु_पूर्ण(args);
	अगर (buffer->size + res >= buffer->len) अणु
		buffer->stop = 1;
		वापस 0;
	पूर्ण
	buffer->curr += res;
	buffer->size += res;
	वापस res;
पूर्ण

अटल व्योम pnp_prपूर्णांक_port(pnp_info_buffer_t * buffer, अक्षर *space,
			   काष्ठा pnp_port *port)
अणु
	pnp_म_लिखो(buffer, "%sport %#llx-%#llx, align %#llx, size %#llx, "
		   "%i-bit address decoding\n", space,
		   (अचिन्हित दीर्घ दीर्घ) port->min,
		   (अचिन्हित दीर्घ दीर्घ) port->max,
		   port->align ? ((अचिन्हित दीर्घ दीर्घ) port->align - 1) : 0,
		   (अचिन्हित दीर्घ दीर्घ) port->size,
		   port->flags & IORESOURCE_IO_16BIT_ADDR ? 16 : 10);
पूर्ण

अटल व्योम pnp_prपूर्णांक_irq(pnp_info_buffer_t * buffer, अक्षर *space,
			  काष्ठा pnp_irq *irq)
अणु
	पूर्णांक first = 1, i;

	pnp_म_लिखो(buffer, "%sirq ", space);
	क्रम (i = 0; i < PNP_IRQ_NR; i++)
		अगर (test_bit(i, irq->map.bits)) अणु
			अगर (!first) अणु
				pnp_म_लिखो(buffer, ",");
			पूर्ण अन्यथा अणु
				first = 0;
			पूर्ण
			अगर (i == 2 || i == 9)
				pnp_म_लिखो(buffer, "2/9");
			अन्यथा
				pnp_म_लिखो(buffer, "%i", i);
		पूर्ण
	अगर (biपंचांगap_empty(irq->map.bits, PNP_IRQ_NR))
		pnp_म_लिखो(buffer, "<none>");
	अगर (irq->flags & IORESOURCE_IRQ_HIGHEDGE)
		pnp_म_लिखो(buffer, " High-Edge");
	अगर (irq->flags & IORESOURCE_IRQ_LOWEDGE)
		pnp_म_लिखो(buffer, " Low-Edge");
	अगर (irq->flags & IORESOURCE_IRQ_HIGHLEVEL)
		pnp_म_लिखो(buffer, " High-Level");
	अगर (irq->flags & IORESOURCE_IRQ_LOWLEVEL)
		pnp_म_लिखो(buffer, " Low-Level");
	अगर (irq->flags & IORESOURCE_IRQ_OPTIONAL)
		pnp_म_लिखो(buffer, " (optional)");
	pnp_म_लिखो(buffer, "\n");
पूर्ण

अटल व्योम pnp_prपूर्णांक_dma(pnp_info_buffer_t * buffer, अक्षर *space,
			  काष्ठा pnp_dma *dma)
अणु
	पूर्णांक first = 1, i;
	अक्षर *s;

	pnp_म_लिखो(buffer, "%sdma ", space);
	क्रम (i = 0; i < 8; i++)
		अगर (dma->map & (1 << i)) अणु
			अगर (!first) अणु
				pnp_म_लिखो(buffer, ",");
			पूर्ण अन्यथा अणु
				first = 0;
			पूर्ण
			pnp_म_लिखो(buffer, "%i", i);
		पूर्ण
	अगर (!dma->map)
		pnp_म_लिखो(buffer, "<none>");
	चयन (dma->flags & IORESOURCE_DMA_TYPE_MASK) अणु
	हाल IORESOURCE_DMA_8BIT:
		s = "8-bit";
		अवरोध;
	हाल IORESOURCE_DMA_8AND16BIT:
		s = "8-bit&16-bit";
		अवरोध;
	शेष:
		s = "16-bit";
	पूर्ण
	pnp_म_लिखो(buffer, " %s", s);
	अगर (dma->flags & IORESOURCE_DMA_MASTER)
		pnp_म_लिखो(buffer, " master");
	अगर (dma->flags & IORESOURCE_DMA_BYTE)
		pnp_म_लिखो(buffer, " byte-count");
	अगर (dma->flags & IORESOURCE_DMA_WORD)
		pnp_म_लिखो(buffer, " word-count");
	चयन (dma->flags & IORESOURCE_DMA_SPEED_MASK) अणु
	हाल IORESOURCE_DMA_TYPEA:
		s = "type-A";
		अवरोध;
	हाल IORESOURCE_DMA_TYPEB:
		s = "type-B";
		अवरोध;
	हाल IORESOURCE_DMA_TYPEF:
		s = "type-F";
		अवरोध;
	शेष:
		s = "compatible";
		अवरोध;
	पूर्ण
	pnp_म_लिखो(buffer, " %s\n", s);
पूर्ण

अटल व्योम pnp_prपूर्णांक_mem(pnp_info_buffer_t * buffer, अक्षर *space,
			  काष्ठा pnp_mem *mem)
अणु
	अक्षर *s;

	pnp_म_लिखो(buffer, "%sMemory %#llx-%#llx, align %#llx, size %#llx",
		   space, (अचिन्हित दीर्घ दीर्घ) mem->min,
		   (अचिन्हित दीर्घ दीर्घ) mem->max,
		   (अचिन्हित दीर्घ दीर्घ) mem->align,
		   (अचिन्हित दीर्घ दीर्घ) mem->size);
	अगर (mem->flags & IORESOURCE_MEM_WRITEABLE)
		pnp_म_लिखो(buffer, ", writeable");
	अगर (mem->flags & IORESOURCE_MEM_CACHEABLE)
		pnp_म_लिखो(buffer, ", cacheable");
	अगर (mem->flags & IORESOURCE_MEM_RANGELENGTH)
		pnp_म_लिखो(buffer, ", range-length");
	अगर (mem->flags & IORESOURCE_MEM_SHADOWABLE)
		pnp_म_लिखो(buffer, ", shadowable");
	अगर (mem->flags & IORESOURCE_MEM_EXPANSIONROM)
		pnp_म_लिखो(buffer, ", expansion ROM");
	चयन (mem->flags & IORESOURCE_MEM_TYPE_MASK) अणु
	हाल IORESOURCE_MEM_8BIT:
		s = "8-bit";
		अवरोध;
	हाल IORESOURCE_MEM_8AND16BIT:
		s = "8-bit&16-bit";
		अवरोध;
	हाल IORESOURCE_MEM_32BIT:
		s = "32-bit";
		अवरोध;
	शेष:
		s = "16-bit";
	पूर्ण
	pnp_म_लिखो(buffer, ", %s\n", s);
पूर्ण

अटल व्योम pnp_prपूर्णांक_option(pnp_info_buffer_t * buffer, अक्षर *space,
			     काष्ठा pnp_option *option)
अणु
	चयन (option->type) अणु
	हाल IORESOURCE_IO:
		pnp_prपूर्णांक_port(buffer, space, &option->u.port);
		अवरोध;
	हाल IORESOURCE_MEM:
		pnp_prपूर्णांक_mem(buffer, space, &option->u.mem);
		अवरोध;
	हाल IORESOURCE_IRQ:
		pnp_prपूर्णांक_irq(buffer, space, &option->u.irq);
		अवरोध;
	हाल IORESOURCE_DMA:
		pnp_prपूर्णांक_dma(buffer, space, &option->u.dma);
		अवरोध;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार options_show(काष्ठा device *dmdev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा pnp_dev *dev = to_pnp_dev(dmdev);
	pnp_info_buffer_t *buffer;
	काष्ठा pnp_option *option;
	पूर्णांक ret, dep = 0, set = 0;
	अक्षर *indent;

	buffer = pnp_alloc(माप(pnp_info_buffer_t));
	अगर (!buffer)
		वापस -ENOMEM;

	buffer->len = PAGE_SIZE;
	buffer->buffer = buf;
	buffer->curr = buffer->buffer;

	list_क्रम_each_entry(option, &dev->options, list) अणु
		अगर (pnp_option_is_dependent(option)) अणु
			indent = "  ";
			अगर (!dep || pnp_option_set(option) != set) अणु
				set = pnp_option_set(option);
				dep = 1;
				pnp_म_लिखो(buffer, "Dependent: %02i - "
					   "Priority %s\n", set,
					   pnp_option_priority_name(option));
			पूर्ण
		पूर्ण अन्यथा अणु
			dep = 0;
			indent = "";
		पूर्ण
		pnp_prपूर्णांक_option(buffer, indent, option);
	पूर्ण

	ret = (buffer->curr - buf);
	kमुक्त(buffer);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(options);

अटल sमाप_प्रकार resources_show(काष्ठा device *dmdev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pnp_dev *dev = to_pnp_dev(dmdev);
	pnp_info_buffer_t *buffer;
	काष्ठा pnp_resource *pnp_res;
	काष्ठा resource *res;
	पूर्णांक ret;

	अगर (!dev)
		वापस -EINVAL;

	buffer = pnp_alloc(माप(pnp_info_buffer_t));
	अगर (!buffer)
		वापस -ENOMEM;

	buffer->len = PAGE_SIZE;
	buffer->buffer = buf;
	buffer->curr = buffer->buffer;

	pnp_म_लिखो(buffer, "state = %s\n", dev->active ? "active" : "disabled");

	list_क्रम_each_entry(pnp_res, &dev->resources, list) अणु
		res = &pnp_res->res;

		pnp_म_लिखो(buffer, pnp_resource_type_name(res));

		अगर (res->flags & IORESOURCE_DISABLED) अणु
			pnp_म_लिखो(buffer, " disabled\n");
			जारी;
		पूर्ण

		चयन (pnp_resource_type(res)) अणु
		हाल IORESOURCE_IO:
		हाल IORESOURCE_MEM:
		हाल IORESOURCE_BUS:
			pnp_म_लिखो(buffer, " %#llx-%#llx%s\n",
				   (अचिन्हित दीर्घ दीर्घ) res->start,
				   (अचिन्हित दीर्घ दीर्घ) res->end,
				   res->flags & IORESOURCE_WINDOW ?
					" window" : "");
			अवरोध;
		हाल IORESOURCE_IRQ:
		हाल IORESOURCE_DMA:
			pnp_म_लिखो(buffer, " %lld\n",
				   (अचिन्हित दीर्घ दीर्घ) res->start);
			अवरोध;
		पूर्ण
	पूर्ण

	ret = (buffer->curr - buf);
	kमुक्त(buffer);
	वापस ret;
पूर्ण

अटल अक्षर *pnp_get_resource_value(अक्षर *buf,
				    अचिन्हित दीर्घ type,
				    resource_माप_प्रकार *start,
				    resource_माप_प्रकार *end,
				    अचिन्हित दीर्घ *flags)
अणु
	अगर (start)
		*start = 0;
	अगर (end)
		*end = 0;
	अगर (flags)
		*flags = 0;

	/* TBD: allow क्रम disabled resources */

	buf = skip_spaces(buf);
	अगर (start) अणु
		*start = simple_म_से_अदीर्घl(buf, &buf, 0);
		अगर (end) अणु
			buf = skip_spaces(buf);
			अगर (*buf == '-') अणु
				buf = skip_spaces(buf + 1);
				*end = simple_म_से_अदीर्घl(buf, &buf, 0);
			पूर्ण अन्यथा
				*end = *start;
		पूर्ण
	पूर्ण

	/* TBD: allow क्रम additional flags, e.g., IORESOURCE_WINDOW */

	वापस buf;
पूर्ण

अटल sमाप_प्रकार resources_store(काष्ठा device *dmdev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *ubuf,
			       माप_प्रकार count)
अणु
	काष्ठा pnp_dev *dev = to_pnp_dev(dmdev);
	अक्षर *buf = (व्योम *)ubuf;
	पूर्णांक retval = 0;

	अगर (dev->status & PNP_ATTACHED) अणु
		retval = -EBUSY;
		dev_info(&dev->dev, "in use; can't configure\n");
		जाओ करोne;
	पूर्ण

	buf = skip_spaces(buf);
	अगर (!strnहालcmp(buf, "disable", 7)) अणु
		retval = pnp_disable_dev(dev);
		जाओ करोne;
	पूर्ण
	अगर (!strnहालcmp(buf, "activate", 8)) अणु
		retval = pnp_activate_dev(dev);
		जाओ करोne;
	पूर्ण
	अगर (!strnहालcmp(buf, "fill", 4)) अणु
		अगर (dev->active)
			जाओ करोne;
		retval = pnp_स्वतः_config_dev(dev);
		जाओ करोne;
	पूर्ण
	अगर (!strnहालcmp(buf, "auto", 4)) अणु
		अगर (dev->active)
			जाओ करोne;
		pnp_init_resources(dev);
		retval = pnp_स्वतः_config_dev(dev);
		जाओ करोne;
	पूर्ण
	अगर (!strnहालcmp(buf, "clear", 5)) अणु
		अगर (dev->active)
			जाओ करोne;
		pnp_init_resources(dev);
		जाओ करोne;
	पूर्ण
	अगर (!strnहालcmp(buf, "get", 3)) अणु
		mutex_lock(&pnp_res_mutex);
		अगर (pnp_can_पढ़ो(dev))
			dev->protocol->get(dev);
		mutex_unlock(&pnp_res_mutex);
		जाओ करोne;
	पूर्ण
	अगर (!strnहालcmp(buf, "set", 3)) अणु
		resource_माप_प्रकार start;
		resource_माप_प्रकार end;
		अचिन्हित दीर्घ flags;

		अगर (dev->active)
			जाओ करोne;
		buf += 3;
		pnp_init_resources(dev);
		mutex_lock(&pnp_res_mutex);
		जबतक (1) अणु
			buf = skip_spaces(buf);
			अगर (!strnहालcmp(buf, "io", 2)) अणु
				buf = pnp_get_resource_value(buf + 2,
							     IORESOURCE_IO,
							     &start, &end,
							     &flags);
				pnp_add_io_resource(dev, start, end, flags);
			पूर्ण अन्यथा अगर (!strnहालcmp(buf, "mem", 3)) अणु
				buf = pnp_get_resource_value(buf + 3,
							     IORESOURCE_MEM,
							     &start, &end,
							     &flags);
				pnp_add_mem_resource(dev, start, end, flags);
			पूर्ण अन्यथा अगर (!strnहालcmp(buf, "irq", 3)) अणु
				buf = pnp_get_resource_value(buf + 3,
							     IORESOURCE_IRQ,
							     &start, शून्य,
							     &flags);
				pnp_add_irq_resource(dev, start, flags);
			पूर्ण अन्यथा अगर (!strnहालcmp(buf, "dma", 3)) अणु
				buf = pnp_get_resource_value(buf + 3,
							     IORESOURCE_DMA,
							     &start, शून्य,
							     &flags);
				pnp_add_dma_resource(dev, start, flags);
			पूर्ण अन्यथा अगर (!strnहालcmp(buf, "bus", 3)) अणु
				buf = pnp_get_resource_value(buf + 3,
							     IORESOURCE_BUS,
							     &start, &end,
							     शून्य);
				pnp_add_bus_resource(dev, start, end);
			पूर्ण अन्यथा
				अवरोध;
		पूर्ण
		mutex_unlock(&pnp_res_mutex);
		जाओ करोne;
	पूर्ण

करोne:
	अगर (retval < 0)
		वापस retval;
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(resources);

अटल sमाप_प्रकार id_show(काष्ठा device *dmdev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	अक्षर *str = buf;
	काष्ठा pnp_dev *dev = to_pnp_dev(dmdev);
	काष्ठा pnp_id *pos = dev->id;

	जबतक (pos) अणु
		str += प्र_लिखो(str, "%s\n", pos->id);
		pos = pos->next;
	पूर्ण
	वापस (str - buf);
पूर्ण
अटल DEVICE_ATTR_RO(id);

अटल काष्ठा attribute *pnp_dev_attrs[] = अणु
	&dev_attr_resources.attr,
	&dev_attr_options.attr,
	&dev_attr_id.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pnp_dev_group = अणु
	.attrs = pnp_dev_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *pnp_dev_groups[] = अणु
	&pnp_dev_group,
	शून्य,
पूर्ण;
