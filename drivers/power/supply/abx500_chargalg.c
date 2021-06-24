<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2012
 * Copyright (c) 2012 Sony Mobile Communications AB
 *
 * Charging algorithm driver क्रम abx500 variants
 *
 * Authors:
 *	Johan Palsson <johan.palsson@stericsson.com>
 *	Karl Komierowski <karl.komierowski@stericsson.com>
 *	Arun R Murthy <arun.murthy@stericsson.com>
 *	Author: Imre Sunyi <imre.sunyi@sonymobile.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/completion.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kobject.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/abx500.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/notअगरier.h>

#समावेश "ab8500-bm.h"
#समावेश "ab8500-chargalg.h"

/* Watchकरोg kick पूर्णांकerval */
#घोषणा CHG_WD_INTERVAL			(6 * HZ)

/* End-of-अक्षरge criteria counter */
#घोषणा EOC_COND_CNT			10

/* One hour expressed in seconds */
#घोषणा ONE_HOUR_IN_SECONDS            3600

/* Five minutes expressed in seconds */
#घोषणा FIVE_MINUTES_IN_SECONDS        300

#घोषणा CHARGALG_CURR_STEP_LOW		0
#घोषणा CHARGALG_CURR_STEP_HIGH	100

क्रमागत abx500_अक्षरgers अणु
	NO_CHG,
	AC_CHG,
	USB_CHG,
पूर्ण;

काष्ठा abx500_अक्षरgalg_अक्षरger_info अणु
	क्रमागत abx500_अक्षरgers conn_chg;
	क्रमागत abx500_अक्षरgers prev_conn_chg;
	क्रमागत abx500_अक्षरgers online_chg;
	क्रमागत abx500_अक्षरgers prev_online_chg;
	क्रमागत abx500_अक्षरgers अक्षरger_type;
	bool usb_chg_ok;
	bool ac_chg_ok;
	पूर्णांक usb_volt;
	पूर्णांक usb_curr;
	पूर्णांक ac_volt;
	पूर्णांक ac_curr;
	पूर्णांक usb_vset;
	पूर्णांक usb_iset;
	पूर्णांक ac_vset;
	पूर्णांक ac_iset;
पूर्ण;

काष्ठा abx500_अक्षरgalg_suspension_status अणु
	bool suspended_change;
	bool ac_suspended;
	bool usb_suspended;
पूर्ण;

काष्ठा abx500_अक्षरgalg_current_step_status अणु
	bool curr_step_change;
	पूर्णांक curr_step;
पूर्ण;

काष्ठा abx500_अक्षरgalg_battery_data अणु
	पूर्णांक temp;
	पूर्णांक volt;
	पूर्णांक avg_curr;
	पूर्णांक inst_curr;
	पूर्णांक percent;
पूर्ण;

क्रमागत abx500_अक्षरgalg_states अणु
	STATE_HANDHELD_INIT,
	STATE_HANDHELD,
	STATE_CHG_NOT_OK_INIT,
	STATE_CHG_NOT_OK,
	STATE_HW_TEMP_PROTECT_INIT,
	STATE_HW_TEMP_PROTECT,
	STATE_NORMAL_INIT,
	STATE_NORMAL,
	STATE_WAIT_FOR_RECHARGE_INIT,
	STATE_WAIT_FOR_RECHARGE,
	STATE_MAINTEन_अंकCE_A_INIT,
	STATE_MAINTEन_अंकCE_A,
	STATE_MAINTEन_अंकCE_B_INIT,
	STATE_MAINTEन_अंकCE_B,
	STATE_TEMP_UNDEROVER_INIT,
	STATE_TEMP_UNDEROVER,
	STATE_TEMP_LOWHIGH_INIT,
	STATE_TEMP_LOWHIGH,
	STATE_SUSPENDED_INIT,
	STATE_SUSPENDED,
	STATE_OVV_PROTECT_INIT,
	STATE_OVV_PROTECT,
	STATE_SAFETY_TIMER_EXPIRED_INIT,
	STATE_SAFETY_TIMER_EXPIRED,
	STATE_BATT_REMOVED_INIT,
	STATE_BATT_REMOVED,
	STATE_WD_EXPIRED_INIT,
	STATE_WD_EXPIRED,
पूर्ण;

अटल स्थिर अक्षर *states[] = अणु
	"HANDHELD_INIT",
	"HANDHELD",
	"CHG_NOT_OK_INIT",
	"CHG_NOT_OK",
	"HW_TEMP_PROTECT_INIT",
	"HW_TEMP_PROTECT",
	"NORMAL_INIT",
	"NORMAL",
	"WAIT_FOR_RECHARGE_INIT",
	"WAIT_FOR_RECHARGE",
	"MAINTENANCE_A_INIT",
	"MAINTENANCE_A",
	"MAINTENANCE_B_INIT",
	"MAINTENANCE_B",
	"TEMP_UNDEROVER_INIT",
	"TEMP_UNDEROVER",
	"TEMP_LOWHIGH_INIT",
	"TEMP_LOWHIGH",
	"SUSPENDED_INIT",
	"SUSPENDED",
	"OVV_PROTECT_INIT",
	"OVV_PROTECT",
	"SAFETY_TIMER_EXPIRED_INIT",
	"SAFETY_TIMER_EXPIRED",
	"BATT_REMOVED_INIT",
	"BATT_REMOVED",
	"WD_EXPIRED_INIT",
	"WD_EXPIRED",
पूर्ण;

काष्ठा abx500_अक्षरgalg_events अणु
	bool batt_unknown;
	bool मुख्यextchnotok;
	bool batt_ovv;
	bool batt_rem;
	bool btemp_underover;
	bool btemp_lowhigh;
	bool मुख्य_thermal_prot;
	bool usb_thermal_prot;
	bool मुख्य_ovv;
	bool vbus_ovv;
	bool usbअक्षरgernotok;
	bool safety_समयr_expired;
	bool मुख्यtenance_समयr_expired;
	bool ac_wd_expired;
	bool usb_wd_expired;
	bool ac_cv_active;
	bool usb_cv_active;
	bool vbus_collapsed;
पूर्ण;

/**
 * काष्ठा abx500_अक्षरge_curr_maximization - Charger maximization parameters
 * @original_iset:	the non optimized/maximised अक्षरger current
 * @current_iset:	the अक्षरging current used at this moment
 * @test_delta_i:	the delta between the current we want to अक्षरge and the
			current that is really going पूर्णांकo the battery
 * @condition_cnt:	number of iterations needed beक्रमe a new अक्षरger current
			is set
 * @max_current:	maximum अक्षरger current
 * @रुको_cnt:		to aव्योम too fast current step करोwn in हाल of अक्षरger
 *			voltage collapse, we insert this delay between step
 *			करोwn
 * @level:		tells in how many steps the अक्षरging current has been
			increased
 */
काष्ठा abx500_अक्षरge_curr_maximization अणु
	पूर्णांक original_iset;
	पूर्णांक current_iset;
	पूर्णांक test_delta_i;
	पूर्णांक condition_cnt;
	पूर्णांक max_current;
	पूर्णांक रुको_cnt;
	u8 level;
पूर्ण;

क्रमागत maxim_ret अणु
	MAXIM_RET_NOACTION,
	MAXIM_RET_CHANGE,
	MAXIM_RET_IBAT_TOO_HIGH,
पूर्ण;

/**
 * काष्ठा abx500_अक्षरgalg - abx500 Charging algorithm device inक्रमmation
 * @dev:		poपूर्णांकer to the काष्ठाure device
 * @अक्षरge_status:	battery operating status
 * @eoc_cnt:		counter used to determine end-of_अक्षरge
 * @मुख्यtenance_chg:	indicate अगर मुख्यtenance अक्षरge is active
 * @t_hyst_norm		temperature hysteresis when the temperature has been
 *			over or under normal limits
 * @t_hyst_lowhigh	temperature hysteresis when the temperature has been
 *			over or under the high or low limits
 * @अक्षरge_state:	current state of the अक्षरging algorithm
 * @ccm			अक्षरging current maximization parameters
 * @chg_info:		inक्रमmation about connected अक्षरger types
 * @batt_data:		data of the battery
 * @susp_status:	current अक्षरger suspension status
 * @bm:           	Platक्रमm specअगरic battery management inक्रमmation
 * @curr_status:	Current step status क्रम over-current protection
 * @parent:		poपूर्णांकer to the काष्ठा abx500
 * @अक्षरgalg_psy:	काष्ठाure that holds the battery properties exposed by
 *			the अक्षरging algorithm
 * @events:		काष्ठाure क्रम inक्रमmation about events triggered
 * @अक्षरgalg_wq:		work queue क्रम running the अक्षरging algorithm
 * @अक्षरgalg_periodic_work:	work to run the अक्षरging algorithm periodically
 * @अक्षरgalg_wd_work:		work to kick the अक्षरger watchकरोg periodically
 * @अक्षरgalg_work:		work to run the अक्षरging algorithm instantly
 * @safety_समयr:		अक्षरging safety समयr
 * @मुख्यtenance_समयr:		मुख्यtenance अक्षरging समयr
 * @अक्षरgalg_kobject:		काष्ठाure of type kobject
 */
काष्ठा abx500_अक्षरgalg अणु
	काष्ठा device *dev;
	पूर्णांक अक्षरge_status;
	पूर्णांक eoc_cnt;
	bool मुख्यtenance_chg;
	पूर्णांक t_hyst_norm;
	पूर्णांक t_hyst_lowhigh;
	क्रमागत abx500_अक्षरgalg_states अक्षरge_state;
	काष्ठा abx500_अक्षरge_curr_maximization ccm;
	काष्ठा abx500_अक्षरgalg_अक्षरger_info chg_info;
	काष्ठा abx500_अक्षरgalg_battery_data batt_data;
	काष्ठा abx500_अक्षरgalg_suspension_status susp_status;
	काष्ठा ab8500 *parent;
	काष्ठा abx500_अक्षरgalg_current_step_status curr_status;
	काष्ठा abx500_bm_data *bm;
	काष्ठा घातer_supply *अक्षरgalg_psy;
	काष्ठा ux500_अक्षरger *ac_chg;
	काष्ठा ux500_अक्षरger *usb_chg;
	काष्ठा abx500_अक्षरgalg_events events;
	काष्ठा workqueue_काष्ठा *अक्षरgalg_wq;
	काष्ठा delayed_work अक्षरgalg_periodic_work;
	काष्ठा delayed_work अक्षरgalg_wd_work;
	काष्ठा work_काष्ठा अक्षरgalg_work;
	काष्ठा hrसमयr safety_समयr;
	काष्ठा hrसमयr मुख्यtenance_समयr;
	काष्ठा kobject अक्षरgalg_kobject;
पूर्ण;

/*External अक्षरger prepare notअगरier*/
BLOCKING_NOTIFIER_HEAD(अक्षरger_notअगरier_list);

