<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <media/i2c/ir-kbd-i2c.h>
#समावेश "pvrusb2-i2c-core.h"
#समावेश "pvrusb2-hdw-internal.h"
#समावेश "pvrusb2-debug.h"
#समावेश "pvrusb2-fx2-cmd.h"
#समावेश "pvrusb2.h"

#घोषणा trace_i2c(...) pvr2_trace(PVR2_TRACE_I2C,__VA_ARGS__)

/*

  This module attempts to implement a compliant I2C adapter क्रम the pvrusb2
  device.

*/

अटल अचिन्हित पूर्णांक i2c_scan;
module_param(i2c_scan, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(i2c_scan,"scan i2c bus at insmod time");

अटल पूर्णांक ir_mode[PVR_NUM] = अणु [0 ... PVR_NUM-1] = 1 पूर्ण;
module_param_array(ir_mode, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(ir_mode,"specify: 0=disable IR reception, 1=normal IR");

अटल पूर्णांक pvr2_disable_ir_video;
module_param_named(disable_स्वतःload_ir_video, pvr2_disable_ir_video,
		   पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(disable_स्वतःload_ir_video,
		 "1=do not try to autoload ir_video IR receiver");

अटल पूर्णांक pvr2_i2c_ग_लिखो(काष्ठा pvr2_hdw *hdw, /* Context */
			  u8 i2c_addr,      /* I2C address we're talking to */
			  u8 *data,         /* Data to ग_लिखो */
			  u16 length)       /* Size of data to ग_लिखो */
अणु
	/* Return value - शेष 0 means success */
	पूर्णांक ret;


	अगर (!data) length = 0;
	अगर (length > (माप(hdw->cmd_buffer) - 3)) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Killing an I2C write to %u that is too large (desired=%u limit=%u)",
			   i2c_addr,
			   length,(अचिन्हित पूर्णांक)(माप(hdw->cmd_buffer) - 3));
		वापस -ENOTSUPP;
	पूर्ण

	LOCK_TAKE(hdw->ctl_lock);

	/* Clear the command buffer (likely to be paranoia) */
	स_रखो(hdw->cmd_buffer, 0, माप(hdw->cmd_buffer));

	/* Set up command buffer क्रम an I2C ग_लिखो */
	hdw->cmd_buffer[0] = FX2CMD_I2C_WRITE;      /* ग_लिखो prefix */
	hdw->cmd_buffer[1] = i2c_addr;  /* i2c addr of chip */
	hdw->cmd_buffer[2] = length;    /* length of what follows */
	अगर (length) स_नकल(hdw->cmd_buffer + 3, data, length);

	/* Do the operation */
	ret = pvr2_send_request(hdw,
				hdw->cmd_buffer,
				length + 3,
				hdw->cmd_buffer,
				1);
	अगर (!ret) अणु
		अगर (hdw->cmd_buffer[0] != 8) अणु
			ret = -EIO;
			अगर (hdw->cmd_buffer[0] != 7) अणु
				trace_i2c("unexpected status from i2_write[%d]: %d",
					  i2c_addr,hdw->cmd_buffer[0]);
			पूर्ण
		पूर्ण
	पूर्ण

	LOCK_GIVE(hdw->ctl_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_i2c_पढ़ो(काष्ठा pvr2_hdw *hdw, /* Context */
			 u8 i2c_addr,       /* I2C address we're talking to */
			 u8 *data,          /* Data to ग_लिखो */
			 u16 dlen,          /* Size of data to ग_लिखो */
			 u8 *res,           /* Where to put data we पढ़ो */
			 u16 rlen)          /* Amount of data to पढ़ो */
अणु
	/* Return value - शेष 0 means success */
	पूर्णांक ret;


	अगर (!data) dlen = 0;
	अगर (dlen > (माप(hdw->cmd_buffer) - 4)) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Killing an I2C read to %u that has wlen too large (desired=%u limit=%u)",
			   i2c_addr,
			   dlen,(अचिन्हित पूर्णांक)(माप(hdw->cmd_buffer) - 4));
		वापस -ENOTSUPP;
	पूर्ण
	अगर (res && (rlen > (माप(hdw->cmd_buffer) - 1))) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Killing an I2C read to %u that has rlen too large (desired=%u limit=%u)",
			   i2c_addr,
			   rlen,(अचिन्हित पूर्णांक)(माप(hdw->cmd_buffer) - 1));
		वापस -ENOTSUPP;
	पूर्ण

	LOCK_TAKE(hdw->ctl_lock);

	/* Clear the command buffer (likely to be paranoia) */
	स_रखो(hdw->cmd_buffer, 0, माप(hdw->cmd_buffer));

	/* Set up command buffer क्रम an I2C ग_लिखो followed by a पढ़ो */
	hdw->cmd_buffer[0] = FX2CMD_I2C_READ;  /* पढ़ो prefix */
	hdw->cmd_buffer[1] = dlen;  /* arg length */
	hdw->cmd_buffer[2] = rlen;  /* answer length. Device will send one
				       more byte (status). */
	hdw->cmd_buffer[3] = i2c_addr;  /* i2c addr of chip */
	अगर (dlen) स_नकल(hdw->cmd_buffer + 4, data, dlen);

	/* Do the operation */
	ret = pvr2_send_request(hdw,
				hdw->cmd_buffer,
				4 + dlen,
				hdw->cmd_buffer,
				rlen + 1);
	अगर (!ret) अणु
		अगर (hdw->cmd_buffer[0] != 8) अणु
			ret = -EIO;
			अगर (hdw->cmd_buffer[0] != 7) अणु
				trace_i2c("unexpected status from i2_read[%d]: %d",
					  i2c_addr,hdw->cmd_buffer[0]);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Copy back the result */
	अगर (res && rlen) अणु
		अगर (ret) अणु
			/* Error, just blank out the वापस buffer */
			स_रखो(res, 0, rlen);
		पूर्ण अन्यथा अणु
			स_नकल(res, hdw->cmd_buffer + 1, rlen);
		पूर्ण
	पूर्ण

	LOCK_GIVE(hdw->ctl_lock);

	वापस ret;
पूर्ण

/* This is the common low level entry poपूर्णांक क्रम करोing I2C operations to the
   hardware. */
अटल पूर्णांक pvr2_i2c_basic_op(काष्ठा pvr2_hdw *hdw,
			     u8 i2c_addr,
			     u8 *wdata,
			     u16 wlen,
			     u8 *rdata,
			     u16 rlen)
अणु
	अगर (!rdata) rlen = 0;
	अगर (!wdata) wlen = 0;
	अगर (rlen || !wlen) अणु
		वापस pvr2_i2c_पढ़ो(hdw,i2c_addr,wdata,wlen,rdata,rlen);
	पूर्ण अन्यथा अणु
		वापस pvr2_i2c_ग_लिखो(hdw,i2c_addr,wdata,wlen);
	पूर्ण
पूर्ण


/* This is a special entry poपूर्णांक क्रम हालs of I2C transaction attempts to
   the IR receiver.  The implementation here simulates the IR receiver by
   issuing a command to the FX2 firmware and using that response to वापस
   what the real I2C receiver would have वापसed.  We use this क्रम 24xxx
   devices, where the IR receiver chip has been हटाओd and replaced with
   FX2 related logic. */
अटल पूर्णांक i2c_24xxx_ir(काष्ठा pvr2_hdw *hdw,
			u8 i2c_addr,u8 *wdata,u16 wlen,u8 *rdata,u16 rlen)
अणु
	u8 dat[4];
	अचिन्हित पूर्णांक stat;

	अगर (!(rlen || wlen)) अणु
		/* This is a probe attempt.  Just let it succeed. */
		वापस 0;
	पूर्ण

	/* We करोn't understand this kind of transaction */
	अगर ((wlen != 0) || (rlen == 0)) वापस -EIO;

	अगर (rlen < 3) अणु
		/* Mike Isely <isely@pobox.com> Appears to be a probe
		   attempt from lirc.  Just fill in zeroes and वापस.  If
		   we try instead to करो the full transaction here, then bad
		   things seem to happen within the lirc driver module
		   (version 0.8.0-7 sources from Debian, when run under
		   vanilla 2.6.17.6 kernel) - and I करोn't have the patience
		   to chase it करोwn. */
		अगर (rlen > 0) rdata[0] = 0;
		अगर (rlen > 1) rdata[1] = 0;
		वापस 0;
	पूर्ण

	/* Issue a command to the FX2 to पढ़ो the IR receiver. */
	LOCK_TAKE(hdw->ctl_lock); करो अणु
		hdw->cmd_buffer[0] = FX2CMD_GET_IR_CODE;
		stat = pvr2_send_request(hdw,
					 hdw->cmd_buffer,1,
					 hdw->cmd_buffer,4);
		dat[0] = hdw->cmd_buffer[0];
		dat[1] = hdw->cmd_buffer[1];
		dat[2] = hdw->cmd_buffer[2];
		dat[3] = hdw->cmd_buffer[3];
	पूर्ण जबतक (0); LOCK_GIVE(hdw->ctl_lock);

	/* Give up अगर that operation failed. */
	अगर (stat != 0) वापस stat;

	/* Mangle the results पूर्णांकo something that looks like the real IR
	   receiver. */
	rdata[2] = 0xc1;
	अगर (dat[0] != 1) अणु
		/* No code received. */
		rdata[0] = 0;
		rdata[1] = 0;
	पूर्ण अन्यथा अणु
		u16 val;
		/* Mash the FX2 firmware-provided IR code पूर्णांकo something
		   that the normal i2c chip-level driver expects. */
		val = dat[1];
		val <<= 8;
		val |= dat[2];
		val >>= 1;
		val &= ~0x0003;
		val |= 0x8000;
		rdata[0] = (val >> 8) & 0xffu;
		rdata[1] = val & 0xffu;
	पूर्ण

	वापस 0;
पूर्ण

/* This is a special entry poपूर्णांक that is entered अगर an I2C operation is
   attempted to a wm8775 chip on model 24xxx hardware.  Autodetect of this
   part करोesn't work, but we know it is really there.  So let's look क्रम
   the स्वतःdetect attempt and just वापस success अगर we see that. */
अटल पूर्णांक i2c_hack_wm8775(काष्ठा pvr2_hdw *hdw,
			   u8 i2c_addr,u8 *wdata,u16 wlen,u8 *rdata,u16 rlen)
अणु
	अगर (!(rlen || wlen)) अणु
		// This is a probe attempt.  Just let it succeed.
		वापस 0;
	पूर्ण
	वापस pvr2_i2c_basic_op(hdw,i2c_addr,wdata,wlen,rdata,rlen);
पूर्ण

/* This is an entry poपूर्णांक deचिन्हित to always fail any attempt to perक्रमm a
   transfer.  We use this to cause certain I2C addresses to not be
   probed. */
अटल पूर्णांक i2c_black_hole(काष्ठा pvr2_hdw *hdw,
			   u8 i2c_addr,u8 *wdata,u16 wlen,u8 *rdata,u16 rlen)
अणु
	वापस -EIO;
पूर्ण

/* This is a special entry poपूर्णांक that is entered अगर an I2C operation is
   attempted to a cx25840 chip on model 24xxx hardware.  This chip can
   someबार wedge itself.  Worse still, when this happens msp3400 can
   falsely detect this part and then the प्रणाली माला_लो hosed up after msp3400
   माला_लो confused and dies.  What we want to करो here is try to keep msp3400
   away and also try to notice अगर the chip is wedged and send a warning to
   the प्रणाली log. */
अटल पूर्णांक i2c_hack_cx25840(काष्ठा pvr2_hdw *hdw,
			    u8 i2c_addr,u8 *wdata,u16 wlen,u8 *rdata,u16 rlen)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक subaddr;
	u8 wbuf[2];
	पूर्णांक state = hdw->i2c_cx25840_hack_state;

	अगर (!(rlen || wlen)) अणु
		// Probe attempt - always just succeed and करोn't bother the
		// hardware (this helps to make the state machine further
		// करोwn somewhat easier).
		वापस 0;
	पूर्ण

	अगर (state == 3) अणु
		वापस pvr2_i2c_basic_op(hdw,i2c_addr,wdata,wlen,rdata,rlen);
	पूर्ण

	/* We're looking क्रम the exact pattern where the revision रेजिस्टर
	   is being पढ़ो.  The cx25840 module will always look at the
	   revision रेजिस्टर first.  Any other pattern of access thereक्रमe
	   has to be a probe attempt from somebody अन्यथा so we'll reject it.
	   Normally we could just let each client just probe the part
	   anyway, but when the cx25840 is wedged, msp3400 will get a false
	   positive and that just screws things up... */

	अगर (wlen == 0) अणु
		चयन (state) अणु
		हाल 1: subaddr = 0x0100; अवरोध;
		हाल 2: subaddr = 0x0101; अवरोध;
		शेष: जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अगर (wlen == 2) अणु
		subaddr = (wdata[0] << 8) | wdata[1];
		चयन (subaddr) अणु
		हाल 0x0100: state = 1; अवरोध;
		हाल 0x0101: state = 2; अवरोध;
		शेष: जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		जाओ fail;
	पूर्ण
	अगर (!rlen) जाओ success;
	state = 0;
	अगर (rlen != 1) जाओ fail;

	/* If we get to here then we have a legitimate पढ़ो क्रम one of the
	   two revision bytes, so pass it through. */
	wbuf[0] = subaddr >> 8;
	wbuf[1] = subaddr;
	ret = pvr2_i2c_basic_op(hdw,i2c_addr,wbuf,2,rdata,rlen);

	अगर ((ret != 0) || (*rdata == 0x04) || (*rdata == 0x0a)) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "***WARNING*** Detected a wedged cx25840 chip; the device will not work.");
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "***WARNING*** Try power cycling the pvrusb2 device.");
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "***WARNING*** Disabling further access to the device to prevent other foul-ups.");
		// This blocks all further communication with the part.
		hdw->i2c_func[0x44] = शून्य;
		pvr2_hdw_render_useless(hdw);
		जाओ fail;
	पूर्ण

	/* Success! */
	pvr2_trace(PVR2_TRACE_CHIPS,"cx25840 appears to be OK.");
	state = 3;

 success:
	hdw->i2c_cx25840_hack_state = state;
	वापस 0;

 fail:
	hdw->i2c_cx25840_hack_state = state;
	वापस -EIO;
