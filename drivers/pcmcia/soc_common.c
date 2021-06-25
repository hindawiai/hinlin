<शैली गुरु>
/*======================================================================

    Common support code क्रम the PCMCIA control functionality of
    पूर्णांकegrated SOCs like the SA-11x0 and PXA2xx microprocessors.

    The contents of this file are subject to the Mozilla Public
    License Version 1.1 (the "License"); you may not use this file
    except in compliance with the License. You may obtain a copy of
    the License at http://www.mozilla.org/MPL/

    Software distributed under the License is distributed on an "AS
    IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
    implied. See the License क्रम the specअगरic language governing
    rights and limitations under the License.

    The initial developer of the original code is John G. Dorsey
    <john+@cs.cmu.edu>.  Portions created by John G. Dorsey are
    Copyright (C) 1999 John G. Dorsey.  All Rights Reserved.

    Alternatively, the contents of this file may be used under the
    terms of the GNU Public License version 2 (the "GPL"), in which
    हाल the provisions of the GPL are applicable instead of the
    above.  If you wish to allow the use of your version of this file
    only under the terms of the GPL and not to allow others to use
    your version of this file under the MPL, indicate your decision
    by deleting the provisions above and replace them with the notice
    and other provisions required by the GPL.  If you करो not delete
    the provisions above, a recipient may use your version of this
    file under either the MPL or the GPL.

======================================================================*/


#समावेश <linux/cpufreq.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>

#समावेश <mach/hardware.h>

#समावेश "soc_common.h"

अटल irqवापस_t soc_common_pcmcia_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev);

#अगर_घोषित CONFIG_PCMCIA_DEBUG

अटल पूर्णांक pc_debug;
module_param(pc_debug, पूर्णांक, 0644);

व्योम soc_pcmcia_debug(काष्ठा soc_pcmcia_socket *skt, स्थिर अक्षर *func,
		      पूर्णांक lvl, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	अगर (pc_debug > lvl) अणु
		बहु_शुरू(args, fmt);

		vaf.fmt = fmt;
		vaf.va = &args;

		prपूर्णांकk(KERN_DEBUG "skt%u: %s: %pV", skt->nr, func, &vaf);

		बहु_पूर्ण(args);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(soc_pcmcia_debug);

#पूर्ण_अगर

#घोषणा to_soc_pcmcia_socket(x)	\
	container_of(x, काष्ठा soc_pcmcia_socket, socket)

पूर्णांक soc_pcmcia_regulator_set(काष्ठा soc_pcmcia_socket *skt,
	काष्ठा soc_pcmcia_regulator *r, पूर्णांक v)
अणु
	bool on;
	पूर्णांक ret;

	अगर (!r->reg)
		वापस 0;

	on = v != 0;
	अगर (r->on == on)
		वापस 0;

	अगर (on) अणु
		ret = regulator_set_voltage(r->reg, v * 100000, v * 100000);
		अगर (ret) अणु
			पूर्णांक vout = regulator_get_voltage(r->reg) / 100000;

			dev_warn(&skt->socket.dev,
				 "CS requested %s=%u.%uV, applying %u.%uV\n",
				 r == &skt->vcc ? "Vcc" : "Vpp",
				 v / 10, v % 10, vout / 10, vout % 10);
		पूर्ण

		ret = regulator_enable(r->reg);
	पूर्ण अन्यथा अणु
		ret = regulator_disable(r->reg);
	पूर्ण
	अगर (ret == 0)
		r->on = on;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(soc_pcmcia_regulator_set);

अटल अचिन्हित लघु
calc_speed(अचिन्हित लघु *spds, पूर्णांक num, अचिन्हित लघु dflt)
अणु
	अचिन्हित लघु speed = 0;
	पूर्णांक i;

	क्रम (i = 0; i < num; i++)
		अगर (speed < spds[i])
			speed = spds[i];
	अगर (speed == 0)
		speed = dflt;

	वापस speed;
पूर्ण

व्योम soc_common_pcmcia_get_timing(काष्ठा soc_pcmcia_socket *skt,
	काष्ठा soc_pcmcia_timing *timing)
अणु
	timing->io =
		calc_speed(skt->spd_io, MAX_IO_WIN, SOC_PCMCIA_IO_ACCESS);
	timing->mem =
		calc_speed(skt->spd_mem, MAX_WIN, SOC_PCMCIA_3V_MEM_ACCESS);
	timing->attr =
		calc_speed(skt->spd_attr, MAX_WIN, SOC_PCMCIA_3V_MEM_ACCESS);
पूर्ण
EXPORT_SYMBOL(soc_common_pcmcia_get_timing);

अटल व्योम __soc_pcmcia_hw_shutकरोwn(काष्ठा soc_pcmcia_socket *skt,
	अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nr; i++)
		अगर (skt->stat[i].irq)
			मुक्त_irq(skt->stat[i].irq, skt);

	अगर (skt->ops->hw_shutकरोwn)
		skt->ops->hw_shutकरोwn(skt);

	clk_disable_unprepare(skt->clk);
पूर्ण

अटल व्योम soc_pcmcia_hw_shutकरोwn(काष्ठा soc_pcmcia_socket *skt)
अणु
	__soc_pcmcia_hw_shutकरोwn(skt, ARRAY_SIZE(skt->stat));
पूर्ण

पूर्णांक soc_pcmcia_request_gpiods(काष्ठा soc_pcmcia_socket *skt)
अणु
	काष्ठा device *dev = skt->socket.dev.parent;
	काष्ठा gpio_desc *desc;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(skt->stat); i++) अणु
		अगर (!skt->stat[i].name)
			जारी;

		desc = devm_gpiod_get(dev, skt->stat[i].name, GPIOD_IN);
		अगर (IS_ERR(desc)) अणु
			dev_err(dev, "Failed to get GPIO for %s: %ld\n",
				skt->stat[i].name, PTR_ERR(desc));
			वापस PTR_ERR(desc);
		पूर्ण

		skt->stat[i].desc = desc;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(soc_pcmcia_request_gpiods);

