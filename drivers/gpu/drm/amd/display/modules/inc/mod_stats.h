<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित MODULES_INC_MOD_STATS_H_
#घोषणा MODULES_INC_MOD_STATS_H_

#समावेश "dm_services.h"

काष्ठा mod_stats अणु
	पूर्णांक dummy;
पूर्ण;

काष्ठा mod_stats_caps अणु
	bool dummy;
पूर्ण;

काष्ठा mod_stats_init_params अणु
	अचिन्हित पूर्णांक stats_enable;
	अचिन्हित पूर्णांक stats_entries;
पूर्ण;

काष्ठा mod_stats *mod_stats_create(काष्ठा dc *dc,
		काष्ठा mod_stats_init_params *init_params);

व्योम mod_stats_destroy(काष्ठा mod_stats *mod_stats);

bool mod_stats_init(काष्ठा mod_stats *mod_stats);

व्योम mod_stats_dump(काष्ठा mod_stats *mod_stats);

व्योम mod_stats_reset_data(काष्ठा mod_stats *mod_stats);

व्योम mod_stats_update_event(काष्ठा mod_stats *mod_stats,
		अक्षर *event_string,
		अचिन्हित पूर्णांक length);

व्योम mod_stats_update_flip(काष्ठा mod_stats *mod_stats,
		अचिन्हित दीर्घ बारtamp_in_ns);

व्योम mod_stats_update_vupdate(काष्ठा mod_stats *mod_stats,
		अचिन्हित दीर्घ बारtamp_in_ns);

व्योम mod_stats_update_मुक्तsync(काष्ठा mod_stats *mod_stats,
		अचिन्हित पूर्णांक v_total_min,
		अचिन्हित पूर्णांक v_total_max,
		अचिन्हित पूर्णांक event_triggers,
		अचिन्हित पूर्णांक winकरोw_min,
		अचिन्हित पूर्णांक winकरोw_max,
		अचिन्हित पूर्णांक lfc_mid_poपूर्णांक_in_us,
		अचिन्हित पूर्णांक inserted_frames,
		अचिन्हित पूर्णांक inserted_frame_duration_in_us);

#पूर्ण_अगर /* MODULES_INC_MOD_STATS_H_ */
