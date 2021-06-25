<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// tuner-xc2028
//
// Copyright (c) 2007-2008 Mauro Carvalho Chehab <mchehab@kernel.org>
//
// Copyright (c) 2007 Michel Ludwig (michel.ludwig@gmail.com)
//       - frontend पूर्णांकerface

#समावेश <linux/i2c.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <linux/firmware.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/delay.h>
#समावेश <media/tuner.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "tuner-i2c.h"
#समावेश "tuner-xc2028.h"
#समावेश "tuner-xc2028-types.h"

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  80

/* Registers (Write-only) */
#घोषणा XREG_INIT         0x00
#घोषणा XREG_RF_FREQ      0x02
#घोषणा XREG_POWER_DOWN   0x08

/* Registers (Read-only) */
#घोषणा XREG_FREQ_ERROR   0x01
#घोषणा XREG_LOCK         0x02
#घोषणा XREG_VERSION      0x04
#घोषणा XREG_PRODUCT_ID   0x08
#घोषणा XREG_HSYNC_FREQ   0x10
#घोषणा XREG_FRAME_LINES  0x20
#घोषणा XREG_SNR          0x40

#घोषणा XREG_ADC_ENV      0x0100

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable verbose debug messages");

अटल पूर्णांक no_घातeroff;
module_param(no_घातeroff, पूर्णांक, 0644);
MODULE_PARM_DESC(no_घातeroff, "0 (default) powers device off when not used.\n"
	"1 keep device energized and with tuner ready all the times.\n"
	"  Faster, but consumes more power and keeps the device hotter\n");

अटल अक्षर audio_std[8];
module_param_string(audio_std, audio_std, माप(audio_std), 0);
MODULE_PARM_DESC(audio_std,
	"Audio standard. XC3028 audio decoder explicitly needs to know what audio\n"
	"standard is needed for some video standards with audio A2 or NICAM.\n"
	"The valid values are:\n"
	"A2\n"
	"A2/A\n"
	"A2/B\n"
	"NICAM\n"
	"NICAM/A\n"
	"NICAM/B\n");

अटल अक्षर firmware_name[30];
module_param_string(firmware_name, firmware_name, माप(firmware_name), 0);
MODULE_PARM_DESC(firmware_name,
		 "Firmware file name. Allows overriding the default firmware name\n");

अटल LIST_HEAD(hybrid_tuner_instance_list);
अटल DEFINE_MUTEX(xc2028_list_mutex);

/* काष्ठा क्रम storing firmware table */
काष्ठा firmware_description अणु
	अचिन्हित पूर्णांक  type;
	v4l2_std_id   id;
	__u16         पूर्णांक_freq;
	अचिन्हित अक्षर *ptr;
	अचिन्हित पूर्णांक  size;
पूर्ण;

काष्ठा firmware_properties अणु
	अचिन्हित पूर्णांक	type;
	v4l2_std_id	id;
	v4l2_std_id	std_req;
	__u16		पूर्णांक_freq;
	अचिन्हित पूर्णांक	scode_table;
	पूर्णांक		scode_nr;
पूर्ण;

क्रमागत xc2028_state अणु
	XC2028_NO_FIRMWARE = 0,
	XC2028_WAITING_FIRMWARE,
	XC2028_ACTIVE,
	XC2028_SLEEP,
	XC2028_NODEV,
पूर्ण;

काष्ठा xc2028_data अणु
	काष्ठा list_head        hybrid_tuner_instance_list;
	काष्ठा tuner_i2c_props  i2c_props;
	__u32			frequency;

	क्रमागत xc2028_state	state;
	स्थिर अक्षर		*fname;

	काष्ठा firmware_description *firm;
	पूर्णांक			firm_size;
	__u16			firm_version;

	__u16			hwmodel;
	__u16			hwvers;

	काष्ठा xc2028_ctrl	ctrl;

	काष्ठा firmware_properties cur_fw;

	काष्ठा mutex lock;
पूर्ण;

#घोषणा i2c_send(priv, buf, size) (अणु					\
	पूर्णांक _rc;							\
	_rc = tuner_i2c_xfer_send(&priv->i2c_props, buf, size);		\
	अगर (size != _rc)						\
		tuner_info("i2c output error: rc = %d (should be %d)\n",\
			   _rc, (पूर्णांक)size);				\
	अगर (priv->ctrl.msleep)						\
		msleep(priv->ctrl.msleep);				\
	_rc;								\
पूर्ण)

#घोषणा i2c_send_recv(priv, obuf, osize, ibuf, isize) (अणु		\
	पूर्णांक _rc;							\
	_rc = tuner_i2c_xfer_send_recv(&priv->i2c_props, obuf, osize,	\
				       ibuf, isize);			\
	अगर (isize != _rc)						\
		tuner_err("i2c input error: rc = %d (should be %d)\n",	\
			   _rc, (पूर्णांक)isize);				\
	अगर (priv->ctrl.msleep)						\
		msleep(priv->ctrl.msleep);				\
	_rc;								\
पूर्ण)

#घोषणा send_seq(priv, data...)	(अणु					\
	अटल u8 _val[] = data;					\
	पूर्णांक _rc;							\
	अगर (माप(_val) !=						\
			(_rc = tuner_i2c_xfer_send(&priv->i2c_props,	\
						_val, माप(_val)))) अणु	\
		tuner_err("Error on line %d: %d\n", __LINE__, _rc);	\
	पूर्ण अन्यथा अगर (priv->ctrl.msleep)					\
		msleep(priv->ctrl.msleep);				\
	_rc;								\
पूर्ण)

अटल पूर्णांक xc2028_get_reg(काष्ठा xc2028_data *priv, u16 reg, u16 *val)
अणु
	अचिन्हित अक्षर buf[2];
	अचिन्हित अक्षर ibuf[2];

	tuner_dbg("%s %04x called\n", __func__, reg);

	buf[0] = reg >> 8;
	buf[1] = (अचिन्हित अक्षर) reg;

	अगर (i2c_send_recv(priv, buf, 2, ibuf, 2) != 2)
		वापस -EIO;

	*val = (ibuf[1]) | (ibuf[0] << 8);
	वापस 0;
पूर्ण

