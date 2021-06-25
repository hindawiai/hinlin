<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TTUSB DVB driver
 *
 * Copyright (c) 2002 Holger Waechtler <holger@convergence.de>
 * Copyright (c) 2003 Felix Domke <पंचांगbinc@elitedvb.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/delay.h>
#समावेश <linux/समय.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश <linux/firmware.h>

#समावेश <media/dvb_frontend.h>
#समावेश <media/dmxdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_net.h>
#समावेश "ves1820.h"
#समावेश "cx22700.h"
#समावेश "tda1004x.h"
#समावेश "stv0299.h"
#समावेश "tda8083.h"
#समावेश "stv0297.h"
#समावेश "lnbp21.h"

#समावेश <linux/dvb/frontend.h>
#समावेश <linux/dvb/dmx.h>
#समावेश <linux/pci.h>

/*
  TTUSB_HWSECTIONS:
    the DSP supports filtering in hardware, however, since the "muxstream"
    is a bit braindead (no matching channel masks or no matching filter mask),
    we won't support this - yet. it doesn't event support negative filters,
    so the best way is maybe to keep TTUSB_HWSECTIONS undef'd and just
    parse TS data. USB bandwidth will be a problem when having large
    datastreams, especially क्रम dvb-net, but hey, that's not my problem.

  TTUSB_DISEQC, TTUSB_TONE:
    let the STC करो the diseqc/tone stuff. this isn't supported at least with
    my TTUSB, so let it undef'd unless you want to implement another
    frontend. never tested.

  debug:
    define it to > 3 क्रम really hardcore debugging. you probably करोn't want
    this unless the device करोesn't load at all. > 2 क्रम bandwidth statistics.
*/

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off debugging (default:off).");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (debug)							\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
		       __func__, ##arg);				\
पूर्ण जबतक (0)


#घोषणा ISO_BUF_COUNT      4
#घोषणा FRAMES_PER_ISO_BUF 4
#घोषणा ISO_FRAME_SIZE     912
#घोषणा TTUSB_MAXCHANNEL   32
#अगर_घोषित TTUSB_HWSECTIONS
#घोषणा TTUSB_MAXFILTER    16	/* ??? */
#पूर्ण_अगर

#घोषणा TTUSB_REV_2_2	0x22
#घोषणा TTUSB_BUDGET_NAME "ttusb_stc_fw"

#घोषणा MAX_SEND	0x28
#घोषणा MAX_RCV		0x20

/*
 *  since we're casting (काष्ठा ttusb*) <-> (काष्ठा dvb_demux*) around
 *  the dvb_demux field must be the first in काष्ठा!!
 */
काष्ठा ttusb अणु
	काष्ठा dvb_demux dvb_demux;
	काष्ठा dmxdev dmxdev;
	काष्ठा dvb_net dvbnet;

	/* and one क्रम USB access. */
	काष्ठा mutex semi2c;
	काष्ठा mutex semusb;

	काष्ठा dvb_adapter adapter;
	काष्ठा usb_device *dev;

	काष्ठा i2c_adapter i2c_adap;

	पूर्णांक disconnecting;
	पूर्णांक iso_streaming;

	अचिन्हित पूर्णांक bulk_out_pipe;
	अचिन्हित पूर्णांक bulk_in_pipe;
	अचिन्हित पूर्णांक isoc_in_pipe;

	व्योम *iso_buffer;

	काष्ठा urb *iso_urb[ISO_BUF_COUNT];

	पूर्णांक running_feed_count;
	पूर्णांक last_channel;
	पूर्णांक last_filter;

	u8 c;			/* transaction counter, wraps around...  */
	क्रमागत fe_sec_tone_mode tone;
	क्रमागत fe_sec_voltage voltage;

	पूर्णांक mux_state;		// 0..2 - MuxSyncWord, 3 - nMuxPacks,    4 - muxpack
	u8 mux_npacks;
	u8 muxpack[256 + 8];
	पूर्णांक muxpack_ptr, muxpack_len;

	पूर्णांक insync;

	पूर्णांक cc;			/* MuxCounter - will increment on EVERY MUX PACKET */
	/* (including stuffing. yes. really.) */

	u8 send_buf[MAX_SEND];
	u8 last_result[MAX_RCV];

	पूर्णांक revision;

	काष्ठा dvb_frontend* fe;
पूर्ण;

अटल पूर्णांक ttusb_cmd(काष्ठा ttusb *ttusb, u8 *data, पूर्णांक len, पूर्णांक len_result)
अणु
	पूर्णांक actual_len;
	पूर्णांक err;

	अगर (mutex_lock_पूर्णांकerruptible(&ttusb->semusb) < 0)
		वापस -EAGAIN;

	अगर (debug >= 3)
		dprपूर्णांकk("> %*ph\n", len, data);

	स_नकल(data, ttusb->send_buf, len);

	err = usb_bulk_msg(ttusb->dev, ttusb->bulk_out_pipe,
			   ttusb->send_buf, len, &actual_len, 1000);
	अगर (err != 0) अणु
		dprपूर्णांकk("usb_bulk_msg(send) failed, err == %i!\n", err);
		जाओ err;
	पूर्ण
	अगर (actual_len != len) अणु
		err = -EIO;
		dprपूर्णांकk("only wrote %d of %d bytes\n",
			actual_len, len);
		जाओ err;
	पूर्ण

	err = usb_bulk_msg(ttusb->dev, ttusb->bulk_in_pipe,
			   ttusb->last_result, MAX_RCV, &actual_len, 1000);

	अगर (err != 0) अणु
		pr_err("cmd xter failed, receive error %d\n", err);
		जाओ err;
	पूर्ण

	अगर (debug >= 3) अणु
		actual_len = ttusb->last_result[3] + 4;
		dprपूर्णांकk("< %*ph\n", actual_len, ttusb->last_result);
	पूर्ण

	अगर (len_result)
		स_नकल(ttusb->send_buf, ttusb->last_result, len_result);

err:
	mutex_unlock(&ttusb->semusb);
	वापस err;
पूर्ण

अटल पूर्णांक ttusb_i2c_msg(काष्ठा ttusb *ttusb,
		  u8 addr, u8 * snd_buf, u8 snd_len, u8 * rcv_buf,
		  u8 rcv_len)
अणु
	u8 b[MAX_SEND];
	u8 id = ++ttusb->c;
	पूर्णांक i, err;

	अगर (snd_len > MAX_SEND - 7 || rcv_len > MAX_RCV - 7)
		वापस -EINVAL;

	b[0] = 0xaa;
	b[1] = id;
	b[2] = 0x31;
	b[3] = snd_len + 3;
	b[4] = addr << 1;
	b[5] = snd_len;
	b[6] = rcv_len;

	क्रम (i = 0; i < snd_len; i++)
		b[7 + i] = snd_buf[i];

	err = ttusb_cmd(ttusb, b, snd_len + 7, MAX_RCV);

	अगर (err)
		वापस -EREMOTEIO;

	/* check अगर the i2c transaction was successful */
	अगर ((snd_len != b[5]) || (rcv_len != b[6])) वापस -EREMOTEIO;

	अगर (rcv_len > 0) अणु

		अगर (err || b[0] != 0x55 || b[1] != id) अणु
			dprपूर्णांकk("usb_bulk_msg(recv) failed, err == %i, id == %02x, b == ",
				err, id);
			वापस -EREMOTEIO;
		पूर्ण

		क्रम (i = 0; i < rcv_len; i++)
			rcv_buf[i] = b[7 + i];
	पूर्ण

	वापस rcv_len;
पूर्ण

