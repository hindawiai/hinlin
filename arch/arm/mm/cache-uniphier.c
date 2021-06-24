<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015-2016 Socionext Inc.
 *   Author: Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#घोषणा pr_fmt(fmt)		"uniphier: " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/log2.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/hardware/cache-uniphier.h>
#समावेश <यंत्र/outercache.h>

/* control रेजिस्टरs */
#घोषणा UNIPHIER_SSCC		0x0	/* Control Register */
#घोषणा    UNIPHIER_SSCC_BST			BIT(20)	/* UCWG burst पढ़ो */
#घोषणा    UNIPHIER_SSCC_ACT			BIT(19)	/* Inst-Data separate */
#घोषणा    UNIPHIER_SSCC_WTG			BIT(18)	/* WT gathering on */
#घोषणा    UNIPHIER_SSCC_PRD			BIT(17)	/* enable pre-fetch */
#घोषणा    UNIPHIER_SSCC_ON			BIT(0)	/* enable cache */
#घोषणा UNIPHIER_SSCLPDAWCR	0x30	/* Unअगरied/Data Active Way Control */
#घोषणा UNIPHIER_SSCLPIAWCR	0x34	/* Inकाष्ठाion Active Way Control */

/* revision रेजिस्टरs */
#घोषणा UNIPHIER_SSCID		0x0	/* ID Register */

/* operation रेजिस्टरs */
#घोषणा UNIPHIER_SSCOPE		0x244	/* Cache Operation Primitive Entry */
#घोषणा    UNIPHIER_SSCOPE_CM_INV		0x0	/* invalidate */
#घोषणा    UNIPHIER_SSCOPE_CM_CLEAN		0x1	/* clean */
#घोषणा    UNIPHIER_SSCOPE_CM_FLUSH		0x2	/* flush */
#घोषणा    UNIPHIER_SSCOPE_CM_SYNC		0x8	/* sync (drain bufs) */
#घोषणा    UNIPHIER_SSCOPE_CM_FLUSH_PREFETCH	0x9	/* flush p-fetch buf */
#घोषणा UNIPHIER_SSCOQM		0x248	/* Cache Operation Queue Mode */
#घोषणा    UNIPHIER_SSCOQM_S_MASK		(0x3 << 17)
#घोषणा    UNIPHIER_SSCOQM_S_RANGE		(0x0 << 17)
#घोषणा    UNIPHIER_SSCOQM_S_ALL		(0x1 << 17)
#घोषणा    UNIPHIER_SSCOQM_CE			BIT(15)	/* notअगरy completion */
#घोषणा    UNIPHIER_SSCOQM_CM_INV		0x0	/* invalidate */
#घोषणा    UNIPHIER_SSCOQM_CM_CLEAN		0x1	/* clean */
#घोषणा    UNIPHIER_SSCOQM_CM_FLUSH		0x2	/* flush */
#घोषणा UNIPHIER_SSCOQAD	0x24c	/* Cache Operation Queue Address */
#घोषणा UNIPHIER_SSCOQSZ	0x250	/* Cache Operation Queue Size */
#घोषणा UNIPHIER_SSCOPPQSEF	0x25c	/* Cache Operation Queue Set Complete*/
#घोषणा    UNIPHIER_SSCOPPQSEF_FE		BIT(1)
#घोषणा    UNIPHIER_SSCOPPQSEF_OE		BIT(0)
#घोषणा UNIPHIER_SSCOLPQS	0x260	/* Cache Operation Queue Status */
#घोषणा    UNIPHIER_SSCOLPQS_EF			BIT(2)
#घोषणा    UNIPHIER_SSCOLPQS_EST		BIT(1)
#घोषणा    UNIPHIER_SSCOLPQS_QST		BIT(0)

/* Is the operation region specअगरied by address range? */
#घोषणा UNIPHIER_SSCOQM_S_IS_RANGE(op) \
		((op & UNIPHIER_SSCOQM_S_MASK) == UNIPHIER_SSCOQM_S_RANGE)

