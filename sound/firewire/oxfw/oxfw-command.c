<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * oxfw_command.c - a part of driver क्रम OXFW970/971 based devices
 *
 * Copyright (c) 2014 Takashi Sakamoto
 */

#समावेश "oxfw.h"

पूर्णांक avc_stream_set_क्रमmat(काष्ठा fw_unit *unit, क्रमागत avc_general_plug_dir dir,
			  अचिन्हित पूर्णांक pid, u8 *क्रमmat, अचिन्हित पूर्णांक len)
अणु
	u8 *buf;
	पूर्णांक err;

	buf = kदो_स्मृति(len + 10, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	buf[0] = 0x00;		/* CONTROL */
	buf[1] = 0xff;		/* UNIT */
	buf[2] = 0xbf;		/* EXTENDED STREAM FORMAT INFORMATION */
	buf[3] = 0xc0;		/* SINGLE subfunction */
	buf[4] = dir;		/* Plug Direction */
	buf[5] = 0x00;		/* UNIT */
	buf[6] = 0x00;		/* PCR (Isochronous Plug) */
	buf[7] = 0xff & pid;	/* Plug ID */
	buf[8] = 0xff;		/* Padding */
	buf[9] = 0xff;		/* Support status in response */
	स_नकल(buf + 10, क्रमmat, len);

	/* करो transaction and check buf[1-8] are the same against command */
	err = fcp_avc_transaction(unit, buf, len + 10, buf, len + 10,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7) | BIT(8));
	अगर (err < 0)
		;
	अन्यथा अगर (err < len + 10)
		err = -EIO;
	अन्यथा अगर (buf[0] == 0x08) /* NOT IMPLEMENTED */
		err = -ENXIO;
	अन्यथा अगर (buf[0] == 0x0a) /* REJECTED */
		err = -EINVAL;
	अन्यथा
		err = 0;

	kमुक्त(buf);

	वापस err;
पूर्ण

पूर्णांक avc_stream_get_क्रमmat(काष्ठा fw_unit *unit,
			  क्रमागत avc_general_plug_dir dir, अचिन्हित पूर्णांक pid,
			  u8 *buf, अचिन्हित पूर्णांक *len, अचिन्हित पूर्णांक eid)
अणु
	अचिन्हित पूर्णांक subfunc;
	पूर्णांक err;

	अगर (eid == 0xff)
		subfunc = 0xc0;	/* SINGLE */
	अन्यथा
		subfunc = 0xc1;	/* LIST */

	buf[0] = 0x01;		/* STATUS */
	buf[1] = 0xff;		/* UNIT */
	buf[2] = 0xbf;		/* EXTENDED STREAM FORMAT INFORMATION */
	buf[3] = subfunc;	/* SINGLE or LIST */
	buf[4] = dir;		/* Plug Direction */
	buf[5] = 0x00;		/* Unit */
	buf[6] = 0x00;		/* PCR (Isochronous Plug) */
	buf[7] = 0xff & pid;	/* Plug ID */
	buf[8] = 0xff;		/* Padding */
	buf[9] = 0xff;		/* support status in response */
	buf[10] = 0xff & eid;	/* entry ID क्रम LIST subfunction */
	buf[11] = 0xff;		/* padding */

	/* करो transaction and check buf[1-7] are the same against command */
	err = fcp_avc_transaction(unit, buf, 12, buf, *len,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7));
	अगर (err < 0)
		;
	अन्यथा अगर (err < 12)
		err = -EIO;
	अन्यथा अगर (buf[0] == 0x08)	/* NOT IMPLEMENTED */
		err = -ENXIO;
	अन्यथा अगर (buf[0] == 0x0a)	/* REJECTED */
		err = -EINVAL;
	अन्यथा अगर (buf[0] == 0x0b)	/* IN TRANSITION */
		err = -EAGAIN;
	/* LIST subfunction has entry ID */
	अन्यथा अगर ((subfunc == 0xc1) && (buf[10] != eid))
		err = -EIO;
	अगर (err < 0)
		जाओ end;

	/* keep just stream क्रमmat inक्रमmation */
	अगर (subfunc == 0xc0) अणु
		स_हटाओ(buf, buf + 10, err - 10);
		*len = err - 10;
	पूर्ण अन्यथा अणु
		स_हटाओ(buf, buf + 11, err - 11);
		*len = err - 11;
	पूर्ण

	err = 0;
end:
	वापस err;
पूर्ण

पूर्णांक avc_general_inquiry_sig_fmt(काष्ठा fw_unit *unit, अचिन्हित पूर्णांक rate,
				क्रमागत avc_general_plug_dir dir,
				अचिन्हित लघु pid)
अणु
	अचिन्हित पूर्णांक sfc;
	u8 *buf;
	पूर्णांक err;

	क्रम (sfc = 0; sfc < CIP_SFC_COUNT; sfc++) अणु
		अगर (amdtp_rate_table[sfc] == rate)
			अवरोध;
	पूर्ण
	अगर (sfc == CIP_SFC_COUNT)
		वापस -EINVAL;

	buf = kzalloc(8, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	buf[0] = 0x02;		/* SPECIFIC INQUIRY */
	buf[1] = 0xff;		/* UNIT */
	अगर (dir == AVC_GENERAL_PLUG_सूची_IN)
		buf[2] = 0x19;	/* INPUT PLUG SIGNAL FORMAT */
	अन्यथा
		buf[2] = 0x18;	/* OUTPUT PLUG SIGNAL FORMAT */
	buf[3] = 0xff & pid;	/* plug id */
	buf[4] = 0x90;		/* EOH_1, Form_1, FMT. AM824 */
	buf[5] = 0x07 & sfc;	/* FDF-hi. AM824, frequency */
	buf[6] = 0xff;		/* FDF-mid. AM824, SYT hi (not used) */
	buf[7] = 0xff;		/* FDF-low. AM824, SYT lo (not used) */

	/* करो transaction and check buf[1-5] are the same against command */
	err = fcp_avc_transaction(unit, buf, 8, buf, 8,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5));
	अगर (err < 0)
		;
	अन्यथा अगर (err < 8)
		err = -EIO;
	अन्यथा अगर (buf[0] == 0x08)	/* NOT IMPLEMENTED */
		err = -ENXIO;
	अगर (err < 0)
		जाओ end;

	err = 0;
end:
	kमुक्त(buf);
	वापस err;
पूर्ण
