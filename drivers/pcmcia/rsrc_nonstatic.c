<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rsrc_nonअटल.c -- Resource management routines क्रम !SS_CAP_STATIC_MAP sockets
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * (C) 1999		David A. Hinds
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/समयr.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/irq.h>

#समावेश <pcmcia/ss.h>
#समावेश <pcmcia/cistpl.h>
#समावेश "cs_internal.h"

/* moved to rsrc_mgr.c
MODULE_AUTHOR("David A. Hinds, Dominik Brodowski");
MODULE_LICENSE("GPL");
*/

/* Parameters that can be set with 'insmod' */

#घोषणा INT_MODULE_PARM(n, v) अटल पूर्णांक n = v; module_param(n, पूर्णांक, 0444)

INT_MODULE_PARM(probe_mem,	1);		/* memory probe? */
#अगर_घोषित CONFIG_PCMCIA_PROBE
INT_MODULE_PARM(probe_io,	1);		/* IO port probe? */
INT_MODULE_PARM(mem_limit,	0x10000);
#पूर्ण_अगर

/* क्रम io_db and mem_db */
काष्ठा resource_map अणु
	u_दीर्घ			base, num;
	काष्ठा resource_map	*next;
पूर्ण;

काष्ठा socket_data अणु
	काष्ठा resource_map		mem_db;
	काष्ठा resource_map		mem_db_valid;
	काष्ठा resource_map		io_db;
पूर्ण;

#घोषणा MEM_PROBE_LOW	(1 << 0)
#घोषणा MEM_PROBE_HIGH	(1 << 1)

/* Action field */
#घोषणा REMOVE_MANAGED_RESOURCE		1
#घोषणा ADD_MANAGED_RESOURCE		2

/*======================================================================

    Linux resource management extensions

======================================================================*/

अटल काष्ठा resource *
claim_region(काष्ठा pcmcia_socket *s, resource_माप_प्रकार base,
		resource_माप_प्रकार size, पूर्णांक type, अक्षर *name)
अणु
	काष्ठा resource *res, *parent;

	parent = type & IORESOURCE_MEM ? &iomem_resource : &ioport_resource;
	res = pcmcia_make_resource(base, size, type | IORESOURCE_BUSY, name);

	अगर (res) अणु
#अगर_घोषित CONFIG_PCI
		अगर (s && s->cb_dev)
			parent = pci_find_parent_resource(s->cb_dev, res);
#पूर्ण_अगर
		अगर (!parent || request_resource(parent, res)) अणु
			kमुक्त(res);
			res = शून्य;
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

अटल व्योम मुक्त_region(काष्ठा resource *res)
अणु
	अगर (res) अणु
		release_resource(res);
		kमुक्त(res);
	पूर्ण
पूर्ण

/*======================================================================

    These manage the पूर्णांकernal databases of available resources.

======================================================================*/

अटल पूर्णांक add_पूर्णांकerval(काष्ठा resource_map *map, u_दीर्घ base, u_दीर्घ num)
अणु
	काष्ठा resource_map *p, *q;

	क्रम (p = map; ; p = p->next) अणु
		अगर ((p != map) && (p->base+p->num >= base)) अणु
			p->num = max(num + base - p->base, p->num);
			वापस 0;
		पूर्ण
		अगर ((p->next == map) || (p->next->base > base+num-1))
			अवरोध;
	पूर्ण
	q = kदो_स्मृति(माप(काष्ठा resource_map), GFP_KERNEL);
	अगर (!q) अणु
		prपूर्णांकk(KERN_WARNING "out of memory to update resources\n");
		वापस -ENOMEM;
	पूर्ण
	q->base = base; q->num = num;
	q->next = p->next; p->next = q;
	वापस 0;
पूर्ण

/*====================================================================*/

अटल पूर्णांक sub_पूर्णांकerval(काष्ठा resource_map *map, u_दीर्घ base, u_दीर्घ num)
अणु
	काष्ठा resource_map *p, *q;

	क्रम (p = map; ; p = q) अणु
		q = p->next;
		अगर (q == map)
			अवरोध;
		अगर ((q->base+q->num > base) && (base+num > q->base)) अणु
			अगर (q->base >= base) अणु
				अगर (q->base+q->num <= base+num) अणु
					/* Delete whole block */
					p->next = q->next;
					kमुक्त(q);
					/* करोn't advance the poपूर्णांकer yet */
					q = p;
				पूर्ण अन्यथा अणु
					/* Cut off bit from the front */
					q->num = q->base + q->num - base - num;
					q->base = base + num;
				पूर्ण
			पूर्ण अन्यथा अगर (q->base+q->num <= base+num) अणु
				/* Cut off bit from the end */
				q->num = base - q->base;
			पूर्ण अन्यथा अणु
				/* Split the block पूर्णांकo two pieces */
				p = kदो_स्मृति(माप(काष्ठा resource_map),
					GFP_KERNEL);
				अगर (!p) अणु
					prपूर्णांकk(KERN_WARNING "out of memory to update resources\n");
					वापस -ENOMEM;
				पूर्ण
				p->base = base+num;
				p->num = q->base+q->num - p->base;
				q->num = base - q->base;
				p->next = q->next ; q->next = p;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*======================================================================

    These routines examine a region of IO or memory addresses to
    determine what ranges might be genuinely available.

