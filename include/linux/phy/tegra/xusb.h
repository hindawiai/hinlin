<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016, NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित PHY_TEGRA_XUSB_H
#घोषणा PHY_TEGRA_XUSB_H

काष्ठा tegra_xusb_padctl;
काष्ठा device;

काष्ठा tegra_xusb_padctl *tegra_xusb_padctl_get(काष्ठा device *dev);
व्योम tegra_xusb_padctl_put(काष्ठा tegra_xusb_padctl *padctl);

पूर्णांक tegra_xusb_padctl_usb3_save_context(काष्ठा tegra_xusb_padctl *padctl,
					अचिन्हित पूर्णांक port);
पूर्णांक tegra_xusb_padctl_hsic_set_idle(काष्ठा tegra_xusb_padctl *padctl,
				    अचिन्हित पूर्णांक port, bool idle);
पूर्णांक tegra_xusb_padctl_usb3_set_lfps_detect(काष्ठा tegra_xusb_padctl *padctl,
					   अचिन्हित पूर्णांक port, bool enable);
पूर्णांक tegra_xusb_padctl_set_vbus_override(काष्ठा tegra_xusb_padctl *padctl,
					bool val);
पूर्णांक tegra_phy_xusb_uपंचांगi_port_reset(काष्ठा phy *phy);
पूर्णांक tegra_xusb_padctl_get_usb3_companion(काष्ठा tegra_xusb_padctl *padctl,
					 अचिन्हित पूर्णांक port);
#पूर्ण_अगर /* PHY_TEGRA_XUSB_H */
