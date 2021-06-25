<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HD-audio controller helpers
 */

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/hdaudपन.स>
#समावेश <sound/hda_रेजिस्टर.h>
#समावेश "local.h"

/* clear CORB पढ़ो poपूर्णांकer properly */
अटल व्योम azx_clear_corbrp(काष्ठा hdac_bus *bus)
अणु
	पूर्णांक समयout;

	क्रम (समयout = 1000; समयout > 0; समयout--) अणु
		अगर (snd_hdac_chip_पढ़ोw(bus, CORBRP) & AZX_CORBRP_RST)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (समयout <= 0)
		dev_err(bus->dev, "CORB reset timeout#1, CORBRP = %d\n",
			snd_hdac_chip_पढ़ोw(bus, CORBRP));

	snd_hdac_chip_ग_लिखोw(bus, CORBRP, 0);
	क्रम (समयout = 1000; समयout > 0; समयout--) अणु
		अगर (snd_hdac_chip_पढ़ोw(bus, CORBRP) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (समयout <= 0)
		dev_err(bus->dev, "CORB reset timeout#2, CORBRP = %d\n",
			snd_hdac_chip_पढ़ोw(bus, CORBRP));
पूर्ण

/**
 * snd_hdac_bus_init_cmd_io - set up CORB/RIRB buffers
 * @bus: HD-audio core bus
 */
व्योम snd_hdac_bus_init_cmd_io(काष्ठा hdac_bus *bus)
अणु
	WARN_ON_ONCE(!bus->rb.area);

	spin_lock_irq(&bus->reg_lock);
	/* CORB set up */
	bus->corb.addr = bus->rb.addr;
	bus->corb.buf = (__le32 *)bus->rb.area;
	snd_hdac_chip_ग_लिखोl(bus, CORBLBASE, (u32)bus->corb.addr);
	snd_hdac_chip_ग_लिखोl(bus, CORBUBASE, upper_32_bits(bus->corb.addr));

	/* set the corb size to 256 entries (ULI requires explicitly) */
	snd_hdac_chip_ग_लिखोb(bus, CORBSIZE, 0x02);
	/* set the corb ग_लिखो poपूर्णांकer to 0 */
	snd_hdac_chip_ग_लिखोw(bus, CORBWP, 0);

	/* reset the corb hw पढ़ो poपूर्णांकer */
	snd_hdac_chip_ग_लिखोw(bus, CORBRP, AZX_CORBRP_RST);
	अगर (!bus->corbrp_self_clear)
		azx_clear_corbrp(bus);

	/* enable corb dma */
	snd_hdac_chip_ग_लिखोb(bus, CORBCTL, AZX_CORBCTL_RUN);

	/* RIRB set up */
	bus->rirb.addr = bus->rb.addr + 2048;
	bus->rirb.buf = (__le32 *)(bus->rb.area + 2048);
	bus->rirb.wp = bus->rirb.rp = 0;
	स_रखो(bus->rirb.cmds, 0, माप(bus->rirb.cmds));
	snd_hdac_chip_ग_लिखोl(bus, RIRBLBASE, (u32)bus->rirb.addr);
	snd_hdac_chip_ग_लिखोl(bus, RIRBUBASE, upper_32_bits(bus->rirb.addr));

	/* set the rirb size to 256 entries (ULI requires explicitly) */
	snd_hdac_chip_ग_लिखोb(bus, RIRBSIZE, 0x02);
	/* reset the rirb hw ग_लिखो poपूर्णांकer */
	snd_hdac_chip_ग_लिखोw(bus, RIRBWP, AZX_RIRBWP_RST);
	/* set N=1, get RIRB response पूर्णांकerrupt क्रम new entry */
	snd_hdac_chip_ग_लिखोw(bus, RINTCNT, 1);
	/* enable rirb dma and response irq */
	snd_hdac_chip_ग_लिखोb(bus, RIRBCTL, AZX_RBCTL_DMA_EN | AZX_RBCTL_IRQ_EN);
	/* Accept unsolicited responses */
	snd_hdac_chip_updatel(bus, GCTL, AZX_GCTL_UNSOL, AZX_GCTL_UNSOL);
	spin_unlock_irq(&bus->reg_lock);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_init_cmd_io);

