<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* bbc_envctrl.c: UltraSPARC-III environment control driver.
 *
 * Copyright (C) 2001, 2008 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/delay.h>
#समावेश <linux/kmod.h>
#समावेश <linux/reboot.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>
#समावेश <यंत्र/oplib.h>

#समावेश "bbc_i2c.h"
#समावेश "max1617.h"

#अघोषित ENVCTRL_TRACE

/* WARNING: Making changes to this driver is very dangerous.
 *          If you misprogram the sensor chips they can
 *          cut the घातer on you instantly.
 */

/* Two temperature sensors exist in the SunBLADE-1000 enclosure.
 * Both are implemented using max1617 i2c devices.  Each max1617
 * monitors 2 temperatures, one क्रम one of the cpu dies and the other
 * क्रम the ambient temperature.
 *
 * The max1617 is capable of being programmed with घातer-off
 * temperature values, one low limit and one high limit.  These
 * can be controlled independently क्रम the cpu or ambient temperature.
 * If a limit is violated, the घातer is simply shut off.  The frequency
 * with which the max1617 करोes temperature sampling can be controlled
 * as well.
 *
 * Three fans exist inside the machine, all three are controlled with
 * an i2c digital to analog converter.  There is a fan directed at the
 * two processor slots, another क्रम the rest of the enclosure, and the
 * third is क्रम the घातer supply.  The first two fans may be speed
 * controlled by changing the voltage fed to them.  The third fan may
 * only be completely off or on.  The third fan is meant to only be
 * disabled/enabled when entering/निकासing the lowest घातer-saving
 * mode of the machine.
 *
 * An environmental control kernel thपढ़ो periodically monitors all
 * temperature sensors.  Based upon the samples it will adjust the
 * fan speeds to try and keep the प्रणाली within a certain temperature
 * range (the goal being to make the fans as quiet as possible without
 * allowing the प्रणाली to get too hot).
 *
 * If the temperature begins to rise/fall outside of the acceptable
 * operating range, a periodic warning will be sent to the kernel log.
 * The fans will be put on full blast to attempt to deal with this
 * situation.  After exceeding the acceptable operating range by a
 * certain threshold, the kernel thपढ़ो will shut करोwn the प्रणाली.
 * Here, the thपढ़ो is attempting to shut the machine करोwn cleanly
 * beक्रमe the hardware based घातer-off event is triggered.
 */

/* These settings are in Celsius.  We use these शेषs only
 * अगर we cannot पूर्णांकerrogate the cpu-fru SEEPROM.
 */
काष्ठा temp_limits अणु
	s8 high_pwroff, high_shutकरोwn, high_warn;
	s8 low_warn, low_shutकरोwn, low_pwroff;
पूर्ण;

अटल काष्ठा temp_limits cpu_temp_limits[2] = अणु
	अणु 100, 85, 80, 5, -5, -10 पूर्ण,
	अणु 100, 85, 80, 5, -5, -10 पूर्ण,
पूर्ण;

अटल काष्ठा temp_limits amb_temp_limits[2] = अणु
	अणु 65, 55, 40, 5, -5, -10 पूर्ण,
	अणु 65, 55, 40, 5, -5, -10 पूर्ण,
पूर्ण;

अटल LIST_HEAD(all_temps);
अटल LIST_HEAD(all_fans);

#घोषणा CPU_FAN_REG	0xf0
#घोषणा SYS_FAN_REG	0xf2
#घोषणा PSUPPLY_FAN_REG	0xf4

#घोषणा FAN_SPEED_MIN	0x0c
#घोषणा FAN_SPEED_MAX	0x3f

#घोषणा PSUPPLY_FAN_ON	0x1f
#घोषणा PSUPPLY_FAN_OFF	0x00

अटल व्योम set_fan_speeds(काष्ठा bbc_fan_control *fp)
अणु
	/* Put temperatures पूर्णांकo range so we करोn't mis-program
	 * the hardware.
	 */
	अगर (fp->cpu_fan_speed < FAN_SPEED_MIN)
		fp->cpu_fan_speed = FAN_SPEED_MIN;
	अगर (fp->cpu_fan_speed > FAN_SPEED_MAX)
		fp->cpu_fan_speed = FAN_SPEED_MAX;
	अगर (fp->प्रणाली_fan_speed < FAN_SPEED_MIN)
		fp->प्रणाली_fan_speed = FAN_SPEED_MIN;
	अगर (fp->प्रणाली_fan_speed > FAN_SPEED_MAX)
		fp->प्रणाली_fan_speed = FAN_SPEED_MAX;
