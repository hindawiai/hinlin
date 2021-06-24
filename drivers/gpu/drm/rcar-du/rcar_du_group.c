<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * rcar_du_group.c  --  R-Car Display Unit Channels Pair
 *
 * Copyright (C) 2013-2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

/*
 * The R8A7779 DU is split in per-CRTC resources (scan-out engine, blending
 * unit, timings generator, ...) and device-global resources (start/stop
 * control, planes, ...) shared between the two CRTCs.
 *
 * The R8A7790 पूर्णांकroduced a third CRTC with its own set of global resources.
 * This would be modeled as two separate DU device instances अगर it wasn't क्रम
 * a handful or resources that are shared between the three CRTCs (mostly
 * related to input and output routing). For this reason the R8A7790 DU must be
 * modeled as a single device with three CRTCs, two sets of "semi-global"
 * resources, and a few device-global resources.
 *
 * The rcar_du_group object is a driver specअगरic object, without any real
 * counterpart in the DU करोcumentation, that models those semi-global resources.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश "rcar_du_drv.h"
#समावेश "rcar_du_group.h"
#समावेश "rcar_du_regs.h"

u32 rcar_du_group_पढ़ो(काष्ठा rcar_du_group *rgrp, u32 reg)
अणु
	वापस rcar_du_पढ़ो(rgrp->dev, rgrp->mmio_offset + reg);
पूर्ण

व्योम rcar_du_group_ग_लिखो(काष्ठा rcar_du_group *rgrp, u32 reg, u32 data)
अणु
	rcar_du_ग_लिखो(rgrp->dev, rgrp->mmio_offset + reg, data);
पूर्ण

अटल व्योम rcar_du_group_setup_pins(काष्ठा rcar_du_group *rgrp)
अणु
	u32 defr6 = DEFR6_CODE;

	अगर (rgrp->channels_mask & BIT(0))
		defr6 |= DEFR6_ODPM02_DISP;

	अगर (rgrp->channels_mask & BIT(1))
		defr6 |= DEFR6_ODPM12_DISP;

	rcar_du_group_ग_लिखो(rgrp, DEFR6, defr6);
पूर्ण

अटल व्योम rcar_du_group_setup_defr8(काष्ठा rcar_du_group *rgrp)
अणु
	काष्ठा rcar_du_device *rcdu = rgrp->dev;
	u32 defr8 = DEFR8_CODE;

	अगर (rcdu->info->gen < 3) अणु
		defr8 |= DEFR8_DEFE8;

		/*
		 * On Gen2 the DEFR8 रेजिस्टर क्रम the first group also controls
		 * RGB output routing to DPAD0 and VSPD1 routing to DU0/1/2 क्रम
		 * DU instances that support it.
		 */
		अगर (rgrp->index == 0) अणु
			defr8 |= DEFR8_DRGBS_DU(rcdu->dpad0_source);
			अगर (rgrp->dev->vspd1_sink == 2)
				defr8 |= DEFR8_VSCS;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * On Gen3 VSPD routing can't be configured, and DPAD routing
		 * is set in the group corresponding to the DPAD output (no Gen3
		 * SoC has multiple DPAD sources beदीर्घing to separate groups).
		 */
		अगर (rgrp->index == rcdu->dpad0_source / 2)
			defr8 |= DEFR8_DRGBS_DU(rcdu->dpad0_source);
	पूर्ण

	rcar_du_group_ग_लिखो(rgrp, DEFR8, defr8);
पूर्ण