======================================================================*/

#अगर_घोषित CONFIG_PCMCIA_PROBE
अटल व्योम करो_io_probe(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक base,
			अचिन्हित पूर्णांक num)
अणु
	काष्ठा resource *res;
	काष्ठा socket_data *s_data = s->resource_data;
	अचिन्हित पूर्णांक i, j, bad;
	पूर्णांक any;
	u_अक्षर *b, hole, most;

	dev_info(&s->dev, "cs: IO port probe %#x-%#x:", base, base+num-1);

	/* First, what करोes a भग्नing port look like? */
	b = kzalloc(256, GFP_KERNEL);
	अगर (!b) अणु
		pr_cont("\n");
		dev_err(&s->dev, "do_io_probe: unable to kmalloc 256 bytes\n");
		वापस;
	पूर्ण
	क्रम (i = base, most = 0; i < base+num; i += 8) अणु
		res = claim_region(s, i, 8, IORESOURCE_IO, "PCMCIA ioprobe");
		अगर (!res)
			जारी;
		hole = inb(i);
		क्रम (j = 1; j < 8; j++)
			अगर (inb(i+j) != hole)
				अवरोध;
		मुक्त_region(res);
		अगर ((j == 8) && (++b[hole] > b[most]))
			most = hole;
		अगर (b[most] == 127)
			अवरोध;
	पूर्ण
	kमुक्त(b);

	bad = any = 0;
	क्रम (i = base; i < base+num; i += 8) अणु
		res = claim_region(s, i, 8, IORESOURCE_IO, "PCMCIA ioprobe");
		अगर (!res) अणु
			अगर (!any)
				pr_cont(" excluding");
			अगर (!bad)
				bad = any = i;
			जारी;
		पूर्ण
		क्रम (j = 0; j < 8; j++)
			अगर (inb(i+j) != most)
				अवरोध;
		मुक्त_region(res);
		अगर (j < 8) अणु
			अगर (!any)
				pr_cont(" excluding");
			अगर (!bad)
				bad = any = i;
		पूर्ण अन्यथा अणु
			अगर (bad) अणु
				sub_पूर्णांकerval(&s_data->io_db, bad, i-bad);
				pr_cont(" %#x-%#x", bad, i-1);
				bad = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (bad) अणु
		अगर ((num > 16) && (bad == base) && (i == base+num)) अणु
			sub_पूर्णांकerval(&s_data->io_db, bad, i-bad);
			pr_cont(" nothing: probe failed.\n");
			वापस;
		पूर्ण अन्यथा अणु
			sub_पूर्णांकerval(&s_data->io_db, bad, i-bad);
			pr_cont(" %#x-%#x", bad, i-1);
		पूर्ण
	पूर्ण

	pr_cont("%s\n", !any ? " clean" : "");
पूर्ण
#पूर्ण_अगर

/*======================================================================*/

/*
 * पढ़ोable() - iomem validation function क्रम cards with a valid CIS
 */
अटल पूर्णांक पढ़ोable(काष्ठा pcmcia_socket *s, काष्ठा resource *res,
		    अचिन्हित पूर्णांक *count)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (s->fake_cis) अणु
		dev_dbg(&s->dev, "fake CIS is being used: can't validate mem\n");
		वापस 0;
	पूर्ण

	s->cis_mem.res = res;
	s->cis_virt = ioremap(res->start, s->map_size);
	अगर (s->cis_virt) अणु
		mutex_unlock(&s->ops_mutex);
		/* as we're only called from pcmcia.c, we're safe */
		अगर (s->callback->validate)
			ret = s->callback->validate(s, count);
		/* invalidate mapping */
		mutex_lock(&s->ops_mutex);
		iounmap(s->cis_virt);
		s->cis_virt = शून्य;
	पूर्ण
	s->cis_mem.res = शून्य;
	अगर ((ret) || (*count == 0))
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * checksum() - iomem validation function क्रम simple memory cards
 */
अटल पूर्णांक checksum(काष्ठा pcmcia_socket *s, काष्ठा resource *res,
		    अचिन्हित पूर्णांक *value)
अणु
	pccard_mem_map map;
	पूर्णांक i, a = 0, b = -1, d;
	व्योम __iomem *virt;

	virt = ioremap(res->start, s->map_size);
	अगर (virt) अणु
		map.map = 0;
		map.flags = MAP_ACTIVE;
		map.speed = 0;
		map.res = res;
		map.card_start = 0;
		s->ops->set_mem_map(s, &map);

		/* Don't bother checking every word... */
		क्रम (i = 0; i < s->map_size; i += 44) अणु
			d = पढ़ोl(virt+i);
			a += d;
			b &= d;
		पूर्ण

		map.flags = 0;
		s->ops->set_mem_map(s, &map);

		iounmap(virt);
	पूर्ण

	अगर (b == -1)
		वापस -EINVAL;

	*value = a;

	वापस 0;
पूर्ण

