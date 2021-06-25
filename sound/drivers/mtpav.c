<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      MOTU Midi Timepiece ALSA Main routines
 *      Copyright by Michael T. Mayers (c) Jan 09, 2000
 *      mail: michael@tweakoz.com
 *      Thanks to John Galbraith
 *
 *      This driver is क्रम the 'Mark Of The Unicorn' (MOTU)
 *      MidiTimePiece AV multiport MIDI पूर्णांकerface 
 *
 *      IOPORTS
 *      -------
 *      8 MIDI Ins and 8 MIDI outs
 *      Video Sync In (BNC), Word Sync Out (BNC), 
 *      ADAT Sync Out (DB9)
 *      SMPTE in/out (1/4")
 *      2 programmable pedal/footचयन inमाला_दो and 4 programmable MIDI controller knobs.
 *      Macपूर्णांकosh RS422 serial port
 *      RS422 "network" port क्रम ganging multiple MTP's
 *      PC Parallel Port ( which this driver currently uses )
 *
 *      MISC FEATURES
 *      -------------
 *      Hardware MIDI routing, merging, and filtering   
 *      MIDI Synchronization to Video, ADAT, SMPTE and other Clock sources
 *      128 'scene' memories, recallable from MIDI program change
 *
 * ChangeLog
 * Jun 11 2001	Takashi Iwai <tiwai@suse.de>
 *      - Recoded & debugged
 *      - Added समयr पूर्णांकerrupt क्रम midi outमाला_दो
 *      - hwports is between 1 and 8, which specअगरies the number of hardware ports.
 *        The three global ports, computer, adat and broadcast ports, are created
 *        always after h/w and remote ports.
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/moduleparam.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/rawmidi.h>
#समावेश <linux/delay.h>

/*
 *      globals
 */
MODULE_AUTHOR("Michael T. Mayers");
MODULE_DESCRIPTION("MOTU MidiTimePiece AV multiport MIDI");
MODULE_LICENSE("GPL");

// io resources
#घोषणा MTPAV_IOBASE		0x378
#घोषणा MTPAV_IRQ		7
#घोषणा MTPAV_MAX_PORTS		8

अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;
अटल अक्षर *id = SNDRV_DEFAULT_STR1;
अटल दीर्घ port = MTPAV_IOBASE;	/* 0x378, 0x278 */
अटल पूर्णांक irq = MTPAV_IRQ;		/* 7, 5 */
अटल पूर्णांक hwports = MTPAV_MAX_PORTS;	/* use hardware ports 1-8 */

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for MotuMTPAV MIDI.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for MotuMTPAV MIDI.");
module_param_hw(port, दीर्घ, ioport, 0444);
MODULE_PARM_DESC(port, "Parallel port # for MotuMTPAV MIDI.");
module_param_hw(irq, पूर्णांक, irq, 0444);
MODULE_PARM_DESC(irq, "Parallel IRQ # for MotuMTPAV MIDI.");
module_param(hwports, पूर्णांक, 0444);
MODULE_PARM_DESC(hwports, "Hardware ports # for MotuMTPAV MIDI.");

अटल काष्ठा platक्रमm_device *device;

/*
 *      defines
 */
//#घोषणा USE_FAKE_MTP //       करोn't actually पढ़ो/ग_लिखो to MTP device (क्रम debugging without an actual unit) (करोes not work yet)

// parallel port usage masks
#घोषणा SIGS_BYTE 0x08
#घोषणा SIGS_RFD 0x80
#घोषणा SIGS_IRQ 0x40
#घोषणा SIGS_IN0 0x10
#घोषणा SIGS_IN1 0x20

#घोषणा SIGC_WRITE 0x04
#घोषणा SIGC_READ 0x08
#घोषणा SIGC_INTEN 0x10

#घोषणा DREG 0
#घोषणा SREG 1
#घोषणा CREG 2

//
#घोषणा MTPAV_MODE_INPUT_OPENED		0x01
#घोषणा MTPAV_MODE_OUTPUT_OPENED	0x02
#घोषणा MTPAV_MODE_INPUT_TRIGGERED	0x04
#घोषणा MTPAV_MODE_OUTPUT_TRIGGERED	0x08

#घोषणा NUMPORTS (0x12+1)


/*
 */

काष्ठा mtpav_port अणु
	u8 number;
	u8 hwport;
	u8 mode;
	u8 running_status;
	काष्ठा snd_rawmidi_substream *input;
	काष्ठा snd_rawmidi_substream *output;
पूर्ण;

काष्ठा mtpav अणु
	काष्ठा snd_card *card;
	अचिन्हित दीर्घ port;
	काष्ठा resource *res_port;
	पूर्णांक irq;			/* पूर्णांकerrupt (क्रम inमाला_दो) */
	spinlock_t spinlock;
	पूर्णांक share_irq;			/* number of accesses to input पूर्णांकerrupts */
	पूर्णांक isसमयr;			/* number of accesses to समयr पूर्णांकerrupts */
	काष्ठा समयr_list समयr;	/* समयr पूर्णांकerrupts क्रम outमाला_दो */
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक num_ports;		/* number of hw ports (1-8) */
	काष्ठा mtpav_port ports[NUMPORTS];	/* all ports including computer, adat and bc */

	u32 inmidiport;		/* selected input midi port */
	u32 inmidistate;	/* during midi command 0xf5 */

	u32 ouपंचांगidihwport;	/* selected output midi hw port */
पूर्ण;


/*
 * possible hardware ports (selected by 0xf5 port message)
 *      0x00		all ports
 *      0x01 .. 0x08    this MTP's ports 1..8
 *      0x09 .. 0x10    networked MTP's ports (9..16)
 *      0x11            networked MTP's computer port
 *      0x63            to ADAT
 *
 * mappig:
 *  subdevice 0 - (X-1)    ports
 *            X - (2*X-1)  networked ports
 *            X            computer
 *            X+1          ADAT
 *            X+2          all ports
 *
 *  where X = chip->num_ports
 */

#घोषणा MTPAV_PIDX_COMPUTER	0
#घोषणा MTPAV_PIDX_ADAT		1
#घोषणा MTPAV_PIDX_BROADCAST	2


अटल पूर्णांक translate_subdevice_to_hwport(काष्ठा mtpav *chip, पूर्णांक subdev)
अणु
	अगर (subdev < 0)
		वापस 0x01; /* invalid - use port 0 as शेष */
	अन्यथा अगर (subdev < chip->num_ports)
		वापस subdev + 1; /* single mtp port */
	अन्यथा अगर (subdev < chip->num_ports * 2)
		वापस subdev - chip->num_ports + 0x09; /* remote port */
	अन्यथा अगर (subdev == chip->num_ports * 2 + MTPAV_PIDX_COMPUTER)
		वापस 0x11; /* computer port */
	अन्यथा अगर (subdev == chip->num_ports + MTPAV_PIDX_ADAT)
		वापस 0x63;		/* ADAT */
	वापस 0; /* all ports */
पूर्ण

अटल पूर्णांक translate_hwport_to_subdevice(काष्ठा mtpav *chip, पूर्णांक hwport)
अणु
	पूर्णांक p;
	अगर (hwport <= 0x00) /* all ports */
		वापस chip->num_ports + MTPAV_PIDX_BROADCAST;
	अन्यथा अगर (hwport <= 0x08) अणु /* single port */
		p = hwport - 1;
		अगर (p >= chip->num_ports)
			p = 0;
		वापस p;
	पूर्ण अन्यथा अगर (hwport <= 0x10) अणु /* remote port */
		p = hwport - 0x09 + chip->num_ports;
		अगर (p >= chip->num_ports * 2)
			p = chip->num_ports;
		वापस p;
	पूर्ण अन्यथा अगर (hwport == 0x11)  /* computer port */
		वापस chip->num_ports + MTPAV_PIDX_COMPUTER;
	अन्यथा  /* ADAT */
		वापस chip->num_ports + MTPAV_PIDX_ADAT;
पूर्ण


/*
 */

अटल u8 snd_mtpav_getreg(काष्ठा mtpav *chip, u16 reg)
अणु
	u8 rval = 0;

	अगर (reg == SREG) अणु
		rval = inb(chip->port + SREG);
		rval = (rval & 0xf8);
	पूर्ण अन्यथा अगर (reg == CREG) अणु
		rval = inb(chip->port + CREG);
		rval = (rval & 0x1c);
	पूर्ण

	वापस rval;
पूर्ण

/*
 */

अटल अंतरभूत व्योम snd_mtpav_mputreg(काष्ठा mtpav *chip, u16 reg, u8 val)
अणु
	अगर (reg == DREG || reg == CREG)
		outb(val, chip->port + reg);
पूर्ण

/*
 */

अटल व्योम snd_mtpav_रुको_rfdhi(काष्ठा mtpav *chip)
अणु
	पूर्णांक counts = 10000;
	u8 sbyte;

	sbyte = snd_mtpav_getreg(chip, SREG);
	जबतक (!(sbyte & SIGS_RFD) && counts--) अणु
		sbyte = snd_mtpav_getreg(chip, SREG);
		udelay(10);
	पूर्ण
पूर्ण

अटल व्योम snd_mtpav_send_byte(काष्ठा mtpav *chip, u8 byte)
अणु
	u8 tcbyt;
	u8 clrग_लिखो;
	u8 setग_लिखो;

	snd_mtpav_रुको_rfdhi(chip);

	/////////////////

	tcbyt = snd_mtpav_getreg(chip, CREG);
	clrग_लिखो = tcbyt & (SIGC_WRITE ^ 0xff);
	setग_लिखो = tcbyt | SIGC_WRITE;

	snd_mtpav_mputreg(chip, DREG, byte);
	snd_mtpav_mputreg(chip, CREG, clrग_लिखो);	// clear ग_लिखो bit

	snd_mtpav_mputreg(chip, CREG, setग_लिखो);	// set ग_लिखो bit

पूर्ण


/*
 */

/* call this with spin lock held */
अटल व्योम snd_mtpav_output_port_ग_लिखो(काष्ठा mtpav *mtp_card,
					काष्ठा mtpav_port *portp,
					काष्ठा snd_rawmidi_substream *substream)
अणु
	u8 outbyte;

	// Get the outbyte first, so we can emulate running status अगर
	// necessary
	अगर (snd_rawmidi_transmit(substream, &outbyte, 1) != 1)
		वापस;

	// send port change command अगर necessary

	अगर (portp->hwport != mtp_card->ouपंचांगidihwport) अणु
		mtp_card->ouपंचांगidihwport = portp->hwport;

		snd_mtpav_send_byte(mtp_card, 0xf5);
		snd_mtpav_send_byte(mtp_card, portp->hwport);
		/*
		snd_prपूर्णांकk(KERN_DEBUG "new outport: 0x%x\n",
			   (अचिन्हित पूर्णांक) portp->hwport);
		*/
		अगर (!(outbyte & 0x80) && portp->running_status)
			snd_mtpav_send_byte(mtp_card, portp->running_status);
	पूर्ण

	// send data

	करो अणु
		अगर (outbyte & 0x80)
			portp->running_status = outbyte;
		
		snd_mtpav_send_byte(mtp_card, outbyte);
	पूर्ण जबतक (snd_rawmidi_transmit(substream, &outbyte, 1) == 1);
पूर्ण

अटल व्योम snd_mtpav_output_ग_लिखो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा mtpav *mtp_card = substream->rmidi->निजी_data;
	काष्ठा mtpav_port *portp = &mtp_card->ports[substream->number];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mtp_card->spinlock, flags);
	snd_mtpav_output_port_ग_लिखो(mtp_card, portp, substream);
	spin_unlock_irqrestore(&mtp_card->spinlock, flags);