अटल पूर्णांक soc_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	पूर्णांक ret = 0, i;

	ret = clk_prepare_enable(skt->clk);
	अगर (ret)
		वापस ret;

	अगर (skt->ops->hw_init) अणु
		ret = skt->ops->hw_init(skt);
		अगर (ret) अणु
			clk_disable_unprepare(skt->clk);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(skt->stat); i++) अणु
		अगर (gpio_is_valid(skt->stat[i].gpio)) अणु
			अचिन्हित दीर्घ flags = GPIOF_IN;

			/* CD is active low by शेष */
			अगर (i == SOC_STAT_CD)
				flags |= GPIOF_ACTIVE_LOW;

			ret = devm_gpio_request_one(skt->socket.dev.parent,
						    skt->stat[i].gpio, flags,
						    skt->stat[i].name);
			अगर (ret) अणु
				__soc_pcmcia_hw_shutकरोwn(skt, i);
				वापस ret;
			पूर्ण

			skt->stat[i].desc = gpio_to_desc(skt->stat[i].gpio);
		पूर्ण

		अगर (i < SOC_STAT_VS1 && skt->stat[i].desc) अणु
			पूर्णांक irq = gpiod_to_irq(skt->stat[i].desc);

			अगर (irq > 0) अणु
				अगर (i == SOC_STAT_RDY)
					skt->socket.pci_irq = irq;
				अन्यथा
					skt->stat[i].irq = irq;
			पूर्ण
		पूर्ण

		अगर (skt->stat[i].irq) अणु
			ret = request_irq(skt->stat[i].irq,
					  soc_common_pcmcia_पूर्णांकerrupt,
					  IRQF_TRIGGER_NONE,
					  skt->stat[i].name, skt);
			अगर (ret) अणु
				__soc_pcmcia_hw_shutकरोwn(skt, i);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम soc_pcmcia_hw_enable(काष्ठा soc_pcmcia_socket *skt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(skt->stat); i++)
		अगर (skt->stat[i].irq) अणु
			irq_set_irq_type(skt->stat[i].irq, IRQ_TYPE_EDGE_RISING);
			irq_set_irq_type(skt->stat[i].irq, IRQ_TYPE_EDGE_BOTH);
		पूर्ण
पूर्ण

अटल व्योम soc_pcmcia_hw_disable(काष्ठा soc_pcmcia_socket *skt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(skt->stat); i++)
		अगर (skt->stat[i].irq)
			irq_set_irq_type(skt->stat[i].irq, IRQ_TYPE_NONE);
पूर्ण

/*
 * The CF 3.0 specअगरication says that cards tie VS1 to ground and leave
 * VS2 खोलो.  Many implementations करो not wire up the VS संकेतs, so we
 * provide hard-coded values as per the CF 3.0 spec.
 */
