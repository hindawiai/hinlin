<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control.
 * Control loops क्रम RackMack3,1 (Xserve G5)
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
अटल काष्ठा wf_sensor *slots_temp;
अटल काष्ठा wf_sensor *dimms_temp;

अटल काष्ठा wf_control *cpu_fans[NR_CHIPS][3];
अटल काष्ठा wf_control *backside_fan;
अटल काष्ठा wf_control *slots_fan;
अटल काष्ठा wf_control *cpufreq_clamp;

/* We keep a temperature history क्रम average calculation of 180s */
#घोषणा CPU_TEMP_HIST_SIZE	180

/* PID loop state */
अटल स्थिर काष्ठा mpu_data *cpu_mpu_data[NR_CHIPS];
अटल काष्ठा wf_cpu_pid_state cpu_pid[NR_CHIPS];
अटल u32 cpu_thist[CPU_TEMP_HIST_SIZE];
अटल पूर्णांक cpu_thist_pt;
अटल s64 cpu_thist_total;
अटल s32 cpu_all_पंचांगax = 100 << 16;
अटल काष्ठा wf_pid_state backside_pid;
अटल पूर्णांक backside_tick;
अटल काष्ठा wf_pid_state slots_pid;
अटल पूर्णांक slots_tick;
अटल पूर्णांक slots_speed;
अटल काष्ठा wf_pid_state dimms_pid;
अटल पूर्णांक dimms_output_clamp;

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
		अगर (cpu_fans[i][0])
			wf_control_set_max(cpu_fans[i][0]);
		अगर (cpu_fans[i][1])
			wf_control_set_max(cpu_fans[i][1]);
		अगर (cpu_fans[i][2])
			wf_control_set_max(cpu_fans[i][2]);
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

अटल व्योम cpu_fans_tick(व्योम)
अणु
	पूर्णांक err, cpu, i;
	s32 speed, temp, घातer, t_max = 0;

	DBG_LOTS("* cpu fans_tick_split()\n");

	क्रम (cpu = 0; cpu < nr_chips; ++cpu) अणु
		काष्ठा wf_cpu_pid_state *sp = &cpu_pid[cpu];

		/* Read current speed */
		wf_control_get(cpu_fans[cpu][0], &sp->target);

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

		/* Apply DIMMs clamp */
		speed = max(sp->target, dimms_output_clamp);

		/* Apply result to all cpu fans */
		क्रम (i = 0; i < 3; i++) अणु
			err = wf_control_set(cpu_fans[cpu][i], speed);
			अगर (err) अणु
				pr_warn("wf_rm31: Fan %s reports error %d\n",
					cpu_fans[cpu][i]->name, err);
				failure_state |= FAILURE_FAN;
			पूर्ण
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
	fmin = wf_control_get_min(cpu_fans[cpu][0]);
	fmax = wf_control_get_max(cpu_fans[cpu][0]);
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
	cpu_pid[cpu].target = 4000;
	
	वापस 0;
पूर्ण

/* Backside/U3 fan */
अटल स्थिर काष्ठा wf_pid_param backside_param = अणु
	.पूर्णांकerval	= 1,
	.history_len	= 2,
	.gd		= 0x00500000,
	.gp		= 0x0004cccc,
	.gr		= 0,
	.itarget	= 70 << 16,
	.additive	= 0,
	.min		= 20,
	.max		= 100,
पूर्ण;

/* DIMMs temperature (clamp the backside fan) */
अटल स्थिर काष्ठा wf_pid_param dimms_param = अणु
	.पूर्णांकerval	= 1,
	.history_len	= 20,
	.gd		= 0,
	.gp		= 0,
	.gr		= 0x06553600,
	.itarget	= 50 << 16,
	.additive	= 0,
	.min		= 4000,
	.max		= 14000,
पूर्ण;

