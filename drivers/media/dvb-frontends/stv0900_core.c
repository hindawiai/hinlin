<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * stv0900_core.c
 *
 * Driver क्रम ST STV0900 satellite demodulator IC.
 *
 * Copyright (C) ST Microelectronics.
 * Copyright (C) 2009 NetUP Inc.
 * Copyright (C) 2009 Igor M. Liplianin <liplianin@netup.ru>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>

#समावेश "stv0900.h"
#समावेश "stv0900_reg.h"
#समावेश "stv0900_priv.h"
#समावेश "stv0900_init.h"

पूर्णांक stvdebug = 1;
module_param_named(debug, stvdebug, पूर्णांक, 0644);

/* पूर्णांकernal params node */
काष्ठा stv0900_inode अणु
	/* poपूर्णांकer क्रम पूर्णांकernal params, one क्रम each pair of demods */
	काष्ठा stv0900_पूर्णांकernal		*पूर्णांकernal;
	काष्ठा stv0900_inode		*next_inode;
पूर्ण;

/* first पूर्णांकernal params */
अटल काष्ठा stv0900_inode *stv0900_first_inode;

/* find chip by i2c adapter and i2c address */
अटल काष्ठा stv0900_inode *find_inode(काष्ठा i2c_adapter *i2c_adap,
							u8 i2c_addr)
अणु
	काष्ठा stv0900_inode *temp_chip = stv0900_first_inode;

	अगर (temp_chip != शून्य) अणु
		/*
		 Search of the last stv0900 chip or
		 find it by i2c adapter and i2c address */
		जबतक ((temp_chip != शून्य) &&
			((temp_chip->पूर्णांकernal->i2c_adap != i2c_adap) ||
			(temp_chip->पूर्णांकernal->i2c_addr != i2c_addr)))

			temp_chip = temp_chip->next_inode;

	पूर्ण

	वापस temp_chip;
पूर्ण

/* deallocating chip */
अटल व्योम हटाओ_inode(काष्ठा stv0900_पूर्णांकernal *पूर्णांकernal)
अणु
	काष्ठा stv0900_inode *prev_node = stv0900_first_inode;
	काष्ठा stv0900_inode *del_node = find_inode(पूर्णांकernal->i2c_adap,
						पूर्णांकernal->i2c_addr);

	अगर (del_node != शून्य) अणु
		अगर (del_node == stv0900_first_inode) अणु
			stv0900_first_inode = del_node->next_inode;
		पूर्ण अन्यथा अणु
			जबतक (prev_node->next_inode != del_node)
				prev_node = prev_node->next_inode;

			अगर (del_node->next_inode == शून्य)
				prev_node->next_inode = शून्य;
			अन्यथा
				prev_node->next_inode =
					prev_node->next_inode->next_inode;
		पूर्ण

		kमुक्त(del_node);
	पूर्ण
पूर्ण

/* allocating new chip */
अटल काष्ठा stv0900_inode *append_पूर्णांकernal(काष्ठा stv0900_पूर्णांकernal *पूर्णांकernal)
अणु
	काष्ठा stv0900_inode *new_node = stv0900_first_inode;

	अगर (new_node == शून्य) अणु
		new_node = kदो_स्मृति(माप(काष्ठा stv0900_inode), GFP_KERNEL);
		stv0900_first_inode = new_node;
	पूर्ण अन्यथा अणु
		जबतक (new_node->next_inode != शून्य)
			new_node = new_node->next_inode;

		new_node->next_inode = kदो_स्मृति(माप(काष्ठा stv0900_inode),
								GFP_KERNEL);
		अगर (new_node->next_inode != शून्य)
			new_node = new_node->next_inode;
		अन्यथा
			new_node = शून्य;
	पूर्ण

	अगर (new_node != शून्य) अणु
		new_node->पूर्णांकernal = पूर्णांकernal;
		new_node->next_inode = शून्य;
	पूर्ण

	वापस new_node;
पूर्ण

s32 ge2comp(s32 a, s32 width)
अणु
	अगर (width == 32)
		वापस a;
	अन्यथा
		वापस (a >= (1 << (width - 1))) ? (a - (1 << width)) : a;
पूर्ण

व्योम stv0900_ग_लिखो_reg(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp, u16 reg_addr,
								u8 reg_data)
अणु
	u8 data[3];
	पूर्णांक ret;
	काष्ठा i2c_msg i2cmsg = अणु
		.addr  = पूर्णांकp->i2c_addr,
		.flags = 0,
		.len   = 3,
		.buf   = data,
	पूर्ण;

	data[0] = MSB(reg_addr);
	data[1] = LSB(reg_addr);
	data[2] = reg_data;

	ret = i2c_transfer(पूर्णांकp->i2c_adap, &i2cmsg, 1);
	अगर (ret != 1)
		dprपूर्णांकk("%s: i2c error %d\n", __func__, ret);
पूर्ण

u8 stv0900_पढ़ो_reg(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp, u16 reg)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु MSB(reg), LSB(reg) पूर्ण;
	u8 buf = 0;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr	= पूर्णांकp->i2c_addr,
			.flags	= 0,
			.buf = b0,
			.len = 2,
		पूर्ण, अणु
			.addr	= पूर्णांकp->i2c_addr,
			.flags	= I2C_M_RD,
			.buf = &buf,
			.len = 1,
		पूर्ण,
	पूर्ण;

	ret = i2c_transfer(पूर्णांकp->i2c_adap, msg, 2);
	अगर (ret != 2)
		dprपूर्णांकk("%s: i2c error %d, reg[0x%02x]\n",
				__func__, ret, reg);

	वापस buf;
पूर्ण

अटल व्योम extract_mask_pos(u32 label, u8 *mask, u8 *pos)
अणु
	u8 position = 0, i = 0;

	(*mask) = label & 0xff;

	जबतक ((position == 0) && (i < 8)) अणु
		position = ((*mask) >> i) & 0x01;
		i++;
	पूर्ण

	(*pos) = (i - 1);
पूर्ण

व्योम stv0900_ग_लिखो_bits(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp, u32 label, u8 val)
अणु
	u8 reg, mask, pos;

	reg = stv0900_पढ़ो_reg(पूर्णांकp, (label >> 16) & 0xffff);
	extract_mask_pos(label, &mask, &pos);

	val = mask & (val << pos);

	reg = (reg & (~mask)) | val;
	stv0900_ग_लिखो_reg(पूर्णांकp, (label >> 16) & 0xffff, reg);

पूर्ण

u8 stv0900_get_bits(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp, u32 label)
अणु
	u8 val;
	u8 mask, pos;

	extract_mask_pos(label, &mask, &pos);

	val = stv0900_पढ़ो_reg(पूर्णांकp, label >> 16);
	val = (val & mask) >> pos;

	वापस val;
पूर्ण

अटल क्रमागत fe_stv0900_error stv0900_initialize(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp)
अणु
	s32 i;

	अगर (पूर्णांकp == शून्य)
		वापस STV0900_INVALID_HANDLE;

	पूर्णांकp->chip_id = stv0900_पढ़ो_reg(पूर्णांकp, R0900_MID);

	अगर (पूर्णांकp->errs != STV0900_NO_ERROR)
		वापस पूर्णांकp->errs;

	/*Startup sequence*/
	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_DMDISTATE, 0x5c);
	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_DMDISTATE, 0x5c);
	msleep(3);
	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_TNRCFG, 0x6c);
	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_TNRCFG, 0x6f);
	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_I2CRPT, 0x20);
	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_I2CRPT, 0x20);
	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_NCOARSE, 0x13);
	msleep(3);
	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_I2CCFG, 0x08);

	चयन (पूर्णांकp->clkmode) अणु
	हाल 0:
	हाल 2:
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_SYNTCTRL, 0x20
				| पूर्णांकp->clkmode);
		अवरोध;
	शेष:
		/* preserve SELOSCI bit */
		i = 0x02 & stv0900_पढ़ो_reg(पूर्णांकp, R0900_SYNTCTRL);
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_SYNTCTRL, 0x20 | i);
		अवरोध;
	पूर्ण

	msleep(3);
	क्रम (i = 0; i < 181; i++)
		stv0900_ग_लिखो_reg(पूर्णांकp, STV0900_InitVal[i][0],
				STV0900_InitVal[i][1]);

	अगर (stv0900_पढ़ो_reg(पूर्णांकp, R0900_MID) >= 0x20) अणु
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_TSGENERAL, 0x0c);
		क्रम (i = 0; i < 32; i++)
			stv0900_ग_लिखो_reg(पूर्णांकp, STV0900_Cut20_AddOnVal[i][0],
					STV0900_Cut20_AddOnVal[i][1]);
	पूर्ण

	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_FSPYCFG, 0x6c);
	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_FSPYCFG, 0x6c);

	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_PDELCTRL2, 0x01);
	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_PDELCTRL2, 0x21);

	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_PDELCTRL3, 0x20);
	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_PDELCTRL3, 0x20);

	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_TSTRES0, 0x80);
	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_TSTRES0, 0x00);

	वापस STV0900_NO_ERROR;
पूर्ण

अटल u32 stv0900_get_mclk_freq(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp, u32 ext_clk)
अणु
	u32 mclk, भाग, ad_भाग;

	भाग = stv0900_get_bits(पूर्णांकp, F0900_M_DIV);
	ad_भाग = ((stv0900_get_bits(पूर्णांकp, F0900_SELX1RATIO) == 1) ? 4 : 6);

	mclk = (भाग + 1) * ext_clk / ad_भाग;

	dprपूर्णांकk("%s: Calculated Mclk = %d\n", __func__, mclk);

	वापस mclk;
