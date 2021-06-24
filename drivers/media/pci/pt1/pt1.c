<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * driver क्रम Earthsoft PT1/PT2
 *
 * Copyright (C) 2009 HIRANO Takahito <hiranotaka@zng.info>
 *
 * based on pt1dvr - http://pt1dvr.sourceक्रमge.jp/
 *	by Tomoaki Ishikawa <tomy@users.sourceक्रमge.jp>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pci.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/माला.स>
#समावेश <linux/i2c.h>

#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dmxdev.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dvb_frontend.h>

#समावेश "tc90522.h"
#समावेश "qm1d1b0004.h"
#समावेश "dvb-pll.h"

#घोषणा DRIVER_NAME "earth-pt1"

#घोषणा PT1_PAGE_SHIFT 12
#घोषणा PT1_PAGE_SIZE (1 << PT1_PAGE_SHIFT)
#घोषणा PT1_NR_UPACKETS 1024
#घोषणा PT1_NR_BUFS 511

काष्ठा pt1_buffer_page अणु
	__le32 upackets[PT1_NR_UPACKETS];
पूर्ण;

काष्ठा pt1_table_page अणु
	__le32 next_pfn;
	__le32 buf_pfns[PT1_NR_BUFS];
पूर्ण;

काष्ठा pt1_buffer अणु
	काष्ठा pt1_buffer_page *page;
	dma_addr_t addr;
पूर्ण;

काष्ठा pt1_table अणु
	काष्ठा pt1_table_page *page;
	dma_addr_t addr;
	काष्ठा pt1_buffer bufs[PT1_NR_BUFS];
पूर्ण;

क्रमागत pt1_fe_clk अणु
	PT1_FE_CLK_20MHZ,	/* PT1 */
	PT1_FE_CLK_25MHZ,	/* PT2 */
पूर्ण;

#घोषणा PT1_NR_ADAPS 4

काष्ठा pt1_adapter;

काष्ठा pt1 अणु
	काष्ठा pci_dev *pdev;
	व्योम __iomem *regs;
	काष्ठा i2c_adapter i2c_adap;
	पूर्णांक i2c_running;
	काष्ठा pt1_adapter *adaps[PT1_NR_ADAPS];
	काष्ठा pt1_table *tables;
	काष्ठा task_काष्ठा *kthपढ़ो;
	पूर्णांक table_index;
	पूर्णांक buf_index;

	काष्ठा mutex lock;
	पूर्णांक घातer;
	पूर्णांक reset;

	क्रमागत pt1_fe_clk fe_clk;
पूर्ण;

काष्ठा pt1_adapter अणु
	काष्ठा pt1 *pt1;
	पूर्णांक index;

	u8 *buf;
	पूर्णांक upacket_count;
	पूर्णांक packet_count;
	पूर्णांक st_count;

	काष्ठा dvb_adapter adap;
	काष्ठा dvb_demux demux;
	पूर्णांक users;
	काष्ठा dmxdev dmxdev;
	काष्ठा dvb_frontend *fe;
	काष्ठा i2c_client *demod_i2c_client;
	काष्ठा i2c_client *tuner_i2c_client;
	पूर्णांक (*orig_set_voltage)(काष्ठा dvb_frontend *fe,
				क्रमागत fe_sec_voltage voltage);
	पूर्णांक (*orig_sleep)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*orig_init)(काष्ठा dvb_frontend *fe);

	क्रमागत fe_sec_voltage voltage;
	पूर्णांक sleep;
पूर्ण;

जोड़ pt1_tuner_config अणु
	काष्ठा qm1d1b0004_config qm1d1b0004;
	काष्ठा dvb_pll_config tda6651;
पूर्ण;

काष्ठा pt1_config अणु
	काष्ठा i2c_board_info demod_info;
	काष्ठा tc90522_config demod_cfg;

	काष्ठा i2c_board_info tuner_info;
	जोड़ pt1_tuner_config tuner_cfg;
पूर्ण;

अटल स्थिर काष्ठा pt1_config pt1_configs[PT1_NR_ADAPS] = अणु
	अणु
		.demod_info = अणु
			I2C_BOARD_INFO(TC90522_I2C_DEV_SAT, 0x1b),
		पूर्ण,
		.tuner_info = अणु
			I2C_BOARD_INFO("qm1d1b0004", 0x60),
		पूर्ण,
	पूर्ण,
	अणु
		.demod_info = अणु
			I2C_BOARD_INFO(TC90522_I2C_DEV_TER, 0x1a),
		पूर्ण,
		.tuner_info = अणु
			I2C_BOARD_INFO("tda665x_earthpt1", 0x61),
		पूर्ण,
	पूर्ण,
	अणु
		.demod_info = अणु
			I2C_BOARD_INFO(TC90522_I2C_DEV_SAT, 0x19),
		पूर्ण,
		.tuner_info = अणु
			I2C_BOARD_INFO("qm1d1b0004", 0x60),
		पूर्ण,
	पूर्ण,
	अणु
		.demod_info = अणु
			I2C_BOARD_INFO(TC90522_I2C_DEV_TER, 0x18),
		पूर्ण,
		.tuner_info = अणु
			I2C_BOARD_INFO("tda665x_earthpt1", 0x61),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर u8 va1j5jf8007s_20mhz_configs[][2] = अणु
	अणु0x04, 0x02पूर्ण, अणु0x0d, 0x55पूर्ण, अणु0x11, 0x40पूर्ण, अणु0x13, 0x80पूर्ण, अणु0x17, 0x01पूर्ण,
	अणु0x1c, 0x0aपूर्ण, अणु0x1d, 0xaaपूर्ण, अणु0x1e, 0x20पूर्ण, अणु0x1f, 0x88पूर्ण, अणु0x51, 0xb0पूर्ण,
	अणु0x52, 0x89पूर्ण, अणु0x53, 0xb3पूर्ण, अणु0x5a, 0x2dपूर्ण, अणु0x5b, 0xd3पूर्ण, अणु0x85, 0x69पूर्ण,
	अणु0x87, 0x04पूर्ण, अणु0x8e, 0x02पूर्ण, अणु0xa3, 0xf7पूर्ण, अणु0xa5, 0xc0पूर्ण,
पूर्ण;

अटल स्थिर u8 va1j5jf8007s_25mhz_configs[][2] = अणु
	अणु0x04, 0x02पूर्ण, अणु0x11, 0x40पूर्ण, अणु0x13, 0x80पूर्ण, अणु0x17, 0x01पूर्ण, अणु0x1c, 0x0aपूर्ण,
	अणु0x1d, 0xaaपूर्ण, अणु0x1e, 0x20पूर्ण, अणु0x1f, 0x88पूर्ण, अणु0x51, 0xb0पूर्ण, अणु0x52, 0x89पूर्ण,
	अणु0x53, 0xb3पूर्ण, अणु0x5a, 0x2dपूर्ण, अणु0x5b, 0xd3पूर्ण, अणु0x85, 0x69पूर्ण, अणु0x87, 0x04पूर्ण,
	अणु0x8e, 0x26पूर्ण, अणु0xa3, 0xf7पूर्ण, अणु0xa5, 0xc0पूर्ण,
