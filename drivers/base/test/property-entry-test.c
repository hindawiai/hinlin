<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Unit tests क्रम property entries API
//
// Copyright 2019 Google LLC.

#समावेश <kunit/test.h>
#समावेश <linux/property.h>
#समावेश <linux/types.h>

अटल व्योम pe_test_uपूर्णांकs(काष्ठा kunit *test)
अणु
	अटल स्थिर काष्ठा property_entry entries[] = अणु
		PROPERTY_ENTRY_U8("prop-u8", 8),
		PROPERTY_ENTRY_U16("prop-u16", 16),
		PROPERTY_ENTRY_U32("prop-u32", 32),
		PROPERTY_ENTRY_U64("prop-u64", 64),
		अणु पूर्ण
	पूर्ण;

	काष्ठा fwnode_handle *node;
	u8 val_u8, array_u8[2];
	u16 val_u16, array_u16[2];
	u32 val_u32, array_u32[2];
	u64 val_u64, array_u64[2];
	पूर्णांक error;

	node = fwnode_create_software_node(entries, शून्य);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, node);

	error = fwnode_property_count_u8(node, "prop-u8");
	KUNIT_EXPECT_EQ(test, error, 1);

	error = fwnode_property_पढ़ो_u8(node, "prop-u8", &val_u8);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)val_u8, 8);

	error = fwnode_property_पढ़ो_u8_array(node, "prop-u8", array_u8, 1);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u8[0], 8);

	error = fwnode_property_पढ़ो_u8_array(node, "prop-u8", array_u8, 2);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u8(node, "no-prop-u8", &val_u8);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u8_array(node, "no-prop-u8", array_u8, 1);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u16(node, "prop-u16", &val_u16);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)val_u16, 16);

	error = fwnode_property_count_u16(node, "prop-u16");
	KUNIT_EXPECT_EQ(test, error, 1);

	error = fwnode_property_पढ़ो_u16_array(node, "prop-u16", array_u16, 1);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u16[0], 16);

	error = fwnode_property_पढ़ो_u16_array(node, "prop-u16", array_u16, 2);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u16(node, "no-prop-u16", &val_u16);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u16_array(node, "no-prop-u16", array_u16, 1);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u32(node, "prop-u32", &val_u32);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)val_u32, 32);

	error = fwnode_property_count_u32(node, "prop-u32");
	KUNIT_EXPECT_EQ(test, error, 1);

	error = fwnode_property_पढ़ो_u32_array(node, "prop-u32", array_u32, 1);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u32[0], 32);

	error = fwnode_property_पढ़ो_u32_array(node, "prop-u32", array_u32, 2);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u32(node, "no-prop-u32", &val_u32);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u32_array(node, "no-prop-u32", array_u32, 1);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u64(node, "prop-u64", &val_u64);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)val_u64, 64);

	error = fwnode_property_count_u64(node, "prop-u64");
	KUNIT_EXPECT_EQ(test, error, 1);

	error = fwnode_property_पढ़ो_u64_array(node, "prop-u64", array_u64, 1);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u64[0], 64);

	error = fwnode_property_पढ़ो_u64_array(node, "prop-u64", array_u64, 2);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u64(node, "no-prop-u64", &val_u64);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u64_array(node, "no-prop-u64", array_u64, 1);
	KUNIT_EXPECT_NE(test, error, 0);

	/* Count 64-bit values as 16-bit */
	error = fwnode_property_count_u16(node, "prop-u64");
	KUNIT_EXPECT_EQ(test, error, 4);

	fwnode_हटाओ_software_node(node);
पूर्ण

