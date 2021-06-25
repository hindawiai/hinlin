<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/cpu.h>

अचिन्हित पूर्णांक x86_family(अचिन्हित पूर्णांक sig)
अणु
	अचिन्हित पूर्णांक x86;

	x86 = (sig >> 8) & 0xf;

	अगर (x86 == 0xf)
		x86 += (sig >> 20) & 0xff;

	वापस x86;
पूर्ण
EXPORT_SYMBOL_GPL(x86_family);

अचिन्हित पूर्णांक x86_model(अचिन्हित पूर्णांक sig)
अणु
	अचिन्हित पूर्णांक fam, model;

	fam = x86_family(sig);

	model = (sig >> 4) & 0xf;

	अगर (fam >= 0x6)
		model += ((sig >> 16) & 0xf) << 4;

	वापस model;
पूर्ण
EXPORT_SYMBOL_GPL(x86_model);

अचिन्हित पूर्णांक x86_stepping(अचिन्हित पूर्णांक sig)
अणु
	वापस sig & 0xf;
पूर्ण
EXPORT_SYMBOL_GPL(x86_stepping);
