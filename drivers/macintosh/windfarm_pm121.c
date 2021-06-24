<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control. iMac G5 iSight
 *
 * (c) Copyright 2007 थ	tienne Bersac <bersace@gmail.com>
 *
 * Bits & pieces from windfarm_pm81.c by (c) Copyright 2005 Benjamin
 * Herrenschmidt, IBM Corp. <benh@kernel.crashing.org>
 *
 * PowerMac12,1
 * ============
 *
 * The algorithm used is the PID control algorithm, used the same way
 * the published Darwin code करोes, using the same values that are
 * present in the Darwin 8.10 snapshot property lists (note however
 * that none of the code has been re-used, it's a complete
 * re-implementation
 *
 * There is two models using PowerMac12,1. Model 2 is iMac G5 iSight
 * 17" while Model 3 is iMac G5 20". They करो have both the same
 * controls with a tiny dअगरference. The control-ids of hard-drive-fan
 * and cpu-fan is swapped.
 *
 * Target Correction :
 *
 * controls have a target correction calculated as :
 *
 * new_min = ((((average_घातer * slope) >> 16) + offset) >> 16) + min_value
 * new_value = max(new_value, max(new_min, 0))
 *
 * OD Fan control correction.
 *
 * # model_id: 2
 *   offset		: -19563152
 *   slope		:  1956315
 *
 * # model_id: 3
 *   offset		: -15650652
 *   slope		:  1565065
 *
 * HD Fan control correction.
 *
 * # model_id: 2
 *   offset		: -15650652
 *   slope		:  1565065
 *
 * # model_id: 3
 *   offset		: -19563152
 *   slope		:  1956315
 *
 * CPU Fan control correction.
 *
 * # model_id: 2
 *   offset		: -25431900
 *   slope		:  2543190
 *
 * # model_id: 3
 *   offset		: -15650652
 *   slope		:  1565065
 *
 * Target rubber-banding :
 *
 * Some controls have a target correction which depends on another
 * control value. The correction is computed in the following way :
 *
 * new_min = ref_value * slope + offset
 *
 * ref_value is the value of the reference control. If new_min is
 * greater than 0, then we correct the target value using :
 *
 * new_target = max (new_target, new_min >> 16)
 *
 * # model_id : 2
 *   control	: cpu-fan
 *   ref	: optical-drive-fan
 *   offset	: -15650652
 *   slope	: 1565065
 *
 * # model_id : 3
 *   control	: optical-drive-fan
 *   ref	: hard-drive-fan
 *   offset	: -32768000
 *   slope	: 65536
 *
 * In order to have the moste efficient correction with those
 * dependencies, we must trigger HD loop beक्रमe OD loop beक्रमe CPU
 * loop.
 *
 * The various control loops found in Darwin config file are:
 *
 * HD Fan control loop.
 *
 * # model_id: 2
 *   control        : hard-drive-fan
 *   sensor         : hard-drive-temp
 *   PID params     : G_d = 0x00000000
 *                    G_p = 0x002D70A3
 *                    G_r = 0x00019999
 *                    History = 2 entries
 *                    Input target = 0x370000
 *                    Interval = 5s
 *
 * # model_id: 3
 *   control        : hard-drive-fan
 *   sensor         : hard-drive-temp
 *   PID params     : G_d = 0x00000000
 *                    G_p = 0x002170A3
 *                    G_r = 0x00019999
 *                    History = 2 entries
 *                    Input target = 0x370000
 *                    Interval = 5s
 *
 * OD Fan control loop.
 *
 * # model_id: 2
 *   control        : optical-drive-fan
 *   sensor         : optical-drive-temp
 *   PID params     : G_d = 0x00000000
 *                    G_p = 0x001FAE14
 *                    G_r = 0x00019999
 *                    History = 2 entries
 *                    Input target = 0x320000
 *                    Interval = 5s
 *
 * # model_id: 3
 *   control        : optical-drive-fan
 *   sensor         : optical-drive-temp
 *   PID params     : G_d = 0x00000000
 *                    G_p = 0x001FAE14
 *                    G_r = 0x00019999
 *                    History = 2 entries
 *                    Input target = 0x320000
 *                    Interval = 5s
 *
 * GPU Fan control loop.
 *
 * # model_id: 2
 *   control        : hard-drive-fan
 *   sensor         : gpu-temp
 *   PID params     : G_d = 0x00000000
 *                    G_p = 0x002A6666
 *                    G_r = 0x00019999
 *                    History = 2 entries
 *                    Input target = 0x5A0000
 *                    Interval = 5s
 *
 * # model_id: 3
 *   control        : cpu-fan
 *   sensor         : gpu-temp
 *   PID params     : G_d = 0x00000000
 *                    G_p = 0x0010CCCC
 *                    G_r = 0x00019999
 *                    History = 2 entries
 *                    Input target = 0x500000
 *                    Interval = 5s
 *
 * KODIAK (aka northbridge) Fan control loop.
 *
 * # model_id: 2
 *   control        : optical-drive-fan
 *   sensor         : north-bridge-temp
 *   PID params     : G_d = 0x00000000
 *                    G_p = 0x003BD70A
 *                    G_r = 0x00019999
 *                    History = 2 entries
 *                    Input target = 0x550000
 *                    Interval = 5s
 *
 * # model_id: 3
 *   control        : hard-drive-fan
 *   sensor         : north-bridge-temp
 *   PID params     : G_d = 0x00000000
 *                    G_p = 0x0030F5C2
 *                    G_r = 0x00019999
 *                    History = 2 entries
 *                    Input target = 0x550000
 *                    Interval = 5s
 *
 * CPU Fan control loop.
 *
 *   control        : cpu-fan
 *   sensors        : cpu-temp, cpu-घातer
 *   PID params     : from SDB partition
 *
 * CPU Slew control loop.
 *
 *   control        : cpufreq-clamp
 *   sensor         : cpu-temp
 */

#अघोषित	DEBUG

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

#घोषणा VERSION "0.3"

अटल पूर्णांक pm121_mach_model;	/* machine model id */

/* Controls & sensors */
अटल काष्ठा wf_sensor	*sensor_cpu_घातer;
अटल काष्ठा wf_sensor	*sensor_cpu_temp;
अटल काष्ठा wf_sensor	*sensor_cpu_voltage;
अटल काष्ठा wf_sensor	*sensor_cpu_current;
अटल काष्ठा wf_sensor	*sensor_gpu_temp;
अटल काष्ठा wf_sensor	*sensor_north_bridge_temp;
अटल काष्ठा wf_sensor	*sensor_hard_drive_temp;
अटल काष्ठा wf_sensor	*sensor_optical_drive_temp;
अटल काष्ठा wf_sensor	*sensor_incoming_air_temp; /* unused ! */

क्रमागत अणु
	FAN_CPU,
	FAN_HD,
	FAN_OD,
	CPUFREQ,
	N_CONTROLS
पूर्ण;
अटल काष्ठा wf_control *controls[N_CONTROLS] = अणुपूर्ण;

/* Set to kick the control loop पूर्णांकo lअगरe */
अटल पूर्णांक pm121_all_controls_ok, pm121_all_sensors_ok;
अटल bool pm121_started;

क्रमागत अणु
	FAILURE_FAN		= 1 << 0,
	FAILURE_SENSOR		= 1 << 1,
	FAILURE_OVERTEMP	= 1 << 2
पूर्ण;

/* All sys loops. Note the HD beक्रमe the OD loop in order to have it
   run beक्रमe. */
क्रमागत अणु
	LOOP_GPU,		/* control = hd or cpu, but luckily,
				   it करोesn't matter */
	LOOP_HD,		/* control = hd */
	LOOP_KODIAK,		/* control = hd or od */
	LOOP_OD,		/* control = od */
	N_LOOPS
पूर्ण;

अटल स्थिर अक्षर *loop_names[N_LOOPS] = अणु
	"GPU",
	"HD",
	"KODIAK",
	"OD",
पूर्ण;

#घोषणा	PM121_NUM_CONFIGS	2

अटल अचिन्हित पूर्णांक pm121_failure_state;
अटल पूर्णांक pm121_पढ़ोjust, pm121_skipping;
अटल bool pm121_overtemp;
अटल s32 average_घातer;

काष्ठा pm121_correction अणु
	पूर्णांक	offset;
	पूर्णांक	slope;
पूर्ण;

अटल काष्ठा pm121_correction corrections[N_CONTROLS][PM121_NUM_CONFIGS] = अणु
	/* FAN_OD */
	अणु
		/* MODEL 2 */
		अणु .offset	= -19563152,
		  .slope	=  1956315
		पूर्ण,
		/* MODEL 3 */
		अणु .offset	= -15650652,
		  .slope	=  1565065
		पूर्ण,
	पूर्ण,
	/* FAN_HD */
	अणु
		/* MODEL 2 */
		अणु .offset	= -15650652,
		  .slope	=  1565065
		पूर्ण,
		/* MODEL 3 */
		अणु .offset	= -19563152,
		  .slope	=  1956315
		पूर्ण,
	पूर्ण,
	/* FAN_CPU */
	अणु
		/* MODEL 2 */
		अणु .offset	= -25431900,
		  .slope	=  2543190
		पूर्ण,
		/* MODEL 3 */
		अणु .offset	= -15650652,
		  .slope	=  1565065
		पूर्ण,
	पूर्ण,
	/* CPUFREQ has no correction (and is not implemented at all) */
पूर्ण;

काष्ठा pm121_connection अणु
	अचिन्हित पूर्णांक	control_id;
	अचिन्हित पूर्णांक	ref_id;
	काष्ठा pm121_correction	correction;
पूर्ण;

अटल काष्ठा pm121_connection pm121_connections[] = अणु
	/* MODEL 2 */
	अणु .control_id	= FAN_CPU,
	  .ref_id	= FAN_OD,
	  अणु .offset	= -32768000,
	    .slope	=  65536
	  पूर्ण
	पूर्ण,
	/* MODEL 3 */
	अणु .control_id	= FAN_OD,
	  .ref_id	= FAN_HD,
	  अणु .offset	= -32768000,
	    .slope	=  65536
	  पूर्ण
	पूर्ण,
पूर्ण;

/* poपूर्णांकer to the current model connection */
अटल काष्ठा pm121_connection *pm121_connection;

/*
 * ****** System Fans Control Loop ******
 *
 */

/* Since each loop handles only one control and we want to aव्योम
 * writing भव control, we store the control correction with the
 * loop params. Some data are not set, there are common to all loop
 * and thus, hardcoded.
 */
काष्ठा pm121_sys_param अणु
	/* purely inक्रमmative since we use mach_model-2 as index */
	पूर्णांक			model_id;
	काष्ठा wf_sensor	**sensor; /* use sensor_id instead ? */
	s32			gp, itarget;
	अचिन्हित पूर्णांक		control_id;
पूर्ण;

अटल काष्ठा pm121_sys_param
pm121_sys_all_params[N_LOOPS][PM121_NUM_CONFIGS] = अणु
	/* GPU Fan control loop */
	अणु
		अणु .model_id	= 2,
		  .sensor	= &sensor_gpu_temp,
		  .gp		= 0x002A6666,
		  .itarget	= 0x5A0000,
		  .control_id	= FAN_HD,
		पूर्ण,
		अणु .model_id	= 3,
		  .sensor	= &sensor_gpu_temp,
		  .gp		= 0x0010CCCC,
		  .itarget	= 0x500000,
		  .control_id	= FAN_CPU,
		पूर्ण,
	पूर्ण,
	/* HD Fan control loop */
	अणु
		अणु .model_id	= 2,
		  .sensor	= &sensor_hard_drive_temp,
		  .gp		= 0x002D70A3,
		  .itarget	= 0x370000,
		  .control_id	= FAN_HD,
		पूर्ण,
		अणु .model_id	= 3,
		  .sensor	= &sensor_hard_drive_temp,
		  .gp		= 0x002170A3,
		  .itarget	= 0x370000,
		  .control_id	= FAN_HD,
		पूर्ण,
	पूर्ण,
	/* KODIAK Fan control loop */
	अणु
		अणु .model_id	= 2,
		  .sensor	= &sensor_north_bridge_temp,
		  .gp		= 0x003BD70A,
		  .itarget	= 0x550000,
		  .control_id	= FAN_OD,
		पूर्ण,
		अणु .model_id	= 3,
		  .sensor	= &sensor_north_bridge_temp,
		  .gp		= 0x0030F5C2,
		  .itarget	= 0x550000,
		  .control_id	= FAN_HD,
		पूर्ण,
	पूर्ण,
	/* OD Fan control loop */
	अणु
		अणु .model_id	= 2,
		  .sensor	= &sensor_optical_drive_temp,
		  .gp		= 0x001FAE14,
		  .itarget	= 0x320000,
		  .control_id	= FAN_OD,
		पूर्ण,
		अणु .model_id	= 3,
		  .sensor	= &sensor_optical_drive_temp,
		  .gp		= 0x001FAE14,
		  .itarget	= 0x320000,
		  .control_id	= FAN_OD,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* the hardcoded values */
#घोषणा	PM121_SYS_GD		0x00000000
#घोषणा	PM121_SYS_GR		0x00019999
#घोषणा	PM121_SYS_HISTORY_SIZE	2
#घोषणा	PM121_SYS_INTERVAL	5

/* State data used by the प्रणाली fans control loop
 */
काष्ठा pm121_sys_state अणु
	पूर्णांक			ticks;
	s32			setpoपूर्णांक;
	काष्ठा wf_pid_state	pid;
पूर्ण;

अटल काष्ठा pm121_sys_state *pm121_sys_state[N_LOOPS] = अणुपूर्ण;

/*
 * ****** CPU Fans Control Loop ******
 *
 */

#घोषणा PM121_CPU_INTERVAL	1

/* State data used by the cpu fans control loop
 */
काष्ठा pm121_cpu_state अणु
	पूर्णांक			ticks;
	s32			setpoपूर्णांक;
	काष्ठा wf_cpu_pid_state	pid;
पूर्ण;

अटल काष्ठा pm121_cpu_state *pm121_cpu_state;



/*
 * ***** Implementation *****
 *
 */

/* correction the value using the output-low-bound correction algo */
अटल s32 pm121_correct(s32 new_setpoपूर्णांक,
			 अचिन्हित पूर्णांक control_id,
			 s32 min)
अणु
	s32 new_min;
	काष्ठा pm121_correction *correction;
	correction = &corrections[control_id][pm121_mach_model - 2];

	new_min = (average_घातer * correction->slope) >> 16;
	new_min += correction->offset;
	new_min = (new_min >> 16) + min;

	वापस max3(new_setpoपूर्णांक, new_min, 0);
पूर्ण

अटल s32 pm121_connect(अचिन्हित पूर्णांक control_id, s32 setpoपूर्णांक)
अणु
	s32 new_min, value, new_setpoपूर्णांक;

	अगर (pm121_connection->control_id == control_id) अणु
		controls[control_id]->ops->get_value(controls[control_id],
						     &value);
		new_min = value * pm121_connection->correction.slope;
		new_min += pm121_connection->correction.offset;
		अगर (new_min > 0) अणु
			new_setpoपूर्णांक = max(setpoपूर्णांक, (new_min >> 16));
			अगर (new_setpoपूर्णांक != setpoपूर्णांक) अणु
				pr_debug("pm121: %s depending on %s, "
					 "corrected from %d to %d RPM\n",
					 controls[control_id]->name,
					 controls[pm121_connection->ref_id]->name,
					 (पूर्णांक) setpoपूर्णांक, (पूर्णांक) new_setpoपूर्णांक);
			पूर्ण
		पूर्ण अन्यथा
			new_setpoपूर्णांक = setpoपूर्णांक;
	पूर्ण
	/* no connection */
	अन्यथा
		new_setpoपूर्णांक = setpoपूर्णांक;

	वापस new_setpoपूर्णांक;
पूर्ण

/* FAN LOOPS */
अटल व्योम pm121_create_sys_fans(पूर्णांक loop_id)
अणु
	काष्ठा pm121_sys_param *param = शून्य;
	काष्ठा wf_pid_param pid_param;
	काष्ठा wf_control *control = शून्य;
	पूर्णांक i;

	/* First, locate the params क्रम this model */
	क्रम (i = 0; i < PM121_NUM_CONFIGS; i++) अणु
		अगर (pm121_sys_all_params[loop_id][i].model_id == pm121_mach_model) अणु
			param = &(pm121_sys_all_params[loop_id][i]);
			अवरोध;
		पूर्ण
	पूर्ण

	/* No params found, put fans to max */
	अगर (param == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "pm121: %s fan config not found "
		       " for this machine model\n",
		       loop_names[loop_id]);
		जाओ fail;
	पूर्ण

	control = controls[param->control_id];

	/* Alloc & initialize state */
	pm121_sys_state[loop_id] = kदो_स्मृति(माप(काष्ठा pm121_sys_state),
					   GFP_KERNEL);
	अगर (pm121_sys_state[loop_id] == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "pm121: Memory allocation error\n");
		जाओ fail;
	पूर्ण
	pm121_sys_state[loop_id]->ticks = 1;

	/* Fill PID params */
	pid_param.gd		= PM121_SYS_GD;
	pid_param.gp		= param->gp;
	pid_param.gr		= PM121_SYS_GR;
	pid_param.पूर्णांकerval	= PM121_SYS_INTERVAL;
	pid_param.history_len	= PM121_SYS_HISTORY_SIZE;
	pid_param.itarget	= param->itarget;
	अगर(control)
	अणु
		pid_param.min		= control->ops->get_min(control);
		pid_param.max		= control->ops->get_max(control);
	पूर्ण अन्यथा अणु
		/*
		 * This is probably not the right!?
		 * Perhaps जाओ fail  अगर control == शून्य  above?
		 */
		pid_param.min		= 0;
		pid_param.max		= 0;
	पूर्ण

	wf_pid_init(&pm121_sys_state[loop_id]->pid, &pid_param);

	pr_debug("pm121: %s Fan control loop initialized.\n"
		 "       itarged=%d.%03d, min=%d RPM, max=%d RPM\n",
		 loop_names[loop_id], FIX32TOPRINT(pid_param.itarget),
		 pid_param.min, pid_param.max);
	वापस;

 fail:
	/* note that this is not optimal since another loop may still
	   control the same control */
	prपूर्णांकk(KERN_WARNING "pm121: failed to set up %s loop "
	       "setting \"%s\" to max speed.\n",
	       loop_names[loop_id], control ? control->name : "uninitialized value");

	अगर (control)
		wf_control_set_max(control);
पूर्ण

अटल व्योम pm121_sys_fans_tick(पूर्णांक loop_id)
अणु
	काष्ठा pm121_sys_param *param;
	काष्ठा pm121_sys_state *st;
	काष्ठा wf_sensor *sensor;
	काष्ठा wf_control *control;
	s32 temp, new_setpoपूर्णांक;
	पूर्णांक rc;

	param = &(pm121_sys_all_params[loop_id][pm121_mach_model-2]);
	st = pm121_sys_state[loop_id];
	sensor = *(param->sensor);
	control = controls[param->control_id];

	अगर (--st->ticks != 0) अणु
		अगर (pm121_पढ़ोjust)
			जाओ पढ़ोjust;
		वापस;
	पूर्ण
	st->ticks = PM121_SYS_INTERVAL;

	rc = sensor->ops->get_value(sensor, &temp);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "windfarm: %s sensor error %d\n",
		       sensor->name, rc);
		pm121_failure_state |= FAILURE_SENSOR;
		वापस;
	पूर्ण

	pr_debug("pm121: %s Fan tick ! %s: %d.%03d\n",
		 loop_names[loop_id], sensor->name,
		 FIX32TOPRINT(temp));

	new_setpoपूर्णांक = wf_pid_run(&st->pid, temp);

	/* correction */
	new_setpoपूर्णांक = pm121_correct(new_setpoपूर्णांक,
				     param->control_id,
				     st->pid.param.min);
	/* linked corretion */
	new_setpoपूर्णांक = pm121_connect(param->control_id, new_setpoपूर्णांक);

	अगर (new_setpoपूर्णांक == st->setpoपूर्णांक)
		वापस;
	st->setpoपूर्णांक = new_setpoपूर्णांक;
	pr_debug("pm121: %s corrected setpoint: %d RPM\n",
		 control->name, (पूर्णांक)new_setpoपूर्णांक);
 पढ़ोjust:
	अगर (control && pm121_failure_state == 0) अणु
		rc = control->ops->set_value(control, st->setpoपूर्णांक);
		अगर (rc) अणु
			prपूर्णांकk(KERN_WARNING "windfarm: %s fan error %d\n",
			       control->name, rc);
			pm121_failure_state |= FAILURE_FAN;
		पूर्ण
	पूर्ण
