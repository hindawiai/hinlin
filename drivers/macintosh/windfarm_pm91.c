<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control. SMU based 1 CPU desktop control loops
 *
 * (c) Copyright 2005 Benjamin Herrenschmidt, IBM Corp.
 *                    <benh@kernel.crashing.org>
 *
 * The algorithm used is the PID control algorithm, used the same
 * way the published Darwin code करोes, using the same values that
 * are present in the Darwin 8.2 snapshot property lists (note however
 * that none of the code has been re-used, it's a complete re-implementation
 *
 * The various control loops found in Darwin config file are:
 *
 * PowerMac9,1
 * ===========
 *
 * Has 3 control loops: CPU fans is similar to PowerMac8,1 (though it करोesn't
 * try to play with other control loops fans). Drive bay is rather basic PID
 * with one sensor and one fan. Slots area is a bit dअगरferent as the Darwin
 * driver is supposed to be capable of working in a special "AGP" mode which
 * involves the presence of an AGP sensor and an AGP fan (possibly on the
 * AGP card itself). I can't deal with that special mode as I don't have
 * access to those additional sensor/fans क्रम now (though ultimately, it would
 * be possible to add sensor objects क्रम them) so I'm only implementing the
 * basic PCI slot control loop
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/kmod.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/smu.h>

#समावेश "windfarm.h"
#समावेश "windfarm_pid.h"

#घोषणा VERSION "0.4"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(args...)	prपूर्णांकk(args)
#अन्यथा
#घोषणा DBG(args...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

/* define this to क्रमce CPU overtemp to 74 degree, useful क्रम testing
 * the overtemp code
 */
#अघोषित HACKED_OVERTEMP

/* Controls & sensors */
अटल काष्ठा wf_sensor	*sensor_cpu_घातer;
अटल काष्ठा wf_sensor	*sensor_cpu_temp;
अटल काष्ठा wf_sensor	*sensor_hd_temp;
अटल काष्ठा wf_sensor	*sensor_slots_घातer;
अटल काष्ठा wf_control *fan_cpu_मुख्य;
अटल काष्ठा wf_control *fan_cpu_second;
अटल काष्ठा wf_control *fan_cpu_third;
अटल काष्ठा wf_control *fan_hd;
अटल काष्ठा wf_control *fan_slots;
अटल काष्ठा wf_control *cpufreq_clamp;

/* Set to kick the control loop पूर्णांकo lअगरe */
अटल पूर्णांक wf_smu_all_controls_ok, wf_smu_all_sensors_ok;
अटल bool wf_smu_started;
अटल bool wf_smu_overtemp;

/* Failure handling.. could be nicer */
#घोषणा FAILURE_FAN		0x01
#घोषणा FAILURE_SENSOR		0x02
#घोषणा FAILURE_OVERTEMP	0x04

अटल अचिन्हित पूर्णांक wf_smu_failure_state;
अटल पूर्णांक wf_smu_पढ़ोjust, wf_smu_skipping;

/*
 * ****** CPU Fans Control Loop ******
 *
 */


#घोषणा WF_SMU_CPU_FANS_INTERVAL	1
#घोषणा WF_SMU_CPU_FANS_MAX_HISTORY	16

/* State data used by the cpu fans control loop
 */
काष्ठा wf_smu_cpu_fans_state अणु
	पूर्णांक			ticks;
	s32			cpu_setpoपूर्णांक;
	काष्ठा wf_cpu_pid_state	pid;
पूर्ण;

अटल काष्ठा wf_smu_cpu_fans_state *wf_smu_cpu_fans;



/*
 * ****** Drive Fan Control Loop ******
 *
 */

काष्ठा wf_smu_drive_fans_state अणु
	पूर्णांक			ticks;
	s32			setpoपूर्णांक;
	काष्ठा wf_pid_state	pid;
पूर्ण;

अटल काष्ठा wf_smu_drive_fans_state *wf_smu_drive_fans;

/*
 * ****** Slots Fan Control Loop ******
 *
 */

काष्ठा wf_smu_slots_fans_state अणु
	पूर्णांक			ticks;
	s32			setpoपूर्णांक;
	काष्ठा wf_pid_state	pid;
पूर्ण;

अटल काष्ठा wf_smu_slots_fans_state *wf_smu_slots_fans;

/*
 * ***** Implementation *****
 *
 */


अटल व्योम wf_smu_create_cpu_fans(व्योम)
अणु
	काष्ठा wf_cpu_pid_param pid_param;
	स्थिर काष्ठा smu_sdbp_header *hdr;
	काष्ठा smu_sdbp_cpupiddata *piddata;
	काष्ठा smu_sdbp_fvt *fvt;
	s32 पंचांगax, tdelta, maxघात, घातadj;

	/* First, locate the PID params in SMU SBD */
	hdr = smu_get_sdb_partition(SMU_SDB_CPUPIDDATA_ID, शून्य);
	अगर (hdr == 0) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: CPU PID fan config not found "
		       "max fan speed\n");
		जाओ fail;
	पूर्ण
	piddata = (काष्ठा smu_sdbp_cpupiddata *)&hdr[1];

	/* Get the FVT params क्रम operating poपूर्णांक 0 (the only supported one
	 * क्रम now) in order to get पंचांगax
	 */
	hdr = smu_get_sdb_partition(SMU_SDB_FVT_ID, शून्य);
	अगर (hdr) अणु
		fvt = (काष्ठा smu_sdbp_fvt *)&hdr[1];
		पंचांगax = ((s32)fvt->maxtemp) << 16;
	पूर्ण अन्यथा
		पंचांगax = 0x5e0000; /* 94 degree शेष */

	/* Alloc & initialize state */
	wf_smu_cpu_fans = kदो_स्मृति(माप(काष्ठा wf_smu_cpu_fans_state),
				  GFP_KERNEL);
	अगर (wf_smu_cpu_fans == शून्य)
		जाओ fail;
       	wf_smu_cpu_fans->ticks = 1;

	/* Fill PID params */
	pid_param.पूर्णांकerval = WF_SMU_CPU_FANS_INTERVAL;
	pid_param.history_len = piddata->history_len;
	अगर (pid_param.history_len > WF_CPU_PID_MAX_HISTORY) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: History size overflow on "
		       "CPU control loop (%d)\n", piddata->history_len);
		pid_param.history_len = WF_CPU_PID_MAX_HISTORY;
	पूर्ण
	pid_param.gd = piddata->gd;
	pid_param.gp = piddata->gp;
	pid_param.gr = piddata->gr / pid_param.history_len;

	tdelta = ((s32)piddata->target_temp_delta) << 16;
	maxघात = ((s32)piddata->max_घातer) << 16;
	घातadj = ((s32)piddata->घातer_adj) << 16;

	pid_param.पंचांगax = पंचांगax;
	pid_param.ttarget = पंचांगax - tdelta;
	pid_param.pmaxadj = maxघात - घातadj;

	pid_param.min = wf_control_get_min(fan_cpu_मुख्य);
	pid_param.max = wf_control_get_max(fan_cpu_मुख्य);

	wf_cpu_pid_init(&wf_smu_cpu_fans->pid, &pid_param);

	DBG("wf: CPU Fan control initialized.\n");
	DBG("    ttarget=%d.%03d, tmax=%d.%03d, min=%d RPM, max=%d RPM\n",
	    FIX32TOPRINT(pid_param.ttarget), FIX32TOPRINT(pid_param.पंचांगax),
	    pid_param.min, pid_param.max);

	वापस;

 fail:
	prपूर्णांकk(KERN_WARNING "windfarm: CPU fan config not found\n"
	       "for this machine model, max fan speed\n");

	अगर (cpufreq_clamp)
		wf_control_set_max(cpufreq_clamp);
	अगर (fan_cpu_मुख्य)
		wf_control_set_max(fan_cpu_मुख्य);
