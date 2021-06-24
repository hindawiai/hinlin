<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PCMCIA 16-bit resource management functions
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * Copyright (C) 1999	     David A. Hinds
 * Copyright (C) 2004-2010   Dominik Broकरोwski
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/irq.h>

#समावेश <pcmcia/ss.h>
#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ds.h>

#समावेश "cs_internal.h"


/* Access speed क्रम IO winकरोws */
अटल पूर्णांक io_speed;
module_param(io_speed, पूर्णांक, 0444);


पूर्णांक pcmcia_validate_mem(काष्ठा pcmcia_socket *s)
अणु
	अगर (s->resource_ops->validate_mem)
		वापस s->resource_ops->validate_mem(s);
	/* अगर there is no callback, we can assume that everything is OK */
	वापस 0;
पूर्ण

काष्ठा resource *pcmcia_find_mem_region(u_दीर्घ base, u_दीर्घ num, u_दीर्घ align,
				 पूर्णांक low, काष्ठा pcmcia_socket *s)
अणु
	अगर (s->resource_ops->find_mem)
		वापस s->resource_ops->find_mem(base, num, align, low, s);
	वापस शून्य;
पूर्ण


/**
 * release_io_space() - release IO ports allocated with alloc_io_space()
 * @s: pcmcia socket
 * @res: resource to release
 *
 */
अटल व्योम release_io_space(काष्ठा pcmcia_socket *s, काष्ठा resource *res)
अणु
	resource_माप_प्रकार num = resource_size(res);
	पूर्णांक i;

	dev_dbg(&s->dev, "release_io_space for %pR\n", res);

	क्रम (i = 0; i < MAX_IO_WIN; i++) अणु
		अगर (!s->io[i].res)
			जारी;
		अगर ((s->io[i].res->start <= res->start) &&
		    (s->io[i].res->end >= res->end)) अणु
			s->io[i].InUse -= num;
			अगर (res->parent)
				release_resource(res);
			res->start = res->end = 0;
			res->flags = IORESOURCE_IO;
			/* Free the winकरोw अगर no one अन्यथा is using it */
			अगर (s->io[i].InUse == 0) अणु
				release_resource(s->io[i].res);
				kमुक्त(s->io[i].res);
				s->io[i].res = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण


/**
 * alloc_io_space() - allocate IO ports क्रम use by a PCMCIA device
 * @s: pcmcia socket
 * @res: resource to allocate (begin: begin, end: size)
 * @lines: number of IO lines decoded by the PCMCIA card
 *
 * Special stuff क्रम managing IO winकरोws, because they are scarce
 */
अटल पूर्णांक alloc_io_space(काष्ठा pcmcia_socket *s, काष्ठा resource *res,
			अचिन्हित पूर्णांक lines)
अणु
	अचिन्हित पूर्णांक align;
	अचिन्हित पूर्णांक base = res->start;
	अचिन्हित पूर्णांक num = res->end;
	पूर्णांक ret;

	res->flags |= IORESOURCE_IO;

	dev_dbg(&s->dev, "alloc_io_space request for %pR, %d lines\n",
		res, lines);

	align = base ? (lines ? 1<<lines : 0) : 1;
	अगर (align && (align < num)) अणु
		अगर (base) अणु
			dev_dbg(&s->dev, "odd IO request\n");
			align = 0;
		पूर्ण अन्यथा
			जबतक (align && (align < num))
				align <<= 1;
	पूर्ण
	अगर (base & ~(align-1)) अणु
		dev_dbg(&s->dev, "odd IO request\n");
		align = 0;
	पूर्ण

	ret = s->resource_ops->find_io(s, res->flags, &base, num, align,
				&res->parent);
	अगर (ret) अणु
		dev_dbg(&s->dev, "alloc_io_space request failed (%d)\n", ret);
		वापस -EINVAL;
	पूर्ण

	res->start = base;
	res->end = res->start + num - 1;

	अगर (res->parent) अणु
		ret = request_resource(res->parent, res);
		अगर (ret) अणु
			dev_warn(&s->dev,
				"request_resource %pR failed: %d\n", res, ret);
			res->parent = शून्य;
			release_io_space(s, res);
		पूर्ण
	पूर्ण
	dev_dbg(&s->dev, "alloc_io_space request result %d: %pR\n", ret, res);
	वापस ret;
पूर्ण


/*
 * pcmcia_access_config() - पढ़ो or ग_लिखो card configuration रेजिस्टरs
 *
 * pcmcia_access_config() पढ़ोs and ग_लिखोs configuration रेजिस्टरs in
 * attribute memory.  Memory winकरोw 0 is reserved क्रम this and the tuple
 * पढ़ोing services. Drivers must use pcmcia_पढ़ो_config_byte() or
 * pcmcia_ग_लिखो_config_byte().
 */