पूर्ण

अटल क्रमागत fe_stv0900_error stv0900_set_mclk(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp, u32 mclk)
अणु
	u32 m_भाग, clk_sel;

	अगर (पूर्णांकp == शून्य)
		वापस STV0900_INVALID_HANDLE;

	अगर (पूर्णांकp->errs)
		वापस STV0900_I2C_ERROR;

	dprपूर्णांकk("%s: Mclk set to %d, Quartz = %d\n", __func__, mclk,
			पूर्णांकp->quartz);

	clk_sel = ((stv0900_get_bits(पूर्णांकp, F0900_SELX1RATIO) == 1) ? 4 : 6);
	m_भाग = ((clk_sel * mclk) / पूर्णांकp->quartz) - 1;
	stv0900_ग_लिखो_bits(पूर्णांकp, F0900_M_DIV, m_भाग);
	पूर्णांकp->mclk = stv0900_get_mclk_freq(पूर्णांकp,
					पूर्णांकp->quartz);

	/*Set the DiseqC frequency to 22KHz */
	/*
		Formula:
		DiseqC_TX_Freq= MasterClock/(32*F22TX_Reg)
		DiseqC_RX_Freq= MasterClock/(32*F22RX_Reg)
	*/
	m_भाग = पूर्णांकp->mclk / 704000;
	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_F22TX, m_भाग);
	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_F22RX, m_भाग);

	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_F22TX, m_भाग);
	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_F22RX, m_भाग);

	अगर ((पूर्णांकp->errs))
		वापस STV0900_I2C_ERROR;

	वापस STV0900_NO_ERROR;
पूर्ण

अटल u32 stv0900_get_err_count(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp, पूर्णांक cntr,
					क्रमागत fe_stv0900_demod_num demod)
अणु
	u32 lsb, msb, hsb, err_val;

	चयन (cntr) अणु
	हाल 0:
	शेष:
		hsb = stv0900_get_bits(पूर्णांकp, ERR_CNT12);
		msb = stv0900_get_bits(पूर्णांकp, ERR_CNT11);
		lsb = stv0900_get_bits(पूर्णांकp, ERR_CNT10);
		अवरोध;
	हाल 1:
		hsb = stv0900_get_bits(पूर्णांकp, ERR_CNT22);
		msb = stv0900_get_bits(पूर्णांकp, ERR_CNT21);
		lsb = stv0900_get_bits(पूर्णांकp, ERR_CNT20);
		अवरोध;
	पूर्ण

	err_val = (hsb << 16) + (msb << 8) + (lsb);

	वापस err_val;
पूर्ण

अटल पूर्णांक stv0900_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;

	stv0900_ग_लिखो_bits(पूर्णांकp, I2CT_ON, enable);

	वापस 0;
पूर्ण

अटल व्योम stv0900_set_ts_parallel_serial(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					क्रमागत fe_stv0900_घड़ी_प्रकारype path1_ts,
					क्रमागत fe_stv0900_घड़ी_प्रकारype path2_ts)
अणु

	dprपूर्णांकk("%s\n", __func__);

	अगर (पूर्णांकp->chip_id >= 0x20) अणु
		चयन (path1_ts) अणु
		हाल STV0900_PARALLEL_PUNCT_CLOCK:
		हाल STV0900_DVBCI_CLOCK:
			चयन (path2_ts) अणु
			हाल STV0900_SERIAL_PUNCT_CLOCK:
			हाल STV0900_SERIAL_CONT_CLOCK:
			शेष:
				stv0900_ग_लिखो_reg(पूर्णांकp, R0900_TSGENERAL,
							0x00);
				अवरोध;
			हाल STV0900_PARALLEL_PUNCT_CLOCK:
			हाल STV0900_DVBCI_CLOCK:
				stv0900_ग_लिखो_reg(पूर्णांकp, R0900_TSGENERAL,
							0x06);
				stv0900_ग_लिखो_bits(पूर्णांकp,
						F0900_P1_TSFIFO_MANSPEED, 3);
				stv0900_ग_लिखो_bits(पूर्णांकp,
						F0900_P2_TSFIFO_MANSPEED, 0);
				stv0900_ग_लिखो_reg(पूर्णांकp,
						R0900_P1_TSSPEED, 0x14);
				stv0900_ग_लिखो_reg(पूर्णांकp,
						R0900_P2_TSSPEED, 0x28);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल STV0900_SERIAL_PUNCT_CLOCK:
		हाल STV0900_SERIAL_CONT_CLOCK:
		शेष:
			चयन (path2_ts) अणु
			हाल STV0900_SERIAL_PUNCT_CLOCK:
			हाल STV0900_SERIAL_CONT_CLOCK:
			शेष:
				stv0900_ग_लिखो_reg(पूर्णांकp,
						R0900_TSGENERAL, 0x0C);
				अवरोध;
			हाल STV0900_PARALLEL_PUNCT_CLOCK:
			हाल STV0900_DVBCI_CLOCK:
				stv0900_ग_लिखो_reg(पूर्णांकp,
						R0900_TSGENERAL, 0x0A);
				dprपूर्णांकk("%s: 0x0a\n", __func__);
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (path1_ts) अणु
		हाल STV0900_PARALLEL_PUNCT_CLOCK:
		हाल STV0900_DVBCI_CLOCK:
			चयन (path2_ts) अणु
			हाल STV0900_SERIAL_PUNCT_CLOCK:
			हाल STV0900_SERIAL_CONT_CLOCK:
			शेष:
				stv0900_ग_लिखो_reg(पूर्णांकp, R0900_TSGENERAL1X,
							0x10);
				अवरोध;
			हाल STV0900_PARALLEL_PUNCT_CLOCK:
			हाल STV0900_DVBCI_CLOCK:
				stv0900_ग_लिखो_reg(पूर्णांकp, R0900_TSGENERAL1X,
							0x16);
				stv0900_ग_लिखो_bits(पूर्णांकp,
						F0900_P1_TSFIFO_MANSPEED, 3);
				stv0900_ग_लिखो_bits(पूर्णांकp,
						F0900_P2_TSFIFO_MANSPEED, 0);
				stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_TSSPEED,
							0x14);
				stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_TSSPEED,
							0x28);
				अवरोध;
			पूर्ण

			अवरोध;
		हाल STV0900_SERIAL_PUNCT_CLOCK:
		हाल STV0900_SERIAL_CONT_CLOCK:
		शेष:
			चयन (path2_ts) अणु
			हाल STV0900_SERIAL_PUNCT_CLOCK:
			हाल STV0900_SERIAL_CONT_CLOCK:
			शेष:
				stv0900_ग_लिखो_reg(पूर्णांकp, R0900_TSGENERAL1X,
							0x14);
				अवरोध;
			हाल STV0900_PARALLEL_PUNCT_CLOCK:
			हाल STV0900_DVBCI_CLOCK:
				stv0900_ग_लिखो_reg(पूर्णांकp, R0900_TSGENERAL1X,
							0x12);
				dprपूर्णांकk("%s: 0x12\n", __func__);
				अवरोध;
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण

	चयन (path1_ts) अणु
	हाल STV0900_PARALLEL_PUNCT_CLOCK:
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_TSFIFO_SERIAL, 0x00);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_TSFIFO_DVBCI, 0x00);
		अवरोध;
	हाल STV0900_DVBCI_CLOCK:
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_TSFIFO_SERIAL, 0x00);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_TSFIFO_DVBCI, 0x01);
		अवरोध;
	हाल STV0900_SERIAL_PUNCT_CLOCK:
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_TSFIFO_SERIAL, 0x01);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_TSFIFO_DVBCI, 0x00);
		अवरोध;
	हाल STV0900_SERIAL_CONT_CLOCK:
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_TSFIFO_SERIAL, 0x01);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_TSFIFO_DVBCI, 0x01);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (path2_ts) अणु
	हाल STV0900_PARALLEL_PUNCT_CLOCK:
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_TSFIFO_SERIAL, 0x00);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_TSFIFO_DVBCI, 0x00);
		अवरोध;
	हाल STV0900_DVBCI_CLOCK:
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_TSFIFO_SERIAL, 0x00);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_TSFIFO_DVBCI, 0x01);
		अवरोध;
	हाल STV0900_SERIAL_PUNCT_CLOCK:
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_TSFIFO_SERIAL, 0x01);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_TSFIFO_DVBCI, 0x00);
		अवरोध;
	हाल STV0900_SERIAL_CONT_CLOCK:
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_TSFIFO_SERIAL, 0x01);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_TSFIFO_DVBCI, 0x01);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_RST_HWARE, 1);
	stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_RST_HWARE, 0);
	stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_RST_HWARE, 1);
	stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_RST_HWARE, 0);
पूर्ण

व्योम stv0900_set_tuner(काष्ठा dvb_frontend *fe, u32 frequency,
							u32 bandwidth)
अणु
	काष्ठा dvb_frontend_ops *frontend_ops = शून्य;
	काष्ठा dvb_tuner_ops *tuner_ops = शून्य;

	frontend_ops = &fe->ops;
	tuner_ops = &frontend_ops->tuner_ops;

	अगर (tuner_ops->set_frequency) अणु
		अगर ((tuner_ops->set_frequency(fe, frequency)) < 0)
			dprपूर्णांकk("%s: Invalid parameter\n", __func__);
		अन्यथा
			dprपूर्णांकk("%s: Frequency=%d\n", __func__, frequency);

	पूर्ण

	अगर (tuner_ops->set_bandwidth) अणु
		अगर ((tuner_ops->set_bandwidth(fe, bandwidth)) < 0)
			dprपूर्णांकk("%s: Invalid parameter\n", __func__);
		अन्यथा
			dprपूर्णांकk("%s: Bandwidth=%d\n", __func__, bandwidth);

	पूर्ण
