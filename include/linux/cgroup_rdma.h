<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Parav Pandit <pandit.parav@gmail.com>
 */

#अगर_अघोषित _CGROUP_RDMA_H
#घोषणा _CGROUP_RDMA_H

#समावेश <linux/cgroup.h>

क्रमागत rdmacg_resource_type अणु
	RDMACG_RESOURCE_HCA_HANDLE,
	RDMACG_RESOURCE_HCA_OBJECT,
	RDMACG_RESOURCE_MAX,
पूर्ण;

#अगर_घोषित CONFIG_CGROUP_RDMA

काष्ठा rdma_cgroup अणु
	काष्ठा cgroup_subsys_state	css;

	/*
	 * head to keep track of all resource pools
	 * that beदीर्घs to this cgroup.
	 */
	काष्ठा list_head		rpools;
पूर्ण;

काष्ठा rdmacg_device अणु
	काष्ठा list_head	dev_node;
	काष्ठा list_head	rpools;
	अक्षर			*name;
पूर्ण;

/*
 * APIs क्रम RDMA/IB stack to publish when a device wants to
 * participate in resource accounting
 */
व्योम rdmacg_रेजिस्टर_device(काष्ठा rdmacg_device *device);
व्योम rdmacg_unरेजिस्टर_device(काष्ठा rdmacg_device *device);

/* APIs क्रम RDMA/IB stack to अक्षरge/unअक्षरge pool specअगरic resources */
पूर्णांक rdmacg_try_अक्षरge(काष्ठा rdma_cgroup **rdmacg,
		      काष्ठा rdmacg_device *device,
		      क्रमागत rdmacg_resource_type index);
व्योम rdmacg_unअक्षरge(काष्ठा rdma_cgroup *cg,
		     काष्ठा rdmacg_device *device,
		     क्रमागत rdmacg_resource_type index);
#पूर्ण_अगर	/* CONFIG_CGROUP_RDMA */
#पूर्ण_अगर	/* _CGROUP_RDMA_H */
