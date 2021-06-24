<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control. iMac G5
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
 * PowerMac8,1 and PowerMac8,2
 * ===========================
 *
 * System Fans control loop. Dअगरferent based on models. In addition to the
 * usual PID algorithm, the control loop माला_लो 2 additional pairs of linear
 * scaling factors (scale/offsets) expressed as 4.12 fixed poपूर्णांक values
 * चिन्हित offset, अचिन्हित scale)
 *
 * The tarमाला_लो are modअगरied such as:
 *  - the linked control (second control) माला_लो the target value as-is
 *    (typically the drive fan)
 *  - the मुख्य control (first control) माला_लो the target value scaled with
 *    the first pair of factors, and is then modअगरied as below
 *  - the value of the target of the CPU Fan control loop is retrieved,
 *    scaled with the second pair of factors, and the max of that and
 *    the scaled target is applied to the मुख्य control.
 *
 * # model_id: 2
 *   controls       : प्रणाली-fan, drive-bay-fan
 *   sensors        : hd-temp
 *   PID params     : G_d = 0x15400000
 *                    G_p = 0x00200000
 *                    G_r = 0x000002fd
 *                    History = 2 entries
 *                    Input target = 0x3a0000
 *                    Interval = 5s
 *   linear-factors : offset = 0xff38 scale  = 0x0ccd
 *                    offset = 0x0208 scale  = 0x07ae
 *
 * # model_id: 3
 *   controls       : प्रणाली-fan, drive-bay-fan
 *   sensors        : hd-temp
 *   PID params     : G_d = 0x08e00000
 *                    G_p = 0x00566666
 *                    G_r = 0x0000072b
 *                    History = 2 entries
 *                    Input target = 0x350000
 *                    Interval = 5s
 *   linear-factors : offset = 0xff38 scale  = 0x0ccd
 *                    offset = 0x0000 scale  = 0x0000
 *
 * # model_id: 5
 *   controls       : प्रणाली-fan
 *   sensors        : hd-temp
 *   PID params     : G_d = 0x15400000
 *                    G_p = 0x00233333
 *                    G_r = 0x000002fd
 *                    History = 2 entries
 *                    Input target = 0x3a0000
 *                    Interval = 5s
 *   linear-factors : offset = 0x0000 scale  = 0x1000
 *                    offset = 0x0091 scale  = 0x0bae
 *
 * CPU Fan control loop. The loop is identical क्रम all models. it
 * has an additional pair of scaling factor. This is used to scale the
 * प्रणालीs fan control loop target result (the one beक्रमe it माला_लो scaled
 * by the System Fans control loop itself). Then, the max value of the
 * calculated target value and प्रणाली fan value is sent to the fans
 *
 *   controls       : cpu-fan
 *   sensors        : cpu-temp cpu-घातer
 *   PID params     : From SMU sdb partition
 *   linear-factors : offset = 0xfb50 scale  = 0x1000
 *
 * CPU Slew control loop. Not implemented. The cpufreq driver in linux is
 * completely separate क्रम now, though we could find a way to link it, either
 * as a client reacting to overtemp notअगरications, or directling monitoring
 * the CPU temperature
 *
 * WARNING ! The CPU control loop requires the CPU पंचांगax क्रम the current
 * operating poपूर्णांक. However, we currently are completely separated from
 * the cpufreq driver and thus करो not know what the current operating
 * poपूर्णांक is. Fortunately, we also करो not have any hardware supporting anything
 * but operating poपूर्णांक 0 at the moment, thus we just peek that value directly
 * from the SDB partition. If we ever end up with actually slewing the प्रणाली
 * घड़ी and thus changing operating poपूर्णांकs, we'll have to find a way to
 * communicate with the CPU freq driver;
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

अटल पूर्णांक wf_smu_mach_model;	/* machine model id */

/* Controls & sensors */
अटल काष्ठा wf_sensor	*sensor_cpu_घातer;
अटल काष्ठा wf_sensor	*sensor_cpu_temp;
अटल काष्ठा wf_sensor	*sensor_hd_temp;
अटल काष्ठा wf_control *fan_cpu_मुख्य;
अटल काष्ठा wf_control *fan_hd;
अटल काष्ठा wf_control *fan_प्रणाली;
अटल काष्ठा wf_control *cpufreq_clamp;

/* Set to kick the control loop पूर्णांकo lअगरe */
अटल पूर्णांक wf_smu_all_controls_ok, wf_smu_all_sensors_ok;
अटल bool wf_smu_started;

/* Failure handling.. could be nicer */
#घोषणा FAILURE_FAN		0x01
#घोषणा FAILURE_SENSOR		0x02
#घोषणा FAILURE_OVERTEMP	0x04

