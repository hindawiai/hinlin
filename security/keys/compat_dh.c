<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* 32-bit compatibility syscall क्रम 64-bit प्रणालीs क्रम DH operations
 *
 * Copyright (C) 2016 Stephan Mueller <smueller@chronox.de>
 */

#समावेश <linux/uaccess.h>

#समावेश "internal.h"

/*
 * Perक्रमm the DH computation or DH based key derivation.
 *
 * If successful, 0 will be वापसed.
 */
दीर्घ compat_keyctl_dh_compute(काष्ठा keyctl_dh_params __user *params,
			      अक्षर __user *buffer, माप_प्रकार buflen,
			      काष्ठा compat_keyctl_kdf_params __user *kdf)
अणु
	काष्ठा keyctl_kdf_params kdfcopy;
	काष्ठा compat_keyctl_kdf_params compat_kdfcopy;

	अगर (!kdf)
		वापस __keyctl_dh_compute(params, buffer, buflen, शून्य);

	अगर (copy_from_user(&compat_kdfcopy, kdf, माप(compat_kdfcopy)) != 0)
		वापस -EFAULT;

	kdfcopy.hashname = compat_ptr(compat_kdfcopy.hashname);
	kdfcopy.otherinfo = compat_ptr(compat_kdfcopy.otherinfo);
	kdfcopy.otherinfolen = compat_kdfcopy.otherinfolen;
	स_नकल(kdfcopy.__spare, compat_kdfcopy.__spare,
	       माप(kdfcopy.__spare));

	वापस __keyctl_dh_compute(params, buffer, buflen, &kdfcopy);
पूर्ण
