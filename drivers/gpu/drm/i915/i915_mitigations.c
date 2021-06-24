<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2021 Intel Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश "i915_drv.h"
#समावेश "i915_mitigations.h"

अटल अचिन्हित दीर्घ mitigations __पढ़ो_mostly = ~0UL;

क्रमागत अणु
	CLEAR_RESIDUALS = 0,
पूर्ण;

अटल स्थिर अक्षर * स्थिर names[] = अणु
	[CLEAR_RESIDUALS] = "residuals",
पूर्ण;

bool i915_mitigate_clear_residuals(व्योम)
अणु
	वापस READ_ONCE(mitigations) & BIT(CLEAR_RESIDUALS);
पूर्ण

अटल पूर्णांक mitigations_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित दीर्घ new = ~0UL;
	अक्षर *str, *sep, *tok;
	bool first = true;
	पूर्णांक err = 0;

	BUILD_BUG_ON(ARRAY_SIZE(names) >= BITS_PER_TYPE(mitigations));

	str = kstrdup(val, GFP_KERNEL);
	अगर (!str)
		वापस -ENOMEM;

	क्रम (sep = str; (tok = strsep(&sep, ","));) अणु
		bool enable = true;
		पूर्णांक i;

		/* Be tolerant of leading/trailing whitespace */
		tok = strim(tok);

		अगर (first) अणु
			first = false;

			अगर (!म_भेद(tok, "auto"))
				जारी;

			new = 0;
			अगर (!म_भेद(tok, "off"))
				जारी;
		पूर्ण

		अगर (*tok == '!') अणु
			enable = !enable;
			tok++;
		पूर्ण

		अगर (!म_भेदन(tok, "no", 2)) अणु
			enable = !enable;
			tok += 2;
		पूर्ण

		अगर (*tok == '\0')
			जारी;

		क्रम (i = 0; i < ARRAY_SIZE(names); i++) अणु
			अगर (!म_भेद(tok, names[i])) अणु
				अगर (enable)
					new |= BIT(i);
				अन्यथा
					new &= ~BIT(i);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == ARRAY_SIZE(names)) अणु
			pr_err("Bad \"%s.mitigations=%s\", '%s' is unknown\n",
			       DRIVER_NAME, val, tok);
			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण
	kमुक्त(str);
	अगर (err)
		वापस err;

	WRITE_ONCE(mitigations, new);
	वापस 0;
पूर्ण

अटल पूर्णांक mitigations_get(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित दीर्घ local = READ_ONCE(mitigations);
	पूर्णांक count, i;
	bool enable;

	अगर (!local)
		वापस scnम_लिखो(buffer, PAGE_SIZE, "%s\n", "off");

	अगर (local & BIT(BITS_PER_LONG - 1)) अणु
		count = scnम_लिखो(buffer, PAGE_SIZE, "%s,", "auto");
		enable = false;
	पूर्ण अन्यथा अणु
		enable = true;
		count = 0;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(names); i++) अणु
		अगर ((local & BIT(i)) != enable)
			जारी;

		count += scnम_लिखो(buffer + count, PAGE_SIZE - count,
				   "%s%s,", enable ? "" : "!", names[i]);
	पूर्ण

	buffer[count - 1] = '\n';
	वापस count;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops ops = अणु
	.set = mitigations_set,
	.get = mitigations_get,
पूर्ण;

module_param_cb_unsafe(mitigations, &ops, शून्य, 0600);
MODULE_PARM_DESC(mitigations,
"Selectively enable security mitigations for all Intelतऍ GPUs in the system.\n"
"\n"
"  auto -- enables all mitigations required for the platform [default]\n"
"  off  -- disables all mitigations\n"
"\n"
"Individual mitigations can be enabled by passing a comma-separated string,\n"
"e.g. mitigations=residuals to enable only clearing residuals or\n"
"mitigations=auto,noresiduals to disable only the clear residual mitigation.\n"
"Either '!' or 'no' may be used to switch from enabling the mitigation to\n"
"disabling it.\n"
"\n"
"Active mitigations for Ivybridge, Baytrail, Haswell:\n"
"  residuals -- clear all thread-local registers between contexts"
);
