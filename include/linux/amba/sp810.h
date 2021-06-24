<शैली गुरु>
/*
 * ARM PrimeXsys System Controller SP810 header file
 *
 * Copyright (C) 2009 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __AMBA_SP810_H
#घोषणा __AMBA_SP810_H

#समावेश <linux/पन.स>

/* sysctl रेजिस्टरs offset */
#घोषणा SCCTRL			0x000
#घोषणा SCSYSSTAT		0x004
#घोषणा SCIMCTRL		0x008
#घोषणा SCIMSTAT		0x00C
#घोषणा SCXTALCTRL		0x010
#घोषणा SCPLLCTRL		0x014
#घोषणा SCPLLFCTRL		0x018
#घोषणा SCPERCTRL0		0x01C
#घोषणा SCPERCTRL1		0x020
#घोषणा SCPEREN			0x024
#घोषणा SCPERDIS		0x028
#घोषणा SCPERCLKEN		0x02C
#घोषणा SCPERSTAT		0x030
#घोषणा SCSYSID0		0xEE0
#घोषणा SCSYSID1		0xEE4
#घोषणा SCSYSID2		0xEE8
#घोषणा SCSYSID3		0xEEC
#घोषणा SCITCR			0xF00
#घोषणा SCITIR0			0xF04
#घोषणा SCITIR1			0xF08
#घोषणा SCITOR			0xF0C
#घोषणा SCCNTCTRL		0xF10
#घोषणा SCCNTDATA		0xF14
#घोषणा SCCNTSTEP		0xF18
#घोषणा SCPERIPHID0		0xFE0
#घोषणा SCPERIPHID1		0xFE4
#घोषणा SCPERIPHID2		0xFE8
#घोषणा SCPERIPHID3		0xFEC
#घोषणा SCPCELLID0		0xFF0
#घोषणा SCPCELLID1		0xFF4
#घोषणा SCPCELLID2		0xFF8
#घोषणा SCPCELLID3		0xFFC

#घोषणा SCCTRL_TIMERENnSEL_SHIFT(n)	(15 + ((n) * 2))

अटल अंतरभूत व्योम sysctl_soft_reset(व्योम __iomem *base)
अणु
	/* चयन to slow mode */
	ग_लिखोl(0x2, base + SCCTRL);

	/* writing any value to SCSYSSTAT reg will reset प्रणाली */
	ग_लिखोl(0, base + SCSYSSTAT);
पूर्ण

#पूर्ण_अगर /* __AMBA_SP810_H */
