<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control.
 * Control loops क्रम machines with SMU and PPC970MP processors.
 *
 * Copyright (C) 2005 Paul Mackerras, IBM Corp. <paulus@samba.org>
 * Copyright (C) 2006 Benjamin Herrenschmidt, IBM Corp.
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

#घोषणा VERSION "0.2"

#घोषणा DEBUG
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

/* We currently only handle 2 chips, 4 cores... */
#घोषणा NR_CHIPS	2
#घोषणा NR_CORES	4
#घोषणा NR_CPU_FANS	3 * NR_CHIPS

/* Controls and sensors */
अटल काष्ठा wf_sensor *sens_cpu_temp[NR_CORES];
अटल काष्ठा wf_sensor *sens_cpu_घातer[NR_CORES];
अटल काष्ठा wf_sensor *hd_temp;
अटल काष्ठा wf_sensor *slots_घातer;
अटल काष्ठा wf_sensor *u4_temp;

अटल काष्ठा wf_control *cpu_fans[NR_CPU_FANS];
अटल अक्षर *cpu_fan_names[NR_CPU_FANS] = अणु
	"cpu-rear-fan-0",
	"cpu-rear-fan-1",
	"cpu-front-fan-0",
	"cpu-front-fan-1",
	"cpu-pump-0",
	"cpu-pump-1",
पूर्ण;
अटल काष्ठा wf_control *cpufreq_clamp;

/* Second pump isn't required (and isn't actually present) */
#घोषणा CPU_FANS_REQD		(NR_CPU_FANS - 2)
#घोषणा FIRST_PUMP		4
#घोषणा LAST_PUMP		5

/* We keep a temperature history क्रम average calculation of 180s */
#घोषणा CPU_TEMP_HIST_SIZE	180

/* Scale factor क्रम fan speed, *100 */
अटल पूर्णांक cpu_fan_scale[NR_CPU_FANS] = अणु
	100,
	100,
	97,		/* inlet fans run at 97% of exhaust fan */
	97,
	100,		/* updated later */
	100,		/* updated later */
पूर्ण;

अटल काष्ठा wf_control *backside_fan;
अटल काष्ठा wf_control *slots_fan;
अटल काष्ठा wf_control *drive_bay_fan;

/* PID loop state */
अटल काष्ठा wf_cpu_pid_state cpu_pid[NR_CORES];
अटल u32 cpu_thist[CPU_TEMP_HIST_SIZE];
अटल पूर्णांक cpu_thist_pt;
अटल s64 cpu_thist_total;
अटल s32 cpu_all_पंचांगax = 100 << 16;
अटल पूर्णांक cpu_last_target;
अटल काष्ठा wf_pid_state backside_pid;
अटल पूर्णांक backside_tick;
अटल काष्ठा wf_pid_state slots_pid;
अटल bool slots_started;
अटल काष्ठा wf_pid_state drive_bay_pid;
अटल पूर्णांक drive_bay_tick;

अटल पूर्णांक nr_cores;
अटल पूर्णांक have_all_controls;
अटल पूर्णांक have_all_sensors;
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


/* Implementation... */
अटल पूर्णांक create_cpu_loop(पूर्णांक cpu)
अणु
	पूर्णांक chip = cpu / 2;
	पूर्णांक core = cpu & 1;
	काष्ठा smu_sdbp_header *hdr;
	काष्ठा smu_sdbp_cpupiddata *piddata;
	काष्ठा wf_cpu_pid_param pid;
	काष्ठा wf_control *मुख्य_fan = cpu_fans[0];
	s32 पंचांगax;
	पूर्णांक fmin;

	/* Get FVT params to get Tmax; अगर not found, assume शेष */
	hdr = smu_sat_get_sdb_partition(chip, 0xC4 + core, शून्य);
	अगर (hdr) अणु
		काष्ठा smu_sdbp_fvt *fvt = (काष्ठा smu_sdbp_fvt *)&hdr[1];
		पंचांगax = fvt->maxtemp << 16;
	पूर्ण अन्यथा
		पंचांगax = 95 << 16;	/* शेष to 95 degrees C */

	/* We keep a global पंचांगax क्रम overtemp calculations */
	अगर (पंचांगax < cpu_all_पंचांगax)
		cpu_all_पंचांगax = पंचांगax;

	kमुक्त(hdr);

	/* Get PID params from the appropriate SAT */
	hdr = smu_sat_get_sdb_partition(chip, 0xC8 + core, शून्य);
	अगर (hdr == शून्य) अणु
		prपूर्णांकk(KERN_WARNING"windfarm: can't get CPU PID fan config\n");
		वापस -EINVAL;
	पूर्ण
	piddata = (काष्ठा smu_sdbp_cpupiddata *)&hdr[1];

	/*
	 * Darwin has a minimum fan speed of 1000 rpm क्रम the 4-way and
	 * 515 क्रम the 2-way.  That appears to be overसमाप्त, so क्रम now,
	 * impose a minimum of 750 or 515.
	 */
	fmin = (nr_cores > 2) ? 750 : 515;

	/* Initialize PID loop */
	pid.पूर्णांकerval = 1;	/* seconds */
	pid.history_len = piddata->history_len;
	pid.gd = piddata->gd;
	pid.gp = piddata->gp;
	pid.gr = piddata->gr / piddata->history_len;
	pid.pmaxadj = (piddata->max_घातer << 16) - (piddata->घातer_adj << 8);
	pid.ttarget = पंचांगax - (piddata->target_temp_delta << 16);
	pid.पंचांगax = पंचांगax;
	pid.min = मुख्य_fan->ops->get_min(मुख्य_fan);
	pid.max = मुख्य_fan->ops->get_max(मुख्य_fan);
	अगर (pid.min < fmin)
		pid.min = fmin;

	wf_cpu_pid_init(&cpu_pid[cpu], &pid);

	kमुक्त(hdr);

	वापस 0;
