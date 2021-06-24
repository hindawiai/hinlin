<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) by Paul Barton-Davis 1998-1999
 *
 * Some portions of this file are taken from work that is
 * copyright (C) by Hannu Savolainen 1993-1996
 */

/*  
 * An ALSA lowlevel driver क्रम Turtle Beach ICS2115 wavetable synth
 *                                             (Maui, Tropez, Tropez Plus)
 *
 * This driver supports the onboard wavetable synthesizer (an ICS2115),
 * including patch, sample and program loading and unloading, conversion
 * of GUS patches during loading, and full user-level access to all
 * WaveFront commands. It tries to provide semi-पूर्णांकelligent patch and
 * sample management as well.
 *
 */

#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/firmware.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/snd_wavefront.h>
#समावेश <sound/initval.h>

अटल पूर्णांक wf_raw = 0; /* we normally check क्रम "raw state" to firmware
			  loading. अगर non-zero, then during driver loading, the
			  state of the board is ignored, and we reset the
			  board and load the firmware anyway.
		       */
		   
अटल पूर्णांक fx_raw = 1; /* अगर this is zero, we'll leave the FX processor in
			  whatever state it is when the driver is loaded.
			  The शेष is to करोwnload the microprogram and
			  associated coefficients to set it up क्रम "default"
			  operation, whatever that means.
		       */

अटल पूर्णांक debug_शेष = 0;  /* you can set this to control debugging
				  during driver loading. it takes any combination
				  of the WF_DEBUG_* flags defined in
				  wavefront.h
			       */

/* XXX this needs to be made firmware and hardware version dependent */

#घोषणा DEFAULT_OSPATH	"wavefront.os"
अटल अक्षर *ospath = DEFAULT_OSPATH; /* the firmware file name */

अटल पूर्णांक रुको_usecs = 150; /* This magic number seems to give pretty optimal
				throughput based on my limited experimentation.
				If you want to play around with it and find a better
				value, be my guest. Remember, the idea is to
				get a number that causes us to just busy रुको
				क्रम as many WaveFront commands as possible, without
				coming up with a number so large that we hog the
				whole CPU.

				Specअगरically, with this number, out of about 134,000
				status रुकोs, only about 250 result in a sleep.
			    */

अटल पूर्णांक sleep_पूर्णांकerval = 100;   /* HZ/sleep_पूर्णांकerval seconds per sleep */
अटल पूर्णांक sleep_tries = 50;       /* number of बार we'll try to sleep */

अटल पूर्णांक reset_समय = 2;        /* hundreths of a second we रुको after a HW
				     reset क्रम the expected पूर्णांकerrupt.
				  */

अटल पूर्णांक ramcheck_समय = 20;    /* समय in seconds to रुको जबतक ROM code
				     checks on-board RAM.
				  */

अटल पूर्णांक osrun_समय = 10;       /* समय in seconds we रुको क्रम the OS to
				     start running.
				  */
module_param(wf_raw, पूर्णांक, 0444);
MODULE_PARM_DESC(wf_raw, "if non-zero, assume that we need to boot the OS");
module_param(fx_raw, पूर्णांक, 0444);
MODULE_PARM_DESC(fx_raw, "if non-zero, assume that the FX process needs help");
module_param(debug_शेष, पूर्णांक, 0444);
MODULE_PARM_DESC(debug_शेष, "debug parameters for card initialization");
module_param(रुको_usecs, पूर्णांक, 0444);
MODULE_PARM_DESC(रुको_usecs, "how long to wait without sleeping, usecs");
module_param(sleep_पूर्णांकerval, पूर्णांक, 0444);
MODULE_PARM_DESC(sleep_पूर्णांकerval, "how long to sleep when waiting for reply");
module_param(sleep_tries, पूर्णांक, 0444);
MODULE_PARM_DESC(sleep_tries, "how many times to try sleeping during a wait");
module_param(ospath, अक्षरp, 0444);
MODULE_PARM_DESC(ospath, "pathname to processed ICS2115 OS firmware");
module_param(reset_समय, पूर्णांक, 0444);
MODULE_PARM_DESC(reset_समय, "how long to wait for a reset to take effect");
module_param(ramcheck_समय, पूर्णांक, 0444);
MODULE_PARM_DESC(ramcheck_समय, "how many seconds to wait for the RAM test");
module_param(osrun_समय, पूर्णांक, 0444);
MODULE_PARM_DESC(osrun_समय, "how many seconds to wait for the ICS2115 OS");

/* अगर WF_DEBUG not defined, no run-समय debugging messages will
   be available via the debug flag setting. Given the current
   beta state of the driver, this will reमुख्य set until a future 
   version.
*/

#घोषणा WF_DEBUG 1

#अगर_घोषित WF_DEBUG

#घोषणा DPRINT(cond, ...) \
       अगर ((dev->debug & (cond)) == (cond)) अणु \
	     snd_prपूर्णांकk (__VA_ARGS__); \
       पूर्ण
#अन्यथा
#घोषणा DPRINT(cond, args...)
#पूर्ण_अगर /* WF_DEBUG */

#घोषणा LOGNAME "WaveFront: "

/* biपंचांगasks क्रम WaveFront status port value */

#घोषणा STAT_RINTR_ENABLED	0x01
#घोषणा STAT_CAN_READ		0x02
#घोषणा STAT_INTR_READ		0x04
#घोषणा STAT_WINTR_ENABLED	0x10
#घोषणा STAT_CAN_WRITE		0x20
#घोषणा STAT_INTR_WRITE		0x40

अटल पूर्णांक wavefront_delete_sample (snd_wavefront_t *, पूर्णांक sampnum);
अटल पूर्णांक wavefront_find_मुक्त_sample (snd_wavefront_t *);

काष्ठा wavefront_command अणु
	पूर्णांक cmd;
	अक्षर *action;
	अचिन्हित पूर्णांक पढ़ो_cnt;
	अचिन्हित पूर्णांक ग_लिखो_cnt;
	पूर्णांक need_ack;
पूर्ण;

अटल काष्ठा अणु
	पूर्णांक त्रुटि_सं;
	स्थिर अक्षर *errstr;
पूर्ण wavefront_errors[] = अणु
	अणु 0x01, "Bad sample number" पूर्ण,
	अणु 0x02, "Out of sample memory" पूर्ण,
	अणु 0x03, "Bad patch number" पूर्ण,
	अणु 0x04, "Error in number of voices" पूर्ण,
	अणु 0x06, "Sample load already in progress" पूर्ण,
	अणु 0x0B, "No sample load request pending" पूर्ण,
	अणु 0x0E, "Bad MIDI channel number" पूर्ण,
	अणु 0x10, "Download Record Error" पूर्ण,
	अणु 0x80, "Success" पूर्ण,
	अणु 0x0 पूर्ण
पूर्ण;

#घोषणा NEEDS_ACK 1

अटल काष्ठा wavefront_command wavefront_commands[] = अणु
	अणु WFC_SET_SYNTHVOL, "set synthesizer volume", 0, 1, NEEDS_ACK पूर्ण,
	अणु WFC_GET_SYNTHVOL, "get synthesizer volume", 1, 0, 0पूर्ण,
	अणु WFC_SET_NVOICES, "set number of voices", 0, 1, NEEDS_ACK पूर्ण,
	अणु WFC_GET_NVOICES, "get number of voices", 1, 0, 0 पूर्ण,
	अणु WFC_SET_TUNING, "set synthesizer tuning", 0, 2, NEEDS_ACK पूर्ण,
	अणु WFC_GET_TUNING, "get synthesizer tuning", 2, 0, 0 पूर्ण,
	अणु WFC_DISABLE_CHANNEL, "disable synth channel", 0, 1, NEEDS_ACK पूर्ण,
	अणु WFC_ENABLE_CHANNEL, "enable synth channel", 0, 1, NEEDS_ACK पूर्ण,
	अणु WFC_GET_CHANNEL_STATUS, "get synth channel status", 3, 0, 0 पूर्ण,
	अणु WFC_MISYNTH_OFF, "disable midi-in to synth", 0, 0, NEEDS_ACK पूर्ण,
	अणु WFC_MISYNTH_ON, "enable midi-in to synth", 0, 0, NEEDS_ACK पूर्ण,
	अणु WFC_VMIDI_ON, "enable virtual midi mode", 0, 0, NEEDS_ACK पूर्ण,
	अणु WFC_VMIDI_OFF, "disable virtual midi mode", 0, 0, NEEDS_ACK पूर्ण,
	अणु WFC_MIDI_STATUS, "report midi status", 1, 0, 0 पूर्ण,
	अणु WFC_FIRMWARE_VERSION, "report firmware version", 2, 0, 0 पूर्ण,
	अणु WFC_HARDWARE_VERSION, "report hardware version", 2, 0, 0 पूर्ण,
	अणु WFC_GET_NSAMPLES, "report number of samples", 2, 0, 0 पूर्ण,
	अणु WFC_INSTOUT_LEVELS, "report instantaneous output levels", 7, 0, 0 पूर्ण,
	अणु WFC_PEAKOUT_LEVELS, "report peak output levels", 7, 0, 0 पूर्ण,
	अणु WFC_DOWNLOAD_SAMPLE, "download sample",
	  0, WF_SAMPLE_BYTES, NEEDS_ACK पूर्ण,
	अणु WFC_DOWNLOAD_BLOCK, "download block", 0, 0, NEEDS_ACKपूर्ण,
	अणु WFC_DOWNLOAD_SAMPLE_HEADER, "download sample header",
	  0, WF_SAMPLE_HDR_BYTES, NEEDS_ACK पूर्ण,
	अणु WFC_UPLOAD_SAMPLE_HEADER, "upload sample header", 13, 2, 0 पूर्ण,

	/* This command requires a variable number of bytes to be written.
	   There is a hack in snd_wavefront_cmd() to support this. The actual
	   count is passed in as the पढ़ो buffer ptr, cast appropriately.
	   Ugh.
	*/

	अणु WFC_DOWNLOAD_MULTISAMPLE, "download multisample", 0, 0, NEEDS_ACK पूर्ण,

	/* This one is a hack as well. We just पढ़ो the first byte of the
	   response, करोn't fetch an ACK, and leave the rest to the 
	   calling function. Ugly, ugly, ugly.
	*/

	अणु WFC_UPLOAD_MULTISAMPLE, "upload multisample", 2, 1, 0 पूर्ण,
	अणु WFC_DOWNLOAD_SAMPLE_ALIAS, "download sample alias",
	  0, WF_ALIAS_BYTES, NEEDS_ACK पूर्ण,
	अणु WFC_UPLOAD_SAMPLE_ALIAS, "upload sample alias", WF_ALIAS_BYTES, 2, 0पूर्ण,
	अणु WFC_DELETE_SAMPLE, "delete sample", 0, 2, NEEDS_ACK पूर्ण,
	अणु WFC_IDENTIFY_SAMPLE_TYPE, "identify sample type", 5, 2, 0 पूर्ण,
	अणु WFC_UPLOAD_SAMPLE_PARAMS, "upload sample parameters" पूर्ण,
	अणु WFC_REPORT_FREE_MEMORY, "report free memory", 4, 0, 0 पूर्ण,
	अणु WFC_DOWNLOAD_PATCH, "download patch", 0, 134, NEEDS_ACK पूर्ण,
	अणु WFC_UPLOAD_PATCH, "upload patch", 132, 2, 0 पूर्ण,
	अणु WFC_DOWNLOAD_PROGRAM, "download program", 0, 33, NEEDS_ACK पूर्ण,
	अणु WFC_UPLOAD_PROGRAM, "upload program", 32, 1, 0 पूर्ण,
	अणु WFC_DOWNLOAD_EDRUM_PROGRAM, "download enhanced drum program", 0, 9,
	  NEEDS_ACKपूर्ण,
	अणु WFC_UPLOAD_EDRUM_PROGRAM, "upload enhanced drum program", 8, 1, 0पूर्ण,
	अणु WFC_SET_EDRUM_CHANNEL, "set enhanced drum program channel",
	  0, 1, NEEDS_ACK पूर्ण,
	अणु WFC_DISABLE_DRUM_PROGRAM, "disable drum program", 0, 1, NEEDS_ACK पूर्ण,
	अणु WFC_REPORT_CHANNEL_PROGRAMS, "report channel program numbers",
	  32, 0, 0 पूर्ण,
	अणु WFC_NOOP, "the no-op command", 0, 0, NEEDS_ACK पूर्ण,
	अणु 0x00 पूर्ण
पूर्ण;

अटल स्थिर अक्षर *
wavefront_errorstr (पूर्णांक errnum)

अणु
	पूर्णांक i;

	क्रम (i = 0; wavefront_errors[i].errstr; i++) अणु
		अगर (wavefront_errors[i].त्रुटि_सं == errnum) अणु
			वापस wavefront_errors[i].errstr;
		पूर्ण
	पूर्ण

	वापस "Unknown WaveFront error";
पूर्ण

अटल काष्ठा wavefront_command *
wavefront_get_command (पूर्णांक cmd) 

अणु
	पूर्णांक i;

	क्रम (i = 0; wavefront_commands[i].cmd != 0; i++) अणु
		अगर (cmd == wavefront_commands[i].cmd) अणु
			वापस &wavefront_commands[i];
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक
wavefront_status (snd_wavefront_t *dev) 

अणु
	वापस inb (dev->status_port);
पूर्ण

अटल पूर्णांक
wavefront_sleep (पूर्णांक limit)

अणु
	schedule_समयout_पूर्णांकerruptible(limit);

	वापस संकेत_pending(current);
पूर्ण

अटल पूर्णांक
wavefront_रुको (snd_wavefront_t *dev, पूर्णांक mask)

अणु
	पूर्णांक             i;

	/* Spin क्रम a लघु period of समय, because >99% of all
	   requests to the WaveFront can be serviced अंतरभूत like this.
	*/

	क्रम (i = 0; i < रुको_usecs; i += 5) अणु
		अगर (wavefront_status (dev) & mask) अणु
			वापस 1;
		पूर्ण
		udelay(5);
	पूर्ण

	क्रम (i = 0; i < sleep_tries; i++) अणु

		अगर (wavefront_status (dev) & mask) अणु
			वापस 1;
		पूर्ण

		अगर (wavefront_sleep (HZ/sleep_पूर्णांकerval)) अणु
			वापस (0);
		पूर्ण
	पूर्ण

	वापस (0);
पूर्ण

अटल पूर्णांक
wavefront_पढ़ो (snd_wavefront_t *dev)

अणु
	अगर (wavefront_रुको (dev, STAT_CAN_READ))
		वापस inb (dev->data_port);

	DPRINT (WF_DEBUG_DATA, "read timeout.\n");

	वापस -1;
पूर्ण

अटल पूर्णांक
wavefront_ग_लिखो (snd_wavefront_t *dev, अचिन्हित अक्षर data)

अणु
	अगर (wavefront_रुको (dev, STAT_CAN_WRITE)) अणु
		outb (data, dev->data_port);
		वापस 0;
	पूर्ण

	DPRINT (WF_DEBUG_DATA, "write timeout.\n");

	वापस -1;
पूर्ण

पूर्णांक
snd_wavefront_cmd (snd_wavefront_t *dev, 
		   पूर्णांक cmd, अचिन्हित अक्षर *rbuf, अचिन्हित अक्षर *wbuf)

अणु
	पूर्णांक ack;
	अचिन्हित पूर्णांक i;
	पूर्णांक c;
	काष्ठा wavefront_command *wfcmd;

	अगर ((wfcmd = wavefront_get_command (cmd)) == शून्य) अणु
		snd_prपूर्णांकk ("command 0x%x not supported.\n",
			cmd);
		वापस 1;
	पूर्ण

	/* Hack to handle the one variable-size ग_लिखो command. See
	   wavefront_send_multisample() क्रम the other half of this
	   gross and ugly strategy.
	*/

	अगर (cmd == WFC_DOWNLOAD_MULTISAMPLE) अणु
		wfcmd->ग_लिखो_cnt = (अचिन्हित दीर्घ) rbuf;
		rbuf = शून्य;
	पूर्ण

	DPRINT (WF_DEBUG_CMD, "0x%x [%s] (%d,%d,%d)\n",
			       cmd, wfcmd->action, wfcmd->पढ़ो_cnt,
			       wfcmd->ग_लिखो_cnt, wfcmd->need_ack);
    
	अगर (wavefront_ग_लिखो (dev, cmd)) अणु 
		DPRINT ((WF_DEBUG_IO|WF_DEBUG_CMD), "cannot request "
						     "0x%x [%s].\n",
						     cmd, wfcmd->action);
		वापस 1;
	पूर्ण 

	अगर (wfcmd->ग_लिखो_cnt > 0) अणु
		DPRINT (WF_DEBUG_DATA, "writing %d bytes "
					"for 0x%x\n",
					wfcmd->ग_लिखो_cnt, cmd);

		क्रम (i = 0; i < wfcmd->ग_लिखो_cnt; i++) अणु
			अगर (wavefront_ग_लिखो (dev, wbuf[i])) अणु
				DPRINT (WF_DEBUG_IO, "bad write for byte "
						      "%d of 0x%x [%s].\n",
						      i, cmd, wfcmd->action);
				वापस 1;
			पूर्ण

			DPRINT (WF_DEBUG_DATA, "write[%d] = 0x%x\n",
						i, wbuf[i]);
		पूर्ण
	पूर्ण

	अगर (wfcmd->पढ़ो_cnt > 0) अणु
		DPRINT (WF_DEBUG_DATA, "reading %d ints "
					"for 0x%x\n",
					wfcmd->पढ़ो_cnt, cmd);

		क्रम (i = 0; i < wfcmd->पढ़ो_cnt; i++) अणु

			अगर ((c = wavefront_पढ़ो (dev)) == -1) अणु
				DPRINT (WF_DEBUG_IO, "bad read for byte "
						      "%d of 0x%x [%s].\n",
						      i, cmd, wfcmd->action);
				वापस 1;
			पूर्ण

			/* Now handle errors. Lots of special हालs here */
	    
			अगर (c == 0xff) अणु 
				अगर ((c = wavefront_पढ़ो (dev)) == -1) अणु
					DPRINT (WF_DEBUG_IO, "bad read for "
							      "error byte at "
							      "read byte %d "
							      "of 0x%x [%s].\n",
							      i, cmd,
							      wfcmd->action);
					वापस 1;
				पूर्ण

				/* Can you believe this madness ? */

				अगर (c == 1 &&
				    wfcmd->cmd == WFC_IDENTIFY_SAMPLE_TYPE) अणु
					rbuf[0] = WF_ST_EMPTY;
					वापस (0);

				पूर्ण अन्यथा अगर (c == 3 &&
					   wfcmd->cmd == WFC_UPLOAD_PATCH) अणु

					वापस 3;

				पूर्ण अन्यथा अगर (c == 1 &&
					   wfcmd->cmd == WFC_UPLOAD_PROGRAM) अणु

					वापस 1;

				पूर्ण अन्यथा अणु

					DPRINT (WF_DEBUG_IO, "error %d (%s) "
							      "during "
							      "read for byte "
							      "%d of 0x%x "
							      "[%s].\n",
							      c,
							      wavefront_errorstr (c),
							      i, cmd,
							      wfcmd->action);
					वापस 1;

				पूर्ण
		
		पूर्ण अन्यथा अणु
				rbuf[i] = c;
			पूर्ण
			
			DPRINT (WF_DEBUG_DATA, "read[%d] = 0x%x\n",i, rbuf[i]);
		पूर्ण
	पूर्ण
	
	अगर ((wfcmd->पढ़ो_cnt == 0 && wfcmd->ग_लिखो_cnt == 0) || wfcmd->need_ack) अणु

		DPRINT (WF_DEBUG_CMD, "reading ACK for 0x%x\n", cmd);

		/* Some commands need an ACK, but वापस zero instead
		   of the standard value.
		*/
	    
		अगर ((ack = wavefront_पढ़ो (dev)) == 0) अणु
			ack = WF_ACK;
		पूर्ण
	
		अगर (ack != WF_ACK) अणु
			अगर (ack == -1) अणु
				DPRINT (WF_DEBUG_IO, "cannot read ack for "
						      "0x%x [%s].\n",
						      cmd, wfcmd->action);
				वापस 1;
		
			पूर्ण अन्यथा अणु
				पूर्णांक err = -1; /* something unknown */

				अगर (ack == 0xff) अणु /* explicit error */
		    
					अगर ((err = wavefront_पढ़ो (dev)) == -1) अणु
						DPRINT (WF_DEBUG_DATA,
							"cannot read err "
							"for 0x%x [%s].\n",
							cmd, wfcmd->action);
					पूर्ण
				पूर्ण
				
				DPRINT (WF_DEBUG_IO, "0x%x [%s] "
					"failed (0x%x, 0x%x, %s)\n",
					cmd, wfcmd->action, ack, err,
					wavefront_errorstr (err));
				
				वापस -err;
			पूर्ण
		पूर्ण
		
		DPRINT (WF_DEBUG_DATA, "ack received "
					"for 0x%x [%s]\n",
					cmd, wfcmd->action);
	पूर्ण अन्यथा अणु

		DPRINT (WF_DEBUG_CMD, "0x%x [%s] does not need "
				       "ACK (%d,%d,%d)\n",
				       cmd, wfcmd->action, wfcmd->पढ़ो_cnt,
				       wfcmd->ग_लिखो_cnt, wfcmd->need_ack);
	पूर्ण

	वापस 0;
	