अटल पूर्णांक pcmcia_access_config(काष्ठा pcmcia_device *p_dev,
				off_t where, u8 *val,
				पूर्णांक (*accessf) (काष्ठा pcmcia_socket *s,
						पूर्णांक attr, अचिन्हित पूर्णांक addr,
						अचिन्हित पूर्णांक len, व्योम *ptr))
अणु
	काष्ठा pcmcia_socket *s;
	config_t *c;
	पूर्णांक addr;
	पूर्णांक ret = 0;

	s = p_dev->socket;

	mutex_lock(&s->ops_mutex);
	c = p_dev->function_config;

	अगर (!(c->state & CONFIG_LOCKED)) अणु
		dev_dbg(&p_dev->dev, "Configuration isn't locked\n");
		mutex_unlock(&s->ops_mutex);
		वापस -EACCES;
	पूर्ण

	addr = (p_dev->config_base + where) >> 1;

	ret = accessf(s, 1, addr, 1, val);

	mutex_unlock(&s->ops_mutex);

	वापस ret;
पूर्ण


/*
 * pcmcia_पढ़ो_config_byte() - पढ़ो a byte from a card configuration रेजिस्टर
 *
 * pcmcia_पढ़ो_config_byte() पढ़ोs a byte from a configuration रेजिस्टर in
 * attribute memory.
 */
पूर्णांक pcmcia_पढ़ो_config_byte(काष्ठा pcmcia_device *p_dev, off_t where, u8 *val)
अणु
	वापस pcmcia_access_config(p_dev, where, val, pcmcia_पढ़ो_cis_mem);
पूर्ण
EXPORT_SYMBOL(pcmcia_पढ़ो_config_byte);


/*
 * pcmcia_ग_लिखो_config_byte() - ग_लिखो a byte to a card configuration रेजिस्टर
 *
 * pcmcia_ग_लिखो_config_byte() ग_लिखोs a byte to a configuration रेजिस्टर in
 * attribute memory.
 */
पूर्णांक pcmcia_ग_लिखो_config_byte(काष्ठा pcmcia_device *p_dev, off_t where, u8 val)
अणु
	वापस pcmcia_access_config(p_dev, where, &val, pcmcia_ग_लिखो_cis_mem);
पूर्ण
EXPORT_SYMBOL(pcmcia_ग_लिखो_config_byte);


/**
 * pcmcia_map_mem_page() - modअगरy iomem winकरोw to poपूर्णांक to a dअगरferent offset
 * @p_dev: pcmcia device
 * @res: iomem resource alपढ़ोy enabled by pcmcia_request_winकरोw()
 * @offset: card_offset to map
 *
 * pcmcia_map_mem_page() modअगरies what can be पढ़ो and written by accessing
 * an iomem range previously enabled by pcmcia_request_winकरोw(), by setting
 * the card_offset value to @offset.
 */
पूर्णांक pcmcia_map_mem_page(काष्ठा pcmcia_device *p_dev, काष्ठा resource *res,
			अचिन्हित पूर्णांक offset)