अटल व्योम pe_test_uपूर्णांक_arrays(काष्ठा kunit *test)
अणु
	अटल स्थिर u8 a_u8[10] = अणु 8, 9 पूर्ण;
	अटल स्थिर u16 a_u16[10] = अणु 16, 17 पूर्ण;
	अटल स्थिर u32 a_u32[10] = अणु 32, 33 पूर्ण;
	अटल स्थिर u64 a_u64[10] = अणु 64, 65 पूर्ण;
	अटल स्थिर काष्ठा property_entry entries[] = अणु
		PROPERTY_ENTRY_U8_ARRAY("prop-u8", a_u8),
		PROPERTY_ENTRY_U16_ARRAY("prop-u16", a_u16),
		PROPERTY_ENTRY_U32_ARRAY("prop-u32", a_u32),
		PROPERTY_ENTRY_U64_ARRAY("prop-u64", a_u64),
		अणु पूर्ण
	पूर्ण;

	काष्ठा fwnode_handle *node;
	u8 val_u8, array_u8[32];
	u16 val_u16, array_u16[32];
	u32 val_u32, array_u32[32];
	u64 val_u64, array_u64[32];
	पूर्णांक error;

	node = fwnode_create_software_node(entries, शून्य);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, node);

	error = fwnode_property_पढ़ो_u8(node, "prop-u8", &val_u8);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)val_u8, 8);

	error = fwnode_property_count_u8(node, "prop-u8");
	KUNIT_EXPECT_EQ(test, error, 10);

	error = fwnode_property_पढ़ो_u8_array(node, "prop-u8", array_u8, 1);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u8[0], 8);

	error = fwnode_property_पढ़ो_u8_array(node, "prop-u8", array_u8, 2);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u8[0], 8);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u8[1], 9);

	error = fwnode_property_पढ़ो_u8_array(node, "prop-u8", array_u8, 17);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u8(node, "no-prop-u8", &val_u8);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u8_array(node, "no-prop-u8", array_u8, 1);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u16(node, "prop-u16", &val_u16);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)val_u16, 16);

	error = fwnode_property_count_u16(node, "prop-u16");
	KUNIT_EXPECT_EQ(test, error, 10);

	error = fwnode_property_पढ़ो_u16_array(node, "prop-u16", array_u16, 1);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u16[0], 16);

	error = fwnode_property_पढ़ो_u16_array(node, "prop-u16", array_u16, 2);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u16[0], 16);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u16[1], 17);

	error = fwnode_property_पढ़ो_u16_array(node, "prop-u16", array_u16, 17);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u16(node, "no-prop-u16", &val_u16);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u16_array(node, "no-prop-u16", array_u16, 1);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u32(node, "prop-u32", &val_u32);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)val_u32, 32);

	error = fwnode_property_count_u32(node, "prop-u32");
	KUNIT_EXPECT_EQ(test, error, 10);

	error = fwnode_property_पढ़ो_u32_array(node, "prop-u32", array_u32, 1);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u32[0], 32);

	error = fwnode_property_पढ़ो_u32_array(node, "prop-u32", array_u32, 2);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u32[0], 32);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u32[1], 33);

	error = fwnode_property_पढ़ो_u32_array(node, "prop-u32", array_u32, 17);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u32(node, "no-prop-u32", &val_u32);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u32_array(node, "no-prop-u32", array_u32, 1);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u64(node, "prop-u64", &val_u64);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)val_u64, 64);

	error = fwnode_property_count_u64(node, "prop-u64");
	KUNIT_EXPECT_EQ(test, error, 10);

	error = fwnode_property_पढ़ो_u64_array(node, "prop-u64", array_u64, 1);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u64[0], 64);

	error = fwnode_property_पढ़ो_u64_array(node, "prop-u64", array_u64, 2);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u64[0], 64);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)array_u64[1], 65);

	error = fwnode_property_पढ़ो_u64_array(node, "prop-u64", array_u64, 17);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u64(node, "no-prop-u64", &val_u64);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_u64_array(node, "no-prop-u64", array_u64, 1);
	KUNIT_EXPECT_NE(test, error, 0);

	/* Count 64-bit values as 16-bit */
	error = fwnode_property_count_u16(node, "prop-u64");
	KUNIT_EXPECT_EQ(test, error, 40);

	/* Other way around */
	error = fwnode_property_count_u64(node, "prop-u16");
	KUNIT_EXPECT_EQ(test, error, 2);

	fwnode_हटाओ_software_node(node);