पूर्ण;

अटल स्थिर u8 va1j5jf8007t_20mhz_configs[][2] = अणु
	अणु0x03, 0x90पूर्ण, अणु0x14, 0x8fपूर्ण, अणु0x1c, 0x2aपूर्ण, अणु0x1d, 0xa8पूर्ण, अणु0x1e, 0xa2पूर्ण,
	अणु0x22, 0x83पूर्ण, अणु0x31, 0x0dपूर्ण, अणु0x32, 0xe0पूर्ण, अणु0x39, 0xd3पूर्ण, अणु0x3a, 0x00पूर्ण,
	अणु0x3b, 0x11पूर्ण, अणु0x3c, 0x3fपूर्ण,
	अणु0x5c, 0x40पूर्ण, अणु0x5f, 0x80पूर्ण, अणु0x75, 0x02पूर्ण, अणु0x76, 0x4eपूर्ण, अणु0x77, 0x03पूर्ण,
	अणु0xef, 0x01पूर्ण
पूर्ण;

अटल स्थिर u8 va1j5jf8007t_25mhz_configs[][2] = अणु
	अणु0x03, 0x90पूर्ण, अणु0x1c, 0x2aपूर्ण, अणु0x1d, 0xa8पूर्ण, अणु0x1e, 0xa2पूर्ण, अणु0x22, 0x83पूर्ण,
	अणु0x3a, 0x04पूर्ण, अणु0x3b, 0x11पूर्ण, अणु0x3c, 0x3fपूर्ण, अणु0x5c, 0x40पूर्ण, अणु0x5f, 0x80पूर्ण,
	अणु0x75, 0x0aपूर्ण, अणु0x76, 0x4cपूर्ण, अणु0x77, 0x03पूर्ण, अणु0xef, 0x01पूर्ण
पूर्ण;

अटल पूर्णांक config_demod(काष्ठा i2c_client *cl, क्रमागत pt1_fe_clk clk)
अणु
	पूर्णांक ret;
	bool is_sat;
	स्थिर u8 (*cfg_data)[2];
	पूर्णांक i, len;

	is_sat = !म_भेदन(cl->name, TC90522_I2C_DEV_SAT,
			  म_माप(TC90522_I2C_DEV_SAT));
	अगर (is_sat) अणु
		काष्ठा i2c_msg msg[2];
		u8 wbuf, rbuf;

		wbuf = 0x07;
		msg[0].addr = cl->addr;
		msg[0].flags = 0;
		msg[0].len = 1;
		msg[0].buf = &wbuf;

		msg[1].addr = cl->addr;
		msg[1].flags = I2C_M_RD;
		msg[1].len = 1;
		msg[1].buf = &rbuf;
		ret = i2c_transfer(cl->adapter, msg, 2);
		अगर (ret < 0)
			वापस ret;
		अगर (rbuf != 0x41)
			वापस -EIO;
	पूर्ण

	/* frontend init */
	अगर (clk == PT1_FE_CLK_20MHZ) अणु
		अगर (is_sat) अणु
			cfg_data = va1j5jf8007s_20mhz_configs;
			len = ARRAY_SIZE(va1j5jf8007s_20mhz_configs);
		पूर्ण अन्यथा अणु
			cfg_data = va1j5jf8007t_20mhz_configs;
			len = ARRAY_SIZE(va1j5jf8007t_20mhz_configs);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (is_sat) अणु
			cfg_data = va1j5jf8007s_25mhz_configs;
			len = ARRAY_SIZE(va1j5jf8007s_25mhz_configs);
		पूर्ण अन्यथा अणु
			cfg_data = va1j5jf8007t_25mhz_configs;
			len = ARRAY_SIZE(va1j5jf8007t_25mhz_configs);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		ret = i2c_master_send(cl, cfg_data[i], 2);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Init रेजिस्टरs क्रम (each pair of) terrestrial/satellite block in demod.
 * Note that resetting terr. block also resets its peer sat. block as well.
 * This function must be called beक्रमe configuring any demod block
 * (beक्रमe pt1_wakeup(), fe->ops.init()).
 */
अटल पूर्णांक pt1_demod_block_init(काष्ठा pt1 *pt1)
अणु
	काष्ठा i2c_client *cl;
	u8 buf[2] = अणु0x01, 0x80पूर्ण;
	पूर्णांक ret;
	पूर्णांक i;

	/* reset all terr. & sat. pairs first */
	क्रम (i = 0; i < PT1_NR_ADAPS; i++) अणु
		cl = pt1->adaps[i]->demod_i2c_client;
		अगर (म_भेदन(cl->name, TC90522_I2C_DEV_TER,
			    म_माप(TC90522_I2C_DEV_TER)))
			जारी;

		ret = i2c_master_send(cl, buf, 2);
		अगर (ret < 0)
			वापस ret;
		usleep_range(30000, 50000);
	पूर्ण

	क्रम (i = 0; i < PT1_NR_ADAPS; i++) अणु
		cl = pt1->adaps[i]->demod_i2c_client;
		अगर (म_भेदन(cl->name, TC90522_I2C_DEV_SAT,
			    म_माप(TC90522_I2C_DEV_SAT)))
			जारी;

		ret = i2c_master_send(cl, buf, 2);
		अगर (ret < 0)
			वापस ret;
		usleep_range(30000, 50000);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pt1_ग_लिखो_reg(काष्ठा pt1 *pt1, पूर्णांक reg, u32 data)
अणु
	ग_लिखोl(data, pt1->regs + reg * 4);
पूर्ण

अटल u32 pt1_पढ़ो_reg(काष्ठा pt1 *pt1, पूर्णांक reg)
अणु
	वापस पढ़ोl(pt1->regs + reg * 4);
पूर्ण

अटल अचिन्हित पूर्णांक pt1_nr_tables = 8;
module_param_named(nr_tables, pt1_nr_tables, uपूर्णांक, 0);

अटल व्योम pt1_increment_table_count(काष्ठा pt1 *pt1)
अणु
	pt1_ग_लिखो_reg(pt1, 0, 0x00000020);
पूर्ण

अटल व्योम pt1_init_table_count(काष्ठा pt1 *pt1)
अणु
	pt1_ग_लिखो_reg(pt1, 0, 0x00000010);
पूर्ण

