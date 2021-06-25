<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *   Copyright (C) 2000 Tilmann Bitterberg
 *   (tilmann@bitterberg.de)
 *
 *   RTAS (Runसमय Abstraction Services) stuff
 *   Intention is to provide a clean user पूर्णांकerface
 *   to use the RTAS.
 *
 *   TODO:
 *   Split off a header file and maybe move it to a dअगरferent
 *   location. Write Documentation on what the /proc/rtas/ entries
 *   actually करो.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/समय.स>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/bitops.h>
#समावेश <linux/rtc.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/machdep.h> /* क्रम ppc_md */
#समावेश <यंत्र/समय.स>

/* Token क्रम Sensors */
#घोषणा KEY_SWITCH		0x0001
#घोषणा ENCLOSURE_SWITCH	0x0002
#घोषणा THERMAL_SENSOR		0x0003
#घोषणा LID_STATUS		0x0004
#घोषणा POWER_SOURCE		0x0005
#घोषणा BATTERY_VOLTAGE		0x0006
#घोषणा BATTERY_REMAINING	0x0007
#घोषणा BATTERY_PERCENTAGE	0x0008
#घोषणा EPOW_SENSOR		0x0009
#घोषणा BATTERY_CYCLESTATE	0x000a
#घोषणा BATTERY_CHARGING	0x000b

/* IBM specअगरic sensors */
#घोषणा IBM_SURVEILLANCE	0x2328 /* 9000 */
#घोषणा IBM_FANRPM		0x2329 /* 9001 */
#घोषणा IBM_VOLTAGE		0x232a /* 9002 */
#घोषणा IBM_DRCONNECTOR		0x232b /* 9003 */
#घोषणा IBM_POWERSUPPLY		0x232c /* 9004 */

/* Status वापस values */
#घोषणा SENSOR_CRITICAL_HIGH	13
#घोषणा SENSOR_WARNING_HIGH	12
#घोषणा SENSOR_NORMAL		11
#घोषणा SENSOR_WARNING_LOW	10
#घोषणा SENSOR_CRITICAL_LOW	 9
#घोषणा SENSOR_SUCCESS		 0
#घोषणा SENSOR_HW_ERROR		-1
#घोषणा SENSOR_BUSY		-2
#घोषणा SENSOR_NOT_EXIST	-3
#घोषणा SENSOR_DR_ENTITY	-9000

/* Location Codes */
#घोषणा LOC_SCSI_DEV_ADDR	'A'
#घोषणा LOC_SCSI_DEV_LOC	'B'
#घोषणा LOC_CPU			'C'
#घोषणा LOC_DISKETTE		'D'
#घोषणा LOC_ETHERNET		'E'
#घोषणा LOC_FAN			'F'
#घोषणा LOC_GRAPHICS		'G'
/* reserved / not used		'H' */
#घोषणा LOC_IO_ADAPTER		'I'
/* reserved / not used		'J' */
#घोषणा LOC_KEYBOARD		'K'
#घोषणा LOC_LCD			'L'
#घोषणा LOC_MEMORY		'M'
#घोषणा LOC_NV_MEMORY		'N'
#घोषणा LOC_MOUSE		'O'
#घोषणा LOC_PLANAR		'P'
#घोषणा LOC_OTHER_IO		'Q'
#घोषणा LOC_PARALLEL		'R'
#घोषणा LOC_SERIAL		'S'
#घोषणा LOC_DEAD_RING		'T'
#घोषणा LOC_RACKMOUNTED		'U' /* क्रम _u_nit is rack mounted */
#घोषणा LOC_VOLTAGE		'V'
#घोषणा LOC_SWITCH_ADAPTER	'W'
#घोषणा LOC_OTHER		'X'
#घोषणा LOC_FIRMWARE		'Y'
#घोषणा LOC_SCSI		'Z'

/* Tokens क्रम indicators */
#घोषणा TONE_FREQUENCY		0x0001 /* 0 - 1000 (HZ)*/
#घोषणा TONE_VOLUME		0x0002 /* 0 - 100 (%) */
#घोषणा SYSTEM_POWER_STATE	0x0003 
#घोषणा WARNING_LIGHT		0x0004
#घोषणा DISK_ACTIVITY_LIGHT	0x0005
#घोषणा HEX_DISPLAY_UNIT	0x0006
#घोषणा BATTERY_WARNING_TIME	0x0007
#घोषणा CONDITION_CYCLE_REQUEST	0x0008
#घोषणा SURVEILLANCE_INDICATOR	0x2328 /* 9000 */
#घोषणा DR_ACTION		0x2329 /* 9001 */
#घोषणा DR_INDICATOR		0x232a /* 9002 */
/* 9003 - 9004: Venकरोr specअगरic */
/* 9006 - 9999: Venकरोr specअगरic */