/**
 * करो_validate_mem() - low level validate a memory region क्रम PCMCIA use
 * @s:		PCMCIA socket to validate
 * @base:	start address of resource to check
 * @size:	size of resource to check
 * @validate:	validation function to use
 *
 * करो_validate_mem() splits up the memory region which is to be checked
 * पूर्णांकo two parts. Both are passed to the @validate() function. If
 * @validate() वापसs non-zero, or the value parameter to @validate()
 * is zero, or the value parameter is dअगरferent between both calls,
 * the check fails, and -EINVAL is वापसed. Else, 0 is वापसed.
 */
अटल पूर्णांक करो_validate_mem(काष्ठा pcmcia_socket *s,
			   अचिन्हित दीर्घ base, अचिन्हित दीर्घ size,
			   पूर्णांक (*validate)(काष्ठा pcmcia_socket *s,
					   काष्ठा resource *res,
					   अचिन्हित पूर्णांक *value))
अणु
	काष्ठा socket_data *s_data = s->resource_data;
	काष्ठा resource *res1, *res2;
	अचिन्हित पूर्णांक info1 = 1, info2 = 1;
	पूर्णांक ret = -EINVAL;

	res1 = claim_region(s, base, size/2, IORESOURCE_MEM, "PCMCIA memprobe");
	res2 = claim_region(s, base + size/2, size/2, IORESOURCE_MEM,
			"PCMCIA memprobe");

	अगर (res1 && res2) अणु
		ret = 0;
		अगर (validate) अणु
			ret = validate(s, res1, &info1);
			ret += validate(s, res2, &info2);
		पूर्ण
	पूर्ण

	dev_dbg(&s->dev, "cs: memory probe 0x%06lx-0x%06lx: %pr %pr %u %u %u",
		base, base+size-1, res1, res2, ret, info1, info2);

	मुक्त_region(res2);
	मुक्त_region(res1);

	अगर ((ret) || (info1 != info2) || (info1 == 0))
		वापस -EINVAL;

	अगर (validate && !s->fake_cis) अणु
		/* move it to the validated data set */
		add_पूर्णांकerval(&s_data->mem_db_valid, base, size);
		sub_पूर्णांकerval(&s_data->mem_db, base, size);
	पूर्ण

	वापस 0;
पूर्ण


/**
 * करो_mem_probe() - validate a memory region क्रम PCMCIA use
 * @s:		PCMCIA socket to validate
 * @base:	start address of resource to check
 * @num:	size of resource to check
 * @validate:	validation function to use
 * @fallback:	validation function to use अगर validate fails
 *
 * करो_mem_probe() checks a memory region क्रम use by the PCMCIA subप्रणाली.
 * To करो so, the area is split up पूर्णांकo sensible parts, and then passed
 * पूर्णांकo the @validate() function. Only अगर @validate() and @fallback() fail,
 * the area is marked as unavaibale क्रम use by the PCMCIA subप्रणाली. The
 * function वापसs the size of the usable memory area.
 */
अटल पूर्णांक करो_mem_probe(काष्ठा pcmcia_socket *s, u_दीर्घ base, u_दीर्घ num,
			पूर्णांक (*validate)(काष्ठा pcmcia_socket *s,
					काष्ठा resource *res,
					अचिन्हित पूर्णांक *value),
			पूर्णांक (*fallback)(काष्ठा pcmcia_socket *s,
					काष्ठा resource *res,
					अचिन्हित पूर्णांक *value))
अणु
	काष्ठा socket_data *s_data = s->resource_data;
	u_दीर्घ i, j, bad, fail, step;

	dev_info(&s->dev, "cs: memory probe 0x%06lx-0x%06lx:",
		 base, base+num-1);
	bad = fail = 0;
	step = (num < 0x20000) ? 0x2000 : ((num>>4) & ~0x1fff);
	/* करोn't allow too large steps */
	अगर (step > 0x800000)
		step = 0x800000;
	/* cis_पढ़ोable wants to map 2x map_size */
	अगर (step < 2 * s->map_size)
		step = 2 * s->map_size;
	क्रम (i = j = base; i < base+num; i = j + step) अणु
		अगर (!fail) अणु
			क्रम (j = i; j < base+num; j += step) अणु
				अगर (!करो_validate_mem(s, j, step, validate))
					अवरोध;
			पूर्ण
			fail = ((i == base) && (j == base+num));
		पूर्ण
		अगर ((fail) && (fallback)) अणु
			क्रम (j = i; j < base+num; j += step)
				अगर (!करो_validate_mem(s, j, step, fallback))
					अवरोध;
		पूर्ण
		अगर (i != j) अणु
			अगर (!bad)
				pr_cont(" excluding");
			pr_cont(" %#05lx-%#05lx", i, j-1);
			sub_पूर्णांकerval(&s_data->mem_db, i, j-i);
			bad += j-i;
		पूर्ण
	पूर्ण
	pr_cont("%s\n", !bad ? " clean" : "");
	वापस num - bad;
पूर्ण


#अगर_घोषित CONFIG_PCMCIA_PROBE

/**
 * inv_probe() - top-to-bottom search क्रम one usuable high memory area
 * @s:		PCMCIA socket to validate
 * @m:		resource_map to check
 */
