<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* vcc.c: sun4v भव channel concentrator
 *
 * Copyright (C) 2017 Oracle. All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <यंत्र/vपन.स>
#समावेश <यंत्र/ldc.h>

MODULE_DESCRIPTION("Sun LDOM virtual console concentrator driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.1");

काष्ठा vcc_port अणु
	काष्ठा vio_driver_state vio;

	spinlock_t lock;
	अक्षर *करोमुख्य;
	काष्ठा tty_काष्ठा *tty;	/* only populated जबतक dev is खोलो */
	अचिन्हित दीर्घ index;	/* index पूर्णांकo the vcc_table */

	u64 refcnt;
	bool excl_locked;

	bool हटाओd;

	/* This buffer is required to support the tty ग_लिखो_room पूर्णांकerface
	 * and guarantee that any अक्षरacters that the driver accepts will
	 * be eventually sent, either immediately or later.
	 */
	पूर्णांक अक्षरs_in_buffer;
	काष्ठा vio_vcc buffer;

	काष्ठा समयr_list rx_समयr;
	काष्ठा समयr_list tx_समयr;
पूर्ण;

/* Microseconds that thपढ़ो will delay रुकोing क्रम a vcc port ref */
#घोषणा VCC_REF_DELAY		100

#घोषणा VCC_MAX_PORTS		1024
#घोषणा VCC_MINOR_START		0	/* must be zero */
#घोषणा VCC_BUFF_LEN		VIO_VCC_MTU_SIZE

#घोषणा VCC_CTL_BREAK		-1
#घोषणा VCC_CTL_HUP		-2

अटल काष्ठा tty_driver *vcc_tty_driver;

अटल काष्ठा vcc_port *vcc_table[VCC_MAX_PORTS];
अटल DEFINE_SPINLOCK(vcc_table_lock);

अटल अचिन्हित पूर्णांक vcc_dbg;
अटल अचिन्हित पूर्णांक vcc_dbg_ldc;
अटल अचिन्हित पूर्णांक vcc_dbg_vio;

module_param(vcc_dbg, uपूर्णांक, 0664);
module_param(vcc_dbg_ldc, uपूर्णांक, 0664);
module_param(vcc_dbg_vio, uपूर्णांक, 0664);

#घोषणा VCC_DBG_DRV	0x1
#घोषणा VCC_DBG_LDC	0x2
#घोषणा VCC_DBG_PKT	0x4

#घोषणा vccdbg(f, a...)						\
	करो अणु							\
		अगर (vcc_dbg & VCC_DBG_DRV)			\
			pr_info(f, ## a);			\
	पूर्ण जबतक (0)						\

#घोषणा vccdbgl(l)						\
	करो अणु							\
		अगर (vcc_dbg & VCC_DBG_LDC)			\
			ldc_prपूर्णांक(l);				\
	पूर्ण जबतक (0)						\

#घोषणा vccdbgp(pkt)						\
	करो अणु							\
		अगर (vcc_dbg & VCC_DBG_PKT) अणु			\
			पूर्णांक i;					\
			क्रम (i = 0; i < pkt.tag.stype; i++)	\
				pr_info("[%c]", pkt.data[i]);	\
		पूर्ण						\
	पूर्ण जबतक (0)						\

/* Note: Be careful when adding flags to this line discipline.  Don't
 * add anything that will cause echoing or we'll go पूर्णांकo recursive
 * loop echoing अक्षरs back and क्रमth with the console drivers.
 */
अटल स्थिर काष्ठा ktermios vcc_tty_termios = अणु
	.c_अगरlag = IGNBRK | IGNPAR,
	.c_oflag = OPOST,
	.c_cflag = B38400 | CS8 | CREAD | HUPCL,
	.c_cc = INIT_C_CC,
	.c_ispeed = 38400,
	.c_ospeed = 38400
पूर्ण;

/**
 * vcc_table_add() - Add VCC port to the VCC table
 * @port: poपूर्णांकer to the VCC port
 *
 * Return: index of the port in the VCC table on success,
 *	   -1 on failure
 */
अटल पूर्णांक vcc_table_add(काष्ठा vcc_port *port)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&vcc_table_lock, flags);
	क्रम (i = VCC_MINOR_START; i < VCC_MAX_PORTS; i++) अणु
		अगर (!vcc_table[i]) अणु
			vcc_table[i] = port;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&vcc_table_lock, flags);

	अगर (i < VCC_MAX_PORTS)
		वापस i;
	अन्यथा
		वापस -1;