#अगर_घोषित ENVCTRL_TRACE
	prपूर्णांकk("fan%d: Changed fan speed to cpu(%02x) sys(%02x)\n",
	       fp->index,
	       fp->cpu_fan_speed, fp->प्रणाली_fan_speed);
#पूर्ण_अगर

	bbc_i2c_ग_लिखोb(fp->client, fp->cpu_fan_speed, CPU_FAN_REG);
	bbc_i2c_ग_लिखोb(fp->client, fp->प्रणाली_fan_speed, SYS_FAN_REG);
	bbc_i2c_ग_लिखोb(fp->client,
		       (fp->psupply_fan_on ?
			PSUPPLY_FAN_ON : PSUPPLY_FAN_OFF),
		       PSUPPLY_FAN_REG);
पूर्ण

अटल व्योम get_current_temps(काष्ठा bbc_cpu_temperature *tp)
अणु
	tp->prev_amb_temp = tp->curr_amb_temp;
	bbc_i2c_पढ़ोb(tp->client,
		      (अचिन्हित अक्षर *) &tp->curr_amb_temp,
		      MAX1617_AMB_TEMP);
	tp->prev_cpu_temp = tp->curr_cpu_temp;
	bbc_i2c_पढ़ोb(tp->client,
		      (अचिन्हित अक्षर *) &tp->curr_cpu_temp,
		      MAX1617_CPU_TEMP);
#अगर_घोषित ENVCTRL_TRACE
	prपूर्णांकk("temp%d: cpu(%d C) amb(%d C)\n",
	       tp->index,
	       (पूर्णांक) tp->curr_cpu_temp, (पूर्णांक) tp->curr_amb_temp);
#पूर्ण_अगर
पूर्ण


अटल व्योम करो_envctrl_shutकरोwn(काष्ठा bbc_cpu_temperature *tp)
अणु
	अटल पूर्णांक shutting_करोwn = 0;
	अक्षर *type = "???";
	s8 val = -1;

	अगर (shutting_करोwn != 0)
		वापस;

	अगर (tp->curr_amb_temp >= amb_temp_limits[tp->index].high_shutकरोwn ||
	    tp->curr_amb_temp < amb_temp_limits[tp->index].low_shutकरोwn) अणु
		type = "ambient";
		val = tp->curr_amb_temp;
	पूर्ण अन्यथा अगर (tp->curr_cpu_temp >= cpu_temp_limits[tp->index].high_shutकरोwn ||
		   tp->curr_cpu_temp < cpu_temp_limits[tp->index].low_shutकरोwn) अणु
		type = "CPU";
		val = tp->curr_cpu_temp;
	पूर्ण

	prपूर्णांकk(KERN_CRIT "temp%d: Outside of safe %s "
	       "operating temperature, %d C.\n",
	       tp->index, type, val);

	prपूर्णांकk(KERN_CRIT "kenvctrld: Shutting down the system now.\n");

	shutting_करोwn = 1;
	orderly_घातeroff(true);
पूर्ण

#घोषणा WARN_INTERVAL	(30 * HZ)

