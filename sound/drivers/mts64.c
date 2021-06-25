<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*     
 *   ALSA Driver क्रम Ego Systems Inc. (ESI) Miditerminal 4140
 *   Copyright (c) 2006 by Matthias Kथघnig <mk@phasorlab.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/parport.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/control.h>

#घोषणा CARD_NAME "Miditerminal 4140"
#घोषणा DRIVER_NAME "MTS64"
#घोषणा PLATFORM_DRIVER "snd_mts64"

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

MODULE_AUTHOR("Matthias Koenig <mk@phasorlab.de>");
MODULE_DESCRIPTION("ESI Miditerminal 4140");
MODULE_LICENSE("GPL");

/*********************************************************************
 * Chip specअगरic
 *********************************************************************/
#घोषणा MTS64_NUM_INPUT_PORTS 5
#घोषणा MTS64_NUM_OUTPUT_PORTS 4
#घोषणा MTS64_SMPTE_SUBSTREAM 4

काष्ठा mts64 अणु
	spinlock_t lock;
	काष्ठा snd_card *card;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा pardevice *pardev;
	पूर्णांक खोलो_count;
	पूर्णांक current_midi_output_port;
	पूर्णांक current_midi_input_port;
	u8 mode[MTS64_NUM_INPUT_PORTS];
	काष्ठा snd_rawmidi_substream *midi_input_substream[MTS64_NUM_INPUT_PORTS];
	पूर्णांक smpte_चयन;
	u8 समय[4]; /* [0]=hh, [1]=mm, [2]=ss, [3]=ff */
	u8 fps;
पूर्ण;

अटल पूर्णांक snd_mts64_मुक्त(काष्ठा mts64 *mts)
अणु
	kमुक्त(mts);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mts64_create(काष्ठा snd_card *card,
			    काष्ठा pardevice *pardev,
			    काष्ठा mts64 **rchip)
अणु
	काष्ठा mts64 *mts;

	*rchip = शून्य;

	mts = kzalloc(माप(काष्ठा mts64), GFP_KERNEL);
	अगर (mts == शून्य) 
		वापस -ENOMEM;

	/* Init chip specअगरic data */
	spin_lock_init(&mts->lock);
	mts->card = card;
	mts->pardev = pardev;
	mts->current_midi_output_port = -1;
	mts->current_midi_input_port = -1;

	*rchip = mts;

	वापस 0;
पूर्ण

/*********************************************************************
 * HW रेजिस्टर related स्थिरants
 *********************************************************************/

/* Status Bits */
#घोषणा MTS64_STAT_BSY             0x80
#घोषणा MTS64_STAT_BIT_SET         0x20  /* पढ़ोout process, bit is set */
#घोषणा MTS64_STAT_PORT            0x10  /* पढ़ो byte is a port number */

/* Control Bits */
#घोषणा MTS64_CTL_READOUT          0x08  /* enable पढ़ोout */
#घोषणा MTS64_CTL_WRITE_CMD        0x06  
#घोषणा MTS64_CTL_WRITE_DATA       0x02  
#घोषणा MTS64_CTL_STROBE           0x01  

/* Command */
#घोषणा MTS64_CMD_RESET            0xfe
#घोषणा MTS64_CMD_PROBE            0x8f  /* Used in probing procedure */
#घोषणा MTS64_CMD_SMPTE_SET_TIME   0xe8
#घोषणा MTS64_CMD_SMPTE_SET_FPS    0xee
#घोषणा MTS64_CMD_SMPTE_STOP       0xef
#घोषणा MTS64_CMD_SMPTE_FPS_24     0xe3
#घोषणा MTS64_CMD_SMPTE_FPS_25     0xe2
#घोषणा MTS64_CMD_SMPTE_FPS_2997   0xe4 
#घोषणा MTS64_CMD_SMPTE_FPS_30D    0xe1
#घोषणा MTS64_CMD_SMPTE_FPS_30     0xe0
#घोषणा MTS64_CMD_COM_OPEN         0xf8  /* setting the communication mode */
#घोषणा MTS64_CMD_COM_CLOSE1       0xff  /* clearing communication mode */
#घोषणा MTS64_CMD_COM_CLOSE2       0xf5

