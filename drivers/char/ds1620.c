<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/अक्षर/ds1620.c: Dallas Semiconductors DS1620
 *   thermometer driver (as used in the Rebel.com NetWinder)
 */
#समावेश <linux/module.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/capability.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/therm.h>

#अगर_घोषित CONFIG_PROC_FS
/* define क्रम /proc पूर्णांकerface */
#घोषणा THERM_USE_PROC
#पूर्ण_अगर

/* Definitions क्रम DS1620 chip */
#घोषणा THERM_START_CONVERT	0xee
#घोषणा THERM_RESET		0xaf
#घोषणा THERM_READ_CONFIG	0xac
#घोषणा THERM_READ_TEMP		0xaa
#घोषणा THERM_READ_TL		0xa2
#घोषणा THERM_READ_TH		0xa1
#घोषणा THERM_WRITE_CONFIG	0x0c
#घोषणा THERM_WRITE_TL		0x02
#घोषणा THERM_WRITE_TH		0x01

#घोषणा CFG_CPU			2
#घोषणा CFG_1SHOT		1

अटल DEFINE_MUTEX(ds1620_mutex);
अटल स्थिर अक्षर *fan_state[] = अणु "off", "on", "on (hardwired)" पूर्ण;

/*
 * Start of NetWinder specअगरics
 *  Note!  We have to hold the gpio lock with IRQs disabled over the
 *  whole of our transaction to the Dallas chip, since there is a
 *  chance that the WaveArtist driver could touch these bits to
 *  enable or disable the speaker.
 */
बाह्य अचिन्हित पूर्णांक प्रणाली_rev;

अटल अंतरभूत व्योम netwinder_ds1620_set_clk(पूर्णांक clk)
अणु
	nw_gpio_modअगरy_op(GPIO_DSCLK, clk ? GPIO_DSCLK : 0);
पूर्ण

अटल अंतरभूत व्योम netwinder_ds1620_set_data(पूर्णांक dat)
अणु
	nw_gpio_modअगरy_op(GPIO_DATA, dat ? GPIO_DATA : 0);
पूर्ण

अटल अंतरभूत पूर्णांक netwinder_ds1620_get_data(व्योम)
अणु
	वापस nw_gpio_पढ़ो() & GPIO_DATA;
पूर्ण

अटल अंतरभूत व्योम netwinder_ds1620_set_data_dir(पूर्णांक dir)
अणु
	nw_gpio_modअगरy_io(GPIO_DATA, dir ? GPIO_DATA : 0);
पूर्ण

अटल अंतरभूत व्योम netwinder_ds1620_reset(व्योम)
अणु
	nw_cpld_modअगरy(CPLD_DS_ENABLE, 0);
	nw_cpld_modअगरy(CPLD_DS_ENABLE, CPLD_DS_ENABLE);
पूर्ण

अटल अंतरभूत व्योम netwinder_lock(अचिन्हित दीर्घ *flags)
अणु
	raw_spin_lock_irqsave(&nw_gpio_lock, *flags);
पूर्ण

अटल अंतरभूत व्योम netwinder_unlock(अचिन्हित दीर्घ *flags)
अणु
	raw_spin_unlock_irqrestore(&nw_gpio_lock, *flags);
पूर्ण

अटल अंतरभूत व्योम netwinder_set_fan(पूर्णांक i)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&nw_gpio_lock, flags);
	nw_gpio_modअगरy_op(GPIO_FAN, i ? GPIO_FAN : 0);
	raw_spin_unlock_irqrestore(&nw_gpio_lock, flags);
पूर्ण

अटल अंतरभूत पूर्णांक netwinder_get_fan(व्योम)
अणु
	अगर ((प्रणाली_rev & 0xf000) == 0x4000)
		वापस FAN_ALWAYS_ON;

	वापस (nw_gpio_पढ़ो() & GPIO_FAN) ? FAN_ON : FAN_OFF;
पूर्ण

/*
 * End of NetWinder specअगरics
 */

