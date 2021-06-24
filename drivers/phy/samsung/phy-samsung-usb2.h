<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Samsung SoC USB 1.1/2.0 PHY driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Author: Kamil Debski <k.debski@samsung.com>
 */

#अगर_अघोषित _PHY_EXYNOS_USB2_H
#घोषणा _PHY_EXYNOS_USB2_H

#समावेश <linux/clk.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा KHZ 1000
#घोषणा MHZ (KHZ * KHZ)

काष्ठा samsung_usb2_phy_driver;
काष्ठा samsung_usb2_phy_instance;
काष्ठा samsung_usb2_phy_config;

काष्ठा samsung_usb2_phy_instance अणु
	स्थिर काष्ठा samsung_usb2_common_phy *cfg;
	काष्ठा phy *phy;
	काष्ठा samsung_usb2_phy_driver *drv;
	पूर्णांक पूर्णांक_cnt;
	पूर्णांक ext_cnt;
पूर्ण;

काष्ठा samsung_usb2_phy_driver अणु
	स्थिर काष्ठा samsung_usb2_phy_config *cfg;
	काष्ठा clk *clk;
	काष्ठा clk *ref_clk;
	काष्ठा regulator *vbus;
	अचिन्हित दीर्घ ref_rate;
	u32 ref_reg_val;
	काष्ठा device *dev;
	व्योम __iomem *reg_phy;
	काष्ठा regmap *reg_pmu;
	काष्ठा regmap *reg_sys;
	spinlock_t lock;
	काष्ठा samsung_usb2_phy_instance instances[];
पूर्ण;

काष्ठा samsung_usb2_common_phy अणु
	पूर्णांक (*घातer_on)(काष्ठा samsung_usb2_phy_instance *);
	पूर्णांक (*घातer_off)(काष्ठा samsung_usb2_phy_instance *);
	अचिन्हित पूर्णांक id;
	अक्षर *label;
पूर्ण;


काष्ठा samsung_usb2_phy_config अणु
	स्थिर काष्ठा samsung_usb2_common_phy *phys;
	पूर्णांक (*rate_to_clk)(अचिन्हित दीर्घ, u32 *);
	अचिन्हित पूर्णांक num_phys;
	bool has_mode_चयन;
	bool has_refclk_sel;
पूर्ण;

बाह्य स्थिर काष्ठा samsung_usb2_phy_config exynos3250_usb2_phy_config;
बाह्य स्थिर काष्ठा samsung_usb2_phy_config exynos4210_usb2_phy_config;
बाह्य स्थिर काष्ठा samsung_usb2_phy_config exynos4x12_usb2_phy_config;
बाह्य स्थिर काष्ठा samsung_usb2_phy_config exynos5250_usb2_phy_config;
बाह्य स्थिर काष्ठा samsung_usb2_phy_config exynos5420_usb2_phy_config;
बाह्य स्थिर काष्ठा samsung_usb2_phy_config s5pv210_usb2_phy_config;
#पूर्ण_अगर
