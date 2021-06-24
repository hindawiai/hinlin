<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_CPU_SH3_DAC_H
#घोषणा __ASM_CPU_SH3_DAC_H

/*
 * Copyright (C) 2003  Andriy Skulysh
 */


#घोषणा DADR0	0xa40000a0
#घोषणा DADR1	0xa40000a2
#घोषणा DACR	0xa40000a4
#घोषणा DACR_DAOE1	0x80
#घोषणा DACR_DAOE0	0x40
#घोषणा DACR_DAE	0x20


अटल __अंतरभूत__ व्योम sh_dac_enable(पूर्णांक channel)
अणु
	अचिन्हित अक्षर v;
	v = __raw_पढ़ोb(DACR);
	अगर(channel) v |= DACR_DAOE1;
	अन्यथा v |= DACR_DAOE0;
	__raw_ग_लिखोb(v,DACR);
पूर्ण

अटल __अंतरभूत__ व्योम sh_dac_disable(पूर्णांक channel)
अणु
	अचिन्हित अक्षर v;
	v = __raw_पढ़ोb(DACR);
	अगर(channel) v &= ~DACR_DAOE1;
	अन्यथा v &= ~DACR_DAOE0;
	__raw_ग_लिखोb(v,DACR);
पूर्ण

अटल __अंतरभूत__ व्योम sh_dac_output(u8 value, पूर्णांक channel)
अणु
	अगर(channel) __raw_ग_लिखोb(value,DADR1);
	अन्यथा __raw_ग_लिखोb(value,DADR0);
पूर्ण

#पूर्ण_अगर /* __ASM_CPU_SH3_DAC_H */