#घोषणा dump_firm_type(t)	dump_firm_type_and_पूर्णांक_freq(t, 0)
अटल व्योम dump_firm_type_and_पूर्णांक_freq(अचिन्हित पूर्णांक type, u16 पूर्णांक_freq)
अणु
	अगर (type & BASE)
		prपूर्णांकk(KERN_CONT "BASE ");
	अगर (type & INIT1)
		prपूर्णांकk(KERN_CONT "INIT1 ");
	अगर (type & F8MHZ)
		prपूर्णांकk(KERN_CONT "F8MHZ ");
	अगर (type & MTS)
		prपूर्णांकk(KERN_CONT "MTS ");
	अगर (type & D2620)
		prपूर्णांकk(KERN_CONT "D2620 ");
	अगर (type & D2633)
		prपूर्णांकk(KERN_CONT "D2633 ");
	अगर (type & DTV6)
		prपूर्णांकk(KERN_CONT "DTV6 ");
	अगर (type & QAM)
		prपूर्णांकk(KERN_CONT "QAM ");
	अगर (type & DTV7)
		prपूर्णांकk(KERN_CONT "DTV7 ");
	अगर (type & DTV78)
		prपूर्णांकk(KERN_CONT "DTV78 ");
	अगर (type & DTV8)
		prपूर्णांकk(KERN_CONT "DTV8 ");
	अगर (type & FM)
		prपूर्णांकk(KERN_CONT "FM ");
	अगर (type & INPUT1)
		prपूर्णांकk(KERN_CONT "INPUT1 ");
	अगर (type & LCD)
		prपूर्णांकk(KERN_CONT "LCD ");
	अगर (type & NOGD)
		prपूर्णांकk(KERN_CONT "NOGD ");
	अगर (type & MONO)
		prपूर्णांकk(KERN_CONT "MONO ");
	अगर (type & ATSC)
		prपूर्णांकk(KERN_CONT "ATSC ");
	अगर (type & IF)
		prपूर्णांकk(KERN_CONT "IF ");
	अगर (type & LG60)
		prपूर्णांकk(KERN_CONT "LG60 ");
	अगर (type & ATI638)
		prपूर्णांकk(KERN_CONT "ATI638 ");
	अगर (type & OREN538)
		prपूर्णांकk(KERN_CONT "OREN538 ");
	अगर (type & OREN36)
		prपूर्णांकk(KERN_CONT "OREN36 ");
	अगर (type & TOYOTA388)
		prपूर्णांकk(KERN_CONT "TOYOTA388 ");
	अगर (type & TOYOTA794)
		prपूर्णांकk(KERN_CONT "TOYOTA794 ");
	अगर (type & DIBCOM52)
		prपूर्णांकk(KERN_CONT "DIBCOM52 ");
	अगर (type & ZARLINK456)
		prपूर्णांकk(KERN_CONT "ZARLINK456 ");
	अगर (type & CHINA)
		prपूर्णांकk(KERN_CONT "CHINA ");
	अगर (type & F6MHZ)
		prपूर्णांकk(KERN_CONT "F6MHZ ");
	अगर (type & INPUT2)
		prपूर्णांकk(KERN_CONT "INPUT2 ");
	अगर (type & SCODE)
		prपूर्णांकk(KERN_CONT "SCODE ");
	अगर (type & HAS_IF)
		prपूर्णांकk(KERN_CONT "HAS_IF_%d ", पूर्णांक_freq);
पूर्ण

अटल  v4l2_std_id parse_audio_std_option(व्योम)
अणु
	अगर (strहालcmp(audio_std, "A2") == 0)
		वापस V4L2_STD_A2;
	अगर (strहालcmp(audio_std, "A2/A") == 0)
		वापस V4L2_STD_A2_A;
	अगर (strहालcmp(audio_std, "A2/B") == 0)
		वापस V4L2_STD_A2_B;
	अगर (strहालcmp(audio_std, "NICAM") == 0)
		वापस V4L2_STD_NICAM;
	अगर (strहालcmp(audio_std, "NICAM/A") == 0)
		वापस V4L2_STD_NICAM_A;
	अगर (strहालcmp(audio_std, "NICAM/B") == 0)
		वापस V4L2_STD_NICAM_B;

	वापस 0;
पूर्ण

अटल पूर्णांक check_device_status(काष्ठा xc2028_data *priv)
अणु
	चयन (priv->state) अणु
	हाल XC2028_NO_FIRMWARE:
	हाल XC2028_WAITING_FIRMWARE:
		वापस -EAGAIN;
	हाल XC2028_ACTIVE:
		वापस 1;
	हाल XC2028_SLEEP:
		वापस 0;
	हाल XC2028_NODEV:
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम मुक्त_firmware(काष्ठा xc2028_data *priv)
अणु
	पूर्णांक i;
	tuner_dbg("%s called\n", __func__);

	/* मुक्त allocated f/w string */
	अगर (priv->fname != firmware_name)
		kमुक्त(priv->fname);
	priv->fname = शून्य;

	priv->state = XC2028_NO_FIRMWARE;
	स_रखो(&priv->cur_fw, 0, माप(priv->cur_fw));

	अगर (!priv->firm)
		वापस;

	क्रम (i = 0; i < priv->firm_size; i++)
		kमुक्त(priv->firm[i].ptr);

	kमुक्त(priv->firm);

	priv->firm = शून्य;
	priv->firm_size = 0;
पूर्ण

