<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Real Time Clock पूर्णांकerface क्रम Linux on the MVME16x
 *
 * Based on the PC driver by Paul Gorपंचांगaker.
 */

#घोषणा RTC_VERSION		"1.00"

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/ioport.h>
#समावेश <linux/capability.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/rtc.h>	/* For काष्ठा rtc_समय and ioctls, etc */
#समावेश <linux/bcd.h>
#समावेश <यंत्र/mvme16xhw.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/setup.h>

/*
 *	We sponge a minor off of the misc major. No need slurping
 *	up another valuable major dev number क्रम this. If you add
 *	an ioctl, make sure you करोn't conflict with SPARC's RTC
 *	ioctls.
 */

अटल स्थिर अचिन्हित अक्षर days_in_mo[] =
अणु0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31पूर्ण;

अटल atomic_t rtc_पढ़ोy = ATOMIC_INIT(1);

अटल दीर्घ rtc_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अस्थिर MK48T08ptr_t rtc = (MK48T08ptr_t)MVME_RTC_BASE;
	अचिन्हित दीर्घ flags;
	काष्ठा rtc_समय wसमय;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल RTC_RD_TIME:	/* Read the समय/date from RTC	*/
	अणु
		local_irq_save(flags);
		/* Ensure घड़ी and real-समय-mode-रेजिस्टर are accessible */
		rtc->ctrl = RTC_READ;
		स_रखो(&wसमय, 0, माप(काष्ठा rtc_समय));
		wसमय.पंचांग_sec =  bcd2bin(rtc->bcd_sec);
		wसमय.पंचांग_min =  bcd2bin(rtc->bcd_min);
		wसमय.पंचांग_hour = bcd2bin(rtc->bcd_hr);
		wसमय.पंचांग_mday =  bcd2bin(rtc->bcd_करोm);
		wसमय.पंचांग_mon =  bcd2bin(rtc->bcd_mth)-1;
		wसमय.पंचांग_year = bcd2bin(rtc->bcd_year);
		अगर (wसमय.पंचांग_year < 70)
			wसमय.पंचांग_year += 100;
		wसमय.पंचांग_wday = bcd2bin(rtc->bcd_करोw)-1;
		rtc->ctrl = 0;
		local_irq_restore(flags);
		वापस copy_to_user(argp, &wसमय, माप wसमय) ?
								-EFAULT : 0;
	पूर्ण
	हाल RTC_SET_TIME:	/* Set the RTC */
	अणु
		काष्ठा rtc_समय rtc_पंचांग;
		अचिन्हित अक्षर mon, day, hrs, min, sec, leap_yr;
		अचिन्हित पूर्णांक yrs;

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EACCES;

		अगर (copy_from_user(&rtc_पंचांग, argp, माप(काष्ठा rtc_समय)))
			वापस -EFAULT;

		yrs = rtc_पंचांग.पंचांग_year;
		अगर (yrs < 1900)
			yrs += 1900;
		mon = rtc_पंचांग.पंचांग_mon + 1;   /* पंचांग_mon starts at zero */
		day = rtc_पंचांग.पंचांग_mday;
		hrs = rtc_पंचांग.पंचांग_hour;
		min = rtc_पंचांग.पंचांग_min;
		sec = rtc_पंचांग.पंचांग_sec;

		leap_yr = ((!(yrs % 4) && (yrs % 100)) || !(yrs % 400));

		अगर ((mon > 12) || (day == 0))
			वापस -EINVAL;

		अगर (day > (days_in_mo[mon] + ((mon == 2) && leap_yr)))
			वापस -EINVAL;

		अगर ((hrs >= 24) || (min >= 60) || (sec >= 60))
			वापस -EINVAL;

		अगर (yrs >= 2070)
			वापस -EINVAL;

		local_irq_save(flags);
		rtc->ctrl     = RTC_WRITE;

		rtc->bcd_sec  = bin2bcd(sec);
		rtc->bcd_min  = bin2bcd(min);
		rtc->bcd_hr   = bin2bcd(hrs);
		rtc->bcd_करोm  = bin2bcd(day);
		rtc->bcd_mth  = bin2bcd(mon);
		rtc->bcd_year = bin2bcd(yrs%100);

		rtc->ctrl     = 0;
		local_irq_restore(flags);
		वापस 0;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * We enक्रमce only one user at a समय here with the खोलो/बंद.
 */
अटल पूर्णांक rtc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर( !atomic_dec_and_test(&rtc_पढ़ोy) )
	अणु
		atomic_inc( &rtc_पढ़ोy );
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	atomic_inc( &rtc_पढ़ोy );
	वापस 0;
पूर्ण

/*
 *	The various file operations we support.
 */

अटल स्थिर काष्ठा file_operations rtc_fops = अणु
	.unlocked_ioctl	= rtc_ioctl,
	.खोलो		= rtc_खोलो,
	.release	= rtc_release,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice rtc_dev=
अणु
	.minor =	RTC_MINOR,
	.name =		"rtc",
	.fops =		&rtc_fops
पूर्ण;

अटल पूर्णांक __init rtc_MK48T08_init(व्योम)
अणु
	अगर (!MACH_IS_MVME16x)
		वापस -ENODEV;

	pr_info("MK48T08 Real Time Clock Driver v%s\n", RTC_VERSION);
	वापस misc_रेजिस्टर(&rtc_dev);
पूर्ण
device_initcall(rtc_MK48T08_init);
