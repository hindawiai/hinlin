<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * rcar_du_of.h - Legacy DT bindings compatibility
 *
 * Copyright (C) 2018 Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */
#अगर_अघोषित __RCAR_DU_OF_H__
#घोषणा __RCAR_DU_OF_H__

#समावेश <linux/init.h>

काष्ठा of_device_id;

#अगर IS_ENABLED(CONFIG_DRM_RCAR_LVDS)
व्योम __init rcar_du_of_init(स्थिर काष्ठा of_device_id *of_ids);
#अन्यथा
अटल अंतरभूत व्योम rcar_du_of_init(स्थिर काष्ठा of_device_id *of_ids) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_DRM_RCAR_LVDS */

#पूर्ण_अगर /* __RCAR_DU_OF_H__ */
