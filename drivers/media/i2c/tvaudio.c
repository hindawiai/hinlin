<शैली गुरु>
/*
 * Driver क्रम simple i2c audio chips.
 *
 * Copyright (c) 2000 Gerd Knorr
 * based on code by:
 *   Eric Sandeen (eric_sandeen@bigfoot.com)
 *   Steve VanDeBogart (vandebo@uclink.berkeley.edu)
 *   Greg Alexander (galexand@acm.org)
 *
 * For the TDA9875 part:
 * Copyright (c) 2000 Guillaume Delvit based on Gerd Knorr source
 * and Eric Sandeen
 *
 * Copyright(c) 2005-2008 Mauro Carvalho Chehab
 *	- Some cleanups, code fixes, etc
 *	- Convert it to V4L2 API
 *
 * This code is placed under the terms of the GNU General Public License
 *
 * OPTIONS:
 *   debug - set to 1 अगर you'd like to see debug messages
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>

#समावेश <media/i2c/tvaudपन.स>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

/* ---------------------------------------------------------------------- */
/* insmod args                                                            */

अटल पूर्णांक debug;	/* insmod parameter */
module_param(debug, पूर्णांक, 0644);

MODULE_DESCRIPTION("device driver for various i2c TV sound decoder / audiomux chips");
MODULE_AUTHOR("Eric Sandeen, Steve VanDeBogart, Greg Alexander, Gerd Knorr");
MODULE_LICENSE("GPL");

#घोषणा UNSET    (-1U)

/* ---------------------------------------------------------------------- */
/* our काष्ठाs                                                            */

#घोषणा MAXREGS 256

काष्ठा CHIPSTATE;
प्रकार पूर्णांक  (*getvalue)(पूर्णांक);
प्रकार पूर्णांक  (*checkit)(काष्ठा CHIPSTATE*);
प्रकार पूर्णांक  (*initialize)(काष्ठा CHIPSTATE*);
प्रकार पूर्णांक  (*getrxsubchans)(काष्ठा CHIPSTATE *);
प्रकार व्योम (*setaudmode)(काष्ठा CHIPSTATE*, पूर्णांक mode);

/* i2c command */
प्रकार काष्ठा AUDIOCMD अणु
	पूर्णांक             count;             /* # of bytes to send */
	अचिन्हित अक्षर   bytes[MAXREGS+1];  /* addr, data, data, ... */
पूर्ण audiocmd;

/* chip description */
काष्ठा CHIPDESC अणु
	अक्षर       *name;             /* chip name         */
	पूर्णांक        addr_lo, addr_hi;  /* i2c address range */
	पूर्णांक        रेजिस्टरs;         /* # of रेजिस्टरs    */

	पूर्णांक        *insmoकरोpt;
	checkit    checkit;
	initialize initialize;
	पूर्णांक        flags;
#घोषणा CHIP_HAS_VOLUME      1
#घोषणा CHIP_HAS_BASSTREBLE  2
#घोषणा CHIP_HAS_INPUTSEL    4
#घोषणा CHIP_NEED_CHECKMODE  8

	/* various i2c command sequences */
	audiocmd   init;

	/* which रेजिस्टर has which value */
	पूर्णांक    leftreg, rightreg, treblereg, bassreg;

	/* initialize with (शेषs to 65535/32768/32768 */
	पूर्णांक    volinit, trebleinit, bassinit;

	/* functions to convert the values (v4l -> chip) */
	getvalue volfunc, treblefunc, bassfunc;

	/* get/set mode */
	getrxsubchans	getrxsubchans;
	setaudmode	setaudmode;

	/* input चयन रेजिस्टर + values क्रम v4l inमाला_दो */
	पूर्णांक  inputreg;
	पूर्णांक  inpuपंचांगap[4];
	पूर्णांक  inpuपंचांगute;
	पूर्णांक  inpuपंचांगask;
पूर्ण;

/* current state of the chip */
काष्ठा CHIPSTATE अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा अणु
		/* volume/balance cluster */
		काष्ठा v4l2_ctrl *volume;
		काष्ठा v4l2_ctrl *balance;
	पूर्ण;

	/* chip-specअगरic description - should poपूर्णांक to
	   an entry at CHIPDESC table */
	काष्ठा CHIPDESC *desc;

	/* shaकरोw रेजिस्टर set */
	audiocmd   shaकरोw;

	/* current settings */
	u16 muted;
	पूर्णांक prevmode;
	पूर्णांक radio;
	पूर्णांक input;

	/* thपढ़ो */
	काष्ठा task_काष्ठा   *thपढ़ो;
	काष्ठा समयr_list    wt;
	पूर्णांक		     audmode;
पूर्ण;

अटल अंतरभूत काष्ठा CHIPSTATE *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा CHIPSTATE, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा CHIPSTATE, hdl)->sd;
पूर्ण


/* ---------------------------------------------------------------------- */
/* i2c I/O functions                                                      */

अटल पूर्णांक chip_ग_लिखो(काष्ठा CHIPSTATE *chip, पूर्णांक subaddr, पूर्णांक val)
अणु
	काष्ठा v4l2_subdev *sd = &chip->sd;
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	अचिन्हित अक्षर buffer[2];
	पूर्णांक rc;

	अगर (subaddr < 0) अणु
		v4l2_dbg(1, debug, sd, "chip_write: 0x%x\n", val);
		chip->shaकरोw.bytes[1] = val;
		buffer[0] = val;
		rc = i2c_master_send(c, buffer, 1);
		अगर (rc != 1) अणु
			v4l2_warn(sd, "I/O error (write 0x%x)\n", val);
			अगर (rc < 0)
				वापस rc;
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (subaddr + 1 >= ARRAY_SIZE(chip->shaकरोw.bytes)) अणु
			v4l2_info(sd,
				"Tried to access a non-existent register: %d\n",
				subaddr);
			वापस -EINVAL;
		पूर्ण

		v4l2_dbg(1, debug, sd, "chip_write: reg%d=0x%x\n",
			subaddr, val);
		chip->shaकरोw.bytes[subaddr+1] = val;
		buffer[0] = subaddr;
		buffer[1] = val;
		rc = i2c_master_send(c, buffer, 2);
		अगर (rc != 2) अणु
			v4l2_warn(sd, "I/O error (write reg%d=0x%x)\n",
				subaddr, val);
			अगर (rc < 0)
				वापस rc;
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक chip_ग_लिखो_masked(काष्ठा CHIPSTATE *chip,
			     पूर्णांक subaddr, पूर्णांक val, पूर्णांक mask)
अणु
	काष्ठा v4l2_subdev *sd = &chip->sd;

	अगर (mask != 0) अणु
		अगर (subaddr < 0) अणु
			val = (chip->shaकरोw.bytes[1] & ~mask) | (val & mask);
		पूर्ण अन्यथा अणु
			अगर (subaddr + 1 >= ARRAY_SIZE(chip->shaकरोw.bytes)) अणु
				v4l2_info(sd,
					"Tried to access a non-existent register: %d\n",
					subaddr);
				वापस -EINVAL;
			पूर्ण

			val = (chip->shaकरोw.bytes[subaddr+1] & ~mask) | (val & mask);
		पूर्ण
	पूर्ण
	वापस chip_ग_लिखो(chip, subaddr, val);
पूर्ण

अटल पूर्णांक chip_पढ़ो(काष्ठा CHIPSTATE *chip)
अणु
	काष्ठा v4l2_subdev *sd = &chip->sd;
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	अचिन्हित अक्षर buffer;
	पूर्णांक rc;

	rc = i2c_master_recv(c, &buffer, 1);
	अगर (rc != 1) अणु
		v4l2_warn(sd, "I/O error (read)\n");
		अगर (rc < 0)
			वापस rc;
		वापस -EIO;
	पूर्ण
	v4l2_dbg(1, debug, sd, "chip_read: 0x%x\n", buffer);
	वापस buffer;
पूर्ण

अटल पूर्णांक chip_पढ़ो2(काष्ठा CHIPSTATE *chip, पूर्णांक subaddr)
अणु
	काष्ठा v4l2_subdev *sd = &chip->sd;
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	पूर्णांक rc;
	अचिन्हित अक्षर ग_लिखो[1];
	अचिन्हित अक्षर पढ़ो[1];
	काष्ठा i2c_msg msgs[2] = अणु
		अणु
			.addr = c->addr,
			.len = 1,
			.buf = ग_लिखो
		पूर्ण,
		अणु
			.addr = c->addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = पढ़ो
		पूर्ण
	पूर्ण;

	ग_लिखो[0] = subaddr;

	rc = i2c_transfer(c->adapter, msgs, 2);
	अगर (rc != 2) अणु
		v4l2_warn(sd, "I/O error (read2)\n");
		अगर (rc < 0)
			वापस rc;
		वापस -EIO;
	पूर्ण
	v4l2_dbg(1, debug, sd, "chip_read2: reg%d=0x%x\n",
		subaddr, पढ़ो[0]);
	वापस पढ़ो[0];
पूर्ण

अटल पूर्णांक chip_cmd(काष्ठा CHIPSTATE *chip, अक्षर *name, audiocmd *cmd)
अणु
	काष्ठा v4l2_subdev *sd = &chip->sd;
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	पूर्णांक i, rc;

	अगर (0 == cmd->count)
		वापस 0;

	अगर (cmd->count + cmd->bytes[0] - 1 >= ARRAY_SIZE(chip->shaकरोw.bytes)) अणु
		v4l2_info(sd,
			 "Tried to access a non-existent register range: %d to %d\n",
			 cmd->bytes[0] + 1, cmd->bytes[0] + cmd->count - 1);
		वापस -EINVAL;
	पूर्ण

	/* FIXME: it seems that the shaकरोw bytes are wrong below !*/

	/* update our shaकरोw रेजिस्टर set; prपूर्णांक bytes अगर (debug > 0) */
	v4l2_dbg(1, debug, sd, "chip_cmd(%s): reg=%d, data:",
		name, cmd->bytes[0]);
	क्रम (i = 1; i < cmd->count; i++) अणु
		अगर (debug)
			prपूर्णांकk(KERN_CONT " 0x%x", cmd->bytes[i]);
		chip->shaकरोw.bytes[i+cmd->bytes[0]] = cmd->bytes[i];
	पूर्ण
	अगर (debug)
		prपूर्णांकk(KERN_CONT "\n");

	/* send data to the chip */
	rc = i2c_master_send(c, cmd->bytes, cmd->count);
	अगर (rc != cmd->count) अणु
		v4l2_warn(sd, "I/O error (%s)\n", name);
		अगर (rc < 0)
			वापस rc;
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------- */
/* kernel thपढ़ो क्रम करोing i2c stuff asyncronly
 *   right now it is used only to check the audio mode (mono/stereo/whatever)
 *   some समय after चयनing to another TV channel, then turn on stereo
 *   अगर available, ...
 */

अटल व्योम chip_thपढ़ो_wake(काष्ठा समयr_list *t)
अणु
	काष्ठा CHIPSTATE *chip = from_समयr(chip, t, wt);
	wake_up_process(chip->thपढ़ो);
पूर्ण