व्योम soc_common_cf_socket_state(काष्ठा soc_pcmcia_socket *skt,
	काष्ठा pcmcia_state *state)
अणु
	state->vs_3v = 1;
पूर्ण
EXPORT_SYMBOL_GPL(soc_common_cf_socket_state);

अटल अचिन्हित पूर्णांक soc_common_pcmcia_skt_state(काष्ठा soc_pcmcia_socket *skt)
अणु
	काष्ठा pcmcia_state state;
	अचिन्हित पूर्णांक stat;

	स_रखो(&state, 0, माप(काष्ठा pcmcia_state));

	/* Make battery voltage state report 'good' */
	state.bvd1 = 1;
	state.bvd2 = 1;

	अगर (skt->stat[SOC_STAT_CD].desc)
		state.detect = !!gpiod_get_value(skt->stat[SOC_STAT_CD].desc);
	अगर (skt->stat[SOC_STAT_RDY].desc)
		state.पढ़ोy = !!gpiod_get_value(skt->stat[SOC_STAT_RDY].desc);
	अगर (skt->stat[SOC_STAT_BVD1].desc)
		state.bvd1 = !!gpiod_get_value(skt->stat[SOC_STAT_BVD1].desc);
	अगर (skt->stat[SOC_STAT_BVD2].desc)
		state.bvd2 = !!gpiod_get_value(skt->stat[SOC_STAT_BVD2].desc);
	अगर (skt->stat[SOC_STAT_VS1].desc)
		state.vs_3v = !!gpiod_get_value(skt->stat[SOC_STAT_VS1].desc);
	अगर (skt->stat[SOC_STAT_VS2].desc)
		state.vs_Xv = !!gpiod_get_value(skt->stat[SOC_STAT_VS2].desc);

	skt->ops->socket_state(skt, &state);

	stat = state.detect  ? SS_DETECT : 0;
	stat |= state.पढ़ोy  ? SS_READY  : 0;
	stat |= state.wrprot ? SS_WRPROT : 0;
	stat |= state.vs_3v  ? SS_3VCARD : 0;
	stat |= state.vs_Xv  ? SS_XVCARD : 0;

	/* The घातer status of inभागidual sockets is not available
	 * explicitly from the hardware, so we just remember the state
	 * and regurgitate it upon request:
	 */
	stat |= skt->cs_state.Vcc ? SS_POWERON : 0;

	अगर (skt->cs_state.flags & SS_IOCARD)
		stat |= state.bvd1 ? 0 : SS_STSCHG;
	अन्यथा अणु
		अगर (state.bvd1 == 0)
			stat |= SS_BATDEAD;
		अन्यथा अगर (state.bvd2 == 0)
			stat |= SS_BATWARN;
	पूर्ण
	वापस stat;
पूर्ण

/*
 * soc_common_pcmcia_config_skt
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *
 * Convert PCMCIA socket state to our socket configure काष्ठाure.
 */
अटल पूर्णांक soc_common_pcmcia_config_skt(
	काष्ठा soc_pcmcia_socket *skt, socket_state_t *state)
अणु
	पूर्णांक ret;

	ret = skt->ops->configure_socket(skt, state);
	अगर (ret < 0) अणु
		pr_err("soc_common_pcmcia: unable to configure socket %d\n",
		       skt->nr);
		/* restore the previous state */
		WARN_ON(skt->ops->configure_socket(skt, &skt->cs_state));
		वापस ret;
	पूर्ण

	अगर (ret == 0) अणु
		काष्ठा gpio_desc *descs[2];
		DECLARE_BITMAP(values, 2);
		पूर्णांक n = 0;

		अगर (skt->gpio_reset) अणु
			descs[n] = skt->gpio_reset;
			__assign_bit(n++, values, state->flags & SS_RESET);
		पूर्ण
		अगर (skt->gpio_bus_enable) अणु
			descs[n] = skt->gpio_bus_enable;
			__assign_bit(n++, values, state->flags & SS_OUTPUT_ENA);
		पूर्ण

		अगर (n)
			gpiod_set_array_value_cansleep(n, descs, शून्य, values);

		/*
		 * This really needs a better solution.  The IRQ
		 * may or may not be claimed by the driver.
		 */
		अगर (skt->irq_state != 1 && state->io_irq) अणु
			skt->irq_state = 1;
			irq_set_irq_type(skt->socket.pci_irq,
					 IRQ_TYPE_EDGE_FALLING);
		पूर्ण अन्यथा अगर (skt->irq_state == 1 && state->io_irq == 0) अणु
			skt->irq_state = 0;
			irq_set_irq_type(skt->socket.pci_irq, IRQ_TYPE_NONE);
		पूर्ण

		skt->cs_state = *state;
	पूर्ण

	वापस ret;
