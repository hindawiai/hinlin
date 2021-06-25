<शैली गुरु>
/*
 * IEEE-1284 implementation क्रम parport.
 *
 * Authors: Phil Blundell <philb@gnu.org>
 *          Carsten Gross <carsten@sol.wohnheim.uni-ulm.de>
 *	    Jose Renau <renau@acm.org>
 *          Tim Waugh <tim@cyberelk.demon.co.uk> (largely rewritten)
 *
 * This file is responsible क्रम IEEE 1284 negotiation, and क्रम handing
 * पढ़ो/ग_लिखो requests to low-level drivers.
 *
 * Any part of this program may be used in करोcuments licensed under
 * the GNU Free Documentation License, Version 1.1 or any later version
 * published by the Free Software Foundation.
 *
 * Various hacks, Fred Barnes <frmb2@ukc.ac.uk>, 04/2000
 */

#समावेश <linux/module.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/parport.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/sched/संकेत.स>

#अघोषित DEBUG /* undef me क्रम production */

#अगर_घोषित CONFIG_LP_CONSOLE
#अघोषित DEBUG /* Don't want a garbled console */
#पूर्ण_अगर

/* Make parport_रुको_peripheral wake up.
 * It will be useful to call this from an पूर्णांकerrupt handler. */
अटल व्योम parport_ieee1284_wakeup (काष्ठा parport *port)
अणु
	up (&port->physport->ieee1284.irq);
पूर्ण

अटल व्योम समयout_रुकोing_on_port (काष्ठा समयr_list *t)
अणु
	काष्ठा parport *port = from_समयr(port, t, समयr);

	parport_ieee1284_wakeup (port);
पूर्ण

/**
 *	parport_रुको_event - रुको क्रम an event on a parallel port
 *	@port: port to रुको on
 *	@समयout: समय to रुको (in jअगरfies)
 *
 *	This function रुकोs क्रम up to @समयout jअगरfies क्रम an
 *	पूर्णांकerrupt to occur on a parallel port.  If the port समयout is
 *	set to zero, it वापसs immediately.
 *
 *	If an पूर्णांकerrupt occurs beक्रमe the समयout period elapses, this
 *	function वापसs zero immediately.  If it बार out, it वापसs
 *	one.  An error code less than zero indicates an error (most
 *	likely a pending संकेत), and the calling code should finish
 *	what it's करोing as soon as it can.
 */

पूर्णांक parport_रुको_event (काष्ठा parport *port, चिन्हित दीर्घ समयout)
अणु
	पूर्णांक ret;

	अगर (!port->physport->cad->समयout)
		/* Zero समयout is special, and we can't करोwn() the
		   semaphore. */
		वापस 1;

	समयr_setup(&port->समयr, समयout_रुकोing_on_port, 0);
	mod_समयr(&port->समयr, jअगरfies + समयout);
	ret = करोwn_पूर्णांकerruptible (&port->physport->ieee1284.irq);
	अगर (!del_समयr_sync(&port->समयr) && !ret)
		/* Timed out. */
		ret = 1;

	वापस ret;
पूर्ण

/**
 *	parport_poll_peripheral - poll status lines
 *	@port: port to watch
 *	@mask: status lines to watch
 *	@result: desired values of chosen status lines
 *	@usec: समयout
 *
 *	This function busy-रुकोs until the masked status lines have
 *	the desired values, or until the समयout period elapses.  The
 *	@mask and @result parameters are biपंचांगasks, with the bits
 *	defined by the स्थिरants in parport.h: %PARPORT_STATUS_BUSY,
 *	and so on.
 *
 *	This function करोes not call schedule(); instead it busy-रुकोs
 *	using udelay().  It currently has a resolution of 5usec.
 *
 *	If the status lines take on the desired values beक्रमe the
 *	समयout period elapses, parport_poll_peripheral() वापसs zero
 *	immediately.  A वापस value greater than zero indicates
 *	a समयout.  An error code (less than zero) indicates an error,
 *	most likely a संकेत that arrived, and the caller should
 *	finish what it is करोing as soon as possible.
*/

