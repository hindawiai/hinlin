<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा A_SG_CONTROL 0x0

#घोषणा S_CONGMODE    29
#घोषणा V_CONGMODE(x) ((x) << S_CONGMODE)
#घोषणा F_CONGMODE    V_CONGMODE(1U)

#घोषणा S_TNLFLMODE    28
#घोषणा V_TNLFLMODE(x) ((x) << S_TNLFLMODE)
#घोषणा F_TNLFLMODE    V_TNLFLMODE(1U)

#घोषणा S_FATLPERREN    27
#घोषणा V_FATLPERREN(x) ((x) << S_FATLPERREN)
#घोषणा F_FATLPERREN    V_FATLPERREN(1U)

#घोषणा S_DROPPKT    20
#घोषणा V_DROPPKT(x) ((x) << S_DROPPKT)
#घोषणा F_DROPPKT    V_DROPPKT(1U)

#घोषणा S_EGRGENCTRL    19
#घोषणा V_EGRGENCTRL(x) ((x) << S_EGRGENCTRL)
#घोषणा F_EGRGENCTRL    V_EGRGENCTRL(1U)

#घोषणा S_USERSPACESIZE    14
#घोषणा M_USERSPACESIZE    0x1f
#घोषणा V_USERSPACESIZE(x) ((x) << S_USERSPACESIZE)

#घोषणा S_HOSTPAGESIZE    11
#घोषणा M_HOSTPAGESIZE    0x7
#घोषणा V_HOSTPAGESIZE(x) ((x) << S_HOSTPAGESIZE)

#घोषणा S_FLMODE    9
#घोषणा V_FLMODE(x) ((x) << S_FLMODE)
#घोषणा F_FLMODE    V_FLMODE(1U)

#घोषणा S_PKTSHIFT    6
#घोषणा M_PKTSHIFT    0x7
#घोषणा V_PKTSHIFT(x) ((x) << S_PKTSHIFT)

#घोषणा S_ONEINTMULTQ    5
#घोषणा V_ONEINTMULTQ(x) ((x) << S_ONEINTMULTQ)
#घोषणा F_ONEINTMULTQ    V_ONEINTMULTQ(1U)

#घोषणा S_BIGENDIANINGRESS    2
#घोषणा V_BIGENDIANINGRESS(x) ((x) << S_BIGENDIANINGRESS)
#घोषणा F_BIGENDIANINGRESS    V_BIGENDIANINGRESS(1U)

#घोषणा S_ISCSICOALESCING    1
#घोषणा V_ISCSICOALESCING(x) ((x) << S_ISCSICOALESCING)
#घोषणा F_ISCSICOALESCING    V_ISCSICOALESCING(1U)

#घोषणा S_GLOBALENABLE    0
#घोषणा V_GLOBALENABLE(x) ((x) << S_GLOBALENABLE)
#घोषणा F_GLOBALENABLE    V_GLOBALENABLE(1U)

#घोषणा S_AVOIDCQOVFL    24
#घोषणा V_AVOIDCQOVFL(x) ((x) << S_AVOIDCQOVFL)
#घोषणा F_AVOIDCQOVFL    V_AVOIDCQOVFL(1U)

#घोषणा S_OPTONEINTMULTQ    23
#घोषणा V_OPTONEINTMULTQ(x) ((x) << S_OPTONEINTMULTQ)
#घोषणा F_OPTONEINTMULTQ    V_OPTONEINTMULTQ(1U)

#घोषणा S_CQCRDTCTRL    22
#घोषणा V_CQCRDTCTRL(x) ((x) << S_CQCRDTCTRL)
#घोषणा F_CQCRDTCTRL    V_CQCRDTCTRL(1U)

#घोषणा A_SG_KDOORBELL 0x4

#घोषणा S_SELEGRCNTX    31
#घोषणा V_SELEGRCNTX(x) ((x) << S_SELEGRCNTX)
#घोषणा F_SELEGRCNTX    V_SELEGRCNTX(1U)

#घोषणा S_EGRCNTX    0
#घोषणा M_EGRCNTX    0xffff
#घोषणा V_EGRCNTX(x) ((x) << S_EGRCNTX)

#घोषणा A_SG_GTS 0x8

#घोषणा S_RSPQ    29
#घोषणा M_RSPQ    0x7
#घोषणा V_RSPQ(x) ((x) << S_RSPQ)
#घोषणा G_RSPQ(x) (((x) >> S_RSPQ) & M_RSPQ)

#घोषणा S_NEWTIMER    16
#घोषणा M_NEWTIMER    0x1fff
#घोषणा V_NEWTIMER(x) ((x) << S_NEWTIMER)

#घोषणा S_NEWINDEX    0
#घोषणा M_NEWINDEX    0xffff
#घोषणा V_NEWINDEX(x) ((x) << S_NEWINDEX)

#घोषणा A_SG_CONTEXT_CMD 0xc

#घोषणा S_CONTEXT_CMD_OPCODE    28
#घोषणा M_CONTEXT_CMD_OPCODE    0xf
#घोषणा V_CONTEXT_CMD_OPCODE(x) ((x) << S_CONTEXT_CMD_OPCODE)

#घोषणा S_CONTEXT_CMD_BUSY    27
#घोषणा V_CONTEXT_CMD_BUSY(x) ((x) << S_CONTEXT_CMD_BUSY)
#घोषणा F_CONTEXT_CMD_BUSY    V_CONTEXT_CMD_BUSY(1U)

#घोषणा S_CQ_CREDIT    20

#घोषणा M_CQ_CREDIT    0x7f

#घोषणा V_CQ_CREDIT(x) ((x) << S_CQ_CREDIT)

#घोषणा G_CQ_CREDIT(x) (((x) >> S_CQ_CREDIT) & M_CQ_CREDIT)

#घोषणा S_CQ    19

#घोषणा V_CQ(x) ((x) << S_CQ)
#घोषणा F_CQ    V_CQ(1U)

#घोषणा S_RESPONSEQ    18
#घोषणा V_RESPONSEQ(x) ((x) << S_RESPONSEQ)
#घोषणा F_RESPONSEQ    V_RESPONSEQ(1U)

#घोषणा S_EGRESS    17
#घोषणा V_EGRESS(x) ((x) << S_EGRESS)
#घोषणा F_EGRESS    V_EGRESS(1U)

#घोषणा S_FREELIST    16
#घोषणा V_FREELIST(x) ((x) << S_FREELIST)
#घोषणा F_FREELIST    V_FREELIST(1U)

#घोषणा S_CONTEXT    0
#घोषणा M_CONTEXT    0xffff
#घोषणा V_CONTEXT(x) ((x) << S_CONTEXT)

#घोषणा G_CONTEXT(x) (((x) >> S_CONTEXT) & M_CONTEXT)

#घोषणा A_SG_CONTEXT_DATA0 0x10

#घोषणा A_SG_CONTEXT_DATA1 0x14

#घोषणा A_SG_CONTEXT_DATA2 0x18

#घोषणा A_SG_CONTEXT_DATA3 0x1c

#घोषणा A_SG_CONTEXT_MASK0 0x20

#घोषणा A_SG_CONTEXT_MASK1 0x24

#घोषणा A_SG_CONTEXT_MASK2 0x28

#घोषणा A_SG_CONTEXT_MASK3 0x2c

#घोषणा A_SG_RSPQ_CREDIT_RETURN 0x30

#घोषणा S_CREDITS    0
#घोषणा M_CREDITS    0xffff
#घोषणा V_CREDITS(x) ((x) << S_CREDITS)

#घोषणा A_SG_DATA_INTR 0x34

#घोषणा S_ERRINTR    31
#घोषणा V_ERRINTR(x) ((x) << S_ERRINTR)
#घोषणा F_ERRINTR    V_ERRINTR(1U)

#घोषणा A_SG_HI_DRB_HI_THRSH 0x38

#घोषणा A_SG_HI_DRB_LO_THRSH 0x3c

#घोषणा A_SG_LO_DRB_HI_THRSH 0x40

#घोषणा A_SG_LO_DRB_LO_THRSH 0x44

#घोषणा A_SG_RSPQ_FL_STATUS 0x4c

#घोषणा S_RSPQ0DISABLED    8

#घोषणा S_FL0EMPTY    16
#घोषणा V_FL0EMPTY(x) ((x) << S_FL0EMPTY)
#घोषणा F_FL0EMPTY    V_FL0EMPTY(1U)

#घोषणा A_SG_EGR_RCQ_DRB_THRSH 0x54

#घोषणा S_HIRCQDRBTHRSH    16
#घोषणा M_HIRCQDRBTHRSH    0x7ff
#घोषणा V_HIRCQDRBTHRSH(x) ((x) << S_HIRCQDRBTHRSH)

#घोषणा S_LORCQDRBTHRSH    0
#घोषणा M_LORCQDRBTHRSH    0x7ff
#घोषणा V_LORCQDRBTHRSH(x) ((x) << S_LORCQDRBTHRSH)

#घोषणा A_SG_EGR_CNTX_BADDR 0x58

#घोषणा A_SG_INT_CAUSE 0x5c

#घोषणा S_HIRCQPARITYERROR    31
#घोषणा V_HIRCQPARITYERROR(x) ((x) << S_HIRCQPARITYERROR)
#घोषणा F_HIRCQPARITYERROR    V_HIRCQPARITYERROR(1U)

#घोषणा S_LORCQPARITYERROR    30
#घोषणा V_LORCQPARITYERROR(x) ((x) << S_LORCQPARITYERROR)
#घोषणा F_LORCQPARITYERROR    V_LORCQPARITYERROR(1U)

#घोषणा S_HIDRBPARITYERROR    29
#घोषणा V_HIDRBPARITYERROR(x) ((x) << S_HIDRBPARITYERROR)
#घोषणा F_HIDRBPARITYERROR    V_HIDRBPARITYERROR(1U)

#घोषणा S_LODRBPARITYERROR    28
#घोषणा V_LODRBPARITYERROR(x) ((x) << S_LODRBPARITYERROR)
#घोषणा F_LODRBPARITYERROR    V_LODRBPARITYERROR(1U)

#घोषणा S_FLPARITYERROR    22
#घोषणा M_FLPARITYERROR    0x3f
#घोषणा V_FLPARITYERROR(x) ((x) << S_FLPARITYERROR)
#घोषणा G_FLPARITYERROR(x) (((x) >> S_FLPARITYERROR) & M_FLPARITYERROR)

#घोषणा S_ITPARITYERROR    20
#घोषणा M_ITPARITYERROR    0x3
#घोषणा V_ITPARITYERROR(x) ((x) << S_ITPARITYERROR)
#घोषणा G_ITPARITYERROR(x) (((x) >> S_ITPARITYERROR) & M_ITPARITYERROR)

#घोषणा S_IRPARITYERROR    19
#घोषणा V_IRPARITYERROR(x) ((x) << S_IRPARITYERROR)
#घोषणा F_IRPARITYERROR    V_IRPARITYERROR(1U)

#घोषणा S_RCPARITYERROR    18
#घोषणा V_RCPARITYERROR(x) ((x) << S_RCPARITYERROR)
#घोषणा F_RCPARITYERROR    V_RCPARITYERROR(1U)

#घोषणा S_OCPARITYERROR    17
#घोषणा V_OCPARITYERROR(x) ((x) << S_OCPARITYERROR)
#घोषणा F_OCPARITYERROR    V_OCPARITYERROR(1U)

#घोषणा S_CPPARITYERROR    16
#घोषणा V_CPPARITYERROR(x) ((x) << S_CPPARITYERROR)
#घोषणा F_CPPARITYERROR    V_CPPARITYERROR(1U)

#घोषणा S_R_REQ_FRAMINGERROR    15
#घोषणा V_R_REQ_FRAMINGERROR(x) ((x) << S_R_REQ_FRAMINGERROR)
#घोषणा F_R_REQ_FRAMINGERROR    V_R_REQ_FRAMINGERROR(1U)

#घोषणा S_UC_REQ_FRAMINGERROR    14
#घोषणा V_UC_REQ_FRAMINGERROR(x) ((x) << S_UC_REQ_FRAMINGERROR)
#घोषणा F_UC_REQ_FRAMINGERROR    V_UC_REQ_FRAMINGERROR(1U)

#घोषणा S_HICTLDRBDROPERR    13
#घोषणा V_HICTLDRBDROPERR(x) ((x) << S_HICTLDRBDROPERR)
#घोषणा F_HICTLDRBDROPERR    V_HICTLDRBDROPERR(1U)

#घोषणा S_LOCTLDRBDROPERR    12
#घोषणा V_LOCTLDRBDROPERR(x) ((x) << S_LOCTLDRBDROPERR)
#घोषणा F_LOCTLDRBDROPERR    V_LOCTLDRBDROPERR(1U)

#घोषणा S_HIPIODRBDROPERR    11
#घोषणा V_HIPIODRBDROPERR(x) ((x) << S_HIPIODRBDROPERR)
#घोषणा F_HIPIODRBDROPERR    V_HIPIODRBDROPERR(1U)

#घोषणा S_LOPIODRBDROPERR    10
#घोषणा V_LOPIODRBDROPERR(x) ((x) << S_LOPIODRBDROPERR)
#घोषणा F_LOPIODRBDROPERR    V_LOPIODRBDROPERR(1U)

#घोषणा S_HIPRIORITYDBFULL    7
#घोषणा V_HIPRIORITYDBFULL(x) ((x) << S_HIPRIORITYDBFULL)
#घोषणा F_HIPRIORITYDBFULL    V_HIPRIORITYDBFULL(1U)

#घोषणा S_HIPRIORITYDBEMPTY   6
#घोषणा V_HIPRIORITYDBEMPTY(x) ((x) << S_HIPRIORITYDBEMPTY)
#घोषणा F_HIPRIORITYDBEMPTY    V_HIPRIORITYDBEMPTY(1U)

#घोषणा S_LOPRIORITYDBFULL    5
#घोषणा V_LOPRIORITYDBFULL(x) ((x) << S_LOPRIORITYDBFULL)
#घोषणा F_LOPRIORITYDBFULL    V_LOPRIORITYDBFULL(1U)

#घोषणा S_LOPRIORITYDBEMPTY   4
#घोषणा V_LOPRIORITYDBEMPTY(x) ((x) << S_LOPRIORITYDBEMPTY)
#घोषणा F_LOPRIORITYDBEMPTY    V_LOPRIORITYDBEMPTY(1U)

#घोषणा S_RSPQDISABLED    3
#घोषणा V_RSPQDISABLED(x) ((x) << S_RSPQDISABLED)
#घोषणा F_RSPQDISABLED    V_RSPQDISABLED(1U)

#घोषणा S_RSPQCREDITOVERFOW    2
#घोषणा V_RSPQCREDITOVERFOW(x) ((x) << S_RSPQCREDITOVERFOW)
#घोषणा F_RSPQCREDITOVERFOW    V_RSPQCREDITOVERFOW(1U)

#घोषणा S_FLEMPTY    1
#घोषणा V_FLEMPTY(x) ((x) << S_FLEMPTY)
#घोषणा F_FLEMPTY    V_FLEMPTY(1U)

#घोषणा A_SG_INT_ENABLE 0x60

#घोषणा A_SG_CMDQ_CREDIT_TH 0x64

#घोषणा S_TIMEOUT    8
#घोषणा M_TIMEOUT    0xffffff
#घोषणा V_TIMEOUT(x) ((x) << S_TIMEOUT)

#घोषणा S_THRESHOLD    0
#घोषणा M_THRESHOLD    0xff
#घोषणा V_THRESHOLD(x) ((x) << S_THRESHOLD)

#घोषणा A_SG_TIMER_TICK 0x68

#घोषणा A_SG_CQ_CONTEXT_BADDR 0x6c

#घोषणा A_SG_OCO_BASE 0x70

#घोषणा S_BASE1    16
#घोषणा M_BASE1    0xffff
#घोषणा V_BASE1(x) ((x) << S_BASE1)

#घोषणा A_SG_DRB_PRI_THRESH 0x74

#घोषणा A_PCIX_INT_ENABLE 0x80

#घोषणा S_MSIXPARERR    22
#घोषणा M_MSIXPARERR    0x7

#घोषणा V_MSIXPARERR(x) ((x) << S_MSIXPARERR)