पूर्ण

/***********************************************************************
WaveFront data munging   

Things here are weird. All data written to the board cannot 
have its most signअगरicant bit set. Any data item with values 
potentially > 0x7F (127) must be split across multiple bytes.

Someबार, we need to munge numeric values that are represented on
the x86 side as 8-32 bit values. Someबार, we need to munge data
that is represented on the x86 side as an array of bytes. The most
efficient approach to handling both हालs seems to be to use 2
dअगरferent functions क्रम munging and 2 क्रम de-munging. This aव्योमs
weird casting and worrying about bit-level offsets.

**********************************************************************/

अटल अचिन्हित अक्षर *
munge_पूर्णांक32 (अचिन्हित पूर्णांक src,
	     अचिन्हित अक्षर *dst,
	     अचिन्हित पूर्णांक dst_size)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dst_size; i++) अणु
		*dst = src & 0x7F;  /* Mask high bit of LSB */
		src = src >> 7;     /* Rotate Right 7 bits  */
	                            /* Note: we leave the upper bits in place */ 

		dst++;
	पूर्ण
	वापस dst;
पूर्ण;

अटल पूर्णांक 
demunge_पूर्णांक32 (अचिन्हित अक्षर* src, पूर्णांक src_size)

अणु
	पूर्णांक i;
 	पूर्णांक outval = 0;
	
 	क्रम (i = src_size - 1; i >= 0; i--) अणु
		outval=(outval<<7)+src[i];
	पूर्ण

	वापस outval;
पूर्ण;

अटल 
अचिन्हित अक्षर *
munge_buf (अचिन्हित अक्षर *src, अचिन्हित अक्षर *dst, अचिन्हित पूर्णांक dst_size)

अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक last = dst_size / 2;

	क्रम (i = 0; i < last; i++) अणु
		*dst++ = src[i] & 0x7f;
		*dst++ = src[i] >> 7;
	पूर्ण
	वापस dst;
पूर्ण

अटल 
अचिन्हित अक्षर *
demunge_buf (अचिन्हित अक्षर *src, अचिन्हित अक्षर *dst, अचिन्हित पूर्णांक src_bytes)

अणु
	पूर्णांक i;
	अचिन्हित अक्षर *end = src + src_bytes;
    
	end = src + src_bytes;

	/* NOTE: src and dst *CAN* poपूर्णांक to the same address */

	क्रम (i = 0; src != end; i++) अणु
		dst[i] = *src++;
		dst[i] |= (*src++)<<7;
	पूर्ण

	वापस dst;
पूर्ण

/***********************************************************************
WaveFront: sample, patch and program management.
***********************************************************************/

अटल पूर्णांक
wavefront_delete_sample (snd_wavefront_t *dev, पूर्णांक sample_num)

अणु
	अचिन्हित अक्षर wbuf[2];
	पूर्णांक x;

	wbuf[0] = sample_num & 0x7f;
	wbuf[1] = sample_num >> 7;

	अगर ((x = snd_wavefront_cmd (dev, WFC_DELETE_SAMPLE, शून्य, wbuf)) == 0) अणु
		dev->sample_status[sample_num] = WF_ST_EMPTY;
	पूर्ण

	वापस x;
पूर्ण

अटल पूर्णांक
wavefront_get_sample_status (snd_wavefront_t *dev, पूर्णांक assume_rom)

अणु
	पूर्णांक i;
	अचिन्हित अक्षर rbuf[32], wbuf[32];
	अचिन्हित पूर्णांक    sc_real, sc_alias, sc_multi;

	/* check sample status */
    
	अगर (snd_wavefront_cmd (dev, WFC_GET_NSAMPLES, rbuf, wbuf)) अणु
		snd_prपूर्णांकk ("cannot request sample count.\n");
		वापस -1;
	पूर्ण 
    
	sc_real = sc_alias = sc_multi = dev->samples_used = 0;
    
	क्रम (i = 0; i < WF_MAX_SAMPLE; i++) अणु
	
		wbuf[0] = i & 0x7f;
		wbuf[1] = i >> 7;

		अगर (snd_wavefront_cmd (dev, WFC_IDENTIFY_SAMPLE_TYPE, rbuf, wbuf)) अणु
			snd_prपूर्णांकk(KERN_WARNING "cannot identify sample "
				   "type of slot %d\n", i);
			dev->sample_status[i] = WF_ST_EMPTY;
			जारी;
		पूर्ण

		dev->sample_status[i] = (WF_SLOT_FILLED|rbuf[0]);

		अगर (assume_rom) अणु
			dev->sample_status[i] |= WF_SLOT_ROM;
		पूर्ण

		चयन (rbuf[0] & WF_ST_MASK) अणु
		हाल WF_ST_SAMPLE:
			sc_real++;
			अवरोध;
		हाल WF_ST_MULTISAMPLE:
			sc_multi++;
			अवरोध;
		हाल WF_ST_ALIAS:
			sc_alias++;
			अवरोध;
		हाल WF_ST_EMPTY:
			अवरोध;

		शेष:
			snd_prपूर्णांकk ("unknown sample type for "
				    "slot %d (0x%x)\n", 
				    i, rbuf[0]);
		पूर्ण

		अगर (rbuf[0] != WF_ST_EMPTY) अणु
			dev->samples_used++;
		पूर्ण 
	पूर्ण

	snd_prपूर्णांकk ("%d samples used (%d real, %d aliases, %d multi), "
		    "%d empty\n", dev->samples_used, sc_real, sc_alias, sc_multi,
		    WF_MAX_SAMPLE - dev->samples_used);


	वापस (0);

पूर्ण

अटल पूर्णांक
wavefront_get_patch_status (snd_wavefront_t *dev)

अणु
	अचिन्हित अक्षर patchbuf[WF_PATCH_BYTES];
	अचिन्हित अक्षर patchnum[2];
	wavefront_patch *p;
	पूर्णांक i, x, cnt, cnt2;

	क्रम (i = 0; i < WF_MAX_PATCH; i++) अणु
		patchnum[0] = i & 0x7f;
		patchnum[1] = i >> 7;

		अगर ((x = snd_wavefront_cmd (dev, WFC_UPLOAD_PATCH, patchbuf,
					patchnum)) == 0) अणु

			dev->patch_status[i] |= WF_SLOT_FILLED;
			p = (wavefront_patch *) patchbuf;
			dev->sample_status
				[p->sample_number|(p->sample_msb<<7)] |=
				WF_SLOT_USED;
	    
		पूर्ण अन्यथा अगर (x == 3) अणु /* Bad patch number */
			dev->patch_status[i] = 0;
		पूर्ण अन्यथा अणु
			snd_prपूर्णांकk ("upload patch "
				    "error 0x%x\n", x);
			dev->patch_status[i] = 0;
			वापस 1;
		पूर्ण
	पूर्ण

	/* program status has alपढ़ोy filled in slot_used bits */

	क्रम (i = 0, cnt = 0, cnt2 = 0; i < WF_MAX_PATCH; i++) अणु
		अगर (dev->patch_status[i] & WF_SLOT_FILLED) अणु
			cnt++;
		पूर्ण
		अगर (dev->patch_status[i] & WF_SLOT_USED) अणु
			cnt2++;
		पूर्ण
	
	पूर्ण
	snd_prपूर्णांकk ("%d patch slots filled, %d in use\n", cnt, cnt2);

	वापस (0);
पूर्ण

अटल पूर्णांक
wavefront_get_program_status (snd_wavefront_t *dev)

