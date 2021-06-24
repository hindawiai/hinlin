<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aic94xx SAS/SATA driver dump पूर्णांकerface.
 *
 * Copyright (C) 2004 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2004 David Chaw <david_chaw@adaptec.com>
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 *
 * 2005/07/14/LT  Complete overhaul of this file.  Update pages, रेजिस्टर
 * locations, names, etc.  Make use of macros.  Prपूर्णांक more inक्रमmation.
 * Prपूर्णांक all cseq and lseq mip and mdp.
 */

#समावेश <linux/pci.h>
#समावेश "aic94xx.h"
#समावेश "aic94xx_reg.h"
#समावेश "aic94xx_reg_def.h"
#समावेश "aic94xx_sas.h"

#समावेश "aic94xx_dump.h"

#अगर_घोषित ASD_DEBUG

#घोषणा MD(x)	    (1 << (x))
#घोषणा MODE_COMMON (1 << 31)
#घोषणा MODE_0_7    (0xFF)

अटल स्थिर काष्ठा lseq_cio_regs अणु
	अक्षर	*name;
	u32	offs;
	u8	width;
	u32	mode;
पूर्ण LSEQmCIOREGS[] = अणु
	अणु"LmMnSCBPTR",    0x20, 16, MD(0)|MD(1)|MD(2)|MD(3)|MD(4) पूर्ण,
	अणु"LmMnDDBPTR",    0x22, 16, MD(0)|MD(1)|MD(2)|MD(3)|MD(4) पूर्ण,
	अणु"LmREQMBX",      0x30, 32, MODE_COMMON पूर्ण,
	अणु"LmRSPMBX",      0x34, 32, MODE_COMMON पूर्ण,
	अणु"LmMnINT",       0x38, 32, MODE_0_7 पूर्ण,
	अणु"LmMnINTEN",     0x3C, 32, MODE_0_7 पूर्ण,
	अणु"LmXMTPRIMD",    0x40, 32, MODE_COMMON पूर्ण,
	अणु"LmXMTPRIMCS",   0x44,  8, MODE_COMMON पूर्ण,
	अणु"LmCONSTAT",     0x45,  8, MODE_COMMON पूर्ण,
	अणु"LmMnDMAERRS",   0x46,  8, MD(0)|MD(1) पूर्ण,
	अणु"LmMnSGDMAERRS", 0x47,  8, MD(0)|MD(1) पूर्ण,
	अणु"LmMnEXPHDRP",   0x48,  8, MD(0) पूर्ण,
	अणु"LmMnSASAALIGN", 0x48,  8, MD(1) पूर्ण,
	अणु"LmMnMSKHDRP",   0x49,  8, MD(0) पूर्ण,
	अणु"LmMnSTPALIGN",  0x49,  8, MD(1) पूर्ण,
	अणु"LmMnRCVHDRP",   0x4A,  8, MD(0) पूर्ण,
	अणु"LmMnXMTHDRP",   0x4A,  8, MD(1) पूर्ण,
	अणु"LmALIGNMODE",   0x4B,  8, MD(1) पूर्ण,
	अणु"LmMnEXPRCVCNT", 0x4C, 32, MD(0) पूर्ण,
	अणु"LmMnXMTCNT",    0x4C, 32, MD(1) पूर्ण,
	अणु"LmMnCURRTAG",   0x54, 16, MD(0) पूर्ण,
	अणु"LmMnPREVTAG",   0x56, 16, MD(0) पूर्ण,
	अणु"LmMnACKOFS",    0x58,  8, MD(1) पूर्ण,
	अणु"LmMnXFRLVL",    0x59,  8, MD(0)|MD(1) पूर्ण,
	अणु"LmMnSGDMACTL",  0x5A,  8, MD(0)|MD(1) पूर्ण,
	अणु"LmMnSGDMASTAT", 0x5B,  8, MD(0)|MD(1) पूर्ण,
	अणु"LmMnDDMACTL",   0x5C,  8, MD(0)|MD(1) पूर्ण,
	अणु"LmMnDDMASTAT",  0x5D,  8, MD(0)|MD(1) पूर्ण,
	अणु"LmMnDDMAMODE",  0x5E, 16, MD(0)|MD(1) पूर्ण,
	अणु"LmMnPIPECTL",   0x61,  8, MD(0)|MD(1) पूर्ण,
	अणु"LmMnACTSCB",    0x62, 16, MD(0)|MD(1) पूर्ण,
	अणु"LmMnSGBHADR",   0x64,  8, MD(0)|MD(1) पूर्ण,
	अणु"LmMnSGBADR",    0x65,  8, MD(0)|MD(1) पूर्ण,
	अणु"LmMnSGDCNT",    0x66,  8, MD(0)|MD(1) पूर्ण,
	अणु"LmMnSGDMADR",   0x68, 32, MD(0)|MD(1) पूर्ण,
	अणु"LmMnSGDMADR",   0x6C, 32, MD(0)|MD(1) पूर्ण,
	अणु"LmMnXFRCNT",    0x70, 32, MD(0)|MD(1) पूर्ण,
	अणु"LmMnXMTCRC",    0x74, 32, MD(1) पूर्ण,
	अणु"LmCURRTAG",     0x74, 16, MD(0) पूर्ण,
	अणु"LmPREVTAG",     0x76, 16, MD(0) पूर्ण,
	अणु"LmMnDPSEL",     0x7B,  8, MD(0)|MD(1) पूर्ण,
	अणु"LmDPTHSTAT",    0x7C,  8, MODE_COMMON पूर्ण,
	अणु"LmMnHOLDLVL",   0x7D,  8, MD(0) पूर्ण,
	अणु"LmMnSATAFS",    0x7E,  8, MD(1) पूर्ण,
	अणु"LmMnCMPLTSTAT", 0x7F,  8, MD(0)|MD(1) पूर्ण,
	अणु"LmPRMSTAT0",    0x80, 32, MODE_COMMON पूर्ण,
	अणु"LmPRMSTAT1",    0x84, 32, MODE_COMMON पूर्ण,
	अणु"LmGPRMINT",     0x88,  8, MODE_COMMON पूर्ण,
        अणु"LmMnCURRSCB",   0x8A, 16, MD(0) पूर्ण,
	अणु"LmPRMICODE",    0x8C, 32, MODE_COMMON पूर्ण,
	अणु"LmMnRCVCNT",    0x90, 16, MD(0) पूर्ण,
	अणु"LmMnBUFSTAT",   0x92, 16, MD(0) पूर्ण,
	अणु"LmMnXMTHDRSIZE",0x92,  8, MD(1) पूर्ण,
	अणु"LmMnXMTSIZE",   0x93,  8, MD(1) पूर्ण,
	अणु"LmMnTGTXFRCNT", 0x94, 32, MD(0) पूर्ण,
	अणु"LmMnEXPROFS",   0x98, 32, MD(0) पूर्ण,
	अणु"LmMnXMTROFS",   0x98, 32, MD(1) पूर्ण,
	अणु"LmMnRCVROFS",   0x9C, 32, MD(0) पूर्ण,
	अणु"LmCONCTL",      0xA0, 16, MODE_COMMON पूर्ण,
	अणु"LmBITLTIMER",   0xA2, 16, MODE_COMMON पूर्ण,
	अणु"LmWWNLOW",      0xA8, 32, MODE_COMMON पूर्ण,
	अणु"LmWWNHIGH",     0xAC, 32, MODE_COMMON पूर्ण,
	अणु"LmMnFRMERR",    0xB0, 32, MD(0) पूर्ण,
	अणु"LmMnFRMERREN",  0xB4, 32, MD(0) पूर्ण,
	अणु"LmAWTIMER",     0xB8, 16, MODE_COMMON पूर्ण,
	अणु"LmAWTCTL",      0xBA,  8, MODE_COMMON पूर्ण,
	अणु"LmMnHDRCMPS",   0xC0, 32, MD(0) पूर्ण,
	अणु"LmMnXMTSTAT",   0xC4,  8, MD(1) पूर्ण,
	अणु"LmHWTSTATEN",   0xC5,  8, MODE_COMMON पूर्ण,
	अणु"LmMnRRDYRC",    0xC6,  8, MD(0) पूर्ण,
        अणु"LmMnRRDYTC",    0xC6,  8, MD(1) पूर्ण,
	अणु"LmHWTSTAT",     0xC7,  8, MODE_COMMON पूर्ण,
	अणु"LmMnDATABUFADR",0xC8, 16, MD(0)|MD(1) पूर्ण,
	अणु"LmDWSSTATUS",   0xCB,  8, MODE_COMMON पूर्ण,
	अणु"LmMnACTSTAT",   0xCE, 16, MD(0)|MD(1) पूर्ण,
	अणु"LmMnREQSCB",    0xD2, 16, MD(0)|MD(1) पूर्ण,
	अणु"LmXXXPRIM",     0xD4, 32, MODE_COMMON पूर्ण,
	अणु"LmRCVASTAT",    0xD9,  8, MODE_COMMON पूर्ण,
	अणु"LmINTDIS1",     0xDA,  8, MODE_COMMON पूर्ण,
	अणु"LmPSTORESEL",   0xDB,  8, MODE_COMMON पूर्ण,
	अणु"LmPSTORE",      0xDC, 32, MODE_COMMON पूर्ण,
	अणु"LmPRIMSTAT0EN", 0xE0, 32, MODE_COMMON पूर्ण,
	अणु"LmPRIMSTAT1EN", 0xE4, 32, MODE_COMMON पूर्ण,
	अणु"LmDONETCTL",    0xF2, 16, MODE_COMMON पूर्ण,
	अणुशून्य, 0, 0, 0 पूर्ण
