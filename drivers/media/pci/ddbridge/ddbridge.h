<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ddbridge.h: Digital Devices PCIe bridge driver
 *
 * Copyright (C) 2010-2017 Digital Devices GmbH
 *                         Ralph Metzler <rmetzler@digitaldevices.de>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 only, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _DDBRIDGE_H_
#घोषणा _DDBRIDGE_H_

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dvb/ca.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/socket.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/swab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvb_ca_en50221.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dvb_ringbuffer.h>

#घोषणा DDBRIDGE_VERSION "0.9.33-integrated"

#घोषणा DDB_MAX_I2C    32
#घोषणा DDB_MAX_PORT   32
#घोषणा DDB_MAX_INPUT  64
#घोषणा DDB_MAX_OUTPUT 32
#घोषणा DDB_MAX_LINK    4
#घोषणा DDB_LINK_SHIFT 28

#घोषणा DDB_LINK_TAG(_x) (_x << DDB_LINK_SHIFT)

काष्ठा ddb_regset अणु
	u32 base;
	u32 num;
	u32 size;
पूर्ण;

काष्ठा ddb_regmap अणु
	u32 irq_base_i2c;
	u32 irq_base_idma;
	u32 irq_base_odma;

	स्थिर काष्ठा ddb_regset *i2c;
	स्थिर काष्ठा ddb_regset *i2c_buf;
	स्थिर काष्ठा ddb_regset *idma;
	स्थिर काष्ठा ddb_regset *idma_buf;
	स्थिर काष्ठा ddb_regset *odma;
	स्थिर काष्ठा ddb_regset *odma_buf;

	स्थिर काष्ठा ddb_regset *input;
	स्थिर काष्ठा ddb_regset *output;

	स्थिर काष्ठा ddb_regset *channel;
पूर्ण;

काष्ठा ddb_ids अणु
	u16 venकरोr;
	u16 device;
	u16 subvenकरोr;
	u16 subdevice;

	u32 hwid;
	u32 regmapid;
	u32 devid;
	u32 mac;
पूर्ण;

काष्ठा ddb_info अणु
	पूर्णांक   type;
#घोषणा DDB_NONE            0
#घोषणा DDB_OCTOPUS         1
#घोषणा DDB_OCTOPUS_CI      2
#घोषणा DDB_OCTOPUS_MAX     5
#घोषणा DDB_OCTOPUS_MAX_CT  6
#घोषणा DDB_OCTOPUS_MCI     9
	अक्षर *name;
	u32   i2c_mask;
	u32   board_control;
	u32   board_control_2;

	u8    port_num;
	u8    led_num;
	u8    fan_num;
	u8    temp_num;
	u8    temp_bus;
	u8    con_घड़ी; /* use a continuous घड़ी */
	u8    ts_quirks;
#घोषणा TS_QUIRK_SERIAL   1
#घोषणा TS_QUIRK_REVERSED 2
#घोषणा TS_QUIRK_ALT_OSC  8
	u8    mci_ports;
	u8    mci_type;

	u32   tempmon_irq;
	स्थिर काष्ठा ddb_regmap *regmap;
पूर्ण;

#घोषणा DMA_MAX_BUFS 32      /* hardware table limit */

काष्ठा ddb;
काष्ठा ddb_port;

काष्ठा ddb_dma अणु
	व्योम                  *io;
	u32                    regs;
	u32                    bufregs;

	dma_addr_t             pbuf[DMA_MAX_BUFS];
	u8                    *vbuf[DMA_MAX_BUFS];
	u32                    num;
	u32                    size;
	u32                    भाग;
	u32                    bufval;

	काष्ठा work_काष्ठा     work;
	spinlock_t             lock; /* DMA lock */
	रुको_queue_head_t      wq;
	पूर्णांक                    running;
	u32                    stat;
	u32                    ctrl;
	u32                    cbuf;
	u32                    coff;
पूर्ण;

काष्ठा ddb_dvb अणु
	काष्ठा dvb_adapter    *adap;
	पूर्णांक                    adap_रेजिस्टरed;
	काष्ठा dvb_device     *dev;
	काष्ठा i2c_client     *i2c_client[1];
	काष्ठा dvb_frontend   *fe;
	काष्ठा dvb_frontend   *fe2;
	काष्ठा dmxdev          dmxdev;
	काष्ठा dvb_demux       demux;
	काष्ठा dvb_net         dvbnet;
	काष्ठा dmx_frontend    hw_frontend;
	काष्ठा dmx_frontend    mem_frontend;
	पूर्णांक                    users;
	u32                    attached;
	u8                     input;

	क्रमागत fe_sec_tone_mode  tone;
	क्रमागत fe_sec_voltage    voltage;

	पूर्णांक (*i2c_gate_ctrl)(काष्ठा dvb_frontend *, पूर्णांक);
	पूर्णांक (*set_voltage)(काष्ठा dvb_frontend *fe,
			   क्रमागत fe_sec_voltage voltage);
	पूर्णांक (*set_input)(काष्ठा dvb_frontend *fe, पूर्णांक input);
	पूर्णांक (*diseqc_send_master_cmd)(काष्ठा dvb_frontend *fe,
				      काष्ठा dvb_diseqc_master_cmd *cmd);
