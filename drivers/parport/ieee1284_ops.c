<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* IEEE-1284 operations क्रम parport.
 *
 * This file is क्रम generic IEEE 1284 operations.  The idea is that
 * they are used by the low-level drivers.  If they have a special way
 * of करोing something, they can provide their own routines (and put
 * the function poपूर्णांकers in port->ops); अगर not, they can just use these
 * as a fallback.
 *
 * Note: Make no assumptions about hardware or architecture in this file!
 *
 * Author: Tim Waugh <tim@cyberelk.demon.co.uk>
 * Fixed AUTOFD polarity in ecp_क्रमward_to_reverse().  Fred Barnes, 1999
 * Software emulated EPP fixes, Fred Barnes, 04/2001.
 */


#समावेश <linux/module.h>
#समावेश <linux/parport.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uaccess.h>

#अघोषित DEBUG /* undef me क्रम production */

#अगर_घोषित CONFIG_LP_CONSOLE
#अघोषित DEBUG /* Don't want a garbled console */
#पूर्ण_अगर

/***                                *
 * One-way data transfer functions. *
 *                                ***/

/* Compatibility mode. */
माप_प्रकार parport_ieee1284_ग_लिखो_compat (काष्ठा parport *port,
				      स्थिर व्योम *buffer, माप_प्रकार len,
				      पूर्णांक flags)
अणु
	पूर्णांक no_irq = 1;
	sमाप_प्रकार count = 0;
	स्थिर अचिन्हित अक्षर *addr = buffer;
	अचिन्हित अक्षर byte;
	काष्ठा pardevice *dev = port->physport->cad;
	अचिन्हित अक्षर ctl = (PARPORT_CONTROL_SELECT
			     | PARPORT_CONTROL_INIT);

	अगर (port->irq != PARPORT_IRQ_NONE) अणु
		parport_enable_irq (port);
		no_irq = 0;
	पूर्ण

	port->physport->ieee1284.phase = IEEE1284_PH_FWD_DATA;
	parport_ग_लिखो_control (port, ctl);
	parport_data_क्रमward (port);
	जबतक (count < len) अणु
		अचिन्हित दीर्घ expire = jअगरfies + dev->समयout;
		दीर्घ रुको = msecs_to_jअगरfies(10);
		अचिन्हित अक्षर mask = (PARPORT_STATUS_ERROR
				      | PARPORT_STATUS_BUSY);
		अचिन्हित अक्षर val = (PARPORT_STATUS_ERROR
				     | PARPORT_STATUS_BUSY);

		/* Wait until the peripheral's पढ़ोy */
		करो अणु
			/* Is the peripheral पढ़ोy yet? */
			अगर (!parport_रुको_peripheral (port, mask, val))
				/* Skip the loop */
				जाओ पढ़ोy;

			/* Is the peripheral upset? */
			अगर ((parport_पढ़ो_status (port) &
			     (PARPORT_STATUS_PAPEROUT |
			      PARPORT_STATUS_SELECT |
			      PARPORT_STATUS_ERROR))
			    != (PARPORT_STATUS_SELECT |
				PARPORT_STATUS_ERROR))
				/* If nFault is निश्चितed (i.e. no
				 * error) and PAPEROUT and SELECT are
				 * just red herrings, give the driver
				 * a chance to check it's happy with
				 * that beक्रमe continuing. */
				जाओ stop;

			/* Have we run out of समय? */
			अगर (!समय_beक्रमe (jअगरfies, expire))
				अवरोध;

			/* Yield the port क्रम a जबतक.  If this is the
                           first समय around the loop, करोn't let go of
                           the port.  This way, we find out अगर we have
                           our पूर्णांकerrupt handler called. */
			अगर (count && no_irq) अणु
				parport_release (dev);
				schedule_समयout_पूर्णांकerruptible(रुको);
				parport_claim_or_block (dev);
			पूर्ण
			अन्यथा
				/* We must have the device claimed here */
				parport_रुको_event (port, रुको);

			/* Is there a संकेत pending? */
			अगर (संकेत_pending (current))
				अवरोध;

			/* Wait दीर्घer next समय. */
			रुको *= 2;
		पूर्ण जबतक (समय_beक्रमe (jअगरfies, expire));

		अगर (संकेत_pending (current))
			अवरोध;

		pr_debug("%s: Timed out\n", port->name);
		अवरोध;

	पढ़ोy:
		/* Write the अक्षरacter to the data lines. */
		byte = *addr++;
		parport_ग_लिखो_data (port, byte);
		udelay (1);

		/* Pulse strobe. */
		parport_ग_लिखो_control (port, ctl | PARPORT_CONTROL_STROBE);
		udelay (1); /* strobe */

		parport_ग_लिखो_control (port, ctl);
		udelay (1); /* hold */

		/* Assume the peripheral received it. */
		count++;

                /* Let another process run अगर it needs to. */
		अगर (समय_beक्रमe (jअगरfies, expire))
			अगर (!parport_yield_blocking (dev)
			    && need_resched())
				schedule ();
	पूर्ण
 stop:
	port->physport->ieee1284.phase = IEEE1284_PH_FWD_IDLE;

	वापस count;