/* Main battery properties */
अटल क्रमागत घातer_supply_property abx500_अक्षरgalg_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_HEALTH,
पूर्ण;

काष्ठा abx500_अक्षरgalg_sysfs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा abx500_अक्षरgalg *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा abx500_अक्षरgalg *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

/**
 * abx500_अक्षरgalg_safety_समयr_expired() - Expiration of the safety समयr
 * @समयr:     poपूर्णांकer to the hrसमयr काष्ठाure
 *
 * This function माला_लो called when the safety समयr क्रम the अक्षरger
 * expires
 */
अटल क्रमागत hrसमयr_restart
abx500_अक्षरgalg_safety_समयr_expired(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा abx500_अक्षरgalg *di = container_of(समयr, काष्ठा abx500_अक्षरgalg,
						  safety_समयr);
	dev_err(di->dev, "Safety timer expired\n");
	di->events.safety_समयr_expired = true;

	/* Trigger execution of the algorithm instantly */
	queue_work(di->अक्षरgalg_wq, &di->अक्षरgalg_work);

	वापस HRTIMER_NORESTART;
पूर्ण

/**
 * abx500_अक्षरgalg_मुख्यtenance_समयr_expired() - Expiration of
 * the मुख्यtenance समयr
 * @समयr:     poपूर्णांकer to the समयr काष्ठाure
 *
 * This function माला_लो called when the मुख्यtenence समयr
 * expires
 */
अटल क्रमागत hrसमयr_restart
abx500_अक्षरgalg_मुख्यtenance_समयr_expired(काष्ठा hrसमयr *समयr)
अणु

	काष्ठा abx500_अक्षरgalg *di = container_of(समयr, काष्ठा abx500_अक्षरgalg,
						  मुख्यtenance_समयr);

	dev_dbg(di->dev, "Maintenance timer expired\n");
	di->events.मुख्यtenance_समयr_expired = true;

	/* Trigger execution of the algorithm instantly */
	queue_work(di->अक्षरgalg_wq, &di->अक्षरgalg_work);

	वापस HRTIMER_NORESTART;
पूर्ण

/**
 * abx500_अक्षरgalg_state_to() - Change अक्षरge state
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 *
 * This function माला_लो called when a अक्षरge state change should occur
 */
अटल व्योम abx500_अक्षरgalg_state_to(काष्ठा abx500_अक्षरgalg *di,
	क्रमागत abx500_अक्षरgalg_states state)
अणु
	dev_dbg(di->dev,
		"State changed: %s (From state: [%d] %s =to=> [%d] %s )\n",
		di->अक्षरge_state == state ? "NO" : "YES",
		di->अक्षरge_state,
		states[di->अक्षरge_state],
		state,
		states[state]);

	di->अक्षरge_state = state;
पूर्ण

अटल पूर्णांक abx500_अक्षरgalg_check_अक्षरger_enable(काष्ठा abx500_अक्षरgalg *di)
अणु
	चयन (di->अक्षरge_state) अणु
	हाल STATE_NORMAL:
	हाल STATE_MAINTEन_अंकCE_A:
	हाल STATE_MAINTEन_अंकCE_B:
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (di->chg_info.अक्षरger_type & USB_CHG) अणु
		वापस di->usb_chg->ops.check_enable(di->usb_chg,
			di->bm->bat_type[di->bm->batt_id].normal_vol_lvl,
			di->bm->bat_type[di->bm->batt_id].normal_cur_lvl);
	पूर्ण अन्यथा अगर ((di->chg_info.अक्षरger_type & AC_CHG) &&
		   !(di->ac_chg->बाह्यal)) अणु
		वापस di->ac_chg->ops.check_enable(di->ac_chg,
			di->bm->bat_type[di->bm->batt_id].normal_vol_lvl,
			di->bm->bat_type[di->bm->batt_id].normal_cur_lvl);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * abx500_अक्षरgalg_check_अक्षरger_connection() - Check अक्षरger connection change
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 *
 * This function will check अगर there is a change in the अक्षरger connection
 * and change अक्षरge state accordingly. AC has precedence over USB.
 */
अटल पूर्णांक abx500_अक्षरgalg_check_अक्षरger_connection(काष्ठा abx500_अक्षरgalg *di)
अणु
	अगर (di->chg_info.conn_chg != di->chg_info.prev_conn_chg ||
		di->susp_status.suspended_change) अणु
		/*
		 * Charger state changed or suspension
		 * has changed since last update
		 */
		अगर ((di->chg_info.conn_chg & AC_CHG) &&
			!di->susp_status.ac_suspended) अणु
			dev_dbg(di->dev, "Charging source is AC\n");
			अगर (di->chg_info.अक्षरger_type != AC_CHG) अणु
				di->chg_info.अक्षरger_type = AC_CHG;
				abx500_अक्षरgalg_state_to(di, STATE_NORMAL_INIT);
			पूर्ण
		पूर्ण अन्यथा अगर ((di->chg_info.conn_chg & USB_CHG) &&
			!di->susp_status.usb_suspended) अणु
			dev_dbg(di->dev, "Charging source is USB\n");
			di->chg_info.अक्षरger_type = USB_CHG;
			abx500_अक्षरgalg_state_to(di, STATE_NORMAL_INIT);
		पूर्ण अन्यथा अगर (di->chg_info.conn_chg &&
			(di->susp_status.ac_suspended ||
			di->susp_status.usb_suspended)) अणु
			dev_dbg(di->dev, "Charging is suspended\n");
			di->chg_info.अक्षरger_type = NO_CHG;
			abx500_अक्षरgalg_state_to(di, STATE_SUSPENDED_INIT);
		पूर्ण अन्यथा अणु
			dev_dbg(di->dev, "Charging source is OFF\n");
			di->chg_info.अक्षरger_type = NO_CHG;
			abx500_अक्षरgalg_state_to(di, STATE_HANDHELD_INIT);
		पूर्ण
		di->chg_info.prev_conn_chg = di->chg_info.conn_chg;
		di->susp_status.suspended_change = false;
	पूर्ण
	वापस di->chg_info.conn_chg;
पूर्ण

/**
 * abx500_अक्षरgalg_check_current_step_status() - Check अक्षरging current
 * step status.
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 *
 * This function will check अगर there is a change in the अक्षरging current step
 * and change अक्षरge state accordingly.
 */
अटल व्योम abx500_अक्षरgalg_check_current_step_status
	(काष्ठा abx500_अक्षरgalg *di)
अणु
	अगर (di->curr_status.curr_step_change)
		abx500_अक्षरgalg_state_to(di, STATE_NORMAL_INIT);
	di->curr_status.curr_step_change = false;
पूर्ण

/**
 * abx500_अक्षरgalg_start_safety_समयr() - Start अक्षरging safety समयr
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 *
 * The safety समयr is used to aव्योम overअक्षरging of old or bad batteries.
 * There are dअगरferent समयrs क्रम AC and USB
 */
अटल व्योम abx500_अक्षरgalg_start_safety_समयr(काष्ठा abx500_अक्षरgalg *di)
अणु
	/* Charger-dependent expiration समय in hours*/
	पूर्णांक समयr_expiration = 0;

	चयन (di->chg_info.अक्षरger_type) अणु
	हाल AC_CHG:
		समयr_expiration = di->bm->मुख्य_safety_पंचांगr_h;
		अवरोध;

	हाल USB_CHG:
		समयr_expiration = di->bm->usb_safety_पंचांगr_h;
		अवरोध;

	शेष:
		dev_err(di->dev, "Unknown charger to charge from\n");
		अवरोध;
	पूर्ण

	di->events.safety_समयr_expired = false;
	hrसमयr_set_expires_range(&di->safety_समयr,
		kसमय_set(समयr_expiration * ONE_HOUR_IN_SECONDS, 0),
		kसमय_set(FIVE_MINUTES_IN_SECONDS, 0));
	hrसमयr_start_expires(&di->safety_समयr, HRTIMER_MODE_REL);
पूर्ण

/**
 * abx500_अक्षरgalg_stop_safety_समयr() - Stop अक्षरging safety समयr
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 *
 * The safety समयr is stopped whenever the NORMAL state is निकासed
 */
अटल व्योम abx500_अक्षरgalg_stop_safety_समयr(काष्ठा abx500_अक्षरgalg *di)
अणु
	अगर (hrसमयr_try_to_cancel(&di->safety_समयr) >= 0)
		di->events.safety_समयr_expired = false;
पूर्ण

/**
 * abx500_अक्षरgalg_start_मुख्यtenance_समयr() - Start अक्षरging मुख्यtenance समयr
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 * @duration:	duration of ther मुख्यtenance समयr in hours
 *
 * The मुख्यtenance समयr is used to मुख्यtain the अक्षरge in the battery once
 * the battery is considered full. These समयrs are chosen to match the
 * disअक्षरge curve of the battery
 */
अटल व्योम abx500_अक्षरgalg_start_मुख्यtenance_समयr(काष्ठा abx500_अक्षरgalg *di,
	पूर्णांक duration)
अणु
	hrसमयr_set_expires_range(&di->मुख्यtenance_समयr,
		kसमय_set(duration * ONE_HOUR_IN_SECONDS, 0),
		kसमय_set(FIVE_MINUTES_IN_SECONDS, 0));
	di->events.मुख्यtenance_समयr_expired = false;
	hrसमयr_start_expires(&di->मुख्यtenance_समयr, HRTIMER_MODE_REL);
पूर्ण

/**
 * abx500_अक्षरgalg_stop_मुख्यtenance_समयr() - Stop मुख्यtenance समयr
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 *
 * The मुख्यtenance समयr is stopped whenever मुख्यtenance ends or when another
 * state is entered
 */
अटल व्योम abx500_अक्षरgalg_stop_मुख्यtenance_समयr(काष्ठा abx500_अक्षरgalg *di)
अणु
	अगर (hrसमयr_try_to_cancel(&di->मुख्यtenance_समयr) >= 0)
		di->events.मुख्यtenance_समयr_expired = false;
पूर्ण

/**
 * abx500_अक्षरgalg_kick_watchकरोg() - Kick अक्षरger watchकरोg
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 *
 * The अक्षरger watchकरोg have to be kicked periodically whenever the अक्षरger is
 * on, अन्यथा the ABB will reset the प्रणाली
 */
अटल पूर्णांक abx500_अक्षरgalg_kick_watchकरोg(काष्ठा abx500_अक्षरgalg *di)
अणु
	/* Check अगर अक्षरger exists and kick watchकरोg अगर अक्षरging */
	अगर (di->ac_chg && di->ac_chg->ops.kick_wd &&
	    di->chg_info.online_chg & AC_CHG) अणु
		/*
		 * If AB अक्षरger watchकरोg expired, pm2xxx अक्षरging
		 * माला_लो disabled. To be safe, kick both AB अक्षरger watchकरोg
		 * and pm2xxx watchकरोg.
		 */
		अगर (di->ac_chg->बाह्यal &&
		    di->usb_chg && di->usb_chg->ops.kick_wd)
			di->usb_chg->ops.kick_wd(di->usb_chg);

		वापस di->ac_chg->ops.kick_wd(di->ac_chg);
	पूर्ण
	अन्यथा अगर (di->usb_chg && di->usb_chg->ops.kick_wd &&
			di->chg_info.online_chg & USB_CHG)
		वापस di->usb_chg->ops.kick_wd(di->usb_chg);

	वापस -ENXIO;
पूर्ण

/**
 * abx500_अक्षरgalg_ac_en() - Turn on/off the AC अक्षरger
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 * @enable:	अक्षरger on/off
 * @vset:	requested अक्षरger output voltage
 * @iset:	requested अक्षरger output current
 *
 * The AC अक्षरger will be turned on/off with the requested अक्षरge voltage and
 * current
 */
अटल पूर्णांक abx500_अक्षरgalg_ac_en(काष्ठा abx500_अक्षरgalg *di, पूर्णांक enable,
	पूर्णांक vset, पूर्णांक iset)
अणु
	अटल पूर्णांक abx500_अक्षरgalg_ex_ac_enable_toggle;

	अगर (!di->ac_chg || !di->ac_chg->ops.enable)
		वापस -ENXIO;

	/* Select maximum of what both the अक्षरger and the battery supports */
	अगर (di->ac_chg->max_out_volt)
		vset = min(vset, di->ac_chg->max_out_volt);
	अगर (di->ac_chg->max_out_curr)
		iset = min(iset, di->ac_chg->max_out_curr);

	di->chg_info.ac_iset = iset;
	di->chg_info.ac_vset = vset;

	/* Enable बाह्यal अक्षरger */
	अगर (enable && di->ac_chg->बाह्यal &&
	    !abx500_अक्षरgalg_ex_ac_enable_toggle) अणु
		blocking_notअगरier_call_chain(&अक्षरger_notअगरier_list,
					     0, di->dev);
		abx500_अक्षरgalg_ex_ac_enable_toggle++;
	पूर्ण

	वापस di->ac_chg->ops.enable(di->ac_chg, enable, vset, iset);
पूर्ण

/**
 * abx500_अक्षरgalg_usb_en() - Turn on/off the USB अक्षरger
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 * @enable:	अक्षरger on/off
 * @vset:	requested अक्षरger output voltage
 * @iset:	requested अक्षरger output current
 *
 * The USB अक्षरger will be turned on/off with the requested अक्षरge voltage and
 * current
 */
अटल पूर्णांक abx500_अक्षरgalg_usb_en(काष्ठा abx500_अक्षरgalg *di, पूर्णांक enable,
	पूर्णांक vset, पूर्णांक iset)
अणु
	अगर (!di->usb_chg || !di->usb_chg->ops.enable)
		वापस -ENXIO;

	/* Select maximum of what both the अक्षरger and the battery supports */
	अगर (di->usb_chg->max_out_volt)
		vset = min(vset, di->usb_chg->max_out_volt);
	अगर (di->usb_chg->max_out_curr)
		iset = min(iset, di->usb_chg->max_out_curr);

	di->chg_info.usb_iset = iset;
	di->chg_info.usb_vset = vset;

	वापस di->usb_chg->ops.enable(di->usb_chg, enable, vset, iset);
पूर्ण

/**
 * abx500_अक्षरgalg_update_chg_curr() - Update अक्षरger current
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 * @iset:	requested अक्षरger output current
 *
 * The अक्षरger output current will be updated क्रम the अक्षरger
 * that is currently in use
 */
अटल पूर्णांक abx500_अक्षरgalg_update_chg_curr(काष्ठा abx500_अक्षरgalg *di,
		पूर्णांक iset)
अणु
	/* Check अगर अक्षरger exists and update current अगर अक्षरging */
	अगर (di->ac_chg && di->ac_chg->ops.update_curr &&
			di->chg_info.अक्षरger_type & AC_CHG) अणु
		/*
		 * Select maximum of what both the अक्षरger
		 * and the battery supports
		 */
		अगर (di->ac_chg->max_out_curr)
			iset = min(iset, di->ac_chg->max_out_curr);

		di->chg_info.ac_iset = iset;

		वापस di->ac_chg->ops.update_curr(di->ac_chg, iset);
	पूर्ण अन्यथा अगर (di->usb_chg && di->usb_chg->ops.update_curr &&
			di->chg_info.अक्षरger_type & USB_CHG) अणु
		/*
		 * Select maximum of what both the अक्षरger
		 * and the battery supports
		 */
		अगर (di->usb_chg->max_out_curr)
			iset = min(iset, di->usb_chg->max_out_curr);

		di->chg_info.usb_iset = iset;

		वापस di->usb_chg->ops.update_curr(di->usb_chg, iset);
	पूर्ण

	वापस -ENXIO;
पूर्ण

/**
 * abx500_अक्षरgalg_stop_अक्षरging() - Stop अक्षरging
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 *
 * This function is called from any state where अक्षरging should be stopped.
 * All अक्षरging is disabled and all status parameters and समयrs are changed
 * accordingly
 */
अटल व्योम abx500_अक्षरgalg_stop_अक्षरging(काष्ठा abx500_अक्षरgalg *di)
अणु
	abx500_अक्षरgalg_ac_en(di, false, 0, 0);
	abx500_अक्षरgalg_usb_en(di, false, 0, 0);
	abx500_अक्षरgalg_stop_safety_समयr(di);
	abx500_अक्षरgalg_stop_मुख्यtenance_समयr(di);
	di->अक्षरge_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
	di->मुख्यtenance_chg = false;
	cancel_delayed_work(&di->अक्षरgalg_wd_work);
	घातer_supply_changed(di->अक्षरgalg_psy);
पूर्ण

/**
 * abx500_अक्षरgalg_hold_अक्षरging() - Pauses अक्षरging
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 *
 * This function is called in the हाल where मुख्यtenance अक्षरging has been
 * disabled and instead a battery voltage mode is entered to check when the
 * battery voltage has reached a certain reअक्षरge voltage
 */
अटल व्योम abx500_अक्षरgalg_hold_अक्षरging(काष्ठा abx500_अक्षरgalg *di)
अणु
	abx500_अक्षरgalg_ac_en(di, false, 0, 0);
	abx500_अक्षरgalg_usb_en(di, false, 0, 0);
	abx500_अक्षरgalg_stop_safety_समयr(di);
	abx500_अक्षरgalg_stop_मुख्यtenance_समयr(di);
	di->अक्षरge_status = POWER_SUPPLY_STATUS_CHARGING;
	di->मुख्यtenance_chg = false;
	cancel_delayed_work(&di->अक्षरgalg_wd_work);
	घातer_supply_changed(di->अक्षरgalg_psy);
पूर्ण

/**
 * abx500_अक्षरgalg_start_अक्षरging() - Start the अक्षरger
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 * @vset:	requested अक्षरger output voltage
 * @iset:	requested अक्षरger output current
 *
 * A अक्षरger will be enabled depending on the requested अक्षरger type that was
 * detected previously.
 */
अटल व्योम abx500_अक्षरgalg_start_अक्षरging(काष्ठा abx500_अक्षरgalg *di,
	पूर्णांक vset, पूर्णांक iset)
अणु
	चयन (di->chg_info.अक्षरger_type) अणु
	हाल AC_CHG:
		dev_dbg(di->dev,
			"AC parameters: Vset %d, Ich %d\n", vset, iset);
		abx500_अक्षरgalg_usb_en(di, false, 0, 0);
		abx500_अक्षरgalg_ac_en(di, true, vset, iset);
		अवरोध;

	हाल USB_CHG:
		dev_dbg(di->dev,
			"USB parameters: Vset %d, Ich %d\n", vset, iset);
		abx500_अक्षरgalg_ac_en(di, false, 0, 0);
		abx500_अक्षरgalg_usb_en(di, true, vset, iset);
		अवरोध;

	शेष:
		dev_err(di->dev, "Unknown charger to charge from\n");
		अवरोध;
	पूर्ण
पूर्ण

/**
 * abx500_अक्षरgalg_check_temp() - Check battery temperature ranges
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 *
 * The battery temperature is checked against the predefined limits and the
 * अक्षरge state is changed accordingly
 */
अटल व्योम abx500_अक्षरgalg_check_temp(काष्ठा abx500_अक्षरgalg *di)
अणु
	अगर (di->batt_data.temp > (di->bm->temp_low + di->t_hyst_norm) &&
		di->batt_data.temp < (di->bm->temp_high - di->t_hyst_norm)) अणु
		/* Temp OK! */
		di->events.btemp_underover = false;
		di->events.btemp_lowhigh = false;
		di->t_hyst_norm = 0;
		di->t_hyst_lowhigh = 0;
	पूर्ण अन्यथा अणु
		अगर (((di->batt_data.temp >= di->bm->temp_high) &&
			(di->batt_data.temp <
				(di->bm->temp_over - di->t_hyst_lowhigh))) ||
			((di->batt_data.temp >
				(di->bm->temp_under + di->t_hyst_lowhigh)) &&
			(di->batt_data.temp <= di->bm->temp_low))) अणु
			/* TEMP minor!!!!! */
			di->events.btemp_underover = false;
			di->events.btemp_lowhigh = true;
			di->t_hyst_norm = di->bm->temp_hysteresis;
			di->t_hyst_lowhigh = 0;
		पूर्ण अन्यथा अगर (di->batt_data.temp <= di->bm->temp_under ||
			di->batt_data.temp >= di->bm->temp_over) अणु
			/* TEMP major!!!!! */
			di->events.btemp_underover = true;
			di->events.btemp_lowhigh = false;
			di->t_hyst_norm = 0;
			di->t_hyst_lowhigh = di->bm->temp_hysteresis;
		पूर्ण अन्यथा अणु
		/* Within hysteresis */
		dev_dbg(di->dev, "Within hysteresis limit temp: %d "
				"hyst_lowhigh %d, hyst normal %d\n",
				di->batt_data.temp, di->t_hyst_lowhigh,
				di->t_hyst_norm);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * abx500_अक्षरgalg_check_अक्षरger_voltage() - Check अक्षरger voltage
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 *
 * Charger voltage is checked against maximum limit
 */
अटल व्योम abx500_अक्षरgalg_check_अक्षरger_voltage(काष्ठा abx500_अक्षरgalg *di)
अणु
	अगर (di->chg_info.usb_volt > di->bm->chg_params->usb_volt_max)
		di->chg_info.usb_chg_ok = false;
	अन्यथा
		di->chg_info.usb_chg_ok = true;

	अगर (di->chg_info.ac_volt > di->bm->chg_params->ac_volt_max)
		di->chg_info.ac_chg_ok = false;
	अन्यथा
		di->chg_info.ac_chg_ok = true;

पूर्ण

/**
 * abx500_अक्षरgalg_end_of_अक्षरge() - Check अगर end-of-अक्षरge criteria is fulfilled
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 *
 * End-of-अक्षरge criteria is fulfilled when the battery voltage is above a
 * certain limit and the battery current is below a certain limit क्रम a
 * predefined number of consecutive seconds. If true, the battery is full
 */
अटल व्योम abx500_अक्षरgalg_end_of_अक्षरge(काष्ठा abx500_अक्षरgalg *di)
अणु
	अगर (di->अक्षरge_status == POWER_SUPPLY_STATUS_CHARGING &&
		di->अक्षरge_state == STATE_NORMAL &&
		!di->मुख्यtenance_chg && (di->batt_data.volt >=
		di->bm->bat_type[di->bm->batt_id].termination_vol ||
		di->events.usb_cv_active || di->events.ac_cv_active) &&
		di->batt_data.avg_curr <
		di->bm->bat_type[di->bm->batt_id].termination_curr &&
		di->batt_data.avg_curr > 0) अणु
		अगर (++di->eoc_cnt >= EOC_COND_CNT) अणु
			di->eoc_cnt = 0;
			di->अक्षरge_status = POWER_SUPPLY_STATUS_FULL;
			di->मुख्यtenance_chg = true;
			dev_dbg(di->dev, "EOC reached!\n");
			घातer_supply_changed(di->अक्षरgalg_psy);
		पूर्ण अन्यथा अणु
			dev_dbg(di->dev,
				" EOC limit reached for the %d"
				" time, out of %d before EOC\n",
				di->eoc_cnt,
				EOC_COND_CNT);
		पूर्ण
	पूर्ण अन्यथा अणु
		di->eoc_cnt = 0;
	पूर्ण
पूर्ण

अटल व्योम init_maxim_chg_curr(काष्ठा abx500_अक्षरgalg *di)
अणु
	di->ccm.original_iset =
		di->bm->bat_type[di->bm->batt_id].normal_cur_lvl;
	di->ccm.current_iset =
		di->bm->bat_type[di->bm->batt_id].normal_cur_lvl;
	di->ccm.test_delta_i = di->bm->maxi->अक्षरger_curr_step;
	di->ccm.max_current = di->bm->maxi->chg_curr;
	di->ccm.condition_cnt = di->bm->maxi->रुको_cycles;
	di->ccm.level = 0;
पूर्ण

/**
 * abx500_अक्षरgalg_chg_curr_maxim - increases the अक्षरger current to
 *			compensate क्रम the प्रणाली load
 * @di		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 *
 * This maximization function is used to उठाओ the अक्षरger current to get the
 * battery current as बंद to the optimal value as possible. The battery
 * current during अक्षरging is affected by the प्रणाली load
 */
अटल क्रमागत maxim_ret abx500_अक्षरgalg_chg_curr_maxim(काष्ठा abx500_अक्षरgalg *di)
अणु
	पूर्णांक delta_i;

	अगर (!di->bm->maxi->ena_maxi)
		वापस MAXIM_RET_NOACTION;

	delta_i = di->ccm.original_iset - di->batt_data.inst_curr;

	अगर (di->events.vbus_collapsed) अणु
		dev_dbg(di->dev, "Charger voltage has collapsed %d\n",
				di->ccm.रुको_cnt);
		अगर (di->ccm.रुको_cnt == 0) अणु
			dev_dbg(di->dev, "lowering current\n");
			di->ccm.रुको_cnt++;
			di->ccm.condition_cnt = di->bm->maxi->रुको_cycles;
			di->ccm.max_current =
				di->ccm.current_iset - di->ccm.test_delta_i;
			di->ccm.current_iset = di->ccm.max_current;
			di->ccm.level--;
			वापस MAXIM_RET_CHANGE;
		पूर्ण अन्यथा अणु
			dev_dbg(di->dev, "waiting\n");
			/* Let's go in here twice beक्रमe lowering curr again */
			di->ccm.रुको_cnt = (di->ccm.रुको_cnt + 1) % 3;
			वापस MAXIM_RET_NOACTION;
		पूर्ण
	पूर्ण

	di->ccm.रुको_cnt = 0;

	अगर ((di->batt_data.inst_curr > di->ccm.original_iset)) अणु
		dev_dbg(di->dev, " Maximization Ibat (%dmA) too high"
			" (limit %dmA) (current iset: %dmA)!\n",
			di->batt_data.inst_curr, di->ccm.original_iset,
			di->ccm.current_iset);

		अगर (di->ccm.current_iset == di->ccm.original_iset)
			वापस MAXIM_RET_NOACTION;

		di->ccm.condition_cnt = di->bm->maxi->रुको_cycles;
		di->ccm.current_iset = di->ccm.original_iset;
		di->ccm.level = 0;

		वापस MAXIM_RET_IBAT_TOO_HIGH;
	पूर्ण

	अगर (delta_i > di->ccm.test_delta_i &&
		(di->ccm.current_iset + di->ccm.test_delta_i) <
		di->ccm.max_current) अणु
		अगर (di->ccm.condition_cnt-- == 0) अणु
			/* Increse the iset with cco.test_delta_i */
			di->ccm.condition_cnt = di->bm->maxi->रुको_cycles;
			di->ccm.current_iset += di->ccm.test_delta_i;
			di->ccm.level++;
			dev_dbg(di->dev, " Maximization needed, increase"
				" with %d mA to %dmA (Optimal ibat: %d)"
				" Level %d\n",
				di->ccm.test_delta_i,
				di->ccm.current_iset,
				di->ccm.original_iset,
				di->ccm.level);
			वापस MAXIM_RET_CHANGE;
		पूर्ण अन्यथा अणु
			वापस MAXIM_RET_NOACTION;
		पूर्ण
	पूर्ण  अन्यथा अणु
		di->ccm.condition_cnt = di->bm->maxi->रुको_cycles;
		वापस MAXIM_RET_NOACTION;
	पूर्ण
पूर्ण

अटल व्योम handle_maxim_chg_curr(काष्ठा abx500_अक्षरgalg *di)
अणु
	क्रमागत maxim_ret ret;
	पूर्णांक result;

	ret = abx500_अक्षरgalg_chg_curr_maxim(di);
	चयन (ret) अणु
	हाल MAXIM_RET_CHANGE:
		result = abx500_अक्षरgalg_update_chg_curr(di,
			di->ccm.current_iset);
		अगर (result)
			dev_err(di->dev, "failed to set chg curr\n");
		अवरोध;
	हाल MAXIM_RET_IBAT_TOO_HIGH:
		result = abx500_अक्षरgalg_update_chg_curr(di,
			di->bm->bat_type[di->bm->batt_id].normal_cur_lvl);
		अगर (result)
			dev_err(di->dev, "failed to set chg curr\n");
		अवरोध;

	हाल MAXIM_RET_NOACTION:
	शेष:
		/* Do nothing..*/
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक abx500_अक्षरgalg_get_ext_psy_data(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा घातer_supply *psy;
	काष्ठा घातer_supply *ext = dev_get_drvdata(dev);
	स्थिर अक्षर **supplicants = (स्थिर अक्षर **)ext->supplied_to;
	काष्ठा abx500_अक्षरgalg *di;
	जोड़ घातer_supply_propval ret;
	पूर्णांक j;
	bool capacity_updated = false;

	psy = (काष्ठा घातer_supply *)data;
	di = घातer_supply_get_drvdata(psy);
	/* For all psy where the driver name appears in any supplied_to */
	j = match_string(supplicants, ext->num_supplicants, psy->desc->name);
	अगर (j < 0)
		वापस 0;

	/*
	 *  If बाह्यal is not रेजिस्टरing 'POWER_SUPPLY_PROP_CAPACITY' to its
	 * property because of handling that sysfs entry on its own, this is
	 * the place to get the battery capacity.
	 */
	अगर (!घातer_supply_get_property(ext, POWER_SUPPLY_PROP_CAPACITY, &ret)) अणु
		di->batt_data.percent = ret.पूर्णांकval;
		capacity_updated = true;
	पूर्ण

	/* Go through all properties क्रम the psy */
	क्रम (j = 0; j < ext->desc->num_properties; j++) अणु
		क्रमागत घातer_supply_property prop;
		prop = ext->desc->properties[j];

		/*
		 * Initialize अक्षरgers अगर not alपढ़ोy करोne.
		 * The ab8500_अक्षरger*/
		अगर (!di->ac_chg &&
			ext->desc->type == POWER_SUPPLY_TYPE_MAINS)
			di->ac_chg = psy_to_ux500_अक्षरger(ext);
		अन्यथा अगर (!di->usb_chg &&
			ext->desc->type == POWER_SUPPLY_TYPE_USB)
			di->usb_chg = psy_to_ux500_अक्षरger(ext);

		अगर (घातer_supply_get_property(ext, prop, &ret))
			जारी;
		चयन (prop) अणु
		हाल POWER_SUPPLY_PROP_PRESENT:
			चयन (ext->desc->type) अणु
			हाल POWER_SUPPLY_TYPE_BATTERY:
				/* Battery present */
				अगर (ret.पूर्णांकval)
					di->events.batt_rem = false;
				/* Battery हटाओd */
				अन्यथा
					di->events.batt_rem = true;
				अवरोध;
			हाल POWER_SUPPLY_TYPE_MAINS:
				/* AC disconnected */
				अगर (!ret.पूर्णांकval &&
					(di->chg_info.conn_chg & AC_CHG)) अणु
					di->chg_info.prev_conn_chg =
						di->chg_info.conn_chg;
					di->chg_info.conn_chg &= ~AC_CHG;
				पूर्ण
				/* AC connected */
				अन्यथा अगर (ret.पूर्णांकval &&
					!(di->chg_info.conn_chg & AC_CHG)) अणु
					di->chg_info.prev_conn_chg =
						di->chg_info.conn_chg;
					di->chg_info.conn_chg |= AC_CHG;
				पूर्ण
				अवरोध;
			हाल POWER_SUPPLY_TYPE_USB:
				/* USB disconnected */
				अगर (!ret.पूर्णांकval &&
					(di->chg_info.conn_chg & USB_CHG)) अणु
					di->chg_info.prev_conn_chg =
						di->chg_info.conn_chg;
					di->chg_info.conn_chg &= ~USB_CHG;
				पूर्ण
				/* USB connected */
				अन्यथा अगर (ret.पूर्णांकval &&
					!(di->chg_info.conn_chg & USB_CHG)) अणु
					di->chg_info.prev_conn_chg =
						di->chg_info.conn_chg;
					di->chg_info.conn_chg |= USB_CHG;
				पूर्ण
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;

		हाल POWER_SUPPLY_PROP_ONLINE:
			चयन (ext->desc->type) अणु
			हाल POWER_SUPPLY_TYPE_BATTERY:
				अवरोध;
			हाल POWER_SUPPLY_TYPE_MAINS:
				/* AC offline */
				अगर (!ret.पूर्णांकval &&
					(di->chg_info.online_chg & AC_CHG)) अणु
					di->chg_info.prev_online_chg =
						di->chg_info.online_chg;
					di->chg_info.online_chg &= ~AC_CHG;
				पूर्ण
				/* AC online */
				अन्यथा अगर (ret.पूर्णांकval &&
					!(di->chg_info.online_chg & AC_CHG)) अणु
					di->chg_info.prev_online_chg =
						di->chg_info.online_chg;
					di->chg_info.online_chg |= AC_CHG;
					queue_delayed_work(di->अक्षरgalg_wq,
						&di->अक्षरgalg_wd_work, 0);
				पूर्ण
				अवरोध;
			हाल POWER_SUPPLY_TYPE_USB:
				/* USB offline */
				अगर (!ret.पूर्णांकval &&
					(di->chg_info.online_chg & USB_CHG)) अणु
					di->chg_info.prev_online_chg =
						di->chg_info.online_chg;
					di->chg_info.online_chg &= ~USB_CHG;
				पूर्ण
				/* USB online */
				अन्यथा अगर (ret.पूर्णांकval &&
					!(di->chg_info.online_chg & USB_CHG)) अणु
					di->chg_info.prev_online_chg =
						di->chg_info.online_chg;
					di->chg_info.online_chg |= USB_CHG;
					queue_delayed_work(di->अक्षरgalg_wq,
						&di->अक्षरgalg_wd_work, 0);
				पूर्ण
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;

		हाल POWER_SUPPLY_PROP_HEALTH:
			चयन (ext->desc->type) अणु
			हाल POWER_SUPPLY_TYPE_BATTERY:
				अवरोध;
			हाल POWER_SUPPLY_TYPE_MAINS:
				चयन (ret.पूर्णांकval) अणु
				हाल POWER_SUPPLY_HEALTH_UNSPEC_FAILURE:
					di->events.मुख्यextchnotok = true;
					di->events.मुख्य_thermal_prot = false;
					di->events.मुख्य_ovv = false;
					di->events.ac_wd_expired = false;
					अवरोध;
				हाल POWER_SUPPLY_HEALTH_DEAD:
					di->events.ac_wd_expired = true;
					di->events.मुख्यextchnotok = false;
					di->events.मुख्य_ovv = false;
					di->events.मुख्य_thermal_prot = false;
					अवरोध;
				हाल POWER_SUPPLY_HEALTH_COLD:
				हाल POWER_SUPPLY_HEALTH_OVERHEAT:
					di->events.मुख्य_thermal_prot = true;
					di->events.मुख्यextchnotok = false;
					di->events.मुख्य_ovv = false;
					di->events.ac_wd_expired = false;
					अवरोध;
				हाल POWER_SUPPLY_HEALTH_OVERVOLTAGE:
					di->events.मुख्य_ovv = true;
					di->events.मुख्यextchnotok = false;
					di->events.मुख्य_thermal_prot = false;
					di->events.ac_wd_expired = false;
					अवरोध;
				हाल POWER_SUPPLY_HEALTH_GOOD:
					di->events.मुख्य_thermal_prot = false;
					di->events.मुख्यextchnotok = false;
					di->events.मुख्य_ovv = false;
					di->events.ac_wd_expired = false;
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
				अवरोध;

			हाल POWER_SUPPLY_TYPE_USB:
				चयन (ret.पूर्णांकval) अणु
				हाल POWER_SUPPLY_HEALTH_UNSPEC_FAILURE:
					di->events.usbअक्षरgernotok = true;
					di->events.usb_thermal_prot = false;
					di->events.vbus_ovv = false;
					di->events.usb_wd_expired = false;
					अवरोध;
				हाल POWER_SUPPLY_HEALTH_DEAD:
					di->events.usb_wd_expired = true;
					di->events.usbअक्षरgernotok = false;
					di->events.usb_thermal_prot = false;
					di->events.vbus_ovv = false;
					अवरोध;
				हाल POWER_SUPPLY_HEALTH_COLD:
				हाल POWER_SUPPLY_HEALTH_OVERHEAT:
					di->events.usb_thermal_prot = true;
					di->events.usbअक्षरgernotok = false;
					di->events.vbus_ovv = false;
					di->events.usb_wd_expired = false;
					अवरोध;
				हाल POWER_SUPPLY_HEALTH_OVERVOLTAGE:
					di->events.vbus_ovv = true;
					di->events.usbअक्षरgernotok = false;
					di->events.usb_thermal_prot = false;
					di->events.usb_wd_expired = false;
					अवरोध;
				हाल POWER_SUPPLY_HEALTH_GOOD:
					di->events.usbअक्षरgernotok = false;
					di->events.usb_thermal_prot = false;
					di->events.vbus_ovv = false;
					di->events.usb_wd_expired = false;
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;

		हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
			चयन (ext->desc->type) अणु
			हाल POWER_SUPPLY_TYPE_BATTERY:
				di->batt_data.volt = ret.पूर्णांकval / 1000;
				अवरोध;
			हाल POWER_SUPPLY_TYPE_MAINS:
				di->chg_info.ac_volt = ret.पूर्णांकval / 1000;
				अवरोध;
			हाल POWER_SUPPLY_TYPE_USB:
				di->chg_info.usb_volt = ret.पूर्णांकval / 1000;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;

		हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
			चयन (ext->desc->type) अणु
			हाल POWER_SUPPLY_TYPE_MAINS:
				/* AVG is used to indicate when we are
				 * in CV mode */
				अगर (ret.पूर्णांकval)
					di->events.ac_cv_active = true;
				अन्यथा
					di->events.ac_cv_active = false;

				अवरोध;
			हाल POWER_SUPPLY_TYPE_USB:
				/* AVG is used to indicate when we are
				 * in CV mode */
				अगर (ret.पूर्णांकval)
					di->events.usb_cv_active = true;
				अन्यथा
					di->events.usb_cv_active = false;

				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;

		हाल POWER_SUPPLY_PROP_TECHNOLOGY:
			चयन (ext->desc->type) अणु
			हाल POWER_SUPPLY_TYPE_BATTERY:
				अगर (ret.पूर्णांकval)
					di->events.batt_unknown = false;
				अन्यथा
					di->events.batt_unknown = true;

				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;

		हाल POWER_SUPPLY_PROP_TEMP:
			di->batt_data.temp = ret.पूर्णांकval / 10;
			अवरोध;

		हाल POWER_SUPPLY_PROP_CURRENT_NOW:
			चयन (ext->desc->type) अणु
			हाल POWER_SUPPLY_TYPE_MAINS:
					di->chg_info.ac_curr =
						ret.पूर्णांकval / 1000;
					अवरोध;
			हाल POWER_SUPPLY_TYPE_USB:
					di->chg_info.usb_curr =
						ret.पूर्णांकval / 1000;
				अवरोध;
			हाल POWER_SUPPLY_TYPE_BATTERY:
				di->batt_data.inst_curr = ret.पूर्णांकval / 1000;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;

		हाल POWER_SUPPLY_PROP_CURRENT_AVG:
			चयन (ext->desc->type) अणु
			हाल POWER_SUPPLY_TYPE_BATTERY:
				di->batt_data.avg_curr = ret.पूर्णांकval / 1000;
				अवरोध;
			हाल POWER_SUPPLY_TYPE_USB:
				अगर (ret.पूर्णांकval)
					di->events.vbus_collapsed = true;
				अन्यथा
					di->events.vbus_collapsed = false;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		हाल POWER_SUPPLY_PROP_CAPACITY:
			अगर (!capacity_updated)
				di->batt_data.percent = ret.पूर्णांकval;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * abx500_अक्षरgalg_बाह्यal_घातer_changed() - callback क्रम घातer supply changes
 * @psy:       poपूर्णांकer to the काष्ठाure घातer_supply
 *
 * This function is the entry poपूर्णांक of the poपूर्णांकer बाह्यal_घातer_changed
 * of the काष्ठाure घातer_supply.
 * This function माला_लो executed when there is a change in any बाह्यal घातer
 * supply that this driver needs to be notअगरied of.
 */
अटल व्योम abx500_अक्षरgalg_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	काष्ठा abx500_अक्षरgalg *di = घातer_supply_get_drvdata(psy);

	/*
	 * Trigger execution of the algorithm instantly and पढ़ो
	 * all घातer_supply properties there instead
	 */
	queue_work(di->अक्षरgalg_wq, &di->अक्षरgalg_work);
पूर्ण

/**
 * abx500_अक्षरgalg_algorithm() - Main function क्रम the algorithm
 * @di:		poपूर्णांकer to the abx500_अक्षरgalg काष्ठाure
 *
 * This is the मुख्य control function क्रम the अक्षरging algorithm.
 * It is called periodically or when something happens that will
 * trigger a state change
 */
अटल व्योम abx500_अक्षरgalg_algorithm(काष्ठा abx500_अक्षरgalg *di)
अणु
	पूर्णांक अक्षरger_status;
	पूर्णांक ret;
	पूर्णांक curr_step_lvl;

	/* Collect data from all घातer_supply class devices */
	class_क्रम_each_device(घातer_supply_class, शून्य,
		di->अक्षरgalg_psy, abx500_अक्षरgalg_get_ext_psy_data);

	abx500_अक्षरgalg_end_of_अक्षरge(di);
	abx500_अक्षरgalg_check_temp(di);
	abx500_अक्षरgalg_check_अक्षरger_voltage(di);

	अक्षरger_status = abx500_अक्षरgalg_check_अक्षरger_connection(di);
	abx500_अक्षरgalg_check_current_step_status(di);

	अगर (is_ab8500(di->parent)) अणु
		ret = abx500_अक्षरgalg_check_अक्षरger_enable(di);
		अगर (ret < 0)
			dev_err(di->dev, "Checking charger is enabled error"
					": Returned Value %d\n", ret);
	पूर्ण

	/*
	 * First check अगर we have a अक्षरger connected.
	 * Also we करोn't allow अक्षरging of unknown batteries अगर configured
	 * this way
	 */
	अगर (!अक्षरger_status ||
		(di->events.batt_unknown && !di->bm->chg_unknown_bat)) अणु
		अगर (di->अक्षरge_state != STATE_HANDHELD) अणु
			di->events.safety_समयr_expired = false;
			abx500_अक्षरgalg_state_to(di, STATE_HANDHELD_INIT);
		पूर्ण
	पूर्ण

	/* If suspended, we should not जारी checking the flags */
	अन्यथा अगर (di->अक्षरge_state == STATE_SUSPENDED_INIT ||
		di->अक्षरge_state == STATE_SUSPENDED) अणु
		/* We करोn't करो anything here, just करोn,t जारी */
	पूर्ण

	/* Safety समयr expiration */
	अन्यथा अगर (di->events.safety_समयr_expired) अणु
		अगर (di->अक्षरge_state != STATE_SAFETY_TIMER_EXPIRED)
			abx500_अक्षरgalg_state_to(di,
				STATE_SAFETY_TIMER_EXPIRED_INIT);
	पूर्ण
	/*
	 * Check अगर any पूर्णांकerrupts has occured
	 * that will prevent us from अक्षरging
	 */

	/* Battery हटाओd */
	अन्यथा अगर (di->events.batt_rem) अणु
		अगर (di->अक्षरge_state != STATE_BATT_REMOVED)
			abx500_अक्षरgalg_state_to(di, STATE_BATT_REMOVED_INIT);
	पूर्ण
	/* Main or USB अक्षरger not ok. */
	अन्यथा अगर (di->events.मुख्यextchnotok || di->events.usbअक्षरgernotok) अणु
		/*
		 * If vbus_collapsed is set, we have to lower the अक्षरger
		 * current, which is करोne in the normal state below
		 */
		अगर (di->अक्षरge_state != STATE_CHG_NOT_OK &&
				!di->events.vbus_collapsed)
			abx500_अक्षरgalg_state_to(di, STATE_CHG_NOT_OK_INIT);
	पूर्ण
	/* VBUS, Main or VBAT OVV. */
	अन्यथा अगर (di->events.vbus_ovv ||
			di->events.मुख्य_ovv ||
			di->events.batt_ovv ||
			!di->chg_info.usb_chg_ok ||
			!di->chg_info.ac_chg_ok) अणु
		अगर (di->अक्षरge_state != STATE_OVV_PROTECT)
			abx500_अक्षरgalg_state_to(di, STATE_OVV_PROTECT_INIT);
	पूर्ण
	/* USB Thermal, stop अक्षरging */
	अन्यथा अगर (di->events.मुख्य_thermal_prot ||
		di->events.usb_thermal_prot) अणु
		अगर (di->अक्षरge_state != STATE_HW_TEMP_PROTECT)
			abx500_अक्षरgalg_state_to(di,
				STATE_HW_TEMP_PROTECT_INIT);
	पूर्ण
	/* Battery temp over/under */
	अन्यथा अगर (di->events.btemp_underover) अणु
		अगर (di->अक्षरge_state != STATE_TEMP_UNDEROVER)
			abx500_अक्षरgalg_state_to(di,
				STATE_TEMP_UNDEROVER_INIT);
	पूर्ण
	/* Watchकरोg expired */
	अन्यथा अगर (di->events.ac_wd_expired ||
		di->events.usb_wd_expired) अणु
		अगर (di->अक्षरge_state != STATE_WD_EXPIRED)
			abx500_अक्षरgalg_state_to(di, STATE_WD_EXPIRED_INIT);
	पूर्ण
	/* Battery temp high/low */
	अन्यथा अगर (di->events.btemp_lowhigh) अणु
		अगर (di->अक्षरge_state != STATE_TEMP_LOWHIGH)
			abx500_अक्षरgalg_state_to(di, STATE_TEMP_LOWHIGH_INIT);
	पूर्ण

	dev_dbg(di->dev,
		"[CHARGALG] Vb %d Ib_avg %d Ib_inst %d Tb %d Cap %d Maint %d "
		"State %s Active_chg %d Chg_status %d AC %d USB %d "
		"AC_online %d USB_online %d AC_CV %d USB_CV %d AC_I %d "
		"USB_I %d AC_Vset %d AC_Iset %d USB_Vset %d USB_Iset %d\n",
		di->batt_data.volt,
		di->batt_data.avg_curr,
		di->batt_data.inst_curr,
		di->batt_data.temp,
		di->batt_data.percent,
		di->मुख्यtenance_chg,
		states[di->अक्षरge_state],
		di->chg_info.अक्षरger_type,
		di->अक्षरge_status,
		di->chg_info.conn_chg & AC_CHG,
		di->chg_info.conn_chg & USB_CHG,
		di->chg_info.online_chg & AC_CHG,
		di->chg_info.online_chg & USB_CHG,
		di->events.ac_cv_active,
		di->events.usb_cv_active,
		di->chg_info.ac_curr,
		di->chg_info.usb_curr,
		di->chg_info.ac_vset,
		di->chg_info.ac_iset,
		di->chg_info.usb_vset,
		di->chg_info.usb_iset);

	चयन (di->अक्षरge_state) अणु
	हाल STATE_HANDHELD_INIT:
		abx500_अक्षरgalg_stop_अक्षरging(di);
		di->अक्षरge_status = POWER_SUPPLY_STATUS_DISCHARGING;
		abx500_अक्षरgalg_state_to(di, STATE_HANDHELD);
		fallthrough;

	हाल STATE_HANDHELD:
		अवरोध;

	हाल STATE_SUSPENDED_INIT:
		अगर (di->susp_status.ac_suspended)
			abx500_अक्षरgalg_ac_en(di, false, 0, 0);
		अगर (di->susp_status.usb_suspended)
			abx500_अक्षरgalg_usb_en(di, false, 0, 0);
		abx500_अक्षरgalg_stop_safety_समयr(di);
		abx500_अक्षरgalg_stop_मुख्यtenance_समयr(di);
		di->अक्षरge_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		di->मुख्यtenance_chg = false;
		abx500_अक्षरgalg_state_to(di, STATE_SUSPENDED);
		घातer_supply_changed(di->अक्षरgalg_psy);
		fallthrough;

	हाल STATE_SUSPENDED:
		/* CHARGING is suspended */
		अवरोध;

	हाल STATE_BATT_REMOVED_INIT:
		abx500_अक्षरgalg_stop_अक्षरging(di);
		abx500_अक्षरgalg_state_to(di, STATE_BATT_REMOVED);
		fallthrough;

	हाल STATE_BATT_REMOVED:
		अगर (!di->events.batt_rem)
			abx500_अक्षरgalg_state_to(di, STATE_NORMAL_INIT);
		अवरोध;

	हाल STATE_HW_TEMP_PROTECT_INIT:
		abx500_अक्षरgalg_stop_अक्षरging(di);
		abx500_अक्षरgalg_state_to(di, STATE_HW_TEMP_PROTECT);
		fallthrough;

	हाल STATE_HW_TEMP_PROTECT:
		अगर (!di->events.मुख्य_thermal_prot &&
				!di->events.usb_thermal_prot)
			abx500_अक्षरgalg_state_to(di, STATE_NORMAL_INIT);
		अवरोध;

	हाल STATE_OVV_PROTECT_INIT:
		abx500_अक्षरgalg_stop_अक्षरging(di);
		abx500_अक्षरgalg_state_to(di, STATE_OVV_PROTECT);
		fallthrough;

	हाल STATE_OVV_PROTECT:
		अगर (!di->events.vbus_ovv &&
				!di->events.मुख्य_ovv &&
				!di->events.batt_ovv &&
				di->chg_info.usb_chg_ok &&
				di->chg_info.ac_chg_ok)
			abx500_अक्षरgalg_state_to(di, STATE_NORMAL_INIT);
		अवरोध;

	हाल STATE_CHG_NOT_OK_INIT:
		abx500_अक्षरgalg_stop_अक्षरging(di);
		abx500_अक्षरgalg_state_to(di, STATE_CHG_NOT_OK);
		fallthrough;

	हाल STATE_CHG_NOT_OK:
		अगर (!di->events.मुख्यextchnotok &&
				!di->events.usbअक्षरgernotok)
			abx500_अक्षरgalg_state_to(di, STATE_NORMAL_INIT);
		अवरोध;

	हाल STATE_SAFETY_TIMER_EXPIRED_INIT:
		abx500_अक्षरgalg_stop_अक्षरging(di);
		abx500_अक्षरgalg_state_to(di, STATE_SAFETY_TIMER_EXPIRED);
		fallthrough;

	हाल STATE_SAFETY_TIMER_EXPIRED:
		/* We निकास this state when अक्षरger is हटाओd */
		अवरोध;

	हाल STATE_NORMAL_INIT:
		अगर (di->curr_status.curr_step == CHARGALG_CURR_STEP_LOW)
			abx500_अक्षरgalg_stop_अक्षरging(di);
		अन्यथा अणु
			curr_step_lvl = di->bm->bat_type[
				di->bm->batt_id].normal_cur_lvl
				* di->curr_status.curr_step
				/ CHARGALG_CURR_STEP_HIGH;
			abx500_अक्षरgalg_start_अक्षरging(di,
				di->bm->bat_type[di->bm->batt_id]
				.normal_vol_lvl, curr_step_lvl);
		पूर्ण

		abx500_अक्षरgalg_state_to(di, STATE_NORMAL);
		abx500_अक्षरgalg_start_safety_समयr(di);
		abx500_अक्षरgalg_stop_मुख्यtenance_समयr(di);
		init_maxim_chg_curr(di);
		di->अक्षरge_status = POWER_SUPPLY_STATUS_CHARGING;
		di->eoc_cnt = 0;
		di->मुख्यtenance_chg = false;
		घातer_supply_changed(di->अक्षरgalg_psy);

		अवरोध;

	हाल STATE_NORMAL:
		handle_maxim_chg_curr(di);
		अगर (di->अक्षरge_status == POWER_SUPPLY_STATUS_FULL &&
			di->मुख्यtenance_chg) अणु
			अगर (di->bm->no_मुख्यtenance)
				abx500_अक्षरgalg_state_to(di,
					STATE_WAIT_FOR_RECHARGE_INIT);
			अन्यथा
				abx500_अक्षरgalg_state_to(di,
					STATE_MAINTEन_अंकCE_A_INIT);
		पूर्ण
		अवरोध;

	/* This state will be used when the मुख्यtenance state is disabled */
	हाल STATE_WAIT_FOR_RECHARGE_INIT:
		abx500_अक्षरgalg_hold_अक्षरging(di);
		abx500_अक्षरgalg_state_to(di, STATE_WAIT_FOR_RECHARGE);
		fallthrough;

	हाल STATE_WAIT_FOR_RECHARGE:
		अगर (di->batt_data.percent <=
		    di->bm->bat_type[di->bm->batt_id].
		    reअक्षरge_cap)
			abx500_अक्षरgalg_state_to(di, STATE_NORMAL_INIT);
		अवरोध;

	हाल STATE_MAINTEन_अंकCE_A_INIT:
		abx500_अक्षरgalg_stop_safety_समयr(di);
		abx500_अक्षरgalg_start_मुख्यtenance_समयr(di,
			di->bm->bat_type[
				di->bm->batt_id].मुख्यt_a_chg_समयr_h);
		abx500_अक्षरgalg_start_अक्षरging(di,
			di->bm->bat_type[
				di->bm->batt_id].मुख्यt_a_vol_lvl,
			di->bm->bat_type[
				di->bm->batt_id].मुख्यt_a_cur_lvl);
		abx500_अक्षरgalg_state_to(di, STATE_MAINTEन_अंकCE_A);
		घातer_supply_changed(di->अक्षरgalg_psy);
		fallthrough;

	हाल STATE_MAINTEन_अंकCE_A:
		अगर (di->events.मुख्यtenance_समयr_expired) अणु
			abx500_अक्षरgalg_stop_मुख्यtenance_समयr(di);
			abx500_अक्षरgalg_state_to(di, STATE_MAINTEन_अंकCE_B_INIT);
		पूर्ण
		अवरोध;

	हाल STATE_MAINTEन_अंकCE_B_INIT:
		abx500_अक्षरgalg_start_मुख्यtenance_समयr(di,
			di->bm->bat_type[
				di->bm->batt_id].मुख्यt_b_chg_समयr_h);
		abx500_अक्षरgalg_start_अक्षरging(di,
			di->bm->bat_type[
				di->bm->batt_id].मुख्यt_b_vol_lvl,
			di->bm->bat_type[
				di->bm->batt_id].मुख्यt_b_cur_lvl);
		abx500_अक्षरgalg_state_to(di, STATE_MAINTEन_अंकCE_B);
		घातer_supply_changed(di->अक्षरgalg_psy);
		fallthrough;

	हाल STATE_MAINTEन_अंकCE_B:
		अगर (di->events.मुख्यtenance_समयr_expired) अणु
			abx500_अक्षरgalg_stop_मुख्यtenance_समयr(di);
			abx500_अक्षरgalg_state_to(di, STATE_NORMAL_INIT);
		पूर्ण
		अवरोध;

	हाल STATE_TEMP_LOWHIGH_INIT:
		abx500_अक्षरgalg_start_अक्षरging(di,
			di->bm->bat_type[
				di->bm->batt_id].low_high_vol_lvl,
			di->bm->bat_type[
				di->bm->batt_id].low_high_cur_lvl);
		abx500_अक्षरgalg_stop_मुख्यtenance_समयr(di);
		di->अक्षरge_status = POWER_SUPPLY_STATUS_CHARGING;
		abx500_अक्षरgalg_state_to(di, STATE_TEMP_LOWHIGH);
		घातer_supply_changed(di->अक्षरgalg_psy);
		fallthrough;

	हाल STATE_TEMP_LOWHIGH:
		अगर (!di->events.btemp_lowhigh)
			abx500_अक्षरgalg_state_to(di, STATE_NORMAL_INIT);
		अवरोध;

	हाल STATE_WD_EXPIRED_INIT:
		abx500_अक्षरgalg_stop_अक्षरging(di);
		abx500_अक्षरgalg_state_to(di, STATE_WD_EXPIRED);
		fallthrough;

	हाल STATE_WD_EXPIRED:
		अगर (!di->events.ac_wd_expired &&
				!di->events.usb_wd_expired)
			abx500_अक्षरgalg_state_to(di, STATE_NORMAL_INIT);
		अवरोध;

	हाल STATE_TEMP_UNDEROVER_INIT:
		abx500_अक्षरgalg_stop_अक्षरging(di);
		abx500_अक्षरgalg_state_to(di, STATE_TEMP_UNDEROVER);
		fallthrough;

	हाल STATE_TEMP_UNDEROVER:
		अगर (!di->events.btemp_underover)
			abx500_अक्षरgalg_state_to(di, STATE_NORMAL_INIT);
		अवरोध;
	पूर्ण

	/* Start अक्षरging directly अगर the new state is a अक्षरge state */
	अगर (di->अक्षरge_state == STATE_NORMAL_INIT ||
			di->अक्षरge_state == STATE_MAINTEन_अंकCE_A_INIT ||
			di->अक्षरge_state == STATE_MAINTEन_अंकCE_B_INIT)
		queue_work(di->अक्षरgalg_wq, &di->अक्षरgalg_work);
पूर्ण

/**
 * abx500_अक्षरgalg_periodic_work() - Periodic work क्रम the algorithm
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Work queue function क्रम the अक्षरging algorithm
 */
अटल व्योम abx500_अक्षरgalg_periodic_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा abx500_अक्षरgalg *di = container_of(work,
		काष्ठा abx500_अक्षरgalg, अक्षरgalg_periodic_work.work);

	abx500_अक्षरgalg_algorithm(di);

	/*
	 * If a अक्षरger is connected then the battery has to be monitored
	 * frequently, अन्यथा the work can be delayed.
	 */
	अगर (di->chg_info.conn_chg)
		queue_delayed_work(di->अक्षरgalg_wq,
			&di->अक्षरgalg_periodic_work,
			di->bm->पूर्णांकerval_अक्षरging * HZ);
	अन्यथा
		queue_delayed_work(di->अक्षरgalg_wq,
			&di->अक्षरgalg_periodic_work,
			di->bm->पूर्णांकerval_not_अक्षरging * HZ);
पूर्ण

/**
 * abx500_अक्षरgalg_wd_work() - periodic work to kick the अक्षरger watchकरोg
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Work queue function क्रम kicking the अक्षरger watchकरोg
 */
अटल व्योम abx500_अक्षरgalg_wd_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा abx500_अक्षरgalg *di = container_of(work,
		काष्ठा abx500_अक्षरgalg, अक्षरgalg_wd_work.work);

	dev_dbg(di->dev, "abx500_chargalg_wd_work\n");

	ret = abx500_अक्षरgalg_kick_watchकरोg(di);
	अगर (ret < 0)
		dev_err(di->dev, "failed to kick watchdog\n");

	queue_delayed_work(di->अक्षरgalg_wq,
		&di->अक्षरgalg_wd_work, CHG_WD_INTERVAL);
पूर्ण

/**
 * abx500_अक्षरgalg_work() - Work to run the अक्षरging algorithm instantly
 * @work:	poपूर्णांकer to the work_काष्ठा काष्ठाure
 *
 * Work queue function क्रम calling the अक्षरging algorithm
 */
अटल व्योम abx500_अक्षरgalg_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा abx500_अक्षरgalg *di = container_of(work,
		काष्ठा abx500_अक्षरgalg, अक्षरgalg_work);

	abx500_अक्षरgalg_algorithm(di);
पूर्ण

/**
 * abx500_अक्षरgalg_get_property() - get the अक्षरgalg properties
 * @psy:	poपूर्णांकer to the घातer_supply काष्ठाure
 * @psp:	poपूर्णांकer to the घातer_supply_property काष्ठाure
 * @val:	poपूर्णांकer to the घातer_supply_propval जोड़
 *
 * This function माला_लो called when an application tries to get the
 * अक्षरgalg properties by पढ़ोing the sysfs files.
 * status:     अक्षरging/disअक्षरging/full/unknown
 * health:     health of the battery
 * Returns error code in हाल of failure अन्यथा 0 on success
 */
अटल पूर्णांक abx500_अक्षरgalg_get_property(काष्ठा घातer_supply *psy,
	क्रमागत घातer_supply_property psp,
	जोड़ घातer_supply_propval *val)
अणु
	काष्ठा abx500_अक्षरgalg *di = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = di->अक्षरge_status;
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		अगर (di->events.batt_ovv) अणु
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		पूर्ण अन्यथा अगर (di->events.btemp_underover) अणु
			अगर (di->batt_data.temp <= di->bm->temp_under)
				val->पूर्णांकval = POWER_SUPPLY_HEALTH_COLD;
			अन्यथा
				val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
		पूर्ण अन्यथा अगर (di->अक्षरge_state == STATE_SAFETY_TIMER_EXPIRED ||
			   di->अक्षरge_state == STATE_SAFETY_TIMER_EXPIRED_INIT) अणु
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		पूर्ण अन्यथा अणु
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Exposure to the sysfs पूर्णांकerface */

अटल sमाप_प्रकार abx500_अक्षरgalg_curr_step_show(काष्ठा abx500_अक्षरgalg *di,
					      अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", di->curr_status.curr_step);
पूर्ण

अटल sमाप_प्रकार abx500_अक्षरgalg_curr_step_store(काष्ठा abx500_अक्षरgalg *di,
					       स्थिर अक्षर *buf, माप_प्रकार length)
अणु
	दीर्घ पूर्णांक param;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &param);
	अगर (ret < 0)
		वापस ret;

	di->curr_status.curr_step = param;
	अगर (di->curr_status.curr_step >= CHARGALG_CURR_STEP_LOW &&
		di->curr_status.curr_step <= CHARGALG_CURR_STEP_HIGH) अणु
		di->curr_status.curr_step_change = true;
		queue_work(di->अक्षरgalg_wq, &di->अक्षरgalg_work);
	पूर्ण अन्यथा
		dev_info(di->dev, "Wrong current step\n"
			"Enter 0. Disable AC/USB Charging\n"
			"1--100. Set AC/USB charging current step\n"
			"100. Enable AC/USB Charging\n");

	वापस म_माप(buf);
पूर्ण


अटल sमाप_प्रकार abx500_अक्षरgalg_en_show(काष्ठा abx500_अक्षरgalg *di,
				       अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n",
		       di->susp_status.ac_suspended &&
		       di->susp_status.usb_suspended);
पूर्ण

अटल sमाप_प्रकार abx500_अक्षरgalg_en_store(काष्ठा abx500_अक्षरgalg *di,
	स्थिर अक्षर *buf, माप_प्रकार length)
अणु
	दीर्घ पूर्णांक param;
	पूर्णांक ac_usb;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &param);
	अगर (ret < 0)
		वापस ret;

	ac_usb = param;
	चयन (ac_usb) अणु
	हाल 0:
		/* Disable अक्षरging */
		di->susp_status.ac_suspended = true;
		di->susp_status.usb_suspended = true;
		di->susp_status.suspended_change = true;
		/* Trigger a state change */
		queue_work(di->अक्षरgalg_wq,
			&di->अक्षरgalg_work);
		अवरोध;
	हाल 1:
		/* Enable AC Charging */
		di->susp_status.ac_suspended = false;
		di->susp_status.suspended_change = true;
		/* Trigger a state change */
		queue_work(di->अक्षरgalg_wq,
			&di->अक्षरgalg_work);
		अवरोध;
	हाल 2:
		/* Enable USB अक्षरging */
		di->susp_status.usb_suspended = false;
		di->susp_status.suspended_change = true;
		/* Trigger a state change */
		queue_work(di->अक्षरgalg_wq,
			&di->अक्षरgalg_work);
		अवरोध;
	शेष:
		dev_info(di->dev, "Wrong input\n"
			"Enter 0. Disable AC/USB Charging\n"
			"1. Enable AC charging\n"
			"2. Enable USB Charging\n");
	पूर्ण
	वापस म_माप(buf);
पूर्ण

अटल काष्ठा abx500_अक्षरgalg_sysfs_entry abx500_अक्षरgalg_en_अक्षरger =
	__ATTR(अक्षरgalg, 0644, abx500_अक्षरgalg_en_show,
				abx500_अक्षरgalg_en_store);

अटल काष्ठा abx500_अक्षरgalg_sysfs_entry abx500_अक्षरgalg_curr_step =
	__ATTR(अक्षरgalg_curr_step, 0644, abx500_अक्षरgalg_curr_step_show,
					abx500_अक्षरgalg_curr_step_store);

अटल sमाप_प्रकार abx500_अक्षरgalg_sysfs_show(काष्ठा kobject *kobj,
	काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा abx500_अक्षरgalg_sysfs_entry *entry = container_of(attr,
		काष्ठा abx500_अक्षरgalg_sysfs_entry, attr);

	काष्ठा abx500_अक्षरgalg *di = container_of(kobj,
		काष्ठा abx500_अक्षरgalg, अक्षरgalg_kobject);

	अगर (!entry->show)
		वापस -EIO;

	वापस entry->show(di, buf);
पूर्ण

अटल sमाप_प्रकार abx500_अक्षरgalg_sysfs_अक्षरger(काष्ठा kobject *kobj,
	काष्ठा attribute *attr, स्थिर अक्षर *buf, माप_प्रकार length)
अणु
	काष्ठा abx500_अक्षरgalg_sysfs_entry *entry = container_of(attr,
		काष्ठा abx500_अक्षरgalg_sysfs_entry, attr);

	काष्ठा abx500_अक्षरgalg *di = container_of(kobj,
		काष्ठा abx500_अक्षरgalg, अक्षरgalg_kobject);

	अगर (!entry->store)
		वापस -EIO;

	वापस entry->store(di, buf, length);
पूर्ण

अटल काष्ठा attribute *abx500_अक्षरgalg_chg[] = अणु
	&abx500_अक्षरgalg_en_अक्षरger.attr,
	&abx500_अक्षरgalg_curr_step.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा sysfs_ops abx500_अक्षरgalg_sysfs_ops = अणु
	.show = abx500_अक्षरgalg_sysfs_show,
	.store = abx500_अक्षरgalg_sysfs_अक्षरger,
पूर्ण;

अटल काष्ठा kobj_type abx500_अक्षरgalg_ktype = अणु
	.sysfs_ops = &abx500_अक्षरgalg_sysfs_ops,
	.शेष_attrs = abx500_अक्षरgalg_chg,
पूर्ण;

/**
 * abx500_अक्षरgalg_sysfs_निकास() - de-init of sysfs entry
 * @di:                poपूर्णांकer to the काष्ठा abx500_अक्षरgalg
 *
 * This function हटाओs the entry in sysfs.
 */
अटल व्योम abx500_अक्षरgalg_sysfs_निकास(काष्ठा abx500_अक्षरgalg *di)
अणु
	kobject_del(&di->अक्षरgalg_kobject);
पूर्ण

/**
 * abx500_अक्षरgalg_sysfs_init() - init of sysfs entry
 * @di:                poपूर्णांकer to the काष्ठा abx500_अक्षरgalg
 *
 * This function adds an entry in sysfs.
 * Returns error code in हाल of failure अन्यथा 0(on success)
 */
अटल पूर्णांक abx500_अक्षरgalg_sysfs_init(काष्ठा abx500_अक्षरgalg *di)
अणु
	पूर्णांक ret = 0;

	ret = kobject_init_and_add(&di->अक्षरgalg_kobject,
		&abx500_अक्षरgalg_ktype,
		शून्य, "abx500_chargalg");
	अगर (ret < 0)
		dev_err(di->dev, "failed to create sysfs entry\n");

	वापस ret;
पूर्ण
/* Exposure to the sysfs पूर्णांकerface <<END>> */

अटल पूर्णांक __maybe_unused abx500_अक्षरgalg_resume(काष्ठा device *dev)
अणु
	काष्ठा abx500_अक्षरgalg *di = dev_get_drvdata(dev);

	/* Kick अक्षरger watchकरोg अगर अक्षरging (any अक्षरger online) */
	अगर (di->chg_info.online_chg)
		queue_delayed_work(di->अक्षरgalg_wq, &di->अक्षरgalg_wd_work, 0);

	/*
	 * Run the अक्षरging algorithm directly to be sure we करोn't
	 * करो it too selकरोm
	 */
	queue_delayed_work(di->अक्षरgalg_wq, &di->अक्षरgalg_periodic_work, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused abx500_अक्षरgalg_suspend(काष्ठा device *dev)
अणु
	काष्ठा abx500_अक्षरgalg *di = dev_get_drvdata(dev);

	अगर (di->chg_info.online_chg)
		cancel_delayed_work_sync(&di->अक्षरgalg_wd_work);

	cancel_delayed_work_sync(&di->अक्षरgalg_periodic_work);

	वापस 0;
पूर्ण

अटल पूर्णांक abx500_अक्षरgalg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा abx500_अक्षरgalg *di = platक्रमm_get_drvdata(pdev);

	/* sysfs पूर्णांकerface to enable/disbale अक्षरging from user space */
	abx500_अक्षरgalg_sysfs_निकास(di);

	hrसमयr_cancel(&di->safety_समयr);
	hrसमयr_cancel(&di->मुख्यtenance_समयr);

	cancel_delayed_work_sync(&di->अक्षरgalg_periodic_work);
	cancel_delayed_work_sync(&di->अक्षरgalg_wd_work);
	cancel_work_sync(&di->अक्षरgalg_work);

	/* Delete the work queue */
	destroy_workqueue(di->अक्षरgalg_wq);

	घातer_supply_unरेजिस्टर(di->अक्षरgalg_psy);

	वापस 0;
पूर्ण

अटल अक्षर *supply_पूर्णांकerface[] = अणु
	"ab8500_fg",
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc abx500_अक्षरgalg_desc = अणु
	.name			= "abx500_chargalg",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.properties		= abx500_अक्षरgalg_props,
	.num_properties		= ARRAY_SIZE(abx500_अक्षरgalg_props),
	.get_property		= abx500_अक्षरgalg_get_property,
	.बाह्यal_घातer_changed	= abx500_अक्षरgalg_बाह्यal_घातer_changed,
पूर्ण;

अटल पूर्णांक abx500_अक्षरgalg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा abx500_अक्षरgalg *di;
	पूर्णांक ret = 0;

	di = devm_kzalloc(&pdev->dev, माप(*di), GFP_KERNEL);
	अगर (!di) अणु
		dev_err(&pdev->dev, "%s no mem for ab8500_chargalg\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	di->bm = &ab8500_bm_data;

	ret = ab8500_bm_of_probe(&pdev->dev, np, di->bm);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to get battery information\n");
		वापस ret;
	पूर्ण

	/* get device काष्ठा and parent */
	di->dev = &pdev->dev;
	di->parent = dev_get_drvdata(pdev->dev.parent);

	psy_cfg.supplied_to = supply_पूर्णांकerface;
	psy_cfg.num_supplicants = ARRAY_SIZE(supply_पूर्णांकerface);
	psy_cfg.drv_data = di;

	/* Initilialize safety समयr */
	hrसमयr_init(&di->safety_समयr, CLOCK_REALTIME, HRTIMER_MODE_ABS);
	di->safety_समयr.function = abx500_अक्षरgalg_safety_समयr_expired;

	/* Initilialize मुख्यtenance समयr */
	hrसमयr_init(&di->मुख्यtenance_समयr, CLOCK_REALTIME, HRTIMER_MODE_ABS);
	di->मुख्यtenance_समयr.function =
		abx500_अक्षरgalg_मुख्यtenance_समयr_expired;

	/* Create a work queue क्रम the अक्षरgalg */
	di->अक्षरgalg_wq = alloc_ordered_workqueue("abx500_chargalg_wq",
						   WQ_MEM_RECLAIM);
	अगर (di->अक्षरgalg_wq == शून्य) अणु
		dev_err(di->dev, "failed to create work queue\n");
		वापस -ENOMEM;
	पूर्ण

	/* Init work क्रम अक्षरgalg */
	INIT_DEFERRABLE_WORK(&di->अक्षरgalg_periodic_work,
		abx500_अक्षरgalg_periodic_work);
	INIT_DEFERRABLE_WORK(&di->अक्षरgalg_wd_work,
		abx500_अक्षरgalg_wd_work);

	/* Init work क्रम अक्षरgalg */
	INIT_WORK(&di->अक्षरgalg_work, abx500_अक्षरgalg_work);

	/* To detect अक्षरger at startup */
	di->chg_info.prev_conn_chg = -1;

	/* Register अक्षरgalg घातer supply class */
	di->अक्षरgalg_psy = घातer_supply_रेजिस्टर(di->dev, &abx500_अक्षरgalg_desc,
						 &psy_cfg);
	अगर (IS_ERR(di->अक्षरgalg_psy)) अणु
		dev_err(di->dev, "failed to register chargalg psy\n");
		ret = PTR_ERR(di->अक्षरgalg_psy);
		जाओ मुक्त_अक्षरgalg_wq;
	पूर्ण

	platक्रमm_set_drvdata(pdev, di);

	/* sysfs पूर्णांकerface to enable/disable अक्षरging from user space */
	ret = abx500_अक्षरgalg_sysfs_init(di);
	अगर (ret) अणु
		dev_err(di->dev, "failed to create sysfs entry\n");
		जाओ मुक्त_psy;
	पूर्ण
	di->curr_status.curr_step = CHARGALG_CURR_STEP_HIGH;

	/* Run the अक्षरging algorithm */
	queue_delayed_work(di->अक्षरgalg_wq, &di->अक्षरgalg_periodic_work, 0);

	dev_info(di->dev, "probe success\n");
	वापस ret;

मुक्त_psy:
	घातer_supply_unरेजिस्टर(di->अक्षरgalg_psy);
मुक्त_अक्षरgalg_wq:
	destroy_workqueue(di->अक्षरgalg_wq);
	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(abx500_अक्षरgalg_pm_ops, abx500_अक्षरgalg_suspend, abx500_अक्षरgalg_resume);

अटल स्थिर काष्ठा of_device_id ab8500_अक्षरgalg_match[] = अणु
	अणु .compatible = "stericsson,ab8500-chargalg", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver abx500_अक्षरgalg_driver = अणु
	.probe = abx500_अक्षरgalg_probe,
	.हटाओ = abx500_अक्षरgalg_हटाओ,
	.driver = अणु
		.name = "ab8500-chargalg",
		.of_match_table = ab8500_अक्षरgalg_match,
		.pm = &abx500_अक्षरgalg_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(abx500_अक्षरgalg_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Johan Palsson, Karl Komierowski");
MODULE_ALIAS("platform:abx500-chargalg");
MODULE_DESCRIPTION("abx500 battery charging algorithm");
