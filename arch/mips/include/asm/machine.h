<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#अगर_अघोषित __MIPS_ASM_MACHINE_H__
#घोषणा __MIPS_ASM_MACHINE_H__

#समावेश <linux/libfdt.h>
#समावेश <linux/of.h>

काष्ठा mips_machine अणु
	स्थिर काष्ठा of_device_id *matches;
	स्थिर व्योम *fdt;
	bool (*detect)(व्योम);
	स्थिर व्योम *(*fixup_fdt)(स्थिर व्योम *fdt, स्थिर व्योम *match_data);
	अचिन्हित पूर्णांक (*measure_hpt_freq)(व्योम);
पूर्ण;

बाह्य दीर्घ __mips_machines_start;
बाह्य दीर्घ __mips_machines_end;

#घोषणा MIPS_MACHINE(name)						\
	अटल स्थिर काष्ठा mips_machine __mips_mach_##name		\
		__used __section(".mips.machines.init")

#घोषणा क्रम_each_mips_machine(mach)					\
	क्रम ((mach) = (काष्ठा mips_machine *)&__mips_machines_start;	\
	     (mach) < (काष्ठा mips_machine *)&__mips_machines_end;	\
	     (mach)++)

/**
 * mips_machine_is_compatible() - check अगर a machine is compatible with an FDT
 * @mach: the machine काष्ठा to check
 * @fdt: the FDT to check क्रम compatibility with
 *
 * Check whether the given machine @mach is compatible with the given flattened
 * device tree @fdt, based upon the compatibility property of the root node.
 *
 * Return: the device id matched अगर any, अन्यथा शून्य
 */
अटल अंतरभूत स्थिर काष्ठा of_device_id *
mips_machine_is_compatible(स्थिर काष्ठा mips_machine *mach, स्थिर व्योम *fdt)
अणु
	स्थिर काष्ठा of_device_id *match;

	अगर (!mach->matches)
		वापस शून्य;

	क्रम (match = mach->matches; match->compatible[0]; match++) अणु
		अगर (fdt_node_check_compatible(fdt, 0, match->compatible) == 0)
			वापस match;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * काष्ठा mips_fdt_fixup - Describe a fixup to apply to an FDT
 * @apply: applies the fixup to @fdt, वापसs zero on success अन्यथा -त्रुटि_सं
 * @description: a लघु description of the fixup
 *
 * Describes a fixup applied to an FDT blob by the @apply function. The
 * @description field provides a लघु description of the fixup पूर्णांकended क्रम
 * use in error messages अगर the @apply function वापसs non-zero.
 */
काष्ठा mips_fdt_fixup अणु
	पूर्णांक (*apply)(व्योम *fdt);
	स्थिर अक्षर *description;
पूर्ण;

/**
 * apply_mips_fdt_fixups() - apply fixups to an FDT blob
 * @fdt_out: buffer in which to place the fixed-up FDT
 * @fdt_out_size: the size of the @fdt_out buffer
 * @fdt_in: the FDT blob
 * @fixups: poपूर्णांकer to an array of fixups to be applied
 *
 * Loop through the array of fixups poपूर्णांकed to by @fixups, calling the apply
 * function on each until either one वापसs an error or we reach the end of
 * the list as indicated by an entry with a शून्य apply field.
 *
 * Return: zero on success, अन्यथा -त्रुटि_सं
 */
बाह्य पूर्णांक __init apply_mips_fdt_fixups(व्योम *fdt_out, माप_प्रकार fdt_out_size,
					स्थिर व्योम *fdt_in,
					स्थिर काष्ठा mips_fdt_fixup *fixups);

#पूर्ण_अगर /* __MIPS_ASM_MACHINE_H__ */