अटल अचिन्हित पूर्णांक wf_smu_failure_state;
अटल पूर्णांक wf_smu_पढ़ोjust, wf_smu_skipping;
अटल bool wf_smu_overtemp;

/*
 * ****** System Fans Control Loop ******
 *
 */

/* Parameters क्रम the System Fans control loop. Parameters
 * not in this table such as पूर्णांकerval, history size, ...
 * are common to all versions and thus hard coded क्रम now.
 */
काष्ठा wf_smu_sys_fans_param अणु
	पूर्णांक	model_id;
	s32	itarget;
	s32	gd, gp, gr;

	s16	offset0;
	u16	scale0;
	s16	offset1;
	u16	scale1;
पूर्ण;

#घोषणा WF_SMU_SYS_FANS_INTERVAL	5
#घोषणा WF_SMU_SYS_FANS_HISTORY_SIZE	2

/* State data used by the प्रणाली fans control loop
 */
काष्ठा wf_smu_sys_fans_state अणु
	पूर्णांक			ticks;
	s32			sys_setpoपूर्णांक;
	s32			hd_setpoपूर्णांक;
	s16			offset0;
	u16			scale0;
	s16			offset1;
	u16			scale1;
	काष्ठा wf_pid_state	pid;
पूर्ण;

/*
 * Configs क्रम SMU System Fan control loop
 */
अटल काष्ठा wf_smu_sys_fans_param wf_smu_sys_all_params[] = अणु
	/* Model ID 2 */
	अणु
		.model_id	= 2,
		.itarget	= 0x3a0000,
		.gd		= 0x15400000,
		.gp		= 0x00200000,
		.gr		= 0x000002fd,
		.offset0	= 0xff38,
		.scale0		= 0x0ccd,
		.offset1	= 0x0208,
		.scale1		= 0x07ae,
	पूर्ण,
	/* Model ID 3 */
	अणु
		.model_id	= 3,
		.itarget	= 0x350000,
		.gd		= 0x08e00000,
		.gp		= 0x00566666,
		.gr		= 0x0000072b,
		.offset0	= 0xff38,
		.scale0		= 0x0ccd,
		.offset1	= 0x0000,
		.scale1		= 0x0000,
	पूर्ण,
	/* Model ID 5 */
	अणु
		.model_id	= 5,
		.itarget	= 0x3a0000,
		.gd		= 0x15400000,
		.gp		= 0x00233333,
		.gr		= 0x000002fd,
		.offset0	= 0x0000,
		.scale0		= 0x1000,
		.offset1	= 0x0091,
		.scale1		= 0x0bae,
	पूर्ण,
पूर्ण;
#घोषणा WF_SMU_SYS_FANS_NUM_CONFIGS ARRAY_SIZE(wf_smu_sys_all_params)

अटल काष्ठा wf_smu_sys_fans_state *wf_smu_sys_fans;

/*
 * ****** CPU Fans Control Loop ******
 *
 */


#घोषणा WF_SMU_CPU_FANS_INTERVAL	1
#घोषणा WF_SMU_CPU_FANS_MAX_HISTORY	16
#घोषणा WF_SMU_CPU_FANS_SIBLING_SCALE	0x00001000
#घोषणा WF_SMU_CPU_FANS_SIBLING_OFFSET	0xfffffb50

/* State data used by the cpu fans control loop
 */
काष्ठा wf_smu_cpu_fans_state अणु
	पूर्णांक			ticks;
	s32			cpu_setpoपूर्णांक;
	s32			scale;
	s32			offset;
	काष्ठा wf_cpu_pid_state	pid;
पूर्ण;

अटल काष्ठा wf_smu_cpu_fans_state *wf_smu_cpu_fans;



/*
 * ***** Implementation *****
 *
 */

