<शैली गुरु>
/* 
 *   Creation Date: <2003/03/14 20:54:13 samuel>
 *   Time-stamp: <2004/03/20 14:20:59 samuel>
 *   
 *	<therm_windtunnel.c>
 *	
 *	The G4 "windtunnel" has a single fan controlled by an
 *	ADM1030 fan controller and a DS1775 thermostat.
 *
 *	The fan controller is equipped with a temperature sensor
 *	which measures the हाल temperature. The DS1775 sensor
 *	measures the CPU temperature. This driver tunes the
 *	behavior of the fan. It is based upon empirical observations
 *	of the 'AppleFan' driver under Mac OS X.
 *
 *	WARNING: This driver has only been testen on Apple's
 *	1.25 MHz Dual G4 (March 03). It is tuned क्रम a CPU
 *	temperature around 57 C.
 *
 *   Copyright (C) 2003, 2004 Samuel Rydh (samuel@ibrium.se)
 *
 *   Loosely based upon 'thermostat.c' written by Benjamin Herrenschmidt
 *   
 *   This program is मुक्त software; you can redistribute it and/or
 *   modअगरy it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation
 *   
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/macपन.स>

#घोषणा LOG_TEMP		0			/* continuously log temperature */

अटल काष्ठा अणु
	अस्थिर पूर्णांक		running;
	काष्ठा task_काष्ठा	*poll_task;
	
	काष्ठा mutex	 	lock;
	काष्ठा platक्रमm_device	*of_dev;
	
	काष्ठा i2c_client	*thermostat;
	काष्ठा i2c_client	*fan;

	पूर्णांक			overheat_temp;		/* 100% fan at this temp */
	पूर्णांक			overheat_hyst;
	पूर्णांक			temp;
	पूर्णांक			हालtemp;
	पूर्णांक			fan_level;		/* active fan_table setting */

	पूर्णांक			करोwnind;
	पूर्णांक			upind;

	पूर्णांक			r0, r1, r20, r23, r25;	/* saved रेजिस्टर */
पूर्ण x;

#घोषणा T(x,y)			(((x)<<8) | (y)*0x100/10 )

अटल काष्ठा अणु
	पूर्णांक			fan_करोwn_setting;
	पूर्णांक			temp;
	पूर्णांक			fan_up_setting;
पूर्ण fan_table[] = अणु
	अणु 11, T(0,0),  11 पूर्ण,	/* min fan */
	अणु 11, T(55,0), 11 पूर्ण,
	अणु  6, T(55,3), 11 पूर्ण,
	अणु  7, T(56,0), 11 पूर्ण,
	अणु  8, T(57,0), 8 पूर्ण,
	अणु  7, T(58,3), 7 पूर्ण,
	अणु  6, T(58,8), 6 पूर्ण,
	अणु  5, T(59,2), 5 पूर्ण,
	अणु  4, T(59,6), 4 पूर्ण,
	अणु  3, T(59,9), 3 पूर्ण,
	अणु  2, T(60,1), 2 पूर्ण,
	अणु  1, 0xfffff, 1 पूर्ण	/* on fire */
पूर्ण;

अटल व्योम
prपूर्णांक_temp( स्थिर अक्षर *s, पूर्णांक temp )
अणु
	prपूर्णांकk("%s%d.%d C", s ? s : "", temp>>8, (temp & 255)*10/256 );
पूर्ण

अटल sमाप_प्रकार
show_cpu_temperature( काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf )
अणु
	वापस प्र_लिखो(buf, "%d.%d\n", x.temp>>8, (x.temp & 255)*10/256 );
पूर्ण

अटल sमाप_प्रकार
show_हाल_temperature( काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf )
अणु
	वापस प्र_लिखो(buf, "%d.%d\n", x.हालtemp>>8, (x.हालtemp & 255)*10/256 );
पूर्ण

