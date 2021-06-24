<शैली गुरु>
/* Copyright (c) 2009 - 2016 Freescale Semiconductor, Inc.
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

#समावेश "bman_priv.h"

u16 bman_ip_rev;
EXPORT_SYMBOL(bman_ip_rev);

/* Register offsets */
#घोषणा REG_FBPR_FPC		0x0800
#घोषणा REG_ECSR		0x0a00
#घोषणा REG_ECIR		0x0a04
#घोषणा REG_EADR		0x0a08
#घोषणा REG_EDATA(n)		(0x0a10 + ((n) * 0x04))
#घोषणा REG_SBEC(n)		(0x0a80 + ((n) * 0x04))
#घोषणा REG_IP_REV_1		0x0bf8
#घोषणा REG_IP_REV_2		0x0bfc
#घोषणा REG_FBPR_BARE		0x0c00
#घोषणा REG_FBPR_BAR		0x0c04
#घोषणा REG_FBPR_AR		0x0c10
#घोषणा REG_SRCIDR		0x0d04
#घोषणा REG_LIODNR		0x0d08
#घोषणा REG_ERR_ISR		0x0e00
#घोषणा REG_ERR_IER		0x0e04
#घोषणा REG_ERR_ISDR		0x0e08

/* Used by all error पूर्णांकerrupt रेजिस्टरs except 'inhibit' */
#घोषणा BM_EIRQ_IVCI	0x00000010	/* Invalid Command Verb */
#घोषणा BM_EIRQ_FLWI	0x00000008	/* FBPR Low Watermark */
#घोषणा BM_EIRQ_MBEI	0x00000004	/* Multi-bit ECC Error */
#घोषणा BM_EIRQ_SBEI	0x00000002	/* Single-bit ECC Error */
#घोषणा BM_EIRQ_BSCN	0x00000001	/* pool State Change Notअगरication */

काष्ठा bman_hwerr_txt अणु
	u32 mask;
	स्थिर अक्षर *txt;
पूर्ण;

अटल स्थिर काष्ठा bman_hwerr_txt bman_hwerr_txts[] = अणु
	अणु BM_EIRQ_IVCI, "Invalid Command Verb" पूर्ण,
	अणु BM_EIRQ_FLWI, "FBPR Low Watermark" पूर्ण,
	अणु BM_EIRQ_MBEI, "Multi-bit ECC Error" पूर्ण,
	अणु BM_EIRQ_SBEI, "Single-bit ECC Error" पूर्ण,
	अणु BM_EIRQ_BSCN, "Pool State Change Notification" पूर्ण,
पूर्ण;

/* Only trigger low water mark पूर्णांकerrupt once only */
#घोषणा BMAN_ERRS_TO_DISABLE BM_EIRQ_FLWI

/* Poपूर्णांकer to the start of the BMan's CCSR space */
अटल u32 __iomem *bm_ccsr_start;

अटल अंतरभूत u32 bm_ccsr_in(u32 offset)
अणु
	वापस ioपढ़ो32be(bm_ccsr_start + offset/4);
पूर्ण
अटल अंतरभूत व्योम bm_ccsr_out(u32 offset, u32 val)
अणु
	ioग_लिखो32be(val, bm_ccsr_start + offset/4);
पूर्ण

अटल व्योम bm_get_version(u16 *id, u8 *major, u8 *minor)
अणु
	u32 v = bm_ccsr_in(REG_IP_REV_1);
	*id = (v >> 16);
	*major = (v >> 8) & 0xff;
	*minor = v & 0xff;
पूर्ण

/* संकेत transactions क्रम FBPRs with higher priority */
#घोषणा FBPR_AR_RPRIO_HI BIT(30)

/* Track अगर probe has occurred and अगर cleanup is required */
अटल पूर्णांक __bman_probed;
अटल पूर्णांक __bman_requires_cleanup;


