<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Software PHY emulation
 *
 * Code taken from fixed_phy.c by Russell King.
 *
 * Author: Vitaly Bordug <vbordug@ru.mvista.com>
 *         Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * Copyright (c) 2006-2007 MontaVista Software, Inc.
 */
#समावेश <linux/export.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>

#समावेश "swphy.h"

#घोषणा MII_REGS_NUM 29

काष्ठा swmii_regs अणु
	u16 bmsr;
	u16 lpa;
	u16 lpagb;
	u16 estat;
पूर्ण;

क्रमागत अणु
	SWMII_SPEED_10 = 0,
	SWMII_SPEED_100,
	SWMII_SPEED_1000,
	SWMII_DUPLEX_HALF = 0,
	SWMII_DUPLEX_FULL,
पूर्ण;

/*
 * These two tables get bitwise-anded together to produce the final result.
 * This means the speed table must contain both duplex settings, and the
 * duplex table must contain all speed settings.
 */
अटल स्थिर काष्ठा swmii_regs speed[] = अणु
	[SWMII_SPEED_10] = अणु
		.lpa   = LPA_10FULL | LPA_10HALF,
	पूर्ण,
	[SWMII_SPEED_100] = अणु
		.bmsr  = BMSR_100FULL | BMSR_100HALF,
		.lpa   = LPA_100FULL | LPA_100HALF,
	पूर्ण,
	[SWMII_SPEED_1000] = अणु
		.bmsr  = BMSR_ESTATEN,
		.lpagb = LPA_1000FULL | LPA_1000HALF,
		.estat = ESTATUS_1000_TFULL | ESTATUS_1000_THALF,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा swmii_regs duplex[] = अणु
	[SWMII_DUPLEX_HALF] = अणु
		.bmsr  = BMSR_ESTATEN | BMSR_100HALF,
		.lpa   = LPA_10HALF | LPA_100HALF,
		.lpagb = LPA_1000HALF,
		.estat = ESTATUS_1000_THALF,
	पूर्ण,
	[SWMII_DUPLEX_FULL] = अणु
		.bmsr  = BMSR_ESTATEN | BMSR_100FULL,
		.lpa   = LPA_10FULL | LPA_100FULL,
		.lpagb = LPA_1000FULL,
		.estat = ESTATUS_1000_TFULL,
	पूर्ण,
पूर्ण;

अटल पूर्णांक swphy_decode_speed(पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल 1000:
		वापस SWMII_SPEED_1000;
	हाल 100:
		वापस SWMII_SPEED_100;
	हाल 10:
		वापस SWMII_SPEED_10;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * swphy_validate_state - validate the software phy status
 * @state: software phy status
 *
 * This checks that we can represent the state stored in @state can be
 * represented in the emulated MII रेजिस्टरs.  Returns 0 अगर it can,
 * otherwise वापसs -EINVAL.
 */
पूर्णांक swphy_validate_state(स्थिर काष्ठा fixed_phy_status *state)
अणु
	पूर्णांक err;

	अगर (state->link) अणु
		err = swphy_decode_speed(state->speed);
		अगर (err < 0) अणु
			pr_warn("swphy: unknown speed\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(swphy_validate_state);

/**
 * swphy_पढ़ो_reg - वापस a MII रेजिस्टर from the fixed phy state
 * @reg: MII रेजिस्टर
 * @state: fixed phy status
 *
 * Return the MII @reg रेजिस्टर generated from the fixed phy state @state.
 */
पूर्णांक swphy_पढ़ो_reg(पूर्णांक reg, स्थिर काष्ठा fixed_phy_status *state)
अणु
	पूर्णांक speed_index, duplex_index;
	u16 bmsr = BMSR_ANEGCAPABLE;
	u16 estat = 0;
	u16 lpagb = 0;
	u16 lpa = 0;

	अगर (reg > MII_REGS_NUM)
		वापस -1;

	speed_index = swphy_decode_speed(state->speed);
	अगर (WARN_ON(speed_index < 0))
		वापस 0;

	duplex_index = state->duplex ? SWMII_DUPLEX_FULL : SWMII_DUPLEX_HALF;

	bmsr |= speed[speed_index].bmsr & duplex[duplex_index].bmsr;
	estat |= speed[speed_index].estat & duplex[duplex_index].estat;

	अगर (state->link) अणु
		bmsr |= BMSR_LSTATUS | BMSR_ANEGCOMPLETE;

		lpa   |= speed[speed_index].lpa   & duplex[duplex_index].lpa;
		lpagb |= speed[speed_index].lpagb & duplex[duplex_index].lpagb;

		अगर (state->छोड़ो)
			lpa |= LPA_PAUSE_CAP;

		अगर (state->asym_छोड़ो)
			lpa |= LPA_PAUSE_ASYM;
	पूर्ण

	चयन (reg) अणु
	हाल MII_BMCR:
		वापस BMCR_ANENABLE;
	हाल MII_BMSR:
		वापस bmsr;
	हाल MII_PHYSID1:
	हाल MII_PHYSID2:
		वापस 0;
	हाल MII_LPA:
		वापस lpa;
	हाल MII_STAT1000:
		वापस lpagb;
	हाल MII_ESTATUS:
		वापस estat;

	/*
	 * We करो not support emulating Clause 45 over Clause 22 रेजिस्टर
	 * पढ़ोs.  Return an error instead of bogus data.
	 */
	हाल MII_MMD_CTRL:
	हाल MII_MMD_DATA:
		वापस -1;

	शेष:
		वापस 0xffff;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(swphy_पढ़ो_reg);
