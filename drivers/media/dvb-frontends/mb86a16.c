<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Fujitsu MB86A16 DVB-S/DSS DC Receiver driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "mb86a16.h"
#समावेश "mb86a16_priv.h"

अटल अचिन्हित पूर्णांक verbose = 5;
module_param(verbose, पूर्णांक, 0644);

काष्ठा mb86a16_state अणु
	काष्ठा i2c_adapter		*i2c_adap;
	स्थिर काष्ठा mb86a16_config	*config;
	काष्ठा dvb_frontend		frontend;

	/* tuning parameters */
	पूर्णांक				frequency;
	पूर्णांक				srate;

	/* Internal stuff */
	पूर्णांक				master_clk;
	पूर्णांक				deci;
	पूर्णांक				csel;
	पूर्णांक				rsel;
पूर्ण;

#घोषणा MB86A16_ERROR		0
#घोषणा MB86A16_NOTICE		1
#घोषणा MB86A16_INFO		2
#घोषणा MB86A16_DEBUG		3

#घोषणा dprपूर्णांकk(x, y, z, क्रमmat, arg...) करो अणु						\
	अगर (z) अणु									\
		अगर	((x > MB86A16_ERROR) && (x > y))				\
			prपूर्णांकk(KERN_ERR "%s: " क्रमmat "\n", __func__, ##arg);		\
		अन्यथा अगर ((x > MB86A16_NOTICE) && (x > y))				\
			prपूर्णांकk(KERN_NOTICE "%s: " क्रमmat "\n", __func__, ##arg);	\
		अन्यथा अगर ((x > MB86A16_INFO) && (x > y))					\
			prपूर्णांकk(KERN_INFO "%s: " क्रमmat "\n", __func__, ##arg);		\
		अन्यथा अगर ((x > MB86A16_DEBUG) && (x > y))				\
			prपूर्णांकk(KERN_DEBUG "%s: " क्रमmat "\n", __func__, ##arg);		\
	पूर्ण अन्यथा अणु									\
		अगर (x > y)								\
			prपूर्णांकk(क्रमmat, ##arg);						\
	पूर्ण										\
पूर्ण जबतक (0)

#घोषणा TRACE_IN	dprपूर्णांकk(verbose, MB86A16_DEBUG, 1, "-->()")
#घोषणा TRACE_OUT	dprपूर्णांकk(verbose, MB86A16_DEBUG, 1, "()-->")

अटल पूर्णांक mb86a16_ग_लिखो(काष्ठा mb86a16_state *state, u8 reg, u8 val)
अणु
	पूर्णांक ret;
	u8 buf[] = अणु reg, val पूर्ण;

	काष्ठा i2c_msg msg = अणु
		.addr = state->config->demod_address,
		.flags = 0,
		.buf = buf,
		.len = 2
	पूर्ण;

	dprपूर्णांकk(verbose, MB86A16_DEBUG, 1,
		"writing to [0x%02x],Reg[0x%02x],Data[0x%02x]",
		state->config->demod_address, buf[0], buf[1]);

	ret = i2c_transfer(state->i2c_adap, &msg, 1);

	वापस (ret != 1) ? -EREMOTEIO : 0;
पूर्ण

अटल पूर्णांक mb86a16_पढ़ो(काष्ठा mb86a16_state *state, u8 reg, u8 *val)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;

	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = state->config->demod_address,
			.flags = 0,
			.buf = b0,
			.len = 1
		पूर्ण, अणु
			.addr = state->config->demod_address,
			.flags = I2C_M_RD,
			.buf = b1,
			.len = 1
		पूर्ण
	पूर्ण;
	ret = i2c_transfer(state->i2c_adap, msg, 2);
	अगर (ret != 2) अणु
		dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "read error(reg=0x%02x, ret=%i)",
			reg, ret);

		अगर (ret < 0)
			वापस ret;
		वापस -EREMOTEIO;
	पूर्ण
	*val = b1[0];

	वापस ret;
पूर्ण

अटल पूर्णांक CNTM_set(काष्ठा mb86a16_state *state,
		    अचिन्हित अक्षर timपूर्णांक1,
		    अचिन्हित अक्षर timपूर्णांक2,
		    अचिन्हित अक्षर cnext)
अणु
	अचिन्हित अक्षर val;

	val = (timपूर्णांक1 << 4) | (timपूर्णांक2 << 2) | cnext;
	अगर (mb86a16_ग_लिखो(state, MB86A16_CNTMR, val) < 0)
		जाओ err;

	वापस 0;

err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल पूर्णांक smrt_set(काष्ठा mb86a16_state *state, पूर्णांक rate)
अणु
	पूर्णांक पंचांगp ;
	पूर्णांक m ;
	अचिन्हित अक्षर STOFS0, STOFS1;

	m = 1 << state->deci;
	पंचांगp = (8192 * state->master_clk - 2 * m * rate * 8192 + state->master_clk / 2) / state->master_clk;

	STOFS0 = पंचांगp & 0x0ff;
	STOFS1 = (पंचांगp & 0xf00) >> 8;

	अगर (mb86a16_ग_लिखो(state, MB86A16_SRATE1, (state->deci << 2) |
				       (state->csel << 1) |
					state->rsel) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, MB86A16_SRATE2, STOFS0) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, MB86A16_SRATE3, STOFS1) < 0)
		जाओ err;

	वापस 0;
err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -1;
पूर्ण

अटल पूर्णांक srst(काष्ठा mb86a16_state *state)
अणु
	अगर (mb86a16_ग_लिखो(state, MB86A16_RESET, 0x04) < 0)
		जाओ err;

	वापस 0;
err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;

पूर्ण

अटल पूर्णांक afcex_data_set(काष्ठा mb86a16_state *state,
			  अचिन्हित अक्षर AFCEX_L,
			  अचिन्हित अक्षर AFCEX_H)
अणु
	अगर (mb86a16_ग_लिखो(state, MB86A16_AFCEXL, AFCEX_L) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, MB86A16_AFCEXH, AFCEX_H) < 0)
		जाओ err;

	वापस 0;
err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");

	वापस -1;
पूर्ण

अटल पूर्णांक afcofs_data_set(काष्ठा mb86a16_state *state,
			   अचिन्हित अक्षर AFCEX_L,
			   अचिन्हित अक्षर AFCEX_H)
अणु
	अगर (mb86a16_ग_लिखो(state, 0x58, AFCEX_L) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, 0x59, AFCEX_H) < 0)
		जाओ err;

	वापस 0;
err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल पूर्णांक stlp_set(काष्ठा mb86a16_state *state,
		    अचिन्हित अक्षर STRAS,
		    अचिन्हित अक्षर STRBS)
अणु
	अगर (mb86a16_ग_लिखो(state, MB86A16_STRFILTCOEF1, (STRBS << 3) | (STRAS)) < 0)
		जाओ err;

	वापस 0;
err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल पूर्णांक Vi_set(काष्ठा mb86a16_state *state, अचिन्हित अक्षर ETH, अचिन्हित अक्षर VIA)
अणु
	अगर (mb86a16_ग_लिखो(state, MB86A16_VISET2, 0x04) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, MB86A16_VISET3, 0xf5) < 0)
		जाओ err;

	वापस 0;
err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल पूर्णांक initial_set(काष्ठा mb86a16_state *state)
अणु
	अगर (stlp_set(state, 5, 7))
		जाओ err;

	udelay(100);
	अगर (afcex_data_set(state, 0, 0))
		जाओ err;

	udelay(100);
	अगर (afcofs_data_set(state, 0, 0))
		जाओ err;

	udelay(100);
	अगर (mb86a16_ग_लिखो(state, MB86A16_CRLFILTCOEF1, 0x16) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, 0x2f, 0x21) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, MB86A16_VIMAG, 0x38) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, MB86A16_FAGCS1, 0x00) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, MB86A16_FAGCS2, 0x1c) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, MB86A16_FAGCS3, 0x20) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, MB86A16_FAGCS4, 0x1e) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, MB86A16_FAGCS5, 0x23) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, 0x54, 0xff) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, MB86A16_TSOUT, 0x00) < 0)
		जाओ err;

	वापस 0;

err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल पूर्णांक S01T_set(काष्ठा mb86a16_state *state,
		    अचिन्हित अक्षर s1t,
		    अचिन्हित s0t)
अणु
	अगर (mb86a16_ग_लिखो(state, 0x33, (s1t << 3) | s0t) < 0)
		जाओ err;

	वापस 0;
err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण


अटल पूर्णांक EN_set(काष्ठा mb86a16_state *state,
		  पूर्णांक cren,
		  पूर्णांक afcen)