अटल DEVICE_ATTR(cpu_temperature, S_IRUGO, show_cpu_temperature, शून्य );
अटल DEVICE_ATTR(हाल_temperature, S_IRUGO, show_हाल_temperature, शून्य );



/************************************************************************/
/*	controller thपढ़ो						*/
/************************************************************************/

अटल पूर्णांक
ग_लिखो_reg( काष्ठा i2c_client *cl, पूर्णांक reg, पूर्णांक data, पूर्णांक len )
अणु
	u8 पंचांगp[3];

	अगर( len < 1 || len > 2 || data < 0 )
		वापस -EINVAL;

	पंचांगp[0] = reg;
	पंचांगp[1] = (len == 1) ? data : (data >> 8);
	पंचांगp[2] = data;
	len++;
	
	अगर( i2c_master_send(cl, पंचांगp, len) != len )
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल पूर्णांक
पढ़ो_reg( काष्ठा i2c_client *cl, पूर्णांक reg, पूर्णांक len )
अणु
	u8 buf[2];

	अगर( len != 1 && len != 2 )
		वापस -EINVAL;
	buf[0] = reg;
	अगर( i2c_master_send(cl, buf, 1) != 1 )
		वापस -ENODEV;
	अगर( i2c_master_recv(cl, buf, len) != len )
		वापस -ENODEV;
	वापस (len == 2)? ((अचिन्हित पूर्णांक)buf[0] << 8) | buf[1] : buf[0];
पूर्ण

अटल व्योम
tune_fan( पूर्णांक fan_setting )
अणु
	पूर्णांक val = (fan_setting << 3) | 7;

	/* ग_लिखो_reg( x.fan, 0x24, val, 1 ); */
	ग_लिखो_reg( x.fan, 0x25, val, 1 );
	ग_लिखो_reg( x.fan, 0x20, 0, 1 );
	prपूर्णांक_temp("CPU-temp: ", x.temp );
	अगर( x.हालtemp )
		prपूर्णांक_temp(", Case: ", x.हालtemp );
	prपूर्णांकk(",  Fan: %d (tuned %+d)\n", 11-fan_setting, x.fan_level-fan_setting );

	x.fan_level = fan_setting;
पूर्ण

अटल व्योम
poll_temp( व्योम )
अणु
	पूर्णांक temp, i, level, हालtemp;

	temp = पढ़ो_reg( x.thermostat, 0, 2 );

	/* this actually occurs when the computer is loaded */
	अगर( temp < 0 )
		वापस;

	हालtemp = पढ़ो_reg(x.fan, 0x0b, 1) << 8;
	हालtemp |= (पढ़ो_reg(x.fan, 0x06, 1) & 0x7) << 5;

	अगर( LOG_TEMP && x.temp != temp ) अणु
		prपूर्णांक_temp("CPU-temp: ", temp );
		prपूर्णांक_temp(", Case: ", हालtemp );
		prपूर्णांकk(",  Fan: %d\n", 11-x.fan_level );
	पूर्ण
	x.temp = temp;
	x.हालtemp = हालtemp;

	level = -1;
	क्रम( i=0; (temp & 0xffff) > fan_table[i].temp ; i++ )
		;
	अगर( i < x.करोwnind )
		level = fan_table[i].fan_करोwn_setting;
	x.करोwnind = i;

	क्रम( i=0; (temp & 0xffff) >= fan_table[i+1].temp ; i++ )
		;
	अगर( x.upind < i )
		level = fan_table[i].fan_up_setting;
	x.upind = i;

	अगर( level >= 0 )
		tune_fan( level );
पूर्ण