अटल पूर्णांक chip_thपढ़ो(व्योम *data)
अणु
	काष्ठा CHIPSTATE *chip = data;
	काष्ठा CHIPDESC  *desc = chip->desc;
	काष्ठा v4l2_subdev *sd = &chip->sd;
	पूर्णांक mode, selected;

	v4l2_dbg(1, debug, sd, "thread started\n");
	set_मुक्तzable();
	क्रम (;;) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (!kthपढ़ो_should_stop())
			schedule();
		set_current_state(TASK_RUNNING);
		try_to_मुक्तze();
		अगर (kthपढ़ो_should_stop())
			अवरोध;
		v4l2_dbg(1, debug, sd, "thread wakeup\n");

		/* करोn't करो anything क्रम radio */
		अगर (chip->radio)
			जारी;

		/* have a look what's going on */
		mode = desc->getrxsubchans(chip);
		अगर (mode == chip->prevmode)
			जारी;

		/* chip detected a new audio mode - set it */
		v4l2_dbg(1, debug, sd, "thread checkmode\n");

		chip->prevmode = mode;

		selected = V4L2_TUNER_MODE_MONO;
		चयन (chip->audmode) अणु
		हाल V4L2_TUNER_MODE_MONO:
			अगर (mode & V4L2_TUNER_SUB_LANG1)
				selected = V4L2_TUNER_MODE_LANG1;
			अवरोध;
		हाल V4L2_TUNER_MODE_STEREO:
		हाल V4L2_TUNER_MODE_LANG1:
			अगर (mode & V4L2_TUNER_SUB_LANG1)
				selected = V4L2_TUNER_MODE_LANG1;
			अन्यथा अगर (mode & V4L2_TUNER_SUB_STEREO)
				selected = V4L2_TUNER_MODE_STEREO;
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG2:
			अगर (mode & V4L2_TUNER_SUB_LANG2)
				selected = V4L2_TUNER_MODE_LANG2;
			अन्यथा अगर (mode & V4L2_TUNER_SUB_STEREO)
				selected = V4L2_TUNER_MODE_STEREO;
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG1_LANG2:
			अगर (mode & V4L2_TUNER_SUB_LANG2)
				selected = V4L2_TUNER_MODE_LANG1_LANG2;
			अन्यथा अगर (mode & V4L2_TUNER_SUB_STEREO)
				selected = V4L2_TUNER_MODE_STEREO;
		पूर्ण
		desc->setaudmode(chip, selected);

		/* schedule next check */
		mod_समयr(&chip->wt, jअगरfies+msecs_to_jअगरfies(2000));
	पूर्ण

	v4l2_dbg(1, debug, sd, "thread exiting\n");
	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------- */
/* audio chip descriptions - defines+functions क्रम tda9840                */

#घोषणा TDA9840_SW         0x00
#घोषणा TDA9840_LVADJ      0x02
#घोषणा TDA9840_STADJ      0x03
#घोषणा TDA9840_TEST       0x04

#घोषणा TDA9840_MONO       0x10
#घोषणा TDA9840_STEREO     0x2a
#घोषणा TDA9840_DUALA      0x12
#घोषणा TDA9840_DUALB      0x1e
#घोषणा TDA9840_DUALAB     0x1a
#घोषणा TDA9840_DUALBA     0x16
#घोषणा TDA9840_EXTERNAL   0x7a

#घोषणा TDA9840_DS_DUAL    0x20 /* Dual sound identअगरied          */
#घोषणा TDA9840_ST_STEREO  0x40 /* Stereo sound identअगरied        */
#घोषणा TDA9840_PONRES     0x80 /* Power-on reset detected अगर = 1 */

#घोषणा TDA9840_TEST_INT1SN 0x1 /* Integration समय 0.5s when set */
#घोषणा TDA9840_TEST_INTFU 0x02 /* Disables पूर्णांकegrator function */

अटल पूर्णांक tda9840_getrxsubchans(काष्ठा CHIPSTATE *chip)
अणु
	काष्ठा v4l2_subdev *sd = &chip->sd;
	पूर्णांक val, mode;

	mode = V4L2_TUNER_SUB_MONO;

	val = chip_पढ़ो(chip);
	अगर (val < 0)
		वापस mode;

	अगर (val & TDA9840_DS_DUAL)
		mode |= V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
	अगर (val & TDA9840_ST_STEREO)
		mode = V4L2_TUNER_SUB_STEREO;

	v4l2_dbg(1, debug, sd,
		"tda9840_getrxsubchans(): raw chip read: %d, return: %d\n",
		val, mode);
	वापस mode;
पूर्ण

अटल व्योम tda9840_setaudmode(काष्ठा CHIPSTATE *chip, पूर्णांक mode)
अणु
	पूर्णांक update = 1;
	पूर्णांक t = chip->shaकरोw.bytes[TDA9840_SW + 1] & ~0x7e;

	चयन (mode) अणु
	हाल V4L2_TUNER_MODE_MONO:
		t |= TDA9840_MONO;
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
		t |= TDA9840_STEREO;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1:
		t |= TDA9840_DUALA;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG2:
		t |= TDA9840_DUALB;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1_LANG2:
		t |= TDA9840_DUALAB;
		अवरोध;
	शेष:
		update = 0;
	पूर्ण

	अगर (update)
		chip_ग_लिखो(chip, TDA9840_SW, t);
पूर्ण

अटल पूर्णांक tda9840_checkit(काष्ठा CHIPSTATE *chip)
अणु
	पूर्णांक rc;

	rc = chip_पढ़ो(chip);
	अगर (rc < 0)
		वापस 0;


	/* lower 5 bits should be 0 */
	वापस ((rc & 0x1f) == 0) ? 1 : 0;
पूर्ण

/* ---------------------------------------------------------------------- */
/* audio chip descriptions - defines+functions क्रम tda985x                */

/* subaddresses क्रम TDA9855 */
#घोषणा TDA9855_VR	0x00 /* Volume, right */
#घोषणा TDA9855_VL	0x01 /* Volume, left */
#घोषणा TDA9855_BA	0x02 /* Bass */
#घोषणा TDA9855_TR	0x03 /* Treble */
#घोषणा TDA9855_SW	0x04 /* Subwoofer - not connected on DTV2000 */

/* subaddresses क्रम TDA9850 */
#घोषणा TDA9850_C4	0x04 /* Control 1 क्रम TDA9850 */

/* subaddesses क्रम both chips */
#घोषणा TDA985x_C5	0x05 /* Control 2 क्रम TDA9850, Control 1 क्रम TDA9855 */
#घोषणा TDA985x_C6	0x06 /* Control 3 क्रम TDA9850, Control 2 क्रम TDA9855 */
#घोषणा TDA985x_C7	0x07 /* Control 4 क्रम TDA9850, Control 3 क्रम TDA9855 */
#घोषणा TDA985x_A1	0x08 /* Alignment 1 क्रम both chips */
#घोषणा TDA985x_A2	0x09 /* Alignment 2 क्रम both chips */
#घोषणा TDA985x_A3	0x0a /* Alignment 3 क्रम both chips */

/* Masks क्रम bits in TDA9855 subaddresses */
/* 0x00 - VR in TDA9855 */
/* 0x01 - VL in TDA9855 */
/* lower 7 bits control gain from -71dB (0x28) to 16dB (0x7f)
 * in 1dB steps - mute is 0x27 */


/* 0x02 - BA in TDA9855 */
/* lower 5 bits control bass gain from -12dB (0x06) to 16.5dB (0x19)
 * in .5dB steps - 0 is 0x0E */


/* 0x03 - TR in TDA9855 */
/* 4 bits << 1 control treble gain from -12dB (0x3) to 12dB (0xb)
 * in 3dB steps - 0 is 0x7 */

/* Masks क्रम bits in both chips' subaddresses */
/* 0x04 - SW in TDA9855, C4/Control 1 in TDA9850 */
/* Unique to TDA9855: */
/* 4 bits << 2 control subwoofer/surround gain from -14db (0x1) to 14db (0xf)
 * in 3dB steps - mute is 0x0 */

/* Unique to TDA9850: */
/* lower 4 bits control stereo noise threshold, over which stereo turns off
 * set to values of 0x00 through 0x0f क्रम Ster1 through Ster16 */


/* 0x05 - C5 - Control 1 in TDA9855 , Control 2 in TDA9850*/
/* Unique to TDA9855: */
#घोषणा TDA9855_MUTE	1<<7 /* GMU, Mute at outमाला_दो */
#घोषणा TDA9855_AVL	1<<6 /* AVL, Automatic Volume Level */
#घोषणा TDA9855_LOUD	1<<5 /* Loudness, 1==off */
#घोषणा TDA9855_SUR	1<<3 /* Surround / Subwoofer 1==.5(L-R) 0==.5(L+R) */
			     /* Bits 0 to 3 select various combinations
			      * of line in and line out, only the
			      * पूर्णांकeresting ones are defined */
#घोषणा TDA9855_EXT	1<<2 /* Selects inमाला_दो LIR and LIL.  Pins 41 & 12 */
#घोषणा TDA9855_INT	0    /* Selects inमाला_दो LOR and LOL.  (पूर्णांकernal) */

/* Unique to TDA9850:  */
/* lower 4 bits control SAP noise threshold, over which SAP turns off
 * set to values of 0x00 through 0x0f क्रम SAP1 through SAP16 */


/* 0x06 - C6 - Control 2 in TDA9855, Control 3 in TDA9850 */
/* Common to TDA9855 and TDA9850: */
#घोषणा TDA985x_SAP	3<<6 /* Selects SAP output, mute अगर not received */
#घोषणा TDA985x_MONOSAP	2<<6 /* Selects Mono on left, SAP on right */
#घोषणा TDA985x_STEREO	1<<6 /* Selects Stereo output, mono अगर not received */
#घोषणा TDA985x_MONO	0    /* Forces Mono output */
#घोषणा TDA985x_LMU	1<<3 /* Mute (LOR/LOL क्रम 9855, OUTL/OUTR क्रम 9850) */

/* Unique to TDA9855: */
#घोषणा TDA9855_TZCM	1<<5 /* If set, करोn't mute till zero crossing */
#घोषणा TDA9855_VZCM	1<<4 /* If set, करोn't change volume till zero crossing*/
#घोषणा TDA9855_LINEAR	0    /* Linear Stereo */
#घोषणा TDA9855_PSEUDO	1    /* Pseuकरो Stereo */
#घोषणा TDA9855_SPAT_30	2    /* Spatial Stereo, 30% anti-phase crosstalk */
#घोषणा TDA9855_SPAT_50	3    /* Spatial Stereo, 52% anti-phase crosstalk */
#घोषणा TDA9855_E_MONO	7    /* Forced mono - mono select अन्यथाware, so useless*/

/* 0x07 - C7 - Control 3 in TDA9855, Control 4 in TDA9850 */
/* Common to both TDA9855 and TDA9850: */
/* lower 4 bits control input gain from -3.5dB (0x0) to 4dB (0xF)
 * in .5dB steps -  0dB is 0x7 */

/* 0x08, 0x09 - A1 and A2 (पढ़ो/ग_लिखो) */
/* Common to both TDA9855 and TDA9850: */
/* lower 5 bites are wideband and spectral expander alignment
 * from 0x00 to 0x1f - nominal at 0x0f and 0x10 (पढ़ो/ग_लिखो) */
#घोषणा TDA985x_STP	1<<5 /* Stereo Pilot/detect (पढ़ो-only) */
#घोषणा TDA985x_SAPP	1<<6 /* SAP Pilot/detect (पढ़ो-only) */
#घोषणा TDA985x_STS	1<<7 /* Stereo trigger 1= <35mV 0= <30mV (ग_लिखो-only)*/

/* 0x0a - A3 */
/* Common to both TDA9855 and TDA9850: */
/* lower 3 bits control timing current क्रम alignment: -30% (0x0), -20% (0x1),
 * -10% (0x2), nominal (0x3), +10% (0x6), +20% (0x5), +30% (0x4) */
#घोषणा TDA985x_ADJ	1<<7 /* Stereo adjust on/off (wideband and spectral */

अटल पूर्णांक tda9855_volume(पूर्णांक val) अणु वापस val/0x2e8+0x27; पूर्ण
अटल पूर्णांक tda9855_bass(पूर्णांक val)   अणु वापस val/0xccc+0x06; पूर्ण
अटल पूर्णांक tda9855_treble(पूर्णांक val) अणु वापस (val/0x1c71+0x3)<<1; पूर्ण

अटल पूर्णांक  tda985x_getrxsubchans(काष्ठा CHIPSTATE *chip)
अणु
	पूर्णांक mode, val;

	/* Add mono mode regardless of SAP and stereo */
	/* Allows क्रमced mono */
	mode = V4L2_TUNER_SUB_MONO;
	val = chip_पढ़ो(chip);
	अगर (val < 0)
		वापस mode;

	अगर (val & TDA985x_STP)
		mode = V4L2_TUNER_SUB_STEREO;
	अगर (val & TDA985x_SAPP)
		mode |= V4L2_TUNER_SUB_SAP;
	वापस mode;