अणु
	अचिन्हित अक्षर val;

	val = 0x7a | (cren << 7) | (afcen << 2);
	अगर (mb86a16_ग_लिखो(state, 0x49, val) < 0)
		जाओ err;

	वापस 0;
err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल पूर्णांक AFCEXEN_set(काष्ठा mb86a16_state *state,
		       पूर्णांक afcexen,
		       पूर्णांक smrt)
अणु
	अचिन्हित अक्षर AFCA ;

	अगर (smrt > 18875)
		AFCA = 4;
	अन्यथा अगर (smrt > 9375)
		AFCA = 3;
	अन्यथा अगर (smrt > 2250)
		AFCA = 2;
	अन्यथा
		AFCA = 1;

	अगर (mb86a16_ग_लिखो(state, 0x2a, 0x02 | (afcexen << 5) | (AFCA << 2)) < 0)
		जाओ err;

	वापस 0;

err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल पूर्णांक DAGC_data_set(काष्ठा mb86a16_state *state,
			 अचिन्हित अक्षर DAGCA,
			 अचिन्हित अक्षर DAGCW)
अणु
	अगर (mb86a16_ग_लिखो(state, 0x2d, (DAGCA << 3) | DAGCW) < 0)
		जाओ err;

	वापस 0;

err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल व्योम smrt_info_get(काष्ठा mb86a16_state *state, पूर्णांक rate)
अणु
	अगर (rate >= 37501) अणु
		state->deci = 0; state->csel = 0; state->rsel = 0;
	पूर्ण अन्यथा अगर (rate >= 30001) अणु
		state->deci = 0; state->csel = 0; state->rsel = 1;
	पूर्ण अन्यथा अगर (rate >= 26251) अणु
		state->deci = 0; state->csel = 1; state->rsel = 0;
	पूर्ण अन्यथा अगर (rate >= 22501) अणु
		state->deci = 0; state->csel = 1; state->rsel = 1;
	पूर्ण अन्यथा अगर (rate >= 18751) अणु
		state->deci = 1; state->csel = 0; state->rsel = 0;
	पूर्ण अन्यथा अगर (rate >= 15001) अणु
		state->deci = 1; state->csel = 0; state->rsel = 1;
	पूर्ण अन्यथा अगर (rate >= 13126) अणु
		state->deci = 1; state->csel = 1; state->rsel = 0;
	पूर्ण अन्यथा अगर (rate >= 11251) अणु
		state->deci = 1; state->csel = 1; state->rsel = 1;
	पूर्ण अन्यथा अगर (rate >= 9376) अणु
		state->deci = 2; state->csel = 0; state->rsel = 0;
	पूर्ण अन्यथा अगर (rate >= 7501) अणु
		state->deci = 2; state->csel = 0; state->rsel = 1;
	पूर्ण अन्यथा अगर (rate >= 6563) अणु
		state->deci = 2; state->csel = 1; state->rsel = 0;
	पूर्ण अन्यथा अगर (rate >= 5626) अणु
		state->deci = 2; state->csel = 1; state->rsel = 1;
	पूर्ण अन्यथा अगर (rate >= 4688) अणु
		state->deci = 3; state->csel = 0; state->rsel = 0;
	पूर्ण अन्यथा अगर (rate >= 3751) अणु
		state->deci = 3; state->csel = 0; state->rsel = 1;
	पूर्ण अन्यथा अगर (rate >= 3282) अणु
		state->deci = 3; state->csel = 1; state->rsel = 0;
	पूर्ण अन्यथा अगर (rate >= 2814) अणु
		state->deci = 3; state->csel = 1; state->rsel = 1;
	पूर्ण अन्यथा अगर (rate >= 2344) अणु
		state->deci = 4; state->csel = 0; state->rsel = 0;
	पूर्ण अन्यथा अगर (rate >= 1876) अणु
		state->deci = 4; state->csel = 0; state->rsel = 1;
	पूर्ण अन्यथा अगर (rate >= 1641) अणु
		state->deci = 4; state->csel = 1; state->rsel = 0;
	पूर्ण अन्यथा अगर (rate >= 1407) अणु
		state->deci = 4; state->csel = 1; state->rsel = 1;
	पूर्ण अन्यथा अगर (rate >= 1172) अणु
		state->deci = 5; state->csel = 0; state->rsel = 0;
	पूर्ण अन्यथा अगर (rate >=  939) अणु
		state->deci = 5; state->csel = 0; state->rsel = 1;
	पूर्ण अन्यथा अगर (rate >=  821) अणु
		state->deci = 5; state->csel = 1; state->rsel = 0;
	पूर्ण अन्यथा अणु
		state->deci = 5; state->csel = 1; state->rsel = 1;
	पूर्ण

	अगर (state->csel == 0)
		state->master_clk = 92000;
	अन्यथा
		state->master_clk = 61333;

पूर्ण

अटल पूर्णांक संकेत_det(काष्ठा mb86a16_state *state,
		      पूर्णांक smrt,
		      अचिन्हित अक्षर *SIG)
अणु
	पूर्णांक ret;
	पूर्णांक smrtd;
	अचिन्हित अक्षर S[3];
	पूर्णांक i;

	अगर (*SIG > 45) अणु
		अगर (CNTM_set(state, 2, 1, 2) < 0) अणु
			dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "CNTM set Error");
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (CNTM_set(state, 3, 1, 2) < 0) अणु
			dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "CNTM set Error");
			वापस -1;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < 3; i++) अणु
		अगर (i == 0)
			smrtd = smrt * 98 / 100;
		अन्यथा अगर (i == 1)
			smrtd = smrt;
		अन्यथा
			smrtd = smrt * 102 / 100;
		smrt_info_get(state, smrtd);
		smrt_set(state, smrtd);
		srst(state);
		msleep_पूर्णांकerruptible(10);
		अगर (mb86a16_पढ़ो(state, 0x37, &(S[i])) != 2) अणु
			dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण
	अगर ((S[1] > S[0] * 112 / 100) && (S[1] > S[2] * 112 / 100))
		ret = 1;
	अन्यथा
		ret = 0;

	*SIG = S[1];

	अगर (CNTM_set(state, 0, 1, 2) < 0) अणु
		dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "CNTM set Error");
		वापस -1;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rf_val_set(काष्ठा mb86a16_state *state,
		      पूर्णांक f,
		      पूर्णांक smrt,
		      अचिन्हित अक्षर R)
अणु
	अचिन्हित अक्षर C, F, B;
	पूर्णांक M;
	अचिन्हित अक्षर rf_val[5];
	पूर्णांक ack = -1;

	अगर (smrt > 37750)
		C = 1;
	अन्यथा अगर (smrt > 18875)
		C = 2;
	अन्यथा अगर (smrt > 5500)
		C = 3;
	अन्यथा
		C = 4;

	अगर (smrt > 30500)
		F = 3;
	अन्यथा अगर (smrt > 9375)
		F = 1;
	अन्यथा अगर (smrt > 4625)
		F = 0;
	अन्यथा
		F = 2;

	अगर (f < 1060)
		B = 0;
	अन्यथा अगर (f < 1175)
		B = 1;
	अन्यथा अगर (f < 1305)
		B = 2;
	अन्यथा अगर (f < 1435)
		B = 3;
	अन्यथा अगर (f < 1570)
		B = 4;
	अन्यथा अगर (f < 1715)
		B = 5;
	अन्यथा अगर (f < 1845)
		B = 6;
	अन्यथा अगर (f < 1980)
		B = 7;
	अन्यथा अगर (f < 2080)
		B = 8;
	अन्यथा
		B = 9;

	M = f * (1 << R) / 2;

	rf_val[0] = 0x01 | (C << 3) | (F << 1);
	rf_val[1] = (R << 5) | ((M & 0x1f000) >> 12);
	rf_val[2] = (M & 0x00ff0) >> 4;
	rf_val[3] = ((M & 0x0000f) << 4) | B;

	/* Frequency Set */
	अगर (mb86a16_ग_लिखो(state, 0x21, rf_val[0]) < 0)
		ack = 0;
	अगर (mb86a16_ग_लिखो(state, 0x22, rf_val[1]) < 0)
		ack = 0;
	अगर (mb86a16_ग_लिखो(state, 0x23, rf_val[2]) < 0)
		ack = 0;
	अगर (mb86a16_ग_लिखो(state, 0x24, rf_val[3]) < 0)
		ack = 0;
	अगर (mb86a16_ग_लिखो(state, 0x25, 0x01) < 0)
		ack = 0;
	अगर (ack == 0) अणु
		dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "RF Setup - I2C transfer error");
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक afcerr_chk(काष्ठा mb86a16_state *state)
अणु
	अचिन्हित अक्षर AFCM_L, AFCM_H ;
	पूर्णांक AFCM ;
	पूर्णांक afcm, afcerr ;

	अगर (mb86a16_पढ़ो(state, 0x0e, &AFCM_L) != 2)
		जाओ err;
	अगर (mb86a16_पढ़ो(state, 0x0f, &AFCM_H) != 2)
		जाओ err;

	AFCM = (AFCM_H << 8) + AFCM_L;

	अगर (AFCM > 2048)
		afcm = AFCM - 4096;
	अन्यथा
		afcm = AFCM;
	afcerr = afcm * state->master_clk / 8192;

	वापस afcerr;