पूर्ण

/**
 * vcc_table_हटाओ() - Removes a VCC port from the VCC table
 * @index: Index पूर्णांकo the VCC table
 */
अटल व्योम vcc_table_हटाओ(अचिन्हित दीर्घ index)
अणु
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(index >= VCC_MAX_PORTS))
		वापस;

	spin_lock_irqsave(&vcc_table_lock, flags);
	vcc_table[index] = शून्य;
	spin_unlock_irqrestore(&vcc_table_lock, flags);
पूर्ण

/**
 * vcc_get() - Gets a reference to VCC port
 * @index: Index पूर्णांकo the VCC table
 * @excl: Indicates अगर an exclusive access is requested
 *
 * Return: reference to the VCC port, अगर found
 *	   शून्य, अगर port not found
 */
अटल काष्ठा vcc_port *vcc_get(अचिन्हित दीर्घ index, bool excl)
अणु
	काष्ठा vcc_port *port;
	अचिन्हित दीर्घ flags;

try_again:
	spin_lock_irqsave(&vcc_table_lock, flags);

	port = vcc_table[index];
	अगर (!port) अणु
		spin_unlock_irqrestore(&vcc_table_lock, flags);
		वापस शून्य;
	पूर्ण

	अगर (!excl) अणु
		अगर (port->excl_locked) अणु
			spin_unlock_irqrestore(&vcc_table_lock, flags);
			udelay(VCC_REF_DELAY);
			जाओ try_again;
		पूर्ण
		port->refcnt++;
		spin_unlock_irqrestore(&vcc_table_lock, flags);
		वापस port;
	पूर्ण

	अगर (port->refcnt) अणु
		spin_unlock_irqrestore(&vcc_table_lock, flags);
		/* Thपढ़ोs wanting exclusive access will रुको half the समय,
		 * probably giving them higher priority in the हाल of
		 * multiple रुकोers.
		 */
		udelay(VCC_REF_DELAY/2);
		जाओ try_again;
	पूर्ण

	port->refcnt++;
	port->excl_locked = true;
	spin_unlock_irqrestore(&vcc_table_lock, flags);

	वापस port;
पूर्ण

/**
 * vcc_put() - Returns a reference to VCC port
 * @port: poपूर्णांकer to VCC port
 * @excl: Indicates अगर the वापसed reference is an exclusive reference
 *
 * Note: It's the caller's responsibility to ensure the correct value
 *	 क्रम the excl flag
 */
अटल व्योम vcc_put(काष्ठा vcc_port *port, bool excl)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!port)
		वापस;

	spin_lock_irqsave(&vcc_table_lock, flags);

	/* check अगर caller attempted to put with the wrong flags */
	अगर (WARN_ON((excl && !port->excl_locked) ||
		    (!excl && port->excl_locked)))
		जाओ करोne;

	port->refcnt--;

	अगर (excl)
		port->excl_locked = false;

करोne:
	spin_unlock_irqrestore(&vcc_table_lock, flags);
पूर्ण

/**
 * vcc_get_ne() - Get a non-exclusive reference to VCC port
 * @index: Index पूर्णांकo the VCC table
 *
 * Gets a non-exclusive reference to VCC port, अगर it's not हटाओd
 *
 * Return: poपूर्णांकer to the VCC port, अगर found
 *	   शून्य, अगर port not found
 */
अटल काष्ठा vcc_port *vcc_get_ne(अचिन्हित दीर्घ index)
अणु
	काष्ठा vcc_port *port;

	port = vcc_get(index, false);

	अगर (port && port->हटाओd) अणु
		vcc_put(port, false);
		वापस शून्य;
	पूर्ण

	वापस port;
पूर्ण

अटल व्योम vcc_kick_rx(काष्ठा vcc_port *port)
अणु
	काष्ठा vio_driver_state *vio = &port->vio;

	निश्चित_spin_locked(&port->lock);

	अगर (!समयr_pending(&port->rx_समयr) && !port->हटाओd) अणु
		disable_irq_nosync(vio->vdev->rx_irq);
		port->rx_समयr.expires = (jअगरfies + 1);
		add_समयr(&port->rx_समयr);
	पूर्ण
पूर्ण