अटल पूर्णांक master_xfer(काष्ठा i2c_adapter* adapter, काष्ठा i2c_msg *msg, पूर्णांक num)
अणु
	काष्ठा ttusb *ttusb = i2c_get_adapdata(adapter);
	पूर्णांक i = 0;
	पूर्णांक inc;

	अगर (mutex_lock_पूर्णांकerruptible(&ttusb->semi2c) < 0)
		वापस -EAGAIN;

	जबतक (i < num) अणु
		u8 addr, snd_len, rcv_len, *snd_buf, *rcv_buf;
		पूर्णांक err;

		अगर (num > i + 1 && (msg[i + 1].flags & I2C_M_RD)) अणु
			addr = msg[i].addr;
			snd_buf = msg[i].buf;
			snd_len = msg[i].len;
			rcv_buf = msg[i + 1].buf;
			rcv_len = msg[i + 1].len;
			inc = 2;
		पूर्ण अन्यथा अणु
			addr = msg[i].addr;
			snd_buf = msg[i].buf;
			snd_len = msg[i].len;
			rcv_buf = शून्य;
			rcv_len = 0;
			inc = 1;
		पूर्ण

		err = ttusb_i2c_msg(ttusb, addr,
				    snd_buf, snd_len, rcv_buf, rcv_len);

		अगर (err < rcv_len) अणु
			dprपूर्णांकk("i == %i\n", i);
			अवरोध;
		पूर्ण

		i += inc;
	पूर्ण

	mutex_unlock(&ttusb->semi2c);
	वापस i;
पूर्ण

अटल पूर्णांक ttusb_boot_dsp(काष्ठा ttusb *ttusb)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक i, err;
	u8 b[40];

	err = request_firmware(&fw, "ttusb-budget/dspbootcode.bin",
			       &ttusb->dev->dev);
	अगर (err) अणु
		pr_err("failed to request firmware\n");
		वापस err;
	पूर्ण

	/* BootBlock */
	b[0] = 0xaa;
	b[2] = 0x13;
	b[3] = 28;

	/* upload dsp code in 32 byte steps (36 didn't work क्रम me ...) */
	/* 32 is max packet size, no messages should be split. */
	क्रम (i = 0; i < fw->size; i += 28) अणु
		स_नकल(&b[4], &fw->data[i], 28);

		b[1] = ++ttusb->c;

		err = ttusb_cmd(ttusb, b, 32, 0);
		अगर (err)
			जाओ करोne;
	पूर्ण

	/* last block ... */
	b[1] = ++ttusb->c;
	b[2] = 0x13;
	b[3] = 0;

	err = ttusb_cmd(ttusb, b, 4, 0);
	अगर (err)
		जाओ करोne;

	/* BootEnd */
	b[1] = ++ttusb->c;
	b[2] = 0x14;
	b[3] = 0;

	err = ttusb_cmd(ttusb, b, 4, 0);

      करोne:
	release_firmware(fw);
	अगर (err) अणु
		dprपूर्णांकk("usb_bulk_msg() failed, return value %i!\n", err);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ttusb_set_channel(काष्ठा ttusb *ttusb, पूर्णांक chan_id, पूर्णांक filter_type,
		      पूर्णांक pid)
अणु
	पूर्णांक err;
	/* SetChannel */
	u8 b[] = अणु 0xaa, ++ttusb->c, 0x22, 4, chan_id, filter_type,
		(pid >> 8) & 0xff, pid & 0xff
	पूर्ण;

	err = ttusb_cmd(ttusb, b, माप(b), 0);
	वापस err;
पूर्ण

अटल पूर्णांक ttusb_del_channel(काष्ठा ttusb *ttusb, पूर्णांक channel_id)
अणु
	पूर्णांक err;
	/* DelChannel */
	u8 b[] = अणु 0xaa, ++ttusb->c, 0x23, 1, channel_id पूर्ण;

	err = ttusb_cmd(ttusb, b, माप(b), 0);
	वापस err;
पूर्ण

#अगर_घोषित TTUSB_HWSECTIONS
अटल पूर्णांक ttusb_set_filter(काष्ठा ttusb *ttusb, पूर्णांक filter_id,
		     पूर्णांक associated_chan, u8 filter[8], u8 mask[8])
अणु
	पूर्णांक err;
	/* SetFilter */
	u8 b[] = अणु 0xaa, 0, 0x24, 0x1a, filter_id, associated_chan,
		filter[0], filter[1], filter[2], filter[3],
		filter[4], filter[5], filter[6], filter[7],
		filter[8], filter[9], filter[10], filter[11],
		mask[0], mask[1], mask[2], mask[3],
		mask[4], mask[5], mask[6], mask[7],
		mask[8], mask[9], mask[10], mask[11]
	पूर्ण;

	err = ttusb_cmd(ttusb, b, माप(b), 0);
	वापस err;
पूर्ण

अटल पूर्णांक ttusb_del_filter(काष्ठा ttusb *ttusb, पूर्णांक filter_id)
अणु
	पूर्णांक err;
	/* DelFilter */
	u8 b[] = अणु 0xaa, ++ttusb->c, 0x25, 1, filter_id पूर्ण;

	err = ttusb_cmd(ttusb, b, माप(b), 0);
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ttusb_init_controller(काष्ठा ttusb *ttusb)
अणु
	u8 b0[] = अणु 0xaa, ++ttusb->c, 0x15, 1, 0 पूर्ण;
	u8 b1[] = अणु 0xaa, ++ttusb->c, 0x15, 1, 1 पूर्ण;
	u8 b2[] = अणु 0xaa, ++ttusb->c, 0x32, 1, 0 पूर्ण;
	/* i2c ग_लिखो पढ़ो: 5 bytes, addr 0x10, 0x02 bytes ग_लिखो, 1 bytes पढ़ो. */
	u8 b3[] =
	    अणु 0xaa, ++ttusb->c, 0x31, 5, 0x10, 0x02, 0x01, 0x00, 0x1e पूर्ण;

	u8 get_version[] = अणु 0xaa, ++ttusb->c, 0x17, 5, 0, 0, 0, 0, 0 पूर्ण;
	u8 get_dsp_version[0x20] =
	    अणु 0xaa, ++ttusb->c, 0x26, 28, 0, 0, 0, 0, 0 पूर्ण;
	पूर्णांक err;

	/* reset board */
	अगर ((err = ttusb_cmd(ttusb, b0, माप(b0), 0)))
		वापस err;

	/* reset board (again?) */
	अगर ((err = ttusb_cmd(ttusb, b1, माप(b1), 0)))
		वापस err;

	ttusb_boot_dsp(ttusb);

	/* set i2c bit rate */
	अगर ((err = ttusb_cmd(ttusb, b2, माप(b2), 0)))
		वापस err;

	अगर ((err = ttusb_cmd(ttusb, b3, माप(b3), 0)))
		वापस err;

	अगर ((err = ttusb_cmd(ttusb, get_version,
			     माप(get_version), माप(get_version))))
		वापस err;

	dprपूर्णांकk("stc-version: %c%c%c%c%c\n", get_version[4], get_version[5],
		get_version[6], get_version[7], get_version[8]);

	अगर (स_भेद(get_version + 4, "V 0.0", 5) &&
	    स_भेद(get_version + 4, "V 1.1", 5) &&
	    स_भेद(get_version + 4, "V 2.1", 5) &&
	    स_भेद(get_version + 4, "V 2.2", 5)) अणु
		pr_err("unknown STC version %c%c%c%c%c, please report!\n",
		       get_version[4], get_version[5],
		       get_version[6], get_version[7], get_version[8]);
	पूर्ण

	ttusb->revision = ((get_version[6] - '0') << 4) |
			   (get_version[8] - '0');

	err =
	    ttusb_cmd(ttusb, get_dsp_version,
		      माप(get_dsp_version), माप(get_dsp_version));
	अगर (err)
		वापस err;

	pr_info("dsp-version: %c%c%c\n",
	       get_dsp_version[4], get_dsp_version[5], get_dsp_version[6]);
	वापस 0;
पूर्ण

