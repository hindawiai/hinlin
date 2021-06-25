<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 	NetWinder Button Driver-
 *	Copyright (C) Alex Holden <alex@linuxhacker.org> 1998, 1999.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयr.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#घोषणा __NWBUTTON_C		/* Tell the header file who we are */
#समावेश "nwbutton.h"

अटल व्योम button_sequence_finished(काष्ठा समयr_list *unused);

अटल पूर्णांक button_press_count;		/* The count of button presses */
/* Times क्रम the end of a sequence */
अटल DEFINE_TIMER(button_समयr, button_sequence_finished);
अटल DECLARE_WAIT_QUEUE_HEAD(button_रुको_queue); /* Used क्रम blocking पढ़ो */
अटल अक्षर button_output_buffer[32];	/* Stores data to ग_लिखो out of device */
अटल पूर्णांक bcount;			/* The number of bytes in the buffer */
अटल पूर्णांक bdelay = BUTTON_DELAY;	/* The delay, in jअगरfies */
अटल काष्ठा button_callback button_callback_list[32]; /* The callback list */
अटल पूर्णांक callback_count;		/* The number of callbacks रेजिस्टरed */
अटल पूर्णांक reboot_count = NUM_PRESSES_REBOOT; /* Number of presses to reboot */

/*
 * This function is called by other drivers to रेजिस्टर a callback function
 * to be called when a particular number of button presses occurs.
 * The callback list is a अटल array of 32 entries (I somehow करोubt many
 * people are ever going to want to रेजिस्टर more than 32 dअगरferent actions
 * to be perक्रमmed by the kernel on dअगरferent numbers of button presses ;).
 * However, अगर an attempt to रेजिस्टर a 33rd entry (perhaps a stuck loop
 * somewhere रेजिस्टरing the same entry over and over?) it will fail to
 * करो so and वापस -ENOMEM. If an attempt is made to रेजिस्टर a null poपूर्णांकer,
 * it will fail to करो so and वापस -EINVAL.
 * Because callbacks can be unरेजिस्टरed at अक्रमom the list can become
 * fragmented, so we need to search through the list until we find the first
 * मुक्त entry.
 *
 * FIXME: Has anyone spotted any locking functions पूर्णांक his code recently ??
 */

पूर्णांक button_add_callback (व्योम (*callback) (व्योम), पूर्णांक count)
अणु
	पूर्णांक lp = 0;
	अगर (callback_count == 32) अणु
		वापस -ENOMEM;
	पूर्ण
	अगर (!callback) अणु
		वापस -EINVAL;
	पूर्ण
	callback_count++;
	क्रम (; (button_callback_list [lp].callback); lp++);
	button_callback_list [lp].callback = callback;
	button_callback_list [lp].count = count;
	वापस 0;
पूर्ण

/*
 * This function is called by other drivers to deरेजिस्टर a callback function.
 * If you attempt to unरेजिस्टर a callback which करोes not exist, it will fail
 * with -EINVAL. If there is more than one entry with the same address,
 * because it searches the list from end to beginning, it will unरेजिस्टर the
 * last one to be रेजिस्टरed first (FILO- First In Last Out).
 * Note that this is not necessarily true अगर the entries are not submitted
 * at the same समय, because another driver could have unरेजिस्टरed a callback
 * between the submissions creating a gap earlier in the list, which would
 * be filled first at submission समय.
 */

पूर्णांक button_del_callback (व्योम (*callback) (व्योम))
अणु
	पूर्णांक lp = 31;
	अगर (!callback) अणु
		वापस -EINVAL;
	पूर्ण
	जबतक (lp >= 0) अणु
		अगर ((button_callback_list [lp].callback) == callback) अणु
			button_callback_list [lp].callback = शून्य;
			button_callback_list [lp].count = 0;
			callback_count--;
			वापस 0;
		पूर्ण
		lp--;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * This function is called by button_sequence_finished to search through the
 * list of callback functions, and call any of them whose count argument
 * matches the current count of button presses. It starts at the beginning
 * of the list and works up to the end. It will refuse to follow a null
 * poपूर्णांकer (which should never happen anyway).
 */

अटल व्योम button_consume_callbacks (पूर्णांक bpcount)
अणु
	पूर्णांक lp = 0;
	क्रम (; lp <= 31; lp++) अणु
		अगर ((button_callback_list [lp].count) == bpcount) अणु
			अगर (button_callback_list [lp].callback) अणु
				button_callback_list[lp].callback();
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* 
 * This function is called when the button_समयr बार out.
 * ie. When you करोn't press the button क्रम bdelay jअगरfies, this is taken to
 * mean you have ended the sequence of key presses, and this function is
 * called to wind things up (ग_लिखो the press_count out to /dev/button, call
 * any matching रेजिस्टरed function callbacks, initiate reboot, etc.).
 */