/* रुको क्रम cmd dmas till they are stopped */
अटल व्योम hdac_रुको_क्रम_cmd_dmas(काष्ठा hdac_bus *bus)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(100);
	जबतक ((snd_hdac_chip_पढ़ोb(bus, RIRBCTL) & AZX_RBCTL_DMA_EN)
		&& समय_beक्रमe(jअगरfies, समयout))
		udelay(10);

	समयout = jअगरfies + msecs_to_jअगरfies(100);
	जबतक ((snd_hdac_chip_पढ़ोb(bus, CORBCTL) & AZX_CORBCTL_RUN)
		&& समय_beक्रमe(jअगरfies, समयout))
		udelay(10);
पूर्ण

/**
 * snd_hdac_bus_stop_cmd_io - clean up CORB/RIRB buffers
 * @bus: HD-audio core bus
 */
व्योम snd_hdac_bus_stop_cmd_io(काष्ठा hdac_bus *bus)
अणु
	spin_lock_irq(&bus->reg_lock);
	/* disable ringbuffer DMAs */
	snd_hdac_chip_ग_लिखोb(bus, RIRBCTL, 0);
	snd_hdac_chip_ग_लिखोb(bus, CORBCTL, 0);
	spin_unlock_irq(&bus->reg_lock);

	hdac_रुको_क्रम_cmd_dmas(bus);

	spin_lock_irq(&bus->reg_lock);
	/* disable unsolicited responses */
	snd_hdac_chip_updatel(bus, GCTL, AZX_GCTL_UNSOL, 0);
	spin_unlock_irq(&bus->reg_lock);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_stop_cmd_io);

अटल अचिन्हित पूर्णांक azx_command_addr(u32 cmd)
अणु
	अचिन्हित पूर्णांक addr = cmd >> 28;

	अगर (snd_BUG_ON(addr >= HDA_MAX_CODECS))
		addr = 0;
	वापस addr;
पूर्ण

/**
 * snd_hdac_bus_send_cmd - send a command verb via CORB
 * @bus: HD-audio core bus
 * @val: encoded verb value to send
 *
 * Returns zero क्रम success or a negative error code.
 */
पूर्णांक snd_hdac_bus_send_cmd(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक addr = azx_command_addr(val);
	अचिन्हित पूर्णांक wp, rp;

	spin_lock_irq(&bus->reg_lock);

	bus->last_cmd[azx_command_addr(val)] = val;

	/* add command to corb */
	wp = snd_hdac_chip_पढ़ोw(bus, CORBWP);
	अगर (wp == 0xffff) अणु
		/* something wrong, controller likely turned to D3 */
		spin_unlock_irq(&bus->reg_lock);
		वापस -EIO;
	पूर्ण
	wp++;
	wp %= AZX_MAX_CORB_ENTRIES;

	rp = snd_hdac_chip_पढ़ोw(bus, CORBRP);
	अगर (wp == rp) अणु
		/* oops, it's full */
		spin_unlock_irq(&bus->reg_lock);
		वापस -EAGAIN;
	पूर्ण

	bus->rirb.cmds[addr]++;
	bus->corb.buf[wp] = cpu_to_le32(val);
	snd_hdac_chip_ग_लिखोw(bus, CORBWP, wp);

	spin_unlock_irq(&bus->reg_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_send_cmd);

#घोषणा AZX_RIRB_EX_UNSOL_EV	(1<<4)

/**
 * snd_hdac_bus_update_rirb - retrieve RIRB entries
 * @bus: HD-audio core bus
 *
 * Usually called from पूर्णांकerrupt handler.
 * The caller needs bus->reg_lock spinlock beक्रमe calling this.
 */
व्योम snd_hdac_bus_update_rirb(काष्ठा hdac_bus *bus)
अणु
	अचिन्हित पूर्णांक rp, wp;
	अचिन्हित पूर्णांक addr;
	u32 res, res_ex;

	wp = snd_hdac_chip_पढ़ोw(bus, RIRBWP);
	अगर (wp == 0xffff) अणु
		/* something wrong, controller likely turned to D3 */
		वापस;
	पूर्ण

	अगर (wp == bus->rirb.wp)
		वापस;
	bus->rirb.wp = wp;

	जबतक (bus->rirb.rp != wp) अणु
		bus->rirb.rp++;
		bus->rirb.rp %= AZX_MAX_RIRB_ENTRIES;

		rp = bus->rirb.rp << 1; /* an RIRB entry is 8-bytes */
		res_ex = le32_to_cpu(bus->rirb.buf[rp + 1]);
		res = le32_to_cpu(bus->rirb.buf[rp]);
		addr = res_ex & 0xf;
		अगर (addr >= HDA_MAX_CODECS) अणु
			dev_err(bus->dev,
				"spurious response %#x:%#x, rp = %d, wp = %d",
				res, res_ex, bus->rirb.rp, wp);
			snd_BUG();
		पूर्ण अन्यथा अगर (res_ex & AZX_RIRB_EX_UNSOL_EV)
			snd_hdac_bus_queue_event(bus, res, res_ex);
		अन्यथा अगर (bus->rirb.cmds[addr]) अणु
			bus->rirb.res[addr] = res;
			bus->rirb.cmds[addr]--;
			अगर (!bus->rirb.cmds[addr] &&
			    रुकोqueue_active(&bus->rirb_wq))
				wake_up(&bus->rirb_wq);
		पूर्ण अन्यथा अणु
			dev_err_ratelimited(bus->dev,
				"spurious response %#x:%#x, last cmd=%#08x\n",
				res, res_ex, bus->last_cmd[addr]);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_update_rirb);

/**
 * snd_hdac_bus_get_response - receive a response via RIRB
 * @bus: HD-audio core bus
 * @addr: codec address
 * @res: poपूर्णांकer to store the value, शून्य when not needed
 *
 * Returns zero अगर a value is पढ़ो, or a negative error code.
 */
पूर्णांक snd_hdac_bus_get_response(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक addr,
			      अचिन्हित पूर्णांक *res)
अणु
	अचिन्हित दीर्घ समयout;
	अचिन्हित दीर्घ loopcounter;
	रुको_queue_entry_t रुको;
	bool warned = false;

	init_रुको_entry(&रुको, 0);
	समयout = jअगरfies + msecs_to_jअगरfies(1000);

	क्रम (loopcounter = 0;; loopcounter++) अणु
		spin_lock_irq(&bus->reg_lock);
		अगर (!bus->polling_mode)
			prepare_to_रुको(&bus->rirb_wq, &रुको,
					TASK_UNINTERRUPTIBLE);
		अगर (bus->polling_mode)
			snd_hdac_bus_update_rirb(bus);
		अगर (!bus->rirb.cmds[addr]) अणु
			अगर (res)
				*res = bus->rirb.res[addr]; /* the last value */
			अगर (!bus->polling_mode)
				finish_रुको(&bus->rirb_wq, &रुको);
			spin_unlock_irq(&bus->reg_lock);
			वापस 0;
		पूर्ण
		spin_unlock_irq(&bus->reg_lock);
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;
#घोषणा LOOP_COUNT_MAX	3000
		अगर (!bus->polling_mode) अणु
			schedule_समयout(msecs_to_jअगरfies(2));
		पूर्ण अन्यथा अगर (bus->needs_damn_दीर्घ_delay ||
			   loopcounter > LOOP_COUNT_MAX) अणु
			अगर (loopcounter > LOOP_COUNT_MAX && !warned) अणु
				dev_dbg_ratelimited(bus->dev,
						    "too slow response, last cmd=%#08x\n",
						    bus->last_cmd[addr]);
				warned = true;
			पूर्ण
			msleep(2); /* temporary workaround */
		पूर्ण अन्यथा अणु
			udelay(10);
			cond_resched();
		पूर्ण
	पूर्ण

	अगर (!bus->polling_mode)
		finish_रुको(&bus->rirb_wq, &रुको);

	वापस -EIO;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_get_response);

#घोषणा HDAC_MAX_CAPS 10
/**
 * snd_hdac_bus_parse_capabilities - parse capability काष्ठाure
 * @bus: the poपूर्णांकer to bus object
 *
 * Returns 0 अगर successful, or a negative error code.
 */
