<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ipmi_si_hoपंचांगod.c
 *
 * Handling क्रम dynamically adding/removing IPMI devices through
 * a module parameter (and thus sysfs).
 */

#घोषणा pr_fmt(fmt) "ipmi_hotmod: " fmt

#समावेश <linux/moduleparam.h>
#समावेश <linux/ipmi.h>
#समावेश <linux/atomic.h>
#समावेश "ipmi_si.h"
#समावेश "ipmi_plat_data.h"

अटल पूर्णांक hoपंचांगod_handler(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);

module_param_call(hoपंचांगod, hoपंचांगod_handler, शून्य, शून्य, 0200);
MODULE_PARM_DESC(hoपंचांगod,
		 "Add and remove interfaces.  See Documentation/driver-api/ipmi.rst in the kernel sources for the gory details.");

/*
 * Parms come in as <op1>[:op2[:op3...]].  ops are:
 *   add|हटाओ,kcs|bt|smic,mem|i/o,<address>[,<opt1>[,<opt2>[,...]]]
 * Options are:
 *   rsp=<regspacing>
 *   rsi=<regsize>
 *   rsh=<regshअगरt>
 *   irq=<irq>
 *   ipmb=<ipmb addr>
 */
क्रमागत hoपंचांगod_op अणु HM_ADD, HM_REMOVE पूर्ण;
काष्ठा hoपंचांगod_vals अणु
	स्थिर अक्षर *name;
	स्थिर पूर्णांक  val;
पूर्ण;

अटल स्थिर काष्ठा hoपंचांगod_vals hoपंचांगod_ops[] = अणु
	अणु "add",	HM_ADD पूर्ण,
	अणु "remove",	HM_REMOVE पूर्ण,
	अणु शून्य पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hoपंचांगod_vals hoपंचांगod_si[] = अणु
	अणु "kcs",	SI_KCS पूर्ण,
	अणु "smic",	SI_SMIC पूर्ण,
	अणु "bt",		SI_BT पूर्ण,
	अणु शून्य पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hoपंचांगod_vals hoपंचांगod_as[] = अणु
	अणु "mem",	IPMI_MEM_ADDR_SPACE पूर्ण,
	अणु "i/o",	IPMI_IO_ADDR_SPACE पूर्ण,
	अणु शून्य पूर्ण
पूर्ण;

अटल पूर्णांक parse_str(स्थिर काष्ठा hoपंचांगod_vals *v, अचिन्हित पूर्णांक *val, अक्षर *name,
		     स्थिर अक्षर **curr)
अणु
	अक्षर *s;
	पूर्णांक  i;

	s = म_अक्षर(*curr, ',');
	अगर (!s) अणु
		pr_warn("No hotmod %s given\n", name);
		वापस -EINVAL;
	पूर्ण
	*s = '\0';
	s++;
	क्रम (i = 0; v[i].name; i++) अणु
		अगर (म_भेद(*curr, v[i].name) == 0) अणु
			*val = v[i].val;
			*curr = s;
			वापस 0;
		पूर्ण
	पूर्ण

	pr_warn("Invalid hotmod %s '%s'\n", name, *curr);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक check_hoपंचांगod_पूर्णांक_op(स्थिर अक्षर *curr, स्थिर अक्षर *option,
			       स्थिर अक्षर *name, अचिन्हित पूर्णांक *val)
अणु
	अक्षर *n;

	अगर (म_भेद(curr, name) == 0) अणु
		अगर (!option) अणु
			pr_warn("No option given for '%s'\n", curr);
			वापस -EINVAL;
		पूर्ण
		*val = simple_म_से_अदीर्घ(option, &n, 0);
		अगर ((*n != '\0') || (*option == '\0')) अणु
			pr_warn("Bad option given for '%s'\n", curr);
			वापस -EINVAL;
		पूर्ण
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक parse_hoपंचांगod_str(स्थिर अक्षर *curr, क्रमागत hoपंचांगod_op *op,
			    काष्ठा ipmi_plat_data *h)