#अगर_घोषित TTUSB_DISEQC
अटल पूर्णांक ttusb_send_diseqc(काष्ठा dvb_frontend* fe,
			     स्थिर काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	काष्ठा ttusb* ttusb = (काष्ठा ttusb*) fe->dvb->priv;
	u8 b[12] = अणु 0xaa, ++ttusb->c, 0x18 पूर्ण;

	पूर्णांक err;

	b[3] = 4 + 2 + cmd->msg_len;
	b[4] = 0xFF;		/* send diseqc master, not burst */
	b[5] = cmd->msg_len;

	स_नकल(b + 5, cmd->msg, cmd->msg_len);

	/* Diseqc */
	अगर ((err = ttusb_cmd(ttusb, b, 4 + b[3], 0))) अणु
		dprपूर्णांकk("usb_bulk_msg() failed, return value %i!\n", err);
	पूर्ण

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ttusb_update_lnb(काष्ठा ttusb *ttusb)
अणु
	u8 b[] = अणु 0xaa, ++ttusb->c, 0x16, 5, /*घातer: */ 1,
		ttusb->voltage == SEC_VOLTAGE_18 ? 0 : 1,
		ttusb->tone == SEC_TONE_ON ? 1 : 0, 1, 1
	पूर्ण;
	पूर्णांक err;

	/* SetLNB */
	अगर ((err = ttusb_cmd(ttusb, b, माप(b), 0))) अणु
		dprपूर्णांकk("usb_bulk_msg() failed, return value %i!\n", err);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ttusb_set_voltage(काष्ठा dvb_frontend *fe,
			     क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा ttusb* ttusb = (काष्ठा ttusb*) fe->dvb->priv;

	ttusb->voltage = voltage;
	वापस ttusb_update_lnb(ttusb);
पूर्ण

#अगर_घोषित TTUSB_TONE
अटल पूर्णांक ttusb_set_tone(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा ttusb* ttusb = (काष्ठा ttusb*) fe->dvb->priv;

	ttusb->tone = tone;
	वापस ttusb_update_lnb(ttusb);
पूर्ण
#पूर्ण_अगर


#अगर 0
अटल व्योम ttusb_set_led_freq(काष्ठा ttusb *ttusb, u8 freq)
अणु
	u8 b[] = अणु 0xaa, ++ttusb->c, 0x19, 1, freq पूर्ण;
	पूर्णांक err, actual_len;

	err = ttusb_cmd(ttusb, b, माप(b), 0);
	अगर (err) अणु
		dprपूर्णांकk("usb_bulk_msg() failed, return value %i!\n", err);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*****************************************************************************/

#अगर_घोषित TTUSB_HWSECTIONS
अटल व्योम ttusb_handle_ts_data(काष्ठा ttusb_channel *channel,
				 स्थिर u8 * data, पूर्णांक len);
अटल व्योम ttusb_handle_sec_data(काष्ठा ttusb_channel *channel,
				  स्थिर u8 * data, पूर्णांक len);
#पूर्ण_अगर

अटल पूर्णांक numpkt, numts, numstuff, numsec, numinvalid;
अटल अचिन्हित दीर्घ lastj;

अटल व्योम ttusb_process_muxpack(काष्ठा ttusb *ttusb, स्थिर u8 * muxpack,
			   पूर्णांक len)
अणु
	u16 csum = 0, cc;
	पूर्णांक i;

	अगर (len < 4 || len & 0x1) अणु
		pr_warn("muxpack has invalid len %d\n", len);
		numinvalid++;
		वापस;
	पूर्ण

	क्रम (i = 0; i < len; i += 2)
		csum ^= le16_to_cpup((__le16 *) (muxpack + i));
	अगर (csum) अणु
		pr_warn("muxpack with incorrect checksum, ignoring\n");
		numinvalid++;
		वापस;
	पूर्ण

	cc = (muxpack[len - 4] << 8) | muxpack[len - 3];
	cc &= 0x7FFF;
	अगर ((cc != ttusb->cc) && (ttusb->cc != -1))
		pr_warn("cc discontinuity (%d frames missing)\n",
			(cc - ttusb->cc) & 0x7FFF);
	ttusb->cc = (cc + 1) & 0x7FFF;
	अगर (muxpack[0] & 0x80) अणु
#अगर_घोषित TTUSB_HWSECTIONS
		/* section data */
		पूर्णांक pusi = muxpack[0] & 0x40;
		पूर्णांक channel = muxpack[0] & 0x1F;
		पूर्णांक payload = muxpack[1];
		स्थिर u8 *data = muxpack + 2;
		/* check offset flag */
		अगर (muxpack[0] & 0x20)
			data++;

		ttusb_handle_sec_data(ttusb->channel + channel, data,
				      payload);
		data += payload;

		अगर ((!!(ttusb->muxpack[0] & 0x20)) ^
		    !!(ttusb->muxpack[1] & 1))
			data++;
#warning TODO: pusi
		dprपूर्णांकk("cc: %04x\n", (data[0] << 8) | data[1]);
#पूर्ण_अगर
		numsec++;
	पूर्ण अन्यथा अगर (muxpack[0] == 0x47) अणु
#अगर_घोषित TTUSB_HWSECTIONS
		/* we have TS data here! */
		पूर्णांक pid = ((muxpack[1] & 0x0F) << 8) | muxpack[2];
		पूर्णांक channel;
		क्रम (channel = 0; channel < TTUSB_MAXCHANNEL; ++channel)
			अगर (ttusb->channel[channel].active
			    && (pid == ttusb->channel[channel].pid))
				ttusb_handle_ts_data(ttusb->channel +
						     channel, muxpack,
						     188);
#पूर्ण_अगर
		numts++;
		dvb_dmx_swfilter_packets(&ttusb->dvb_demux, muxpack, 1);
	पूर्ण अन्यथा अगर (muxpack[0] != 0) अणु
		numinvalid++;
		pr_err("illegal muxpack type %02x\n", muxpack[0]);
	पूर्ण अन्यथा
		numstuff++;
पूर्ण

अटल व्योम ttusb_process_frame(काष्ठा ttusb *ttusb, u8 * data, पूर्णांक len)
अणु
	पूर्णांक maxwork = 1024;
	जबतक (len) अणु
		अगर (!(maxwork--)) अणु
			pr_err("too much work\n");
			अवरोध;
		पूर्ण

		चयन (ttusb->mux_state) अणु
		हाल 0:
		हाल 1:
		हाल 2:
			len--;
			अगर (*data++ == 0xAA)
				++ttusb->mux_state;
			अन्यथा अणु
				ttusb->mux_state = 0;
				अगर (ttusb->insync) अणु
					pr_info("lost sync.\n");
					ttusb->insync = 0;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 3:
			ttusb->insync = 1;
			len--;
			ttusb->mux_npacks = *data++;
			++ttusb->mux_state;
			ttusb->muxpack_ptr = 0;
			/* maximum bytes, until we know the length */
			ttusb->muxpack_len = 2;
			अवरोध;
		हाल 4:
			अणु
				पूर्णांक avail;
				avail = len;
				अगर (avail >
				    (ttusb->muxpack_len -
				     ttusb->muxpack_ptr))
					avail =
					    ttusb->muxpack_len -
					    ttusb->muxpack_ptr;
				स_नकल(ttusb->muxpack + ttusb->muxpack_ptr,
				       data, avail);
				ttusb->muxpack_ptr += avail;
				BUG_ON(ttusb->muxpack_ptr > 264);
				data += avail;
				len -= avail;
				/* determine length */
				अगर (ttusb->muxpack_ptr == 2) अणु
					अगर (ttusb->muxpack[0] & 0x80) अणु
						ttusb->muxpack_len =
						    ttusb->muxpack[1] + 2;
						अगर (ttusb->
						    muxpack[0] & 0x20)
							ttusb->
							    muxpack_len++;
						अगर ((!!
						     (ttusb->
						      muxpack[0] & 0x20)) ^
						    !!(ttusb->
						       muxpack[1] & 1))
							ttusb->
							    muxpack_len++;
						ttusb->muxpack_len += 4;
					पूर्ण अन्यथा अगर (ttusb->muxpack[0] ==
						   0x47)
						ttusb->muxpack_len =
						    188 + 4;
					अन्यथा अगर (ttusb->muxpack[0] == 0x00)
						ttusb->muxpack_len =
						    ttusb->muxpack[1] + 2 +
						    4;
					अन्यथा अणु
						dprपूर्णांकk("invalid state: first byte is %x\n",
							ttusb->muxpack[0]);
						ttusb->mux_state = 0;
					पूर्ण
				पूर्ण

			/*
			 * अगर length is valid and we reached the end:
			 * जाओ next muxpack
			 */
				अगर ((ttusb->muxpack_ptr >= 2) &&
				    (ttusb->muxpack_ptr ==
				     ttusb->muxpack_len)) अणु
					ttusb_process_muxpack(ttusb,
							      ttusb->
							      muxpack,
							      ttusb->
							      muxpack_ptr);
					ttusb->muxpack_ptr = 0;
					/* maximum bytes, until we know the length */
					ttusb->muxpack_len = 2;

				/*
				 * no muxpacks left?
				 * वापस to search-sync state
				 */
					अगर (!ttusb->mux_npacks--) अणु
						ttusb->mux_state = 0;
						अवरोध;
					पूर्ण
				पूर्ण
				अवरोध;
			पूर्ण
		शेष:
			BUG();
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ttusb_iso_irq(काष्ठा urb *urb)
अणु
	काष्ठा ttusb *ttusb = urb->context;
	काष्ठा usb_iso_packet_descriptor *d;
	u8 *data;
	पूर्णांक len, i;

	अगर (!ttusb->iso_streaming)
		वापस;

	अगर (!urb->status) अणु
		क्रम (i = 0; i < urb->number_of_packets; ++i) अणु
			numpkt++;
			अगर (समय_after_eq(jअगरfies, lastj + HZ)) अणु
				dprपूर्णांकk("frames/s: %lu (ts: %d, stuff %d, sec: %d, invalid: %d, all: %d)\n",
					numpkt * HZ / (jअगरfies - lastj),
					numts, numstuff, numsec, numinvalid,
					numts + numstuff + numsec + numinvalid);
				numts = numstuff = numsec = numinvalid = 0;
				lastj = jअगरfies;
				numpkt = 0;
			पूर्ण
			d = &urb->iso_frame_desc[i];
			data = urb->transfer_buffer + d->offset;
			len = d->actual_length;
			d->actual_length = 0;
			d->status = 0;
			ttusb_process_frame(ttusb, data, len);
		पूर्ण
	पूर्ण
	usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

अटल व्योम ttusb_मुक्त_iso_urbs(काष्ठा ttusb *ttusb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ISO_BUF_COUNT; i++)
		usb_मुक्त_urb(ttusb->iso_urb[i]);
	kमुक्त(ttusb->iso_buffer);
पूर्ण

अटल पूर्णांक ttusb_alloc_iso_urbs(काष्ठा ttusb *ttusb)
अणु
	पूर्णांक i;

	ttusb->iso_buffer = kसुस्मृति(FRAMES_PER_ISO_BUF * ISO_BUF_COUNT,
			ISO_FRAME_SIZE, GFP_KERNEL);
	अगर (!ttusb->iso_buffer)
		वापस -ENOMEM;

	क्रम (i = 0; i < ISO_BUF_COUNT; i++) अणु
		काष्ठा urb *urb;

		अगर (!
		    (urb =
		     usb_alloc_urb(FRAMES_PER_ISO_BUF, GFP_ATOMIC))) अणु
			ttusb_मुक्त_iso_urbs(ttusb);
			वापस -ENOMEM;
		पूर्ण

		ttusb->iso_urb[i] = urb;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ttusb_stop_iso_xfer(काष्ठा ttusb *ttusb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ISO_BUF_COUNT; i++)
		usb_समाप्त_urb(ttusb->iso_urb[i]);

	ttusb->iso_streaming = 0;
पूर्ण

अटल पूर्णांक ttusb_start_iso_xfer(काष्ठा ttusb *ttusb)
अणु
	पूर्णांक i, j, err, buffer_offset = 0;

	अगर (ttusb->iso_streaming) अणु
		pr_err("iso xfer already running!\n");
		वापस 0;
	पूर्ण

	ttusb->cc = -1;
	ttusb->insync = 0;
	ttusb->mux_state = 0;

	क्रम (i = 0; i < ISO_BUF_COUNT; i++) अणु
		पूर्णांक frame_offset = 0;
		काष्ठा urb *urb = ttusb->iso_urb[i];

		urb->dev = ttusb->dev;
		urb->context = ttusb;
		urb->complete = ttusb_iso_irq;
		urb->pipe = ttusb->isoc_in_pipe;
		urb->transfer_flags = URB_ISO_ASAP;
		urb->पूर्णांकerval = 1;
		urb->number_of_packets = FRAMES_PER_ISO_BUF;
		urb->transfer_buffer_length =
		    ISO_FRAME_SIZE * FRAMES_PER_ISO_BUF;
		urb->transfer_buffer = ttusb->iso_buffer + buffer_offset;
		buffer_offset += ISO_FRAME_SIZE * FRAMES_PER_ISO_BUF;

		क्रम (j = 0; j < FRAMES_PER_ISO_BUF; j++) अणु
			urb->iso_frame_desc[j].offset = frame_offset;
			urb->iso_frame_desc[j].length = ISO_FRAME_SIZE;
			frame_offset += ISO_FRAME_SIZE;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ISO_BUF_COUNT; i++) अणु
		अगर ((err = usb_submit_urb(ttusb->iso_urb[i], GFP_ATOMIC))) अणु
			ttusb_stop_iso_xfer(ttusb);
			pr_err("failed urb submission (%i: err = %i)!\n",
			       i, err);
			वापस err;
		पूर्ण
	पूर्ण

	ttusb->iso_streaming = 1;

	वापस 0;
पूर्ण

#अगर_घोषित TTUSB_HWSECTIONS
अटल व्योम ttusb_handle_ts_data(काष्ठा dvb_demux_feed *dvbdmxfeed, स्थिर u8 * data,
			  पूर्णांक len)
अणु
	dvbdmxfeed->cb.ts(data, len, 0, 0, &dvbdmxfeed->feed.ts, 0);
पूर्ण

अटल व्योम ttusb_handle_sec_data(काष्ठा dvb_demux_feed *dvbdmxfeed, स्थिर u8 * data,
			   पूर्णांक len)
अणु
//      काष्ठा dvb_demux_feed *dvbdmxfeed = channel->dvbdmxfeed;
#त्रुटि TODO: handle ugly stuff
//      dvbdmxfeed->cb.sec(data, len, 0, 0, &dvbdmxfeed->feed.sec, 0);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ttusb_start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा ttusb *ttusb = (काष्ठा ttusb *) dvbdmxfeed->demux;
	पूर्णांक feed_type = 1;

	dprपूर्णांकk("ttusb_start_feed\n");

	चयन (dvbdmxfeed->type) अणु
	हाल DMX_TYPE_TS:
		अवरोध;
	हाल DMX_TYPE_SEC:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (dvbdmxfeed->type == DMX_TYPE_TS) अणु
		चयन (dvbdmxfeed->pes_type) अणु
		हाल DMX_PES_VIDEO:
		हाल DMX_PES_AUDIO:
		हाल DMX_PES_TELETEXT:
		हाल DMX_PES_PCR:
		हाल DMX_PES_OTHER:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

#अगर_घोषित TTUSB_HWSECTIONS
#त्रुटि TODO: allocate filters
	अगर (dvbdmxfeed->type == DMX_TYPE_TS) अणु
		feed_type = 1;
	पूर्ण अन्यथा अगर (dvbdmxfeed->type == DMX_TYPE_SEC) अणु
		feed_type = 2;
	पूर्ण
#पूर्ण_अगर

	ttusb_set_channel(ttusb, dvbdmxfeed->index, feed_type, dvbdmxfeed->pid);

	अगर (0 == ttusb->running_feed_count++)
		ttusb_start_iso_xfer(ttusb);

	वापस 0;
पूर्ण

अटल पूर्णांक ttusb_stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा ttusb *ttusb = (काष्ठा ttusb *) dvbdmxfeed->demux;

	ttusb_del_channel(ttusb, dvbdmxfeed->index);

	अगर (--ttusb->running_feed_count == 0)
		ttusb_stop_iso_xfer(ttusb);

	वापस 0;
पूर्ण

अटल पूर्णांक ttusb_setup_पूर्णांकerfaces(काष्ठा ttusb *ttusb)
अणु
	usb_set_पूर्णांकerface(ttusb->dev, 1, 1);

	ttusb->bulk_out_pipe = usb_sndbulkpipe(ttusb->dev, 1);
	ttusb->bulk_in_pipe = usb_rcvbulkpipe(ttusb->dev, 1);
	ttusb->isoc_in_pipe = usb_rcvisocpipe(ttusb->dev, 2);

	वापस 0;
पूर्ण

#अगर 0
अटल u8 stc_firmware[8192];

अटल पूर्णांक stc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ttusb *ttusb = file->निजी_data;
	पूर्णांक addr;

	क्रम (addr = 0; addr < 8192; addr += 16) अणु
		u8 snd_buf[2] = अणु addr >> 8, addr & 0xFF पूर्ण;
		ttusb_i2c_msg(ttusb, 0x50, snd_buf, 2, stc_firmware + addr,
			      16);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार stc_पढ़ो(काष्ठा file *file, अक्षर *buf, माप_प्रकार count,
		 loff_t *offset)
अणु
	वापस simple_पढ़ो_from_buffer(buf, count, offset, stc_firmware, 8192);
पूर्ण

अटल पूर्णांक stc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations stc_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = stc_पढ़ो,
	.खोलो = stc_खोलो,
	.release = stc_release,
पूर्ण;
#पूर्ण_अगर

अटल u32 functionality(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण



अटल पूर्णांक alps_tdmb7_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा ttusb* ttusb = (काष्ठा ttusb*) fe->dvb->priv;
	u8 data[4];
	काष्ठा i2c_msg msg = अणु.addr=0x61, .flags=0, .buf=data, .len=माप(data) पूर्ण;
	u32 भाग;

	भाग = (p->frequency + 36166667) / 166667;

	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = ((भाग >> 10) & 0x60) | 0x85;
	data[3] = p->frequency < 592000000 ? 0x40 : 0x80;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&ttusb->i2c_adap, &msg, 1) != 1) वापस -EIO;
	वापस 0;
पूर्ण

अटल काष्ठा cx22700_config alps_tdmb7_config = अणु
	.demod_address = 0x43,
पूर्ण;





अटल पूर्णांक philips_tdm1316l_tuner_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा ttusb* ttusb = (काष्ठा ttusb*) fe->dvb->priv;
	अटल u8 td1316_init[] = अणु 0x0b, 0xf5, 0x85, 0xab पूर्ण;
	अटल u8 disable_mc44BC374c[] = अणु 0x1d, 0x74, 0xa0, 0x68 पूर्ण;
	काष्ठा i2c_msg tuner_msg = अणु .addr=0x60, .flags=0, .buf=td1316_init, .len=माप(td1316_init) पूर्ण;

	// setup PLL configuration
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&ttusb->i2c_adap, &tuner_msg, 1) != 1) वापस -EIO;
	msleep(1);

	// disable the mc44BC374c (करो not check क्रम errors)
	tuner_msg.addr = 0x65;
	tuner_msg.buf = disable_mc44BC374c;
	tuner_msg.len = माप(disable_mc44BC374c);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&ttusb->i2c_adap, &tuner_msg, 1) != 1) अणु
		i2c_transfer(&ttusb->i2c_adap, &tuner_msg, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक philips_tdm1316l_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा ttusb* ttusb = (काष्ठा ttusb*) fe->dvb->priv;
	u8 tuner_buf[4];
	काष्ठा i2c_msg tuner_msg = अणु.addr=0x60, .flags=0, .buf=tuner_buf, .len=माप(tuner_buf) पूर्ण;
	पूर्णांक tuner_frequency = 0;
	u8 band, cp, filter;

	// determine अक्षरge pump
	tuner_frequency = p->frequency + 36130000;
	अगर (tuner_frequency < 87000000) वापस -EINVAL;
	अन्यथा अगर (tuner_frequency < 130000000) cp = 3;
	अन्यथा अगर (tuner_frequency < 160000000) cp = 5;
	अन्यथा अगर (tuner_frequency < 200000000) cp = 6;
	अन्यथा अगर (tuner_frequency < 290000000) cp = 3;
	अन्यथा अगर (tuner_frequency < 420000000) cp = 5;
	अन्यथा अगर (tuner_frequency < 480000000) cp = 6;
	अन्यथा अगर (tuner_frequency < 620000000) cp = 3;
	अन्यथा अगर (tuner_frequency < 830000000) cp = 5;
	अन्यथा अगर (tuner_frequency < 895000000) cp = 7;
	अन्यथा वापस -EINVAL;

	// determine band
	अगर (p->frequency < 49000000)
		वापस -EINVAL;
	अन्यथा अगर (p->frequency < 159000000)
		band = 1;
	अन्यथा अगर (p->frequency < 444000000)
		band = 2;
	अन्यथा अगर (p->frequency < 861000000)
		band = 4;
	अन्यथा वापस -EINVAL;

	// setup PLL filter
	चयन (p->bandwidth_hz) अणु
	हाल 6000000:
		tda1004x_ग_लिखोreg(fe, 0x0C, 0);
		filter = 0;
		अवरोध;

	हाल 7000000:
		tda1004x_ग_लिखोreg(fe, 0x0C, 0);
		filter = 0;
		अवरोध;

	हाल 8000000:
		tda1004x_ग_लिखोreg(fe, 0x0C, 0xFF);
		filter = 1;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	// calculate भागisor
	// ((36130000+((1000000/6)/2)) + Finput)/(1000000/6)
	tuner_frequency = (((p->frequency / 1000) * 6) + 217280) / 1000;

	// setup tuner buffer
	tuner_buf[0] = tuner_frequency >> 8;
	tuner_buf[1] = tuner_frequency & 0xff;
	tuner_buf[2] = 0xca;
	tuner_buf[3] = (cp << 5) | (filter << 3) | band;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&ttusb->i2c_adap, &tuner_msg, 1) != 1)
		वापस -EIO;

	msleep(1);
	वापस 0;