अटल पूर्णांक load_all_firmwares(काष्ठा dvb_frontend *fe,
			      स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा xc2028_data    *priv = fe->tuner_priv;
	स्थिर अचिन्हित अक्षर   *p, *endp;
	पूर्णांक                   rc = 0;
	पूर्णांक		      n, n_array;
	अक्षर		      name[33];

	tuner_dbg("%s called\n", __func__);

	p = fw->data;
	endp = p + fw->size;

	अगर (fw->size < माप(name) - 1 + 2 + 2) अणु
		tuner_err("Error: firmware file %s has invalid size!\n",
			  priv->fname);
		जाओ corrupt;
	पूर्ण

	स_नकल(name, p, माप(name) - 1);
	name[माप(name) - 1] = 0;
	p += माप(name) - 1;

	priv->firm_version = get_unaligned_le16(p);
	p += 2;

	n_array = get_unaligned_le16(p);
	p += 2;

	tuner_info("Loading %d firmware images from %s, type: %s, ver %d.%d\n",
		   n_array, priv->fname, name,
		   priv->firm_version >> 8, priv->firm_version & 0xff);

	priv->firm = kसुस्मृति(n_array, माप(*priv->firm), GFP_KERNEL);
	अगर (priv->firm == शून्य) अणु
		tuner_err("Not enough memory to load firmware file.\n");
		rc = -ENOMEM;
		जाओ err;
	पूर्ण
	priv->firm_size = n_array;

	n = -1;
	जबतक (p < endp) अणु
		__u32 type, size;
		v4l2_std_id id;
		__u16 पूर्णांक_freq = 0;

		n++;
		अगर (n >= n_array) अणु
			tuner_err("More firmware images in file than were expected!\n");
			जाओ corrupt;
		पूर्ण

		/* Checks अगर there's enough bytes to पढ़ो */
		अगर (endp - p < माप(type) + माप(id) + माप(size))
			जाओ header;

		type = get_unaligned_le32(p);
		p += माप(type);

		id = get_unaligned_le64(p);
		p += माप(id);

		अगर (type & HAS_IF) अणु
			पूर्णांक_freq = get_unaligned_le16(p);
			p += माप(पूर्णांक_freq);
			अगर (endp - p < माप(size))
				जाओ header;
		पूर्ण

		size = get_unaligned_le32(p);
		p += माप(size);

		अगर (!size || size > endp - p) अणु
			tuner_err("Firmware type ");
			dump_firm_type(type);
			prपूर्णांकk(KERN_CONT
			       "(%x), id %llx is corrupted (size=%zd, expected %d)\n",
			       type, (अचिन्हित दीर्घ दीर्घ)id, (endp - p), size);
			जाओ corrupt;
		पूर्ण

		priv->firm[n].ptr = kmemdup(p, size, GFP_KERNEL);
		अगर (priv->firm[n].ptr == शून्य) अणु
			tuner_err("Not enough memory to load firmware file.\n");
			rc = -ENOMEM;
			जाओ err;
		पूर्ण
		tuner_dbg("Reading firmware type ");
		अगर (debug) अणु
			dump_firm_type_and_पूर्णांक_freq(type, पूर्णांक_freq);
			prपूर्णांकk(KERN_CONT "(%x), id %llx, size=%d.\n",
			       type, (अचिन्हित दीर्घ दीर्घ)id, size);
		पूर्ण

		priv->firm[n].type = type;
		priv->firm[n].id   = id;
		priv->firm[n].size = size;
		priv->firm[n].पूर्णांक_freq = पूर्णांक_freq;

		p += size;
	पूर्ण

	अगर (n + 1 != priv->firm_size) अणु
		tuner_err("Firmware file is incomplete!\n");
		जाओ corrupt;
	पूर्ण

	जाओ करोne;

header:
	tuner_err("Firmware header is incomplete!\n");
corrupt:
	rc = -EINVAL;
	tuner_err("Error: firmware file is corrupted!\n");

err:
	tuner_info("Releasing partially loaded firmware file.\n");
	मुक्त_firmware(priv);

करोne:
	अगर (rc == 0)
		tuner_dbg("Firmware files loaded.\n");
	अन्यथा
		priv->state = XC2028_NODEV;

	वापस rc;
पूर्ण

अटल पूर्णांक seek_firmware(काष्ठा dvb_frontend *fe, अचिन्हित पूर्णांक type,
			 v4l2_std_id *id)
अणु
	काष्ठा xc2028_data *priv = fe->tuner_priv;
	पूर्णांक                 i, best_i = -1, best_nr_matches = 0;
	अचिन्हित पूर्णांक        type_mask = 0;

	tuner_dbg("%s called, want type=", __func__);
	अगर (debug) अणु
		dump_firm_type(type);
		prपूर्णांकk(KERN_CONT "(%x), id %016llx.\n",
		       type, (अचिन्हित दीर्घ दीर्घ)*id);
	पूर्ण

	अगर (!priv->firm) अणु
		tuner_err("Error! firmware not loaded\n");
		वापस -EINVAL;
	पूर्ण

	अगर (((type & ~SCODE) == 0) && (*id == 0))
		*id = V4L2_STD_PAL;

	अगर (type & BASE)
		type_mask = BASE_TYPES;
	अन्यथा अगर (type & SCODE) अणु
		type &= SCODE_TYPES;
		type_mask = SCODE_TYPES & ~HAS_IF;
	पूर्ण अन्यथा अगर (type & DTV_TYPES)
		type_mask = DTV_TYPES;
	अन्यथा अगर (type & STD_SPECIFIC_TYPES)
		type_mask = STD_SPECIFIC_TYPES;

	type &= type_mask;

	अगर (!(type & SCODE))
		type_mask = ~0;

	/* Seek क्रम exact match */
	क्रम (i = 0; i < priv->firm_size; i++) अणु
		अगर ((type == (priv->firm[i].type & type_mask)) &&
		    (*id == priv->firm[i].id))
			जाओ found;
	पूर्ण

	/* Seek क्रम generic video standard match */
	क्रम (i = 0; i < priv->firm_size; i++) अणु
		v4l2_std_id match_mask;
		पूर्णांक nr_matches;

		अगर (type != (priv->firm[i].type & type_mask))
			जारी;

		match_mask = *id & priv->firm[i].id;
		अगर (!match_mask)
			जारी;

		अगर ((*id & match_mask) == *id)
			जाओ found; /* Supports all the requested standards */

		nr_matches = hweight64(match_mask);
		अगर (nr_matches > best_nr_matches) अणु
			best_nr_matches = nr_matches;
			best_i = i;
		पूर्ण
	पूर्ण

	अगर (best_nr_matches > 0) अणु
		tuner_dbg("Selecting best matching firmware (%d bits) for type=",
			  best_nr_matches);
		dump_firm_type(type);
		prपूर्णांकk(KERN_CONT
		       "(%x), id %016llx:\n", type, (अचिन्हित दीर्घ दीर्घ)*id);
		i = best_i;
		जाओ found;
	पूर्ण

	/*FIXME: Would make sense to seek क्रम type "hint" match ? */

	i = -ENOENT;
	जाओ ret;

found:
	*id = priv->firm[i].id;

ret:
	tuner_dbg("%s firmware for type=", (i < 0) ? "Can't find" : "Found");
	अगर (debug) अणु
		dump_firm_type(type);
		prपूर्णांकk(KERN_CONT "(%x), id %016llx.\n",
		       type, (अचिन्हित दीर्घ दीर्घ)*id);
	पूर्ण
	वापस i;
पूर्ण

अटल अंतरभूत पूर्णांक करो_tuner_callback(काष्ठा dvb_frontend *fe, पूर्णांक cmd, पूर्णांक arg)
अणु
	काष्ठा xc2028_data *priv = fe->tuner_priv;

	/* analog side (tuner-core) uses i2c_adap->algo_data.
	 * digital side is not guaranteed to have algo_data defined.
	 *
	 * digital side will always have fe->dvb defined.
	 * analog side (tuner-core) करोesn't (yet) define fe->dvb.
	 */

	वापस (!fe->callback) ? -EINVAL :
		fe->callback(((fe->dvb) && (fe->dvb->priv)) ?
				fe->dvb->priv : priv->i2c_props.adap->algo_data,
			     DVB_FRONTEND_COMPONENT_TUNER, cmd, arg);
पूर्ण

अटल पूर्णांक load_firmware(काष्ठा dvb_frontend *fe, अचिन्हित पूर्णांक type,
			 v4l2_std_id *id)
अणु
	काष्ठा xc2028_data *priv = fe->tuner_priv;
	पूर्णांक                pos, rc;
	अचिन्हित अक्षर      *p, *endp, buf[MAX_XFER_SIZE];

	अगर (priv->ctrl.max_len > माप(buf))
		priv->ctrl.max_len = माप(buf);

	tuner_dbg("%s called\n", __func__);

	pos = seek_firmware(fe, type, id);
	अगर (pos < 0)
		वापस pos;

	tuner_info("Loading firmware for type=");
	dump_firm_type(priv->firm[pos].type);
	prपूर्णांकk(KERN_CONT "(%x), id %016llx.\n",
	       priv->firm[pos].type, (अचिन्हित दीर्घ दीर्घ)*id);

	p = priv->firm[pos].ptr;
	endp = p + priv->firm[pos].size;

	जबतक (p < endp) अणु
		__u16 size;

		/* Checks अगर there's enough bytes to पढ़ो */
		अगर (p + माप(size) > endp) अणु
			tuner_err("Firmware chunk size is wrong\n");
			वापस -EINVAL;
		पूर्ण

		size = le16_to_cpu(*(__le16 *) p);
		p += माप(size);

		अगर (size == 0xffff)
			वापस 0;

		अगर (!size) अणु
			/* Special callback command received */
			rc = करो_tuner_callback(fe, XC2028_TUNER_RESET, 0);
			अगर (rc < 0) अणु
				tuner_err("Error at RESET code %d\n",
					   (*p) & 0x7f);
				वापस -EINVAL;
			पूर्ण
			जारी;
		पूर्ण
		अगर (size >= 0xff00) अणु
			चयन (size) अणु
			हाल 0xff00:
				rc = करो_tuner_callback(fe, XC2028_RESET_CLK, 0);
				अगर (rc < 0) अणु
					tuner_err("Error at RESET code %d\n",
						  (*p) & 0x7f);
					वापस -EINVAL;
				पूर्ण
				अवरोध;
			शेष:
				tuner_info("Invalid RESET code %d\n",
					   size & 0x7f);
				वापस -EINVAL;

			पूर्ण
			जारी;
		पूर्ण

		/* Checks क्रम a sleep command */
		अगर (size & 0x8000) अणु
			msleep(size & 0x7fff);
			जारी;
		पूर्ण

		अगर ((size + p > endp)) अणु
			tuner_err("missing bytes: need %d, have %zd\n",
				   size, (endp - p));
			वापस -EINVAL;
		पूर्ण

		buf[0] = *p;
		p++;
		size--;

		/* Sends message chunks */
		जबतक (size > 0) अणु
			पूर्णांक len = (size < priv->ctrl.max_len - 1) ?
				   size : priv->ctrl.max_len - 1;

			स_नकल(buf + 1, p, len);

			rc = i2c_send(priv, buf, len + 1);
			अगर (rc < 0) अणु
				tuner_err("%d returned from send\n", rc);
				वापस -EINVAL;
			पूर्ण

			p += len;
			size -= len;
		पूर्ण

		/* silently fail अगर the frontend करोesn't support I2C flush */
		rc = करो_tuner_callback(fe, XC2028_I2C_FLUSH, 0);
		अगर ((rc < 0) && (rc != -EINVAL)) अणु
			tuner_err("error executing flush: %d\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक load_scode(काष्ठा dvb_frontend *fe, अचिन्हित पूर्णांक type,
			 v4l2_std_id *id, __u16 पूर्णांक_freq, पूर्णांक scode)
अणु
	काष्ठा xc2028_data *priv = fe->tuner_priv;
	पूर्णांक                pos, rc;
	अचिन्हित अक्षर	   *p;

	tuner_dbg("%s called\n", __func__);

	अगर (!पूर्णांक_freq) अणु
		pos = seek_firmware(fe, type, id);
		अगर (pos < 0)
			वापस pos;
	पूर्ण अन्यथा अणु
		क्रम (pos = 0; pos < priv->firm_size; pos++) अणु
			अगर ((priv->firm[pos].पूर्णांक_freq == पूर्णांक_freq) &&
			    (priv->firm[pos].type & HAS_IF))
				अवरोध;
		पूर्ण
		अगर (pos == priv->firm_size)
			वापस -ENOENT;
	पूर्ण

	p = priv->firm[pos].ptr;

	अगर (priv->firm[pos].type & HAS_IF) अणु
		अगर (priv->firm[pos].size != 12 * 16 || scode >= 16)
			वापस -EINVAL;
		p += 12 * scode;
	पूर्ण अन्यथा अणु
		/* 16 SCODE entries per file; each SCODE entry is 12 bytes and
		 * has a 2-byte size header in the firmware क्रमmat. */
		अगर (priv->firm[pos].size != 14 * 16 || scode >= 16 ||
		    le16_to_cpu(*(__le16 *)(p + 14 * scode)) != 12)
			वापस -EINVAL;
		p += 14 * scode + 2;
	पूर्ण

	tuner_info("Loading SCODE for type=");
	dump_firm_type_and_पूर्णांक_freq(priv->firm[pos].type,
				    priv->firm[pos].पूर्णांक_freq);
	prपूर्णांकk(KERN_CONT "(%x), id %016llx.\n", priv->firm[pos].type,
	       (अचिन्हित दीर्घ दीर्घ)*id);

	अगर (priv->firm_version < 0x0202)
		rc = send_seq(priv, अणु0x20, 0x00, 0x00, 0x00पूर्ण);
	अन्यथा
		rc = send_seq(priv, अणु0xa0, 0x00, 0x00, 0x00पूर्ण);
	अगर (rc < 0)
		वापस -EIO;

	rc = i2c_send(priv, p, 12);
	अगर (rc < 0)
		वापस -EIO;

	rc = send_seq(priv, अणु0x00, 0x8cपूर्ण);
	अगर (rc < 0)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक xc2028_sleep(काष्ठा dvb_frontend *fe);

अटल पूर्णांक check_firmware(काष्ठा dvb_frontend *fe, अचिन्हित पूर्णांक type,
			  v4l2_std_id std, __u16 पूर्णांक_freq)
अणु
	काष्ठा xc2028_data         *priv = fe->tuner_priv;
	काष्ठा firmware_properties new_fw;
	पूर्णांक			   rc, retry_count = 0;
	u16			   version, hwmodel;
	v4l2_std_id		   std0;

	tuner_dbg("%s called\n", __func__);

	rc = check_device_status(priv);
	अगर (rc < 0)
		वापस rc;

	अगर (priv->ctrl.mts && !(type & FM))
		type |= MTS;

retry:
	new_fw.type = type;
	new_fw.id = std;
	new_fw.std_req = std;
	new_fw.scode_table = SCODE | priv->ctrl.scode_table;
	new_fw.scode_nr = 0;
	new_fw.पूर्णांक_freq = पूर्णांक_freq;

	tuner_dbg("checking firmware, user requested type=");
	अगर (debug) अणु
		dump_firm_type(new_fw.type);
		prपूर्णांकk(KERN_CONT "(%x), id %016llx, ", new_fw.type,
		       (अचिन्हित दीर्घ दीर्घ)new_fw.std_req);
		अगर (!पूर्णांक_freq) अणु
			prपूर्णांकk(KERN_CONT "scode_tbl ");
			dump_firm_type(priv->ctrl.scode_table);
			prपूर्णांकk(KERN_CONT "(%x), ", priv->ctrl.scode_table);
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_CONT "int_freq %d, ", new_fw.पूर्णांक_freq);
		prपूर्णांकk(KERN_CONT "scode_nr %d\n", new_fw.scode_nr);
	पूर्ण

	/*
	 * No need to reload base firmware अगर it matches and अगर the tuner
	 * is not at sleep mode
	 */
	अगर ((priv->state == XC2028_ACTIVE) &&
	    (((BASE | new_fw.type) & BASE_TYPES) ==
	    (priv->cur_fw.type & BASE_TYPES))) अणु
		tuner_dbg("BASE firmware not changed.\n");
		जाओ skip_base;
	पूर्ण

	/* Updating BASE - क्रमget about all currently loaded firmware */
	स_रखो(&priv->cur_fw, 0, माप(priv->cur_fw));

	/* Reset is needed beक्रमe loading firmware */
	rc = करो_tuner_callback(fe, XC2028_TUNER_RESET, 0);
	अगर (rc < 0)
		जाओ fail;

	/* BASE firmwares are all std0 */
	std0 = 0;
	rc = load_firmware(fe, BASE | new_fw.type, &std0);
	अगर (rc < 0) अणु
		tuner_err("Error %d while loading base firmware\n",
			  rc);
		जाओ fail;
	पूर्ण

	/* Load INIT1, अगर needed */
	tuner_dbg("Load init1 firmware, if exists\n");

	rc = load_firmware(fe, BASE | INIT1 | new_fw.type, &std0);
	अगर (rc == -ENOENT)
		rc = load_firmware(fe, (BASE | INIT1 | new_fw.type) & ~F8MHZ,
				   &std0);
	अगर (rc < 0 && rc != -ENOENT) अणु
		tuner_err("Error %d while loading init1 firmware\n",
			  rc);
		जाओ fail;
	पूर्ण

