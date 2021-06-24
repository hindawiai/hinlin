<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASMARC_SEGMENT_H
#घोषणा __ASMARC_SEGMENT_H

#अगर_अघोषित __ASSEMBLY__

प्रकार अचिन्हित दीर्घ mm_segment_t;

#घोषणा MAKE_MM_SEG(s)	((mm_segment_t) अणु (s) पूर्ण)

#घोषणा KERNEL_DS		MAKE_MM_SEG(0)
#घोषणा USER_DS			MAKE_MM_SEG(TASK_SIZE)
#घोषणा uaccess_kernel()	(get_fs() == KERNEL_DS)

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASMARC_SEGMENT_H */