अणु
	अक्षर *s, *o;
	पूर्णांक rv;
	अचिन्हित पूर्णांक ival;

	h->अगरtype = IPMI_PLAT_IF_SI;
	rv = parse_str(hoपंचांगod_ops, &ival, "operation", &curr);
	अगर (rv)
		वापस rv;
	*op = ival;

	rv = parse_str(hoपंचांगod_si, &ival, "interface type", &curr);
	अगर (rv)
		वापस rv;
	h->type = ival;

	rv = parse_str(hoपंचांगod_as, &ival, "address space", &curr);
	अगर (rv)
		वापस rv;
	h->space = ival;

	s = म_अक्षर(curr, ',');
	अगर (s) अणु
		*s = '\0';
		s++;
	पूर्ण
	rv = kम_से_अदीर्घ(curr, 0, &h->addr);
	अगर (rv) अणु
		pr_warn("Invalid hotmod address '%s': %d\n", curr, rv);
		वापस rv;
	पूर्ण

	जबतक (s) अणु
		curr = s;
		s = म_अक्षर(curr, ',');
		अगर (s) अणु
			*s = '\0';
			s++;
		पूर्ण
		o = म_अक्षर(curr, '=');
		अगर (o) अणु
			*o = '\0';
			o++;
		पूर्ण
		rv = check_hoपंचांगod_पूर्णांक_op(curr, o, "rsp", &h->regspacing);
		अगर (rv < 0)
			वापस rv;
		अन्यथा अगर (rv)
			जारी;
		rv = check_hoपंचांगod_पूर्णांक_op(curr, o, "rsi", &h->regsize);
		अगर (rv < 0)
			वापस rv;
		अन्यथा अगर (rv)
			जारी;
		rv = check_hoपंचांगod_पूर्णांक_op(curr, o, "rsh", &h->regshअगरt);
		अगर (rv < 0)
			वापस rv;
		अन्यथा अगर (rv)
			जारी;
		rv = check_hoपंचांगod_पूर्णांक_op(curr, o, "irq", &h->irq);
		अगर (rv < 0)
			वापस rv;
		अन्यथा अगर (rv)
			जारी;
		rv = check_hoपंचांगod_पूर्णांक_op(curr, o, "ipmb", &h->slave_addr);
		अगर (rv < 0)
			वापस rv;
		अन्यथा अगर (rv)
			जारी;

		pr_warn("Invalid hotmod option '%s'\n", curr);
		वापस -EINVAL;
	पूर्ण

	h->addr_source = SI_HOTMOD;
	वापस 0;
पूर्ण

अटल atomic_t hoपंचांगod_nr;

अटल पूर्णांक hoपंचांगod_handler(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक  rv;
	काष्ठा ipmi_plat_data h;
	अक्षर *str, *curr, *next;

	str = kstrdup(val, GFP_KERNEL);
	अगर (!str)
		वापस -ENOMEM;

	/* Kill any trailing spaces, as we can get a "\n" from echo. */
	क्रम (curr = म_मालाip(str); curr; curr = next) अणु
		क्रमागत hoपंचांगod_op op;

		next = म_अक्षर(curr, ':');
		अगर (next) अणु
			*next = '\0';
			next++;
		पूर्ण

		स_रखो(&h, 0, माप(h));
		rv = parse_hoपंचांगod_str(curr, &op, &h);
		अगर (rv)
			जाओ out;

		अगर (op == HM_ADD) अणु
			ipmi_platक्रमm_add("hotmod-ipmi-si",
					  atomic_inc_वापस(&hoपंचांगod_nr),
					  &h);
		पूर्ण अन्यथा अणु
			काष्ठा device *dev;

			dev = ipmi_si_हटाओ_by_data(h.space, h.type, h.addr);
			अगर (dev && dev_is_platक्रमm(dev)) अणु
				काष्ठा platक्रमm_device *pdev;

				pdev = to_platक्रमm_device(dev);
				अगर (म_भेद(pdev->name, "hotmod-ipmi-si") == 0)
					platक्रमm_device_unरेजिस्टर(pdev);
			पूर्ण
			put_device(dev);
		पूर्ण
	पूर्ण
	rv = म_माप(val);
out:
	kमुक्त(str);
	वापस rv;
पूर्ण

व्योम ipmi_si_hoपंचांगod_निकास(व्योम)
अणु
	ipmi_हटाओ_platक्रमm_device_by_name("hotmod-ipmi-si");
पूर्ण
