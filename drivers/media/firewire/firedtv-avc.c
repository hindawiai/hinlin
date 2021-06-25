<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * FireDTV driver (क्रमmerly known as FireSAT)
 *
 * Copyright (C) 2004 Andreas Monitzer <andy@monitzer.com>
 * Copyright (C) 2008 Ben Backx <ben@bbackx.com>
 * Copyright (C) 2008 Henrik Kurelid <henrik@kurelid.se>
 */

#समावेश <linux/bug.h>
#समावेश <linux/crc32.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mutex.h>
#समावेश <linux/माला.स>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>

#समावेश <media/dvb_frontend.h>

#समावेश "firedtv.h"

#घोषणा FCP_COMMAND_REGISTER		0xfffff0000b00ULL

#घोषणा AVC_CTYPE_CONTROL		0x0
#घोषणा AVC_CTYPE_STATUS		0x1
#घोषणा AVC_CTYPE_NOTIFY		0x3

#घोषणा AVC_RESPONSE_ACCEPTED		0x9
#घोषणा AVC_RESPONSE_STABLE		0xc
#घोषणा AVC_RESPONSE_CHANGED		0xd
#घोषणा AVC_RESPONSE_INTERIM		0xf

#घोषणा AVC_SUBUNIT_TYPE_TUNER		(0x05 << 3)
#घोषणा AVC_SUBUNIT_TYPE_UNIT		(0x1f << 3)

#घोषणा AVC_OPCODE_VENDOR		0x00
#घोषणा AVC_OPCODE_READ_DESCRIPTOR	0x09
#घोषणा AVC_OPCODE_DSIT			0xc8
#घोषणा AVC_OPCODE_DSD			0xcb

#घोषणा DESCRIPTOR_TUNER_STATUS		0x80
#घोषणा DESCRIPTOR_SUBUNIT_IDENTIFIER	0x00

#घोषणा SFE_VENDOR_DE_COMPANYID_0	0x00 /* OUI of Digital Everywhere */
#घोषणा SFE_VENDOR_DE_COMPANYID_1	0x12
#घोषणा SFE_VENDOR_DE_COMPANYID_2	0x87

#घोषणा SFE_VENDOR_OPCODE_REGISTER_REMOTE_CONTROL 0x0a
#घोषणा SFE_VENDOR_OPCODE_LNB_CONTROL		0x52
#घोषणा SFE_VENDOR_OPCODE_TUNE_QPSK		0x58 /* क्रम DVB-S */

#घोषणा SFE_VENDOR_OPCODE_GET_FIRMWARE_VERSION	0x00
#घोषणा SFE_VENDOR_OPCODE_HOST2CA		0x56
#घोषणा SFE_VENDOR_OPCODE_CA2HOST		0x57
#घोषणा SFE_VENDOR_OPCODE_CISTATUS		0x59
#घोषणा SFE_VENDOR_OPCODE_TUNE_QPSK2		0x60 /* क्रम DVB-S2 */

#घोषणा SFE_VENDOR_TAG_CA_RESET			0x00
#घोषणा SFE_VENDOR_TAG_CA_APPLICATION_INFO	0x01
#घोषणा SFE_VENDOR_TAG_CA_PMT			0x02
#घोषणा SFE_VENDOR_TAG_CA_DATE_TIME		0x04
#घोषणा SFE_VENDOR_TAG_CA_MMI			0x05
#घोषणा SFE_VENDOR_TAG_CA_ENTER_MENU		0x07

#घोषणा EN50221_LIST_MANAGEMENT_ONLY	0x03
#घोषणा EN50221_TAG_APP_INFO		0x9f8021
#घोषणा EN50221_TAG_CA_INFO		0x9f8031

काष्ठा avc_command_frame अणु
	u8 ctype;
	u8 subunit;
	u8 opcode;
	u8 opeअक्रम[509];
पूर्ण;

काष्ठा avc_response_frame अणु
	u8 response;
	u8 subunit;
	u8 opcode;
	u8 opeअक्रम[509];
पूर्ण;

#घोषणा LAST_OPERAND (509 - 1)

अटल अंतरभूत व्योम clear_opeअक्रमs(काष्ठा avc_command_frame *c, पूर्णांक from, पूर्णांक to)
अणु
	स_रखो(&c->opeअक्रम[from], 0, to - from + 1);
पूर्ण

अटल व्योम pad_opeअक्रमs(काष्ठा avc_command_frame *c, पूर्णांक from)
अणु
	पूर्णांक to = ALIGN(from, 4);

	अगर (from <= to && to <= LAST_OPERAND)
		clear_opeअक्रमs(c, from, to);
पूर्ण

#घोषणा AVC_DEBUG_READ_DESCRIPTOR              0x0001
#घोषणा AVC_DEBUG_DSIT                         0x0002
#घोषणा AVC_DEBUG_DSD                          0x0004
#घोषणा AVC_DEBUG_REGISTER_REMOTE_CONTROL      0x0008
#घोषणा AVC_DEBUG_LNB_CONTROL                  0x0010
#घोषणा AVC_DEBUG_TUNE_QPSK                    0x0020
#घोषणा AVC_DEBUG_TUNE_QPSK2                   0x0040
#घोषणा AVC_DEBUG_HOST2CA                      0x0080
#घोषणा AVC_DEBUG_CA2HOST                      0x0100
#घोषणा AVC_DEBUG_APPLICATION_PMT              0x4000
#घोषणा AVC_DEBUG_FCP_PAYLOADS                 0x8000

