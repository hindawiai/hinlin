<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies */

#अगर_अघोषित __MLX5_MAPPING_H__
#घोषणा __MLX5_MAPPING_H__

काष्ठा mapping_ctx;

पूर्णांक mapping_add(काष्ठा mapping_ctx *ctx, व्योम *data, u32 *id);
पूर्णांक mapping_हटाओ(काष्ठा mapping_ctx *ctx, u32 id);
पूर्णांक mapping_find(काष्ठा mapping_ctx *ctx, u32 id, व्योम *data);

/* mapping uses an xarray to map data to ids in add(), and क्रम find().
 * For locking, it uses a पूर्णांकernal xarray spin lock क्रम add()/हटाओ(),
 * find() uses rcu_पढ़ो_lock().
 * Choosing delayed_removal postpones the removal of a previously mapped
 * id by MAPPING_GRACE_PERIOD milliseconds.
 * This is to aव्योम races against hardware, where we mark the packet in
 * hardware with a previous id, and quick हटाओ() and add() reusing the same
 * previous id. Then find() will get the new mapping instead of the old
 * which was used to mark the packet.
 */
काष्ठा mapping_ctx *mapping_create(माप_प्रकार data_size, u32 max_id,
				   bool delayed_removal);
व्योम mapping_destroy(काष्ठा mapping_ctx *ctx);

#पूर्ण_अगर /* __MLX5_MAPPING_H__ */
