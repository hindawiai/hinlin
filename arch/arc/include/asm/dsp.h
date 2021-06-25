<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 Synopsys, Inc. (www.synopsys.com)
 *
 * Author: Eugeniy Paltsev <Eugeniy.Paltsev@synopsys.com>
 */
#अगर_अघोषित __ASM_ARC_DSP_H
#घोषणा __ASM_ARC_DSP_H

#अगर_अघोषित __ASSEMBLY__

/*
 * DSP-related saved रेजिस्टरs - need to be saved only when you are
 * scheduled out.
 * काष्ठाure fields name must correspond to aux रेजिस्टर defenitions क्रम
 * स्वतःmatic offset calculation in DSP_AUX_SAVE_RESTORE macros
 */
काष्ठा dsp_callee_regs अणु
	अचिन्हित दीर्घ ACC0_GLO, ACC0_GHI, DSP_BFLY0, DSP_FFT_CTRL;
#अगर_घोषित CONFIG_ARC_DSP_AGU_USERSPACE
	अचिन्हित दीर्घ AGU_AP0, AGU_AP1, AGU_AP2, AGU_AP3;
	अचिन्हित दीर्घ AGU_OS0, AGU_OS1;
	अचिन्हित दीर्घ AGU_MOD0, AGU_MOD1, AGU_MOD2, AGU_MOD3;
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_ARC_DSP_H */
