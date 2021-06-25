<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Linux driver क्रम digital TV devices equipped with B2C2 FlexcopII(b)/III
 * flexcop-i2c.c - flexcop पूर्णांकernal 2Wire bus (I2C) and dvb i2c initialization
 * see flexcop.c क्रम copyright inक्रमmation
 */
#समावेश "flexcop.h"

#घोषणा FC_MAX_I2C_RETRIES 100000

अटल पूर्णांक flexcop_i2c_operation(काष्ठा flexcop_device *fc,
		flexcop_ibi_value *r100)
अणु
	पूर्णांक i;
	flexcop_ibi_value r;

	r100->tw_sm_c_100.working_start = 1;
	deb_i2c("r100 before: %08x\n",r100->raw);

	fc->ग_लिखो_ibi_reg(fc, tw_sm_c_100, ibi_zero);
	fc->ग_लिखो_ibi_reg(fc, tw_sm_c_100, *r100); /* initiating i2c operation */

	क्रम (i = 0; i < FC_MAX_I2C_RETRIES; i++) अणु
		r = fc->पढ़ो_ibi_reg(fc, tw_sm_c_100);

		अगर (!r.tw_sm_c_100.no_base_addr_ack_error) अणु
			अगर (r.tw_sm_c_100.st_करोne) अणु
				*r100 = r;
				deb_i2c("i2c success\n");
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			deb_i2c("suffering from an i2c ack_error\n");
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण
	deb_i2c("tried %d times i2c operation, never finished or too many ack errors.\n",
		i);
	वापस -EREMOTEIO;
पूर्ण

अटल पूर्णांक flexcop_i2c_पढ़ो4(काष्ठा flexcop_i2c_adapter *i2c,
		flexcop_ibi_value r100, u8 *buf)
अणु
	flexcop_ibi_value r104;
	पूर्णांक len = r100.tw_sm_c_100.total_bytes,
		/* remember total_bytes is buflen-1 */
		ret;

	/* work-around to have CableStar2 and SkyStar2 rev 2.7 work
	 * correctly:
	 *
	 * the ITD1000 is behind an i2c-gate which बंदs स्वतःmatically
	 * after an i2c-transaction the STV0297 needs 2 consecutive पढ़ोs
	 * one with no_base_addr = 0 and one with 1
	 *
	 * those two work-arounds are conflictin: we check क्रम the card
	 * type, it is set when probing the ITD1000 */
	अगर (i2c->fc->dev_type == FC_SKY_REV27)
		r100.tw_sm_c_100.no_base_addr_ack_error = i2c->no_base_addr;

	ret = flexcop_i2c_operation(i2c->fc, &r100);
	अगर (ret != 0) अणु
		deb_i2c("Retrying operation\n");
		r100.tw_sm_c_100.no_base_addr_ack_error = i2c->no_base_addr;
		ret = flexcop_i2c_operation(i2c->fc, &r100);
	पूर्ण
	अगर (ret != 0) अणु
		deb_i2c("read failed. %d\n", ret);
		वापस ret;
	पूर्ण

	buf[0] = r100.tw_sm_c_100.data1_reg;

	अगर (len > 0) अणु
		r104 = i2c->fc->पढ़ो_ibi_reg(i2c->fc, tw_sm_c_104);
		deb_i2c("read: r100: %08x, r104: %08x\n", r100.raw, r104.raw);

		/* there is at least one more byte, otherwise we wouldn't be here */
		buf[1] = r104.tw_sm_c_104.data2_reg;
		अगर (len > 1) buf[2] = r104.tw_sm_c_104.data3_reg;
		अगर (len > 2) buf[3] = r104.tw_sm_c_104.data4_reg;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक flexcop_i2c_ग_लिखो4(काष्ठा flexcop_device *fc,
		flexcop_ibi_value r100, u8 *buf)
