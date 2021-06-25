<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2014-2019 MediaTek Inc.
 *
 * Author: Tianping.Fang <tianping.fang@mediatek.com>
 *        Sean Wang <sean.wang@mediatek.com>
 */

#अगर_अघोषित _LINUX_MFD_MT6397_RTC_H_
#घोषणा _LINUX_MFD_MT6397_RTC_H_

#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>

#घोषणा RTC_BBPU               0x0000
#घोषणा RTC_BBPU_CBUSY         BIT(6)
#घोषणा RTC_BBPU_KEY            (0x43 << 8)

#घोषणा RTC_WRTGR_MT6358       0x003a
#घोषणा RTC_WRTGR_MT6397       0x003c
#घोषणा RTC_WRTGR_MT6323       RTC_WRTGR_MT6397

#घोषणा RTC_IRQ_STA            0x0002
#घोषणा RTC_IRQ_STA_AL         BIT(0)
#घोषणा RTC_IRQ_STA_LP         BIT(3)

#घोषणा RTC_IRQ_EN             0x0004
#घोषणा RTC_IRQ_EN_AL          BIT(0)
#घोषणा RTC_IRQ_EN_ONESHOT     BIT(2)
#घोषणा RTC_IRQ_EN_LP          BIT(3)
#घोषणा RTC_IRQ_EN_ONESHOT_AL  (RTC_IRQ_EN_ONESHOT | RTC_IRQ_EN_AL)

#घोषणा RTC_AL_MASK            0x0008
#घोषणा RTC_AL_MASK_DOW                BIT(4)

#घोषणा RTC_TC_SEC             0x000a
/* Min, Hour, Dom... रेजिस्टर offset to RTC_TC_SEC */
#घोषणा RTC_OFFSET_SEC         0
#घोषणा RTC_OFFSET_MIN         1
#घोषणा RTC_OFFSET_HOUR                2
#घोषणा RTC_OFFSET_DOM         3
#घोषणा RTC_OFFSET_DOW         4
#घोषणा RTC_OFFSET_MTH         5
#घोषणा RTC_OFFSET_YEAR                6
#घोषणा RTC_OFFSET_COUNT       7

#घोषणा RTC_AL_SEC             0x0018

#घोषणा RTC_AL_SEC_MASK        0x003f
#घोषणा RTC_AL_MIN_MASK        0x003f
#घोषणा RTC_AL_HOU_MASK        0x001f
#घोषणा RTC_AL_DOM_MASK        0x001f
#घोषणा RTC_AL_DOW_MASK        0x0007
#घोषणा RTC_AL_MTH_MASK        0x000f
#घोषणा RTC_AL_YEA_MASK        0x007f

#घोषणा RTC_PDN2               0x002e
#घोषणा RTC_PDN2_PWRON_ALARM   BIT(4)

#घोषणा RTC_MIN_YEAR           1968
#घोषणा RTC_BASE_YEAR          1900
#घोषणा RTC_NUM_YEARS          128
#घोषणा RTC_MIN_YEAR_OFFSET    (RTC_MIN_YEAR - RTC_BASE_YEAR)

#घोषणा MTK_RTC_POLL_DELAY_US  10
#घोषणा MTK_RTC_POLL_TIMEOUT   (jअगरfies_to_usecs(HZ))

काष्ठा mtk_rtc_data अणु
	u32                     wrtgr;
पूर्ण;

काष्ठा mt6397_rtc अणु
	काष्ठा rtc_device       *rtc_dev;

	/* Protect रेजिस्टर access from multiple tasks */
	काष्ठा mutex            lock;
	काष्ठा regmap           *regmap;
	पूर्णांक                     irq;
	u32                     addr_base;
	स्थिर काष्ठा mtk_rtc_data *data;
पूर्ण;

#पूर्ण_अगर /* _LINUX_MFD_MT6397_RTC_H_ */
