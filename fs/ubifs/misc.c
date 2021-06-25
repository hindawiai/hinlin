<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश "ubifs.h"

/* Normal UBIFS messages */
व्योम ubअगरs_msg(स्थिर काष्ठा ubअगरs_info *c, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	pr_notice("UBIFS (ubi%d:%d): %pV\n",
		  c->vi.ubi_num, c->vi.vol_id, &vaf);

	बहु_पूर्ण(args);
पूर्ण								    \

/* UBIFS error messages */
व्योम ubअगरs_err(स्थिर काष्ठा ubअगरs_info *c, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	pr_err("UBIFS error (ubi%d:%d pid %d): %ps: %pV\n",
	       c->vi.ubi_num, c->vi.vol_id, current->pid,
	       __builtin_वापस_address(0),
	       &vaf);

	बहु_पूर्ण(args);
पूर्ण								    \

/* UBIFS warning messages */
व्योम ubअगरs_warn(स्थिर काष्ठा ubअगरs_info *c, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	pr_warn("UBIFS warning (ubi%d:%d pid %d): %ps: %pV\n",
		c->vi.ubi_num, c->vi.vol_id, current->pid,
		__builtin_वापस_address(0),
		&vaf);

	बहु_पूर्ण(args);
पूर्ण

अटल अक्षर *निश्चित_names[] = अणु
	[ASSACT_REPORT] = "report",
	[ASSACT_RO] = "read-only",
	[ASSACT_PANIC] = "panic",
पूर्ण;

स्थिर अक्षर *ubअगरs_निश्चित_action_name(काष्ठा ubअगरs_info *c)
अणु
	वापस निश्चित_names[c->निश्चित_action];
पूर्ण