अणु
	flexcop_ibi_value r104;
	पूर्णांक len = r100.tw_sm_c_100.total_bytes; /* remember total_bytes is buflen-1 */
	r104.raw = 0;

	/* there is at least one byte, otherwise we wouldn't be here */
	r100.tw_sm_c_100.data1_reg = buf[0];
	r104.tw_sm_c_104.data2_reg = len > 0 ? buf[1] : 0;
	r104.tw_sm_c_104.data3_reg = len > 1 ? buf[2] : 0;
	r104.tw_sm_c_104.data4_reg = len > 2 ? buf[3] : 0;

	deb_i2c("write: r100: %08x, r104: %08x\n", r100.raw, r104.raw);

	/* ग_लिखो the additional i2c data beक्रमe करोing the actual i2c operation */
	fc->ग_लिखो_ibi_reg(fc, tw_sm_c_104, r104);
	वापस flexcop_i2c_operation(fc, &r100);
पूर्ण

पूर्णांक flexcop_i2c_request(काष्ठा flexcop_i2c_adapter *i2c,
			flexcop_access_op_t op, u8 chipaddr,
			u8 start_addr, u8 *buf, u16 size)
अणु
	पूर्णांक ret;
	पूर्णांक len = size;
	u8 *p;
	u8 addr = start_addr;

	u16 bytes_to_transfer;
	flexcop_ibi_value r100;

	deb_i2c("port %d %s(%02x): register %02x, size: %d\n",
		i2c->port,
		op == FC_READ ? "rd" : "wr",
		chipaddr, start_addr, size);
	r100.raw = 0;
	r100.tw_sm_c_100.chipaddr = chipaddr;
	r100.tw_sm_c_100.twoWS_rw = op;
	r100.tw_sm_c_100.twoWS_port_reg = i2c->port;

	/* in that हाल addr is the only value ->
	 * we ग_लिखो it twice as baseaddr and val0
	 * BBTI is करोing it like that क्रम ISL6421 at least */
	अगर (i2c->no_base_addr && len == 0 && op == FC_WRITE) अणु
		buf = &start_addr;
		len = 1;
	पूर्ण

	p = buf;

	जबतक (len != 0) अणु
		bytes_to_transfer = len > 4 ? 4 : len;

		r100.tw_sm_c_100.total_bytes = bytes_to_transfer - 1;
		r100.tw_sm_c_100.baseaddr = addr;

		अगर (op == FC_READ)
			ret = flexcop_i2c_पढ़ो4(i2c, r100, p);
		अन्यथा
			ret = flexcop_i2c_ग_लिखो4(i2c->fc, r100, p);

		अगर (ret < 0)
			वापस ret;

		p  += bytes_to_transfer;
		addr += bytes_to_transfer;
		len  -= bytes_to_transfer;
	पूर्ण
	deb_i2c_dump("port %d %s(%02x): register %02x: %*ph\n",
		i2c->port,
		op == FC_READ ? "rd" : "wr",
		chipaddr, start_addr, size, buf);

	वापस 0;
पूर्ण
/* exported क्रम PCI i2c */
EXPORT_SYMBOL(flexcop_i2c_request);

/* master xfer callback क्रम demodulator */
अटल पूर्णांक flexcop_master_xfer(काष्ठा i2c_adapter *i2c_adap,
		काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा flexcop_i2c_adapter *i2c = i2c_get_adapdata(i2c_adap);
	पूर्णांक i, ret = 0;

	/* Some drivers use 1 byte or 0 byte पढ़ोs as probes, which this
	 * driver करोesn't support.  These probes will always fail, so this
	 * hack makes them always succeed.  If one knew how, it would of
	 * course be better to actually करो the पढ़ो.  */
	अगर (num == 1 && msgs[0].flags == I2C_M_RD && msgs[0].len <= 1)
		वापस 1;

	अगर (mutex_lock_पूर्णांकerruptible(&i2c->fc->i2c_mutex))
		वापस -ERESTARTSYS;

	क्रम (i = 0; i < num; i++) अणु
		/* पढ़ोing */
		अगर (i+1 < num && (msgs[i+1].flags == I2C_M_RD)) अणु
			ret = i2c->fc->i2c_request(i2c, FC_READ, msgs[i].addr,
					msgs[i].buf[0], msgs[i+1].buf,
					msgs[i+1].len);
			i++; /* skip the following message */
		पूर्ण अन्यथा /* writing */
			ret = i2c->fc->i2c_request(i2c, FC_WRITE, msgs[i].addr,
					msgs[i].buf[0], &msgs[i].buf[1],
					msgs[i].len - 1);
		अगर (ret < 0) अणु
			deb_i2c("i2c master_xfer failed");
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&i2c->fc->i2c_mutex);

	अगर (ret == 0)
		ret = num;
	वापस ret;