पूर्ण

अटल पूर्णांक philips_tdm1316l_request_firmware(काष्ठा dvb_frontend* fe, स्थिर काष्ठा firmware **fw, अक्षर* name)
अणु
	काष्ठा ttusb* ttusb = (काष्ठा ttusb*) fe->dvb->priv;

	वापस request_firmware(fw, name, &ttusb->dev->dev);
पूर्ण

अटल काष्ठा tda1004x_config philips_tdm1316l_config = अणु

	.demod_address = 0x8,
	.invert = 1,
	.invert_oclk = 0,
	.request_firmware = philips_tdm1316l_request_firmware,
पूर्ण;

अटल u8 alps_bsbe1_inittab[] = अणु
	0x01, 0x15,
	0x02, 0x30,
	0x03, 0x00,
	0x04, 0x7d,             /* F22FR = 0x7d, F22 = f_VCO / 128 / 0x7d = 22 kHz */
	0x05, 0x35,             /* I2CT = 0, SCLT = 1, SDAT = 1 */
	0x06, 0x40,             /* DAC not used, set to high impendance mode */
	0x07, 0x00,             /* DAC LSB */
	0x08, 0x40,             /* DiSEqC off, LNB घातer on OP2/LOCK pin on */
	0x09, 0x00,             /* FIFO */
	0x0c, 0x51,             /* OP1 ctl = Normal, OP1 val = 1 (LNB Power ON) */
	0x0d, 0x82,             /* DC offset compensation = ON, beta_agc1 = 2 */
	0x0e, 0x23,             /* alpha_पंचांगg = 2, beta_पंचांगg = 3 */
	0x10, 0x3f,             // AGC2  0x3d
	0x11, 0x84,
	0x12, 0xb9,
	0x15, 0xc9,             // lock detector threshold
	0x16, 0x00,
	0x17, 0x00,
	0x18, 0x00,
	0x19, 0x00,
	0x1a, 0x00,
	0x1f, 0x50,
	0x20, 0x00,
	0x21, 0x00,
	0x22, 0x00,
	0x23, 0x00,
	0x28, 0x00,             // out imp: normal  out type: parallel FEC mode:0
	0x29, 0x1e,             // 1/2 threshold
	0x2a, 0x14,             // 2/3 threshold
	0x2b, 0x0f,             // 3/4 threshold
	0x2c, 0x09,             // 5/6 threshold
	0x2d, 0x05,             // 7/8 threshold
	0x2e, 0x01,
	0x31, 0x1f,             // test all FECs
	0x32, 0x19,             // viterbi and synchro search
	0x33, 0xfc,             // rs control
	0x34, 0x93,             // error control
	0x0f, 0x92,
	0xff, 0xff