अटल व्योम button_sequence_finished(काष्ठा समयr_list *unused)
अणु
	अगर (IS_ENABLED(CONFIG_NWBUTTON_REBOOT) &&
	    button_press_count == reboot_count)
		समाप्त_cad_pid(संक_विघ्न, 1);	/* Ask init to reboot us */
	button_consume_callbacks (button_press_count);
	bcount = प्र_लिखो (button_output_buffer, "%d\n", button_press_count);
	button_press_count = 0;		/* Reset the button press counter */
	wake_up_पूर्णांकerruptible (&button_रुको_queue);
पूर्ण

/* 
 *  This handler is called when the orange button is pressed (GPIO 10 of the
 *  SuperIO chip, which maps to logical IRQ 26). If the press_count is 0,
 *  this is the first press, so it starts a समयr and increments the counter.
 *  If it is higher than 0, it deletes the old समयr, starts a new one, and
 *  increments the counter.
 */ 

अटल irqवापस_t button_handler (पूर्णांक irq, व्योम *dev_id)
अणु
	button_press_count++;
	mod_समयr(&button_समयr, jअगरfies + bdelay);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * This function is called when a user space program attempts to पढ़ो
 * /dev/nwbutton. It माला_दो the device to sleep on the रुको queue until
 * button_sequence_finished ग_लिखोs some data to the buffer and flushes
 * the queue, at which poपूर्णांक it ग_लिखोs the data out to the device and
 * वापसs the number of अक्षरacters it has written. This function is
 * reentrant, so that many processes can be attempting to पढ़ो from the
 * device at any one समय.
 */

अटल पूर्णांक button_पढ़ो (काष्ठा file *filp, अक्षर __user *buffer,
			माप_प्रकार count, loff_t *ppos)
अणु
	DEFINE_WAIT(रुको);
	prepare_to_रुको(&button_रुको_queue, &रुको, TASK_INTERRUPTIBLE);
	schedule();
	finish_रुको(&button_रुको_queue, &रुको);
	वापस (copy_to_user (buffer, &button_output_buffer, bcount))
		 ? -EFAULT : bcount;
पूर्ण

/* 
 * This काष्ठाure is the file operations काष्ठाure, which specअगरies what
 * callbacks functions the kernel should call when a user mode process
 * attempts to perक्रमm these operations on the device.
 */

अटल स्थिर काष्ठा file_operations button_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= button_पढ़ो,
	.llseek		= noop_llseek,
पूर्ण;

/* 
 * This काष्ठाure is the misc device काष्ठाure, which specअगरies the minor
 * device number (158 in this हाल), the name of the device (क्रम /proc/misc),
 * and the address of the above file operations काष्ठाure.
 */

अटल काष्ठा miscdevice button_misc_device = अणु
	BUTTON_MINOR,
	"nwbutton",
	&button_fops,
पूर्ण;

/*
 * This function is called to initialise the driver, either from misc.c at
 * bootup अगर the driver is compiled पूर्णांकo the kernel, or from init_module
 * below at module insert समय. It attempts to रेजिस्टर the device node
 * and the IRQ and fails with a warning message अगर either fails, though
 * neither ever should because the device number and IRQ are unique to
 * this driver.
 */

अटल पूर्णांक __init nwbutton_init(व्योम)
अणु
	अगर (!machine_is_netwinder())
		वापस -ENODEV;

	prपूर्णांकk (KERN_INFO "NetWinder Button Driver Version %s (C) Alex Holden "
			"<alex@linuxhacker.org> 1998.\n", VERSION);

	अगर (misc_रेजिस्टर (&button_misc_device)) अणु
		prपूर्णांकk (KERN_WARNING "nwbutton: Couldn't register device 10, "
				"%d.\n", BUTTON_MINOR);
		वापस -EBUSY;
	पूर्ण

	अगर (request_irq (IRQ_NETWINDER_BUTTON, button_handler, 0,
			"nwbutton", शून्य)) अणु
		prपूर्णांकk (KERN_WARNING "nwbutton: IRQ %d is not free.\n",
				IRQ_NETWINDER_BUTTON);
		misc_deरेजिस्टर (&button_misc_device);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास nwbutton_निकास (व्योम) 
अणु
	मुक्त_irq (IRQ_NETWINDER_BUTTON, शून्य);
	misc_deरेजिस्टर (&button_misc_device);
पूर्ण


MODULE_AUTHOR("Alex Holden");
MODULE_LICENSE("GPL");

module_init(nwbutton_init);
module_निकास(nwbutton_निकास);