अटल u_दीर्घ inv_probe(काष्ठा resource_map *m, काष्ठा pcmcia_socket *s)
अणु
	काष्ठा socket_data *s_data = s->resource_data;
	u_दीर्घ ok;
	अगर (m == &s_data->mem_db)
		वापस 0;
	ok = inv_probe(m->next, s);
	अगर (ok) अणु
		अगर (m->base >= 0x100000)
			sub_पूर्णांकerval(&s_data->mem_db, m->base, m->num);
		वापस ok;
	पूर्ण
	अगर (m->base < 0x100000)
		वापस 0;
	वापस करो_mem_probe(s, m->base, m->num, पढ़ोable, checksum);
पूर्ण

/**
 * validate_mem() - memory probe function
 * @s:		PCMCIA socket to validate
 * @probe_mask: MEM_PROBE_LOW | MEM_PROBE_HIGH
 *
 * The memory probe.  If the memory list includes a 64K-aligned block
 * below 1MB, we probe in 64K chunks, and as soon as we accumulate at
 * least mem_limit मुक्त space, we quit. Returns 0 on usuable ports.
 */
अटल पूर्णांक validate_mem(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक probe_mask)
अणु
	काष्ठा resource_map *m, mm;
	अटल अचिन्हित अक्षर order[] = अणु 0xd0, 0xe0, 0xc0, 0xf0 पूर्ण;
	अचिन्हित दीर्घ b, i, ok = 0;
	काष्ठा socket_data *s_data = s->resource_data;

	/* We करो up to four passes through the list */
	अगर (probe_mask & MEM_PROBE_HIGH) अणु
		अगर (inv_probe(s_data->mem_db.next, s) > 0)
			वापस 0;
		अगर (s_data->mem_db_valid.next != &s_data->mem_db_valid)
			वापस 0;
		dev_notice(&s->dev,
			   "cs: warning: no high memory space available!\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (m = s_data->mem_db.next; m != &s_data->mem_db; m = mm.next) अणु
		mm = *m;
		/* Only probe < 1 MB */
		अगर (mm.base >= 0x100000)
			जारी;
		अगर ((mm.base | mm.num) & 0xffff) अणु
			ok += करो_mem_probe(s, mm.base, mm.num, पढ़ोable,
					   checksum);
			जारी;
		पूर्ण
		/* Special probe क्रम 64K-aligned block */
		क्रम (i = 0; i < 4; i++) अणु
			b = order[i] << 12;
			अगर ((b >= mm.base) && (b+0x10000 <= mm.base+mm.num)) अणु
				अगर (ok >= mem_limit)
					sub_पूर्णांकerval(&s_data->mem_db, b, 0x10000);
				अन्यथा
					ok += करो_mem_probe(s, b, 0x10000,
							   पढ़ोable, checksum);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ok > 0)
		वापस 0;

	वापस -ENODEV;
पूर्ण

#अन्यथा /* CONFIG_PCMCIA_PROBE */

/**
 * validate_mem() - memory probe function
 * @s:		PCMCIA socket to validate
 * @probe_mask: ignored
 *
 * Returns 0 on usuable ports.
 */
अटल पूर्णांक validate_mem(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक probe_mask)
अणु
	काष्ठा resource_map *m, mm;
	काष्ठा socket_data *s_data = s->resource_data;
	अचिन्हित दीर्घ ok = 0;

	क्रम (m = s_data->mem_db.next; m != &s_data->mem_db; m = mm.next) अणु
		mm = *m;
		ok += करो_mem_probe(s, mm.base, mm.num, पढ़ोable, checksum);
	पूर्ण
	अगर (ok > 0)
		वापस 0;
	वापस -ENODEV;
पूर्ण

#पूर्ण_अगर /* CONFIG_PCMCIA_PROBE */


/**
 * pcmcia_nonअटल_validate_mem() - try to validate iomem क्रम PCMCIA use
 * @s:		PCMCIA socket to validate
 *
 * This is tricky... when we set up CIS memory, we try to validate
 * the memory winकरोw space allocations.
 *
 * Locking note: Must be called with skt_mutex held!
 */
अटल पूर्णांक pcmcia_nonअटल_validate_mem(काष्ठा pcmcia_socket *s)
अणु
	काष्ठा socket_data *s_data = s->resource_data;
	अचिन्हित पूर्णांक probe_mask = MEM_PROBE_LOW;
	पूर्णांक ret;

	अगर (!probe_mem || !(s->state & SOCKET_PRESENT))
		वापस 0;

	अगर (s->features & SS_CAP_PAGE_REGS)
		probe_mask = MEM_PROBE_HIGH;

	ret = validate_mem(s, probe_mask);

	अगर (s_data->mem_db_valid.next != &s_data->mem_db_valid)
		वापस 0;

	वापस ret;
पूर्ण

काष्ठा pcmcia_align_data अणु
	अचिन्हित दीर्घ	mask;
	अचिन्हित दीर्घ	offset;
	काष्ठा resource_map	*map;
पूर्ण;

अटल resource_माप_प्रकार pcmcia_common_align(काष्ठा pcmcia_align_data *align_data,
					resource_माप_प्रकार start)
अणु
	resource_माप_प्रकार ret;
	/*
	 * Ensure that we have the correct start address
	 */
	ret = (start & ~align_data->mask) + align_data->offset;
	अगर (ret < start)
		ret += align_data->mask + 1;
	वापस ret;