पूर्ण

अटल व्योम tda985x_setaudmode(काष्ठा CHIPSTATE *chip, पूर्णांक mode)
अणु
	पूर्णांक update = 1;
	पूर्णांक c6 = chip->shaकरोw.bytes[TDA985x_C6+1] & 0x3f;

	चयन (mode) अणु
	हाल V4L2_TUNER_MODE_MONO:
		c6 |= TDA985x_MONO;
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
	हाल V4L2_TUNER_MODE_LANG1:
		c6 |= TDA985x_STEREO;
		अवरोध;
	हाल V4L2_TUNER_MODE_SAP:
		c6 |= TDA985x_SAP;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1_LANG2:
		c6 |= TDA985x_MONOSAP;
		अवरोध;
	शेष:
		update = 0;
	पूर्ण
	अगर (update)
		chip_ग_लिखो(chip,TDA985x_C6,c6);
पूर्ण


/* ---------------------------------------------------------------------- */
/* audio chip descriptions - defines+functions क्रम tda9873h               */

/* Subaddresses क्रम TDA9873H */

#घोषणा TDA9873_SW	0x00 /* Switching                    */
#घोषणा TDA9873_AD	0x01 /* Adjust                       */
#घोषणा TDA9873_PT	0x02 /* Port                         */

/* Subaddress 0x00: Switching Data
 * B7..B0:
 *
 * B1, B0: Input source selection
 *  0,  0  पूर्णांकernal
 *  1,  0  बाह्यal stereo
 *  0,  1  बाह्यal mono
 */
#घोषणा TDA9873_INP_MASK    3
#घोषणा TDA9873_INTERNAL    0
#घोषणा TDA9873_EXT_STEREO  2
#घोषणा TDA9873_EXT_MONO    1

/*    B3, B2: output संकेत select
 * B4    : transmission mode
 *  0, 0, 1   Mono
 *  1, 0, 0   Stereo
 *  1, 1, 1   Stereo (reversed channel)
 *  0, 0, 0   Dual AB
 *  0, 0, 1   Dual AA
 *  0, 1, 0   Dual BB
 *  0, 1, 1   Dual BA
 */

#घोषणा TDA9873_TR_MASK     (7 << 2)
#घोषणा TDA9873_TR_MONO     4
#घोषणा TDA9873_TR_STEREO   1 << 4
#घोषणा TDA9873_TR_REVERSE  ((1 << 3) | (1 << 2))
#घोषणा TDA9873_TR_DUALA    1 << 2
#घोषणा TDA9873_TR_DUALB    1 << 3
#घोषणा TDA9873_TR_DUALAB   0

/* output level controls
 * B5:  output level चयन (0 = reduced gain, 1 = normal gain)
 * B6:  mute                (1 = muted)
 * B7:  स्वतः-mute           (1 = स्वतः-mute enabled)
 */

#घोषणा TDA9873_GAIN_NORMAL 1 << 5
#घोषणा TDA9873_MUTE        1 << 6
#घोषणा TDA9873_AUTOMUTE    1 << 7

/* Subaddress 0x01:  Adjust/standard */

/* Lower 4 bits (C3..C0) control stereo adjusपंचांगent on R channel (-0.6 - +0.7 dB)
 * Recommended value is +0 dB
 */

#घोषणा	TDA9873_STEREO_ADJ	0x06 /* 0dB gain */

/* Bits C6..C4 control FM stantard
 * C6, C5, C4
 *  0,  0,  0   B/G (PAL FM)
 *  0,  0,  1   M
 *  0,  1,  0   D/K(1)
 *  0,  1,  1   D/K(2)
 *  1,  0,  0   D/K(3)
 *  1,  0,  1   I
 */
#घोषणा TDA9873_BG		0
#घोषणा TDA9873_M       1
#घोषणा TDA9873_DK1     2
#घोषणा TDA9873_DK2     3
#घोषणा TDA9873_DK3     4
#घोषणा TDA9873_I       5

/* C7 controls identअगरication response समय (1=fast/0=normal)
 */
#घोषणा TDA9873_IDR_NORM 0
#घोषणा TDA9873_IDR_FAST 1 << 7


/* Subaddress 0x02: Port data */

/* E1, E0   मुक्त programmable ports P1/P2
    0,  0   both ports low
    0,  1   P1 high
    1,  0   P2 high
    1,  1   both ports high
*/

#घोषणा TDA9873_PORTS    3

/* E2: test port */
#घोषणा TDA9873_TST_PORT 1 << 2

/* E5..E3 control mono output channel (together with transmission mode bit B4)
 *
 * E5 E4 E3 B4     OUTM
 *  0  0  0  0     mono
 *  0  0  1  0     DUAL B
 *  0  1  0  1     mono (from stereo decoder)
 */
#घोषणा TDA9873_MOUT_MONO   0
#घोषणा TDA9873_MOUT_FMONO  0
#घोषणा TDA9873_MOUT_DUALA  0
#घोषणा TDA9873_MOUT_DUALB  1 << 3
#घोषणा TDA9873_MOUT_ST     1 << 4
#घोषणा TDA9873_MOUT_EXTM   ((1 << 4) | (1 << 3))
#घोषणा TDA9873_MOUT_EXTL   1 << 5
#घोषणा TDA9873_MOUT_EXTR   ((1 << 5) | (1 << 3))
#घोषणा TDA9873_MOUT_EXTLR  ((1 << 5) | (1 << 4))
#घोषणा TDA9873_MOUT_MUTE   ((1 << 5) | (1 << 4) | (1 << 3))

/* Status bits: (chip पढ़ो) */
#घोषणा TDA9873_PONR        0 /* Power-on reset detected अगर = 1 */
#घोषणा TDA9873_STEREO      2 /* Stereo sound is identअगरied     */
#घोषणा TDA9873_DUAL        4 /* Dual sound is identअगरied       */

अटल पूर्णांक tda9873_getrxsubchans(काष्ठा CHIPSTATE *chip)
अणु
	काष्ठा v4l2_subdev *sd = &chip->sd;
	पूर्णांक val,mode;

	mode = V4L2_TUNER_SUB_MONO;

	val = chip_पढ़ो(chip);
	अगर (val < 0)
		वापस mode;

	अगर (val & TDA9873_STEREO)
		mode = V4L2_TUNER_SUB_STEREO;
	अगर (val & TDA9873_DUAL)
		mode |= V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
	v4l2_dbg(1, debug, sd,
		"tda9873_getrxsubchans(): raw chip read: %d, return: %d\n",
		val, mode);
	वापस mode;
पूर्ण

अटल व्योम tda9873_setaudmode(काष्ठा CHIPSTATE *chip, पूर्णांक mode)
अणु
	काष्ठा v4l2_subdev *sd = &chip->sd;
	पूर्णांक sw_data  = chip->shaकरोw.bytes[TDA9873_SW+1] & ~ TDA9873_TR_MASK;
	/*	पूर्णांक adj_data = chip->shaकरोw.bytes[TDA9873_AD+1] ; */

	अगर ((sw_data & TDA9873_INP_MASK) != TDA9873_INTERNAL) अणु
		v4l2_dbg(1, debug, sd,
			 "tda9873_setaudmode(): external input\n");
		वापस;
	पूर्ण

	v4l2_dbg(1, debug, sd,
		 "tda9873_setaudmode(): chip->shadow.bytes[%d] = %d\n",
		 TDA9873_SW+1, chip->shaकरोw.bytes[TDA9873_SW+1]);
	v4l2_dbg(1, debug, sd, "tda9873_setaudmode(): sw_data  = %d\n",
		 sw_data);

	चयन (mode) अणु
	हाल V4L2_TUNER_MODE_MONO:
		sw_data |= TDA9873_TR_MONO;
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
		sw_data |= TDA9873_TR_STEREO;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1:
		sw_data |= TDA9873_TR_DUALA;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG2:
		sw_data |= TDA9873_TR_DUALB;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1_LANG2:
		sw_data |= TDA9873_TR_DUALAB;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	chip_ग_लिखो(chip, TDA9873_SW, sw_data);
	v4l2_dbg(1, debug, sd,
		"tda9873_setaudmode(): req. mode %d; chip_write: %d\n",
		mode, sw_data);
पूर्ण

अटल पूर्णांक tda9873_checkit(काष्ठा CHIPSTATE *chip)
अणु
	पूर्णांक rc;

	rc = chip_पढ़ो2(chip, 254);
	अगर (rc < 0)
		वापस 0;
	वापस (rc & ~0x1f) == 0x80;
पूर्ण


/* ---------------------------------------------------------------------- */
/* audio chip description - defines+functions क्रम tda9874h and tda9874a   */
/* Dariusz Kowalewski <darekk@स्वतःmex.pl>                                 */

/* Subaddresses क्रम TDA9874H and TDA9874A (slave rx) */
#घोषणा TDA9874A_AGCGR		0x00	/* AGC gain */
#घोषणा TDA9874A_GCONR		0x01	/* general config */
#घोषणा TDA9874A_MSR		0x02	/* monitor select */
#घोषणा TDA9874A_C1FRA		0x03	/* carrier 1 freq. */
#घोषणा TDA9874A_C1FRB		0x04	/* carrier 1 freq. */
#घोषणा TDA9874A_C1FRC		0x05	/* carrier 1 freq. */
#घोषणा TDA9874A_C2FRA		0x06	/* carrier 2 freq. */
#घोषणा TDA9874A_C2FRB		0x07	/* carrier 2 freq. */
#घोषणा TDA9874A_C2FRC		0x08	/* carrier 2 freq. */
#घोषणा TDA9874A_DCR		0x09	/* demodulator config */
#घोषणा TDA9874A_FMER		0x0a	/* FM de-emphasis */
#घोषणा TDA9874A_FMMR		0x0b	/* FM dematrix */
#घोषणा TDA9874A_C1OLAR		0x0c	/* ch.1 output level adj. */
#घोषणा TDA9874A_C2OLAR		0x0d	/* ch.2 output level adj. */
#घोषणा TDA9874A_NCONR		0x0e	/* NICAM config */
#घोषणा TDA9874A_NOLAR		0x0f	/* NICAM output level adj. */
#घोषणा TDA9874A_NLELR		0x10	/* NICAM lower error limit */
#घोषणा TDA9874A_NUELR		0x11	/* NICAM upper error limit */
#घोषणा TDA9874A_AMCONR		0x12	/* audio mute control */
#घोषणा TDA9874A_SDACOSR	0x13	/* stereo DAC output select */
#घोषणा TDA9874A_AOSR		0x14	/* analog output select */
#घोषणा TDA9874A_DAICONR	0x15	/* digital audio पूर्णांकerface config */
#घोषणा TDA9874A_I2SOSR		0x16	/* I2S-bus output select */
#घोषणा TDA9874A_I2SOLAR	0x17	/* I2S-bus output level adj. */
#घोषणा TDA9874A_MDACOSR	0x18	/* mono DAC output select (tda9874a) */
#घोषणा TDA9874A_ESP		0xFF	/* easy standard progr. (tda9874a) */

/* Subaddresses क्रम TDA9874H and TDA9874A (slave tx) */
#घोषणा TDA9874A_DSR		0x00	/* device status */
#घोषणा TDA9874A_NSR		0x01	/* NICAM status */
#घोषणा TDA9874A_NECR		0x02	/* NICAM error count */
#घोषणा TDA9874A_DR1		0x03	/* add. data LSB */
#घोषणा TDA9874A_DR2		0x04	/* add. data MSB */
#घोषणा TDA9874A_LLRA		0x05	/* monitor level पढ़ो-out LSB */
#घोषणा TDA9874A_LLRB		0x06	/* monitor level पढ़ो-out MSB */
#घोषणा TDA9874A_SIFLR		0x07	/* SIF level */
#घोषणा TDA9874A_TR2		252	/* test reg. 2 */
#घोषणा TDA9874A_TR1		253	/* test reg. 1 */
#घोषणा TDA9874A_DIC		254	/* device id. code */
#घोषणा TDA9874A_SIC		255	/* software id. code */


