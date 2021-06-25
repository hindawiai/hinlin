<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copied from the kernel sources to tools/perf/:
 *
 * Generic barrier definitions.
 *
 * It should be possible to use these on really simple architectures,
 * but it serves more as a starting poपूर्णांक क्रम new ports.
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#अगर_अघोषित __TOOLS_LINUX_ASM_GENERIC_BARRIER_H
#घोषणा __TOOLS_LINUX_ASM_GENERIC_BARRIER_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/compiler.h>

/*
 * Force strict CPU ordering. And yes, this is required on UP too when we're
 * talking to devices.
 *
 * Fall back to compiler barriers अगर nothing better is provided.
 */

#अगर_अघोषित mb
#घोषणा mb()	barrier()
#पूर्ण_अगर

#अगर_अघोषित rmb
#घोषणा rmb()	mb()
#पूर्ण_अगर

#अगर_अघोषित wmb
#घोषणा wmb()	mb()
#पूर्ण_अगर

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* __TOOLS_LINUX_ASM_GENERIC_BARRIER_H */
