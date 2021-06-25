<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thunderbolt driver - quirks
 *
 * Copyright (c) 2020 Mario Limonciello <mario.limonciello@dell.com>
 */

#समावेश "tb.h"

अटल व्योम quirk_क्रमce_घातer_link(काष्ठा tb_चयन *sw)
अणु
	sw->quirks |= QUIRK_FORCE_POWER_LINK_CONTROLLER;
पूर्ण

काष्ठा tb_quirk अणु
	u16 venकरोr;
	u16 device;
	व्योम (*hook)(काष्ठा tb_चयन *sw);
पूर्ण;

अटल स्थिर काष्ठा tb_quirk tb_quirks[] = अणु
	/* Dell WD19TB supports self-authentication on unplug */
	अणु 0x00d4, 0xb070, quirk_क्रमce_घातer_link पूर्ण,
पूर्ण;

/**
 * tb_check_quirks() - Check क्रम quirks to apply
 * @sw: Thunderbolt चयन
 *
 * Apply any quirks क्रम the Thunderbolt controller.
 */
व्योम tb_check_quirks(काष्ठा tb_चयन *sw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tb_quirks); i++) अणु
		स्थिर काष्ठा tb_quirk *q = &tb_quirks[i];

		अगर (sw->device == q->device && sw->venकरोr == q->venकरोr)
			q->hook(sw);
	पूर्ण
पूर्ण