अटल व्योम pt1_रेजिस्टर_tables(काष्ठा pt1 *pt1, u32 first_pfn)
अणु
	pt1_ग_लिखो_reg(pt1, 5, first_pfn);
	pt1_ग_लिखो_reg(pt1, 0, 0x0c000040);
पूर्ण

अटल व्योम pt1_unरेजिस्टर_tables(काष्ठा pt1 *pt1)
अणु
	pt1_ग_लिखो_reg(pt1, 0, 0x08080000);
पूर्ण

अटल पूर्णांक pt1_sync(काष्ठा pt1 *pt1)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 57; i++) अणु
		अगर (pt1_पढ़ो_reg(pt1, 0) & 0x20000000)
			वापस 0;
		pt1_ग_लिखो_reg(pt1, 0, 0x00000008);
	पूर्ण
	dev_err(&pt1->pdev->dev, "could not sync\n");
	वापस -EIO;
पूर्ण

अटल u64 pt1_identअगरy(काष्ठा pt1 *pt1)
अणु
	पूर्णांक i;
	u64 id = 0;
	क्रम (i = 0; i < 57; i++) अणु
		id |= (u64)(pt1_पढ़ो_reg(pt1, 0) >> 30 & 1) << i;
		pt1_ग_लिखो_reg(pt1, 0, 0x00000008);
	पूर्ण
	वापस id;
पूर्ण

