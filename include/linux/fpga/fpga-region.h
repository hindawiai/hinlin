<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _FPGA_REGION_H
#घोषणा _FPGA_REGION_H

#समावेश <linux/device.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/fpga/fpga-bridge.h>

/**
 * काष्ठा fpga_region - FPGA Region काष्ठाure
 * @dev: FPGA Region device
 * @mutex: enक्रमces exclusive reference to region
 * @bridge_list: list of FPGA bridges specअगरied in region
 * @mgr: FPGA manager
 * @info: FPGA image info
 * @compat_id: FPGA region id क्रम compatibility check.
 * @priv: निजी data
 * @get_bridges: optional function to get bridges to a list
 */
काष्ठा fpga_region अणु
	काष्ठा device dev;
	काष्ठा mutex mutex; /* क्रम exclusive reference to region */
	काष्ठा list_head bridge_list;
	काष्ठा fpga_manager *mgr;
	काष्ठा fpga_image_info *info;
	काष्ठा fpga_compat_id *compat_id;
	व्योम *priv;
	पूर्णांक (*get_bridges)(काष्ठा fpga_region *region);
पूर्ण;

#घोषणा to_fpga_region(d) container_of(d, काष्ठा fpga_region, dev)

काष्ठा fpga_region *fpga_region_class_find(
	काष्ठा device *start, स्थिर व्योम *data,
	पूर्णांक (*match)(काष्ठा device *, स्थिर व्योम *));

पूर्णांक fpga_region_program_fpga(काष्ठा fpga_region *region);

काष्ठा fpga_region
*fpga_region_create(काष्ठा device *dev, काष्ठा fpga_manager *mgr,
		    पूर्णांक (*get_bridges)(काष्ठा fpga_region *));
व्योम fpga_region_मुक्त(काष्ठा fpga_region *region);
पूर्णांक fpga_region_रेजिस्टर(काष्ठा fpga_region *region);
व्योम fpga_region_unरेजिस्टर(काष्ठा fpga_region *region);

काष्ठा fpga_region
*devm_fpga_region_create(काष्ठा device *dev, काष्ठा fpga_manager *mgr,
			पूर्णांक (*get_bridges)(काष्ठा fpga_region *));

#पूर्ण_अगर /* _FPGA_REGION_H */