पूर्ण


/* CPU LOOP */
अटल व्योम pm121_create_cpu_fans(व्योम)
अणु
	काष्ठा wf_cpu_pid_param pid_param;
	स्थिर काष्ठा smu_sdbp_header *hdr;
	काष्ठा smu_sdbp_cpupiddata *piddata;
	काष्ठा smu_sdbp_fvt *fvt;
	काष्ठा wf_control *fan_cpu;
	s32 पंचांगax, tdelta, maxघात, घातadj;

	fan_cpu = controls[FAN_CPU];

	/* First, locate the PID params in SMU SBD */
	hdr = smu_get_sdb_partition(SMU_SDB_CPUPIDDATA_ID, शून्य);
	अगर (hdr == 0) अणु
		prपूर्णांकk(KERN_WARNING "pm121: CPU PID fan config not found.\n");
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
	pm121_cpu_state = kदो_स्मृति(माप(काष्ठा pm121_cpu_state),
				  GFP_KERNEL);
	अगर (pm121_cpu_state == शून्य)
		जाओ fail;
	pm121_cpu_state->ticks = 1;

	/* Fill PID params */
	pid_param.पूर्णांकerval = PM121_CPU_INTERVAL;
	pid_param.history_len = piddata->history_len;
	अगर (pid_param.history_len > WF_CPU_PID_MAX_HISTORY) अणु
		prपूर्णांकk(KERN_WARNING "pm121: History size overflow on "
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

	pid_param.min = fan_cpu->ops->get_min(fan_cpu);
	pid_param.max = fan_cpu->ops->get_max(fan_cpu);

	wf_cpu_pid_init(&pm121_cpu_state->pid, &pid_param);

	pr_debug("pm121: CPU Fan control initialized.\n");
	pr_debug("       ttarget=%d.%03d, tmax=%d.%03d, min=%d RPM, max=%d RPM,\n",
		 FIX32TOPRINT(pid_param.ttarget), FIX32TOPRINT(pid_param.पंचांगax),
		 pid_param.min, pid_param.max);

	वापस;

 fail:
	prपूर्णांकk(KERN_WARNING "pm121: CPU fan config not found, max fan speed\n");

	अगर (controls[CPUFREQ])
		wf_control_set_max(controls[CPUFREQ]);
	अगर (fan_cpu)
		wf_control_set_max(fan_cpu);
पूर्ण


अटल व्योम pm121_cpu_fans_tick(काष्ठा pm121_cpu_state *st)
अणु
	s32 new_setpoपूर्णांक, temp, घातer;
	काष्ठा wf_control *fan_cpu = शून्य;
	पूर्णांक rc;

	अगर (--st->ticks != 0) अणु
		अगर (pm121_पढ़ोjust)
			जाओ पढ़ोjust;
		वापस;
	पूर्ण
	st->ticks = PM121_CPU_INTERVAL;

	fan_cpu = controls[FAN_CPU];

	rc = sensor_cpu_temp->ops->get_value(sensor_cpu_temp, &temp);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "pm121: CPU temp sensor error %d\n",
		       rc);
		pm121_failure_state |= FAILURE_SENSOR;
		वापस;
	पूर्ण

	rc = sensor_cpu_घातer->ops->get_value(sensor_cpu_घातer, &घातer);
	अगर (rc) अणु
		prपूर्णांकk(KERN_WARNING "pm121: CPU power sensor error %d\n",
		       rc);
		pm121_failure_state |= FAILURE_SENSOR;
		वापस;
	पूर्ण

	pr_debug("pm121: CPU Fans tick ! CPU temp: %d.%03dतओC, power: %d.%03d\n",
		 FIX32TOPRINT(temp), FIX32TOPRINT(घातer));

	अगर (temp > st->pid.param.पंचांगax)
		pm121_failure_state |= FAILURE_OVERTEMP;

	new_setpoपूर्णांक = wf_cpu_pid_run(&st->pid, घातer, temp);

	/* correction */
	new_setpoपूर्णांक = pm121_correct(new_setpoपूर्णांक,
				     FAN_CPU,
				     st->pid.param.min);

	/* connected correction */
	new_setpoपूर्णांक = pm121_connect(FAN_CPU, new_setpoपूर्णांक);

	अगर (st->setpoपूर्णांक == new_setpoपूर्णांक)
		वापस;
	st->setpoपूर्णांक = new_setpoपूर्णांक;
	pr_debug("pm121: CPU corrected setpoint: %d RPM\n", (पूर्णांक)new_setpoपूर्णांक);

 पढ़ोjust:
	अगर (fan_cpu && pm121_failure_state == 0) अणु
		rc = fan_cpu->ops->set_value(fan_cpu, st->setpoपूर्णांक);
		अगर (rc) अणु
			prपूर्णांकk(KERN_WARNING "pm121: %s fan error %d\n",
			       fan_cpu->name, rc);
			pm121_failure_state |= FAILURE_FAN;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * ****** Common ******
 *
 */