अणु
	अचिन्हित अक्षर progbuf[WF_PROGRAM_BYTES];
	wavefront_program prog;
	अचिन्हित अक्षर prognum;
	पूर्णांक i, x, l, cnt;

	क्रम (i = 0; i < WF_MAX_PROGRAM; i++) अणु
		prognum = i;

		अगर ((x = snd_wavefront_cmd (dev, WFC_UPLOAD_PROGRAM, progbuf,
					&prognum)) == 0) अणु

			dev->prog_status[i] |= WF_SLOT_USED;

			demunge_buf (progbuf, (अचिन्हित अक्षर *) &prog,
				     WF_PROGRAM_BYTES);

			क्रम (l = 0; l < WF_NUM_LAYERS; l++) अणु
				अगर (prog.layer[l].mute) अणु
					dev->patch_status
						[prog.layer[l].patch_number] |=
						WF_SLOT_USED;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (x == 1) अणु /* Bad program number */
			dev->prog_status[i] = 0;
		पूर्ण अन्यथा अणु
			snd_prपूर्णांकk ("upload program "
				    "error 0x%x\n", x);
			dev->prog_status[i] = 0;
		पूर्ण
	पूर्ण

	क्रम (i = 0, cnt = 0; i < WF_MAX_PROGRAM; i++) अणु
		अगर (dev->prog_status[i]) अणु
			cnt++;
		पूर्ण
	पूर्ण

	snd_prपूर्णांकk ("%d programs slots in use\n", cnt);

	वापस (0);
पूर्ण

अटल पूर्णांक
wavefront_send_patch (snd_wavefront_t *dev, wavefront_patch_info *header)

अणु
	अचिन्हित अक्षर buf[WF_PATCH_BYTES+2];
	अचिन्हित अक्षर *bptr;

	DPRINT (WF_DEBUG_LOAD_PATCH, "downloading patch %d\n",
				      header->number);

	अगर (header->number >= ARRAY_SIZE(dev->patch_status))
		वापस -EINVAL;

	dev->patch_status[header->number] |= WF_SLOT_FILLED;

	bptr = munge_पूर्णांक32 (header->number, buf, 2);
	munge_buf ((अचिन्हित अक्षर *)&header->hdr.p, bptr, WF_PATCH_BYTES);
    
	अगर (snd_wavefront_cmd (dev, WFC_DOWNLOAD_PATCH, शून्य, buf)) अणु
		snd_prपूर्णांकk ("download patch failed\n");
		वापस -EIO;
	पूर्ण

	वापस (0);
पूर्ण

अटल पूर्णांक
wavefront_send_program (snd_wavefront_t *dev, wavefront_patch_info *header)

अणु
	अचिन्हित अक्षर buf[WF_PROGRAM_BYTES+1];
	पूर्णांक i;

	DPRINT (WF_DEBUG_LOAD_PATCH, "downloading program %d\n",
		header->number);

	अगर (header->number >= ARRAY_SIZE(dev->prog_status))
		वापस -EINVAL;

	dev->prog_status[header->number] = WF_SLOT_USED;

	/* XXX need to zero existing SLOT_USED bit क्रम program_status[i]
	   where `i' is the program that's being (potentially) overwritten.
	*/
    
	क्रम (i = 0; i < WF_NUM_LAYERS; i++) अणु
		अगर (header->hdr.pr.layer[i].mute) अणु
			dev->patch_status[header->hdr.pr.layer[i].patch_number] |=
				WF_SLOT_USED;

			/* XXX need to mark SLOT_USED क्रम sample used by
			   patch_number, but this means we have to load it. Ick.
			*/
		पूर्ण
	पूर्ण

	buf[0] = header->number;
	munge_buf ((अचिन्हित अक्षर *)&header->hdr.pr, &buf[1], WF_PROGRAM_BYTES);
    
	अगर (snd_wavefront_cmd (dev, WFC_DOWNLOAD_PROGRAM, शून्य, buf)) अणु
		snd_prपूर्णांकk ("download patch failed\n");	
		वापस -EIO;
	पूर्ण

	वापस (0);
पूर्ण

अटल पूर्णांक
wavefront_मुक्तmem (snd_wavefront_t *dev)

अणु
	अक्षर rbuf[8];

	अगर (snd_wavefront_cmd (dev, WFC_REPORT_FREE_MEMORY, rbuf, शून्य)) अणु
		snd_prपूर्णांकk ("can't get memory stats.\n");
		वापस -1;
	पूर्ण अन्यथा अणु
		वापस demunge_पूर्णांक32 (rbuf, 4);
	पूर्ण
पूर्ण

अटल पूर्णांक
wavefront_send_sample (snd_wavefront_t *dev, 
		       wavefront_patch_info *header,
		       u16 __user *dataptr,
		       पूर्णांक data_is_अचिन्हित)

अणु
	/* samples are करोwnloaded via a 16-bit wide i/o port
	   (you could think of it as 2 adjacent 8-bit wide ports
	   but its less efficient that way). thereक्रमe, all
	   the blocksizes and so क्रमth listed in the करोcumentation,
	   and used conventionally to refer to sample sizes,
	   which are given in 8-bit units (bytes), need to be
	   भागided by 2.
        */

	u16 sample_लघु = 0;
	u32 length;
	u16 __user *data_end = शून्य;
	अचिन्हित पूर्णांक i;
	स्थिर अचिन्हित पूर्णांक max_blksize = 4096/2;
	अचिन्हित पूर्णांक written;
	अचिन्हित पूर्णांक blocksize;
	पूर्णांक dma_ack;
	पूर्णांक blocknum;
	अचिन्हित अक्षर sample_hdr[WF_SAMPLE_HDR_BYTES];
	अचिन्हित अक्षर *shptr;
	पूर्णांक skip = 0;
	पूर्णांक initial_skip = 0;

	DPRINT (WF_DEBUG_LOAD_PATCH, "sample %sdownload for slot %d, "
				      "type %d, %d bytes from 0x%lx\n",
				      header->size ? "" : "header ", 
				      header->number, header->subkey,
				      header->size,
				      (अचिन्हित दीर्घ) header->dataptr);

	अगर (header->number == WAVEFRONT_FIND_FREE_SAMPLE_SLOT) अणु
		पूर्णांक x;

		अगर ((x = wavefront_find_मुक्त_sample (dev)) < 0) अणु
			वापस -ENOMEM;
		पूर्ण
		snd_prपूर्णांकk ("unspecified sample => %d\n", x);
		header->number = x;
	पूर्ण

	अगर (header->number >= WF_MAX_SAMPLE)
		वापस -EINVAL;

	अगर (header->size) अणु

		/* XXX it's a debatable poपूर्णांक whether or not RDONLY semantics
		   on the ROM samples should cover just the sample data or
		   the sample header. For now, it only covers the sample data,
		   so anyone is मुक्त at all बार to reग_लिखो sample headers.

		   My reason क्रम this is that we have the sample headers
		   available in the WFB file क्रम General MIDI, and so these
		   can always be reset अगर needed. The sample data, however,
		   cannot be recovered without a complete reset and firmware
		   reload of the ICS2115, which is a very expensive operation.

		   So, करोing things this way allows us to honor the notion of
		   "RESETSAMPLES" reasonably cheaply. Note however, that this
		   is करोne purely at user level: there is no WFB parser in
		   this driver, and so a complete reset (back to General MIDI,
		   or theoretically some other configuration) is the
		   responsibility of the user level library. 

		   To try to करो this in the kernel would be a little
		   crazy: we'd need 158K of kernel space just to hold
		   a copy of the patch/program/sample header data.
		*/

		अगर (dev->rom_samples_rकरोnly) अणु
			अगर (dev->sample_status[header->number] & WF_SLOT_ROM) अणु
				snd_prपूर्णांकk ("sample slot %d "
					    "write protected\n",
					    header->number);
				वापस -EACCES;
			पूर्ण
		पूर्ण

		wavefront_delete_sample (dev, header->number);
	पूर्ण

	अगर (header->size) अणु
		dev->मुक्तmem = wavefront_मुक्तmem (dev);

		अगर (dev->मुक्तmem < (पूर्णांक)header->size) अणु
			snd_prपूर्णांकk ("insufficient memory to "
				    "load %d byte sample.\n",
				    header->size);
			वापस -ENOMEM;
		पूर्ण
	
	पूर्ण

	skip = WF_GET_CHANNEL(&header->hdr.s);

	अगर (skip > 0 && header->hdr.s.SampleResolution != LINEAR_16BIT) अणु
		snd_prपूर्णांकk ("channel selection only "
			    "possible on 16-bit samples");
		वापस -EINVAL;
	पूर्ण

	चयन (skip) अणु
	हाल 0:
		initial_skip = 0;
		skip = 1;
		अवरोध;
	हाल 1:
		initial_skip = 0;
		skip = 2;
		अवरोध;
	हाल 2:
		initial_skip = 1;
		skip = 2;
		अवरोध;
	हाल 3:
		initial_skip = 2;
		skip = 3;
		अवरोध;
	हाल 4:
		initial_skip = 3;
		skip = 4;
		अवरोध;
	हाल 5:
		initial_skip = 4;
		skip = 5;
		अवरोध;
	हाल 6:
		initial_skip = 5;
		skip = 6;
		अवरोध;
	पूर्ण

	DPRINT (WF_DEBUG_LOAD_PATCH, "channel selection: %d => "
				      "initial skip = %d, skip = %d\n",
				      WF_GET_CHANNEL (&header->hdr.s),
				      initial_skip, skip);
    
	/* Be safe, and zero the "Unused" bits ... */

	WF_SET_CHANNEL(&header->hdr.s, 0);

	/* adjust size क्रम 16 bit samples by भागiding by two.  We always
	   send 16 bits per ग_लिखो, even क्रम 8 bit samples, so the length
	   is always half the size of the sample data in bytes.
	*/

	length = header->size / 2;

	/* the data we're sent has not been munged, and in fact, the
	   header we have to send isn't just a munged copy either.
	   so, build the sample header right here.
	*/

	shptr = &sample_hdr[0];

	shptr = munge_पूर्णांक32 (header->number, shptr, 2);

	अगर (header->size) अणु
		shptr = munge_पूर्णांक32 (length, shptr, 4);
	पूर्ण

	/* Yes, a 4 byte result करोesn't contain all of the offset bits,
	   but the offset only uses 24 bits.
	*/

	shptr = munge_पूर्णांक32 (*((u32 *) &header->hdr.s.sampleStartOffset),
			     shptr, 4);
	shptr = munge_पूर्णांक32 (*((u32 *) &header->hdr.s.loopStartOffset),
			     shptr, 4);
	shptr = munge_पूर्णांक32 (*((u32 *) &header->hdr.s.loopEndOffset),
			     shptr, 4);
	shptr = munge_पूर्णांक32 (*((u32 *) &header->hdr.s.sampleEndOffset),
			     shptr, 4);
	
	/* This one is truly weird. What kind of weirकरो decided that in
	   a प्रणाली करोminated by 16 and 32 bit पूर्णांकegers, they would use
	   a just 12 bits ?
	*/
	
	shptr = munge_पूर्णांक32 (header->hdr.s.FrequencyBias, shptr, 3);
	
	/* Why is this nybblअगरied, when the MSB is *always* zero ? 
	   Anyway, we can't take address of bitfield, so make a
	   good-faith guess at where it starts.
	*/
	
	shptr = munge_पूर्णांक32 (*(&header->hdr.s.FrequencyBias+1),
			     shptr, 2);

	अगर (snd_wavefront_cmd (dev, 
			   header->size ?
			   WFC_DOWNLOAD_SAMPLE : WFC_DOWNLOAD_SAMPLE_HEADER,
			   शून्य, sample_hdr)) अणु
		snd_prपूर्णांकk ("sample %sdownload refused.\n",
			    header->size ? "" : "header ");
		वापस -EIO;
	पूर्ण

	अगर (header->size == 0) अणु
		जाओ sent; /* Sorry. Just had to have one somewhere */
	पूर्ण
    
	data_end = dataptr + length;

	/* Do any initial skip over an unused channel's data */

	dataptr += initial_skip;
    
	क्रम (written = 0, blocknum = 0;
	     written < length; written += max_blksize, blocknum++) अणु
	
		अगर ((length - written) > max_blksize) अणु
			blocksize = max_blksize;
		पूर्ण अन्यथा अणु
			/* round to nearest 16-byte value */
			blocksize = ALIGN(length - written, 8);
		पूर्ण

		अगर (snd_wavefront_cmd (dev, WFC_DOWNLOAD_BLOCK, शून्य, शून्य)) अणु
			snd_prपूर्णांकk ("download block "
				    "request refused.\n");
			वापस -EIO;
		पूर्ण

		क्रम (i = 0; i < blocksize; i++) अणु

			अगर (dataptr < data_end) अणु
		
				__get_user (sample_लघु, dataptr);
				dataptr += skip;
		
				अगर (data_is_अचिन्हित) अणु /* GUS ? */

					अगर (WF_SAMPLE_IS_8BIT(&header->hdr.s)) अणु
			
						/* 8 bit sample
						 resolution, sign
						 extend both bytes.
						*/
			
						((अचिन्हित अक्षर*)
						 &sample_लघु)[0] += 0x7f;
						((अचिन्हित अक्षर*)
						 &sample_लघु)[1] += 0x7f;
			
					पूर्ण अन्यथा अणु
			
						/* 16 bit sample
						 resolution, sign
						 extend the MSB.
						*/
			
						sample_लघु += 0x7fff;
					पूर्ण
				पूर्ण

			पूर्ण अन्यथा अणु

				/* In padding section of final block:

				   Don't fetch unsupplied data from
				   user space, just जारी with
				   whatever the final value was.
				*/
			पूर्ण
	    
			अगर (i < blocksize - 1) अणु
				outw (sample_लघु, dev->block_port);
			पूर्ण अन्यथा अणु
				outw (sample_लघु, dev->last_block_port);
			पूर्ण
		पूर्ण

		/* Get "DMA page acknowledge", even though its really
		   nothing to करो with DMA at all.
		*/
	
		अगर ((dma_ack = wavefront_पढ़ो (dev)) != WF_DMA_ACK) अणु
			अगर (dma_ack == -1) अणु
				snd_prपूर्णांकk ("upload sample "
					    "DMA ack timeout\n");
				वापस -EIO;
			पूर्ण अन्यथा अणु
				snd_prपूर्णांकk ("upload sample "
					    "DMA ack error 0x%x\n",
					    dma_ack);
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण

	dev->sample_status[header->number] = (WF_SLOT_FILLED|WF_ST_SAMPLE);

	/* Note, label is here because sending the sample header shouldn't
	   alter the sample_status info at all.
	*/

 sent:
	वापस (0);
