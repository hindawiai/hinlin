<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Routines क्रम control of MPU-401 in UART mode
 *
 *   Modअगरied क्रम the Aureal Vortex based Soundcards
 *   by Manuel Jander (mjande@embedded.cl).
 */

#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <sound/core.h>
#समावेश <sound/mpu401.h>
#समावेश "au88x0.h"

/* Check क्रम mpu401 mmio support. */
/* MPU401 legacy support is only provided as a emergency fallback *
 * क्रम older versions of ALSA. Its usage is strongly discouraged. */
#अगर_अघोषित MPU401_HW_AUREAL
#घोषणा VORTEX_MPU401_LEGACY
#पूर्ण_अगर

/* Vortex MPU401 defines. */
#घोषणा MIDI_CLOCK_DIV      0x61
/* Standart MPU401 defines. */
#घोषणा MPU401_RESET		0xff
#घोषणा MPU401_ENTER_UART	0x3f
#घोषणा MPU401_ACK		    0xfe

अटल पूर्णांक snd_vortex_midi(vortex_t *vortex)
अणु
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक temp, mode;
	काष्ठा snd_mpu401 *mpu;
	अचिन्हित दीर्घ port;

#अगर_घोषित VORTEX_MPU401_LEGACY
	/* EnableHardCodedMPU401Port() */
	/* Enable Legacy MIDI Interface port. */
	port = (0x03 << 5);	/* FIXME: अटल address. 0x330 */
	temp =
	    (hwपढ़ो(vortex->mmio, VORTEX_CTRL) & ~CTRL_MIDI_PORT) |
	    CTRL_MIDI_EN | port;
	hwग_लिखो(vortex->mmio, VORTEX_CTRL, temp);
#अन्यथा
	/* Disable Legacy MIDI Interface port. */
	temp =
	    (hwपढ़ो(vortex->mmio, VORTEX_CTRL) & ~CTRL_MIDI_PORT) &
	    ~CTRL_MIDI_EN;
	hwग_लिखो(vortex->mmio, VORTEX_CTRL, temp);
#पूर्ण_अगर
	/* Mpu401UartInit() */
	mode = 1;
	temp = hwपढ़ो(vortex->mmio, VORTEX_CTRL2) & 0xffff00cf;
	temp |= (MIDI_CLOCK_DIV << 8) | ((mode >> 24) & 0xff) << 4;
	hwग_लिखो(vortex->mmio, VORTEX_CTRL2, temp);
	hwग_लिखो(vortex->mmio, VORTEX_MIDI_CMD, MPU401_RESET);

	/* Check अगर anything is OK. */
	temp = hwपढ़ो(vortex->mmio, VORTEX_MIDI_DATA);
	अगर (temp != MPU401_ACK /*0xfe */ ) अणु
		dev_err(vortex->card->dev, "midi port doesn't acknowledge!\n");
		वापस -ENODEV;
	पूर्ण
	/* Enable MPU401 पूर्णांकerrupts. */
	hwग_लिखो(vortex->mmio, VORTEX_IRQ_CTRL,
		hwपढ़ो(vortex->mmio, VORTEX_IRQ_CTRL) | IRQ_MIDI);

	/* Create MPU401 instance. */
#अगर_घोषित VORTEX_MPU401_LEGACY
	अगर ((temp =
	     snd_mpu401_uart_new(vortex->card, 0, MPU401_HW_MPU401, 0x330,
				 MPU401_INFO_IRQ_HOOK, -1, &rmidi)) != 0) अणु
		hwग_लिखो(vortex->mmio, VORTEX_CTRL,
			(hwपढ़ो(vortex->mmio, VORTEX_CTRL) &
			 ~CTRL_MIDI_PORT) & ~CTRL_MIDI_EN);
		वापस temp;
	पूर्ण
#अन्यथा
	port = (अचिन्हित दीर्घ)(vortex->mmio + VORTEX_MIDI_DATA);
	अगर ((temp =
	     snd_mpu401_uart_new(vortex->card, 0, MPU401_HW_AUREAL, port,
				 MPU401_INFO_INTEGRATED | MPU401_INFO_MMIO |
				 MPU401_INFO_IRQ_HOOK, -1, &rmidi)) != 0) अणु
		hwग_लिखो(vortex->mmio, VORTEX_CTRL,
			(hwपढ़ो(vortex->mmio, VORTEX_CTRL) &
			 ~CTRL_MIDI_PORT) & ~CTRL_MIDI_EN);
		वापस temp;
	पूर्ण
	mpu = rmidi->निजी_data;
	mpu->cport = (अचिन्हित दीर्घ)(vortex->mmio + VORTEX_MIDI_CMD);
#पूर्ण_अगर
	/* Overग_लिखो MIDI name */
	snम_लिखो(rmidi->name, माप(rmidi->name), "%s MIDI %d", CARD_NAME_SHORT , vortex->card->number);

	vortex->rmidi = rmidi;
	वापस 0;
पूर्ण
