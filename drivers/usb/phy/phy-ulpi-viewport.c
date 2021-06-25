<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 Google, Inc.
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/usb.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/ulpi.h>

#घोषणा ULPI_VIEW_WAKEUP	(1 << 31)
#घोषणा ULPI_VIEW_RUN		(1 << 30)
#घोषणा ULPI_VIEW_WRITE		(1 << 29)
#घोषणा ULPI_VIEW_READ		(0 << 29)
#घोषणा ULPI_VIEW_ADDR(x)	(((x) & 0xff) << 16)
#घोषणा ULPI_VIEW_DATA_READ(x)	(((x) >> 8) & 0xff)
#घोषणा ULPI_VIEW_DATA_WRITE(x)	((x) & 0xff)

अटल पूर्णांक ulpi_viewport_रुको(व्योम __iomem *view, u32 mask)
अणु
	u32 val;

	वापस पढ़ोl_poll_समयout_atomic(view, val, !(val & mask), 1, 2000);
पूर्ण

अटल पूर्णांक ulpi_viewport_पढ़ो(काष्ठा usb_phy *otg, u32 reg)
अणु
	पूर्णांक ret;
	व्योम __iomem *view = otg->io_priv;

	ग_लिखोl(ULPI_VIEW_WAKEUP | ULPI_VIEW_WRITE, view);
	ret = ulpi_viewport_रुको(view, ULPI_VIEW_WAKEUP);
	अगर (ret)
		वापस ret;

	ग_लिखोl(ULPI_VIEW_RUN | ULPI_VIEW_READ | ULPI_VIEW_ADDR(reg), view);
	ret = ulpi_viewport_रुको(view, ULPI_VIEW_RUN);
	अगर (ret)
		वापस ret;

	वापस ULPI_VIEW_DATA_READ(पढ़ोl(view));
पूर्ण

अटल पूर्णांक ulpi_viewport_ग_लिखो(काष्ठा usb_phy *otg, u32 val, u32 reg)
अणु
	पूर्णांक ret;
	व्योम __iomem *view = otg->io_priv;

	ग_लिखोl(ULPI_VIEW_WAKEUP | ULPI_VIEW_WRITE, view);
	ret = ulpi_viewport_रुको(view, ULPI_VIEW_WAKEUP);
	अगर (ret)
		वापस ret;

	ग_लिखोl(ULPI_VIEW_RUN | ULPI_VIEW_WRITE | ULPI_VIEW_DATA_WRITE(val) |
						 ULPI_VIEW_ADDR(reg), view);

	वापस ulpi_viewport_रुको(view, ULPI_VIEW_RUN);
पूर्ण

काष्ठा usb_phy_io_ops ulpi_viewport_access_ops = अणु
	.पढ़ो	= ulpi_viewport_पढ़ो,
	.ग_लिखो	= ulpi_viewport_ग_लिखो,
पूर्ण;
EXPORT_SYMBOL_GPL(ulpi_viewport_access_ops);