/**
 * uniphier_cache_data - UniPhier outer cache specअगरic data
 *
 * @ctrl_base: भव base address of control रेजिस्टरs
 * @rev_base: भव base address of revision रेजिस्टरs
 * @op_base: भव base address of operation रेजिस्टरs
 * @way_mask: each bit specअगरies अगर the way is present
 * @nsets: number of associativity sets
 * @line_size: line size in bytes
 * @range_op_max_size: max size that can be handled by a single range operation
 * @list: list node to include this level in the whole cache hierarchy
 */
काष्ठा uniphier_cache_data अणु
	व्योम __iomem *ctrl_base;
	व्योम __iomem *rev_base;
	व्योम __iomem *op_base;
	व्योम __iomem *way_ctrl_base;
	u32 way_mask;
	u32 nsets;
	u32 line_size;
	u32 range_op_max_size;
	काष्ठा list_head list;
पूर्ण;

/*
 * List of the whole outer cache hierarchy.  This list is only modअगरied during
 * the early boot stage, so no mutex is taken क्रम the access to the list.
 */
अटल LIST_HEAD(uniphier_cache_list);

/**
 * __uniphier_cache_sync - perक्रमm a sync poपूर्णांक क्रम a particular cache level
 *
 * @data: cache controller specअगरic data
 */
अटल व्योम __uniphier_cache_sync(काष्ठा uniphier_cache_data *data)
अणु
	/* This sequence need not be atomic.  Do not disable IRQ. */
	ग_लिखोl_relaxed(UNIPHIER_SSCOPE_CM_SYNC,
		       data->op_base + UNIPHIER_SSCOPE);
	/* need a पढ़ो back to confirm */
	पढ़ोl_relaxed(data->op_base + UNIPHIER_SSCOPE);
पूर्ण

/**
 * __uniphier_cache_मुख्यt_common - run a queue operation क्रम a particular level
 *
 * @data: cache controller specअगरic data
 * @start: start address of range operation (करोn't care क्रम "all" operation)
 * @size: data size of range operation (करोn't care क्रम "all" operation)
 * @operation: flags to specअगरy the desired cache operation
 */
अटल व्योम __uniphier_cache_मुख्यt_common(काष्ठा uniphier_cache_data *data,
					  अचिन्हित दीर्घ start,
					  अचिन्हित दीर्घ size,
					  u32 operation)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * No spin lock is necessary here because:
	 *
	 * [1] This outer cache controller is able to accept मुख्यtenance
	 * operations from multiple CPUs at a समय in an SMP प्रणाली; अगर a
	 * मुख्यtenance operation is under way and another operation is issued,
	 * the new one is stored in the queue.  The controller perक्रमms one
	 * operation after another.  If the queue is full, the status रेजिस्टर,
	 * UNIPHIER_SSCOPPQSEF, indicates that the queue registration has
	 * failed.  The status रेजिस्टरs, UNIPHIER_अणुSSCOPPQSEF, SSCOLPQSपूर्ण, have
	 * dअगरferent instances क्रम each CPU, i.e. each CPU can track the status
	 * of the मुख्यtenance operations triggered by itself.
	 *
	 * [2] The cache command रेजिस्टरs, UNIPHIER_अणुSSCOQM, SSCOQAD, SSCOQSZ,
	 * SSCOQWNपूर्ण, are shared between multiple CPUs, but the hardware still
	 * guarantees the registration sequence is atomic; the ग_लिखो access to
	 * them are arbitrated by the hardware.  The first accessor to the
	 * रेजिस्टर, UNIPHIER_SSCOQM, holds the access right and it is released
	 * by पढ़ोing the status रेजिस्टर, UNIPHIER_SSCOPPQSEF.  While one CPU
	 * is holding the access right, other CPUs fail to रेजिस्टर operations.
	 * One CPU should not hold the access right क्रम a दीर्घ समय, so local
	 * IRQs should be disabled जबतक the following sequence.
	 */
	local_irq_save(flags);

	/* clear the complete notअगरication flag */
	ग_लिखोl_relaxed(UNIPHIER_SSCOLPQS_EF, data->op_base + UNIPHIER_SSCOLPQS);

	करो अणु
		/* set cache operation */
		ग_लिखोl_relaxed(UNIPHIER_SSCOQM_CE | operation,
			       data->op_base + UNIPHIER_SSCOQM);

		/* set address range अगर needed */
		अगर (likely(UNIPHIER_SSCOQM_S_IS_RANGE(operation))) अणु
			ग_लिखोl_relaxed(start, data->op_base + UNIPHIER_SSCOQAD);
			ग_लिखोl_relaxed(size, data->op_base + UNIPHIER_SSCOQSZ);
		पूर्ण
	पूर्ण जबतक (unlikely(पढ़ोl_relaxed(data->op_base + UNIPHIER_SSCOPPQSEF) &
			  (UNIPHIER_SSCOPPQSEF_FE | UNIPHIER_SSCOPPQSEF_OE)));

	/* रुको until the operation is completed */
	जबतक (likely(पढ़ोl_relaxed(data->op_base + UNIPHIER_SSCOLPQS) !=
		      UNIPHIER_SSCOLPQS_EF))
		cpu_relax();

	local_irq_restore(flags);