/* other */
#घोषणा MAX_SENSORS		 17  /* I only know of 17 sensors */    
#घोषणा MAX_LINELENGTH          256
#घोषणा SENSOR_PREFIX		"ibm,sensor-"
#घोषणा cel_to_fahr(x)		((x*9/5)+32)

काष्ठा inभागidual_sensor अणु
	अचिन्हित पूर्णांक token;
	अचिन्हित पूर्णांक quant;
पूर्ण;

काष्ठा rtas_sensors अणु
        काष्ठा inभागidual_sensor sensor[MAX_SENSORS];
	अचिन्हित पूर्णांक quant;
पूर्ण;

/* Globals */
अटल काष्ठा rtas_sensors sensors;
अटल काष्ठा device_node *rtas_node = शून्य;
अटल अचिन्हित दीर्घ घातer_on_समय = 0; /* Save the समय the user set */
अटल अक्षर progress_led[MAX_LINELENGTH];

अटल अचिन्हित दीर्घ rtas_tone_frequency = 1000;
अटल अचिन्हित दीर्घ rtas_tone_volume = 0;

/* ****************************************************************** */
/* Declarations */
अटल पूर्णांक ppc_rtas_sensors_show(काष्ठा seq_file *m, व्योम *v);
अटल पूर्णांक ppc_rtas_घड़ी_show(काष्ठा seq_file *m, व्योम *v);
अटल sमाप_प्रकार ppc_rtas_घड़ी_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos);
अटल पूर्णांक ppc_rtas_progress_show(काष्ठा seq_file *m, व्योम *v);
अटल sमाप_प्रकार ppc_rtas_progress_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos);
अटल पूर्णांक ppc_rtas_घातeron_show(काष्ठा seq_file *m, व्योम *v);
अटल sमाप_प्रकार ppc_rtas_घातeron_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos);

अटल sमाप_प्रकार ppc_rtas_tone_freq_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos);
अटल पूर्णांक ppc_rtas_tone_freq_show(काष्ठा seq_file *m, व्योम *v);
अटल sमाप_प्रकार ppc_rtas_tone_volume_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos);
अटल पूर्णांक ppc_rtas_tone_volume_show(काष्ठा seq_file *m, व्योम *v);
अटल पूर्णांक ppc_rtas_rmo_buf_show(काष्ठा seq_file *m, व्योम *v);

अटल पूर्णांक घातeron_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ppc_rtas_घातeron_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा proc_ops ppc_rtas_घातeron_proc_ops = अणु
	.proc_खोलो	= घातeron_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= ppc_rtas_घातeron_ग_लिखो,
	.proc_release	= single_release,
पूर्ण;

अटल पूर्णांक progress_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ppc_rtas_progress_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा proc_ops ppc_rtas_progress_proc_ops = अणु
	.proc_खोलो	= progress_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= ppc_rtas_progress_ग_लिखो,
	.proc_release	= single_release,
पूर्ण;

अटल पूर्णांक घड़ी_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ppc_rtas_घड़ी_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा proc_ops ppc_rtas_घड़ी_proc_ops = अणु
	.proc_खोलो	= घड़ी_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= ppc_rtas_घड़ी_ग_लिखो,
	.proc_release	= single_release,
पूर्ण;

अटल पूर्णांक tone_freq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ppc_rtas_tone_freq_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा proc_ops ppc_rtas_tone_freq_proc_ops = अणु
	.proc_खोलो	= tone_freq_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= ppc_rtas_tone_freq_ग_लिखो,
	.proc_release	= single_release,
पूर्ण;

अटल पूर्णांक tone_volume_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ppc_rtas_tone_volume_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा proc_ops ppc_rtas_tone_volume_proc_ops = अणु
	.proc_खोलो	= tone_volume_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= ppc_rtas_tone_volume_ग_लिखो,
	.proc_release	= single_release,
पूर्ण;

