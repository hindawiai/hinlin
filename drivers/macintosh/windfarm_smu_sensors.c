<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control. SMU based sensors
 *
 * (c) Copyright 2005 Benjamin Herrenschmidt, IBM Corp.
 *                    <benh@kernel.crashing.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/रुको.h>
#समावेश <linux/completion.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/smu.h>

#समावेश "windfarm.h"

#घोषणा VERSION "0.2"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(args...)	prपूर्णांकk(args)
#अन्यथा
#घोषणा DBG(args...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

/*
 * Various SMU "partitions" calibration objects क्रम which we
 * keep poपूर्णांकers here क्रम use by bits & pieces of the driver
 */
अटल काष्ठा smu_sdbp_cpuvcp *cpuvcp;
अटल पूर्णांक  cpuvcp_version;
अटल काष्ठा smu_sdbp_cpudiode *cpudiode;
अटल काष्ठा smu_sdbp_slotsघात *slotsघात;
अटल u8 *debugचयनes;

/*
 * SMU basic sensors objects
 */

अटल LIST_HEAD(smu_ads);

काष्ठा smu_ad_sensor अणु
	काष्ठा list_head	link;
	u32			reg;		/* index in SMU */
	काष्ठा wf_sensor	sens;
पूर्ण;
#घोषणा to_smu_ads(c) container_of(c, काष्ठा smu_ad_sensor, sens)

अटल व्योम smu_ads_release(काष्ठा wf_sensor *sr)
अणु
	काष्ठा smu_ad_sensor *ads = to_smu_ads(sr);

	kमुक्त(ads);
पूर्ण

अटल पूर्णांक smu_पढ़ो_adc(u8 id, s32 *value)
अणु
	काष्ठा smu_simple_cmd	cmd;
	DECLARE_COMPLETION_ONSTACK(comp);
	पूर्णांक rc;

	rc = smu_queue_simple(&cmd, SMU_CMD_READ_ADC, 1,
			      smu_करोne_complete, &comp, id);
	अगर (rc)
		वापस rc;
	रुको_क्रम_completion(&comp);
	अगर (cmd.cmd.status != 0)
		वापस cmd.cmd.status;
	अगर (cmd.cmd.reply_len != 2) अणु
		prपूर्णांकk(KERN_ERR "winfarm: read ADC 0x%x returned %d bytes !\n",
		       id, cmd.cmd.reply_len);
		वापस -EIO;
	पूर्ण
	*value = *((u16 *)cmd.buffer);
	वापस 0;
पूर्ण

अटल पूर्णांक smu_cputemp_get(काष्ठा wf_sensor *sr, s32 *value)
अणु
	काष्ठा smu_ad_sensor *ads = to_smu_ads(sr);
	पूर्णांक rc;
	s32 val;
	s64 scaled;

	rc = smu_पढ़ो_adc(ads->reg, &val);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "windfarm: read CPU temp failed, err %d\n",
		       rc);
		वापस rc;
	पूर्ण

	/* Ok, we have to scale & adjust, taking units पूर्णांकo account */
	scaled = (s64)(((u64)val) * (u64)cpudiode->m_value);
	scaled >>= 3;
	scaled += ((s64)cpudiode->b_value) << 9;
	*value = (s32)(scaled << 1);

	वापस 0;
पूर्ण

अटल पूर्णांक smu_cpuamp_get(काष्ठा wf_sensor *sr, s32 *value)
अणु
	काष्ठा smu_ad_sensor *ads = to_smu_ads(sr);
	s32 val, scaled;
	पूर्णांक rc;

	rc = smu_पढ़ो_adc(ads->reg, &val);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "windfarm: read CPU current failed, err %d\n",
		       rc);
		वापस rc;
	पूर्ण

	/* Ok, we have to scale & adjust, taking units पूर्णांकo account */
	scaled = (s32)(val * (u32)cpuvcp->curr_scale);
	scaled += (s32)cpuvcp->curr_offset;
	*value = scaled << 4;

	वापस 0;
पूर्ण

अटल पूर्णांक smu_cpuvolt_get(काष्ठा wf_sensor *sr, s32 *value)
अणु
	काष्ठा smu_ad_sensor *ads = to_smu_ads(sr);
	s32 val, scaled;
	पूर्णांक rc;

	rc = smu_पढ़ो_adc(ads->reg, &val);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "windfarm: read CPU voltage failed, err %d\n",
		       rc);
		वापस rc;
	पूर्ण

	/* Ok, we have to scale & adjust, taking units पूर्णांकo account */
	scaled = (s32)(val * (u32)cpuvcp->volt_scale);
	scaled += (s32)cpuvcp->volt_offset;
	*value = scaled << 4;

	वापस 0;