skip_base:
	/*
	 * No need to reload standard specअगरic firmware अगर base firmware
	 * was not reloaded and requested video standards have not changed.
	 */
	अगर (priv->cur_fw.type == (BASE | new_fw.type) &&
	    priv->cur_fw.std_req == std) अणु
		tuner_dbg("Std-specific firmware already loaded.\n");
		जाओ skip_std_specअगरic;
	पूर्ण

	/* Reloading std-specअगरic firmware क्रमces a SCODE update */
	priv->cur_fw.scode_table = 0;

	rc = load_firmware(fe, new_fw.type, &new_fw.id);
	अगर (rc == -ENOENT)
		rc = load_firmware(fe, new_fw.type & ~F8MHZ, &new_fw.id);

	अगर (rc < 0)
		जाओ fail;

skip_std_specअगरic:
	अगर (priv->cur_fw.scode_table == new_fw.scode_table &&
	    priv->cur_fw.scode_nr == new_fw.scode_nr) अणु
		tuner_dbg("SCODE firmware already loaded.\n");
		जाओ check_device;
	पूर्ण

	अगर (new_fw.type & FM)
		जाओ check_device;

	/* Load SCODE firmware, अगर exists */
	tuner_dbg("Trying to load scode %d\n", new_fw.scode_nr);

	rc = load_scode(fe, new_fw.type | new_fw.scode_table, &new_fw.id,
			new_fw.पूर्णांक_freq, new_fw.scode_nr);