अटल व्योम analyze_ambient_temp(काष्ठा bbc_cpu_temperature *tp, अचिन्हित दीर्घ *last_warn, पूर्णांक tick)
अणु
	पूर्णांक ret = 0;

	अगर (समय_after(jअगरfies, (*last_warn + WARN_INTERVAL))) अणु
		अगर (tp->curr_amb_temp >=
		    amb_temp_limits[tp->index].high_warn) अणु
			prपूर्णांकk(KERN_WARNING "temp%d: "
			       "Above safe ambient operating temperature, %d C.\n",
			       tp->index, (पूर्णांक) tp->curr_amb_temp);
			ret = 1;
		पूर्ण अन्यथा अगर (tp->curr_amb_temp <
			   amb_temp_limits[tp->index].low_warn) अणु
			prपूर्णांकk(KERN_WARNING "temp%d: "
			       "Below safe ambient operating temperature, %d C.\n",
			       tp->index, (पूर्णांक) tp->curr_amb_temp);
			ret = 1;
		पूर्ण
		अगर (ret)
			*last_warn = jअगरfies;
	पूर्ण अन्यथा अगर (tp->curr_amb_temp >= amb_temp_limits[tp->index].high_warn ||
		   tp->curr_amb_temp < amb_temp_limits[tp->index].low_warn)
		ret = 1;

	/* Now check the shutकरोwn limits. */
	अगर (tp->curr_amb_temp >= amb_temp_limits[tp->index].high_shutकरोwn ||
	    tp->curr_amb_temp < amb_temp_limits[tp->index].low_shutकरोwn) अणु
		करो_envctrl_shutकरोwn(tp);
		ret = 1;
	पूर्ण

	अगर (ret) अणु
		tp->fan_toकरो[FAN_AMBIENT] = FAN_FULLBLAST;
	पूर्ण अन्यथा अगर ((tick & (8 - 1)) == 0) अणु
		s8 amb_goal_hi = amb_temp_limits[tp->index].high_warn - 10;
		s8 amb_goal_lo;

		amb_goal_lo = amb_goal_hi - 3;

		/* We करो not try to aव्योम 'too cold' events.  Basically we
		 * only try to deal with over-heating and fan noise reduction.
		 */
		अगर (tp->avg_amb_temp < amb_goal_hi) अणु
			अगर (tp->avg_amb_temp >= amb_goal_lo)
				tp->fan_toकरो[FAN_AMBIENT] = FAN_SAME;
			अन्यथा
				tp->fan_toकरो[FAN_AMBIENT] = FAN_SLOWER;
		पूर्ण अन्यथा अणु
			tp->fan_toकरो[FAN_AMBIENT] = FAN_FASTER;
		पूर्ण
	पूर्ण अन्यथा अणु
		tp->fan_toकरो[FAN_AMBIENT] = FAN_SAME;
	पूर्ण
पूर्ण

अटल व्योम analyze_cpu_temp(काष्ठा bbc_cpu_temperature *tp, अचिन्हित दीर्घ *last_warn, पूर्णांक tick)
अणु
	पूर्णांक ret = 0;

	अगर (समय_after(jअगरfies, (*last_warn + WARN_INTERVAL))) अणु
		अगर (tp->curr_cpu_temp >=
		    cpu_temp_limits[tp->index].high_warn) अणु
			prपूर्णांकk(KERN_WARNING "temp%d: "
			       "Above safe CPU operating temperature, %d C.\n",
			       tp->index, (पूर्णांक) tp->curr_cpu_temp);
			ret = 1;
		पूर्ण अन्यथा अगर (tp->curr_cpu_temp <
			   cpu_temp_limits[tp->index].low_warn) अणु
			prपूर्णांकk(KERN_WARNING "temp%d: "
			       "Below safe CPU operating temperature, %d C.\n",
			       tp->index, (पूर्णांक) tp->curr_cpu_temp);
			ret = 1;
		पूर्ण
		अगर (ret)
			*last_warn = jअगरfies;
	पूर्ण अन्यथा अगर (tp->curr_cpu_temp >= cpu_temp_limits[tp->index].high_warn ||
		   tp->curr_cpu_temp < cpu_temp_limits[tp->index].low_warn)
		ret = 1;

	/* Now check the shutकरोwn limits. */
	अगर (tp->curr_cpu_temp >= cpu_temp_limits[tp->index].high_shutकरोwn ||
	    tp->curr_cpu_temp < cpu_temp_limits[tp->index].low_shutकरोwn) अणु
		करो_envctrl_shutकरोwn(tp);
		ret = 1;
	पूर्ण

	अगर (ret) अणु
		tp->fan_toकरो[FAN_CPU] = FAN_FULLBLAST;
	पूर्ण अन्यथा अगर ((tick & (8 - 1)) == 0) अणु
		s8 cpu_goal_hi = cpu_temp_limits[tp->index].high_warn - 10;
		s8 cpu_goal_lo;

		cpu_goal_lo = cpu_goal_hi - 3;

		/* We करो not try to aव्योम 'too cold' events.  Basically we
		 * only try to deal with over-heating and fan noise reduction.
		 */
		अगर (tp->avg_cpu_temp < cpu_goal_hi) अणु
			अगर (tp->avg_cpu_temp >= cpu_goal_lo)
				tp->fan_toकरो[FAN_CPU] = FAN_SAME;
			अन्यथा
				tp->fan_toकरो[FAN_CPU] = FAN_SLOWER;
		पूर्ण अन्यथा अणु
			tp->fan_toकरो[FAN_CPU] = FAN_FASTER;
		पूर्ण
	पूर्ण अन्यथा अणु
		tp->fan_toकरो[FAN_CPU] = FAN_SAME;
	पूर्ण
