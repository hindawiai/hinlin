<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

/* Just a quick and causal check of the shmem_utils API */

अटल पूर्णांक igt_shmem_basic(व्योम *ignored)
अणु
	u32 datum = 0xdeadbeef, result;
	काष्ठा file *file;
	u32 *map;
	पूर्णांक err;

	file = shmem_create_from_data("mock", &datum, माप(datum));
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	result = 0;
	err = shmem_पढ़ो(file, 0, &result, माप(result));
	अगर (err)
		जाओ out_file;

	अगर (result != datum) अणु
		pr_err("Incorrect read back from shmemfs: %x != %x\n",
		       result, datum);
		err = -EINVAL;
		जाओ out_file;
	पूर्ण

	result = 0xc0ffee;
	err = shmem_ग_लिखो(file, 0, &result, माप(result));
	अगर (err)
		जाओ out_file;

	map = shmem_pin_map(file);
	अगर (!map) अणु
		err = -ENOMEM;
		जाओ out_file;
	पूर्ण

	अगर (*map != result) अणु
		pr_err("Incorrect read back via mmap of last write: %x != %x\n",
		       *map, result);
		err = -EINVAL;
		जाओ out_map;
	पूर्ण

out_map:
	shmem_unpin_map(file, map);
out_file:
	fput(file);
	वापस err;
पूर्ण

पूर्णांक shmem_utils_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_shmem_basic),
	पूर्ण;

	वापस i915_subtests(tests, शून्य);
पूर्ण
