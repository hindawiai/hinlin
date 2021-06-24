<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014 Sebastian Reichel <sre@kernel.org>
 */

#अगर_अघोषित _TOUCHSCREEN_H
#घोषणा _TOUCHSCREEN_H

काष्ठा input_dev;
काष्ठा input_mt_pos;

काष्ठा touchscreen_properties अणु
	अचिन्हित पूर्णांक max_x;
	अचिन्हित पूर्णांक max_y;
	bool invert_x;
	bool invert_y;
	bool swap_x_y;
पूर्ण;

व्योम touchscreen_parse_properties(काष्ठा input_dev *input, bool multitouch,
				  काष्ठा touchscreen_properties *prop);

व्योम touchscreen_set_mt_pos(काष्ठा input_mt_pos *pos,
			    स्थिर काष्ठा touchscreen_properties *prop,
			    अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y);

व्योम touchscreen_report_pos(काष्ठा input_dev *input,
			    स्थिर काष्ठा touchscreen_properties *prop,
			    अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y,
			    bool multitouch);

#पूर्ण_अगर
