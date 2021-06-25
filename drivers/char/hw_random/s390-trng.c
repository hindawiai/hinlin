<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * s390 TRNG device driver
 *
 * Driver क्रम the TRNG (true अक्रमom number generation) command
 * available via CPACF extension MSA 7 on the s390 arch.

 * Copyright IBM Corp. 2017
 * Author(s): Harald Freudenberger <freude@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "trng"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/atomic.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/cpacf.h>

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("IBM Corporation");
MODULE_DESCRIPTION("s390 CPACF TRNG device driver");


/* trng related debug feature things */

अटल debug_info_t *debug_info;

#घोषणा DEBUG_DBG(...)	debug_प्र_लिखो_event(debug_info, 6, ##__VA_ARGS__)
#घोषणा DEBUG_INFO(...) debug_प्र_लिखो_event(debug_info, 5, ##__VA_ARGS__)
#घोषणा DEBUG_WARN(...) debug_प्र_लिखो_event(debug_info, 4, ##__VA_ARGS__)
#घोषणा DEBUG_ERR(...)	debug_प्र_लिखो_event(debug_info, 3, ##__VA_ARGS__)


/* trng helpers */

अटल atomic64_t trng_dev_counter = ATOMIC64_INIT(0);
अटल atomic64_t trng_hwrng_counter = ATOMIC64_INIT(0);


/* file io functions */

अटल पूर्णांक trng_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल sमाप_प्रकार trng_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
			 माप_प्रकार nbytes, loff_t *ppos)
अणु
	u8 buf[32];
	u8 *p = buf;
	अचिन्हित पूर्णांक n;
	sमाप_प्रकार ret = 0;

	/*
	 * use buf क्रम requests <= माप(buf),
	 * otherwise allocate one page and fetch
	 * pagewise.
	 */

	अगर (nbytes > माप(buf)) अणु
		p = (u8 *) __get_मुक्त_page(GFP_KERNEL);
		अगर (!p)
			वापस -ENOMEM;
	पूर्ण

	जबतक (nbytes) अणु
		अगर (need_resched()) अणु
			अगर (संकेत_pending(current)) अणु
				अगर (ret == 0)
					ret = -ERESTARTSYS;
				अवरोध;
			पूर्ण
			schedule();
		पूर्ण
		n = nbytes > PAGE_SIZE ? PAGE_SIZE : nbytes;
		cpacf_trng(शून्य, 0, p, n);
		atomic64_add(n, &trng_dev_counter);
		अगर (copy_to_user(ubuf, p, n)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		nbytes -= n;
		ubuf += n;
		ret += n;
	पूर्ण

	अगर (p != buf)
		मुक्त_page((अचिन्हित दीर्घ) p);

	DEBUG_DBG("trng_read()=%zd\n", ret);
	वापस ret;
पूर्ण


/* sysfs */

अटल sमाप_प्रकार trng_counter_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u64 dev_counter = atomic64_पढ़ो(&trng_dev_counter);
	u64 hwrng_counter = atomic64_पढ़ो(&trng_hwrng_counter);
#अगर IS_ENABLED(CONFIG_ARCH_RANDOM)
	u64 arch_counter = atomic64_पढ़ो(&s390_arch_अक्रमom_counter);

	वापस snम_लिखो(buf, PAGE_SIZE,
			"trng:  %llu\n"
			"hwrng: %llu\n"
			"arch:  %llu\n"
			"total: %llu\n",
			dev_counter, hwrng_counter, arch_counter,
			dev_counter + hwrng_counter + arch_counter);
#अन्यथा
	वापस snम_लिखो(buf, PAGE_SIZE,
			"trng:  %llu\n"
			"hwrng: %llu\n"
			"total: %llu\n",
			dev_counter, hwrng_counter,
			dev_counter + hwrng_counter);
#पूर्ण_अगर
पूर्ण
अटल DEVICE_ATTR(byte_counter, 0444, trng_counter_show, शून्य);

अटल काष्ठा attribute *trng_dev_attrs[] = अणु
	&dev_attr_byte_counter.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group trng_dev_attr_group = अणु
	.attrs = trng_dev_attrs
पूर्ण;

अटल स्थिर काष्ठा attribute_group *trng_dev_attr_groups[] = अणु
	&trng_dev_attr_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा file_operations trng_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= &trng_खोलो,
	.release	= शून्य,
	.पढ़ो		= &trng_पढ़ो,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice trng_dev = अणु
	.name	= "trng",
	.minor	= MISC_DYNAMIC_MINOR,
	.mode	= 0444,
	.fops	= &trng_fops,
	.groups = trng_dev_attr_groups,
पूर्ण;


/* hwrng_रेजिस्टर */

अटल अंतरभूत व्योम _trng_hwrng_पढ़ो(u8 *buf, माप_प्रकार len)
अणु
	cpacf_trng(शून्य, 0, buf, len);
	atomic64_add(len, &trng_hwrng_counter);
पूर्ण

अटल पूर्णांक trng_hwrng_data_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	माप_प्रकार len = माप(*data);

	_trng_hwrng_पढ़ो((u8 *) data, len);

	DEBUG_DBG("trng_hwrng_data_read()=%zu\n", len);

	वापस len;
पूर्ण

अटल पूर्णांक trng_hwrng_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max, bool रुको)
अणु
	माप_प्रकार len = max <= PAGE_SIZE ? max : PAGE_SIZE;

	_trng_hwrng_पढ़ो((u8 *) data, len);

	DEBUG_DBG("trng_hwrng_read()=%zu\n", len);

	वापस len;
