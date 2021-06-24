<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Driver क्रम Midiman Porपंचांगan2x4 parallel port midi पूर्णांकerface
 *
 *   Copyright (c) by Levent Guenकरोgdu <levon@feature-it.com>
 *
 * ChangeLog
 * Jan 24 2007 Matthias Koenig <mkoenig@suse.de>
 *      - cleanup and reग_लिखो
 * Sep 30 2004 Tobias Gehrig <tobias@gehrig.tk>
 *      - source code cleanup
 * Sep 03 2004 Tobias Gehrig <tobias@gehrig.tk>
 *      - fixed compilation problem with alsa 1.0.6a (हटाओd MODULE_CLASSES,
 *        MODULE_PARM_SYNTAX and changed MODULE_DEVICES to
 *        MODULE_SUPPORTED_DEVICE)
 * Mar 24 2004 Tobias Gehrig <tobias@gehrig.tk>
 *      - added 2.6 kernel support
 * Mar 18 2004 Tobias Gehrig <tobias@gehrig.tk>
 *      - added parport_unरेजिस्टर_driver to the startup routine अगर the driver fails to detect a porपंचांगan
 *      - added support क्रम all 4 output ports in porपंचांगan_puपंचांगidi
 * Mar 17 2004 Tobias Gehrig <tobias@gehrig.tk>
 *      - added checks क्रम खोलोed input device in पूर्णांकerrupt handler
 * Feb 20 2004 Tobias Gehrig <tobias@gehrig.tk>
 *      - ported from alsa 0.5 to 1.0
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/parport.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/control.h>

#घोषणा CARD_NAME "Portman 2x4"
#घोषणा DRIVER_NAME "portman"
#घोषणा PLATFORM_DRIVER "snd_portman2x4"

अटल पूर्णांक index[SNDRV_CARDS]  = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS]   = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

अटल काष्ठा platक्रमm_device *platक्रमm_devices[SNDRV_CARDS]; 
अटल पूर्णांक device_count;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for " CARD_NAME " soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for " CARD_NAME " soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable " CARD_NAME " soundcard.");

MODULE_AUTHOR("Levent Guendogdu, Tobias Gehrig, Matthias Koenig");
MODULE_DESCRIPTION("Midiman Portman2x4");
MODULE_LICENSE("GPL");

/*********************************************************************
 * Chip specअगरic
 *********************************************************************/
#घोषणा PORTMAN_NUM_INPUT_PORTS 2
#घोषणा PORTMAN_NUM_OUTPUT_PORTS 4

काष्ठा porपंचांगan अणु
	spinlock_t reg_lock;
	काष्ठा snd_card *card;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा pardevice *pardev;
	पूर्णांक खोलो_count;
	पूर्णांक mode[PORTMAN_NUM_INPUT_PORTS];
	काष्ठा snd_rawmidi_substream *midi_input[PORTMAN_NUM_INPUT_PORTS];
पूर्ण;

अटल पूर्णांक porपंचांगan_मुक्त(काष्ठा porपंचांगan *pm)
अणु
	kमुक्त(pm);
	वापस 0;
पूर्ण

अटल पूर्णांक porपंचांगan_create(काष्ठा snd_card *card,
			  काष्ठा pardevice *pardev,
			  काष्ठा porपंचांगan **rchip)
अणु
	काष्ठा porपंचांगan *pm;

	*rchip = शून्य;

	pm = kzalloc(माप(काष्ठा porपंचांगan), GFP_KERNEL);
	अगर (pm == शून्य) 
		वापस -ENOMEM;

	/* Init chip specअगरic data */
	spin_lock_init(&pm->reg_lock);
	pm->card = card;
	pm->pardev = pardev;

	*rchip = pm;

	वापस 0;
पूर्ण

/*********************************************************************
 * HW related स्थिरants
 *********************************************************************/

/* Standard PC parallel port status रेजिस्टर equates. */
#घोषणा	PP_STAT_BSY   	0x80	/* Busy status.  Inverted. */
#घोषणा	PP_STAT_ACK   	0x40	/* Acknowledge.  Non-Inverted. */
#घोषणा	PP_STAT_POUT  	0x20	/* Paper Out.    Non-Inverted. */
#घोषणा	PP_STAT_SEL   	0x10	/* Select.       Non-Inverted. */
#घोषणा	PP_STAT_ERR   	0x08	/* Error.        Non-Inverted. */

