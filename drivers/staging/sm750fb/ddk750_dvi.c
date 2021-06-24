<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा USE_DVICHIP
#अगर_घोषित USE_DVICHIP
#समावेश "ddk750_chip.h"
#समावेश "ddk750_reg.h"
#समावेश "ddk750_dvi.h"
#समावेश "ddk750_sii164.h"

/*
 * This global variable contains all the supported driver and its corresponding
 * function API. Please set the function poपूर्णांकer to शून्य whenever the function
 * is not supported.
 */
अटल काष्ठा dvi_ctrl_device g_dcftSupportedDviController[] = अणु
#अगर_घोषित DVI_CTRL_SII164
	अणु
		.pfnInit = sii164InitChip,
		.pfnGetVenकरोrId = sii164GetVenकरोrID,
		.pfnGetDeviceId = sii164GetDeviceID,
#अगर_घोषित SII164_FULL_FUNCTIONS
		.pfnResetChip = sii164ResetChip,
		.pfnGetChipString = sii164GetChipString,
		.pfnSetPower = sii164SetPower,
		.pfnEnableHotPlugDetection = sii164EnableHotPlugDetection,
		.pfnIsConnected = sii164IsConnected,
		.pfnCheckInterrupt = sii164CheckInterrupt,
		.pfnClearInterrupt = sii164ClearInterrupt,
#पूर्ण_अगर
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

पूर्णांक dviInit(अचिन्हित अक्षर edge_select,
	    अचिन्हित अक्षर bus_select,
	    अचिन्हित अक्षर dual_edge_clk_select,
	    अचिन्हित अक्षर hsync_enable,
	    अचिन्हित अक्षर vsync_enable,
	    अचिन्हित अक्षर deskew_enable,
	    अचिन्हित अक्षर deskew_setting,
	    अचिन्हित अक्षर continuous_sync_enable,
	    अचिन्हित अक्षर pll_filter_enable,
	    अचिन्हित अक्षर pll_filter_value)
अणु
	काष्ठा dvi_ctrl_device *pCurrentDviCtrl;

	pCurrentDviCtrl = g_dcftSupportedDviController;
	अगर (pCurrentDviCtrl->pfnInit) अणु
		वापस pCurrentDviCtrl->pfnInit(edge_select,
						bus_select,
						dual_edge_clk_select,
						hsync_enable,
						vsync_enable,
						deskew_enable,
						deskew_setting,
						continuous_sync_enable,
						pll_filter_enable,
						pll_filter_value);
	पूर्ण
	वापस -1; /* error */
पूर्ण

#पूर्ण_अगर
