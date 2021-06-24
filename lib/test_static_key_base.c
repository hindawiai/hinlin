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
काष्ठा अटल_key base_old_true_key = STATIC_KEY_INIT_TRUE;
EXPORT_SYMBOL_GPL(base_old_true_key);
काष्ठा अटल_key base_inv_old_true_key = STATIC_KEY_INIT_TRUE;
EXPORT_SYMBOL_GPL(base_inv_old_true_key);
काष्ठा अटल_key base_old_false_key = STATIC_KEY_INIT_FALSE;
EXPORT_SYMBOL_GPL(base_old_false_key);
काष्ठा अटल_key base_inv_old_false_key = STATIC_KEY_INIT_FALSE;
EXPORT_SYMBOL_GPL(base_inv_old_false_key);

/* new keys */
DEFINE_STATIC_KEY_TRUE(base_true_key);
EXPORT_SYMBOL_GPL(base_true_key);
DEFINE_STATIC_KEY_TRUE(base_inv_true_key);
EXPORT_SYMBOL_GPL(base_inv_true_key);
DEFINE_STATIC_KEY_FALSE(base_false_key);
EXPORT_SYMBOL_GPL(base_false_key);
DEFINE_STATIC_KEY_FALSE(base_inv_false_key);
EXPORT_SYMBOL_GPL(base_inv_false_key);

अटल व्योम invert_key(काष्ठा अटल_key *key)
अणु
	अगर (अटल_key_enabled(key))
		अटल_key_disable(key);
	अन्यथा
		अटल_key_enable(key);
पूर्ण

अटल पूर्णांक __init test_अटल_key_base_init(व्योम)
अणु
	invert_key(&base_inv_old_true_key);
	invert_key(&base_inv_old_false_key);
	invert_key(&base_inv_true_key.key);
	invert_key(&base_inv_false_key.key);

	वापस 0;
पूर्ण

अटल व्योम __निकास test_अटल_key_base_निकास(व्योम)
अणु
पूर्ण

module_init(test_अटल_key_base_init);
module_निकास(test_अटल_key_base_निकास);

MODULE_AUTHOR("Jason Baron <jbaron@akamai.com>");
MODULE_LICENSE("GPL");
