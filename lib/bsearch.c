<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * A generic implementation of binary search क्रम the Linux kernel
 *
 * Copyright (C) 2008-2009 Ksplice, Inc.
 * Author: Tim Abbott <tabbott@ksplice.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/kprobes.h>

/*
 * द्वा_खोज - binary search an array of elements
 * @key: poपूर्णांकer to item being searched क्रम
 * @base: poपूर्णांकer to first element to search
 * @num: number of elements
 * @size: size of each element
 * @cmp: poपूर्णांकer to comparison function
 *
 * This function करोes a binary search on the given array.  The
 * contents of the array should alपढ़ोy be in ascending sorted order
 * under the provided comparison function.
 *
 * Note that the key need not have the same type as the elements in
 * the array, e.g. key could be a string and the comparison function
 * could compare the string with the काष्ठा's name field.  However, अगर
 * the key and elements in the array are of the same type, you can use
 * the same comparison function क्रम both sort() and द्वा_खोज().
 */
व्योम *द्वा_खोज(स्थिर व्योम *key, स्थिर व्योम *base, माप_प्रकार num, माप_प्रकार size, cmp_func_t cmp)
अणु
	वापस __अंतरभूत_द्वा_खोज(key, base, num, size, cmp);
पूर्ण
EXPORT_SYMBOL(द्वा_खोज);
NOKPROBE_SYMBOL(द्वा_खोज);