अटल पूर्णांक tda9874a_mode = 1;		/* 0: A2, 1: NICAM */
अटल पूर्णांक tda9874a_GCONR = 0xc0;	/* शेष config. input pin: SIFSEL=0 */
अटल पूर्णांक tda9874a_NCONR = 0x01;	/* शेष NICAM config.: AMSEL=0,AMUTE=1 */
अटल पूर्णांक tda9874a_ESP = 0x07;		/* शेष standard: NICAM D/K */
अटल पूर्णांक tda9874a_dic = -1;		/* device id. code */

/* insmod options क्रम tda9874a */
अटल अचिन्हित पूर्णांक tda9874a_SIF   = UNSET;
अटल अचिन्हित पूर्णांक tda9874a_AMSEL = UNSET;
अटल अचिन्हित पूर्णांक tda9874a_STD   = UNSET;
module_param(tda9874a_SIF, पूर्णांक, 0444);
module_param(tda9874a_AMSEL, पूर्णांक, 0444);
module_param(tda9874a_STD, पूर्णांक, 0444);

/*
 * initialization table क्रम tda9874 decoder:
 *  - carrier 1 freq. रेजिस्टरs (3 bytes)
 *  - carrier 2 freq. रेजिस्टरs (3 bytes)
 *  - demudulator config रेजिस्टर
 *  - FM de-emphasis रेजिस्टर (slow identअगरication mode)
 * Note: frequency रेजिस्टरs must be written in single i2c transfer.
 */
अटल काष्ठा tda9874a_MODES अणु
	अक्षर *name;
	audiocmd cmd;
पूर्ण tda9874a_modelist[9] = अणु
  अणु	"A2, B/G", /* शेष */
	अणु 9, अणु TDA9874A_C1FRA, 0x72,0x95,0x55, 0x77,0xA0,0x00, 0x00,0x00 पूर्णपूर्ण पूर्ण,
  अणु	"A2, M (Korea)",
	अणु 9, अणु TDA9874A_C1FRA, 0x5D,0xC0,0x00, 0x62,0x6A,0xAA, 0x20,0x22 पूर्णपूर्ण पूर्ण,
  अणु	"A2, D/K (1)",
	अणु 9, अणु TDA9874A_C1FRA, 0x87,0x6A,0xAA, 0x82,0x60,0x00, 0x00,0x00 पूर्णपूर्ण पूर्ण,
  अणु	"A2, D/K (2)",
	अणु 9, अणु TDA9874A_C1FRA, 0x87,0x6A,0xAA, 0x8C,0x75,0x55, 0x00,0x00 पूर्णपूर्ण पूर्ण,
  अणु	"A2, D/K (3)",
	अणु 9, अणु TDA9874A_C1FRA, 0x87,0x6A,0xAA, 0x77,0xA0,0x00, 0x00,0x00 पूर्णपूर्ण पूर्ण,
  अणु	"NICAM, I",
	अणु 9, अणु TDA9874A_C1FRA, 0x7D,0x00,0x00, 0x88,0x8A,0xAA, 0x08,0x33 पूर्णपूर्ण पूर्ण,
  अणु	"NICAM, B/G",
	अणु 9, अणु TDA9874A_C1FRA, 0x72,0x95,0x55, 0x79,0xEA,0xAA, 0x08,0x33 पूर्णपूर्ण पूर्ण,
  अणु	"NICAM, D/K",
	अणु 9, अणु TDA9874A_C1FRA, 0x87,0x6A,0xAA, 0x79,0xEA,0xAA, 0x08,0x33 पूर्णपूर्ण पूर्ण,
  अणु	"NICAM, L",
	अणु 9, अणु TDA9874A_C1FRA, 0x87,0x6A,0xAA, 0x79,0xEA,0xAA, 0x09,0x33 पूर्णपूर्ण पूर्ण
पूर्ण;

अटल पूर्णांक tda9874a_setup(काष्ठा CHIPSTATE *chip)
अणु
	काष्ठा v4l2_subdev *sd = &chip->sd;

	chip_ग_लिखो(chip, TDA9874A_AGCGR, 0x00); /* 0 dB */
	chip_ग_लिखो(chip, TDA9874A_GCONR, tda9874a_GCONR);
	chip_ग_लिखो(chip, TDA9874A_MSR, (tda9874a_mode) ? 0x03:0x02);
	अगर(tda9874a_dic == 0x11) अणु
		chip_ग_लिखो(chip, TDA9874A_FMMR, 0x80);
	पूर्ण अन्यथा अणु /* dic == 0x07 */
		chip_cmd(chip,"tda9874_modelist",&tda9874a_modelist[tda9874a_STD].cmd);
		chip_ग_लिखो(chip, TDA9874A_FMMR, 0x00);
	पूर्ण
	chip_ग_लिखो(chip, TDA9874A_C1OLAR, 0x00); /* 0 dB */
	chip_ग_लिखो(chip, TDA9874A_C2OLAR, 0x00); /* 0 dB */
	chip_ग_लिखो(chip, TDA9874A_NCONR, tda9874a_NCONR);
	chip_ग_लिखो(chip, TDA9874A_NOLAR, 0x00); /* 0 dB */
	/* Note: If संकेत quality is poor you may want to change NICAM */
	/* error limit रेजिस्टरs (NLELR and NUELR) to some greater values. */
	/* Then the sound would reमुख्य stereo, but won't be so clear. */
	chip_ग_लिखो(chip, TDA9874A_NLELR, 0x14); /* शेष */
	chip_ग_लिखो(chip, TDA9874A_NUELR, 0x50); /* शेष */

	अगर(tda9874a_dic == 0x11) अणु
		chip_ग_लिखो(chip, TDA9874A_AMCONR, 0xf9);
		chip_ग_लिखो(chip, TDA9874A_SDACOSR, (tda9874a_mode) ? 0x81:0x80);
		chip_ग_लिखो(chip, TDA9874A_AOSR, 0x80);
		chip_ग_लिखो(chip, TDA9874A_MDACOSR, (tda9874a_mode) ? 0x82:0x80);
		chip_ग_लिखो(chip, TDA9874A_ESP, tda9874a_ESP);
	पूर्ण अन्यथा अणु /* dic == 0x07 */
		chip_ग_लिखो(chip, TDA9874A_AMCONR, 0xfb);
		chip_ग_लिखो(chip, TDA9874A_SDACOSR, (tda9874a_mode) ? 0x81:0x80);
		chip_ग_लिखो(chip, TDA9874A_AOSR, 0x00); /* or 0x10 */
	पूर्ण
	v4l2_dbg(1, debug, sd, "tda9874a_setup(): %s [0x%02X].\n",
		tda9874a_modelist[tda9874a_STD].name,tda9874a_STD);
	वापस 1;
पूर्ण

अटल पूर्णांक tda9874a_getrxsubchans(काष्ठा CHIPSTATE *chip)
अणु
	काष्ठा v4l2_subdev *sd = &chip->sd;
	पूर्णांक dsr,nsr,mode;
	पूर्णांक necr; /* just क्रम debugging */

	mode = V4L2_TUNER_SUB_MONO;

	dsr = chip_पढ़ो2(chip, TDA9874A_DSR);
	अगर (dsr < 0)
		वापस mode;
	nsr = chip_पढ़ो2(chip, TDA9874A_NSR);
	अगर (nsr < 0)
		वापस mode;
	necr = chip_पढ़ो2(chip, TDA9874A_NECR);
	अगर (necr < 0)
		वापस mode;

	/* need to store dsr/nsr somewhere */
	chip->shaकरोw.bytes[MAXREGS-2] = dsr;
	chip->shaकरोw.bytes[MAXREGS-1] = nsr;

	अगर(tda9874a_mode) अणु
		/* Note: DSR.RSSF and DSR.AMSTAT bits are also checked.
		 * If NICAM स्वतः-muting is enabled, DSR.AMSTAT=1 indicates
		 * that sound has (temporarily) चयनed from NICAM to
		 * mono FM (or AM) on 1st sound carrier due to high NICAM bit
		 * error count. So in fact there is no stereo in this हाल :-(
		 * But changing the mode to V4L2_TUNER_MODE_MONO would चयन
		 * बाह्यal 4052 multiplexer in audio_hook().
		 */
		अगर(nsr & 0x02) /* NSR.S/MB=1 */
			mode = V4L2_TUNER_SUB_STEREO;
		अगर(nsr & 0x01) /* NSR.D/SB=1 */
			mode |= V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
	पूर्ण अन्यथा अणु
		अगर(dsr & 0x02) /* DSR.IDSTE=1 */
			mode = V4L2_TUNER_SUB_STEREO;
		अगर(dsr & 0x04) /* DSR.IDDUA=1 */
			mode |= V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
	पूर्ण

	v4l2_dbg(1, debug, sd,
		 "tda9874a_getrxsubchans(): DSR=0x%X, NSR=0x%X, NECR=0x%X, return: %d.\n",
		 dsr, nsr, necr, mode);
	वापस mode;
पूर्ण

अटल व्योम tda9874a_setaudmode(काष्ठा CHIPSTATE *chip, पूर्णांक mode)
अणु
	काष्ठा v4l2_subdev *sd = &chip->sd;

	/* Disable/enable NICAM स्वतः-muting (based on DSR.RSSF status bit). */
	/* If स्वतः-muting is disabled, we can hear a संकेत of degrading quality. */
	अगर (tda9874a_mode) अणु
		अगर(chip->shaकरोw.bytes[MAXREGS-2] & 0x20) /* DSR.RSSF=1 */
			tda9874a_NCONR &= 0xfe; /* enable */
		अन्यथा
			tda9874a_NCONR |= 0x01; /* disable */
		chip_ग_लिखो(chip, TDA9874A_NCONR, tda9874a_NCONR);
	पूर्ण

	/* Note: TDA9874A supports स्वतःmatic FM dematrixing (FMMR रेजिस्टर)
	 * and has स्वतः-select function क्रम audio output (AOSR रेजिस्टर).
	 * Old TDA9874H करोesn't support these features.
	 * TDA9874A also has additional mono output pin (OUTM), which
	 * on same (all?) tv-cards is not used, anyway (as well as MONOIN).
	 */
	अगर(tda9874a_dic == 0x11) अणु
		पूर्णांक aosr = 0x80;
		पूर्णांक mdacosr = (tda9874a_mode) ? 0x82:0x80;

		चयन(mode) अणु
		हाल V4L2_TUNER_MODE_MONO:
		हाल V4L2_TUNER_MODE_STEREO:
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG1:
			aosr = 0x80; /* स्वतः-select, dual A/A */
			mdacosr = (tda9874a_mode) ? 0x82:0x80;
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG2:
			aosr = 0xa0; /* स्वतः-select, dual B/B */
			mdacosr = (tda9874a_mode) ? 0x83:0x81;
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG1_LANG2:
			aosr = 0x00; /* always route L to L and R to R */
			mdacosr = (tda9874a_mode) ? 0x82:0x80;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		chip_ग_लिखो(chip, TDA9874A_AOSR, aosr);
		chip_ग_लिखो(chip, TDA9874A_MDACOSR, mdacosr);

		v4l2_dbg(1, debug, sd,
			"tda9874a_setaudmode(): req. mode %d; AOSR=0x%X, MDACOSR=0x%X.\n",
			mode, aosr, mdacosr);

	पूर्ण अन्यथा अणु /* dic == 0x07 */
		पूर्णांक fmmr,aosr;

		चयन(mode) अणु
		हाल V4L2_TUNER_MODE_MONO:
			fmmr = 0x00; /* mono */
			aosr = 0x10; /* A/A */
			अवरोध;
		हाल V4L2_TUNER_MODE_STEREO:
			अगर(tda9874a_mode) अणु
				fmmr = 0x00;
				aosr = 0x00; /* handled by NICAM स्वतः-mute */
			पूर्ण अन्यथा अणु
				fmmr = (tda9874a_ESP == 1) ? 0x05 : 0x04; /* stereo */
				aosr = 0x00;
			पूर्ण
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG1:
			fmmr = 0x02; /* dual */
			aosr = 0x10; /* dual A/A */
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG2:
			fmmr = 0x02; /* dual */
			aosr = 0x20; /* dual B/B */
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG1_LANG2:
			fmmr = 0x02; /* dual */
			aosr = 0x00; /* dual A/B */
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		chip_ग_लिखो(chip, TDA9874A_FMMR, fmmr);
		chip_ग_लिखो(chip, TDA9874A_AOSR, aosr);

		v4l2_dbg(1, debug, sd,
			"tda9874a_setaudmode(): req. mode %d; FMMR=0x%X, AOSR=0x%X.\n",
			mode, fmmr, aosr);
	पूर्ण
