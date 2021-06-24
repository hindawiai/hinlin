<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1251
 *
 * Copyright (C) 2008 Nokia Corporation
 */

#समावेश "reg.h"
#समावेश "ps.h"
#समावेश "cmd.h"
#समावेश "io.h"

/* in ms */
#घोषणा WL1251_WAKEUP_TIMEOUT 100

व्योम wl1251_elp_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork;
	काष्ठा wl1251 *wl;

	dwork = to_delayed_work(work);
	wl = container_of(dwork, काष्ठा wl1251, elp_work);

	wl1251_debug(DEBUG_PSM, "elp work");

	mutex_lock(&wl->mutex);

	अगर (wl->elp || wl->station_mode == STATION_ACTIVE_MODE)
		जाओ out;

	wl1251_debug(DEBUG_PSM, "chip to elp");
	wl1251_ग_लिखो_elp(wl, HW_ACCESS_ELP_CTRL_REG_ADDR, ELPCTRL_SLEEP);
	wl->elp = true;

out:
	mutex_unlock(&wl->mutex);
पूर्ण

#घोषणा ELP_ENTRY_DELAY  5

/* Routines to toggle sleep mode जबतक in ELP */
व्योम wl1251_ps_elp_sleep(काष्ठा wl1251 *wl)
अणु
	अचिन्हित दीर्घ delay;

	अगर (wl->station_mode != STATION_ACTIVE_MODE) अणु
		delay = msecs_to_jअगरfies(ELP_ENTRY_DELAY);
		ieee80211_queue_delayed_work(wl->hw, &wl->elp_work, delay);
	पूर्ण
पूर्ण

पूर्णांक wl1251_ps_elp_wakeup(काष्ठा wl1251 *wl)
अणु
	अचिन्हित दीर्घ समयout, start;
	u32 elp_reg;

	cancel_delayed_work(&wl->elp_work);

	अगर (!wl->elp)
		वापस 0;

	wl1251_debug(DEBUG_PSM, "waking up chip from elp");

	start = jअगरfies;
	समयout = jअगरfies + msecs_to_jअगरfies(WL1251_WAKEUP_TIMEOUT);

	wl1251_ग_लिखो_elp(wl, HW_ACCESS_ELP_CTRL_REG_ADDR, ELPCTRL_WAKE_UP);

	elp_reg = wl1251_पढ़ो_elp(wl, HW_ACCESS_ELP_CTRL_REG_ADDR);

	/*
	 * FIXME: we should रुको क्रम irq from chip but, as a temporary
	 * solution to simplअगरy locking, let's poll instead
	 */
	जबतक (!(elp_reg & ELPCTRL_WLAN_READY)) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			wl1251_error("elp wakeup timeout");
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(1);
		elp_reg = wl1251_पढ़ो_elp(wl, HW_ACCESS_ELP_CTRL_REG_ADDR);
	पूर्ण

	wl1251_debug(DEBUG_PSM, "wakeup time: %u ms",
		     jअगरfies_to_msecs(jअगरfies - start));

	wl->elp = false;

	वापस 0;
पूर्ण

पूर्णांक wl1251_ps_set_mode(काष्ठा wl1251 *wl, क्रमागत wl1251_station_mode mode)
अणु
	पूर्णांक ret;

	चयन (mode) अणु
	हाल STATION_POWER_SAVE_MODE:
		wl1251_debug(DEBUG_PSM, "entering psm");

		/* enable beacon filtering */
		ret = wl1251_acx_beacon_filter_opt(wl, true);
		अगर (ret < 0)
			वापस ret;

		ret = wl1251_acx_wake_up_conditions(wl,
						    WAKE_UP_EVENT_DTIM_BITMAP,
						    wl->listen_पूर्णांक);
		अगर (ret < 0)
			वापस ret;

		ret = wl1251_acx_bet_enable(wl, WL1251_ACX_BET_ENABLE,
					    WL1251_DEFAULT_BET_CONSECUTIVE);
		अगर (ret < 0)
			वापस ret;

		ret = wl1251_cmd_ps_mode(wl, CHIP_POWER_SAVE_MODE);
		अगर (ret < 0)
			वापस ret;

		ret = wl1251_acx_sleep_auth(wl, WL1251_PSM_ELP);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल STATION_IDLE:
		wl1251_debug(DEBUG_PSM, "entering idle");

		ret = wl1251_acx_sleep_auth(wl, WL1251_PSM_ELP);
		अगर (ret < 0)
			वापस ret;

		ret = wl1251_cmd_ढाँचा_set(wl, CMD_DISCONNECT, शून्य, 0);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल STATION_ACTIVE_MODE:
	शेष:
		wl1251_debug(DEBUG_PSM, "leaving psm");

		ret = wl1251_acx_sleep_auth(wl, WL1251_PSM_CAM);
		अगर (ret < 0)
			वापस ret;

		/* disable BET */
		ret = wl1251_acx_bet_enable(wl, WL1251_ACX_BET_DISABLE,
					    WL1251_DEFAULT_BET_CONSECUTIVE);
		अगर (ret < 0)
			वापस ret;

		/* disable beacon filtering */
		ret = wl1251_acx_beacon_filter_opt(wl, false);
		अगर (ret < 0)
			वापस ret;

		ret = wl1251_acx_wake_up_conditions(wl,
						    WAKE_UP_EVENT_DTIM_BITMAP,
						    wl->listen_पूर्णांक);
		अगर (ret < 0)
			वापस ret;

		ret = wl1251_cmd_ps_mode(wl, CHIP_ACTIVE_MODE);
		अगर (ret < 0)
			वापस ret;

		अवरोध;
	पूर्ण
	wl->station_mode = mode;

	वापस ret;
पूर्ण

