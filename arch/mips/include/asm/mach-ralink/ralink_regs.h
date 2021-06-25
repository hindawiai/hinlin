<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Ralink SoC रेजिस्टर definitions
 *
 *  Copyright (C) 2013 John Crispin <john@phrozen.org>
 *  Copyright (C) 2008-2010 Gabor Juhos <juhosg@खोलोwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@खोलोwrt.org>
 */

#अगर_अघोषित _RALINK_REGS_H_
#घोषणा _RALINK_REGS_H_

#समावेश <linux/पन.स>

क्रमागत ralink_soc_type अणु
	RALINK_UNKNOWN = 0,
	RT2880_SOC,
	RT3883_SOC,
	RT305X_SOC_RT3050,
	RT305X_SOC_RT3052,
	RT305X_SOC_RT3350,
	RT305X_SOC_RT3352,
	RT305X_SOC_RT5350,
	MT762X_SOC_MT7620A,
	MT762X_SOC_MT7620N,
	MT762X_SOC_MT7621AT,
	MT762X_SOC_MT7628AN,
	MT762X_SOC_MT7688,
पूर्ण;
बाह्य क्रमागत ralink_soc_type ralink_soc;

बाह्य __iomem व्योम *rt_sysc_membase;
बाह्य __iomem व्योम *rt_memc_membase;

अटल अंतरभूत व्योम rt_sysc_w32(u32 val, अचिन्हित reg)
अणु
	__raw_ग_लिखोl(val, rt_sysc_membase + reg);
पूर्ण

अटल अंतरभूत u32 rt_sysc_r32(अचिन्हित reg)
अणु
	वापस __raw_पढ़ोl(rt_sysc_membase + reg);
पूर्ण

अटल अंतरभूत व्योम rt_sysc_m32(u32 clr, u32 set, अचिन्हित reg)
अणु
	u32 val = rt_sysc_r32(reg) & ~clr;

	__raw_ग_लिखोl(val | set, rt_sysc_membase + reg);
पूर्ण

अटल अंतरभूत व्योम rt_memc_w32(u32 val, अचिन्हित reg)
अणु
	__raw_ग_लिखोl(val, rt_memc_membase + reg);
पूर्ण

अटल अंतरभूत u32 rt_memc_r32(अचिन्हित reg)
अणु
	वापस __raw_पढ़ोl(rt_memc_membase + reg);
पूर्ण

#पूर्ण_अगर /* _RALINK_REGS_H_ */
