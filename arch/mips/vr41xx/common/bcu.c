<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  bcu.c, Bus Control Unit routines क्रम the NEC VR4100 series.
 *
 *  Copyright (C) 2002	MontaVista Software Inc.
 *    Author: Yoichi Yuasa <source@mvista.com>
 *  Copyright (C) 2003-2005  Yoichi Yuasa <yuasa@linux-mips.org>
 */
/*
 * Changes:
 *  MontaVista Software Inc. <source@mvista.com>
 *  - New creation, NEC VR4122 and VR4131 are supported.
 *  - Added support क्रम NEC VR4111 and VR4121.
 *
 *  Yoichi Yuasa <yuasa@linux-mips.org>
 *  - Added support क्रम NEC VR4133.
 */
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/पन.स>

#घोषणा CLKSPEEDREG_TYPE1	(व्योम __iomem *)KSEG1ADDR(0x0b000014)
#घोषणा CLKSPEEDREG_TYPE2	(व्योम __iomem *)KSEG1ADDR(0x0f000014)
 #घोषणा CLKSP(x)		((x) & 0x001f)
 #घोषणा CLKSP_VR4133(x)	((x) & 0x0007)

 #घोषणा DIV2B			0x8000
 #घोषणा DIV3B			0x4000
 #घोषणा DIV4B			0x2000

 #घोषणा DIVT(x)		(((x) & 0xf000) >> 12)
 #घोषणा DIVVT(x)		(((x) & 0x0f00) >> 8)

 #घोषणा TDIVMODE(x)		(2 << (((x) & 0x1000) >> 12))
 #घोषणा VTDIVMODE(x)		(((x) & 0x0700) >> 8)

अटल अचिन्हित दीर्घ vr41xx_vtघड़ी;
अटल अचिन्हित दीर्घ vr41xx_tघड़ी;

अचिन्हित दीर्घ vr41xx_get_vtघड़ी_frequency(व्योम)
अणु
	वापस vr41xx_vtघड़ी;
पूर्ण

EXPORT_SYMBOL_GPL(vr41xx_get_vtघड़ी_frequency);

अचिन्हित दीर्घ vr41xx_get_tघड़ी_frequency(व्योम)
अणु
	वापस vr41xx_tघड़ी;
पूर्ण

EXPORT_SYMBOL_GPL(vr41xx_get_tघड़ी_frequency);

अटल अंतरभूत uपूर्णांक16_t पढ़ो_clkspeed(व्योम)
अणु
	चयन (current_cpu_type()) अणु
	हाल CPU_VR4111:
	हाल CPU_VR4121: वापस पढ़ोw(CLKSPEEDREG_TYPE1);
	हाल CPU_VR4122:
	हाल CPU_VR4131:
	हाल CPU_VR4133: वापस पढ़ोw(CLKSPEEDREG_TYPE2);
	शेष:
		prपूर्णांकk(KERN_INFO "Unexpected CPU of NEC VR4100 series\n");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ calculate_pघड़ी(uपूर्णांक16_t clkspeed)
अणु
	अचिन्हित दीर्घ pघड़ी = 0;

	चयन (current_cpu_type()) अणु
	हाल CPU_VR4111:
	हाल CPU_VR4121:
		pघड़ी = 18432000 * 64;
		pघड़ी /= CLKSP(clkspeed);
		अवरोध;
	हाल CPU_VR4122:
		pघड़ी = 18432000 * 98;
		pघड़ी /= CLKSP(clkspeed);
		अवरोध;
	हाल CPU_VR4131:
		pघड़ी = 18432000 * 108;
		pघड़ी /= CLKSP(clkspeed);
		अवरोध;
	हाल CPU_VR4133:
		चयन (CLKSP_VR4133(clkspeed)) अणु
		हाल 0:
			pघड़ी = 133000000;
			अवरोध;
		हाल 1:
			pघड़ी = 149000000;
			अवरोध;
		हाल 2:
			pघड़ी = 165900000;
			अवरोध;
		हाल 3:
			pघड़ी = 199100000;
			अवरोध;
		हाल 4:
			pघड़ी = 265900000;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_INFO "Unknown PClock speed for NEC VR4133\n");
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_INFO "Unexpected CPU of NEC VR4100 series\n");
		अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_INFO "PClock: %ldHz\n", pघड़ी);

	वापस pघड़ी;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ calculate_vtघड़ी(uपूर्णांक16_t clkspeed, अचिन्हित दीर्घ pघड़ी)