पूर्ण

अटल व्योम wf_smu_cpu_fans_tick(काष्ठा wf_smu_cpu_fans_state *st)
अणु
	s32 new_setpoपूर्णांक, temp, घातer;
	पूर्णांक rc;

	अगर (--st->ticks != 0) अणु
		अगर (wf_smu_पढ़ोjust)
			जाओ पढ़ोjust;
		वापस;
	पूर्ण
	st->ticks = WF_SMU_CPU_FANS_INTERVAL;

	rc = wf_sensor_get(sensor_cpu_temp, &temp);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: CPU temp sensor error %d\n",
		       rc);
		wf_smu_failure_state |= FAILURE_SENSOR;
		वापस;
	पूर्ण

	rc = wf_sensor_get(sensor_cpu_घातer, &घातer);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: CPU power sensor error %d\n",
		       rc);
		wf_smu_failure_state |= FAILURE_SENSOR;
		वापस;
	पूर्ण

	DBG("wf_smu: CPU Fans tick ! CPU temp: %d.%03d, power: %d.%03d\n",
	    FIX32TOPRINT(temp), FIX32TOPRINT(घातer));

#अगर_घोषित HACKED_OVERTEMP
	अगर (temp > 0x4a0000)
		wf_smu_failure_state |= FAILURE_OVERTEMP;
