<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_CPU_TYPE_H
#घोषणा __ASM_CPU_TYPE_H

/*
 * Sparc (general) CPU types
 */
क्रमागत sparc_cpu अणु
  sun4m       = 0x00,
  sun4d       = 0x01,
  sun4e       = 0x02,
  sun4u       = 0x03, /* V8 ploos ploos */
  sun_unknown = 0x04,
  ap1000      = 0x05, /* almost a sun4m */
  sparc_leon  = 0x06, /* Leon SoC */
पूर्ण;

#अगर_घोषित CONFIG_SPARC32
बाह्य क्रमागत sparc_cpu sparc_cpu_model;

#घोषणा SUN4M_NCPUS            4              /* Architectural limit of sun4m. */

#अन्यथा

#घोषणा sparc_cpu_model sun4u

#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_CPU_TYPE_H */