पूर्ण

अटल u32 flexcop_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm flexcop_algo = अणु
	.master_xfer	= flexcop_master_xfer,
	.functionality	= flexcop_i2c_func,
पूर्ण;

पूर्णांक flexcop_i2c_init(काष्ठा flexcop_device *fc)
अणु
	पूर्णांक ret;
	mutex_init(&fc->i2c_mutex);

	fc->fc_i2c_adap[0].fc = fc;
	fc->fc_i2c_adap[1].fc = fc;
	fc->fc_i2c_adap[2].fc = fc;
	fc->fc_i2c_adap[0].port = FC_I2C_PORT_DEMOD;
	fc->fc_i2c_adap[1].port = FC_I2C_PORT_EEPROM;
	fc->fc_i2c_adap[2].port = FC_I2C_PORT_TUNER;

	strscpy(fc->fc_i2c_adap[0].i2c_adap.name, "B2C2 FlexCop I2C to demod",
		माप(fc->fc_i2c_adap[0].i2c_adap.name));
	strscpy(fc->fc_i2c_adap[1].i2c_adap.name, "B2C2 FlexCop I2C to eeprom",
		माप(fc->fc_i2c_adap[1].i2c_adap.name));
	strscpy(fc->fc_i2c_adap[2].i2c_adap.name, "B2C2 FlexCop I2C to tuner",
		माप(fc->fc_i2c_adap[2].i2c_adap.name));

	i2c_set_adapdata(&fc->fc_i2c_adap[0].i2c_adap, &fc->fc_i2c_adap[0]);
	i2c_set_adapdata(&fc->fc_i2c_adap[1].i2c_adap, &fc->fc_i2c_adap[1]);
	i2c_set_adapdata(&fc->fc_i2c_adap[2].i2c_adap, &fc->fc_i2c_adap[2]);

	fc->fc_i2c_adap[0].i2c_adap.algo =
		fc->fc_i2c_adap[1].i2c_adap.algo =
		fc->fc_i2c_adap[2].i2c_adap.algo = &flexcop_algo;
	fc->fc_i2c_adap[0].i2c_adap.algo_data =
		fc->fc_i2c_adap[1].i2c_adap.algo_data =
		fc->fc_i2c_adap[2].i2c_adap.algo_data = शून्य;
	fc->fc_i2c_adap[0].i2c_adap.dev.parent =
		fc->fc_i2c_adap[1].i2c_adap.dev.parent =
		fc->fc_i2c_adap[2].i2c_adap.dev.parent = fc->dev;

	ret = i2c_add_adapter(&fc->fc_i2c_adap[0].i2c_adap);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_add_adapter(&fc->fc_i2c_adap[1].i2c_adap);
	अगर (ret < 0)
		जाओ adap_1_failed;

	ret = i2c_add_adapter(&fc->fc_i2c_adap[2].i2c_adap);
	अगर (ret < 0)
		जाओ adap_2_failed;

	fc->init_state |= FC_STATE_I2C_INIT;
	वापस 0;

adap_2_failed:
	i2c_del_adapter(&fc->fc_i2c_adap[1].i2c_adap);
adap_1_failed:
	i2c_del_adapter(&fc->fc_i2c_adap[0].i2c_adap);
	वापस ret;
पूर्ण

व्योम flexcop_i2c_निकास(काष्ठा flexcop_device *fc)
अणु
	अगर (fc->init_state & FC_STATE_I2C_INIT) अणु
		i2c_del_adapter(&fc->fc_i2c_adap[2].i2c_adap);
		i2c_del_adapter(&fc->fc_i2c_adap[1].i2c_adap);
		i2c_del_adapter(&fc->fc_i2c_adap[0].i2c_adap);
	पूर्ण
	fc->init_state &= ~FC_STATE_I2C_INIT;
पूर्ण
