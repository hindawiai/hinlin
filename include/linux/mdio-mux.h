<शैली गुरु>
/*
 * MDIO bus multiplexer framwork.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2011, 2012 Cavium, Inc.
 */
#अगर_अघोषित __LINUX_MDIO_MUX_H
#घोषणा __LINUX_MDIO_MUX_H
#समावेश <linux/device.h>
#समावेश <linux/phy.h>

/* mdio_mux_init() - Initialize a MDIO mux
 * @dev		The device owning the MDIO mux
 * @mux_node	The device node of the MDIO mux
 * @चयन_fn	The function called क्रम चयनing target MDIO child
 * mux_handle	A poपूर्णांकer to a (व्योम *) used पूर्णांकernaly by mdio-mux
 * @data	Private data used by चयन_fn()
 * @mux_bus	An optional parent bus (Other हाल are to use parent_bus property)
 */
पूर्णांक mdio_mux_init(काष्ठा device *dev,
		  काष्ठा device_node *mux_node,
		  पूर्णांक (*चयन_fn) (पूर्णांक cur, पूर्णांक desired, व्योम *data),
		  व्योम **mux_handle,
		  व्योम *data,
		  काष्ठा mii_bus *mux_bus);

व्योम mdio_mux_uninit(व्योम *mux_handle);

#पूर्ण_अगर /* __LINUX_MDIO_MUX_H */
