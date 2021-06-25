<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Interconnect framework driver क्रम i.MX SoC
 *
 * Copyright (c) 2019, BayLibre
 * Copyright (c) 2019-2020, NXP
 * Author: Alexandre Bailon <abailon@baylibre.com>
 * Author: Leonard Crestez <leonard.crestez@nxp.com>
 */
#अगर_अघोषित __DRIVERS_INTERCONNECT_IMX_H
#घोषणा __DRIVERS_INTERCONNECT_IMX_H

#समावेश <linux/kernel.h>

#घोषणा IMX_ICC_MAX_LINKS	4

/*
 * काष्ठा imx_icc_node_adj - Describe a dynamic adjustable node
 */
काष्ठा imx_icc_node_adj_desc अणु
	अचिन्हित पूर्णांक bw_mul, bw_भाग;
	स्थिर अक्षर *phandle_name;
	bool मुख्य_noc;
पूर्ण;

/*
 * काष्ठा imx_icc_node - Describe an पूर्णांकerconnect node
 * @name: name of the node
 * @id: an unique id to identअगरy the node
 * @links: an array of slaves' node id
 * @num_links: number of id defined in links
 */
काष्ठा imx_icc_node_desc अणु
	स्थिर अक्षर *name;
	u16 id;
	u16 links[IMX_ICC_MAX_LINKS];
	u16 num_links;
	स्थिर काष्ठा imx_icc_node_adj_desc *adj;
पूर्ण;

#घोषणा DEFINE_BUS_INTERCONNECT(_name, _id, _adj, ...)			\
	अणु								\
		.id = _id,						\
		.name = _name,						\
		.adj = _adj,						\
		.num_links = ARRAY_SIZE(((पूर्णांक[])अणु __VA_ARGS__ पूर्ण)),	\
		.links = अणु __VA_ARGS__ पूर्ण,				\
	पूर्ण

#घोषणा DEFINE_BUS_MASTER(_name, _id, _dest_id)				\
	DEFINE_BUS_INTERCONNECT(_name, _id, शून्य, _dest_id)

#घोषणा DEFINE_BUS_SLAVE(_name, _id, _adj)				\
	DEFINE_BUS_INTERCONNECT(_name, _id, _adj)

पूर्णांक imx_icc_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
		     काष्ठा imx_icc_node_desc *nodes,
		     पूर्णांक nodes_count);
पूर्णांक imx_icc_unरेजिस्टर(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर /* __DRIVERS_INTERCONNECT_IMX_H */