अटल पूर्णांक bm_set_memory(u64 ba, u32 size)
अणु
	u32 bar, bare;
	u32 exp = ilog2(size);
	/* choke अगर size isn't within range */
	DPAA_ASSERT(size >= 4096 && size <= 1024*1024*1024 &&
		   is_घातer_of_2(size));
	/* choke अगर '[e]ba' has lower-alignment than 'size' */
	DPAA_ASSERT(!(ba & (size - 1)));

	/* Check to see अगर BMan has alपढ़ोy been initialized */
	bar = bm_ccsr_in(REG_FBPR_BAR);
	अगर (bar) अणु
		/* Maker sure ba == what was programmed) */
		bare = bm_ccsr_in(REG_FBPR_BARE);
		अगर (bare != upper_32_bits(ba) || bar != lower_32_bits(ba)) अणु
			pr_err("Attempted to reinitialize BMan with different BAR, got 0x%llx read BARE=0x%x BAR=0x%x\n",
			       ba, bare, bar);
			वापस -ENOMEM;
		पूर्ण
		pr_info("BMan BAR already configured\n");
		__bman_requires_cleanup = 1;
		वापस 1;
	पूर्ण

	bm_ccsr_out(REG_FBPR_BARE, upper_32_bits(ba));
	bm_ccsr_out(REG_FBPR_BAR, lower_32_bits(ba));
	bm_ccsr_out(REG_FBPR_AR, exp - 1);
	वापस 0;
पूर्ण

/*
 * Location and size of BMan निजी memory
 *
 * Ideally we would use the DMA API to turn rmem->base पूर्णांकo a DMA address
 * (especially अगर iommu translations ever get involved).  Unक्रमtunately, the
 * DMA API currently करोes not allow mapping anything that is not backed with
 * a काष्ठा page.
 */
अटल dma_addr_t fbpr_a;
अटल माप_प्रकार fbpr_sz;

अटल पूर्णांक bman_fbpr(काष्ठा reserved_mem *rmem)
अणु
	fbpr_a = rmem->base;
	fbpr_sz = rmem->size;

	WARN_ON(!(fbpr_a && fbpr_sz));

	वापस 0;
पूर्ण
RESERVEDMEM_OF_DECLARE(bman_fbpr, "fsl,bman-fbpr", bman_fbpr);

अटल irqवापस_t bman_isr(पूर्णांक irq, व्योम *ptr)
अणु
	u32 isr_val, ier_val, ecsr_val, isr_mask, i;
	काष्ठा device *dev = ptr;

	ier_val = bm_ccsr_in(REG_ERR_IER);
	isr_val = bm_ccsr_in(REG_ERR_ISR);
	ecsr_val = bm_ccsr_in(REG_ECSR);
	isr_mask = isr_val & ier_val;

	अगर (!isr_mask)
		वापस IRQ_NONE;

	क्रम (i = 0; i < ARRAY_SIZE(bman_hwerr_txts); i++) अणु
		अगर (bman_hwerr_txts[i].mask & isr_mask) अणु
			dev_err_ratelimited(dev, "ErrInt: %s\n",
					    bman_hwerr_txts[i].txt);
			अगर (bman_hwerr_txts[i].mask & ecsr_val) अणु
				/* Re-arm error capture रेजिस्टरs */
				bm_ccsr_out(REG_ECSR, ecsr_val);
			पूर्ण
			अगर (bman_hwerr_txts[i].mask & BMAN_ERRS_TO_DISABLE) अणु
				dev_dbg(dev, "Disabling error 0x%x\n",
					bman_hwerr_txts[i].mask);
				ier_val &= ~bman_hwerr_txts[i].mask;
				bm_ccsr_out(REG_ERR_IER, ier_val);
			पूर्ण
		पूर्ण
	पूर्ण
	bm_ccsr_out(REG_ERR_ISR, isr_val);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक bman_is_probed(व्योम)
अणु
	वापस __bman_probed;
पूर्ण
EXPORT_SYMBOL_GPL(bman_is_probed);