पूर्ण

/* Nibble mode. */
माप_प्रकार parport_ieee1284_पढ़ो_nibble (काष्ठा parport *port, 
				     व्योम *buffer, माप_प्रकार len,
				     पूर्णांक flags)
अणु
#अगर_अघोषित CONFIG_PARPORT_1284
	वापस 0;
#अन्यथा
	अचिन्हित अक्षर *buf = buffer;
	पूर्णांक i;
	अचिन्हित अक्षर byte = 0;

	len *= 2; /* in nibbles */
	क्रम (i=0; i < len; i++) अणु
		अचिन्हित अक्षर nibble;

		/* Does the error line indicate end of data? */
		अगर (((i & 1) == 0) &&
		    (parport_पढ़ो_status(port) & PARPORT_STATUS_ERROR)) अणु
			जाओ end_of_data;
		पूर्ण

		/* Event 7: Set nAutoFd low. */
		parport_frob_control (port,
				      PARPORT_CONTROL_AUTOFD,
				      PARPORT_CONTROL_AUTOFD);

		/* Event 9: nAck goes low. */
		port->ieee1284.phase = IEEE1284_PH_REV_DATA;
		अगर (parport_रुको_peripheral (port,
					     PARPORT_STATUS_ACK, 0)) अणु
			/* Timeout -- no more data? */
			pr_debug("%s: Nibble timeout at event 9 (%d bytes)\n",
				 port->name, i / 2);
			parport_frob_control (port, PARPORT_CONTROL_AUTOFD, 0);
			अवरोध;
		पूर्ण


		/* Read a nibble. */
		nibble = parport_पढ़ो_status (port) >> 3;
		nibble &= ~8;
		अगर ((nibble & 0x10) == 0)
			nibble |= 8;
		nibble &= 0xf;

		/* Event 10: Set nAutoFd high. */
		parport_frob_control (port, PARPORT_CONTROL_AUTOFD, 0);

		/* Event 11: nAck goes high. */
		अगर (parport_रुको_peripheral (port,
					     PARPORT_STATUS_ACK,
					     PARPORT_STATUS_ACK)) अणु
			/* Timeout -- no more data? */
			pr_debug("%s: Nibble timeout at event 11\n",
				 port->name);
			अवरोध;
		पूर्ण

		अगर (i & 1) अणु
			/* Second nibble */
			byte |= nibble << 4;
			*buf++ = byte;
		पूर्ण अन्यथा 
			byte = nibble;
	पूर्ण

	अगर (i == len) अणु
		/* Read the last nibble without checking data avail. */
		अगर (parport_पढ़ो_status (port) & PARPORT_STATUS_ERROR) अणु
		end_of_data:
			pr_debug("%s: No more nibble data (%d bytes)\n",
				 port->name, i / 2);

			/* Go to reverse idle phase. */
			parport_frob_control (port,
					      PARPORT_CONTROL_AUTOFD,
					      PARPORT_CONTROL_AUTOFD);
			port->physport->ieee1284.phase = IEEE1284_PH_REV_IDLE;
		पूर्ण
		अन्यथा
			port->physport->ieee1284.phase = IEEE1284_PH_HBUSY_DAVAIL;
	पूर्ण

	वापस i/2;
#पूर्ण_अगर /* IEEE1284 support */
पूर्ण

