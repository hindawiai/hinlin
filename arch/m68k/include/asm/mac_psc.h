<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Apple Peripheral System Controller (PSC)
 *
 * The PSC is used on the AV Macs to control IO functions not handled
 * by the VIAs (Ethernet, DSP, SCC, Sound). This includes nine DMA
 * channels.
 *
 * The first seven DMA channels appear to be "one-shot" and are actually
 * sets of two channels; one member is active जबतक the other is being
 * configured, and then you flip the active member and start all over again.
 * The one-shot channels are grouped together and are:
 *
 * 1. SCSI
 * 2. Ethernet Read
 * 3. Ethernet Write
 * 4. Floppy Disk Controller
 * 5. SCC Channel A Receive
 * 6. SCC Channel B Receive
 * 7. SCC Channel A Transmit
 *
 * The reमुख्यing two channels are handled somewhat dअगरferently. They appear
 * to be बंदly tied and share one set of रेजिस्टरs. They also seem to run
 * continuously, although how you keep the buffer filled in this scenario is
 * not understood as there seems to be only one input and one output buffer
 * poपूर्णांकer.
 *
 * Much of this was extrapolated from what was known about the Ethernet
 * रेजिस्टरs and subsequently confirmed using MacsBug (ie by pinging the
 * machine with easy-to-find patterns and looking क्रम them in the DMA
 * buffers, or by sending a file over the serial ports and finding the
 * file in the buffers.)
 *
 * 1999-05-25 (jmt)
 */

#घोषणा PSC_BASE	(0x50F31000)

/*
 * The IER/IFR रेजिस्टरs work like the VIA, except that it has 4
 * of them each on dअगरferent पूर्णांकerrupt levels, and each रेजिस्टर
 * set only seems to handle four पूर्णांकerrupts instead of seven.
 *
 * To access a particular set of रेजिस्टरs, add 0xn0 to the base
 * where n = 3,4,5 or 6.
 */

#घोषणा pIFRbase	0x100
#घोषणा pIERbase	0x104

/*
 * One-shot DMA control रेजिस्टरs
 */

#घोषणा PSC_MYSTERY	0x804

#घोषणा PSC_CTL_BASE	0xC00

#घोषणा PSC_SCSI_CTL	0xC00
#घोषणा PSC_ENETRD_CTL  0xC10
#घोषणा PSC_ENETWR_CTL  0xC20
#घोषणा PSC_FDC_CTL	0xC30
#घोषणा PSC_SCCA_CTL	0xC40
#घोषणा PSC_SCCB_CTL	0xC50
#घोषणा PSC_SCCATX_CTL	0xC60

/*
 * DMA channels. Add +0x10 क्रम the second channel in the set.
 * You're supposed to use one channel जबतक the other runs and
 * then flip channels and करो the whole thing again.
 */

#घोषणा PSC_ADDR_BASE	0x1000
#घोषणा PSC_LEN_BASE	0x1004
#घोषणा PSC_CMD_BASE	0x1008

#घोषणा PSC_SET0	0x00
#घोषणा PSC_SET1	0x10

#घोषणा PSC_SCSI_ADDR	0x1000	/* confirmed */
#घोषणा PSC_SCSI_LEN	0x1004	/* confirmed */
#घोषणा PSC_SCSI_CMD	0x1008	/* confirmed */
#घोषणा PSC_ENETRD_ADDR 0x1020	/* confirmed */
#घोषणा PSC_ENETRD_LEN  0x1024	/* confirmed */
#घोषणा PSC_ENETRD_CMD  0x1028	/* confirmed */
#घोषणा PSC_ENETWR_ADDR 0x1040	/* confirmed */
#घोषणा PSC_ENETWR_LEN  0x1044	/* confirmed */
#घोषणा PSC_ENETWR_CMD  0x1048	/* confirmed */
#घोषणा PSC_FDC_ADDR	0x1060	/* strongly suspected */
#घोषणा PSC_FDC_LEN	0x1064	/* strongly suspected */
#घोषणा PSC_FDC_CMD	0x1068	/* strongly suspected */
#घोषणा PSC_SCCA_ADDR	0x1080	/* confirmed */
#घोषणा PSC_SCCA_LEN	0x1084	/* confirmed */
#घोषणा PSC_SCCA_CMD	0x1088	/* confirmed */
#घोषणा PSC_SCCB_ADDR	0x10A0	/* confirmed */
#घोषणा PSC_SCCB_LEN	0x10A4	/* confirmed */
#घोषणा PSC_SCCB_CMD	0x10A8	/* confirmed */
#घोषणा PSC_SCCATX_ADDR	0x10C0	/* confirmed */
#घोषणा PSC_SCCATX_LEN	0x10C4	/* confirmed */
#घोषणा PSC_SCCATX_CMD	0x10C8	/* confirmed */

/*
 * Free-running DMA रेजिस्टरs. The only part known क्रम sure are the bits in
 * the control रेजिस्टर, the buffer addresses and the buffer length. Everything
 * अन्यथा is anybody's guess.
 *
 * These रेजिस्टरs seem to be mirrored every thirty-two bytes up until offset
 * 0x300. It's safe to assume then that a new set of रेजिस्टरs starts there.
 */