पूर्णांक snd_hdac_bus_parse_capabilities(काष्ठा hdac_bus *bus)
अणु
	अचिन्हित पूर्णांक cur_cap;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक counter = 0;

	offset = snd_hdac_chip_पढ़ोw(bus, LLCH);

	/* Lets walk the linked capabilities list */
	करो अणु
		cur_cap = _snd_hdac_chip_पढ़ोl(bus, offset);

		dev_dbg(bus->dev, "Capability version: 0x%x\n",
			(cur_cap & AZX_CAP_HDR_VER_MASK) >> AZX_CAP_HDR_VER_OFF);

		dev_dbg(bus->dev, "HDA capability ID: 0x%x\n",
			(cur_cap & AZX_CAP_HDR_ID_MASK) >> AZX_CAP_HDR_ID_OFF);

		अगर (cur_cap == -1) अणु
			dev_dbg(bus->dev, "Invalid capability reg read\n");
			अवरोध;
		पूर्ण

		चयन ((cur_cap & AZX_CAP_HDR_ID_MASK) >> AZX_CAP_HDR_ID_OFF) अणु
		हाल AZX_ML_CAP_ID:
			dev_dbg(bus->dev, "Found ML capability\n");
			bus->mlcap = bus->remap_addr + offset;
			अवरोध;

		हाल AZX_GTS_CAP_ID:
			dev_dbg(bus->dev, "Found GTS capability offset=%x\n", offset);
			bus->gtscap = bus->remap_addr + offset;
			अवरोध;

		हाल AZX_PP_CAP_ID:
			/* PP capability found, the Audio DSP is present */
			dev_dbg(bus->dev, "Found PP capability offset=%x\n", offset);
			bus->ppcap = bus->remap_addr + offset;
			अवरोध;

		हाल AZX_SPB_CAP_ID:
			/* SPIB capability found, handler function */
			dev_dbg(bus->dev, "Found SPB capability\n");
			bus->spbcap = bus->remap_addr + offset;
			अवरोध;

		हाल AZX_DRSM_CAP_ID:
			/* DMA resume  capability found, handler function */
			dev_dbg(bus->dev, "Found DRSM capability\n");
			bus->drsmcap = bus->remap_addr + offset;
			अवरोध;

		शेष:
			dev_err(bus->dev, "Unknown capability %d\n", cur_cap);
			cur_cap = 0;
			अवरोध;
		पूर्ण

		counter++;

		अगर (counter > HDAC_MAX_CAPS) अणु
			dev_err(bus->dev, "We exceeded HDAC capabilities!!!\n");
			अवरोध;
		पूर्ण

		/* पढ़ो the offset of next capability */
		offset = cur_cap & AZX_CAP_HDR_NXT_PTR_MASK;

	पूर्ण जबतक (offset);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_parse_capabilities);

/*
 * Lowlevel पूर्णांकerface
 */

/**
 * snd_hdac_bus_enter_link_reset - enter link reset
 * @bus: HD-audio core bus
 *
 * Enter to the link reset state.
 */
व्योम snd_hdac_bus_enter_link_reset(काष्ठा hdac_bus *bus)
अणु
	अचिन्हित दीर्घ समयout;

	/* reset controller */
	snd_hdac_chip_updatel(bus, GCTL, AZX_GCTL_RESET, 0);

	समयout = jअगरfies + msecs_to_jअगरfies(100);
	जबतक ((snd_hdac_chip_पढ़ोb(bus, GCTL) & AZX_GCTL_RESET) &&
	       समय_beक्रमe(jअगरfies, समयout))
		usleep_range(500, 1000);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_enter_link_reset);

/**
 * snd_hdac_bus_निकास_link_reset - निकास link reset
 * @bus: HD-audio core bus
 *
 * Exit from the link reset state.
 */
व्योम snd_hdac_bus_निकास_link_reset(काष्ठा hdac_bus *bus)
अणु
	अचिन्हित दीर्घ समयout;

	snd_hdac_chip_updateb(bus, GCTL, AZX_GCTL_RESET, AZX_GCTL_RESET);

	समयout = jअगरfies + msecs_to_jअगरfies(100);
	जबतक (!snd_hdac_chip_पढ़ोb(bus, GCTL) && समय_beक्रमe(jअगरfies, समयout))
		usleep_range(500, 1000);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_निकास_link_reset);

/* reset codec link */
पूर्णांक snd_hdac_bus_reset_link(काष्ठा hdac_bus *bus, bool full_reset)
अणु
	अगर (!full_reset)
		जाओ skip_reset;

	/* clear STATESTS */
	snd_hdac_chip_ग_लिखोw(bus, STATESTS, STATESTS_INT_MASK);

	/* reset controller */
	snd_hdac_bus_enter_link_reset(bus);

	/* delay क्रम >= 100us क्रम codec PLL to settle per spec
	 * Rev 0.9 section 5.5.1
	 */
	usleep_range(500, 1000);

	/* Bring controller out of reset */
	snd_hdac_bus_निकास_link_reset(bus);

	/* Brent Chartअक्रम said to रुको >= 540us क्रम codecs to initialize */
	usleep_range(1000, 1200);

 skip_reset:
	/* check to see अगर controller is पढ़ोy */
	अगर (!snd_hdac_chip_पढ़ोb(bus, GCTL)) अणु
		dev_dbg(bus->dev, "controller not ready!\n");
		वापस -EBUSY;
	पूर्ण

	/* detect codecs */
	अगर (!bus->codec_mask) अणु
		bus->codec_mask = snd_hdac_chip_पढ़ोw(bus, STATESTS);
		dev_dbg(bus->dev, "codec_mask = 0x%lx\n", bus->codec_mask);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_reset_link);

