<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BOOT_CPUFLAGS_H
#घोषणा BOOT_CPUFLAGS_H

#समावेश <यंत्र/cpufeatures.h>
#समावेश <यंत्र/processor-flags.h>

काष्ठा cpu_features अणु
	पूर्णांक level;		/* Family, or 64 क्रम x86-64 */
	पूर्णांक family;		/* Family, always */
	पूर्णांक model;
	u32 flags[NCAPINTS];
पूर्ण;

बाह्य काष्ठा cpu_features cpu;
बाह्य u32 cpu_venकरोr[3];

पूर्णांक has_eflag(अचिन्हित दीर्घ mask);
व्योम get_cpuflags(व्योम);

#पूर्ण_अगर
