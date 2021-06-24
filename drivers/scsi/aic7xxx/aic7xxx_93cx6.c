<शैली गुरु>
/*
 * Interface क्रम the 93C66/56/46/26/06 serial eeprom parts.
 *
 * Copyright (c) 1995, 1996 Daniel M. Eischen
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aic7xxx_93cx6.c#19 $
 */

/*
 *   The inकाष्ठाion set of the 93C66/56/46/26/06 chips are as follows:
 *
 *               Start  OP	    *
 *     Function   Bit  Code  Address**  Data     Description
 *     -------------------------------------------------------------------
 *     READ        1    10   A5 - A0             Reads data stored in memory,
 *                                               starting at specअगरied address
 *     EWEN        1    00   11XXXX              Write enable must precede
 *                                               all programming modes
 *     ERASE       1    11   A5 - A0             Erase रेजिस्टर A5A4A3A2A1A0
 *     WRITE       1    01   A5 - A0   D15 - D0  Writes रेजिस्टर
 *     ERAL        1    00   10XXXX              Erase all रेजिस्टरs
 *     WRAL        1    00   01XXXX    D15 - D0  Writes to all रेजिस्टरs
 *     EWDS        1    00   00XXXX              Disables all programming
 *                                               inकाष्ठाions
 *     *Note: A value of X क्रम address is a करोn't care condition.
 *    **Note: There are 8 address bits क्रम the 93C56/66 chips unlike
 *	      the 93C46/26/06 chips which have 6 address bits.
 *
 *   The 93C46 has a four wire पूर्णांकerface: घड़ी, chip select, data in, and
 *   data out.  In order to perक्रमm one of the above functions, you need
 *   to enable the chip select क्रम a घड़ी period (typically a minimum of
 *   1 usec, with the घड़ी high and low a minimum of 750 and 250 nsec
 *   respectively).  While the chip select reमुख्यs high, you can घड़ी in
 *   the inकाष्ठाions (above) starting with the start bit, followed by the
 *   OP code, Address, and Data (अगर needed).  For the READ inकाष्ठाion, the
 *   requested 16-bit रेजिस्टर contents is पढ़ो from the data out line but
 *   is preceded by an initial zero (leading 0, followed by 16-bits, MSB
 *   first).  The घड़ी cycling from low to high initiates the next data
 *   bit to be sent from the chip.
 */

#समावेश "aic7xxx_osm.h"
#समावेश "aic7xxx_inline.h"
#समावेश "aic7xxx_93cx6.h"

/*
 * Right now, we only have to पढ़ो the SEEPROM.  But we make it easier to
 * add other 93Cx6 functions.
 */
काष्ठा seeprom_cmd अणु
	uपूर्णांक8_t len;
	uपूर्णांक8_t bits[11];
पूर्ण;

/* Short opcodes क्रम the c46 */
अटल स्थिर काष्ठा seeprom_cmd seeprom_ewen = अणु9, अणु1, 0, 0, 1, 1, 0, 0, 0, 0पूर्णपूर्ण;
अटल स्थिर काष्ठा seeprom_cmd seeprom_ewds = अणु9, अणु1, 0, 0, 0, 0, 0, 0, 0, 0पूर्णपूर्ण;

/* Long opcodes क्रम the C56/C66 */
अटल स्थिर काष्ठा seeprom_cmd seeprom_दीर्घ_ewen = अणु11, अणु1, 0, 0, 1, 1, 0, 0, 0, 0पूर्णपूर्ण;
अटल स्थिर काष्ठा seeprom_cmd seeprom_दीर्घ_ewds = अणु11, अणु1, 0, 0, 0, 0, 0, 0, 0, 0पूर्णपूर्ण;

/* Common opcodes */
अटल स्थिर काष्ठा seeprom_cmd seeprom_ग_लिखो = अणु3, अणु1, 0, 1पूर्णपूर्ण;
अटल स्थिर काष्ठा seeprom_cmd seeprom_पढ़ो  = अणु3, अणु1, 1, 0पूर्णपूर्ण;

/*
 * Wait क्रम the SEERDY to go high; about 800 ns.
 */
#घोषणा CLOCK_PULSE(sd, rdy)				\
	जबतक ((SEEPROM_STATUS_INB(sd) & rdy) == 0) अणु	\
		;  /* Do nothing */			\
	पूर्ण						\
	(व्योम)SEEPROM_INB(sd);	/* Clear घड़ी */

/*
 * Send a START condition and the given command
 */
अटल व्योम
send_seeprom_cmd(काष्ठा seeprom_descriptor *sd, स्थिर काष्ठा seeprom_cmd *cmd)
अणु
	uपूर्णांक8_t temp;
	पूर्णांक i = 0;

	/* Send chip select क्रम one घड़ी cycle. */
	temp = sd->sd_MS ^ sd->sd_CS;
	SEEPROM_OUTB(sd, temp ^ sd->sd_CK);
	CLOCK_PULSE(sd, sd->sd_RDY);

	क्रम (i = 0; i < cmd->len; i++) अणु
		अगर (cmd->bits[i] != 0)
			temp ^= sd->sd_DO;
		SEEPROM_OUTB(sd, temp);
		CLOCK_PULSE(sd, sd->sd_RDY);
		SEEPROM_OUTB(sd, temp ^ sd->sd_CK);
		CLOCK_PULSE(sd, sd->sd_RDY);
		अगर (cmd->bits[i] != 0)
			temp ^= sd->sd_DO;
	पूर्ण
पूर्ण

/*
 * Clear CS put the chip in the reset state, where it can रुको क्रम new commands.
 */
अटल व्योम
reset_seeprom(काष्ठा seeprom_descriptor *sd)
अणु
	uपूर्णांक8_t temp;

	temp = sd->sd_MS;
	SEEPROM_OUTB(sd, temp);
	CLOCK_PULSE(sd, sd->sd_RDY);
	SEEPROM_OUTB(sd, temp ^ sd->sd_CK);
	CLOCK_PULSE(sd, sd->sd_RDY);
	SEEPROM_OUTB(sd, temp);
	CLOCK_PULSE(sd, sd->sd_RDY);
पूर्ण

/*
 * Read the serial EEPROM and वापसs 1 अगर successful and 0 अगर
 * not successful.
 */
पूर्णांक
ahc_पढ़ो_seeprom(काष्ठा seeprom_descriptor *sd, uपूर्णांक16_t *buf,
		 u_पूर्णांक start_addr, u_पूर्णांक count)
अणु
	पूर्णांक i = 0;
	u_पूर्णांक k = 0;
	uपूर्णांक16_t v;
	uपूर्णांक8_t temp;

	/*
	 * Read the requested रेजिस्टरs of the seeprom.  The loop
	 * will range from 0 to count-1.
	 */
	क्रम (k = start_addr; k < count + start_addr; k++) अणु
		/*
		 * Now we're पढ़ोy to send the पढ़ो command followed by the
		 * address of the 16-bit रेजिस्टर we want to पढ़ो.
		 */
		send_seeprom_cmd(sd, &seeprom_पढ़ो);

		/* Send the 6 or 8 bit address (MSB first, LSB last). */
		temp = sd->sd_MS ^ sd->sd_CS;
		क्रम (i = (sd->sd_chip - 1); i >= 0; i--) अणु
			अगर ((k & (1 << i)) != 0)
				temp ^= sd->sd_DO;
			SEEPROM_OUTB(sd, temp);
			CLOCK_PULSE(sd, sd->sd_RDY);
			SEEPROM_OUTB(sd, temp ^ sd->sd_CK);
			CLOCK_PULSE(sd, sd->sd_RDY);
			अगर ((k & (1 << i)) != 0)
				temp ^= sd->sd_DO;
		पूर्ण

		/*
		 * Now पढ़ो the 16 bit रेजिस्टर.  An initial 0 precedes the
		 * रेजिस्टर contents which begins with bit 15 (MSB) and ends
		 * with bit 0 (LSB).  The initial 0 will be shअगरted off the
		 * top of our word as we let the loop run from 0 to 16.
		 */
		v = 0;
		क्रम (i = 16; i >= 0; i--) अणु
			SEEPROM_OUTB(sd, temp);
			CLOCK_PULSE(sd, sd->sd_RDY);
			v <<= 1;
			अगर (SEEPROM_DATA_INB(sd) & sd->sd_DI)
				v |= 1;
			SEEPROM_OUTB(sd, temp ^ sd->sd_CK);
			CLOCK_PULSE(sd, sd->sd_RDY);
		पूर्ण

		buf[k - start_addr] = v;

		/* Reset the chip select क्रम the next command cycle. */
		reset_seeprom(sd);
	पूर्ण
#अगर_घोषित AHC_DUMP_EEPROM
	prपूर्णांकk("\nSerial EEPROM:\n\t");
	क्रम (k = 0; k < count; k = k + 1) अणु
		अगर (((k % 8) == 0) && (k != 0)) अणु
			prपूर्णांकk(KERN_CONT "\n\t");
		पूर्ण
		prपूर्णांकk(KERN_CONT " 0x%x", buf[k]);
	पूर्ण
	prपूर्णांकk(KERN_CONT "\n");
#पूर्ण_अगर
	वापस (1);
पूर्ण

/*
 * Write the serial EEPROM and वापस 1 अगर successful and 0 अगर
 * not successful.
 */
पूर्णांक
ahc_ग_लिखो_seeprom(काष्ठा seeprom_descriptor *sd, uपूर्णांक16_t *buf,
		  u_पूर्णांक start_addr, u_पूर्णांक count)
अणु
	स्थिर काष्ठा seeprom_cmd *ewen, *ewds;
	uपूर्णांक16_t v;
	uपूर्णांक8_t temp;
	पूर्णांक i, k;

	/* Place the chip पूर्णांकo ग_लिखो-enable mode */
	अगर (sd->sd_chip == C46) अणु
		ewen = &seeprom_ewen;
		ewds = &seeprom_ewds;
	पूर्ण अन्यथा अगर (sd->sd_chip == C56_66) अणु
		ewen = &seeprom_दीर्घ_ewen;
		ewds = &seeprom_दीर्घ_ewds;
	पूर्ण अन्यथा अणु
		prपूर्णांकk("ahc_write_seeprom: unsupported seeprom type %d\n",
		       sd->sd_chip);
		वापस (0);
	पूर्ण

	send_seeprom_cmd(sd, ewen);
	reset_seeprom(sd);

	/* Write all requested data out to the seeprom. */
	temp = sd->sd_MS ^ sd->sd_CS;
	क्रम (k = start_addr; k < count + start_addr; k++) अणु
		/* Send the ग_लिखो command */
		send_seeprom_cmd(sd, &seeprom_ग_लिखो);

		/* Send the 6 or 8 bit address (MSB first). */
		क्रम (i = (sd->sd_chip - 1); i >= 0; i--) अणु
			अगर ((k & (1 << i)) != 0)
				temp ^= sd->sd_DO;
			SEEPROM_OUTB(sd, temp);
			CLOCK_PULSE(sd, sd->sd_RDY);
			SEEPROM_OUTB(sd, temp ^ sd->sd_CK);
			CLOCK_PULSE(sd, sd->sd_RDY);
			अगर ((k & (1 << i)) != 0)
				temp ^= sd->sd_DO;
		पूर्ण

		/* Write the 16 bit value, MSB first */
		v = buf[k - start_addr];
		क्रम (i = 15; i >= 0; i--) अणु
			अगर ((v & (1 << i)) != 0)
				temp ^= sd->sd_DO;
			SEEPROM_OUTB(sd, temp);
			CLOCK_PULSE(sd, sd->sd_RDY);
			SEEPROM_OUTB(sd, temp ^ sd->sd_CK);
			CLOCK_PULSE(sd, sd->sd_RDY);
			अगर ((v & (1 << i)) != 0)
				temp ^= sd->sd_DO;
		पूर्ण

		/* Wait क्रम the chip to complete the ग_लिखो */
		temp = sd->sd_MS;
		SEEPROM_OUTB(sd, temp);
		CLOCK_PULSE(sd, sd->sd_RDY);
		temp = sd->sd_MS ^ sd->sd_CS;
		करो अणु
			SEEPROM_OUTB(sd, temp);
			CLOCK_PULSE(sd, sd->sd_RDY);
			SEEPROM_OUTB(sd, temp ^ sd->sd_CK);
			CLOCK_PULSE(sd, sd->sd_RDY);
		पूर्ण जबतक ((SEEPROM_DATA_INB(sd) & sd->sd_DI) == 0);

		reset_seeprom(sd);
	पूर्ण

	/* Put the chip back पूर्णांकo ग_लिखो-protect mode */
	send_seeprom_cmd(sd, ewds);
	reset_seeprom(sd);

	वापस (1);
पूर्ण

पूर्णांक
ahc_verअगरy_cksum(काष्ठा seeprom_config *sc)
अणु
	पूर्णांक i;
	पूर्णांक maxaddr;
	uपूर्णांक32_t checksum;
	uपूर्णांक16_t *scarray;

	maxaddr = (माप(*sc)/2) - 1;
	checksum = 0;
	scarray = (uपूर्णांक16_t *)sc;

	क्रम (i = 0; i < maxaddr; i++)
		checksum = checksum + scarray[i];
	अगर (checksum == 0
	 || (checksum & 0xFFFF) != sc->checksum) अणु
		वापस (0);
	पूर्ण अन्यथा अणु
		वापस(1);
	पूर्ण
पूर्ण