पूर्ण

अटल पूर्णांक tda9874a_checkit(काष्ठा CHIPSTATE *chip)
अणु
	काष्ठा v4l2_subdev *sd = &chip->sd;
	पूर्णांक dic,sic;	/* device id. and software id. codes */

	dic = chip_पढ़ो2(chip, TDA9874A_DIC);
	अगर (dic < 0)
		वापस 0;
	sic = chip_पढ़ो2(chip, TDA9874A_SIC);
	अगर (sic < 0)
		वापस 0;

	v4l2_dbg(1, debug, sd, "tda9874a_checkit(): DIC=0x%X, SIC=0x%X.\n", dic, sic);

	अगर((dic == 0x11)||(dic == 0x07)) अणु
		v4l2_info(sd, "found tda9874%s.\n", (dic == 0x11) ? "a" : "h");
		tda9874a_dic = dic;	/* remember device id. */
		वापस 1;
	पूर्ण
	वापस 0;	/* not found */
पूर्ण

अटल पूर्णांक tda9874a_initialize(काष्ठा CHIPSTATE *chip)
अणु
	अगर (tda9874a_SIF > 2)
		tda9874a_SIF = 1;
	अगर (tda9874a_STD >= ARRAY_SIZE(tda9874a_modelist))
		tda9874a_STD = 0;
	अगर(tda9874a_AMSEL > 1)
		tda9874a_AMSEL = 0;

	अगर(tda9874a_SIF == 1)
		tda9874a_GCONR = 0xc0;	/* sound IF input 1 */
	अन्यथा
		tda9874a_GCONR = 0xc1;	/* sound IF input 2 */

	tda9874a_ESP = tda9874a_STD;
	tda9874a_mode = (tda9874a_STD < 5) ? 0 : 1;

	अगर(tda9874a_AMSEL == 0)
		tda9874a_NCONR = 0x01; /* स्वतः-mute: analog mono input */
	अन्यथा
		tda9874a_NCONR = 0x05; /* स्वतः-mute: 1st carrier FM or AM */

	tda9874a_setup(chip);
	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------- */
/* audio chip description - defines+functions क्रम tda9875                 */
/* The TDA9875 is made by Philips Semiconductor
 * http://www.semiconductors.philips.com
 * TDA9875: I2C-bus controlled DSP audio processor, FM demodulator
 *
 */

/* subaddresses क्रम TDA9875 */
#घोषणा TDA9875_MUT         0x12  /*General mute  (value --> 0b11001100*/
#घोषणा TDA9875_CFG         0x01  /* Config रेजिस्टर (value --> 0b00000000 */
#घोषणा TDA9875_DACOS       0x13  /*DAC i/o select (ADC) 0b0000100*/
#घोषणा TDA9875_LOSR        0x16  /*Line output select regirter 0b0100 0001*/

#घोषणा TDA9875_CH1V        0x0c  /*Channel 1 volume (mute)*/
#घोषणा TDA9875_CH2V        0x0d  /*Channel 2 volume (mute)*/
#घोषणा TDA9875_SC1         0x14  /*SCART 1 in (mono)*/
#घोषणा TDA9875_SC2         0x15  /*SCART 2 in (mono)*/

#घोषणा TDA9875_ADCIS       0x17  /*ADC input select (mono) 0b0110 000*/
#घोषणा TDA9875_AER         0x19  /*Audio effect (AVL+Pseuकरो) 0b0000 0110*/
#घोषणा TDA9875_MCS         0x18  /*Main channel select (DAC) 0b0000100*/
#घोषणा TDA9875_MVL         0x1a  /* Main volume gauche */
#घोषणा TDA9875_MVR         0x1b  /* Main volume droite */
#घोषणा TDA9875_MBA         0x1d  /* Main Basse */
#घोषणा TDA9875_MTR         0x1e  /* Main treble */
#घोषणा TDA9875_ACS         0x1f  /* Auxiliary channel select (FM) 0b0000000*/
#घोषणा TDA9875_AVL         0x20  /* Auxiliary volume gauche */
#घोषणा TDA9875_AVR         0x21  /* Auxiliary volume droite */
#घोषणा TDA9875_ABA         0x22  /* Auxiliary Basse */
#घोषणा TDA9875_ATR         0x23  /* Auxiliary treble */

#घोषणा TDA9875_MSR         0x02  /* Monitor select रेजिस्टर */
#घोषणा TDA9875_C1MSB       0x03  /* Carrier 1 (FM) frequency रेजिस्टर MSB */
#घोषणा TDA9875_C1MIB       0x04  /* Carrier 1 (FM) frequency रेजिस्टर (16-8]b */
#घोषणा TDA9875_C1LSB       0x05  /* Carrier 1 (FM) frequency रेजिस्टर LSB */
#घोषणा TDA9875_C2MSB       0x06  /* Carrier 2 (nicam) frequency रेजिस्टर MSB */
#घोषणा TDA9875_C2MIB       0x07  /* Carrier 2 (nicam) frequency रेजिस्टर (16-8]b */
#घोषणा TDA9875_C2LSB       0x08  /* Carrier 2 (nicam) frequency रेजिस्टर LSB */
#घोषणा TDA9875_DCR         0x09  /* Demodulateur configuration regirter*/
#घोषणा TDA9875_DEEM        0x0a  /* FM de-emphasis regirter*/
#घोषणा TDA9875_FMAT        0x0b  /* FM Matrix regirter*/

/* values */
#घोषणा TDA9875_MUTE_ON	    0xff /* general mute */
#घोषणा TDA9875_MUTE_OFF    0xcc /* general no mute */

अटल पूर्णांक tda9875_initialize(काष्ठा CHIPSTATE *chip)
अणु
	chip_ग_लिखो(chip, TDA9875_CFG, 0xd0); /*reg de config 0 (reset)*/
	chip_ग_लिखो(chip, TDA9875_MSR, 0x03);    /* Monitor 0b00000XXX*/
	chip_ग_लिखो(chip, TDA9875_C1MSB, 0x00);  /*Car1(FM) MSB XMHz*/
	chip_ग_लिखो(chip, TDA9875_C1MIB, 0x00);  /*Car1(FM) MIB XMHz*/
	chip_ग_लिखो(chip, TDA9875_C1LSB, 0x00);  /*Car1(FM) LSB XMHz*/
	chip_ग_लिखो(chip, TDA9875_C2MSB, 0x00);  /*Car2(NICAM) MSB XMHz*/
	chip_ग_लिखो(chip, TDA9875_C2MIB, 0x00);  /*Car2(NICAM) MIB XMHz*/
	chip_ग_लिखो(chip, TDA9875_C2LSB, 0x00);  /*Car2(NICAM) LSB XMHz*/
	chip_ग_लिखो(chip, TDA9875_DCR, 0x00);    /*Demod config 0x00*/
	chip_ग_लिखो(chip, TDA9875_DEEM, 0x44);   /*DE-Emph 0b0100 0100*/
	chip_ग_लिखो(chip, TDA9875_FMAT, 0x00);   /*FM Matrix reg 0x00*/
	chip_ग_लिखो(chip, TDA9875_SC1, 0x00);    /* SCART 1 (SC1)*/
	chip_ग_लिखो(chip, TDA9875_SC2, 0x01);    /* SCART 2 (sc2)*/

	chip_ग_लिखो(chip, TDA9875_CH1V, 0x10);  /* Channel volume 1 mute*/
	chip_ग_लिखो(chip, TDA9875_CH2V, 0x10);  /* Channel volume 2 mute */
	chip_ग_लिखो(chip, TDA9875_DACOS, 0x02); /* sig DAC i/o(in:nicam)*/
	chip_ग_लिखो(chip, TDA9875_ADCIS, 0x6f); /* sig ADC input(in:mono)*/
	chip_ग_लिखो(chip, TDA9875_LOSR, 0x00);  /* line out (in:mono)*/
	chip_ग_लिखो(chip, TDA9875_AER, 0x00);   /*06 Effect (AVL+PSEUDO) */
	chip_ग_लिखो(chip, TDA9875_MCS, 0x44);   /* Main ch select (DAC) */
	chip_ग_लिखो(chip, TDA9875_MVL, 0x03);   /* Vol Main left 10dB */
	chip_ग_लिखो(chip, TDA9875_MVR, 0x03);   /* Vol Main right 10dB*/
	chip_ग_लिखो(chip, TDA9875_MBA, 0x00);   /* Main Bass Main 0dB*/
	chip_ग_लिखो(chip, TDA9875_MTR, 0x00);   /* Main Treble Main 0dB*/
	chip_ग_लिखो(chip, TDA9875_ACS, 0x44);   /* Aux chan select (dac)*/
	chip_ग_लिखो(chip, TDA9875_AVL, 0x00);   /* Vol Aux left 0dB*/
	chip_ग_लिखो(chip, TDA9875_AVR, 0x00);   /* Vol Aux right 0dB*/
	chip_ग_लिखो(chip, TDA9875_ABA, 0x00);   /* Aux Bass Main 0dB*/
	chip_ग_लिखो(chip, TDA9875_ATR, 0x00);   /* Aux Aigus Main 0dB*/

	chip_ग_लिखो(chip, TDA9875_MUT, 0xcc);   /* General mute  */
	वापस 0;
पूर्ण

अटल पूर्णांक tda9875_volume(पूर्णांक val) अणु वापस (अचिन्हित अक्षर)(val / 602 - 84); पूर्ण
अटल पूर्णांक tda9875_bass(पूर्णांक val) अणु वापस (अचिन्हित अक्षर)(max(-12, val / 2115 - 15)); पूर्ण
अटल पूर्णांक tda9875_treble(पूर्णांक val) अणु वापस (अचिन्हित अक्षर)(val / 2622 - 12); पूर्ण

/* ----------------------------------------------------------------------- */


/* *********************** *
 * i2c पूर्णांकerface functions *
 * *********************** */

अटल पूर्णांक tda9875_checkit(काष्ठा CHIPSTATE *chip)
अणु
	काष्ठा v4l2_subdev *sd = &chip->sd;
	पूर्णांक dic, rev;

	dic = chip_पढ़ो2(chip, 254);
	अगर (dic < 0)
		वापस 0;
	rev = chip_पढ़ो2(chip, 255);
	अगर (rev < 0)
		वापस 0;

	अगर (dic == 0 || dic == 2) अणु /* tda9875 and tda9875A */
		v4l2_info(sd, "found tda9875%s rev. %d.\n",
			dic == 0 ? "" : "A", rev);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------- */
/* audio chip descriptions - defines+functions क्रम tea6420                */

#घोषणा TEA6300_VL         0x00  /* volume left */
#घोषणा TEA6300_VR         0x01  /* volume right */
#घोषणा TEA6300_BA         0x02  /* bass */
#घोषणा TEA6300_TR         0x03  /* treble */
#घोषणा TEA6300_FA         0x04  /* fader control */
#घोषणा TEA6300_S          0x05  /* चयन रेजिस्टर */
				 /* values क्रम those रेजिस्टरs: */
#घोषणा TEA6300_S_SA       0x01  /* stereo A input */
#घोषणा TEA6300_S_SB       0x02  /* stereo B */
#घोषणा TEA6300_S_SC       0x04  /* stereo C */
#घोषणा TEA6300_S_GMU      0x80  /* general mute */

