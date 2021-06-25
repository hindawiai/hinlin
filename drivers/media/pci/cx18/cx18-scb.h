<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  cx18 System Control Block initialization
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#अगर_अघोषित CX18_SCB_H
#घोषणा CX18_SCB_H

#समावेश "cx18-mailbox.h"

/* NOTE: All ACK पूर्णांकerrupts are in the SW2 रेजिस्टर.  All non-ACK पूर्णांकerrupts
   are in the SW1 रेजिस्टर. */

#घोषणा IRQ_APU_TO_CPU         0x00000001
#घोषणा IRQ_CPU_TO_APU_ACK     0x00000001
#घोषणा IRQ_HPU_TO_CPU         0x00000002
#घोषणा IRQ_CPU_TO_HPU_ACK     0x00000002
#घोषणा IRQ_PPU_TO_CPU         0x00000004
#घोषणा IRQ_CPU_TO_PPU_ACK     0x00000004
#घोषणा IRQ_EPU_TO_CPU         0x00000008
#घोषणा IRQ_CPU_TO_EPU_ACK     0x00000008

#घोषणा IRQ_CPU_TO_APU         0x00000010
#घोषणा IRQ_APU_TO_CPU_ACK     0x00000010
#घोषणा IRQ_HPU_TO_APU         0x00000020
#घोषणा IRQ_APU_TO_HPU_ACK     0x00000020
#घोषणा IRQ_PPU_TO_APU         0x00000040
#घोषणा IRQ_APU_TO_PPU_ACK     0x00000040
#घोषणा IRQ_EPU_TO_APU         0x00000080
#घोषणा IRQ_APU_TO_EPU_ACK     0x00000080

#घोषणा IRQ_CPU_TO_HPU         0x00000100
#घोषणा IRQ_HPU_TO_CPU_ACK     0x00000100
#घोषणा IRQ_APU_TO_HPU         0x00000200
#घोषणा IRQ_HPU_TO_APU_ACK     0x00000200
#घोषणा IRQ_PPU_TO_HPU         0x00000400
#घोषणा IRQ_HPU_TO_PPU_ACK     0x00000400
#घोषणा IRQ_EPU_TO_HPU         0x00000800
#घोषणा IRQ_HPU_TO_EPU_ACK     0x00000800

#घोषणा IRQ_CPU_TO_PPU         0x00001000
#घोषणा IRQ_PPU_TO_CPU_ACK     0x00001000
#घोषणा IRQ_APU_TO_PPU         0x00002000
#घोषणा IRQ_PPU_TO_APU_ACK     0x00002000
#घोषणा IRQ_HPU_TO_PPU         0x00004000
#घोषणा IRQ_PPU_TO_HPU_ACK     0x00004000
#घोषणा IRQ_EPU_TO_PPU         0x00008000
#घोषणा IRQ_PPU_TO_EPU_ACK     0x00008000

#घोषणा IRQ_CPU_TO_EPU         0x00010000
#घोषणा IRQ_EPU_TO_CPU_ACK     0x00010000
#घोषणा IRQ_APU_TO_EPU         0x00020000
#घोषणा IRQ_EPU_TO_APU_ACK     0x00020000
#घोषणा IRQ_HPU_TO_EPU         0x00040000
#घोषणा IRQ_EPU_TO_HPU_ACK     0x00040000
#घोषणा IRQ_PPU_TO_EPU         0x00080000
#घोषणा IRQ_EPU_TO_PPU_ACK     0x00080000

#घोषणा SCB_OFFSET  0xDC0000

/* If Firmware uses fixed memory map, it shall not allocate the area
   between SCB_OFFSET and SCB_OFFSET+SCB_RESERVED_SIZE-1 inclusive */
#घोषणा SCB_RESERVED_SIZE 0x10000


/* This काष्ठाure is used by EPU to provide memory descriptors in its memory */
काष्ठा cx18_mdl_ent अणु
    u32 paddr;  /* Physical address of a buffer segment */
    u32 length; /* Length of the buffer segment */
पूर्ण;

