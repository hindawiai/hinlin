<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control.
 * Control loops क्रम PowerMac7,2 and 7,3
 *
 * Copyright (C) 2012 Benjamin Herrenschmidt, IBM Corp.
 */
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/smu.h>

#समावेश "windfarm.h"
#समावेश "windfarm_pid.h"
#समावेश "windfarm_mpu.h"

#घोषणा VERSION "1.0"

#अघोषित DEBUG
#अघोषित LOTSA_DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(args...)	prपूर्णांकk(args)
#अन्यथा
#घोषणा DBG(args...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#अगर_घोषित LOTSA_DEBUG
#घोषणा DBG_LOTS(args...)	prपूर्णांकk(args)
#अन्यथा
#घोषणा DBG_LOTS(args...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

/* define this to क्रमce CPU overtemp to 60 degree, useful क्रम testing
 * the overtemp code
 */
#अघोषित HACKED_OVERTEMP

/* We currently only handle 2 chips */
#घोषणा NR_CHIPS	2
#घोषणा NR_CPU_FANS	3 * NR_CHIPS

/* Controls and sensors */
अटल काष्ठा wf_sensor *sens_cpu_temp[NR_CHIPS];
अटल काष्ठा wf_sensor *sens_cpu_volts[NR_CHIPS];
अटल काष्ठा wf_sensor *sens_cpu_amps[NR_CHIPS];
अटल काष्ठा wf_sensor *backside_temp;
अटल काष्ठा wf_sensor *drives_temp;

अटल काष्ठा wf_control *cpu_front_fans[NR_CHIPS];
अटल काष्ठा wf_control *cpu_rear_fans[NR_CHIPS];
अटल काष्ठा wf_control *cpu_pumps[NR_CHIPS];
अटल काष्ठा wf_control *backside_fan;
अटल काष्ठा wf_control *drives_fan;
अटल काष्ठा wf_control *slots_fan;
अटल काष्ठा wf_control *cpufreq_clamp;

/* We keep a temperature history क्रम average calculation of 180s */
#घोषणा CPU_TEMP_HIST_SIZE	180

/* Fixed speed क्रम slot fan */
#घोषणा	SLOTS_FAN_DEFAULT_PWM	40

/* Scale value क्रम CPU पूर्णांकake fans */
#घोषणा CPU_INTAKE_SCALE	0x0000f852

/* PID loop state */
अटल स्थिर काष्ठा mpu_data *cpu_mpu_data[NR_CHIPS];
अटल काष्ठा wf_cpu_pid_state cpu_pid[NR_CHIPS];
अटल bool cpu_pid_combined;
अटल u32 cpu_thist[CPU_TEMP_HIST_SIZE];
अटल पूर्णांक cpu_thist_pt;
अटल s64 cpu_thist_total;
अटल s32 cpu_all_पंचांगax = 100 << 16;
अटल काष्ठा wf_pid_state backside_pid;
अटल पूर्णांक backside_tick;
अटल काष्ठा wf_pid_state drives_pid;
अटल पूर्णांक drives_tick;

अटल पूर्णांक nr_chips;
अटल bool have_all_controls;
अटल bool have_all_sensors;
अटल bool started;

अटल पूर्णांक failure_state;
#घोषणा FAILURE_SENSOR		1
#घोषणा FAILURE_FAN		2
#घोषणा FAILURE_PERM		4
#घोषणा FAILURE_LOW_OVERTEMP	8
#घोषणा FAILURE_HIGH_OVERTEMP	16

/* Overtemp values */
#घोषणा LOW_OVER_AVERAGE	0
#घोषणा LOW_OVER_IMMEDIATE	(10 << 16)
#घोषणा LOW_OVER_CLEAR		((-10) << 16)
#घोषणा HIGH_OVER_IMMEDIATE	(14 << 16)
#घोषणा HIGH_OVER_AVERAGE	(10 << 16)
#घोषणा HIGH_OVER_IMMEDIATE	(14 << 16)


