<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2012-2019 ARM Limited or its affiliates. */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <linux/crypto.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "cc_driver.h"
#समावेश "cc_request_mgr.h"
#समावेश "cc_buffer_mgr.h"
#समावेश "cc_debugfs.h"
#समावेश "cc_cipher.h"
#समावेश "cc_aead.h"
#समावेश "cc_hash.h"
#समावेश "cc_sram_mgr.h"
#समावेश "cc_pm.h"
#समावेश "cc_fips.h"

bool cc_dump_desc;
module_param_named(dump_desc, cc_dump_desc, bool, 0600);
MODULE_PARM_DESC(cc_dump_desc, "Dump descriptors to kernel log as debugging aid");
bool cc_dump_bytes;
module_param_named(dump_bytes, cc_dump_bytes, bool, 0600);
MODULE_PARM_DESC(cc_dump_bytes, "Dump buffers to kernel log as debugging aid");

अटल bool cc_sec_disable;
module_param_named(sec_disable, cc_sec_disable, bool, 0600);
MODULE_PARM_DESC(cc_sec_disable, "Disable security functions");

काष्ठा cc_hw_data अणु
	अक्षर *name;
	क्रमागत cc_hw_rev rev;
	u32 sig;
	u32 cidr_0123;
	u32 pidr_0124;
	पूर्णांक std_bodies;
पूर्ण;

#घोषणा CC_NUM_IDRS 4
#घोषणा CC_HW_RESET_LOOP_COUNT 10

/* Note: PIDR3 holds CMOD/Rev so ignored क्रम HW identअगरication purposes */
अटल स्थिर u32 pidr_0124_offsets[CC_NUM_IDRS] = अणु
	CC_REG(PERIPHERAL_ID_0), CC_REG(PERIPHERAL_ID_1),
	CC_REG(PERIPHERAL_ID_2), CC_REG(PERIPHERAL_ID_4)
पूर्ण;

अटल स्थिर u32 cidr_0123_offsets[CC_NUM_IDRS] = अणु
	CC_REG(COMPONENT_ID_0), CC_REG(COMPONENT_ID_1),
	CC_REG(COMPONENT_ID_2), CC_REG(COMPONENT_ID_3)
पूर्ण;

/* Hardware revisions defs. */

/* The 703 is a OSCCA only variant of the 713 */
अटल स्थिर काष्ठा cc_hw_data cc703_hw = अणु
	.name = "703", .rev = CC_HW_REV_713, .cidr_0123 = 0xB105F00DU,
	.pidr_0124 = 0x040BB0D0U, .std_bodies = CC_STD_OSCCA
पूर्ण;

अटल स्थिर काष्ठा cc_hw_data cc713_hw = अणु
	.name = "713", .rev = CC_HW_REV_713, .cidr_0123 = 0xB105F00DU,
	.pidr_0124 = 0x040BB0D0U, .std_bodies = CC_STD_ALL
पूर्ण;

अटल स्थिर काष्ठा cc_hw_data cc712_hw = अणु
	.name = "712", .rev = CC_HW_REV_712, .sig =  0xDCC71200U,
	.std_bodies = CC_STD_ALL
पूर्ण;

अटल स्थिर काष्ठा cc_hw_data cc710_hw = अणु
	.name = "710", .rev = CC_HW_REV_710, .sig =  0xDCC63200U,
	.std_bodies = CC_STD_ALL
पूर्ण;

अटल स्थिर काष्ठा cc_hw_data cc630p_hw = अणु
	.name = "630P", .rev = CC_HW_REV_630, .sig = 0xDCC63000U,
	.std_bodies = CC_STD_ALL
पूर्ण;

अटल स्थिर काष्ठा of_device_id arm_ccree_dev_of_match[] = अणु
	अणु .compatible = "arm,cryptocell-703-ree", .data = &cc703_hw पूर्ण,
	अणु .compatible = "arm,cryptocell-713-ree", .data = &cc713_hw पूर्ण,
	अणु .compatible = "arm,cryptocell-712-ree", .data = &cc712_hw पूर्ण,
	अणु .compatible = "arm,cryptocell-710-ree", .data = &cc710_hw पूर्ण,
	अणु .compatible = "arm,cryptocell-630p-ree", .data = &cc630p_hw पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, arm_ccree_dev_of_match);