पूर्ण

अटल व्योम __uniphier_cache_मुख्यt_all(काष्ठा uniphier_cache_data *data,
				       u32 operation)
अणु
	__uniphier_cache_मुख्यt_common(data, 0, 0,
				      UNIPHIER_SSCOQM_S_ALL | operation);

	__uniphier_cache_sync(data);
पूर्ण

अटल व्योम __uniphier_cache_मुख्यt_range(काष्ठा uniphier_cache_data *data,
					 अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
					 u32 operation)
अणु
	अचिन्हित दीर्घ size;

	/*
	 * If the start address is not aligned,
	 * perक्रमm a cache operation क्रम the first cache-line
	 */
	start = start & ~(data->line_size - 1);

	size = end - start;

	अगर (unlikely(size >= (अचिन्हित दीर्घ)(-data->line_size))) अणु
		/* this means cache operation क्रम all range */
		__uniphier_cache_मुख्यt_all(data, operation);
		वापस;
	पूर्ण

	/*
	 * If the end address is not aligned,
	 * perक्रमm a cache operation क्रम the last cache-line
	 */
	size = ALIGN(size, data->line_size);

	जबतक (size) अणु
		अचिन्हित दीर्घ chunk_size = min_t(अचिन्हित दीर्घ, size,
						 data->range_op_max_size);

		__uniphier_cache_मुख्यt_common(data, start, chunk_size,
					UNIPHIER_SSCOQM_S_RANGE | operation);

		start += chunk_size;
		size -= chunk_size;
	पूर्ण

	__uniphier_cache_sync(data);
पूर्ण

अटल व्योम __uniphier_cache_enable(काष्ठा uniphier_cache_data *data, bool on)
अणु
	u32 val = 0;

	अगर (on)
		val = UNIPHIER_SSCC_WTG | UNIPHIER_SSCC_PRD | UNIPHIER_SSCC_ON;

	ग_लिखोl_relaxed(val, data->ctrl_base + UNIPHIER_SSCC);
पूर्ण

अटल व्योम __init __uniphier_cache_set_active_ways(
					काष्ठा uniphier_cache_data *data)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		ग_लिखोl_relaxed(data->way_mask, data->way_ctrl_base + 4 * cpu);
पूर्ण

अटल व्योम uniphier_cache_मुख्यt_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				       u32 operation)
अणु
	काष्ठा uniphier_cache_data *data;

	list_क्रम_each_entry(data, &uniphier_cache_list, list)
		__uniphier_cache_मुख्यt_range(data, start, end, operation);
