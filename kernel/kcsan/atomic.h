<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Rules क्रम implicitly atomic memory accesses.
 *
 * Copyright (C) 2019, Google LLC.
 */

#अगर_अघोषित _KERNEL_KCSAN_ATOMIC_H
#घोषणा _KERNEL_KCSAN_ATOMIC_H

#समावेश <linux/types.h>

/*
 * Special rules क्रम certain memory where concurrent conflicting accesses are
 * common, however, the current convention is to not mark them; वापसs true अगर
 * access to @ptr should be considered atomic. Called from slow-path.
 */
अटल bool kcsan_is_atomic_special(स्थिर अस्थिर व्योम *ptr)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* _KERNEL_KCSAN_ATOMIC_H */