अटल व्योम vcc_kick_tx(काष्ठा vcc_port *port)
अणु
	निश्चित_spin_locked(&port->lock);

	अगर (!समयr_pending(&port->tx_समयr) && !port->हटाओd) अणु
		port->tx_समयr.expires = (jअगरfies + 1);
		add_समयr(&port->tx_समयr);
	पूर्ण
पूर्ण

अटल पूर्णांक vcc_rx_check(काष्ठा tty_काष्ठा *tty, पूर्णांक size)
अणु
	अगर (WARN_ON(!tty || !tty->port))
		वापस 1;

	/* tty_buffer_request_room won't sleep because it uses
	 * GFP_ATOMIC flag to allocate buffer
	 */
	अगर (test_bit(TTY_THROTTLED, &tty->flags) ||
	    (tty_buffer_request_room(tty->port, VCC_BUFF_LEN) < VCC_BUFF_LEN))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक vcc_rx(काष्ठा tty_काष्ठा *tty, अक्षर *buf, पूर्णांक size)
अणु
	पूर्णांक len = 0;

	अगर (WARN_ON(!tty || !tty->port))
		वापस len;

	len = tty_insert_flip_string(tty->port, buf, size);
	अगर (len)
		tty_flip_buffer_push(tty->port);

	वापस len;
पूर्ण

अटल पूर्णांक vcc_ldc_पढ़ो(काष्ठा vcc_port *port)
अणु
	काष्ठा vio_driver_state *vio = &port->vio;
	काष्ठा tty_काष्ठा *tty;
	काष्ठा vio_vcc pkt;
	पूर्णांक rv = 0;

	tty = port->tty;
	अगर (!tty) अणु
		rv = ldc_rx_reset(vio->lp);
		vccdbg("VCC: reset rx q: rv=%d\n", rv);
		जाओ करोne;
	पूर्ण

	/* Read as दीर्घ as LDC has incoming data. */
	जबतक (1) अणु
		अगर (!vcc_rx_check(tty, VIO_VCC_MTU_SIZE)) अणु
			vcc_kick_rx(port);
			अवरोध;
		पूर्ण

		vccdbgl(vio->lp);

		rv = ldc_पढ़ो(vio->lp, &pkt, माप(pkt));
		अगर (rv <= 0)
			अवरोध;

		vccdbg("VCC: ldc_read()=%d\n", rv);
		vccdbg("TAG [%02x:%02x:%04x:%08x]\n",
		       pkt.tag.type, pkt.tag.stype,
		       pkt.tag.stype_env, pkt.tag.sid);

		अगर (pkt.tag.type == VIO_TYPE_DATA) अणु
			vccdbgp(pkt);
			/* vcc_rx_check ensures memory availability */
			vcc_rx(tty, pkt.data, pkt.tag.stype);
		पूर्ण अन्यथा अणु
			pr_err("VCC: unknown msg [%02x:%02x:%04x:%08x]\n",
			       pkt.tag.type, pkt.tag.stype,
			       pkt.tag.stype_env, pkt.tag.sid);
			rv = -ECONNRESET;
			अवरोध;
		पूर्ण

		WARN_ON(rv != LDC_PACKET_SIZE);
	पूर्ण

करोne:
	वापस rv;
पूर्ण

अटल व्योम vcc_rx_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा vcc_port *port = from_समयr(port, t, rx_समयr);
	काष्ठा vio_driver_state *vio;
	अचिन्हित दीर्घ flags;
	पूर्णांक rv;

	spin_lock_irqsave(&port->lock, flags);
	port->rx_समयr.expires = 0;

	vio = &port->vio;

	enable_irq(vio->vdev->rx_irq);

	अगर (!port->tty || port->हटाओd)
		जाओ करोne;

	rv = vcc_ldc_पढ़ो(port);
	अगर (rv == -ECONNRESET)
		vio_conn_reset(vio);

करोne:
	spin_unlock_irqrestore(&port->lock, flags);
	vcc_put(port, false);
पूर्ण

