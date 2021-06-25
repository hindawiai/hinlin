<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Generic on-chip SRAM allocation driver
 *
 * Copyright (C) 2012 Philipp Zabel, Pengutronix
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/पन.स>
#समावेश <linux/list_sort.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <soc/at91/aपंचांगel-secumod.h>

#समावेश "sram.h"

#घोषणा SRAM_GRANULARITY	32

अटल sमाप_प्रकार sram_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			 काष्ठा bin_attribute *attr,
			 अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	काष्ठा sram_partition *part;

	part = container_of(attr, काष्ठा sram_partition, battr);

	mutex_lock(&part->lock);
	स_नकल_fromio(buf, part->base + pos, count);
	mutex_unlock(&part->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार sram_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			  काष्ठा bin_attribute *attr,
			  अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	काष्ठा sram_partition *part;

	part = container_of(attr, काष्ठा sram_partition, battr);

	mutex_lock(&part->lock);
	स_नकल_toio(part->base + pos, buf, count);
	mutex_unlock(&part->lock);

	वापस count;
पूर्ण

अटल पूर्णांक sram_add_pool(काष्ठा sram_dev *sram, काष्ठा sram_reserve *block,
			 phys_addr_t start, काष्ठा sram_partition *part)
अणु
	पूर्णांक ret;

	part->pool = devm_gen_pool_create(sram->dev, ilog2(SRAM_GRANULARITY),
					  NUMA_NO_NODE, block->label);
	अगर (IS_ERR(part->pool))
		वापस PTR_ERR(part->pool);

	ret = gen_pool_add_virt(part->pool, (अचिन्हित दीर्घ)part->base, start,
				block->size, NUMA_NO_NODE);
	अगर (ret < 0) अणु
		dev_err(sram->dev, "failed to register subpool: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sram_add_export(काष्ठा sram_dev *sram, काष्ठा sram_reserve *block,
			   phys_addr_t start, काष्ठा sram_partition *part)
अणु
	sysfs_bin_attr_init(&part->battr);
	part->battr.attr.name = devm_kaप्र_लिखो(sram->dev, GFP_KERNEL,
					       "%llx.sram",
					       (अचिन्हित दीर्घ दीर्घ)start);
	अगर (!part->battr.attr.name)
		वापस -ENOMEM;

	part->battr.attr.mode = S_IRUSR | S_IWUSR;
	part->battr.पढ़ो = sram_पढ़ो;
	part->battr.ग_लिखो = sram_ग_लिखो;
	part->battr.size = block->size;

	वापस device_create_bin_file(sram->dev, &part->battr);
पूर्ण

अटल पूर्णांक sram_add_partition(काष्ठा sram_dev *sram, काष्ठा sram_reserve *block,
			      phys_addr_t start)
अणु
	पूर्णांक ret;
	काष्ठा sram_partition *part = &sram->partition[sram->partitions];

	mutex_init(&part->lock);
	part->base = sram->virt_base + block->start;

	अगर (block->pool) अणु
		ret = sram_add_pool(sram, block, start, part);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (block->export) अणु
		ret = sram_add_export(sram, block, start, part);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (block->protect_exec) अणु
		ret = sram_check_protect_exec(sram, block, part);
		अगर (ret)
			वापस ret;

		ret = sram_add_pool(sram, block, start, part);
		अगर (ret)
			वापस ret;

		sram_add_protect_exec(part);
	पूर्ण

	sram->partitions++;

	वापस 0;
पूर्ण

अटल व्योम sram_मुक्त_partitions(काष्ठा sram_dev *sram)
अणु
	काष्ठा sram_partition *part;

	अगर (!sram->partitions)
		वापस;

	part = &sram->partition[sram->partitions - 1];
	क्रम (; sram->partitions; sram->partitions--, part--) अणु
		अगर (part->battr.size)
			device_हटाओ_bin_file(sram->dev, &part->battr);

		अगर (part->pool &&
		    gen_pool_avail(part->pool) < gen_pool_size(part->pool))
			dev_err(sram->dev, "removed pool while SRAM allocated\n");
	पूर्ण
पूर्ण

अटल पूर्णांक sram_reserve_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
					स्थिर काष्ठा list_head *b)
अणु
	काष्ठा sram_reserve *ra = list_entry(a, काष्ठा sram_reserve, list);
	काष्ठा sram_reserve *rb = list_entry(b, काष्ठा sram_reserve, list);

	वापस ra->start - rb->start;
