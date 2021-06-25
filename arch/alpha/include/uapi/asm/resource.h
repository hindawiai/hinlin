<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ALPHA_RESOURCE_H
#घोषणा _ALPHA_RESOURCE_H

/*
 * Alpha/Linux-specअगरic ordering of these four resource limit IDs,
 * the rest comes from the generic header:
 */
#घोषणा RLIMIT_NOखाता		6	/* max number of खोलो files */
#घोषणा RLIMIT_AS		7	/* address space limit */
#घोषणा RLIMIT_NPROC		8	/* max number of processes */
#घोषणा RLIMIT_MEMLOCK		9	/* max locked-in-memory address space */

/*
 * SuS says limits have to be अचिन्हित.  Fine, it's अचिन्हित, but
 * we retain the old value क्रम compatibility, especially with DU. 
 * When you run पूर्णांकo the 2^63 barrier, you call me.
 */
#घोषणा RLIM_अनन्त		0x7ffffffffffffffful

#समावेश <यंत्र-generic/resource.h>

#पूर्ण_अगर /* _ALPHA_RESOURCE_H */