अटल व्योम vcc_tx_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा vcc_port *port = from_समयr(port, t, tx_समयr);
	काष्ठा vio_vcc *pkt;
	अचिन्हित दीर्घ flags;
	पूर्णांक tosend = 0;
	पूर्णांक rv;

	spin_lock_irqsave(&port->lock, flags);
	port->tx_समयr.expires = 0;

	अगर (!port->tty || port->हटाओd)
		जाओ करोne;

	tosend = min(VCC_BUFF_LEN, port->अक्षरs_in_buffer);
	अगर (!tosend)
		जाओ करोne;

	pkt = &port->buffer;
	pkt->tag.type = VIO_TYPE_DATA;
	pkt->tag.stype = tosend;
	vccdbgl(port->vio.lp);

	rv = ldc_ग_लिखो(port->vio.lp, pkt, (VIO_TAG_SIZE + tosend));
	WARN_ON(!rv);

	अगर (rv < 0) अणु
		vccdbg("VCC: ldc_write()=%d\n", rv);
		vcc_kick_tx(port);
	पूर्ण अन्यथा अणु
		काष्ठा tty_काष्ठा *tty = port->tty;

		port->अक्षरs_in_buffer = 0;
		अगर (tty)
			tty_wakeup(tty);
	पूर्ण

करोne:
	spin_unlock_irqrestore(&port->lock, flags);
	vcc_put(port, false);
पूर्ण

/**
 * vcc_event() - LDC event processing engine
 * @arg: VCC निजी data
 * @event: LDC event
 *
 * Handles LDC events क्रम VCC
 */
अटल व्योम vcc_event(व्योम *arg, पूर्णांक event)
अणु
	काष्ठा vio_driver_state *vio;
	काष्ठा vcc_port *port;
	अचिन्हित दीर्घ flags;
	पूर्णांक rv;

	port = arg;
	vio = &port->vio;

	spin_lock_irqsave(&port->lock, flags);

	चयन (event) अणु
	हाल LDC_EVENT_RESET:
	हाल LDC_EVENT_UP:
		vio_link_state_change(vio, event);
		अवरोध;

	हाल LDC_EVENT_DATA_READY:
		rv = vcc_ldc_पढ़ो(port);
		अगर (rv == -ECONNRESET)
			vio_conn_reset(vio);
		अवरोध;

	शेष:
		pr_err("VCC: unexpected LDC event(%d)\n", event);
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल काष्ठा ldc_channel_config vcc_ldc_cfg = अणु
	.event		= vcc_event,
	.mtu		= VIO_VCC_MTU_SIZE,
	.mode		= LDC_MODE_RAW,
	.debug		= 0,
पूर्ण;

/* Ordered from largest major to lowest */
अटल काष्ठा vio_version vcc_versions[] = अणु
	अणु .major = 1, .minor = 0 पूर्ण,
पूर्ण;

अटल काष्ठा tty_port_operations vcc_port_ops = अणु 0 पूर्ण;

अटल sमाप_प्रकार vcc_sysfs_करोमुख्य_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा vcc_port *port;
	पूर्णांक rv;

	port = dev_get_drvdata(dev);
	अगर (!port)
		वापस -ENODEV;

	rv = scnम_लिखो(buf, PAGE_SIZE, "%s\n", port->करोमुख्य);

	वापस rv;
पूर्ण

अटल पूर्णांक vcc_send_ctl(काष्ठा vcc_port *port, पूर्णांक ctl)
अणु
	काष्ठा vio_vcc pkt;
	पूर्णांक rv;

	pkt.tag.type = VIO_TYPE_CTRL;
	pkt.tag.sid = ctl;
	pkt.tag.stype = 0;

	rv = ldc_ग_लिखो(port->vio.lp, &pkt, माप(pkt.tag));
	WARN_ON(!rv);
	vccdbg("VCC: ldc_write(%ld)=%d\n", माप(pkt.tag), rv);

	वापस rv;
पूर्ण

अटल sमाप_प्रकार vcc_sysfs_अवरोध_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा vcc_port *port;
	अचिन्हित दीर्घ flags;
	पूर्णांक rv = count;
	पूर्णांक brk;

	port = dev_get_drvdata(dev);
	अगर (!port)
		वापस -ENODEV;

	spin_lock_irqsave(&port->lock, flags);

	अगर (माला_पूछो(buf, "%ud", &brk) != 1 || brk != 1)
		rv = -EINVAL;
	अन्यथा अगर (vcc_send_ctl(port, VCC_CTL_BREAK) < 0)
		vcc_kick_tx(port);

	spin_unlock_irqrestore(&port->lock, flags);

	वापस rv;
पूर्ण

