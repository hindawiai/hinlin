<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * rcar_du_group.c  --  R-Car Display Unit Planes and CRTCs Group
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __RCAR_DU_GROUP_H__
#घोषणा __RCAR_DU_GROUP_H__

#समावेश <linux/mutex.h>

#समावेश "rcar_du_plane.h"

काष्ठा rcar_du_device;

/*
 * काष्ठा rcar_du_group - CRTCs and planes group
 * @dev: the DU device
 * @mmio_offset: रेजिस्टरs offset in the device memory map
 * @index: group index
 * @channels_mask: biपंचांगask of populated DU channels in this group
 * @cmms_mask: biपंचांगask of available CMMs in this group
 * @num_crtcs: number of CRTCs in this group (1 or 2)
 * @use_count: number of users of the group (rcar_du_group_(get|put))
 * @used_crtcs: number of CRTCs currently in use
 * @lock: protects the dptsr_planes field and the DPTSR रेजिस्टर
 * @dptsr_planes: biपंचांगask of planes driven by करोt-घड़ी and timing generator 1
 * @num_planes: number of planes in the group
 * @planes: planes handled by the group
 * @need_restart: the group needs to be restarted due to a configuration change
 */
काष्ठा rcar_du_group अणु
	काष्ठा rcar_du_device *dev;
	अचिन्हित पूर्णांक mmio_offset;
	अचिन्हित पूर्णांक index;

	अचिन्हित पूर्णांक channels_mask;
	अचिन्हित पूर्णांक cmms_mask;
	अचिन्हित पूर्णांक num_crtcs;
	अचिन्हित पूर्णांक use_count;
	अचिन्हित पूर्णांक used_crtcs;

	काष्ठा mutex lock;
	अचिन्हित पूर्णांक dptsr_planes;

	अचिन्हित पूर्णांक num_planes;
	काष्ठा rcar_du_plane planes[RCAR_DU_NUM_KMS_PLANES];
	bool need_restart;
पूर्ण;

u32 rcar_du_group_पढ़ो(काष्ठा rcar_du_group *rgrp, u32 reg);
व्योम rcar_du_group_ग_लिखो(काष्ठा rcar_du_group *rgrp, u32 reg, u32 data);

पूर्णांक rcar_du_group_get(काष्ठा rcar_du_group *rgrp);
व्योम rcar_du_group_put(काष्ठा rcar_du_group *rgrp);
व्योम rcar_du_group_start_stop(काष्ठा rcar_du_group *rgrp, bool start);
व्योम rcar_du_group_restart(काष्ठा rcar_du_group *rgrp);
पूर्णांक rcar_du_group_set_routing(काष्ठा rcar_du_group *rgrp);

पूर्णांक rcar_du_set_dpad0_vsp1_routing(काष्ठा rcar_du_device *rcdu);

#पूर्ण_अगर /* __RCAR_DU_GROUP_H__ */