/* Standard PC parallel port command रेजिस्टर equates. */
#घोषणा	PP_CMD_IEN  	0x10	/* IRQ Enable.   Non-Inverted. */
#घोषणा	PP_CMD_SELI 	0x08	/* Select Input. Inverted. */
#घोषणा	PP_CMD_INIT 	0x04	/* Init Prपूर्णांकer. Non-Inverted. */
#घोषणा	PP_CMD_FEED 	0x02	/* Auto Feed.    Inverted. */
#घोषणा	PP_CMD_STB      0x01	/* Strobe.       Inverted. */

/* Parallel Port Command Register as implemented by PCP2x4. */
#घोषणा	INT_EN	 	PP_CMD_IEN	/* Interrupt enable. */
#घोषणा	STROBE	        PP_CMD_STB	/* Command strobe. */

/* The parallel port command रेजिस्टर field (b1..b3) selects the 
 * various "registers" within the PC/P 2x4.  These are the पूर्णांकernal
 * address of these "registers" that must be written to the parallel
 * port command रेजिस्टर.
 */
#घोषणा	RXDATA0		(0 << 1)	/* PCP RxData channel 0. */
#घोषणा	RXDATA1		(1 << 1)	/* PCP RxData channel 1. */
#घोषणा	GEN_CTL		(2 << 1)	/* PCP General Control Register. */
#घोषणा	SYNC_CTL 	(3 << 1)	/* PCP Sync Control Register. */
#घोषणा	TXDATA0		(4 << 1)	/* PCP TxData channel 0. */
#घोषणा	TXDATA1		(5 << 1)	/* PCP TxData channel 1. */
#घोषणा	TXDATA2		(6 << 1)	/* PCP TxData channel 2. */
#घोषणा	TXDATA3		(7 << 1)	/* PCP TxData channel 3. */

/* Parallel Port Status Register as implemented by PCP2x4. */
#घोषणा	ESTB		PP_STAT_POUT	/* Echoed strobe. */
#घोषणा	INT_REQ         PP_STAT_ACK	/* Input data पूर्णांक request. */
#घोषणा	BUSY            PP_STAT_ERR	/* Interface Busy. */

/* Parallel Port Status Register BUSY and SELECT lines are multiplexed
 * between several functions.  Depending on which 2x4 "register" is
 * currently selected (b1..b3), the BUSY and SELECT lines are
 * asचिन्हित as follows:
 *
 *   SELECT LINE:                                                    A3 A2 A1
 *                                                                   --------
 */
#घोषणा	RXAVAIL		PP_STAT_SEL	/* Rx Available, channel 0.   0 0 0 */
//  RXAVAIL1    PP_STAT_SEL             /* Rx Available, channel 1.   0 0 1 */
#घोषणा	SYNC_STAT	PP_STAT_SEL	/* Reserved - Sync Status.    0 1 0 */
//                                      /* Reserved.                  0 1 1 */
#घोषणा	TXEMPTY		PP_STAT_SEL	/* Tx Empty, channel 0.       1 0 0 */
//      TXEMPTY1        PP_STAT_SEL     /* Tx Empty, channel 1.       1 0 1 */
//  TXEMPTY2    PP_STAT_SEL             /* Tx Empty, channel 2.       1 1 0 */
//  TXEMPTY3    PP_STAT_SEL             /* Tx Empty, channel 3.       1 1 1 */

/*   BUSY LINE:                                                      A3 A2 A1
 *                                                                   --------
 */
#घोषणा	RXDATA		PP_STAT_BSY	/* Rx Input Data, channel 0.  0 0 0 */
//      RXDATA1         PP_STAT_BSY     /* Rx Input Data, channel 1.  0 0 1 */
#घोषणा	SYNC_DATA       PP_STAT_BSY	/* Reserved - Sync Data.      0 1 0 */
					/* Reserved.                  0 1 1 */
#घोषणा	DATA_ECHO       PP_STAT_BSY	/* Parallel Port Data Echo.   1 0 0 */
#घोषणा	A0_ECHO         PP_STAT_BSY	/* Address 0 Echo.            1 0 1 */
#घोषणा	A1_ECHO         PP_STAT_BSY	/* Address 1 Echo.            1 1 0 */
#घोषणा	A2_ECHO         PP_STAT_BSY	/* Address 2 Echo.            1 1 1 */

