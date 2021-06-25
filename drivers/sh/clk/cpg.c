<शैली गुरु>
/*
 * Helper routines क्रम SuperH Clock Pulse Generator blocks (CPG).
 *
 *  Copyright (C) 2010  Magnus Damm
 *  Copyright (C) 2010 - 2012  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/clk.h>
#समावेश <linux/compiler.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/sh_clk.h>

#घोषणा CPG_CKSTP_BIT	BIT(8)

अटल अचिन्हित पूर्णांक sh_clk_पढ़ो(काष्ठा clk *clk)
अणु
	अगर (clk->flags & CLK_ENABLE_REG_8BIT)
		वापस ioपढ़ो8(clk->mapped_reg);
	अन्यथा अगर (clk->flags & CLK_ENABLE_REG_16BIT)
		वापस ioपढ़ो16(clk->mapped_reg);

	वापस ioपढ़ो32(clk->mapped_reg);
पूर्ण

अटल व्योम sh_clk_ग_लिखो(पूर्णांक value, काष्ठा clk *clk)
अणु
	अगर (clk->flags & CLK_ENABLE_REG_8BIT)
		ioग_लिखो8(value, clk->mapped_reg);
	अन्यथा अगर (clk->flags & CLK_ENABLE_REG_16BIT)
		ioग_लिखो16(value, clk->mapped_reg);
	अन्यथा
		ioग_लिखो32(value, clk->mapped_reg);
पूर्ण

अटल पूर्णांक sh_clk_mstp_enable(काष्ठा clk *clk)
अणु
	sh_clk_ग_लिखो(sh_clk_पढ़ो(clk) & ~(1 << clk->enable_bit), clk);
	अगर (clk->status_reg) अणु
		अचिन्हित पूर्णांक (*पढ़ो)(स्थिर व्योम __iomem *addr);
		पूर्णांक i;
		व्योम __iomem *mapped_status = (phys_addr_t)clk->status_reg -
			(phys_addr_t)clk->enable_reg + clk->mapped_reg;

		अगर (clk->flags & CLK_ENABLE_REG_8BIT)
			पढ़ो = ioपढ़ो8;
		अन्यथा अगर (clk->flags & CLK_ENABLE_REG_16BIT)
			पढ़ो = ioपढ़ो16;
		अन्यथा
			पढ़ो = ioपढ़ो32;

		क्रम (i = 1000;
		     (पढ़ो(mapped_status) & (1 << clk->enable_bit)) && i;
		     i--)
			cpu_relax();
		अगर (!i) अणु
			pr_err("cpg: failed to enable %p[%d]\n",
			       clk->enable_reg, clk->enable_bit);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sh_clk_mstp_disable(काष्ठा clk *clk)
अणु
	sh_clk_ग_लिखो(sh_clk_पढ़ो(clk) | (1 << clk->enable_bit), clk);
पूर्ण

अटल काष्ठा sh_clk_ops sh_clk_mstp_clk_ops = अणु
	.enable		= sh_clk_mstp_enable,
	.disable	= sh_clk_mstp_disable,
	.recalc		= followparent_recalc,
पूर्ण;

पूर्णांक __init sh_clk_mstp_रेजिस्टर(काष्ठा clk *clks, पूर्णांक nr)
अणु
	काष्ठा clk *clkp;
	पूर्णांक ret = 0;
	पूर्णांक k;

	क्रम (k = 0; !ret && (k < nr); k++) अणु
		clkp = clks + k;
		clkp->ops = &sh_clk_mstp_clk_ops;
		ret |= clk_रेजिस्टर(clkp);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Div/mult table lookup helpers
 */
अटल अंतरभूत काष्ठा clk_भाग_प्रकारable *clk_to_भाग_प्रकारable(काष्ठा clk *clk)
अणु
	वापस clk->priv;
पूर्ण

अटल अंतरभूत काष्ठा clk_भाग_mult_table *clk_to_भाग_mult_table(काष्ठा clk *clk)
अणु
	वापस clk_to_भाग_प्रकारable(clk)->भाग_mult_table;
पूर्ण

/*
 * Common भाग ops
 */
अटल दीर्घ sh_clk_भाग_round_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	वापस clk_rate_table_round(clk, clk->freq_table, rate);
पूर्ण