पूर्ण;
/*
अटल काष्ठा lseq_cio_regs LSEQmOOBREGS[] = अणु
   अणु"OOB_BFLTR"        ,0x100, 8, MD(5)पूर्ण,
   अणु"OOB_INIT_MIN"     ,0x102,16, MD(5)पूर्ण,
   अणु"OOB_INIT_MAX"     ,0x104,16, MD(5)पूर्ण,
   अणु"OOB_INIT_NEG"     ,0x106,16, MD(5)पूर्ण,
   अणु"OOB_SAS_MIN"      ,0x108,16, MD(5)पूर्ण,
   अणु"OOB_SAS_MAX"      ,0x10A,16, MD(5)पूर्ण,
   अणु"OOB_SAS_NEG"      ,0x10C,16, MD(5)पूर्ण,
   अणु"OOB_WAKE_MIN"     ,0x10E,16, MD(5)पूर्ण,
   अणु"OOB_WAKE_MAX"     ,0x110,16, MD(5)पूर्ण,
   अणु"OOB_WAKE_NEG"     ,0x112,16, MD(5)पूर्ण,
   अणु"OOB_IDLE_MAX"     ,0x114,16, MD(5)पूर्ण,
   अणु"OOB_BURST_MAX"    ,0x116,16, MD(5)पूर्ण,
   अणु"OOB_XMIT_BURST"   ,0x118, 8, MD(5)पूर्ण,
   अणु"OOB_SEND_PAIRS"   ,0x119, 8, MD(5)पूर्ण,
   अणु"OOB_INIT_IDLE"    ,0x11A, 8, MD(5)पूर्ण,
   अणु"OOB_INIT_NEGO"    ,0x11C, 8, MD(5)पूर्ण,
   अणु"OOB_SAS_IDLE"     ,0x11E, 8, MD(5)पूर्ण,
   अणु"OOB_SAS_NEGO"     ,0x120, 8, MD(5)पूर्ण,
   अणु"OOB_WAKE_IDLE"    ,0x122, 8, MD(5)पूर्ण,
   अणु"OOB_WAKE_NEGO"    ,0x124, 8, MD(5)पूर्ण,
   अणु"OOB_DATA_KBITS"   ,0x126, 8, MD(5)पूर्ण,
   अणु"OOB_BURST_DATA"   ,0x128,32, MD(5)पूर्ण,
   अणु"OOB_ALIGN_0_DATA" ,0x12C,32, MD(5)पूर्ण,
   अणु"OOB_ALIGN_1_DATA" ,0x130,32, MD(5)पूर्ण,
   अणु"OOB_SYNC_DATA"    ,0x134,32, MD(5)पूर्ण,
   अणु"OOB_D10_2_DATA"   ,0x138,32, MD(5)पूर्ण,
   अणु"OOB_PHY_RST_CNT"  ,0x13C,32, MD(5)पूर्ण,
   अणु"OOB_SIG_GEN"      ,0x140, 8, MD(5)पूर्ण,
   अणु"OOB_XMIT"         ,0x141, 8, MD(5)पूर्ण,
   अणु"FUNCTION_MAKS"    ,0x142, 8, MD(5)पूर्ण,
   अणु"OOB_MODE"         ,0x143, 8, MD(5)पूर्ण,
   अणु"CURRENT_STATUS"   ,0x144, 8, MD(5)पूर्ण,
   अणु"SPEED_MASK"       ,0x145, 8, MD(5)पूर्ण,
   अणु"PRIM_COUNT"       ,0x146, 8, MD(5)पूर्ण,
   अणु"OOB_SIGNALS"      ,0x148, 8, MD(5)पूर्ण,
   अणु"OOB_DATA_DET"     ,0x149, 8, MD(5)पूर्ण,
   अणु"OOB_TIME_OUT"     ,0x14C, 8, MD(5)पूर्ण,
   अणु"OOB_TIMER_ENABLE" ,0x14D, 8, MD(5)पूर्ण,
   अणु"OOB_STATUS"       ,0x14E, 8, MD(5)पूर्ण,
   अणु"HOT_PLUG_DELAY"   ,0x150, 8, MD(5)पूर्ण,
   अणु"RCD_DELAY"        ,0x151, 8, MD(5)पूर्ण,
   अणु"COMSAS_TIMER"     ,0x152, 8, MD(5)पूर्ण,
   अणु"SNTT_DELAY"       ,0x153, 8, MD(5)पूर्ण,
   अणु"SPD_CHNG_DELAY"   ,0x154, 8, MD(5)पूर्ण,
   अणु"SNLT_DELAY"       ,0x155, 8, MD(5)पूर्ण,
   अणु"SNWT_DELAY"       ,0x156, 8, MD(5)पूर्ण,
   अणु"ALIGN_DELAY"      ,0x157, 8, MD(5)पूर्ण,
   अणु"INT_ENABLE_0"     ,0x158, 8, MD(5)पूर्ण,
   अणु"INT_ENABLE_1"     ,0x159, 8, MD(5)पूर्ण,
   अणु"INT_ENABLE_2"     ,0x15A, 8, MD(5)पूर्ण,
   अणु"INT_ENABLE_3"     ,0x15B, 8, MD(5)पूर्ण,
   अणु"OOB_TEST_REG"     ,0x15C, 8, MD(5)पूर्ण,
   अणु"PHY_CONTROL_0"    ,0x160, 8, MD(5)पूर्ण,
   अणु"PHY_CONTROL_1"    ,0x161, 8, MD(5)पूर्ण,
   अणु"PHY_CONTROL_2"    ,0x162, 8, MD(5)पूर्ण,
   अणु"PHY_CONTROL_3"    ,0x163, 8, MD(5)पूर्ण,
   अणु"PHY_OOB_CAL_TX"   ,0x164, 8, MD(5)पूर्ण,
   अणु"PHY_OOB_CAL_RX"   ,0x165, 8, MD(5)पूर्ण,
   अणु"OOB_PHY_CAL_TX"   ,0x166, 8, MD(5)पूर्ण,
   अणु"OOB_PHY_CAL_RX"   ,0x167, 8, MD(5)पूर्ण,
   अणु"PHY_CONTROL_4"    ,0x168, 8, MD(5)पूर्ण,
   अणु"PHY_TEST"         ,0x169, 8, MD(5)पूर्ण,
   अणु"PHY_PWR_CTL"      ,0x16A, 8, MD(5)पूर्ण,
   अणु"PHY_PWR_DELAY"    ,0x16B, 8, MD(5)पूर्ण,
   अणु"OOB_SM_CON"       ,0x16C, 8, MD(5)पूर्ण,
   अणु"ADDR_TRAP_1"      ,0x16D, 8, MD(5)पूर्ण,
   अणु"ADDR_NEXT_1"      ,0x16E, 8, MD(5)पूर्ण,
   अणु"NEXT_ST_1"        ,0x16F, 8, MD(5)पूर्ण,
   अणु"OOB_SM_STATE"     ,0x170, 8, MD(5)पूर्ण,
   अणु"ADDR_TRAP_2"      ,0x171, 8, MD(5)पूर्ण,
   अणु"ADDR_NEXT_2"      ,0x172, 8, MD(5)पूर्ण,
   अणु"NEXT_ST_2"        ,0x173, 8, MD(5)पूर्ण,
   अणुशून्य, 0, 0, 0 पूर्ण
पूर्ण;
*/
#घोषणा STR_8BIT   "   %30s[0x%04x]:0x%02x\n"
#घोषणा STR_16BIT  "   %30s[0x%04x]:0x%04x\n"
#घोषणा STR_32BIT  "   %30s[0x%04x]:0x%08x\n"
#घोषणा STR_64BIT  "   %30s[0x%04x]:0x%llx\n"