#घोषणा S_CFPARERR    18
#घोषणा M_CFPARERR    0xf

#घोषणा V_CFPARERR(x) ((x) << S_CFPARERR)

#घोषणा S_RFPARERR    14
#घोषणा M_RFPARERR    0xf

#घोषणा V_RFPARERR(x) ((x) << S_RFPARERR)

#घोषणा S_WFPARERR    12
#घोषणा M_WFPARERR    0x3

#घोषणा V_WFPARERR(x) ((x) << S_WFPARERR)

#घोषणा S_PIOPARERR    11
#घोषणा V_PIOPARERR(x) ((x) << S_PIOPARERR)
#घोषणा F_PIOPARERR    V_PIOPARERR(1U)

#घोषणा S_DETUNCECCERR    10
#घोषणा V_DETUNCECCERR(x) ((x) << S_DETUNCECCERR)
#घोषणा F_DETUNCECCERR    V_DETUNCECCERR(1U)

#घोषणा S_DETCORECCERR    9
#घोषणा V_DETCORECCERR(x) ((x) << S_DETCORECCERR)
#घोषणा F_DETCORECCERR    V_DETCORECCERR(1U)

#घोषणा S_RCVSPLCMPERR    8
#घोषणा V_RCVSPLCMPERR(x) ((x) << S_RCVSPLCMPERR)
#घोषणा F_RCVSPLCMPERR    V_RCVSPLCMPERR(1U)

#घोषणा S_UNXSPLCMP    7
#घोषणा V_UNXSPLCMP(x) ((x) << S_UNXSPLCMP)
#घोषणा F_UNXSPLCMP    V_UNXSPLCMP(1U)

#घोषणा S_SPLCMPDIS    6
#घोषणा V_SPLCMPDIS(x) ((x) << S_SPLCMPDIS)
#घोषणा F_SPLCMPDIS    V_SPLCMPDIS(1U)

#घोषणा S_DETPARERR    5
#घोषणा V_DETPARERR(x) ((x) << S_DETPARERR)
#घोषणा F_DETPARERR    V_DETPARERR(1U)

#घोषणा S_SIGSYSERR    4
#घोषणा V_SIGSYSERR(x) ((x) << S_SIGSYSERR)
#घोषणा F_SIGSYSERR    V_SIGSYSERR(1U)

#घोषणा S_RCVMSTABT    3
#घोषणा V_RCVMSTABT(x) ((x) << S_RCVMSTABT)
#घोषणा F_RCVMSTABT    V_RCVMSTABT(1U)

#घोषणा S_RCVTARABT    2
#घोषणा V_RCVTARABT(x) ((x) << S_RCVTARABT)
#घोषणा F_RCVTARABT    V_RCVTARABT(1U)

#घोषणा S_SIGTARABT    1
#घोषणा V_SIGTARABT(x) ((x) << S_SIGTARABT)
#घोषणा F_SIGTARABT    V_SIGTARABT(1U)

#घोषणा S_MSTDETPARERR    0
#घोषणा V_MSTDETPARERR(x) ((x) << S_MSTDETPARERR)
#घोषणा F_MSTDETPARERR    V_MSTDETPARERR(1U)

#घोषणा A_PCIX_INT_CAUSE 0x84

#घोषणा A_PCIX_CFG 0x88

#घोषणा S_DMASTOPEN    19
#घोषणा V_DMASTOPEN(x) ((x) << S_DMASTOPEN)
#घोषणा F_DMASTOPEN    V_DMASTOPEN(1U)

#घोषणा S_CLIDECEN    18
#घोषणा V_CLIDECEN(x) ((x) << S_CLIDECEN)
#घोषणा F_CLIDECEN    V_CLIDECEN(1U)

#घोषणा A_PCIX_MODE 0x8c

#घोषणा S_PCLKRANGE    6
#घोषणा M_PCLKRANGE    0x3
#घोषणा V_PCLKRANGE(x) ((x) << S_PCLKRANGE)
#घोषणा G_PCLKRANGE(x) (((x) >> S_PCLKRANGE) & M_PCLKRANGE)

#घोषणा S_PCIXINITPAT    2
#घोषणा M_PCIXINITPAT    0xf
#घोषणा V_PCIXINITPAT(x) ((x) << S_PCIXINITPAT)
#घोषणा G_PCIXINITPAT(x) (((x) >> S_PCIXINITPAT) & M_PCIXINITPAT)

#घोषणा S_64BIT    0
#घोषणा V_64BIT(x) ((x) << S_64BIT)
#घोषणा F_64BIT    V_64BIT(1U)

#घोषणा A_PCIE_INT_ENABLE 0x80

#घोषणा S_BISTERR    15
#घोषणा M_BISTERR    0xff

#घोषणा V_BISTERR(x) ((x) << S_BISTERR)

#घोषणा S_TXPARERR    18
#घोषणा V_TXPARERR(x) ((x) << S_TXPARERR)
#घोषणा F_TXPARERR    V_TXPARERR(1U)

#घोषणा S_RXPARERR    17
#घोषणा V_RXPARERR(x) ((x) << S_RXPARERR)
#घोषणा F_RXPARERR    V_RXPARERR(1U)

#घोषणा S_RETRYLUTPARERR    16
#घोषणा V_RETRYLUTPARERR(x) ((x) << S_RETRYLUTPARERR)
#घोषणा F_RETRYLUTPARERR    V_RETRYLUTPARERR(1U)

#घोषणा S_RETRYBUFPARERR    15
#घोषणा V_RETRYBUFPARERR(x) ((x) << S_RETRYBUFPARERR)
#घोषणा F_RETRYBUFPARERR    V_RETRYBUFPARERR(1U)

#घोषणा S_PCIE_MSIXPARERR    12
#घोषणा M_PCIE_MSIXPARERR    0x7

#घोषणा V_PCIE_MSIXPARERR(x) ((x) << S_PCIE_MSIXPARERR)

#घोषणा S_PCIE_CFPARERR    11
#घोषणा V_PCIE_CFPARERR(x) ((x) << S_PCIE_CFPARERR)
#घोषणा F_PCIE_CFPARERR    V_PCIE_CFPARERR(1U)

#घोषणा S_PCIE_RFPARERR    10
#घोषणा V_PCIE_RFPARERR(x) ((x) << S_PCIE_RFPARERR)
#घोषणा F_PCIE_RFPARERR    V_PCIE_RFPARERR(1U)

#घोषणा S_PCIE_WFPARERR    9
#घोषणा V_PCIE_WFPARERR(x) ((x) << S_PCIE_WFPARERR)
#घोषणा F_PCIE_WFPARERR    V_PCIE_WFPARERR(1U)

#घोषणा S_PCIE_PIOPARERR    8
#घोषणा V_PCIE_PIOPARERR(x) ((x) << S_PCIE_PIOPARERR)
#घोषणा F_PCIE_PIOPARERR    V_PCIE_PIOPARERR(1U)

#घोषणा S_UNXSPLCPLERRC    7
#घोषणा V_UNXSPLCPLERRC(x) ((x) << S_UNXSPLCPLERRC)
#घोषणा F_UNXSPLCPLERRC    V_UNXSPLCPLERRC(1U)

#घोषणा S_UNXSPLCPLERRR    6
#घोषणा V_UNXSPLCPLERRR(x) ((x) << S_UNXSPLCPLERRR)
#घोषणा F_UNXSPLCPLERRR    V_UNXSPLCPLERRR(1U)

#घोषणा S_PEXERR    0
#घोषणा V_PEXERR(x) ((x) << S_PEXERR)
#घोषणा F_PEXERR    V_PEXERR(1U)

#घोषणा A_PCIE_INT_CAUSE 0x84

#घोषणा S_PCIE_DMASTOPEN    24
#घोषणा V_PCIE_DMASTOPEN(x) ((x) << S_PCIE_DMASTOPEN)
#घोषणा F_PCIE_DMASTOPEN    V_PCIE_DMASTOPEN(1U)

#घोषणा A_PCIE_CFG 0x88

#घोषणा S_ENABLELINKDWNDRST    21
#घोषणा V_ENABLELINKDWNDRST(x) ((x) << S_ENABLELINKDWNDRST)
#घोषणा F_ENABLELINKDWNDRST    V_ENABLELINKDWNDRST(1U)

#घोषणा S_ENABLELINKDOWNRST    20
#घोषणा V_ENABLELINKDOWNRST(x) ((x) << S_ENABLELINKDOWNRST)
#घोषणा F_ENABLELINKDOWNRST    V_ENABLELINKDOWNRST(1U)

#घोषणा S_PCIE_CLIDECEN    16
#घोषणा V_PCIE_CLIDECEN(x) ((x) << S_PCIE_CLIDECEN)
#घोषणा F_PCIE_CLIDECEN    V_PCIE_CLIDECEN(1U)

#घोषणा S_CRSTWRMMODE    0
#घोषणा V_CRSTWRMMODE(x) ((x) << S_CRSTWRMMODE)
#घोषणा F_CRSTWRMMODE    V_CRSTWRMMODE(1U)

#घोषणा A_PCIE_MODE 0x8c

#घोषणा S_NUMFSTTRNSEQRX    10
#घोषणा M_NUMFSTTRNSEQRX    0xff
#घोषणा V_NUMFSTTRNSEQRX(x) ((x) << S_NUMFSTTRNSEQRX)
#घोषणा G_NUMFSTTRNSEQRX(x) (((x) >> S_NUMFSTTRNSEQRX) & M_NUMFSTTRNSEQRX)

#घोषणा A_PCIE_PEX_CTRL0 0x98

#घोषणा S_NUMFSTTRNSEQ    22
#घोषणा M_NUMFSTTRNSEQ    0xff
#घोषणा V_NUMFSTTRNSEQ(x) ((x) << S_NUMFSTTRNSEQ)
#घोषणा G_NUMFSTTRNSEQ(x) (((x) >> S_NUMFSTTRNSEQ) & M_NUMFSTTRNSEQ)

#घोषणा S_REPLAYLMT    2
#घोषणा M_REPLAYLMT    0xfffff

#घोषणा V_REPLAYLMT(x) ((x) << S_REPLAYLMT)

#घोषणा A_PCIE_PEX_CTRL1 0x9c

#घोषणा S_T3A_ACKLAT    0
#घोषणा M_T3A_ACKLAT    0x7ff

#घोषणा V_T3A_ACKLAT(x) ((x) << S_T3A_ACKLAT)

#घोषणा S_ACKLAT    0
#घोषणा M_ACKLAT    0x1fff

#घोषणा V_ACKLAT(x) ((x) << S_ACKLAT)

#घोषणा A_PCIE_PEX_ERR 0xa4

#घोषणा A_T3DBG_GPIO_EN 0xd0

#घोषणा S_GPIO11_OEN    27
#घोषणा V_GPIO11_OEN(x) ((x) << S_GPIO11_OEN)
#घोषणा F_GPIO11_OEN    V_GPIO11_OEN(1U)

#घोषणा S_GPIO10_OEN    26
#घोषणा V_GPIO10_OEN(x) ((x) << S_GPIO10_OEN)
#घोषणा F_GPIO10_OEN    V_GPIO10_OEN(1U)

#घोषणा S_GPIO7_OEN    23
#घोषणा V_GPIO7_OEN(x) ((x) << S_GPIO7_OEN)
#घोषणा F_GPIO7_OEN    V_GPIO7_OEN(1U)

#घोषणा S_GPIO6_OEN    22
#घोषणा V_GPIO6_OEN(x) ((x) << S_GPIO6_OEN)
#घोषणा F_GPIO6_OEN    V_GPIO6_OEN(1U)

#घोषणा S_GPIO5_OEN    21
#घोषणा V_GPIO5_OEN(x) ((x) << S_GPIO5_OEN)
#घोषणा F_GPIO5_OEN    V_GPIO5_OEN(1U)

#घोषणा S_GPIO4_OEN    20
#घोषणा V_GPIO4_OEN(x) ((x) << S_GPIO4_OEN)
#घोषणा F_GPIO4_OEN    V_GPIO4_OEN(1U)

#घोषणा S_GPIO2_OEN    18
#घोषणा V_GPIO2_OEN(x) ((x) << S_GPIO2_OEN)
#घोषणा F_GPIO2_OEN    V_GPIO2_OEN(1U)

#घोषणा S_GPIO1_OEN    17
#घोषणा V_GPIO1_OEN(x) ((x) << S_GPIO1_OEN)
#घोषणा F_GPIO1_OEN    V_GPIO1_OEN(1U)

#घोषणा S_GPIO0_OEN    16
#घोषणा V_GPIO0_OEN(x) ((x) << S_GPIO0_OEN)
#घोषणा F_GPIO0_OEN    V_GPIO0_OEN(1U)

#घोषणा S_GPIO10_OUT_VAL    10
#घोषणा V_GPIO10_OUT_VAL(x) ((x) << S_GPIO10_OUT_VAL)
#घोषणा F_GPIO10_OUT_VAL    V_GPIO10_OUT_VAL(1U)

#घोषणा S_GPIO7_OUT_VAL    7
#घोषणा V_GPIO7_OUT_VAL(x) ((x) << S_GPIO7_OUT_VAL)
#घोषणा F_GPIO7_OUT_VAL    V_GPIO7_OUT_VAL(1U)

#घोषणा S_GPIO6_OUT_VAL    6
#घोषणा V_GPIO6_OUT_VAL(x) ((x) << S_GPIO6_OUT_VAL)
#घोषणा F_GPIO6_OUT_VAL    V_GPIO6_OUT_VAL(1U)

#घोषणा S_GPIO5_OUT_VAL    5
#घोषणा V_GPIO5_OUT_VAL(x) ((x) << S_GPIO5_OUT_VAL)
#घोषणा F_GPIO5_OUT_VAL    V_GPIO5_OUT_VAL(1U)

#घोषणा S_GPIO4_OUT_VAL    4
#घोषणा V_GPIO4_OUT_VAL(x) ((x) << S_GPIO4_OUT_VAL)
#घोषणा F_GPIO4_OUT_VAL    V_GPIO4_OUT_VAL(1U)

#घोषणा S_GPIO2_OUT_VAL    2
#घोषणा V_GPIO2_OUT_VAL(x) ((x) << S_GPIO2_OUT_VAL)
#घोषणा F_GPIO2_OUT_VAL    V_GPIO2_OUT_VAL(1U)

#घोषणा S_GPIO1_OUT_VAL    1
#घोषणा V_GPIO1_OUT_VAL(x) ((x) << S_GPIO1_OUT_VAL)
#घोषणा F_GPIO1_OUT_VAL    V_GPIO1_OUT_VAL(1U)

#घोषणा S_GPIO0_OUT_VAL    0
#घोषणा V_GPIO0_OUT_VAL(x) ((x) << S_GPIO0_OUT_VAL)
#घोषणा F_GPIO0_OUT_VAL    V_GPIO0_OUT_VAL(1U)

#घोषणा A_T3DBG_INT_ENABLE 0xd8

#घोषणा S_GPIO11    11
#घोषणा V_GPIO11(x) ((x) << S_GPIO11)
#घोषणा F_GPIO11    V_GPIO11(1U)

#घोषणा S_GPIO10    10
#घोषणा V_GPIO10(x) ((x) << S_GPIO10)
#घोषणा F_GPIO10    V_GPIO10(1U)

#घोषणा S_GPIO9    9
#घोषणा V_GPIO9(x) ((x) << S_GPIO9)
#घोषणा F_GPIO9    V_GPIO9(1U)

#घोषणा S_GPIO7    7
#घोषणा V_GPIO7(x) ((x) << S_GPIO7)
#घोषणा F_GPIO7    V_GPIO7(1U)

#घोषणा S_GPIO6    6
#घोषणा V_GPIO6(x) ((x) << S_GPIO6)
#घोषणा F_GPIO6    V_GPIO6(1U)

#घोषणा S_GPIO5    5
#घोषणा V_GPIO5(x) ((x) << S_GPIO5)
#घोषणा F_GPIO5    V_GPIO5(1U)

#घोषणा S_GPIO4    4
#घोषणा V_GPIO4(x) ((x) << S_GPIO4)
#घोषणा F_GPIO4    V_GPIO4(1U)

#घोषणा S_GPIO3    3
#घोषणा V_GPIO3(x) ((x) << S_GPIO3)
#घोषणा F_GPIO3    V_GPIO3(1U)