पूर्ण

अटल व्योम analyze_temps(काष्ठा bbc_cpu_temperature *tp, अचिन्हित दीर्घ *last_warn)
अणु
	tp->avg_amb_temp = (s8)((पूर्णांक)((पूर्णांक)tp->avg_amb_temp + (पूर्णांक)tp->curr_amb_temp) / 2);
	tp->avg_cpu_temp = (s8)((पूर्णांक)((पूर्णांक)tp->avg_cpu_temp + (पूर्णांक)tp->curr_cpu_temp) / 2);

	analyze_ambient_temp(tp, last_warn, tp->sample_tick);
	analyze_cpu_temp(tp, last_warn, tp->sample_tick);

	tp->sample_tick++;
पूर्ण

अटल क्रमागत fan_action prioritize_fan_action(पूर्णांक which_fan)
अणु
	काष्ठा bbc_cpu_temperature *tp;
	क्रमागत fan_action decision = FAN_STATE_MAX;

	/* Basically, prioritize what the temperature sensors
	 * recommend we करो, and perक्रमm that action on all the
	 * fans.
	 */
	list_क्रम_each_entry(tp, &all_temps, glob_list) अणु
		अगर (tp->fan_toकरो[which_fan] == FAN_FULLBLAST) अणु
			decision = FAN_FULLBLAST;
			अवरोध;
		पूर्ण
		अगर (tp->fan_toकरो[which_fan] == FAN_SAME &&
		    decision != FAN_FASTER)
			decision = FAN_SAME;
		अन्यथा अगर (tp->fan_toकरो[which_fan] == FAN_FASTER)
			decision = FAN_FASTER;
		अन्यथा अगर (decision != FAN_FASTER &&
			 decision != FAN_SAME &&
			 tp->fan_toकरो[which_fan] == FAN_SLOWER)
			decision = FAN_SLOWER;
	पूर्ण
	अगर (decision == FAN_STATE_MAX)
		decision = FAN_SAME;

	वापस decision;
पूर्ण

अटल पूर्णांक maybe_new_ambient_fan_speed(काष्ठा bbc_fan_control *fp)
अणु
	क्रमागत fan_action decision = prioritize_fan_action(FAN_AMBIENT);
	पूर्णांक ret;

	अगर (decision == FAN_SAME)
		वापस 0;

	ret = 1;
	अगर (decision == FAN_FULLBLAST) अणु
		अगर (fp->प्रणाली_fan_speed >= FAN_SPEED_MAX)
			ret = 0;
		अन्यथा
			fp->प्रणाली_fan_speed = FAN_SPEED_MAX;
	पूर्ण अन्यथा अणु
		अगर (decision == FAN_FASTER) अणु
			अगर (fp->प्रणाली_fan_speed >= FAN_SPEED_MAX)
				ret = 0;
			अन्यथा
				fp->प्रणाली_fan_speed += 2;
		पूर्ण अन्यथा अणु
			पूर्णांक orig_speed = fp->प्रणाली_fan_speed;

			अगर (orig_speed <= FAN_SPEED_MIN ||
			    orig_speed <= (fp->cpu_fan_speed - 3))
				ret = 0;
			अन्यथा
				fp->प्रणाली_fan_speed -= 1;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक maybe_new_cpu_fan_speed(काष्ठा bbc_fan_control *fp)
अणु
	क्रमागत fan_action decision = prioritize_fan_action(FAN_CPU);
	पूर्णांक ret;

	अगर (decision == FAN_SAME)
		वापस 0;

	ret = 1;
	अगर (decision == FAN_FULLBLAST) अणु
		अगर (fp->cpu_fan_speed >= FAN_SPEED_MAX)
			ret = 0;
		अन्यथा
			fp->cpu_fan_speed = FAN_SPEED_MAX;
	पूर्ण अन्यथा अणु
		अगर (decision == FAN_FASTER) अणु
			अगर (fp->cpu_fan_speed >= FAN_SPEED_MAX)
				ret = 0;
			अन्यथा अणु
				fp->cpu_fan_speed += 2;
				अगर (fp->प्रणाली_fan_speed <
				    (fp->cpu_fan_speed - 3))
					fp->प्रणाली_fan_speed =
						fp->cpu_fan_speed - 3;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (fp->cpu_fan_speed <= FAN_SPEED_MIN)
				ret = 0;
			अन्यथा
				fp->cpu_fan_speed -= 1;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम maybe_new_fan_speeds(काष्ठा bbc_fan_control *fp)
