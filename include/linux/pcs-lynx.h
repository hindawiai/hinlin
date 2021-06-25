<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/* Copyright 2020 NXP
 * Lynx PCS helpers
 */

#अगर_अघोषित __LINUX_PCS_LYNX_H
#घोषणा __LINUX_PCS_LYNX_H

#समावेश <linux/mdपन.स>
#समावेश <linux/phylink.h>

काष्ठा lynx_pcs अणु
	काष्ठा phylink_pcs pcs;
	काष्ठा mdio_device *mdio;
पूर्ण;

काष्ठा lynx_pcs *lynx_pcs_create(काष्ठा mdio_device *mdio);

व्योम lynx_pcs_destroy(काष्ठा lynx_pcs *pcs);

#पूर्ण_अगर /* __LINUX_PCS_LYNX_H */
