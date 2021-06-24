<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012, The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/bug.h>
#समावेश <यंत्र/hardware/cp14.h>

#समावेश "coresight-etm.h"

पूर्णांक eपंचांग_पढ़ोl_cp14(u32 reg, अचिन्हित पूर्णांक *val)
अणु
	चयन (reg) अणु
	हाल ETMCR:
		*val = eपंचांग_पढ़ो(ETMCR);
		वापस 0;
	हाल ETMCCR:
		*val = eपंचांग_पढ़ो(ETMCCR);
		वापस 0;
	हाल ETMTRIGGER:
		*val = eपंचांग_पढ़ो(ETMTRIGGER);
		वापस 0;
	हाल ETMSR:
		*val = eपंचांग_पढ़ो(ETMSR);
		वापस 0;
	हाल ETMSCR:
		*val = eपंचांग_पढ़ो(ETMSCR);
		वापस 0;
	हाल ETMTSSCR:
		*val = eपंचांग_पढ़ो(ETMTSSCR);
		वापस 0;
	हाल ETMTEEVR:
		*val = eपंचांग_पढ़ो(ETMTEEVR);
		वापस 0;
	हाल ETMTECR1:
		*val = eपंचांग_पढ़ो(ETMTECR1);
		वापस 0;
	हाल ETMFFLR:
		*val = eपंचांग_पढ़ो(ETMFFLR);
		वापस 0;
	हाल ETMACVRn(0):
		*val = eपंचांग_पढ़ो(ETMACVR0);
		वापस 0;
	हाल ETMACVRn(1):
		*val = eपंचांग_पढ़ो(ETMACVR1);
		वापस 0;
	हाल ETMACVRn(2):
		*val = eपंचांग_पढ़ो(ETMACVR2);
		वापस 0;
	हाल ETMACVRn(3):
		*val = eपंचांग_पढ़ो(ETMACVR3);
		वापस 0;
	हाल ETMACVRn(4):
		*val = eपंचांग_पढ़ो(ETMACVR4);
		वापस 0;
	हाल ETMACVRn(5):
		*val = eपंचांग_पढ़ो(ETMACVR5);
		वापस 0;
	हाल ETMACVRn(6):
		*val = eपंचांग_पढ़ो(ETMACVR6);
		वापस 0;
	हाल ETMACVRn(7):
		*val = eपंचांग_पढ़ो(ETMACVR7);
		वापस 0;
	हाल ETMACVRn(8):
		*val = eपंचांग_पढ़ो(ETMACVR8);
		वापस 0;
	हाल ETMACVRn(9):
		*val = eपंचांग_पढ़ो(ETMACVR9);
		वापस 0;
	हाल ETMACVRn(10):
		*val = eपंचांग_पढ़ो(ETMACVR10);
		वापस 0;
	हाल ETMACVRn(11):
		*val = eपंचांग_पढ़ो(ETMACVR11);
		वापस 0;
	हाल ETMACVRn(12):
		*val = eपंचांग_पढ़ो(ETMACVR12);
		वापस 0;
	हाल ETMACVRn(13):
		*val = eपंचांग_पढ़ो(ETMACVR13);
		वापस 0;
	हाल ETMACVRn(14):
		*val = eपंचांग_पढ़ो(ETMACVR14);
		वापस 0;
	हाल ETMACVRn(15):
		*val = eपंचांग_पढ़ो(ETMACVR15);
		वापस 0;
	हाल ETMACTRn(0):
		*val = eपंचांग_पढ़ो(ETMACTR0);
		वापस 0;
	हाल ETMACTRn(1):
		*val = eपंचांग_पढ़ो(ETMACTR1);
		वापस 0;
	हाल ETMACTRn(2):
		*val = eपंचांग_पढ़ो(ETMACTR2);
		वापस 0;
	हाल ETMACTRn(3):
		*val = eपंचांग_पढ़ो(ETMACTR3);
		वापस 0;
	हाल ETMACTRn(4):
		*val = eपंचांग_पढ़ो(ETMACTR4);
		वापस 0;
	हाल ETMACTRn(5):
		*val = eपंचांग_पढ़ो(ETMACTR5);
		वापस 0;
	हाल ETMACTRn(6):
		*val = eपंचांग_पढ़ो(ETMACTR6);
		वापस 0;
	हाल ETMACTRn(7):
		*val = eपंचांग_पढ़ो(ETMACTR7);
		वापस 0;
	हाल ETMACTRn(8):
		*val = eपंचांग_पढ़ो(ETMACTR8);
		वापस 0;
	हाल ETMACTRn(9):
		*val = eपंचांग_पढ़ो(ETMACTR9);
		वापस 0;
	हाल ETMACTRn(10):
		*val = eपंचांग_पढ़ो(ETMACTR10);
		वापस 0;
	हाल ETMACTRn(11):
		*val = eपंचांग_पढ़ो(ETMACTR11);
		वापस 0;
	हाल ETMACTRn(12):
		*val = eपंचांग_पढ़ो(ETMACTR12);
		वापस 0;
	हाल ETMACTRn(13):
		*val = eपंचांग_पढ़ो(ETMACTR13);
		वापस 0;
	हाल ETMACTRn(14):
		*val = eपंचांग_पढ़ो(ETMACTR14);
		वापस 0;
	हाल ETMACTRn(15):
		*val = eपंचांग_पढ़ो(ETMACTR15);
		वापस 0;
	हाल ETMCNTRLDVRn(0):
		*val = eपंचांग_पढ़ो(ETMCNTRLDVR0);
		वापस 0;
	हाल ETMCNTRLDVRn(1):
		*val = eपंचांग_पढ़ो(ETMCNTRLDVR1);
		वापस 0;
	हाल ETMCNTRLDVRn(2):
		*val = eपंचांग_पढ़ो(ETMCNTRLDVR2);
		वापस 0;
	हाल ETMCNTRLDVRn(3):
		*val = eपंचांग_पढ़ो(ETMCNTRLDVR3);
		वापस 0;
	हाल ETMCNTENRn(0):
		*val = eपंचांग_पढ़ो(ETMCNTENR0);
		वापस 0;
	हाल ETMCNTENRn(1):
		*val = eपंचांग_पढ़ो(ETMCNTENR1);
		वापस 0;
	हाल ETMCNTENRn(2):
		*val = eपंचांग_पढ़ो(ETMCNTENR2);
		वापस 0;
	हाल ETMCNTENRn(3):
		*val = eपंचांग_पढ़ो(ETMCNTENR3);
		वापस 0;
	हाल ETMCNTRLDEVRn(0):
		*val = eपंचांग_पढ़ो(ETMCNTRLDEVR0);
		वापस 0;
	हाल ETMCNTRLDEVRn(1):
		*val = eपंचांग_पढ़ो(ETMCNTRLDEVR1);
		वापस 0;
	हाल ETMCNTRLDEVRn(2):
		*val = eपंचांग_पढ़ो(ETMCNTRLDEVR2);
		वापस 0;
	हाल ETMCNTRLDEVRn(3):
		*val = eपंचांग_पढ़ो(ETMCNTRLDEVR3);
		वापस 0;
	हाल ETMCNTVRn(0):
		*val = eपंचांग_पढ़ो(ETMCNTVR0);
		वापस 0;
	हाल ETMCNTVRn(1):
		*val = eपंचांग_पढ़ो(ETMCNTVR1);
		वापस 0;
	हाल ETMCNTVRn(2):
		*val = eपंचांग_पढ़ो(ETMCNTVR2);
		वापस 0;
	हाल ETMCNTVRn(3):
		*val = eपंचांग_पढ़ो(ETMCNTVR3);
		वापस 0;
	हाल ETMSQ12EVR:
		*val = eपंचांग_पढ़ो(ETMSQ12EVR);
		वापस 0;
	हाल ETMSQ21EVR:
		*val = eपंचांग_पढ़ो(ETMSQ21EVR);
		वापस 0;
	हाल ETMSQ23EVR:
		*val = eपंचांग_पढ़ो(ETMSQ23EVR);
		वापस 0;
	हाल ETMSQ31EVR:
		*val = eपंचांग_पढ़ो(ETMSQ31EVR);
		वापस 0;
	हाल ETMSQ32EVR:
		*val = eपंचांग_पढ़ो(ETMSQ32EVR);
		वापस 0;
	हाल ETMSQ13EVR:
		*val = eपंचांग_पढ़ो(ETMSQ13EVR);
		वापस 0;
	हाल ETMSQR:
		*val = eपंचांग_पढ़ो(ETMSQR);
		वापस 0;
	हाल ETMEXTOUTEVRn(0):
		*val = eपंचांग_पढ़ो(ETMEXTOUTEVR0);
		वापस 0;
	हाल ETMEXTOUTEVRn(1):
		*val = eपंचांग_पढ़ो(ETMEXTOUTEVR1);
		वापस 0;
	हाल ETMEXTOUTEVRn(2):
		*val = eपंचांग_पढ़ो(ETMEXTOUTEVR2);
		वापस 0;
	हाल ETMEXTOUTEVRn(3):
		*val = eपंचांग_पढ़ो(ETMEXTOUTEVR3);
		वापस 0;
	हाल ETMCIDCVRn(0):
		*val = eपंचांग_पढ़ो(ETMCIDCVR0);
		वापस 0;
	हाल ETMCIDCVRn(1):
		*val = eपंचांग_पढ़ो(ETMCIDCVR1);
		वापस 0;
	हाल ETMCIDCVRn(2):
		*val = eपंचांग_पढ़ो(ETMCIDCVR2);
		वापस 0;
	हाल ETMCIDCMR:
		*val = eपंचांग_पढ़ो(ETMCIDCMR);
		वापस 0;
	हाल ETMIMPSPEC0:
		*val = eपंचांग_पढ़ो(ETMIMPSPEC0);
		वापस 0;
	हाल ETMIMPSPEC1:
		*val = eपंचांग_पढ़ो(ETMIMPSPEC1);
		वापस 0;
	हाल ETMIMPSPEC2:
		*val = eपंचांग_पढ़ो(ETMIMPSPEC2);
		वापस 0;
	हाल ETMIMPSPEC3:
		*val = eपंचांग_पढ़ो(ETMIMPSPEC3);
		वापस 0;
	हाल ETMIMPSPEC4:
		*val = eपंचांग_पढ़ो(ETMIMPSPEC4);
		वापस 0;
	हाल ETMIMPSPEC5:
		*val = eपंचांग_पढ़ो(ETMIMPSPEC5);
		वापस 0;
	हाल ETMIMPSPEC6:
		*val = eपंचांग_पढ़ो(ETMIMPSPEC6);
		वापस 0;
	हाल ETMIMPSPEC7:
		*val = eपंचांग_पढ़ो(ETMIMPSPEC7);
		वापस 0;
	हाल ETMSYNCFR:
		*val = eपंचांग_पढ़ो(ETMSYNCFR);
		वापस 0;
	हाल ETMIDR:
		*val = eपंचांग_पढ़ो(ETMIDR);
		वापस 0;
	हाल ETMCCER:
		*val = eपंचांग_पढ़ो(ETMCCER);
		वापस 0;
	हाल ETMEXTINSELR:
		*val = eपंचांग_पढ़ो(ETMEXTINSELR);
		वापस 0;
	हाल ETMTESSEICR:
		*val = eपंचांग_पढ़ो(ETMTESSEICR);
		वापस 0;
	हाल ETMEIBCR:
		*val = eपंचांग_पढ़ो(ETMEIBCR);
		वापस 0;
	हाल ETMTSEVR:
		*val = eपंचांग_पढ़ो(ETMTSEVR);
		वापस 0;
	हाल ETMAUXCR:
		*val = eपंचांग_पढ़ो(ETMAUXCR);
		वापस 0;
	हाल ETMTRACEIDR:
		*val = eपंचांग_पढ़ो(ETMTRACEIDR);
		वापस 0;
	हाल ETMVMIDCVR:
		*val = eपंचांग_पढ़ो(ETMVMIDCVR);
		वापस 0;
	हाल ETMOSLSR:
		*val = eपंचांग_पढ़ो(ETMOSLSR);
		वापस 0;
	हाल ETMOSSRR:
		*val = eपंचांग_पढ़ो(ETMOSSRR);
		वापस 0;
	हाल ETMPDCR:
		*val = eपंचांग_पढ़ो(ETMPDCR);
		वापस 0;
	हाल ETMPDSR:
		*val = eपंचांग_पढ़ो(ETMPDSR);
		वापस 0;
	शेष:
		*val = 0;
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक eपंचांग_ग_लिखोl_cp14(u32 reg, u32 val)
अणु
	चयन (reg) अणु
	हाल ETMCR:
		eपंचांग_ग_लिखो(val, ETMCR);
		अवरोध;
	हाल ETMTRIGGER:
		eपंचांग_ग_लिखो(val, ETMTRIGGER);
		अवरोध;
	हाल ETMSR:
		eपंचांग_ग_लिखो(val, ETMSR);
		अवरोध;
	हाल ETMTSSCR:
		eपंचांग_ग_लिखो(val, ETMTSSCR);
		अवरोध;
	हाल ETMTEEVR:
		eपंचांग_ग_लिखो(val, ETMTEEVR);
		अवरोध;
	हाल ETMTECR1:
		eपंचांग_ग_लिखो(val, ETMTECR1);
		अवरोध;
	हाल ETMFFLR:
		eपंचांग_ग_लिखो(val, ETMFFLR);
		अवरोध;
	हाल ETMACVRn(0):
		eपंचांग_ग_लिखो(val, ETMACVR0);
		अवरोध;
	हाल ETMACVRn(1):
		eपंचांग_ग_लिखो(val, ETMACVR1);
		अवरोध;
	हाल ETMACVRn(2):
		eपंचांग_ग_लिखो(val, ETMACVR2);
		अवरोध;
	हाल ETMACVRn(3):
		eपंचांग_ग_लिखो(val, ETMACVR3);
		अवरोध;
	हाल ETMACVRn(4):
		eपंचांग_ग_लिखो(val, ETMACVR4);
		अवरोध;
	हाल ETMACVRn(5):
		eपंचांग_ग_लिखो(val, ETMACVR5);
		अवरोध;
	हाल ETMACVRn(6):
		eपंचांग_ग_लिखो(val, ETMACVR6);
		अवरोध;
	हाल ETMACVRn(7):
		eपंचांग_ग_लिखो(val, ETMACVR7);
		अवरोध;
	हाल ETMACVRn(8):
		eपंचांग_ग_लिखो(val, ETMACVR8);
		अवरोध;
	हाल ETMACVRn(9):
		eपंचांग_ग_लिखो(val, ETMACVR9);
		अवरोध;
	हाल ETMACVRn(10):
		eपंचांग_ग_लिखो(val, ETMACVR10);
		अवरोध;
	हाल ETMACVRn(11):
		eपंचांग_ग_लिखो(val, ETMACVR11);
		अवरोध;
	हाल ETMACVRn(12):
		eपंचांग_ग_लिखो(val, ETMACVR12);
		अवरोध;
	हाल ETMACVRn(13):
		eपंचांग_ग_लिखो(val, ETMACVR13);
		अवरोध;
	हाल ETMACVRn(14):
		eपंचांग_ग_लिखो(val, ETMACVR14);
		अवरोध;
	हाल ETMACVRn(15):
		eपंचांग_ग_लिखो(val, ETMACVR15);
		अवरोध;
	हाल ETMACTRn(0):
		eपंचांग_ग_लिखो(val, ETMACTR0);
		अवरोध;
	हाल ETMACTRn(1):
		eपंचांग_ग_लिखो(val, ETMACTR1);
		अवरोध;
	हाल ETMACTRn(2):
		eपंचांग_ग_लिखो(val, ETMACTR2);
		अवरोध;
	हाल ETMACTRn(3):
		eपंचांग_ग_लिखो(val, ETMACTR3);
		अवरोध;
	हाल ETMACTRn(4):
		eपंचांग_ग_लिखो(val, ETMACTR4);
		अवरोध;
	हाल ETMACTRn(5):
		eपंचांग_ग_लिखो(val, ETMACTR5);
		अवरोध;
	हाल ETMACTRn(6):
		eपंचांग_ग_लिखो(val, ETMACTR6);
		अवरोध;
	हाल ETMACTRn(7):
		eपंचांग_ग_लिखो(val, ETMACTR7);
		अवरोध;
	हाल ETMACTRn(8):
		eपंचांग_ग_लिखो(val, ETMACTR8);
		अवरोध;
	हाल ETMACTRn(9):
		eपंचांग_ग_लिखो(val, ETMACTR9);
		अवरोध;
	हाल ETMACTRn(10):
		eपंचांग_ग_लिखो(val, ETMACTR10);
		अवरोध;
	हाल ETMACTRn(11):
		eपंचांग_ग_लिखो(val, ETMACTR11);
		अवरोध;
	हाल ETMACTRn(12):
		eपंचांग_ग_लिखो(val, ETMACTR12);
		अवरोध;
	हाल ETMACTRn(13):
		eपंचांग_ग_लिखो(val, ETMACTR13);
		अवरोध;
	हाल ETMACTRn(14):
		eपंचांग_ग_लिखो(val, ETMACTR14);
		अवरोध;
	हाल ETMACTRn(15):
		eपंचांग_ग_लिखो(val, ETMACTR15);
		अवरोध;
	हाल ETMCNTRLDVRn(0):
		eपंचांग_ग_लिखो(val, ETMCNTRLDVR0);
		अवरोध;
	हाल ETMCNTRLDVRn(1):
		eपंचांग_ग_लिखो(val, ETMCNTRLDVR1);
		अवरोध;
	हाल ETMCNTRLDVRn(2):
		eपंचांग_ग_लिखो(val, ETMCNTRLDVR2);
		अवरोध;
	हाल ETMCNTRLDVRn(3):
		eपंचांग_ग_लिखो(val, ETMCNTRLDVR3);
		अवरोध;
	हाल ETMCNTENRn(0):
		eपंचांग_ग_लिखो(val, ETMCNTENR0);
		अवरोध;
	हाल ETMCNTENRn(1):
		eपंचांग_ग_लिखो(val, ETMCNTENR1);
		अवरोध;
	हाल ETMCNTENRn(2):
		eपंचांग_ग_लिखो(val, ETMCNTENR2);
		अवरोध;
	हाल ETMCNTENRn(3):
		eपंचांग_ग_लिखो(val, ETMCNTENR3);
		अवरोध;
	हाल ETMCNTRLDEVRn(0):
		eपंचांग_ग_लिखो(val, ETMCNTRLDEVR0);
		अवरोध;
	हाल ETMCNTRLDEVRn(1):
		eपंचांग_ग_लिखो(val, ETMCNTRLDEVR1);
		अवरोध;
	हाल ETMCNTRLDEVRn(2):
		eपंचांग_ग_लिखो(val, ETMCNTRLDEVR2);
		अवरोध;
	हाल ETMCNTRLDEVRn(3):
		eपंचांग_ग_लिखो(val, ETMCNTRLDEVR3);
		अवरोध;
	हाल ETMCNTVRn(0):
		eपंचांग_ग_लिखो(val, ETMCNTVR0);
		अवरोध;
	हाल ETMCNTVRn(1):
		eपंचांग_ग_लिखो(val, ETMCNTVR1);
		अवरोध;
	हाल ETMCNTVRn(2):
		eपंचांग_ग_लिखो(val, ETMCNTVR2);
		अवरोध;
	हाल ETMCNTVRn(3):
		eपंचांग_ग_लिखो(val, ETMCNTVR3);
		अवरोध;
	हाल ETMSQ12EVR:
		eपंचांग_ग_लिखो(val, ETMSQ12EVR);
		अवरोध;
	हाल ETMSQ21EVR:
		eपंचांग_ग_लिखो(val, ETMSQ21EVR);
		अवरोध;
	हाल ETMSQ23EVR:
		eपंचांग_ग_लिखो(val, ETMSQ23EVR);
		अवरोध;
	हाल ETMSQ31EVR:
		eपंचांग_ग_लिखो(val, ETMSQ31EVR);
		अवरोध;
	हाल ETMSQ32EVR:
		eपंचांग_ग_लिखो(val, ETMSQ32EVR);
		अवरोध;
	हाल ETMSQ13EVR:
		eपंचांग_ग_लिखो(val, ETMSQ13EVR);
		अवरोध;
	हाल ETMSQR:
		eपंचांग_ग_लिखो(val, ETMSQR);
		अवरोध;
	हाल ETMEXTOUTEVRn(0):
		eपंचांग_ग_लिखो(val, ETMEXTOUTEVR0);
		अवरोध;
	हाल ETMEXTOUTEVRn(1):
		eपंचांग_ग_लिखो(val, ETMEXTOUTEVR1);
		अवरोध;
	हाल ETMEXTOUTEVRn(2):
		eपंचांग_ग_लिखो(val, ETMEXTOUTEVR2);
		अवरोध;
	हाल ETMEXTOUTEVRn(3):
		eपंचांग_ग_लिखो(val, ETMEXTOUTEVR3);
		अवरोध;
	हाल ETMCIDCVRn(0):
		eपंचांग_ग_लिखो(val, ETMCIDCVR0);
		अवरोध;
	हाल ETMCIDCVRn(1):
		eपंचांग_ग_लिखो(val, ETMCIDCVR1);
		अवरोध;
	हाल ETMCIDCVRn(2):
		eपंचांग_ग_लिखो(val, ETMCIDCVR2);
		अवरोध;
	हाल ETMCIDCMR:
		eपंचांग_ग_लिखो(val, ETMCIDCMR);
		अवरोध;
	हाल ETMIMPSPEC0:
		eपंचांग_ग_लिखो(val, ETMIMPSPEC0);
		अवरोध;
	हाल ETMIMPSPEC1:
		eपंचांग_ग_लिखो(val, ETMIMPSPEC1);
		अवरोध;
	हाल ETMIMPSPEC2:
		eपंचांग_ग_लिखो(val, ETMIMPSPEC2);
		अवरोध;
	हाल ETMIMPSPEC3:
		eपंचांग_ग_लिखो(val, ETMIMPSPEC3);
		अवरोध;
	हाल ETMIMPSPEC4:
		eपंचांग_ग_लिखो(val, ETMIMPSPEC4);
		अवरोध;
	हाल ETMIMPSPEC5:
		eपंचांग_ग_लिखो(val, ETMIMPSPEC5);
		अवरोध;
	हाल ETMIMPSPEC6:
		eपंचांग_ग_लिखो(val, ETMIMPSPEC6);
		अवरोध;
	हाल ETMIMPSPEC7:
		eपंचांग_ग_लिखो(val, ETMIMPSPEC7);
		अवरोध;
	हाल ETMSYNCFR:
		eपंचांग_ग_लिखो(val, ETMSYNCFR);
		अवरोध;
	हाल ETMEXTINSELR:
		eपंचांग_ग_लिखो(val, ETMEXTINSELR);
		अवरोध;
	हाल ETMTESSEICR:
		eपंचांग_ग_लिखो(val, ETMTESSEICR);
		अवरोध;
	हाल ETMEIBCR:
		eपंचांग_ग_लिखो(val, ETMEIBCR);
		अवरोध;
	हाल ETMTSEVR:
		eपंचांग_ग_लिखो(val, ETMTSEVR);
		अवरोध;
	हाल ETMAUXCR:
		eपंचांग_ग_लिखो(val, ETMAUXCR);
		अवरोध;
	हाल ETMTRACEIDR:
		eपंचांग_ग_लिखो(val, ETMTRACEIDR);
		अवरोध;
	हाल ETMVMIDCVR:
		eपंचांग_ग_लिखो(val, ETMVMIDCVR);
		अवरोध;
	हाल ETMOSLAR:
		eपंचांग_ग_लिखो(val, ETMOSLAR);
		अवरोध;
	हाल ETMOSSRR:
		eपंचांग_ग_लिखो(val, ETMOSSRR);
		अवरोध;
	हाल ETMPDCR:
		eपंचांग_ग_लिखो(val, ETMPDCR);
		अवरोध;
	हाल ETMPDSR:
		eपंचांग_ग_लिखो(val, ETMPDSR);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
