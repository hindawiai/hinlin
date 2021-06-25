<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control.  SMU "satellite" controller sensors.
 *
 * Copyright (C) 2005 Paul Mackerras, IBM Corp. <paulus@samba.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/रुको.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/smu.h>
#समावेश <यंत्र/pmac_low_i2c.h>

#समावेश "windfarm.h"

#घोषणा VERSION "1.0"

/* If the cache is older than 800ms we'll refetch it */
#घोषणा MAX_AGE		msecs_to_jअगरfies(800)

काष्ठा wf_sat अणु
	काष्ठा kref		ref;
	पूर्णांक			nr;
	काष्ठा mutex		mutex;
	अचिन्हित दीर्घ		last_पढ़ो; /* jअगरfies when cache last updated */
	u8			cache[16];
	काष्ठा list_head	sensors;
	काष्ठा i2c_client	*i2c;
	काष्ठा device_node	*node;
पूर्ण;

अटल काष्ठा wf_sat *sats[2];

काष्ठा wf_sat_sensor अणु
	काष्ठा list_head	link;
	पूर्णांक			index;
	पूर्णांक			index2;		/* used क्रम घातer sensors */
	पूर्णांक			shअगरt;
	काष्ठा wf_sat		*sat;
	काष्ठा wf_sensor 	sens;
पूर्ण;

#घोषणा wf_to_sat(c)	container_of(c, काष्ठा wf_sat_sensor, sens)

काष्ठा smu_sdbp_header *smu_sat_get_sdb_partition(अचिन्हित पूर्णांक sat_id, पूर्णांक id,
						  अचिन्हित पूर्णांक *size)
अणु
	काष्ठा wf_sat *sat;
	पूर्णांक err;
	अचिन्हित पूर्णांक i, len;
	u8 *buf;
	u8 data[4];

	/* TODO: Add the resulting partition to the device-tree */

	अगर (sat_id > 1 || (sat = sats[sat_id]) == शून्य)
		वापस शून्य;

	err = i2c_smbus_ग_लिखो_word_data(sat->i2c, 8, id << 8);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "smu_sat_get_sdb_part wr error %d\n", err);
		वापस शून्य;
	पूर्ण

	err = i2c_smbus_पढ़ो_word_data(sat->i2c, 9);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "smu_sat_get_sdb_part rd len error\n");
		वापस शून्य;
	पूर्ण
	len = err;
	अगर (len == 0) अणु
		prपूर्णांकk(KERN_ERR "smu_sat_get_sdb_part no partition %x\n", id);
		वापस शून्य;
	पूर्ण

	len = le16_to_cpu(len);
	len = (len + 3) & ~3;
	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस शून्य;

	क्रम (i = 0; i < len; i += 4) अणु
		err = i2c_smbus_पढ़ो_i2c_block_data(sat->i2c, 0xa, 4, data);
		अगर (err < 0) अणु
			prपूर्णांकk(KERN_ERR "smu_sat_get_sdb_part rd err %d\n",
			       err);
			जाओ fail;
		पूर्ण
		buf[i] = data[1];
		buf[i+1] = data[0];
		buf[i+2] = data[3];
		buf[i+3] = data[2];
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "sat %d partition %x:", sat_id, id);
	prपूर्णांक_hex_dump(KERN_DEBUG, "  ", DUMP_PREFIX_OFFSET,
		       16, 1, buf, len, false);
	अगर (size)
		*size = len;
	वापस (काष्ठा smu_sdbp_header *) buf;

 fail:
	kमुक्त(buf);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(smu_sat_get_sdb_partition);

/* refresh the cache */
अटल पूर्णांक wf_sat_पढ़ो_cache(काष्ठा wf_sat *sat)
अणु
	पूर्णांक err;

	err = i2c_smbus_पढ़ो_i2c_block_data(sat->i2c, 0x3f, 16, sat->cache);
	अगर (err < 0)
		वापस err;
	sat->last_पढ़ो = jअगरfies;

#अगर_घोषित LOTSA_DEBUG
	अणु
		पूर्णांक i;
		prपूर्णांकk(KERN_DEBUG "wf_sat_get: data is");
		prपूर्णांक_hex_dump(KERN_DEBUG, "  ", DUMP_PREFIX_OFFSET,
			       16, 1, sat->cache, 16, false);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक wf_sat_sensor_get(काष्ठा wf_sensor *sr, s32 *value)
