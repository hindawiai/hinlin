<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2010 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modअगरied under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#अगर_अघोषित __TEGRA_USB_PHY_H
#घोषणा __TEGRA_USB_PHY_H

#समावेश <linux/clk.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/reset.h>
#समावेश <linux/usb/otg.h>

/*
 * uपंचांगi_pll_config_in_car_module: true अगर the UTMI PLL configuration रेजिस्टरs
 *     should be set up by clk-tegra, false अगर by the PHY code
 * has_hostpc: true अगर the USB controller has the HOSTPC extension, which
 *     changes the location of the PHCD and PTS fields
 * requires_usbmode_setup: true अगर the USBMODE रेजिस्टर needs to be set to
 *      enter host mode
 * requires_extra_tuning_parameters: true अगर xcvr_hsslew, hssquelch_level
 *      and hsdiscon_level should be set क्रम adequate संकेत quality
 */

काष्ठा tegra_phy_soc_config अणु
	bool uपंचांगi_pll_config_in_car_module;
	bool has_hostpc;
	bool requires_usbmode_setup;
	bool requires_extra_tuning_parameters;
पूर्ण;

काष्ठा tegra_uपंचांगip_config अणु
	u8 hssync_start_delay;
	u8 elastic_limit;
	u8 idle_रुको_delay;
	u8 term_range_adj;
	bool xcvr_setup_use_fuses;
	u8 xcvr_setup;
	u8 xcvr_lsfslew;
	u8 xcvr_lsrslew;
	u8 xcvr_hsslew;
	u8 hssquelch_level;
	u8 hsdiscon_level;
पूर्ण;

क्रमागत tegra_usb_phy_port_speed अणु
	TEGRA_USB_PHY_PORT_SPEED_FULL = 0,
	TEGRA_USB_PHY_PORT_SPEED_LOW,
	TEGRA_USB_PHY_PORT_SPEED_HIGH,
पूर्ण;

काष्ठा tegra_xtal_freq;

काष्ठा tegra_usb_phy अणु
	पूर्णांक instance;
	स्थिर काष्ठा tegra_xtal_freq *freq;
	व्योम __iomem *regs;
	व्योम __iomem *pad_regs;
	काष्ठा clk *clk;
	काष्ठा clk *pll_u;
	काष्ठा clk *pad_clk;
	काष्ठा regulator *vbus;
	क्रमागत usb_dr_mode mode;
	व्योम *config;
	स्थिर काष्ठा tegra_phy_soc_config *soc_config;
	काष्ठा usb_phy *ulpi;
	काष्ठा usb_phy u_phy;
	bool is_legacy_phy;
	bool is_ulpi_phy;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा reset_control *pad_rst;
	bool wakeup_enabled;
	bool pad_wakeup;
	bool घातered_on;
पूर्ण;

व्योम tegra_usb_phy_preresume(काष्ठा usb_phy *phy);

व्योम tegra_usb_phy_postresume(काष्ठा usb_phy *phy);

व्योम tegra_ehci_phy_restore_start(काष्ठा usb_phy *phy,
				 क्रमागत tegra_usb_phy_port_speed port_speed);

व्योम tegra_ehci_phy_restore_end(काष्ठा usb_phy *phy);

#पूर्ण_अगर /* __TEGRA_USB_PHY_H */
