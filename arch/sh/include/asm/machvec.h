<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/machvec.h
 *
 * Copyright 2000 Stuart Menefy (stuart.menefy@st.com)
 */

#अगर_अघोषित _ASM_SH_MACHVEC_H
#घोषणा _ASM_SH_MACHVEC_H

#समावेश <linux/types.h>
#समावेश <linux/समय.स>
#समावेश <generated/machtypes.h>

काष्ठा sh_machine_vector अणु
	व्योम (*mv_setup)(अक्षर **cmdline_p);
	स्थिर अक्षर *mv_name;

	पूर्णांक (*mv_irq_demux)(पूर्णांक irq);
	व्योम (*mv_init_irq)(व्योम);

#अगर_घोषित CONFIG_HAS_IOPORT_MAP
	व्योम __iomem *(*mv_ioport_map)(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक size);
	व्योम (*mv_ioport_unmap)(व्योम __iomem *);
#पूर्ण_अगर

	पूर्णांक (*mv_clk_init)(व्योम);
	पूर्णांक (*mv_mode_pins)(व्योम);

	व्योम (*mv_mem_init)(व्योम);
	व्योम (*mv_mem_reserve)(व्योम);
पूर्ण;

बाह्य काष्ठा sh_machine_vector sh_mv;

#घोषणा get_प्रणाली_type()	sh_mv.mv_name

#घोषणा __iniपंचांगv \
	__used __section(".machvec.init")

#पूर्ण_अगर /* _ASM_SH_MACHVEC_H */
