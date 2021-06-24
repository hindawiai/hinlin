<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2012
 * Author: Johan Gardsmark <johan.gardsmark@stericsson.com> क्रम ST-Ericsson.
 */

#अगर_अघोषित _AB8500_CHARGALG_H_
#घोषणा _AB8500_CHARGALG_H_

#समावेश <linux/घातer_supply.h>

/*
 * Valid only क्रम supplies of type:
 * - POWER_SUPPLY_TYPE_MAINS,
 * - POWER_SUPPLY_TYPE_USB,
 * because only them store as drv_data poपूर्णांकer to काष्ठा ux500_अक्षरger.
 */
#घोषणा psy_to_ux500_अक्षरger(x) घातer_supply_get_drvdata(psy)

/* Forward declaration */
काष्ठा ux500_अक्षरger;

काष्ठा ux500_अक्षरger_ops अणु
	पूर्णांक (*enable) (काष्ठा ux500_अक्षरger *, पूर्णांक, पूर्णांक, पूर्णांक);
	पूर्णांक (*check_enable) (काष्ठा ux500_अक्षरger *, पूर्णांक, पूर्णांक);
	पूर्णांक (*kick_wd) (काष्ठा ux500_अक्षरger *);
	पूर्णांक (*update_curr) (काष्ठा ux500_अक्षरger *, पूर्णांक);
पूर्ण;

/**
 * काष्ठा ux500_अक्षरger - घातer supply ux500 अक्षरger sub class
 * @psy			घातer supply base class
 * @ops			ux500 अक्षरger operations
 * @max_out_volt	maximum output अक्षरger voltage in mV
 * @max_out_curr	maximum output अक्षरger current in mA
 * @enabled		indicates अगर this अक्षरger is used or not
 * @बाह्यal		बाह्यal अक्षरger unit (pm2xxx)
 */
काष्ठा ux500_अक्षरger अणु
	काष्ठा घातer_supply *psy;
	काष्ठा ux500_अक्षरger_ops ops;
	पूर्णांक max_out_volt;
	पूर्णांक max_out_curr;
	पूर्णांक wdt_refresh;
	bool enabled;
	bool बाह्यal;
पूर्ण;

बाह्य काष्ठा blocking_notअगरier_head अक्षरger_notअगरier_list;

#पूर्ण_अगर /* _AB8500_CHARGALG_H_ */
