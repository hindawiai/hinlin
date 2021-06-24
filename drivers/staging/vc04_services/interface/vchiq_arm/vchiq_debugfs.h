<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright (c) 2014 Raspberry Pi (Trading) Ltd. All rights reserved. */

#अगर_अघोषित VCHIQ_DEBUGFS_H
#घोषणा VCHIQ_DEBUGFS_H

#समावेश "vchiq_core.h"

काष्ठा vchiq_debugfs_node अणु
	काष्ठा dentry *dentry;
पूर्ण;

व्योम vchiq_debugfs_init(व्योम);

व्योम vchiq_debugfs_deinit(व्योम);

व्योम vchiq_debugfs_add_instance(काष्ठा vchiq_instance *instance);

व्योम vchiq_debugfs_हटाओ_instance(काष्ठा vchiq_instance *instance);

#पूर्ण_अगर /* VCHIQ_DEBUGFS_H */
