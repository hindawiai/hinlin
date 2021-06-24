<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright तऊ 2016 Intel Corporation
 *
 * Authors:
 *    Scott  Bauer      <scott.bauer@पूर्णांकel.com>
 *    Rafael Antognolli <rafael.antognolli@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":OPAL: " fmt

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/genhd.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <uapi/linux/sed-opal.h>
#समावेश <linux/sed-opal.h>
#समावेश <linux/माला.स>
#समावेश <linux/kdev_t.h>

#समावेश "opal_proto.h"

#घोषणा IO_BUFFER_LENGTH 2048
#घोषणा MAX_TOKS 64

/* Number of bytes needed by cmd_finalize. */
#घोषणा CMD_FINALIZE_BYTES_NEEDED 7

काष्ठा opal_step अणु
	पूर्णांक (*fn)(काष्ठा opal_dev *dev, व्योम *data);
	व्योम *data;
पूर्ण;
प्रकार पूर्णांक (cont_fn)(काष्ठा opal_dev *dev);

क्रमागत opal_atom_width अणु
	OPAL_WIDTH_TINY,
	OPAL_WIDTH_SHORT,
	OPAL_WIDTH_MEDIUM,
	OPAL_WIDTH_LONG,
	OPAL_WIDTH_TOKEN
पूर्ण;

/*
 * On the parsed response, we करोn't store again the toks that are alपढ़ोy
 * stored in the response buffer. Instead, क्रम each token, we just store a
 * poपूर्णांकer to the position in the buffer where the token starts, and the size
 * of the token in bytes.
 */
काष्ठा opal_resp_tok अणु
	स्थिर u8 *pos;
	माप_प्रकार len;
	क्रमागत opal_response_token type;
	क्रमागत opal_atom_width width;
	जोड़ अणु
		u64 u;
		s64 s;
	पूर्ण stored;
पूर्ण;

/*
 * From the response header it's not possible to know how many tokens there are
 * on the payload. So we hardcode that the maximum will be MAX_TOKS, and later
 * अगर we start dealing with messages that have more than that, we can increase
 * this number. This is करोne to aव्योम having to make two passes through the
 * response, the first one counting how many tokens we have and the second one
 * actually storing the positions.
 */
काष्ठा parsed_resp अणु
	पूर्णांक num;
	काष्ठा opal_resp_tok toks[MAX_TOKS];
पूर्ण;

काष्ठा opal_dev अणु
	bool supported;
	bool mbr_enabled;

	व्योम *data;
	sec_send_recv *send_recv;

	काष्ठा mutex dev_lock;
	u16 comid;
	u32 hsn;
	u32 tsn;
	u64 align;
	u64 lowest_lba;

	माप_प्रकार pos;
	u8 cmd[IO_BUFFER_LENGTH];
	u8 resp[IO_BUFFER_LENGTH];

	काष्ठा parsed_resp parsed;
	माप_प्रकार prev_d_len;
	व्योम *prev_data;

	काष्ठा list_head unlk_lst;
पूर्ण;


अटल स्थिर u8 opaluid[][OPAL_UID_LENGTH] = अणु
	/* users */
	[OPAL_SMUID_UID] =
		अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff पूर्ण,
	[OPAL_THISSP_UID] =
		अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 पूर्ण,
	[OPAL_ADMINSP_UID] =
		अणु 0x00, 0x00, 0x02, 0x05, 0x00, 0x00, 0x00, 0x01 पूर्ण,
	[OPAL_LOCKINGSP_UID] =
		अणु 0x00, 0x00, 0x02, 0x05, 0x00, 0x00, 0x00, 0x02 पूर्ण,
	[OPAL_ENTERPRISE_LOCKINGSP_UID] =
		अणु 0x00, 0x00, 0x02, 0x05, 0x00, 0x01, 0x00, 0x01 पूर्ण,
	[OPAL_ANYBODY_UID] =
		अणु 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x01 पूर्ण,
	[OPAL_SID_UID] =
		अणु 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x06 पूर्ण,
	[OPAL_ADMIN1_UID] =
		अणु 0x00, 0x00, 0x00, 0x09, 0x00, 0x01, 0x00, 0x01 पूर्ण,
	[OPAL_USER1_UID] =
		अणु 0x00, 0x00, 0x00, 0x09, 0x00, 0x03, 0x00, 0x01 पूर्ण,
	[OPAL_USER2_UID] =
		अणु 0x00, 0x00, 0x00, 0x09, 0x00, 0x03, 0x00, 0x02 पूर्ण,
	[OPAL_PSID_UID] =
		अणु 0x00, 0x00, 0x00, 0x09, 0x00, 0x01, 0xff, 0x01 पूर्ण,
	[OPAL_ENTERPRISE_BANDMASTER0_UID] =
		अणु 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x80, 0x01 पूर्ण,
	[OPAL_ENTERPRISE_ERASEMASTER_UID] =
		अणु 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x84, 0x01 पूर्ण,

	/* tables */
	[OPAL_TABLE_TABLE] =
		अणु 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01 पूर्ण,
	[OPAL_LOCKINGRANGE_GLOBAL] =
		अणु 0x00, 0x00, 0x08, 0x02, 0x00, 0x00, 0x00, 0x01 पूर्ण,
	[OPAL_LOCKINGRANGE_ACE_RDLOCKED] =
		अणु 0x00, 0x00, 0x00, 0x08, 0x00, 0x03, 0xE0, 0x01 पूर्ण,
	[OPAL_LOCKINGRANGE_ACE_WRLOCKED] =
		अणु 0x00, 0x00, 0x00, 0x08, 0x00, 0x03, 0xE8, 0x01 पूर्ण,
	[OPAL_MBRCONTROL] =
		अणु 0x00, 0x00, 0x08, 0x03, 0x00, 0x00, 0x00, 0x01 पूर्ण,
	[OPAL_MBR] =
		अणु 0x00, 0x00, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00 पूर्ण,
	[OPAL_AUTHORITY_TABLE] =
		अणु 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00पूर्ण,
	[OPAL_C_PIN_TABLE] =
		अणु 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00पूर्ण,
	[OPAL_LOCKING_INFO_TABLE] =
		अणु 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0x00, 0x01 पूर्ण,
	[OPAL_ENTERPRISE_LOCKING_INFO_TABLE] =
		अणु 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00 पूर्ण,
	[OPAL_DATASTORE] =
		अणु 0x00, 0x00, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00 पूर्ण,

	/* C_PIN_TABLE object ID's */
	[OPAL_C_PIN_MSID] =
		अणु 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x84, 0x02पूर्ण,
	[OPAL_C_PIN_SID] =
		अणु 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x01पूर्ण,
	[OPAL_C_PIN_ADMIN1] =
		अणु 0x00, 0x00, 0x00, 0x0B, 0x00, 0x01, 0x00, 0x01पूर्ण,

	/* half UID's (only first 4 bytes used) */
	[OPAL_HALF_UID_AUTHORITY_OBJ_REF] =
		अणु 0x00, 0x00, 0x0C, 0x05, 0xff, 0xff, 0xff, 0xff पूर्ण,
	[OPAL_HALF_UID_BOOLEAN_ACE] =
		अणु 0x00, 0x00, 0x04, 0x0E, 0xff, 0xff, 0xff, 0xff पूर्ण,

	/* special value क्रम omitted optional parameter */
	[OPAL_UID_HEXFF] =
		अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण,
पूर्ण;

/*
 * TCG Storage SSC Methods.
 * Derived from: TCG_Storage_Architecture_Core_Spec_v2.01_r1.00
 * Section: 6.3 Asचिन्हित UIDs
 */
अटल स्थिर u8 opalmethod[][OPAL_METHOD_LENGTH] = अणु
	[OPAL_PROPERTIES] =
		अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x01 पूर्ण,
	[OPAL_STARTSESSION] =
		अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x02 पूर्ण,
	[OPAL_REVERT] =
		अणु 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x02, 0x02 पूर्ण,
	[OPAL_ACTIVATE] =
		अणु 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x02, 0x03 पूर्ण,
	[OPAL_EGET] =
		अणु 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06 पूर्ण,
	[OPAL_ESET] =
		अणु 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x07 पूर्ण,
	[OPAL_NEXT] =
		अणु 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x08 पूर्ण,
	[OPAL_EAUTHENTICATE] =
		अणु 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0c पूर्ण,
	[OPAL_GETACL] =
		अणु 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0d पूर्ण,
	[OPAL_GENKEY] =
		अणु 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x10 पूर्ण,
	[OPAL_REVERTSP] =
		अणु 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x11 पूर्ण,
	[OPAL_GET] =
		अणु 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x16 पूर्ण,
	[OPAL_SET] =
		अणु 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x17 पूर्ण,
	[OPAL_AUTHENTICATE] =
		अणु 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x1c पूर्ण,
	[OPAL_RANDOM] =
		अणु 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x01 पूर्ण,
	[OPAL_ERASE] =
		अणु 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x08, 0x03 पूर्ण,
पूर्ण;

अटल पूर्णांक end_opal_session_error(काष्ठा opal_dev *dev);
अटल पूर्णांक opal_discovery0_step(काष्ठा opal_dev *dev);

काष्ठा opal_suspend_data अणु
	काष्ठा opal_lock_unlock unlk;
	u8 lr;
	काष्ठा list_head node;
पूर्ण;

/*
 * Derived from:
 * TCG_Storage_Architecture_Core_Spec_v2.01_r1.00
 * Section: 5.1.5 Method Status Codes
 */
अटल स्थिर अक्षर * स्थिर opal_errors[] = अणु
	"Success",
	"Not Authorized",
	"Unknown Error",
	"SP Busy",
	"SP Failed",
	"SP Disabled",
	"SP Frozen",
	"No Sessions Available",
	"Uniqueness Conflict",
	"Insufficient Space",
	"Insufficient Rows",
	"Invalid Function",
	"Invalid Parameter",
	"Invalid Reference",
	"Unknown Error",
	"TPER Malfunction",
	"Transaction Failure",
	"Response Overflow",
	"Authority Locked Out",
पूर्ण;

अटल स्थिर अक्षर *opal_error_to_human(पूर्णांक error)
अणु
	अगर (error == 0x3f)
		वापस "Failed";

	अगर (error >= ARRAY_SIZE(opal_errors) || error < 0)
		वापस "Unknown Error";

	वापस opal_errors[error];
पूर्ण

अटल व्योम prपूर्णांक_buffer(स्थिर u8 *ptr, u32 length)
अणु
#अगर_घोषित DEBUG
	prपूर्णांक_hex_dump_bytes("OPAL: ", DUMP_PREFIX_OFFSET, ptr, length);
	pr_debug("\n");
#पूर्ण_अगर
पूर्ण

अटल bool check_tper(स्थिर व्योम *data)
अणु
	स्थिर काष्ठा d0_tper_features *tper = data;
	u8 flags = tper->supported_features;

	अगर (!(flags & TPER_SYNC_SUPPORTED)) अणु
		pr_debug("TPer sync not supported. flags = %d\n",
			 tper->supported_features);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool check_mbrenabled(स्थिर व्योम *data)
अणु
	स्थिर काष्ठा d0_locking_features *lfeat = data;
	u8 sup_feat = lfeat->supported_features;

	वापस !!(sup_feat & MBR_ENABLED_MASK);
पूर्ण

