<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/bits.h>
#समावेश "probe.h"

अटल umode_t
not_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr, पूर्णांक i)
अणु
	वापस 0;
पूर्ण

/*
 * Accepts msr[] array with non populated entries as दीर्घ as either
 * msr[i].msr is 0 or msr[i].grp is शून्य. Note that the शेष sysfs
 * visibility is visible when group->is_visible callback is set.
 */
अचिन्हित दीर्घ
perf_msr_probe(काष्ठा perf_msr *msr, पूर्णांक cnt, bool zero, व्योम *data)
अणु
	अचिन्हित दीर्घ avail = 0;
	अचिन्हित पूर्णांक bit;
	u64 val;

	अगर (cnt >= BITS_PER_LONG)
		वापस 0;

	क्रम (bit = 0; bit < cnt; bit++) अणु
		अगर (!msr[bit].no_check) अणु
			काष्ठा attribute_group *grp = msr[bit].grp;
			u64 mask;

			/* skip entry with no group */
			अगर (!grp)
				जारी;

			grp->is_visible = not_visible;

			/* skip unpopulated entry */
			अगर (!msr[bit].msr)
				जारी;

			अगर (msr[bit].test && !msr[bit].test(bit, data))
				जारी;
			/* Virt sucks; you cannot tell अगर a R/O MSR is present :/ */
			अगर (rdmsrl_safe(msr[bit].msr, &val))
				जारी;

			mask = msr[bit].mask;
			अगर (!mask)
				mask = ~0ULL;
			/* Disable zero counters अगर requested. */
			अगर (!zero && !(val & mask))
				जारी;

			grp->is_visible = शून्य;
		पूर्ण
		avail |= BIT(bit);
	पूर्ण

	वापस avail;
पूर्ण
EXPORT_SYMBOL_GPL(perf_msr_probe);