अटल DEVICE_ATTR(करोमुख्य, 0400, vcc_sysfs_करोमुख्य_show, शून्य);
अटल DEVICE_ATTR(अवरोध, 0200, शून्य, vcc_sysfs_अवरोध_store);

अटल काष्ठा attribute *vcc_sysfs_entries[] = अणु
	&dev_attr_करोमुख्य.attr,
	&dev_attr_अवरोध.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group vcc_attribute_group = अणु
	.name = शून्य,
	.attrs = vcc_sysfs_entries,
पूर्ण;

/**
 * vcc_probe() - Initialize VCC port
 * @vdev: Poपूर्णांकer to VIO device of the new VCC port
 * @id: VIO device ID
 *
 * Initializes a VCC port to receive serial console data from
 * the guest करोमुख्य. Sets up a TTY end poपूर्णांक on the control
 * करोमुख्य. Sets up VIO/LDC link between the guest & control
 * करोमुख्य endpoपूर्णांकs.
 *
 * Return: status of the probe
 */
अटल पूर्णांक vcc_probe(काष्ठा vio_dev *vdev, स्थिर काष्ठा vio_device_id *id)
अणु
	काष्ठा mdesc_handle *hp;
	काष्ठा vcc_port *port;
	काष्ठा device *dev;
	स्थिर अक्षर *करोमुख्य;
	अक्षर *name;
	u64 node;
	पूर्णांक rv;

	vccdbg("VCC: name=%s\n", dev_name(&vdev->dev));

	अगर (!vcc_tty_driver) अणु
		pr_err("VCC: TTY driver not registered\n");
		वापस -ENODEV;
	पूर्ण

	port = kzalloc(माप(काष्ठा vcc_port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	name = kstrdup(dev_name(&vdev->dev), GFP_KERNEL);

	rv = vio_driver_init(&port->vio, vdev, VDEV_CONSOLE_CON, vcc_versions,
			     ARRAY_SIZE(vcc_versions), शून्य, name);
	अगर (rv)
		जाओ मुक्त_port;

	port->vio.debug = vcc_dbg_vio;
	vcc_ldc_cfg.debug = vcc_dbg_ldc;

	rv = vio_ldc_alloc(&port->vio, &vcc_ldc_cfg, port);
	अगर (rv)
		जाओ मुक्त_port;

	spin_lock_init(&port->lock);

	port->index = vcc_table_add(port);
	अगर (port->index == -1) अणु
		pr_err("VCC: no more TTY indices left for allocation\n");
		rv = -ENOMEM;
		जाओ मुक्त_ldc;
	पूर्ण

	/* Register the device using VCC table index as TTY index */
	dev = tty_रेजिस्टर_device(vcc_tty_driver, port->index, &vdev->dev);
	अगर (IS_ERR(dev)) अणु
		rv = PTR_ERR(dev);
		जाओ मुक्त_table;
	पूर्ण

	hp = mdesc_grab();

	node = vio_vdev_node(hp, vdev);
	अगर (node == MDESC_NODE_शून्य) अणु
		rv = -ENXIO;
		mdesc_release(hp);
		जाओ unreg_tty;
	पूर्ण

	करोमुख्य = mdesc_get_property(hp, node, "vcc-domain-name", शून्य);
	अगर (!करोमुख्य) अणु
		rv = -ENXIO;
		mdesc_release(hp);
		जाओ unreg_tty;
	पूर्ण
	port->करोमुख्य = kstrdup(करोमुख्य, GFP_KERNEL);

	mdesc_release(hp);

	rv = sysfs_create_group(&vdev->dev.kobj, &vcc_attribute_group);
	अगर (rv)
		जाओ मुक्त_करोमुख्य;

	समयr_setup(&port->rx_समयr, vcc_rx_समयr, 0);
	समयr_setup(&port->tx_समयr, vcc_tx_समयr, 0);

	dev_set_drvdata(&vdev->dev, port);

	/* It's possible to receive IRQs in the middle of vio_port_up. Disable
	 * IRQs until the port is up.
	 */
	disable_irq_nosync(vdev->rx_irq);
	vio_port_up(&port->vio);
	enable_irq(vdev->rx_irq);

	वापस 0;

मुक्त_करोमुख्य:
	kमुक्त(port->करोमुख्य);
unreg_tty:
	tty_unरेजिस्टर_device(vcc_tty_driver, port->index);
मुक्त_table:
	vcc_table_हटाओ(port->index);
मुक्त_ldc:
	vio_ldc_मुक्त(&port->vio);
मुक्त_port:
	kमुक्त(name);
	kमुक्त(port);

	वापस rv;
पूर्ण

/**
 * vcc_हटाओ() - Terminate a VCC port
 * @vdev: Poपूर्णांकer to VIO device of the VCC port
 *
 * Terminates a VCC port. Sets up the tearकरोwn of TTY and
 * VIO/LDC link between guest and primary करोमुख्यs.
 *
 * Return: status of removal
 */
अटल पूर्णांक vcc_हटाओ(काष्ठा vio_dev *vdev)
अणु
	काष्ठा vcc_port *port = dev_get_drvdata(&vdev->dev);

	del_समयr_sync(&port->rx_समयr);
	del_समयr_sync(&port->tx_समयr);

	/* If there's a process with the device खोलो, करो a synchronous
	 * hangup of the TTY. This *may* cause the process to call बंद
	 * asynchronously, but it's not guaranteed.
	 */
	अगर (port->tty)
		tty_vhangup(port->tty);

	/* Get exclusive reference to VCC, ensures that there are no other
	 * clients to this port. This cannot fail.
	 */
	vcc_get(port->index, true);

	tty_unरेजिस्टर_device(vcc_tty_driver, port->index);

	del_समयr_sync(&port->vio.समयr);
	vio_ldc_मुक्त(&port->vio);
	sysfs_हटाओ_group(&vdev->dev.kobj, &vcc_attribute_group);
	dev_set_drvdata(&vdev->dev, शून्य);
	अगर (port->tty) अणु
		port->हटाओd = true;
		vcc_put(port, true);
	पूर्ण अन्यथा अणु
		vcc_table_हटाओ(port->index);

		kमुक्त(port->vio.name);
		kमुक्त(port->करोमुख्य);
		kमुक्त(port);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vio_device_id vcc_match[] = अणु
	अणु
		.type = "vcc-port",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(vio, vcc_match);

अटल काष्ठा vio_driver vcc_driver = अणु
	.id_table	= vcc_match,
	.probe		= vcc_probe,
	.हटाओ		= vcc_हटाओ,
	.name		= "vcc",
पूर्ण;

अटल पूर्णांक vcc_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *vcc_file)
अणु
	काष्ठा vcc_port *port;

	अगर (tty->count > 1)
		वापस -EBUSY;

	port = vcc_get_ne(tty->index);
	अगर (unlikely(!port)) अणु
		pr_err("VCC: open: Failed to find VCC port\n");
		वापस -ENODEV;
	पूर्ण

	अगर (unlikely(!port->vio.lp)) अणु
		pr_err("VCC: open: LDC channel not configured\n");
		vcc_put(port, false);
		वापस -EPIPE;
	पूर्ण
	vccdbgl(port->vio.lp);

	vcc_put(port, false);

	अगर (unlikely(!tty->port)) अणु
		pr_err("VCC: open: TTY port not found\n");
		वापस -ENXIO;
	पूर्ण

	अगर (unlikely(!tty->port->ops)) अणु
		pr_err("VCC: open: TTY ops not defined\n");
		वापस -ENXIO;
	पूर्ण

	वापस tty_port_खोलो(tty->port, tty, vcc_file);
पूर्ण

अटल व्योम vcc_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *vcc_file)
अणु
	अगर (unlikely(tty->count > 1))
		वापस;

	अगर (unlikely(!tty->port)) अणु
		pr_err("VCC: close: TTY port not found\n");
		वापस;
	पूर्ण

	tty_port_बंद(tty->port, tty, vcc_file);