/* Byte mode. */
माप_प्रकार parport_ieee1284_पढ़ो_byte (काष्ठा parport *port,
				   व्योम *buffer, माप_प्रकार len,
				   पूर्णांक flags)
अणु
#अगर_अघोषित CONFIG_PARPORT_1284
	वापस 0;
#अन्यथा
	अचिन्हित अक्षर *buf = buffer;
	sमाप_प्रकार count = 0;

	क्रम (count = 0; count < len; count++) अणु
		अचिन्हित अक्षर byte;

		/* Data available? */
		अगर (parport_पढ़ो_status (port) & PARPORT_STATUS_ERROR) अणु
			जाओ end_of_data;
		पूर्ण

		/* Event 14: Place data bus in high impedance state. */
		parport_data_reverse (port);

		/* Event 7: Set nAutoFd low. */
		parport_frob_control (port,
				      PARPORT_CONTROL_AUTOFD,
				      PARPORT_CONTROL_AUTOFD);

		/* Event 9: nAck goes low. */
		port->physport->ieee1284.phase = IEEE1284_PH_REV_DATA;
		अगर (parport_रुको_peripheral (port,
					     PARPORT_STATUS_ACK,
					     0)) अणु
			/* Timeout -- no more data? */
			parport_frob_control (port, PARPORT_CONTROL_AUTOFD,
						 0);
			pr_debug("%s: Byte timeout at event 9\n", port->name);
			अवरोध;
		पूर्ण

		byte = parport_पढ़ो_data (port);
		*buf++ = byte;

		/* Event 10: Set nAutoFd high */
		parport_frob_control (port, PARPORT_CONTROL_AUTOFD, 0);

		/* Event 11: nAck goes high. */
		अगर (parport_रुको_peripheral (port,
					     PARPORT_STATUS_ACK,
					     PARPORT_STATUS_ACK)) अणु
			/* Timeout -- no more data? */
			pr_debug("%s: Byte timeout at event 11\n", port->name);
			अवरोध;
		पूर्ण

		/* Event 16: Set nStrobe low. */
		parport_frob_control (port,
				      PARPORT_CONTROL_STROBE,
				      PARPORT_CONTROL_STROBE);
		udelay (5);

		/* Event 17: Set nStrobe high. */
		parport_frob_control (port, PARPORT_CONTROL_STROBE, 0);
	पूर्ण

	अगर (count == len) अणु
		/* Read the last byte without checking data avail. */
		अगर (parport_पढ़ो_status (port) & PARPORT_STATUS_ERROR) अणु
		end_of_data:
			pr_debug("%s: No more byte data (%zd bytes)\n",
				 port->name, count);

			/* Go to reverse idle phase. */
			parport_frob_control (port,
					      PARPORT_CONTROL_AUTOFD,
					      PARPORT_CONTROL_AUTOFD);
			port->physport->ieee1284.phase = IEEE1284_PH_REV_IDLE;
		पूर्ण
		अन्यथा
			port->physport->ieee1284.phase = IEEE1284_PH_HBUSY_DAVAIL;
	पूर्ण

	वापस count;
#पूर्ण_अगर /* IEEE1284 support */
पूर्ण

/***              *
 * ECP Functions. *
 *              ***/

#अगर_घोषित CONFIG_PARPORT_1284

अटल अंतरभूत
पूर्णांक ecp_क्रमward_to_reverse (काष्ठा parport *port)
अणु
	पूर्णांक retval;

	/* Event 38: Set nAutoFd low */
	parport_frob_control (port,
			      PARPORT_CONTROL_AUTOFD,
			      PARPORT_CONTROL_AUTOFD);
	parport_data_reverse (port);
	udelay (5);

	/* Event 39: Set nInit low to initiate bus reversal */
	parport_frob_control (port,
			      PARPORT_CONTROL_INIT,
			      0);

	/* Event 40: PError goes low */
	retval = parport_रुको_peripheral (port,
					  PARPORT_STATUS_PAPEROUT, 0);

	अगर (!retval) अणु
		pr_debug("%s: ECP direction: reverse\n", port->name);
		port->ieee1284.phase = IEEE1284_PH_REV_IDLE;
	पूर्ण अन्यथा अणु
		pr_debug("%s: ECP direction: failed to reverse\n", port->name);
		port->ieee1284.phase = IEEE1284_PH_ECP_सूची_UNKNOWN;
	पूर्ण

	वापस retval;
