<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DDK750_DVI_H__
#घोषणा DDK750_DVI_H__

/* dvi chip stuffs काष्ठाros */

प्रकार दीर्घ (*PFN_DVICTRL_INIT)(अचिन्हित अक्षर edgeSelect,
				 अचिन्हित अक्षर busSelect,
				 अचिन्हित अक्षर dualEdgeClkSelect,
				 अचिन्हित अक्षर hsyncEnable,
				 अचिन्हित अक्षर vsyncEnable,
				 अचिन्हित अक्षर deskewEnable,
				 अचिन्हित अक्षर deskewSetting,
				 अचिन्हित अक्षर continuousSyncEnable,
				 अचिन्हित अक्षर pllFilterEnable,
				 अचिन्हित अक्षर pllFilterValue);

प्रकार व्योम (*PFN_DVICTRL_RESETCHIP)(व्योम);
प्रकार अक्षर* (*PFN_DVICTRL_GETCHIPSTRING)(व्योम);
प्रकार अचिन्हित लघु (*PFN_DVICTRL_GETVENDORID)(व्योम);
प्रकार अचिन्हित लघु (*PFN_DVICTRL_GETDEVICEID)(व्योम);
प्रकार व्योम (*PFN_DVICTRL_SETPOWER)(अचिन्हित अक्षर घातerUp);
प्रकार व्योम (*PFN_DVICTRL_HOTPLUGDETECTION)(अचिन्हित अक्षर enableHotPlug);
प्रकार अचिन्हित अक्षर (*PFN_DVICTRL_ISCONNECTED)(व्योम);
प्रकार अचिन्हित अक्षर (*PFN_DVICTRL_CHECKINTERRUPT)(व्योम);
प्रकार व्योम (*PFN_DVICTRL_CLEARINTERRUPT)(व्योम);

/* Structure to hold all the function poपूर्णांकer to the DVI Controller. */
काष्ठा dvi_ctrl_device अणु
	PFN_DVICTRL_INIT		pfnInit;
	PFN_DVICTRL_RESETCHIP		pfnResetChip;
	PFN_DVICTRL_GETCHIPSTRING	pfnGetChipString;
	PFN_DVICTRL_GETVENDORID		pfnGetVenकरोrId;
	PFN_DVICTRL_GETDEVICEID		pfnGetDeviceId;
	PFN_DVICTRL_SETPOWER		pfnSetPower;
	PFN_DVICTRL_HOTPLUGDETECTION	pfnEnableHotPlugDetection;
	PFN_DVICTRL_ISCONNECTED		pfnIsConnected;
	PFN_DVICTRL_CHECKINTERRUPT	pfnCheckInterrupt;
	PFN_DVICTRL_CLEARINTERRUPT	pfnClearInterrupt;
पूर्ण;

#घोषणा DVI_CTRL_SII164

/* dvi functions prototype */
पूर्णांक dviInit(अचिन्हित अक्षर edgeSelect,
	    अचिन्हित अक्षर busSelect,
	    अचिन्हित अक्षर dualEdgeClkSelect,
	    अचिन्हित अक्षर hsyncEnable,
	    अचिन्हित अक्षर vsyncEnable,
	    अचिन्हित अक्षर deskewEnable,
	    अचिन्हित अक्षर deskewSetting,
	    अचिन्हित अक्षर continuousSyncEnable,
	    अचिन्हित अक्षर pllFilterEnable,
	    अचिन्हित अक्षर pllFilterValue);

#पूर्ण_अगर

