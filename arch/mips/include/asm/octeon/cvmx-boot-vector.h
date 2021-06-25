<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003-2017 Cavium, Inc.
 */

#अगर_अघोषित __CVMX_BOOT_VECTOR_H__
#घोषणा __CVMX_BOOT_VECTOR_H__

#समावेश <यंत्र/octeon/octeon.h>

/*
 * The boot vector table is made up of an array of 1024 elements of
 * काष्ठा cvmx_boot_vector_element.  There is one entry क्रम each
 * possible MIPS CPUNum, indexed by the CPUNum.
 *
 * Once cvmx_boot_vector_get() वापसs a non-शून्य value (indicating
 * success), NMI to a core will cause execution to transfer to the
 * target_ptr location क्रम that core's entry in the vector table.
 *
 * The काष्ठा cvmx_boot_vector_element fields app0, app1, and app2 can
 * be used by the application that has set the target_ptr in any
 * application specअगरic manner, they are not touched by the vectoring
 * code.
 *
 * The boot vector code clobbers the CP0_DESAVE रेजिस्टर, and on
 * OCTEON II and later CPUs also clobbers CP0_KScratch2.  All GP
 * रेजिस्टरs are preserved, except on pre-OCTEON II CPUs, where k1 is
 * clobbered.
 *
 */


/*
 * Applications install the boot bus code in cvmx-boot-vector.c, which
 * uses this magic:
 */
#घोषणा OCTEON_BOOT_MOVEABLE_MAGIC1 0xdb00110ad358eacdull

काष्ठा cvmx_boot_vector_element अणु
	/* kseg0 or xkphys address of target code. */
	uपूर्णांक64_t target_ptr;
	/* Three application specअगरic arguments. */
	uपूर्णांक64_t app0;
	uपूर्णांक64_t app1;
	uपूर्णांक64_t app2;
पूर्ण;

काष्ठा cvmx_boot_vector_element *cvmx_boot_vector_get(व्योम);

#पूर्ण_अगर /* __CVMX_BOOT_VECTOR_H__ */
