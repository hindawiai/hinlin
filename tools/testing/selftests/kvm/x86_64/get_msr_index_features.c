<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test that KVM_GET_MSR_INDEX_LIST and
 * KVM_GET_MSR_FEATURE_INDEX_LIST work as पूर्णांकended
 *
 * Copyright (C) 2020, Red Hat, Inc.
 */
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"

अटल पूर्णांक kvm_num_index_msrs(पूर्णांक kvm_fd, पूर्णांक nmsrs)
अणु
	काष्ठा kvm_msr_list *list;
	पूर्णांक r;

	list = दो_स्मृति(माप(*list) + nmsrs * माप(list->indices[0]));
	list->nmsrs = nmsrs;
	r = ioctl(kvm_fd, KVM_GET_MSR_INDEX_LIST, list);
	TEST_ASSERT(r == -1 && त्रुटि_सं == E2BIG,
				"Unexpected result from KVM_GET_MSR_INDEX_LIST probe, r: %i",
				r);

	r = list->nmsrs;
	मुक्त(list);
	वापस r;
पूर्ण

अटल व्योम test_get_msr_index(व्योम)
अणु
	पूर्णांक old_res, res, kvm_fd, r;
	काष्ठा kvm_msr_list *list;

	kvm_fd = खोलो_kvm_dev_path_or_निकास();

	old_res = kvm_num_index_msrs(kvm_fd, 0);
	TEST_ASSERT(old_res != 0, "Expecting nmsrs to be > 0");

	अगर (old_res != 1) अणु
		res = kvm_num_index_msrs(kvm_fd, 1);
		TEST_ASSERT(res > 1, "Expecting nmsrs to be > 1");
		TEST_ASSERT(res == old_res, "Expecting nmsrs to be identical");
	पूर्ण

	list = दो_स्मृति(माप(*list) + old_res * माप(list->indices[0]));
	list->nmsrs = old_res;
	r = ioctl(kvm_fd, KVM_GET_MSR_INDEX_LIST, list);

	TEST_ASSERT(r == 0,
		    "Unexpected result from KVM_GET_MSR_FEATURE_INDEX_LIST, r: %i",
		    r);
	TEST_ASSERT(list->nmsrs == old_res, "Expecting nmsrs to be identical");
	मुक्त(list);

	बंद(kvm_fd);
पूर्ण

अटल पूर्णांक kvm_num_feature_msrs(पूर्णांक kvm_fd, पूर्णांक nmsrs)
अणु
	काष्ठा kvm_msr_list *list;
	पूर्णांक r;

	list = दो_स्मृति(माप(*list) + nmsrs * माप(list->indices[0]));
	list->nmsrs = nmsrs;
	r = ioctl(kvm_fd, KVM_GET_MSR_FEATURE_INDEX_LIST, list);
	TEST_ASSERT(r == -1 && त्रुटि_सं == E2BIG,
		"Unexpected result from KVM_GET_MSR_FEATURE_INDEX_LIST probe, r: %i",
				r);

	r = list->nmsrs;
	मुक्त(list);
	वापस r;
पूर्ण

काष्ठा kvm_msr_list *kvm_get_msr_feature_list(पूर्णांक kvm_fd, पूर्णांक nmsrs)
अणु
	काष्ठा kvm_msr_list *list;
	पूर्णांक r;

	list = दो_स्मृति(माप(*list) + nmsrs * माप(list->indices[0]));
	list->nmsrs = nmsrs;
	r = ioctl(kvm_fd, KVM_GET_MSR_FEATURE_INDEX_LIST, list);

	TEST_ASSERT(r == 0,
		"Unexpected result from KVM_GET_MSR_FEATURE_INDEX_LIST, r: %i",
		r);

	वापस list;
पूर्ण

अटल व्योम test_get_msr_feature(व्योम)
अणु
	पूर्णांक res, old_res, i, kvm_fd;
	काष्ठा kvm_msr_list *feature_list;

	kvm_fd = खोलो_kvm_dev_path_or_निकास();

	old_res = kvm_num_feature_msrs(kvm_fd, 0);
	TEST_ASSERT(old_res != 0, "Expecting nmsrs to be > 0");

	अगर (old_res != 1) अणु
		res = kvm_num_feature_msrs(kvm_fd, 1);
		TEST_ASSERT(res > 1, "Expecting nmsrs to be > 1");
		TEST_ASSERT(res == old_res, "Expecting nmsrs to be identical");
	पूर्ण

	feature_list = kvm_get_msr_feature_list(kvm_fd, old_res);
	TEST_ASSERT(old_res == feature_list->nmsrs,
				"Unmatching number of msr indexes");

	क्रम (i = 0; i < feature_list->nmsrs; i++)
		kvm_get_feature_msr(feature_list->indices[i]);

	मुक्त(feature_list);
	बंद(kvm_fd);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अगर (kvm_check_cap(KVM_CAP_GET_MSR_FEATURES))
		test_get_msr_feature();

	test_get_msr_index();
पूर्ण