पूर्णांक parport_poll_peripheral(काष्ठा parport *port,
			    अचिन्हित अक्षर mask,
			    अचिन्हित अक्षर result,
			    पूर्णांक usec)
अणु
	/* Zero वापस code is success, >0 is समयout. */
	पूर्णांक count = usec / 5 + 2;
	पूर्णांक i;
	अचिन्हित अक्षर status;
	क्रम (i = 0; i < count; i++) अणु
		status = parport_पढ़ो_status (port);
		अगर ((status & mask) == result)
			वापस 0;
		अगर (संकेत_pending (current))
			वापस -EINTR;
		अगर (need_resched())
			अवरोध;
		अगर (i >= 2)
			udelay (5);
	पूर्ण

	वापस 1;
पूर्ण

/**
 *	parport_रुको_peripheral - रुको क्रम status lines to change in 35ms
 *	@port: port to watch
 *	@mask: status lines to watch
 *	@result: desired values of chosen status lines
 *
 *	This function रुकोs until the masked status lines have the
 *	desired values, or until 35ms have elapsed (see IEEE 1284-1994
 *	page 24 to 25 क्रम why this value in particular is hardcoded).
 *	The @mask and @result parameters are biपंचांगasks, with the bits
 *	defined by the स्थिरants in parport.h: %PARPORT_STATUS_BUSY,
 *	and so on.
 *
 *	The port is polled quickly to start off with, in anticipation
 *	of a fast response from the peripheral.  This fast polling
 *	समय is configurable (using /proc), and शेषs to 500usec.
 *	If the समयout क्रम this port (see parport_set_समयout()) is
 *	zero, the fast polling समय is 35ms, and this function करोes
 *	not call schedule().
 *
 *	If the समयout क्रम this port is non-zero, after the fast
 *	polling fails it uses parport_रुको_event() to रुको क्रम up to
 *	10ms, waking up अगर an पूर्णांकerrupt occurs.
 */

पूर्णांक parport_रुको_peripheral(काष्ठा parport *port,
			    अचिन्हित अक्षर mask, 
			    अचिन्हित अक्षर result)