पूर्ण

अटल पूर्णांक smu_slotsघात_get(काष्ठा wf_sensor *sr, s32 *value)
अणु
	काष्ठा smu_ad_sensor *ads = to_smu_ads(sr);
	s32 val, scaled;
	पूर्णांक rc;

	rc = smu_पढ़ो_adc(ads->reg, &val);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "windfarm: read slots power failed, err %d\n",
		       rc);
		वापस rc;
	पूर्ण

	/* Ok, we have to scale & adjust, taking units पूर्णांकo account */
	scaled = (s32)(val * (u32)slotsघात->घात_scale);
	scaled += (s32)slotsघात->घात_offset;
	*value = scaled << 4;

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा wf_sensor_ops smu_cputemp_ops = अणु
	.get_value	= smu_cputemp_get,
	.release	= smu_ads_release,
	.owner		= THIS_MODULE,
पूर्ण;
अटल स्थिर काष्ठा wf_sensor_ops smu_cpuamp_ops = अणु
	.get_value	= smu_cpuamp_get,
	.release	= smu_ads_release,
	.owner		= THIS_MODULE,
पूर्ण;
अटल स्थिर काष्ठा wf_sensor_ops smu_cpuvolt_ops = अणु
	.get_value	= smu_cpuvolt_get,
	.release	= smu_ads_release,
	.owner		= THIS_MODULE,
पूर्ण;
अटल स्थिर काष्ठा wf_sensor_ops smu_slotsघात_ops = अणु
	.get_value	= smu_slotsघात_get,
	.release	= smu_ads_release,
	.owner		= THIS_MODULE,
पूर्ण;


अटल काष्ठा smu_ad_sensor *smu_ads_create(काष्ठा device_node *node)
अणु
	काष्ठा smu_ad_sensor *ads;
	स्थिर अक्षर *l;
	स्थिर u32 *v;

	ads = kदो_स्मृति(माप(काष्ठा smu_ad_sensor), GFP_KERNEL);
	अगर (ads == शून्य)
		वापस शून्य;
	l = of_get_property(node, "location", शून्य);
	अगर (l == शून्य)
		जाओ fail;

	/* We currently pick the sensors based on the OF name and location
	 * properties, जबतक Darwin uses the sensor-id's.
	 * The problem with the IDs is that they are model specअगरic जबतक it
	 * looks like apple has been करोing a reasonably good job at keeping
	 * the names and locations consistents so I'll stick with the names
	 * and locations क्रम now.
	 */
	अगर (of_node_is_type(node, "temp-sensor") &&
	    !म_भेद(l, "CPU T-Diode")) अणु
		ads->sens.ops = &smu_cputemp_ops;
		ads->sens.name = "cpu-temp";
		अगर (cpudiode == शून्य) अणु
			DBG("wf: cpudiode partition (%02x) not found\n",
			    SMU_SDB_CPUDIODE_ID);
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अगर (of_node_is_type(node, "current-sensor") &&
		   !म_भेद(l, "CPU Current")) अणु
		ads->sens.ops = &smu_cpuamp_ops;
		ads->sens.name = "cpu-current";
		अगर (cpuvcp == शून्य) अणु
			DBG("wf: cpuvcp partition (%02x) not found\n",
			    SMU_SDB_CPUVCP_ID);
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अगर (of_node_is_type(node, "voltage-sensor") &&
		   !म_भेद(l, "CPU Voltage")) अणु
		ads->sens.ops = &smu_cpuvolt_ops;
		ads->sens.name = "cpu-voltage";
		अगर (cpuvcp == शून्य) अणु
			DBG("wf: cpuvcp partition (%02x) not found\n",
			    SMU_SDB_CPUVCP_ID);
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अगर (of_node_is_type(node, "power-sensor") &&
		   !म_भेद(l, "Slots Power")) अणु
		ads->sens.ops = &smu_slotsघात_ops;
		ads->sens.name = "slots-power";
		अगर (slotsघात == शून्य) अणु
			DBG("wf: slotspow partition (%02x) not found\n",
			    SMU_SDB_SLOTSPOW_ID);
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा
		जाओ fail;

	v = of_get_property(node, "reg", शून्य);
	अगर (v == शून्य)
		जाओ fail;
	ads->reg = *v;

	अगर (wf_रेजिस्टर_sensor(&ads->sens))
		जाओ fail;
	वापस ads;
 fail:
	kमुक्त(ads);
	वापस शून्य;