अटल व्योम pm121_tick(व्योम)
अणु
	अचिन्हित पूर्णांक last_failure = pm121_failure_state;
	अचिन्हित पूर्णांक new_failure;
	s32 total_घातer;
	पूर्णांक i;

	अगर (!pm121_started) अणु
		pr_debug("pm121: creating control loops !\n");
		क्रम (i = 0; i < N_LOOPS; i++)
			pm121_create_sys_fans(i);

		pm121_create_cpu_fans();
		pm121_started = true;
	पूर्ण

	/* skipping ticks */
	अगर (pm121_skipping && --pm121_skipping)
		वापस;

	/* compute average घातer */
	total_घातer = 0;
	क्रम (i = 0; i < pm121_cpu_state->pid.param.history_len; i++)
		total_घातer += pm121_cpu_state->pid.घातers[i];

	average_घातer = total_घातer / pm121_cpu_state->pid.param.history_len;


	pm121_failure_state = 0;
	क्रम (i = 0 ; i < N_LOOPS; i++) अणु
		अगर (pm121_sys_state[i])
			pm121_sys_fans_tick(i);
	पूर्ण

	अगर (pm121_cpu_state)
		pm121_cpu_fans_tick(pm121_cpu_state);

	pm121_पढ़ोjust = 0;
	new_failure = pm121_failure_state & ~last_failure;

	/* If entering failure mode, clamp cpufreq and ramp all
	 * fans to full speed.
	 */
	अगर (pm121_failure_state && !last_failure) अणु
		क्रम (i = 0; i < N_CONTROLS; i++) अणु
			अगर (controls[i])
				wf_control_set_max(controls[i]);
		पूर्ण
	पूर्ण

	/* If leaving failure mode, unclamp cpufreq and पढ़ोjust
	 * all fans on next iteration
	 */
	अगर (!pm121_failure_state && last_failure) अणु
		अगर (controls[CPUFREQ])
			wf_control_set_min(controls[CPUFREQ]);
		pm121_पढ़ोjust = 1;
	पूर्ण

	/* Overtemp condition detected, notअगरy and start skipping a couple
	 * ticks to let the temperature go करोwn
	 */
	अगर (new_failure & FAILURE_OVERTEMP) अणु
		wf_set_overtemp();
		pm121_skipping = 2;
		pm121_overtemp = true;
	पूर्ण

	/* We only clear the overtemp condition अगर overtemp is cleared
	 * _and_ no other failure is present. Since a sensor error will
	 * clear the overtemp condition (can't measure temperature) at
	 * the control loop levels, but we करोn't want to keep it clear
	 * here in this हाल
	 */
	अगर (!pm121_failure_state && pm121_overtemp) अणु
		wf_clear_overtemp();
		pm121_overtemp = false;
	पूर्ण
