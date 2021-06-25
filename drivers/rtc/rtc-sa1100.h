<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __RTC_SA1100_H__
#घोषणा __RTC_SA1100_H__

#समावेश <linux/kernel.h>

काष्ठा clk;
काष्ठा platक्रमm_device;

काष्ठा sa1100_rtc अणु
	spinlock_t		lock;
	व्योम __iomem		*rcnr;
	व्योम __iomem		*rtar;
	व्योम __iomem		*rtsr;
	व्योम __iomem		*rttr;
	पूर्णांक			irq_1hz;
	पूर्णांक			irq_alarm;
	काष्ठा rtc_device	*rtc;
	काष्ठा clk		*clk;
पूर्ण;

पूर्णांक sa1100_rtc_init(काष्ठा platक्रमm_device *pdev, काष्ठा sa1100_rtc *info);

#पूर्ण_अगर
