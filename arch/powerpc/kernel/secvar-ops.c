<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 IBM Corporation
 * Author: Nayna Jain
 *
 * This file initializes secvar operations क्रम PowerPC Secureboot
 */

#समावेश <linux/cache.h>
#समावेश <यंत्र/secvar.h>

स्थिर काष्ठा secvar_operations *secvar_ops __ro_after_init;

व्योम set_secvar_ops(स्थिर काष्ठा secvar_operations *ops)
अणु
	secvar_ops = ops;
पूर्ण