पूर्ण

अटल व्योम cpu_max_all_fans(व्योम)
अणु
	पूर्णांक i;

	/* We max all CPU fans in हाल of a sensor error. We also करो the
	 * cpufreq clamping now, even अगर it's supposedly करोne later by the
	 * generic code anyway, we करो it earlier here to react faster
	 */
	अगर (cpufreq_clamp)
		wf_control_set_max(cpufreq_clamp);
	क्रम (i = 0; i < NR_CPU_FANS; ++i)
		अगर (cpu_fans[i])
			wf_control_set_max(cpu_fans[i]);
पूर्ण

अटल पूर्णांक cpu_check_overtemp(s32 temp)
अणु
	पूर्णांक new_state = 0;
	s32 t_avg, t_old;

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

	/* We calculate a history of max temperatures and use that क्रम the
	 * overtemp management
	 */
	t_old = cpu_thist[cpu_thist_pt];
	cpu_thist[cpu_thist_pt] = temp;
	cpu_thist_pt = (cpu_thist_pt + 1) % CPU_TEMP_HIST_SIZE;
	cpu_thist_total -= t_old;
	cpu_thist_total += temp;
	t_avg = cpu_thist_total / CPU_TEMP_HIST_SIZE;

	DBG_LOTS("t_avg = %d.%03d (out: %d.%03d, in: %d.%03d)\n",
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

अटल व्योम cpu_fans_tick(व्योम)
अणु
	पूर्णांक err, cpu;
	s32 greatest_delta = 0;
	s32 temp, घातer, t_max = 0;
	पूर्णांक i, t, target = 0;
	काष्ठा wf_sensor *sr;
	काष्ठा wf_control *ct;
	काष्ठा wf_cpu_pid_state *sp;

	DBG_LOTS(KERN_DEBUG);
	क्रम (cpu = 0; cpu < nr_cores; ++cpu) अणु
		/* Get CPU core temperature */
		sr = sens_cpu_temp[cpu];
		err = sr->ops->get_value(sr, &temp);
		अगर (err) अणु
			DBG("\n");
			prपूर्णांकk(KERN_WARNING "windfarm: CPU %d temperature "
			       "sensor error %d\n", cpu, err);
			failure_state |= FAILURE_SENSOR;
			cpu_max_all_fans();
			वापस;
		पूर्ण

		/* Keep track of highest temp */
		t_max = max(t_max, temp);

		/* Get CPU घातer */
		sr = sens_cpu_घातer[cpu];
		err = sr->ops->get_value(sr, &घातer);
		अगर (err) अणु
			DBG("\n");
			prपूर्णांकk(KERN_WARNING "windfarm: CPU %d power "
			       "sensor error %d\n", cpu, err);
			failure_state |= FAILURE_SENSOR;
			cpu_max_all_fans();
			वापस;
		पूर्ण

		/* Run PID */
		sp = &cpu_pid[cpu];
		t = wf_cpu_pid_run(sp, घातer, temp);

		अगर (cpu == 0 || sp->last_delta > greatest_delta) अणु
			greatest_delta = sp->last_delta;
			target = t;
		पूर्ण
		DBG_LOTS("[%d] P=%d.%.3d T=%d.%.3d ",
		    cpu, FIX32TOPRINT(घातer), FIX32TOPRINT(temp));
	पूर्ण
	DBG_LOTS("fans = %d, t_max = %d.%03d\n", target, FIX32TOPRINT(t_max));

	/* Darwin limits decrease to 20 per iteration */
	अगर (target < (cpu_last_target - 20))
		target = cpu_last_target - 20;
	cpu_last_target = target;
	क्रम (cpu = 0; cpu < nr_cores; ++cpu)
		cpu_pid[cpu].target = target;

	/* Handle possible overtemps */
	अगर (cpu_check_overtemp(t_max))
		वापस;

	/* Set fans */
	क्रम (i = 0; i < NR_CPU_FANS; ++i) अणु
		ct = cpu_fans[i];
		अगर (ct == शून्य)
			जारी;
		err = ct->ops->set_value(ct, target * cpu_fan_scale[i] / 100);
		अगर (err) अणु
			prपूर्णांकk(KERN_WARNING "windfarm: fan %s reports "
			       "error %d\n", ct->name, err);
			failure_state |= FAILURE_FAN;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* Backside/U4 fan */
अटल काष्ठा wf_pid_param backside_param = अणु
	.पूर्णांकerval	= 5,
	.history_len	= 2,
	.gd		= 48 << 20,
	.gp		= 5 << 20,
	.gr		= 0,
	.itarget	= 64 << 16,
	.additive	= 1,
पूर्ण;

अटल व्योम backside_fan_tick(व्योम)
अणु
	s32 temp;
	पूर्णांक speed;
	पूर्णांक err;

	अगर (!backside_fan || !u4_temp)
		वापस;
	अगर (!backside_tick) अणु
		/* first समय; initialize things */
		prपूर्णांकk(KERN_INFO "windfarm: Backside control loop started.\n");
		backside_param.min = backside_fan->ops->get_min(backside_fan);
		backside_param.max = backside_fan->ops->get_max(backside_fan);
		wf_pid_init(&backside_pid, &backside_param);
		backside_tick = 1;
	पूर्ण
	अगर (--backside_tick > 0)
		वापस;
	backside_tick = backside_pid.param.पूर्णांकerval;

	err = u4_temp->ops->get_value(u4_temp, &temp);
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

	err = backside_fan->ops->set_value(backside_fan, speed);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: backside fan error %d\n", err);
		failure_state |= FAILURE_FAN;
	पूर्ण
पूर्ण

/* Drive bay fan */
अटल काष्ठा wf_pid_param drive_bay_prm = अणु
	.पूर्णांकerval	= 5,
	.history_len	= 2,
	.gd		= 30 << 20,
	.gp		= 5 << 20,
	.gr		= 0,
	.itarget	= 40 << 16,
	.additive	= 1,
पूर्ण;

अटल व्योम drive_bay_fan_tick(व्योम)
अणु
	s32 temp;
	पूर्णांक speed;
	पूर्णांक err;

	अगर (!drive_bay_fan || !hd_temp)
		वापस;
	अगर (!drive_bay_tick) अणु
		/* first समय; initialize things */
		prपूर्णांकk(KERN_INFO "windfarm: Drive bay control loop started.\n");
		drive_bay_prm.min = drive_bay_fan->ops->get_min(drive_bay_fan);
		drive_bay_prm.max = drive_bay_fan->ops->get_max(drive_bay_fan);
		wf_pid_init(&drive_bay_pid, &drive_bay_prm);
		drive_bay_tick = 1;
	पूर्ण
	अगर (--drive_bay_tick > 0)
		वापस;
	drive_bay_tick = drive_bay_pid.param.पूर्णांकerval;

	err = hd_temp->ops->get_value(hd_temp, &temp);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: drive bay temp sensor "
		       "error %d\n", err);
		failure_state |= FAILURE_SENSOR;
		wf_control_set_max(drive_bay_fan);
		वापस;
	पूर्ण
	speed = wf_pid_run(&drive_bay_pid, temp);
	DBG_LOTS("drive_bay PID temp=%d.%.3d speed=%d\n",
		 FIX32TOPRINT(temp), speed);

	err = drive_bay_fan->ops->set_value(drive_bay_fan, speed);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: drive bay fan error %d\n", err);
		failure_state |= FAILURE_FAN;
	पूर्ण