अटल पूर्णांक pt1_unlock(काष्ठा pt1 *pt1)
अणु
	पूर्णांक i;
	pt1_ग_लिखो_reg(pt1, 0, 0x00000008);
	क्रम (i = 0; i < 3; i++) अणु
		अगर (pt1_पढ़ो_reg(pt1, 0) & 0x80000000)
			वापस 0;
		usleep_range(1000, 2000);
	पूर्ण
	dev_err(&pt1->pdev->dev, "could not unlock\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक pt1_reset_pci(काष्ठा pt1 *pt1)
अणु
	पूर्णांक i;
	pt1_ग_लिखो_reg(pt1, 0, 0x01010000);
	pt1_ग_लिखो_reg(pt1, 0, 0x01000000);
	क्रम (i = 0; i < 10; i++) अणु
		अगर (pt1_पढ़ो_reg(pt1, 0) & 0x00000001)
			वापस 0;
		usleep_range(1000, 2000);
	पूर्ण
	dev_err(&pt1->pdev->dev, "could not reset PCI\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक pt1_reset_ram(काष्ठा pt1 *pt1)
अणु
	पूर्णांक i;
	pt1_ग_लिखो_reg(pt1, 0, 0x02020000);
	pt1_ग_लिखो_reg(pt1, 0, 0x02000000);
	क्रम (i = 0; i < 10; i++) अणु
		अगर (pt1_पढ़ो_reg(pt1, 0) & 0x00000002)
			वापस 0;
		usleep_range(1000, 2000);
	पूर्ण
	dev_err(&pt1->pdev->dev, "could not reset RAM\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक pt1_करो_enable_ram(काष्ठा pt1 *pt1)
अणु
	पूर्णांक i, j;
	u32 status;
	status = pt1_पढ़ो_reg(pt1, 0) & 0x00000004;
	pt1_ग_लिखो_reg(pt1, 0, 0x00000002);
	क्रम (i = 0; i < 10; i++) अणु
		क्रम (j = 0; j < 1024; j++) अणु
			अगर ((pt1_पढ़ो_reg(pt1, 0) & 0x00000004) != status)
				वापस 0;
		पूर्ण
		usleep_range(1000, 2000);
	पूर्ण
	dev_err(&pt1->pdev->dev, "could not enable RAM\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक pt1_enable_ram(काष्ठा pt1 *pt1)
अणु
	पूर्णांक i, ret;
	पूर्णांक phase;
	usleep_range(1000, 2000);
	phase = pt1->pdev->device == 0x211a ? 128 : 166;
	क्रम (i = 0; i < phase; i++) अणु
		ret = pt1_करो_enable_ram(pt1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pt1_disable_ram(काष्ठा pt1 *pt1)
अणु
	pt1_ग_लिखो_reg(pt1, 0, 0x0b0b0000);
पूर्ण

अटल व्योम pt1_set_stream(काष्ठा pt1 *pt1, पूर्णांक index, पूर्णांक enabled)
अणु
	pt1_ग_लिखो_reg(pt1, 2, 1 << (index + 8) | enabled << index);
पूर्ण

अटल व्योम pt1_init_streams(काष्ठा pt1 *pt1)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < PT1_NR_ADAPS; i++)
		pt1_set_stream(pt1, i, 0);
पूर्ण

अटल पूर्णांक pt1_filter(काष्ठा pt1 *pt1, काष्ठा pt1_buffer_page *page)
अणु
	u32 upacket;
	पूर्णांक i;
	पूर्णांक index;
	काष्ठा pt1_adapter *adap;
	पूर्णांक offset;
	u8 *buf;
	पूर्णांक sc;

	अगर (!page->upackets[PT1_NR_UPACKETS - 1])
		वापस 0;

	क्रम (i = 0; i < PT1_NR_UPACKETS; i++) अणु
		upacket = le32_to_cpu(page->upackets[i]);
		index = (upacket >> 29) - 1;
		अगर (index < 0 || index >=  PT1_NR_ADAPS)
			जारी;

		adap = pt1->adaps[index];
		अगर (upacket >> 25 & 1)
			adap->upacket_count = 0;
		अन्यथा अगर (!adap->upacket_count)
			जारी;

		अगर (upacket >> 24 & 1)
			prपूर्णांकk_ratelimited(KERN_INFO "earth-pt1: device buffer overflowing. table[%d] buf[%d]\n",
				pt1->table_index, pt1->buf_index);
		sc = upacket >> 26 & 0x7;
		अगर (adap->st_count != -1 && sc != ((adap->st_count + 1) & 0x7))
			prपूर्णांकk_ratelimited(KERN_INFO "earth-pt1: data loss in streamID(adapter)[%d]\n",
					   index);
		adap->st_count = sc;

		buf = adap->buf;
		offset = adap->packet_count * 188 + adap->upacket_count * 3;
		buf[offset] = upacket >> 16;
		buf[offset + 1] = upacket >> 8;
		अगर (adap->upacket_count != 62)
			buf[offset + 2] = upacket;

		अगर (++adap->upacket_count >= 63) अणु
			adap->upacket_count = 0;
			अगर (++adap->packet_count >= 21) अणु
				dvb_dmx_swfilter_packets(&adap->demux, buf, 21);
				adap->packet_count = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	page->upackets[PT1_NR_UPACKETS - 1] = 0;
	वापस 1;
पूर्ण

अटल पूर्णांक pt1_thपढ़ो(व्योम *data)
अणु
	काष्ठा pt1 *pt1;
	काष्ठा pt1_buffer_page *page;
	bool was_frozen;

#घोषणा PT1_FETCH_DELAY 10
#घोषणा PT1_FETCH_DELAY_DELTA 2

	pt1 = data;
	set_मुक्तzable();

	जबतक (!kthपढ़ो_मुक्तzable_should_stop(&was_frozen)) अणु
		अगर (was_frozen) अणु
			पूर्णांक i;

			क्रम (i = 0; i < PT1_NR_ADAPS; i++)
				pt1_set_stream(pt1, i, !!pt1->adaps[i]->users);
		पूर्ण

		page = pt1->tables[pt1->table_index].bufs[pt1->buf_index].page;
		अगर (!pt1_filter(pt1, page)) अणु
			kसमय_प्रकार delay;

			delay = kसमय_set(0, PT1_FETCH_DELAY * NSEC_PER_MSEC);
			set_current_state(TASK_INTERRUPTIBLE);
			schedule_hrसमयout_range(&delay,
					PT1_FETCH_DELAY_DELTA * NSEC_PER_MSEC,
					HRTIMER_MODE_REL);
			जारी;
		पूर्ण

		अगर (++pt1->buf_index >= PT1_NR_BUFS) अणु
			pt1_increment_table_count(pt1);
			pt1->buf_index = 0;
			अगर (++pt1->table_index >= pt1_nr_tables)
				pt1->table_index = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pt1_मुक्त_page(काष्ठा pt1 *pt1, व्योम *page, dma_addr_t addr)
अणु
	dma_मुक्त_coherent(&pt1->pdev->dev, PT1_PAGE_SIZE, page, addr);
पूर्ण

अटल व्योम *pt1_alloc_page(काष्ठा pt1 *pt1, dma_addr_t *addrp, u32 *pfnp)
अणु
	व्योम *page;
	dma_addr_t addr;

	page = dma_alloc_coherent(&pt1->pdev->dev, PT1_PAGE_SIZE, &addr,
				  GFP_KERNEL);
	अगर (page == शून्य)
		वापस शून्य;

	BUG_ON(addr & (PT1_PAGE_SIZE - 1));
	BUG_ON(addr >> PT1_PAGE_SHIFT >> 31 >> 1);

	*addrp = addr;
	*pfnp = addr >> PT1_PAGE_SHIFT;
	वापस page;
पूर्ण

अटल व्योम pt1_cleanup_buffer(काष्ठा pt1 *pt1, काष्ठा pt1_buffer *buf)
अणु
	pt1_मुक्त_page(pt1, buf->page, buf->addr);
पूर्ण

अटल पूर्णांक
pt1_init_buffer(काष्ठा pt1 *pt1, काष्ठा pt1_buffer *buf,  u32 *pfnp)
अणु
	काष्ठा pt1_buffer_page *page;
	dma_addr_t addr;

	page = pt1_alloc_page(pt1, &addr, pfnp);
	अगर (page == शून्य)
		वापस -ENOMEM;

	page->upackets[PT1_NR_UPACKETS - 1] = 0;

	buf->page = page;
	buf->addr = addr;
	वापस 0;
पूर्ण

अटल व्योम pt1_cleanup_table(काष्ठा pt1 *pt1, काष्ठा pt1_table *table)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PT1_NR_BUFS; i++)
		pt1_cleanup_buffer(pt1, &table->bufs[i]);

	pt1_मुक्त_page(pt1, table->page, table->addr);
पूर्ण

अटल पूर्णांक
pt1_init_table(काष्ठा pt1 *pt1, काष्ठा pt1_table *table, u32 *pfnp)
अणु
	काष्ठा pt1_table_page *page;
	dma_addr_t addr;
	पूर्णांक i, ret;
	u32 buf_pfn;

	page = pt1_alloc_page(pt1, &addr, pfnp);
	अगर (page == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < PT1_NR_BUFS; i++) अणु
		ret = pt1_init_buffer(pt1, &table->bufs[i], &buf_pfn);
		अगर (ret < 0)
			जाओ err;

		page->buf_pfns[i] = cpu_to_le32(buf_pfn);
	पूर्ण

	pt1_increment_table_count(pt1);
	table->page = page;
	table->addr = addr;
	वापस 0;

err:
	जबतक (i--)
		pt1_cleanup_buffer(pt1, &table->bufs[i]);

	pt1_मुक्त_page(pt1, page, addr);
	वापस ret;
पूर्ण

अटल व्योम pt1_cleanup_tables(काष्ठा pt1 *pt1)
अणु
	काष्ठा pt1_table *tables;
	पूर्णांक i;

	tables = pt1->tables;
	pt1_unरेजिस्टर_tables(pt1);

	क्रम (i = 0; i < pt1_nr_tables; i++)
		pt1_cleanup_table(pt1, &tables[i]);

	vमुक्त(tables);
पूर्ण

अटल पूर्णांक pt1_init_tables(काष्ठा pt1 *pt1)
अणु
	काष्ठा pt1_table *tables;
	पूर्णांक i, ret;
	u32 first_pfn, pfn;

	अगर (!pt1_nr_tables)
		वापस 0;

	tables = vदो_स्मृति(array_size(pt1_nr_tables, माप(काष्ठा pt1_table)));
	अगर (tables == शून्य)
		वापस -ENOMEM;

	pt1_init_table_count(pt1);

	i = 0;
	ret = pt1_init_table(pt1, &tables[0], &first_pfn);
	अगर (ret)
		जाओ err;
	i++;

	जबतक (i < pt1_nr_tables) अणु
		ret = pt1_init_table(pt1, &tables[i], &pfn);
		अगर (ret)
			जाओ err;
		tables[i - 1].page->next_pfn = cpu_to_le32(pfn);
		i++;
	पूर्ण

	tables[pt1_nr_tables - 1].page->next_pfn = cpu_to_le32(first_pfn);

	pt1_रेजिस्टर_tables(pt1, first_pfn);
	pt1->tables = tables;
	वापस 0;

err:
	जबतक (i--)
		pt1_cleanup_table(pt1, &tables[i]);

	vमुक्त(tables);
	वापस ret;
पूर्ण

अटल पूर्णांक pt1_start_polling(काष्ठा pt1 *pt1)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&pt1->lock);
	अगर (!pt1->kthपढ़ो) अणु
		pt1->kthपढ़ो = kthपढ़ो_run(pt1_thपढ़ो, pt1, "earth-pt1");
		अगर (IS_ERR(pt1->kthपढ़ो)) अणु
			ret = PTR_ERR(pt1->kthपढ़ो);
			pt1->kthपढ़ो = शून्य;
		पूर्ण
	पूर्ण
	mutex_unlock(&pt1->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pt1_start_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा pt1_adapter *adap;
	adap = container_of(feed->demux, काष्ठा pt1_adapter, demux);
	अगर (!adap->users++) अणु
		पूर्णांक ret;

		ret = pt1_start_polling(adap->pt1);
		अगर (ret)
			वापस ret;
		pt1_set_stream(adap->pt1, adap->index, 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pt1_stop_polling(काष्ठा pt1 *pt1)
अणु
	पूर्णांक i, count;

	mutex_lock(&pt1->lock);
	क्रम (i = 0, count = 0; i < PT1_NR_ADAPS; i++)
		count += pt1->adaps[i]->users;

	अगर (count == 0 && pt1->kthपढ़ो) अणु
		kthपढ़ो_stop(pt1->kthपढ़ो);
		pt1->kthपढ़ो = शून्य;
	पूर्ण
	mutex_unlock(&pt1->lock);
पूर्ण

अटल पूर्णांक pt1_stop_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा pt1_adapter *adap;
	adap = container_of(feed->demux, काष्ठा pt1_adapter, demux);
	अगर (!--adap->users) अणु
		pt1_set_stream(adap->pt1, adap->index, 0);
		pt1_stop_polling(adap->pt1);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
pt1_update_घातer(काष्ठा pt1 *pt1)
अणु
	पूर्णांक bits;
	पूर्णांक i;
	काष्ठा pt1_adapter *adap;
	अटल स्थिर पूर्णांक sleep_bits[] = अणु
		1 << 4,
		1 << 6 | 1 << 7,
		1 << 5,
		1 << 6 | 1 << 8,
	पूर्ण;

	bits = pt1->घातer | !pt1->reset << 3;
	mutex_lock(&pt1->lock);
	क्रम (i = 0; i < PT1_NR_ADAPS; i++) अणु
		adap = pt1->adaps[i];
		चयन (adap->voltage) अणु
		हाल SEC_VOLTAGE_13: /* actually 11V */
			bits |= 1 << 2;
			अवरोध;
		हाल SEC_VOLTAGE_18: /* actually 15V */
			bits |= 1 << 1 | 1 << 2;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		/* XXX: The bits should be changed depending on adap->sleep. */
		bits |= sleep_bits[i];
	पूर्ण
	pt1_ग_लिखो_reg(pt1, 1, bits);
	mutex_unlock(&pt1->lock);
पूर्ण

अटल पूर्णांक pt1_set_voltage(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा pt1_adapter *adap;

	adap = container_of(fe->dvb, काष्ठा pt1_adapter, adap);
	adap->voltage = voltage;
	pt1_update_घातer(adap->pt1);

	अगर (adap->orig_set_voltage)
		वापस adap->orig_set_voltage(fe, voltage);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक pt1_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा pt1_adapter *adap;
	पूर्णांक ret;

	adap = container_of(fe->dvb, काष्ठा pt1_adapter, adap);

	ret = 0;
	अगर (adap->orig_sleep)
		ret = adap->orig_sleep(fe);

	adap->sleep = 1;
	pt1_update_घातer(adap->pt1);
	वापस ret;
पूर्ण

अटल पूर्णांक pt1_wakeup(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा pt1_adapter *adap;
	पूर्णांक ret;

	adap = container_of(fe->dvb, काष्ठा pt1_adapter, adap);
	adap->sleep = 0;
	pt1_update_घातer(adap->pt1);
	usleep_range(1000, 2000);

	ret = config_demod(adap->demod_i2c_client, adap->pt1->fe_clk);
	अगर (ret == 0 && adap->orig_init)
		ret = adap->orig_init(fe);
	वापस ret;
पूर्ण

अटल व्योम pt1_मुक्त_adapter(काष्ठा pt1_adapter *adap)
अणु
	adap->demux.dmx.बंद(&adap->demux.dmx);
	dvb_dmxdev_release(&adap->dmxdev);
	dvb_dmx_release(&adap->demux);
	dvb_unरेजिस्टर_adapter(&adap->adap);
	मुक्त_page((अचिन्हित दीर्घ)adap->buf);
	kमुक्त(adap);
पूर्ण

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल काष्ठा pt1_adapter *
pt1_alloc_adapter(काष्ठा pt1 *pt1)
अणु
	काष्ठा pt1_adapter *adap;
	व्योम *buf;
	काष्ठा dvb_adapter *dvb_adap;
	काष्ठा dvb_demux *demux;
	काष्ठा dmxdev *dmxdev;
	पूर्णांक ret;

	adap = kzalloc(माप(काष्ठा pt1_adapter), GFP_KERNEL);
	अगर (!adap) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	adap->pt1 = pt1;

	adap->voltage = SEC_VOLTAGE_OFF;
	adap->sleep = 1;

	buf = (u8 *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ err_kमुक्त;
	पूर्ण

	adap->buf = buf;
	adap->upacket_count = 0;
	adap->packet_count = 0;
	adap->st_count = -1;

	dvb_adap = &adap->adap;
	dvb_adap->priv = adap;
	ret = dvb_रेजिस्टर_adapter(dvb_adap, DRIVER_NAME, THIS_MODULE,
				   &pt1->pdev->dev, adapter_nr);
	अगर (ret < 0)
		जाओ err_मुक्त_page;

	demux = &adap->demux;
	demux->dmx.capabilities = DMX_TS_FILTERING | DMX_SECTION_FILTERING;
	demux->priv = adap;
	demux->feednum = 256;
	demux->filternum = 256;
	demux->start_feed = pt1_start_feed;
	demux->stop_feed = pt1_stop_feed;
	demux->ग_लिखो_to_decoder = शून्य;
	ret = dvb_dmx_init(demux);
	अगर (ret < 0)
		जाओ err_unरेजिस्टर_adapter;

	dmxdev = &adap->dmxdev;
	dmxdev->filternum = 256;
	dmxdev->demux = &demux->dmx;
	dmxdev->capabilities = 0;
	ret = dvb_dmxdev_init(dmxdev, dvb_adap);
	अगर (ret < 0)
		जाओ err_dmx_release;

	वापस adap;

err_dmx_release:
	dvb_dmx_release(demux);
err_unरेजिस्टर_adapter:
	dvb_unरेजिस्टर_adapter(dvb_adap);
err_मुक्त_page:
	मुक्त_page((अचिन्हित दीर्घ)buf);
err_kमुक्त:
	kमुक्त(adap);
err:
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम pt1_cleanup_adapters(काष्ठा pt1 *pt1)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < PT1_NR_ADAPS; i++)
		pt1_मुक्त_adapter(pt1->adaps[i]);
पूर्ण

अटल पूर्णांक pt1_init_adapters(काष्ठा pt1 *pt1)
अणु
	पूर्णांक i;
	काष्ठा pt1_adapter *adap;
	पूर्णांक ret;

	क्रम (i = 0; i < PT1_NR_ADAPS; i++) अणु
		adap = pt1_alloc_adapter(pt1);
		अगर (IS_ERR(adap)) अणु
			ret = PTR_ERR(adap);
			जाओ err;
		पूर्ण

		adap->index = i;
		pt1->adaps[i] = adap;
	पूर्ण
	वापस 0;

err:
	जबतक (i--)
		pt1_मुक्त_adapter(pt1->adaps[i]);

	वापस ret;
पूर्ण

अटल व्योम pt1_cleanup_frontend(काष्ठा pt1_adapter *adap)
अणु
	dvb_unरेजिस्टर_frontend(adap->fe);
	dvb_module_release(adap->tuner_i2c_client);
	dvb_module_release(adap->demod_i2c_client);
पूर्ण

अटल पूर्णांक pt1_init_frontend(काष्ठा pt1_adapter *adap, काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;

	adap->orig_set_voltage = fe->ops.set_voltage;
	adap->orig_sleep = fe->ops.sleep;
	adap->orig_init = fe->ops.init;
	fe->ops.set_voltage = pt1_set_voltage;
	fe->ops.sleep = pt1_sleep;
	fe->ops.init = pt1_wakeup;

	ret = dvb_रेजिस्टर_frontend(&adap->adap, fe);
	अगर (ret < 0)
		वापस ret;

	adap->fe = fe;
	वापस 0;
पूर्ण

अटल व्योम pt1_cleanup_frontends(काष्ठा pt1 *pt1)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < PT1_NR_ADAPS; i++)
		pt1_cleanup_frontend(pt1->adaps[i]);
पूर्ण

अटल पूर्णांक pt1_init_frontends(काष्ठा pt1 *pt1)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(pt1_configs); i++) अणु
		स्थिर काष्ठा i2c_board_info *info;
		काष्ठा tc90522_config dcfg;
		काष्ठा i2c_client *cl;

		info = &pt1_configs[i].demod_info;
		dcfg = pt1_configs[i].demod_cfg;
		dcfg.tuner_i2c = शून्य;

		ret = -ENODEV;
		cl = dvb_module_probe("tc90522", info->type, &pt1->i2c_adap,
				      info->addr, &dcfg);
		अगर (!cl)
			जाओ fe_unरेजिस्टर;
		pt1->adaps[i]->demod_i2c_client = cl;

		अगर (!म_भेदन(cl->name, TC90522_I2C_DEV_SAT,
			     म_माप(TC90522_I2C_DEV_SAT))) अणु
			काष्ठा qm1d1b0004_config tcfg;

			info = &pt1_configs[i].tuner_info;
			tcfg = pt1_configs[i].tuner_cfg.qm1d1b0004;
			tcfg.fe = dcfg.fe;
			cl = dvb_module_probe("qm1d1b0004",
					      info->type, dcfg.tuner_i2c,
					      info->addr, &tcfg);
		पूर्ण अन्यथा अणु
			काष्ठा dvb_pll_config tcfg;

			info = &pt1_configs[i].tuner_info;
			tcfg = pt1_configs[i].tuner_cfg.tda6651;
			tcfg.fe = dcfg.fe;
			cl = dvb_module_probe("dvb_pll",
					      info->type, dcfg.tuner_i2c,
					      info->addr, &tcfg);
		पूर्ण
		अगर (!cl)
			जाओ demod_release;
		pt1->adaps[i]->tuner_i2c_client = cl;

		ret = pt1_init_frontend(pt1->adaps[i], dcfg.fe);
		अगर (ret < 0)
			जाओ tuner_release;
	पूर्ण

	ret = pt1_demod_block_init(pt1);
	अगर (ret < 0)
		जाओ fe_unरेजिस्टर;

	वापस 0;

tuner_release:
	dvb_module_release(pt1->adaps[i]->tuner_i2c_client);
demod_release:
	dvb_module_release(pt1->adaps[i]->demod_i2c_client);
fe_unरेजिस्टर:
	dev_warn(&pt1->pdev->dev, "failed to init FE(%d).\n", i);
	i--;
	क्रम (; i >= 0; i--) अणु
		dvb_unरेजिस्टर_frontend(pt1->adaps[i]->fe);
		dvb_module_release(pt1->adaps[i]->tuner_i2c_client);
		dvb_module_release(pt1->adaps[i]->demod_i2c_client);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम pt1_i2c_emit(काष्ठा pt1 *pt1, पूर्णांक addr, पूर्णांक busy, पूर्णांक पढ़ो_enable,
			 पूर्णांक घड़ी, पूर्णांक data, पूर्णांक next_addr)
अणु
	pt1_ग_लिखो_reg(pt1, 4, addr << 18 | busy << 13 | पढ़ो_enable << 12 |
		      !घड़ी << 11 | !data << 10 | next_addr);
पूर्ण

अटल व्योम pt1_i2c_ग_लिखो_bit(काष्ठा pt1 *pt1, पूर्णांक addr, पूर्णांक *addrp, पूर्णांक data)
अणु
	pt1_i2c_emit(pt1, addr,     1, 0, 0, data, addr + 1);
	pt1_i2c_emit(pt1, addr + 1, 1, 0, 1, data, addr + 2);
	pt1_i2c_emit(pt1, addr + 2, 1, 0, 0, data, addr + 3);
	*addrp = addr + 3;
पूर्ण

अटल व्योम pt1_i2c_पढ़ो_bit(काष्ठा pt1 *pt1, पूर्णांक addr, पूर्णांक *addrp)
अणु
	pt1_i2c_emit(pt1, addr,     1, 0, 0, 1, addr + 1);
	pt1_i2c_emit(pt1, addr + 1, 1, 0, 1, 1, addr + 2);
	pt1_i2c_emit(pt1, addr + 2, 1, 1, 1, 1, addr + 3);
	pt1_i2c_emit(pt1, addr + 3, 1, 0, 0, 1, addr + 4);
	*addrp = addr + 4;
पूर्ण

अटल व्योम pt1_i2c_ग_लिखो_byte(काष्ठा pt1 *pt1, पूर्णांक addr, पूर्णांक *addrp, पूर्णांक data)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 8; i++)
		pt1_i2c_ग_लिखो_bit(pt1, addr, &addr, data >> (7 - i) & 1);
	pt1_i2c_ग_लिखो_bit(pt1, addr, &addr, 1);
	*addrp = addr;
पूर्ण

अटल व्योम pt1_i2c_पढ़ो_byte(काष्ठा pt1 *pt1, पूर्णांक addr, पूर्णांक *addrp, पूर्णांक last)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 8; i++)
		pt1_i2c_पढ़ो_bit(pt1, addr, &addr);
	pt1_i2c_ग_लिखो_bit(pt1, addr, &addr, last);
	*addrp = addr;
पूर्ण

अटल व्योम pt1_i2c_prepare(काष्ठा pt1 *pt1, पूर्णांक addr, पूर्णांक *addrp)
अणु
	pt1_i2c_emit(pt1, addr,     1, 0, 1, 1, addr + 1);
	pt1_i2c_emit(pt1, addr + 1, 1, 0, 1, 0, addr + 2);
	pt1_i2c_emit(pt1, addr + 2, 1, 0, 0, 0, addr + 3);
	*addrp = addr + 3;
पूर्ण

अटल व्योम
pt1_i2c_ग_लिखो_msg(काष्ठा pt1 *pt1, पूर्णांक addr, पूर्णांक *addrp, काष्ठा i2c_msg *msg)
अणु
	पूर्णांक i;
	pt1_i2c_prepare(pt1, addr, &addr);
	pt1_i2c_ग_लिखो_byte(pt1, addr, &addr, msg->addr << 1);
	क्रम (i = 0; i < msg->len; i++)
		pt1_i2c_ग_लिखो_byte(pt1, addr, &addr, msg->buf[i]);
	*addrp = addr;
पूर्ण

अटल व्योम
pt1_i2c_पढ़ो_msg(काष्ठा pt1 *pt1, पूर्णांक addr, पूर्णांक *addrp, काष्ठा i2c_msg *msg)
अणु
	पूर्णांक i;
	pt1_i2c_prepare(pt1, addr, &addr);
	pt1_i2c_ग_लिखो_byte(pt1, addr, &addr, msg->addr << 1 | 1);
	क्रम (i = 0; i < msg->len; i++)
		pt1_i2c_पढ़ो_byte(pt1, addr, &addr, i == msg->len - 1);
	*addrp = addr;
पूर्ण

अटल पूर्णांक pt1_i2c_end(काष्ठा pt1 *pt1, पूर्णांक addr)
अणु
	pt1_i2c_emit(pt1, addr,     1, 0, 0, 0, addr + 1);
	pt1_i2c_emit(pt1, addr + 1, 1, 0, 1, 0, addr + 2);
	pt1_i2c_emit(pt1, addr + 2, 1, 0, 1, 1, 0);

	pt1_ग_लिखो_reg(pt1, 0, 0x00000004);
	करो अणु
		अगर (संकेत_pending(current))
			वापस -EINTR;
		usleep_range(1000, 2000);
	पूर्ण जबतक (pt1_पढ़ो_reg(pt1, 0) & 0x00000080);
	वापस 0;
पूर्ण

अटल व्योम pt1_i2c_begin(काष्ठा pt1 *pt1, पूर्णांक *addrp)
अणु
	पूर्णांक addr = 0;

	pt1_i2c_emit(pt1, addr,     0, 0, 1, 1, addr /* itself */);
	addr = addr + 1;

	अगर (!pt1->i2c_running) अणु
		pt1_i2c_emit(pt1, addr,     1, 0, 1, 1, addr + 1);
		pt1_i2c_emit(pt1, addr + 1, 1, 0, 1, 0, addr + 2);
		addr = addr + 2;
		pt1->i2c_running = 1;
	पूर्ण
	*addrp = addr;
पूर्ण

अटल पूर्णांक pt1_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा pt1 *pt1;
	पूर्णांक i;
	काष्ठा i2c_msg *msg, *next_msg;
	पूर्णांक addr, ret;
	u16 len;
	u32 word;

	pt1 = i2c_get_adapdata(adap);

	क्रम (i = 0; i < num; i++) अणु
		msg = &msgs[i];
		अगर (msg->flags & I2C_M_RD)
			वापस -ENOTSUPP;

		अगर (i + 1 < num)
			next_msg = &msgs[i + 1];
		अन्यथा
			next_msg = शून्य;

		अगर (next_msg && next_msg->flags & I2C_M_RD) अणु
			i++;

			len = next_msg->len;
			अगर (len > 4)
				वापस -ENOTSUPP;

			pt1_i2c_begin(pt1, &addr);
			pt1_i2c_ग_लिखो_msg(pt1, addr, &addr, msg);
			pt1_i2c_पढ़ो_msg(pt1, addr, &addr, next_msg);
			ret = pt1_i2c_end(pt1, addr);
			अगर (ret < 0)
				वापस ret;

			word = pt1_पढ़ो_reg(pt1, 2);
			जबतक (len--) अणु
				next_msg->buf[len] = word;
				word >>= 8;
			पूर्ण
		पूर्ण अन्यथा अणु
			pt1_i2c_begin(pt1, &addr);
			pt1_i2c_ग_लिखो_msg(pt1, addr, &addr, msg);
			ret = pt1_i2c_end(pt1, addr);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस num;
पूर्ण

अटल u32 pt1_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm pt1_i2c_algo = अणु
	.master_xfer = pt1_i2c_xfer,
	.functionality = pt1_i2c_func,
पूर्ण;

अटल व्योम pt1_i2c_रुको(काष्ठा pt1 *pt1)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 128; i++)
		pt1_i2c_emit(pt1, 0, 0, 0, 1, 1, 0);
पूर्ण

अटल व्योम pt1_i2c_init(काष्ठा pt1 *pt1)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 1024; i++)
		pt1_i2c_emit(pt1, i, 0, 0, 1, 1, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक pt1_suspend(काष्ठा device *dev)
अणु
	काष्ठा pt1 *pt1 = dev_get_drvdata(dev);

	pt1_init_streams(pt1);
	pt1_disable_ram(pt1);
	pt1->घातer = 0;
	pt1->reset = 1;
	pt1_update_घातer(pt1);
	वापस 0;
पूर्ण

अटल पूर्णांक pt1_resume(काष्ठा device *dev)
अणु
	काष्ठा pt1 *pt1 = dev_get_drvdata(dev);
	पूर्णांक ret;
	पूर्णांक i;

	pt1->घातer = 0;
	pt1->reset = 1;
	pt1_update_घातer(pt1);

	pt1_i2c_init(pt1);
	pt1_i2c_रुको(pt1);

	ret = pt1_sync(pt1);
	अगर (ret < 0)
		जाओ resume_err;

	pt1_identअगरy(pt1);

	ret = pt1_unlock(pt1);
	अगर (ret < 0)
		जाओ resume_err;

	ret = pt1_reset_pci(pt1);
	अगर (ret < 0)
		जाओ resume_err;

	ret = pt1_reset_ram(pt1);
	अगर (ret < 0)
		जाओ resume_err;

	ret = pt1_enable_ram(pt1);
	अगर (ret < 0)
		जाओ resume_err;

	pt1_init_streams(pt1);

	pt1->घातer = 1;
	pt1_update_घातer(pt1);
	msleep(20);

	pt1->reset = 0;
	pt1_update_घातer(pt1);
	usleep_range(1000, 2000);

	ret = pt1_demod_block_init(pt1);
	अगर (ret < 0)
		जाओ resume_err;

	क्रम (i = 0; i < PT1_NR_ADAPS; i++)
		dvb_frontend_reinitialise(pt1->adaps[i]->fe);

	pt1_init_table_count(pt1);
	क्रम (i = 0; i < pt1_nr_tables; i++) अणु
		पूर्णांक j;

		क्रम (j = 0; j < PT1_NR_BUFS; j++)
			pt1->tables[i].bufs[j].page->upackets[PT1_NR_UPACKETS-1]
				= 0;
		pt1_increment_table_count(pt1);
	पूर्ण
	pt1_रेजिस्टर_tables(pt1, pt1->tables[0].addr >> PT1_PAGE_SHIFT);

	pt1->table_index = 0;
	pt1->buf_index = 0;
	क्रम (i = 0; i < PT1_NR_ADAPS; i++) अणु
		pt1->adaps[i]->upacket_count = 0;
		pt1->adaps[i]->packet_count = 0;
		pt1->adaps[i]->st_count = -1;
	पूर्ण

	वापस 0;

resume_err:
	dev_info(&pt1->pdev->dev, "failed to resume PT1/PT2.");
	वापस 0;	/* resume anyway */
पूर्ण

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल व्योम pt1_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pt1 *pt1;
	व्योम __iomem *regs;

	pt1 = pci_get_drvdata(pdev);
	regs = pt1->regs;

	अगर (pt1->kthपढ़ो)
		kthपढ़ो_stop(pt1->kthपढ़ो);
	pt1_cleanup_tables(pt1);
	pt1_cleanup_frontends(pt1);
	pt1_disable_ram(pt1);
	pt1->घातer = 0;
	pt1->reset = 1;
	pt1_update_घातer(pt1);
	pt1_cleanup_adapters(pt1);
	i2c_del_adapter(&pt1->i2c_adap);
	kमुक्त(pt1);
	pci_iounmap(pdev, regs);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक pt1_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक ret;
	व्योम __iomem *regs;
	काष्ठा pt1 *pt1;
	काष्ठा i2c_adapter *i2c_adap;

	ret = pci_enable_device(pdev);
	अगर (ret < 0)
		जाओ err;

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (ret < 0)
		जाओ err_pci_disable_device;

	pci_set_master(pdev);

	ret = pci_request_regions(pdev, DRIVER_NAME);
	अगर (ret < 0)
		जाओ err_pci_disable_device;

	regs = pci_iomap(pdev, 0, 0);
	अगर (!regs) अणु
		ret = -EIO;
		जाओ err_pci_release_regions;
	पूर्ण

	pt1 = kzalloc(माप(काष्ठा pt1), GFP_KERNEL);
	अगर (!pt1) अणु
		ret = -ENOMEM;
		जाओ err_pci_iounmap;
	पूर्ण

	mutex_init(&pt1->lock);
	pt1->pdev = pdev;
	pt1->regs = regs;
	pt1->fe_clk = (pdev->device == 0x211a) ?
				PT1_FE_CLK_20MHZ : PT1_FE_CLK_25MHZ;
	pci_set_drvdata(pdev, pt1);

	ret = pt1_init_adapters(pt1);
	अगर (ret < 0)
		जाओ err_kमुक्त;

	mutex_init(&pt1->lock);

	pt1->घातer = 0;
	pt1->reset = 1;
	pt1_update_घातer(pt1);

	i2c_adap = &pt1->i2c_adap;
	i2c_adap->algo = &pt1_i2c_algo;
	i2c_adap->algo_data = शून्य;
	i2c_adap->dev.parent = &pdev->dev;
	strscpy(i2c_adap->name, DRIVER_NAME, माप(i2c_adap->name));
	i2c_set_adapdata(i2c_adap, pt1);
	ret = i2c_add_adapter(i2c_adap);
	अगर (ret < 0)
		जाओ err_pt1_cleanup_adapters;

	pt1_i2c_init(pt1);
	pt1_i2c_रुको(pt1);

	ret = pt1_sync(pt1);
	अगर (ret < 0)
		जाओ err_i2c_del_adapter;

	pt1_identअगरy(pt1);

	ret = pt1_unlock(pt1);
	अगर (ret < 0)
		जाओ err_i2c_del_adapter;

	ret = pt1_reset_pci(pt1);
	अगर (ret < 0)
		जाओ err_i2c_del_adapter;

	ret = pt1_reset_ram(pt1);
	अगर (ret < 0)
		जाओ err_i2c_del_adapter;

	ret = pt1_enable_ram(pt1);
	अगर (ret < 0)
		जाओ err_i2c_del_adapter;

	pt1_init_streams(pt1);

	pt1->घातer = 1;
	pt1_update_घातer(pt1);
	msleep(20);

	pt1->reset = 0;
	pt1_update_घातer(pt1);
	usleep_range(1000, 2000);

	ret = pt1_init_frontends(pt1);
	अगर (ret < 0)
		जाओ err_pt1_disable_ram;

	ret = pt1_init_tables(pt1);
	अगर (ret < 0)
		जाओ err_pt1_cleanup_frontends;

	वापस 0;

err_pt1_cleanup_frontends:
	pt1_cleanup_frontends(pt1);
err_pt1_disable_ram:
	pt1_disable_ram(pt1);
	pt1->घातer = 0;
	pt1->reset = 1;
	pt1_update_घातer(pt1);
err_i2c_del_adapter:
	i2c_del_adapter(i2c_adap);
err_pt1_cleanup_adapters:
	pt1_cleanup_adapters(pt1);
err_kमुक्त:
	kमुक्त(pt1);
err_pci_iounmap:
	pci_iounmap(pdev, regs);
err_pci_release_regions:
	pci_release_regions(pdev);
err_pci_disable_device:
	pci_disable_device(pdev);
err:
	वापस ret;

पूर्ण

अटल स्थिर काष्ठा pci_device_id pt1_id_table[] = अणु
	अणु PCI_DEVICE(0x10ee, 0x211a) पूर्ण,
	अणु PCI_DEVICE(0x10ee, 0x222a) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, pt1_id_table);

अटल SIMPLE_DEV_PM_OPS(pt1_pm_ops, pt1_suspend, pt1_resume);

अटल काष्ठा pci_driver pt1_driver = अणु
	.name		= DRIVER_NAME,
	.probe		= pt1_probe,
	.हटाओ		= pt1_हटाओ,
	.id_table	= pt1_id_table,
	.driver.pm	= &pt1_pm_ops,
पूर्ण;

module_pci_driver(pt1_driver);

MODULE_AUTHOR("Takahito HIRANO <hiranotaka@zng.info>");
MODULE_DESCRIPTION("Earthsoft PT1/PT2 Driver");
MODULE_LICENSE("GPL");