अटल व्योम wf_smu_create_sys_fans(व्योम)
अणु
	काष्ठा wf_smu_sys_fans_param *param = शून्य;
	काष्ठा wf_pid_param pid_param;
	पूर्णांक i;

	/* First, locate the params क्रम this model */
	क्रम (i = 0; i < WF_SMU_SYS_FANS_NUM_CONFIGS; i++)
		अगर (wf_smu_sys_all_params[i].model_id == wf_smu_mach_model) अणु
			param = &wf_smu_sys_all_params[i];
			अवरोध;
		पूर्ण

	/* No params found, put fans to max */
	अगर (param == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: System fan config not found "
		       "for this machine model, max fan speed\n");
		जाओ fail;
	पूर्ण

	/* Alloc & initialize state */
	wf_smu_sys_fans = kदो_स्मृति(माप(काष्ठा wf_smu_sys_fans_state),
				  GFP_KERNEL);
	अगर (wf_smu_sys_fans == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: Memory allocation error"
		       " max fan speed\n");
		जाओ fail;
	पूर्ण
	wf_smu_sys_fans->ticks = 1;
	wf_smu_sys_fans->scale0 = param->scale0;
	wf_smu_sys_fans->offset0 = param->offset0;
	wf_smu_sys_fans->scale1 = param->scale1;
	wf_smu_sys_fans->offset1 = param->offset1;

	/* Fill PID params */
	pid_param.gd = param->gd;
	pid_param.gp = param->gp;
	pid_param.gr = param->gr;
	pid_param.पूर्णांकerval = WF_SMU_SYS_FANS_INTERVAL;
	pid_param.history_len = WF_SMU_SYS_FANS_HISTORY_SIZE;
	pid_param.itarget = param->itarget;
	pid_param.min = wf_control_get_min(fan_प्रणाली);
	pid_param.max = wf_control_get_max(fan_प्रणाली);
	अगर (fan_hd) अणु
		pid_param.min =
			max(pid_param.min, wf_control_get_min(fan_hd));
		pid_param.max =
			min(pid_param.max, wf_control_get_max(fan_hd));
	पूर्ण
	wf_pid_init(&wf_smu_sys_fans->pid, &pid_param);

	DBG("wf: System Fan control initialized.\n");
	DBG("    itarged=%d.%03d, min=%d RPM, max=%d RPM\n",
	    FIX32TOPRINT(pid_param.itarget), pid_param.min, pid_param.max);
	वापस;

 fail:

	अगर (fan_प्रणाली)
		wf_control_set_max(fan_प्रणाली);
	अगर (fan_hd)
		wf_control_set_max(fan_hd);
पूर्ण

अटल व्योम wf_smu_sys_fans_tick(काष्ठा wf_smu_sys_fans_state *st)
अणु
	s32 new_setpoपूर्णांक, temp, scaled, cputarget;
	पूर्णांक rc;

	अगर (--st->ticks != 0) अणु
		अगर (wf_smu_पढ़ोjust)
			जाओ पढ़ोjust;
		वापस;
	पूर्ण
	st->ticks = WF_SMU_SYS_FANS_INTERVAL;

	rc = wf_sensor_get(sensor_hd_temp, &temp);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: HD temp sensor error %d\n",
		       rc);
		wf_smu_failure_state |= FAILURE_SENSOR;
		वापस;
	पूर्ण

	DBG("wf_smu: System Fans tick ! HD temp: %d.%03d\n",
	    FIX32TOPRINT(temp));

	अगर (temp > (st->pid.param.itarget + 0x50000))
		wf_smu_failure_state |= FAILURE_OVERTEMP;

	new_setpoपूर्णांक = wf_pid_run(&st->pid, temp);

	DBG("wf_smu: new_setpoint: %d RPM\n", (पूर्णांक)new_setpoपूर्णांक);

	scaled = ((((s64)new_setpoपूर्णांक) * (s64)st->scale0) >> 12) + st->offset0;

	DBG("wf_smu: scaled setpoint: %d RPM\n", (पूर्णांक)scaled);

	cputarget = wf_smu_cpu_fans ? wf_smu_cpu_fans->pid.target : 0;
	cputarget = ((((s64)cputarget) * (s64)st->scale1) >> 12) + st->offset1;
	scaled = max(scaled, cputarget);
	scaled = max(scaled, st->pid.param.min);
	scaled = min(scaled, st->pid.param.max);

	DBG("wf_smu: adjusted setpoint: %d RPM\n", (पूर्णांक)scaled);

	अगर (st->sys_setpoपूर्णांक == scaled && new_setpoपूर्णांक == st->hd_setpoपूर्णांक)
		वापस;
	st->sys_setpoपूर्णांक = scaled;
	st->hd_setpoपूर्णांक = new_setpoपूर्णांक;
 पढ़ोjust:
	अगर (fan_प्रणाली && wf_smu_failure_state == 0) अणु
		rc = wf_control_set(fan_प्रणाली, st->sys_setpoपूर्णांक);
		अगर (rc) अणु
			prपूर्णांकk(KERN_WARNING "windfarm: Sys fan error %d\n",
			       rc);
			wf_smu_failure_state |= FAILURE_FAN;
		पूर्ण
	पूर्ण
	अगर (fan_hd && wf_smu_failure_state == 0) अणु
		rc = wf_control_set(fan_hd, st->hd_setpoपूर्णांक);
		अगर (rc) अणु
			prपूर्णांकk(KERN_WARNING "windfarm: HD fan error %d\n",
			       rc);
			wf_smu_failure_state |= FAILURE_FAN;
		पूर्ण
	पूर्ण
