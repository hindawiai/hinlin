<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vio driver पूर्णांकerface to hvc_console.c
 *
 * This code was moved here to allow the reमुख्यing code to be reused as a
 * generic polling mode with semi-reliable transport driver core to the
 * console and tty subप्रणालीs.
 *
 *
 * Copyright (C) 2001 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 * Copyright (C) 2001 Paul Mackerras <paulus@au.ibm.com>, IBM
 * Copyright (C) 2004 Benjamin Herrenschmidt <benh@kernel.crashing.org>, IBM Corp.
 * Copyright (C) 2004 IBM Corporation
 *
 * Additional Author(s):
 *  Ryan S. Arnold <rsa@us.ibm.com>
 *
 * TODO:
 *
 *   - handle error in sending hvsi protocol packets
 *   - retry nego on subsequent sends ?
 */

#अघोषित DEBUG

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/console.h>

#समावेश <यंत्र/hvconsole.h>
#समावेश <यंत्र/vपन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/hvsi.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/machdep.h>

#समावेश "hvc_console.h"

अटल स्थिर अक्षर hvc_driver_name[] = "hvc_console";

अटल स्थिर काष्ठा vio_device_id hvc_driver_table[] = अणु
	अणु"serial", "hvterm1"पूर्ण,
#अगर_अघोषित HVC_OLD_HVSI
	अणु"serial", "hvterm-protocol"पूर्ण,
#पूर्ण_अगर
	अणु "", "" पूर्ण
पूर्ण;

प्रकार क्रमागत hv_protocol अणु
	HV_PROTOCOL_RAW,
	HV_PROTOCOL_HVSI
पूर्ण hv_protocol_t;

काष्ठा hvterm_priv अणु
	u32			termno;	/* HV term number */
	hv_protocol_t		proto;	/* Raw data or HVSI packets */
	काष्ठा hvsi_priv	hvsi;	/* HVSI specअगरic data */
	spinlock_t		buf_lock;
	अक्षर			buf[SIZE_VIO_GET_CHARS];
	पूर्णांक			left;
	पूर्णांक			offset;
पूर्ण;
अटल काष्ठा hvterm_priv *hvterm_privs[MAX_NR_HVC_CONSOLES];
/* For early boot console */
अटल काष्ठा hvterm_priv hvterm_priv0;