पूर्ण

अटल व्योम vcc_ldc_hup(काष्ठा vcc_port *port)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	अगर (vcc_send_ctl(port, VCC_CTL_HUP) < 0)
		vcc_kick_tx(port);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम vcc_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा vcc_port *port;

	port = vcc_get_ne(tty->index);
	अगर (unlikely(!port)) अणु
		pr_err("VCC: hangup: Failed to find VCC port\n");
		वापस;
	पूर्ण

	अगर (unlikely(!tty->port)) अणु
		pr_err("VCC: hangup: TTY port not found\n");
		vcc_put(port, false);
		वापस;
	पूर्ण

	vcc_ldc_hup(port);

	vcc_put(port, false);

	tty_port_hangup(tty->port);
पूर्ण

अटल पूर्णांक vcc_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf,
		     पूर्णांक count)
अणु
	काष्ठा vcc_port *port;
	काष्ठा vio_vcc *pkt;
	अचिन्हित दीर्घ flags;
	पूर्णांक total_sent = 0;
	पूर्णांक tosend = 0;
	पूर्णांक rv = -EINVAL;

	port = vcc_get_ne(tty->index);
	अगर (unlikely(!port)) अणु
		pr_err("VCC: write: Failed to find VCC port");
		वापस -ENODEV;
	पूर्ण

	spin_lock_irqsave(&port->lock, flags);

	pkt = &port->buffer;
	pkt->tag.type = VIO_TYPE_DATA;

	जबतक (count > 0) अणु
		/* Minimum of data to ग_लिखो and space available */
		tosend = min(count, (VCC_BUFF_LEN - port->अक्षरs_in_buffer));

		अगर (!tosend)
			अवरोध;

		स_नकल(&pkt->data[port->अक्षरs_in_buffer], &buf[total_sent],
		       tosend);
		port->अक्षरs_in_buffer += tosend;
		pkt->tag.stype = tosend;

		vccdbg("TAG [%02x:%02x:%04x:%08x]\n", pkt->tag.type,
		       pkt->tag.stype, pkt->tag.stype_env, pkt->tag.sid);
		vccdbg("DATA [%s]\n", pkt->data);
		vccdbgl(port->vio.lp);

		/* Since we know we have enough room in VCC buffer क्रम tosend
		 * we record that it was sent regardless of whether the
		 * hypervisor actually took it because we have it buffered.
		 */
		rv = ldc_ग_लिखो(port->vio.lp, pkt, (VIO_TAG_SIZE + tosend));
		vccdbg("VCC: write: ldc_write(%d)=%d\n",
		       (VIO_TAG_SIZE + tosend), rv);

		total_sent += tosend;
		count -= tosend;
		अगर (rv < 0) अणु
			vcc_kick_tx(port);
			अवरोध;
		पूर्ण

		port->अक्षरs_in_buffer = 0;
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);

	vcc_put(port, false);

	vccdbg("VCC: write: total=%d rv=%d", total_sent, rv);

	वापस total_sent ? total_sent : rv;
