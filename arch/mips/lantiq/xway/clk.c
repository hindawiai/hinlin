<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2010 John Crispin <john@phrozen.org>
 *  Copyright (C) 2013-2015 Lantiq Beteiligungs-GmbH & Co.KG
 */

#समावेश <linux/पन.स>
#समावेश <linux/export.h>
#समावेश <linux/clk.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <lantiq_soc.h>

#समावेश "../clk.h"

अटल अचिन्हित पूर्णांक ram_घड़ीs[] = अणु
	CLOCK_167M, CLOCK_133M, CLOCK_111M, CLOCK_83M पूर्ण;
#घोषणा DDR_HZ ram_घड़ीs[ltq_cgu_r32(CGU_SYS) & 0x3]

/* legacy xway घड़ी */
#घोषणा CGU_SYS			0x10

/* vr9, ar10/grx390 घड़ी */
#घोषणा CGU_SYS_XRX		0x0c
#घोषणा CGU_IF_CLK_AR10		0x24

अचिन्हित दीर्घ ltq_danube_fpi_hz(व्योम)
अणु
	अचिन्हित दीर्घ ddr_घड़ी = DDR_HZ;

	अगर (ltq_cgu_r32(CGU_SYS) & 0x40)
		वापस ddr_घड़ी >> 1;
	वापस ddr_घड़ी;
पूर्ण

अचिन्हित दीर्घ ltq_danube_cpu_hz(व्योम)
अणु
	चयन (ltq_cgu_r32(CGU_SYS) & 0xc) अणु
	हाल 0:
		वापस CLOCK_333M;
	हाल 4:
		वापस DDR_HZ;
	हाल 8:
		वापस DDR_HZ << 1;
	शेष:
		वापस DDR_HZ >> 1;
	पूर्ण
पूर्ण

अचिन्हित दीर्घ ltq_danube_pp32_hz(व्योम)
अणु
	अचिन्हित पूर्णांक clksys = (ltq_cgu_r32(CGU_SYS) >> 7) & 3;
	अचिन्हित दीर्घ clk;

	चयन (clksys) अणु
	हाल 1:
		clk = CLOCK_240M;
		अवरोध;
	हाल 2:
		clk = CLOCK_222M;
		अवरोध;
	हाल 3:
		clk = CLOCK_133M;
		अवरोध;
	शेष:
		clk = CLOCK_266M;
		अवरोध;
	पूर्ण

	वापस clk;
पूर्ण

अचिन्हित दीर्घ ltq_ar9_sys_hz(व्योम)
अणु
	अगर (((ltq_cgu_r32(CGU_SYS) >> 3) & 0x3) == 0x2)
		वापस CLOCK_393M;
	वापस CLOCK_333M;
पूर्ण

अचिन्हित दीर्घ ltq_ar9_fpi_hz(व्योम)
अणु
	अचिन्हित दीर्घ sys = ltq_ar9_sys_hz();

	अगर (ltq_cgu_r32(CGU_SYS) & BIT(0))
		वापस sys / 3;
	अन्यथा
		वापस sys / 2;
पूर्ण

अचिन्हित दीर्घ ltq_ar9_cpu_hz(व्योम)
अणु
	अगर (ltq_cgu_r32(CGU_SYS) & BIT(2))
		वापस ltq_ar9_fpi_hz();
	अन्यथा
		वापस ltq_ar9_sys_hz();
पूर्ण

अचिन्हित दीर्घ ltq_vr9_cpu_hz(व्योम)
अणु
	अचिन्हित पूर्णांक cpu_sel;
	अचिन्हित दीर्घ clk;

	cpu_sel = (ltq_cgu_r32(CGU_SYS_XRX) >> 4) & 0xf;

	चयन (cpu_sel) अणु
	हाल 0:
		clk = CLOCK_600M;
		अवरोध;
	हाल 1:
		clk = CLOCK_500M;
		अवरोध;
	हाल 2:
		clk = CLOCK_393M;
		अवरोध;
	हाल 3:
		clk = CLOCK_333M;
		अवरोध;
	हाल 5:
	हाल 6:
		clk = CLOCK_196_608M;
		अवरोध;
	हाल 7:
		clk = CLOCK_167M;
		अवरोध;
	हाल 4:
	हाल 8:
	हाल 9:
		clk = CLOCK_125M;
		अवरोध;
	शेष:
		clk = 0;
		अवरोध;
	पूर्ण

	वापस clk;
पूर्ण

अचिन्हित दीर्घ ltq_vr9_fpi_hz(व्योम)
अणु
	अचिन्हित पूर्णांक ocp_sel, cpu_clk;
	अचिन्हित दीर्घ clk;

	cpu_clk = ltq_vr9_cpu_hz();
	ocp_sel = ltq_cgu_r32(CGU_SYS_XRX) & 0x3;

	चयन (ocp_sel) अणु
	हाल 0:
		/* OCP ratio 1 */
		clk = cpu_clk;
		अवरोध;
	हाल 2:
		/* OCP ratio 2 */
		clk = cpu_clk / 2;
		अवरोध;
	हाल 3:
		/* OCP ratio 2.5 */
		clk = (cpu_clk * 2) / 5;
		अवरोध;
	हाल 4:
		/* OCP ratio 3 */
		clk = cpu_clk / 3;
		अवरोध;
	शेष:
		clk = 0;
		अवरोध;
	पूर्ण

	वापस clk;
पूर्ण