पूर्ण

/* PCI slots area fan */
/* This makes the fan speed proportional to the घातer consumed */
अटल काष्ठा wf_pid_param slots_param = अणु
	.पूर्णांकerval	= 1,
	.history_len	= 2,
	.gd		= 0,
	.gp		= 0,
	.gr		= 0x1277952,
	.itarget	= 0,
	.min		= 1560,
	.max		= 3510,
पूर्ण;

अटल व्योम slots_fan_tick(व्योम)
अणु
	s32 घातer;
	पूर्णांक speed;
	पूर्णांक err;

	अगर (!slots_fan || !slots_घातer)
		वापस;
	अगर (!slots_started) अणु
		/* first समय; initialize things */
		prपूर्णांकk(KERN_INFO "windfarm: Slots control loop started.\n");
		wf_pid_init(&slots_pid, &slots_param);
		slots_started = true;
	पूर्ण

	err = slots_घातer->ops->get_value(slots_घातer, &घातer);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: slots power sensor error %d\n",
		       err);
		failure_state |= FAILURE_SENSOR;
		wf_control_set_max(slots_fan);
		वापस;
	पूर्ण
	speed = wf_pid_run(&slots_pid, घातer);
	DBG_LOTS("slots PID power=%d.%.3d speed=%d\n",
		 FIX32TOPRINT(घातer), speed);

	err = slots_fan->ops->set_value(slots_fan, speed);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: slots fan error %d\n", err);
		failure_state |= FAILURE_FAN;
	पूर्ण
