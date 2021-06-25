<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel module क्रम testing अटल keys.
 *
 * Copyright 2015 Akamai Technologies Inc. All Rights Reserved
 *
 * Authors:
 *      Jason Baron       <jbaron@akamai.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/jump_label.h>

/* old keys */
काष्ठा अटल_key old_true_key	= STATIC_KEY_INIT_TRUE;
काष्ठा अटल_key old_false_key	= STATIC_KEY_INIT_FALSE;

/* new api */
DEFINE_STATIC_KEY_TRUE(true_key);
DEFINE_STATIC_KEY_FALSE(false_key);

/* बाह्यal */
बाह्य काष्ठा अटल_key base_old_true_key;
बाह्य काष्ठा अटल_key base_inv_old_true_key;
बाह्य काष्ठा अटल_key base_old_false_key;
बाह्य काष्ठा अटल_key base_inv_old_false_key;

/* new api */
बाह्य काष्ठा अटल_key_true base_true_key;
बाह्य काष्ठा अटल_key_true base_inv_true_key;
बाह्य काष्ठा अटल_key_false base_false_key;
बाह्य काष्ठा अटल_key_false base_inv_false_key;


काष्ठा test_key अणु
	bool			init_state;
	काष्ठा अटल_key	*key;
	bool			(*test_key)(व्योम);
पूर्ण;

#घोषणा test_key_func(key, branch)	\
अटल bool key ## _ ## branch(व्योम)	\
अणु					\
	वापस branch(&key);		\
पूर्ण

अटल व्योम invert_key(काष्ठा अटल_key *key)
अणु
	अगर (अटल_key_enabled(key))
		अटल_key_disable(key);
	अन्यथा
		अटल_key_enable(key);
पूर्ण

अटल व्योम invert_keys(काष्ठा test_key *keys, पूर्णांक size)
अणु
	काष्ठा अटल_key *previous = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर (previous != keys[i].key) अणु
			invert_key(keys[i].key);
			previous = keys[i].key;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक verअगरy_keys(काष्ठा test_key *keys, पूर्णांक size, bool invert)
अणु
	पूर्णांक i;
	bool ret, init;

	क्रम (i = 0; i < size; i++) अणु
		ret = अटल_key_enabled(keys[i].key);
		init = keys[i].init_state;
		अगर (ret != (invert ? !init : init))
			वापस -EINVAL;
		ret = keys[i].test_key();
		अगर (अटल_key_enabled(keys[i].key)) अणु
			अगर (!ret)
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (ret)
				वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

test_key_func(old_true_key, अटल_key_true)
test_key_func(old_false_key, अटल_key_false)
test_key_func(true_key, अटल_branch_likely)
test_key_func(true_key, अटल_branch_unlikely)
test_key_func(false_key, अटल_branch_likely)
test_key_func(false_key, अटल_branch_unlikely)
test_key_func(base_old_true_key, अटल_key_true)
test_key_func(base_inv_old_true_key, अटल_key_true)
test_key_func(base_old_false_key, अटल_key_false)
test_key_func(base_inv_old_false_key, अटल_key_false)
test_key_func(base_true_key, अटल_branch_likely)
test_key_func(base_true_key, अटल_branch_unlikely)
test_key_func(base_inv_true_key, अटल_branch_likely)
test_key_func(base_inv_true_key, अटल_branch_unlikely)
test_key_func(base_false_key, अटल_branch_likely)
test_key_func(base_false_key, अटल_branch_unlikely)
test_key_func(base_inv_false_key, अटल_branch_likely)
test_key_func(base_inv_false_key, अटल_branch_unlikely)