पूर्ण;

अटल u8 alps_bsru6_inittab[] = अणु
	0x01, 0x15,
	0x02, 0x30,
	0x03, 0x00,
	0x04, 0x7d,		/* F22FR = 0x7d, F22 = f_VCO / 128 / 0x7d = 22 kHz */
	0x05, 0x35,		/* I2CT = 0, SCLT = 1, SDAT = 1 */
	0x06, 0x40,		/* DAC not used, set to high impendance mode */
	0x07, 0x00,		/* DAC LSB */
	0x08, 0x40,		/* DiSEqC off, LNB घातer on OP2/LOCK pin on */
	0x09, 0x00,		/* FIFO */
	0x0c, 0x51,		/* OP1 ctl = Normal, OP1 val = 1 (LNB Power ON) */
	0x0d, 0x82,		/* DC offset compensation = ON, beta_agc1 = 2 */
	0x0e, 0x23,		/* alpha_पंचांगg = 2, beta_पंचांगg = 3 */
	0x10, 0x3f,		// AGC2  0x3d
	0x11, 0x84,
	0x12, 0xb9,
	0x15, 0xc9,		// lock detector threshold
	0x16, 0x00,
	0x17, 0x00,
	0x18, 0x00,
	0x19, 0x00,
	0x1a, 0x00,
	0x1f, 0x50,
	0x20, 0x00,
	0x21, 0x00,
	0x22, 0x00,
	0x23, 0x00,
	0x28, 0x00,		// out imp: normal  out type: parallel FEC mode:0
	0x29, 0x1e,		// 1/2 threshold
	0x2a, 0x14,		// 2/3 threshold
	0x2b, 0x0f,		// 3/4 threshold
	0x2c, 0x09,		// 5/6 threshold
	0x2d, 0x05,		// 7/8 threshold
	0x2e, 0x01,
	0x31, 0x1f,		// test all FECs
	0x32, 0x19,		// viterbi and synchro search
	0x33, 0xfc,		// rs control
	0x34, 0x93,		// error control
	0x0f, 0x52,
	0xff, 0xff