पूर्ण

व्योम stv0900_set_bandwidth(काष्ठा dvb_frontend *fe, u32 bandwidth)
अणु
	काष्ठा dvb_frontend_ops *frontend_ops = शून्य;
	काष्ठा dvb_tuner_ops *tuner_ops = शून्य;

	frontend_ops = &fe->ops;
	tuner_ops = &frontend_ops->tuner_ops;

	अगर (tuner_ops->set_bandwidth) अणु
		अगर ((tuner_ops->set_bandwidth(fe, bandwidth)) < 0)
			dprपूर्णांकk("%s: Invalid parameter\n", __func__);
		अन्यथा
			dprपूर्णांकk("%s: Bandwidth=%d\n", __func__, bandwidth);

	पूर्ण
पूर्ण

u32 stv0900_get_freq_स्वतः(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp, पूर्णांक demod)
अणु
	u32 freq, round;
	/*	Formulat :
	Tuner_Frequency(MHz)	= Regs / 64
	Tuner_granularity(MHz)	= Regs / 2048
	real_Tuner_Frequency	= Tuner_Frequency(MHz) - Tuner_granularity(MHz)
	*/
	freq = (stv0900_get_bits(पूर्णांकp, TUN_RFFREQ2) << 10) +
		(stv0900_get_bits(पूर्णांकp, TUN_RFFREQ1) << 2) +
		stv0900_get_bits(पूर्णांकp, TUN_RFFREQ0);

	freq = (freq * 1000) / 64;

	round = (stv0900_get_bits(पूर्णांकp, TUN_RFRESTE1) >> 2) +
		stv0900_get_bits(पूर्णांकp, TUN_RFRESTE0);

	round = (round * 1000) / 2048;

	वापस freq + round;
पूर्ण

व्योम stv0900_set_tuner_स्वतः(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp, u32 Frequency,
						u32 Bandwidth, पूर्णांक demod)
अणु
	u32 tunerFrequency;
	/* Formulat:
	Tuner_frequency_reg= Frequency(MHz)*64
	*/
	tunerFrequency = (Frequency * 64) / 1000;

	stv0900_ग_लिखो_bits(पूर्णांकp, TUN_RFFREQ2, (tunerFrequency >> 10));
	stv0900_ग_लिखो_bits(पूर्णांकp, TUN_RFFREQ1, (tunerFrequency >> 2) & 0xff);
	stv0900_ग_लिखो_bits(पूर्णांकp, TUN_RFFREQ0, (tunerFrequency & 0x03));
	/* Low Pass Filter = BW /2 (MHz)*/
	stv0900_ग_लिखो_bits(पूर्णांकp, TUN_BW, Bandwidth / 2000000);
	/* Tuner Write trig */
	stv0900_ग_लिखो_reg(पूर्णांकp, TNRLD, 1);
पूर्ण

अटल s32 stv0900_get_rf_level(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
				स्थिर काष्ठा stv0900_table *lookup,
				क्रमागत fe_stv0900_demod_num demod)
अणु
	s32 agc_gain = 0,
		imin,
		imax,
		i,
		rf_lvl = 0;

	dprपूर्णांकk("%s\n", __func__);

	अगर ((lookup == शून्य) || (lookup->size <= 0))
		वापस 0;

	agc_gain = MAKEWORD(stv0900_get_bits(पूर्णांकp, AGCIQ_VALUE1),
				stv0900_get_bits(पूर्णांकp, AGCIQ_VALUE0));

	imin = 0;
	imax = lookup->size - 1;
	अगर (INRANGE(lookup->table[imin].regval, agc_gain,
					lookup->table[imax].regval)) अणु
		जबतक ((imax - imin) > 1) अणु
			i = (imax + imin) >> 1;

			अगर (INRANGE(lookup->table[imin].regval,
					agc_gain,
					lookup->table[i].regval))
				imax = i;
			अन्यथा
				imin = i;
		पूर्ण

		rf_lvl = (s32)agc_gain - lookup->table[imin].regval;
		rf_lvl *= (lookup->table[imax].realval -
				lookup->table[imin].realval);
		rf_lvl /= (lookup->table[imax].regval -
				lookup->table[imin].regval);
		rf_lvl += lookup->table[imin].realval;
	पूर्ण अन्यथा अगर (agc_gain > lookup->table[0].regval)
		rf_lvl = 5;
	अन्यथा अगर (agc_gain < lookup->table[lookup->size-1].regval)
		rf_lvl = -100;

	dprपूर्णांकk("%s: RFLevel = %d\n", __func__, rf_lvl);

	वापस rf_lvl;
पूर्ण

अटल पूर्णांक stv0900_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकernal = state->पूर्णांकernal;
	s32 rflevel = stv0900_get_rf_level(पूर्णांकernal, &stv0900_rf,
								state->demod);

	rflevel = (rflevel + 100) * (65535 / 70);
	अगर (rflevel < 0)
		rflevel = 0;

	अगर (rflevel > 65535)
		rflevel = 65535;

	*strength = rflevel;

	वापस 0;
पूर्ण

अटल s32 stv0900_carr_get_quality(काष्ठा dvb_frontend *fe,
					स्थिर काष्ठा stv0900_table *lookup)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;

	s32	c_n = -100,
		regval,
		imin,
		imax,
		i,
		noise_field1,
		noise_field0;

	dprपूर्णांकk("%s\n", __func__);

	अगर (stv0900_get_standard(fe, demod) == STV0900_DVBS2_STANDARD) अणु
		noise_field1 = NOSPLHT_NORMED1;
		noise_field0 = NOSPLHT_NORMED0;
	पूर्ण अन्यथा अणु
		noise_field1 = NOSDATAT_NORMED1;
		noise_field0 = NOSDATAT_NORMED0;
	पूर्ण

	अगर (stv0900_get_bits(पूर्णांकp, LOCK_DEFINITIF)) अणु
		अगर ((lookup != शून्य) && lookup->size) अणु
			regval = 0;
			msleep(5);
			क्रम (i = 0; i < 16; i++) अणु
				regval += MAKEWORD(stv0900_get_bits(पूर्णांकp,
								noise_field1),
						stv0900_get_bits(पूर्णांकp,
								noise_field0));
				msleep(1);
			पूर्ण

			regval /= 16;
			imin = 0;
			imax = lookup->size - 1;
			अगर (INRANGE(lookup->table[imin].regval,
					regval,
					lookup->table[imax].regval)) अणु
				जबतक ((imax - imin) > 1) अणु
					i = (imax + imin) >> 1;
					अगर (INRANGE(lookup->table[imin].regval,
						    regval,
						    lookup->table[i].regval))
						imax = i;
					अन्यथा
						imin = i;
				पूर्ण

				c_n = ((regval - lookup->table[imin].regval)
						* (lookup->table[imax].realval
						- lookup->table[imin].realval)
						/ (lookup->table[imax].regval
						- lookup->table[imin].regval))
						+ lookup->table[imin].realval;
			पूर्ण अन्यथा अगर (regval < lookup->table[imin].regval)
				c_n = 1000;
		पूर्ण
	पूर्ण

	वापस c_n;
पूर्ण

अटल पूर्णांक stv0900_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 * ucblocks)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;
	u8 err_val1, err_val0;
	u32 header_err_val = 0;

	*ucblocks = 0x0;
	अगर (stv0900_get_standard(fe, demod) == STV0900_DVBS2_STANDARD) अणु
		/* DVB-S2 delineator errors count */

		/* retrieving number क्रम त्रुटि_संus headers */
		err_val1 = stv0900_पढ़ो_reg(पूर्णांकp, BBFCRCKO1);
		err_val0 = stv0900_पढ़ो_reg(पूर्णांकp, BBFCRCKO0);
		header_err_val = (err_val1 << 8) | err_val0;

		/* retrieving number क्रम त्रुटि_संus packets */
		err_val1 = stv0900_पढ़ो_reg(पूर्णांकp, UPCRCKO1);
		err_val0 = stv0900_पढ़ो_reg(पूर्णांकp, UPCRCKO0);
		*ucblocks = (err_val1 << 8) | err_val0;
		*ucblocks += header_err_val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0900_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	s32 snrlcl = stv0900_carr_get_quality(fe,
			(स्थिर काष्ठा stv0900_table *)&stv0900_s2_cn);
	snrlcl = (snrlcl + 30) * 384;
	अगर (snrlcl < 0)
		snrlcl = 0;

	अगर (snrlcl > 65535)
		snrlcl = 65535;

	*snr = snrlcl;

	वापस 0;
पूर्ण

अटल u32 stv0900_get_ber(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
				क्रमागत fe_stv0900_demod_num demod)
अणु
	u32 ber = 10000000, i;
	s32 demod_state;

	demod_state = stv0900_get_bits(पूर्णांकp, HEADER_MODE);

	चयन (demod_state) अणु
	हाल STV0900_SEARCH:
	हाल STV0900_PLH_DETECTED:
	शेष:
		ber = 10000000;
		अवरोध;
	हाल STV0900_DVBS_FOUND:
		ber = 0;
		क्रम (i = 0; i < 5; i++) अणु
			msleep(5);
			ber += stv0900_get_err_count(पूर्णांकp, 0, demod);
		पूर्ण

		ber /= 5;
		अगर (stv0900_get_bits(पूर्णांकp, PRFVIT)) अणु
			ber *= 9766;
			ber = ber >> 13;
		पूर्ण

		अवरोध;
	हाल STV0900_DVBS2_FOUND:
		ber = 0;
		क्रम (i = 0; i < 5; i++) अणु
			msleep(5);
			ber += stv0900_get_err_count(पूर्णांकp, 0, demod);
		पूर्ण

		ber /= 5;
		अगर (stv0900_get_bits(पूर्णांकp, PKTDELIN_LOCK)) अणु
			ber *= 9766;
			ber = ber >> 13;
		पूर्ण

		अवरोध;
	पूर्ण

	वापस ber;
पूर्ण

अटल पूर्णांक stv0900_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकernal = state->पूर्णांकernal;

	*ber = stv0900_get_ber(पूर्णांकernal, state->demod);

	वापस 0;
पूर्ण

पूर्णांक stv0900_get_demod_lock(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
			क्रमागत fe_stv0900_demod_num demod, s32 समय_out)
अणु
	s32 समयr = 0,
		lock = 0;

	क्रमागत fe_stv0900_search_state	dmd_state;

	जबतक ((समयr < समय_out) && (lock == 0)) अणु
		dmd_state = stv0900_get_bits(पूर्णांकp, HEADER_MODE);
		dprपूर्णांकk("Demod State = %d\n", dmd_state);
		चयन (dmd_state) अणु
		हाल STV0900_SEARCH:
		हाल STV0900_PLH_DETECTED:
		शेष:
			lock = 0;
			अवरोध;
		हाल STV0900_DVBS2_FOUND:
		हाल STV0900_DVBS_FOUND:
			lock = stv0900_get_bits(पूर्णांकp, LOCK_DEFINITIF);
			अवरोध;
		पूर्ण

		अगर (lock == 0)
			msleep(10);

		समयr += 10;
	पूर्ण

	अगर (lock)
		dprपूर्णांकk("DEMOD LOCK OK\n");
	अन्यथा
		dprपूर्णांकk("DEMOD LOCK FAIL\n");

	वापस lock;
पूर्ण

व्योम stv0900_stop_all_s2_modcod(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
				क्रमागत fe_stv0900_demod_num demod)
अणु
	s32 regflist,
	i;

	dprपूर्णांकk("%s\n", __func__);

	regflist = MODCODLST0;

	क्रम (i = 0; i < 16; i++)
		stv0900_ग_लिखो_reg(पूर्णांकp, regflist + i, 0xff);
पूर्ण

व्योम stv0900_activate_s2_modcod(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
				क्रमागत fe_stv0900_demod_num demod)
अणु
	u32 matype,
		mod_code,
		भ_शेष,
		reg_index,
		field_index;

	dprपूर्णांकk("%s\n", __func__);

	अगर (पूर्णांकp->chip_id <= 0x11) अणु
		msleep(5);

		mod_code = stv0900_पढ़ो_reg(पूर्णांकp, PLHMODCOD);
		matype = mod_code & 0x3;
		mod_code = (mod_code & 0x7f) >> 2;

		reg_index = MODCODLSTF - mod_code / 2;
		field_index = mod_code % 2;

		चयन (matype) अणु
		हाल 0:
		शेष:
			भ_शेष = 14;
			अवरोध;
		हाल 1:
			भ_शेष = 13;
			अवरोध;
		हाल 2:
			भ_शेष = 11;
			अवरोध;
		हाल 3:
			भ_शेष = 7;
			अवरोध;
		पूर्ण

		अगर ((INRANGE(STV0900_QPSK_12, mod_code, STV0900_8PSK_910))
						&& (matype <= 1)) अणु
			अगर (field_index == 0)
				stv0900_ग_लिखो_reg(पूर्णांकp, reg_index,
							0xf0 | भ_शेष);
			अन्यथा
				stv0900_ग_लिखो_reg(पूर्णांकp, reg_index,
							(भ_शेष << 4) | 0xf);
		पूर्ण

	पूर्ण अन्यथा अगर (पूर्णांकp->chip_id >= 0x12) अणु
		क्रम (reg_index = 0; reg_index < 7; reg_index++)
			stv0900_ग_लिखो_reg(पूर्णांकp, MODCODLST0 + reg_index, 0xff);

		stv0900_ग_लिखो_reg(पूर्णांकp, MODCODLSTE, 0xff);
		stv0900_ग_लिखो_reg(पूर्णांकp, MODCODLSTF, 0xcf);
		क्रम (reg_index = 0; reg_index < 8; reg_index++)
			stv0900_ग_लिखो_reg(पूर्णांकp, MODCODLST7 + reg_index, 0xcc);


	पूर्ण
पूर्ण

व्योम stv0900_activate_s2_modcod_single(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					क्रमागत fe_stv0900_demod_num demod)
अणु
	u32 reg_index;

	dprपूर्णांकk("%s\n", __func__);

	stv0900_ग_लिखो_reg(पूर्णांकp, MODCODLST0, 0xff);
	stv0900_ग_लिखो_reg(पूर्णांकp, MODCODLST1, 0xf0);
	stv0900_ग_लिखो_reg(पूर्णांकp, MODCODLSTF, 0x0f);
	क्रम (reg_index = 0; reg_index < 13; reg_index++)
		stv0900_ग_लिखो_reg(पूर्णांकp, MODCODLST2 + reg_index, 0);

पूर्ण

अटल क्रमागत dvbfe_algo stv0900_frontend_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस DVBFE_ALGO_CUSTOM;
पूर्ण

व्योम stv0900_start_search(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
				क्रमागत fe_stv0900_demod_num demod)
अणु
	u32 freq;
	s16 freq_s16 ;

	stv0900_ग_लिखो_bits(पूर्णांकp, DEMOD_MODE, 0x1f);
	अगर (पूर्णांकp->chip_id == 0x10)
		stv0900_ग_लिखो_reg(पूर्णांकp, CORRELEXP, 0xaa);

	अगर (पूर्णांकp->chip_id < 0x20)
		stv0900_ग_लिखो_reg(पूर्णांकp, CARHDR, 0x55);

	अगर (पूर्णांकp->chip_id <= 0x20) अणु
		अगर (पूर्णांकp->symbol_rate[0] <= 5000000) अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, CARCFG, 0x44);
			stv0900_ग_लिखो_reg(पूर्णांकp, CFRUP1, 0x0f);
			stv0900_ग_लिखो_reg(पूर्णांकp, CFRUP0, 0xff);
			stv0900_ग_लिखो_reg(पूर्णांकp, CFRLOW1, 0xf0);
			stv0900_ग_लिखो_reg(पूर्णांकp, CFRLOW0, 0x00);
			stv0900_ग_लिखो_reg(पूर्णांकp, RTCS2, 0x68);
		पूर्ण अन्यथा अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, CARCFG, 0xc4);
			stv0900_ग_लिखो_reg(पूर्णांकp, RTCS2, 0x44);
		पूर्ण

	पूर्ण अन्यथा अणु /*cut 3.0 above*/
		अगर (पूर्णांकp->symbol_rate[demod] <= 5000000)
			stv0900_ग_लिखो_reg(पूर्णांकp, RTCS2, 0x68);
		अन्यथा
			stv0900_ग_लिखो_reg(पूर्णांकp, RTCS2, 0x44);

		stv0900_ग_लिखो_reg(पूर्णांकp, CARCFG, 0x46);
		अगर (पूर्णांकp->srch_algo[demod] == STV0900_WARM_START) अणु
			freq = 1000 << 16;
			freq /= (पूर्णांकp->mclk / 1000);
			freq_s16 = (s16)freq;
		पूर्ण अन्यथा अणु
			freq = (पूर्णांकp->srch_range[demod] / 2000);
			अगर (पूर्णांकp->symbol_rate[demod] <= 5000000)
				freq += 80;
			अन्यथा
				freq += 600;

			freq = freq << 16;
			freq /= (पूर्णांकp->mclk / 1000);
			freq_s16 = (s16)freq;
		पूर्ण

		stv0900_ग_लिखो_bits(पूर्णांकp, CFR_UP1, MSB(freq_s16));
		stv0900_ग_लिखो_bits(पूर्णांकp, CFR_UP0, LSB(freq_s16));
		freq_s16 *= (-1);
		stv0900_ग_लिखो_bits(पूर्णांकp, CFR_LOW1, MSB(freq_s16));
		stv0900_ग_लिखो_bits(पूर्णांकp, CFR_LOW0, LSB(freq_s16));
	पूर्ण

	stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT1, 0);
	stv0900_ग_लिखो_reg(पूर्णांकp, CFRINIT0, 0);

	अगर (पूर्णांकp->chip_id >= 0x20) अणु
		stv0900_ग_लिखो_reg(पूर्णांकp, EQUALCFG, 0x41);
		stv0900_ग_लिखो_reg(पूर्णांकp, FFECFG, 0x41);

		अगर ((पूर्णांकp->srch_standard[demod] == STV0900_SEARCH_DVBS1) ||
			(पूर्णांकp->srch_standard[demod] == STV0900_SEARCH_DSS) ||
			(पूर्णांकp->srch_standard[demod] == STV0900_AUTO_SEARCH)) अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, VITSCALE,
								0x82);
			stv0900_ग_लिखो_reg(पूर्णांकp, VAVSRVIT, 0x0);
		पूर्ण
	पूर्ण

	stv0900_ग_लिखो_reg(पूर्णांकp, SFRSTEP, 0x00);
	stv0900_ग_लिखो_reg(पूर्णांकp, TMGTHRISE, 0xe0);
	stv0900_ग_लिखो_reg(पूर्णांकp, TMGTHFALL, 0xc0);
	stv0900_ग_लिखो_bits(पूर्णांकp, SCAN_ENABLE, 0);
	stv0900_ग_लिखो_bits(पूर्णांकp, CFR_AUTOSCAN, 0);
	stv0900_ग_लिखो_bits(पूर्णांकp, S1S2_SEQUENTIAL, 0);
	stv0900_ग_लिखो_reg(पूर्णांकp, RTC, 0x88);
	अगर (पूर्णांकp->chip_id >= 0x20) अणु
		अगर (पूर्णांकp->symbol_rate[demod] < 2000000) अणु
			अगर (पूर्णांकp->chip_id <= 0x20)
				stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0x39);
			अन्यथा  /*cut 3.0*/
				stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0x89);

			stv0900_ग_लिखो_reg(पूर्णांकp, CARHDR, 0x40);
		पूर्ण अन्यथा अगर (पूर्णांकp->symbol_rate[demod] < 10000000) अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0x4c);
			stv0900_ग_लिखो_reg(पूर्णांकp, CARHDR, 0x20);
		पूर्ण अन्यथा अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0x4b);
			stv0900_ग_लिखो_reg(पूर्णांकp, CARHDR, 0x20);
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर (पूर्णांकp->symbol_rate[demod] < 10000000)
			stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0xef);
		अन्यथा
			stv0900_ग_लिखो_reg(पूर्णांकp, CARFREQ, 0xed);
	पूर्ण

	चयन (पूर्णांकp->srch_algo[demod]) अणु
	हाल STV0900_WARM_START:
		stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x1f);
		stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x18);
		अवरोध;
	हाल STV0900_COLD_START:
		stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x1f);
		stv0900_ग_लिखो_reg(पूर्णांकp, DMDISTATE, 0x15);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

