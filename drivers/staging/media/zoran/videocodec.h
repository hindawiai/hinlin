<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * VIDEO MOTION CODECs पूर्णांकernal API क्रम video devices
 *
 * Interface क्रम MJPEG (and maybe later MPEG/WAVELETS) codec's
 * bound to a master device.
 *
 * (c) 2002 Wolfgang Scherr <scherr@net4you.at>
 */

/* =================== */
/* general description */
/* =================== */

/* Should ease the (re-)usage of drivers supporting cards with (dअगरferent)
   video codecs. The codecs रेजिस्टर to this module their functionality,
   and the processors (masters) can attach to them अगर they fit.

   The codecs are typically have a "strong" binding to their master - so I
   करोn't think it makes sense to have a full blown पूर्णांकerfacing as with e.g.
   i2c. If you have an other opinion, let's discuss & implement it :-)))

   Usage:

   The slave has just to setup the videocodec काष्ठाure and use two functions:
   videocodec_रेजिस्टर(codecdata);
   videocodec_unरेजिस्टर(codecdata);
   The best is just calling them at module (de-)initialisation.

   The master sets up the काष्ठाure videocodec_master and calls:
   codecdata=videocodec_attach(master_codecdata);
   videocodec_detach(codecdata);

   The slave is called during attach/detach via functions setup previously
   during रेजिस्टर. At that समय, the master_data poपूर्णांकer is set up
   and the slave can access any io रेजिस्टरs of the master device (in the हाल
   the slave is bound to it). Otherwise it करोesn't need this functions and
   therक्रम they may not be initialized.

   The other functions are just क्रम convenience, as they are क्रम sure used by
   most/all of the codecs. The last ones may be omitted, too.

   See the काष्ठाure declaration below क्रम more inक्रमmation and which data has
   to be set up क्रम the master and the slave.

   ----------------------------------------------------------------------------
   The master should have "knowledge" of the slave and vice versa.  So the data
   काष्ठाures sent to/from slave via set_data/get_data set_image/get_image are
   device dependent and vary between MJPEG/MPEG/WAVELET/... devices. (!!!!)
   ----------------------------------------------------------------------------
*/

/* ========================================== */
/* description of the videocodec_io काष्ठाure */
/* ========================================== */

/*
   ==== master setup ====
   name -> name of the device काष्ठाure क्रम reference and debugging
   master_data ->  data ref. क्रम the master (e.g. the zr36055,57,67)
   पढ़ोreg -> ref. to पढ़ो-fn from रेजिस्टर (setup by master, used by slave)
   ग_लिखोreg -> ref. to ग_लिखो-fn to रेजिस्टर (setup by master, used by slave)
	       this two functions करो the lowlevel I/O job

   ==== slave functionality setup ====
   slave_data -> data ref. क्रम the slave (e.g. the zr36050,60)
   check -> fn-ref. checks availability of an device, वापसs -EIO on failure or
	    the type on success
	    this makes espcecially sense अगर a driver module supports more than
	    one codec which may be quite similar to access, nevertheless it
	    is good क्रम a first functionality check

   -- मुख्य functions you always need क्रम compression/decompression --

   set_mode -> this fn-ref. resets the entire codec, and sets up the mode
	       with the last defined norm/size (or device शेष अगर not
	       available) - it वापसs 0 अगर the mode is possible
   set_size -> this fn-ref. sets the norm and image size क्रम
	       compression/decompression (वापसs 0 on success)
	       the norm param is defined in videodev2.h (V4L2_STD_*)

   additional setup may be available, too - but the codec should work with
   some शेष values even without this

   set_data -> sets device-specअगरic data (tables, quality etc.)
   get_data -> query device-specअगरic data (tables, quality etc.)

   अगर the device delivers पूर्णांकerrupts, they may be setup/handled here
   setup_पूर्णांकerrupt -> codec irq setup (not needed क्रम 36050/60)
   handle_पूर्णांकerrupt -> codec irq handling (not needed क्रम 36050/60)

   अगर the device delivers pictures, they may be handled here
   put_image -> माला_दो image data to the codec (not needed क्रम 36050/60)
   get_image -> माला_लो image data from the codec (not needed क्रम 36050/60)
		the calls include frame numbers and flags (even/odd/...)
		अगर needed and a flag which allows blocking until its पढ़ोy
*/