/* enable पूर्णांकerrupts */
अटल व्योम azx_पूर्णांक_enable(काष्ठा hdac_bus *bus)
अणु
	/* enable controller CIE and GIE */
	snd_hdac_chip_updatel(bus, INTCTL,
			      AZX_INT_CTRL_EN | AZX_INT_GLOBAL_EN,
			      AZX_INT_CTRL_EN | AZX_INT_GLOBAL_EN);
पूर्ण

/* disable पूर्णांकerrupts */
अटल व्योम azx_पूर्णांक_disable(काष्ठा hdac_bus *bus)
अणु
	काष्ठा hdac_stream *azx_dev;

	/* disable पूर्णांकerrupts in stream descriptor */
	list_क्रम_each_entry(azx_dev, &bus->stream_list, list)
		snd_hdac_stream_updateb(azx_dev, SD_CTL, SD_INT_MASK, 0);

	/* disable SIE क्रम all streams */
	snd_hdac_chip_ग_लिखोb(bus, INTCTL, 0);

	/* disable controller CIE and GIE */
	snd_hdac_chip_updatel(bus, INTCTL, AZX_INT_CTRL_EN | AZX_INT_GLOBAL_EN, 0);
पूर्ण

/* clear पूर्णांकerrupts */
अटल व्योम azx_पूर्णांक_clear(काष्ठा hdac_bus *bus)
अणु
	काष्ठा hdac_stream *azx_dev;

	/* clear stream status */
	list_क्रम_each_entry(azx_dev, &bus->stream_list, list)
		snd_hdac_stream_ग_लिखोb(azx_dev, SD_STS, SD_INT_MASK);

	/* clear STATESTS */
	snd_hdac_chip_ग_लिखोw(bus, STATESTS, STATESTS_INT_MASK);

	/* clear rirb status */
	snd_hdac_chip_ग_लिखोb(bus, RIRBSTS, RIRB_INT_MASK);

	/* clear पूर्णांक status */
	snd_hdac_chip_ग_लिखोl(bus, INTSTS, AZX_INT_CTRL_EN | AZX_INT_ALL_STREAM);
पूर्ण

/**
 * snd_hdac_bus_init_chip - reset and start the controller रेजिस्टरs
 * @bus: HD-audio core bus
 * @full_reset: Do full reset
 */
bool snd_hdac_bus_init_chip(काष्ठा hdac_bus *bus, bool full_reset)
अणु
	अगर (bus->chip_init)
		वापस false;

	/* reset controller */
	snd_hdac_bus_reset_link(bus, full_reset);

	/* clear पूर्णांकerrupts */
	azx_पूर्णांक_clear(bus);

	/* initialize the codec command I/O */
	snd_hdac_bus_init_cmd_io(bus);

	/* enable पूर्णांकerrupts after CORB/RIRB buffers are initialized above */
	azx_पूर्णांक_enable(bus);

	/* program the position buffer */
	अगर (bus->use_posbuf && bus->posbuf.addr) अणु
		snd_hdac_chip_ग_लिखोl(bus, DPLBASE, (u32)bus->posbuf.addr);
		snd_hdac_chip_ग_लिखोl(bus, DPUBASE, upper_32_bits(bus->posbuf.addr));
	पूर्ण

	bus->chip_init = true;

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_init_chip);

/**
 * snd_hdac_bus_stop_chip - disable the whole IRQ and I/Os
 * @bus: HD-audio core bus
 */
व्योम snd_hdac_bus_stop_chip(काष्ठा hdac_bus *bus)
अणु
	अगर (!bus->chip_init)
		वापस;

	/* disable पूर्णांकerrupts */
	azx_पूर्णांक_disable(bus);
	azx_पूर्णांक_clear(bus);

	/* disable CORB/RIRB */
	snd_hdac_bus_stop_cmd_io(bus);

	/* disable position buffer */
	अगर (bus->posbuf.addr) अणु
		snd_hdac_chip_ग_लिखोl(bus, DPLBASE, 0);
		snd_hdac_chip_ग_लिखोl(bus, DPUBASE, 0);
	पूर्ण

	bus->chip_init = false;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_stop_chip);