अटल अचिन्हित दीर्घ sh_clk_भाग_recalc(काष्ठा clk *clk)
अणु
	काष्ठा clk_भाग_mult_table *table = clk_to_भाग_mult_table(clk);
	अचिन्हित पूर्णांक idx;

	clk_rate_table_build(clk, clk->freq_table, table->nr_भागisors,
			     table, clk->arch_flags ? &clk->arch_flags : शून्य);

	idx = (sh_clk_पढ़ो(clk) >> clk->enable_bit) & clk->भाग_mask;

	वापस clk->freq_table[idx].frequency;
पूर्ण

अटल पूर्णांक sh_clk_भाग_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk_भाग_प्रकारable *dt = clk_to_भाग_प्रकारable(clk);
	अचिन्हित दीर्घ value;
	पूर्णांक idx;

	idx = clk_rate_table_find(clk, clk->freq_table, rate);
	अगर (idx < 0)
		वापस idx;

	value = sh_clk_पढ़ो(clk);
	value &= ~(clk->भाग_mask << clk->enable_bit);
	value |= (idx << clk->enable_bit);
	sh_clk_ग_लिखो(value, clk);

	/* XXX: Should use a post-change notअगरier */
	अगर (dt->kick)
		dt->kick(clk);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_clk_भाग_enable(काष्ठा clk *clk)
अणु
	अगर (clk->भाग_mask == SH_CLK_DIV6_MSK) अणु
		पूर्णांक ret = sh_clk_भाग_set_rate(clk, clk->rate);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	sh_clk_ग_लिखो(sh_clk_पढ़ो(clk) & ~CPG_CKSTP_BIT, clk);
	वापस 0;
पूर्ण

अटल व्योम sh_clk_भाग_disable(काष्ठा clk *clk)
अणु
	अचिन्हित पूर्णांक val;

	val = sh_clk_पढ़ो(clk);
	val |= CPG_CKSTP_BIT;

	/*
	 * भाग6 घड़ीs require the भागisor field to be non-zero or the
	 * above CKSTP toggle silently fails. Ensure that the भागisor
	 * array is reset to its initial state on disable.
	 */
	अगर (clk->flags & CLK_MASK_DIV_ON_DISABLE)
		val |= clk->भाग_mask;

	sh_clk_ग_लिखो(val, clk);
पूर्ण

अटल काष्ठा sh_clk_ops sh_clk_भाग_clk_ops = अणु
	.recalc		= sh_clk_भाग_recalc,
	.set_rate	= sh_clk_भाग_set_rate,
	.round_rate	= sh_clk_भाग_round_rate,
पूर्ण;

अटल काष्ठा sh_clk_ops sh_clk_भाग_enable_clk_ops = अणु
	.recalc		= sh_clk_भाग_recalc,
	.set_rate	= sh_clk_भाग_set_rate,
	.round_rate	= sh_clk_भाग_round_rate,
	.enable		= sh_clk_भाग_enable,
	.disable	= sh_clk_भाग_disable,
पूर्ण;

अटल पूर्णांक __init sh_clk_init_parent(काष्ठा clk *clk)
अणु
	u32 val;

	अगर (clk->parent)
		वापस 0;

	अगर (!clk->parent_table || !clk->parent_num)
		वापस 0;

	अगर (!clk->src_width) अणु
		pr_err("sh_clk_init_parent: cannot select parent clock\n");
		वापस -EINVAL;
	पूर्ण

	val  = (sh_clk_पढ़ो(clk) >> clk->src_shअगरt);
	val &= (1 << clk->src_width) - 1;

	अगर (val >= clk->parent_num) अणु
		pr_err("sh_clk_init_parent: parent table size failed\n");
		वापस -EINVAL;
	पूर्ण

	clk_reparent(clk, clk->parent_table[val]);
	अगर (!clk->parent) अणु
		pr_err("sh_clk_init_parent: unable to set parent");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init sh_clk_भाग_रेजिस्टर_ops(काष्ठा clk *clks, पूर्णांक nr,
			काष्ठा clk_भाग_प्रकारable *table, काष्ठा sh_clk_ops *ops)