पूर्ण

अटल व्योम set_fail_state(व्योम)
अणु
	पूर्णांक i;

	अगर (cpufreq_clamp)
		wf_control_set_max(cpufreq_clamp);
	क्रम (i = 0; i < NR_CPU_FANS; ++i)
		अगर (cpu_fans[i])
			wf_control_set_max(cpu_fans[i]);
	अगर (backside_fan)
		wf_control_set_max(backside_fan);
	अगर (slots_fan)
		wf_control_set_max(slots_fan);
	अगर (drive_bay_fan)
		wf_control_set_max(drive_bay_fan);
पूर्ण

अटल व्योम pm112_tick(व्योम)
अणु
	पूर्णांक i, last_failure;

	अगर (!started) अणु
		started = true;
		prपूर्णांकk(KERN_INFO "windfarm: CPUs control loops started.\n");
		क्रम (i = 0; i < nr_cores; ++i) अणु
			अगर (create_cpu_loop(i) < 0) अणु
				failure_state = FAILURE_PERM;
				set_fail_state();
				अवरोध;
			पूर्ण
		पूर्ण
		DBG_LOTS("cpu_all_tmax=%d.%03d\n", FIX32TOPRINT(cpu_all_पंचांगax));

#अगर_घोषित HACKED_OVERTEMP
		cpu_all_पंचांगax = 60 << 16;
#पूर्ण_अगर
	पूर्ण

	/* Permanent failure, bail out */
	अगर (failure_state & FAILURE_PERM)
		वापस;
	/* Clear all failure bits except low overtemp which will be eventually
	 * cleared by the control loop itself
	 */
	last_failure = failure_state;
	failure_state &= FAILURE_LOW_OVERTEMP;
	cpu_fans_tick();
	backside_fan_tick();
	slots_fan_tick();
	drive_bay_fan_tick();

	DBG_LOTS("last_failure: 0x%x, failure_state: %x\n",
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

अटल व्योम pm112_new_control(काष्ठा wf_control *ct)
अणु
	पूर्णांक i, max_exhaust;

	अगर (cpufreq_clamp == शून्य && !म_भेद(ct->name, "cpufreq-clamp")) अणु
		अगर (wf_get_control(ct) == 0)
			cpufreq_clamp = ct;
	पूर्ण

	क्रम (i = 0; i < NR_CPU_FANS; ++i) अणु
		अगर (!म_भेद(ct->name, cpu_fan_names[i])) अणु
			अगर (cpu_fans[i] == शून्य && wf_get_control(ct) == 0)
				cpu_fans[i] = ct;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i >= NR_CPU_FANS) अणु
		/* not a CPU fan, try the others */
		अगर (!म_भेद(ct->name, "backside-fan")) अणु
			अगर (backside_fan == शून्य && wf_get_control(ct) == 0)
				backside_fan = ct;
		पूर्ण अन्यथा अगर (!म_भेद(ct->name, "slots-fan")) अणु
			अगर (slots_fan == शून्य && wf_get_control(ct) == 0)
				slots_fan = ct;
		पूर्ण अन्यथा अगर (!म_भेद(ct->name, "drive-bay-fan")) अणु
			अगर (drive_bay_fan == शून्य && wf_get_control(ct) == 0)
				drive_bay_fan = ct;
		पूर्ण
		वापस;
	पूर्ण

	क्रम (i = 0; i < CPU_FANS_REQD; ++i)
		अगर (cpu_fans[i] == शून्य)
			वापस;

	/* work out pump scaling factors */
	max_exhaust = cpu_fans[0]->ops->get_max(cpu_fans[0]);
	क्रम (i = FIRST_PUMP; i <= LAST_PUMP; ++i)
		अगर ((ct = cpu_fans[i]) != शून्य)
			cpu_fan_scale[i] =
				ct->ops->get_max(ct) * 100 / max_exhaust;

	have_all_controls = 1;