अटल bool check_sum(स्थिर व्योम *data)
अणु
	स्थिर काष्ठा d0_single_user_mode *sum = data;
	u32 nlo = be32_to_cpu(sum->num_locking_objects);

	अगर (nlo == 0) अणु
		pr_debug("Need at least one locking object.\n");
		वापस false;
	पूर्ण

	pr_debug("Number of locking objects: %d\n", nlo);

	वापस true;
पूर्ण

अटल u16 get_comid_v100(स्थिर व्योम *data)
अणु
	स्थिर काष्ठा d0_opal_v100 *v100 = data;

	वापस be16_to_cpu(v100->baseComID);
पूर्ण

अटल u16 get_comid_v200(स्थिर व्योम *data)
अणु
	स्थिर काष्ठा d0_opal_v200 *v200 = data;

	वापस be16_to_cpu(v200->baseComID);
पूर्ण

अटल पूर्णांक opal_send_cmd(काष्ठा opal_dev *dev)
अणु
	वापस dev->send_recv(dev->data, dev->comid, TCG_SECP_01,
			      dev->cmd, IO_BUFFER_LENGTH,
			      true);
पूर्ण

अटल पूर्णांक opal_recv_cmd(काष्ठा opal_dev *dev)
अणु
	वापस dev->send_recv(dev->data, dev->comid, TCG_SECP_01,
			      dev->resp, IO_BUFFER_LENGTH,
			      false);
पूर्ण

अटल पूर्णांक opal_recv_check(काष्ठा opal_dev *dev)
अणु
	माप_प्रकार buflen = IO_BUFFER_LENGTH;
	व्योम *buffer = dev->resp;
	काष्ठा opal_header *hdr = buffer;
	पूर्णांक ret;

	करो अणु
		pr_debug("Sent OPAL command: outstanding=%d, minTransfer=%d\n",
			 hdr->cp.outstandingData,
			 hdr->cp.minTransfer);

		अगर (hdr->cp.outstandingData == 0 ||
		    hdr->cp.minTransfer != 0)
			वापस 0;

		स_रखो(buffer, 0, buflen);
		ret = opal_recv_cmd(dev);
	पूर्ण जबतक (!ret);

	वापस ret;
पूर्ण

अटल पूर्णांक opal_send_recv(काष्ठा opal_dev *dev, cont_fn *cont)
अणु
	पूर्णांक ret;

	ret = opal_send_cmd(dev);
	अगर (ret)
		वापस ret;
	ret = opal_recv_cmd(dev);
	अगर (ret)
		वापस ret;
	ret = opal_recv_check(dev);
	अगर (ret)
		वापस ret;
	वापस cont(dev);
पूर्ण

