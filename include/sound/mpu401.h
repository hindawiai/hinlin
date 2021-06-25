<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_MPU401_H
#घोषणा __SOUND_MPU401_H

/*
 *  Header file क्रम MPU-401 and compatible cards
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <sound/rawmidi.h>
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा MPU401_HW_MPU401		1	/* native MPU401 */
#घोषणा MPU401_HW_SB			2	/* SoundBlaster MPU-401 UART */
#घोषणा MPU401_HW_ES1688		3	/* AudioDrive ES1688 MPU-401 UART */
#घोषणा MPU401_HW_OPL3SA2		4	/* Yamaha OPL3-SA2 */
#घोषणा MPU401_HW_SONICVIBES		5	/* S3 SonicVibes */
#घोषणा MPU401_HW_CS4232		6	/* CS4232 */
#घोषणा MPU401_HW_ES18XX		7	/* AudioDrive ES18XX MPU-401 UART */
#घोषणा MPU401_HW_FM801			8	/* ForteMedia FM801 */
#घोषणा MPU401_HW_TRID4DWAVE		9	/* Trident 4DWave */
#घोषणा MPU401_HW_AZT2320		10	/* Aztech AZT2320 */
#घोषणा MPU401_HW_ALS100		11	/* Avance Logic ALS100 */
#घोषणा MPU401_HW_ICE1712		12	/* Envy24 */
#घोषणा MPU401_HW_VIA686A		13	/* VIA 82C686A */
#घोषणा MPU401_HW_YMFPCI		14	/* YMF DS-XG PCI */
#घोषणा MPU401_HW_CMIPCI		15	/* CMIPCI MPU-401 UART */
#घोषणा MPU401_HW_ALS4000		16	/* Avance Logic ALS4000 */
#घोषणा MPU401_HW_INTEL8X0		17	/* Intel8x0 driver */
#घोषणा MPU401_HW_PC98II		18	/* Roland PC98II */
#घोषणा MPU401_HW_AUREAL		19	/* Aureal Vortex */

#घोषणा MPU401_INFO_INPUT	(1 << 0)	/* input stream */
#घोषणा MPU401_INFO_OUTPUT	(1 << 1)	/* output stream */
#घोषणा MPU401_INFO_INTEGRATED	(1 << 2)	/* पूर्णांकegrated h/w port */
#घोषणा MPU401_INFO_MMIO	(1 << 3)	/* MMIO access */
#घोषणा MPU401_INFO_TX_IRQ	(1 << 4)	/* independent TX irq */
#घोषणा MPU401_INFO_IRQ_HOOK	(1 << 5)	/* mpu401 irq handler is called
						   from driver irq handler */
#घोषणा MPU401_INFO_NO_ACK	(1 << 6)	/* No ACK cmd needed */
#घोषणा MPU401_INFO_USE_TIMER	(1 << 15)	/* पूर्णांकernal */

#घोषणा MPU401_MODE_BIT_INPUT		0
#घोषणा MPU401_MODE_BIT_OUTPUT		1
#घोषणा MPU401_MODE_BIT_INPUT_TRIGGER	2
#घोषणा MPU401_MODE_BIT_OUTPUT_TRIGGER	3

#घोषणा MPU401_MODE_INPUT		(1<<MPU401_MODE_BIT_INPUT)
#घोषणा MPU401_MODE_OUTPUT		(1<<MPU401_MODE_BIT_OUTPUT)
#घोषणा MPU401_MODE_INPUT_TRIGGER	(1<<MPU401_MODE_BIT_INPUT_TRIGGER)
#घोषणा MPU401_MODE_OUTPUT_TRIGGER	(1<<MPU401_MODE_BIT_OUTPUT_TRIGGER)

#घोषणा MPU401_MODE_INPUT_TIMER		(1<<0)
#घोषणा MPU401_MODE_OUTPUT_TIMER	(1<<1)

काष्ठा snd_mpu401 अणु
	काष्ठा snd_rawmidi *rmidi;

	अचिन्हित लघु hardware;	/* MPU401_HW_XXXX */
	अचिन्हित पूर्णांक info_flags;	/* MPU401_INFO_XXX */
	अचिन्हित दीर्घ port;		/* base port of MPU-401 chip */
	अचिन्हित दीर्घ cport;		/* port + 1 (usually) */
	काष्ठा resource *res;		/* port resource */
	पूर्णांक irq;			/* IRQ number of MPU-401 chip */

	अचिन्हित दीर्घ mode;		/* MPU401_MODE_XXXX */
	पूर्णांक समयr_invoked;

	पूर्णांक (*खोलो_input) (काष्ठा snd_mpu401 * mpu);
	व्योम (*बंद_input) (काष्ठा snd_mpu401 * mpu);
	पूर्णांक (*खोलो_output) (काष्ठा snd_mpu401 * mpu);
	व्योम (*बंद_output) (काष्ठा snd_mpu401 * mpu);
	व्योम *निजी_data;

	काष्ठा snd_rawmidi_substream *substream_input;
	काष्ठा snd_rawmidi_substream *substream_output;

	spinlock_t input_lock;
	spinlock_t output_lock;
	spinlock_t समयr_lock;
	
	काष्ठा समयr_list समयr;

	व्योम (*ग_लिखो) (काष्ठा snd_mpu401 * mpu, अचिन्हित अक्षर data, अचिन्हित दीर्घ addr);
	अचिन्हित अक्षर (*पढ़ो) (काष्ठा snd_mpu401 *mpu, अचिन्हित दीर्घ addr);
पूर्ण;

/* I/O ports */

#घोषणा MPU401C(mpu) (mpu)->cport
#घोषणा MPU401D(mpu) (mpu)->port

/*
 * control रेजिस्टर bits
 */
/* पढ़ो MPU401C() */
#घोषणा MPU401_RX_EMPTY		0x80
#घोषणा MPU401_TX_FULL		0x40

/* ग_लिखो MPU401C() */
#घोषणा MPU401_RESET		0xff
#घोषणा MPU401_ENTER_UART	0x3f

/* पढ़ो MPU401D() */
#घोषणा MPU401_ACK		0xfe


/*

 */

irqवापस_t snd_mpu401_uart_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
irqवापस_t snd_mpu401_uart_पूर्णांकerrupt_tx(पूर्णांक irq, व्योम *dev_id);

पूर्णांक snd_mpu401_uart_new(काष्ठा snd_card *card,
			पूर्णांक device,
			अचिन्हित लघु hardware,
			अचिन्हित दीर्घ port,
			अचिन्हित पूर्णांक info_flags,
			पूर्णांक irq,
			काष्ठा snd_rawmidi ** rrawmidi);

#पूर्ण_अगर /* __SOUND_MPU401_H */
