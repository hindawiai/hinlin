<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * OF graph binding parsing helpers
 *
 * Copyright (C) 2012 - 2013 Samsung Electronics Co., Ltd.
 * Author: Sylwester Nawrocki <s.nawrocki@samsung.com>
 *
 * Copyright (C) 2012 Renesas Electronics Corp.
 * Author: Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */
#अगर_अघोषित __LINUX_OF_GRAPH_H
#घोषणा __LINUX_OF_GRAPH_H

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>

/**
 * काष्ठा of_endpoपूर्णांक - the OF graph endpoपूर्णांक data काष्ठाure
 * @port: identअगरier (value of reg property) of a port this endpoपूर्णांक beदीर्घs to
 * @id: identअगरier (value of reg property) of this endpoपूर्णांक
 * @local_node: poपूर्णांकer to device_node of this endpoपूर्णांक
 */
काष्ठा of_endpoपूर्णांक अणु
	अचिन्हित पूर्णांक port;
	अचिन्हित पूर्णांक id;
	स्थिर काष्ठा device_node *local_node;
पूर्ण;

/**
 * क्रम_each_endpoपूर्णांक_of_node - iterate over every endpoपूर्णांक in a device node
 * @parent: parent device node containing ports and endpoपूर्णांकs
 * @child: loop variable poपूर्णांकing to the current endpoपूर्णांक node
 *
 * When अवरोधing out of the loop, of_node_put(child) has to be called manually.
 */
#घोषणा क्रम_each_endpoपूर्णांक_of_node(parent, child) \
	क्रम (child = of_graph_get_next_endpoपूर्णांक(parent, शून्य); child != शून्य; \
	     child = of_graph_get_next_endpoपूर्णांक(parent, child))

#अगर_घोषित CONFIG_OF
bool of_graph_is_present(स्थिर काष्ठा device_node *node);
पूर्णांक of_graph_parse_endpoपूर्णांक(स्थिर काष्ठा device_node *node,
				काष्ठा of_endpoपूर्णांक *endpoपूर्णांक);
पूर्णांक of_graph_get_endpoपूर्णांक_count(स्थिर काष्ठा device_node *np);
काष्ठा device_node *of_graph_get_port_by_id(काष्ठा device_node *node, u32 id);
काष्ठा device_node *of_graph_get_next_endpoपूर्णांक(स्थिर काष्ठा device_node *parent,
					काष्ठा device_node *previous);
काष्ठा device_node *of_graph_get_endpoपूर्णांक_by_regs(
		स्थिर काष्ठा device_node *parent, पूर्णांक port_reg, पूर्णांक reg);
काष्ठा device_node *of_graph_get_remote_endpoपूर्णांक(
					स्थिर काष्ठा device_node *node);
काष्ठा device_node *of_graph_get_port_parent(काष्ठा device_node *node);
काष्ठा device_node *of_graph_get_remote_port_parent(
					स्थिर काष्ठा device_node *node);
काष्ठा device_node *of_graph_get_remote_port(स्थिर काष्ठा device_node *node);
काष्ठा device_node *of_graph_get_remote_node(स्थिर काष्ठा device_node *node,
					     u32 port, u32 endpoपूर्णांक);
#अन्यथा

अटल अंतरभूत bool of_graph_is_present(स्थिर काष्ठा device_node *node)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक of_graph_parse_endpoपूर्णांक(स्थिर काष्ठा device_node *node,
					काष्ठा of_endpoपूर्णांक *endpoपूर्णांक)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक of_graph_get_endpoपूर्णांक_count(स्थिर काष्ठा device_node *np)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_graph_get_port_by_id(
					काष्ठा device_node *node, u32 id)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_graph_get_next_endpoपूर्णांक(
					स्थिर काष्ठा device_node *parent,
					काष्ठा device_node *previous)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_graph_get_endpoपूर्णांक_by_regs(
		स्थिर काष्ठा device_node *parent, पूर्णांक port_reg, पूर्णांक reg)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_graph_get_remote_endpoपूर्णांक(
					स्थिर काष्ठा device_node *node)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_graph_get_port_parent(
	काष्ठा device_node *node)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_graph_get_remote_port_parent(
					स्थिर काष्ठा device_node *node)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *of_graph_get_remote_port(
					स्थिर काष्ठा device_node *node)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा device_node *of_graph_get_remote_node(
					स्थिर काष्ठा device_node *node,
					u32 port, u32 endpoपूर्णांक)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_OF */

#पूर्ण_अगर /* __LINUX_OF_GRAPH_H */
