<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2016-2018 NXP
 * Copyright 2020 NXP
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/msi.h>
#समावेश <linux/fsl/mc.h>

#समावेश "dpaa2-ptp.h"

अटल पूर्णांक dpaa2_ptp_enable(काष्ठा ptp_घड़ी_info *ptp,
			    काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा ptp_qoriq *ptp_qoriq = container_of(ptp, काष्ठा ptp_qoriq, caps);
	काष्ठा fsl_mc_device *mc_dev;
	काष्ठा device *dev;
	u32 mask = 0;
	u32 bit;
	पूर्णांक err;

	dev = ptp_qoriq->dev;
	mc_dev = to_fsl_mc_device(dev);

	चयन (rq->type) अणु
	हाल PTP_CLK_REQ_EXTTS:
		चयन (rq->extts.index) अणु
		हाल 0:
			bit = DPRTC_EVENT_ETS1;
			अवरोध;
		हाल 1:
			bit = DPRTC_EVENT_ETS2;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (on)
			extts_clean_up(ptp_qoriq, rq->extts.index, false);
		अवरोध;
	हाल PTP_CLK_REQ_PPS:
		bit = DPRTC_EVENT_PPS;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	err = dprtc_get_irq_mask(mc_dev->mc_io, 0, mc_dev->mc_handle,
				 DPRTC_IRQ_INDEX, &mask);
	अगर (err < 0) अणु
		dev_err(dev, "dprtc_get_irq_mask(): %d\n", err);
		वापस err;
	पूर्ण

	अगर (on)
		mask |= bit;
	अन्यथा
		mask &= ~bit;

	err = dprtc_set_irq_mask(mc_dev->mc_io, 0, mc_dev->mc_handle,
				 DPRTC_IRQ_INDEX, mask);
	अगर (err < 0) अणु
		dev_err(dev, "dprtc_set_irq_mask(): %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info dpaa2_ptp_caps = अणु
	.owner		= THIS_MODULE,
	.name		= "DPAA2 PTP Clock",
	.max_adj	= 512000,
	.n_alarm	= 2,
	.n_ext_ts	= 2,
	.n_per_out	= 3,
	.n_pins		= 0,
	.pps		= 1,
	.adjfine	= ptp_qoriq_adjfine,
	.adjसमय	= ptp_qoriq_adjसमय,
	.समय_लो64	= ptp_qoriq_समय_लो,
	.समय_रखो64	= ptp_qoriq_समय_रखो,
	.enable		= dpaa2_ptp_enable,
पूर्ण;

अटल irqवापस_t dpaa2_ptp_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा ptp_qoriq *ptp_qoriq = priv;
	काष्ठा ptp_घड़ी_event event;
	काष्ठा fsl_mc_device *mc_dev;
	काष्ठा device *dev;
	u32 status = 0;
	पूर्णांक err;

	dev = ptp_qoriq->dev;
	mc_dev = to_fsl_mc_device(dev);

	err = dprtc_get_irq_status(mc_dev->mc_io, 0, mc_dev->mc_handle,
				   DPRTC_IRQ_INDEX, &status);
	अगर (unlikely(err)) अणु
		dev_err(dev, "dprtc_get_irq_status err %d\n", err);
		वापस IRQ_NONE;
	पूर्ण

	अगर (status & DPRTC_EVENT_PPS) अणु
		event.type = PTP_CLOCK_PPS;
		ptp_घड़ी_event(ptp_qoriq->घड़ी, &event);
	पूर्ण

	अगर (status & DPRTC_EVENT_ETS1)
		extts_clean_up(ptp_qoriq, 0, true);

	अगर (status & DPRTC_EVENT_ETS2)
		extts_clean_up(ptp_qoriq, 1, true);

	err = dprtc_clear_irq_status(mc_dev->mc_io, 0, mc_dev->mc_handle,
				     DPRTC_IRQ_INDEX, status);
	अगर (unlikely(err)) अणु
		dev_err(dev, "dprtc_clear_irq_status err %d\n", err);
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dpaa2_ptp_probe(काष्ठा fsl_mc_device *mc_dev)
अणु
	काष्ठा device *dev = &mc_dev->dev;
	काष्ठा fsl_mc_device_irq *irq;
	काष्ठा ptp_qoriq *ptp_qoriq;
	काष्ठा device_node *node;
	व्योम __iomem *base;
	पूर्णांक err;

	ptp_qoriq = devm_kzalloc(dev, माप(*ptp_qoriq), GFP_KERNEL);
	अगर (!ptp_qoriq)
		वापस -ENOMEM;

	err = fsl_mc_portal_allocate(mc_dev, 0, &mc_dev->mc_io);
	अगर (err) अणु
		अगर (err == -ENXIO)
			err = -EPROBE_DEFER;
		अन्यथा
			dev_err(dev, "fsl_mc_portal_allocate err %d\n", err);
		जाओ err_निकास;
	पूर्ण

	err = dprtc_खोलो(mc_dev->mc_io, 0, mc_dev->obj_desc.id,
			 &mc_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dprtc_open err %d\n", err);
		जाओ err_मुक्त_mcp;
	पूर्ण

	ptp_qoriq->dev = dev;

	node = of_find_compatible_node(शून्य, शून्य, "fsl,dpaa2-ptp");
	अगर (!node) अणु
		err = -ENODEV;
		जाओ err_बंद;
	पूर्ण

	dev->of_node = node;

	base = of_iomap(node, 0);
	अगर (!base) अणु
		err = -ENOMEM;
		जाओ err_बंद;
	पूर्ण

	err = fsl_mc_allocate_irqs(mc_dev);
	अगर (err) अणु
		dev_err(dev, "MC irqs allocation failed\n");
		जाओ err_unmap;
	पूर्ण

	irq = mc_dev->irqs[0];
	ptp_qoriq->irq = irq->msi_desc->irq;

	err = request_thपढ़ोed_irq(ptp_qoriq->irq, शून्य,
				   dpaa2_ptp_irq_handler_thपढ़ो,
				   IRQF_NO_SUSPEND | IRQF_ONESHOT,
				   dev_name(dev), ptp_qoriq);
	अगर (err < 0) अणु
		dev_err(dev, "devm_request_threaded_irq(): %d\n", err);
		जाओ err_मुक्त_mc_irq;
	पूर्ण

	err = dprtc_set_irq_enable(mc_dev->mc_io, 0, mc_dev->mc_handle,
				   DPRTC_IRQ_INDEX, 1);
	अगर (err < 0) अणु
		dev_err(dev, "dprtc_set_irq_enable(): %d\n", err);
		जाओ err_मुक्त_thपढ़ोed_irq;
	पूर्ण

	err = ptp_qoriq_init(ptp_qoriq, base, &dpaa2_ptp_caps);
	अगर (err)
		जाओ err_मुक्त_thपढ़ोed_irq;

	dpaa2_phc_index = ptp_qoriq->phc_index;
	dpaa2_ptp = ptp_qoriq;
	dev_set_drvdata(dev, ptp_qoriq);

	वापस 0;

err_मुक्त_thपढ़ोed_irq:
	मुक्त_irq(ptp_qoriq->irq, ptp_qoriq);
err_मुक्त_mc_irq:
	fsl_mc_मुक्त_irqs(mc_dev);
err_unmap:
	iounmap(base);
err_बंद:
	dprtc_बंद(mc_dev->mc_io, 0, mc_dev->mc_handle);
err_मुक्त_mcp:
	fsl_mc_portal_मुक्त(mc_dev->mc_io);
err_निकास:
	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_ptp_हटाओ(काष्ठा fsl_mc_device *mc_dev)
अणु
	काष्ठा device *dev = &mc_dev->dev;
	काष्ठा ptp_qoriq *ptp_qoriq;

	ptp_qoriq = dev_get_drvdata(dev);

	dpaa2_phc_index = -1;
	ptp_qoriq_मुक्त(ptp_qoriq);

	fsl_mc_मुक्त_irqs(mc_dev);
	dprtc_बंद(mc_dev->mc_io, 0, mc_dev->mc_handle);
	fsl_mc_portal_मुक्त(mc_dev->mc_io);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fsl_mc_device_id dpaa2_ptp_match_id_table[] = अणु
	अणु
		.venकरोr = FSL_MC_VENDOR_FREESCALE,
		.obj_type = "dprtc",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(fslmc, dpaa2_ptp_match_id_table);

अटल काष्ठा fsl_mc_driver dpaa2_ptp_drv = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.owner = THIS_MODULE,
	पूर्ण,
	.probe = dpaa2_ptp_probe,
	.हटाओ = dpaa2_ptp_हटाओ,
	.match_id_table = dpaa2_ptp_match_id_table,
पूर्ण;

module_fsl_mc_driver(dpaa2_ptp_drv);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("DPAA2 PTP Clock Driver");