पूर्ण

/*
 * SMU Power combo sensor object
 */

काष्ठा smu_cpu_घातer_sensor अणु
	काष्ठा list_head	link;
	काष्ठा wf_sensor	*volts;
	काष्ठा wf_sensor	*amps;
	पूर्णांक			fake_volts : 1;
	पूर्णांक			quadratic : 1;
	काष्ठा wf_sensor	sens;
पूर्ण;
#घोषणा to_smu_cpu_घातer(c) container_of(c, काष्ठा smu_cpu_घातer_sensor, sens)

अटल काष्ठा smu_cpu_घातer_sensor *smu_cpu_घातer;

अटल व्योम smu_cpu_घातer_release(काष्ठा wf_sensor *sr)
अणु
	काष्ठा smu_cpu_घातer_sensor *घात = to_smu_cpu_घातer(sr);

	अगर (घात->volts)
		wf_put_sensor(घात->volts);
	अगर (घात->amps)
		wf_put_sensor(घात->amps);
	kमुक्त(घात);
पूर्ण

अटल पूर्णांक smu_cpu_घातer_get(काष्ठा wf_sensor *sr, s32 *value)
अणु
	काष्ठा smu_cpu_घातer_sensor *घात = to_smu_cpu_घातer(sr);
	s32 volts, amps, घातer;
	u64 पंचांगps, पंचांगpa, पंचांगpb;
	पूर्णांक rc;

	rc = घात->amps->ops->get_value(घात->amps, &amps);
	अगर (rc)
		वापस rc;

	अगर (घात->fake_volts) अणु
		*value = amps * 12 - 0x30000;
		वापस 0;
	पूर्ण

	rc = घात->volts->ops->get_value(घात->volts, &volts);
	अगर (rc)
		वापस rc;

	घातer = (s32)((((u64)volts) * ((u64)amps)) >> 16);
	अगर (!घात->quadratic) अणु
		*value = घातer;
		वापस 0;
	पूर्ण
	पंचांगps = (((u64)घातer) * ((u64)घातer)) >> 16;
	पंचांगpa = ((u64)cpuvcp->घातer_quads[0]) * पंचांगps;
	पंचांगpb = ((u64)cpuvcp->घातer_quads[1]) * ((u64)घातer);
	*value = (पंचांगpa >> 28) + (पंचांगpb >> 28) + (cpuvcp->घातer_quads[2] >> 12);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा wf_sensor_ops smu_cpu_घातer_ops = अणु
	.get_value	= smu_cpu_घातer_get,
	.release	= smu_cpu_घातer_release,
	.owner		= THIS_MODULE,
पूर्ण;


अटल काष्ठा smu_cpu_घातer_sensor *
smu_cpu_घातer_create(काष्ठा wf_sensor *volts, काष्ठा wf_sensor *amps)
अणु
	काष्ठा smu_cpu_घातer_sensor *घात;

	घात = kदो_स्मृति(माप(काष्ठा smu_cpu_घातer_sensor), GFP_KERNEL);
	अगर (घात == शून्य)
		वापस शून्य;
	घात->sens.ops = &smu_cpu_घातer_ops;
	घात->sens.name = "cpu-power";

	wf_get_sensor(volts);
	घात->volts = volts;
	wf_get_sensor(amps);
	घात->amps = amps;

	/* Some early machines need a faked voltage */
	अगर (debugचयनes && ((*debugचयनes) & 0x80)) अणु
		prपूर्णांकk(KERN_INFO "windfarm: CPU Power sensor using faked"
		       " voltage !\n");
		घात->fake_volts = 1;
	पूर्ण अन्यथा
		घात->fake_volts = 0;

	/* Try to use quadratic transक्रमms on PowerMac8,1 and 9,1 क्रम now,
	 * I yet have to figure out what's up with 8,2 and will have to
	 * adjust क्रम later, unless we can 100% trust the SDB partition...
	 */
	अगर ((of_machine_is_compatible("PowerMac8,1") ||
	     of_machine_is_compatible("PowerMac8,2") ||
	     of_machine_is_compatible("PowerMac9,1")) &&
	    cpuvcp_version >= 2) अणु
		घात->quadratic = 1;
		DBG("windfarm: CPU Power using quadratic transform\n");
	पूर्ण अन्यथा
		घात->quadratic = 0;

	अगर (wf_रेजिस्टर_sensor(&घात->sens))
		जाओ fail;
	वापस घात;
 fail:
	kमुक्त(घात);
	वापस शून्य;
