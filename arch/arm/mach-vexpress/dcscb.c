<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-vexpress/dcscb.c - Dual Cluster System Configuration Block
 *
 * Created by:	Nicolas Pitre, May 2012
 * Copyright:	(C) 2012-2013  Linaro Limited
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/of_address.h>
#समावेश <linux/vexpress.h>
#समावेश <linux/arm-cci.h>

#समावेश <यंत्र/mcpm.h>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/cp15.h>

#समावेश "core.h"

#घोषणा RST_HOLD0	0x0
#घोषणा RST_HOLD1	0x4
#घोषणा SYS_SWRESET	0x8
#घोषणा RST_STAT0	0xc
#घोषणा RST_STAT1	0x10
#घोषणा EAG_CFG_R	0x20
#घोषणा EAG_CFG_W	0x24
#घोषणा KFC_CFG_R	0x28
#घोषणा KFC_CFG_W	0x2c
#घोषणा DCS_CFG_R	0x30

अटल व्योम __iomem *dcscb_base;
अटल पूर्णांक dcscb_allcpus_mask[2];

अटल पूर्णांक dcscb_cpu_घातerup(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	अचिन्हित पूर्णांक rst_hold, cpumask = (1 << cpu);

	pr_debug("%s: cpu %u cluster %u\n", __func__, cpu, cluster);
	अगर (cluster >= 2 || !(cpumask & dcscb_allcpus_mask[cluster]))
		वापस -EINVAL;

	rst_hold = पढ़ोl_relaxed(dcscb_base + RST_HOLD0 + cluster * 4);
	rst_hold &= ~(cpumask | (cpumask << 4));
	ग_लिखोl_relaxed(rst_hold, dcscb_base + RST_HOLD0 + cluster * 4);
	वापस 0;
पूर्ण

अटल पूर्णांक dcscb_cluster_घातerup(अचिन्हित पूर्णांक cluster)
अणु
	अचिन्हित पूर्णांक rst_hold;

	pr_debug("%s: cluster %u\n", __func__, cluster);
	अगर (cluster >= 2)
		वापस -EINVAL;

	/* हटाओ cluster reset and add inभागidual CPU's reset */
	rst_hold = पढ़ोl_relaxed(dcscb_base + RST_HOLD0 + cluster * 4);
	rst_hold &= ~(1 << 8);
	rst_hold |= dcscb_allcpus_mask[cluster];
	ग_लिखोl_relaxed(rst_hold, dcscb_base + RST_HOLD0 + cluster * 4);
	वापस 0;
पूर्ण

अटल व्योम dcscb_cpu_घातerकरोwn_prepare(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	अचिन्हित पूर्णांक rst_hold;

	pr_debug("%s: cpu %u cluster %u\n", __func__, cpu, cluster);
	BUG_ON(cluster >= 2 || !((1 << cpu) & dcscb_allcpus_mask[cluster]));

	rst_hold = पढ़ोl_relaxed(dcscb_base + RST_HOLD0 + cluster * 4);
	rst_hold |= (1 << cpu);
	ग_लिखोl_relaxed(rst_hold, dcscb_base + RST_HOLD0 + cluster * 4);
पूर्ण

अटल व्योम dcscb_cluster_घातerकरोwn_prepare(अचिन्हित पूर्णांक cluster)
अणु
	अचिन्हित पूर्णांक rst_hold;

	pr_debug("%s: cluster %u\n", __func__, cluster);
	BUG_ON(cluster >= 2);

	rst_hold = पढ़ोl_relaxed(dcscb_base + RST_HOLD0 + cluster * 4);
	rst_hold |= (1 << 8);
	ग_लिखोl_relaxed(rst_hold, dcscb_base + RST_HOLD0 + cluster * 4);
पूर्ण

अटल व्योम dcscb_cpu_cache_disable(व्योम)
अणु
	/* Disable and flush the local CPU cache. */
	v7_निकास_coherency_flush(louis);
पूर्ण

अटल व्योम dcscb_cluster_cache_disable(व्योम)
अणु
	/* Flush all cache levels क्रम this cluster. */
	v7_निकास_coherency_flush(all);

	/*
	 * A full outer cache flush could be needed at this poपूर्णांक
	 * on platक्रमms with such a cache, depending on where the
	 * outer cache sits. In some हालs the notion of a "last
	 * cluster standing" would need to be implemented अगर the
	 * outer cache is shared across clusters. In any हाल, when
	 * the outer cache needs flushing, there is no concurrent
	 * access to the cache controller to worry about and no
	 * special locking besides what is alपढ़ोy provided by the
	 * MCPM state machinery is needed.
	 */

	/*
	 * Disable cluster-level coherency by masking
	 * incoming snoops and DVM messages:
	 */
	cci_disable_port_by_cpu(पढ़ो_cpuid_mpidr());
पूर्ण

अटल स्थिर काष्ठा mcpm_platक्रमm_ops dcscb_घातer_ops = अणु
	.cpu_घातerup		= dcscb_cpu_घातerup,
	.cluster_घातerup	= dcscb_cluster_घातerup,
	.cpu_घातerकरोwn_prepare	= dcscb_cpu_घातerकरोwn_prepare,
	.cluster_घातerकरोwn_prepare = dcscb_cluster_घातerकरोwn_prepare,
	.cpu_cache_disable	= dcscb_cpu_cache_disable,
	.cluster_cache_disable	= dcscb_cluster_cache_disable,
पूर्ण;

बाह्य व्योम dcscb_घातer_up_setup(अचिन्हित पूर्णांक affinity_level);

अटल पूर्णांक __init dcscb_init(व्योम)
अणु
	काष्ठा device_node *node;
	अचिन्हित पूर्णांक cfg;
	पूर्णांक ret;

	अगर (!cci_probed())
		वापस -ENODEV;

	node = of_find_compatible_node(शून्य, शून्य, "arm,rtsm,dcscb");
	अगर (!node)
		वापस -ENODEV;
	dcscb_base = of_iomap(node, 0);
	अगर (!dcscb_base)
		वापस -EADDRNOTAVAIL;
	cfg = पढ़ोl_relaxed(dcscb_base + DCS_CFG_R);
	dcscb_allcpus_mask[0] = (1 << (((cfg >> 16) >> (0 << 2)) & 0xf)) - 1;
	dcscb_allcpus_mask[1] = (1 << (((cfg >> 16) >> (1 << 2)) & 0xf)) - 1;

	ret = mcpm_platक्रमm_रेजिस्टर(&dcscb_घातer_ops);
	अगर (!ret)
		ret = mcpm_sync_init(dcscb_घातer_up_setup);
	अगर (ret) अणु
		iounmap(dcscb_base);
		वापस ret;
	पूर्ण

	pr_info("VExpress DCSCB support installed\n");

	/*
	 * Future entries पूर्णांकo the kernel can now go
	 * through the cluster entry vectors.
	 */
	vexpress_flags_set(__pa_symbol(mcpm_entry_poपूर्णांक));

	वापस 0;
पूर्ण

early_initcall(dcscb_init);
