<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched/loadavg.h>

#समावेश <यंत्र/auxपन.स>

#घोषणा LED_MAX_LENGTH 8 /* maximum अक्षरs written to proc file */

अटल अंतरभूत व्योम led_toggle(व्योम)
अणु
	अचिन्हित अक्षर val = get_auxio();
	अचिन्हित अक्षर on, off;

	अगर (val & AUXIO_LED) अणु
		on = 0;
		off = AUXIO_LED;
	पूर्ण अन्यथा अणु
		on = AUXIO_LED;
		off = 0;
	पूर्ण

	set_auxio(on, off);
पूर्ण

अटल काष्ठा समयr_list led_blink_समयr;
अटल अचिन्हित दीर्घ led_blink_समयr_समयout;

अटल व्योम led_blink(काष्ठा समयr_list *unused)
अणु
	अचिन्हित दीर्घ समयout = led_blink_समयr_समयout;

	led_toggle();

	/* reschedule */
	अगर (!समयout) अणु /* blink according to load */
		led_blink_समयr.expires = jअगरfies +
			((1 + (avenrun[0] >> FSHIFT)) * HZ);
	पूर्ण अन्यथा अणु /* blink at user specअगरied पूर्णांकerval */
		led_blink_समयr.expires = jअगरfies + (समयout * HZ);
	पूर्ण
	add_समयr(&led_blink_समयr);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक led_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अगर (get_auxio() & AUXIO_LED)
		seq_माला_दो(m, "on\n");
	अन्यथा
		seq_माला_दो(m, "off\n");
	वापस 0;
पूर्ण

अटल पूर्णांक led_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, led_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार led_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			      माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *buf = शून्य;

	अगर (count > LED_MAX_LENGTH)
		count = LED_MAX_LENGTH;

	buf = memdup_user_nul(buffer, count);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	/* work around \न when echo'ing पूर्णांकo proc */
	अगर (buf[count - 1] == '\n')
		buf[count - 1] = '\0';

	/* beक्रमe we change anything we want to stop any running समयrs,
	 * otherwise calls such as on will have no persistent effect
	 */
	del_समयr_sync(&led_blink_समयr);

	अगर (!म_भेद(buf, "on")) अणु
		auxio_set_led(AUXIO_LED_ON);
	पूर्ण अन्यथा अगर (!म_भेद(buf, "toggle")) अणु
		led_toggle();
	पूर्ण अन्यथा अगर ((*buf > '0') && (*buf <= '9')) अणु
		led_blink_समयr_समयout = simple_म_से_अदीर्घ(buf, शून्य, 10);
		led_blink(&led_blink_समयr);
	पूर्ण अन्यथा अगर (!म_भेद(buf, "load")) अणु
		led_blink_समयr_समयout = 0;
		led_blink(&led_blink_समयr);
	पूर्ण अन्यथा अणु
		auxio_set_led(AUXIO_LED_OFF);
	पूर्ण

	kमुक्त(buf);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops led_proc_ops = अणु
	.proc_खोलो	= led_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= led_proc_ग_लिखो,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा proc_dir_entry *led;

#घोषणा LED_VERSION	"0.1"

अटल पूर्णांक __init led_init(व्योम)
अणु
	समयr_setup(&led_blink_समयr, led_blink, 0);

	led = proc_create("led", 0, शून्य, &led_proc_ops);
	अगर (!led)
		वापस -ENOMEM;

	prपूर्णांकk(KERN_INFO
	       "led: version %s, Lars Kotthoff <metalhead@metalhead.ws>\n",
	       LED_VERSION);

	वापस 0;
पूर्ण

अटल व्योम __निकास led_निकास(व्योम)
अणु
	हटाओ_proc_entry("led", शून्य);
	del_समयr_sync(&led_blink_समयr);
पूर्ण

module_init(led_init);
module_निकास(led_निकास);

MODULE_AUTHOR("Lars Kotthoff <metalhead@metalhead.ws>");
MODULE_DESCRIPTION("Provides control of the front LED on SPARC systems.");
MODULE_LICENSE("GPL");
MODULE_VERSION(LED_VERSION);
