<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2019 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "komeda_dev.h"

काष्ठा komeda_str अणु
	अक्षर *str;
	u32 sz;
	u32 len;
पूर्ण;

/* वापस 0 on success,  < 0 on no space.
 */
__म_लिखो(2, 3)
अटल पूर्णांक komeda_प्र_लिखो(काष्ठा komeda_str *str, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक num, मुक्त_sz;
	पूर्णांक err;

	मुक्त_sz = str->sz - str->len - 1;
	अगर (मुक्त_sz <= 0)
		वापस -ENOSPC;

	बहु_शुरू(args, fmt);

	num = vsnम_लिखो(str->str + str->len, मुक्त_sz, fmt, args);

	बहु_पूर्ण(args);

	अगर (num < मुक्त_sz) अणु
		str->len += num;
		err = 0;
	पूर्ण अन्यथा अणु
		str->len = str->sz - 1;
		err = -ENOSPC;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम evt_प्र_लिखो(काष्ठा komeda_str *str, u64 evt, स्थिर अक्षर *msg)
अणु
	अगर (evt)
		komeda_प्र_लिखो(str, msg);
पूर्ण

अटल व्योम evt_str(काष्ठा komeda_str *str, u64 events)
अणु
	अगर (events == 0ULL) अणु
		komeda_प्र_लिखो(str, "None");
		वापस;
	पूर्ण

	evt_प्र_लिखो(str, events & KOMEDA_EVENT_VSYNC, "VSYNC|");
	evt_प्र_लिखो(str, events & KOMEDA_EVENT_FLIP, "FLIP|");
	evt_प्र_लिखो(str, events & KOMEDA_EVENT_EOW, "EOW|");
	evt_प्र_लिखो(str, events & KOMEDA_EVENT_MODE, "OP-MODE|");

	evt_प्र_लिखो(str, events & KOMEDA_EVENT_URUN, "UNDERRUN|");
	evt_प्र_लिखो(str, events & KOMEDA_EVENT_OVR, "OVERRUN|");

	/* GLB error */
	evt_प्र_लिखो(str, events & KOMEDA_ERR_MERR, "MERR|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_FRAMETO, "FRAMETO|");

	/* DOU error */
	evt_प्र_लिखो(str, events & KOMEDA_ERR_DRIFTTO, "DRIFTTO|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_FRAMETO, "FRAMETO|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_TETO, "TETO|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_CSCE, "CSCE|");

	/* LPU errors or events */
	evt_प्र_लिखो(str, events & KOMEDA_EVENT_IBSY, "IBSY|");
	evt_प्र_लिखो(str, events & KOMEDA_EVENT_EMPTY, "EMPTY|");
	evt_प्र_लिखो(str, events & KOMEDA_EVENT_FULL, "FULL|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_AXIE, "AXIE|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_ACE0, "ACE0|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_ACE1, "ACE1|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_ACE2, "ACE2|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_ACE3, "ACE3|");

	/* LPU TBU errors*/
	evt_प्र_लिखो(str, events & KOMEDA_ERR_TCF, "TCF|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_TTNG, "TTNG|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_TITR, "TITR|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_TEMR, "TEMR|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_TTF, "TTF|");

	/* CU errors*/
	evt_प्र_लिखो(str, events & KOMEDA_ERR_CPE, "COPROC|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_ZME, "ZME|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_CFGE, "CFGE|");
	evt_प्र_लिखो(str, events & KOMEDA_ERR_TEMR, "TEMR|");

	अगर (str->len > 0 && (str->str[str->len - 1] == '|')) अणु
		str->str[str->len - 1] = 0;
		str->len--;
	पूर्ण
पूर्ण

अटल bool is_new_frame(काष्ठा komeda_events *a)
अणु
	वापस (a->pipes[0] | a->pipes[1]) &
	       (KOMEDA_EVENT_FLIP | KOMEDA_EVENT_EOW);
पूर्ण

व्योम komeda_prपूर्णांक_events(काष्ठा komeda_events *evts, काष्ठा drm_device *dev)
अणु
	u64 prपूर्णांक_evts = 0;
	अटल bool en_prपूर्णांक = true;
	काष्ठा komeda_dev *mdev = dev->dev_निजी;
	u16 स्थिर err_verbosity = mdev->err_verbosity;
	u64 evts_mask = evts->global | evts->pipes[0] | evts->pipes[1];

	/* reduce the same msg prपूर्णांक, only prपूर्णांक the first evt क्रम one frame */
	अगर (evts->global || is_new_frame(evts))
		en_prपूर्णांक = true;
	अगर (!(err_verbosity & KOMEDA_DEV_PRINT_DISABLE_RATELIMIT) && !en_prपूर्णांक)
		वापस;

	अगर (err_verbosity & KOMEDA_DEV_PRINT_ERR_EVENTS)
		prपूर्णांक_evts |= KOMEDA_ERR_EVENTS;
	अगर (err_verbosity & KOMEDA_DEV_PRINT_WARN_EVENTS)
		prपूर्णांक_evts |= KOMEDA_WARN_EVENTS;
	अगर (err_verbosity & KOMEDA_DEV_PRINT_INFO_EVENTS)
		prपूर्णांक_evts |= KOMEDA_INFO_EVENTS;

	अगर (evts_mask & prपूर्णांक_evts) अणु
		अक्षर msg[256];
		काष्ठा komeda_str str;
		काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(dev->dev);

		str.str = msg;
		str.sz  = माप(msg);
		str.len = 0;

		komeda_प्र_लिखो(&str, "gcu: ");
		evt_str(&str, evts->global);
		komeda_प्र_लिखो(&str, ", pipes[0]: ");
		evt_str(&str, evts->pipes[0]);
		komeda_प्र_लिखो(&str, ", pipes[1]: ");
		evt_str(&str, evts->pipes[1]);

		DRM_ERROR("err detect: %s\n", msg);
		अगर ((err_verbosity & KOMEDA_DEV_PRINT_DUMP_STATE_ON_EVENT) &&
		    (evts_mask & (KOMEDA_ERR_EVENTS | KOMEDA_WARN_EVENTS)))
			drm_state_dump(dev, &p);

		en_prपूर्णांक = false;
	पूर्ण
पूर्ण
