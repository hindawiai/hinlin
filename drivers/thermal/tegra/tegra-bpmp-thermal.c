<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015-2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author:
 *	Mikko Perttunen <mperttunen@nvidia.com>
 *	Aapo Vienamo	<avienamo@nvidia.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/thermal.h>
#समावेश <linux/workqueue.h>

#समावेश <soc/tegra/bpmp.h>
#समावेश <soc/tegra/bpmp-abi.h>

काष्ठा tegra_bpmp_thermal_zone अणु
	काष्ठा tegra_bpmp_thermal *tegra;
	काष्ठा thermal_zone_device *tzd;
	काष्ठा work_काष्ठा tz_device_update_work;
	अचिन्हित पूर्णांक idx;
पूर्ण;

काष्ठा tegra_bpmp_thermal अणु
	काष्ठा device *dev;
	काष्ठा tegra_bpmp *bpmp;
	अचिन्हित पूर्णांक num_zones;
	काष्ठा tegra_bpmp_thermal_zone **zones;
पूर्ण;

अटल पूर्णांक tegra_bpmp_thermal_get_temp(व्योम *data, पूर्णांक *out_temp)
अणु
	काष्ठा tegra_bpmp_thermal_zone *zone = data;
	काष्ठा mrq_thermal_host_to_bpmp_request req;
	जोड़ mrq_thermal_bpmp_to_host_response reply;
	काष्ठा tegra_bpmp_message msg;
	पूर्णांक err;

	स_रखो(&req, 0, माप(req));
	req.type = CMD_THERMAL_GET_TEMP;
	req.get_temp.zone = zone->idx;

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_THERMAL;
	msg.tx.data = &req;
	msg.tx.size = माप(req);
	msg.rx.data = &reply;
	msg.rx.size = माप(reply);

	err = tegra_bpmp_transfer(zone->tegra->bpmp, &msg);
	अगर (err)
		वापस err;

	*out_temp = reply.get_temp.temp;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_bpmp_thermal_set_trips(व्योम *data, पूर्णांक low, पूर्णांक high)
अणु
	काष्ठा tegra_bpmp_thermal_zone *zone = data;
	काष्ठा mrq_thermal_host_to_bpmp_request req;
	काष्ठा tegra_bpmp_message msg;

	स_रखो(&req, 0, माप(req));
	req.type = CMD_THERMAL_SET_TRIP;
	req.set_trip.zone = zone->idx;
	req.set_trip.enabled = true;
	req.set_trip.low = low;
	req.set_trip.high = high;

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_THERMAL;
	msg.tx.data = &req;
	msg.tx.size = माप(req);

	वापस tegra_bpmp_transfer(zone->tegra->bpmp, &msg);
पूर्ण

अटल व्योम tz_device_update_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tegra_bpmp_thermal_zone *zone;

	zone = container_of(work, काष्ठा tegra_bpmp_thermal_zone,
			    tz_device_update_work);

	thermal_zone_device_update(zone->tzd, THERMAL_TRIP_VIOLATED);
पूर्ण

अटल व्योम bpmp_mrq_thermal(अचिन्हित पूर्णांक mrq, काष्ठा tegra_bpmp_channel *ch,
			     व्योम *data)
अणु
	काष्ठा mrq_thermal_bpmp_to_host_request *req;
	काष्ठा tegra_bpmp_thermal *tegra = data;
	पूर्णांक i;

	req = (काष्ठा mrq_thermal_bpmp_to_host_request *)ch->ib->data;

	अगर (req->type != CMD_THERMAL_HOST_TRIP_REACHED) अणु
		dev_err(tegra->dev, "%s: invalid request type: %d\n",
			__func__, req->type);
		tegra_bpmp_mrq_वापस(ch, -EINVAL, शून्य, 0);
		वापस;
	पूर्ण

	क्रम (i = 0; i < tegra->num_zones; ++i) अणु
		अगर (tegra->zones[i]->idx != req->host_trip_reached.zone)
			जारी;

		schedule_work(&tegra->zones[i]->tz_device_update_work);
		tegra_bpmp_mrq_वापस(ch, 0, शून्य, 0);
		वापस;
	पूर्ण

	dev_err(tegra->dev, "%s: invalid thermal zone: %d\n", __func__,
		req->host_trip_reached.zone);
	tegra_bpmp_mrq_वापस(ch, -EINVAL, शून्य, 0);
पूर्ण