पूर्ण


अटल काष्ठा wf_control* pm121_रेजिस्टर_control(काष्ठा wf_control *ct,
						 स्थिर अक्षर *match,
						 अचिन्हित पूर्णांक id)
अणु
	अगर (controls[id] == शून्य && !म_भेद(ct->name, match)) अणु
		अगर (wf_get_control(ct) == 0)
			controls[id] = ct;
	पूर्ण
	वापस controls[id];
पूर्ण

अटल व्योम pm121_new_control(काष्ठा wf_control *ct)
अणु
	पूर्णांक all = 1;

	अगर (pm121_all_controls_ok)
		वापस;

	all = pm121_रेजिस्टर_control(ct, "optical-drive-fan", FAN_OD) && all;
	all = pm121_रेजिस्टर_control(ct, "hard-drive-fan", FAN_HD) && all;
	all = pm121_रेजिस्टर_control(ct, "cpu-fan", FAN_CPU) && all;
	all = pm121_रेजिस्टर_control(ct, "cpufreq-clamp", CPUFREQ) && all;

	अगर (all)
		pm121_all_controls_ok = 1;
पूर्ण




अटल काष्ठा wf_sensor* pm121_रेजिस्टर_sensor(काष्ठा wf_sensor *sensor,
					       स्थिर अक्षर *match,
					       काष्ठा wf_sensor **var)
