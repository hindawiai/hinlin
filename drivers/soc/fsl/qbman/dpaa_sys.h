<शैली गुरु>
/* Copyright 2008 - 2016 Freescale Semiconductor, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __DPAA_SYS_H
#घोषणा __DPAA_SYS_H

#समावेश <linux/cpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/prefetch.h>
#समावेश <linux/genभाग.स>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>

/* For 2-element tables related to cache-inhibited and cache-enabled mappings */
#घोषणा DPAA_PORTAL_CE 0
#घोषणा DPAA_PORTAL_CI 1

अटल अंतरभूत व्योम dpaa_flush(व्योम *p)
अणु
	/*
	 * Only PPC needs to flush the cache currently - on ARM the mapping
	 * is non cacheable
	 */
#अगर_घोषित CONFIG_PPC
	flush_dcache_range((अचिन्हित दीर्घ)p, (अचिन्हित दीर्घ)p+64);
#पूर्ण_अगर
पूर्ण

#घोषणा dpaa_invalidate(p) dpaa_flush(p)

#घोषणा dpaa_zero(p) स_रखो(p, 0, 64)

अटल अंतरभूत व्योम dpaa_touch_ro(व्योम *p)
अणु
#अगर (L1_CACHE_BYTES == 32)
	prefetch(p+32);
#पूर्ण_अगर
	prefetch(p);
पूर्ण

/* Commonly used combo */
अटल अंतरभूत व्योम dpaa_invalidate_touch_ro(व्योम *p)
अणु
	dpaa_invalidate(p);
	dpaa_touch_ro(p);
पूर्ण


#अगर_घोषित CONFIG_FSL_DPAA_CHECKING
#घोषणा DPAA_ASSERT(x) WARN_ON(!(x))
#अन्यथा
#घोषणा DPAA_ASSERT(x)
#पूर्ण_अगर

/* cyclic helper क्रम rings */
अटल अंतरभूत u8 dpaa_cyc_dअगरf(u8 ringsize, u8 first, u8 last)
अणु
	/* 'first' is included, 'last' is excluded */
	अगर (first <= last)
		वापस last - first;
	वापस ringsize + last - first;
पूर्ण

/* Offset applied to genalloc pools due to zero being an error वापस */
#घोषणा DPAA_GENALLOC_OFF	0x80000000

/* Initialize the devices निजी memory region */
पूर्णांक qbman_init_निजी_mem(काष्ठा device *dev, पूर्णांक idx, dma_addr_t *addr,
				माप_प्रकार *size);

/* memremap() attributes क्रम dअगरferent platक्रमms */
#अगर_घोषित CONFIG_PPC
#घोषणा QBMAN_MEMREMAP_ATTR	MEMREMAP_WB
#अन्यथा
#घोषणा QBMAN_MEMREMAP_ATTR	MEMREMAP_WC
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक dpaa_set_portal_irq_affinity(काष्ठा device *dev,
					       पूर्णांक irq, पूर्णांक cpu)
अणु
	पूर्णांक ret = 0;

	अगर (!irq_can_set_affinity(irq)) अणु
		dev_err(dev, "unable to set IRQ affinity\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cpu == -1 || !cpu_online(cpu))
		cpu = cpumask_any(cpu_online_mask);

	ret = irq_set_affinity(irq, cpumask_of(cpu));
	अगर (ret)
		dev_err(dev, "irq_set_affinity() on CPU %d failed\n", cpu);

	वापस ret;
पूर्ण

#पूर्ण_अगर	/* __DPAA_SYS_H */
