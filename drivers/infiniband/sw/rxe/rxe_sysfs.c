<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश "rxe.h"
#समावेश "rxe_net.h"

/* Copy argument and हटाओ trailing CR. Return the new length. */
अटल पूर्णांक sanitize_arg(स्थिर अक्षर *val, अक्षर *पूर्णांकf, पूर्णांक पूर्णांकf_len)
अणु
	पूर्णांक len;

	अगर (!val)
		वापस 0;

	/* Remove newline. */
	क्रम (len = 0; len < पूर्णांकf_len - 1 && val[len] && val[len] != '\n'; len++)
		पूर्णांकf[len] = val[len];
	पूर्णांकf[len] = 0;

	अगर (len == 0 || (val[len] != 0 && val[len] != '\n'))
		वापस 0;

	वापस len;
पूर्ण

अटल पूर्णांक rxe_param_set_add(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक len;
	पूर्णांक err = 0;
	अक्षर पूर्णांकf[32];
	काष्ठा net_device *ndev;
	काष्ठा rxe_dev *exists;

	अगर (!rxe_initialized) अणु
		pr_err("Module parameters are not supported, use rdma link add or rxe_cfg\n");
		वापस -EAGAIN;
	पूर्ण

	len = sanitize_arg(val, पूर्णांकf, माप(पूर्णांकf));
	अगर (!len) अणु
		pr_err("add: invalid interface name\n");
		वापस -EINVAL;
	पूर्ण

	ndev = dev_get_by_name(&init_net, पूर्णांकf);
	अगर (!ndev) अणु
		pr_err("interface %s not found\n", पूर्णांकf);
		वापस -EINVAL;
	पूर्ण

	अगर (is_vlan_dev(ndev)) अणु
		pr_err("rxe creation allowed on top of a real device only\n");
		err = -EPERM;
		जाओ err;
	पूर्ण

	exists = rxe_get_dev_from_net(ndev);
	अगर (exists) अणु
		ib_device_put(&exists->ib_dev);
		pr_err("already configured on %s\n", पूर्णांकf);
		err = -EINVAL;
		जाओ err;
	पूर्ण

	err = rxe_net_add("rxe%d", ndev);
	अगर (err) अणु
		pr_err("failed to add %s\n", पूर्णांकf);
		जाओ err;
	पूर्ण

err:
	dev_put(ndev);
	वापस err;
पूर्ण

अटल पूर्णांक rxe_param_set_हटाओ(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक len;
	अक्षर पूर्णांकf[32];
	काष्ठा ib_device *ib_dev;

	len = sanitize_arg(val, पूर्णांकf, माप(पूर्णांकf));
	अगर (!len) अणु
		pr_err("add: invalid interface name\n");
		वापस -EINVAL;
	पूर्ण

	अगर (म_भेदन("all", पूर्णांकf, len) == 0) अणु
		pr_info("rxe_sys: remove all");
		ib_unरेजिस्टर_driver(RDMA_DRIVER_RXE);
		वापस 0;
	पूर्ण

	ib_dev = ib_device_get_by_name(पूर्णांकf, RDMA_DRIVER_RXE);
	अगर (!ib_dev) अणु
		pr_err("not configured on %s\n", पूर्णांकf);
		वापस -EINVAL;
	पूर्ण

	ib_unरेजिस्टर_device_and_put(ib_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops rxe_add_ops = अणु
	.set = rxe_param_set_add,
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops rxe_हटाओ_ops = अणु
	.set = rxe_param_set_हटाओ,
पूर्ण;

module_param_cb(add, &rxe_add_ops, शून्य, 0200);
MODULE_PARM_DESC(add, "DEPRECATED.  Create RXE device over network interface");
module_param_cb(हटाओ, &rxe_हटाओ_ops, शून्य, 0200);
MODULE_PARM_DESC(हटाओ, "DEPRECATED.  Remove RXE device over network interface");
