<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2006-2008, Michael Ellerman, IBM Corporation.
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/msi_biपंचांगap.h>
#समावेश <यंत्र/setup.h>

पूर्णांक msi_biपंचांगap_alloc_hwirqs(काष्ठा msi_biपंचांगap *bmp, पूर्णांक num)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक offset, order = get_count_order(num);

	spin_lock_irqsave(&bmp->lock, flags);

	offset = biपंचांगap_find_next_zero_area(bmp->biपंचांगap, bmp->irq_count, 0,
					    num, (1 << order) - 1);
	अगर (offset > bmp->irq_count)
		जाओ err;

	biपंचांगap_set(bmp->biपंचांगap, offset, num);
	spin_unlock_irqrestore(&bmp->lock, flags);

	pr_debug("msi_bitmap: allocated 0x%x at offset 0x%x\n", num, offset);

	वापस offset;
err:
	spin_unlock_irqrestore(&bmp->lock, flags);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(msi_biपंचांगap_alloc_hwirqs);

व्योम msi_biपंचांगap_मुक्त_hwirqs(काष्ठा msi_biपंचांगap *bmp, अचिन्हित पूर्णांक offset,
			    अचिन्हित पूर्णांक num)
अणु
	अचिन्हित दीर्घ flags;

	pr_debug("msi_bitmap: freeing 0x%x at offset 0x%x\n",
		 num, offset);

	spin_lock_irqsave(&bmp->lock, flags);
	biपंचांगap_clear(bmp->biपंचांगap, offset, num);
	spin_unlock_irqrestore(&bmp->lock, flags);
पूर्ण
EXPORT_SYMBOL(msi_biपंचांगap_मुक्त_hwirqs);

व्योम msi_biपंचांगap_reserve_hwirq(काष्ठा msi_biपंचांगap *bmp, अचिन्हित पूर्णांक hwirq)
अणु
	अचिन्हित दीर्घ flags;

	pr_debug("msi_bitmap: reserving hwirq 0x%x\n", hwirq);

	spin_lock_irqsave(&bmp->lock, flags);
	biपंचांगap_allocate_region(bmp->biपंचांगap, hwirq, 0);
	spin_unlock_irqrestore(&bmp->lock, flags);
पूर्ण

/**
 * msi_biपंचांगap_reserve_dt_hwirqs - Reserve irqs specअगरied in the device tree.
 * @bmp: poपूर्णांकer to the MSI biपंचांगap.
 *
 * Looks in the device tree to see अगर there is a property specअगरying which
 * irqs can be used क्रम MSI. If found those irqs reserved in the device tree
 * are reserved in the biपंचांगap.
 *
 * Returns 0 क्रम success, < 0 अगर there was an error, and > 0 अगर no property
 * was found in the device tree.
 **/
पूर्णांक msi_biपंचांगap_reserve_dt_hwirqs(काष्ठा msi_biपंचांगap *bmp)
अणु
	पूर्णांक i, j, len;
	स्थिर u32 *p;

	अगर (!bmp->of_node)
		वापस 1;

	p = of_get_property(bmp->of_node, "msi-available-ranges", &len);
	अगर (!p) अणु
		pr_debug("msi_bitmap: no msi-available-ranges property " \
			 "found on %pOF\n", bmp->of_node);
		वापस 1;
	पूर्ण

	अगर (len % (2 * माप(u32)) != 0) अणु
		prपूर्णांकk(KERN_WARNING "msi_bitmap: Malformed msi-available-ranges"
		       " property on %pOF\n", bmp->of_node);
		वापस -EINVAL;
	पूर्ण

	biपंचांगap_allocate_region(bmp->biपंचांगap, 0, get_count_order(bmp->irq_count));

	spin_lock(&bmp->lock);

	/* Format is: (<u32 start> <u32 count>)+ */
	len /= 2 * माप(u32);
	क्रम (i = 0; i < len; i++, p += 2) अणु
		क्रम (j = 0; j < *(p + 1); j++)
			biपंचांगap_release_region(bmp->biपंचांगap, *p + j, 0);
	पूर्ण

	spin_unlock(&bmp->lock);

	वापस 0;