#घोषणा PORTMAN2X4_MODE_INPUT_TRIGGERED	 0x01

/*********************************************************************
 * Hardware specअगरic functions
 *********************************************************************/
अटल अंतरभूत व्योम porपंचांगan_ग_लिखो_command(काष्ठा porपंचांगan *pm, u8 value)
अणु
	parport_ग_लिखो_control(pm->pardev->port, value);
पूर्ण

अटल अंतरभूत u8 porपंचांगan_पढ़ो_command(काष्ठा porपंचांगan *pm)
अणु
	वापस parport_पढ़ो_control(pm->pardev->port);
पूर्ण

अटल अंतरभूत u8 porपंचांगan_पढ़ो_status(काष्ठा porपंचांगan *pm)
अणु
	वापस parport_पढ़ो_status(pm->pardev->port);
पूर्ण

अटल अंतरभूत u8 porपंचांगan_पढ़ो_data(काष्ठा porपंचांगan *pm)
अणु
	वापस parport_पढ़ो_data(pm->pardev->port);
पूर्ण

अटल अंतरभूत व्योम porपंचांगan_ग_लिखो_data(काष्ठा porपंचांगan *pm, u8 value)
अणु
	parport_ग_लिखो_data(pm->pardev->port, value);
पूर्ण

अटल व्योम porपंचांगan_ग_लिखो_midi(काष्ठा porपंचांगan *pm, 
			       पूर्णांक port, u8 mididata)
अणु
	पूर्णांक command = ((port + 4) << 1);

	/* Get entering data byte and port number in BL and BH respectively.
	 * Set up Tx Channel address field क्रम use with PP Cmd Register.
	 * Store address field in BH रेजिस्टर.
	 * Inमाला_दो:      AH = Output port number (0..3).
	 *              AL = Data byte.
	 *    command = TXDATA0 | INT_EN;
	 * Align port num with address field (b1...b3),
	 * set address क्रम TXDatax, Strobe=0
	 */
	command |= INT_EN;

	/* Disable पूर्णांकerrupts so that the process is not पूर्णांकerrupted, then 
	 * ग_लिखो the address associated with the current Tx channel to the 
	 * PP Command Reg.  Do not set the Strobe संकेत yet.
	 */

	करो अणु
		porपंचांगan_ग_लिखो_command(pm, command);

		/* While the address lines settle, ग_लिखो parallel output data to 
		 * PP Data Reg.  This has no effect until Strobe संकेत is निश्चितed.
		 */

		porपंचांगan_ग_लिखो_data(pm, mididata);
		
		/* If PCP channel's TxEmpty is set (TxEmpty is पढ़ो through the PP
		 * Status Register), then go ग_लिखो data.  Else go back and रुको.
		 */
	पूर्ण जबतक ((porपंचांगan_पढ़ो_status(pm) & TXEMPTY) != TXEMPTY);

	/* TxEmpty is set.  Maपूर्णांकain PC/P destination address and निश्चित
	 * Strobe through the PP Command Reg.  This will Strobe data पूर्णांकo
	 * the PC/P transmitter and set the PC/P BUSY संकेत.
	 */

	porपंचांगan_ग_लिखो_command(pm, command | STROBE);

	/* Wait क्रम strobe line to settle and echo back through hardware.
	 * Once it has echoed back, assume that the address and data lines
	 * have settled!
	 */

	जबतक ((porपंचांगan_पढ़ो_status(pm) & ESTB) == 0)
		cpu_relax();

	/* Release strobe and immediately re-allow पूर्णांकerrupts. */
	porपंचांगan_ग_लिखो_command(pm, command);

	जबतक ((porपंचांगan_पढ़ो_status(pm) & ESTB) == ESTB)
		cpu_relax();

	/* PC/P BUSY is now set.  We must रुको until BUSY resets itself.
	 * We'll reenable ints while we're रुकोing.
	 */

	जबतक ((porपंचांगan_पढ़ो_status(pm) & BUSY) == BUSY)
		cpu_relax();

	/* Data sent. */
पूर्ण


/*
 *  Read MIDI byte from port
 *  Attempt to पढ़ो input byte from specअगरied hardware input port (0..).
 *  Return -1 अगर no data
 */
