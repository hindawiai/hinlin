<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2017 Chelsio Communications.  All rights reserved.
 *
 *  Written by: Ganesh Goudar (ganeshgr@chelsio.com)
 */

#समावेश "cxgb4.h"

#घोषणा CXGB4_NUM_TRIPS 1

अटल पूर्णांक cxgb4_thermal_get_temp(काष्ठा thermal_zone_device *tzdev,
				  पूर्णांक *temp)
अणु
	काष्ठा adapter *adap = tzdev->devdata;
	u32 param, val;
	पूर्णांक ret;

	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_DIAG) |
		 FW_PARAMS_PARAM_Y_V(FW_PARAM_DEV_DIAG_TMP));

	ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 1,
			      &param, &val);
	अगर (ret < 0 || val == 0)
		वापस -1;

	*temp = val * 1000;
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_thermal_get_trip_type(काष्ठा thermal_zone_device *tzdev,
				       पूर्णांक trip, क्रमागत thermal_trip_type *type)
अणु
	काष्ठा adapter *adap = tzdev->devdata;

	अगर (!adap->ch_thermal.trip_temp)
		वापस -EINVAL;

	*type = adap->ch_thermal.trip_type;
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_thermal_get_trip_temp(काष्ठा thermal_zone_device *tzdev,
				       पूर्णांक trip, पूर्णांक *temp)
अणु
	काष्ठा adapter *adap = tzdev->devdata;

	अगर (!adap->ch_thermal.trip_temp)
		वापस -EINVAL;

	*temp = adap->ch_thermal.trip_temp;
	वापस 0;
पूर्ण

अटल काष्ठा thermal_zone_device_ops cxgb4_thermal_ops = अणु
	.get_temp = cxgb4_thermal_get_temp,
	.get_trip_type = cxgb4_thermal_get_trip_type,
	.get_trip_temp = cxgb4_thermal_get_trip_temp,
पूर्ण;

पूर्णांक cxgb4_thermal_init(काष्ठा adapter *adap)
अणु
	काष्ठा ch_thermal *ch_thermal = &adap->ch_thermal;
	अक्षर ch_tz_name[THERMAL_NAME_LENGTH];
	पूर्णांक num_trip = CXGB4_NUM_TRIPS;
	u32 param, val;
	पूर्णांक ret;

	/* on older firmwares we may not get the trip temperature,
	 * set the num of trips to 0.
	 */
	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_DIAG) |
		 FW_PARAMS_PARAM_Y_V(FW_PARAM_DEV_DIAG_MAXTMPTHRESH));

	ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 1,
			      &param, &val);
	अगर (ret < 0) अणु
		num_trip = 0; /* could not get trip temperature */
	पूर्ण अन्यथा अणु
		ch_thermal->trip_temp = val * 1000;
		ch_thermal->trip_type = THERMAL_TRIP_CRITICAL;
	पूर्ण

	snम_लिखो(ch_tz_name, माप(ch_tz_name), "cxgb4_%s", adap->name);
	ch_thermal->tzdev = thermal_zone_device_रेजिस्टर(ch_tz_name, num_trip,
							 0, adap,
							 &cxgb4_thermal_ops,
							 शून्य, 0, 0);
	अगर (IS_ERR(ch_thermal->tzdev)) अणु
		ret = PTR_ERR(ch_thermal->tzdev);
		dev_err(adap->pdev_dev, "Failed to register thermal zone\n");
		ch_thermal->tzdev = शून्य;
		वापस ret;
	पूर्ण

	ret = thermal_zone_device_enable(ch_thermal->tzdev);
	अगर (ret) अणु
		dev_err(adap->pdev_dev, "Failed to enable thermal zone\n");
		thermal_zone_device_unरेजिस्टर(adap->ch_thermal.tzdev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cxgb4_thermal_हटाओ(काष्ठा adapter *adap)
अणु
	अगर (adap->ch_thermal.tzdev) अणु
		thermal_zone_device_unरेजिस्टर(adap->ch_thermal.tzdev);
		adap->ch_thermal.tzdev = शून्य;
	पूर्ण
	वापस 0;
पूर्ण