अटल व्योम init_cc_cache_params(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	u32 cache_params, ace_स्थिर, val, mask;

	/* compute CC_AXIM_CACHE_PARAMS */
	cache_params = cc_ioपढ़ो(drvdata, CC_REG(AXIM_CACHE_PARAMS));
	dev_dbg(dev, "Cache params previous: 0x%08X\n", cache_params);

	/* non cached or ग_लिखो-back, ग_लिखो allocate */
	val = drvdata->coherent ? 0xb : 0x2;

	mask = CC_GENMASK(CC_AXIM_CACHE_PARAMS_AWCACHE);
	cache_params &= ~mask;
	cache_params |= FIELD_PREP(mask, val);

	mask = CC_GENMASK(CC_AXIM_CACHE_PARAMS_AWCACHE_LAST);
	cache_params &= ~mask;
	cache_params |= FIELD_PREP(mask, val);

	mask = CC_GENMASK(CC_AXIM_CACHE_PARAMS_ARCACHE);
	cache_params &= ~mask;
	cache_params |= FIELD_PREP(mask, val);

	drvdata->cache_params = cache_params;

	dev_dbg(dev, "Cache params current: 0x%08X\n", cache_params);

	अगर (drvdata->hw_rev <= CC_HW_REV_710)
		वापस;

	/* compute CC_AXIM_ACE_CONST */
	ace_स्थिर = cc_ioपढ़ो(drvdata, CC_REG(AXIM_ACE_CONST));
	dev_dbg(dev, "ACE-const previous: 0x%08X\n", ace_स्थिर);

	/* प्रणाली or outer-sharable */
	val = drvdata->coherent ? 0x2 : 0x3;

	mask = CC_GENMASK(CC_AXIM_ACE_CONST_ARDOMAIN);
	ace_स्थिर &= ~mask;
	ace_स्थिर |= FIELD_PREP(mask, val);

	mask = CC_GENMASK(CC_AXIM_ACE_CONST_AWDOMAIN);
	ace_स्थिर &= ~mask;
	ace_स्थिर |= FIELD_PREP(mask, val);

	dev_dbg(dev, "ACE-const current: 0x%08X\n", ace_स्थिर);

	drvdata->ace_स्थिर = ace_स्थिर;
पूर्ण

अटल u32 cc_पढ़ो_idr(काष्ठा cc_drvdata *drvdata, स्थिर u32 *idr_offsets)
अणु
	पूर्णांक i;
	जोड़ अणु
		u8 regs[CC_NUM_IDRS];
		__le32 val;
	पूर्ण idr;

	क्रम (i = 0; i < CC_NUM_IDRS; ++i)
		idr.regs[i] = cc_ioपढ़ो(drvdata, idr_offsets[i]);

	वापस le32_to_cpu(idr.val);
पूर्ण

व्योम __dump_byte_array(स्थिर अक्षर *name, स्थिर u8 *buf, माप_प्रकार len)
अणु
	अक्षर prefix[64];

	अगर (!buf)
		वापस;

	snम_लिखो(prefix, माप(prefix), "%s[%zu]: ", name, len);

	prपूर्णांक_hex_dump(KERN_DEBUG, prefix, DUMP_PREFIX_ADDRESS, 16, 1, buf,
		       len, false);
पूर्ण

अटल irqवापस_t cc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cc_drvdata *drvdata = (काष्ठा cc_drvdata *)dev_id;
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	u32 irr;
	u32 imr;

	/* STAT_OP_TYPE_GENERIC STAT_PHASE_0: Interrupt */
	/* अगर driver suspended वापस, probably shared पूर्णांकerrupt */
	अगर (pm_runसमय_suspended(dev))
		वापस IRQ_NONE;

	/* पढ़ो the पूर्णांकerrupt status */
	irr = cc_ioपढ़ो(drvdata, CC_REG(HOST_IRR));
	dev_dbg(dev, "Got IRR=0x%08X\n", irr);

	अगर (irr == 0) /* Probably shared पूर्णांकerrupt line */
		वापस IRQ_NONE;

	imr = cc_ioपढ़ो(drvdata, CC_REG(HOST_IMR));

	/* clear पूर्णांकerrupt - must be beक्रमe processing events */
	cc_ioग_लिखो(drvdata, CC_REG(HOST_ICR), irr);

	drvdata->irq = irr;
	/* Completion पूर्णांकerrupt - most probable */
	अगर (irr & drvdata->comp_mask) अणु
		/* Mask all completion पूर्णांकerrupts - will be unmasked in
		 * deferred service handler
		 */
		cc_ioग_लिखो(drvdata, CC_REG(HOST_IMR), imr | drvdata->comp_mask);
		irr &= ~drvdata->comp_mask;
		complete_request(drvdata);
	पूर्ण
#अगर_घोषित CONFIG_CRYPTO_FIPS
	/* TEE FIPS पूर्णांकerrupt */
	अगर (irr & CC_GPR0_IRQ_MASK) अणु
		/* Mask पूर्णांकerrupt - will be unmasked in Deferred service
		 * handler
		 */
		cc_ioग_लिखो(drvdata, CC_REG(HOST_IMR), imr | CC_GPR0_IRQ_MASK);
		irr &= ~CC_GPR0_IRQ_MASK;
		fips_handler(drvdata);
	पूर्ण
#पूर्ण_अगर
	/* AXI error पूर्णांकerrupt */
	अगर (irr & CC_AXI_ERR_IRQ_MASK) अणु
		u32 axi_err;

		/* Read the AXI error ID */
		axi_err = cc_ioपढ़ो(drvdata, CC_REG(AXIM_MON_ERR));
		dev_dbg(dev, "AXI completion error: axim_mon_err=0x%08X\n",
			axi_err);

		irr &= ~CC_AXI_ERR_IRQ_MASK;
	पूर्ण

	अगर (irr) अणु
		dev_dbg_ratelimited(dev, "IRR includes unknown cause bits (0x%08X)\n",
				    irr);
		/* Just warning */
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

bool cc_रुको_क्रम_reset_completion(काष्ठा cc_drvdata *drvdata)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक i;

	/* 712/710/63 has no reset completion indication, always वापस true */
	अगर (drvdata->hw_rev <= CC_HW_REV_712)
		वापस true;

	क्रम (i = 0; i < CC_HW_RESET_LOOP_COUNT; i++) अणु
		/* in cc7x3 NVM_IS_IDLE indicates that CC reset is
		 *  completed and device is fully functional
		 */
		val = cc_ioपढ़ो(drvdata, CC_REG(NVM_IS_IDLE));
		अगर (val & CC_NVM_IS_IDLE_MASK) अणु
			/* hw indicate reset completed */
			वापस true;
		पूर्ण
		/* allow scheduling other process on the processor */
		schedule();
	पूर्ण
	/* reset not completed */
	वापस false;
पूर्ण

पूर्णांक init_cc_regs(काष्ठा cc_drvdata *drvdata)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा device *dev = drvdata_to_dev(drvdata);

	/* Unmask all AXI पूर्णांकerrupt sources AXI_CFG1 रेजिस्टर   */
	/* AXI पूर्णांकerrupt config are obsoleted startign at cc7x3 */
	अगर (drvdata->hw_rev <= CC_HW_REV_712) अणु
		val = cc_ioपढ़ो(drvdata, CC_REG(AXIM_CFG));
		cc_ioग_लिखो(drvdata, CC_REG(AXIM_CFG), val & ~CC_AXI_IRQ_MASK);
		dev_dbg(dev, "AXIM_CFG=0x%08X\n",
			cc_ioपढ़ो(drvdata, CC_REG(AXIM_CFG)));
	पूर्ण

	/* Clear all pending पूर्णांकerrupts */
	val = cc_ioपढ़ो(drvdata, CC_REG(HOST_IRR));
	dev_dbg(dev, "IRR=0x%08X\n", val);
	cc_ioग_लिखो(drvdata, CC_REG(HOST_ICR), val);

	/* Unmask relevant पूर्णांकerrupt cause */
	val = drvdata->comp_mask | CC_AXI_ERR_IRQ_MASK;

	अगर (drvdata->hw_rev >= CC_HW_REV_712)
		val |= CC_GPR0_IRQ_MASK;

	cc_ioग_लिखो(drvdata, CC_REG(HOST_IMR), ~val);

	cc_ioग_लिखो(drvdata, CC_REG(AXIM_CACHE_PARAMS), drvdata->cache_params);
	अगर (drvdata->hw_rev >= CC_HW_REV_712)
		cc_ioग_लिखो(drvdata, CC_REG(AXIM_ACE_CONST), drvdata->ace_स्थिर);

	वापस 0;
पूर्ण

अटल पूर्णांक init_cc_resources(काष्ठा platक्रमm_device *plat_dev)
अणु
	काष्ठा resource *req_mem_cc_regs = शून्य;
	काष्ठा cc_drvdata *new_drvdata;
	काष्ठा device *dev = &plat_dev->dev;
	काष्ठा device_node *np = dev->of_node;
	u32 val, hw_rev_pidr, sig_cidr;
	u64 dma_mask;
	स्थिर काष्ठा cc_hw_data *hw_rev;
	काष्ठा clk *clk;
	पूर्णांक irq;
	पूर्णांक rc = 0;

	new_drvdata = devm_kzalloc(dev, माप(*new_drvdata), GFP_KERNEL);
	अगर (!new_drvdata)
		वापस -ENOMEM;

	hw_rev = of_device_get_match_data(dev);
	new_drvdata->hw_rev_name = hw_rev->name;
	new_drvdata->hw_rev = hw_rev->rev;
	new_drvdata->std_bodies = hw_rev->std_bodies;

	अगर (hw_rev->rev >= CC_HW_REV_712) अणु
		new_drvdata->axim_mon_offset = CC_REG(AXIM_MON_COMP);
		new_drvdata->sig_offset = CC_REG(HOST_SIGNATURE_712);
		new_drvdata->ver_offset = CC_REG(HOST_VERSION_712);
	पूर्ण अन्यथा अणु
		new_drvdata->axim_mon_offset = CC_REG(AXIM_MON_COMP8);
		new_drvdata->sig_offset = CC_REG(HOST_SIGNATURE_630);
		new_drvdata->ver_offset = CC_REG(HOST_VERSION_630);
	पूर्ण

	new_drvdata->comp_mask = CC_COMP_IRQ_MASK;

	platक्रमm_set_drvdata(plat_dev, new_drvdata);
	new_drvdata->plat_dev = plat_dev;

	clk = devm_clk_get_optional(dev, शून्य);
	अगर (IS_ERR(clk))
		वापस dev_err_probe(dev, PTR_ERR(clk), "Error getting clock\n");
	new_drvdata->clk = clk;

	new_drvdata->coherent = of_dma_is_coherent(np);

	/* Get device resources */
	/* First CC रेजिस्टरs space */
	req_mem_cc_regs = platक्रमm_get_resource(plat_dev, IORESOURCE_MEM, 0);
	/* Map रेजिस्टरs space */
	new_drvdata->cc_base = devm_ioremap_resource(dev, req_mem_cc_regs);
	अगर (IS_ERR(new_drvdata->cc_base))
		वापस PTR_ERR(new_drvdata->cc_base);

	dev_dbg(dev, "Got MEM resource (%s): %pR\n", req_mem_cc_regs->name,
		req_mem_cc_regs);
	dev_dbg(dev, "CC registers mapped from %pa to 0x%p\n",
		&req_mem_cc_regs->start, new_drvdata->cc_base);

	/* Then IRQ */
	irq = platक्रमm_get_irq(plat_dev, 0);
	अगर (irq < 0)
		वापस irq;

	init_completion(&new_drvdata->hw_queue_avail);

	अगर (!dev->dma_mask)
		dev->dma_mask = &dev->coherent_dma_mask;

	dma_mask = DMA_BIT_MASK(DMA_BIT_MASK_LEN);
	जबतक (dma_mask > 0x7fffffffUL) अणु
		अगर (dma_supported(dev, dma_mask)) अणु
			rc = dma_set_coherent_mask(dev, dma_mask);
			अगर (!rc)
				अवरोध;
		पूर्ण
		dma_mask >>= 1;
	पूर्ण

	अगर (rc) अणु
		dev_err(dev, "Failed in dma_set_mask, mask=%llx\n", dma_mask);
		वापस rc;
	पूर्ण

	rc = clk_prepare_enable(new_drvdata->clk);
	अगर (rc) अणु
		dev_err(dev, "Failed to enable clock");
		वापस rc;
	पूर्ण

	new_drvdata->sec_disabled = cc_sec_disable;

	pm_runसमय_set_स्वतःsuspend_delay(dev, CC_SUSPEND_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	rc = pm_runसमय_get_sync(dev);
	अगर (rc < 0) अणु
		dev_err(dev, "pm_runtime_get_sync() failed: %d\n", rc);
		जाओ post_pm_err;
	पूर्ण

	/* Wait क्रम Cryptocell reset completion */
	अगर (!cc_रुको_क्रम_reset_completion(new_drvdata)) अणु
		dev_err(dev, "Cryptocell reset not completed");
	पूर्ण

	अगर (hw_rev->rev <= CC_HW_REV_712) अणु
		/* Verअगरy correct mapping */
		val = cc_ioपढ़ो(new_drvdata, new_drvdata->sig_offset);
		अगर (val != hw_rev->sig) अणु
			dev_err(dev, "Invalid CC signature: SIGNATURE=0x%08X != expected=0x%08X\n",
				val, hw_rev->sig);
			rc = -EINVAL;
			जाओ post_pm_err;
		पूर्ण
		sig_cidr = val;
		hw_rev_pidr = cc_ioपढ़ो(new_drvdata, new_drvdata->ver_offset);
	पूर्ण अन्यथा अणु
		/* Verअगरy correct mapping */
		val = cc_पढ़ो_idr(new_drvdata, pidr_0124_offsets);
		अगर (val != hw_rev->pidr_0124) अणु
			dev_err(dev, "Invalid CC PIDR: PIDR0124=0x%08X != expected=0x%08X\n",
				val,  hw_rev->pidr_0124);
			rc = -EINVAL;
			जाओ post_pm_err;
		पूर्ण
		hw_rev_pidr = val;

		val = cc_पढ़ो_idr(new_drvdata, cidr_0123_offsets);
		अगर (val != hw_rev->cidr_0123) अणु
			dev_err(dev, "Invalid CC CIDR: CIDR0123=0x%08X != expected=0x%08X\n",
			val,  hw_rev->cidr_0123);
			rc = -EINVAL;
			जाओ post_pm_err;
		पूर्ण
		sig_cidr = val;

		/* Check HW engine configuration */
		val = cc_ioपढ़ो(new_drvdata, CC_REG(HOST_REMOVE_INPUT_PINS));
		चयन (val) अणु
		हाल CC_PINS_FULL:
			/* This is fine */
			अवरोध;
		हाल CC_PINS_SLIM:
			अगर (new_drvdata->std_bodies & CC_STD_NIST) अणु
				dev_warn(dev, "703 mode forced due to HW configuration.\n");
				new_drvdata->std_bodies = CC_STD_OSCCA;
			पूर्ण
			अवरोध;
		शेष:
			dev_err(dev, "Unsupported engines configuration.\n");
			rc = -EINVAL;
			जाओ post_pm_err;
		पूर्ण

		/* Check security disable state */
		val = cc_ioपढ़ो(new_drvdata, CC_REG(SECURITY_DISABLED));
		val &= CC_SECURITY_DISABLED_MASK;
		new_drvdata->sec_disabled |= !!val;

		अगर (!new_drvdata->sec_disabled) अणु
			new_drvdata->comp_mask |= CC_CPP_SM4_ABORT_MASK;
			अगर (new_drvdata->std_bodies & CC_STD_NIST)
				new_drvdata->comp_mask |= CC_CPP_AES_ABORT_MASK;
		पूर्ण
	पूर्ण

	अगर (new_drvdata->sec_disabled)
		dev_info(dev, "Security Disabled mode is in effect. Security functions disabled.\n");

	/* Display HW versions */
	dev_info(dev, "ARM CryptoCell %s Driver: HW version 0x%08X/0x%8X, Driver version %s\n",
		 hw_rev->name, hw_rev_pidr, sig_cidr, DRV_MODULE_VERSION);
	/* रेजिस्टर the driver isr function */
	rc = devm_request_irq(dev, irq, cc_isr, IRQF_SHARED, "ccree",
			      new_drvdata);
	अगर (rc) अणु
		dev_err(dev, "Could not register to interrupt %d\n", irq);
		जाओ post_pm_err;
	पूर्ण
	dev_dbg(dev, "Registered to IRQ: %d\n", irq);

	init_cc_cache_params(new_drvdata);

	rc = init_cc_regs(new_drvdata);
	अगर (rc) अणु
		dev_err(dev, "init_cc_regs failed\n");
		जाओ post_pm_err;
	पूर्ण

	rc = cc_debugfs_init(new_drvdata);
	अगर (rc) अणु
		dev_err(dev, "Failed registering debugfs interface\n");
		जाओ post_regs_err;
	पूर्ण

	rc = cc_fips_init(new_drvdata);
	अगर (rc) अणु
		dev_err(dev, "cc_fips_init failed 0x%x\n", rc);
		जाओ post_debugfs_err;
	पूर्ण
	rc = cc_sram_mgr_init(new_drvdata);
	अगर (rc) अणु
		dev_err(dev, "cc_sram_mgr_init failed\n");
		जाओ post_fips_init_err;
	पूर्ण

	new_drvdata->mlli_sram_addr =
		cc_sram_alloc(new_drvdata, MAX_MLLI_BUFF_SIZE);
	अगर (new_drvdata->mlli_sram_addr == शून्य_SRAM_ADDR) अणु
		rc = -ENOMEM;
		जाओ post_fips_init_err;
	पूर्ण

	rc = cc_req_mgr_init(new_drvdata);
	अगर (rc) अणु
		dev_err(dev, "cc_req_mgr_init failed\n");
		जाओ post_fips_init_err;
	पूर्ण

	rc = cc_buffer_mgr_init(new_drvdata);
	अगर (rc) अणु
		dev_err(dev, "cc_buffer_mgr_init failed\n");
		जाओ post_req_mgr_err;
	पूर्ण

	/* Allocate crypto algs */
	rc = cc_cipher_alloc(new_drvdata);
	अगर (rc) अणु
		dev_err(dev, "cc_cipher_alloc failed\n");
		जाओ post_buf_mgr_err;
	पूर्ण

	/* hash must be allocated beक्रमe aead since hash exports APIs */
	rc = cc_hash_alloc(new_drvdata);
	अगर (rc) अणु
		dev_err(dev, "cc_hash_alloc failed\n");
		जाओ post_cipher_err;
	पूर्ण

	rc = cc_aead_alloc(new_drvdata);
	अगर (rc) अणु
		dev_err(dev, "cc_aead_alloc failed\n");
		जाओ post_hash_err;
	पूर्ण

	/* If we got here and FIPS mode is enabled
	 * it means all FIPS test passed, so let TEE
	 * know we're good.
	 */
	cc_set_ree_fips_status(new_drvdata, true);

	pm_runसमय_put(dev);
	वापस 0;

post_hash_err:
	cc_hash_मुक्त(new_drvdata);
post_cipher_err:
	cc_cipher_मुक्त(new_drvdata);
post_buf_mgr_err:
	 cc_buffer_mgr_fini(new_drvdata);
post_req_mgr_err:
	cc_req_mgr_fini(new_drvdata);
post_fips_init_err:
	cc_fips_fini(new_drvdata);
post_debugfs_err:
	cc_debugfs_fini(new_drvdata);
post_regs_err:
	fini_cc_regs(new_drvdata);
post_pm_err:
	pm_runसमय_put_noidle(dev);
	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	clk_disable_unprepare(new_drvdata->clk);
	वापस rc;
पूर्ण

व्योम fini_cc_regs(काष्ठा cc_drvdata *drvdata)
अणु
	/* Mask all पूर्णांकerrupts */
	cc_ioग_लिखो(drvdata, CC_REG(HOST_IMR), 0xFFFFFFFF);
पूर्ण

अटल व्योम cleanup_cc_resources(काष्ठा platक्रमm_device *plat_dev)
अणु
	काष्ठा device *dev = &plat_dev->dev;
	काष्ठा cc_drvdata *drvdata =
		(काष्ठा cc_drvdata *)platक्रमm_get_drvdata(plat_dev);

	cc_aead_मुक्त(drvdata);
	cc_hash_मुक्त(drvdata);
	cc_cipher_मुक्त(drvdata);
	cc_buffer_mgr_fini(drvdata);
	cc_req_mgr_fini(drvdata);
	cc_fips_fini(drvdata);
	cc_debugfs_fini(drvdata);
	fini_cc_regs(drvdata);
	pm_runसमय_put_noidle(dev);
	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	clk_disable_unprepare(drvdata->clk);
पूर्ण

अचिन्हित पूर्णांक cc_get_शेष_hash_len(काष्ठा cc_drvdata *drvdata)
अणु
	अगर (drvdata->hw_rev >= CC_HW_REV_712)
		वापस HASH_LEN_SIZE_712;
	अन्यथा
		वापस HASH_LEN_SIZE_630;
पूर्ण

अटल पूर्णांक ccree_probe(काष्ठा platक्रमm_device *plat_dev)
अणु
	पूर्णांक rc;
	काष्ठा device *dev = &plat_dev->dev;

	/* Map रेजिस्टरs space */
	rc = init_cc_resources(plat_dev);
	अगर (rc)
		वापस rc;

	dev_info(dev, "ARM ccree device initialized\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ccree_हटाओ(काष्ठा platक्रमm_device *plat_dev)
अणु
	काष्ठा device *dev = &plat_dev->dev;

	dev_dbg(dev, "Releasing ccree resources...\n");

	cleanup_cc_resources(plat_dev);

	dev_info(dev, "ARM ccree device terminated\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ccree_driver = अणु
	.driver = अणु
		   .name = "ccree",
		   .of_match_table = arm_ccree_dev_of_match,
#अगर_घोषित CONFIG_PM
		   .pm = &ccree_pm,
#पूर्ण_अगर
	पूर्ण,
	.probe = ccree_probe,
	.हटाओ = ccree_हटाओ,
पूर्ण;

अटल पूर्णांक __init ccree_init(व्योम)
अणु
	cc_debugfs_global_init();

	वापस platक्रमm_driver_रेजिस्टर(&ccree_driver);
पूर्ण
module_init(ccree_init);

अटल व्योम __निकास ccree_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ccree_driver);
	cc_debugfs_global_fini();
पूर्ण
module_निकास(ccree_निकास);

/* Module description */
MODULE_DESCRIPTION("ARM TrustZone CryptoCell REE Driver");
MODULE_VERSION(DRV_MODULE_VERSION);
MODULE_AUTHOR("ARM");
MODULE_LICENSE("GPL v2");