पूर्ण

अटल resource_माप_प्रकार
pcmcia_align(व्योम *align_data, स्थिर काष्ठा resource *res,
	resource_माप_प्रकार size, resource_माप_प्रकार align)
अणु
	काष्ठा pcmcia_align_data *data = align_data;
	काष्ठा resource_map *m;
	resource_माप_प्रकार start;

	start = pcmcia_common_align(data, res->start);

	क्रम (m = data->map->next; m != data->map; m = m->next) अणु
		अचिन्हित दीर्घ map_start = m->base;
		अचिन्हित दीर्घ map_end = m->base + m->num - 1;

		/*
		 * If the lower resources are not available, try aligning
		 * to this entry of the resource database to see अगर it'll
		 * fit here.
		 */
		अगर (start < map_start)
			start = pcmcia_common_align(data, map_start);

		/*
		 * If we're above the area which was passed in, there's
		 * no poपूर्णांक proceeding.
		 */
		अगर (start >= res->end)
			अवरोध;

		अगर ((start + size - 1) <= map_end)
			अवरोध;
	पूर्ण

	/*
	 * If we failed to find something suitable, ensure we fail.
	 */
	अगर (m == data->map)
		start = res->end;

	वापस start;
पूर्ण

/*
 * Adjust an existing IO region allocation, but making sure that we करोn't
 * encroach outside the resources which the user supplied.
 */
अटल पूर्णांक __nonअटल_adjust_io_region(काष्ठा pcmcia_socket *s,
					अचिन्हित दीर्घ r_start,
					अचिन्हित दीर्घ r_end)
अणु
	काष्ठा resource_map *m;
	काष्ठा socket_data *s_data = s->resource_data;
	पूर्णांक ret = -ENOMEM;

	क्रम (m = s_data->io_db.next; m != &s_data->io_db; m = m->next) अणु
		अचिन्हित दीर्घ start = m->base;
		अचिन्हित दीर्घ end = m->base + m->num - 1;

		अगर (start > r_start || r_end > end)
			जारी;

		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/*======================================================================

    These find ranges of I/O ports or memory addresses that are not
    currently allocated by other devices.

    The 'align' field should reflect the number of bits of address
    that need to be preserved from the initial value of *base.  It
    should be a घातer of two, greater than or equal to 'num'.  A value
    of 0 means that all bits of *base are signअगरicant.  *base should
    also be strictly less than 'align'.

======================================================================*/

अटल काष्ठा resource *__nonअटल_find_io_region(काष्ठा pcmcia_socket *s,
						अचिन्हित दीर्घ base, पूर्णांक num,
						अचिन्हित दीर्घ align)
अणु
	काष्ठा resource *res = pcmcia_make_resource(0, num, IORESOURCE_IO,
						dev_name(&s->dev));
	काष्ठा socket_data *s_data = s->resource_data;
	काष्ठा pcmcia_align_data data;
	अचिन्हित दीर्घ min = base;
	पूर्णांक ret;

	data.mask = align - 1;
	data.offset = base & data.mask;
	data.map = &s_data->io_db;

#अगर_घोषित CONFIG_PCI
	अगर (s->cb_dev) अणु
		ret = pci_bus_alloc_resource(s->cb_dev->bus, res, num, 1,
					     min, 0, pcmcia_align, &data);
	पूर्ण अन्यथा
#पूर्ण_अगर
		ret = allocate_resource(&ioport_resource, res, num, min, ~0UL,
					1, pcmcia_align, &data);

	अगर (ret != 0) अणु
		kमुक्त(res);
		res = शून्य;
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक nonअटल_find_io(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक attr,
			अचिन्हित पूर्णांक *base, अचिन्हित पूर्णांक num,
			अचिन्हित पूर्णांक align, काष्ठा resource **parent)
अणु
	पूर्णांक i, ret = 0;

	/* Check क्रम an alपढ़ोy-allocated winकरोw that must conflict with
	 * what was asked क्रम.  It is a hack because it करोes not catch all
	 * potential conflicts, just the most obvious ones.
	 */
	क्रम (i = 0; i < MAX_IO_WIN; i++) अणु
		अगर (!s->io[i].res)
			जारी;

		अगर (!*base)
			जारी;

		अगर ((s->io[i].res->start & (align-1)) == *base)
			वापस -EBUSY;
	पूर्ण

	क्रम (i = 0; i < MAX_IO_WIN; i++) अणु
		काष्ठा resource *res = s->io[i].res;
		अचिन्हित पूर्णांक try;

		अगर (res && (res->flags & IORESOURCE_BITS) !=
			(attr & IORESOURCE_BITS))
			जारी;

		अगर (!res) अणु
			अगर (align == 0)
				align = 0x10000;

			res = s->io[i].res = __nonअटल_find_io_region(s,
								*base, num,
								align);
			अगर (!res)
				वापस -EINVAL;

			*base = res->start;
			s->io[i].res->flags =
				((res->flags & ~IORESOURCE_BITS) |
					(attr & IORESOURCE_BITS));
			s->io[i].InUse = num;
			*parent = res;
			वापस 0;
		पूर्ण

		/* Try to extend top of winकरोw */
		try = res->end + 1;
		अगर ((*base == 0) || (*base == try)) अणु
			ret =  __nonअटल_adjust_io_region(s, res->start,
							res->end + num);
			अगर (!ret) अणु
				ret = adjust_resource(s->io[i].res, res->start,
						      resource_size(res) + num);
				अगर (ret)
					जारी;
				*base = try;
				s->io[i].InUse += num;
				*parent = res;
				वापस 0;
			पूर्ण
		पूर्ण

		/* Try to extend bottom of winकरोw */
		try = res->start - num;
		अगर ((*base == 0) || (*base == try)) अणु
			ret =  __nonअटल_adjust_io_region(s,
							res->start - num,
							res->end);
			अगर (!ret) अणु
				ret = adjust_resource(s->io[i].res,
						      res->start - num,
						      resource_size(res) + num);
				अगर (ret)
					जारी;
				*base = try;
				s->io[i].InUse += num;
				*parent = res;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण


अटल काष्ठा resource *nonअटल_find_mem_region(u_दीर्घ base, u_दीर्घ num,
		u_दीर्घ align, पूर्णांक low, काष्ठा pcmcia_socket *s)
अणु
	काष्ठा resource *res = pcmcia_make_resource(0, num, IORESOURCE_MEM,
						dev_name(&s->dev));
	काष्ठा socket_data *s_data = s->resource_data;
	काष्ठा pcmcia_align_data data;
	अचिन्हित दीर्घ min, max;
	पूर्णांक ret, i, j;

	low = low || !(s->features & SS_CAP_PAGE_REGS);

	data.mask = align - 1;
	data.offset = base & data.mask;

	क्रम (i = 0; i < 2; i++) अणु
		data.map = &s_data->mem_db_valid;
		अगर (low) अणु
			max = 0x100000UL;
			min = base < max ? base : 0;
		पूर्ण अन्यथा अणु
			max = ~0UL;
			min = 0x100000UL + base;
		पूर्ण

		क्रम (j = 0; j < 2; j++) अणु
#अगर_घोषित CONFIG_PCI
			अगर (s->cb_dev) अणु
				ret = pci_bus_alloc_resource(s->cb_dev->bus,
							res, num, 1, min, 0,
							pcmcia_align, &data);
			पूर्ण अन्यथा
#पूर्ण_अगर
			अणु
				ret = allocate_resource(&iomem_resource,
							res, num, min, max, 1,
							pcmcia_align, &data);
			पूर्ण
			अगर (ret == 0)
				अवरोध;
			data.map = &s_data->mem_db;
		पूर्ण
		अगर (ret == 0 || low)
			अवरोध;
		low = 1;
	पूर्ण

	अगर (ret != 0) अणु
		kमुक्त(res);
		res = शून्य;
	पूर्ण
	वापस res;
पूर्ण