पूर्ण;

अटल पूर्णांक alps_stv0299_set_symbol_rate(काष्ठा dvb_frontend *fe, u32 srate, u32 ratio)
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
	stv0299_ग_लिखोreg(fe, 0x20, (ratio >> 8) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x21, (ratio) & 0xf0);

	वापस 0;
पूर्ण

अटल पूर्णांक philips_tsa5059_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा ttusb* ttusb = (काष्ठा ttusb*) fe->dvb->priv;
	u8 buf[4];
	u32 भाग;
	काष्ठा i2c_msg msg = अणु.addr = 0x61,.flags = 0,.buf = buf,.len = माप(buf) पूर्ण;

	अगर ((p->frequency < 950000) || (p->frequency > 2150000))
		वापस -EINVAL;

	भाग = (p->frequency + (125 - 1)) / 125;	/* round correctly */
	buf[0] = (भाग >> 8) & 0x7f;
	buf[1] = भाग & 0xff;
	buf[2] = 0x80 | ((भाग & 0x18000) >> 10) | 4;
	buf[3] = 0xC4;

	अगर (p->frequency > 1530000)
		buf[3] = 0xC0;

	/* BSBE1 wants XCE bit set */
	अगर (ttusb->revision == TTUSB_REV_2_2)
		buf[3] |= 0x20;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&ttusb->i2c_adap, &msg, 1) != 1)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल काष्ठा stv0299_config alps_stv0299_config = अणु
	.demod_address = 0x68,
	.inittab = alps_bsru6_inittab,
	.mclk = 88000000UL,
	.invert = 1,
	.skip_reinit = 0,
	.lock_output = STV0299_LOCKOUTPUT_1,
	.volt13_op0_op1 = STV0299_VOLT13_OP1,
	.min_delay_ms = 100,
	.set_symbol_rate = alps_stv0299_set_symbol_rate,
पूर्ण;

अटल पूर्णांक ttusb_novas_grundig_29504_491_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा ttusb* ttusb = (काष्ठा ttusb*) fe->dvb->priv;
	u8 buf[4];
	u32 भाग;
	काष्ठा i2c_msg msg = अणु.addr = 0x61,.flags = 0,.buf = buf,.len = माप(buf) पूर्ण;

	भाग = p->frequency / 125;

	buf[0] = (भाग >> 8) & 0x7f;
	buf[1] = भाग & 0xff;
	buf[2] = 0x8e;
	buf[3] = 0x00;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&ttusb->i2c_adap, &msg, 1) != 1)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल काष्ठा tda8083_config ttusb_novas_grundig_29504_491_config = अणु

	.demod_address = 0x68,
पूर्ण;

अटल पूर्णांक alps_tdbe2_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा ttusb* ttusb = fe->dvb->priv;
	u32 भाग;
	u8 data[4];
	काष्ठा i2c_msg msg = अणु .addr = 0x62, .flags = 0, .buf = data, .len = माप(data) पूर्ण;

	भाग = (p->frequency + 35937500 + 31250) / 62500;

	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = 0x85 | ((भाग >> 10) & 0x60);
	data[3] = (p->frequency < 174000000 ? 0x88 : p->frequency < 470000000 ? 0x84 : 0x81);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer (&ttusb->i2c_adap, &msg, 1) != 1)
		वापस -EIO;

	वापस 0;
पूर्ण


अटल काष्ठा ves1820_config alps_tdbe2_config = अणु
	.demod_address = 0x09,
	.xin = 57840000UL,
	.invert = 1,
	.selagc = VES1820_SELAGC_SIGNAMPERR,
पूर्ण;

अटल u8 पढ़ो_pwm(काष्ठा ttusb* ttusb)
अणु
	u8 b = 0xff;
	u8 pwm;
	काष्ठा i2c_msg msg[] = अणु अणु .addr = 0x50,.flags = 0,.buf = &b,.len = 1 पूर्ण,
				अणु .addr = 0x50,.flags = I2C_M_RD,.buf = &pwm,.len = 1पूर्ण पूर्ण;

	अगर ((i2c_transfer(&ttusb->i2c_adap, msg, 2) != 2) || (pwm == 0xff))
		pwm = 0x48;

	वापस pwm;
पूर्ण