पूर्ण

अटल पूर्णांक
wavefront_send_alias (snd_wavefront_t *dev, wavefront_patch_info *header)

अणु
	अचिन्हित अक्षर alias_hdr[WF_ALIAS_BYTES];

	DPRINT (WF_DEBUG_LOAD_PATCH, "download alias, %d is "
				      "alias for %d\n",
				      header->number,
				      header->hdr.a.OriginalSample);

	अगर (header->number >= WF_MAX_SAMPLE)
		वापस -EINVAL;

	munge_पूर्णांक32 (header->number, &alias_hdr[0], 2);
	munge_पूर्णांक32 (header->hdr.a.OriginalSample, &alias_hdr[2], 2);
	munge_पूर्णांक32 (*((अचिन्हित पूर्णांक *)&header->hdr.a.sampleStartOffset),
		     &alias_hdr[4], 4);
	munge_पूर्णांक32 (*((अचिन्हित पूर्णांक *)&header->hdr.a.loopStartOffset),
		     &alias_hdr[8], 4);
	munge_पूर्णांक32 (*((अचिन्हित पूर्णांक *)&header->hdr.a.loopEndOffset),
		     &alias_hdr[12], 4);
	munge_पूर्णांक32 (*((अचिन्हित पूर्णांक *)&header->hdr.a.sampleEndOffset),
		     &alias_hdr[16], 4);
	munge_पूर्णांक32 (header->hdr.a.FrequencyBias, &alias_hdr[20], 3);
	munge_पूर्णांक32 (*(&header->hdr.a.FrequencyBias+1), &alias_hdr[23], 2);

	अगर (snd_wavefront_cmd (dev, WFC_DOWNLOAD_SAMPLE_ALIAS, शून्य, alias_hdr)) अणु
		snd_prपूर्णांकk ("download alias failed.\n");
		वापस -EIO;
	पूर्ण

	dev->sample_status[header->number] = (WF_SLOT_FILLED|WF_ST_ALIAS);

	वापस (0);
पूर्ण

अटल पूर्णांक
wavefront_send_multisample (snd_wavefront_t *dev, wavefront_patch_info *header)
अणु
	पूर्णांक i;
	पूर्णांक num_samples;
	अचिन्हित अक्षर *msample_hdr;

	अगर (header->number >= WF_MAX_SAMPLE)
		वापस -EINVAL;

	msample_hdr = kदो_स्मृति(WF_MSAMPLE_BYTES, GFP_KERNEL);
	अगर (! msample_hdr)
		वापस -ENOMEM;

	munge_पूर्णांक32 (header->number, &msample_hdr[0], 2);

	/* You'll recall at this poपूर्णांक that the "number of samples" value
	   in a wavefront_multisample काष्ठा is actually the log2 of the
	   real number of samples.
	*/

	num_samples = (1<<(header->hdr.ms.NumberOfSamples&7));
	msample_hdr[2] = (अचिन्हित अक्षर) header->hdr.ms.NumberOfSamples;

	DPRINT (WF_DEBUG_LOAD_PATCH, "multi %d with %d=%d samples\n",
				      header->number,
				      header->hdr.ms.NumberOfSamples,
				      num_samples);

	क्रम (i = 0; i < num_samples; i++) अणु
		DPRINT(WF_DEBUG_LOAD_PATCH|WF_DEBUG_DATA, "sample[%d] = %d\n",
		       i, header->hdr.ms.SampleNumber[i]);
		munge_पूर्णांक32 (header->hdr.ms.SampleNumber[i],
		     &msample_hdr[3+(i*2)], 2);
	पूर्ण
    
	/* Need a hack here to pass in the number of bytes
	   to be written to the synth. This is ugly, and perhaps
	   one day, I'll fix it.
	*/

	अगर (snd_wavefront_cmd (dev, WFC_DOWNLOAD_MULTISAMPLE, 
			   (अचिन्हित अक्षर *) (दीर्घ) ((num_samples*2)+3),
			   msample_hdr)) अणु
		snd_prपूर्णांकk ("download of multisample failed.\n");
		kमुक्त(msample_hdr);
		वापस -EIO;
	पूर्ण

	dev->sample_status[header->number] = (WF_SLOT_FILLED|WF_ST_MULTISAMPLE);

	kमुक्त(msample_hdr);
	वापस (0);
पूर्ण

अटल पूर्णांक
wavefront_fetch_multisample (snd_wavefront_t *dev, 
			     wavefront_patch_info *header)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर log_ns[1];
	अचिन्हित अक्षर number[2];
	पूर्णांक num_samples;

	munge_पूर्णांक32 (header->number, number, 2);
    
	अगर (snd_wavefront_cmd (dev, WFC_UPLOAD_MULTISAMPLE, log_ns, number)) अणु
		snd_prपूर्णांकk ("upload multisample failed.\n");
		वापस -EIO;
	पूर्ण
    
	DPRINT (WF_DEBUG_DATA, "msample %d has %d samples\n",
				header->number, log_ns[0]);

	header->hdr.ms.NumberOfSamples = log_ns[0];

	/* get the number of samples ... */

	num_samples = (1 << log_ns[0]);
    
	क्रम (i = 0; i < num_samples; i++) अणु
		अक्षर d[2];
		पूर्णांक val;
	
		अगर ((val = wavefront_पढ़ो (dev)) == -1) अणु
			snd_prपूर्णांकk ("upload multisample failed "
				    "during sample loop.\n");
			वापस -EIO;
		पूर्ण
		d[0] = val;

		अगर ((val = wavefront_पढ़ो (dev)) == -1) अणु
			snd_prपूर्णांकk ("upload multisample failed "
				    "during sample loop.\n");
			वापस -EIO;
		पूर्ण
		d[1] = val;
	
		header->hdr.ms.SampleNumber[i] =
			demunge_पूर्णांक32 ((अचिन्हित अक्षर *) d, 2);
	
		DPRINT (WF_DEBUG_DATA, "msample sample[%d] = %d\n",
					i, header->hdr.ms.SampleNumber[i]);
	पूर्ण

	वापस (0);