अटल पूर्णांक ppc_rtas_find_all_sensors(व्योम);
अटल व्योम ppc_rtas_process_sensor(काष्ठा seq_file *m,
	काष्ठा inभागidual_sensor *s, पूर्णांक state, पूर्णांक error, स्थिर अक्षर *loc);
अटल अक्षर *ppc_rtas_process_error(पूर्णांक error);
अटल व्योम get_location_code(काष्ठा seq_file *m,
	काष्ठा inभागidual_sensor *s, स्थिर अक्षर *loc);
अटल व्योम check_location_string(काष्ठा seq_file *m, स्थिर अक्षर *c);
अटल व्योम check_location(काष्ठा seq_file *m, स्थिर अक्षर *c);

अटल पूर्णांक __init proc_rtas_init(व्योम)
अणु
	अगर (!machine_is(pseries))
		वापस -ENODEV;

	rtas_node = of_find_node_by_name(शून्य, "rtas");
	अगर (rtas_node == शून्य)
		वापस -ENODEV;

	proc_create("powerpc/rtas/progress", 0644, शून्य,
		    &ppc_rtas_progress_proc_ops);
	proc_create("powerpc/rtas/clock", 0644, शून्य,
		    &ppc_rtas_घड़ी_proc_ops);
	proc_create("powerpc/rtas/poweron", 0644, शून्य,
		    &ppc_rtas_घातeron_proc_ops);
	proc_create_single("powerpc/rtas/sensors", 0444, शून्य,
			ppc_rtas_sensors_show);
	proc_create("powerpc/rtas/frequency", 0644, शून्य,
		    &ppc_rtas_tone_freq_proc_ops);
	proc_create("powerpc/rtas/volume", 0644, शून्य,
		    &ppc_rtas_tone_volume_proc_ops);
	proc_create_single("powerpc/rtas/rmo_buffer", 0400, शून्य,
			ppc_rtas_rmo_buf_show);
	वापस 0;
पूर्ण

__initcall(proc_rtas_init);

अटल पूर्णांक parse_number(स्थिर अक्षर __user *p, माप_प्रकार count, u64 *val)
अणु
	अक्षर buf[40];
	अक्षर *end;

	अगर (count > 39)
		वापस -EINVAL;

	अगर (copy_from_user(buf, p, count))
		वापस -EFAULT;

	buf[count] = 0;

	*val = simple_म_से_अदीर्घl(buf, &end, 10);
	अगर (*end && *end != '\n')
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* ****************************************************************** */
/* POWER-ON-TIME                                                      */
/* ****************************************************************** */
अटल sमाप_प्रकार ppc_rtas_घातeron_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा rtc_समय पंचांग;
	समय64_t nowसमय;
	पूर्णांक error = parse_number(buf, count, &nowसमय);
	अगर (error)
		वापस error;

	घातer_on_समय = nowसमय; /* save the समय */

	rtc_समय64_to_पंचांग(nowसमय, &पंचांग);

	error = rtas_call(rtas_token("set-time-for-power-on"), 7, 1, शून्य, 
			पंचांग.पंचांग_year + 1900, पंचांग.पंचांग_mon + 1, पंचांग.पंचांग_mday,
			पंचांग.पंचांग_hour, पंचांग.पंचांग_min, पंचांग.पंचांग_sec, 0 /* nano */);
	अगर (error)
		prपूर्णांकk(KERN_WARNING "error: setting poweron time returned: %s\n", 
				ppc_rtas_process_error(error));
	वापस count;
पूर्ण
/* ****************************************************************** */
अटल पूर्णांक ppc_rtas_घातeron_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अगर (घातer_on_समय == 0)
		seq_म_लिखो(m, "Power on time not set\n");
	अन्यथा
		seq_म_लिखो(m, "%lu\n",घातer_on_समय);
	वापस 0;
पूर्ण

/* ****************************************************************** */
/* PROGRESS                                                           */
/* ****************************************************************** */
अटल sमाप_प्रकार ppc_rtas_progress_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ hex;

	अगर (count >= MAX_LINELENGTH)
		count = MAX_LINELENGTH -1;
	अगर (copy_from_user(progress_led, buf, count)) अणु /* save the string */
		वापस -EFAULT;
	पूर्ण
	progress_led[count] = 0;

	/* Lets see अगर the user passed hexdigits */
	hex = simple_म_से_अदीर्घ(progress_led, शून्य, 10);

	rtas_progress ((अक्षर *)progress_led, hex);
	वापस count;

	/* clear the line */
	/* rtas_progress("                   ", 0xffff);*/