अणु
	पूर्णांक ret;
	पूर्णांक usec;
	अचिन्हित दीर्घ deadline;
	अचिन्हित अक्षर status;

	usec = port->physport->spपूर्णांकime; /* usecs of fast polling */
	अगर (!port->physport->cad->समयout)
		/* A zero समयout is "special": busy रुको क्रम the
		   entire 35ms. */
		usec = 35000;

	/* Fast polling.
	 *
	 * This should be adjustable.
	 * How about making a note (in the device काष्ठाure) of how दीर्घ
	 * it takes, so we know क्रम next समय?
	 */
	ret = parport_poll_peripheral (port, mask, result, usec);
	अगर (ret != 1)
		वापस ret;

	अगर (!port->physport->cad->समयout)
		/* We may be in an पूर्णांकerrupt handler, so we can't poll
		 * slowly anyway. */
		वापस 1;

	/* 40ms of slow polling. */
	deadline = jअगरfies + msecs_to_jअगरfies(40);
	जबतक (समय_beक्रमe (jअगरfies, deadline)) अणु
		अगर (संकेत_pending (current))
			वापस -EINTR;

		/* Wait क्रम 10ms (or until an पूर्णांकerrupt occurs अगर
		 * the handler is set) */
		अगर ((ret = parport_रुको_event (port, msecs_to_jअगरfies(10))) < 0)
			वापस ret;

		status = parport_पढ़ो_status (port);
		अगर ((status & mask) == result)
			वापस 0;

		अगर (!ret) अणु
			/* parport_रुको_event didn't समय out, but the
			 * peripheral wasn't actually पढ़ोy either.
			 * Wait क्रम another 10ms. */
			schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(10));
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_PARPORT_1284
/* Terminate a negotiated mode. */
अटल व्योम parport_ieee1284_terminate (काष्ठा parport *port)
अणु
	पूर्णांक r;
	port = port->physport;

	/* EPP terminates dअगरferently. */
	चयन (port->ieee1284.mode) अणु
	हाल IEEE1284_MODE_EPP:
	हाल IEEE1284_MODE_EPPSL:
	हाल IEEE1284_MODE_EPPSWE:
		/* Terminate from EPP mode. */

		/* Event 68: Set nInit low */
		parport_frob_control (port, PARPORT_CONTROL_INIT, 0);
		udelay (50);

		/* Event 69: Set nInit high, nSelectIn low */
		parport_frob_control (port,
				      PARPORT_CONTROL_SELECT
				      | PARPORT_CONTROL_INIT,
				      PARPORT_CONTROL_SELECT
				      | PARPORT_CONTROL_INIT);
		अवरोध;

	हाल IEEE1284_MODE_ECP:
	हाल IEEE1284_MODE_ECPRLE:
	हाल IEEE1284_MODE_ECPSWE:
		/* In ECP we can only terminate from fwd idle phase. */
		अगर (port->ieee1284.phase != IEEE1284_PH_FWD_IDLE) अणु
			/* Event 47: Set nInit high */
			parport_frob_control (port,
					      PARPORT_CONTROL_INIT
					      | PARPORT_CONTROL_AUTOFD,
					      PARPORT_CONTROL_INIT
					      | PARPORT_CONTROL_AUTOFD);

			/* Event 49: PError goes high */
			r = parport_रुको_peripheral (port,
						     PARPORT_STATUS_PAPEROUT,
						     PARPORT_STATUS_PAPEROUT);
			अगर (r)
				pr_debug("%s: Timeout at event 49\n",
					 port->name);

			parport_data_क्रमward (port);
			pr_debug("%s: ECP direction: forward\n", port->name);
			port->ieee1284.phase = IEEE1284_PH_FWD_IDLE;
		पूर्ण

		fallthrough;

	शेष:
		/* Terminate from all other modes. */

		/* Event 22: Set nSelectIn low, nAutoFd high */
		parport_frob_control (port,
				      PARPORT_CONTROL_SELECT
				      | PARPORT_CONTROL_AUTOFD,
				      PARPORT_CONTROL_SELECT);

		/* Event 24: nAck goes low */
		r = parport_रुको_peripheral (port, PARPORT_STATUS_ACK, 0);
		अगर (r)
			pr_debug("%s: Timeout at event 24\n", port->name);

		/* Event 25: Set nAutoFd low */
		parport_frob_control (port,
				      PARPORT_CONTROL_AUTOFD,
				      PARPORT_CONTROL_AUTOFD);

		/* Event 27: nAck goes high */
		r = parport_रुको_peripheral (port,
					     PARPORT_STATUS_ACK, 
					     PARPORT_STATUS_ACK);
		अगर (r)
			pr_debug("%s: Timeout at event 27\n", port->name);

		/* Event 29: Set nAutoFd high */
		parport_frob_control (port, PARPORT_CONTROL_AUTOFD, 0);
	पूर्ण

	port->ieee1284.mode = IEEE1284_MODE_COMPAT;
	port->ieee1284.phase = IEEE1284_PH_FWD_IDLE;

	pr_debug("%s: In compatibility (forward idle) mode\n", port->name);
पूर्ण		
#पूर्ण_अगर /* IEEE1284 support */

/**
 *	parport_negotiate - negotiate an IEEE 1284 mode
 *	@port: port to use
 *	@mode: mode to negotiate to
 *
 *	Use this to negotiate to a particular IEEE 1284 transfer mode.
 *	The @mode parameter should be one of the स्थिरants in
 *	parport.h starting %IEEE1284_MODE_xxx.
 *
 *	The वापस value is 0 अगर the peripheral has accepted the
 *	negotiation to the mode specअगरied, -1 अगर the peripheral is not
 *	IEEE 1284 compliant (or not present), or 1 अगर the peripheral
 *	has rejected the negotiation.
 */

