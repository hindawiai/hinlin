<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVM Express target device driver tracepoपूर्णांकs
 * Copyright (c) 2018 Johannes Thumshirn, SUSE Linux GmbH
 */

#समावेश <यंत्र/unaligned.h>
#समावेश "trace.h"

अटल स्थिर अक्षर *nvmet_trace_admin_identअगरy(काष्ठा trace_seq *p, u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u8 cns = cdw10[0];
	u16 ctrlid = get_unaligned_le16(cdw10 + 2);

	trace_seq_म_लिखो(p, "cns=%u, ctrlid=%u", cns, ctrlid);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvmet_trace_admin_get_features(काष्ठा trace_seq *p,
						 u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u8 fid = cdw10[0];
	u8 sel = cdw10[1] & 0x7;
	u32 cdw11 = get_unaligned_le32(cdw10 + 4);

	trace_seq_म_लिखो(p, "fid=0x%x sel=0x%x cdw11=0x%x", fid, sel, cdw11);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvmet_trace_get_lba_status(काष्ठा trace_seq *p,
					     u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u64 slba = get_unaligned_le64(cdw10);
	u32 mndw = get_unaligned_le32(cdw10 + 8);
	u16 rl = get_unaligned_le16(cdw10 + 12);
	u8 atype = cdw10[15];

	trace_seq_म_लिखो(p, "slba=0x%llx, mndw=0x%x, rl=0x%x, atype=%u",
			slba, mndw, rl, atype);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvmet_trace_पढ़ो_ग_लिखो(काष्ठा trace_seq *p, u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u64 slba = get_unaligned_le64(cdw10);
	u16 length = get_unaligned_le16(cdw10 + 8);
	u16 control = get_unaligned_le16(cdw10 + 10);
	u32 dsmgmt = get_unaligned_le32(cdw10 + 12);
	u32 reftag = get_unaligned_le32(cdw10 +  16);

	trace_seq_म_लिखो(p,
			 "slba=%llu, len=%u, ctrl=0x%x, dsmgmt=%u, reftag=%u",
			 slba, length, control, dsmgmt, reftag);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvmet_trace_dsm(काष्ठा trace_seq *p, u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	trace_seq_म_लिखो(p, "nr=%u, attributes=%u",
			 get_unaligned_le32(cdw10),
			 get_unaligned_le32(cdw10 + 4));
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvmet_trace_common(काष्ठा trace_seq *p, u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	trace_seq_म_लिखो(p, "cdw10=%*ph", 24, cdw10);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

स्थिर अक्षर *nvmet_trace_parse_admin_cmd(काष्ठा trace_seq *p,
		u8 opcode, u8 *cdw10)
अणु
	चयन (opcode) अणु
	हाल nvme_admin_identअगरy:
		वापस nvmet_trace_admin_identअगरy(p, cdw10);
	हाल nvme_admin_get_features:
		वापस nvmet_trace_admin_get_features(p, cdw10);
	हाल nvme_admin_get_lba_status:
		वापस nvmet_trace_get_lba_status(p, cdw10);
	शेष:
		वापस nvmet_trace_common(p, cdw10);
	पूर्ण
पूर्ण

स्थिर अक्षर *nvmet_trace_parse_nvm_cmd(काष्ठा trace_seq *p,
		u8 opcode, u8 *cdw10)
अणु
	चयन (opcode) अणु
	हाल nvme_cmd_पढ़ो:
	हाल nvme_cmd_ग_लिखो:
	हाल nvme_cmd_ग_लिखो_zeroes:
		वापस nvmet_trace_पढ़ो_ग_लिखो(p, cdw10);
	हाल nvme_cmd_dsm:
		वापस nvmet_trace_dsm(p, cdw10);
	शेष:
		वापस nvmet_trace_common(p, cdw10);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *nvmet_trace_fabrics_property_set(काष्ठा trace_seq *p,
		u8 *spc)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u8 attrib = spc[0];
	u32 ofst = get_unaligned_le32(spc + 4);
	u64 value = get_unaligned_le64(spc + 8);

	trace_seq_म_लिखो(p, "attrib=%u, ofst=0x%x, value=0x%llx",
			 attrib, ofst, value);
	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvmet_trace_fabrics_connect(काष्ठा trace_seq *p,
		u8 *spc)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u16 recfmt = get_unaligned_le16(spc);
	u16 qid = get_unaligned_le16(spc + 2);
	u16 sqsize = get_unaligned_le16(spc + 4);
	u8 cattr = spc[6];
	u32 kato = get_unaligned_le32(spc + 8);

	trace_seq_म_लिखो(p, "recfmt=%u, qid=%u, sqsize=%u, cattr=%u, kato=%u",
			 recfmt, qid, sqsize, cattr, kato);
	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvmet_trace_fabrics_property_get(काष्ठा trace_seq *p,
		u8 *spc)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u8 attrib = spc[0];
	u32 ofst = get_unaligned_le32(spc + 4);

	trace_seq_म_लिखो(p, "attrib=%u, ofst=0x%x", attrib, ofst);
	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvmet_trace_fabrics_common(काष्ठा trace_seq *p, u8 *spc)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	trace_seq_म_लिखो(p, "specific=%*ph", 24, spc);
	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

स्थिर अक्षर *nvmet_trace_parse_fabrics_cmd(काष्ठा trace_seq *p,
		u8 fctype, u8 *spc)
अणु
	चयन (fctype) अणु
	हाल nvme_fabrics_type_property_set:
		वापस nvmet_trace_fabrics_property_set(p, spc);
	हाल nvme_fabrics_type_connect:
		वापस nvmet_trace_fabrics_connect(p, spc);
	हाल nvme_fabrics_type_property_get:
		वापस nvmet_trace_fabrics_property_get(p, spc);
	शेष:
		वापस nvmet_trace_fabrics_common(p, spc);
	पूर्ण
पूर्ण

स्थिर अक्षर *nvmet_trace_disk_name(काष्ठा trace_seq *p, अक्षर *name)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	अगर (*name)
		trace_seq_म_लिखो(p, "disk=%s, ", name);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

स्थिर अक्षर *nvmet_trace_ctrl_name(काष्ठा trace_seq *p, काष्ठा nvmet_ctrl *ctrl)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	/*
	 * XXX: We करोn't know the controller instance beक्रमe executing the
	 * connect command itself because the connect command क्रम the admin
	 * queue will not provide the cntlid which will be allocated in this
	 * command.  In हाल of io queues, the controller instance will be
	 * mapped by the extra data of the connect command.
	 * If we can know the extra data of the connect command in this stage,
	 * we can update this prपूर्णांक statement later.
	 */
	अगर (ctrl)
		trace_seq_म_लिखो(p, "%d", ctrl->cntlid);
	अन्यथा
		trace_seq_म_लिखो(p, "_");
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