/*********************************************************************
 * Hardware specअगरic functions
 *********************************************************************/
अटल व्योम mts64_enable_पढ़ोout(काष्ठा parport *p);
अटल व्योम mts64_disable_पढ़ोout(काष्ठा parport *p);
अटल पूर्णांक mts64_device_पढ़ोy(काष्ठा parport *p);
अटल पूर्णांक mts64_device_init(काष्ठा parport *p);
अटल पूर्णांक mts64_device_खोलो(काष्ठा mts64 *mts);
अटल पूर्णांक mts64_device_बंद(काष्ठा mts64 *mts);
अटल u8 mts64_map_midi_input(u8 c);
अटल पूर्णांक mts64_probe(काष्ठा parport *p);
अटल u16 mts64_पढ़ो(काष्ठा parport *p);
अटल u8 mts64_पढ़ो_अक्षर(काष्ठा parport *p);
अटल व्योम mts64_smpte_start(काष्ठा parport *p,
			      u8 hours, u8 minutes,
			      u8 seconds, u8 frames,
			      u8 idx);
अटल व्योम mts64_smpte_stop(काष्ठा parport *p);
अटल व्योम mts64_ग_लिखो_command(काष्ठा parport *p, u8 c);
अटल व्योम mts64_ग_लिखो_data(काष्ठा parport *p, u8 c);
अटल व्योम mts64_ग_लिखो_midi(काष्ठा mts64 *mts, u8 c, पूर्णांक midiport);


/*  Enables the पढ़ोout procedure
 *
 *  Beक्रमe we can पढ़ो a midi byte from the device, we have to set
 *  bit 3 of control port.
 */
अटल व्योम mts64_enable_पढ़ोout(काष्ठा parport *p)
अणु
	u8 c;

	c = parport_पढ़ो_control(p);
	c |= MTS64_CTL_READOUT;
	parport_ग_लिखो_control(p, c); 
पूर्ण

/*  Disables पढ़ोout 
 *
 *  Reaकरोut is disabled by clearing bit 3 of control
 */
अटल व्योम mts64_disable_पढ़ोout(काष्ठा parport *p)
अणु
	u8 c;

	c = parport_पढ़ो_control(p);
	c &= ~MTS64_CTL_READOUT;
	parport_ग_लिखो_control(p, c);
पूर्ण

/*  रुकोs क्रम device पढ़ोy
 *
 *  Checks अगर BUSY (Bit 7 of status) is clear
 *  1 device पढ़ोy
 *  0 failure
 */
अटल पूर्णांक mts64_device_पढ़ोy(काष्ठा parport *p)
अणु
	पूर्णांक i;
	u8 c;

	क्रम (i = 0; i < 0xffff; ++i) अणु
		c = parport_पढ़ो_status(p);
		c &= MTS64_STAT_BSY;
		अगर (c != 0) 
			वापस 1;
	पूर्ण 

	वापस 0;
पूर्ण

/*  Init device (LED blinking startup magic)
 *
 *  Returns:
 *  0 init ok
 *  -EIO failure
 */
अटल पूर्णांक mts64_device_init(काष्ठा parport *p)
अणु
	पूर्णांक i;

	mts64_ग_लिखो_command(p, MTS64_CMD_RESET);

	क्रम (i = 0; i < 64; ++i) अणु
		msleep(100);

		अगर (mts64_probe(p) == 0) अणु
			/* success */
			mts64_disable_पढ़ोout(p);
			वापस 0;
		पूर्ण
	पूर्ण
	mts64_disable_पढ़ोout(p);

	वापस -EIO;
पूर्ण

/* 
 *  Opens the device (set communication mode)
 */
अटल पूर्णांक mts64_device_खोलो(काष्ठा mts64 *mts)
अणु
	पूर्णांक i;
	काष्ठा parport *p = mts->pardev->port;

	क्रम (i = 0; i < 5; ++i)
		mts64_ग_लिखो_command(p, MTS64_CMD_COM_OPEN);

	वापस 0;
पूर्ण

/*  
 *  Close device (clear communication mode)
 */