check_device:
	अगर (xc2028_get_reg(priv, 0x0004, &version) < 0 ||
	    xc2028_get_reg(priv, 0x0008, &hwmodel) < 0) अणु
		tuner_err("Unable to read tuner registers.\n");
		जाओ fail;
	पूर्ण

	tuner_dbg("Device is Xceive %d version %d.%d, firmware version %d.%d\n",
		  hwmodel, (version & 0xf000) >> 12, (version & 0xf00) >> 8,
		  (version & 0xf0) >> 4, version & 0xf);


	अगर (priv->ctrl.पढ़ो_not_reliable)
		जाओ पढ़ो_not_reliable;

	/* Check firmware version against what we करोwnloaded. */
	अगर (priv->firm_version != ((version & 0xf0) << 4 | (version & 0x0f))) अणु
		अगर (!priv->ctrl.पढ़ो_not_reliable) अणु
			tuner_err("Incorrect readback of firmware version.\n");
			जाओ fail;
		पूर्ण अन्यथा अणु
			tuner_err("Returned an incorrect version. However, read is not reliable enough. Ignoring it.\n");
			hwmodel = 3028;
		पूर्ण
	पूर्ण

	/* Check that the tuner hardware model reमुख्यs consistent over समय. */
	अगर (priv->hwmodel == 0 && (hwmodel == 2028 || hwmodel == 3028)) अणु
		priv->hwmodel = hwmodel;
		priv->hwvers  = version & 0xff00;
	पूर्ण अन्यथा अगर (priv->hwmodel == 0 || priv->hwmodel != hwmodel ||
		   priv->hwvers != (version & 0xff00)) अणु
		tuner_err("Read invalid device hardware information - tuner hung?\n");
		जाओ fail;
	पूर्ण

पढ़ो_not_reliable:
	priv->cur_fw = new_fw;

	/*
	 * By setting BASE in cur_fw.type only after successfully loading all
	 * firmwares, we can:
	 * 1. Identअगरy that BASE firmware with type=0 has been loaded;
	 * 2. Tell whether BASE firmware was just changed the next समय through.
	 */
	priv->cur_fw.type |= BASE;
	priv->state = XC2028_ACTIVE;

	वापस 0;

fail:
	मुक्त_firmware(priv);

	अगर (retry_count < 8) अणु
		msleep(50);
		retry_count++;
		tuner_dbg("Retrying firmware load\n");
		जाओ retry;
	पूर्ण

	/* Firmware didn't load. Put the device to sleep */
	xc2028_sleep(fe);

	अगर (rc == -ENOENT)
		rc = -EINVAL;
	वापस rc;
पूर्ण