अटल व्योम rcar_du_group_setup_didsr(काष्ठा rcar_du_group *rgrp)
अणु
	काष्ठा rcar_du_device *rcdu = rgrp->dev;
	काष्ठा rcar_du_crtc *rcrtc;
	अचिन्हित पूर्णांक num_crtcs = 0;
	अचिन्हित पूर्णांक i;
	u32 didsr;

	/*
	 * Configure input करोt घड़ी routing with a hardcoded configuration. If
	 * the DU channel can use the LVDS encoder output घड़ी as the करोt
	 * घड़ी, करो so. Otherwise route DU_DOTCLKINn संकेत to DUn.
	 *
	 * Each channel can then select between the करोt घड़ी configured here
	 * and the घड़ी provided by the CPG through the ESCR रेजिस्टर.
	 */
	अगर (rcdu->info->gen < 3 && rgrp->index == 0) अणु
		/*
		 * On Gen2 a single रेजिस्टर in the first group controls करोt
		 * घड़ी selection क्रम all channels.
		 */
		rcrtc = rcdu->crtcs;
		num_crtcs = rcdu->num_crtcs;
	पूर्ण अन्यथा अगर (rcdu->info->gen == 3 && rgrp->num_crtcs > 1) अणु
		/*
		 * On Gen3 करोt घड़ीs are setup through per-group रेजिस्टरs,
		 * only available when the group has two channels.
		 */
		rcrtc = &rcdu->crtcs[rgrp->index * 2];
		num_crtcs = rgrp->num_crtcs;
	पूर्ण

	अगर (!num_crtcs)
		वापस;

	didsr = DIDSR_CODE;
	क्रम (i = 0; i < num_crtcs; ++i, ++rcrtc) अणु
		अगर (rcdu->info->lvds_clk_mask & BIT(rcrtc->index))
			didsr |= DIDSR_LCDS_LVDS0(i)
			      |  DIDSR_PDCS_CLK(i, 0);
		अन्यथा
			didsr |= DIDSR_LCDS_DCLKIN(i)
			      |  DIDSR_PDCS_CLK(i, 0);
	पूर्ण

	rcar_du_group_ग_लिखो(rgrp, DIDSR, didsr);
पूर्ण

अटल व्योम rcar_du_group_setup(काष्ठा rcar_du_group *rgrp)
अणु
	काष्ठा rcar_du_device *rcdu = rgrp->dev;
	u32 defr7 = DEFR7_CODE;

	/* Enable extended features */
	rcar_du_group_ग_लिखो(rgrp, DEFR, DEFR_CODE | DEFR_DEFE);
	अगर (rcdu->info->gen < 3) अणु
		rcar_du_group_ग_लिखो(rgrp, DEFR2, DEFR2_CODE | DEFR2_DEFE2G);
		rcar_du_group_ग_लिखो(rgrp, DEFR3, DEFR3_CODE | DEFR3_DEFE3);
		rcar_du_group_ग_लिखो(rgrp, DEFR4, DEFR4_CODE);
	पूर्ण
	rcar_du_group_ग_लिखो(rgrp, DEFR5, DEFR5_CODE | DEFR5_DEFE5);

	rcar_du_group_setup_pins(rgrp);

	/*
	 * TODO: Handle routing of the DU output to CMM dynamically, as we
	 * should bypass CMM completely when no color management feature is
	 * used.
	 */
	defr7 |= (rgrp->cmms_mask & BIT(1) ? DEFR7_CMME1 : 0) |
		 (rgrp->cmms_mask & BIT(0) ? DEFR7_CMME0 : 0);
	rcar_du_group_ग_लिखो(rgrp, DEFR7, defr7);

	अगर (rcdu->info->gen >= 2) अणु
		rcar_du_group_setup_defr8(rgrp);
		rcar_du_group_setup_didsr(rgrp);
	पूर्ण

	अगर (rcdu->info->gen >= 3)
		rcar_du_group_ग_लिखो(rgrp, DEFR10, DEFR10_CODE | DEFR10_DEFE10);

	/*
	 * Use DS1PR and DS2PR to configure planes priorities and connects the
	 * superposition 0 to DU0 pins. DU1 pins will be configured dynamically.
	 */
	rcar_du_group_ग_लिखो(rgrp, DORCR, DORCR_PG1D_DS1 | DORCR_DPRS);

	/* Apply planes to CRTCs association. */
	mutex_lock(&rgrp->lock);
	rcar_du_group_ग_लिखो(rgrp, DPTSR, (rgrp->dptsr_planes << 16) |
			    rgrp->dptsr_planes);
	mutex_unlock(&rgrp->lock);
पूर्ण

