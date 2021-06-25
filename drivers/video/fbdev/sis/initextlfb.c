<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SiS 300/540/630[S]/730[S]
 * SiS 315[E|PRO]/550/[M]65x/[M]66x[F|M|G]X/[M]74x[GX]/330/[M]76x[GX]
 * XGI V3XT/V5/V8, Z7
 * frame buffer driver क्रम Linux kernels >= 2.4.14 and >=2.6.3
 *
 * Linux kernel specअगरic extensions to init.c/init301.c
 *
 * Copyright (C) 2001-2005 Thomas Winischhofer, Vienna, Austria.
 *
 * Author:	Thomas Winischhofer <thomas@winischhofer.net>
 */

#समावेश "initdef.h"
#समावेश "vgatypes.h"
#समावेश "vstruct.h"

#समावेश <linux/types.h>
#समावेश <linux/fb.h>

पूर्णांक		sisfb_mode_rate_to_dघड़ी(काष्ठा SiS_Private *SiS_Pr,
			अचिन्हित अक्षर modeno, अचिन्हित अक्षर rateindex);
पूर्णांक		sisfb_mode_rate_to_ddata(काष्ठा SiS_Private *SiS_Pr, अचिन्हित अक्षर modeno,
			अचिन्हित अक्षर rateindex, काष्ठा fb_var_screeninfo *var);
bool		sisfb_gettotalfrommode(काष्ठा SiS_Private *SiS_Pr, अचिन्हित अक्षर modeno,
			पूर्णांक *htotal, पूर्णांक *vtotal, अचिन्हित अक्षर rateindex);

बाह्य bool	SiSInitPtr(काष्ठा SiS_Private *SiS_Pr);
बाह्य bool	SiS_SearchModeID(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु *ModeNo,
			अचिन्हित लघु *ModeIdIndex);
बाह्य व्योम	SiS_Generic_ConvertCRData(काष्ठा SiS_Private *SiS_Pr, अचिन्हित अक्षर *crdata,
			पूर्णांक xres, पूर्णांक yres, काष्ठा fb_var_screeninfo *var, bool ग_लिखोres);

पूर्णांक
sisfb_mode_rate_to_dघड़ी(काष्ठा SiS_Private *SiS_Pr, अचिन्हित अक्षर modeno,
			अचिन्हित अक्षर rateindex)
अणु
    अचिन्हित लघु ModeNo = modeno;
    अचिन्हित लघु ModeIdIndex = 0, ClockIndex = 0;
    अचिन्हित लघु RRTI = 0;
    पूर्णांक Clock;

    अगर(!SiSInitPtr(SiS_Pr)) वापस 65000;

    अगर(rateindex > 0) rateindex--;

#अगर_घोषित CONFIG_FB_SIS_315
    चयन(ModeNo) अणु
    हाल 0x5a: ModeNo = 0x50; अवरोध;
    हाल 0x5b: ModeNo = 0x56;
    पूर्ण
#पूर्ण_अगर

    अगर(!(SiS_SearchModeID(SiS_Pr, &ModeNo, &ModeIdIndex))) अणु
       prपूर्णांकk(KERN_ERR "Could not find mode %x\n", ModeNo);
       वापस 65000;
    पूर्ण

    RRTI = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].REFindex;

    अगर(SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag & HaveWideTiming) अणु
       अगर(SiS_Pr->SiS_UseWide == 1) अणु
	  /* Wide screen: Ignore rateindex */
	  ClockIndex = SiS_Pr->SiS_RefIndex[RRTI].Ext_CRTVCLK_WIDE;
       पूर्ण अन्यथा अणु
	  RRTI += rateindex;
	  ClockIndex = SiS_Pr->SiS_RefIndex[RRTI].Ext_CRTVCLK_NORM;
       पूर्ण
    पूर्ण अन्यथा अणु
       RRTI += rateindex;
       ClockIndex = SiS_Pr->SiS_RefIndex[RRTI].Ext_CRTVCLK;
    पूर्ण

    Clock = SiS_Pr->SiS_VCLKData[ClockIndex].CLOCK * 1000;

    वापस Clock;
पूर्ण

पूर्णांक
sisfb_mode_rate_to_ddata(काष्ठा SiS_Private *SiS_Pr, अचिन्हित अक्षर modeno,
			अचिन्हित अक्षर rateindex, काष्ठा fb_var_screeninfo *var)
अणु
    अचिन्हित लघु ModeNo = modeno;
    अचिन्हित लघु ModeIdIndex = 0, index = 0, RRTI = 0;
    पूर्णांक            j;

    अगर(!SiSInitPtr(SiS_Pr)) वापस 0;

    अगर(rateindex > 0) rateindex--;

#अगर_घोषित CONFIG_FB_SIS_315
    चयन(ModeNo) अणु
       हाल 0x5a: ModeNo = 0x50; अवरोध;
       हाल 0x5b: ModeNo = 0x56;
    पूर्ण