अटल पूर्णांक porपंचांगan_पढ़ो_midi(काष्ठा porपंचांगan *pm, पूर्णांक port)
अणु
	अचिन्हित अक्षर midi_data = 0;
	अचिन्हित अक्षर cmकरोut;	/* Saved address+IE bit. */

	/* Make sure घड़ीing edge is करोwn beक्रमe starting... */
	porपंचांगan_ग_लिखो_data(pm, 0);	/* Make sure edge is करोwn. */

	/* Set destination address to PCP. */
	cmकरोut = (port << 1) | INT_EN;	/* Address + IE + No Strobe. */
	porपंचांगan_ग_लिखो_command(pm, cmकरोut);

	जबतक ((porपंचांगan_पढ़ो_status(pm) & ESTB) == ESTB)
		cpu_relax();	/* Wait क्रम strobe echo. */

	/* After the address lines settle, check multiplexed RxAvail संकेत.
	 * If data is available, पढ़ो it.
	 */
	अगर ((porपंचांगan_पढ़ो_status(pm) & RXAVAIL) == 0)
		वापस -1;	/* No data. */

	/* Set the Strobe संकेत to enable the Rx घड़ीing circuitry. */
	porपंचांगan_ग_लिखो_command(pm, cmकरोut | STROBE);	/* Write address+IE+Strobe. */

	जबतक ((porपंचांगan_पढ़ो_status(pm) & ESTB) == 0)
		cpu_relax(); /* Wait क्रम strobe echo. */

	/* The first data bit (msb) is alपढ़ोy sitting on the input line. */
	midi_data = (porपंचांगan_पढ़ो_status(pm) & 128);
	porपंचांगan_ग_लिखो_data(pm, 1);	/* Cause rising edge, which shअगरts data. */

	/* Data bit 6. */
	porपंचांगan_ग_लिखो_data(pm, 0);	/* Cause falling edge जबतक data settles. */
	midi_data |= (porपंचांगan_पढ़ो_status(pm) >> 1) & 64;
	porपंचांगan_ग_लिखो_data(pm, 1);	/* Cause rising edge, which shअगरts data. */

	/* Data bit 5. */
	porपंचांगan_ग_लिखो_data(pm, 0);	/* Cause falling edge जबतक data settles. */
	midi_data |= (porपंचांगan_पढ़ो_status(pm) >> 2) & 32;
	porपंचांगan_ग_लिखो_data(pm, 1);	/* Cause rising edge, which shअगरts data. */

	/* Data bit 4. */
	porपंचांगan_ग_लिखो_data(pm, 0);	/* Cause falling edge जबतक data settles. */
	midi_data |= (porपंचांगan_पढ़ो_status(pm) >> 3) & 16;
	porपंचांगan_ग_लिखो_data(pm, 1);	/* Cause rising edge, which shअगरts data. */

	/* Data bit 3. */
	porपंचांगan_ग_लिखो_data(pm, 0);	/* Cause falling edge जबतक data settles. */
	midi_data |= (porपंचांगan_पढ़ो_status(pm) >> 4) & 8;
	porपंचांगan_ग_लिखो_data(pm, 1);	/* Cause rising edge, which shअगरts data. */

	/* Data bit 2. */
	porपंचांगan_ग_लिखो_data(pm, 0);	/* Cause falling edge जबतक data settles. */
	midi_data |= (porपंचांगan_पढ़ो_status(pm) >> 5) & 4;
	porपंचांगan_ग_लिखो_data(pm, 1);	/* Cause rising edge, which shअगरts data. */

	/* Data bit 1. */
	porपंचांगan_ग_लिखो_data(pm, 0);	/* Cause falling edge जबतक data settles. */
	midi_data |= (porपंचांगan_पढ़ो_status(pm) >> 6) & 2;
	porपंचांगan_ग_लिखो_data(pm, 1);	/* Cause rising edge, which shअगरts data. */

	/* Data bit 0. */
	porपंचांगan_ग_लिखो_data(pm, 0);	/* Cause falling edge जबतक data settles. */
	midi_data |= (porपंचांगan_पढ़ो_status(pm) >> 7) & 1;
	porपंचांगan_ग_लिखो_data(pm, 1);	/* Cause rising edge, which shअगरts data. */
	porपंचांगan_ग_लिखो_data(pm, 0);	/* Return data घड़ी low. */


	/* De-निश्चित Strobe and वापस data. */
	porपंचांगan_ग_लिखो_command(pm, cmकरोut);	/* Output saved address+IE. */

	/* Wait क्रम strobe echo. */
	जबतक ((porपंचांगan_पढ़ो_status(pm) & ESTB) == ESTB)
		cpu_relax();

	वापस (midi_data & 255);	/* Shअगरt back and वापस value. */
