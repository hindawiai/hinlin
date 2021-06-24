<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * KUnit tests क्रम AppArmor's policy unpack.
 */

#समावेश <kunit/test.h>

#समावेश "include/policy.h"
#समावेश "include/policy_unpack.h"

#घोषणा TEST_STRING_NAME "TEST_STRING"
#घोषणा TEST_STRING_DATA "testing"
#घोषणा TEST_STRING_BUF_OFFSET \
	(3 + म_माप(TEST_STRING_NAME) + 1)

#घोषणा TEST_U32_NAME "U32_TEST"
#घोषणा TEST_U32_DATA ((u32)0x01020304)
#घोषणा TEST_NAMED_U32_BUF_OFFSET \
	(TEST_STRING_BUF_OFFSET + 3 + म_माप(TEST_STRING_DATA) + 1)
#घोषणा TEST_U32_BUF_OFFSET \
	(TEST_NAMED_U32_BUF_OFFSET + 3 + म_माप(TEST_U32_NAME) + 1)

#घोषणा TEST_U16_OFFSET (TEST_U32_BUF_OFFSET + 3)
#घोषणा TEST_U16_DATA ((u16)(TEST_U32_DATA >> 16))

#घोषणा TEST_U64_NAME "U64_TEST"
#घोषणा TEST_U64_DATA ((u64)0x0102030405060708)
#घोषणा TEST_NAMED_U64_BUF_OFFSET (TEST_U32_BUF_OFFSET + माप(u32) + 1)
#घोषणा TEST_U64_BUF_OFFSET \
	(TEST_NAMED_U64_BUF_OFFSET + 3 + म_माप(TEST_U64_NAME) + 1)

#घोषणा TEST_BLOB_NAME "BLOB_TEST"
#घोषणा TEST_BLOB_DATA "\xde\xad\x00\xbe\xef"
#घोषणा TEST_BLOB_DATA_SIZE (ARRAY_SIZE(TEST_BLOB_DATA))
#घोषणा TEST_NAMED_BLOB_BUF_OFFSET (TEST_U64_BUF_OFFSET + माप(u64) + 1)
#घोषणा TEST_BLOB_BUF_OFFSET \
	(TEST_NAMED_BLOB_BUF_OFFSET + 3 + म_माप(TEST_BLOB_NAME) + 1)

#घोषणा TEST_ARRAY_NAME "ARRAY_TEST"
#घोषणा TEST_ARRAY_SIZE 16
#घोषणा TEST_NAMED_ARRAY_BUF_OFFSET \
	(TEST_BLOB_BUF_OFFSET + 5 + TEST_BLOB_DATA_SIZE)
#घोषणा TEST_ARRAY_BUF_OFFSET \
	(TEST_NAMED_ARRAY_BUF_OFFSET + 3 + म_माप(TEST_ARRAY_NAME) + 1)

काष्ठा policy_unpack_fixture अणु
	काष्ठा aa_ext *e;
	माप_प्रकार e_size;
पूर्ण;

काष्ठा aa_ext *build_aa_ext_काष्ठा(काष्ठा policy_unpack_fixture *puf,
				   काष्ठा kunit *test, माप_प्रकार buf_size)