#घोषणा PRINT_REG_8bit(_ha, _n, _r) asd_prपूर्णांकk(STR_8BIT, #_n, _n,      \
					     asd_पढ़ो_reg_byte(_ha, _r))
#घोषणा PRINT_REG_16bit(_ha, _n, _r) asd_prपूर्णांकk(STR_16BIT, #_n, _n,     \
					      asd_पढ़ो_reg_word(_ha, _r))
#घोषणा PRINT_REG_32bit(_ha, _n, _r) asd_prपूर्णांकk(STR_32BIT, #_n, _n,      \
					      asd_पढ़ो_reg_dword(_ha, _r))

#घोषणा PRINT_CREG_8bit(_ha, _n) asd_prपूर्णांकk(STR_8BIT, #_n, _n,      \
					     asd_पढ़ो_reg_byte(_ha, C##_n))
#घोषणा PRINT_CREG_16bit(_ha, _n) asd_prपूर्णांकk(STR_16BIT, #_n, _n,     \
					      asd_पढ़ो_reg_word(_ha, C##_n))
#घोषणा PRINT_CREG_32bit(_ha, _n) asd_prपूर्णांकk(STR_32BIT, #_n, _n,      \
					      asd_पढ़ो_reg_dword(_ha, C##_n))

#घोषणा MSTR_8BIT   "   Mode:%02d %30s[0x%04x]:0x%02x\n"
#घोषणा MSTR_16BIT  "   Mode:%02d %30s[0x%04x]:0x%04x\n"
#घोषणा MSTR_32BIT  "   Mode:%02d %30s[0x%04x]:0x%08x\n"

#घोषणा PRINT_MREG_8bit(_ha, _m, _n, _r) asd_prपूर्णांकk(MSTR_8BIT, _m, #_n, _n,   \
					     asd_पढ़ो_reg_byte(_ha, _r))
#घोषणा PRINT_MREG_16bit(_ha, _m, _n, _r) asd_prपूर्णांकk(MSTR_16BIT, _m, #_n, _n, \
					      asd_पढ़ो_reg_word(_ha, _r))
#घोषणा PRINT_MREG_32bit(_ha, _m, _n, _r) asd_prपूर्णांकk(MSTR_32BIT, _m, #_n, _n, \
					      asd_पढ़ो_reg_dword(_ha, _r))

