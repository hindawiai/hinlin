<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * traps.h:  Format of entries क्रम the Sparc trap table.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */
#अगर_अघोषित _SPARC_TRAPS_H
#घोषणा _SPARC_TRAPS_H

#समावेश <uapi/यंत्र/traps.h>

#अगर_अघोषित __ASSEMBLY__
/* This is क्रम V8 compliant Sparc CPUS */
काष्ठा tt_entry अणु
	अचिन्हित दीर्घ inst_one;
	अचिन्हित दीर्घ inst_two;
	अचिन्हित दीर्घ inst_three;
	अचिन्हित दीर्घ inst_four;
पूर्ण;

/* We set this to _start in प्रणाली setup. */
बाह्य काष्ठा tt_entry *sparc_ttable;

#पूर्ण_अगर /* !(__ASSEMBLY__) */
#पूर्ण_अगर /* !(_SPARC_TRAPS_H) */