पूर्ण

अटल पूर्णांक sram_reserve_regions(काष्ठा sram_dev *sram, काष्ठा resource *res)
अणु
	काष्ठा device_node *np = sram->dev->of_node, *child;
	अचिन्हित दीर्घ size, cur_start, cur_size;
	काष्ठा sram_reserve *rblocks, *block;
	काष्ठा list_head reserve_list;
	अचिन्हित पूर्णांक nblocks, exports = 0;
	स्थिर अक्षर *label;
	पूर्णांक ret = 0;

	INIT_LIST_HEAD(&reserve_list);

	size = resource_size(res);

	/*
	 * We need an additional block to mark the end of the memory region
	 * after the reserved blocks from the dt are processed.
	 */
	nblocks = (np) ? of_get_available_child_count(np) + 1 : 1;
	rblocks = kसुस्मृति(nblocks, माप(*rblocks), GFP_KERNEL);
	अगर (!rblocks)
		वापस -ENOMEM;

	block = &rblocks[0];
	क्रम_each_available_child_of_node(np, child) अणु
		काष्ठा resource child_res;

		ret = of_address_to_resource(child, 0, &child_res);
		अगर (ret < 0) अणु
			dev_err(sram->dev,
				"could not get address for node %pOF\n",
				child);
			जाओ err_chunks;
		पूर्ण

		अगर (child_res.start < res->start || child_res.end > res->end) अणु
			dev_err(sram->dev,
				"reserved block %pOF outside the sram area\n",
				child);
			ret = -EINVAL;
			जाओ err_chunks;
		पूर्ण

		block->start = child_res.start - res->start;
		block->size = resource_size(&child_res);
		list_add_tail(&block->list, &reserve_list);

		अगर (of_find_property(child, "export", शून्य))
			block->export = true;

		अगर (of_find_property(child, "pool", शून्य))
			block->pool = true;

		अगर (of_find_property(child, "protect-exec", शून्य))
			block->protect_exec = true;

		अगर ((block->export || block->pool || block->protect_exec) &&
		    block->size) अणु
			exports++;

			label = शून्य;
			ret = of_property_पढ़ो_string(child, "label", &label);
			अगर (ret && ret != -EINVAL) अणु
				dev_err(sram->dev,
					"%pOF has invalid label name\n",
					child);
				जाओ err_chunks;
			पूर्ण
			अगर (!label)
				label = child->name;

			block->label = devm_kstrdup(sram->dev,
						    label, GFP_KERNEL);
			अगर (!block->label) अणु
				ret = -ENOMEM;
				जाओ err_chunks;
			पूर्ण

			dev_dbg(sram->dev, "found %sblock '%s' 0x%x-0x%x\n",
				block->export ? "exported " : "", block->label,
				block->start, block->start + block->size);
		पूर्ण अन्यथा अणु
			dev_dbg(sram->dev, "found reserved block 0x%x-0x%x\n",
				block->start, block->start + block->size);
		पूर्ण

		block++;
	पूर्ण
	child = शून्य;

	/* the last chunk marks the end of the region */
	rblocks[nblocks - 1].start = size;
	rblocks[nblocks - 1].size = 0;
	list_add_tail(&rblocks[nblocks - 1].list, &reserve_list);

	list_sort(शून्य, &reserve_list, sram_reserve_cmp);

	अगर (exports) अणु
		sram->partition = devm_kसुस्मृति(sram->dev,
				       exports, माप(*sram->partition),
				       GFP_KERNEL);
		अगर (!sram->partition) अणु
			ret = -ENOMEM;
			जाओ err_chunks;
		पूर्ण
	पूर्ण

	cur_start = 0;
	list_क्रम_each_entry(block, &reserve_list, list) अणु
		/* can only happen अगर sections overlap */
		अगर (block->start < cur_start) अणु
			dev_err(sram->dev,
				"block at 0x%x starts after current offset 0x%lx\n",
				block->start, cur_start);
			ret = -EINVAL;
			sram_मुक्त_partitions(sram);
			जाओ err_chunks;
		पूर्ण

		अगर ((block->export || block->pool || block->protect_exec) &&
		    block->size) अणु
			ret = sram_add_partition(sram, block,
						 res->start + block->start);
			अगर (ret) अणु
				sram_मुक्त_partitions(sram);
				जाओ err_chunks;
			पूर्ण
		पूर्ण

		/* current start is in a reserved block, so जारी after it */
		अगर (block->start == cur_start) अणु
			cur_start = block->start + block->size;
			जारी;
		पूर्ण

		/*
		 * allocate the space between the current starting
		 * address and the following reserved block, or the
		 * end of the region.
		 */
		cur_size = block->start - cur_start;

		dev_dbg(sram->dev, "adding chunk 0x%lx-0x%lx\n",
			cur_start, cur_start + cur_size);

		ret = gen_pool_add_virt(sram->pool,
				(अचिन्हित दीर्घ)sram->virt_base + cur_start,
				res->start + cur_start, cur_size, -1);
		अगर (ret < 0) अणु
			sram_मुक्त_partitions(sram);
			जाओ err_chunks;
		पूर्ण

		/* next allocation after this reserved block */
		cur_start = block->start + block->size;
	पूर्ण