/**
 * snd_hdac_bus_handle_stream_irq - पूर्णांकerrupt handler क्रम streams
 * @bus: HD-audio core bus
 * @status: INTSTS रेजिस्टर value
 * @ack: callback to be called क्रम woken streams
 *
 * Returns the bits of handled streams, or zero अगर no stream is handled.
 */
पूर्णांक snd_hdac_bus_handle_stream_irq(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक status,
				    व्योम (*ack)(काष्ठा hdac_bus *,
						काष्ठा hdac_stream *))
अणु
	काष्ठा hdac_stream *azx_dev;
	u8 sd_status;
	पूर्णांक handled = 0;

	list_क्रम_each_entry(azx_dev, &bus->stream_list, list) अणु
		अगर (status & azx_dev->sd_पूर्णांक_sta_mask) अणु
			sd_status = snd_hdac_stream_पढ़ोb(azx_dev, SD_STS);
			snd_hdac_stream_ग_लिखोb(azx_dev, SD_STS, SD_INT_MASK);
			handled |= 1 << azx_dev->index;
			अगर (!azx_dev->substream || !azx_dev->running ||
			    !(sd_status & SD_INT_COMPLETE))
				जारी;
			अगर (ack)
				ack(bus, azx_dev);
		पूर्ण
	पूर्ण
	वापस handled;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_handle_stream_irq);

/**
 * snd_hdac_bus_alloc_stream_pages - allocate BDL and other buffers
 * @bus: HD-audio core bus
 *
 * Call this after assigning the all streams.
 * Returns zero क्रम success, or a negative error code.
 */
पूर्णांक snd_hdac_bus_alloc_stream_pages(काष्ठा hdac_bus *bus)
अणु
	काष्ठा hdac_stream *s;
	पूर्णांक num_streams = 0;
	पूर्णांक dma_type = bus->dma_type ? bus->dma_type : SNDRV_DMA_TYPE_DEV;
	पूर्णांक err;

	list_क्रम_each_entry(s, &bus->stream_list, list) अणु
		/* allocate memory क्रम the BDL क्रम each stream */
		err = snd_dma_alloc_pages(dma_type, bus->dev,
					  BDL_SIZE, &s->bdl);
		num_streams++;
		अगर (err < 0)
			वापस -ENOMEM;
	पूर्ण

	अगर (WARN_ON(!num_streams))
		वापस -EINVAL;
	/* allocate memory क्रम the position buffer */
	err = snd_dma_alloc_pages(dma_type, bus->dev,
				  num_streams * 8, &bus->posbuf);
	अगर (err < 0)
		वापस -ENOMEM;
	list_क्रम_each_entry(s, &bus->stream_list, list)
		s->posbuf = (__le32 *)(bus->posbuf.area + s->index * 8);

	/* single page (at least 4096 bytes) must suffice क्रम both ringbuffes */
	वापस snd_dma_alloc_pages(dma_type, bus->dev, PAGE_SIZE, &bus->rb);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_alloc_stream_pages);

/**
 * snd_hdac_bus_मुक्त_stream_pages - release BDL and other buffers
 * @bus: HD-audio core bus
 */
व्योम snd_hdac_bus_मुक्त_stream_pages(काष्ठा hdac_bus *bus)
अणु
	काष्ठा hdac_stream *s;

	list_क्रम_each_entry(s, &bus->stream_list, list) अणु
		अगर (s->bdl.area)
			snd_dma_मुक्त_pages(&s->bdl);
	पूर्ण

	अगर (bus->rb.area)
		snd_dma_मुक्त_pages(&bus->rb);
	अगर (bus->posbuf.area)
		snd_dma_मुक्त_pages(&bus->posbuf);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_मुक्त_stream_pages);

/**
 * snd_hdac_bus_link_घातer - घातer up/करोwn codec link
 * @codec: HD-audio device
 * @enable: whether to घातer-up the link
 */
व्योम snd_hdac_bus_link_घातer(काष्ठा hdac_device *codec, bool enable)
अणु
	अगर (enable)
		set_bit(codec->addr, &codec->bus->codec_घातered);
	अन्यथा
		clear_bit(codec->addr, &codec->bus->codec_घातered);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_bus_link_घातer);