अटल पूर्णांक xc2028_संकेत(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा xc2028_data *priv = fe->tuner_priv;
	u16                 frq_lock, संकेत = 0;
	पूर्णांक                 rc, i;

	tuner_dbg("%s called\n", __func__);

	rc = check_device_status(priv);
	अगर (rc < 0)
		वापस rc;

	/* If the device is sleeping, no channel is tuned */
	अगर (!rc) अणु
		*strength = 0;
		वापस 0;
	पूर्ण

	mutex_lock(&priv->lock);

	/* Sync Lock Indicator */
	क्रम (i = 0; i < 3; i++) अणु
		rc = xc2028_get_reg(priv, XREG_LOCK, &frq_lock);
		अगर (rc < 0)
			जाओ ret;

		अगर (frq_lock)
			अवरोध;
		msleep(6);
	पूर्ण

	/* Frequency didn't lock */
	अगर (frq_lock == 2)
		जाओ ret;

	/* Get SNR of the video संकेत */
	rc = xc2028_get_reg(priv, XREG_SNR, &संकेत);
	अगर (rc < 0)
		जाओ ret;

	/* Signal level is 3 bits only */

	संकेत = ((1 << 12) - 1) | ((संकेत & 0x07) << 12);

ret:
	mutex_unlock(&priv->lock);

	*strength = संकेत;

	tuner_dbg("signal strength is %d\n", संकेत);

	वापस rc;
पूर्ण

अटल पूर्णांक xc2028_get_afc(काष्ठा dvb_frontend *fe, s32 *afc)
अणु
	काष्ठा xc2028_data *priv = fe->tuner_priv;
	पूर्णांक i, rc;
	u16 frq_lock = 0;
	s16 afc_reg = 0;

	rc = check_device_status(priv);
	अगर (rc < 0)
		वापस rc;

	/* If the device is sleeping, no channel is tuned */
	अगर (!rc) अणु
		*afc = 0;
		वापस 0;
	पूर्ण

	mutex_lock(&priv->lock);

	/* Sync Lock Indicator */
	क्रम (i = 0; i < 3; i++) अणु
		rc = xc2028_get_reg(priv, XREG_LOCK, &frq_lock);
		अगर (rc < 0)
			जाओ ret;

		अगर (frq_lock)
			अवरोध;
		msleep(6);
	पूर्ण

	/* Frequency didn't lock */
	अगर (frq_lock == 2)
		जाओ ret;

	/* Get AFC */
	rc = xc2028_get_reg(priv, XREG_FREQ_ERROR, &afc_reg);
	अगर (rc < 0)
		जाओ ret;

	*afc = afc_reg * 15625; /* Hz */

	tuner_dbg("AFC is %d Hz\n", *afc);

ret:
	mutex_unlock(&priv->lock);

	वापस rc;
पूर्ण

#घोषणा DIV 15625

अटल पूर्णांक generic_set_freq(काष्ठा dvb_frontend *fe, u32 freq /* in HZ */,
			    क्रमागत v4l2_tuner_type new_type,
			    अचिन्हित पूर्णांक type,
			    v4l2_std_id std,
			    u16 पूर्णांक_freq)
अणु
	काष्ठा xc2028_data *priv = fe->tuner_priv;
	पूर्णांक		   rc = -EINVAL;
	अचिन्हित अक्षर	   buf[4];
	u32		   भाग, offset = 0;

	tuner_dbg("%s called\n", __func__);

	mutex_lock(&priv->lock);

	tuner_dbg("should set frequency %d kHz\n", freq / 1000);

	अगर (check_firmware(fe, type, std, पूर्णांक_freq) < 0)
		जाओ ret;

	/* On some हालs xc2028 can disable video output, अगर
	 * very weak संकेतs are received. By sending a soft
	 * reset, this is re-enabled. So, it is better to always
	 * send a soft reset beक्रमe changing channels, to be sure
	 * that xc2028 will be in a safe state.
	 * Maybe this might also be needed क्रम DTV.
	 */
	चयन (new_type) अणु
	हाल V4L2_TUNER_ANALOG_TV:
		rc = send_seq(priv, अणु0x00, 0x00पूर्ण);

		/* Analog mode requires offset = 0 */
		अवरोध;
	हाल V4L2_TUNER_RADIO:
		/* Radio mode requires offset = 0 */
		अवरोध;
	हाल V4L2_TUNER_DIGITAL_TV:
		/*
		 * Digital modes require an offset to adjust to the
		 * proper frequency. The offset depends on what
		 * firmware version is used.
		 */

		/*
		 * Adjust to the center frequency. This is calculated by the
		 * क्रमmula: offset = 1.25MHz - BW/2
		 * For DTV 7/8, the firmware uses BW = 8000, so it needs a
		 * further adjusपंचांगent to get the frequency center on VHF
		 */

		/*
		 * The firmware DTV78 used to work fine in UHF band (8 MHz
		 * bandwidth) but not at all in VHF band (7 MHz bandwidth).
		 * The real problem was connected to the क्रमmula used to
		 * calculate the center frequency offset in VHF band.
		 * In fact, removing the 500KHz adjusपंचांगent fixed the problem.
		 * This is coherent to what was implemented क्रम the DTV7
		 * firmware.
		 * In the end, now the center frequency is the same क्रम all 3
		 * firmwares (DTV7, DTV8, DTV78) and करोesn't depend on channel
		 * bandwidth.
		 */

		अगर (priv->cur_fw.type & DTV6)
			offset = 1750000;
		अन्यथा	/* DTV7 or DTV8 or DTV78 */
			offset = 2750000;

		/*
		 * xc3028 additional "magic"
		 * Depending on the firmware version, it needs some adjusपंचांगents
		 * to properly centralize the frequency. This seems to be
		 * needed to compensate the SCODE table adjusपंचांगents made by
		 * newer firmwares
		 */

		/*
		 * The proper adjusपंचांगent would be to करो it at s-code table.
		 * However, this didn't work, as reported by
		 * Robert Lowery <rglowery@exemail.com.au>
		 */

#अगर 0
		/*
		 * Still need tests क्रम XC3028L (firmware 3.2 or upper)
		 * So, क्रम now, let's just comment the per-firmware
		 * version of this change. Reports with xc3028l working
		 * with and without the lines below are welcome
		 */

		अगर (priv->firm_version < 0x0302) अणु
			अगर (priv->cur_fw.type & DTV7)
				offset += 500000;
		पूर्ण अन्यथा अणु
			अगर (priv->cur_fw.type & DTV7)
				offset -= 300000;
			अन्यथा अगर (type != ATSC) /* DVB @6MHz, DTV 8 and DTV 7/8 */
				offset += 200000;
		पूर्ण
#पूर्ण_अगर
		अवरोध;
	शेष:
		tuner_err("Unsupported tuner type %d.\n", new_type);
		अवरोध;
	पूर्ण

	भाग = (freq - offset + DIV / 2) / DIV;

	/* CMD= Set frequency */
	अगर (priv->firm_version < 0x0202)
		rc = send_seq(priv, अणु0x00, XREG_RF_FREQ, 0x00, 0x00पूर्ण);
	अन्यथा
		rc = send_seq(priv, अणु0x80, XREG_RF_FREQ, 0x00, 0x00पूर्ण);
	अगर (rc < 0)
		जाओ ret;

	/* Return code shouldn't be checked.
	   The reset CLK is needed only with पंचांग6000.
	   Driver should work fine even अगर this fails.
	 */
	अगर (priv->ctrl.msleep)
		msleep(priv->ctrl.msleep);
	करो_tuner_callback(fe, XC2028_RESET_CLK, 1);

	msleep(10);

	buf[0] = 0xff & (भाग >> 24);
	buf[1] = 0xff & (भाग >> 16);
	buf[2] = 0xff & (भाग >> 8);
	buf[3] = 0xff & (भाग);

	rc = i2c_send(priv, buf, माप(buf));
	अगर (rc < 0)
		जाओ ret;
	msleep(100);

	priv->frequency = freq;

	tuner_dbg("divisor= %*ph (freq=%d.%03d)\n", 4, buf,
	       freq / 1000000, (freq % 1000000) / 1000);

	rc = 0;

ret:
	mutex_unlock(&priv->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक xc2028_set_analog_freq(काष्ठा dvb_frontend *fe,
			      काष्ठा analog_parameters *p)
अणु
	काष्ठा xc2028_data *priv = fe->tuner_priv;
	अचिन्हित पूर्णांक       type=0;

	tuner_dbg("%s called\n", __func__);

	अगर (p->mode == V4L2_TUNER_RADIO) अणु
		type |= FM;
		अगर (priv->ctrl.input1)
			type |= INPUT1;
		वापस generic_set_freq(fe, (625l * p->frequency) / 10,
				V4L2_TUNER_RADIO, type, 0, 0);
	पूर्ण

	/* अगर std is not defined, choose one */
	अगर (!p->std)
		p->std = V4L2_STD_MN;

	/* PAL/M, PAL/N, PAL/Nc and NTSC variants should use 6MHz firmware */
	अगर (!(p->std & V4L2_STD_MN))
		type |= F8MHZ;

	/* Add audio hack to std mask */
	p->std |= parse_audio_std_option();

	वापस generic_set_freq(fe, 62500l * p->frequency,
				V4L2_TUNER_ANALOG_TV, type, p->std, 0);
पूर्ण

अटल पूर्णांक xc2028_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 delsys = c->delivery_प्रणाली;
	u32 bw = c->bandwidth_hz;
	काष्ठा xc2028_data *priv = fe->tuner_priv;
	पूर्णांक rc;
	अचिन्हित पूर्णांक       type = 0;
	u16                demod = 0;

	tuner_dbg("%s called\n", __func__);

	rc = check_device_status(priv);
	अगर (rc < 0)
		वापस rc;

	चयन (delsys) अणु
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		/*
		 * The only countries with 6MHz seem to be Taiwan/Uruguay.
		 * Both seem to require QAM firmware क्रम OFDM decoding
		 * Tested in Taiwan by Terry Wu <terrywu2009@gmail.com>
		 */
		अगर (bw <= 6000000)
			type |= QAM;

		चयन (priv->ctrl.type) अणु
		हाल XC2028_D2633:
			type |= D2633;
			अवरोध;
		हाल XC2028_D2620:
			type |= D2620;
			अवरोध;
		हाल XC2028_AUTO:
		शेष:
			/* Zarlink seems to need D2633 */
			अगर (priv->ctrl.demod == XC3028_FE_ZARLINK456)
				type |= D2633;
			अन्यथा
				type |= D2620;
		पूर्ण
		अवरोध;
	हाल SYS_ATSC:
		/* The only ATSC firmware (at least on v2.7) is D2633 */
		type |= ATSC | D2633;
		अवरोध;
	/* DVB-S and pure QAM (FE_QAM) are not supported */
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (bw <= 6000000) अणु
		type |= DTV6;
		priv->ctrl.vhfbw7 = 0;
		priv->ctrl.uhfbw8 = 0;
	पूर्ण अन्यथा अगर (bw <= 7000000) अणु
		अगर (c->frequency < 470000000)
			priv->ctrl.vhfbw7 = 1;
		अन्यथा
			priv->ctrl.uhfbw8 = 0;
		type |= (priv->ctrl.vhfbw7 && priv->ctrl.uhfbw8) ? DTV78 : DTV7;
		type |= F8MHZ;
	पूर्ण अन्यथा अणु
		अगर (c->frequency < 470000000)
			priv->ctrl.vhfbw7 = 0;
		अन्यथा
			priv->ctrl.uhfbw8 = 1;
		type |= (priv->ctrl.vhfbw7 && priv->ctrl.uhfbw8) ? DTV78 : DTV8;
		type |= F8MHZ;
	पूर्ण

	/* All S-code tables need a 200kHz shअगरt */
	अगर (priv->ctrl.demod) अणु
		demod = priv->ctrl.demod;

		/*
		 * Newer firmwares require a 200 kHz offset only क्रम ATSC
		 */
		अगर (type == ATSC || priv->firm_version < 0x0302)
			demod += 200;
		/*
		 * The DTV7 S-code table needs a 700 kHz shअगरt.
		 *
		 * DTV7 is only used in Australia.  Germany or Italy may also
		 * use this firmware after initialization, but a tune to a UHF
		 * channel should then cause DTV78 to be used.
		 *
		 * Unक्रमtunately, on real-field tests, the s-code offset
		 * didn't work as expected, as reported by
		 * Robert Lowery <rglowery@exemail.com.au>
		 */
	पूर्ण

	वापस generic_set_freq(fe, c->frequency,
				V4L2_TUNER_DIGITAL_TV, type, 0, demod);
पूर्ण

अटल पूर्णांक xc2028_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc2028_data *priv = fe->tuner_priv;
	पूर्णांक rc;

	rc = check_device_status(priv);
	अगर (rc < 0)
		वापस rc;

	/* Device is alपढ़ोy in sleep mode */
	अगर (!rc)
		वापस 0;

	/* Aव्योम firmware reload on slow devices or अगर PM disabled */
	अगर (no_घातeroff || priv->ctrl.disable_घातer_mgmt)
		वापस 0;

	tuner_dbg("Putting xc2028/3028 into poweroff mode.\n");
	अगर (debug > 1) अणु
		tuner_dbg("Printing sleep stack trace:\n");
		dump_stack();
	पूर्ण

	mutex_lock(&priv->lock);

	अगर (priv->firm_version < 0x0202)
		rc = send_seq(priv, अणु0x00, XREG_POWER_DOWN, 0x00, 0x00पूर्ण);
	अन्यथा
		rc = send_seq(priv, अणु0x80, XREG_POWER_DOWN, 0x00, 0x00पूर्ण);

	अगर (rc >= 0)
		priv->state = XC2028_SLEEP;

	mutex_unlock(&priv->lock);

	वापस rc;
पूर्ण

अटल व्योम xc2028_dvb_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc2028_data *priv = fe->tuner_priv;

	tuner_dbg("%s called\n", __func__);

	mutex_lock(&xc2028_list_mutex);

	/* only perक्रमm final cleanup अगर this is the last instance */
	अगर (hybrid_tuner_report_instance_count(priv) == 1)
		मुक्त_firmware(priv);

	अगर (priv)
		hybrid_tuner_release_state(priv);

	mutex_unlock(&xc2028_list_mutex);

	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक xc2028_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा xc2028_data *priv = fe->tuner_priv;
	पूर्णांक rc;

	tuner_dbg("%s called\n", __func__);

	rc = check_device_status(priv);
	अगर (rc < 0)
		वापस rc;

	*frequency = priv->frequency;

	वापस 0;
पूर्ण

अटल व्योम load_firmware_cb(स्थिर काष्ठा firmware *fw,
			     व्योम *context)
अणु
	काष्ठा dvb_frontend *fe = context;
	काष्ठा xc2028_data *priv = fe->tuner_priv;
	पूर्णांक rc;

	tuner_dbg("request_firmware_nowait(): %s\n", fw ? "OK" : "error");
	अगर (!fw) अणु
		tuner_err("Could not load firmware %s.\n", priv->fname);
		priv->state = XC2028_NODEV;
		वापस;
	पूर्ण

	rc = load_all_firmwares(fe, fw);

	release_firmware(fw);

	अगर (rc < 0)
		वापस;
	priv->state = XC2028_ACTIVE;
पूर्ण

अटल पूर्णांक xc2028_set_config(काष्ठा dvb_frontend *fe, व्योम *priv_cfg)
अणु
	काष्ठा xc2028_data *priv = fe->tuner_priv;
	काष्ठा xc2028_ctrl *p    = priv_cfg;
	पूर्णांक                 rc   = 0;

	tuner_dbg("%s called\n", __func__);

	mutex_lock(&priv->lock);

	/*
	 * Copy the config data.
	 */
	स_नकल(&priv->ctrl, p, माप(priv->ctrl));

	/*
	 * If firmware name changed, मुक्तs firmware. As मुक्त_firmware will
	 * reset the status to NO_FIRMWARE, this क्रमces a new request_firmware
	 */
	अगर (!firmware_name[0] && p->fname &&
	    priv->fname && म_भेद(p->fname, priv->fname))
		मुक्त_firmware(priv);

	अगर (priv->ctrl.max_len < 9)
		priv->ctrl.max_len = 13;

	अगर (priv->state == XC2028_NO_FIRMWARE) अणु
		अगर (!firmware_name[0])
			priv->fname = kstrdup(p->fname, GFP_KERNEL);
		अन्यथा
			priv->fname = firmware_name;

		अगर (!priv->fname) अणु
			rc = -ENOMEM;
			जाओ unlock;
		पूर्ण

		rc = request_firmware_noरुको(THIS_MODULE, 1,
					     priv->fname,
					     priv->i2c_props.adap->dev.parent,
					     GFP_KERNEL,
					     fe, load_firmware_cb);
		अगर (rc < 0) अणु
			tuner_err("Failed to request firmware %s\n",
				  priv->fname);
			priv->state = XC2028_NODEV;
		पूर्ण अन्यथा
			priv->state = XC2028_WAITING_FIRMWARE;
	पूर्ण
unlock:
	mutex_unlock(&priv->lock);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops xc2028_dvb_tuner_ops = अणु
	.info = अणु
		 .name = "Xceive XC3028",
		 .frequency_min_hz  =  42 * MHz,
		 .frequency_max_hz  = 864 * MHz,
		 .frequency_step_hz =  50 * kHz,
		 पूर्ण,

	.set_config	   = xc2028_set_config,
	.set_analog_params = xc2028_set_analog_freq,
	.release           = xc2028_dvb_release,
	.get_frequency     = xc2028_get_frequency,
	.get_rf_strength   = xc2028_संकेत,
	.get_afc           = xc2028_get_afc,
	.set_params        = xc2028_set_params,
	.sleep             = xc2028_sleep,
पूर्ण;

काष्ठा dvb_frontend *xc2028_attach(काष्ठा dvb_frontend *fe,
				   काष्ठा xc2028_config *cfg)
अणु
	काष्ठा xc2028_data *priv;
	पूर्णांक instance;

	अगर (debug)
		prपूर्णांकk(KERN_DEBUG "xc2028: Xcv2028/3028 init called!\n");

	अगर (शून्य == cfg)
		वापस शून्य;

	अगर (!fe) अणु
		prपूर्णांकk(KERN_ERR "xc2028: No frontend!\n");
		वापस शून्य;
	पूर्ण

	mutex_lock(&xc2028_list_mutex);

	instance = hybrid_tuner_request_state(काष्ठा xc2028_data, priv,
					      hybrid_tuner_instance_list,
					      cfg->i2c_adap, cfg->i2c_addr,
					      "xc2028");
	चयन (instance) अणु
	हाल 0:
		/* memory allocation failure */
		जाओ fail;
	हाल 1:
		/* new tuner instance */
		priv->ctrl.max_len = 13;

		mutex_init(&priv->lock);

		fe->tuner_priv = priv;
		अवरोध;
	हाल 2:
		/* existing tuner instance */
		fe->tuner_priv = priv;
		अवरोध;
	पूर्ण

	स_नकल(&fe->ops.tuner_ops, &xc2028_dvb_tuner_ops,
	       माप(xc2028_dvb_tuner_ops));

	tuner_info("type set to %s\n", "XCeive xc2028/xc3028 tuner");

	अगर (cfg->ctrl)
		xc2028_set_config(fe, cfg->ctrl);

	mutex_unlock(&xc2028_list_mutex);

	वापस fe;
fail:
	mutex_unlock(&xc2028_list_mutex);

	xc2028_dvb_release(fe);
	वापस शून्य;
पूर्ण

EXPORT_SYMBOL(xc2028_attach);

MODULE_DESCRIPTION("Xceive xc2028/xc3028 tuner driver");
MODULE_AUTHOR("Michel Ludwig <michel.ludwig@gmail.com>");
MODULE_AUTHOR("Mauro Carvalho Chehab <mchehab@kernel.org>");
MODULE_LICENSE("GPL v2");
MODULE_FIRMWARE(XC2028_DEFAULT_FIRMWARE);
MODULE_FIRMWARE(XC3028L_DEFAULT_FIRMWARE);