अटल व्योम check_geometry(काष्ठा opal_dev *dev, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा d0_geometry_features *geo = data;

	dev->align = be64_to_cpu(geo->alignment_granularity);
	dev->lowest_lba = be64_to_cpu(geo->lowest_aligned_lba);
पूर्ण

अटल पूर्णांक execute_step(काष्ठा opal_dev *dev,
			स्थिर काष्ठा opal_step *step, माप_प्रकार stepIndex)
अणु
	पूर्णांक error = step->fn(dev, step->data);

	अगर (error) अणु
		pr_debug("Step %zu (%pS) failed with error %d: %s\n",
			 stepIndex, step->fn, error,
			 opal_error_to_human(error));
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक execute_steps(काष्ठा opal_dev *dev,
			 स्थिर काष्ठा opal_step *steps, माप_प्रकार n_steps)
अणु
	माप_प्रकार state = 0;
	पूर्णांक error;

	/* first करो a discovery0 */
	error = opal_discovery0_step(dev);
	अगर (error)
		वापस error;

	क्रम (state = 0; state < n_steps; state++) अणु
		error = execute_step(dev, &steps[state], state);
		अगर (error)
			जाओ out_error;
	पूर्ण

	वापस 0;

out_error:
	/*
	 * For each OPAL command the first step in steps starts some sort of
	 * session. If an error occurred in the initial discovery0 or अगर an
	 * error occurred in the first step (and thus stopping the loop with
	 * state == 0) then there was an error beक्रमe or during the attempt to
	 * start a session. Thereक्रमe we shouldn't attempt to terminate a
	 * session, as one has not yet been created.
	 */
	अगर (state > 0)
		end_opal_session_error(dev);

	वापस error;
पूर्ण

अटल पूर्णांक opal_discovery0_end(काष्ठा opal_dev *dev)
अणु
	bool found_com_id = false, supported = true, single_user = false;
	स्थिर काष्ठा d0_header *hdr = (काष्ठा d0_header *)dev->resp;
	स्थिर u8 *epos = dev->resp, *cpos = dev->resp;
	u16 comid = 0;
	u32 hlen = be32_to_cpu(hdr->length);

	prपूर्णांक_buffer(dev->resp, hlen);
	dev->mbr_enabled = false;

	अगर (hlen > IO_BUFFER_LENGTH - माप(*hdr)) अणु
		pr_debug("Discovery length overflows buffer (%zu+%u)/%u\n",
			 माप(*hdr), hlen, IO_BUFFER_LENGTH);
		वापस -EFAULT;
	पूर्ण

	epos += hlen; /* end of buffer */
	cpos += माप(*hdr); /* current position on buffer */

	जबतक (cpos < epos && supported) अणु
		स्थिर काष्ठा d0_features *body =
			(स्थिर काष्ठा d0_features *)cpos;

		चयन (be16_to_cpu(body->code)) अणु
		हाल FC_TPER:
			supported = check_tper(body->features);
			अवरोध;
		हाल FC_SINGLEUSER:
			single_user = check_sum(body->features);
			अवरोध;
		हाल FC_GEOMETRY:
			check_geometry(dev, body);
			अवरोध;
		हाल FC_LOCKING:
			dev->mbr_enabled = check_mbrenabled(body->features);
			अवरोध;
		हाल FC_ENTERPRISE:
		हाल FC_DATASTORE:
			/* some ignored properties */
			pr_debug("Found OPAL feature description: %d\n",
				 be16_to_cpu(body->code));
			अवरोध;
		हाल FC_OPALV100:
			comid = get_comid_v100(body->features);
			found_com_id = true;
			अवरोध;
		हाल FC_OPALV200:
			comid = get_comid_v200(body->features);
			found_com_id = true;
			अवरोध;
		हाल 0xbfff ... 0xffff:
			/* venकरोr specअगरic, just ignore */
			अवरोध;
		शेष:
			pr_debug("OPAL Unknown feature: %d\n",
				 be16_to_cpu(body->code));

		पूर्ण
		cpos += body->length + 4;
	पूर्ण

	अगर (!supported) अणु
		pr_debug("This device is not Opal enabled. Not Supported!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!single_user)
		pr_debug("Device doesn't support single user mode\n");


	अगर (!found_com_id) अणु
		pr_debug("Could not find OPAL comid for device. Returning early\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	dev->comid = comid;

	वापस 0;
पूर्ण

अटल पूर्णांक opal_discovery0(काष्ठा opal_dev *dev, व्योम *data)
अणु
	पूर्णांक ret;

	स_रखो(dev->resp, 0, IO_BUFFER_LENGTH);
	dev->comid = OPAL_DISCOVERY_COMID;
	ret = opal_recv_cmd(dev);
	अगर (ret)
		वापस ret;

	वापस opal_discovery0_end(dev);
पूर्ण

अटल पूर्णांक opal_discovery0_step(काष्ठा opal_dev *dev)
अणु
	स्थिर काष्ठा opal_step discovery0_step = अणु
		opal_discovery0,
	पूर्ण;

	वापस execute_step(dev, &discovery0_step, 0);
पूर्ण

अटल माप_प्रकार reमुख्यing_size(काष्ठा opal_dev *cmd)
अणु
	वापस IO_BUFFER_LENGTH - cmd->pos;
पूर्ण

अटल bool can_add(पूर्णांक *err, काष्ठा opal_dev *cmd, माप_प्रकार len)
अणु
	अगर (*err)
		वापस false;

	अगर (reमुख्यing_size(cmd) < len) अणु
		pr_debug("Error adding %zu bytes: end of buffer.\n", len);
		*err = -दुस्फल;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम add_token_u8(पूर्णांक *err, काष्ठा opal_dev *cmd, u8 tok)
अणु
	अगर (!can_add(err, cmd, 1))
		वापस;

	cmd->cmd[cmd->pos++] = tok;
पूर्ण

अटल व्योम add_लघु_atom_header(काष्ठा opal_dev *cmd, bool bytestring,
				  bool has_sign, पूर्णांक len)
अणु
	u8 atom;
	पूर्णांक err = 0;

	atom = SHORT_ATOM_ID;
	atom |= bytestring ? SHORT_ATOM_BYTESTRING : 0;
	atom |= has_sign ? SHORT_ATOM_SIGNED : 0;
	atom |= len & SHORT_ATOM_LEN_MASK;

	add_token_u8(&err, cmd, atom);
पूर्ण

अटल व्योम add_medium_atom_header(काष्ठा opal_dev *cmd, bool bytestring,
				   bool has_sign, पूर्णांक len)
अणु
	u8 header0;

	header0 = MEDIUM_ATOM_ID;
	header0 |= bytestring ? MEDIUM_ATOM_BYTESTRING : 0;
	header0 |= has_sign ? MEDIUM_ATOM_SIGNED : 0;
	header0 |= (len >> 8) & MEDIUM_ATOM_LEN_MASK;

	cmd->cmd[cmd->pos++] = header0;
	cmd->cmd[cmd->pos++] = len;
पूर्ण

अटल व्योम add_token_u64(पूर्णांक *err, काष्ठा opal_dev *cmd, u64 number)
अणु
	माप_प्रकार len;
	पूर्णांक msb;

	अगर (!(number & ~TINY_ATOM_DATA_MASK)) अणु
		add_token_u8(err, cmd, number);
		वापस;
	पूर्ण

	msb = fls64(number);
	len = DIV_ROUND_UP(msb, 8);

	अगर (!can_add(err, cmd, len + 1)) अणु
		pr_debug("Error adding u64: end of buffer.\n");
		वापस;
	पूर्ण
	add_लघु_atom_header(cmd, false, false, len);
	जबतक (len--)
		add_token_u8(err, cmd, number >> (len * 8));
पूर्ण

अटल u8 *add_bytestring_header(पूर्णांक *err, काष्ठा opal_dev *cmd, माप_प्रकार len)
अणु
	माप_प्रकार header_len = 1;
	bool is_लघु_atom = true;

	अगर (len & ~SHORT_ATOM_LEN_MASK) अणु
		header_len = 2;
		is_लघु_atom = false;
	पूर्ण

	अगर (!can_add(err, cmd, header_len + len)) अणु
		pr_debug("Error adding bytestring: end of buffer.\n");
		वापस शून्य;
	पूर्ण

	अगर (is_लघु_atom)
		add_लघु_atom_header(cmd, true, false, len);
	अन्यथा
		add_medium_atom_header(cmd, true, false, len);

	वापस &cmd->cmd[cmd->pos];
पूर्ण

अटल व्योम add_token_bytestring(पूर्णांक *err, काष्ठा opal_dev *cmd,
				 स्थिर u8 *bytestring, माप_प्रकार len)
अणु
	u8 *start;

	start = add_bytestring_header(err, cmd, len);
	अगर (!start)
		वापस;
	स_नकल(start, bytestring, len);
	cmd->pos += len;
पूर्ण

अटल पूर्णांक build_locking_range(u8 *buffer, माप_प्रकार length, u8 lr)
अणु
	अगर (length > OPAL_UID_LENGTH) अणु
		pr_debug("Can't build locking range. Length OOB\n");
		वापस -दुस्फल;
	पूर्ण

	स_नकल(buffer, opaluid[OPAL_LOCKINGRANGE_GLOBAL], OPAL_UID_LENGTH);

	अगर (lr == 0)
		वापस 0;

	buffer[5] = LOCKING_RANGE_NON_GLOBAL;
	buffer[7] = lr;

	वापस 0;
पूर्ण

अटल पूर्णांक build_locking_user(u8 *buffer, माप_प्रकार length, u8 lr)
अणु
	अगर (length > OPAL_UID_LENGTH) अणु
		pr_debug("Can't build locking range user. Length OOB\n");
		वापस -दुस्फल;
	पूर्ण

	स_नकल(buffer, opaluid[OPAL_USER1_UID], OPAL_UID_LENGTH);

	buffer[7] = lr + 1;

	वापस 0;
पूर्ण

अटल व्योम set_comid(काष्ठा opal_dev *cmd, u16 comid)
अणु
	काष्ठा opal_header *hdr = (काष्ठा opal_header *)cmd->cmd;

	hdr->cp.extendedComID[0] = comid >> 8;
	hdr->cp.extendedComID[1] = comid;
	hdr->cp.extendedComID[2] = 0;
	hdr->cp.extendedComID[3] = 0;
पूर्ण

अटल पूर्णांक cmd_finalize(काष्ठा opal_dev *cmd, u32 hsn, u32 tsn)
अणु
	काष्ठा opal_header *hdr;
	पूर्णांक err = 0;

	/*
	 * Close the parameter list खोलोed from cmd_start.
	 * The number of bytes added must be equal to
	 * CMD_FINALIZE_BYTES_NEEDED.
	 */
	add_token_u8(&err, cmd, OPAL_ENDLIST);

	add_token_u8(&err, cmd, OPAL_ENDOFDATA);
	add_token_u8(&err, cmd, OPAL_STARTLIST);
	add_token_u8(&err, cmd, 0);
	add_token_u8(&err, cmd, 0);
	add_token_u8(&err, cmd, 0);
	add_token_u8(&err, cmd, OPAL_ENDLIST);

	अगर (err) अणु
		pr_debug("Error finalizing command.\n");
		वापस -EFAULT;
	पूर्ण

	hdr = (काष्ठा opal_header *) cmd->cmd;

	hdr->pkt.tsn = cpu_to_be32(tsn);
	hdr->pkt.hsn = cpu_to_be32(hsn);

	hdr->subpkt.length = cpu_to_be32(cmd->pos - माप(*hdr));
	जबतक (cmd->pos % 4) अणु
		अगर (cmd->pos >= IO_BUFFER_LENGTH) अणु
			pr_debug("Error: Buffer overrun\n");
			वापस -दुस्फल;
		पूर्ण
		cmd->cmd[cmd->pos++] = 0;
	पूर्ण
	hdr->pkt.length = cpu_to_be32(cmd->pos - माप(hdr->cp) -
				      माप(hdr->pkt));
	hdr->cp.length = cpu_to_be32(cmd->pos - माप(hdr->cp));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा opal_resp_tok *response_get_token(
				स्थिर काष्ठा parsed_resp *resp,
				पूर्णांक n)
अणु
	स्थिर काष्ठा opal_resp_tok *tok;

	अगर (!resp) अणु
		pr_debug("Response is NULL\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (n >= resp->num) अणु
		pr_debug("Token number doesn't exist: %d, resp: %d\n",
			 n, resp->num);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	tok = &resp->toks[n];
	अगर (tok->len == 0) अणु
		pr_debug("Token length must be non-zero\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस tok;
पूर्ण

अटल sमाप_प्रकार response_parse_tiny(काष्ठा opal_resp_tok *tok,
				   स्थिर u8 *pos)
अणु
	tok->pos = pos;
	tok->len = 1;
	tok->width = OPAL_WIDTH_TINY;

	अगर (pos[0] & TINY_ATOM_SIGNED) अणु
		tok->type = OPAL_DTA_TOKENID_SINT;
	पूर्ण अन्यथा अणु
		tok->type = OPAL_DTA_TOKENID_UINT;
		tok->stored.u = pos[0] & 0x3f;
	पूर्ण

	वापस tok->len;
पूर्ण

अटल sमाप_प्रकार response_parse_लघु(काष्ठा opal_resp_tok *tok,
				    स्थिर u8 *pos)
अणु
	tok->pos = pos;
	tok->len = (pos[0] & SHORT_ATOM_LEN_MASK) + 1;
	tok->width = OPAL_WIDTH_SHORT;

	अगर (pos[0] & SHORT_ATOM_BYTESTRING) अणु
		tok->type = OPAL_DTA_TOKENID_BYTESTRING;
	पूर्ण अन्यथा अगर (pos[0] & SHORT_ATOM_SIGNED) अणु
		tok->type = OPAL_DTA_TOKENID_SINT;
	पूर्ण अन्यथा अणु
		u64 u_पूर्णांकeger = 0;
		sमाप_प्रकार i, b = 0;

		tok->type = OPAL_DTA_TOKENID_UINT;
		अगर (tok->len > 9) अणु
			pr_debug("uint64 with more than 8 bytes\n");
			वापस -EINVAL;
		पूर्ण
		क्रम (i = tok->len - 1; i > 0; i--) अणु
			u_पूर्णांकeger |= ((u64)pos[i] << (8 * b));
			b++;
		पूर्ण
		tok->stored.u = u_पूर्णांकeger;
	पूर्ण

	वापस tok->len;
पूर्ण

अटल sमाप_प्रकार response_parse_medium(काष्ठा opal_resp_tok *tok,
				     स्थिर u8 *pos)
अणु
	tok->pos = pos;
	tok->len = (((pos[0] & MEDIUM_ATOM_LEN_MASK) << 8) | pos[1]) + 2;
	tok->width = OPAL_WIDTH_MEDIUM;

	अगर (pos[0] & MEDIUM_ATOM_BYTESTRING)
		tok->type = OPAL_DTA_TOKENID_BYTESTRING;
	अन्यथा अगर (pos[0] & MEDIUM_ATOM_SIGNED)
		tok->type = OPAL_DTA_TOKENID_SINT;
	अन्यथा
		tok->type = OPAL_DTA_TOKENID_UINT;

	वापस tok->len;
पूर्ण

अटल sमाप_प्रकार response_parse_दीर्घ(काष्ठा opal_resp_tok *tok,
				   स्थिर u8 *pos)
अणु
	tok->pos = pos;
	tok->len = ((pos[1] << 16) | (pos[2] << 8) | pos[3]) + 4;
	tok->width = OPAL_WIDTH_LONG;

	अगर (pos[0] & LONG_ATOM_BYTESTRING)
		tok->type = OPAL_DTA_TOKENID_BYTESTRING;
	अन्यथा अगर (pos[0] & LONG_ATOM_SIGNED)
		tok->type = OPAL_DTA_TOKENID_SINT;
	अन्यथा
		tok->type = OPAL_DTA_TOKENID_UINT;

	वापस tok->len;
पूर्ण

अटल sमाप_प्रकार response_parse_token(काष्ठा opal_resp_tok *tok,
				    स्थिर u8 *pos)
अणु
	tok->pos = pos;
	tok->len = 1;
	tok->type = OPAL_DTA_TOKENID_TOKEN;
	tok->width = OPAL_WIDTH_TOKEN;

	वापस tok->len;
पूर्ण

अटल पूर्णांक response_parse(स्थिर u8 *buf, माप_प्रकार length,
			  काष्ठा parsed_resp *resp)
अणु
	स्थिर काष्ठा opal_header *hdr;
	काष्ठा opal_resp_tok *iter;
	पूर्णांक num_entries = 0;
	पूर्णांक total;
	sमाप_प्रकार token_length;
	स्थिर u8 *pos;
	u32 clen, plen, slen;

	अगर (!buf)
		वापस -EFAULT;

	अगर (!resp)
		वापस -EFAULT;

	hdr = (काष्ठा opal_header *)buf;
	pos = buf;
	pos += माप(*hdr);

	clen = be32_to_cpu(hdr->cp.length);
	plen = be32_to_cpu(hdr->pkt.length);
	slen = be32_to_cpu(hdr->subpkt.length);
	pr_debug("Response size: cp: %u, pkt: %u, subpkt: %u\n",
		 clen, plen, slen);

	अगर (clen == 0 || plen == 0 || slen == 0 ||
	    slen > IO_BUFFER_LENGTH - माप(*hdr)) अणु
		pr_debug("Bad header length. cp: %u, pkt: %u, subpkt: %u\n",
			 clen, plen, slen);
		prपूर्णांक_buffer(pos, माप(*hdr));
		वापस -EINVAL;
	पूर्ण

	अगर (pos > buf + length)
		वापस -EFAULT;

	iter = resp->toks;
	total = slen;
	prपूर्णांक_buffer(pos, total);
	जबतक (total > 0) अणु
		अगर (pos[0] <= TINY_ATOM_BYTE) /* tiny atom */
			token_length = response_parse_tiny(iter, pos);
		अन्यथा अगर (pos[0] <= SHORT_ATOM_BYTE) /* लघु atom */
			token_length = response_parse_लघु(iter, pos);
		अन्यथा अगर (pos[0] <= MEDIUM_ATOM_BYTE) /* medium atom */
			token_length = response_parse_medium(iter, pos);
		अन्यथा अगर (pos[0] <= LONG_ATOM_BYTE) /* दीर्घ atom */
			token_length = response_parse_दीर्घ(iter, pos);
		अन्यथा /* TOKEN */
			token_length = response_parse_token(iter, pos);

		अगर (token_length < 0)
			वापस token_length;

		pos += token_length;
		total -= token_length;
		iter++;
		num_entries++;
	पूर्ण

	resp->num = num_entries;

	वापस 0;
पूर्ण

अटल माप_प्रकार response_get_string(स्थिर काष्ठा parsed_resp *resp, पूर्णांक n,
				  स्थिर अक्षर **store)
अणु
	u8 skip;
	स्थिर काष्ठा opal_resp_tok *tok;

	*store = शून्य;
	tok = response_get_token(resp, n);
	अगर (IS_ERR(tok))
		वापस 0;

	अगर (tok->type != OPAL_DTA_TOKENID_BYTESTRING) अणु
		pr_debug("Token is not a byte string!\n");
		वापस 0;
	पूर्ण

	चयन (tok->width) अणु
	हाल OPAL_WIDTH_TINY:
	हाल OPAL_WIDTH_SHORT:
		skip = 1;
		अवरोध;
	हाल OPAL_WIDTH_MEDIUM:
		skip = 2;
		अवरोध;
	हाल OPAL_WIDTH_LONG:
		skip = 4;
		अवरोध;
	शेष:
		pr_debug("Token has invalid width!\n");
		वापस 0;
	पूर्ण

	*store = tok->pos + skip;

	वापस tok->len - skip;
पूर्ण

अटल u64 response_get_u64(स्थिर काष्ठा parsed_resp *resp, पूर्णांक n)
अणु
	स्थिर काष्ठा opal_resp_tok *tok;

	tok = response_get_token(resp, n);
	अगर (IS_ERR(tok))
		वापस 0;

	अगर (tok->type != OPAL_DTA_TOKENID_UINT) अणु
		pr_debug("Token is not unsigned int: %d\n", tok->type);
		वापस 0;
	पूर्ण

	अगर (tok->width != OPAL_WIDTH_TINY && tok->width != OPAL_WIDTH_SHORT) अणु
		pr_debug("Atom is not short or tiny: %d\n", tok->width);
		वापस 0;
	पूर्ण

	वापस tok->stored.u;
पूर्ण

अटल bool response_token_matches(स्थिर काष्ठा opal_resp_tok *token, u8 match)
अणु
	अगर (IS_ERR(token) ||
	    token->type != OPAL_DTA_TOKENID_TOKEN ||
	    token->pos[0] != match)
		वापस false;
	वापस true;
पूर्ण

अटल u8 response_status(स्थिर काष्ठा parsed_resp *resp)
अणु
	स्थिर काष्ठा opal_resp_tok *tok;

	tok = response_get_token(resp, 0);
	अगर (response_token_matches(tok, OPAL_ENDOFSESSION))
		वापस 0;

	अगर (resp->num < 5)
		वापस DTAERROR_NO_METHOD_STATUS;

	tok = response_get_token(resp, resp->num - 5);
	अगर (!response_token_matches(tok, OPAL_STARTLIST))
		वापस DTAERROR_NO_METHOD_STATUS;

	tok = response_get_token(resp, resp->num - 1);
	अगर (!response_token_matches(tok, OPAL_ENDLIST))
		वापस DTAERROR_NO_METHOD_STATUS;

	वापस response_get_u64(resp, resp->num - 4);
पूर्ण

/* Parses and checks क्रम errors */
अटल पूर्णांक parse_and_check_status(काष्ठा opal_dev *dev)
अणु
	पूर्णांक error;

	prपूर्णांक_buffer(dev->cmd, dev->pos);

	error = response_parse(dev->resp, IO_BUFFER_LENGTH, &dev->parsed);
	अगर (error) अणु
		pr_debug("Couldn't parse response.\n");
		वापस error;
	पूर्ण

	वापस response_status(&dev->parsed);
पूर्ण

अटल व्योम clear_opal_cmd(काष्ठा opal_dev *dev)
अणु
	dev->pos = माप(काष्ठा opal_header);
	स_रखो(dev->cmd, 0, IO_BUFFER_LENGTH);
पूर्ण

अटल पूर्णांक cmd_start(काष्ठा opal_dev *dev, स्थिर u8 *uid, स्थिर u8 *method)
अणु
	पूर्णांक err = 0;

	clear_opal_cmd(dev);
	set_comid(dev, dev->comid);

	add_token_u8(&err, dev, OPAL_CALL);
	add_token_bytestring(&err, dev, uid, OPAL_UID_LENGTH);
	add_token_bytestring(&err, dev, method, OPAL_METHOD_LENGTH);

	/*
	 * Every method call is followed by its parameters enबंदd within
	 * OPAL_STARTLIST and OPAL_ENDLIST tokens. We स्वतःmatically खोलो the
	 * parameter list here and बंद it later in cmd_finalize.
	 */
	add_token_u8(&err, dev, OPAL_STARTLIST);

	वापस err;
पूर्ण

अटल पूर्णांक start_opal_session_cont(काष्ठा opal_dev *dev)
अणु
	u32 hsn, tsn;
	पूर्णांक error = 0;

	error = parse_and_check_status(dev);
	अगर (error)
		वापस error;

	hsn = response_get_u64(&dev->parsed, 4);
	tsn = response_get_u64(&dev->parsed, 5);

	अगर (hsn != GENERIC_HOST_SESSION_NUM || tsn < FIRST_TPER_SESSION_NUM) अणु
		pr_debug("Couldn't authenticate session\n");
		वापस -EPERM;
	पूर्ण

	dev->hsn = hsn;
	dev->tsn = tsn;

	वापस 0;
पूर्ण

अटल व्योम add_suspend_info(काष्ठा opal_dev *dev,
			     काष्ठा opal_suspend_data *sus)
अणु
	काष्ठा opal_suspend_data *iter;

	list_क्रम_each_entry(iter, &dev->unlk_lst, node) अणु
		अगर (iter->lr == sus->lr) अणु
			list_del(&iter->node);
			kमुक्त(iter);
			अवरोध;
		पूर्ण
	पूर्ण
	list_add_tail(&sus->node, &dev->unlk_lst);
पूर्ण

अटल पूर्णांक end_session_cont(काष्ठा opal_dev *dev)
अणु
	dev->hsn = 0;
	dev->tsn = 0;

	वापस parse_and_check_status(dev);
पूर्ण

अटल पूर्णांक finalize_and_send(काष्ठा opal_dev *dev, cont_fn cont)
अणु
	पूर्णांक ret;

	ret = cmd_finalize(dev, dev->hsn, dev->tsn);
	अगर (ret) अणु
		pr_debug("Error finalizing command buffer: %d\n", ret);
		वापस ret;
	पूर्ण

	prपूर्णांक_buffer(dev->cmd, dev->pos);

	वापस opal_send_recv(dev, cont);
पूर्ण

/*
 * request @column from table @table on device @dev. On success, the column
 * data will be available in dev->resp->tok[4]
 */
अटल पूर्णांक generic_get_column(काष्ठा opal_dev *dev, स्थिर u8 *table,
			      u64 column)
अणु
	पूर्णांक err;

	err = cmd_start(dev, table, opalmethod[OPAL_GET]);

	add_token_u8(&err, dev, OPAL_STARTLIST);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_STARTCOLUMN);
	add_token_u64(&err, dev, column);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_ENDCOLUMN);
	add_token_u64(&err, dev, column);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_ENDLIST);

	अगर (err)
		वापस err;

	वापस finalize_and_send(dev, parse_and_check_status);
पूर्ण

/*
 * see TCG SAS 5.3.2.3 क्रम a description of the available columns
 *
 * the result is provided in dev->resp->tok[4]
 */
अटल पूर्णांक generic_get_table_info(काष्ठा opal_dev *dev, स्थिर u8 *table_uid,
				  u64 column)
अणु
	u8 uid[OPAL_UID_LENGTH];
	स्थिर अचिन्हित पूर्णांक half = OPAL_UID_LENGTH_HALF;

	/* sed-opal UIDs can be split in two halves:
	 *  first:  actual table index
	 *  second: relative index in the table
	 * so we have to get the first half of the OPAL_TABLE_TABLE and use the
	 * first part of the target table as relative index पूर्णांकo that table
	 */
	स_नकल(uid, opaluid[OPAL_TABLE_TABLE], half);
	स_नकल(uid + half, table_uid, half);

	वापस generic_get_column(dev, uid, column);
पूर्ण

अटल पूर्णांक gen_key(काष्ठा opal_dev *dev, व्योम *data)
अणु
	u8 uid[OPAL_UID_LENGTH];
	पूर्णांक err;

	स_नकल(uid, dev->prev_data, min(माप(uid), dev->prev_d_len));
	kमुक्त(dev->prev_data);
	dev->prev_data = शून्य;

	err = cmd_start(dev, uid, opalmethod[OPAL_GENKEY]);

	अगर (err) अणु
		pr_debug("Error building gen key command\n");
		वापस err;

	पूर्ण

	वापस finalize_and_send(dev, parse_and_check_status);
पूर्ण

अटल पूर्णांक get_active_key_cont(काष्ठा opal_dev *dev)
अणु
	स्थिर अक्षर *activekey;
	माप_प्रकार keylen;
	पूर्णांक error = 0;

	error = parse_and_check_status(dev);
	अगर (error)
		वापस error;

	keylen = response_get_string(&dev->parsed, 4, &activekey);
	अगर (!activekey) अणु
		pr_debug("%s: Couldn't extract the Activekey from the response\n",
			 __func__);
		वापस OPAL_INVAL_PARAM;
	पूर्ण

	dev->prev_data = kmemdup(activekey, keylen, GFP_KERNEL);

	अगर (!dev->prev_data)
		वापस -ENOMEM;

	dev->prev_d_len = keylen;

	वापस 0;
पूर्ण

अटल पूर्णांक get_active_key(काष्ठा opal_dev *dev, व्योम *data)
अणु
	u8 uid[OPAL_UID_LENGTH];
	पूर्णांक err;
	u8 *lr = data;

	err = build_locking_range(uid, माप(uid), *lr);
	अगर (err)
		वापस err;

	err = generic_get_column(dev, uid, OPAL_ACTIVEKEY);
	अगर (err)
		वापस err;

	वापस get_active_key_cont(dev);
पूर्ण

अटल पूर्णांक generic_table_ग_लिखो_data(काष्ठा opal_dev *dev, स्थिर u64 data,
				    u64 offset, u64 size, स्थिर u8 *uid)
अणु
	स्थिर u8 __user *src = (u8 __user *)(uपूर्णांकptr_t)data;
	u8 *dst;
	u64 len;
	माप_प्रकार off = 0;
	पूर्णांक err;

	/* करो we fit in the available space? */
	err = generic_get_table_info(dev, uid, OPAL_TABLE_ROWS);
	अगर (err) अणु
		pr_debug("Couldn't get the table size\n");
		वापस err;
	पूर्ण

	len = response_get_u64(&dev->parsed, 4);
	अगर (size > len || offset > len - size) अणु
		pr_debug("Does not fit in the table (%llu vs. %llu)\n",
			  offset + size, len);
		वापस -ENOSPC;
	पूर्ण

	/* करो the actual transmission(s) */
	जबतक (off < size) अणु
		err = cmd_start(dev, uid, opalmethod[OPAL_SET]);
		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, OPAL_WHERE);
		add_token_u64(&err, dev, offset + off);
		add_token_u8(&err, dev, OPAL_ENDNAME);

		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, OPAL_VALUES);

		/*
		 * The bytestring header is either 1 or 2 bytes, so assume 2.
		 * There also needs to be enough space to accommodate the
		 * trailing OPAL_ENDNAME (1 byte) and tokens added by
		 * cmd_finalize.
		 */
		len = min(reमुख्यing_size(dev) - (2+1+CMD_FINALIZE_BYTES_NEEDED),
			  (माप_प्रकार)(size - off));
		pr_debug("Write bytes %zu+%llu/%llu\n", off, len, size);

		dst = add_bytestring_header(&err, dev, len);
		अगर (!dst)
			अवरोध;

		अगर (copy_from_user(dst, src + off, len)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		dev->pos += len;

		add_token_u8(&err, dev, OPAL_ENDNAME);
		अगर (err)
			अवरोध;

		err = finalize_and_send(dev, parse_and_check_status);
		अगर (err)
			अवरोध;

		off += len;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक generic_lr_enable_disable(काष्ठा opal_dev *dev,
				     u8 *uid, bool rle, bool wle,
				     bool rl, bool wl)
अणु
	पूर्णांक err;

	err = cmd_start(dev, uid, opalmethod[OPAL_SET]);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_VALUES);
	add_token_u8(&err, dev, OPAL_STARTLIST);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_READLOCKENABLED);
	add_token_u8(&err, dev, rle);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_WRITELOCKENABLED);
	add_token_u8(&err, dev, wle);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_READLOCKED);
	add_token_u8(&err, dev, rl);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_WRITELOCKED);
	add_token_u8(&err, dev, wl);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_ENDLIST);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक enable_global_lr(काष्ठा opal_dev *dev, u8 *uid,
				   काष्ठा opal_user_lr_setup *setup)
