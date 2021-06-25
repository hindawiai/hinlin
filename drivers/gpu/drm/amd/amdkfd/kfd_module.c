<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/sched.h>
#समावेश <linux/device.h>
#समावेश "kfd_priv.h"
#समावेश "amdgpu_amdkfd.h"

अटल पूर्णांक kfd_init(व्योम)
अणु
	पूर्णांक err;

	/* Verअगरy module parameters */
	अगर ((sched_policy < KFD_SCHED_POLICY_HWS) ||
		(sched_policy > KFD_SCHED_POLICY_NO_HWS)) अणु
		pr_err("sched_policy has invalid value\n");
		वापस -EINVAL;
	पूर्ण

	/* Verअगरy module parameters */
	अगर ((max_num_of_queues_per_device < 1) ||
		(max_num_of_queues_per_device >
			KFD_MAX_NUM_OF_QUEUES_PER_DEVICE)) अणु
		pr_err("max_num_of_queues_per_device must be between 1 to KFD_MAX_NUM_OF_QUEUES_PER_DEVICE\n");
		वापस -EINVAL;
	पूर्ण

	err = kfd_अक्षरdev_init();
	अगर (err < 0)
		जाओ err_ioctl;

	err = kfd_topology_init();
	अगर (err < 0)
		जाओ err_topology;

	err = kfd_process_create_wq();
	अगर (err < 0)
		जाओ err_create_wq;

	/* Ignore the वापस value, so that we can जारी
	 * to init the KFD, even अगर procfs isn't craated
	 */
	kfd_procfs_init();

	kfd_debugfs_init();

	वापस 0;

err_create_wq:
	kfd_topology_shutकरोwn();
err_topology:
	kfd_अक्षरdev_निकास();
err_ioctl:
	pr_err("KFD is disabled due to module initialization failure\n");
	वापस err;
पूर्ण

अटल व्योम kfd_निकास(व्योम)
अणु
	kfd_debugfs_fini();
	kfd_process_destroy_wq();
	kfd_procfs_shutकरोwn();
	kfd_topology_shutकरोwn();
	kfd_अक्षरdev_निकास();
पूर्ण

पूर्णांक kgd2kfd_init(व्योम)
अणु
	वापस kfd_init();
पूर्ण

व्योम kgd2kfd_निकास(व्योम)
अणु
	kfd_निकास();
पूर्ण