पूर्ण

/*
 *  Checks अगर any input data on the given channel is available
 *  Checks RxAvail 
 */
अटल पूर्णांक porपंचांगan_data_avail(काष्ठा porपंचांगan *pm, पूर्णांक channel)
अणु
	पूर्णांक command = INT_EN;
	चयन (channel) अणु
	हाल 0:
		command |= RXDATA0;
		अवरोध;
	हाल 1:
		command |= RXDATA1;
		अवरोध;
	पूर्ण
	/* Write hardware (assumme STROBE=0) */
	porपंचांगan_ग_लिखो_command(pm, command);
	/* Check multiplexed RxAvail संकेत */
	अगर ((porपंचांगan_पढ़ो_status(pm) & RXAVAIL) == RXAVAIL)
		वापस 1;	/* Data available */

	/* No Data available */
	वापस 0;
पूर्ण


/*
 *  Flushes any input
 */
अटल व्योम porपंचांगan_flush_input(काष्ठा porपंचांगan *pm, अचिन्हित अक्षर port)
अणु
	/* Local variable क्रम counting things */
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित अक्षर command = 0;

	चयन (port) अणु
	हाल 0:
		command = RXDATA0;
		अवरोध;
	हाल 1:
		command = RXDATA1;
		अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_WARNING
			   "portman_flush_input() Won't flush port %i\n",
			   port);
		वापस;
	पूर्ण

	/* Set address क्रम specअगरied channel in port and allow to settle. */
	porपंचांगan_ग_लिखो_command(pm, command);

	/* Assert the Strobe and रुको क्रम echo back. */
	porपंचांगan_ग_लिखो_command(pm, command | STROBE);

	/* Wait क्रम ESTB */
	जबतक ((porपंचांगan_पढ़ो_status(pm) & ESTB) == 0)
		cpu_relax();

	/* Output घड़ी cycles to the Rx circuitry. */
	porपंचांगan_ग_लिखो_data(pm, 0);

	/* Flush 250 bits... */
	क्रम (i = 0; i < 250; i++) अणु
		porपंचांगan_ग_लिखो_data(pm, 1);
		porपंचांगan_ग_लिखो_data(pm, 0);
	पूर्ण

	/* Deनिश्चित the Strobe संकेत of the port and रुको क्रम it to settle. */
	porपंचांगan_ग_लिखो_command(pm, command | INT_EN);

	/* Wait क्रम settling */
	जबतक ((porपंचांगan_पढ़ो_status(pm) & ESTB) == ESTB)
		cpu_relax();
पूर्ण

अटल पूर्णांक porपंचांगan_probe(काष्ठा parport *p)
अणु
	/* Initialize the parallel port data रेजिस्टर.  Will set Rx घड़ीs
	 * low in हाल we happen to be addressing the Rx ports at this समय.
	 */
	/* 1 */
	parport_ग_लिखो_data(p, 0);

	/* Initialize the parallel port command रेजिस्टर, thus initializing
	 * hardware handshake lines to midi box:
	 *
	 *                                  Strobe = 0
	 *                                  Interrupt Enable = 0            
	 */
	/* 2 */
	parport_ग_लिखो_control(p, 0);

	/* Check अगर Porपंचांगan PC/P 2x4 is out there. */
	/* 3 */
	parport_ग_लिखो_control(p, RXDATA0);	/* Write Strobe=0 to command reg. */

	/* Check क्रम ESTB to be clear */
	/* 4 */
	अगर ((parport_पढ़ो_status(p) & ESTB) == ESTB)
		वापस 1;	/* CODE 1 - Strobe Failure. */

	/* Set क्रम RXDATA0 where no damage will be करोne. */
	/* 5 */
	parport_ग_लिखो_control(p, RXDATA0 | STROBE);	/* Write Strobe=1 to command reg. */

	/* 6 */
	अगर ((parport_पढ़ो_status(p) & ESTB) != ESTB)
		वापस 1;	/* CODE 1 - Strobe Failure. */

	/* 7 */
	parport_ग_लिखो_control(p, 0);	/* Reset Strobe=0. */

	/* Check अगर Tx circuitry is functioning properly.  If initialized 
	 * unit TxEmpty is false, send out अक्षर and see अगर it goes true.
	 */
	/* 8 */
	parport_ग_लिखो_control(p, TXDATA0);	/* Tx channel 0, strobe off. */

	/* If PCP channel's TxEmpty is set (TxEmpty is पढ़ो through the PP
	 * Status Register), then go ग_लिखो data.  Else go back and रुको.
	 */
	/* 9 */
	अगर ((parport_पढ़ो_status(p) & TXEMPTY) == 0)
		वापस 2;

	/* Return OK status. */
	वापस 0;
