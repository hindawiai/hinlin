<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ulpi.c - DesignWare USB3 Controller's ULPI PHY पूर्णांकerface
 *
 * Copyright (C) 2015 Intel Corporation
 *
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/समय64.h>
#समावेश <linux/ulpi/regs.h>

#समावेश "core.h"
#समावेश "io.h"

#घोषणा DWC3_ULPI_ADDR(a) \
		((a >= ULPI_EXT_VENDOR_SPECIFIC) ? \
		DWC3_GUSB2PHYACC_ADDR(ULPI_ACCESS_EXTENDED) | \
		DWC3_GUSB2PHYACC_EXTEND_ADDR(a) : DWC3_GUSB2PHYACC_ADDR(a))

#घोषणा DWC3_ULPI_BASE_DELAY	DIV_ROUND_UP(NSEC_PER_SEC, 60000000L)

अटल पूर्णांक dwc3_ulpi_busyloop(काष्ठा dwc3 *dwc, u8 addr, bool पढ़ो)
अणु
	अचिन्हित दीर्घ ns = 5L * DWC3_ULPI_BASE_DELAY;
	अचिन्हित पूर्णांक count = 10000;
	u32 reg;

	अगर (addr >= ULPI_EXT_VENDOR_SPECIFIC)
		ns += DWC3_ULPI_BASE_DELAY;

	अगर (पढ़ो)
		ns += DWC3_ULPI_BASE_DELAY;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUSB2PHYCFG(0));
	अगर (reg & DWC3_GUSB2PHYCFG_SUSPHY)
		usleep_range(1000, 1200);

	जबतक (count--) अणु
		ndelay(ns);
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUSB2PHYACC(0));
		अगर (reg & DWC3_GUSB2PHYACC_DONE)
			वापस 0;
		cpu_relax();
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक dwc3_ulpi_पढ़ो(काष्ठा device *dev, u8 addr)
अणु
	काष्ठा dwc3 *dwc = dev_get_drvdata(dev);
	u32 reg;
	पूर्णांक ret;

	reg = DWC3_GUSB2PHYACC_NEWREGREQ | DWC3_ULPI_ADDR(addr);
	dwc3_ग_लिखोl(dwc->regs, DWC3_GUSB2PHYACC(0), reg);

	ret = dwc3_ulpi_busyloop(dwc, addr, true);
	अगर (ret)
		वापस ret;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUSB2PHYACC(0));

	वापस DWC3_GUSB2PHYACC_DATA(reg);
पूर्ण

अटल पूर्णांक dwc3_ulpi_ग_लिखो(काष्ठा device *dev, u8 addr, u8 val)
अणु
	काष्ठा dwc3 *dwc = dev_get_drvdata(dev);
	u32 reg;

	reg = DWC3_GUSB2PHYACC_NEWREGREQ | DWC3_ULPI_ADDR(addr);
	reg |= DWC3_GUSB2PHYACC_WRITE | val;
	dwc3_ग_लिखोl(dwc->regs, DWC3_GUSB2PHYACC(0), reg);

	वापस dwc3_ulpi_busyloop(dwc, addr, false);
पूर्ण

अटल स्थिर काष्ठा ulpi_ops dwc3_ulpi_ops = अणु
	.पढ़ो = dwc3_ulpi_पढ़ो,
	.ग_लिखो = dwc3_ulpi_ग_लिखो,
पूर्ण;

पूर्णांक dwc3_ulpi_init(काष्ठा dwc3 *dwc)
अणु
	/* Register the पूर्णांकerface */
	dwc->ulpi = ulpi_रेजिस्टर_पूर्णांकerface(dwc->dev, &dwc3_ulpi_ops);
	अगर (IS_ERR(dwc->ulpi)) अणु
		dev_err(dwc->dev, "failed to register ULPI interface");
		वापस PTR_ERR(dwc->ulpi);
	पूर्ण

	वापस 0;
पूर्ण

व्योम dwc3_ulpi_निकास(काष्ठा dwc3 *dwc)
अणु
	अगर (dwc->ulpi) अणु
		ulpi_unरेजिस्टर_पूर्णांकerface(dwc->ulpi);
		dwc->ulpi = शून्य;
	पूर्ण
पूर्ण
