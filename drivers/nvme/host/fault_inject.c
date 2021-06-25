<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fault injection support क्रम nvme.
 *
 * Copyright (c) 2018, Oracle and/or its affiliates
 */

#समावेश <linux/moduleparam.h>
#समावेश "nvme.h"

अटल DECLARE_FAULT_ATTR(fail_शेष_attr);
/* optional fault injection attributes boot समय option:
 * nvme_core.fail_request=<पूर्णांकerval>,<probability>,<space>,<बार>
 */
अटल अक्षर *fail_request;
module_param(fail_request, अक्षरp, 0000);

व्योम nvme_fault_inject_init(काष्ठा nvme_fault_inject *fault_inj,
			    स्थिर अक्षर *dev_name)
अणु
	काष्ठा dentry *dir, *parent;
	काष्ठा fault_attr *attr = &fault_inj->attr;

	/* set शेष fault injection attribute */
	अगर (fail_request)
		setup_fault_attr(&fail_शेष_attr, fail_request);

	/* create debugfs directory and attribute */
	parent = debugfs_create_dir(dev_name, शून्य);
	अगर (!parent) अणु
		pr_warn("%s: failed to create debugfs directory\n", dev_name);
		वापस;
	पूर्ण

	*attr = fail_शेष_attr;
	dir = fault_create_debugfs_attr("fault_inject", parent, attr);
	अगर (IS_ERR(dir)) अणु
		pr_warn("%s: failed to create debugfs attr\n", dev_name);
		debugfs_हटाओ_recursive(parent);
		वापस;
	पूर्ण
	fault_inj->parent = parent;

	/* create debugfs क्रम status code and करोnt_retry */
	fault_inj->status = NVME_SC_INVALID_OPCODE;
	fault_inj->करोnt_retry = true;
	debugfs_create_x16("status", 0600, dir,	&fault_inj->status);
	debugfs_create_bool("dont_retry", 0600, dir, &fault_inj->करोnt_retry);
पूर्ण

व्योम nvme_fault_inject_fini(काष्ठा nvme_fault_inject *fault_inject)
अणु
	/* हटाओ debugfs directories */
	debugfs_हटाओ_recursive(fault_inject->parent);
पूर्ण

व्योम nvme_should_fail(काष्ठा request *req)
अणु
	काष्ठा gendisk *disk = req->rq_disk;
	काष्ठा nvme_fault_inject *fault_inject = शून्य;
	u16 status;

	अगर (disk) अणु
		काष्ठा nvme_ns *ns = disk->निजी_data;

		अगर (ns)
			fault_inject = &ns->fault_inject;
		अन्यथा
			WARN_ONCE(1, "No namespace found for request\n");
	पूर्ण अन्यथा अणु
		fault_inject = &nvme_req(req)->ctrl->fault_inject;
	पूर्ण

	अगर (fault_inject && should_fail(&fault_inject->attr, 1)) अणु
		/* inject status code and DNR bit */
		status = fault_inject->status;
		अगर (fault_inject->करोnt_retry)
			status |= NVME_SC_DNR;
		nvme_req(req)->status =	status;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nvme_should_fail);