पूर्ण

अटल अंतरभूत
पूर्णांक ecp_reverse_to_क्रमward (काष्ठा parport *port)
अणु
	पूर्णांक retval;

	/* Event 47: Set nInit high */
	parport_frob_control (port,
			      PARPORT_CONTROL_INIT
			      | PARPORT_CONTROL_AUTOFD,
			      PARPORT_CONTROL_INIT
			      | PARPORT_CONTROL_AUTOFD);

	/* Event 49: PError goes high */
	retval = parport_रुको_peripheral (port,
					  PARPORT_STATUS_PAPEROUT,
					  PARPORT_STATUS_PAPEROUT);

	अगर (!retval) अणु
		parport_data_क्रमward (port);
		pr_debug("%s: ECP direction: forward\n", port->name);
		port->ieee1284.phase = IEEE1284_PH_FWD_IDLE;
	पूर्ण अन्यथा अणु
		pr_debug("%s: ECP direction: failed to switch forward\n",
			 port->name);
		port->ieee1284.phase = IEEE1284_PH_ECP_सूची_UNKNOWN;
	पूर्ण


	वापस retval;
पूर्ण

#पूर्ण_अगर /* IEEE1284 support */

/* ECP mode, क्रमward channel, data. */
माप_प्रकार parport_ieee1284_ecp_ग_लिखो_data (काष्ठा parport *port,
					स्थिर व्योम *buffer, माप_प्रकार len,
					पूर्णांक flags)
अणु
#अगर_अघोषित CONFIG_PARPORT_1284
	वापस 0;
#अन्यथा
	स्थिर अचिन्हित अक्षर *buf = buffer;
	माप_प्रकार written;
	पूर्णांक retry;

	port = port->physport;

	अगर (port->ieee1284.phase != IEEE1284_PH_FWD_IDLE)
		अगर (ecp_reverse_to_क्रमward (port))
			वापस 0;

	port->ieee1284.phase = IEEE1284_PH_FWD_DATA;

	/* HostAck high (data, not command) */
	parport_frob_control (port,
			      PARPORT_CONTROL_AUTOFD
			      | PARPORT_CONTROL_STROBE
			      | PARPORT_CONTROL_INIT,
			      PARPORT_CONTROL_INIT);
	क्रम (written = 0; written < len; written++, buf++) अणु
		अचिन्हित दीर्घ expire = jअगरfies + port->cad->समयout;
		अचिन्हित अक्षर byte;

		byte = *buf;
	try_again:
		parport_ग_लिखो_data (port, byte);
		parport_frob_control (port, PARPORT_CONTROL_STROBE,
				      PARPORT_CONTROL_STROBE);
		udelay (5);
		क्रम (retry = 0; retry < 100; retry++) अणु
			अगर (!parport_रुको_peripheral (port,
						      PARPORT_STATUS_BUSY, 0))
				जाओ success;

			अगर (संकेत_pending (current)) अणु
				parport_frob_control (port,
						      PARPORT_CONTROL_STROBE,
						      0);
				अवरोध;
			पूर्ण
		पूर्ण

		/* Time क्रम Host Transfer Recovery (page 41 of IEEE1284) */
		pr_debug("%s: ECP transfer stalled!\n", port->name);

		parport_frob_control (port, PARPORT_CONTROL_INIT,
				      PARPORT_CONTROL_INIT);
		udelay (50);
		अगर (parport_पढ़ो_status (port) & PARPORT_STATUS_PAPEROUT) अणु
			/* It's buggered. */
			parport_frob_control (port, PARPORT_CONTROL_INIT, 0);
			अवरोध;
		पूर्ण

		parport_frob_control (port, PARPORT_CONTROL_INIT, 0);
		udelay (50);
		अगर (!(parport_पढ़ो_status (port) & PARPORT_STATUS_PAPEROUT))
			अवरोध;

		pr_debug("%s: Host transfer recovered\n", port->name);

		अगर (समय_after_eq (jअगरfies, expire)) अवरोध;
		जाओ try_again;
	success:
		parport_frob_control (port, PARPORT_CONTROL_STROBE, 0);
		udelay (5);
		अगर (parport_रुको_peripheral (port,
					     PARPORT_STATUS_BUSY,
					     PARPORT_STATUS_BUSY))
			/* Peripheral hasn't accepted the data. */
			अवरोध;
	पूर्ण

	port->ieee1284.phase = IEEE1284_PH_FWD_IDLE;

	वापस written;
#पूर्ण_अगर /* IEEE1284 support */
पूर्ण

/* ECP mode, reverse channel, data. */
माप_प्रकार parport_ieee1284_ecp_पढ़ो_data (काष्ठा parport *port,
				       व्योम *buffer, माप_प्रकार len, पूर्णांक flags)
अणु
#अगर_अघोषित CONFIG_PARPORT_1284
	वापस 0;
#अन्यथा
	काष्ठा pardevice *dev = port->cad;
	अचिन्हित अक्षर *buf = buffer;
	पूर्णांक rle_count = 0; /* shut gcc up */
	अचिन्हित अक्षर ctl;
	पूर्णांक rle = 0;
	sमाप_प्रकार count = 0;

	port = port->physport;

	अगर (port->ieee1284.phase != IEEE1284_PH_REV_IDLE)
		अगर (ecp_क्रमward_to_reverse (port))
			वापस 0;

	port->ieee1284.phase = IEEE1284_PH_REV_DATA;

	/* Set HostAck low to start accepting data. */
	ctl = parport_पढ़ो_control (port);
	ctl &= ~(PARPORT_CONTROL_STROBE | PARPORT_CONTROL_INIT |
		 PARPORT_CONTROL_AUTOFD);
	parport_ग_लिखो_control (port,
			       ctl | PARPORT_CONTROL_AUTOFD);
	जबतक (count < len) अणु
		अचिन्हित दीर्घ expire = jअगरfies + dev->समयout;
		अचिन्हित अक्षर byte;
		पूर्णांक command;

		/* Event 43: Peripheral sets nAck low. It can take as
                   दीर्घ as it wants. */
		जबतक (parport_रुको_peripheral (port, PARPORT_STATUS_ACK, 0)) अणु
			/* The peripheral hasn't given us data in
			   35ms.  If we have data to give back to the
			   caller, करो it now. */
			अगर (count)
				जाओ out;

			/* If we've used up all the समय we were allowed,
			   give up altogether. */
			अगर (!समय_beक्रमe (jअगरfies, expire))
				जाओ out;

			/* Yield the port क्रम a जबतक. */
			अगर (count && dev->port->irq != PARPORT_IRQ_NONE) अणु
				parport_release (dev);
				schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(40));
				parport_claim_or_block (dev);
			पूर्ण
			अन्यथा
				/* We must have the device claimed here. */
				parport_रुको_event (port, msecs_to_jअगरfies(40));

			/* Is there a संकेत pending? */
			अगर (संकेत_pending (current))
				जाओ out;
		पूर्ण

		/* Is this a command? */
		अगर (rle)
			/* The last byte was a run-length count, so
                           this can't be as well. */
			command = 0;
		अन्यथा
			command = (parport_पढ़ो_status (port) &
				   PARPORT_STATUS_BUSY) ? 1 : 0;

		/* Read the data. */
		byte = parport_पढ़ो_data (port);

		/* If this is a channel command, rather than an RLE
                   command or a normal data byte, करोn't accept it. */
		अगर (command) अणु
			अगर (byte & 0x80) अणु
				pr_debug("%s: stopping short at channel command (%02x)\n",
					 port->name, byte);
				जाओ out;
			पूर्ण
			अन्यथा अगर (port->ieee1284.mode != IEEE1284_MODE_ECPRLE)
				pr_debug("%s: device illegally using RLE; accepting anyway\n",
					 port->name);

			rle_count = byte + 1;

			/* Are we allowed to पढ़ो that many bytes? */
			अगर (rle_count > (len - count)) अणु
				pr_debug("%s: leaving %d RLE bytes for next time\n",
					 port->name, rle_count);
				अवरोध;
			पूर्ण

			rle = 1;
		पूर्ण

		/* Event 44: Set HostAck high, acknowledging handshake. */
		parport_ग_लिखो_control (port, ctl);

		/* Event 45: The peripheral has 35ms to set nAck high. */
		अगर (parport_रुको_peripheral (port, PARPORT_STATUS_ACK,
					     PARPORT_STATUS_ACK)) अणु
			/* It's gone wrong.  Return what data we have
                           to the caller. */
			pr_debug("ECP read timed out at 45\n");

			अगर (command)
				pr_warn("%s: command ignored (%02x)\n",
					port->name, byte);

			अवरोध;
		पूर्ण

		/* Event 46: Set HostAck low and accept the data. */
		parport_ग_लिखो_control (port,
				       ctl | PARPORT_CONTROL_AUTOFD);

		/* If we just पढ़ो a run-length count, fetch the data. */
		अगर (command)
			जारी;

		/* If this is the byte after a run-length count, decompress. */
		अगर (rle) अणु
			rle = 0;
			स_रखो (buf, byte, rle_count);
			buf += rle_count;
			count += rle_count;
			pr_debug("%s: decompressed to %d bytes\n",
				 port->name, rle_count);
		पूर्ण अन्यथा अणु
			/* Normal data byte. */
			*buf = byte;
			buf++, count++;
		पूर्ण
	पूर्ण

 out:
	port->ieee1284.phase = IEEE1284_PH_REV_IDLE;
	वापस count;
#पूर्ण_अगर /* IEEE1284 support */
पूर्ण

/* ECP mode, क्रमward channel, commands. */
माप_प्रकार parport_ieee1284_ecp_ग_लिखो_addr (काष्ठा parport *port,
					स्थिर व्योम *buffer, माप_प्रकार len,
					पूर्णांक flags)
अणु
#अगर_अघोषित CONFIG_PARPORT_1284
	वापस 0;
#अन्यथा
	स्थिर अचिन्हित अक्षर *buf = buffer;
	माप_प्रकार written;
	पूर्णांक retry;

	port = port->physport;

	अगर (port->ieee1284.phase != IEEE1284_PH_FWD_IDLE)
		अगर (ecp_reverse_to_क्रमward (port))
			वापस 0;

	port->ieee1284.phase = IEEE1284_PH_FWD_DATA;

	/* HostAck low (command, not data) */
	parport_frob_control (port,
			      PARPORT_CONTROL_AUTOFD
			      | PARPORT_CONTROL_STROBE
			      | PARPORT_CONTROL_INIT,
			      PARPORT_CONTROL_AUTOFD
			      | PARPORT_CONTROL_INIT);
	क्रम (written = 0; written < len; written++, buf++) अणु
		अचिन्हित दीर्घ expire = jअगरfies + port->cad->समयout;
		अचिन्हित अक्षर byte;

		byte = *buf;
	try_again:
		parport_ग_लिखो_data (port, byte);
		parport_frob_control (port, PARPORT_CONTROL_STROBE,
				      PARPORT_CONTROL_STROBE);
		udelay (5);
		क्रम (retry = 0; retry < 100; retry++) अणु
			अगर (!parport_रुको_peripheral (port,
						      PARPORT_STATUS_BUSY, 0))
				जाओ success;

			अगर (संकेत_pending (current)) अणु
				parport_frob_control (port,
						      PARPORT_CONTROL_STROBE,
						      0);
				अवरोध;
			पूर्ण
		पूर्ण

		/* Time क्रम Host Transfer Recovery (page 41 of IEEE1284) */
		pr_debug("%s: ECP transfer stalled!\n", port->name);

		parport_frob_control (port, PARPORT_CONTROL_INIT,
				      PARPORT_CONTROL_INIT);
		udelay (50);
		अगर (parport_पढ़ो_status (port) & PARPORT_STATUS_PAPEROUT) अणु
			/* It's buggered. */
			parport_frob_control (port, PARPORT_CONTROL_INIT, 0);
			अवरोध;
		पूर्ण

		parport_frob_control (port, PARPORT_CONTROL_INIT, 0);
		udelay (50);
		अगर (!(parport_पढ़ो_status (port) & PARPORT_STATUS_PAPEROUT))
			अवरोध;

		pr_debug("%s: Host transfer recovered\n", port->name);

		अगर (समय_after_eq (jअगरfies, expire)) अवरोध;
		जाओ try_again;
	success:
		parport_frob_control (port, PARPORT_CONTROL_STROBE, 0);
		udelay (5);
		अगर (parport_रुको_peripheral (port,
					     PARPORT_STATUS_BUSY,
					     PARPORT_STATUS_BUSY))
			/* Peripheral hasn't accepted the data. */
			अवरोध;
	पूर्ण

	port->ieee1284.phase = IEEE1284_PH_FWD_IDLE;

	वापस written;
