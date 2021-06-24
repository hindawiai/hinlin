<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    bt878.h - Bt878 audio module (रेजिस्टर offsets)

    Copyright (C) 2002 Peter Hettkamp <peter.hettkamp@htp-tel.de>

*/

#अगर_अघोषित _BT878_H_
#घोषणा _BT878_H_

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>

#समावेश "bt848.h"
#समावेश "bttv.h"

#घोषणा BT878_VERSION_CODE 0x000000

#घोषणा BT878_AINT_STAT		0x100
#घोषणा BT878_ARISCS		(0xf<<28)
#घोषणा BT878_ARISC_EN		(1<<27)
#घोषणा BT878_ASCERR		(1<<19)
#घोषणा BT878_AOCERR		(1<<18)
#घोषणा BT878_APABORT		(1<<17)
#घोषणा BT878_ARIPERR		(1<<16)
#घोषणा BT878_APPERR		(1<<15)
#घोषणा BT878_AFDSR		(1<<14)
#घोषणा BT878_AFTRGT		(1<<13)
#घोषणा BT878_AFBUS		(1<<12)
#घोषणा BT878_ARISCI		(1<<11)
#घोषणा BT878_AOFLOW		(1<<3)

#घोषणा BT878_AINT_MASK		0x104

#घोषणा BT878_AGPIO_DMA_CTL	0x10c
#घोषणा BT878_A_GAIN		(0xf<<28)
#घोषणा BT878_A_G2X		(1<<27)
#घोषणा BT878_A_PWRDN		(1<<26)
#घोषणा BT878_A_SEL		(3<<24)
#घोषणा BT878_DA_SCE		(1<<23)
#घोषणा BT878_DA_LRI		(1<<22)
#घोषणा BT878_DA_MLB		(1<<21)
#घोषणा BT878_DA_LRD		(0x1f<<16)
#घोषणा BT878_DA_DPM		(1<<15)
#घोषणा BT878_DA_SBR		(1<<14)
#घोषणा BT878_DA_ES2		(1<<13)
#घोषणा BT878_DA_LMT		(1<<12)
#घोषणा BT878_DA_SDR		(0xf<<8)
#घोषणा BT878_DA_IOM		(3<<6)
#घोषणा BT878_DA_APP		(1<<5)
#घोषणा BT878_ACAP_EN		(1<<4)
#घोषणा BT878_PKTP		(3<<2)
#घोषणा BT878_RISC_EN		(1<<1)
#घोषणा BT878_FIFO_EN		1

#घोषणा BT878_APACK_LEN		0x110
#घोषणा BT878_AFP_LEN		(0xff<<16)
#घोषणा BT878_ALP_LEN		0xfff

#घोषणा BT878_ARISC_START	0x114

#घोषणा BT878_ARISC_PC		0x120

/* BT878 FUNCTION 0 REGISTERS */
#घोषणा BT878_GPIO_DMA_CTL	0x10c

/* Interrupt रेजिस्टर */
#घोषणा BT878_INT_STAT		0x100
#घोषणा BT878_INT_MASK		0x104
#घोषणा BT878_I2CRACK		(1<<25)
#घोषणा BT878_I2CDONE		(1<<8)

#घोषणा BT878_MAX 4

#घोषणा BT878_RISC_SYNC_MASK	(1 << 15)


#घोषणा BTTV_BOARD_UNKNOWN                 0x00
#घोषणा BTTV_BOARD_PINNACLESAT             0x5e
#घोषणा BTTV_BOARD_NEBULA_DIGITV           0x68
#घोषणा BTTV_BOARD_PC_HDTV                 0x70
#घोषणा BTTV_BOARD_TWINHAN_DST             0x71
#घोषणा BTTV_BOARD_AVDVBT_771              0x7b
#घोषणा BTTV_BOARD_AVDVBT_761              0x7c
#घोषणा BTTV_BOARD_DVICO_DVBT_LITE         0x80
#घोषणा BTTV_BOARD_DVICO_FUSIONHDTV_5_LITE 0x87

बाह्य पूर्णांक bt878_num;

काष्ठा bt878 अणु
	काष्ठा mutex gpio_lock;
	अचिन्हित पूर्णांक nr;
	अचिन्हित पूर्णांक bttv_nr;
	काष्ठा i2c_adapter *adapter;
	काष्ठा pci_dev *dev;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक TS_Size;
	अचिन्हित अक्षर revision;
	अचिन्हित पूर्णांक irq;
	अचिन्हित दीर्घ bt878_adr;
	अस्थिर व्योम __iomem *bt878_mem; /* function 1 */

	अस्थिर u32 finished_block;
	अस्थिर u32 last_block;
	u32 block_count;
	u32 block_bytes;
	u32 line_bytes;
	u32 line_count;

	u32 buf_size;
	u8 *buf_cpu;
	dma_addr_t buf_dma;

	u32 risc_size;
	__le32 *risc_cpu;
	dma_addr_t risc_dma;
	u32 risc_pos;

	काष्ठा tasklet_काष्ठा tasklet;
	पूर्णांक shutकरोwn;
पूर्ण;

बाह्य काष्ठा bt878 bt878[BT878_MAX];

व्योम bt878_start(काष्ठा bt878 *bt, u32 controlreg, u32 op_sync_orin,
		u32 irq_err_ignore);
व्योम bt878_stop(काष्ठा bt878 *bt);

#घोषणा bmtग_लिखो(dat,adr)  ग_लिखोl((dat), (adr))
#घोषणा bmtपढ़ो(adr)       पढ़ोl(adr)

#पूर्ण_अगर