#घोषणा S_GPIO2    2
#घोषणा V_GPIO2(x) ((x) << S_GPIO2)
#घोषणा F_GPIO2    V_GPIO2(1U)

#घोषणा S_GPIO1    1
#घोषणा V_GPIO1(x) ((x) << S_GPIO1)
#घोषणा F_GPIO1    V_GPIO1(1U)

#घोषणा S_GPIO0    0
#घोषणा V_GPIO0(x) ((x) << S_GPIO0)
#घोषणा F_GPIO0    V_GPIO0(1U)

#घोषणा A_T3DBG_INT_CAUSE 0xdc

#घोषणा A_T3DBG_GPIO_ACT_LOW 0xf0

#घोषणा MC7_PMRX_BASE_ADDR 0x100

#घोषणा A_MC7_CFG 0x100

#घोषणा S_IFEN    13
#घोषणा V_IFEN(x) ((x) << S_IFEN)
#घोषणा F_IFEN    V_IFEN(1U)

#घोषणा S_TERM150    11
#घोषणा V_TERM150(x) ((x) << S_TERM150)
#घोषणा F_TERM150    V_TERM150(1U)

#घोषणा S_SLOW    10
#घोषणा V_SLOW(x) ((x) << S_SLOW)
#घोषणा F_SLOW    V_SLOW(1U)

#घोषणा S_WIDTH    8
#घोषणा M_WIDTH    0x3
#घोषणा V_WIDTH(x) ((x) << S_WIDTH)
#घोषणा G_WIDTH(x) (((x) >> S_WIDTH) & M_WIDTH)

#घोषणा S_BKS    6
#घोषणा V_BKS(x) ((x) << S_BKS)
#घोषणा F_BKS    V_BKS(1U)

#घोषणा S_ORG    5
#घोषणा V_ORG(x) ((x) << S_ORG)
#घोषणा F_ORG    V_ORG(1U)

#घोषणा S_DEN    2
#घोषणा M_DEN    0x7
#घोषणा V_DEN(x) ((x) << S_DEN)
#घोषणा G_DEN(x) (((x) >> S_DEN) & M_DEN)

#घोषणा S_RDY    1
#घोषणा V_RDY(x) ((x) << S_RDY)
#घोषणा F_RDY    V_RDY(1U)

#घोषणा S_CLKEN    0
#घोषणा V_CLKEN(x) ((x) << S_CLKEN)
#घोषणा F_CLKEN    V_CLKEN(1U)

#घोषणा A_MC7_MODE 0x104

#घोषणा S_BUSY    31
#घोषणा V_BUSY(x) ((x) << S_BUSY)
#घोषणा F_BUSY    V_BUSY(1U)

#घोषणा A_MC7_EXT_MODE1 0x108

#घोषणा A_MC7_EXT_MODE2 0x10c

#घोषणा A_MC7_EXT_MODE3 0x110

#घोषणा A_MC7_PRE 0x114

#घोषणा A_MC7_REF 0x118

#घोषणा S_PREREFDIV    1
#घोषणा M_PREREFDIV    0x3fff
#घोषणा V_PREREFDIV(x) ((x) << S_PREREFDIV)

#घोषणा S_PERREFEN    0
#घोषणा V_PERREFEN(x) ((x) << S_PERREFEN)
#घोषणा F_PERREFEN    V_PERREFEN(1U)

#घोषणा A_MC7_DLL 0x11c

#घोषणा S_DLLENB    1
#घोषणा V_DLLENB(x) ((x) << S_DLLENB)
#घोषणा F_DLLENB    V_DLLENB(1U)

#घोषणा S_DLLRST    0
#घोषणा V_DLLRST(x) ((x) << S_DLLRST)
#घोषणा F_DLLRST    V_DLLRST(1U)

#घोषणा A_MC7_PARM 0x120

#घोषणा S_ACTTOPREDLY    26
#घोषणा M_ACTTOPREDLY    0xf
#घोषणा V_ACTTOPREDLY(x) ((x) << S_ACTTOPREDLY)

#घोषणा S_ACTTORDWRDLY    23
#घोषणा M_ACTTORDWRDLY    0x7
#घोषणा V_ACTTORDWRDLY(x) ((x) << S_ACTTORDWRDLY)

#घोषणा S_PRECYC    20
#घोषणा M_PRECYC    0x7
#घोषणा V_PRECYC(x) ((x) << S_PRECYC)

#घोषणा S_REFCYC    13
#घोषणा M_REFCYC    0x7f
#घोषणा V_REFCYC(x) ((x) << S_REFCYC)

#घोषणा S_BKCYC    8
#घोषणा M_BKCYC    0x1f
#घोषणा V_BKCYC(x) ((x) << S_BKCYC)

#घोषणा S_WRTORDDLY    4
#घोषणा M_WRTORDDLY    0xf
#घोषणा V_WRTORDDLY(x) ((x) << S_WRTORDDLY)

#घोषणा S_RDTOWRDLY    0
#घोषणा M_RDTOWRDLY    0xf
#घोषणा V_RDTOWRDLY(x) ((x) << S_RDTOWRDLY)

#घोषणा A_MC7_CAL 0x128

#घोषणा S_CAL_FAULT    30
#घोषणा V_CAL_FAULT(x) ((x) << S_CAL_FAULT)
#घोषणा F_CAL_FAULT    V_CAL_FAULT(1U)

#घोषणा S_SGL_CAL_EN    20
#घोषणा V_SGL_CAL_EN(x) ((x) << S_SGL_CAL_EN)
#घोषणा F_SGL_CAL_EN    V_SGL_CAL_EN(1U)

#घोषणा A_MC7_ERR_ADDR 0x12c

#घोषणा A_MC7_ECC 0x130

#घोषणा S_ECCCHKEN    1
#घोषणा V_ECCCHKEN(x) ((x) << S_ECCCHKEN)
#घोषणा F_ECCCHKEN    V_ECCCHKEN(1U)

#घोषणा S_ECCGENEN    0
#घोषणा V_ECCGENEN(x) ((x) << S_ECCGENEN)
#घोषणा F_ECCGENEN    V_ECCGENEN(1U)

#घोषणा A_MC7_CE_ADDR 0x134

#घोषणा A_MC7_CE_DATA0 0x138

#घोषणा A_MC7_CE_DATA1 0x13c

#घोषणा A_MC7_CE_DATA2 0x140

#घोषणा S_DATA    0
#घोषणा M_DATA    0xff

#घोषणा G_DATA(x) (((x) >> S_DATA) & M_DATA)

#घोषणा A_MC7_UE_ADDR 0x144

#घोषणा A_MC7_UE_DATA0 0x148

#घोषणा A_MC7_UE_DATA1 0x14c

#घोषणा A_MC7_UE_DATA2 0x150

#घोषणा A_MC7_BD_ADDR 0x154

#घोषणा S_ADDR    3

#घोषणा M_ADDR    0x1fffffff

#घोषणा A_MC7_BD_DATA0 0x158

#घोषणा A_MC7_BD_DATA1 0x15c

#घोषणा A_MC7_BD_OP 0x164

#घोषणा S_OP    0

#घोषणा V_OP(x) ((x) << S_OP)
#घोषणा F_OP    V_OP(1U)

#घोषणा A_MC7_BIST_ADDR_BEG 0x168

#घोषणा A_MC7_BIST_ADDR_END 0x16c

#घोषणा A_MC7_BIST_DATA 0x170

#घोषणा A_MC7_BIST_OP 0x174

#घोषणा S_CONT    3
#घोषणा V_CONT(x) ((x) << S_CONT)
#घोषणा F_CONT    V_CONT(1U)

#घोषणा A_MC7_INT_ENABLE 0x178

#घोषणा S_AE    17
#घोषणा V_AE(x) ((x) << S_AE)
#घोषणा F_AE    V_AE(1U)

#घोषणा S_PE    2
#घोषणा M_PE    0x7fff

#घोषणा V_PE(x) ((x) << S_PE)

#घोषणा G_PE(x) (((x) >> S_PE) & M_PE)

#घोषणा S_UE    1
#घोषणा V_UE(x) ((x) << S_UE)
#घोषणा F_UE    V_UE(1U)

#घोषणा S_CE    0
#घोषणा V_CE(x) ((x) << S_CE)
#घोषणा F_CE    V_CE(1U)

#घोषणा A_MC7_INT_CAUSE 0x17c

#घोषणा MC7_PMTX_BASE_ADDR 0x180

#घोषणा MC7_CM_BASE_ADDR 0x200

#घोषणा A_CIM_BOOT_CFG 0x280

#घोषणा S_BOOTADDR    2
#घोषणा M_BOOTADDR    0x3fffffff
#घोषणा V_BOOTADDR(x) ((x) << S_BOOTADDR)

#घोषणा A_CIM_SDRAM_BASE_ADDR 0x28c

#घोषणा A_CIM_SDRAM_ADDR_SIZE 0x290

#घोषणा A_CIM_HOST_INT_ENABLE 0x298

#घोषणा S_DTAGPARERR    28
#घोषणा V_DTAGPARERR(x) ((x) << S_DTAGPARERR)
#घोषणा F_DTAGPARERR    V_DTAGPARERR(1U)

#घोषणा S_ITAGPARERR    27
#घोषणा V_ITAGPARERR(x) ((x) << S_ITAGPARERR)
#घोषणा F_ITAGPARERR    V_ITAGPARERR(1U)

#घोषणा S_IBQTPPARERR    26
#घोषणा V_IBQTPPARERR(x) ((x) << S_IBQTPPARERR)
#घोषणा F_IBQTPPARERR    V_IBQTPPARERR(1U)

#घोषणा S_IBQULPPARERR    25
#घोषणा V_IBQULPPARERR(x) ((x) << S_IBQULPPARERR)
#घोषणा F_IBQULPPARERR    V_IBQULPPARERR(1U)

#घोषणा S_IBQSGEHIPARERR    24
#घोषणा V_IBQSGEHIPARERR(x) ((x) << S_IBQSGEHIPARERR)
#घोषणा F_IBQSGEHIPARERR    V_IBQSGEHIPARERR(1U)

#घोषणा S_IBQSGELOPARERR    23
#घोषणा V_IBQSGELOPARERR(x) ((x) << S_IBQSGELOPARERR)
#घोषणा F_IBQSGELOPARERR    V_IBQSGELOPARERR(1U)

#घोषणा S_OBQULPLOPARERR    22
#घोषणा V_OBQULPLOPARERR(x) ((x) << S_OBQULPLOPARERR)
#घोषणा F_OBQULPLOPARERR    V_OBQULPLOPARERR(1U)

#घोषणा S_OBQULPHIPARERR    21
#घोषणा V_OBQULPHIPARERR(x) ((x) << S_OBQULPHIPARERR)
#घोषणा F_OBQULPHIPARERR    V_OBQULPHIPARERR(1U)

#घोषणा S_OBQSGEPARERR    20
#घोषणा V_OBQSGEPARERR(x) ((x) << S_OBQSGEPARERR)
#घोषणा F_OBQSGEPARERR    V_OBQSGEPARERR(1U)

#घोषणा S_DCACHEPARERR    19
#घोषणा V_DCACHEPARERR(x) ((x) << S_DCACHEPARERR)
#घोषणा F_DCACHEPARERR    V_DCACHEPARERR(1U)

#घोषणा S_ICACHEPARERR    18
#घोषणा V_ICACHEPARERR(x) ((x) << S_ICACHEPARERR)
#घोषणा F_ICACHEPARERR    V_ICACHEPARERR(1U)

#घोषणा S_DRAMPARERR    17
#घोषणा V_DRAMPARERR(x) ((x) << S_DRAMPARERR)
#घोषणा F_DRAMPARERR    V_DRAMPARERR(1U)

#घोषणा A_CIM_HOST_INT_CAUSE 0x29c

#घोषणा S_BLKWRPLINT    12
#घोषणा V_BLKWRPLINT(x) ((x) << S_BLKWRPLINT)
#घोषणा F_BLKWRPLINT    V_BLKWRPLINT(1U)

#घोषणा S_BLKRDPLINT    11
#घोषणा V_BLKRDPLINT(x) ((x) << S_BLKRDPLINT)
#घोषणा F_BLKRDPLINT    V_BLKRDPLINT(1U)

#घोषणा S_BLKWRCTLINT    10
#घोषणा V_BLKWRCTLINT(x) ((x) << S_BLKWRCTLINT)
#घोषणा F_BLKWRCTLINT    V_BLKWRCTLINT(1U)

#घोषणा S_BLKRDCTLINT    9
#घोषणा V_BLKRDCTLINT(x) ((x) << S_BLKRDCTLINT)
#घोषणा F_BLKRDCTLINT    V_BLKRDCTLINT(1U)

#घोषणा S_BLKWRFLASHINT    8
#घोषणा V_BLKWRFLASHINT(x) ((x) << S_BLKWRFLASHINT)
#घोषणा F_BLKWRFLASHINT    V_BLKWRFLASHINT(1U)

#घोषणा S_BLKRDFLASHINT    7
#घोषणा V_BLKRDFLASHINT(x) ((x) << S_BLKRDFLASHINT)
#घोषणा F_BLKRDFLASHINT    V_BLKRDFLASHINT(1U)

#घोषणा S_SGLWRFLASHINT    6
#घोषणा V_SGLWRFLASHINT(x) ((x) << S_SGLWRFLASHINT)
#घोषणा F_SGLWRFLASHINT    V_SGLWRFLASHINT(1U)

#घोषणा S_WRBLKFLASHINT    5
#घोषणा V_WRBLKFLASHINT(x) ((x) << S_WRBLKFLASHINT)
#घोषणा F_WRBLKFLASHINT    V_WRBLKFLASHINT(1U)

#घोषणा S_BLKWRBOOTINT    4
#घोषणा V_BLKWRBOOTINT(x) ((x) << S_BLKWRBOOTINT)
#घोषणा F_BLKWRBOOTINT    V_BLKWRBOOTINT(1U)

#घोषणा S_FLASHRANGEINT    2
#घोषणा V_FLASHRANGEINT(x) ((x) << S_FLASHRANGEINT)
#घोषणा F_FLASHRANGEINT    V_FLASHRANGEINT(1U)

#घोषणा S_SDRAMRANGEINT    1
#घोषणा V_SDRAMRANGEINT(x) ((x) << S_SDRAMRANGEINT)
#घोषणा F_SDRAMRANGEINT    V_SDRAMRANGEINT(1U)

#घोषणा S_RSVDSPACEINT    0
#घोषणा V_RSVDSPACEINT(x) ((x) << S_RSVDSPACEINT)
#घोषणा F_RSVDSPACEINT    V_RSVDSPACEINT(1U)

#घोषणा A_CIM_HOST_ACC_CTRL 0x2b0

#घोषणा S_HOSTBUSY    17
#घोषणा V_HOSTBUSY(x) ((x) << S_HOSTBUSY)
#घोषणा F_HOSTBUSY    V_HOSTBUSY(1U)

#घोषणा A_CIM_HOST_ACC_DATA 0x2b4

#घोषणा A_CIM_IBQ_DBG_CFG 0x2c0

#घोषणा S_IBQDBGADDR    16
#घोषणा M_IBQDBGADDR    0x1ff
#घोषणा V_IBQDBGADDR(x) ((x) << S_IBQDBGADDR)
#घोषणा G_IBQDBGADDR(x) (((x) >> S_IBQDBGADDR) & M_IBQDBGADDR)

#घोषणा S_IBQDBGQID    3
#घोषणा M_IBQDBGQID    0x3
#घोषणा V_IBQDBGQID(x) ((x) << S_IBQDBGQID)
#घोषणा G_IBQDBGQID(x) (((x) >> S_IBQDBGQID) & M_IBQDBGQID)

#घोषणा S_IBQDBGWR    2
#घोषणा V_IBQDBGWR(x) ((x) << S_IBQDBGWR)
#घोषणा F_IBQDBGWR    V_IBQDBGWR(1U)

#घोषणा S_IBQDBGBUSY    1
#घोषणा V_IBQDBGBUSY(x) ((x) << S_IBQDBGBUSY)
#घोषणा F_IBQDBGBUSY    V_IBQDBGBUSY(1U)