अटल व्योम
setup_hardware( व्योम )
अणु
	पूर्णांक val;
	पूर्णांक err;

	/* save रेजिस्टरs (अगर we unload the module) */
	x.r0 = पढ़ो_reg( x.fan, 0x00, 1 );
	x.r1 = पढ़ो_reg( x.fan, 0x01, 1 );
	x.r20 = पढ़ो_reg( x.fan, 0x20, 1 );
	x.r23 = पढ़ो_reg( x.fan, 0x23, 1 );
	x.r25 = पढ़ो_reg( x.fan, 0x25, 1 );

	/* improve measurement resolution (convergence समय 1.5s) */
	अगर( (val=पढ़ो_reg(x.thermostat, 1, 1)) >= 0 ) अणु
		val |= 0x60;
		अगर( ग_लिखो_reg( x.thermostat, 1, val, 1 ) )
			prपूर्णांकk("Failed writing config register\n");
	पूर्ण
	/* disable पूर्णांकerrupts and TAC input */
	ग_लिखो_reg( x.fan, 0x01, 0x01, 1 );
	/* enable filter */
	ग_लिखो_reg( x.fan, 0x23, 0x91, 1 );
	/* remote temp. controls fan */
	ग_लिखो_reg( x.fan, 0x00, 0x95, 1 );

	/* The thermostat (which besides measureing temperature controls
	 * has a THERM output which माला_दो the fan on 100%) is usually
	 * set to kick in at 80 C (chip शेष). We reduce this a bit
	 * to be on the safe side (OSX करोesn't)...
	 */
	अगर( x.overheat_temp == (80 << 8) ) अणु
		x.overheat_temp = 75 << 8;
		x.overheat_hyst = 70 << 8;
		ग_लिखो_reg( x.thermostat, 2, x.overheat_hyst, 2 );
		ग_लिखो_reg( x.thermostat, 3, x.overheat_temp, 2 );

		prपूर्णांक_temp("Reducing overheating limit to ", x.overheat_temp );
		prपूर्णांक_temp(" (Hyst: ", x.overheat_hyst );
		prपूर्णांकk(")\n");
	पूर्ण

	/* set an initial fan setting */
	x.करोwnind = 0xffff;
	x.upind = -1;
	/* tune_fan( fan_up_table[x.upind].fan_setting ); */

	err = device_create_file( &x.of_dev->dev, &dev_attr_cpu_temperature );
	err |= device_create_file( &x.of_dev->dev, &dev_attr_हाल_temperature );
	अगर (err)
		prपूर्णांकk(KERN_WARNING
			"Failed to create temperature attribute file(s).\n");
पूर्ण

अटल व्योम
restore_regs( व्योम )
अणु
	device_हटाओ_file( &x.of_dev->dev, &dev_attr_cpu_temperature );
	device_हटाओ_file( &x.of_dev->dev, &dev_attr_हाल_temperature );

	ग_लिखो_reg( x.fan, 0x01, x.r1, 1 );
	ग_लिखो_reg( x.fan, 0x20, x.r20, 1 );
	ग_लिखो_reg( x.fan, 0x23, x.r23, 1 );
	ग_लिखो_reg( x.fan, 0x25, x.r25, 1 );
	ग_लिखो_reg( x.fan, 0x00, x.r0, 1 );
पूर्ण

अटल पूर्णांक control_loop(व्योम *dummy)
अणु
	mutex_lock(&x.lock);
	setup_hardware();
	mutex_unlock(&x.lock);

	क्रम (;;) अणु
		msleep_पूर्णांकerruptible(8000);
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		mutex_lock(&x.lock);
		poll_temp();
		mutex_unlock(&x.lock);
	पूर्ण

	mutex_lock(&x.lock);
	restore_regs();
	mutex_unlock(&x.lock);

	वापस 0;
पूर्ण


/************************************************************************/
/*	i2c probing and setup						*/
/************************************************************************/