#घोषणा PSC_SND_CTL	0x200	/*
				 * [ 16-bit ]
				 * Sound (Singer?) control रेजिस्टर.
				 *
				 * bit 0  : ????
				 * bit 1  : ????
				 * bit 2  : Set to one to enable sound
				 *          output. Possibly a mute flag.
				 * bit 3  : ????
				 * bit 4  : ????
				 * bit 5  : ????
				 * bit 6  : Set to one to enable pass-thru
				 *          audio. In this mode the audio data
				 *          seems to appear in both the input
				 *          buffer and the output buffer.
				 * bit 7  : Set to one to activate the
				 *          sound input DMA or zero to
				 *          disable it.
				 * bit 8  : Set to one to activate the
				 *          sound output DMA or zero to
				 *          disable it.
				 * bit 9  : \
				 * bit 11 :  |
				 *          These two bits control the sample
				 *          rate. Usually set to binary 10 and
				 *	    MacOS 8.0 says I'm at 48 KHz. Using
				 *	    a binary value of 01 makes things
				 *	    sound about 1/2 speed (24 KHz?) and
				 *          binary 00 is slower still (22 KHz?)
				 *
				 * Setting this to 0x0000 is a good way to
				 * समाप्त all DMA at boot समय so that the
				 * PSC won't overग_लिखो the kernel image
				 * with sound data.
				 */

/*
 * 0x0202 - 0x0203 is unused. Writing there
 * seems to clobber the control रेजिस्टर.
 */

#घोषणा PSC_SND_SOURCE	0x204	/*
				 * [ 32-bit ]
				 * Controls input source and volume:
				 *
				 * bits 12-15 : input source volume, 0 - F
				 * bits 16-19 : unknown, always 0x5
				 * bits 20-23 : input source selection:
				 *                  0x3 = CD Audio
				 *                  0x4 = External Audio
				 *
				 * The volume is definitely not the general
				 * output volume as it करोesn't affect the
				 * alert sound volume.
				 */
#घोषणा PSC_SND_STATUS1	0x208	/*
				 * [ 32-bit ]
				 * Appears to be a पढ़ो-only status रेजिस्टर.
				 * The usual value is 0x00400002.
				 */
#घोषणा PSC_SND_HUH3	0x20C	/*
				 * [ 16-bit ]
				 * Unknown 16-bit value, always 0x0000.
				 */
#घोषणा PSC_SND_BITS2GO	0x20E	/*
				 * [ 16-bit ]
				 * Counts करोwn to zero from some स्थिरant
				 * value. The value appears to be the
				 * number of _bits_ reमुख्यing beक्रमe the
				 * buffer is full, which would make sense
				 * since Apple's करोcs say the sound DMA
				 * channels are 1 bit wide.
				 */
#घोषणा PSC_SND_INADDR	0x210	/*
				 * [ 32-bit ]
				 * Address of the sound input DMA buffer
				 */
#घोषणा PSC_SND_OUTADDR	0x214	/*
				 * [ 32-bit ]
				 * Address of the sound output DMA buffer
				 */
#घोषणा PSC_SND_LEN	0x218	/*
				 * [ 16-bit ]
				 * Length of both buffers in eight-byte units.
				 */
#घोषणा PSC_SND_HUH4	0x21A	/*
				 * [ 16-bit ]
				 * Unknown, always 0x0000.
				 */
#घोषणा PSC_SND_STATUS2	0x21C	/*
				 * [ 16-bit ]
				 * Appears to e a पढ़ो-only status रेजिस्टर.
				 * The usual value is 0x0200.
				 */
#घोषणा PSC_SND_HUH5	0x21E	/*
				 * [ 16-bit ]
				 * Unknown, always 0x0000.
				 */

#अगर_अघोषित __ASSEMBLY__

बाह्य अस्थिर __u8 *psc;

बाह्य व्योम psc_रेजिस्टर_पूर्णांकerrupts(व्योम);
बाह्य व्योम psc_irq_enable(पूर्णांक);
बाह्य व्योम psc_irq_disable(पूर्णांक);

/*
 *	Access functions
 */

अटल अंतरभूत व्योम psc_ग_लिखो_byte(पूर्णांक offset, __u8 data)
अणु
	*((अस्थिर __u8 *)(psc + offset)) = data;
पूर्ण

अटल अंतरभूत व्योम psc_ग_लिखो_word(पूर्णांक offset, __u16 data)
अणु
	*((अस्थिर __u16 *)(psc + offset)) = data;
पूर्ण

अटल अंतरभूत व्योम psc_ग_लिखो_दीर्घ(पूर्णांक offset, __u32 data)
अणु
	*((अस्थिर __u32 *)(psc + offset)) = data;
पूर्ण

अटल अंतरभूत u8 psc_पढ़ो_byte(पूर्णांक offset)
अणु
	वापस *((अस्थिर __u8 *)(psc + offset));
पूर्ण

अटल अंतरभूत u16 psc_पढ़ो_word(पूर्णांक offset)
अणु
	वापस *((अस्थिर __u16 *)(psc + offset));
पूर्ण

अटल अंतरभूत u32 psc_पढ़ो_दीर्घ(पूर्णांक offset)
अणु
	वापस *((अस्थिर __u32 *)(psc + offset));
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */
