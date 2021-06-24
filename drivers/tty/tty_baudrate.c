<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/termios.h>
#समावेश <linux/tty.h>
#समावेश <linux/export.h>
#समावेश "tty.h"


/*
 * Routine which वापसs the baud rate of the tty
 *
 * Note that the baud_table needs to be kept in sync with the
 * include/यंत्र/termbits.h file.
 */
अटल स्थिर speed_t baud_table[] = अणु
	0, 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400,
	4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800,
#अगर_घोषित __sparc__
	76800, 153600, 307200, 614400, 921600, 500000, 576000,
	1000000, 1152000, 1500000, 2000000
#अन्यथा
	500000, 576000, 921600, 1000000, 1152000, 1500000, 2000000,
	2500000, 3000000, 3500000, 4000000
#पूर्ण_अगर
पूर्ण;

अटल स्थिर tcflag_t baud_bits[] = अणु
	B0, B50, B75, B110, B134, B150, B200, B300, B600, B1200, B1800, B2400,
	B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800,
#अगर_घोषित __sparc__
	B76800, B153600, B307200, B614400, B921600, B500000, B576000,
	B1000000, B1152000, B1500000, B2000000
#अन्यथा
	B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000,
	B2500000, B3000000, B3500000, B4000000
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक n_baud_table = ARRAY_SIZE(baud_table);

/**
 *	tty_termios_baud_rate
 *	@termios: termios काष्ठाure
 *
 *	Convert termios baud rate data पूर्णांकo a speed. This should be called
 *	with the termios lock held अगर this termios is a terminal termios
 *	काष्ठाure. May change the termios data. Device drivers can call this
 *	function but should use ->c_[io]speed directly as they are updated.
 *
 *	Locking: none
 */

speed_t tty_termios_baud_rate(काष्ठा ktermios *termios)
अणु
	अचिन्हित पूर्णांक cbaud;

	cbaud = termios->c_cflag & CBAUD;

#अगर_घोषित BOTHER
	/* Magic token क्रम arbitrary speed via c_ispeed/c_ospeed */
	अगर (cbaud == BOTHER)
		वापस termios->c_ospeed;
#पूर्ण_अगर
	अगर (cbaud & CBAUDEX) अणु
		cbaud &= ~CBAUDEX;

		अगर (cbaud < 1 || cbaud + 15 > n_baud_table)
			termios->c_cflag &= ~CBAUDEX;
		अन्यथा
			cbaud += 15;
	पूर्ण
	वापस cbaud >= n_baud_table ? 0 : baud_table[cbaud];
पूर्ण
EXPORT_SYMBOL(tty_termios_baud_rate);

/**
 *	tty_termios_input_baud_rate
 *	@termios: termios काष्ठाure
 *
 *	Convert termios baud rate data पूर्णांकo a speed. This should be called
 *	with the termios lock held अगर this termios is a terminal termios
 *	काष्ठाure. May change the termios data. Device drivers can call this
 *	function but should use ->c_[io]speed directly as they are updated.
 *
 *	Locking: none
 */

speed_t tty_termios_input_baud_rate(काष्ठा ktermios *termios)
अणु
#अगर_घोषित IBSHIFT
	अचिन्हित पूर्णांक cbaud = (termios->c_cflag >> IBSHIFT) & CBAUD;

	अगर (cbaud == B0)
		वापस tty_termios_baud_rate(termios);
#अगर_घोषित BOTHER
	/* Magic token क्रम arbitrary speed via c_ispeed*/
	अगर (cbaud == BOTHER)
		वापस termios->c_ispeed;
#पूर्ण_अगर
	अगर (cbaud & CBAUDEX) अणु
		cbaud &= ~CBAUDEX;

		अगर (cbaud < 1 || cbaud + 15 > n_baud_table)
			termios->c_cflag &= ~(CBAUDEX << IBSHIFT);
		अन्यथा
			cbaud += 15;
	पूर्ण
	वापस cbaud >= n_baud_table ? 0 : baud_table[cbaud];
#अन्यथा	/* IBSHIFT */
	वापस tty_termios_baud_rate(termios);
#पूर्ण_अगर	/* IBSHIFT */
पूर्ण
EXPORT_SYMBOL(tty_termios_input_baud_rate);

/**
 *	tty_termios_encode_baud_rate
 *	@termios: ktermios काष्ठाure holding user requested state
 *	@ibaud: input speed
 *	@obaud: output speed
 *
 *	Encode the speeds set पूर्णांकo the passed termios काष्ठाure. This is
 *	used as a library helper क्रम drivers so that they can report back
 *	the actual speed selected when it dअगरfers from the speed requested
 *
 *	For maximal back compatibility with legacy SYS5/POSIX *nix behaviour
 *	we need to carefully set the bits when the user करोes not get the
 *	desired speed. We allow small margins and preserve as much of possible
 *	of the input पूर्णांकent to keep compatibility.
 *
 *	Locking: Caller should hold termios lock. This is alपढ़ोy held
 *	when calling this function from the driver termios handler.
 *
 *	The अगरdefs deal with platक्रमms whose owners have yet to update them
 *	and will all go away once this is करोne.
 */

व्योम tty_termios_encode_baud_rate(काष्ठा ktermios *termios,
				  speed_t ibaud, speed_t obaud)
अणु
	पूर्णांक i = 0;
	पूर्णांक अगरound = -1, ofound = -1;
	पूर्णांक iबंद = ibaud/50, oबंद = obaud/50;
	पूर्णांक ibinput = 0;

	अगर (obaud == 0)			/* CD dropped 		  */
		ibaud = 0;		/* Clear ibaud to be sure */

	termios->c_ispeed = ibaud;
	termios->c_ospeed = obaud;

#अगर_घोषित IBSHIFT
	अगर ((termios->c_cflag >> IBSHIFT) & CBAUD)
		ibinput = 1;	/* An input speed was specअगरied */
#पूर्ण_अगर
#अगर_घोषित BOTHER
	/* If the user asked क्रम a precise weird speed give a precise weird
	   answer. If they asked क्रम a Bfoo speed they may have problems
	   digesting non-exact replies so fuzz a bit */

	अगर ((termios->c_cflag & CBAUD) == BOTHER) अणु
		oबंद = 0;
		अगर (!ibinput)
			iबंद = 0;
	पूर्ण
	अगर (((termios->c_cflag >> IBSHIFT) & CBAUD) == BOTHER)
		iबंद = 0;
#पूर्ण_अगर
	termios->c_cflag &= ~CBAUD;
#अगर_घोषित IBSHIFT
	termios->c_cflag &= ~(CBAUD << IBSHIFT);
#पूर्ण_अगर

	/*
	 *	Our goal is to find a बंद match to the standard baud rate
	 *	वापसed. Walk the baud rate table and अगर we get a very बंद
	 *	match then report back the speed as a POSIX Bxxxx value by
	 *	preference
	 */

	करो अणु
		अगर (obaud - oबंद <= baud_table[i] &&
		    obaud + oबंद >= baud_table[i]) अणु
			termios->c_cflag |= baud_bits[i];
			ofound = i;
		पूर्ण
		अगर (ibaud - iबंद <= baud_table[i] &&
		    ibaud + iबंद >= baud_table[i]) अणु
			/* For the हाल input == output करोn't set IBAUD bits
			   अगर the user didn't करो so */
			अगर (ofound == i && !ibinput)
				अगरound  = i;
#अगर_घोषित IBSHIFT
			अन्यथा अणु
				अगरound = i;
				termios->c_cflag |= (baud_bits[i] << IBSHIFT);
			पूर्ण
#पूर्ण_अगर
		पूर्ण
	पूर्ण जबतक (++i < n_baud_table);

	/*
	 *	If we found no match then use BOTHER अगर provided or warn
	 *	the user their platक्रमm मुख्यtainer needs to wake up अगर not.
	 */
#अगर_घोषित BOTHER
	अगर (ofound == -1)
		termios->c_cflag |= BOTHER;
	/* Set exact input bits only अगर the input and output dअगरfer or the
	   user alपढ़ोy did */
	अगर (अगरound == -1 && (ibaud != obaud || ibinput))
		termios->c_cflag |= (BOTHER << IBSHIFT);
#अन्यथा
	अगर (अगरound == -1 || ofound == -1)
		pr_warn_once("tty: Unable to return correct speed data as your architecture needs updating.\n");
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(tty_termios_encode_baud_rate);

/**
 *	tty_encode_baud_rate		-	set baud rate of the tty
 *	@tty:   terminal device
 *	@ibaud: input baud rate
 *	@obaud: output baud rate
 *
 *	Update the current termios data क्रम the tty with the new speed
 *	settings. The caller must hold the termios_rwsem क्रम the tty in
 *	question.
 */

व्योम tty_encode_baud_rate(काष्ठा tty_काष्ठा *tty, speed_t ibaud, speed_t obaud)
अणु
	tty_termios_encode_baud_rate(&tty->termios, ibaud, obaud);
पूर्ण
EXPORT_SYMBOL_GPL(tty_encode_baud_rate);