काष्ठा cx18_scb अणु
	/* These fields क्रमm the System Control Block which is used at boot समय
	   क्रम localizing the IPC data as well as the code positions क्रम all
	   processors. The offsets are from the start of this काष्ठा. */

	/* Offset where to find the Inter-Processor Communication data */
	u32 ipc_offset;
	u32 reserved01[7];
	/* Offset where to find the start of the CPU code */
	u32 cpu_code_offset;
	u32 reserved02[3];
	/* Offset where to find the start of the APU code */
	u32 apu_code_offset;
	u32 reserved03[3];
	/* Offset where to find the start of the HPU code */
	u32 hpu_code_offset;
	u32 reserved04[3];
	/* Offset where to find the start of the PPU code */
	u32 ppu_code_offset;
	u32 reserved05[3];

	/* These fields क्रमm Inter-Processor Communication data which is used
	   by all processors to locate the inक्रमmation needed क्रम communicating
	   with other processors */

	/* Fields क्रम CPU: */

	/* bit 0: 1/0 processor पढ़ोy/not पढ़ोy. Set other bits to 0. */
	u32 cpu_state;
	u32 reserved1[7];
	/* Offset to the mailbox used क्रम sending commands from APU to CPU */
	u32 apu2cpu_mb_offset;
	/* Value to ग_लिखो to रेजिस्टर SW1 रेजिस्टर set (0xC7003100) after the
	   command is पढ़ोy */
	u32 apu2cpu_irq;
	/* Value to ग_लिखो to रेजिस्टर SW2 रेजिस्टर set (0xC7003140) after the
	   command is cleared */
	u32 cpu2apu_irq_ack;
	u32 reserved2[13];

	u32 hpu2cpu_mb_offset;
	u32 hpu2cpu_irq;
	u32 cpu2hpu_irq_ack;
	u32 reserved3[13];

	u32 ppu2cpu_mb_offset;
	u32 ppu2cpu_irq;
	u32 cpu2ppu_irq_ack;
	u32 reserved4[13];

	u32 epu2cpu_mb_offset;
	u32 epu2cpu_irq;
	u32 cpu2epu_irq_ack;
	u32 reserved5[13];
	u32 reserved6[8];

	/* Fields क्रम APU: */

	u32 apu_state;
	u32 reserved11[7];
	u32 cpu2apu_mb_offset;
	u32 cpu2apu_irq;
	u32 apu2cpu_irq_ack;
	u32 reserved12[13];

	u32 hpu2apu_mb_offset;
	u32 hpu2apu_irq;
	u32 apu2hpu_irq_ack;
	u32 reserved13[13];

	u32 ppu2apu_mb_offset;
	u32 ppu2apu_irq;
	u32 apu2ppu_irq_ack;
	u32 reserved14[13];

	u32 epu2apu_mb_offset;
	u32 epu2apu_irq;
	u32 apu2epu_irq_ack;
	u32 reserved15[13];
	u32 reserved16[8];

	/* Fields क्रम HPU: */

	u32 hpu_state;
	u32 reserved21[7];
	u32 cpu2hpu_mb_offset;
	u32 cpu2hpu_irq;
	u32 hpu2cpu_irq_ack;
	u32 reserved22[13];

	u32 apu2hpu_mb_offset;
	u32 apu2hpu_irq;
	u32 hpu2apu_irq_ack;
	u32 reserved23[13];

	u32 ppu2hpu_mb_offset;
	u32 ppu2hpu_irq;
	u32 hpu2ppu_irq_ack;
	u32 reserved24[13];

	u32 epu2hpu_mb_offset;
	u32 epu2hpu_irq;
	u32 hpu2epu_irq_ack;
	u32 reserved25[13];
	u32 reserved26[8];

	/* Fields क्रम PPU: */

	u32 ppu_state;
	u32 reserved31[7];
	u32 cpu2ppu_mb_offset;
	u32 cpu2ppu_irq;
	u32 ppu2cpu_irq_ack;
	u32 reserved32[13];

	u32 apu2ppu_mb_offset;
	u32 apu2ppu_irq;
	u32 ppu2apu_irq_ack;
	u32 reserved33[13];

	u32 hpu2ppu_mb_offset;
	u32 hpu2ppu_irq;
	u32 ppu2hpu_irq_ack;
	u32 reserved34[13];

	u32 epu2ppu_mb_offset;
	u32 epu2ppu_irq;
	u32 ppu2epu_irq_ack;
	u32 reserved35[13];
	u32 reserved36[8];

	/* Fields क्रम EPU: */

	u32 epu_state;
	u32 reserved41[7];
	u32 cpu2epu_mb_offset;
	u32 cpu2epu_irq;
	u32 epu2cpu_irq_ack;
	u32 reserved42[13];

	u32 apu2epu_mb_offset;
	u32 apu2epu_irq;
	u32 epu2apu_irq_ack;
	u32 reserved43[13];

	u32 hpu2epu_mb_offset;
	u32 hpu2epu_irq;
	u32 epu2hpu_irq_ack;
	u32 reserved44[13];

	u32 ppu2epu_mb_offset;
	u32 ppu2epu_irq;
	u32 epu2ppu_irq_ack;
	u32 reserved45[13];
	u32 reserved46[8];

	u32 semaphores[8];  /* Semaphores */

	u32 reserved50[32]; /* Reserved क्रम future use */

	काष्ठा cx18_mailbox  apu2cpu_mb;
	काष्ठा cx18_mailbox  hpu2cpu_mb;
	काष्ठा cx18_mailbox  ppu2cpu_mb;
	काष्ठा cx18_mailbox  epu2cpu_mb;

	काष्ठा cx18_mailbox  cpu2apu_mb;
	काष्ठा cx18_mailbox  hpu2apu_mb;
	काष्ठा cx18_mailbox  ppu2apu_mb;
	काष्ठा cx18_mailbox  epu2apu_mb;

	काष्ठा cx18_mailbox  cpu2hpu_mb;
	काष्ठा cx18_mailbox  apu2hpu_mb;
	काष्ठा cx18_mailbox  ppu2hpu_mb;
	काष्ठा cx18_mailbox  epu2hpu_mb;

	काष्ठा cx18_mailbox  cpu2ppu_mb;
	काष्ठा cx18_mailbox  apu2ppu_mb;
	काष्ठा cx18_mailbox  hpu2ppu_mb;
	काष्ठा cx18_mailbox  epu2ppu_mb;

	काष्ठा cx18_mailbox  cpu2epu_mb;
	काष्ठा cx18_mailbox  apu2epu_mb;
	काष्ठा cx18_mailbox  hpu2epu_mb;
	काष्ठा cx18_mailbox  ppu2epu_mb;

	काष्ठा cx18_mdl_ack  cpu_mdl_ack[CX18_MAX_STREAMS][CX18_MAX_MDL_ACKS];
	काष्ठा cx18_mdl_ent  cpu_mdl[1];
पूर्ण;

व्योम cx18_init_scb(काष्ठा cx18 *cx);

#पूर्ण_अगर