पूर्ण

/* soc_common_pcmcia_sock_init()
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *
 * (Re-)Initialise the socket, turning on status पूर्णांकerrupts
 * and PCMCIA bus.  This must रुको क्रम घातer to stabilise
 * so that the card status संकेतs report correctly.
 *
 * Returns: 0
 */
अटल पूर्णांक soc_common_pcmcia_sock_init(काष्ठा pcmcia_socket *sock)
अणु
	काष्ठा soc_pcmcia_socket *skt = to_soc_pcmcia_socket(sock);

	debug(skt, 2, "initializing socket\n");
	अगर (skt->ops->socket_init)
		skt->ops->socket_init(skt);
	soc_pcmcia_hw_enable(skt);
	वापस 0;
पूर्ण


/*
 * soc_common_pcmcia_suspend()
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *
 * Remove घातer on the socket, disable IRQs from the card.
 * Turn off status पूर्णांकerrupts, and disable the PCMCIA bus.
 *
 * Returns: 0
 */
अटल पूर्णांक soc_common_pcmcia_suspend(काष्ठा pcmcia_socket *sock)
अणु
	काष्ठा soc_pcmcia_socket *skt = to_soc_pcmcia_socket(sock);

	debug(skt, 2, "suspending socket\n");

	soc_pcmcia_hw_disable(skt);
	अगर (skt->ops->socket_suspend)
		skt->ops->socket_suspend(skt);

	वापस 0;
पूर्ण

अटल DEFINE_SPINLOCK(status_lock);

अटल व्योम soc_common_check_status(काष्ठा soc_pcmcia_socket *skt)
अणु
	अचिन्हित पूर्णांक events;

	debug(skt, 4, "entering PCMCIA monitoring thread\n");

	करो अणु
		अचिन्हित पूर्णांक status;
		अचिन्हित दीर्घ flags;

		status = soc_common_pcmcia_skt_state(skt);

		spin_lock_irqsave(&status_lock, flags);
		events = (status ^ skt->status) & skt->cs_state.csc_mask;
		skt->status = status;
		spin_unlock_irqrestore(&status_lock, flags);

		debug(skt, 4, "events: %s%s%s%s%s%s\n",
			events == 0         ? "<NONE>"   : "",
			events & SS_DETECT  ? "DETECT "  : "",
			events & SS_READY   ? "READY "   : "",
			events & SS_BATDEAD ? "BATDEAD " : "",
			events & SS_BATWARN ? "BATWARN " : "",
			events & SS_STSCHG  ? "STSCHG "  : "");

		अगर (events)
			pcmcia_parse_events(&skt->socket, events);
	पूर्ण जबतक (events);
पूर्ण

/* Let's poll क्रम events in addition to IRQs since IRQ only is unreliable... */
अटल व्योम soc_common_pcmcia_poll_event(काष्ठा समयr_list *t)
अणु
	काष्ठा soc_pcmcia_socket *skt = from_समयr(skt, t, poll_समयr);
	debug(skt, 4, "polling for events\n");

	mod_समयr(&skt->poll_समयr, jअगरfies + SOC_PCMCIA_POLL_PERIOD);

	soc_common_check_status(skt);
पूर्ण


/*
 * Service routine क्रम socket driver पूर्णांकerrupts (requested by the
 * low-level PCMCIA init() operation via soc_common_pcmcia_thपढ़ो()).
 * The actual पूर्णांकerrupt-servicing work is perक्रमmed by
 * soc_common_pcmcia_thपढ़ो(), largely because the Card Services event-
 * handling code perक्रमms scheduling operations which cannot be
 * executed from within an पूर्णांकerrupt context.
 */
अटल irqवापस_t soc_common_pcmcia_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा soc_pcmcia_socket *skt = dev;

	debug(skt, 3, "servicing IRQ %d\n", irq);

	soc_common_check_status(skt);

	वापस IRQ_HANDLED;