err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल पूर्णांक dagcm_val_get(काष्ठा mb86a16_state *state)
अणु
	पूर्णांक DAGCM;
	अचिन्हित अक्षर DAGCM_H, DAGCM_L;

	अगर (mb86a16_पढ़ो(state, 0x45, &DAGCM_L) != 2)
		जाओ err;
	अगर (mb86a16_पढ़ो(state, 0x46, &DAGCM_H) != 2)
		जाओ err;

	DAGCM = (DAGCM_H << 8) + DAGCM_L;

	वापस DAGCM;

err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल पूर्णांक mb86a16_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	u8 stat, stat2;
	काष्ठा mb86a16_state *state = fe->demodulator_priv;

	*status = 0;

	अगर (mb86a16_पढ़ो(state, MB86A16_SIG1, &stat) != 2)
		जाओ err;
	अगर (mb86a16_पढ़ो(state, MB86A16_SIG2, &stat2) != 2)
		जाओ err;
	अगर ((stat > 25) && (stat2 > 25))
		*status |= FE_HAS_SIGNAL;
	अगर ((stat > 45) && (stat2 > 45))
		*status |= FE_HAS_CARRIER;

	अगर (mb86a16_पढ़ो(state, MB86A16_STATUS, &stat) != 2)
		जाओ err;

	अगर (stat & 0x01)
		*status |= FE_HAS_SYNC;
	अगर (stat & 0x01)
		*status |= FE_HAS_VITERBI;

	अगर (mb86a16_पढ़ो(state, MB86A16_FRAMESYNC, &stat) != 2)
		जाओ err;

	अगर ((stat & 0x0f) && (*status & FE_HAS_VITERBI))
		*status |= FE_HAS_LOCK;

	वापस 0;

err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल पूर्णांक sync_chk(काष्ठा mb86a16_state *state,
		    अचिन्हित अक्षर *VIRM)
अणु
	अचिन्हित अक्षर val;
	पूर्णांक sync;

	अगर (mb86a16_पढ़ो(state, 0x0d, &val) != 2)
		जाओ err;

	dprपूर्णांकk(verbose, MB86A16_INFO, 1, "Status = %02x,", val);
	sync = val & 0x01;
	*VIRM = (val & 0x1c) >> 2;

	वापस sync;
err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	*VIRM = 0;
	वापस -EREMOTEIO;

पूर्ण

अटल पूर्णांक freqerr_chk(काष्ठा mb86a16_state *state,
		       पूर्णांक fTP,
		       पूर्णांक smrt,
		       पूर्णांक unit)
अणु
	अचिन्हित अक्षर CRM, AFCML, AFCMH;
	अचिन्हित अक्षर temp1, temp2, temp3;
	पूर्णांक crm, afcm, AFCM;
	पूर्णांक crrerr, afcerr;		/* kHz */
	पूर्णांक frqerr;			/* MHz */
	पूर्णांक afcen, afcexen = 0;
	पूर्णांक R, M, fOSC, fOSC_OFS;

	अगर (mb86a16_पढ़ो(state, 0x43, &CRM) != 2)
		जाओ err;

	अगर (CRM > 127)
		crm = CRM - 256;
	अन्यथा
		crm = CRM;

	crrerr = smrt * crm / 256;
	अगर (mb86a16_पढ़ो(state, 0x49, &temp1) != 2)
		जाओ err;

	afcen = (temp1 & 0x04) >> 2;
	अगर (afcen == 0) अणु
		अगर (mb86a16_पढ़ो(state, 0x2a, &temp1) != 2)
			जाओ err;
		afcexen = (temp1 & 0x20) >> 5;
	पूर्ण

	अगर (afcen == 1) अणु
		अगर (mb86a16_पढ़ो(state, 0x0e, &AFCML) != 2)
			जाओ err;
		अगर (mb86a16_पढ़ो(state, 0x0f, &AFCMH) != 2)
			जाओ err;
	पूर्ण अन्यथा अगर (afcexen == 1) अणु
		अगर (mb86a16_पढ़ो(state, 0x2b, &AFCML) != 2)
			जाओ err;
		अगर (mb86a16_पढ़ो(state, 0x2c, &AFCMH) != 2)
			जाओ err;
	पूर्ण
	अगर ((afcen == 1) || (afcexen == 1)) अणु
		smrt_info_get(state, smrt);
		AFCM = ((AFCMH & 0x01) << 8) + AFCML;
		अगर (AFCM > 255)
			afcm = AFCM - 512;
		अन्यथा
			afcm = AFCM;

		afcerr = afcm * state->master_clk / 8192;
	पूर्ण अन्यथा
		afcerr = 0;

	अगर (mb86a16_पढ़ो(state, 0x22, &temp1) != 2)
		जाओ err;
	अगर (mb86a16_पढ़ो(state, 0x23, &temp2) != 2)
		जाओ err;
	अगर (mb86a16_पढ़ो(state, 0x24, &temp3) != 2)
		जाओ err;

	R = (temp1 & 0xe0) >> 5;
	M = ((temp1 & 0x1f) << 12) + (temp2 << 4) + (temp3 >> 4);
	अगर (R == 0)
		fOSC = 2 * M;
	अन्यथा
		fOSC = M;

	fOSC_OFS = fOSC - fTP;

	अगर (unit == 0) अणु	/* MHz */
		अगर (crrerr + afcerr + fOSC_OFS * 1000 >= 0)
			frqerr = (crrerr + afcerr + fOSC_OFS * 1000 + 500) / 1000;
		अन्यथा
			frqerr = (crrerr + afcerr + fOSC_OFS * 1000 - 500) / 1000;
	पूर्ण अन्यथा अणु	/* kHz */
		frqerr = crrerr + afcerr + fOSC_OFS * 1000;
	पूर्ण

	वापस frqerr;
err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल अचिन्हित अक्षर vco_dev_get(काष्ठा mb86a16_state *state, पूर्णांक smrt)
अणु
	अचिन्हित अक्षर R;

	अगर (smrt > 9375)
		R = 0;
	अन्यथा
		R = 1;

	वापस R;
पूर्ण

अटल व्योम swp_info_get(काष्ठा mb86a16_state *state,
			 पूर्णांक fOSC_start,
			 पूर्णांक smrt,
			 पूर्णांक v, पूर्णांक R,
			 पूर्णांक swp_ofs,
			 पूर्णांक *fOSC,
			 पूर्णांक *afcex_freq,
			 अचिन्हित अक्षर *AFCEX_L,
			 अचिन्हित अक्षर *AFCEX_H)
अणु
	पूर्णांक AFCEX ;
	पूर्णांक crnt_swp_freq ;

	crnt_swp_freq = fOSC_start * 1000 + v * swp_ofs;

	अगर (R == 0)
		*fOSC = (crnt_swp_freq + 1000) / 2000 * 2;
	अन्यथा
		*fOSC = (crnt_swp_freq + 500) / 1000;

	अगर (*fOSC >= crnt_swp_freq)
		*afcex_freq = *fOSC * 1000 - crnt_swp_freq;
	अन्यथा
		*afcex_freq = crnt_swp_freq - *fOSC * 1000;

	AFCEX = *afcex_freq * 8192 / state->master_clk;
	*AFCEX_L =  AFCEX & 0x00ff;
	*AFCEX_H = (AFCEX & 0x0f00) >> 8;
पूर्ण


अटल पूर्णांक swp_freq_calcuation(काष्ठा mb86a16_state *state, पूर्णांक i, पूर्णांक v, पूर्णांक *V,  पूर्णांक vmax, पूर्णांक vmin,
			       पूर्णांक SIGMIN, पूर्णांक fOSC, पूर्णांक afcex_freq, पूर्णांक swp_ofs, अचिन्हित अक्षर *SIG1)
