<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// rt711-sdw.c -- rt711 ALSA SoC audio driver
//
// Copyright(c) 2019 Realtek Semiconductor Corp.
//
//

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_type.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश "rt711.h"
#समावेश "rt711-sdw.h"

अटल bool rt711_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x00e0:
	हाल 0x00f0:
	हाल 0x2012 ... 0x2016:
	हाल 0x201a ... 0x2027:
	हाल 0x2029 ... 0x202a:
	हाल 0x202d ... 0x2034:
	हाल 0x2201 ... 0x2204:
	हाल 0x2206 ... 0x2212:
	हाल 0x2220 ... 0x2223:
	हाल 0x2230 ... 0x2239:
	हाल 0x2f01 ... 0x2f0f:
	हाल 0x3000 ... 0x3fff:
	हाल 0x7000 ... 0x7fff:
	हाल 0x8300 ... 0x83ff:
	हाल 0x9c00 ... 0x9cff:
	हाल 0xb900 ... 0xb9ff:
	हाल 0x752009:
	हाल 0x752011:
	हाल 0x75201a:
	हाल 0x752045:
	हाल 0x752046:
	हाल 0x752048:
	हाल 0x75204a:
	हाल 0x75206b:
	हाल 0x75206f:
	हाल 0x752080:
	हाल 0x752081:
	हाल 0x752091:
	हाल 0x755800:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rt711_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x2016:
	हाल 0x201b:
	हाल 0x201c:
	हाल 0x201d:
	हाल 0x201f:
	हाल 0x2021:
	हाल 0x2023:
	हाल 0x2230:
	हाल 0x2012 ... 0x2015: /* HD-A पढ़ो */
	हाल 0x202d ... 0x202f: /* BRA */
	हाल 0x2201 ... 0x2212: /* i2c debug */
	हाल 0x2220 ... 0x2223: /* decoded HD-A */
	हाल 0x9c00 ... 0x9cff:
	हाल 0xb900 ... 0xb9ff:
	हाल 0xff01:
	हाल 0x75201a:
	हाल 0x752046:
	हाल 0x752080:
	हाल 0x752081:
	हाल 0x755800:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक rt711_sdw_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा device *dev = context;
	काष्ठा rt711_priv *rt711 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक sdw_data_3, sdw_data_2, sdw_data_1, sdw_data_0;
	अचिन्हित पूर्णांक reg2 = 0, reg3 = 0, reg4 = 0, mask, nid, val2;
	अचिन्हित पूर्णांक is_hda_reg = 1, is_index_reg = 0;
	पूर्णांक ret;

	अगर (reg > 0xffff)
		is_index_reg = 1;

	mask = reg & 0xf000;

	अगर (is_index_reg) अणु /* index रेजिस्टरs */
		val2 = reg & 0xff;
		reg = reg >> 8;
		nid = reg & 0xff;
		ret = regmap_ग_लिखो(rt711->sdw_regmap, reg, 0);
		अगर (ret < 0)
			वापस ret;
		reg2 = reg + 0x1000;
		reg2 |= 0x80;
		ret = regmap_ग_लिखो(rt711->sdw_regmap, reg2, val2);
		अगर (ret < 0)
			वापस ret;

		reg3 = RT711_PRIV_DATA_R_H | nid;
		ret = regmap_ग_लिखो(rt711->sdw_regmap,
			reg3, ((*val >> 8) & 0xff));
		अगर (ret < 0)
			वापस ret;
		reg4 = reg3 + 0x1000;
		reg4 |= 0x80;
		ret = regmap_ग_लिखो(rt711->sdw_regmap, reg4, (*val & 0xff));
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (mask   == 0x3000) अणु
		reg += 0x8000;
		ret = regmap_ग_लिखो(rt711->sdw_regmap, reg, *val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (mask == 0x7000) अणु
		reg += 0x2000;
		reg |= 0x800;
		ret = regmap_ग_लिखो(rt711->sdw_regmap,
			reg, ((*val >> 8) & 0xff));
		अगर (ret < 0)
			वापस ret;
		reg2 = reg + 0x1000;
		reg2 |= 0x80;
		ret = regmap_ग_लिखो(rt711->sdw_regmap, reg2, (*val & 0xff));
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर ((reg & 0xff00) == 0x8300) अणु /* क्रम R channel */
		reg2 = reg - 0x1000;
		reg2 &= ~0x80;
		ret = regmap_ग_लिखो(rt711->sdw_regmap,
			reg2, ((*val >> 8) & 0xff));
		अगर (ret < 0)
			वापस ret;
		ret = regmap_ग_लिखो(rt711->sdw_regmap, reg, (*val & 0xff));
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (mask == 0x9000) अणु
		ret = regmap_ग_लिखो(rt711->sdw_regmap,
			reg, ((*val >> 8) & 0xff));
		अगर (ret < 0)
			वापस ret;
		reg2 = reg + 0x1000;
		reg2 |= 0x80;
		ret = regmap_ग_लिखो(rt711->sdw_regmap, reg2, (*val & 0xff));
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (mask == 0xb000) अणु
		ret = regmap_ग_लिखो(rt711->sdw_regmap, reg, *val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = regmap_पढ़ो(rt711->sdw_regmap, reg, val);
		अगर (ret < 0)
			वापस ret;
		is_hda_reg = 0;
	पूर्ण

	अगर (is_hda_reg || is_index_reg) अणु
		sdw_data_3 = 0;
		sdw_data_2 = 0;
		sdw_data_1 = 0;
		sdw_data_0 = 0;
		ret = regmap_पढ़ो(rt711->sdw_regmap,
			RT711_READ_HDA_3, &sdw_data_3);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_पढ़ो(rt711->sdw_regmap,
			RT711_READ_HDA_2, &sdw_data_2);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_पढ़ो(rt711->sdw_regmap,
			RT711_READ_HDA_1, &sdw_data_1);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_पढ़ो(rt711->sdw_regmap,
			RT711_READ_HDA_0, &sdw_data_0);
		अगर (ret < 0)
			वापस ret;
		*val = ((sdw_data_3 & 0xff) << 24) |
			((sdw_data_2 & 0xff) << 16) |
			((sdw_data_1 & 0xff) << 8) | (sdw_data_0 & 0xff);
	पूर्ण

	अगर (is_hda_reg == 0)
		dev_dbg(dev, "[%s] %04x => %08x\n", __func__, reg, *val);
	अन्यथा अगर (is_index_reg)
		dev_dbg(dev, "[%s] %04x %04x %04x %04x => %08x\n",
			__func__, reg, reg2, reg3, reg4, *val);
	अन्यथा
		dev_dbg(dev, "[%s] %04x %04x => %08x\n",
			__func__, reg, reg2, *val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdw_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा device *dev = context;
	काष्ठा rt711_priv *rt711 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक reg2 = 0, reg3, reg4, nid, mask, val2;
	अचिन्हित पूर्णांक is_index_reg = 0;
	पूर्णांक ret;

	अगर (reg > 0xffff)
		is_index_reg = 1;

	mask = reg & 0xf000;

	अगर (is_index_reg) अणु /* index रेजिस्टरs */
		val2 = reg & 0xff;
		reg = reg >> 8;
		nid = reg & 0xff;
		ret = regmap_ग_लिखो(rt711->sdw_regmap, reg, 0);
		अगर (ret < 0)
			वापस ret;
		reg2 = reg + 0x1000;
		reg2 |= 0x80;
		ret = regmap_ग_लिखो(rt711->sdw_regmap, reg2, val2);
		अगर (ret < 0)
			वापस ret;

		reg3 = RT711_PRIV_DATA_W_H | nid;
		ret = regmap_ग_लिखो(rt711->sdw_regmap,
			reg3, ((val >> 8) & 0xff));
		अगर (ret < 0)
			वापस ret;
		reg4 = reg3 + 0x1000;
		reg4 |= 0x80;
		ret = regmap_ग_लिखो(rt711->sdw_regmap, reg4, (val & 0xff));
		अगर (ret < 0)
			वापस ret;
		is_index_reg = 1;
	पूर्ण अन्यथा अगर (reg < 0x4fff) अणु
		ret = regmap_ग_लिखो(rt711->sdw_regmap, reg, val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (reg == RT711_FUNC_RESET) अणु
		ret = regmap_ग_लिखो(rt711->sdw_regmap, reg, val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (mask == 0x7000) अणु
		ret = regmap_ग_लिखो(rt711->sdw_regmap,
			reg, ((val >> 8) & 0xff));
		अगर (ret < 0)
			वापस ret;
		reg2 = reg + 0x1000;
		reg2 |= 0x80;
		ret = regmap_ग_लिखो(rt711->sdw_regmap, reg2, (val & 0xff));
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर ((reg & 0xff00) == 0x8300) अणु  /* क्रम R channel */
		reg2 = reg - 0x1000;
		reg2 &= ~0x80;
		ret = regmap_ग_लिखो(rt711->sdw_regmap,
			reg2, ((val >> 8) & 0xff));
		अगर (ret < 0)
			वापस ret;
		ret = regmap_ग_लिखो(rt711->sdw_regmap, reg, (val & 0xff));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (reg2 == 0)
		dev_dbg(dev, "[%s] %04x <= %04x\n", __func__, reg, val);
	अन्यथा अगर (is_index_reg)
		dev_dbg(dev, "[%s] %04x %04x %04x %04x <= %04x %04x\n",
			__func__, reg, reg2, reg3, reg4, val2, val);
	अन्यथा
		dev_dbg(dev, "[%s] %04x %04x <= %04x\n",
			__func__, reg, reg2, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config rt711_regmap = अणु
	.reg_bits = 24,
	.val_bits = 32,
	.पढ़ोable_reg = rt711_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = rt711_अस्थिर_रेजिस्टर,
	.max_रेजिस्टर = 0x755800,
	.reg_शेषs = rt711_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(rt711_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	.reg_पढ़ो = rt711_sdw_पढ़ो,
	.reg_ग_लिखो = rt711_sdw_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt711_sdw_regmap = अणु
	.name = "sdw",
	.reg_bits = 32,
	.val_bits = 8,
	.पढ़ोable_reg = rt711_पढ़ोable_रेजिस्टर,
	.max_रेजिस्टर = 0xff01,
	.cache_type = REGCACHE_NONE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल पूर्णांक rt711_update_status(काष्ठा sdw_slave *slave,
				क्रमागत sdw_slave_status status)
अणु
	काष्ठा rt711_priv *rt711 = dev_get_drvdata(&slave->dev);

	/* Update the status */
	rt711->status = status;

	अगर (status == SDW_SLAVE_UNATTACHED)
		rt711->hw_init = false;

	/*
	 * Perक्रमm initialization only अगर slave status is present and
	 * hw_init flag is false
	 */
	अगर (rt711->hw_init || rt711->status != SDW_SLAVE_ATTACHED)
		वापस 0;

	/* perक्रमm I/O transfers required क्रम Slave initialization */
	वापस rt711_io_init(&slave->dev, slave);
पूर्ण

अटल पूर्णांक rt711_पढ़ो_prop(काष्ठा sdw_slave *slave)
अणु
	काष्ठा sdw_slave_prop *prop = &slave->prop;
	पूर्णांक nval;
	पूर्णांक i, j;
	u32 bit;
	अचिन्हित दीर्घ addr;
	काष्ठा sdw_dpn_prop *dpn;

	prop->scp_पूर्णांक1_mask = SDW_SCP_INT1_IMPL_DEF | SDW_SCP_INT1_BUS_CLASH |
		SDW_SCP_INT1_PARITY;
	prop->quirks = SDW_SLAVE_QUIRKS_INVALID_INITIAL_PARITY;

	prop->paging_support = false;

	/* first we need to allocate memory क्रम set bits in port lists */
	prop->source_ports = 0x14; /* BITMAP: 00010100 */
	prop->sink_ports = 0x8; /* BITMAP:  00001000 */

	nval = hweight32(prop->source_ports);
	prop->src_dpn_prop = devm_kसुस्मृति(&slave->dev, nval,
						माप(*prop->src_dpn_prop),
						GFP_KERNEL);
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
						माप(*prop->sink_dpn_prop),
						GFP_KERNEL);
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

अटल पूर्णांक rt711_bus_config(काष्ठा sdw_slave *slave,
				काष्ठा sdw_bus_params *params)
अणु
	काष्ठा rt711_priv *rt711 = dev_get_drvdata(&slave->dev);
	पूर्णांक ret;

	स_नकल(&rt711->params, params, माप(*params));

	ret = rt711_घड़ी_config(&slave->dev);
	अगर (ret < 0)
		dev_err(&slave->dev, "Invalid clk config");

	वापस ret;
पूर्ण

अटल पूर्णांक rt711_पूर्णांकerrupt_callback(काष्ठा sdw_slave *slave,
					काष्ठा sdw_slave_पूर्णांकr_status *status)
अणु
	काष्ठा rt711_priv *rt711 = dev_get_drvdata(&slave->dev);

	dev_dbg(&slave->dev,
		"%s control_port_stat=%x", __func__, status->control_port);

	अगर (status->control_port & 0x4) अणु
		mod_delayed_work(प्रणाली_घातer_efficient_wq,
			&rt711->jack_detect_work, msecs_to_jअगरfies(250));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdw_slave_ops rt711_slave_ops = अणु
	.पढ़ो_prop = rt711_पढ़ो_prop,
	.पूर्णांकerrupt_callback = rt711_पूर्णांकerrupt_callback,
	.update_status = rt711_update_status,
	.bus_config = rt711_bus_config,
पूर्ण;

अटल पूर्णांक rt711_sdw_probe(काष्ठा sdw_slave *slave,
				स्थिर काष्ठा sdw_device_id *id)
अणु
	काष्ठा regmap *sdw_regmap, *regmap;

	/* Regmap Initialization */
	sdw_regmap = devm_regmap_init_sdw(slave, &rt711_sdw_regmap);
	अगर (IS_ERR(sdw_regmap))
		वापस PTR_ERR(sdw_regmap);

	regmap = devm_regmap_init(&slave->dev, शून्य,
		&slave->dev, &rt711_regmap);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	rt711_init(&slave->dev, sdw_regmap, regmap, slave);

	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdw_हटाओ(काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt711_priv *rt711 = dev_get_drvdata(&slave->dev);

	अगर (rt711 && rt711->hw_init) अणु
		cancel_delayed_work_sync(&rt711->jack_detect_work);
		cancel_delayed_work_sync(&rt711->jack_btn_check_work);
		cancel_work_sync(&rt711->calibration_work);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdw_device_id rt711_id[] = अणु
	SDW_SLAVE_ENTRY_EXT(0x025d, 0x711, 0x2, 0, 0),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(sdw, rt711_id);

अटल पूर्णांक __maybe_unused rt711_dev_suspend(काष्ठा device *dev)
अणु
	काष्ठा rt711_priv *rt711 = dev_get_drvdata(dev);

	अगर (!rt711->hw_init)
		वापस 0;

	cancel_delayed_work_sync(&rt711->jack_detect_work);
	cancel_delayed_work_sync(&rt711->jack_btn_check_work);
	cancel_work_sync(&rt711->calibration_work);

	regcache_cache_only(rt711->regmap, true);

	वापस 0;
पूर्ण

#घोषणा RT711_PROBE_TIMEOUT 5000

अटल पूर्णांक __maybe_unused rt711_dev_resume(काष्ठा device *dev)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	काष्ठा rt711_priv *rt711 = dev_get_drvdata(dev);
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
	regcache_sync_region(rt711->regmap, 0x3000, 0x8fff);
	regcache_sync_region(rt711->regmap, 0x752009, 0x752091);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rt711_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rt711_dev_suspend, rt711_dev_resume)
	SET_RUNTIME_PM_OPS(rt711_dev_suspend, rt711_dev_resume, शून्य)
पूर्ण;

अटल काष्ठा sdw_driver rt711_sdw_driver = अणु
	.driver = अणु
		.name = "rt711",
		.owner = THIS_MODULE,
		.pm = &rt711_pm,
	पूर्ण,
	.probe = rt711_sdw_probe,
	.हटाओ = rt711_sdw_हटाओ,
	.ops = &rt711_slave_ops,
	.id_table = rt711_id,
पूर्ण;
module_sdw_driver(rt711_sdw_driver);

MODULE_DESCRIPTION("ASoC RT711 SDW driver");
MODULE_AUTHOR("Shuming Fan <shumingf@realtek.com>");
MODULE_LICENSE("GPL");