पूर्ण

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

	wf_smu_cpu_fans->scale = WF_SMU_CPU_FANS_SIBLING_SCALE;
	wf_smu_cpu_fans->offset = WF_SMU_CPU_FANS_SIBLING_OFFSET;

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
	s32 new_setpoपूर्णांक, temp, घातer, systarget;
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

	systarget = wf_smu_sys_fans ? wf_smu_sys_fans->pid.target : 0;
	systarget = ((((s64)systarget) * (s64)st->scale) >> 12)
		+ st->offset;
	new_setpoपूर्णांक = max(new_setpoपूर्णांक, systarget);
	new_setpoपूर्णांक = max(new_setpoपूर्णांक, st->pid.param.min);
	new_setpoपूर्णांक = min(new_setpoपूर्णांक, st->pid.param.max);

	DBG("wf_smu: adjusted setpoint: %d RPM\n", (पूर्णांक)new_setpoपूर्णांक);

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
		wf_smu_create_sys_fans();
		wf_smu_create_cpu_fans();
		wf_smu_started = true;
	पूर्ण

	/* Skipping ticks */
	अगर (wf_smu_skipping && --wf_smu_skipping)
		वापस;

	wf_smu_failure_state = 0;
	अगर (wf_smu_sys_fans)
		wf_smu_sys_fans_tick(wf_smu_sys_fans);
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
		अगर (fan_प्रणाली)
			wf_control_set_max(fan_प्रणाली);
		अगर (fan_cpu_मुख्य)
			wf_control_set_max(fan_cpu_मुख्य);
		अगर (fan_hd)
			wf_control_set_max(fan_hd);
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

	अगर (fan_cpu_मुख्य == शून्य && !म_भेद(ct->name, "cpu-fan")) अणु
		अगर (wf_get_control(ct) == 0)
			fan_cpu_मुख्य = ct;
	पूर्ण

	अगर (fan_प्रणाली == शून्य && !म_भेद(ct->name, "system-fan")) अणु
		अगर (wf_get_control(ct) == 0)
			fan_प्रणाली = ct;
	पूर्ण

	अगर (cpufreq_clamp == शून्य && !म_भेद(ct->name, "cpufreq-clamp")) अणु
		अगर (wf_get_control(ct) == 0)
			cpufreq_clamp = ct;
	पूर्ण

	/* Darwin property list says the HD fan is only क्रम model ID
	 * 0, 1, 2 and 3
	 */

	अगर (wf_smu_mach_model > 3) अणु
		अगर (fan_प्रणाली && fan_cpu_मुख्य && cpufreq_clamp)
			wf_smu_all_controls_ok = 1;
		वापस;
	पूर्ण

	अगर (fan_hd == शून्य && !म_भेद(ct->name, "drive-bay-fan")) अणु
		अगर (wf_get_control(ct) == 0)
			fan_hd = ct;
	पूर्ण

	अगर (fan_प्रणाली && fan_hd && fan_cpu_मुख्य && cpufreq_clamp)
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

	अगर (sensor_cpu_घातer && sensor_cpu_temp && sensor_hd_temp)
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
	स्थिर काष्ठा smu_sdbp_header *hdr;

	hdr = smu_get_sdb_partition(SMU_SDB_SENSORTREE_ID, शून्य);
	अगर (hdr != 0) अणु
		काष्ठा smu_sdbp_sensortree *st =
			(काष्ठा smu_sdbp_sensortree *)&hdr[1];
		wf_smu_mach_model = st->model_id;
	पूर्ण

	prपूर्णांकk(KERN_INFO "windfarm: Initializing for iMacG5 model ID %d\n",
	       wf_smu_mach_model);

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

	/* Release all controls */
	अगर (fan_cpu_मुख्य)
		wf_put_control(fan_cpu_मुख्य);
	अगर (fan_hd)
		wf_put_control(fan_hd);
	अगर (fan_प्रणाली)
		wf_put_control(fan_प्रणाली);
	अगर (cpufreq_clamp)
		wf_put_control(cpufreq_clamp);

	/* Destroy control loops state काष्ठाures */
	kमुक्त(wf_smu_sys_fans);
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

	अगर (of_machine_is_compatible("PowerMac8,1") ||
	    of_machine_is_compatible("PowerMac8,2"))
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
MODULE_DESCRIPTION("Thermal control logic for iMac G5");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:windfarm");
