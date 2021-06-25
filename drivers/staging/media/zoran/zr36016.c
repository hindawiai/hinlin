<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Zoran ZR36016 basic configuration functions
 *
 * Copyright (C) 2001 Wolfgang Scherr <scherr@net4you.at>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>

/* headerfile of this module */
#समावेश "zr36016.h"

/* codec io API */
#समावेश "videocodec.h"

/* it करोesn't make sense to have more than 20 or so,
  just to prevent some unwanted loops */
#घोषणा MAX_CODECS 20

/* amount of chips attached via this driver */
अटल पूर्णांक zr36016_codecs;

/* debugging is available via module parameter */
अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0-4)");

#घोषणा dprपूर्णांकk(num, क्रमmat, args...) \
	करो अणु \
		अगर (debug >= num) \
			prपूर्णांकk(क्रमmat, ##args); \
	पूर्ण जबतक (0)

/* =========================================================================
   Local hardware I/O functions:

   पढ़ो/ग_लिखो via codec layer (रेजिस्टरs are located in the master device)
   ========================================================================= */

/* पढ़ो and ग_लिखो functions */
अटल u8 zr36016_पढ़ो(काष्ठा zr36016 *ptr, u16 reg)
अणु
	u8 value = 0;

	/* just in हाल something is wrong... */
	अगर (ptr->codec->master_data->पढ़ोreg)
		value = (ptr->codec->master_data->पढ़ोreg(ptr->codec, reg)) & 0xFF;
	अन्यथा
		pr_err("%s: invalid I/O setup, nothing read!\n", ptr->name);

	dprपूर्णांकk(4, "%s: reading from 0x%04x: %02x\n", ptr->name, reg, value);

	वापस value;
पूर्ण

अटल व्योम zr36016_ग_लिखो(काष्ठा zr36016 *ptr, u16 reg, u8 value)
अणु
	dprपूर्णांकk(4, "%s: writing 0x%02x to 0x%04x\n", ptr->name, value, reg);

	// just in हाल something is wrong...
	अगर (ptr->codec->master_data->ग_लिखोreg)
		ptr->codec->master_data->ग_लिखोreg(ptr->codec, reg, value);
	अन्यथा
		pr_err("%s: invalid I/O setup, nothing written!\n", ptr->name);
पूर्ण

/* indirect पढ़ो and ग_लिखो functions */
/* the 016 supports स्वतः-addr-increment, but
 * writing it all समय cost not much and is safer... */
अटल u8 zr36016_पढ़ोi(काष्ठा zr36016 *ptr, u16 reg)
अणु
	u8 value = 0;

	/* just in हाल something is wrong... */
	अगर ((ptr->codec->master_data->ग_लिखोreg) && (ptr->codec->master_data->पढ़ोreg)) अणु
		ptr->codec->master_data->ग_लिखोreg(ptr->codec, ZR016_IADDR, reg & 0x0F);	// ADDR
		value = (ptr->codec->master_data->पढ़ोreg(ptr->codec, ZR016_IDATA)) & 0xFF;	// DATA
	पूर्ण अन्यथा अणु
		pr_err("%s: invalid I/O setup, nothing read (i)!\n", ptr->name);
	पूर्ण

	dprपूर्णांकk(4, "%s: reading indirect from 0x%04x: %02x\n", ptr->name, reg, value);
	वापस value;
पूर्ण

अटल व्योम zr36016_ग_लिखोi(काष्ठा zr36016 *ptr, u16 reg, u8 value)
अणु
	dprपूर्णांकk(4, "%s: writing indirect 0x%02x to 0x%04x\n", ptr->name,
		value, reg);

	/* just in हाल something is wrong... */
	अगर (ptr->codec->master_data->ग_लिखोreg) अणु
		ptr->codec->master_data->ग_लिखोreg(ptr->codec, ZR016_IADDR, reg & 0x0F);	// ADDR
		ptr->codec->master_data->ग_लिखोreg(ptr->codec, ZR016_IDATA, value & 0x0FF);	// DATA
	पूर्ण अन्यथा अणु
		pr_err("%s: invalid I/O setup, nothing written (i)!\n", ptr->name);
	पूर्ण
पूर्ण

/* =========================================================================
   Local helper function:

   version पढ़ो
   ========================================================================= */

/* version kept in dataकाष्ठाure */
अटल u8 zr36016_पढ़ो_version(काष्ठा zr36016 *ptr)
अणु
	ptr->version = zr36016_पढ़ो(ptr, 0) >> 4;
	वापस ptr->version;
पूर्ण

/* =========================================================================
   Local helper function:

   basic test of "connectivity", ग_लिखोs/पढ़ोs to/from PAX-Lo रेजिस्टर
   ========================================================================= */

अटल पूर्णांक zr36016_basic_test(काष्ठा zr36016 *ptr)
अणु
	अगर (debug) अणु
		पूर्णांक i;

		zr36016_ग_लिखोi(ptr, ZR016I_PAX_LO, 0x55);
		dprपूर्णांकk(1, KERN_INFO "%s: registers: ", ptr->name);
		क्रम (i = 0; i <= 0x0b; i++)
			dprपूर्णांकk(1, "%02x ", zr36016_पढ़ोi(ptr, i));
		dprपूर्णांकk(1, "\n");
	पूर्ण
	// क्रम testing just ग_लिखो 0, then the शेष value to a रेजिस्टर and पढ़ो
	// it back in both हालs
	zr36016_ग_लिखोi(ptr, ZR016I_PAX_LO, 0x00);
	अगर (zr36016_पढ़ोi(ptr, ZR016I_PAX_LO) != 0x0) अणु
		pr_err("%s: attach failed, can't connect to vfe processor!\n", ptr->name);
		वापस -ENXIO;
	पूर्ण
	zr36016_ग_लिखोi(ptr, ZR016I_PAX_LO, 0x0d0);
	अगर (zr36016_पढ़ोi(ptr, ZR016I_PAX_LO) != 0x0d0) अणु
		pr_err("%s: attach failed, can't connect to vfe processor!\n", ptr->name);
		वापस -ENXIO;
	पूर्ण
	// we allow version numbers from 0-3, should be enough, though
	zr36016_पढ़ो_version(ptr);
	अगर (ptr->version & 0x0c) अणु
		pr_err("%s: attach failed, suspicious version %d found...\n", ptr->name,
		       ptr->version);
		वापस -ENXIO;
	पूर्ण

	वापस 0;		/* looks good! */
पूर्ण

/* =========================================================================
   Local helper function:

   simple loop क्रम pushing the init datasets - NO USE --
   ========================================================================= */

#अगर 0
अटल पूर्णांक zr36016_pushit(काष्ठा zr36016 *ptr,
			  u16             startreg,
			   u16             len,
			   स्थिर अक्षर     *data)
अणु
	पूर्णांक i = 0;

	dprपूर्णांकk(4, "%s: write data block to 0x%04x (len=%d)\n",
		ptr->name, startreg, len);
	जबतक (i < len) अणु
		zr36016_ग_लिखोi(ptr, startreg++,  data[i++]);
	पूर्ण

	वापस i;
पूर्ण
#पूर्ण_अगर

/* =========================================================================
   Basic datasets & init:

   //TODO//
   ========================================================================= */

अटल व्योम zr36016_init(काष्ठा zr36016 *ptr)
अणु
	// stop any processing
	zr36016_ग_लिखो(ptr, ZR016_GOSTOP, 0);

	// mode setup (yuv422 in and out, compression/expansuon due to mode)
	zr36016_ग_लिखो(ptr, ZR016_MODE,
		      ZR016_YUV422 | ZR016_YUV422_YUV422 |
		      (ptr->mode == CODEC_DO_COMPRESSION ?
		       ZR016_COMPRESSION : ZR016_EXPANSION));

	// misc setup
	zr36016_ग_लिखोi(ptr, ZR016I_SETUP1,
		       (ptr->xdec ? (ZR016_HRFL | ZR016_HORZ) : 0) |
		       (ptr->ydec ? ZR016_VERT : 0) | ZR016_CNTI);
	zr36016_ग_लिखोi(ptr, ZR016I_SETUP2, ZR016_CCIR);

	// Winकरोw setup
	// (no extra offset क्रम now, norm defines offset, शेष width height)
	zr36016_ग_लिखोi(ptr, ZR016I_PAX_HI, ptr->width >> 8);
	zr36016_ग_लिखोi(ptr, ZR016I_PAX_LO, ptr->width & 0xFF);
	zr36016_ग_लिखोi(ptr, ZR016I_PAY_HI, ptr->height >> 8);
	zr36016_ग_लिखोi(ptr, ZR016I_PAY_LO, ptr->height & 0xFF);
	zr36016_ग_लिखोi(ptr, ZR016I_NAX_HI, ptr->xoff >> 8);
	zr36016_ग_लिखोi(ptr, ZR016I_NAX_LO, ptr->xoff & 0xFF);
	zr36016_ग_लिखोi(ptr, ZR016I_NAY_HI, ptr->yoff >> 8);
	zr36016_ग_लिखोi(ptr, ZR016I_NAY_LO, ptr->yoff & 0xFF);

	/* shall we जारी now, please? */
	zr36016_ग_लिखो(ptr, ZR016_GOSTOP, 1);
पूर्ण

/* =========================================================================
   CODEC API FUNCTIONS

   this functions are accessed by the master via the API काष्ठाure
   ========================================================================= */

/* set compression/expansion mode and launches codec -
   this should be the last call from the master beक्रमe starting processing */
अटल पूर्णांक zr36016_set_mode(काष्ठा videocodec *codec, पूर्णांक mode)
अणु
	काष्ठा zr36016 *ptr = (काष्ठा zr36016 *)codec->data;

	dprपूर्णांकk(2, "%s: set_mode %d call\n", ptr->name, mode);

	अगर ((mode != CODEC_DO_EXPANSION) && (mode != CODEC_DO_COMPRESSION))
		वापस -EINVAL;

	ptr->mode = mode;
	zr36016_init(ptr);

	वापस 0;
पूर्ण

/* set picture size */
अटल पूर्णांक zr36016_set_video(काष्ठा videocodec *codec, स्थिर काष्ठा tvnorm *norm,
			     काष्ठा vfe_settings *cap, काष्ठा vfe_polarity *pol)
अणु
	काष्ठा zr36016 *ptr = (काष्ठा zr36016 *)codec->data;

	dprपूर्णांकk(2, "%s: set_video %d.%d, %d/%d-%dx%d (0x%x) call\n",
		ptr->name, norm->h_start, norm->v_start,
		cap->x, cap->y, cap->width, cap->height,
		cap->decimation);

	/* अगर () वापस -EINVAL;
	 * trust the master driver that it knows what it करोes - so
	 * we allow invalid startx/y क्रम now ... */
	ptr->width = cap->width;
	ptr->height = cap->height;
	/* (Ronald) This is ugly. zoran_device.c, line 387
	 * alपढ़ोy mentions what happens अगर h_start is even
	 * (blue faces, etc., cr/cb inversed). There's probably
	 * some good reason why h_start is 0 instead of 1, so I'm
	 * leaving it to this क्रम now, but really... This can be
	 * करोne a lot simpler */
	ptr->xoff = (norm->h_start ? norm->h_start : 1) + cap->x;
	/* Something to note here (I करोn't understand it), setting
	 * v_start too high will cause the codec to 'not work'. I
	 * really करोn't get it. values of 16 (v_start) alपढ़ोy अवरोध
	 * it here. Just '0' seems to work. More testing needed! */
	ptr->yoff = norm->v_start + cap->y;
	/* (Ronald) dzjeeh, can't this thing करो hor_decimation = 4? */
	ptr->xdec = ((cap->decimation & 0xff) == 1) ? 0 : 1;
	ptr->ydec = (((cap->decimation >> 8) & 0xff) == 1) ? 0 : 1;

	वापस 0;
पूर्ण

/* additional control functions */
अटल पूर्णांक zr36016_control(काष्ठा videocodec *codec, पूर्णांक type, पूर्णांक size, व्योम *data)
अणु
	काष्ठा zr36016 *ptr = (काष्ठा zr36016 *)codec->data;
	पूर्णांक *ival = (पूर्णांक *)data;

	dprपूर्णांकk(2, "%s: control %d call with %d byte\n", ptr->name, type, size);

	चयन (type) अणु
	हाल CODEC_G_STATUS:	/* get last status - we करोn't know it ... */
		अगर (size != माप(पूर्णांक))
			वापस -EFAULT;
		*ival = 0;
		अवरोध;

	हाल CODEC_G_CODEC_MODE:
		अगर (size != माप(पूर्णांक))
			वापस -EFAULT;
		*ival = 0;
		अवरोध;

	हाल CODEC_S_CODEC_MODE:
		अगर (size != माप(पूर्णांक))
			वापस -EFAULT;
		अगर (*ival != 0)
			वापस -EINVAL;
		/* not needed, करो nothing */
		वापस 0;

	हाल CODEC_G_VFE:
	हाल CODEC_S_VFE:
		वापस 0;

	हाल CODEC_S_MMAP:
		/* not available, give an error */
		वापस -ENXIO;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस size;
पूर्ण

/* =========================================================================
   Exit and unरेजिस्टर function:

   Deinitializes Zoran's JPEG processor
   ========================================================================= */

अटल पूर्णांक zr36016_unset(काष्ठा videocodec *codec)
अणु
	काष्ठा zr36016 *ptr = codec->data;

	अगर (ptr) अणु
		/* करो wee need some codec deinit here, too ???? */

		dprपूर्णांकk(1, "%s: finished codec #%d\n", ptr->name, ptr->num);
		kमुक्त(ptr);
		codec->data = शून्य;

		zr36016_codecs--;
		वापस 0;
	पूर्ण

	वापस -EFAULT;
पूर्ण

/* =========================================================================
   Setup and registry function:

   Initializes Zoran's JPEG processor

   Also sets pixel size, average code size, mode (compr./decompr.)
   (the given size is determined by the processor with the video पूर्णांकerface)
   ========================================================================= */

अटल पूर्णांक zr36016_setup(काष्ठा videocodec *codec)
अणु
	काष्ठा zr36016 *ptr;
	पूर्णांक res;

	dprपूर्णांकk(2, "zr36016: initializing VFE subsystem #%d.\n", zr36016_codecs);

	अगर (zr36016_codecs == MAX_CODECS) अणु
		pr_err("zr36016: Can't attach more codecs!\n");
		वापस -ENOSPC;
	पूर्ण
	//mem काष्ठाure init
	codec->data = ptr = kzalloc(माप(काष्ठा zr36016), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	snम_लिखो(ptr->name, माप(ptr->name), "zr36016[%d]", zr36016_codecs);
	ptr->num = zr36016_codecs++;
	ptr->codec = codec;

	//testing
	res = zr36016_basic_test(ptr);
	अगर (res < 0) अणु
		zr36016_unset(codec);
		वापस res;
	पूर्ण
	//final setup
	ptr->mode = CODEC_DO_COMPRESSION;
	ptr->width = 768;
	ptr->height = 288;
	ptr->xdec = 1;
	ptr->ydec = 0;
	zr36016_init(ptr);

	dprपूर्णांकk(1, KERN_INFO "%s: codec v%d attached and running\n", ptr->name, ptr->version);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा videocodec zr36016_codec = अणु
	.owner = THIS_MODULE,
	.name = "zr36016",
	.magic = 0L,		/* magic not used */
	.flags =
	    CODEC_FLAG_HARDWARE | CODEC_FLAG_VFE | CODEC_FLAG_ENCODER |
	    CODEC_FLAG_DECODER,
	.type = CODEC_TYPE_ZR36016,
	.setup = zr36016_setup,	/* functionality */
	.unset = zr36016_unset,
	.set_mode = zr36016_set_mode,
	.set_video = zr36016_set_video,
	.control = zr36016_control,
	/* others are not used */
पूर्ण;

/* =========================================================================
   HOOK IN DRIVER AS KERNEL MODULE
   ========================================================================= */

अटल पूर्णांक __init zr36016_init_module(व्योम)
अणु
	//dprपूर्णांकk(1, "ZR36016 driver %s\n",ZR016_VERSION);
	zr36016_codecs = 0;
	वापस videocodec_रेजिस्टर(&zr36016_codec);
पूर्ण

अटल व्योम __निकास zr36016_cleanup_module(व्योम)
अणु
	अगर (zr36016_codecs) अणु
		dprपूर्णांकk(1,
			"zr36016: something's wrong - %d codecs left somehow.\n",
			zr36016_codecs);
	पूर्ण
	videocodec_unरेजिस्टर(&zr36016_codec);
पूर्ण

module_init(zr36016_init_module);
module_निकास(zr36016_cleanup_module);

MODULE_AUTHOR("Wolfgang Scherr <scherr@net4you.at>");
MODULE_DESCRIPTION("Driver module for ZR36016 video frontends");
MODULE_LICENSE("GPL");