पूर्ण

अटल व्योम uniphier_cache_मुख्यt_all(u32 operation)
अणु
	काष्ठा uniphier_cache_data *data;

	list_क्रम_each_entry(data, &uniphier_cache_list, list)
		__uniphier_cache_मुख्यt_all(data, operation);
पूर्ण

अटल व्योम uniphier_cache_inv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	uniphier_cache_मुख्यt_range(start, end, UNIPHIER_SSCOQM_CM_INV);
पूर्ण

अटल व्योम uniphier_cache_clean_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	uniphier_cache_मुख्यt_range(start, end, UNIPHIER_SSCOQM_CM_CLEAN);
पूर्ण

अटल व्योम uniphier_cache_flush_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	uniphier_cache_मुख्यt_range(start, end, UNIPHIER_SSCOQM_CM_FLUSH);
पूर्ण

अटल व्योम __init uniphier_cache_inv_all(व्योम)
अणु
	uniphier_cache_मुख्यt_all(UNIPHIER_SSCOQM_CM_INV);
पूर्ण

अटल व्योम uniphier_cache_flush_all(व्योम)
अणु
	uniphier_cache_मुख्यt_all(UNIPHIER_SSCOQM_CM_FLUSH);
पूर्ण

अटल व्योम uniphier_cache_disable(व्योम)
अणु
	काष्ठा uniphier_cache_data *data;

	list_क्रम_each_entry_reverse(data, &uniphier_cache_list, list)
		__uniphier_cache_enable(data, false);

	uniphier_cache_flush_all();
पूर्ण

अटल व्योम __init uniphier_cache_enable(व्योम)
अणु
	काष्ठा uniphier_cache_data *data;

	uniphier_cache_inv_all();

	list_क्रम_each_entry(data, &uniphier_cache_list, list) अणु
		__uniphier_cache_enable(data, true);
		__uniphier_cache_set_active_ways(data);
	पूर्ण
पूर्ण

अटल व्योम uniphier_cache_sync(व्योम)
अणु
	काष्ठा uniphier_cache_data *data;

	list_क्रम_each_entry(data, &uniphier_cache_list, list)
		__uniphier_cache_sync(data);
पूर्ण

अटल स्थिर काष्ठा of_device_id uniphier_cache_match[] __initस्थिर = अणु
	अणु .compatible = "socionext,uniphier-system-cache" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक __init __uniphier_cache_init(काष्ठा device_node *np,
					अचिन्हित पूर्णांक *cache_level)
