<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	OSS
 *
 *	This is used in place of VIA2 on the IIfx.
 */

#घोषणा OSS_BASE	(0x50f1a000)

/*
 * Interrupt level offsets क्रम mac_oss->irq_level
 */

#घोषणा OSS_NUBUS0	0
#घोषणा OSS_NUBUS1	1
#घोषणा OSS_NUBUS2	2
#घोषणा OSS_NUBUS3	3
#घोषणा OSS_NUBUS4	4
#घोषणा OSS_NUBUS5	5
#घोषणा OSS_IOPISM	6
#घोषणा OSS_IOPSCC	7
#घोषणा OSS_SOUND	8
#घोषणा OSS_SCSI	9
#घोषणा OSS_60HZ	10
#घोषणा OSS_VIA1	11
#घोषणा OSS_UNUSED1	12
#घोषणा OSS_UNUSED2	13
#घोषणा OSS_PARITY	14
#घोषणा OSS_UNUSED3	15

#घोषणा OSS_NUM_SOURCES	16

/*
 * Pending पूर्णांकerrupt bits in mac_oss->irq_pending
 */

#घोषणा OSS_IP_NUBUS0	0x0001
#घोषणा OSS_IP_NUBUS1	0x0002
#घोषणा OSS_IP_NUBUS2	0x0004
#घोषणा OSS_IP_NUBUS3	0x0008
#घोषणा OSS_IP_NUBUS4	0x0010
#घोषणा OSS_IP_NUBUS5	0x0020
#घोषणा OSS_IP_IOPISM	0x0040
#घोषणा OSS_IP_IOPSCC	0x0080
#घोषणा OSS_IP_SOUND	0x0100
#घोषणा OSS_IP_SCSI	0x0200
#घोषणा OSS_IP_60HZ	0x0400
#घोषणा OSS_IP_VIA1	0x0800
#घोषणा OSS_IP_UNUSED1	0x1000
#घोषणा OSS_IP_UNUSED2	0x2000
#घोषणा OSS_IP_PARITY	0x4000
#घोषणा OSS_IP_UNUSED3	0x8000

#घोषणा OSS_IP_NUBUS (OSS_IP_NUBUS0|OSS_IP_NUBUS1|OSS_IP_NUBUS2|OSS_IP_NUBUS3|OSS_IP_NUBUS4|OSS_IP_NUBUS5)

/*
 * Rom Control Register
 */

#घोषणा OSS_POWEROFF	0x80

#अगर_अघोषित __ASSEMBLY__

काष्ठा mac_oss अणु
    __u8  irq_level[0x10];	/* [0x000-0x00f] Interrupt levels */
    __u8  padding0[0x1F2];	/* [0x010-0x201] IO space filler */
    __u16 irq_pending;		/* [0x202-0x203] pending पूर्णांकerrupts bits */
    __u8  rom_ctrl;		/* [0x204-0x204] ROM cntl reg (क्रम घातeroff) */
    __u8  padding1[0x2];	/* [0x205-0x206] currently unused by A/UX */
    __u8  ack_60hz;		/* [0x207-0x207] 60 Hz ack. */
पूर्ण;

बाह्य अस्थिर काष्ठा mac_oss *oss;
बाह्य पूर्णांक oss_present;

बाह्य व्योम oss_रेजिस्टर_पूर्णांकerrupts(व्योम);
बाह्य व्योम oss_irq_enable(पूर्णांक);
बाह्य व्योम oss_irq_disable(पूर्णांक);

#पूर्ण_अगर /* __ASSEMBLY__ */