पूर्ण

अटल व्योम pe_test_strings(काष्ठा kunit *test)
अणु
	अटल स्थिर अक्षर *strings[] = अणु
		"string-a",
		"string-b",
	पूर्ण;

	अटल स्थिर काष्ठा property_entry entries[] = अणु
		PROPERTY_ENTRY_STRING("str", "single"),
		PROPERTY_ENTRY_STRING("empty", ""),
		PROPERTY_ENTRY_STRING_ARRAY("strs", strings),
		अणु पूर्ण
	पूर्ण;

	काष्ठा fwnode_handle *node;
	स्थिर अक्षर *str;
	स्थिर अक्षर *strs[10];
	पूर्णांक error;

	node = fwnode_create_software_node(entries, शून्य);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, node);

	error = fwnode_property_पढ़ो_string(node, "str", &str);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_STREQ(test, str, "single");

	error = fwnode_property_string_array_count(node, "str");
	KUNIT_EXPECT_EQ(test, error, 1);

	error = fwnode_property_पढ़ो_string_array(node, "str", strs, 1);
	KUNIT_EXPECT_EQ(test, error, 1);
	KUNIT_EXPECT_STREQ(test, strs[0], "single");

	/* asking क्रम more data वापसs what we have */
	error = fwnode_property_पढ़ो_string_array(node, "str", strs, 2);
	KUNIT_EXPECT_EQ(test, error, 1);
	KUNIT_EXPECT_STREQ(test, strs[0], "single");

	error = fwnode_property_पढ़ो_string(node, "no-str", &str);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_पढ़ो_string_array(node, "no-str", strs, 1);
	KUNIT_EXPECT_LT(test, error, 0);

	error = fwnode_property_पढ़ो_string(node, "empty", &str);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_STREQ(test, str, "");

	error = fwnode_property_string_array_count(node, "strs");
	KUNIT_EXPECT_EQ(test, error, 2);

	error = fwnode_property_पढ़ो_string_array(node, "strs", strs, 3);
	KUNIT_EXPECT_EQ(test, error, 2);
	KUNIT_EXPECT_STREQ(test, strs[0], "string-a");
	KUNIT_EXPECT_STREQ(test, strs[1], "string-b");

	error = fwnode_property_पढ़ो_string_array(node, "strs", strs, 1);
	KUNIT_EXPECT_EQ(test, error, 1);
	KUNIT_EXPECT_STREQ(test, strs[0], "string-a");

	/* शून्य argument -> वापसs size */
	error = fwnode_property_पढ़ो_string_array(node, "strs", शून्य, 0);
	KUNIT_EXPECT_EQ(test, error, 2);

	/* accessing array as single value */
	error = fwnode_property_पढ़ो_string(node, "strs", &str);
	KUNIT_EXPECT_EQ(test, error, 0);
	KUNIT_EXPECT_STREQ(test, str, "string-a");

	fwnode_हटाओ_software_node(node);
पूर्ण

अटल व्योम pe_test_bool(काष्ठा kunit *test)
अणु
	अटल स्थिर काष्ठा property_entry entries[] = अणु
		PROPERTY_ENTRY_BOOL("prop"),
		अणु पूर्ण
	पूर्ण;

	काष्ठा fwnode_handle *node;

	node = fwnode_create_software_node(entries, शून्य);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, node);

	KUNIT_EXPECT_TRUE(test, fwnode_property_पढ़ो_bool(node, "prop"));
	KUNIT_EXPECT_FALSE(test, fwnode_property_पढ़ो_bool(node, "not-prop"));

	fwnode_हटाओ_software_node(node);
पूर्ण