पूर्णांक parport_negotiate (काष्ठा parport *port, पूर्णांक mode)
अणु
#अगर_अघोषित CONFIG_PARPORT_1284
	अगर (mode == IEEE1284_MODE_COMPAT)
		वापस 0;
	pr_err("parport: IEEE1284 not supported in this kernel\n");
	वापस -1;
#अन्यथा
	पूर्णांक m = mode & ~IEEE1284_ADDR;
	पूर्णांक r;
	अचिन्हित अक्षर xflag;

	port = port->physport;

	/* Is there anything to करो? */
	अगर (port->ieee1284.mode == mode)
		वापस 0;

	/* Is the dअगरference just an address-or-not bit? */
	अगर ((port->ieee1284.mode & ~IEEE1284_ADDR) == (mode & ~IEEE1284_ADDR))अणु
		port->ieee1284.mode = mode;
		वापस 0;
	पूर्ण

	/* Go to compatibility क्रमward idle mode */
	अगर (port->ieee1284.mode != IEEE1284_MODE_COMPAT)
		parport_ieee1284_terminate (port);

	अगर (mode == IEEE1284_MODE_COMPAT)
		/* Compatibility mode: no negotiation. */
		वापस 0; 

	चयन (mode) अणु
	हाल IEEE1284_MODE_ECPSWE:
		m = IEEE1284_MODE_ECP;
		अवरोध;
	हाल IEEE1284_MODE_EPPSL:
	हाल IEEE1284_MODE_EPPSWE:
		m = IEEE1284_MODE_EPP;
		अवरोध;
	हाल IEEE1284_MODE_BECP:
		वापस -ENOSYS; /* FIXME (implement BECP) */
	पूर्ण

	अगर (mode & IEEE1284_EXT_LINK)
		m = 1<<7; /* request extensibility link */

	port->ieee1284.phase = IEEE1284_PH_NEGOTIATION;

	/* Start off with nStrobe and nAutoFd high, and nSelectIn low */
	parport_frob_control (port,
			      PARPORT_CONTROL_STROBE
			      | PARPORT_CONTROL_AUTOFD
			      | PARPORT_CONTROL_SELECT,
			      PARPORT_CONTROL_SELECT);
	udelay(1);

	/* Event 0: Set data */
	parport_data_क्रमward (port);
	parport_ग_लिखो_data (port, m);
	udelay (400); /* Shouldn't need to रुको this दीर्घ. */

	/* Event 1: Set nSelectIn high, nAutoFd low */
	parport_frob_control (port,
			      PARPORT_CONTROL_SELECT
			      | PARPORT_CONTROL_AUTOFD,
			      PARPORT_CONTROL_AUTOFD);

	/* Event 2: PError, Select, nFault go high, nAck goes low */
	अगर (parport_रुको_peripheral (port,
				     PARPORT_STATUS_ERROR
				     | PARPORT_STATUS_SELECT
				     | PARPORT_STATUS_PAPEROUT
				     | PARPORT_STATUS_ACK,
				     PARPORT_STATUS_ERROR
				     | PARPORT_STATUS_SELECT
				     | PARPORT_STATUS_PAPEROUT)) अणु
		/* Timeout */
		parport_frob_control (port,
				      PARPORT_CONTROL_SELECT
				      | PARPORT_CONTROL_AUTOFD,
				      PARPORT_CONTROL_SELECT);
		pr_debug("%s: Peripheral not IEEE1284 compliant (0x%02X)\n",
			 port->name, parport_पढ़ो_status (port));
		port->ieee1284.phase = IEEE1284_PH_FWD_IDLE;
		वापस -1; /* Not IEEE1284 compliant */
	पूर्ण

	/* Event 3: Set nStrobe low */
	parport_frob_control (port,
			      PARPORT_CONTROL_STROBE,
			      PARPORT_CONTROL_STROBE);

	/* Event 4: Set nStrobe and nAutoFd high */
	udelay (5);
	parport_frob_control (port,
			      PARPORT_CONTROL_STROBE
			      | PARPORT_CONTROL_AUTOFD,
			      0);

	/* Event 6: nAck goes high */
	अगर (parport_रुको_peripheral (port,
				     PARPORT_STATUS_ACK,
				     PARPORT_STATUS_ACK)) अणु
		/* This shouldn't really happen with a compliant device. */
		pr_debug("%s: Mode 0x%02x not supported? (0x%02x)\n",
			 port->name, mode, port->ops->पढ़ो_status (port));
		parport_ieee1284_terminate (port);
		वापस 1;
	पूर्ण

	xflag = parport_पढ़ो_status (port) & PARPORT_STATUS_SELECT;

	/* xflag should be high क्रम all modes other than nibble (0). */
	अगर (mode && !xflag) अणु
		/* Mode not supported. */
		pr_debug("%s: Mode 0x%02x rejected by peripheral\n",
			 port->name, mode);
		parport_ieee1284_terminate (port);
		वापस 1;
	पूर्ण

	/* More to करो अगर we've requested extensibility link. */
	अगर (mode & IEEE1284_EXT_LINK) अणु
		m = mode & 0x7f;
		udelay (1);
		parport_ग_लिखो_data (port, m);
		udelay (1);

		/* Event 51: Set nStrobe low */
		parport_frob_control (port,
				      PARPORT_CONTROL_STROBE,
				      PARPORT_CONTROL_STROBE);

		/* Event 52: nAck goes low */
		अगर (parport_रुको_peripheral (port, PARPORT_STATUS_ACK, 0)) अणु
			/* This peripheral is _very_ slow. */
			pr_debug("%s: Event 52 didn't happen\n", port->name);
			parport_ieee1284_terminate (port);
			वापस 1;
		पूर्ण

		/* Event 53: Set nStrobe high */
		parport_frob_control (port,
				      PARPORT_CONTROL_STROBE,
				      0);

		/* Event 55: nAck goes high */
		अगर (parport_रुको_peripheral (port,
					     PARPORT_STATUS_ACK,
					     PARPORT_STATUS_ACK)) अणु
			/* This shouldn't really happen with a compliant
			 * device. */
			pr_debug("%s: Mode 0x%02x not supported? (0x%02x)\n",
				 port->name, mode,
				 port->ops->पढ़ो_status(port));
			parport_ieee1284_terminate (port);
			वापस 1;
		पूर्ण

		/* Event 54: Peripheral sets XFlag to reflect support */
		xflag = parport_पढ़ो_status (port) & PARPORT_STATUS_SELECT;

		/* xflag should be high. */
		अगर (!xflag) अणु
			/* Extended mode not supported. */
			pr_debug("%s: Extended mode 0x%02x not supported\n",
				 port->name, mode);
			parport_ieee1284_terminate (port);
			वापस 1;
		पूर्ण

		/* Any further setup is left to the caller. */
	पूर्ण

	/* Mode is supported */
	pr_debug("%s: In mode 0x%02x\n", port->name, mode);
	port->ieee1284.mode = mode;

	/* But ECP is special */
	अगर (!(mode & IEEE1284_EXT_LINK) && (m & IEEE1284_MODE_ECP)) अणु
		port->ieee1284.phase = IEEE1284_PH_ECP_SETUP;

		/* Event 30: Set nAutoFd low */
		parport_frob_control (port,
				      PARPORT_CONTROL_AUTOFD,
				      PARPORT_CONTROL_AUTOFD);

		/* Event 31: PError goes high. */
		r = parport_रुको_peripheral (port,
					     PARPORT_STATUS_PAPEROUT,
					     PARPORT_STATUS_PAPEROUT);
		अगर (r) अणु
			pr_debug("%s: Timeout at event 31\n", port->name);
		पूर्ण

		port->ieee1284.phase = IEEE1284_PH_FWD_IDLE;
		pr_debug("%s: ECP direction: forward\n", port->name);
	पूर्ण अन्यथा चयन (mode) अणु
	हाल IEEE1284_MODE_NIBBLE:
	हाल IEEE1284_MODE_BYTE:
		port->ieee1284.phase = IEEE1284_PH_REV_IDLE;
		अवरोध;
	शेष:
		port->ieee1284.phase = IEEE1284_PH_FWD_IDLE;
	पूर्ण


	वापस 0;