अणु
	पूर्णांक swp_freq ;

	अगर ((i % 2 == 1) && (v <= vmax)) अणु
		/* positive v (हाल 1) */
		अगर ((v - 1 == vmin)				&&
		    (*(V + 30 + v) >= 0)			&&
		    (*(V + 30 + v - 1) >= 0)			&&
		    (*(V + 30 + v - 1) > *(V + 30 + v))		&&
		    (*(V + 30 + v - 1) > SIGMIN)) अणु

			swp_freq = fOSC * 1000 + afcex_freq - swp_ofs;
			*SIG1 = *(V + 30 + v - 1);
		पूर्ण अन्यथा अगर ((v == vmax)				&&
			   (*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v - 1) >= 0)		&&
			   (*(V + 30 + v) > *(V + 30 + v - 1))	&&
			   (*(V + 30 + v) > SIGMIN)) अणु
			/* (हाल 2) */
			swp_freq = fOSC * 1000 + afcex_freq;
			*SIG1 = *(V + 30 + v);
		पूर्ण अन्यथा अगर ((*(V + 30 + v) > 0)			&&
			   (*(V + 30 + v - 1) > 0)		&&
			   (*(V + 30 + v - 2) > 0)		&&
			   (*(V + 30 + v - 3) > 0)		&&
			   (*(V + 30 + v - 1) > *(V + 30 + v))	&&
			   (*(V + 30 + v - 2) > *(V + 30 + v - 3)) &&
			   ((*(V + 30 + v - 1) > SIGMIN)	||
			   (*(V + 30 + v - 2) > SIGMIN))) अणु
			/* (हाल 3) */
			अगर (*(V + 30 + v - 1) >= *(V + 30 + v - 2)) अणु
				swp_freq = fOSC * 1000 + afcex_freq - swp_ofs;
				*SIG1 = *(V + 30 + v - 1);
			पूर्ण अन्यथा अणु
				swp_freq = fOSC * 1000 + afcex_freq - swp_ofs * 2;
				*SIG1 = *(V + 30 + v - 2);
			पूर्ण
		पूर्ण अन्यथा अगर ((v == vmax)				&&
			   (*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v - 1) >= 0)		&&
			   (*(V + 30 + v - 2) >= 0)		&&
			   (*(V + 30 + v) > *(V + 30 + v - 2))	&&
			   (*(V + 30 + v - 1) > *(V + 30 + v - 2)) &&
			   ((*(V + 30 + v) > SIGMIN)		||
			   (*(V + 30 + v - 1) > SIGMIN))) अणु
			/* (हाल 4) */
			अगर (*(V + 30 + v) >= *(V + 30 + v - 1)) अणु
				swp_freq = fOSC * 1000 + afcex_freq;
				*SIG1 = *(V + 30 + v);
			पूर्ण अन्यथा अणु
				swp_freq = fOSC * 1000 + afcex_freq - swp_ofs;
				*SIG1 = *(V + 30 + v - 1);
			पूर्ण
		पूर्ण अन्यथा  अणु
			swp_freq = -1 ;
		पूर्ण
	पूर्ण अन्यथा अगर ((i % 2 == 0) && (v >= vmin)) अणु
		/* Negative v (हाल 1) */
		अगर ((*(V + 30 + v) > 0)				&&
		    (*(V + 30 + v + 1) > 0)			&&
		    (*(V + 30 + v + 2) > 0)			&&
		    (*(V + 30 + v + 1) > *(V + 30 + v))		&&
		    (*(V + 30 + v + 1) > *(V + 30 + v + 2))	&&
		    (*(V + 30 + v + 1) > SIGMIN)) अणु

			swp_freq = fOSC * 1000 + afcex_freq + swp_ofs;
			*SIG1 = *(V + 30 + v + 1);
		पूर्ण अन्यथा अगर ((v + 1 == vmax)			&&
			   (*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v + 1) >= 0)		&&
			   (*(V + 30 + v + 1) > *(V + 30 + v))	&&
			   (*(V + 30 + v + 1) > SIGMIN)) अणु
			/* (हाल 2) */
			swp_freq = fOSC * 1000 + afcex_freq + swp_ofs;
			*SIG1 = *(V + 30 + v);
		पूर्ण अन्यथा अगर ((v == vmin)				&&
			   (*(V + 30 + v) > 0)			&&
			   (*(V + 30 + v + 1) > 0)		&&
			   (*(V + 30 + v + 2) > 0)		&&
			   (*(V + 30 + v) > *(V + 30 + v + 1))	&&
			   (*(V + 30 + v) > *(V + 30 + v + 2))	&&
			   (*(V + 30 + v) > SIGMIN)) अणु
			/* (हाल 3) */
			swp_freq = fOSC * 1000 + afcex_freq;
			*SIG1 = *(V + 30 + v);
		पूर्ण अन्यथा अगर ((*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v + 1) >= 0)		&&
			   (*(V + 30 + v + 2) >= 0)		&&
			   (*(V + 30 + v + 3) >= 0)		&&
			   (*(V + 30 + v + 1) > *(V + 30 + v))	&&
			   (*(V + 30 + v + 2) > *(V + 30 + v + 3)) &&
			   ((*(V + 30 + v + 1) > SIGMIN)	||
			    (*(V + 30 + v + 2) > SIGMIN))) अणु
			/* (हाल 4) */
			अगर (*(V + 30 + v + 1) >= *(V + 30 + v + 2)) अणु
				swp_freq = fOSC * 1000 + afcex_freq + swp_ofs;
				*SIG1 = *(V + 30 + v + 1);
			पूर्ण अन्यथा अणु
				swp_freq = fOSC * 1000 + afcex_freq + swp_ofs * 2;
				*SIG1 = *(V + 30 + v + 2);
			पूर्ण
		पूर्ण अन्यथा अगर ((*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v + 1) >= 0)		&&
			   (*(V + 30 + v + 2) >= 0)		&&
			   (*(V + 30 + v + 3) >= 0)		&&
			   (*(V + 30 + v) > *(V + 30 + v + 2))	&&
			   (*(V + 30 + v + 1) > *(V + 30 + v + 2)) &&
			   (*(V + 30 + v) > *(V + 30 + v + 3))	&&
			   (*(V + 30 + v + 1) > *(V + 30 + v + 3)) &&
			   ((*(V + 30 + v) > SIGMIN)		||
			    (*(V + 30 + v + 1) > SIGMIN))) अणु
			/* (हाल 5) */
			अगर (*(V + 30 + v) >= *(V + 30 + v + 1)) अणु
				swp_freq = fOSC * 1000 + afcex_freq;
				*SIG1 = *(V + 30 + v);
			पूर्ण अन्यथा अणु
				swp_freq = fOSC * 1000 + afcex_freq + swp_ofs;
				*SIG1 = *(V + 30 + v + 1);
			पूर्ण
		पूर्ण अन्यथा अगर ((v + 2 == vmin)			&&
			   (*(V + 30 + v) >= 0)			&&
			   (*(V + 30 + v + 1) >= 0)		&&
			   (*(V + 30 + v + 2) >= 0)		&&
			   (*(V + 30 + v + 1) > *(V + 30 + v))	&&
			   (*(V + 30 + v + 2) > *(V + 30 + v))	&&
			   ((*(V + 30 + v + 1) > SIGMIN)	||
			    (*(V + 30 + v + 2) > SIGMIN))) अणु
			/* (हाल 6) */
			अगर (*(V + 30 + v + 1) >= *(V + 30 + v + 2)) अणु
				swp_freq = fOSC * 1000 + afcex_freq + swp_ofs;
				*SIG1 = *(V + 30 + v + 1);
			पूर्ण अन्यथा अणु
				swp_freq = fOSC * 1000 + afcex_freq + swp_ofs * 2;
				*SIG1 = *(V + 30 + v + 2);
			पूर्ण
		पूर्ण अन्यथा अगर ((vmax == 0) && (vmin == 0) && (*(V + 30 + v) > SIGMIN)) अणु
			swp_freq = fOSC * 1000;
			*SIG1 = *(V + 30 + v);
		पूर्ण अन्यथा
			swp_freq = -1;
	पूर्ण अन्यथा
		swp_freq = -1;

	वापस swp_freq;
पूर्ण

अटल व्योम swp_info_get2(काष्ठा mb86a16_state *state,
			  पूर्णांक smrt,
			  पूर्णांक R,
			  पूर्णांक swp_freq,
			  पूर्णांक *afcex_freq,
			  पूर्णांक *fOSC,
			  अचिन्हित अक्षर *AFCEX_L,
			  अचिन्हित अक्षर *AFCEX_H)
अणु
	पूर्णांक AFCEX ;

	अगर (R == 0)
		*fOSC = (swp_freq + 1000) / 2000 * 2;
	अन्यथा
		*fOSC = (swp_freq + 500) / 1000;

	अगर (*fOSC >= swp_freq)
		*afcex_freq = *fOSC * 1000 - swp_freq;
	अन्यथा
		*afcex_freq = swp_freq - *fOSC * 1000;

	AFCEX = *afcex_freq * 8192 / state->master_clk;
	*AFCEX_L =  AFCEX & 0x00ff;
	*AFCEX_H = (AFCEX & 0x0f00) >> 8;