अटल पूर्णांक tegra_bpmp_thermal_get_num_zones(काष्ठा tegra_bpmp *bpmp,
					    पूर्णांक *num_zones)
अणु
	काष्ठा mrq_thermal_host_to_bpmp_request req;
	जोड़ mrq_thermal_bpmp_to_host_response reply;
	काष्ठा tegra_bpmp_message msg;
	पूर्णांक err;

	स_रखो(&req, 0, माप(req));
	req.type = CMD_THERMAL_GET_NUM_ZONES;

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_THERMAL;
	msg.tx.data = &req;
	msg.tx.size = माप(req);
	msg.rx.data = &reply;
	msg.rx.size = माप(reply);

	err = tegra_bpmp_transfer(bpmp, &msg);
	अगर (err)
		वापस err;

	*num_zones = reply.get_num_zones.num;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops tegra_bpmp_of_thermal_ops = अणु
	.get_temp = tegra_bpmp_thermal_get_temp,
	.set_trips = tegra_bpmp_thermal_set_trips,
पूर्ण;

अटल पूर्णांक tegra_bpmp_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_bpmp *bpmp = dev_get_drvdata(pdev->dev.parent);
	काष्ठा tegra_bpmp_thermal *tegra;
	काष्ठा thermal_zone_device *tzd;
	अचिन्हित पूर्णांक i, max_num_zones;
	पूर्णांक err;

	tegra = devm_kzalloc(&pdev->dev, माप(*tegra), GFP_KERNEL);
	अगर (!tegra)
		वापस -ENOMEM;

	tegra->dev = &pdev->dev;
	tegra->bpmp = bpmp;

	err = tegra_bpmp_thermal_get_num_zones(bpmp, &max_num_zones);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to get the number of zones: %d\n",
			err);
		वापस err;
	पूर्ण

	tegra->zones = devm_kसुस्मृति(&pdev->dev, max_num_zones,
				    माप(*tegra->zones), GFP_KERNEL);
	अगर (!tegra->zones)
		वापस -ENOMEM;

	क्रम (i = 0; i < max_num_zones; ++i) अणु
		काष्ठा tegra_bpmp_thermal_zone *zone;
		पूर्णांक temp;

		zone = devm_kzalloc(&pdev->dev, माप(*zone), GFP_KERNEL);
		अगर (!zone)
			वापस -ENOMEM;

		zone->idx = i;
		zone->tegra = tegra;

		err = tegra_bpmp_thermal_get_temp(zone, &temp);
		अगर (err < 0) अणु
			devm_kमुक्त(&pdev->dev, zone);
			जारी;
		पूर्ण

		tzd = devm_thermal_zone_of_sensor_रेजिस्टर(
			&pdev->dev, i, zone, &tegra_bpmp_of_thermal_ops);
		अगर (IS_ERR(tzd)) अणु
			अगर (PTR_ERR(tzd) == -EPROBE_DEFER)
				वापस -EPROBE_DEFER;
			devm_kमुक्त(&pdev->dev, zone);
			जारी;
		पूर्ण

		zone->tzd = tzd;
		INIT_WORK(&zone->tz_device_update_work,
			  tz_device_update_work_fn);

		tegra->zones[tegra->num_zones++] = zone;
	पूर्ण

	err = tegra_bpmp_request_mrq(bpmp, MRQ_THERMAL, bpmp_mrq_thermal,
				     tegra);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register mrq handler: %d\n",
			err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, tegra);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_bpmp_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_bpmp_thermal *tegra = platक्रमm_get_drvdata(pdev);

	tegra_bpmp_मुक्त_mrq(tegra->bpmp, MRQ_THERMAL, tegra);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_bpmp_thermal_of_match[] = अणु
	अणु .compatible = "nvidia,tegra186-bpmp-thermal" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_bpmp_thermal_of_match);

अटल काष्ठा platक्रमm_driver tegra_bpmp_thermal_driver = अणु
	.probe = tegra_bpmp_thermal_probe,
	.हटाओ = tegra_bpmp_thermal_हटाओ,
	.driver = अणु
		.name = "tegra-bpmp-thermal",
		.of_match_table = tegra_bpmp_thermal_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_bpmp_thermal_driver);

MODULE_AUTHOR("Mikko Perttunen <mperttunen@nvidia.com>");
MODULE_DESCRIPTION("NVIDIA Tegra BPMP thermal sensor driver");
MODULE_LICENSE("GPL v2");