अटल पूर्णांक mts64_device_बंद(काष्ठा mts64 *mts)
अणु
	पूर्णांक i;
	काष्ठा parport *p = mts->pardev->port;

	क्रम (i = 0; i < 5; ++i) अणु
		mts64_ग_लिखो_command(p, MTS64_CMD_COM_CLOSE1);
		mts64_ग_लिखो_command(p, MTS64_CMD_COM_CLOSE2);
	पूर्ण

	वापस 0;
पूर्ण

/*  map hardware port to substream number
 * 
 *  When पढ़ोing a byte from the device, the device tells us
 *  on what port the byte is. This HW port has to be mapped to
 *  the midiport (substream number).
 *  substream 0-3 are Midiports 1-4
 *  substream 4 is SMPTE Timecode
 *  The mapping is करोne by the table:
 *  HW | 0 | 1 | 2 | 3 | 4 
 *  SW | 0 | 1 | 4 | 2 | 3
 */
अटल u8 mts64_map_midi_input(u8 c)
अणु
	अटल स्थिर u8 map[] = अणु 0, 1, 4, 2, 3 पूर्ण;

	वापस map[c];
पूर्ण


/*  Probe parport क्रम device
 *
 *  Do we have a Miditerminal 4140 on parport? 
 *  Returns:
 *  0       device found
 *  -ENODEV no device
 */
अटल पूर्णांक mts64_probe(काष्ठा parport *p)
अणु
	u8 c;

	mts64_smpte_stop(p);
	mts64_ग_लिखो_command(p, MTS64_CMD_PROBE);

	msleep(50);
	
	c = mts64_पढ़ो(p);

	c &= 0x00ff;
	अगर (c != MTS64_CMD_PROBE) 
		वापस -ENODEV;
	अन्यथा 
		वापस 0;

पूर्ण

/*  Read byte incl. status from device
 *
 *  Returns:
 *  data in lower 8 bits and status in upper 8 bits
 */
अटल u16 mts64_पढ़ो(काष्ठा parport *p)
अणु
	u8 data, status;

	mts64_device_पढ़ोy(p);
	mts64_enable_पढ़ोout(p);
	status = parport_पढ़ो_status(p);
	data = mts64_पढ़ो_अक्षर(p);
	mts64_disable_पढ़ोout(p);

	वापस (status << 8) | data;
पूर्ण

/*  Read a byte from device
 *
 *  Note, that पढ़ोout mode has to be enabled.
 *  पढ़ोout procedure is as follows: 
 *  - Write number of the Bit to पढ़ो to DATA
 *  - Read STATUS
 *  - Bit 5 of STATUS indicates अगर Bit is set
 *
 *  Returns:
 *  Byte पढ़ो from device
 */
अटल u8 mts64_पढ़ो_अक्षर(काष्ठा parport *p)
अणु
	u8 c = 0;
	u8 status;
	u8 i;

	क्रम (i = 0; i < 8; ++i) अणु
		parport_ग_लिखो_data(p, i);
		c >>= 1;
		status = parport_पढ़ो_status(p);
		अगर (status & MTS64_STAT_BIT_SET) 
			c |= 0x80;
	पूर्ण
	
	वापस c;
पूर्ण

/*  Starts SMPTE Timecode generation
 *
 *  The device creates SMPTE Timecode by hardware.
 *  0 24 fps
 *  1 25 fps
 *  2 29.97 fps
 *  3 30 fps (Drop-frame)
 *  4 30 fps
 */
अटल व्योम mts64_smpte_start(काष्ठा parport *p,
			      u8 hours, u8 minutes,
			      u8 seconds, u8 frames,
			      u8 idx)
अणु
	अटल स्थिर u8 fps[5] = अणु MTS64_CMD_SMPTE_FPS_24,
			     MTS64_CMD_SMPTE_FPS_25,
			     MTS64_CMD_SMPTE_FPS_2997, 
			     MTS64_CMD_SMPTE_FPS_30D,
			     MTS64_CMD_SMPTE_FPS_30    पूर्ण;

	mts64_ग_लिखो_command(p, MTS64_CMD_SMPTE_SET_TIME);
	mts64_ग_लिखो_command(p, frames);
	mts64_ग_लिखो_command(p, seconds);
	mts64_ग_लिखो_command(p, minutes);
	mts64_ग_लिखो_command(p, hours);

	mts64_ग_लिखो_command(p, MTS64_CMD_SMPTE_SET_FPS);
	mts64_ग_लिखो_command(p, fps[idx]);