u8 stv0900_get_optim_carr_loop(s32 srate, क्रमागत fe_stv0900_modcode modcode,
							s32 pilot, u8 chip_id)
अणु
	u8 aclc_value = 0x29;
	s32 i, cllas2_size;
	स्थिर काष्ठा stv0900_car_loop_optim *cls2, *cllqs2, *cllas2;

	dprपूर्णांकk("%s\n", __func__);

	अगर (chip_id <= 0x12) अणु
		cls2 = FE_STV0900_S2CarLoop;
		cllqs2 = FE_STV0900_S2LowQPCarLoopCut30;
		cllas2 = FE_STV0900_S2APSKCarLoopCut30;
		cllas2_size = ARRAY_SIZE(FE_STV0900_S2APSKCarLoopCut30);
	पूर्ण अन्यथा अगर (chip_id == 0x20) अणु
		cls2 = FE_STV0900_S2CarLoopCut20;
		cllqs2 = FE_STV0900_S2LowQPCarLoopCut20;
		cllas2 = FE_STV0900_S2APSKCarLoopCut20;
		cllas2_size = ARRAY_SIZE(FE_STV0900_S2APSKCarLoopCut20);
	पूर्ण अन्यथा अणु
		cls2 = FE_STV0900_S2CarLoopCut30;
		cllqs2 = FE_STV0900_S2LowQPCarLoopCut30;
		cllas2 = FE_STV0900_S2APSKCarLoopCut30;
		cllas2_size = ARRAY_SIZE(FE_STV0900_S2APSKCarLoopCut30);
	पूर्ण

	अगर (modcode < STV0900_QPSK_12) अणु
		i = 0;
		जबतक ((i < 3) && (modcode != cllqs2[i].modcode))
			i++;

		अगर (i >= 3)
			i = 2;
	पूर्ण अन्यथा अणु
		i = 0;
		जबतक ((i < 14) && (modcode != cls2[i].modcode))
			i++;

		अगर (i >= 14) अणु
			i = 0;
			जबतक ((i < 11) && (modcode != cllas2[i].modcode))
				i++;

			अगर (i >= 11)
				i = 10;
		पूर्ण
	पूर्ण

	अगर (modcode <= STV0900_QPSK_25) अणु
		अगर (pilot) अणु
			अगर (srate <= 3000000)
				aclc_value = cllqs2[i].car_loop_pilots_on_2;
			अन्यथा अगर (srate <= 7000000)
				aclc_value = cllqs2[i].car_loop_pilots_on_5;
			अन्यथा अगर (srate <= 15000000)
				aclc_value = cllqs2[i].car_loop_pilots_on_10;
			अन्यथा अगर (srate <= 25000000)
				aclc_value = cllqs2[i].car_loop_pilots_on_20;
			अन्यथा
				aclc_value = cllqs2[i].car_loop_pilots_on_30;
		पूर्ण अन्यथा अणु
			अगर (srate <= 3000000)
				aclc_value = cllqs2[i].car_loop_pilots_off_2;
			अन्यथा अगर (srate <= 7000000)
				aclc_value = cllqs2[i].car_loop_pilots_off_5;
			अन्यथा अगर (srate <= 15000000)
				aclc_value = cllqs2[i].car_loop_pilots_off_10;
			अन्यथा अगर (srate <= 25000000)
				aclc_value = cllqs2[i].car_loop_pilots_off_20;
			अन्यथा
				aclc_value = cllqs2[i].car_loop_pilots_off_30;
		पूर्ण

	पूर्ण अन्यथा अगर (modcode <= STV0900_8PSK_910) अणु
		अगर (pilot) अणु
			अगर (srate <= 3000000)
				aclc_value = cls2[i].car_loop_pilots_on_2;
			अन्यथा अगर (srate <= 7000000)
				aclc_value = cls2[i].car_loop_pilots_on_5;
			अन्यथा अगर (srate <= 15000000)
				aclc_value = cls2[i].car_loop_pilots_on_10;
			अन्यथा अगर (srate <= 25000000)
				aclc_value = cls2[i].car_loop_pilots_on_20;
			अन्यथा
				aclc_value = cls2[i].car_loop_pilots_on_30;
		पूर्ण अन्यथा अणु
			अगर (srate <= 3000000)
				aclc_value = cls2[i].car_loop_pilots_off_2;
			अन्यथा अगर (srate <= 7000000)
				aclc_value = cls2[i].car_loop_pilots_off_5;
			अन्यथा अगर (srate <= 15000000)
				aclc_value = cls2[i].car_loop_pilots_off_10;
			अन्यथा अगर (srate <= 25000000)
				aclc_value = cls2[i].car_loop_pilots_off_20;
			अन्यथा
				aclc_value = cls2[i].car_loop_pilots_off_30;
		पूर्ण

	पूर्ण अन्यथा अगर (i < cllas2_size) अणु
		अगर (srate <= 3000000)
			aclc_value = cllas2[i].car_loop_pilots_on_2;
		अन्यथा अगर (srate <= 7000000)
			aclc_value = cllas2[i].car_loop_pilots_on_5;
		अन्यथा अगर (srate <= 15000000)
			aclc_value = cllas2[i].car_loop_pilots_on_10;
		अन्यथा अगर (srate <= 25000000)
			aclc_value = cllas2[i].car_loop_pilots_on_20;
		अन्यथा
			aclc_value = cllas2[i].car_loop_pilots_on_30;
	पूर्ण

	वापस aclc_value;
पूर्ण

u8 stv0900_get_optim_लघु_carr_loop(s32 srate,
				क्रमागत fe_stv0900_modulation modulation,
				u8 chip_id)
अणु
	स्थिर काष्ठा stv0900_लघु_frames_car_loop_optim *s2scl;
	स्थिर काष्ठा stv0900_लघु_frames_car_loop_optim_vs_mod *s2sclc30;
	s32 mod_index = 0;
	u8 aclc_value = 0x0b;

	dprपूर्णांकk("%s\n", __func__);

	s2scl = FE_STV0900_S2ShortCarLoop;
	s2sclc30 = FE_STV0900_S2ShortCarLoopCut30;

	चयन (modulation) अणु
	हाल STV0900_QPSK:
	शेष:
		mod_index = 0;
		अवरोध;
	हाल STV0900_8PSK:
		mod_index = 1;
		अवरोध;
	हाल STV0900_16APSK:
		mod_index = 2;
		अवरोध;
	हाल STV0900_32APSK:
		mod_index = 3;
		अवरोध;
	पूर्ण

	अगर (chip_id >= 0x30) अणु
		अगर (srate <= 3000000)
			aclc_value = s2sclc30[mod_index].car_loop_2;
		अन्यथा अगर (srate <= 7000000)
			aclc_value = s2sclc30[mod_index].car_loop_5;
		अन्यथा अगर (srate <= 15000000)
			aclc_value = s2sclc30[mod_index].car_loop_10;
		अन्यथा अगर (srate <= 25000000)
			aclc_value = s2sclc30[mod_index].car_loop_20;
		अन्यथा
			aclc_value = s2sclc30[mod_index].car_loop_30;

	पूर्ण अन्यथा अगर (chip_id >= 0x20) अणु
		अगर (srate <= 3000000)
			aclc_value = s2scl[mod_index].car_loop_cut20_2;
		अन्यथा अगर (srate <= 7000000)
			aclc_value = s2scl[mod_index].car_loop_cut20_5;
		अन्यथा अगर (srate <= 15000000)
			aclc_value = s2scl[mod_index].car_loop_cut20_10;
		अन्यथा अगर (srate <= 25000000)
			aclc_value = s2scl[mod_index].car_loop_cut20_20;
		अन्यथा
			aclc_value = s2scl[mod_index].car_loop_cut20_30;

	पूर्ण अन्यथा अणु
		अगर (srate <= 3000000)
			aclc_value = s2scl[mod_index].car_loop_cut12_2;
		अन्यथा अगर (srate <= 7000000)
			aclc_value = s2scl[mod_index].car_loop_cut12_5;
		अन्यथा अगर (srate <= 15000000)
			aclc_value = s2scl[mod_index].car_loop_cut12_10;
		अन्यथा अगर (srate <= 25000000)
			aclc_value = s2scl[mod_index].car_loop_cut12_20;
		अन्यथा
			aclc_value = s2scl[mod_index].car_loop_cut12_30;

	पूर्ण

	वापस aclc_value;
