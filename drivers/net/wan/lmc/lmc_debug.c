<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "lmc_debug.h"

/*
 * Prपूर्णांकs out len, max to 80 octets using prपूर्णांकk, 20 per line
 */
#अगर_घोषित DEBUG
#अगर_घोषित LMC_PACKET_LOG
व्योम lmcConsoleLog(अक्षर *type, अचिन्हित अक्षर *ucData, पूर्णांक iLen)
अणु
  पूर्णांक iNewLine = 1;
  अक्षर str[80], *pstr;
  
  प्र_लिखो(str, KERN_DEBUG "lmc: %s: ", type);
  pstr = str+म_माप(str);
  
  अगर(iLen > 240)अणु
      prपूर्णांकk(KERN_DEBUG "lmc: Printing 240 chars... out of: %d\n", iLen);
    iLen = 240;
  पूर्ण
  अन्यथाअणु
      prपूर्णांकk(KERN_DEBUG "lmc: Printing %d chars\n", iLen);
  पूर्ण

  जबतक(iLen > 0) 
    अणु
      प्र_लिखो(pstr, "%02x ", *ucData);
      pstr+=3;
      ucData++;
      अगर( !(iNewLine % 20))
	अणु
	  प्र_लिखो(pstr, "\n");
	  prपूर्णांकk(str);
	  प्र_लिखो(str, KERN_DEBUG "lmc: %s: ", type);
	  pstr=str+म_माप(str);
	पूर्ण
      iNewLine++;
      iLen--;
    पूर्ण
  प्र_लिखो(pstr, "\n");
  prपूर्णांकk(str);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित DEBUG
u32 lmcEventLogIndex;
u32 lmcEventLogBuf[LMC_EVENTLOGSIZE * LMC_EVENTLOGARGS];

व्योम lmcEventLog(u32 EventNum, u32 arg2, u32 arg3)
अणु
  lmcEventLogBuf[lmcEventLogIndex++] = EventNum;
  lmcEventLogBuf[lmcEventLogIndex++] = arg2;
  lmcEventLogBuf[lmcEventLogIndex++] = arg3;
  lmcEventLogBuf[lmcEventLogIndex++] = jअगरfies;

  lmcEventLogIndex &= (LMC_EVENTLOGSIZE * LMC_EVENTLOGARGS) - 1;
पूर्ण
#पूर्ण_अगर  /*  DEBUG  */

/* --------------------------- end अगर_lmc_linux.c ------------------------ */