अणु
	पूर्णांक new;

	new  = maybe_new_ambient_fan_speed(fp);
	new |= maybe_new_cpu_fan_speed(fp);

	अगर (new)
		set_fan_speeds(fp);
पूर्ण

अटल व्योम fans_full_blast(व्योम)
अणु
	काष्ठा bbc_fan_control *fp;

	/* Since we will not be monitoring things anymore, put
	 * the fans on full blast.
	 */
	list_क्रम_each_entry(fp, &all_fans, glob_list) अणु
		fp->cpu_fan_speed = FAN_SPEED_MAX;
		fp->प्रणाली_fan_speed = FAN_SPEED_MAX;
		fp->psupply_fan_on = 1;
		set_fan_speeds(fp);
	पूर्ण
पूर्ण

#घोषणा POLL_INTERVAL	(5 * 1000)
अटल अचिन्हित दीर्घ last_warning_jअगरfies;
अटल काष्ठा task_काष्ठा *kenvctrld_task;

अटल पूर्णांक kenvctrld(व्योम *__unused)
अणु
	prपूर्णांकk(KERN_INFO "bbc_envctrl: kenvctrld starting...\n");
	last_warning_jअगरfies = jअगरfies - WARN_INTERVAL;
	क्रम (;;) अणु
		काष्ठा bbc_cpu_temperature *tp;
		काष्ठा bbc_fan_control *fp;

		msleep_पूर्णांकerruptible(POLL_INTERVAL);
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		list_क्रम_each_entry(tp, &all_temps, glob_list) अणु
			get_current_temps(tp);
			analyze_temps(tp, &last_warning_jअगरfies);
		पूर्ण
		list_क्रम_each_entry(fp, &all_fans, glob_list)
			maybe_new_fan_speeds(fp);
	पूर्ण
	prपूर्णांकk(KERN_INFO "bbc_envctrl: kenvctrld exiting...\n");

	fans_full_blast();

	वापस 0;
पूर्ण

अटल व्योम attach_one_temp(काष्ठा bbc_i2c_bus *bp, काष्ठा platक्रमm_device *op,
			    पूर्णांक temp_idx)
अणु
	काष्ठा bbc_cpu_temperature *tp;

	tp = kzalloc(माप(*tp), GFP_KERNEL);
	अगर (!tp)
		वापस;

	INIT_LIST_HEAD(&tp->bp_list);
	INIT_LIST_HEAD(&tp->glob_list);

	tp->client = bbc_i2c_attach(bp, op);
	अगर (!tp->client) अणु
		kमुक्त(tp);
		वापस;
	पूर्ण


	tp->index = temp_idx;

	list_add(&tp->glob_list, &all_temps);
	list_add(&tp->bp_list, &bp->temps);

	/* Tell it to convert once every 5 seconds, clear all cfg
	 * bits.
	 */
	bbc_i2c_ग_लिखोb(tp->client, 0x00, MAX1617_WR_CFG_BYTE);
	bbc_i2c_ग_लिखोb(tp->client, 0x02, MAX1617_WR_CVRATE_BYTE);

	/* Program the hard temperature limits पूर्णांकo the chip. */
	bbc_i2c_ग_लिखोb(tp->client, amb_temp_limits[tp->index].high_pwroff,
		       MAX1617_WR_AMB_HIGHLIM);
	bbc_i2c_ग_लिखोb(tp->client, amb_temp_limits[tp->index].low_pwroff,
		       MAX1617_WR_AMB_LOWLIM);
	bbc_i2c_ग_लिखोb(tp->client, cpu_temp_limits[tp->index].high_pwroff,
		       MAX1617_WR_CPU_HIGHLIM);
	bbc_i2c_ग_लिखोb(tp->client, cpu_temp_limits[tp->index].low_pwroff,
		       MAX1617_WR_CPU_LOWLIM);

	get_current_temps(tp);
	tp->prev_cpu_temp = tp->avg_cpu_temp = tp->curr_cpu_temp;
	tp->prev_amb_temp = tp->avg_amb_temp = tp->curr_amb_temp;

	tp->fan_toकरो[FAN_AMBIENT] = FAN_SAME;
	tp->fan_toकरो[FAN_CPU] = FAN_SAME;
