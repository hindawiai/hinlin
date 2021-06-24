<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_BCM47XX_WDT_H_
#घोषणा LINUX_BCM47XX_WDT_H_

#समावेश <linux/समयr.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>


काष्ठा bcm47xx_wdt अणु
	u32 (*समयr_set)(काष्ठा bcm47xx_wdt *, u32);
	u32 (*समयr_set_ms)(काष्ठा bcm47xx_wdt *, u32);
	u32 max_समयr_ms;

	व्योम *driver_data;

	काष्ठा watchकरोg_device wdd;

	काष्ठा समयr_list soft_समयr;
	atomic_t soft_ticks;
पूर्ण;

अटल अंतरभूत व्योम *bcm47xx_wdt_get_drvdata(काष्ठा bcm47xx_wdt *wdt)
अणु
	वापस wdt->driver_data;
पूर्ण
#पूर्ण_अगर /* LINUX_BCM47XX_WDT_H_ */
