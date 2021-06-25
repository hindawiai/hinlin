<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved.
 */

#अगर_अघोषित _RDMA_RESTRACK_H_
#घोषणा _RDMA_RESTRACK_H_

#समावेश <linux/typecheck.h>
#समावेश <linux/sched.h>
#समावेश <linux/kref.h>
#समावेश <linux/completion.h>
#समावेश <linux/sched/task.h>
#समावेश <uapi/rdma/rdma_netlink.h>
#समावेश <linux/xarray.h>

काष्ठा ib_device;
काष्ठा sk_buff;

/**
 * क्रमागत rdma_restrack_type - HW objects to track
 */
क्रमागत rdma_restrack_type अणु
	/**
	 * @RDMA_RESTRACK_PD: Protection करोमुख्य (PD)
	 */
	RDMA_RESTRACK_PD,
	/**
	 * @RDMA_RESTRACK_CQ: Completion queue (CQ)
	 */
	RDMA_RESTRACK_CQ,
	/**
	 * @RDMA_RESTRACK_QP: Queue pair (QP)
	 */
	RDMA_RESTRACK_QP,
	/**
	 * @RDMA_RESTRACK_CM_ID: Connection Manager ID (CM_ID)
	 */
	RDMA_RESTRACK_CM_ID,
	/**
	 * @RDMA_RESTRACK_MR: Memory Region (MR)
	 */
	RDMA_RESTRACK_MR,
	/**
	 * @RDMA_RESTRACK_CTX: Verbs contexts (CTX)
	 */
	RDMA_RESTRACK_CTX,
	/**
	 * @RDMA_RESTRACK_COUNTER: Statistic Counter
	 */
	RDMA_RESTRACK_COUNTER,
	/**
	 * @RDMA_RESTRACK_SRQ: Shared receive queue (SRQ)
	 */
	RDMA_RESTRACK_SRQ,
	/**
	 * @RDMA_RESTRACK_MAX: Last entry, used क्रम array dclarations
	 */
	RDMA_RESTRACK_MAX
पूर्ण;

/**
 * काष्ठा rdma_restrack_entry - metadata per-entry
 */
काष्ठा rdma_restrack_entry अणु
	/**
	 * @valid: validity indicator
	 *
	 * The entries are filled during rdma_restrack_add,
	 * can be attempted to be मुक्त during rdma_restrack_del.
	 *
	 * As an example क्रम that, see mlx5 QPs with type MLX5_IB_QPT_HW_GSI
	 */
	bool			valid;
	/**
	 * @no_track: करोn't add this entry to restrack DB
	 *
	 * This field is used to mark an entry that करोesn't need to be added to
	 * पूर्णांकernal restrack DB and presented later to the users at the nldev
	 * query stage.
	 */
	u8			no_track : 1;
	/*
	 * @kref: Protect destroy of the resource
	 */
	काष्ठा kref		kref;
	/*
	 * @comp: Signal that all consumers of resource are completed their work
	 */
	काष्ठा completion	comp;
	/**
	 * @task: owner of resource tracking entity
	 *
	 * There are two types of entities: created by user and created
	 * by kernel.
	 *
	 * This is relevant क्रम the entities created by users.
	 * For the entities created by kernel, this poपूर्णांकer will be शून्य.
	 */
	काष्ठा task_काष्ठा	*task;
	/**
	 * @kern_name: name of owner क्रम the kernel created entities.
	 */
	स्थिर अक्षर		*kern_name;
	/**
	 * @type: various objects in restrack database
	 */
	क्रमागत rdma_restrack_type	type;
	/**
	 * @user: user resource
	 */
	bool			user;
	/**
	 * @id: ID to expose to users
	 */
	u32 id;
पूर्ण;

पूर्णांक rdma_restrack_count(काष्ठा ib_device *dev,
			क्रमागत rdma_restrack_type type);
/**
 * rdma_is_kernel_res() - check the owner of resource
 * @res:  resource entry
 */
अटल अंतरभूत bool rdma_is_kernel_res(स्थिर काष्ठा rdma_restrack_entry *res)
अणु
	वापस !res->user;
पूर्ण

/**
 * rdma_restrack_get() - grab to protect resource from release
 * @res:  resource entry
 */
पूर्णांक __must_check rdma_restrack_get(काष्ठा rdma_restrack_entry *res);

/**
 * rdma_restrack_put() - release resource
 * @res:  resource entry
 */
पूर्णांक rdma_restrack_put(काष्ठा rdma_restrack_entry *res);

/*
 * Helper functions क्रम rdma drivers when filling out
 * nldev driver attributes.
 */
पूर्णांक rdma_nl_put_driver_u32(काष्ठा sk_buff *msg, स्थिर अक्षर *name, u32 value);
पूर्णांक rdma_nl_put_driver_u32_hex(काष्ठा sk_buff *msg, स्थिर अक्षर *name,
			       u32 value);
पूर्णांक rdma_nl_put_driver_u64(काष्ठा sk_buff *msg, स्थिर अक्षर *name, u64 value);
पूर्णांक rdma_nl_put_driver_u64_hex(काष्ठा sk_buff *msg, स्थिर अक्षर *name,
			       u64 value);
पूर्णांक rdma_nl_put_driver_string(काष्ठा sk_buff *msg, स्थिर अक्षर *name,
			      स्थिर अक्षर *str);
पूर्णांक rdma_nl_stat_hwcounter_entry(काष्ठा sk_buff *msg, स्थिर अक्षर *name,
				 u64 value);

काष्ठा rdma_restrack_entry *rdma_restrack_get_byid(काष्ठा ib_device *dev,
						   क्रमागत rdma_restrack_type type,
						   u32 id);

/**
 * rdma_restrack_no_track() - करोn't add resource to the DB
 * @res: resource entry
 *
 * Every user of thie API should be cross examined.
 * Probaby you करोn't need to use this function.
 */
अटल अंतरभूत व्योम rdma_restrack_no_track(काष्ठा rdma_restrack_entry *res)
अणु
	res->no_track = true;
पूर्ण
अटल अंतरभूत bool rdma_restrack_is_tracked(काष्ठा rdma_restrack_entry *res)
अणु
	वापस !res->no_track;
पूर्ण
#पूर्ण_अगर /* _RDMA_RESTRACK_H_ */