#पूर्ण_अगर /* IEEE1284 support */
पूर्ण

/* Acknowledge that the peripheral has data available.
 * Events 18-20, in order to get from Reverse Idle phase
 * to Host Busy Data Available.
 * This will most likely be called from an पूर्णांकerrupt.
 * Returns zero अगर data was available.
 */
#अगर_घोषित CONFIG_PARPORT_1284
अटल पूर्णांक parport_ieee1284_ack_data_avail (काष्ठा parport *port)
अणु
	अगर (parport_पढ़ो_status (port) & PARPORT_STATUS_ERROR)
		/* Event 18 didn't happen. */
		वापस -1;

	/* Event 20: nAutoFd goes high. */
	port->ops->frob_control (port, PARPORT_CONTROL_AUTOFD, 0);
	port->ieee1284.phase = IEEE1284_PH_HBUSY_DAVAIL;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* IEEE1284 support */

/* Handle an पूर्णांकerrupt. */
व्योम parport_ieee1284_पूर्णांकerrupt (व्योम *handle)
अणु
	काष्ठा parport *port = handle;
	parport_ieee1284_wakeup (port);

#अगर_घोषित CONFIG_PARPORT_1284
	अगर (port->ieee1284.phase == IEEE1284_PH_REV_IDLE) अणु
		/* An पूर्णांकerrupt in this phase means that data
		 * is now available. */
		pr_debug("%s: Data available\n", port->name);
		parport_ieee1284_ack_data_avail (port);
	पूर्ण
