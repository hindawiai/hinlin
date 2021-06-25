<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Alchemy Development Board example suspend userspace पूर्णांकerface.
 *
 * (c) 2008 Manuel Lauss <mano@roarinelk.homelinux.net>
 */

#समावेश <linux/init.h>
#समावेश <linux/kobject.h>
#समावेश <linux/suspend.h>
#समावेश <linux/sysfs.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/gpio-au1000.h>
#समावेश <यंत्र/mach-db1x00/bcsr.h>

/*
 * Generic suspend userspace पूर्णांकerface क्रम Alchemy development boards.
 * This code exports a few sysfs nodes under /sys/घातer/db1x/ which
 * can be used by userspace to en/disable all au1x-provided wakeup
 * sources and configure the समयout after which the the TOYMATCH2 irq
 * is to trigger a wakeup.
 */


अटल अचिन्हित दीर्घ db1x_pm_sleep_secs;
अटल अचिन्हित दीर्घ db1x_pm_wakemsk;
अटल अचिन्हित दीर्घ db1x_pm_last_wakesrc;

अटल पूर्णांक db1x_pm_enter(suspend_state_t state)
अणु
	अचिन्हित लघु bcsrs[16];
	पूर्णांक i, j, hasपूर्णांक;

	/* save CPLD regs */
	hasपूर्णांक = bcsr_पढ़ो(BCSR_WHOAMI);
	hasपूर्णांक = BCSR_WHOAMI_BOARD(hasपूर्णांक) >= BCSR_WHOAMI_DB1200;
	j = (hasपूर्णांक) ? BCSR_MASKSET : BCSR_SYSTEM;

	क्रम (i = BCSR_STATUS; i <= j; i++)
		bcsrs[i] = bcsr_पढ़ो(i);

	/* shut off hexleds */
	bcsr_ग_लिखो(BCSR_HEXCLEAR, 3);

	/* enable GPIO based wakeup */
	alchemy_gpio1_input_enable();

	/* clear and setup wake cause and source */
	alchemy_wrsys(0, AU1000_SYS_WAKEMSK);
	alchemy_wrsys(0, AU1000_SYS_WAKESRC);

	alchemy_wrsys(db1x_pm_wakemsk, AU1000_SYS_WAKEMSK);

	/* setup 1Hz-समयr-based wakeup: रुको क्रम reg access */
	जबतक (alchemy_rdsys(AU1000_SYS_CNTRCTRL) & SYS_CNTRL_M20)
		यंत्र अस्थिर ("nop");

	alchemy_wrsys(alchemy_rdsys(AU1000_SYS_TOYREAD) + db1x_pm_sleep_secs,
		      AU1000_SYS_TOYMATCH2);

	/* रुको क्रम value to really hit the रेजिस्टर */
	जबतक (alchemy_rdsys(AU1000_SYS_CNTRCTRL) & SYS_CNTRL_M20)
		यंत्र अस्थिर ("nop");

	/* ...and now the sandman can come! */
	au_sleep();


	/* restore CPLD regs */
	क्रम (i = BCSR_STATUS; i <= BCSR_SYSTEM; i++)
		bcsr_ग_लिखो(i, bcsrs[i]);

	/* restore CPLD पूर्णांक रेजिस्टरs */
	अगर (hasपूर्णांक) अणु
		bcsr_ग_लिखो(BCSR_INTCLR, 0xffff);
		bcsr_ग_लिखो(BCSR_MASKCLR, 0xffff);
		bcsr_ग_लिखो(BCSR_INTSTAT, 0xffff);
		bcsr_ग_लिखो(BCSR_INTSET, bcsrs[BCSR_INTSET]);
		bcsr_ग_लिखो(BCSR_MASKSET, bcsrs[BCSR_MASKSET]);
	पूर्ण

	/* light up hexleds */
	bcsr_ग_लिखो(BCSR_HEXCLEAR, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक db1x_pm_begin(suspend_state_t state)
अणु
	अगर (!db1x_pm_wakemsk) अणु
		prपूर्णांकk(KERN_ERR "db1x: no wakeup source activated!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम db1x_pm_end(व्योम)
अणु
	/* पढ़ो and store wakeup source, the clear the रेजिस्टर. To
	 * be able to clear it, WAKEMSK must be cleared first.
	 */
	db1x_pm_last_wakesrc = alchemy_rdsys(AU1000_SYS_WAKESRC);

	alchemy_wrsys(0, AU1000_SYS_WAKEMSK);
	alchemy_wrsys(0, AU1000_SYS_WAKESRC);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops db1x_pm_ops = अणु
	.valid		= suspend_valid_only_mem,
	.begin		= db1x_pm_begin,
	.enter		= db1x_pm_enter,
	.end		= db1x_pm_end,
पूर्ण;

#घोषणा ATTRCMP(x) (0 == म_भेद(attr->attr.name, #x))

अटल sमाप_प्रकार db1x_pmattr_show(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr,
				अक्षर *buf)
अणु
	पूर्णांक idx;

	अगर (ATTRCMP(समयr_समयout))
		वापस प्र_लिखो(buf, "%lu\n", db1x_pm_sleep_secs);

	अन्यथा अगर (ATTRCMP(समयr))
		वापस प्र_लिखो(buf, "%u\n",
				!!(db1x_pm_wakemsk & SYS_WAKEMSK_M2));

	अन्यथा अगर (ATTRCMP(wakesrc))
		वापस प्र_लिखो(buf, "%lu\n", db1x_pm_last_wakesrc);

	अन्यथा अगर (ATTRCMP(gpio0) || ATTRCMP(gpio1) || ATTRCMP(gpio2) ||
		 ATTRCMP(gpio3) || ATTRCMP(gpio4) || ATTRCMP(gpio5) ||
		 ATTRCMP(gpio6) || ATTRCMP(gpio7)) अणु
		idx = (attr->attr.name)[4] - '0';
		वापस प्र_लिखो(buf, "%d\n",
			!!(db1x_pm_wakemsk & SYS_WAKEMSK_GPIO(idx)));

	पूर्ण अन्यथा अगर (ATTRCMP(wakemsk)) अणु
		वापस प्र_लिखो(buf, "%08lx\n", db1x_pm_wakemsk);
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल sमाप_प्रकार db1x_pmattr_store(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr,
				 स्थिर अक्षर *instr,
				 माप_प्रकार bytes)
अणु
	अचिन्हित दीर्घ l;
	पूर्णांक पंचांगp;

	अगर (ATTRCMP(समयr_समयout)) अणु
		पंचांगp = kम_से_अदीर्घ(instr, 0, &l);
		अगर (पंचांगp)
			वापस पंचांगp;

		db1x_pm_sleep_secs = l;

	पूर्ण अन्यथा अगर (ATTRCMP(समयr)) अणु
		अगर (instr[0] != '0')
			db1x_pm_wakemsk |= SYS_WAKEMSK_M2;
		अन्यथा
			db1x_pm_wakemsk &= ~SYS_WAKEMSK_M2;

	पूर्ण अन्यथा अगर (ATTRCMP(gpio0) || ATTRCMP(gpio1) || ATTRCMP(gpio2) ||
		   ATTRCMP(gpio3) || ATTRCMP(gpio4) || ATTRCMP(gpio5) ||
		   ATTRCMP(gpio6) || ATTRCMP(gpio7)) अणु
		पंचांगp = (attr->attr.name)[4] - '0';
		अगर (instr[0] != '0') अणु
			db1x_pm_wakemsk |= SYS_WAKEMSK_GPIO(पंचांगp);
		पूर्ण अन्यथा अणु
			db1x_pm_wakemsk &= ~SYS_WAKEMSK_GPIO(पंचांगp);
		पूर्ण

	पूर्ण अन्यथा अगर (ATTRCMP(wakemsk)) अणु
		पंचांगp = kम_से_अदीर्घ(instr, 0, &l);
		अगर (पंचांगp)
			वापस पंचांगp;

		db1x_pm_wakemsk = l & 0x0000003f;

	पूर्ण अन्यथा
		bytes = -ENOENT;

	वापस bytes;
पूर्ण

#घोषणा ATTR(x)							\
	अटल काष्ठा kobj_attribute x##_attribute =		\
		__ATTR(x, 0664, db1x_pmattr_show,		\
				db1x_pmattr_store);

ATTR(gpio0)		/* GPIO-based wakeup enable */
ATTR(gpio1)
ATTR(gpio2)
ATTR(gpio3)
ATTR(gpio4)
ATTR(gpio5)
ATTR(gpio6)
ATTR(gpio7)
ATTR(समयr)		/* TOYMATCH2-based wakeup enable */
ATTR(समयr_समयout)	/* समयr-based wakeup समयout value, in seconds */
ATTR(wakesrc)		/* contents of SYS_WAKESRC after last wakeup */
ATTR(wakemsk)		/* direct access to SYS_WAKEMSK */

#घोषणा ATTR_LIST(x)	& x ## _attribute.attr
अटल काष्ठा attribute *db1x_pmattrs[] = अणु
	ATTR_LIST(gpio0),
	ATTR_LIST(gpio1),
	ATTR_LIST(gpio2),
	ATTR_LIST(gpio3),
	ATTR_LIST(gpio4),
	ATTR_LIST(gpio5),
	ATTR_LIST(gpio6),
	ATTR_LIST(gpio7),
	ATTR_LIST(समयr),
	ATTR_LIST(समयr_समयout),
	ATTR_LIST(wakesrc),
	ATTR_LIST(wakemsk),
	शून्य,		/* terminator */
पूर्ण;

अटल काष्ठा attribute_group db1x_pmattr_group = अणु
	.name	= "db1x",
	.attrs	= db1x_pmattrs,
पूर्ण;

/*
 * Initialize suspend पूर्णांकerface
 */
अटल पूर्णांक __init pm_init(व्योम)
अणु
	/* init TOY to tick at 1Hz अगर not alपढ़ोy करोne. No need to रुको
	 * क्रम confirmation since there's plenty of समय from here to
	 * the next suspend cycle.
	 */
	अगर (alchemy_rdsys(AU1000_SYS_TOYTRIM) != 32767)
		alchemy_wrsys(32767, AU1000_SYS_TOYTRIM);

	db1x_pm_last_wakesrc = alchemy_rdsys(AU1000_SYS_WAKESRC);

	alchemy_wrsys(0, AU1000_SYS_WAKESRC);
	alchemy_wrsys(0, AU1000_SYS_WAKEMSK);

	suspend_set_ops(&db1x_pm_ops);

	वापस sysfs_create_group(घातer_kobj, &db1x_pmattr_group);
पूर्ण

late_initcall(pm_init);