#घोषणा S_IBQDBGEN    0
#घोषणा V_IBQDBGEN(x) ((x) << S_IBQDBGEN)
#घोषणा F_IBQDBGEN    V_IBQDBGEN(1U)

#घोषणा A_CIM_IBQ_DBG_DATA 0x2c8

#घोषणा A_TP_IN_CONFIG 0x300

#घोषणा S_RXFBARBPRIO    25
#घोषणा V_RXFBARBPRIO(x) ((x) << S_RXFBARBPRIO)
#घोषणा F_RXFBARBPRIO    V_RXFBARBPRIO(1U)

#घोषणा S_TXFBARBPRIO    24
#घोषणा V_TXFBARBPRIO(x) ((x) << S_TXFBARBPRIO)
#घोषणा F_TXFBARBPRIO    V_TXFBARBPRIO(1U)

#घोषणा S_NICMODE    14
#घोषणा V_NICMODE(x) ((x) << S_NICMODE)
#घोषणा F_NICMODE    V_NICMODE(1U)

#घोषणा S_IPV6ENABLE    15
#घोषणा V_IPV6ENABLE(x) ((x) << S_IPV6ENABLE)
#घोषणा F_IPV6ENABLE    V_IPV6ENABLE(1U)

#घोषणा A_TP_OUT_CONFIG 0x304

#घोषणा S_VLANEXTRACTIONENABLE    12

#घोषणा A_TP_GLOBAL_CONFIG 0x308

#घोषणा S_TXPACINGENABLE    24
#घोषणा V_TXPACINGENABLE(x) ((x) << S_TXPACINGENABLE)
#घोषणा F_TXPACINGENABLE    V_TXPACINGENABLE(1U)

#घोषणा S_PATHMTU    15
#घोषणा V_PATHMTU(x) ((x) << S_PATHMTU)
#घोषणा F_PATHMTU    V_PATHMTU(1U)

#घोषणा S_IPCHECKSUMOFFLOAD    13
#घोषणा V_IPCHECKSUMOFFLOAD(x) ((x) << S_IPCHECKSUMOFFLOAD)
#घोषणा F_IPCHECKSUMOFFLOAD    V_IPCHECKSUMOFFLOAD(1U)

#घोषणा S_UDPCHECKSUMOFFLOAD    12
#घोषणा V_UDPCHECKSUMOFFLOAD(x) ((x) << S_UDPCHECKSUMOFFLOAD)
#घोषणा F_UDPCHECKSUMOFFLOAD    V_UDPCHECKSUMOFFLOAD(1U)

#घोषणा S_TCPCHECKSUMOFFLOAD    11
#घोषणा V_TCPCHECKSUMOFFLOAD(x) ((x) << S_TCPCHECKSUMOFFLOAD)
#घोषणा F_TCPCHECKSUMOFFLOAD    V_TCPCHECKSUMOFFLOAD(1U)

#घोषणा S_IPTTL    0
#घोषणा M_IPTTL    0xff
#घोषणा V_IPTTL(x) ((x) << S_IPTTL)

#घोषणा A_TP_CMM_MM_BASE 0x314

#घोषणा A_TP_CMM_TIMER_BASE 0x318

#घोषणा S_CMTIMERMAXNUM    28
#घोषणा M_CMTIMERMAXNUM    0x3
#घोषणा V_CMTIMERMAXNUM(x) ((x) << S_CMTIMERMAXNUM)

#घोषणा A_TP_PMM_SIZE 0x31c

#घोषणा A_TP_PMM_TX_BASE 0x320

#घोषणा A_TP_PMM_RX_BASE 0x328

#घोषणा A_TP_PMM_RX_PAGE_SIZE 0x32c

#घोषणा A_TP_PMM_RX_MAX_PAGE 0x330

#घोषणा A_TP_PMM_TX_PAGE_SIZE 0x334

#घोषणा A_TP_PMM_TX_MAX_PAGE 0x338

#घोषणा A_TP_TCP_OPTIONS 0x340

#घोषणा S_MTUDEFAULT    16
#घोषणा M_MTUDEFAULT    0xffff
#घोषणा V_MTUDEFAULT(x) ((x) << S_MTUDEFAULT)

#घोषणा S_MTUENABLE    10
#घोषणा V_MTUENABLE(x) ((x) << S_MTUENABLE)
#घोषणा F_MTUENABLE    V_MTUENABLE(1U)

#घोषणा S_SACKRX    8
#घोषणा V_SACKRX(x) ((x) << S_SACKRX)
#घोषणा F_SACKRX    V_SACKRX(1U)

#घोषणा S_SACKMODE    4

#घोषणा M_SACKMODE    0x3

#घोषणा V_SACKMODE(x) ((x) << S_SACKMODE)

#घोषणा S_WINDOWSCALEMODE    2
#घोषणा M_WINDOWSCALEMODE    0x3
#घोषणा V_WINDOWSCALEMODE(x) ((x) << S_WINDOWSCALEMODE)

#घोषणा S_TIMESTAMPSMODE    0

#घोषणा M_TIMESTAMPSMODE    0x3

#घोषणा V_TIMESTAMPSMODE(x) ((x) << S_TIMESTAMPSMODE)

#घोषणा A_TP_DACK_CONFIG 0x344

#घोषणा S_AUTOSTATE3    30
#घोषणा M_AUTOSTATE3    0x3
#घोषणा V_AUTOSTATE3(x) ((x) << S_AUTOSTATE3)

#घोषणा S_AUTOSTATE2    28
#घोषणा M_AUTOSTATE2    0x3
#घोषणा V_AUTOSTATE2(x) ((x) << S_AUTOSTATE2)

#घोषणा S_AUTOSTATE1    26
#घोषणा M_AUTOSTATE1    0x3
#घोषणा V_AUTOSTATE1(x) ((x) << S_AUTOSTATE1)

#घोषणा S_BYTETHRESHOLD    5
#घोषणा M_BYTETHRESHOLD    0xfffff
#घोषणा V_BYTETHRESHOLD(x) ((x) << S_BYTETHRESHOLD)

#घोषणा S_MSSTHRESHOLD    3
#घोषणा M_MSSTHRESHOLD    0x3
#घोषणा V_MSSTHRESHOLD(x) ((x) << S_MSSTHRESHOLD)

#घोषणा S_AUTOCAREFUL    2
#घोषणा V_AUTOCAREFUL(x) ((x) << S_AUTOCAREFUL)
#घोषणा F_AUTOCAREFUL    V_AUTOCAREFUL(1U)

#घोषणा S_AUTOENABLE    1
#घोषणा V_AUTOENABLE(x) ((x) << S_AUTOENABLE)
#घोषणा F_AUTOENABLE    V_AUTOENABLE(1U)

#घोषणा S_DACK_MODE    0
#घोषणा V_DACK_MODE(x) ((x) << S_DACK_MODE)
#घोषणा F_DACK_MODE    V_DACK_MODE(1U)

#घोषणा A_TP_PC_CONFIG 0x348

#घोषणा S_TXTOSQUEUEMAPMODE    26
#घोषणा V_TXTOSQUEUEMAPMODE(x) ((x) << S_TXTOSQUEUEMAPMODE)
#घोषणा F_TXTOSQUEUEMAPMODE    V_TXTOSQUEUEMAPMODE(1U)

#घोषणा S_ENABLEEPCMDAFULL    23
#घोषणा V_ENABLEEPCMDAFULL(x) ((x) << S_ENABLEEPCMDAFULL)
#घोषणा F_ENABLEEPCMDAFULL    V_ENABLEEPCMDAFULL(1U)

#घोषणा S_MODULATEUNIONMODE    22
#घोषणा V_MODULATEUNIONMODE(x) ((x) << S_MODULATEUNIONMODE)
#घोषणा F_MODULATEUNIONMODE    V_MODULATEUNIONMODE(1U)

#घोषणा S_TXDEFERENABLE    20
#घोषणा V_TXDEFERENABLE(x) ((x) << S_TXDEFERENABLE)
#घोषणा F_TXDEFERENABLE    V_TXDEFERENABLE(1U)

#घोषणा S_RXCONGESTIONMODE    19
#घोषणा V_RXCONGESTIONMODE(x) ((x) << S_RXCONGESTIONMODE)
#घोषणा F_RXCONGESTIONMODE    V_RXCONGESTIONMODE(1U)

#घोषणा S_HEARBEATDACK    16
#घोषणा V_HEARBEATDACK(x) ((x) << S_HEARBEATDACK)
#घोषणा F_HEARBEATDACK    V_HEARBEATDACK(1U)

#घोषणा S_TXCONGESTIONMODE    15
#घोषणा V_TXCONGESTIONMODE(x) ((x) << S_TXCONGESTIONMODE)
#घोषणा F_TXCONGESTIONMODE    V_TXCONGESTIONMODE(1U)

#घोषणा S_ENABLEOCSPIFULL    30
#घोषणा V_ENABLEOCSPIFULL(x) ((x) << S_ENABLEOCSPIFULL)
#घोषणा F_ENABLEOCSPIFULL    V_ENABLEOCSPIFULL(1U)

#घोषणा S_LOCKTID    28
#घोषणा V_LOCKTID(x) ((x) << S_LOCKTID)
#घोषणा F_LOCKTID    V_LOCKTID(1U)

#घोषणा S_TABLELATENCYDELTA    0
#घोषणा M_TABLELATENCYDELTA    0xf
#घोषणा V_TABLELATENCYDELTA(x) ((x) << S_TABLELATENCYDELTA)
#घोषणा G_TABLELATENCYDELTA(x) \
	(((x) >> S_TABLELATENCYDELTA) & M_TABLELATENCYDELTA)

#घोषणा A_TP_PC_CONFIG2 0x34c

#घोषणा S_DISBLEDAPARBIT0    15
#घोषणा V_DISBLEDAPARBIT0(x) ((x) << S_DISBLEDAPARBIT0)
#घोषणा F_DISBLEDAPARBIT0    V_DISBLEDAPARBIT0(1U)

#घोषणा S_ENABLEARPMISS    13
#घोषणा V_ENABLEARPMISS(x) ((x) << S_ENABLEARPMISS)
#घोषणा F_ENABLEARPMISS    V_ENABLEARPMISS(1U)

#घोषणा S_ENABLENONOFDTNLSYN    12
#घोषणा V_ENABLENONOFDTNLSYN(x) ((x) << S_ENABLENONOFDTNLSYN)
#घोषणा F_ENABLENONOFDTNLSYN    V_ENABLENONOFDTNLSYN(1U)

#घोषणा S_ENABLEIPV6RSS    11
#घोषणा V_ENABLEIPV6RSS(x) ((x) << S_ENABLEIPV6RSS)
#घोषणा F_ENABLEIPV6RSS    V_ENABLEIPV6RSS(1U)

#घोषणा S_CHDRAFULL    4
#घोषणा V_CHDRAFULL(x) ((x) << S_CHDRAFULL)
#घोषणा F_CHDRAFULL    V_CHDRAFULL(1U)

#घोषणा A_TP_TCP_BACKOFF_REG0 0x350

#घोषणा A_TP_TCP_BACKOFF_REG1 0x354

#घोषणा A_TP_TCP_BACKOFF_REG2 0x358

#घोषणा A_TP_TCP_BACKOFF_REG3 0x35c

#घोषणा A_TP_PARA_REG2 0x368

#घोषणा S_MAXRXDATA    16
#घोषणा M_MAXRXDATA    0xffff
#घोषणा V_MAXRXDATA(x) ((x) << S_MAXRXDATA)

#घोषणा S_RXCOALESCESIZE    0
#घोषणा M_RXCOALESCESIZE    0xffff
#घोषणा V_RXCOALESCESIZE(x) ((x) << S_RXCOALESCESIZE)

#घोषणा A_TP_PARA_REG3 0x36c

#घोषणा S_TXDATAACKIDX    16
#घोषणा M_TXDATAACKIDX    0xf

#घोषणा V_TXDATAACKIDX(x) ((x) << S_TXDATAACKIDX)

#घोषणा S_TXPACEAUTOSTRICT    10
#घोषणा V_TXPACEAUTOSTRICT(x) ((x) << S_TXPACEAUTOSTRICT)
#घोषणा F_TXPACEAUTOSTRICT    V_TXPACEAUTOSTRICT(1U)

#घोषणा S_TXPACEFIXED    9
#घोषणा V_TXPACEFIXED(x) ((x) << S_TXPACEFIXED)
#घोषणा F_TXPACEFIXED    V_TXPACEFIXED(1U)

#घोषणा S_TXPACEAUTO    8
#घोषणा V_TXPACEAUTO(x) ((x) << S_TXPACEAUTO)
#घोषणा F_TXPACEAUTO    V_TXPACEAUTO(1U)

#घोषणा S_RXCOALESCEENABLE    1
#घोषणा V_RXCOALESCEENABLE(x) ((x) << S_RXCOALESCEENABLE)
#घोषणा F_RXCOALESCEENABLE    V_RXCOALESCEENABLE(1U)

#घोषणा S_RXCOALESCEPSHEN    0
#घोषणा V_RXCOALESCEPSHEN(x) ((x) << S_RXCOALESCEPSHEN)
#घोषणा F_RXCOALESCEPSHEN    V_RXCOALESCEPSHEN(1U)

#घोषणा A_TP_PARA_REG4 0x370

#घोषणा A_TP_PARA_REG5 0x374

#घोषणा S_RXDDPOFFINIT    3
#घोषणा V_RXDDPOFFINIT(x) ((x) << S_RXDDPOFFINIT)
#घोषणा F_RXDDPOFFINIT    V_RXDDPOFFINIT(1U)

#घोषणा A_TP_PARA_REG6 0x378

#घोषणा S_T3A_ENABLEESND    13
#घोषणा V_T3A_ENABLEESND(x) ((x) << S_T3A_ENABLEESND)
#घोषणा F_T3A_ENABLEESND    V_T3A_ENABLEESND(1U)

#घोषणा S_ENABLEESND    11
#घोषणा V_ENABLEESND(x) ((x) << S_ENABLEESND)
#घोषणा F_ENABLEESND    V_ENABLEESND(1U)

#घोषणा A_TP_PARA_REG7 0x37c

#घोषणा S_PMMAXXFERLEN1    16
#घोषणा M_PMMAXXFERLEN1    0xffff
#घोषणा V_PMMAXXFERLEN1(x) ((x) << S_PMMAXXFERLEN1)

#घोषणा S_PMMAXXFERLEN0    0
#घोषणा M_PMMAXXFERLEN0    0xffff
#घोषणा V_PMMAXXFERLEN0(x) ((x) << S_PMMAXXFERLEN0)

#घोषणा A_TP_TIMER_RESOLUTION 0x390

#घोषणा S_TIMERRESOLUTION    16
#घोषणा M_TIMERRESOLUTION    0xff
#घोषणा V_TIMERRESOLUTION(x) ((x) << S_TIMERRESOLUTION)

#घोषणा S_TIMESTAMPRESOLUTION    8
#घोषणा M_TIMESTAMPRESOLUTION    0xff
#घोषणा V_TIMESTAMPRESOLUTION(x) ((x) << S_TIMESTAMPRESOLUTION)

#घोषणा S_DELAYEDACKRESOLUTION    0
#घोषणा M_DELAYEDACKRESOLUTION    0xff
#घोषणा V_DELAYEDACKRESOLUTION(x) ((x) << S_DELAYEDACKRESOLUTION)

#घोषणा A_TP_MSL 0x394

#घोषणा A_TP_RXT_MIN 0x398

#घोषणा A_TP_RXT_MAX 0x39c

#घोषणा A_TP_PERS_MIN 0x3a0

#घोषणा A_TP_PERS_MAX 0x3a4

#घोषणा A_TP_KEEP_IDLE 0x3a8

#घोषणा A_TP_KEEP_INTVL 0x3ac

#घोषणा A_TP_INIT_SRTT 0x3b0

#घोषणा A_TP_DACK_TIMER 0x3b4

#घोषणा A_TP_FINWAIT2_TIMER 0x3b8

#घोषणा A_TP_SHIFT_CNT 0x3c0

#घोषणा S_SYNSHIFTMAX    24

#घोषणा M_SYNSHIFTMAX    0xff

#घोषणा V_SYNSHIFTMAX(x) ((x) << S_SYNSHIFTMAX)