पूर्ण


/*
 *      mtpav control
 */

अटल व्योम snd_mtpav_portscan(काष्ठा mtpav *chip)	// put mtp पूर्णांकo smart routing mode
अणु
	u8 p;

	क्रम (p = 0; p < 8; p++) अणु
		snd_mtpav_send_byte(chip, 0xf5);
		snd_mtpav_send_byte(chip, p);
		snd_mtpav_send_byte(chip, 0xfe);
	पूर्ण
पूर्ण

/*
 */

अटल पूर्णांक snd_mtpav_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा mtpav *mtp_card = substream->rmidi->निजी_data;
	काष्ठा mtpav_port *portp = &mtp_card->ports[substream->number];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mtp_card->spinlock, flags);
	portp->mode |= MTPAV_MODE_INPUT_OPENED;
	portp->input = substream;
	अगर (mtp_card->share_irq++ == 0)
		snd_mtpav_mputreg(mtp_card, CREG, (SIGC_INTEN | SIGC_WRITE));	// enable pport पूर्णांकerrupts
	spin_unlock_irqrestore(&mtp_card->spinlock, flags);
	वापस 0;
पूर्ण

/*
 */

अटल पूर्णांक snd_mtpav_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा mtpav *mtp_card = substream->rmidi->निजी_data;
	काष्ठा mtpav_port *portp = &mtp_card->ports[substream->number];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mtp_card->spinlock, flags);
	portp->mode &= ~MTPAV_MODE_INPUT_OPENED;
	portp->input = शून्य;
	अगर (--mtp_card->share_irq == 0)
		snd_mtpav_mputreg(mtp_card, CREG, 0);	// disable pport पूर्णांकerrupts
	spin_unlock_irqrestore(&mtp_card->spinlock, flags);
	वापस 0;
