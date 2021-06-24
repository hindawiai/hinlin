<शैली गुरु>
/*
 * Setup code क्रम PC-style Real-Time Clock.
 *
 * Author: Wade Farnsworth <wfarnsworth@mvista.com>
 *
 * 2007 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mc146818rtc.h>

#समावेश <यंत्र/prom.h>

अटल पूर्णांक  __init add_rtc(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा platक्रमm_device *pd;
	काष्ठा resource res[2];
	अचिन्हित पूर्णांक num_res = 1;
	पूर्णांक ret;

	स_रखो(&res, 0, माप(res));

	np = of_find_compatible_node(शून्य, शून्य, "pnpPNP,b00");
	अगर (!np)
		वापस -ENODEV;

	ret = of_address_to_resource(np, 0, &res[0]);
	of_node_put(np);
	अगर (ret)
		वापस ret;

	/*
	 * RTC_PORT(x) is hardcoded in यंत्र/mc146818rtc.h.  Verअगरy that the
	 * address provided by the device node matches.
	 */
	अगर (res[0].start != RTC_PORT(0))
		वापस -EINVAL;

	np = of_find_compatible_node(शून्य, शून्य, "chrp,iic");
	अगर (!np)
		np = of_find_compatible_node(शून्य, शून्य, "pnpPNP,000");
	अगर (np) अणु
		of_node_put(np);
		/*
		 * Use a fixed पूर्णांकerrupt value of 8 since on PPC अगर we are
		 * using this its off an i8259 which we ensure has पूर्णांकerrupt
		 * numbers 0..15.
		 */
		res[1].start = 8;
		res[1].end = 8;
		res[1].flags = IORESOURCE_IRQ;
		num_res++;
	पूर्ण

	pd = platक्रमm_device_रेजिस्टर_simple("rtc_cmos", -1,
					     &res[0], num_res);

	वापस PTR_ERR_OR_ZERO(pd);
पूर्ण
fs_initcall(add_rtc);

MODULE_LICENSE("GPL");