/*
 * rcar_du_group_get - Acquire a reference to the DU channels group
 *
 * Acquiring the first reference setups core रेजिस्टरs. A reference must be held
 * beक्रमe accessing any hardware रेजिस्टरs.
 *
 * This function must be called with the DRM mode_config lock held.
 *
 * Return 0 in हाल of success or a negative error code otherwise.
 */
पूर्णांक rcar_du_group_get(काष्ठा rcar_du_group *rgrp)
अणु
	अगर (rgrp->use_count)
		जाओ करोne;

	rcar_du_group_setup(rgrp);

करोne:
	rgrp->use_count++;
	वापस 0;
पूर्ण

/*
 * rcar_du_group_put - Release a reference to the DU
 *
 * This function must be called with the DRM mode_config lock held.
 */
व्योम rcar_du_group_put(काष्ठा rcar_du_group *rgrp)
अणु
	--rgrp->use_count;
पूर्ण

अटल व्योम __rcar_du_group_start_stop(काष्ठा rcar_du_group *rgrp, bool start)
अणु
	काष्ठा rcar_du_device *rcdu = rgrp->dev;

	/*
	 * Group start/stop is controlled by the DRES and DEN bits of DSYSR0
	 * क्रम the first group and DSYSR2 क्रम the second group. On most DU
	 * instances, this maps to the first CRTC of the group, and we can just
	 * use rcar_du_crtc_dsysr_clr_set() to access the correct DSYSR. On
	 * M3-N, however, DU2 करोesn't exist, but DSYSR2 करोes. We thus need to
	 * access the रेजिस्टर directly using group पढ़ो/ग_लिखो.
	 */
	अगर (rcdu->info->channels_mask & BIT(rgrp->index * 2)) अणु
		काष्ठा rcar_du_crtc *rcrtc = &rgrp->dev->crtcs[rgrp->index * 2];

		rcar_du_crtc_dsysr_clr_set(rcrtc, DSYSR_DRES | DSYSR_DEN,
					   start ? DSYSR_DEN : DSYSR_DRES);
	पूर्ण अन्यथा अणु
		rcar_du_group_ग_लिखो(rgrp, DSYSR,
				    start ? DSYSR_DEN : DSYSR_DRES);
	पूर्ण
पूर्ण

व्योम rcar_du_group_start_stop(काष्ठा rcar_du_group *rgrp, bool start)
अणु
	/*
	 * Many of the configuration bits are only updated when the display
	 * reset (DRES) bit in DSYSR is set to 1, disabling *both* CRTCs. Some
	 * of those bits could be pre-configured, but others (especially the
	 * bits related to plane assignment to display timing controllers) need
	 * to be modअगरied at runसमय.
	 *
	 * Restart the display controller अगर a start is requested. Sorry क्रम the
	 * flicker. It should be possible to move most of the "DRES-update" bits
	 * setup to driver initialization समय and minimize the number of हालs
	 * when the display controller will have to be restarted.
	 */
	अगर (start) अणु
		अगर (rgrp->used_crtcs++ != 0)
			__rcar_du_group_start_stop(rgrp, false);
		__rcar_du_group_start_stop(rgrp, true);
	पूर्ण अन्यथा अणु
		अगर (--rgrp->used_crtcs == 0)
			__rcar_du_group_start_stop(rgrp, false);
	पूर्ण
पूर्ण

व्योम rcar_du_group_restart(काष्ठा rcar_du_group *rgrp)
अणु
	rgrp->need_restart = false;

	__rcar_du_group_start_stop(rgrp, false);
	__rcar_du_group_start_stop(rgrp, true);
पूर्ण