पूर्ण
/* ****************************************************************** */
अटल पूर्णांक ppc_rtas_progress_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अगर (progress_led[0])
		seq_म_लिखो(m, "%s\n", progress_led);
	वापस 0;
पूर्ण

/* ****************************************************************** */
/* CLOCK                                                              */
/* ****************************************************************** */
अटल sमाप_प्रकार ppc_rtas_घड़ी_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा rtc_समय पंचांग;
	समय64_t nowसमय;
	पूर्णांक error = parse_number(buf, count, &nowसमय);
	अगर (error)
		वापस error;

	rtc_समय64_to_पंचांग(nowसमय, &पंचांग);
	error = rtas_call(rtas_token("set-time-of-day"), 7, 1, शून्य, 
			पंचांग.पंचांग_year + 1900, पंचांग.पंचांग_mon + 1, पंचांग.पंचांग_mday,
			पंचांग.पंचांग_hour, पंचांग.पंचांग_min, पंचांग.पंचांग_sec, 0);
	अगर (error)
		prपूर्णांकk(KERN_WARNING "error: setting the clock returned: %s\n", 
				ppc_rtas_process_error(error));
	वापस count;
पूर्ण
/* ****************************************************************** */
अटल पूर्णांक ppc_rtas_घड़ी_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक ret[8];
	पूर्णांक error = rtas_call(rtas_token("get-time-of-day"), 0, 8, ret);

	अगर (error) अणु
		prपूर्णांकk(KERN_WARNING "error: reading the clock returned: %s\n", 
				ppc_rtas_process_error(error));
		seq_म_लिखो(m, "0");
	पूर्ण अन्यथा अणु 
		अचिन्हित पूर्णांक year, mon, day, hour, min, sec;
		year = ret[0]; mon  = ret[1]; day  = ret[2];
		hour = ret[3]; min  = ret[4]; sec  = ret[5];
		seq_म_लिखो(m, "%lld\n",
				स_गढ़ो64(year, mon, day, hour, min, sec));
	पूर्ण
	वापस 0;
पूर्ण

/* ****************************************************************** */
/* SENSOR STUFF                                                       */
/* ****************************************************************** */
अटल पूर्णांक ppc_rtas_sensors_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i,j;
	पूर्णांक state, error;
	पूर्णांक get_sensor_state = rtas_token("get-sensor-state");

	seq_म_लिखो(m, "RTAS (RunTime Abstraction Services) Sensor Information\n");
	seq_म_लिखो(m, "Sensor\t\tValue\t\tCondition\tLocation\n");
	seq_म_लिखो(m, "********************************************************\n");

	अगर (ppc_rtas_find_all_sensors() != 0) अणु
		seq_म_लिखो(m, "\nNo sensors are available\n");
		वापस 0;
	पूर्ण

	क्रम (i=0; i<sensors.quant; i++) अणु
		काष्ठा inभागidual_sensor *p = &sensors.sensor[i];
		अक्षर rstr[64];
		स्थिर अक्षर *loc;
		पूर्णांक llen, offs;

		प्र_लिखो (rstr, SENSOR_PREFIX"%04d", p->token);
		loc = of_get_property(rtas_node, rstr, &llen);

		/* A sensor may have multiple instances */
		क्रम (j = 0, offs = 0; j <= p->quant; j++) अणु
			error =	rtas_call(get_sensor_state, 2, 2, &state, 
				  	  p->token, j);

			ppc_rtas_process_sensor(m, p, state, error, loc);
			seq_अ_दो(m, '\n');
			अगर (loc) अणु
				offs += म_माप(loc) + 1;
				loc += म_माप(loc) + 1;
				अगर (offs >= llen)
					loc = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* ****************************************************************** */

अटल पूर्णांक ppc_rtas_find_all_sensors(व्योम)
अणु
	स्थिर अचिन्हित पूर्णांक *uपंचांगp;
	पूर्णांक len, i;

	uपंचांगp = of_get_property(rtas_node, "rtas-sensors", &len);
	अगर (uपंचांगp == शून्य) अणु
		prपूर्णांकk (KERN_ERR "error: could not get rtas-sensors\n");
		वापस 1;
	पूर्ण

	sensors.quant = len / 8;      /* पूर्णांक + पूर्णांक */

	क्रम (i=0; i<sensors.quant; i++) अणु
		sensors.sensor[i].token = *uपंचांगp++;
		sensors.sensor[i].quant = *uपंचांगp++;
	पूर्ण
	वापस 0;