पूर्ण

/* This is a very, very limited I2C adapter implementation.  We can only
   support what we actually know will work on the device... */
अटल पूर्णांक pvr2_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			 काष्ठा i2c_msg msgs[],
			 पूर्णांक num)
अणु
	पूर्णांक ret = -ENOTSUPP;
	pvr2_i2c_func funcp = शून्य;
	काष्ठा pvr2_hdw *hdw = (काष्ठा pvr2_hdw *)(i2c_adap->algo_data);

	अगर (!num) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण
	अगर (msgs[0].addr < PVR2_I2C_FUNC_CNT) अणु
		funcp = hdw->i2c_func[msgs[0].addr];
	पूर्ण
	अगर (!funcp) अणु
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	अगर (num == 1) अणु
		अगर (msgs[0].flags & I2C_M_RD) अणु
			/* Simple पढ़ो */
			u16 tcnt,bcnt,offs;
			अगर (!msgs[0].len) अणु
				/* Length == 0 पढ़ो.  This is a probe. */
				अगर (funcp(hdw,msgs[0].addr,शून्य,0,शून्य,0)) अणु
					ret = -EIO;
					जाओ करोne;
				पूर्ण
				ret = 1;
				जाओ करोne;
			पूर्ण
			/* If the पढ़ो is लघु enough we'll करो the whole
			   thing atomically.  Otherwise we have no choice
			   but to अवरोध apart the पढ़ोs. */
			tcnt = msgs[0].len;
			offs = 0;
			जबतक (tcnt) अणु
				bcnt = tcnt;
				अगर (bcnt > माप(hdw->cmd_buffer)-1) अणु
					bcnt = माप(hdw->cmd_buffer)-1;
				पूर्ण
				अगर (funcp(hdw,msgs[0].addr,शून्य,0,
					  msgs[0].buf+offs,bcnt)) अणु
					ret = -EIO;
					जाओ करोne;
				पूर्ण
				offs += bcnt;
				tcnt -= bcnt;
			पूर्ण
			ret = 1;
			जाओ करोne;
		पूर्ण अन्यथा अणु
			/* Simple ग_लिखो */
			ret = 1;
			अगर (funcp(hdw,msgs[0].addr,
				  msgs[0].buf,msgs[0].len,शून्य,0)) अणु
				ret = -EIO;
			पूर्ण
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अगर (num == 2) अणु
		अगर (msgs[0].addr != msgs[1].addr) अणु
			trace_i2c("i2c refusing 2 phase transfer with conflicting target addresses");
			ret = -ENOTSUPP;
			जाओ करोne;
		पूर्ण
		अगर ((!((msgs[0].flags & I2C_M_RD))) &&
		    (msgs[1].flags & I2C_M_RD)) अणु
			u16 tcnt,bcnt,wcnt,offs;
			/* Write followed by atomic पढ़ो.  If the पढ़ो
			   portion is लघु enough we'll करो the whole thing
			   atomically.  Otherwise we have no choice but to
			   अवरोध apart the पढ़ोs. */
			tcnt = msgs[1].len;
			wcnt = msgs[0].len;
			offs = 0;
			जबतक (tcnt || wcnt) अणु
				bcnt = tcnt;
				अगर (bcnt > माप(hdw->cmd_buffer)-1) अणु
					bcnt = माप(hdw->cmd_buffer)-1;
				पूर्ण
				अगर (funcp(hdw,msgs[0].addr,
					  msgs[0].buf,wcnt,
					  msgs[1].buf+offs,bcnt)) अणु
					ret = -EIO;
					जाओ करोne;
				पूर्ण
				offs += bcnt;
				tcnt -= bcnt;
				wcnt = 0;
			पूर्ण
			ret = 2;
			जाओ करोne;
		पूर्ण अन्यथा अणु
			trace_i2c("i2c refusing complex transfer read0=%d read1=%d",
				  (msgs[0].flags & I2C_M_RD),
				  (msgs[1].flags & I2C_M_RD));
		पूर्ण
	पूर्ण अन्यथा अणु
		trace_i2c("i2c refusing %d phase transfer",num);
	पूर्ण

 करोne:
	अगर (pvrusb2_debug & PVR2_TRACE_I2C_TRAF) अणु
		अचिन्हित पूर्णांक idx,offs,cnt;
		क्रम (idx = 0; idx < num; idx++) अणु
			cnt = msgs[idx].len;
			pr_info("pvrusb2 i2c xfer %u/%u: addr=0x%x len=%d %s",
			       idx+1,num,
			       msgs[idx].addr,
			       cnt,
			       (msgs[idx].flags & I2C_M_RD ?
				"read" : "write"));
			अगर ((ret > 0) || !(msgs[idx].flags & I2C_M_RD)) अणु
				अगर (cnt > 8) cnt = 8;
				pr_cont(" [");
				क्रम (offs = 0; offs < cnt; offs++) अणु
					अगर (offs) pr_cont(" ");
					pr_cont("%02x", msgs[idx].buf[offs]);
				पूर्ण
				अगर (offs < cnt) pr_cont(" ...");
				pr_cont("]");
			पूर्ण
			अगर (idx+1 == num) अणु
				pr_cont(" result=%d", ret);
			पूर्ण
			pr_cont("\n");
		पूर्ण
		अगर (!num) अणु
			pr_info("pvrusb2 i2c xfer null transfer result=%d\n",
			       ret);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल u32 pvr2_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_SMBUS_EMUL | I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm pvr2_i2c_algo_ढाँचा = अणु
	.master_xfer   = pvr2_i2c_xfer,
	.functionality = pvr2_i2c_functionality,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter pvr2_i2c_adap_ढाँचा = अणु
	.owner         = THIS_MODULE,
	.class	       = 0,