पूर्ण

पूर्णांक __ref msi_biपंचांगap_alloc(काष्ठा msi_biपंचांगap *bmp, अचिन्हित पूर्णांक irq_count,
		     काष्ठा device_node *of_node)
अणु
	पूर्णांक size;

	अगर (!irq_count)
		वापस -EINVAL;

	size = BITS_TO_LONGS(irq_count) * माप(दीर्घ);
	pr_debug("msi_bitmap: allocator bitmap size is 0x%x bytes\n", size);

	bmp->biपंचांगap_from_slab = slab_is_available();
	अगर (bmp->biपंचांगap_from_slab)
		bmp->biपंचांगap = kzalloc(size, GFP_KERNEL);
	अन्यथा अणु
		bmp->biपंचांगap = memblock_alloc(size, SMP_CACHE_BYTES);
		अगर (!bmp->biपंचांगap)
			panic("%s: Failed to allocate %u bytes\n", __func__,
			      size);
		/* the biपंचांगap won't be मुक्तd from memblock allocator */
		kmemleak_not_leak(bmp->biपंचांगap);
	पूर्ण

	अगर (!bmp->biपंचांगap) अणु
		pr_debug("msi_bitmap: ENOMEM allocating allocator bitmap!\n");
		वापस -ENOMEM;
	पूर्ण

	/* We zalloc'ed the biपंचांगap, so all irqs are मुक्त by शेष */
	spin_lock_init(&bmp->lock);
	bmp->of_node = of_node_get(of_node);
	bmp->irq_count = irq_count;

	वापस 0;
पूर्ण

व्योम msi_biपंचांगap_मुक्त(काष्ठा msi_biपंचांगap *bmp)
अणु
	अगर (bmp->biपंचांगap_from_slab)
		kमुक्त(bmp->biपंचांगap);
	of_node_put(bmp->of_node);
	bmp->biपंचांगap = शून्य;
पूर्ण

#अगर_घोषित CONFIG_MSI_BITMAP_SELFTEST

अटल व्योम __init test_basics(व्योम)
अणु
	काष्ठा msi_biपंचांगap bmp;
	पूर्णांक rc, i, size = 512;

	/* Can't allocate a biपंचांगap of 0 irqs */
	WARN_ON(msi_biपंचांगap_alloc(&bmp, 0, शून्य) == 0);

	/* of_node may be शून्य */
	WARN_ON(msi_biपंचांगap_alloc(&bmp, size, शून्य));

	/* Should all be मुक्त by शेष */
	WARN_ON(biपंचांगap_find_मुक्त_region(bmp.biपंचांगap, size, get_count_order(size)));
	biपंचांगap_release_region(bmp.biपंचांगap, 0, get_count_order(size));

	/* With no node, there's no msi-available-ranges, so expect > 0 */
	WARN_ON(msi_biपंचांगap_reserve_dt_hwirqs(&bmp) <= 0);

	/* Should all still be मुक्त */
	WARN_ON(biपंचांगap_find_मुक्त_region(bmp.biपंचांगap, size, get_count_order(size)));
	biपंचांगap_release_region(bmp.biपंचांगap, 0, get_count_order(size));

	/* Check we can fill it up and then no more */
	क्रम (i = 0; i < size; i++)
		WARN_ON(msi_biपंचांगap_alloc_hwirqs(&bmp, 1) < 0);

	WARN_ON(msi_biपंचांगap_alloc_hwirqs(&bmp, 1) >= 0);

	/* Should all be allocated */
	WARN_ON(biपंचांगap_find_मुक्त_region(bmp.biपंचांगap, size, 0) >= 0);

	/* And अगर we मुक्त one we can then allocate another */
	msi_biपंचांगap_मुक्त_hwirqs(&bmp, size / 2, 1);
	WARN_ON(msi_biपंचांगap_alloc_hwirqs(&bmp, 1) != size / 2);

	/* Free most of them क्रम the alignment tests */
	msi_biपंचांगap_मुक्त_hwirqs(&bmp, 3, size - 3);

	/* Check we get a naturally aligned offset */
	rc = msi_biपंचांगap_alloc_hwirqs(&bmp, 2);
	WARN_ON(rc < 0 && rc % 2 != 0);
	rc = msi_biपंचांगap_alloc_hwirqs(&bmp, 4);
	WARN_ON(rc < 0 && rc % 4 != 0);
	rc = msi_biपंचांगap_alloc_hwirqs(&bmp, 8);
	WARN_ON(rc < 0 && rc % 8 != 0);
	rc = msi_biपंचांगap_alloc_hwirqs(&bmp, 9);
	WARN_ON(rc < 0 && rc % 16 != 0);
	rc = msi_biपंचांगap_alloc_hwirqs(&bmp, 3);
	WARN_ON(rc < 0 && rc % 4 != 0);
	rc = msi_biपंचांगap_alloc_hwirqs(&bmp, 7);
	WARN_ON(rc < 0 && rc % 8 != 0);
	rc = msi_biपंचांगap_alloc_hwirqs(&bmp, 121);
	WARN_ON(rc < 0 && rc % 128 != 0);

	msi_biपंचांगap_मुक्त(&bmp);

	/* Clients may WARN_ON biपंचांगap == शून्य क्रम "not-allocated" */
	WARN_ON(bmp.biपंचांगap != शून्य);