पूर्ण

अटल व्योम pm112_new_sensor(काष्ठा wf_sensor *sr)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!म_भेदन(sr->name, "cpu-temp-", 9)) अणु
		i = sr->name[9] - '0';
		अगर (sr->name[10] == 0 && i < NR_CORES &&
		    sens_cpu_temp[i] == शून्य && wf_get_sensor(sr) == 0)
			sens_cpu_temp[i] = sr;

	पूर्ण अन्यथा अगर (!म_भेदन(sr->name, "cpu-power-", 10)) अणु
		i = sr->name[10] - '0';
		अगर (sr->name[11] == 0 && i < NR_CORES &&
		    sens_cpu_घातer[i] == शून्य && wf_get_sensor(sr) == 0)
			sens_cpu_घातer[i] = sr;
	पूर्ण अन्यथा अगर (!म_भेद(sr->name, "hd-temp")) अणु
		अगर (hd_temp == शून्य && wf_get_sensor(sr) == 0)
			hd_temp = sr;
	पूर्ण अन्यथा अगर (!म_भेद(sr->name, "slots-power")) अणु
		अगर (slots_घातer == शून्य && wf_get_sensor(sr) == 0)
			slots_घातer = sr;
	पूर्ण अन्यथा अगर (!म_भेद(sr->name, "backside-temp")) अणु
		अगर (u4_temp == शून्य && wf_get_sensor(sr) == 0)
			u4_temp = sr;
	पूर्ण अन्यथा
		वापस;

	/* check अगर we have all the sensors we need */
	क्रम (i = 0; i < nr_cores; ++i)
		अगर (sens_cpu_temp[i] == शून्य || sens_cpu_घातer[i] == शून्य)
			वापस;

	have_all_sensors = 1;
पूर्ण

अटल पूर्णांक pm112_wf_notअगरy(काष्ठा notअगरier_block *self,
			   अचिन्हित दीर्घ event, व्योम *data)
अणु
	चयन (event) अणु
	हाल WF_EVENT_NEW_SENSOR:
		pm112_new_sensor(data);
		अवरोध;
	हाल WF_EVENT_NEW_CONTROL:
		pm112_new_control(data);
		अवरोध;
	हाल WF_EVENT_TICK:
		अगर (have_all_controls && have_all_sensors)
			pm112_tick();
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block pm112_events = अणु
	.notअगरier_call = pm112_wf_notअगरy,
पूर्ण;

अटल पूर्णांक wf_pm112_probe(काष्ठा platक्रमm_device *dev)
अणु
	wf_रेजिस्टर_client(&pm112_events);
	वापस 0;
पूर्ण

अटल पूर्णांक wf_pm112_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	wf_unरेजिस्टर_client(&pm112_events);
	/* should release all sensors and controls */
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wf_pm112_driver = अणु
	.probe = wf_pm112_probe,
	.हटाओ = wf_pm112_हटाओ,
	.driver = अणु
		.name = "windfarm",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init wf_pm112_init(व्योम)
अणु
	काष्ठा device_node *cpu;

	अगर (!of_machine_is_compatible("PowerMac11,2"))
		वापस -ENODEV;

	/* Count the number of CPU cores */
	nr_cores = 0;
	क्रम_each_node_by_type(cpu, "cpu")
		++nr_cores;

	prपूर्णांकk(KERN_INFO "windfarm: initializing for dual-core desktop G5\n");

#अगर_घोषित MODULE
	request_module("windfarm_smu_controls");
	request_module("windfarm_smu_sensors");
	request_module("windfarm_smu_sat");
	request_module("windfarm_lm75_sensor");
	request_module("windfarm_max6690_sensor");
	request_module("windfarm_cpufreq_clamp");

#पूर्ण_अगर /* MODULE */

	platक्रमm_driver_रेजिस्टर(&wf_pm112_driver);
	वापस 0;
पूर्ण

अटल व्योम __निकास wf_pm112_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&wf_pm112_driver);
पूर्ण

module_init(wf_pm112_init);
module_निकास(wf_pm112_निकास);

MODULE_AUTHOR("Paul Mackerras <paulus@samba.org>");
MODULE_DESCRIPTION("Thermal control for PowerMac11,2");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:windfarm");
