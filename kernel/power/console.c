<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions क्रम saving/restoring console.
 *
 * Originally from swsusp.
 */

#समावेश <linux/console.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/kbd_kern.h>
#समावेश <linux/vt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश "power.h"

#घोषणा SUSPEND_CONSOLE	(MAX_NR_CONSOLES-1)

अटल पूर्णांक orig_fgconsole, orig_kmsg;

अटल DEFINE_MUTEX(vt_चयन_mutex);

काष्ठा pm_vt_चयन अणु
	काष्ठा list_head head;
	काष्ठा device *dev;
	bool required;
पूर्ण;

अटल LIST_HEAD(pm_vt_चयन_list);


/**
 * pm_vt_चयन_required - indicate VT चयन at suspend requirements
 * @dev: device
 * @required: अगर true, caller needs VT चयन at suspend/resume समय
 *
 * The dअगरferent console drivers may or may not require VT चयनes across
 * suspend/resume, depending on how they handle restoring video state and
 * what may be running.
 *
 * Drivers can indicate support क्रम चयनless suspend/resume, which can
 * save समय and flicker, by using this routine and passing 'false' as
 * the argument.  If any loaded driver needs VT चयनing, or the
 * no_console_suspend argument has been passed on the command line, VT
 * चयनes will occur.
 */
व्योम pm_vt_चयन_required(काष्ठा device *dev, bool required)
अणु
	काष्ठा pm_vt_चयन *entry, *पंचांगp;

	mutex_lock(&vt_चयन_mutex);
	list_क्रम_each_entry(पंचांगp, &pm_vt_चयन_list, head) अणु
		अगर (पंचांगp->dev == dev) अणु
			/* alपढ़ोy रेजिस्टरed, update requirement */
			पंचांगp->required = required;
			जाओ out;
		पूर्ण
	पूर्ण

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		जाओ out;

	entry->required = required;
	entry->dev = dev;

	list_add(&entry->head, &pm_vt_चयन_list);
out:
	mutex_unlock(&vt_चयन_mutex);
पूर्ण
EXPORT_SYMBOL(pm_vt_चयन_required);

/**
 * pm_vt_चयन_unरेजिस्टर - stop tracking a device's VT चयनing needs
 * @dev: device
 *
 * Remove @dev from the vt चयन list.
 */
व्योम pm_vt_चयन_unरेजिस्टर(काष्ठा device *dev)
अणु
	काष्ठा pm_vt_चयन *पंचांगp;

	mutex_lock(&vt_चयन_mutex);
	list_क्रम_each_entry(पंचांगp, &pm_vt_चयन_list, head) अणु
		अगर (पंचांगp->dev == dev) अणु
			list_del(&पंचांगp->head);
			kमुक्त(पंचांगp);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&vt_चयन_mutex);
पूर्ण
EXPORT_SYMBOL(pm_vt_चयन_unरेजिस्टर);

/*
 * There are three हालs when a VT चयन on suspend/resume are required:
 *   1) no driver has indicated a requirement one way or another, so preserve
 *      the old behavior
 *   2) console suspend is disabled, we want to see debug messages across
 *      suspend/resume
 *   3) any रेजिस्टरed driver indicates it needs a VT चयन
 *
 * If none of these conditions is present, meaning we have at least one driver
 * that करोesn't need the चयन, and none that करो, we can aव्योम it to make
 * resume look a little prettier (and suspend too, but that's usually hidden,
 * e.g. when closing the lid on a laptop).
 */
अटल bool pm_vt_चयन(व्योम)
अणु
	काष्ठा pm_vt_चयन *entry;
	bool ret = true;

	mutex_lock(&vt_चयन_mutex);
	अगर (list_empty(&pm_vt_चयन_list))
		जाओ out;

	अगर (!console_suspend_enabled)
		जाओ out;

	list_क्रम_each_entry(entry, &pm_vt_चयन_list, head) अणु
		अगर (entry->required)
			जाओ out;
	पूर्ण

	ret = false;
out:
	mutex_unlock(&vt_चयन_mutex);
	वापस ret;
पूर्ण

व्योम pm_prepare_console(व्योम)
अणु
	अगर (!pm_vt_चयन())
		वापस;

	orig_fgconsole = vt_move_to_console(SUSPEND_CONSOLE, 1);
	अगर (orig_fgconsole < 0)
		वापस;

	orig_kmsg = vt_kmsg_redirect(SUSPEND_CONSOLE);
	वापस;
पूर्ण

व्योम pm_restore_console(व्योम)
अणु
	अगर (!pm_vt_चयन())
		वापस;

	अगर (orig_fgconsole >= 0) अणु
		vt_move_to_console(orig_fgconsole, 0);
		vt_kmsg_redirect(orig_kmsg);
	पूर्ण
पूर्ण
