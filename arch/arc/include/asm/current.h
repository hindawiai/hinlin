<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Vineetg: May 16th, 2008
 *  - Current macro is now implemented as "global register" r25
 */

#अगर_अघोषित _ASM_ARC_CURRENT_H
#घोषणा _ASM_ARC_CURRENT_H

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_ARC_CURR_IN_REG

रेजिस्टर काष्ठा task_काष्ठा *curr_arc यंत्र("r25");
#घोषणा current (curr_arc)

#अन्यथा
#समावेश <यंत्र-generic/current.h>
#पूर्ण_अगर /* ! CONFIG_ARC_CURR_IN_REG */

#पूर्ण_अगर /* ! __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_ARC_CURRENT_H */