पूर्ण

अटल व्योम attach_one_fan(काष्ठा bbc_i2c_bus *bp, काष्ठा platक्रमm_device *op,
			   पूर्णांक fan_idx)
अणु
	काष्ठा bbc_fan_control *fp;

	fp = kzalloc(माप(*fp), GFP_KERNEL);
	अगर (!fp)
		वापस;

	INIT_LIST_HEAD(&fp->bp_list);
	INIT_LIST_HEAD(&fp->glob_list);

	fp->client = bbc_i2c_attach(bp, op);
	अगर (!fp->client) अणु
		kमुक्त(fp);
		वापस;
	पूर्ण

	fp->index = fan_idx;

	list_add(&fp->glob_list, &all_fans);
	list_add(&fp->bp_list, &bp->fans);

	/* The i2c device controlling the fans is ग_लिखो-only.
	 * So the only way to keep track of the current घातer
	 * level fed to the fans is via software.  Choose half
	 * घातer क्रम cpu/प्रणाली and 'on' fo the घातersupply fan
	 * and set it now.
	 */
	fp->psupply_fan_on = 1;
	fp->cpu_fan_speed = (FAN_SPEED_MAX - FAN_SPEED_MIN) / 2;
	fp->cpu_fan_speed += FAN_SPEED_MIN;
	fp->प्रणाली_fan_speed = (FAN_SPEED_MAX - FAN_SPEED_MIN) / 2;
	fp->प्रणाली_fan_speed += FAN_SPEED_MIN;

	set_fan_speeds(fp);
पूर्ण

अटल व्योम destroy_one_temp(काष्ठा bbc_cpu_temperature *tp)
अणु
	bbc_i2c_detach(tp->client);
	kमुक्त(tp);
पूर्ण

अटल व्योम destroy_all_temps(काष्ठा bbc_i2c_bus *bp)
अणु
	काष्ठा bbc_cpu_temperature *tp, *tpos;

	list_क्रम_each_entry_safe(tp, tpos, &bp->temps, bp_list) अणु
		list_del(&tp->bp_list);
		list_del(&tp->glob_list);
		destroy_one_temp(tp);
	पूर्ण
पूर्ण

अटल व्योम destroy_one_fan(काष्ठा bbc_fan_control *fp)
अणु
	bbc_i2c_detach(fp->client);
	kमुक्त(fp);
पूर्ण

अटल व्योम destroy_all_fans(काष्ठा bbc_i2c_bus *bp)
अणु
	काष्ठा bbc_fan_control *fp, *fpos;

	list_क्रम_each_entry_safe(fp, fpos, &bp->fans, bp_list) अणु
		list_del(&fp->bp_list);
		list_del(&fp->glob_list);
		destroy_one_fan(fp);
	पूर्ण
पूर्ण

पूर्णांक bbc_envctrl_init(काष्ठा bbc_i2c_bus *bp)
अणु
	काष्ठा platक्रमm_device *op;
	पूर्णांक temp_index = 0;
	पूर्णांक fan_index = 0;
	पूर्णांक devidx = 0;

	जबतक ((op = bbc_i2c_getdev(bp, devidx++)) != शून्य) अणु
		अगर (of_node_name_eq(op->dev.of_node, "temperature"))
			attach_one_temp(bp, op, temp_index++);
		अगर (of_node_name_eq(op->dev.of_node, "fan-control"))
			attach_one_fan(bp, op, fan_index++);
	पूर्ण
	अगर (temp_index != 0 && fan_index != 0) अणु
		kenvctrld_task = kthपढ़ो_run(kenvctrld, शून्य, "kenvctrld");
		अगर (IS_ERR(kenvctrld_task)) अणु
			पूर्णांक err = PTR_ERR(kenvctrld_task);

			kenvctrld_task = शून्य;
			destroy_all_temps(bp);
			destroy_all_fans(bp);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम bbc_envctrl_cleanup(काष्ठा bbc_i2c_bus *bp)
अणु
	अगर (kenvctrld_task)
		kthपढ़ो_stop(kenvctrld_task);

	destroy_all_temps(bp);
	destroy_all_fans(bp);
पूर्ण
