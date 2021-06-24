<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2020 Synopsys, Inc. and/or its affiliates.
 * Synopsys DesignWare XPCS helpers
 */

#अगर_अघोषित __LINUX_PCS_XPCS_H
#घोषणा __LINUX_PCS_XPCS_H

#समावेश <linux/phy.h>
#समावेश <linux/phylink.h>

/* AN mode */
#घोषणा DW_AN_C73			1
#घोषणा DW_AN_C37_SGMII			2

काष्ठा mdio_xpcs_args अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(supported);
	काष्ठा mii_bus *bus;
	पूर्णांक addr;
	पूर्णांक an_mode;
पूर्ण;

काष्ठा mdio_xpcs_ops अणु
	पूर्णांक (*validate)(काष्ठा mdio_xpcs_args *xpcs,
			अचिन्हित दीर्घ *supported,
			काष्ठा phylink_link_state *state);
	पूर्णांक (*config)(काष्ठा mdio_xpcs_args *xpcs,
		      स्थिर काष्ठा phylink_link_state *state);
	पूर्णांक (*get_state)(काष्ठा mdio_xpcs_args *xpcs,
			 काष्ठा phylink_link_state *state);
	पूर्णांक (*link_up)(काष्ठा mdio_xpcs_args *xpcs, पूर्णांक speed,
		       phy_पूर्णांकerface_t पूर्णांकerface);
	पूर्णांक (*probe)(काष्ठा mdio_xpcs_args *xpcs, phy_पूर्णांकerface_t पूर्णांकerface);
पूर्ण;

#अगर IS_ENABLED(CONFIG_PCS_XPCS)
काष्ठा mdio_xpcs_ops *mdio_xpcs_get_ops(व्योम);
#अन्यथा
अटल अंतरभूत काष्ठा mdio_xpcs_ops *mdio_xpcs_get_ops(व्योम)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_PCS_XPCS_H */