अणु
	काष्ठा clk *clkp;
	व्योम *freq_table;
	पूर्णांक nr_भागs = table->भाग_mult_table->nr_भागisors;
	पूर्णांक freq_table_size = माप(काष्ठा cpufreq_frequency_table);
	पूर्णांक ret = 0;
	पूर्णांक k;

	freq_table_size *= (nr_भागs + 1);
	freq_table = kसुस्मृति(nr, freq_table_size, GFP_KERNEL);
	अगर (!freq_table) अणु
		pr_err("%s: unable to alloc memory\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	क्रम (k = 0; !ret && (k < nr); k++) अणु
		clkp = clks + k;

		clkp->ops = ops;
		clkp->priv = table;

		clkp->freq_table = freq_table + (k * freq_table_size);
		clkp->freq_table[nr_भागs].frequency = CPUFREQ_TABLE_END;

		ret = clk_रेजिस्टर(clkp);
		अगर (ret == 0)
			ret = sh_clk_init_parent(clkp);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * भाग6 support
 */
अटल पूर्णांक sh_clk_भाग6_भागisors[64] = अणु
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
	17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
	33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
	49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64
पूर्ण;

अटल काष्ठा clk_भाग_mult_table भाग6_भाग_mult_table = अणु
	.भागisors = sh_clk_भाग6_भागisors,
	.nr_भागisors = ARRAY_SIZE(sh_clk_भाग6_भागisors),
पूर्ण;

अटल काष्ठा clk_भाग_प्रकारable sh_clk_भाग6_table = अणु
	.भाग_mult_table	= &भाग6_भाग_mult_table,
पूर्ण;

अटल पूर्णांक sh_clk_भाग6_set_parent(काष्ठा clk *clk, काष्ठा clk *parent)
अणु
	काष्ठा clk_भाग_mult_table *table = clk_to_भाग_mult_table(clk);
	u32 value;
	पूर्णांक ret, i;

	अगर (!clk->parent_table || !clk->parent_num)
		वापस -EINVAL;

	/* Search the parent */
	क्रम (i = 0; i < clk->parent_num; i++)
		अगर (clk->parent_table[i] == parent)
			अवरोध;

	अगर (i == clk->parent_num)
		वापस -ENODEV;

	ret = clk_reparent(clk, parent);
	अगर (ret < 0)
		वापस ret;

	value = sh_clk_पढ़ो(clk) &
		~(((1 << clk->src_width) - 1) << clk->src_shअगरt);

	sh_clk_ग_लिखो(value | (i << clk->src_shअगरt), clk);

	/* Rebuild the frequency table */
	clk_rate_table_build(clk, clk->freq_table, table->nr_भागisors,
			     table, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा sh_clk_ops sh_clk_भाग6_reparent_clk_ops = अणु
	.recalc		= sh_clk_भाग_recalc,
	.round_rate	= sh_clk_भाग_round_rate,
	.set_rate	= sh_clk_भाग_set_rate,
	.enable		= sh_clk_भाग_enable,
	.disable	= sh_clk_भाग_disable,
	.set_parent	= sh_clk_भाग6_set_parent,
पूर्ण;

पूर्णांक __init sh_clk_भाग6_रेजिस्टर(काष्ठा clk *clks, पूर्णांक nr)
अणु
	वापस sh_clk_भाग_रेजिस्टर_ops(clks, nr, &sh_clk_भाग6_table,
				       &sh_clk_भाग_enable_clk_ops);
पूर्ण

पूर्णांक __init sh_clk_भाग6_reparent_रेजिस्टर(काष्ठा clk *clks, पूर्णांक nr)
अणु
	वापस sh_clk_भाग_रेजिस्टर_ops(clks, nr, &sh_clk_भाग6_table,
				       &sh_clk_भाग6_reparent_clk_ops);
पूर्ण

/*
 * भाग4 support
 */
अटल पूर्णांक sh_clk_भाग4_set_parent(काष्ठा clk *clk, काष्ठा clk *parent)
अणु
	काष्ठा clk_भाग_mult_table *table = clk_to_भाग_mult_table(clk);
	u32 value;
	पूर्णांक ret;

	/* we really need a better way to determine parent index, but क्रम
	 * now assume पूर्णांकernal parent comes with CLK_ENABLE_ON_INIT set,
	 * no CLK_ENABLE_ON_INIT means बाह्यal घड़ी...
	 */

	अगर (parent->flags & CLK_ENABLE_ON_INIT)
		value = sh_clk_पढ़ो(clk) & ~(1 << 7);
	अन्यथा
		value = sh_clk_पढ़ो(clk) | (1 << 7);

	ret = clk_reparent(clk, parent);
	अगर (ret < 0)
		वापस ret;

	sh_clk_ग_लिखो(value, clk);

	/* Rebiuld the frequency table */
	clk_rate_table_build(clk, clk->freq_table, table->nr_भागisors,
			     table, &clk->arch_flags);

	वापस 0;
पूर्ण

अटल काष्ठा sh_clk_ops sh_clk_भाग4_reparent_clk_ops = अणु
	.recalc		= sh_clk_भाग_recalc,
	.set_rate	= sh_clk_भाग_set_rate,
	.round_rate	= sh_clk_भाग_round_rate,
	.enable		= sh_clk_भाग_enable,
	.disable	= sh_clk_भाग_disable,
	.set_parent	= sh_clk_भाग4_set_parent,
पूर्ण;

पूर्णांक __init sh_clk_भाग4_रेजिस्टर(काष्ठा clk *clks, पूर्णांक nr,
				काष्ठा clk_भाग4_table *table)
अणु
	वापस sh_clk_भाग_रेजिस्टर_ops(clks, nr, table, &sh_clk_भाग_clk_ops);
पूर्ण

पूर्णांक __init sh_clk_भाग4_enable_रेजिस्टर(काष्ठा clk *clks, पूर्णांक nr,
				काष्ठा clk_भाग4_table *table)
अणु
	वापस sh_clk_भाग_रेजिस्टर_ops(clks, nr, table,
				       &sh_clk_भाग_enable_clk_ops);
पूर्ण

पूर्णांक __init sh_clk_भाग4_reparent_रेजिस्टर(काष्ठा clk *clks, पूर्णांक nr,
				काष्ठा clk_भाग4_table *table)
अणु
	वापस sh_clk_भाग_रेजिस्टर_ops(clks, nr, table,
				       &sh_clk_भाग4_reparent_clk_ops);
पूर्ण

/* FSI-DIV */
अटल अचिन्हित दीर्घ fsiभाग_recalc(काष्ठा clk *clk)
अणु
	u32 value;

	value = __raw_पढ़ोl(clk->mapping->base);

	value >>= 16;
	अगर (value < 2)
		वापस clk->parent->rate;

	वापस clk->parent->rate / value;
पूर्ण

अटल दीर्घ fsiभाग_round_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	वापस clk_rate_भाग_range_round(clk, 1, 0xffff, rate);
पूर्ण

अटल व्योम fsiभाग_disable(काष्ठा clk *clk)
अणु
	__raw_ग_लिखोl(0, clk->mapping->base);
पूर्ण

अटल पूर्णांक fsiभाग_enable(काष्ठा clk *clk)
अणु
	u32 value;

	value  = __raw_पढ़ोl(clk->mapping->base) >> 16;
	अगर (value < 2)
		वापस 0;

	__raw_ग_लिखोl((value << 16) | 0x3, clk->mapping->base);

	वापस 0;
पूर्ण

अटल पूर्णांक fsiभाग_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक idx;

	idx = (clk->parent->rate / rate) & 0xffff;
	अगर (idx < 2)
		__raw_ग_लिखोl(0, clk->mapping->base);
	अन्यथा
		__raw_ग_लिखोl(idx << 16, clk->mapping->base);

	वापस 0;
पूर्ण

अटल काष्ठा sh_clk_ops fsiभाग_clk_ops = अणु
	.recalc		= fsiभाग_recalc,
	.round_rate	= fsiभाग_round_rate,
	.set_rate	= fsiभाग_set_rate,
	.enable		= fsiभाग_enable,
	.disable	= fsiभाग_disable,
पूर्ण;

पूर्णांक __init sh_clk_fsiभाग_रेजिस्टर(काष्ठा clk *clks, पूर्णांक nr)
अणु
	काष्ठा clk_mapping *map;
	पूर्णांक i;

	क्रम (i = 0; i < nr; i++) अणु

		map = kzalloc(माप(काष्ठा clk_mapping), GFP_KERNEL);
		अगर (!map) अणु
			pr_err("%s: unable to alloc memory\n", __func__);
			वापस -ENOMEM;
		पूर्ण

		/* clks[i].enable_reg came from SH_CLK_FSIDIV() */
		map->phys		= (phys_addr_t)clks[i].enable_reg;
		map->len		= 8;

		clks[i].enable_reg	= 0; /* हटाओ .enable_reg */
		clks[i].ops		= &fsiभाग_clk_ops;
		clks[i].mapping		= map;

		clk_रेजिस्टर(&clks[i]);
	पूर्ण

	वापस 0;
पूर्ण