अटल व्योम backside_fan_tick(व्योम)
अणु
	s32 temp, dtemp;
	पूर्णांक speed, dspeed, fan_min;
	पूर्णांक err;

	अगर (!backside_fan || !backside_temp || !dimms_temp || !backside_tick)
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
		prपूर्णांकk(KERN_WARNING "windfarm: U3 temp sensor error %d\n",
		       err);
		failure_state |= FAILURE_SENSOR;
		wf_control_set_max(backside_fan);
		वापस;
	पूर्ण
	speed = wf_pid_run(&backside_pid, temp);

	DBG_LOTS("backside PID temp=%d.%.3d speed=%d\n",
		 FIX32TOPRINT(temp), speed);

	err = wf_sensor_get(dimms_temp, &dtemp);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: DIMMs temp sensor error %d\n",
		       err);
		failure_state |= FAILURE_SENSOR;
		wf_control_set_max(backside_fan);
		वापस;
	पूर्ण
	dspeed = wf_pid_run(&dimms_pid, dtemp);
	dimms_output_clamp = dspeed;

	fan_min = (dspeed * 100) / 14000;
	fan_min = max(fan_min, backside_param.min);
	speed = max(speed, fan_min);

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

	param = backside_param;
	param.min = max(param.min, fmin);
	param.max = min(param.max, fmax);
	wf_pid_init(&backside_pid, &param);

	param = dimms_param;
	wf_pid_init(&dimms_pid, &param);

	backside_tick = 1;

	pr_info("wf_rm31: Backside control loop started.\n");
पूर्ण

/* Slots fan */
अटल स्थिर काष्ठा wf_pid_param slots_param = अणु
	.पूर्णांकerval	= 1,
	.history_len	= 20,
	.gd		= 0,
	.gp		= 0,
	.gr		= 0x00100000,
	.itarget	= 3200000,
	.additive	= 0,
	.min		= 20,
	.max		= 100,
पूर्ण;

अटल व्योम slots_fan_tick(व्योम)
अणु
	s32 temp;
	पूर्णांक speed;
	पूर्णांक err;

	अगर (!slots_fan || !slots_temp || !slots_tick)
		वापस;
	अगर (--slots_tick > 0)
		वापस;
	slots_tick = slots_pid.param.पूर्णांकerval;

	DBG_LOTS("* slots fans tick\n");

	err = wf_sensor_get(slots_temp, &temp);
	अगर (err) अणु
		pr_warn("wf_rm31: slots temp sensor error %d\n", err);
		failure_state |= FAILURE_SENSOR;
		wf_control_set_max(slots_fan);
		वापस;
	पूर्ण
	speed = wf_pid_run(&slots_pid, temp);

	DBG_LOTS("slots PID temp=%d.%.3d speed=%d\n",
		 FIX32TOPRINT(temp), speed);

	slots_speed = speed;
	err = wf_control_set(slots_fan, speed);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: slots bay fan error %d\n", err);
		failure_state |= FAILURE_FAN;
	पूर्ण
पूर्ण

अटल व्योम slots_setup_pid(व्योम)
अणु
	/* first समय initialize things */
	s32 fmin = wf_control_get_min(slots_fan);
	s32 fmax = wf_control_get_max(slots_fan);
	काष्ठा wf_pid_param param = slots_param;

	param.min = max(param.min, fmin);
	param.max = min(param.max, fmax);
	wf_pid_init(&slots_pid, &param);
	slots_tick = 1;

	pr_info("wf_rm31: Slots control loop started.\n");
पूर्ण

अटल व्योम set_fail_state(व्योम)
अणु
	cpu_max_all_fans();

	अगर (backside_fan)
		wf_control_set_max(backside_fan);
	अगर (slots_fan)
		wf_control_set_max(slots_fan);
पूर्ण

अटल व्योम rm31_tick(व्योम)
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
		slots_setup_pid();

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
	backside_fan_tick();
	slots_fan_tick();

	/* We करो CPUs last because they can be clamped high by
	 * DIMM temperature
	 */
	cpu_fans_tick();

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

