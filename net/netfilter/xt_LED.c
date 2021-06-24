<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * xt_LED.c - netfilter target to make LEDs blink upon packet matches
 *
 * Copyright (C) 2008 Adam Niअन्यथाn <a.niअन्यथाn@shikadi.net>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>
#समावेश <linux/mutex.h>

#समावेश <linux/netfilter/xt_LED.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Adam Nielsen <a.nielsen@shikadi.net>");
MODULE_DESCRIPTION("Xtables: trigger LED devices on packet match");
MODULE_ALIAS("ipt_LED");
MODULE_ALIAS("ip6t_LED");

अटल LIST_HEAD(xt_led_triggers);
अटल DEFINE_MUTEX(xt_led_mutex);

/*
 * This is declared in here (the kernel module) only, to aव्योम having these
 * dependencies in userspace code.  This is what xt_led_info.पूर्णांकernal_data
 * poपूर्णांकs to.
 */
काष्ठा xt_led_info_पूर्णांकernal अणु
	काष्ठा list_head list;
	पूर्णांक refcnt;
	अक्षर *trigger_id;
	काष्ठा led_trigger netfilter_led_trigger;
	काष्ठा समयr_list समयr;
पूर्ण;

#घोषणा XT_LED_BLINK_DELAY 50 /* ms */

अटल अचिन्हित पूर्णांक
led_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_led_info *ledinfo = par->targinfo;
	काष्ठा xt_led_info_पूर्णांकernal *ledपूर्णांकernal = ledinfo->पूर्णांकernal_data;
	अचिन्हित दीर्घ led_delay = XT_LED_BLINK_DELAY;

	/*
	 * If "always blink" is enabled, and there's still some समय until the
	 * LED will चयन off, briefly चयन it off now.
	 */
	अगर ((ledinfo->delay > 0) && ledinfo->always_blink &&
	    समयr_pending(&ledपूर्णांकernal->समयr))
		led_trigger_blink_oneshot(&ledपूर्णांकernal->netfilter_led_trigger,
					  &led_delay, &led_delay, 1);
	अन्यथा
		led_trigger_event(&ledपूर्णांकernal->netfilter_led_trigger, LED_FULL);

	/* If there's a positive delay, start/update the समयr */
	अगर (ledinfo->delay > 0) अणु
		mod_समयr(&ledपूर्णांकernal->समयr,
			  jअगरfies + msecs_to_jअगरfies(ledinfo->delay));

	/* Otherwise अगर there was no delay given, blink as fast as possible */
	पूर्ण अन्यथा अगर (ledinfo->delay == 0) अणु
		led_trigger_event(&ledपूर्णांकernal->netfilter_led_trigger, LED_OFF);
	पूर्ण

	/* अन्यथा the delay is negative, which means चयन on and stay on */

	वापस XT_CONTINUE;
पूर्ण

अटल व्योम led_समयout_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा xt_led_info_पूर्णांकernal *ledपूर्णांकernal = from_समयr(ledपूर्णांकernal, t,
							      समयr);

	led_trigger_event(&ledपूर्णांकernal->netfilter_led_trigger, LED_OFF);
पूर्ण

अटल काष्ठा xt_led_info_पूर्णांकernal *led_trigger_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा xt_led_info_पूर्णांकernal *ledपूर्णांकernal;

	list_क्रम_each_entry(ledपूर्णांकernal, &xt_led_triggers, list) अणु
		अगर (!म_भेद(name, ledपूर्णांकernal->netfilter_led_trigger.name)) अणु
			वापस ledपूर्णांकernal;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक led_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा xt_led_info *ledinfo = par->targinfo;
	काष्ठा xt_led_info_पूर्णांकernal *ledपूर्णांकernal;
	पूर्णांक err;

	अगर (ledinfo->id[0] == '\0')
		वापस -EINVAL;

	mutex_lock(&xt_led_mutex);

	ledपूर्णांकernal = led_trigger_lookup(ledinfo->id);
	अगर (ledपूर्णांकernal) अणु
		ledपूर्णांकernal->refcnt++;
		जाओ out;
	पूर्ण

	err = -ENOMEM;
	ledपूर्णांकernal = kzalloc(माप(काष्ठा xt_led_info_पूर्णांकernal), GFP_KERNEL);
	अगर (!ledपूर्णांकernal)
		जाओ निकास_mutex_only;

	ledपूर्णांकernal->trigger_id = kstrdup(ledinfo->id, GFP_KERNEL);
	अगर (!ledपूर्णांकernal->trigger_id)
		जाओ निकास_पूर्णांकernal_alloc;

	ledपूर्णांकernal->refcnt = 1;
	ledपूर्णांकernal->netfilter_led_trigger.name = ledपूर्णांकernal->trigger_id;

	err = led_trigger_रेजिस्टर(&ledपूर्णांकernal->netfilter_led_trigger);
	अगर (err) अणु
		pr_info_ratelimited("Trigger name is already in use.\n");
		जाओ निकास_alloc;
	पूर्ण

	/* Since the letपूर्णांकernal समयr can be shared between multiple tarमाला_लो,
	 * always set it up, even अगर the current target करोes not need it
	 */
	समयr_setup(&ledपूर्णांकernal->समयr, led_समयout_callback, 0);

	list_add_tail(&ledपूर्णांकernal->list, &xt_led_triggers);

out:
	mutex_unlock(&xt_led_mutex);

	ledinfo->पूर्णांकernal_data = ledपूर्णांकernal;

	वापस 0;

निकास_alloc:
	kमुक्त(ledपूर्णांकernal->trigger_id);

निकास_पूर्णांकernal_alloc:
	kमुक्त(ledपूर्णांकernal);

निकास_mutex_only:
	mutex_unlock(&xt_led_mutex);

	वापस err;
पूर्ण

अटल व्योम led_tg_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	स्थिर काष्ठा xt_led_info *ledinfo = par->targinfo;
	काष्ठा xt_led_info_पूर्णांकernal *ledपूर्णांकernal = ledinfo->पूर्णांकernal_data;

	mutex_lock(&xt_led_mutex);

	अगर (--ledपूर्णांकernal->refcnt) अणु
		mutex_unlock(&xt_led_mutex);
		वापस;
	पूर्ण

	list_del(&ledपूर्णांकernal->list);

	del_समयr_sync(&ledपूर्णांकernal->समयr);

	led_trigger_unरेजिस्टर(&ledपूर्णांकernal->netfilter_led_trigger);

	mutex_unlock(&xt_led_mutex);

	kमुक्त(ledपूर्णांकernal->trigger_id);
	kमुक्त(ledपूर्णांकernal);
पूर्ण

अटल काष्ठा xt_target led_tg_reg __पढ़ो_mostly = अणु
	.name		= "LED",
	.revision	= 0,
	.family		= NFPROTO_UNSPEC,
	.target		= led_tg,
	.tarमाला_लोize	= माप(काष्ठा xt_led_info),
	.usersize	= दुरत्व(काष्ठा xt_led_info, पूर्णांकernal_data),
	.checkentry	= led_tg_check,
	.destroy	= led_tg_destroy,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init led_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&led_tg_reg);
पूर्ण

अटल व्योम __निकास led_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_target(&led_tg_reg);
पूर्ण

module_init(led_tg_init);
module_निकास(led_tg_निकास);