#घोषणा S_RXTSHIFTMAXR1    20

#घोषणा M_RXTSHIFTMAXR1    0xf

#घोषणा V_RXTSHIFTMAXR1(x) ((x) << S_RXTSHIFTMAXR1)

#घोषणा S_RXTSHIFTMAXR2    16

#घोषणा M_RXTSHIFTMAXR2    0xf

#घोषणा V_RXTSHIFTMAXR2(x) ((x) << S_RXTSHIFTMAXR2)

#घोषणा S_PERSHIFTBACKOFFMAX    12
#घोषणा M_PERSHIFTBACKOFFMAX    0xf
#घोषणा V_PERSHIFTBACKOFFMAX(x) ((x) << S_PERSHIFTBACKOFFMAX)

#घोषणा S_PERSHIFTMAX    8
#घोषणा M_PERSHIFTMAX    0xf
#घोषणा V_PERSHIFTMAX(x) ((x) << S_PERSHIFTMAX)

#घोषणा S_KEEPALIVEMAX    0

#घोषणा M_KEEPALIVEMAX    0xff

#घोषणा V_KEEPALIVEMAX(x) ((x) << S_KEEPALIVEMAX)

#घोषणा A_TP_MTU_PORT_TABLE 0x3d0

#घोषणा A_TP_CCTRL_TABLE 0x3dc

#घोषणा A_TP_MTU_TABLE 0x3e4

#घोषणा A_TP_RSS_MAP_TABLE 0x3e8

#घोषणा A_TP_RSS_LKP_TABLE 0x3ec

#घोषणा A_TP_RSS_CONFIG 0x3f0

#घोषणा S_TNL4TUPEN    29
#घोषणा V_TNL4TUPEN(x) ((x) << S_TNL4TUPEN)
#घोषणा F_TNL4TUPEN    V_TNL4TUPEN(1U)

#घोषणा S_TNL2TUPEN    28
#घोषणा V_TNL2TUPEN(x) ((x) << S_TNL2TUPEN)
#घोषणा F_TNL2TUPEN    V_TNL2TUPEN(1U)

#घोषणा S_TNLPRTEN    26
#घोषणा V_TNLPRTEN(x) ((x) << S_TNLPRTEN)
#घोषणा F_TNLPRTEN    V_TNLPRTEN(1U)

#घोषणा S_TNLMAPEN    25
#घोषणा V_TNLMAPEN(x) ((x) << S_TNLMAPEN)
#घोषणा F_TNLMAPEN    V_TNLMAPEN(1U)

#घोषणा S_TNLLKPEN    24
#घोषणा V_TNLLKPEN(x) ((x) << S_TNLLKPEN)
#घोषणा F_TNLLKPEN    V_TNLLKPEN(1U)

#घोषणा S_RRCPLMAPEN    7
#घोषणा V_RRCPLMAPEN(x) ((x) << S_RRCPLMAPEN)
#घोषणा F_RRCPLMAPEN    V_RRCPLMAPEN(1U)

#घोषणा S_RRCPLCPUSIZE    4
#घोषणा M_RRCPLCPUSIZE    0x7
#घोषणा V_RRCPLCPUSIZE(x) ((x) << S_RRCPLCPUSIZE)

#घोषणा S_RQFEEDBACKENABLE    3
#घोषणा V_RQFEEDBACKENABLE(x) ((x) << S_RQFEEDBACKENABLE)
#घोषणा F_RQFEEDBACKENABLE    V_RQFEEDBACKENABLE(1U)

#घोषणा S_HASHTOEPLITZ    2
#घोषणा V_HASHTOEPLITZ(x) ((x) << S_HASHTOEPLITZ)
#घोषणा F_HASHTOEPLITZ    V_HASHTOEPLITZ(1U)

#घोषणा S_DISABLE    0

#घोषणा A_TP_TM_PIO_ADDR 0x418

#घोषणा A_TP_TM_PIO_DATA 0x41c

#घोषणा A_TP_TX_MOD_QUE_TABLE 0x420

#घोषणा A_TP_TX_RESOURCE_LIMIT 0x424

#घोषणा A_TP_TX_MOD_QUEUE_REQ_MAP 0x428

#घोषणा S_TX_MOD_QUEUE_REQ_MAP    0
#घोषणा M_TX_MOD_QUEUE_REQ_MAP    0xff
#घोषणा V_TX_MOD_QUEUE_REQ_MAP(x) ((x) << S_TX_MOD_QUEUE_REQ_MAP)

#घोषणा A_TP_TX_MOD_QUEUE_WEIGHT1 0x42c

#घोषणा A_TP_TX_MOD_QUEUE_WEIGHT0 0x430

#घोषणा A_TP_MOD_CHANNEL_WEIGHT 0x434

#घोषणा A_TP_MOD_RATE_LIMIT 0x438

#घोषणा A_TP_PIO_ADDR 0x440

#घोषणा A_TP_PIO_DATA 0x444

#घोषणा A_TP_RESET 0x44c

#घोषणा S_FLSTINITENABLE    1
#घोषणा V_FLSTINITENABLE(x) ((x) << S_FLSTINITENABLE)
#घोषणा F_FLSTINITENABLE    V_FLSTINITENABLE(1U)

#घोषणा S_TPRESET    0
#घोषणा V_TPRESET(x) ((x) << S_TPRESET)
#घोषणा F_TPRESET    V_TPRESET(1U)

#घोषणा A_TP_CMM_MM_RX_FLST_BASE 0x460

#घोषणा A_TP_CMM_MM_TX_FLST_BASE 0x464

#घोषणा A_TP_CMM_MM_PS_FLST_BASE 0x468

#घोषणा A_TP_MIB_INDEX 0x450

#घोषणा A_TP_MIB_RDATA 0x454

#घोषणा A_TP_CMM_MM_MAX_PSTRUCT 0x46c

#घोषणा A_TP_INT_ENABLE 0x470

#घोषणा S_FLMTXFLSTEMPTY    30
#घोषणा V_FLMTXFLSTEMPTY(x) ((x) << S_FLMTXFLSTEMPTY)
#घोषणा F_FLMTXFLSTEMPTY    V_FLMTXFLSTEMPTY(1U)

#घोषणा S_FLMRXFLSTEMPTY    29
#घोषणा V_FLMRXFLSTEMPTY(x) ((x) << S_FLMRXFLSTEMPTY)
#घोषणा F_FLMRXFLSTEMPTY    V_FLMRXFLSTEMPTY(1U)

#घोषणा S_ARPLUTPERR    26
#घोषणा V_ARPLUTPERR(x) ((x) << S_ARPLUTPERR)
#घोषणा F_ARPLUTPERR    V_ARPLUTPERR(1U)

#घोषणा S_CMCACHEPERR    24
#घोषणा V_CMCACHEPERR(x) ((x) << S_CMCACHEPERR)
#घोषणा F_CMCACHEPERR    V_CMCACHEPERR(1U)

#घोषणा A_TP_INT_CAUSE 0x474

#घोषणा A_TP_TX_MOD_Q1_Q0_RATE_LIMIT 0x8

#घोषणा A_TP_TX_DROP_CFG_CH0 0x12b

#घोषणा A_TP_TX_DROP_MODE 0x12f

#घोषणा A_TP_EGRESS_CONFIG 0x145

#घोषणा S_REWRITEFORCETOSIZE    0
#घोषणा V_REWRITEFORCETOSIZE(x) ((x) << S_REWRITEFORCETOSIZE)
#घोषणा F_REWRITEFORCETOSIZE    V_REWRITEFORCETOSIZE(1U)

#घोषणा A_TP_TX_TRC_KEY0 0x20

#घोषणा A_TP_RX_TRC_KEY0 0x120

#घोषणा A_TP_TX_DROP_CNT_CH0 0x12d

#घोषणा S_TXDROPCNTCH0RCVD    0
#घोषणा M_TXDROPCNTCH0RCVD    0xffff
#घोषणा V_TXDROPCNTCH0RCVD(x) ((x) << S_TXDROPCNTCH0RCVD)
#घोषणा G_TXDROPCNTCH0RCVD(x) (((x) >> S_TXDROPCNTCH0RCVD) & \
			       M_TXDROPCNTCH0RCVD)

#घोषणा A_TP_PROXY_FLOW_CNTL 0x4b0

#घोषणा A_TP_EMBED_OP_FIELD0 0x4e8
#घोषणा A_TP_EMBED_OP_FIELD1 0x4ec
#घोषणा A_TP_EMBED_OP_FIELD2 0x4f0
#घोषणा A_TP_EMBED_OP_FIELD3 0x4f4
#घोषणा A_TP_EMBED_OP_FIELD4 0x4f8
#घोषणा A_TP_EMBED_OP_FIELD5 0x4fc

#घोषणा A_ULPRX_CTL 0x500

#घोषणा S_ROUND_ROBIN    4
#घोषणा V_ROUND_ROBIN(x) ((x) << S_ROUND_ROBIN)
#घोषणा F_ROUND_ROBIN    V_ROUND_ROBIN(1U)

#घोषणा A_ULPRX_INT_ENABLE 0x504

#घोषणा S_DATASELFRAMEERR0    7
#घोषणा V_DATASELFRAMEERR0(x) ((x) << S_DATASELFRAMEERR0)
#घोषणा F_DATASELFRAMEERR0    V_DATASELFRAMEERR0(1U)

#घोषणा S_DATASELFRAMEERR1    6
#घोषणा V_DATASELFRAMEERR1(x) ((x) << S_DATASELFRAMEERR1)
#घोषणा F_DATASELFRAMEERR1    V_DATASELFRAMEERR1(1U)

#घोषणा S_PCMDMUXPERR    5
#घोषणा V_PCMDMUXPERR(x) ((x) << S_PCMDMUXPERR)
#घोषणा F_PCMDMUXPERR    V_PCMDMUXPERR(1U)

#घोषणा S_ARBFPERR    4
#घोषणा V_ARBFPERR(x) ((x) << S_ARBFPERR)
#घोषणा F_ARBFPERR    V_ARBFPERR(1U)

#घोषणा S_ARBPF0PERR    3
#घोषणा V_ARBPF0PERR(x) ((x) << S_ARBPF0PERR)
#घोषणा F_ARBPF0PERR    V_ARBPF0PERR(1U)

#घोषणा S_ARBPF1PERR    2
#घोषणा V_ARBPF1PERR(x) ((x) << S_ARBPF1PERR)
#घोषणा F_ARBPF1PERR    V_ARBPF1PERR(1U)

#घोषणा S_PARERRPCMD    1
#घोषणा V_PARERRPCMD(x) ((x) << S_PARERRPCMD)
#घोषणा F_PARERRPCMD    V_PARERRPCMD(1U)

#घोषणा S_PARERRDATA    0
#घोषणा V_PARERRDATA(x) ((x) << S_PARERRDATA)
#घोषणा F_PARERRDATA    V_PARERRDATA(1U)

#घोषणा A_ULPRX_INT_CAUSE 0x508

#घोषणा A_ULPRX_ISCSI_LLIMIT 0x50c

#घोषणा A_ULPRX_ISCSI_ULIMIT 0x510

#घोषणा A_ULPRX_ISCSI_TAGMASK 0x514

#घोषणा A_ULPRX_ISCSI_PSZ 0x518

#घोषणा A_ULPRX_TDDP_LLIMIT 0x51c

#घोषणा A_ULPRX_TDDP_ULIMIT 0x520
#घोषणा A_ULPRX_TDDP_PSZ 0x528

#घोषणा S_HPZ0    0
#घोषणा M_HPZ0    0xf
#घोषणा V_HPZ0(x) ((x) << S_HPZ0)
#घोषणा G_HPZ0(x) (((x) >> S_HPZ0) & M_HPZ0)

#घोषणा A_ULPRX_STAG_LLIMIT 0x52c

#घोषणा A_ULPRX_STAG_ULIMIT 0x530

#घोषणा A_ULPRX_RQ_LLIMIT 0x534

#घोषणा A_ULPRX_RQ_ULIMIT 0x538

#घोषणा A_ULPRX_PBL_LLIMIT 0x53c

#घोषणा A_ULPRX_PBL_ULIMIT 0x540

#घोषणा A_ULPRX_TDDP_TAGMASK 0x524

#घोषणा A_ULPTX_CONFIG 0x580

#घोषणा S_CFG_CQE_SOP_MASK    1
#घोषणा V_CFG_CQE_SOP_MASK(x) ((x) << S_CFG_CQE_SOP_MASK)
#घोषणा F_CFG_CQE_SOP_MASK    V_CFG_CQE_SOP_MASK(1U)

#घोषणा S_CFG_RR_ARB    0
#घोषणा V_CFG_RR_ARB(x) ((x) << S_CFG_RR_ARB)
#घोषणा F_CFG_RR_ARB    V_CFG_RR_ARB(1U)

#घोषणा A_ULPTX_INT_ENABLE 0x584

#घोषणा S_PBL_BOUND_ERR_CH1    1
#घोषणा V_PBL_BOUND_ERR_CH1(x) ((x) << S_PBL_BOUND_ERR_CH1)
#घोषणा F_PBL_BOUND_ERR_CH1    V_PBL_BOUND_ERR_CH1(1U)

#घोषणा S_PBL_BOUND_ERR_CH0    0
#घोषणा V_PBL_BOUND_ERR_CH0(x) ((x) << S_PBL_BOUND_ERR_CH0)
#घोषणा F_PBL_BOUND_ERR_CH0    V_PBL_BOUND_ERR_CH0(1U)

#घोषणा A_ULPTX_INT_CAUSE 0x588

#घोषणा A_ULPTX_TPT_LLIMIT 0x58c

#घोषणा A_ULPTX_TPT_ULIMIT 0x590

#घोषणा A_ULPTX_PBL_LLIMIT 0x594

#घोषणा A_ULPTX_PBL_ULIMIT 0x598

#घोषणा A_ULPTX_DMA_WEIGHT 0x5ac

#घोषणा S_D1_WEIGHT    16
#घोषणा M_D1_WEIGHT    0xffff
#घोषणा V_D1_WEIGHT(x) ((x) << S_D1_WEIGHT)

#घोषणा S_D0_WEIGHT    0
#घोषणा M_D0_WEIGHT    0xffff
#घोषणा V_D0_WEIGHT(x) ((x) << S_D0_WEIGHT)

#घोषणा A_PM1_RX_CFG 0x5c0
#घोषणा A_PM1_RX_MODE 0x5c4

#घोषणा A_PM1_RX_INT_ENABLE 0x5d8

#घोषणा S_ZERO_E_CMD_ERROR    18
#घोषणा V_ZERO_E_CMD_ERROR(x) ((x) << S_ZERO_E_CMD_ERROR)
#घोषणा F_ZERO_E_CMD_ERROR    V_ZERO_E_CMD_ERROR(1U)

#घोषणा S_IESPI0_FIFO2X_RX_FRAMING_ERROR    17
#घोषणा V_IESPI0_FIFO2X_RX_FRAMING_ERROR(x) ((x) << S_IESPI0_FIFO2X_RX_FRAMING_ERROR)
#घोषणा F_IESPI0_FIFO2X_RX_FRAMING_ERROR    V_IESPI0_FIFO2X_RX_FRAMING_ERROR(1U)

#घोषणा S_IESPI1_FIFO2X_RX_FRAMING_ERROR    16
#घोषणा V_IESPI1_FIFO2X_RX_FRAMING_ERROR(x) ((x) << S_IESPI1_FIFO2X_RX_FRAMING_ERROR)
#घोषणा F_IESPI1_FIFO2X_RX_FRAMING_ERROR    V_IESPI1_FIFO2X_RX_FRAMING_ERROR(1U)

#घोषणा S_IESPI0_RX_FRAMING_ERROR    15
#घोषणा V_IESPI0_RX_FRAMING_ERROR(x) ((x) << S_IESPI0_RX_FRAMING_ERROR)
#घोषणा F_IESPI0_RX_FRAMING_ERROR    V_IESPI0_RX_FRAMING_ERROR(1U)

#घोषणा S_IESPI1_RX_FRAMING_ERROR    14
#घोषणा V_IESPI1_RX_FRAMING_ERROR(x) ((x) << S_IESPI1_RX_FRAMING_ERROR)
#घोषणा F_IESPI1_RX_FRAMING_ERROR    V_IESPI1_RX_FRAMING_ERROR(1U)