पूर्ण

/*
 */

अटल व्योम snd_mtpav_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा mtpav *mtp_card = substream->rmidi->निजी_data;
	काष्ठा mtpav_port *portp = &mtp_card->ports[substream->number];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mtp_card->spinlock, flags);
	अगर (up)
		portp->mode |= MTPAV_MODE_INPUT_TRIGGERED;
	अन्यथा
		portp->mode &= ~MTPAV_MODE_INPUT_TRIGGERED;
	spin_unlock_irqrestore(&mtp_card->spinlock, flags);

पूर्ण


/*
 * समयr पूर्णांकerrupt क्रम outमाला_दो
 */

अटल व्योम snd_mtpav_output_समयr(काष्ठा समयr_list *t)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mtpav *chip = from_समयr(chip, t, समयr);
	पूर्णांक p;

	spin_lock_irqsave(&chip->spinlock, flags);
	/* reprogram समयr */
	mod_समयr(&chip->समयr, 1 + jअगरfies);
	/* process each port */
	क्रम (p = 0; p <= chip->num_ports * 2 + MTPAV_PIDX_BROADCAST; p++) अणु
		काष्ठा mtpav_port *portp = &chip->ports[p];
		अगर ((portp->mode & MTPAV_MODE_OUTPUT_TRIGGERED) && portp->output)
			snd_mtpav_output_port_ग_लिखो(chip, portp, portp->output);
	पूर्ण
	spin_unlock_irqrestore(&chip->spinlock, flags);