अटल पूर्णांक hvterm_raw_get_अक्षरs(uपूर्णांक32_t vtermno, अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा hvterm_priv *pv = hvterm_privs[vtermno];
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ flags;
	पूर्णांक got;

	अगर (WARN_ON(!pv))
		वापस 0;

	spin_lock_irqsave(&pv->buf_lock, flags);

	अगर (pv->left == 0) अणु
		pv->offset = 0;
		pv->left = hvc_get_अक्षरs(pv->termno, pv->buf, count);

		/*
		 * Work around a HV bug where it gives us a null
		 * after every \ल.  -- paulus
		 */
		क्रम (i = 1; i < pv->left; ++i) अणु
			अगर (pv->buf[i] == 0 && pv->buf[i-1] == '\r') अणु
				--pv->left;
				अगर (i < pv->left) अणु
					स_हटाओ(&pv->buf[i], &pv->buf[i+1],
						pv->left - i);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	got = min(count, pv->left);
	स_नकल(buf, &pv->buf[pv->offset], got);
	pv->offset += got;
	pv->left -= got;

	spin_unlock_irqrestore(&pv->buf_lock, flags);

	वापस got;
पूर्ण

/**
 * hvterm_raw_put_अक्षरs: send अक्षरacters to firmware क्रम given vterm adapter
 * @vtermno: The भव terminal number.
 * @buf: The अक्षरacters to send. Because of the underlying hypercall in
 *       hvc_put_अक्षरs(), this buffer must be at least 16 bytes दीर्घ, even अगर
 *       you are sending fewer अक्षरs.
 * @count: number of अक्षरs to send.
 */
अटल पूर्णांक hvterm_raw_put_अक्षरs(uपूर्णांक32_t vtermno, स्थिर अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा hvterm_priv *pv = hvterm_privs[vtermno];

	अगर (WARN_ON(!pv))
		वापस 0;

	वापस hvc_put_अक्षरs(pv->termno, buf, count);
पूर्ण

अटल स्थिर काष्ठा hv_ops hvterm_raw_ops = अणु
	.get_अक्षरs = hvterm_raw_get_अक्षरs,
	.put_अक्षरs = hvterm_raw_put_अक्षरs,
	.notअगरier_add = notअगरier_add_irq,
	.notअगरier_del = notअगरier_del_irq,
	.notअगरier_hangup = notअगरier_hangup_irq,
पूर्ण;

अटल पूर्णांक hvterm_hvsi_get_अक्षरs(uपूर्णांक32_t vtermno, अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा hvterm_priv *pv = hvterm_privs[vtermno];

	अगर (WARN_ON(!pv))
		वापस 0;

	वापस hvsilib_get_अक्षरs(&pv->hvsi, buf, count);
पूर्ण

अटल पूर्णांक hvterm_hvsi_put_अक्षरs(uपूर्णांक32_t vtermno, स्थिर अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा hvterm_priv *pv = hvterm_privs[vtermno];

	अगर (WARN_ON(!pv))
		वापस 0;

	वापस hvsilib_put_अक्षरs(&pv->hvsi, buf, count);
पूर्ण

अटल पूर्णांक hvterm_hvsi_खोलो(काष्ठा hvc_काष्ठा *hp, पूर्णांक data)
अणु
	काष्ठा hvterm_priv *pv = hvterm_privs[hp->vtermno];
	पूर्णांक rc;

	pr_devel("HVSI@%x: open !\n", pv->termno);

	rc = notअगरier_add_irq(hp, data);
	अगर (rc)
		वापस rc;

	वापस hvsilib_खोलो(&pv->hvsi, hp);
पूर्ण

अटल व्योम hvterm_hvsi_बंद(काष्ठा hvc_काष्ठा *hp, पूर्णांक data)
अणु
	काष्ठा hvterm_priv *pv = hvterm_privs[hp->vtermno];

	pr_devel("HVSI@%x: do close !\n", pv->termno);

	hvsilib_बंद(&pv->hvsi, hp);

	notअगरier_del_irq(hp, data);
पूर्ण

अटल व्योम hvterm_hvsi_hangup(काष्ठा hvc_काष्ठा *hp, पूर्णांक data)
अणु
	काष्ठा hvterm_priv *pv = hvterm_privs[hp->vtermno];

	pr_devel("HVSI@%x: do hangup !\n", pv->termno);

	hvsilib_बंद(&pv->hvsi, hp);

	notअगरier_hangup_irq(hp, data);
पूर्ण

अटल पूर्णांक hvterm_hvsi_tiocmget(काष्ठा hvc_काष्ठा *hp)
अणु
	काष्ठा hvterm_priv *pv = hvterm_privs[hp->vtermno];

	अगर (!pv)
		वापस -EINVAL;
	वापस pv->hvsi.mctrl;
पूर्ण

अटल पूर्णांक hvterm_hvsi_tiocmset(काष्ठा hvc_काष्ठा *hp, अचिन्हित पूर्णांक set,
				अचिन्हित पूर्णांक clear)
अणु
	काष्ठा hvterm_priv *pv = hvterm_privs[hp->vtermno];

	pr_devel("HVSI@%x: Set modem control, set=%x,clr=%x\n",
		 pv->termno, set, clear);

	अगर (set & TIOCM_DTR)
		hvsilib_ग_लिखो_mctrl(&pv->hvsi, 1);
	अन्यथा अगर (clear & TIOCM_DTR)
		hvsilib_ग_लिखो_mctrl(&pv->hvsi, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hv_ops hvterm_hvsi_ops = अणु
	.get_अक्षरs = hvterm_hvsi_get_अक्षरs,
	.put_अक्षरs = hvterm_hvsi_put_अक्षरs,
	.notअगरier_add = hvterm_hvsi_खोलो,
	.notअगरier_del = hvterm_hvsi_बंद,
	.notअगरier_hangup = hvterm_hvsi_hangup,
	.tiocmget = hvterm_hvsi_tiocmget,
	.tiocmset = hvterm_hvsi_tiocmset,
पूर्ण;

अटल व्योम udbg_hvc_अ_दो(अक्षर c)
अणु
	पूर्णांक count = -1;
	अचिन्हित अक्षर bounce_buffer[16];

	अगर (!hvterm_privs[0])
		वापस;

	अगर (c == '\n')
		udbg_hvc_अ_दो('\r');

	करो अणु
		चयन(hvterm_privs[0]->proto) अणु
		हाल HV_PROTOCOL_RAW:
			/*
			 * hvterm_raw_put_अक्षरs requires at least a 16-byte
			 * buffer, so go via the bounce buffer
			 */
			bounce_buffer[0] = c;
			count = hvterm_raw_put_अक्षरs(0, bounce_buffer, 1);
			अवरोध;
		हाल HV_PROTOCOL_HVSI:
			count = hvterm_hvsi_put_अक्षरs(0, &c, 1);
			अवरोध;
		पूर्ण
	पूर्ण जबतक(count == 0);
पूर्ण

अटल पूर्णांक udbg_hvc_अ_लो_poll(व्योम)
अणु
	पूर्णांक rc = 0;
	अक्षर c;

	अगर (!hvterm_privs[0])
		वापस -1;

	चयन(hvterm_privs[0]->proto) अणु
	हाल HV_PROTOCOL_RAW:
		rc = hvterm_raw_get_अक्षरs(0, &c, 1);
		अवरोध;
	हाल HV_PROTOCOL_HVSI:
		rc = hvterm_hvsi_get_अक्षरs(0, &c, 1);
		अवरोध;
	पूर्ण
	अगर (!rc)
		वापस -1;
	वापस c;
पूर्ण

अटल पूर्णांक udbg_hvc_अ_लो(व्योम)
अणु
	पूर्णांक ch;

	अगर (!hvterm_privs[0])
		वापस -1;

	क्रम (;;) अणु
		ch = udbg_hvc_अ_लो_poll();
		अगर (ch == -1) अणु
			/* This shouldn't be needed...but... */
			अस्थिर अचिन्हित दीर्घ delay;
			क्रम (delay=0; delay < 2000000; delay++)
				;
		पूर्ण अन्यथा अणु
			वापस ch;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hvc_vio_probe(काष्ठा vio_dev *vdev,
				   स्थिर काष्ठा vio_device_id *id)
अणु
	स्थिर काष्ठा hv_ops *ops;
	काष्ठा hvc_काष्ठा *hp;
	काष्ठा hvterm_priv *pv;
	hv_protocol_t proto;
	पूर्णांक i, termno = -1;

	/* probed with invalid parameters. */
	अगर (!vdev || !id)
		वापस -EPERM;

	अगर (of_device_is_compatible(vdev->dev.of_node, "hvterm1")) अणु
		proto = HV_PROTOCOL_RAW;
		ops = &hvterm_raw_ops;
	पूर्ण अन्यथा अगर (of_device_is_compatible(vdev->dev.of_node, "hvterm-protocol")) अणु
		proto = HV_PROTOCOL_HVSI;
		ops = &hvterm_hvsi_ops;
	पूर्ण अन्यथा अणु
		pr_err("hvc_vio: Unknown protocol for %pOF\n", vdev->dev.of_node);
		वापस -ENXIO;
	पूर्ण

	pr_devel("hvc_vio_probe() device %pOF, using %s protocol\n",
		 vdev->dev.of_node,
		 proto == HV_PROTOCOL_RAW ? "raw" : "hvsi");

	/* Is it our boot one ? */
	अगर (hvterm_privs[0] == &hvterm_priv0 &&
	    vdev->unit_address == hvterm_priv0.termno) अणु
		pv = hvterm_privs[0];
		termno = 0;
		pr_devel("->boot console, using termno 0\n");
	पूर्ण
	/* nope, allocate a new one */
	अन्यथा अणु
		क्रम (i = 0; i < MAX_NR_HVC_CONSOLES && termno < 0; i++)
			अगर (!hvterm_privs[i])
				termno = i;
		pr_devel("->non-boot console, using termno %d\n", termno);
		अगर (termno < 0)
			वापस -ENODEV;
		pv = kzalloc(माप(काष्ठा hvterm_priv), GFP_KERNEL);
		अगर (!pv)
			वापस -ENOMEM;
		pv->termno = vdev->unit_address;
		pv->proto = proto;
		spin_lock_init(&pv->buf_lock);
		hvterm_privs[termno] = pv;
		hvsilib_init(&pv->hvsi, hvc_get_अक्षरs, hvc_put_अक्षरs,
			     pv->termno, 0);
	पूर्ण

	hp = hvc_alloc(termno, vdev->irq, ops, MAX_VIO_PUT_CHARS);
	अगर (IS_ERR(hp))
		वापस PTR_ERR(hp);
	dev_set_drvdata(&vdev->dev, hp);

	/* रेजिस्टर udbg अगर it's not there alपढ़ोy क्रम console 0 */
	अगर (hp->index == 0 && !udbg_अ_दो) अणु
		udbg_अ_दो = udbg_hvc_अ_दो;
		udbg_अ_लो = udbg_hvc_अ_लो;
		udbg_अ_लो_poll = udbg_hvc_अ_लो_poll;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा vio_driver hvc_vio_driver = अणु
	.id_table	= hvc_driver_table,
	.probe		= hvc_vio_probe,
	.name		= hvc_driver_name,
	.driver = अणु
		.suppress_bind_attrs	= true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init hvc_vio_init(व्योम)
अणु
	पूर्णांक rc;

	/* Register as a vio device to receive callbacks */
	rc = vio_रेजिस्टर_driver(&hvc_vio_driver);

	वापस rc;
पूर्ण
device_initcall(hvc_vio_init); /* after drivers/tty/hvc/hvc_console.c */

व्योम __init hvc_vio_init_early(व्योम)
अणु
	स्थिर __be32 *termno;
	स्थिर काष्ठा hv_ops *ops;

	/* find the boot console from /chosen/मानक_निकास */
	/* Check अगर it's a भव terminal */
	अगर (!of_node_name_prefix(of_मानक_निकास, "vty"))
		वापस;
	termno = of_get_property(of_मानक_निकास, "reg", शून्य);
	अगर (termno == शून्य)
		वापस;
	hvterm_priv0.termno = of_पढ़ो_number(termno, 1);
	spin_lock_init(&hvterm_priv0.buf_lock);
	hvterm_privs[0] = &hvterm_priv0;

	/* Check the protocol */
	अगर (of_device_is_compatible(of_मानक_निकास, "hvterm1")) अणु
		hvterm_priv0.proto = HV_PROTOCOL_RAW;
		ops = &hvterm_raw_ops;
	पूर्ण
	अन्यथा अगर (of_device_is_compatible(of_मानक_निकास, "hvterm-protocol")) अणु
		hvterm_priv0.proto = HV_PROTOCOL_HVSI;
		ops = &hvterm_hvsi_ops;
		hvsilib_init(&hvterm_priv0.hvsi, hvc_get_अक्षरs, hvc_put_अक्षरs,
			     hvterm_priv0.termno, 1);
		/* HVSI, perक्रमm the handshake now */
		hvsilib_establish(&hvterm_priv0.hvsi);
	पूर्ण अन्यथा
		वापस;
	udbg_अ_दो = udbg_hvc_अ_दो;
	udbg_अ_लो = udbg_hvc_अ_लो;
	udbg_अ_लो_poll = udbg_hvc_अ_लो_poll;
#अगर_घोषित HVC_OLD_HVSI
	/* When using the old HVSI driver करोn't रेजिस्टर the HVC
	 * backend क्रम HVSI, only करो udbg
	 */
	अगर (hvterm_priv0.proto == HV_PROTOCOL_HVSI)
		वापस;
#पूर्ण_अगर
	/* Check whether the user has requested a dअगरferent console. */
	अगर (!म_माला(boot_command_line, "console="))
		add_preferred_console("hvc", 0, शून्य);
	hvc_instantiate(0, 0, ops);
पूर्ण

/* call this from early_init() क्रम a working debug console on
 * vterm capable LPAR machines
 */
#अगर_घोषित CONFIG_PPC_EARLY_DEBUG_LPAR
व्योम __init udbg_init_debug_lpar(व्योम)
अणु
	/*
	 * If we're running as a hypervisor then we definitely can't call the
	 * hypervisor to prपूर्णांक debug output (we *are* the hypervisor), so करोn't
	 * रेजिस्टर अगर we detect that MSR_HV=1.
	 */
	अगर (mfmsr() & MSR_HV)
		वापस;

	hvterm_privs[0] = &hvterm_priv0;
	hvterm_priv0.termno = 0;
	hvterm_priv0.proto = HV_PROTOCOL_RAW;
	spin_lock_init(&hvterm_priv0.buf_lock);
	udbg_अ_दो = udbg_hvc_अ_दो;
	udbg_अ_लो = udbg_hvc_अ_लो;
	udbg_अ_लो_poll = udbg_hvc_अ_लो_poll;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_EARLY_DEBUG_LPAR */

#अगर_घोषित CONFIG_PPC_EARLY_DEBUG_LPAR_HVSI
व्योम __init udbg_init_debug_lpar_hvsi(व्योम)
अणु
	/* See comment above in udbg_init_debug_lpar() */
	अगर (mfmsr() & MSR_HV)
		वापस;

	hvterm_privs[0] = &hvterm_priv0;
	hvterm_priv0.termno = CONFIG_PPC_EARLY_DEBUG_HVSI_VTERMNO;
	hvterm_priv0.proto = HV_PROTOCOL_HVSI;
	spin_lock_init(&hvterm_priv0.buf_lock);
	udbg_अ_दो = udbg_hvc_अ_दो;
	udbg_अ_लो = udbg_hvc_अ_लो;
	udbg_अ_लो_poll = udbg_hvc_अ_लो_poll;
	hvsilib_init(&hvterm_priv0.hvsi, hvc_get_अक्षरs, hvc_put_अक्षरs,
		     hvterm_priv0.termno, 1);
	hvsilib_establish(&hvterm_priv0.hvsi);
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_EARLY_DEBUG_LPAR_HVSI */