अचिन्हित दीर्घ ltq_vr9_pp32_hz(व्योम)
अणु
	अचिन्हित पूर्णांक clksys = (ltq_cgu_r32(CGU_SYS) >> 16) & 0x7;
	अचिन्हित दीर्घ clk;

	चयन (clksys) अणु
	हाल 0:
		clk = CLOCK_500M;
		अवरोध;
	हाल 1:
		clk = CLOCK_432M;
		अवरोध;
	हाल 2:
		clk = CLOCK_288M;
		अवरोध;
	शेष:
		clk = CLOCK_500M;
		अवरोध;
	पूर्ण

	वापस clk;
पूर्ण

अचिन्हित दीर्घ ltq_ar10_cpu_hz(व्योम)
अणु
	अचिन्हित पूर्णांक clksys;
	पूर्णांक cpu_fs = (ltq_cgu_r32(CGU_SYS_XRX) >> 8) & 0x1;
	पूर्णांक freq_भाग = (ltq_cgu_r32(CGU_SYS_XRX) >> 4) & 0x7;

	चयन (cpu_fs) अणु
	हाल 0:
		clksys = CLOCK_500M;
		अवरोध;
	हाल 1:
		clksys = CLOCK_600M;
		अवरोध;
	शेष:
		clksys = CLOCK_500M;
		अवरोध;
	पूर्ण

	चयन (freq_भाग) अणु
	हाल 0:
		वापस clksys;
	हाल 1:
		वापस clksys >> 1;
	हाल 2:
		वापस clksys >> 2;
	शेष:
		वापस clksys;
	पूर्ण
पूर्ण

अचिन्हित दीर्घ ltq_ar10_fpi_hz(व्योम)
अणु
	पूर्णांक freq_fpi = (ltq_cgu_r32(CGU_IF_CLK_AR10) >> 25) & 0xf;

	चयन (freq_fpi) अणु
	हाल 1:
		वापस CLOCK_300M;
	हाल 5:
		वापस CLOCK_250M;
	हाल 2:
		वापस CLOCK_150M;
	हाल 6:
		वापस CLOCK_125M;

	शेष:
		वापस CLOCK_125M;
	पूर्ण
पूर्ण

अचिन्हित दीर्घ ltq_ar10_pp32_hz(व्योम)
अणु
	अचिन्हित पूर्णांक clksys = (ltq_cgu_r32(CGU_SYS) >> 16) & 0x7;
	अचिन्हित दीर्घ clk;

	चयन (clksys) अणु
	हाल 1:
		clk = CLOCK_250M;
		अवरोध;
	हाल 4:
		clk = CLOCK_400M;
		अवरोध;
	शेष:
		clk = CLOCK_250M;
		अवरोध;
	पूर्ण

	वापस clk;
पूर्ण

अचिन्हित दीर्घ ltq_grx390_cpu_hz(व्योम)
अणु
	अचिन्हित पूर्णांक clksys;
	पूर्णांक cpu_fs = ((ltq_cgu_r32(CGU_SYS_XRX) >> 9) & 0x3);
	पूर्णांक freq_भाग = ((ltq_cgu_r32(CGU_SYS_XRX) >> 4) & 0x7);

	चयन (cpu_fs) अणु
	हाल 0:
		clksys = CLOCK_600M;
		अवरोध;
	हाल 1:
		clksys = CLOCK_666M;
		अवरोध;
	हाल 2:
		clksys = CLOCK_720M;
		अवरोध;
	शेष:
		clksys = CLOCK_600M;
		अवरोध;
	पूर्ण

	चयन (freq_भाग) अणु
	हाल 0:
		वापस clksys;
	हाल 1:
		वापस clksys >> 1;
	हाल 2:
		वापस clksys >> 2;
	शेष:
		वापस clksys;
	पूर्ण
पूर्ण

अचिन्हित दीर्घ ltq_grx390_fpi_hz(व्योम)
अणु
	/* fpi घड़ी is derived from ddr_clk */
	अचिन्हित पूर्णांक clksys;
	पूर्णांक cpu_fs = ((ltq_cgu_r32(CGU_SYS_XRX) >> 9) & 0x3);
	पूर्णांक freq_भाग = ((ltq_cgu_r32(CGU_SYS_XRX)) & 0x7);
	चयन (cpu_fs) अणु
	हाल 0:
		clksys = CLOCK_600M;
		अवरोध;
	हाल 1:
		clksys = CLOCK_666M;
		अवरोध;
	हाल 2:
		clksys = CLOCK_720M;
		अवरोध;
	शेष:
		clksys = CLOCK_600M;
		अवरोध;
	पूर्ण

	चयन (freq_भाग) अणु
	हाल 1:
		वापस clksys >> 1;
	हाल 2:
		वापस clksys >> 2;
	शेष:
		वापस clksys >> 1;
	पूर्ण
पूर्ण

अचिन्हित दीर्घ ltq_grx390_pp32_hz(व्योम)
अणु
	अचिन्हित पूर्णांक clksys = (ltq_cgu_r32(CGU_SYS) >> 16) & 0x7;
	अचिन्हित दीर्घ clk;

	चयन (clksys) अणु
	हाल 1:
		clk = CLOCK_250M;
		अवरोध;
	हाल 2:
		clk = CLOCK_432M;
		अवरोध;
	हाल 4:
		clk = CLOCK_400M;
		अवरोध;
	शेष:
		clk = CLOCK_250M;
		अवरोध;
	पूर्ण
	वापस clk;
पूर्ण