पूर्ण

/* spinlock held! */
अटल व्योम snd_mtpav_add_output_समयr(काष्ठा mtpav *chip)
अणु
	mod_समयr(&chip->समयr, 1 + jअगरfies);
पूर्ण

/* spinlock held! */
अटल व्योम snd_mtpav_हटाओ_output_समयr(काष्ठा mtpav *chip)
अणु
	del_समयr(&chip->समयr);
पूर्ण

/*
 */

अटल पूर्णांक snd_mtpav_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा mtpav *mtp_card = substream->rmidi->निजी_data;
	काष्ठा mtpav_port *portp = &mtp_card->ports[substream->number];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mtp_card->spinlock, flags);
	portp->mode |= MTPAV_MODE_OUTPUT_OPENED;
	portp->output = substream;
	spin_unlock_irqrestore(&mtp_card->spinlock, flags);
	वापस 0;
पूर्ण;

/*
 */

अटल पूर्णांक snd_mtpav_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा mtpav *mtp_card = substream->rmidi->निजी_data;
	काष्ठा mtpav_port *portp = &mtp_card->ports[substream->number];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mtp_card->spinlock, flags);
	portp->mode &= ~MTPAV_MODE_OUTPUT_OPENED;
	portp->output = शून्य;
	spin_unlock_irqrestore(&mtp_card->spinlock, flags);
	वापस 0;