#अन्यथा
	अगर (temp > st->pid.param.पंचांगax)
		wf_smu_failure_state |= FAILURE_OVERTEMP;
#पूर्ण_अगर
	new_setpoपूर्णांक = wf_cpu_pid_run(&st->pid, घातer, temp);

	DBG("wf_smu: new_setpoint: %d RPM\n", (पूर्णांक)new_setpoपूर्णांक);

	अगर (st->cpu_setpoपूर्णांक == new_setpoपूर्णांक)
		वापस;
	st->cpu_setpoपूर्णांक = new_setpoपूर्णांक;
 पढ़ोjust:
	अगर (fan_cpu_मुख्य && wf_smu_failure_state == 0) अणु
		rc = wf_control_set(fan_cpu_मुख्य, st->cpu_setpoपूर्णांक);
		अगर (rc) अणु
			prपूर्णांकk(KERN_WARNING "windfarm: CPU main fan"
			       " error %d\n", rc);
			wf_smu_failure_state |= FAILURE_FAN;
		पूर्ण
	पूर्ण
	अगर (fan_cpu_second && wf_smu_failure_state == 0) अणु
		rc = wf_control_set(fan_cpu_second, st->cpu_setpoपूर्णांक);
		अगर (rc) अणु
			prपूर्णांकk(KERN_WARNING "windfarm: CPU second fan"
			       " error %d\n", rc);
			wf_smu_failure_state |= FAILURE_FAN;
		पूर्ण
	पूर्ण
	अगर (fan_cpu_third && wf_smu_failure_state == 0) अणु
		rc = wf_control_set(fan_cpu_third, st->cpu_setpoपूर्णांक);
		अगर (rc) अणु
			prपूर्णांकk(KERN_WARNING "windfarm: CPU third fan"
			       " error %d\n", rc);
			wf_smu_failure_state |= FAILURE_FAN;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम wf_smu_create_drive_fans(व्योम)
अणु
	काष्ठा wf_pid_param param = अणु
		.पूर्णांकerval	= 5,
		.history_len	= 2,
		.gd		= 0x01e00000,
		.gp		= 0x00500000,
		.gr		= 0x00000000,
		.itarget	= 0x00200000,
	पूर्ण;

	/* Alloc & initialize state */
	wf_smu_drive_fans = kदो_स्मृति(माप(काष्ठा wf_smu_drive_fans_state),
					GFP_KERNEL);
	अगर (wf_smu_drive_fans == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: Memory allocation error"
		       " max fan speed\n");
		जाओ fail;
	पूर्ण
       	wf_smu_drive_fans->ticks = 1;

	/* Fill PID params */
	param.additive = (fan_hd->type == WF_CONTROL_RPM_FAN);
	param.min = wf_control_get_min(fan_hd);
	param.max = wf_control_get_max(fan_hd);
	wf_pid_init(&wf_smu_drive_fans->pid, &param);

	DBG("wf: Drive Fan control initialized.\n");
	DBG("    itarged=%d.%03d, min=%d RPM, max=%d RPM\n",
	    FIX32TOPRINT(param.itarget), param.min, param.max);
	वापस;

 fail:
	अगर (fan_hd)
		wf_control_set_max(fan_hd);
