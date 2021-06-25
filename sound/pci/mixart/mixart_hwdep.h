<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Digigram miXart soundcards
 *
 * definitions and makros क्रम basic card access
 *
 * Copyright (c) 2003 by Digigram <alsa@digigram.com>
 */

#अगर_अघोषित __SOUND_MIXART_HWDEP_H
#घोषणा __SOUND_MIXART_HWDEP_H

#समावेश <sound/hwdep.h>

#अगर_अघोषित पढ़ोl_be
#घोषणा पढ़ोl_be(x) be32_to_cpu((__क्रमce __be32)__raw_पढ़ोl(x))
#पूर्ण_अगर

#अगर_अघोषित ग_लिखोl_be
#घोषणा ग_लिखोl_be(data,addr) __raw_ग_लिखोl((__क्रमce u32)cpu_to_be32(data),addr)
#पूर्ण_अगर

#अगर_अघोषित पढ़ोl_le
#घोषणा पढ़ोl_le(x) le32_to_cpu((__क्रमce __le32)__raw_पढ़ोl(x))
#पूर्ण_अगर

#अगर_अघोषित ग_लिखोl_le
#घोषणा ग_लिखोl_le(data,addr) __raw_ग_लिखोl((__क्रमce u32)cpu_to_le32(data),addr)
#पूर्ण_अगर

#घोषणा MIXART_MEM(mgr,x)	((mgr)->mem[0].virt + (x))
#घोषणा MIXART_REG(mgr,x)	((mgr)->mem[1].virt + (x))


/* Daughter board Type */
#घोषणा DAUGHTER_TYPE_MASK     0x0F 
#घोषणा DAUGHTER_VER_MASK      0xF0 
#घोषणा DAUGHTER_TYPEVER_MASK  (DAUGHTER_TYPE_MASK|DAUGHTER_VER_MASK)
 
#घोषणा MIXART_DAUGHTER_TYPE_NONE     0x00 
#घोषणा MIXART_DAUGHTER_TYPE_COBRANET 0x08 
#घोषणा MIXART_DAUGHTER_TYPE_AES      0x0E



#घोषणा MIXART_BA0_SIZE 	(16 * 1024 * 1024) /* 16M */
#घोषणा MIXART_BA1_SIZE 	(4  * 1024)        /* 4k */

/*
 * -----------BAR 0 --------------------------------------------------------------------------------------------------------
 */
#घोषणा  MIXART_PSEUDOREG                          0x2000                    /* base address क्रम pseuकरोरेजिस्टर */

#घोषणा  MIXART_PSEUDOREG_BOARDNUMBER              MIXART_PSEUDOREG+0        /* board number */

/* perfmeter (available when elf loaded)*/
#घोषणा  MIXART_PSEUDOREG_PERF_STREAM_LOAD_OFFSET  MIXART_PSEUDOREG+0x70     /* streaming load */
#घोषणा  MIXART_PSEUDOREG_PERF_SYSTEM_LOAD_OFFSET  MIXART_PSEUDOREG+0x78     /* प्रणाली load (reference)*/
#घोषणा  MIXART_PSEUDOREG_PERF_MAILBX_LOAD_OFFSET  MIXART_PSEUDOREG+0x7C     /* mailbox load */
#घोषणा  MIXART_PSEUDOREG_PERF_INTERR_LOAD_OFFSET  MIXART_PSEUDOREG+0x74     /* पूर्णांकerrupt handling  load */

/* motherboard xilinx loader info */
#घोषणा  MIXART_PSEUDOREG_MXLX_BASE_ADDR_OFFSET    MIXART_PSEUDOREG+0x9C     /* 0x00600000 */ 
#घोषणा  MIXART_PSEUDOREG_MXLX_SIZE_OFFSET         MIXART_PSEUDOREG+0xA0     /* xilinx size in bytes */ 
#घोषणा  MIXART_PSEUDOREG_MXLX_STATUS_OFFSET       MIXART_PSEUDOREG+0xA4     /* status = EMBEBBED_STAT_XXX */ 

/* elf loader info */
#घोषणा  MIXART_PSEUDOREG_ELF_STATUS_OFFSET        MIXART_PSEUDOREG+0xB0     /* status = EMBEBBED_STAT_XXX */ 

/* 
*  after the elf code is loaded, and the flowtable info was passed to it,
*  the driver polls on this address, until it shows 1 (presence) or 2 (असलence)
*  once it is non-zero, the daughter board type may be पढ़ो
*/
#घोषणा  MIXART_PSEUDOREG_DBRD_PRESENCE_OFFSET     MIXART_PSEUDOREG+0x990   

/* Global info काष्ठाure */
#घोषणा  MIXART_PSEUDOREG_DBRD_TYPE_OFFSET         MIXART_PSEUDOREG+0x994    /* Type and version of daughterboard  */