अटल पूर्णांक avc_debug;
module_param_named(debug, avc_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Verbose logging (none = 0"
	", FCP subactions"
	": READ DESCRIPTOR = "		__stringअगरy(AVC_DEBUG_READ_DESCRIPTOR)
	", DSIT = "			__stringअगरy(AVC_DEBUG_DSIT)
	", REGISTER_REMOTE_CONTROL = "	__stringअगरy(AVC_DEBUG_REGISTER_REMOTE_CONTROL)
	", LNB CONTROL = "		__stringअगरy(AVC_DEBUG_LNB_CONTROL)
	", TUNE QPSK = "		__stringअगरy(AVC_DEBUG_TUNE_QPSK)
	", TUNE QPSK2 = "		__stringअगरy(AVC_DEBUG_TUNE_QPSK2)
	", HOST2CA = "			__stringअगरy(AVC_DEBUG_HOST2CA)
	", CA2HOST = "			__stringअगरy(AVC_DEBUG_CA2HOST)
	"; Application sent PMT = "	__stringअगरy(AVC_DEBUG_APPLICATION_PMT)
	", FCP payloads = "		__stringअगरy(AVC_DEBUG_FCP_PAYLOADS)
	", or a combination, or all = -1)");

/*
 * This is a workaround since there is no venकरोr specअगरic command to retrieve
 * ca_info using AVC. If this parameter is not used, ca_प्रणाली_id will be
 * filled with application_manufacturer from ca_app_info.
 * Digital Everywhere have said that adding ca_info is on their TODO list.
 */
अटल अचिन्हित पूर्णांक num_fake_ca_प्रणाली_ids;
अटल पूर्णांक fake_ca_प्रणाली_ids[4] = अणु -1, -1, -1, -1 पूर्ण;
module_param_array(fake_ca_प्रणाली_ids, पूर्णांक, &num_fake_ca_प्रणाली_ids, 0644);
MODULE_PARM_DESC(fake_ca_प्रणाली_ids, "If your CAM application manufacturer "
		 "does not have the same ca_system_id as your CAS, you can "
		 "override what ca_system_ids are presented to the "
		 "application by setting this field to an array of ids.");

अटल स्थिर अक्षर *debug_fcp_ctype(अचिन्हित पूर्णांक ctype)
अणु
	अटल स्थिर अक्षर *ctypes[] = अणु
		[0x0] = "CONTROL",		[0x1] = "STATUS",
		[0x2] = "SPECIFIC INQUIRY",	[0x3] = "NOTIFY",
		[0x4] = "GENERAL INQUIRY",	[0x8] = "NOT IMPLEMENTED",
		[0x9] = "ACCEPTED",		[0xa] = "REJECTED",
		[0xb] = "IN TRANSITION",	[0xc] = "IMPLEMENTED/STABLE",
		[0xd] = "CHANGED",		[0xf] = "INTERIM",
	पूर्ण;
	स्थिर अक्षर *ret = ctype < ARRAY_SIZE(ctypes) ? ctypes[ctype] : शून्य;

	वापस ret ? ret : "?";
पूर्ण

अटल स्थिर अक्षर *debug_fcp_opcode(अचिन्हित पूर्णांक opcode,
				    स्थिर u8 *data, पूर्णांक length)
अणु
	चयन (opcode) अणु
	हाल AVC_OPCODE_VENDOR:
		अवरोध;
	हाल AVC_OPCODE_READ_DESCRIPTOR:
		वापस avc_debug & AVC_DEBUG_READ_DESCRIPTOR ?
				"ReadDescriptor" : शून्य;
	हाल AVC_OPCODE_DSIT:
		वापस avc_debug & AVC_DEBUG_DSIT ?
				"DirectSelectInfo.Type" : शून्य;
	हाल AVC_OPCODE_DSD:
		वापस avc_debug & AVC_DEBUG_DSD ? "DirectSelectData" : शून्य;
	शेष:
		वापस "Unknown";
	पूर्ण

	अगर (length < 7 ||
	    data[3] != SFE_VENDOR_DE_COMPANYID_0 ||
	    data[4] != SFE_VENDOR_DE_COMPANYID_1 ||
	    data[5] != SFE_VENDOR_DE_COMPANYID_2)
		वापस "Vendor/Unknown";

	चयन (data[6]) अणु
	हाल SFE_VENDOR_OPCODE_REGISTER_REMOTE_CONTROL:
		वापस avc_debug & AVC_DEBUG_REGISTER_REMOTE_CONTROL ?
				"RegisterRC" : शून्य;
	हाल SFE_VENDOR_OPCODE_LNB_CONTROL:
		वापस avc_debug & AVC_DEBUG_LNB_CONTROL ? "LNBControl" : शून्य;
	हाल SFE_VENDOR_OPCODE_TUNE_QPSK:
		वापस avc_debug & AVC_DEBUG_TUNE_QPSK ? "TuneQPSK" : शून्य;
	हाल SFE_VENDOR_OPCODE_TUNE_QPSK2:
		वापस avc_debug & AVC_DEBUG_TUNE_QPSK2 ? "TuneQPSK2" : शून्य;
	हाल SFE_VENDOR_OPCODE_HOST2CA:
		वापस avc_debug & AVC_DEBUG_HOST2CA ? "Host2CA" : शून्य;
	हाल SFE_VENDOR_OPCODE_CA2HOST:
		वापस avc_debug & AVC_DEBUG_CA2HOST ? "CA2Host" : शून्य;
	पूर्ण
	वापस "Vendor/Unknown";
पूर्ण

अटल व्योम debug_fcp(स्थिर u8 *data, पूर्णांक length)
अणु
	अचिन्हित पूर्णांक subunit_type, subunit_id, opcode;
	स्थिर अक्षर *op, *prefix;

	prefix       = data[0] > 7 ? "FCP <- " : "FCP -> ";
	subunit_type = data[1] >> 3;
	subunit_id   = data[1] & 7;
	opcode       = subunit_type == 0x1e || subunit_id == 5 ? ~0 : data[2];
	op           = debug_fcp_opcode(opcode, data, length);

	अगर (op) अणु
		prपूर्णांकk(KERN_INFO "%ssu=%x.%x l=%d: %-8s - %s\n",
		       prefix, subunit_type, subunit_id, length,
		       debug_fcp_ctype(data[0]), op);
		अगर (avc_debug & AVC_DEBUG_FCP_PAYLOADS)
			prपूर्णांक_hex_dump(KERN_INFO, prefix, DUMP_PREFIX_NONE,
				       16, 1, data, length, false);
	पूर्ण
पूर्ण

अटल व्योम debug_pmt(अक्षर *msg, पूर्णांक length)
अणु
	prपूर्णांकk(KERN_INFO "APP PMT -> l=%d\n", length);
	prपूर्णांक_hex_dump(KERN_INFO, "APP PMT -> ", DUMP_PREFIX_NONE,
		       16, 1, msg, length, false);
पूर्ण

अटल पूर्णांक avc_ग_लिखो(काष्ठा firedtv *fdtv)
अणु
	पूर्णांक err, retry;

	fdtv->avc_reply_received = false;

	क्रम (retry = 0; retry < 6; retry++) अणु
		अगर (unlikely(avc_debug))
			debug_fcp(fdtv->avc_data, fdtv->avc_data_length);

		err = fdtv_ग_लिखो(fdtv, FCP_COMMAND_REGISTER,
				 fdtv->avc_data, fdtv->avc_data_length);
		अगर (err) अणु
			dev_err(fdtv->device, "FCP command write failed\n");

			वापस err;
		पूर्ण

		/*
		 * AV/C specs say that answers should be sent within 150 ms.
		 * Time out after 200 ms.
		 */
		अगर (रुको_event_समयout(fdtv->avc_रुको,
				       fdtv->avc_reply_received,
				       msecs_to_jअगरfies(200)) != 0)
			वापस 0;
	पूर्ण
	dev_err(fdtv->device, "FCP response timed out\n");

	वापस -ETIMEDOUT;
पूर्ण

अटल bool is_रेजिस्टर_rc(काष्ठा avc_response_frame *r)
अणु
	वापस r->opcode     == AVC_OPCODE_VENDOR &&
	       r->opeअक्रम[0] == SFE_VENDOR_DE_COMPANYID_0 &&
	       r->opeअक्रम[1] == SFE_VENDOR_DE_COMPANYID_1 &&
	       r->opeअक्रम[2] == SFE_VENDOR_DE_COMPANYID_2 &&
	       r->opeअक्रम[3] == SFE_VENDOR_OPCODE_REGISTER_REMOTE_CONTROL;
पूर्ण

पूर्णांक avc_recv(काष्ठा firedtv *fdtv, व्योम *data, माप_प्रकार length)
अणु
	काष्ठा avc_response_frame *r = data;

	अगर (unlikely(avc_debug))
		debug_fcp(data, length);

	अगर (length >= 8 && is_रेजिस्टर_rc(r)) अणु
		चयन (r->response) अणु
		हाल AVC_RESPONSE_CHANGED:
			fdtv_handle_rc(fdtv, r->opeअक्रम[4] << 8 | r->opeअक्रम[5]);
			schedule_work(&fdtv->remote_ctrl_work);
			अवरोध;
		हाल AVC_RESPONSE_INTERIM:
			अगर (is_रेजिस्टर_rc((व्योम *)fdtv->avc_data))
				जाओ wake;
			अवरोध;
		शेष:
			dev_info(fdtv->device,
				 "remote control result = %d\n", r->response);
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (fdtv->avc_reply_received) अणु
		dev_err(fdtv->device, "out-of-order AVC response, ignored\n");
		वापस -EIO;
	पूर्ण

	स_नकल(fdtv->avc_data, data, length);
	fdtv->avc_data_length = length;
wake:
	fdtv->avc_reply_received = true;
	wake_up(&fdtv->avc_रुको);

	वापस 0;
पूर्ण

अटल पूर्णांक add_pid_filter(काष्ठा firedtv *fdtv, u8 *opeअक्रम)
अणु
	पूर्णांक i, n, pos = 1;

	क्रम (i = 0, n = 0; i < 16; i++) अणु
		अगर (test_bit(i, &fdtv->channel_active)) अणु
			opeअक्रम[pos++] = 0x13; /* flowfunction relay */
			opeअक्रम[pos++] = 0x80; /* dsd_sel_spec_valid_flags -> PID */
			opeअक्रम[pos++] = (fdtv->channel_pid[i] >> 8) & 0x1f;
			opeअक्रम[pos++] = fdtv->channel_pid[i] & 0xff;
			opeअक्रम[pos++] = 0x00; /* tableID */
			opeअक्रम[pos++] = 0x00; /* filter_length */
			n++;
		पूर्ण
	पूर्ण
	opeअक्रम[0] = n;

	वापस pos;
पूर्ण

/*
 * tuning command क्रम setting the relative LNB frequency
 * (not supported by the AVC standard)
 */
अटल पूर्णांक avc_tuner_tuneqpsk(काष्ठा firedtv *fdtv,
			      काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;

	c->opcode = AVC_OPCODE_VENDOR;

	c->opeअक्रम[0] = SFE_VENDOR_DE_COMPANYID_0;
	c->opeअक्रम[1] = SFE_VENDOR_DE_COMPANYID_1;
	c->opeअक्रम[2] = SFE_VENDOR_DE_COMPANYID_2;
	अगर (fdtv->type == FIREDTV_DVB_S2)
		c->opeअक्रम[3] = SFE_VENDOR_OPCODE_TUNE_QPSK2;
	अन्यथा
		c->opeअक्रम[3] = SFE_VENDOR_OPCODE_TUNE_QPSK;

	c->opeअक्रम[4] = (p->frequency >> 24) & 0xff;
	c->opeअक्रम[5] = (p->frequency >> 16) & 0xff;
	c->opeअक्रम[6] = (p->frequency >> 8) & 0xff;
	c->opeअक्रम[7] = p->frequency & 0xff;

	c->opeअक्रम[8] = ((p->symbol_rate / 1000) >> 8) & 0xff;
	c->opeअक्रम[9] = (p->symbol_rate / 1000) & 0xff;

	चयन (p->fec_inner) अणु
	हाल FEC_1_2:	c->opeअक्रम[10] = 0x1; अवरोध;
	हाल FEC_2_3:	c->opeअक्रम[10] = 0x2; अवरोध;
	हाल FEC_3_4:	c->opeअक्रम[10] = 0x3; अवरोध;
	हाल FEC_5_6:	c->opeअक्रम[10] = 0x4; अवरोध;
	हाल FEC_7_8:	c->opeअक्रम[10] = 0x5; अवरोध;
	हाल FEC_4_5:
	हाल FEC_8_9:
	हाल FEC_AUTO:
	शेष:	c->opeअक्रम[10] = 0x0;
	पूर्ण

	अगर (fdtv->voltage == 0xff)
		c->opeअक्रम[11] = 0xff;
	अन्यथा अगर (fdtv->voltage == SEC_VOLTAGE_18) /* polarisation */
		c->opeअक्रम[11] = 0;
	अन्यथा
		c->opeअक्रम[11] = 1;

	अगर (fdtv->tone == 0xff)
		c->opeअक्रम[12] = 0xff;
	अन्यथा अगर (fdtv->tone == SEC_TONE_ON) /* band */
		c->opeअक्रम[12] = 1;
	अन्यथा
		c->opeअक्रम[12] = 0;

	अगर (fdtv->type == FIREDTV_DVB_S2) अणु
		अगर (fdtv->fe.dtv_property_cache.delivery_प्रणाली == SYS_DVBS2) अणु
			चयन (fdtv->fe.dtv_property_cache.modulation) अणु
			हाल QAM_16:		c->opeअक्रम[13] = 0x1; अवरोध;
			हाल QPSK:		c->opeअक्रम[13] = 0x2; अवरोध;
			हाल PSK_8:		c->opeअक्रम[13] = 0x3; अवरोध;
			शेष:		c->opeअक्रम[13] = 0x2; अवरोध;
			पूर्ण
			चयन (fdtv->fe.dtv_property_cache.rolloff) अणु
			हाल ROLLOFF_35:	c->opeअक्रम[14] = 0x2; अवरोध;
			हाल ROLLOFF_20:	c->opeअक्रम[14] = 0x0; अवरोध;
			हाल ROLLOFF_25:	c->opeअक्रम[14] = 0x1; अवरोध;
			हाल ROLLOFF_AUTO:
			शेष:		c->opeअक्रम[14] = 0x2; अवरोध;
			/* हाल ROLLOFF_NONE:	c->opeअक्रम[14] = 0xff; अवरोध; */
			पूर्ण
			चयन (fdtv->fe.dtv_property_cache.pilot) अणु
			हाल PILOT_AUTO:	c->opeअक्रम[15] = 0x0; अवरोध;
			हाल PILOT_OFF:		c->opeअक्रम[15] = 0x0; अवरोध;
			हाल PILOT_ON:		c->opeअक्रम[15] = 0x1; अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			c->opeअक्रम[13] = 0x1;  /* स्वतः modulation */
			c->opeअक्रम[14] = 0xff; /* disable rolloff */
			c->opeअक्रम[15] = 0xff; /* disable pilot */
		पूर्ण
		वापस 16;
	पूर्ण अन्यथा अणु
		वापस 13;
	पूर्ण
पूर्ण

अटल पूर्णांक avc_tuner_dsd_dvb_c(काष्ठा firedtv *fdtv,
			       काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;

	c->opcode = AVC_OPCODE_DSD;

	c->opeअक्रम[0] = 0;    /* source plug */
	c->opeअक्रम[1] = 0xd2; /* subfunction replace */
	c->opeअक्रम[2] = 0x20; /* प्रणाली id = DVB */
	c->opeअक्रम[3] = 0x00; /* antenna number */
	c->opeअक्रम[4] = 0x11; /* प्रणाली_specअगरic_multiplex selection_length */

	/* multiplex_valid_flags, high byte */
	c->opeअक्रम[5] =   0 << 7 /* reserved */
			| 0 << 6 /* Polarisation */
			| 0 << 5 /* Orbital_Pos */
			| 1 << 4 /* Frequency */
			| 1 << 3 /* Symbol_Rate */
			| 0 << 2 /* FEC_outer */
			| (p->fec_inner  != FEC_AUTO ? 1 << 1 : 0)
			| (p->modulation != QAM_AUTO ? 1 << 0 : 0);

	/* multiplex_valid_flags, low byte */
	c->opeअक्रम[6] =   0 << 7 /* NetworkID */
			| 0 << 0 /* reserved */ ;

	c->opeअक्रम[7]  = 0x00;
	c->opeअक्रम[8]  = 0x00;
	c->opeअक्रम[9]  = 0x00;
	c->opeअक्रम[10] = 0x00;

	c->opeअक्रम[11] = (((p->frequency / 4000) >> 16) & 0xff) | (2 << 6);
	c->opeअक्रम[12] = ((p->frequency / 4000) >> 8) & 0xff;
	c->opeअक्रम[13] = (p->frequency / 4000) & 0xff;
	c->opeअक्रम[14] = ((p->symbol_rate / 1000) >> 12) & 0xff;
	c->opeअक्रम[15] = ((p->symbol_rate / 1000) >> 4) & 0xff;
	c->opeअक्रम[16] = ((p->symbol_rate / 1000) << 4) & 0xf0;
	c->opeअक्रम[17] = 0x00;

	चयन (p->fec_inner) अणु
	हाल FEC_1_2:	c->opeअक्रम[18] = 0x1; अवरोध;
	हाल FEC_2_3:	c->opeअक्रम[18] = 0x2; अवरोध;
	हाल FEC_3_4:	c->opeअक्रम[18] = 0x3; अवरोध;
	हाल FEC_5_6:	c->opeअक्रम[18] = 0x4; अवरोध;
	हाल FEC_7_8:	c->opeअक्रम[18] = 0x5; अवरोध;
	हाल FEC_8_9:	c->opeअक्रम[18] = 0x6; अवरोध;
	हाल FEC_4_5:	c->opeअक्रम[18] = 0x8; अवरोध;
	हाल FEC_AUTO:
	शेष:	c->opeअक्रम[18] = 0x0;
	पूर्ण

	चयन (p->modulation) अणु
	हाल QAM_16:	c->opeअक्रम[19] = 0x08; अवरोध;
	हाल QAM_32:	c->opeअक्रम[19] = 0x10; अवरोध;
	हाल QAM_64:	c->opeअक्रम[19] = 0x18; अवरोध;
	हाल QAM_128:	c->opeअक्रम[19] = 0x20; अवरोध;
	हाल QAM_256:	c->opeअक्रम[19] = 0x28; अवरोध;
	हाल QAM_AUTO:
	शेष:	c->opeअक्रम[19] = 0x00;
	पूर्ण

	c->opeअक्रम[20] = 0x00;
	c->opeअक्रम[21] = 0x00;

	वापस 22 + add_pid_filter(fdtv, &c->opeअक्रम[22]);
पूर्ण

अटल पूर्णांक avc_tuner_dsd_dvb_t(काष्ठा firedtv *fdtv,
			       काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;

	c->opcode = AVC_OPCODE_DSD;

	c->opeअक्रम[0] = 0;    /* source plug */
	c->opeअक्रम[1] = 0xd2; /* subfunction replace */
	c->opeअक्रम[2] = 0x20; /* प्रणाली id = DVB */
	c->opeअक्रम[3] = 0x00; /* antenna number */
	c->opeअक्रम[4] = 0x0c; /* प्रणाली_specअगरic_multiplex selection_length */

	/* multiplex_valid_flags, high byte */
	c->opeअक्रम[5] =
	      0 << 7 /* reserved */
	    | 1 << 6 /* CenterFrequency */
	    | (p->bandwidth_hz != 0        ? 1 << 5 : 0)
	    | (p->modulation  != QAM_AUTO              ? 1 << 4 : 0)
	    | (p->hierarchy != HIERARCHY_AUTO ? 1 << 3 : 0)
	    | (p->code_rate_HP   != FEC_AUTO              ? 1 << 2 : 0)
	    | (p->code_rate_LP   != FEC_AUTO              ? 1 << 1 : 0)
	    | (p->guard_पूर्णांकerval != GUARD_INTERVAL_AUTO   ? 1 << 0 : 0);

	/* multiplex_valid_flags, low byte */
	c->opeअक्रम[6] =
	      0 << 7 /* NetworkID */
	    | (p->transmission_mode != TRANSMISSION_MODE_AUTO ? 1 << 6 : 0)
	    | 0 << 5 /* OtherFrequencyFlag */
	    | 0 << 0 /* reserved */ ;

	c->opeअक्रम[7]  = 0x0;
	c->opeअक्रम[8]  = (p->frequency / 10) >> 24;
	c->opeअक्रम[9]  = ((p->frequency / 10) >> 16) & 0xff;
	c->opeअक्रम[10] = ((p->frequency / 10) >>  8) & 0xff;
	c->opeअक्रम[11] = (p->frequency / 10) & 0xff;

	चयन (p->bandwidth_hz) अणु
	हाल 7000000:	c->opeअक्रम[12] = 0x20; अवरोध;
	हाल 8000000:
	हाल 6000000:	/* not defined by AVC spec */
	हाल 0:
	शेष:		c->opeअक्रम[12] = 0x00;
	पूर्ण

	चयन (p->modulation) अणु
	हाल QAM_16:	c->opeअक्रम[13] = 1 << 6; अवरोध;
	हाल QAM_64:	c->opeअक्रम[13] = 2 << 6; अवरोध;
	हाल QPSK:
	शेष:	c->opeअक्रम[13] = 0x00;
	पूर्ण

	चयन (p->hierarchy) अणु
	हाल HIERARCHY_1:	c->opeअक्रम[13] |= 1 << 3; अवरोध;
	हाल HIERARCHY_2:	c->opeअक्रम[13] |= 2 << 3; अवरोध;
	हाल HIERARCHY_4:	c->opeअक्रम[13] |= 3 << 3; अवरोध;
	हाल HIERARCHY_AUTO:
	हाल HIERARCHY_NONE:
	शेष:		अवरोध;
	पूर्ण

	चयन (p->code_rate_HP) अणु
	हाल FEC_2_3:	c->opeअक्रम[13] |= 1; अवरोध;
	हाल FEC_3_4:	c->opeअक्रम[13] |= 2; अवरोध;
	हाल FEC_5_6:	c->opeअक्रम[13] |= 3; अवरोध;
	हाल FEC_7_8:	c->opeअक्रम[13] |= 4; अवरोध;
	हाल FEC_1_2:
	शेष:	अवरोध;
	पूर्ण

	चयन (p->code_rate_LP) अणु
	हाल FEC_2_3:	c->opeअक्रम[14] = 1 << 5; अवरोध;
	हाल FEC_3_4:	c->opeअक्रम[14] = 2 << 5; अवरोध;
	हाल FEC_5_6:	c->opeअक्रम[14] = 3 << 5; अवरोध;
	हाल FEC_7_8:	c->opeअक्रम[14] = 4 << 5; अवरोध;
	हाल FEC_1_2:
	शेष:	c->opeअक्रम[14] = 0x00; अवरोध;
	पूर्ण

	चयन (p->guard_पूर्णांकerval) अणु
	हाल GUARD_INTERVAL_1_16:	c->opeअक्रम[14] |= 1 << 3; अवरोध;
	हाल GUARD_INTERVAL_1_8:	c->opeअक्रम[14] |= 2 << 3; अवरोध;
	हाल GUARD_INTERVAL_1_4:	c->opeअक्रम[14] |= 3 << 3; अवरोध;
	हाल GUARD_INTERVAL_1_32:
	हाल GUARD_INTERVAL_AUTO:
	शेष:			अवरोध;
	पूर्ण

	चयन (p->transmission_mode) अणु
	हाल TRANSMISSION_MODE_8K:	c->opeअक्रम[14] |= 1 << 1; अवरोध;
	हाल TRANSMISSION_MODE_2K:
	हाल TRANSMISSION_MODE_AUTO:
	शेष:			अवरोध;
	पूर्ण

	c->opeअक्रम[15] = 0x00; /* network_ID[0] */
	c->opeअक्रम[16] = 0x00; /* network_ID[1] */

	वापस 17 + add_pid_filter(fdtv, &c->opeअक्रम[17]);
पूर्ण

पूर्णांक avc_tuner_dsd(काष्ठा firedtv *fdtv,
		  काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;
	पूर्णांक pos, ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTROL;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;

	चयन (fdtv->type) अणु
	हाल FIREDTV_DVB_S:
	हाल FIREDTV_DVB_S2: pos = avc_tuner_tuneqpsk(fdtv, p); अवरोध;
	हाल FIREDTV_DVB_C: pos = avc_tuner_dsd_dvb_c(fdtv, p); अवरोध;
	हाल FIREDTV_DVB_T: pos = avc_tuner_dsd_dvb_t(fdtv, p); अवरोध;
	शेष:
		BUG();
	पूर्ण
	pad_opeअक्रमs(c, pos);

	fdtv->avc_data_length = ALIGN(3 + pos, 4);
	ret = avc_ग_लिखो(fdtv);
#अगर 0
	/*
	 * FIXME:
	 * u8 *status was an out-parameter of avc_tuner_dsd, unused by caller.
	 * Check क्रम AVC_RESPONSE_ACCEPTED here instead?
	 */
	अगर (status)
		*status = r->opeअक्रम[2];
#पूर्ण_अगर
	mutex_unlock(&fdtv->avc_mutex);

	अगर (ret == 0)
		msleep(500);

	वापस ret;
पूर्ण

पूर्णांक avc_tuner_set_pids(काष्ठा firedtv *fdtv, अचिन्हित अक्षर pidc, u16 pid[])
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;
	पूर्णांक ret, pos, k;

	अगर (pidc > 16 && pidc != 0xff)
		वापस -EINVAL;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTROL;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_DSD;

	c->opeअक्रम[0] = 0;	/* source plug */
	c->opeअक्रम[1] = 0xd2;	/* subfunction replace */
	c->opeअक्रम[2] = 0x20;	/* प्रणाली id = DVB */
	c->opeअक्रम[3] = 0x00;	/* antenna number */
	c->opeअक्रम[4] = 0x00;	/* प्रणाली_specअगरic_multiplex selection_length */
	c->opeअक्रम[5] = pidc;	/* Nr_of_dsd_sel_specs */

	pos = 6;
	अगर (pidc != 0xff)
		क्रम (k = 0; k < pidc; k++) अणु
			c->opeअक्रम[pos++] = 0x13; /* flowfunction relay */
			c->opeअक्रम[pos++] = 0x80; /* dsd_sel_spec_valid_flags -> PID */
			c->opeअक्रम[pos++] = (pid[k] >> 8) & 0x1f;
			c->opeअक्रम[pos++] = pid[k] & 0xff;
			c->opeअक्रम[pos++] = 0x00; /* tableID */
			c->opeअक्रम[pos++] = 0x00; /* filter_length */
		पूर्ण
	pad_opeअक्रमs(c, pos);

	fdtv->avc_data_length = ALIGN(3 + pos, 4);
	ret = avc_ग_लिखो(fdtv);

	/* FIXME: check response code? */

	mutex_unlock(&fdtv->avc_mutex);

	अगर (ret == 0)
		msleep(50);

	वापस ret;
पूर्ण

पूर्णांक avc_tuner_get_ts(काष्ठा firedtv *fdtv)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;
	पूर्णांक ret, sl;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTROL;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_DSIT;

	sl = fdtv->type == FIREDTV_DVB_T ? 0x0c : 0x11;

	c->opeअक्रम[0] = 0;	/* source plug */
	c->opeअक्रम[1] = 0xd2;	/* subfunction replace */
	c->opeअक्रम[2] = 0xff;	/* status */
	c->opeअक्रम[3] = 0x20;	/* प्रणाली id = DVB */
	c->opeअक्रम[4] = 0x00;	/* antenna number */
	c->opeअक्रम[5] = 0x0;	/* प्रणाली_specअगरic_search_flags */
	c->opeअक्रम[6] = sl;	/* प्रणाली_specअगरic_multiplex selection_length */
	/*
	 * opeअक्रम[7]: valid_flags[0]
	 * opeअक्रम[8]: valid_flags[1]
	 * opeअक्रम[7 + sl]: nr_of_dsit_sel_specs (always 0)
	 */
	clear_opeअक्रमs(c, 7, 24);

	fdtv->avc_data_length = fdtv->type == FIREDTV_DVB_T ? 24 : 28;
	ret = avc_ग_लिखो(fdtv);

	/* FIXME: check response code? */

	mutex_unlock(&fdtv->avc_mutex);

	अगर (ret == 0)
		msleep(250);

	वापस ret;
पूर्ण

पूर्णांक avc_identअगरy_subunit(काष्ठा firedtv *fdtv)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;
	काष्ठा avc_response_frame *r = (व्योम *)fdtv->avc_data;
	पूर्णांक ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTROL;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_READ_DESCRIPTOR;

	c->opeअक्रम[0] = DESCRIPTOR_SUBUNIT_IDENTIFIER;
	c->opeअक्रम[1] = 0xff;
	c->opeअक्रम[2] = 0x00;
	c->opeअक्रम[3] = 0x00; /* length highbyte */
	c->opeअक्रम[4] = 0x08; /* length lowbyte  */
	c->opeअक्रम[5] = 0x00; /* offset highbyte */
	c->opeअक्रम[6] = 0x0d; /* offset lowbyte  */
	clear_opeअक्रमs(c, 7, 8); /* padding */

	fdtv->avc_data_length = 12;
	ret = avc_ग_लिखो(fdtv);
	अगर (ret < 0)
		जाओ out;

	अगर ((r->response != AVC_RESPONSE_STABLE &&
	     r->response != AVC_RESPONSE_ACCEPTED) ||
	    (r->opeअक्रम[3] << 8) + r->opeअक्रम[4] != 8) अणु
		dev_err(fdtv->device, "cannot read subunit identifier\n");
		ret = -EINVAL;
	पूर्ण
out:
	mutex_unlock(&fdtv->avc_mutex);

	वापस ret;
पूर्ण

#घोषणा SIZखातापूर्ण_ANTENNA_INPUT_INFO 22

पूर्णांक avc_tuner_status(काष्ठा firedtv *fdtv, काष्ठा firedtv_tuner_status *stat)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;
	काष्ठा avc_response_frame *r = (व्योम *)fdtv->avc_data;
	पूर्णांक length, ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTROL;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_READ_DESCRIPTOR;

	c->opeअक्रम[0] = DESCRIPTOR_TUNER_STATUS;
	c->opeअक्रम[1] = 0xff;	/* पढ़ो_result_status */
	/*
	 * opeअक्रम[2]: reserved
	 * opeअक्रम[3]: SIZखातापूर्ण_ANTENNA_INPUT_INFO >> 8
	 * opeअक्रम[4]: SIZखातापूर्ण_ANTENNA_INPUT_INFO & 0xff
	 */
	clear_opeअक्रमs(c, 2, 31);

	fdtv->avc_data_length = 12;
	ret = avc_ग_लिखो(fdtv);
	अगर (ret < 0)
		जाओ out;

	अगर (r->response != AVC_RESPONSE_STABLE &&
	    r->response != AVC_RESPONSE_ACCEPTED) अणु
		dev_err(fdtv->device, "cannot read tuner status\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	length = r->opeअक्रम[9];
	अगर (r->opeअक्रम[1] != 0x10 || length != SIZखातापूर्ण_ANTENNA_INPUT_INFO) अणु
		dev_err(fdtv->device, "got invalid tuner status\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	stat->active_प्रणाली		= r->opeअक्रम[10];
	stat->searching			= r->opeअक्रम[11] >> 7 & 1;
	stat->moving			= r->opeअक्रम[11] >> 6 & 1;
	stat->no_rf			= r->opeअक्रम[11] >> 5 & 1;
	stat->input			= r->opeअक्रम[12] >> 7 & 1;
	stat->selected_antenna		= r->opeअक्रम[12] & 0x7f;
	stat->ber			= r->opeअक्रम[13] << 24 |
					  r->opeअक्रम[14] << 16 |
					  r->opeअक्रम[15] << 8 |
					  r->opeअक्रम[16];
	stat->संकेत_strength		= r->opeअक्रम[17];
	stat->raster_frequency		= r->opeअक्रम[18] >> 6 & 2;
	stat->rf_frequency		= (r->opeअक्रम[18] & 0x3f) << 16 |
					  r->opeअक्रम[19] << 8 |
					  r->opeअक्रम[20];
	stat->man_dep_info_length	= r->opeअक्रम[21];
	stat->front_end_error		= r->opeअक्रम[22] >> 4 & 1;
	stat->antenna_error		= r->opeअक्रम[22] >> 3 & 1;
	stat->front_end_घातer_status	= r->opeअक्रम[22] >> 1 & 1;
	stat->घातer_supply		= r->opeअक्रम[22] & 1;
	stat->carrier_noise_ratio	= r->opeअक्रम[23] << 8 |
					  r->opeअक्रम[24];
	stat->घातer_supply_voltage	= r->opeअक्रम[27];
	stat->antenna_voltage		= r->opeअक्रम[28];
	stat->firewire_bus_voltage	= r->opeअक्रम[29];
	stat->ca_mmi			= r->opeअक्रम[30] & 1;
	stat->ca_pmt_reply		= r->opeअक्रम[31] >> 7 & 1;
	stat->ca_date_समय_request	= r->opeअक्रम[31] >> 6 & 1;
	stat->ca_application_info	= r->opeअक्रम[31] >> 5 & 1;
	stat->ca_module_present_status	= r->opeअक्रम[31] >> 4 & 1;
	stat->ca_dvb_flag		= r->opeअक्रम[31] >> 3 & 1;
	stat->ca_error_flag		= r->opeअक्रम[31] >> 2 & 1;
	stat->ca_initialization_status	= r->opeअक्रम[31] >> 1 & 1;
out:
	mutex_unlock(&fdtv->avc_mutex);

	वापस ret;
पूर्ण

पूर्णांक avc_lnb_control(काष्ठा firedtv *fdtv, अक्षर voltage, अक्षर burst,
		    अक्षर conttone, अक्षर nrdiseq,
		    काष्ठा dvb_diseqc_master_cmd *diseqcmd)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;
	काष्ठा avc_response_frame *r = (व्योम *)fdtv->avc_data;
	पूर्णांक pos, j, k, ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTROL;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOR;

	c->opeअक्रम[0] = SFE_VENDOR_DE_COMPANYID_0;
	c->opeअक्रम[1] = SFE_VENDOR_DE_COMPANYID_1;
	c->opeअक्रम[2] = SFE_VENDOR_DE_COMPANYID_2;
	c->opeअक्रम[3] = SFE_VENDOR_OPCODE_LNB_CONTROL;
	c->opeअक्रम[4] = voltage;
	c->opeअक्रम[5] = nrdiseq;

	pos = 6;
	क्रम (j = 0; j < nrdiseq; j++) अणु
		c->opeअक्रम[pos++] = diseqcmd[j].msg_len;

		क्रम (k = 0; k < diseqcmd[j].msg_len; k++)
			c->opeअक्रम[pos++] = diseqcmd[j].msg[k];
	पूर्ण
	c->opeअक्रम[pos++] = burst;
	c->opeअक्रम[pos++] = conttone;
	pad_opeअक्रमs(c, pos);

	fdtv->avc_data_length = ALIGN(3 + pos, 4);
	ret = avc_ग_लिखो(fdtv);
	अगर (ret < 0)
		जाओ out;

	अगर (r->response != AVC_RESPONSE_ACCEPTED) अणु
		dev_err(fdtv->device, "LNB control failed\n");
		ret = -EINVAL;
	पूर्ण
out:
	mutex_unlock(&fdtv->avc_mutex);

	वापस ret;
पूर्ण

पूर्णांक avc_रेजिस्टर_remote_control(काष्ठा firedtv *fdtv)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;
	पूर्णांक ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_NOTIFY;
	c->subunit = AVC_SUBUNIT_TYPE_UNIT | 7;
	c->opcode  = AVC_OPCODE_VENDOR;

	c->opeअक्रम[0] = SFE_VENDOR_DE_COMPANYID_0;
	c->opeअक्रम[1] = SFE_VENDOR_DE_COMPANYID_1;
	c->opeअक्रम[2] = SFE_VENDOR_DE_COMPANYID_2;
	c->opeअक्रम[3] = SFE_VENDOR_OPCODE_REGISTER_REMOTE_CONTROL;
	c->opeअक्रम[4] = 0; /* padding */

	fdtv->avc_data_length = 8;
	ret = avc_ग_लिखो(fdtv);

	/* FIXME: check response code? */

	mutex_unlock(&fdtv->avc_mutex);

	वापस ret;
पूर्ण

व्योम avc_remote_ctrl_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा firedtv *fdtv =
			container_of(work, काष्ठा firedtv, remote_ctrl_work);

	/* Should it be rescheduled in failure हालs? */
	avc_रेजिस्टर_remote_control(fdtv);
पूर्ण

#अगर 0 /* FIXME: unused */
पूर्णांक avc_tuner_host2ca(काष्ठा firedtv *fdtv)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;
	पूर्णांक ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTROL;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOR;

	c->opeअक्रम[0] = SFE_VENDOR_DE_COMPANYID_0;
	c->opeअक्रम[1] = SFE_VENDOR_DE_COMPANYID_1;
	c->opeअक्रम[2] = SFE_VENDOR_DE_COMPANYID_2;
	c->opeअक्रम[3] = SFE_VENDOR_OPCODE_HOST2CA;
	c->opeअक्रम[4] = 0; /* slot */
	c->opeअक्रम[5] = SFE_VENDOR_TAG_CA_APPLICATION_INFO; /* ca tag */
	clear_opeअक्रमs(c, 6, 8);

	fdtv->avc_data_length = 12;
	ret = avc_ग_लिखो(fdtv);

	/* FIXME: check response code? */

	mutex_unlock(&fdtv->avc_mutex);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक get_ca_object_pos(काष्ठा avc_response_frame *r)
अणु
	पूर्णांक length = 1;

	/* Check length of length field */
	अगर (r->opeअक्रम[7] & 0x80)
		length = (r->opeअक्रम[7] & 0x7f) + 1;
	वापस length + 7;
पूर्ण

अटल पूर्णांक get_ca_object_length(काष्ठा avc_response_frame *r)
अणु
#अगर 0 /* FIXME: unused */
	पूर्णांक size = 0;
	पूर्णांक i;

	अगर (r->opeअक्रम[7] & 0x80)
		क्रम (i = 0; i < (r->opeअक्रम[7] & 0x7f); i++) अणु
			size <<= 8;
			size += r->opeअक्रम[8 + i];
		पूर्ण
#पूर्ण_अगर
	वापस r->opeअक्रम[7];
पूर्ण

पूर्णांक avc_ca_app_info(काष्ठा firedtv *fdtv, अचिन्हित अक्षर *app_info,
		    अचिन्हित पूर्णांक *len)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;
	काष्ठा avc_response_frame *r = (व्योम *)fdtv->avc_data;
	पूर्णांक pos, ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_STATUS;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOR;

	c->opeअक्रम[0] = SFE_VENDOR_DE_COMPANYID_0;
	c->opeअक्रम[1] = SFE_VENDOR_DE_COMPANYID_1;
	c->opeअक्रम[2] = SFE_VENDOR_DE_COMPANYID_2;
	c->opeअक्रम[3] = SFE_VENDOR_OPCODE_CA2HOST;
	c->opeअक्रम[4] = 0; /* slot */
	c->opeअक्रम[5] = SFE_VENDOR_TAG_CA_APPLICATION_INFO; /* ca tag */
	clear_opeअक्रमs(c, 6, LAST_OPERAND);

	fdtv->avc_data_length = 12;
	ret = avc_ग_लिखो(fdtv);
	अगर (ret < 0)
		जाओ out;

	/* FIXME: check response code and validate response data */

	pos = get_ca_object_pos(r);
	app_info[0] = (EN50221_TAG_APP_INFO >> 16) & 0xff;
	app_info[1] = (EN50221_TAG_APP_INFO >>  8) & 0xff;
	app_info[2] = (EN50221_TAG_APP_INFO >>  0) & 0xff;
	app_info[3] = 6 + r->opeअक्रम[pos + 4];
	app_info[4] = 0x01;
	स_नकल(&app_info[5], &r->opeअक्रम[pos], 5 + r->opeअक्रम[pos + 4]);
	*len = app_info[3] + 4;
out:
	mutex_unlock(&fdtv->avc_mutex);

	वापस ret;
पूर्ण

पूर्णांक avc_ca_info(काष्ठा firedtv *fdtv, अचिन्हित अक्षर *app_info,
		अचिन्हित पूर्णांक *len)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;
	काष्ठा avc_response_frame *r = (व्योम *)fdtv->avc_data;
	पूर्णांक i, pos, ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_STATUS;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOR;

	c->opeअक्रम[0] = SFE_VENDOR_DE_COMPANYID_0;
	c->opeअक्रम[1] = SFE_VENDOR_DE_COMPANYID_1;
	c->opeअक्रम[2] = SFE_VENDOR_DE_COMPANYID_2;
	c->opeअक्रम[3] = SFE_VENDOR_OPCODE_CA2HOST;
	c->opeअक्रम[4] = 0; /* slot */
	c->opeअक्रम[5] = SFE_VENDOR_TAG_CA_APPLICATION_INFO; /* ca tag */
	clear_opeअक्रमs(c, 6, LAST_OPERAND);

	fdtv->avc_data_length = 12;
	ret = avc_ग_लिखो(fdtv);
	अगर (ret < 0)
		जाओ out;

	/* FIXME: check response code and validate response data */

	pos = get_ca_object_pos(r);
	app_info[0] = (EN50221_TAG_CA_INFO >> 16) & 0xff;
	app_info[1] = (EN50221_TAG_CA_INFO >>  8) & 0xff;
	app_info[2] = (EN50221_TAG_CA_INFO >>  0) & 0xff;
	अगर (num_fake_ca_प्रणाली_ids == 0) अणु
		app_info[3] = 2;
		app_info[4] = r->opeअक्रम[pos + 0];
		app_info[5] = r->opeअक्रम[pos + 1];
	पूर्ण अन्यथा अणु
		app_info[3] = num_fake_ca_प्रणाली_ids * 2;
		क्रम (i = 0; i < num_fake_ca_प्रणाली_ids; i++) अणु
			app_info[4 + i * 2] =
				(fake_ca_प्रणाली_ids[i] >> 8) & 0xff;
			app_info[5 + i * 2] = fake_ca_प्रणाली_ids[i] & 0xff;
		पूर्ण
	पूर्ण
	*len = app_info[3] + 4;
out:
	mutex_unlock(&fdtv->avc_mutex);

	वापस ret;
पूर्ण

पूर्णांक avc_ca_reset(काष्ठा firedtv *fdtv)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;
	पूर्णांक ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTROL;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOR;

	c->opeअक्रम[0] = SFE_VENDOR_DE_COMPANYID_0;
	c->opeअक्रम[1] = SFE_VENDOR_DE_COMPANYID_1;
	c->opeअक्रम[2] = SFE_VENDOR_DE_COMPANYID_2;
	c->opeअक्रम[3] = SFE_VENDOR_OPCODE_HOST2CA;
	c->opeअक्रम[4] = 0; /* slot */
	c->opeअक्रम[5] = SFE_VENDOR_TAG_CA_RESET; /* ca tag */
	c->opeअक्रम[6] = 0; /* more/last */
	c->opeअक्रम[7] = 1; /* length */
	c->opeअक्रम[8] = 0; /* क्रमce hardware reset */

	fdtv->avc_data_length = 12;
	ret = avc_ग_लिखो(fdtv);

	/* FIXME: check response code? */

	mutex_unlock(&fdtv->avc_mutex);

	वापस ret;
पूर्ण

पूर्णांक avc_ca_pmt(काष्ठा firedtv *fdtv, अक्षर *msg, पूर्णांक length)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;
	काष्ठा avc_response_frame *r = (व्योम *)fdtv->avc_data;
	पूर्णांक list_management;
	पूर्णांक program_info_length;
	पूर्णांक pmt_cmd_id;
	पूर्णांक पढ़ो_pos;
	पूर्णांक ग_लिखो_pos;
	पूर्णांक es_info_length;
	पूर्णांक crc32_csum;
	पूर्णांक ret;

	अगर (unlikely(avc_debug & AVC_DEBUG_APPLICATION_PMT))
		debug_pmt(msg, length);

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTROL;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOR;

	अगर (msg[0] != EN50221_LIST_MANAGEMENT_ONLY) अणु
		dev_info(fdtv->device, "forcing list_management to ONLY\n");
		msg[0] = EN50221_LIST_MANAGEMENT_ONLY;
	पूर्ण
	/* We take the cmd_id from the programme level only! */
	list_management = msg[0];
	program_info_length = ((msg[4] & 0x0f) << 8) + msg[5];
	अगर (program_info_length > 0)
		program_info_length--; /* Remove pmt_cmd_id */
	pmt_cmd_id = msg[6];

	c->opeअक्रम[0] = SFE_VENDOR_DE_COMPANYID_0;
	c->opeअक्रम[1] = SFE_VENDOR_DE_COMPANYID_1;
	c->opeअक्रम[2] = SFE_VENDOR_DE_COMPANYID_2;
	c->opeअक्रम[3] = SFE_VENDOR_OPCODE_HOST2CA;
	c->opeअक्रम[4] = 0; /* slot */
	c->opeअक्रम[5] = SFE_VENDOR_TAG_CA_PMT; /* ca tag */
	c->opeअक्रम[6] = 0; /* more/last */
	/* Use three bytes क्रम length field in हाल length > 127 */
	c->opeअक्रम[10] = list_management;
	c->opeअक्रम[11] = 0x01; /* pmt_cmd=OK_descramble */

	/* TS program map table */

	c->opeअक्रम[12] = 0x02; /* Table id=2 */
	c->opeअक्रम[13] = 0x80; /* Section syntax + length */

	c->opeअक्रम[15] = msg[1]; /* Program number */
	c->opeअक्रम[16] = msg[2];
	c->opeअक्रम[17] = msg[3]; /* Version number and current/next */
	c->opeअक्रम[18] = 0x00; /* Section number=0 */
	c->opeअक्रम[19] = 0x00; /* Last section number=0 */
	c->opeअक्रम[20] = 0x1f; /* PCR_PID=1FFF */
	c->opeअक्रम[21] = 0xff;
	c->opeअक्रम[22] = (program_info_length >> 8); /* Program info length */
	c->opeअक्रम[23] = (program_info_length & 0xff);

	/* CA descriptors at programme level */
	पढ़ो_pos = 6;
	ग_लिखो_pos = 24;
	अगर (program_info_length > 0) अणु
		pmt_cmd_id = msg[पढ़ो_pos++];
		अगर (pmt_cmd_id != 1 && pmt_cmd_id != 4)
			dev_err(fdtv->device,
				"invalid pmt_cmd_id %d\n", pmt_cmd_id);
		अगर (program_info_length > माप(c->opeअक्रम) - 4 - ग_लिखो_pos) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		स_नकल(&c->opeअक्रम[ग_लिखो_pos], &msg[पढ़ो_pos],
		       program_info_length);
		पढ़ो_pos += program_info_length;
		ग_लिखो_pos += program_info_length;
	पूर्ण
	जबतक (पढ़ो_pos < length) अणु
		c->opeअक्रम[ग_लिखो_pos++] = msg[पढ़ो_pos++];
		c->opeअक्रम[ग_लिखो_pos++] = msg[पढ़ो_pos++];
		c->opeअक्रम[ग_लिखो_pos++] = msg[पढ़ो_pos++];
		es_info_length =
			((msg[पढ़ो_pos] & 0x0f) << 8) + msg[पढ़ो_pos + 1];
		पढ़ो_pos += 2;
		अगर (es_info_length > 0)
			es_info_length--; /* Remove pmt_cmd_id */
		c->opeअक्रम[ग_लिखो_pos++] = es_info_length >> 8;
		c->opeअक्रम[ग_लिखो_pos++] = es_info_length & 0xff;
		अगर (es_info_length > 0) अणु
			pmt_cmd_id = msg[पढ़ो_pos++];
			अगर (pmt_cmd_id != 1 && pmt_cmd_id != 4)
				dev_err(fdtv->device, "invalid pmt_cmd_id %d at stream level\n",
					pmt_cmd_id);

			अगर (es_info_length > माप(c->opeअक्रम) - 4 -
					     ग_लिखो_pos) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			स_नकल(&c->opeअक्रम[ग_लिखो_pos], &msg[पढ़ो_pos],
			       es_info_length);
			पढ़ो_pos += es_info_length;
			ग_लिखो_pos += es_info_length;
		पूर्ण
	पूर्ण
	ग_लिखो_pos += 4; /* CRC */

	c->opeअक्रम[7] = 0x82;
	c->opeअक्रम[8] = (ग_लिखो_pos - 10) >> 8;
	c->opeअक्रम[9] = (ग_लिखो_pos - 10) & 0xff;
	c->opeअक्रम[14] = ग_लिखो_pos - 15;

	crc32_csum = crc32_be(0, &c->opeअक्रम[10], c->opeअक्रम[12] - 1);
	c->opeअक्रम[ग_लिखो_pos - 4] = (crc32_csum >> 24) & 0xff;
	c->opeअक्रम[ग_लिखो_pos - 3] = (crc32_csum >> 16) & 0xff;
	c->opeअक्रम[ग_लिखो_pos - 2] = (crc32_csum >>  8) & 0xff;
	c->opeअक्रम[ग_लिखो_pos - 1] = (crc32_csum >>  0) & 0xff;
	pad_opeअक्रमs(c, ग_लिखो_pos);

	fdtv->avc_data_length = ALIGN(3 + ग_लिखो_pos, 4);
	ret = avc_ग_लिखो(fdtv);
	अगर (ret < 0)
		जाओ out;

	अगर (r->response != AVC_RESPONSE_ACCEPTED) अणु
		dev_err(fdtv->device,
			"CA PMT failed with response 0x%x\n", r->response);
		ret = -EACCES;
	पूर्ण
out:
	mutex_unlock(&fdtv->avc_mutex);

	वापस ret;
पूर्ण

पूर्णांक avc_ca_get_समय_date(काष्ठा firedtv *fdtv, पूर्णांक *पूर्णांकerval)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;
	काष्ठा avc_response_frame *r = (व्योम *)fdtv->avc_data;
	पूर्णांक ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_STATUS;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOR;

	c->opeअक्रम[0] = SFE_VENDOR_DE_COMPANYID_0;
	c->opeअक्रम[1] = SFE_VENDOR_DE_COMPANYID_1;
	c->opeअक्रम[2] = SFE_VENDOR_DE_COMPANYID_2;
	c->opeअक्रम[3] = SFE_VENDOR_OPCODE_CA2HOST;
	c->opeअक्रम[4] = 0; /* slot */
	c->opeअक्रम[5] = SFE_VENDOR_TAG_CA_DATE_TIME; /* ca tag */
	clear_opeअक्रमs(c, 6, LAST_OPERAND);

	fdtv->avc_data_length = 12;
	ret = avc_ग_लिखो(fdtv);
	अगर (ret < 0)
		जाओ out;

	/* FIXME: check response code and validate response data */

	*पूर्णांकerval = r->opeअक्रम[get_ca_object_pos(r)];
out:
	mutex_unlock(&fdtv->avc_mutex);

	वापस ret;
पूर्ण

पूर्णांक avc_ca_enter_menu(काष्ठा firedtv *fdtv)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;
	पूर्णांक ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_STATUS;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOR;

	c->opeअक्रम[0] = SFE_VENDOR_DE_COMPANYID_0;
	c->opeअक्रम[1] = SFE_VENDOR_DE_COMPANYID_1;
	c->opeअक्रम[2] = SFE_VENDOR_DE_COMPANYID_2;
	c->opeअक्रम[3] = SFE_VENDOR_OPCODE_HOST2CA;
	c->opeअक्रम[4] = 0; /* slot */
	c->opeअक्रम[5] = SFE_VENDOR_TAG_CA_ENTER_MENU;
	clear_opeअक्रमs(c, 6, 8);

	fdtv->avc_data_length = 12;
	ret = avc_ग_लिखो(fdtv);

	/* FIXME: check response code? */

	mutex_unlock(&fdtv->avc_mutex);

	वापस ret;
पूर्ण

पूर्णांक avc_ca_get_mmi(काष्ठा firedtv *fdtv, अक्षर *mmi_object, अचिन्हित पूर्णांक *len)
अणु
	काष्ठा avc_command_frame *c = (व्योम *)fdtv->avc_data;
	काष्ठा avc_response_frame *r = (व्योम *)fdtv->avc_data;
	पूर्णांक ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_STATUS;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOR;

	c->opeअक्रम[0] = SFE_VENDOR_DE_COMPANYID_0;
	c->opeअक्रम[1] = SFE_VENDOR_DE_COMPANYID_1;
	c->opeअक्रम[2] = SFE_VENDOR_DE_COMPANYID_2;
	c->opeअक्रम[3] = SFE_VENDOR_OPCODE_CA2HOST;
	c->opeअक्रम[4] = 0; /* slot */
	c->opeअक्रम[5] = SFE_VENDOR_TAG_CA_MMI;
	clear_opeअक्रमs(c, 6, LAST_OPERAND);

	fdtv->avc_data_length = 12;
	ret = avc_ग_लिखो(fdtv);
	अगर (ret < 0)
		जाओ out;

	/* FIXME: check response code and validate response data */

	*len = get_ca_object_length(r);
	स_नकल(mmi_object, &r->opeअक्रम[get_ca_object_pos(r)], *len);
out:
	mutex_unlock(&fdtv->avc_mutex);

	वापस ret;
पूर्ण

#घोषणा CMP_OUTPUT_PLUG_CONTROL_REG_0	0xfffff0000904ULL

अटल पूर्णांक cmp_पढ़ो(काष्ठा firedtv *fdtv, u64 addr, __be32 *data)
अणु
	पूर्णांक ret;

	ret = fdtv_पढ़ो(fdtv, addr, data);
	अगर (ret < 0)
		dev_err(fdtv->device, "CMP: read I/O error\n");

	वापस ret;
पूर्ण

अटल पूर्णांक cmp_lock(काष्ठा firedtv *fdtv, u64 addr, __be32 data[])
अणु
	पूर्णांक ret;

	ret = fdtv_lock(fdtv, addr, data);
	अगर (ret < 0)
		dev_err(fdtv->device, "CMP: lock I/O error\n");

	वापस ret;
पूर्ण

अटल अंतरभूत u32 get_opcr(__be32 opcr, u32 mask, u32 shअगरt)
अणु
	वापस (be32_to_cpu(opcr) >> shअगरt) & mask;
पूर्ण

अटल अंतरभूत व्योम set_opcr(__be32 *opcr, u32 value, u32 mask, u32 shअगरt)
अणु
	*opcr &= ~cpu_to_be32(mask << shअगरt);
	*opcr |= cpu_to_be32((value & mask) << shअगरt);
पूर्ण

#घोषणा get_opcr_online(v)		get_opcr((v), 0x1, 31)
#घोषणा get_opcr_p2p_connections(v)	get_opcr((v), 0x3f, 24)
#घोषणा get_opcr_channel(v)		get_opcr((v), 0x3f, 16)

#घोषणा set_opcr_p2p_connections(p, v)	set_opcr((p), (v), 0x3f, 24)
#घोषणा set_opcr_channel(p, v)		set_opcr((p), (v), 0x3f, 16)
#घोषणा set_opcr_data_rate(p, v)	set_opcr((p), (v), 0x3, 14)
#घोषणा set_opcr_overhead_id(p, v)	set_opcr((p), (v), 0xf, 10)

पूर्णांक cmp_establish_pp_connection(काष्ठा firedtv *fdtv, पूर्णांक plug, पूर्णांक channel)
अणु
	__be32 old_opcr, opcr[2];
	u64 opcr_address = CMP_OUTPUT_PLUG_CONTROL_REG_0 + (plug << 2);
	पूर्णांक attempts = 0;
	पूर्णांक ret;

	ret = cmp_पढ़ो(fdtv, opcr_address, opcr);
	अगर (ret < 0)
		वापस ret;

repeat:
	अगर (!get_opcr_online(*opcr)) अणु
		dev_err(fdtv->device, "CMP: output offline\n");
		वापस -EBUSY;
	पूर्ण

	old_opcr = *opcr;

	अगर (get_opcr_p2p_connections(*opcr)) अणु
		अगर (get_opcr_channel(*opcr) != channel) अणु
			dev_err(fdtv->device, "CMP: cannot change channel\n");
			वापस -EBUSY;
		पूर्ण
		dev_info(fdtv->device, "CMP: overlaying connection\n");

		/* We करोn't allocate isochronous resources. */
	पूर्ण अन्यथा अणु
		set_opcr_channel(opcr, channel);
		set_opcr_data_rate(opcr, 2); /* S400 */

		/* FIXME: this is क्रम the worst हाल - optimize */
		set_opcr_overhead_id(opcr, 0);

		/* FIXME: allocate isochronous channel and bandwidth at IRM */
	पूर्ण

	set_opcr_p2p_connections(opcr, get_opcr_p2p_connections(*opcr) + 1);

	opcr[1] = *opcr;
	opcr[0] = old_opcr;

	ret = cmp_lock(fdtv, opcr_address, opcr);
	अगर (ret < 0)
		वापस ret;

	अगर (old_opcr != *opcr) अणु
		/*
		 * FIXME: अगर old_opcr.P2P_Connections > 0,
		 * deallocate isochronous channel and bandwidth at IRM
		 */

		अगर (++attempts < 6) /* arbitrary limit */
			जाओ repeat;
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

व्योम cmp_अवरोध_pp_connection(काष्ठा firedtv *fdtv, पूर्णांक plug, पूर्णांक channel)
अणु
	__be32 old_opcr, opcr[2];
	u64 opcr_address = CMP_OUTPUT_PLUG_CONTROL_REG_0 + (plug << 2);
	पूर्णांक attempts = 0;

	अगर (cmp_पढ़ो(fdtv, opcr_address, opcr) < 0)
		वापस;

repeat:
	अगर (!get_opcr_online(*opcr) || !get_opcr_p2p_connections(*opcr) ||
	    get_opcr_channel(*opcr) != channel) अणु
		dev_err(fdtv->device, "CMP: no connection to break\n");
		वापस;
	पूर्ण

	old_opcr = *opcr;
	set_opcr_p2p_connections(opcr, get_opcr_p2p_connections(*opcr) - 1);

	opcr[1] = *opcr;
	opcr[0] = old_opcr;

	अगर (cmp_lock(fdtv, opcr_address, opcr) < 0)
		वापस;

	अगर (old_opcr != *opcr) अणु
		/*
		 * FIXME: अगर old_opcr.P2P_Connections == 1, i.e. we were last
		 * owner, deallocate isochronous channel and bandwidth at IRM
		 * अगर (...)
		 *	fdtv->backend->dealloc_resources(fdtv, channel, bw);
		 */

		अगर (++attempts < 6) /* arbitrary limit */
			जाओ repeat;
	पूर्ण
पूर्ण
