<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2004-2007, 2010-2015 Freescale Semiconductor, Inc.
 * Copyright (C) 2008 Juergen Beisert (kernel@pengutronix.de)
 */

#अगर_अघोषित __ASM_ARCH_MXC_H__
#घोषणा __ASM_ARCH_MXC_H__

#समावेश <linux/types.h>
#समावेश <soc/imx/cpu.h>

#अगर_अघोषित __ASM_ARCH_MXC_HARDWARE_H__
#त्रुटि "Do not include directly."
#पूर्ण_अगर

#घोषणा IMX_DDR_TYPE_LPDDR2		1

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_SOC_IMX6SL
अटल अंतरभूत bool cpu_is_imx6sl(व्योम)
अणु
	वापस __mxc_cpu_type == MXC_CPU_IMX6SL;
पूर्ण
#अन्यथा
अटल अंतरभूत bool cpu_is_imx6sl(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool cpu_is_imx6dl(व्योम)
अणु
	वापस __mxc_cpu_type == MXC_CPU_IMX6DL;
पूर्ण

अटल अंतरभूत bool cpu_is_imx6sx(व्योम)
अणु
	वापस __mxc_cpu_type == MXC_CPU_IMX6SX;
पूर्ण

अटल अंतरभूत bool cpu_is_imx6ul(व्योम)
अणु
	वापस __mxc_cpu_type == MXC_CPU_IMX6UL;
पूर्ण

अटल अंतरभूत bool cpu_is_imx6ull(व्योम)
अणु
	वापस __mxc_cpu_type == MXC_CPU_IMX6ULL;
पूर्ण

अटल अंतरभूत bool cpu_is_imx6ulz(व्योम)
अणु
	वापस __mxc_cpu_type == MXC_CPU_IMX6ULZ;
पूर्ण

अटल अंतरभूत bool cpu_is_imx6sll(व्योम)
अणु
	वापस __mxc_cpu_type == MXC_CPU_IMX6SLL;
पूर्ण

अटल अंतरभूत bool cpu_is_imx6q(व्योम)
अणु
	वापस __mxc_cpu_type == MXC_CPU_IMX6Q;
पूर्ण

अटल अंतरभूत bool cpu_is_imx7d(व्योम)
अणु
	वापस __mxc_cpu_type == MXC_CPU_IMX7D;
पूर्ण

काष्ठा cpu_op अणु
	u32 cpu_rate;
पूर्ण;

पूर्णांक tzic_enable_wake(व्योम);

बाह्य काष्ठा cpu_op *(*get_cpu_op)(पूर्णांक *op);
#पूर्ण_अगर

#घोषणा imx_पढ़ोl	पढ़ोl_relaxed
#घोषणा imx_पढ़ोw	पढ़ोw_relaxed
#घोषणा imx_ग_लिखोl	ग_लिखोl_relaxed
#घोषणा imx_ग_लिखोw	ग_लिखोw_relaxed

#पूर्ण_अगर /*  __ASM_ARCH_MXC_H__ */