पूर्ण


अटल पूर्णांक
wavefront_send_drum (snd_wavefront_t *dev, wavefront_patch_info *header)

अणु
	अचिन्हित अक्षर drumbuf[WF_DRUM_BYTES];
	wavefront_drum *drum = &header->hdr.d;
	पूर्णांक i;

	DPRINT (WF_DEBUG_LOAD_PATCH, "downloading edrum for MIDI "
		"note %d, patch = %d\n", 
		header->number, drum->PatchNumber);

	drumbuf[0] = header->number & 0x7f;

	क्रम (i = 0; i < 4; i++) अणु
		munge_पूर्णांक32 (((अचिन्हित अक्षर *)drum)[i], &drumbuf[1+(i*2)], 2);
	पूर्ण

	अगर (snd_wavefront_cmd (dev, WFC_DOWNLOAD_EDRUM_PROGRAM, शून्य, drumbuf)) अणु
		snd_prपूर्णांकk ("download drum failed.\n");
		वापस -EIO;
	पूर्ण

	वापस (0);
पूर्ण

अटल पूर्णांक 
wavefront_find_मुक्त_sample (snd_wavefront_t *dev)

अणु
	पूर्णांक i;

	क्रम (i = 0; i < WF_MAX_SAMPLE; i++) अणु
		अगर (!(dev->sample_status[i] & WF_SLOT_FILLED)) अणु
			वापस i;
		पूर्ण
	पूर्ण
	snd_prपूर्णांकk ("no free sample slots!\n");
	वापस -1;
पूर्ण

#अगर 0
अटल पूर्णांक 
wavefront_find_मुक्त_patch (snd_wavefront_t *dev)

अणु
	पूर्णांक i;

	क्रम (i = 0; i < WF_MAX_PATCH; i++) अणु
		अगर (!(dev->patch_status[i] & WF_SLOT_FILLED)) अणु
			वापस i;
		पूर्ण
	पूर्ण
	snd_prपूर्णांकk ("no free patch slots!\n");
	वापस -1;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