अणु
	काष्ठा pcmcia_socket *s = p_dev->socket;
	अचिन्हित पूर्णांक w;
	पूर्णांक ret;

	w = ((res->flags & IORESOURCE_BITS & WIN_FLAGS_REQ) >> 2) - 1;
	अगर (w >= MAX_WIN)
		वापस -EINVAL;

	mutex_lock(&s->ops_mutex);
	s->win[w].card_start = offset;
	ret = s->ops->set_mem_map(s, &s->win[w]);
	अगर (ret)
		dev_warn(&p_dev->dev, "failed to set_mem_map\n");
	mutex_unlock(&s->ops_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(pcmcia_map_mem_page);


/**
 * pcmcia_fixup_iowidth() - reduce io width to 8bit
 * @p_dev: pcmcia device
 *
 * pcmcia_fixup_iowidth() allows a PCMCIA device driver to reduce the
 * IO width to 8bit after having called pcmcia_enable_device()
 * previously.
 */
पूर्णांक pcmcia_fixup_iowidth(काष्ठा pcmcia_device *p_dev)
अणु
	काष्ठा pcmcia_socket *s = p_dev->socket;
	pccard_io_map io_off = अणु 0, 0, 0, 0, 1 पूर्ण;
	pccard_io_map io_on;
	पूर्णांक i, ret = 0;

	mutex_lock(&s->ops_mutex);

	dev_dbg(&p_dev->dev, "fixup iowidth to 8bit\n");

	अगर (!(s->state & SOCKET_PRESENT) ||
		!(p_dev->function_config->state & CONFIG_LOCKED)) अणु
		dev_dbg(&p_dev->dev, "No card? Config not locked?\n");
		ret = -EACCES;
		जाओ unlock;
	पूर्ण

	io_on.speed = io_speed;
	क्रम (i = 0; i < MAX_IO_WIN; i++) अणु
		अगर (!s->io[i].res)
			जारी;
		io_off.map = i;
		io_on.map = i;

		io_on.flags = MAP_ACTIVE | IO_DATA_PATH_WIDTH_8;
		io_on.start = s->io[i].res->start;
		io_on.stop = s->io[i].res->end;

		s->ops->set_io_map(s, &io_off);
		msleep(40);
		s->ops->set_io_map(s, &io_on);
	पूर्ण
unlock:
	mutex_unlock(&s->ops_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(pcmcia_fixup_iowidth);


/**
 * pcmcia_fixup_vpp() - set Vpp to a new voltage level
 * @p_dev: pcmcia device
 * @new_vpp: new Vpp voltage
 *
 * pcmcia_fixup_vpp() allows a PCMCIA device driver to set Vpp to
 * a new voltage level between calls to pcmcia_enable_device()
 * and pcmcia_disable_device().
 */
पूर्णांक pcmcia_fixup_vpp(काष्ठा pcmcia_device *p_dev, अचिन्हित अक्षर new_vpp)
अणु
	काष्ठा pcmcia_socket *s = p_dev->socket;
	पूर्णांक ret = 0;

	mutex_lock(&s->ops_mutex);

	dev_dbg(&p_dev->dev, "fixup Vpp to %d\n", new_vpp);

	अगर (!(s->state & SOCKET_PRESENT) ||
		!(p_dev->function_config->state & CONFIG_LOCKED)) अणु
		dev_dbg(&p_dev->dev, "No card? Config not locked?\n");
		ret = -EACCES;
		जाओ unlock;
	पूर्ण

	s->socket.Vpp = new_vpp;
	अगर (s->ops->set_socket(s, &s->socket)) अणु
		dev_warn(&p_dev->dev, "Unable to set VPP\n");
		ret = -EIO;
		जाओ unlock;
	पूर्ण
	p_dev->vpp = new_vpp;

unlock:
	mutex_unlock(&s->ops_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(pcmcia_fixup_vpp);


/**
 * pcmcia_release_configuration() - physically disable a PCMCIA device
 * @p_dev: pcmcia device
 *
 * pcmcia_release_configuration() is the 1:1 counterpart to
 * pcmcia_enable_device(): If a PCMCIA device is no दीर्घer used by any
 * driver, the Vpp voltage is set to 0, IRQs will no दीर्घer be generated,
 * and I/O ranges will be disabled. As pcmcia_release_io() and
 * pcmcia_release_winकरोw() still need to be called, device drivers are
 * expected to call pcmcia_disable_device() instead.
 */
पूर्णांक pcmcia_release_configuration(काष्ठा pcmcia_device *p_dev)
अणु
	pccard_io_map io = अणु 0, 0, 0, 0, 1 पूर्ण;
	काष्ठा pcmcia_socket *s = p_dev->socket;
	config_t *c;
	पूर्णांक i;

	mutex_lock(&s->ops_mutex);
	c = p_dev->function_config;
	अगर (p_dev->_locked) अणु
		p_dev->_locked = 0;
		अगर (--(s->lock_count) == 0) अणु
			s->socket.flags = SS_OUTPUT_ENA; /* Is this correct? */
			s->socket.Vpp = 0;
			s->socket.io_irq = 0;
			s->ops->set_socket(s, &s->socket);
		पूर्ण
	पूर्ण
	अगर (c->state & CONFIG_LOCKED) अणु
		c->state &= ~CONFIG_LOCKED;
		अगर (c->state & CONFIG_IO_REQ)
			क्रम (i = 0; i < MAX_IO_WIN; i++) अणु
				अगर (!s->io[i].res)
					जारी;
				s->io[i].Config--;
				अगर (s->io[i].Config != 0)
					जारी;
				io.map = i;
				s->ops->set_io_map(s, &io);
			पूर्ण
	पूर्ण
	mutex_unlock(&s->ops_mutex);

	वापस 0;
पूर्ण


/**
 * pcmcia_release_io() - release I/O allocated by a PCMCIA device
 * @p_dev: pcmcia device
 *
 * pcmcia_release_io() releases the I/O ranges allocated by a PCMCIA
 * device.  This may be invoked some समय after a card ejection has
 * alपढ़ोy dumped the actual socket configuration, so अगर the client is
 * "stale", we करोn't bother checking the port ranges against the
 * current socket values.
 */
अटल पूर्णांक pcmcia_release_io(काष्ठा pcmcia_device *p_dev)
अणु
	काष्ठा pcmcia_socket *s = p_dev->socket;
	पूर्णांक ret = -EINVAL;
	config_t *c;

	mutex_lock(&s->ops_mutex);
	अगर (!p_dev->_io)
		जाओ out;

	c = p_dev->function_config;

	release_io_space(s, &c->io[0]);

	अगर (c->io[1].end)
		release_io_space(s, &c->io[1]);

	p_dev->_io = 0;
	c->state &= ~CONFIG_IO_REQ;

out:
	mutex_unlock(&s->ops_mutex);

	वापस ret;
पूर्ण /* pcmcia_release_io */


/**
 * pcmcia_release_winकरोw() - release reserved iomem क्रम PCMCIA devices
 * @p_dev: pcmcia device
 * @res: iomem resource to release
 *
 * pcmcia_release_winकरोw() releases &काष्ठा resource *res which was
 * previously reserved by calling pcmcia_request_winकरोw().
 */
पूर्णांक pcmcia_release_winकरोw(काष्ठा pcmcia_device *p_dev, काष्ठा resource *res)
अणु
	काष्ठा pcmcia_socket *s = p_dev->socket;
	pccard_mem_map *win;
	अचिन्हित पूर्णांक w;

	dev_dbg(&p_dev->dev, "releasing window %pR\n", res);

	w = ((res->flags & IORESOURCE_BITS & WIN_FLAGS_REQ) >> 2) - 1;
	अगर (w >= MAX_WIN)
		वापस -EINVAL;

	mutex_lock(&s->ops_mutex);
	win = &s->win[w];

	अगर (!(p_dev->_win & CLIENT_WIN_REQ(w))) अणु
		dev_dbg(&p_dev->dev, "not releasing unknown window\n");
		mutex_unlock(&s->ops_mutex);
		वापस -EINVAL;
	पूर्ण

	/* Shut करोwn memory winकरोw */
	win->flags &= ~MAP_ACTIVE;
	s->ops->set_mem_map(s, win);
	s->state &= ~SOCKET_WIN_REQ(w);

	/* Release प्रणाली memory */
	अगर (win->res) अणु
		release_resource(res);
		release_resource(win->res);
		kमुक्त(win->res);
		win->res = शून्य;
	पूर्ण
	res->start = res->end = 0;
	res->flags = IORESOURCE_MEM;
	p_dev->_win &= ~CLIENT_WIN_REQ(w);
	mutex_unlock(&s->ops_mutex);

	वापस 0;
पूर्ण /* pcmcia_release_winकरोw */
EXPORT_SYMBOL(pcmcia_release_winकरोw);


/**
 * pcmcia_enable_device() - set up and activate a PCMCIA device
 * @p_dev: the associated PCMCIA device
 *
 * pcmcia_enable_device() physically enables a PCMCIA device. It parses
 * the flags passed to in @flags and stored in @p_dev->flags and sets up
 * the Vpp voltage, enables the speaker line, I/O ports and store proper
 * values to configuration रेजिस्टरs.
 */
पूर्णांक pcmcia_enable_device(काष्ठा pcmcia_device *p_dev)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक base;
	काष्ठा pcmcia_socket *s = p_dev->socket;
	config_t *c;
	pccard_io_map iomap;
	अचिन्हित अक्षर status = 0;
	अचिन्हित अक्षर ext_status = 0;
	अचिन्हित अक्षर option = 0;
	अचिन्हित पूर्णांक flags = p_dev->config_flags;

	अगर (!(s->state & SOCKET_PRESENT))
		वापस -ENODEV;

	mutex_lock(&s->ops_mutex);
	c = p_dev->function_config;
	अगर (c->state & CONFIG_LOCKED) अणु
		mutex_unlock(&s->ops_mutex);
		dev_dbg(&p_dev->dev, "Configuration is locked\n");
		वापस -EACCES;
	पूर्ण

	/* Do घातer control.  We करोn't allow changes in Vcc. */
	s->socket.Vpp = p_dev->vpp;
	अगर (s->ops->set_socket(s, &s->socket)) अणु
		mutex_unlock(&s->ops_mutex);
		dev_warn(&p_dev->dev, "Unable to set socket state\n");
		वापस -EINVAL;
	पूर्ण

	/* Pick memory or I/O card, DMA mode, पूर्णांकerrupt */
	अगर (p_dev->_io || flags & CONF_ENABLE_IRQ)
		flags |= CONF_ENABLE_IOCARD;
	अगर (flags & CONF_ENABLE_IOCARD)
		s->socket.flags |= SS_IOCARD;
	अगर (flags & CONF_ENABLE_ZVCARD)
		s->socket.flags |= SS_ZVCARD | SS_IOCARD;
	अगर (flags & CONF_ENABLE_SPKR) अणु
		s->socket.flags |= SS_SPKR_ENA;
		status = CCSR_AUDIO_ENA;
		अगर (!(p_dev->config_regs & PRESENT_STATUS))
			dev_warn(&p_dev->dev, "speaker requested, but "
					      "PRESENT_STATUS not set!\n");
	पूर्ण
	अगर (flags & CONF_ENABLE_IRQ)
		s->socket.io_irq = s->pcmcia_irq;
	अन्यथा
		s->socket.io_irq = 0;
	अगर (flags & CONF_ENABLE_ESR) अणु
		p_dev->config_regs |= PRESENT_EXT_STATUS;
		ext_status = ESR_REQ_ATTN_ENA;
	पूर्ण
	s->ops->set_socket(s, &s->socket);
	s->lock_count++;

	dev_dbg(&p_dev->dev,
		"enable_device: V %d, flags %x, base %x, regs %x, idx %x\n",
		p_dev->vpp, flags, p_dev->config_base, p_dev->config_regs,
		p_dev->config_index);

	/* Set up CIS configuration रेजिस्टरs */
	base = p_dev->config_base;
	अगर (p_dev->config_regs & PRESENT_COPY) अणु
		u16 पंचांगp = 0;
		dev_dbg(&p_dev->dev, "clearing CISREG_SCR\n");
		pcmcia_ग_लिखो_cis_mem(s, 1, (base + CISREG_SCR)>>1, 1, &पंचांगp);
	पूर्ण
	अगर (p_dev->config_regs & PRESENT_PIN_REPLACE) अणु
		u16 पंचांगp = 0;
		dev_dbg(&p_dev->dev, "clearing CISREG_PRR\n");
		pcmcia_ग_लिखो_cis_mem(s, 1, (base + CISREG_PRR)>>1, 1, &पंचांगp);
	पूर्ण
	अगर (p_dev->config_regs & PRESENT_OPTION) अणु
		अगर (s->functions == 1) अणु
			option = p_dev->config_index & COR_CONFIG_MASK;
		पूर्ण अन्यथा अणु
			option = p_dev->config_index & COR_MFC_CONFIG_MASK;
			option |= COR_FUNC_ENA|COR_IREQ_ENA;
			अगर (p_dev->config_regs & PRESENT_IOBASE_0)
				option |= COR_ADDR_DECODE;
		पूर्ण
		अगर ((flags & CONF_ENABLE_IRQ) &&
			!(flags & CONF_ENABLE_PULSE_IRQ))
			option |= COR_LEVEL_REQ;
		pcmcia_ग_लिखो_cis_mem(s, 1, (base + CISREG_COR)>>1, 1, &option);
		msleep(40);
	पूर्ण
	अगर (p_dev->config_regs & PRESENT_STATUS)
		pcmcia_ग_लिखो_cis_mem(s, 1, (base + CISREG_CCSR)>>1, 1, &status);

	अगर (p_dev->config_regs & PRESENT_EXT_STATUS)
		pcmcia_ग_लिखो_cis_mem(s, 1, (base + CISREG_ESR)>>1, 1,
					&ext_status);

	अगर (p_dev->config_regs & PRESENT_IOBASE_0) अणु
		u8 b = c->io[0].start & 0xff;
		pcmcia_ग_लिखो_cis_mem(s, 1, (base + CISREG_IOBASE_0)>>1, 1, &b);
		b = (c->io[0].start >> 8) & 0xff;
		pcmcia_ग_लिखो_cis_mem(s, 1, (base + CISREG_IOBASE_1)>>1, 1, &b);
	पूर्ण
	अगर (p_dev->config_regs & PRESENT_IOSIZE) अणु
		u8 b = resource_size(&c->io[0]) + resource_size(&c->io[1]) - 1;
		pcmcia_ग_लिखो_cis_mem(s, 1, (base + CISREG_IOSIZE)>>1, 1, &b);
	पूर्ण

	/* Configure I/O winकरोws */
	अगर (c->state & CONFIG_IO_REQ) अणु
		iomap.speed = io_speed;
		क्रम (i = 0; i < MAX_IO_WIN; i++)
			अगर (s->io[i].res) अणु
				iomap.map = i;
				iomap.flags = MAP_ACTIVE;
				चयन (s->io[i].res->flags & IO_DATA_PATH_WIDTH) अणु
				हाल IO_DATA_PATH_WIDTH_16:
					iomap.flags |= MAP_16BIT; अवरोध;
				हाल IO_DATA_PATH_WIDTH_AUTO:
					iomap.flags |= MAP_AUTOSZ; अवरोध;
				शेष:
					अवरोध;
				पूर्ण
				iomap.start = s->io[i].res->start;
				iomap.stop = s->io[i].res->end;
				s->ops->set_io_map(s, &iomap);
				s->io[i].Config++;
			पूर्ण
	पूर्ण

	c->state |= CONFIG_LOCKED;
	p_dev->_locked = 1;
	mutex_unlock(&s->ops_mutex);
	वापस 0;
पूर्ण /* pcmcia_enable_device */
EXPORT_SYMBOL(pcmcia_enable_device);


/**
 * pcmcia_request_io() - attempt to reserve port ranges क्रम PCMCIA devices
 * @p_dev: the associated PCMCIA device
 *
 * pcmcia_request_io() attempts to reserve the IO port ranges specअगरied in
 * &काष्ठा pcmcia_device @p_dev->resource[0] and @p_dev->resource[1]. The
 * "start" value is the requested start of the IO port resource; "end"
 * reflects the number of ports requested. The number of IO lines requested
 * is specअगरied in &काष्ठा pcmcia_device @p_dev->io_lines.
 */
पूर्णांक pcmcia_request_io(काष्ठा pcmcia_device *p_dev)
अणु
	काष्ठा pcmcia_socket *s = p_dev->socket;
	config_t *c = p_dev->function_config;
	पूर्णांक ret = -EINVAL;

	mutex_lock(&s->ops_mutex);
	dev_dbg(&p_dev->dev, "pcmcia_request_io: %pR , %pR",
		&c->io[0], &c->io[1]);

	अगर (!(s->state & SOCKET_PRESENT)) अणु
		dev_dbg(&p_dev->dev, "pcmcia_request_io: No card present\n");
		जाओ out;
	पूर्ण

	अगर (c->state & CONFIG_LOCKED) अणु
		dev_dbg(&p_dev->dev, "Configuration is locked\n");
		जाओ out;
	पूर्ण
	अगर (c->state & CONFIG_IO_REQ) अणु
		dev_dbg(&p_dev->dev, "IO already configured\n");
		जाओ out;
	पूर्ण

	ret = alloc_io_space(s, &c->io[0], p_dev->io_lines);
	अगर (ret)
		जाओ out;

	अगर (c->io[1].end) अणु
		ret = alloc_io_space(s, &c->io[1], p_dev->io_lines);
		अगर (ret) अणु
			काष्ठा resource पंचांगp = c->io[0];
			/* release the previously allocated resource */
			release_io_space(s, &c->io[0]);
			/* but preserve the settings, क्रम they worked... */
			c->io[0].end = resource_size(&पंचांगp);
			c->io[0].start = पंचांगp.start;
			c->io[0].flags = पंचांगp.flags;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा
		c->io[1].start = 0;

	c->state |= CONFIG_IO_REQ;
	p_dev->_io = 1;

	dev_dbg(&p_dev->dev, "pcmcia_request_io succeeded: %pR , %pR",
		&c->io[0], &c->io[1]);
out:
	mutex_unlock(&s->ops_mutex);

	वापस ret;
पूर्ण /* pcmcia_request_io */
EXPORT_SYMBOL(pcmcia_request_io);


/**
 * pcmcia_request_irq() - attempt to request a IRQ क्रम a PCMCIA device
 * @p_dev: the associated PCMCIA device
 * @handler: IRQ handler to रेजिस्टर
 *
 * pcmcia_request_irq() is a wrapper around request_irq() which allows
 * the PCMCIA core to clean up the registration in pcmcia_disable_device().
 * Drivers are मुक्त to use request_irq() directly, but then they need to
 * call मुक्त_irq() themselfves, too. Also, only %IRQF_SHARED capable IRQ
 * handlers are allowed.
 */
पूर्णांक __must_check pcmcia_request_irq(काष्ठा pcmcia_device *p_dev,
				    irq_handler_t handler)
अणु
	पूर्णांक ret;

	अगर (!p_dev->irq)
		वापस -EINVAL;

	ret = request_irq(p_dev->irq, handler, IRQF_SHARED,
			p_dev->devname, p_dev->priv);
	अगर (!ret)
		p_dev->_irq = 1;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(pcmcia_request_irq);


#अगर_घोषित CONFIG_PCMCIA_PROBE

/* mask of IRQs alपढ़ोy reserved by other cards, we should aव्योम using them */
अटल u8 pcmcia_used_irq[32];

अटल irqवापस_t test_action(पूर्णांक cpl, व्योम *dev_id)
अणु
	वापस IRQ_NONE;
पूर्ण

/**
 * pcmcia_setup_isa_irq() - determine whether an ISA IRQ can be used
 * @p_dev: the associated PCMCIA device
 * @type:  IRQ type (flags)
 *
 * locking note: must be called with ops_mutex locked.
 */
अटल पूर्णांक pcmcia_setup_isa_irq(काष्ठा pcmcia_device *p_dev, पूर्णांक type)
अणु
	काष्ठा pcmcia_socket *s = p_dev->socket;
	अचिन्हित पूर्णांक try, irq;
	u32 mask = s->irq_mask;
	पूर्णांक ret = -ENODEV;

	क्रम (try = 0; try < 64; try++) अणु
		irq = try % 32;

		अगर (irq > NR_IRQS)
			जारी;

		/* marked as available by driver, not blocked by userspace? */
		अगर (!((mask >> irq) & 1))
			जारी;

		/* aव्योम an IRQ which is alपढ़ोy used by another PCMCIA card */
		अगर ((try < 32) && pcmcia_used_irq[irq])
			जारी;

		/* रेजिस्टर the correct driver, अगर possible, to check whether
		 * रेजिस्टरing a dummy handle works, i.e. अगर the IRQ isn't
		 * marked as used by the kernel resource management core */
		ret = request_irq(irq, test_action, type, p_dev->devname,
				  p_dev);
		अगर (!ret) अणु
			मुक्त_irq(irq, p_dev);
			p_dev->irq = s->pcmcia_irq = irq;
			pcmcia_used_irq[irq]++;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

व्योम pcmcia_cleanup_irq(काष्ठा pcmcia_socket *s)
अणु
	pcmcia_used_irq[s->pcmcia_irq]--;
	s->pcmcia_irq = 0;
पूर्ण

#अन्यथा /* CONFIG_PCMCIA_PROBE */

अटल पूर्णांक pcmcia_setup_isa_irq(काष्ठा pcmcia_device *p_dev, पूर्णांक type)
अणु
	वापस -EINVAL;
पूर्ण

व्योम pcmcia_cleanup_irq(काष्ठा pcmcia_socket *s)
अणु
	s->pcmcia_irq = 0;
	वापस;
पूर्ण

#पूर्ण_अगर  /* CONFIG_PCMCIA_PROBE */


/**
 * pcmcia_setup_irq() - determine IRQ to be used क्रम device
 * @p_dev: the associated PCMCIA device
 *
 * locking note: must be called with ops_mutex locked.
 */
पूर्णांक pcmcia_setup_irq(काष्ठा pcmcia_device *p_dev)
अणु
	काष्ठा pcmcia_socket *s = p_dev->socket;

	अगर (p_dev->irq)
		वापस 0;

	/* alपढ़ोy asचिन्हित? */
	अगर (s->pcmcia_irq) अणु
		p_dev->irq = s->pcmcia_irq;
		वापस 0;
	पूर्ण

	/* prefer an exclusive ISA irq */
	अगर (!pcmcia_setup_isa_irq(p_dev, 0))
		वापस 0;

	/* but accept a shared ISA irq */
	अगर (!pcmcia_setup_isa_irq(p_dev, IRQF_SHARED))
		वापस 0;

	/* but use the PCI irq otherwise */
	अगर (s->pci_irq) अणु
		p_dev->irq = s->pcmcia_irq = s->pci_irq;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण


/**
 * pcmcia_request_winकरोw() - attempt to reserve iomem क्रम PCMCIA devices
 * @p_dev: the associated PCMCIA device
 * @res: &काष्ठा resource poपूर्णांकing to p_dev->resource[2..5]
 * @speed: access speed
 *
 * pcmcia_request_winकरोw() attepts to reserve an iomem ranges specअगरied in
 * &काष्ठा resource @res poपूर्णांकing to one of the entries in
 * &काष्ठा pcmcia_device @p_dev->resource[2..5]. The "start" value is the
 * requested start of the IO mem resource; "end" reflects the size
 * requested.
 */
पूर्णांक pcmcia_request_winकरोw(काष्ठा pcmcia_device *p_dev, काष्ठा resource *res,
			अचिन्हित पूर्णांक speed)
अणु
	काष्ठा pcmcia_socket *s = p_dev->socket;
	pccard_mem_map *win;
	u_दीर्घ align;
	पूर्णांक w;

	dev_dbg(&p_dev->dev, "request_window %pR %d\n", res, speed);

	अगर (!(s->state & SOCKET_PRESENT)) अणु
		dev_dbg(&p_dev->dev, "No card present\n");
		वापस -ENODEV;
	पूर्ण

	/* Winकरोw size शेषs to smallest available */
	अगर (res->end == 0)
		res->end = s->map_size;
	align = (s->features & SS_CAP_MEM_ALIGN) ? res->end : s->map_size;
	अगर (res->end & (s->map_size-1)) अणु
		dev_dbg(&p_dev->dev, "invalid map size\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((res->start && (s->features & SS_CAP_STATIC_MAP)) ||
	    (res->start & (align-1))) अणु
		dev_dbg(&p_dev->dev, "invalid base address\n");
		वापस -EINVAL;
	पूर्ण
	अगर (res->start)
		align = 0;

	/* Allocate प्रणाली memory winकरोw */
	mutex_lock(&s->ops_mutex);
	क्रम (w = 0; w < MAX_WIN; w++)
		अगर (!(s->state & SOCKET_WIN_REQ(w)))
			अवरोध;
	अगर (w == MAX_WIN) अणु
		dev_dbg(&p_dev->dev, "all windows are used already\n");
		mutex_unlock(&s->ops_mutex);
		वापस -EINVAL;
	पूर्ण

	win = &s->win[w];

	अगर (!(s->features & SS_CAP_STATIC_MAP)) अणु
		win->res = pcmcia_find_mem_region(res->start, res->end, align,
						0, s);
		अगर (!win->res) अणु
			dev_dbg(&p_dev->dev, "allocating mem region failed\n");
			mutex_unlock(&s->ops_mutex);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	p_dev->_win |= CLIENT_WIN_REQ(w);

	/* Configure the socket controller */
	win->map = w+1;
	win->flags = res->flags & WIN_FLAGS_MAP;
	win->speed = speed;
	win->card_start = 0;

	अगर (s->ops->set_mem_map(s, win) != 0) अणु
		dev_dbg(&p_dev->dev, "failed to set memory mapping\n");
		mutex_unlock(&s->ops_mutex);
		वापस -EIO;
	पूर्ण
	s->state |= SOCKET_WIN_REQ(w);

	/* Return winकरोw handle */
	अगर (s->features & SS_CAP_STATIC_MAP)
		res->start = win->अटल_start;
	अन्यथा
		res->start = win->res->start;

	/* convert to new-style resources */
	res->end += res->start - 1;
	res->flags &= ~WIN_FLAGS_REQ;
	res->flags |= (win->map << 2) | IORESOURCE_MEM;
	res->parent = win->res;
	अगर (win->res)
		request_resource(&iomem_resource, res);

	dev_dbg(&p_dev->dev, "request_window results in %pR\n", res);

	mutex_unlock(&s->ops_mutex);

	वापस 0;
पूर्ण /* pcmcia_request_winकरोw */
EXPORT_SYMBOL(pcmcia_request_winकरोw);


/**
 * pcmcia_disable_device() - disable and clean up a PCMCIA device
 * @p_dev: the associated PCMCIA device
 *
 * pcmcia_disable_device() is the driver-callable counterpart to
 * pcmcia_enable_device(): If a PCMCIA device is no दीर्घer used,
 * drivers are expected to clean up and disable the device by calling
 * this function. Any I/O ranges (iomem and ioports) will be released,
 * the Vpp voltage will be set to 0, and IRQs will no दीर्घer be
 * generated -- at least अगर there is no other card function (of
 * multअगरunction devices) being used.
 */
व्योम pcmcia_disable_device(काष्ठा pcmcia_device *p_dev)
अणु
	पूर्णांक i;

	dev_dbg(&p_dev->dev, "disabling device\n");

	क्रम (i = 0; i < MAX_WIN; i++) अणु
		काष्ठा resource *res = p_dev->resource[MAX_IO_WIN + i];
		अगर (res->flags & WIN_FLAGS_REQ)
			pcmcia_release_winकरोw(p_dev, res);
	पूर्ण

	pcmcia_release_configuration(p_dev);
	pcmcia_release_io(p_dev);
	अगर (p_dev->_irq) अणु
		मुक्त_irq(p_dev->irq, p_dev->priv);
		p_dev->_irq = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(pcmcia_disable_device);