पूर्ण

अटल व्योम wf_smu_drive_fans_tick(काष्ठा wf_smu_drive_fans_state *st)
अणु
	s32 new_setpoपूर्णांक, temp;
	पूर्णांक rc;

	अगर (--st->ticks != 0) अणु
		अगर (wf_smu_पढ़ोjust)
			जाओ पढ़ोjust;
		वापस;
	पूर्ण
	st->ticks = st->pid.param.पूर्णांकerval;

	rc = wf_sensor_get(sensor_hd_temp, &temp);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: HD temp sensor error %d\n",
		       rc);
		wf_smu_failure_state |= FAILURE_SENSOR;
		वापस;
	पूर्ण

	DBG("wf_smu: Drive Fans tick ! HD temp: %d.%03d\n",
	    FIX32TOPRINT(temp));

	अगर (temp > (st->pid.param.itarget + 0x50000))
		wf_smu_failure_state |= FAILURE_OVERTEMP;

	new_setpoपूर्णांक = wf_pid_run(&st->pid, temp);

	DBG("wf_smu: new_setpoint: %d\n", (पूर्णांक)new_setpoपूर्णांक);

	अगर (st->setpoपूर्णांक == new_setpoपूर्णांक)
		वापस;
	st->setpoपूर्णांक = new_setpoपूर्णांक;
 पढ़ोjust:
	अगर (fan_hd && wf_smu_failure_state == 0) अणु
		rc = wf_control_set(fan_hd, st->setpoपूर्णांक);
		अगर (rc) अणु
			prपूर्णांकk(KERN_WARNING "windfarm: HD fan error %d\n",
			       rc);
			wf_smu_failure_state |= FAILURE_FAN;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम wf_smu_create_slots_fans(व्योम)
अणु
	काष्ठा wf_pid_param param = अणु
		.पूर्णांकerval	= 1,
		.history_len	= 8,
		.gd		= 0x00000000,
		.gp		= 0x00000000,
		.gr		= 0x00020000,
		.itarget	= 0x00000000
	पूर्ण;

	/* Alloc & initialize state */
	wf_smu_slots_fans = kदो_स्मृति(माप(काष्ठा wf_smu_slots_fans_state),
					GFP_KERNEL);
	अगर (wf_smu_slots_fans == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: Memory allocation error"
		       " max fan speed\n");
		जाओ fail;
	पूर्ण
       	wf_smu_slots_fans->ticks = 1;

	/* Fill PID params */
	param.additive = (fan_slots->type == WF_CONTROL_RPM_FAN);
	param.min = wf_control_get_min(fan_slots);
	param.max = wf_control_get_max(fan_slots);
	wf_pid_init(&wf_smu_slots_fans->pid, &param);

	DBG("wf: Slots Fan control initialized.\n");
	DBG("    itarged=%d.%03d, min=%d RPM, max=%d RPM\n",
	    FIX32TOPRINT(param.itarget), param.min, param.max);
	वापस;

 fail:
	अगर (fan_slots)
		wf_control_set_max(fan_slots);
पूर्ण