#पूर्ण_अगर /* IEEE1284 support */
पूर्ण

/***              *
 * EPP functions. *
 *              ***/

/* EPP mode, क्रमward channel, data. */
माप_प्रकार parport_ieee1284_epp_ग_लिखो_data (काष्ठा parport *port,
					स्थिर व्योम *buffer, माप_प्रकार len,
					पूर्णांक flags)
अणु
	अचिन्हित अक्षर *bp = (अचिन्हित अक्षर *) buffer;
	माप_प्रकार ret = 0;

	/* set EPP idle state (just to make sure) with strobe low */
	parport_frob_control (port,
			      PARPORT_CONTROL_STROBE |
			      PARPORT_CONTROL_AUTOFD |
			      PARPORT_CONTROL_SELECT |
			      PARPORT_CONTROL_INIT,
			      PARPORT_CONTROL_STROBE |
			      PARPORT_CONTROL_INIT);
	port->ops->data_क्रमward (port);
	क्रम (; len > 0; len--, bp++) अणु
		/* Event 62: Write data and set स्वतःfd low */
		parport_ग_लिखो_data (port, *bp);
		parport_frob_control (port, PARPORT_CONTROL_AUTOFD,
				      PARPORT_CONTROL_AUTOFD);

		/* Event 58: रुको क्रम busy (nWait) to go high */
		अगर (parport_poll_peripheral (port, PARPORT_STATUS_BUSY, 0, 10))
			अवरोध;

		/* Event 63: set nAutoFd (nDStrb) high */
		parport_frob_control (port, PARPORT_CONTROL_AUTOFD, 0);

		/* Event 60: रुको क्रम busy (nWait) to go low */
		अगर (parport_poll_peripheral (port, PARPORT_STATUS_BUSY,
					     PARPORT_STATUS_BUSY, 5))
			अवरोध;

		ret++;
	पूर्ण

	/* Event 61: set strobe (nWrite) high */
	parport_frob_control (port, PARPORT_CONTROL_STROBE, 0);

	वापस ret;
पूर्ण

/* EPP mode, reverse channel, data. */
माप_प्रकार parport_ieee1284_epp_पढ़ो_data (काष्ठा parport *port,
				       व्योम *buffer, माप_प्रकार len,
				       पूर्णांक flags)
अणु
	अचिन्हित अक्षर *bp = (अचिन्हित अक्षर *) buffer;
	अचिन्हित ret = 0;

	/* set EPP idle state (just to make sure) with strobe high */
	parport_frob_control (port,
			      PARPORT_CONTROL_STROBE |
			      PARPORT_CONTROL_AUTOFD |
			      PARPORT_CONTROL_SELECT |
			      PARPORT_CONTROL_INIT,
			      PARPORT_CONTROL_INIT);
	port->ops->data_reverse (port);
	क्रम (; len > 0; len--, bp++) अणु
		/* Event 67: set nAutoFd (nDStrb) low */
		parport_frob_control (port,
				      PARPORT_CONTROL_AUTOFD,
				      PARPORT_CONTROL_AUTOFD);
		/* Event 58: रुको क्रम Busy to go high */
		अगर (parport_रुको_peripheral (port, PARPORT_STATUS_BUSY, 0)) अणु
			अवरोध;
		पूर्ण

		*bp = parport_पढ़ो_data (port);

		/* Event 63: set nAutoFd (nDStrb) high */
		parport_frob_control (port, PARPORT_CONTROL_AUTOFD, 0);

		/* Event 60: रुको क्रम Busy to go low */
		अगर (parport_poll_peripheral (port, PARPORT_STATUS_BUSY,
					     PARPORT_STATUS_BUSY, 5)) अणु
			अवरोध;
		पूर्ण

		ret++;
	पूर्ण
	port->ops->data_क्रमward (port);

	वापस ret;
पूर्ण

/* EPP mode, क्रमward channel, addresses. */
माप_प्रकार parport_ieee1284_epp_ग_लिखो_addr (काष्ठा parport *port,
					स्थिर व्योम *buffer, माप_प्रकार len,
					पूर्णांक flags)