पूर्ण

/*  Stops SMPTE Timecode generation
 */
अटल व्योम mts64_smpte_stop(काष्ठा parport *p)
अणु
	mts64_ग_लिखो_command(p, MTS64_CMD_SMPTE_STOP);
पूर्ण

/*  Write a command byte to device
 */
अटल व्योम mts64_ग_लिखो_command(काष्ठा parport *p, u8 c)
अणु
	mts64_device_पढ़ोy(p);

	parport_ग_लिखो_data(p, c);

	parport_ग_लिखो_control(p, MTS64_CTL_WRITE_CMD);
	parport_ग_लिखो_control(p, MTS64_CTL_WRITE_CMD | MTS64_CTL_STROBE);
	parport_ग_लिखो_control(p, MTS64_CTL_WRITE_CMD);
पूर्ण

/*  Write a data byte to device 
 */
अटल व्योम mts64_ग_लिखो_data(काष्ठा parport *p, u8 c)
अणु
	mts64_device_पढ़ोy(p);

	parport_ग_लिखो_data(p, c);

	parport_ग_लिखो_control(p, MTS64_CTL_WRITE_DATA);
	parport_ग_लिखो_control(p, MTS64_CTL_WRITE_DATA | MTS64_CTL_STROBE);
	parport_ग_लिखो_control(p, MTS64_CTL_WRITE_DATA);
पूर्ण

/*  Write a MIDI byte to midiport
 *
 *  midiport ranges from 0-3 and maps to Ports 1-4
 *  assumptions: communication mode is on
 */
अटल व्योम mts64_ग_लिखो_midi(काष्ठा mts64 *mts, u8 c,
			     पूर्णांक midiport)
अणु
	काष्ठा parport *p = mts->pardev->port;

	/* check current midiport */
	अगर (mts->current_midi_output_port != midiport)
		mts64_ग_लिखो_command(p, midiport);

	/* ग_लिखो midi byte */
	mts64_ग_लिखो_data(p, c);
पूर्ण

/*********************************************************************
 * Control elements
 *********************************************************************/

/* SMPTE Switch */
#घोषणा snd_mts64_ctl_smpte_चयन_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_mts64_ctl_smpte_चयन_get(काष्ठा snd_kcontrol* kctl,
					  काष्ठा snd_ctl_elem_value *uctl)
अणु
	काष्ठा mts64 *mts = snd_kcontrol_chip(kctl);

	spin_lock_irq(&mts->lock);
	uctl->value.पूर्णांकeger.value[0] = mts->smpte_चयन;
	spin_unlock_irq(&mts->lock);

	वापस 0;
पूर्ण

/* smpte_चयन is not accessed from IRQ handler, so we just need
   to protect the HW access */
अटल पूर्णांक snd_mts64_ctl_smpte_चयन_put(काष्ठा snd_kcontrol* kctl,
					  काष्ठा snd_ctl_elem_value *uctl)
अणु
	काष्ठा mts64 *mts = snd_kcontrol_chip(kctl);
	पूर्णांक changed = 0;
	पूर्णांक val = !!uctl->value.पूर्णांकeger.value[0];

	spin_lock_irq(&mts->lock);
	अगर (mts->smpte_चयन == val)
		जाओ __out;

	changed = 1;
	mts->smpte_चयन = val;
	अगर (mts->smpte_चयन) अणु
		mts64_smpte_start(mts->pardev->port,
				  mts->समय[0], mts->समय[1],
				  mts->समय[2], mts->समय[3],
				  mts->fps);
	पूर्ण अन्यथा अणु
		mts64_smpte_stop(mts->pardev->port);
	पूर्ण
__out:
	spin_unlock_irq(&mts->lock);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mts64_ctl_smpte_चयन = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_RAWMIDI,
	.name  = "SMPTE Playback Switch",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value = 0,
	.info = snd_mts64_ctl_smpte_चयन_info,
	.get  = snd_mts64_ctl_smpte_चयन_get,
	.put  = snd_mts64_ctl_smpte_चयन_put