err_chunks:
	of_node_put(child);
	kमुक्त(rblocks);

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_securam_रुको(व्योम)
अणु
	काष्ठा regmap *regmap;
	u32 val;

	regmap = syscon_regmap_lookup_by_compatible("atmel,sama5d2-secumod");
	अगर (IS_ERR(regmap))
		वापस -ENODEV;

	वापस regmap_पढ़ो_poll_समयout(regmap, AT91_SECUMOD_RAMRDY, val,
					val & AT91_SECUMOD_RAMRDY_READY,
					10000, 500000);
पूर्ण

अटल स्थिर काष्ठा of_device_id sram_dt_ids[] = अणु
	अणु .compatible = "mmio-sram" पूर्ण,
	अणु .compatible = "atmel,sama5d2-securam", .data = aपंचांगel_securam_रुको पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक sram_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sram_dev *sram;
	पूर्णांक ret;
	पूर्णांक (*init_func)(व्योम);

	sram = devm_kzalloc(&pdev->dev, माप(*sram), GFP_KERNEL);
	अगर (!sram)
		वापस -ENOMEM;

	sram->dev = &pdev->dev;

	अगर (of_property_पढ़ो_bool(pdev->dev.of_node, "no-memory-wc"))
		sram->virt_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अन्यथा
		sram->virt_base = devm_platक्रमm_ioremap_resource_wc(pdev, 0);
	अगर (IS_ERR(sram->virt_base)) अणु
		dev_err(&pdev->dev, "could not map SRAM registers\n");
		वापस PTR_ERR(sram->virt_base);
	पूर्ण

	sram->pool = devm_gen_pool_create(sram->dev, ilog2(SRAM_GRANULARITY),
					  NUMA_NO_NODE, शून्य);
	अगर (IS_ERR(sram->pool))
		वापस PTR_ERR(sram->pool);

	sram->clk = devm_clk_get(sram->dev, शून्य);
	अगर (IS_ERR(sram->clk))
		sram->clk = शून्य;
	अन्यथा
		clk_prepare_enable(sram->clk);

	ret = sram_reserve_regions(sram,
			platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0));
	अगर (ret)
		जाओ err_disable_clk;

	platक्रमm_set_drvdata(pdev, sram);

	init_func = of_device_get_match_data(&pdev->dev);
	अगर (init_func) अणु
		ret = init_func();
		अगर (ret)
			जाओ err_मुक्त_partitions;
	पूर्ण

	dev_dbg(sram->dev, "SRAM pool: %zu KiB @ 0x%p\n",
		gen_pool_size(sram->pool) / 1024, sram->virt_base);

	वापस 0;

err_मुक्त_partitions:
	sram_मुक्त_partitions(sram);
err_disable_clk:
	अगर (sram->clk)
		clk_disable_unprepare(sram->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक sram_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sram_dev *sram = platक्रमm_get_drvdata(pdev);

	sram_मुक्त_partitions(sram);

	अगर (gen_pool_avail(sram->pool) < gen_pool_size(sram->pool))
		dev_err(sram->dev, "removed while SRAM allocated\n");

	अगर (sram->clk)
		clk_disable_unprepare(sram->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sram_driver = अणु
	.driver = अणु
		.name = "sram",
		.of_match_table = sram_dt_ids,
	पूर्ण,
	.probe = sram_probe,
	.हटाओ = sram_हटाओ,
पूर्ण;

अटल पूर्णांक __init sram_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sram_driver);
पूर्ण

postcore_initcall(sram_init);
