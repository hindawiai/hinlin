<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * device driver क्रम Conexant 2388x based TV cards
 * MPEG Transport Stream (DVB) routines
 *
 * (c) 2004, 2005 Chris Pascoe <c.pascoe@itee.uq.edu.au>
 * (c) 2004 Gerd Knorr <kraxel@bytesex.org> [SuSE Lअसल]
 */

#समावेश "cx88.h"
#समावेश "dvb-pll.h"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/file.h>
#समावेश <linux/suspend.h>

#समावेश <media/v4l2-common.h>

#समावेश "mt352.h"
#समावेश "mt352_priv.h"
#समावेश "cx88-vp3054-i2c.h"
#समावेश "zl10353.h"
#समावेश "cx22702.h"
#समावेश "or51132.h"
#समावेश "lgdt330x.h"
#समावेश "s5h1409.h"
#समावेश "xc4000.h"
#समावेश "xc5000.h"
#समावेश "nxt200x.h"
#समावेश "cx24123.h"
#समावेश "isl6421.h"
#समावेश "tuner-simple.h"
#समावेश "tda9887.h"
#समावेश "s5h1411.h"
#समावेश "stv0299.h"
#समावेश "z0194a.h"
#समावेश "stv0288.h"
#समावेश "stb6000.h"
#समावेश "cx24116.h"
#समावेश "stv0900.h"
#समावेश "stb6100.h"
#समावेश "stb6100_proc.h"
#समावेश "mb86a16.h"
#समावेश "ts2020.h"
#समावेश "ds3000.h"

MODULE_DESCRIPTION("driver for cx2388x based DVB cards");
MODULE_AUTHOR("Chris Pascoe <c.pascoe@itee.uq.edu.au>");
MODULE_AUTHOR("Gerd Knorr <kraxel@bytesex.org> [SuSE Labs]");
MODULE_LICENSE("GPL");
MODULE_VERSION(CX88_VERSION);

अटल अचिन्हित पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debug messages [dvb]");

अटल अचिन्हित पूर्णांक dvb_buf_tscnt = 32;
module_param(dvb_buf_tscnt, पूर्णांक, 0644);
MODULE_PARM_DESC(dvb_buf_tscnt, "DVB Buffer TS count [dvb]");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				\
	अगर (debug >= level)						\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: dvb:" fmt),		\
			__func__, ##arg);				\
पूर्ण जबतक (0)

/* ------------------------------------------------------------------ */

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *q,
		       अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा cx8802_dev *dev = q->drv_priv;

	*num_planes = 1;
	dev->ts_packet_size  = 188 * 4;
	dev->ts_packet_count = dvb_buf_tscnt;
	sizes[0] = dev->ts_packet_size * dev->ts_packet_count;
	*num_buffers = dvb_buf_tscnt;
	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx8802_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx88_buffer *buf = container_of(vbuf, काष्ठा cx88_buffer, vb);

	वापस cx8802_buf_prepare(vb->vb2_queue, dev, buf);
पूर्ण

अटल व्योम buffer_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx8802_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx88_buffer *buf = container_of(vbuf, काष्ठा cx88_buffer, vb);
	काष्ठा cx88_riscmem *risc = &buf->risc;

	अगर (risc->cpu)
		pci_मुक्त_consistent(dev->pci, risc->size, risc->cpu, risc->dma);
	स_रखो(risc, 0, माप(*risc));
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx8802_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx88_buffer    *buf = container_of(vbuf, काष्ठा cx88_buffer, vb);

	cx8802_buf_queue(dev, buf);
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cx8802_dev *dev = q->drv_priv;
	काष्ठा cx88_dmaqueue *dmaq = &dev->mpegq;
	काष्ठा cx88_buffer *buf;

	buf = list_entry(dmaq->active.next, काष्ठा cx88_buffer, list);
	cx8802_start_dma(dev, dmaq, buf);
	वापस 0;
पूर्ण

अटल व्योम stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा cx8802_dev *dev = q->drv_priv;
	काष्ठा cx88_dmaqueue *dmaq = &dev->mpegq;
	अचिन्हित दीर्घ flags;

	cx8802_cancel_buffers(dev);

	spin_lock_irqsave(&dev->slock, flags);
	जबतक (!list_empty(&dmaq->active)) अणु
		काष्ठा cx88_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx88_buffer, list);

		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

अटल स्थिर काष्ठा vb2_ops dvb_qops = अणु
	.queue_setup    = queue_setup,
	.buf_prepare  = buffer_prepare,
	.buf_finish = buffer_finish,
	.buf_queue    = buffer_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = start_streaming,
	.stop_streaming = stop_streaming,
पूर्ण;

/* ------------------------------------------------------------------ */