पूर्ण;

/* Time */
अटल पूर्णांक snd_mts64_ctl_smpte_समय_h_info(काष्ठा snd_kcontrol *kctl,
					   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 23;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mts64_ctl_smpte_समय_f_info(काष्ठा snd_kcontrol *kctl,
					   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 99;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mts64_ctl_smpte_समय_info(काष्ठा snd_kcontrol *kctl,
					 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 59;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_mts64_ctl_smpte_समय_get(काष्ठा snd_kcontrol *kctl,
					काष्ठा snd_ctl_elem_value *uctl)
अणु
	काष्ठा mts64 *mts = snd_kcontrol_chip(kctl);
	पूर्णांक idx = kctl->निजी_value;

	spin_lock_irq(&mts->lock);
	uctl->value.पूर्णांकeger.value[0] = mts->समय[idx];
	spin_unlock_irq(&mts->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_mts64_ctl_smpte_समय_put(काष्ठा snd_kcontrol *kctl,
					काष्ठा snd_ctl_elem_value *uctl)
अणु
	काष्ठा mts64 *mts = snd_kcontrol_chip(kctl);
	पूर्णांक idx = kctl->निजी_value;
	अचिन्हित पूर्णांक समय = uctl->value.पूर्णांकeger.value[0] % 60;
	पूर्णांक changed = 0;

	spin_lock_irq(&mts->lock);
	अगर (mts->समय[idx] != समय) अणु
		changed = 1;
		mts->समय[idx] = समय;
	पूर्ण
	spin_unlock_irq(&mts->lock);

	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mts64_ctl_smpte_समय_hours = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_RAWMIDI,
	.name  = "SMPTE Time Hours",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value = 0,
	.info = snd_mts64_ctl_smpte_समय_h_info,
	.get  = snd_mts64_ctl_smpte_समय_get,
	.put  = snd_mts64_ctl_smpte_समय_put
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mts64_ctl_smpte_समय_minutes = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_RAWMIDI,
	.name  = "SMPTE Time Minutes",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value = 1,
	.info = snd_mts64_ctl_smpte_समय_info,
	.get  = snd_mts64_ctl_smpte_समय_get,
	.put  = snd_mts64_ctl_smpte_समय_put
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mts64_ctl_smpte_समय_seconds = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_RAWMIDI,
	.name  = "SMPTE Time Seconds",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value = 2,
	.info = snd_mts64_ctl_smpte_समय_info,
	.get  = snd_mts64_ctl_smpte_समय_get,
	.put  = snd_mts64_ctl_smpte_समय_put
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mts64_ctl_smpte_समय_frames = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_RAWMIDI,
	.name  = "SMPTE Time Frames",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value = 3,
	.info = snd_mts64_ctl_smpte_समय_f_info,
	.get  = snd_mts64_ctl_smpte_समय_get,
	.put  = snd_mts64_ctl_smpte_समय_put
पूर्ण;

/* FPS */
अटल पूर्णांक snd_mts64_ctl_smpte_fps_info(काष्ठा snd_kcontrol *kctl,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[5] = अणु
		"24", "25", "29.97", "30D", "30"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 5, texts);
पूर्ण

अटल पूर्णांक snd_mts64_ctl_smpte_fps_get(काष्ठा snd_kcontrol *kctl,
				       काष्ठा snd_ctl_elem_value *uctl)
अणु
	काष्ठा mts64 *mts = snd_kcontrol_chip(kctl);

	spin_lock_irq(&mts->lock);
	uctl->value.क्रमागतerated.item[0] = mts->fps;
	spin_unlock_irq(&mts->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_mts64_ctl_smpte_fps_put(काष्ठा snd_kcontrol *kctl,
				       काष्ठा snd_ctl_elem_value *uctl)
अणु
	काष्ठा mts64 *mts = snd_kcontrol_chip(kctl);
	पूर्णांक changed = 0;

	अगर (uctl->value.क्रमागतerated.item[0] >= 5)
		वापस -EINVAL;
	spin_lock_irq(&mts->lock);
	अगर (mts->fps != uctl->value.क्रमागतerated.item[0]) अणु
		changed = 1;
		mts->fps = uctl->value.क्रमागतerated.item[0];
	पूर्ण
	spin_unlock_irq(&mts->lock);

	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mts64_ctl_smpte_fps = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_RAWMIDI,
	.name  = "SMPTE Fps",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value = 0,
	.info  = snd_mts64_ctl_smpte_fps_info,
	.get   = snd_mts64_ctl_smpte_fps_get,
	.put   = snd_mts64_ctl_smpte_fps_put
पूर्ण;


अटल पूर्णांक snd_mts64_ctl_create(काष्ठा snd_card *card,
				काष्ठा mts64 *mts)
अणु
	पूर्णांक err, i;
	अटल स्थिर काष्ठा snd_kcontrol_new *control[] = अणु
		&mts64_ctl_smpte_चयन,
		&mts64_ctl_smpte_समय_hours,
		&mts64_ctl_smpte_समय_minutes,
		&mts64_ctl_smpte_समय_seconds,
		&mts64_ctl_smpte_समय_frames,
		&mts64_ctl_smpte_fps,
	        शून्य  पूर्ण;

	क्रम (i = 0; control[i]; ++i) अणु
		err = snd_ctl_add(card, snd_ctl_new1(control[i], mts));
		अगर (err < 0) अणु
			snd_prपूर्णांकd("Cannot create control: %s\n", 
				   control[i]->name);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*********************************************************************
 * Rawmidi
 *********************************************************************/
#घोषणा MTS64_MODE_INPUT_TRIGGERED 0x01

अटल पूर्णांक snd_mts64_rawmidi_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा mts64 *mts = substream->rmidi->निजी_data;

	अगर (mts->खोलो_count == 0) अणु
		/* We करोn't need a spinlock here, because this is just called 
		   अगर the device has not been खोलोed beक्रमe. 
		   So there aren't any IRQs from the device */
		mts64_device_खोलो(mts);

		msleep(50);
	पूर्ण
	++(mts->खोलो_count);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_mts64_rawmidi_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा mts64 *mts = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	--(mts->खोलो_count);
	अगर (mts->खोलो_count == 0) अणु
		/* We need the spinlock_irqsave here because we can still
		   have IRQs at this poपूर्णांक */
		spin_lock_irqsave(&mts->lock, flags);
		mts64_device_बंद(mts);
		spin_unlock_irqrestore(&mts->lock, flags);

		msleep(500);

	पूर्ण अन्यथा अगर (mts->खोलो_count < 0)
		mts->खोलो_count = 0;

	वापस 0;
पूर्ण

अटल व्योम snd_mts64_rawmidi_output_trigger(काष्ठा snd_rawmidi_substream *substream,
					     पूर्णांक up)
अणु
	काष्ठा mts64 *mts = substream->rmidi->निजी_data;
	u8 data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mts->lock, flags);
	जबतक (snd_rawmidi_transmit_peek(substream, &data, 1) == 1) अणु
		mts64_ग_लिखो_midi(mts, data, substream->number+1);
		snd_rawmidi_transmit_ack(substream, 1);
	पूर्ण
	spin_unlock_irqrestore(&mts->lock, flags);
पूर्ण

अटल व्योम snd_mts64_rawmidi_input_trigger(काष्ठा snd_rawmidi_substream *substream,
					    पूर्णांक up)
अणु
	काष्ठा mts64 *mts = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mts->lock, flags);
	अगर (up)
		mts->mode[substream->number] |= MTS64_MODE_INPUT_TRIGGERED;
	अन्यथा
 		mts->mode[substream->number] &= ~MTS64_MODE_INPUT_TRIGGERED;
	
	spin_unlock_irqrestore(&mts->lock, flags);
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops snd_mts64_rawmidi_output_ops = अणु
	.खोलो    = snd_mts64_rawmidi_खोलो,
	.बंद   = snd_mts64_rawmidi_बंद,
	.trigger = snd_mts64_rawmidi_output_trigger
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_mts64_rawmidi_input_ops = अणु
	.खोलो    = snd_mts64_rawmidi_खोलो,
	.बंद   = snd_mts64_rawmidi_बंद,
	.trigger = snd_mts64_rawmidi_input_trigger
पूर्ण;

/* Create and initialize the rawmidi component */
अटल पूर्णांक snd_mts64_rawmidi_create(काष्ठा snd_card *card)
अणु
	काष्ठा mts64 *mts = card->निजी_data;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *substream;
	काष्ठा list_head *list;
	पूर्णांक err;
	
	err = snd_rawmidi_new(card, CARD_NAME, 0, 
			      MTS64_NUM_OUTPUT_PORTS, 
			      MTS64_NUM_INPUT_PORTS, 
			      &rmidi);
	अगर (err < 0) 
		वापस err;

	rmidi->निजी_data = mts;
	म_नकल(rmidi->name, CARD_NAME);
	rmidi->info_flags = SNDRV_RAWMIDI_INFO_OUTPUT |
		            SNDRV_RAWMIDI_INFO_INPUT |
                            SNDRV_RAWMIDI_INFO_DUPLEX;

	mts->rmidi = rmidi;

	/* रेजिस्टर rawmidi ops */
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, 
			    &snd_mts64_rawmidi_output_ops);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, 
			    &snd_mts64_rawmidi_input_ops);

	/* name substreams */
	/* output */
	list_क्रम_each(list, 
		      &rmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT].substreams) अणु
		substream = list_entry(list, काष्ठा snd_rawmidi_substream, list);
		प्र_लिखो(substream->name,
			"Miditerminal %d", substream->number+1);
	पूर्ण
	/* input */
	list_क्रम_each(list, 
		      &rmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT].substreams) अणु
		substream = list_entry(list, काष्ठा snd_rawmidi_substream, list);
		mts->midi_input_substream[substream->number] = substream;
		चयन(substream->number) अणु
		हाल MTS64_SMPTE_SUBSTREAM:
			म_नकल(substream->name, "Miditerminal SMPTE");
			अवरोध;
		शेष:
			प्र_लिखो(substream->name,
				"Miditerminal %d", substream->number+1);
		पूर्ण
	पूर्ण

	/* controls */
	err = snd_mts64_ctl_create(card, mts);

	वापस err;