/* can also be used क्रम MD when the रेजिस्टर is mode aware alपढ़ोy */
#घोषणा PRINT_MIS_byte(_ha, _n) asd_prपूर्णांकk(STR_8BIT, #_n,CSEQ_##_n-CMAPPEDSCR,\
                                           asd_पढ़ो_reg_byte(_ha, CSEQ_##_n))
#घोषणा PRINT_MIS_word(_ha, _n) asd_prपूर्णांकk(STR_16BIT,#_n,CSEQ_##_n-CMAPPEDSCR,\
                                           asd_पढ़ो_reg_word(_ha, CSEQ_##_n))
#घोषणा PRINT_MIS_dword(_ha, _n)                      \
        asd_prपूर्णांकk(STR_32BIT,#_n,CSEQ_##_n-CMAPPEDSCR,\
                   asd_पढ़ो_reg_dword(_ha, CSEQ_##_n))
#घोषणा PRINT_MIS_qword(_ha, _n)                                       \
        asd_prपूर्णांकk(STR_64BIT, #_n,CSEQ_##_n-CMAPPEDSCR,                \
                   (अचिन्हित दीर्घ दीर्घ)(((u64)asd_पढ़ो_reg_dword(_ha, CSEQ_##_n))     \
                 | (((u64)asd_पढ़ो_reg_dword(_ha, (CSEQ_##_n)+4))<<32)))

#घोषणा CMDP_REG(_n, _m) (_m*(CSEQ_PAGE_SIZE*2)+CSEQ_##_n)
#घोषणा PRINT_CMDP_word(_ha, _n) \
asd_prपूर्णांकk("%20s 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n", \
	#_n, \
	asd_पढ़ो_reg_word(_ha, CMDP_REG(_n, 0)), \
	asd_पढ़ो_reg_word(_ha, CMDP_REG(_n, 1)), \
	asd_पढ़ो_reg_word(_ha, CMDP_REG(_n, 2)), \
	asd_पढ़ो_reg_word(_ha, CMDP_REG(_n, 3)), \
	asd_पढ़ो_reg_word(_ha, CMDP_REG(_n, 4)), \
	asd_पढ़ो_reg_word(_ha, CMDP_REG(_n, 5)), \
	asd_पढ़ो_reg_word(_ha, CMDP_REG(_n, 6)), \
	asd_पढ़ो_reg_word(_ha, CMDP_REG(_n, 7)))

#घोषणा PRINT_CMDP_byte(_ha, _n) \
asd_prपूर्णांकk("%20s 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n", \
	#_n, \
	asd_पढ़ो_reg_byte(_ha, CMDP_REG(_n, 0)), \
	asd_पढ़ो_reg_byte(_ha, CMDP_REG(_n, 1)), \
	asd_पढ़ो_reg_byte(_ha, CMDP_REG(_n, 2)), \
	asd_पढ़ो_reg_byte(_ha, CMDP_REG(_n, 3)), \
	asd_पढ़ो_reg_byte(_ha, CMDP_REG(_n, 4)), \
	asd_पढ़ो_reg_byte(_ha, CMDP_REG(_n, 5)), \
	asd_पढ़ो_reg_byte(_ha, CMDP_REG(_n, 6)), \
	asd_पढ़ो_reg_byte(_ha, CMDP_REG(_n, 7)))

अटल व्योम asd_dump_cseq_state(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक mode;

	asd_prपूर्णांकk("CSEQ STATE\n");

	asd_prपूर्णांकk("ARP2 REGISTERS\n");

	PRINT_CREG_32bit(asd_ha, ARP2CTL);
	PRINT_CREG_32bit(asd_ha, ARP2INT);
	PRINT_CREG_32bit(asd_ha, ARP2INTEN);
	PRINT_CREG_8bit(asd_ha, MODEPTR);
	PRINT_CREG_8bit(asd_ha, ALTMODE);
	PRINT_CREG_8bit(asd_ha, FLAG);
	PRINT_CREG_8bit(asd_ha, ARP2INTCTL);
	PRINT_CREG_16bit(asd_ha, STACK);
	PRINT_CREG_16bit(asd_ha, PRGMCNT);
	PRINT_CREG_16bit(asd_ha, ACCUM);
	PRINT_CREG_16bit(asd_ha, SINDEX);
	PRINT_CREG_16bit(asd_ha, DINDEX);
	PRINT_CREG_8bit(asd_ha, SINसूची);
	PRINT_CREG_8bit(asd_ha, DINसूची);
	PRINT_CREG_8bit(asd_ha, JUMLसूची);
	PRINT_CREG_8bit(asd_ha, ARP2HALTCODE);
	PRINT_CREG_16bit(asd_ha, CURRADDR);
	PRINT_CREG_16bit(asd_ha, LASTADDR);
	PRINT_CREG_16bit(asd_ha, NXTLADDR);

	asd_prपूर्णांकk("IOP REGISTERS\n");

	PRINT_REG_32bit(asd_ha, BISTCTL1, CBISTCTL);
	PRINT_CREG_32bit(asd_ha, MAPPEDSCR);

	asd_prपूर्णांकk("CIO REGISTERS\n");

	क्रम (mode = 0; mode < 9; mode++)
		PRINT_MREG_16bit(asd_ha, mode, MnSCBPTR, CMnSCBPTR(mode));
	PRINT_MREG_16bit(asd_ha, 15, MnSCBPTR, CMnSCBPTR(15));

	क्रम (mode = 0; mode < 9; mode++)
		PRINT_MREG_16bit(asd_ha, mode, MnDDBPTR, CMnDDBPTR(mode));
	PRINT_MREG_16bit(asd_ha, 15, MnDDBPTR, CMnDDBPTR(15));

	क्रम (mode = 0; mode < 8; mode++)
		PRINT_MREG_32bit(asd_ha, mode, MnREQMBX, CMnREQMBX(mode));
	क्रम (mode = 0; mode < 8; mode++)
		PRINT_MREG_32bit(asd_ha, mode, MnRSPMBX, CMnRSPMBX(mode));
	क्रम (mode = 0; mode < 8; mode++)
		PRINT_MREG_32bit(asd_ha, mode, MnINT, CMnINT(mode));
	क्रम (mode = 0; mode < 8; mode++)
		PRINT_MREG_32bit(asd_ha, mode, MnINTEN, CMnINTEN(mode));

	PRINT_CREG_8bit(asd_ha, SCRATCHPAGE);
	क्रम (mode = 0; mode < 8; mode++)
		PRINT_MREG_8bit(asd_ha, mode, MnSCRATCHPAGE,
				CMnSCRATCHPAGE(mode));

	PRINT_REG_32bit(asd_ha, CLINKCON, CLINKCON);
	PRINT_REG_8bit(asd_ha, CCONMSK, CCONMSK);
	PRINT_REG_8bit(asd_ha, CCONEXIST, CCONEXIST);
	PRINT_REG_16bit(asd_ha, CCONMODE, CCONMODE);
	PRINT_REG_32bit(asd_ha, CTIMERCALC, CTIMERCALC);
	PRINT_REG_8bit(asd_ha, CINTDIS, CINTDIS);

	asd_prपूर्णांकk("SCRATCH MEMORY\n");

	asd_prपूर्णांकk("MIP 4 >>>>>\n");
	PRINT_MIS_word(asd_ha, Q_EXE_HEAD);
	PRINT_MIS_word(asd_ha, Q_EXE_TAIL);
	PRINT_MIS_word(asd_ha, Q_DONE_HEAD);
	PRINT_MIS_word(asd_ha, Q_DONE_TAIL);
	PRINT_MIS_word(asd_ha, Q_SEND_HEAD);
	PRINT_MIS_word(asd_ha, Q_SEND_TAIL);
	PRINT_MIS_word(asd_ha, Q_DMA2CHIM_HEAD);
	PRINT_MIS_word(asd_ha, Q_DMA2CHIM_TAIL);
	PRINT_MIS_word(asd_ha, Q_COPY_HEAD);
	PRINT_MIS_word(asd_ha, Q_COPY_TAIL);
	PRINT_MIS_word(asd_ha, REG0);
	PRINT_MIS_word(asd_ha, REG1);
	PRINT_MIS_dword(asd_ha, REG2);
	PRINT_MIS_byte(asd_ha, LINK_CTL_Q_MAP);
	PRINT_MIS_byte(asd_ha, MAX_CSEQ_MODE);
	PRINT_MIS_byte(asd_ha, FREE_LIST_HACK_COUNT);

	asd_prपूर्णांकk("MIP 5 >>>>\n");
	PRINT_MIS_qword(asd_ha, EST_NEXUS_REQ_QUEUE);
	PRINT_MIS_qword(asd_ha, EST_NEXUS_REQ_COUNT);
	PRINT_MIS_word(asd_ha, Q_EST_NEXUS_HEAD);
	PRINT_MIS_word(asd_ha, Q_EST_NEXUS_TAIL);
	PRINT_MIS_word(asd_ha, NEED_EST_NEXUS_SCB);
	PRINT_MIS_byte(asd_ha, EST_NEXUS_REQ_HEAD);
	PRINT_MIS_byte(asd_ha, EST_NEXUS_REQ_TAIL);
	PRINT_MIS_byte(asd_ha, EST_NEXUS_SCB_OFFSET);

	asd_prपूर्णांकk("MIP 6 >>>>\n");
	PRINT_MIS_word(asd_ha, INT_ROUT_RET_ADDR0);
	PRINT_MIS_word(asd_ha, INT_ROUT_RET_ADDR1);
	PRINT_MIS_word(asd_ha, INT_ROUT_SCBPTR);
	PRINT_MIS_byte(asd_ha, INT_ROUT_MODE);
	PRINT_MIS_byte(asd_ha, ISR_SCRATCH_FLAGS);
	PRINT_MIS_word(asd_ha, ISR_SAVE_SINDEX);
	PRINT_MIS_word(asd_ha, ISR_SAVE_DINDEX);
	PRINT_MIS_word(asd_ha, Q_MONIRTT_HEAD);
	PRINT_MIS_word(asd_ha, Q_MONIRTT_TAIL);
	PRINT_MIS_byte(asd_ha, FREE_SCB_MASK);
	PRINT_MIS_word(asd_ha, BUILTIN_FREE_SCB_HEAD);
	PRINT_MIS_word(asd_ha, BUILTIN_FREE_SCB_TAIL);
	PRINT_MIS_word(asd_ha, EXTENDED_FREE_SCB_HEAD);
	PRINT_MIS_word(asd_ha, EXTENDED_FREE_SCB_TAIL);

	asd_prपूर्णांकk("MIP 7 >>>>\n");
	PRINT_MIS_qword(asd_ha, EMPTY_REQ_QUEUE);
	PRINT_MIS_qword(asd_ha, EMPTY_REQ_COUNT);
	PRINT_MIS_word(asd_ha, Q_EMPTY_HEAD);
	PRINT_MIS_word(asd_ha, Q_EMPTY_TAIL);
	PRINT_MIS_word(asd_ha, NEED_EMPTY_SCB);
	PRINT_MIS_byte(asd_ha, EMPTY_REQ_HEAD);
	PRINT_MIS_byte(asd_ha, EMPTY_REQ_TAIL);
	PRINT_MIS_byte(asd_ha, EMPTY_SCB_OFFSET);
	PRINT_MIS_word(asd_ha, PRIMITIVE_DATA);
	PRINT_MIS_dword(asd_ha, TIMEOUT_CONST);

	asd_prपूर्णांकk("MDP 0 >>>>\n");
	asd_prपूर्णांकk("%-20s %6s %6s %6s %6s %6s %6s %6s %6s\n",
		   "Mode: ", "0", "1", "2", "3", "4", "5", "6", "7");
	PRINT_CMDP_word(asd_ha, LRM_SAVE_SINDEX);
	PRINT_CMDP_word(asd_ha, LRM_SAVE_SCBPTR);
	PRINT_CMDP_word(asd_ha, Q_LINK_HEAD);
	PRINT_CMDP_word(asd_ha, Q_LINK_TAIL);
	PRINT_CMDP_byte(asd_ha, LRM_SAVE_SCRPAGE);

	asd_prपूर्णांकk("MDP 0 Mode 8 >>>>\n");
	PRINT_MIS_word(asd_ha, RET_ADDR);
	PRINT_MIS_word(asd_ha, RET_SCBPTR);
	PRINT_MIS_word(asd_ha, SAVE_SCBPTR);
	PRINT_MIS_word(asd_ha, EMPTY_TRANS_CTX);
	PRINT_MIS_word(asd_ha, RESP_LEN);
	PRINT_MIS_word(asd_ha, TMF_SCBPTR);
	PRINT_MIS_word(asd_ha, GLOBAL_PREV_SCB);
	PRINT_MIS_word(asd_ha, GLOBAL_HEAD);
	PRINT_MIS_word(asd_ha, CLEAR_LU_HEAD);
	PRINT_MIS_byte(asd_ha, TMF_OPCODE);
	PRINT_MIS_byte(asd_ha, SCRATCH_FLAGS);
	PRINT_MIS_word(asd_ha, HSB_SITE);
	PRINT_MIS_word(asd_ha, FIRST_INV_SCB_SITE);
	PRINT_MIS_word(asd_ha, FIRST_INV_DDB_SITE);

	asd_prपूर्णांकk("MDP 1 Mode 8 >>>>\n");
	PRINT_MIS_qword(asd_ha, LUN_TO_CLEAR);
	PRINT_MIS_qword(asd_ha, LUN_TO_CHECK);

	asd_prपूर्णांकk("MDP 2 Mode 8 >>>>\n");
	PRINT_MIS_qword(asd_ha, HQ_NEW_POINTER);
	PRINT_MIS_qword(asd_ha, HQ_DONE_BASE);
	PRINT_MIS_dword(asd_ha, HQ_DONE_POINTER);
	PRINT_MIS_byte(asd_ha, HQ_DONE_PASS);
पूर्ण

#घोषणा PRINT_LREG_8bit(_h, _lseq, _n) \
        asd_prपूर्णांकk(STR_8BIT, #_n, _n, asd_पढ़ो_reg_byte(_h, Lm##_n(_lseq)))
#घोषणा PRINT_LREG_16bit(_h, _lseq, _n) \
        asd_prपूर्णांकk(STR_16BIT, #_n, _n, asd_पढ़ो_reg_word(_h, Lm##_n(_lseq)))
#घोषणा PRINT_LREG_32bit(_h, _lseq, _n) \
        asd_prपूर्णांकk(STR_32BIT, #_n, _n, asd_पढ़ो_reg_dword(_h, Lm##_n(_lseq)))

#घोषणा PRINT_LMIP_byte(_h, _lseq, _n)                              \
	asd_prपूर्णांकk(STR_8BIT, #_n, LmSEQ_##_n(_lseq)-LmSCRATCH(_lseq), \
		   asd_पढ़ो_reg_byte(_h, LmSEQ_##_n(_lseq)))
#घोषणा PRINT_LMIP_word(_h, _lseq, _n)                              \
	asd_prपूर्णांकk(STR_16BIT, #_n, LmSEQ_##_n(_lseq)-LmSCRATCH(_lseq), \
		   asd_पढ़ो_reg_word(_h, LmSEQ_##_n(_lseq)))
#घोषणा PRINT_LMIP_dword(_h, _lseq, _n)                             \
	asd_prपूर्णांकk(STR_32BIT, #_n, LmSEQ_##_n(_lseq)-LmSCRATCH(_lseq), \
		   asd_पढ़ो_reg_dword(_h, LmSEQ_##_n(_lseq)))
#घोषणा PRINT_LMIP_qword(_h, _lseq, _n)                                \
	asd_prपूर्णांकk(STR_64BIT, #_n, LmSEQ_##_n(_lseq)-LmSCRATCH(_lseq), \
		 (अचिन्हित दीर्घ दीर्घ)(((अचिन्हित दीर्घ दीर्घ) \
		 asd_पढ़ो_reg_dword(_h, LmSEQ_##_n(_lseq))) \
	          | (((अचिन्हित दीर्घ दीर्घ) \
		 asd_पढ़ो_reg_dword(_h, LmSEQ_##_n(_lseq)+4))<<32)))

अटल व्योम asd_prपूर्णांक_lseq_cio_reg(काष्ठा asd_ha_काष्ठा *asd_ha,
				   u32 lseq_cio_addr, पूर्णांक i)
अणु
	चयन (LSEQmCIOREGS[i].width) अणु
	हाल 8:
		asd_prपूर्णांकk("%20s[0x%x]: 0x%02x\n", LSEQmCIOREGS[i].name,
			   LSEQmCIOREGS[i].offs,
			   asd_पढ़ो_reg_byte(asd_ha, lseq_cio_addr +
					     LSEQmCIOREGS[i].offs));

		अवरोध;
	हाल 16:
		asd_prपूर्णांकk("%20s[0x%x]: 0x%04x\n", LSEQmCIOREGS[i].name,
			   LSEQmCIOREGS[i].offs,
			   asd_पढ़ो_reg_word(asd_ha, lseq_cio_addr +
					     LSEQmCIOREGS[i].offs));

		अवरोध;
	हाल 32:
		asd_prपूर्णांकk("%20s[0x%x]: 0x%08x\n", LSEQmCIOREGS[i].name,
			   LSEQmCIOREGS[i].offs,
			   asd_पढ़ो_reg_dword(asd_ha, lseq_cio_addr +
					      LSEQmCIOREGS[i].offs));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम asd_dump_lseq_state(काष्ठा asd_ha_काष्ठा *asd_ha, पूर्णांक lseq)
अणु
	u32 moffs;
	पूर्णांक mode;

	asd_prपूर्णांकk("LSEQ %d STATE\n", lseq);

	asd_prपूर्णांकk("LSEQ%d: ARP2 REGISTERS\n", lseq);
	PRINT_LREG_32bit(asd_ha, lseq, ARP2CTL);
	PRINT_LREG_32bit(asd_ha, lseq, ARP2INT);
	PRINT_LREG_32bit(asd_ha, lseq, ARP2INTEN);
	PRINT_LREG_8bit(asd_ha, lseq, MODEPTR);
	PRINT_LREG_8bit(asd_ha, lseq, ALTMODE);
	PRINT_LREG_8bit(asd_ha, lseq, FLAG);
	PRINT_LREG_8bit(asd_ha, lseq, ARP2INTCTL);
	PRINT_LREG_16bit(asd_ha, lseq, STACK);
	PRINT_LREG_16bit(asd_ha, lseq, PRGMCNT);
	PRINT_LREG_16bit(asd_ha, lseq, ACCUM);
	PRINT_LREG_16bit(asd_ha, lseq, SINDEX);
	PRINT_LREG_16bit(asd_ha, lseq, DINDEX);
	PRINT_LREG_8bit(asd_ha, lseq, SINसूची);
	PRINT_LREG_8bit(asd_ha, lseq, DINसूची);
	PRINT_LREG_8bit(asd_ha, lseq, JUMLसूची);
	PRINT_LREG_8bit(asd_ha, lseq, ARP2HALTCODE);
	PRINT_LREG_16bit(asd_ha, lseq, CURRADDR);
	PRINT_LREG_16bit(asd_ha, lseq, LASTADDR);
	PRINT_LREG_16bit(asd_ha, lseq, NXTLADDR);

	asd_prपूर्णांकk("LSEQ%d: IOP REGISTERS\n", lseq);

	PRINT_LREG_32bit(asd_ha, lseq, MODECTL);
	PRINT_LREG_32bit(asd_ha, lseq, DBGMODE);
	PRINT_LREG_32bit(asd_ha, lseq, CONTROL);
	PRINT_REG_32bit(asd_ha, BISTCTL0, LmBISTCTL0(lseq));
	PRINT_REG_32bit(asd_ha, BISTCTL1, LmBISTCTL1(lseq));

	asd_prपूर्णांकk("LSEQ%d: CIO REGISTERS\n", lseq);
	asd_prपूर्णांकk("Mode common:\n");

	क्रम (mode = 0; mode < 8; mode++) अणु
		u32 lseq_cio_addr = LmSEQ_PHY_BASE(mode, lseq);
		पूर्णांक i;

		क्रम (i = 0; LSEQmCIOREGS[i].name; i++)
			अगर (LSEQmCIOREGS[i].mode == MODE_COMMON)
				asd_prपूर्णांक_lseq_cio_reg(asd_ha,lseq_cio_addr,i);
	पूर्ण

	asd_prपूर्णांकk("Mode unique:\n");
	क्रम (mode = 0; mode < 8; mode++) अणु
		u32 lseq_cio_addr = LmSEQ_PHY_BASE(mode, lseq);
		पूर्णांक i;

		asd_prपूर्णांकk("Mode %d\n", mode);
		क्रम  (i = 0; LSEQmCIOREGS[i].name; i++) अणु
			अगर (!(LSEQmCIOREGS[i].mode & (1 << mode)))
				जारी;
			asd_prपूर्णांक_lseq_cio_reg(asd_ha, lseq_cio_addr, i);
		पूर्ण
	पूर्ण

	asd_prपूर्णांकk("SCRATCH MEMORY\n");

	asd_prपूर्णांकk("LSEQ%d MIP 0 >>>>\n", lseq);
	PRINT_LMIP_word(asd_ha, lseq, Q_TGTXFR_HEAD);
	PRINT_LMIP_word(asd_ha, lseq, Q_TGTXFR_TAIL);
	PRINT_LMIP_byte(asd_ha, lseq, LINK_NUMBER);
	PRINT_LMIP_byte(asd_ha, lseq, SCRATCH_FLAGS);
	PRINT_LMIP_dword(asd_ha, lseq, CONNECTION_STATE);
	PRINT_LMIP_word(asd_ha, lseq, CONCTL);
	PRINT_LMIP_byte(asd_ha, lseq, CONSTAT);
	PRINT_LMIP_byte(asd_ha, lseq, CONNECTION_MODES);
	PRINT_LMIP_word(asd_ha, lseq, REG1_ISR);
	PRINT_LMIP_word(asd_ha, lseq, REG2_ISR);
	PRINT_LMIP_word(asd_ha, lseq, REG3_ISR);
	PRINT_LMIP_qword(asd_ha, lseq,REG0_ISR);

	asd_prपूर्णांकk("LSEQ%d MIP 1 >>>>\n", lseq);
	PRINT_LMIP_word(asd_ha, lseq, EST_NEXUS_SCBPTR0);
	PRINT_LMIP_word(asd_ha, lseq, EST_NEXUS_SCBPTR1);
	PRINT_LMIP_word(asd_ha, lseq, EST_NEXUS_SCBPTR2);
	PRINT_LMIP_word(asd_ha, lseq, EST_NEXUS_SCBPTR3);
	PRINT_LMIP_byte(asd_ha, lseq, EST_NEXUS_SCB_OPCODE0);
	PRINT_LMIP_byte(asd_ha, lseq, EST_NEXUS_SCB_OPCODE1);
	PRINT_LMIP_byte(asd_ha, lseq, EST_NEXUS_SCB_OPCODE2);
	PRINT_LMIP_byte(asd_ha, lseq, EST_NEXUS_SCB_OPCODE3);
	PRINT_LMIP_byte(asd_ha, lseq, EST_NEXUS_SCB_HEAD);
	PRINT_LMIP_byte(asd_ha, lseq, EST_NEXUS_SCB_TAIL);
	PRINT_LMIP_byte(asd_ha, lseq, EST_NEXUS_BUF_AVAIL);
	PRINT_LMIP_dword(asd_ha, lseq, TIMEOUT_CONST);
	PRINT_LMIP_word(asd_ha, lseq, ISR_SAVE_SINDEX);
	PRINT_LMIP_word(asd_ha, lseq, ISR_SAVE_DINDEX);

	asd_prपूर्णांकk("LSEQ%d MIP 2 >>>>\n", lseq);
	PRINT_LMIP_word(asd_ha, lseq, EMPTY_SCB_PTR0);
	PRINT_LMIP_word(asd_ha, lseq, EMPTY_SCB_PTR1);
	PRINT_LMIP_word(asd_ha, lseq, EMPTY_SCB_PTR2);
	PRINT_LMIP_word(asd_ha, lseq, EMPTY_SCB_PTR3);
	PRINT_LMIP_byte(asd_ha, lseq, EMPTY_SCB_OPCD0);
	PRINT_LMIP_byte(asd_ha, lseq, EMPTY_SCB_OPCD1);
	PRINT_LMIP_byte(asd_ha, lseq, EMPTY_SCB_OPCD2);
	PRINT_LMIP_byte(asd_ha, lseq, EMPTY_SCB_OPCD3);
	PRINT_LMIP_byte(asd_ha, lseq, EMPTY_SCB_HEAD);
	PRINT_LMIP_byte(asd_ha, lseq, EMPTY_SCB_TAIL);
	PRINT_LMIP_byte(asd_ha, lseq, EMPTY_BUFS_AVAIL);

	asd_prपूर्णांकk("LSEQ%d MIP 3 >>>>\n", lseq);
	PRINT_LMIP_dword(asd_ha, lseq, DEV_PRES_TMR_TOUT_CONST);
	PRINT_LMIP_dword(asd_ha, lseq, SATA_INTERLOCK_TIMEOUT);
	PRINT_LMIP_dword(asd_ha, lseq, SRST_ASSERT_TIMEOUT);
	PRINT_LMIP_dword(asd_ha, lseq, RCV_FIS_TIMEOUT);
	PRINT_LMIP_dword(asd_ha, lseq, ONE_MILLISEC_TIMEOUT);
	PRINT_LMIP_dword(asd_ha, lseq, TEN_MS_COMINIT_TIMEOUT);
	PRINT_LMIP_dword(asd_ha, lseq, SMP_RCV_TIMEOUT);

	क्रम (mode = 0; mode < 3; mode++) अणु
		asd_prपूर्णांकk("LSEQ%d MDP 0 MODE %d >>>>\n", lseq, mode);
		moffs = mode * LSEQ_MODE_SCRATCH_SIZE;

		asd_prपूर्णांकk(STR_16BIT, "RET_ADDR", 0,
			   asd_पढ़ो_reg_word(asd_ha, LmSEQ_RET_ADDR(lseq)
					     + moffs));
		asd_prपूर्णांकk(STR_16BIT, "REG0_MODE", 2,
			   asd_पढ़ो_reg_word(asd_ha, LmSEQ_REG0_MODE(lseq)
					     + moffs));
		asd_prपूर्णांकk(STR_16BIT, "MODE_FLAGS", 4,
			   asd_पढ़ो_reg_word(asd_ha, LmSEQ_MODE_FLAGS(lseq)
					     + moffs));
		asd_prपूर्णांकk(STR_16BIT, "RET_ADDR2", 0x6,
			   asd_पढ़ो_reg_word(asd_ha, LmSEQ_RET_ADDR2(lseq)
					     + moffs));
		asd_prपूर्णांकk(STR_16BIT, "RET_ADDR1", 0x8,
			   asd_पढ़ो_reg_word(asd_ha, LmSEQ_RET_ADDR1(lseq)
					     + moffs));
		asd_prपूर्णांकk(STR_8BIT, "OPCODE_TO_CSEQ", 0xB,
			   asd_पढ़ो_reg_byte(asd_ha, LmSEQ_OPCODE_TO_CSEQ(lseq)
					     + moffs));
		asd_prपूर्णांकk(STR_16BIT, "DATA_TO_CSEQ", 0xC,
			   asd_पढ़ो_reg_word(asd_ha, LmSEQ_DATA_TO_CSEQ(lseq)
					     + moffs));
	पूर्ण

	asd_prपूर्णांकk("LSEQ%d MDP 0 MODE 5 >>>>\n", lseq);
	moffs = LSEQ_MODE5_PAGE0_OFFSET;
	asd_prपूर्णांकk(STR_16BIT, "RET_ADDR", 0,
		   asd_पढ़ो_reg_word(asd_ha, LmSEQ_RET_ADDR(lseq) + moffs));
	asd_prपूर्णांकk(STR_16BIT, "REG0_MODE", 2,
		   asd_पढ़ो_reg_word(asd_ha, LmSEQ_REG0_MODE(lseq) + moffs));
	asd_prपूर्णांकk(STR_16BIT, "MODE_FLAGS", 4,
		   asd_पढ़ो_reg_word(asd_ha, LmSEQ_MODE_FLAGS(lseq) + moffs));
	asd_prपूर्णांकk(STR_16BIT, "RET_ADDR2", 0x6,
		   asd_पढ़ो_reg_word(asd_ha, LmSEQ_RET_ADDR2(lseq) + moffs));
	asd_prपूर्णांकk(STR_16BIT, "RET_ADDR1", 0x8,
		   asd_पढ़ो_reg_word(asd_ha, LmSEQ_RET_ADDR1(lseq) + moffs));
	asd_prपूर्णांकk(STR_8BIT, "OPCODE_TO_CSEQ", 0xB,
	   asd_पढ़ो_reg_byte(asd_ha, LmSEQ_OPCODE_TO_CSEQ(lseq) + moffs));
	asd_prपूर्णांकk(STR_16BIT, "DATA_TO_CSEQ", 0xC,
	   asd_पढ़ो_reg_word(asd_ha, LmSEQ_DATA_TO_CSEQ(lseq) + moffs));

	asd_prपूर्णांकk("LSEQ%d MDP 0 MODE 0 >>>>\n", lseq);
	PRINT_LMIP_word(asd_ha, lseq, FIRST_INV_DDB_SITE);
	PRINT_LMIP_word(asd_ha, lseq, EMPTY_TRANS_CTX);
	PRINT_LMIP_word(asd_ha, lseq, RESP_LEN);
	PRINT_LMIP_word(asd_ha, lseq, FIRST_INV_SCB_SITE);
	PRINT_LMIP_dword(asd_ha, lseq, INTEN_SAVE);
	PRINT_LMIP_byte(asd_ha, lseq, LINK_RST_FRM_LEN);
	PRINT_LMIP_byte(asd_ha, lseq, LINK_RST_PROTOCOL);
	PRINT_LMIP_byte(asd_ha, lseq, RESP_STATUS);
	PRINT_LMIP_byte(asd_ha, lseq, LAST_LOADED_SGE);
	PRINT_LMIP_byte(asd_ha, lseq, SAVE_SCBPTR);

	asd_prपूर्णांकk("LSEQ%d MDP 0 MODE 1 >>>>\n", lseq);
	PRINT_LMIP_word(asd_ha, lseq, Q_XMIT_HEAD);
	PRINT_LMIP_word(asd_ha, lseq, M1_EMPTY_TRANS_CTX);
	PRINT_LMIP_word(asd_ha, lseq, INI_CONN_TAG);
	PRINT_LMIP_byte(asd_ha, lseq, FAILED_OPEN_STATUS);
	PRINT_LMIP_byte(asd_ha, lseq, XMIT_REQUEST_TYPE);
	PRINT_LMIP_byte(asd_ha, lseq, M1_RESP_STATUS);
	PRINT_LMIP_byte(asd_ha, lseq, M1_LAST_LOADED_SGE);
	PRINT_LMIP_word(asd_ha, lseq, M1_SAVE_SCBPTR);

	asd_prपूर्णांकk("LSEQ%d MDP 0 MODE 2 >>>>\n", lseq);
	PRINT_LMIP_word(asd_ha, lseq, PORT_COUNTER);
	PRINT_LMIP_word(asd_ha, lseq, PM_TABLE_PTR);
	PRINT_LMIP_word(asd_ha, lseq, SATA_INTERLOCK_TMR_SAVE);
	PRINT_LMIP_word(asd_ha, lseq, IP_BITL);
	PRINT_LMIP_word(asd_ha, lseq, COPY_SMP_CONN_TAG);
	PRINT_LMIP_byte(asd_ha, lseq, P0M2_OFFS1AH);

	asd_prपूर्णांकk("LSEQ%d MDP 0 MODE 4/5 >>>>\n", lseq);
	PRINT_LMIP_byte(asd_ha, lseq, SAVED_OOB_STATUS);
	PRINT_LMIP_byte(asd_ha, lseq, SAVED_OOB_MODE);
	PRINT_LMIP_word(asd_ha, lseq, Q_LINK_HEAD);
	PRINT_LMIP_byte(asd_ha, lseq, LINK_RST_ERR);
	PRINT_LMIP_byte(asd_ha, lseq, SAVED_OOB_SIGNALS);
	PRINT_LMIP_byte(asd_ha, lseq, SAS_RESET_MODE);
	PRINT_LMIP_byte(asd_ha, lseq, LINK_RESET_RETRY_COUNT);
	PRINT_LMIP_byte(asd_ha, lseq, NUM_LINK_RESET_RETRIES);
	PRINT_LMIP_word(asd_ha, lseq, OOB_INT_ENABLES);
	PRINT_LMIP_word(asd_ha, lseq, NOTIFY_TIMER_TIMEOUT);
	PRINT_LMIP_word(asd_ha, lseq, NOTIFY_TIMER_DOWN_COUNT);

	asd_prपूर्णांकk("LSEQ%d MDP 1 MODE 0 >>>>\n", lseq);
	PRINT_LMIP_qword(asd_ha, lseq, SG_LIST_PTR_ADDR0);
	PRINT_LMIP_qword(asd_ha, lseq, SG_LIST_PTR_ADDR1);

	asd_prपूर्णांकk("LSEQ%d MDP 1 MODE 1 >>>>\n", lseq);
	PRINT_LMIP_qword(asd_ha, lseq, M1_SG_LIST_PTR_ADDR0);
	PRINT_LMIP_qword(asd_ha, lseq, M1_SG_LIST_PTR_ADDR1);

	asd_prपूर्णांकk("LSEQ%d MDP 1 MODE 2 >>>>\n", lseq);
	PRINT_LMIP_dword(asd_ha, lseq, INVALID_DWORD_COUNT);
	PRINT_LMIP_dword(asd_ha, lseq, DISPARITY_ERROR_COUNT);
	PRINT_LMIP_dword(asd_ha, lseq, LOSS_OF_SYNC_COUNT);

	asd_prपूर्णांकk("LSEQ%d MDP 1 MODE 4/5 >>>>\n", lseq);
	PRINT_LMIP_dword(asd_ha, lseq, FRAME_TYPE_MASK);
	PRINT_LMIP_dword(asd_ha, lseq, HASHED_SRC_ADDR_MASK_PRINT);
	PRINT_LMIP_byte(asd_ha, lseq, NUM_FILL_BYTES_MASK);
	PRINT_LMIP_word(asd_ha, lseq, TAG_MASK);
	PRINT_LMIP_word(asd_ha, lseq, TARGET_PORT_XFER_TAG);
	PRINT_LMIP_dword(asd_ha, lseq, DATA_OFFSET);

	asd_prपूर्णांकk("LSEQ%d MDP 2 MODE 0 >>>>\n", lseq);
	PRINT_LMIP_dword(asd_ha, lseq, SMP_RCV_TIMER_TERM_TS);
	PRINT_LMIP_byte(asd_ha, lseq, DEVICE_BITS);
	PRINT_LMIP_word(asd_ha, lseq, SDB_DDB);
	PRINT_LMIP_word(asd_ha, lseq, SDB_NUM_TAGS);
	PRINT_LMIP_word(asd_ha, lseq, SDB_CURR_TAG);

	asd_prपूर्णांकk("LSEQ%d MDP 2 MODE 1 >>>>\n", lseq);
	PRINT_LMIP_qword(asd_ha, lseq, TX_ID_ADDR_FRAME);
	PRINT_LMIP_dword(asd_ha, lseq, OPEN_TIMER_TERM_TS);
	PRINT_LMIP_dword(asd_ha, lseq, SRST_AS_TIMER_TERM_TS);
	PRINT_LMIP_dword(asd_ha, lseq, LAST_LOADED_SG_EL);

	asd_prपूर्णांकk("LSEQ%d MDP 2 MODE 2 >>>>\n", lseq);
	PRINT_LMIP_dword(asd_ha, lseq, CLOSE_TIMER_TERM_TS);
	PRINT_LMIP_dword(asd_ha, lseq, BREAK_TIMER_TERM_TS);
	PRINT_LMIP_dword(asd_ha, lseq, DWS_RESET_TIMER_TERM_TS);
	PRINT_LMIP_dword(asd_ha, lseq, SATA_INTERLOCK_TIMER_TERM_TS);
	PRINT_LMIP_dword(asd_ha, lseq, MCTL_TIMER_TERM_TS);

	asd_prपूर्णांकk("LSEQ%d MDP 2 MODE 4/5 >>>>\n", lseq);
	PRINT_LMIP_dword(asd_ha, lseq, COMINIT_TIMER_TERM_TS);
	PRINT_LMIP_dword(asd_ha, lseq, RCV_ID_TIMER_TERM_TS);
	PRINT_LMIP_dword(asd_ha, lseq, RCV_FIS_TIMER_TERM_TS);
	PRINT_LMIP_dword(asd_ha, lseq, DEV_PRES_TIMER_TERM_TS);
पूर्ण

/**
 * asd_dump_seq_state -- dump CSEQ and LSEQ states
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @lseq_mask: mask of LSEQs of पूर्णांकerest
 */
व्योम asd_dump_seq_state(काष्ठा asd_ha_काष्ठा *asd_ha, u8 lseq_mask)
अणु
	पूर्णांक lseq;

	asd_dump_cseq_state(asd_ha);

	अगर (lseq_mask != 0)
		क्रम_each_sequencer(lseq_mask, lseq_mask, lseq)
			asd_dump_lseq_state(asd_ha, lseq);
पूर्ण

व्योम asd_dump_frame_rcvd(काष्ठा asd_phy *phy,
			 काष्ठा करोne_list_काष्ठा *dl)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	चयन ((dl->status_block[1] & 0x70) >> 3) अणु
	हाल SAS_PROTOCOL_STP:
		ASD_DPRINTK("STP proto device-to-host FIS:\n");
		अवरोध;
	शेष:
	हाल SAS_PROTOCOL_SSP:
		ASD_DPRINTK("SAS proto IDENTIFY:\n");
		अवरोध;
	पूर्ण
	spin_lock_irqsave(&phy->sas_phy.frame_rcvd_lock, flags);
	क्रम (i = 0; i < phy->sas_phy.frame_rcvd_size; i+=4)
		ASD_DPRINTK("%02x: %02x %02x %02x %02x\n",
			    i,
			    phy->frame_rcvd[i],
			    phy->frame_rcvd[i+1],
			    phy->frame_rcvd[i+2],
			    phy->frame_rcvd[i+3]);
	spin_unlock_irqrestore(&phy->sas_phy.frame_rcvd_lock, flags);
पूर्ण

#पूर्ण_अगर /* ASD_DEBUG */
