<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "ddk750_reg.h"
#समावेश "ddk750_mode.h"
#समावेश "ddk750_chip.h"

/*
 * SM750LE only:
 * This function takes care extra रेजिस्टरs and bit fields required to set
 * up a mode in SM750LE
 *
 * Explanation about Display Control रेजिस्टर:
 * HW only supports 7 predefined pixel घड़ीs, and घड़ी select is
 * in bit 29:27 of Display Control रेजिस्टर.
 */
अटल अचिन्हित दीर्घ
displayControlAdjust_SM750LE(काष्ठा mode_parameter *pModeParam,
			     अचिन्हित दीर्घ dispControl)
अणु
	अचिन्हित दीर्घ x, y;

	x = pModeParam->horizontal_display_end;
	y = pModeParam->vertical_display_end;

	/*
	 * SM750LE has to set up the top-left and bottom-right
	 * रेजिस्टरs as well.
	 * Note that normal SM750/SM718 only use those two रेजिस्टर क्रम
	 * स्वतः-centering mode.
	 */
	poke32(CRT_AUTO_CENTERING_TL, 0);

	poke32(CRT_AUTO_CENTERING_BR,
	       (((y - 1) << CRT_AUTO_CENTERING_BR_BOTTOM_SHIFT) &
		CRT_AUTO_CENTERING_BR_BOTTOM_MASK) |
	       ((x - 1) & CRT_AUTO_CENTERING_BR_RIGHT_MASK));

	/*
	 * Assume common fields in dispControl have been properly set beक्रमe
	 * calling this function.
	 * This function only sets the extra fields in dispControl.
	 */

	/* Clear bit 29:27 of display control रेजिस्टर */
	dispControl &= ~CRT_DISPLAY_CTRL_CLK_MASK;

	/* Set bit 29:27 of display control रेजिस्टर क्रम the right घड़ी */
	/* Note that SM750LE only need to supported 7 resolutions. */
	अगर (x == 800 && y == 600)
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL41;
	अन्यथा अगर (x == 1024 && y == 768)
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL65;
	अन्यथा अगर (x == 1152 && y == 864)
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL80;
	अन्यथा अगर (x == 1280 && y == 768)
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL80;
	अन्यथा अगर (x == 1280 && y == 720)
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL74;
	अन्यथा अगर (x == 1280 && y == 960)
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL108;
	अन्यथा अगर (x == 1280 && y == 1024)
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL108;
	अन्यथा /* शेष to VGA घड़ी */
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL25;

	/* Set bit 25:24 of display controller */
	dispControl |= (CRT_DISPLAY_CTRL_CRTSELECT | CRT_DISPLAY_CTRL_RGBBIT);

	/* Set bit 14 of display controller */
	dispControl |= DISPLAY_CTRL_CLOCK_PHASE;

	poke32(CRT_DISPLAY_CTRL, dispControl);

	वापस dispControl;
पूर्ण

/* only timing related रेजिस्टरs will be  programed */
अटल पूर्णांक programModeRegisters(काष्ठा mode_parameter *pModeParam,
				काष्ठा pll_value *pll)
