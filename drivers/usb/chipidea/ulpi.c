<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 Linaro Ltd.
 */

#समावेश <linux/device.h>
#समावेश <linux/usb/chipidea.h>
#समावेश <linux/ulpi/पूर्णांकerface.h>

#समावेश "ci.h"

#घोषणा ULPI_WAKEUP		BIT(31)
#घोषणा ULPI_RUN		BIT(30)
#घोषणा ULPI_WRITE		BIT(29)
#घोषणा ULPI_SYNC_STATE		BIT(27)
#घोषणा ULPI_ADDR(n)		((n) << 16)
#घोषणा ULPI_DATA(n)		(n)

अटल पूर्णांक ci_ulpi_रुको(काष्ठा ci_hdrc *ci, u32 mask)
अणु
	अचिन्हित दीर्घ usec = 10000;

	जबतक (usec--) अणु
		अगर (!hw_पढ़ो(ci, OP_ULPI_VIEWPORT, mask))
			वापस 0;

		udelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक ci_ulpi_पढ़ो(काष्ठा device *dev, u8 addr)
अणु
	काष्ठा ci_hdrc *ci = dev_get_drvdata(dev);
	पूर्णांक ret;

	hw_ग_लिखो(ci, OP_ULPI_VIEWPORT, 0xffffffff, ULPI_WRITE | ULPI_WAKEUP);
	ret = ci_ulpi_रुको(ci, ULPI_WAKEUP);
	अगर (ret)
		वापस ret;

	hw_ग_लिखो(ci, OP_ULPI_VIEWPORT, 0xffffffff, ULPI_RUN | ULPI_ADDR(addr));
	ret = ci_ulpi_रुको(ci, ULPI_RUN);
	अगर (ret)
		वापस ret;

	वापस hw_पढ़ो(ci, OP_ULPI_VIEWPORT, GENMASK(15, 8)) >> 8;
पूर्ण

अटल पूर्णांक ci_ulpi_ग_लिखो(काष्ठा device *dev, u8 addr, u8 val)
अणु
	काष्ठा ci_hdrc *ci = dev_get_drvdata(dev);
	पूर्णांक ret;

	hw_ग_लिखो(ci, OP_ULPI_VIEWPORT, 0xffffffff, ULPI_WRITE | ULPI_WAKEUP);
	ret = ci_ulpi_रुको(ci, ULPI_WAKEUP);
	अगर (ret)
		वापस ret;

	hw_ग_लिखो(ci, OP_ULPI_VIEWPORT, 0xffffffff,
		 ULPI_RUN | ULPI_WRITE | ULPI_ADDR(addr) | val);
	वापस ci_ulpi_रुको(ci, ULPI_RUN);
पूर्ण

पूर्णांक ci_ulpi_init(काष्ठा ci_hdrc *ci)
अणु
	अगर (ci->platdata->phy_mode != USBPHY_INTERFACE_MODE_ULPI)
		वापस 0;

	/*
	 * Set PORTSC correctly so we can पढ़ो/ग_लिखो ULPI रेजिस्टरs क्रम
	 * identअगरication purposes
	 */
	hw_phymode_configure(ci);

	ci->ulpi_ops.पढ़ो = ci_ulpi_पढ़ो;
	ci->ulpi_ops.ग_लिखो = ci_ulpi_ग_लिखो;
	ci->ulpi = ulpi_रेजिस्टर_पूर्णांकerface(ci->dev, &ci->ulpi_ops);
	अगर (IS_ERR(ci->ulpi))
		dev_err(ci->dev, "failed to register ULPI interface");

	वापस PTR_ERR_OR_ZERO(ci->ulpi);
पूर्ण

व्योम ci_ulpi_निकास(काष्ठा ci_hdrc *ci)
अणु
	अगर (ci->ulpi) अणु
		ulpi_unरेजिस्टर_पूर्णांकerface(ci->ulpi);
		ci->ulpi = शून्य;
	पूर्ण
पूर्ण

पूर्णांक ci_ulpi_resume(काष्ठा ci_hdrc *ci)
अणु
	पूर्णांक cnt = 100000;

	अगर (ci->platdata->phy_mode != USBPHY_INTERFACE_MODE_ULPI)
		वापस 0;

	जबतक (cnt-- > 0) अणु
		अगर (hw_पढ़ो(ci, OP_ULPI_VIEWPORT, ULPI_SYNC_STATE))
			वापस 0;
		udelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण
