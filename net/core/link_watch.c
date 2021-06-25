<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux network device link state notअगरication
 *
 * Author:
 *     Stefan Rompf <sux@loplof.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर.h>
#समावेश <net/sock.h>
#समावेश <net/pkt_sched.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/bitops.h>
#समावेश <linux/types.h>


क्रमागत lw_bits अणु
	LW_URGENT = 0,
पूर्ण;

अटल अचिन्हित दीर्घ linkwatch_flags;
अटल अचिन्हित दीर्घ linkwatch_nextevent;

अटल व्योम linkwatch_event(काष्ठा work_काष्ठा *dummy);
अटल DECLARE_DELAYED_WORK(linkwatch_work, linkwatch_event);

अटल LIST_HEAD(lweventlist);
अटल DEFINE_SPINLOCK(lweventlist_lock);

अटल अचिन्हित अक्षर शेष_operstate(स्थिर काष्ठा net_device *dev)
अणु
	अगर (netअगर_testing(dev))
		वापस IF_OPER_TESTING;

	अगर (!netअगर_carrier_ok(dev))
		वापस (dev->अगरindex != dev_get_अगरlink(dev) ?
			IF_OPER_LOWERLAYERDOWN : IF_OPER_DOWN);

	अगर (netअगर_करोrmant(dev))
		वापस IF_OPER_DORMANT;

	वापस IF_OPER_UP;
पूर्ण


अटल व्योम rfc2863_policy(काष्ठा net_device *dev)
अणु
	अचिन्हित अक्षर operstate = शेष_operstate(dev);

	अगर (operstate == dev->operstate)
		वापस;

	ग_लिखो_lock_bh(&dev_base_lock);

	चयन(dev->link_mode) अणु
	हाल IF_LINK_MODE_TESTING:
		अगर (operstate == IF_OPER_UP)
			operstate = IF_OPER_TESTING;
		अवरोध;

	हाल IF_LINK_MODE_DORMANT:
		अगर (operstate == IF_OPER_UP)
			operstate = IF_OPER_DORMANT;
		अवरोध;
	हाल IF_LINK_MODE_DEFAULT:
	शेष:
		अवरोध;
	पूर्ण

	dev->operstate = operstate;

	ग_लिखो_unlock_bh(&dev_base_lock);
पूर्ण


व्योम linkwatch_init_dev(काष्ठा net_device *dev)
अणु
	/* Handle pre-registration link state changes */
	अगर (!netअगर_carrier_ok(dev) || netअगर_करोrmant(dev) ||
	    netअगर_testing(dev))
		rfc2863_policy(dev);
पूर्ण


अटल bool linkwatch_urgent_event(काष्ठा net_device *dev)
अणु
	अगर (!netअगर_running(dev))
		वापस false;

	अगर (dev->अगरindex != dev_get_अगरlink(dev))
		वापस true;

	अगर (netअगर_is_lag_port(dev) || netअगर_is_lag_master(dev))
		वापस true;

	वापस netअगर_carrier_ok(dev) &&	qdisc_tx_changing(dev);
पूर्ण


अटल व्योम linkwatch_add_event(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lweventlist_lock, flags);
	अगर (list_empty(&dev->link_watch_list)) अणु
		list_add_tail(&dev->link_watch_list, &lweventlist);
		dev_hold(dev);
	पूर्ण
	spin_unlock_irqrestore(&lweventlist_lock, flags);
पूर्ण


अटल व्योम linkwatch_schedule_work(पूर्णांक urgent)
अणु
	अचिन्हित दीर्घ delay = linkwatch_nextevent - jअगरfies;

	अगर (test_bit(LW_URGENT, &linkwatch_flags))
		वापस;

	/* Minimise करोwn-समय: drop delay क्रम up event. */
	अगर (urgent) अणु
		अगर (test_and_set_bit(LW_URGENT, &linkwatch_flags))
			वापस;
		delay = 0;
	पूर्ण

	/* If we wrap around we'll delay it by at most HZ. */
	अगर (delay > HZ)
		delay = 0;

	/*
	 * If urgent, schedule immediate execution; otherwise, करोn't
	 * override the existing समयr.
	 */
	अगर (test_bit(LW_URGENT, &linkwatch_flags))
		mod_delayed_work(प्रणाली_wq, &linkwatch_work, 0);
	अन्यथा
		schedule_delayed_work(&linkwatch_work, delay);
पूर्ण


अटल व्योम linkwatch_करो_dev(काष्ठा net_device *dev)
अणु
	/*
	 * Make sure the above पढ़ो is complete since it can be
	 * rewritten as soon as we clear the bit below.
	 */
	smp_mb__beक्रमe_atomic();

	/* We are about to handle this device,
	 * so new events can be accepted
	 */
	clear_bit(__LINK_STATE_LINKWATCH_PENDING, &dev->state);

	rfc2863_policy(dev);
	अगर (dev->flags & IFF_UP && netअगर_device_present(dev)) अणु
		अगर (netअगर_carrier_ok(dev))
			dev_activate(dev);
		अन्यथा
			dev_deactivate(dev);

		netdev_state_change(dev);
	पूर्ण
	dev_put(dev);
पूर्ण

अटल व्योम __linkwatch_run_queue(पूर्णांक urgent_only)
अणु
#घोषणा MAX_DO_DEV_PER_LOOP	100

	पूर्णांक करो_dev = MAX_DO_DEV_PER_LOOP;
	काष्ठा net_device *dev;
	LIST_HEAD(wrk);

	/* Give urgent हाल more budget */
	अगर (urgent_only)
		करो_dev += MAX_DO_DEV_PER_LOOP;

	/*
	 * Limit the number of linkwatch events to one
	 * per second so that a runaway driver करोes not
	 * cause a storm of messages on the netlink
	 * socket.  This limit करोes not apply to up events
	 * जबतक the device qdisc is करोwn.
	 */
	अगर (!urgent_only)
		linkwatch_nextevent = jअगरfies + HZ;
	/* Limit wrap-around effect on delay. */
	अन्यथा अगर (समय_after(linkwatch_nextevent, jअगरfies + HZ))
		linkwatch_nextevent = jअगरfies;

	clear_bit(LW_URGENT, &linkwatch_flags);

	spin_lock_irq(&lweventlist_lock);
	list_splice_init(&lweventlist, &wrk);

	जबतक (!list_empty(&wrk) && करो_dev > 0) अणु

		dev = list_first_entry(&wrk, काष्ठा net_device, link_watch_list);
		list_del_init(&dev->link_watch_list);

		अगर (urgent_only && !linkwatch_urgent_event(dev)) अणु
			list_add_tail(&dev->link_watch_list, &lweventlist);
			जारी;
		पूर्ण
		spin_unlock_irq(&lweventlist_lock);
		linkwatch_करो_dev(dev);
		करो_dev--;
		spin_lock_irq(&lweventlist_lock);
	पूर्ण

	/* Add the reमुख्यing work back to lweventlist */
	list_splice_init(&wrk, &lweventlist);

	अगर (!list_empty(&lweventlist))
		linkwatch_schedule_work(0);
	spin_unlock_irq(&lweventlist_lock);
पूर्ण

व्योम linkwatch_क्रमget_dev(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक clean = 0;

	spin_lock_irqsave(&lweventlist_lock, flags);
	अगर (!list_empty(&dev->link_watch_list)) अणु
		list_del_init(&dev->link_watch_list);
		clean = 1;
	पूर्ण
	spin_unlock_irqrestore(&lweventlist_lock, flags);
	अगर (clean)
		linkwatch_करो_dev(dev);
पूर्ण


/* Must be called with the rtnl semaphore held */
व्योम linkwatch_run_queue(व्योम)
अणु
	__linkwatch_run_queue(0);
पूर्ण


अटल व्योम linkwatch_event(काष्ठा work_काष्ठा *dummy)
अणु
	rtnl_lock();
	__linkwatch_run_queue(समय_after(linkwatch_nextevent, jअगरfies));
	rtnl_unlock();
पूर्ण


व्योम linkwatch_fire_event(काष्ठा net_device *dev)
अणु
	bool urgent = linkwatch_urgent_event(dev);

	अगर (!test_and_set_bit(__LINK_STATE_LINKWATCH_PENDING, &dev->state)) अणु
		linkwatch_add_event(dev);
	पूर्ण अन्यथा अगर (!urgent)
		वापस;

	linkwatch_schedule_work(urgent);
पूर्ण
EXPORT_SYMBOL(linkwatch_fire_event);