पूर्ण

अटल
क्रमागत fe_stv0900_error stv0900_st_dvbs2_single(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					क्रमागत fe_stv0900_demod_mode LDPC_Mode,
					क्रमागत fe_stv0900_demod_num demod)
अणु
	s32 reg_ind;

	dprपूर्णांकk("%s\n", __func__);

	चयन (LDPC_Mode) अणु
	हाल STV0900_DUAL:
	शेष:
		अगर ((पूर्णांकp->demod_mode != STV0900_DUAL)
			|| (stv0900_get_bits(पूर्णांकp, F0900_DDEMOD) != 1)) अणु
			stv0900_ग_लिखो_reg(पूर्णांकp, R0900_GENCFG, 0x1d);

			पूर्णांकp->demod_mode = STV0900_DUAL;

			stv0900_ग_लिखो_bits(पूर्णांकp, F0900_FRESFEC, 1);
			stv0900_ग_लिखो_bits(पूर्णांकp, F0900_FRESFEC, 0);

			क्रम (reg_ind = 0; reg_ind < 7; reg_ind++)
				stv0900_ग_लिखो_reg(पूर्णांकp,
						R0900_P1_MODCODLST0 + reg_ind,
						0xff);
			क्रम (reg_ind = 0; reg_ind < 8; reg_ind++)
				stv0900_ग_लिखो_reg(पूर्णांकp,
						R0900_P1_MODCODLST7 + reg_ind,
						0xcc);

			stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_MODCODLSTE, 0xff);
			stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_MODCODLSTF, 0xcf);

			क्रम (reg_ind = 0; reg_ind < 7; reg_ind++)
				stv0900_ग_लिखो_reg(पूर्णांकp,
						R0900_P2_MODCODLST0 + reg_ind,
						0xff);
			क्रम (reg_ind = 0; reg_ind < 8; reg_ind++)
				stv0900_ग_लिखो_reg(पूर्णांकp,
						R0900_P2_MODCODLST7 + reg_ind,
						0xcc);

			stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_MODCODLSTE, 0xff);
			stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_MODCODLSTF, 0xcf);
		पूर्ण

		अवरोध;
	हाल STV0900_SINGLE:
		अगर (demod == STV0900_DEMOD_2) अणु
			stv0900_stop_all_s2_modcod(पूर्णांकp, STV0900_DEMOD_1);
			stv0900_activate_s2_modcod_single(पूर्णांकp,
							STV0900_DEMOD_2);
			stv0900_ग_लिखो_reg(पूर्णांकp, R0900_GENCFG, 0x06);
		पूर्ण अन्यथा अणु
			stv0900_stop_all_s2_modcod(पूर्णांकp, STV0900_DEMOD_2);
			stv0900_activate_s2_modcod_single(पूर्णांकp,
							STV0900_DEMOD_1);
			stv0900_ग_लिखो_reg(पूर्णांकp, R0900_GENCFG, 0x04);
		पूर्ण

		पूर्णांकp->demod_mode = STV0900_SINGLE;

		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_FRESFEC, 1);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_FRESFEC, 0);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_ALGOSWRST, 1);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_ALGOSWRST, 0);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_ALGOSWRST, 1);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_ALGOSWRST, 0);
		अवरोध;
	पूर्ण

	वापस STV0900_NO_ERROR;
पूर्ण

अटल क्रमागत fe_stv0900_error stv0900_init_पूर्णांकernal(काष्ठा dvb_frontend *fe,
					काष्ठा stv0900_init_params *p_init)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	क्रमागत fe_stv0900_error error = STV0900_NO_ERROR;
	क्रमागत fe_stv0900_error demodError = STV0900_NO_ERROR;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = शून्य;
	पूर्णांक selosci, i;

	काष्ठा stv0900_inode *temp_पूर्णांक = find_inode(state->i2c_adap,
						state->config->demod_address);

	dprपूर्णांकk("%s\n", __func__);

	अगर ((temp_पूर्णांक != शून्य) && (p_init->demod_mode == STV0900_DUAL)) अणु
		state->पूर्णांकernal = temp_पूर्णांक->पूर्णांकernal;
		(state->पूर्णांकernal->dmds_used)++;
		dprपूर्णांकk("%s: Find Internal Structure!\n", __func__);
		वापस STV0900_NO_ERROR;
	पूर्ण अन्यथा अणु
		state->पूर्णांकernal = kदो_स्मृति(माप(काष्ठा stv0900_पूर्णांकernal),
								GFP_KERNEL);
		अगर (state->पूर्णांकernal == शून्य)
			वापस STV0900_INVALID_HANDLE;
		temp_पूर्णांक = append_पूर्णांकernal(state->पूर्णांकernal);
		अगर (temp_पूर्णांक == शून्य) अणु
			kमुक्त(state->पूर्णांकernal);
			state->पूर्णांकernal = शून्य;
			वापस STV0900_INVALID_HANDLE;
		पूर्ण
		state->पूर्णांकernal->dmds_used = 1;
		state->पूर्णांकernal->i2c_adap = state->i2c_adap;
		state->पूर्णांकernal->i2c_addr = state->config->demod_address;
		state->पूर्णांकernal->clkmode = state->config->clkmode;
		state->पूर्णांकernal->errs = STV0900_NO_ERROR;
		dprपूर्णांकk("%s: Create New Internal Structure!\n", __func__);
	पूर्ण

	अगर (state->पूर्णांकernal == शून्य) अणु
		error = STV0900_INVALID_HANDLE;
		वापस error;
	पूर्ण

	demodError = stv0900_initialize(state->पूर्णांकernal);
	अगर (demodError == STV0900_NO_ERROR) अणु
			error = STV0900_NO_ERROR;
	पूर्ण अन्यथा अणु
		अगर (demodError == STV0900_INVALID_HANDLE)
			error = STV0900_INVALID_HANDLE;
		अन्यथा
			error = STV0900_I2C_ERROR;

		वापस error;
	पूर्ण

	पूर्णांकp = state->पूर्णांकernal;

	पूर्णांकp->demod_mode = p_init->demod_mode;
	stv0900_st_dvbs2_single(पूर्णांकp, पूर्णांकp->demod_mode,	STV0900_DEMOD_1);
	पूर्णांकp->chip_id = stv0900_पढ़ो_reg(पूर्णांकp, R0900_MID);
	पूर्णांकp->rolloff = p_init->rolloff;
	पूर्णांकp->quartz = p_init->dmd_ref_clk;

	stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_ROLLOFF_CONTROL, p_init->rolloff);
	stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_ROLLOFF_CONTROL, p_init->rolloff);

	पूर्णांकp->ts_config = p_init->ts_config;
	अगर (पूर्णांकp->ts_config == शून्य)
		stv0900_set_ts_parallel_serial(पूर्णांकp,
				p_init->path1_ts_घड़ी,
				p_init->path2_ts_घड़ी);
	अन्यथा अणु
		क्रम (i = 0; पूर्णांकp->ts_config[i].addr != 0xffff; i++)
			stv0900_ग_लिखो_reg(पूर्णांकp,
					पूर्णांकp->ts_config[i].addr,
					पूर्णांकp->ts_config[i].val);

		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_RST_HWARE, 1);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_RST_HWARE, 0);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_RST_HWARE, 1);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_RST_HWARE, 0);
	पूर्ण

	पूर्णांकp->tuner_type[0] = p_init->tuner1_type;
	पूर्णांकp->tuner_type[1] = p_init->tuner2_type;
	/* tuner init */
	चयन (p_init->tuner1_type) अणु
	हाल 3: /*FE_AUTO_STB6100:*/
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_TNRCFG, 0x3c);
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_TNRCFG2, 0x86);
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_TNRCFG3, 0x18);
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_TNRXTAL, 27); /* 27MHz */
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_TNRSTEPS, 0x05);
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_TNRGAIN, 0x17);
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_TNRADJ, 0x1f);
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_TNRCTL2, 0x0);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_TUN_TYPE, 3);
		अवरोध;
	/* हाल FE_SW_TUNER: */
	शेष:
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_TUN_TYPE, 6);
		अवरोध;
	पूर्ण

	stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_TUN_MADDRESS, p_init->tun1_maddress);
	चयन (p_init->tuner1_adc) अणु
	हाल 1:
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_TSTTNR1, 0x26);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P1_TNRLD, 1); /* hw tuner */

	/* tuner init */
	चयन (p_init->tuner2_type) अणु
	हाल 3: /*FE_AUTO_STB6100:*/
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_TNRCFG, 0x3c);
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_TNRCFG2, 0x86);
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_TNRCFG3, 0x18);
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_TNRXTAL, 27); /* 27MHz */
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_TNRSTEPS, 0x05);
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_TNRGAIN, 0x17);
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_TNRADJ, 0x1f);
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_TNRCTL2, 0x0);
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_TUN_TYPE, 3);
		अवरोध;
	/* हाल FE_SW_TUNER: */
	शेष:
		stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_TUN_TYPE, 6);
		अवरोध;
	पूर्ण

	stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_TUN_MADDRESS, p_init->tun2_maddress);
	चयन (p_init->tuner2_adc) अणु
	हाल 1:
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_TSTTNR3, 0x26);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	stv0900_ग_लिखो_reg(पूर्णांकp, R0900_P2_TNRLD, 1); /* hw tuner */

	stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P1_TUN_IQSWAP, p_init->tun1_iq_inv);
	stv0900_ग_लिखो_bits(पूर्णांकp, F0900_P2_TUN_IQSWAP, p_init->tun2_iq_inv);
	stv0900_set_mclk(पूर्णांकp, 135000000);
	msleep(3);

	चयन (पूर्णांकp->clkmode) अणु
	हाल 0:
	हाल 2:
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_SYNTCTRL, 0x20 | पूर्णांकp->clkmode);
		अवरोध;
	शेष:
		selosci = 0x02 & stv0900_पढ़ो_reg(पूर्णांकp, R0900_SYNTCTRL);
		stv0900_ग_लिखो_reg(पूर्णांकp, R0900_SYNTCTRL, 0x20 | selosci);
		अवरोध;
	पूर्ण
	msleep(3);

	पूर्णांकp->mclk = stv0900_get_mclk_freq(पूर्णांकp, पूर्णांकp->quartz);
	अगर (पूर्णांकp->errs)
		error = STV0900_I2C_ERROR;

	वापस error;