#घोषणा TEA6320_V          0x00  /* volume (0-5)/loudness off (6)/zero crossing mute(7) */
#घोषणा TEA6320_FFR        0x01  /* fader front right (0-5) */
#घोषणा TEA6320_FFL        0x02  /* fader front left (0-5) */
#घोषणा TEA6320_FRR        0x03  /* fader rear right (0-5) */
#घोषणा TEA6320_FRL        0x04  /* fader rear left (0-5) */
#घोषणा TEA6320_BA         0x05  /* bass (0-4) */
#घोषणा TEA6320_TR         0x06  /* treble (0-4) */
#घोषणा TEA6320_S          0x07  /* चयन रेजिस्टर */
				 /* values क्रम those रेजिस्टरs: */
#घोषणा TEA6320_S_SA       0x07  /* stereo A input */
#घोषणा TEA6320_S_SB       0x06  /* stereo B */
#घोषणा TEA6320_S_SC       0x05  /* stereo C */
#घोषणा TEA6320_S_SD       0x04  /* stereo D */
#घोषणा TEA6320_S_GMU      0x80  /* general mute */

#घोषणा TEA6420_S_SA       0x00  /* stereo A input */
#घोषणा TEA6420_S_SB       0x01  /* stereo B */
#घोषणा TEA6420_S_SC       0x02  /* stereo C */
#घोषणा TEA6420_S_SD       0x03  /* stereo D */
#घोषणा TEA6420_S_SE       0x04  /* stereo E */
#घोषणा TEA6420_S_GMU      0x05  /* general mute */

अटल पूर्णांक tea6300_shअगरt10(पूर्णांक val) अणु वापस val >> 10; पूर्ण
अटल पूर्णांक tea6300_shअगरt12(पूर्णांक val) अणु वापस val >> 12; पूर्ण

/* Assumes 16bit input (values 0x3f to 0x0c are unique, values less than */
/* 0x0c mirror those immediately higher) */
अटल पूर्णांक tea6320_volume(पूर्णांक val) अणु वापस (val / (65535/(63-12)) + 12) & 0x3f; पूर्ण
अटल पूर्णांक tea6320_shअगरt11(पूर्णांक val) अणु वापस val >> 11; पूर्ण
अटल पूर्णांक tea6320_initialize(काष्ठा CHIPSTATE * chip)
अणु
	chip_ग_लिखो(chip, TEA6320_FFR, 0x3f);
	chip_ग_लिखो(chip, TEA6320_FFL, 0x3f);
	chip_ग_लिखो(chip, TEA6320_FRR, 0x3f);
	chip_ग_लिखो(chip, TEA6320_FRL, 0x3f);

	वापस 0;
पूर्ण


/* ---------------------------------------------------------------------- */
/* audio chip descriptions - defines+functions क्रम tda8425                */

#घोषणा TDA8425_VL         0x00  /* volume left */
#घोषणा TDA8425_VR         0x01  /* volume right */
#घोषणा TDA8425_BA         0x02  /* bass */
#घोषणा TDA8425_TR         0x03  /* treble */
#घोषणा TDA8425_S1         0x08  /* चयन functions */
				 /* values क्रम those रेजिस्टरs: */
#घोषणा TDA8425_S1_OFF     0xEE  /* audio off (mute on) */
#घोषणा TDA8425_S1_CH1     0xCE  /* audio channel 1 (mute off) - "linear stereo" mode */
#घोषणा TDA8425_S1_CH2     0xCF  /* audio channel 2 (mute off) - "linear stereo" mode */
#घोषणा TDA8425_S1_MU      0x20  /* mute bit */
#घोषणा TDA8425_S1_STEREO  0x18  /* stereo bits */
#घोषणा TDA8425_S1_STEREO_SPATIAL 0x18 /* spatial stereo */
#घोषणा TDA8425_S1_STEREO_LINEAR  0x08 /* linear stereo */
#घोषणा TDA8425_S1_STEREO_PSEUDO  0x10 /* pseuकरो stereo */
#घोषणा TDA8425_S1_STEREO_MONO    0x00 /* क्रमced mono */
#घोषणा TDA8425_S1_ML      0x06        /* language selector */
#घोषणा TDA8425_S1_ML_SOUND_A 0x02     /* sound a */
#घोषणा TDA8425_S1_ML_SOUND_B 0x04     /* sound b */
#घोषणा TDA8425_S1_ML_STEREO  0x06     /* stereo */
#घोषणा TDA8425_S1_IS      0x01        /* channel selector */


अटल पूर्णांक tda8425_shअगरt10(पूर्णांक val) अणु वापस (val >> 10) | 0xc0; पूर्ण
अटल पूर्णांक tda8425_shअगरt12(पूर्णांक val) अणु वापस (val >> 12) | 0xf0; पूर्ण

अटल व्योम tda8425_setaudmode(काष्ठा CHIPSTATE *chip, पूर्णांक mode)
अणु
	पूर्णांक s1 = chip->shaकरोw.bytes[TDA8425_S1+1] & 0xe1;

	चयन (mode) अणु
	हाल V4L2_TUNER_MODE_LANG1:
		s1 |= TDA8425_S1_ML_SOUND_A;
		s1 |= TDA8425_S1_STEREO_PSEUDO;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG2:
		s1 |= TDA8425_S1_ML_SOUND_B;
		s1 |= TDA8425_S1_STEREO_PSEUDO;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1_LANG2:
		s1 |= TDA8425_S1_ML_STEREO;
		s1 |= TDA8425_S1_STEREO_LINEAR;
		अवरोध;
	हाल V4L2_TUNER_MODE_MONO:
		s1 |= TDA8425_S1_ML_STEREO;
		s1 |= TDA8425_S1_STEREO_MONO;
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
		s1 |= TDA8425_S1_ML_STEREO;
		s1 |= TDA8425_S1_STEREO_SPATIAL;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	chip_ग_लिखो(chip,TDA8425_S1,s1);
पूर्ण


/* ---------------------------------------------------------------------- */
/* audio chip descriptions - defines+functions क्रम pic16c54 (PV951)       */

/* the रेजिस्टरs of 16C54, I2C sub address. */
#घोषणा PIC16C54_REG_KEY_CODE     0x01	       /* Not use. */
#घोषणा PIC16C54_REG_MISC         0x02

/* bit definition of the RESET रेजिस्टर, I2C data. */
#घोषणा PIC16C54_MISC_RESET_REMOTE_CTL 0x01 /* bit 0, Reset to receive the key */
					    /*        code of remote controller */
#घोषणा PIC16C54_MISC_MTS_MAIN         0x02 /* bit 1 */
#घोषणा PIC16C54_MISC_MTS_SAP          0x04 /* bit 2 */
#घोषणा PIC16C54_MISC_MTS_BOTH         0x08 /* bit 3 */
#घोषणा PIC16C54_MISC_SND_MUTE         0x10 /* bit 4, Mute Audio(Line-in and Tuner) */
#घोषणा PIC16C54_MISC_SND_NOTMUTE      0x20 /* bit 5 */
#घोषणा PIC16C54_MISC_SWITCH_TUNER     0x40 /* bit 6	, Switch to Line-in */
#घोषणा PIC16C54_MISC_SWITCH_LINE      0x80 /* bit 7	, Switch to Tuner */

/* ---------------------------------------------------------------------- */
/* audio chip descriptions - defines+functions क्रम TA8874Z                */

/* ग_लिखो 1st byte */
#घोषणा TA8874Z_LED_STE	0x80
#घोषणा TA8874Z_LED_BIL	0x40
#घोषणा TA8874Z_LED_EXT	0x20
#घोषणा TA8874Z_MONO_SET	0x10
#घोषणा TA8874Z_MUTE	0x08
#घोषणा TA8874Z_F_MONO	0x04
#घोषणा TA8874Z_MODE_SUB	0x02
#घोषणा TA8874Z_MODE_MAIN	0x01

/* ग_लिखो 2nd byte */
/*#घोषणा TA8874Z_TI	0x80  */ /* test mode */
#घोषणा TA8874Z_SEPARATION	0x3f
#घोषणा TA8874Z_SEPARATION_DEFAULT	0x10

/* पढ़ो */
#घोषणा TA8874Z_B1	0x80
#घोषणा TA8874Z_B0	0x40
#घोषणा TA8874Z_CHAG_FLAG	0x20

/*
 *        B1 B0
 * mono    L  H
 * stereo  L  L
 * BIL     H  L
 */
अटल पूर्णांक ta8874z_getrxsubchans(काष्ठा CHIPSTATE *chip)
अणु
	पूर्णांक val, mode;

	mode = V4L2_TUNER_SUB_MONO;

	val = chip_पढ़ो(chip);
	अगर (val < 0)
		वापस mode;

	अगर (val & TA8874Z_B1)अणु
		mode |= V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
	पूर्णअन्यथा अगर (!(val & TA8874Z_B0))अणु
		mode = V4L2_TUNER_SUB_STEREO;
	पूर्ण
	/* v4l2_dbg(1, debug, &chip->sd,
		 "ta8874z_getrxsubchans(): raw chip read: 0x%02x, return: 0x%02x\n",
		 val, mode); */
	वापस mode;
पूर्ण

अटल audiocmd ta8874z_stereo = अणु 2, अणु0, TA8874Z_SEPARATION_DEFAULTपूर्णपूर्ण;
अटल audiocmd ta8874z_mono = अणु2, अणु TA8874Z_MONO_SET, TA8874Z_SEPARATION_DEFAULTपूर्णपूर्ण;
अटल audiocmd ta8874z_मुख्य = अणु2, अणु 0, TA8874Z_SEPARATION_DEFAULTपूर्णपूर्ण;
अटल audiocmd ta8874z_sub = अणु2, अणु TA8874Z_MODE_SUB, TA8874Z_SEPARATION_DEFAULTपूर्णपूर्ण;
अटल audiocmd ta8874z_both = अणु2, अणु TA8874Z_MODE_MAIN | TA8874Z_MODE_SUB, TA8874Z_SEPARATION_DEFAULTपूर्णपूर्ण;

अटल व्योम ta8874z_setaudmode(काष्ठा CHIPSTATE *chip, पूर्णांक mode)
अणु
	काष्ठा v4l2_subdev *sd = &chip->sd;
	पूर्णांक update = 1;
	audiocmd *t = शून्य;

	v4l2_dbg(1, debug, sd, "ta8874z_setaudmode(): mode: 0x%02x\n", mode);

	चयन(mode)अणु
	हाल V4L2_TUNER_MODE_MONO:
		t = &ta8874z_mono;
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
		t = &ta8874z_stereo;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1:
		t = &ta8874z_मुख्य;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG2:
		t = &ta8874z_sub;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1_LANG2:
		t = &ta8874z_both;
		अवरोध;
	शेष:
		update = 0;
	पूर्ण

	अगर(update)
		chip_cmd(chip, "TA8874Z", t);
पूर्ण

अटल पूर्णांक ta8874z_checkit(काष्ठा CHIPSTATE *chip)
अणु
	पूर्णांक rc;

	rc = chip_पढ़ो(chip);
	अगर (rc < 0)
		वापस rc;

	वापस ((rc & 0x1f) == 0x1f) ? 1 : 0;
पूर्ण

/* ---------------------------------------------------------------------- */
/* audio chip descriptions - काष्ठा CHIPDESC                              */

/* insmod options to enable/disable inभागidual audio chips */
अटल पूर्णांक tda8425  = 1;
अटल पूर्णांक tda9840  = 1;
अटल पूर्णांक tda9850  = 1;
अटल पूर्णांक tda9855  = 1;
अटल पूर्णांक tda9873  = 1;
अटल पूर्णांक tda9874a = 1;
अटल पूर्णांक tda9875  = 1;
अटल पूर्णांक tea6300;	/* शेष 0 - address clash with msp34xx */
अटल पूर्णांक tea6320;	/* शेष 0 - address clash with msp34xx */
अटल पूर्णांक tea6420  = 1;
अटल पूर्णांक pic16c54 = 1;
अटल पूर्णांक ta8874z;	/* शेष 0 - address clash with tda9840 */