/* ============== */
/* user पूर्णांकerface */
/* ============== */

/*
   Currently there is only a inक्रमmation display planned, as the layer
   is not visible क्रम the user space at all.

   Inक्रमmation is available via procfs. The current entry is "/proc/videocodecs"
   but it makes sense to "hide" it in the /proc/video tree of v4l(2) --TODO--.

A example क्रम such an output is:

<S>lave or attached <M>aster name  type flags    magic    (connected as)
S                          zr36050 0002 0000d001 00000000 (TEMPLATE)
M                       zr36055[0] 0001 0000c001 00000000 (zr36050[0])
M                       zr36055[1] 0001 0000c001 00000000 (zr36050[1])

*/

/* =============================================== */
/* special defines क्रम the videocodec_io काष्ठाure */
/* =============================================== */

#अगर_अघोषित __LINUX_VIDEOCODEC_H
#घोषणा __LINUX_VIDEOCODEC_H

#समावेश <linux/videodev2.h>

#घोषणा CODEC_DO_COMPRESSION 0
#घोषणा CODEC_DO_EXPANSION   1

/* this are the current codec flags I think they are needed */
/*  -> type value in काष्ठाure */
#घोषणा CODEC_FLAG_JPEG      0x00000001L	// JPEG codec
#घोषणा CODEC_FLAG_MPEG      0x00000002L	// MPEG1/2/4 codec
#घोषणा CODEC_FLAG_DIVX      0x00000004L	// DIVX codec
#घोषणा CODEC_FLAG_WAVELET   0x00000008L	// WAVELET codec
					  // room क्रम other types

#घोषणा CODEC_FLAG_MAGIC     0x00000800L	// magic key must match
#घोषणा CODEC_FLAG_HARDWARE  0x00001000L	// is a hardware codec
#घोषणा CODEC_FLAG_VFE       0x00002000L	// has direct video frontend
#घोषणा CODEC_FLAG_ENCODER   0x00004000L	// compression capability
#घोषणा CODEC_FLAG_DECODER   0x00008000L	// decompression capability
#घोषणा CODEC_FLAG_NEEसूचीQ   0x00010000L	// needs irq handling
#घोषणा CODEC_FLAG_RDWRPIC   0x00020000L	// handles picture I/O

/* a list of modes, some are just examples (is there any HW?) */
#घोषणा CODEC_MODE_BJPG      0x0001	// Baseline JPEG
#घोषणा CODEC_MODE_LJPG      0x0002	// Lossless JPEG
#घोषणा CODEC_MODE_MPEG1     0x0003	// MPEG 1
#घोषणा CODEC_MODE_MPEG2     0x0004	// MPEG 2
#घोषणा CODEC_MODE_MPEG4     0x0005	// MPEG 4
#घोषणा CODEC_MODE_MSDIVX    0x0006	// MS DivX
#घोषणा CODEC_MODE_ODIVX     0x0007	// Open DivX
#घोषणा CODEC_MODE_WAVELET   0x0008	// Wavelet

/* this are the current codec types I want to implement */
/*  -> type value in काष्ठाure */
#घोषणा CODEC_TYPE_NONE    0
#घोषणा CODEC_TYPE_L64702  1
#घोषणा CODEC_TYPE_ZR36050 2
#घोषणा CODEC_TYPE_ZR36016 3
#घोषणा CODEC_TYPE_ZR36060 4