अटल व्योम wf_smu_slots_fans_tick(काष्ठा wf_smu_slots_fans_state *st)
अणु
	s32 new_setpoपूर्णांक, घातer;
	पूर्णांक rc;

	अगर (--st->ticks != 0) अणु
		अगर (wf_smu_पढ़ोjust)
			जाओ पढ़ोjust;
		वापस;
	पूर्ण
	st->ticks = st->pid.param.पूर्णांकerval;

	rc = wf_sensor_get(sensor_slots_घातer, &घातer);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: Slots power sensor error %d\n",
		       rc);
		wf_smu_failure_state |= FAILURE_SENSOR;
		वापस;
	पूर्ण

	DBG("wf_smu: Slots Fans tick ! Slots power: %d.%03d\n",
	    FIX32TOPRINT(घातer));

#अगर 0 /* Check what makes a good overtemp condition */
	अगर (घातer > (st->pid.param.itarget + 0x50000))
		wf_smu_failure_state |= FAILURE_OVERTEMP;
#पूर्ण_अगर

	new_setpoपूर्णांक = wf_pid_run(&st->pid, घातer);

	DBG("wf_smu: new_setpoint: %d\n", (पूर्णांक)new_setpoपूर्णांक);

	अगर (st->setpoपूर्णांक == new_setpoपूर्णांक)
		वापस;
	st->setpoपूर्णांक = new_setpoपूर्णांक;
 पढ़ोjust:
	अगर (fan_slots && wf_smu_failure_state == 0) अणु
		rc = wf_control_set(fan_slots, st->setpoपूर्णांक);
		अगर (rc) अणु
			prपूर्णांकk(KERN_WARNING "windfarm: Slots fan error %d\n",
			       rc);
			wf_smu_failure_state |= FAILURE_FAN;
		पूर्ण
	पूर्ण
पूर्ण


/*
 * ****** Setup / Init / Misc ... ******
 *
 */

अटल व्योम wf_smu_tick(व्योम)
अणु
	अचिन्हित पूर्णांक last_failure = wf_smu_failure_state;
	अचिन्हित पूर्णांक new_failure;

	अगर (!wf_smu_started) अणु
		DBG("wf: creating control loops !\n");
		wf_smu_create_drive_fans();
		wf_smu_create_slots_fans();
		wf_smu_create_cpu_fans();
		wf_smu_started = true;
	पूर्ण

	/* Skipping ticks */
	अगर (wf_smu_skipping && --wf_smu_skipping)
		वापस;

	wf_smu_failure_state = 0;
	अगर (wf_smu_drive_fans)
		wf_smu_drive_fans_tick(wf_smu_drive_fans);
	अगर (wf_smu_slots_fans)
		wf_smu_slots_fans_tick(wf_smu_slots_fans);
	अगर (wf_smu_cpu_fans)
		wf_smu_cpu_fans_tick(wf_smu_cpu_fans);

	wf_smu_पढ़ोjust = 0;
	new_failure = wf_smu_failure_state & ~last_failure;

	/* If entering failure mode, clamp cpufreq and ramp all
	 * fans to full speed.
	 */
	अगर (wf_smu_failure_state && !last_failure) अणु
		अगर (cpufreq_clamp)
			wf_control_set_max(cpufreq_clamp);
		अगर (fan_cpu_मुख्य)
			wf_control_set_max(fan_cpu_मुख्य);
		अगर (fan_cpu_second)
			wf_control_set_max(fan_cpu_second);
		अगर (fan_cpu_third)
			wf_control_set_max(fan_cpu_third);
		अगर (fan_hd)
			wf_control_set_max(fan_hd);
		अगर (fan_slots)
			wf_control_set_max(fan_slots);
	पूर्ण

	/* If leaving failure mode, unclamp cpufreq and पढ़ोjust
	 * all fans on next iteration
	 */
	अगर (!wf_smu_failure_state && last_failure) अणु
		अगर (cpufreq_clamp)
			wf_control_set_min(cpufreq_clamp);
		wf_smu_पढ़ोjust = 1;
	पूर्ण

	/* Overtemp condition detected, notअगरy and start skipping a couple
	 * ticks to let the temperature go करोwn
	 */
	अगर (new_failure & FAILURE_OVERTEMP) अणु
		wf_set_overtemp();
		wf_smu_skipping = 2;
		wf_smu_overtemp = true;
	पूर्ण

	/* We only clear the overtemp condition अगर overtemp is cleared
	 * _and_ no other failure is present. Since a sensor error will
	 * clear the overtemp condition (can't measure temperature) at
	 * the control loop levels, but we करोn't want to keep it clear
	 * here in this हाल
	 */
	अगर (!wf_smu_failure_state && wf_smu_overtemp) अणु
		wf_clear_overtemp();
		wf_smu_overtemp = false;
	पूर्ण
