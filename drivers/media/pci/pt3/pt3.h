<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Earthsoft PT3 driver
 *
 * Copyright (C) 2014 Akihiro Tsukada <tskd08@gmail.com>
 */

#अगर_अघोषित PT3_H
#घोषणा PT3_H

#समावेश <linux/atomic.h>
#समावेश <linux/types.h>

#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dmxdev.h>

#समावेश "tc90522.h"
#समावेश "mxl301rf.h"
#समावेश "qm1d1c0042.h"

#घोषणा DRV_NAME KBUILD_MODNAME

#घोषणा PT3_NUM_FE 4

/*
 * रेजिस्टर index of the FPGA chip
 */
#घोषणा REG_VERSION	0x00
#घोषणा REG_BUS		0x04
#घोषणा REG_SYSTEM_W	0x08
#घोषणा REG_SYSTEM_R	0x0c
#घोषणा REG_I2C_W	0x10
#घोषणा REG_I2C_R	0x14
#घोषणा REG_RAM_W	0x18
#घोषणा REG_RAM_R	0x1c
#घोषणा REG_DMA_BASE	0x40	/* regs क्रम FE[i] = REG_DMA_BASE + 0x18 * i */
#घोषणा OFST_DMA_DESC_L	0x00
#घोषणा OFST_DMA_DESC_H	0x04
#घोषणा OFST_DMA_CTL	0x08
#घोषणा OFST_TS_CTL	0x0c
#घोषणा OFST_STATUS	0x10
#घोषणा OFST_TS_ERR	0x14

/*
 * पूर्णांकernal buffer क्रम I2C
 */
#घोषणा PT3_I2C_MAX 4091
काष्ठा pt3_i2cbuf अणु
	u8  data[PT3_I2C_MAX];
	u8  पंचांगp;
	u32 num_cmds;
पूर्ण;

/*
 * DMA things
 */
#घोषणा TS_PACKET_SZ  188
/* DMA transfers must not cross 4GiB, so use one page / transfer */
#घोषणा DATA_XFER_SZ   4096
#घोषणा DATA_BUF_XFERS 47
/* (num_bufs * DATA_BUF_SZ) % TS_PACKET_SZ must be 0 */
#घोषणा DATA_BUF_SZ    (DATA_BUF_XFERS * DATA_XFER_SZ)
#घोषणा MAX_DATA_BUFS  16
#घोषणा MIN_DATA_BUFS   2

#घोषणा DESCS_IN_PAGE (PAGE_SIZE / माप(काष्ठा xfer_desc))
#घोषणा MAX_NUM_XFERS (MAX_DATA_BUFS * DATA_BUF_XFERS)
#घोषणा MAX_DESC_BUFS DIV_ROUND_UP(MAX_NUM_XFERS, DESCS_IN_PAGE)

/* DMA transfer description.
 * device is passed a poपूर्णांकer to this काष्ठा, dma-पढ़ोs it,
 * and माला_लो the DMA buffer ring क्रम storing TS data.
 */
काष्ठा xfer_desc अणु
	u32 addr_l; /* bus address of target data buffer */
	u32 addr_h;
	u32 size;
	u32 next_l; /* bus address of the next xfer_desc */
	u32 next_h;
पूर्ण;

/* A DMA mapping of a page containing xfer_desc's */
काष्ठा xfer_desc_buffer अणु
	dma_addr_t b_addr;
	काष्ठा xfer_desc *descs; /* PAGE_SIZE (xfer_desc[DESCS_IN_PAGE]) */
पूर्ण;

/* A DMA mapping of a data buffer */
काष्ठा dma_data_buffer अणु
	dma_addr_t b_addr;
	u8 *data; /* size: u8[PAGE_SIZE] */
पूर्ण;

/*
 * device things
 */
काष्ठा pt3_adap_config अणु
	काष्ठा i2c_board_info demod_info;
	काष्ठा tc90522_config demod_cfg;

	काष्ठा i2c_board_info tuner_info;
	जोड़ tuner_config अणु
		काष्ठा qm1d1c0042_config qm1d1c0042;
		काष्ठा mxl301rf_config   mxl301rf;
	पूर्ण tuner_cfg;
	u32 init_freq;
पूर्ण;

काष्ठा pt3_adapter अणु
	काष्ठा dvb_adapter  dvb_adap;  /* dvb_adap.priv => काष्ठा pt3_board */
	पूर्णांक adap_idx;

	काष्ठा dvb_demux    demux;
	काष्ठा dmxdev       dmxdev;
	काष्ठा dvb_frontend *fe;
	काष्ठा i2c_client   *i2c_demod;
	काष्ठा i2c_client   *i2c_tuner;

	/* data fetch thपढ़ो */
	काष्ठा task_काष्ठा *thपढ़ो;
	पूर्णांक num_feeds;

	bool cur_lna;
	bool cur_lnb; /* current LNB घातer status (on/off) */

	/* items below are क्रम DMA */
	काष्ठा dma_data_buffer buffer[MAX_DATA_BUFS];
	पूर्णांक buf_idx;
	पूर्णांक buf_ofs;
	पूर्णांक num_bufs;  /* == pt3_board->num_bufs */
	पूर्णांक num_discard; /* how many access units to discard initially */

	काष्ठा xfer_desc_buffer desc_buf[MAX_DESC_BUFS];
	पूर्णांक num_desc_bufs;  /* == num_bufs * DATA_BUF_XFERS / DESCS_IN_PAGE */
पूर्ण;


काष्ठा pt3_board अणु
	काष्ठा pci_dev *pdev;
	व्योम __iomem *regs[2];
	/* regs[0]: रेजिस्टरs, regs[1]: पूर्णांकernal memory, used क्रम I2C */

	काष्ठा mutex lock;

	/* LNB घातer shared among sat-FEs */
	पूर्णांक lnb_on_cnt; /* LNB घातer on count */

	/* LNA shared among terr-FEs */
	पूर्णांक lna_on_cnt; /* booster enabled count */

	पूर्णांक num_bufs;  /* number of DMA buffers allocated/mapped per FE */

	काष्ठा i2c_adapter i2c_adap;
	काष्ठा pt3_i2cbuf *i2c_buf;

	काष्ठा pt3_adapter *adaps[PT3_NUM_FE];
पूर्ण;


/*
 * prototypes
 */
बाह्य पूर्णांक  pt3_alloc_dmabuf(काष्ठा pt3_adapter *adap);
बाह्य व्योम pt3_init_dmabuf(काष्ठा pt3_adapter *adap);
बाह्य व्योम pt3_मुक्त_dmabuf(काष्ठा pt3_adapter *adap);
बाह्य पूर्णांक  pt3_start_dma(काष्ठा pt3_adapter *adap);
बाह्य पूर्णांक  pt3_stop_dma(काष्ठा pt3_adapter *adap);
बाह्य पूर्णांक  pt3_proc_dma(काष्ठा pt3_adapter *adap);

बाह्य पूर्णांक  pt3_i2c_master_xfer(काष्ठा i2c_adapter *adap,
				काष्ठा i2c_msg *msgs, पूर्णांक num);
बाह्य u32  pt3_i2c_functionality(काष्ठा i2c_adapter *adap);
बाह्य व्योम pt3_i2c_reset(काष्ठा pt3_board *pt3);
बाह्य पूर्णांक  pt3_init_all_demods(काष्ठा pt3_board *pt3);
बाह्य पूर्णांक  pt3_init_all_mxl301rf(काष्ठा pt3_board *pt3);
#पूर्ण_अगर /* PT3_H */