पूर्ण

अटल पूर्णांक stv0900_status(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
					क्रमागत fe_stv0900_demod_num demod)
अणु
	क्रमागत fe_stv0900_search_state demod_state;
	पूर्णांक locked = FALSE;
	u8 tsbitrate0_val, tsbitrate1_val;
	s32 bitrate;

	demod_state = stv0900_get_bits(पूर्णांकp, HEADER_MODE);
	चयन (demod_state) अणु
	हाल STV0900_SEARCH:
	हाल STV0900_PLH_DETECTED:
	शेष:
		locked = FALSE;
		अवरोध;
	हाल STV0900_DVBS2_FOUND:
		locked = stv0900_get_bits(पूर्णांकp, LOCK_DEFINITIF) &&
				stv0900_get_bits(पूर्णांकp, PKTDELIN_LOCK) &&
				stv0900_get_bits(पूर्णांकp, TSFIFO_LINEOK);
		अवरोध;
	हाल STV0900_DVBS_FOUND:
		locked = stv0900_get_bits(पूर्णांकp, LOCK_DEFINITIF) &&
				stv0900_get_bits(पूर्णांकp, LOCKEDVIT) &&
				stv0900_get_bits(पूर्णांकp, TSFIFO_LINEOK);
		अवरोध;
	पूर्ण

	dprपूर्णांकk("%s: locked = %d\n", __func__, locked);

	अगर (stvdebug) अणु
		/* Prपूर्णांक TS bitrate */
		tsbitrate0_val = stv0900_पढ़ो_reg(पूर्णांकp, TSBITRATE0);
		tsbitrate1_val = stv0900_पढ़ो_reg(पूर्णांकp, TSBITRATE1);
		/* Formula Bit rate = Mclk * px_tsfअगरo_bitrate / 16384 */
		bitrate = (stv0900_get_mclk_freq(पूर्णांकp, पूर्णांकp->quartz)/1000000)
			* (tsbitrate1_val << 8 | tsbitrate0_val);
		bitrate /= 16384;
		dprपूर्णांकk("TS bitrate = %d Mbit/sec\n", bitrate);
	पूर्ण

	वापस locked;
पूर्ण

अटल पूर्णांक stv0900_set_mis(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp,
				क्रमागत fe_stv0900_demod_num demod, पूर्णांक mis)
अणु
	dprपूर्णांकk("%s\n", __func__);

	अगर (mis < 0 || mis > 255) अणु
		dprपूर्णांकk("Disable MIS filtering\n");
		stv0900_ग_लिखो_bits(पूर्णांकp, FILTER_EN, 0);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("Enable MIS filtering - %d\n", mis);
		stv0900_ग_लिखो_bits(पूर्णांकp, FILTER_EN, 1);
		stv0900_ग_लिखो_reg(पूर्णांकp, ISIENTRY, mis);
		stv0900_ग_लिखो_reg(पूर्णांकp, ISIBITENA, 0xff);
	पूर्ण

	वापस STV0900_NO_ERROR;
पूर्ण


