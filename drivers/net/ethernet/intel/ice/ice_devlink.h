<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019, Intel Corporation. */

#अगर_अघोषित _ICE_DEVLINK_H_
#घोषणा _ICE_DEVLINK_H_

काष्ठा ice_pf *ice_allocate_pf(काष्ठा device *dev);

पूर्णांक ice_devlink_रेजिस्टर(काष्ठा ice_pf *pf);
व्योम ice_devlink_unरेजिस्टर(काष्ठा ice_pf *pf);
पूर्णांक ice_devlink_create_port(काष्ठा ice_vsi *vsi);
व्योम ice_devlink_destroy_port(काष्ठा ice_vsi *vsi);

व्योम ice_devlink_init_regions(काष्ठा ice_pf *pf);
व्योम ice_devlink_destroy_regions(काष्ठा ice_pf *pf);

#पूर्ण_अगर /* _ICE_DEVLINK_H_ */