#पूर्ण_अगर /* IEEE1284 support */
पूर्ण

/**
 *	parport_ग_लिखो - ग_लिखो a block of data to a parallel port
 *	@port: port to ग_लिखो to
 *	@buffer: data buffer (in kernel space)
 *	@len: number of bytes of data to transfer
 *
 *	This will ग_लिखो up to @len bytes of @buffer to the port
 *	specअगरied, using the IEEE 1284 transfer mode most recently
 *	negotiated to (using parport_negotiate()), as दीर्घ as that
 *	mode supports क्रमward transfers (host to peripheral).
 *
 *	It is the caller's responsibility to ensure that the first
 *	@len bytes of @buffer are valid.
 *
 *	This function वापसs the number of bytes transferred (अगर zero
 *	or positive), or अन्यथा an error code.
 */

sमाप_प्रकार parport_ग_लिखो (काष्ठा parport *port, स्थिर व्योम *buffer, माप_प्रकार len)
अणु
#अगर_अघोषित CONFIG_PARPORT_1284
	वापस port->ops->compat_ग_लिखो_data (port, buffer, len, 0);
#अन्यथा
	sमाप_प्रकार retval;
	पूर्णांक mode = port->ieee1284.mode;
	पूर्णांक addr = mode & IEEE1284_ADDR;
	माप_प्रकार (*fn) (काष्ठा parport *, स्थिर व्योम *, माप_प्रकार, पूर्णांक);

	/* Ignore the device-ID-request bit and the address bit. */
	mode &= ~(IEEE1284_DEVICEID | IEEE1284_ADDR);

	/* Use the mode we're in. */
	चयन (mode) अणु
	हाल IEEE1284_MODE_NIBBLE:
	हाल IEEE1284_MODE_BYTE:
		parport_negotiate (port, IEEE1284_MODE_COMPAT);
		fallthrough;
	हाल IEEE1284_MODE_COMPAT:
		pr_debug("%s: Using compatibility mode\n", port->name);
		fn = port->ops->compat_ग_लिखो_data;
		अवरोध;

	हाल IEEE1284_MODE_EPP:
		pr_debug("%s: Using EPP mode\n", port->name);
		अगर (addr) अणु
			fn = port->ops->epp_ग_लिखो_addr;
		पूर्ण अन्यथा अणु
			fn = port->ops->epp_ग_लिखो_data;
		पूर्ण
		अवरोध;
	हाल IEEE1284_MODE_EPPSWE:
		pr_debug("%s: Using software-emulated EPP mode\n", port->name);
		अगर (addr) अणु
			fn = parport_ieee1284_epp_ग_लिखो_addr;
		पूर्ण अन्यथा अणु
			fn = parport_ieee1284_epp_ग_लिखो_data;
		पूर्ण
		अवरोध;
	हाल IEEE1284_MODE_ECP:
	हाल IEEE1284_MODE_ECPRLE:
		pr_debug("%s: Using ECP mode\n", port->name);
		अगर (addr) अणु
			fn = port->ops->ecp_ग_लिखो_addr;
		पूर्ण अन्यथा अणु
			fn = port->ops->ecp_ग_लिखो_data;
		पूर्ण
		अवरोध;

	हाल IEEE1284_MODE_ECPSWE:
		pr_debug("%s: Using software-emulated ECP mode\n", port->name);
		/* The caller has specअगरied that it must be emulated,
		 * even अगर we have ECP hardware! */
		अगर (addr) अणु
			fn = parport_ieee1284_ecp_ग_लिखो_addr;
		पूर्ण अन्यथा अणु
			fn = parport_ieee1284_ecp_ग_लिखो_data;
		पूर्ण
		अवरोध;

	शेष:
		pr_debug("%s: Unknown mode 0x%02x\n",
			 port->name, port->ieee1284.mode);
		वापस -ENOSYS;
	पूर्ण

	retval = (*fn) (port, buffer, len, 0);
	pr_debug("%s: wrote %zd/%zu bytes\n", port->name, retval, len);
	वापस retval;