अणु
	अक्षर *buf;
	काष्ठा aa_ext *e;

	buf = kunit_kzalloc(test, buf_size, GFP_USER);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, buf);

	e = kunit_kदो_स्मृति(test, माप(*e), GFP_USER);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, e);

	e->start = buf;
	e->end = e->start + buf_size;
	e->pos = e->start;

	*buf = AA_NAME;
	*(buf + 1) = म_माप(TEST_STRING_NAME) + 1;
	म_नकल(buf + 3, TEST_STRING_NAME);

	buf = e->start + TEST_STRING_BUF_OFFSET;
	*buf = AA_STRING;
	*(buf + 1) = म_माप(TEST_STRING_DATA) + 1;
	म_नकल(buf + 3, TEST_STRING_DATA);

	buf = e->start + TEST_NAMED_U32_BUF_OFFSET;
	*buf = AA_NAME;
	*(buf + 1) = म_माप(TEST_U32_NAME) + 1;
	म_नकल(buf + 3, TEST_U32_NAME);
	*(buf + 3 + म_माप(TEST_U32_NAME) + 1) = AA_U32;
	*((u32 *)(buf + 3 + म_माप(TEST_U32_NAME) + 2)) = TEST_U32_DATA;

	buf = e->start + TEST_NAMED_U64_BUF_OFFSET;
	*buf = AA_NAME;
	*(buf + 1) = म_माप(TEST_U64_NAME) + 1;
	म_नकल(buf + 3, TEST_U64_NAME);
	*(buf + 3 + म_माप(TEST_U64_NAME) + 1) = AA_U64;
	*((u64 *)(buf + 3 + म_माप(TEST_U64_NAME) + 2)) = TEST_U64_DATA;

	buf = e->start + TEST_NAMED_BLOB_BUF_OFFSET;
	*buf = AA_NAME;
	*(buf + 1) = म_माप(TEST_BLOB_NAME) + 1;
	म_नकल(buf + 3, TEST_BLOB_NAME);
	*(buf + 3 + म_माप(TEST_BLOB_NAME) + 1) = AA_BLOB;
	*(buf + 3 + म_माप(TEST_BLOB_NAME) + 2) = TEST_BLOB_DATA_SIZE;
	स_नकल(buf + 3 + म_माप(TEST_BLOB_NAME) + 6,
		TEST_BLOB_DATA, TEST_BLOB_DATA_SIZE);

	buf = e->start + TEST_NAMED_ARRAY_BUF_OFFSET;
	*buf = AA_NAME;
	*(buf + 1) = म_माप(TEST_ARRAY_NAME) + 1;
	म_नकल(buf + 3, TEST_ARRAY_NAME);
	*(buf + 3 + म_माप(TEST_ARRAY_NAME) + 1) = AA_ARRAY;
	*((u16 *)(buf + 3 + म_माप(TEST_ARRAY_NAME) + 2)) = TEST_ARRAY_SIZE;

	वापस e;
पूर्ण

अटल पूर्णांक policy_unpack_test_init(काष्ठा kunit *test)
अणु
	माप_प्रकार e_size = TEST_ARRAY_BUF_OFFSET + माप(u16) + 1;
	काष्ठा policy_unpack_fixture *puf;

	puf = kunit_kदो_स्मृति(test, माप(*puf), GFP_USER);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, puf);

	puf->e_size = e_size;
	puf->e = build_aa_ext_काष्ठा(puf, test, e_size);

	test->priv = puf;
	वापस 0;
पूर्ण

