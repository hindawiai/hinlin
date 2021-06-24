<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap2-restart.c - code common to all OMAP2xxx machines.
 *
 * Copyright (C) 2012 Texas Instruments
 * Paul Walmsley
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश "soc.h"
#समावेश "common.h"
#समावेश "prm.h"

/*
 * reset_virt_prcm_set_ck, reset_sys_ck: poपूर्णांकers to the virt_prcm_set
 * घड़ी and the sys_ck.  Used during the reset process
 */
अटल काष्ठा clk *reset_virt_prcm_set_ck, *reset_sys_ck;

/* Reboot handling */

/**
 * omap2xxx_restart - Set DPLL to bypass mode क्रम reboot to work
 *
 * Set the DPLL to bypass so that reboot completes successfully.  No
 * वापस value.
 */
व्योम omap2xxx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	u32 rate;

	rate = clk_get_rate(reset_sys_ck);
	clk_set_rate(reset_virt_prcm_set_ck, rate);

	/* XXX Should save the cmd argument क्रम use after the reboot */

	omap_prm_reset_प्रणाली();
पूर्ण

/**
 * omap2xxx_common_look_up_clks_क्रम_reset - look up घड़ीs needed क्रम restart
 *
 * Some घड़ीs need to be looked up in advance क्रम the SoC restart
 * operation to work - see omap2xxx_restart().  Returns -EINVAL upon
 * error or 0 upon success.
 */
अटल पूर्णांक __init omap2xxx_common_look_up_clks_क्रम_reset(व्योम)
अणु
	reset_virt_prcm_set_ck = clk_get(शून्य, "virt_prcm_set");
	अगर (IS_ERR(reset_virt_prcm_set_ck))
		वापस -EINVAL;

	reset_sys_ck = clk_get(शून्य, "sys_ck");
	अगर (IS_ERR(reset_sys_ck))
		वापस -EINVAL;

	वापस 0;
पूर्ण
omap_postcore_initcall(omap2xxx_common_look_up_clks_क्रम_reset);