पूर्ण

/* ****************************************************************** */
/*
 * Builds a string of what rtas वापसed
 */
अटल अक्षर *ppc_rtas_process_error(पूर्णांक error)
अणु
	चयन (error) अणु
		हाल SENSOR_CRITICAL_HIGH:
			वापस "(critical high)";
		हाल SENSOR_WARNING_HIGH:
			वापस "(warning high)";
		हाल SENSOR_NORMAL:
			वापस "(normal)";
		हाल SENSOR_WARNING_LOW:
			वापस "(warning low)";
		हाल SENSOR_CRITICAL_LOW:
			वापस "(critical low)";
		हाल SENSOR_SUCCESS:
			वापस "(read ok)";
		हाल SENSOR_HW_ERROR:
			वापस "(hardware error)";
		हाल SENSOR_BUSY:
			वापस "(busy)";
		हाल SENSOR_NOT_EXIST:
			वापस "(non existent)";
		हाल SENSOR_DR_ENTITY:
			वापस "(dr entity removed)";
		शेष:
			वापस "(UNKNOWN)";
	पूर्ण
पूर्ण

/* ****************************************************************** */
/*
 * Builds a string out of what the sensor said
 */

अटल व्योम ppc_rtas_process_sensor(काष्ठा seq_file *m,
	काष्ठा inभागidual_sensor *s, पूर्णांक state, पूर्णांक error, स्थिर अक्षर *loc)