पूर्ण


/*
 *  Implements the get_status() operation क्रम the in-kernel PCMCIA
 * service (क्रमmerly SS_GetStatus in Card Services). Essentially just
 * fills in bits in `status' according to पूर्णांकernal driver state or
 * the value of the voltage detect chipselect रेजिस्टर.
 *
 * As a debugging note, during card startup, the PCMCIA core issues
 * three set_socket() commands in a row the first with RESET deनिश्चितed,
 * the second with RESET निश्चितed, and the last with RESET deनिश्चितed
 * again. Following the third set_socket(), a get_status() command will
 * be issued. The kernel is looking क्रम the SS_READY flag (see
 * setup_socket(), reset_socket(), and unreset_socket() in cs.c).
 *
 * Returns: 0
 */
अटल पूर्णांक
soc_common_pcmcia_get_status(काष्ठा pcmcia_socket *sock, अचिन्हित पूर्णांक *status)
अणु
	काष्ठा soc_pcmcia_socket *skt = to_soc_pcmcia_socket(sock);

	skt->status = soc_common_pcmcia_skt_state(skt);
	*status = skt->status;

	वापस 0;
पूर्ण


/*
 * Implements the set_socket() operation क्रम the in-kernel PCMCIA
 * service (क्रमmerly SS_SetSocket in Card Services). We more or
 * less punt all of this work and let the kernel handle the details
 * of घातer configuration, reset, &c. We also record the value of
 * `state' in order to regurgitate it to the PCMCIA core later.
 */
अटल पूर्णांक soc_common_pcmcia_set_socket(
	काष्ठा pcmcia_socket *sock, socket_state_t *state)
अणु
	काष्ठा soc_pcmcia_socket *skt = to_soc_pcmcia_socket(sock);

	debug(skt, 2, "mask: %s%s%s%s%s%s flags: %s%s%s%s%s%s Vcc %d Vpp %d irq %d\n",
			(state->csc_mask == 0)		? "<NONE> " :	"",
			(state->csc_mask & SS_DETECT)	? "DETECT " :	"",
			(state->csc_mask & SS_READY)	? "READY " :	"",
			(state->csc_mask & SS_BATDEAD)	? "BATDEAD " :	"",
			(state->csc_mask & SS_BATWARN)	? "BATWARN " :	"",
			(state->csc_mask & SS_STSCHG)	? "STSCHG " :	"",
			(state->flags == 0)		? "<NONE> " :	"",
			(state->flags & SS_PWR_AUTO)	? "PWR_AUTO " :	"",
			(state->flags & SS_IOCARD)	? "IOCARD " :	"",
			(state->flags & SS_RESET)	? "RESET " :	"",
			(state->flags & SS_SPKR_ENA)	? "SPKR_ENA " :	"",
			(state->flags & SS_OUTPUT_ENA)	? "OUTPUT_ENA " : "",
			state->Vcc, state->Vpp, state->io_irq);

	वापस soc_common_pcmcia_config_skt(skt, state);
पूर्ण


/*
 * Implements the set_io_map() operation क्रम the in-kernel PCMCIA
 * service (क्रमmerly SS_SetIOMap in Card Services). We configure
 * the map speed as requested, but override the address ranges
 * supplied by Card Services.
 *
 * Returns: 0 on success, -1 on error
 */
अटल पूर्णांक soc_common_pcmcia_set_io_map(
	काष्ठा pcmcia_socket *sock, काष्ठा pccard_io_map *map)
