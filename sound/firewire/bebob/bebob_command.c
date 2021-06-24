<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * bebob_command.c - driver क्रम BeBoB based devices
 *
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

#समावेश "./bebob.h"

पूर्णांक avc_audio_set_selector(काष्ठा fw_unit *unit, अचिन्हित पूर्णांक subunit_id,
			   अचिन्हित पूर्णांक fb_id, अचिन्हित पूर्णांक num)
अणु
	u8 *buf;
	पूर्णांक err;

	buf = kzalloc(12, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	buf[0]  = 0x00;		/* AV/C CONTROL */
	buf[1]  = 0x08 | (0x07 & subunit_id);	/* AUDIO SUBUNIT ID */
	buf[2]  = 0xb8;		/* FUNCTION BLOCK  */
	buf[3]  = 0x80;		/* type is 'selector'*/
	buf[4]  = 0xff & fb_id;	/* function block id */
	buf[5]  = 0x10;		/* control attribute is CURRENT */
	buf[6]  = 0x02;		/* selector length is 2 */
	buf[7]  = 0xff & num;	/* input function block plug number */
	buf[8]  = 0x01;		/* control selector is SELECTOR_CONTROL */

	err = fcp_avc_transaction(unit, buf, 12, buf, 12,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7) | BIT(8));
	अगर (err < 0)
		;
	अन्यथा अगर (err < 9)
		err = -EIO;
	अन्यथा अगर (buf[0] == 0x08) /* NOT IMPLEMENTED */
		err = -ENOSYS;
	अन्यथा अगर (buf[0] == 0x0a) /* REJECTED */
		err = -EINVAL;
	अन्यथा
		err = 0;

	kमुक्त(buf);
	वापस err;
पूर्ण

पूर्णांक avc_audio_get_selector(काष्ठा fw_unit *unit, अचिन्हित पूर्णांक subunit_id,
			   अचिन्हित पूर्णांक fb_id, अचिन्हित पूर्णांक *num)