अणु
	काष्ठा wf_sat_sensor *sens = wf_to_sat(sr);
	काष्ठा wf_sat *sat = sens->sat;
	पूर्णांक i, err;
	s32 val;

	अगर (sat->i2c == शून्य)
		वापस -ENODEV;

	mutex_lock(&sat->mutex);
	अगर (समय_after(jअगरfies, (sat->last_पढ़ो + MAX_AGE))) अणु
		err = wf_sat_पढ़ो_cache(sat);
		अगर (err)
			जाओ fail;
	पूर्ण

	i = sens->index * 2;
	val = ((sat->cache[i] << 8) + sat->cache[i+1]) << sens->shअगरt;
	अगर (sens->index2 >= 0) अणु
		i = sens->index2 * 2;
		/* 4.12 * 8.8 -> 12.20; shअगरt right 4 to get 16.16 */
		val = (val * ((sat->cache[i] << 8) + sat->cache[i+1])) >> 4;
	पूर्ण

	*value = val;
	err = 0;

 fail:
	mutex_unlock(&sat->mutex);
	वापस err;
पूर्ण

अटल व्योम wf_sat_release(काष्ठा kref *ref)
अणु
	काष्ठा wf_sat *sat = container_of(ref, काष्ठा wf_sat, ref);

	अगर (sat->nr >= 0)
		sats[sat->nr] = शून्य;
	kमुक्त(sat);
पूर्ण

अटल व्योम wf_sat_sensor_release(काष्ठा wf_sensor *sr)
अणु
	काष्ठा wf_sat_sensor *sens = wf_to_sat(sr);
	काष्ठा wf_sat *sat = sens->sat;

	kमुक्त(sens);
	kref_put(&sat->ref, wf_sat_release);
पूर्ण