#घोषणा S_IESPI0_TX_FRAMING_ERROR    13
#घोषणा V_IESPI0_TX_FRAMING_ERROR(x) ((x) << S_IESPI0_TX_FRAMING_ERROR)
#घोषणा F_IESPI0_TX_FRAMING_ERROR    V_IESPI0_TX_FRAMING_ERROR(1U)

#घोषणा S_IESPI1_TX_FRAMING_ERROR    12
#घोषणा V_IESPI1_TX_FRAMING_ERROR(x) ((x) << S_IESPI1_TX_FRAMING_ERROR)
#घोषणा F_IESPI1_TX_FRAMING_ERROR    V_IESPI1_TX_FRAMING_ERROR(1U)

#घोषणा S_OCSPI0_RX_FRAMING_ERROR    11
#घोषणा V_OCSPI0_RX_FRAMING_ERROR(x) ((x) << S_OCSPI0_RX_FRAMING_ERROR)
#घोषणा F_OCSPI0_RX_FRAMING_ERROR    V_OCSPI0_RX_FRAMING_ERROR(1U)

#घोषणा S_OCSPI1_RX_FRAMING_ERROR    10
#घोषणा V_OCSPI1_RX_FRAMING_ERROR(x) ((x) << S_OCSPI1_RX_FRAMING_ERROR)
#घोषणा F_OCSPI1_RX_FRAMING_ERROR    V_OCSPI1_RX_FRAMING_ERROR(1U)

#घोषणा S_OCSPI0_TX_FRAMING_ERROR    9
#घोषणा V_OCSPI0_TX_FRAMING_ERROR(x) ((x) << S_OCSPI0_TX_FRAMING_ERROR)
#घोषणा F_OCSPI0_TX_FRAMING_ERROR    V_OCSPI0_TX_FRAMING_ERROR(1U)

#घोषणा S_OCSPI1_TX_FRAMING_ERROR    8
#घोषणा V_OCSPI1_TX_FRAMING_ERROR(x) ((x) << S_OCSPI1_TX_FRAMING_ERROR)
#घोषणा F_OCSPI1_TX_FRAMING_ERROR    V_OCSPI1_TX_FRAMING_ERROR(1U)

#घोषणा S_OCSPI0_OFIFO2X_TX_FRAMING_ERROR    7
#घोषणा V_OCSPI0_OFIFO2X_TX_FRAMING_ERROR(x) ((x) << S_OCSPI0_OFIFO2X_TX_FRAMING_ERROR)
#घोषणा F_OCSPI0_OFIFO2X_TX_FRAMING_ERROR    V_OCSPI0_OFIFO2X_TX_FRAMING_ERROR(1U)

#घोषणा S_OCSPI1_OFIFO2X_TX_FRAMING_ERROR    6
#घोषणा V_OCSPI1_OFIFO2X_TX_FRAMING_ERROR(x) ((x) << S_OCSPI1_OFIFO2X_TX_FRAMING_ERROR)
#घोषणा F_OCSPI1_OFIFO2X_TX_FRAMING_ERROR    V_OCSPI1_OFIFO2X_TX_FRAMING_ERROR(1U)

#घोषणा S_IESPI_PAR_ERROR    3
#घोषणा M_IESPI_PAR_ERROR    0x7

#घोषणा V_IESPI_PAR_ERROR(x) ((x) << S_IESPI_PAR_ERROR)

#घोषणा S_OCSPI_PAR_ERROR    0
#घोषणा M_OCSPI_PAR_ERROR    0x7

#घोषणा V_OCSPI_PAR_ERROR(x) ((x) << S_OCSPI_PAR_ERROR)

#घोषणा A_PM1_RX_INT_CAUSE 0x5dc

#घोषणा A_PM1_TX_CFG 0x5e0
#घोषणा A_PM1_TX_MODE 0x5e4

#घोषणा A_PM1_TX_INT_ENABLE 0x5f8

#घोषणा S_ZERO_C_CMD_ERROR    18
#घोषणा V_ZERO_C_CMD_ERROR(x) ((x) << S_ZERO_C_CMD_ERROR)
#घोषणा F_ZERO_C_CMD_ERROR    V_ZERO_C_CMD_ERROR(1U)

#घोषणा S_ICSPI0_FIFO2X_RX_FRAMING_ERROR    17
#घोषणा V_ICSPI0_FIFO2X_RX_FRAMING_ERROR(x) ((x) << S_ICSPI0_FIFO2X_RX_FRAMING_ERROR)
#घोषणा F_ICSPI0_FIFO2X_RX_FRAMING_ERROR    V_ICSPI0_FIFO2X_RX_FRAMING_ERROR(1U)

#घोषणा S_ICSPI1_FIFO2X_RX_FRAMING_ERROR    16
#घोषणा V_ICSPI1_FIFO2X_RX_FRAMING_ERROR(x) ((x) << S_ICSPI1_FIFO2X_RX_FRAMING_ERROR)
#घोषणा F_ICSPI1_FIFO2X_RX_FRAMING_ERROR    V_ICSPI1_FIFO2X_RX_FRAMING_ERROR(1U)

#घोषणा S_ICSPI0_RX_FRAMING_ERROR    15
#घोषणा V_ICSPI0_RX_FRAMING_ERROR(x) ((x) << S_ICSPI0_RX_FRAMING_ERROR)
#घोषणा F_ICSPI0_RX_FRAMING_ERROR    V_ICSPI0_RX_FRAMING_ERROR(1U)

#घोषणा S_ICSPI1_RX_FRAMING_ERROR    14
#घोषणा V_ICSPI1_RX_FRAMING_ERROR(x) ((x) << S_ICSPI1_RX_FRAMING_ERROR)
#घोषणा F_ICSPI1_RX_FRAMING_ERROR    V_ICSPI1_RX_FRAMING_ERROR(1U)

#घोषणा S_ICSPI0_TX_FRAMING_ERROR    13
#घोषणा V_ICSPI0_TX_FRAMING_ERROR(x) ((x) << S_ICSPI0_TX_FRAMING_ERROR)
#घोषणा F_ICSPI0_TX_FRAMING_ERROR    V_ICSPI0_TX_FRAMING_ERROR(1U)

#घोषणा S_ICSPI1_TX_FRAMING_ERROR    12
#घोषणा V_ICSPI1_TX_FRAMING_ERROR(x) ((x) << S_ICSPI1_TX_FRAMING_ERROR)
#घोषणा F_ICSPI1_TX_FRAMING_ERROR    V_ICSPI1_TX_FRAMING_ERROR(1U)

#घोषणा S_OESPI0_RX_FRAMING_ERROR    11
#घोषणा V_OESPI0_RX_FRAMING_ERROR(x) ((x) << S_OESPI0_RX_FRAMING_ERROR)
#घोषणा F_OESPI0_RX_FRAMING_ERROR    V_OESPI0_RX_FRAMING_ERROR(1U)

#घोषणा S_OESPI1_RX_FRAMING_ERROR    10
#घोषणा V_OESPI1_RX_FRAMING_ERROR(x) ((x) << S_OESPI1_RX_FRAMING_ERROR)
#घोषणा F_OESPI1_RX_FRAMING_ERROR    V_OESPI1_RX_FRAMING_ERROR(1U)

#घोषणा S_OESPI0_TX_FRAMING_ERROR    9
#घोषणा V_OESPI0_TX_FRAMING_ERROR(x) ((x) << S_OESPI0_TX_FRAMING_ERROR)
#घोषणा F_OESPI0_TX_FRAMING_ERROR    V_OESPI0_TX_FRAMING_ERROR(1U)

#घोषणा S_OESPI1_TX_FRAMING_ERROR    8
#घोषणा V_OESPI1_TX_FRAMING_ERROR(x) ((x) << S_OESPI1_TX_FRAMING_ERROR)
#घोषणा F_OESPI1_TX_FRAMING_ERROR    V_OESPI1_TX_FRAMING_ERROR(1U)

#घोषणा S_OESPI0_OFIFO2X_TX_FRAMING_ERROR    7
#घोषणा V_OESPI0_OFIFO2X_TX_FRAMING_ERROR(x) ((x) << S_OESPI0_OFIFO2X_TX_FRAMING_ERROR)
#घोषणा F_OESPI0_OFIFO2X_TX_FRAMING_ERROR    V_OESPI0_OFIFO2X_TX_FRAMING_ERROR(1U)

#घोषणा S_OESPI1_OFIFO2X_TX_FRAMING_ERROR    6
#घोषणा V_OESPI1_OFIFO2X_TX_FRAMING_ERROR(x) ((x) << S_OESPI1_OFIFO2X_TX_FRAMING_ERROR)
#घोषणा F_OESPI1_OFIFO2X_TX_FRAMING_ERROR    V_OESPI1_OFIFO2X_TX_FRAMING_ERROR(1U)

#घोषणा S_ICSPI_PAR_ERROR    3
#घोषणा M_ICSPI_PAR_ERROR    0x7

#घोषणा V_ICSPI_PAR_ERROR(x) ((x) << S_ICSPI_PAR_ERROR)

#घोषणा S_OESPI_PAR_ERROR    0
#घोषणा M_OESPI_PAR_ERROR    0x7

#घोषणा V_OESPI_PAR_ERROR(x) ((x) << S_OESPI_PAR_ERROR)

#घोषणा A_PM1_TX_INT_CAUSE 0x5fc

#घोषणा A_MPS_CFG 0x600

#घोषणा S_TPRXPORTEN    4
#घोषणा V_TPRXPORTEN(x) ((x) << S_TPRXPORTEN)
#घोषणा F_TPRXPORTEN    V_TPRXPORTEN(1U)

#घोषणा S_TPTXPORT1EN    3
#घोषणा V_TPTXPORT1EN(x) ((x) << S_TPTXPORT1EN)
#घोषणा F_TPTXPORT1EN    V_TPTXPORT1EN(1U)

#घोषणा S_TPTXPORT0EN    2
#घोषणा V_TPTXPORT0EN(x) ((x) << S_TPTXPORT0EN)
#घोषणा F_TPTXPORT0EN    V_TPTXPORT0EN(1U)

#घोषणा S_PORT1ACTIVE    1
#घोषणा V_PORT1ACTIVE(x) ((x) << S_PORT1ACTIVE)
#घोषणा F_PORT1ACTIVE    V_PORT1ACTIVE(1U)

#घोषणा S_PORT0ACTIVE    0
#घोषणा V_PORT0ACTIVE(x) ((x) << S_PORT0ACTIVE)
#घोषणा F_PORT0ACTIVE    V_PORT0ACTIVE(1U)

#घोषणा S_ENFORCEPKT    11
#घोषणा V_ENFORCEPKT(x) ((x) << S_ENFORCEPKT)
#घोषणा F_ENFORCEPKT    V_ENFORCEPKT(1U)

#घोषणा A_MPS_INT_ENABLE 0x61c

#घोषणा S_MCAPARERRENB    6
#घोषणा M_MCAPARERRENB    0x7

#घोषणा V_MCAPARERRENB(x) ((x) << S_MCAPARERRENB)

#घोषणा S_RXTPPARERRENB    4
#घोषणा M_RXTPPARERRENB    0x3

#घोषणा V_RXTPPARERRENB(x) ((x) << S_RXTPPARERRENB)

#घोषणा S_TX1TPPARERRENB    2
#घोषणा M_TX1TPPARERRENB    0x3

#घोषणा V_TX1TPPARERRENB(x) ((x) << S_TX1TPPARERRENB)

#घोषणा S_TX0TPPARERRENB    0
#घोषणा M_TX0TPPARERRENB    0x3

#घोषणा V_TX0TPPARERRENB(x) ((x) << S_TX0TPPARERRENB)

#घोषणा A_MPS_INT_CAUSE 0x620

#घोषणा S_MCAPARERR    6
#घोषणा M_MCAPARERR    0x7

#घोषणा V_MCAPARERR(x) ((x) << S_MCAPARERR)

#घोषणा S_RXTPPARERR    4
#घोषणा M_RXTPPARERR    0x3

#घोषणा V_RXTPPARERR(x) ((x) << S_RXTPPARERR)

#घोषणा S_TX1TPPARERR    2
#घोषणा M_TX1TPPARERR    0x3

#घोषणा V_TX1TPPARERR(x) ((x) << S_TX1TPPARERR)

#घोषणा S_TX0TPPARERR    0
#घोषणा M_TX0TPPARERR    0x3

#घोषणा V_TX0TPPARERR(x) ((x) << S_TX0TPPARERR)

#घोषणा A_CPL_SWITCH_CNTRL 0x640

#घोषणा A_CPL_INTR_ENABLE 0x650

#घोषणा S_CIM_OP_MAP_PERR    5
#घोषणा V_CIM_OP_MAP_PERR(x) ((x) << S_CIM_OP_MAP_PERR)
#घोषणा F_CIM_OP_MAP_PERR    V_CIM_OP_MAP_PERR(1U)

#घोषणा S_CIM_OVFL_ERROR    4
#घोषणा V_CIM_OVFL_ERROR(x) ((x) << S_CIM_OVFL_ERROR)
#घोषणा F_CIM_OVFL_ERROR    V_CIM_OVFL_ERROR(1U)

#घोषणा S_TP_FRAMING_ERROR    3
#घोषणा V_TP_FRAMING_ERROR(x) ((x) << S_TP_FRAMING_ERROR)
#घोषणा F_TP_FRAMING_ERROR    V_TP_FRAMING_ERROR(1U)

#घोषणा S_SGE_FRAMING_ERROR    2
#घोषणा V_SGE_FRAMING_ERROR(x) ((x) << S_SGE_FRAMING_ERROR)
#घोषणा F_SGE_FRAMING_ERROR    V_SGE_FRAMING_ERROR(1U)

#घोषणा S_CIM_FRAMING_ERROR    1
#घोषणा V_CIM_FRAMING_ERROR(x) ((x) << S_CIM_FRAMING_ERROR)
#घोषणा F_CIM_FRAMING_ERROR    V_CIM_FRAMING_ERROR(1U)

#घोषणा S_ZERO_SWITCH_ERROR    0
#घोषणा V_ZERO_SWITCH_ERROR(x) ((x) << S_ZERO_SWITCH_ERROR)
#घोषणा F_ZERO_SWITCH_ERROR    V_ZERO_SWITCH_ERROR(1U)

#घोषणा A_CPL_INTR_CAUSE 0x654

#घोषणा A_CPL_MAP_TBL_DATA 0x65c

#घोषणा A_SMB_GLOBAL_TIME_CFG 0x660

#घोषणा A_I2C_CFG 0x6a0

#घोषणा S_I2C_CLKDIV    0
#घोषणा M_I2C_CLKDIV    0xfff
#घोषणा V_I2C_CLKDIV(x) ((x) << S_I2C_CLKDIV)

#घोषणा A_MI1_CFG 0x6b0

#घोषणा S_CLKDIV    5
#घोषणा M_CLKDIV    0xff
#घोषणा V_CLKDIV(x) ((x) << S_CLKDIV)

#घोषणा S_ST    3

#घोषणा M_ST    0x3

#घोषणा V_ST(x) ((x) << S_ST)

#घोषणा G_ST(x) (((x) >> S_ST) & M_ST)

#घोषणा S_PREEN    2
#घोषणा V_PREEN(x) ((x) << S_PREEN)
#घोषणा F_PREEN    V_PREEN(1U)

#घोषणा S_MDIINV    1
#घोषणा V_MDIINV(x) ((x) << S_MDIINV)
#घोषणा F_MDIINV    V_MDIINV(1U)

#घोषणा S_MDIEN    0
#घोषणा V_MDIEN(x) ((x) << S_MDIEN)
#घोषणा F_MDIEN    V_MDIEN(1U)

#घोषणा A_MI1_ADDR 0x6b4

#घोषणा S_PHYADDR    5
#घोषणा M_PHYADDR    0x1f
#घोषणा V_PHYADDR(x) ((x) << S_PHYADDR)

#घोषणा S_REGADDR    0
#घोषणा M_REGADDR    0x1f
#घोषणा V_REGADDR(x) ((x) << S_REGADDR)

#घोषणा A_MI1_DATA 0x6b8