पूर्ण;

/*
 */

अटल व्योम snd_mtpav_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा mtpav *mtp_card = substream->rmidi->निजी_data;
	काष्ठा mtpav_port *portp = &mtp_card->ports[substream->number];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mtp_card->spinlock, flags);
	अगर (up) अणु
		अगर (! (portp->mode & MTPAV_MODE_OUTPUT_TRIGGERED)) अणु
			अगर (mtp_card->isसमयr++ == 0)
				snd_mtpav_add_output_समयr(mtp_card);
			portp->mode |= MTPAV_MODE_OUTPUT_TRIGGERED;
		पूर्ण
	पूर्ण अन्यथा अणु
		portp->mode &= ~MTPAV_MODE_OUTPUT_TRIGGERED;
		अगर (--mtp_card->isसमयr == 0)
			snd_mtpav_हटाओ_output_समयr(mtp_card);
	पूर्ण
	spin_unlock_irqrestore(&mtp_card->spinlock, flags);

	अगर (up)
		snd_mtpav_output_ग_लिखो(substream);
पूर्ण

/*
 * midi पूर्णांकerrupt क्रम inमाला_दो
 */

अटल व्योम snd_mtpav_inmidi_process(काष्ठा mtpav *mcrd, u8 inbyte)
अणु
	काष्ठा mtpav_port *portp;

	अगर ((पूर्णांक)mcrd->inmidiport > mcrd->num_ports * 2 + MTPAV_PIDX_BROADCAST)
		वापस;

	portp = &mcrd->ports[mcrd->inmidiport];
	अगर (portp->mode & MTPAV_MODE_INPUT_TRIGGERED)
		snd_rawmidi_receive(portp->input, &inbyte, 1);
पूर्ण

अटल व्योम snd_mtpav_inmidi_h(काष्ठा mtpav *mcrd, u8 inbyte)
अणु
	अगर (inbyte >= 0xf8) अणु
		/* real-समय midi code */
		snd_mtpav_inmidi_process(mcrd, inbyte);
		वापस;
	पूर्ण

	अगर (mcrd->inmidistate == 0) अणु	// aरुकोing command
		अगर (inbyte == 0xf5)	// MTP port #
			mcrd->inmidistate = 1;
		अन्यथा
			snd_mtpav_inmidi_process(mcrd, inbyte);
	पूर्ण अन्यथा अगर (mcrd->inmidistate) अणु
		mcrd->inmidiport = translate_hwport_to_subdevice(mcrd, inbyte);
		mcrd->inmidistate = 0;
	पूर्ण
पूर्ण

अटल व्योम snd_mtpav_पढ़ो_bytes(काष्ठा mtpav *mcrd)
अणु
	u8 clrपढ़ो, setपढ़ो;
	u8 mtp_पढ़ो_byte;
	u8 sr, cbyt;
	पूर्णांक i;

	u8 sbyt = snd_mtpav_getreg(mcrd, SREG);

	/* prपूर्णांकk(KERN_DEBUG "snd_mtpav_read_bytes() sbyt: 0x%x\n", sbyt); */

	अगर (!(sbyt & SIGS_BYTE))
		वापस;

	cbyt = snd_mtpav_getreg(mcrd, CREG);
	clrपढ़ो = cbyt & (SIGC_READ ^ 0xff);
	setपढ़ो = cbyt | SIGC_READ;

	करो अणु

		mtp_पढ़ो_byte = 0;
		क्रम (i = 0; i < 4; i++) अणु
			snd_mtpav_mputreg(mcrd, CREG, setपढ़ो);
			sr = snd_mtpav_getreg(mcrd, SREG);
			snd_mtpav_mputreg(mcrd, CREG, clrपढ़ो);

			sr &= SIGS_IN0 | SIGS_IN1;
			sr >>= 4;
			mtp_पढ़ो_byte |= sr << (i * 2);
		पूर्ण

		snd_mtpav_inmidi_h(mcrd, mtp_पढ़ो_byte);

		sbyt = snd_mtpav_getreg(mcrd, SREG);

	पूर्ण जबतक (sbyt & SIGS_BYTE);