पूर्ण

अटल पूर्णांक porपंचांगan_device_init(काष्ठा porपंचांगan *pm)
अणु
	porपंचांगan_flush_input(pm, 0);
	porपंचांगan_flush_input(pm, 1);

	वापस 0;
पूर्ण

/*********************************************************************
 * Rawmidi
 *********************************************************************/
अटल पूर्णांक snd_porपंचांगan_midi_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक snd_porपंचांगan_midi_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल व्योम snd_porपंचांगan_midi_input_trigger(काष्ठा snd_rawmidi_substream *substream,
					   पूर्णांक up)
अणु
	काष्ठा porपंचांगan *pm = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pm->reg_lock, flags);
	अगर (up)
		pm->mode[substream->number] |= PORTMAN2X4_MODE_INPUT_TRIGGERED;
	अन्यथा
		pm->mode[substream->number] &= ~PORTMAN2X4_MODE_INPUT_TRIGGERED;
	spin_unlock_irqrestore(&pm->reg_lock, flags);
पूर्ण

अटल व्योम snd_porपंचांगan_midi_output_trigger(काष्ठा snd_rawmidi_substream *substream,
					    पूर्णांक up)
अणु
	काष्ठा porपंचांगan *pm = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर byte;

	spin_lock_irqsave(&pm->reg_lock, flags);
	अगर (up) अणु
		जबतक ((snd_rawmidi_transmit(substream, &byte, 1) == 1))
			porपंचांगan_ग_लिखो_midi(pm, substream->number, byte);
	पूर्ण
	spin_unlock_irqrestore(&pm->reg_lock, flags);
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops snd_porपंचांगan_midi_output = अणु
	.खोलो =		snd_porपंचांगan_midi_खोलो,
	.बंद =	snd_porपंचांगan_midi_बंद,
	.trigger =	snd_porपंचांगan_midi_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_porपंचांगan_midi_input = अणु
	.खोलो =		snd_porपंचांगan_midi_खोलो,
	.बंद =	snd_porपंचांगan_midi_बंद,
	.trigger =	snd_porपंचांगan_midi_input_trigger,
पूर्ण;

/* Create and initialize the rawmidi component */
अटल पूर्णांक snd_porपंचांगan_rawmidi_create(काष्ठा snd_card *card)
अणु
	काष्ठा porपंचांगan *pm = card->निजी_data;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *substream;
	पूर्णांक err;
	
	err = snd_rawmidi_new(card, CARD_NAME, 0, 
			      PORTMAN_NUM_OUTPUT_PORTS, 
			      PORTMAN_NUM_INPUT_PORTS, 
			      &rmidi);
	अगर (err < 0) 
		वापस err;

	rmidi->निजी_data = pm;
	म_नकल(rmidi->name, CARD_NAME);
	rmidi->info_flags = SNDRV_RAWMIDI_INFO_OUTPUT |
		            SNDRV_RAWMIDI_INFO_INPUT |
                            SNDRV_RAWMIDI_INFO_DUPLEX;

	pm->rmidi = rmidi;

	/* रेजिस्टर rawmidi ops */
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, 
			    &snd_porपंचांगan_midi_output);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, 
			    &snd_porपंचांगan_midi_input);

	/* name substreams */
	/* output */
	list_क्रम_each_entry(substream,
			    &rmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT].substreams,
			    list) अणु
		प्र_लिखो(substream->name,
			"Portman2x4 %d", substream->number+1);
	पूर्ण
	/* input */
	list_क्रम_each_entry(substream,
			    &rmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT].substreams,
			    list) अणु
		pm->midi_input[substream->number] = substream;
		प्र_लिखो(substream->name,
			"Portman2x4 %d", substream->number+1);
	पूर्ण

	वापस err;
पूर्ण

/*********************************************************************
 * parport stuff
 *********************************************************************/