अटल क्रमागत dvbfe_search stv0900_search(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	काष्ठा stv0900_search_params p_search;
	काष्ठा stv0900_संकेत_info p_result = पूर्णांकp->result[demod];

	क्रमागत fe_stv0900_error error = STV0900_NO_ERROR;

	dprपूर्णांकk("%s: ", __func__);

	अगर (!(INRANGE(100000, c->symbol_rate, 70000000)))
		वापस DVBFE_ALGO_SEARCH_FAILED;

	अगर (state->config->set_ts_params)
		state->config->set_ts_params(fe, 0);

	stv0900_set_mis(पूर्णांकp, demod, c->stream_id);

	p_result.locked = FALSE;
	p_search.path = demod;
	p_search.frequency = c->frequency;
	p_search.symbol_rate = c->symbol_rate;
	p_search.search_range = 10000000;
	p_search.fec = STV0900_FEC_UNKNOWN;
	p_search.standard = STV0900_AUTO_SEARCH;
	p_search.iq_inversion = STV0900_IQ_AUTO;
	p_search.search_algo = STV0900_BLIND_SEARCH;
	/* Speeds up DVB-S searching */
	अगर (c->delivery_प्रणाली == SYS_DVBS)
		p_search.standard = STV0900_SEARCH_DVBS1;

	पूर्णांकp->srch_standard[demod] = p_search.standard;
	पूर्णांकp->symbol_rate[demod] = p_search.symbol_rate;
	पूर्णांकp->srch_range[demod] = p_search.search_range;
	पूर्णांकp->freq[demod] = p_search.frequency;
	पूर्णांकp->srch_algo[demod] = p_search.search_algo;
	पूर्णांकp->srch_iq_inv[demod] = p_search.iq_inversion;
	पूर्णांकp->fec[demod] = p_search.fec;
	अगर ((stv0900_algo(fe) == STV0900_RANGEOK) &&
				(पूर्णांकp->errs == STV0900_NO_ERROR)) अणु
		p_result.locked = पूर्णांकp->result[demod].locked;
		p_result.standard = पूर्णांकp->result[demod].standard;
		p_result.frequency = पूर्णांकp->result[demod].frequency;
		p_result.symbol_rate = पूर्णांकp->result[demod].symbol_rate;
		p_result.fec = पूर्णांकp->result[demod].fec;
		p_result.modcode = पूर्णांकp->result[demod].modcode;
		p_result.pilot = पूर्णांकp->result[demod].pilot;
		p_result.frame_len = पूर्णांकp->result[demod].frame_len;
		p_result.spectrum = पूर्णांकp->result[demod].spectrum;
		p_result.rolloff = पूर्णांकp->result[demod].rolloff;
		p_result.modulation = पूर्णांकp->result[demod].modulation;
	पूर्ण अन्यथा अणु
		p_result.locked = FALSE;
		चयन (पूर्णांकp->err[demod]) अणु
		हाल STV0900_I2C_ERROR:
			error = STV0900_I2C_ERROR;
			अवरोध;
		हाल STV0900_NO_ERROR:
		शेष:
			error = STV0900_SEARCH_FAILED;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((p_result.locked == TRUE) && (error == STV0900_NO_ERROR)) अणु
		dprपूर्णांकk("Search Success\n");
		वापस DVBFE_ALGO_SEARCH_SUCCESS;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("Search Fail\n");
		वापस DVBFE_ALGO_SEARCH_FAILED;
	पूर्ण

पूर्ण

अटल पूर्णांक stv0900_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s: ", __func__);

	अगर ((stv0900_status(state->पूर्णांकernal, state->demod)) == TRUE) अणु
		dprपूर्णांकk("DEMOD LOCK OK\n");
		*status = FE_HAS_CARRIER
			| FE_HAS_VITERBI
			| FE_HAS_SYNC
			| FE_HAS_LOCK;
		अगर (state->config->set_lock_led)
			state->config->set_lock_led(fe, 1);
	पूर्ण अन्यथा अणु
		*status = 0;
		अगर (state->config->set_lock_led)
			state->config->set_lock_led(fe, 0);
		dprपूर्णांकk("DEMOD LOCK FAIL\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0900_stop_ts(काष्ठा dvb_frontend *fe, पूर्णांक stop_ts)
अणु

	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;

	अगर (stop_ts == TRUE)
		stv0900_ग_लिखो_bits(पूर्णांकp, RST_HWARE, 1);
	अन्यथा
		stv0900_ग_लिखो_bits(पूर्णांकp, RST_HWARE, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक stv0900_diseqc_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;

	stv0900_ग_लिखो_bits(पूर्णांकp, DISTX_MODE, state->config->diseqc_mode);
	stv0900_ग_लिखो_bits(पूर्णांकp, DISEQC_RESET, 1);
	stv0900_ग_लिखो_bits(पूर्णांकp, DISEQC_RESET, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक stv0900_init(काष्ठा dvb_frontend *fe)
अणु
	dprपूर्णांकk("%s\n", __func__);

	stv0900_stop_ts(fe, 1);
	stv0900_diseqc_init(fe);

	वापस 0;
पूर्ण

अटल पूर्णांक stv0900_diseqc_send(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp , u8 *data,
				u32 NbData, क्रमागत fe_stv0900_demod_num demod)
अणु
	s32 i = 0;

	stv0900_ग_लिखो_bits(पूर्णांकp, DIS_PRECHARGE, 1);
	जबतक (i < NbData) अणु
		जबतक (stv0900_get_bits(पूर्णांकp, FIFO_FULL))
			;/* checkpatch complains */
		stv0900_ग_लिखो_reg(पूर्णांकp, DISTXDATA, data[i]);
		i++;
	पूर्ण

	stv0900_ग_लिखो_bits(पूर्णांकp, DIS_PRECHARGE, 0);
	i = 0;
	जबतक ((stv0900_get_bits(पूर्णांकp, TX_IDLE) != 1) && (i < 10)) अणु
		msleep(10);
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0900_send_master_cmd(काष्ठा dvb_frontend *fe,
					काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;

	वापस stv0900_diseqc_send(state->पूर्णांकernal,
				cmd->msg,
				cmd->msg_len,
				state->demod);
पूर्ण

अटल पूर्णांक stv0900_send_burst(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;
	u8 data;


	चयन (burst) अणु
	हाल SEC_MINI_A:
		stv0900_ग_लिखो_bits(पूर्णांकp, DISTX_MODE, 3);/* Unmodulated */
		data = 0x00;
		stv0900_diseqc_send(पूर्णांकp, &data, 1, state->demod);
		अवरोध;
	हाल SEC_MINI_B:
		stv0900_ग_लिखो_bits(पूर्णांकp, DISTX_MODE, 2);/* Modulated */
		data = 0xff;
		stv0900_diseqc_send(पूर्णांकp, &data, 1, state->demod);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0900_recv_slave_reply(काष्ठा dvb_frontend *fe,
				काष्ठा dvb_diseqc_slave_reply *reply)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;
	s32 i = 0;

	reply->msg_len = 0;

	जबतक ((stv0900_get_bits(पूर्णांकp, RX_END) != 1) && (i < 10)) अणु
		msleep(10);
		i++;
	पूर्ण

	अगर (stv0900_get_bits(पूर्णांकp, RX_END)) अणु
		reply->msg_len = stv0900_get_bits(पूर्णांकp, FIFO_BYTENBR);

		क्रम (i = 0; i < reply->msg_len; i++)
			reply->msg[i] = stv0900_पढ़ो_reg(पूर्णांकp, DISRXDATA);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0900_set_tone(काष्ठा dvb_frontend *fe,
			    क्रमागत fe_sec_tone_mode toneoff)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;

	dprपूर्णांकk("%s: %s\n", __func__, ((toneoff == 0) ? "On" : "Off"));

	चयन (toneoff) अणु
	हाल SEC_TONE_ON:
		/*Set the DiseqC mode to 22Khz _जारीs_ tone*/
		stv0900_ग_लिखो_bits(पूर्णांकp, DISTX_MODE, 0);
		stv0900_ग_लिखो_bits(पूर्णांकp, DISEQC_RESET, 1);
		/*release DiseqC reset to enable the 22KHz tone*/
		stv0900_ग_लिखो_bits(पूर्णांकp, DISEQC_RESET, 0);
		अवरोध;
	हाल SEC_TONE_OFF:
		/*वापस diseqc mode to config->diseqc_mode.
		Usually it's without _जारीs_ tone */
		stv0900_ग_लिखो_bits(पूर्णांकp, DISTX_MODE,
				state->config->diseqc_mode);
		/*मुख्यtain the DiseqC reset to disable the 22KHz tone*/
		stv0900_ग_लिखो_bits(पूर्णांकp, DISEQC_RESET, 1);
		stv0900_ग_लिखो_bits(पूर्णांकp, DISEQC_RESET, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम stv0900_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s\n", __func__);

	अगर (state->config->set_lock_led)
		state->config->set_lock_led(fe, 0);

	अगर ((--(state->पूर्णांकernal->dmds_used)) <= 0) अणु

		dprपूर्णांकk("%s: Actually removing\n", __func__);

		हटाओ_inode(state->पूर्णांकernal);
		kमुक्त(state->पूर्णांकernal);
	पूर्ण

	kमुक्त(state);
पूर्ण

अटल पूर्णांक stv0900_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s\n", __func__);

	अगर (state->config->set_lock_led)
		state->config->set_lock_led(fe, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक stv0900_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा stv0900_state *state = fe->demodulator_priv;
	काष्ठा stv0900_पूर्णांकernal *पूर्णांकp = state->पूर्णांकernal;
	क्रमागत fe_stv0900_demod_num demod = state->demod;
	काष्ठा stv0900_संकेत_info p_result = पूर्णांकp->result[demod];

	p->frequency = p_result.locked ? p_result.frequency : 0;
	p->symbol_rate = p_result.locked ? p_result.symbol_rate : 0;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops stv0900_ops = अणु
	.delsys = अणु SYS_DVBS, SYS_DVBS2, SYS_DSS पूर्ण,
	.info = अणु
		.name			= "STV0900 frontend",
		.frequency_min_hz	=  950 * MHz,
		.frequency_max_hz	= 2150 * MHz,
		.frequency_stepsize_hz	=  125 * kHz,
		.symbol_rate_min	= 1000000,
		.symbol_rate_max	= 45000000,
		.symbol_rate_tolerance	= 500,
		.caps			= FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 |
					  FE_CAN_FEC_3_4 | FE_CAN_FEC_5_6 |
					  FE_CAN_FEC_7_8 | FE_CAN_QPSK    |
					  FE_CAN_2G_MODULATION |
					  FE_CAN_FEC_AUTO
	पूर्ण,
	.release			= stv0900_release,
	.init				= stv0900_init,
	.get_frontend                   = stv0900_get_frontend,
	.sleep				= stv0900_sleep,
	.get_frontend_algo		= stv0900_frontend_algo,
	.i2c_gate_ctrl			= stv0900_i2c_gate_ctrl,
	.diseqc_send_master_cmd		= stv0900_send_master_cmd,
	.diseqc_send_burst		= stv0900_send_burst,
	.diseqc_recv_slave_reply	= stv0900_recv_slave_reply,
	.set_tone			= stv0900_set_tone,
	.search				= stv0900_search,
	.पढ़ो_status			= stv0900_पढ़ो_status,
	.पढ़ो_ber			= stv0900_पढ़ो_ber,
	.पढ़ो_संकेत_strength		= stv0900_पढ़ो_संकेत_strength,
	.पढ़ो_snr			= stv0900_पढ़ो_snr,
	.पढ़ो_ucblocks                  = stv0900_पढ़ो_ucblocks,
पूर्ण;

काष्ठा dvb_frontend *stv0900_attach(स्थिर काष्ठा stv0900_config *config,
					काष्ठा i2c_adapter *i2c,
					पूर्णांक demod)
अणु
	काष्ठा stv0900_state *state = शून्य;
	काष्ठा stv0900_init_params init_params;
	क्रमागत fe_stv0900_error err_stv0900;

	state = kzalloc(माप(काष्ठा stv0900_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	state->demod		= demod;
	state->config		= config;
	state->i2c_adap		= i2c;

	स_नकल(&state->frontend.ops, &stv0900_ops,
			माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	चयन (demod) अणु
	हाल 0:
	हाल 1:
		init_params.dmd_ref_clk		= config->xtal;
		init_params.demod_mode		= config->demod_mode;
		init_params.rolloff		= STV0900_35;
		init_params.path1_ts_घड़ी	= config->path1_mode;
		init_params.tun1_maddress	= config->tun1_maddress;
		init_params.tun1_iq_inv		= STV0900_IQ_NORMAL;
		init_params.tuner1_adc		= config->tun1_adc;
		init_params.tuner1_type		= config->tun1_type;
		init_params.path2_ts_घड़ी	= config->path2_mode;
		init_params.ts_config		= config->ts_config_regs;
		init_params.tun2_maddress	= config->tun2_maddress;
		init_params.tuner2_adc		= config->tun2_adc;
		init_params.tuner2_type		= config->tun2_type;
		init_params.tun2_iq_inv		= STV0900_IQ_SWAPPED;

		err_stv0900 = stv0900_init_पूर्णांकernal(&state->frontend,
							&init_params);

		अगर (err_stv0900)
			जाओ error;

		अगर (state->पूर्णांकernal->chip_id >= 0x30)
			state->frontend.ops.info.caps |= FE_CAN_MULTISTREAM;

		अवरोध;
	शेष:
		जाओ error;
		अवरोध;
	पूर्ण

	dprपूर्णांकk("%s: Attaching STV0900 demodulator(%d) \n", __func__, demod);
	वापस &state->frontend;

error:
	dprपूर्णांकk("%s: Failed to attach STV0900 demodulator(%d) \n",
		__func__, demod);
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(stv0900_attach);

MODULE_PARM_DESC(debug, "Set debug");

MODULE_AUTHOR("Igor M. Liplianin");
MODULE_DESCRIPTION("ST STV0900 frontend");
MODULE_LICENSE("GPL");