अटल पूर्णांक cx88_dvb_bus_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक acquire)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;
	काष्ठा cx8802_driver *drv = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक fe_id;

	fe_id = vb2_dvb_find_frontend(&dev->frontends, fe);
	अगर (!fe_id) अणु
		pr_err("%s() No frontend found\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&dev->core->lock);
	drv = cx8802_get_driver(dev, CX88_MPEG_DVB);
	अगर (drv) अणु
		अगर (acquire) अणु
			dev->frontends.active_fe_id = fe_id;
			ret = drv->request_acquire(drv);
		पूर्ण अन्यथा अणु
			ret = drv->request_release(drv);
			dev->frontends.active_fe_id = 0;
		पूर्ण
	पूर्ण
	mutex_unlock(&dev->core->lock);

	वापस ret;
पूर्ण

अटल व्योम cx88_dvb_gate_ctrl(काष्ठा cx88_core  *core, पूर्णांक खोलो)
अणु
	काष्ठा vb2_dvb_frontends *f;
	काष्ठा vb2_dvb_frontend *fe;

	अगर (!core->dvbdev)
		वापस;

	f = &core->dvbdev->frontends;

	अगर (!f)
		वापस;

	अगर (f->gate <= 1) /* undefined or fe0 */
		fe = vb2_dvb_get_frontend(f, 1);
	अन्यथा
		fe = vb2_dvb_get_frontend(f, f->gate);

	अगर (fe && fe->dvb.frontend && fe->dvb.frontend->ops.i2c_gate_ctrl)
		fe->dvb.frontend->ops.i2c_gate_ctrl(fe->dvb.frontend, खोलो);
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक dvico_fusionhdtv_demod_init(काष्ठा dvb_frontend *fe)
अणु
	अटल स्थिर u8 घड़ी_config[]  = अणु CLOCK_CTL,  0x38, 0x39 पूर्ण;
	अटल स्थिर u8 reset[]         = अणु RESET,      0x80 पूर्ण;
	अटल स्थिर u8 adc_ctl_1_cfg[] = अणु ADC_CTL_1,  0x40 पूर्ण;
	अटल स्थिर u8 agc_cfg[]       = अणु AGC_TARGET, 0x24, 0x20 पूर्ण;
	अटल स्थिर u8 gpp_ctl_cfg[]   = अणु GPP_CTL,    0x33 पूर्ण;
	अटल स्थिर u8 capt_range_cfg[] = अणु CAPT_RANGE, 0x32 पूर्ण;

	mt352_ग_लिखो(fe, घड़ी_config,   माप(घड़ी_config));
	udelay(200);
	mt352_ग_लिखो(fe, reset,          माप(reset));
	mt352_ग_लिखो(fe, adc_ctl_1_cfg,  माप(adc_ctl_1_cfg));

	mt352_ग_लिखो(fe, agc_cfg,        माप(agc_cfg));
	mt352_ग_लिखो(fe, gpp_ctl_cfg,    माप(gpp_ctl_cfg));
	mt352_ग_लिखो(fe, capt_range_cfg, माप(capt_range_cfg));
	वापस 0;
पूर्ण

अटल पूर्णांक dvico_dual_demod_init(काष्ठा dvb_frontend *fe)
अणु
	अटल स्थिर u8 घड़ी_config[]  = अणु CLOCK_CTL,  0x38, 0x38 पूर्ण;
	अटल स्थिर u8 reset[]         = अणु RESET,      0x80 पूर्ण;
	अटल स्थिर u8 adc_ctl_1_cfg[] = अणु ADC_CTL_1,  0x40 पूर्ण;
	अटल स्थिर u8 agc_cfg[]       = अणु AGC_TARGET, 0x28, 0x20 पूर्ण;
	अटल स्थिर u8 gpp_ctl_cfg[]   = अणु GPP_CTL,    0x33 पूर्ण;
	अटल स्थिर u8 capt_range_cfg[] = अणु CAPT_RANGE, 0x32 पूर्ण;

	mt352_ग_लिखो(fe, घड़ी_config,   माप(घड़ी_config));
	udelay(200);
	mt352_ग_लिखो(fe, reset,          माप(reset));
	mt352_ग_लिखो(fe, adc_ctl_1_cfg,  माप(adc_ctl_1_cfg));

	mt352_ग_लिखो(fe, agc_cfg,        माप(agc_cfg));
	mt352_ग_लिखो(fe, gpp_ctl_cfg,    माप(gpp_ctl_cfg));
	mt352_ग_लिखो(fe, capt_range_cfg, माप(capt_range_cfg));

	वापस 0;
पूर्ण

अटल पूर्णांक dntv_live_dvbt_demod_init(काष्ठा dvb_frontend *fe)
अणु
	अटल स्थिर u8 घड़ी_config[]  = अणु 0x89, 0x38, 0x39 पूर्ण;
	अटल स्थिर u8 reset[]         = अणु 0x50, 0x80 पूर्ण;
	अटल स्थिर u8 adc_ctl_1_cfg[] = अणु 0x8E, 0x40 पूर्ण;
	अटल स्थिर u8 agc_cfg[]       = अणु 0x67, 0x10, 0x23, 0x00, 0xFF, 0xFF,
				       0x00, 0xFF, 0x00, 0x40, 0x40 पूर्ण;
	अटल स्थिर u8 dntv_extra[]     = अणु 0xB5, 0x7A पूर्ण;
	अटल स्थिर u8 capt_range_cfg[] = अणु 0x75, 0x32 पूर्ण;

	mt352_ग_लिखो(fe, घड़ी_config,   माप(घड़ी_config));
	udelay(2000);
	mt352_ग_लिखो(fe, reset,          माप(reset));
	mt352_ग_लिखो(fe, adc_ctl_1_cfg,  माप(adc_ctl_1_cfg));

	mt352_ग_लिखो(fe, agc_cfg,        माप(agc_cfg));
	udelay(2000);
	mt352_ग_लिखो(fe, dntv_extra,     माप(dntv_extra));
	mt352_ग_लिखो(fe, capt_range_cfg, माप(capt_range_cfg));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mt352_config dvico_fusionhdtv = अणु
	.demod_address = 0x0f,
	.demod_init    = dvico_fusionhdtv_demod_init,
पूर्ण;

अटल स्थिर काष्ठा mt352_config dntv_live_dvbt_config = अणु
	.demod_address = 0x0f,
	.demod_init    = dntv_live_dvbt_demod_init,
पूर्ण;

अटल स्थिर काष्ठा mt352_config dvico_fusionhdtv_dual = अणु
	.demod_address = 0x0f,
	.demod_init    = dvico_dual_demod_init,
पूर्ण;

अटल स्थिर काष्ठा zl10353_config cx88_terratec_cinergy_ht_pci_mkii_config = अणु
	.demod_address = (0x1e >> 1),
	.no_tuner      = 1,
	.अगर2           = 45600,
पूर्ण;

अटल स्थिर काष्ठा mb86a16_config twinhan_vp1027 = अणु
	.demod_address  = 0x08,
पूर्ण;

#अगर IS_ENABLED(CONFIG_VIDEO_CX88_VP3054)
अटल पूर्णांक dntv_live_dvbt_pro_demod_init(काष्ठा dvb_frontend *fe)
अणु
	अटल स्थिर u8 घड़ी_config[]  = अणु 0x89, 0x38, 0x38 पूर्ण;
	अटल स्थिर u8 reset[]         = अणु 0x50, 0x80 पूर्ण;
	अटल स्थिर u8 adc_ctl_1_cfg[] = अणु 0x8E, 0x40 पूर्ण;
	अटल स्थिर u8 agc_cfg[]       = अणु 0x67, 0x10, 0x20, 0x00, 0xFF, 0xFF,
				       0x00, 0xFF, 0x00, 0x40, 0x40 पूर्ण;
	अटल स्थिर u8 dntv_extra[]     = अणु 0xB5, 0x7A पूर्ण;
	अटल स्थिर u8 capt_range_cfg[] = अणु 0x75, 0x32 पूर्ण;

	mt352_ग_लिखो(fe, घड़ी_config,   माप(घड़ी_config));
	udelay(2000);
	mt352_ग_लिखो(fe, reset,          माप(reset));
	mt352_ग_लिखो(fe, adc_ctl_1_cfg,  माप(adc_ctl_1_cfg));

	mt352_ग_लिखो(fe, agc_cfg,        माप(agc_cfg));
	udelay(2000);
	mt352_ग_लिखो(fe, dntv_extra,     माप(dntv_extra));
	mt352_ग_लिखो(fe, capt_range_cfg, माप(capt_range_cfg));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mt352_config dntv_live_dvbt_pro_config = अणु
	.demod_address = 0x0f,
	.no_tuner      = 1,
	.demod_init    = dntv_live_dvbt_pro_demod_init,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा zl10353_config dvico_fusionhdtv_hybrid = अणु
	.demod_address = 0x0f,
	.no_tuner      = 1,
पूर्ण;

अटल स्थिर काष्ठा zl10353_config dvico_fusionhdtv_xc3028 = अणु
	.demod_address = 0x0f,
	.अगर2           = 45600,
	.no_tuner      = 1,
पूर्ण;

अटल स्थिर काष्ठा mt352_config dvico_fusionhdtv_mt352_xc3028 = अणु
	.demod_address = 0x0f,
	.अगर2 = 4560,
	.no_tuner = 1,
	.demod_init = dvico_fusionhdtv_demod_init,
पूर्ण;

अटल स्थिर काष्ठा zl10353_config dvico_fusionhdtv_plus_v1_1 = अणु
	.demod_address = 0x0f,
पूर्ण;

अटल स्थिर काष्ठा cx22702_config connexant_refboard_config = अणु
	.demod_address = 0x43,
	.output_mode   = CX22702_SERIAL_OUTPUT,
पूर्ण;

अटल स्थिर काष्ठा cx22702_config hauppauge_hvr_config = अणु
	.demod_address = 0x63,
	.output_mode   = CX22702_SERIAL_OUTPUT,
पूर्ण;

अटल पूर्णांक or51132_set_ts_param(काष्ठा dvb_frontend *fe, पूर्णांक is_punctured)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;

	dev->ts_gen_cntrl = is_punctured ? 0x04 : 0x00;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा or51132_config pchdtv_hd3000 = अणु
	.demod_address = 0x15,
	.set_ts_params = or51132_set_ts_param,
पूर्ण;

अटल पूर्णांक lgdt330x_pll_rf_set(काष्ठा dvb_frontend *fe, पूर्णांक index)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;
	काष्ठा cx88_core *core = dev->core;

	dprपूर्णांकk(1, "%s: index = %d\n", __func__, index);
	अगर (index == 0)
		cx_clear(MO_GP0_IO, 8);
	अन्यथा
		cx_set(MO_GP0_IO, 8);
	वापस 0;
पूर्ण

अटल पूर्णांक lgdt330x_set_ts_param(काष्ठा dvb_frontend *fe, पूर्णांक is_punctured)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;

	अगर (is_punctured)
		dev->ts_gen_cntrl |= 0x04;
	अन्यथा
		dev->ts_gen_cntrl &= ~0x04;
	वापस 0;
पूर्ण

अटल काष्ठा lgdt330x_config fusionhdtv_3_gold = अणु
	.demod_chip    = LGDT3302,
	.serial_mpeg   = 0x04, /* TPSERIAL क्रम 3302 in TOP_CONTROL */
	.set_ts_params = lgdt330x_set_ts_param,
पूर्ण;

अटल स्थिर काष्ठा lgdt330x_config fusionhdtv_5_gold = अणु
	.demod_chip    = LGDT3303,
	.serial_mpeg   = 0x40, /* TPSERIAL क्रम 3303 in TOP_CONTROL */
	.set_ts_params = lgdt330x_set_ts_param,
पूर्ण;

अटल स्थिर काष्ठा lgdt330x_config pchdtv_hd5500 = अणु
	.demod_chip    = LGDT3303,
	.serial_mpeg   = 0x40, /* TPSERIAL क्रम 3303 in TOP_CONTROL */
	.set_ts_params = lgdt330x_set_ts_param,
पूर्ण;

अटल पूर्णांक nxt200x_set_ts_param(काष्ठा dvb_frontend *fe, पूर्णांक is_punctured)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;

	dev->ts_gen_cntrl = is_punctured ? 0x04 : 0x00;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nxt200x_config ati_hdtvwonder = अणु
	.demod_address = 0x0a,
	.set_ts_params = nxt200x_set_ts_param,
पूर्ण;

अटल पूर्णांक cx24123_set_ts_param(काष्ठा dvb_frontend *fe,
				पूर्णांक is_punctured)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;

	dev->ts_gen_cntrl = 0x02;
	वापस 0;
पूर्ण

अटल पूर्णांक kworld_dvbs_100_set_voltage(काष्ठा dvb_frontend *fe,
				       क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;
	काष्ठा cx88_core *core = dev->core;

	अगर (voltage == SEC_VOLTAGE_OFF)
		cx_ग_लिखो(MO_GP0_IO, 0x000006fb);
	अन्यथा
		cx_ग_लिखो(MO_GP0_IO, 0x000006f9);

	अगर (core->prev_set_voltage)
		वापस core->prev_set_voltage(fe, voltage);
	वापस 0;
पूर्ण

अटल पूर्णांक geniatech_dvbs_set_voltage(काष्ठा dvb_frontend *fe,
				      क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;
	काष्ठा cx88_core *core = dev->core;

	अगर (voltage == SEC_VOLTAGE_OFF) अणु
		dprपूर्णांकk(1, "LNB Voltage OFF\n");
		cx_ग_लिखो(MO_GP0_IO, 0x0000efff);
	पूर्ण

	अगर (core->prev_set_voltage)
		वापस core->prev_set_voltage(fe, voltage);
	वापस 0;
पूर्ण

अटल पूर्णांक tevii_dvbs_set_voltage(काष्ठा dvb_frontend *fe,
				  क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;
	काष्ठा cx88_core *core = dev->core;

	cx_set(MO_GP0_IO, 0x6040);
	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
		cx_clear(MO_GP0_IO, 0x20);
		अवरोध;
	हाल SEC_VOLTAGE_18:
		cx_set(MO_GP0_IO, 0x20);
		अवरोध;
	हाल SEC_VOLTAGE_OFF:
		cx_clear(MO_GP0_IO, 0x20);
		अवरोध;
	पूर्ण

	अगर (core->prev_set_voltage)
		वापस core->prev_set_voltage(fe, voltage);
	वापस 0;
पूर्ण

अटल पूर्णांक vp1027_set_voltage(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;
	काष्ठा cx88_core *core = dev->core;

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
		dprपूर्णांकk(1, "LNB SEC Voltage=13\n");
		cx_ग_लिखो(MO_GP0_IO, 0x00001220);
		अवरोध;
	हाल SEC_VOLTAGE_18:
		dprपूर्णांकk(1, "LNB SEC Voltage=18\n");
		cx_ग_लिखो(MO_GP0_IO, 0x00001222);
		अवरोध;
	हाल SEC_VOLTAGE_OFF:
		dprपूर्णांकk(1, "LNB Voltage OFF\n");
		cx_ग_लिखो(MO_GP0_IO, 0x00001230);
		अवरोध;
	पूर्ण

	अगर (core->prev_set_voltage)
		वापस core->prev_set_voltage(fe, voltage);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cx24123_config geniatech_dvbs_config = अणु
	.demod_address = 0x55,
	.set_ts_params = cx24123_set_ts_param,
पूर्ण;

अटल स्थिर काष्ठा cx24123_config hauppauge_novas_config = अणु
	.demod_address = 0x55,
	.set_ts_params = cx24123_set_ts_param,
पूर्ण;

अटल स्थिर काष्ठा cx24123_config kworld_dvbs_100_config = अणु
	.demod_address = 0x15,
	.set_ts_params = cx24123_set_ts_param,
	.lnb_polarity  = 1,
पूर्ण;

अटल स्थिर काष्ठा s5h1409_config pinnacle_pctv_hd_800i_config = अणु
	.demod_address = 0x32 >> 1,
	.output_mode   = S5H1409_PARALLEL_OUTPUT,
	.gpio	       = S5H1409_GPIO_ON,
	.qam_अगर	       = 44000,
	.inversion     = S5H1409_INVERSION_OFF,
	.status_mode   = S5H1409_DEMODLOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_NONCONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;

अटल स्थिर काष्ठा s5h1409_config dvico_hdtv5_pci_nano_config = अणु
	.demod_address = 0x32 >> 1,
	.output_mode   = S5H1409_SERIAL_OUTPUT,
	.gpio          = S5H1409_GPIO_OFF,
	.inversion     = S5H1409_INVERSION_OFF,
	.status_mode   = S5H1409_DEMODLOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;

अटल स्थिर काष्ठा s5h1409_config kworld_atsc_120_config = अणु
	.demod_address = 0x32 >> 1,
	.output_mode   = S5H1409_SERIAL_OUTPUT,
	.gpio	       = S5H1409_GPIO_OFF,
	.inversion     = S5H1409_INVERSION_OFF,
	.status_mode   = S5H1409_DEMODLOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;

अटल स्थिर काष्ठा xc5000_config pinnacle_pctv_hd_800i_tuner_config = अणु
	.i2c_address	= 0x64,
	.अगर_khz		= 5380,
पूर्ण;

अटल स्थिर काष्ठा zl10353_config cx88_pinnacle_hybrid_pctv = अणु
	.demod_address = (0x1e >> 1),
	.no_tuner      = 1,
	.अगर2           = 45600,
पूर्ण;

अटल स्थिर काष्ठा zl10353_config cx88_geniatech_x8000_mt = अणु
	.demod_address = (0x1e >> 1),
	.no_tuner = 1,
	.disable_i2c_gate_ctrl = 1,
पूर्ण;

अटल स्थिर काष्ठा s5h1411_config dvico_fusionhdtv7_config = अणु
	.output_mode   = S5H1411_SERIAL_OUTPUT,
	.gpio          = S5H1411_GPIO_ON,
	.mpeg_timing   = S5H1411_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
	.qam_अगर        = S5H1411_IF_44000,
	.vsb_अगर        = S5H1411_IF_44000,
	.inversion     = S5H1411_INVERSION_OFF,
	.status_mode   = S5H1411_DEMODLOCKING
पूर्ण;

अटल स्थिर काष्ठा xc5000_config dvico_fusionhdtv7_tuner_config = अणु
	.i2c_address    = 0xc2 >> 1,
	.अगर_khz         = 5380,
पूर्ण;

अटल पूर्णांक attach_xc3028(u8 addr, काष्ठा cx8802_dev *dev)
अणु
	काष्ठा dvb_frontend *fe;
	काष्ठा vb2_dvb_frontend *fe0 = शून्य;
	काष्ठा xc2028_ctrl ctl;
	काष्ठा xc2028_config cfg = अणु
		.i2c_adap  = &dev->core->i2c_adap,
		.i2c_addr  = addr,
		.ctrl      = &ctl,
	पूर्ण;

	/* Get the first frontend */
	fe0 = vb2_dvb_get_frontend(&dev->frontends, 1);
	अगर (!fe0)
		वापस -EINVAL;

	अगर (!fe0->dvb.frontend) अणु
		pr_err("dvb frontend not attached. Can't attach xc3028\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Some xc3028 devices may be hidden by an I2C gate. This is known
	 * to happen with some s5h1409-based devices.
	 * Now that I2C gate is खोलो, sets up xc3028 configuration
	 */
	cx88_setup_xc3028(dev->core, &ctl);

	fe = dvb_attach(xc2028_attach, fe0->dvb.frontend, &cfg);
	अगर (!fe) अणु
		pr_err("xc3028 attach failed\n");
		dvb_frontend_detach(fe0->dvb.frontend);
		dvb_unरेजिस्टर_frontend(fe0->dvb.frontend);
		fe0->dvb.frontend = शून्य;
		वापस -EINVAL;
	पूर्ण

	pr_info("xc3028 attached\n");

	वापस 0;
पूर्ण

अटल पूर्णांक attach_xc4000(काष्ठा cx8802_dev *dev, काष्ठा xc4000_config *cfg)
अणु
	काष्ठा dvb_frontend *fe;
	काष्ठा vb2_dvb_frontend *fe0 = शून्य;

	/* Get the first frontend */
	fe0 = vb2_dvb_get_frontend(&dev->frontends, 1);
	अगर (!fe0)
		वापस -EINVAL;

	अगर (!fe0->dvb.frontend) अणु
		pr_err("dvb frontend not attached. Can't attach xc4000\n");
		वापस -EINVAL;
	पूर्ण

	fe = dvb_attach(xc4000_attach, fe0->dvb.frontend, &dev->core->i2c_adap,
			cfg);
	अगर (!fe) अणु
		pr_err("xc4000 attach failed\n");
		dvb_frontend_detach(fe0->dvb.frontend);
		dvb_unरेजिस्टर_frontend(fe0->dvb.frontend);
		fe0->dvb.frontend = शून्य;
		वापस -EINVAL;
	पूर्ण

	pr_info("xc4000 attached\n");

	वापस 0;
पूर्ण

अटल पूर्णांक cx24116_set_ts_param(काष्ठा dvb_frontend *fe,
				पूर्णांक is_punctured)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;

	dev->ts_gen_cntrl = 0x2;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0900_set_ts_param(काष्ठा dvb_frontend *fe,
				पूर्णांक is_punctured)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;

	dev->ts_gen_cntrl = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक cx24116_reset_device(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;
	काष्ठा cx88_core *core = dev->core;

	/* Reset the part */
	/* Put the cx24116 पूर्णांकo reset */
	cx_ग_लिखो(MO_SRST_IO, 0);
	usleep_range(10000, 20000);
	/* Take the cx24116 out of reset */
	cx_ग_लिखो(MO_SRST_IO, 1);
	usleep_range(10000, 20000);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cx24116_config hauppauge_hvr4000_config = अणु
	.demod_address          = 0x05,
	.set_ts_params          = cx24116_set_ts_param,
	.reset_device           = cx24116_reset_device,
पूर्ण;

अटल स्थिर काष्ठा cx24116_config tevii_s460_config = अणु
	.demod_address = 0x55,
	.set_ts_params = cx24116_set_ts_param,
	.reset_device  = cx24116_reset_device,
पूर्ण;

अटल पूर्णांक ds3000_set_ts_param(काष्ठा dvb_frontend *fe,
			       पूर्णांक is_punctured)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;

	dev->ts_gen_cntrl = 4;

	वापस 0;
पूर्ण

अटल काष्ठा ds3000_config tevii_ds3000_config = अणु
	.demod_address = 0x68,
	.set_ts_params = ds3000_set_ts_param,
पूर्ण;

अटल काष्ठा ts2020_config tevii_ts2020_config  = अणु
	.tuner_address = 0x60,
	.clk_out_भाग = 1,
पूर्ण;

अटल स्थिर काष्ठा stv0900_config prof_7301_stv0900_config = अणु
	.demod_address = 0x6a,
/*	demod_mode = 0,*/
	.xtal = 27000000,
	.clkmode = 3,/* 0-CLKI, 2-XTALI, अन्यथा AUTO */
	.diseqc_mode = 2,/* 2/3 PWM */
	.tun1_maddress = 0,/* 0x60 */
	.tun1_adc = 0,/* 2 Vpp */
	.path1_mode = 3,
	.set_ts_params = stv0900_set_ts_param,
पूर्ण;

अटल स्थिर काष्ठा stb6100_config prof_7301_stb6100_config = अणु
	.tuner_address = 0x60,
	.refघड़ी = 27000000,
पूर्ण;

अटल स्थिर काष्ठा stv0299_config tevii_tuner_sharp_config = अणु
	.demod_address = 0x68,
	.inittab = sharp_z0194a_inittab,
	.mclk = 88000000UL,
	.invert = 1,
	.skip_reinit = 0,
	.lock_output = 1,
	.volt13_op0_op1 = STV0299_VOLT13_OP1,
	.min_delay_ms = 100,
	.set_symbol_rate = sharp_z0194a_set_symbol_rate,
	.set_ts_params = cx24116_set_ts_param,
पूर्ण;

अटल स्थिर काष्ठा stv0288_config tevii_tuner_earda_config = अणु
	.demod_address = 0x68,
	.min_delay_ms = 100,
	.set_ts_params = cx24116_set_ts_param,
पूर्ण;

अटल पूर्णांक cx8802_alloc_frontends(काष्ठा cx8802_dev *dev)
अणु
	काष्ठा cx88_core *core = dev->core;
	काष्ठा vb2_dvb_frontend *fe = शून्य;
	पूर्णांक i;

	mutex_init(&dev->frontends.lock);
	INIT_LIST_HEAD(&dev->frontends.felist);

	अगर (!core->board.num_frontends)
		वापस -ENODEV;

	pr_info("%s: allocating %d frontend(s)\n", __func__,
		core->board.num_frontends);
	क्रम (i = 1; i <= core->board.num_frontends; i++) अणु
		fe = vb2_dvb_alloc_frontend(&dev->frontends, i);
		अगर (!fe) अणु
			pr_err("%s() failed to alloc\n", __func__);
			vb2_dvb_dealloc_frontends(&dev->frontends);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर u8 samsung_smt_7020_inittab[] = अणु
	     0x01, 0x15,
	     0x02, 0x00,
	     0x03, 0x00,
	     0x04, 0x7D,
	     0x05, 0x0F,
	     0x06, 0x02,
	     0x07, 0x00,
	     0x08, 0x60,

	     0x0A, 0xC2,
	     0x0B, 0x00,
	     0x0C, 0x01,
	     0x0D, 0x81,
	     0x0E, 0x44,
	     0x0F, 0x09,
	     0x10, 0x3C,
	     0x11, 0x84,
	     0x12, 0xDA,
	     0x13, 0x99,
	     0x14, 0x8D,
	     0x15, 0xCE,
	     0x16, 0xE8,
	     0x17, 0x43,
	     0x18, 0x1C,
	     0x19, 0x1B,
	     0x1A, 0x1D,

	     0x1C, 0x12,
	     0x1D, 0x00,
	     0x1E, 0x00,
	     0x1F, 0x00,
	     0x20, 0x00,
	     0x21, 0x00,
	     0x22, 0x00,
	     0x23, 0x00,

	     0x28, 0x02,
	     0x29, 0x28,
	     0x2A, 0x14,
	     0x2B, 0x0F,
	     0x2C, 0x09,
	     0x2D, 0x05,

	     0x31, 0x1F,
	     0x32, 0x19,
	     0x33, 0xFC,
	     0x34, 0x13,
	     0xff, 0xff,
पूर्ण;

अटल पूर्णांक samsung_smt_7020_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा cx8802_dev *dev = fe->dvb->priv;
	u8 buf[4];
	u32 भाग;
	काष्ठा i2c_msg msg = अणु
		.addr = 0x61,
		.flags = 0,
		.buf = buf,
		.len = माप(buf) पूर्ण;

	भाग = c->frequency / 125;

	buf[0] = (भाग >> 8) & 0x7f;
	buf[1] = भाग & 0xff;
	buf[2] = 0x84;  /* 0xC4 */
	buf[3] = 0x00;

	अगर (c->frequency < 1500000)
		buf[3] |= 0x10;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	अगर (i2c_transfer(&dev->core->i2c_adap, &msg, 1) != 1)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक samsung_smt_7020_set_tone(काष्ठा dvb_frontend *fe,
				     क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;
	काष्ठा cx88_core *core = dev->core;

	cx_set(MO_GP0_IO, 0x0800);

	चयन (tone) अणु
	हाल SEC_TONE_ON:
		cx_set(MO_GP0_IO, 0x08);
		अवरोध;
	हाल SEC_TONE_OFF:
		cx_clear(MO_GP0_IO, 0x08);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक samsung_smt_7020_set_voltage(काष्ठा dvb_frontend *fe,
					क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा cx8802_dev *dev = fe->dvb->priv;
	काष्ठा cx88_core *core = dev->core;

	u8 data;
	काष्ठा i2c_msg msg = अणु
		.addr = 8,
		.flags = 0,
		.buf = &data,
		.len = माप(data) पूर्ण;

	cx_set(MO_GP0_IO, 0x8000);

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_OFF:
		अवरोध;
	हाल SEC_VOLTAGE_13:
		data = ISL6421_EN1 | ISL6421_LLC1;
		cx_clear(MO_GP0_IO, 0x80);
		अवरोध;
	हाल SEC_VOLTAGE_18:
		data = ISL6421_EN1 | ISL6421_LLC1 | ISL6421_VSEL1;
		cx_clear(MO_GP0_IO, 0x80);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस (i2c_transfer(&dev->core->i2c_adap, &msg, 1) == 1) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक samsung_smt_7020_stv0299_set_symbol_rate(काष्ठा dvb_frontend *fe,
						    u32 srate, u32 ratio)
अणु
	u8 aclk = 0;
	u8 bclk = 0;

	अगर (srate < 1500000) अणु
		aclk = 0xb7;
		bclk = 0x47;
	पूर्ण अन्यथा अगर (srate < 3000000) अणु
		aclk = 0xb7;
		bclk = 0x4b;
	पूर्ण अन्यथा अगर (srate < 7000000) अणु
		aclk = 0xb7;
		bclk = 0x4f;
	पूर्ण अन्यथा अगर (srate < 14000000) अणु
		aclk = 0xb7;
		bclk = 0x53;
	पूर्ण अन्यथा अगर (srate < 30000000) अणु
		aclk = 0xb6;
		bclk = 0x53;
	पूर्ण अन्यथा अगर (srate < 45000000) अणु
		aclk = 0xb4;
		bclk = 0x51;
	पूर्ण

	stv0299_ग_लिखोreg(fe, 0x13, aclk);
	stv0299_ग_लिखोreg(fe, 0x14, bclk);
	stv0299_ग_लिखोreg(fe, 0x1f, (ratio >> 16) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x20, (ratio >>  8) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x21, ratio & 0xf0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा stv0299_config samsung_stv0299_config = अणु
	.demod_address = 0x68,
	.inittab = samsung_smt_7020_inittab,
	.mclk = 88000000UL,
	.invert = 0,
	.skip_reinit = 0,
	.lock_output = STV0299_LOCKOUTPUT_LK,
	.volt13_op0_op1 = STV0299_VOLT13_OP1,
	.min_delay_ms = 100,
	.set_symbol_rate = samsung_smt_7020_stv0299_set_symbol_rate,
पूर्ण;

अटल पूर्णांक dvb_रेजिस्टर(काष्ठा cx8802_dev *dev)
अणु
	काष्ठा cx88_core *core = dev->core;
	काष्ठा vb2_dvb_frontend *fe0, *fe1 = शून्य;
	पूर्णांक mfe_shared = 0; /* bus not shared by शेष */
	पूर्णांक res = -EINVAL;

	अगर (core->i2c_rc != 0) अणु
		pr_err("no i2c-bus available, cannot attach dvb drivers\n");
		जाओ frontend_detach;
	पूर्ण

	/* Get the first frontend */
	fe0 = vb2_dvb_get_frontend(&dev->frontends, 1);
	अगर (!fe0)
		जाओ frontend_detach;

	/* multi-frontend gate control is undefined or शेषs to fe0 */
	dev->frontends.gate = 0;

	/* Sets the gate control callback to be used by i2c command calls */
	core->gate_ctrl = cx88_dvb_gate_ctrl;

	/* init frontend(s) */
	चयन (core->boardnr) अणु
	हाल CX88_BOARD_HAUPPAUGE_DVB_T1:
		fe0->dvb.frontend = dvb_attach(cx22702_attach,
					       &connexant_refboard_config,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(dvb_pll_attach, fe0->dvb.frontend,
					0x61, &core->i2c_adap,
					DVB_PLL_THOMSON_DTT759X))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_TERRATEC_CINERGY_1400_DVB_T1:
	हाल CX88_BOARD_CONEXANT_DVB_T1:
	हाल CX88_BOARD_KWORLD_DVB_T_CX22702:
	हाल CX88_BOARD_WINFAST_DTV1000:
		fe0->dvb.frontend = dvb_attach(cx22702_attach,
					       &connexant_refboard_config,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(dvb_pll_attach, fe0->dvb.frontend,
					0x60, &core->i2c_adap,
					DVB_PLL_THOMSON_DTT7579))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_WINFAST_DTV2000H:
	हाल CX88_BOARD_HAUPPAUGE_HVR1100:
	हाल CX88_BOARD_HAUPPAUGE_HVR1100LP:
	हाल CX88_BOARD_HAUPPAUGE_HVR1300:
		fe0->dvb.frontend = dvb_attach(cx22702_attach,
					       &hauppauge_hvr_config,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
					&core->i2c_adap, 0x61,
					TUNER_PHILIPS_FMD1216ME_MK3))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_WINFAST_DTV2000H_J:
		fe0->dvb.frontend = dvb_attach(cx22702_attach,
					       &hauppauge_hvr_config,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
					&core->i2c_adap, 0x61,
					TUNER_PHILIPS_FMD1216MEX_MK3))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_HAUPPAUGE_HVR3000:
		/* MFE frontend 1 */
		mfe_shared = 1;
		dev->frontends.gate = 2;
		/* DVB-S init */
		fe0->dvb.frontend = dvb_attach(cx24123_attach,
					       &hauppauge_novas_config,
					       &dev->core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(isl6421_attach,
					fe0->dvb.frontend,
					&dev->core->i2c_adap,
					0x08, ISL6421_DCL, 0x00, false))
				जाओ frontend_detach;
		पूर्ण
		/* MFE frontend 2 */
		fe1 = vb2_dvb_get_frontend(&dev->frontends, 2);
		अगर (!fe1)
			जाओ frontend_detach;
		/* DVB-T init */
		fe1->dvb.frontend = dvb_attach(cx22702_attach,
					       &hauppauge_hvr_config,
					       &dev->core->i2c_adap);
		अगर (fe1->dvb.frontend) अणु
			fe1->dvb.frontend->id = 1;
			अगर (!dvb_attach(simple_tuner_attach,
					fe1->dvb.frontend,
					&dev->core->i2c_adap,
					0x61, TUNER_PHILIPS_FMD1216ME_MK3))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PLUS:
		fe0->dvb.frontend = dvb_attach(mt352_attach,
					       &dvico_fusionhdtv,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(dvb_pll_attach, fe0->dvb.frontend,
					0x60, शून्य, DVB_PLL_THOMSON_DTT7579))
				जाओ frontend_detach;
			अवरोध;
		पूर्ण
		/* ZL10353 replaces MT352 on later cards */
		fe0->dvb.frontend = dvb_attach(zl10353_attach,
					       &dvico_fusionhdtv_plus_v1_1,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(dvb_pll_attach, fe0->dvb.frontend,
					0x60, शून्य, DVB_PLL_THOMSON_DTT7579))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL:
		/*
		 * The tin box says DEE1601, but it seems to be DTT7579
		 * compatible, with a slightly dअगरferent MT352 AGC gain.
		 */
		fe0->dvb.frontend = dvb_attach(mt352_attach,
					       &dvico_fusionhdtv_dual,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(dvb_pll_attach, fe0->dvb.frontend,
					0x61, शून्य, DVB_PLL_THOMSON_DTT7579))
				जाओ frontend_detach;
			अवरोध;
		पूर्ण
		/* ZL10353 replaces MT352 on later cards */
		fe0->dvb.frontend = dvb_attach(zl10353_attach,
					       &dvico_fusionhdtv_plus_v1_1,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(dvb_pll_attach, fe0->dvb.frontend,
					0x61, शून्य, DVB_PLL_THOMSON_DTT7579))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_DVB_T1:
		fe0->dvb.frontend = dvb_attach(mt352_attach,
					       &dvico_fusionhdtv,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(dvb_pll_attach, fe0->dvb.frontend,
					0x61, शून्य, DVB_PLL_LG_Z201))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_KWORLD_DVB_T:
	हाल CX88_BOARD_DNTV_LIVE_DVB_T:
	हाल CX88_BOARD_ADSTECH_DVB_T_PCI:
		fe0->dvb.frontend = dvb_attach(mt352_attach,
					       &dntv_live_dvbt_config,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(dvb_pll_attach, fe0->dvb.frontend,
					0x61, शून्य, DVB_PLL_UNKNOWN_1))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_DNTV_LIVE_DVB_T_PRO:
#अगर IS_ENABLED(CONFIG_VIDEO_CX88_VP3054)
		/* MT352 is on a secondary I2C bus made from some GPIO lines */
		fe0->dvb.frontend = dvb_attach(mt352_attach,
					       &dntv_live_dvbt_pro_config,
					       &dev->vp3054->adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
					&core->i2c_adap, 0x61,
					TUNER_PHILIPS_FMD1216ME_MK3))
				जाओ frontend_detach;
		पूर्ण
#अन्यथा
		pr_err("built without vp3054 support\n");
#पूर्ण_अगर
		अवरोध;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_HYBRID:
		fe0->dvb.frontend = dvb_attach(zl10353_attach,
					       &dvico_fusionhdtv_hybrid,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
					&core->i2c_adap, 0x61,
					TUNER_THOMSON_FE6600))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PRO:
		fe0->dvb.frontend = dvb_attach(zl10353_attach,
					       &dvico_fusionhdtv_xc3028,
					       &core->i2c_adap);
		अगर (!fe0->dvb.frontend)
			fe0->dvb.frontend = dvb_attach(mt352_attach,
						&dvico_fusionhdtv_mt352_xc3028,
						&core->i2c_adap);
		/*
		 * On this board, the demod provides the I2C bus pullup.
		 * We must not permit gate_ctrl to be perक्रमmed, or
		 * the xc3028 cannot communicate on the bus.
		 */
		अगर (fe0->dvb.frontend)
			fe0->dvb.frontend->ops.i2c_gate_ctrl = शून्य;
		अगर (attach_xc3028(0x61, dev) < 0)
			जाओ frontend_detach;
		अवरोध;
	हाल CX88_BOARD_PCHDTV_HD3000:
		fe0->dvb.frontend = dvb_attach(or51132_attach, &pchdtv_hd3000,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
					&core->i2c_adap, 0x61,
					TUNER_THOMSON_DTT761X))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_3_GOLD_Q:
		dev->ts_gen_cntrl = 0x08;

		/* Do a hardware reset of chip beक्रमe using it. */
		cx_clear(MO_GP0_IO, 1);
		msleep(100);
		cx_set(MO_GP0_IO, 1);
		msleep(200);

		/* Select RF connector callback */
		fusionhdtv_3_gold.pll_rf_set = lgdt330x_pll_rf_set;
		fe0->dvb.frontend = dvb_attach(lgdt330x_attach,
					       &fusionhdtv_3_gold,
					       0x0e,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
					&core->i2c_adap, 0x61,
					TUNER_MICROTUNE_4042FI5))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_3_GOLD_T:
		dev->ts_gen_cntrl = 0x08;

		/* Do a hardware reset of chip beक्रमe using it. */
		cx_clear(MO_GP0_IO, 1);
		msleep(100);
		cx_set(MO_GP0_IO, 9);
		msleep(200);
		fe0->dvb.frontend = dvb_attach(lgdt330x_attach,
					       &fusionhdtv_3_gold,
					       0x0e,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
					&core->i2c_adap, 0x61,
					TUNER_THOMSON_DTT761X))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_5_GOLD:
		dev->ts_gen_cntrl = 0x08;

		/* Do a hardware reset of chip beक्रमe using it. */
		cx_clear(MO_GP0_IO, 1);
		msleep(100);
		cx_set(MO_GP0_IO, 1);
		msleep(200);
		fe0->dvb.frontend = dvb_attach(lgdt330x_attach,
					       &fusionhdtv_5_gold,
					       0x0e,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
					&core->i2c_adap, 0x61,
					TUNER_LG_TDVS_H06XF))
				जाओ frontend_detach;
			अगर (!dvb_attach(tda9887_attach, fe0->dvb.frontend,
					&core->i2c_adap, 0x43))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_PCHDTV_HD5500:
		dev->ts_gen_cntrl = 0x08;

		/* Do a hardware reset of chip beक्रमe using it. */
		cx_clear(MO_GP0_IO, 1);
		msleep(100);
		cx_set(MO_GP0_IO, 1);
		msleep(200);
		fe0->dvb.frontend = dvb_attach(lgdt330x_attach,
					       &pchdtv_hd5500,
					       0x59,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
					&core->i2c_adap, 0x61,
					TUNER_LG_TDVS_H06XF))
				जाओ frontend_detach;
			अगर (!dvb_attach(tda9887_attach, fe0->dvb.frontend,
					&core->i2c_adap, 0x43))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_ATI_HDTVWONDER:
		fe0->dvb.frontend = dvb_attach(nxt200x_attach,
					       &ati_hdtvwonder,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
					&core->i2c_adap, 0x61,
					TUNER_PHILIPS_TUV1236D))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_HAUPPAUGE_NOVASPLUS_S1:
	हाल CX88_BOARD_HAUPPAUGE_NOVASE2_S1:
		fe0->dvb.frontend = dvb_attach(cx24123_attach,
					       &hauppauge_novas_config,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			bool override_tone;

			अगर (core->model == 92001)
				override_tone = true;
			अन्यथा
				override_tone = false;

			अगर (!dvb_attach(isl6421_attach, fe0->dvb.frontend,
					&core->i2c_adap, 0x08, ISL6421_DCL,
					0x00, override_tone))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_KWORLD_DVBS_100:
		fe0->dvb.frontend = dvb_attach(cx24123_attach,
					       &kworld_dvbs_100_config,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			core->prev_set_voltage = fe0->dvb.frontend->ops.set_voltage;
			fe0->dvb.frontend->ops.set_voltage = kworld_dvbs_100_set_voltage;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_GENIATECH_DVBS:
		fe0->dvb.frontend = dvb_attach(cx24123_attach,
					       &geniatech_dvbs_config,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			core->prev_set_voltage = fe0->dvb.frontend->ops.set_voltage;
			fe0->dvb.frontend->ops.set_voltage = geniatech_dvbs_set_voltage;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_PINNACLE_PCTV_HD_800i:
		fe0->dvb.frontend = dvb_attach(s5h1409_attach,
					       &pinnacle_pctv_hd_800i_config,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(xc5000_attach, fe0->dvb.frontend,
					&core->i2c_adap,
					&pinnacle_pctv_hd_800i_tuner_config))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_5_PCI_न_अंकO:
		fe0->dvb.frontend = dvb_attach(s5h1409_attach,
					       &dvico_hdtv5_pci_nano_config,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			काष्ठा dvb_frontend *fe;
			काष्ठा xc2028_config cfg = अणु
				.i2c_adap  = &core->i2c_adap,
				.i2c_addr  = 0x61,
			पूर्ण;
			अटल काष्ठा xc2028_ctrl ctl = अणु
				.fname       = XC2028_DEFAULT_FIRMWARE,
				.max_len     = 64,
				.scode_table = XC3028_FE_OREN538,
			पूर्ण;

			fe = dvb_attach(xc2028_attach,
					fe0->dvb.frontend, &cfg);
			अगर (fe && fe->ops.tuner_ops.set_config)
				fe->ops.tuner_ops.set_config(fe, &ctl);
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_NOTONLYTV_LV3H:
	हाल CX88_BOARD_PINNACLE_HYBRID_PCTV:
	हाल CX88_BOARD_WINFAST_DTV1800H:
		fe0->dvb.frontend = dvb_attach(zl10353_attach,
					       &cx88_pinnacle_hybrid_pctv,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			fe0->dvb.frontend->ops.i2c_gate_ctrl = शून्य;
			अगर (attach_xc3028(0x61, dev) < 0)
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_WINFAST_DTV1800H_XC4000:
	हाल CX88_BOARD_WINFAST_DTV2000H_PLUS:
		fe0->dvb.frontend = dvb_attach(zl10353_attach,
					       &cx88_pinnacle_hybrid_pctv,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			काष्ठा xc4000_config cfg = अणु
				.i2c_address	  = 0x61,
				.शेष_pm	  = 0,
				.dvb_amplitude	  = 134,
				.set_smoothedcvbs = 1,
				.अगर_khz		  = 4560
			पूर्ण;
			fe0->dvb.frontend->ops.i2c_gate_ctrl = शून्य;
			अगर (attach_xc4000(dev, &cfg) < 0)
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_GENIATECH_X8000_MT:
		dev->ts_gen_cntrl = 0x00;

		fe0->dvb.frontend = dvb_attach(zl10353_attach,
					       &cx88_geniatech_x8000_mt,
					       &core->i2c_adap);
		अगर (attach_xc3028(0x61, dev) < 0)
			जाओ frontend_detach;
		अवरोध;
	हाल CX88_BOARD_KWORLD_ATSC_120:
		fe0->dvb.frontend = dvb_attach(s5h1409_attach,
					       &kworld_atsc_120_config,
					       &core->i2c_adap);
		अगर (attach_xc3028(0x61, dev) < 0)
			जाओ frontend_detach;
		अवरोध;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_7_GOLD:
		fe0->dvb.frontend = dvb_attach(s5h1411_attach,
					       &dvico_fusionhdtv7_config,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(xc5000_attach, fe0->dvb.frontend,
					&core->i2c_adap,
					&dvico_fusionhdtv7_tuner_config))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_HAUPPAUGE_HVR4000:
		/* MFE frontend 1 */
		mfe_shared = 1;
		dev->frontends.gate = 2;
		/* DVB-S/S2 Init */
		fe0->dvb.frontend = dvb_attach(cx24116_attach,
					       &hauppauge_hvr4000_config,
					       &dev->core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(isl6421_attach,
					fe0->dvb.frontend,
					&dev->core->i2c_adap,
					0x08, ISL6421_DCL, 0x00, false))
				जाओ frontend_detach;
		पूर्ण
		/* MFE frontend 2 */
		fe1 = vb2_dvb_get_frontend(&dev->frontends, 2);
		अगर (!fe1)
			जाओ frontend_detach;
		/* DVB-T Init */
		fe1->dvb.frontend = dvb_attach(cx22702_attach,
					       &hauppauge_hvr_config,
					       &dev->core->i2c_adap);
		अगर (fe1->dvb.frontend) अणु
			fe1->dvb.frontend->id = 1;
			अगर (!dvb_attach(simple_tuner_attach,
					fe1->dvb.frontend,
					&dev->core->i2c_adap,
					0x61, TUNER_PHILIPS_FMD1216ME_MK3))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_HAUPPAUGE_HVR4000LITE:
		fe0->dvb.frontend = dvb_attach(cx24116_attach,
					       &hauppauge_hvr4000_config,
					       &dev->core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(isl6421_attach,
					fe0->dvb.frontend,
					&dev->core->i2c_adap,
					0x08, ISL6421_DCL, 0x00, false))
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_PROF_6200:
	हाल CX88_BOARD_TBS_8910:
	हाल CX88_BOARD_TEVII_S420:
		fe0->dvb.frontend = dvb_attach(stv0299_attach,
						&tevii_tuner_sharp_config,
						&core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(dvb_pll_attach, fe0->dvb.frontend, 0x60,
					&core->i2c_adap, DVB_PLL_OPERA1))
				जाओ frontend_detach;
			core->prev_set_voltage = fe0->dvb.frontend->ops.set_voltage;
			fe0->dvb.frontend->ops.set_voltage = tevii_dvbs_set_voltage;

		पूर्ण अन्यथा अणु
			fe0->dvb.frontend = dvb_attach(stv0288_attach,
							    &tevii_tuner_earda_config,
							    &core->i2c_adap);
			अगर (fe0->dvb.frontend) अणु
				अगर (!dvb_attach(stb6000_attach,
						fe0->dvb.frontend, 0x61,
						&core->i2c_adap))
					जाओ frontend_detach;
				core->prev_set_voltage = fe0->dvb.frontend->ops.set_voltage;
				fe0->dvb.frontend->ops.set_voltage = tevii_dvbs_set_voltage;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_TEVII_S460:
		fe0->dvb.frontend = dvb_attach(cx24116_attach,
					       &tevii_s460_config,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend)
			fe0->dvb.frontend->ops.set_voltage = tevii_dvbs_set_voltage;
		अवरोध;
	हाल CX88_BOARD_TEVII_S464:
		fe0->dvb.frontend = dvb_attach(ds3000_attach,
						&tevii_ds3000_config,
						&core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			dvb_attach(ts2020_attach, fe0->dvb.frontend,
				   &tevii_ts2020_config, &core->i2c_adap);
			fe0->dvb.frontend->ops.set_voltage =
							tevii_dvbs_set_voltage;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_OMICOM_SS4_PCI:
	हाल CX88_BOARD_TBS_8920:
	हाल CX88_BOARD_PROF_7300:
	हाल CX88_BOARD_SATTRADE_ST4200:
		fe0->dvb.frontend = dvb_attach(cx24116_attach,
					       &hauppauge_hvr4000_config,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend)
			fe0->dvb.frontend->ops.set_voltage = tevii_dvbs_set_voltage;
		अवरोध;
	हाल CX88_BOARD_TERRATEC_CINERGY_HT_PCI_MKII:
		fe0->dvb.frontend = dvb_attach(zl10353_attach,
					       &cx88_terratec_cinergy_ht_pci_mkii_config,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			fe0->dvb.frontend->ops.i2c_gate_ctrl = शून्य;
			अगर (attach_xc3028(0x61, dev) < 0)
				जाओ frontend_detach;
		पूर्ण
		अवरोध;
	हाल CX88_BOARD_PROF_7301:अणु
		काष्ठा dvb_tuner_ops *tuner_ops = शून्य;

		fe0->dvb.frontend = dvb_attach(stv0900_attach,
					       &prof_7301_stv0900_config,
					       &core->i2c_adap, 0);
		अगर (fe0->dvb.frontend) अणु
			अगर (!dvb_attach(stb6100_attach, fe0->dvb.frontend,
					&prof_7301_stb6100_config,
					&core->i2c_adap))
				जाओ frontend_detach;

			tuner_ops = &fe0->dvb.frontend->ops.tuner_ops;
			tuner_ops->set_frequency = stb6100_set_freq;
			tuner_ops->get_frequency = stb6100_get_freq;
			tuner_ops->set_bandwidth = stb6100_set_bandw;
			tuner_ops->get_bandwidth = stb6100_get_bandw;

			core->prev_set_voltage =
					fe0->dvb.frontend->ops.set_voltage;
			fe0->dvb.frontend->ops.set_voltage =
					tevii_dvbs_set_voltage;
		पूर्ण
		अवरोध;
		पूर्ण
	हाल CX88_BOARD_SAMSUNG_SMT_7020:
		dev->ts_gen_cntrl = 0x08;

		cx_set(MO_GP0_IO, 0x0101);

		cx_clear(MO_GP0_IO, 0x01);
		msleep(100);
		cx_set(MO_GP0_IO, 0x01);
		msleep(200);

		fe0->dvb.frontend = dvb_attach(stv0299_attach,
					       &samsung_stv0299_config,
					       &dev->core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			fe0->dvb.frontend->ops.tuner_ops.set_params =
				samsung_smt_7020_tuner_set_params;
			fe0->dvb.frontend->tuner_priv =
				&dev->core->i2c_adap;
			fe0->dvb.frontend->ops.set_voltage =
				samsung_smt_7020_set_voltage;
			fe0->dvb.frontend->ops.set_tone =
				samsung_smt_7020_set_tone;
		पूर्ण

		अवरोध;
	हाल CX88_BOARD_TWINHAN_VP1027_DVBS:
		dev->ts_gen_cntrl = 0x00;
		fe0->dvb.frontend = dvb_attach(mb86a16_attach,
					       &twinhan_vp1027,
					       &core->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			core->prev_set_voltage =
					fe0->dvb.frontend->ops.set_voltage;
			fe0->dvb.frontend->ops.set_voltage =
					vp1027_set_voltage;
		पूर्ण
		अवरोध;

	शेष:
		pr_err("The frontend of your DVB/ATSC card isn't supported yet\n");
		अवरोध;
	पूर्ण

	अगर ((शून्य == fe0->dvb.frontend) || (fe1 && शून्य == fe1->dvb.frontend)) अणु
		pr_err("frontend initialization failed\n");
		जाओ frontend_detach;
	पूर्ण
	/* define general-purpose callback poपूर्णांकer */
	fe0->dvb.frontend->callback = cx88_tuner_callback;

	/* Ensure all frontends negotiate bus access */
	fe0->dvb.frontend->ops.ts_bus_ctrl = cx88_dvb_bus_ctrl;
	अगर (fe1)
		fe1->dvb.frontend->ops.ts_bus_ctrl = cx88_dvb_bus_ctrl;

	/* Put the tuner in standby to keep it quiet */
	call_all(core, tuner, standby);

	/* रेजिस्टर everything */
	res = vb2_dvb_रेजिस्टर_bus(&dev->frontends, THIS_MODULE, dev,
				   &dev->pci->dev, शून्य, adapter_nr,
				   mfe_shared);
	अगर (res)
		जाओ frontend_detach;
	वापस res;

frontend_detach:
	core->gate_ctrl = शून्य;
	vb2_dvb_dealloc_frontends(&dev->frontends);
	वापस res;
पूर्ण

/* ----------------------------------------------------------- */

/* CX8802 MPEG -> mini driver - We have been given the hardware */
अटल पूर्णांक cx8802_dvb_advise_acquire(काष्ठा cx8802_driver *drv)
अणु
	काष्ठा cx88_core *core = drv->core;
	पूर्णांक err = 0;

	dprपूर्णांकk(1, "%s\n", __func__);

	चयन (core->boardnr) अणु
	हाल CX88_BOARD_HAUPPAUGE_HVR1300:
		/* We arrive here with either the cx23416 or the cx22702
		 * on the bus. Take the bus from the cx23416 and enable the
		 * cx22702 demod
		 */
		/* Toggle reset on cx22702 leaving i2c active */
		cx_set(MO_GP0_IO, 0x00000080);
		udelay(1000);
		cx_clear(MO_GP0_IO, 0x00000080);
		udelay(50);
		cx_set(MO_GP0_IO, 0x00000080);
		udelay(1000);
		/* enable the cx22702 pins */
		cx_clear(MO_GP0_IO, 0x00000004);
		udelay(1000);
		अवरोध;

	हाल CX88_BOARD_HAUPPAUGE_HVR3000:
	हाल CX88_BOARD_HAUPPAUGE_HVR4000:
		/* Toggle reset on cx22702 leaving i2c active */
		cx_set(MO_GP0_IO, 0x00000080);
		udelay(1000);
		cx_clear(MO_GP0_IO, 0x00000080);
		udelay(50);
		cx_set(MO_GP0_IO, 0x00000080);
		udelay(1000);
		चयन (core->dvbdev->frontends.active_fe_id) अणु
		हाल 1: /* DVB-S/S2 Enabled */
			/* tri-state the cx22702 pins */
			cx_set(MO_GP0_IO, 0x00000004);
			/* Take the cx24116/cx24123 out of reset */
			cx_ग_लिखो(MO_SRST_IO, 1);
			core->dvbdev->ts_gen_cntrl = 0x02; /* Parallel IO */
			अवरोध;
		हाल 2: /* DVB-T Enabled */
			/* Put the cx24116/cx24123 पूर्णांकo reset */
			cx_ग_लिखो(MO_SRST_IO, 0);
			/* enable the cx22702 pins */
			cx_clear(MO_GP0_IO, 0x00000004);
			core->dvbdev->ts_gen_cntrl = 0x0c; /* Serial IO */
			अवरोध;
		पूर्ण
		udelay(1000);
		अवरोध;

	हाल CX88_BOARD_WINFAST_DTV2000H_PLUS:
		/* set RF input to AIR क्रम DVB-T (GPIO 16) */
		cx_ग_लिखो(MO_GP2_IO, 0x0101);
		अवरोध;

	शेष:
		err = -ENODEV;
	पूर्ण
	वापस err;
पूर्ण

/* CX8802 MPEG -> mini driver - We no दीर्घer have the hardware */
अटल पूर्णांक cx8802_dvb_advise_release(काष्ठा cx8802_driver *drv)
अणु
	काष्ठा cx88_core *core = drv->core;
	पूर्णांक err = 0;

	dprपूर्णांकk(1, "%s\n", __func__);

	चयन (core->boardnr) अणु
	हाल CX88_BOARD_HAUPPAUGE_HVR1300:
		/* Do Nothing, leave the cx22702 on the bus. */
		अवरोध;
	हाल CX88_BOARD_HAUPPAUGE_HVR3000:
	हाल CX88_BOARD_HAUPPAUGE_HVR4000:
		अवरोध;
	शेष:
		err = -ENODEV;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक cx8802_dvb_probe(काष्ठा cx8802_driver *drv)
अणु
	काष्ठा cx88_core *core = drv->core;
	काष्ठा cx8802_dev *dev = drv->core->dvbdev;
	पूर्णांक err;
	काष्ठा vb2_dvb_frontend *fe;
	पूर्णांक i;

	dprपूर्णांकk(1, "%s\n", __func__);
	dprपूर्णांकk(1, " ->being probed by Card=%d Name=%s, PCI %02x:%02x\n",
		core->boardnr,
		core->name,
		core->pci_bus,
		core->pci_slot);

	err = -ENODEV;
	अगर (!(core->board.mpeg & CX88_MPEG_DVB))
		जाओ fail_core;

	/* If vp3054 isn't enabled, a stub will just वापस 0 */
	err = vp3054_i2c_probe(dev);
	अगर (err != 0)
		जाओ fail_core;

	/* dvb stuff */
	pr_info("cx2388x based DVB/ATSC card\n");
	dev->ts_gen_cntrl = 0x0c;

	err = cx8802_alloc_frontends(dev);
	अगर (err)
		जाओ fail_core;

	क्रम (i = 1; i <= core->board.num_frontends; i++) अणु
		काष्ठा vb2_queue *q;

		fe = vb2_dvb_get_frontend(&core->dvbdev->frontends, i);
		अगर (!fe) अणु
			pr_err("%s() failed to get frontend(%d)\n",
			       __func__, i);
			err = -ENODEV;
			जाओ fail_probe;
		पूर्ण
		q = &fe->dvb.dvbq;
		q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF | VB2_READ;
		q->gfp_flags = GFP_DMA32;
		q->min_buffers_needed = 2;
		q->drv_priv = dev;
		q->buf_काष्ठा_size = माप(काष्ठा cx88_buffer);
		q->ops = &dvb_qops;
		q->mem_ops = &vb2_dma_sg_memops;
		q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
		q->lock = &core->lock;
		q->dev = &dev->pci->dev;

		err = vb2_queue_init(q);
		अगर (err < 0)
			जाओ fail_probe;

		/* init काष्ठा vb2_dvb */
		fe->dvb.name = dev->core->name;
	पूर्ण

	err = dvb_रेजिस्टर(dev);
	अगर (err)
		/* frontends/adapter de-allocated in dvb_रेजिस्टर */
		pr_err("dvb_register failed (err = %d)\n", err);
	वापस err;
fail_probe:
	vb2_dvb_dealloc_frontends(&core->dvbdev->frontends);
fail_core:
	वापस err;
पूर्ण

अटल पूर्णांक cx8802_dvb_हटाओ(काष्ठा cx8802_driver *drv)
अणु
	काष्ठा cx88_core *core = drv->core;
	काष्ठा cx8802_dev *dev = drv->core->dvbdev;

	dprपूर्णांकk(1, "%s\n", __func__);

	vb2_dvb_unरेजिस्टर_bus(&dev->frontends);

	vp3054_i2c_हटाओ(dev);

	core->gate_ctrl = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा cx8802_driver cx8802_dvb_driver = अणु
	.type_id        = CX88_MPEG_DVB,
	.hw_access      = CX8802_DRVCTL_SHARED,
	.probe          = cx8802_dvb_probe,
	.हटाओ         = cx8802_dvb_हटाओ,
	.advise_acquire = cx8802_dvb_advise_acquire,
	.advise_release = cx8802_dvb_advise_release,
पूर्ण;

अटल पूर्णांक __init dvb_init(व्योम)
अणु
	pr_info("cx2388x dvb driver version %s loaded\n", CX88_VERSION);
	वापस cx8802_रेजिस्टर_driver(&cx8802_dvb_driver);
पूर्ण

अटल व्योम __निकास dvb_fini(व्योम)
अणु
	cx8802_unरेजिस्टर_driver(&cx8802_dvb_driver);
पूर्ण

module_init(dvb_init);
module_निकास(dvb_fini);