पूर्ण

अटल व्योम afcex_info_get(काष्ठा mb86a16_state *state,
			   पूर्णांक afcex_freq,
			   अचिन्हित अक्षर *AFCEX_L,
			   अचिन्हित अक्षर *AFCEX_H)
अणु
	पूर्णांक AFCEX ;

	AFCEX = afcex_freq * 8192 / state->master_clk;
	*AFCEX_L =  AFCEX & 0x00ff;
	*AFCEX_H = (AFCEX & 0x0f00) >> 8;
पूर्ण

अटल पूर्णांक SEQ_set(काष्ठा mb86a16_state *state, अचिन्हित अक्षर loop)
अणु
	/* SLOCK0 = 0 */
	अगर (mb86a16_ग_लिखो(state, 0x32, 0x02 | (loop << 2)) < 0) अणु
		dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iq_vt_set(काष्ठा mb86a16_state *state, अचिन्हित अक्षर IQINV)
अणु
	/* Viterbi Rate, IQ Settings */
	अगर (mb86a16_ग_लिखो(state, 0x06, 0xdf | (IQINV << 5)) < 0) अणु
		dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक FEC_srst(काष्ठा mb86a16_state *state)
अणु
	अगर (mb86a16_ग_लिखो(state, MB86A16_RESET, 0x02) < 0) अणु
		dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक S2T_set(काष्ठा mb86a16_state *state, अचिन्हित अक्षर S2T)
अणु
	अगर (mb86a16_ग_लिखो(state, 0x34, 0x70 | S2T) < 0) अणु
		dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक S45T_set(काष्ठा mb86a16_state *state, अचिन्हित अक्षर S4T, अचिन्हित अक्षर S5T)
अणु
	अगर (mb86a16_ग_लिखो(state, 0x35, 0x00 | (S5T << 4) | S4T) < 0) अणु
		dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक mb86a16_set_fe(काष्ठा mb86a16_state *state)
अणु
	u8 agcval, cnmval;

	पूर्णांक i, j;
	पूर्णांक fOSC = 0;
	पूर्णांक fOSC_start = 0;
	पूर्णांक रुको_t;
	पूर्णांक fcp;
	पूर्णांक swp_ofs;
	पूर्णांक V[60];
	u8 SIG1MIN;

	अचिन्हित अक्षर CREN, AFCEN, AFCEXEN;
	अचिन्हित अक्षर SIG1;
	अचिन्हित अक्षर TIMINT1, TIMINT2, TIMEXT;
	अचिन्हित अक्षर S0T, S1T;
	अचिन्हित अक्षर S2T;
/*	अचिन्हित अक्षर S2T, S3T; */
	अचिन्हित अक्षर S4T, S5T;
	अचिन्हित अक्षर AFCEX_L, AFCEX_H;
	अचिन्हित अक्षर R;
	अचिन्हित अक्षर VIRM;
	अचिन्हित अक्षर ETH, VIA;
	अचिन्हित अक्षर junk;

	पूर्णांक loop;
	पूर्णांक ftemp;
	पूर्णांक v, vmax, vmin;
	पूर्णांक vmax_his, vmin_his;
	पूर्णांक swp_freq, prev_swp_freq[20];
	पूर्णांक prev_freq_num;
	पूर्णांक संकेत_dupl;
	पूर्णांक afcex_freq;
	पूर्णांक संकेत;
	पूर्णांक afcerr;
	पूर्णांक temp_freq, delta_freq;
	पूर्णांक dagcm[4];
	पूर्णांक smrt_d;
