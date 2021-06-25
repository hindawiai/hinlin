<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2012 Steffen Trumtrar <s.trumtrar@pengutronix.de>
 *
 * display timings of helpers
 */

#अगर_अघोषित __LINUX_OF_DISPLAY_TIMING_H
#घोषणा __LINUX_OF_DISPLAY_TIMING_H

काष्ठा device_node;
काष्ठा display_timing;
काष्ठा display_timings;

#घोषणा OF_USE_NATIVE_MODE -1

#अगर_घोषित CONFIG_OF
पूर्णांक of_get_display_timing(स्थिर काष्ठा device_node *np, स्थिर अक्षर *name,
		काष्ठा display_timing *dt);
काष्ठा display_timings *of_get_display_timings(स्थिर काष्ठा device_node *np);
#अन्यथा
अटल अंतरभूत पूर्णांक of_get_display_timing(स्थिर काष्ठा device_node *np,
		स्थिर अक्षर *name, काष्ठा display_timing *dt)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत काष्ठा display_timings *
of_get_display_timings(स्थिर काष्ठा device_node *np)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
