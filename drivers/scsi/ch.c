<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SCSI Media Changer device driver क्रम Linux 2.6
 *
 *     (c) 1996-2003 Gerd Knorr <kraxel@bytesex.org>
 *
 */

#घोषणा VERSION "0.25"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/major.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/completion.h>
#समावेश <linux/compat.h>
#समावेश <linux/chपन.स>			/* here are all the ioctls */
#समावेश <linux/mutex.h>
#समावेश <linux/idr.h>
#समावेश <linux/slab.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_driver.h>
#समावेश <scsi/scsi_ioctl.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_dbg.h>

#घोषणा CH_DT_MAX       16
#घोषणा CH_TYPES        8
#घोषणा CH_MAX_DEVS     128

MODULE_DESCRIPTION("device driver for scsi media changer devices");
MODULE_AUTHOR("Gerd Knorr <kraxel@bytesex.org>");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CHARDEV_MAJOR(SCSI_CHANGER_MAJOR);
MODULE_ALIAS_SCSI_DEVICE(TYPE_MEDIUM_CHANGER);

अटल पूर्णांक init = 1;
module_param(init, पूर्णांक, 0444);
MODULE_PARM_DESC(init, \
    "initialize element status on driver load (default: on)");

अटल पूर्णांक समयout_move = 300;
module_param(समयout_move, पूर्णांक, 0644);
MODULE_PARM_DESC(समयout_move,"timeout for move commands "
		 "(default: 300 seconds)");

अटल पूर्णांक समयout_init = 3600;
module_param(समयout_init, पूर्णांक, 0644);
MODULE_PARM_DESC(समयout_init,"timeout for INITIALIZE ELEMENT STATUS "
		 "(default: 3600 seconds)");

अटल पूर्णांक verbose = 1;
module_param(verbose, पूर्णांक, 0644);
MODULE_PARM_DESC(verbose,"be verbose (default: on)");

अटल पूर्णांक debug = 0;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug,"enable/disable debug messages, also prints more "
		 "detailed sense codes on scsi errors (default: off)");

अटल पूर्णांक dt_id[CH_DT_MAX] = अणु [ 0 ... (CH_DT_MAX-1) ] = -1 पूर्ण;
अटल पूर्णांक dt_lun[CH_DT_MAX];
module_param_array(dt_id,  पूर्णांक, शून्य, 0444);
module_param_array(dt_lun, पूर्णांक, शून्य, 0444);

/* tell the driver about venकरोr-specअगरic slots */
अटल पूर्णांक venकरोr_firsts[CH_TYPES-4];
अटल पूर्णांक venकरोr_counts[CH_TYPES-4];
module_param_array(venकरोr_firsts, पूर्णांक, शून्य, 0444);
module_param_array(venकरोr_counts, पूर्णांक, शून्य, 0444);

अटल स्थिर अक्षर * venकरोr_labels[CH_TYPES-4] = अणु
	"v0", "v1", "v2", "v3"
पूर्ण;
// module_param_string_array(venकरोr_labels, शून्य, 0444);