/* the type of data may be enhanced by future implementations (data-fn.'s) */
/*  -> used in command                                                     */
#घोषणा CODEC_G_STATUS         0x0000	/* codec status (query only) */
#घोषणा CODEC_S_CODEC_MODE     0x0001	/* codec mode (baseline JPEG, MPEG1,... */
#घोषणा CODEC_G_CODEC_MODE     0x8001
#घोषणा CODEC_S_VFE            0x0002	/* additional video frontend setup */
#घोषणा CODEC_G_VFE            0x8002
#घोषणा CODEC_S_MMAP           0x0003	/* MMAP setup (अगर available) */

#घोषणा CODEC_S_JPEG_TDS_BYTE  0x0010	/* target data size in bytes */
#घोषणा CODEC_G_JPEG_TDS_BYTE  0x8010
#घोषणा CODEC_S_JPEG_SCALE     0x0011	/* scaling factor क्रम quant. tables */
#घोषणा CODEC_G_JPEG_SCALE     0x8011
#घोषणा CODEC_S_JPEG_HDT_DATA  0x0018	/* huffman-tables */
#घोषणा CODEC_G_JPEG_HDT_DATA  0x8018
#घोषणा CODEC_S_JPEG_QDT_DATA  0x0019	/* quantizing-tables */
#घोषणा CODEC_G_JPEG_QDT_DATA  0x8019
#घोषणा CODEC_S_JPEG_APP_DATA  0x001A	/* APP marker */
#घोषणा CODEC_G_JPEG_APP_DATA  0x801A
#घोषणा CODEC_S_JPEG_COM_DATA  0x001B	/* COM marker */
#घोषणा CODEC_G_JPEG_COM_DATA  0x801B

#घोषणा CODEC_S_PRIVATE        0x1000	/* "private" commands start here */
#घोषणा CODEC_G_PRIVATE        0x9000

#घोषणा CODEC_G_FLAG           0x8000	/* this is how 'get' is detected */

/* types of transfer, directly user space or a kernel buffer (image-fn.'s) */
/*  -> used in get_image, put_image */
#घोषणा CODEC_TRANSFER_KERNEL 0	/* use "memcopy" */
#घोषणा CODEC_TRANSFER_USER   1	/* use "to/from_user" */

/* ========================= */
/* the काष्ठाures itself ... */
/* ========================= */

काष्ठा vfe_polarity अणु
	अचिन्हित पूर्णांक vsync_pol:1;
	अचिन्हित पूर्णांक hsync_pol:1;
	अचिन्हित पूर्णांक field_pol:1;
	अचिन्हित पूर्णांक blank_pol:1;
	अचिन्हित पूर्णांक subimg_pol:1;
	अचिन्हित पूर्णांक poe_pol:1;
	अचिन्हित पूर्णांक pvalid_pol:1;
	अचिन्हित पूर्णांक vclk_pol:1;
पूर्ण;

काष्ठा vfe_settings अणु
	__u32 x, y;		/* Offsets पूर्णांकo image */
	__u32 width, height;	/* Area to capture */
	__u16 decimation;	/* Decimation भागider */
	__u16 flags;		/* Flags क्रम capture */
	__u16 quality;		/* quality of the video */
पूर्ण;

काष्ठा tvnorm अणु
	u16 wt, wa, h_start, h_sync_start, ht, ha, v_start;
पूर्ण;

काष्ठा jpeg_com_marker अणु
	पूर्णांक len; /* number of usable bytes in data */
	अक्षर data[60];
पूर्ण;

काष्ठा jpeg_app_marker अणु
	पूर्णांक appn; /* number app segment */
	पूर्णांक len; /* number of usable bytes in data */
	अक्षर data[60];
पूर्ण;

