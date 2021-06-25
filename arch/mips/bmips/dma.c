<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2014 Kevin Cernekee <cernekee@gmail.com>
 */

#घोषणा pr_fmt(fmt)		"bmips-dma: " fmt

#समावेश <linux/device.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/bmips.h>

/*
 * BCM338x has configurable address translation winकरोws which allow the
 * peripherals' DMA addresses to be dअगरferent from the Zephyr-visible
 * physical addresses.  e.g. usb_dma_addr = zephyr_pa ^ 0x08000000
 *
 * If the "brcm,ubus" node has a "dma-ranges" property we will enable this
 * translation globally using the provided inक्रमmation.  This implements a
 * very limited subset of "dma-ranges" support and it will probably be
 * replaced by a more generic version later.
 */

काष्ठा bmips_dma_range अणु
	u32			child_addr;
	u32			parent_addr;
	u32			size;
पूर्ण;

अटल काष्ठा bmips_dma_range *bmips_dma_ranges;

#घोषणा FLUSH_RAC		0x100

dma_addr_t phys_to_dma(काष्ठा device *dev, phys_addr_t pa)
अणु
	काष्ठा bmips_dma_range *r;

	क्रम (r = bmips_dma_ranges; r && r->size; r++) अणु
		अगर (pa >= r->child_addr &&
		    pa < (r->child_addr + r->size))
			वापस pa - r->child_addr + r->parent_addr;
	पूर्ण
	वापस pa;
पूर्ण

phys_addr_t dma_to_phys(काष्ठा device *dev, dma_addr_t dma_addr)
अणु
	काष्ठा bmips_dma_range *r;

	क्रम (r = bmips_dma_ranges; r && r->size; r++) अणु
		अगर (dma_addr >= r->parent_addr &&
		    dma_addr < (r->parent_addr + r->size))
			वापस dma_addr - r->parent_addr + r->child_addr;
	पूर्ण
	वापस dma_addr;
पूर्ण

व्योम arch_sync_dma_क्रम_cpu_all(व्योम)
अणु
	व्योम __iomem *cbr = BMIPS_GET_CBR();
	u32 cfg;

	अगर (boot_cpu_type() != CPU_BMIPS3300 &&
	    boot_cpu_type() != CPU_BMIPS4350 &&
	    boot_cpu_type() != CPU_BMIPS4380)
		वापस;

	/* Flush stale data out of the पढ़ोahead cache */
	cfg = __raw_पढ़ोl(cbr + BMIPS_RAC_CONFIG);
	__raw_ग_लिखोl(cfg | 0x100, cbr + BMIPS_RAC_CONFIG);
	__raw_पढ़ोl(cbr + BMIPS_RAC_CONFIG);
पूर्ण

अटल पूर्णांक __init bmips_init_dma_ranges(व्योम)
अणु
	काष्ठा device_node *np =
		of_find_compatible_node(शून्य, शून्य, "brcm,ubus");
	स्थिर __be32 *data;
	काष्ठा bmips_dma_range *r;
	पूर्णांक len;

	अगर (!np)
		वापस 0;

	data = of_get_property(np, "dma-ranges", &len);
	अगर (!data)
		जाओ out_good;

	len /= माप(*data) * 3;
	अगर (!len)
		जाओ out_bad;

	/* add a dummy (zero) entry at the end as a sentinel */
	bmips_dma_ranges = kसुस्मृति(len + 1, माप(काष्ठा bmips_dma_range),
				   GFP_KERNEL);
	अगर (!bmips_dma_ranges)
		जाओ out_bad;

	क्रम (r = bmips_dma_ranges; len; len--, r++) अणु
		r->child_addr = be32_to_cpup(data++);
		r->parent_addr = be32_to_cpup(data++);
		r->size = be32_to_cpup(data++);
	पूर्ण

out_good:
	of_node_put(np);
	वापस 0;

out_bad:
	pr_err("error parsing dma-ranges property\n");
	of_node_put(np);
	वापस -EINVAL;
पूर्ण
arch_initcall(bmips_init_dma_ranges);