पूर्ण

/*********************************************************************
 * parport stuff
 *********************************************************************/
अटल व्योम snd_mts64_पूर्णांकerrupt(व्योम *निजी)
अणु
	काष्ठा mts64 *mts = ((काष्ठा snd_card*)निजी)->निजी_data;
	u16 ret;
	u8 status, data;
	काष्ठा snd_rawmidi_substream *substream;

	spin_lock(&mts->lock);
	ret = mts64_पढ़ो(mts->pardev->port);
	data = ret & 0x00ff;
	status = ret >> 8;

	अगर (status & MTS64_STAT_PORT) अणु
		mts->current_midi_input_port = mts64_map_midi_input(data);
	पूर्ण अन्यथा अणु
		अगर (mts->current_midi_input_port == -1) 
			जाओ __out;
		substream = mts->midi_input_substream[mts->current_midi_input_port];
		अगर (mts->mode[substream->number] & MTS64_MODE_INPUT_TRIGGERED)
			snd_rawmidi_receive(substream, &data, 1);
	पूर्ण
__out:
	spin_unlock(&mts->lock);
पूर्ण

अटल व्योम snd_mts64_attach(काष्ठा parport *p)
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

अटल व्योम snd_mts64_detach(काष्ठा parport *p)
अणु
	/* nothing to करो here */
