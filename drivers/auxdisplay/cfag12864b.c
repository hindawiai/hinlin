<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Filename: cfag12864b.c
 *     Version: 0.1.0
 * Description: cfag12864b LCD driver
 *     Depends: ks0108
 *
 *      Author: Copyright (C) Miguel Ojeda <ojeda@kernel.org>
 *        Date: 2006-10-31
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/cdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/ks0108.h>
#समावेश <linux/cfag12864b.h>


#घोषणा CFAG12864B_NAME "cfag12864b"

/*
 * Module Parameters
 */

अटल अचिन्हित पूर्णांक cfag12864b_rate = CONFIG_CFAG12864B_RATE;
module_param(cfag12864b_rate, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(cfag12864b_rate,
	"Refresh rate (hertz)");

अचिन्हित पूर्णांक cfag12864b_getrate(व्योम)
अणु
	वापस cfag12864b_rate;
पूर्ण

/*
 * cfag12864b Commands
 *
 *	E = Enable संकेत
 *		Every समय E चयन from low to high,
 *		cfag12864b/ks0108 पढ़ोs the command/data.
 *
 *	CS1 = First ks0108controller.
 *		If high, the first ks0108 controller receives commands/data.
 *
 *	CS2 = Second ks0108 controller
 *		If high, the second ks0108 controller receives commands/data.
 *
 *	DI = Data/Inकाष्ठाion
 *		If low, cfag12864b will expect commands.
 *		If high, cfag12864b will expect data.
 *
 */

#घोषणा bit(n) (((अचिन्हित अक्षर)1)<<(n))

#घोषणा CFAG12864B_BIT_E	(0)
#घोषणा CFAG12864B_BIT_CS1	(2)
#घोषणा CFAG12864B_BIT_CS2	(1)
#घोषणा CFAG12864B_BIT_DI	(3)

अटल अचिन्हित अक्षर cfag12864b_state;

अटल व्योम cfag12864b_set(व्योम)
अणु
	ks0108_ग_लिखोcontrol(cfag12864b_state);
पूर्ण

अटल व्योम cfag12864b_setbit(अचिन्हित अक्षर state, अचिन्हित अक्षर n)
अणु
	अगर (state)
		cfag12864b_state |= bit(n);
	अन्यथा
		cfag12864b_state &= ~bit(n);
पूर्ण

अटल व्योम cfag12864b_e(अचिन्हित अक्षर state)
अणु
	cfag12864b_setbit(state, CFAG12864B_BIT_E);
	cfag12864b_set();
पूर्ण

अटल व्योम cfag12864b_cs1(अचिन्हित अक्षर state)
अणु
	cfag12864b_setbit(state, CFAG12864B_BIT_CS1);
पूर्ण

अटल व्योम cfag12864b_cs2(अचिन्हित अक्षर state)
अणु
	cfag12864b_setbit(state, CFAG12864B_BIT_CS2);
पूर्ण

अटल व्योम cfag12864b_di(अचिन्हित अक्षर state)
अणु
	cfag12864b_setbit(state, CFAG12864B_BIT_DI);
पूर्ण

अटल व्योम cfag12864b_setcontrollers(अचिन्हित अक्षर first,
	अचिन्हित अक्षर second)
अणु
	अगर (first)
		cfag12864b_cs1(0);
	अन्यथा
		cfag12864b_cs1(1);

	अगर (second)
		cfag12864b_cs2(0);
	अन्यथा
		cfag12864b_cs2(1);
पूर्ण

अटल व्योम cfag12864b_controller(अचिन्हित अक्षर which)
अणु
	अगर (which == 0)
		cfag12864b_setcontrollers(1, 0);
	अन्यथा अगर (which == 1)
		cfag12864b_setcontrollers(0, 1);
पूर्ण

अटल व्योम cfag12864b_displaystate(अचिन्हित अक्षर state)
अणु
	cfag12864b_di(0);
	cfag12864b_e(1);
	ks0108_displaystate(state);
	cfag12864b_e(0);
पूर्ण

अटल व्योम cfag12864b_address(अचिन्हित अक्षर address)
अणु
	cfag12864b_di(0);
	cfag12864b_e(1);
	ks0108_address(address);
	cfag12864b_e(0);
पूर्ण

अटल व्योम cfag12864b_page(अचिन्हित अक्षर page)
अणु
	cfag12864b_di(0);
	cfag12864b_e(1);
	ks0108_page(page);
	cfag12864b_e(0);
पूर्ण

अटल व्योम cfag12864b_startline(अचिन्हित अक्षर startline)
अणु
	cfag12864b_di(0);
	cfag12864b_e(1);
	ks0108_startline(startline);
	cfag12864b_e(0);
पूर्ण

अटल व्योम cfag12864b_ग_लिखोbyte(अचिन्हित अक्षर byte)
अणु
	cfag12864b_di(1);
	cfag12864b_e(1);
	ks0108_ग_लिखोdata(byte);
	cfag12864b_e(0);
पूर्ण

अटल व्योम cfag12864b_nop(व्योम)
अणु
	cfag12864b_startline(0);
पूर्ण

/*
 * cfag12864b Internal Commands
 */

अटल व्योम cfag12864b_on(व्योम)
अणु
	cfag12864b_setcontrollers(1, 1);
	cfag12864b_displaystate(1);
पूर्ण

अटल व्योम cfag12864b_off(व्योम)
अणु
	cfag12864b_setcontrollers(1, 1);
	cfag12864b_displaystate(0);
पूर्ण

अटल व्योम cfag12864b_clear(व्योम)
अणु
	अचिन्हित अक्षर i, j;

	cfag12864b_setcontrollers(1, 1);
	क्रम (i = 0; i < CFAG12864B_PAGES; i++) अणु
		cfag12864b_page(i);
		cfag12864b_address(0);
		क्रम (j = 0; j < CFAG12864B_ADDRESSES; j++)
			cfag12864b_ग_लिखोbyte(0);
	पूर्ण
पूर्ण

/*
 * Update work
 */

अचिन्हित अक्षर *cfag12864b_buffer;
अटल अचिन्हित अक्षर *cfag12864b_cache;
अटल DEFINE_MUTEX(cfag12864b_mutex);
अटल अचिन्हित अक्षर cfag12864b_updating;
अटल व्योम cfag12864b_update(काष्ठा work_काष्ठा *delayed_work);
अटल काष्ठा workqueue_काष्ठा *cfag12864b_workqueue;
अटल DECLARE_DELAYED_WORK(cfag12864b_work, cfag12864b_update);

अटल व्योम cfag12864b_queue(व्योम)
अणु
	queue_delayed_work(cfag12864b_workqueue, &cfag12864b_work,
		HZ / cfag12864b_rate);
पूर्ण

अचिन्हित अक्षर cfag12864b_enable(व्योम)
अणु
	अचिन्हित अक्षर ret;

	mutex_lock(&cfag12864b_mutex);

	अगर (!cfag12864b_updating) अणु
		cfag12864b_updating = 1;
		cfag12864b_queue();
		ret = 0;
	पूर्ण अन्यथा
		ret = 1;

	mutex_unlock(&cfag12864b_mutex);

	वापस ret;
पूर्ण

व्योम cfag12864b_disable(व्योम)
अणु
	mutex_lock(&cfag12864b_mutex);

	अगर (cfag12864b_updating) अणु
		cfag12864b_updating = 0;
		cancel_delayed_work(&cfag12864b_work);
		flush_workqueue(cfag12864b_workqueue);
	पूर्ण

	mutex_unlock(&cfag12864b_mutex);
पूर्ण

अचिन्हित अक्षर cfag12864b_isenabled(व्योम)
अणु
	वापस cfag12864b_updating;
पूर्ण

अटल व्योम cfag12864b_update(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित अक्षर c;
	अचिन्हित लघु i, j, k, b;

	अगर (स_भेद(cfag12864b_cache, cfag12864b_buffer, CFAG12864B_SIZE)) अणु
		क्रम (i = 0; i < CFAG12864B_CONTROLLERS; i++) अणु
			cfag12864b_controller(i);
			cfag12864b_nop();
			क्रम (j = 0; j < CFAG12864B_PAGES; j++) अणु
				cfag12864b_page(j);
				cfag12864b_nop();
				cfag12864b_address(0);
				cfag12864b_nop();
				क्रम (k = 0; k < CFAG12864B_ADDRESSES; k++) अणु
					क्रम (c = 0, b = 0; b < 8; b++)
						अगर (cfag12864b_buffer
							[i * CFAG12864B_ADDRESSES / 8
							+ k / 8 + (j * 8 + b) *
							CFAG12864B_WIDTH / 8]
							& bit(k % 8))
							c |= bit(b);
					cfag12864b_ग_लिखोbyte(c);
				पूर्ण
			पूर्ण
		पूर्ण

		स_नकल(cfag12864b_cache, cfag12864b_buffer, CFAG12864B_SIZE);
	पूर्ण

	अगर (cfag12864b_updating)
		cfag12864b_queue();
पूर्ण

/*
 * cfag12864b Exported Symbols
 */

EXPORT_SYMBOL_GPL(cfag12864b_buffer);
EXPORT_SYMBOL_GPL(cfag12864b_getrate);
EXPORT_SYMBOL_GPL(cfag12864b_enable);
EXPORT_SYMBOL_GPL(cfag12864b_disable);
EXPORT_SYMBOL_GPL(cfag12864b_isenabled);

/*
 * Is the module inited?
 */

अटल अचिन्हित अक्षर cfag12864b_inited;
अचिन्हित अक्षर cfag12864b_isinited(व्योम)
अणु
	वापस cfag12864b_inited;
पूर्ण
EXPORT_SYMBOL_GPL(cfag12864b_isinited);

/*
 * Module Init & Exit
 */

अटल पूर्णांक __init cfag12864b_init(व्योम)
अणु
	पूर्णांक ret = -EINVAL;

	/* ks0108_init() must be called first */
	अगर (!ks0108_isinited()) अणु
		prपूर्णांकk(KERN_ERR CFAG12864B_NAME ": ERROR: "
			"ks0108 is not initialized\n");
		जाओ none;
	पूर्ण
	BUILD_BUG_ON(PAGE_SIZE < CFAG12864B_SIZE);

	cfag12864b_buffer = (अचिन्हित अक्षर *) get_zeroed_page(GFP_KERNEL);
	अगर (cfag12864b_buffer == शून्य) अणु
		prपूर्णांकk(KERN_ERR CFAG12864B_NAME ": ERROR: "
			"can't get a free page\n");
		ret = -ENOMEM;
		जाओ none;
	पूर्ण

	cfag12864b_cache = kदो_स्मृति(CFAG12864B_SIZE,
				   GFP_KERNEL);
	अगर (cfag12864b_cache == शून्य) अणु
		prपूर्णांकk(KERN_ERR CFAG12864B_NAME ": ERROR: "
			"can't alloc cache buffer (%i bytes)\n",
			CFAG12864B_SIZE);
		ret = -ENOMEM;
		जाओ bufferalloced;
	पूर्ण

	cfag12864b_workqueue = create_singlethपढ़ो_workqueue(CFAG12864B_NAME);
	अगर (cfag12864b_workqueue == शून्य)
		जाओ cachealloced;

	cfag12864b_clear();
	cfag12864b_on();

	cfag12864b_inited = 1;
	वापस 0;

cachealloced:
	kमुक्त(cfag12864b_cache);

bufferalloced:
	मुक्त_page((अचिन्हित दीर्घ) cfag12864b_buffer);

none:
	वापस ret;
पूर्ण

अटल व्योम __निकास cfag12864b_निकास(व्योम)
अणु
	cfag12864b_disable();
	cfag12864b_off();
	destroy_workqueue(cfag12864b_workqueue);
	kमुक्त(cfag12864b_cache);
	मुक्त_page((अचिन्हित दीर्घ) cfag12864b_buffer);
पूर्ण

module_init(cfag12864b_init);
module_निकास(cfag12864b_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Miguel Ojeda <ojeda@kernel.org>");
MODULE_DESCRIPTION("cfag12864b LCD driver");
