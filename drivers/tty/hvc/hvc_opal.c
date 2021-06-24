<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * opal driver पूर्णांकerface to hvc_console.c
 *
 * Copyright 2011 Benjamin Herrenschmidt <benh@kernel.crashing.org>, IBM Corp.
 */

#अघोषित DEBUG

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/console.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/hvconsole.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/hvsi.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/opal.h>

#समावेश "hvc_console.h"

अटल स्थिर अक्षर hvc_opal_name[] = "hvc_opal";

अटल स्थिर काष्ठा of_device_id hvc_opal_match[] = अणु
	अणु .name = "serial", .compatible = "ibm,opal-console-raw" पूर्ण,
	अणु .name = "serial", .compatible = "ibm,opal-console-hvsi" पूर्ण,
	अणु पूर्ण,
पूर्ण;

प्रकार क्रमागत hv_protocol अणु
	HV_PROTOCOL_RAW,
	HV_PROTOCOL_HVSI
पूर्ण hv_protocol_t;

काष्ठा hvc_opal_priv अणु
	hv_protocol_t		proto;	/* Raw data or HVSI packets */
	काष्ठा hvsi_priv	hvsi;	/* HVSI specअगरic data */
पूर्ण;
अटल काष्ठा hvc_opal_priv *hvc_opal_privs[MAX_NR_HVC_CONSOLES];

/* For early boot console */
अटल काष्ठा hvc_opal_priv hvc_opal_boot_priv;
अटल u32 hvc_opal_boot_termno;

अटल स्थिर काष्ठा hv_ops hvc_opal_raw_ops = अणु
	.get_अक्षरs = opal_get_अक्षरs,
	.put_अक्षरs = opal_put_अक्षरs,
	.flush = opal_flush_अक्षरs,
	.notअगरier_add = notअगरier_add_irq,
	.notअगरier_del = notअगरier_del_irq,
	.notअगरier_hangup = notअगरier_hangup_irq,
पूर्ण;