/* daughterboard xilinx loader info */
#घोषणा  MIXART_PSEUDOREG_DXLX_BASE_ADDR_OFFSET    MIXART_PSEUDOREG+0x998    /* get the address here where to ग_लिखो the file */ 
#घोषणा  MIXART_PSEUDOREG_DXLX_SIZE_OFFSET         MIXART_PSEUDOREG+0x99C    /* xilinx size in bytes */ 
#घोषणा  MIXART_PSEUDOREG_DXLX_STATUS_OFFSET       MIXART_PSEUDOREG+0x9A0    /* status = EMBEBBED_STAT_XXX */ 

/*  */
#घोषणा  MIXART_FLOWTABLE_PTR                      0x3000                    /* poपूर्णांकer to flow table */

/* mailbox addresses  */

/* message DRV -> EMB */
#घोषणा MSG_INBOUND_POST_HEAD       0x010008	/* DRV posts MF + increment4 */
#घोषणा	MSG_INBOUND_POST_TAIL       0x01000C	/* EMB माला_लो MF + increment4 */
/* message EMB -> DRV */
#घोषणा	MSG_OUTBOUND_POST_TAIL      0x01001C	/* DRV माला_लो MF + increment4 */
#घोषणा	MSG_OUTBOUND_POST_HEAD      0x010018	/* EMB posts MF + increment4 */
/* Get Free Frames */
#घोषणा MSG_INBOUND_FREE_TAIL       0x010004	/* DRV माला_लो MFA + increment4 */
#घोषणा MSG_OUTBOUND_FREE_TAIL      0x010014	/* EMB माला_लो MFA + increment4 */
/* Put Free Frames */
#घोषणा MSG_OUTBOUND_FREE_HEAD      0x010010	/* DRV माला_दो MFA + increment4 */
#घोषणा MSG_INBOUND_FREE_HEAD       0x010000    /* EMB माला_दो MFA + increment4 */

/* firmware addresses of the message fअगरos */
#घोषणा MSG_BOUND_STACK_SIZE        0x004000    /* size of each following stack */
/* posted messages */
#घोषणा MSG_OUTBOUND_POST_STACK     0x108000    /* stack of messages to the DRV */
#घोषणा MSG_INBOUND_POST_STACK      0x104000    /* stack of messages to the EMB */
/* available empty messages */
#घोषणा MSG_OUTBOUND_FREE_STACK     0x10C000    /* stack of मुक्त enveloped क्रम EMB */
#घोषणा MSG_INBOUND_FREE_STACK      0x100000    /* stack of मुक्त enveloped क्रम DRV */


/* defines क्रम mailbox message frames */
#घोषणा MSG_FRAME_OFFSET            0x64
#घोषणा MSG_FRAME_SIZE              0x6400
#घोषणा MSG_FRAME_NUMBER            32
#घोषणा MSG_FROM_AGENT_ITMF_OFFSET  (MSG_FRAME_OFFSET + (MSG_FRAME_SIZE * MSG_FRAME_NUMBER))
#घोषणा MSG_TO_AGENT_ITMF_OFFSET    (MSG_FROM_AGENT_ITMF_OFFSET + MSG_FRAME_SIZE)
#घोषणा MSG_HOST_RSC_PROTECTION     (MSG_TO_AGENT_ITMF_OFFSET + MSG_FRAME_SIZE)
#घोषणा MSG_AGENT_RSC_PROTECTION    (MSG_HOST_RSC_PROTECTION + 4)


/*
 * -----------BAR 1 --------------------------------------------------------------------------------------------------------
 */

/* पूर्णांकerrupt addresses and स्थिरants */
#घोषणा MIXART_PCI_OMIMR_OFFSET                 0x34    /* outbound message पूर्णांकerrupt mask रेजिस्टर */
#घोषणा MIXART_PCI_OMISR_OFFSET                 0x30    /* outbound message पूर्णांकerrupt status रेजिस्टर */
#घोषणा MIXART_PCI_ODBR_OFFSET                  0x60    /* outbound करोorbell रेजिस्टर */

#घोषणा MIXART_BA1_BRUTAL_RESET_OFFSET          0x68    /* ग_लिखो 1 in LSBit to reset board */

#घोषणा MIXART_HOST_ALL_INTERRUPT_MASKED        0x02B   /* 0000 0010 1011 */
#घोषणा MIXART_ALLOW_OUTBOUND_DOORBELL          0x023   /* 0000 0010 0011 */
#घोषणा MIXART_OIDI                             0x008   /* 0000 0000 1000 */


पूर्णांक snd_mixart_setup_firmware(काष्ठा mixart_mgr *mgr);

#पूर्ण_अगर /* __SOUND_MIXART_HWDEP_H */