अटल व्योम rm31_new_control(काष्ठा wf_control *ct)
अणु
	bool all_controls;

	अगर (!म_भेद(ct->name, "cpu-fan-a-0"))
		cpu_fans[0][0] = ct;
	अन्यथा अगर (!म_भेद(ct->name, "cpu-fan-b-0"))
		cpu_fans[0][1] = ct;
	अन्यथा अगर (!म_भेद(ct->name, "cpu-fan-c-0"))
		cpu_fans[0][2] = ct;
	अन्यथा अगर (!म_भेद(ct->name, "cpu-fan-a-1"))
		cpu_fans[1][0] = ct;
	अन्यथा अगर (!म_भेद(ct->name, "cpu-fan-b-1"))
		cpu_fans[1][1] = ct;
	अन्यथा अगर (!म_भेद(ct->name, "cpu-fan-c-1"))
		cpu_fans[1][2] = ct;
	अन्यथा अगर (!म_भेद(ct->name, "backside-fan"))
		backside_fan = ct;
	अन्यथा अगर (!म_भेद(ct->name, "slots-fan"))
		slots_fan = ct;
	अन्यथा अगर (!म_भेद(ct->name, "cpufreq-clamp"))
		cpufreq_clamp = ct;

	all_controls =
		cpu_fans[0][0] &&
		cpu_fans[0][1] &&
		cpu_fans[0][2] &&
		backside_fan &&
		slots_fan;
	अगर (nr_chips > 1)
		all_controls &=
			cpu_fans[1][0] &&
			cpu_fans[1][1] &&
			cpu_fans[1][2];
	have_all_controls = all_controls;
पूर्ण


अटल व्योम rm31_new_sensor(काष्ठा wf_sensor *sr)
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
	अन्यथा अगर (!म_भेद(sr->name, "slots-temp"))
		slots_temp = sr;
	अन्यथा अगर (!म_भेद(sr->name, "dimms-temp"))
		dimms_temp = sr;

	all_sensors =
		sens_cpu_temp[0] &&
		sens_cpu_volts[0] &&
		sens_cpu_amps[0] &&
		backside_temp &&
		slots_temp &&
		dimms_temp;
	अगर (nr_chips > 1)
		all_sensors &=
			sens_cpu_temp[1] &&
			sens_cpu_volts[1] &&
			sens_cpu_amps[1];

	have_all_sensors = all_sensors;
पूर्ण

अटल पूर्णांक rm31_wf_notअगरy(काष्ठा notअगरier_block *self,
			  अचिन्हित दीर्घ event, व्योम *data)
अणु
	चयन (event) अणु
	हाल WF_EVENT_NEW_SENSOR:
		rm31_new_sensor(data);
		अवरोध;
	हाल WF_EVENT_NEW_CONTROL:
		rm31_new_control(data);
		अवरोध;
	हाल WF_EVENT_TICK:
		अगर (have_all_controls && have_all_sensors)
			rm31_tick();
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block rm31_events = अणु
	.notअगरier_call = rm31_wf_notअगरy,
पूर्ण;

अटल पूर्णांक wf_rm31_probe(काष्ठा platक्रमm_device *dev)
अणु
	wf_रेजिस्टर_client(&rm31_events);
	वापस 0;
पूर्ण

अटल पूर्णांक wf_rm31_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	wf_unरेजिस्टर_client(&rm31_events);

	/* should release all sensors and controls */
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wf_rm31_driver = अणु
	.probe	= wf_rm31_probe,
	.हटाओ	= wf_rm31_हटाओ,
	.driver	= अणु
		.name = "windfarm",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init wf_rm31_init(व्योम)
अणु
	काष्ठा device_node *cpu;
	पूर्णांक i;

	अगर (!of_machine_is_compatible("RackMac3,1"))
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
			pr_err("wf_rm31: Failed to find MPU data for CPU %d\n", i);
			वापस -ENXIO;
		पूर्ण
	पूर्ण

#अगर_घोषित MODULE
	request_module("windfarm_fcu_controls");
	request_module("windfarm_lm75_sensor");
	request_module("windfarm_lm87_sensor");
	request_module("windfarm_ad7417_sensor");
	request_module("windfarm_max6690_sensor");
	request_module("windfarm_cpufreq_clamp");
#पूर्ण_अगर /* MODULE */

	platक्रमm_driver_रेजिस्टर(&wf_rm31_driver);
	वापस 0;
पूर्ण

अटल व्योम __निकास wf_rm31_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&wf_rm31_driver);
पूर्ण

module_init(wf_rm31_init);
module_निकास(wf_rm31_निकास);

MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("Thermal control for Xserve G5");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:windfarm");