#पूर्ण_अगर

    अगर(!(SiS_SearchModeID(SiS_Pr, &ModeNo, &ModeIdIndex))) वापस 0;

    RRTI = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].REFindex;
    अगर(SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag & HaveWideTiming) अणु
       अगर(SiS_Pr->SiS_UseWide == 1) अणु
	  /* Wide screen: Ignore rateindex */
	  index = SiS_Pr->SiS_RefIndex[RRTI].Ext_CRT1CRTC_WIDE;
       पूर्ण अन्यथा अणु
	  RRTI += rateindex;
	  index = SiS_Pr->SiS_RefIndex[RRTI].Ext_CRT1CRTC_NORM;
       पूर्ण
    पूर्ण अन्यथा अणु
       RRTI += rateindex;
       index = SiS_Pr->SiS_RefIndex[RRTI].Ext_CRT1CRTC;
    पूर्ण

    SiS_Generic_ConvertCRData(SiS_Pr,
			(अचिन्हित अक्षर *)&SiS_Pr->SiS_CRT1Table[index].CR[0],
			SiS_Pr->SiS_RefIndex[RRTI].XRes,
			SiS_Pr->SiS_RefIndex[RRTI].YRes,
			var, false);

    अगर(SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag & 0x8000)
       var->sync &= ~FB_SYNC_VERT_HIGH_ACT;
    अन्यथा
       var->sync |= FB_SYNC_VERT_HIGH_ACT;

    अगर(SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag & 0x4000)
       var->sync &= ~FB_SYNC_HOR_HIGH_ACT;
    अन्यथा
       var->sync |= FB_SYNC_HOR_HIGH_ACT;

    var->vmode = FB_VMODE_NONINTERLACED;
    अगर(SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag & 0x0080)
       var->vmode = FB_VMODE_INTERLACED;
    अन्यथा अणु
       j = 0;
       जबतक(SiS_Pr->SiS_EModeIDTable[j].Ext_ModeID != 0xff) अणु
	  अगर(SiS_Pr->SiS_EModeIDTable[j].Ext_ModeID ==
	                  SiS_Pr->SiS_RefIndex[RRTI].ModeID) अणु
	      अगर(SiS_Pr->SiS_EModeIDTable[j].Ext_ModeFlag & DoubleScanMode) अणु
	      	  var->vmode = FB_VMODE_DOUBLE;
	      पूर्ण
	      अवरोध;
	  पूर्ण
	  j++;
       पूर्ण
    पूर्ण

    अगर((var->vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED) अणु
#अगर 0  /* Do this? */
       var->upper_margin <<= 1;
       var->lower_margin <<= 1;
       var->vsync_len <<= 1;
#पूर्ण_अगर
    पूर्ण अन्यथा अगर((var->vmode & FB_VMODE_MASK) == FB_VMODE_DOUBLE) अणु
       var->upper_margin >>= 1;
       var->lower_margin >>= 1;
       var->vsync_len >>= 1;
    पूर्ण

    वापस 1;
पूर्ण

bool
sisfb_gettotalfrommode(काष्ठा SiS_Private *SiS_Pr, अचिन्हित अक्षर modeno, पूर्णांक *htotal,
			पूर्णांक *vtotal, अचिन्हित अक्षर rateindex)
अणु
    अचिन्हित लघु ModeNo = modeno;
    अचिन्हित लघु ModeIdIndex = 0, CRT1Index = 0;
    अचिन्हित लघु RRTI = 0;
    अचिन्हित अक्षर  sr_data, cr_data, cr_data2;

    अगर(!SiSInitPtr(SiS_Pr)) वापस false;

    अगर(rateindex > 0) rateindex--;

#अगर_घोषित CONFIG_FB_SIS_315
    चयन(ModeNo) अणु
       हाल 0x5a: ModeNo = 0x50; अवरोध;
       हाल 0x5b: ModeNo = 0x56;
    पूर्ण
#पूर्ण_अगर

    अगर(!(SiS_SearchModeID(SiS_Pr, &ModeNo, &ModeIdIndex))) वापस false;

    RRTI = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].REFindex;
    अगर(SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag & HaveWideTiming) अणु
       अगर(SiS_Pr->SiS_UseWide == 1) अणु
	  /* Wide screen: Ignore rateindex */
	  CRT1Index = SiS_Pr->SiS_RefIndex[RRTI].Ext_CRT1CRTC_WIDE;
       पूर्ण अन्यथा अणु
	  RRTI += rateindex;
	  CRT1Index = SiS_Pr->SiS_RefIndex[RRTI].Ext_CRT1CRTC_NORM;
       पूर्ण
    पूर्ण अन्यथा अणु
       RRTI += rateindex;
       CRT1Index = SiS_Pr->SiS_RefIndex[RRTI].Ext_CRT1CRTC;
    पूर्ण

    sr_data = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[14];
    cr_data = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[0];
    *htotal = (((cr_data & 0xff) | ((अचिन्हित लघु) (sr_data & 0x03) << 8)) + 5) * 8;

    sr_data = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[13];
    cr_data = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[6];
    cr_data2 = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[7];
    *vtotal = ((cr_data & 0xFF) |
	       ((अचिन्हित लघु)(cr_data2 & 0x01) <<  8) |
	       ((अचिन्हित लघु)(cr_data2 & 0x20) <<  4) |
	       ((अचिन्हित लघु)(sr_data  & 0x01) << 10)) + 2;

    अगर(SiS_Pr->SiS_RefIndex[RRTI].Ext_InfoFlag & InterlaceMode)
       *vtotal *= 2;

    वापस true;
पूर्ण



