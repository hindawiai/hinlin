<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// rt711-sdw-sdca.c -- rt711 SDCA ALSA SoC audio driver
//
// Copyright(c) 2021 Realtek Semiconductor Corp.
//
//

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश <linux/module.h>

#समावेश "rt711-sdca.h"
#समावेश "rt711-sdca-sdw.h"

अटल bool rt711_sdca_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x201a ... 0x2027:
	हाल 0x2029 ... 0x202a:
	हाल 0x202d ... 0x2034:
	हाल 0x2200 ... 0x2204:
	हाल 0x2206 ... 0x2212:
	हाल 0x2220 ... 0x2223:
	हाल 0x2230 ... 0x2239:
	हाल 0x2f01 ... 0x2f0f:
	हाल 0x2f30 ... 0x2f36:
	हाल 0x2f50 ... 0x2f5a:
	हाल 0x2f60:
	हाल 0x3200 ... 0x3212:
	हाल SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_GE49, RT711_SDCA_CTL_SELECTED_MODE, 0):
	हाल SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_GE49, RT711_SDCA_CTL_DETECTED_MODE, 0):
	हाल SDW_SDCA_CTL(FUNC_NUM_HID, RT711_SDCA_ENT_HID01, RT711_SDCA_CTL_HIDTX_CURRENT_OWNER, 0) ...
		SDW_SDCA_CTL(FUNC_NUM_HID, RT711_SDCA_ENT_HID01, RT711_SDCA_CTL_HIDTX_MESSAGE_LENGTH, 0):
	हाल RT711_BUF_ADDR_HID1 ... RT711_BUF_ADDR_HID2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt711_sdca_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x201b:
	हाल 0x201c:
	हाल 0x201d:
	हाल 0x201f:
	हाल 0x2021:
	हाल 0x2023:
	हाल 0x2230:
	हाल 0x202d ... 0x202f: /* BRA */
	हाल 0x2200 ... 0x2212: /* i2c debug */
	हाल RT711_RC_CAL_STATUS:
	हाल SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_GE49, RT711_SDCA_CTL_DETECTED_MODE, 0):
	हाल SDW_SDCA_CTL(FUNC_NUM_HID, RT711_SDCA_ENT_HID01, RT711_SDCA_CTL_HIDTX_CURRENT_OWNER, 0) ...
		SDW_SDCA_CTL(FUNC_NUM_HID, RT711_SDCA_ENT_HID01, RT711_SDCA_CTL_HIDTX_MESSAGE_LENGTH, 0):
	हाल RT711_BUF_ADDR_HID1 ... RT711_BUF_ADDR_HID2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt711_sdca_mbq_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x2000000 ... 0x20000ff:
	हाल 0x5600000 ... 0x56000ff:
	हाल 0x5700000 ... 0x57000ff:
	हाल 0x5800000 ... 0x58000ff:
	हाल 0x5900000 ... 0x59000ff:
	हाल 0x5b00000 ... 0x5b000ff:
	हाल 0x5f00000 ... 0x5f000ff:
	हाल 0x6100000 ... 0x61000ff:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt711_sdca_mbq_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x2000000:
	हाल 0x200001a:
	हाल 0x2000046:
	हाल 0x2000080:
	हाल 0x2000081:
	हाल 0x2000083:
	हाल 0x5800000:
	हाल 0x5800001:
	हाल 0x5f00001:
	हाल 0x6100008:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config rt711_sdca_regmap = अणु
	.reg_bits = 32,
	.val_bits = 8,
	.पढ़ोable_reg = rt711_sdca_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = rt711_sdca_अस्थिर_रेजिस्टर,
	.max_रेजिस्टर = 0x44ffffff,
	.reg_शेषs = rt711_sdca_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(rt711_sdca_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt711_sdca_mbq_regmap = अणु
	.name = "sdw-mbq",
	.reg_bits = 32,
	.val_bits = 16,
	.पढ़ोable_reg = rt711_sdca_mbq_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = rt711_sdca_mbq_अस्थिर_रेजिस्टर,
	.max_रेजिस्टर = 0x40800f12,
	.reg_शेषs = rt711_sdca_mbq_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(rt711_sdca_mbq_शेषs),
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल पूर्णांक rt711_sdca_update_status(काष्ठा sdw_slave *slave,
				क्रमागत sdw_slave_status status)
अणु
	काष्ठा rt711_sdca_priv *rt711 = dev_get_drvdata(&slave->dev);

	/* Update the status */
	rt711->status = status;

	अगर (status == SDW_SLAVE_UNATTACHED)
		rt711->hw_init = false;

	अगर (status == SDW_SLAVE_ATTACHED) अणु
		अगर (rt711->hs_jack) अणु
			/*
			 * Due to the SCP_SDCA_INTMASK will be cleared by any reset, and then
			 * अगर the device attached again, we will need to set the setting back.
			 * It could aव्योम losing the jack detection पूर्णांकerrupt.
			 * This also could sync with the cache value as the rt711_sdca_jack_init set.
			 */
			sdw_ग_लिखो_no_pm(rt711->slave, SDW_SCP_SDCA_INTMASK1,
				SDW_SCP_SDCA_INTMASK_SDCA_0);
			sdw_ग_लिखो_no_pm(rt711->slave, SDW_SCP_SDCA_INTMASK2,
				SDW_SCP_SDCA_INTMASK_SDCA_8);
		पूर्ण
	पूर्ण

	/*
	 * Perक्रमm initialization only अगर slave status is present and
	 * hw_init flag is false
	 */
	अगर (rt711->hw_init || rt711->status != SDW_SLAVE_ATTACHED)
		वापस 0;

	/* perक्रमm I/O transfers required क्रम Slave initialization */
	वापस rt711_sdca_io_init(&slave->dev, slave);
पूर्ण

अटल पूर्णांक rt711_sdca_पढ़ो_prop(काष्ठा sdw_slave *slave)
अणु
	काष्ठा sdw_slave_prop *prop = &slave->prop;
	पूर्णांक nval;
	पूर्णांक i, j;
	u32 bit;
	अचिन्हित दीर्घ addr;
	काष्ठा sdw_dpn_prop *dpn;

	prop->scp_पूर्णांक1_mask = SDW_SCP_INT1_BUS_CLASH | SDW_SCP_INT1_PARITY;
	prop->quirks = SDW_SLAVE_QUIRKS_INVALID_INITIAL_PARITY;
	prop->is_sdca = true;

	prop->paging_support = true;

	/* first we need to allocate memory क्रम set bits in port lists */
	prop->source_ports = 0x14; /* BITMAP: 00010100 */
	prop->sink_ports = 0x8; /* BITMAP:  00001000 */

	nval = hweight32(prop->source_ports);
	prop->src_dpn_prop = devm_kसुस्मृति(&slave->dev, nval,
		माप(*prop->src_dpn_prop), GFP_KERNEL);
	अगर (!prop->src_dpn_prop)
		वापस -ENOMEM;

	i = 0;
	dpn = prop->src_dpn_prop;
	addr = prop->source_ports;
	क्रम_each_set_bit(bit, &addr, 32) अणु
		dpn[i].num = bit;
		dpn[i].type = SDW_DPN_FULL;
		dpn[i].simple_ch_prep_sm = true;
		dpn[i].ch_prep_समयout = 10;
		i++;
	पूर्ण

	/* करो this again क्रम sink now */
	nval = hweight32(prop->sink_ports);
	prop->sink_dpn_prop = devm_kसुस्मृति(&slave->dev, nval,
		माप(*prop->sink_dpn_prop), GFP_KERNEL);
	अगर (!prop->sink_dpn_prop)
		वापस -ENOMEM;

	j = 0;
	dpn = prop->sink_dpn_prop;
	addr = prop->sink_ports;
	क्रम_each_set_bit(bit, &addr, 32) अणु
		dpn[j].num = bit;
		dpn[j].type = SDW_DPN_FULL;
		dpn[j].simple_ch_prep_sm = true;
		dpn[j].ch_prep_समयout = 10;
		j++;
	पूर्ण

	/* set the समयout values */
	prop->clk_stop_समयout = 20;

	/* wake-up event */
	prop->wake_capable = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_पूर्णांकerrupt_callback(काष्ठा sdw_slave *slave,
					काष्ठा sdw_slave_पूर्णांकr_status *status)
अणु
	काष्ठा rt711_sdca_priv *rt711 = dev_get_drvdata(&slave->dev);
	पूर्णांक ret, stat;
	पूर्णांक count = 0, retry = 3;
	अचिन्हित पूर्णांक sdca_cascade, scp_sdca_stat1, scp_sdca_stat2 = 0;

	dev_dbg(&slave->dev,
		"%s control_port_stat=%x, sdca_cascade=%x", __func__,
		status->control_port, status->sdca_cascade);

	अगर (cancel_delayed_work_sync(&rt711->jack_detect_work)) अणु
		dev_warn(&slave->dev, "%s the pending delayed_work was cancelled", __func__);
		/* aव्योम the HID owner करोesn't change to device */
		अगर (rt711->scp_sdca_stat2)
			scp_sdca_stat2 = rt711->scp_sdca_stat2;
	पूर्ण

	ret = sdw_पढ़ो_no_pm(rt711->slave, SDW_SCP_SDCA_INT1);
	अगर (ret < 0)
		जाओ io_error;
	rt711->scp_sdca_stat1 = ret;
	ret = sdw_पढ़ो_no_pm(rt711->slave, SDW_SCP_SDCA_INT2);
	अगर (ret < 0)
		जाओ io_error;
	rt711->scp_sdca_stat2 = ret;
	अगर (scp_sdca_stat2)
		rt711->scp_sdca_stat2 |= scp_sdca_stat2;

	करो अणु
		/* clear flag */
		ret = sdw_पढ़ो_no_pm(rt711->slave, SDW_SCP_SDCA_INT1);
		अगर (ret < 0)
			जाओ io_error;
		अगर (ret & SDW_SCP_SDCA_INTMASK_SDCA_0) अणु
			ret = sdw_ग_लिखो_no_pm(rt711->slave, SDW_SCP_SDCA_INT1,
						SDW_SCP_SDCA_INTMASK_SDCA_0);
			अगर (ret < 0)
				जाओ io_error;
		पूर्ण
		ret = sdw_पढ़ो_no_pm(rt711->slave, SDW_SCP_SDCA_INT2);
		अगर (ret < 0)
			जाओ io_error;
		अगर (ret & SDW_SCP_SDCA_INTMASK_SDCA_8) अणु
			ret = sdw_ग_लिखो_no_pm(rt711->slave, SDW_SCP_SDCA_INT2,
						SDW_SCP_SDCA_INTMASK_SDCA_8);
			अगर (ret < 0)
				जाओ io_error;
		पूर्ण

		/* check अगर flag clear or not */
		ret = sdw_पढ़ो_no_pm(rt711->slave, SDW_DP0_INT);
		अगर (ret < 0)
			जाओ io_error;
		sdca_cascade = ret & SDW_DP0_SDCA_CASCADE;

		ret = sdw_पढ़ो_no_pm(rt711->slave, SDW_SCP_SDCA_INT1);
		अगर (ret < 0)
			जाओ io_error;
		scp_sdca_stat1 = ret & SDW_SCP_SDCA_INTMASK_SDCA_0;

		ret = sdw_पढ़ो_no_pm(rt711->slave, SDW_SCP_SDCA_INT2);
		अगर (ret < 0)
			जाओ io_error;
		scp_sdca_stat2 = ret & SDW_SCP_SDCA_INTMASK_SDCA_8;

		stat = scp_sdca_stat1 || scp_sdca_stat2 || sdca_cascade;

		count++;
	पूर्ण जबतक (stat != 0 && count < retry);

	अगर (stat)
		dev_warn(&slave->dev,
			"%s scp_sdca_stat1=0x%x, scp_sdca_stat2=0x%x\n", __func__,
			rt711->scp_sdca_stat1, rt711->scp_sdca_stat2);

	अगर (status->sdca_cascade)
		mod_delayed_work(प्रणाली_घातer_efficient_wq,
			&rt711->jack_detect_work, msecs_to_jअगरfies(30));

	वापस 0;

io_error:
	pr_err_ratelimited("IO error in %s, ret %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल काष्ठा sdw_slave_ops rt711_sdca_slave_ops = अणु
	.पढ़ो_prop = rt711_sdca_पढ़ो_prop,
	.पूर्णांकerrupt_callback = rt711_sdca_पूर्णांकerrupt_callback,
	.update_status = rt711_sdca_update_status,
पूर्ण;

अटल पूर्णांक rt711_sdca_sdw_probe(काष्ठा sdw_slave *slave,
				स्थिर काष्ठा sdw_device_id *id)
अणु
	काष्ठा regmap *regmap, *mbq_regmap;

	/* Regmap Initialization */
	mbq_regmap = devm_regmap_init_sdw_mbq(slave, &rt711_sdca_mbq_regmap);
	अगर (IS_ERR(mbq_regmap))
		वापस PTR_ERR(mbq_regmap);

	regmap = devm_regmap_init_sdw(slave, &rt711_sdca_regmap);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस rt711_sdca_init(&slave->dev, regmap, mbq_regmap, slave);
पूर्ण

अटल पूर्णांक rt711_sdca_sdw_हटाओ(काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt711_sdca_priv *rt711 = dev_get_drvdata(&slave->dev);

	अगर (rt711 && rt711->hw_init) अणु
		cancel_delayed_work_sync(&rt711->jack_detect_work);
		cancel_delayed_work_sync(&rt711->jack_btn_check_work);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdw_device_id rt711_sdca_id[] = अणु
	SDW_SLAVE_ENTRY_EXT(0x025d, 0x711, 0x3, 0x1, 0),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(sdw, rt711_sdca_id);

अटल पूर्णांक __maybe_unused rt711_sdca_dev_suspend(काष्ठा device *dev)
अणु
	काष्ठा rt711_sdca_priv *rt711 = dev_get_drvdata(dev);

	अगर (!rt711->hw_init)
		वापस 0;

	cancel_delayed_work_sync(&rt711->jack_detect_work);
	cancel_delayed_work_sync(&rt711->jack_btn_check_work);

	regcache_cache_only(rt711->regmap, true);
	regcache_cache_only(rt711->mbq_regmap, true);

	वापस 0;
पूर्ण

#घोषणा RT711_PROBE_TIMEOUT 5000

अटल पूर्णांक __maybe_unused rt711_sdca_dev_resume(काष्ठा device *dev)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	काष्ठा rt711_sdca_priv *rt711 = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समय;

	अगर (!rt711->hw_init)
		वापस 0;

	अगर (!slave->unattach_request)
		जाओ regmap_sync;

	समय = रुको_क्रम_completion_समयout(&slave->initialization_complete,
				msecs_to_jअगरfies(RT711_PROBE_TIMEOUT));
	अगर (!समय) अणु
		dev_err(&slave->dev, "Initialization not complete, timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

regmap_sync:
	slave->unattach_request = 0;
	regcache_cache_only(rt711->regmap, false);
	regcache_sync(rt711->regmap);
	regcache_cache_only(rt711->mbq_regmap, false);
	regcache_sync(rt711->mbq_regmap);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rt711_sdca_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rt711_sdca_dev_suspend, rt711_sdca_dev_resume)
	SET_RUNTIME_PM_OPS(rt711_sdca_dev_suspend, rt711_sdca_dev_resume, शून्य)
पूर्ण;

अटल काष्ठा sdw_driver rt711_sdca_sdw_driver = अणु
	.driver = अणु
		.name = "rt711-sdca",
		.owner = THIS_MODULE,
		.pm = &rt711_sdca_pm,
	पूर्ण,
	.probe = rt711_sdca_sdw_probe,
	.हटाओ = rt711_sdca_sdw_हटाओ,
	.ops = &rt711_sdca_slave_ops,
	.id_table = rt711_sdca_id,
पूर्ण;
module_sdw_driver(rt711_sdca_sdw_driver);

MODULE_DESCRIPTION("ASoC RT711 SDCA SDW driver");
MODULE_AUTHOR("Shuming Fan <shumingf@realtek.com>");
MODULE_LICENSE("GPL");
