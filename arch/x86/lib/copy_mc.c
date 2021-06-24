<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2016-2020 Intel Corporation. All rights reserved. */

#समावेश <linux/jump_label.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश <यंत्र/mce.h>

#अगर_घोषित CONFIG_X86_MCE
अटल DEFINE_STATIC_KEY_FALSE(copy_mc_fragile_key);

व्योम enable_copy_mc_fragile(व्योम)
अणु
	अटल_branch_inc(&copy_mc_fragile_key);
पूर्ण
#घोषणा copy_mc_fragile_enabled (अटल_branch_unlikely(&copy_mc_fragile_key))

/*
 * Similar to copy_user_handle_tail, probe क्रम the ग_लिखो fault poपूर्णांक, or
 * source exception poपूर्णांक.
 */
__visible notrace अचिन्हित दीर्घ
copy_mc_fragile_handle_tail(अक्षर *to, अक्षर *from, अचिन्हित len)
अणु
	क्रम (; len; --len, to++, from++)
		अगर (copy_mc_fragile(to, from, 1))
			अवरोध;
	वापस len;
पूर्ण
#अन्यथा
/*
 * No poपूर्णांक in करोing careful copying, or consulting a अटल key when
 * there is no #MC handler in the CONFIG_X86_MCE=n हाल.
 */
व्योम enable_copy_mc_fragile(व्योम)
अणु
पूर्ण
#घोषणा copy_mc_fragile_enabled (0)
#पूर्ण_अगर

अचिन्हित दीर्घ copy_mc_enhanced_fast_string(व्योम *dst, स्थिर व्योम *src, अचिन्हित len);

/**
 * copy_mc_to_kernel - memory copy that handles source exceptions
 *
 * @dst:	destination address
 * @src:	source address
 * @len:	number of bytes to copy
 *
 * Call पूर्णांकo the 'fragile' version on प्रणालीs that benefit from aव्योमing
 * corner हाल poison consumption scenarios, For example, accessing
 * poison across 2 cachelines with a single inकाष्ठाion. Almost all
 * other uses हाल can use copy_mc_enhanced_fast_string() क्रम a fast
 * recoverable copy, or fallback to plain स_नकल.
 *
 * Return 0 क्रम success, or number of bytes not copied अगर there was an
 * exception.
 */
अचिन्हित दीर्घ __must_check copy_mc_to_kernel(व्योम *dst, स्थिर व्योम *src, अचिन्हित len)
अणु
	अगर (copy_mc_fragile_enabled)
		वापस copy_mc_fragile(dst, src, len);
	अगर (अटल_cpu_has(X86_FEATURE_ERMS))
		वापस copy_mc_enhanced_fast_string(dst, src, len);
	स_नकल(dst, src, len);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(copy_mc_to_kernel);

अचिन्हित दीर्घ __must_check copy_mc_to_user(व्योम *dst, स्थिर व्योम *src, अचिन्हित len)
अणु
	अचिन्हित दीर्घ ret;

	अगर (copy_mc_fragile_enabled) अणु
		__uaccess_begin();
		ret = copy_mc_fragile(dst, src, len);
		__uaccess_end();
		वापस ret;
	पूर्ण

	अगर (अटल_cpu_has(X86_FEATURE_ERMS)) अणु
		__uaccess_begin();
		ret = copy_mc_enhanced_fast_string(dst, src, len);
		__uaccess_end();
		वापस ret;
	पूर्ण

	वापस copy_user_generic(dst, src, len);
पूर्ण