अटल पूर्णांक hvc_opal_hvsi_get_अक्षरs(uपूर्णांक32_t vtermno, अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा hvc_opal_priv *pv = hvc_opal_privs[vtermno];

	अगर (WARN_ON(!pv))
		वापस -ENODEV;

	वापस hvsilib_get_अक्षरs(&pv->hvsi, buf, count);
पूर्ण

अटल पूर्णांक hvc_opal_hvsi_put_अक्षरs(uपूर्णांक32_t vtermno, स्थिर अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा hvc_opal_priv *pv = hvc_opal_privs[vtermno];

	अगर (WARN_ON(!pv))
		वापस -ENODEV;

	वापस hvsilib_put_अक्षरs(&pv->hvsi, buf, count);
पूर्ण

अटल पूर्णांक hvc_opal_hvsi_खोलो(काष्ठा hvc_काष्ठा *hp, पूर्णांक data)
अणु
	काष्ठा hvc_opal_priv *pv = hvc_opal_privs[hp->vtermno];
	पूर्णांक rc;

	pr_devel("HVSI@%x: do open !\n", hp->vtermno);

	rc = notअगरier_add_irq(hp, data);
	अगर (rc)
		वापस rc;

	वापस hvsilib_खोलो(&pv->hvsi, hp);
पूर्ण

अटल व्योम hvc_opal_hvsi_बंद(काष्ठा hvc_काष्ठा *hp, पूर्णांक data)
अणु
	काष्ठा hvc_opal_priv *pv = hvc_opal_privs[hp->vtermno];

	pr_devel("HVSI@%x: do close !\n", hp->vtermno);

	hvsilib_बंद(&pv->hvsi, hp);

	notअगरier_del_irq(hp, data);
पूर्ण

अटल व्योम hvc_opal_hvsi_hangup(काष्ठा hvc_काष्ठा *hp, पूर्णांक data)
अणु
	काष्ठा hvc_opal_priv *pv = hvc_opal_privs[hp->vtermno];

	pr_devel("HVSI@%x: do hangup !\n", hp->vtermno);

	hvsilib_बंद(&pv->hvsi, hp);

	notअगरier_hangup_irq(hp, data);
पूर्ण

अटल पूर्णांक hvc_opal_hvsi_tiocmget(काष्ठा hvc_काष्ठा *hp)
अणु
	काष्ठा hvc_opal_priv *pv = hvc_opal_privs[hp->vtermno];

	अगर (!pv)
		वापस -EINVAL;
	वापस pv->hvsi.mctrl;
पूर्ण

अटल पूर्णांक hvc_opal_hvsi_tiocmset(काष्ठा hvc_काष्ठा *hp, अचिन्हित पूर्णांक set,
				अचिन्हित पूर्णांक clear)
अणु
	काष्ठा hvc_opal_priv *pv = hvc_opal_privs[hp->vtermno];

	pr_devel("HVSI@%x: Set modem control, set=%x,clr=%x\n",
		 hp->vtermno, set, clear);

	अगर (set & TIOCM_DTR)
		hvsilib_ग_लिखो_mctrl(&pv->hvsi, 1);
	अन्यथा अगर (clear & TIOCM_DTR)
		hvsilib_ग_लिखो_mctrl(&pv->hvsi, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hv_ops hvc_opal_hvsi_ops = अणु
	.get_अक्षरs = hvc_opal_hvsi_get_अक्षरs,
	.put_अक्षरs = hvc_opal_hvsi_put_अक्षरs,
	.flush = opal_flush_अक्षरs,
	.notअगरier_add = hvc_opal_hvsi_खोलो,
	.notअगरier_del = hvc_opal_hvsi_बंद,
	.notअगरier_hangup = hvc_opal_hvsi_hangup,
	.tiocmget = hvc_opal_hvsi_tiocmget,
	.tiocmset = hvc_opal_hvsi_tiocmset,
पूर्ण;

अटल पूर्णांक hvc_opal_probe(काष्ठा platक्रमm_device *dev)
अणु
	स्थिर काष्ठा hv_ops *ops;
	काष्ठा hvc_काष्ठा *hp;
	काष्ठा hvc_opal_priv *pv;
	hv_protocol_t proto;
	अचिन्हित पूर्णांक termno, irq, boot = 0;
	स्थिर __be32 *reg;

	अगर (of_device_is_compatible(dev->dev.of_node, "ibm,opal-console-raw")) अणु
		proto = HV_PROTOCOL_RAW;
		ops = &hvc_opal_raw_ops;
	पूर्ण अन्यथा अगर (of_device_is_compatible(dev->dev.of_node,
					   "ibm,opal-console-hvsi")) अणु
		proto = HV_PROTOCOL_HVSI;
		ops = &hvc_opal_hvsi_ops;
	पूर्ण अन्यथा अणु
		pr_err("hvc_opal: Unknown protocol for %pOF\n",
		       dev->dev.of_node);
		वापस -ENXIO;
	पूर्ण

	reg = of_get_property(dev->dev.of_node, "reg", शून्य);
	termno = reg ? be32_to_cpup(reg) : 0;

	/* Is it our boot one ? */
	अगर (hvc_opal_privs[termno] == &hvc_opal_boot_priv) अणु
		pv = hvc_opal_privs[termno];
		boot = 1;
	पूर्ण अन्यथा अगर (hvc_opal_privs[termno] == शून्य) अणु
		pv = kzalloc(माप(काष्ठा hvc_opal_priv), GFP_KERNEL);
		अगर (!pv)
			वापस -ENOMEM;
		pv->proto = proto;
		hvc_opal_privs[termno] = pv;
		अगर (proto == HV_PROTOCOL_HVSI) अणु
			/*
			 * We want put_अक्षरs to be atomic to aव्योम mangling of
			 * hvsi packets.
			 */
			hvsilib_init(&pv->hvsi,
				     opal_get_अक्षरs, opal_put_अक्षरs_atomic,
				     termno, 0);
		पूर्ण

		/* Instanciate now to establish a mapping index==vtermno */
		hvc_instantiate(termno, termno, ops);
	पूर्ण अन्यथा अणु
		pr_err("hvc_opal: Device %pOF has duplicate terminal number #%d\n",
		       dev->dev.of_node, termno);
		वापस -ENXIO;
	पूर्ण

	pr_info("hvc%d: %s protocol on %pOF%s\n", termno,
		proto == HV_PROTOCOL_RAW ? "raw" : "hvsi",
		dev->dev.of_node,
		boot ? " (boot console)" : "");

	irq = irq_of_parse_and_map(dev->dev.of_node, 0);
	अगर (!irq) अणु
		pr_info("hvc%d: No interrupts property, using OPAL event\n",
				termno);
		irq = opal_event_request(ilog2(OPAL_EVENT_CONSOLE_INPUT));
	पूर्ण

	अगर (!irq) अणु
		pr_err("hvc_opal: Unable to map interrupt for device %pOF\n",
			dev->dev.of_node);
		वापस irq;
	पूर्ण

	hp = hvc_alloc(termno, irq, ops, MAX_VIO_PUT_CHARS);
	अगर (IS_ERR(hp))
		वापस PTR_ERR(hp);

	/* hvc consoles on घातernv may need to share a single irq */
	hp->flags = IRQF_SHARED;
	dev_set_drvdata(&dev->dev, hp);

	वापस 0;
पूर्ण

अटल पूर्णांक hvc_opal_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा hvc_काष्ठा *hp = dev_get_drvdata(&dev->dev);
	पूर्णांक rc, termno;

	termno = hp->vtermno;
	rc = hvc_हटाओ(hp);
	अगर (rc == 0) अणु
		अगर (hvc_opal_privs[termno] != &hvc_opal_boot_priv)
			kमुक्त(hvc_opal_privs[termno]);
		hvc_opal_privs[termno] = शून्य;
	पूर्ण
	वापस rc;
पूर्ण

अटल काष्ठा platक्रमm_driver hvc_opal_driver = अणु
	.probe		= hvc_opal_probe,
	.हटाओ		= hvc_opal_हटाओ,
	.driver		= अणु
		.name	= hvc_opal_name,
		.of_match_table	= hvc_opal_match,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init hvc_opal_init(व्योम)
अणु
	अगर (!firmware_has_feature(FW_FEATURE_OPAL))
		वापस -ENODEV;

	/* Register as a vio device to receive callbacks */
	वापस platक्रमm_driver_रेजिस्टर(&hvc_opal_driver);
पूर्ण
device_initcall(hvc_opal_init);

अटल व्योम udbg_opal_अ_दो(अक्षर c)
अणु
	अचिन्हित पूर्णांक termno = hvc_opal_boot_termno;
	पूर्णांक count = -1;

	अगर (c == '\n')
		udbg_opal_अ_दो('\r');

	करो अणु
		चयन(hvc_opal_boot_priv.proto) अणु
		हाल HV_PROTOCOL_RAW:
			count = opal_put_अक्षरs(termno, &c, 1);
			अवरोध;
		हाल HV_PROTOCOL_HVSI:
			count = hvc_opal_hvsi_put_अक्षरs(termno, &c, 1);
			अवरोध;
		पूर्ण

		/* This is needed क्रम the cosole to flush
		 * when there aren't any पूर्णांकerrupts.
		 */
		opal_flush_console(termno);
	पूर्ण जबतक(count == 0 || count == -EAGAIN);
पूर्ण

अटल पूर्णांक udbg_opal_अ_लो_poll(व्योम)
अणु
	अचिन्हित पूर्णांक termno = hvc_opal_boot_termno;
	पूर्णांक rc = 0;
	अक्षर c;

	चयन(hvc_opal_boot_priv.proto) अणु
	हाल HV_PROTOCOL_RAW:
		rc = opal_get_अक्षरs(termno, &c, 1);
		अवरोध;
	हाल HV_PROTOCOL_HVSI:
		rc = hvc_opal_hvsi_get_अक्षरs(termno, &c, 1);
		अवरोध;
	पूर्ण
	अगर (!rc)
		वापस -1;
	वापस c;
पूर्ण

अटल पूर्णांक udbg_opal_अ_लो(व्योम)
अणु
	पूर्णांक ch;
	क्रम (;;) अणु
		ch = udbg_opal_अ_लो_poll();
		अगर (ch != -1)
			वापस ch;
	पूर्ण
पूर्ण

अटल व्योम udbg_init_opal_common(व्योम)
अणु
	udbg_अ_दो = udbg_opal_अ_दो;
	udbg_अ_लो = udbg_opal_अ_लो;
	udbg_अ_लो_poll = udbg_opal_अ_लो_poll;
पूर्ण

व्योम __init hvc_opal_init_early(व्योम)
अणु
	काष्ठा device_node *मानक_निकास_node = of_node_get(of_मानक_निकास);
	स्थिर __be32 *termno;
	स्थिर काष्ठा hv_ops *ops;
	u32 index;

	/* If the console wasn't in /chosen, try /ibm,opal */
	अगर (!मानक_निकास_node) अणु
		काष्ठा device_node *opal, *np;

		/* Current OPAL takeover करोesn't provide the मानक_निकास
		 * path, so we hard wire it
		 */
		opal = of_find_node_by_path("/ibm,opal/consoles");
		अगर (opal)
			pr_devel("hvc_opal: Found consoles in new location\n");
		अगर (!opal) अणु
			opal = of_find_node_by_path("/ibm,opal");
			अगर (opal)
				pr_devel("hvc_opal: "
					 "Found consoles in old location\n");
		पूर्ण
		अगर (!opal)
			वापस;
		क्रम_each_child_of_node(opal, np) अणु
			अगर (of_node_name_eq(np, "serial")) अणु
				मानक_निकास_node = np;
				अवरोध;
			पूर्ण
		पूर्ण
		of_node_put(opal);
	पूर्ण
	अगर (!मानक_निकास_node)
		वापस;
	termno = of_get_property(मानक_निकास_node, "reg", शून्य);
	index = termno ? be32_to_cpup(termno) : 0;
	अगर (index >= MAX_NR_HVC_CONSOLES)
		वापस;
	hvc_opal_privs[index] = &hvc_opal_boot_priv;

	/* Check the protocol */
	अगर (of_device_is_compatible(मानक_निकास_node, "ibm,opal-console-raw")) अणु
		hvc_opal_boot_priv.proto = HV_PROTOCOL_RAW;
		ops = &hvc_opal_raw_ops;
		pr_devel("hvc_opal: Found RAW console\n");
	पूर्ण
	अन्यथा अगर (of_device_is_compatible(मानक_निकास_node,"ibm,opal-console-hvsi")) अणु
		hvc_opal_boot_priv.proto = HV_PROTOCOL_HVSI;
		ops = &hvc_opal_hvsi_ops;
		hvsilib_init(&hvc_opal_boot_priv.hvsi,
			     opal_get_अक्षरs, opal_put_अक्षरs_atomic,
			     index, 1);
		/* HVSI, perक्रमm the handshake now */
		hvsilib_establish(&hvc_opal_boot_priv.hvsi);
		pr_devel("hvc_opal: Found HVSI console\n");
	पूर्ण अन्यथा
		जाओ out;
	hvc_opal_boot_termno = index;
	udbg_init_opal_common();
	add_preferred_console("hvc", index, शून्य);
	hvc_instantiate(index, index, ops);
out:
	of_node_put(मानक_निकास_node);
पूर्ण

#अगर_घोषित CONFIG_PPC_EARLY_DEBUG_OPAL_RAW
व्योम __init udbg_init_debug_opal_raw(व्योम)
अणु
	u32 index = CONFIG_PPC_EARLY_DEBUG_OPAL_VTERMNO;
	hvc_opal_privs[index] = &hvc_opal_boot_priv;
	hvc_opal_boot_priv.proto = HV_PROTOCOL_RAW;
	hvc_opal_boot_termno = index;
	udbg_init_opal_common();
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_EARLY_DEBUG_OPAL_RAW */

#अगर_घोषित CONFIG_PPC_EARLY_DEBUG_OPAL_HVSI
व्योम __init udbg_init_debug_opal_hvsi(व्योम)
अणु
	u32 index = CONFIG_PPC_EARLY_DEBUG_OPAL_VTERMNO;
	hvc_opal_privs[index] = &hvc_opal_boot_priv;
	hvc_opal_boot_termno = index;
	udbg_init_opal_common();
	hvsilib_init(&hvc_opal_boot_priv.hvsi,
		     opal_get_अक्षरs, opal_put_अक्षरs_atomic,
		     index, 1);
	hvsilib_establish(&hvc_opal_boot_priv.hvsi);
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_EARLY_DEBUG_OPAL_HVSI */
