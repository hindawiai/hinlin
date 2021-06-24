<शैली गुरु>
/*
 * Interface to the 93C46/56 serial EEPROM that is used to store BIOS
 * settings क्रम the aic7xxx based adaptec SCSI controllers.  It can
 * also be used क्रम 93C26 and 93C06 serial EEPROMS.
 *
 * Copyright (c) 1994, 1995, 2000 Justin T. Gibbs.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aic7xxx_93cx6.h#12 $
 *
 * $FreeBSD$
 */
#अगर_अघोषित _AIC7XXX_93CX6_H_
#घोषणा _AIC7XXX_93CX6_H_

प्रकार क्रमागत अणु
	C46 = 6,
	C56_66 = 8
पूर्ण seeprom_chip_t;

काष्ठा seeprom_descriptor अणु
	काष्ठा ahc_softc *sd_ahc;
	u_पूर्णांक sd_control_offset;
	u_पूर्णांक sd_status_offset;
	u_पूर्णांक sd_dataout_offset;
	seeprom_chip_t sd_chip;
	uपूर्णांक16_t sd_MS;
	uपूर्णांक16_t sd_RDY;
	uपूर्णांक16_t sd_CS;
	uपूर्णांक16_t sd_CK;
	uपूर्णांक16_t sd_DO;
	uपूर्णांक16_t sd_DI;
पूर्ण;

/*
 * This function will पढ़ो count 16-bit words from the serial EEPROM and
 * वापस their value in buf.  The port address of the aic7xxx serial EEPROM
 * control रेजिस्टर is passed in as offset.  The following parameters are
 * also passed in:
 *
 *   CS  - Chip select
 *   CK  - Clock
 *   DO  - Data out
 *   DI  - Data in
 *   RDY - SEEPROM पढ़ोy
 *   MS  - Memory port mode select
 *
 *  A failed पढ़ो attempt वापसs 0, and a successful पढ़ो वापसs 1.
 */

#घोषणा	SEEPROM_INB(sd) \
	ahc_inb(sd->sd_ahc, sd->sd_control_offset)
#घोषणा	SEEPROM_OUTB(sd, value)					\
करो अणु								\
	ahc_outb(sd->sd_ahc, sd->sd_control_offset, value);	\
	ahc_flush_device_ग_लिखोs(sd->sd_ahc);			\
पूर्ण जबतक(0)

#घोषणा	SEEPROM_STATUS_INB(sd) \
	ahc_inb(sd->sd_ahc, sd->sd_status_offset)
#घोषणा	SEEPROM_DATA_INB(sd) \
	ahc_inb(sd->sd_ahc, sd->sd_dataout_offset)

पूर्णांक ahc_पढ़ो_seeprom(काष्ठा seeprom_descriptor *sd, uपूर्णांक16_t *buf,
		     u_पूर्णांक start_addr, u_पूर्णांक count);
पूर्णांक ahc_ग_लिखो_seeprom(काष्ठा seeprom_descriptor *sd, uपूर्णांक16_t *buf,
		      u_पूर्णांक start_addr, u_पूर्णांक count);
पूर्णांक ahc_verअगरy_cksum(काष्ठा seeprom_config *sc);

#पूर्ण_अगर /* _AIC7XXX_93CX6_H_ */