अणु
	काष्ठा uniphier_cache_data *data;
	u32 level, cache_size;
	काष्ठा device_node *next_np;
	पूर्णांक ret = 0;

	अगर (!of_match_node(uniphier_cache_match, np)) अणु
		pr_err("L%d: not compatible with uniphier cache\n",
		       *cache_level);
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cache-level", &level)) अणु
		pr_err("L%d: cache-level is not specified\n", *cache_level);
		वापस -EINVAL;
	पूर्ण

	अगर (level != *cache_level) अणु
		pr_err("L%d: cache-level is unexpected value %d\n",
		       *cache_level, level);
		वापस -EINVAL;
	पूर्ण

	अगर (!of_property_पढ़ो_bool(np, "cache-unified")) अणु
		pr_err("L%d: cache-unified is not specified\n", *cache_level);
		वापस -EINVAL;
	पूर्ण

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	अगर (of_property_पढ़ो_u32(np, "cache-line-size", &data->line_size) ||
	    !is_घातer_of_2(data->line_size)) अणु
		pr_err("L%d: cache-line-size is unspecified or invalid\n",
		       *cache_level);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cache-sets", &data->nsets) ||
	    !is_घातer_of_2(data->nsets)) अणु
		pr_err("L%d: cache-sets is unspecified or invalid\n",
		       *cache_level);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cache-size", &cache_size) ||
	    cache_size == 0 || cache_size % (data->nsets * data->line_size)) अणु
		pr_err("L%d: cache-size is unspecified or invalid\n",
		       *cache_level);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	data->way_mask = GENMASK(cache_size / data->nsets / data->line_size - 1,
				 0);

	data->ctrl_base = of_iomap(np, 0);
	अगर (!data->ctrl_base) अणु
		pr_err("L%d: failed to map control register\n", *cache_level);
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	data->rev_base = of_iomap(np, 1);
	अगर (!data->rev_base) अणु
		pr_err("L%d: failed to map revision register\n", *cache_level);
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	data->op_base = of_iomap(np, 2);
	अगर (!data->op_base) अणु
		pr_err("L%d: failed to map operation register\n", *cache_level);
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	data->way_ctrl_base = data->ctrl_base + 0xc00;

	अगर (*cache_level == 2) अणु
		u32 revision = पढ़ोl(data->rev_base + UNIPHIER_SSCID);
		/*
		 * The size of range operation is limited to (1 << 22) or less
		 * क्रम PH-sLD8 or older SoCs.
		 */
		अगर (revision <= 0x16)
			data->range_op_max_size = (u32)1 << 22;

		/*
		 * Unक्रमtunatly, the offset address of active way control base
		 * varies from SoC to SoC.
		 */
		चयन (revision) अणु
		हाल 0x11:	/* sLD3 */
			data->way_ctrl_base = data->ctrl_base + 0x870;
			अवरोध;
		हाल 0x12:	/* LD4 */
		हाल 0x16:	/* sld8 */
			data->way_ctrl_base = data->ctrl_base + 0x840;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	data->range_op_max_size -= data->line_size;

	INIT_LIST_HEAD(&data->list);
	list_add_tail(&data->list, &uniphier_cache_list); /* no mutex */

	/*
	 * OK, this level has been successfully initialized.  Look क्रम the next
	 * level cache.  Do not roll back even अगर the initialization of the
	 * next level cache fails because we want to जारी with available
	 * cache levels.
	 */
	next_np = of_find_next_cache_node(np);
	अगर (next_np) अणु
		(*cache_level)++;
		ret = __uniphier_cache_init(next_np, cache_level);
	पूर्ण
	of_node_put(next_np);

	वापस ret;
err:
	iounmap(data->op_base);
	iounmap(data->rev_base);
	iounmap(data->ctrl_base);
	kमुक्त(data);

	वापस ret;
पूर्ण

पूर्णांक __init uniphier_cache_init(व्योम)
अणु
	काष्ठा device_node *np = शून्य;
	अचिन्हित पूर्णांक cache_level;
	पूर्णांक ret = 0;

	/* look क्रम level 2 cache */
	जबतक ((np = of_find_matching_node(np, uniphier_cache_match)))
		अगर (!of_property_पढ़ो_u32(np, "cache-level", &cache_level) &&
		    cache_level == 2)
			अवरोध;

	अगर (!np)
		वापस -ENODEV;

	ret = __uniphier_cache_init(np, &cache_level);
	of_node_put(np);

	अगर (ret) अणु
		/*
		 * Error out iअगर L2 initialization fails.  Continue with any
		 * error on L3 or outer because they are optional.
		 */
		अगर (cache_level == 2) अणु
			pr_err("failed to initialize L2 cache\n");
			वापस ret;
		पूर्ण

		cache_level--;
		ret = 0;
	पूर्ण

	outer_cache.inv_range = uniphier_cache_inv_range;
	outer_cache.clean_range = uniphier_cache_clean_range;
	outer_cache.flush_range = uniphier_cache_flush_range;
	outer_cache.flush_all = uniphier_cache_flush_all;
	outer_cache.disable = uniphier_cache_disable;
	outer_cache.sync = uniphier_cache_sync;

	uniphier_cache_enable();

	pr_info("enabled outer cache (cache level: %d)\n", cache_level);

	वापस ret;
पूर्ण