अणु
	काष्ठा soc_pcmcia_socket *skt = to_soc_pcmcia_socket(sock);
	अचिन्हित लघु speed = map->speed;

	debug(skt, 2, "map %u  speed %u start 0x%08llx stop 0x%08llx\n",
		map->map, map->speed, (अचिन्हित दीर्घ दीर्घ)map->start,
		(अचिन्हित दीर्घ दीर्घ)map->stop);
	debug(skt, 2, "flags: %s%s%s%s%s%s%s%s\n",
		(map->flags == 0)		? "<NONE>"	: "",
		(map->flags & MAP_ACTIVE)	? "ACTIVE "	: "",
		(map->flags & MAP_16BIT)	? "16BIT "	: "",
		(map->flags & MAP_AUTOSZ)	? "AUTOSZ "	: "",
		(map->flags & MAP_0WS)		? "0WS "	: "",
		(map->flags & MAP_WRPROT)	? "WRPROT "	: "",
		(map->flags & MAP_USE_WAIT)	? "USE_WAIT "	: "",
		(map->flags & MAP_PREFETCH)	? "PREFETCH "	: "");

	अगर (map->map >= MAX_IO_WIN) अणु
		prपूर्णांकk(KERN_ERR "%s(): map (%d) out of range\n", __func__,
		       map->map);
		वापस -1;
	पूर्ण

	अगर (map->flags & MAP_ACTIVE) अणु
		अगर (speed == 0)
			speed = SOC_PCMCIA_IO_ACCESS;
	पूर्ण अन्यथा अणु
		speed = 0;
	पूर्ण

	skt->spd_io[map->map] = speed;
	skt->ops->set_timing(skt);

	अगर (map->stop == 1)
		map->stop = PAGE_SIZE-1;

	map->stop -= map->start;
	map->stop += skt->socket.io_offset;
	map->start = skt->socket.io_offset;

	वापस 0;
पूर्ण


/*
 * Implements the set_mem_map() operation क्रम the in-kernel PCMCIA
 * service (क्रमmerly SS_SetMemMap in Card Services). We configure
 * the map speed as requested, but override the address ranges
 * supplied by Card Services.
 *
 * Returns: 0 on success, -ERRNO on error
 */
अटल पूर्णांक soc_common_pcmcia_set_mem_map(
	काष्ठा pcmcia_socket *sock, काष्ठा pccard_mem_map *map)
अणु
	काष्ठा soc_pcmcia_socket *skt = to_soc_pcmcia_socket(sock);
	काष्ठा resource *res;
	अचिन्हित लघु speed = map->speed;

	debug(skt, 2, "map %u speed %u card_start %08x\n",
		map->map, map->speed, map->card_start);
	debug(skt, 2, "flags: %s%s%s%s%s%s%s%s\n",
		(map->flags == 0)		? "<NONE>"	: "",
		(map->flags & MAP_ACTIVE)	? "ACTIVE "	: "",
		(map->flags & MAP_16BIT)	? "16BIT "	: "",
		(map->flags & MAP_AUTOSZ)	? "AUTOSZ "	: "",
		(map->flags & MAP_0WS)		? "0WS "	: "",
		(map->flags & MAP_WRPROT)	? "WRPROT "	: "",
		(map->flags & MAP_ATTRIB)	? "ATTRIB "	: "",
		(map->flags & MAP_USE_WAIT)	? "USE_WAIT "	: "");

	अगर (map->map >= MAX_WIN)
		वापस -EINVAL;

	अगर (map->flags & MAP_ACTIVE) अणु
		अगर (speed == 0)
			speed = 300;
	पूर्ण अन्यथा अणु
		speed = 0;
	पूर्ण

	अगर (map->flags & MAP_ATTRIB) अणु
		res = &skt->res_attr;
		skt->spd_attr[map->map] = speed;
		skt->spd_mem[map->map] = 0;
	पूर्ण अन्यथा अणु
		res = &skt->res_mem;
		skt->spd_attr[map->map] = 0;
		skt->spd_mem[map->map] = speed;
	पूर्ण

	skt->ops->set_timing(skt);

	map->अटल_start = res->start + map->card_start;

	वापस 0;
पूर्ण

काष्ठा bittbl अणु
	अचिन्हित पूर्णांक mask;
	स्थिर अक्षर *name;
पूर्ण;

अटल काष्ठा bittbl status_bits[] = अणु
	अणु SS_WRPROT,		"SS_WRPROT"	पूर्ण,
	अणु SS_BATDEAD,		"SS_BATDEAD"	पूर्ण,
	अणु SS_BATWARN,		"SS_BATWARN"	पूर्ण,
	अणु SS_READY,		"SS_READY"	पूर्ण,
	अणु SS_DETECT,		"SS_DETECT"	पूर्ण,
	अणु SS_POWERON,		"SS_POWERON"	पूर्ण,
	अणु SS_STSCHG,		"SS_STSCHG"	पूर्ण,
	अणु SS_3VCARD,		"SS_3VCARD"	पूर्ण,
	अणु SS_XVCARD,		"SS_XVCARD"	पूर्ण,
पूर्ण;

अटल काष्ठा bittbl conf_bits[] = अणु
	अणु SS_PWR_AUTO,		"SS_PWR_AUTO"	पूर्ण,
	अणु SS_IOCARD,		"SS_IOCARD"	पूर्ण,
	अणु SS_RESET,		"SS_RESET"	पूर्ण,
	अणु SS_DMA_MODE,		"SS_DMA_MODE"	पूर्ण,
	अणु SS_SPKR_ENA,		"SS_SPKR_ENA"	पूर्ण,
	अणु SS_OUTPUT_ENA,	"SS_OUTPUT_ENA"	पूर्ण,
पूर्ण;

अटल व्योम dump_bits(अक्षर **p, स्थिर अक्षर *prefix,
	अचिन्हित पूर्णांक val, काष्ठा bittbl *bits, पूर्णांक sz)
अणु
	अक्षर *b = *p;
	पूर्णांक i;

	b += प्र_लिखो(b, "%-9s:", prefix);
	क्रम (i = 0; i < sz; i++)
		अगर (val & bits[i].mask)
			b += प्र_लिखो(b, " %s", bits[i].name);
	*b++ = '\n';
	*p = b;
पूर्ण

/*
 * Implements the /sys/class/pcmcia_socket/??/status file.
 *
 * Returns: the number of अक्षरacters added to the buffer
 */