अणु
	/* Defined वापस vales */
	स्थिर अक्षर * key_चयन[]        = अणु "Off\t", "Normal\t", "Secure\t", 
						"Maintenance" पूर्ण;
	स्थिर अक्षर * enclosure_चयन[]  = अणु "Closed", "Open" पूर्ण;
	स्थिर अक्षर * lid_status[]        = अणु " ", "Open", "Closed" पूर्ण;
	स्थिर अक्षर * घातer_source[]      = अणु "AC\t", "Battery", 
		  				"AC & Battery" पूर्ण;
	स्थिर अक्षर * battery_reमुख्यing[] = अणु "Very Low", "Low", "Mid", "High" पूर्ण;
	स्थिर अक्षर * eघात_sensor[]       = अणु 
		"EPOW Reset", "Cooling warning", "Power warning",
		"System shutdown", "System halt", "EPOW main enclosure",
		"EPOW power off" पूर्ण;
	स्थिर अक्षर * battery_cyclestate[]  = अणु "None", "In progress", 
						"Requested" पूर्ण;
	स्थिर अक्षर * battery_अक्षरging[]    = अणु "Charging", "Discharging",
						"No current flow" पूर्ण;
	स्थिर अक्षर * ibm_drconnector[]     = अणु "Empty", "Present", "Unusable", 
						"Exchange" पूर्ण;

	पूर्णांक have_strings = 0;
	पूर्णांक num_states = 0;
	पूर्णांक temperature = 0;
	पूर्णांक unknown = 0;

	/* What kind of sensor करो we have here? */
	
	चयन (s->token) अणु
		हाल KEY_SWITCH:
			seq_म_लिखो(m, "Key switch:\t");
			num_states = माप(key_चयन) / माप(अक्षर *);
			अगर (state < num_states) अणु
				seq_म_लिखो(m, "%s\t", key_चयन[state]);
				have_strings = 1;
			पूर्ण
			अवरोध;
		हाल ENCLOSURE_SWITCH:
			seq_म_लिखो(m, "Enclosure switch:\t");
			num_states = माप(enclosure_चयन) / माप(अक्षर *);
			अगर (state < num_states) अणु
				seq_म_लिखो(m, "%s\t", 
						enclosure_चयन[state]);
				have_strings = 1;
			पूर्ण
			अवरोध;
		हाल THERMAL_SENSOR:
			seq_म_लिखो(m, "Temp. (C/F):\t");
			temperature = 1;
			अवरोध;
		हाल LID_STATUS:
			seq_म_लिखो(m, "Lid status:\t");
			num_states = माप(lid_status) / माप(अक्षर *);
			अगर (state < num_states) अणु
				seq_म_लिखो(m, "%s\t", lid_status[state]);
				have_strings = 1;
			पूर्ण
			अवरोध;
		हाल POWER_SOURCE:
			seq_म_लिखो(m, "Power source:\t");
			num_states = माप(घातer_source) / माप(अक्षर *);
			अगर (state < num_states) अणु
				seq_म_लिखो(m, "%s\t", 
						घातer_source[state]);
				have_strings = 1;
			पूर्ण
			अवरोध;
		हाल BATTERY_VOLTAGE:
			seq_म_लिखो(m, "Battery voltage:\t");
			अवरोध;
		हाल BATTERY_REMAINING:
			seq_म_लिखो(m, "Battery remaining:\t");
			num_states = माप(battery_reमुख्यing) / माप(अक्षर *);
			अगर (state < num_states)
			अणु
				seq_म_लिखो(m, "%s\t", 
						battery_reमुख्यing[state]);
				have_strings = 1;
			पूर्ण
			अवरोध;
		हाल BATTERY_PERCENTAGE:
			seq_म_लिखो(m, "Battery percentage:\t");
			अवरोध;
		हाल EPOW_SENSOR:
			seq_म_लिखो(m, "EPOW Sensor:\t");
			num_states = माप(eघात_sensor) / माप(अक्षर *);
			अगर (state < num_states) अणु
				seq_म_लिखो(m, "%s\t", eघात_sensor[state]);
				have_strings = 1;
			पूर्ण
			अवरोध;
		हाल BATTERY_CYCLESTATE:
			seq_म_लिखो(m, "Battery cyclestate:\t");
			num_states = माप(battery_cyclestate) / 
				     	माप(अक्षर *);
			अगर (state < num_states) अणु
				seq_म_लिखो(m, "%s\t", 
						battery_cyclestate[state]);
				have_strings = 1;
			पूर्ण
			अवरोध;
		हाल BATTERY_CHARGING:
			seq_म_लिखो(m, "Battery Charging:\t");
			num_states = माप(battery_अक्षरging) / माप(अक्षर *);
			अगर (state < num_states) अणु
				seq_म_लिखो(m, "%s\t", 
						battery_अक्षरging[state]);
				have_strings = 1;
			पूर्ण
			अवरोध;
		हाल IBM_SURVEILLANCE:
			seq_म_लिखो(m, "Surveillance:\t");
			अवरोध;
		हाल IBM_FANRPM:
			seq_म_लिखो(m, "Fan (rpm):\t");
			अवरोध;
		हाल IBM_VOLTAGE:
			seq_म_लिखो(m, "Voltage (mv):\t");
			अवरोध;
		हाल IBM_DRCONNECTOR:
			seq_म_लिखो(m, "DR connector:\t");
			num_states = माप(ibm_drconnector) / माप(अक्षर *);
			अगर (state < num_states) अणु
				seq_म_लिखो(m, "%s\t", 
						ibm_drconnector[state]);
				have_strings = 1;
			पूर्ण
			अवरोध;
		हाल IBM_POWERSUPPLY:
			seq_म_लिखो(m, "Powersupply:\t");
			अवरोध;
		शेष:
			seq_म_लिखो(m,  "Unknown sensor (type %d), ignoring it\n",
					s->token);
			unknown = 1;
			have_strings = 1;
			अवरोध;
	पूर्ण
	अगर (have_strings == 0) अणु
		अगर (temperature) अणु
			seq_म_लिखो(m, "%4d /%4d\t", state, cel_to_fahr(state));
		पूर्ण अन्यथा
			seq_म_लिखो(m, "%10d\t", state);
	पूर्ण
	अगर (unknown == 0) अणु
		seq_म_लिखो(m, "%s\t", ppc_rtas_process_error(error));
		get_location_code(m, s, loc);
	पूर्ण
पूर्ण

/* ****************************************************************** */

