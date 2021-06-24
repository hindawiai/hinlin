<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright Altera Corporation (C) 2016. All rights reserved.
 *
 * Author: Tien Hock Loh <thloh@altera.com>
 */

#अगर_अघोषित __TSE_PCS_H__
#घोषणा __TSE_PCS_H__

#समावेश <linux/phy.h>
#समावेश <linux/समयr.h>

काष्ठा tse_pcs अणु
	काष्ठा device *dev;
	व्योम __iomem *tse_pcs_base;
	व्योम __iomem *sgmii_adapter_base;
	काष्ठा समयr_list aneg_link_समयr;
	पूर्णांक स्वतःneg;
पूर्ण;

पूर्णांक tse_pcs_init(व्योम __iomem *base, काष्ठा tse_pcs *pcs);
व्योम tse_pcs_fix_mac_speed(काष्ठा tse_pcs *pcs, काष्ठा phy_device *phy_dev,
			   अचिन्हित पूर्णांक speed);

#पूर्ण_अगर /* __TSE_PCS_H__ */