पूर्ण;


/* Return true अगर device exists at given address */
अटल पूर्णांक करो_i2c_probe(काष्ठा pvr2_hdw *hdw, पूर्णांक addr)
अणु
	काष्ठा i2c_msg msg[1];
	पूर्णांक rc;
	msg[0].addr = 0;
	msg[0].flags = I2C_M_RD;
	msg[0].len = 0;
	msg[0].buf = शून्य;
	msg[0].addr = addr;
	rc = i2c_transfer(&hdw->i2c_adap, msg, ARRAY_SIZE(msg));
	वापस rc == 1;
पूर्ण

अटल व्योम करो_i2c_scan(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक i;
	pr_info("%s: i2c scan beginning\n", hdw->name);
	क्रम (i = 0; i < 128; i++) अणु
		अगर (करो_i2c_probe(hdw, i)) अणु
			pr_info("%s: i2c scan: found device @ 0x%x\n",
			       hdw->name, i);
		पूर्ण
	पूर्ण
	pr_info("%s: i2c scan done.\n", hdw->name);
पूर्ण

अटल व्योम pvr2_i2c_रेजिस्टर_ir(काष्ठा pvr2_hdw *hdw)
अणु
	काष्ठा i2c_board_info info;
	काष्ठा IR_i2c_init_data *init_data = &hdw->ir_init_data;
	अगर (pvr2_disable_ir_video) अणु
		pvr2_trace(PVR2_TRACE_INFO,
			   "Automatic binding of ir_video has been disabled.");
		वापस;
	पूर्ण
	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	चयन (hdw->ir_scheme_active) अणु
	हाल PVR2_IR_SCHEME_24XXX: /* FX2-controlled IR */
	हाल PVR2_IR_SCHEME_29XXX: /* Original 29xxx device */
		init_data->ir_codes              = RC_MAP_HAUPPAUGE;
		init_data->पूर्णांकernal_get_key_func = IR_KBD_GET_KEY_HAUP;
		init_data->type                  = RC_PROTO_BIT_RC5;
		init_data->name                  = hdw->hdw_desc->description;
		init_data->polling_पूर्णांकerval      = 100; /* ms From ir-kbd-i2c */
		/* IR Receiver */
		info.addr          = 0x18;
		info.platक्रमm_data = init_data;
		strscpy(info.type, "ir_video", I2C_NAME_SIZE);
		pvr2_trace(PVR2_TRACE_INFO, "Binding %s to i2c address 0x%02x.",
			   info.type, info.addr);
		i2c_new_client_device(&hdw->i2c_adap, &info);
		अवरोध;
	हाल PVR2_IR_SCHEME_ZILOG:     /* HVR-1950 style */
	हाल PVR2_IR_SCHEME_24XXX_MCE: /* 24xxx MCE device */
		init_data->ir_codes = RC_MAP_HAUPPAUGE;
		init_data->पूर्णांकernal_get_key_func = IR_KBD_GET_KEY_HAUP_XVR;
		init_data->type = RC_PROTO_BIT_RC5 | RC_PROTO_BIT_RC6_MCE |
							RC_PROTO_BIT_RC6_6A_32;
		init_data->name = hdw->hdw_desc->description;
		/* IR Transceiver */
		info.addr = 0x71;
		info.platक्रमm_data = init_data;
		strscpy(info.type, "ir_z8f0811_haup", I2C_NAME_SIZE);
		pvr2_trace(PVR2_TRACE_INFO, "Binding %s to i2c address 0x%02x.",
			   info.type, info.addr);
		i2c_new_client_device(&hdw->i2c_adap, &info);
		अवरोध;
	शेष:
		/* The device either करोesn't support I2C-based IR or we
		   करोn't know (yet) how to operate IR on the device. */
		अवरोध;
	पूर्ण
पूर्ण

व्योम pvr2_i2c_core_init(काष्ठा pvr2_hdw *hdw)
अणु
	अचिन्हित पूर्णांक idx;

	/* The शेष action क्रम all possible I2C addresses is just to करो
	   the transfer normally. */
	क्रम (idx = 0; idx < PVR2_I2C_FUNC_CNT; idx++) अणु
		hdw->i2c_func[idx] = pvr2_i2c_basic_op;
	पूर्ण

	/* However, deal with various special हालs क्रम 24xxx hardware. */
	अगर (ir_mode[hdw->unit_number] == 0) अणु
		pr_info("%s: IR disabled\n", hdw->name);
		hdw->i2c_func[0x18] = i2c_black_hole;
	पूर्ण अन्यथा अगर (ir_mode[hdw->unit_number] == 1) अणु
		अगर (hdw->ir_scheme_active == PVR2_IR_SCHEME_24XXX) अणु
			/* Set up translation so that our IR looks like a
			   29xxx device */
			hdw->i2c_func[0x18] = i2c_24xxx_ir;
		पूर्ण
	पूर्ण
	अगर (hdw->hdw_desc->flag_has_cx25840) अणु
		hdw->i2c_func[0x44] = i2c_hack_cx25840;
	पूर्ण
	अगर (hdw->hdw_desc->flag_has_wm8775) अणु
		hdw->i2c_func[0x1b] = i2c_hack_wm8775;
	पूर्ण

	// Configure the adapter and set up everything अन्यथा related to it.
	hdw->i2c_adap = pvr2_i2c_adap_ढाँचा;
	hdw->i2c_algo = pvr2_i2c_algo_ढाँचा;
	strscpy(hdw->i2c_adap.name, hdw->name, माप(hdw->i2c_adap.name));
	hdw->i2c_adap.dev.parent = &hdw->usb_dev->dev;
	hdw->i2c_adap.algo = &hdw->i2c_algo;
	hdw->i2c_adap.algo_data = hdw;
	hdw->i2c_linked = !0;
	i2c_set_adapdata(&hdw->i2c_adap, &hdw->v4l2_dev);
	i2c_add_adapter(&hdw->i2c_adap);
	अगर (hdw->i2c_func[0x18] == i2c_24xxx_ir) अणु
		/* Probe क्रम a dअगरferent type of IR receiver on this
		   device.  This is really the only way to dअगरferentiate
		   older 24xxx devices from 24xxx variants that include an
		   IR blaster.  If the IR blaster is present, the IR
		   receiver is part of that chip and thus we must disable
		   the emulated IR receiver. */
		अगर (करो_i2c_probe(hdw, 0x71)) अणु
			pvr2_trace(PVR2_TRACE_INFO,
				   "Device has newer IR hardware; disabling unneeded virtual IR device");
			hdw->i2c_func[0x18] = शून्य;
			/* Remember that this is a dअगरferent device... */
			hdw->ir_scheme_active = PVR2_IR_SCHEME_24XXX_MCE;
		पूर्ण
	पूर्ण
	अगर (i2c_scan) करो_i2c_scan(hdw);

	pvr2_i2c_रेजिस्टर_ir(hdw);
पूर्ण

व्योम pvr2_i2c_core_करोne(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (hdw->i2c_linked) अणु
		i2c_del_adapter(&hdw->i2c_adap);
		hdw->i2c_linked = 0;
	पूर्ण
पूर्ण