अटल व्योम check_location(काष्ठा seq_file *m, स्थिर अक्षर *c)
अणु
	चयन (c[0]) अणु
		हाल LOC_PLANAR:
			seq_म_लिखो(m, "Planar #%c", c[1]);
			अवरोध;
		हाल LOC_CPU:
			seq_म_लिखो(m, "CPU #%c", c[1]);
			अवरोध;
		हाल LOC_FAN:
			seq_म_लिखो(m, "Fan #%c", c[1]);
			अवरोध;
		हाल LOC_RACKMOUNTED:
			seq_म_लिखो(m, "Rack #%c", c[1]);
			अवरोध;
		हाल LOC_VOLTAGE:
			seq_म_लिखो(m, "Voltage #%c", c[1]);
			अवरोध;
		हाल LOC_LCD:
			seq_म_लिखो(m, "LCD #%c", c[1]);
			अवरोध;
		हाल '.':
			seq_म_लिखो(m, "- %c", c[1]);
			अवरोध;
		शेष:
			seq_म_लिखो(m, "Unknown location");
			अवरोध;
	पूर्ण
पूर्ण


/* ****************************************************************** */
/* 
 * Format: 
 * $अणुLETTERपूर्ण$अणुNUMBERपूर्ण[[-/]$अणुLETTERपूर्ण$अणुNUMBERपूर्ण [ ... ] ]
 * the '.' may be an abbreviation
 */
अटल व्योम check_location_string(काष्ठा seq_file *m, स्थिर अक्षर *c)
अणु
	जबतक (*c) अणु
		अगर (है_अक्षर(*c) || *c == '.')
			check_location(m, c);
		अन्यथा अगर (*c == '/' || *c == '-')
			seq_म_लिखो(m, " at ");
		c++;
	पूर्ण
पूर्ण


/* ****************************************************************** */

अटल व्योम get_location_code(काष्ठा seq_file *m, काष्ठा inभागidual_sensor *s,
		स्थिर अक्षर *loc)
अणु
	अगर (!loc || !*loc) अणु
		seq_म_लिखो(m, "---");/* करोes not have a location */
	पूर्ण अन्यथा अणु
		check_location_string(m, loc);
	पूर्ण
	seq_अ_दो(m, ' ');
पूर्ण
/* ****************************************************************** */
/* INDICATORS - Tone Frequency                                        */
/* ****************************************************************** */
अटल sमाप_प्रकार ppc_rtas_tone_freq_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	u64 freq;
	पूर्णांक error = parse_number(buf, count, &freq);
	अगर (error)
		वापस error;

	rtas_tone_frequency = freq; /* save it क्रम later */
	error = rtas_call(rtas_token("set-indicator"), 3, 1, शून्य,
			TONE_FREQUENCY, 0, freq);
	अगर (error)
		prपूर्णांकk(KERN_WARNING "error: setting tone frequency returned: %s\n", 
				ppc_rtas_process_error(error));
	वापस count;
पूर्ण
/* ****************************************************************** */
अटल पूर्णांक ppc_rtas_tone_freq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "%lu\n", rtas_tone_frequency);
	वापस 0;
पूर्ण
/* ****************************************************************** */
/* INDICATORS - Tone Volume                                           */
/* ****************************************************************** */
अटल sमाप_प्रकार ppc_rtas_tone_volume_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	u64 volume;
	पूर्णांक error = parse_number(buf, count, &volume);
	अगर (error)
		वापस error;

	अगर (volume > 100)
		volume = 100;
	
        rtas_tone_volume = volume; /* save it क्रम later */
	error = rtas_call(rtas_token("set-indicator"), 3, 1, शून्य,
			TONE_VOLUME, 0, volume);
	अगर (error)
		prपूर्णांकk(KERN_WARNING "error: setting tone volume returned: %s\n", 
				ppc_rtas_process_error(error));
	वापस count;
पूर्ण
/* ****************************************************************** */
अटल पूर्णांक ppc_rtas_tone_volume_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "%lu\n", rtas_tone_volume);
	वापस 0;
पूर्ण

/**
 * ppc_rtas_rmo_buf_show() - Describe RTAS-addressable region क्रम user space.
 *
 * Base + size description of a range of RTAS-addressable memory set
 * aside क्रम user space to use as work area(s) क्रम certain RTAS
 * functions. User space accesses this region via /dev/mem. Apart from
 * security policies, the kernel करोes not arbitrate or serialize
 * access to this region, and user space must ensure that concurrent
 * users करो not पूर्णांकerfere with each other.
 */
अटल पूर्णांक ppc_rtas_rmo_buf_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "%016lx %x\n", rtas_rmo_buf, RTAS_USER_REGION_SIZE);
	वापस 0;
पूर्ण
