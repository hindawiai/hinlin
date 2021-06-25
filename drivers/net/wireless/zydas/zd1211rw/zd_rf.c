<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ZD1211 USB-WLAN driver क्रम Linux
 *
 * Copyright (C) 2005-2007 Ulrich Kunitz <kune@deine-taler.de>
 * Copyright (C) 2006-2007 Daniel Drake <dsd@gentoo.org>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>

#समावेश "zd_def.h"
#समावेश "zd_rf.h"
#समावेश "zd_mac.h"
#समावेश "zd_chip.h"

अटल स्थिर अक्षर * स्थिर rfs[] = अणु
	[0]		= "unknown RF0",
	[1]		= "unknown RF1",
	[UW2451_RF]	= "UW2451_RF",
	[UCHIP_RF]	= "UCHIP_RF",
	[AL2230_RF]	= "AL2230_RF",
	[AL7230B_RF]	= "AL7230B_RF",
	[THETA_RF]	= "THETA_RF",
	[AL2210_RF]	= "AL2210_RF",
	[MAXIM_NEW_RF]	= "MAXIM_NEW_RF",
	[UW2453_RF]	= "UW2453_RF",
	[AL2230S_RF]	= "AL2230S_RF",
	[RALINK_RF]	= "RALINK_RF",
	[INTERSIL_RF]	= "INTERSIL_RF",
	[RF2959_RF]	= "RF2959_RF",
	[MAXIM_NEW2_RF]	= "MAXIM_NEW2_RF",
	[PHILIPS_RF]	= "PHILIPS_RF",
पूर्ण;

स्थिर अक्षर *zd_rf_name(u8 type)
अणु
	अगर (type & 0xf0)
		type = 0;
	वापस rfs[type];
पूर्ण

व्योम zd_rf_init(काष्ठा zd_rf *rf)
अणु
	स_रखो(rf, 0, माप(*rf));

	/* शेष to update channel पूर्णांकegration, as almost all RF's करो want
	 * this */
	rf->update_channel_पूर्णांक = 1;
पूर्ण

व्योम zd_rf_clear(काष्ठा zd_rf *rf)
अणु
	अगर (rf->clear)
		rf->clear(rf);
	ZD_MEMCLEAR(rf, माप(*rf));
पूर्ण

पूर्णांक zd_rf_init_hw(काष्ठा zd_rf *rf, u8 type)
अणु
	पूर्णांक r = 0;
	पूर्णांक t;
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	चयन (type) अणु
	हाल RF2959_RF:
		r = zd_rf_init_rf2959(rf);
		अवरोध;
	हाल AL2230_RF:
	हाल AL2230S_RF:
		r = zd_rf_init_al2230(rf);
		अवरोध;
	हाल AL7230B_RF:
		r = zd_rf_init_al7230b(rf);
		अवरोध;
	हाल MAXIM_NEW_RF:
	हाल UW2453_RF:
		r = zd_rf_init_uw2453(rf);
		अवरोध;
	शेष:
		dev_err(zd_chip_dev(chip),
			"RF %s %#x is not supported\n", zd_rf_name(type), type);
		rf->type = 0;
		वापस -ENODEV;
	पूर्ण

	अगर (r)
		वापस r;

	rf->type = type;

	r = zd_chip_lock_phy_regs(chip);
	अगर (r)
		वापस r;
	t = rf->init_hw(rf);
	r = zd_chip_unlock_phy_regs(chip);
	अगर (t)
		r = t;
	वापस r;
पूर्ण

पूर्णांक zd_rf_scnprपूर्णांक_id(काष्ठा zd_rf *rf, अक्षर *buffer, माप_प्रकार size)
अणु
	वापस scnम_लिखो(buffer, size, "%s", zd_rf_name(rf->type));
पूर्ण

पूर्णांक zd_rf_set_channel(काष्ठा zd_rf *rf, u8 channel)
अणु
	पूर्णांक r;

	ZD_ASSERT(mutex_is_locked(&zd_rf_to_chip(rf)->mutex));
	अगर (channel < MIN_CHANNEL24)
		वापस -EINVAL;
	अगर (channel > MAX_CHANNEL24)
		वापस -EINVAL;
	dev_dbg_f(zd_chip_dev(zd_rf_to_chip(rf)), "channel: %d\n", channel);

	r = rf->set_channel(rf, channel);
	अगर (r >= 0)
		rf->channel = channel;
	वापस r;
पूर्ण

पूर्णांक zd_चयन_radio_on(काष्ठा zd_rf *rf)
अणु
	पूर्णांक r, t;
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = zd_chip_lock_phy_regs(chip);
	अगर (r)
		वापस r;
	t = rf->चयन_radio_on(rf);
	r = zd_chip_unlock_phy_regs(chip);
	अगर (t)
		r = t;
	वापस r;
पूर्ण

पूर्णांक zd_चयन_radio_off(काष्ठा zd_rf *rf)
अणु
	पूर्णांक r, t;
	काष्ठा zd_chip *chip = zd_rf_to_chip(rf);

	/* TODO: move phy regs handling to zd_chip */
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = zd_chip_lock_phy_regs(chip);
	अगर (r)
		वापस r;
	t = rf->चयन_radio_off(rf);
	r = zd_chip_unlock_phy_regs(chip);
	अगर (t)
		r = t;
	वापस r;
पूर्ण

पूर्णांक zd_rf_patch_6m_band_edge(काष्ठा zd_rf *rf, u8 channel)
अणु
	अगर (!rf->patch_6m_band_edge)
		वापस 0;

	वापस rf->patch_6m_band_edge(rf, channel);
पूर्ण

पूर्णांक zd_rf_generic_patch_6m(काष्ठा zd_rf *rf, u8 channel)
अणु
	वापस zd_chip_generic_patch_6m_band(zd_rf_to_chip(rf), channel);
पूर्ण