पूर्ण

अटल व्योम __init test_of_node(व्योम)
अणु
	u32 prop_data[] = अणु 10, 10, 25, 3, 40, 1, 100, 100, 200, 20 पूर्ण;
	स्थिर अक्षर *expected_str = "0-9,20-24,28-39,41-99,220-255";
	अक्षर *prop_name = "msi-available-ranges";
	अक्षर *node_name = "/fakenode";
	काष्ठा device_node of_node;
	काष्ठा property prop;
	काष्ठा msi_biपंचांगap bmp;
#घोषणा SIZE_EXPECTED 256
	DECLARE_BITMAP(expected, SIZE_EXPECTED);

	/* There should really be a काष्ठा device_node allocator */
	स_रखो(&of_node, 0, माप(of_node));
	of_node_init(&of_node);
	of_node.full_name = node_name;

	WARN_ON(msi_biपंचांगap_alloc(&bmp, SIZE_EXPECTED, &of_node));

	/* No msi-available-ranges, so expect > 0 */
	WARN_ON(msi_biपंचांगap_reserve_dt_hwirqs(&bmp) <= 0);

	/* Should all still be मुक्त */
	WARN_ON(biपंचांगap_find_मुक्त_region(bmp.biपंचांगap, SIZE_EXPECTED,
					get_count_order(SIZE_EXPECTED)));
	biपंचांगap_release_region(bmp.biपंचांगap, 0, get_count_order(SIZE_EXPECTED));

	/* Now create a fake msi-available-ranges property */

	/* There should really .. oh whatever */
	स_रखो(&prop, 0, माप(prop));
	prop.name = prop_name;
	prop.value = &prop_data;
	prop.length = माप(prop_data);

	of_node.properties = &prop;

	/* msi-available-ranges, so expect == 0 */
	WARN_ON(msi_biपंचांगap_reserve_dt_hwirqs(&bmp));

	/* Check we got the expected result */
	WARN_ON(biपंचांगap_parselist(expected_str, expected, SIZE_EXPECTED));
	WARN_ON(!biपंचांगap_equal(expected, bmp.biपंचांगap, SIZE_EXPECTED));

	msi_biपंचांगap_मुक्त(&bmp);
	kमुक्त(bmp.biपंचांगap);
पूर्ण

अटल पूर्णांक __init msi_biपंचांगap_selftest(व्योम)
अणु
	prपूर्णांकk(KERN_DEBUG "Running MSI bitmap self-tests ...\n");

	test_basics();
	test_of_node();

	वापस 0;
पूर्ण
late_initcall(msi_biपंचांगap_selftest);
#पूर्ण_अगर /* CONFIG_MSI_BITMAP_SELFTEST */