अणु
	अचिन्हित दीर्घ vtघड़ी = 0;

	चयन (current_cpu_type()) अणु
	हाल CPU_VR4111:
		/* The NEC VR4111 करोesn't have the VTClock. */
		अवरोध;
	हाल CPU_VR4121:
		vtघड़ी = pघड़ी;
		/* DIVVT == 9 Divide by 1.5 . VTClock = (PClock * 6) / 9 */
		अगर (DIVVT(clkspeed) == 9)
			vtघड़ी = pघड़ी * 6;
		/* DIVVT == 10 Divide by 2.5 . VTClock = (PClock * 4) / 10 */
		अन्यथा अगर (DIVVT(clkspeed) == 10)
			vtघड़ी = pघड़ी * 4;
		vtघड़ी /= DIVVT(clkspeed);
		prपूर्णांकk(KERN_INFO "VTClock: %ldHz\n", vtघड़ी);
		अवरोध;
	हाल CPU_VR4122:
		अगर(VTDIVMODE(clkspeed) == 7)
			vtघड़ी = pघड़ी / 1;
		अन्यथा अगर(VTDIVMODE(clkspeed) == 1)
			vtघड़ी = pघड़ी / 2;
		अन्यथा
			vtघड़ी = pघड़ी / VTDIVMODE(clkspeed);
		prपूर्णांकk(KERN_INFO "VTClock: %ldHz\n", vtघड़ी);
		अवरोध;
	हाल CPU_VR4131:
	हाल CPU_VR4133:
		vtघड़ी = pघड़ी / VTDIVMODE(clkspeed);
		prपूर्णांकk(KERN_INFO "VTClock: %ldHz\n", vtघड़ी);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_INFO "Unexpected CPU of NEC VR4100 series\n");
		अवरोध;
	पूर्ण

	वापस vtघड़ी;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ calculate_tघड़ी(uपूर्णांक16_t clkspeed, अचिन्हित दीर्घ pघड़ी,
					     अचिन्हित दीर्घ vtघड़ी)
अणु
	अचिन्हित दीर्घ tघड़ी = 0;

	चयन (current_cpu_type()) अणु
	हाल CPU_VR4111:
		अगर (!(clkspeed & DIV2B))
			tघड़ी = pघड़ी / 2;
		अन्यथा अगर (!(clkspeed & DIV3B))
			tघड़ी = pघड़ी / 3;
		अन्यथा अगर (!(clkspeed & DIV4B))
			tघड़ी = pघड़ी / 4;
		अवरोध;
	हाल CPU_VR4121:
		tघड़ी = pघड़ी / DIVT(clkspeed);
		अवरोध;
	हाल CPU_VR4122:
	हाल CPU_VR4131:
	हाल CPU_VR4133:
		tघड़ी = vtघड़ी / TDIVMODE(clkspeed);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_INFO "Unexpected CPU of NEC VR4100 series\n");
		अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_INFO "TClock: %ldHz\n", tघड़ी);

	वापस tघड़ी;
पूर्ण

व्योम vr41xx_calculate_घड़ी_frequency(व्योम)
अणु
	अचिन्हित दीर्घ pघड़ी;
	uपूर्णांक16_t clkspeed;

	clkspeed = पढ़ो_clkspeed();

	pघड़ी = calculate_pघड़ी(clkspeed);
	vr41xx_vtघड़ी = calculate_vtघड़ी(clkspeed, pघड़ी);
	vr41xx_tघड़ी = calculate_tघड़ी(clkspeed, pघड़ी, vr41xx_vtघड़ी);
पूर्ण

EXPORT_SYMBOL_GPL(vr41xx_calculate_घड़ी_frequency);