अणु
	पूर्णांक err;

	err = generic_lr_enable_disable(dev, uid, !!setup->RLE, !!setup->WLE,
					0, 0);
	अगर (err)
		pr_debug("Failed to create enable global lr command\n");

	वापस err;
पूर्ण

अटल पूर्णांक setup_locking_range(काष्ठा opal_dev *dev, व्योम *data)
अणु
	u8 uid[OPAL_UID_LENGTH];
	काष्ठा opal_user_lr_setup *setup = data;
	u8 lr;
	पूर्णांक err;

	lr = setup->session.opal_key.lr;
	err = build_locking_range(uid, माप(uid), lr);
	अगर (err)
		वापस err;

	अगर (lr == 0)
		err = enable_global_lr(dev, uid, setup);
	अन्यथा अणु
		err = cmd_start(dev, uid, opalmethod[OPAL_SET]);

		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, OPAL_VALUES);
		add_token_u8(&err, dev, OPAL_STARTLIST);

		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, OPAL_RANGESTART);
		add_token_u64(&err, dev, setup->range_start);
		add_token_u8(&err, dev, OPAL_ENDNAME);

		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, OPAL_RANGELENGTH);
		add_token_u64(&err, dev, setup->range_length);
		add_token_u8(&err, dev, OPAL_ENDNAME);

		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, OPAL_READLOCKENABLED);
		add_token_u64(&err, dev, !!setup->RLE);
		add_token_u8(&err, dev, OPAL_ENDNAME);

		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, OPAL_WRITELOCKENABLED);
		add_token_u64(&err, dev, !!setup->WLE);
		add_token_u8(&err, dev, OPAL_ENDNAME);

		add_token_u8(&err, dev, OPAL_ENDLIST);
		add_token_u8(&err, dev, OPAL_ENDNAME);
	पूर्ण
	अगर (err) अणु
		pr_debug("Error building Setup Locking range command.\n");
		वापस err;
	पूर्ण

	वापस finalize_and_send(dev, parse_and_check_status);
