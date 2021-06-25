<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SDK7786 FPGA NMI Support.
 *
 * Copyright (C) 2010  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <mach/fpga.h>

क्रमागत अणु
	NMI_MODE_MANUAL,
	NMI_MODE_AUX,
	NMI_MODE_MASKED,
	NMI_MODE_ANY,
	NMI_MODE_UNKNOWN,
पूर्ण;

/*
 * Default to the manual NMI चयन.
 */
अटल अचिन्हित पूर्णांक __initdata nmi_mode = NMI_MODE_ANY;

अटल पूर्णांक __init nmi_mode_setup(अक्षर *str)
अणु
	अगर (!str)
		वापस 0;

	अगर (म_भेद(str, "manual") == 0)
		nmi_mode = NMI_MODE_MANUAL;
	अन्यथा अगर (म_भेद(str, "aux") == 0)
		nmi_mode = NMI_MODE_AUX;
	अन्यथा अगर (म_भेद(str, "masked") == 0)
		nmi_mode = NMI_MODE_MASKED;
	अन्यथा अगर (म_भेद(str, "any") == 0)
		nmi_mode = NMI_MODE_ANY;
	अन्यथा अणु
		nmi_mode = NMI_MODE_UNKNOWN;
		pr_warn("Unknown NMI mode %s\n", str);
	पूर्ण

	prपूर्णांकk("Set NMI mode to %d\n", nmi_mode);
	वापस 0;
पूर्ण
early_param("nmi_mode", nmi_mode_setup);

व्योम __init sdk7786_nmi_init(व्योम)
अणु
	अचिन्हित पूर्णांक source, mask, पंचांगp;

	चयन (nmi_mode) अणु
	हाल NMI_MODE_MANUAL:
		source = NMISR_MAN_NMI;
		mask = NMIMR_MAN_NMIM;
		अवरोध;
	हाल NMI_MODE_AUX:
		source = NMISR_AUX_NMI;
		mask = NMIMR_AUX_NMIM;
		अवरोध;
	हाल NMI_MODE_ANY:
		source = NMISR_MAN_NMI | NMISR_AUX_NMI;
		mask = NMIMR_MAN_NMIM | NMIMR_AUX_NMIM;
		अवरोध;
	हाल NMI_MODE_MASKED:
	हाल NMI_MODE_UNKNOWN:
	शेष:
		source = mask = 0;
		अवरोध;
	पूर्ण

	/* Set the NMI source */
	पंचांगp = fpga_पढ़ो_reg(NMISR);
	पंचांगp &= ~NMISR_MASK;
	पंचांगp |= source;
	fpga_ग_लिखो_reg(पंचांगp, NMISR);

	/* And the IRQ masking */
	fpga_ग_लिखो_reg(NMIMR_MASK ^ mask, NMIMR);
पूर्ण
