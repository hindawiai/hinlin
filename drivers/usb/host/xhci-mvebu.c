<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Marvell
 * Author: Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/mbus.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>

#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश "xhci-mvebu.h"
#समावेश "xhci.h"

#घोषणा USB3_MAX_WINDOWS	4
#घोषणा USB3_WIN_CTRL(w)	(0x0 + ((w) * 8))
#घोषणा USB3_WIN_BASE(w)	(0x4 + ((w) * 8))

अटल व्योम xhci_mvebu_mbus_config(व्योम __iomem *base,
			स्थिर काष्ठा mbus_dram_target_info *dram)
अणु
	पूर्णांक win;

	/* Clear all existing winकरोws */
	क्रम (win = 0; win < USB3_MAX_WINDOWS; win++) अणु
		ग_लिखोl(0, base + USB3_WIN_CTRL(win));
		ग_लिखोl(0, base + USB3_WIN_BASE(win));
	पूर्ण

	/* Program each DRAM CS in a seperate winकरोw */
	क्रम (win = 0; win < dram->num_cs; win++) अणु
		स्थिर काष्ठा mbus_dram_winकरोw *cs = dram->cs + win;

		ग_लिखोl(((cs->size - 1) & 0xffff0000) | (cs->mbus_attr << 8) |
		       (dram->mbus_dram_target_id << 4) | 1,
		       base + USB3_WIN_CTRL(win));

		ग_लिखोl((cs->base & 0xffff0000), base + USB3_WIN_BASE(win));
	पूर्ण
पूर्ण

पूर्णांक xhci_mvebu_mbus_init_quirk(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा device *dev = hcd->self.controller;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource	*res;
	व्योम __iomem *base;
	स्थिर काष्ठा mbus_dram_target_info *dram;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res)
		वापस -ENODEV;

	/*
	 * We करोn't use devm_ioremap() because this mapping should
	 * only exists क्रम the duration of this probe function.
	 */
	base = ioremap(res->start, resource_size(res));
	अगर (!base)
		वापस -ENODEV;

	dram = mv_mbus_dram_info();
	xhci_mvebu_mbus_config(base, dram);

	/*
	 * This memory area was only needed to configure the MBus
	 * winकरोws, and is thereक्रमe no दीर्घer useful.
	 */
	iounmap(base);

	वापस 0;
पूर्ण

पूर्णांक xhci_mvebu_a3700_plat_setup(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	काष्ठा device *dev = hcd->self.controller;
	काष्ठा phy *phy;
	पूर्णांक ret;

	/* Old bindings miss the PHY handle */
	phy = of_phy_get(dev->of_node, "usb3-phy");
	अगर (IS_ERR(phy) && PTR_ERR(phy) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अन्यथा अगर (IS_ERR(phy))
		जाओ phy_out;

	ret = phy_init(phy);
	अगर (ret)
		जाओ phy_put;

	ret = phy_set_mode(phy, PHY_MODE_USB_HOST_SS);
	अगर (ret)
		जाओ phy_निकास;

	ret = phy_घातer_on(phy);
	अगर (ret == -EOPNOTSUPP) अणु
		/* Skip initializatin of XHCI PHY when it is unsupported by firmware */
		dev_warn(dev, "PHY unsupported by firmware\n");
		xhci->quirks |= XHCI_SKIP_PHY_INIT;
	पूर्ण
	अगर (ret)
		जाओ phy_निकास;

	phy_घातer_off(phy);
phy_निकास:
	phy_निकास(phy);
phy_put:
	of_phy_put(phy);
phy_out:

	वापस 0;
पूर्ण

पूर्णांक xhci_mvebu_a3700_init_quirk(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);

	/* Without reset on resume, the HC won't work at all */
	xhci->quirks |= XHCI_RESET_ON_RESUME;

	वापस 0;
पूर्ण
