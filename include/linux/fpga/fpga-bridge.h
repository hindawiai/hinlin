<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _LINUX_FPGA_BRIDGE_H
#घोषणा _LINUX_FPGA_BRIDGE_H

#समावेश <linux/device.h>
#समावेश <linux/fpga/fpga-mgr.h>

काष्ठा fpga_bridge;

/**
 * काष्ठा fpga_bridge_ops - ops क्रम low level FPGA bridge drivers
 * @enable_show: वापसs the FPGA bridge's status
 * @enable_set: set a FPGA bridge as enabled or disabled
 * @fpga_bridge_हटाओ: set FPGA पूर्णांकo a specअगरic state during driver हटाओ
 * @groups: optional attribute groups.
 */
काष्ठा fpga_bridge_ops अणु
	पूर्णांक (*enable_show)(काष्ठा fpga_bridge *bridge);
	पूर्णांक (*enable_set)(काष्ठा fpga_bridge *bridge, bool enable);
	व्योम (*fpga_bridge_हटाओ)(काष्ठा fpga_bridge *bridge);
	स्थिर काष्ठा attribute_group **groups;
पूर्ण;

/**
 * काष्ठा fpga_bridge - FPGA bridge काष्ठाure
 * @name: name of low level FPGA bridge
 * @dev: FPGA bridge device
 * @mutex: enक्रमces exclusive reference to bridge
 * @br_ops: poपूर्णांकer to काष्ठा of FPGA bridge ops
 * @info: fpga image specअगरic inक्रमmation
 * @node: FPGA bridge list node
 * @priv: low level driver निजी date
 */
काष्ठा fpga_bridge अणु
	स्थिर अक्षर *name;
	काष्ठा device dev;
	काष्ठा mutex mutex; /* क्रम exclusive reference to bridge */
	स्थिर काष्ठा fpga_bridge_ops *br_ops;
	काष्ठा fpga_image_info *info;
	काष्ठा list_head node;
	व्योम *priv;
पूर्ण;

#घोषणा to_fpga_bridge(d) container_of(d, काष्ठा fpga_bridge, dev)

काष्ठा fpga_bridge *of_fpga_bridge_get(काष्ठा device_node *node,
				       काष्ठा fpga_image_info *info);
काष्ठा fpga_bridge *fpga_bridge_get(काष्ठा device *dev,
				    काष्ठा fpga_image_info *info);
व्योम fpga_bridge_put(काष्ठा fpga_bridge *bridge);
पूर्णांक fpga_bridge_enable(काष्ठा fpga_bridge *bridge);
पूर्णांक fpga_bridge_disable(काष्ठा fpga_bridge *bridge);

पूर्णांक fpga_bridges_enable(काष्ठा list_head *bridge_list);
पूर्णांक fpga_bridges_disable(काष्ठा list_head *bridge_list);
व्योम fpga_bridges_put(काष्ठा list_head *bridge_list);
पूर्णांक fpga_bridge_get_to_list(काष्ठा device *dev,
			    काष्ठा fpga_image_info *info,
			    काष्ठा list_head *bridge_list);
पूर्णांक of_fpga_bridge_get_to_list(काष्ठा device_node *np,
			       काष्ठा fpga_image_info *info,
			       काष्ठा list_head *bridge_list);

काष्ठा fpga_bridge *fpga_bridge_create(काष्ठा device *dev, स्थिर अक्षर *name,
				       स्थिर काष्ठा fpga_bridge_ops *br_ops,
				       व्योम *priv);
व्योम fpga_bridge_मुक्त(काष्ठा fpga_bridge *br);
पूर्णांक fpga_bridge_रेजिस्टर(काष्ठा fpga_bridge *br);
व्योम fpga_bridge_unरेजिस्टर(काष्ठा fpga_bridge *br);

काष्ठा fpga_bridge
*devm_fpga_bridge_create(काष्ठा device *dev, स्थिर अक्षर *name,
			 स्थिर काष्ठा fpga_bridge_ops *br_ops, व्योम *priv);

#पूर्ण_अगर /* _LINUX_FPGA_BRIDGE_H */