#घोषणा ch_prपूर्णांकk(prefix, ch, fmt, a...) \
	sdev_prefix_prपूर्णांकk(prefix, (ch)->device, (ch)->name, fmt, ##a)

#घोषणा DPRINTK(fmt, arg...)						\
करो अणु									\
	अगर (debug)							\
		ch_prपूर्णांकk(KERN_DEBUG, ch, fmt, ##arg);			\
पूर्ण जबतक (0)
#घोषणा VPRINTK(level, fmt, arg...)					\
करो अणु									\
	अगर (verbose)							\
		ch_prपूर्णांकk(level, ch, fmt, ##arg);			\
पूर्ण जबतक (0)

/* ------------------------------------------------------------------- */

#घोषणा MAX_RETRIES   1

अटल काष्ठा class * ch_sysfs_class;

प्रकार काष्ठा अणु
	काष्ठा kref         ref;
	काष्ठा list_head    list;
	पूर्णांक                 minor;
	अक्षर                name[8];
	काष्ठा scsi_device  *device;
	काष्ठा scsi_device  **dt;        /* ptrs to data transfer elements */
	u_पूर्णांक               firsts[CH_TYPES];
	u_पूर्णांक               counts[CH_TYPES];
	u_पूर्णांक               unit_attention;
	u_पूर्णांक		    voltags;
	काष्ठा mutex	    lock;
पूर्ण scsi_changer;

अटल DEFINE_IDR(ch_index_idr);
अटल DEFINE_SPINLOCK(ch_index_lock);

अटल स्थिर काष्ठा अणु
	अचिन्हित अक्षर  sense;
	अचिन्हित अक्षर  asc;
	अचिन्हित अक्षर  ascq;
	पूर्णांक	       त्रुटि_सं;
पूर्ण ch_err[] = अणु
/* Just filled in what looks right. Hav'nt checked any standard paper क्रम
   these त्रुटि_सं assignments, so they may be wrong... */
	अणु
		.sense  = ILLEGAL_REQUEST,
		.asc    = 0x21,
		.ascq   = 0x01,
		.त्रुटि_सं  = EBADSLT, /* Invalid element address */
	पूर्ण,अणु
		.sense  = ILLEGAL_REQUEST,
		.asc    = 0x28,
		.ascq   = 0x01,
		.त्रुटि_सं  = EBADE,   /* Import or export element accessed */
	पूर्ण,अणु
		.sense  = ILLEGAL_REQUEST,
		.asc    = 0x3B,
		.ascq   = 0x0D,
		.त्रुटि_सं  = EXFULL,  /* Medium destination element full */
	पूर्ण,अणु
		.sense  = ILLEGAL_REQUEST,
		.asc    = 0x3B,
		.ascq   = 0x0E,
		.त्रुटि_सं  = EBADE,   /* Medium source element empty */
	पूर्ण,अणु
		.sense  = ILLEGAL_REQUEST,
		.asc    = 0x20,
		.ascq   = 0x00,
		.त्रुटि_सं  = EBADRQC, /* Invalid command operation code */
	पूर्ण,अणु
	        /* end of list */
	पूर्ण
पूर्ण;

/* ------------------------------------------------------------------- */

अटल पूर्णांक ch_find_त्रुटि_सं(काष्ठा scsi_sense_hdr *sshdr)
अणु
	पूर्णांक i,त्रुटि_सं = 0;

	/* Check to see अगर additional sense inक्रमmation is available */
	अगर (scsi_sense_valid(sshdr) &&
	    sshdr->asc != 0) अणु
		क्रम (i = 0; ch_err[i].त्रुटि_सं != 0; i++) अणु
			अगर (ch_err[i].sense == sshdr->sense_key &&
			    ch_err[i].asc   == sshdr->asc &&
			    ch_err[i].ascq  == sshdr->ascq) अणु
				त्रुटि_सं = -ch_err[i].त्रुटि_सं;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (त्रुटि_सं == 0)
		त्रुटि_सं = -EIO;
	वापस त्रुटि_सं;
पूर्ण

अटल पूर्णांक
ch_करो_scsi(scsi_changer *ch, अचिन्हित अक्षर *cmd, पूर्णांक cmd_len,
	   व्योम *buffer, अचिन्हित buflength,
	   क्रमागत dma_data_direction direction)
अणु
	पूर्णांक त्रुटि_सं, retries = 0, समयout, result;
	काष्ठा scsi_sense_hdr sshdr;

	समयout = (cmd[0] == INITIALIZE_ELEMENT_STATUS)
		? समयout_init : समयout_move;

 retry:
	त्रुटि_सं = 0;
	result = scsi_execute_req(ch->device, cmd, direction, buffer,
				  buflength, &sshdr, समयout * HZ,
				  MAX_RETRIES, शून्य);

	अगर (driver_byte(result) == DRIVER_SENSE) अणु
		अगर (debug)
			scsi_prपूर्णांक_sense_hdr(ch->device, ch->name, &sshdr);
		त्रुटि_सं = ch_find_त्रुटि_सं(&sshdr);

		चयन(sshdr.sense_key) अणु
		हाल UNIT_ATTENTION:
			ch->unit_attention = 1;
			अगर (retries++ < 3)
				जाओ retry;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस त्रुटि_सं;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक
ch_elem_to_typecode(scsi_changer *ch, u_पूर्णांक elem)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CH_TYPES; i++) अणु
		अगर (elem >= ch->firsts[i]  &&
		    elem <  ch->firsts[i] +
	            ch->counts[i])
			वापस i+1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
ch_पढ़ो_element_status(scsi_changer *ch, u_पूर्णांक elem, अक्षर *data)
अणु
	u_अक्षर  cmd[12];
	u_अक्षर  *buffer;
	पूर्णांक     result;

	buffer = kदो_स्मृति(512, GFP_KERNEL | GFP_DMA);
	अगर(!buffer)
		वापस -ENOMEM;

 retry:
	स_रखो(cmd,0,माप(cmd));
	cmd[0] = READ_ELEMENT_STATUS;
	cmd[1] = ((ch->device->lun & 0x7) << 5) |
		(ch->voltags ? 0x10 : 0) |
		ch_elem_to_typecode(ch,elem);
	cmd[2] = (elem >> 8) & 0xff;
	cmd[3] = elem        & 0xff;
	cmd[5] = 1;
	cmd[9] = 255;
	अगर (0 == (result = ch_करो_scsi(ch, cmd, 12,
				      buffer, 256, DMA_FROM_DEVICE))) अणु
		अगर (((buffer[16] << 8) | buffer[17]) != elem) अणु
			DPRINTK("asked for element 0x%02x, got 0x%02x\n",
				elem,(buffer[16] << 8) | buffer[17]);
			kमुक्त(buffer);
			वापस -EIO;
		पूर्ण
		स_नकल(data,buffer+16,16);
	पूर्ण अन्यथा अणु
		अगर (ch->voltags) अणु
			ch->voltags = 0;
			VPRINTK(KERN_INFO, "device has no volume tag support\n");
			जाओ retry;
		पूर्ण
		DPRINTK("READ ELEMENT STATUS for element 0x%x failed\n",elem);
	पूर्ण
	kमुक्त(buffer);
	वापस result;
पूर्ण

अटल पूर्णांक
ch_init_elem(scsi_changer *ch)
अणु
	पूर्णांक err;
	u_अक्षर cmd[6];

	VPRINTK(KERN_INFO, "INITIALIZE ELEMENT STATUS, may take some time ...\n");
	स_रखो(cmd,0,माप(cmd));
	cmd[0] = INITIALIZE_ELEMENT_STATUS;
	cmd[1] = (ch->device->lun & 0x7) << 5;
	err = ch_करो_scsi(ch, cmd, 6, शून्य, 0, DMA_NONE);
	VPRINTK(KERN_INFO, "... finished\n");
	वापस err;
पूर्ण

अटल पूर्णांक
ch_पढ़ोconfig(scsi_changer *ch)
अणु
	u_अक्षर  cmd[10], data[16];
	u_अक्षर  *buffer;
	पूर्णांक     result,id,lun,i;
	u_पूर्णांक   elem;

	buffer = kzalloc(512, GFP_KERNEL | GFP_DMA);
	अगर (!buffer)
		वापस -ENOMEM;

	स_रखो(cmd,0,माप(cmd));
	cmd[0] = MODE_SENSE;
	cmd[1] = (ch->device->lun & 0x7) << 5;
	cmd[2] = 0x1d;
	cmd[4] = 255;
	result = ch_करो_scsi(ch, cmd, 10, buffer, 255, DMA_FROM_DEVICE);
	अगर (0 != result) अणु
		cmd[1] |= (1<<3);
		result  = ch_करो_scsi(ch, cmd, 10, buffer, 255, DMA_FROM_DEVICE);
	पूर्ण
	अगर (0 == result) अणु
		ch->firsts[CHET_MT] =
			(buffer[buffer[3]+ 6] << 8) | buffer[buffer[3]+ 7];
		ch->counts[CHET_MT] =
			(buffer[buffer[3]+ 8] << 8) | buffer[buffer[3]+ 9];
		ch->firsts[CHET_ST] =
			(buffer[buffer[3]+10] << 8) | buffer[buffer[3]+11];
		ch->counts[CHET_ST] =
			(buffer[buffer[3]+12] << 8) | buffer[buffer[3]+13];
		ch->firsts[CHET_IE] =
			(buffer[buffer[3]+14] << 8) | buffer[buffer[3]+15];
		ch->counts[CHET_IE] =
			(buffer[buffer[3]+16] << 8) | buffer[buffer[3]+17];
		ch->firsts[CHET_DT] =
			(buffer[buffer[3]+18] << 8) | buffer[buffer[3]+19];
		ch->counts[CHET_DT] =
			(buffer[buffer[3]+20] << 8) | buffer[buffer[3]+21];
		VPRINTK(KERN_INFO, "type #1 (mt): 0x%x+%d [medium transport]\n",
			ch->firsts[CHET_MT],
			ch->counts[CHET_MT]);
		VPRINTK(KERN_INFO, "type #2 (st): 0x%x+%d [storage]\n",
			ch->firsts[CHET_ST],
			ch->counts[CHET_ST]);
		VPRINTK(KERN_INFO, "type #3 (ie): 0x%x+%d [import/export]\n",
			ch->firsts[CHET_IE],
			ch->counts[CHET_IE]);
		VPRINTK(KERN_INFO, "type #4 (dt): 0x%x+%d [data transfer]\n",
			ch->firsts[CHET_DT],
			ch->counts[CHET_DT]);
	पूर्ण अन्यथा अणु
		VPRINTK(KERN_INFO, "reading element address assignment page failed!\n");
	पूर्ण

	/* venकरोr specअगरic element types */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (0 == venकरोr_counts[i])
			जारी;
		अगर (शून्य == venकरोr_labels[i])
			जारी;
		ch->firsts[CHET_V1+i] = venकरोr_firsts[i];
		ch->counts[CHET_V1+i] = venकरोr_counts[i];
		VPRINTK(KERN_INFO, "type #%d (v%d): 0x%x+%d [%s, vendor specific]\n",
			i+5,i+1,venकरोr_firsts[i],venकरोr_counts[i],
			venकरोr_labels[i]);
	पूर्ण

	/* look up the devices of the data transfer elements */
	ch->dt = kसुस्मृति(ch->counts[CHET_DT], माप(*ch->dt),
			 GFP_KERNEL);

	अगर (!ch->dt) अणु
		kमुक्त(buffer);
		वापस -ENOMEM;
	पूर्ण

	क्रम (elem = 0; elem < ch->counts[CHET_DT]; elem++) अणु
		id  = -1;
		lun = 0;
		अगर (elem < CH_DT_MAX  &&  -1 != dt_id[elem]) अणु
			id  = dt_id[elem];
			lun = dt_lun[elem];
			VPRINTK(KERN_INFO, "dt 0x%x: [insmod option] ",
				elem+ch->firsts[CHET_DT]);
		पूर्ण अन्यथा अगर (0 != ch_पढ़ो_element_status
			   (ch,elem+ch->firsts[CHET_DT],data)) अणु
			VPRINTK(KERN_INFO, "dt 0x%x: READ ELEMENT STATUS failed\n",
				elem+ch->firsts[CHET_DT]);
		पूर्ण अन्यथा अणु
			VPRINTK(KERN_INFO, "dt 0x%x: ",elem+ch->firsts[CHET_DT]);
			अगर (data[6] & 0x80) अणु
				VPRINTK(KERN_CONT, "not this SCSI bus\n");
				ch->dt[elem] = शून्य;
			पूर्ण अन्यथा अगर (0 == (data[6] & 0x30)) अणु
				VPRINTK(KERN_CONT, "ID/LUN unknown\n");
				ch->dt[elem] = शून्य;
			पूर्ण अन्यथा अणु
				id  = ch->device->id;
				lun = 0;
				अगर (data[6] & 0x20) id  = data[7];
				अगर (data[6] & 0x10) lun = data[6] & 7;
			पूर्ण
		पूर्ण
		अगर (-1 != id) अणु
			VPRINTK(KERN_CONT, "ID %i, LUN %i, ",id,lun);
			ch->dt[elem] =
				scsi_device_lookup(ch->device->host,
						   ch->device->channel,
						   id,lun);
			अगर (!ch->dt[elem]) अणु
				/* should not happen */
				VPRINTK(KERN_CONT, "Huh? device not found!\n");
			पूर्ण अन्यथा अणु
				VPRINTK(KERN_CONT, "name: %8.8s %16.16s %4.4s\n",
					ch->dt[elem]->venकरोr,
					ch->dt[elem]->model,
					ch->dt[elem]->rev);
			पूर्ण
		पूर्ण
	पूर्ण
	ch->voltags = 1;
	kमुक्त(buffer);

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक
ch_position(scsi_changer *ch, u_पूर्णांक trans, u_पूर्णांक elem, पूर्णांक rotate)
अणु
	u_अक्षर  cmd[10];

	DPRINTK("position: 0x%x\n",elem);
	अगर (0 == trans)
		trans = ch->firsts[CHET_MT];
	स_रखो(cmd,0,माप(cmd));
	cmd[0]  = POSITION_TO_ELEMENT;
	cmd[1]  = (ch->device->lun & 0x7) << 5;
	cmd[2]  = (trans >> 8) & 0xff;
	cmd[3]  =  trans       & 0xff;
	cmd[4]  = (elem  >> 8) & 0xff;
	cmd[5]  =  elem        & 0xff;
	cmd[8]  = rotate ? 1 : 0;
	वापस ch_करो_scsi(ch, cmd, 10, शून्य, 0, DMA_NONE);
पूर्ण

अटल पूर्णांक
ch_move(scsi_changer *ch, u_पूर्णांक trans, u_पूर्णांक src, u_पूर्णांक dest, पूर्णांक rotate)
अणु
	u_अक्षर  cmd[12];

	DPRINTK("move: 0x%x => 0x%x\n",src,dest);
	अगर (0 == trans)
		trans = ch->firsts[CHET_MT];
	स_रखो(cmd,0,माप(cmd));
	cmd[0]  = MOVE_MEDIUM;
	cmd[1]  = (ch->device->lun & 0x7) << 5;
	cmd[2]  = (trans >> 8) & 0xff;
	cmd[3]  =  trans       & 0xff;
	cmd[4]  = (src   >> 8) & 0xff;
	cmd[5]  =  src         & 0xff;
	cmd[6]  = (dest  >> 8) & 0xff;
	cmd[7]  =  dest        & 0xff;
	cmd[10] = rotate ? 1 : 0;
	वापस ch_करो_scsi(ch, cmd, 12, शून्य,0, DMA_NONE);
पूर्ण

अटल पूर्णांक
ch_exchange(scsi_changer *ch, u_पूर्णांक trans, u_पूर्णांक src,
	    u_पूर्णांक dest1, u_पूर्णांक dest2, पूर्णांक rotate1, पूर्णांक rotate2)
अणु
	u_अक्षर  cmd[12];

	DPRINTK("exchange: 0x%x => 0x%x => 0x%x\n",
		src,dest1,dest2);
	अगर (0 == trans)
		trans = ch->firsts[CHET_MT];
	स_रखो(cmd,0,माप(cmd));
	cmd[0]  = EXCHANGE_MEDIUM;
	cmd[1]  = (ch->device->lun & 0x7) << 5;
	cmd[2]  = (trans >> 8) & 0xff;
	cmd[3]  =  trans       & 0xff;
	cmd[4]  = (src   >> 8) & 0xff;
	cmd[5]  =  src         & 0xff;
	cmd[6]  = (dest1 >> 8) & 0xff;
	cmd[7]  =  dest1       & 0xff;
	cmd[8]  = (dest2 >> 8) & 0xff;
	cmd[9]  =  dest2       & 0xff;
	cmd[10] = (rotate1 ? 1 : 0) | (rotate2 ? 2 : 0);

	वापस ch_करो_scsi(ch, cmd, 12, शून्य, 0, DMA_NONE);
पूर्ण

अटल व्योम
ch_check_voltag(अक्षर *tag)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 32; i++) अणु
		/* restrict to ascii */
		अगर (tag[i] >= 0x7f || tag[i] < 0x20)
			tag[i] = ' ';
		/* करोn't allow search wildcards */
		अगर (tag[i] == '?' ||
		    tag[i] == '*')
			tag[i] = ' ';
	पूर्ण
पूर्ण

अटल पूर्णांक
ch_set_voltag(scsi_changer *ch, u_पूर्णांक elem,
	      पूर्णांक alternate, पूर्णांक clear, u_अक्षर *tag)
अणु
	u_अक्षर  cmd[12];
	u_अक्षर  *buffer;
	पूर्णांक result;

	buffer = kzalloc(512, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	DPRINTK("%s %s voltag: 0x%x => \"%s\"\n",
		clear     ? "clear"     : "set",
		alternate ? "alternate" : "primary",
		elem, tag);
	स_रखो(cmd,0,माप(cmd));
	cmd[0]  = SEND_VOLUME_TAG;
	cmd[1] = ((ch->device->lun & 0x7) << 5) |
		ch_elem_to_typecode(ch,elem);
	cmd[2] = (elem >> 8) & 0xff;
	cmd[3] = elem        & 0xff;
	cmd[5] = clear
		? (alternate ? 0x0d : 0x0c)
		: (alternate ? 0x0b : 0x0a);

	cmd[9] = 255;

	स_नकल(buffer,tag,32);
	ch_check_voltag(buffer);

	result = ch_करो_scsi(ch, cmd, 12, buffer, 256, DMA_TO_DEVICE);
	kमुक्त(buffer);
	वापस result;
पूर्ण

अटल पूर्णांक ch_gstatus(scsi_changer *ch, पूर्णांक type, अचिन्हित अक्षर __user *dest)
अणु
	पूर्णांक retval = 0;
	u_अक्षर data[16];
	अचिन्हित पूर्णांक i;

	mutex_lock(&ch->lock);
	क्रम (i = 0; i < ch->counts[type]; i++) अणु
		अगर (0 != ch_पढ़ो_element_status
		    (ch, ch->firsts[type]+i,data)) अणु
			retval = -EIO;
			अवरोध;
		पूर्ण
		put_user(data[2], dest+i);
		अगर (data[2] & CESTATUS_EXCEPT)
			VPRINTK(KERN_INFO, "element 0x%x: asc=0x%x, ascq=0x%x\n",
				ch->firsts[type]+i,
				(पूर्णांक)data[4],(पूर्णांक)data[5]);
		retval = ch_पढ़ो_element_status
			(ch, ch->firsts[type]+i,data);
		अगर (0 != retval)
			अवरोध;
	पूर्ण
	mutex_unlock(&ch->lock);
	वापस retval;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल व्योम ch_destroy(काष्ठा kref *ref)
अणु
	scsi_changer *ch = container_of(ref, scsi_changer, ref);

	ch->device = शून्य;
	kमुक्त(ch->dt);
	kमुक्त(ch);
पूर्ण

अटल पूर्णांक
ch_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	scsi_changer *ch = file->निजी_data;

	scsi_device_put(ch->device);
	file->निजी_data = शून्य;
	kref_put(&ch->ref, ch_destroy);
	वापस 0;
पूर्ण

अटल पूर्णांक
ch_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	scsi_changer *ch;
	पूर्णांक minor = iminor(inode);

	spin_lock(&ch_index_lock);
	ch = idr_find(&ch_index_idr, minor);

	अगर (ch == शून्य || !kref_get_unless_zero(&ch->ref)) अणु
		spin_unlock(&ch_index_lock);
		वापस -ENXIO;
	पूर्ण
	spin_unlock(&ch_index_lock);
	अगर (scsi_device_get(ch->device)) अणु
		kref_put(&ch->ref, ch_destroy);
		वापस -ENXIO;
	पूर्ण
	/* Synchronize with ch_probe() */
	mutex_lock(&ch->lock);
	file->निजी_data = ch;
	mutex_unlock(&ch->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
ch_checkrange(scsi_changer *ch, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक unit)
अणु
	अगर (type >= CH_TYPES  ||  unit >= ch->counts[type])
		वापस -1;
	वापस 0;
पूर्ण

अटल दीर्घ ch_ioctl(काष्ठा file *file,
		    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	scsi_changer *ch = file->निजी_data;
	पूर्णांक retval;
	व्योम __user *argp = (व्योम __user *)arg;

	retval = scsi_ioctl_block_when_processing_errors(ch->device, cmd,
			file->f_flags & O_NDELAY);
	अगर (retval)
		वापस retval;

	चयन (cmd) अणु
	हाल CHIOGPARAMS:
	अणु
		काष्ठा changer_params params;

		params.cp_curpicker = 0;
		params.cp_npickers  = ch->counts[CHET_MT];
		params.cp_nslots    = ch->counts[CHET_ST];
		params.cp_nportals  = ch->counts[CHET_IE];
		params.cp_ndrives   = ch->counts[CHET_DT];

		अगर (copy_to_user(argp, &params, माप(params)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल CHIOGVPARAMS:
	अणु
		काष्ठा changer_venकरोr_params vparams;

		स_रखो(&vparams,0,माप(vparams));
		अगर (ch->counts[CHET_V1]) अणु
			vparams.cvp_n1  = ch->counts[CHET_V1];
			म_नकलन(vparams.cvp_label1,venकरोr_labels[0],16);
		पूर्ण
		अगर (ch->counts[CHET_V2]) अणु
			vparams.cvp_n2  = ch->counts[CHET_V2];
			म_नकलन(vparams.cvp_label2,venकरोr_labels[1],16);
		पूर्ण
		अगर (ch->counts[CHET_V3]) अणु
			vparams.cvp_n3  = ch->counts[CHET_V3];
			म_नकलन(vparams.cvp_label3,venकरोr_labels[2],16);
		पूर्ण
		अगर (ch->counts[CHET_V4]) अणु
			vparams.cvp_n4  = ch->counts[CHET_V4];
			म_नकलन(vparams.cvp_label4,venकरोr_labels[3],16);
		पूर्ण
		अगर (copy_to_user(argp, &vparams, माप(vparams)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	हाल CHIOPOSITION:
	अणु
		काष्ठा changer_position pos;

		अगर (copy_from_user(&pos, argp, माप (pos)))
			वापस -EFAULT;

		अगर (0 != ch_checkrange(ch, pos.cp_type, pos.cp_unit)) अणु
			DPRINTK("CHIOPOSITION: invalid parameter\n");
			वापस -EBADSLT;
		पूर्ण
		mutex_lock(&ch->lock);
		retval = ch_position(ch,0,
				     ch->firsts[pos.cp_type] + pos.cp_unit,
				     pos.cp_flags & CP_INVERT);
		mutex_unlock(&ch->lock);
		वापस retval;
	पूर्ण

	हाल CHIOMOVE:
	अणु
		काष्ठा changer_move mv;

		अगर (copy_from_user(&mv, argp, माप (mv)))
			वापस -EFAULT;

		अगर (0 != ch_checkrange(ch, mv.cm_fromtype, mv.cm_fromunit) ||
		    0 != ch_checkrange(ch, mv.cm_totype,   mv.cm_tounit  )) अणु
			DPRINTK("CHIOMOVE: invalid parameter\n");
			वापस -EBADSLT;
		पूर्ण

		mutex_lock(&ch->lock);
		retval = ch_move(ch,0,
				 ch->firsts[mv.cm_fromtype] + mv.cm_fromunit,
				 ch->firsts[mv.cm_totype]   + mv.cm_tounit,
				 mv.cm_flags & CM_INVERT);
		mutex_unlock(&ch->lock);
		वापस retval;
	पूर्ण

	हाल CHIOEXCHANGE:
	अणु
		काष्ठा changer_exchange mv;

		अगर (copy_from_user(&mv, argp, माप (mv)))
			वापस -EFAULT;

		अगर (0 != ch_checkrange(ch, mv.ce_srctype,  mv.ce_srcunit ) ||
		    0 != ch_checkrange(ch, mv.ce_fdsttype, mv.ce_fdstunit) ||
		    0 != ch_checkrange(ch, mv.ce_sdsttype, mv.ce_sdstunit)) अणु
			DPRINTK("CHIOEXCHANGE: invalid parameter\n");
			वापस -EBADSLT;
		पूर्ण

		mutex_lock(&ch->lock);
		retval = ch_exchange
			(ch,0,
			 ch->firsts[mv.ce_srctype]  + mv.ce_srcunit,
			 ch->firsts[mv.ce_fdsttype] + mv.ce_fdstunit,
			 ch->firsts[mv.ce_sdsttype] + mv.ce_sdstunit,
			 mv.ce_flags & CE_INVERT1, mv.ce_flags & CE_INVERT2);
		mutex_unlock(&ch->lock);
		वापस retval;
	पूर्ण

	हाल CHIOGSTATUS:
	अणु
		काष्ठा changer_element_status ces;

		अगर (copy_from_user(&ces, argp, माप (ces)))
			वापस -EFAULT;
		अगर (ces.ces_type < 0 || ces.ces_type >= CH_TYPES)
			वापस -EINVAL;

		वापस ch_gstatus(ch, ces.ces_type, ces.ces_data);
	पूर्ण

	हाल CHIOGELEM:
	अणु
		काष्ठा changer_get_element cge;
		u_अक्षर ch_cmd[12];
		u_अक्षर *buffer;
		अचिन्हित पूर्णांक elem;
		पूर्णांक     result,i;

		अगर (copy_from_user(&cge, argp, माप (cge)))
			वापस -EFAULT;

		अगर (0 != ch_checkrange(ch, cge.cge_type, cge.cge_unit))
			वापस -EINVAL;
		elem = ch->firsts[cge.cge_type] + cge.cge_unit;

		buffer = kदो_स्मृति(512, GFP_KERNEL | GFP_DMA);
		अगर (!buffer)
			वापस -ENOMEM;
		mutex_lock(&ch->lock);

	voltag_retry:
		स_रखो(ch_cmd, 0, माप(ch_cmd));
		ch_cmd[0] = READ_ELEMENT_STATUS;
		ch_cmd[1] = ((ch->device->lun & 0x7) << 5) |
			(ch->voltags ? 0x10 : 0) |
			ch_elem_to_typecode(ch,elem);
		ch_cmd[2] = (elem >> 8) & 0xff;
		ch_cmd[3] = elem        & 0xff;
		ch_cmd[5] = 1;
		ch_cmd[9] = 255;

		result = ch_करो_scsi(ch, ch_cmd, 12,
				    buffer, 256, DMA_FROM_DEVICE);
		अगर (!result) अणु
			cge.cge_status = buffer[18];
			cge.cge_flags = 0;
			अगर (buffer[18] & CESTATUS_EXCEPT) अणु
				cge.cge_त्रुटि_सं = EIO;
			पूर्ण
			अगर (buffer[25] & 0x80) अणु
				cge.cge_flags |= CGE_SRC;
				अगर (buffer[25] & 0x40)
					cge.cge_flags |= CGE_INVERT;
				elem = (buffer[26]<<8) | buffer[27];
				क्रम (i = 0; i < 4; i++) अणु
					अगर (elem >= ch->firsts[i] &&
					    elem <  ch->firsts[i] + ch->counts[i]) अणु
						cge.cge_srctype = i;
						cge.cge_srcunit = elem-ch->firsts[i];
					पूर्ण
				पूर्ण
			पूर्ण
			अगर ((buffer[22] & 0x30) == 0x30) अणु
				cge.cge_flags |= CGE_IDLUN;
				cge.cge_id  = buffer[23];
				cge.cge_lun = buffer[22] & 7;
			पूर्ण
			अगर (buffer[9] & 0x80) अणु
				cge.cge_flags |= CGE_PVOLTAG;
				स_नकल(cge.cge_pvoltag,buffer+28,36);
			पूर्ण
			अगर (buffer[9] & 0x40) अणु
				cge.cge_flags |= CGE_AVOLTAG;
				स_नकल(cge.cge_avoltag,buffer+64,36);
			पूर्ण
		पूर्ण अन्यथा अगर (ch->voltags) अणु
			ch->voltags = 0;
			VPRINTK(KERN_INFO, "device has no volume tag support\n");
			जाओ voltag_retry;
		पूर्ण
		kमुक्त(buffer);
		mutex_unlock(&ch->lock);

		अगर (copy_to_user(argp, &cge, माप (cge)))
			वापस -EFAULT;
		वापस result;
	पूर्ण

	हाल CHIOINITELEM:
	अणु
		mutex_lock(&ch->lock);
		retval = ch_init_elem(ch);
		mutex_unlock(&ch->lock);
		वापस retval;
	पूर्ण

	हाल CHIOSVOLTAG:
	अणु
		काष्ठा changer_set_voltag csv;
		पूर्णांक elem;

		अगर (copy_from_user(&csv, argp, माप(csv)))
			वापस -EFAULT;

		अगर (0 != ch_checkrange(ch, csv.csv_type, csv.csv_unit)) अणु
			DPRINTK("CHIOSVOLTAG: invalid parameter\n");
			वापस -EBADSLT;
		पूर्ण
		elem = ch->firsts[csv.csv_type] + csv.csv_unit;
		mutex_lock(&ch->lock);
		retval = ch_set_voltag(ch, elem,
				       csv.csv_flags & CSV_AVOLTAG,
				       csv.csv_flags & CSV_CLEARTAG,
				       csv.csv_voltag);
		mutex_unlock(&ch->lock);
		वापस retval;
	पूर्ण

	शेष:
		वापस scsi_ioctl(ch->device, cmd, argp);

	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT

काष्ठा changer_element_status32 अणु
	पूर्णांक		ces_type;
	compat_uptr_t	ces_data;
पूर्ण;
#घोषणा CHIOGSTATUS32  _IOW('c', 8,काष्ठा changer_element_status32)

अटल दीर्घ ch_ioctl_compat(काष्ठा file * file,
			    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	scsi_changer *ch = file->निजी_data;
	पूर्णांक retval = scsi_ioctl_block_when_processing_errors(ch->device, cmd,
							file->f_flags & O_NDELAY);
	अगर (retval)
		वापस retval;

	चयन (cmd) अणु
	हाल CHIOGPARAMS:
	हाल CHIOGVPARAMS:
	हाल CHIOPOSITION:
	हाल CHIOMOVE:
	हाल CHIOEXCHANGE:
	हाल CHIOGELEM:
	हाल CHIOINITELEM:
	हाल CHIOSVOLTAG:
		/* compatible */
		वापस ch_ioctl(file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
	हाल CHIOGSTATUS32:
	अणु
		काष्ठा changer_element_status32 ces32;
		अचिन्हित अक्षर __user *data;

		अगर (copy_from_user(&ces32, (व्योम __user *)arg, माप (ces32)))
			वापस -EFAULT;
		अगर (ces32.ces_type < 0 || ces32.ces_type >= CH_TYPES)
			वापस -EINVAL;

		data = compat_ptr(ces32.ces_data);
		वापस ch_gstatus(ch, ces32.ces_type, data);
	पूर्ण
	शेष:
		वापस scsi_compat_ioctl(ch->device, cmd, compat_ptr(arg));

	पूर्ण
पूर्ण
#पूर्ण_अगर

/* ------------------------------------------------------------------------ */

अटल पूर्णांक ch_probe(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sd = to_scsi_device(dev);
	काष्ठा device *class_dev;
	पूर्णांक ret;
	scsi_changer *ch;

	अगर (sd->type != TYPE_MEDIUM_CHANGER)
		वापस -ENODEV;

	ch = kzalloc(माप(*ch), GFP_KERNEL);
	अगर (शून्य == ch)
		वापस -ENOMEM;

	idr_preload(GFP_KERNEL);
	spin_lock(&ch_index_lock);
	ret = idr_alloc(&ch_index_idr, ch, 0, CH_MAX_DEVS + 1, GFP_NOWAIT);
	spin_unlock(&ch_index_lock);
	idr_preload_end();

	अगर (ret < 0) अणु
		अगर (ret == -ENOSPC)
			ret = -ENODEV;
		जाओ मुक्त_ch;
	पूर्ण

	ch->minor = ret;
	प्र_लिखो(ch->name,"ch%d",ch->minor);
	ret = scsi_device_get(sd);
	अगर (ret) अणु
		sdev_prपूर्णांकk(KERN_WARNING, sd, "ch%d: failed to get device\n",
			    ch->minor);
		जाओ हटाओ_idr;
	पूर्ण

	mutex_init(&ch->lock);
	kref_init(&ch->ref);
	ch->device = sd;
	class_dev = device_create(ch_sysfs_class, dev,
				  MKDEV(SCSI_CHANGER_MAJOR, ch->minor), ch,
				  "s%s", ch->name);
	अगर (IS_ERR(class_dev)) अणु
		sdev_prपूर्णांकk(KERN_WARNING, sd, "ch%d: device_create failed\n",
			    ch->minor);
		ret = PTR_ERR(class_dev);
		जाओ put_device;
	पूर्ण

	mutex_lock(&ch->lock);
	ret = ch_पढ़ोconfig(ch);
	अगर (ret) अणु
		mutex_unlock(&ch->lock);
		जाओ destroy_dev;
	पूर्ण
	अगर (init)
		ch_init_elem(ch);

	mutex_unlock(&ch->lock);
	dev_set_drvdata(dev, ch);
	sdev_prपूर्णांकk(KERN_INFO, sd, "Attached scsi changer %s\n", ch->name);

	वापस 0;
destroy_dev:
	device_destroy(ch_sysfs_class, MKDEV(SCSI_CHANGER_MAJOR, ch->minor));
put_device:
	scsi_device_put(sd);
हटाओ_idr:
	idr_हटाओ(&ch_index_idr, ch->minor);
मुक्त_ch:
	kमुक्त(ch);
	वापस ret;
पूर्ण

अटल पूर्णांक ch_हटाओ(काष्ठा device *dev)
अणु
	scsi_changer *ch = dev_get_drvdata(dev);

	spin_lock(&ch_index_lock);
	idr_हटाओ(&ch_index_idr, ch->minor);
	dev_set_drvdata(dev, शून्य);
	spin_unlock(&ch_index_lock);

	device_destroy(ch_sysfs_class, MKDEV(SCSI_CHANGER_MAJOR,ch->minor));
	scsi_device_put(ch->device);
	kref_put(&ch->ref, ch_destroy);
	वापस 0;
पूर्ण

अटल काष्ठा scsi_driver ch_ढाँचा = अणु
	.gendrv     	= अणु
		.name	= "ch",
		.owner	= THIS_MODULE,
		.probe  = ch_probe,
		.हटाओ = ch_हटाओ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा file_operations changer_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= ch_खोलो,
	.release	= ch_release,
	.unlocked_ioctl	= ch_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= ch_ioctl_compat,
#पूर्ण_अगर
	.llseek		= noop_llseek,
पूर्ण;

अटल पूर्णांक __init init_ch_module(व्योम)
अणु
	पूर्णांक rc;

	prपूर्णांकk(KERN_INFO "SCSI Media Changer driver v" VERSION " \n");
        ch_sysfs_class = class_create(THIS_MODULE, "scsi_changer");
        अगर (IS_ERR(ch_sysfs_class)) अणु
		rc = PTR_ERR(ch_sysfs_class);
		वापस rc;
        पूर्ण
	rc = रेजिस्टर_chrdev(SCSI_CHANGER_MAJOR,"ch",&changer_fops);
	अगर (rc < 0) अणु
		prपूर्णांकk("Unable to get major %d for SCSI-Changer\n",
		       SCSI_CHANGER_MAJOR);
		जाओ fail1;
	पूर्ण
	rc = scsi_रेजिस्टर_driver(&ch_ढाँचा.gendrv);
	अगर (rc < 0)
		जाओ fail2;
	वापस 0;

 fail2:
	unरेजिस्टर_chrdev(SCSI_CHANGER_MAJOR, "ch");
 fail1:
	class_destroy(ch_sysfs_class);
	वापस rc;
पूर्ण

अटल व्योम __निकास निकास_ch_module(व्योम)
अणु
	scsi_unरेजिस्टर_driver(&ch_ढाँचा.gendrv);
	unरेजिस्टर_chrdev(SCSI_CHANGER_MAJOR, "ch");
	class_destroy(ch_sysfs_class);
	idr_destroy(&ch_index_idr);
पूर्ण

module_init(init_ch_module);
module_निकास(निकास_ch_module);