अटल व्योम ds1620_send_bits(पूर्णांक nr, पूर्णांक value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr; i++) अणु
		netwinder_ds1620_set_data(value & 1);
		netwinder_ds1620_set_clk(0);
		udelay(1);
		netwinder_ds1620_set_clk(1);
		udelay(1);

		value >>= 1;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ds1620_recv_bits(पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक value = 0, mask = 1;
	पूर्णांक i;

	netwinder_ds1620_set_data(0);

	क्रम (i = 0; i < nr; i++) अणु
		netwinder_ds1620_set_clk(0);
		udelay(1);

		अगर (netwinder_ds1620_get_data())
			value |= mask;

		mask <<= 1;

		netwinder_ds1620_set_clk(1);
		udelay(1);
	पूर्ण

	वापस value;
पूर्ण

अटल व्योम ds1620_out(पूर्णांक cmd, पूर्णांक bits, पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags;

	netwinder_lock(&flags);
	netwinder_ds1620_set_clk(1);
	netwinder_ds1620_set_data_dir(0);
	netwinder_ds1620_reset();

	udelay(1);

	ds1620_send_bits(8, cmd);
	अगर (bits)
		ds1620_send_bits(bits, value);

	udelay(1);

	netwinder_ds1620_reset();
	netwinder_unlock(&flags);

	msleep(20);
पूर्ण

अटल अचिन्हित पूर्णांक ds1620_in(पूर्णांक cmd, पूर्णांक bits)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक value;

	netwinder_lock(&flags);
	netwinder_ds1620_set_clk(1);
	netwinder_ds1620_set_data_dir(0);
	netwinder_ds1620_reset();

	udelay(1);

	ds1620_send_bits(8, cmd);

	netwinder_ds1620_set_data_dir(1);
	value = ds1620_recv_bits(bits);

	netwinder_ds1620_reset();
	netwinder_unlock(&flags);

	वापस value;
पूर्ण

अटल पूर्णांक cvt_9_to_पूर्णांक(अचिन्हित पूर्णांक val)
अणु
	अगर (val & 0x100)
		val |= 0xfffffe00;

	वापस val;
पूर्ण

अटल व्योम ds1620_ग_लिखो_state(काष्ठा therm *therm)
अणु
	ds1620_out(THERM_WRITE_CONFIG, 8, CFG_CPU);
	ds1620_out(THERM_WRITE_TL, 9, therm->lo);
	ds1620_out(THERM_WRITE_TH, 9, therm->hi);
	ds1620_out(THERM_START_CONVERT, 0, 0);
पूर्ण

अटल व्योम ds1620_पढ़ो_state(काष्ठा therm *therm)
अणु
	therm->lo = cvt_9_to_पूर्णांक(ds1620_in(THERM_READ_TL, 9));
	therm->hi = cvt_9_to_पूर्णांक(ds1620_in(THERM_READ_TH, 9));
पूर्ण

अटल पूर्णांक ds1620_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस stream_खोलो(inode, file);
पूर्ण

अटल sमाप_प्रकार
ds1620_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *ptr)
अणु
	चिन्हित पूर्णांक cur_temp;
	चिन्हित अक्षर cur_temp_degF;

	cur_temp = cvt_9_to_पूर्णांक(ds1620_in(THERM_READ_TEMP, 9)) >> 1;

	/* convert to Fahrenheit, as per wdt.c */
	cur_temp_degF = (cur_temp * 9) / 5 + 32;

	अगर (copy_to_user(buf, &cur_temp_degF, 1))
		वापस -EFAULT;

	वापस 1;
पूर्ण

अटल पूर्णांक
ds1620_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा therm therm;
	जोड़ अणु
		काष्ठा therm __user *therm;
		पूर्णांक __user *i;
	पूर्ण uarg;
	पूर्णांक i;

	uarg.i = (पूर्णांक __user *)arg;

	चयन(cmd) अणु
	हाल CMD_SET_THERMOSTATE:
	हाल CMD_SET_THERMOSTATE2:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		अगर (cmd == CMD_SET_THERMOSTATE) अणु
			अगर (get_user(therm.hi, uarg.i))
				वापस -EFAULT;
			therm.lo = therm.hi - 3;
		पूर्ण अन्यथा अणु
			अगर (copy_from_user(&therm, uarg.therm, माप(therm)))
				वापस -EFAULT;
		पूर्ण

		therm.lo <<= 1;
		therm.hi <<= 1;

		ds1620_ग_लिखो_state(&therm);
		अवरोध;

	हाल CMD_GET_THERMOSTATE:
	हाल CMD_GET_THERMOSTATE2:
		ds1620_पढ़ो_state(&therm);

		therm.lo >>= 1;
		therm.hi >>= 1;

		अगर (cmd == CMD_GET_THERMOSTATE) अणु
			अगर (put_user(therm.hi, uarg.i))
				वापस -EFAULT;
		पूर्ण अन्यथा अणु
			अगर (copy_to_user(uarg.therm, &therm, माप(therm)))
				वापस -EFAULT;
		पूर्ण
		अवरोध;

	हाल CMD_GET_TEMPERATURE:
	हाल CMD_GET_TEMPERATURE2:
		i = cvt_9_to_पूर्णांक(ds1620_in(THERM_READ_TEMP, 9));

		अगर (cmd == CMD_GET_TEMPERATURE)
			i >>= 1;

		वापस put_user(i, uarg.i) ? -EFAULT : 0;

	हाल CMD_GET_STATUS:
		i = ds1620_in(THERM_READ_CONFIG, 8) & 0xe3;

		वापस put_user(i, uarg.i) ? -EFAULT : 0;

	हाल CMD_GET_FAN:
		i = netwinder_get_fan();

		वापस put_user(i, uarg.i) ? -EFAULT : 0;

	हाल CMD_SET_FAN:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		अगर (get_user(i, uarg.i))
			वापस -EFAULT;

		netwinder_set_fan(i);
		अवरोध;
		
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ
ds1620_unlocked_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;

	mutex_lock(&ds1620_mutex);
	ret = ds1620_ioctl(file, cmd, arg);
	mutex_unlock(&ds1620_mutex);

	वापस ret;
पूर्ण

#अगर_घोषित THERM_USE_PROC
अटल पूर्णांक ds1620_proc_therm_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा therm th;
	पूर्णांक temp;

	ds1620_पढ़ो_state(&th);
	temp =  cvt_9_to_पूर्णांक(ds1620_in(THERM_READ_TEMP, 9));

	seq_म_लिखो(m, "Thermostat: HI %i.%i, LOW %i.%i; temperature: %i.%i C, fan %s\n",
		   th.hi >> 1, th.hi & 1 ? 5 : 0,
		   th.lo >> 1, th.lo & 1 ? 5 : 0,
		   temp  >> 1, temp  & 1 ? 5 : 0,
		   fan_state[netwinder_get_fan()]);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations ds1620_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= ds1620_खोलो,
	.पढ़ो		= ds1620_पढ़ो,
	.unlocked_ioctl	= ds1620_unlocked_ioctl,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice ds1620_miscdev = अणु
	TEMP_MINOR,
	"temp",
	&ds1620_fops
पूर्ण;

अटल पूर्णांक __init ds1620_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा therm th, th_start;

	अगर (!machine_is_netwinder())
		वापस -ENODEV;

	ds1620_out(THERM_RESET, 0, 0);
	ds1620_out(THERM_WRITE_CONFIG, 8, CFG_CPU);
	ds1620_out(THERM_START_CONVERT, 0, 0);

	/*
	 * Trigger the fan to start by setting
	 * temperature high poपूर्णांक low.  This kicks
	 * the fan पूर्णांकo action.
	 */
	ds1620_पढ़ो_state(&th);
	th_start.lo = 0;
	th_start.hi = 1;
	ds1620_ग_लिखो_state(&th_start);

	msleep(2000);

	ds1620_ग_लिखो_state(&th);

	ret = misc_रेजिस्टर(&ds1620_miscdev);
	अगर (ret < 0)
		वापस ret;

#अगर_घोषित THERM_USE_PROC
	अगर (!proc_create_single("therm", 0, शून्य, ds1620_proc_therm_show))
		prपूर्णांकk(KERN_ERR "therm: unable to register /proc/therm\n");
#पूर्ण_अगर

	ds1620_पढ़ो_state(&th);
	ret = cvt_9_to_पूर्णांक(ds1620_in(THERM_READ_TEMP, 9));

	prपूर्णांकk(KERN_INFO "Thermostat: high %i.%i, low %i.%i, "
	       "current %i.%i C, fan %s.\n",
	       th.hi >> 1, th.hi & 1 ? 5 : 0,
	       th.lo >> 1, th.lo & 1 ? 5 : 0,
	       ret   >> 1, ret   & 1 ? 5 : 0,
	       fan_state[netwinder_get_fan()]);

	वापस 0;
पूर्ण

अटल व्योम __निकास ds1620_निकास(व्योम)
अणु
#अगर_घोषित THERM_USE_PROC
	हटाओ_proc_entry("therm", शून्य);
#पूर्ण_अगर
	misc_deरेजिस्टर(&ds1620_miscdev);
पूर्ण

module_init(ds1620_init);
module_निकास(ds1620_निकास);

MODULE_LICENSE("GPL");