अटल व्योम snd_porपंचांगan_पूर्णांकerrupt(व्योम *userdata)
अणु
	अचिन्हित अक्षर miभागalue = 0;
	काष्ठा porपंचांगan *pm = ((काष्ठा snd_card*)userdata)->निजी_data;

	spin_lock(&pm->reg_lock);

	/* While any input data is रुकोing */
	जबतक ((porपंचांगan_पढ़ो_status(pm) & INT_REQ) == INT_REQ) अणु
		/* If data available on channel 0, 
		   पढ़ो it and stuff it पूर्णांकo the queue. */
		अगर (porपंचांगan_data_avail(pm, 0)) अणु
			/* Read Midi */
			miभागalue = porपंचांगan_पढ़ो_midi(pm, 0);
			/* put midi पूर्णांकo queue... */
			अगर (pm->mode[0] & PORTMAN2X4_MODE_INPUT_TRIGGERED)
				snd_rawmidi_receive(pm->midi_input[0],
						    &miभागalue, 1);

		पूर्ण
		/* If data available on channel 1, 
		   पढ़ो it and stuff it पूर्णांकo the queue. */
		अगर (porपंचांगan_data_avail(pm, 1)) अणु
			/* Read Midi */
			miभागalue = porपंचांगan_पढ़ो_midi(pm, 1);
			/* put midi पूर्णांकo queue... */
			अगर (pm->mode[1] & PORTMAN2X4_MODE_INPUT_TRIGGERED)
				snd_rawmidi_receive(pm->midi_input[1],
						    &miभागalue, 1);
		पूर्ण

	पूर्ण

	spin_unlock(&pm->reg_lock);
पूर्ण

अटल व्योम snd_porपंचांगan_attach(काष्ठा parport *p)
अणु
	काष्ठा platक्रमm_device *device;

	device = platक्रमm_device_alloc(PLATFORM_DRIVER, device_count);
	अगर (!device)
		वापस;

	/* Temporary assignment to क्रमward the parport */
	platक्रमm_set_drvdata(device, p);

	अगर (platक्रमm_device_add(device) < 0) अणु
		platक्रमm_device_put(device);
		वापस;
	पूर्ण

	/* Since we करोnt get the वापस value of probe
	 * We need to check अगर device probing succeeded or not */
	अगर (!platक्रमm_get_drvdata(device)) अणु
		platक्रमm_device_unरेजिस्टर(device);
		वापस;
	पूर्ण

	/* रेजिस्टर device in global table */
	platक्रमm_devices[device_count] = device;
	device_count++;
पूर्ण

अटल व्योम snd_porपंचांगan_detach(काष्ठा parport *p)
अणु
	/* nothing to करो here */
पूर्ण

अटल पूर्णांक snd_porपंचांगan_dev_probe(काष्ठा pardevice *pardev)
अणु
	अगर (म_भेद(pardev->name, DRIVER_NAME))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल काष्ठा parport_driver porपंचांगan_parport_driver = अणु
	.name		= "portman2x4",
	.probe		= snd_porपंचांगan_dev_probe,
	.match_port	= snd_porपंचांगan_attach,
	.detach		= snd_porपंचांगan_detach,
	.devmodel	= true,
पूर्ण;

/*********************************************************************
 * platक्रमm stuff
 *********************************************************************/
अटल व्योम snd_porपंचांगan_card_निजी_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा porपंचांगan *pm = card->निजी_data;
	काष्ठा pardevice *pardev = pm->pardev;

	अगर (pardev) अणु
		parport_release(pardev);
		parport_unरेजिस्टर_device(pardev);
	पूर्ण

	porपंचांगan_मुक्त(pm);
पूर्ण