अणु
	अगर (*var == शून्य && !म_भेद(sensor->name, match)) अणु
		अगर (wf_get_sensor(sensor) == 0)
			*var = sensor;
	पूर्ण
	वापस *var;
पूर्ण

अटल व्योम pm121_new_sensor(काष्ठा wf_sensor *sr)
अणु
	पूर्णांक all = 1;

	अगर (pm121_all_sensors_ok)
		वापस;

	all = pm121_रेजिस्टर_sensor(sr, "cpu-temp",
				    &sensor_cpu_temp) && all;
	all = pm121_रेजिस्टर_sensor(sr, "cpu-current",
				    &sensor_cpu_current) && all;
	all = pm121_रेजिस्टर_sensor(sr, "cpu-voltage",
				    &sensor_cpu_voltage) && all;
	all = pm121_रेजिस्टर_sensor(sr, "cpu-power",
				    &sensor_cpu_घातer) && all;
	all = pm121_रेजिस्टर_sensor(sr, "hard-drive-temp",
				    &sensor_hard_drive_temp) && all;
	all = pm121_रेजिस्टर_sensor(sr, "optical-drive-temp",
				    &sensor_optical_drive_temp) && all;
	all = pm121_रेजिस्टर_sensor(sr, "incoming-air-temp",
				    &sensor_incoming_air_temp) && all;
	all = pm121_रेजिस्टर_sensor(sr, "north-bridge-temp",
				    &sensor_north_bridge_temp) && all;
	all = pm121_रेजिस्टर_sensor(sr, "gpu-temp",
				    &sensor_gpu_temp) && all;

	अगर (all)
		pm121_all_sensors_ok = 1;
