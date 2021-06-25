<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * resource.h: Resource definitions.
 *
 * Copyright (C) 1995,1996 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित _SPARC_RESOURCE_H
#घोषणा _SPARC_RESOURCE_H

/*
 * These two resource limit IDs have a Sparc/Linux-specअगरic ordering,
 * the rest comes from the generic header:
 */
#घोषणा RLIMIT_NOखाता		6	/* max number of खोलो files */
#घोषणा RLIMIT_NPROC		7	/* max number of processes */

#अगर defined(__sparc__) && defined(__arch64__)
/* Use generic version */
#अन्यथा
/*
 * SuS says limits have to be अचिन्हित.
 * We make this अचिन्हित, but keep the
 * old value क्रम compatibility:
 */
#घोषणा RLIM_अनन्त		0x7fffffff
#पूर्ण_अगर

#समावेश <यंत्र-generic/resource.h>

#पूर्ण_अगर /* !(_SPARC_RESOURCE_H) */