/*	पूर्णांक freq_err; */
	पूर्णांक n;
	पूर्णांक ret = -1;
	पूर्णांक sync;

	dprपूर्णांकk(verbose, MB86A16_INFO, 1, "freq=%d Mhz, symbrt=%d Ksps", state->frequency, state->srate);

	fcp = 3000;
	swp_ofs = state->srate / 4;

	क्रम (i = 0; i < 60; i++)
		V[i] = -1;

	क्रम (i = 0; i < 20; i++)
		prev_swp_freq[i] = 0;

	SIG1MIN = 25;

	क्रम (n = 0; ((n < 3) && (ret == -1)); n++) अणु
		SEQ_set(state, 0);
		iq_vt_set(state, 0);

		CREN = 0;
		AFCEN = 0;
		AFCEXEN = 1;
		TIMINT1 = 0;
		TIMINT2 = 1;
		TIMEXT = 2;
		S1T = 0;
		S0T = 0;

		अगर (initial_set(state) < 0) अणु
			dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "initial set failed");
			वापस -1;
		पूर्ण
		अगर (DAGC_data_set(state, 3, 2) < 0) अणु
			dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "DAGC data set error");
			वापस -1;
		पूर्ण
		अगर (EN_set(state, CREN, AFCEN) < 0) अणु
			dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "EN set error");
			वापस -1; /* (0, 0) */
		पूर्ण
		अगर (AFCEXEN_set(state, AFCEXEN, state->srate) < 0) अणु
			dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "AFCEXEN set error");
			वापस -1; /* (1, smrt) = (1, symbolrate) */
		पूर्ण
		अगर (CNTM_set(state, TIMINT1, TIMINT2, TIMEXT) < 0) अणु
			dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "CNTM set error");
			वापस -1; /* (0, 1, 2) */
		पूर्ण
		अगर (S01T_set(state, S1T, S0T) < 0) अणु
			dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "S01T set error");
			वापस -1; /* (0, 0) */
		पूर्ण
		smrt_info_get(state, state->srate);
		अगर (smrt_set(state, state->srate) < 0) अणु
			dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "smrt info get error");
			वापस -1;
		पूर्ण

		R = vco_dev_get(state, state->srate);
		अगर (R == 1)
			fOSC_start = state->frequency;

		अन्यथा अगर (R == 0) अणु
			अगर (state->frequency % 2 == 0) अणु
				fOSC_start = state->frequency;
			पूर्ण अन्यथा अणु
				fOSC_start = state->frequency + 1;
				अगर (fOSC_start > 2150)
					fOSC_start = state->frequency - 1;
			पूर्ण
		पूर्ण
		loop = 1;
		ftemp = fOSC_start * 1000;
		vmax = 0 ;
		जबतक (loop == 1) अणु
			ftemp = ftemp + swp_ofs;
			vmax++;

			/* Upper bound */
			अगर (ftemp > 2150000) अणु
				loop = 0;
				vmax--;
			पूर्ण अन्यथा अणु
				अगर ((ftemp == 2150000) ||
				    (ftemp - state->frequency * 1000 >= fcp + state->srate / 4))
					loop = 0;
			पूर्ण
		पूर्ण

		loop = 1;
		ftemp = fOSC_start * 1000;
		vmin = 0 ;
		जबतक (loop == 1) अणु
			ftemp = ftemp - swp_ofs;
			vmin--;

			/* Lower bound */
			अगर (ftemp < 950000) अणु
				loop = 0;
				vmin++;
			पूर्ण अन्यथा अणु
				अगर ((ftemp == 950000) ||
				    (state->frequency * 1000 - ftemp >= fcp + state->srate / 4))
					loop = 0;
			पूर्ण
		पूर्ण

		रुको_t = (8000 + state->srate / 2) / state->srate;
		अगर (रुको_t == 0)
			रुको_t = 1;

		i = 0;
		j = 0;
		prev_freq_num = 0;
		loop = 1;
		संकेत = 0;
		vmax_his = 0;
		vmin_his = 0;
		v = 0;

		जबतक (loop == 1) अणु
			swp_info_get(state, fOSC_start, state->srate,
				     v, R, swp_ofs, &fOSC,
				     &afcex_freq, &AFCEX_L, &AFCEX_H);

			udelay(100);
			अगर (rf_val_set(state, fOSC, state->srate, R) < 0) अणु
				dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "rf val set error");
				वापस -1;
			पूर्ण
			udelay(100);
			अगर (afcex_data_set(state, AFCEX_L, AFCEX_H) < 0) अणु
				dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "afcex data set error");
				वापस -1;
			पूर्ण
			अगर (srst(state) < 0) अणु
				dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "srst error");
				वापस -1;
			पूर्ण
			msleep_पूर्णांकerruptible(रुको_t);

			अगर (mb86a16_पढ़ो(state, 0x37, &SIG1) != 2) अणु
				dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
				वापस -1;
			पूर्ण
			V[30 + v] = SIG1 ;
			swp_freq = swp_freq_calcuation(state, i, v, V, vmax, vmin,
						      SIG1MIN, fOSC, afcex_freq,
						      swp_ofs, &SIG1);	/* changed */

			संकेत_dupl = 0;
			क्रम (j = 0; j < prev_freq_num; j++) अणु
				अगर ((असल(prev_swp_freq[j] - swp_freq)) < (swp_ofs * 3 / 2)) अणु
					संकेत_dupl = 1;
					dprपूर्णांकk(verbose, MB86A16_INFO, 1, "Probably Duplicate Signal, j = %d", j);
				पूर्ण
			पूर्ण
			अगर ((संकेत_dupl == 0) && (swp_freq > 0) && (असल(swp_freq - state->frequency * 1000) < fcp + state->srate / 6)) अणु
				dprपूर्णांकk(verbose, MB86A16_DEBUG, 1, "------ Signal detect ------ [swp_freq=[%07d, srate=%05d]]", swp_freq, state->srate);
				prev_swp_freq[prev_freq_num] = swp_freq;
				prev_freq_num++;
				swp_info_get2(state, state->srate, R, swp_freq,
					      &afcex_freq, &fOSC,
					      &AFCEX_L, &AFCEX_H);

				अगर (rf_val_set(state, fOSC, state->srate, R) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "rf val set error");
					वापस -1;
				पूर्ण
				अगर (afcex_data_set(state, AFCEX_L, AFCEX_H) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "afcex data set error");
					वापस -1;
				पूर्ण
				संकेत = संकेत_det(state, state->srate, &SIG1);
				अगर (संकेत == 1) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "***** Signal Found *****");
					loop = 0;
				पूर्ण अन्यथा अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "!!!!! No signal !!!!!, try again...");
					smrt_info_get(state, state->srate);
					अगर (smrt_set(state, state->srate) < 0) अणु
						dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "smrt set error");
						वापस -1;
					पूर्ण
				पूर्ण
			पूर्ण
			अगर (v > vmax)
				vmax_his = 1 ;
			अगर (v < vmin)
				vmin_his = 1 ;
			i++;

			अगर ((i % 2 == 1) && (vmax_his == 1))
				i++;
			अगर ((i % 2 == 0) && (vmin_his == 1))
				i++;

			अगर (i % 2 == 1)
				v = (i + 1) / 2;
			अन्यथा
				v = -i / 2;

			अगर ((vmax_his == 1) && (vmin_his == 1))
				loop = 0 ;
		पूर्ण

		अगर (संकेत == 1) अणु
			dprपूर्णांकk(verbose, MB86A16_INFO, 1, " Start Freq Error Check");
			S1T = 7 ;
			S0T = 1 ;
			CREN = 0 ;
			AFCEN = 1 ;
			AFCEXEN = 0 ;

			अगर (S01T_set(state, S1T, S0T) < 0) अणु
				dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "S01T set error");
				वापस -1;
			पूर्ण
			smrt_info_get(state, state->srate);
			अगर (smrt_set(state, state->srate) < 0) अणु
				dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "smrt set error");
				वापस -1;
			पूर्ण
			अगर (EN_set(state, CREN, AFCEN) < 0) अणु
				dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "EN set error");
				वापस -1;
			पूर्ण
			अगर (AFCEXEN_set(state, AFCEXEN, state->srate) < 0) अणु
				dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "AFCEXEN set error");
				वापस -1;
			पूर्ण
			afcex_info_get(state, afcex_freq, &AFCEX_L, &AFCEX_H);
			अगर (afcofs_data_set(state, AFCEX_L, AFCEX_H) < 0) अणु
				dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "AFCOFS data set error");
				वापस -1;
			पूर्ण
			अगर (srst(state) < 0) अणु
				dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "srst error");
				वापस -1;
			पूर्ण
			/* delay 4~200 */
			रुको_t = 200000 / state->master_clk + 200000 / state->srate;
			msleep(रुको_t);
			afcerr = afcerr_chk(state);
			अगर (afcerr == -1)
				वापस -1;

			swp_freq = fOSC * 1000 + afcerr ;
			AFCEXEN = 1 ;
			अगर (state->srate >= 1500)
				smrt_d = state->srate / 3;
			अन्यथा
				smrt_d = state->srate / 2;
			smrt_info_get(state, smrt_d);
			अगर (smrt_set(state, smrt_d) < 0) अणु
				dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "smrt set error");
				वापस -1;
			पूर्ण
			अगर (AFCEXEN_set(state, AFCEXEN, smrt_d) < 0) अणु
				dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "AFCEXEN set error");
				वापस -1;
			पूर्ण
			R = vco_dev_get(state, smrt_d);
			अगर (DAGC_data_set(state, 2, 0) < 0) अणु
				dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "DAGC data set error");
				वापस -1;
			पूर्ण
			क्रम (i = 0; i < 3; i++) अणु
				temp_freq = swp_freq + (i - 1) * state->srate / 8;
				swp_info_get2(state, smrt_d, R, temp_freq, &afcex_freq, &fOSC, &AFCEX_L, &AFCEX_H);
				अगर (rf_val_set(state, fOSC, smrt_d, R) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "rf val set error");
					वापस -1;
				पूर्ण
				अगर (afcex_data_set(state, AFCEX_L, AFCEX_H) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "afcex data set error");
					वापस -1;
				पूर्ण
				रुको_t = 200000 / state->master_clk + 40000 / smrt_d;
				msleep(रुको_t);
				dagcm[i] = dagcm_val_get(state);
			पूर्ण
			अगर ((dagcm[0] > dagcm[1]) &&
			    (dagcm[0] > dagcm[2]) &&
			    (dagcm[0] - dagcm[1] > 2 * (dagcm[2] - dagcm[1]))) अणु

				temp_freq = swp_freq - 2 * state->srate / 8;
				swp_info_get2(state, smrt_d, R, temp_freq, &afcex_freq, &fOSC, &AFCEX_L, &AFCEX_H);
				अगर (rf_val_set(state, fOSC, smrt_d, R) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "rf val set error");
					वापस -1;
				पूर्ण
				अगर (afcex_data_set(state, AFCEX_L, AFCEX_H) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "afcex data set");
					वापस -1;
				पूर्ण
				रुको_t = 200000 / state->master_clk + 40000 / smrt_d;
				msleep(रुको_t);
				dagcm[3] = dagcm_val_get(state);
				अगर (dagcm[3] > dagcm[1])
					delta_freq = (dagcm[2] - dagcm[0] + dagcm[1] - dagcm[3]) * state->srate / 300;
				अन्यथा
					delta_freq = 0;
			पूर्ण अन्यथा अगर ((dagcm[2] > dagcm[1]) &&
				   (dagcm[2] > dagcm[0]) &&
				   (dagcm[2] - dagcm[1] > 2 * (dagcm[0] - dagcm[1]))) अणु

				temp_freq = swp_freq + 2 * state->srate / 8;
				swp_info_get2(state, smrt_d, R, temp_freq, &afcex_freq, &fOSC, &AFCEX_L, &AFCEX_H);
				अगर (rf_val_set(state, fOSC, smrt_d, R) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "rf val set");
					वापस -1;
				पूर्ण
				अगर (afcex_data_set(state, AFCEX_L, AFCEX_H) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "afcex data set");
					वापस -1;
				पूर्ण
				रुको_t = 200000 / state->master_clk + 40000 / smrt_d;
				msleep(रुको_t);
				dagcm[3] = dagcm_val_get(state);
				अगर (dagcm[3] > dagcm[1])
					delta_freq = (dagcm[2] - dagcm[0] + dagcm[3] - dagcm[1]) * state->srate / 300;
				अन्यथा
					delta_freq = 0 ;

			पूर्ण अन्यथा अणु
				delta_freq = 0 ;
			पूर्ण
			dprपूर्णांकk(verbose, MB86A16_INFO, 1, "SWEEP Frequency = %d", swp_freq);
			swp_freq += delta_freq;
			dprपूर्णांकk(verbose, MB86A16_INFO, 1, "Adjusting .., DELTA Freq = %d, SWEEP Freq=%d", delta_freq, swp_freq);
			अगर (असल(state->frequency * 1000 - swp_freq) > 3800) अणु
				dprपूर्णांकk(verbose, MB86A16_INFO, 1, "NO  --  SIGNAL !");
			पूर्ण अन्यथा अणु

				S1T = 0;
				S0T = 3;
				CREN = 1;
				AFCEN = 0;
				AFCEXEN = 1;

				अगर (S01T_set(state, S1T, S0T) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "S01T set error");
					वापस -1;
				पूर्ण
				अगर (DAGC_data_set(state, 0, 0) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "DAGC data set error");
					वापस -1;
				पूर्ण
				R = vco_dev_get(state, state->srate);
				smrt_info_get(state, state->srate);
				अगर (smrt_set(state, state->srate) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "smrt set error");
					वापस -1;
				पूर्ण
				अगर (EN_set(state, CREN, AFCEN) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "EN set error");
					वापस -1;
				पूर्ण
				अगर (AFCEXEN_set(state, AFCEXEN, state->srate) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "AFCEXEN set error");
					वापस -1;
				पूर्ण
				swp_info_get2(state, state->srate, R, swp_freq, &afcex_freq, &fOSC, &AFCEX_L, &AFCEX_H);
				अगर (rf_val_set(state, fOSC, state->srate, R) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "rf val set error");
					वापस -1;
				पूर्ण
				अगर (afcex_data_set(state, AFCEX_L, AFCEX_H) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "afcex data set error");
					वापस -1;
				पूर्ण
				अगर (srst(state) < 0) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "srst error");
					वापस -1;
				पूर्ण
				रुको_t = 7 + (10000 + state->srate / 2) / state->srate;
				अगर (रुको_t == 0)
					रुको_t = 1;
				msleep_पूर्णांकerruptible(रुको_t);
				अगर (mb86a16_पढ़ो(state, 0x37, &SIG1) != 2) अणु
					dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
					वापस -EREMOTEIO;
				पूर्ण

				अगर (SIG1 > 110) अणु
					S2T = 4; S4T = 1; S5T = 6; ETH = 4; VIA = 6;
					रुको_t = 7 + (917504 + state->srate / 2) / state->srate;
				पूर्ण अन्यथा अगर (SIG1 > 105) अणु
					S2T = 4; S4T = 2; S5T = 8; ETH = 7; VIA = 2;
					रुको_t = 7 + (1048576 + state->srate / 2) / state->srate;
				पूर्ण अन्यथा अगर (SIG1 > 85) अणु
					S2T = 5; S4T = 2; S5T = 8; ETH = 7; VIA = 2;
					रुको_t = 7 + (1310720 + state->srate / 2) / state->srate;
				पूर्ण अन्यथा अगर (SIG1 > 65) अणु
					S2T = 6; S4T = 2; S5T = 8; ETH = 7; VIA = 2;
					रुको_t = 7 + (1572864 + state->srate / 2) / state->srate;
				पूर्ण अन्यथा अणु
					S2T = 7; S4T = 2; S5T = 8; ETH = 7; VIA = 2;
					रुको_t = 7 + (2097152 + state->srate / 2) / state->srate;
				पूर्ण
				रुको_t *= 2; /* FOS */
				S2T_set(state, S2T);
				S45T_set(state, S4T, S5T);
				Vi_set(state, ETH, VIA);
				srst(state);
				msleep_पूर्णांकerruptible(रुको_t);
				sync = sync_chk(state, &VIRM);
				dprपूर्णांकk(verbose, MB86A16_INFO, 1, "-------- Viterbi=[%d] SYNC=[%d] ---------", VIRM, sync);
				अगर (VIRM) अणु
					अगर (VIRM == 4) अणु
						/* 5/6 */
						अगर (SIG1 > 110)
							रुको_t = (786432 + state->srate / 2) / state->srate;
						अन्यथा
							रुको_t = (1572864 + state->srate / 2) / state->srate;

						msleep_पूर्णांकerruptible(रुको_t);

						अगर (sync_chk(state, &junk) == 0) अणु
							iq_vt_set(state, 1);
							FEC_srst(state);
						पूर्ण
					पूर्ण
					/* 1/2, 2/3, 3/4, 7/8 */
					अगर (SIG1 > 110)
						रुको_t = (786432 + state->srate / 2) / state->srate;
					अन्यथा
						रुको_t = (1572864 + state->srate / 2) / state->srate;
					msleep_पूर्णांकerruptible(रुको_t);
					SEQ_set(state, 1);
				पूर्ण अन्यथा अणु
					dprपूर्णांकk(verbose, MB86A16_INFO, 1, "NO  -- SYNC");
					SEQ_set(state, 1);
					ret = -1;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			dprपूर्णांकk(verbose, MB86A16_INFO, 1, "NO  -- SIGNAL");
			ret = -1;
		पूर्ण

		sync = sync_chk(state, &junk);
		अगर (sync) अणु
			dprपूर्णांकk(verbose, MB86A16_INFO, 1, "******* SYNC *******");
			freqerr_chk(state, state->frequency, state->srate, 1);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	mb86a16_पढ़ो(state, 0x15, &agcval);
	mb86a16_पढ़ो(state, 0x26, &cnmval);
	dprपूर्णांकk(verbose, MB86A16_INFO, 1, "AGC = %02x CNM = %02x", agcval, cnmval);

	वापस ret;
