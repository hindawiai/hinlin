<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVM Express device driver tracepoपूर्णांकs
 * Copyright (c) 2018 Johannes Thumshirn, SUSE Linux GmbH
 */

#समावेश <यंत्र/unaligned.h>
#समावेश "trace.h"

अटल स्थिर अक्षर *nvme_trace_delete_sq(काष्ठा trace_seq *p, u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u16 sqid = get_unaligned_le16(cdw10);

	trace_seq_म_लिखो(p, "sqid=%u", sqid);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvme_trace_create_sq(काष्ठा trace_seq *p, u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u16 sqid = get_unaligned_le16(cdw10);
	u16 qsize = get_unaligned_le16(cdw10 + 2);
	u16 sq_flags = get_unaligned_le16(cdw10 + 4);
	u16 cqid = get_unaligned_le16(cdw10 + 6);


	trace_seq_म_लिखो(p, "sqid=%u, qsize=%u, sq_flags=0x%x, cqid=%u",
			 sqid, qsize, sq_flags, cqid);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvme_trace_delete_cq(काष्ठा trace_seq *p, u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u16 cqid = get_unaligned_le16(cdw10);

	trace_seq_म_लिखो(p, "cqid=%u", cqid);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvme_trace_create_cq(काष्ठा trace_seq *p, u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u16 cqid = get_unaligned_le16(cdw10);
	u16 qsize = get_unaligned_le16(cdw10 + 2);
	u16 cq_flags = get_unaligned_le16(cdw10 + 4);
	u16 irq_vector = get_unaligned_le16(cdw10 + 6);

	trace_seq_म_लिखो(p, "cqid=%u, qsize=%u, cq_flags=0x%x, irq_vector=%u",
			 cqid, qsize, cq_flags, irq_vector);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvme_trace_admin_identअगरy(काष्ठा trace_seq *p, u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u8 cns = cdw10[0];
	u16 ctrlid = get_unaligned_le16(cdw10 + 2);

	trace_seq_म_लिखो(p, "cns=%u, ctrlid=%u", cns, ctrlid);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvme_trace_admin_get_features(काष्ठा trace_seq *p,
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

अटल स्थिर अक्षर *nvme_trace_get_lba_status(काष्ठा trace_seq *p,
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

अटल स्थिर अक्षर *nvme_trace_admin_क्रमmat_nvm(काष्ठा trace_seq *p, u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u8 lbaf = cdw10[0] & 0xF;
	u8 mset = (cdw10[0] >> 4) & 0x1;
	u8 pi = (cdw10[0] >> 5) & 0x7;
	u8 pil = cdw10[1] & 0x1;
	u8 ses = (cdw10[1] >> 1) & 0x7;

	trace_seq_म_लिखो(p, "lbaf=%u, mset=%u, pi=%u, pil=%u, ses=%u",
			lbaf, mset, pi, pil, ses);

	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvme_trace_पढ़ो_ग_लिखो(काष्ठा trace_seq *p, u8 *cdw10)
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

अटल स्थिर अक्षर *nvme_trace_dsm(काष्ठा trace_seq *p, u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	trace_seq_म_लिखो(p, "nr=%u, attributes=%u",
			 get_unaligned_le32(cdw10),
			 get_unaligned_le32(cdw10 + 4));
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvme_trace_zone_mgmt_send(काष्ठा trace_seq *p, u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u64 slba = get_unaligned_le64(cdw10);
	u8 zsa = cdw10[12];
	u8 all = cdw10[13];

	trace_seq_म_लिखो(p, "slba=%llu, zsa=%u, all=%u", slba, zsa, all);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvme_trace_zone_mgmt_recv(काष्ठा trace_seq *p, u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u64 slba = get_unaligned_le64(cdw10);
	u32 numd = get_unaligned_le32(cdw10 + 8);
	u8 zra = cdw10[12];
	u8 zrasf = cdw10[13];
	u8 pr = cdw10[14];

	trace_seq_म_लिखो(p, "slba=%llu, numd=%u, zra=%u, zrasf=%u, pr=%u",
			 slba, numd, zra, zrasf, pr);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvme_trace_common(काष्ठा trace_seq *p, u8 *cdw10)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	trace_seq_म_लिखो(p, "cdw10=%*ph", 24, cdw10);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

स्थिर अक्षर *nvme_trace_parse_admin_cmd(काष्ठा trace_seq *p,
				       u8 opcode, u8 *cdw10)
अणु
	चयन (opcode) अणु
	हाल nvme_admin_delete_sq:
		वापस nvme_trace_delete_sq(p, cdw10);
	हाल nvme_admin_create_sq:
		वापस nvme_trace_create_sq(p, cdw10);
	हाल nvme_admin_delete_cq:
		वापस nvme_trace_delete_cq(p, cdw10);
	हाल nvme_admin_create_cq:
		वापस nvme_trace_create_cq(p, cdw10);
	हाल nvme_admin_identअगरy:
		वापस nvme_trace_admin_identअगरy(p, cdw10);
	हाल nvme_admin_get_features:
		वापस nvme_trace_admin_get_features(p, cdw10);
	हाल nvme_admin_get_lba_status:
		वापस nvme_trace_get_lba_status(p, cdw10);
	हाल nvme_admin_क्रमmat_nvm:
		वापस nvme_trace_admin_क्रमmat_nvm(p, cdw10);
	शेष:
		वापस nvme_trace_common(p, cdw10);
	पूर्ण
पूर्ण

स्थिर अक्षर *nvme_trace_parse_nvm_cmd(काष्ठा trace_seq *p,
				     u8 opcode, u8 *cdw10)
अणु
	चयन (opcode) अणु
	हाल nvme_cmd_पढ़ो:
	हाल nvme_cmd_ग_लिखो:
	हाल nvme_cmd_ग_लिखो_zeroes:
	हाल nvme_cmd_zone_append:
		वापस nvme_trace_पढ़ो_ग_लिखो(p, cdw10);
	हाल nvme_cmd_dsm:
		वापस nvme_trace_dsm(p, cdw10);
	हाल nvme_cmd_zone_mgmt_send:
		वापस nvme_trace_zone_mgmt_send(p, cdw10);
	हाल nvme_cmd_zone_mgmt_recv:
		वापस nvme_trace_zone_mgmt_recv(p, cdw10);
	शेष:
		वापस nvme_trace_common(p, cdw10);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *nvme_trace_fabrics_property_set(काष्ठा trace_seq *p, u8 *spc)
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

अटल स्थिर अक्षर *nvme_trace_fabrics_connect(काष्ठा trace_seq *p, u8 *spc)
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

अटल स्थिर अक्षर *nvme_trace_fabrics_property_get(काष्ठा trace_seq *p, u8 *spc)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u8 attrib = spc[0];
	u32 ofst = get_unaligned_le32(spc + 4);

	trace_seq_म_लिखो(p, "attrib=%u, ofst=0x%x", attrib, ofst);
	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *nvme_trace_fabrics_common(काष्ठा trace_seq *p, u8 *spc)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	trace_seq_म_लिखो(p, "specific=%*ph", 24, spc);
	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

स्थिर अक्षर *nvme_trace_parse_fabrics_cmd(काष्ठा trace_seq *p,
		u8 fctype, u8 *spc)
अणु
	चयन (fctype) अणु
	हाल nvme_fabrics_type_property_set:
		वापस nvme_trace_fabrics_property_set(p, spc);
	हाल nvme_fabrics_type_connect:
		वापस nvme_trace_fabrics_connect(p, spc);
	हाल nvme_fabrics_type_property_get:
		वापस nvme_trace_fabrics_property_get(p, spc);
	शेष:
		वापस nvme_trace_fabrics_common(p, spc);
	पूर्ण
पूर्ण

स्थिर अक्षर *nvme_trace_disk_name(काष्ठा trace_seq *p, अक्षर *name)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	अगर (*name)
		trace_seq_म_लिखो(p, "disk=%s, ", name);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

EXPORT_TRACEPOINT_SYMBOL_GPL(nvme_sq);