अटल पूर्णांक dvbc_philips_tdm1316l_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा ttusb *ttusb = (काष्ठा ttusb *) fe->dvb->priv;
	u8 tuner_buf[5];
	काष्ठा i2c_msg tuner_msg = अणु.addr = 0x60,
				    .flags = 0,
				    .buf = tuner_buf,
				    .len = माप(tuner_buf) पूर्ण;
	पूर्णांक tuner_frequency = 0;
	u8 band, cp, filter;

	// determine अक्षरge pump
	tuner_frequency = p->frequency;
	अगर      (tuner_frequency <  87000000) अणुवापस -EINVAL;पूर्ण
	अन्यथा अगर (tuner_frequency < 130000000) अणुcp = 3; band = 1;पूर्ण
	अन्यथा अगर (tuner_frequency < 160000000) अणुcp = 5; band = 1;पूर्ण
	अन्यथा अगर (tuner_frequency < 200000000) अणुcp = 6; band = 1;पूर्ण
	अन्यथा अगर (tuner_frequency < 290000000) अणुcp = 3; band = 2;पूर्ण
	अन्यथा अगर (tuner_frequency < 420000000) अणुcp = 5; band = 2;पूर्ण
	अन्यथा अगर (tuner_frequency < 480000000) अणुcp = 6; band = 2;पूर्ण
	अन्यथा अगर (tuner_frequency < 620000000) अणुcp = 3; band = 4;पूर्ण
	अन्यथा अगर (tuner_frequency < 830000000) अणुcp = 5; band = 4;पूर्ण
	अन्यथा अगर (tuner_frequency < 895000000) अणुcp = 7; band = 4;पूर्ण
	अन्यथा अणुवापस -EINVAL;पूर्ण

	// assume PLL filter should always be 8MHz क्रम the moment.
	filter = 1;

	// calculate भागisor
	// (Finput + Fअगर)/Fref; Fअगर = 36125000 Hz, Fref = 62500 Hz
	tuner_frequency = ((p->frequency + 36125000) / 62500);

	// setup tuner buffer
	tuner_buf[0] = tuner_frequency >> 8;
	tuner_buf[1] = tuner_frequency & 0xff;
	tuner_buf[2] = 0xc8;
	tuner_buf[3] = (cp << 5) | (filter << 3) | band;
	tuner_buf[4] = 0x80;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&ttusb->i2c_adap, &tuner_msg, 1) != 1) अणु
		pr_err("dvbc_philips_tdm1316l_pll_set Error 1\n");
		वापस -EIO;
	पूर्ण

	msleep(50);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&ttusb->i2c_adap, &tuner_msg, 1) != 1) अणु
		pr_err("dvbc_philips_tdm1316l_pll_set Error 2\n");
		वापस -EIO;
	पूर्ण

	msleep(1);

	वापस 0;
पूर्ण

अटल u8 dvbc_philips_tdm1316l_inittab[] = अणु
	0x80, 0x21,
	0x80, 0x20,
	0x81, 0x01,
	0x81, 0x00,
	0x00, 0x09,
	0x01, 0x69,
	0x03, 0x00,
	0x04, 0x00,
	0x07, 0x00,
	0x08, 0x00,
	0x20, 0x00,
	0x21, 0x40,
	0x22, 0x00,
	0x23, 0x00,
	0x24, 0x40,
	0x25, 0x88,
	0x30, 0xff,
	0x31, 0x00,
	0x32, 0xff,
	0x33, 0x00,
	0x34, 0x50,
	0x35, 0x7f,
	0x36, 0x00,
	0x37, 0x20,
	0x38, 0x00,
	0x40, 0x1c,
	0x41, 0xff,
	0x42, 0x29,
	0x43, 0x20,
	0x44, 0xff,
	0x45, 0x00,
	0x46, 0x00,
	0x49, 0x04,
	0x4a, 0xff,
	0x4b, 0x7f,
	0x52, 0x30,
	0x55, 0xae,
	0x56, 0x47,
	0x57, 0xe1,
	0x58, 0x3a,
	0x5a, 0x1e,
	0x5b, 0x34,
	0x60, 0x00,
	0x63, 0x00,
	0x64, 0x00,
	0x65, 0x00,
	0x66, 0x00,
	0x67, 0x00,
	0x68, 0x00,
	0x69, 0x00,
	0x6a, 0x02,
	0x6b, 0x00,
	0x70, 0xff,
	0x71, 0x00,
	0x72, 0x00,
	0x73, 0x00,
	0x74, 0x0c,
	0x80, 0x00,
	0x81, 0x00,
	0x82, 0x00,
	0x83, 0x00,
	0x84, 0x04,
	0x85, 0x80,
	0x86, 0x24,
	0x87, 0x78,
	0x88, 0x00,
	0x89, 0x00,
	0x90, 0x01,
	0x91, 0x01,
	0xa0, 0x00,
	0xa1, 0x00,
	0xa2, 0x00,
	0xb0, 0x91,
	0xb1, 0x0b,
	0xc0, 0x4b,
	0xc1, 0x00,
	0xc2, 0x00,
	0xd0, 0x00,
	0xd1, 0x00,
	0xd2, 0x00,
	0xd3, 0x00,
	0xd4, 0x00,
	0xd5, 0x00,
	0xde, 0x00,
	0xdf, 0x00,
	0x61, 0x38,
	0x62, 0x0a,
	0x53, 0x13,
	0x59, 0x08,
	0x55, 0x00,
	0x56, 0x40,
	0x57, 0x08,
	0x58, 0x3d,
	0x88, 0x10,
	0xa0, 0x00,
	0xa0, 0x00,
	0xa0, 0x00,
	0xa0, 0x04,
	0xff, 0xff,
पूर्ण;

अटल काष्ठा stv0297_config dvbc_philips_tdm1316l_config = अणु
	.demod_address = 0x1c,
	.inittab = dvbc_philips_tdm1316l_inittab,
	.invert = 0,
पूर्ण;

अटल व्योम frontend_init(काष्ठा ttusb* ttusb)
अणु
	चयन(le16_to_cpu(ttusb->dev->descriptor.idProduct)) अणु
	हाल 0x1003: // Hauppauge/TT Nova-USB-S budget (stv0299/ALPS BSRU6|BSBE1(tsa5059))
		// try the stv0299 based first
		ttusb->fe = dvb_attach(stv0299_attach, &alps_stv0299_config, &ttusb->i2c_adap);
		अगर (ttusb->fe != शून्य) अणु
			ttusb->fe->ops.tuner_ops.set_params = philips_tsa5059_tuner_set_params;

			अगर(ttusb->revision == TTUSB_REV_2_2) अणु // ALPS BSBE1
				alps_stv0299_config.inittab = alps_bsbe1_inittab;
				dvb_attach(lnbp21_attach, ttusb->fe, &ttusb->i2c_adap, 0, 0);
			पूर्ण अन्यथा अणु // ALPS BSRU6
				ttusb->fe->ops.set_voltage = ttusb_set_voltage;
			पूर्ण
			अवरोध;
		पूर्ण

		// Grundig 29504-491
		ttusb->fe = dvb_attach(tda8083_attach, &ttusb_novas_grundig_29504_491_config, &ttusb->i2c_adap);
		अगर (ttusb->fe != शून्य) अणु
			ttusb->fe->ops.tuner_ops.set_params = ttusb_novas_grundig_29504_491_tuner_set_params;
			ttusb->fe->ops.set_voltage = ttusb_set_voltage;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 0x1004: // Hauppauge/TT DVB-C budget (ves1820/ALPS TDBE2(sp5659))
		ttusb->fe = dvb_attach(ves1820_attach, &alps_tdbe2_config, &ttusb->i2c_adap, पढ़ो_pwm(ttusb));
		अगर (ttusb->fe != शून्य) अणु
			ttusb->fe->ops.tuner_ops.set_params = alps_tdbe2_tuner_set_params;
			अवरोध;
		पूर्ण

		ttusb->fe = dvb_attach(stv0297_attach, &dvbc_philips_tdm1316l_config, &ttusb->i2c_adap);
		अगर (ttusb->fe != शून्य) अणु
			ttusb->fe->ops.tuner_ops.set_params = dvbc_philips_tdm1316l_tuner_set_params;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 0x1005: // Hauppauge/TT Nova-USB-t budget (tda10046/Philips td1316(tda6651tt) OR cx22700/ALPS TDMB7(??))
		// try the ALPS TDMB7 first
		ttusb->fe = dvb_attach(cx22700_attach, &alps_tdmb7_config, &ttusb->i2c_adap);
		अगर (ttusb->fe != शून्य) अणु
			ttusb->fe->ops.tuner_ops.set_params = alps_tdmb7_tuner_set_params;
			अवरोध;
		पूर्ण

		// Philips td1316
		ttusb->fe = dvb_attach(tda10046_attach, &philips_tdm1316l_config, &ttusb->i2c_adap);
		अगर (ttusb->fe != शून्य) अणु
			ttusb->fe->ops.tuner_ops.init = philips_tdm1316l_tuner_init;
			ttusb->fe->ops.tuner_ops.set_params = philips_tdm1316l_tuner_set_params;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (ttusb->fe == शून्य) अणु
		pr_err("no frontend driver found for device [%04x:%04x]\n",
		       le16_to_cpu(ttusb->dev->descriptor.idVenकरोr),
		       le16_to_cpu(ttusb->dev->descriptor.idProduct));
	पूर्ण अन्यथा अणु
		अगर (dvb_रेजिस्टर_frontend(&ttusb->adapter, ttusb->fe)) अणु
			pr_err("Frontend registration failed!\n");
			dvb_frontend_detach(ttusb->fe);
			ttusb->fe = शून्य;
		पूर्ण
	पूर्ण