पूर्ण

अटल पूर्णांक snd_mts64_dev_probe(काष्ठा pardevice *pardev)
अणु
	अगर (म_भेद(pardev->name, DRIVER_NAME))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल काष्ठा parport_driver mts64_parport_driver = अणु
	.name		= "mts64",
	.probe		= snd_mts64_dev_probe,
	.match_port	= snd_mts64_attach,
	.detach		= snd_mts64_detach,
	.devmodel	= true,
पूर्ण;

/*********************************************************************
 * platक्रमm stuff
 *********************************************************************/
अटल व्योम snd_mts64_card_निजी_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा mts64 *mts = card->निजी_data;
	काष्ठा pardevice *pardev = mts->pardev;

	अगर (pardev) अणु
		parport_release(pardev);
		parport_unरेजिस्टर_device(pardev);
	पूर्ण

	snd_mts64_मुक्त(mts);
पूर्ण

अटल पूर्णांक snd_mts64_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pardevice *pardev;
	काष्ठा parport *p;
	पूर्णांक dev = pdev->id;
	काष्ठा snd_card *card = शून्य;
	काष्ठा mts64 *mts = शून्य;
	पूर्णांक err;
	काष्ठा pardev_cb mts64_cb = अणु
		.preempt = शून्य,
		.wakeup = शून्य,
		.irq_func = snd_mts64_पूर्णांकerrupt,	/* ISR */
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
	म_नकल(card->लघुname, "ESI " CARD_NAME);
	प्र_लिखो(card->दीर्घname,  "%s at 0x%lx, irq %i", 
		card->लघुname, p->base, p->irq);

	mts64_cb.निजी = card;			 /* निजी */
	pardev = parport_रेजिस्टर_dev_model(p,		 /* port */
					    DRIVER_NAME, /* name */
					    &mts64_cb,	 /* callbacks */
					    pdev->id);	 /* device number */
	अगर (!pardev) अणु
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

	अगर ((err = snd_mts64_create(card, pardev, &mts)) < 0) अणु
		snd_prपूर्णांकd("Cannot create main component\n");
		जाओ release_pardev;
	पूर्ण
	card->निजी_data = mts;
	card->निजी_मुक्त = snd_mts64_card_निजी_मुक्त;

	err = mts64_probe(p);
	अगर (err) अणु
		err = -EIO;
		जाओ __err;
	पूर्ण
	
	अगर ((err = snd_mts64_rawmidi_create(card)) < 0) अणु
		snd_prपूर्णांकd("Creating Rawmidi component failed\n");
		जाओ __err;
	पूर्ण

	/* init device */
	अगर ((err = mts64_device_init(p)) < 0)
		जाओ __err;

	platक्रमm_set_drvdata(pdev, card);

	/* At this poपूर्णांक card will be usable */
	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_prपूर्णांकd("Cannot register card\n");
		जाओ __err;
	पूर्ण

	snd_prपूर्णांकk(KERN_INFO "ESI Miditerminal 4140 on 0x%lx\n", p->base);
	वापस 0;

