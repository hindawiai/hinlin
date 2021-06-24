<शैली गुरु>
/*
 * Copyright (c) 2017 Oracle and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _ASM_SPARC_CLOCKSOURCE_H
#घोषणा _ASM_SPARC_CLOCKSOURCE_H

/* VDSO घड़ीsources */
#घोषणा VCLOCK_NONE   0  /* Nothing userspace can करो. */
#घोषणा VCLOCK_TICK   1  /* Use %tick.  */
#घोषणा VCLOCK_STICK  2  /* Use %stick. */

काष्ठा arch_घड़ीsource_data अणु
	पूर्णांक vघड़ी_mode;
पूर्ण;

#पूर्ण_अगर /* _ASM_SPARC_CLOCKSOURCE_H */