#घोषणा A_MI1_OP 0x6bc

#घोषणा S_MDI_OP    0
#घोषणा M_MDI_OP    0x3
#घोषणा V_MDI_OP(x) ((x) << S_MDI_OP)

#घोषणा A_SF_DATA 0x6d8

#घोषणा A_SF_OP 0x6dc

#घोषणा S_BYTECNT    1
#घोषणा M_BYTECNT    0x3
#घोषणा V_BYTECNT(x) ((x) << S_BYTECNT)

#घोषणा A_PL_INT_ENABLE0 0x6e0

#घोषणा S_T3DBG    23
#घोषणा V_T3DBG(x) ((x) << S_T3DBG)
#घोषणा F_T3DBG    V_T3DBG(1U)

#घोषणा S_XGMAC0_1    20
#घोषणा V_XGMAC0_1(x) ((x) << S_XGMAC0_1)
#घोषणा F_XGMAC0_1    V_XGMAC0_1(1U)

#घोषणा S_XGMAC0_0    19
#घोषणा V_XGMAC0_0(x) ((x) << S_XGMAC0_0)
#घोषणा F_XGMAC0_0    V_XGMAC0_0(1U)

#घोषणा S_MC5A    18
#घोषणा V_MC5A(x) ((x) << S_MC5A)
#घोषणा F_MC5A    V_MC5A(1U)

#घोषणा S_CPL_SWITCH    12
#घोषणा V_CPL_SWITCH(x) ((x) << S_CPL_SWITCH)
#घोषणा F_CPL_SWITCH    V_CPL_SWITCH(1U)

#घोषणा S_MPS0    11
#घोषणा V_MPS0(x) ((x) << S_MPS0)
#घोषणा F_MPS0    V_MPS0(1U)

#घोषणा S_PM1_TX    10
#घोषणा V_PM1_TX(x) ((x) << S_PM1_TX)
#घोषणा F_PM1_TX    V_PM1_TX(1U)

#घोषणा S_PM1_RX    9
#घोषणा V_PM1_RX(x) ((x) << S_PM1_RX)
#घोषणा F_PM1_RX    V_PM1_RX(1U)

#घोषणा S_ULP2_TX    8
#घोषणा V_ULP2_TX(x) ((x) << S_ULP2_TX)
#घोषणा F_ULP2_TX    V_ULP2_TX(1U)

#घोषणा S_ULP2_RX    7
#घोषणा V_ULP2_RX(x) ((x) << S_ULP2_RX)
#घोषणा F_ULP2_RX    V_ULP2_RX(1U)

#घोषणा S_TP1    6
#घोषणा V_TP1(x) ((x) << S_TP1)
#घोषणा F_TP1    V_TP1(1U)

#घोषणा S_CIM    5
#घोषणा V_CIM(x) ((x) << S_CIM)
#घोषणा F_CIM    V_CIM(1U)

#घोषणा S_MC7_CM    4
#घोषणा V_MC7_CM(x) ((x) << S_MC7_CM)
#घोषणा F_MC7_CM    V_MC7_CM(1U)

#घोषणा S_MC7_PMTX    3
#घोषणा V_MC7_PMTX(x) ((x) << S_MC7_PMTX)
#घोषणा F_MC7_PMTX    V_MC7_PMTX(1U)

#घोषणा S_MC7_PMRX    2
#घोषणा V_MC7_PMRX(x) ((x) << S_MC7_PMRX)
#घोषणा F_MC7_PMRX    V_MC7_PMRX(1U)

#घोषणा S_PCIM0    1
#घोषणा V_PCIM0(x) ((x) << S_PCIM0)
#घोषणा F_PCIM0    V_PCIM0(1U)

#घोषणा S_SGE3    0
#घोषणा V_SGE3(x) ((x) << S_SGE3)
#घोषणा F_SGE3    V_SGE3(1U)

#घोषणा A_PL_INT_CAUSE0 0x6e4

#घोषणा A_PL_RST 0x6f0

#घोषणा S_FATALPERREN    4
#घोषणा V_FATALPERREN(x) ((x) << S_FATALPERREN)
#घोषणा F_FATALPERREN    V_FATALPERREN(1U)

#घोषणा S_CRSTWRM    1
#घोषणा V_CRSTWRM(x) ((x) << S_CRSTWRM)
#घोषणा F_CRSTWRM    V_CRSTWRM(1U)

#घोषणा A_PL_REV 0x6f4

#घोषणा A_PL_CLI 0x6f8

#घोषणा A_MC5_DB_CONFIG 0x704

#घोषणा S_TMTYPEHI    30
#घोषणा V_TMTYPEHI(x) ((x) << S_TMTYPEHI)
#घोषणा F_TMTYPEHI    V_TMTYPEHI(1U)

#घोषणा S_TMPARTSIZE    28
#घोषणा M_TMPARTSIZE    0x3
#घोषणा V_TMPARTSIZE(x) ((x) << S_TMPARTSIZE)
#घोषणा G_TMPARTSIZE(x) (((x) >> S_TMPARTSIZE) & M_TMPARTSIZE)

#घोषणा S_TMTYPE    26
#घोषणा M_TMTYPE    0x3
#घोषणा V_TMTYPE(x) ((x) << S_TMTYPE)
#घोषणा G_TMTYPE(x) (((x) >> S_TMTYPE) & M_TMTYPE)

#घोषणा S_COMPEN    17
#घोषणा V_COMPEN(x) ((x) << S_COMPEN)
#घोषणा F_COMPEN    V_COMPEN(1U)

#घोषणा S_PRTYEN    6
#घोषणा V_PRTYEN(x) ((x) << S_PRTYEN)
#घोषणा F_PRTYEN    V_PRTYEN(1U)

#घोषणा S_MBUSEN    5
#घोषणा V_MBUSEN(x) ((x) << S_MBUSEN)
#घोषणा F_MBUSEN    V_MBUSEN(1U)

#घोषणा S_DBGIEN    4
#घोषणा V_DBGIEN(x) ((x) << S_DBGIEN)
#घोषणा F_DBGIEN    V_DBGIEN(1U)

#घोषणा S_TMRDY    2
#घोषणा V_TMRDY(x) ((x) << S_TMRDY)
#घोषणा F_TMRDY    V_TMRDY(1U)

#घोषणा S_TMRST    1
#घोषणा V_TMRST(x) ((x) << S_TMRST)
#घोषणा F_TMRST    V_TMRST(1U)

#घोषणा S_TMMODE    0
#घोषणा V_TMMODE(x) ((x) << S_TMMODE)
#घोषणा F_TMMODE    V_TMMODE(1U)

#घोषणा A_MC5_DB_ROUTING_TABLE_INDEX 0x70c

#घोषणा A_MC5_DB_FILTER_TABLE 0x710

#घोषणा A_MC5_DB_SERVER_INDEX 0x714

#घोषणा A_MC5_DB_RSP_LATENCY 0x720

#घोषणा S_RDLAT    16
#घोषणा M_RDLAT    0x1f
#घोषणा V_RDLAT(x) ((x) << S_RDLAT)

#घोषणा S_LRNLAT    8
#घोषणा M_LRNLAT    0x1f
#घोषणा V_LRNLAT(x) ((x) << S_LRNLAT)

#घोषणा S_SRCHLAT    0
#घोषणा M_SRCHLAT    0x1f
#घोषणा V_SRCHLAT(x) ((x) << S_SRCHLAT)

#घोषणा A_MC5_DB_PART_ID_INDEX 0x72c

#घोषणा A_MC5_DB_INT_ENABLE 0x740

#घोषणा S_DELACTEMPTY    18
#घोषणा V_DELACTEMPTY(x) ((x) << S_DELACTEMPTY)
#घोषणा F_DELACTEMPTY    V_DELACTEMPTY(1U)

#घोषणा S_DISPQPARERR    17
#घोषणा V_DISPQPARERR(x) ((x) << S_DISPQPARERR)
#घोषणा F_DISPQPARERR    V_DISPQPARERR(1U)

#घोषणा S_REQQPARERR    16
#घोषणा V_REQQPARERR(x) ((x) << S_REQQPARERR)
#घोषणा F_REQQPARERR    V_REQQPARERR(1U)

#घोषणा S_UNKNOWNCMD    15
#घोषणा V_UNKNOWNCMD(x) ((x) << S_UNKNOWNCMD)
#घोषणा F_UNKNOWNCMD    V_UNKNOWNCMD(1U)

#घोषणा S_NFASRCHFAIL    8
#घोषणा V_NFASRCHFAIL(x) ((x) << S_NFASRCHFAIL)
#घोषणा F_NFASRCHFAIL    V_NFASRCHFAIL(1U)

#घोषणा S_ACTRGNFULL    7
#घोषणा V_ACTRGNFULL(x) ((x) << S_ACTRGNFULL)
#घोषणा F_ACTRGNFULL    V_ACTRGNFULL(1U)

#घोषणा S_PARITYERR    6
#घोषणा V_PARITYERR(x) ((x) << S_PARITYERR)
#घोषणा F_PARITYERR    V_PARITYERR(1U)

#घोषणा A_MC5_DB_INT_CAUSE 0x744

#घोषणा A_MC5_DB_DBGI_CONFIG 0x774

#घोषणा A_MC5_DB_DBGI_REQ_CMD 0x778

#घोषणा A_MC5_DB_DBGI_REQ_ADDR0 0x77c

#घोषणा A_MC5_DB_DBGI_REQ_ADDR1 0x780

#घोषणा A_MC5_DB_DBGI_REQ_ADDR2 0x784

#घोषणा A_MC5_DB_DBGI_REQ_DATA0 0x788

#घोषणा A_MC5_DB_DBGI_REQ_DATA1 0x78c

#घोषणा A_MC5_DB_DBGI_REQ_DATA2 0x790

#घोषणा A_MC5_DB_DBGI_RSP_STATUS 0x7b0

#घोषणा S_DBGIRSPVALID    0
#घोषणा V_DBGIRSPVALID(x) ((x) << S_DBGIRSPVALID)
#घोषणा F_DBGIRSPVALID    V_DBGIRSPVALID(1U)

#घोषणा A_MC5_DB_DBGI_RSP_DATA0 0x7b4

#घोषणा A_MC5_DB_DBGI_RSP_DATA1 0x7b8

#घोषणा A_MC5_DB_DBGI_RSP_DATA2 0x7bc

#घोषणा A_MC5_DB_POPEN_DATA_WR_CMD 0x7cc

#घोषणा A_MC5_DB_POPEN_MASK_WR_CMD 0x7d0

#घोषणा A_MC5_DB_AOPEN_SRCH_CMD 0x7d4

#घोषणा A_MC5_DB_AOPEN_LRN_CMD 0x7d8

#घोषणा A_MC5_DB_SYN_SRCH_CMD 0x7dc

#घोषणा A_MC5_DB_SYN_LRN_CMD 0x7e0

#घोषणा A_MC5_DB_ACK_SRCH_CMD 0x7e4

#घोषणा A_MC5_DB_ACK_LRN_CMD 0x7e8

#घोषणा A_MC5_DB_ILOOKUP_CMD 0x7ec

#घोषणा A_MC5_DB_ELOOKUP_CMD 0x7f0

#घोषणा A_MC5_DB_DATA_WRITE_CMD 0x7f4

#घोषणा A_MC5_DB_DATA_READ_CMD 0x7f8

#घोषणा XGMAC0_0_BASE_ADDR 0x800

#घोषणा A_XGM_TX_CTRL 0x800

#घोषणा S_TXEN    0
#घोषणा V_TXEN(x) ((x) << S_TXEN)
#घोषणा F_TXEN    V_TXEN(1U)

#घोषणा A_XGM_TX_CFG 0x804

#घोषणा S_TXPAUSEEN    0
#घोषणा V_TXPAUSEEN(x) ((x) << S_TXPAUSEEN)
#घोषणा F_TXPAUSEEN    V_TXPAUSEEN(1U)

#घोषणा A_XGM_TX_PAUSE_QUANTA 0x808

#घोषणा A_XGM_RX_CTRL 0x80c

#घोषणा S_RXEN    0
#घोषणा V_RXEN(x) ((x) << S_RXEN)
#घोषणा F_RXEN    V_RXEN(1U)

#घोषणा A_XGM_RX_CFG 0x810

#घोषणा S_DISPAUSEFRAMES    9
#घोषणा V_DISPAUSEFRAMES(x) ((x) << S_DISPAUSEFRAMES)
#घोषणा F_DISPAUSEFRAMES    V_DISPAUSEFRAMES(1U)

#घोषणा S_EN1536BFRAMES    8
#घोषणा V_EN1536BFRAMES(x) ((x) << S_EN1536BFRAMES)
#घोषणा F_EN1536BFRAMES    V_EN1536BFRAMES(1U)

#घोषणा S_ENJUMBO    7
#घोषणा V_ENJUMBO(x) ((x) << S_ENJUMBO)
#घोषणा F_ENJUMBO    V_ENJUMBO(1U)

#घोषणा S_RMFCS    6
#घोषणा V_RMFCS(x) ((x) << S_RMFCS)
#घोषणा F_RMFCS    V_RMFCS(1U)

#घोषणा S_ENHASHMCAST    2
#घोषणा V_ENHASHMCAST(x) ((x) << S_ENHASHMCAST)
#घोषणा F_ENHASHMCAST    V_ENHASHMCAST(1U)

#घोषणा S_COPYALLFRAMES    0
#घोषणा V_COPYALLFRAMES(x) ((x) << S_COPYALLFRAMES)
#घोषणा F_COPYALLFRAMES    V_COPYALLFRAMES(1U)

#घोषणा S_DISBCAST    1
#घोषणा V_DISBCAST(x) ((x) << S_DISBCAST)
#घोषणा F_DISBCAST    V_DISBCAST(1U)

#घोषणा A_XGM_RX_HASH_LOW 0x814

#घोषणा A_XGM_RX_HASH_HIGH 0x818

#घोषणा A_XGM_RX_EXACT_MATCH_LOW_1 0x81c

#घोषणा A_XGM_RX_EXACT_MATCH_HIGH_1 0x820

#घोषणा A_XGM_RX_EXACT_MATCH_LOW_2 0x824

#घोषणा A_XGM_RX_EXACT_MATCH_LOW_3 0x82c

#घोषणा A_XGM_RX_EXACT_MATCH_LOW_4 0x834

#घोषणा A_XGM_RX_EXACT_MATCH_LOW_5 0x83c

#घोषणा A_XGM_RX_EXACT_MATCH_LOW_6 0x844

#घोषणा A_XGM_RX_EXACT_MATCH_LOW_7 0x84c

#घोषणा A_XGM_RX_EXACT_MATCH_LOW_8 0x854

#घोषणा A_XGM_INT_STATUS 0x86c

#घोषणा S_LINKFAULTCHANGE    9
#घोषणा V_LINKFAULTCHANGE(x) ((x) << S_LINKFAULTCHANGE)
#घोषणा F_LINKFAULTCHANGE    V_LINKFAULTCHANGE(1U)

#घोषणा A_XGM_XGM_INT_ENABLE 0x874
#घोषणा A_XGM_XGM_INT_DISABLE 0x878

#घोषणा A_XGM_STAT_CTRL 0x880

#घोषणा S_CLRSTATS    2
#घोषणा V_CLRSTATS(x) ((x) << S_CLRSTATS)
#घोषणा F_CLRSTATS    V_CLRSTATS(1U)

#घोषणा A_XGM_RXFIFO_CFG 0x884

#घोषणा S_RXFIFO_EMPTY    31
#घोषणा V_RXFIFO_EMPTY(x) ((x) << S_RXFIFO_EMPTY)
#घोषणा F_RXFIFO_EMPTY    V_RXFIFO_EMPTY(1U)

#घोषणा S_RXFIFOPAUSEHWM    17
#घोषणा M_RXFIFOPAUSEHWM    0xfff

#घोषणा V_RXFIFOPAUSEHWM(x) ((x) << S_RXFIFOPAUSEHWM)

#घोषणा G_RXFIFOPAUSEHWM(x) (((x) >> S_RXFIFOPAUSEHWM) & M_RXFIFOPAUSEHWM)

#घोषणा S_RXFIFOPAUSELWM    5
#घोषणा M_RXFIFOPAUSELWM    0xfff

