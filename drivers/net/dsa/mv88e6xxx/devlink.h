<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

/* Marvell 88E6xxx Switch devlink support. */

#अगर_अघोषित _MV88E6XXX_DEVLINK_H
#घोषणा _MV88E6XXX_DEVLINK_H

पूर्णांक mv88e6xxx_setup_devlink_params(काष्ठा dsa_चयन *ds);
व्योम mv88e6xxx_tearकरोwn_devlink_params(काष्ठा dsa_चयन *ds);
पूर्णांक mv88e6xxx_setup_devlink_resources(काष्ठा dsa_चयन *ds);
पूर्णांक mv88e6xxx_devlink_param_get(काष्ठा dsa_चयन *ds, u32 id,
				काष्ठा devlink_param_gset_ctx *ctx);
पूर्णांक mv88e6xxx_devlink_param_set(काष्ठा dsa_चयन *ds, u32 id,
				काष्ठा devlink_param_gset_ctx *ctx);
पूर्णांक mv88e6xxx_setup_devlink_regions(काष्ठा dsa_चयन *ds);
व्योम mv88e6xxx_tearकरोwn_devlink_regions(काष्ठा dsa_चयन *ds);

पूर्णांक mv88e6xxx_devlink_info_get(काष्ठा dsa_चयन *ds,
			       काष्ठा devlink_info_req *req,
			       काष्ठा netlink_ext_ack *extack);
#पूर्ण_अगर /* _MV88E6XXX_DEVLINK_H */