पूर्ण

अटल पूर्णांक vcc_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा vcc_port *port;
	u64 num;

	port = vcc_get_ne(tty->index);
	अगर (unlikely(!port)) अणु
		pr_err("VCC: write_room: Failed to find VCC port\n");
		वापस 0;
	पूर्ण

	num = VCC_BUFF_LEN - port->अक्षरs_in_buffer;

	vcc_put(port, false);

	वापस num;
पूर्ण

अटल पूर्णांक vcc_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा vcc_port *port;
	u64 num;

	port = vcc_get_ne(tty->index);
	अगर (unlikely(!port)) अणु
		pr_err("VCC: chars_in_buffer: Failed to find VCC port\n");
		वापस 0;
	पूर्ण

	num = port->अक्षरs_in_buffer;

	vcc_put(port, false);

	वापस num;
पूर्ण

अटल पूर्णांक vcc_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक state)
अणु
	काष्ठा vcc_port *port;
	अचिन्हित दीर्घ flags;

	port = vcc_get_ne(tty->index);
	अगर (unlikely(!port)) अणु
		pr_err("VCC: break_ctl: Failed to find VCC port\n");
		वापस -ENODEV;
	पूर्ण

	/* Turn off अवरोध */
	अगर (state == 0) अणु
		vcc_put(port, false);
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&port->lock, flags);

	अगर (vcc_send_ctl(port, VCC_CTL_BREAK) < 0)
		vcc_kick_tx(port);

	spin_unlock_irqrestore(&port->lock, flags);

	vcc_put(port, false);

	वापस 0;
पूर्ण

अटल पूर्णांक vcc_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा vcc_port *port_vcc;
	काष्ठा tty_port *port_tty;
	पूर्णांक ret;

	अगर (tty->index >= VCC_MAX_PORTS)
		वापस -EINVAL;

	ret = tty_standard_install(driver, tty);
	अगर (ret)
		वापस ret;

	port_tty = kzalloc(माप(काष्ठा tty_port), GFP_KERNEL);
	अगर (!port_tty)
		वापस -ENOMEM;

	port_vcc = vcc_get(tty->index, true);
	अगर (!port_vcc) अणु
		pr_err("VCC: install: Failed to find VCC port\n");
		tty->port = शून्य;
		kमुक्त(port_tty);
		वापस -ENODEV;
	पूर्ण

	tty_port_init(port_tty);
	port_tty->ops = &vcc_port_ops;
	tty->port = port_tty;

	port_vcc->tty = tty;

	vcc_put(port_vcc, true);

	वापस 0;
