<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

#समावेश <linux/kernel.h>
#समावेश <linux/fips.h>
#समावेश <linux/notअगरier.h>

#समावेश "cc_driver.h"
#समावेश "cc_fips.h"

अटल व्योम fips_dsr(अचिन्हित दीर्घ devarg);

काष्ठा cc_fips_handle अणु
	काष्ठा tasklet_काष्ठा tasklet;
	काष्ठा notअगरier_block nb;
	काष्ठा cc_drvdata *drvdata;
पूर्ण;

/* The function called once at driver entry poपूर्णांक to check
 * whether TEE FIPS error occurred.
 */
अटल bool cc_get_tee_fips_status(काष्ठा cc_drvdata *drvdata)
अणु
	u32 reg;

	reg = cc_ioपढ़ो(drvdata, CC_REG(GPR_HOST));
	/* Did the TEE report status? */
	अगर (reg & CC_FIPS_SYNC_TEE_STATUS)
		/* Yes. Is it OK? */
		वापस (reg & CC_FIPS_SYNC_MODULE_OK);

	/* No. It's either not in use or will be reported later */
	वापस true;
पूर्ण

/*
 * This function should push the FIPS REE library status towards the TEE library
 * by writing the error state to HOST_GPR0 रेजिस्टर.
 */
व्योम cc_set_ree_fips_status(काष्ठा cc_drvdata *drvdata, bool status)
अणु
	पूर्णांक val = CC_FIPS_SYNC_REE_STATUS;

	अगर (drvdata->hw_rev < CC_HW_REV_712)
		वापस;

	val |= (status ? CC_FIPS_SYNC_MODULE_OK : CC_FIPS_SYNC_MODULE_ERROR);

	cc_ioग_लिखो(drvdata, CC_REG(HOST_GPR0), val);
पूर्ण

/* Push REE side FIPS test failure to TEE side */
अटल पूर्णांक cc_ree_fips_failure(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ unused1,
			       व्योम *unused2)
अणु
	काष्ठा cc_fips_handle *fips_h =
				container_of(nb, काष्ठा cc_fips_handle, nb);
	काष्ठा cc_drvdata *drvdata = fips_h->drvdata;
	काष्ठा device *dev = drvdata_to_dev(drvdata);

	cc_set_ree_fips_status(drvdata, false);
	dev_info(dev, "Notifying TEE of FIPS test failure...\n");

	वापस NOTIFY_OK;
पूर्ण

व्योम cc_fips_fini(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा cc_fips_handle *fips_h = drvdata->fips_handle;

	अगर (drvdata->hw_rev < CC_HW_REV_712 || !fips_h)
		वापस;

	atomic_notअगरier_chain_unरेजिस्टर(&fips_fail_notअगर_chain, &fips_h->nb);

	/* Kill tasklet */
	tasklet_समाप्त(&fips_h->tasklet);
	drvdata->fips_handle = शून्य;
पूर्ण

व्योम fips_handler(काष्ठा cc_drvdata *drvdata)
अणु
	काष्ठा cc_fips_handle *fips_handle_ptr = drvdata->fips_handle;

	अगर (drvdata->hw_rev < CC_HW_REV_712)
		वापस;

	tasklet_schedule(&fips_handle_ptr->tasklet);
पूर्ण

अटल अंतरभूत व्योम tee_fips_error(काष्ठा device *dev)
अणु
	अगर (fips_enabled)
		panic("ccree: TEE reported cryptographic error in fips mode!\n");
	अन्यथा
		dev_err(dev, "TEE reported error!\n");
पूर्ण

/*
 * This function check अगर cryptocell tee fips error occurred
 * and in such हाल triggers प्रणाली error
 */
व्योम cc_tee_handle_fips_error(काष्ठा cc_drvdata *p_drvdata)
अणु
	काष्ठा device *dev = drvdata_to_dev(p_drvdata);

	अगर (!cc_get_tee_fips_status(p_drvdata))
		tee_fips_error(dev);
पूर्ण

/* Deferred service handler, run as पूर्णांकerrupt-fired tasklet */
अटल व्योम fips_dsr(अचिन्हित दीर्घ devarg)
अणु
	काष्ठा cc_drvdata *drvdata = (काष्ठा cc_drvdata *)devarg;
	u32 irq, val;

	irq = (drvdata->irq & (CC_GPR0_IRQ_MASK));

	अगर (irq) अणु
		cc_tee_handle_fips_error(drvdata);
	पूर्ण

	/* after verअगरying that there is nothing to करो,
	 * unmask AXI completion पूर्णांकerrupt.
	 */
	val = (CC_REG(HOST_IMR) & ~irq);
	cc_ioग_लिखो(drvdata, CC_REG(HOST_IMR), val);
पूर्ण

/* The function called once at driver entry poपूर्णांक .*/
पूर्णांक cc_fips_init(काष्ठा cc_drvdata *p_drvdata)
अणु
	काष्ठा cc_fips_handle *fips_h;
	काष्ठा device *dev = drvdata_to_dev(p_drvdata);

	अगर (p_drvdata->hw_rev < CC_HW_REV_712)
		वापस 0;

	fips_h = devm_kzalloc(dev, माप(*fips_h), GFP_KERNEL);
	अगर (!fips_h)
		वापस -ENOMEM;

	p_drvdata->fips_handle = fips_h;

	dev_dbg(dev, "Initializing fips tasklet\n");
	tasklet_init(&fips_h->tasklet, fips_dsr, (अचिन्हित दीर्घ)p_drvdata);
	fips_h->drvdata = p_drvdata;
	fips_h->nb.notअगरier_call = cc_ree_fips_failure;
	atomic_notअगरier_chain_रेजिस्टर(&fips_fail_notअगर_chain, &fips_h->nb);

	cc_tee_handle_fips_error(p_drvdata);

	वापस 0;
पूर्ण