पूर्ण

अटल irqवापस_t snd_mtpav_irqh(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mtpav *mcard = dev_id;

	spin_lock(&mcard->spinlock);
	snd_mtpav_पढ़ो_bytes(mcard);
	spin_unlock(&mcard->spinlock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * get ISA resources
 */
अटल पूर्णांक snd_mtpav_get_ISA(काष्ठा mtpav *mcard)
अणु
	अगर ((mcard->res_port = request_region(port, 3, "MotuMTPAV MIDI")) == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR "MTVAP port 0x%lx is busy\n", port);
		वापस -EBUSY;
	पूर्ण
	mcard->port = port;
	अगर (request_irq(irq, snd_mtpav_irqh, 0, "MOTU MTPAV", mcard)) अणु
		snd_prपूर्णांकk(KERN_ERR "MTVAP IRQ %d busy\n", irq);
		वापस -EBUSY;
	पूर्ण
	mcard->irq = irq;
	वापस 0;
पूर्ण


/*
 */

अटल स्थिर काष्ठा snd_rawmidi_ops snd_mtpav_output = अणु
	.खोलो =		snd_mtpav_output_खोलो,
	.बंद =	snd_mtpav_output_बंद,
	.trigger =	snd_mtpav_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_mtpav_input = अणु
	.खोलो =		snd_mtpav_input_खोलो,
	.बंद =	snd_mtpav_input_बंद,
	.trigger =	snd_mtpav_input_trigger,
पूर्ण;


/*
 * get RAWMIDI resources
 */

अटल व्योम snd_mtpav_set_name(काष्ठा mtpav *chip,
			       काष्ठा snd_rawmidi_substream *substream)
अणु
	अगर (substream->number >= 0 && substream->number < chip->num_ports)
		प्र_लिखो(substream->name, "MTP direct %d", (substream->number % chip->num_ports) + 1);
	अन्यथा अगर (substream->number >= 8 && substream->number < chip->num_ports * 2)
		प्र_लिखो(substream->name, "MTP remote %d", (substream->number % chip->num_ports) + 1);
	अन्यथा अगर (substream->number == chip->num_ports * 2)
		म_नकल(substream->name, "MTP computer");
	अन्यथा अगर (substream->number == chip->num_ports * 2 + 1)
		म_नकल(substream->name, "MTP ADAT");
	अन्यथा
		म_नकल(substream->name, "MTP broadcast");
पूर्ण

अटल पूर्णांक snd_mtpav_get_RAWMIDI(काष्ठा mtpav *mcard)
अणु
	पूर्णांक rval;
	काष्ठा snd_rawmidi *rawmidi;
	काष्ठा snd_rawmidi_substream *substream;
	काष्ठा list_head *list;

	अगर (hwports < 1)
		hwports = 1;
	अन्यथा अगर (hwports > 8)
		hwports = 8;
	mcard->num_ports = hwports;

	अगर ((rval = snd_rawmidi_new(mcard->card, "MotuMIDI", 0,
				    mcard->num_ports * 2 + MTPAV_PIDX_BROADCAST + 1,
				    mcard->num_ports * 2 + MTPAV_PIDX_BROADCAST + 1,
				    &mcard->rmidi)) < 0)
		वापस rval;
	rawmidi = mcard->rmidi;
	rawmidi->निजी_data = mcard;

	list_क्रम_each(list, &rawmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT].substreams) अणु
		substream = list_entry(list, काष्ठा snd_rawmidi_substream, list);
		snd_mtpav_set_name(mcard, substream);
		substream->ops = &snd_mtpav_input;
	पूर्ण
	list_क्रम_each(list, &rawmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT].substreams) अणु
		substream = list_entry(list, काष्ठा snd_rawmidi_substream, list);
		snd_mtpav_set_name(mcard, substream);
		substream->ops = &snd_mtpav_output;
		mcard->ports[substream->number].hwport = translate_subdevice_to_hwport(mcard, substream->number);
	पूर्ण
	rawmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT | SNDRV_RAWMIDI_INFO_INPUT |
			       SNDRV_RAWMIDI_INFO_DUPLEX;
	प्र_लिखो(rawmidi->name, "MTP AV MIDI");
	वापस 0;