पूर्णांक bman_requires_cleanup(व्योम)
अणु
	वापस __bman_requires_cleanup;
पूर्ण

व्योम bman_करोne_cleanup(व्योम)
अणु
	__bman_requires_cleanup = 0;
पूर्ण

अटल पूर्णांक fsl_bman_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret, err_irq;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा resource *res;
	u16 id, bm_pool_cnt;
	u8 major, minor;

	__bman_probed = -1;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "Can't get %pOF property 'IORESOURCE_MEM'\n",
			node);
		वापस -ENXIO;
	पूर्ण
	bm_ccsr_start = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!bm_ccsr_start)
		वापस -ENXIO;

	bm_get_version(&id, &major, &minor);
	अगर (major == 1 && minor == 0) अणु
		bman_ip_rev = BMAN_REV10;
		bm_pool_cnt = BM_POOL_MAX;
	पूर्ण अन्यथा अगर (major == 2 && minor == 0) अणु
		bman_ip_rev = BMAN_REV20;
		bm_pool_cnt = 8;
	पूर्ण अन्यथा अगर (major == 2 && minor == 1) अणु
		bman_ip_rev = BMAN_REV21;
		bm_pool_cnt = BM_POOL_MAX;
	पूर्ण अन्यथा अणु
		dev_err(dev, "Unknown Bman version:%04x,%02x,%02x\n",
			id, major, minor);
		वापस -ENODEV;
	पूर्ण

	/*
	 * If FBPR memory wasn't defined using the qbman compatible string
	 * try using the of_reserved_mem_device method
	 */
	अगर (!fbpr_a) अणु
		ret = qbman_init_निजी_mem(dev, 0, &fbpr_a, &fbpr_sz);
		अगर (ret) अणु
			dev_err(dev, "qbman_init_private_mem() failed 0x%x\n",
				ret);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	dev_dbg(dev, "Allocated FBPR 0x%llx 0x%zx\n", fbpr_a, fbpr_sz);

	bm_set_memory(fbpr_a, fbpr_sz);

	err_irq = platक्रमm_get_irq(pdev, 0);
	अगर (err_irq <= 0) अणु
		dev_info(dev, "Can't get %pOF IRQ\n", node);
		वापस -ENODEV;
	पूर्ण
	ret = devm_request_irq(dev, err_irq, bman_isr, IRQF_SHARED, "bman-err",
			       dev);
	अगर (ret)  अणु
		dev_err(dev, "devm_request_irq() failed %d for '%pOF'\n",
			ret, node);
		वापस ret;
	पूर्ण
	/* Disable Buffer Pool State Change */
	bm_ccsr_out(REG_ERR_ISDR, BM_EIRQ_BSCN);
	/*
	 * Write-to-clear any stale bits, (eg. starvation being निश्चितed prior
	 * to resource allocation during driver init).
	 */
	bm_ccsr_out(REG_ERR_ISR, 0xffffffff);
	/* Enable Error Interrupts */
	bm_ccsr_out(REG_ERR_IER, 0xffffffff);

	bm_bpalloc = devm_gen_pool_create(dev, 0, -1, "bman-bpalloc");
	अगर (IS_ERR(bm_bpalloc)) अणु
		ret = PTR_ERR(bm_bpalloc);
		dev_err(dev, "bman-bpalloc pool init failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* seed BMan resource pool */
	ret = gen_pool_add(bm_bpalloc, DPAA_GENALLOC_OFF, bm_pool_cnt, -1);
	अगर (ret) अणु
		dev_err(dev, "Failed to seed BPID range [%d..%d] (%d)\n",
			0, bm_pool_cnt - 1, ret);
		वापस ret;
	पूर्ण

	__bman_probed = 1;

	वापस 0;
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_bman_ids[] = अणु
	अणु
		.compatible = "fsl,bman",
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_bman_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = fsl_bman_ids,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = fsl_bman_probe,
पूर्ण;

builtin_platक्रमm_driver(fsl_bman_driver);