पूर्ण



अटल स्थिर काष्ठा i2c_algorithm ttusb_dec_algo = अणु
	.master_xfer	= master_xfer,
	.functionality	= functionality,
पूर्ण;

अटल पूर्णांक ttusb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev;
	काष्ठा ttusb *ttusb;
	पूर्णांक result;

	dprपूर्णांकk("TTUSB DVB connected\n");

	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	अगर (पूर्णांकf->altsetting->desc.bInterfaceNumber != 1) वापस -ENODEV;

	अगर (!(ttusb = kzalloc(माप(काष्ठा ttusb), GFP_KERNEL)))
		वापस -ENOMEM;

	ttusb->dev = udev;
	ttusb->c = 0;
	ttusb->mux_state = 0;
	mutex_init(&ttusb->semi2c);

	mutex_lock(&ttusb->semi2c);

	mutex_init(&ttusb->semusb);

	ttusb_setup_पूर्णांकerfaces(ttusb);

	result = ttusb_alloc_iso_urbs(ttusb);
	अगर (result < 0) अणु
		dprपूर्णांकk("ttusb_alloc_iso_urbs - failed\n");
		mutex_unlock(&ttusb->semi2c);
		kमुक्त(ttusb);
		वापस result;
	पूर्ण

	अगर (ttusb_init_controller(ttusb))
		pr_err("ttusb_init_controller: error\n");

	mutex_unlock(&ttusb->semi2c);

	result = dvb_रेजिस्टर_adapter(&ttusb->adapter,
				      "Technotrend/Hauppauge Nova-USB",
				      THIS_MODULE, &udev->dev, adapter_nr);
	अगर (result < 0) अणु
		ttusb_मुक्त_iso_urbs(ttusb);
		kमुक्त(ttusb);
		वापस result;
	पूर्ण
	ttusb->adapter.priv = ttusb;

	/* i2c */
	स_रखो(&ttusb->i2c_adap, 0, माप(काष्ठा i2c_adapter));
	strscpy(ttusb->i2c_adap.name, "TTUSB DEC", माप(ttusb->i2c_adap.name));

	i2c_set_adapdata(&ttusb->i2c_adap, ttusb);

	ttusb->i2c_adap.algo              = &ttusb_dec_algo;
	ttusb->i2c_adap.algo_data         = शून्य;
	ttusb->i2c_adap.dev.parent	  = &udev->dev;

	result = i2c_add_adapter(&ttusb->i2c_adap);
	अगर (result)
		जाओ err_unरेजिस्टर_adapter;

	स_रखो(&ttusb->dvb_demux, 0, माप(ttusb->dvb_demux));

	ttusb->dvb_demux.dmx.capabilities =
	    DMX_TS_FILTERING | DMX_SECTION_FILTERING;
	ttusb->dvb_demux.priv = शून्य;
#अगर_घोषित TTUSB_HWSECTIONS
	ttusb->dvb_demux.filternum = TTUSB_MAXFILTER;
#अन्यथा
	ttusb->dvb_demux.filternum = 32;
#पूर्ण_अगर
	ttusb->dvb_demux.feednum = TTUSB_MAXCHANNEL;
	ttusb->dvb_demux.start_feed = ttusb_start_feed;
	ttusb->dvb_demux.stop_feed = ttusb_stop_feed;
	ttusb->dvb_demux.ग_लिखो_to_decoder = शून्य;

	result = dvb_dmx_init(&ttusb->dvb_demux);
	अगर (result < 0) अणु
		pr_err("dvb_dmx_init failed (errno = %d)\n", result);
		result = -ENODEV;
		जाओ err_i2c_del_adapter;
	पूर्ण
//FIXME dmxdev (nur WAS?)
	ttusb->dmxdev.filternum = ttusb->dvb_demux.filternum;
	ttusb->dmxdev.demux = &ttusb->dvb_demux.dmx;
	ttusb->dmxdev.capabilities = 0;

	result = dvb_dmxdev_init(&ttusb->dmxdev, &ttusb->adapter);
	अगर (result < 0) अणु
		pr_err("dvb_dmxdev_init failed (errno = %d)\n",
		       result);
		result = -ENODEV;
		जाओ err_release_dmx;
	पूर्ण

	अगर (dvb_net_init(&ttusb->adapter, &ttusb->dvbnet, &ttusb->dvb_demux.dmx)) अणु
		pr_err("dvb_net_init failed!\n");
		result = -ENODEV;
		जाओ err_release_dmxdev;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, (व्योम *) ttusb);

	frontend_init(ttusb);

	वापस 0;

err_release_dmxdev:
	dvb_dmxdev_release(&ttusb->dmxdev);
err_release_dmx:
	dvb_dmx_release(&ttusb->dvb_demux);
err_i2c_del_adapter:
	i2c_del_adapter(&ttusb->i2c_adap);
err_unरेजिस्टर_adapter:
	dvb_unरेजिस्टर_adapter (&ttusb->adapter);
	ttusb_मुक्त_iso_urbs(ttusb);
	kमुक्त(ttusb);
	वापस result;
पूर्ण

अटल व्योम ttusb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ttusb *ttusb = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	ttusb->disconnecting = 1;

	ttusb_stop_iso_xfer(ttusb);

	ttusb->dvb_demux.dmx.बंद(&ttusb->dvb_demux.dmx);
	dvb_net_release(&ttusb->dvbnet);
	dvb_dmxdev_release(&ttusb->dmxdev);
	dvb_dmx_release(&ttusb->dvb_demux);
	अगर (ttusb->fe != शून्य) अणु
		dvb_unरेजिस्टर_frontend(ttusb->fe);
		dvb_frontend_detach(ttusb->fe);
	पूर्ण
	i2c_del_adapter(&ttusb->i2c_adap);
	dvb_unरेजिस्टर_adapter(&ttusb->adapter);

	ttusb_मुक्त_iso_urbs(ttusb);

	kमुक्त(ttusb);

	dprपूर्णांकk("TTUSB DVB disconnected\n");
पूर्ण

अटल स्थिर काष्ठा usb_device_id ttusb_table[] = अणु
	अणुUSB_DEVICE(0xb48, 0x1003)पूर्ण,
	अणुUSB_DEVICE(0xb48, 0x1004)पूर्ण,
	अणुUSB_DEVICE(0xb48, 0x1005)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, ttusb_table);

अटल काष्ठा usb_driver ttusb_driver = अणु
      .name		= "ttusb",
      .probe		= ttusb_probe,
      .disconnect	= ttusb_disconnect,
      .id_table		= ttusb_table,
पूर्ण;

module_usb_driver(ttusb_driver);

MODULE_AUTHOR("Holger Waechtler <holger@convergence.de>");
MODULE_DESCRIPTION("TTUSB DVB Driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("ttusb-budget/dspbootcode.bin");
