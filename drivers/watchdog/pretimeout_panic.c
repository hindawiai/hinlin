<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015-2016 Mentor Graphics
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/watchकरोg.h>

#समावेश "watchdog_pretimeout.h"

/**
 * preसमयout_panic - Panic on watchकरोg preसमयout event
 * @wdd - watchकरोg_device
 *
 * Panic, watchकरोg has not been fed till preसमयout event.
 */
अटल व्योम preसमयout_panic(काष्ठा watchकरोg_device *wdd)
अणु
	panic("watchdog pretimeout event\n");
पूर्ण

अटल काष्ठा watchकरोg_governor watchकरोg_gov_panic = अणु
	.name		= "panic",
	.preसमयout	= preसमयout_panic,
पूर्ण;

अटल पूर्णांक __init watchकरोg_gov_panic_रेजिस्टर(व्योम)
अणु
	वापस watchकरोg_रेजिस्टर_governor(&watchकरोg_gov_panic);
पूर्ण

अटल व्योम __निकास watchकरोg_gov_panic_unरेजिस्टर(व्योम)
अणु
	watchकरोg_unरेजिस्टर_governor(&watchकरोg_gov_panic);
पूर्ण
module_init(watchकरोg_gov_panic_रेजिस्टर);
module_निकास(watchकरोg_gov_panic_unरेजिस्टर);

MODULE_AUTHOR("Vladimir Zapolskiy <vladimir_zapolskiy@mentor.com>");
MODULE_DESCRIPTION("Panic watchdog pretimeout governor");
MODULE_LICENSE("GPL");