पूर्णांक rcar_du_set_dpad0_vsp1_routing(काष्ठा rcar_du_device *rcdu)
अणु
	काष्ठा rcar_du_group *rgrp;
	काष्ठा rcar_du_crtc *crtc;
	अचिन्हित पूर्णांक index;
	पूर्णांक ret;

	अगर (rcdu->info->gen < 2)
		वापस 0;

	/*
	 * RGB output routing to DPAD0 and VSP1D routing to DU0/1/2 are
	 * configured in the DEFR8 रेजिस्टर of the first group on Gen2 and the
	 * last group on Gen3. As this function can be called with the DU
	 * channels of the corresponding CRTCs disabled, we need to enable the
	 * group घड़ी beक्रमe accessing the रेजिस्टर.
	 */
	index = rcdu->info->gen < 3 ? 0 : DIV_ROUND_UP(rcdu->num_crtcs, 2) - 1;
	rgrp = &rcdu->groups[index];
	crtc = &rcdu->crtcs[index * 2];

	ret = clk_prepare_enable(crtc->घड़ी);
	अगर (ret < 0)
		वापस ret;

	rcar_du_group_setup_defr8(rgrp);

	clk_disable_unprepare(crtc->घड़ी);

	वापस 0;
पूर्ण

अटल व्योम rcar_du_group_set_dpad_levels(काष्ठा rcar_du_group *rgrp)
अणु
	अटल स्थिर u32 करोflr_values[2] = अणु
		DOFLR_HSYCFL0 | DOFLR_VSYCFL0 | DOFLR_ODDFL0 |
		DOFLR_DISPFL0 | DOFLR_CDEFL0  | DOFLR_RGBFL0,
		DOFLR_HSYCFL1 | DOFLR_VSYCFL1 | DOFLR_ODDFL1 |
		DOFLR_DISPFL1 | DOFLR_CDEFL1  | DOFLR_RGBFL1,
	पूर्ण;
	अटल स्थिर u32 dpad_mask = BIT(RCAR_DU_OUTPUT_DPAD1)
				   | BIT(RCAR_DU_OUTPUT_DPAD0);
	काष्ठा rcar_du_device *rcdu = rgrp->dev;
	u32 करोflr = DOFLR_CODE;
	अचिन्हित पूर्णांक i;

	अगर (rcdu->info->gen < 2)
		वापस;

	/*
	 * The DPAD outमाला_दो can't be controlled directly. However, the parallel
	 * output of the DU channels routed to DPAD can be set to fixed levels
	 * through the DOFLR group रेजिस्टर. Use this to turn the DPAD on or off
	 * by driving fixed low-level संकेतs at the output of any DU channel
	 * not routed to a DPAD output. This करोesn't affect the DU output
	 * संकेतs going to other outमाला_दो, such as the पूर्णांकernal LVDS and HDMI
	 * encoders.
	 */

	क्रम (i = 0; i < rgrp->num_crtcs; ++i) अणु
		काष्ठा rcar_du_crtc_state *rstate;
		काष्ठा rcar_du_crtc *rcrtc;

		rcrtc = &rcdu->crtcs[rgrp->index * 2 + i];
		rstate = to_rcar_crtc_state(rcrtc->crtc.state);

		अगर (!(rstate->outमाला_दो & dpad_mask))
			करोflr |= करोflr_values[i];
	पूर्ण

	rcar_du_group_ग_लिखो(rgrp, DOFLR, करोflr);
पूर्ण

पूर्णांक rcar_du_group_set_routing(काष्ठा rcar_du_group *rgrp)
अणु
	काष्ठा rcar_du_device *rcdu = rgrp->dev;
	u32 करोrcr = rcar_du_group_पढ़ो(rgrp, DORCR);

	करोrcr &= ~(DORCR_PG2T | DORCR_DK2S | DORCR_PG2D_MASK);

	/*
	 * Set the DPAD1 pins sources. Select CRTC 0 अगर explicitly requested and
	 * CRTC 1 in all other हालs to aव्योम cloning CRTC 0 to DPAD0 and DPAD1
	 * by शेष.
	 */
	अगर (rcdu->dpad1_source == rgrp->index * 2)
		करोrcr |= DORCR_PG2D_DS1;
	अन्यथा
		करोrcr |= DORCR_PG2T | DORCR_DK2S | DORCR_PG2D_DS2;

	rcar_du_group_ग_लिखो(rgrp, DORCR, करोrcr);

	rcar_du_group_set_dpad_levels(rgrp);

	वापस rcar_du_set_dpad0_vsp1_routing(rgrp->dev);
पूर्ण