अटल पूर्णांक __init test_अटल_key_init(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक size;

	काष्ठा test_key अटल_key_tests[] = अणु
		/* पूर्णांकernal keys - old keys */
		अणु
			.init_state	= true,
			.key		= &old_true_key,
			.test_key	= &old_true_key_अटल_key_true,
		पूर्ण,
		अणु
			.init_state	= false,
			.key		= &old_false_key,
			.test_key	= &old_false_key_अटल_key_false,
		पूर्ण,
		/* पूर्णांकernal keys - new keys */
		अणु
			.init_state	= true,
			.key		= &true_key.key,
			.test_key	= &true_key_अटल_branch_likely,
		पूर्ण,
		अणु
			.init_state	= true,
			.key		= &true_key.key,
			.test_key	= &true_key_अटल_branch_unlikely,
		पूर्ण,
		अणु
			.init_state	= false,
			.key		= &false_key.key,
			.test_key	= &false_key_अटल_branch_likely,
		पूर्ण,
		अणु
			.init_state	= false,
			.key		= &false_key.key,
			.test_key	= &false_key_अटल_branch_unlikely,
		पूर्ण,
		/* बाह्यal keys - old keys */
		अणु
			.init_state	= true,
			.key		= &base_old_true_key,
			.test_key	= &base_old_true_key_अटल_key_true,
		पूर्ण,
		अणु
			.init_state	= false,
			.key		= &base_inv_old_true_key,
			.test_key	= &base_inv_old_true_key_अटल_key_true,
		पूर्ण,
		अणु
			.init_state	= false,
			.key		= &base_old_false_key,
			.test_key	= &base_old_false_key_अटल_key_false,
		पूर्ण,
		अणु
			.init_state	= true,
			.key		= &base_inv_old_false_key,
			.test_key	= &base_inv_old_false_key_अटल_key_false,
		पूर्ण,
		/* बाह्यal keys - new keys */
		अणु
			.init_state	= true,
			.key		= &base_true_key.key,
			.test_key	= &base_true_key_अटल_branch_likely,
		पूर्ण,
		अणु
			.init_state	= true,
			.key		= &base_true_key.key,
			.test_key	= &base_true_key_अटल_branch_unlikely,
		पूर्ण,
		अणु
			.init_state	= false,
			.key		= &base_inv_true_key.key,
			.test_key	= &base_inv_true_key_अटल_branch_likely,
		पूर्ण,
		अणु
			.init_state	= false,
			.key		= &base_inv_true_key.key,
			.test_key	= &base_inv_true_key_अटल_branch_unlikely,
		पूर्ण,
		अणु
			.init_state	= false,
			.key		= &base_false_key.key,
			.test_key	= &base_false_key_अटल_branch_likely,
		पूर्ण,
		अणु
			.init_state	= false,
			.key		= &base_false_key.key,
			.test_key	= &base_false_key_अटल_branch_unlikely,
		पूर्ण,
		अणु
			.init_state	= true,
			.key		= &base_inv_false_key.key,
			.test_key	= &base_inv_false_key_अटल_branch_likely,
		पूर्ण,
		अणु
			.init_state	= true,
			.key		= &base_inv_false_key.key,
			.test_key	= &base_inv_false_key_अटल_branch_unlikely,
		पूर्ण,
	पूर्ण;

	size = ARRAY_SIZE(अटल_key_tests);

	ret = verअगरy_keys(अटल_key_tests, size, false);
	अगर (ret)
		जाओ out;

	invert_keys(अटल_key_tests, size);
	ret = verअगरy_keys(अटल_key_tests, size, true);
	अगर (ret)
		जाओ out;

	invert_keys(अटल_key_tests, size);
	ret = verअगरy_keys(अटल_key_tests, size, false);
	अगर (ret)
		जाओ out;
	वापस 0;
out:
	वापस ret;
पूर्ण

अटल व्योम __निकास test_अटल_key_निकास(व्योम)
अणु
पूर्ण

module_init(test_अटल_key_init);
module_निकास(test_अटल_key_निकास);

MODULE_AUTHOR("Jason Baron <jbaron@akamai.com>");
MODULE_LICENSE("GPL");