/* Verअगरies that small U8 array is stored अंतरभूत when property is copied */
अटल व्योम pe_test_move_अंतरभूत_u8(काष्ठा kunit *test)
अणु
	अटल स्थिर u8 u8_array_small[8] = अणु 1, 2, 3, 4 पूर्ण;
	अटल स्थिर u8 u8_array_big[128] = अणु 5, 6, 7, 8 पूर्ण;
	अटल स्थिर काष्ठा property_entry entries[] = अणु
		PROPERTY_ENTRY_U8_ARRAY("small", u8_array_small),
		PROPERTY_ENTRY_U8_ARRAY("big", u8_array_big),
		अणु पूर्ण
	पूर्ण;

	काष्ठा property_entry *copy;
	स्थिर u8 *data_ptr;

	copy = property_entries_dup(entries);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, copy);

	KUNIT_EXPECT_TRUE(test, copy[0].is_अंतरभूत);
	data_ptr = (u8 *)&copy[0].value;
	KUNIT_EXPECT_EQ(test, (पूर्णांक)data_ptr[0], 1);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)data_ptr[1], 2);

	KUNIT_EXPECT_FALSE(test, copy[1].is_अंतरभूत);
	data_ptr = copy[1].poपूर्णांकer;
	KUNIT_EXPECT_EQ(test, (पूर्णांक)data_ptr[0], 5);
	KUNIT_EXPECT_EQ(test, (पूर्णांक)data_ptr[1], 6);

	property_entries_मुक्त(copy);
पूर्ण

/* Verअगरies that single string array is stored अंतरभूत when property is copied */
अटल व्योम pe_test_move_अंतरभूत_str(काष्ठा kunit *test)
अणु
	अटल अक्षर *str_array_small[] = अणु "a" पूर्ण;
	अटल अक्षर *str_array_big[] = अणु "b", "c", "d", "e" पूर्ण;
	अटल अक्षर *str_array_small_empty[] = अणु "" पूर्ण;
	अटल काष्ठा property_entry entries[] = अणु
		PROPERTY_ENTRY_STRING_ARRAY("small", str_array_small),
		PROPERTY_ENTRY_STRING_ARRAY("big", str_array_big),
		PROPERTY_ENTRY_STRING_ARRAY("small-empty", str_array_small_empty),
		अणु पूर्ण
	पूर्ण;

	काष्ठा property_entry *copy;
	स्थिर अक्षर * स्थिर *data_ptr;

	copy = property_entries_dup(entries);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, copy);

	KUNIT_EXPECT_TRUE(test, copy[0].is_अंतरभूत);
	KUNIT_EXPECT_STREQ(test, copy[0].value.str[0], "a");

	KUNIT_EXPECT_FALSE(test, copy[1].is_अंतरभूत);
	data_ptr = copy[1].poपूर्णांकer;
	KUNIT_EXPECT_STREQ(test, data_ptr[0], "b");
	KUNIT_EXPECT_STREQ(test, data_ptr[1], "c");

	KUNIT_EXPECT_TRUE(test, copy[2].is_अंतरभूत);
	KUNIT_EXPECT_STREQ(test, copy[2].value.str[0], "");

	property_entries_मुक्त(copy);
पूर्ण