काष्ठा videocodec अणु
	काष्ठा module *owner;
	/* -- filled in by slave device during रेजिस्टर -- */
	अक्षर name[32];
	अचिन्हित दीर्घ magic;	/* may be used क्रम client<->master attaching */
	अचिन्हित दीर्घ flags;	/* functionality flags */
	अचिन्हित पूर्णांक type;	/* codec type */

	/* -- these is filled in later during master device attach -- */

	काष्ठा videocodec_master *master_data;

	/* -- these are filled in by the slave device during रेजिस्टर -- */

	व्योम *data;		/* निजी slave data */

	/* attach/detach client functions (indirect call) */
	पूर्णांक (*setup)(काष्ठा videocodec *codec);
	पूर्णांक (*unset)(काष्ठा videocodec *codec);

	/* मुख्य functions, every client needs them क्रम sure! */
	// set compression or decompression (or मुक्तze, stop, standby, etc)
	पूर्णांक (*set_mode)(काष्ठा videocodec *codec, पूर्णांक mode);
	// setup picture size and norm (क्रम the codec's video frontend)
	पूर्णांक (*set_video)(काष्ठा videocodec *codec, स्थिर काष्ठा tvnorm *norm,
			 काष्ठा vfe_settings *cap, काष्ठा vfe_polarity *pol);
	// other control commands, also mmap setup etc.
	पूर्णांक (*control)(काष्ठा videocodec *codec, पूर्णांक type, पूर्णांक size, व्योम *data);

	/* additional setup/query/processing (may be शून्य poपूर्णांकer) */
	// पूर्णांकerrupt setup / handling (क्रम irq's delivered by master)
	पूर्णांक (*setup_पूर्णांकerrupt)(काष्ठा videocodec *codec, दीर्घ mode);
	पूर्णांक (*handle_पूर्णांकerrupt)(काष्ठा videocodec *codec, पूर्णांक source, दीर्घ flag);
	// picture पूर्णांकerface (अगर any)
	दीर्घ (*put_image)(काष्ठा videocodec *codec, पूर्णांक tr_type, पूर्णांक block,
			  दीर्घ *fr_num, दीर्घ *flag, दीर्घ size, व्योम *buf);
	दीर्घ (*get_image)(काष्ठा videocodec *codec, पूर्णांक tr_type, पूर्णांक block,
			  दीर्घ *fr_num, दीर्घ *flag, दीर्घ size, व्योम *buf);
पूर्ण;

काष्ठा videocodec_master अणु
	/* -- filled in by master device क्रम registration -- */
	अक्षर name[32];
	अचिन्हित दीर्घ magic;	/* may be used क्रम client<->master attaching */
	अचिन्हित दीर्घ flags;	/* functionality flags */
	अचिन्हित पूर्णांक type;	/* master type */

	व्योम *data;		/* निजी master data */

	__u32 (*पढ़ोreg)(काष्ठा videocodec *codec, __u16 reg);
	व्योम (*ग_लिखोreg)(काष्ठा videocodec *codec, __u16 reg, __u32 value);
पूर्ण;

/* ================================================= */
/* function prototypes of the master/slave पूर्णांकerface */
/* ================================================= */

/* attach and detach commands क्रम the master */
// * master काष्ठाure needs to be kदो_स्मृति'ed beक्रमe calling attach
//   and मुक्त'd after calling detach
// * वापसs poपूर्णांकer on success, शून्य on failure
बाह्य काष्ठा videocodec *videocodec_attach(काष्ठा videocodec_master *);
// * 0 on success, <0 (त्रुटि_सं) on failure
बाह्य पूर्णांक videocodec_detach(काष्ठा videocodec *);

/* रेजिस्टर and unरेजिस्टर commands क्रम the slaves */
// * 0 on success, <0 (त्रुटि_सं) on failure
बाह्य पूर्णांक videocodec_रेजिस्टर(स्थिर काष्ठा videocodec *);
// * 0 on success, <0 (त्रुटि_सं) on failure
बाह्य पूर्णांक videocodec_unरेजिस्टर(स्थिर काष्ठा videocodec *);

/* the other calls are directly करोne via the videocodec काष्ठाure! */

#पूर्ण_अगर				/*अगरndef __LINUX_VIDEOCODEC_H */