पूर्ण

अटल पूर्णांक mb86a16_send_diseqc_msg(काष्ठा dvb_frontend *fe,
				   काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	काष्ठा mb86a16_state *state = fe->demodulator_priv;
	पूर्णांक i;
	u8 regs;

	अगर (mb86a16_ग_लिखो(state, MB86A16_DCC1, MB86A16_DCC1_DISTA) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, MB86A16_DCCOUT, 0x00) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, MB86A16_TONEOUT2, 0x04) < 0)
		जाओ err;

	regs = 0x18;

	अगर (cmd->msg_len > 5 || cmd->msg_len < 4)
		वापस -EINVAL;

	क्रम (i = 0; i < cmd->msg_len; i++) अणु
		अगर (mb86a16_ग_लिखो(state, regs, cmd->msg[i]) < 0)
			जाओ err;

		regs++;
	पूर्ण
	i += 0x90;

	msleep_पूर्णांकerruptible(10);

	अगर (mb86a16_ग_लिखो(state, MB86A16_DCC1, i) < 0)
		जाओ err;
	अगर (mb86a16_ग_लिखो(state, MB86A16_DCCOUT, MB86A16_DCCOUT_DISEN) < 0)
		जाओ err;

	वापस 0;

err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल पूर्णांक mb86a16_send_diseqc_burst(काष्ठा dvb_frontend *fe,
				     क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा mb86a16_state *state = fe->demodulator_priv;

	चयन (burst) अणु
	हाल SEC_MINI_A:
		अगर (mb86a16_ग_लिखो(state, MB86A16_DCC1, MB86A16_DCC1_DISTA |
						       MB86A16_DCC1_TBEN  |
						       MB86A16_DCC1_TBO) < 0)
			जाओ err;
		अगर (mb86a16_ग_लिखो(state, MB86A16_DCCOUT, MB86A16_DCCOUT_DISEN) < 0)
			जाओ err;
		अवरोध;
	हाल SEC_MINI_B:
		अगर (mb86a16_ग_लिखो(state, MB86A16_DCC1, MB86A16_DCC1_DISTA |
						       MB86A16_DCC1_TBEN) < 0)
			जाओ err;
		अगर (mb86a16_ग_लिखो(state, MB86A16_DCCOUT, MB86A16_DCCOUT_DISEN) < 0)
			जाओ err;
		अवरोध;
	पूर्ण

	वापस 0;
err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल पूर्णांक mb86a16_set_tone(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा mb86a16_state *state = fe->demodulator_priv;

	चयन (tone) अणु
	हाल SEC_TONE_ON:
		अगर (mb86a16_ग_लिखो(state, MB86A16_TONEOUT2, 0x00) < 0)
			जाओ err;
		अगर (mb86a16_ग_लिखो(state, MB86A16_DCC1, MB86A16_DCC1_DISTA |
						       MB86A16_DCC1_CTOE) < 0)

			जाओ err;
		अगर (mb86a16_ग_लिखो(state, MB86A16_DCCOUT, MB86A16_DCCOUT_DISEN) < 0)
			जाओ err;
		अवरोध;
	हाल SEC_TONE_OFF:
		अगर (mb86a16_ग_लिखो(state, MB86A16_TONEOUT2, 0x04) < 0)
			जाओ err;
		अगर (mb86a16_ग_लिखो(state, MB86A16_DCC1, MB86A16_DCC1_DISTA) < 0)
			जाओ err;
		अगर (mb86a16_ग_लिखो(state, MB86A16_DCCOUT, 0x00) < 0)
			जाओ err;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;

err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल क्रमागत dvbfe_search mb86a16_search(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा mb86a16_state *state = fe->demodulator_priv;

	state->frequency = p->frequency / 1000;
	state->srate = p->symbol_rate / 1000;

	अगर (!mb86a16_set_fe(state)) अणु
		dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "Successfully acquired LOCK");
		वापस DVBFE_ALGO_SEARCH_SUCCESS;
	पूर्ण

	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "Lock acquisition failed!");
	वापस DVBFE_ALGO_SEARCH_FAILED;
पूर्ण

अटल व्योम mb86a16_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mb86a16_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल पूर्णांक mb86a16_init(काष्ठा dvb_frontend *fe)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mb86a16_sleep(काष्ठा dvb_frontend *fe)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mb86a16_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	u8 ber_mon, ber_tab, ber_lsb, ber_mid, ber_msb, ber_tim, ber_rst;
	u32 समयr;

	काष्ठा mb86a16_state *state = fe->demodulator_priv;

	*ber = 0;
	अगर (mb86a16_पढ़ो(state, MB86A16_BERMON, &ber_mon) != 2)
		जाओ err;
	अगर (mb86a16_पढ़ो(state, MB86A16_BERTAB, &ber_tab) != 2)
		जाओ err;
	अगर (mb86a16_पढ़ो(state, MB86A16_BERLSB, &ber_lsb) != 2)
		जाओ err;
	अगर (mb86a16_पढ़ो(state, MB86A16_BERMID, &ber_mid) != 2)
		जाओ err;
	अगर (mb86a16_पढ़ो(state, MB86A16_BERMSB, &ber_msb) != 2)
		जाओ err;
	/* BER monitor invalid when BER_EN = 0	*/
	अगर (ber_mon & 0x04) अणु
		/* coarse, fast calculation	*/
		*ber = ber_tab & 0x1f;
		dprपूर्णांकk(verbose, MB86A16_DEBUG, 1, "BER coarse=[0x%02x]", *ber);
		अगर (ber_mon & 0x01) अणु
			/*
			 * BER_SEL = 1, The monitored BER is the estimated
			 * value with a Reed-Solomon decoder error amount at
			 * the deपूर्णांकerleaver output.
			 * monitored BER is expressed as a 20 bit output in total
			 */
			ber_rst = (ber_mon >> 3) & 0x03;
			*ber = (((ber_msb << 8) | ber_mid) << 8) | ber_lsb;
			अगर (ber_rst == 0)
				समयr =  12500000;
			अन्यथा अगर (ber_rst == 1)
				समयr =  25000000;
			अन्यथा अगर (ber_rst == 2)
				समयr =  50000000;
			अन्यथा /* ber_rst == 3 */
				समयr = 100000000;

			*ber /= समयr;
			dprपूर्णांकk(verbose, MB86A16_DEBUG, 1, "BER fine=[0x%02x]", *ber);
		पूर्ण अन्यथा अणु
			/*
			 * BER_SEL = 0, The monitored BER is the estimated
			 * value with a Viterbi decoder error amount at the
			 * QPSK demodulator output.
			 * monitored BER is expressed as a 24 bit output in total
			 */
			ber_tim = (ber_mon >> 1) & 0x01;
			*ber = (((ber_msb << 8) | ber_mid) << 8) | ber_lsb;
			अगर (ber_tim == 0)
				समयr = 16;
			अन्यथा /* ber_tim == 1 */
				समयr = 24;

			*ber /= 2 ^ समयr;
			dprपूर्णांकk(verbose, MB86A16_DEBUG, 1, "BER fine=[0x%02x]", *ber);
		पूर्ण
	पूर्ण
	वापस 0;
err:
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	वापस -EREMOTEIO;
पूर्ण

अटल पूर्णांक mb86a16_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	u8 agcm = 0;
	काष्ठा mb86a16_state *state = fe->demodulator_priv;

	*strength = 0;
	अगर (mb86a16_पढ़ो(state, MB86A16_AGCM, &agcm) != 2) अणु
		dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
		वापस -EREMOTEIO;
	पूर्ण

	*strength = ((0xff - agcm) * 100) / 256;
	dprपूर्णांकk(verbose, MB86A16_DEBUG, 1, "Signal strength=[%d %%]", (u8) *strength);
	*strength = (0xffff - 0xff) + agcm;

	वापस 0;
पूर्ण

काष्ठा cnr अणु
	u8 cn_reg;
	u8 cn_val;
पूर्ण;

अटल स्थिर काष्ठा cnr cnr_tab[] = अणु
	अणु  35,  2 पूर्ण,
	अणु  40,  3 पूर्ण,
	अणु  50,  4 पूर्ण,
	अणु  60,  5 पूर्ण,
	अणु  70,  6 पूर्ण,
	अणु  80,  7 पूर्ण,
	अणु  92,  8 पूर्ण,
	अणु 103,  9 पूर्ण,
	अणु 115, 10 पूर्ण,
	अणु 138, 12 पूर्ण,
	अणु 162, 15 पूर्ण,
	अणु 180, 18 पूर्ण,
	अणु 185, 19 पूर्ण,
	अणु 189, 20 पूर्ण,
	अणु 195, 22 पूर्ण,
	अणु 199, 24 पूर्ण,
	अणु 201, 25 पूर्ण,
	अणु 202, 26 पूर्ण,
	अणु 203, 27 पूर्ण,
	अणु 205, 28 पूर्ण,
	अणु 208, 30 पूर्ण
पूर्ण;

अटल पूर्णांक mb86a16_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा mb86a16_state *state = fe->demodulator_priv;
	पूर्णांक i = 0;
	पूर्णांक low_tide = 2, high_tide = 30, q_level;
	u8  cn;

	*snr = 0;
	अगर (mb86a16_पढ़ो(state, 0x26, &cn) != 2) अणु
		dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
		वापस -EREMOTEIO;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(cnr_tab); i++) अणु
		अगर (cn < cnr_tab[i].cn_reg) अणु
			*snr = cnr_tab[i].cn_val;
			अवरोध;
		पूर्ण
	पूर्ण
	q_level = (*snr * 100) / (high_tide - low_tide);
	dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "SNR (Quality) = [%d dB], Level=%d %%", *snr, q_level);
	*snr = (0xffff - 0xff) + *snr;

	वापस 0;
