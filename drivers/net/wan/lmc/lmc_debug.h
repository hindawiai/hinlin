<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LMC_DEBUG_H_
#घोषणा _LMC_DEBUG_H_

#अगर_घोषित DEBUG
#अगर_घोषित LMC_PACKET_LOG
#घोषणा LMC_CONSOLE_LOG(x,y,z) lmcConsoleLog((x), (y), (z))
#अन्यथा
#घोषणा LMC_CONSOLE_LOG(x,y,z)
#पूर्ण_अगर
#अन्यथा
#घोषणा LMC_CONSOLE_LOG(x,y,z)
#पूर्ण_अगर



/* Debug --- Event log definitions --- */
/* EVENTLOGSIZE*EVENTLOGARGS needs to be a घातer of 2 */
#घोषणा LMC_EVENTLOGSIZE 1024	/* number of events in eventlog */
#घोषणा LMC_EVENTLOGARGS 4		/* number of args क्रम each event */

/* event indicators */
#घोषणा LMC_EVENT_XMT           1
#घोषणा LMC_EVENT_XMTEND        2
#घोषणा LMC_EVENT_XMTINT        3
#घोषणा LMC_EVENT_RCVINT        4
#घोषणा LMC_EVENT_RCVEND        5
#घोषणा LMC_EVENT_INT           6
#घोषणा LMC_EVENT_XMTINTTMO     7
#घोषणा LMC_EVENT_XMTPRCTMO     8
#घोषणा LMC_EVENT_INTEND        9
#घोषणा LMC_EVENT_RESET1       10
#घोषणा LMC_EVENT_RESET2       11
#घोषणा LMC_EVENT_FORCEDRESET  12
#घोषणा LMC_EVENT_WATCHDOG     13
#घोषणा LMC_EVENT_BADPKTSURGE  14
#घोषणा LMC_EVENT_TBUSY0       15
#घोषणा LMC_EVENT_TBUSY1       16


#अगर_घोषित DEBUG
बाह्य u32 lmcEventLogIndex;
बाह्य u32 lmcEventLogBuf[LMC_EVENTLOGSIZE * LMC_EVENTLOGARGS];
#घोषणा LMC_EVENT_LOG(x, y, z) lmcEventLog((x), (y), (z))
#अन्यथा
#घोषणा LMC_EVENT_LOG(x,y,z)
#पूर्ण_अगर /* end अगरdef _DBG_EVENTLOG */

व्योम lmcConsoleLog(अक्षर *type, अचिन्हित अक्षर *ucData, पूर्णांक iLen);
व्योम lmcEventLog(u32 EventNum, u32 arg2, u32 arg3);

#पूर्ण_अगर