अटल पूर्णांक adjust_memory(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक action, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा socket_data *data = s->resource_data;
	अचिन्हित दीर्घ size = end - start + 1;
	पूर्णांक ret = 0;

	अगर (end < start)
		वापस -EINVAL;

	चयन (action) अणु
	हाल ADD_MANAGED_RESOURCE:
		ret = add_पूर्णांकerval(&data->mem_db, start, size);
		अगर (!ret)
			करो_mem_probe(s, start, size, शून्य, शून्य);
		अवरोध;
	हाल REMOVE_MANAGED_RESOURCE:
		ret = sub_पूर्णांकerval(&data->mem_db, start, size);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण


अटल पूर्णांक adjust_io(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक action, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा socket_data *data = s->resource_data;
	अचिन्हित दीर्घ size;
	पूर्णांक ret = 0;

#अगर defined(CONFIG_X86)
	/* on x86, aव्योम anything < 0x100 क्रम it is often used क्रम
	 * legacy platक्रमm devices */
	अगर (start < 0x100)
		start = 0x100;
#पूर्ण_अगर

	size = end - start + 1;

	अगर (end < start)
		वापस -EINVAL;

	अगर (end > IO_SPACE_LIMIT)
		वापस -EINVAL;

	चयन (action) अणु
	हाल ADD_MANAGED_RESOURCE:
		अगर (add_पूर्णांकerval(&data->io_db, start, size) != 0) अणु
			ret = -EBUSY;
			अवरोध;
		पूर्ण
#अगर_घोषित CONFIG_PCMCIA_PROBE
		अगर (probe_io)
			करो_io_probe(s, start, size);
#पूर्ण_अगर
		अवरोध;
	हाल REMOVE_MANAGED_RESOURCE:
		sub_पूर्णांकerval(&data->io_db, start, size);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण


#अगर_घोषित CONFIG_PCI
अटल पूर्णांक nonअटल_स्वतःadd_resources(काष्ठा pcmcia_socket *s)
अणु
	काष्ठा resource *res;
	पूर्णांक i, करोne = 0;

	अगर (!s->cb_dev || !s->cb_dev->bus)
		वापस -ENODEV;

#अगर defined(CONFIG_X86)
	/* If this is the root bus, the risk of hitting some strange
	 * प्रणाली devices is too high: If a driver isn't loaded, the
	 * resources are not claimed; even अगर a driver is loaded, it
	 * may not request all resources or even the wrong one. We
	 * can neither trust the rest of the kernel nor ACPI/PNP and
	 * CRS parsing to get it right. Thereक्रमe, use several
	 * safeguards:
	 *
	 * - Do not स्वतः-add resources अगर the CardBus bridge is on
	 *   the PCI root bus
	 *
	 * - Aव्योम any I/O ports < 0x100.
	 *
	 * - On PCI-PCI bridges, only use resources which are set up
	 *   exclusively क्रम the secondary PCI bus: the risk of hitting
	 *   प्रणाली devices is quite low, as they usually aren't
	 *   connected to the secondary PCI bus.
	 */
	अगर (s->cb_dev->bus->number == 0)
		वापस -EINVAL;

	क्रम (i = 0; i < PCI_BRIDGE_RESOURCE_NUM; i++) अणु
		res = s->cb_dev->bus->resource[i];
#अन्यथा
	pci_bus_क्रम_each_resource(s->cb_dev->bus, res, i) अणु
#पूर्ण_अगर
		अगर (!res)
			जारी;

		अगर (res->flags & IORESOURCE_IO) अणु
			/* safeguard against the root resource, where the
			 * risk of hitting any other device would be too
			 * high */
			अगर (res == &ioport_resource)
				जारी;

			dev_info(&s->cb_dev->dev,
				 "pcmcia: parent PCI bridge window: %pR\n",
				 res);
			अगर (!adjust_io(s, ADD_MANAGED_RESOURCE, res->start, res->end))
				करोne |= IORESOURCE_IO;

		पूर्ण

		अगर (res->flags & IORESOURCE_MEM) अणु
			/* safeguard against the root resource, where the
			 * risk of hitting any other device would be too
			 * high */
			अगर (res == &iomem_resource)
				जारी;

			dev_info(&s->cb_dev->dev,
				 "pcmcia: parent PCI bridge window: %pR\n",
				 res);
			अगर (!adjust_memory(s, ADD_MANAGED_RESOURCE, res->start, res->end))
				करोne |= IORESOURCE_MEM;
		पूर्ण
	पूर्ण

	/* अगर we got at least one of IO, and one of MEM, we can be glad and
	 * activate the PCMCIA subप्रणाली */
	अगर (करोne == (IORESOURCE_MEM | IORESOURCE_IO))
		s->resource_setup_करोne = 1;

	वापस 0;
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक nonअटल_स्वतःadd_resources(काष्ठा pcmcia_socket *s)
अणु
	वापस -ENODEV;
पूर्ण

#पूर्ण_अगर


अटल पूर्णांक nonअटल_init(काष्ठा pcmcia_socket *s)
अणु
	काष्ठा socket_data *data;

	data = kzalloc(माप(काष्ठा socket_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->mem_db.next = &data->mem_db;
	data->mem_db_valid.next = &data->mem_db_valid;
	data->io_db.next = &data->io_db;

	s->resource_data = (व्योम *) data;

	nonअटल_स्वतःadd_resources(s);

	वापस 0;
पूर्ण

अटल व्योम nonअटल_release_resource_db(काष्ठा pcmcia_socket *s)
अणु
	काष्ठा socket_data *data = s->resource_data;
	काष्ठा resource_map *p, *q;

	क्रम (p = data->mem_db_valid.next; p != &data->mem_db_valid; p = q) अणु
		q = p->next;
		kमुक्त(p);
	पूर्ण
	क्रम (p = data->mem_db.next; p != &data->mem_db; p = q) अणु
		q = p->next;
		kमुक्त(p);
	पूर्ण
	क्रम (p = data->io_db.next; p != &data->io_db; p = q) अणु
		q = p->next;
		kमुक्त(p);
	पूर्ण
पूर्ण


काष्ठा pccard_resource_ops pccard_nonअटल_ops = अणु
	.validate_mem = pcmcia_nonअटल_validate_mem,
	.find_io = nonअटल_find_io,
	.find_mem = nonअटल_find_mem_region,
	.init = nonअटल_init,
	.निकास = nonअटल_release_resource_db,
पूर्ण;
EXPORT_SYMBOL(pccard_nonअटल_ops);


/* sysfs पूर्णांकerface to the resource database */

अटल sमाप_प्रकार show_io_db(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pcmcia_socket *s = dev_get_drvdata(dev);
	काष्ठा socket_data *data;
	काष्ठा resource_map *p;
	sमाप_प्रकार ret = 0;

	mutex_lock(&s->ops_mutex);
	data = s->resource_data;

	क्रम (p = data->io_db.next; p != &data->io_db; p = p->next) अणु
		अगर (ret > (PAGE_SIZE - 10))
			जारी;
		ret += scnम_लिखो(&buf[ret], (PAGE_SIZE - ret - 1),
				"0x%08lx - 0x%08lx\n",
				((अचिन्हित दीर्घ) p->base),
				((अचिन्हित दीर्घ) p->base + p->num - 1));
	पूर्ण

	mutex_unlock(&s->ops_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार store_io_db(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcmcia_socket *s = dev_get_drvdata(dev);
	अचिन्हित दीर्घ start_addr, end_addr;
	अचिन्हित पूर्णांक add = ADD_MANAGED_RESOURCE;
	sमाप_प्रकार ret = 0;

	ret = माला_पूछो(buf, "+ 0x%lx - 0x%lx", &start_addr, &end_addr);
	अगर (ret != 2) अणु
		ret = माला_पूछो(buf, "- 0x%lx - 0x%lx", &start_addr, &end_addr);
		add = REMOVE_MANAGED_RESOURCE;
		अगर (ret != 2) अणु
			ret = माला_पूछो(buf, "0x%lx - 0x%lx", &start_addr,
				&end_addr);
			add = ADD_MANAGED_RESOURCE;
			अगर (ret != 2)
				वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (end_addr < start_addr)
		वापस -EINVAL;

	mutex_lock(&s->ops_mutex);
	ret = adjust_io(s, add, start_addr, end_addr);
	mutex_unlock(&s->ops_mutex);

	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR(available_resources_io, 0600, show_io_db, store_io_db);

अटल sमाप_प्रकार show_mem_db(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pcmcia_socket *s = dev_get_drvdata(dev);
	काष्ठा socket_data *data;
	काष्ठा resource_map *p;
	sमाप_प्रकार ret = 0;

	mutex_lock(&s->ops_mutex);
	data = s->resource_data;

	क्रम (p = data->mem_db_valid.next; p != &data->mem_db_valid;
	     p = p->next) अणु
		अगर (ret > (PAGE_SIZE - 10))
			जारी;
		ret += scnम_लिखो(&buf[ret], (PAGE_SIZE - ret - 1),
				"0x%08lx - 0x%08lx\n",
				((अचिन्हित दीर्घ) p->base),
				((अचिन्हित दीर्घ) p->base + p->num - 1));
	पूर्ण

	क्रम (p = data->mem_db.next; p != &data->mem_db; p = p->next) अणु
		अगर (ret > (PAGE_SIZE - 10))
			जारी;
		ret += scnम_लिखो(&buf[ret], (PAGE_SIZE - ret - 1),
				"0x%08lx - 0x%08lx\n",
				((अचिन्हित दीर्घ) p->base),
				((अचिन्हित दीर्घ) p->base + p->num - 1));
	पूर्ण

	mutex_unlock(&s->ops_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार store_mem_db(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcmcia_socket *s = dev_get_drvdata(dev);
	अचिन्हित दीर्घ start_addr, end_addr;
	अचिन्हित पूर्णांक add = ADD_MANAGED_RESOURCE;
	sमाप_प्रकार ret = 0;

	ret = माला_पूछो(buf, "+ 0x%lx - 0x%lx", &start_addr, &end_addr);
	अगर (ret != 2) अणु
		ret = माला_पूछो(buf, "- 0x%lx - 0x%lx", &start_addr, &end_addr);
		add = REMOVE_MANAGED_RESOURCE;
		अगर (ret != 2) अणु
			ret = माला_पूछो(buf, "0x%lx - 0x%lx", &start_addr,
				&end_addr);
			add = ADD_MANAGED_RESOURCE;
			अगर (ret != 2)
				वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (end_addr < start_addr)
		वापस -EINVAL;

	mutex_lock(&s->ops_mutex);
	ret = adjust_memory(s, add, start_addr, end_addr);
	mutex_unlock(&s->ops_mutex);

	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR(available_resources_mem, 0600, show_mem_db, store_mem_db);

अटल काष्ठा attribute *pccard_rsrc_attributes[] = अणु
	&dev_attr_available_resources_io.attr,
	&dev_attr_available_resources_mem.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rsrc_attributes = अणु
	.attrs = pccard_rsrc_attributes,
पूर्ण;

अटल पूर्णांक pccard_sysfs_add_rsrc(काष्ठा device *dev,
					   काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	काष्ठा pcmcia_socket *s = dev_get_drvdata(dev);

	अगर (s->resource_ops != &pccard_nonअटल_ops)
		वापस 0;
	वापस sysfs_create_group(&dev->kobj, &rsrc_attributes);
पूर्ण

अटल व्योम pccard_sysfs_हटाओ_rsrc(काष्ठा device *dev,
					       काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	काष्ठा pcmcia_socket *s = dev_get_drvdata(dev);

	अगर (s->resource_ops != &pccard_nonअटल_ops)
		वापस;
	sysfs_हटाओ_group(&dev->kobj, &rsrc_attributes);
पूर्ण

अटल काष्ठा class_पूर्णांकerface pccard_rsrc_पूर्णांकerface __refdata = अणु
	.class = &pcmcia_socket_class,
	.add_dev = &pccard_sysfs_add_rsrc,
	.हटाओ_dev = &pccard_sysfs_हटाओ_rsrc,
पूर्ण;

अटल पूर्णांक __init nonअटल_sysfs_init(व्योम)
अणु
	वापस class_पूर्णांकerface_रेजिस्टर(&pccard_rsrc_पूर्णांकerface);
पूर्ण

अटल व्योम __निकास nonअटल_sysfs_निकास(व्योम)
अणु
	class_पूर्णांकerface_unरेजिस्टर(&pccard_rsrc_पूर्णांकerface);
पूर्ण

module_init(nonअटल_sysfs_init);
module_निकास(nonअटल_sysfs_निकास);