अणु
	पूर्णांक ret = 0;
	पूर्णांक cnt = 0;
	अचिन्हित पूर्णांक पंचांगp, reg;

	अगर (pll->घड़ी_प्रकारype == SECONDARY_PLL) अणु
		/* programe secondary pixel घड़ी */
		poke32(CRT_PLL_CTRL, sm750_क्रमmat_pll_reg(pll));

		पंचांगp = ((pModeParam->horizontal_total - 1) <<
		       CRT_HORIZONTAL_TOTAL_TOTAL_SHIFT) &
		     CRT_HORIZONTAL_TOTAL_TOTAL_MASK;
		पंचांगp |= (pModeParam->horizontal_display_end - 1) &
		      CRT_HORIZONTAL_TOTAL_DISPLAY_END_MASK;

		poke32(CRT_HORIZONTAL_TOTAL, पंचांगp);

		पंचांगp = (pModeParam->horizontal_sync_width <<
		       CRT_HORIZONTAL_SYNC_WIDTH_SHIFT) &
		     CRT_HORIZONTAL_SYNC_WIDTH_MASK;
		पंचांगp |= (pModeParam->horizontal_sync_start - 1) &
		      CRT_HORIZONTAL_SYNC_START_MASK;

		poke32(CRT_HORIZONTAL_SYNC, पंचांगp);

		पंचांगp = ((pModeParam->vertical_total - 1) <<
		       CRT_VERTICAL_TOTAL_TOTAL_SHIFT) &
		     CRT_VERTICAL_TOTAL_TOTAL_MASK;
		पंचांगp |= (pModeParam->vertical_display_end - 1) &
		      CRT_VERTICAL_TOTAL_DISPLAY_END_MASK;

		poke32(CRT_VERTICAL_TOTAL, पंचांगp);

		पंचांगp = ((pModeParam->vertical_sync_height <<
		       CRT_VERTICAL_SYNC_HEIGHT_SHIFT)) &
		     CRT_VERTICAL_SYNC_HEIGHT_MASK;
		पंचांगp |= (pModeParam->vertical_sync_start - 1) &
		      CRT_VERTICAL_SYNC_START_MASK;

		poke32(CRT_VERTICAL_SYNC, पंचांगp);

		पंचांगp = DISPLAY_CTRL_TIMING | DISPLAY_CTRL_PLANE;
		अगर (pModeParam->vertical_sync_polarity)
			पंचांगp |= DISPLAY_CTRL_VSYNC_PHASE;
		अगर (pModeParam->horizontal_sync_polarity)
			पंचांगp |= DISPLAY_CTRL_HSYNC_PHASE;

		अगर (sm750_get_chip_type() == SM750LE) अणु
			displayControlAdjust_SM750LE(pModeParam, पंचांगp);
		पूर्ण अन्यथा अणु
			reg = peek32(CRT_DISPLAY_CTRL) &
				~(DISPLAY_CTRL_VSYNC_PHASE |
				  DISPLAY_CTRL_HSYNC_PHASE |
				  DISPLAY_CTRL_TIMING | DISPLAY_CTRL_PLANE);

			poke32(CRT_DISPLAY_CTRL, पंचांगp | reg);
		पूर्ण

	पूर्ण अन्यथा अगर (pll->घड़ी_प्रकारype == PRIMARY_PLL) अणु
		अचिन्हित पूर्णांक reserved;

		poke32(PANEL_PLL_CTRL, sm750_क्रमmat_pll_reg(pll));

		reg = ((pModeParam->horizontal_total - 1) <<
			PANEL_HORIZONTAL_TOTAL_TOTAL_SHIFT) &
			PANEL_HORIZONTAL_TOTAL_TOTAL_MASK;
		reg |= ((pModeParam->horizontal_display_end - 1) &
			PANEL_HORIZONTAL_TOTAL_DISPLAY_END_MASK);
		poke32(PANEL_HORIZONTAL_TOTAL, reg);

		poke32(PANEL_HORIZONTAL_SYNC,
		       ((pModeParam->horizontal_sync_width <<
			 PANEL_HORIZONTAL_SYNC_WIDTH_SHIFT) &
			PANEL_HORIZONTAL_SYNC_WIDTH_MASK) |
		       ((pModeParam->horizontal_sync_start - 1) &
			PANEL_HORIZONTAL_SYNC_START_MASK));

		poke32(PANEL_VERTICAL_TOTAL,
		       (((pModeParam->vertical_total - 1) <<
			 PANEL_VERTICAL_TOTAL_TOTAL_SHIFT) &
			PANEL_VERTICAL_TOTAL_TOTAL_MASK) |
		       ((pModeParam->vertical_display_end - 1) &
			PANEL_VERTICAL_TOTAL_DISPLAY_END_MASK));

		poke32(PANEL_VERTICAL_SYNC,
		       ((pModeParam->vertical_sync_height <<
			 PANEL_VERTICAL_SYNC_HEIGHT_SHIFT) &
			PANEL_VERTICAL_SYNC_HEIGHT_MASK) |
		       ((pModeParam->vertical_sync_start - 1) &
			PANEL_VERTICAL_SYNC_START_MASK));

		पंचांगp = DISPLAY_CTRL_TIMING | DISPLAY_CTRL_PLANE;
		अगर (pModeParam->vertical_sync_polarity)
			पंचांगp |= DISPLAY_CTRL_VSYNC_PHASE;
		अगर (pModeParam->horizontal_sync_polarity)
			पंचांगp |= DISPLAY_CTRL_HSYNC_PHASE;
		अगर (pModeParam->घड़ी_phase_polarity)
			पंचांगp |= DISPLAY_CTRL_CLOCK_PHASE;

		reserved = PANEL_DISPLAY_CTRL_RESERVED_MASK |
			PANEL_DISPLAY_CTRL_VSYNC;

		reg = (peek32(PANEL_DISPLAY_CTRL) & ~reserved) &
			~(DISPLAY_CTRL_CLOCK_PHASE | DISPLAY_CTRL_VSYNC_PHASE |
			  DISPLAY_CTRL_HSYNC_PHASE | DISPLAY_CTRL_TIMING |
			  DISPLAY_CTRL_PLANE);

		/*
		 * May a hardware bug or just my test chip (not confirmed).
		 * PANEL_DISPLAY_CTRL रेजिस्टर seems requiring few ग_लिखोs
		 * beक्रमe a value can be successfully written in.
		 * Added some masks to mask out the reserved bits.
		 * Note: This problem happens by design. The hardware will रुको
		 *       क्रम the next vertical sync to turn on/off the plane.
		 */
		poke32(PANEL_DISPLAY_CTRL, पंचांगp | reg);

		जबतक ((peek32(PANEL_DISPLAY_CTRL) & ~reserved) !=
			(पंचांगp | reg)) अणु
			cnt++;
			अगर (cnt > 1000)
				अवरोध;
			poke32(PANEL_DISPLAY_CTRL, पंचांगp | reg);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक ddk750_setModeTiming(काष्ठा mode_parameter *parm, क्रमागत घड़ी_प्रकारype घड़ी)
अणु
	काष्ठा pll_value pll;

	pll.input_freq = DEFAULT_INPUT_CLOCK;
	pll.घड़ी_प्रकारype = घड़ी;

	sm750_calc_pll_value(parm->pixel_घड़ी, &pll);
	अगर (sm750_get_chip_type() == SM750LE) अणु
		/* set graphic mode via IO method */
		outb_p(0x88, 0x3d4);
		outb_p(0x06, 0x3d5);
	पूर्ण
	programModeRegisters(parm, &pll);
	वापस 0;
पूर्ण