अटल व्योम cpu_max_all_fans(व्योम)
अणु
	पूर्णांक i;

	/* We max all CPU fans in हाल of a sensor error. We also करो the
	 * cpufreq clamping now, even अगर it's supposedly करोne later by the
	 * generic code anyway, we करो it earlier here to react faster
	 */
	अगर (cpufreq_clamp)
		wf_control_set_max(cpufreq_clamp);
	क्रम (i = 0; i < nr_chips; i++) अणु
		अगर (cpu_front_fans[i])
			wf_control_set_max(cpu_front_fans[i]);
		अगर (cpu_rear_fans[i])
			wf_control_set_max(cpu_rear_fans[i]);
		अगर (cpu_pumps[i])
			wf_control_set_max(cpu_pumps[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक cpu_check_overtemp(s32 temp)
अणु
	पूर्णांक new_state = 0;
	s32 t_avg, t_old;
	अटल bool first = true;

	/* First check क्रम immediate overtemps */
	अगर (temp >= (cpu_all_पंचांगax + LOW_OVER_IMMEDIATE)) अणु
		new_state |= FAILURE_LOW_OVERTEMP;
		अगर ((failure_state & FAILURE_LOW_OVERTEMP) == 0)
			prपूर्णांकk(KERN_ERR "windfarm: Overtemp due to immediate CPU"
			       " temperature !\n");
	पूर्ण
	अगर (temp >= (cpu_all_पंचांगax + HIGH_OVER_IMMEDIATE)) अणु
		new_state |= FAILURE_HIGH_OVERTEMP;
		अगर ((failure_state & FAILURE_HIGH_OVERTEMP) == 0)
			prपूर्णांकk(KERN_ERR "windfarm: Critical overtemp due to"
			       " immediate CPU temperature !\n");
	पूर्ण

	/*
	 * The first समय around, initialize the array with the first
	 * temperature पढ़ोing
	 */
	अगर (first) अणु
		पूर्णांक i;

		cpu_thist_total = 0;
		क्रम (i = 0; i < CPU_TEMP_HIST_SIZE; i++) अणु
			cpu_thist[i] = temp;
			cpu_thist_total += temp;
		पूर्ण
		first = false;
	पूर्ण

	/*
	 * We calculate a history of max temperatures and use that क्रम the
	 * overtemp management
	 */
	t_old = cpu_thist[cpu_thist_pt];
	cpu_thist[cpu_thist_pt] = temp;
	cpu_thist_pt = (cpu_thist_pt + 1) % CPU_TEMP_HIST_SIZE;
	cpu_thist_total -= t_old;
	cpu_thist_total += temp;
	t_avg = cpu_thist_total / CPU_TEMP_HIST_SIZE;

	DBG_LOTS("  t_avg = %d.%03d (out: %d.%03d, in: %d.%03d)\n",
		 FIX32TOPRINT(t_avg), FIX32TOPRINT(t_old), FIX32TOPRINT(temp));

	/* Now check क्रम average overtemps */
	अगर (t_avg >= (cpu_all_पंचांगax + LOW_OVER_AVERAGE)) अणु
		new_state |= FAILURE_LOW_OVERTEMP;
		अगर ((failure_state & FAILURE_LOW_OVERTEMP) == 0)
			prपूर्णांकk(KERN_ERR "windfarm: Overtemp due to average CPU"
			       " temperature !\n");
	पूर्ण
	अगर (t_avg >= (cpu_all_पंचांगax + HIGH_OVER_AVERAGE)) अणु
		new_state |= FAILURE_HIGH_OVERTEMP;
		अगर ((failure_state & FAILURE_HIGH_OVERTEMP) == 0)
			prपूर्णांकk(KERN_ERR "windfarm: Critical overtemp due to"
			       " average CPU temperature !\n");
	पूर्ण

	/* Now handle overtemp conditions. We करोn't currently use the windfarm
	 * overtemp handling core as it's not fully suited to the needs of those
	 * new machine. This will be fixed later.
	 */
	अगर (new_state) अणु
		/* High overtemp -> immediate shutकरोwn */
		अगर (new_state & FAILURE_HIGH_OVERTEMP)
			machine_घातer_off();
		अगर ((failure_state & new_state) != new_state)
			cpu_max_all_fans();
		failure_state |= new_state;
	पूर्ण अन्यथा अगर ((failure_state & FAILURE_LOW_OVERTEMP) &&
		   (temp < (cpu_all_पंचांगax + LOW_OVER_CLEAR))) अणु
		prपूर्णांकk(KERN_ERR "windfarm: Overtemp condition cleared !\n");
		failure_state &= ~FAILURE_LOW_OVERTEMP;
	पूर्ण

	वापस failure_state & (FAILURE_LOW_OVERTEMP | FAILURE_HIGH_OVERTEMP);
पूर्ण

अटल पूर्णांक पढ़ो_one_cpu_vals(पूर्णांक cpu, s32 *temp, s32 *घातer)
अणु
	s32 dtemp, volts, amps;
	पूर्णांक rc;

	/* Get diode temperature */
	rc = wf_sensor_get(sens_cpu_temp[cpu], &dtemp);
	अगर (rc) अणु
		DBG("  CPU%d: temp reading error !\n", cpu);
		वापस -EIO;
	पूर्ण
	DBG_LOTS("  CPU%d: temp   = %d.%03d\n", cpu, FIX32TOPRINT((dtemp)));
	*temp = dtemp;

	/* Get voltage */
	rc = wf_sensor_get(sens_cpu_volts[cpu], &volts);
	अगर (rc) अणु
		DBG("  CPU%d, volts reading error !\n", cpu);
		वापस -EIO;
	पूर्ण
	DBG_LOTS("  CPU%d: volts  = %d.%03d\n", cpu, FIX32TOPRINT((volts)));

	/* Get current */
	rc = wf_sensor_get(sens_cpu_amps[cpu], &amps);
	अगर (rc) अणु
		DBG("  CPU%d, current reading error !\n", cpu);
		वापस -EIO;
	पूर्ण
	DBG_LOTS("  CPU%d: amps   = %d.%03d\n", cpu, FIX32TOPRINT((amps)));

	/* Calculate घातer */

	/* Scale voltage and current raw sensor values according to fixed scales
	 * obtained in Darwin and calculate घातer from I and V
	 */
	*घातer = (((u64)volts) * ((u64)amps)) >> 16;

	DBG_LOTS("  CPU%d: power  = %d.%03d\n", cpu, FIX32TOPRINT((*घातer)));

	वापस 0;

पूर्ण

अटल व्योम cpu_fans_tick_split(व्योम)
अणु
	पूर्णांक err, cpu;
	s32 पूर्णांकake, temp, घातer, t_max = 0;

	DBG_LOTS("* cpu fans_tick_split()\n");

	क्रम (cpu = 0; cpu < nr_chips; ++cpu) अणु
		काष्ठा wf_cpu_pid_state *sp = &cpu_pid[cpu];

		/* Read current speed */
		wf_control_get(cpu_rear_fans[cpu], &sp->target);

		DBG_LOTS("  CPU%d: cur_target = %d RPM\n", cpu, sp->target);

		err = पढ़ो_one_cpu_vals(cpu, &temp, &घातer);
		अगर (err) अणु
			failure_state |= FAILURE_SENSOR;
			cpu_max_all_fans();
			वापस;
		पूर्ण

		/* Keep track of highest temp */
		t_max = max(t_max, temp);

		/* Handle possible overtemps */
		अगर (cpu_check_overtemp(t_max))
			वापस;

		/* Run PID */
		wf_cpu_pid_run(sp, घातer, temp);

		DBG_LOTS("  CPU%d: target = %d RPM\n", cpu, sp->target);

		/* Apply result directly to exhaust fan */
		err = wf_control_set(cpu_rear_fans[cpu], sp->target);
		अगर (err) अणु
			pr_warn("wf_pm72: Fan %s reports error %d\n",
				cpu_rear_fans[cpu]->name, err);
			failure_state |= FAILURE_FAN;
			अवरोध;
		पूर्ण

		/* Scale result क्रम पूर्णांकake fan */
		पूर्णांकake = (sp->target * CPU_INTAKE_SCALE) >> 16;
		DBG_LOTS("  CPU%d: intake = %d RPM\n", cpu, पूर्णांकake);
		err = wf_control_set(cpu_front_fans[cpu], पूर्णांकake);
		अगर (err) अणु
			pr_warn("wf_pm72: Fan %s reports error %d\n",
				cpu_front_fans[cpu]->name, err);
			failure_state |= FAILURE_FAN;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cpu_fans_tick_combined(व्योम)
अणु
	s32 temp0, घातer0, temp1, घातer1, t_max = 0;
	s32 temp, घातer, पूर्णांकake, pump;
	काष्ठा wf_control *pump0, *pump1;
	काष्ठा wf_cpu_pid_state *sp = &cpu_pid[0];
	पूर्णांक err, cpu;

	DBG_LOTS("* cpu fans_tick_combined()\n");

	/* Read current speed from cpu 0 */
	wf_control_get(cpu_rear_fans[0], &sp->target);

	DBG_LOTS("  CPUs: cur_target = %d RPM\n", sp->target);

	/* Read values क्रम both CPUs */
	err = पढ़ो_one_cpu_vals(0, &temp0, &घातer0);
	अगर (err) अणु
		failure_state |= FAILURE_SENSOR;
		cpu_max_all_fans();
		वापस;
	पूर्ण
	err = पढ़ो_one_cpu_vals(1, &temp1, &घातer1);
	अगर (err) अणु
		failure_state |= FAILURE_SENSOR;
		cpu_max_all_fans();
		वापस;
	पूर्ण

	/* Keep track of highest temp */
	t_max = max(t_max, max(temp0, temp1));

	/* Handle possible overtemps */
	अगर (cpu_check_overtemp(t_max))
		वापस;

	/* Use the max temp & घातer of both */
	temp = max(temp0, temp1);
	घातer = max(घातer0, घातer1);

	/* Run PID */
	wf_cpu_pid_run(sp, घातer, temp);

	/* Scale result क्रम पूर्णांकake fan */
	पूर्णांकake = (sp->target * CPU_INTAKE_SCALE) >> 16;

	/* Same deal with pump speed */
	pump0 = cpu_pumps[0];
	pump1 = cpu_pumps[1];
	अगर (!pump0) अणु
		pump0 = pump1;
		pump1 = शून्य;
	पूर्ण
	pump = (sp->target * wf_control_get_max(pump0)) /
		cpu_mpu_data[0]->rmaxn_exhaust_fan;

	DBG_LOTS("  CPUs: target = %d RPM\n", sp->target);
	DBG_LOTS("  CPUs: intake = %d RPM\n", पूर्णांकake);
	DBG_LOTS("  CPUs: pump   = %d RPM\n", pump);

	क्रम (cpu = 0; cpu < nr_chips; cpu++) अणु
		err = wf_control_set(cpu_rear_fans[cpu], sp->target);
		अगर (err) अणु
			pr_warn("wf_pm72: Fan %s reports error %d\n",
				cpu_rear_fans[cpu]->name, err);
			failure_state |= FAILURE_FAN;
		पूर्ण
		err = wf_control_set(cpu_front_fans[cpu], पूर्णांकake);
		अगर (err) अणु
			pr_warn("wf_pm72: Fan %s reports error %d\n",
				cpu_front_fans[cpu]->name, err);
			failure_state |= FAILURE_FAN;
		पूर्ण
		err = 0;
		अगर (cpu_pumps[cpu])
			err = wf_control_set(cpu_pumps[cpu], pump);
		अगर (err) अणु
			pr_warn("wf_pm72: Pump %s reports error %d\n",
				cpu_pumps[cpu]->name, err);
			failure_state |= FAILURE_FAN;
		पूर्ण
	पूर्ण
पूर्ण

/* Implementation... */
अटल पूर्णांक cpu_setup_pid(पूर्णांक cpu)
अणु
	काष्ठा wf_cpu_pid_param pid;
	स्थिर काष्ठा mpu_data *mpu = cpu_mpu_data[cpu];
	s32 पंचांगax, ttarget, ptarget;
	पूर्णांक fmin, fmax, hsize;

	/* Get PID params from the appropriate MPU EEPROM */
	पंचांगax = mpu->पंचांगax << 16;
	ttarget = mpu->ttarget << 16;
	ptarget = ((s32)(mpu->pmaxh - mpu->padjmax)) << 16;

	DBG("wf_72: CPU%d ttarget = %d.%03d, tmax = %d.%03d\n",
	    cpu, FIX32TOPRINT(ttarget), FIX32TOPRINT(पंचांगax));

	/* We keep a global पंचांगax क्रम overtemp calculations */
	अगर (पंचांगax < cpu_all_पंचांगax)
		cpu_all_पंचांगax = पंचांगax;

	/* Set PID min/max by using the rear fan min/max */
	fmin = wf_control_get_min(cpu_rear_fans[cpu]);
	fmax = wf_control_get_max(cpu_rear_fans[cpu]);
	DBG("wf_72: CPU%d max RPM range = [%d..%d]\n", cpu, fmin, fmax);

	/* History size */
	hsize = min_t(पूर्णांक, mpu->tguardband, WF_PID_MAX_HISTORY);
	DBG("wf_72: CPU%d history size = %d\n", cpu, hsize);

	/* Initialize PID loop */
	pid.पूर्णांकerval	= 1;	/* seconds */
	pid.history_len = hsize;
	pid.gd		= mpu->pid_gd;
	pid.gp		= mpu->pid_gp;
	pid.gr		= mpu->pid_gr;
	pid.पंचांगax	= पंचांगax;
	pid.ttarget	= ttarget;
	pid.pmaxadj	= ptarget;
	pid.min		= fmin;
	pid.max		= fmax;

	wf_cpu_pid_init(&cpu_pid[cpu], &pid);
	cpu_pid[cpu].target = 1000;

	वापस 0;
पूर्ण

/* Backside/U3 fan */
अटल काष्ठा wf_pid_param backside_u3_param = अणु
	.पूर्णांकerval	= 5,
	.history_len	= 2,
	.gd		= 40 << 20,
	.gp		= 5 << 20,
	.gr		= 0,
	.itarget	= 65 << 16,
	.additive	= 1,
	.min		= 20,
	.max		= 100,
पूर्ण;

अटल काष्ठा wf_pid_param backside_u3h_param = अणु
	.पूर्णांकerval	= 5,
	.history_len	= 2,
	.gd		= 20 << 20,
	.gp		= 5 << 20,
	.gr		= 0,
	.itarget	= 75 << 16,
	.additive	= 1,
	.min		= 20,
	.max		= 100,
पूर्ण;

अटल व्योम backside_fan_tick(व्योम)
अणु
	s32 temp;
	पूर्णांक speed;
	पूर्णांक err;

	अगर (!backside_fan || !backside_temp || !backside_tick)
		वापस;
	अगर (--backside_tick > 0)
		वापस;
	backside_tick = backside_pid.param.पूर्णांकerval;

	DBG_LOTS("* backside fans tick\n");

	/* Update fan speed from actual fans */
	err = wf_control_get(backside_fan, &speed);
	अगर (!err)
		backside_pid.target = speed;

	err = wf_sensor_get(backside_temp, &temp);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: U4 temp sensor error %d\n",
		       err);
		failure_state |= FAILURE_SENSOR;
		wf_control_set_max(backside_fan);
		वापस;
	पूर्ण
	speed = wf_pid_run(&backside_pid, temp);

	DBG_LOTS("backside PID temp=%d.%.3d speed=%d\n",
		 FIX32TOPRINT(temp), speed);

	err = wf_control_set(backside_fan, speed);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: backside fan error %d\n", err);
		failure_state |= FAILURE_FAN;
	पूर्ण
पूर्ण

अटल व्योम backside_setup_pid(व्योम)
अणु
	/* first समय initialize things */
	s32 fmin = wf_control_get_min(backside_fan);
	s32 fmax = wf_control_get_max(backside_fan);
	काष्ठा wf_pid_param param;
	काष्ठा device_node *u3;
	पूर्णांक u3h = 1; /* conservative by शेष */

	u3 = of_find_node_by_path("/u3@0,f8000000");
	अगर (u3 != शून्य) अणु
		स्थिर u32 *vers = of_get_property(u3, "device-rev", शून्य);
		अगर (vers)
			अगर (((*vers) & 0x3f) < 0x34)
				u3h = 0;
		of_node_put(u3);
	पूर्ण

	param = u3h ? backside_u3h_param : backside_u3_param;

	param.min = max(param.min, fmin);
	param.max = min(param.max, fmax);
	wf_pid_init(&backside_pid, &param);
	backside_tick = 1;

	pr_info("wf_pm72: Backside control loop started.\n");
पूर्ण

/* Drive bay fan */
अटल स्थिर काष्ठा wf_pid_param drives_param = अणु
	.पूर्णांकerval	= 5,
	.history_len	= 2,
	.gd		= 30 << 20,
	.gp		= 5 << 20,
	.gr		= 0,
	.itarget	= 40 << 16,
	.additive	= 1,
	.min		= 300,
	.max		= 4000,
पूर्ण;

अटल व्योम drives_fan_tick(व्योम)
अणु
	s32 temp;
	पूर्णांक speed;
	पूर्णांक err;

	अगर (!drives_fan || !drives_temp || !drives_tick)
		वापस;
	अगर (--drives_tick > 0)
		वापस;
	drives_tick = drives_pid.param.पूर्णांकerval;

	DBG_LOTS("* drives fans tick\n");

	/* Update fan speed from actual fans */
	err = wf_control_get(drives_fan, &speed);
	अगर (!err)
		drives_pid.target = speed;

	err = wf_sensor_get(drives_temp, &temp);
	अगर (err) अणु
		pr_warn("wf_pm72: drive bay temp sensor error %d\n", err);
		failure_state |= FAILURE_SENSOR;
		wf_control_set_max(drives_fan);
		वापस;
	पूर्ण
	speed = wf_pid_run(&drives_pid, temp);

	DBG_LOTS("drives PID temp=%d.%.3d speed=%d\n",
		 FIX32TOPRINT(temp), speed);

	err = wf_control_set(drives_fan, speed);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: drive bay fan error %d\n", err);
		failure_state |= FAILURE_FAN;
	पूर्ण
पूर्ण

अटल व्योम drives_setup_pid(व्योम)
अणु
	/* first समय initialize things */
	s32 fmin = wf_control_get_min(drives_fan);
	s32 fmax = wf_control_get_max(drives_fan);
	काष्ठा wf_pid_param param = drives_param;

	param.min = max(param.min, fmin);
	param.max = min(param.max, fmax);
	wf_pid_init(&drives_pid, &param);
	drives_tick = 1;

	pr_info("wf_pm72: Drive bay control loop started.\n");
पूर्ण

अटल व्योम set_fail_state(व्योम)
अणु
	cpu_max_all_fans();

	अगर (backside_fan)
		wf_control_set_max(backside_fan);
	अगर (slots_fan)
		wf_control_set_max(slots_fan);
	अगर (drives_fan)
		wf_control_set_max(drives_fan);
पूर्ण

अटल व्योम pm72_tick(व्योम)
अणु
	पूर्णांक i, last_failure;

	अगर (!started) अणु
		started = true;
		prपूर्णांकk(KERN_INFO "windfarm: CPUs control loops started.\n");
		क्रम (i = 0; i < nr_chips; ++i) अणु
			अगर (cpu_setup_pid(i) < 0) अणु
				failure_state = FAILURE_PERM;
				set_fail_state();
				अवरोध;
			पूर्ण
		पूर्ण
		DBG_LOTS("cpu_all_tmax=%d.%03d\n", FIX32TOPRINT(cpu_all_पंचांगax));

		backside_setup_pid();
		drives_setup_pid();

		/*
		 * We करोn't have the right stuff to drive the PCI fan
		 * so we fix it to a शेष value
		 */
		wf_control_set(slots_fan, SLOTS_FAN_DEFAULT_PWM);

#अगर_घोषित HACKED_OVERTEMP
		cpu_all_पंचांगax = 60 << 16;
#पूर्ण_अगर
	पूर्ण

	/* Permanent failure, bail out */
	अगर (failure_state & FAILURE_PERM)
		वापस;

	/*
	 * Clear all failure bits except low overtemp which will be eventually
	 * cleared by the control loop itself
	 */
	last_failure = failure_state;
	failure_state &= FAILURE_LOW_OVERTEMP;
	अगर (cpu_pid_combined)
		cpu_fans_tick_combined();
	अन्यथा
		cpu_fans_tick_split();
	backside_fan_tick();
	drives_fan_tick();

	DBG_LOTS("  last_failure: 0x%x, failure_state: %x\n",
		 last_failure, failure_state);

	/* Check क्रम failures. Any failure causes cpufreq clamping */
	अगर (failure_state && last_failure == 0 && cpufreq_clamp)
		wf_control_set_max(cpufreq_clamp);
	अगर (failure_state == 0 && last_failure && cpufreq_clamp)
		wf_control_set_min(cpufreq_clamp);

	/* That's it क्रम now, we might want to deal with other failures
	 * dअगरferently in the future though
	 */
पूर्ण

अटल व्योम pm72_new_control(काष्ठा wf_control *ct)
अणु
	bool all_controls;
	bool had_pump = cpu_pumps[0] || cpu_pumps[1];

	अगर (!म_भेद(ct->name, "cpu-front-fan-0"))
		cpu_front_fans[0] = ct;
	अन्यथा अगर (!म_भेद(ct->name, "cpu-front-fan-1"))
		cpu_front_fans[1] = ct;
	अन्यथा अगर (!म_भेद(ct->name, "cpu-rear-fan-0"))
		cpu_rear_fans[0] = ct;
	अन्यथा अगर (!म_भेद(ct->name, "cpu-rear-fan-1"))
		cpu_rear_fans[1] = ct;
	अन्यथा अगर (!म_भेद(ct->name, "cpu-pump-0"))
		cpu_pumps[0] = ct;
	अन्यथा अगर (!म_भेद(ct->name, "cpu-pump-1"))
		cpu_pumps[1] = ct;
	अन्यथा अगर (!म_भेद(ct->name, "backside-fan"))
		backside_fan = ct;
	अन्यथा अगर (!म_भेद(ct->name, "slots-fan"))
		slots_fan = ct;
	अन्यथा अगर (!म_भेद(ct->name, "drive-bay-fan"))
		drives_fan = ct;
	अन्यथा अगर (!म_भेद(ct->name, "cpufreq-clamp"))
		cpufreq_clamp = ct;

	all_controls =
		cpu_front_fans[0] &&
		cpu_rear_fans[0] &&
		backside_fan &&
		slots_fan &&
		drives_fan;
	अगर (nr_chips > 1)
		all_controls &=
			cpu_front_fans[1] &&
			cpu_rear_fans[1];
	have_all_controls = all_controls;

	अगर ((cpu_pumps[0] || cpu_pumps[1]) && !had_pump) अणु
		pr_info("wf_pm72: Liquid cooling pump(s) detected,"
			" using new algorithm !\n");
		cpu_pid_combined = true;
	पूर्ण
पूर्ण


अटल व्योम pm72_new_sensor(काष्ठा wf_sensor *sr)
अणु
	bool all_sensors;

	अगर (!म_भेद(sr->name, "cpu-diode-temp-0"))
		sens_cpu_temp[0] = sr;
	अन्यथा अगर (!म_भेद(sr->name, "cpu-diode-temp-1"))
		sens_cpu_temp[1] = sr;
	अन्यथा अगर (!म_भेद(sr->name, "cpu-voltage-0"))
		sens_cpu_volts[0] = sr;
	अन्यथा अगर (!म_भेद(sr->name, "cpu-voltage-1"))
		sens_cpu_volts[1] = sr;
	अन्यथा अगर (!म_भेद(sr->name, "cpu-current-0"))
		sens_cpu_amps[0] = sr;
	अन्यथा अगर (!म_भेद(sr->name, "cpu-current-1"))
		sens_cpu_amps[1] = sr;
	अन्यथा अगर (!म_भेद(sr->name, "backside-temp"))
		backside_temp = sr;
	अन्यथा अगर (!म_भेद(sr->name, "hd-temp"))
		drives_temp = sr;

	all_sensors =
		sens_cpu_temp[0] &&
		sens_cpu_volts[0] &&
		sens_cpu_amps[0] &&
		backside_temp &&
		drives_temp;
	अगर (nr_chips > 1)
		all_sensors &=
			sens_cpu_temp[1] &&
			sens_cpu_volts[1] &&
			sens_cpu_amps[1];

	have_all_sensors = all_sensors;
पूर्ण

अटल पूर्णांक pm72_wf_notअगरy(काष्ठा notअगरier_block *self,
			  अचिन्हित दीर्घ event, व्योम *data)
अणु
	चयन (event) अणु
	हाल WF_EVENT_NEW_SENSOR:
		pm72_new_sensor(data);
		अवरोध;
	हाल WF_EVENT_NEW_CONTROL:
		pm72_new_control(data);
		अवरोध;
	हाल WF_EVENT_TICK:
		अगर (have_all_controls && have_all_sensors)
			pm72_tick();
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block pm72_events = अणु
	.notअगरier_call = pm72_wf_notअगरy,
पूर्ण;

अटल पूर्णांक wf_pm72_probe(काष्ठा platक्रमm_device *dev)
अणु
	wf_रेजिस्टर_client(&pm72_events);
	वापस 0;
पूर्ण

अटल पूर्णांक wf_pm72_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	wf_unरेजिस्टर_client(&pm72_events);

	/* should release all sensors and controls */
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wf_pm72_driver = अणु
	.probe	= wf_pm72_probe,
	.हटाओ	= wf_pm72_हटाओ,
	.driver	= अणु
		.name = "windfarm",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init wf_pm72_init(व्योम)
अणु
	काष्ठा device_node *cpu;
	पूर्णांक i;

	अगर (!of_machine_is_compatible("PowerMac7,2") &&
	    !of_machine_is_compatible("PowerMac7,3"))
		वापस -ENODEV;

	/* Count the number of CPU cores */
	nr_chips = 0;
	क्रम_each_node_by_type(cpu, "cpu")
		++nr_chips;
	अगर (nr_chips > NR_CHIPS)
		nr_chips = NR_CHIPS;

	pr_info("windfarm: Initializing for desktop G5 with %d chips\n",
		nr_chips);

	/* Get MPU data क्रम each CPU */
	क्रम (i = 0; i < nr_chips; i++) अणु
		cpu_mpu_data[i] = wf_get_mpu(i);
		अगर (!cpu_mpu_data[i]) अणु
			pr_err("wf_pm72: Failed to find MPU data for CPU %d\n", i);
			वापस -ENXIO;
		पूर्ण
	पूर्ण

#अगर_घोषित MODULE
	request_module("windfarm_fcu_controls");
	request_module("windfarm_lm75_sensor");
	request_module("windfarm_ad7417_sensor");
	request_module("windfarm_max6690_sensor");
	request_module("windfarm_cpufreq_clamp");
#पूर्ण_अगर /* MODULE */

	platक्रमm_driver_रेजिस्टर(&wf_pm72_driver);
	वापस 0;
पूर्ण

अटल व्योम __निकास wf_pm72_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&wf_pm72_driver);
पूर्ण

module_init(wf_pm72_init);
module_निकास(wf_pm72_निकास);

MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("Thermal control for AGP PowerMac G5s");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:windfarm");
