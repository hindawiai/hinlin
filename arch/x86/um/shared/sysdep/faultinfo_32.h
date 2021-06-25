<शैली गुरु>
/*
 * Copyright (C) 2004 Fujitsu Siemens Computers GmbH
 * Author: Boकरो Stroesser <bstroesser@fujitsu-siemens.com>
 * Licensed under the GPL
 */

#अगर_अघोषित __FAULTINFO_I386_H
#घोषणा __FAULTINFO_I386_H

/* this काष्ठाure contains the full arch-specअगरic faultinfo
 * from the traps.
 * On i386, ptrace_faultinfo unक्रमtunately करोesn't provide
 * all the info, since trap_no is missing.
 * All common elements are defined at the same position in
 * both काष्ठाures, thus making it easy to copy the
 * contents without knowledge about the काष्ठाure elements.
 */
काष्ठा faultinfo अणु
        पूर्णांक error_code; /* in ptrace_faultinfo misleadingly called is_ग_लिखो */
        अचिन्हित दीर्घ cr2; /* in ptrace_faultinfo called addr */
        पूर्णांक trap_no; /* missing in ptrace_faultinfo */
पूर्ण;

#घोषणा FAULT_WRITE(fi) ((fi).error_code & 2)
#घोषणा FAULT_ADDRESS(fi) ((fi).cr2)

/* This is Page Fault */
#घोषणा SEGV_IS_FIXABLE(fi)	((fi)->trap_no == 14)

#घोषणा PTRACE_FULL_FAULTINFO 0

#पूर्ण_अगर