पूर्ण

अटल पूर्णांक mb86a16_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	u8 dist;
	काष्ठा mb86a16_state *state = fe->demodulator_priv;

	अगर (mb86a16_पढ़ो(state, MB86A16_DISTMON, &dist) != 2) अणु
		dprपूर्णांकk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
		वापस -EREMOTEIO;
	पूर्ण
	*ucblocks = dist;

	वापस 0;
पूर्ण

अटल क्रमागत dvbfe_algo mb86a16_frontend_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस DVBFE_ALGO_CUSTOM;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops mb86a16_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name			= "Fujitsu MB86A16 DVB-S",
		.frequency_min_hz	=  950 * MHz,
		.frequency_max_hz	= 2150 * MHz,
		.frequency_stepsize_hz	=    3 * MHz,
		.symbol_rate_min	= 1000000,
		.symbol_rate_max	= 45000000,
		.symbol_rate_tolerance	= 500,
		.caps			= FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 |
					  FE_CAN_FEC_3_4 | FE_CAN_FEC_5_6 |
					  FE_CAN_FEC_7_8 | FE_CAN_QPSK    |
					  FE_CAN_FEC_AUTO
	पूर्ण,
	.release			= mb86a16_release,

	.get_frontend_algo		= mb86a16_frontend_algo,
	.search				= mb86a16_search,
	.init				= mb86a16_init,
	.sleep				= mb86a16_sleep,
	.पढ़ो_status			= mb86a16_पढ़ो_status,

	.पढ़ो_ber			= mb86a16_पढ़ो_ber,
	.पढ़ो_संकेत_strength		= mb86a16_पढ़ो_संकेत_strength,
	.पढ़ो_snr			= mb86a16_पढ़ो_snr,
	.पढ़ो_ucblocks			= mb86a16_पढ़ो_ucblocks,

	.diseqc_send_master_cmd		= mb86a16_send_diseqc_msg,
	.diseqc_send_burst		= mb86a16_send_diseqc_burst,
	.set_tone			= mb86a16_set_tone,
पूर्ण;

काष्ठा dvb_frontend *mb86a16_attach(स्थिर काष्ठा mb86a16_config *config,
				    काष्ठा i2c_adapter *i2c_adap)
अणु
	u8 dev_id = 0;
	काष्ठा mb86a16_state *state = शून्य;

	state = kदो_स्मृति(माप(काष्ठा mb86a16_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	state->config = config;
	state->i2c_adap = i2c_adap;

	mb86a16_पढ़ो(state, 0x7f, &dev_id);
	अगर (dev_id != 0xfe)
		जाओ error;

	स_नकल(&state->frontend.ops, &mb86a16_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	state->frontend.ops.set_voltage = state->config->set_voltage;

	वापस &state->frontend;
error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mb86a16_attach);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manu Abraham");