अटल व्योम policy_unpack_test_inbounds_when_inbounds(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;

	KUNIT_EXPECT_TRUE(test, inbounds(puf->e, 0));
	KUNIT_EXPECT_TRUE(test, inbounds(puf->e, puf->e_size / 2));
	KUNIT_EXPECT_TRUE(test, inbounds(puf->e, puf->e_size));
पूर्ण

अटल व्योम policy_unpack_test_inbounds_when_out_of_bounds(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;

	KUNIT_EXPECT_FALSE(test, inbounds(puf->e, puf->e_size + 1));
पूर्ण

अटल व्योम policy_unpack_test_unpack_array_with_null_name(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	u16 array_size;

	puf->e->pos += TEST_ARRAY_BUF_OFFSET;

	array_size = unpack_array(puf->e, शून्य);

	KUNIT_EXPECT_EQ(test, array_size, (u16)TEST_ARRAY_SIZE);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos,
		puf->e->start + TEST_ARRAY_BUF_OFFSET + माप(u16) + 1);
पूर्ण

अटल व्योम policy_unpack_test_unpack_array_with_name(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	स्थिर अक्षर name[] = TEST_ARRAY_NAME;
	u16 array_size;

	puf->e->pos += TEST_NAMED_ARRAY_BUF_OFFSET;

	array_size = unpack_array(puf->e, name);

	KUNIT_EXPECT_EQ(test, array_size, (u16)TEST_ARRAY_SIZE);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos,
		puf->e->start + TEST_ARRAY_BUF_OFFSET + माप(u16) + 1);
पूर्ण

अटल व्योम policy_unpack_test_unpack_array_out_of_bounds(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	स्थिर अक्षर name[] = TEST_ARRAY_NAME;
	u16 array_size;

	puf->e->pos += TEST_NAMED_ARRAY_BUF_OFFSET;
	puf->e->end = puf->e->start + TEST_ARRAY_BUF_OFFSET + माप(u16);

	array_size = unpack_array(puf->e, name);

	KUNIT_EXPECT_EQ(test, array_size, (u16)0);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos,
		puf->e->start + TEST_NAMED_ARRAY_BUF_OFFSET);
पूर्ण

अटल व्योम policy_unpack_test_unpack_blob_with_null_name(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	अक्षर *blob = शून्य;
	माप_प्रकार size;

	puf->e->pos += TEST_BLOB_BUF_OFFSET;
	size = unpack_blob(puf->e, &blob, शून्य);

	KUNIT_ASSERT_EQ(test, size, TEST_BLOB_DATA_SIZE);
	KUNIT_EXPECT_TRUE(test,
		स_भेद(blob, TEST_BLOB_DATA, TEST_BLOB_DATA_SIZE) == 0);
पूर्ण

अटल व्योम policy_unpack_test_unpack_blob_with_name(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	अक्षर *blob = शून्य;
	माप_प्रकार size;

	puf->e->pos += TEST_NAMED_BLOB_BUF_OFFSET;
	size = unpack_blob(puf->e, &blob, TEST_BLOB_NAME);

	KUNIT_ASSERT_EQ(test, size, TEST_BLOB_DATA_SIZE);
	KUNIT_EXPECT_TRUE(test,
		स_भेद(blob, TEST_BLOB_DATA, TEST_BLOB_DATA_SIZE) == 0);
पूर्ण

अटल व्योम policy_unpack_test_unpack_blob_out_of_bounds(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	अक्षर *blob = शून्य;
	व्योम *start;
	पूर्णांक size;

	puf->e->pos += TEST_NAMED_BLOB_BUF_OFFSET;
	start = puf->e->pos;
	puf->e->end = puf->e->start + TEST_BLOB_BUF_OFFSET
		+ TEST_BLOB_DATA_SIZE - 1;

	size = unpack_blob(puf->e, &blob, TEST_BLOB_NAME);

	KUNIT_EXPECT_EQ(test, size, 0);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos, start);
पूर्ण

अटल व्योम policy_unpack_test_unpack_str_with_null_name(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	स्थिर अक्षर *string = शून्य;
	माप_प्रकार size;

	puf->e->pos += TEST_STRING_BUF_OFFSET;
	size = unpack_str(puf->e, &string, शून्य);

	KUNIT_EXPECT_EQ(test, size, म_माप(TEST_STRING_DATA) + 1);
	KUNIT_EXPECT_STREQ(test, string, TEST_STRING_DATA);
पूर्ण

अटल व्योम policy_unpack_test_unpack_str_with_name(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	स्थिर अक्षर *string = शून्य;
	माप_प्रकार size;

	size = unpack_str(puf->e, &string, TEST_STRING_NAME);

	KUNIT_EXPECT_EQ(test, size, म_माप(TEST_STRING_DATA) + 1);
	KUNIT_EXPECT_STREQ(test, string, TEST_STRING_DATA);
पूर्ण

अटल व्योम policy_unpack_test_unpack_str_out_of_bounds(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	स्थिर अक्षर *string = शून्य;
	व्योम *start = puf->e->pos;
	पूर्णांक size;

	puf->e->end = puf->e->pos + TEST_STRING_BUF_OFFSET
		+ म_माप(TEST_STRING_DATA) - 1;

	size = unpack_str(puf->e, &string, TEST_STRING_NAME);

	KUNIT_EXPECT_EQ(test, size, 0);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos, start);
पूर्ण

अटल व्योम policy_unpack_test_unpack_strdup_with_null_name(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	अक्षर *string = शून्य;
	माप_प्रकार size;

	puf->e->pos += TEST_STRING_BUF_OFFSET;
	size = unpack_strdup(puf->e, &string, शून्य);

	KUNIT_EXPECT_EQ(test, size, म_माप(TEST_STRING_DATA) + 1);
	KUNIT_EXPECT_FALSE(test,
			   ((uपूर्णांकptr_t)puf->e->start <= (uपूर्णांकptr_t)string)
			   && ((uपूर्णांकptr_t)string <= (uपूर्णांकptr_t)puf->e->end));
	KUNIT_EXPECT_STREQ(test, string, TEST_STRING_DATA);
पूर्ण

अटल व्योम policy_unpack_test_unpack_strdup_with_name(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	अक्षर *string = शून्य;
	माप_प्रकार size;

	size = unpack_strdup(puf->e, &string, TEST_STRING_NAME);

	KUNIT_EXPECT_EQ(test, size, म_माप(TEST_STRING_DATA) + 1);
	KUNIT_EXPECT_FALSE(test,
			   ((uपूर्णांकptr_t)puf->e->start <= (uपूर्णांकptr_t)string)
			   && ((uपूर्णांकptr_t)string <= (uपूर्णांकptr_t)puf->e->end));
	KUNIT_EXPECT_STREQ(test, string, TEST_STRING_DATA);
पूर्ण

अटल व्योम policy_unpack_test_unpack_strdup_out_of_bounds(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	व्योम *start = puf->e->pos;
	अक्षर *string = शून्य;
	पूर्णांक size;

	puf->e->end = puf->e->pos + TEST_STRING_BUF_OFFSET
		+ म_माप(TEST_STRING_DATA) - 1;

	size = unpack_strdup(puf->e, &string, TEST_STRING_NAME);

	KUNIT_EXPECT_EQ(test, size, 0);
	KUNIT_EXPECT_PTR_EQ(test, string, (अक्षर *)शून्य);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos, start);
पूर्ण

अटल व्योम policy_unpack_test_unpack_nameX_with_null_name(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	bool success;

	puf->e->pos += TEST_U32_BUF_OFFSET;

	success = unpack_nameX(puf->e, AA_U32, शून्य);

	KUNIT_EXPECT_TRUE(test, success);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos,
			    puf->e->start + TEST_U32_BUF_OFFSET + 1);
पूर्ण

अटल व्योम policy_unpack_test_unpack_nameX_with_wrong_code(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	bool success;

	puf->e->pos += TEST_U32_BUF_OFFSET;

	success = unpack_nameX(puf->e, AA_BLOB, शून्य);

	KUNIT_EXPECT_FALSE(test, success);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos,
			    puf->e->start + TEST_U32_BUF_OFFSET);
पूर्ण

अटल व्योम policy_unpack_test_unpack_nameX_with_name(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	स्थिर अक्षर name[] = TEST_U32_NAME;
	bool success;

	puf->e->pos += TEST_NAMED_U32_BUF_OFFSET;

	success = unpack_nameX(puf->e, AA_U32, name);

	KUNIT_EXPECT_TRUE(test, success);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos,
			    puf->e->start + TEST_U32_BUF_OFFSET + 1);
पूर्ण

अटल व्योम policy_unpack_test_unpack_nameX_with_wrong_name(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	अटल स्थिर अक्षर name[] = "12345678";
	bool success;

	puf->e->pos += TEST_NAMED_U32_BUF_OFFSET;

	success = unpack_nameX(puf->e, AA_U32, name);

	KUNIT_EXPECT_FALSE(test, success);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos,
			    puf->e->start + TEST_NAMED_U32_BUF_OFFSET);
पूर्ण

अटल व्योम policy_unpack_test_unpack_u16_chunk_basic(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	अक्षर *chunk = शून्य;
	माप_प्रकार size;

	puf->e->pos += TEST_U16_OFFSET;
	/*
	 * WARNING: For unit testing purposes, we're pushing puf->e->end past
	 * the end of the allocated memory. Doing anything other than comparing
	 * memory addresses is dangerous.
	 */
	puf->e->end += TEST_U16_DATA;

	size = unpack_u16_chunk(puf->e, &chunk);

	KUNIT_EXPECT_PTR_EQ(test, (व्योम *)chunk,
			    puf->e->start + TEST_U16_OFFSET + 2);
	KUNIT_EXPECT_EQ(test, size, (माप_प्रकार)TEST_U16_DATA);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos, (व्योम *)(chunk + TEST_U16_DATA));
पूर्ण

अटल व्योम policy_unpack_test_unpack_u16_chunk_out_of_bounds_1(
		काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	अक्षर *chunk = शून्य;
	माप_प्रकार size;

	puf->e->pos = puf->e->end - 1;

	size = unpack_u16_chunk(puf->e, &chunk);

	KUNIT_EXPECT_EQ(test, size, (माप_प्रकार)0);
	KUNIT_EXPECT_PTR_EQ(test, chunk, (अक्षर *)शून्य);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos, puf->e->end - 1);
पूर्ण

अटल व्योम policy_unpack_test_unpack_u16_chunk_out_of_bounds_2(
		काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	अक्षर *chunk = शून्य;
	माप_प्रकार size;

	puf->e->pos += TEST_U16_OFFSET;
	/*
	 * WARNING: For unit testing purposes, we're pushing puf->e->end past
	 * the end of the allocated memory. Doing anything other than comparing
	 * memory addresses is dangerous.
	 */
	puf->e->end = puf->e->pos + TEST_U16_DATA - 1;

	size = unpack_u16_chunk(puf->e, &chunk);

	KUNIT_EXPECT_EQ(test, size, (माप_प्रकार)0);
	KUNIT_EXPECT_PTR_EQ(test, chunk, (अक्षर *)शून्य);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos, puf->e->start + TEST_U16_OFFSET);
पूर्ण

अटल व्योम policy_unpack_test_unpack_u32_with_null_name(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	bool success;
	u32 data;

	puf->e->pos += TEST_U32_BUF_OFFSET;

	success = unpack_u32(puf->e, &data, शून्य);

	KUNIT_EXPECT_TRUE(test, success);
	KUNIT_EXPECT_EQ(test, data, TEST_U32_DATA);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos,
			puf->e->start + TEST_U32_BUF_OFFSET + माप(u32) + 1);
पूर्ण

अटल व्योम policy_unpack_test_unpack_u32_with_name(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	स्थिर अक्षर name[] = TEST_U32_NAME;
	bool success;
	u32 data;

	puf->e->pos += TEST_NAMED_U32_BUF_OFFSET;

	success = unpack_u32(puf->e, &data, name);

	KUNIT_EXPECT_TRUE(test, success);
	KUNIT_EXPECT_EQ(test, data, TEST_U32_DATA);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos,
			puf->e->start + TEST_U32_BUF_OFFSET + माप(u32) + 1);
पूर्ण

अटल व्योम policy_unpack_test_unpack_u32_out_of_bounds(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	स्थिर अक्षर name[] = TEST_U32_NAME;
	bool success;
	u32 data;

	puf->e->pos += TEST_NAMED_U32_BUF_OFFSET;
	puf->e->end = puf->e->start + TEST_U32_BUF_OFFSET + माप(u32);

	success = unpack_u32(puf->e, &data, name);

	KUNIT_EXPECT_FALSE(test, success);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos,
			puf->e->start + TEST_NAMED_U32_BUF_OFFSET);
पूर्ण

अटल व्योम policy_unpack_test_unpack_u64_with_null_name(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	bool success;
	u64 data;

	puf->e->pos += TEST_U64_BUF_OFFSET;

	success = unpack_u64(puf->e, &data, शून्य);

	KUNIT_EXPECT_TRUE(test, success);
	KUNIT_EXPECT_EQ(test, data, TEST_U64_DATA);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos,
			puf->e->start + TEST_U64_BUF_OFFSET + माप(u64) + 1);
पूर्ण

अटल व्योम policy_unpack_test_unpack_u64_with_name(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	स्थिर अक्षर name[] = TEST_U64_NAME;
	bool success;
	u64 data;

	puf->e->pos += TEST_NAMED_U64_BUF_OFFSET;

	success = unpack_u64(puf->e, &data, name);

	KUNIT_EXPECT_TRUE(test, success);
	KUNIT_EXPECT_EQ(test, data, TEST_U64_DATA);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos,
			puf->e->start + TEST_U64_BUF_OFFSET + माप(u64) + 1);
पूर्ण

अटल व्योम policy_unpack_test_unpack_u64_out_of_bounds(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	स्थिर अक्षर name[] = TEST_U64_NAME;
	bool success;
	u64 data;

	puf->e->pos += TEST_NAMED_U64_BUF_OFFSET;
	puf->e->end = puf->e->start + TEST_U64_BUF_OFFSET + माप(u64);

	success = unpack_u64(puf->e, &data, name);

	KUNIT_EXPECT_FALSE(test, success);
	KUNIT_EXPECT_PTR_EQ(test, puf->e->pos,
			puf->e->start + TEST_NAMED_U64_BUF_OFFSET);
पूर्ण

अटल व्योम policy_unpack_test_unpack_X_code_match(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	bool success = unpack_X(puf->e, AA_NAME);

	KUNIT_EXPECT_TRUE(test, success);
	KUNIT_EXPECT_TRUE(test, puf->e->pos == puf->e->start + 1);
पूर्ण

अटल व्योम policy_unpack_test_unpack_X_code_mismatch(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	bool success = unpack_X(puf->e, AA_STRING);

	KUNIT_EXPECT_FALSE(test, success);
	KUNIT_EXPECT_TRUE(test, puf->e->pos == puf->e->start);
पूर्ण

अटल व्योम policy_unpack_test_unpack_X_out_of_bounds(काष्ठा kunit *test)
अणु
	काष्ठा policy_unpack_fixture *puf = test->priv;
	bool success;

	puf->e->pos = puf->e->end;
	success = unpack_X(puf->e, AA_NAME);

	KUNIT_EXPECT_FALSE(test, success);
पूर्ण

अटल काष्ठा kunit_हाल apparmor_policy_unpack_test_हालs[] = अणु
	KUNIT_CASE(policy_unpack_test_inbounds_when_inbounds),
	KUNIT_CASE(policy_unpack_test_inbounds_when_out_of_bounds),
	KUNIT_CASE(policy_unpack_test_unpack_array_with_null_name),
	KUNIT_CASE(policy_unpack_test_unpack_array_with_name),
	KUNIT_CASE(policy_unpack_test_unpack_array_out_of_bounds),
	KUNIT_CASE(policy_unpack_test_unpack_blob_with_null_name),
	KUNIT_CASE(policy_unpack_test_unpack_blob_with_name),
	KUNIT_CASE(policy_unpack_test_unpack_blob_out_of_bounds),
	KUNIT_CASE(policy_unpack_test_unpack_nameX_with_null_name),
	KUNIT_CASE(policy_unpack_test_unpack_nameX_with_wrong_code),
	KUNIT_CASE(policy_unpack_test_unpack_nameX_with_name),
	KUNIT_CASE(policy_unpack_test_unpack_nameX_with_wrong_name),
	KUNIT_CASE(policy_unpack_test_unpack_str_with_null_name),
	KUNIT_CASE(policy_unpack_test_unpack_str_with_name),
	KUNIT_CASE(policy_unpack_test_unpack_str_out_of_bounds),
	KUNIT_CASE(policy_unpack_test_unpack_strdup_with_null_name),
	KUNIT_CASE(policy_unpack_test_unpack_strdup_with_name),
	KUNIT_CASE(policy_unpack_test_unpack_strdup_out_of_bounds),
	KUNIT_CASE(policy_unpack_test_unpack_u16_chunk_basic),
	KUNIT_CASE(policy_unpack_test_unpack_u16_chunk_out_of_bounds_1),
	KUNIT_CASE(policy_unpack_test_unpack_u16_chunk_out_of_bounds_2),
	KUNIT_CASE(policy_unpack_test_unpack_u32_with_null_name),
	KUNIT_CASE(policy_unpack_test_unpack_u32_with_name),
	KUNIT_CASE(policy_unpack_test_unpack_u32_out_of_bounds),
	KUNIT_CASE(policy_unpack_test_unpack_u64_with_null_name),
	KUNIT_CASE(policy_unpack_test_unpack_u64_with_name),
	KUNIT_CASE(policy_unpack_test_unpack_u64_out_of_bounds),
	KUNIT_CASE(policy_unpack_test_unpack_X_code_match),
	KUNIT_CASE(policy_unpack_test_unpack_X_code_mismatch),
	KUNIT_CASE(policy_unpack_test_unpack_X_out_of_bounds),
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा kunit_suite apparmor_policy_unpack_test_module = अणु
	.name = "apparmor_policy_unpack",
	.init = policy_unpack_test_init,
	.test_हालs = apparmor_policy_unpack_test_हालs,
पूर्ण;

kunit_test_suite(apparmor_policy_unpack_test_module);