अणु
	अचिन्हित अक्षर *bp = (अचिन्हित अक्षर *) buffer;
	माप_प्रकार ret = 0;

	/* set EPP idle state (just to make sure) with strobe low */
	parport_frob_control (port,
			      PARPORT_CONTROL_STROBE |
			      PARPORT_CONTROL_AUTOFD |
			      PARPORT_CONTROL_SELECT |
			      PARPORT_CONTROL_INIT,
			      PARPORT_CONTROL_STROBE |
			      PARPORT_CONTROL_INIT);
	port->ops->data_क्रमward (port);
	क्रम (; len > 0; len--, bp++) अणु
		/* Event 56: Write data and set nAStrb low. */
		parport_ग_लिखो_data (port, *bp);
		parport_frob_control (port, PARPORT_CONTROL_SELECT,
				      PARPORT_CONTROL_SELECT);

		/* Event 58: रुको क्रम busy (nWait) to go high */
		अगर (parport_poll_peripheral (port, PARPORT_STATUS_BUSY, 0, 10))
			अवरोध;

		/* Event 59: set nAStrb high */
		parport_frob_control (port, PARPORT_CONTROL_SELECT, 0);

		/* Event 60: रुको क्रम busy (nWait) to go low */
		अगर (parport_poll_peripheral (port, PARPORT_STATUS_BUSY,
					     PARPORT_STATUS_BUSY, 5))
			अवरोध;

		ret++;
	पूर्ण

	/* Event 61: set strobe (nWrite) high */
	parport_frob_control (port, PARPORT_CONTROL_STROBE, 0);

	वापस ret;
पूर्ण

/* EPP mode, reverse channel, addresses. */
माप_प्रकार parport_ieee1284_epp_पढ़ो_addr (काष्ठा parport *port,
				       व्योम *buffer, माप_प्रकार len,
				       पूर्णांक flags)
अणु
	अचिन्हित अक्षर *bp = (अचिन्हित अक्षर *) buffer;
	अचिन्हित ret = 0;

	/* Set EPP idle state (just to make sure) with strobe high */
	parport_frob_control (port,
			      PARPORT_CONTROL_STROBE |
			      PARPORT_CONTROL_AUTOFD |
			      PARPORT_CONTROL_SELECT |
			      PARPORT_CONTROL_INIT,
			      PARPORT_CONTROL_INIT);
	port->ops->data_reverse (port);
	क्रम (; len > 0; len--, bp++) अणु
		/* Event 64: set nSelectIn (nAStrb) low */
		parport_frob_control (port, PARPORT_CONTROL_SELECT,
				      PARPORT_CONTROL_SELECT);

		/* Event 58: रुको क्रम Busy to go high */
		अगर (parport_रुको_peripheral (port, PARPORT_STATUS_BUSY, 0)) अणु
			अवरोध;
		पूर्ण

		*bp = parport_पढ़ो_data (port);

		/* Event 59: set nSelectIn (nAStrb) high */
		parport_frob_control (port, PARPORT_CONTROL_SELECT,
				      0);

		/* Event 60: रुको क्रम Busy to go low */
		अगर (parport_poll_peripheral (port, PARPORT_STATUS_BUSY, 
					     PARPORT_STATUS_BUSY, 5))
			अवरोध;

		ret++;
	पूर्ण
	port->ops->data_क्रमward (port);

	वापस ret;
पूर्ण

EXPORT_SYMBOL(parport_ieee1284_ecp_ग_लिखो_data);
EXPORT_SYMBOL(parport_ieee1284_ecp_पढ़ो_data);
EXPORT_SYMBOL(parport_ieee1284_ecp_ग_लिखो_addr);
EXPORT_SYMBOL(parport_ieee1284_ग_लिखो_compat);
EXPORT_SYMBOL(parport_ieee1284_पढ़ो_nibble);
EXPORT_SYMBOL(parport_ieee1284_पढ़ो_byte);
EXPORT_SYMBOL(parport_ieee1284_epp_ग_लिखो_data);
EXPORT_SYMBOL(parport_ieee1284_epp_पढ़ो_data);
EXPORT_SYMBOL(parport_ieee1284_epp_ग_लिखो_addr);
EXPORT_SYMBOL(parport_ieee1284_epp_पढ़ो_addr);