अटल sमाप_प्रकार show_status(
	काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा soc_pcmcia_socket *skt =
		container_of(dev, काष्ठा soc_pcmcia_socket, socket.dev);
	अक्षर *p = buf;

	p += प्र_लिखो(p, "slot     : %d\n", skt->nr);

	dump_bits(&p, "status", skt->status,
		  status_bits, ARRAY_SIZE(status_bits));
	dump_bits(&p, "csc_mask", skt->cs_state.csc_mask,
		  status_bits, ARRAY_SIZE(status_bits));
	dump_bits(&p, "cs_flags", skt->cs_state.flags,
		  conf_bits, ARRAY_SIZE(conf_bits));

	p += प्र_लिखो(p, "Vcc      : %d\n", skt->cs_state.Vcc);
	p += प्र_लिखो(p, "Vpp      : %d\n", skt->cs_state.Vpp);
	p += प्र_लिखो(p, "IRQ      : %d (%d)\n", skt->cs_state.io_irq,
		skt->socket.pci_irq);
	अगर (skt->ops->show_timing)
		p += skt->ops->show_timing(skt, p);

	वापस p-buf;
पूर्ण
अटल DEVICE_ATTR(status, S_IRUGO, show_status, शून्य);


अटल काष्ठा pccard_operations soc_common_pcmcia_operations = अणु
	.init			= soc_common_pcmcia_sock_init,
	.suspend		= soc_common_pcmcia_suspend,
	.get_status		= soc_common_pcmcia_get_status,
	.set_socket		= soc_common_pcmcia_set_socket,
	.set_io_map		= soc_common_pcmcia_set_io_map,
	.set_mem_map		= soc_common_pcmcia_set_mem_map,
पूर्ण;


#अगर_घोषित CONFIG_CPU_FREQ
अटल पूर्णांक soc_common_pcmcia_cpufreq_nb(काष्ठा notअगरier_block *nb,
	अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा soc_pcmcia_socket *skt = container_of(nb, काष्ठा soc_pcmcia_socket, cpufreq_nb);
	काष्ठा cpufreq_freqs *freqs = data;

	वापस skt->ops->frequency_change(skt, val, freqs);
पूर्ण
#पूर्ण_अगर

व्योम soc_pcmcia_init_one(काष्ठा soc_pcmcia_socket *skt,
	स्थिर काष्ठा pcmcia_low_level *ops, काष्ठा device *dev)
अणु
	पूर्णांक i;

	skt->ops = ops;
	skt->socket.owner = ops->owner;
	skt->socket.dev.parent = dev;
	skt->socket.pci_irq = NO_IRQ;

	क्रम (i = 0; i < ARRAY_SIZE(skt->stat); i++)
		skt->stat[i].gpio = -EINVAL;
पूर्ण
EXPORT_SYMBOL(soc_pcmcia_init_one);

व्योम soc_pcmcia_हटाओ_one(काष्ठा soc_pcmcia_socket *skt)
अणु
	del_समयr_sync(&skt->poll_समयr);

	pcmcia_unरेजिस्टर_socket(&skt->socket);

#अगर_घोषित CONFIG_CPU_FREQ
	अगर (skt->ops->frequency_change)
		cpufreq_unरेजिस्टर_notअगरier(&skt->cpufreq_nb,
					    CPUFREQ_TRANSITION_NOTIFIER);
#पूर्ण_अगर

	soc_pcmcia_hw_shutकरोwn(skt);

	/* should not be required; violates some lowlevel drivers */
	soc_common_pcmcia_config_skt(skt, &dead_socket);

	iounmap(skt->virt_io);
	skt->virt_io = शून्य;
	release_resource(&skt->res_attr);
	release_resource(&skt->res_mem);
	release_resource(&skt->res_io);
	release_resource(&skt->res_skt);
पूर्ण
EXPORT_SYMBOL(soc_pcmcia_हटाओ_one);

पूर्णांक soc_pcmcia_add_one(काष्ठा soc_pcmcia_socket *skt)
अणु
	पूर्णांक ret;

	skt->cs_state = dead_socket;

	समयr_setup(&skt->poll_समयr, soc_common_pcmcia_poll_event, 0);
	skt->poll_समयr.expires = jअगरfies + SOC_PCMCIA_POLL_PERIOD;

	ret = request_resource(&iomem_resource, &skt->res_skt);
	अगर (ret)
		जाओ out_err_1;

	ret = request_resource(&skt->res_skt, &skt->res_io);
	अगर (ret)
		जाओ out_err_2;

	ret = request_resource(&skt->res_skt, &skt->res_mem);
	अगर (ret)
		जाओ out_err_3;

	ret = request_resource(&skt->res_skt, &skt->res_attr);
	अगर (ret)
		जाओ out_err_4;

	skt->virt_io = ioremap(skt->res_io.start, 0x10000);
	अगर (skt->virt_io == शून्य) अणु
		ret = -ENOMEM;
		जाओ out_err_5;
	पूर्ण

	/*
	 * We initialize शेष socket timing here, because
	 * we are not guaranteed to see a SetIOMap operation at
	 * runसमय.
	 */
	skt->ops->set_timing(skt);

	ret = soc_pcmcia_hw_init(skt);
	अगर (ret)
		जाओ out_err_6;

	skt->socket.ops = &soc_common_pcmcia_operations;
	skt->socket.features = SS_CAP_STATIC_MAP|SS_CAP_PCCARD;
	skt->socket.resource_ops = &pccard_अटल_ops;
	skt->socket.irq_mask = 0;
	skt->socket.map_size = PAGE_SIZE;
	skt->socket.io_offset = (अचिन्हित दीर्घ)skt->virt_io;

	skt->status = soc_common_pcmcia_skt_state(skt);

#अगर_घोषित CONFIG_CPU_FREQ
	अगर (skt->ops->frequency_change) अणु
		skt->cpufreq_nb.notअगरier_call = soc_common_pcmcia_cpufreq_nb;

		ret = cpufreq_रेजिस्टर_notअगरier(&skt->cpufreq_nb,
						CPUFREQ_TRANSITION_NOTIFIER);
		अगर (ret < 0)
			dev_err(skt->socket.dev.parent,
				"unable to register CPU frequency change notifier for PCMCIA (%d)\n",
				ret);
	पूर्ण
#पूर्ण_अगर

	ret = pcmcia_रेजिस्टर_socket(&skt->socket);
	अगर (ret)
		जाओ out_err_7;

	ret = device_create_file(&skt->socket.dev, &dev_attr_status);
	अगर (ret)
		जाओ out_err_8;

	वापस ret;

 out_err_8:
	del_समयr_sync(&skt->poll_समयr);
	pcmcia_unरेजिस्टर_socket(&skt->socket);

 out_err_7:
	soc_pcmcia_hw_shutकरोwn(skt);
 out_err_6:
	iounmap(skt->virt_io);
 out_err_5:
	release_resource(&skt->res_attr);
 out_err_4:
	release_resource(&skt->res_mem);
 out_err_3:
	release_resource(&skt->res_io);
 out_err_2:
	release_resource(&skt->res_skt);
 out_err_1:

	वापस ret;
पूर्ण
EXPORT_SYMBOL(soc_pcmcia_add_one);

MODULE_AUTHOR("John Dorsey <john+@cs.cmu.edu>");
MODULE_DESCRIPTION("Linux PCMCIA Card Services: Common SoC support");
MODULE_LICENSE("Dual MPL/GPL");