अटल व्योम करो_attach(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा i2c_board_info info = अणु पूर्ण;
	काष्ठा device_node *np;

	/* scan 0x48-0x4f (DS1775) and 0x2c-2x2f (ADM1030) */
	अटल स्थिर अचिन्हित लघु scan_ds1775[] = अणु
		0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
		I2C_CLIENT_END
	पूर्ण;
	अटल स्थिर अचिन्हित लघु scan_adm1030[] = अणु
		0x2c, 0x2d, 0x2e, 0x2f,
		I2C_CLIENT_END
	पूर्ण;

	अगर (x.running || म_भेदन(adapter->name, "uni-n", 5))
		वापस;

	np = of_find_compatible_node(adapter->dev.of_node, शून्य, "MAC,ds1775");
	अगर (np) अणु
		of_node_put(np);
	पूर्ण अन्यथा अणु
		strlcpy(info.type, "MAC,ds1775", I2C_NAME_SIZE);
		i2c_new_scanned_device(adapter, &info, scan_ds1775, शून्य);
	पूर्ण

	np = of_find_compatible_node(adapter->dev.of_node, शून्य, "MAC,adm1030");
	अगर (np) अणु
		of_node_put(np);
	पूर्ण अन्यथा अणु
		strlcpy(info.type, "MAC,adm1030", I2C_NAME_SIZE);
		i2c_new_scanned_device(adapter, &info, scan_adm1030, शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक
करो_हटाओ(काष्ठा i2c_client *client)
अणु
	अगर (x.running) अणु
		x.running = 0;
		kthपढ़ो_stop(x.poll_task);
		x.poll_task = शून्य;
	पूर्ण
	अगर (client == x.thermostat)
		x.thermostat = शून्य;
	अन्यथा अगर (client == x.fan)
		x.fan = शून्य;
	अन्यथा
		prपूर्णांकk(KERN_ERR "g4fan: bad client\n");

	वापस 0;
पूर्ण

अटल पूर्णांक
attach_fan( काष्ठा i2c_client *cl )
अणु
	अगर( x.fan )
		जाओ out;

	/* check that this is an ADM1030 */
	अगर( पढ़ो_reg(cl, 0x3d, 1) != 0x30 || पढ़ो_reg(cl, 0x3e, 1) != 0x41 )
		जाओ out;
	prपूर्णांकk("ADM1030 fan controller [@%02x]\n", cl->addr );

	x.fan = cl;
 out:
	वापस 0;
पूर्ण

अटल पूर्णांक
attach_thermostat( काष्ठा i2c_client *cl ) 
अणु
	पूर्णांक hyst_temp, os_temp, temp;

	अगर( x.thermostat )
		जाओ out;

	अगर( (temp=पढ़ो_reg(cl, 0, 2)) < 0 )
		जाओ out;
	
	/* temperature sanity check */
	अगर( temp < 0x1600 || temp > 0x3c00 )
		जाओ out;
	hyst_temp = पढ़ो_reg(cl, 2, 2);
	os_temp = पढ़ो_reg(cl, 3, 2);
	अगर( hyst_temp < 0 || os_temp < 0 )
		जाओ out;

	prपूर्णांकk("DS1775 digital thermometer [@%02x]\n", cl->addr );
	prपूर्णांक_temp("Temp: ", temp );
	prपूर्णांक_temp("  Hyst: ", hyst_temp );
	prपूर्णांक_temp("  OS: ", os_temp );
	prपूर्णांकk("\n");

	x.temp = temp;
	x.overheat_temp = os_temp;
	x.overheat_hyst = hyst_temp;
	x.thermostat = cl;
out:
	वापस 0;
पूर्ण

क्रमागत chip अणु ds1775, adm1030 पूर्ण;

अटल स्थिर काष्ठा i2c_device_id therm_windtunnel_id[] = अणु
	अणु "MAC,ds1775", ds1775 पूर्ण,
	अणु "MAC,adm1030", adm1030 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, therm_windtunnel_id);

अटल पूर्णांक
करो_probe(काष्ठा i2c_client *cl, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = cl->adapter;
	पूर्णांक ret = 0;

	अगर( !i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA
				     | I2C_FUNC_SMBUS_WRITE_BYTE) )
		वापस 0;

	चयन (id->driver_data) अणु
	हाल adm1030:
		ret = attach_fan(cl);
		अवरोध;
	हाल ds1775:
		ret = attach_thermostat(cl);
		अवरोध;
	पूर्ण

	अगर (!x.running && x.thermostat && x.fan) अणु
		x.running = 1;
		x.poll_task = kthपढ़ो_run(control_loop, शून्य, "g4fand");
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा i2c_driver g4fan_driver = अणु
	.driver = अणु
		.name	= "therm_windtunnel",
	पूर्ण,
	.probe		= करो_probe,
	.हटाओ		= करो_हटाओ,
	.id_table	= therm_windtunnel_id,
पूर्ण;


/************************************************************************/
/*	initialization / cleanup					*/
/************************************************************************/

अटल पूर्णांक therm_of_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा i2c_adapter *adap;
	पूर्णांक ret, i = 0;

	adap = i2c_get_adapter(0);
	अगर (!adap)
		वापस -EPROBE_DEFER;

	ret = i2c_add_driver(&g4fan_driver);
	अगर (ret) अणु
		i2c_put_adapter(adap);
		वापस ret;
	पूर्ण

	/* We assume Macs have consecutive I2C bus numbers starting at 0 */
	जबतक (adap) अणु
		करो_attach(adap);
		अगर (x.running)
			वापस 0;
		i2c_put_adapter(adap);
		adap = i2c_get_adapter(++i);
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
therm_of_हटाओ( काष्ठा platक्रमm_device *dev )
अणु
	i2c_del_driver( &g4fan_driver );
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id therm_of_match[] = अणुअणु
	.name		= "fan",
	.compatible	= "adm1030"
    पूर्ण, अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, therm_of_match);