#पूर्ण_अगर /* IEEE1284 support */
पूर्ण

/**
 *	parport_पढ़ो - पढ़ो a block of data from a parallel port
 *	@port: port to पढ़ो from
 *	@buffer: data buffer (in kernel space)
 *	@len: number of bytes of data to transfer
 *
 *	This will पढ़ो up to @len bytes of @buffer to the port
 *	specअगरied, using the IEEE 1284 transfer mode most recently
 *	negotiated to (using parport_negotiate()), as दीर्घ as that
 *	mode supports reverse transfers (peripheral to host).
 *
 *	It is the caller's responsibility to ensure that the first
 *	@len bytes of @buffer are available to ग_लिखो to.
 *
 *	This function वापसs the number of bytes transferred (अगर zero
 *	or positive), or अन्यथा an error code.
 */

sमाप_प्रकार parport_पढ़ो (काष्ठा parport *port, व्योम *buffer, माप_प्रकार len)
अणु
#अगर_अघोषित CONFIG_PARPORT_1284
	pr_err("parport: IEEE1284 not supported in this kernel\n");
	वापस -ENODEV;
#अन्यथा
	पूर्णांक mode = port->physport->ieee1284.mode;
	पूर्णांक addr = mode & IEEE1284_ADDR;
	माप_प्रकार (*fn) (काष्ठा parport *, व्योम *, माप_प्रकार, पूर्णांक);

	/* Ignore the device-ID-request bit and the address bit. */
	mode &= ~(IEEE1284_DEVICEID | IEEE1284_ADDR);

	/* Use the mode we're in. */
	चयन (mode) अणु
	हाल IEEE1284_MODE_COMPAT:
		/* अगर we can tri-state use BYTE mode instead of NIBBLE mode,
		 * अगर that fails, revert to NIBBLE mode -- ought to store somewhere
		 * the device's ability to do BYTE mode reverse transfers, so we don't
		 * end up needlessly calling negotiate(BYTE) repeately..  (fb)
		 */
		अगर ((port->physport->modes & PARPORT_MODE_TRISTATE) &&
		    !parport_negotiate (port, IEEE1284_MODE_BYTE)) अणु
			/* got पूर्णांकo BYTE mode OK */
			pr_debug("%s: Using byte mode\n", port->name);
			fn = port->ops->byte_पढ़ो_data;
			अवरोध;
		पूर्ण
		अगर (parport_negotiate (port, IEEE1284_MODE_NIBBLE)) अणु
			वापस -EIO;
		पूर्ण
		fallthrough;	/* to NIBBLE */
	हाल IEEE1284_MODE_NIBBLE:
		pr_debug("%s: Using nibble mode\n", port->name);
		fn = port->ops->nibble_पढ़ो_data;
		अवरोध;

	हाल IEEE1284_MODE_BYTE:
		pr_debug("%s: Using byte mode\n", port->name);
		fn = port->ops->byte_पढ़ो_data;
		अवरोध;

	हाल IEEE1284_MODE_EPP:
		pr_debug("%s: Using EPP mode\n", port->name);
		अगर (addr) अणु
			fn = port->ops->epp_पढ़ो_addr;
		पूर्ण अन्यथा अणु
			fn = port->ops->epp_पढ़ो_data;
		पूर्ण
		अवरोध;
	हाल IEEE1284_MODE_EPPSWE:
		pr_debug("%s: Using software-emulated EPP mode\n", port->name);
		अगर (addr) अणु
			fn = parport_ieee1284_epp_पढ़ो_addr;
		पूर्ण अन्यथा अणु
			fn = parport_ieee1284_epp_पढ़ो_data;
		पूर्ण
		अवरोध;
	हाल IEEE1284_MODE_ECP:
	हाल IEEE1284_MODE_ECPRLE:
		pr_debug("%s: Using ECP mode\n", port->name);
		fn = port->ops->ecp_पढ़ो_data;
		अवरोध;

	हाल IEEE1284_MODE_ECPSWE:
		pr_debug("%s: Using software-emulated ECP mode\n", port->name);
		fn = parport_ieee1284_ecp_पढ़ो_data;
		अवरोध;

	शेष:
		pr_debug("%s: Unknown mode 0x%02x\n",
			 port->name, port->physport->ieee1284.mode);
		वापस -ENOSYS;
	पूर्ण

	वापस (*fn) (port, buffer, len, 0);