पूर्ण;

काष्ठा ddb_ci अणु
	काष्ठा dvb_ca_en50221  en;
	काष्ठा ddb_port       *port;
	u32                    nr;
पूर्ण;

काष्ठा ddb_io अणु
	काष्ठा ddb_port       *port;
	u32                    nr;
	u32                    regs;
	काष्ठा ddb_dma        *dma;
	काष्ठा ddb_io         *reकरो;
	काष्ठा ddb_io         *redi;
पूर्ण;

#घोषणा ddb_output ddb_io
#घोषणा ddb_input ddb_io

काष्ठा ddb_i2c अणु
	काष्ठा ddb            *dev;
	u32                    nr;
	u32                    regs;
	u32                    link;
	काष्ठा i2c_adapter     adap;
	u32                    rbuf;
	u32                    wbuf;
	u32                    bsize;
	काष्ठा completion      completion;
पूर्ण;

काष्ठा ddb_port अणु
	काष्ठा ddb            *dev;
	u32                    nr;
	u32                    pnr;
	u32                    regs;
	u32                    lnr;
	काष्ठा ddb_i2c        *i2c;
	काष्ठा mutex           i2c_gate_lock; /* I2C access lock */
	u32                    class;
#घोषणा DDB_PORT_NONE           0
#घोषणा DDB_PORT_CI             1
#घोषणा DDB_PORT_TUNER          2
#घोषणा DDB_PORT_LOOP           3
	अक्षर                   *name;
	अक्षर                   *type_name;
	u32                     type;
#घोषणा DDB_TUNER_DUMMY          0xffffffff
#घोषणा DDB_TUNER_NONE           0
#घोषणा DDB_TUNER_DVBS_ST        1
#घोषणा DDB_TUNER_DVBS_ST_AA     2
#घोषणा DDB_TUNER_DVBCT_TR       3
#घोषणा DDB_TUNER_DVBCT_ST       4
#घोषणा DDB_CI_INTERNAL          5
#घोषणा DDB_CI_EXTERNAL_SONY     6
#घोषणा DDB_TUNER_DVBCT2_SONY_P  7
#घोषणा DDB_TUNER_DVBC2T2_SONY_P 8
#घोषणा DDB_TUNER_ISDBT_SONY_P   9
#घोषणा DDB_TUNER_DVBS_STV0910_P 10
#घोषणा DDB_TUNER_MXL5XX         11
#घोषणा DDB_CI_EXTERNAL_XO2      12
#घोषणा DDB_CI_EXTERNAL_XO2_B    13
#घोषणा DDB_TUNER_DVBS_STV0910_PR 14
#घोषणा DDB_TUNER_DVBC2T2I_SONY_P 15

#घोषणा DDB_TUNER_XO2            32
#घोषणा DDB_TUNER_DVBS_STV0910   (DDB_TUNER_XO2 + 0)
#घोषणा DDB_TUNER_DVBCT2_SONY    (DDB_TUNER_XO2 + 1)
#घोषणा DDB_TUNER_ISDBT_SONY     (DDB_TUNER_XO2 + 2)
#घोषणा DDB_TUNER_DVBC2T2_SONY   (DDB_TUNER_XO2 + 3)
#घोषणा DDB_TUNER_ATSC_ST        (DDB_TUNER_XO2 + 4)
#घोषणा DDB_TUNER_DVBC2T2I_SONY  (DDB_TUNER_XO2 + 5)

#घोषणा DDB_TUNER_MCI            48
#घोषणा DDB_TUNER_MCI_SX8        (DDB_TUNER_MCI + 0)

	काष्ठा ddb_input      *input[2];
	काष्ठा ddb_output     *output;
	काष्ठा dvb_ca_en50221 *en;
	u8                     en_मुक्तdata;
	काष्ठा ddb_dvb         dvb[2];
	u32                    gap;
	u32                    obr;
	u8                     creg;
पूर्ण;

#घोषणा CM_STARTUP_DELAY 2
#घोषणा CM_AVERAGE  20
#घोषणा CM_GAIN     10

#घोषणा HW_LSB_SHIFT    12
#घोषणा HW_LSB_MASK     0x1000

#घोषणा CM_IDLE    0
#घोषणा CM_STARTUP 1
#घोषणा CM_ADJUST  2

#घोषणा TS_CAPTURE_LEN  (4096)

काष्ठा ddb_lnb अणु
	काष्ठा mutex           lock; /* lock lnb access */
	u32                    tone;
	क्रमागत fe_sec_voltage    oldvoltage[4];
	u32                    voltage[4];
	u32                    voltages;
	u32                    भ_शेषe;
पूर्ण;

काष्ठा ddb_irq अणु
	व्योम                   (*handler)(व्योम *);
	व्योम                  *data;
पूर्ण;

काष्ठा ddb_link अणु
	काष्ठा ddb            *dev;
	स्थिर काष्ठा ddb_info *info;
	u32                    nr;
	u32                    regs;
	spinlock_t             lock; /* lock link access */
	काष्ठा mutex           flash_mutex; /* lock flash access */
	काष्ठा ddb_lnb         lnb;
	काष्ठा tasklet_काष्ठा  tasklet;
	काष्ठा ddb_ids         ids;

	spinlock_t             temp_lock; /* lock temp chip access */
	पूर्णांक                    overtemperature_error;
	u8                     temp_tab[11];
	काष्ठा ddb_irq         irq[256];
पूर्ण;

काष्ठा ddb अणु
	काष्ठा pci_dev          *pdev;
	काष्ठा platक्रमm_device  *pfdev;
	काष्ठा device           *dev;

	पूर्णांक                      msi;
	काष्ठा workqueue_काष्ठा *wq;
	u32                      has_dma;

	काष्ठा ddb_link          link[DDB_MAX_LINK];
	अचिन्हित अक्षर __iomem   *regs;
	u32                      regs_len;
	u32                      port_num;
	काष्ठा ddb_port          port[DDB_MAX_PORT];
	u32                      i2c_num;
	काष्ठा ddb_i2c           i2c[DDB_MAX_I2C];
	काष्ठा ddb_input         input[DDB_MAX_INPUT];
	काष्ठा ddb_output        output[DDB_MAX_OUTPUT];
	काष्ठा dvb_adapter       adap[DDB_MAX_INPUT];
	काष्ठा ddb_dma           idma[DDB_MAX_INPUT];
	काष्ठा ddb_dma           odma[DDB_MAX_OUTPUT];

	काष्ठा device           *ddb_dev;
	u32                      ddb_dev_users;
	u32                      nr;
	u8                       iobuf[1028];

	u8                       leds;
	u32                      ts_irq;
	u32                      i2c_irq;

	काष्ठा mutex             mutex; /* lock access to global ddb array */

	u8                       tsbuf[TS_CAPTURE_LEN];
पूर्ण;

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

पूर्णांक ddbridge_flashपढ़ो(काष्ठा ddb *dev, u32 link, u8 *buf, u32 addr, u32 len);

/****************************************************************************/

/* ddbridge-core.c */
काष्ठा ddb_irq *ddb_irq_set(काष्ठा ddb *dev, u32 link, u32 nr,
			    व्योम (*handler)(व्योम *), व्योम *data);
व्योम ddb_ports_detach(काष्ठा ddb *dev);
व्योम ddb_ports_release(काष्ठा ddb *dev);
व्योम ddb_buffers_मुक्त(काष्ठा ddb *dev);
व्योम ddb_device_destroy(काष्ठा ddb *dev);
irqवापस_t ddb_irq_handler0(पूर्णांक irq, व्योम *dev_id);
irqवापस_t ddb_irq_handler1(पूर्णांक irq, व्योम *dev_id);
irqवापस_t ddb_irq_handler(पूर्णांक irq, व्योम *dev_id);
व्योम ddb_ports_init(काष्ठा ddb *dev);
पूर्णांक ddb_buffers_alloc(काष्ठा ddb *dev);
पूर्णांक ddb_ports_attach(काष्ठा ddb *dev);
पूर्णांक ddb_device_create(काष्ठा ddb *dev);
पूर्णांक ddb_init(काष्ठा ddb *dev);
व्योम ddb_unmap(काष्ठा ddb *dev);
पूर्णांक ddb_निकास_ddbridge(पूर्णांक stage, पूर्णांक error);
पूर्णांक ddb_init_ddbridge(व्योम);

#पूर्ण_अगर /* DDBRIDGE_H */