अटल काष्ठा platक्रमm_driver therm_of_driver = अणु
	.driver = अणु
		.name = "temperature",
		.of_match_table = therm_of_match,
	पूर्ण,
	.probe		= therm_of_probe,
	.हटाओ		= therm_of_हटाओ,
पूर्ण;

काष्ठा apple_thermal_info अणु
	u8		id;			/* implementation ID */
	u8		fan_count;		/* number of fans */
	u8		thermostat_count;	/* number of thermostats */
	u8		unused;
पूर्ण;

अटल पूर्णांक __init
g4fan_init( व्योम )
अणु
	स्थिर काष्ठा apple_thermal_info *info;
	काष्ठा device_node *np;

	mutex_init(&x.lock);

	अगर( !(np=of_find_node_by_name(शून्य, "power-mgt")) )
		वापस -ENODEV;
	info = of_get_property(np, "thermal-info", शून्य);
	of_node_put(np);

	अगर( !info || !of_machine_is_compatible("PowerMac3,6") )
		वापस -ENODEV;

	अगर( info->id != 3 ) अणु
		prपूर्णांकk(KERN_ERR "therm_windtunnel: unsupported thermal design %d\n", info->id );
		वापस -ENODEV;
	पूर्ण
	अगर( !(np=of_find_node_by_name(शून्य, "fan")) )
		वापस -ENODEV;
	x.of_dev = of_platक्रमm_device_create(np, "temperature", शून्य);
	of_node_put( np );

	अगर( !x.of_dev ) अणु
		prपूर्णांकk(KERN_ERR "Can't register fan controller!\n");
		वापस -ENODEV;
	पूर्ण

	platक्रमm_driver_रेजिस्टर( &therm_of_driver );
	वापस 0;
पूर्ण

अटल व्योम __निकास
g4fan_निकास( व्योम )
अणु
	platक्रमm_driver_unरेजिस्टर( &therm_of_driver );

	अगर( x.of_dev )
		of_device_unरेजिस्टर( x.of_dev );
पूर्ण

module_init(g4fan_init);
module_निकास(g4fan_निकास);

MODULE_AUTHOR("Samuel Rydh <samuel@ibrium.se>");
MODULE_DESCRIPTION("Apple G4 (windtunnel) fan controller");
MODULE_LICENSE("GPL");