#पूर्ण_अगर /* IEEE1284 support */
पूर्ण

/**
 *	parport_set_समयout - set the inactivity समयout क्रम a device
 *	@dev: device on a port
 *	@inactivity: inactivity समयout (in jअगरfies)
 *
 *	This sets the inactivity समयout क्रम a particular device on a
 *	port.  This affects functions like parport_रुको_peripheral().
 *	The special value 0 means not to call schedule() जबतक dealing
 *	with this device.
 *
 *	The वापस value is the previous inactivity समयout.
 *
 *	Any callers of parport_रुको_event() क्रम this device are woken
 *	up.
 */

दीर्घ parport_set_समयout (काष्ठा pardevice *dev, दीर्घ inactivity)
अणु
	दीर्घ पूर्णांक old = dev->समयout;

	dev->समयout = inactivity;

	अगर (dev->port->physport->cad == dev)
		parport_ieee1284_wakeup (dev->port);

	वापस old;
पूर्ण

/* Exported symbols क्रम modules. */

EXPORT_SYMBOL(parport_negotiate);
EXPORT_SYMBOL(parport_ग_लिखो);
EXPORT_SYMBOL(parport_पढ़ो);
EXPORT_SYMBOL(parport_रुको_peripheral);
EXPORT_SYMBOL(parport_रुको_event);
EXPORT_SYMBOL(parport_set_समयout);
EXPORT_SYMBOL(parport_ieee1284_पूर्णांकerrupt);