पूर्ण



अटल पूर्णांक pm121_notअगरy(काष्ठा notअगरier_block *self,
			अचिन्हित दीर्घ event, व्योम *data)
अणु
	चयन (event) अणु
	हाल WF_EVENT_NEW_CONTROL:
		pr_debug("pm121: new control %s detected\n",
			 ((काष्ठा wf_control *)data)->name);
		pm121_new_control(data);
		अवरोध;
	हाल WF_EVENT_NEW_SENSOR:
		pr_debug("pm121: new sensor %s detected\n",
			 ((काष्ठा wf_sensor *)data)->name);
		pm121_new_sensor(data);
		अवरोध;
	हाल WF_EVENT_TICK:
		अगर (pm121_all_controls_ok && pm121_all_sensors_ok)
			pm121_tick();
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block pm121_events = अणु
	.notअगरier_call	= pm121_notअगरy,
पूर्ण;

अटल पूर्णांक pm121_init_pm(व्योम)
अणु
	स्थिर काष्ठा smu_sdbp_header *hdr;

	hdr = smu_get_sdb_partition(SMU_SDB_SENSORTREE_ID, शून्य);
	अगर (hdr != 0) अणु
		काष्ठा smu_sdbp_sensortree *st =
			(काष्ठा smu_sdbp_sensortree *)&hdr[1];
		pm121_mach_model = st->model_id;
	पूर्ण

	pm121_connection = &pm121_connections[pm121_mach_model - 2];

	prपूर्णांकk(KERN_INFO "pm121: Initializing for iMac G5 iSight model ID %d\n",
	       pm121_mach_model);

	वापस 0;