पूर्ण

अटल पूर्णांक start_generic_opal_session(काष्ठा opal_dev *dev,
				      क्रमागत opal_uid auth,
				      क्रमागत opal_uid sp_type,
				      स्थिर अक्षर *key,
				      u8 key_len)
अणु
	u32 hsn;
	पूर्णांक err;

	अगर (key == शून्य && auth != OPAL_ANYBODY_UID)
		वापस OPAL_INVAL_PARAM;

	hsn = GENERIC_HOST_SESSION_NUM;
	err = cmd_start(dev, opaluid[OPAL_SMUID_UID],
			opalmethod[OPAL_STARTSESSION]);

	add_token_u64(&err, dev, hsn);
	add_token_bytestring(&err, dev, opaluid[sp_type], OPAL_UID_LENGTH);
	add_token_u8(&err, dev, 1);

	चयन (auth) अणु
	हाल OPAL_ANYBODY_UID:
		अवरोध;
	हाल OPAL_ADMIN1_UID:
	हाल OPAL_SID_UID:
	हाल OPAL_PSID_UID:
		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, 0); /* HostChallenge */
		add_token_bytestring(&err, dev, key, key_len);
		add_token_u8(&err, dev, OPAL_ENDNAME);
		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, 3); /* HostSignAuth */
		add_token_bytestring(&err, dev, opaluid[auth],
				     OPAL_UID_LENGTH);
		add_token_u8(&err, dev, OPAL_ENDNAME);
		अवरोध;
	शेष:
		pr_debug("Cannot start Admin SP session with auth %d\n", auth);
		वापस OPAL_INVAL_PARAM;
	पूर्ण

	अगर (err) अणु
		pr_debug("Error building start adminsp session command.\n");
		वापस err;
	पूर्ण

	वापस finalize_and_send(dev, start_opal_session_cont);
पूर्ण

अटल पूर्णांक start_anybodyASP_opal_session(काष्ठा opal_dev *dev, व्योम *data)
अणु
	वापस start_generic_opal_session(dev, OPAL_ANYBODY_UID,
					  OPAL_ADMINSP_UID, शून्य, 0);
पूर्ण

अटल पूर्णांक start_SIDASP_opal_session(काष्ठा opal_dev *dev, व्योम *data)
अणु
	पूर्णांक ret;
	स्थिर u8 *key = dev->prev_data;

	अगर (!key) अणु
		स्थिर काष्ठा opal_key *okey = data;

		ret = start_generic_opal_session(dev, OPAL_SID_UID,
						 OPAL_ADMINSP_UID,
						 okey->key,
						 okey->key_len);
	पूर्ण अन्यथा अणु
		ret = start_generic_opal_session(dev, OPAL_SID_UID,
						 OPAL_ADMINSP_UID,
						 key, dev->prev_d_len);
		kमुक्त(key);
		dev->prev_data = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक start_admin1LSP_opal_session(काष्ठा opal_dev *dev, व्योम *data)
अणु
	काष्ठा opal_key *key = data;

	वापस start_generic_opal_session(dev, OPAL_ADMIN1_UID,
					  OPAL_LOCKINGSP_UID,
					  key->key, key->key_len);
पूर्ण

अटल पूर्णांक start_PSID_opal_session(काष्ठा opal_dev *dev, व्योम *data)
अणु
	स्थिर काष्ठा opal_key *okey = data;

	वापस start_generic_opal_session(dev, OPAL_PSID_UID,
					  OPAL_ADMINSP_UID,
					  okey->key,
					  okey->key_len);
पूर्ण

अटल पूर्णांक start_auth_opal_session(काष्ठा opal_dev *dev, व्योम *data)
अणु
	काष्ठा opal_session_info *session = data;
	u8 lk_ul_user[OPAL_UID_LENGTH];
	माप_प्रकार keylen = session->opal_key.key_len;
	पूर्णांक err = 0;

	u8 *key = session->opal_key.key;
	u32 hsn = GENERIC_HOST_SESSION_NUM;

	अगर (session->sum)
		err = build_locking_user(lk_ul_user, माप(lk_ul_user),
					 session->opal_key.lr);
	अन्यथा अगर (session->who != OPAL_ADMIN1 && !session->sum)
		err = build_locking_user(lk_ul_user, माप(lk_ul_user),
					 session->who - 1);
	अन्यथा
		स_नकल(lk_ul_user, opaluid[OPAL_ADMIN1_UID], OPAL_UID_LENGTH);

	अगर (err)
		वापस err;

	err = cmd_start(dev, opaluid[OPAL_SMUID_UID],
			opalmethod[OPAL_STARTSESSION]);

	add_token_u64(&err, dev, hsn);
	add_token_bytestring(&err, dev, opaluid[OPAL_LOCKINGSP_UID],
			     OPAL_UID_LENGTH);
	add_token_u8(&err, dev, 1);
	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, 0);
	add_token_bytestring(&err, dev, key, keylen);
	add_token_u8(&err, dev, OPAL_ENDNAME);
	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, 3);
	add_token_bytestring(&err, dev, lk_ul_user, OPAL_UID_LENGTH);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	अगर (err) अणु
		pr_debug("Error building STARTSESSION command.\n");
		वापस err;
	पूर्ण

	वापस finalize_and_send(dev, start_opal_session_cont);
पूर्ण

अटल पूर्णांक revert_tper(काष्ठा opal_dev *dev, व्योम *data)
अणु
	पूर्णांक err;

	err = cmd_start(dev, opaluid[OPAL_ADMINSP_UID],
			opalmethod[OPAL_REVERT]);
	अगर (err) अणु
		pr_debug("Error building REVERT TPER command.\n");
		वापस err;
	पूर्ण

	वापस finalize_and_send(dev, parse_and_check_status);
पूर्ण

अटल पूर्णांक पूर्णांकernal_activate_user(काष्ठा opal_dev *dev, व्योम *data)
अणु
	काष्ठा opal_session_info *session = data;
	u8 uid[OPAL_UID_LENGTH];
	पूर्णांक err;

	स_नकल(uid, opaluid[OPAL_USER1_UID], OPAL_UID_LENGTH);
	uid[7] = session->who;

	err = cmd_start(dev, uid, opalmethod[OPAL_SET]);
	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_VALUES);
	add_token_u8(&err, dev, OPAL_STARTLIST);
	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, 5); /* Enabled */
	add_token_u8(&err, dev, OPAL_TRUE);
	add_token_u8(&err, dev, OPAL_ENDNAME);
	add_token_u8(&err, dev, OPAL_ENDLIST);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	अगर (err) अणु
		pr_debug("Error building Activate UserN command.\n");
		वापस err;
	पूर्ण

	वापस finalize_and_send(dev, parse_and_check_status);
पूर्ण

अटल पूर्णांक erase_locking_range(काष्ठा opal_dev *dev, व्योम *data)
अणु
	काष्ठा opal_session_info *session = data;
	u8 uid[OPAL_UID_LENGTH];
	पूर्णांक err;

	अगर (build_locking_range(uid, माप(uid), session->opal_key.lr) < 0)
		वापस -दुस्फल;

	err = cmd_start(dev, uid, opalmethod[OPAL_ERASE]);

	अगर (err) अणु
		pr_debug("Error building Erase Locking Range Command.\n");
		वापस err;
	पूर्ण

	वापस finalize_and_send(dev, parse_and_check_status);
पूर्ण

अटल पूर्णांक set_mbr_करोne(काष्ठा opal_dev *dev, व्योम *data)
अणु
	u8 *mbr_करोne_tf = data;
	पूर्णांक err;

	err = cmd_start(dev, opaluid[OPAL_MBRCONTROL],
			opalmethod[OPAL_SET]);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_VALUES);
	add_token_u8(&err, dev, OPAL_STARTLIST);
	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_MBRDONE);
	add_token_u8(&err, dev, *mbr_करोne_tf); /* Done T or F */
	add_token_u8(&err, dev, OPAL_ENDNAME);
	add_token_u8(&err, dev, OPAL_ENDLIST);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	अगर (err) अणु
		pr_debug("Error Building set MBR Done command\n");
		वापस err;
	पूर्ण

	वापस finalize_and_send(dev, parse_and_check_status);
पूर्ण

अटल पूर्णांक set_mbr_enable_disable(काष्ठा opal_dev *dev, व्योम *data)
अणु
	u8 *mbr_en_dis = data;
	पूर्णांक err;

	err = cmd_start(dev, opaluid[OPAL_MBRCONTROL],
			opalmethod[OPAL_SET]);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_VALUES);
	add_token_u8(&err, dev, OPAL_STARTLIST);
	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_MBRENABLE);
	add_token_u8(&err, dev, *mbr_en_dis);
	add_token_u8(&err, dev, OPAL_ENDNAME);
	add_token_u8(&err, dev, OPAL_ENDLIST);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	अगर (err) अणु
		pr_debug("Error Building set MBR done command\n");
		वापस err;
	पूर्ण

	वापस finalize_and_send(dev, parse_and_check_status);
पूर्ण

अटल पूर्णांक ग_लिखो_shaकरोw_mbr(काष्ठा opal_dev *dev, व्योम *data)
अणु
	काष्ठा opal_shaकरोw_mbr *shaकरोw = data;

	वापस generic_table_ग_लिखो_data(dev, shaकरोw->data, shaकरोw->offset,
					shaकरोw->size, opaluid[OPAL_MBR]);
पूर्ण

अटल पूर्णांक generic_pw_cmd(u8 *key, माप_प्रकार key_len, u8 *cpin_uid,
			  काष्ठा opal_dev *dev)