अटल पूर्णांक snd_porपंचांगan_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pardevice *pardev;
	काष्ठा parport *p;
	पूर्णांक dev = pdev->id;
	काष्ठा snd_card *card = शून्य;
	काष्ठा porपंचांगan *pm = शून्य;
	पूर्णांक err;
	काष्ठा pardev_cb porपंचांगan_cb = अणु
		.preempt = शून्य,
		.wakeup = शून्य,
		.irq_func = snd_porपंचांगan_पूर्णांकerrupt,	/* ISR */
		.flags = PARPORT_DEV_EXCL,		/* flags */
	पूर्ण;

	p = platक्रमm_get_drvdata(pdev);
	platक्रमm_set_drvdata(pdev, शून्य);

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) 
		वापस -ENOENT;

	err = snd_card_new(&pdev->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0) अणु
		snd_prपूर्णांकd("Cannot create card\n");
		वापस err;
	पूर्ण
	म_नकल(card->driver, DRIVER_NAME);
	म_नकल(card->लघुname, CARD_NAME);
	प्र_लिखो(card->दीर्घname,  "%s at 0x%lx, irq %i", 
		card->लघुname, p->base, p->irq);

	porपंचांगan_cb.निजी = card;			   /* निजी */
	pardev = parport_रेजिस्टर_dev_model(p,		   /* port */
					    DRIVER_NAME,   /* name */
					    &porपंचांगan_cb,   /* callbacks */
					    pdev->id);	   /* device number */
	अगर (pardev == शून्य) अणु
		snd_prपूर्णांकd("Cannot register pardevice\n");
		err = -EIO;
		जाओ __err;
	पूर्ण

	/* claim parport */
	अगर (parport_claim(pardev)) अणु
		snd_prपूर्णांकd("Cannot claim parport 0x%lx\n", pardev->port->base);
		err = -EIO;
		जाओ मुक्त_pardev;
	पूर्ण

	अगर ((err = porपंचांगan_create(card, pardev, &pm)) < 0) अणु
		snd_prपूर्णांकd("Cannot create main component\n");
		जाओ release_pardev;
	पूर्ण
	card->निजी_data = pm;
	card->निजी_मुक्त = snd_porपंचांगan_card_निजी_मुक्त;

	err = porपंचांगan_probe(p);
	अगर (err) अणु
		err = -EIO;
		जाओ __err;
	पूर्ण
	
	अगर ((err = snd_porपंचांगan_rawmidi_create(card)) < 0) अणु
		snd_prपूर्णांकd("Creating Rawmidi component failed\n");
		जाओ __err;
	पूर्ण

	/* init device */
	अगर ((err = porपंचांगan_device_init(pm)) < 0)
		जाओ __err;

	platक्रमm_set_drvdata(pdev, card);

	/* At this poपूर्णांक card will be usable */
	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_prपूर्णांकd("Cannot register card\n");
		जाओ __err;
	पूर्ण

	snd_prपूर्णांकk(KERN_INFO "Portman 2x4 on 0x%lx\n", p->base);
	वापस 0;

release_pardev:
	parport_release(pardev);
मुक्त_pardev:
	parport_unरेजिस्टर_device(pardev);
__err:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक snd_porपंचांगan_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_card *card = platक्रमm_get_drvdata(pdev);

	अगर (card)
		snd_card_मुक्त(card);

	वापस 0;
पूर्ण


अटल काष्ठा platक्रमm_driver snd_porपंचांगan_driver = अणु
	.probe  = snd_porपंचांगan_probe,
	.हटाओ = snd_porपंचांगan_हटाओ,
	.driver = अणु
		.name = PLATFORM_DRIVER,
	पूर्ण
पूर्ण;

/*********************************************************************
 * module init stuff
 *********************************************************************/
अटल व्योम snd_porपंचांगan_unरेजिस्टर_all(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SNDRV_CARDS; ++i) अणु
		अगर (platक्रमm_devices[i]) अणु
			platक्रमm_device_unरेजिस्टर(platक्रमm_devices[i]);
			platक्रमm_devices[i] = शून्य;
		पूर्ण
	पूर्ण		
	platक्रमm_driver_unरेजिस्टर(&snd_porपंचांगan_driver);
	parport_unरेजिस्टर_driver(&porपंचांगan_parport_driver);
पूर्ण

अटल पूर्णांक __init snd_porपंचांगan_module_init(व्योम)
अणु
	पूर्णांक err;

	अगर ((err = platक्रमm_driver_रेजिस्टर(&snd_porपंचांगan_driver)) < 0)
		वापस err;

	अगर (parport_रेजिस्टर_driver(&porपंचांगan_parport_driver) != 0) अणु
		platक्रमm_driver_unरेजिस्टर(&snd_porपंचांगan_driver);
		वापस -EIO;
	पूर्ण

	अगर (device_count == 0) अणु
		snd_porपंचांगan_unरेजिस्टर_all();
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास snd_porपंचांगan_module_निकास(व्योम)
अणु
	snd_porपंचांगan_unरेजिस्टर_all();
पूर्ण

module_init(snd_porपंचांगan_module_init);
module_निकास(snd_porपंचांगan_module_निकास);