पूर्ण


अटल व्योम wf_smu_new_control(काष्ठा wf_control *ct)
अणु
	अगर (wf_smu_all_controls_ok)
		वापस;

	अगर (fan_cpu_मुख्य == शून्य && !म_भेद(ct->name, "cpu-rear-fan-0")) अणु
		अगर (wf_get_control(ct) == 0)
			fan_cpu_मुख्य = ct;
	पूर्ण

	अगर (fan_cpu_second == शून्य && !म_भेद(ct->name, "cpu-rear-fan-1")) अणु
		अगर (wf_get_control(ct) == 0)
			fan_cpu_second = ct;
	पूर्ण

	अगर (fan_cpu_third == शून्य && !म_भेद(ct->name, "cpu-front-fan-0")) अणु
		अगर (wf_get_control(ct) == 0)
			fan_cpu_third = ct;
	पूर्ण

	अगर (cpufreq_clamp == शून्य && !म_भेद(ct->name, "cpufreq-clamp")) अणु
		अगर (wf_get_control(ct) == 0)
			cpufreq_clamp = ct;
	पूर्ण

	अगर (fan_hd == शून्य && !म_भेद(ct->name, "drive-bay-fan")) अणु
		अगर (wf_get_control(ct) == 0)
			fan_hd = ct;
	पूर्ण

	अगर (fan_slots == शून्य && !म_भेद(ct->name, "slots-fan")) अणु
		अगर (wf_get_control(ct) == 0)
			fan_slots = ct;
	पूर्ण

	अगर (fan_cpu_मुख्य && (fan_cpu_second || fan_cpu_third) && fan_hd &&
	    fan_slots && cpufreq_clamp)
		wf_smu_all_controls_ok = 1;
पूर्ण

अटल व्योम wf_smu_new_sensor(काष्ठा wf_sensor *sr)
अणु
	अगर (wf_smu_all_sensors_ok)
		वापस;

	अगर (sensor_cpu_घातer == शून्य && !म_भेद(sr->name, "cpu-power")) अणु
		अगर (wf_get_sensor(sr) == 0)
			sensor_cpu_घातer = sr;
	पूर्ण

	अगर (sensor_cpu_temp == शून्य && !म_भेद(sr->name, "cpu-temp")) अणु
		अगर (wf_get_sensor(sr) == 0)
			sensor_cpu_temp = sr;
	पूर्ण

	अगर (sensor_hd_temp == शून्य && !म_भेद(sr->name, "hd-temp")) अणु
		अगर (wf_get_sensor(sr) == 0)
			sensor_hd_temp = sr;
	पूर्ण

	अगर (sensor_slots_घातer == शून्य && !म_भेद(sr->name, "slots-power")) अणु
		अगर (wf_get_sensor(sr) == 0)
			sensor_slots_घातer = sr;
	पूर्ण

	अगर (sensor_cpu_घातer && sensor_cpu_temp &&
	    sensor_hd_temp && sensor_slots_घातer)
		wf_smu_all_sensors_ok = 1;
पूर्ण


अटल पूर्णांक wf_smu_notअगरy(काष्ठा notअगरier_block *self,
			       अचिन्हित दीर्घ event, व्योम *data)