#घोषणा V_RXFIFOPAUSELWM(x) ((x) << S_RXFIFOPAUSELWM)

#घोषणा G_RXFIFOPAUSELWM(x) (((x) >> S_RXFIFOPAUSELWM) & M_RXFIFOPAUSELWM)

#घोषणा S_RXSTRFRWRD    1
#घोषणा V_RXSTRFRWRD(x) ((x) << S_RXSTRFRWRD)
#घोषणा F_RXSTRFRWRD    V_RXSTRFRWRD(1U)

#घोषणा S_DISERRFRAMES    0
#घोषणा V_DISERRFRAMES(x) ((x) << S_DISERRFRAMES)
#घोषणा F_DISERRFRAMES    V_DISERRFRAMES(1U)

#घोषणा A_XGM_TXFIFO_CFG 0x888

#घोषणा S_UNDERUNFIX    22
#घोषणा V_UNDERUNFIX(x) ((x) << S_UNDERUNFIX)
#घोषणा F_UNDERUNFIX    V_UNDERUNFIX(1U)

#घोषणा S_TXIPG    13
#घोषणा M_TXIPG    0xff
#घोषणा V_TXIPG(x) ((x) << S_TXIPG)
#घोषणा G_TXIPG(x) (((x) >> S_TXIPG) & M_TXIPG)

#घोषणा S_TXFIFOTHRESH    4
#घोषणा M_TXFIFOTHRESH    0x1ff

#घोषणा V_TXFIFOTHRESH(x) ((x) << S_TXFIFOTHRESH)

#घोषणा S_ENDROPPKT    21
#घोषणा V_ENDROPPKT(x) ((x) << S_ENDROPPKT)
#घोषणा F_ENDROPPKT    V_ENDROPPKT(1U)

#घोषणा A_XGM_SERDES_CTRL 0x890
#घोषणा A_XGM_SERDES_CTRL0 0x8e0

#घोषणा S_SERDESRESET_    24
#घोषणा V_SERDESRESET_(x) ((x) << S_SERDESRESET_)
#घोषणा F_SERDESRESET_    V_SERDESRESET_(1U)

#घोषणा S_RXENABLE    4
#घोषणा V_RXENABLE(x) ((x) << S_RXENABLE)
#घोषणा F_RXENABLE    V_RXENABLE(1U)

#घोषणा S_TXENABLE    3
#घोषणा V_TXENABLE(x) ((x) << S_TXENABLE)
#घोषणा F_TXENABLE    V_TXENABLE(1U)

#घोषणा A_XGM_PAUSE_TIMER 0x890

#घोषणा A_XGM_RGMII_IMP 0x89c

#घोषणा S_XGM_IMPSETUPDATE    6
#घोषणा V_XGM_IMPSETUPDATE(x) ((x) << S_XGM_IMPSETUPDATE)
#घोषणा F_XGM_IMPSETUPDATE    V_XGM_IMPSETUPDATE(1U)

#घोषणा S_RGMIIIMPPD    3
#घोषणा M_RGMIIIMPPD    0x7
#घोषणा V_RGMIIIMPPD(x) ((x) << S_RGMIIIMPPD)

#घोषणा S_RGMIIIMPPU    0
#घोषणा M_RGMIIIMPPU    0x7
#घोषणा V_RGMIIIMPPU(x) ((x) << S_RGMIIIMPPU)

#घोषणा S_CALRESET    8
#घोषणा V_CALRESET(x) ((x) << S_CALRESET)
#घोषणा F_CALRESET    V_CALRESET(1U)

#घोषणा S_CALUPDATE    7
#घोषणा V_CALUPDATE(x) ((x) << S_CALUPDATE)
#घोषणा F_CALUPDATE    V_CALUPDATE(1U)

#घोषणा A_XGM_XAUI_IMP 0x8a0

#घोषणा S_CALBUSY    31
#घोषणा V_CALBUSY(x) ((x) << S_CALBUSY)
#घोषणा F_CALBUSY    V_CALBUSY(1U)

#घोषणा S_XGM_CALFAULT    29
#घोषणा V_XGM_CALFAULT(x) ((x) << S_XGM_CALFAULT)
#घोषणा F_XGM_CALFAULT    V_XGM_CALFAULT(1U)

#घोषणा S_CALIMP    24
#घोषणा M_CALIMP    0x1f
#घोषणा V_CALIMP(x) ((x) << S_CALIMP)
#घोषणा G_CALIMP(x) (((x) >> S_CALIMP) & M_CALIMP)

#घोषणा S_XAUIIMP    0
#घोषणा M_XAUIIMP    0x7
#घोषणा V_XAUIIMP(x) ((x) << S_XAUIIMP)

#घोषणा A_XGM_RX_MAX_PKT_SIZE 0x8a8

#घोषणा S_RXMAXFRAMERSIZE    17
#घोषणा M_RXMAXFRAMERSIZE    0x3fff
#घोषणा V_RXMAXFRAMERSIZE(x) ((x) << S_RXMAXFRAMERSIZE)
#घोषणा G_RXMAXFRAMERSIZE(x) (((x) >> S_RXMAXFRAMERSIZE) & M_RXMAXFRAMERSIZE)

#घोषणा S_RXENFRAMER    14
#घोषणा V_RXENFRAMER(x) ((x) << S_RXENFRAMER)
#घोषणा F_RXENFRAMER    V_RXENFRAMER(1U)

#घोषणा S_RXMAXPKTSIZE    0
#घोषणा M_RXMAXPKTSIZE    0x3fff
#घोषणा V_RXMAXPKTSIZE(x) ((x) << S_RXMAXPKTSIZE)
#घोषणा G_RXMAXPKTSIZE(x) (((x) >> S_RXMAXPKTSIZE) & M_RXMAXPKTSIZE)

#घोषणा A_XGM_RESET_CTRL 0x8ac

#घोषणा S_XGMAC_STOP_EN    4
#घोषणा V_XGMAC_STOP_EN(x) ((x) << S_XGMAC_STOP_EN)
#घोषणा F_XGMAC_STOP_EN    V_XGMAC_STOP_EN(1U)

#घोषणा S_XG2G_RESET_    3
#घोषणा V_XG2G_RESET_(x) ((x) << S_XG2G_RESET_)
#घोषणा F_XG2G_RESET_    V_XG2G_RESET_(1U)

#घोषणा S_RGMII_RESET_    2
#घोषणा V_RGMII_RESET_(x) ((x) << S_RGMII_RESET_)
#घोषणा F_RGMII_RESET_    V_RGMII_RESET_(1U)

#घोषणा S_PCS_RESET_    1
#घोषणा V_PCS_RESET_(x) ((x) << S_PCS_RESET_)
#घोषणा F_PCS_RESET_    V_PCS_RESET_(1U)

#घोषणा S_MAC_RESET_    0
#घोषणा V_MAC_RESET_(x) ((x) << S_MAC_RESET_)
#घोषणा F_MAC_RESET_    V_MAC_RESET_(1U)

#घोषणा A_XGM_PORT_CFG 0x8b8

#घोषणा S_CLKDIVRESET_    3
#घोषणा V_CLKDIVRESET_(x) ((x) << S_CLKDIVRESET_)
#घोषणा F_CLKDIVRESET_    V_CLKDIVRESET_(1U)

#घोषणा S_PORTSPEED    1
#घोषणा M_PORTSPEED    0x3

#घोषणा V_PORTSPEED(x) ((x) << S_PORTSPEED)

#घोषणा S_ENRGMII    0
#घोषणा V_ENRGMII(x) ((x) << S_ENRGMII)
#घोषणा F_ENRGMII    V_ENRGMII(1U)

#घोषणा A_XGM_INT_ENABLE 0x8d4

#घोषणा S_TXFIFO_PRTY_ERR    17
#घोषणा M_TXFIFO_PRTY_ERR    0x7

#घोषणा V_TXFIFO_PRTY_ERR(x) ((x) << S_TXFIFO_PRTY_ERR)

#घोषणा S_RXFIFO_PRTY_ERR    14
#घोषणा M_RXFIFO_PRTY_ERR    0x7

#घोषणा V_RXFIFO_PRTY_ERR(x) ((x) << S_RXFIFO_PRTY_ERR)

#घोषणा S_TXFIFO_UNDERRUN    13
#घोषणा V_TXFIFO_UNDERRUN(x) ((x) << S_TXFIFO_UNDERRUN)
#घोषणा F_TXFIFO_UNDERRUN    V_TXFIFO_UNDERRUN(1U)

#घोषणा S_RXFIFO_OVERFLOW    12
#घोषणा V_RXFIFO_OVERFLOW(x) ((x) << S_RXFIFO_OVERFLOW)
#घोषणा F_RXFIFO_OVERFLOW    V_RXFIFO_OVERFLOW(1U)

#घोषणा S_SERDES_LOS    4
#घोषणा M_SERDES_LOS    0xf

#घोषणा V_SERDES_LOS(x) ((x) << S_SERDES_LOS)

#घोषणा S_XAUIPCSCTCERR    3
#घोषणा V_XAUIPCSCTCERR(x) ((x) << S_XAUIPCSCTCERR)
#घोषणा F_XAUIPCSCTCERR    V_XAUIPCSCTCERR(1U)

#घोषणा S_XAUIPCSALIGNCHANGE    2
#घोषणा V_XAUIPCSALIGNCHANGE(x) ((x) << S_XAUIPCSALIGNCHANGE)
#घोषणा F_XAUIPCSALIGNCHANGE    V_XAUIPCSALIGNCHANGE(1U)

#घोषणा S_XGM_INT    0
#घोषणा V_XGM_INT(x) ((x) << S_XGM_INT)
#घोषणा F_XGM_INT    V_XGM_INT(1U)

#घोषणा A_XGM_INT_CAUSE 0x8d8

#घोषणा A_XGM_XAUI_ACT_CTRL 0x8dc

#घोषणा S_TXACTENABLE    1
#घोषणा V_TXACTENABLE(x) ((x) << S_TXACTENABLE)
#घोषणा F_TXACTENABLE    V_TXACTENABLE(1U)

#घोषणा S_RESET3    23
#घोषणा V_RESET3(x) ((x) << S_RESET3)
#घोषणा F_RESET3    V_RESET3(1U)

#घोषणा S_RESET2    22
#घोषणा V_RESET2(x) ((x) << S_RESET2)
#घोषणा F_RESET2    V_RESET2(1U)

#घोषणा S_RESET1    21
#घोषणा V_RESET1(x) ((x) << S_RESET1)
#घोषणा F_RESET1    V_RESET1(1U)

#घोषणा S_RESET0    20
#घोषणा V_RESET0(x) ((x) << S_RESET0)
#घोषणा F_RESET0    V_RESET0(1U)

#घोषणा S_PWRDN3    19
#घोषणा V_PWRDN3(x) ((x) << S_PWRDN3)
#घोषणा F_PWRDN3    V_PWRDN3(1U)

#घोषणा S_PWRDN2    18
#घोषणा V_PWRDN2(x) ((x) << S_PWRDN2)
#घोषणा F_PWRDN2    V_PWRDN2(1U)

#घोषणा S_PWRDN1    17
#घोषणा V_PWRDN1(x) ((x) << S_PWRDN1)
#घोषणा F_PWRDN1    V_PWRDN1(1U)

#घोषणा S_PWRDN0    16
#घोषणा V_PWRDN0(x) ((x) << S_PWRDN0)
#घोषणा F_PWRDN0    V_PWRDN0(1U)

#घोषणा S_RESETPLL23    15
#घोषणा V_RESETPLL23(x) ((x) << S_RESETPLL23)
#घोषणा F_RESETPLL23    V_RESETPLL23(1U)

#घोषणा S_RESETPLL01    14
#घोषणा V_RESETPLL01(x) ((x) << S_RESETPLL01)
#घोषणा F_RESETPLL01    V_RESETPLL01(1U)

#घोषणा A_XGM_SERDES_STAT0 0x8f0
#घोषणा A_XGM_SERDES_STAT1 0x8f4
#घोषणा A_XGM_SERDES_STAT2 0x8f8

#घोषणा S_LOWSIG0    0
#घोषणा V_LOWSIG0(x) ((x) << S_LOWSIG0)
#घोषणा F_LOWSIG0    V_LOWSIG0(1U)

#घोषणा A_XGM_SERDES_STAT3 0x8fc

#घोषणा A_XGM_STAT_TX_BYTE_LOW 0x900

#घोषणा A_XGM_STAT_TX_BYTE_HIGH 0x904

#घोषणा A_XGM_STAT_TX_FRAME_LOW 0x908

#घोषणा A_XGM_STAT_TX_FRAME_HIGH 0x90c

#घोषणा A_XGM_STAT_TX_BCAST 0x910

#घोषणा A_XGM_STAT_TX_MCAST 0x914

#घोषणा A_XGM_STAT_TX_PAUSE 0x918

#घोषणा A_XGM_STAT_TX_64B_FRAMES 0x91c

#घोषणा A_XGM_STAT_TX_65_127B_FRAMES 0x920

#घोषणा A_XGM_STAT_TX_128_255B_FRAMES 0x924

#घोषणा A_XGM_STAT_TX_256_511B_FRAMES 0x928

#घोषणा A_XGM_STAT_TX_512_1023B_FRAMES 0x92c

#घोषणा A_XGM_STAT_TX_1024_1518B_FRAMES 0x930

#घोषणा A_XGM_STAT_TX_1519_MAXB_FRAMES 0x934

#घोषणा A_XGM_STAT_TX_ERR_FRAMES 0x938

#घोषणा A_XGM_STAT_RX_BYTES_LOW 0x93c

#घोषणा A_XGM_STAT_RX_BYTES_HIGH 0x940

#घोषणा A_XGM_STAT_RX_FRAMES_LOW 0x944

#घोषणा A_XGM_STAT_RX_FRAMES_HIGH 0x948

#घोषणा A_XGM_STAT_RX_BCAST_FRAMES 0x94c

#घोषणा A_XGM_STAT_RX_MCAST_FRAMES 0x950

#घोषणा A_XGM_STAT_RX_PAUSE_FRAMES 0x954

#घोषणा A_XGM_STAT_RX_64B_FRAMES 0x958

#घोषणा A_XGM_STAT_RX_65_127B_FRAMES 0x95c

#घोषणा A_XGM_STAT_RX_128_255B_FRAMES 0x960

#घोषणा A_XGM_STAT_RX_256_511B_FRAMES 0x964

#घोषणा A_XGM_STAT_RX_512_1023B_FRAMES 0x968

#घोषणा A_XGM_STAT_RX_1024_1518B_FRAMES 0x96c

#घोषणा A_XGM_STAT_RX_1519_MAXB_FRAMES 0x970

#घोषणा A_XGM_STAT_RX_SHORT_FRAMES 0x974

#घोषणा A_XGM_STAT_RX_OVERSIZE_FRAMES 0x978

#घोषणा A_XGM_STAT_RX_JABBER_FRAMES 0x97c

#घोषणा A_XGM_STAT_RX_CRC_ERR_FRAMES 0x980

#घोषणा A_XGM_STAT_RX_LENGTH_ERR_FRAMES 0x984

#घोषणा A_XGM_STAT_RX_SYM_CODE_ERR_FRAMES 0x988

#घोषणा A_XGM_SERDES_STATUS0 0x98c

#घोषणा A_XGM_SERDES_STATUS1 0x990

#घोषणा S_CMULOCK    31
#घोषणा V_CMULOCK(x) ((x) << S_CMULOCK)
#घोषणा F_CMULOCK    V_CMULOCK(1U)

#घोषणा A_XGM_RX_MAX_PKT_SIZE_ERR_CNT 0x9a4

#घोषणा A_XGM_TX_SPI4_SOP_EOP_CNT 0x9a8

#घोषणा S_TXSPI4SOPCNT    16
#घोषणा M_TXSPI4SOPCNT    0xffff
#घोषणा V_TXSPI4SOPCNT(x) ((x) << S_TXSPI4SOPCNT)
#घोषणा G_TXSPI4SOPCNT(x) (((x) >> S_TXSPI4SOPCNT) & M_TXSPI4SOPCNT)

#घोषणा A_XGM_RX_SPI4_SOP_EOP_CNT 0x9ac

#घोषणा XGMAC0_1_BASE_ADDR 0xa00