अटल स्थिर काष्ठा wf_sensor_ops wf_sat_ops = अणु
	.get_value	= wf_sat_sensor_get,
	.release	= wf_sat_sensor_release,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक wf_sat_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device_node *dev = client->dev.of_node;
	काष्ठा wf_sat *sat;
	काष्ठा wf_sat_sensor *sens;
	स्थिर u32 *reg;
	स्थिर अक्षर *loc;
	u8 chip, core;
	काष्ठा device_node *child;
	पूर्णांक shअगरt, cpu, index;
	अक्षर *name;
	पूर्णांक vsens[2], isens[2];

	sat = kzalloc(माप(काष्ठा wf_sat), GFP_KERNEL);
	अगर (sat == शून्य)
		वापस -ENOMEM;
	sat->nr = -1;
	sat->node = of_node_get(dev);
	kref_init(&sat->ref);
	mutex_init(&sat->mutex);
	sat->i2c = client;
	INIT_LIST_HEAD(&sat->sensors);
	i2c_set_clientdata(client, sat);

	vsens[0] = vsens[1] = -1;
	isens[0] = isens[1] = -1;
	क्रम_each_child_of_node(dev, child) अणु
		reg = of_get_property(child, "reg", शून्य);
		loc = of_get_property(child, "location", शून्य);
		अगर (reg == शून्य || loc == शून्य)
			जारी;

		/* the cooked sensors are between 0x30 and 0x37 */
		अगर (*reg < 0x30 || *reg > 0x37)
			जारी;
		index = *reg - 0x30;

		/* expect location to be CPU [AB][01] ... */
		अगर (म_भेदन(loc, "CPU ", 4) != 0)
			जारी;
		chip = loc[4] - 'A';
		core = loc[5] - '0';
		अगर (chip > 1 || core > 1) अणु
			prपूर्णांकk(KERN_ERR "wf_sat_create: don't understand "
			       "location %s for %pOF\n", loc, child);
			जारी;
		पूर्ण
		cpu = 2 * chip + core;
		अगर (sat->nr < 0)
			sat->nr = chip;
		अन्यथा अगर (sat->nr != chip) अणु
			prपूर्णांकk(KERN_ERR "wf_sat_create: can't cope with "
			       "multiple CPU chips on one SAT (%s)\n", loc);
			जारी;
		पूर्ण

		अगर (of_node_is_type(child, "voltage-sensor")) अणु
			name = "cpu-voltage";
			shअगरt = 4;
			vsens[core] = index;
		पूर्ण अन्यथा अगर (of_node_is_type(child, "current-sensor")) अणु
			name = "cpu-current";
			shअगरt = 8;
			isens[core] = index;
		पूर्ण अन्यथा अगर (of_node_is_type(child, "temp-sensor")) अणु
			name = "cpu-temp";
			shअगरt = 10;
		पूर्ण अन्यथा
			जारी;	/* hmmm shouldn't happen */

		/* the +16 is enough क्रम "cpu-voltage-n" */
		sens = kzalloc(माप(काष्ठा wf_sat_sensor) + 16, GFP_KERNEL);
		अगर (sens == शून्य) अणु
			prपूर्णांकk(KERN_ERR "wf_sat_create: couldn't create "
			       "%s sensor %d (no memory)\n", name, cpu);
			जारी;
		पूर्ण
		sens->index = index;
		sens->index2 = -1;
		sens->shअगरt = shअगरt;
		sens->sat = sat;
		sens->sens.ops = &wf_sat_ops;
		sens->sens.name = (अक्षर *) (sens + 1);
		snम_लिखो((अक्षर *)sens->sens.name, 16, "%s-%d", name, cpu);

		अगर (wf_रेजिस्टर_sensor(&sens->sens))
			kमुक्त(sens);
		अन्यथा अणु
			list_add(&sens->link, &sat->sensors);
			kref_get(&sat->ref);
		पूर्ण
	पूर्ण

	/* make the घातer sensors */
	क्रम (core = 0; core < 2; ++core) अणु
		अगर (vsens[core] < 0 || isens[core] < 0)
			जारी;
		cpu = 2 * sat->nr + core;
		sens = kzalloc(माप(काष्ठा wf_sat_sensor) + 16, GFP_KERNEL);
		अगर (sens == शून्य) अणु
			prपूर्णांकk(KERN_ERR "wf_sat_create: couldn't create power "
			       "sensor %d (no memory)\n", cpu);
			जारी;
		पूर्ण
		sens->index = vsens[core];
		sens->index2 = isens[core];
		sens->shअगरt = 0;
		sens->sat = sat;
		sens->sens.ops = &wf_sat_ops;
		sens->sens.name = (अक्षर *) (sens + 1);
		snम_लिखो((अक्षर *)sens->sens.name, 16, "cpu-power-%d", cpu);

		अगर (wf_रेजिस्टर_sensor(&sens->sens))
			kमुक्त(sens);
		अन्यथा अणु
			list_add(&sens->link, &sat->sensors);
			kref_get(&sat->ref);
		पूर्ण
	पूर्ण

	अगर (sat->nr >= 0)
		sats[sat->nr] = sat;

	वापस 0;
पूर्ण

अटल पूर्णांक wf_sat_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा wf_sat *sat = i2c_get_clientdata(client);
	काष्ठा wf_sat_sensor *sens;

	/* release sensors */
	जबतक(!list_empty(&sat->sensors)) अणु
		sens = list_first_entry(&sat->sensors,
					काष्ठा wf_sat_sensor, link);
		list_del(&sens->link);
		wf_unरेजिस्टर_sensor(&sens->sens);
	पूर्ण
	sat->i2c = शून्य;
	kref_put(&sat->ref, wf_sat_release);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wf_sat_id[] = अणु
	अणु "MAC,smu-sat", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wf_sat_id);

अटल स्थिर काष्ठा of_device_id wf_sat_of_id[] = अणु
	अणु .compatible = "smu-sat", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wf_sat_of_id);

अटल काष्ठा i2c_driver wf_sat_driver = अणु
	.driver = अणु
		.name		= "wf_smu_sat",
		.of_match_table = wf_sat_of_id,
	पूर्ण,
	.probe		= wf_sat_probe,
	.हटाओ		= wf_sat_हटाओ,
	.id_table	= wf_sat_id,
पूर्ण;

module_i2c_driver(wf_sat_driver);

MODULE_AUTHOR("Paul Mackerras <paulus@samba.org>");
MODULE_DESCRIPTION("SMU satellite sensors for PowerMac thermal control");
MODULE_LICENSE("GPL");