अणु
	u8 *buf;
	पूर्णांक err;

	buf = kzalloc(12, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	buf[0]  = 0x01;		/* AV/C STATUS */
	buf[1]  = 0x08 | (0x07 & subunit_id);	/* AUDIO SUBUNIT ID */
	buf[2]  = 0xb8;		/* FUNCTION BLOCK */
	buf[3]  = 0x80;		/* type is 'selector'*/
	buf[4]  = 0xff & fb_id;	/* function block id */
	buf[5]  = 0x10;		/* control attribute is CURRENT */
	buf[6]  = 0x02;		/* selector length is 2 */
	buf[7]  = 0xff;		/* input function block plug number */
	buf[8]  = 0x01;		/* control selector is SELECTOR_CONTROL */

	err = fcp_avc_transaction(unit, buf, 12, buf, 12,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(8));
	अगर (err < 0)
		;
	अन्यथा अगर (err < 9)
		err = -EIO;
	अन्यथा अगर (buf[0] == 0x08) /* NOT IMPLEMENTED */
		err = -ENOSYS;
	अन्यथा अगर (buf[0] == 0x0a) /* REJECTED */
		err = -EINVAL;
	अन्यथा अगर (buf[0] == 0x0b) /* IN TRANSITION */
		err = -EAGAIN;
	अगर (err < 0)
		जाओ end;

	*num = buf[7];
	err = 0;
end:
	kमुक्त(buf);
	वापस err;
पूर्ण

अटल अंतरभूत व्योम
avc_bridgeco_fill_extension_addr(u8 *buf, u8 *addr)
अणु
	buf[1] = addr[0];
	स_नकल(buf + 4, addr + 1, 5);
पूर्ण

अटल अंतरभूत व्योम
avc_bridgeco_fill_plug_info_extension_command(u8 *buf, u8 *addr,
					      अचिन्हित पूर्णांक itype)
अणु
	buf[0] = 0x01;	/* AV/C STATUS */
	buf[2] = 0x02;	/* AV/C GENERAL PLUG INFO */
	buf[3] = 0xc0;	/* BridgeCo extension */
	avc_bridgeco_fill_extension_addr(buf, addr);
	buf[9] = itype;	/* info type */
पूर्ण

पूर्णांक avc_bridgeco_get_plug_type(काष्ठा fw_unit *unit,
			       u8 addr[AVC_BRIDGECO_ADDR_BYTES],
			       क्रमागत avc_bridgeco_plug_type *type)
अणु
	u8 *buf;
	पूर्णांक err;

	buf = kzalloc(12, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	/* Info type is 'plug type'. */
	avc_bridgeco_fill_plug_info_extension_command(buf, addr, 0x00);

	err = fcp_avc_transaction(unit, buf, 12, buf, 12,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7) | BIT(9));
	अगर (err < 0)
		;
	अन्यथा अगर (err < 11)
		err = -EIO;
	अन्यथा अगर (buf[0] == 0x08) /* NOT IMPLEMENTED */
		err = -ENOSYS;
	अन्यथा अगर (buf[0] == 0x0a) /* REJECTED */
		err = -EINVAL;
	अन्यथा अगर (buf[0] == 0x0b) /* IN TRANSITION */
		err = -EAGAIN;
	अगर (err < 0)
		जाओ end;

	*type = buf[10];
	err = 0;
end:
	kमुक्त(buf);
	वापस err;
पूर्ण

पूर्णांक avc_bridgeco_get_plug_ch_count(काष्ठा fw_unit *unit, u8 addr[AVC_BRIDGECO_ADDR_BYTES],
				   अचिन्हित पूर्णांक *ch_count)
अणु
	u8 *buf;
	पूर्णांक err;

	buf = kzalloc(12, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	// Info type is 'plug type'.
	avc_bridgeco_fill_plug_info_extension_command(buf, addr, 0x02);

	err = fcp_avc_transaction(unit, buf, 12, buf, 12,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7) | BIT(9));
	अगर (err < 0)
		;
	अन्यथा अगर (err < 11)
		err = -EIO;
	अन्यथा अगर (buf[0] == 0x08) // NOT IMPLEMENTED
		err = -ENOSYS;
	अन्यथा अगर (buf[0] == 0x0a) // REJECTED
		err = -EINVAL;
	अन्यथा अगर (buf[0] == 0x0b) // IN TRANSITION
		err = -EAGAIN;
	अगर (err < 0)
		जाओ end;

	*ch_count = buf[10];
	err = 0;
end:
	kमुक्त(buf);
	वापस err;
पूर्ण

पूर्णांक avc_bridgeco_get_plug_ch_pos(काष्ठा fw_unit *unit,
				 u8 addr[AVC_BRIDGECO_ADDR_BYTES],
				 u8 *buf, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक err;

	/* Info type is 'channel position'. */
	avc_bridgeco_fill_plug_info_extension_command(buf, addr, 0x03);

	err = fcp_avc_transaction(unit, buf, 12, buf, 256,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) |
				  BIT(5) | BIT(6) | BIT(7) | BIT(9));
	अगर (err < 0)
		;
	अन्यथा अगर (err < 11)
		err = -EIO;
	अन्यथा अगर (buf[0] == 0x08) /* NOT IMPLEMENTED */
		err = -ENOSYS;
	अन्यथा अगर (buf[0] == 0x0a) /* REJECTED */
		err = -EINVAL;
	अन्यथा अगर (buf[0] == 0x0b) /* IN TRANSITION */
		err = -EAGAIN;
	अगर (err < 0)
		जाओ end;

	/* Pick up specअगरic data. */
	स_हटाओ(buf, buf + 10, err - 10);
	err = 0;
end:
	वापस err;
पूर्ण

पूर्णांक avc_bridgeco_get_plug_section_type(काष्ठा fw_unit *unit,
				       u8 addr[AVC_BRIDGECO_ADDR_BYTES],
				       अचिन्हित पूर्णांक id, u8 *type)
अणु
	u8 *buf;
	पूर्णांक err;

	/* section info includes अक्षरactors but this module करोn't need it */
	buf = kzalloc(12, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	/* Info type is 'section info'. */
	avc_bridgeco_fill_plug_info_extension_command(buf, addr, 0x07);
	buf[10] = 0xff & ++id;	/* section id */

	err = fcp_avc_transaction(unit, buf, 12, buf, 12,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7) | BIT(9) | BIT(10));
	अगर (err < 0)
		;
	अन्यथा अगर (err < 12)
		err = -EIO;
	अन्यथा अगर (buf[0] == 0x08) /* NOT IMPLEMENTED */
		err = -ENOSYS;
	अन्यथा अगर (buf[0] == 0x0a) /* REJECTED */
		err = -EINVAL;
	अन्यथा अगर (buf[0] == 0x0b) /* IN TRANSITION */
		err = -EAGAIN;
	अगर (err < 0)
		जाओ end;

	*type = buf[11];
	err = 0;
end:
	kमुक्त(buf);
	वापस err;
पूर्ण

पूर्णांक avc_bridgeco_get_plug_input(काष्ठा fw_unit *unit,
				u8 addr[AVC_BRIDGECO_ADDR_BYTES], u8 input[7])
अणु
	पूर्णांक err;
	u8 *buf;

	buf = kzalloc(18, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	/* Info type is 'plug input'. */
	avc_bridgeco_fill_plug_info_extension_command(buf, addr, 0x05);

	err = fcp_avc_transaction(unit, buf, 16, buf, 16,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7));
	अगर (err < 0)
		;
	अन्यथा अगर (err < 16)
		err = -EIO;
	अन्यथा अगर (buf[0] == 0x08) /* NOT IMPLEMENTED */
		err = -ENOSYS;
	अन्यथा अगर (buf[0] == 0x0a) /* REJECTED */
		err = -EINVAL;
	अन्यथा अगर (buf[0] == 0x0b) /* IN TRANSITION */
		err = -EAGAIN;
	अगर (err < 0)
		जाओ end;

	स_नकल(input, buf + 10, 5);
	err = 0;
end:
	kमुक्त(buf);
	वापस err;
पूर्ण

पूर्णांक avc_bridgeco_get_plug_strm_fmt(काष्ठा fw_unit *unit,
				   u8 addr[AVC_BRIDGECO_ADDR_BYTES], u8 *buf,
				   अचिन्हित पूर्णांक *len, अचिन्हित पूर्णांक eid)
अणु
	पूर्णांक err;

	/* check given buffer */
	अगर ((buf == शून्य) || (*len < 12)) अणु
		err = -EINVAL;
		जाओ end;
	पूर्ण

	buf[0] = 0x01;	/* AV/C STATUS */
	buf[2] = 0x2f;	/* AV/C STREAM FORMAT SUPPORT */
	buf[3] = 0xc1;	/* Bridgeco extension - List Request */
	avc_bridgeco_fill_extension_addr(buf, addr);
	buf[10] = 0xff & eid;	/* Entry ID */

	err = fcp_avc_transaction(unit, buf, 12, buf, *len,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7) | BIT(10));
	अगर (err < 0)
		;
	अन्यथा अगर (err < 12)
		err = -EIO;
	अन्यथा अगर (buf[0] == 0x08)        /* NOT IMPLEMENTED */
		err = -ENOSYS;
	अन्यथा अगर (buf[0] == 0x0a)        /* REJECTED */
		err = -EINVAL;
	अन्यथा अगर (buf[0] == 0x0b)        /* IN TRANSITION */
		err = -EAGAIN;
	अन्यथा अगर (buf[10] != eid)
		err = -EIO;
	अगर (err < 0)
		जाओ end;

	/* Pick up 'stream format info'. */
	स_हटाओ(buf, buf + 11, err - 11);
	*len = err - 11;
	err = 0;
end:
	वापस err;
पूर्ण