अणु
	पूर्णांक err;

	err = cmd_start(dev, cpin_uid, opalmethod[OPAL_SET]);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_VALUES);
	add_token_u8(&err, dev, OPAL_STARTLIST);
	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_PIN);
	add_token_bytestring(&err, dev, key, key_len);
	add_token_u8(&err, dev, OPAL_ENDNAME);
	add_token_u8(&err, dev, OPAL_ENDLIST);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	वापस err;
पूर्ण

अटल पूर्णांक set_new_pw(काष्ठा opal_dev *dev, व्योम *data)
अणु
	u8 cpin_uid[OPAL_UID_LENGTH];
	काष्ठा opal_session_info *usr = data;

	स_नकल(cpin_uid, opaluid[OPAL_C_PIN_ADMIN1], OPAL_UID_LENGTH);

	अगर (usr->who != OPAL_ADMIN1) अणु
		cpin_uid[5] = 0x03;
		अगर (usr->sum)
			cpin_uid[7] = usr->opal_key.lr + 1;
		अन्यथा
			cpin_uid[7] = usr->who;
	पूर्ण

	अगर (generic_pw_cmd(usr->opal_key.key, usr->opal_key.key_len,
			   cpin_uid, dev)) अणु
		pr_debug("Error building set password command.\n");
		वापस -दुस्फल;
	पूर्ण

	वापस finalize_and_send(dev, parse_and_check_status);
पूर्ण

अटल पूर्णांक set_sid_cpin_pin(काष्ठा opal_dev *dev, व्योम *data)
अणु
	u8 cpin_uid[OPAL_UID_LENGTH];
	काष्ठा opal_key *key = data;

	स_नकल(cpin_uid, opaluid[OPAL_C_PIN_SID], OPAL_UID_LENGTH);

	अगर (generic_pw_cmd(key->key, key->key_len, cpin_uid, dev)) अणु
		pr_debug("Error building Set SID cpin\n");
		वापस -दुस्फल;
	पूर्ण
	वापस finalize_and_send(dev, parse_and_check_status);
पूर्ण

अटल पूर्णांक add_user_to_lr(काष्ठा opal_dev *dev, व्योम *data)
अणु
	u8 lr_buffer[OPAL_UID_LENGTH];
	u8 user_uid[OPAL_UID_LENGTH];
	काष्ठा opal_lock_unlock *lkul = data;
	पूर्णांक err;

	स_नकल(lr_buffer, opaluid[OPAL_LOCKINGRANGE_ACE_RDLOCKED],
	       OPAL_UID_LENGTH);

	अगर (lkul->l_state == OPAL_RW)
		स_नकल(lr_buffer, opaluid[OPAL_LOCKINGRANGE_ACE_WRLOCKED],
		       OPAL_UID_LENGTH);

	lr_buffer[7] = lkul->session.opal_key.lr;

	स_नकल(user_uid, opaluid[OPAL_USER1_UID], OPAL_UID_LENGTH);

	user_uid[7] = lkul->session.who;

	err = cmd_start(dev, lr_buffer, opalmethod[OPAL_SET]);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_VALUES);

	add_token_u8(&err, dev, OPAL_STARTLIST);
	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, 3);

	add_token_u8(&err, dev, OPAL_STARTLIST);


	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_bytestring(&err, dev,
			     opaluid[OPAL_HALF_UID_AUTHORITY_OBJ_REF],
			     OPAL_UID_LENGTH/2);
	add_token_bytestring(&err, dev, user_uid, OPAL_UID_LENGTH);
	add_token_u8(&err, dev, OPAL_ENDNAME);


	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_bytestring(&err, dev,
			     opaluid[OPAL_HALF_UID_AUTHORITY_OBJ_REF],
			     OPAL_UID_LENGTH/2);
	add_token_bytestring(&err, dev, user_uid, OPAL_UID_LENGTH);
	add_token_u8(&err, dev, OPAL_ENDNAME);


	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_bytestring(&err, dev, opaluid[OPAL_HALF_UID_BOOLEAN_ACE],
			     OPAL_UID_LENGTH/2);
	add_token_u8(&err, dev, 1);
	add_token_u8(&err, dev, OPAL_ENDNAME);


	add_token_u8(&err, dev, OPAL_ENDLIST);
	add_token_u8(&err, dev, OPAL_ENDNAME);
	add_token_u8(&err, dev, OPAL_ENDLIST);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	अगर (err) अणु
		pr_debug("Error building add user to locking range command.\n");
		वापस err;
	पूर्ण

	वापस finalize_and_send(dev, parse_and_check_status);
पूर्ण

अटल पूर्णांक lock_unlock_locking_range(काष्ठा opal_dev *dev, व्योम *data)
अणु
	u8 lr_buffer[OPAL_UID_LENGTH];
	काष्ठा opal_lock_unlock *lkul = data;
	u8 पढ़ो_locked = 1, ग_लिखो_locked = 1;
	पूर्णांक err = 0;

	अगर (build_locking_range(lr_buffer, माप(lr_buffer),
				lkul->session.opal_key.lr) < 0)
		वापस -दुस्फल;

	चयन (lkul->l_state) अणु
	हाल OPAL_RO:
		पढ़ो_locked = 0;
		ग_लिखो_locked = 1;
		अवरोध;
	हाल OPAL_RW:
		पढ़ो_locked = 0;
		ग_लिखो_locked = 0;
		अवरोध;
	हाल OPAL_LK:
		/* vars are initialized to locked */
		अवरोध;
	शेष:
		pr_debug("Tried to set an invalid locking state... returning to uland\n");
		वापस OPAL_INVAL_PARAM;
	पूर्ण

	err = cmd_start(dev, lr_buffer, opalmethod[OPAL_SET]);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_VALUES);
	add_token_u8(&err, dev, OPAL_STARTLIST);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_READLOCKED);
	add_token_u8(&err, dev, पढ़ो_locked);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_WRITELOCKED);
	add_token_u8(&err, dev, ग_लिखो_locked);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_ENDLIST);
	add_token_u8(&err, dev, OPAL_ENDNAME);

	अगर (err) अणु
		pr_debug("Error building SET command.\n");
		वापस err;
	पूर्ण

	वापस finalize_and_send(dev, parse_and_check_status);
पूर्ण


अटल पूर्णांक lock_unlock_locking_range_sum(काष्ठा opal_dev *dev, व्योम *data)
अणु
	u8 lr_buffer[OPAL_UID_LENGTH];
	u8 पढ़ो_locked = 1, ग_लिखो_locked = 1;
	काष्ठा opal_lock_unlock *lkul = data;
	पूर्णांक ret;

	clear_opal_cmd(dev);
	set_comid(dev, dev->comid);

	अगर (build_locking_range(lr_buffer, माप(lr_buffer),
				lkul->session.opal_key.lr) < 0)
		वापस -दुस्फल;

	चयन (lkul->l_state) अणु
	हाल OPAL_RO:
		पढ़ो_locked = 0;
		ग_लिखो_locked = 1;
		अवरोध;
	हाल OPAL_RW:
		पढ़ो_locked = 0;
		ग_लिखो_locked = 0;
		अवरोध;
	हाल OPAL_LK:
		/* vars are initialized to locked */
		अवरोध;
	शेष:
		pr_debug("Tried to set an invalid locking state.\n");
		वापस OPAL_INVAL_PARAM;
	पूर्ण
	ret = generic_lr_enable_disable(dev, lr_buffer, 1, 1,
					पढ़ो_locked, ग_लिखो_locked);

	अगर (ret < 0) अणु
		pr_debug("Error building SET command.\n");
		वापस ret;
	पूर्ण

	वापस finalize_and_send(dev, parse_and_check_status);
पूर्ण

अटल पूर्णांक activate_lsp(काष्ठा opal_dev *dev, व्योम *data)
अणु
	काष्ठा opal_lr_act *opal_act = data;
	u8 user_lr[OPAL_UID_LENGTH];
	पूर्णांक err, i;

	err = cmd_start(dev, opaluid[OPAL_LOCKINGSP_UID],
			opalmethod[OPAL_ACTIVATE]);

	अगर (opal_act->sum) अणु
		err = build_locking_range(user_lr, माप(user_lr),
					  opal_act->lr[0]);
		अगर (err)
			वापस err;

		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u64(&err, dev, OPAL_SUM_SET_LIST);

		add_token_u8(&err, dev, OPAL_STARTLIST);
		add_token_bytestring(&err, dev, user_lr, OPAL_UID_LENGTH);
		क्रम (i = 1; i < opal_act->num_lrs; i++) अणु
			user_lr[7] = opal_act->lr[i];
			add_token_bytestring(&err, dev, user_lr, OPAL_UID_LENGTH);
		पूर्ण
		add_token_u8(&err, dev, OPAL_ENDLIST);
		add_token_u8(&err, dev, OPAL_ENDNAME);
	पूर्ण

	अगर (err) अणु
		pr_debug("Error building Activate LockingSP command.\n");
		वापस err;
	पूर्ण

	वापस finalize_and_send(dev, parse_and_check_status);
पूर्ण