अणु
	चयन(event) अणु
	हाल WF_EVENT_NEW_CONTROL:
		DBG("wf: new control %s detected\n",
		    ((काष्ठा wf_control *)data)->name);
		wf_smu_new_control(data);
		wf_smu_पढ़ोjust = 1;
		अवरोध;
	हाल WF_EVENT_NEW_SENSOR:
		DBG("wf: new sensor %s detected\n",
		    ((काष्ठा wf_sensor *)data)->name);
		wf_smu_new_sensor(data);
		अवरोध;
	हाल WF_EVENT_TICK:
		अगर (wf_smu_all_controls_ok && wf_smu_all_sensors_ok)
			wf_smu_tick();
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block wf_smu_events = अणु
	.notअगरier_call	= wf_smu_notअगरy,
पूर्ण;

अटल पूर्णांक wf_init_pm(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "windfarm: Initializing for Desktop G5 model\n");

	वापस 0;
पूर्ण

अटल पूर्णांक wf_smu_probe(काष्ठा platक्रमm_device *ddev)
अणु
	wf_रेजिस्टर_client(&wf_smu_events);

	वापस 0;
पूर्ण

अटल पूर्णांक wf_smu_हटाओ(काष्ठा platक्रमm_device *ddev)
अणु
	wf_unरेजिस्टर_client(&wf_smu_events);

	/* XXX We करोn't have yet a guarantee that our callback isn't
	 * in progress when वापसing from wf_unरेजिस्टर_client, so
	 * we add an arbitrary delay. I'll have to fix that in the core
	 */
	msleep(1000);

	/* Release all sensors */
	/* One more crappy race: I करोn't think we have any guarantee here
	 * that the attribute callback won't race with the sensor beeing
	 * disposed of, and I'm not 100% certain what best way to deal
	 * with that except by adding locks all over... I'll करो that
	 * eventually but heh, who ever rmmod this module anyway ?
	 */
	अगर (sensor_cpu_घातer)
		wf_put_sensor(sensor_cpu_घातer);
	अगर (sensor_cpu_temp)
		wf_put_sensor(sensor_cpu_temp);
	अगर (sensor_hd_temp)
		wf_put_sensor(sensor_hd_temp);
	अगर (sensor_slots_घातer)
		wf_put_sensor(sensor_slots_घातer);

	/* Release all controls */
	अगर (fan_cpu_मुख्य)
		wf_put_control(fan_cpu_मुख्य);
	अगर (fan_cpu_second)
		wf_put_control(fan_cpu_second);
	अगर (fan_cpu_third)
		wf_put_control(fan_cpu_third);
	अगर (fan_hd)
		wf_put_control(fan_hd);
	अगर (fan_slots)
		wf_put_control(fan_slots);
	अगर (cpufreq_clamp)
		wf_put_control(cpufreq_clamp);

	/* Destroy control loops state काष्ठाures */
	kमुक्त(wf_smu_slots_fans);
	kमुक्त(wf_smu_drive_fans);
	kमुक्त(wf_smu_cpu_fans);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wf_smu_driver = अणु
        .probe = wf_smu_probe,
        .हटाओ = wf_smu_हटाओ,
	.driver = अणु
		.name = "windfarm",
	पूर्ण,
पूर्ण;


अटल पूर्णांक __init wf_smu_init(व्योम)
अणु
	पूर्णांक rc = -ENODEV;

	अगर (of_machine_is_compatible("PowerMac9,1"))
		rc = wf_init_pm();

	अगर (rc == 0) अणु
#अगर_घोषित MODULE
		request_module("windfarm_smu_controls");
		request_module("windfarm_smu_sensors");
		request_module("windfarm_lm75_sensor");
		request_module("windfarm_cpufreq_clamp");

#पूर्ण_अगर /* MODULE */
		platक्रमm_driver_रेजिस्टर(&wf_smu_driver);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम __निकास wf_smu_निकास(व्योम)
अणु

	platक्रमm_driver_unरेजिस्टर(&wf_smu_driver);
पूर्ण


module_init(wf_smu_init);
module_निकास(wf_smu_निकास);

MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("Thermal control logic for PowerMac9,1");
MODULE_LICENSE("GPL");

MODULE_ALIAS("platform:windfarm");
