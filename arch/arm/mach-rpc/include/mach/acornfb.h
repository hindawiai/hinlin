<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-rpc/include/mach/acornfb.h
 *
 *  Copyright (C) 1999 Russell King
 *
 *  AcornFB architecture specअगरic code
 */

#घोषणा acornfb_bandwidth(var) ((var)->pixघड़ी * 8 / (var)->bits_per_pixel)

अटल अंतरभूत पूर्णांक
acornfb_valid_pixrate(काष्ठा fb_var_screeninfo *var)
अणु
	u_दीर्घ limit;

	अगर (!var->pixघड़ी)
		वापस 0;

	/*
	 * Limits below are taken from RISC OS bandwidthlimit file
	 */
	अगर (current_par.using_vram) अणु
		अगर (current_par.vram_half_sam == 2048)
			limit = 6578;
		अन्यथा
			limit = 13157;
	पूर्ण अन्यथा अणु
		limit = 26315;
	पूर्ण

	वापस acornfb_bandwidth(var) >= limit;
पूर्ण

/*
 * Try to find the best PLL parameters क्रम the pixel घड़ी.
 * This algorithm seems to give best predictable results,
 * and produces the same values as detailed in the VIDC20
 * data sheet.
 */
अटल अंतरभूत u_पूर्णांक
acornfb_vidc20_find_pll(u_पूर्णांक pixclk)
अणु
	u_पूर्णांक r, best_r = 2, best_v = 2;
	पूर्णांक best_d = 0x7fffffff;

	क्रम (r = 2; r <= 32; r++) अणु
		u_पूर्णांक rr, v, p;
		पूर्णांक d;

		rr = 41667 * r;

		v = (rr + pixclk / 2) / pixclk;

		अगर (v > 32 || v < 2)
			जारी;

		p = (rr + v / 2) / v;

		d = pixclk - p;

		अगर (d < 0)
			d = -d;

		अगर (d < best_d) अणु
			best_d = d;
			best_v = v - 1;
			best_r = r - 1;
		पूर्ण

		अगर (d == 0)
			अवरोध;
	पूर्ण

	वापस best_v << 8 | best_r;
पूर्ण

अटल अंतरभूत व्योम
acornfb_vidc20_find_rates(काष्ठा vidc_timing *vidc,
			  काष्ठा fb_var_screeninfo *var)
अणु
	u_पूर्णांक भाग;

	/* Select pixel-घड़ी भागisor to keep PLL in range */
	भाग = var->pixघड़ी / 9090; /*9921*/

	/* Limit भागisor */
	अगर (भाग == 0)
		भाग = 1;
	अगर (भाग > 8)
		भाग = 8;

	/* Encode भागisor to VIDC20 setting */
	चयन (भाग) अणु
	हाल 1:	vidc->control |= VIDC20_CTRL_PIX_CK;  अवरोध;
	हाल 2:	vidc->control |= VIDC20_CTRL_PIX_CK2; अवरोध;
	हाल 3:	vidc->control |= VIDC20_CTRL_PIX_CK3; अवरोध;
	हाल 4:	vidc->control |= VIDC20_CTRL_PIX_CK4; अवरोध;
	हाल 5:	vidc->control |= VIDC20_CTRL_PIX_CK5; अवरोध;
	हाल 6:	vidc->control |= VIDC20_CTRL_PIX_CK6; अवरोध;
	हाल 7:	vidc->control |= VIDC20_CTRL_PIX_CK7; अवरोध;
	हाल 8: vidc->control |= VIDC20_CTRL_PIX_CK8; अवरोध;
	पूर्ण

	/*
	 * With VRAM, the FIFO can be set to the highest possible setting
	 * because there are no latency considerations क्रम other memory
	 * accesses. However, in 64 bit bus mode the FIFO preload value
	 * must not be set to VIDC20_CTRL_FIFO_28 because this will let
	 * the FIFO overflow. See VIDC20 manual page 33 (6.0 Setting the
	 * FIFO preload value).
	 */
	अगर (current_par.using_vram) अणु
		अगर (current_par.vram_half_sam == 2048)
			vidc->control |= VIDC20_CTRL_FIFO_24;
		अन्यथा
			vidc->control |= VIDC20_CTRL_FIFO_28;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ bandwidth = acornfb_bandwidth(var);

		/* Encode bandwidth as VIDC20 setting */
		अगर (bandwidth > 33334)		/* < 30.0MB/s */
			vidc->control |= VIDC20_CTRL_FIFO_16;
		अन्यथा अगर (bandwidth > 26666)	/* < 37.5MB/s */
			vidc->control |= VIDC20_CTRL_FIFO_20;
		अन्यथा अगर (bandwidth > 22222)	/* < 45.0MB/s */
			vidc->control |= VIDC20_CTRL_FIFO_24;
		अन्यथा				/* > 45.0MB/s */
			vidc->control |= VIDC20_CTRL_FIFO_28;
	पूर्ण

	/* Find the PLL values */
	vidc->pll_ctl = acornfb_vidc20_find_pll(var->pixघड़ी / भाग);
पूर्ण

#घोषणा acornfb_शेष_control()	(VIDC20_CTRL_PIX_VCLK)
#घोषणा acornfb_शेष_econtrol()	(VIDC20_ECTL_DAC | VIDC20_ECTL_REG(3))
