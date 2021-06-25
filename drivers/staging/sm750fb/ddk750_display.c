<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "ddk750_reg.h"
#समावेश "ddk750_chip.h"
#समावेश "ddk750_display.h"
#समावेश "ddk750_power.h"
#समावेश "ddk750_dvi.h"

अटल व्योम set_display_control(पूर्णांक ctrl, पूर्णांक disp_state)
अणु
	/* state != 0 means turn on both timing & plane en_bit */
	अचिन्हित दीर्घ reg, val, reserved;
	पूर्णांक cnt = 0;

	अगर (!ctrl) अणु
		reg = PANEL_DISPLAY_CTRL;
		reserved = PANEL_DISPLAY_CTRL_RESERVED_MASK;
	पूर्ण अन्यथा अणु
		reg = CRT_DISPLAY_CTRL;
		reserved = CRT_DISPLAY_CTRL_RESERVED_MASK;
	पूर्ण

	val = peek32(reg);
	अगर (disp_state) अणु
		/*
		 * Timing should be enabled first beक्रमe enabling the
		 * plane because changing at the same समय करोes not
		 * guarantee that the plane will also enabled or
		 * disabled.
		 */
		val |= DISPLAY_CTRL_TIMING;
		poke32(reg, val);

		val |= DISPLAY_CTRL_PLANE;

		/*
		 * Somehow the रेजिस्टर value on the plane is not set
		 * until a few delay. Need to ग_लिखो and पढ़ो it a
		 * couple बार
		 */
		करो अणु
			cnt++;
			poke32(reg, val);
		पूर्ण जबतक ((peek32(reg) & ~reserved) != (val & ~reserved));
		pr_debug("Set Plane enbit:after tried %d times\n", cnt);
	पूर्ण अन्यथा अणु
		/*
		 * When turning off, there is no rule on the
		 * programming sequence since whenever the घड़ी is
		 * off, then it करोes not matter whether the plane is
		 * enabled or disabled.  Note: Modअगरying the plane bit
		 * will take effect on the next vertical sync. Need to
		 * find out अगर it is necessary to रुको क्रम 1 vsync
		 * beक्रमe modअगरying the timing enable bit.
		 */
		val &= ~DISPLAY_CTRL_PLANE;
		poke32(reg, val);

		val &= ~DISPLAY_CTRL_TIMING;
		poke32(reg, val);
	पूर्ण
पूर्ण

अटल व्योम primary_रुको_vertical_sync(पूर्णांक delay)
अणु
	अचिन्हित पूर्णांक status;

	/*
	 * Do not रुको when the Primary PLL is off or display control is
	 * alपढ़ोy off. This will prevent the software to रुको क्रमever.
	 */
	अगर (!(peek32(PANEL_PLL_CTRL) & PLL_CTRL_POWER) ||
	    !(peek32(PANEL_DISPLAY_CTRL) & DISPLAY_CTRL_TIMING))
		वापस;

	जबतक (delay-- > 0) अणु
		/* Wait क्रम end of vsync. */
		करो अणु
			status = peek32(SYSTEM_CTRL);
		पूर्ण जबतक (status & SYSTEM_CTRL_PANEL_VSYNC_ACTIVE);

		/* Wait क्रम start of vsync. */
		करो अणु
			status = peek32(SYSTEM_CTRL);
		पूर्ण जबतक (!(status & SYSTEM_CTRL_PANEL_VSYNC_ACTIVE));
	पूर्ण
पूर्ण

अटल व्योम sw_panel_घातer_sequence(पूर्णांक disp, पूर्णांक delay)
अणु
	अचिन्हित पूर्णांक reg;

	/* disp should be 1 to खोलो sequence */
	reg = peek32(PANEL_DISPLAY_CTRL);
	reg |= (disp ? PANEL_DISPLAY_CTRL_FPEN : 0);
	poke32(PANEL_DISPLAY_CTRL, reg);
	primary_रुको_vertical_sync(delay);

	reg = peek32(PANEL_DISPLAY_CTRL);
	reg |= (disp ? PANEL_DISPLAY_CTRL_DATA : 0);
	poke32(PANEL_DISPLAY_CTRL, reg);
	primary_रुको_vertical_sync(delay);

	reg = peek32(PANEL_DISPLAY_CTRL);
	reg |= (disp ? PANEL_DISPLAY_CTRL_VBIASEN : 0);
	poke32(PANEL_DISPLAY_CTRL, reg);
	primary_रुको_vertical_sync(delay);

	reg = peek32(PANEL_DISPLAY_CTRL);
	reg |= (disp ? PANEL_DISPLAY_CTRL_FPEN : 0);
	poke32(PANEL_DISPLAY_CTRL, reg);
	primary_रुको_vertical_sync(delay);
पूर्ण

व्योम ddk750_set_logical_disp_out(क्रमागत disp_output output)
अणु
	अचिन्हित पूर्णांक reg;

	अगर (output & PNL_2_USAGE) अणु
		/* set panel path controller select */
		reg = peek32(PANEL_DISPLAY_CTRL);
		reg &= ~PANEL_DISPLAY_CTRL_SELECT_MASK;
		reg |= (((output & PNL_2_MASK) >> PNL_2_OFFSET) <<
			PANEL_DISPLAY_CTRL_SELECT_SHIFT);
		poke32(PANEL_DISPLAY_CTRL, reg);
	पूर्ण

	अगर (output & CRT_2_USAGE) अणु
		/* set crt path controller select */
		reg = peek32(CRT_DISPLAY_CTRL);
		reg &= ~CRT_DISPLAY_CTRL_SELECT_MASK;
		reg |= (((output & CRT_2_MASK) >> CRT_2_OFFSET) <<
			CRT_DISPLAY_CTRL_SELECT_SHIFT);
		/*se blank off */
		reg &= ~CRT_DISPLAY_CTRL_BLANK;
		poke32(CRT_DISPLAY_CTRL, reg);
	पूर्ण

	अगर (output & PRI_TP_USAGE) अणु
		/* set primary timing and plane en_bit */
		set_display_control(0, (output & PRI_TP_MASK) >> PRI_TP_OFFSET);
	पूर्ण

	अगर (output & SEC_TP_USAGE) अणु
		/* set secondary timing and plane en_bit*/
		set_display_control(1, (output & SEC_TP_MASK) >> SEC_TP_OFFSET);
	पूर्ण

	अगर (output & PNL_SEQ_USAGE) अणु
		/* set  panel sequence */
		sw_panel_घातer_sequence((output & PNL_SEQ_MASK) >>
					PNL_SEQ_OFFSET, 4);
	पूर्ण

	अगर (output & DAC_USAGE)
		set_DAC((output & DAC_MASK) >> DAC_OFFSET);

	अगर (output & DPMS_USAGE)
		ddk750_set_dpms((output & DPMS_MASK) >> DPMS_OFFSET);
पूर्ण