पूर्ण

/*
 * hwrng रेजिस्टर काष्ठा
 * The trng is supposed to have 100% entropy, and thus we रेजिस्टर with a very
 * high quality value. If we ever have a better driver in the future, we should
 * change this value again when we merge this driver.
 */
अटल काष्ठा hwrng trng_hwrng_dev = अणु
	.name		= "s390-trng",
	.data_पढ़ो	= trng_hwrng_data_पढ़ो,
	.पढ़ो		= trng_hwrng_पढ़ो,
	.quality	= 1024,
पूर्ण;


/* init and निकास */

अटल व्योम __init trng_debug_init(व्योम)
अणु
	debug_info = debug_रेजिस्टर("trng", 1, 1, 4 * माप(दीर्घ));
	debug_रेजिस्टर_view(debug_info, &debug_प्र_लिखो_view);
	debug_set_level(debug_info, 3);
पूर्ण

अटल व्योम trng_debug_निकास(व्योम)
अणु
	debug_unरेजिस्टर(debug_info);
पूर्ण

अटल पूर्णांक __init trng_init(व्योम)
अणु
	पूर्णांक ret;

	trng_debug_init();

	/* check अगर subfunction CPACF_PRNO_TRNG is available */
	अगर (!cpacf_query_func(CPACF_PRNO, CPACF_PRNO_TRNG)) अणु
		DEBUG_INFO("trng_init CPACF_PRNO_TRNG not available\n");
		ret = -ENODEV;
		जाओ out_dbg;
	पूर्ण

	ret = misc_रेजिस्टर(&trng_dev);
	अगर (ret) अणु
		DEBUG_WARN("trng_init misc_register() failed rc=%d\n", ret);
		जाओ out_dbg;
	पूर्ण

	ret = hwrng_रेजिस्टर(&trng_hwrng_dev);
	अगर (ret) अणु
		DEBUG_WARN("trng_init hwrng_register() failed rc=%d\n", ret);
		जाओ out_misc;
	पूर्ण

	DEBUG_DBG("trng_init successful\n");

	वापस 0;

out_misc:
	misc_deरेजिस्टर(&trng_dev);
out_dbg:
	trng_debug_निकास();
	वापस ret;
पूर्ण

अटल व्योम __निकास trng_निकास(व्योम)
अणु
	hwrng_unरेजिस्टर(&trng_hwrng_dev);
	misc_deरेजिस्टर(&trng_dev);
	trng_debug_निकास();
पूर्ण

module_cpu_feature_match(MSA, trng_init);
module_निकास(trng_निकास);
