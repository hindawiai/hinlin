<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <linux/cpu.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>

/**
 * x86_match_cpu - match current CPU again an array of x86_cpu_ids
 * @match: Poपूर्णांकer to array of x86_cpu_ids. Last entry terminated with
 *         अणुपूर्ण.
 *
 * Return the entry अगर the current CPU matches the entries in the
 * passed x86_cpu_id match table. Otherwise शून्य.  The match table
 * contains venकरोr (X86_VENDOR_*), family, model and feature bits or
 * respective wildcard entries.
 *
 * A typical table entry would be to match a specअगरic CPU
 *
 * X86_MATCH_VENDOR_FAM_MODEL_FEATURE(INTEL, 6, INTEL_FAM6_BROADWELL,
 *				      X86_FEATURE_ANY, शून्य);
 *
 * Fields can be wildcarded with %X86_VENDOR_ANY, %X86_FAMILY_ANY,
 * %X86_MODEL_ANY, %X86_FEATURE_ANY (except क्रम venकरोr)
 *
 * यंत्र/cpu_device_id.h contains a set of useful macros which are लघुcuts
 * क्रम various common selections. The above can be लघुened to:
 *
 * X86_MATCH_INTEL_FAM6_MODEL(BROADWELL, शून्य);
 *
 * Arrays used to match क्रम this should also be declared using
 * MODULE_DEVICE_TABLE(x86cpu, ...)
 *
 * This always matches against the boot cpu, assuming models and features are
 * consistent over all CPUs.
 */
स्थिर काष्ठा x86_cpu_id *x86_match_cpu(स्थिर काष्ठा x86_cpu_id *match)
अणु
	स्थिर काष्ठा x86_cpu_id *m;
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;

	क्रम (m = match;
	     m->venकरोr | m->family | m->model | m->steppings | m->feature;
	     m++) अणु
		अगर (m->venकरोr != X86_VENDOR_ANY && c->x86_venकरोr != m->venकरोr)
			जारी;
		अगर (m->family != X86_FAMILY_ANY && c->x86 != m->family)
			जारी;
		अगर (m->model != X86_MODEL_ANY && c->x86_model != m->model)
			जारी;
		अगर (m->steppings != X86_STEPPING_ANY &&
		    !(BIT(c->x86_stepping) & m->steppings))
			जारी;
		अगर (m->feature != X86_FEATURE_ANY && !cpu_has(c, m->feature))
			जारी;
		वापस m;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(x86_match_cpu);

अटल स्थिर काष्ठा x86_cpu_desc *
x86_match_cpu_with_stepping(स्थिर काष्ठा x86_cpu_desc *match)
अणु
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;
	स्थिर काष्ठा x86_cpu_desc *m;

	क्रम (m = match; m->x86_family | m->x86_model; m++) अणु
		अगर (c->x86_venकरोr != m->x86_venकरोr)
			जारी;
		अगर (c->x86 != m->x86_family)
			जारी;
		अगर (c->x86_model != m->x86_model)
			जारी;
		अगर (c->x86_stepping != m->x86_stepping)
			जारी;
		वापस m;
	पूर्ण
	वापस शून्य;
पूर्ण

bool x86_cpu_has_min_microcode_rev(स्थिर काष्ठा x86_cpu_desc *table)
अणु
	स्थिर काष्ठा x86_cpu_desc *res = x86_match_cpu_with_stepping(table);

	अगर (!res || res->x86_microcode_rev > boot_cpu_data.microcode)
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(x86_cpu_has_min_microcode_rev);
