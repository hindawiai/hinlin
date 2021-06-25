<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * flat.h -- uClinux flat-क्रमmat executables
 */

#अगर_अघोषित __M68KNOMMU_FLAT_H__
#घोषणा __M68KNOMMU_FLAT_H__

#समावेश <यंत्र-generic/flat.h>

#घोषणा FLAT_PLAT_INIT(regs) \
	करो अणु \
		अगर (current->mm) \
			(regs)->d5 = current->mm->start_data; \
	पूर्ण जबतक (0)

#पूर्ण_अगर /* __M68KNOMMU_FLAT_H__ */
