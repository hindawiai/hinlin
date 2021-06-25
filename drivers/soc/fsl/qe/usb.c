<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * QE USB routines
 *
 * Copyright 2006 Freescale Semiconductor, Inc.
 *               Shlomi Gridish <gridish@मुक्तscale.com>
 *               Jerry Huang <Chang-Ming.Huang@मुक्तscale.com>
 * Copyright (c) MontaVista Software, Inc. 2008.
 *               Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <soc/fsl/qe/immap_qe.h>
#समावेश <soc/fsl/qe/qe.h>

पूर्णांक qe_usb_घड़ी_set(क्रमागत qe_घड़ी clk, पूर्णांक rate)
अणु
	काष्ठा qe_mux __iomem *mux = &qe_immr->qmx;
	अचिन्हित दीर्घ flags;
	u32 val;

	चयन (clk) अणु
	हाल QE_CLK3:  val = QE_CMXGCR_USBCS_CLK3;  अवरोध;
	हाल QE_CLK5:  val = QE_CMXGCR_USBCS_CLK5;  अवरोध;
	हाल QE_CLK7:  val = QE_CMXGCR_USBCS_CLK7;  अवरोध;
	हाल QE_CLK9:  val = QE_CMXGCR_USBCS_CLK9;  अवरोध;
	हाल QE_CLK13: val = QE_CMXGCR_USBCS_CLK13; अवरोध;
	हाल QE_CLK17: val = QE_CMXGCR_USBCS_CLK17; अवरोध;
	हाल QE_CLK19: val = QE_CMXGCR_USBCS_CLK19; अवरोध;
	हाल QE_CLK21: val = QE_CMXGCR_USBCS_CLK21; अवरोध;
	हाल QE_BRG9:  val = QE_CMXGCR_USBCS_BRG9;  अवरोध;
	हाल QE_BRG10: val = QE_CMXGCR_USBCS_BRG10; अवरोध;
	शेष:
		pr_err("%s: requested unknown clock %d\n", __func__, clk);
		वापस -EINVAL;
	पूर्ण

	अगर (qe_घड़ी_is_brg(clk))
		qe_setbrg(clk, rate, 1);

	spin_lock_irqsave(&cmxgcr_lock, flags);

	qe_clrsetbits_be32(&mux->cmxgcr, QE_CMXGCR_USBCS, val);

	spin_unlock_irqrestore(&cmxgcr_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(qe_usb_घड़ी_set);