पूर्ण

अटल व्योम vcc_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा vcc_port *port;

	port = vcc_get(tty->index, true);
	अगर (port) अणु
		port->tty = शून्य;

		अगर (port->हटाओd) अणु
			vcc_table_हटाओ(tty->index);
			kमुक्त(port->vio.name);
			kमुक्त(port->करोमुख्य);
			kमुक्त(port);
		पूर्ण अन्यथा अणु
			vcc_put(port, true);
		पूर्ण
	पूर्ण

	tty_port_destroy(tty->port);
	kमुक्त(tty->port);
	tty->port = शून्य;
पूर्ण

अटल स्थिर काष्ठा tty_operations vcc_ops = अणु
	.खोलो			= vcc_खोलो,
	.बंद			= vcc_बंद,
	.hangup			= vcc_hangup,
	.ग_लिखो			= vcc_ग_लिखो,
	.ग_लिखो_room		= vcc_ग_लिखो_room,
	.अक्षरs_in_buffer	= vcc_अक्षरs_in_buffer,
	.अवरोध_ctl		= vcc_अवरोध_ctl,
	.install		= vcc_install,
	.cleanup		= vcc_cleanup,
पूर्ण;

#घोषणा VCC_TTY_FLAGS   (TTY_DRIVER_DYNAMIC_DEV | TTY_DRIVER_REAL_RAW)

अटल पूर्णांक vcc_tty_init(व्योम)
अणु
	पूर्णांक rv;

	vcc_tty_driver = tty_alloc_driver(VCC_MAX_PORTS, VCC_TTY_FLAGS);
	अगर (IS_ERR(vcc_tty_driver)) अणु
		pr_err("VCC: TTY driver alloc failed\n");
		वापस PTR_ERR(vcc_tty_driver);
	पूर्ण

	vcc_tty_driver->driver_name = "vcc";
	vcc_tty_driver->name = "vcc";

	vcc_tty_driver->minor_start = VCC_MINOR_START;
	vcc_tty_driver->type = TTY_DRIVER_TYPE_SYSTEM;
	vcc_tty_driver->init_termios = vcc_tty_termios;

	tty_set_operations(vcc_tty_driver, &vcc_ops);

	rv = tty_रेजिस्टर_driver(vcc_tty_driver);
	अगर (rv) अणु
		pr_err("VCC: TTY driver registration failed\n");
		put_tty_driver(vcc_tty_driver);
		vcc_tty_driver = शून्य;
		वापस rv;
	पूर्ण

	vccdbg("VCC: TTY driver registered\n");

	वापस 0;
पूर्ण

अटल व्योम vcc_tty_निकास(व्योम)
अणु
	tty_unरेजिस्टर_driver(vcc_tty_driver);
	put_tty_driver(vcc_tty_driver);
	vccdbg("VCC: TTY driver unregistered\n");

	vcc_tty_driver = शून्य;
पूर्ण

अटल पूर्णांक __init vcc_init(व्योम)
अणु
	पूर्णांक rv;

	rv = vcc_tty_init();
	अगर (rv) अणु
		pr_err("VCC: TTY init failed\n");
		वापस rv;
	पूर्ण

	rv = vio_रेजिस्टर_driver(&vcc_driver);
	अगर (rv) अणु
		pr_err("VCC: VIO driver registration failed\n");
		vcc_tty_निकास();
	पूर्ण अन्यथा अणु
		vccdbg("VCC: VIO driver registered successfully\n");
	पूर्ण

	वापस rv;
पूर्ण

अटल व्योम __निकास vcc_निकास(व्योम)
अणु
	vio_unरेजिस्टर_driver(&vcc_driver);
	vccdbg("VCC: VIO driver unregistered\n");
	vcc_tty_निकास();
	vccdbg("VCC: TTY driver unregistered\n");
पूर्ण

module_init(vcc_init);
module_निकास(vcc_निकास);