/* Handling of reference properties */
अटल व्योम pe_test_reference(काष्ठा kunit *test)
अणु
	अटल स्थिर काष्ठा software_node nodes[] = अणु
		अणु .name = "1", पूर्ण,
		अणु .name = "2", पूर्ण,
		अणु पूर्ण
	पूर्ण;

	अटल स्थिर काष्ठा software_node_ref_args refs[] = अणु
		SOFTWARE_NODE_REFERENCE(&nodes[0]),
		SOFTWARE_NODE_REFERENCE(&nodes[1], 3, 4),
	पूर्ण;

	स्थिर काष्ठा property_entry entries[] = अणु
		PROPERTY_ENTRY_REF("ref-1", &nodes[0]),
		PROPERTY_ENTRY_REF("ref-2", &nodes[1], 1, 2),
		PROPERTY_ENTRY_REF_ARRAY("ref-3", refs),
		अणु पूर्ण
	पूर्ण;

	काष्ठा fwnode_handle *node;
	काष्ठा fwnode_reference_args ref;
	पूर्णांक error;

	error = software_node_रेजिस्टर_nodes(nodes);
	KUNIT_ASSERT_EQ(test, error, 0);

	node = fwnode_create_software_node(entries, शून्य);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, node);

	error = fwnode_property_get_reference_args(node, "ref-1", शून्य,
						   0, 0, &ref);
	KUNIT_ASSERT_EQ(test, error, 0);
	KUNIT_EXPECT_PTR_EQ(test, to_software_node(ref.fwnode), &nodes[0]);
	KUNIT_EXPECT_EQ(test, ref.nargs, 0U);

	/* wrong index */
	error = fwnode_property_get_reference_args(node, "ref-1", शून्य,
						   0, 1, &ref);
	KUNIT_EXPECT_NE(test, error, 0);

	error = fwnode_property_get_reference_args(node, "ref-2", शून्य,
						   1, 0, &ref);
	KUNIT_ASSERT_EQ(test, error, 0);
	KUNIT_EXPECT_PTR_EQ(test, to_software_node(ref.fwnode), &nodes[1]);
	KUNIT_EXPECT_EQ(test, ref.nargs, 1U);
	KUNIT_EXPECT_EQ(test, ref.args[0], 1LLU);

	/* asking क्रम more args, padded with zero data */
	error = fwnode_property_get_reference_args(node, "ref-2", शून्य,
						   3, 0, &ref);
	KUNIT_ASSERT_EQ(test, error, 0);
	KUNIT_EXPECT_PTR_EQ(test, to_software_node(ref.fwnode), &nodes[1]);
	KUNIT_EXPECT_EQ(test, ref.nargs, 3U);
	KUNIT_EXPECT_EQ(test, ref.args[0], 1LLU);
	KUNIT_EXPECT_EQ(test, ref.args[1], 2LLU);
	KUNIT_EXPECT_EQ(test, ref.args[2], 0LLU);

	/* wrong index */
	error = fwnode_property_get_reference_args(node, "ref-2", शून्य,
						   2, 1, &ref);
	KUNIT_EXPECT_NE(test, error, 0);

	/* array of references */
	error = fwnode_property_get_reference_args(node, "ref-3", शून्य,
						   0, 0, &ref);
	KUNIT_ASSERT_EQ(test, error, 0);
	KUNIT_EXPECT_PTR_EQ(test, to_software_node(ref.fwnode), &nodes[0]);
	KUNIT_EXPECT_EQ(test, ref.nargs, 0U);

	/* second reference in the array */
	error = fwnode_property_get_reference_args(node, "ref-3", शून्य,
						   2, 1, &ref);
	KUNIT_ASSERT_EQ(test, error, 0);
	KUNIT_EXPECT_PTR_EQ(test, to_software_node(ref.fwnode), &nodes[1]);
	KUNIT_EXPECT_EQ(test, ref.nargs, 2U);
	KUNIT_EXPECT_EQ(test, ref.args[0], 3LLU);
	KUNIT_EXPECT_EQ(test, ref.args[1], 4LLU);

	/* wrong index */
	error = fwnode_property_get_reference_args(node, "ref-1", शून्य,
						   0, 2, &ref);
	KUNIT_EXPECT_NE(test, error, 0);

	fwnode_हटाओ_software_node(node);
	software_node_unरेजिस्टर_nodes(nodes);
पूर्ण

अटल काष्ठा kunit_हाल property_entry_test_हालs[] = अणु
	KUNIT_CASE(pe_test_uपूर्णांकs),
	KUNIT_CASE(pe_test_uपूर्णांक_arrays),
	KUNIT_CASE(pe_test_strings),
	KUNIT_CASE(pe_test_bool),
	KUNIT_CASE(pe_test_move_अंतरभूत_u8),
	KUNIT_CASE(pe_test_move_अंतरभूत_str),
	KUNIT_CASE(pe_test_reference),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा kunit_suite property_entry_test_suite = अणु
	.name = "property-entry",
	.test_हालs = property_entry_test_हालs,
पूर्ण;

kunit_test_suite(property_entry_test_suite);