release_pardev:
	parport_release(pardev);
मुक्त_pardev:
	parport_unरेजिस्टर_device(pardev);
__err:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक snd_mts64_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_card *card = platक्रमm_get_drvdata(pdev);

	अगर (card)
		snd_card_मुक्त(card);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver snd_mts64_driver = अणु
	.probe  = snd_mts64_probe,
	.हटाओ = snd_mts64_हटाओ,
	.driver = अणु
		.name = PLATFORM_DRIVER,
	पूर्ण
पूर्ण;

/*********************************************************************
 * module init stuff
 *********************************************************************/
अटल व्योम snd_mts64_unरेजिस्टर_all(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SNDRV_CARDS; ++i) अणु
		अगर (platक्रमm_devices[i]) अणु
			platक्रमm_device_unरेजिस्टर(platक्रमm_devices[i]);
			platक्रमm_devices[i] = शून्य;
		पूर्ण
	पूर्ण		
	platक्रमm_driver_unरेजिस्टर(&snd_mts64_driver);
	parport_unरेजिस्टर_driver(&mts64_parport_driver);
पूर्ण

अटल पूर्णांक __init snd_mts64_module_init(व्योम)
अणु
	पूर्णांक err;

	अगर ((err = platक्रमm_driver_रेजिस्टर(&snd_mts64_driver)) < 0)
		वापस err;

	अगर (parport_रेजिस्टर_driver(&mts64_parport_driver) != 0) अणु
		platक्रमm_driver_unरेजिस्टर(&snd_mts64_driver);
		वापस -EIO;
	पूर्ण

	अगर (device_count == 0) अणु
		snd_mts64_unरेजिस्टर_all();
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास snd_mts64_module_निकास(व्योम)
अणु
	snd_mts64_unरेजिस्टर_all();
पूर्ण

module_init(snd_mts64_module_init);
module_निकास(snd_mts64_module_निकास);