/* Determine अगर we're in the Manufactured Inactive or Active state */
अटल पूर्णांक get_lsp_lअगरecycle(काष्ठा opal_dev *dev, व्योम *data)
अणु
	u8 lc_status;
	पूर्णांक err;

	err = generic_get_column(dev, opaluid[OPAL_LOCKINGSP_UID],
				 OPAL_LIFECYCLE);
	अगर (err)
		वापस err;

	lc_status = response_get_u64(&dev->parsed, 4);
	/* 0x08 is Manufactured Inactive */
	/* 0x09 is Manufactured */
	अगर (lc_status != OPAL_MANUFACTURED_INACTIVE) अणु
		pr_debug("Couldn't determine the status of the Lifecycle state\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_msid_cpin_pin(काष्ठा opal_dev *dev, व्योम *data)
अणु
	स्थिर अक्षर *msid_pin;
	माप_प्रकार म_माप;
	पूर्णांक err;

	err = generic_get_column(dev, opaluid[OPAL_C_PIN_MSID], OPAL_PIN);
	अगर (err)
		वापस err;

	म_माप = response_get_string(&dev->parsed, 4, &msid_pin);
	अगर (!msid_pin) अणु
		pr_debug("Couldn't extract MSID_CPIN from response\n");
		वापस OPAL_INVAL_PARAM;
	पूर्ण

	dev->prev_data = kmemdup(msid_pin, म_माप, GFP_KERNEL);
	अगर (!dev->prev_data)
		वापस -ENOMEM;

	dev->prev_d_len = म_माप;

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_table_data(काष्ठा opal_dev *dev, व्योम *data)
अणु
	काष्ठा opal_पढ़ो_ग_लिखो_table *ग_लिखो_tbl = data;

	वापस generic_table_ग_लिखो_data(dev, ग_लिखो_tbl->data, ग_लिखो_tbl->offset,
					ग_लिखो_tbl->size, ग_लिखो_tbl->table_uid);
पूर्ण

अटल पूर्णांक पढ़ो_table_data_cont(काष्ठा opal_dev *dev)
अणु
	पूर्णांक err;
	स्थिर अक्षर *data_पढ़ो;

	err = parse_and_check_status(dev);
	अगर (err)
		वापस err;

	dev->prev_d_len = response_get_string(&dev->parsed, 1, &data_पढ़ो);
	dev->prev_data = (व्योम *)data_पढ़ो;
	अगर (!dev->prev_data) अणु
		pr_debug("%s: Couldn't read data from the table.\n", __func__);
		वापस OPAL_INVAL_PARAM;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * IO_BUFFER_LENGTH = 2048
 * माप(header) = 56
 * No. of Token Bytes in the Response = 11
 * MAX size of data that can be carried in response buffer
 * at a समय is : 2048 - (56 + 11) = 1981 = 0x7BD.
 */
#घोषणा OPAL_MAX_READ_TABLE (0x7BD)

अटल पूर्णांक पढ़ो_table_data(काष्ठा opal_dev *dev, व्योम *data)
अणु
	काष्ठा opal_पढ़ो_ग_लिखो_table *पढ़ो_tbl = data;
	पूर्णांक err;
	माप_प्रकार off = 0, max_पढ़ो_size = OPAL_MAX_READ_TABLE;
	u64 table_len, len;
	u64 offset = पढ़ो_tbl->offset, पढ़ो_size = पढ़ो_tbl->size - 1;
	u8 __user *dst;

	err = generic_get_table_info(dev, पढ़ो_tbl->table_uid, OPAL_TABLE_ROWS);
	अगर (err) अणु
		pr_debug("Couldn't get the table size\n");
		वापस err;
	पूर्ण

	table_len = response_get_u64(&dev->parsed, 4);

	/* Check अगर the user is trying to पढ़ो from the table limits */
	अगर (पढ़ो_size > table_len || offset > table_len - पढ़ो_size) अणु
		pr_debug("Read size exceeds the Table size limits (%llu vs. %llu)\n",
			  offset + पढ़ो_size, table_len);
		वापस -EINVAL;
	पूर्ण

	जबतक (off < पढ़ो_size) अणु
		err = cmd_start(dev, पढ़ो_tbl->table_uid, opalmethod[OPAL_GET]);

		add_token_u8(&err, dev, OPAL_STARTLIST);
		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, OPAL_STARTROW);
		add_token_u64(&err, dev, offset + off); /* start row value */
		add_token_u8(&err, dev, OPAL_ENDNAME);

		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, OPAL_ENDROW);

		len = min(max_पढ़ो_size, (माप_प्रकार)(पढ़ो_size - off));
		add_token_u64(&err, dev, offset + off + len); /* end row value
							       */
		add_token_u8(&err, dev, OPAL_ENDNAME);
		add_token_u8(&err, dev, OPAL_ENDLIST);

		अगर (err) अणु
			pr_debug("Error building read table data command.\n");
			अवरोध;
		पूर्ण

		err = finalize_and_send(dev, पढ़ो_table_data_cont);
		अगर (err)
			अवरोध;

		/* len+1: This includes the शून्य terminator at the end*/
		अगर (dev->prev_d_len > len + 1) अणु
			err = -EOVERFLOW;
			अवरोध;
		पूर्ण

		dst = (u8 __user *)(uपूर्णांकptr_t)पढ़ो_tbl->data;
		अगर (copy_to_user(dst + off, dev->prev_data, dev->prev_d_len)) अणु
			pr_debug("Error copying data to userspace\n");
			err = -EFAULT;
			अवरोध;
		पूर्ण
		dev->prev_data = शून्य;

		off += len;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक end_opal_session(काष्ठा opal_dev *dev, व्योम *data)
अणु
	पूर्णांक err = 0;

	clear_opal_cmd(dev);
	set_comid(dev, dev->comid);
	add_token_u8(&err, dev, OPAL_ENDOFSESSION);

	अगर (err < 0)
		वापस err;

	वापस finalize_and_send(dev, end_session_cont);
पूर्ण

अटल पूर्णांक end_opal_session_error(काष्ठा opal_dev *dev)
अणु
	स्थिर काष्ठा opal_step error_end_session = अणु
		end_opal_session,
	पूर्ण;

	वापस execute_step(dev, &error_end_session, 0);
पूर्ण

अटल अंतरभूत व्योम setup_opal_dev(काष्ठा opal_dev *dev)
अणु
	dev->tsn = 0;
	dev->hsn = 0;
	dev->prev_data = शून्य;
पूर्ण

अटल पूर्णांक check_opal_support(काष्ठा opal_dev *dev)
अणु
	पूर्णांक ret;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = opal_discovery0_step(dev);
	dev->supported = !ret;
	mutex_unlock(&dev->dev_lock);

	वापस ret;
पूर्ण

अटल व्योम clean_opal_dev(काष्ठा opal_dev *dev)
अणु

	काष्ठा opal_suspend_data *suspend, *next;

	mutex_lock(&dev->dev_lock);
	list_क्रम_each_entry_safe(suspend, next, &dev->unlk_lst, node) अणु
		list_del(&suspend->node);
		kमुक्त(suspend);
	पूर्ण
	mutex_unlock(&dev->dev_lock);
पूर्ण

व्योम मुक्त_opal_dev(काष्ठा opal_dev *dev)
अणु
	अगर (!dev)
		वापस;

	clean_opal_dev(dev);
	kमुक्त(dev);
पूर्ण
EXPORT_SYMBOL(मुक्त_opal_dev);