module_param(tda8425, पूर्णांक, 0444);
module_param(tda9840, पूर्णांक, 0444);
module_param(tda9850, पूर्णांक, 0444);
module_param(tda9855, पूर्णांक, 0444);
module_param(tda9873, पूर्णांक, 0444);
module_param(tda9874a, पूर्णांक, 0444);
module_param(tda9875, पूर्णांक, 0444);
module_param(tea6300, पूर्णांक, 0444);
module_param(tea6320, पूर्णांक, 0444);
module_param(tea6420, पूर्णांक, 0444);
module_param(pic16c54, पूर्णांक, 0444);
module_param(ta8874z, पूर्णांक, 0444);

अटल काष्ठा CHIPDESC chiplist[] = अणु
	अणु
		.name       = "tda9840",
		.insmoकरोpt  = &tda9840,
		.addr_lo    = I2C_ADDR_TDA9840 >> 1,
		.addr_hi    = I2C_ADDR_TDA9840 >> 1,
		.रेजिस्टरs  = 5,
		.flags      = CHIP_NEED_CHECKMODE,

		/* callbacks */
		.checkit    = tda9840_checkit,
		.getrxsubchans = tda9840_getrxsubchans,
		.setaudmode = tda9840_setaudmode,

		.init       = अणु 2, अणु TDA9840_TEST, TDA9840_TEST_INT1SN
				/* ,TDA9840_SW, TDA9840_MONO */पूर्ण पूर्ण
	पूर्ण,
	अणु
		.name       = "tda9873h",
		.insmoकरोpt  = &tda9873,
		.addr_lo    = I2C_ADDR_TDA985x_L >> 1,
		.addr_hi    = I2C_ADDR_TDA985x_H >> 1,
		.रेजिस्टरs  = 3,
		.flags      = CHIP_HAS_INPUTSEL | CHIP_NEED_CHECKMODE,

		/* callbacks */
		.checkit    = tda9873_checkit,
		.getrxsubchans = tda9873_getrxsubchans,
		.setaudmode = tda9873_setaudmode,

		.init       = अणु 4, अणु TDA9873_SW, 0xa4, 0x06, 0x03 पूर्ण पूर्ण,
		.inputreg   = TDA9873_SW,
		.inpuपंचांगute  = TDA9873_MUTE | TDA9873_AUTOMUTE,
		.inpuपंचांगap   = अणु0xa0, 0xa2, 0xa0, 0xa0पूर्ण,
		.inpuपंचांगask  = TDA9873_INP_MASK|TDA9873_MUTE|TDA9873_AUTOMUTE,

	पूर्ण,
	अणु
		.name       = "tda9874h/a",
		.insmoकरोpt  = &tda9874a,
		.addr_lo    = I2C_ADDR_TDA9874 >> 1,
		.addr_hi    = I2C_ADDR_TDA9874 >> 1,
		.flags      = CHIP_NEED_CHECKMODE,

		/* callbacks */
		.initialize = tda9874a_initialize,
		.checkit    = tda9874a_checkit,
		.getrxsubchans = tda9874a_getrxsubchans,
		.setaudmode = tda9874a_setaudmode,
	पूर्ण,
	अणु
		.name       = "tda9875",
		.insmoकरोpt  = &tda9875,
		.addr_lo    = I2C_ADDR_TDA9875 >> 1,
		.addr_hi    = I2C_ADDR_TDA9875 >> 1,
		.flags      = CHIP_HAS_VOLUME | CHIP_HAS_BASSTREBLE,

		/* callbacks */
		.initialize = tda9875_initialize,
		.checkit    = tda9875_checkit,
		.volfunc    = tda9875_volume,
		.bassfunc   = tda9875_bass,
		.treblefunc = tda9875_treble,
		.leftreg    = TDA9875_MVL,
		.rightreg   = TDA9875_MVR,
		.bassreg    = TDA9875_MBA,
		.treblereg  = TDA9875_MTR,
		.volinit    = 58880,
	पूर्ण,
	अणु
		.name       = "tda9850",
		.insmoकरोpt  = &tda9850,
		.addr_lo    = I2C_ADDR_TDA985x_L >> 1,
		.addr_hi    = I2C_ADDR_TDA985x_H >> 1,
		.रेजिस्टरs  = 11,

		.getrxsubchans = tda985x_getrxsubchans,
		.setaudmode = tda985x_setaudmode,

		.init       = अणु 8, अणु TDA9850_C4, 0x08, 0x08, TDA985x_STEREO, 0x07, 0x10, 0x10, 0x03 पूर्ण पूर्ण
	पूर्ण,
	अणु
		.name       = "tda9855",
		.insmoकरोpt  = &tda9855,
		.addr_lo    = I2C_ADDR_TDA985x_L >> 1,
		.addr_hi    = I2C_ADDR_TDA985x_H >> 1,
		.रेजिस्टरs  = 11,
		.flags      = CHIP_HAS_VOLUME | CHIP_HAS_BASSTREBLE,

		.leftreg    = TDA9855_VL,
		.rightreg   = TDA9855_VR,
		.bassreg    = TDA9855_BA,
		.treblereg  = TDA9855_TR,

		/* callbacks */
		.volfunc    = tda9855_volume,
		.bassfunc   = tda9855_bass,
		.treblefunc = tda9855_treble,
		.getrxsubchans = tda985x_getrxsubchans,
		.setaudmode = tda985x_setaudmode,

		.init       = अणु 12, अणु 0, 0x6f, 0x6f, 0x0e, 0x07<<1, 0x8<<2,
				    TDA9855_MUTE | TDA9855_AVL | TDA9855_LOUD | TDA9855_INT,
				    TDA985x_STEREO | TDA9855_LINEAR | TDA9855_TZCM | TDA9855_VZCM,
				    0x07, 0x10, 0x10, 0x03 पूर्णपूर्ण
	पूर्ण,
	अणु
		.name       = "tea6300",
		.insmoकरोpt  = &tea6300,
		.addr_lo    = I2C_ADDR_TEA6300 >> 1,
		.addr_hi    = I2C_ADDR_TEA6300 >> 1,
		.रेजिस्टरs  = 6,
		.flags      = CHIP_HAS_VOLUME | CHIP_HAS_BASSTREBLE | CHIP_HAS_INPUTSEL,

		.leftreg    = TEA6300_VR,
		.rightreg   = TEA6300_VL,
		.bassreg    = TEA6300_BA,
		.treblereg  = TEA6300_TR,

		/* callbacks */
		.volfunc    = tea6300_shअगरt10,
		.bassfunc   = tea6300_shअगरt12,
		.treblefunc = tea6300_shअगरt12,

		.inputreg   = TEA6300_S,
		.inpuपंचांगap   = अणु TEA6300_S_SA, TEA6300_S_SB, TEA6300_S_SC पूर्ण,
		.inpuपंचांगute  = TEA6300_S_GMU,
	पूर्ण,
	अणु
		.name       = "tea6320",
		.insmoकरोpt  = &tea6320,
		.addr_lo    = I2C_ADDR_TEA6300 >> 1,
		.addr_hi    = I2C_ADDR_TEA6300 >> 1,
		.रेजिस्टरs  = 8,
		.flags      = CHIP_HAS_VOLUME | CHIP_HAS_BASSTREBLE | CHIP_HAS_INPUTSEL,

		.leftreg    = TEA6320_V,
		.rightreg   = TEA6320_V,
		.bassreg    = TEA6320_BA,
		.treblereg  = TEA6320_TR,

		/* callbacks */
		.initialize = tea6320_initialize,
		.volfunc    = tea6320_volume,
		.bassfunc   = tea6320_shअगरt11,
		.treblefunc = tea6320_shअगरt11,

		.inputreg   = TEA6320_S,
		.inpuपंचांगap   = अणु TEA6320_S_SA, TEA6420_S_SB, TEA6300_S_SC, TEA6320_S_SD पूर्ण,
		.inpuपंचांगute  = TEA6300_S_GMU,
	पूर्ण,
	अणु
		.name       = "tea6420",
		.insmoकरोpt  = &tea6420,
		.addr_lo    = I2C_ADDR_TEA6420 >> 1,
		.addr_hi    = I2C_ADDR_TEA6420 >> 1,
		.रेजिस्टरs  = 1,
		.flags      = CHIP_HAS_INPUTSEL,

		.inputreg   = -1,
		.inpuपंचांगap   = अणु TEA6420_S_SA, TEA6420_S_SB, TEA6420_S_SC पूर्ण,
		.inpuपंचांगute  = TEA6420_S_GMU,
		.inpuपंचांगask  = 0x07,
	पूर्ण,
	अणु
		.name       = "tda8425",
		.insmoकरोpt  = &tda8425,
		.addr_lo    = I2C_ADDR_TDA8425 >> 1,
		.addr_hi    = I2C_ADDR_TDA8425 >> 1,
		.रेजिस्टरs  = 9,
		.flags      = CHIP_HAS_VOLUME | CHIP_HAS_BASSTREBLE | CHIP_HAS_INPUTSEL,

		.leftreg    = TDA8425_VL,
		.rightreg   = TDA8425_VR,
		.bassreg    = TDA8425_BA,
		.treblereg  = TDA8425_TR,

		/* callbacks */
		.volfunc    = tda8425_shअगरt10,
		.bassfunc   = tda8425_shअगरt12,
		.treblefunc = tda8425_shअगरt12,
		.setaudmode = tda8425_setaudmode,

		.inputreg   = TDA8425_S1,
		.inpuपंचांगap   = अणु TDA8425_S1_CH1, TDA8425_S1_CH1, TDA8425_S1_CH1 पूर्ण,
		.inpuपंचांगute  = TDA8425_S1_OFF,

	पूर्ण,
	अणु
		.name       = "pic16c54 (PV951)",
		.insmoकरोpt  = &pic16c54,
		.addr_lo    = I2C_ADDR_PIC16C54 >> 1,
		.addr_hi    = I2C_ADDR_PIC16C54>> 1,
		.रेजिस्टरs  = 2,
		.flags      = CHIP_HAS_INPUTSEL,

		.inputreg   = PIC16C54_REG_MISC,
		.inpuपंचांगap   = अणुPIC16C54_MISC_SND_NOTMUTE|PIC16C54_MISC_SWITCH_TUNER,
			     PIC16C54_MISC_SND_NOTMUTE|PIC16C54_MISC_SWITCH_LINE,
			     PIC16C54_MISC_SND_NOTMUTE|PIC16C54_MISC_SWITCH_LINE,
			     PIC16C54_MISC_SND_MUTEपूर्ण,
		.inpuपंचांगute  = PIC16C54_MISC_SND_MUTE,
	पूर्ण,
	अणु
		.name       = "ta8874z",
		.checkit    = ta8874z_checkit,
		.insmoकरोpt  = &ta8874z,
		.addr_lo    = I2C_ADDR_TDA9840 >> 1,
		.addr_hi    = I2C_ADDR_TDA9840 >> 1,
		.रेजिस्टरs  = 2,

		/* callbacks */
		.getrxsubchans = ta8874z_getrxsubchans,
		.setaudmode = ta8874z_setaudmode,

		.init       = अणु2, अणु TA8874Z_MONO_SET, TA8874Z_SEPARATION_DEFAULTपूर्णपूर्ण,
	पूर्ण,
	अणु .name = शून्य पूर्ण /* खातापूर्ण */
पूर्ण;


/* ---------------------------------------------------------------------- */

अटल पूर्णांक tvaudio_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा CHIPSTATE *chip = to_state(sd);
	काष्ठा CHIPDESC *desc = chip->desc;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		chip->muted = ctrl->val;
		अगर (chip->muted)
			chip_ग_लिखो_masked(chip,desc->inputreg,desc->inpuपंचांगute,desc->inpuपंचांगask);
		अन्यथा
			chip_ग_लिखो_masked(chip,desc->inputreg,
					desc->inpuपंचांगap[chip->input],desc->inpuपंचांगask);
		वापस 0;
	हाल V4L2_CID_AUDIO_VOLUME: अणु
		u32 volume, balance;
		u32 left, right;

		volume = chip->volume->val;
		balance = chip->balance->val;
		left = (min(65536U - balance, 32768U) * volume) / 32768U;
		right = (min(balance, 32768U) * volume) / 32768U;

		chip_ग_लिखो(chip, desc->leftreg, desc->volfunc(left));
		chip_ग_लिखो(chip, desc->rightreg, desc->volfunc(right));
		वापस 0;
	पूर्ण
	हाल V4L2_CID_AUDIO_BASS:
		chip_ग_लिखो(chip, desc->bassreg, desc->bassfunc(ctrl->val));
		वापस 0;
	हाल V4L2_CID_AUDIO_TREBLE:
		chip_ग_लिखो(chip, desc->treblereg, desc->treblefunc(ctrl->val));
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण


/* ---------------------------------------------------------------------- */
/* video4linux पूर्णांकerface                                                  */

अटल पूर्णांक tvaudio_s_radio(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा CHIPSTATE *chip = to_state(sd);

	chip->radio = 1;
	/* del_समयr(&chip->wt); */
	वापस 0;
पूर्ण

अटल पूर्णांक tvaudio_s_routing(काष्ठा v4l2_subdev *sd,
			     u32 input, u32 output, u32 config)
अणु
	काष्ठा CHIPSTATE *chip = to_state(sd);
	काष्ठा CHIPDESC *desc = chip->desc;

	अगर (!(desc->flags & CHIP_HAS_INPUTSEL))
		वापस 0;
	अगर (input >= 4)
		वापस -EINVAL;
	/* There are four inमाला_दो: tuner, radio, बाह्य and पूर्णांकern. */
	chip->input = input;
	अगर (chip->muted)
		वापस 0;
	chip_ग_लिखो_masked(chip, desc->inputreg,
			desc->inpuपंचांगap[chip->input], desc->inpuपंचांगask);
	वापस 0;
पूर्ण

अटल पूर्णांक tvaudio_s_tuner(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा CHIPSTATE *chip = to_state(sd);
	काष्ठा CHIPDESC *desc = chip->desc;

	अगर (!desc->setaudmode)
		वापस 0;
	अगर (chip->radio)
		वापस 0;

	चयन (vt->audmode) अणु
	हाल V4L2_TUNER_MODE_MONO:
	हाल V4L2_TUNER_MODE_STEREO:
	हाल V4L2_TUNER_MODE_LANG1:
	हाल V4L2_TUNER_MODE_LANG2:
	हाल V4L2_TUNER_MODE_LANG1_LANG2:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	chip->audmode = vt->audmode;

	अगर (chip->thपढ़ो)
		wake_up_process(chip->thपढ़ो);
	अन्यथा
		desc->setaudmode(chip, vt->audmode);

	वापस 0;
पूर्ण

अटल पूर्णांक tvaudio_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा CHIPSTATE *chip = to_state(sd);
	काष्ठा CHIPDESC *desc = chip->desc;

	अगर (!desc->getrxsubchans)
		वापस 0;
	अगर (chip->radio)
		वापस 0;

	vt->audmode = chip->audmode;
	vt->rxsubchans = desc->getrxsubchans(chip);
	vt->capability |= V4L2_TUNER_CAP_STEREO |
		V4L2_TUNER_CAP_LANG1 | V4L2_TUNER_CAP_LANG2;

	वापस 0;
पूर्ण

अटल पूर्णांक tvaudio_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा CHIPSTATE *chip = to_state(sd);

	chip->radio = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक tvaudio_s_frequency(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_frequency *freq)
अणु
	काष्ठा CHIPSTATE *chip = to_state(sd);
	काष्ठा CHIPDESC *desc = chip->desc;

	/* For chips that provide getrxsubchans and setaudmode, and करोesn't
	   स्वतःmatically follows the stereo carrier, a kthपढ़ो is
	   created to set the audio standard. In this हाल, when then
	   the video channel is changed, tvaudio starts on MONO mode.
	   After रुकोing क्रम 2 seconds, the kernel thपढ़ो is called,
	   to follow whatever audio standard is poपूर्णांकed by the
	   audio carrier.
	 */
	अगर (chip->thपढ़ो) अणु
		desc->setaudmode(chip, V4L2_TUNER_MODE_MONO);
		chip->prevmode = -1; /* reset previous mode */
		mod_समयr(&chip->wt, jअगरfies+msecs_to_jअगरfies(2000));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tvaudio_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा CHIPSTATE *chip = to_state(sd);
	काष्ठा CHIPDESC *desc = chip->desc;

	v4l2_info(sd, "Chip: %s\n", desc->name);
	v4l2_ctrl_handler_log_status(&chip->hdl, sd->name);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops tvaudio_ctrl_ops = अणु
	.s_ctrl = tvaudio_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops tvaudio_core_ops = अणु
	.log_status = tvaudio_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops tvaudio_tuner_ops = अणु
	.s_radio = tvaudio_s_radio,
	.s_frequency = tvaudio_s_frequency,
	.s_tuner = tvaudio_s_tuner,
	.g_tuner = tvaudio_g_tuner,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_audio_ops tvaudio_audio_ops = अणु
	.s_routing = tvaudio_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops tvaudio_video_ops = अणु
	.s_std = tvaudio_s_std,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tvaudio_ops = अणु
	.core = &tvaudio_core_ops,
	.tuner = &tvaudio_tuner_ops,
	.audio = &tvaudio_audio_ops,
	.video = &tvaudio_video_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */


/* i2c registration                                                       */

अटल पूर्णांक tvaudio_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा CHIPSTATE *chip;
	काष्ठा CHIPDESC  *desc;
	काष्ठा v4l2_subdev *sd;

	अगर (debug) अणु
		prपूर्णांकk(KERN_INFO "tvaudio: TV audio decoder + audio/video mux driver\n");
		prपूर्णांकk(KERN_INFO "tvaudio: known chips: ");
		क्रम (desc = chiplist; desc->name != शून्य; desc++)
			prपूर्णांकk(KERN_CONT "%s%s",
			       (desc == chiplist) ? "" : ", ", desc->name);
		prपूर्णांकk(KERN_CONT "\n");
	पूर्ण

	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;
	sd = &chip->sd;
	v4l2_i2c_subdev_init(sd, client, &tvaudio_ops);

	/* find description क्रम the chip */
	v4l2_dbg(1, debug, sd, "chip found @ 0x%x\n", client->addr<<1);
	क्रम (desc = chiplist; desc->name != शून्य; desc++) अणु
		अगर (0 == *(desc->insmoकरोpt))
			जारी;
		अगर (client->addr < desc->addr_lo ||
		    client->addr > desc->addr_hi)
			जारी;
		अगर (desc->checkit && !desc->checkit(chip))
			जारी;
		अवरोध;
	पूर्ण
	अगर (desc->name == शून्य) अणु
		v4l2_dbg(1, debug, sd, "no matching chip description found\n");
		वापस -EIO;
	पूर्ण
	v4l2_info(sd, "%s found @ 0x%x (%s)\n", desc->name, client->addr<<1, client->adapter->name);
	अगर (desc->flags) अणु
		v4l2_dbg(1, debug, sd, "matches:%s%s%s.\n",
			(desc->flags & CHIP_HAS_VOLUME)     ? " volume"      : "",
			(desc->flags & CHIP_HAS_BASSTREBLE) ? " bass/treble" : "",
			(desc->flags & CHIP_HAS_INPUTSEL)   ? " audiomux"    : "");
	पूर्ण

	/* fill required data काष्ठाures */
	अगर (!id)
		strscpy(client->name, desc->name, I2C_NAME_SIZE);
	chip->desc = desc;
	chip->shaकरोw.count = desc->रेजिस्टरs+1;
	chip->prevmode = -1;
	chip->audmode = V4L2_TUNER_MODE_LANG1;

	/* initialization  */
	अगर (desc->initialize != शून्य)
		desc->initialize(chip);
	अन्यथा
		chip_cmd(chip, "init", &desc->init);

	v4l2_ctrl_handler_init(&chip->hdl, 5);
	अगर (desc->flags & CHIP_HAS_INPUTSEL)
		v4l2_ctrl_new_std(&chip->hdl, &tvaudio_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	अगर (desc->flags & CHIP_HAS_VOLUME) अणु
		अगर (!desc->volfunc) अणु
			/* This shouldn't be happen. Warn user, but keep working
			   without volume controls
			 */
			v4l2_info(sd, "volume callback undefined!\n");
			desc->flags &= ~CHIP_HAS_VOLUME;
		पूर्ण अन्यथा अणु
			chip->volume = v4l2_ctrl_new_std(&chip->hdl,
				&tvaudio_ctrl_ops, V4L2_CID_AUDIO_VOLUME,
				0, 65535, 65535 / 100,
				desc->volinit ? desc->volinit : 65535);
			chip->balance = v4l2_ctrl_new_std(&chip->hdl,
				&tvaudio_ctrl_ops, V4L2_CID_AUDIO_BALANCE,
				0, 65535, 65535 / 100, 32768);
			v4l2_ctrl_cluster(2, &chip->volume);
		पूर्ण
	पूर्ण
	अगर (desc->flags & CHIP_HAS_BASSTREBLE) अणु
		अगर (!desc->bassfunc || !desc->treblefunc) अणु
			/* This shouldn't be happen. Warn user, but keep working
			   without bass/treble controls
			 */
			v4l2_info(sd, "bass/treble callbacks undefined!\n");
			desc->flags &= ~CHIP_HAS_BASSTREBLE;
		पूर्ण अन्यथा अणु
			v4l2_ctrl_new_std(&chip->hdl,
				&tvaudio_ctrl_ops, V4L2_CID_AUDIO_BASS,
				0, 65535, 65535 / 100,
				desc->bassinit ? desc->bassinit : 32768);
			v4l2_ctrl_new_std(&chip->hdl,
				&tvaudio_ctrl_ops, V4L2_CID_AUDIO_TREBLE,
				0, 65535, 65535 / 100,
				desc->trebleinit ? desc->trebleinit : 32768);
		पूर्ण
	पूर्ण

	sd->ctrl_handler = &chip->hdl;
	अगर (chip->hdl.error) अणु
		पूर्णांक err = chip->hdl.error;

		v4l2_ctrl_handler_मुक्त(&chip->hdl);
		वापस err;
	पूर्ण
	/* set controls to the शेष values */
	v4l2_ctrl_handler_setup(&chip->hdl);

	chip->thपढ़ो = शून्य;
	समयr_setup(&chip->wt, chip_thपढ़ो_wake, 0);
	अगर (desc->flags & CHIP_NEED_CHECKMODE) अणु
		अगर (!desc->getrxsubchans || !desc->setaudmode) अणु
			/* This shouldn't be happen. Warn user, but keep working
			   without kthपढ़ो
			 */
			v4l2_info(sd, "set/get mode callbacks undefined!\n");
			वापस 0;
		पूर्ण
		/* start async thपढ़ो */
		chip->thपढ़ो = kthपढ़ो_run(chip_thपढ़ो, chip, "%s",
					   client->name);
		अगर (IS_ERR(chip->thपढ़ो)) अणु
			v4l2_warn(sd, "failed to create kthread\n");
			chip->thपढ़ो = शून्य;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tvaudio_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा CHIPSTATE *chip = to_state(sd);

	del_समयr_sync(&chip->wt);
	अगर (chip->thपढ़ो) अणु
		/* shutकरोwn async thपढ़ो */
		kthपढ़ो_stop(chip->thपढ़ो);
		chip->thपढ़ो = शून्य;
	पूर्ण

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&chip->hdl);
	वापस 0;
पूर्ण

/* This driver supports many devices and the idea is to let the driver
   detect which device is present. So rather than listing all supported
   devices here, we pretend to support a single, fake device type. */
अटल स्थिर काष्ठा i2c_device_id tvaudio_id[] = अणु
	अणु "tvaudio", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tvaudio_id);

अटल काष्ठा i2c_driver tvaudio_driver = अणु
	.driver = अणु
		.name	= "tvaudio",
	पूर्ण,
	.probe		= tvaudio_probe,
	.हटाओ		= tvaudio_हटाओ,
	.id_table	= tvaudio_id,
पूर्ण;

module_i2c_driver(tvaudio_driver);