पूर्ण

/*
 */

अटल व्योम snd_mtpav_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा mtpav *crd = card->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&crd->spinlock, flags);
	अगर (crd->isसमयr > 0)
		snd_mtpav_हटाओ_output_समयr(crd);
	spin_unlock_irqrestore(&crd->spinlock, flags);
	अगर (crd->irq >= 0)
		मुक्त_irq(crd->irq, (व्योम *)crd);
	release_and_मुक्त_resource(crd->res_port);
पूर्ण

/*
 */
अटल पूर्णांक snd_mtpav_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;
	काष्ठा mtpav *mtp_card;

	err = snd_card_new(&dev->dev, index, id, THIS_MODULE,
			   माप(*mtp_card), &card);
	अगर (err < 0)
		वापस err;

	mtp_card = card->निजी_data;
	spin_lock_init(&mtp_card->spinlock);
	mtp_card->card = card;
	mtp_card->irq = -1;
	mtp_card->share_irq = 0;
	mtp_card->inmidistate = 0;
	mtp_card->ouपंचांगidihwport = 0xffffffff;
	समयr_setup(&mtp_card->समयr, snd_mtpav_output_समयr, 0);

	card->निजी_मुक्त = snd_mtpav_मुक्त;

	err = snd_mtpav_get_RAWMIDI(mtp_card);
	अगर (err < 0)
		जाओ __error;

	mtp_card->inmidiport = mtp_card->num_ports + MTPAV_PIDX_BROADCAST;

	err = snd_mtpav_get_ISA(mtp_card);
	अगर (err < 0)
		जाओ __error;

	म_नकल(card->driver, "MTPAV");
	म_नकल(card->लघुname, "MTPAV on parallel port");
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "MTPAV on parallel port at 0x%lx", port);

	snd_mtpav_portscan(mtp_card);

	err = snd_card_रेजिस्टर(mtp_card->card);
	अगर (err < 0)
		जाओ __error;

	platक्रमm_set_drvdata(dev, card);
	prपूर्णांकk(KERN_INFO "Motu MidiTimePiece on parallel port irq: %d ioport: 0x%lx\n", irq, port);
	वापस 0;

 __error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक snd_mtpav_हटाओ(काष्ठा platक्रमm_device *devptr)
अणु
	snd_card_मुक्त(platक्रमm_get_drvdata(devptr));
	वापस 0;
पूर्ण

#घोषणा SND_MTPAV_DRIVER	"snd_mtpav"

अटल काष्ठा platक्रमm_driver snd_mtpav_driver = अणु
	.probe		= snd_mtpav_probe,
	.हटाओ		= snd_mtpav_हटाओ,
	.driver		= अणु
		.name	= SND_MTPAV_DRIVER,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init alsa_card_mtpav_init(व्योम)
अणु
	पूर्णांक err;

	अगर ((err = platक्रमm_driver_रेजिस्टर(&snd_mtpav_driver)) < 0)
		वापस err;

	device = platक्रमm_device_रेजिस्टर_simple(SND_MTPAV_DRIVER, -1, शून्य, 0);
	अगर (!IS_ERR(device)) अणु
		अगर (platक्रमm_get_drvdata(device))
			वापस 0;
		platक्रमm_device_unरेजिस्टर(device);
		err = -ENODEV;
	पूर्ण अन्यथा
		err = PTR_ERR(device);
	platक्रमm_driver_unरेजिस्टर(&snd_mtpav_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास alsa_card_mtpav_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(device);
	platक्रमm_driver_unरेजिस्टर(&snd_mtpav_driver);
पूर्ण

module_init(alsa_card_mtpav_init)
module_निकास(alsa_card_mtpav_निकास)