पूर्ण


अटल पूर्णांक pm121_probe(काष्ठा platक्रमm_device *ddev)
अणु
	wf_रेजिस्टर_client(&pm121_events);

	वापस 0;
पूर्ण

अटल पूर्णांक pm121_हटाओ(काष्ठा platक्रमm_device *ddev)
अणु
	wf_unरेजिस्टर_client(&pm121_events);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pm121_driver = अणु
	.probe = pm121_probe,
	.हटाओ = pm121_हटाओ,
	.driver = अणु
		.name = "windfarm",
		.bus = &platक्रमm_bus_type,
	पूर्ण,
पूर्ण;


अटल पूर्णांक __init pm121_init(व्योम)
अणु
	पूर्णांक rc = -ENODEV;

	अगर (of_machine_is_compatible("PowerMac12,1"))
		rc = pm121_init_pm();

	अगर (rc == 0) अणु
		request_module("windfarm_smu_controls");
		request_module("windfarm_smu_sensors");
		request_module("windfarm_smu_sat");
		request_module("windfarm_lm75_sensor");
		request_module("windfarm_max6690_sensor");
		request_module("windfarm_cpufreq_clamp");
		platक्रमm_driver_रेजिस्टर(&pm121_driver);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम __निकास pm121_निकास(व्योम)
अणु

	platक्रमm_driver_unरेजिस्टर(&pm121_driver);
पूर्ण


module_init(pm121_init);
module_निकास(pm121_निकास);

MODULE_AUTHOR("थ	tienne Bersac <bersace@gmail.com>");
MODULE_DESCRIPTION("Thermal control logic for iMac G5 (iSight)");
MODULE_LICENSE("GPL");