wavefront_load_patch (snd_wavefront_t *dev, स्थिर अक्षर __user *addr)
अणु
	wavefront_patch_info *header;
	पूर्णांक err;
	
	header = kदो_स्मृति(माप(*header), GFP_KERNEL);
	अगर (! header)
		वापस -ENOMEM;

	अगर (copy_from_user (header, addr, माप(wavefront_patch_info) -
			    माप(wavefront_any))) अणु
		snd_prपूर्णांकk ("bad address for load patch.\n");
		err = -EFAULT;
		जाओ __error;
	पूर्ण

	DPRINT (WF_DEBUG_LOAD_PATCH, "download "
				      "Sample type: %d "
				      "Sample number: %d "
				      "Sample size: %d\n",
				      header->subkey,
				      header->number,
				      header->size);

	चयन (header->subkey) अणु
	हाल WF_ST_SAMPLE:  /* sample or sample_header, based on patch->size */

		अगर (copy_from_user (&header->hdr.s, header->hdrptr,
				    माप (wavefront_sample))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		err = wavefront_send_sample (dev, header, header->dataptr, 0);
		अवरोध;

	हाल WF_ST_MULTISAMPLE:

		अगर (copy_from_user (&header->hdr.s, header->hdrptr,
				    माप (wavefront_multisample))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		err = wavefront_send_multisample (dev, header);
		अवरोध;

	हाल WF_ST_ALIAS:

		अगर (copy_from_user (&header->hdr.a, header->hdrptr,
				    माप (wavefront_alias))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		err = wavefront_send_alias (dev, header);
		अवरोध;

	हाल WF_ST_DRUM:
		अगर (copy_from_user (&header->hdr.d, header->hdrptr,
				    माप (wavefront_drum))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		err = wavefront_send_drum (dev, header);
		अवरोध;

	हाल WF_ST_PATCH:
		अगर (copy_from_user (&header->hdr.p, header->hdrptr,
				    माप (wavefront_patch))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		
		err = wavefront_send_patch (dev, header);
		अवरोध;

	हाल WF_ST_PROGRAM:
		अगर (copy_from_user (&header->hdr.pr, header->hdrptr,
				    माप (wavefront_program))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		err = wavefront_send_program (dev, header);
		अवरोध;

	शेष:
		snd_prपूर्णांकk ("unknown patch type %d.\n",
			    header->subkey);
		err = -EINVAL;
		अवरोध;
	पूर्ण

 __error:
	kमुक्त(header);
	वापस err;
पूर्ण

/***********************************************************************
WaveFront: hardware-dependent पूर्णांकerface
***********************************************************************/

अटल व्योम
process_sample_hdr (u8 *buf)

अणु
	wavefront_sample s;
	u8 *ptr;

	ptr = buf;

	/* The board करोesn't send us an exact copy of a "wavefront_sample"
	   in response to an Upload Sample Header command. Instead, we 
	   have to convert the data क्रमmat back पूर्णांकo our data काष्ठाure,
	   just as in the Download Sample command, where we have to करो
	   something very similar in the reverse direction.
	*/

	*((u32 *) &s.sampleStartOffset) = demunge_पूर्णांक32 (ptr, 4); ptr += 4;
	*((u32 *) &s.loopStartOffset) = demunge_पूर्णांक32 (ptr, 4); ptr += 4;
	*((u32 *) &s.loopEndOffset) = demunge_पूर्णांक32 (ptr, 4); ptr += 4;
	*((u32 *) &s.sampleEndOffset) = demunge_पूर्णांक32 (ptr, 4); ptr += 4;
	*((u32 *) &s.FrequencyBias) = demunge_पूर्णांक32 (ptr, 3); ptr += 3;

	s.SampleResolution = *ptr & 0x3;
	s.Loop = *ptr & 0x8;
	s.Bidirectional = *ptr & 0x10;
	s.Reverse = *ptr & 0x40;

	/* Now copy it back to where it came from */

	स_नकल (buf, (अचिन्हित अक्षर *) &s, माप (wavefront_sample));
पूर्ण

अटल पूर्णांक
wavefront_synth_control (snd_wavefront_card_t *acard, 
			 wavefront_control *wc)

अणु
	snd_wavefront_t *dev = &acard->wavefront;
	अचिन्हित अक्षर patchnumbuf[2];
	पूर्णांक i;

	DPRINT (WF_DEBUG_CMD, "synth control with "
		"cmd 0x%x\n", wc->cmd);

	/* Pre-handling of or क्रम various commands */

	चयन (wc->cmd) अणु
		
	हाल WFC_DISABLE_INTERRUPTS:
		snd_prपूर्णांकk ("interrupts disabled.\n");
		outb (0x80|0x20, dev->control_port);
		dev->पूर्णांकerrupts_are_midi = 1;
		वापस 0;

	हाल WFC_ENABLE_INTERRUPTS:
		snd_prपूर्णांकk ("interrupts enabled.\n");
		outb (0x80|0x40|0x20, dev->control_port);
		dev->पूर्णांकerrupts_are_midi = 1;
		वापस 0;

	हाल WFC_INTERRUPT_STATUS:
		wc->rbuf[0] = dev->पूर्णांकerrupts_are_midi;
		वापस 0;

	हाल WFC_ROMSAMPLES_RDONLY:
		dev->rom_samples_rकरोnly = wc->wbuf[0];
		wc->status = 0;
		वापस 0;

	हाल WFC_IDENTIFY_SLOT_TYPE:
		i = wc->wbuf[0] | (wc->wbuf[1] << 7);
		अगर (i <0 || i >= WF_MAX_SAMPLE) अणु
			snd_prपूर्णांकk ("invalid slot ID %d\n",
				i);
			wc->status = EINVAL;
			वापस -EINVAL;
		पूर्ण
		wc->rbuf[0] = dev->sample_status[i];
		wc->status = 0;
		वापस 0;

	हाल WFC_DEBUG_DRIVER:
		dev->debug = wc->wbuf[0];
		snd_prपूर्णांकk ("debug = 0x%x\n", dev->debug);
		वापस 0;

	हाल WFC_UPLOAD_PATCH:
		munge_पूर्णांक32 (*((u32 *) wc->wbuf), patchnumbuf, 2);
		स_नकल (wc->wbuf, patchnumbuf, 2);
		अवरोध;

	हाल WFC_UPLOAD_MULTISAMPLE:
		/* multisamples have to be handled dअगरferently, and
		   cannot be dealt with properly by snd_wavefront_cmd() alone.
		*/
		wc->status = wavefront_fetch_multisample
			(dev, (wavefront_patch_info *) wc->rbuf);
		वापस 0;

	हाल WFC_UPLOAD_SAMPLE_ALIAS:
		snd_prपूर्णांकk ("support for sample alias upload "
			"being considered.\n");
		wc->status = EINVAL;
		वापस -EINVAL;
	पूर्ण

	wc->status = snd_wavefront_cmd (dev, wc->cmd, wc->rbuf, wc->wbuf);

	/* Post-handling of certain commands.

	   In particular, अगर the command was an upload, demunge the data
	   so that the user-level करोesn't have to think about it.
	*/

	अगर (wc->status == 0) अणु
		चयन (wc->cmd) अणु
			/* पूर्णांकercept any मुक्तmem requests so that we know
			   we are always current with the user-level view
			   of things.
			*/

		हाल WFC_REPORT_FREE_MEMORY:
			dev->मुक्तmem = demunge_पूर्णांक32 (wc->rbuf, 4);
			अवरोध;

		हाल WFC_UPLOAD_PATCH:
			demunge_buf (wc->rbuf, wc->rbuf, WF_PATCH_BYTES);
			अवरोध;

		हाल WFC_UPLOAD_PROGRAM:
			demunge_buf (wc->rbuf, wc->rbuf, WF_PROGRAM_BYTES);
			अवरोध;

		हाल WFC_UPLOAD_EDRUM_PROGRAM:
			demunge_buf (wc->rbuf, wc->rbuf, WF_DRUM_BYTES - 1);
			अवरोध;

		हाल WFC_UPLOAD_SAMPLE_HEADER:
			process_sample_hdr (wc->rbuf);
			अवरोध;

		हाल WFC_UPLOAD_SAMPLE_ALIAS:
			snd_prपूर्णांकk ("support for "
				    "sample aliases still "
				    "being considered.\n");
			अवरोध;

		हाल WFC_VMIDI_OFF:
			snd_wavefront_midi_disable_भव (acard);
			अवरोध;

		हाल WFC_VMIDI_ON:
			snd_wavefront_midi_enable_भव (acard);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक 
snd_wavefront_synth_खोलो (काष्ठा snd_hwdep *hw, काष्ठा file *file)

अणु
	अगर (!try_module_get(hw->card->module))
		वापस -EFAULT;
	file->निजी_data = hw;
	वापस 0;
पूर्ण

पूर्णांक 
snd_wavefront_synth_release (काष्ठा snd_hwdep *hw, काष्ठा file *file)

अणु
	module_put(hw->card->module);
	वापस 0;
पूर्ण

पूर्णांक
snd_wavefront_synth_ioctl (काष्ठा snd_hwdep *hw, काष्ठा file *file,
			   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)

अणु
	काष्ठा snd_card *card;
	snd_wavefront_t *dev;
	snd_wavefront_card_t *acard;
	wavefront_control *wc;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक err;

	card = (काष्ठा snd_card *) hw->card;

	अगर (snd_BUG_ON(!card))
		वापस -ENODEV;
	अगर (snd_BUG_ON(!card->निजी_data))
		वापस -ENODEV;

	acard = card->निजी_data;
	dev = &acard->wavefront;
	
	चयन (cmd) अणु
	हाल WFCTL_LOAD_SPP:
		अगर (wavefront_load_patch (dev, argp) != 0) अणु
			वापस -EIO;
		पूर्ण
		अवरोध;

	हाल WFCTL_WFCMD:
		wc = memdup_user(argp, माप(*wc));
		अगर (IS_ERR(wc))
			वापस PTR_ERR(wc);

		अगर (wavefront_synth_control (acard, wc) < 0)
			err = -EIO;
		अन्यथा अगर (copy_to_user (argp, wc, माप (*wc)))
			err = -EFAULT;
		अन्यथा
			err = 0;
		kमुक्त(wc);
		वापस err;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


/***********************************************************************/
/*  WaveFront: पूर्णांकerface क्रम card-level wavefront module               */
/***********************************************************************/

व्योम
snd_wavefront_पूर्णांकernal_पूर्णांकerrupt (snd_wavefront_card_t *card)
अणु
	snd_wavefront_t *dev = &card->wavefront;

	/*
	   Some comments on पूर्णांकerrupts. I attempted a version of this
	   driver that used पूर्णांकerrupts throughout the code instead of
	   करोing busy and/or sleep-रुकोing. Alas, it appears that once
	   the Motorola firmware is करोwnloaded, the card *never*
	   generates an RX पूर्णांकerrupt. These are successfully generated
	   during firmware loading, and after that wavefront_status()
	   reports that an पूर्णांकerrupt is pending on the card from समय
	   to समय, but it never seems to be delivered to this
	   driver. Note also that wavefront_status() जारीs to
	   report that RX पूर्णांकerrupts are enabled, suggesting that I
	   didn't goof up and disable them by mistake.

	   Thus, I stepped back to a prior version of
	   wavefront_रुको(), the only place where this really
	   matters. Its sad, but I've looked through the code to check
	   on things, and I really feel certain that the Motorola
	   firmware prevents RX-पढ़ोy पूर्णांकerrupts.
	*/

	अगर ((wavefront_status(dev) & (STAT_INTR_READ|STAT_INTR_WRITE)) == 0) अणु
		वापस;
	पूर्ण

	spin_lock(&dev->irq_lock);
	dev->irq_ok = 1;
	dev->irq_cnt++;
	spin_unlock(&dev->irq_lock);
	wake_up(&dev->पूर्णांकerrupt_sleeper);
पूर्ण

/* STATUS REGISTER 

0 Host Rx Interrupt Enable (1=Enabled)
1 Host Rx Register Full (1=Full)
2 Host Rx Interrupt Pending (1=Interrupt)
3 Unused
4 Host Tx Interrupt (1=Enabled)
5 Host Tx Register empty (1=Empty)
6 Host Tx Interrupt Pending (1=Interrupt)
7 Unused
*/

अटल पूर्णांक
snd_wavefront_पूर्णांकerrupt_bits (पूर्णांक irq)

अणु
	पूर्णांक bits;

	चयन (irq) अणु
	हाल 9:
		bits = 0x00;
		अवरोध;
	हाल 5:
		bits = 0x08;
		अवरोध;
	हाल 12:
		bits = 0x10;
		अवरोध;
	हाल 15:
		bits = 0x18;
		अवरोध;
	
	शेष:
		snd_prपूर्णांकk ("invalid IRQ %d\n", irq);
		bits = -1;
	पूर्ण

	वापस bits;
पूर्ण

अटल व्योम
wavefront_should_cause_पूर्णांकerrupt (snd_wavefront_t *dev, 
				  पूर्णांक val, पूर्णांक port, अचिन्हित दीर्घ समयout)

अणु
	रुको_queue_entry_t रुको;

	init_रुकोqueue_entry(&रुको, current);
	spin_lock_irq(&dev->irq_lock);
	add_रुको_queue(&dev->पूर्णांकerrupt_sleeper, &रुको);
	dev->irq_ok = 0;
	outb (val,port);
	spin_unlock_irq(&dev->irq_lock);
	जबतक (!dev->irq_ok && समय_beक्रमe(jअगरfies, समयout)) अणु
		schedule_समयout_unपूर्णांकerruptible(1);
		barrier();
	पूर्ण
पूर्ण

अटल पूर्णांक
wavefront_reset_to_cleanliness (snd_wavefront_t *dev)

अणु
	पूर्णांक bits;
	पूर्णांक hwv[2];

	/* IRQ alपढ़ोy checked */

	bits = snd_wavefront_पूर्णांकerrupt_bits (dev->irq);

	/* try reset of port */

	outb (0x0, dev->control_port); 
  
	/* At this poपूर्णांक, the board is in reset, and the H/W initialization
	   रेजिस्टर is accessed at the same address as the data port.
     
	   Bit 7 - Enable IRQ Driver	
	   0 - Tri-state the Wave-Board drivers क्रम the PC Bus IRQs
	   1 - Enable IRQ selected by bits 5:3 to be driven onto the PC Bus.
     
	   Bit 6 - MIDI Interface Select

	   0 - Use the MIDI Input from the 26-pin WaveBlaster
	   compatible header as the serial MIDI source
	   1 - Use the MIDI Input from the 9-pin D connector as the
	   serial MIDI source.
     
	   Bits 5:3 - IRQ Selection
	   0 0 0 - IRQ 2/9
	   0 0 1 - IRQ 5
	   0 1 0 - IRQ 12
	   0 1 1 - IRQ 15
	   1 0 0 - Reserved
	   1 0 1 - Reserved
	   1 1 0 - Reserved
	   1 1 1 - Reserved
     
	   Bits 2:1 - Reserved
	   Bit 0 - Disable Boot ROM
	   0 - memory accesses to 03FC30-03FFFFH utilize the पूर्णांकernal Boot ROM
	   1 - memory accesses to 03FC30-03FFFFH are directed to बाह्यal 
	   storage.
     
	*/

	/* configure hardware: IRQ, enable पूर्णांकerrupts, 
	   plus बाह्यal 9-pin MIDI पूर्णांकerface selected
	*/

	outb (0x80 | 0x40 | bits, dev->data_port);	
  
	/* CONTROL REGISTER

	   0 Host Rx Interrupt Enable (1=Enabled)      0x1
	   1 Unused                                    0x2
	   2 Unused                                    0x4
	   3 Unused                                    0x8
	   4 Host Tx Interrupt Enable                 0x10
	   5 Mute (0=Mute; 1=Play)                    0x20
	   6 Master Interrupt Enable (1=Enabled)      0x40
	   7 Master Reset (0=Reset; 1=Run)            0x80

	   Take us out of reset, mute output, master + TX + RX पूर्णांकerrupts on.
	   
	   We'll get an पूर्णांकerrupt presumably to tell us that the TX
	   रेजिस्टर is clear.
	*/

	wavefront_should_cause_पूर्णांकerrupt(dev, 0x80|0x40|0x10|0x1,
					 dev->control_port,
					 (reset_समय*HZ)/100);

	/* Note: data port is now the data port, not the h/w initialization
	   port.
	 */

	अगर (!dev->irq_ok) अणु
		snd_prपूर्णांकk ("intr not received after h/w un-reset.\n");
		जाओ gone_bad;
	पूर्ण 

	/* Note: data port is now the data port, not the h/w initialization
	   port.

	   At this poपूर्णांक, only "HW VERSION" or "DOWNLOAD OS" commands
	   will work. So, issue one of them, and रुको क्रम TX
	   पूर्णांकerrupt. This can take a *दीर्घ* समय after a cold boot,
	   जबतक the ISC ROM करोes its RAM test. The SDK says up to 4
	   seconds - with 12MB of RAM on a Tropez+, it takes a lot
	   दीर्घer than that (~16secs). Note that the card understands
	   the dअगरference between a warm and a cold boot, so
	   subsequent ISC2115 reboots (say, caused by module
	   reloading) will get through this much faster.

	   XXX Interesting question: why is no RX पूर्णांकerrupt received first ?
	*/

	wavefront_should_cause_पूर्णांकerrupt(dev, WFC_HARDWARE_VERSION, 
					 dev->data_port, ramcheck_समय*HZ);

	अगर (!dev->irq_ok) अणु
		snd_prपूर्णांकk ("post-RAM-check interrupt not received.\n");
		जाओ gone_bad;
	पूर्ण 

	अगर (!wavefront_रुको (dev, STAT_CAN_READ)) अणु
		snd_prपूर्णांकk ("no response to HW version cmd.\n");
		जाओ gone_bad;
	पूर्ण
	
	अगर ((hwv[0] = wavefront_पढ़ो (dev)) == -1) अणु
		snd_prपूर्णांकk ("board not responding correctly.\n");
		जाओ gone_bad;
	पूर्ण

	अगर (hwv[0] == 0xFF) अणु /* NAK */

		/* Board's RAM test failed. Try to पढ़ो error code,
		   and tell us about it either way.
		*/
		
		अगर ((hwv[0] = wavefront_पढ़ो (dev)) == -1) अणु
			snd_prपूर्णांकk ("on-board RAM test failed "
				    "(bad error code).\n");
		पूर्ण अन्यथा अणु
			snd_prपूर्णांकk ("on-board RAM test failed "
				    "(error code: 0x%x).\n",
				hwv[0]);
		पूर्ण
		जाओ gone_bad;
	पूर्ण

	/* We're OK, just get the next byte of the HW version response */

	अगर ((hwv[1] = wavefront_पढ़ो (dev)) == -1) अणु
		snd_prपूर्णांकk ("incorrect h/w response.\n");
		जाओ gone_bad;
	पूर्ण

	snd_prपूर्णांकk ("hardware version %d.%d\n",
		    hwv[0], hwv[1]);

	वापस 0;


     gone_bad:
	वापस (1);
पूर्ण

अटल पूर्णांक
wavefront_करोwnload_firmware (snd_wavefront_t *dev, अक्षर *path)

अणु
	स्थिर अचिन्हित अक्षर *buf;
	पूर्णांक len, err;
	पूर्णांक section_cnt_करोwnloaded = 0;
	स्थिर काष्ठा firmware *firmware;

	err = request_firmware(&firmware, path, dev->card->dev);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "firmware (%s) download failed!!!\n", path);
		वापस 1;
	पूर्ण

	len = 0;
	buf = firmware->data;
	क्रम (;;) अणु
		पूर्णांक section_length = *(चिन्हित अक्षर *)buf;
		अगर (section_length == 0)
			अवरोध;
		अगर (section_length < 0 || section_length > WF_SECTION_MAX) अणु
			snd_prपूर्णांकk(KERN_ERR
				   "invalid firmware section length %d\n",
				   section_length);
			जाओ failure;
		पूर्ण
		buf++;
		len++;

		अगर (firmware->size < len + section_length) अणु
			snd_prपूर्णांकk(KERN_ERR "firmware section read error.\n");
			जाओ failure;
		पूर्ण

		/* Send command */
		अगर (wavefront_ग_लिखो(dev, WFC_DOWNLOAD_OS))
			जाओ failure;
	
		क्रम (; section_length; section_length--) अणु
			अगर (wavefront_ग_लिखो(dev, *buf))
				जाओ failure;
			buf++;
			len++;
		पूर्ण
	
		/* get ACK */
		अगर (!wavefront_रुको(dev, STAT_CAN_READ)) अणु
			snd_prपूर्णांकk(KERN_ERR "time out for firmware ACK.\n");
			जाओ failure;
		पूर्ण
		err = inb(dev->data_port);
		अगर (err != WF_ACK) अणु
			snd_prपूर्णांकk(KERN_ERR
				   "download of section #%d not "
				   "acknowledged, ack = 0x%x\n",
				   section_cnt_करोwnloaded + 1, err);
			जाओ failure;
		पूर्ण

		section_cnt_करोwnloaded++;
	पूर्ण

	release_firmware(firmware);
	वापस 0;

 failure:
	release_firmware(firmware);
	snd_prपूर्णांकk(KERN_ERR "firmware download failed!!!\n");
	वापस 1;
पूर्ण


अटल पूर्णांक
wavefront_करो_reset (snd_wavefront_t *dev)

अणु
	अक्षर voices[1];

	अगर (wavefront_reset_to_cleanliness (dev)) अणु
		snd_prपूर्णांकk ("hw reset failed.\n");
		जाओ gone_bad;
	पूर्ण

	अगर (dev->israw) अणु
		अगर (wavefront_करोwnload_firmware (dev, ospath)) अणु
			जाओ gone_bad;
		पूर्ण

		dev->israw = 0;

		/* Wait क्रम the OS to get running. The protocol क्रम
		   this is non-obvious, and was determined by
		   using port-IO tracing in DOSemu and some
		   experimentation here.
		   
		   Rather than using समयd रुकोs, use पूर्णांकerrupts creatively.
		*/

		wavefront_should_cause_पूर्णांकerrupt (dev, WFC_NOOP,
						  dev->data_port,
						  (osrun_समय*HZ));

		अगर (!dev->irq_ok) अणु
			snd_prपूर्णांकk ("no post-OS interrupt.\n");
			जाओ gone_bad;
		पूर्ण
		
		/* Now, करो it again ! */
		
		wavefront_should_cause_पूर्णांकerrupt (dev, WFC_NOOP,
						  dev->data_port, (10*HZ));
		
		अगर (!dev->irq_ok) अणु
			snd_prपूर्णांकk ("no post-OS interrupt(2).\n");
			जाओ gone_bad;
		पूर्ण

		/* OK, no (RX/TX) पूर्णांकerrupts any more, but leave mute
		   in effect. 
		*/
		
		outb (0x80|0x40, dev->control_port); 
	पूर्ण

	/* SETUPSND.EXE asks क्रम sample memory config here, but since i
	   have no idea how to पूर्णांकerpret the result, we'll क्रमget
	   about it.
	*/
	
	अगर ((dev->मुक्तmem = wavefront_मुक्तmem (dev)) < 0) अणु
		जाओ gone_bad;
	पूर्ण
		
	snd_prपूर्णांकk ("available DRAM %dk\n", dev->मुक्तmem / 1024);

	अगर (wavefront_ग_लिखो (dev, 0xf0) ||
	    wavefront_ग_लिखो (dev, 1) ||
	    (wavefront_पढ़ो (dev) < 0)) अणु
		dev->debug = 0;
		snd_prपूर्णांकk ("MPU emulation mode not set.\n");
		जाओ gone_bad;
	पूर्ण

	voices[0] = 32;

	अगर (snd_wavefront_cmd (dev, WFC_SET_NVOICES, शून्य, voices)) अणु
		snd_prपूर्णांकk ("cannot set number of voices to 32.\n");
		जाओ gone_bad;
	पूर्ण


	वापस 0;

 gone_bad:
	/* reset that sucker so that it करोesn't bother us. */

	outb (0x0, dev->control_port);
	dev->पूर्णांकerrupts_are_midi = 0;
	वापस 1;
पूर्ण

पूर्णांक
snd_wavefront_start (snd_wavefront_t *dev)

अणु
	पूर्णांक samples_are_from_rom;

	/* IMPORTANT: assumes that snd_wavefront_detect() and/or
	   wavefront_reset_to_cleanliness() has alपढ़ोy been called 
	*/

	अगर (dev->israw) अणु
		samples_are_from_rom = 1;
	पूर्ण अन्यथा अणु
		/* XXX is this always true ? */
		samples_are_from_rom = 0;
	पूर्ण

	अगर (dev->israw || fx_raw) अणु
		अगर (wavefront_करो_reset (dev)) अणु
			वापस -1;
		पूर्ण
	पूर्ण
	/* Check क्रम FX device, present only on Tropez+ */

	dev->has_fx = (snd_wavefront_fx_detect (dev) == 0);

	अगर (dev->has_fx && fx_raw) अणु
		snd_wavefront_fx_start (dev);
	पूर्ण

	wavefront_get_sample_status (dev, samples_are_from_rom);
	wavefront_get_program_status (dev);
	wavefront_get_patch_status (dev);

	/* Start normal operation: unreset, master पूर्णांकerrupt enabled, no mute
	*/

	outb (0x80|0x40|0x20, dev->control_port); 

	वापस (0);
पूर्ण

पूर्णांक
snd_wavefront_detect (snd_wavefront_card_t *card)

अणु
	अचिन्हित अक्षर   rbuf[4], wbuf[4];
	snd_wavefront_t *dev = &card->wavefront;
	
	/* वापसs zero अगर a WaveFront card is successfully detected.
	   negative otherwise.
	*/

	dev->israw = 0;
	dev->has_fx = 0;
	dev->debug = debug_शेष;
	dev->पूर्णांकerrupts_are_midi = 0;
	dev->irq_cnt = 0;
	dev->rom_samples_rकरोnly = 1;

	अगर (snd_wavefront_cmd (dev, WFC_FIRMWARE_VERSION, rbuf, wbuf) == 0) अणु

		dev->fw_version[0] = rbuf[0];
		dev->fw_version[1] = rbuf[1];

		snd_prपूर्णांकk ("firmware %d.%d already loaded.\n",
			    rbuf[0], rbuf[1]);

		/* check that a command actually works */
      
		अगर (snd_wavefront_cmd (dev, WFC_HARDWARE_VERSION,
				       rbuf, wbuf) == 0) अणु
			dev->hw_version[0] = rbuf[0];
			dev->hw_version[1] = rbuf[1];
		पूर्ण अन्यथा अणु
			snd_prपूर्णांकk ("not raw, but no "
				    "hardware version!\n");
			वापस -1;
		पूर्ण

		अगर (!wf_raw) अणु
			वापस 0;
		पूर्ण अन्यथा अणु
			snd_prपूर्णांकk ("reloading firmware as you requested.\n");
			dev->israw = 1;
		पूर्ण

	पूर्ण अन्यथा अणु

		dev->israw = 1;
		snd_prपूर्णांकk ("no response to firmware probe, assume raw.\n");

	पूर्ण

	वापस 0;
पूर्ण

MODULE_FIRMWARE(DEFAULT_OSPATH);