काष्ठा opal_dev *init_opal_dev(व्योम *data, sec_send_recv *send_recv)
अणु
	काष्ठा opal_dev *dev;

	dev = kदो_स्मृति(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	INIT_LIST_HEAD(&dev->unlk_lst);
	mutex_init(&dev->dev_lock);
	dev->data = data;
	dev->send_recv = send_recv;
	अगर (check_opal_support(dev) != 0) अणु
		pr_debug("Opal is not supported on this device\n");
		kमुक्त(dev);
		वापस शून्य;
	पूर्ण

	वापस dev;
पूर्ण
EXPORT_SYMBOL(init_opal_dev);

अटल पूर्णांक opal_secure_erase_locking_range(काष्ठा opal_dev *dev,
					   काष्ठा opal_session_info *opal_session)
अणु
	स्थिर काष्ठा opal_step erase_steps[] = अणु
		अणु start_auth_opal_session, opal_session पूर्ण,
		अणु get_active_key, &opal_session->opal_key.lr पूर्ण,
		अणु gen_key, पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;
	पूर्णांक ret;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = execute_steps(dev, erase_steps, ARRAY_SIZE(erase_steps));
	mutex_unlock(&dev->dev_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक opal_erase_locking_range(काष्ठा opal_dev *dev,
				    काष्ठा opal_session_info *opal_session)
अणु
	स्थिर काष्ठा opal_step erase_steps[] = अणु
		अणु start_auth_opal_session, opal_session पूर्ण,
		अणु erase_locking_range, opal_session पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;
	पूर्णांक ret;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = execute_steps(dev, erase_steps, ARRAY_SIZE(erase_steps));
	mutex_unlock(&dev->dev_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक opal_enable_disable_shaकरोw_mbr(काष्ठा opal_dev *dev,
					  काष्ठा opal_mbr_data *opal_mbr)
अणु
	u8 enable_disable = opal_mbr->enable_disable == OPAL_MBR_ENABLE ?
		OPAL_TRUE : OPAL_FALSE;

	स्थिर काष्ठा opal_step mbr_steps[] = अणु
		अणु start_admin1LSP_opal_session, &opal_mbr->key पूर्ण,
		अणु set_mbr_करोne, &enable_disable पूर्ण,
		अणु end_opal_session, पूर्ण,
		अणु start_admin1LSP_opal_session, &opal_mbr->key पूर्ण,
		अणु set_mbr_enable_disable, &enable_disable पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;
	पूर्णांक ret;

	अगर (opal_mbr->enable_disable != OPAL_MBR_ENABLE &&
	    opal_mbr->enable_disable != OPAL_MBR_DISABLE)
		वापस -EINVAL;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = execute_steps(dev, mbr_steps, ARRAY_SIZE(mbr_steps));
	mutex_unlock(&dev->dev_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक opal_set_mbr_करोne(काष्ठा opal_dev *dev,
			     काष्ठा opal_mbr_करोne *mbr_करोne)
अणु
	u8 mbr_करोne_tf = mbr_करोne->करोne_flag == OPAL_MBR_DONE ?
		OPAL_TRUE : OPAL_FALSE;

	स्थिर काष्ठा opal_step mbr_steps[] = अणु
		अणु start_admin1LSP_opal_session, &mbr_करोne->key पूर्ण,
		अणु set_mbr_करोne, &mbr_करोne_tf पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;
	पूर्णांक ret;

	अगर (mbr_करोne->करोne_flag != OPAL_MBR_DONE &&
	    mbr_करोne->करोne_flag != OPAL_MBR_NOT_DONE)
		वापस -EINVAL;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = execute_steps(dev, mbr_steps, ARRAY_SIZE(mbr_steps));
	mutex_unlock(&dev->dev_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक opal_ग_लिखो_shaकरोw_mbr(काष्ठा opal_dev *dev,
				 काष्ठा opal_shaकरोw_mbr *info)
अणु
	स्थिर काष्ठा opal_step mbr_steps[] = अणु
		अणु start_admin1LSP_opal_session, &info->key पूर्ण,
		अणु ग_लिखो_shaकरोw_mbr, info पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;
	पूर्णांक ret;

	अगर (info->size == 0)
		वापस 0;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = execute_steps(dev, mbr_steps, ARRAY_SIZE(mbr_steps));
	mutex_unlock(&dev->dev_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक opal_save(काष्ठा opal_dev *dev, काष्ठा opal_lock_unlock *lk_unlk)
अणु
	काष्ठा opal_suspend_data *suspend;

	suspend = kzalloc(माप(*suspend), GFP_KERNEL);
	अगर (!suspend)
		वापस -ENOMEM;

	suspend->unlk = *lk_unlk;
	suspend->lr = lk_unlk->session.opal_key.lr;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	add_suspend_info(dev, suspend);
	mutex_unlock(&dev->dev_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक opal_add_user_to_lr(काष्ठा opal_dev *dev,
			       काष्ठा opal_lock_unlock *lk_unlk)
अणु
	स्थिर काष्ठा opal_step steps[] = अणु
		अणु start_admin1LSP_opal_session, &lk_unlk->session.opal_key पूर्ण,
		अणु add_user_to_lr, lk_unlk पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;
	पूर्णांक ret;

	अगर (lk_unlk->l_state != OPAL_RO &&
	    lk_unlk->l_state != OPAL_RW) अणु
		pr_debug("Locking state was not RO or RW\n");
		वापस -EINVAL;
	पूर्ण

	अगर (lk_unlk->session.who < OPAL_USER1 ||
	    lk_unlk->session.who > OPAL_USER9) अणु
		pr_debug("Authority was not within the range of users: %d\n",
			 lk_unlk->session.who);
		वापस -EINVAL;
	पूर्ण

	अगर (lk_unlk->session.sum) अणु
		pr_debug("%s not supported in sum. Use setup locking range\n",
			 __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = execute_steps(dev, steps, ARRAY_SIZE(steps));
	mutex_unlock(&dev->dev_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक opal_reverttper(काष्ठा opal_dev *dev, काष्ठा opal_key *opal, bool psid)
अणु
	/* controller will terminate session */
	स्थिर काष्ठा opal_step revert_steps[] = अणु
		अणु start_SIDASP_opal_session, opal पूर्ण,
		अणु revert_tper, पूर्ण
	पूर्ण;
	स्थिर काष्ठा opal_step psid_revert_steps[] = अणु
		अणु start_PSID_opal_session, opal पूर्ण,
		अणु revert_tper, पूर्ण
	पूर्ण;

	पूर्णांक ret;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	अगर (psid)
		ret = execute_steps(dev, psid_revert_steps,
				    ARRAY_SIZE(psid_revert_steps));
	अन्यथा
		ret = execute_steps(dev, revert_steps,
				    ARRAY_SIZE(revert_steps));
	mutex_unlock(&dev->dev_lock);

	/*
	 * If we successfully reverted lets clean
	 * any saved locking ranges.
	 */
	अगर (!ret)
		clean_opal_dev(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक __opal_lock_unlock(काष्ठा opal_dev *dev,
			      काष्ठा opal_lock_unlock *lk_unlk)
अणु
	स्थिर काष्ठा opal_step unlock_steps[] = अणु
		अणु start_auth_opal_session, &lk_unlk->session पूर्ण,
		अणु lock_unlock_locking_range, lk_unlk पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;
	स्थिर काष्ठा opal_step unlock_sum_steps[] = अणु
		अणु start_auth_opal_session, &lk_unlk->session पूर्ण,
		अणु lock_unlock_locking_range_sum, lk_unlk पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;

	अगर (lk_unlk->session.sum)
		वापस execute_steps(dev, unlock_sum_steps,
				     ARRAY_SIZE(unlock_sum_steps));
	अन्यथा
		वापस execute_steps(dev, unlock_steps,
				     ARRAY_SIZE(unlock_steps));
पूर्ण

अटल पूर्णांक __opal_set_mbr_करोne(काष्ठा opal_dev *dev, काष्ठा opal_key *key)
अणु
	u8 mbr_करोne_tf = OPAL_TRUE;
	स्थिर काष्ठा opal_step mbrकरोne_step[] = अणु
		अणु start_admin1LSP_opal_session, key पूर्ण,
		अणु set_mbr_करोne, &mbr_करोne_tf पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;

	वापस execute_steps(dev, mbrकरोne_step, ARRAY_SIZE(mbrकरोne_step));
पूर्ण

अटल पूर्णांक opal_lock_unlock(काष्ठा opal_dev *dev,
			    काष्ठा opal_lock_unlock *lk_unlk)
अणु
	पूर्णांक ret;

	अगर (lk_unlk->session.who > OPAL_USER9)
		वापस -EINVAL;

	mutex_lock(&dev->dev_lock);
	ret = __opal_lock_unlock(dev, lk_unlk);
	mutex_unlock(&dev->dev_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक opal_take_ownership(काष्ठा opal_dev *dev, काष्ठा opal_key *opal)
अणु
	स्थिर काष्ठा opal_step owner_steps[] = अणु
		अणु start_anybodyASP_opal_session, पूर्ण,
		अणु get_msid_cpin_pin, पूर्ण,
		अणु end_opal_session, पूर्ण,
		अणु start_SIDASP_opal_session, opal पूर्ण,
		अणु set_sid_cpin_pin, opal पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;
	पूर्णांक ret;

	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = execute_steps(dev, owner_steps, ARRAY_SIZE(owner_steps));
	mutex_unlock(&dev->dev_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक opal_activate_lsp(काष्ठा opal_dev *dev,
			     काष्ठा opal_lr_act *opal_lr_act)
अणु
	स्थिर काष्ठा opal_step active_steps[] = अणु
		अणु start_SIDASP_opal_session, &opal_lr_act->key पूर्ण,
		अणु get_lsp_lअगरecycle, पूर्ण,
		अणु activate_lsp, opal_lr_act पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;
	पूर्णांक ret;

	अगर (!opal_lr_act->num_lrs || opal_lr_act->num_lrs > OPAL_MAX_LRS)
		वापस -EINVAL;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = execute_steps(dev, active_steps, ARRAY_SIZE(active_steps));
	mutex_unlock(&dev->dev_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक opal_setup_locking_range(काष्ठा opal_dev *dev,
				    काष्ठा opal_user_lr_setup *opal_lrs)
अणु
	स्थिर काष्ठा opal_step lr_steps[] = अणु
		अणु start_auth_opal_session, &opal_lrs->session पूर्ण,
		अणु setup_locking_range, opal_lrs पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;
	पूर्णांक ret;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = execute_steps(dev, lr_steps, ARRAY_SIZE(lr_steps));
	mutex_unlock(&dev->dev_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक opal_set_new_pw(काष्ठा opal_dev *dev, काष्ठा opal_new_pw *opal_pw)
अणु
	स्थिर काष्ठा opal_step pw_steps[] = अणु
		अणु start_auth_opal_session, &opal_pw->session पूर्ण,
		अणु set_new_pw, &opal_pw->new_user_pw पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;
	पूर्णांक ret;

	अगर (opal_pw->session.who > OPAL_USER9  ||
	    opal_pw->new_user_pw.who > OPAL_USER9)
		वापस -EINVAL;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = execute_steps(dev, pw_steps, ARRAY_SIZE(pw_steps));
	mutex_unlock(&dev->dev_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक opal_activate_user(काष्ठा opal_dev *dev,
			      काष्ठा opal_session_info *opal_session)
अणु
	स्थिर काष्ठा opal_step act_steps[] = अणु
		अणु start_admin1LSP_opal_session, &opal_session->opal_key पूर्ण,
		अणु पूर्णांकernal_activate_user, opal_session पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;
	पूर्णांक ret;

	/* We can't activate Admin1 it's active as manufactured */
	अगर (opal_session->who < OPAL_USER1 ||
	    opal_session->who > OPAL_USER9) अणु
		pr_debug("Who was not a valid user: %d\n", opal_session->who);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);
	ret = execute_steps(dev, act_steps, ARRAY_SIZE(act_steps));
	mutex_unlock(&dev->dev_lock);

	वापस ret;
पूर्ण

bool opal_unlock_from_suspend(काष्ठा opal_dev *dev)
अणु
	काष्ठा opal_suspend_data *suspend;
	bool was_failure = false;
	पूर्णांक ret = 0;

	अगर (!dev)
		वापस false;

	अगर (!dev->supported)
		वापस false;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);

	list_क्रम_each_entry(suspend, &dev->unlk_lst, node) अणु
		dev->tsn = 0;
		dev->hsn = 0;

		ret = __opal_lock_unlock(dev, &suspend->unlk);
		अगर (ret) अणु
			pr_debug("Failed to unlock LR %hhu with sum %d\n",
				 suspend->unlk.session.opal_key.lr,
				 suspend->unlk.session.sum);
			was_failure = true;
		पूर्ण

		अगर (dev->mbr_enabled) अणु
			ret = __opal_set_mbr_करोne(dev, &suspend->unlk.session.opal_key);
			अगर (ret)
				pr_debug("Failed to set MBR Done in S3 resume\n");
		पूर्ण
	पूर्ण
	mutex_unlock(&dev->dev_lock);

	वापस was_failure;
पूर्ण
EXPORT_SYMBOL(opal_unlock_from_suspend);

अटल पूर्णांक opal_पढ़ो_table(काष्ठा opal_dev *dev,
			   काष्ठा opal_पढ़ो_ग_लिखो_table *rw_tbl)
अणु
	स्थिर काष्ठा opal_step पढ़ो_table_steps[] = अणु
		अणु start_admin1LSP_opal_session, &rw_tbl->key पूर्ण,
		अणु पढ़ो_table_data, rw_tbl पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;
	पूर्णांक ret = 0;

	अगर (!rw_tbl->size)
		वापस ret;

	वापस execute_steps(dev, पढ़ो_table_steps,
			     ARRAY_SIZE(पढ़ो_table_steps));
पूर्ण

अटल पूर्णांक opal_ग_लिखो_table(काष्ठा opal_dev *dev,
			    काष्ठा opal_पढ़ो_ग_लिखो_table *rw_tbl)
अणु
	स्थिर काष्ठा opal_step ग_लिखो_table_steps[] = अणु
		अणु start_admin1LSP_opal_session, &rw_tbl->key पूर्ण,
		अणु ग_लिखो_table_data, rw_tbl पूर्ण,
		अणु end_opal_session, पूर्ण
	पूर्ण;
	पूर्णांक ret = 0;

	अगर (!rw_tbl->size)
		वापस ret;

	वापस execute_steps(dev, ग_लिखो_table_steps,
			     ARRAY_SIZE(ग_लिखो_table_steps));
पूर्ण

अटल पूर्णांक opal_generic_पढ़ो_ग_लिखो_table(काष्ठा opal_dev *dev,
					 काष्ठा opal_पढ़ो_ग_लिखो_table *rw_tbl)
अणु
	पूर्णांक ret, bit_set;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev);

	bit_set = fls64(rw_tbl->flags) - 1;
	चयन (bit_set) अणु
	हाल OPAL_READ_TABLE:
		ret = opal_पढ़ो_table(dev, rw_tbl);
		अवरोध;
	हाल OPAL_WRITE_TABLE:
		ret = opal_ग_लिखो_table(dev, rw_tbl);
		अवरोध;
	शेष:
		pr_debug("Invalid bit set in the flag (%016llx).\n",
			 rw_tbl->flags);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&dev->dev_lock);

	वापस ret;
पूर्ण

पूर्णांक sed_ioctl(काष्ठा opal_dev *dev, अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	व्योम *p;
	पूर्णांक ret = -ENOTTY;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	अगर (!dev)
		वापस -ENOTSUPP;
	अगर (!dev->supported)
		वापस -ENOTSUPP;

	p = memdup_user(arg, _IOC_SIZE(cmd));
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);

	चयन (cmd) अणु
	हाल IOC_OPAL_SAVE:
		ret = opal_save(dev, p);
		अवरोध;
	हाल IOC_OPAL_LOCK_UNLOCK:
		ret = opal_lock_unlock(dev, p);
		अवरोध;
	हाल IOC_OPAL_TAKE_OWNERSHIP:
		ret = opal_take_ownership(dev, p);
		अवरोध;
	हाल IOC_OPAL_ACTIVATE_LSP:
		ret = opal_activate_lsp(dev, p);
		अवरोध;
	हाल IOC_OPAL_SET_PW:
		ret = opal_set_new_pw(dev, p);
		अवरोध;
	हाल IOC_OPAL_ACTIVATE_USR:
		ret = opal_activate_user(dev, p);
		अवरोध;
	हाल IOC_OPAL_REVERT_TPR:
		ret = opal_reverttper(dev, p, false);
		अवरोध;
	हाल IOC_OPAL_LR_SETUP:
		ret = opal_setup_locking_range(dev, p);
		अवरोध;
	हाल IOC_OPAL_ADD_USR_TO_LR:
		ret = opal_add_user_to_lr(dev, p);
		अवरोध;
	हाल IOC_OPAL_ENABLE_DISABLE_MBR:
		ret = opal_enable_disable_shaकरोw_mbr(dev, p);
		अवरोध;
	हाल IOC_OPAL_MBR_DONE:
		ret = opal_set_mbr_करोne(dev, p);
		अवरोध;
	हाल IOC_OPAL_WRITE_SHADOW_MBR:
		ret = opal_ग_लिखो_shaकरोw_mbr(dev, p);
		अवरोध;
	हाल IOC_OPAL_ERASE_LR:
		ret = opal_erase_locking_range(dev, p);
		अवरोध;
	हाल IOC_OPAL_SECURE_ERASE_LR:
		ret = opal_secure_erase_locking_range(dev, p);
		अवरोध;
	हाल IOC_OPAL_PSID_REVERT_TPR:
		ret = opal_reverttper(dev, p, true);
		अवरोध;
	हाल IOC_OPAL_GENERIC_TABLE_RW:
		ret = opal_generic_पढ़ो_ग_लिखो_table(dev, p);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	kमुक्त(p);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sed_ioctl);