पूर्ण

अटल व्योम smu_fetch_param_partitions(व्योम)
अणु
	स्थिर काष्ठा smu_sdbp_header *hdr;

	/* Get CPU voltage/current/घातer calibration data */
	hdr = smu_get_sdb_partition(SMU_SDB_CPUVCP_ID, शून्य);
	अगर (hdr != शून्य) अणु
		cpuvcp = (काष्ठा smu_sdbp_cpuvcp *)&hdr[1];
		/* Keep version around */
		cpuvcp_version = hdr->version;
	पूर्ण

	/* Get CPU diode calibration data */
	hdr = smu_get_sdb_partition(SMU_SDB_CPUDIODE_ID, शून्य);
	अगर (hdr != शून्य)
		cpudiode = (काष्ठा smu_sdbp_cpudiode *)&hdr[1];

	/* Get slots घातer calibration data अगर any */
	hdr = smu_get_sdb_partition(SMU_SDB_SLOTSPOW_ID, शून्य);
	अगर (hdr != शून्य)
		slotsघात = (काष्ठा smu_sdbp_slotsघात *)&hdr[1];

	/* Get debug चयनes अगर any */
	hdr = smu_get_sdb_partition(SMU_SDB_DEBUG_SWITCHES_ID, शून्य);
	अगर (hdr != शून्य)
		debugचयनes = (u8 *)&hdr[1];
पूर्ण

अटल पूर्णांक __init smu_sensors_init(व्योम)
अणु
	काष्ठा device_node *smu, *sensors, *s;
	काष्ठा smu_ad_sensor *volt_sensor = शून्य, *curr_sensor = शून्य;

	अगर (!smu_present())
		वापस -ENODEV;

	/* Get parameters partitions */
	smu_fetch_param_partitions();

	smu = of_find_node_by_type(शून्य, "smu");
	अगर (smu == शून्य)
		वापस -ENODEV;

	/* Look क्रम sensors subdir */
	क्रम_each_child_of_node(smu, sensors)
		अगर (of_node_name_eq(sensors, "sensors"))
			अवरोध;

	of_node_put(smu);

	/* Create basic sensors */
	क्रम (s = शून्य;
	     sensors && (s = of_get_next_child(sensors, s)) != शून्य;) अणु
		काष्ठा smu_ad_sensor *ads;

		ads = smu_ads_create(s);
		अगर (ads == शून्य)
			जारी;
		list_add(&ads->link, &smu_ads);
		/* keep track of cpu voltage & current */
		अगर (!म_भेद(ads->sens.name, "cpu-voltage"))
			volt_sensor = ads;
		अन्यथा अगर (!म_भेद(ads->sens.name, "cpu-current"))
			curr_sensor = ads;
	पूर्ण

	of_node_put(sensors);

	/* Create CPU घातer sensor अगर possible */
	अगर (volt_sensor && curr_sensor)
		smu_cpu_घातer = smu_cpu_घातer_create(&volt_sensor->sens,
						     &curr_sensor->sens);

	वापस 0;
पूर्ण

अटल व्योम __निकास smu_sensors_निकास(व्योम)
अणु
	काष्ठा smu_ad_sensor *ads;

	/* dispose of घातer sensor */
	अगर (smu_cpu_घातer)
		wf_unरेजिस्टर_sensor(&smu_cpu_घातer->sens);

	/* dispose of basic sensors */
	जबतक (!list_empty(&smu_ads)) अणु
		ads = list_entry(smu_ads.next, काष्ठा smu_ad_sensor, link);
		list_del(&ads->link);
		wf_unरेजिस्टर_sensor(&ads->sens);
	पूर्ण
पूर्ण


module_init(smu_sensors_init);
module_निकास(smu_sensors_निकास);

MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("SMU sensor objects for PowerMacs thermal control");
MODULE_LICENSE("GPL");

